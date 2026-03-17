log_info("akhenaten: mods started")

mods {
    mods_repo [
        { url:"https://api.github.com/repos/dalerank/Akhenaten/contents/mods" }
    ]

    mods_list [
        {
            name : "pharaoh_german_voices"
            desc : "German voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_german_voices.sgx"
            email : "dalerankn8@gmail.com"
        }

        {
            name : "pharaoh_french_voices"
            desc : "French voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_french_voices.sgx"
            email : "dalerankn8@gmail.com"
        }

        {
            name : "pharaoh_spanish_voices"
            desc : "Spanish voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_spanish_voices.sgx"
            email : "dalerankn8@gmail.com"
        }

        {
            name : "pharaoh_polish_voices"
            desc : "Polish voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_polish_voices.sgx"
            email : "dalerankn8@gmail.com"
        }

        {
            name : "pharaoh_italian_voices"
            desc : "Italian voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_italian_voices.sgx"
            email : "dalerankn8@gmail.com"
        }

        {
            name : "pharaoh_russian_voices"
            desc : "Russian voices for the game"
            version : "1.0.0"
            author : "dalerank"
            url : "https://f003.backblazeb2.com/file/akhenaten-mods/pharaoh_russian_voices.sgx"
            email : "dalerankn8@gmail.com"
        }
    ]

    count : __mods_count
    name : __mods_name
    display_name : __mods_display_name
    enabled : __mods_enabled
    download_progress : __mods_download_progress
    downloaded : __mods_downloaded
    download_mod_async : __mods_download_mod_async
    toggle : __mods_toggle
    remount : __mods_remount
}