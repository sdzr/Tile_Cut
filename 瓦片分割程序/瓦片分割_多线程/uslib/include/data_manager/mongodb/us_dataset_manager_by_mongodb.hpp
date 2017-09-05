#ifndef __US_DATASET_MANAGER_BY_MONGODB_HPP__
#define __US_DATASET_MANAGER_BY_MONGODB_HPP__

#ifndef __US_DATASET_MANAGER_HPP__
#include "../us_dataset_manager.hpp"
#endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;


namespace unispace
{

	/**********************************************************************//**
	 * @brief	基于MySQL数据库的数据集管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/8/30
	 *************************************************************************/
	class us_dataset_manager_by_mongodb :
		public us_dataset_manager
	{
				/** 给予基类访问权限 */
		friend class us_dataset_manager;

		/** mongodb数据库对象 */
		mongoc_client_t* mog_client;
		/** mongodb数据库集合 */
		mongoc_collection_t* collection;

		/**********************************************************************//**
		 * @brief	构造函数
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 *************************************************************************/
		us_dataset_manager_by_mongodb(const char* host, unsigned short port,
									const char* user = 0,const char* passwd = 0);
		/**********************************************************************//**
		 * @brief	构造函数
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_dataset_manager_by_mongodb(mongoc_client_t* client = 0);
		/** 拷贝构造 */
		us_dataset_manager_by_mongodb(const us_dataset_manager_by_mongodb&);
		/** 赋值重载 */
		us_dataset_manager_by_mongodb& operator=(const us_dataset_manager_by_mongodb&);
	public:
		virtual ~us_dataset_manager_by_mongodb();

		/**********************************************************************//**
		* @brief	添加数据集到数据库.
		* @author	yimin.liu@unispace-x.com
		* @date		2016/8/22
		* @param	meta		数据集meta信息.
		* @param	update_ctime是否更新创建时间.
		* @return	A DM_RESULT.
		*************************************************************************/
		virtual DM_RESULT add_dataset(us_dataset_basic_meta& meta,
									  bool update_ctime = true)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	uuid		数据集的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_uuid& uuid)const;

		/**********************************************************************//**
		 * @brief	从数据库中删除数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	name		数据集的名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_dataset(const us_ustring& name)const;

		/**********************************************************************//**
		 * @brief	查找数据集名称.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	uuid			数据集的 uuid.
		 * @param	[out] out_name	如果非NULL，传出数据集名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_name(const us_uuid& uuid,
											us_ustring* out_name)const;

		/**********************************************************************//**
		 * @brief	查找数据集UUID.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	name			影像的 uuid数据集的名称.
		 * @param	[out] out_uuid	如果非NULL，传出数据集UUID.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset_uuid(const us_ustring& name,
											us_uuid* out_uuid)const;



		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	uuid		数据集的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_uuid& uuid,
									   us_dataset_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	查找数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	name		数据集的名称.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_dataset(const us_ustring& name,
									   us_dataset_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	更新数据集.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	meta			数据集meta信息.
		 * @param	not_up_uuidset	是否不更新uuidset，默认为是.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_dataset(us_dataset_basic_meta& meta,
										 bool not_up_uuidset = true)const;

		/**********************************************************************//**
		 * @brief	获取当前数据库总的数据集数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	out_count	传出总的影像数.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_count(long int* out_count)const;


		/**********************************************************************//**
		 * @brief	获取当前数据库数据集索引列表.
		 * 			获取到的是根据起止索引数(SQL表中的行号)影像的路径和uuid的索引。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/22
		 * @param	beg_index	要获取的数据集的起始索引号(从0开始)
		 * @param	count		要获取的数据集索引数
		 * @param	out_index	传出索引范围内的数据集索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_dataset_index_list_by_range(int beg_index, int count,
														  us_dataset_index_list* out_list
														  )const;
	};

}
#endif //! __US_DATASET_MANAGER_BY_MONGODB_HPP__
