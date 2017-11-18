#if !defined(VERTOR_INTERFACE_TYPE)
#error vector type is not define
#else
Vector() noexcept(std::is_nothrow_default_constructible<VERTOR_INTERFACE_TYPE>::value);
Vector(uint32 size) noexcept(std::is_nothrow_default_constructible<VERTOR_INTERFACE_TYPE>::value);
~Vector() noexcept;
void push_back(const VERTOR_INTERFACE_TYPE& val);
void push_back(VERTOR_INTERFACE_TYPE&& val);
void insert(uint32 index, const VERTOR_INTERFACE_TYPE& val);
void insert(uint32 index, VERTOR_INTERFACE_TYPE&& val);
void insert(uint32 index,uint32 size, const VERTOR_INTERFACE_TYPE& val);
void insert(uint32 index,uint32 size, VERTOR_INTERFACE_TYPE&& val);
void pop_back() noexcept;
void erase(uint32 index) noexcept;
void erase(uint32 startIndex, uint32 lastIndex) noexcept;
void resize(uint32 newSize);
void reserve(uint32 newMaxSize);
void clear() noexcept;
uint32 size() const noexcept;
uint32 capacity() const noexcept;
const VERTOR_INTERFACE_TYPE *data() const;
VERTOR_INTERFACE_TYPE *data();
bool empty() const;
VERTOR_INTERFACE_TYPE& operator[](uint32 index) noexcept;
const VERTOR_INTERFACE_TYPE& operator[](uint32 index) const noexcept;
VERTOR_INTERFACE_TYPE& at(uint32 index) noexcept;
const VERTOR_INTERFACE_TYPE& at(uint32 index) const noexcept;
VERTOR_INTERFACE_TYPE& front() noexcept;
const VERTOR_INTERFACE_TYPE& front() const noexcept;
VERTOR_INTERFACE_TYPE& back() noexcept;
const VERTOR_INTERFACE_TYPE& back() const noexcept;
#endif