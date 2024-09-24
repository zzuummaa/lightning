#pragma once

namespace lightning
{

template <typename _value>
struct gl_mutable_state
{
    using value_type = _value;

    gl_mutable_state(const value_type& value) : value_(value) {}

    gl_mutable_state& operator=(const value_type& new_value)
    {
        value_ = new_value;
        return *this;
    }

    operator const value_type&()
    {
        return value_;
    }
private:
    value_type value_;
};

} // namespace lightning