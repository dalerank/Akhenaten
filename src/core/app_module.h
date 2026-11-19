#pragma once

#include "core/core.h"

namespace application {

    struct AppTag {};
    using module_iterator_function_cb = void();
    using ModuleIterator = FuncLinkedList<module_iterator_function_cb*, AppTag>;

} // end namespace application

#define ANK_REGISTER_APPLICATION_MODULE(func)                                          \
    func();                                                                            \
    namespace application {                                                            \
        int ANK_CONFIG_PULL_VAR_NAME(func) = 1;                                        \
    }                                                                                  \
    static application::ModuleIterator ANK_CONFIG_CC1(module_handler, __LINE__)(func); \
    void func()
