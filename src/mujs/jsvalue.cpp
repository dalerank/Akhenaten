#include "jsi.h"
#include "jslex.h"
#include "jscompile.h"
#include "jsvalue.h"
#include "jsbuiltin.h"
#include "utf.h"

#include "core/profiler.h"

static js_StringNode property_length = js_intern("length");
static js_StringNode property_constructor = js_intern("constructor");
static js_StringNode property_prototype = js_intern("prototype");
static js_StringNode property_toString = js_intern("toString");
static js_StringNode property_valueOf = js_intern("valueOf");
static js_StringNode property_atobject = js_intern("[object]");

#define JSV_ISSTRING(v) (v->type == JS_TSHRSTR || v->type == JS_TMEMSTR || v->type == JS_TLITSTR)
inline pcstr JSV_TOSTRING(js_Value* v) {
    return v->type == JS_TSHRSTR   ? js_strnode_cstr(v->u.shrstr)
           : v->type == JS_TLITSTR ? js_strnode_cstr(v->u.litstr)
           : v->type == JS_TMEMSTR ? js_strnode_cstr(v->u.memstr)
                                   : "";
}

int jsV_numbertointeger(double n) {
    double sign = n < 0 ? -1 : 1;
    if (isnan(n))
        return 0;
    if (n == 0 || isinf(n))
        return n;
    return sign * floor(fabs(n));
}

int jsV_numbertoint32(double n) {
    double two32 = 4294967296.0;
    double two31 = 2147483648.0;

    if (!isfinite(n) || n == 0)
        return 0;

    n = fmod(n, two32);
    n = n >= 0 ? floor(n) : ceil(n) + two32;
    if (n >= two31)
        return n - two32;
    else
        return n;
}

unsigned int jsV_numbertouint32(double n) {
    return (unsigned int)jsV_numbertoint32(n);
}

short jsV_numbertoint16(double n) {
    return jsV_numbertoint32(n);
}

unsigned short jsV_numbertouint16(double n) {
    return jsV_numbertoint32(n);
}

/* obj.toString() */
static int jsV_toString(js_State* J, js_Object* obj) {
    js_pushobject(J, obj);
    J->getproperty(-1, property_toString);
    if (J->iscallable(-1)) {
        js_rot2(J);
        J->call(0);
        if (js_isprimitive(J, -1))
            return 1;
        js_pop(J, 1);
        return 0;
    }
    js_pop(J, 2);
    return 0;
}

/* obj.valueOf() */
static int jsV_valueOf(js_State* J, js_Object* obj) {
    js_pushobject(J, obj);
    J->getproperty(-1, property_valueOf);
    if (J->iscallable(-1)) {
        js_rot2(J);
        J->call(0);
        if (js_isprimitive(J, -1))
            return 1;
        js_pop(J, 1);
        return 0;
    }
    js_pop(J, 2);
    return 0;
}

/* ToPrimitive() on a value */
void jsV_toprimitive(js_State* J, js_Value* v, int preferred) {
    js_Object* obj;

    if (v->type != JS_TOBJECT)
        return;

    obj = v->u.object;

    if (obj->type == JS_CPTR) {
        void* p = obj->u.p.ptr;
        switch (obj->u.p.ptype) {
        case JS_PTR_INT:
            v->type = JS_TNUMBER;
            v->u.number = *(int*)p;
            return;
        case JS_PTR_BOOL:
            v->type = JS_TBOOLEAN;
            v->u.boolean = *(bool*)p;
            return;
        case JS_PTR_FLOAT:
            v->type = JS_TNUMBER;
            v->u.number = (double)*(float*)p;
            return;
        default:
            return;
        }
    }

    if (preferred == JS_HNONE)
        preferred = obj->type == JS_CDATE ? JS_HSTRING : JS_HNUMBER;

    if (preferred == JS_HSTRING) {
        if (jsV_toString(J, obj) || jsV_valueOf(J, obj)) {
            *v = *js_tovalue(J, -1);
            js_pop(J, 1);
            return;
        }
    } else {
        if (jsV_valueOf(J, obj) || jsV_toString(J, obj)) {
            *v = *js_tovalue(J, -1);
            js_pop(J, 1);
            return;
        }
    }

    v->type = JS_TLITSTR;
    v->u.litstr = property_atobject;
    return;
}

