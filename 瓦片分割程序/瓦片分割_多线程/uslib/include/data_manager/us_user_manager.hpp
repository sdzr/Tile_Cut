#ifndef __US_USER_MANAGER_HPP__
#define __US_USER_MANAGER_HPP__

#ifndef __US_DATA_MANAGER_HPP__
#include "us_data_manager.hpp"
#endif

#include <stdint.h>
#include <string>

namespace unispace
{
	class us_uuid;
	class us_ustring;
	class us_user_index_list;
	class us_user_basic_meta;

	/**********************************************************************//**
	 * @brief	用户信息管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/04/26
	 *************************************************************************/

	class _US_DATA_MANAGER_DLL us_user_manager
	{
	protected:
		/** 用于转换us_user_basic_meta到二进制 */
		static bool meta_to_msgpack(const us_user_basic_meta& in, std::string& out);
		static bool msgpack_to_meta(const std::string& in, us_user_basic_meta& out);
		static bool msgpack_to_meta(const char* in_data, size_t in_size, us_user_basic_meta& out);

		// 默认构造函数
		us_user_manager() {}
		// 拷贝构造函数
		us_user_manager(const us_user_manager&) = delete;
		// 赋值操作符重载
		void operator=(const us_user_manager&) = delete;
	public:
		/**********************************************************************//**
		 * @brief	默认析构函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 *************************************************************************/
		virtual ~us_user_manager() {}

		/**********************************************************************//**
		 * @brief	添加user信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	meta		用户meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_user_meta(const us_user_basic_meta& meta) = 0;

		/**********************************************************************//**
		 * @brief	从数据库删除一条user记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	uuid	user的id.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_user(const us_uuid& uuid) = 0;

		/**********************************************************************//**
		 * @brief	从数据库删除一条user记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	name	user的用户名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_user(const us_ustring& name) = 0;

		/**********************************************************************//**
		 * @brief	从数据库查找user记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	uuid		user信息的id.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的user信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user(const us_uuid& uuid, us_user_basic_meta* out_meta) = 0;

		/**********************************************************************//**
		 * @brief	从数据库查找user记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	name		user信息的name.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的user信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user(const us_ustring& name, us_user_basic_meta* out_meta) = 0;

		/**********************************************************************//**
		 * @brief	查找user id.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	name		user的用户名.
		 * @param	[out] out_uuid	如果非NULL，传出用户id.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_uuid(const us_ustring& name,
										  us_uuid* out_uuid)const =0;

		/**********************************************************************//**
		 * @brief	查找用户名.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	uuid		user的 uuid.
		 * @param	[out] out_name	如果非NULL，传出用户名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_name(const us_uuid& uuid,
										  us_ustring* out_name)const =0;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的user数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	out_count	传出总的user meta数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_user_count(long int* out_count)const = 0;


		/**********************************************************************//**
		 * @brief	获取当前数据库user索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)用户名和用户ID的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	beg_index	要获取的user起始索引号(从0开始)
		 * @param	count		要获取的user索引数
		 * @param	out_index	传出索引范围内的user索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_user_list_by_range(int beg_index, int count,
			us_user_index_list* out_index)const = 0;

		/**********************************************************************//**
		 * @brief	判断user的meta记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @return	存在返回ture,不存在返回false.
		 *************************************************************************/
		virtual bool has_record(const us_uuid& uuid)const;

		virtual bool has_record(const us_ustring& name)const;


		/**********************************************************************//**
		 * @brief	获取一个基于SQLite的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	filename	数据库文件路径.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_user_manager* get_manager_by_sqlite(const char* filename);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		  * @param	host		主机名或IP地址
		 * @param	user		用户的MySQL登录ID
		 * @param	passwd		用户的密码
		 * @param	db			数据库名称
		 * @param	port		如果非0，其值将用作TCP/IP连接的端口号
		 * @param	unix_socket	如果非NULL，该字符串描述了应使用的套接字或命名管道
		 * @param	clientflag	通常为0，但是，也能将其设置为下述标志的组合.
		 *						|标志名称|标志描述|
		 *						|:---|:---|
		 *						|CLIENT_COMPRESS|使用压缩协议。|
		 *						|CLIENT_FOUND_ROWS|返回发现的行数（匹配的），而不是受影响的行数。|
		 *						|CLIENT_IGNORE_SPACE|允许在函数名后使用空格。使所有的函数名成为保留字。|
		 *						|CLIENT_INTERACTIVE|关闭连接之前，允许interactive_timeout秒的不活动时间。|
		 *						|CLIENT_LOCAL_FILES|允许LOAD DATA LOCAL处理功能。|
		 *						|CLIENT_MULTI_STATEMENTS|通知服务器，客户端可能在单个字符串内发送多条语句。|
		 *						|CLIENT_MULTI_RESULTS|通知服务器，客户端能够处理来自多语句执行。|
		 *						|CLIENT_NO_SCHEMA|禁止db_name.tbl_name.col_name语法。|
		 *						|CLIENT_ODBC|客户端是ODBC客户端。它将mysqld变得更为ODBC友好。|
		 *						|CLIENT_SSL|使用SSL，该选项不应由应用程序设置，而是在客户端库内部设置。|
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_user_manager* get_manager_by_mysql(const char *host,
													  const char *user,
													  const char *passwd,
													  const char *db = "unispace",
													  unsigned int port = 3306,
													  const char *unix_socket = 0,
													  unsigned long clientflag = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		  * @param	pmysql		已连接数据库的连接对象.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_user_manager* get_manager_by_mysql(void* pmysql);


		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_user_manager* get_manager_by_mongodb(const char* host,
														  unsigned short port,
														  const char* user = 0,
														  const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/26
		 * @param	client		已连接数据库的client.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_user_manager* get_manager_by_mongodb(void* client);

		/**********************************************************************//**
		 * @brief	释放用户管理器.
		 *			因为已经将析构函数设置为protected了，所有提供此函数来释放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/4/26
		 *************************************************************************/
		static void destory(us_user_manager * mgr);
	};

}

#endif //!__US_USER_MANAGER_HPP__
