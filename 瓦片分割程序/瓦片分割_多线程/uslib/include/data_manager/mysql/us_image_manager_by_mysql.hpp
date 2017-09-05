#ifndef __US_IMAGE_MANAGER_BY_MYSQL_HPP__
#define __US_IMAGE_MANAGER_BY_MYSQL_HPP__

#ifndef __US_IMAGE_MANAGER_HPP__
#include "data_manager/us_image_manager.hpp"
#endif

struct st_mysql;

namespace unispace
{
	/**********************************************************************//**
	 * @brief	基于MySQL数据库的影像数据管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/5/31
	 *************************************************************************/
	class us_image_manager_by_mysql :
		public us_image_manager
	{
	protected:
		/** 拷贝构造 */
		us_image_manager_by_mysql(const us_image_manager_by_mysql&);
		/** 赋值重载 */
		us_image_manager_by_mysql& operator=(const us_image_manager_by_mysql&);
		/** 给予基类访问权限 */
		friend class us_image_manager;
		
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
		us_image_manager_by_mysql(const char *host,
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
		us_image_manager_by_mysql(st_mysql* pmysql);

		st_mysql* mysql;
	public:
		/** 析构函数 */
		virtual ~us_image_manager_by_mysql();

		/**********************************************************************//**
		 * @brief	添加影像元数据
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_image_meta(const us_image_basic_meta& meta)const;

		/**********************************************************************//**
		 * @brief	查找影像文件uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	img_url		影像的路径.
		 * @param	[out] out_uuid	如果非NULL，传出数据库中影像文件的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_uuid(const us_ustring& img_url,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找影像文件的路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_url	如果非NULL，传出影像文件的路径.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_url(const us_uuid& img_uuid,
										  us_ustring* out_url)const;

		/**********************************************************************//**
		 * @brief	通过影像uuid查找影像文件元数据.
		 *			不会修改传出Meta中的影像路径信息。仅从数据库中取出数据放入。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_only_image_meta(const us_uuid& img_uuid,
										  us_image_basic_meta* out_meta)const;


		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	image_path		影像文件的路径(原始数据存储位置).
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_ustring& image_path,
										  us_image_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_uuid& img_uuid,
										  us_image_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	删除的影像的 meta 信息，通过影像的 uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	img_uuid	影像的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_image_meta(const us_uuid& img_uuid)const;

		/**********************************************************************//**
		 * @brief	更新指定影像的 meta 信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/31
		 * @param	meta	待更新meta的影像的 meta .
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_image_meta(const us_image_basic_meta& meta)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的影像数.
		 * 			这里假设long int是32位的，这里没有用无符号类型，传出的数值最大为20亿多。
		 * 			20亿已经是一个很大的数据量了，如果到了这个数据量，应该考虑分库。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/3
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_image_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库影像索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/6
		 * @param	beg_index	要获取的影像的起始索引号(从0开始)
		 * @param	count		要获取的影像索引数
		 * @param	out_index	传出索引范围内的影像索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_image_list_by_range(int beg_index, int count,
												  us_image_index_list* out_index)const;
	};

}

#endif //! __US_IMAGE_MANAGER_BY_MYSQL_HPP__
