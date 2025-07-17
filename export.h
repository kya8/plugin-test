#ifndef EXPORT_H_D15B5274_B5CC_4F5B_A28A_222576CB8FD5
#define EXPORT_H_D15B5274_B5CC_4F5B_A28A_222576CB8FD5

#if defined(_WIN32)
    #if defined(PLUGIN_SOURCE)
        #define PLUGIN_API __declspec(dllexport)
    #else
        #define PLUGIN_API __declspec(dllimport)
    #endif
#else
    #define PLUGIN_API __attribute__((visibility("default")))
#endif

#endif /* EXPORT_H_D15B5274_B5CC_4F5B_A28A_222576CB8FD5 */
