#ifndef __US_IMAGE_MANAGER_BY_MONGODB_HPP__
#define __US_IMAGE_MANAGER_BY_MONGODB_HPP__

#ifndef __US_IMAGE_MANAGER_HPP__
#include "data_manager/us_image_manager.hpp"
#endif

//struct _mongoc_client_t;
typedef struct _mongoc_client_t mongoc_client_t;

//struct _mongoc_collection_t;
typedef struct _mongoc_collection_t mongoc_collection_t;


namespace unispace
{

	/**********************************************************************//**
	 * @brief	基于MongoDB数据库的影像数据管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/6/30
	 *************************************************************************/
	class us_image_manager_by_mongodb :
		public us_image_manager
	{
		/** 给予基类访问权限 */
		friend class us_image_manager;

		/** mongodb数据库对象 */
		mongoc_client_t* mog_client;
		/** mongodb数据库集合 */
		mongoc_collection_t* collection;

		/**********************************************************************//**
		 * @brief	构造函数
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/7/01
		 * @param	host		mongodb数据库主机.
		 * @param	port		mongodb数据库端口.
		 * @param	user		mongodb数据库用户名.
		 * @param	passwd		mongodb数据库密码.
		 *************************************************************************/
		us_image_manager_by_mongodb(const char* host,unsigned short port,
									const char* user = 0,const char* passwd = 0);
		/**********************************************************************//**
		 * @brief	构造函数
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/8/23
		 * @param	client		已连接数据库的client.
		 *************************************************************************/
		us_image_manager_by_mongodb(mongoc_client_t* client);
		/** 拷贝构造 */
		us_image_manager_by_mongodb(const us_image_manager_by_mongodb&);
		/** 赋值重载 */
		us_image_manager_by_mongodb& operator=(const us_image_manager_by_mongodb&);
	public:
		virtual ~us_image_manager_by_mongodb();

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

#endif //!__US_IMAGE_MANAGER_BY_MONGODB_HPP__
