#include "plugin_common.h"
#include <cstdio>
#include <type_traits>
#include "export.h"

extern "C" {

PLUGIN_API void plugin_func();

}

static_assert(std::is_same_v<decltype(&plugin_func), PluginFunc>);

void plugin_func()
{
    std::puts("Hello, from plugin!");
}
