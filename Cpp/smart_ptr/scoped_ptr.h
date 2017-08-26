#ifndef SCOPED_PTR_H
#define SCOPED_PTR_H

#include <algorithm>    // std::swap
#include <cassert>      // assert
#include <cstddef>      // std::nullptr_t

template<class T>
class scoped_ptr {
public:
    typedef T element_type;

    constexpr scoped_ptr() noexcept : px(nullptr) {}

    constexpr scoped_ptr(std::nullptr_t) noexcept : scoped_ptr() {}

    explicit scoped_ptr(T *p) noexcept : px(p) {}

    scoped_ptr(const scoped_ptr &) = delete;

    scoped_ptr(scoped_ptr &&) = delete;

    scoped_ptr &operator=(const scoped_ptr &) = delete;

    scoped_ptr &operator=(scoped_ptr &&) = delete;

    ~scoped_ptr() {
        delete px;
    }

    void swap(scoped_ptr &rhs) noexcept {
        std::swap(px, rhs.px);
    }

    void reset() {
        scoped_ptr<T>(nullptr).swap(*this);
    }

    void reset(T *p) {
        assert(p == nullptr || p != px);
        scoped_ptr<T>(p).swap(*this);
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

    operator bool() const noexcept {
        return px != nullptr;
    }

private:
    T *px;
};

template<class T, class U>
inline bool operator==(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<class T, class U>
inline bool operator!=(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() != rhs.get();
}

template<class T, class U>
inline bool operator<=(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template<class T, class U>
inline bool operator<(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() < rhs.get();
}

template<class T, class U>
inline bool operator>=(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template<class T, class U>
inline bool operator>(const scoped_ptr<T> &lhs, const scoped_ptr<U> &rhs) noexcept {
    return lhs.get() > rhs.get();
}

template<class T>
inline void swap(scoped_ptr<T> &lhs, scoped_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}

#endif // SCOPED_PTR_H
