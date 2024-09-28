#include <lightning/exception.h>
#include <lightning/gl_window.h>
#include <lightning/gtk/gtk.h>

namespace lightning
{

gl_window::gl_window(
    gl_context& context, const gl_rect& dims, const char* title)
    : gl_object(context), dims_(dims), title_(title)
{
}

void gl_window::operator()()
{
    // Get current coroutine from context
    // Add window to coroutine storage

    // Init window
    GtkWidget* window  = gtk_window_new();

    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), dims_.size.width, dims_.size.height);

    gtk_widget_show(window);

    // Destroy window
    // g_object_unref(window);
}

} // namespace lightning