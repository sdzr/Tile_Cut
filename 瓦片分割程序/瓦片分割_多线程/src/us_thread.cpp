#include "us_thread.h"
//用于变量共享
std::mutex some_mutex;

us_thread::us_thread()
{
	return;
}

void us_thread::ini_thread(int lf, int rt, int up, int dw, google_grid *grid, std::vector<unispace::us_image_basic_meta> *metalist, char *str)
{
	i_lf = lf;
	i_rt = rt;
	i_up = up;
	i_dw = dw;
	g_grid.ilevel = grid->ilevel;
	v_metalist = *metalist;
	strcpy(s_str, str);
}


us_thread::us_thread(int lf, int rt, int up, int dw, google_grid *grid, std::vector<unispace::us_image_basic_meta> *metalist, char *str)
{
	i_lf = lf;
	i_rt = rt;
	i_up = up;
	i_dw = dw;
	g_grid.ilevel=grid->ilevel;
	v_metalist = *metalist;
	strcpy(s_str, str);
}

void us_thread::ThreadEntryPoint()
{
	//金字塔的路径.		
	unispace::us_ustring  pyramid_root_path;
	//金字塔的格式
	unispace::us_image::IMAGE_FORMAT pyramid_fmt = unispace::us_image::IMG_FMT_TIF;

	//设置取图输出宽.
	int inOutW = 256;
	//设置取图输出高
	int inOutH = 256;

	//传出取出的位置的中网格的UV
	unispace::us_basic_uv outUV;

	//传出影像像素数据保存的buffer.
	std::vector<uint8_t> outBuf;

	//取图的网格
	unispace::us_vec2<double> gridGeoCorner[4];
	//存储瓦片4角的向量
	std::vector<unispace::us_vec2<double>> vec4;

	//.png数据缓存区
	std::vector<uint8_t> pDst(256 * 256 * 4);



	for (int i = i_lf; i <= i_rt; i++)
	{
		for (int j = i_up; j <= i_dw; j++)
		{
			//由行列号获取瓦片的经纬纵坐标gridCorner.
			vec4 = g_grid.get_Geo_coor(i, j);

			//赋值给gridCorner
			gridGeoCorner[0] = vec4[0];
			gridGeoCorner[1] = vec4[1];
			gridGeoCorner[2] = vec4[2];
			gridGeoCorner[3] = vec4[3];

			//读取瓦片内容到outBuf
			unispace::Point2i pl[4];
			pl[0].set_xy(0, 0);
			pl[1].set_xy(256, 0);
			pl[2].set_xy(256, 256);
			pl[3].set_xy(0, 256);
			outUV.set_uv(pl, 256, 256);
			//单个瓦片获取到outBuf成功
			if (unispace::get_grid_image_rgba_buffer_aux(v_metalist, gridGeoCorner, &outBuf, &inOutW, &inOutH, outUV, pyramid_root_path, pyramid_fmt, false) < 1)
			{
				continue;
			};

			long length = outBuf.size();
			unsigned int  temp = 0;
			int count1 = 0;
			for (int i = 0; i <1024; i=i+4)
			{
				temp = outBuf[i];
				temp << 8;
				temp=temp&outBuf[i + 1];
				temp<< 8;
				temp = temp&outBuf[i + 2];
				if (temp != 0)
				{
					count1++;
				}	
			}
			int count2 = 0;
			for (int i = 1024*255; i < 256*1024; i=i+4)
			{
				temp = outBuf[i];
				temp << 8;
				temp = temp&outBuf[i + 1];
				temp << 8;
				temp = temp&outBuf[i + 2];
				if (temp != 0)
				{
					count2++;
				}			
			}
			if (count1 > 0 || count2 > 0)
			{
				//将瓦片保存到文件中。
				//现将像素数据转成.png数据。
				unispace::encode_rgba8888_to_png32(outBuf.data(), inOutW, inOutH, &pDst);
				//保存的瓦片文件名及绝对路径，行_列.png
				char filename[512];
				//打开文件，若文件不存在，则创建文件,文件名：行_列.png
				char te[100];
				std::ofstream outfile;
				strcpy(filename, s_str);
				strcat(filename, "\\");

				//造子文件夹
				int unit = (pow(2, floor(g_grid.ilevel / 2) - 3)) * 16;
				int temp1 = i / unit;
				int temp2 = (g_grid.get_max_row() - j) / unit;
				if (g_grid.ilevel <= 11)
				{
					if (temp1<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp1, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					if (temp2<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp2, te, 10);
					strcat(filename, te);
					_mkdir(filename);
					strcat(filename, "\\");




					if (i < 1000 && i >= 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i <100 && i >= 10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(i, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					//
					if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j <100 && g_grid.get_max_row() - j >= 10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(g_grid.get_max_row() - j, te, 10);
					strcat(filename, te);
				}
				else if (g_grid.ilevel <= 17)
				{
					if (temp1<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp1 >= 10 && temp1 < 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp1, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					if (temp2<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp2 >= 10 && temp2 < 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp2, te, 10);
					strcat(filename, te);
					_mkdir(filename);
					strcat(filename, "\\");




					if (i < 100000 && i >= 10000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i <10000 && i >= 1000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 1000 && i >= 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 100 && i >= 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(i, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					//
					if (g_grid.get_max_row() - j < 100000 && g_grid.get_max_row() - j >= 10000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j <10000 && g_grid.get_max_row() - j >= 1000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 100 && g_grid.get_max_row() - j >= 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(g_grid.get_max_row() - j, te, 10);
					strcat(filename, te);
				}
				else if (g_grid.ilevel <= 24)
				{
					if (temp1<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp1 >= 10 && temp1 < 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp1 >= 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp1, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					if (temp2<10)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp2 >= 10 && temp2 < 100)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (temp2 >= 100 && temp2<1000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(temp2, te, 10);
					strcat(filename, te);
					_mkdir(filename);
					strcat(filename, "\\");




					if (i < 10000000 && i >= 1000000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i <1000000 && i >= 100000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 100000 && i >= 10000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 10000 && i >= 1000)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 1000 && i >= 100)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 100 && i >= 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (i < 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(i, te, 10);
					strcat(filename, te);
					strcat(filename, "_");
					//
					if (g_grid.get_max_row() - j < 10000000 && g_grid.get_max_row() - j >= 1000000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j <1000000 && g_grid.get_max_row() - j >= 100000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 100000 && g_grid.get_max_row() - j >= 10000)
					{
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 10000 && g_grid.get_max_row() - j >= 1000)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 100 && g_grid.get_max_row() - j >= 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					if (g_grid.get_max_row() - j < 10)
					{
						itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
						_itoa(0, te, 10);
						strcat(filename, te);
					}
					_itoa(g_grid.get_max_row() - j, te, 10);
					strcat(filename, te);
				}




				strcat(filename, ".png");
				//将造出的.png空文件打开
				outfile.open(filename, std::ios::binary | std::ios::trunc);
				outfile.write((const char*)pDst.data(), pDst.size());
				//关闭的打开的文件
				outfile.close();


				//给共享变量上锁保证计数是正确的。
				some_mutex.lock();
				google_grid::count++;
				some_mutex.unlock();
			}
			else
			{
				bool  check = false;
				for (long i = 3; i <length; i = i + 4)
				{					
					if ((outBuf[i - 1] != 0) && (outBuf[i - 2] != 0) && (outBuf[i - 3] != 0))
					{
						check = true;
						break;
					}					
				}
				if (check == true)
				{
					//将瓦片保存到文件中。
					//现将像素数据转成.png数据。
					unispace::encode_rgba8888_to_png32(outBuf.data(), inOutW, inOutH, &pDst);
					//保存的瓦片文件名及绝对路径，行_列.png
					char filename[512];
					//打开文件，若文件不存在，则创建文件,文件名：行_列.png
					char te[100];
					std::ofstream outfile;
					strcpy(filename, s_str);
					strcat(filename, "\\");

					//造子文件夹
					int unit = (pow(2,floor(g_grid.ilevel / 2) - 3)) * 16;
					int temp1 = i / unit;
					int temp2 = (g_grid.get_max_row() - j) / unit;
					if (g_grid.ilevel <= 11)
					{
						if (temp1<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp1, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						if (temp2<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp2, te, 10);
						strcat(filename, te);
						_mkdir(filename);
						strcat(filename, "\\");




						if (i < 1000 && i >= 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i <100 && i >= 10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(i, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						//
						if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j <100 && g_grid.get_max_row() - j >= 10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(g_grid.get_max_row() - j, te, 10);
						strcat(filename, te);
					}
					else if (g_grid.ilevel <= 17)
					{
						if (temp1<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp1 >= 10 && temp1 < 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp1, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						if (temp2<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp2 >= 10 && temp2 < 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp2, te, 10);
						strcat(filename, te);
						_mkdir(filename);
						strcat(filename, "\\");




						if (i < 100000 && i >= 10000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i <10000 && i >= 1000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 1000&&i>=100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 100 && i>=10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(i, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						//
						if (g_grid.get_max_row() - j < 100000 && g_grid.get_max_row() - j >= 10000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j <10000 && g_grid.get_max_row() - j>= 1000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 100 && g_grid.get_max_row() - j >= 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(g_grid.get_max_row() - j, te, 10);
						strcat(filename, te);
					}
					else if (g_grid.ilevel<=24)
					{
						if (temp1<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp1 >= 10 && temp1 < 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp1 >= 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp1, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						if (temp2<10)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp2 >= 10 && temp2 < 100)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (temp2 >= 100&&temp2<1000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(temp2, te, 10);
						strcat(filename, te);
						_mkdir(filename);
						strcat(filename, "\\");




						if (i < 10000000 && i >= 1000000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i <1000000 && i >= 100000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 100000 && i >= 10000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 10000 && i >= 1000)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 1000&&i>=100)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 100 && i >= 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (i < 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(i, te, 10);
						strcat(filename, te);
						strcat(filename, "_");
						//
						if (g_grid.get_max_row() - j < 10000000 && g_grid.get_max_row() - j >= 1000000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j <1000000 && g_grid.get_max_row() - j >= 100000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 100000 && g_grid.get_max_row() - j >= 10000)
						{
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 10000 && g_grid.get_max_row() - j >= 1000)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 1000 && g_grid.get_max_row() - j >= 100)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 100 && g_grid.get_max_row() - j >= 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						if (g_grid.get_max_row() - j < 10)
						{
							itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
							_itoa(0, te, 10);
							strcat(filename, te);
						}
						_itoa(g_grid.get_max_row() - j, te, 10);
						strcat(filename, te);
					}
					
									


					strcat(filename, ".png");
					//将造出的.png空文件打开
					outfile.open(filename, std::ios::binary | std::ios::trunc);
					outfile.write((const char*)pDst.data(), pDst.size());
					//关闭的打开的文件
					outfile.close();


					//给共享变量上锁保证计数是正确的。
					some_mutex.lock();
					google_grid::count++;
					some_mutex.unlock();
				}
				else
				{
					continue;
				}
			}


			//long length = outBuf.size();
			//bool a = (outBuf[3] != 0) && (outBuf[length - 1] != 0)&&(outBuf[0]!=0) && (outBuf[1] != 0) && (outBuf[2] != 0);
			////为节约时间，先用if进行初判，若有可能透明加全黑，或全黑。则在进行细判排除。
			//if (a)
			//{
			//	//将瓦片保存到文件中。
			//	//现将像素数据转成.png数据。
			//	unispace::encode_rgba8888_to_png32(outBuf.data(), inOutW, inOutH, &pDst);
			//	//保存的瓦片文件名及绝对路径，行_列.png
			//	char filename[256];
			//	//打开文件，若文件不存在，则创建文件,文件名：行_列.png
			//	char te[100];
			//	std::ofstream outfile;
			//	strcpy(filename, s_str);
			//	strcat(filename, "\\");
			//	_itoa(i, te, 10);
			//	strcat(filename, te);
			//	strcat(filename, "_");
			//	_itoa(j, te, 10);
			//	strcat(filename, te);
			//	strcat(filename, ".png");
			//	//将造出的.png空文件打开
			//	outfile.open(filename, std::ios::binary | std::ios::trunc);
			//	outfile.write((const char*)pDst.data(), pDst.size());
			//	//关闭的打开的文件
			//	outfile.close();


			//	//给共享变量上锁保证计数是正确的。
			//	some_mutex.lock();
			//	google_grid::count++;
			//	some_mutex.unlock();
			//}
			//else
			//{
			//	bool  check =false;
			//	for (long i = 3; i <length ; i=i+4)
			//	{
			//		if (outBuf[i] != 0)
			//		{
			//			if ((outBuf[i-1]!=0)&&(outBuf[i-2]!=0)&&(outBuf[i-3]!=0))
			//			{
			//				check=true;	
			//				break;
			//			}						

			//		}
			//	}
			//	if (check==true)
			//	{
			//		//将瓦片保存到文件中。
			//		//现将像素数据转成.png数据。
			//		unispace::encode_rgba8888_to_png32(outBuf.data(), inOutW, inOutH, &pDst);
			//		//保存的瓦片文件名及绝对路径，行_列.png
			//		char filename[256];
			//		//打开文件，若文件不存在，则创建文件,文件名：行_列.png
			//		char te[100];
			//		std::ofstream outfile;
			//		strcpy(filename, s_str);
			//		strcat(filename, "\\");
			//		_itoa(i, te, 10);
			//		strcat(filename, te);
			//		strcat(filename, "_");
			//		_itoa(j, te, 10);
			//		strcat(filename, te);
			//		strcat(filename, ".png");
			//		//将造出的.png空文件打开
			//		outfile.open(filename, std::ios::binary | std::ios::trunc);
			//		outfile.write((const char*)pDst.data(), pDst.size());
			//		//关闭的打开的文件
			//		outfile.close();


			//		//给共享变量上锁保证计数是正确的。
			//		some_mutex.lock();
			//		google_grid::count++;
			//		some_mutex.unlock();
			//	}
			//	else
			//	{
			//		continue;
			//	}
			//	
			//}
			
		}
	}
}