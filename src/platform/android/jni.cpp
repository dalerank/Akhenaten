#include "jni.h"

#include "SDL.h"

int jni_init_function_handler(const char *class_name, jni_function_handler *handler)
{
    handler->env = (JNIEnv *)SDL_AndroidGetJNIEnv();
    if (handler->env == NULL) {
        SDL_Log("Problem setting up JNI environment");
        return 0;
    }
    handler->activity = (jobject) SDL_AndroidGetActivity();
    if (handler->activity == NULL) {
        SDL_Log("Problem loading the activity.");
        return 0;
    }
    if(class_name) {
        handler->nclass = handler->env->FindClass(class_name);
    } else {
        handler->nclass = handler->env->GetObjectClass(handler->activity);
    }
    if (handler->nclass == NULL) {
        SDL_Log("Problem loading class '%s'.", class_name);
        return 0;
    }
    return 1;
}

int jni_get_static_method_handler(
    const char *class_name, const char *method_name, const char *method_signature, jni_function_handler *handler)
{
    if (!jni_init_function_handler(class_name, handler)) {
        return 0;
    }
    handler->method = handler->env->GetStaticMethodID(handler->nclass, method_name, method_signature);
    if (handler->method == NULL) {
        SDL_Log("Problem loading static method '%s' from class '%s'.", method_name, class_name);
        return 0;
    }
    return 1;
}

int jni_get_method_handler(
    const char *class_name, const char *method_name, const char *method_signature, jni_function_handler *handler)
{
    if (!jni_init_function_handler(class_name, handler)) {
        return 0;
    }
    handler->method = handler->env->GetMethodID(handler->nclass, method_name, method_signature);
    if (handler->method == NULL) {
        SDL_Log("Problem loading method '%s' from class '%s'.", method_name, class_name);
        return 0;
    }
    return 1;
}

void jni_destroy_function_handler(jni_function_handler *handler)
{
    if (!handler) {
        return;
    }
    if (handler->env) {
        if (handler->activity) {
            handler->env->DeleteLocalRef(handler->activity);
        }
        if (handler->nclass) {
            handler->env->DeleteLocalRef(handler->nclass);
        }
    }
    handler->env = NULL;
    handler->nclass = NULL;
    handler->activity = NULL;
    handler->method = NULL;
}
