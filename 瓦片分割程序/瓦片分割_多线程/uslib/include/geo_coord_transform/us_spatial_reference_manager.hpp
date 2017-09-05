#ifndef __US_SPATIAL_REFERENCE_ACCESS_HPP__
#define __US_SPATIAL_REFERENCE_ACCESS_HPP__

#ifndef __US_SPATIAL_RECORD_HPP__
#include "us_spatial_record.hpp"
#endif // !__US_SPATIAL_RECORD_HPP__

#ifndef __US_INI_CONFIG_HPP__
#include "util/config/us_ini_config.hpp"
#endif // !__US_INI_CONFIG_HPP__

#ifndef __US_GEO_COORD_TRANSFORM_HPP__
#include "us_geo_coord_transform.hpp"
#endif

#include <map>
#include <vector>

/*
* config 文件形式如下
* [proj]
* ; 下面可以填写相对路径或者绝对路径
* predef = /usr/local/proj/epsg
* userdef  = /usr/local/proj/userdef
*/

namespace unispace
{
	class _US_GEO_COORD_TRANSFORM_DLL us_spatial_reference_manager
	{
		us_spatial_reference_manager();
		~us_spatial_reference_manager();
	public:
		// 打开一个空间参考管理器
		static us_spatial_reference_manager* open_manager();
		// 关闭空间参考管理器
		static void close_manager(us_spatial_reference_manager* mgr);

		/**********************************************************************//**
		 * @brief	重新加载配置文件的数据记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/21
		 * @return	成功true，失败false.
		 *************************************************************************/
		bool reload_config();

		/**********************************************************************//**
		 * @brief	查找记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @param	id	空间参考的ID.
		 * @param	out	传出空间参考记录.
		 * @return	找到返回true，没找到或者out==null返回false.
		 *************************************************************************/
		bool get_spr_record(const us_uuid& id, us_spatial_record* out)const;
		
		/**********************************************************************//**
		 * @brief	判断记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @param	id	空间参考的ID.
		 * @return	记录存在返回true.
		 *************************************************************************/
		bool has_record(const us_uuid& id)const;

		/**********************************************************************//**
		 * @brief	添加一个自定义的空间参考记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @param	rd	空间参考记录.
		 * @return	添加成功返回0，失败<0.
		 *************************************************************************/
		int add_user_define_spr_record(const us_spatial_record& rd);

		/**********************************************************************//**
		 * @brief	获取所有用户定义的空间参考记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @return	所有用户定义的空间参考记录.
		 *************************************************************************/
		std::vector<us_spatial_record> get_all_user_define_record()const;

		/**********************************************************************//**
		 * @brief	获取所有预定义的空间参考记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @return	所有预定义的空间参考记录.
		 *************************************************************************/
		std::vector<us_spatial_record> get_all_predefine_record()const;

		/**********************************************************************//**
		 * @brief	获取所有空间参考记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/16
		 * @return	所有空间参考记录.
		 *************************************************************************/
		std::vector<us_spatial_record> get_all_record()const;
		

		/**********************************************************************//**
		 * @brief	引用用户定义的空间参考记录map.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/28
		 * @return	用户空间参考记录map.
		 *************************************************************************/
		inline const std::map<us_uuid, us_spatial_record>& ref_user_define_record()const
		{
			return m_userdef_spr;
		}
		/**********************************************************************//**
		 * @brief	引用预定义的空间参考记录map.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/28
		 * @return	预空间参考记录map.
		 *************************************************************************/
		inline const std::map<us_uuid, us_spatial_record>& ref_predefine_record()const
		{
			return m_predef_spr;
		}

		/**********************************************************************//**
		 * @brief	获取用户定义空间参考记录数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/17
		 * @return	用户定义空间参考记录数.
		 *************************************************************************/
		size_t get_user_define_spr_count()const;
		/**********************************************************************//**
		 * @brief	获取预定义空间参考记录数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/17
		 * @return	预定义空间参考记录数.
		 *************************************************************************/
		size_t get_predefine_spr_count()const;
		/**********************************************************************//**
		 * @brief	获取所有空间参考记录数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/17
		 * @return	所有空间参考记录数.
		 *************************************************************************/
		size_t get_all_define_spr_count()const;

		us_spatial_reference get_spatial_reference(const us_uuid& id)const;
	private:
		// 成功返回读取到的记录数，失败返回负数
		static int load_spr_record(const us_ustring& filename,
			std::map<us_uuid, us_spatial_record>& srm,bool userdef = true);


	private:
		us_ini_config	m_config;	///< 配置信息
		std::map<us_uuid,us_spatial_record> m_predef_spr;	///< 预定义的空间参考
		std::map<us_uuid,us_spatial_record> m_userdef_spr;	///< 用户定义空间参考

		static us_spatial_reference_manager* s_instance_ptr;	///< 单例对象指针
	};

}

#endif // !__US_SPATIAL_REFERENCE_ACCESS_HPP__
