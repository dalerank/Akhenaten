#include "jsi.h"
#include "jsvalue.h"

#include <atomic>
#include <cstddef>
#include <new>

#include "core/profiler.h"

#include <cstring>

/*
    Use an AA-tree to quickly look up properties in objects:

    The level of every leaf node is one.
    The level of every left child is one less than its parent.
    The level of every right child is equal or one less than its parent.
    The level of every right grandchild is less than its grandparent.
    Every node of level greater than one has two children.

    A link where the child's level is equal to that of its parent is called a horizontal link.
    Individual right horizontal links are allowed, but consecutive ones are forbidden.
    Left horizontal links are forbidden.

    skew() fixes left horizontal links.
    split() fixes consecutive right horizontal links.
*/

static js_Property sentinel = {
    js_StringNode(),
    &sentinel, &sentinel,
    NULL, NULL,
    0, 0,
    { {0}, {0}, JS_TUNDEFINED },
    NULL, NULL
};

static js_Property* newproperty(js_State* J, js_Object* obj, const js_StringNode name) {
    OZZY_PROFILER_FUNCTION();

    js_Property *node = (js_Property *)js_malloc(J, sizeof * node);
    new (&node->name) js_StringNode();
    node->name = name;
    node->left = node->right = &sentinel;
    node->prevp = NULL;
    node->next = NULL;
    node->level = 1;
    node->atts = 0;
    node->value.type = JS_TUNDEFINED;
    node->value.u.number = 0;
    node->getter = NULL;
    node->setter = NULL;
    ++obj->count;
    return node;
}

