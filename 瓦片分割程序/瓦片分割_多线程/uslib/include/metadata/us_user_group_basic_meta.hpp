/**********************************************************************//**
 * @file us_user_group_basic_meta.hpp
 *
 * 定义us_user_group_basic_meta类.
 *************************************************************************/

#ifndef __US_USER_GROUP_BASIC_META_HPP__
#define __US_USER_GROUP_BASIC_META_HPP__

#ifndef __US_STRING_HPP__
#include <util/common/us_string.hpp>
#endif // !__US_STRING_HPP__

#ifndef __US_UUID_HPP__
#include <util/uuid/us_uuid.hpp>
#endif

#include <vector>

namespace unispace
{
	/**********************************************************************//**
	 * @class	us_user_group_basic_meta
	 * @brief	用户组基本元数据.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/5/15
	 *************************************************************************/
	struct us_user_group_basic_meta
	{
		us_uuid		m_id;			///< 组ID
		us_ustring	m_group_name;	

		std::vector<us_ustring>	m_user_set;
		std::vector<us_ustring>	m_dataset_set;

		uint32_t	m_ds_perm_bits;
		bool		m_is_private;

	};
}

#endif //!__US_USER_GROUP_BASIC_META_HPP__
