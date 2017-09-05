#include "googleTile_segment.h"
#include <iostream>



int main()
{
	char src[128];

	char destDrec[256];
	char i,j;
	int level_start;
	int level_end;
	int num=100;
	//存储瓦片的文件夹路径必须存在。若不存在，不会自动创建新文件夹。
	//若指定路径下，level_i的文件夹已存在，也不行
	//若level_i的文件夹下已经存在与即将生成的文件重名的文件，也不行。

	while (true)
	{
		std::cout << "请输入.tif源图片所在的位置:" << std::endl;
      std::cout<<std::endl;
		std::cin >> src ;
      std::cout<<std::endl;
		std::cout << "请输入瓦片文件的保存路径：" << std::endl;
      std::cout<<std::endl;
		std::cin >> destDrec;
      std::cout<<std::endl;
		std::cout << "请输入瓦片级别范围(6-24的整数)!" << std::endl;
      std::cout<<std::endl;
		std::cout << "请输入:" << std::endl;
      std::cout<<std::endl;
		std::cin >> level_start;
      std::cout<<std::endl;
		std::cout << "请输入：" << std::endl;
      std::cout<<std::endl;
	  std::cin >> level_end;
	  std::cout << std::endl;
	  std::cout << "是否要输入线程数?（默认100）(y/n)" <<std::endl;
	  std::cout << std::endl;
	  std::cin >> j;
	  if (j == 'y')
	  {
		  std::cout << std::endl;
		  std::cout <<"请输入线程数："<< std::endl;
		  std::cout << std::endl;
		  std::cin >> num;

	  }
		
		if (level_end < level_start)
		{
			level_start = level_start^level_end;
			level_end = level_end^level_start;
			level_start = level_start^level_end;
		}
		std::cout << std::endl;
		if (googleTile_segment(src, level_start, level_end, destDrec,num)==true)
		{
			break;
		}
		std::cout << std::endl;
		std::cout << "是否继续？输入y/n:" << std::endl;
		std::cin >> i;
		if (i == 'n')
		{
			break;
		}

	}
	
}


//int main()
//{
//	char src[128];
//	char  srcDr[128]="C:\\Users\\Ren\\Desktop\\level14";
//	char destDrec[256]= "C:\\Users\\Ren\\Desktop\\瓦片分割14";
//	int level_start=6;
//	int level_end=15;
//	googleTile_segment(srcDr, level_start, level_end, destDrec,100);
//	return(system("pause"));
//}