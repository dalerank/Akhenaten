#include "jsi.h"
#include "jsvalue.h"
#include "jsbuiltin.h"

#include <cstdio>

static js_StringNode property_x = js_intern("x");
static js_StringNode property_y = js_intern("y");

static void vec2i_read_arg(js_State *J, int idx, int *x, int *y) {
	if (js_iscvec2i(J, idx)) {
		js_Object *o = J->toobject(idx);
		*x = o->u.vec2.x;
		*y = o->u.vec2.y;
		return;
	}
	if (J->isobject(idx) && !js_isarray(J, idx)) {
		J->getproperty(idx, property_x);
		*x = js_isnumber(J, -1) ? js_tointeger(J, -1) : 0;
		js_pop(J, 1);
		J->getproperty(idx, property_y);
		*y = js_isnumber(J, -1) ? js_tointeger(J, -1) : 0;
		js_pop(J, 1);
		return;
	}
	*x = js_tointeger(J, idx);
	*y = *x;
}

static js_Object *vec2i_self(js_State *J) {
	js_Object *self = J->toobject(0);
	if (self->type != JS_CVEC2I) {
		js_typeerror(J, "not a vec2i");
	}
	return self;
}

static void jsB_new_Vec2i(js_State *J)
{
	int x = 0;
	int y = 0;
	if (js_gettop(J) > 1 && (J->isobject(1) || js_iscvec2i(J, 1)) && js_gettop(J) <= 2) {
		vec2i_read_arg(J, 1, &x, &y);
	} else {
		x = js_gettop(J) > 1 ? js_tointeger(J, 1) : 0;
		y = js_gettop(J) > 2 ? js_tointeger(J, 2) : x;
	}
	js_newvec2i(J, x, y);
}

static void jsB_Vec2i(js_State *J)
{
	jsB_new_Vec2i(J);
}

static void Vp_toString(js_State *J)
{
	js_Object *self = vec2i_self(J);
	char buf[48];
	snprintf(buf, sizeof buf, "Vec2i(%d,%d)", self->u.vec2.x, self->u.vec2.y);
	J->pushstring(buf);
}

static void Vp_add(js_State *J)
{
	js_Object *self = vec2i_self(J);
	int ox = 0, oy = 0;
	vec2i_read_arg(J, 1, &ox, &oy);
	js_newvec2i(J, self->u.vec2.x + ox, self->u.vec2.y + oy);
}

static void Vp_sub(js_State *J)
{
	js_Object *self = vec2i_self(J);
	int ox = 0, oy = 0;
	vec2i_read_arg(J, 1, &ox, &oy);
	js_newvec2i(J, self->u.vec2.x - ox, self->u.vec2.y - oy);
}

static void Vp_mul(js_State *J)
{
	js_Object *self = vec2i_self(J);
	const int s = js_tointeger(J, 1);
	js_newvec2i(J, self->u.vec2.x * s, self->u.vec2.y * s);
}

static void Vp_div(js_State *J)
{
	js_Object *self = vec2i_self(J);
	const int s = js_tointeger(J, 1);
	if (s == 0) {
		js_newvec2i(J, 0, 0);
		return;
	}
	js_newvec2i(J, self->u.vec2.x / s, self->u.vec2.y / s);
}

void jsB_initvec2i(js_State *J)
{
	J->Vec2i_prototype->u.vec2.x = 0;
	J->Vec2i_prototype->u.vec2.y = 0;

	js_pushobject(J, J->Vec2i_prototype);
	{
		jsB_propf(J, js_intern("Vec2i.prototype.toString"), Vp_toString, 0);
		jsB_propf(J, js_intern("Vec2i.prototype.toLocaleString"), Vp_toString, 0);
		jsB_propf(J, js_intern("Vec2i.prototype.add"), Vp_add, 1);
		jsB_propf(J, js_intern("Vec2i.prototype.sub"), Vp_sub, 1);
		jsB_propf(J, js_intern("Vec2i.prototype.mul"), Vp_mul, 1);
		jsB_propf(J, js_intern("Vec2i.prototype.div"), Vp_div, 1);
	}
	js_newcconstructor(J, jsB_Vec2i, jsB_new_Vec2i, js_intern("Vec2i"), 2);
	js_defglobal(J, js_intern("Vec2i"), JS_DONTENUM);
}
