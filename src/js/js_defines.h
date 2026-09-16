#pragma once

#define DEF_GLOBAL_OBJECT(J,name) J->newobject();
#define REGISTER_FUNCTION(J, func, name, params) J->newcfunction(func, js_intern(name), params); js_setproperty(J, -2, js_intern(name));
#define REGISTER_GLOBAL_OBJECT(J,name) js_setglobal(J, #name);
#define REGISTER_GLOBAL_FUNCTION(J,func,name,params) J->newcfunction(func, js_intern(name), params); js_setglobal(J, name);
#define REGISTER_GLOBAL_CONSTANT(J,name) J->newnumber(name); js_setglobal(J, #name);