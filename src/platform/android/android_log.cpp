#include "platform/android/android.h"

#include "content/content.h"
#include "core/app.h"
#include "core/log.h"
#include "core/xvalue.h"

#include <android/log.h>
#include <cstdio>
#include <utility>

struct android_log_t {
    ~android_log_t() {
        close_file();
        if (logcat_sink_ != logs::invalid_sink) {
            logs::remove_sink(logcat_sink_);
            logcat_sink_ = logs::invalid_sink;
        }
    }

    void install() {
        if (installed_) {
            return;
        }
        installed_ = true;

        logs::file_backend backend;
        backend.open = [](pcstr folder, pcstr filename, xstring &out_path) {
            return xvalue<android_log_t>::ref().open_file(folder, filename, out_path);
        };
        backend.close = []() { xvalue<android_log_t>::ref().close_file(); };
        backend.write = [](pcstr prefix, pcstr message) {
            xvalue<android_log_t>::ref().write_file(prefix, message);
        };
        backend.flush = []() { xvalue<android_log_t>::ref().flush_file(); };
        backend.has_pending = []() { return xvalue<android_log_t>::ref().has_pending(); };
        logs::set_file_backend(std::move(backend));

        logcat_sink_ = logs::add_sink([](int priority, pcstr prefix, pcstr message) {
            xvalue<android_log_t>::ref().write_logcat(priority, prefix, message);
        });
    }

    bool open_file(pcstr /*folder*/, pcstr filename, xstring &out_path) {
        close_file();

        out_path = filename;
        vfs::platform_file_manager_remove_file(filename);
        file_ = vfs::platform_file_manager_open_file(filename, "w");
        if (!file_) {
            __android_log_print(ANDROID_LOG_WARN, "ank-and", "Failed to open log file: %s", filename);
            return false;
        }

        const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        fwrite(bom, 1, sizeof(bom), file_);
        fflush(file_);
        dirty_ = false;
        return true;
    }

    void close_file() {
        if (file_) {
            fclose(file_);
            file_ = nullptr;
        }
        dirty_ = false;
    }

    void write_file(pcstr prefix, pcstr message) {
        if (!file_) {
            return;
        }
        fprintf(file_, "%s%s\n", prefix, message);
        dirty_ = true;
    }

    void flush_file() {
        if (file_) {
            fflush(file_);
        }
        dirty_ = false;
    }

    bool has_pending() const {
        return dirty_;
    }

    void write_logcat(int /*priority*/, pcstr prefix, pcstr message) {
        __android_log_print(ANDROID_LOG_INFO, "ank-and", "%s%s", prefix, message);
        android_append_startup_log(message);
    }

    FILE *file_ = nullptr;
    bool dirty_ = false;
    bool installed_ = false;
    logs::sink_handle logcat_sink_ = logs::invalid_sink;
};

void ANK_REGISTER_APPLICATION_MODULE(register_android_log_module) {
    xvalue<android_log_t>::ref().install();
}
