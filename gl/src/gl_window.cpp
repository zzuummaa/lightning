#include <lightning/exception.h>
#include <lightning/gl_window.h>
#include <lightning/gtk/gtk.h>

namespace lightning
{

gl_window::gl_window(gl_window_settings&& settings, gl_context& context)
    : gl_object(context), settings_(std::move(settings)), handle_(nullptr)
{
}

gl_window::~gl_window()
{
    if (handle_)
    {
        g_object_unref(handle_);
    }
}

void gl_window::operator()(const surface_type& surface)
{
    // Init window
    if (!handle_)
    {
        handle_ = gtk_window_new();
    }

    if (settings_.is_durty)
    {
        gtk_window_set_title(GTK_WINDOW(handle_), settings_.title.c_str());
        gtk_window_set_default_size(GTK_WINDOW(handle_), settings_.dims.size.width, settings_.dims.size.height);

        gtk_widget_show(GTK_WIDGET(handle_));

        settings_.is_durty = false;
    }

    surface(*this);
}

} // namespace lightning