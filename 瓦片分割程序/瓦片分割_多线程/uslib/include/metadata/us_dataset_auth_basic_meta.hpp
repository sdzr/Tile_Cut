/**********************************************************************//**
 * @file us_dataset_auth_basic_meta.hpp
 *
 * 定义us_dataset_auth_basic_meta类.
 *************************************************************************/

#ifndef __US_DATASET_AUTH_BASIC_META_HPP__
#define __US_DATASET_AUTH_BASIC_META_HPP__

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
	 * @class	us_dataset_auth_basic_meta
	 * @brief	用户基本元数据.
	 * 			保存了用户的一些基本信息，以及需要存入数据库中的字段值.
	 * @author	yimin.liu@unispace-x.com
	 * @date	2017/4/26
	 *************************************************************************/
	struct us_dataset_auth_basic_meta
	{
		us_uuid		m_id;			///< ID
		us_ustring	m_dset_auth_name;
		us_ustring	m_owner_id;

		std::vector<us_ustring>	m_group_set;
		std::map<us_ustring,uint32_t>	m_ds_perm_map;

		uint32_t	m_ou_perm_bits;
		bool		m_is_private;
	};
}

#endif //!__US_DATASET_AUTH_BASIC_META_HPP__
