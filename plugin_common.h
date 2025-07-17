#ifndef PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815
#define PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815

#ifdef __cplusplus
#include <memory>
#endif

typedef void(*PluginFunc)();

struct PluginContent {
    void(*greet)();
    const char* msg;
};

typedef const PluginContent* (*PluginContentFunc)();

#ifdef __cplusplus

class PluginInterface {
public:
    virtual void greet() = 0;
    virtual ~PluginInterface() = default;
};

using PluginInterfaceFunc = std::unique_ptr<PluginInterface> (*)();

#endif

#endif /* PLUGIN_COMMON_H_DA7572C6_4FEC_425E_BD88_D6E90ADA6815 */
