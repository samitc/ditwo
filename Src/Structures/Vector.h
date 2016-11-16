//
// Created by amit on 14/11/2016.
//

#ifndef _VECTOR_H
#define _VECTOR_H

#include "../../GeneralTypes.h"

#if !defined(VECTOR_GROW_MODIFIER)
#define VECTOR_GROW_MODIFIER	2
#endif
#define COMMA	,
#define CREATE_GET_FUNCTION_NOEXCPET(name,params,returnType)\
	returnType name(params) noexcept;\
	const returnType name(params) const noexcept;
#define CREATE_R_AND_L_FUNC(name,type,paramName,returnType)\
	returnType name(const type& paramName);\
	returnType name(type&& paramName);
#define CREATE_R_AND_L_FUNC_PARAMS(name,type,paramName,params,returnType)\
	returnType name(params, const type& paramName);\
	returnType name(params, type&& paramName);

template<class T, class Alloc> class Vector :public Alloc {
public:
	Vector() NOEXPECT_NOTHROW_DEFAULT_CONSTRACTUR(T);
	~Vector() noexcept ;
	CREATE_R_AND_L_FUNC(push_back,T,val,void);
	CREATE_R_AND_L_FUNC_PARAMS(insert,T,val,uint32 index,void);
	CREATE_R_AND_L_FUNC_PARAMS(insert,T,val,uint32 index COMMA uint32 size,void);
	void pop_back() noexcept;
	void erase(uint32 index) noexcept;
	void erase(uint32 startIndex,uint32 lastIndex) noexcept;
	void resize(uint32 newSize);
	void reserve(uint32 newMaxSize);
	void clear() noexcept;
	uint32 size() const noexcept;
	uint32 capacity() const noexcept;
	const T* data() const;
	CREATE_GET_FUNCTION_NOEXCPET(operator[],uint32 index,T&);
	CREATE_GET_FUNCTION_NOEXCPET(at,uint32 index,T&);
	CREATE_GET_FUNCTION_NOEXCPET(front,,T&);
	CREATE_GET_FUNCTION_NOEXCPET(back,,T&);
private:
	static T* move(T* first,T* last,T* dst);
	static void rmove(T* first,T* last,T* dst);
	void checkForReserve(uint32 addSize);
	void destroy(T* first,T* last);
	T* dataVal;
	T* last;
	T* maxMem;
};

#include "Vector.cpp"
#endif