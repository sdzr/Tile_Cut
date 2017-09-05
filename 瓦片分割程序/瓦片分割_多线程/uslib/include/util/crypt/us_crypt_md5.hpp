#ifndef __US_CRYPT_MD5_HPP__
#define __US_CRYPT_MD5_HPP__

#ifndef __US_STRING_HPP__
#include "common/us_string.hpp"
#endif

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{
	class _US_UTIL_DLL us_crypt_md5 {
	public:
		/**********************************************************************//**
		 * @brief	获取md5值的十六进制字符串结果.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @return	字符数组地址.
		 *************************************************************************/
		const char* get_hex_digest()const;

		/**********************************************************************//**
		 * @brief	更新md5值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @param	input	用于计算md5值的数据.
		 * @param	len		数据字节数.
		 * @return	成功返回true.
		 *************************************************************************/
		bool update(unsigned char* input, size_t len);

		/**********************************************************************//**
		 * @brief	更新md5值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @param	filepath	文件路径(用于计算md5值).
		 * @return	成功返回true.
		 *************************************************************************/
		bool update(const us_ustring& filepath);
	private:
		unsigned char m_data[16];
	};
}

#endif // !__US_CRYPT_MD5_HPP__