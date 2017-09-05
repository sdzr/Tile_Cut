#ifndef __US_IMAGE_HPP__
#define __US_IMAGE_HPP__


#ifndef __US_RECT_HPP__
#include "util/math/us_rect.hpp"
#endif

#ifndef __US_GEO_RECT_HPP__
#include "util/math/us_geo_rect.hpp"
#endif


#ifndef __US_DATA_PROCESS_HPP__
#include "us_data_process.hpp"
#endif


#include <memory>



/******************************************************************
 * us_image实际上是关联到了一个GDALDataset上的数据结构
 * 它并不关联到具体的影像。
 * us_image保存了它自身的范围(rect)和高宽(w/h)。
 * 因为Dataset是实际关联某张影像数据的，所以其高宽是影像
 * 的高宽。而us_image的高宽实际上是通过Dataset去取真实
 * 的影像数据时候的目标大小。
 * 内部的rect范围，指的是这个对象的取图范围是Dataset的
 * 范围中的范围。
 * 
 * us_image  obj1    obj2    obj3  obj4   obj5
 *             \_____ | _____/       \_  __/   
 *                   \|/               \/
 * Dataset          dsetA            dsetB
 *          size [500,600]        [512,1024]
 * 多个us_image可以关联一个Dataset。          
 *
 * 例:  obj4的w=100,h=200.rect为(128,128,w=256,h=512)
 * 那么就是说这个对象要取图的范围是Dataset中512*1024这个范围
 * 中左上角128,128这个点起始，到128+256,128+512这个点所表示
 * 的范围。取出来的图片已经将抽稀为100*200大小的图片。
 ****************************************************************/




namespace unispace
{
	class us_ustring;
	class us_basic_uv;

	/**********************************************************************//**
	 * @class	us_image.
	 * @brief	影像操作类.
	 *			<pre>us_image实际上是关联到了一个GDALDataset上的数据结构
	 *			<b>它并不关联到具体的影像。</b>
	 *			us_image保存了<b>它自身的范围(rect)和高宽(w/h)</b>。
	 *			因为Dataset是实际关联某张影像数据的，所以其高宽是影像
	 *			的高宽。而us_image的高宽实际上是通过Dataset去取真实
	 *			的影像数据时候的目标大小。
	 *			内部的rect范围，指的是这个对象的取图范围是Dataset的
	 *			范围中的范围。
	 *			
	 *			us_image  obj1    obj2    obj3  obj4   obj5
	 *			            \\_____ | _____/       \\_  __/   
	 *			                  \\|/               \\/
	 *			Dataset          dsetA            dsetB
	 *			         size [500,600]        [512,1024]
	 *			多个us_image可以关联一个Dataset。          
	 *
	 *			例:  obj4的w=100,h=200.rect为(128,128,w=256,h=512)
	 *			那么就是说这个对象要取图的范围是Dataset中512*1024这个范围
	 *			中左上角128,128这个点起始，到128+256,128+512这个点所表示
	 *			的范围。取出来的图片已经将抽稀为100*200大小的图片。
	 *			</pre>
	 * @author yimin.liu@unispace-x.com
	 * @date 2016/4/5
	 *************************************************************************/
	class _US_DATA_PROCESS_DLL us_image
	{
	public:
		/** 输出影像格式编码. */
		enum IMAGE_FORMAT
		{
			IMG_FMT_BMP = 0	,	///< BMP位图
			IMG_FMT_TIF		,	///< TIFF图像
			IMG_FMT_GTiff	,	///< GeoTiff
			IMG_FMT_JPEG	,	///< JPEG图像
			IMG_FMT_PNG		,	///< PNG图像
			IMG_FMT_GIF			///< GIF图像
		};
		typedef void* ColorTablePtr;
	public:
		// 从文件构造
		explicit us_image(const us_ustring& imgpath);
		us_image(const us_image& img);

		// 从传入的Dataset构造
		//explicit us_image(GDALDataset* in_dset);


		~us_image();
	public:

