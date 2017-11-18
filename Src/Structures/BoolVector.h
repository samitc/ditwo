//
// Created by amit on 20/11/2016.
//

#ifndef DITWO_BOOLVECTOR_H
#define DITWO_BOOLVECTOR_H
#include "Vector.h"

namespace ditwo
{
	template <class Alloc>
	class Vector<bool, Alloc> : private Alloc
	{
	public:
#define VERTOR_INTERFACE_TYPE bool
#include "VectorInterface.h"
#undef VERTOR_INTERFACE_TYPE
	private:
		void checkForReserve(uint32 addSize);
		void setVal(uint32, uint32, bool);
		void insertVectorm(uint32);
		using valType=bool;
		static constexpr int LOCAL_SIZE=64;
		valType localData[LOCAL_SIZE / sizeof(valType)];
		valType *dataVal;
		int curSize;
		valType *maxMem;
	};
}
#include "BoolVector.cpp"
#endif //DITWO_BOOLVECTOR_H
