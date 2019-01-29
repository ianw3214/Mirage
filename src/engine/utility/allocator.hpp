/* Default implementation of an allocator */
/* TODO: (Ian) Actually implement the allocation/deallocation functions - BUDDY ALLOCATOR */
#pragma once

static const size_t DEFAULT_SIZE = 1000;

class Allocator{

public:
    Allocator(size_t size = DEFAULT_SIZE);
    Allocator(const Allocator& other);

    Allocator& operator=(const Allocator& other);

    void* allocate(size_t n, int flags = 0);
    void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0);
    void  deallocate(void* p, size_t n);

private:

    size_t  m_size;
    void*   m_data;
    void*   m_ptr;

};

bool operator==(const Allocator& a, const Allocator& b);
bool operator!=(const Allocator& a, const Allocator& b);