#include "jsi.h"
#include "jscompile.h"
#include "jsvalue.h"
#include "jsrun.h"

#include "regexp.h"
#include "core/profiler.h"

#include <atomic>
#include <cstddef>

static inline uint32_t gcmark_load(const std::atomic<uint32_t> &a) {
    return a.load(std::memory_order_relaxed);
}

/* Forward declarations */
static void gc_markproperty(js_State *J, uint32_t mark, js_Property *node);
static void gc_markobject(js_State *J, uint32_t mark, js_Object *obj);
static void gc_markenvironment(js_State *J, uint32_t mark, js_Environment *env);
static void gc_markfunction(js_State *J, uint32_t mark, js_Function *fun);

/*
 * Mark graph: if gcmark already equals `mark`, return immediately (second path into the same
 * object does not re-walk children). std::atomic keeps memory accesses defined for future MT mark.
 */
static void gc_markproperty(js_State *J, uint32_t mark, js_Property *node) {
    OZZY_PROFILER_FUNCTION();
    (void)J;

    while (node) {
        if (node->value.type == JS_TMEMSTR && gcmark_load(node->value.u.memstr->gcmark) != mark)
            node->value.u.memstr->gcmark.store(mark, std::memory_order_relaxed);

        if (node->value.type == JS_TOBJECT && node->value.u.object)
            gc_markobject(J, mark, node->value.u.object);

        if (node->getter)
            gc_markobject(J, mark, node->getter);

        if (node->setter)
            gc_markobject(J, mark, node->setter);

        node = node->next;
    }
}

static void gc_markobject(js_State *J, uint32_t mark, js_Object *obj) {
    OZZY_PROFILER_FUNCTION();

    if (!obj) {
        return;
    }

    if (gcmark_load(obj->gcmark) == mark) {
        return;
    }
    obj->gcmark.store(mark, std::memory_order_relaxed);

    if (obj->head)
        gc_markproperty(J, mark, obj->head);

    if (obj->prototype)
        gc_markobject(J, mark, obj->prototype);

    if (obj->type == JS_CITERATOR && obj->u.iter.target)
        gc_markobject(J, mark, obj->u.iter.target);

    if (obj->type == JS_CFUNCTION || obj->type == JS_CSCRIPT) {
        gc_markenvironment(J, mark, obj->u.f.scope);
        gc_markfunction(J, mark, obj->u.f.function);
    }
}

static void gc_markenvironment(js_State *J, uint32_t mark, js_Environment *env) {
    (void)J;

    while (env) {
        if (gcmark_load(env->gcmark) == mark) {
            break;
        }
        env->gcmark.store(mark, std::memory_order_relaxed);
        if (env->variables)
            gc_markobject(J, mark, env->variables);
        env = env->outer;
    }
}

static void gc_markfunction(js_State *J, uint32_t mark, js_Function *fun) {
    OZZY_PROFILER_FUNCTION();
    (void)J;

    if (!fun) return;
    if (gcmark_load(fun->gcmark) == mark) return;
    fun->gcmark.store(mark, std::memory_order_relaxed);

    for (int i = 0; i < fun->funlen; ++i) {
        if (fun->funtab[i])
            gc_markfunction(J, mark, fun->funtab[i]);
    }
}

static void gc_markstack(js_State *J, uint32_t mark) {
    OZZY_PROFILER_FUNCTION();

    js_Value *v = J->stack;
    int n = J->top;
    while (n--) {
        if (v->type == JS_TMEMSTR && gcmark_load(v->u.memstr->gcmark) != mark)
            v->u.memstr->gcmark.store(mark, std::memory_order_relaxed);

        if (v->type == JS_TOBJECT && v->u.object)
            gc_markobject(J, mark, v->u.object);

        ++v;
    }
}

static void jsG_freeenvironment(js_State *J, js_Environment *env) {
    js_free(J, env);
}

static void jsG_freemodifiers(js_State *J, js_FunctionModifier *mod) {
    while (mod) {
        js_FunctionModifier *next = mod->next;
        js_free(J, mod);
        mod = next;
    }
}

static void jsG_freefunction(js_State *J, js_Function *fun) {
    jsG_freemodifiers(J, fun->modifiers);
    js_free(J, fun->funtab);
    js_free(J, fun->numtab);
    js_free(J, fun->strtab);
    js_free(J, fun->vartab);
    js_free(J, fun->code);
    js_free(J, fun);
}

static void jsG_freeproperty(js_State *J, js_Property *node) {
    while (node) {
        js_Property *next = node->next;
        js_free(J, node);
        node = next;
    }
}

static void jsG_freeiterator(js_State *J, js_Iterator *node) {
    while (node) {
        js_Iterator *next = node->next;
        js_free(J, node);
        node = next;
    }
}

static void jsG_freeobject(js_State *J, js_Object *obj) {
    OZZY_PROFILER_FUNCTION();

    jsG_freemodifiers(J, obj->modifiers);
    if (obj->head)
        jsG_freeproperty(J, obj->head);

    if (obj->type == JS_CREGEXP)
        js_regfree((Reprog *)obj->u.r.prog);

    if (obj->type == JS_CITERATOR)
        jsG_freeiterator(J, obj->u.iter.head);

    if (obj->type == JS_CUSERDATA && obj->u.user.finalize)
        obj->u.user.finalize(J, obj->u.user.data);

    js_free(J, obj);
}

