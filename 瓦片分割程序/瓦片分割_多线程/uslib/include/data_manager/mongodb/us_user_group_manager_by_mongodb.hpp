#ifndef __US_USER_GROUP_MANAGER_BY_MONGODB_HPP__
#define __US_USER_GROUP_MANAGER_BY_MONGODB_HPP__


#ifndef __US_USER_GROUP_MANAGER_HPP__
#include "us_user_group_manager.hpp"
#endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;

namespace unispace
{

	class us_user_group_manager_by_mongodb :
		public us_user_group_manager
	{
		/** 给予基类访问权限 */
		friend class us_user_group_manager;

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
		us_user_group_manager_by_mongodb(const char* host,
			unsigned short port,
			const char* user_group = 0,
			const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_user_group_manager_by_mongodb(mongoc_client_t* client);
	public:
		/** 析构函数 */
		virtual ~us_user_group_manager_by_mongodb();

		/**********************************************************************//**
		 * @brief	添加user_group信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_user_group_meta(const us_user_group_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	从数据库删除一条user_group记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid	user_group的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_user_group(const us_uuid& uuid);

		/**********************************************************************//**
		 * @brief	从数据库删除一条user_group记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name	user_group的name.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_user_group(const us_ustring& name);

		/**********************************************************************//**
		 * @brief	查找user_group名对应id.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name		user_group的用户组名.
		 * @param	[out] out_uuid	如果非NULL，传出uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_group_uuid(const us_ustring& name,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找用户组ID对应的用户组名.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid		user_group的 uuid.
		 * @param	[out] out_name	如果非NULL，传出user_group用户组名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_group_name(const us_uuid& uuid,
										  us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	从数据库查找user_group记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	uuid		user_group信息的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的user_group信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_group(const us_uuid& uuid, us_user_group_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	从数据库查找user_group记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	name		user_group信息的name.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的user_group信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_user_group(const us_ustring& name, us_user_group_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	获取当前数据库总的user_group数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/05/15
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_user_group_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库user_group索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/05/15
		 * @param	beg_index	要获取的user_group起始索引号(从0开始)
		 * @param	count		要获取的user_group索引数
		 * @param	out_index	传出索引范围内的user_group索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_user_group_list_by_range(int beg_index, int count,
			us_user_group_index_list* out_index)const;
	};

}

#endif // !__US_USER_GROUP_MANAGER_BY_MONGODB_HPP__
