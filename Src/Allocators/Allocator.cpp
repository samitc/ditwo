//
// Created by amit on 14/11/2016.
//

#ifndef _ALLOCATOR_CPP_
#define _ALLOCATOR_CPP_
#include "Allocator.h"
#include <utility>
template<class T>
template<typename... Args>
void Allocator<T>::construct(Allocator<T> &a, T *p, Args &&... args) {
::new (p) T(std::forward<Args>(args)...);
}
template<class T>
void Allocator<T>::destroy(Allocator<T> &a, T *p) {
p->~T();
}
template<class T>
T *Allocator<T>::allocate(Allocator<T> &a, unsigned int size) {
	return (T*)::operator new(size* sizeof(T));
}
template<class T>
void Allocator<T>::deallocate(Allocator<T> &a, T *p, unsigned int size) {
	::operator delete(p);
}

#endif