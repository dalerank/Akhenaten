#include "jni.h"

#include "SDL.h"

#include <string>

static void jni_clear_pending_exception(JNIEnv *env)
{
    if (env && env->ExceptionCheck()) {
        env->ExceptionClear();
    }
}

static std::string jni_slash_to_dotted(const char *class_name)
{
    std::string dotted(class_name ? class_name : "");
    for (char &c : dotted) {
        if (c == '/') {
            c = '.';
        }
    }
    return dotted;
}

static jclass jni_load_class(JNIEnv *env, jobject activity, const char *class_name)
{
    if (!env || !activity || !class_name) {
        return nullptr;
    }

    jclass activity_class = env->GetObjectClass(activity);
    if (!activity_class) {
        jni_clear_pending_exception(env);
        return nullptr;
    }

    jmethodID get_class_loader = env->GetMethodID(activity_class, "getClassLoader", "()Ljava/lang/ClassLoader;");
    if (!get_class_loader) {
        jni_clear_pending_exception(env);
        env->DeleteLocalRef(activity_class);
        return nullptr;
    }

    jobject class_loader = env->CallObjectMethod(activity, get_class_loader);
    if (!class_loader) {
        jni_clear_pending_exception(env);
        env->DeleteLocalRef(activity_class);
        return nullptr;
    }

    jclass class_loader_class = env->FindClass("java/lang/ClassLoader");
    if (!class_loader_class) {
        jni_clear_pending_exception(env);
        env->DeleteLocalRef(class_loader);
        env->DeleteLocalRef(activity_class);
        return nullptr;
    }

    jmethodID load_class = env->GetMethodID(class_loader_class, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    if (!load_class) {
        jni_clear_pending_exception(env);
        env->DeleteLocalRef(class_loader_class);
        env->DeleteLocalRef(class_loader);
        env->DeleteLocalRef(activity_class);
        return nullptr;
    }

    const std::string dotted = jni_slash_to_dotted(class_name);
    jstring jclass_name = env->NewStringUTF(dotted.c_str());
    jclass result = (jclass) env->CallObjectMethod(class_loader, load_class, jclass_name);

    env->DeleteLocalRef(jclass_name);
    env->DeleteLocalRef(class_loader_class);
    env->DeleteLocalRef(class_loader);
    env->DeleteLocalRef(activity_class);

    if (!result) {
        jni_clear_pending_exception(env);
    }

    return result;
}

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
    if (class_name) {
        handler->nclass = jni_load_class(handler->env, handler->activity, class_name);
    } else {
        handler->nclass = handler->env->GetObjectClass(handler->activity);
        if (!handler->nclass) {
            jni_clear_pending_exception(handler->env);
        }
    }
    if (handler->nclass == NULL) {
        SDL_Log("Problem loading class '%s'.", class_name ? class_name : "<activity>");
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
        jni_clear_pending_exception(handler->env);
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
        jni_clear_pending_exception(handler->env);
        SDL_Log("Problem loading method '%s' from class '%s'.", method_name, class_name ? class_name : "<activity>");
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
