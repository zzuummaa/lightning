#pragma once

#include "gl_context.h"

#include <lightning/gl_object.h>

namespace lightning
{

struct gl_button_settings : gl_object_settings
{
    using on_click_type = std::function<void()>;

    const std::string title;
    const gl_rect dims;
    const on_click_type on_click;

    gl_button_settings(std::string title, gl_rect dims, on_click_type&& on_click)
        : title(std::move(title)), dims(dims), on_click(std::move(on_click)) {}
};

struct gl_button : gl_object
{
    explicit gl_button(gl_button_settings&& settings, gl_context& context);

    ~gl_button() override;

    void operator()(const surface_type& surface) override;

private:
    gl_button_settings settings_;

    gl_object_handle handle_;

    static void on_click(gl_button* button);
};


} // namespace lightning