#ifndef __US_WMTS_THEME_BASIC_META_HPP__
#define __US_WMTS_THEME_BASIC_META_HPP__

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif

#ifndef __US_UUID_HPP__
#include "util/uuid/us_uuid.hpp"
#endif // !__US_UUID_HPP__

#include <set>

namespace unispace 
{
	class us_wmts_theme_basic_meta {
	public:
		us_ustring	m_name;		///< 主题名称
		us_uuid		m_uuid;		///< 主题uuid
		us_ustring	m_other;	///< 其他
		us_ustring	m_description;	///< xml描述
		std::set<us_uuid>	m_layerset;	///< 包含的wmts layer 集合
		bool		m_auto_run;	// 弃用
	};

}


#endif // !__US_WMTS_THEME_BASIC_META_HPP__
