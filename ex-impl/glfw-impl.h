#ifndef __GLFW_IMPL_H__
#define __GLFW_IMPL_H__

#include "../external/glfw/include/GLFW/glfw3.h"

#if defined(_WIN32)
    #define _GLFW_WIN32
#endif
#if defined(__linux__)
    #if !defined(_GLFW_WAYLAND)     // Required for Wayland windowing
        #define _GLFW_X11
    #endif
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #define _GLFW_X11
#endif
#if defined(__APPLE__)
    #define _GLFW_COCOA
    #define _GLFW_USE_MENUBAR       // To create and populate the menu bar when the first window is created
    #define _GLFW_USE_RETINA        // To have windows use the full resolution of Retina displays
#endif
#if defined(__TINYC__)
    #define _WIN32_WINNT_WINXP      0x0501
#endif

// NOTE: _GLFW_MIR experimental platform not supported at this moment

#include "../external/glfw/src/context.c"
#include "../external/glfw/src/init.c"
#include "../external/glfw/src/input.c"
#include "../external/glfw/src/monitor.c"
#include "../external/glfw/src/vulkan.c"
#include "../external/glfw/src/window.c"
#include "../external/glfw/src/platform.c"

#if (defined _WIN32 | defined _WIN64)
    #include "../external/glfw/src/win32_init.c"
    #include "../external/glfw/src/win32_joystick.c"
    #include "../external/glfw/src/win32_monitor.c"
    #include "../external/glfw/src/win32_module.c"
    #include "../external/glfw/src/win32_time.c"
    #include "../external/glfw/src/win32_thread.c"
    #include "../external/glfw/src/win32_window.c"
    #include "../external/glfw/src/wgl_context.c"
    #include "../external/glfw/src/egl_context.c"
    #include "../external/glfw/src/osmesa_context.c"
#endif

#if (defined __linux__ || defined _linux || defined __linux)
    #if defined(_GLFW_WAYLAND)
        #include "../external/glfw/src/wl_init.c"
        #include "../external/glfw/src/wl_monitor.c"
        #include "../external/glfw/src/wl_window.c"
        #include "wayland-pointer-constraints-unstable-v1-client-protocol.c"
        #include "wayland-relative-pointer-unstable-v1-client-protocol.c"
        #endif
    #if defined(_GLFW_X11)
        #include "../external/glfw/src/x11_init.c"
        #include "../external/glfw/src/x11_monitor.c"
        #include "../external/glfw/src/x11_window.c"
        #include "../external/glfw/src/glx_context.c"
    #endif

    #include "../external/glfw/src/linux_joystick.c"
    #include "../external/glfw/src/posix_thread.c"
    #include "../external/glfw/src/posix_time.c"
    #include "../external/glfw/src/posix_module.c"
    #include "../external/glfw/src/posix_poll.c"
    #include "../external/glfw/src/xkb_unicode.c"
    #include "../external/glfw/src/egl_context.c"
    #include "../external/glfw/src/osmesa_context.c"
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #include "../external/glfw/src/x11_init.c"
    #include "../external/glfw/src/x11_monitor.c"
    #include "../external/glfw/src/x11_window.c"
    #include "../external/glfw/src/xkb_unicode.c"
    // TODO: Joystick implementation
    #include "../external/glfw/src/null_joystick.c"
    #include "../external/glfw/src/posix_time.c"
    #include "../external/glfw/src/posix_thread.c"
    #include "../external/glfw/src/glx_context.c"
    #include "../external/glfw/src/egl_context.c"
    #include "../external/glfw/src/osmesa_context.c"
#endif

#if defined(__APPLE__)
    #include "../external/glfw/src/cocoa_init.m"
    #include "../external/glfw/src/cocoa_joystick.m"
    #include "../external/glfw/src/cocoa_monitor.m"
    #include "../external/glfw/src/cocoa_window.m"
    #include "../external/glfw/src/cocoa_time.c"
    #include "../external/glfw/src/posix_thread.c"
    #include "../external/glfw/src/nsgl_context.m"
    #include "../external/glfw/src/egl_context.c"
    #include "../external/glfw/src/osmesa_context.c"
#endif

#endif // __GLFW_IMPL_H__
