#ifndef __US_FILESYSTEM_HPP__
#define __US_FILESYSTEM_HPP__

#include <vector>

#ifndef __US_STRING_HPP__
#include "../common/us_string.hpp"
#endif

namespace unispace
{
	class us_ustring;
	namespace filesystem
	{

		/**********************************************************************//**
		 * @brief	判断文件是否存在.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	filename	待测试的文件路径.
		 * @return	文件存在返回true，不存在返回false.
		 *************************************************************************/
		_US_UTIL_DLL bool is_file(const us_ustring& filename);
		
		/**********************************************************************//**
		 * @brief	创建文件.
		 *			在当前工作目录下创建文件，可使用绝对路径在其它目录下创建。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	file		待创建文件名.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	创建成功返回true，失败返回false.
		 *************************************************************************/
		_US_UTIL_DLL bool create_file(const us_ustring& file, bool isreplance = false);
		
		/**********************************************************************//**
		 * @brief	拷贝文件.
		 *			将文件拷贝到指定目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	exist_file		待拷贝文件.
		 * @param	dest_dir		目标目录.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/
		_US_UTIL_DLL bool copy_file(const us_ustring& exist_file, const us_ustring& dest_dir, 
			bool isreplance = false);
		/**********************************************************************//**
		 * @brief	拷贝文件.
		 *			将文件拷贝到指定目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	exist_file		待拷贝文件.
		 * @param	dest_dir		目标目录.
		 * @param	dest_file		目标文件名.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	成功返回true，失败返回false.
		 *************************************************************************/
		_US_UTIL_DLL bool copy_file(const us_ustring& exist_file, const us_ustring& dest_dir, 
			const us_ustring& dest_file, bool isreplance = false);

		/**********************************************************************//**
		 * @brief	拷贝批量文件.
		 *			将多个文件拷贝到指定目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	files			待拷贝文件列表指针.
		 * @param	count			待拷贝文件数.
		 * @param	dest_dir		目标目录.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	拷贝成功的文件数，出错返回-1.
		 *************************************************************************/
		_US_UTIL_DLL int copy_file(const us_ustring* files, size_t count, const us_ustring& dest_dir, bool isreplance = false);
		/**********************************************************************//**
		 * @brief	拷贝批量文件.
		 *			将多个文件拷贝到指定目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	files			待拷贝文件列表.
		 * @param	dest_dir		目标目录.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	拷贝成功的文件数，出错返回-1.
		 *************************************************************************/
		_US_UTIL_DLL int copy_file(const std::vector<us_ustring> files, const us_ustring& dest_dir, bool isreplance = false);

		/**********************************************************************//**
		 * @brief	拷贝目录下所有文件(返回拷贝成功的文件数).
		 *			拷贝指定目录下的所有普通文件，不包括子目录等，到指定的目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	exist_dir	待拷贝文件的目录.
		 * @param	dest_dir	目标目录.
		 * @param	isreplance	是否替换已经存在文件.
		 * @return	拷贝成功的文件数，出错返回-1.
		 *************************************************************************/
		_US_UTIL_DLL int copy_all_files(const us_ustring& exist_dir, const us_ustring& dest_dir, bool isreplance = false);

		/**********************************************************************//**
		 * @brief	删除文件.
		 *			当文件不存在或者没有权限删除文件，以及删除标准输入输出或内存映射
		 *			文件的时候返回失败。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	exist_file		待删除的文件.
		 * @return	成功执行删除返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool remove_file(const us_ustring& exist_file);

		/**********************************************************************//**
		 * @brief	重命名文件或目录.
		 *			当目标名称已经存在的时候，将失败.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	old_name	当前文件/目录名.
		 * @param	new_name	目标文件/目录名.
		 * @return	成功返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool rename(const us_ustring& old_name, const us_ustring& new_name);

		/**********************************************************************//**
		 * @brief	移动文件或目录到指定路径下.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	src_path	当前文件/目录路径.
		 * @param	dest_dir	目标目录路径.
		 * @param	dst_name	目标文件/目录名.
		 * @return	成功返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool move(const us_ustring& src_path, const us_ustring& dest_dir,
			const us_ustring& dst_name);

		/**********************************************************************//**
		 * @brief	判断指定路径是否是一个已经目录.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory		待判断目录路径.
		 * @return	directory是一个存在目录时返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool is_dir(const us_ustring& directory);

		
		/**********************************************************************//**
		 * @brief	创建目录.
		 *			默认不递归创建，指定路径中的某一层级不存在的时候，不进行创建。
		 *			可通过指定recursive参数来进行递归创建.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory		待创建目录路径.
		 * @param	recursive		是否递归创建.
		 * @return	成功返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool mk_dir(const us_ustring& directory, bool recursive = false);
		
		/**********************************************************************//**
		 * @brief	拷贝目录.
		 *			默认进行递归拷贝。即原目录中的文件及子目录都将拷贝到新的目录中。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	exist_dir		待拷贝路径.
		 * @param	dest_dir		目标路径.
		 * @param	recursive		是否递归拷贝.
		 * @return	成功返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool copy_dir(const us_ustring& exist_dir, const us_ustring& dest_dir,
			bool recursive = true);

		/**********************************************************************//**
		 * @brief	判断目录是否为空.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory		待检测目录.
		 * @return	目录存在且为空的时候返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool is_empty_dir(const us_ustring& directory);
		
		/**********************************************************************//**
		 * @brief	删除目录(默认仅删除空目录).
		 *			默认不进行递归删除，仅仅删除空目录。可通过指定第二个参数进行递归
		 *			删除。目录不存在或没有权限等情况下返回失败。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory		待删除目录.
		 * @param	only_empty_dir	是否仅删除空目录.
		 * @return	删除成功返回true.
		 *************************************************************************/
		_US_UTIL_DLL bool rm_dir(const us_ustring& directory, bool only_empty_dir = true);