/* ToBoolean() on a value */
int jsV_toboolean(js_State* J, js_Value* v) {
    switch (v->type) {
    default:
    case JS_TSHRSTR:
        return !v->u.shrstr->value.empty();
    case JS_TUNDEFINED:
        return 0;
    case JS_TNULL:
        return 0;
    case JS_TBOOLEAN:
        return v->u.boolean;
    case JS_TNUMBER:
        return v->u.number != 0 && !isnan(v->u.number);
    case JS_TLITSTR:
        return !v->u.litstr->value.empty();
    case JS_TMEMSTR:
        return !v->u.memstr->value.empty();
    case JS_TOBJECT: {
        js_Object* obj = v->u.object;
        if (obj->type == JS_CPTR) {
            void* p = obj->u.p.ptr;
            switch (obj->u.p.ptype) {
            case JS_PTR_INT:
                return *(int*)p != 0;
            case JS_PTR_BOOL:
                return *(bool*)p != 0;
            case JS_PTR_FLOAT:
                return *(float*)p != 0;
            default:
                return 1;
            }
        }
        return 1;
    }
    }
}

const char* js_itoa(char* out, int a) {
    char buf[32], *s = out;
    int i = 0;
    while (a) {
        buf[i++] = (a % 10) + '0';
        a /= 10;
    }
    if (i == 0)
        buf[i++] = '0';
    while (i > 0)
        *s++ = buf[--i];
    *s = 0;
    return out;
}

double js_stringtofloat(const char* s, char** ep) {
    char* end;
    double n;
    const char* e = s;
    int isflt = 0;
    if (*e == '+' || *e == '-')
        ++e;
    while (*e >= '0' && *e <= '9')
        ++e;
    if (*e == '.') {
        ++e;
        isflt = 1;
    }
    while (*e >= '0' && *e <= '9')
        ++e;
    if (*e == 'e' || *e == 'E') {
        ++e;
        if (*e == '+' || *e == '-')
            ++e;
        while (*e >= '0' && *e <= '9')
            ++e;
        isflt = 1;
    }
    if (isflt || e - s > 9)
        n = js_strtod(s, &end);
    else
        n = strtol(s, &end, 10);
    if (end == e) {
        *ep = (char*)e;
        return n;
    }
    *ep = (char*)s;
    return 0;
}

/* ToNumber() on a string */
double jsV_stringtonumber(js_State* J, const char* s) {
    char* e;
    double n;
    while (jsY_iswhite(*s) || jsY_isnewline(*s)) {
        ++s;
    }

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X') && s[2] != 0)
        n = strtol(s + 2, &e, 16);
    else if (!strncmp(s, "Infinity", 8))
        n = INFINITY, e = (char*)s + 8;
    else if (!strncmp(s, "+Infinity", 9))
        n = INFINITY, e = (char*)s + 9;
    else if (!strncmp(s, "-Infinity", 9))
        n = -INFINITY, e = (char*)s + 9;
    else
        n = js_stringtofloat(s, &e);

    while (jsY_iswhite(*e) || jsY_isnewline(*e)) {
        ++e;
    }

    if (*e) {
        return NAN;
    }

    return n;
}

/* ToNumber() on a value */
double jsV_tonumber(js_State* J, js_Value* v) {
    switch (v->type) {
    default:
    case JS_TSHRSTR:
        return jsV_stringtonumber(J, js_strnode_cstr(v->u.shrstr));
    case JS_TUNDEFINED:
        return NAN;
    case JS_TNULL:
        return 0;
    case JS_TBOOLEAN:
        return v->u.boolean;
    case JS_TNUMBER:
        return v->u.number;
    case JS_TLITSTR:
        return jsV_stringtonumber(J, js_strnode_cstr(v->u.litstr));
    case JS_TMEMSTR:
        return jsV_stringtonumber(J, js_strnode_cstr(v->u.memstr));
    case JS_TOBJECT: {
        js_Object* obj = v->u.object;
        if (obj->type == JS_CPTR) {
            void* p = obj->u.p.ptr;
            switch (obj->u.p.ptype) {
            case JS_PTR_INT:
                return *(int*)p;
            case JS_PTR_BOOL:
                return *(bool*)p ? 1 : 0;
            case JS_PTR_FLOAT:
                return (double)*(float*)p;
            default:
                return 0;
            }
        }
        jsV_toprimitive(J, v, JS_HNUMBER);
        return jsV_tonumber(J, v);
    }
    }
}

double jsV_tointeger(js_State* J, js_Value* v) {
    return jsV_numbertointeger(jsV_tonumber(J, v));
}

