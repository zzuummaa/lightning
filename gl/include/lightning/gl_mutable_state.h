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
    };

    using value_type = std::conditional_t<std::is_void_v<_value>, dummy_value, _value>;
    using data_type = std::conditional_t<std::is_void_v<_value>, void, data>;

    gl_mutable_state() = default;
    gl_mutable_state(const gl_mutable_state&) = default;
    gl_mutable_state(gl_mutable_state&&) = default;

    gl_mutable_state(const std::shared_ptr<data_type>& pointer) : data_(pointer)
    {
    }

    explicit gl_mutable_state(const value_type& value)
        : data_(std::make_shared<data>(value))
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
