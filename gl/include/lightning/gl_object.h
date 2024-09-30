#pragma once

#include <lightning/exception.h>
#include <lightning/gl_types.h>
#include <lightning/gl_util.h>

#include <memory>

namespace lightning
{

struct gl_object_settings
{
    bool is_durty;

    gl_object_settings() : is_durty(true) {}

    gl_object_settings(const gl_object_settings&) : is_durty(true) {}

    gl_object_settings(gl_object_settings&&) noexcept : is_durty(true) {}

    virtual ~gl_object_settings() = default;

    gl_object_settings& operator=(const gl_object_settings& other)
    {
        is_durty = *this != other;
        return *this;
    }

    gl_object_settings& operator=(gl_object_settings&& other) noexcept
    {
        is_durty = *this != other;
        return *this;
    }

    virtual bool operator==(const gl_object_settings& other) const
    {
        return true;
    }
};

struct gl_object
{
    using surface_type = std::function<void(gl_object&)>;

    explicit gl_object(gl_context& context) : context_(context) {}

    virtual ~gl_object() = default;

    template<typename _object, typename _settings>
    _object& child(_settings&& settings, const std::source_location position = std::source_location::current())
    {
        auto it = childs_.find(position);
        if (it == std::end(childs_))
        {
            auto ptr = std::make_unique<_object>(std::forward<_settings>(settings), context_);
            ptr->set_parent(this);
            auto [new_it, success] = childs_.emplace(position, std::move(ptr));
            expect(success);
            it = new_it;
        }
        expect(it->second->parent_, this);
        return *expect(dynamic_cast<_object*>(it->second.get()), nullptr, std::not_equal_to<>{});
    }

    virtual void operator()(const surface_type& surface)
    {
        if (surface) surface(*this);
    }

    void set_parent(gl_object* parent)
    {
        parent_ = parent;
    }

    gl_context& context() const
    {
        return context_;
    }

protected:
    gl_context& context_;

    std::unordered_map<std::source_location, std::unique_ptr<gl_object>> childs_;
    gl_object* parent_ = nullptr;
};

} // namespace lightning