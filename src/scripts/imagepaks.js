log_info("akhenaten: imagepaks started")

imagepaks = [
  {id: PACK_UNLOADED, name:"Pharaoh_Unloaded", index:0, system:true},  // 0     --> 682
  {id: PACK_SPR_MAIN, name:"SprMain", index:700, system:false}, // 700   --> 11007
  {id: PACK_GENERAL, name:"Pharaoh_General", index:11706, system:false}, // 11706 --> 11866
  {id: PACK_TERRAIN, name:"Pharaoh_Terrain", index:14252, system:false}, // 14252 --> 15767 (+64)
  {id: PACK_SPR_AMBIENT, name:"SprAmbient", index:15831, system:false}, // 15831 --> 18765
  {id: PACK_MASTABA, name:"mastaba", index:25000, system:false}, // 25000 --> 25000 + 429
  {id: PACK_TEMPLE_RA, name:"Temple_ra", index:32000, system:false}, // 32000 --> 32000 + 239
  {id: PACK_TEMPLE_NILE, name:"Temple_nile", index:32250, system:false}, // 32250 --> 32250 + 239
  {id: PACK_TEMPLE_PTAH, name:"Temple_ptah", index:32500, system:false}, // 32500 --> 32500 + 239
  {id: PACK_TEMPLE_SETH, name:"Temple_seth", index:32750, system:false}, // 32750 --> 32750 + 239
  {id: PACK_TEMPLE_BAST, name:"Temple_bast", index:33000, system:false}, // 33000 --> 33000 + 239
  {id: PACK_EXPANSION, name:"Expansion", index:23035, system:false}, // 23035 --> 23935
  {id: PACK_EMPIRE, name:"Empire", index:20305, system:false}, // 20305 --> 20506 (+177)
  {id: PACK_EXPANSION_SPR, name:"SprMain2", index:20683, system:false}, // 20683 --> 23035
  {id: PACK_LIB_EXTRA, name:"LibExtra", index:24000, system:false}, // 24000 --> 24030
  {id: PACK_LIB_EXTRA_2, name:"LibExtra2", index:24040, system:false}, // 24040 --> 24080
  {id: PACK_LIB_MAUS_CARRYOVER, name:"MausCarryover", index:24080, system:false}, // 24080 --> 24090
  {id: PACK_LIB_MAUSOLEUM_0, name:"mausoleum0_extra", index:24090, system:false}, // 24090 --> 24110  
  {id: PACK_LIB_MAUSOLEUM_1, name:"mausoleum1_extra", index:24110, system:false}, // 24110 --> 24130
  {id: PACK_LIB_MAUSOLEUM_2, name:"mausoleum2_extra", index:24130, system:false}, // 24130 --> 24150
  {id: PACK_PYRAMID, name:"Pyramid", index:34000, system:false}, // 34000 --> 34230
  {id: PACK_BENT_PYRAMID, name:"bent_pyramid", index:34250, system:false}, // 34250 --> 34500
  {id: PACK_MUDBRICK_PYRAMID, name:"mudbrick_pyramid", index:34500, system:false}, // 34500 --> 34700
  {id: PACK_ABUSIMBEL, name:"AbuSimbel", index:35900, system:false}, // 35900 --> 35970
  {id: PACK_CAESAREUM_1, name:"caesareum1", index:36000, system:false}, // 36000 --> 36010
  {id: PACK_CAESAREUM_2, name:"caesareum2", index:36010, system:false}, // 36010 --> 36020
  {id: PACK_CAESAREUM_3, name:"caesareum3", index:36020, system:false}, // 36020 --> 36030
  {id: PACK_CAESAREUM_4, name:"caesareum4", index:36030, system:false}, // 36030 --> 36040
  {id: PACK_OBELISK_EXTRA, name:"obelisk_extra", index:36040, system:false}, // 36040 --> 36060
  {id: PACK_OBELISK_X3_A, name:"obelisk3x3a", index:36060, system:false}, // 36060 --> 36061
  {id: PACK_OBELISK_X3_B, name:"obelisk3x3b", index:36061, system:false}, // 36061 --> 36062
  {id: PACK_OBELISK_X3_C, name:"obelisk3x3c", index:36062, system:false}, // 36062 --> 36063
  {id: PACK_OBELISK_X5_A, name:"obelisk5x5a", index:36063, system:false}, // 36063 --> 36064
  {id: PACK_OBELISK_X5_B, name:"obelisk5x5b", index:36064, system:false}, // 36064 --> 36065
  {id: PACK_OBELISK_X5_C, name:"obelisk5x5c", index:36065, system:false}, // 36065 --> 36066
  {id: PACK_OBELISK_X5_D, name:"obelisk5x5d", index:36066, system:false}, // 36066 --> 36067
  {id: PACK_OBELISK_X5_E, name:"obelisk5x5e", index:36067, system:false}, // 36067 --> 36068
  {id: PACK_OBELISK_X5_F, name:"obelisk5x5f", index:36068, system:false}, // 36068 --> 36069
  {id: PACK_ENEMY_ASSYRIAN, name:"Assyrian", index:37000, system:false}, // 37000 --> 37900
  {id: PACK_ENEMY_CANAANITE, name:"Canaanite", index:38000, system:false}, // 38000 --> 38860
  {id: PACK_ENEMY_EGYPTIAN, name:"Egyptian", index:39000, system:false}, // 39000 --> 39800
  {id: PACK_ENEMY_BARBARIAN, name:"Enemy_1", index:40000, system:false}, // 40000 --> 40750
  {id: PACK_ENEMY_HITTITE, name:"Hittite", index:41000, system:false}, // 41000 --> 41900
  {id: PACK_ENEMY_HYKSOS, name:"Hyksos", index:42000, system:false}, // 42000 --> 42900
  {id: PACK_ENEMY_KUSHITE, name:"Kushite", index:43000, system:false}, // 43000 --> 42900
  {id: PACK_ENEMY_LIBIAN, name:"Libian", index:44000, system:false}, // 44000 --> 44900
  {id: PACK_ENEMY_NUBIAN, name:"Nubian", index:45000, system:false}, // 45000 --> 45850
  //{id: PACK_CUSTOM, name:"Pharaoh_Custom", index:30000, system:false, custom:true},  // 30000 -->
]
