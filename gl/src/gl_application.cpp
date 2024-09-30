#include <lightning/exception.h>
#include <lightning/gl_application.h>
#include <lightning/gtk/gtk.h>
#include <utility>

namespace lightning
{

void gl_application::activate(gl_object_handle, gl_application* app)
{
    (*app)(app->surface_);
}

gl_application::gl_application(const char* app_id, gl_context& context, surface_type surface)
    : gl_object(context), surface_(surface)
{
    handle_ = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);
    expect(handle_);
    g_signal_connect(handle_, "activate", G_CALLBACK(activate), this);
}

} // namespace lightning