		/**********************************************************************//**
		 * @brief	获取逻辑图像宽度(横向像素数).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @return	逻辑图像横向像素数.
		 *************************************************************************/
		int get_width()const;

		/**********************************************************************//**
		 * @brief	获取逻辑图像高度(纵向像素数).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @return	逻辑图像纵向像素数.
		 *************************************************************************/
		int get_height()const;

		/**********************************************************************//**
		 * @brief	获取实际关联的图像的宽度(横向像素数).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 * @return	纵向像素数.
		 *************************************************************************/
		int get_width_from_associated()const;

		/**********************************************************************//**
		 * @brief	获取实际关联的图像的高度(纵向像素数).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 * @return	纵向像素数.
		 *************************************************************************/
		int get_height_from_associated()const;

		/**********************************************************************//**
		 * @brief	获取影像波段数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @return	波段数.
		 *************************************************************************/
		int get_band_count()const;

		/**********************************************************************//**
		 * @brief	获取影像数据类型编号.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/13
		 * @return	获取成功返回像素数据类型编号，失败(获取波段失败)返回-1.
		 * 			|与GDAL中对应的数据类型|含义|
		 * 			|:---|:---|
		 *			|GDT_Unknown  = 0	|	未知或未指定类型|
		 *			|GDT_Byte     = 1	|	8bit无符号整数|
		 *			|GDT_UInt16   = 2	|	16bit无符号整数|
		 *			|GDT_Int16    = 3	|	16bit有符号整数|
		 *			|GDT_UInt32   = 4	|	32bit无符号整数|
		 *			|GDT_Int32    = 5	|	32bit有符号整数|
		 *			|GDT_Float32  = 6	|	32bit有符号浮点数|
		 *			|GDT_Float64  = 7	|	64bit有符号浮点数|
		 *			|GDT_CInt16   = 8	|	16bit有符号整型复数|
		 *			|GDT_CInt32   = 9	|	32bit有符号整型复数|
		 *			|GDT_CFloat32 = 10	|	32bit有符号浮点型复数|
		 *			|GDT_CFloat64 = 11	|	64bit有符号浮点型复数|
		 *			|GDT_TypeCount = 12	|	最大类型编号 + 1 |
		 *************************************************************************/
		int get_data_type()const;


		/**********************************************************************//**
		 * @brief	获取逻辑影像的仿射变换参数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 * @param	[out] outTransform If non-null, the out transform.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool get_geo_transfrom(double* outTransform)const;

		/**********************************************************************//**
		 * @brief	获取实际关联的影像的仿射变换参数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	[out] outTransform If non-null, the out transform.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool GetGeoTransform(double* outTransform)const;


		/**********************************************************************//**
		 * @brief	获取逻辑图像的地理范围.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 * @return	逻辑图像的地理范围.
		 *************************************************************************/
		us_geo_rect get_geo_rect()const;
		/**********************************************************************//**
		 * @brief	获取实际关联的图像地理范围.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 * @return	实际关联图像的地理范围.
		 *************************************************************************/
		us_geo_rect get_geo_rect_from_associated()const;



		/**********************************************************************//**
		 * @brief	获取影像像素数据.
		 * 			读取影像的数据，默认是读取所有波段的数据，并按照不同波段交叉排列(RGBRGBRGB)。
		 * 			默认传出的像素数据类型就是关联的影像的像素数据类型。暂时未考虑2G以上影像数据
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/14
		 * @param	[out] pData	传出影像像素数据保存的buffer.
		 * @param	nBufSize	pData指向的缓存区大小(请确保其足够大).
		 * @param	nBandCount	要读取的波段数，为0时读取所有波段.
		 * @param	panBandMap	要读取的波段，nBandCount不为0时有效.
		 * @param	isLikeRGB	读取数据排列是否类似于RGBRGBRGB这种，如果传入false,则为
		 * 						RRRGGGBBB类型的方式.
		 * @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		 * 			|返回值|含义|
		 * 			|:---|:---|
		 * 			|-1|pData或影像无效|
		 * 			|-2|pData指向缓冲区太小|
		 * 			|-3|nBandCount无效|
		 * 			|-4|panBandMap无效(不是获取所有的波段时)|
		 * 			|-5|读取数据返回错误|
		 *			|-6|获取波段类型失败|
		 *************************************************************************/
		int64_t	get_image_buffer(void * pData, int64_t nBufSize, int nBandCount = 0,
								 int * panBandMap = NULL,bool isLikeRGB = true)const;

