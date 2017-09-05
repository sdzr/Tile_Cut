#ifndef __US_DB_CONNECTION_HPP__
#define __US_DB_CONNECTION_HPP__

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_db_connection
	 * @brief	数据库连接信息类基类.
	 * 			实现获取需要连接的数据库的连接相关参数等.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/4/25
	 *************************************************************************/
	class us_db_connection
	{
	public:
		// 构造函数
		us_db_connection();
		// 析构函数
		virtual ~us_db_connection();
		// 获取数据库类型描述
		virtual const char* get_db_type()const;

		/**********************************************************************//**
		 * @brief	获取主机地址(例如IP/sqlite文件路径等).
		 * 			派生类必须实现此方法。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回主机地址或数据库路径.
		 *************************************************************************/
		virtual const char* get_host()const = 0;
		
		/**********************************************************************//**
		 * @brief	获取端口号(sqlite等无需端口号的可以不实现).
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回端口号.
		 *************************************************************************/
		virtual int get_port()const;

		/**********************************************************************//**
		 * @brief	获取数据库连接的时候的用户名.
		 * 			无需用户验证的数据库可以不实现.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回数据库验证使用的用户名.
		 *************************************************************************/
		virtual const char* get_user()const;
		
		/**********************************************************************//**
		 * @brief	获取对应用户的密码.
		 * 			无需用户验证的数据库可以不实现.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/4/25
		 * @return	返回数据库验证使用的账户的密码.
		 *************************************************************************/
		virtual const char* get_passwd()const;
	};

}

#endif //!__US_DB_CONNECTION_HPP__