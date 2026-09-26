#pragma once

#include "mujs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <setjmp.h>
#include <math.h>
#include <float.h>

#include <type_traits>

#include "core/string.h"
#include "jsstring.h"

/* Microsoft Visual C */
#ifdef _MSC_VER
#pragma warning(disable:4996) /* _CRT_SECURE_NO_WARNINGS */
#pragma warning(disable:4244) /* implicit conversion from double to int */
#pragma warning(disable:4267) /* implicit conversion of int to smaller int */
#endif

#define soffsetof(x,y) ((int)offsetof(x,y))
#define nelem(a) (int)(sizeof (a) / sizeof (a)[0])

void *js_malloc(js_State *J, int size);
void *js_realloc(js_State *J, void *ptr, int size);
void js_free(js_State *J, void *ptr);

struct js_Regexp;
struct js_Value;
struct js_Object;
struct js_String;
struct js_Ast;
struct js_Function;
struct js_Environment;
struct js_Jumpbuf;
struct js_StackTrace;
struct js_Property;

/* Limits */

#define JS_STACKSIZE 256	/* value stack size */
#define JS_ENVLIMIT 64		/* environment stack size */
#define JS_TRYLIMIT 64		/* exception stack size */
#define JS_GCLIMIT 10000	/* run gc cycle every N allocations */

/* 0 = soft log on ephemeral escape; 1 = js_error. */
#ifndef JS_FRAME_ESCAPE_HARD
#define JS_FRAME_ESCAPE_HARD 1
#endif

/* instruction size -- change to int if you get integer overflow syntax errors */
typedef int js_Instruction;

/* Portable strtod and printf float formatting */
void js_fmtexp(char *p, int e);
void js_dtoa(double f, char *digits, int *exp, int *neg, int *ndigits);
double js_strtod(const char *as, char **aas);

/* Private stack functions */

void js_newfunction(js_State *J, js_Function *function, js_Environment *scope);
void js_newscript(js_State *J, js_Function *function, js_Environment *scope);
void js_loadeval(js_State *J, const char *filename, const char *source);

js_Regexp *js_toregexp(js_State *J, int idx);
int js_isarrayindex(js_State *J, const char *str, int *idx);
int js_runeat(js_State *J, const char *s, int i);
int js_utfptrtoidx(const char *s, const char *p);
const char *js_utfidxtoptr(const char *s, int i);

void js_dup(js_State *J);
void js_rot2(js_State *J);
void js_rot3(js_State *J);
void js_rot4(js_State *J);
void js_rot2pop1(js_State *J);
void js_rot3pop2(js_State *J);
void js_dup1rot3(js_State *J);
void js_dup1rot4(js_State *J);

void js_RegExp_prototype_exec(js_State *J, js_Regexp *re, const char *text);

void js_trap(js_State *J, int pc); /* dump stack and environment to stdout */
void js_stacktrace(js_State *J);

struct js_StackTrace
{
	const char *name;
	const char *file;
	int line;
};

/* Exception handling.
 *
 * js_throw() unwinds with longjmp (jsrun.cpp), which does NOT run destructors of
 * objects in the frames it jumps over. Engine code must therefore keep every local
 * trivially destructible: no std::string/vector, no RAII guards, nothing owning a
 * resource. Allocate through js_malloc / js_frame_alloc and release on the js_try
 * error path instead. This holds for all of src/mujs today — keep it that way. */

struct js_Jumpbuf
{
	jmp_buf buf;
	js_Environment *E;
	int envtop;
	int tracetop;
	int top, bot;
	js_Instruction *pc;
};

void *js_savetrypc(js_State *J, js_Instruction *pc);

#define js_trypc(J, PC) \
	setjmp(*((jmp_buf *)js_savetrypc(J, PC)))

class xstring;

/* Enums bind by width only: 1- and 2-byte enums read back as unsigned, whatever their underlying type. */
template<typename FieldT>
constexpr js_CPtrType js_cptr_type_of() {
	using T = std::remove_cv_t<FieldT>;
	if constexpr (std::is_same_v<T, bool>) {
		return JS_PTR_BOOL;
	} else if constexpr (std::is_same_v<T, float>) {
		return JS_PTR_FLOAT;
	} else if constexpr (std::is_same_v<T, int8_t>) {
		return JS_PTR_INT8;
	} else if constexpr (std::is_same_v<T, uint8_t>) {
		return JS_PTR_UINT8;
	} else if constexpr (std::is_same_v<T, int16_t>) {
		return JS_PTR_INT16;
	} else if constexpr (std::is_same_v<T, uint16_t>) {
		return JS_PTR_UINT16;
	} else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, unsigned int>) {
		return JS_PTR_INT;
	} else if constexpr (std::is_same_v<T, xstring>) {
		return JS_PTR_XSTRING;
	} else if constexpr (std::is_enum_v<T>) {
		static_assert(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == sizeof(int), "js_cptr_type_of: enum must be 1, 2 or 4 bytes");
		if constexpr (sizeof(T) == 1) {
			return JS_PTR_UINT8;
		} else if constexpr (sizeof(T) == 2) {
			return JS_PTR_UINT16;
		} else {
			return JS_PTR_INT;
		}
	} else {
		static_assert(sizeof(T) == 0, "js_cptr_type_of: unsupported native type for a JS binding");
		return JS_PTR_INT;
	}
}

