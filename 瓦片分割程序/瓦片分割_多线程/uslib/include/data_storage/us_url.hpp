#ifndef __US_URL_HPP__
#define __US_URL_HPP__


#include <string>
#include <stdexcept>

#include "us_path.hpp"

#ifndef __US_STRING_HPP__
#include "util/common/us_string.hpp"
#endif

#ifndef __US_DATA_STORAGE_HPP__
#include "us_data_storage.hpp"
#endif

/**
 * @addtogroup url
 * @brief 处理RFC 3986说明
 *
 * @{
 */

 /**
  * @class us_url us_url.hpp
  * @brief handles URLs
  *
  * 根据RFC 3986描述，在程序中分割其组成部分
  *
  * \verbatim
  * 查看 RFC 3986.
  * http://user:password@host:port/path
  * foo://example.com:8042/over/there?name=ferret#nose
  * \_/   \______________/\_________/ \_________/ \__/
  *  |           |            |           |        |
  * 方案        认证          路径       请求      片段
  * scheme     authority     path      query     fragment
  *        \_______________________/
  *                  |
  *              hier_part
  *
  * 最重要的是ABNF规则:
  *
  * authority     = [ userinfo "@" ] host [ ":" port ]
  * URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
  *
  * \endverbatim
  *
  */


namespace unispace
{
	/**
	 * @brief 如果网址看起来无效，则抛出异常
	 */
	class us_bad_url : public std::runtime_error {
	public:
		us_bad_url(const std::string& reason) : std::runtime_error(reason) { }
		us_bad_url() : std::runtime_error("unspecified") { }
	};

	/**
	 * @brief 如果url无法正确解析，则抛出异常
	 */
	class us_url_parse_error : public us_bad_url {
	public:
		us_url_parse_error(const std::string& reason) : us_bad_url(reason) { }
		us_url_parse_error() : us_bad_url() { }
	};



	class _US_DATA_STORAGE_DLL us_url {
	public:
		/// @throw us_url_parse_error 在URL解析错误时
		explicit us_url(const us_ustring& s);
		explicit us_url();


		_US_DATA_STORAGE_DLL friend std::ostream& operator<<(std::ostream& os, const us_url& u);

		/// @throw us_url_parse_error 在URL解析错误时
		void assign(const us_ustring& s);

		/**
		 * @brief 与相对引用合并
		 * 将相对引用u变换为目标URL。详见 [RFC3986 Page 34]
		 */
		us_url& merge_ref(const us_url& u);

		/*** 重载运算符 ***/
		us_url& operator=(const us_ustring& s);

		/**
		 * 这用于合并两个相对URI或一个绝对URI和一个相对URI。
		 * Since merging with an absolute URI just overwrites everything.
		 * Urls with authority have absolute paths
		 * @throws us_bad_url
		 */
		us_url& operator+=(const us_url& u);
		bool operator==(const us_url& u);
		bool operator!=(const us_url& u);

		// 安全的bool手法, operator bool将导致意外转换到char,所以我们使用operator us_ustring
		// http://www.artima.com/cppsource/safebool2.html
		typedef void (us_url::*safe_bool)() const;

		inline operator safe_bool() const
		{
			if (empty()) {
				return 0;
			}
			else {
				return &us_url::safe_bool_aux;
			}
		}
		inline void safe_bool_aux() const {}

		inline operator us_ustring()
		{
			return get();
		}

		/**
		 * 方案和主机不区分大小写
		 * scheme and host are case insensitive
		 */
		void normalize_scheme();	// 归一化方案
		void normalize_host();		// 归一化主机
		/**
		 * 按照rfc强制要求将pct编码的转义标准化为大写
		 * normalize pct-encoded escapes to uppercase as mandated by rfc
		 */
		void normalize_escapes();
		static us_ustring normalize_escapes(const us_ustring&);
		/**
		 * 归一化所有组件
		 * does all normalizations
		 */
		void normalize();

		// 清空url
		inline void clear()
		{
			m_scheme.clear();
			clear_authority();

			m_path.clear();

			clear_query();
			clear_fragment();
		}

