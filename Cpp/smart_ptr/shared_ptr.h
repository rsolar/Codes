#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <algorithm>    // std::swap
#include <cassert>      // assert
#include <cstddef>      // std::nullptr_t

class shared_ptr_count {
public:
    shared_ptr_count() noexcept : pn(nullptr) {}

    void swap(shared_ptr_count &lhs) noexcept {
        std::swap(pn, lhs.pn);
    }

    long int use_count() const noexcept {
        long int count = 0;
        if (pn != nullptr) {
            count = *pn;
        }
        return count;
    }

    template<class U>
    void acquire(U *p) {
        if (p != nullptr) {
            if (pn == nullptr) {
                try {
                    pn = new long int(1);
                } catch (std::bad_alloc &) {
                    delete p;
                    throw;
                }
            } else {
                ++(*pn);
            }
        }
    }

    template<class U>
    void release(U *p) noexcept {
        if (pn != nullptr) {
            --(*pn);
            if (*pn == 0) {
                delete p;
                delete pn;
            }
            pn = nullptr;
        }
    }

public:
    long int *pn;
};

template<class T>
class shared_ptr {
public:
    typedef T element_type;

    constexpr shared_ptr() noexcept : px(nullptr), pn() {}

    constexpr shared_ptr(std::nullptr_t) noexcept : shared_ptr() {}

    explicit shared_ptr(T *p) : pn() {
        acquire(p);
    }

    shared_ptr(const shared_ptr &ptr) noexcept : pn(ptr.pn) {
        assert(ptr.px == nullptr || ptr.use_count() != 0);
        acquire(ptr.px);
    }

    template<class U>
    shared_ptr(const shared_ptr<U> &ptr) noexcept : pn(ptr.pn) {
        assert(ptr.px == nullptr || ptr.use_count() != 0);
        acquire(static_cast<typename shared_ptr<T>::element_type *>(ptr.px));
    }

    template<class U>
    shared_ptr(const shared_ptr<U> &ptr, T *p) : pn(ptr.pn) {
        acquire(p);
    }

    shared_ptr(shared_ptr &&ptr) noexcept : px(ptr.px) {
        pn.swap(ptr.pn);
        ptr.px = nullptr;
    }

    template<class U>
    shared_ptr(shared_ptr<U> &&ptr) noexcept : px(ptr.px) {
        pn.swap(ptr.pn);
        ptr.px = nullptr;
    }

    template<class U>
    shared_ptr(shared_ptr<U> &&ptr, T *p) : px(ptr.px) {
        pn.swap(ptr.pn);
        ptr.px = nullptr;
    }

    shared_ptr &operator=(const shared_ptr &ptr) noexcept {
        shared_ptr<T>(ptr).swap(*this);
        return *this;
    }

    template<class U>
    shared_ptr &operator=(const shared_ptr<U> &ptr) noexcept {
        shared_ptr<T>(ptr).swap(*this);
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&ptr) noexcept {
        shared_ptr<T>(static_cast<shared_ptr &&>(ptr)).swap(*this);
        return *this;
    }

    template<class U>
    shared_ptr &operator=(shared_ptr<U> &&ptr) noexcept {
        shared_ptr<T>(static_cast<shared_ptr<U> &&>(ptr)).swap(*this);
        return *this;
    }

    ~shared_ptr() noexcept {
        release();
    }

    void swap(shared_ptr &rhs) noexcept {
        std::swap(px, rhs.px);
        pn.swap(rhs.pn);
    }

    void reset() noexcept {
        release();
    }

    void reset(T *p) {
        assert(p == nullptr || px != p);
        release();
        acquire(p);
    }

    T *get() const noexcept {
        return px;
    }

    T &operator*() const noexcept {
        assert(px != nullptr);
        return *px;
    }

    T *operator->() const noexcept {
        assert(px != nullptr);
        return px;
    }

    long int use_count() const noexcept {
        return pn.use_count();
    }

    bool unique() const noexcept {
        return pn.use_count() == 1;
    }

    explicit operator bool() const noexcept {
        return pn.use_count() > 0;
    }

private:
    void acquire(T *p) {
        pn.acquire(p);
        px = p;
    }

    void release() noexcept {
        pn.release(px);
        px = nullptr;
    }

private:
    template<class U>
    friend
    class shared_ptr;

private:
    T *px;
    shared_ptr_count pn;
};

template<class T, class U>
inline bool operator==(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<class T, class U>
inline bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() != rhs.get();
}

template<class T, class U>
inline bool operator<=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template<class T, class U>
inline bool operator<(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() < rhs.get();
}

template<class T, class U>
inline bool operator>=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template<class T, class U>
inline bool operator>(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept {
    return lhs.get() > rhs.get();
}

template<class T>
inline void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}

template<class T, class U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &ptr) noexcept {
    return shared_ptr<T>(ptr, static_cast<typename shared_ptr<T>::element_type *>(ptr.get()));
};

template<class T, class U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &ptr) noexcept {
    T *p = dynamic_cast<typename shared_ptr<T>::element_type *>(ptr.get());
    if (p != nullptr) {
        return shared_ptr<T>(ptr, p);
    } else {
        return shared_ptr<T>();
    }
};

template<class T, class U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &ptr) noexcept {
    return shared_ptr<T>(ptr, const_cast<typename shared_ptr<T>::element_type *>(ptr.get()));
};

template<class T, class... Args>
inline shared_ptr<T> make_shared(Args &&... args) {
    T *p = new T(std::forward<Args>(args)...);
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return shared_ptr<T>(p);
}

#endif // SHARED_PTR_H
