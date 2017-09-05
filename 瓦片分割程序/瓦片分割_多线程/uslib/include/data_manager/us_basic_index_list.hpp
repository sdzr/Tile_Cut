#ifndef __US_BASIC_INDEX_LIST_HPP__
#define __US_BASIC_INDEX_LIST_HPP__

#include <vector>

namespace unispace
{

	/**********************************************************************//**
	 * @brief	数据库基本索引列表.
	 *			是影像索引列表和数据集索引列表等的基础。只提供几个基本的对外接口<br>
	 *			避免直接修改索引列表，所有非const方法都在子类以private方式实现。
	 * @author	yimin.liu@unispace-x.com
	 * @date	2016/10/12
	 *************************************************************************/
	template<typename INDEX_T>
	class us_basic_index_list{
	public:
		typedef typename std::vector<INDEX_T>::const_iterator const_iterator;
		// typedef INDEX_T* const_iterator;
		/**********************************************************************//**
		 * @brief	构造函数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @param	count	索引个数(只是参考)
		 *************************************************************************/
		us_basic_index_list(int32_t count = 50);

		/**********************************************************************//**
		 * @brief	获取当前索引数.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @return	返回保存的数据集数.
		 *************************************************************************/
		const int get_count()const;

		const INDEX_T& operator[](int index)const;

		/**********************************************************************//**
		 * @brief	获取指向保存索引的容器起始位置的迭代器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @return	返回指向容器起始位置的迭代器.
		 *************************************************************************/
		const_iterator begin()const
		{
			return m_index.begin();
		}

		/**********************************************************************//**
		 * @brief	获取指向保存索引的容器末尾位置的迭代器.
		 * @author	yimin.liu@unispace-x.com
		 * @date	2016/10/12
		 * @return	返回指向容器末尾位置的迭代器.
		 *************************************************************************/
		const_iterator end()const
		{
			return m_index.end();
		}

	protected:
		std::vector<INDEX_T> m_index;
	};

	template<typename INDEX_T>
	inline us_basic_index_list<INDEX_T>::us_basic_index_list(int32_t count)
	{
		m_index.reserve(count);
	}

	template<typename INDEX_T>
	inline const int us_basic_index_list<INDEX_T>::get_count() const
	{
		return m_index.size();
	}

	template<typename INDEX_T>
	inline const INDEX_T & us_basic_index_list<INDEX_T>::operator[](int index) const
	{
		return m_index[index];
	}
}



#endif // !__US_BASIC_INDEX_LIST_HPP__