		/**********************************************************************//**
		 * @brief	获取影像像素数据.
		 * 			读取影像的数据，默认是读取所有波段的数据，并按照不同波段交叉排列(RGBRGBRGB)。
		 * 			默认传出的像素数据类型就是关联的影像的像素数据类型。暂时未考虑2G以上影像数据。
		 * 			<br>前四个参数决定取图的范围。第5、6个参数决定输出的取图的大小。最后一个参数
		 * 			表示是否基于关联图像来取图。当基于关联图像来取图的时候，left/top是相对于关联
		 *			图像进行设置的。当不基于关联图像取图时，left/top是相对于当前的取图范围原点的
		 *			偏移值。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/28
		 * @param	left		左上角横向坐标.
		 * @param	top			左上角纵向坐标.
		 * @param	width		设置取图范围宽.
		 * @param	height		设置取图范围高.
		 * @param	out_width	设置取图输出宽.
		 * @param	out_height	设置取图输出高.
		 * @param	[out] pData	传出影像像素数据保存的buffer.
		 * @param	nBufSize	pData指向的缓存区大小(请确保其足够大).
		 * @param	nBandCount	要读取的波段数，为0时读取所有波段.
		 * @param	panBandMap	要读取的波段，nBandCount不为0时有效.
		 * @param	isLikeRGB	读取数据排列是否类似于RGBRGBRGB这种，如果传入false,则为
		 * 						RRRGGGBBB类型的方式.
		 * @param	basedOnAssociation	是否基于关联的影像来取图.
		 * @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		 * 			|返回值|含义|
		 * 			|:---|:---|
		 * 			|-1|pData或影像无效|
		 * 			|-2|pData指向缓冲区太小|
		 * 			|-3|nBandCount无效|
		 * 			|-4|panBandMap无效(不是获取所有的波段时)|
		 * 			|-5|读取数据返回错误|
		 *			|-6|获取波段类型失败|
		 *************************************************************************/
		int64_t	get_image_buffer(int left, int top, int width, int height,
								 int out_width, int out_height,
								 void * pData, int64_t nBufSize,int nBandCount = 0,
								 int * panBandMap = NULL,bool isLikeRGB = true,
								 bool basedOnAssociation = true)const;


		/**********************************************************************//**
		 * @brief	获取有效性.
		 * 			1、Dataset是否有效 2、rect范围是否有效 3、size是否有负值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @return	true if valid, false if not.
		 *************************************************************************/
		bool is_valid()const;

		/**********************************************************************//**
		 * @brief	获取等比缩放后的逻辑影像.
		 *			不对缩放因子进行检查，如果参数不合理，也会进行设置。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	scalefactor 缩放因子.
		 * @return	由原对象缩放后的新的us_image对象.
		 *************************************************************************/
		us_image scale(double scalefactor)const;

		/**********************************************************************//**
		 * @brief	获取缩放后逻辑影像.
		 *			不对缩放因子进行检查，如果参数不合理，也会进行设置。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	xscale X方向缩放因子.
		 * @param	yscale Y方向缩放因子.
		 * @return	由原对象缩放后的新的us_image对象.
		 *************************************************************************/
		us_image scale(double xscale, double yscale)const;

		/**********************************************************************//**
		 * @brief	对逻辑影像对象自身进行缩放.
		 *			不对缩放因子进行检查，如果参数不合理，也会进行设置。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	scalefactor The scalefactor.
		 *************************************************************************/
		void set_scale(double scalefactor);

