#include <lightning/exception.h>
#include <lightning/gl_context.h>
#include <lightning/gl_window.h>

namespace lightning
{

void gl_context::register_window(gl_window& window)
{
    expect(windows.emplace(window.handle(), &window).second);
}

void gl_context::unregister_window(gl_window& window)
{
    expect(windows.erase(window.handle()), 0, std::greater{});
}

} // namespace lightning