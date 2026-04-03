#include "jsi.h"
#include "jsvalue.h"
#include "jsbuiltin.h"

static void jsB_new_Object(js_State *J)
{
	if (js_isundefined(J, 1) || js_isnull(J, 1))
		js_newobject(J);
	else
		js_pushobject(J, J->toobject(1));
}

static void jsB_Object(js_State *J)
{
	if (js_isundefined(J, 1) || js_isnull(J, 1))
		js_newobject(J);
	else
		js_pushobject(J, J->toobject(1));
}

static void Op_toString(js_State *J)
{
	js_Object *self = J->toobject(0);
	switch (self->type) {
	case JS_COBJECT: J->pushliteral(js_intern("[object Object]")); break;
	case JS_CARRAY: J->pushliteral(js_intern("[object Array]")); break;
	case JS_CFUNCTION: J->pushliteral(js_intern("[object Function]")); break;
	case JS_CSCRIPT: J->pushliteral(js_intern("[object Function]")); break;
	case JS_CCFUNCTION: J->pushliteral(js_intern("[object Function]")); break;
	case JS_CERROR: J->pushliteral(js_intern("[object Error]")); break;
	case JS_CBOOLEAN: J->pushliteral(js_intern("[object Boolean]")); break;
	case JS_CNUMBER: J->pushliteral(js_intern("[object Number]")); break;
	case JS_CVEC2I: J->pushliteral(js_intern("[object Vec2i]")); break;
	case JS_CSTRING: J->pushliteral(js_intern("[object String]")); break;
	case JS_CREGEXP: J->pushliteral(js_intern("[object RegExp]")); break;
	case JS_CDATE: J->pushliteral(js_intern("[object Date]")); break;
	case JS_CMATH: J->pushliteral(js_intern("[object Math]")); break;
	case JS_CJSON: J->pushliteral(js_intern("[object JSON]")); break;
	case JS_CITERATOR: J->pushliteral(js_intern("[Iterator]")); break;
	case JS_CUSERDATA:
        J->pushliteral(js_intern("[object "));
        J->pushliteral(js_intern(self->u.user.tag));
		js_concat(J);
        J->pushliteral(js_intern("]"));
		js_concat(J);
		break;
	case JS_CPTR:
        J->pushliteral(js_intern("[object Bound]"));
		break;
	}
}

static void Op_valueOf(js_State *J)
{
	js_copy(J, 0);
}

static js_StringNode op_prop_vec2_x = js_intern("x");
static js_StringNode op_prop_vec2_y = js_intern("y");

static void Op_hasOwnProperty(js_State *J)
{
	js_Object *self = J->toobject(0);
	auto name = js_tostring(J, 1);
	if (self->type == JS_CVEC2I && (name == op_prop_vec2_x || name == op_prop_vec2_y)) {
		js_pushboolean(J, 1);
		return;
	}
	js_Property *ref = J->vget_ownproperty(self, name);
	js_pushboolean(J, ref != NULL);
}

static void Op_isPrototypeOf(js_State *J)
{
	js_Object *self = J->toobject(0);
	if (J->isobject(1)) {
		js_Object *V = J->toobject(1);
		do {
			V = V->prototype;
			if (V == self) {
				js_pushboolean(J, 1);
				return;
			}
		} while (V);
	}
	js_pushboolean(J, 0);
}

static void Op_propertyIsEnumerable(js_State *J)
{
	js_Object *self = J->toobject(0);
	auto name = js_tostring(J, 1);
	if (self->type == JS_CVEC2I && (name == op_prop_vec2_x || name == op_prop_vec2_y)) {
		js_pushboolean(J, 1);
		return;
	}
	js_Property *ref = J->vget_ownproperty(self, name);
	js_pushboolean(J, ref && !(ref->atts & JS_DONTENUM));
}

static void O_getPrototypeOf(js_State *J)
{
	js_Object *obj;
	if (!J->isobject(1))
		js_typeerror(J, "not an object");
	obj = J->toobject(1);
	if (obj->prototype)
		js_pushobject(J, obj->prototype);
	else
		js_pushnull(J);
}

