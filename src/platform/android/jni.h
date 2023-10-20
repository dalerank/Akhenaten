#pragma once

#ifdef __ANDROID__

#include <jni.h>

typedef struct {
    JNIEnv *env;
    jclass nclass;
    jobject activity;
    jmethodID method;
} jni_function_handler;

#define CLASS_AKHENATEN_ACTIVITY "com/github/dalerank/akhenaten/AkhenatenMainActivity"
#define CLASS_FILE_MANAGER "com/github/dalerank/akhenaten/FileManager"

int jni_init_function_handler(const char *class_name, jni_function_handler *handler);
int jni_get_static_method_handler(const char *class_name, const char *method_name, const char *method_signature, jni_function_handler *handler);
int jni_get_method_handler(const char *class_name, const char *method_name, const char *method_signature, jni_function_handler *handler);
void jni_destroy_function_handler(jni_function_handler *handler);

#endif // __ANDROID__
