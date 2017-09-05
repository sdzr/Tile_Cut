#include "thread_test.h"

void *get_tile(void *threadarg)
{
	struct pdata *mydata;
	mydata = (struct pdata*)threadarg;
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



	for (int i = mydata->lf; i <= mydata->rt; i++)
	{
		for (int j = mydata->up; j <= mydata->dw; j++)
		{
			//由行列号获取瓦片的经纬纵坐标gridCorner.
			vec4 = mydata->grid.get_Geo_coor(i, j);

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
			if (unispace::get_grid_image_rgba_buffer_aux(mydata->metalist, gridGeoCorner, &outBuf, &inOutW, &inOutH, outUV, pyramid_root_path, pyramid_fmt, false) < 1)
			{
				continue;
			};

			//将瓦片保存到文件中。
			//现将像素数据转成.png数据。
			unispace::encode_rgba8888_to_png32(outBuf.data(), inOutW, inOutH, &pDst);

			//保存的瓦片文件名及绝对路径，行_列.png
			char filename[256];
			//打开文件，若文件不存在，则创建文件,文件名：行_列.png
			char te[100];
			std::ofstream outfile;
			strcpy(filename, mydata->str);
			strcat(filename, "\\");
			_itoa(i, te, 10);
			strcat(filename, te);
			strcat(filename, "_");
			_itoa(j, te, 10);
			strcat(filename, te);
			strcat(filename, ".png");
			//将造出的.png空文件打开
			outfile.open(filename, std::ios::binary | std::ios::trunc);
			outfile.write((const char*)pDst.data(), pDst.size());
			//关闭的打开的文件
			outfile.close();

		}
	}
}