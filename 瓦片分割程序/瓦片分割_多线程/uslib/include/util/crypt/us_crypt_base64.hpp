#ifndef __US_CRYPT_BASE64_HPP__
#define __US_CRYPT_BASE64_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{
	class _US_UTIL_DLL us_crypt_base64
	{
	public:
		/**
		* \brief          编码一个buffer到base64格式
		*
		* \param dst      目标 buffer
		* \param dlen     目标buffer大小
		* \param src      源 buffer
		* \param slen     要编码的数据量
		*
		* \return         成功返回0，失败返回非0值.
		*
		* \note           调用时候传入的 *dlen = 0 用于获取适当的*dlen大小.
		*/
		static int encode(unsigned char *dst, int *dlen,
			unsigned char *src, int  slen);

		/**
		* \brief          解码一个base64格式数据
		*
		* \param dst      目标 buffer
		* \param dlen     目标buffer大小
		* \param src      源 buffer
		* \param slen     要解码的数据量
		*
		* \return         成功返回0，失败返回非0值.
		*
		* \note           调用时候传入的 *dlen = 0 用于获取适当的*dlen大小.
		*/
		static int decode(unsigned char *dst, int *dlen,
			unsigned char *src, int  slen);

	};

}
#endif // !__US_CRYPT_BASE64_HPP__
