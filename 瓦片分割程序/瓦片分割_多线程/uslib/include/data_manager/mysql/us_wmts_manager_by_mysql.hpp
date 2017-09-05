#ifndef __US_WMTS_MANAGER_BY_MYSQL_HPP__
#define __US_WMTS_MANAGER_BY_MYSQL_HPP__

#ifndef __US_WMTS_MANAGER_HPP__
#include "us_wmts_manager.hpp"
#endif

struct st_mysql;

namespace unispace
{
	class us_wmts_manager_by_mysql :
		public us_wmts_manager
	{
		/** 拷贝构造 */
		//us_image_manager_by_mysql(const us_wmts_manager_by_mysql&)=delete;
		/** 赋值重载 */
		//void operator=(const us_wmts_manager_by_mysql&)=delete;
		/** 给予基类访问权限 */
		friend class us_wmts_manager;
		
		/**********************************************************************//**
		 * @brief	构造函数.
		 *			在构造的时候将进行连接到数据库，如果失败，之后所有操作都会报数据库异常错误。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/2
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
		 *************************************************************************/
		us_wmts_manager_by_mysql(const char *host,
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
		us_wmts_manager_by_mysql(st_mysql* pmysql);

		st_mysql* mysql;
	public:
		/** 析构函数 */
		virtual ~us_wmts_manager_by_mysql();


		/**********************************************************************//**
		 * @brief	添加wmts信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_wmts_meta(const us_wmts_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	从数据库删除一条wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	uuid	wmts的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_wmts(const us_uuid& uuid);

		/**********************************************************************//**
		 * @brief	从数据库删除一条wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	layer	wmts的layer.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_wmts(const us_ustring& layer);

		/**********************************************************************//**
		 * @brief	查找wmts对应的数据集uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	layer		wmts的图层名.
		 * @param	[out] out_uuid	如果非NULL，传出uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_uuid(const us_ustring& layer,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找影像文件的路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	uuid		wmts的 uuid.
		 * @param	[out] out_layer	如果非NULL，传出wmts图层名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_layer(const us_uuid& uuid,
										  us_ustring* out_layer)const;

		/**********************************************************************//**
		 * @brief	从数据库查找wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	uuid		wmts信息的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的wmts信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts(const us_uuid& uuid, us_wmts_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	从数据库查找wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	layer		wmts信息的layer.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的wmts信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts(const us_ustring& layer, us_wmts_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	获取当前数据库总的wmts数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_wmts_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库wmts索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/11
		 * @param	beg_index	要获取的wmts起始索引号(从0开始)
		 * @param	count		要获取的wmts索引数
		 * @param	out_index	传出索引范围内的wmts索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_wmts_list_by_range(int beg_index, int count,
			us_wmts_index_list* out_index)const;
	};

}

#endif //!__US_WMTS_MANAGER_BY_MYSQL_HPP__