/* Typed stack conversion behind js_State::to / push: static T to(J, idx) and static void push(J, v).
   Primitives are specialized below js_State; game types in src/js/js_game.h. */
template<typename T, typename Enable = void>
struct js_convert;

/* State struct */

struct js_State
{
	void *actx;
	void *uctx;
	js_Alloc alloc;
	void *frame_actx;
	js_Alloc frame_alloc;
	js_Panic panic;

	int strict;

	/* parser input source */
	const char *filename;
	const char *source;
	int line;

	/* lexer state */
	struct { char *text; int len, cap; } lexbuf;
	int lexline;
	int lexchar;
	int lasttoken;
	int newline;

	/* parser state */
	int astline;
	int lookahead;
	js_StringNode text;
	double number;
	js_Ast *gcast; /* list of allocated nodes to free after parsing */

	/* runtime environment */
	js_Object *Object_prototype;
	js_Object *Array_prototype;
	js_Object *Function_prototype;
	js_Object *Boolean_prototype;
	js_Object *Number_prototype;
	js_Object *Vec2i_prototype;
	js_Object *String_prototype;
	js_Object *RegExp_prototype;
	js_Object *Date_prototype;

	js_Object *Error_prototype;
	js_Object *EvalError_prototype;
	js_Object *RangeError_prototype;
	js_Object *ReferenceError_prototype;
	js_Object *SyntaxError_prototype;
	js_Object *TypeError_prototype;
	js_Object *URIError_prototype;

	int nextref; /* for js_ref use */
	js_Object *R; /* registry of hidden values */
	js_Object *G; /* the global object */
	js_Environment *E; /* current environment scope */
	js_Environment *GE; /* global environment scope (at the root) */

	/* execution stack */
	int top, bot;
	js_Value *stack;

	/* garbage collector: increments each collection; objects store this value when live */
	uint32_t gc_generation;
	int gccounter;
	js_Environment *gcenv;
	js_Function *gcfun;
	js_Object *gcobj;
	js_String *gcstr;

	/* draw frame-zone: nested depth; ephemeral objects use frame_alloc */
	int frame_zone_depth;
	unsigned frame_escape_count;
	void (*frame_arena_release)(void *actx);
	void *frame_arena_release_actx;
	js_Import jscimport;
	js_Emit jscemit;
	void (*dumpfunction)(js_State *J, const char *);

	/* environments on the call stack but currently not in scope */
	int envtop;
	js_Environment *envstack[JS_ENVLIMIT];

	/* debug info stack trace */
	int tracetop;
	js_StackTrace trace[JS_ENVLIMIT];

	/* exception stack */
	int trytop;
	js_Jumpbuf trybuf[JS_TRYLIMIT];

	/* property name being accessed when toobject fails — used for error location */
	const char *pending_prop;

	/* debug hook — called on every OP_LINE (source line change).
	   Both fields are zero-initialised by js_newstate via memset. */
	js_DebugHook debug_hook;
	void *debug_hook_udata;

	void gc(int report);
	void stackoverflow();

	void savescope(js_Environment *newE);
	void restorescope();

	void pushundefined();
	void pushstring(pcstr v);
    void pushstring(const js_StringNode v);

	void getproperty(js_Object* obj, const js_StringNode name);
    void getproperty(int idx, const js_StringNode name) { getproperty(toobject(idx), name); }

	int hasproperty(js_Object *obj, js_StringNode name);

	int hasproperty(int idx, const js_StringNode name);

	int isobject(int idx);
	int isdefined(int idx);
	int isundefined(int idx);
	int isnull(int idx);
	int isboolean(int idx);
	int isnumber(int idx);
	int iscnumber(int idx);
	int isstring(int idx);
	int isprimitive(int idx);
	int isarray(int idx);
	int isregexp(int idx);
	int iscvec2i(int idx);
	int iscoercible(int idx);
	int isuserdata(int idx, const char *tag);

