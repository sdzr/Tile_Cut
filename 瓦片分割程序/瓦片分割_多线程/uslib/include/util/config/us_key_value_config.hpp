#ifndef __US_KEY_VALUE_CONFIG_HPP__
#define __US_KEY_VALUE_CONFIG_HPP__


#ifndef __US_CONFIG_VALUE_HPP__
#include "us_config_value.hpp"
#endif

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#include <map>
#include <vector>

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_key_value_config
	 * @brief	键值对配置信息类.<br>
	 * 			简单的键值对配置信息类,支持';'和'#'开头文本作为注释.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/9/23
	 *************************************************************************/
	class _US_UTIL_DLL us_key_value_config
	{
		std::map<us_ustring, us_config_value> m_kvs;	///< 保存键值对信息
	public:
		/**********************************************************************//**
		 * @brief	从文件读取键值对配置.
		 *			当前只支持utf-8不带bom格式的文本.文件中保存的键值对以行为单位
		 *			读取，键值对为'key = value'形式。键值对首尾空白将自动过滤掉。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	filename		INI文件路径.
		 * @param	[out] outconf	传出读取到的配置信息.
		 * @return	成功返回true,失败返回false.
		 *************************************************************************/
		static bool from_file(const us_ustring& filename, 
			us_key_value_config* outconf);

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
		 * @brief	获取配置信息字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @return	返回键值对配置的字符串形式.
		 *************************************************************************/
		us_ustring to_string()const;


		/**********************************************************************//**
		 * @brief	构造一个空的键值对配置.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		us_key_value_config();
		/**********************************************************************//**
		 * @brief	拷贝构造.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		us_key_value_config(const us_key_value_config& kvconf);
		us_key_value_config(us_key_value_config&& kvconf);
		/**********************************************************************//**
		 * @brief	从字符串读取键值对配置构造.
		 *			从kvstr字符串中解析出键值对信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	kvstr		保存键值对信息的字符串.
		 *************************************************************************/
		us_key_value_config(const us_ustring& kvstr);
	public:
		/**********************************************************************//**
		 * @brief	查询配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	key			配置项的键.
		 * @param	defaultval	没有找到时候的默认值.
		 * @return	查询到的配置项的值.
		 *************************************************************************/
		const us_config_value& get(const us_ustring& key,
			const us_config_value& defaultval = us_ustring("Not Found"))const;
		/**********************************************************************//**
		 * @brief	获取所有的键.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/26
		 * @return	查询到的键.
		 *************************************************************************/
		std::vector<us_ustring> get_all_keys()const;

		/**********************************************************************//**
		 * @brief	设置一个配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	key			配置项的键.
		 * @param	value		配置项的值.
		 *************************************************************************/
		void set(const us_ustring& key,const us_config_value& value);
		/**********************************************************************//**
		 * @brief	从完整的INI配置字符串设置配置项.
		 *			与从文件读取类似,以INI文件格式解析inistr中的配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	kvstr		保存键值对信息的字符串.
		 *************************************************************************/
		void set(const us_ustring& kvstr);
		/**********************************************************************//**
		 * @brief	删除一个配置项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	key			配置项的键.
		 * @return	找到并删除返回true,没有找到返回false.
		 *************************************************************************/
		bool remove(const us_ustring& key);
		/**********************************************************************//**
		 * @brief	清空所有配置信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 *************************************************************************/
		void clear();
	};

}
#endif //!__US_KEY_VALUE_CONFIG_HPP__