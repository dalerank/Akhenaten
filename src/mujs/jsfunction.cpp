#include "jsi.h"
#include "jsparse.h"
#include "jscompile.h"
#include "jsvalue.h"
#include "jsbuiltin.h"

static void jsB_Function(js_State *J)
{
	int i, top = js_gettop(J);
	js_Buffer *sb = NULL;
	const char *body;
	js_Ast *parse;
	js_Function *fun;

	/* p1, p2, ..., pn */
	if (top > 2) {
		for (i = 1; i < top - 1; ++i) {
            if (i > 1) {
                js_putc(J, &sb, ',');
            }

			js_puts(J, &sb, js_tostring(J, i)->value.c_str());
		}
		js_putc(J, &sb, ')');
	}

	/* body */
	body = js_isdefined(J, top - 1) ? js_tostring(J, top - 1)->value.c_str() : "";

	if (js_try(J)) {
		jsP_freeparse(J);
		js_throw(J);
	}

	parse = jsP_parsefunction(J, "[string]", sb ? sb->s : NULL, body);
	fun = jsC_compilefunction(J, parse);

	js_endtry(J);
	jsP_freeparse(J);

	js_newfunction(J, fun, J->GE);
}

static void jsB_Function_prototype(js_State *J)
{
	J->pushundefined();
}

static void Fp_toString(js_State *J)
{
	js_Object *self = J->toobject(0);
	char *s = 0;
	int i, n;

	if (!J->iscallable(0)) {
		js_typeerror(J, "not a function");
	}

	if (self->type == JS_CFUNCTION || self->type == JS_CSCRIPT) {
		js_Function *F = self->u.f.function;
		pcstr name_c = js_strnode_cstr(F->name);
		n = strlen("function () { ... }");
		n += (int)strlen(name_c);
		for (i = 0; i < F->numparams; ++i)
			n += F->vartab[i]->value.length() + 1;

		s = (char*)js_frame_alloc(J, n + 16);
		strcpy(s, "function ");
		strcat(s, name_c);
		strcat(s, "(");
		for (i = 0; i < F->numparams; ++i) {
			if (i > 0) {
				strcat(s, ",");
			}
			strcat(s, F->vartab[i]->value.c_str());
		}
		strcat(s, ") { ... }");
		if (js_try(J)) {
			//js_free(J, s);
			js_throw(J);
		}
		J->pushstring(s);
		js_endtry(J);
	} else {
		J->pushliteral(js_intern("function () { ... }"));
	}
}

static void Fp_apply(js_State *J)
{
	int i, n;

	if (!J->iscallable(0))
		js_typeerror(J, "not a function");

	js_copy(J, 0);
	js_copy(J, 1);

	if (js_isnull(J, 2) || js_isundefined(J, 2)) {
		n = 0;
	} else {
		n = js_getlength(J, 2);
		for (i = 0; i < n; ++i)
			js_getindex(J, 2, i);
	}

	J->call(n);
}

static void Fp_call(js_State *J)
{
	int i, top = js_gettop(J);

	if (!J->iscallable(0))
		js_typeerror(J, "not a function");

	for (i = 0; i < top; ++i)
		js_copy(J, i);

	J->call(top - 2);
}

js_StringNode property_prototype = js_intern("prototype");
js_StringNode property___TargetFunction__ = js_intern("__TargetFunction__");
js_StringNode property___BoundThis__ = js_intern("__BoundThis__");
js_StringNode property___BoundArguments__ = js_intern("__BoundArguments__");

static void callbound(js_State *J)
{
	int top = js_gettop(J);
	int i, fun, args, n;

	fun = js_gettop(J);
	js_currentfunction(J);
    J->getproperty(fun, property___TargetFunction__);
    J->getproperty(fun, property___BoundThis__);

	args = js_gettop(J);
    J->getproperty(fun, property___BoundArguments__);
	n = js_getlength(J, args);
	for (i = 0; i < n; ++i)
		js_getindex(J, args, i);
	js_remove(J, args);

	for (i = 1; i < top; ++i)
		js_copy(J, i);

	J->call(n + top - 1);
}

static void constructbound(js_State* J) {
    int top = js_gettop(J);
    int i, fun, args, n;

    fun = js_gettop(J);
    js_currentfunction(J);
    J->getproperty(fun, property___TargetFunction__);

    args = js_gettop(J);
    J->getproperty(fun, property___BoundArguments__);
    n = js_getlength(J, args);
    for (i = 0; i < n; ++i)
        js_getindex(J, args, i);
    js_remove(J, args);

    for (i = 1; i < top; ++i)
        js_copy(J, i);

    J->construct(n + top - 1);
}

static void Fp_bind(js_State *J)
{
	int i, top = js_gettop(J);
	int n;

	if (!J->iscallable(0))
		js_typeerror(J, "not a function");

	n = js_getlength(J, 0);
	if (n > top - 2)
		n -= top - 2;
	else
		n = 0;

	/* Reuse target function's prototype for HasInstance check. */
    J->getproperty(0, property_prototype);
    js_newcconstructor(J, callbound, constructbound, js_intern("[bind]"), n);

	/* target function */
	js_copy(J, 0);
    js_defproperty(J, -2, property___TargetFunction__, JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	/* bound this */
	js_copy(J, 1);
    js_defproperty(J, -2, property___BoundThis__, JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	/* bound arguments */
	js_newarray(J);
	for (i = 2; i < top; ++i) {
		js_copy(J, i);
		js_setindex(J, -2, i - 2);
	}
    js_defproperty(J, -2, property___BoundArguments__, JS_READONLY | JS_DONTENUM | JS_DONTCONF);
}

void jsB_initfunction(js_State *J)
{
	J->Function_prototype->u.c.function = jsB_Function_prototype;
	J->Function_prototype->u.c.constructor = NULL;

	js_pushobject(J, J->Function_prototype);
	{
		jsB_propf(J, js_intern("Function.prototype.toString"), Fp_toString, 2);
		jsB_propf(J, js_intern("Function.prototype.apply"), Fp_apply, 2);
		jsB_propf(J, js_intern("Function.prototype.call"), Fp_call, 1);
		jsB_propf(J, js_intern("Function.prototype.bind"), Fp_bind, 1);
	}
    js_newcconstructor(J, jsB_Function, jsB_Function, js_intern("Function"), 1);
    js_defglobal(J, js_intern("Function"), JS_DONTENUM);
}
