#ifndef __US_DATA_MANAGER_HPP__
#define __US_DATA_MANAGER_HPP__

// windows下DLL导出
#if defined(_WIN32)		// WIN32平台才导出或导入

#if defined(_US_DATA_MANAGER_LIB) // 本工程中才导出(引用此项目的程序需定义此宏才导入)

#if defined(_WINDLL) && defined(_US_DATA_MANAGER_DLL)	// 是_WINDLL项目且定义了_US_UTIL_DLL才导出
#undef _US_DATA_MANAGER_DLL
#define _US_DATA_MANAGER_DLL __declspec(dllexport)
#else
#define _US_DATA_MANAGER_DLL __declspec(dllimport)
#endif	// _WINDLL + _US_DATA_MANAGER_LIB

#endif  // _US_DATA_MANAGER_LIB

#ifndef _US_DATA_MANAGER_DLL
#define _US_DATA_MANAGER_DLL	// 如果没有定义，那就定义
#endif

#else
#define _US_DATA_MANAGER_DLL
#endif	// _WIN32


namespace unispace
{
	/** Data Manager的各个操作返回的结果 */
	enum DM_RESULT
	{
		SUCCESS             = 0,	///< 成功
		ALREADY_EXISTS      = 1,	///< 已存在
		DATABASE_EXCEPTIONS = 2,	///< 数据库异常
		META_EXCEPTION      = 10,	///< meta信息异常
		GRID_ID_INVALID     = 11,	///< 网格ID无效
		PROGRAM_EXCEPTION	= 20,	///< 程序异常
		PARAMETER_INVALID	= 30,	///< 参数无效
		GET_RESULT_FAILD	= 31,	///< 获取结果失败
		DATA_PARSE_FAILD	= 32,	///< 数据解析失败
		NOT_FOUND           = 100,	///< 没有找到
		UNKNOWN_ERROR		= 101	///< 未知错误	
	};


}


#if !defined(__US_IMAGE_MANAGER_HPP__) &&\
	!defined(__US_DATASET_MANAGER_HPP__) &&\
	!defined(__US_IMAGE_INDEX_LIST_HPP__) &&\
	!defined(__US_DATASET_INDEX_LIST_HPP__) &&\
	!defined(__US_WMTS_INDEX_LIST_HPP__) &&\
	!defined(__US_WMTS_MANAGER_HPP__) &&\
	!defined(__US_USER_INDEX_LIST_HPP__) &&\
	!defined(__US_USER_MANAGER_HPP__) &&\
	!defined(__US_USER_GROUP_INDEX_LIST_HPP__) &&\
	!defined(__US_USER_GROUP_MANAGER_HPP__) &&\
	!defined(__US_DATASET_AUTH_INDEX_LIST_HPP__) &&\
	!defined(__US_DATASET_AUTH_MANAGER_HPP__) &&\
	!defined(__US_WMTS_THEME_MANAGER_HPP__) &&\
	!defined(__US_WMTS_THEME_INDEX_LIST_HPP__)

#include "us_image_manager.hpp"
#include "us_dataset_manager.hpp"
#include "us_image_index_list.hpp"
#include "us_dataset_index_list.hpp"
#include "us_wmts_index_list.hpp"
#include "us_wmts_manager.hpp"
#include "us_wmts_theme_manager.hpp"
#include "us_wmts_theme_index_list.hpp"

#include "us_user_index_list.hpp"
#include "us_user_manager.hpp"
#include "us_user_group_index_list.hpp"
#include "us_user_group_manager.hpp"
#include "us_dataset_auth_index_list.hpp"
#include "us_dataset_auth_manager.hpp"

#else
namespace unispace{
	class us_image_manager;
	class us_dataset_manager;
	class us_wmts_manager;
	class us_wmts_theme_manager;

	class us_user_manager;
	class us_user_group_manager;
	class us_dataset_auth_manager;
}

#endif

// 会有线程安全问题
#define __ONLY_SGE_G__
#ifdef __ONLY_SGE_G__

namespace unispace 
{
	
	/**********************************************************************//**
	 * @brief	数据管理类.
	 *			仅仅用于获取共用连接对象的影像和数据集管理对象。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/24
	 *************************************************************************/
	class _US_DATA_MANAGER_DLL us_data_manager{
	public:
		/**********************************************************************//**
		 * @brief	获取影像管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/28
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		us_image_manager* get_image_manager(){ return m_imgmgr; }
		/**********************************************************************//**
		 * @brief	获取数据集管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/28
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		us_dataset_manager* get_dataset_manager(){ return m_dsetmgr; }

		/**********************************************************************//**
		 * @brief	获取wmts管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/11/16
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		us_wmts_manager* get_wmts_manager() { return m_wmtsmgr; }

		us_wmts_theme_manager* get_wmts_theme_manager() { return m_wmts_theme_mgr; }

		us_user_manager* get_user_manager() { return m_usermgr; }
		us_user_group_manager* get_user_group_manager() { return m_user_group_mgr; }
		us_dataset_auth_manager* get_user_dataset_auth_manager() { return m_dset_auth_mgr; }

		/**********************************************************************//**
		 * @brief	获取一个基于SQLite的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/27
		 * @param	filename	数据库文件路径.
		 * @return	成功返回管理器地址，失败返回NULL.
		 *************************************************************************/
		static us_data_manager* get_manager_by_sqlite(const char* filename);

		/**********************************************************************//**
		 * @brief	获取一个基于MySQL的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/27
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
		static us_data_manager* get_manager_by_mysql(const char *host,
													  const char *user,
													  const char *passwd,
													  const char *db = "unispace",
													  unsigned int port = 3306,
													  const char *unix_socket = 0,
													  unsigned long clientflag = 0);

		/**********************************************************************//**
		 * @brief	获取一个基于MongoDB的管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/27
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		static us_data_manager* get_manager_by_mongodb(const char* host,
														  unsigned short port,
														  const char* user = 0,
														  const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	释放管理器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/27
		 *************************************************************************/
		static void destory(us_data_manager* mgr);

	private:
		// 构造函数
		us_data_manager(){}

		us_dataset_manager*	m_dsetmgr;
		us_image_manager*	m_imgmgr;
		us_wmts_manager*	m_wmtsmgr;
		us_wmts_theme_manager* m_wmts_theme_mgr;

		us_user_manager*			m_usermgr;
		us_user_group_manager*		m_user_group_mgr;
		us_dataset_auth_manager*	m_dset_auth_mgr;
	};


}

#endif //!__ONLY_SGE_G__


#endif //!__US_DATA_MANAGER_HPP__
