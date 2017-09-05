#ifndef __US_DB_SQLITE3_CONNECTION_HPP__
#define __US_DB_SQLITE3_CONNECTION_HPP__

#ifndef __US_DB_CONNECTION_HPP__
#include "../us_db_connection.hpp"
#endif

#ifndef __US_DATABASE_HPP__
#include "../us_database.hpp"
#endif

namespace unispace
{

	class _US_DATABASE_DLL us_db_sqlite3_connection :
		public us_db_connection
	{
	public:
		us_db_sqlite3_connection();
		virtual ~us_db_sqlite3_connection();

		// 获取数据库类型描述
		virtual const char* get_db_type()const;

		// 获取主机地址(例如IP/sqlite文件路径等)
		virtual const char* get_host()const;

		/**********************************************************************//**
		 * @brief	设置数据库路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/
		bool set_dbfile_path(const char* filename);

		// 获取端口号(sqlite等无需端口号的可以不实现)
		//virtual int get_port();

		// 获取数据库连接的时候的用户名
		//virtual const char* get_user();

		// 获取对应用户的密码
		//virtual const char* get_passwd();

	private:
		char* m_filename;	///< 数据库文件路径
	};

}


#endif //!__US_DB_SQLITE3_CONNECTION_HPP__