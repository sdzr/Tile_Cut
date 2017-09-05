#ifndef __US_DB_SQLITE3_REPLY_HPP__
#define __US_DB_SQLITE3_REPLY_HPP__

#ifndef __US_DB_REPLY_HPP__
#include "../us_db_reply.hpp"
#endif

#ifndef __US_DATABASE_HPP__
#include "../us_database.hpp"
#endif


namespace unispace
{

	class us_db_sqlite3_driver;

	class _US_DATABASE_DLL us_db_sqlite3_reply :
		public us_db_reply
	{
	public:
		// 构造函数
		us_db_sqlite3_reply();
		// 析构函数
		virtual ~us_db_sqlite3_reply();
		// 获取错误代码
		virtual int get_error_code()const;
		// 获取错误描述
		virtual const char* get_error_string()const;

		// 获取结果集
		virtual void* get_result()const;

		friend class us_db_sqlite3_driver;
	protected:
		char*	m_result;	///< request结果(将转换为Json字符串)
		char*	m_errmsg;	///< 错误描述字符串(SQLite操作出错结果)
		int		m_errcode;	///< 错误代码(SQLite操作返回结果)
	};

}

#endif //!__US_DB_SQLITE3_REPLY_HPP__