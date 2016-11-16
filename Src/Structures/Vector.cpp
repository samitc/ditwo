//
// Created by amit on 14/11/2016.
//

#ifndef DITWO_VECTOR_CPP
#define DITWO_VECTOR_CPP
#include "Vector.h"

namespace ditwo
{
	template <class T, class Alloc>
	Vector<T, Alloc>::~Vector() noexcept
	{
		clear();
		Alloc::deallocate(*this, dataVal, capacity());
	}
	template <class T, class Alloc>
	Vector<T, Alloc>::Vector() NOEXPECT_NOTHROW_DEFAULT_CONSTRACTUR(T) :
			Alloc(), dataVal(nullptr), last(nullptr), maxMem(
			nullptr)
	{
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::resize(uint32 newSize)
	{
		if (newSize < size())
		{
			erase(newSize, last - dataVal);
		}
		else
		{
			if (newSize > capacity())
			{
				reserve(newSize * VECTOR_GROW_MODIFIER);
			}
			auto newSizeP = dataVal + newSize;
			while (last < newSizeP)
			{
				Alloc::construct(*this, last++);
			}
		}
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::pop_back()noexcept
	{
		Alloc::destroy(*this, last--);
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::erase(uint32 index) noexcept
	{
		erase(index, index + 1);
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::erase(uint32 startIndex, uint32 lastIndex) noexcept
	{
		if (startIndex != lastIndex)
		{
			auto lastP = dataVal + lastIndex;
			auto startP = dataVal + startIndex;
			lastP = move(lastP, last, startP);
			destroy(lastP, last);
			last = lastP;
		}
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::clear()noexcept
	{
		destroy(dataVal, last);
		last = dataVal;
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::reserve(uint32 newMaxSize)
	{
		if (capacity() < newMaxSize)
		{
			auto ptr = Alloc::allocate(*this, newMaxSize);
			auto preSize = size();
			move(dataVal, last, ptr);
			Alloc::deallocate(*this, dataVal, capacity());
			dataVal = ptr;
			last = dataVal + preSize;
			maxMem = dataVal + newMaxSize;
		}
	}
	template <class T, class Alloc>
	T *Vector<T, Alloc>::move(T *first, T *last, T *dst)
	{
		while (first < last)
		{
			*dst++ = std::move(*first++);
		}
		return dst;
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::rmove(T *first, T *last, T *dst)
	{
		auto nDst = dst + (last - first);
		while (last > first)
		{
			*--nDst = std::move(*--last);
		}
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::destroy(T *first, T *last)
	{
		while (first < last)
		{
			Alloc::destroy(*this, first++);
		}
	}
	template <class T, class Alloc>
	uint32 Vector<T, Alloc>::size() const noexcept
	{
		return last - dataVal;
	}
	template <class T, class Alloc>
	uint32 Vector<T, Alloc>::capacity() const noexcept
	{
		return maxMem - dataVal;
	}
	template <class T, class Alloc>
	const T *Vector<T, Alloc>::data() const
	{
		return dataVal;
	}
	template <class T, class Alloc>
	T *Vector<T, Alloc>::data()
	{
		return dataVal;
	}
	template <class T, class Alloc>
	bool Vector<T, Alloc>::empty() const
	{
		return dataVal == last;
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::checkForReserve(uint32 addSize)
	{
		if (last + addSize > maxMem)
		{
			reserve((capacity() + addSize) * VECTOR_GROW_MODIFIER);
		}
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::push_back(const T &val)
	{
		checkForReserve(1);
		Alloc::construct(*this, last++, val);
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::push_back(T &&val)
	{
		checkForReserve(1);
		*last++ = std::move(val);
	}
	#define insertVector(num)\
    checkForReserve(num);\
    auto p=dataVal+index;auto pEnd=p+(num);\
    rmove(p,last,pEnd);\
    last += num;
	template <class T, class Alloc>
	void Vector<T, Alloc>::insert(uint32 index, const T &val)
	{
		insert(index, 1, val);
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::insert(uint32 index, T &&val)
	{
		insertVector(1);
		*p = std::move(val);
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::insert(uint32 index, uint32 size, const T &val)
	{
		insertVector(size);
		while (p < pEnd)
		{
			Alloc::construct(*this, p++, val);
		}
	}
	template <class T, class Alloc>
	void Vector<T, Alloc>::insert(uint32 index, uint32 size, T &&val)
	{
		insertVector(size);
		while (p < pEnd - 1)
		{
			Alloc::construct(*this, p++, val);
		}
		*p = std::move(val);
	}
	template <class T, class Alloc>
	T &Vector<T, Alloc>::operator[](uint32 index) noexcept
	{
		return *(dataVal + index);
	}
	template <class T, class Alloc>
	const T &Vector<T, Alloc>::operator[](uint32 index) const noexcept
	{
		return *(dataVal + index);
	}
	template <class T, class Alloc>
	T &Vector<T, Alloc>::at(uint32 index) noexcept
	{
		return *(dataVal + index);
	}
	template <class T, class Alloc>
	const T &Vector<T, Alloc>::at(uint32 index) const noexcept
	{
		return *(dataVal + index);
	}
	template <class T, class Alloc>
	T &Vector<T, Alloc>::front() noexcept
	{
		return *(dataVal);
	}
	template <class T, class Alloc>
	const T &Vector<T, Alloc>::front() const noexcept
	{
		return *(dataVal);
	}
	template <class T, class Alloc>
	T &Vector<T, Alloc>::back() noexcept
	{
		return *(last - 1);
	}
	template <class T, class Alloc>
	const T &Vector<T, Alloc>::back() const noexcept
	{
		return *(last - 1);
	}
}
#endif