/* ToString() on a number */
const char* jsV_numbertostring(js_State* J, char buf[32], double f) {
    OZZY_PROFILER_FUNCTION();

    char digits[32], *p = buf, *s = digits;
    int exp, neg, ndigits, point;

    if (isnan(f))
        return "NaN";
    if (isinf(f))
        return f < 0 ? "-Infinity" : "Infinity";
    if (f == 0)
        return "0";

    js_dtoa(f, digits, &exp, &neg, &ndigits);
    point = ndigits + exp;

    if (neg)
        *p++ = '-';

    if (point < -5 || point > 21) {
        *p++ = *s++;
        if (ndigits > 1) {
            int n = ndigits - 1;
            *p++ = '.';
            while (n--)
                *p++ = *s++;
        }
        js_fmtexp(p, point - 1);
    }

    else if (point <= 0) {
        *p++ = '0';
        *p++ = '.';
        while (point++ < 0)
            *p++ = '0';
        while (ndigits-- > 0)
            *p++ = *s++;
        *p = 0;
    }

    else {
        while (ndigits-- > 0) {
            *p++ = *s++;
            if (--point == 0 && ndigits > 0)
                *p++ = '.';
        }
        while (point-- > 0)
            *p++ = '0';
        *p = 0;
    }

    return buf;
}

static js_StringNode property_undefined = js_intern("undefined");
static js_StringNode property_null = js_intern("null");
static js_StringNode property_true = js_intern("true");
static js_StringNode property_false = js_intern("false");

/* ToString() on a value */
const js_StringNode jsV_tostring(js_State* J, js_Value* v) {
    OZZY_PROFILER_FUNCTION();

    char buf[32];
    const char* p;
    switch (v->type) {
    default:
    case JS_TSHRSTR:
        return v->u.shrstr;
    case JS_TUNDEFINED:
        return property_undefined;
    case JS_TNULL:
        return property_null;
    case JS_TBOOLEAN:
        return v->u.boolean ? property_true : property_false;
    case JS_TLITSTR:
        return v->u.litstr;
    case JS_TMEMSTR:
        return v->u.memstr;
    case JS_TNUMBER:
        /* js_StringNode is an interned pointer; do not reuse JS_TSHRSTR without assigning it. */
        p = jsV_numbertostring(J, buf, v->u.number);
        return js_intern(p);
    case JS_TOBJECT:
        jsV_toprimitive(J, v, JS_HSTRING);
        return jsV_tostring(J, v);
    }
}

/* Objects */

static js_Object* jsV_newboolean(js_State* J, int v) {
    js_Object* obj = jsV_newobject(J, JS_CBOOLEAN, J->Boolean_prototype);
    obj->u.boolean = v;
    return obj;
}

static js_Object* jsV_newnumber(js_State* J, double v) {
    js_Object* obj = jsV_newobject(J, JS_CNUMBER, J->Number_prototype);
    obj->u.number = v;
    return obj;
}

js_Object* jsV_newvec2i(js_State* J, int x, int y) {
    js_Object* obj = jsV_newobject(J, JS_CVEC2I, J->Vec2i_prototype);
    obj->u.vec2.x = x;
    obj->u.vec2.y = y;
    return obj;
}

static js_Object* jsV_newstring(js_State* J, const js_StringNode v) {
    js_Object* obj = jsV_newobject(J, JS_CSTRING, J->String_prototype);
    obj->u.s.string = v; /* TODO: js_String */
    obj->u.s.length = utflen(js_strnode_cstr(v));
    return obj;
}

static js_Object* jsV_newstring(js_State* J, const char* v) {
    js_Object* obj = jsV_newobject(J, JS_CSTRING, J->String_prototype);
    obj->u.s.string = js_intern(v); /* TODO: js_String */
    obj->u.s.length = utflen(v);
    return obj;
}

/* ToObject() on a value */
js_Object* js_State::toobject(js_Value* v) {
    OZZY_PROFILER_FUNCTION();

    auto J = this;
    switch (v->type) {
    default:
    case JS_TSHRSTR:
        return jsV_newstring(J, v->u.shrstr);
    case JS_TUNDEFINED:
        js_typeerror_detailed(J, "undefined", "object");
    case JS_TNULL:
        js_typeerror_detailed(J, "null", "object");
    case JS_TBOOLEAN:
        return jsV_newboolean(J, v->u.boolean);
    case JS_TNUMBER:
        return jsV_newnumber(J, v->u.number);
    case JS_TLITSTR:
        return jsV_newstring(J, v->u.litstr);
    case JS_TMEMSTR:
        return jsV_newstring(J, v->u.memstr);
    case JS_TOBJECT:
        return v->u.object;
    }
}

void js_newobject(js_State* J) {
    OZZY_PROFILER_FUNCTION();

    js_pushobject(J, jsV_newobject(J, JS_COBJECT, J->Object_prototype));
}