static js_StringNode property_writable = js_intern("writable");
static js_StringNode property_enumerable = js_intern("enumerable");
static js_StringNode property_configurable = js_intern("configurable");
static js_StringNode property_value = js_intern("value");
static js_StringNode property_get = js_intern("get");
static js_StringNode property_set = js_intern("set");
static js_StringNode property_length = js_intern("length");
static js_StringNode property_source = js_intern("source");
static js_StringNode property_global = js_intern("global");
static js_StringNode property_ignoreCase = js_intern("ignoreCase");
static js_StringNode property_multiline = js_intern("multiline");
static js_StringNode property_lastIndex = js_intern("lastIndex");

static void O_getOwnPropertyDescriptor(js_State *J)
{
	js_Object *obj;
	js_Property *ref;
	if (!J->isobject(1)) {
		js_typeerror(J, "not an object");
	}

	obj = J->toobject(1);
	{
		js_StringNode key = js_tostring(J, 2);
		if (obj->type == JS_CVEC2I && (key == op_prop_vec2_x || key == op_prop_vec2_y)) {
			js_newobject(J);
			js_pushnumber(J, key == op_prop_vec2_x ? obj->u.vec2.x : obj->u.vec2.y);
			js_setproperty(J, -2, property_value);
			js_pushboolean(J, 1);
			js_setproperty(J, -2, property_writable);
			js_pushboolean(J, 1);
			js_setproperty(J, -2, property_enumerable);
			js_pushboolean(J, 0);
			js_setproperty(J, -2, property_configurable);
			return;
		}
	}
	ref = obj->vgetproperty(js_tostring(J, 2));
	if (!ref)
		J->pushundefined();
	else {
		js_newobject(J);
		if (!ref->getter && !ref->setter) {
			js_pushvalue(J, ref->value);
            js_setproperty(J, -2, property_value);
			js_pushboolean(J, !(ref->atts & JS_READONLY));
            js_setproperty(J, -2, property_writable);
		} else {
			if (ref->getter)
				js_pushobject(J, ref->getter);
			else
				J->pushundefined();
            js_setproperty(J, -2, property_get);
			if (ref->setter)
				js_pushobject(J, ref->setter);
			else
				J->pushundefined();
            js_setproperty(J, -2, property_set);
		}
		js_pushboolean(J, !(ref->atts & JS_DONTENUM));
        js_setproperty(J, -2, property_enumerable);
		js_pushboolean(J, !(ref->atts & JS_DONTCONF));
        js_setproperty(J, -2, property_configurable);
	}
}

static void O_getOwnPropertyNames(js_State *J)
{
	js_Object *obj;
	js_Property *ref;
	int k;
	int i;

	if (!J->isobject(1))
		js_typeerror(J, "not an object");
	obj = J->toobject(1);

	js_newarray(J);

	i = 0;
	for (ref = obj->head; ref; ref = ref->next) {
		J->pushliteral(ref->name);
		js_setindex(J, -2, i++);
	}

	if (obj->type == JS_CARRAY) {
        J->pushliteral(property_length);
		js_setindex(J, -2, i++);
	}

	if (obj->type == JS_CSTRING) {
        J->pushliteral(property_length);
		js_setindex(J, -2, i++);
		for (k = 0; k < obj->u.s.length; ++k) {
			js_pushnumber(J, k);
			js_setindex(J, -2, i++);
		}
	}

	if (obj->type == JS_CREGEXP) {
        J->pushliteral(property_source);
		js_setindex(J, -2, i++);
        J->pushliteral(property_global);
		js_setindex(J, -2, i++);
        J->pushliteral(property_ignoreCase);
		js_setindex(J, -2, i++);
        J->pushliteral(property_multiline);
		js_setindex(J, -2, i++);
        J->pushliteral(property_lastIndex);
		js_setindex(J, -2, i++);
	}

	if (obj->type == JS_CVEC2I) {
        J->pushliteral(op_prop_vec2_x);
		js_setindex(J, -2, i++);
        J->pushliteral(op_prop_vec2_y);
		js_setindex(J, -2, i++);
	}
}

