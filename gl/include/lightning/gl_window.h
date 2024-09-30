#pragma once

#include <lightning/gl_types.h>
#include <lightning/gl_object.h>

namespace lightning
{

struct gl_window_settings : gl_object_settings
{
    const std::string title;
    const gl_rect dims;

    gl_window_settings(std::string title, const gl_rect dims) noexcept : title(std::move(title)), dims(dims) {}

    bool operator==(const gl_object_settings& other_object) const override
    {
        const auto* other = dynamic_cast<const gl_window_settings*>(&other_object);
        if (!other)
        {
            return false;
        }

        return this->title == other->title
            && this->dims == other->dims;
    }
};

struct gl_window : gl_object
{
    gl_window(gl_window_settings&& settings, gl_context& context);

    gl_window(const gl_window&) = delete;

    gl_window(gl_window&&) = default;

    ~gl_window() override;

    void operator()(surface_type surface) override;

private:
    gl_window_settings settings_;
    gl_window_handle handle_;

    static void on_display();
};

} // namespace lightning