void js_newarray(js_State* J) {
    js_pushobject(J, jsV_newobject(J, JS_CARRAY, J->Array_prototype));
}

void js_newboolean(js_State* J, int v) {
    js_pushobject(J, jsV_newboolean(J, v));
}

void js_newnumber(js_State* J, double v) {
    js_pushobject(J, jsV_newnumber(J, v));
}

void js_newvec2i(js_State* J, int x, int y) {
    js_pushobject(J, jsV_newvec2i(J, x, y));
}

void js_newstring(js_State* J, const char* v) {
    js_pushobject(J, jsV_newstring(J, v));
}

void js_newfunction(js_State* J, js_Function* fun, js_Environment* scope) {
    js_Object* obj = jsV_newobject(J, JS_CFUNCTION, J->Function_prototype);
    obj->u.f.function = fun;
    obj->u.f.scope = scope;
    js_pushobject(J, obj);
    {
        js_pushnumber(J, fun->numparams);
        js_defproperty(J, -2, property_length, JS_READONLY | JS_DONTENUM | JS_DONTCONF);
        js_newobject(J);
        {
            js_copy(J, -2);
            js_defproperty(J, -2, property_constructor, JS_DONTENUM);
        }
        js_defproperty(J, -2, property_prototype, JS_DONTCONF);
    }
}

void js_newscript(js_State* J, js_Function* fun, js_Environment* scope) {
    js_Object* obj = jsV_newobject(J, JS_CSCRIPT, NULL);
    obj->u.f.function = fun;
    obj->u.f.scope = scope;
    js_pushobject(J, obj);
}

void js_newcfunction(js_State* J, js_CFunction cfun, const js_StringNode name, int length) {
    js_Object* obj = jsV_newobject(J, JS_CCFUNCTION, J->Function_prototype);
    obj->u.c.name = name;
    obj->u.c.function = cfun;
    obj->u.c.constructor = NULL;
    obj->u.c.length = length;
    js_pushobject(J, obj);
    {
        js_pushnumber(J, length);
        js_defproperty(J, -2, property_length, JS_READONLY | JS_DONTENUM | JS_DONTCONF);
        js_newobject(J);
        {
            js_copy(J, -2);
            js_defproperty(J, -2, property_constructor, JS_DONTENUM);
        }
        js_defproperty(J, -2, property_prototype, JS_DONTCONF);
    }
}

/* prototype -- constructor */
void js_newcconstructor(js_State* J, js_CFunction cfun, js_CFunction ccon, const js_StringNode name, int length) {
    js_Object* obj = jsV_newobject(J, JS_CCFUNCTION, J->Function_prototype);
    obj->u.c.name = name;
    obj->u.c.function = cfun;
    obj->u.c.constructor = ccon;
    obj->u.c.length = length;
    js_pushobject(J, obj); /* proto obj */
    {
        js_pushnumber(J, length);
        js_defproperty(J, -2, property_length, JS_READONLY | JS_DONTENUM | JS_DONTCONF);
        js_rot2(J);     /* obj proto */
        js_copy(J, -2); /* obj proto obj */
        js_defproperty(J, -2, property_constructor, JS_DONTENUM);
        js_defproperty(J, -2, property_prototype, JS_READONLY | JS_DONTENUM | JS_DONTCONF);
    }
}

void js_newuserdatax(js_State* J, const char* tag, void* data, js_HasProperty has, js_Put put, js_Delete rdelete,
  js_Finalize finalize) {
    js_Object* prototype = NULL;
    js_Object* obj;

    if (J->isobject(-1)) {
        prototype = J->toobject(-1);
    }
    js_pop(J, 1);

    obj = jsV_newobject(J, JS_CUSERDATA, prototype);
    obj->u.user.tag = tag;
    obj->u.user.data = data;
    obj->u.user.has = has;
    obj->u.user.put = put;
    obj->u.user.rdelete = rdelete;
    obj->u.user.finalize = finalize;
    js_pushobject(J, obj);
}

void js_newuserdata(js_State* J, const char* tag, void* data, js_Finalize finalize) {
    js_newuserdatax(J, tag, data, NULL, NULL, NULL, finalize);
}

/* Non-trivial operations on values. These are implemented using the stack. */

int js_instanceof(js_State* J) {
    js_Object *O, *V;

    if (!J->iscallable(-1))
        js_typeerror(J, "instanceof: invalid operand");

    if (!J->isobject(-2))
        return 0;

    J->getproperty(-1, property_prototype);
    if (!J->isobject(-1))
        js_typeerror(J, "instanceof: 'prototype' property is not an object");
    O = J->toobject(-1);
    js_pop(J, 1);

    V = J->toobject(-2);
    while (V) {
        V = V->prototype;
        if (O == V)
            return 1;
    }

    return 0;
}