		// URL是否为空判断
		bool empty() const;


		/**
		 * 获取us_ustring形式的整个url
		 */
		us_ustring get() const;
		us_ustring to_string() const { return get(); };
		us_ustring as_string() const { return get(); };

		/**
		 * 该URL表示为一个字符串的时大小
		 */
		size_t size() const;

		static us_ustring escape_reserved_unsafe(const us_ustring& s);

		/**
		 * 使用提供的转义字符掩码
		 */
		static us_ustring escape(const us_ustring& s, const unsigned char mask);

		/**
		 * 匹配字符表中的非转义字符给掩码
		 */
		static us_ustring unescape(const us_ustring& s, const unsigned char mask);

		/**
		 * 未转义那些不匹配掩码
		 */
		static us_ustring unescape_not(const us_ustring& s, const unsigned char mask);

		/**
		 * 未转义的是安全的
		 */
		static us_ustring unescape_safe(const us_ustring& s);

		/**
		 * 取消转义所有pct编码
		 */
		static us_ustring unescape(const us_ustring& s);

		/**
		 * The rfc says: "If a URI does not contain an authority component, then the path cannot begin with two slash characters ("//")"
		 * But then, there are the file:// URIs that can be file:///tmp/ or similar, so this apparently violates the rfc.
		 * @throws boost::regex_error
		 */
		bool syntax_ok() const;
		bool valid_host() const;
		static bool valid_host(const us_ustring&);

		/***** 访问 *****/
		void scheme(const us_ustring& s);
		inline us_ustring scheme() const
		{
			return m_scheme;
		}

		void set_authority(const us_ustring& s);
		us_ustring authority() const;

		/**
		 * authority     = [ userinfo "@" ] host [ ":" port ]
		 */
		inline bool has_authority() const
		{
			return m_has_authority;
		}
		// 有方案?
		inline bool has_scheme() const
		{
			return (!m_scheme.empty());
		}
		// 清空认证信息
		inline void clear_authority()
		{
			m_host_ip_literal = false;
			m_has_authority = false;
			m_userinfo.clear();
			m_host.clear();
			m_port.clear();
		}

		// 是否有请求
		inline bool has_query() const
		{
			return !m_query.empty();
		}

		// 清空请求
		inline void clear_query()
		{
			m_query.clear();
		}
		// 有片段
		inline bool has_fragment() const
		{
			return !m_fragment.empty();
		}
		// 清空片段
		inline void clear_fragment()
		{
			m_fragment.clear();
		}

		/**
		 * absolute-URI  = scheme ":" hier-part [ "?" query ]
		 * hier-part     = "//" authority path-abempty
		 *                    / path-absolute
		 *                    / path-rootless
		 *                    / path-empty
		 */
		bool absolute() const;

		// 用户信息
		void set_userinfo(const us_ustring& s);
		inline us_ustring userinfo() const
		{
			return m_userinfo;
		}

		void set_host(const us_ustring& s);
		inline us_ustring host() const
		{
			return m_host;
		}

		void set_port(const us_ustring& s);
		/// @returns port
		us_ustring port() const;
		int port_int() const;

		void set_path(const us_ustring& s);

		/// @returns the path
		inline us_ustring path() const
		{
			return m_path.get();
		}

		/// normalize path, removing /./ and /../ segments
		void normalize_path() { m_path.normalize(); };

		void query(const us_ustring& s);
		/// @return the query part
		us_ustring query() const { return m_query; }

		void set_fragment(const us_ustring& s);

		/// @return the fragment part
		inline us_ustring fragment() const { return m_fragment; }

		void set_def_port();

		bool m_has_authority;
		bool m_host_ip_literal;
		us_ustring m_scheme;	// 方案
		us_path     m_path;		// 路径
		us_ustring m_userinfo;	// 用户信息
		us_ustring m_host;		// 主机
		us_ustring m_port;		// 端口
		us_ustring m_query;	// 请求
		us_ustring m_fragment;	// 片段
	};


} // end ns url

/** @} */

#endif // !__US_URL_HPP__
