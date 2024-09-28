#pragma once

#include <lightning/gl_types.h>

namespace lightning
{

struct gl_object
{
    using surface_type = std::function<void(gl_context&)>;

    explicit gl_object(gl_context& context, surface_type surface = {}) : context_(context), surface_(std::move(surface)) {}

    void operator()()
    {
        if (surface_) surface_(context_);
    }
protected:
    gl_context& context_;
    surface_type surface_;
};

} // namespace lightning