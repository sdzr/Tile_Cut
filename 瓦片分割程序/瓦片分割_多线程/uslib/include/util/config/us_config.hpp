#ifndef __US_CONFIG_HPP__
#define __US_CONFIG_HPP__

#ifndef __US_CONFIG_VALUE_HPP__
#include "us_config_value.hpp"
#endif

#ifndef __US_KEY_VALUE_CONFIG_HPP__
#include "us_key_value_config.hpp"
#endif

#ifndef __US_INI_CONFIG_HPP__
#include "us_ini_config.hpp"
#endif // !__US_INI_CONFIG_HPP__


namespace unispace
{
	/**********************************************************************//**
	* @brief	读取配置文件目录路径.
	*			默认所有库的配置路径都在一个统一的目录下。其它部分(如data_storage)模块的
	*			配置文件都从这个目录下获取。这里提供一个统一的接口来获取这个目录的路径。<br>
	*			获取到的路径结尾是带有'/'符号的，所以无需添加。<br>
	*			获取路径的方式为从'us_lib.conf'文件中读取，查找这个文件的顺序可以见us_lib_share
	*			目录下的'说明.txt'文件。
	* @author	yimin.liu@unispace-x.com
	* @date	2016/9/22
	* @return	设置后的值，默认是us_ustring类型.
	*************************************************************************/
	_US_UTIL_DLL bool us_read_share_root_path(us_ustring* out_path);
}

#endif // !__US_CONFIG_HPP__