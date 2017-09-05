#ifndef __US_SPATIAL_REFERENCE_HPP__
#define __US_SPATIAL_REFERENCE_HPP__

#ifndef __US_VEC2_HPP__
#include "util/math/us_vec2.hpp"
#endif
#ifndef __US_VEC3_HPP__
#include "util/math/us_vec3.hpp"
#endif

#ifndef __US_GEO_COORD_TRANSFORM_HPP__
#include "us_geo_coord_transform.hpp"
#endif

//typedef void* projPJ;

namespace unispace
{

	/**********************************************************************//**
	 * @brief	地理空间参考类.
	 *			可以是一个单独的地理坐标系(latlong)<br>
	 *			也可以是一个投影坐标系，投影坐标系是基于地理坐标系的.<br>
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/30
	 *************************************************************************/
	class _US_GEO_COORD_TRANSFORM_DLL us_spatial_reference
	{
		void*	proj;
	public:
		us_spatial_reference();
		us_spatial_reference(const char * definition);
		us_spatial_reference(const us_spatial_reference& other);
		us_spatial_reference(us_spatial_reference&& other);

		~us_spatial_reference();

		bool reset_by_proj_str(const char* definition);

		/**********************************************************************//**
		 * @brief	经纬度(地理坐标)转换投影坐标(将废弃).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @param	lnglat	待转换的点经纬度坐标.
		 * @return	返回转换后的结果点坐标,如果操作失败，返回结果的值分量为HUGE_VAL.
		 *************************************************************************/
		Point2lf fwd(Point2lf lnglat)const;
		/**********************************************************************//**
		 * @brief	经纬度(地理坐标)转换投影坐标(将废弃).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @param	lng	待转换的点经度坐标.
		 * @param	lat	待转换的点维度坐标
		 * @return	返回转换后的结果点坐标,如果操作失败，返回结果的值分量为HUGE_VAL.
		 *************************************************************************/
		Point2lf fwd(double lng /*经度*/, double lat /*维度*/)const;


		/**********************************************************************//**
		 * @brief	投影坐标转地理坐标(将废弃).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @param	xy	待转换的点坐标.
		 * @return	返回转换后的结果点坐标,如果操作失败，返回结果的值分量为HUGE_VAL.
		 *************************************************************************/
		Point2lf inv(Point2lf xy)const;
		/**********************************************************************//**
		 * @brief	投影坐标转地理坐标(将废弃).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @param	x	待转换的点X坐标.
		 * @param	y	待转换的点Y坐标
		 * @return	返回转换后的结果点坐标,如果操作失败，返回结果的值分量为HUGE_VAL.
		 *************************************************************************/
		Point2lf inv(double x, double y)const;

		/**********************************************************************//**
		 * @brief	空间参考是否是地理坐标(经纬)系统.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @return	返回true表示是一个地理坐标系.
		 *************************************************************************/
		bool is_latlng()const;

		/**********************************************************************//**
		 * @brief	空间参考是否是地心坐标系统.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @return	返回true表示是一个地心坐标系.
		 *************************************************************************/
		bool is_geocent()const;

		/**********************************************************************//**
		 * @brief	获取proj4字符串定义的坐标系.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/00
		 * @return	返回proj4字符串.
		 *************************************************************************/
		std::string get_proj_define()const;

		/**********************************************************************//**
		 * @brief	获取Spr是否是一个有效的坐标系.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/00
		 * @return	有效返回true.
		 *************************************************************************/
		bool is_valid()const;

		/**********************************************************************//**
		 * @brief	地心坐标转地理坐标(严密转换).
		 *			即空间直角坐标系(XYZ)转空间大地坐标系(BLH)。传出单位为度。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	a		椭球体长半轴.
		 * @param	es		椭球体扁率.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入地心空间直角坐标的x，传出地理大地坐标的经度.
		 * @param	[in,out]	y	传入地心空间直角坐标的y，传出地理大地坐标的纬度.
		 * @param	[in,out]	z	传入地心空间直角坐标的z，传出地理大地坐标的高程(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int geocentric_to_geodetic(double a/*长半轴*/, double es/*扁率*/,
										  long point_count/*点数*/, int point_offset/*点偏移*/,
										  double *x/*传入x传出α*/, double *y/*传入y传出β*/,
										  double *z =NULL/*传入z传出H*/);

