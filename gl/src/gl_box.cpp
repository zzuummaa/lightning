#include <lightning/gl_box.h>
#include <lightning/gtk/gtk.h>

namespace lightning
{

gl_box::gl_box(gl_box_settings&& settings, gl_context& context)
    : gl_object(context), settings_(std::move(settings)), handle_(nullptr)
{
}

gl_box::~gl_box()
{
    if (handle_)
    {
        g_object_unref(handle_);
    }
}

void gl_box::operator()(const surface_type& surface)
{
    if (!handle_)
    {
        handle_ = gtk_box_new(static_cast<GtkOrientation>(settings_.orientation), settings_.spacing);
    }

    if (settings_.is_durty)
    {
        gtk_box_set_spacing(GTK_BOX(handle_), settings_.spacing);
        gtk_widget_show(GTK_WIDGET(handle_));

        settings_.is_durty = false;
    }

    surface(*this);
}

} // namespace lightning