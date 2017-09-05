/**********************************************************************//**
 * @file us_user_basic_meta.hpp
 *
 * 定义us_user_basic_meta类.
 *************************************************************************/

#ifndef __US_USER_BASIC_META_HPP__
#define __US_USER_BASIC_META_HPP__

#ifndef __US_STRING_HPP__
#include <util/common/us_string.hpp>
#endif // !__US_STRING_HPP__

#ifndef __US_UUID_HPP__
#include <util/uuid/us_uuid.hpp>
#endif

#include <vector>
#include <map>

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_user_basic_meta
	 * @brief	用户基本元数据.
	 * 			保存了用户的一些基本信息，以及需要存入数据库中的字段值.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/4/26
	 *************************************************************************/
	struct us_user_basic_meta
	{
		us_uuid		m_id;			///< 用户ID
		us_ustring	m_username;		///< 用户名
		us_ustring	m_password;		///< 密码
		us_ustring	m_group_id;		///< 组ID
		us_ustring	m_descr_info;	///< 描述信息
		uint32_t	m_role_type;	///< 角色类型
		uint32_t	m_opp_bits;		///< 用户权限位
		uint32_t	m_class_level;	///< 分类层级

		std::vector<us_ustring>	m_group_set;	///< 组集
		std::map<us_ustring, uint32_t> m_dataset_map; ///< 数据集集合
	};
}

#endif //!__US_USER_BASIC_META_HPP__
