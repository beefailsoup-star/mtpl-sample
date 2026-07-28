#include "memory_pool.h"
#include <cstdlib>
#include <new>
#include <algorithm>

MemoryPool::MemoryPool(size_t block_size, size_t initial_blocks)
    : block_size_(std::max(block_size, sizeof(Block)))
    , allocated_(0)
    , free_(nullptr) {
    for (size_t i = 0; i < initial_blocks; ++i)
        grow();
}

MemoryPool::~MemoryPool() {
    for (auto chunk : chunks_)
        std::free(chunk);
}

void* MemoryPool::allocate() {
    if (!free_) grow();
    Block* block = free_;
    free_ = free_->next;
    ++allocated_;
    return block;
}

void MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;
    Block* block = static_cast<Block*>(ptr);
    block->next = free_;
    free_ = block;
    --allocated_;
}

void MemoryPool::grow() {
    const size_t chunk_size = 4096;
    size_t blocks_per_chunk = chunk_size / block_size_;
    void* chunk = std::malloc(block_size_ * blocks_per_chunk);
    if (!chunk) throw std::bad_alloc();
    chunks_.push_back(chunk);
    char* start = static_cast<char*>(chunk);
    for (size_t i = 0; i < blocks_per_chunk; ++i) {
        Block* block = reinterpret_cast<Block*>(start + i * block_size_);
        block->next = free_;
        free_ = block;
    }
}
