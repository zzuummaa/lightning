#include <gtk/gtk.h>

static bool application_running; // As use_count is private

static void print_hello(GtkWidget* widget, gpointer data) { g_print("Hello World\n"); }

// Add close_window event watcher to tell our application loop we should stop
static void close_window(void)
{
    printf("Window is closed\n");
    application_running = FALSE;
}

// Add timeout to make sure the application loop is unblocked once per second
static gboolean timeout(gpointer data)
{
    printf("timeout\n");
    return true;
}

static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget* window;
    GtkWidget *button;

    window = gtk_application_window_new(app);

    // Add destroy call-back so we know when window is closed.
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_window_set_child (GTK_WINDOW (window), button);

    gtk_widget_show(window);
}

int main(int argc, char** argv)
{
    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // g_timeout_add_seconds(1, timeout, NULL);

    // **** begin g_application_run alternative ****
    // Setup
    GMainContext* context;
    gboolean acquired_context;

    context = g_main_context_default();
    acquired_context = g_main_context_acquire(context);
    g_return_val_if_fail(acquired_context, 0);

    GError* error = NULL;
    if (!g_application_register(G_APPLICATION(app), NULL, &error))
    {
        g_printerr("Failed to register: %s\n", error->message);
        g_error_free(error);
        return 1;
    }

    g_application_activate(G_APPLICATION(app));

    // Main event loop
    application_running = true;
    int loop = 0;
    while (application_running)
    {
        bool may_block = TRUE;
        // may_block = TRUE: g_main_context_iteration blocks execution if no events are coming
        // may_block = FALSE: g_main_context_iterations processes pending events and continues
        g_main_context_iteration(context, may_block);
        printf("Loop %i\n", loop++);
    }

    // Release
    g_settings_sync();
    while (g_main_context_iteration(context, FALSE))
        ;
    g_main_context_release(context);
    // **** end g_application_run alternative ****

    g_object_unref(app);

    return status;
}