#include "jsi.h"
#include "jsvalue.h"
#include "jsbuiltin.h"

#include <stdio.h>
#include <string.h>

#define QQ(X) #X
#define Q(X) QQ(X)

/* Get a line from source code by line number */
static const char *jsB_getline(const char *source, int target_line, char *buf, size_t bufsize)
{
  if (!source || target_line < 1 || !buf || bufsize < 2) {
    return NULL;
  }
  
  int current_line = 1;
  const char *line_start = source;
  const char *p = source;
  
  /* Find the target line */
  while (*p && current_line < target_line) {
    if (*p == '\n') {
      current_line++;
      line_start = p + 1;
    }
    p++;
  }
  
  /* If we didn't reach the target line */
  if (current_line != target_line) {
    return NULL;
  }
  
  /* Find the end of the line */
  const char *line_end = line_start;
  while (*line_end && *line_end != '\n' && *line_end != '\r') {
    line_end++;
  }
  
  /* Copy the line to buffer */
  size_t len = line_end - line_start;
  if (len >= bufsize - 1) {
    len = bufsize - 2;
  }
  
  if (len > 0) {
    memcpy(buf, line_start, len);
  }
  buf[len] = '\0';
  
  return buf;
}

/* Read a line from a file */
static const char *jsB_getline_from_file(const char *filename, int target_line, char *buf, size_t bufsize)
{
  if (!filename || target_line < 1 || !buf || bufsize < 2) {
    return NULL;
  }
  
  FILE *f = fopen(filename, "r");
  if (!f) {
    return NULL;
  }
  
  int current_line = 1;
  
  while (current_line < target_line && fgets(buf, bufsize, f)) {
    current_line++;
  }
  
  if (current_line == target_line && fgets(buf, bufsize, f)) {
    /* Remove trailing newline */
    size_t len = strlen(buf);
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
      buf[--len] = '\0';
    }
    fclose(f);
    return buf;
  }
  
  fclose(f);
  return NULL;
}

/* Find the position of property access in a line (simple heuristic).
 * For assignments like "a.b.c = x.y", the error is on the LHS member
 * access, so we return the last dot before the '='. For non-assignment
 * expressions we fall back to the last dot in the whole expression. */
static int jsB_find_property_access_pos(const char *line)
{
  const char *p = line;
  const char *assign_pos = NULL;
  const char *last_dot = NULL;
  const char *last_dot_before_assign = NULL;

  while (*p && *p != ';' && *p != '\n') {
    /* Stop at line comments */
    if (*p == '/' && *(p + 1) == '/')
      break;

    if (*p == '=') {
      char prev = (p > line) ? *(p - 1) : 0;
      char next = *(p + 1);
      /* Ignore ==, !=, <=, >= */
      if (prev != '!' && prev != '<' && prev != '>' && prev != '=' && next != '=') {
        if (!assign_pos)
          assign_pos = p;
      }
    } else if (*p == '.') {
      last_dot = p;
      if (!assign_pos)
        last_dot_before_assign = p;
    }
    p++;
  }

  /* Prefer last dot in LHS of assignment, fall back to last dot overall */
  const char *target = last_dot_before_assign ? last_dot_before_assign : last_dot;
  if (target)
    return (int)(target - line);

  /* Last resort: find last alphanumeric character */
  p = line;
  int last_alphanum = -1;
  while (*p && *p != ';' && *p != '/' && *p != '\n') {
    if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9'))
      last_alphanum = (int)(p - line);
    p++;
  }

  return last_alphanum > 0 ? last_alphanum : (int)strlen(line) - 1;
}

/* Find the position to highlight for "cannot convert undefined to object".
 * If prop_name is given (the property that was being accessed on the undefined
 * value), we search for the dot before it and then step back one more dot so
 * the arrow lands on the object expression that returned undefined.
 * Example: "window.mothball.enabled = ..."  prop_name="enabled"
 *   -> find ".enabled", then the previous "." -> points at ".mothball". */