js_Property *js_Property::lookup(js_StringNode name) {
    if (!name) {
        return nullptr;
    }
    const char *want = js_strnode_cstr(name);
    js_Property *node = this;
    while (node != &sentinel) {
        int c = strcmp(want, js_strnode_cstr(node->name));
        if (c == 0) {
            return node;
        }
        if (c < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return nullptr;
}

/** AA-tree lookup, then head/next list (kept in sync on insert; tree walk alone can miss nodes). */
static js_Property *property_lookup_on_object(js_Object *obj, js_StringNode name) {
    if (!obj || !name) {
        return nullptr;
    }
    js_Property *ref = obj->properties->lookup(name);
    if (ref) {
        return ref;
    }
    const char *want = js_strnode_cstr(name);
    for (js_Property *p = obj->head; p; p = p->next) {
        if (p->name == name || (want && want[0] && !strcmp(js_strnode_cstr(p->name), want))) {
            return p;
        }
    }
    return nullptr;
}

static js_Property *skew(js_Property *node) {
    if (node->left->level == node->level) {
        js_Property *temp = node;
        node = node->left;
        temp->left = node->right;
        node->right = temp;
    }
    return node;
}

static js_Property *split(js_Property *node) {
    if (node->right->right->level == node->level) {
        js_Property *temp = node;
        node = node->right;
        temp->right = node->left;
        node->left = temp;
        ++node->level;
    }
    return node;
}

static js_Property* insert(js_State* J, js_Object* obj, js_Property* node, const js_StringNode name,
  js_Property** result) {
    if (node != &sentinel) {
        int c = strcmp(js_strnode_cstr(node->name), js_strnode_cstr(name));

        if (c < 0)
            node->left = insert(J, obj, node->left, name, result);
        else if (c > 0)
            node->right = insert(J, obj, node->right, name, result);
        else
            return *result = node;

        node = skew(node);
        node = split(node);
        return node;
    }
    return *result = newproperty(J, obj, name);
}

static void freeproperty(js_State *J, js_Object *obj, js_Property *node) {
    if (node->next)
        node->next->prevp = node->prevp;
    else
        obj->tailp = node->prevp;
    *node->prevp = node->next;
    node->name.~js_StringNode();
    js_free(J, node);
    --obj->count;
}

js_Property* prop_delete(js_State* J, js_Object* obj, js_Property* node, const js_StringNode name) {
    js_Property *temp, *succ;

    if (node != &sentinel) {
        int c = strcmp(js_strnode_cstr(node->name), js_strnode_cstr(name));
        if (c < 0) {
            node->left = prop_delete(J, obj, node->left, name);
        } else if (c > 0) {
            node->right = prop_delete(J, obj, node->right, name);
        } else {
            if (node->left == &sentinel) {
                temp = node;
                node = node->right;
                freeproperty(J, obj, temp);
            } else if (node->right == &sentinel) {
                temp = node;
                node = node->left;
                freeproperty(J, obj, temp);
            } else {
                succ = node->right;
                while (succ->left != &sentinel)
                    succ = succ->left;
                node->name = succ->name;
                node->atts = succ->atts;
                node->value = succ->value;
                node->right = prop_delete(J, obj, node->right, succ->name);
            }
        }

        if (node->left->level < node->level - 1 ||
            node->right->level < node->level - 1) {
            if (node->right->level > --node->level)
                node->right->level = node->level;
            node = skew(node);
            node->right = skew(node->right);
            node->right->right = skew(node->right->right);
            node = split(node);
            node->right = split(node->right);
        }
    }
    return node;
}


js_Object *jsV_newobject(js_State *J, enum js_Class type, js_Object *prototype) {
    OZZY_PROFILER_FUNCTION();

    js_Object *obj = (js_Object *)js_malloc(J, sizeof * obj);
    memset(obj, 0, offsetof(js_Object, gcmark));
    new (&obj->gcmark) std::atomic<uint32_t>(0);
    obj->gcnext = J->gcobj;
    J->gcobj = obj;
    ++J->gccounter;

    obj->type = type;
    obj->properties = &sentinel;
    obj->head = NULL;
    obj->tailp = &obj->head;
    obj->prototype = prototype;
    obj->extensible = 1;

    if (type == JS_CSTRING || type == JS_CERROR) {
        new (&obj->u.s.string) js_StringNode();
    }

    return obj;
}

js_Property* js_State::vget_ownproperty(js_Object* obj, const js_StringNode name) {
    return property_lookup_on_object(obj, name);
}

js_Property* jsV_getpropertyx(js_State* J, js_Object* obj, const js_StringNode name, int* own) {
    *own = 1;
    do {
        js_Property *ref = property_lookup_on_object(obj, name);
        if (ref)
            return ref;

        obj = obj->prototype;
        *own = 0;
    } while (obj);
    return NULL;
}

js_Property *js_Object::vgetproperty(const js_StringNode name) {
    js_Object *obj = this;
    do {
        js_Property *ref = property_lookup_on_object(obj, name);
        if (ref) {
            return ref;
        }
        obj = obj->prototype;
    } while (obj);

    return nullptr;
}

js_Property* jsV_setproperty(js_State* J, js_Object* obj, const js_StringNode name) {
    js_Property *result;

    if (!obj->extensible) {
        result = property_lookup_on_object(obj, name);
        if (J->strict && !result)
            js_typeerror(J, "object is non-extensible");
        return result;
    }

    obj->properties = insert(J, obj, obj->properties, name, &result);
    if (!result->prevp) {
        result->prevp = obj->tailp;
        *obj->tailp = result;
        obj->tailp = &result->next;
    }
    return result;
}

void jsV_delproperty(js_State* J, js_Object* obj, const js_StringNode name) {
    obj->properties = prop_delete(J, obj, obj->properties, name);
}

/* Flatten hierarchy of enumerable properties into an iterator object */

static int itshadow(js_State* J, js_Object* top, js_Object* bot, const js_StringNode name) {
    int k;
    while (top != bot) {
        js_Property *prop = property_lookup_on_object(top, name);
        if (prop && !(prop->atts & JS_DONTENUM))
            return 1;
        if (top->type == JS_CSTRING) {
            if (js_isarrayindex(J, js_strnode_cstr(name), &k) && k < top->u.s.length)
                return 1;
        }
        top = top->prototype;
    }
    return 0;
}

static void itwalk(js_State *J, js_Object *io, js_Object *top, int own) {
    js_Object *obj = top;
    js_Iterator *tail = NULL;
    char buf[32];
    int k;

#define ITADD(x) \
	js_Iterator *node = (js_Iterator*)js_malloc(J, sizeof *node); \
	node->name = x; \
	node->next = NULL; \
	if (!tail) { \
		io->u.iter.head = tail = node; \
	} else { \
		tail->next = node; \
		tail = node; \
	}

    while (obj) {
        js_Property *prop = obj->head;
        while (prop) {
            if (!(prop->atts & JS_DONTENUM) && !itshadow(J, top, obj, prop->name)) {
                ITADD(prop->name);
            }
            prop = prop->next;
        }

        if (obj->type == JS_CSTRING) {
            for (k = 0; k < obj->u.s.length; ++k) {
                js_itoa(buf, k);
                auto bufp = js_intern(buf);
                if (!itshadow(J, top, obj, bufp)) {
                    ITADD(bufp);
                }
            }
        }

        if (own)
            break;
        obj = obj->prototype;
    }
}

js_Object *jsV_newiterator(js_State *J, js_Object *obj, int own) {
    js_Object *io = jsV_newobject(J, JS_CITERATOR, NULL);
    io->u.iter.target = obj;
    io->u.iter.head = NULL;
    itwalk(J, io, obj, own);
    return io;
}

const js_StringNode jsV_nextiterator(js_State *J, js_Object *io) {
    int k;
    if (io->type != JS_CITERATOR) {
        js_typeerror(J, "not an iterator");
    }

    while (io->u.iter.head) {
        js_Iterator *next = io->u.iter.head->next;
        const js_StringNode name = io->u.iter.head->name;
        js_free(J, io->u.iter.head);
        io->u.iter.head = next;

        if (io->u.iter.target->vgetproperty(name))
            return name;

        if (io->u.iter.target->type == JS_CSTRING)
            if (js_isarrayindex(J, js_strnode_cstr(name), &k) && k < io->u.iter.target->u.s.length)
                return name;
    }
    return NULL;
}

/* Walk all the properties and delete them one by one for arrays */

void jsV_resizearray(js_State *J, js_Object *obj, int newlen) {
    char buf[32];
    js_StringNode s;
    int k;
    if (newlen < obj->u.a.length) {
        if (obj->u.a.length > obj->count * 2) {
            js_Object *it = jsV_newiterator(J, obj, 1);
            while ((s = jsV_nextiterator(J, it))) {
                auto sstr = js_strnode_cstr(s);
                k = jsV_numbertointeger(jsV_stringtonumber(J, sstr));
                if (k >= newlen && !strcmp(sstr, jsV_numbertostring(J, buf, k)))
                    jsV_delproperty(J, obj, s);
            }
        } else {
            for (k = newlen; k < obj->u.a.length; ++k) {
                jsV_delproperty(J, obj, js_intern(js_itoa(buf, k)));
            }
        }
    }
    obj->u.a.length = newlen;
}
