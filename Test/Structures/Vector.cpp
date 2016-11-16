//
// Created by amit on 16/11/2016.
//
#include <random>
#include "gtest/gtest.h"
#include "../../Src/Structures/Vector.h"

using namespace ditwo;
void initVectorTest()
{
	srand((unsigned int) time(nullptr));
}
TEST(VectorGeneralTests, GeneralTest)
{
	Vector<int> v;
	ASSERT_TRUE(v.empty());
	ASSERT_EQ(0, v.size());
	ASSERT_EQ(0, v.capacity());
}
TEST(VectorGeneralTests, pushTest)
{
	Vector<int> v;
	v.push_back(5);
	ASSERT_EQ(1, v.size());
	ASSERT_FALSE(v.empty());
	ASSERT_EQ(5, v.at(0));
	ASSERT_EQ(5, v.back());
	ASSERT_EQ(5, v.front());
	ASSERT_EQ(5, v[0]);
}
TEST(VectorGeneralTests, popTest)
{
	Vector<int> v;
	v.push_back(5);
	v.pop_back();
	ASSERT_EQ(0, v.size());
}
TEST(VectorGeneralTests, pushPopMultiTest)
{
	constexpr int AMOUNT = 5;
	int data[AMOUNT];
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand();
	}
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.push_back(data[i]);
	}
	ASSERT_EQ(AMOUNT, v.size());
	ASSERT_EQ(data[AMOUNT - 1], v.back());
	ASSERT_EQ(data[0], v.front());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		for (size_t j = 0; j < AMOUNT - i; j++)
		{
			ASSERT_EQ(data[i], v[i]);
			ASSERT_EQ(data[i], v.at(i));
		}
		v.pop_back();
	}
}
TEST(VectorGeneralTests, dataTest)
{
	Vector<int> v;
	v.push_back(5);
	v.push_back(16);
	ASSERT_EQ(5, *v.data());
	ASSERT_EQ(16, *(v.data() + 1));
}
TEST(VectorGeneralTests, reserveTest)
{
	const int r1 = 6;
	const int r2 = 2;
	const int r3 = 10;
	Vector<int> v;
	v.reserve(r1);
	ASSERT_EQ(r1, v.capacity());
	ASSERT_EQ(0, v.size());
	v.push_back(5);
	v.push_back(7);
	ASSERT_EQ(r2, v.size());
	ASSERT_EQ(5, v[0]);
	ASSERT_EQ(7, v[1]);
	v.reserve(r2);
	ASSERT_EQ(r1, v.capacity());
	ASSERT_EQ(r2, v.size());
	ASSERT_EQ(5, v[0]);
	ASSERT_EQ(7, v[1]);
	v.reserve(r3);
	ASSERT_EQ(r3, v.capacity());
	ASSERT_EQ(r2, v.size());
	ASSERT_EQ(5, v[0]);
	ASSERT_EQ(7, v[1]);
}
TEST(VectorGeneralTests, resizeTest)
{
	const int s1 = 6;
	const int s2 = 3;
	const int s3 = 10;
	Vector<int> v;
	v.resize(s1);
	ASSERT_EQ(s1, v.size());
	for (size_t i = 0; i < s1; i++)
	{
		ASSERT_EQ(0, v[i]);
	}
	v.resize(s2);
	ASSERT_EQ(s2, v.size());
	for (size_t i = 0; i < s2; i++)
	{
		ASSERT_EQ(0, v[i]);
	}
	v.resize(s3);
	ASSERT_EQ(s3, v.size());
	for (size_t i = 0; i < s3; i++)
	{
		ASSERT_EQ(0, v[i]);
	}
}
TEST(VectorGeneralTests, changeTest)
{
	Vector<int> v;
	v.push_back(5);
	v[0] = 6;
	ASSERT_EQ(1, v.size());
	ASSERT_EQ(6, v.at(0));
	ASSERT_EQ(6, v.back());
	ASSERT_EQ(6, v.front());
	ASSERT_EQ(6, v[0]);
}
TEST(VectorGeneralTests, insertTest)
{
	constexpr int AMOUNT = 50;
	int data[AMOUNT];
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand();
	}
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.insert(0, data[AMOUNT - i - 1]);
	}
	ASSERT_EQ(AMOUNT, v.size());
	ASSERT_EQ(data[AMOUNT - 1], v.back());
	ASSERT_EQ(data[0], v.front());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		ASSERT_EQ(data[i], v[i]);
		ASSERT_EQ(data[i], v.at(i));
	}
	v.insert(AMOUNT / 2, 555);
	ASSERT_EQ(AMOUNT + 1, v.size());
	ASSERT_EQ(555, v[AMOUNT / 2]);
	ASSERT_EQ(data[AMOUNT / 2], v[(AMOUNT / 2) + 1]);
	ASSERT_EQ(data[(AMOUNT / 2) - 1], v[(AMOUNT / 2) - 1]);
}
TEST(VectorGeneralTests, insertMultiTest)
{
	constexpr int AMOUNT = 50;
	constexpr int DATA_AMOUNT = 5;
	int data[AMOUNT];
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand();
	}
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.insert(0, DATA_AMOUNT, data[AMOUNT - i - 1]);
	}
	ASSERT_EQ(AMOUNT * DATA_AMOUNT, v.size());
	ASSERT_EQ(data[AMOUNT - 1], v.back());
	ASSERT_EQ(data[0], v.front());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		for (size_t j = 0; j < DATA_AMOUNT; j++)
		{
			ASSERT_EQ(data[i], v[i * DATA_AMOUNT + j]);
			ASSERT_EQ(data[i], v.at(i * DATA_AMOUNT + j));
		}
	}
	v.insert(AMOUNT / 2, DATA_AMOUNT, 555);
	ASSERT_EQ(AMOUNT * DATA_AMOUNT + DATA_AMOUNT, v.size());
	for (size_t i = 0; i < DATA_AMOUNT; i++)
	{
		ASSERT_EQ(555, v[AMOUNT / 2 + i]);
	}
	ASSERT_EQ(data[(AMOUNT / 2) / DATA_AMOUNT], v[(AMOUNT / 2) + DATA_AMOUNT]);
	ASSERT_EQ(data[(AMOUNT / 2) / DATA_AMOUNT - 1], v[(AMOUNT / 2) - 1]);
}
TEST(VectorGeneralTests, eraseTest)
{
	constexpr int AMOUNT = 50;
	int data[AMOUNT];
	std::vector<int> removedData;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand();
		removedData.push_back(i);
	}
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.insert(0, data[AMOUNT - i - 1]);
	}
	for (size_t i = 0; i < AMOUNT; i++)
	{
		int curEraseI = (abs(rand())) % removedData.size();
		int curErase = removedData[curEraseI];
		removedData.erase(removedData.begin() + curEraseI);
		v.erase(curEraseI);
		ASSERT_EQ(removedData.size(), v.size());
		for (size_t i = 0; i < removedData.size(); i++)
		{
			ASSERT_EQ(data[removedData[i]], v[i]);
		}
	}
}
TEST(VectorGeneralTests, eraseMultiTest)
{
	constexpr int AMOUNT = 50;
	constexpr int DATA_AMOUNT = 5;
	int data[AMOUNT];
	std::vector<int> removedData;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand();
		removedData.push_back(i);
	}
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.insert(0, DATA_AMOUNT, data[AMOUNT - i - 1]);
	}
	for (size_t i = 0; i < AMOUNT; i++)
	{
		int curEraseI = (abs(rand())) % removedData.size();
		int curErase = removedData[curEraseI];
		removedData.erase(removedData.begin() + curEraseI);
		v.erase(curEraseI * DATA_AMOUNT, (curEraseI + 1) * DATA_AMOUNT);
		ASSERT_EQ(removedData.size() * DATA_AMOUNT, v.size());
		for (size_t i = 0; i < removedData.size(); i++)
		{
			for (size_t j = 0; j < DATA_AMOUNT; j++)
			{
				ASSERT_EQ(data[removedData[i]], v[i * DATA_AMOUNT + j]);
			}
		}
	}
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.push_back(data[i]);
	}
	v.erase(0, v.size());
	ASSERT_EQ(0, v.size());
}
TEST(VectorGeneralTests, clearTest)
{
	constexpr int AMOUNT = 50;
	int data[AMOUNT];
	Vector<int> v;
	for (size_t i = 0; i < AMOUNT; i++)
	{
		v.insert(0, data[AMOUNT - i - 1]);
	}
	ASSERT_EQ(AMOUNT, v.size());
	v.clear();
	ASSERT_EQ(0, v.size());
}
TEST(VectorTypesTests, floatTypeTest)
{
	Vector<float> f;
	const int AMOUNT = 50;
	float data[AMOUNT];
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = ((float) rand()) / RAND_MAX;
		f.push_back(data[i]);
	}
	ASSERT_EQ(AMOUNT, f.size());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		ASSERT_EQ(data[i], f[i]);
	}
}
TEST(VectorTypesTests, boolTypeTest)
{
	Vector<bool> b;
	const int AMOUNT = 50;
	bool data[AMOUNT];
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data[i] = rand() % 2 == 0;
		b.push_back(data[i]);
	}
	ASSERT_EQ(AMOUNT, b.size());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		ASSERT_EQ(data[i], b[i]);
	}
}
class CustomType
{
public:
	CustomType(int num)
	{
		this->num = num;
	}
	~CustomType()
	{
	}
	bool operator==(const CustomType &o) const
	{
		return num == o.num;
	}
	int num;
};
TEST(VectorTypesTests, customTypeTest)
{
	Vector<CustomType> c;
	const int AMOUNT = 50;
	std::vector<CustomType> data;
	data.reserve(AMOUNT);
	for (size_t i = 0; i < AMOUNT; i++)
	{
		data.push_back(CustomType(i));
		c.push_back(data[i]);
	}
	ASSERT_EQ(AMOUNT, c.size());
	for (size_t i = 0; i < AMOUNT; i++)
	{
		ASSERT_EQ(data[i], c[i]);
	}
}
void *curAlloc = nullptr;
template <class T>
class CustomAllocator
{
public:
	using value_type = T;
	CustomAllocator() : ptr((T *) ::operator new(sizeof(T) * MAX_SIZE))
	{
		curAlloc = (void *) ptr;
	}
	~CustomAllocator()
	{
		curAlloc = nullptr;
		::operator delete(ptr);
	}
	template <typename... Args>
	static void construct(CustomAllocator &a, T *p, Args &&... args)
	{
		::new(p) T(std::forward<Args>(args)...);
	}
	static void destroy(CustomAllocator &a, T *p)
	{
		p->~T();
	}
	static T *allocate(CustomAllocator &a, unsigned int size)
	{
		if (size > MAX_SIZE)
		{
			throw std::bad_alloc();
		}
		return a.ptr;
	}
	static void deallocate(CustomAllocator &a, T *p, unsigned int size)
	{
	}
	static constexpr int MAX_SIZE = 10000000;
	T *ptr;
};
TEST(VectorCustomAllocator, allocateTest)
{
	Vector<int, CustomAllocator<int>> v;
	v.reserve(4);
	ASSERT_EQ(curAlloc, v.data());
}