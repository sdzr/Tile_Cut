/**********************************************************************//**
 * @file us_image_manager.hpp
 *
 * Declares the image manager class.
 *************************************************************************/

#ifndef __US_IMAGE_MANAGER_HPP__
#define __US_IMAGE_MANAGER_HPP__

#ifndef __US_DATA_MANAGER_HPP__
#include "us_data_manager.hpp"
#endif

#include <stdint.h>
#include <string>

namespace unispace
{

	class us_ustring;
	class us_grid_uv;	// 网格UV
	class us_image_basic_meta;	//影像meta
	class us_uuid;		// uuid
	class us_grid_id;	// 网格id
	class us_image_index_list;	// 影像索引列表

	/**********************************************************************//**
	 * @brief	影像数据管理类.
	 *			只对影像数据进行管理，不对其进行处理操作.<br>
	 *			影像数据的处理操作，使用Data Process模块中的相关方法进行.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/3/22
	 *************************************************************************/

	class _US_DATA_MANAGER_DLL us_image_manager
	{
	protected:
		/** 用于转换us_image_basic_meta到二进制 */
		static bool meta_to_msgpack(const us_image_basic_meta& in, std::string& out);
		static bool msgpack_to_meta(const std::string& in, us_image_basic_meta& out);
		static bool msgpack_to_meta(const char* in_data, size_t in_size, us_image_basic_meta& out);

		/**********************************************************************//**
		 * @brief	默认构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 *************************************************************************/
		us_image_manager(){};

		/**********************************************************************//**
		 * @brief	默认析构函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 *************************************************************************/
		virtual ~us_image_manager(){};

	private:
		/**********************************************************************//**
		 * @brief	拷贝构造函数
		 *************************************************************************/
		us_image_manager(const us_image_manager&) = delete;
		void operator=(const us_image_manager&) = delete;
	public:

		/**********************************************************************//**
		 * @brief	添加影像元数据
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_image_meta(const us_image_basic_meta& meta)const =0;

		/**********************************************************************//**
		 * @brief	查找影像文件uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
		 * @param	img_url		影像的路径.
		 * @param	[out] out_uuid	如果非NULL，传出数据库中影像文件的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_uuid(const us_ustring& img_url,
										  us_uuid* out_uuid)const =0;

		/**********************************************************************//**
		 * @brief	查找影像文件的路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_url	如果非NULL，传出影像文件的路径.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_url(const us_uuid& img_uuid,
										  us_ustring* out_url)const =0;

		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	image_path		影像文件的路径(原始数据存储位置).
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_ustring& image_path,
										  us_image_basic_meta* out_meta)const = 0;

		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_uuid& img_uuid,
										  us_image_basic_meta* out_meta)const = 0;

		/**********************************************************************//**
		 * @brief	删除的影像的 meta 信息，通过影像的 uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	img_uuid	影像的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_image_meta(const us_uuid& img_uuid)const = 0;

		/**********************************************************************//**
		 * @brief	删除的影像的 meta 信息，通过影像的 uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/12
		 * @param	img_url		影像的路径.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_image_meta(const us_ustring& img_url)const;

		/**********************************************************************//**
		 * @brief	更新指定影像的 meta 信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	meta	待更新meta的影像的 meta .
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_image_meta(const us_image_basic_meta& meta)const = 0;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的影像数.
		 * 			这里假设long int是32位的，这里没有用无符号类型，传出的数值最大为20亿多。
		 * 			20亿已经是一个很大的数据量了，如果到了这个数据量，应该考虑分库。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/3
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_image_count(long int* out_count)const = 0;

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
												  us_image_index_list* out_index)const= 0;

		/**********************************************************************//**
		 * @brief	判断影像的meta记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/4
		 * @return	存在返回ture,不存在返回false.
		 *************************************************************************/
		virtual bool has_record(const us_uuid& uuid)const ;

		/**********************************************************************//**
		 * @brief	判断影像的meta记录是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/4
		 * @return	存在返回ture,不存在返回false.
		 *************************************************************************/
		virtual bool has_record(const us_ustring& url)const;

	public:

		/**********************************************************************//**
		 * @brief	获取一个基于SQLite的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
		 * @param	filename	数据库文件路径.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_image_manager* get_manager_by_sqlite(const char* filename);

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
		static us_image_manager* get_manager_by_mysql(const char *host,
													  const char *user,
													  const char *passwd,
													  const char *db = "unispace",
													  unsigned int port = 3306,
													  const char *unix_socket = 0,
													  unsigned long clientflag = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/02
		  * @param	pmysql		已连接数据库的连接对象.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_image_manager* get_manager_by_mysql(void* pmysql);


		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_image_manager* get_manager_by_mongodb(const char* host,
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
		static us_image_manager* get_manager_by_mongodb(void* client);

		/**********************************************************************//**
		 * @brief	释放影像管理器.
		 *			因为已经将析构函数设置为protected了，所有提供此函数来释放.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/6/20
		 *************************************************************************/
		static void destory(us_image_manager* mgr);

	};
}

#endif // __US_IMAGE_MANAGER_HPP__
