#ifndef PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815
#define PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815

#ifdef __cplusplus
#include <memory>
#endif

typedef void(*PluginFunc)();

// Plain functions
// Or, functions to create ctx, and operate the ctx.
struct PluginContent {
    void(*greet)();
    const char* msg;
};

typedef const PluginContent* (*PluginContentFunc)();

#ifdef __cplusplus

// Suitable for plugin functionalities that require a ctx/instance.
class PluginInterface {
public:
    virtual void greet() = 0;
    virtual ~PluginInterface() = default;
};

// The caller program and the plugin dynlib can be built by different compilers,
// but to use the C++ interface, the C++ ABIs of both sides must be compatible.
// So if one is built with MSVC, we assume the other is built with MSVC.
#ifdef _MSC_VER
using PluginInterfaceFunc = PluginInterface* (*)();
using PluginInterfaceDestroyFunc = void(*)(PluginInterface*);
#else
using PluginInterfaceFunc = std::unique_ptr<PluginInterface> (*)();
#endif

#endif

#endif /* PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815 */
