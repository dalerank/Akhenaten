#pragma once

#include "mujs/mujs.h"

#include <cstddef>
#include <cstdint>

/** Binds &(obj).field to a JS CPTR property; anything else selects the deleted overload below. */
inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, int *ptr) {
    js_register_bound_int_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, bool *ptr) {
    js_register_bound_bool_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, float *ptr) {
    js_register_bound_float_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, int8_t *ptr) {
    js_register_bound_int8_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, uint8_t *ptr) {
    js_register_bound_uint8_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, uint16_t *ptr) {
    js_register_bound_uint16_property(J, name, ptr);
}

inline void ank_global_obj_bind_field(js_State *J, js_StringNode name, int16_t *ptr) {
    js_register_bound_int16_property(J, name, ptr);
}

template<typename T>
void ank_global_obj_bind_field(js_State *J, js_StringNode name, T *ptr) = delete;

/** Paste helpers for ANK_GLOBAL_OBJECT (generated from archive.h ANK_CONFIG_STRUCT_PASTE pattern). */
#define ANK_GLOBAL_OBJ_BIND(C, F) ank_global_obj_bind_field(J, js_intern(#F), &(C).F);

#define ANK_GLOBAL_OBJ_EXPAND(x) x
#define ANK_GLOBAL_OBJ_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define ANK_GLOBAL_OBJ_PASTE(...) ANK_GLOBAL_OBJ_EXPAND(ANK_GLOBAL_OBJ_GET_MACRO(__VA_ARGS__, \
        ANK_GLOBAL_OBJ_PASTE64, \
        ANK_GLOBAL_OBJ_PASTE63, \
        ANK_GLOBAL_OBJ_PASTE62, \
        ANK_GLOBAL_OBJ_PASTE61, \
        ANK_GLOBAL_OBJ_PASTE60, \
        ANK_GLOBAL_OBJ_PASTE59, \
        ANK_GLOBAL_OBJ_PASTE58, \
        ANK_GLOBAL_OBJ_PASTE57, \
        ANK_GLOBAL_OBJ_PASTE56, \
        ANK_GLOBAL_OBJ_PASTE55, \
        ANK_GLOBAL_OBJ_PASTE54, \
        ANK_GLOBAL_OBJ_PASTE53, \
        ANK_GLOBAL_OBJ_PASTE52, \
        ANK_GLOBAL_OBJ_PASTE51, \
        ANK_GLOBAL_OBJ_PASTE50, \
        ANK_GLOBAL_OBJ_PASTE49, \
        ANK_GLOBAL_OBJ_PASTE48, \
        ANK_GLOBAL_OBJ_PASTE47, \
        ANK_GLOBAL_OBJ_PASTE46, \
        ANK_GLOBAL_OBJ_PASTE45, \
        ANK_GLOBAL_OBJ_PASTE44, \
        ANK_GLOBAL_OBJ_PASTE43, \
        ANK_GLOBAL_OBJ_PASTE42, \
        ANK_GLOBAL_OBJ_PASTE41, \
        ANK_GLOBAL_OBJ_PASTE40, \
        ANK_GLOBAL_OBJ_PASTE39, \
        ANK_GLOBAL_OBJ_PASTE38, \
        ANK_GLOBAL_OBJ_PASTE37, \
        ANK_GLOBAL_OBJ_PASTE36, \
        ANK_GLOBAL_OBJ_PASTE35, \
        ANK_GLOBAL_OBJ_PASTE34, \
        ANK_GLOBAL_OBJ_PASTE33, \
        ANK_GLOBAL_OBJ_PASTE32, \
        ANK_GLOBAL_OBJ_PASTE31, \
        ANK_GLOBAL_OBJ_PASTE30, \
        ANK_GLOBAL_OBJ_PASTE29, \
        ANK_GLOBAL_OBJ_PASTE28, \
        ANK_GLOBAL_OBJ_PASTE27, \
        ANK_GLOBAL_OBJ_PASTE26, \
        ANK_GLOBAL_OBJ_PASTE25, \
        ANK_GLOBAL_OBJ_PASTE24, \
        ANK_GLOBAL_OBJ_PASTE23, \
        ANK_GLOBAL_OBJ_PASTE22, \
        ANK_GLOBAL_OBJ_PASTE21, \
        ANK_GLOBAL_OBJ_PASTE20, \
        ANK_GLOBAL_OBJ_PASTE19, \
        ANK_GLOBAL_OBJ_PASTE18, \
        ANK_GLOBAL_OBJ_PASTE17, \
        ANK_GLOBAL_OBJ_PASTE16, \
        ANK_GLOBAL_OBJ_PASTE15, \
        ANK_GLOBAL_OBJ_PASTE14, \
        ANK_GLOBAL_OBJ_PASTE13, \
        ANK_GLOBAL_OBJ_PASTE12, \
        ANK_GLOBAL_OBJ_PASTE11, \
        ANK_GLOBAL_OBJ_PASTE10, \
        ANK_GLOBAL_OBJ_PASTE9, \
        ANK_GLOBAL_OBJ_PASTE8, \
        ANK_GLOBAL_OBJ_PASTE7, \
        ANK_GLOBAL_OBJ_PASTE6, \
        ANK_GLOBAL_OBJ_PASTE5, \
        ANK_GLOBAL_OBJ_PASTE4, \
        ANK_GLOBAL_OBJ_PASTE3, \
        ANK_GLOBAL_OBJ_PASTE2, \
        ANK_GLOBAL_OBJ_PASTE1)(__VA_ARGS__))
