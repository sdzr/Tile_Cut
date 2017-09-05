#ifndef __US_LOG_HPP__
#define __US_LOG_HPP__


#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

//#ifndef LOG_ERR
////日志层级
//#define	LOG_EMERG	 0       /* system is unusable */
//#define	LOG_ALERT	 1       /* action must be taken immediately */
//#define	LOG_CRIT	 2       /* critical conditions */
//#define	LOG_ERR		 3       /* error conditions */
//#define	LOG_WARNING	 4       /* warning conditions */
//#define	LOG_NOTICE	 5       /* normal but significant condition */
//#define	LOG_INFO	 6       /* informational */
//#define	LOG_DEBUG	 7       /* debug-level messages */
//#endif


namespace unispace
{
	class us_ustring;
	namespace log
	{
		enum LEVEL
		{
			EMERG_LEVEL	 = 0,       /* system is unusable */
			ALERT_LEVEL	 = 1,       /* action must be taken immediately */
			CRIT_LEVEL	 = 2,       /* critical conditions */
			ERR_LEVEL	 = 3,       /* error conditions */
			WARNING_LEVEL= 4,       /* warning conditions */
			NOTICE_LEVEL = 5,       /* normal but significant condition */
			INFO_LEVEL	 = 6,       /* informational */
			DEBUG_LEVEL	 = 7       /* debug-level messages */
		};


		// 设置日志文件保存目录
		_US_UTIL_DLL bool set_save_dir(const us_ustring& dir);
		// 设置日志文件名前缀，后缀
		//bool set_prefix_suffix(const us_ustring& prefix, const us_ustring& suffix = us_ustring());
		// 设置为按时间分割日志文件(为0或负值时为停止按时间分割)
		_US_UTIL_DLL void set_dump_time(long long second);
		// 设置为按文件大小分割(最大为2GB，为0或负值的时候为不按文件大小进行分割)
		_US_UTIL_DLL void set_dump_size(int byte);
		// 设置按日志级别分割
		_US_UTIL_DLL void set_dump_level(bool yes);
		// 设置输出到标准输入输出
		_US_UTIL_DLL void set_default_out();

		/*******************************************************************//*
		 * @fn	int Emerg(const char* format,...);
		 * @brief	输出极其紧急的错误 system is unusable.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//*****************************************************************/
		_US_UTIL_DLL int Emerg(const char* format, ...);

		/********************************************************************//*
		 * @fn	int Alert(const char* format, ...);
		 * @brief	输出需立即纠正的错误 Action must be taken immediately.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int Alert(const char* format, ...);

		/********************************************************************//*
		 * @fn	int Critical(const char* format, ...);
		 * @brief	输出关键信息 Critical conditions.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int Critical(const char* format, ...);

		/******************************************************************//*
		 * @fn	int Error(const char* format, ...);
		 * @brief	需关注但不关键的错误 Error conditions.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//*****************************************************************/
		_US_UTIL_DLL int Error(const char* format, ...);

		/********************************************************************//*
		 * @fn	int Warning(const char* format, ...);
		 * @brief	输出警告信息，可能存在某种差错 warning conditions.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int Warning(const char* format, ...);

		/*******************************************************************//*
		 * @fn	int Notification(const char* format, ...);
		 * @brief	输出需要注意的信息.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int Notification(const char* format, ...);

		/********************************************************************//*
		 * @fn	int Information(const char* format, ...);
		 * @brief	输出一般提示信息 informational.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int Information(const char* format, ...);

		/*********************************************************************//*
		 * @fn	int Debug(const char* format, ...);
		 * @brief	输出调试信息 Debug-level messages.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//*******************************************************************/
		_US_UTIL_DLL int Debug(const char* format, ...);

		/*********************************************************************//*
		 * @fn	int logOut(int level, const char* format, ...);
		 * @brief	输出日志信息.
		 * @author	solym@sohu.com
		 * @date	2015/09/17
		 * @param	level 	The level.
		 * @param	format	格式控制字符串(参考printf)
		 * @return	输出的字节数.
		 *//******************************************************************/
		_US_UTIL_DLL int logOut(LEVEL level, const char* format, ...);

		/*************************************************************************//*
		 * @fn	bool setDisableOutputInfo(bool yes);
		 * @brief	设置不能够输出一般信息.
		 * @author	solym@sohu.com
		 * @date	2015/10/06
		 * @param	yes	true to yes.
		 * @return	true if it succeeds, false if it fails.
		 *//************************************************************************/
		_US_UTIL_DLL bool setDisableOutputInfo(bool yes);

		/*************************************************************************//*
		 * @fn	bool setDisableOutputWarning(bool yes);
		 * @brief	设置不能够输出警告信息.
		 * @author	solym@sohu.com
		 * @date	2015/10/06
		 * @param	yes	true to yes.
		 * @return	true if it succeeds, false if it fails.
		 *//************************************************************************/
		_US_UTIL_DLL bool setDisableOutputWarning(bool yes);

		/*************************************************************************//*
		 * @brief	设置关闭日志输出.
		 * @author	solym@sohu.com
		 * @date	2015/10/06
		 * @param	yes	true to yes.
		 * @return	true if it succeeds, false if it fails.
		 *//************************************************************************/
		_US_UTIL_DLL bool setDisableOutputLog(bool yes);
	};

}

#ifdef _DEBUG
#define US_INFO(format,...)	\
	unispace::log::Information("%s(%d)," format, __FILE__ ,__LINE__ ,##__VA_ARGS__)
#else
#define US_INFO(format,...)
#endif

// C++11要求，当字符串跟变量连接的时候，必须增加一个空格
#ifdef _DEBUG
#define US_DEBUG(format,...)	\
	unispace::log::Debug("%s(%d)," format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define US_DEBUG(format,...)
#endif

#define US_WARN(format,...)	\
	unispace::log::Warning("%s(%d)," format, __FILE__, __LINE__, ##__VA_ARGS__)

#define US_ERROR(format,...)	\
	unispace::log::Error("%s(%d)," format, __FILE__, __LINE__, ##__VA_ARGS__)


#endif //!__US_LOG_HPP__
