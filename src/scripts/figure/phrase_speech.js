log_info("akhenaten: figure phrase speech started")

// OG figure_speech_sounds (figure_phrase.c, figure_speech_sounds.json): the speech id of each figure type's
// phrases. -3: by the god of the priest's temple (230 + god), -4: by the walker the festival guy stands for.
// OG has one hunter type whose speech follows the climate's prey; the remake splits it by prey.
figure_speech_sounds = [
    { type: FIGURE_IMMIGRANT, speech: 202 }
    { type: FIGURE_EMIGRANT, speech: 203 }
    { type: FIGURE_HOMELESS, speech: 204 }
    { type: FIGURE_CART_PUSHER, speech: 222 }
    { type: FIGURE_LABOR_SEEKER, speech: 213 }
    { type: FIGURE_TAX_COLLECTOR, speech: 245 }
    { type: FIGURE_ARCHITECT, speech: 243 }
    { type: FIGURE_STORAGEYARD_CART, speech: 222 }
    { type: FIGURE_FIREMAN, speech: 242 }
    { type: FIGURE_JUGGLER, speech: 226 }
    { type: FIGURE_MUSICIAN, speech: 227 }
    { type: FIGURE_DANCER, speech: 228 }
    { type: FIGURE_SENET_PLAYER, speech: 229 }
    { type: FIGURE_TRADE_CARAVAN, speech: 225 }
    { type: FIGURE_TRADE_SHIP, speech: 224 }
    { type: FIGURE_TRADE_CARAVAN_DONKEY, speech: 225 }
    { type: FIGURE_ROBBER, speech: 205 }
    { type: FIGURE_TOMB_ROBER, speech: 248 }
    { type: FIGURE_FISHING_BOAT, speech: 211 }
    { type: FIGURE_MARKET_TRADER, speech: 220 }
    { type: FIGURE_PRIEST, speech: -3 }
    { type: FIGURE_TEACHER, speech: 235 }
    { type: FIGURE_LIBRARIAN, speech: 236 }
    { type: FIGURE_DENTIST, speech: 238 }
    { type: FIGURE_PHYSICIAN, speech: 239 }
    { type: FIGURE_HERBALIST, speech: 241 }
    { type: FIGURE_EMBALMER, speech: 240 }
    { type: FIGURE_WORKER, speech: 212 }
    { type: FIGURE_DOCKER, speech: 222 }
    { type: FIGURE_MARKET_BUYER, speech: 219 }
    { type: FIGURE_NOBLES, speech: 207 }
    { type: FIGURE_TOWER_SENTRY, speech: 252 }
    { type: FIGURE_DELIVERY_BOY, speech: 221 }
    { type: FIGURE_OSTRICH_HUNTER, speech: 209 }
    { type: FIGURE_ANTELOPE_HUNTER, speech: 208 }
    { type: FIGURE_BIRDS_HUNTER, speech: 210 }
    { type: FIGURE_LUMBERJACK, speech: 214 }
    { type: FIGURE_TRANSPORT_SHIP, speech: 250 }
    { type: FIGURE_WARSHIP, speech: 249 }
    { type: FIGURE_CARPENTER, speech: 216 }
    { type: FIGURE_BRICKLAYER, speech: 217 }
    { type: FIGURE_STONEMASON, speech: 218 }
    { type: FIGURE_LABORER, speech: 212 }
    { type: FIGURE_WATER_CARRIER, speech: 237 }
    { type: FIGURE_CONSTABLE, speech: 244 }
    { type: FIGURE_MAGISTRATE, speech: 246 }
    { type: FIGURE_REED_GATHERER, speech: 215 }
    { type: FIGURE_FESTIVAL_GUY, speech: -4 }
    { type: FIGURE_SLED_PULLER, speech: 212 }
    { type: FIGURE_PLAGUED_CITIZEN, speech: 206 }
    { type: FIGURE_ZOOKEEPER, speech: 309 }
    { type: FIGURE_TOMB_ARTISAN, speech: 247 }
]

