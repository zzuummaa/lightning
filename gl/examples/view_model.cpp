#include <lightning/gl_types.h>
#include <lightning/gl_context.h>
#include <lightning/gl_mutable_state.h>
#include <lightning/gl_window.h>

using namespace lightning;

struct model
{
    bool show_rect;
};

void window_surface(gl_object& context)
{
    // We should save show_rect object betwen function calls
    auto show_box = make_mutable_state(context, false);

    gl_box box({ 0, 100, 100, 100 });

    // We should save button between function calls
    gl_button button({0, 0, 100, 100}, [&show_box] { show_box = !show_box; });
}

void app_surface(gl_object& context)
{
    context.child<gl_window>
    (
        gl_window_settings
        {
            "View model example",
            gl_rect{ .size = { .width = 200, .height = 200 } }
        }
    )(window_surface);
}

int main(int argc, char** argv)
{
    gl_context context;
    context.register_object<gl_application>("ru.zuma.view_model", context, app_surface);
    context.run();
}