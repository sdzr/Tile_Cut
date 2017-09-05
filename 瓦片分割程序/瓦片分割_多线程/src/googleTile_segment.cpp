#include "googleTile_segment.h"
#include <time.h>

//瓦片数计数
int google_grid::count = 0;
//读取指定目录下的.tif图像文件
//将文件分割成指定等级的瓦片
//瓦片以.png的格式保存
//指定保存瓦片文件夹的绝对路径
//瓦片文件夹格式为：在指定文件夹下，每个级别的瓦片保存到一个文件夹下，文件夹名称：level_级别
//瓦片命名规则：瓦片在谷歌瓦片的行列号，名称：行号_列号.png
bool  googleTile_segment(char *srcDr, int level_start, int level_end, char *destDrec, int thread_num)
{
	//控制瓦片级别
	if (level_start < 6 || level_start>24)
	{
		std::cout <<"瓦片级别超出范围" << std::endl;
		return false;
	}
	if (level_end < 6 || level_end>24)
	{
		std::cout << "瓦片级别超出范围" << std::endl;
		return false;
	}
	time_t time1;
	time_t time2;
	time(&time1);
	std::cout << "分割开始：" << ctime(&time1) << std::endl;
	//目录转码
	unispace::us_ustring  srcDrec(srcDr);	

	if (!srcDrec.is_utf8_encode())
	{
		srcDrec = unispace::us_ustring::from_gbk(srcDr);
	}

	if (thread_num<=0|thread_num>1000)
	{
		std::cout << "线程输入超出范围" << std::endl;
		exit(1);
	}
	//行列范围
	int lf, rt, up, dw;
	//设置取图输出宽.
	int inOutW = 256;
	//设置取图输出高
	int inOutH = 256;
	//传出影像像素数据保存的buffer.
	std::vector<uint8_t> outBuf;
	//金字塔的路径.		
	unispace::us_ustring  pyramid_root_path;
	//金字塔的格式
	unispace::us_image::IMAGE_FORMAT pyramid_fmt = unispace::us_image::IMG_FMT_TIF;
	//.png数据缓存区
	std::vector<uint8_t> pDst(256 * 256 * 4);


		
	//获取文件路径下的目录，存储到vector。
	std::vector<unispace::us_ustring> list;
	unispace::us_ustring filter("*.tif");
	list = unispace::filesystem::list_entry(srcDrec, filter);
	
	if (list.size() == 0)
	{
		std::cout << "指定源路径下没有可用的.tif 文件" << std::endl;
		return false;
	}
	//影像列表,从指定路径读取元数据
	unispace::us_image_basic_meta out_meta;
	std::vector<unispace::us_image_basic_meta> metalist;

	//将第一张图片的经纬度地理范围，用来初始化图集的外包矩形经纬度范围。
	unispace::generate_image_meta(srcDrec + "\\" + list[0], &out_meta);
	metalist.push_back(out_meta);

	//图集外包框的经纬度地理范围。
	unispace::us_geo_rect max_geo_rect = out_meta.m_geo_rect;

	for (int i = 1; i < list.size(); i++)
	{
		unispace::generate_image_meta(srcDrec + "\\" + list[i], &out_meta);
		//寻找图集的外包框经纬度范围。
		if (max_geo_rect.get_north() < out_meta.m_geo_rect.get_north())
		{
			max_geo_rect.set_north(out_meta.m_geo_rect.get_north());
		}

		if (max_geo_rect.get_south() > out_meta.m_geo_rect.get_south())
		{
			max_geo_rect.set_south(out_meta.m_geo_rect.get_south());
		}

		if (max_geo_rect.get_west() > out_meta.m_geo_rect.get_west())
		{
			max_geo_rect.set_west(out_meta.m_geo_rect.get_west());
		}

		if (max_geo_rect.get_east() < out_meta.m_geo_rect.get_east())
		{
			max_geo_rect.set_east(out_meta.m_geo_rect.get_east());
		}
		metalist.push_back(out_meta);
	}
	

	//在各级level下，生成网格，切割瓦片。
	for (int level = level_start; level <= level_end; level++)
	{
		//每一级分割所花费的时间。
		time_t time_s;
		time_t time_e;
		time_s = time(NULL);
		//每一级的瓦片计数。
		google_grid::count = 0;
		//初始化网格。
		google_grid grid(level);

		//找出在此网格下，图集外包矩形所确定的网格行列范围。max_geo_rect
		lf = grid.get_col_from_lng(max_geo_rect.get_west());
		rt = grid.get_col_from_lng(max_geo_rect.get_east());
		up = grid.get_row_from_lat(max_geo_rect.get_north());
		dw = grid.get_row_from_lat(max_geo_rect.get_south());

		//level整形转字符串
		char s[4];
		_itoa(level, s, 10);
		//到此可知，图片集在各级别下，需要取图的瓦片行列坐标范围。
		//创建文件夹，命名规则为level_i,i为级别数。
		char str[256];
		strcpy(str, destDrec);
		strcat(str, "\\");
		if (level < 10)
		{
			strcat(str, "EPSG_4326_0");
		}
		else
		{
			strcat(str, "EPSG_4326_");
		}
		strcat_s(str, s);
		if (_mkdir(str) == -1)
		{
			std::cout << "指定的存储文件夹不存在,或指定路径下已存在重名子文件夹，请删除子文件夹或更换路径" << std::endl;
			return false;
		};//文件夹创建完成


		  // 决定分多少个线程
		if (thread_num >= (rt - lf + 1)*(dw - up + 1))
		{
			//给每块瓦片开一个线程。
			us_thread *pth=new us_thread[(rt - lf + 1)*(dw - up + 1)];
			//给每个线程重新赋值。
			for (int i = lf; i <=rt ; i++)
			{
				for (int j = up; j <= dw; j++)
				{
					pth[(i - lf) + (j - up)*(rt - lf + 1)].ini_thread(i,i,j,j,&grid,&metalist,str);
				}
			}
			HANDLE *hth = new HANDLE[(rt - lf + 1)*(dw - up + 1)];
			unsigned *ID = new unsigned[(rt - lf + 1)*(dw - up + 1)];
			for (int k = 0; k <(rt - lf + 1)*(dw - up + 1); k++)
			{
				hth[k]= (HANDLE)_beginthreadex(NULL, 0, us_thread::ThreadStaticEntryPoint, &pth[k], CREATE_SUSPENDED, &ID[k]);
				if (hth[k]==0)
				{
					std::cout << "线程"<<level<<k<<"创建失败" << std::endl;
					exit(1);
				}
			}
			//激活线程
			for (int i = 0; i <(rt - lf + 1)*(dw - up + 1); i++)
			{
				ResumeThread(hth[i]);
			}
			//无限等待线程执行
			for (int i = 0; i <(rt - lf + 1)*(dw - up + 1); i++)
			{
				WaitForSingleObject(hth[i],INFINITE);
			}
			//执行完毕清理线程
			for (int i = 0; i <(rt - lf + 1)*(dw - up + 1); i++)
			{
				CloseHandle(hth[i]);
			}
			//释放对象
			delete []pth;
			delete[]ID;
			pth = NULL;
			ID = NULL;
			
			
			//取出该级别下文件名列表。
			/*unispace::us_ustring file_road(str);
			if (!file_road.is_utf8_encode())
			{
				file_road = unispace::us_ustring::from_gbk(str);
			}

			unispace::us_ustring filt("*.png");
			std::vector<unispace::us_ustring> file_list;
			file_list = unispace::filesystem::list_entry(file_road, filt);
*/
			//存储信息到文件
			std::ofstream fp;
			char fname[128];
			strcpy(fname, str);
			strcat(fname, ".txt");
			time_e = time(NULL);
			fp.open(fname, std::ios::trunc);
			fp << "瓦片分割时长：" << time_e - time_s << "  秒" << std::endl;
			fp << "\r\n";
			fp << "图片数量：" << google_grid::count << std::endl;
			//fp << "\r\n";
			//fp << level << "级瓦片的文件名列表：" << std::endl;
			////fp << file_list[3];
			//for (int m = 0; m < file_list.size(); m++)
			//{
			//	fp << "\r\n";
			//	fp << file_list[m];
			//}
			fp.close();


			time_e = time(NULL);
			time_e = time_e - time_s;
			long s, mi, h, d;
			s = time_e % 60;
			mi = (long)floor(time_e / 60) % 60;
			h = (long)floor(time_e / 3600) % 24;
			d = (long)floor(time_e / (3600 * 24));
			std::cout << std::endl;
			std::cout << "级别:" << level << "    瓦片数： " << google_grid::count << "   耗时：" << d << " 天 " << h << " 小时 " << mi << " 分钟 " << s << " 秒" << std::endl;
			std::cout << std::endl;


			continue;
		}
		if (thread_num >= (rt - lf + 1))
		{
			//每一列开一个线程
			us_thread *pth = new us_thread[(rt - lf + 1)];
			//给每一个线程重新赋值
			for (int i = lf; i <= rt; i++)
			{
				pth[i - lf].ini_thread(i, i, up, dw, &grid, &metalist, str);
			}
			HANDLE *hth = new HANDLE[(rt - lf + 1)];
			unsigned *ID = new unsigned[(rt - lf + 1)];
			for (int k = 0; k <(rt - lf + 1); k++)
			{
				hth[k] = (HANDLE)_beginthreadex(NULL, 0, us_thread::ThreadStaticEntryPoint, &pth[k], CREATE_SUSPENDED, &ID[k]);
				if (hth[k] == 0)
				{
					std::cout << "线程" <<level<<k << "创建失败" << std::endl;
					exit(1);
				}
			}
			//激活线程
			for (int i = 0; i <(rt - lf + 1); i++)
			{
				ResumeThread(hth[i]);
			}
			//无限等待线程执行
			for (int i = 0; i <(rt - lf + 1); i++)
			{
				WaitForSingleObject(hth[i], INFINITE);
			}
			//执行完毕清理线程
			for (int i = 0; i <(rt - lf + 1); i++)
			{
				CloseHandle(hth[i]);
			}
			//释放对象
			delete[]pth;
			delete[]ID;
			pth = NULL;
			ID = NULL;

			

			//取出该级别下文件名列表。
			/*unispace::us_ustring file_road(str);
			if (!file_road.is_utf8_encode())
			{
				file_road = unispace::us_ustring::from_gbk(str);
			}

			unispace::us_ustring filt("*.png");
			std::vector<unispace::us_ustring> file_list;
			file_list = unispace::filesystem::list_entry(file_road, filt);*/

			//存储信息到文件
			std::ofstream fp;
			char fname[128];
			strcpy(fname, str);
			strcat(fname, ".txt");
			time_e = time(NULL);
			fp.open(fname, std::ios::trunc);
			fp << "瓦片分割时长：" << time_e - time_s << "  秒" << std::endl;
			fp << "\r\n";
			fp << "图片数量：" << google_grid::count << std::endl;
			//fp << "\r\n";
			//fp << level << "级瓦片的文件名列表：" << std::endl;
			////fp << file_list[3];
			//for (int m = 0; m < file_list.size(); m++)
			//{
			//	fp << "\r\n";
			//	fp << file_list[m];
			//}
			fp.close();


			time_e = time(NULL);
			time_e = time_e - time_s;
			long s, mi, h, d;
			s = time_e % 60;
			mi = (long)floor(time_e / 60) % 60;
			h = (long)floor(time_e / 3600) % 24;
			d = (long)floor(time_e / (3600 * 24));
			std::cout << std::endl;
			std::cout << "级别:" << level << "    瓦片数： " << google_grid::count << "   耗时：" << d << " 天 " << h << " 小时 " << mi << " 分钟 " << s << " 秒" << std::endl;
			std::cout << std::endl;

			continue;
		}

		//thread_num小于（rt-lf+1）时。
		//此时开 thread_num个线程。
		us_thread *pth = new us_thread[thread_num];
		//如果列数是线程数的整数倍。
		if ((rt - lf + 1) % thread_num == 0)
		{
			int width = (rt - lf + 1) / thread_num;
			//重新初始化线程类
			for (int i = 0; i < thread_num; i++)
			{
				pth[i].ini_thread(lf + i*width, lf + (i + 1)*width - 1, up, dw, &grid, &metalist, str);
			}
			HANDLE *hth = new HANDLE[thread_num];
			unsigned *ID = new unsigned[thread_num];
			for (int k = 0; k <thread_num; k++)
			{
				hth[k] = (HANDLE)_beginthreadex(NULL, 0, us_thread::ThreadStaticEntryPoint, &pth[k], CREATE_SUSPENDED, &ID[k]);
				if (hth[k] == 0)
				{
					std::cout << "线程" << level << k << "创建失败" << std::endl;
					exit(1);
				}
			}
			//激活线程
			for (int i = 0; i <thread_num; i++)
			{
				ResumeThread(hth[i]);
			}
			//无限等待线程执行
			for (int i = 0; i <thread_num; i++)
			{
				WaitForSingleObject(hth[i], INFINITE);
			}
			//执行完毕清理线程
			for (int i = 0; i <thread_num; i++)
			{
				CloseHandle(hth[i]);
			}
			//释放对象
			delete[]pth;
			delete[]ID;
			pth = NULL;
			ID = NULL;

			

			////取出该级别下文件名列表。
			//unispace::us_ustring file_road(str);
			//if (!file_road.is_utf8_encode())
			//{
			//	file_road = unispace::us_ustring::from_gbk(str);
			//}

			//unispace::us_ustring filt("*.png");
			//std::vector<unispace::us_ustring> file_list;
			//file_list = unispace::filesystem::list_entry(file_road, filt);

			//存储信息到文件
			std::ofstream fp;
			char fname[128];
			strcpy(fname, str);
			strcat(fname, ".txt");
			time_e = time(NULL);
			fp.open(fname, std::ios::trunc);
			fp << "瓦片分割时长：" << time_e - time_s << "  秒" << std::endl;
			fp << "\r\n";
			fp << "图片数量：" << google_grid::count << std::endl;
			fp << "\r\n";
			//fp << level << "级瓦片的文件名列表：" << std::endl;
			////fp << file_list[3];
			//for (int m = 0; m < file_list.size(); m++)
			//{
			//	fp << "\r\n";
			//	fp << file_list[m];
			//}
			fp.close();


			time_e = time(NULL);
			time_e = time_e - time_s;
			long s, mi, h, d;
			s = time_e % 60;
			mi = (long)floor(time_e / 60) % 60;
			h = (long)floor(time_e / 3600) % 24;
			d = (long)floor(time_e / (3600 * 24));
			std::cout << std::endl;
			std::cout << "级别:" << level << "    瓦片数： " << google_grid::count << "   耗时：" << d << " 天 " << h << " 小时 " << mi << " 分钟 " << s << " 秒" << std::endl;
			std::cout << std::endl;


			continue;
		}
		//如果不是整数倍
		if ((rt - lf + 1) % thread_num != 0)
		{
			int width = floor((rt - lf + 1) / thread_num);
			int lenth = (rt - lf+1) % thread_num;
			//给每一个线程重新赋值。
			for (int i = 0; i < lenth; i++)
			{
				pth[i].ini_thread(lf + i*(width+1), lf + (i + 1)*(width+1) - 1, up, dw, &grid, &metalist, str);
			}
			for (int i = lenth; i < thread_num; i++)
			{
				pth[i].ini_thread(lf + lenth*(width + 1)+(i-lenth)*width, lf + lenth*(width + 1) + (i-lenth+1)*width - 1, up, dw, &grid, &metalist, str);
			}
			HANDLE *hth = new HANDLE[thread_num];
			unsigned *ID = new unsigned[thread_num];
			for (int k = 0; k <thread_num; k++)
			{
				hth[k] = (HANDLE)_beginthreadex(NULL, 0, us_thread::ThreadStaticEntryPoint, &pth[k], CREATE_SUSPENDED, &ID[k]);
				if (hth[k] == 0)
				{
					std::cout << "线程" << level << k << "创建失败" << std::endl;
					exit(1);
				}
			}
			//激活线程
			for (int i = 0; i <thread_num; i++)
			{
				ResumeThread(hth[i]);
			}
			//无限等待线程执行
			for (int i = 0; i <thread_num; i++)
			{
				WaitForSingleObject(hth[i], INFINITE);
			}
			//执行完毕清理线程
			for (int i = 0; i <thread_num; i++)
			{
				CloseHandle(hth[i]);
			}
			//释放对象
			delete[]pth;
			delete[]ID;
			pth = NULL;
			ID = NULL;

			

			////取出该级别下文件名列表。
			//unispace::us_ustring file_road(str);
			//if (!file_road.is_utf8_encode())
			//{
			//	file_road = unispace::us_ustring::from_gbk(str);
			//}

			//unispace::us_ustring filt("*.png");
			//std::vector<unispace::us_ustring> file_list;
			//file_list = unispace::filesystem::list_entry(file_road, filt);

			//存储信息到文件
			std::ofstream fp;
			char fname[128];
			strcpy(fname, str);
			strcat(fname, ".txt");
			time_e = time(NULL);
			fp.open(fname, std::ios::trunc);
			fp << "瓦片分割时长：" << time_e - time_s << "  秒" << std::endl;
			fp << "\r\n";
			fp << "图片数量：" << google_grid::count << std::endl;
			/*fp << "\r\n";
			fp << level << "级瓦片的文件名列表：" << std::endl;
			fp << file_list[3];
			for (int m = 0; m < file_list.size(); m++)
			{
				fp << "\r\n";
				fp << file_list[m];
			}*/
			fp.close();


			time_e = time(NULL);
			time_e = time_e - time_s;
			long s, mi, h, d;
			s = time_e % 60;
			mi = (long)floor(time_e / 60) % 60;
			h = (long)floor(time_e / 3600) % 24;
			d = (long)floor(time_e / (3600 * 24));
			std::cout << std::endl;
			std::cout << "级别:" << level << "    瓦片数： " << google_grid::count << "   耗时：" << d << " 天 " << h << " 小时 " << mi << " 分钟 " << s << " 秒" << std::endl;
			std::cout << std::endl;

			continue;
			
		}


		

		

		
		
	}
		time(&time2);
		std::cout << std::endl;
		std::cout << "分割结束：" << ctime(&time2) << std::endl;
		time2 = time2 - time1;
		long second,min,hour,day;
		second = time2 % 60;
		min = (long)floor(time2 / 60) % 60;
		hour = (long)floor(time2 / 3600) % 24;
		day = (long)floor(time2 / (3600 * 24));
		std::cout << "总耗时：" << day<<" 天 "<<hour<<" 小时 "<<min <<" 分钟 "<<second<<" 秒"<< std::endl;
		std::cout << std::endl;
		system("pause");
		return true;
	
}