		/**********************************************************************//**
		 * @brief	对逻辑影像对象自身进行缩放.
		 *			不对缩放因子进行检查，如果参数不合理，也会进行设置。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	xscale X方向缩放因子.
		 * @param	yscale Y方向缩放因子.
		 *************************************************************************/
		void set_scale(double xscale, double yscale);

		/**********************************************************************//**
		 * @brief	对逻辑影像对象自身进行大小设置.（等同于缩放设置）
		 *			不对参数进行检查，如果参数不合理，也会进行设置。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/28
		 * @param	width	设置逻辑图形宽.
		 * @param	height	设置逻辑图形高.
		 *************************************************************************/
		void set_size(int width, int height);

		/**********************************************************************//**
		 * @brief	对逻辑影像对象自身的范围进行设置.
		 *			如果设置的范围在关联图像的范围内，则进行设置，否则不设置。<br>设置了范围后，
		 *			默认将对图像的输出大小进行同步缩放，所以<b>输出大小变为设置范围大小</b>。如果
		 *			最后一个参数设置为false，那么保持输出大小为设置前的范围大小。<br>例如：<br>
		 *			关联的图像大小是[512,512]，设置范围为[100,128,256,200]，那么这张影像的
		 *			输出大小变为[256,200]，如果在设置范围的时候不进行缩放，那么输出大小就是
		 *			[512,512].也就是说这个操作默认会重置缩放操作。<br>
		 *			<b>必须确保设置的范围在当前关联的影像范围内，否则设置无效！！！</b>
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	left	左上角横向坐标.
		 * @param	top		左上角纵向坐标.
		 * @param	width	设置取图范围宽.
		 * @param	height	设置取图范围高.
		 * @param	toscale	是否进行同步缩放.
		 * @return	范围合理返回 true,范围超出关联图像范围返回false.
		 *************************************************************************/
		bool set_rect(int left, int top, int width, int height, bool toscale = true);

		/**********************************************************************//**
		 * @brief	重置逻辑图像的相关参数.
		 *			使得逻辑图像的大小和关联图像一致，逻辑图像的取图范围和关联图像重合.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/27
		 *************************************************************************/
		void reset_image();

		/**********************************************************************//**
		 * @brief	保存为文件.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/5
		 * @param	filepath	目标存储路径.
		 * @param	fmt			模板影像格式.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		bool save_to_file(const us_ustring& filepath, IMAGE_FORMAT fmt,
						  int BandCount = 0,int* pBandMap = NULL)const;

		/**********************************************************************//**
		 * @brief	获取影像像素数据.
		 * 			读取影像的数据，只读取RGB波段(3,2,1)的数据，并根据取图范围，插入alpha波
		 *			段。按照不同波段交叉排列(RGBRGBRGB)。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/18
		 * @param	image		待读取的影像.
		 * @param	[out] pData	传出影像像素数据保存的buffer.
		 * @param	nBufSize	pData指向的缓存区大小(请确保其足够大).
		 * @param	isLikeRGB	读取数据排列是否类似于RGBRGBRGB这种，如果传入false,则为
		 * 						RRRGGGBBB类型的方式.
		 * @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		 * 			|返回值|含义|
		 * 			|:---|:---|
		 * 			|-1|pData或影像无效|
		 * 			|-2|pData指向缓冲区太小|
		 * 			|-3|nBandCount无效|
		 * 			|-4|panBandMap无效(不是获取所有的波段时)|
		 * 			|-5|读取数据返回错误|
		 *			|-6|获取波段类型失败|
		 *************************************************************************/
		_US_DATA_PROCESS_DLL friend int64_t get_image_rgb_embed_alpha_buffer(
			const us_image& image, void * pData, int64_t nBufSize,
			bool isLikeRGB = true,
			int rband = 3, int gband = 2, int bband = 1);

