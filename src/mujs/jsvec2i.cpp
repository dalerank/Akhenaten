#include "jsi.h"
#include "jsvalue.h"
#include "jsbuiltin.h"

#include <cstdio>

static void jsB_new_Vec2i(js_State *J)
{
	int x = js_gettop(J) > 1 ? js_tointeger(J, 1) : 0;
	int y = js_gettop(J) > 2 ? js_tointeger(J, 2) : 0;
	js_newvec2i(J, x, y);
}

static void jsB_Vec2i(js_State *J)
{
	jsB_new_Vec2i(J);
}

static void Vp_toString(js_State *J)
{
	js_Object *self = J->toobject(0);
	char buf[48];
	if (self->type != JS_CVEC2I)
		js_typeerror(J, "not a vec2i");
	snprintf(buf, sizeof buf, "Vec2i(%d,%d)", self->u.vec2.x, self->u.vec2.y);
	J->pushstring(buf);
}

void jsB_initvec2i(js_State *J)
{
	J->Vec2i_prototype->u.vec2.x = 0;
	J->Vec2i_prototype->u.vec2.y = 0;

	js_pushobject(J, J->Vec2i_prototype);
	{
		jsB_propf(J, js_intern("Vec2i.prototype.toString"), Vp_toString, 0);
		jsB_propf(J, js_intern("Vec2i.prototype.toLocaleString"), Vp_toString, 0);
	}
	js_newcconstructor(J, jsB_Vec2i, jsB_new_Vec2i, js_intern("Vec2i"), 2);
    js_defglobal(J, js_intern("Vec2i"), JS_DONTENUM);
}
