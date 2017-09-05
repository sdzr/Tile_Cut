#ifndef __US_DB_DRIVER_HPP__
#define __US_DB_DRIVER_HPP__

namespace unispace
{


	class us_db_connection;
	class us_db_reply;

	/**********************************************************************//**
	 * @class	us_db_driver
	 * @brief	数据库操作驱动类基类.
	 * 			实现对数据库的连接、关闭、执行SQL语句等请求命令.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/4/25
	 *************************************************************************/
	class us_db_driver
	{
	public:
		us_db_driver();
		// 析构函数，派生类必须实现
		virtual ~us_db_driver() = 0{}

		/**********************************************************************//**
		 * @brief	连接到数据库.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的结果根据具体实现确定.
		 *************************************************************************/
		virtual int connect(const us_db_connection& conn) = 0;

		/**********************************************************************//**
		 * @brief	执行一个请求(SQL语句或者NoSQL命令).
		 * 			例如，在SQLite的封装实现中，就是SQL语句。在Redis中就是相关的命令。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的结果根据具体实现确定.
		 *************************************************************************/
		virtual int execute(const char* request, us_db_reply* out_reply) = 0;
		
		/**********************************************************************//**
		 * @brief	获取数据库的类型(描述).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回数据库的描述字符串.
		 *************************************************************************/
		virtual const char* get_db_type()const;

		/**********************************************************************//**
		 * @brief	关闭数据库连接.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回的结果根据具体实现确定.
		 *************************************************************************/
		virtual int close() = 0;
	};


}

#endif //!__US_DB_DRIVER_HPP__