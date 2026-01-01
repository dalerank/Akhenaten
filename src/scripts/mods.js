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
    ]
}