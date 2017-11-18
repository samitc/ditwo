//
// Created by amit on 14/11/2016.
//

#ifndef DITWO_VECTOR_H
#define DITWO_VECTOR_H
#include "../GeneralTypes.h"
#include "../Allocators/Allocator.h"

namespace ditwo
{
	#if !defined(VECTOR_GROW_MODIFIER)
		#define VECTOR_GROW_MODIFIER    2
	#endif
	template <class T, class Alloc = Allocator<T>>
	class Vector : private Alloc
	{
	public:
#define VERTOR_INTERFACE_TYPE T
#include "VectorInterface.h"
#undef VERTOR_INTERFACE_TYPE
	private:
		static T *move(T *first, T *last, T *dst);
		static void rmove(T *first, T *last, T *dst);
		void checkForReserve(uint32 addSize);
		void destroy(T *first, T *last);
		T *dataVal;
		T *last;
		T *maxMem;
	};
}
#include "Vector.cpp"

#endif