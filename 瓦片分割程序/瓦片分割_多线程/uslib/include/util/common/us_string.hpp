/**********************************************************************//**
 * @file common\us_string.hpp
 *
 * Declares the string class.
 *************************************************************************/

#ifndef __US_STRING_HPP__
#define __US_STRING_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#include <string>
#include <vector>
#include <list>
#include <set>
#include <stdint.h>


namespace unispace
{
	/**********************************************************************//**
	 * @class	us_string
	 * @brief	字符串封装类.<br>
	 * 			继承自std::string，并对内部的操作默认使用utf-8编码。使用C风格的字符串来
	 * 			初始化的的时候要注意编码问题。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/04
	 *************************************************************************/
	class us_ustring :
		public std::string
	{
	public:
		//构造函数
		_US_UTIL_DLL us_ustring() :std::string(){}
		_US_UTIL_DLL us_ustring(size_type count, char ch) : std::string(count, ch){}
		_US_UTIL_DLL us_ustring(const std::string& other,
				  size_type pos,
				  size_type count = std::string::npos)
				  :std::string(other, pos, count){}
		_US_UTIL_DLL us_ustring(const char* s, size_type count) : std::string(s, count){}
		// 不允许给us_string赋值一个C风格字符串(隐式转换)
		// 注意编码问题
		explicit us_ustring(const char* s) :std::string(s){}
		template< class InputIt >
		us_ustring(InputIt first, InputIt last) : std::string(first, last){}
		// 拷贝构造
		_US_UTIL_DLL us_ustring(const us_ustring& other) : std::string(other){}
		_US_UTIL_DLL us_ustring(const std::string& other) : std::string(other){}

		// 移动构造
		_US_UTIL_DLL us_ustring(us_ustring&& other) : std::string(std::move(other)){}
		_US_UTIL_DLL us_ustring(std::string&& other) : std::string(std::move(other)){}
		// 列表初始化
		_US_UTIL_DLL us_ustring(std::initializer_list<char> init) : std::string(init){}

		// using std::string::operator=;
		// using std::string::operator+=;
		// using std::string::operator[];

		_US_UTIL_DLL us_ustring operator+ (const us_ustring&);
		_US_UTIL_DLL us_ustring operator+ (char ch);

		_US_UTIL_DLL us_ustring& operator=(const us_ustring&);
		_US_UTIL_DLL us_ustring& operator=(us_ustring&& str);
		_US_UTIL_DLL us_ustring& operator=(char ch);

		_US_UTIL_DLL us_ustring& operator+= (char ch);
		_US_UTIL_DLL us_ustring& operator+= (const us_ustring& other);
		_US_UTIL_DLL us_ustring& append(const us_ustring& other);
		using std::string::append;
		

	public:
		
		/**********************************************************************//**
		 * @brief	设置值为数字的十进制字符串形式.
		 *			只支持转换为10进制形式的数字。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	num		待转换的数字.
		 * @return	数字形式的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& set_num(short int num);
		_US_UTIL_DLL us_ustring& set_num(unsigned short num);
		_US_UTIL_DLL us_ustring& set_num(int num);
		_US_UTIL_DLL us_ustring& set_num(unsigned int num);
		_US_UTIL_DLL us_ustring& set_num(long long int num);
		_US_UTIL_DLL us_ustring& set_num(unsigned long long num);
		_US_UTIL_DLL us_ustring& set_num(float num);
		_US_UTIL_DLL us_ustring& set_num(double num);
		_US_UTIL_DLL us_ustring& set_num(long double num);

		/**********************************************************************//**
		 * @brief	转换字符串为bool值.
		 *			支持'true''false'字符串形式的值，以及可转换为数字的值进行转换。
		 *			可以通过参数ok获取是否转换成功.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	[out] ok	传出是否成功.
		 * @return	转换得到的bool值.
		 *************************************************************************/
		_US_UTIL_DLL const bool to_bool(bool* ok = NULL)const;

		/**********************************************************************//**
		 * @brief	转换字符串为数值.
		 *			进制默认为10，如果需要其他可以自行设定(支持2/8/16等)。可以设置为
		 *			0进行自动判断进制。
		 *			无法转换或者超出范围的时候会出错，可以通过参数ok获取是否转换成功.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	base		数字的进制.
		 * @param	[out] ok	传出是否成功.
		 * @return	转换得到的bool值.
		 *************************************************************************/
		_US_UTIL_DLL const int32_t  to_int32(int base = 10,bool* ok = NULL)const;
		_US_UTIL_DLL const uint32_t to_uint32(int base = 10, bool* ok = NULL)const;
		_US_UTIL_DLL const int64_t  to_int64(int base = 10, bool* ok = NULL)const;
		_US_UTIL_DLL const uint64_t to_uint64(int base = 10, bool* ok = NULL)const;
		_US_UTIL_DLL const float    to_float(bool* ok = NULL)const;
		_US_UTIL_DLL const double   to_double(bool* ok = NULL)const;

		/**********************************************************************//**
		 * @brief	获取字符串中的英文字母全部小写的拷贝串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/14
		 * @return	返回由这个字符串转换的小写字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring to_lower()const;

		/**********************************************************************//**
		 * @brief	获取字符串中的英文字母全部大写的拷贝串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/14
		 * @return	返回由这个字符串转换的大写字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring to_upper()const;



		/**********************************************************************//**
		 * @brief	删除左边指定的字符(默认空白字符).
		 *			默认删除字符串首部的'\r\t\n\v'和空格等空白字符。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	trimstr		匹配的字符组成的字符串(不支持中文)
		 * @return	删除空白后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& set_trim_left(const std::string& trimstr = " \r\n\t\v");
		/**********************************************************************//**
		 * @brief	删除右边指定的字符(默认空白字符).
		 *			默认删除字符串尾部的'\r\t\n\v'和空格等空白字符。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	trimstr		匹配的字符组成的字符串(不支持中文)
		 * @return	删除空白后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& set_trim_right(const std::string& trimstr = " \r\n\t\v");
		/**********************************************************************//**
		 * @brief	删除两边指定的字符(默认空白字符).
		 *			默认删除两头尾部的'\r\t\n\v'和空格等空白字符。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/23
		 * @param	trimstr		匹配的字符组成的字符串(不支持中文)
		 * @return	删除空白后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& set_trim(const std::string& trimstr = " \r\n\t\v");


		/**********************************************************************//**
		 * @brief	替换子串.
		 *			使用newstr替换所有的substr。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/21
		 * @param	substr		待替换的子串(pattern).
		 * @param	newstr		用于替换的字符串(replacement).
		 * @return	替换子串后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& replace_substr(
			const us_ustring& substr, const us_ustring& newstr);
		/**********************************************************************//**
		 * @brief	替换子串.
		 *			使用newstr替换第一个出现的的substr。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/21
		 * @param	substr		待替换的子串(pattern).
		 * @param	newstr		用于替换的字符串(replacement).
		 * @return	替换子串后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& replace_substr_first(
			const us_ustring& substr, const us_ustring& newstr);
		/**********************************************************************//**
		 * @brief	替换子串.
		 *			使用newstr替换最后一个出现的substr。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/21
		 * @param	substr		待替换的子串(pattern).
		 * @param	newstr		用于替换的字符串(replacement).
		 * @return	替换子串后的字符串.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring& replace_substr_last(
			const us_ustring& substr, const us_ustring& newstr);

		/**********************************************************************//**
		 * @brief	分割字符串为子字符串.
		 *			使用delim作为分隔串，分隔字符串为多个子串，并存入传出容器中。
		 *			传出结果中不包含空字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/07/28
		 * @param	delim		标识子字符串边界的字符串.
		 * @param	strvec		用于传出子串结果的容器.
		 *************************************************************************/
		_US_UTIL_DLL void split(const std::string& delim, std::vector<us_ustring>* strvec);
		_US_UTIL_DLL void split(const std::string& delim, std::list<us_ustring>* strlist);
		_US_UTIL_DLL void split(const std::string& delim, std::set<us_ustring>* strset);
	public:

		/**********************************************************************//**
		 * @brief	获取转换为GBK编码的字符串.
		 *			转换的时候，将跳过Unicode值大于0x0000FFFF的部分。对于不能转换为对应的
		 *			GBK编码的部分，将以0xFFFF填充，这是一个不存在的GBK编码值。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @return	一个以GBK编码的std::string字符串.
		 *************************************************************************/
		_US_UTIL_DLL std::string to_gbk(bool* ok = NULL)const;

		/**********************************************************************//**
		 * @brief	获取转换为UTF-16 LE编码的字符串
		 *			转换的时候，将跳过Unicode值大于0x0000FFFF的部分。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	addbom	是否添加BOM标记.
		 * @param	ok		传出转换是否成功(不符合utf8编码的字符串传出false).
		 * @return	以UTF-16LE编码的std::u16string字符串，带有BOM标识.
		 *************************************************************************/
		_US_UTIL_DLL std::u16string to_utf16le(bool addbom = false, bool* ok = NULL)const;

		/**********************************************************************//**
		 * @brief	获取转换为UTF-16 BE的字符串(带BOM)
		 *			转换的时候，将跳过Unicode值大于0x0000FFFF的部分。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	addbom	是否添加BOM标记.
		 * @param	ok		传出转换是否成功(不符合utf8编码的字符串传出false).
		 * @return 以UTF-16BE编码的std::u16string字符串，带有BOM标识.
		 *************************************************************************/
		_US_UTIL_DLL std::u16string to_utf16be(bool addbom = false, bool* ok = NULL)const;



		/**********************************************************************//**
		 * @brief	获取字符总数.
		 *			获取的是字符的数量，不是字节数。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @return	The character number.
		 *************************************************************************/
		_US_UTIL_DLL size_type get_character_number()const;


		/**********************************************************************//**
		 * @brief	判断是否是合法的UTF-8编码字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @return	true if UTF 8 encode, false if not.
		 *************************************************************************/
		_US_UTIL_DLL bool is_utf8_encode()const;


	public:
		/**********************************************************************//**
		 * @brief	从GBK编码的字符串构建.
		 *			对于传入的GBK编码，并不检测其编码的正确性。对于不能转换的码位，以0xFFFF
		 *			替代.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	gbkstr	gbk编码的C风格字符串.
		 * @return	以UTF8编码的us_string字符串.
		 *************************************************************************/
		_US_UTIL_DLL static us_ustring from_gbk(const char* gbkstr);

		/**********************************************************************//**
		 * @brief	从GBK编码的字符串构建.
		 *			对于传入的GBK编码，并不检测其编码的正确性。对于不能转换的码位，以0xFFFF
		 *			替代.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	gbkstr	gbk编码的字符串.
		 * @return	以UTF8编码的us_string字符串.
		 *************************************************************************/
		_US_UTIL_DLL static us_ustring from_gbk(const std::string& gbkstr);

		/**********************************************************************//**
		 * @brief	从UTF16编码字符串构建，需要带BOM标记.
		 *			必须是带BOM标记的字符串，否则将无法区分是LE还是BE编码。如果第一个元素不是
		 *			BOM标记，将返回一个空字符串。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	u16str	UTF16编码的字符串.
		 * @return	以UTF8编码的us_string字符串.
		 *************************************************************************/
		_US_UTIL_DLL static us_ustring from_utf16_with_bom(const std::u16string& u16str);

		/**********************************************************************//**
		 * @brief	从UTF16 LE编码的字符串创建.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	u16str UTF16-LE编码的字符串.
		 * @return	以UTF8编码的us_string字符串.
		 *************************************************************************/
		_US_UTIL_DLL static us_ustring from_utf16le(const std::u16string& u16str);

		/**********************************************************************//**
		 * @brief	从UTF16BE编码字符串创建.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/22
		 * @param	u16str UTF16-BE编码的字符串.
		 * @return	以UTF8编码的us_string字符串.
		 *************************************************************************/
		_US_UTIL_DLL static us_ustring from_utf16be(const std::u16string& u16str);
	};

}

#endif	//!__US_STRING_HPP__
