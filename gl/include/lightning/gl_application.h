#pragma once

#include <lightning/gl_object.h>

namespace lightning
{

struct gl_application : protected gl_object
{
    template<typename ..._args>
    friend std::unique_ptr<gl_application> make_gl_application(_args&& ...args);

    gl_application(const gl_application&) = delete;

    gl_object_handle handle()
    {
        return handle_;
    }

protected:
    explicit gl_application(const char* app_id, gl_context& context, surface_type surface);

    gl_application(gl_application&&) = default;

private:
    surface_type surface_;
    gl_object_handle handle_;

    static void activate(gl_object_handle handle, gl_application* context);
};

template<typename ..._args>
std::unique_ptr<gl_application> make_gl_application(_args&& ...args)
{
    return std::unique_ptr<gl_application>(new gl_application(std::forward<_args>(args)...));
}

} // namespace lightning