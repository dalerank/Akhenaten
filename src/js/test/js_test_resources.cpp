#include "js/test/js_test_common.h"

#include "content/content.h"
#include "graphics/image.h"
#include "platform/arguments.h"

static pcstr __test_data_dir() {
    return vfs::platform_file_manager_get_base_path();
}
ANK_FUNCTION(__test_data_dir);

static bool __test_data_dir_from_cli() {
    return g_args.is("data_directory_cli", false);
}
ANK_FUNCTION(__test_data_dir_from_cli);

static int __test_paks_loaded() {
    return image_paks_loaded_count();
}
ANK_FUNCTION(__test_paks_loaded);

static bool __test_pak_loaded(pcstr name) {
    return image_pak_is_loaded(xstring(name));
}
ANK_FUNCTION_1(__test_pak_loaded);
