#include <Windows.h>
#include "googleTile.h"
#include "googleTile_segment.h"


struct pdata
{
	int lf;
	int rt;
	int up;
	int dw;
	google_grid grid;
	std::vector<unispace::us_image_basic_meta> metalist;
	char str[256];
};