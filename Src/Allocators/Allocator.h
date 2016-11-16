//
// Created by amit on 14/11/2016.
//

#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H
#include <new>
#include "../../GeneralTypes.h"

namespace ditwo
{
	template <class T>
	class Allocator
	{
	public:
		using value_type = T;
		Allocator() = default;
		~Allocator() = default;
		template <typename... Args>
		static void construct(Allocator &a, T *p, Args &&... args);
		static void destroy(Allocator &a, T *p);
		static T *allocate(Allocator &a, unsigned int size);
		static void deallocate(Allocator &a, T *p, unsigned int size);
	};
}
#include "Allocator.cpp"

#endif