	void newobject();
	void newarray();
	void newboolean(int v);
	void newnumber(double v);
	void newvec2i(int x, int y);
	void newstring(const char *v);
	void newcfunction(js_CFunction fun, const js_StringNode name, int length);
	void newcconstructor(js_CFunction fun, js_CFunction con, const js_StringNode name, int length);
	void newuserdata(const char *tag, void *data, js_Finalize finalize);
	void newuserdatax(const char *tag, void *data, js_HasProperty has, js_Put put, js_Delete delet, js_Finalize finalize);
	void newregexp(const char *pattern, int flags);

	int pcall(int n);
	void call(int n);

	int iscallable(int idx);
	js_Object *toobject(int idx);

	js_Object *toobject(js_Value *v);
	js_Object *toobject_pending(int idx, const char *prop);

	void pushtrace(const char *name, const char *file, int line);
	void callwfunction(int n, js_Function *F, js_Environment *scope);
	void callfunction(int n, js_Function *F, js_Environment *scope);

	int delvar(const js_StringNode name);
    js_Property* vget_ownproperty(js_Object* obj, const js_StringNode name);
	int rdelproperty(js_Object *obj, const js_StringNode name);
	void r_run(js_Function *F);
	void construct(int n);

	void dup2();
    void pushliteral(js_StringNode val);

	/* JS_CPTR bindings: the script reads and writes *ptr in place.
	   bind_global defines a global; bind_property sets a property on the object at -1. */
	void bind_global(const js_StringNode name, void *ptr, js_CPtrType ptype);
	void bind_property(const js_StringNode name, void *ptr, js_CPtrType ptype);
	/* JS_CPTROFF: field at byte_offset from the receiver's cobj_ptr, set with set_cobj_ptr. */
	void bind_offset_property(const js_StringNode name, size_t byte_offset, js_CPtrType ptype);
	/* Object at -1 becomes the base for its JS_CPTROFF prototype fields. */
	void set_cobj_ptr(void *cpp_object);

	template<typename T>
	void bind_global(const js_StringNode name, T *ptr) { bind_global(name, (void *)ptr, js_cptr_type_of<T>()); }

	template<typename T>
	void bind_property(const js_StringNode name, T *ptr) { bind_property(name, (void *)ptr, js_cptr_type_of<T>()); }

	template<typename FieldT>
	void bind_offset_property(const js_StringNode name, size_t byte_offset) { bind_offset_property(name, byte_offset, js_cptr_type_of<FieldT>()); }

	/* A conversion may run script code (toString/valueOf) and js_throw, whose longjmp skips
	   destructors of the bridge frames holding already-converted values. */
	template<typename T>
	T to(int idx) {
		static_assert(std::is_trivially_destructible_v<T>,
		              "js_State::to: JS-bound argument types must be trivially destructible (MuJS unwinds with longjmp)");
		return js_convert<T>::to(this, idx);
	}

	template<typename T>
	void push(const T &value) { js_convert<std::decay_t<const T>>::push(this, value); }
};

template<>
struct js_convert<int> {
	static int to(js_State *J, int idx) { return js_tointeger(J, idx); }
	static void push(js_State *J, int v) { js_pushnumber(J, v); }
};

template<>
struct js_convert<unsigned int> {
	static unsigned int to(js_State *J, int idx) { return js_touint32(J, idx); }
	static void push(js_State *J, unsigned int v) { js_pushnumber(J, v); }
};

template<>
struct js_convert<double> {
	static double to(js_State *J, int idx) { return js_tonumber(J, idx); }
	static void push(js_State *J, double v) { js_pushnumber(J, v); }
};

template<>
struct js_convert<float> {
	static float to(js_State *J, int idx) { return (float)js_tonumber(J, idx); }
	static void push(js_State *J, float v) { js_pushnumber(J, v); }
};

template<>
struct js_convert<bool> {
	static bool to(js_State *J, int idx) { return js_toboolean(J, idx) != 0; }
	static void push(js_State *J, bool v) { js_pushboolean(J, v); }
};

template<>
struct js_convert<const char *> {
	static const char *to(js_State *J, int idx) { return js_strnode_cstr(js_tostring(J, idx)); }
	static void push(js_State *J, const char *v) { J->pushstring(v); }
};

template<typename T>
struct js_convert<T, std::enable_if_t<std::is_enum_v<T>>> {
	static T to(js_State *J, int idx) { return (T)js_tointeger(J, idx); }
	static void push(js_State *J, T v) { js_pushnumber(J, (double)v); }
};

template<typename T>
struct js_convert<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
	static T to(js_State *J, int idx) { return (T)js_tonumber(J, idx); }
	static void push(js_State *J, T v) { js_pushnumber(J, (double)v); }
};
