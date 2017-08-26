#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <algorithm>    // std::swap
#include <cassert>      // assert
#include <cstddef>      // std::nullptr_t

template<class T>
class unique_ptr {
public:
    typedef T element_type;

    constexpr unique_ptr() noexcept : px(nullptr) {}

    constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr() {}

    explicit unique_ptr(T *p) noexcept : px(p) {}

    unique_ptr(const unique_ptr &) = delete;

    template<class U>
    unique_ptr(const unique_ptr<U> &) = delete;

    unique_ptr(unique_ptr &&ptr) noexcept : px(ptr.release()) {}

    template<class U>
    unique_ptr(unique_ptr<U> &&ptr) noexcept : px(ptr.release()) {}

    unique_ptr &operator=(const unique_ptr &) = delete;

    template<class U>
    unique_ptr &operator=(const unique_ptr<U> &) = delete;

    unique_ptr &operator=(unique_ptr &&ptr) noexcept {
        reset(ptr.release());
        return *this;
    }

    template<class U>
    unique_ptr &operator=(unique_ptr<U> &&ptr) noexcept {
        reset(ptr.release());
        return *this;
    }

    unique_ptr &operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    ~unique_ptr() noexcept {
        destroy();
    }

    void swap(unique_ptr &rhs) noexcept {
        std::swap(px, rhs.px);
    }

    void reset() noexcept {
        destroy();
    }

    void reset(T *p) noexcept {
        assert(p == nullptr || px != p);
        destroy();
        px = p;
    }

    T *release() noexcept {
        T *p = px;
        px = nullptr;
        return p;
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

    explicit operator bool() const noexcept {
        return px != nullptr;
    }

private:
    void destroy() noexcept {
        delete px;
        px = nullptr;
    }

private:
    template<class U>
    friend
    class unique_ptr;

private:
    T *px;
};

template<class T, class U>
inline bool operator==(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<class T, class U>
inline bool operator!=(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() != rhs.get();
}

template<class T, class U>
inline bool operator<=(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template<class T, class U>
inline bool operator<(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() < rhs.get();
}

template<class T, class U>
inline bool operator>=(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template<class T, class U>
inline bool operator>(const unique_ptr<T> &lhs, const unique_ptr<U> &rhs) noexcept {
    return lhs.get() > rhs.get();
}

template<class T>
inline void swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}

template<class T, class... Args>
inline unique_ptr<T> make_unique(Args &&... args) {
    T *p = new T(std::forward<Args>(args)...);
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    return unique_ptr<T>(p);
}

#endif // UNIQUE_PTR_H
