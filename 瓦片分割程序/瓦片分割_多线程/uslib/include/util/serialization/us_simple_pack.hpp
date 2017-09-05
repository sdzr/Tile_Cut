#ifndef __US_SIMPALE_PACK_HPP__
#define __US_SIMPALE_PACK_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{

	namespace serialization
	{
		typedef enum
		{
			TP_ST_OK               = 0,	// 成功
			TP_ST_PARAM_INVALID    = 1,	// 参数无效
			TP_ST_ALLOC_BAD        = 2,	// 内存申请失败
			TS_ST_STRING_TOO_LONG  = 3,	// 字符串太长
			TP_ST_ARRAT_TOO_LONG   = 4,	// 数组太长
			TP_ST_TYPE_NOT_MATCH   = 5,	// 类型不匹配
			TP_ST_OUT_OF_RANGE     = 6,	// 超出范围
			TS_ST_NOT_ENOUGH_DATA  = 7,	// 没有足够数据
			TP_ST_BUFFER_TOO_SMALL = 8,	// 缓冲区太小
			TP_ST_VALUE_OVERFLOW   = 9	// 数值溢出
		}us_serialization_status;

		typedef us_serialization_status US_SR_CODE;

#pragma pack()
#pragma pack(8)
		struct us_serializtion_object {
			uint64_t capacity;	// 容量
			uint64_t lenght;	// 当前使用长度
			uint8_t* data;		// 数据区
		};
#pragma pack()

		/**********************************************************************//**
		 * @brief	获取状态码信息字符串.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	ts		状态码.
		 * @param	返回状态码信息字符串指针(不会返回NULL).
		 *************************************************************************/
		_US_UTIL_DLL const char* us_status_string(us_serialization_status st);

		/**********************************************************************//**
		 * @brief	创建一个序列化对象.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	成功返回序列化对象地址，失败返回NULL.
		 *************************************************************************/
		_US_UTIL_DLL struct us_serializtion_object* us_create_serialization_object();

		/**********************************************************************//**
		 * @brief	释放一个序列化对象.
		 *			必须是由us_create_serialization_object()调用的，才能使用本函数
		 *			释放，否则会出问题。释放完成后请主动将obj置为NULL.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 *************************************************************************/
		_US_UTIL_DLL void us_free_serialization_object(struct us_serializtion_object* obj);

		/**********************************************************************//**
		 * @brief	打包数据进序列化对象(尾部).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	value	要打包进去的值.
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_pack_bool(struct us_serializtion_object* obj, bool value);
		_US_UTIL_DLL US_SR_CODE us_pack_int32(struct us_serializtion_object* obj, int32_t value);
		_US_UTIL_DLL US_SR_CODE us_pack_int64(struct us_serializtion_object* obj, int64_t value);
		_US_UTIL_DLL US_SR_CODE us_pack_uint32(struct us_serializtion_object* obj, uint32_t value);
		_US_UTIL_DLL US_SR_CODE us_pack_uint64(struct us_serializtion_object* obj, uint64_t value);
		_US_UTIL_DLL US_SR_CODE us_pack_float32(struct us_serializtion_object* obj, float value);
		_US_UTIL_DLL US_SR_CODE us_pack_float64(struct us_serializtion_object* obj, double value);

		/**********************************************************************//**
		 * @brief	打包一个字节数组数据进序列化对象(尾部).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	value	要打包进去的数组首地址.
		 * @param	value	要打包进去的数组长度(字节数).
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_pack_byte_array(struct us_serializtion_object* obj, const void* value, uint32_t len);

		/**********************************************************************//**
		 * @brief	打包一个C风格字符串数据进序列化对象(尾部).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	value	要打包进去的字符串首地址.
		 * @param	value	要打包进去的数组长度(字节数).
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_pack_c_string_n(struct us_serializtion_object* obj, const char* value, uint32_t len);

		/**********************************************************************//**
		 * @brief	打包一个C风格字符串数据进序列化对象(尾部).
		 *			字符串的长度使用strlen获取.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	value	要打包进去的字符串首地址.
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_pack_c_string(struct us_serializtion_object* obj, const char* value);

		/**********************************************************************//**
		 * @brief	从序列包中读取数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置，传出下一个读取的偏移位置.
		 * @param	out_value	传出读取到的数据.
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_unpack_bool(const struct us_serializtion_object* obj, uint64_t* offset, bool* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_int8(const struct us_serializtion_object* obj, uint64_t* offset, int8_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_uint8(const struct us_serializtion_object* obj, uint64_t* offset, uint8_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_int16(const struct us_serializtion_object* obj, uint64_t* offset, int16_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_uint16(const struct us_serializtion_object* obj, uint64_t* offset, uint16_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_int32(const struct us_serializtion_object* obj, uint64_t* offset, int32_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_uint32(const struct us_serializtion_object* obj, uint64_t* offset, uint32_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_int64(const struct us_serializtion_object* obj, uint64_t* offset, int64_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_uint64(const struct us_serializtion_object* obj, uint64_t* offset, uint64_t* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_float32(const struct us_serializtion_object* obj, uint64_t* offset, float* out_value);
		_US_UTIL_DLL US_SR_CODE us_unpack_float64(const struct us_serializtion_object* obj, uint64_t* offset, double* out_value);

		/**********************************************************************//**
		 * @brief	从序列包中读取一个字节数组的数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置，传出下一个读取的偏移位置.
		 * @param	out_buf		存放读取到的数据.
		 * @param	in_out_len	传入缓冲区大小，传出读取到的字节数.
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_unpack_byte_array(const struct us_serializtion_object* obj, uint64_t* offset, void* out_buf, uint32_t* in_out_len);
		/**********************************************************************//**
		 * @brief	从序列包中引用一个字节数组的数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置，传出下一个读取的偏移位置.
		 * @param	out_ptr	传出字节数组的首地址.
		 * @param	out_len	传出字节数组的字节数.
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_unpack_byte_array_ref(const struct us_serializtion_object* obj, uint64_t* offset, void** out_ptr, uint32_t* out_len);

		/**********************************************************************//**
		 * @brief	从序列包中读取一个C风格的字符串数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置，传出下一个读取的偏移位置.
		 * @param	out_buf		存放读取到的数据.
		 * @param	in_out_len	传入缓冲区大小，传出读取到的字节数(不含结尾'\0').
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_unpack_c_string(const struct us_serializtion_object* obj, uint64_t* offset, char* out_buf, uint32_t* in_out_len);
		/**********************************************************************//**
		 * @brief	从序列包中引用一个字节数组的数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置，传出下一个读取的偏移位置.
		 * @param	out_ptr	传出字符串的首地址.
		 * @param	out_len	传出字符串的字节数(不含结尾'\0').
		 * @param	返回状态码.
		 *************************************************************************/
		_US_UTIL_DLL US_SR_CODE us_unpack_c_string_ref(const struct us_serializtion_object* obj, uint64_t* offset, char** out_ptr, uint32_t* out_len);
		
		/**********************************************************************//**
		 * @brief	从序列包获取字节数组或C风格字符串长度（不含'\0'）.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/14
		 * @param	obj		序列化对象指针.
		 * @param	offset	传入读取的偏移位置.
		 * @param	返回size，失败返回-1.
		 *************************************************************************/
		_US_UTIL_DLL int64_t us_get_byte_array_or_string_size(const struct us_serializtion_object* obj, uint64_t offset);
	};

}

#endif // !__US_SIMPALE_PACK_HPP__
