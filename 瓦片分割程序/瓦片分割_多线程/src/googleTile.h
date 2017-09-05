#pragma once

#include <cstdlib>
#include <iostream>
#include <util\math\us_vec2.hpp>
#include <vector>
#include <math.h>

class google_grid
{
public:
	//0<=level<=24;
	google_grid(int level=6);
	//获取网格最大行数
	int get_max_row();
	//获取最大列数
	int get_max_col();
	//给定瓦片行列号，返回瓦片四个角的经纬坐标。
	std::vector<unispace::us_vec2<double>> get_Geo_coor(int col, int row);
	//给定经度，返回列号。
	int get_col_from_lng(double lng);
	//给定纬度。返回行号。
	int get_row_from_lat(double lat);
	const google_grid &operator=(google_grid &grid)
	{
		return *this;
	}
	int static count;

public:
	int ilevel;
	double max_lng;
	double max_lat;
};