		/**********************************************************************//**
		 * @brief	获取目录项.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory		待读取目录.
		 * @param	filter			过滤文本.
		 * @param	only_file		是否仅列出文件
		 * @return	读取到的目录项.
		 *************************************************************************/
		_US_UTIL_DLL std::vector<us_ustring> list_entry(const us_ustring& directory,
			const us_ustring & filter = us_ustring("*.*"),bool only_file = true);

		/**********************************************************************//**
		 * @brief	获取目录项.
		 *			mode为文件类型，只有其中的7个bit位有效。<br>
		 *			S_IFSOCK    0140000     socket  <br>
		 *			S_IFLNK     0120000     符号链接(symbolic link)  <br>
		 *			S_IFREG     0100000     一般文件  <br>
		 *			S_IFBLK     0060000     区块装置(block device)  <br>
		 *			S_IFDIR     0040000     目录  <br>
		 *			S_IFCHR     0020000     字符装置(character device)  <br>
		 *			S_IFIFO     0010000     先进先出(fifo)  <br>
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	directory	待读取目录.
		 * @param	filter		过滤文本.
		 * @param	mode		列出的目录项的类型。
		 * @return	读取到的目录项.
		 *************************************************************************/
		_US_UTIL_DLL std::vector<us_ustring> list_entry(
			const us_ustring& directory,
			const us_ustring & filter,
			uint32_t mode);

		/**********************************************************************//**
		 * @brief	获取当前工作路径.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @return	当前工作路径(绝对路径).
		 *************************************************************************/
		_US_UTIL_DLL us_ustring get_cwd();

		/**********************************************************************//**
		 * @brief	获取文件大小(字节数)
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	filename	文件路径.
		 * @return	返回文件的大小，失败返回负值.
		 *************************************************************************/
		_US_UTIL_DLL int64_t filesize(const us_ustring& filename);

		/**********************************************************************//**
		 * @brief	读取文件内容
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/02/17
		 * @param	filename	文件路径.
		 * @param	outbuf		指向缓冲区的字符指针.
		 * @param	number		要读取的字节数，同时也是outbuf的最小保证大小.
		 * @param	offset		读取文件起始位置，默认为0(从文件头部开始读取).
		 * @return	返回读取到的字节数，失败返回负值.
		 *************************************************************************/
		_US_UTIL_DLL int64_t read_file(const us_ustring& filename,
			char* outbuf,size_t number,size_t offset = 0);

		/**********************************************************************//**
		 * @brief	获取路径中的文件名部分.
		 *			获取最后的文件名部分，例如"C:\123\456.txt"则返回"456.txt"。
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/9/26
		 * @param	filepath		文件路径.
		 * @return	文件名.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring basename(const us_ustring& filepath);

		/**********************************************************************//**
		 * @brief	返回根目录的绝对路径.
		 *			在Unix操作系统这个返回“/”。<br>
		 *			在Windows操作系统，使用SystemDrive环境变量值。如果获取失败，返回"C:\".
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/15
		 * @return	用户的主目录的绝对路径.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring root_dir_path();

		/**********************************************************************//**
		 * @brief	返回用户的主目录的绝对路径.
		 *			在Windows NT/2000下，这个函数返回HOMEPATH环境变量的值。没有则通过连接
		 *			HOMEDRIVE和HOMEPATH环境变量来形成这个路径。<br>
		 *			在Windows 9x和非Windows操作系统，HOME环境变量被使用。<br>
		 *			如果这个环境变量没有被设置，root_dir_path()用来代替它.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2017/3/15
		 * @return	用户的主目录的绝对路径.
		 *************************************************************************/
		_US_UTIL_DLL us_ustring home_dir_path();
	}
};

#endif //!__US_FILE_SYSTEM_HPP__
