#pragma once

js_Environment *jsR_newenvironment(js_State *J, js_Object *variables, js_Environment *outer);

struct js_Environment
{
	js_Environment *outer;
	js_Object *variables;

	js_Environment *gcnext;
	int gcmark;
};