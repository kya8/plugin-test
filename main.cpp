#include <cstdio>
#include <filesystem>
#include "dso.hpp"
#include "plugin_common.h"

namespace fs = std::filesystem;

namespace {

bool
do_things_with_plugin(const char* filename) noexcept
{
    Dso dso; // lifetime ends with this function
    dso.open(filename);
    if (!dso.is_open()) {
        return false;
    }
    const auto plugin_func = reinterpret_cast<PluginFunc>(dso.get_sym("plugin_func"));
    if (!plugin_func) {
        return false;
    }
    plugin_func();

    const auto get_plugin_interface = reinterpret_cast<PluginInterfaceFunc>(dso.get_sym("get_plugin_interface"));
    if (get_plugin_interface) {
        const auto interface = get_plugin_interface();
        interface->greet();
#ifdef _MSC_VER
        const auto plugin_destroy = reinterpret_cast<PluginInterfaceDestroyFunc>(dso.get_sym("destroy_plugin_interface"));
        plugin_destroy(interface);
#endif
    }
    return true;
}

}

int main(int argc, char** argv) try
{
    if (argc < 2) {
        std::fputs("Usage: plugin-test <plugin_dir>\n", stderr);
        return 1;
    }

    const fs::path plugin_dir = argv[1];
    int files_tried = 0;
    for (const auto& entry : fs::directory_iterator(plugin_dir)) {
#ifdef _WIN32
        const fs::path ext = ".dll";
#elif defined(__APPLE__) && defined(__MACH__)
        const fs::path ext = ".dylib";
#else
        const fs::path ext = ".so";
#endif
        if (entry.is_regular_file()) {
            const auto &path = entry.path();
            if (path.extension() == ext) {
                const auto filename = path.string();
                std::printf("Loading plugin %s\n", filename.c_str());
                if (!do_things_with_plugin(filename.c_str())) {
                    std::fprintf(stderr, "Cannot load plugin %s\n", filename.c_str());
                }
                files_tried += 1;
            }
        }
    }

    if (files_tried == 0) {
        std::fprintf(stderr, "No plugins were found in %s!\n", argv[1]);
        return 1;
    }
}
catch (const fs::filesystem_error& ex) {
    std::fprintf(stderr, "%s\n", ex.what());
    return 1;
}
