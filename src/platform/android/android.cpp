#include "android.h"

#include "core/bstring.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "platform/android/asset_handler.h"
#include "platform/android/jni.h"
#include "content/content.h"

#include <SDL.h>
#include <string.h>

static volatile int has_directory;
static vfs::path path;

static const char *get_pharaoh_path()
{
    jni_function_handler handler;
    if (!jni_get_static_method_handler(CLASS_FILE_MANAGER, "getPharaohPath", "(L" CLASS_AKHENATEN_ACTIVITY ";)Ljava/lang/String;", &handler)) {
        jni_destroy_function_handler(&handler);
        return NULL;
    }

    jobject result = handler.env->CallStaticObjectMethod(handler.nclass, handler.method, handler.activity);
    const char *temp_path = handler.env->GetStringUTFChars((jstring) result, NULL);
    path = temp_path;
    handler.env->ReleaseStringUTFChars((jstring) result, temp_path);
    handler.env->DeleteLocalRef(result);

    jni_destroy_function_handler(&handler);

    return !path.empty() ? path.c_str() : nullptr;
}

const char *android_show_pharaoh_path_dialog(int again)
{
    jni_function_handler handler;
    if (jni_get_method_handler(CLASS_AKHENATEN_ACTIVITY, "showDirectorySelection", "(Z)V", &handler)) {
        handler.env->CallVoidMethod(handler.activity, handler.method, again ? JNI_TRUE : JNI_FALSE);
    }
    jni_destroy_function_handler(&handler);

    has_directory = 0;

    while (!has_directory) {
        SDL_WaitEventTimeout(NULL, 2000);
    }

    return get_pharaoh_path();
}

float android_get_screen_density()
{
    jni_function_handler handler;
    float result = 1.0f;
    if (jni_get_method_handler(CLASS_AKHENATEN_ACTIVITY, "getScreenDensity", "()F", &handler)) {
        result = (float) handler.env->CallFloatMethod(handler.activity, handler.method);
    }
    jni_destroy_function_handler(&handler);
    return result;
}

int android_get_file_descriptor(const char *filename, const char *mode)
{
    int result = 0;
    jni_function_handler handler;
    if (!jni_get_static_method_handler(CLASS_FILE_MANAGER, "openFileDescriptor",
        "(L" CLASS_AKHENATEN_ACTIVITY ";Ljava/lang/String;Ljava/lang/String;)I", &handler)) {
        jni_destroy_function_handler(&handler);
        return 0;
    }
    jstring jfilename = handler.env->NewStringUTF(filename);
    jstring jmode = handler.env->NewStringUTF(mode);
    result = (int) handler.env->CallStaticIntMethod(handler.nclass, handler.method, handler.activity, jfilename, jmode);
    handler.env->DeleteLocalRef(jfilename);
    handler.env->DeleteLocalRef(jmode);
    jni_destroy_function_handler(&handler);

    return result;
}

void *android_open_asset(const char *asset, const char *mode)
{
    return asset_handler_open_asset(asset, mode);
}

int android_set_base_path(const char *path)
{
    int result = 0;
    jni_function_handler handler;
    if (!jni_get_static_method_handler(CLASS_FILE_MANAGER, "setBaseUri", "(Ljava/lang/String;)I", &handler)) {
        jni_destroy_function_handler(&handler);
        return 0;
    }
    jstring jpath = handler.env->NewStringUTF(path);
    result = (int) handler.env->CallStaticIntMethod(handler.nclass, handler.method, jpath);
    handler.env->DeleteLocalRef(jpath);
    jni_destroy_function_handler(&handler);

    return result;
}

