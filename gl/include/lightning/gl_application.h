#pragma once

#include <lightning/gl_object.h>

#include <memory>

namespace lightning
{

struct gl_application
{
    using surface_type = gl_object::surface_type;

    explicit gl_application(const char* app_id, surface_type surface, gl_context& context);

    gl_application(const gl_application&) = delete;
    gl_application(gl_application&&) = default;

    gl_app_handle handle()
    {
        return state_->handle_;
    }

private:
    struct app_state
    {
        ~app_state();

        gl_app_handle handle_;
        gl_object object_;
    };

    std::unique_ptr<app_state> state_;

    static void activate(gl_app_handle handle, app_state* context);
};

} // namespace lightning