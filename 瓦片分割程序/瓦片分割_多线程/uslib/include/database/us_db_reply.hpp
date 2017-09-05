#ifndef __US_DB_REPLY_HPP__
#define __US_DB_REPLY_HPP__

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_db_reply
	 * @brief	数据库请求结果类基类.
	 * 			需要派生类实现三个方法.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/4/25
	 *************************************************************************/
	class us_db_reply
	{
	public:
		us_db_reply(){};
		virtual ~us_db_reply(){};
		/**********************************************************************//**
		 * @brief	获取错误代码.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的错误代码根据具体实现确定.
		 *************************************************************************/
		virtual int get_error_code()const = 0;

		/**********************************************************************//**
		 * @brief	获取错误描述.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的错误描述根据具体实现确定.
		 *************************************************************************/
		virtual const char* get_error_string()const = 0;

		/**********************************************************************//**
		 * @brief	获取结果即.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的结果集根据具体实现确定.
		 *************************************************************************/
		virtual void* get_result()const = 0;
	};

}

#endif //!__US_DB_REPLY_HPP__