#ifndef __US_WMTS_THEME_MANAGER_BY_MONGODB_HPP__
#define __US_WMTS_THEME_MANAGER_BY_MONGODB_HPP__

#ifndef __US_WMTS_THEME_MANAGER_HPP__
#include "data_manager/us_wmts_theme_manager.hpp"
#endif // !__US_WMTS_THEME_MANAGER_HPP__

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;


namespace unispace
{

	class us_wmts_theme_manager_by_mongodb :
		public us_wmts_theme_manager
	{
	private:
		/** 给予基类访问权限 */
		friend class us_wmts_theme_manager;
		/** mongodb数据库对象 */
		mongoc_client_t* mog_client;
		/** mongodb数据库集合 */
		mongoc_collection_t* collection;
	public:
		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 *************************************************************************/
		us_wmts_theme_manager_by_mongodb(const char* host,
			unsigned short port,
			const char* user = 0,
			const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_wmts_theme_manager_by_mongodb(mongoc_client_t* client);
		/** 析构函数 */
		virtual ~us_wmts_theme_manager_by_mongodb();
	public:

		/**********************************************************************//**
		 * @brief	添加wmts主题到数据库.
		 *			如果已经存在，？？？？
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/01
		 * @param	meta			wmts主题meta信息.
		 * @param	update_ctime	是否更新创建时间.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_wmts_theme(const us_wmts_theme_basic_meta& meta,
			bool update_ctime = true)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除wmts主题.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	uuid		wmts主题的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_wmts_theme(const us_uuid& uuid)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除wmts主题.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	name		wmts主题的名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_wmts_theme(const us_ustring& name)const;

		/**********************************************************************//**
		 * @brief	查找wmts主题名称.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	uuid			wmts主题的 uuid.
		 * @param	[out] out_name	如果非NULL，传出wmts主题名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_theme_name(const us_uuid& uuid,
			us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	查找wmts主题UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	name			影像的 uuidwmts主题的名称.
		 * @param	[out] out_uuid	如果非NULL，传出wmts主题UUID.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_theme_uuid(const us_ustring& name,
			us_uuid* out_uuid)const;



		/**********************************************************************//**
		 * @brief	查找wmts主题.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	uuid		wmts主题的uuid.
		 * @param	[out] out_meta	如果非NULL，传出wmts主题的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_theme(const us_uuid& uuid,
			us_wmts_theme_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	查找wmts主题.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	name		wmts主题的名称.
		 * @param	[out] out_meta	如果非NULL，传出wmts主题的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts_theme(const us_ustring& name,
			us_wmts_theme_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	更新wmts主题.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	meta			wmts主题meta信息.
		 * @param	not_up_uuidset	是否不更新uuidset，默认为是.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_wmts_theme(const us_wmts_theme_basic_meta& meta,
			bool not_up_uuidset = true)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的wmts主题数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_wmts_theme_count(long int* out_count)const;


		/**********************************************************************//**
		 * @brief	获取当前数据库wmts主题索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/12/13
		 * @param	beg_index	要获取的wmts主题的起始索引号(从0开始)
		 * @param	count		要获取的wmts主题索引数
		 * @param	out_list	传出索引范围内的wmts主题索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_wmts_theme_index_list_by_range(int beg_index, int count,
			us_wmts_theme_index_list* out_list
		)const;
	};

}
#endif // !__US_WMTS_THEME_MANAGER_BY_MONGODB_HPP__
