#include "plugin_common.h"
#include <cstdio>
#include <type_traits>
#include "export.h"

extern "C" {

PLUGIN_API void plugin_func();
PLUGIN_API std::unique_ptr<PluginInterface> get_plugin_interface();

}

static_assert(std::is_same_v<decltype(&plugin_func), PluginFunc>);
static_assert(std::is_same_v<decltype(&get_plugin_interface), PluginInterfaceFunc>);

void plugin_func()
{
    std::puts("Hello, from plugin!");
}

struct PluginImpl : PluginInterface {
    void greet() noexcept override {
        plugin_func();
    }

    ~PluginImpl() noexcept {
        std::puts("Destroying PluginImpl...");
    }
};

// If there can be only one instance of PluginImpl,
// just return a plain pointer to a static object.
std::unique_ptr<PluginInterface> get_plugin_interface()
{
    return std::make_unique<PluginImpl>();
}