		/**********************************************************************//**
		 * @brief	获取影像像素数据.
		 * 			读取影像的数据，默认是读取RGB波段(3,2,1)的数据，并根据取图范围，插入alpha波
		 *			段。按照不同波段交叉排列(RGBRGBRGB)。无论原图的像素是用的什么数据类型，都统
		 *			一转换到RGBA32位图。
		 * 			默认传出的像素数据类型就是关联的影像的像素数据类型。暂时未考虑2G以上影像数据。
		 * 			<br>前四个参数决定取图的范围。第5、6个参数决定输出的取图的大小。最后一个参数
		 * 			表示是否基于关联图像来取图。当基于关联图像来取图的时候，left/top是相对于关联
		 *			图像进行设置的。当不基于关联图像取图时，left/top是相对于当前的取图范围原点的
		 *			偏移值。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/18
		 * @param	image		待读取的影像.
		 * @param	left		左上角横向坐标.
		 * @param	top			左上角纵向坐标.
		 * @param	width		设置取图范围宽.
		 * @param	height		设置取图范围高.
		 * @param	out_width	设置取图输出宽.
		 * @param	out_height	设置取图输出高.
		 * @param	[out] pData	传出影像像素数据保存的buffer.
		 * @param	nBufSize	pData指向的缓存区大小(请确保其足够大).
		 * @param	isLikeRGB	读取数据排列是否类似于RGBRGBRGB这种，如果传入false,则为
		 * 						RRRGGGBBB类型的方式.
		 * @param	basedOnAssociation	是否基于关联的影像来取图.
		 * @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		 * 			|返回值|含义|
		 * 			|:---|:---|
		 * 			|-1|pData或影像无效|
		 * 			|-2|pData指向缓冲区太小|
		 * 			|-3|nBandCount无效|
		 * 			|-4|panBandMap无效(不是获取所有的波段时)|
		 * 			|-5|读取数据返回错误|
		 *			|-6|获取波段类型失败|
		 *************************************************************************/
		_US_DATA_PROCESS_DLL friend int64_t get_image_rgb_embed_alpha_buffer(
			const us_image& image,
			int left, int top, int width, int height,
			int out_width, int out_height,
			void * pData, int64_t nBufSize,
			bool isLikeRGB = true,
			bool basedOnAssociation = true,
			int rband = 3,int gband = 2,int bband = 1);

	private:
		/** 不是Dataset中高宽. */
		us_size<int> m_size;

		/** 在Dataset中的有效范围 */
		us_rect<int> m_rect;

		std::shared_ptr<int> pdset;
	};

	/**********************************************************************//**
		* @brief	获取影像像素数据.
		* 			读取uv参数所指定的部分区域的影像，并经过透视变换到一个矩形。只读取
		*			RGB波段，并添加alpha波段。
		* @author	yimin.liu@unispace-x.com
		* @date	2016/10/18
		* @param	image		待读取的影像.
		* @param	uv			读图的范围信息.
		* @param	out_width	设置取图输出宽.
		* @param	out_height	设置取图输出高.
		* @param	[out] pData	传出影像像素数据保存的buffer.
		* @param	nBufSize	pData指向的缓存区大小(请确保其足够大).
		* @param	basedOnAssociation	是否基于关联的影像来取图.
		* @return	读取成功返回保存到缓冲区的数据量(字节数),失败返回一个负数.
		* 			|返回值|含义|
		* 			|:---|:---|
		* 			|-1|pData或影像无效|
		* 			|-2|pData指向缓冲区太小|
		* 			|-3|nBandCount无效|
		* 			|-4|panBandMap无效(不是获取所有的波段时)|
		* 			|-5|读取数据返回错误|
		*			|-6|获取波段类型失败|
		*************************************************************************/
	_US_DATA_PROCESS_DLL int64_t get_image_perspective_transform_buffer(
		const us_image& image,
		const us_basic_uv& uv,
		int out_width, int out_height,
		void * pData, int64_t nBufSize,
		bool basedOnAssociation = true);
}


#endif //!__US_IMAGE_HPP__
