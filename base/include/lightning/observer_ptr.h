#pragma once

#include <type_traits>
#include <exception>

namespace lightning
{


class bad_observer_ptr_access : public std::exception
{
public:
    bad_observer_ptr_access() = default;
    ~bad_observer_ptr_access() override = default;

    const char* what() const noexcept override
    {
        return "bad observer_ptr access";
    }
};

template <typename _ptr>
  class observer_ptr
{
public:
    // publish our template parameter and variations thereof
    using element_type = _ptr;
    using pointer_type = std::add_pointer_t<_ptr>;
    using reference_type = std::add_lvalue_reference_t<_ptr>;

    constexpr observer_ptr() noexcept : ptr_() { }

    constexpr observer_ptr(std::nullptr_t) noexcept : ptr_() { }

    constexpr explicit observer_ptr(pointer_type ptr) noexcept : ptr_(ptr) { }

    // copying c'tors (in addition to compiler-generated copy c'tor)
    template <typename _Up,
      typename = typename std::enable_if<
        std::is_convertible<typename std::add_pointer<_Up>::type, pointer_type
        >::value
      >::type>
    constexpr observer_ptr(observer_ptr<_Up> other) noexcept : ptr_(other.get()) { }

    constexpr reference_type& value() &
    {
        if (ptr_) return *ptr_;
        throw bad_observer_ptr_access{};
    }

    constexpr const reference_type& value() const&
    {
        if (ptr_) return *ptr_;
        throw bad_observer_ptr_access{};
    }

    // 3.2.3, observer_ptr observers
    constexpr pointer_type get() const noexcept
    {
        return ptr_;
    }

    constexpr reference_type operator*() const
    {
        return *get();
    }

    constexpr pointer_type operator->() const noexcept
    {
        return get();
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator pointer_type() const noexcept
    {
        return get();
    }

    constexpr pointer_type release() noexcept
    {
        pointer_type tmp = get();
        reset();
        return tmp;
    }

    constexpr void reset(pointer_type ptr = nullptr) noexcept
    {
        ptr_ = ptr;
    }

    constexpr void swap(observer_ptr& other) noexcept
    {
        std::swap(ptr_, other.ptr_);
    }

private:
    pointer_type ptr_;
}; // observer_ptr<>

}