#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
#include <vector>
#include <cstdint>

class MemoryPool {
public:
    MemoryPool(size_t block_size, size_t initial_blocks = 64);
    ~MemoryPool();

    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;

    void* allocate();
    void deallocate(void* ptr);

    size_t block_size() const { return block_size_; }
    size_t allocated() const { return allocated_; }
    size_t available() const { return free_.size(); }

private:
    struct Block {
        union { Block* next; char data[1]; };
    };

    size_t block_size_;
    size_t allocated_;
    Block* free_;
    std::vector<void*> chunks_;

    void grow();
};

#endif
