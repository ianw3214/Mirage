#include "allocator.hpp"

#include <cstdlib>

Allocator::Allocator(size_t size) : m_size(size) {
    m_data = malloc(size);
    m_ptr = m_data;
}

Allocator::Allocator(const Allocator& other) {
    m_size = other.m_size;
    m_data = other.m_data;
    m_ptr = m_data;
}

Allocator& Allocator::operator=(const Allocator& other) {
    m_size = other.m_size;
    m_data = other.m_data;
    m_ptr = m_data;
    return *this;
}

void* Allocator::allocate(size_t n, int flags) {
    void * ptr = m_ptr;
    m_ptr = static_cast<char*>(m_ptr) + n;
    return m_ptr;
}

void* Allocator::allocate(size_t n, size_t alignment, size_t offset, int flags) {
    // TODO: (Ian) Implement
    return nullptr;
}

void  Allocator::deallocate(void* p, size_t n) {
    // TODO: (Ian) Implement
}


bool operator==(const Allocator& a, const Allocator& b) {
    // TODO: (Ian) Implement
    return false;
}

bool operator!=(const Allocator& a, const Allocator& b) {
    // TODO: (Ian) Implement
    return false;
}