static void ToPropertyDescriptor(js_State *J, js_Object *obj, js_StringNode name, js_Object *desc)
{
	int haswritable = 0;
	int hasvalue = 0;
	int enumerable = 0;
	int configurable = 0;
	int writable = 0;
	int atts = 0;

	js_pushobject(J, obj);
	js_pushobject(J, desc);

	if (J->hasproperty(-1, property_writable)) {
		haswritable = 1;
		writable = js_toboolean(J, -1);
		js_pop(J, 1);
	}

    if (J->hasproperty(-1, property_enumerable)) {
		enumerable = js_toboolean(J, -1);
		js_pop(J, 1);
	}

    if (J->hasproperty(-1, property_configurable)) {
		configurable = js_toboolean(J, -1);
		js_pop(J, 1);
	}

    if (J->hasproperty(-1, property_value)) {
		hasvalue = 1;
		js_setproperty(J, -3, name);
	}

	if (!writable) atts |= JS_READONLY;
	if (!enumerable) atts |= JS_DONTENUM;
	if (!configurable) atts |= JS_DONTCONF;

	if (J->hasproperty(-1, property_get)) {
		if (haswritable || hasvalue)
			js_typeerror(J, "value/writable and get/set attributes are exclusive");
	} else {
		J->pushundefined();
	}

	if (J->hasproperty(-2, property_set)) {
		if (haswritable || hasvalue)
			js_typeerror(J, "value/writable and get/set attributes are exclusive");
	} else {
		J->pushundefined();
	}

	js_defaccessor(J, -4, name, atts);

	js_pop(J, 2);
}

static void O_defineProperty(js_State *J)
{
	if (!J->isobject(1)) js_typeerror(J, "not an object");
	if (!J->isobject(3)) js_typeerror(J, "not an object");
	ToPropertyDescriptor(J, J->toobject(1), js_tostring(J, 2), J->toobject(3));
	js_copy(J, 1);
}

static void O_defineProperties(js_State *J)
{
	js_Object *props;
	js_Property *ref;

	if (!J->isobject(1)) js_typeerror(J, "not an object");
	if (!J->isobject(2)) js_typeerror(J, "not an object");

	props = J->toobject(2);
	for (ref = props->head; ref; ref = ref->next) {
		if (!(ref->atts & JS_DONTENUM)) {
			js_pushvalue(J, ref->value);
			ToPropertyDescriptor(J, J->toobject(1), ref->name, J->toobject(-1));
			js_pop(J, 1);
		}
	}

	js_copy(J, 1);
}

static void O_create(js_State *J)
{
	js_Object *obj;
	js_Object *proto;
	js_Object *props;
	js_Property *ref;

	if (J->isobject(1))
		proto = J->toobject(1);
	else if (js_isnull(J, 1))
		proto = NULL;
	else
		js_typeerror(J, "not an object or null");

	obj = jsV_newobject(J, JS_COBJECT, proto);
	js_pushobject(J, obj);

	if (js_isdefined(J, 2)) {
		if (!J->isobject(2)) js_typeerror(J, "not an object");
		props = J->toobject(2);
		for (ref = props->head; ref; ref = ref->next) {
			if (!(ref->atts & JS_DONTENUM)) {
				if (ref->value.type != JS_TOBJECT) js_typeerror(J, "not an object");
				ToPropertyDescriptor(J, obj, ref->name, ref->value.u.object);
			}
		}
	}
}

static void O_keys(js_State *J)
{
	js_Object *obj;
	js_Property *ref;
	int k;
	int i;

	if (!J->isobject(1))
		js_typeerror(J, "not an object");

	obj = J->toobject(1);

	js_newarray(J);

	i = 0;
	for (ref = obj->head; ref; ref = ref->next) {
		if (!(ref->atts & JS_DONTENUM)) {
			J->pushliteral(ref->name);
			js_setindex(J, -2, i++);
		}
	}

	if (obj->type == JS_CVEC2I) {
		J->pushliteral(op_prop_vec2_x);
		js_setindex(J, -2, i++);
		J->pushliteral(op_prop_vec2_y);
		js_setindex(J, -2, i++);
	}

	if (obj->type == JS_CSTRING) {
		for (k = 0; k < obj->u.s.length; ++k) {
			js_pushnumber(J, k);
			js_setindex(J, -2, i++);
		}
	}
}

static void O_preventExtensions(js_State *J)
{
    if (!J->isobject(1)) {
        js_typeerror(J, "not an object");
    }

	J->toobject(1)->extensible = 0;
	js_copy(J, 1);
}

