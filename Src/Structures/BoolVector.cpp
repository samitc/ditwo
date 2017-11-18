//
// Created by amit on 20/11/2016.
//
#ifndef _BOOLVECTOR_CPP_
#define _BOOLVECTOR_CPP_
#include "BoolVector.h"

namespace ditwo
{
	template <class T> constexpr uint32 getSize(uint32 size)
	{
		uint32 retSize = size / sizeof(T);
		if (size % sizeof(T) > 0)
		{
			retSize += 1;
		}
	}
	template <class T, bool val> void setAll(T *mem, T* maxMem)
	{
		if (val)
		{
			memset(mem, -1, maxMem - mem);
		}
		else
		{
			memset(mem, 0, maxMem - mem);
		}
	}
	template <class Alloc>
	Vector<bool, Alloc>::Vector() noexcept(std::is_nothrow_default_constructible<bool>::value) :Alloc(), dataVal(localData), maxMem(localData + LOCAL_SIZE / sizeof(valType)), curSize(0)
	{

	}
	template <class Alloc>
	Vector<bool, Alloc>::Vector(uint32 size) noexcept(std::is_nothrow_default_constructible<bool>::value) :Alloc(), curSize(0)
	{
		if (size > LOCAL_SIZE)
		{
			dataVal = new valType[getSize(size)];
			maxMem = dataVal + getSize(size);
		}
		else
		{
			dataVal = &localData;
			maxMem = localData + LOCAL_SIZE / sizeof(valType);
		}
	}
	template <class Alloc>
	Vector<bool, Alloc>::~Vector() noexcept
	{
		clear();
		if (dataVal != localData)
		{
			Alloc::deallocate(*this, dataVal, capacity() / sizeof(valType));
		}
	}
	template <class Alloc>
	void Vector<bool, Alloc>::clear() noexcept
	{
		for (uint32 i = 0; i < curSize; i++)
		{
			Alloc::destroy(*this, dataVal[i]);
		}
		curSize = 0;
	}
	template <class Alloc>
	void Vector<bool, Alloc>::erase(uint32 startIndex, uint32 lastIndex) noexcept
	{
		uint32 startIndexVal = getSize<valType>(startIndex);
		uint32 endIndexVal = lastIndex / sizeof(valType);
		throw "not implement";
		if (startIndex != lastIndex)
		{
			auto lastP = dataVal + lastIndex;
			auto startP = dataVal + startIndex;
			lastP = move(lastP, last, startP);
			destroy(lastP, last);
			last = lastP;
		}
	}
	template <class Alloc>
	void Vector<bool, Alloc>::reserve(uint32 newMaxSize)
	{
		if (capacity() < newMaxSize)
		{
			auto ptr = Alloc::allocate(*this, newMaxSize);
			memmove(ptr, dataVal, curSize);
			Alloc::deallocate(*this, dataVal, capacity());
			dataVal = ptr;
			maxMem = dataVal + newMaxSize;
		}
	}
	template <class Alloc>
	uint32 Vector<bool, Alloc>::size() const noexcept
	{
		return curSize;
	}
	template <class Alloc>
	uint32 Vector<bool, Alloc>::capacity() const noexcept
	{
		return (maxMem - dataVal) * sizeof(valType);
	}
	template < class Alloc>
	void Vector<bool, Alloc>::checkForReserve(uint32 addSize)
	{
		if (curSize + addSize > capacity())
		{
			reserve((capacity() + addSize) * VECTOR_GROW_MODIFIER);
		}
	}
	template<class Alloc>
	void Vector<bool, Alloc>::setVal(uint32 posInArray, uint32 posInVal, bool val)
	{
		int finalPos = (1 << posInVal)&(val == true ? 1 : 0);
		this->dataVal[posInArray] = this->dataVal[posInArray] & ~(1 << posInVal) | (val << posInVal);
	}
	template<class Alloc>
	void Vector<bool, Alloc>::insertVectorm(uint32 size)
	{
		if (curSize % sizeof(valType) == 0 || size > sizeof(valType) - curSize % sizeof(valType) || size > sizeof(valType))
		{
			checkForReserve(size / sizeof(valType) + size % sizeof(valType) == 0 ? 0 : 1);
			Alloc::construct(*this, dataVal + (curSize / sizeof(valType)), 0);
		}
	}
	template <class Alloc>
	void Vector<bool, Alloc>::push_back(const bool &val)
	{
		if (curSize % sizeof(valType) == 0)
		{
			checkForReserve(1);
			Alloc::construct(*this, dataVal + (curSize / sizeof(valType)), 0);
		}
		int posInArray = curSize / sizeof(valType);
		int posInVal = curSize % sizeof(valType);
		setVal(posInArray, posInVal, val);
	}
	template <class Alloc>
	void Vector<bool, Alloc>::push_back(bool &&val)
	{
		push_back(val);
	}
	template <class Alloc>
	void Vector<bool, Alloc>::insert(uint32 index, const bool &val)
	{
		insert(index, 1, val);
	}
	template <class Alloc>
	void Vector<bool, Alloc>::insert(uint32 index, bool &&val)
	{
		insertVector(1);
		*p = std::move(val);
	}
	template <class Alloc>
	void Vector<bool, Alloc>::insert(uint32 index, uint32 size, const bool &val)
	{
		insertVector(size);
		while (p < pEnd)
		{
			Alloc::construct(*this, p++, val);
		}
	}
	template <class Alloc>
	void Vector<bool, Alloc>::insert(uint32 index, uint32 size, bool &&val)
	{
		insertVector(size);
		while (p < pEnd - 1)
		{
			Alloc::construct(*this, p++, val);
		}
		*p = std::move(val);
	}
	template <class Alloc>
	bool &Vector<bool, Alloc>::operator[](uint32 index) noexcept
	{
		return at(index);
	}
	template <class Alloc>
	const bool &Vector<bool, Alloc>::operator[](uint32 index) const noexcept
	{
		return at(index);
	}
	template <class Alloc>
	bool &Vector<bool, Alloc>::at(uint32 index) noexcept
	{
		uint32 posInArray = index / sizeof(valType);
		uint32 posInVal = index % sizeof(valType);
		return (dataVal[posInArray] & (1 << posInVal)) != 0;
	}
	template <class Alloc>
	const bool &Vector<bool, Alloc>::at(uint32 index) const noexcept
	{
		return at(index);
	}
	template <class Alloc>
	bool &Vector<bool, Alloc>::front() noexcept
	{
		return at(0);
	}
	template <class Alloc>
	const bool &Vector<bool, Alloc>::front() const noexcept
	{
		return front();
	}
	template <class Alloc>
	bool &Vector<bool, Alloc>::back() noexcept
	{
		return at(curSize - 1);
	}
	template <class Alloc>
	const bool &Vector<bool, Alloc>::back() const noexcept
	{
		return back();
	}
}
#endif