#include <lightning/async_task.h>
#include <lightning/gl_types.h>
#include <lightning/gl_context.h>
#include <lightning/gl_loop.h>
#include <lightning/gl_mutable_state.h>
#include <lightning/gl_window.h>

using namespace lightning;

struct model
{
    bool show_rect;
};

async_task<gl_context> window_surface(gl_context& context)
{
    // We should save show_rect object betwen function calls
    auto show_box = make_mutable_state(context, false);

    // We should save button between function calls
    gl_button button
    (
        {0, 0, 100, 100},
        [&show_box](){ show_box = !show_box; }
    );

    gl_box box({ 0, 100, 100, 100 });

    co_return;
}

int main(int argc, char** argv)
{
    gl_init(&argc, argv);

    gl_context context;

    gl_window window(
        { 0, 0, 300, 300 },
        "View model example",
        context
    );
    window.set_surface(window_surface);

    gl_loop::poll();
}