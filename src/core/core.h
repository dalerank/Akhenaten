#pragma once

#include "smart_cast.h"
#include <type_traits>

#define ANK_CONFIG_CC0(a, b) a##b
#define ANK_CONFIG_CC1(a, b) ANK_CONFIG_CC0(a, b)
#define ANK_CONFIG_PULL_VAR_NAME(func) ANK_CONFIG_CC1(config_pull_, func)

#define STRINGIFY1(x) #x
#define STRINGIFY2(x) STRINGIFY1(x)
#define SOURCE_LOCATION __FILE__ ":" STRINGIFY2(__LINE__)

template<typename Func>
struct FuncLinkedList {
    FuncLinkedList(Func cb) : func(cb) {
        next = tail;
        tail = this;
    }

    Func func;
    FuncLinkedList *next = nullptr; // slist
    static inline FuncLinkedList *tail = nullptr;
};

#define NO_COPY_OR_ASSIGNMENT(classname) \
private: \
	classname( const classname& other ) = delete; \
	classname& operator=( const classname& other ) = delete; 

struct no_copy_assignment {
    no_copy_assignment(const no_copy_assignment &other) = delete;
    no_copy_assignment &operator=(const no_copy_assignment &other) = delete;
};