/**********************************************************************//**
 * @file us_dataset_manager.hpp
 *
 * Declares the us_dataset_manager class.
 *************************************************************************/

#ifndef __US_DATASET_MANAGER_HPP__
#define __US_DATASET_MANAGER_HPP__

#include <stdint.h>
#include <vector>
#include <string>

#ifndef __US_DATA_MANAGER_HPP__
#include "us_data_manager.hpp"
#endif

namespace unispace
{
	class us_ustring;
	class us_uuid;
	class us_image_manager_by_sqlite;	//sqlite数据库管理影像
	class us_dataset_basic_meta;	// 数据集meta类
	class us_dataset_index_list;


	/**********************************************************************//**
	 * @brief	数据集管理类.
	 *			数据集是多个影像数据的集合，数据集有自己的Meta信息.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/22
	 *************************************************************************/

	class _US_DATA_MANAGER_DLL us_dataset_manager
	{
	protected:
		/** 用于转换us_dataset_basic_meta到二进制 */
		static bool meta_to_msgpack(const us_dataset_basic_meta& in, std::string& out);
		static bool msgpack_to_meta(const std::string& in, us_dataset_basic_meta& out);
		static bool msgpack_to_meta(const char* in_data, size_t in_size, us_dataset_basic_meta& out);

		us_dataset_manager(const us_dataset_manager&) {};
		us_dataset_manager& operator=(const us_dataset_manager&);
		us_dataset_manager();
	public:
		virtual ~us_dataset_manager();

		/**********************************************************************//**
		 * @brief	添加数据集到数据库.
		 *			如果已经存在，？？？？
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	meta			数据集meta信息.
		 * @param	update_ctime	是否更新创建时间.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_dataset(us_dataset_basic_meta& meta,
									  bool update_ctime = true)const = 0;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	uuid		数据集的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_uuid& uuid)const = 0;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	name		数据集的名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_ustring& name)const = 0;

		/**********************************************************************//**
		 * @brief	查找数据集名称.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/29
		 * @param	uuid			数据集的 uuid.
		 * @param	[out] out_name	如果非NULL，传出数据集名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_name(const us_uuid& uuid,
											us_ustring* out_name)const = 0;

		/**********************************************************************//**
		 * @brief	查找数据集UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/29
		 * @param	name			影像的 uuid数据集的名称.
		 * @param	[out] out_uuid	如果非NULL，传出数据集UUID.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_uuid(const us_ustring& name,
											us_uuid* out_uuid)const = 0;



		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	uuid		数据集的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据集的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_uuid& uuid,
									   us_dataset_basic_meta* out_meta)const = 0;

		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	name		数据集的名称.
		 * @param	[out] out_meta	如果非NULL，传出数据集的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_ustring& name,
									   us_dataset_basic_meta* out_meta)const = 0;

		/**********************************************************************//**
		 * @brief	更新数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	meta			数据集meta信息.
		 * @param	not_up_uuidset	是否不更新uuidset，默认为是.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_dataset(us_dataset_basic_meta& meta,
										 bool not_up_uuidset = true)const = 0;


		/**********************************************************************//**
		 * @brief	更新数据集包含的影像的uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/20
		 * @param	uuid		数据集的uuid.
		 * @param	uuidset		要更新的uuid集合.
		 * @param	op			进行的操作.
		 *						|值|操作|
		 *						|:---|:---|
		 *						|1|添加uuidset中的uuid到数据集|
		 *						|2|从数据集中删除uuidset中的uuid|
		 *						|3|使用uuidset中的uuid替换数据集中包含的|
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_dataset_uuidset(const us_uuid& uuid,
												 const std::vector<us_uuid>& uuidset,
												 int op);


		/**********************************************************************//**
		 * @brief	获取当前数据库总的数据集数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/22
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_count(long int* out_count)const = 0;


		/**********************************************************************//**
		 * @brief	获取当前数据库数据集索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/02
		 * @param	beg_index	要获取的数据集的起始索引号(从0开始)
		 * @param	count		要获取的数据集索引数
		 * @param	out_list	传出索引范围内的数据集索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_index_list_by_range(int beg_index,int count,
														  us_dataset_index_list* out_list
														  )const = 0;


		/**********************************************************************//**
		 * @brief	判断数据集的meta记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/29
		 * @return	存在返回ture,不存在返回false.
		 *************************************************************************/
		virtual bool has_record(const us_uuid& uuid)const ;

		/**********************************************************************//**
		 * @brief	判断数据集的meta记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/29
		 * @return	存在返回ture,不存在返回false.
		 *************************************************************************/
		virtual bool has_record(const us_ustring& name)const;

	public:
		/**********************************************************************//**
		 * @brief	获取一个基于SQLite的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
		 * @param	filename	数据库文件路径.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_dataset_manager* get_manager_by_sqlite(const char* filename);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
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
		static us_dataset_manager* get_manager_by_mysql(const char *host,
														const char *user,
														const char *passwd,
														const char *db = "unispace",
														unsigned int port = 3306,
														const char *unix_socket = 0,
														unsigned long clientflag = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		  * @param	pmysql		已连接数据库的连接对象.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_dataset_manager* get_manager_by_mysql(void* pmysql);


		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_dataset_manager* get_manager_by_mongodb(const char* host,
														  unsigned short port,
														  const char* user = 0,
														  const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		 * @param	client		已连接数据库的client.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_dataset_manager* get_manager_by_mongodb(void* client);

		/**********************************************************************//**
		 * @brief	释放影像管理器.
		 *			因为已经将析构函数设置为protected了，所有提供此函数来释放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/20
		 *************************************************************************/
		static void destory(us_dataset_manager* mgr);
	};
}

#endif //! __US_DATASET_MANAGER_HPP__
