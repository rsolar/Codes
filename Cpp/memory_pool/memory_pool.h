#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstdlib>
#include <iostream>

class DefaultMemoryAllocator {
public:
    static inline void *Allocate(size_t size) {
        return ::operator new(size, ::std::nothrow);
    }

    static inline void Deallocate(void *pointer, size_t size) {
        ::operator delete(pointer);
    }
};

template<typename T, class TMemoryAllocator = DefaultMemoryAllocator>
class MemoryPool {
public:
    explicit MemoryPool(size_t initial_capacity = 32, size_t max_block_length = 1000000)
            : last_deleted_(nullptr),
              count_in_node_(0),
              node_capacity_(initial_capacity),
              first_node_(initial_capacity),
              max_block_length_(max_block_length) {
        if (max_block_length < 1) {
            throw std::invalid_argument("max_block_length must be at least 1.");
        }
        node_memory_ = first_node_.memory_;
        last_node_ = &first_node_;
    }

    MemoryPool(const MemoryPool<T, TMemoryAllocator> &) = delete;

    MemoryPool(MemoryPool<T, TMemoryAllocator> &&) noexcept = default;

    void operator=(const MemoryPool<T, TMemoryAllocator> &) = delete;

    MemoryPool &operator=(MemoryPool<T, TMemoryAllocator> &&) noexcept = default;

    ~MemoryPool() {
        Node *node = first_node_.next_node_;
        while (node) {
            Node *next_node = node->next_node_;
            delete node;
            node = next_node;
        }
    }

    T *New() {
        T *result = NewWithoutInitializing();
        new(result) T();
        return result;
    }

    // This method is useful if you want to call a non-default constructor.
    // It should be used like this:
    // new (pool.NewWithoutInitializing()) ObjectType(...parameters...);
    T *NewWithoutInitializing() {
        if (last_deleted_) {
            T *result = last_deleted_;
            last_deleted_ = *((T **) last_deleted_);
            return result;
        }

        if (count_in_node_ >= node_capacity_) {
            AllocateNewNode();
        }

        char *result = (char *) node_memory_;
        result += count_in_node_ * item_size_;
        count_in_node_++;
        return (T *) result;
    }

    void Delete(T *pointer) {
        pointer->~T();
        DeleteWithoutDestroying(pointer);
    }

    void DeleteWithoutDestroying(T *pointer) {
        *((T **) pointer) = last_deleted_;
        last_deleted_ = pointer;
    }

private:
    struct Node {
        Node(size_t capacity)
                : capacity_(capacity),
                  next_node_(nullptr) {
            if (capacity < 1) {
                throw std::invalid_argument("Node capacity must be at least 1.");
            }
            memory_ = TMemoryAllocator::Allocate(item_size_ * capacity);
            if (memory_ == nullptr) {
                throw std::bad_alloc();
            }
        }

        Node(const Node &) = delete;

        Node(Node &&) noexcept = default;

        Node &operator=(const Node &) = delete;

        Node &operator=(Node &&) noexcept = default;

        ~Node() {
            TMemoryAllocator::Deallocate(memory_, item_size_ * capacity_);
        }

        void *memory_;
        size_t capacity_;
        Node *next_node_;
    };

    void AllocateNewNode() {
        size_t size = count_in_node_;
        if (size < max_block_length_) {
            size *= 2;
            if (size < count_in_node_) {
                throw std::overflow_error("MemoryPool's size became too big.");
            }
        }
        if (size >= max_block_length_) {
            size = max_block_length_;
        }

        Node *new_node = new Node(size);
        last_node_->next_node_ = new_node;
        last_node_ = new_node;
        node_memory_ = new_node->memory_;
        count_in_node_ = 0;
        node_capacity_ = size;
    }

    void *node_memory_;
    size_t count_in_node_;
    size_t node_capacity_;
    size_t max_block_length_;
    Node first_node_;
    Node *last_node_;
    T *last_deleted_;

    static const size_t item_size_;
};

template<typename T, class TMemoryAllocator>
const size_t MemoryPool<T, TMemoryAllocator>::item_size_ =
        ((sizeof(T) + sizeof(void *) - 1) / sizeof(void *)) * sizeof(void *);

#endif //MEMORY_POOL_H