pcstr ASSETS_DIRECTORY = "Assets";
int android_get_directory_contents(const char *dir, int type, const char *extension, int (*callback)(const char *))
{
    if (strncmp(dir, ASSETS_DIRECTORY, strlen(ASSETS_DIRECTORY)) == 0) {
        return asset_handler_get_directory_contents(dir + strlen(ASSETS_DIRECTORY), type, extension, callback);
    }
    jni_function_handler handler;
    jni_function_handler get_name;
    jni_function_handler get_last_modified_time;

    if (!jni_get_static_method_handler(CLASS_FILE_MANAGER, "getDirectoryFileList",
        "(L" CLASS_AKHENATEN_ACTIVITY ";Ljava/lang/String;ILjava/lang/String;)[L" CLASS_FILE_MANAGER "$FileInfo;", &handler)) {
        jni_destroy_function_handler(&handler);
        return vfs::LIST_ERROR;
    }
    if (!jni_get_method_handler(CLASS_FILE_MANAGER "$FileInfo", "getName", "()Ljava/lang/String;", &get_name)) {
        jni_destroy_function_handler(&get_name);
        jni_destroy_function_handler(&handler);
        return vfs::LIST_ERROR;
    }
    if (!jni_get_method_handler(CLASS_FILE_MANAGER "$FileInfo", "getModifiedTime", "()J", &get_last_modified_time)) {
        jni_destroy_function_handler(&get_last_modified_time);
        jni_destroy_function_handler(&get_name);
        jni_destroy_function_handler(&handler);
        return vfs::LIST_ERROR;
    }

    jstring jdir = handler.env->NewStringUTF(dir);
    jstring jextension = handler.env->NewStringUTF(extension);
    jobjectArray result = (jobjectArray) handler.env->CallStaticObjectMethod(handler.nclass, handler.method, handler.activity, jdir, type, jextension);
    handler.env->DeleteLocalRef(jdir);
    handler.env->DeleteLocalRef(jextension);
    int match = vfs::LIST_NO_MATCH;
    int len = handler.env->GetArrayLength(result);
    for (int i = 0; i < len; ++i) {
        jobject jfile_info = (jobject) handler.env->GetObjectArrayElement(result, i);
        jstring jfilename = (jstring) handler.env->CallObjectMethod(jfile_info, get_name.method);
        const char *filename = handler.env->GetStringUTFChars(jfilename, NULL);
        long last_modified = (long) handler.env->CallLongMethod(jfile_info, get_last_modified_time.method);
        match = callback(filename);
        handler.env->ReleaseStringUTFChars((jstring) jfilename, filename);
        handler.env->DeleteLocalRef(jfilename);
        handler.env->DeleteLocalRef(jfile_info);
        if (match == vfs::LIST_MATCH) {
            break;
        }
    }
    handler.env->DeleteLocalRef(result);
    jni_destroy_function_handler(&get_last_modified_time);
    jni_destroy_function_handler(&get_name);
    jni_destroy_function_handler(&handler);
    return match;
}

int android_remove_file(const char *filename)
{
    int result = 0;
    jni_function_handler handler;
    if (!jni_get_static_method_handler(CLASS_FILE_MANAGER, "deleteFile",
        "(L" CLASS_AKHENATEN_ACTIVITY ";Ljava/lang/String;)Z", &handler)) {
        jni_destroy_function_handler(&handler);
        return 0;
    }
    jstring jfilename = handler.env->NewStringUTF(filename);
    result = (int) handler.env->CallStaticBooleanMethod(handler.nclass, handler.method, handler.activity, jfilename);
    handler.env->DeleteLocalRef(jfilename);
    jni_destroy_function_handler(&handler);

    return result;
}

extern "C" JNIEXPORT void JNICALL Java_com_github_dalerank_akhenaten_AkhenatenMainActivity_gotDirectory(JNIEnv *env, jobject thiz)
{
    has_directory = 1;
}

void platform_show_virtual_keyboard(void)
{
    if (!SDL_IsTextInputActive()) {
        SDL_StartTextInput();
    }
}

void platform_hide_virtual_keyboard(void)
{
    if (SDL_IsTextInputActive()) {
        SDL_StopTextInput();
    }
}
