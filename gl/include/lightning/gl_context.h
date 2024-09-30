#pragma once

#include <lightning/exception.h>
#include <lightning/gl_application.h>
#include <lightning/gl_mutable_state.h>
#include <lightning/gl_types.h>

#include <unordered_map>

namespace lightning
{

struct gl_context
{

    void register_window(gl_window& window);

    void unregister_window(gl_window& window);

    template<typename _value>
    gl_mutable_state<_value> register_mutable_state(
        const std::source_location position, _value&& value)
    {
        auto it = mutable_states_.find(position);
        if (it == std::end(mutable_states_))
        {
            gl_mutable_state<_value> mutable_state(std::forward<_value>(value));
            const auto [new_it, success] = mutable_states_.try_emplace(position, static_state_cast<void>(mutable_state));
            expect(success);
            it = new_it;
        }

        return static_state_cast<_value>(it->second);
    }

    template<typename _object, typename ..._args>
    void register_object(_args&& ...args)
    {
        if constexpr (std::is_base_of_v<gl_application, _object>)
        {
            auto ptr = make_gl_application(std::forward<_args>(args)...);
            apps_.emplace(ptr->handle(), std::move(ptr));
        }
        else
        {
            expect(false);
        }
    }

    void run();

    void shutdown();

private:
    std::unordered_map<gl_app_handle, std::unique_ptr<gl_application>> apps_;
    std::unordered_map<std::source_location, gl_mutable_state<void>> mutable_states_;

    bool application_running = false;
};

template<typename _context_holder_type, typename _value>
gl_mutable_state<_value> make_mutable_state(_context_holder_type& holder, _value&& value)
{
    return holder.context().register_mutable_state(std::source_location::current(), std::forward<_value>(value));
}

} // namespace lightning