		/**********************************************************************//**
		 * @brief	地心坐标转地理坐标(严密转换).
		 *			即空间直角坐标系(XYZ)转空间大地坐标系(BLH)。传出单位为弧度
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	a		椭球体长半轴.
		 * @param	es		椭球体扁率.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入地心空间直角坐标的x，传出地理大地坐标的经度.
		 * @param	[in,out]	y	传入地心空间直角坐标的y，传出地理大地坐标的纬度.
		 * @param	[in,out]	z	传入地心空间直角坐标的z，传出地理大地坐标的高程(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int geocentric_to_geodetic_rad(double a/*长半轴*/, double es/*扁率*/,
										  long point_count/*点数*/, int point_offset/*点偏移*/,
										  double *x/*传入x传出α*/, double *y/*传入y传出β*/,
										  double *z =NULL/*传入z传出H*/);

		/**********************************************************************//**
		 * @brief	地理坐标转地心坐标(严密转换).
		 *			即空间大地坐标系(BLH)转空间直角坐标系(XYZ)。传入参数单位为度。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	a		椭球体长半轴.
		 * @param	es		椭球体扁率.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入地理大地坐标的经度，传出地心空间直角坐标的x.
		 * @param	[in,out]	y	传入地理大地坐标的纬度，传出地心空间直角坐标的y.
		 * @param	[in,out]	z	传入地理大地坐标的高程，传出地心空间直角坐标的z(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int geodetic_to_geocentric(double a, double es,
										  long point_count, int point_offset,
										  double *x, double *y, double *z=NULL);

		/**********************************************************************//**
		 * @brief	地理坐标转地心坐标(严密转换).
		 *			即空间大地坐标系(BLH)转空间直角坐标系(XYZ)。传入参数单位为弧度。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	a		椭球体长半轴.
		 * @param	es		椭球体扁率.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入地理大地坐标的经度，传出地心空间直角坐标的x.
		 * @param	[in,out]	y	传入地理大地坐标的纬度，传出地心空间直角坐标的y.
		 * @param	[in,out]	z	传入地理大地坐标的高程，传出地心空间直角坐标的z(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int geodetic_to_geocentric_rad(double a, double es,
										  long point_count, int point_offset,
										  double *x, double *y, double *z=NULL);

		/**********************************************************************//**
		 * @brief	不同空间参考下坐标转换.
		 *			变换传入点从源坐标系统到目标坐标系统。<br><b>注意:</b>
		 *			传入的地理位置需要度为单位。并且返回的也是度单位。如果没有Z值，
		 *			可以传入NULL做参数。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	src		源坐标系统.
		 * @param	dst		目标坐标系统.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的经度或x).
		 * @param	[in,out]	y	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的纬度或y).
		 * @param	[in,out]	z	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的高程或z)(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *			如果所有转换都失败，那么返回错误代码。如果个别点失败(例如地平线上的点)，转换
		 *			结果将被设置为HUGE_VAL。如果传入的数据是HUGE_VAL，将不做转换。
		 *************************************************************************/
		static int transform(const us_spatial_reference& src,
							 const us_spatial_reference& dst,
							 size_t point_count, int point_offset,
							 double *x, double *y, double *z);

		/**********************************************************************//**
		 * @brief	不同空间参考下坐标转换.
		 *			变换传入点从源坐标系统到目标坐标系统。<br><b>注意:</b>
		 *			传入的地理位置需要度为单位。并且返回的也是度单位。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/28
		 * @param	src		源坐标系统.
		 * @param	dst		目标坐标系统.
		 * @param	point_array		待转换的点.
		 * @param	point_count		待转换的点数.
		 * @return	成功返回0，失败返回错误代码.
		 *			如果所有转换都失败，那么返回错误代码。如果个别点失败(例如地平线上的点)，转换
		 *			结果将被设置为HUGE_VAL。如果传入的数据是HUGE_VAL，将不做转换。
		 *************************************************************************/
		static int transform(const us_spatial_reference& src,
							 const us_spatial_reference& dst,
							 Point2lf* point_array , size_t point_count);

		/**********************************************************************//**
		 * @brief	不同空间参考下坐标转换.
		 *			变换传入点从源坐标系统到模板坐标系统。<br><b>注意:</b>
		 *			传入的地理位置需要以弧度为单位，而不是度。并且返回的也是弧度单位。如果没有Z值，
		 *			可以传入NULL做参数。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	src		源坐标系统.
		 * @param	dst		目标坐标系统.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	x	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的经度或x).
		 * @param	[in,out]	y	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的纬度或y).
		 * @param	[in,out]	z	传入源坐标系下坐标，传出目标坐标系下坐标(地理大地坐标的高程或z)(可选).
		 * @return	成功返回0，失败返回错误代码.
		 *			如果所有转换都失败，那么返回错误代码。如果个别点失败(例如地平线上的点)，转换
		 *			结果将被设置为HUGE_VAL。如果传入的数据是HUGE_VAL，将不做转换。
		 *************************************************************************/
		static int transform_rad(const us_spatial_reference& src,
								 const us_spatial_reference& dst,
								 long point_count, int point_offset,
								 double *x, double *y, double *z);

		/**********************************************************************//**
		 * @brief	不同空间参考下坐标转换.
		 *			变换传入点从源坐标系统到模板坐标系统。<br><b>注意:</b>
		 *			传入的地理位置需要以弧度为单位，而不是度。并且返回的也是弧度单位。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/28
		 * @param	src		源坐标系统.
		 * @param	dst		目标坐标系统.
		 * @param	point_array		待转换的点.
		 * @param	point_count		待转换的点数.
		 * @return	成功返回0，失败返回错误代码.
		 *			如果所有转换都失败，那么返回错误代码。如果个别点失败(例如地平线上的点)，转换
		 *			结果将被设置为HUGE_VAL。如果传入的数据是HUGE_VAL，将不做转换。
		 *************************************************************************/
		static int transform_rad(const us_spatial_reference& src,
								 const us_spatial_reference& dst,
								 Point2lf* point_array, size_t point_count);

		/**********************************************************************//**
		 * @brief	不同基准面坐标转换.
		 *			两个不同基准面的地理坐标之间的转换。要求src和dst两个空间参考对象都必须含有
		 *			基准面转换参数(+towgs84)，可以是三参数或者七参数，例如:<br>
		 *			三参数(dx,dy,dz):+towgs84=-199.87,74.79,246.62<br>
		 *			七参数(dx,dy,dz,rx,ry,rz,dscale):+towgs=0,0,4.5,0,0,0.554,0.219<br>
		 *			平移参数单位为米，选择参数单位为角秒(非弧度)。
		 *			比例校正因子dscale的单位为ppm(百万分之一)，缩放值实际为 1+ dscale/1000000.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	src		源基准面空间参考.
		 * @param	dst		目标基准面空间参考.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	lng	传入传出地理大地坐标的经度(角度值).
		 * @param	[in,out]	lat	传入传出地理大地坐标的纬度(角度值).
		 * @param	[in,out]	hgt	传入传出地理大地坐标的高程.
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int datum_transform(const us_spatial_reference& src,
								   const us_spatial_reference& dst,
								   long point_count, int point_offset,
								   double *lng, double *lat, double *hgt);

		/**********************************************************************//**
		 * @brief	不同基准面坐标转换.
		 *			两个不同基准面的地理坐标之间的转换。要求src和dst两个空间参考对象都必须含有
		 *			基准面转换参数(+towgs84)，可以是三参数或者七参数，例如:<br>
		 *			三参数(dx,dy,dz):+towgs84=-199.87,74.79,246.62<br>
		 *			七参数(dx,dy,dz,rx,ry,rz,dscale):+towgs=0,0,4.5,0,0,0.554,0.219<br>
		 *			比例校正因子dscale的单位为ppm(百万分之一)，缩放值实际为 1+ dscale/1000000.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/26
		 * @param	src		源基准面空间参考.
		 * @param	dst		目标基准面空间参考.
		 * @param	point_count		要转换的点数.
		 * @param	point_offset	传入点数组中两个相邻点的对应坐标在数组位置的偏移数.
		 * 							例如:传入数组为[x1,y1,x2,y2...]则为2
		 * 							传入数组为[x1,x2,x3...]则为1.
		 * @param	[in,out]	lng	传入传出地理大地坐标的经度(弧度值).
		 * @param	[in,out]	lat	传入传出地理大地坐标的纬度(弧度值).
		 * @param	[in,out]	hgt	传入传出地理大地坐标的高程.
		 * @return	成功返回0，失败返回错误代码.
		 *************************************************************************/
		static int datum_transform_rad(const us_spatial_reference& src,
								   const us_spatial_reference& dst,
								   long point_count, int point_offset,
								   double *lng, double *lat, double *hgt);

		/**********************************************************************//**
		 * @brief	获取错误代码字符串.
		 *			错误代码大于0，实际上会是系统相关错误，直接返回的strerror结果.小于0时才会
		 *			返回proj.4内部定义的错误描述字符串。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/30
		 * @param	errcode	错误代码.
		 * @return	成功返回字符串地址.
		 *************************************************************************/
		static const char* get_error_str(int errcode);

	};

}

#endif //!__US_SPATIAL_REFERENCE_HPP__