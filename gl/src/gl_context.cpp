#include <lightning/exception.h>
#include <lightning/gl_context.h>
#include <lightning/gl_window.h>
#include <lightning/gtk/gtk.h>

namespace lightning
{

void gl_context::run()
{
    // **** begin g_application_run alternative ****
    // Setup
    GMainContext* context;

    context = g_main_context_default();
    expect(g_main_context_acquire(context));

    for (auto& [handle, app] : apps_)
    {
        GError* error = nullptr;
        if (!g_application_register(G_APPLICATION(handle), nullptr, &error))
        {
            g_printerr("Failed to register: %s\n", error->message);
            g_error_free(error);
            expect(false);
        }

        g_application_activate(G_APPLICATION(handle));
    }

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
}

void gl_context::shutdown()
{
    application_running = false;
}

} // namespace lightning