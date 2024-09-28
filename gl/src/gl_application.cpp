#include <lightning/exception.h>
#include <lightning/gl_application.h>
#include <lightning/gtk/gtk.h>
#include <utility>

namespace lightning
{

void gl_application::activate(gl_app_handle, app_state* state)
{
    state->object_();
}

gl_application::gl_application(const char* app_id, surface_type surface, gl_context& context)
{
    auto handle = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);
    expect(handle);

    state_ = std::make_unique<app_state>(handle, gl_object(context, std::move(surface)));
    g_signal_connect(handle, "activate", G_CALLBACK(activate), state_.get());
}

gl_application::app_state::~app_state()
{
    if (handle_)
    {
        g_object_unref(handle_);
    }
}

} // namespace lightning