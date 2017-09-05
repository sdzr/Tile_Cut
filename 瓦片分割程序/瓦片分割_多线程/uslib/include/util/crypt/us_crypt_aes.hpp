#ifndef __US_CRYPT_AES_HPP__
#define __US_CRYPT_AES_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{
	class _US_UTIL_DLL us_crypt_aes {
	public:
		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @param	key		密匙.
		 * @param	len		密匙字节数,必须为128,192或256.
		 *************************************************************************/
		us_crypt_aes(unsigned char* key, int len);

		/**********************************************************************//**
		 * @brief	加密数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @param	input	待加密数据.
		 * @param	len		待加密数据字节数.
		 * @param	output	密文输出.
		 *************************************************************************/
		void encode_cbc(unsigned char* input, size_t len,unsigned char* output);

		/**********************************************************************//**
		 * @brief	解密数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @param	input	待解密数据.
		 * @param	len		待解密数据字节数.
		 * @param	output	明文输出.
		 *************************************************************************/
		void decode_cbc(unsigned char* input, size_t len, unsigned char* output);

	private:
		unsigned char m_key[256];
		int			  m_key_size;
	};
}

#endif // !__US_CRYPT_AES_HPP__
