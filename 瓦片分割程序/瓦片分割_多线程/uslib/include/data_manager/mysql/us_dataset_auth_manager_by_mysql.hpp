#ifndef __US_DATASET_AUTH_MANAGER_BY_MYSQL_HPP__
#define __US_DATASET_AUTH_MANAGER_BY_MYSQL_HPP__

#ifndef __US_DATASET_AUTH_MANAGER_HPP__
#include "us_dataset_auth_manager.hpp"
#endif

struct st_mysql;

namespace unispace
{
	class us_dataset_auth_manager_by_mysql :
		public us_dataset_auth_manager
	{
		/** 拷贝构造 */
		//us_image_manager_by_mysql(const us_dataset_auth_manager_by_mysql&)=delete;
		/** 赋值重载 */
		//void operator=(const us_dataset_auth_manager_by_mysql&)=delete;
		/** 给予基类访问权限 */
		friend class us_dataset_auth_manager;
		
		/**********************************************************************//**
		 * @brief	构造函数.
		 *			在构造的时候将进行连接到数据库，如果失败，之后所有操作都会报数据库异常错误。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/2
		 * @param	host		主机名或IP地址
		 * @param	user		的MySQL登录ID
		 * @param	passwd		密码
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
		 *************************************************************************/
		us_dataset_auth_manager_by_mysql(const char *host,
								  const char *user,
								  const char *passwd,
								  const char *db,
								  unsigned int port,
								  const char *unix_socket,
								  unsigned long clientflag);

		/**********************************************************************//**
		 * @brief	构造函数.
		 *			使用已经连接到数据库的对象，作为管理器内数据库操作对象。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		 *************************************************************************/
		us_dataset_auth_manager_by_mysql(st_mysql* pmysql);

		st_mysql* mysql;
	public:
		/** 析构函数 */
		virtual ~us_dataset_auth_manager_by_mysql();


		/**********************************************************************//**
		 * @brief	添加dataset_auth信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	meta		dataset_auth的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_dataset_auth_meta(const us_dataset_auth_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	从数据库删除一条dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid	dataset_auth的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset_auth(const us_uuid& uuid);

		/**********************************************************************//**
		 * @brief	从数据库删除一条dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name	dataset_auth的name.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset_auth(const us_ustring& name);

		/**********************************************************************//**
		 * @brief	查找dataset_auth对应的数据集uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name		dataset_auth的数据集认证名.
		 * @param	[out] out_uuid	如果非NULL，传出uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth_uuid(const us_ustring& name,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找数据集认证名.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid		dataset_auth的 uuid.
		 * @param	[out] out_name	如果非NULL，传出dataset_auth数据集认证名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth_name(const us_uuid& uuid,
										  us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	从数据库查找dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid		dataset_auth信息的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的dataset_auth信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth(const us_uuid& uuid, us_dataset_auth_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	从数据库查找dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name		dataset_auth信息的name.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的dataset_auth信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth(const us_ustring& name, us_dataset_auth_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	获取当前数据库总的dataset_auth数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	out_count	传出总的dataset_auth数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_auth_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库dataset_auth索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	beg_index	要获取的dataset_auth起始索引号(从0开始)
		 * @param	count		要获取的dataset_auth索引数
		 * @param	out_index	传出索引范围内的dataset_auth索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_auth_list_by_range(int beg_index, int count,
			us_dataset_auth_index_list* out_index)const;
	};

}

#endif //!__US_dataset_auth_MANAGER_BY_MYSQL_HPP__