void js_State::gc(int report) {
    OZZY_PROFILER_FUNCTION();

    int nenv = 0, nfun = 0, nobj = 0, nstr = 0;
    int genv = 0, gfun = 0, gobj = 0, gstr = 0;
    uint32_t mark;
    int i;

    mark = ++gc_generation;

    {
        OZZY_PROFILER_SECTION(_, "Mark objects")

        auto J = this;
        gc_markobject(J, mark, J->Object_prototype);
        gc_markobject(J, mark, J->Array_prototype);
        gc_markobject(J, mark, J->Function_prototype);
        gc_markobject(J, mark, J->Boolean_prototype);
        gc_markobject(J, mark, J->Number_prototype);
        gc_markobject(J, mark, J->String_prototype);
        gc_markobject(J, mark, J->RegExp_prototype);
        gc_markobject(J, mark, J->Date_prototype);

        gc_markobject(J, mark, J->Error_prototype);
        gc_markobject(J, mark, J->EvalError_prototype);
        gc_markobject(J, mark, J->RangeError_prototype);
        gc_markobject(J, mark, J->ReferenceError_prototype);
        gc_markobject(J, mark, J->SyntaxError_prototype);
        gc_markobject(J, mark, J->TypeError_prototype);
        gc_markobject(J, mark, J->URIError_prototype);

        gc_markstack(J, mark);

        gc_markobject(J, mark, J->G);
        gc_markobject(J, mark, J->R);

        gc_markenvironment(J, mark, J->E);
        gc_markenvironment(J, mark, J->GE);
        for (i = 0; i < envtop; ++i) {
            gc_markenvironment(J, mark, J->envstack[i]);
        }
    }

    {
        OZZY_PROFILER_SECTION(_, "Environment")

        js_Environment *env, *nextenv;
        js_Environment **prevnextenv = &gcenv;
        for (env = gcenv; env; env = nextenv) {
            nextenv = env->gcnext;
            if (gcmark_load(env->gcmark) != mark) {
                *prevnextenv = nextenv;
                jsG_freeenvironment(this, env);
                ++genv;
            } else {
                prevnextenv = &env->gcnext;
            }
            ++nenv;
        }
    }

    {
        OZZY_PROFILER_SECTION(_, "Functions")

        js_Function *fun, *nextfun, **prevnextfun;
        prevnextfun = &gcfun;
        for (fun = gcfun; fun; fun = nextfun) {
            nextfun = fun->gcnext;
            if (gcmark_load(fun->gcmark) != mark) {
                *prevnextfun = nextfun;
                jsG_freefunction(this, fun);
                ++gfun;
            } else {
                prevnextfun = &fun->gcnext;
            }
            ++nfun;
        }
    }

    {
        OZZY_PROFILER_SECTION(_, "Objects")

        js_Object *obj, *nextobj, **prevnextobj;
        prevnextobj = &gcobj;
        for (obj = gcobj; obj; obj = nextobj) {
            nextobj = obj->gcnext;
            if (gcmark_load(obj->gcmark) != mark) {
                *prevnextobj = nextobj;
                jsG_freeobject(this, obj);
                ++gobj;
            } else {
                prevnextobj = &obj->gcnext;
            }
            ++nobj;
        }
    }

    {
        OZZY_PROFILER_SECTION(_, "Strings")

        js_String *str, *nextstr, **prevnextstr;
        prevnextstr = &gcstr;
        for (str = gcstr; str; str = nextstr) {
            nextstr = str->gcnext;
            if (gcmark_load(str->gcmark) != mark) {
                *prevnextstr = nextstr;
                js_free(this, str);
                ++gstr;
            } else {
                prevnextstr = &str->gcnext;
            }
            ++nstr;
        }
    }

    if (report) {
        printf("garbage collected: %d/%d envs, %d/%d funs, %d/%d objs, %d/%d strs\n",
            genv, nenv, gfun, nfun, gobj, nobj, gstr, nstr);
    }
}

void js_freestate(js_State *J) {
    js_Function *fun, *nextfun;
    js_Object *obj, *nextobj;
    js_Environment *env, *nextenv;
    js_String *str, *nextstr;

    for (env = J->gcenv; env; env = nextenv)
        nextenv = env->gcnext, jsG_freeenvironment(J, env);
    for (fun = J->gcfun; fun; fun = nextfun)
        nextfun = fun->gcnext, jsG_freefunction(J, fun);
    for (obj = J->gcobj; obj; obj = nextobj)
        nextobj = obj->gcnext, jsG_freeobject(J, obj);
    for (str = J->gcstr; str; str = nextstr)
        nextstr = str->gcnext, js_free(J, str);

    jsS_freestrings(J);

    js_free(J, J->lexbuf.text);
    J->alloc(J->actx, J->stack, 0);
    J->alloc(J->actx, J, 0);
}
