#include <lightning/gl_box.h>
#include <lightning/gl_button.h>
#include <lightning/gl_context.h>
#include <lightning/gl_mutable_state.h>
#include <lightning/gl_types.h>
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

    context.child<gl_box>(gl_box_settings(VERTICAL, 5))
    ([](gl_object& context)
    {

    });

    // We should save button between function calls
    context.child<gl_button>
    (
        gl_button_settings
        (
            "Switch",
            { .size = { 100, 100 } },
            [&show_box](){ show_box = !show_box; }
        )
    )([](gl_object& context)
    {
    });
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