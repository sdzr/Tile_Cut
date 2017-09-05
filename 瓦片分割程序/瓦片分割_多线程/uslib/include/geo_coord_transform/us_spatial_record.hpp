#ifndef __US_SPATIAL_RECORD_HPP__
#define __US_SPATIAL_RECORD_HPP__


#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif // !__US_STRING_HPP__

#include <string.h>

/*
* 使用uuid来表示一个空间参考的编码
* uuid各个字节表示内容如下
* |0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F|
*  | \ \_________    ____________/
*  |  \          \  /
* 版本 是否    坐标编码(C风格字符串形式)
* 0   自定义   最多13个字符，多余位全部置零
*/
namespace unispace
{
	struct us_spatial_record
	{
	public:
		// 获取版本号
		inline int get_version()const
		{
			return id.get_raw_data()[0];
		}
		// 获取是否是用户自定义空间参考
		inline bool is_user_define_spr()const
		{
			return id.get_raw_data()[1] == 1;
		}
		// 获取空间参考标识码
		inline uint32_t get_spr_code()const
		{
			return std::atoll((const char*)id.get_raw_data() + 2);
		}
		inline const char* get_spr_code_str()const
		{
			return (const char*)(id.get_raw_data() + 2);
		}
		// 设置空间参考ID
		inline void set_spr_id(uint32_t spr_code, bool userdef = true, uint8_t version = 0)
		{
			uint8_t* data = (uint8_t*)id.get_raw_data();
			memset(data, 0, 16);
			data[0] = version;
			data[1] = userdef ? 1 : 0;
			std::string codestr = std::to_string(spr_code);
			memcpy(data + 2, codestr.c_str(), codestr.size());
		}
	public:
		us_uuid		id;			///< 空间参考内部编码
		us_ustring	name;		///< 空间参考名称
		us_ustring	projdef;	///< 空间参考的proj4定义字符串
	};

	inline bool operator< (const us_spatial_record& t1, const us_spatial_record& t2)
	{
		return t1.id < t2.id;
	}
	inline bool operator== (const us_spatial_record& t1, const us_spatial_record& t2)
	{
		return (t1.id == t2.id) &&
			(t1.name == t2.name) &&
			(t1.projdef == t2.projdef);
	}
	inline bool operator!= (const us_spatial_record& t1, const us_spatial_record& t2)
	{
		return !(t1 == t2);
	}

}

#endif // !__US_SPATIAL_RECORD_HPP__

