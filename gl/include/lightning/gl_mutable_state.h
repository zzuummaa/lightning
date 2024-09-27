#pragma once

#include <lightning/util.h>

#include <memory>
#include <source_location>

namespace lightning
{

template <typename _value>
struct gl_mutable_state
{
    struct dummy_value
    {
    };

    struct data
    {
        _value value_;
        std::source_location location_;
    };

    using value_type = std::conditional_t<std::is_void_v<_value>, dummy_value, _value>;
    using data_type = std::conditional_t<std::is_void_v<_value>, void, data>;

    gl_mutable_state() = default;
    gl_mutable_state(const gl_mutable_state&) = default;
    gl_mutable_state(gl_mutable_state&&) = default;

    gl_mutable_state(const std::shared_ptr<data_type>& pointer) : data_(pointer)
    {
    }

    explicit gl_mutable_state(const value_type& value, const std::source_location location = std::source_location::current())
        : data_(std::make_shared<data>(value, location))
    {
    }

    gl_mutable_state& operator=(const value_type& new_value)
    {
        data_->value_ = new_value;
        return *this;
    }

    operator const value_type&()
    {
        return data_->value_;
    }

    std::source_location& position()
    {
        return data_->location_;
    }

    const std::shared_ptr<data_type>& pointer()
    {
        return data_;
    }

private:
    std::shared_ptr<data_type> data_;
};

template<typename _t, typename _r>
gl_mutable_state<_t> static_state_cast(gl_mutable_state<_r>& state)
{
    const auto pointer = std::static_pointer_cast<typename gl_mutable_state<_t>::data_type>(state.pointer());
    return pointer;
}

} // namespace lightning

namespace std
{

template<>
struct hash<std::source_location>
{
    size_t operator()(const std::source_location location) const noexcept
    {
        return lightning::hash_combine(location.file_name(), location.function_name(), location.line(), location.column());
    }
};

constexpr bool operator==(const std::source_location& lhs, const std::source_location& rhs)
{
    return std::string_view{lhs.file_name()} == rhs.file_name()
        && std::string_view{lhs.function_name()} == rhs.function_name()
        && lhs.line() == rhs.line()
        && lhs.column() == rhs.column();
}

}

