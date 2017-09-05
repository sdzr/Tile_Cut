/**********************************************************************//**
 * @file us_image_manager_by_sqlite.hpp
 *
 * 定义 the us_image_manager_by_sqlite 类.
 *************************************************************************/
#ifndef __US_IMAGE_MANAGER_BY_SQLITE_HPP__
#define __US_IMAGE_MANAGER_BY_SQLITE_HPP__

#ifndef __US_IMAGE_MANAGER_HPP__
#include "../us_image_manager.hpp"
#endif

struct sqlite3;

namespace unispace
{
	/**********************************************************************//**
	 * @brief	基于SQLite3数据库的影像数据管理类.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/5/17
	 *************************************************************************/
	class us_image_manager_by_sqlite :
		public us_image_manager
	{
		us_image_manager_by_sqlite(const us_image_manager_by_sqlite&);
		us_image_manager_by_sqlite& operator=(const us_image_manager_by_sqlite&);
	private:
		/** 给予基类访问权限 */
		friend class us_image_manager;

		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	filename SQLite3文件路径.
		 *************************************************************************/
		us_image_manager_by_sqlite(const char* filename);

		/** sqlite数据库操作句柄 */
		sqlite3* sqlite;
	public:
		/** 析构函数 */
		virtual ~us_image_manager_by_sqlite();
		
		/**********************************************************************//**
		 * @brief	添加影像元数据
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	meta		影像的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT add_image_meta(const us_image_basic_meta& meta)const;

		/**********************************************************************//**
		 * @brief	查找影像文件uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/19
		 * @param	img_url		影像的路径.
		 * @param	[out] out_uuid	如果非NULL，传出数据库中影像文件的uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_uuid(const us_ustring& img_url,
										  us_uuid* out_uuid)const;

		/**********************************************************************//**
		 * @brief	查找影像文件的路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/19
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
		 * @date	2016/3/16
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_only_image_meta(const us_uuid& img_uuid,
										  us_image_basic_meta* out_meta)const;


		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	image_path		影像文件的路径(原始数据存储位置).
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_ustring& image_path,
										  us_image_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	查找影像文件元数据.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/3/16
		 * @param	img_uuid		影像的 uuid.
		 * @param	[out] out_meta	如果非NULL，传出影像文件的meta信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT find_image_meta(const us_uuid& img_uuid,
										  us_image_basic_meta* out_meta)const;

		/**********************************************************************//**
		 * @brief	删除的影像的 meta 信息，通过影像的 uuid.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	img_uuid	影像的 uuid.
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT delete_image_meta(const us_uuid& img_uuid)const;

		/**********************************************************************//**
		 * @brief	更新指定影像的 meta 信息.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	meta	待更新meta的影像的 meta .
		 * @return	A DM_RESULT.
		 *************************************************************************/
		virtual DM_RESULT update_image_meta(const us_image_basic_meta& meta)const;

		/**********************************************************************//**
		 * @brief	获取网格影像信息（包含四角局部坐标、影像内容等）
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/5/17
		 * @param	meta		影像的 meta 信息.
		 * @param	grid_id		网格的ID.
		 * @param	[out] out_image_uv	如果不是null，传出影像在网格中的UV等信息.
		 * @return	A DM_RESULT.
		 *************************************************************************/

		virtual DM_RESULT get_grid_image_info(const us_image_basic_meta& meta,
											  const us_grid_id& grid_id,
											  us_grid_uv* out_image_uv)const;

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

#endif //!__US_IMAGE_MANAGER_BY_SQLITE_HPP__