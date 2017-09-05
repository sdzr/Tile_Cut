#include "googleTile.h"

google_grid::google_grid(int level)
{
	ilevel = level;
	if (ilevel < 0 || ilevel>=24)
	{
		std::cout << "level超出规定范围！！" << std::endl;
	}
	max_lng = 180;
	//max_lat = 85.05112877980659;

	max_lat = 90;
}

int google_grid::get_max_row()
{
	return pow(2,ilevel)-1;
}

int google_grid::get_max_col()
{
	return pow(2,ilevel+1) - 1;
}
std::vector<unispace::us_vec2<double>> google_grid::get_Geo_coor(int col, int row)
{
	std::vector<unispace::us_vec2<double>> vec;
	double x = max_lng * 2 / pow(2,ilevel+1);
	double y = max_lat * 2 / pow(2,ilevel);
	unispace::us_vec2<double> temp;
	temp.set_x(col*x-max_lng);
	temp.set_y(max_lat-row*y);
	vec.push_back(temp);

	temp.set_x((col + 1)*x-max_lng);
	temp.set_y(max_lat-row*y);
	vec.push_back(temp);

	temp.set_x((col + 1)*x-max_lng);
	temp.set_y(max_lat-(row + 1)*y);
	vec.push_back(temp);

	temp.set_x((col)*x-max_lng);
	temp.set_y(max_lat-(row + 1)*y);
	vec.push_back(temp);

	return vec;
}

int google_grid::get_col_from_lng(double lng)
{
	int col;
	double x = max_lng * 2 / pow(2,ilevel+1);
	col = floor((lng + max_lng) / x);
	return col;
}

int google_grid::get_row_from_lat(double lat)
{
	int row;
	double y = max_lat * 2 / pow(2,ilevel);
	row = floor((max_lat-lat) / y);
	return row;
}