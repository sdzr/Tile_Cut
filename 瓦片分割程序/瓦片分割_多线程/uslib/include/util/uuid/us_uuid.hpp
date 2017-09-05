/**********************************************************************//**
 * @file uuid\us_uuid.hpp
 *
 * Declares the uuid class.
 *************************************************************************/

#ifndef __US_UUID_HPP__
#define __US_UUID_HPP__


#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#include <string>
#include <stdint.h>

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_uuid
	 * @brief	UUID 通用唯一识别码 (Universally Unique Identifier).
	 * 			
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/10
	 *************************************************************************/
	class _US_UTIL_DLL us_uuid
	{
		friend class us_uuid_factory;
	public:

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 *************************************************************************/

		us_uuid();

		/**********************************************************************//**
		 * @brief	构造函数，从字符串构造.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	[in,out] uuidstr The uuidstr.
		 *************************************************************************/

		us_uuid(const std::string& uuidstr);

		/**********************************************************************//**
		 * @brief	用二进制数据构造uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/20
		 * @param	data	uuid数据首地址.
		 *************************************************************************/
		us_uuid(const unsigned char data[16]);


		/**********************************************************************//**
		 * @brief	重载 = 运算符，进行赋值操作.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/23
		 * @param	other The other.
		 * @return	A shallow copy of this object.
		 *************************************************************************/

		us_uuid& operator =(const us_uuid& other);

		/**********************************************************************//**
		 * @brief	重载 == 运算符，判断两个uuid是否相同.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/23
		 * @param	uuid The uuid.
		 * @return	true if the parameters are considered equivalent.
		 *************************************************************************/
		bool operator ==(const us_uuid& uuid)const;

		/**********************************************************************//**
		 * @brief	重载 != 运算符，判断两个uuid是否不同.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/23
		 * @param	uuid The uuid.
		 * @return	true if the parameters are not considered equivalent.
		 *************************************************************************/
		bool operator != (const us_uuid& uuid)const;

		bool operator< (const us_uuid& rhs) const;

		inline bool operator>(const us_uuid& rhs) const
		{
			return rhs < *this;
		}
		inline bool operator<=(const us_uuid& rhs) const
		{
			return !(rhs < *this);
		}

		inline bool operator>=(const us_uuid& rhs) const
		{
			return !(*this < rhs);
		}


		/**********************************************************************//**
		 * @brief	转换为字符串形式.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	This object as a std::string.
		 *************************************************************************/
		std::string to_string()const;
		std::string to_brief_string()const;

		/**********************************************************************//**
		 * @brief	获取16字节二进制数据.
		 * @brief	获取保存UUID值的16字节二进制数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @return	uuid数据首地址.
		 *************************************************************************/
		const unsigned char* get_raw_data()const;

		/**********************************************************************//**
		 * @brief	获取16字节二进制数据.
		 * @brief	获取保存UUID值的16字节二进制数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/11
		 * @param	out 用于保存uuid数据的内存首地址.
		 *************************************************************************/
		void get_raw_data(unsigned char* out)const;

		/**********************************************************************//**
		 * @brief	用二进制数据设置uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	data	uuid数据首地址.
		 *************************************************************************/
		us_uuid& set_raw_data(const unsigned char data[16]);

	public:
		/**********************************************************************//**
		 * @brief	从uuid的字符串形式构建一个uuid对象.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	uuidstr		    The uuidstr.
		 * @param	[out] out_uuid 如果非null,输出uuid.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		static bool uuid_from_string(const char* uuidstr, us_uuid* out_uuid);

		/**********************************************************************//**
		 * @brief	从uuid的字符串形式构建一个uuid对象.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	uuidstr		    The uuidstr.
		 * @param	[in,out] out_uuid 如果非null,输出uuid.
		 * @return	true if it succeeds, false if it fails.
		 *************************************************************************/
		static bool uuid_from_string(const std::string& uuidstr, us_uuid* out_uuid);

		/**********************************************************************//**
		 * @brief	将一个uuid对象转换为字符串形式.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	uuid	The uuid.
		 * @param	[out]	outbuf 如果非null,outbuf用于传出uuid字符串.
		 *************************************************************************/
		static void uuid_to_string(const us_uuid& uuid, char* outbuf);

		/**********************************************************************//**
		 * @brief	Uuid to string.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	uuid			  The uuid.
		 * @param	[out] outstr If non-null, the outstr.
		 *************************************************************************/
		static void uuid_to_string(const us_uuid& uuid, std::string* outstr);

		static void uuid_to_brief_string(const us_uuid& uuid, std::string* outstr);

	protected:

		/**********************************************************************//**
		 * @brief	uuid 组装(成员量转二进制形式)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	[in]  in_uu		The in uu.
		 * @param	[out] out_uu	If non-null, the out uu.
		 *************************************************************************/

		static void uuid_pack(const us_uuid& in_uu,us_uuid* out_uu);

		/**********************************************************************//**
		 * @brief	uuid 解包(二进制转成员量)
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param in_uu			  The in uu.
		 * @param [in,out] out_uu If non-null, the out uu.
		 *************************************************************************/

		static void uuid_unpack(const us_uuid& in_uu, us_uuid *out_uu);

		/**********************************************************************//**
		 * @brief	uuid 字符串形式解析为uuid对象.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 *
		 * @param in_uu			  The in uu.
		 * @param [in,out] out_uu If non-null, the out uu.
		 * @return true if it succeeds, false if it fails.
		 *************************************************************************/

		static bool uuid_parse(const char *in_uu, us_uuid* out_uu);

		/**********************************************************************//**
		 * @brief	将 uuid 对象输出为字符串(大写)形式.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param in_uu		   The in uu.
		 * @param [in,out] out If non-null, the out.
		 *************************************************************************/

		static void uuid_unparse_lower(const us_uuid& in_uu, char *out);

		/**********************************************************************//**
		 * @brief	将 uuid 对象输出为字符串(小写)形式.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param in_uu		   The in uu.
		 * @param [in,out] out If non-null, the out.
		 *************************************************************************/

		static void uuid_unparse_upper(const us_uuid& in_uu, char *out);

		/**********************************************************************//**
		 * @brief	将 uuid 对象输出为字符串(默认大写)形式.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param in_uu		   The in uu.
		 * @param [in,out] out If non-null, the out.
		 *************************************************************************/

		static void uuid_unparse(const us_uuid& in_uu, char *out);

		/**********************************************************************//**
		 * @brief	实际将 uuid 对象转为字符串的函数.
		 * @author yimin.liu@unispace-x.com
		 * @date 2016/3/14
		 * @param in_uu		   The in uu.
		 * @param [in,out] out If non-null, the out.
		 * @param fmt		   Describes the format to use.
		 *************************************************************************/

		static void uuid_unparse_x(const us_uuid& in_uu, char *out, const char *fmt);

	protected:
		union{
			struct{
				uint32_t	time_low;	/*时间低位*/
				uint16_t	time_mid;	/*时间中位*/
				uint16_t	time_hi_and_version;	/*时间高位和版本号*/
				uint16_t	clock_seq;	/*时钟序列*/
				uint8_t		node[6];	/*节点号(MAC)*/
			};
			unsigned char m_data[16];
		};
	};

}
#endif //!__US_UUID_HPP__