void js_concat(js_State* J) {
    js_toprimitive(J, -2, JS_HNONE);
    js_toprimitive(J, -1, JS_HNONE);

    if (js_isstring(J, -2) || js_isstring(J, -1)) {
        const char* sa = js_strnode_cstr(js_tostring(J, -2));
        const char* sb = js_strnode_cstr(js_tostring(J, -1));
        char* sab = (char*)js_frame_alloc(J, strlen(sa) + strlen(sb) + 1);
        strcpy(sab, sa);
        strcat(sab, sb);
        if (js_try(J)) {
            js_frame_free(J, sab);
            js_throw(J);
        }
        js_pop(J, 2);
        J->pushstring(sab);
        js_endtry(J);
        js_frame_free(J, sab);
    } else {
        double x = js_tonumber(J, -2);
        double y = js_tonumber(J, -1);
        js_pop(J, 2);
        js_pushnumber(J, x + y);
    }
}

int js_compare(js_State* J, int* okay) {
    js_toprimitive(J, -2, JS_HNUMBER);
    js_toprimitive(J, -1, JS_HNUMBER);

    *okay = 1;
    if (js_isstring(J, -2) && js_isstring(J, -1)) {
        auto sa = js_tostring(J, -2);
        auto sb = js_tostring(J, -1);
        return strcmp(js_strnode_cstr(sa), js_strnode_cstr(sb));
    } else {
        double x = js_tonumber(J, -2);
        double y = js_tonumber(J, -1);
        if (isnan(x) || isnan(y)) {
            *okay = 0;
        }
        return x < y ? -1 : x > y ? 1 : 0;
    }
}

int js_equal(js_State* J) {
    js_Value* x = js_tovalue(J, -2);
    js_Value* y = js_tovalue(J, -1);

retry:
    if (JSV_ISSTRING(x) && JSV_ISSTRING(y))
        return !strcmp(JSV_TOSTRING(x), JSV_TOSTRING(y));
    if (x->type == y->type) {
        if (x->type == JS_TUNDEFINED)
            return 1;
        if (x->type == JS_TNULL)
            return 1;
        if (x->type == JS_TNUMBER)
            return x->u.number == y->u.number;
        if (x->type == JS_TBOOLEAN)
            return x->u.boolean == y->u.boolean;
        if (x->type == JS_TOBJECT)
            return x->u.object == y->u.object;
        return 0;
    }

    if (x->type == JS_TNULL && y->type == JS_TUNDEFINED)
        return 1;
    if (x->type == JS_TUNDEFINED && y->type == JS_TNULL)
        return 1;

    if (x->type == JS_TNUMBER && JSV_ISSTRING(y))
        return x->u.number == jsV_tonumber(J, y);
    if (JSV_ISSTRING(x) && y->type == JS_TNUMBER)
        return jsV_tonumber(J, x) == y->u.number;

    if (x->type == JS_TBOOLEAN) {
        x->type = JS_TNUMBER;
        x->u.number = x->u.boolean;
        goto retry;
    }
    if (y->type == JS_TBOOLEAN) {
        y->type = JS_TNUMBER;
        y->u.number = y->u.boolean;
        goto retry;
    }
    if ((JSV_ISSTRING(x) || x->type == JS_TNUMBER) && y->type == JS_TOBJECT) {
        jsV_toprimitive(J, y, JS_HNONE);
        goto retry;
    }
    if (x->type == JS_TOBJECT && (JSV_ISSTRING(y) || y->type == JS_TNUMBER)) {
        jsV_toprimitive(J, x, JS_HNONE);
        goto retry;
    }

    return 0;
}

int js_strictequal(js_State* J) {
    js_Value* x = js_tovalue(J, -2);
    js_Value* y = js_tovalue(J, -1);

    if (JSV_ISSTRING(x) && JSV_ISSTRING(y)) {
        return strcmp(JSV_TOSTRING(x), JSV_TOSTRING(y)) == 0;
    }

    if (x->type != y->type)
        return 0;
    if (x->type == JS_TUNDEFINED)
        return 1;
    if (x->type == JS_TNULL)
        return 1;
    if (x->type == JS_TNUMBER)
        return x->u.number == y->u.number;
    if (x->type == JS_TBOOLEAN)
        return x->u.boolean == y->u.boolean;
    if (x->type == JS_TOBJECT)
        return x->u.object == y->u.object;
    return 0;
}
