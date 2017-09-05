#ifndef __US_WMTS_MANAGER_BY_MONGODB_HPP__
#define __US_WMTS_MANAGER_BY_MONGODB_HPP__


#ifndef __US_WMTS_MANAGER_HPP__
#include "us_wmts_manager.hpp"
#endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;

namespace unispace
{

	class us_wmts_manager_by_mongodb :
		public us_wmts_manager
	{
		/** 给予基类访问权限 */
		friend class us_wmts_manager;

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
		us_wmts_manager_by_mongodb(const char* host,
			unsigned short port,
			const char* user = 0,
			const char* passwd = 0);

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_wmts_manager_by_mongodb(mongoc_client_t* client);
	public:
		/** 析构函数 */
		virtual ~us_wmts_manager_by_mongodb();

		/**********************************************************************//**
		 * @brief	添加wmts信息到数据库
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_wmts_meta(const us_wmts_basic_meta& meta);

		/**********************************************************************//**
		 * @brief	从数据库删除一条wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	uuid	wmts的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_wmts(const us_uuid& uuid);

		/**********************************************************************//**
		 * @brief	从数据库删除一条wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
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
		 * @date	2016/10/12
		 * @param	uuid		wmts信息的uuid.
		 * @param	[out] out_meta	如果非NULL，传出数据库中对应的wmts信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_wmts(const us_uuid& uuid, us_wmts_basic_meta* out_meta);

		/**********************************************************************//**
		 * @brief	从数据库查找wmts记录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
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
		 * @date	2016/10/12
		 * @param	beg_index	要获取的wmts起始索引号(从0开始)
		 * @param	count		要获取的wmts索引数
		 * @param	out_index	传出索引范围内的wmts索引.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT get_wmts_list_by_range(int beg_index, int count,
			us_wmts_index_list* out_index)const;
	};

}

#endif // !__US_WMTS_MANAGER_BY_MONGODB_HPP__
