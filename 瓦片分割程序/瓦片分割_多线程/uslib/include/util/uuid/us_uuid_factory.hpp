/**********************************************************************//**
 * @file uuid\us_uuid_factory.hpp
 *
 * Declares the uuid factory class.
 *************************************************************************/

#ifndef __US_UUID_FACTORY_HPP__
#define __US_UUID_FACTORY_HPP__


#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

#include <mutex>

namespace unispace
{
	class us_uuid;

	/**********************************************************************//**
	 * @class	us_uuid_factory
	 * @brief	uuid工厂类
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/14
	 *************************************************************************/

	class us_uuid_factory
	{
		us_uuid_factory();
		~us_uuid_factory();
		
		/** 单例对象指针. */
		static us_uuid_factory* s_instance;
		/** 节点数据(默认MAC地址). */
		static unsigned char s_node[6];
		/** 时钟序列. */
		static uint16_t	s_clock_seq;
		/** 百纳秒精度的尾数部分. */
		static int32_t  s_nano_mantissa;
		/** 互斥锁，避免多线程同步获取到相同的时间序列. */
		static std::mutex	s_mt_lock;
		// 初始化 Node 值
		static void init_node();

	public:

		/******************************************************************//**
		 * @fn		static us_uuid_factory* us_uuid_factory::get_instance();
		 * @brief	获取单例对象指针.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	null if it fails, else the instance.
		 *********************************************************************/
		_US_UTIL_DLL static us_uuid_factory* get_instance();

		/******************************************************************//**
		 * @fn		us_uuid us_uuid_factory::uuid_generate();
		 * @brief	创建一个UUID(基于时间的)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @return	An us_uuid.
		 *********************************************************************/
		_US_UTIL_DLL us_uuid uuid_generate();

		/**********************************************************************//**
		 * @brief	创建一个UUID(基于时间的)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/23
		 * @param	[in,out] out_uuid If non-null, the out uuid.
		 * @return	A reference to an us_uuid.
		 *************************************************************************/
		_US_UTIL_DLL void uuid_generate(us_uuid* out_uuid);



		/******************************************************************//**
		 * @fn		static void us_uuid_factory::set_node(const unsigned char* node);
		 * @brief	设置 Node 值.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/14
		 * @param	[in,out] node If non-null, the node.
		 *********************************************************************/
		_US_UTIL_DLL static void set_node(const unsigned char* node);
	};
}

#endif //!__US_UUID_FACTORY_HPP__