static int jsB_find_error_pos(const char *line, const char *prop_name)
{
  if (prop_name && prop_name[0]) {
    /* Build ".propname" and search for it */
    size_t plen = strlen(prop_name);
    const char *p = line;
    while (*p) {
      if (*p == '.' && strncmp(p + 1, prop_name, plen) == 0) {
        /* Make sure it's not a prefix of a longer name */
        char after = p[1 + plen];
        if (!((after >= 'a' && after <= 'z') || (after >= 'A' && after <= 'Z') ||
              (after >= '0' && after <= '9') || after == '_' || after == '$')) {
          /* Found ".propname" at position (p - line).
           * Now search backwards for the previous dot — that's the object
           * expression that evaluated to undefined. */
          if (p > line) {
            const char *q = p - 1;
            while (q > line && *q != '.') q--;
            if (*q == '.')
              return (int)(q - line);
          }
          /* No previous dot: point at this dot */
          return (int)(p - line);
        }
      }
      p++;
    }
  }

  /* Fallback: last dot before '=' (LHS), or last dot overall */
  return jsB_find_property_access_pos(line);
}

/* Format detailed error message with code context */
static void jsB_format_detailed_error(js_State *J, const char *error_type, const char *value_type, char *outbuf, size_t outsize)
{
  char linebuf[512];
  const char *line_text = NULL;
  int line_num = 0;
  const char *filename = NULL;
  
  /* Get the current line number and filename from trace */
  if (J->tracetop >= 0) {
    line_num = J->trace[J->tracetop].line;
    filename = J->trace[J->tracetop].file;
  }
  
  /* Try to get the source line */
  if (filename && line_num > 0) {
    /* First try from current source if available */
    if (J->source && J->filename && strcmp(J->filename, filename) == 0) {
      line_text = jsB_getline(J->source, line_num, linebuf, sizeof(linebuf));
    }
    /* If not available, try reading from file */
    if (!line_text && filename && strcmp(filename, "native") != 0) {
      line_text = jsB_getline_from_file(filename, line_num, linebuf, sizeof(linebuf));
    }
  }
  
  /* Format the error message */
  if (line_text && line_text[0]) {
    /* Trim leading whitespace for display */
    const char *trimmed = line_text;
    while (*trimmed == ' ' || *trimmed == '\t')
      trimmed++;

    /* Find position of the error using runtime property name when available */
    int error_pos = jsB_find_error_pos(trimmed, J->pending_prop);
    if (error_pos < 0) error_pos = 0;
    if (error_pos > (int)strlen(trimmed) - 1) error_pos = (int)strlen(trimmed) - 1;
    
    /* Build detailed error message with code context */
    snprintf(outbuf, outsize,
             "cannot convert %s to %s\n"
             "\n"
             "%s\n"
             "%*s^\n"
             "%*s|\n"
             "%*s+-- %s",
             value_type, error_type,
             trimmed,
             error_pos, "",
             error_pos, "",
             error_pos, "", value_type);
  } else {
    /* Fallback to simple message */
    snprintf(outbuf, outsize, "cannot convert %s to %s", value_type, error_type);
  }
}

static void jsB_stacktrace(js_State *J, int skip)
{
  int n;
  char buf[256];
  for (n = J->tracetop - skip; n >= 0; --n) {
    const char *name = J->trace[n].name;
    const char *file = J->trace[n].file;
    int line = J->trace[n].line;
    if (line > 0) {
      if (name[0])
        snprintf(buf, sizeof buf, "\n\tat %s (%s:%d)", name, file, line);
      else
        snprintf(buf, sizeof buf, "\n\tat %s:%d", file, line);
    } else
      snprintf(buf, sizeof buf, "\n\tat %s (%s)", name, file);
    js_pushstring(J, buf);
    if (n < J->tracetop - skip)
      js_concat(J);
  }
}

