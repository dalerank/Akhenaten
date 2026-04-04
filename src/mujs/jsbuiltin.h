#pragma once

#include "mujs.h"

#include <cstddef>
#include <cstring>

void jsB_init(js_State *J);
void jsB_initobject(js_State *J);
void jsB_initarray(js_State *J);
void jsB_initfunction(js_State *J);
void jsB_initboolean(js_State *J);
void jsB_initnumber(js_State *J);
void jsB_initvec2i(js_State *J);
void jsB_initstring(js_State *J);
void jsB_initregexp(js_State *J);
void jsB_initerror(js_State *J);
void jsB_initmath(js_State *J);

/* Detailed error functions */
void js_newtypeerror_detailed(js_State *J, const char *value_type, const char *target_type);
JS_NORETURN void js_typeerror_detailed(js_State *J, const char *value_type, const char *target_type);
void jsB_initjson(js_State *J);
void jsB_initdate(js_State *J);

void jsB_propf(js_State* J, const js_StringNode name, js_CFunction cfun, int n);
void jsB_propn(js_State* J, const js_StringNode name, double number);
void jsB_props(js_State *J, const js_StringNode name, const char *string);

typedef struct js_Buffer { int n, m; char s[64]; } js_Buffer;

static void js_putc(js_State *J, js_Buffer **sbp, int c)
{
	js_Buffer *sb = *sbp;
	const int hsize = static_cast<int>(offsetof(js_Buffer, s));
	if (!sb) {
		sb = static_cast<js_Buffer*>(js_frame_alloc(J, static_cast<int>(sizeof(js_Buffer))));
		sb->n = 0;
		sb->m = static_cast<int>(sizeof(sb->s));
		*sbp = sb;
	} else if (sb->n == sb->m) {
		const int old_m = sb->m;
		sb->m *= 2;
		js_Buffer *nb = static_cast<js_Buffer*>(js_frame_alloc(J, hsize + sb->m));
		memcpy(nb, sb, static_cast<size_t>(hsize + old_m));
		*sbp = nb;
		sb = nb;
	}
	sb->s[sb->n++] = c;
}

static inline void js_puts(js_State *J, js_Buffer **sb, const char *s)
{
	while (*s)
		js_putc(J, sb, *s++);
}

static inline void js_putm(js_State *J, js_Buffer **sb, const char *s, const char *e)
{
	while (s < e)
		js_putc(J, sb, *s++);
}
