#pragma once
#include <Windows.h>
#include "googleTile.h"
#include "googleTile_segment.h"
#include "process.h"
#include <mutex>
class us_thread
{
public:
	//参数
	int i_lf;
	int i_rt;
	int i_up;
	int i_dw;
	google_grid g_grid;
	std::vector<unispace::us_image_basic_meta> v_metalist;
	char s_str[256];
public:
	//
	us_thread();
   //初始化类
	us_thread(int lf, int rt, int up, int dw, google_grid *grid, std::vector<unispace::us_image_basic_meta> *metalist, char *str);
	
	//对象重新赋初值。
	void ini_thread(int lf, int rt, int up, int dw, google_grid *grid, std::vector<unispace::us_image_basic_meta> *metalist, char *str);


	//静态入口函数
	static unsigned __stdcall ThreadStaticEntryPoint(void * pThis)
	{
		us_thread * pthX = (us_thread*)pThis;   // the tricky cast
		pthX->ThreadEntryPoint();           // now call the true entry-point-function

											// A thread terminates automatically if it completes execution,
									// or it can terminate itself with a call to _endthread().
		
		return 1;          // the thread exit code
	}

	void ThreadEntryPoint();
};