#pragma once

#include <lightning/gl_object.h>
#include <lightning/gl_types.h>

namespace lightning
{

enum gl_orientation
{
    HORIZONTAL,
    VERTICAL
};

struct gl_box_settings : gl_object_settings
{
    gl_orientation orientation;
    const int spacing;

    explicit gl_box_settings(gl_orientation orientation, int spacing) : orientation(orientation), spacing(spacing) {}

    bool operator==(const gl_object_settings& other_object) const override
    {
        const auto* other = dynamic_cast<const gl_box_settings*>(&other_object);
        if (!other)
        {
            return false;
        }

        return this->orientation == other->orientation
            && this->spacing == other->spacing;
    }
};

struct gl_box : gl_object
{
    explicit gl_box(gl_box_settings&& settings, gl_context& context);

    ~gl_box() override;

    void operator()(const surface_type& surface) override;

private:
    gl_box_settings settings_;

    gl_object_handle handle_;
};

} // namespace lightning