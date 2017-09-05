#ifndef __US_CONFIG_VALUE_HPP__
#define __US_CONFIG_VALUE_HPP__

#include <stdint.h>

#ifndef __US_STRING_HPP__
#include "../common/us_string.hpp"
#endif
#ifndef __US_UUID_HPP__
#include "../uuid/us_uuid.hpp"
#endif

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_config_value
	 * @brief	配置值类.<br>
	 * 			内部仅保存us_ustring的值，可通过get<type>方法获取指定类型的值.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/9/22
	 *************************************************************************/
	class us_config_value
	{
		us_ustring value;
	public:
		us_config_value(){}
		us_config_value(const us_config_value& other)
			:value(other.value)
		{}
		us_config_value(us_config_value&& other)
		{
			value.swap(other.value);
		}

		template<typename T = const us_ustring&>
		us_config_value(T val)
		{
			set<T>(val);
		}
		/**********************************************************************//**
		 * @brief	获取指定类型的值.
		 *			当前支持各种数值和uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/22
		 * @return	指定类型的值，默认是us_ustring类型.
		 *************************************************************************/
		template<typename T=us_ustring>
		const T get(bool* ok = nullptr)const;

		/**********************************************************************//**
		 * @brief	设置为指定类型的值.
		 *			当前支持各种数值和uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/22
		 * @return	设置后的值，默认是us_ustring类型.
		 *************************************************************************/
		template<typename T=us_ustring>
		const us_config_value& set(const T val);

		// 重载赋值运算符
		template<typename T=us_ustring>
		const us_config_value& operator=(const T val)
		{
			return set<T>(val);
		}
		const us_config_value& operator=(const us_config_value& val)
		{
			value = val.value;
			return *this;
		}
	};



	template<>
	inline const bool us_config_value::get<bool>(bool* ok)const
	{
		return value.to_bool(ok);
	}
	template<>
	inline const int us_config_value::get<int>(bool* ok)const
	{
		return value.to_int32(10,ok);
	}
	template<>
	inline const float us_config_value::get<float>(bool* ok)const
	{
		return value.to_float(ok);
	}
	template<>
	inline const double us_config_value::get<double>(bool* ok)const
	{
		return value.to_double(ok);
	}
	template<>
	inline const std::string us_config_value::get<std::string>(bool* ok)const
	{
		if (ok != nullptr){ *ok = true; }
		return value;
	}

	template<>
	inline const us_ustring us_config_value::get<us_ustring>(bool* ok)const
	{
		if (ok != nullptr){ *ok = true; }
		return value;
	}
	template<>
	inline const us_uuid us_config_value::get<us_uuid>(bool* ok)const
	{
		us_uuid u; bool oks;
		ok = (ok == nullptr) ? &oks : ok;
		if (us_uuid::uuid_from_string(value, &u)){
			*ok = true;
		}
		else{
			*ok = false;
		}
		return u;
	}

	template<typename T>
	inline const us_config_value & us_config_value::set(const T val)
	{
		value = val;
		return *this;
	}
	template<>
	inline const us_config_value& us_config_value::set<us_config_value>(const us_config_value val)
	{
		value = val.value;
		return *this;
	}
	template<>
	inline const us_config_value& us_config_value::set<bool>(const bool val)
	{
		value.resize(1);
		value[0] = val ? '1' : '0';
		return *this;
	}

	template<>
	inline const us_config_value& us_config_value::set<int>(const int val)
	{
		value.set_num(val);
		return *this;
	}
	template<>
	inline const us_config_value& us_config_value::set<float>(const float val)
	{
		value.set_num(val);
		return *this;
	}
	template<>
	inline const us_config_value& us_config_value::set<double>(const double val)
	{
		value.set_num(val);
		return *this;
	}
	template<>
	inline const us_config_value& us_config_value::set<us_ustring>(const us_ustring val)
	{
		value = val;
		return *this;
	}

	template<>
	inline const us_config_value& us_config_value::set<us_uuid>(const us_uuid val)
	{
		value = val.to_string();
		return *this;
	}
}

#endif //!__US_CONFIG_VALUE_HPP__