static void Ep_toString(js_State *J)
{
  char buf[256];
  const char *name = "Error";
  const char *message = "";

  if (!js_isobject(J, -1))
    js_typeerror(J, "not an object");

  if (js_hasproperty(J, 0, "name"))
    name = js_tostring(J, -1);
  if (js_hasproperty(J, 0, "message"))
    message = js_tostring(J, -1);

  snprintf(buf, sizeof buf, "%s: %s", name, message);
  js_pushstring(J, buf);

  if (js_hasproperty(J, 0, "stackTrace"))
    js_concat(J);
}

static int jsB_ErrorX(js_State *J, js_Object *prototype)
{
  int top = js_gettop(J);
  js_pushobject(J, jsV_newobject(J, JS_CERROR, prototype));
  if (top > 1) {
    js_pushstring(J, js_tostring(J, 1));
    js_setproperty(J, -2, "message");
  }
  jsB_stacktrace(J, 1);
  js_setproperty(J, -2, "stackTrace");
  return 1;
}

static void js_newerrorx(js_State *J, const char *message, js_Object *prototype)
{
  js_pushobject(J, jsV_newobject(J, JS_CERROR, prototype));
  js_pushstring(J, message);
  js_setproperty(J, -2, "message");
  jsB_stacktrace(J, 0);
  js_setproperty(J, -2, "stackTrace");
}

/* Create a detailed type error with code context */
void js_newtypeerror_detailed(js_State *J, const char *value_type, const char *target_type)
{
  char detailed_msg[1024];
  jsB_format_detailed_error(J, target_type, value_type, detailed_msg, sizeof(detailed_msg));
  
  js_pushobject(J, jsV_newobject(J, JS_CERROR, J->TypeError_prototype));
  js_pushstring(J, detailed_msg);
  js_setproperty(J, -2, "message");
  jsB_stacktrace(J, 0);
  js_setproperty(J, -2, "stackTrace");
}

/* Throw a detailed type error with code context */
JS_NORETURN void js_typeerror_detailed(js_State *J, const char *value_type, const char *target_type)
{
  js_newtypeerror_detailed(J, value_type, target_type);
  js_throw(J);
}

#define DERROR(name, Name) \
  static void jsB_##Name(js_State *J) { \
    jsB_ErrorX(J, J->Name##_prototype); \
  } \
  void js_new##name(js_State *J, const char *s) { \
    js_newerrorx(J, s, J->Name##_prototype); \
  } \
  void js_##name(js_State *J, const char *fmt, ...) { \
    va_list ap; \
    char buf[256]; \
    va_start(ap, fmt); \
    vsnprintf(buf, sizeof buf, fmt, ap); \
    va_end(ap); \
    js_newerrorx(J, buf, J->Name##_prototype); \
    js_throw(J); \
  }

DERROR(error, Error)
DERROR(evalerror, EvalError)
DERROR(rangeerror, RangeError)
DERROR(referenceerror, ReferenceError)
DERROR(syntaxerror, SyntaxError)
DERROR(typeerror, TypeError)
DERROR(urierror, URIError)

#undef DERROR

void jsB_initerror(js_State *J)
{
  js_pushobject(J, J->Error_prototype);
  {
      jsB_props(J, "name", "Error");
      jsB_props(J, "message", "an error has occurred");
      jsB_propf(J, "Error.prototype.toString", Ep_toString, 0);
  }
  js_newcconstructor(J, jsB_Error, jsB_Error, "Error", 1);
  js_defglobal(J, "Error", JS_DONTENUM);

  #define IERROR(NAME) \
    js_pushobject(J, J->NAME##_prototype); \
    jsB_props(J, "name", Q(NAME)); \
    js_newcconstructor(J, jsB_##NAME, jsB_##NAME, Q(NAME), 1); \
    js_defglobal(J, Q(NAME), JS_DONTENUM);

  IERROR(EvalError);
  IERROR(RangeError);
  IERROR(ReferenceError);
  IERROR(SyntaxError);
  IERROR(TypeError);
  IERROR(URIError);

  #undef IERROR
}