// OG phrase_names_walkers / phrase_names_zookeeper (sound_data.c): the speech file of each phrase id, by speech id.
figure_speech_phrases = [
    { speech: 202, files: ["Immigrant_e01.wav", "Immigrant_e02.wav", "Immigrant_e03.wav"] }
    { speech: 203, files: ["Emigrant_e01.wav", "Emigrant_e02.wav", "Emigrant_e03.wav", "Emigrant_e04.wav", "Emigrant_e05.wav"] }
    { speech: 204, files: ["vagrant_e01.wav", "vagrant_e02.wav"] }
    { speech: 205, files: ["thief_e01.wav", "thief_e02.wav", "thief_e03.wav", "thief_e04.wav"] }
    { speech: 206, files: ["disease_e01.wav"] }
    { speech: 207, files: ["scribe_g01.wav", "scribe_g02.wav", "scribe_g03.wav", "scribe_g04.wav", "scribe_g05.wav", "scribe_g06.wav", "scribe_g07.wav", "scribe_g08.wav", "scribe_g09.wav", "scribe_g10.wav", "scribe_e01.wav"] }
    { speech: 208, files: ["hunt_ant_e01.wav", "hunt_ant_e02.wav"] }
    { speech: 209, files: ["hunt_ostrich_e01.wav", "hunt_ostrich_e02.wav"] }
    { speech: 210, files: ["hunt_bird_e01.wav", "hunt_bird_e02.wav"] }
    { speech: 211, files: ["fishing_e01.wav", "fishing_e02.wav", "fishing_e03.wav"] }
    { speech: 212, files: ["worker_g01.wav", "worker_g02.wav", "worker_g03.wav", "worker_g04.wav", "worker_g05.wav", "worker_g06.wav", "worker_g07.wav", "worker_g08.wav", "worker_g09.wav", "worker_g10.wav", "worker_e01.wav", "worker_e02.wav", "worker_e03.wav"] }
    { speech: 213, files: ["labor_g01.wav", "labor_g02.wav", "labor_g03.wav", "labor_g04.wav", "labor_g05.wav", "labor_g06.wav", "labor_g07.wav", "labor_g08.wav", "labor_g09.wav", "labor_g10.wav", "labor_e01.wav", "labor_e02.wav"] }
    { speech: 214, files: ["woodcutter_e01.wav", "woodcutter_e02.wav"] }
    { speech: 215, files: ["reed_e01.wav", "reed_e02.wav"] }
    { speech: 216, files: ["carpenter_e01.wav", "carpenter_e02.wav"] }
    { speech: 217, files: ["brick_e01.wav", "brick_e02.wav"] }
    { speech: 218, files: ["stone_e01.wav", "stone_e02.wav"] }
    { speech: 219, files: ["mkt_buyer_g01.wav", "mkt_buyer_g02.wav", "mkt_buyer_g03.wav", "mkt_buyer_g04.wav", "mkt_buyer_g05.wav", "mkt_buyer_g06.wav", "mkt_buyer_g07.wav", "mkt_buyer_g08.wav", "mkt_buyer_g09.wav", "mkt_buyer_g10.wav", "mkt_buyer_e01.wav", "mkt_buyer_e02.wav"] }
    { speech: 220, files: ["mkt_seller_e01.wav", "mkt_seller_e02.wav"] }
    { speech: 221, files: ["marketboy_e01.wav", "marketboy_e02.wav", "marketboy_e03.wav"] }
    { speech: 222, files: ["cartpusher_e01.wav", "cartpusher_e02.wav", "cartpusher_e03.wav"] }
    { speech: 223, files: ["dockpusher_e01.wav", "dockpusher_e02.wav", "dockpusher_e03.wav"] }
    { speech: 224, files: ["barge_e01.wav", "barge_e02.wav", "barge_e03.wav", "barge_e04.wav", "barge_e05.wav"] }
    { speech: 225, files: ["caravan_e01.wav", "caravan_e02.wav", "caravan_e03.wav", "caravan_e04.wav", "caravan_e05.wav"] }
    { speech: 226, files: ["juggler_g01.wav", "juggler_g02.wav", "juggler_g03.wav", "juggler_g04.wav", "juggler_g05.wav", "juggler_g06.wav", "juggler_g07.wav", "juggler_g08.wav", "juggler_g09.wav", "juggler_g10.wav", "juggler_e01.wav"] }
    { speech: 227, files: ["musician_g01.wav", "musician_g02.wav", "musician_g03.wav", "musician_g04.wav", "musician_g05.wav", "musician_g06.wav", "musician_g07.wav", "musician_g08.wav", "musician_g09.wav", "musician_g10.wav", "musician_e01.wav"] }
    { speech: 228, files: ["dancer_g01.wav", "dancer_g02.wav", "dancer_g03.wav", "dancer_g04.wav", "dancer_g05.wav", "dancer_g06.wav", "dancer_g07.wav", "dancer_g08.wav", "dancer_g09.wav", "dancer_g10.wav", "dancer_e01.wav"] }
    { speech: 229, files: ["senet_g01.wav", "senet_g02.wav", "senet_g03.wav", "senet_g04.wav", "senet_g05.wav", "senet_g06.wav", "senet_g07.wav", "senet_g08.wav", "senet_g09.wav", "senet_g10.wav", "senet_e01.wav"] }
    { speech: 230, files: ["priest_osiris_g01.wav", "priest_osiris_g02.wav", "priest_osiris_g03.wav", "priest_osiris_g04.wav", "priest_osiris_g05.wav", "priest_osiris_g06.wav", "priest_osiris_g07.wav", "priest_osiris_g08.wav", "priest_osiris_g09.wav", "priest_osiris_g10.wav", "priest_osiris_e01.wav", "priest_osiris_e02.wav"] }
    { speech: 231, files: ["priest_ra_g01.wav", "priest_ra_g02.wav", "priest_ra_g03.wav", "priest_ra_g04.wav", "priest_ra_g05.wav", "priest_ra_g06.wav", "priest_ra_g07.wav", "priest_ra_g08.wav", "priest_ra_g09.wav", "priest_ra_g10.wav", "priest_ra_e01.wav", "priest_ra_e02.wav"] }
    { speech: 232, files: ["priest_ptah_g01.wav", "priest_ptah_g02.wav", "priest_ptah_g03.wav", "priest_ptah_g04.wav", "priest_ptah_g05.wav", "priest_ptah_g06.wav", "priest_ptah_g07.wav", "priest_ptah_g08.wav", "priest_ptah_g09.wav", "priest_ptah_g10.wav", "priest_ptah_e01.wav", "priest_ptah_e02.wav"] }
    { speech: 233, files: ["priest_seth_g01.wav", "priest_seth_g02.wav", "priest_seth_g03.wav", "priest_seth_g04.wav", "priest_seth_g05.wav", "priest_seth_g06.wav", "priest_seth_g07.wav", "priest_seth_g08.wav", "priest_seth_g09.wav", "priest_seth_g10.wav", "priest_seth_e01.wav", "priest_seth_e02.wav"] }
    { speech: 234, files: ["priest_bast_g01.wav", "priest_bast_g02.wav", "priest_bast_g03.wav", "priest_bast_g04.wav", "priest_bast_g05.wav", "priest_bast_g06.wav", "priest_bast_g07.wav", "priest_bast_g08.wav", "priest_bast_g09.wav", "priest_bast_g10.wav", "priest_bast_e01.wav", "priest_bast_e02.wav", "priest_bast_e03.wav", "priest_bast_e04.wav"] }
    { speech: 235, files: ["teacher_g01.wav", "teacher_g02.wav", "teacher_g03.wav", "teacher_g04.wav", "teacher_g05.wav", "teacher_g06.wav", "teacher_g07.wav", "teacher_g08.wav", "teacher_g09.wav", "teacher_g10.wav", "teacher_e01.wav"] }
    { speech: 236, files: ["library_g01.wav", "library_g02.wav", "library_g03.wav", "library_g04.wav", "library_g05.wav", "library_g06.wav", "library_g07.wav", "library_g08.wav", "library_g09.wav", "library_g10.wav", "library_e01.wav"] }
    { speech: 237, files: ["water_g01.wav", "water_g02.wav", "water_g03.wav", "water_g04.wav", "water_g05.wav", "water_g06.wav", "water_g07.wav", "water_g08.wav", "water_g09.wav", "water_g10.wav"] }
    { speech: 238, files: ["dentist_g01.wav", "dentist_g02.wav", "dentist_g03.wav", "dentist_g04.wav", "dentist_g05.wav", "dentist_g06.wav", "dentist_g07.wav", "dentist_g08.wav", "dentist_g09.wav", "dentist_g10.wav"] }
    { speech: 239, files: ["doctor_g01.wav", "doctor_g02.wav", "doctor_g03.wav", "doctor_g04.wav", "doctor_g05.wav", "doctor_g06.wav", "doctor_g07.wav", "doctor_g08.wav", "doctor_g09.wav", "doctor_g10.wav", "doctor_e01.wav"] }
    { speech: 240, files: ["embalmer_g01.wav", "embalmer_g02.wav", "embalmer_g03.wav", "embalmer_g04.wav", "embalmer_g05.wav", "embalmer_g06.wav", "embalmer_g07.wav", "embalmer_g08.wav", "embalmer_g09.wav", "embalmer_g10.wav", "embalmer_e01.wav"] }
    { speech: 241, files: ["nothing.wav", "apothecary_e02.wav", "apothecary_e03.wav"] }
    { speech: 242, files: ["fireman_g01.wav", "fireman_g02.wav", "fireman_g03.wav", "fireman_g04.wav", "fireman_g05.wav", "fireman_g06.wav", "fireman_g07.wav", "fireman_g08.wav", "fireman_g09.wav", "fireman_g10.wav", "fireman_e01.wav", "fireman_e02.wav", "fireman_e03.wav"] }
    { speech: 243, files: ["engineer_g01.wav", "engineer_g02.wav", "engineer_g03.wav", "engineer_g04.wav", "engineer_g05.wav", "engineer_g06.wav", "engineer_g07.wav", "engineer_g08.wav", "engineer_g09.wav", "engineer_g10.wav", "engineer_e01.wav", "engineer_e02.wav"] }
    { speech: 244, files: ["police_g01.wav", "police_g02.wav", "police_g03.wav", "police_g04.wav", "police_g05.wav", "police_g06.wav", "police_g07.wav", "police_g08.wav", "police_g09.wav", "police_g10.wav", "police_e01.wav", "police_e02.wav", "police_e03.wav", "police_e04.wav", "police_e05.wav", "police_e06.wav", "police_e07.wav", "police_e08.wav"] }
    { speech: 245, files: ["taxman_g01.wav", "taxman_g02.wav", "taxman_g03.wav", "taxman_g04.wav", "taxman_g05.wav", "taxman_g06.wav", "taxman_g07.wav", "taxman_g08.wav", "taxman_g09.wav", "taxman_g10.wav", "taxman_e01.wav", "taxman_e02.wav", "taxman_e03.wav"] }
    { speech: 246, files: ["magistrate_g01.wav", "magistrate_g02.wav", "magistrate_g03.wav", "magistrate_g04.wav", "magistrate_g05.wav", "magistrate_g06.wav", "magistrate_g07.wav", "magistrate_g08.wav", "magistrate_g09.wav", "magistrate_g10.wav", "magistrate_e01.wav", "magistrate_e02.wav", "magistrate_e03.wav", "magistrate_e04.wav", "magistrate_e05.wav"] }
    { speech: 247, files: ["artisan_e01.wav", "artisan_e02.wav"] }
    { speech: 248, files: ["robber_e01.wav", "robber_e02.wav"] }
    { speech: 249, files: ["warship_e01.wav", "warship_e02.wav", "warship_e03.wav", "warship_e04.wav", "warship_e05.wav"] }
    { speech: 250, files: ["transport_e01.wav", "transport_e02.wav", "transport_e03.wav", "transport_e04.wav"] }
    { speech: 251, files: ["CHARIOT.wav"] }
    { speech: 252, files: ["guard_e01.wav", "guard_e02.wav", "guard_e03.wav", "guard_e04.wav"] }
    { speech: 309, files: ["zookeeper_e01.wav", "zookeeper_e02.wav", "zookeeper_e03.wav", "zookeeper_e04.wav", "zookeeper_e05.wav", "zookeeper_e06.wav", "zookeeper_e07.wav", "zookeeper_e08.wav", "zookeeper_e09.wav", "zookeeper_e10.wav"] }
]
