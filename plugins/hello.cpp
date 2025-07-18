#include "plugin_common.h"
#include <cstdio>
#include <type_traits>
#include "export.h"

extern "C" {

PLUGIN_API void plugin_func();
#ifdef _MSC_VER // !! MSVC disallows extern C function with C++ class as return type.
PLUGIN_API PluginInterface* get_plugin_interface();
PLUGIN_API void destroy_plugin_interface(PluginInterface*);
#else
PLUGIN_API std::unique_ptr<PluginInterface> get_plugin_interface();
#endif
}

static_assert(std::is_same_v<decltype(&plugin_func), PluginFunc>);
static_assert(std::is_same_v<decltype(&get_plugin_interface), PluginInterfaceFunc>);
#ifdef _MSC_VER
static_assert(std::is_same_v<decltype(&destroy_plugin_interface), PluginInterfaceDestroyFunc>);
#endif

void plugin_func()
{
    std::puts("Hello, from plugin!");
}

namespace {

struct PluginImpl : PluginInterface {
    void greet() noexcept override {
        plugin_func();
    }

    PluginImpl() noexcept {
        std::puts("Creating PluginImpl...");
    }
    ~PluginImpl() noexcept override {
        std::puts("Destroying PluginImpl...");
    }
};

}

#ifdef _MSC_VER
PluginInterface* get_plugin_interface()
{
    return new PluginImpl{};
}

void destroy_plugin_interface(PluginInterface* p)
{
    delete p;
}
#else
// If there can be only one instance of PluginImpl,
// just return a plain pointer to a static object.
std::unique_ptr<PluginInterface> get_plugin_interface()
{
    return std::make_unique<PluginImpl>();
}
#endif
