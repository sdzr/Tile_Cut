#ifndef __US_DB_SQLITE3_DRIVER_HPP__
#define __US_DB_SQLITE3_DRIVER_HPP__


#ifndef __US_DB_DRIVER_HPP__
#include "../us_db_driver.hpp"
#endif

#ifndef __US_DB_SQLITE3_REPLY_HPP__
#include "us_db_sqlite3_reply.hpp"
#endif

#ifndef _US_DB_SQLITE3_CONNECTION_HPP__
#include "us_db_sqlite3_connection.hpp"
#endif

#ifndef __US_DATABASE_HPP__
#include "../us_database.hpp"
#endif

struct sqlite3;

namespace unispace
{

	class _US_DATABASE_DLL us_db_sqlite3_driver :
		public us_db_driver
	{
	public:
		// 构造函数
		us_db_sqlite3_driver();
		// 析构函数
		virtual ~us_db_sqlite3_driver();
		// 连接到数据库
		virtual int connect(const us_db_connection& conn);
		// 执行一个请求(SQL语句或者NoSQL命令)
		virtual int execute(const char* sql, us_db_reply* out_reply);
		// 获取数据库的类型(描述)
		virtual const char* get_db_type()const;
		// 关闭数据库连接
		virtual int close();
	private:
		// SQLite3 exec函数调用的回调函数
		static int sqlite3_exec_callback(void * para,
										 int  n_column,
										 char ** column_value,
										 char ** column_name);
	protected:
		sqlite3*	m_db;	///< SQLite3对象句柄
	};
}

#endif //!__US_DB_SQLITE3_DRIVER_HPP__