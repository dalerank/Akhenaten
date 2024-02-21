#pragma once

#define ANK_CONFIG_CC0(a, b) a##b
#define ANK_CONFIG_CC1(a, b) ANK_CONFIG_CC0(a, b)
#define ANK_CONFIG_PULL_VAR_NAME(func) ANK_CONFIG_CC1(config_pull, func)

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