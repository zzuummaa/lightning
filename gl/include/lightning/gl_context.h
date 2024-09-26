#pragma once

#include <lightning/gl_mutable_state.h>
#include <lightning/exception.h>

#include <unordered_map>

namespace lightning
{

struct gl_window;

struct gl_context
{
    void register_window(gl_window& window);

    void unregister_window(gl_window& window);

    template<typename _value>
    gl_mutable_state<_value> register_mutable_state_if_not_exists(
        const std::source_location position, _value&& value)
    {
        auto it = mutable_states_.find(position);
        if (it == std::end(mutable_states_))
        {
            gl_mutable_state<_value> mutable_state(std::forward<_value>(value), position);
            const auto [new_it, success] = mutable_states_.try_emplace(position, static_state_cast<void>(mutable_state));
            expect(success);
            it = new_it;
        }

        return static_state_cast<_value>(it->second);
    }

private:
    std::unordered_map<int, gl_window*> windows;
    std::unordered_map<std::source_location, gl_mutable_state<void>> mutable_states_;
};

template<typename _value>
gl_mutable_state<_value> make_mutable_state(gl_context& context, _value&& value)
{
    return context.register_mutable_state_if_not_exists(std::source_location::current(), std::forward<_value>(value));
}

} // namespace lightning