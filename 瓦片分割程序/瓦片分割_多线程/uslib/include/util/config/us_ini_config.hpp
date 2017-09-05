#ifndef __US_INI_CONFIG_HPP__
#define __US_INI_CONFIG_HPP__

#ifndef __US_KEY_VALUE_CONFIG_HPP__
#include "us_key_value_config.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_ini_config
	 * @brief	INI配置信息类.<br>
	 * 			用于读取类似于INI文件格式的信息，也分为[section]和[key-value]结构.
	 *			同时支持';'和'#'开头文本作为注释.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/9/23
	 *************************************************************************/
	class _US_UTIL_DLL us_ini_config
	{
		std::map<us_ustring, us_key_value_config> m_ini;
	public:
		/**********************************************************************//**
		 * @brief	从文件读取键值对配置.
		 *			当前只支持utf-8不带bom格式的文本.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	filename		INI文件路径.
		 * @param	[out] outconf	传出读取到的配置信息.
		 * @return	成功返回true,失败返回false.
		 *************************************************************************/
		static bool from_file(const us_ustring& filename,
			us_ini_config* outconf);

		/**********************************************************************//**
		 * @brief	保存键值对配置到文件.
		 *			当前只支持保存为UTF-8不带bom标识的文本文件.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	filename	文件的路径.
		 * @param	noreplace	不覆盖文件，打开文件时如果文件存在就返回false.
		 * @return	成功返回true,失败返回false.
		 *************************************************************************/
		bool save_to_file(const us_ustring& filename,bool noreplace = false)const;

		/**********************************************************************//**
		 * @brief	构造一个空的键值对配置.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		us_ini_config();

		/**********************************************************************//**
		 * @brief	拷贝构造.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		us_ini_config(const us_ini_config& iniconf);
		us_ini_config(us_ini_config&& iniconf);
		
		/**********************************************************************//**
		 * @brief	从字符串读取键值对配置构造.
		 *			与从文件读取类似,以INI文件格式解析inistr中的配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	inistr		保存ini信息的字符串.
		 * @return	转换得到的bool值.
		 *************************************************************************/
		us_ini_config(const us_ustring& inistr);

	public:
		/**********************************************************************//**
		 * @brief	查询配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	section		配置项所在的段.
		 * @param	key			配置项的键.
		 * @param	defaultval	没有找到时候的默认值.
		 * @return	查询到的配置项的值.
		 *************************************************************************/
		const us_config_value& get(const us_ustring& section,
			const us_ustring& key,
			const us_config_value& defaultval = us_ustring("Not Found"))const;
		
		/**********************************************************************//**
		 * @brief	查询一个配置段.
		 *			每一个配置段实际上都是一个键值对配置组.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	section			配置段名称.
		 * @param	default_section	没有找到时候的默认值.
		 * @return	查询到的配置段.
		 *************************************************************************/
		const us_key_value_config& get(const us_ustring& section,
			const us_key_value_config& default_section = us_key_value_config())const;
		
		/**********************************************************************//**
		 * @brief	设置一个配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	section		配置项所在的段.
		 * @param	key			配置项的键.
		 * @param	value		配置项的值.
		 *************************************************************************/
		void set(const us_ustring& section,
			const us_ustring& key,
			const us_config_value& value);

		/**********************************************************************//**
		 * @brief	从完整的INI配置字符串设置配置项.
		 *			与从文件读取类似,以INI文件格式解析inistr中的配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	inistr		保存ini信息的字符串.
		 *************************************************************************/
		void set(const us_ustring& inistr);

		/**********************************************************************//**
		 * @brief	删除一个配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	section		配置项所在的段.
		 * @param	key			配置项的键.
		 * @return	找到并删除返回true,没有找到返回false.
		 *************************************************************************/
		bool remove(const us_ustring& section, const us_ustring& key);

		/**********************************************************************//**
		 * @brief	删除一个配置段.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	section		配置项所在的段.
		 * @return	找到并删除返回true,没有找到返回false.
		 *************************************************************************/
		bool remove(const us_ustring& section);

		/**********************************************************************//**
		 * @brief	清空所有配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		void clear();

		/**********************************************************************//**
		 * @brief	交换配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/20
		 *************************************************************************/
		void swap(us_ini_config& iniconf);
		void swap(us_ini_config&& iniconf);
	};

}
#endif