#include <lightning/gl_button.h>
#include <lightning/gtk/gtk.h>

namespace lightning
{

void gl_button::on_click(gl_button* button)
{
    button->settings_.on_click();
}

gl_button::gl_button(gl_button_settings&& settings, gl_context& context)
    : gl_object(context), settings_(settings), handle_(nullptr)
{
}

gl_button::~gl_button()
{
    if (handle_)
    {
        g_object_unref(handle_);
    }
}

void gl_button::operator()(const surface_type& surface)
{
    if (!handle_)
    {
        handle_ = gtk_button_new();
    }

    if (settings_.is_durty)
    {
        gtk_button_set_label(GTK_BUTTON(handle_), settings_.title.c_str());
        g_signal_connect (handle_, "clicked", G_CALLBACK(on_click), this);

        settings_.is_durty = false;
    }

    surface(*this);
}

} // namespace lightning