static void O_isExtensible(js_State *J)
{
    if (!J->isobject(1)) {
        js_typeerror(J, "not an object");
    }

	js_pushboolean(J, J->toobject(1)->extensible);
}

static void O_seal(js_State *J)
{
	js_Object *obj;
	js_Property *ref;

	if (!J->isobject(1)) {
		js_typeerror(J, "not an object");
	}

	obj = J->toobject(1);
	obj->extensible = 0;

	for (ref = obj->head; ref; ref = ref->next) {
		ref->atts |= JS_DONTCONF;
	}

	js_copy(J, 1);
}

static void O_isSealed(js_State *J)
{
	js_Object *obj;
	js_Property *ref;

	if (!J->isobject(1))
		js_typeerror(J, "not an object");

	obj = J->toobject(1);
	if (obj->extensible) {
		js_pushboolean(J, 0);
		return;
	}

	for (ref = obj->head; ref; ref = ref->next) {
		if (!(ref->atts & JS_DONTCONF)) {
			js_pushboolean(J, 0);
			return;
		}
	}

	js_pushboolean(J, 1);
}

static void O_freeze(js_State *J)
{
	js_Object *obj;
	js_Property *ref;

	if (!J->isobject(1))
		js_typeerror(J, "not an object");

	obj = J->toobject(1);
	obj->extensible = 0;

	for (ref = obj->head; ref; ref = ref->next)
		ref->atts |= JS_READONLY | JS_DONTCONF;

	js_copy(J, 1);
}

static void O_isFrozen(js_State *J)
{
	js_Object *obj;
	js_Property *ref;

	if (!J->isobject(1)) {
		js_typeerror(J, "not an object");
	}

	obj = J->toobject(1);
	if (obj->extensible) {
		js_pushboolean(J, 0);
		return;
	}

	for (ref = obj->head; ref; ref = ref->next) {
		if (!(ref->atts & (JS_READONLY | JS_DONTCONF))) {
			js_pushboolean(J, 0);
			return;
		}
	}

	js_pushboolean(J, 1);
}

void jsB_initobject(js_State *J)
{
	js_pushobject(J, J->Object_prototype);
	{
		jsB_propf(J, js_intern("Object.prototype.toString"), Op_toString, 0);
		jsB_propf(J, js_intern("Object.prototype.toLocaleString"), Op_toString, 0);
		jsB_propf(J, js_intern("Object.prototype.valueOf"), Op_valueOf, 0);
		jsB_propf(J, js_intern("Object.prototype.hasOwnProperty"), Op_hasOwnProperty, 1);
		jsB_propf(J, js_intern("Object.prototype.isPrototypeOf"), Op_isPrototypeOf, 1);
		jsB_propf(J, js_intern("Object.prototype.propertyIsEnumerable"), Op_propertyIsEnumerable, 1);
	}
    js_newcconstructor(J, jsB_Object, jsB_new_Object, js_intern("Object"), 1);
	{
		/* ES5 */
		jsB_propf(J, js_intern("Object.getPrototypeOf"), O_getPrototypeOf, 1);
		jsB_propf(J, js_intern("Object.getOwnPropertyDescriptor"), O_getOwnPropertyDescriptor, 2);
		jsB_propf(J, js_intern("Object.getOwnPropertyNames"), O_getOwnPropertyNames, 1);
		jsB_propf(J, js_intern("Object.create"), O_create, 2);
		jsB_propf(J, js_intern("Object.defineProperty"), O_defineProperty, 3);
		jsB_propf(J, js_intern("Object.defineProperties"), O_defineProperties, 2);
		jsB_propf(J, js_intern("Object.seal"), O_seal, 1);
		jsB_propf(J, js_intern("Object.freeze"), O_freeze, 1);
		jsB_propf(J, js_intern("Object.preventExtensions"), O_preventExtensions, 1);
		jsB_propf(J, js_intern("Object.isSealed"), O_isSealed, 1);
		jsB_propf(J, js_intern("Object.isFrozen"), O_isFrozen, 1);
		jsB_propf(J, js_intern("Object.isExtensible"), O_isExtensible, 1);
		jsB_propf(J, js_intern("Object.keys"), O_keys, 1);
	}
    js_defglobal(J, js_intern("Object"), JS_DONTENUM);
}