#define ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_BIND(C, v1)
#define ANK_GLOBAL_OBJ_PASTE3(C, v1, v2) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE2(C, v2)
#define ANK_GLOBAL_OBJ_PASTE4(C, v1, v2, v3) ANK_GLOBAL_OBJ_PASTE2(C, v1)  ANK_GLOBAL_OBJ_PASTE3(C, v2, v3)
#define ANK_GLOBAL_OBJ_PASTE5(C, v1, v2, v3, v4) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE4(C, v2, v3, v4)
#define ANK_GLOBAL_OBJ_PASTE6(C, v1, v2, v3, v4, v5) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE5(C, v2, v3, v4, v5)
#define ANK_GLOBAL_OBJ_PASTE7(C, v1, v2, v3, v4, v5, v6) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE6(C, v2, v3, v4, v5, v6)
#define ANK_GLOBAL_OBJ_PASTE8(C, v1, v2, v3, v4, v5, v6, v7) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE7(C, v2, v3, v4, v5, v6, v7)
#define ANK_GLOBAL_OBJ_PASTE9(C, v1, v2, v3, v4, v5, v6, v7, v8) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE8(C, v2, v3, v4, v5, v6, v7, v8)
#define ANK_GLOBAL_OBJ_PASTE10(C, v1, v2, v3, v4, v5, v6, v7, v8, v9) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE9(C, v2, v3, v4, v5, v6, v7, v8, v9)
#define ANK_GLOBAL_OBJ_PASTE11(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE10(C, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define ANK_GLOBAL_OBJ_PASTE12(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE11(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define ANK_GLOBAL_OBJ_PASTE13(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE12(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define ANK_GLOBAL_OBJ_PASTE14(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE13(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define ANK_GLOBAL_OBJ_PASTE15(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE14(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define ANK_GLOBAL_OBJ_PASTE16(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE15(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define ANK_GLOBAL_OBJ_PASTE17(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE16(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define ANK_GLOBAL_OBJ_PASTE18(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE17(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define ANK_GLOBAL_OBJ_PASTE19(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE18(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define ANK_GLOBAL_OBJ_PASTE20(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE19(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define ANK_GLOBAL_OBJ_PASTE21(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE20(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define ANK_GLOBAL_OBJ_PASTE22(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE21(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define ANK_GLOBAL_OBJ_PASTE23(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE22(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define ANK_GLOBAL_OBJ_PASTE24(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE23(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define ANK_GLOBAL_OBJ_PASTE25(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE24(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define ANK_GLOBAL_OBJ_PASTE26(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE25(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define ANK_GLOBAL_OBJ_PASTE27(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE26(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define ANK_GLOBAL_OBJ_PASTE28(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE27(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define ANK_GLOBAL_OBJ_PASTE29(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE28(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define ANK_GLOBAL_OBJ_PASTE30(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE29(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define ANK_GLOBAL_OBJ_PASTE31(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE30(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define ANK_GLOBAL_OBJ_PASTE32(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE31(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define ANK_GLOBAL_OBJ_PASTE33(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE32(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define ANK_GLOBAL_OBJ_PASTE34(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE33(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define ANK_GLOBAL_OBJ_PASTE35(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE34(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define ANK_GLOBAL_OBJ_PASTE36(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE35(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define ANK_GLOBAL_OBJ_PASTE37(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE36(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define ANK_GLOBAL_OBJ_PASTE38(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE37(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define ANK_GLOBAL_OBJ_PASTE39(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE38(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define ANK_GLOBAL_OBJ_PASTE40(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE39(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define ANK_GLOBAL_OBJ_PASTE41(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE40(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define ANK_GLOBAL_OBJ_PASTE42(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE41(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define ANK_GLOBAL_OBJ_PASTE43(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE42(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define ANK_GLOBAL_OBJ_PASTE44(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE43(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define ANK_GLOBAL_OBJ_PASTE45(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE44(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define ANK_GLOBAL_OBJ_PASTE46(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE45(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define ANK_GLOBAL_OBJ_PASTE47(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE46(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define ANK_GLOBAL_OBJ_PASTE48(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE47(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define ANK_GLOBAL_OBJ_PASTE49(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE48(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define ANK_GLOBAL_OBJ_PASTE50(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE49(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define ANK_GLOBAL_OBJ_PASTE51(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE50(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define ANK_GLOBAL_OBJ_PASTE52(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE51(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define ANK_GLOBAL_OBJ_PASTE53(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE52(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define ANK_GLOBAL_OBJ_PASTE54(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE53(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define ANK_GLOBAL_OBJ_PASTE55(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE54(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define ANK_GLOBAL_OBJ_PASTE56(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE55(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define ANK_GLOBAL_OBJ_PASTE57(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE56(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define ANK_GLOBAL_OBJ_PASTE58(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE57(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define ANK_GLOBAL_OBJ_PASTE59(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE58(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define ANK_GLOBAL_OBJ_PASTE60(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE59(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define ANK_GLOBAL_OBJ_PASTE61(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE60(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define ANK_GLOBAL_OBJ_PASTE62(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE61(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define ANK_GLOBAL_OBJ_PASTE63(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE62(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define ANK_GLOBAL_OBJ_PASTE64(C, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) ANK_GLOBAL_OBJ_PASTE2(C, v1) ANK_GLOBAL_OBJ_PASTE63(C, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

