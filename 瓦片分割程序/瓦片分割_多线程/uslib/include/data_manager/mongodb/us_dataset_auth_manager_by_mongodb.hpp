#ifndef __US_DATASET_AUTH_MANAGER_BY_MONGODB_HPP__
#define __US_DATASET_AUTH_MANAGER_BY_MONGODB_HPP__


#ifndef __US_DATASET_AUTH_MANAGER_HPP__
#include "us_dataset_auth_manager.hpp"
#endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;

namespace unispace
{

	class us_dataset_auth_manager_by_mongodb :
		public us_dataset_auth_manager
	{
		/** 给予基类访问权限 */
		friend class us_dataset_auth_manager;

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
		us_dataset_auth_manager_by_mongodb(const char* host,
			unsigned short port,
			const char* user = 0,
			const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_dataset_auth_manager_by_mongodb(mongoc_client_t* client);
	public:
		/** 析构函数 */
		virtual ~us_dataset_auth_manager_by_mongodb();

		/**********************************************************************//**
		 * @brief	添加dataset_auth信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_dataset_auth_meta(const us_dataset_auth_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	从数据库删除一条dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	uuid	dataset_auth的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset_auth(const us_uuid& uuid);

		/**********************************************************************//**
		 * @brief	从数据库删除一条dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	name	dataset_auth的name.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset_auth(const us_ustring& name);

		/**********************************************************************//**
		 * @brief	查找dataset_auth名对应id.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	name		dataset_auth的数据集认证名.
		 * @param	[out] out_uuid	如果非NULL，传出uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth_uuid(const us_ustring& name,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找数据集认证ID对应的数据集认证名.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	uuid		dataset_auth的 uuid.
		 * @param	[out] out_name	如果非NULL，传出dataset_auth数据集认证名.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth_name(const us_uuid& uuid,
										  us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	从数据库查找dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	uuid		dataset_auth信息的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的dataset_auth信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth(const us_uuid& uuid, us_dataset_auth_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	从数据库查找dataset_auth记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	name		dataset_auth信息的name.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的dataset_auth信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_auth(const us_ustring& name, us_dataset_auth_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	获取当前数据库总的dataset_auth数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/04/26
		 * @param	out_count	传出总的dataset auth.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_auth_count(long int* out_count)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库dataset_auth索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/04/26
		 * @param	beg_index	要获取的dataset_auth起始索引号(从0开始)
		 * @param	count		要获取的dataset_auth索引数
		 * @param	out_index	传出索引范围内的dataset_auth索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_auth_list_by_range(int beg_index, int count,
			us_dataset_auth_index_list* out_index)const;
	};

}

#endif // !__US_DATASET_AUTH_MANAGER_BY_MONGODB_HPP__
