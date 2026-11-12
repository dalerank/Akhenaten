log_info("akhenaten: imagepaks started")

imagepaks = [
  {id: PACK_UNLOADED, name:"Pharaoh_Unloaded", index:0, system:true},  // 0     --> 682
  {id: PACK_SPR_MAIN, name:"SprMain", index:700, system:false}, // 700   --> 11007
  {id: PACK_GENERAL, name:"Pharaoh_General", index:11706, system:false}, // 11706 --> 11866
  {id: PACK_TERRAIN, name:"Pharaoh_Terrain", index:14252, system:false}, // 14252 --> 15767 (+64)
  {id: PACK_SPR_AMBIENT, name:"SprAmbient", index:15831, system:false}, // 15831 --> 18765
  {id: PACK_MASTABA, name:"mastaba", index:25000, delayed:true, system:false}, // 25000 --> 25000 + 228 + 201
  {id: PACK_TEMPLE_RA, name:"Temple_ra", index:32000, delayed:true,system:false}, // 32000 --> 32000 + 201 + 38
  {id: PACK_TEMPLE_NILE, name:"Temple_nile", index:32250, delayed:true, system:false}, // 32250 --> 32250 + 201 + 38
  {id: PACK_TEMPLE_PTAH, name:"Temple_ptah", index:32500, delayed:true, system:false}, // 32500 --> 32500 + 201 + 38
  {id: PACK_TEMPLE_SETH, name:"Temple_seth", index:32750, delayed:true, system:false}, // 32750 --> 32750 + 201 + 38
  {id: PACK_TEMPLE_BAST, name:"Temple_bast", index:33000, delayed:true, system:false}, // 33000 --> 33000 + 201 + 38
  {id: PACK_EXPANSION, name:"Expansion", index:23035, delayed:true, system:false}, // 23035 --> 23035 + 201 + 699
  {id: PACK_EMPIRE, name:"Empire", index:20305, system:false}, // 20305 --> 20305 + 201 + 1
  {id: PACK_EXPANSION_SPR, name:"SprMain2", index:20683, system:false}, // 20683 --> 23035
  {id: PACK_LIB_EXTRA, name:"LibExtra", index:24000, delayed:true, system:false}, // 24000 --> 24000 + 201 + 27
  {id: PACK_LIB_EXTRA_2, name:"LibExtra2", index:24230, delayed:true, system:false}, // 24230 --> 24230 + 201 + 27
  {id: PACK_LIB_MAUS_CARRYOVER, name:"MausCarryover", index:24460, delayed:true, system:false}, // 24460 --> 24460 + 201 + 9
  // Ground/fence extras (16 frames). Compact + high indices — avoid mastaba@25000 overlap.
  {id: PACK_LIB_MAUSOLEUM_0, name:"mausoleum0_extra", index:52072, delayed:true, system:false, compact:true}, // 16
  {id: PACK_LIB_MAUSOLEUM_1, name:"mausoleum1_extra", index:52088, delayed:true, system:false, compact:true}, // 16
  {id: PACK_LIB_MAUSOLEUM_2, name:"mausoleum2_extra", index:52104, delayed:true, system:false, compact:true}, // 16
  // OG block stage packs maus{skin}_{1..3}{a..d}: 2 camera frames each. Before sphinx@53000.
  {id: PACK_MAUS0_1A, name:"maus0_1a", index:52000, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_1B, name:"maus0_1b", index:52002, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_1C, name:"maus0_1c", index:52004, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_1D, name:"maus0_1d", index:52006, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_2A, name:"maus0_2a", index:52008, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_2B, name:"maus0_2b", index:52010, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_2C, name:"maus0_2c", index:52012, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_2D, name:"maus0_2d", index:52014, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_3A, name:"maus0_3a", index:52016, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_3B, name:"maus0_3b", index:52018, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_3C, name:"maus0_3c", index:52020, delayed:true, system:false, compact:true},
  {id: PACK_MAUS0_3D, name:"maus0_3d", index:52022, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_1A, name:"maus1_1a", index:52024, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_1B, name:"maus1_1b", index:52026, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_1C, name:"maus1_1c", index:52028, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_1D, name:"maus1_1d", index:52030, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_2A, name:"maus1_2a", index:52032, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_2B, name:"maus1_2b", index:52034, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_2C, name:"maus1_2c", index:52036, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_2D, name:"maus1_2d", index:52038, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_3A, name:"maus1_3a", index:52040, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_3B, name:"maus1_3b", index:52042, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_3C, name:"maus1_3c", index:52044, delayed:true, system:false, compact:true},
  {id: PACK_MAUS1_3D, name:"maus1_3d", index:52046, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_1A, name:"maus2_1a", index:52048, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_1B, name:"maus2_1b", index:52050, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_1C, name:"maus2_1c", index:52052, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_1D, name:"maus2_1d", index:52054, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_2A, name:"maus2_2a", index:52056, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_2B, name:"maus2_2b", index:52058, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_2C, name:"maus2_2c", index:52060, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_2D, name:"maus2_2d", index:52062, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_3A, name:"maus2_3a", index:52064, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_3B, name:"maus2_3b", index:52066, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_3C, name:"maus2_3c", index:52068, delayed:true, system:false, compact:true},
  {id: PACK_MAUS2_3D, name:"maus2_3d", index:52070, delayed:true, system:false, compact:true},
  {id: PACK_PYRAMID, name:"Pyramid", index:34000, delayed:true, system:false}, // 34000 --> 34000 + 201 + 228
  {id: PACK_BENT_PYRAMID, name:"bent_pyramid", index:34450, delayed:true, system:false}, // 34250 --> 34250 + 201 + 228
  {id: PACK_MUDBRICK_PYRAMID, name:"mudbrick_pyramid", index:34900, delayed:true, system:false}, // 34900 --> 34900 + 201 + 228
  {id: PACK_STEPPED_PYRAMID, name:"stepped_pyramid", index:35350, delayed:true, system:false}, // 35350 --> 35350 + 201 + 228
  // AbuSimbel.sg3: 201 SYSTEM + 70 layers (backing/2statue/midcut/stairs/cliffs/scaffold).
  // Keep system slots (no compact) — JS uses group ids 1..16 (see abu_simbel.js).
  {id: PACK_ABUSIMBEL, name:"AbuSimbel", index:35850, delayed:true, system:false}, // 35850 --> 35850 + 201 + 70
  // caesareum1..20: one pack per OG stage (0..18, 19 = complete), 9 part images each (compact).
  {id: PACK_CAESAREUM_1, name:"caesareum1", index:36150, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_2, name:"caesareum2", index:36159, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_3, name:"caesareum3", index:36168, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_4, name:"caesareum4", index:36177, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_5, name:"caesareum5", index:36186, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_6, name:"caesareum6", index:36195, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_7, name:"caesareum7", index:36204, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_8, name:"caesareum8", index:36213, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_9, name:"caesareum9", index:36222, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_10, name:"caesareum10", index:36231, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_11, name:"caesareum11", index:36240, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_12, name:"caesareum12", index:36249, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_13, name:"caesareum13", index:36258, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_14, name:"caesareum14", index:36267, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_15, name:"caesareum15", index:36276, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_16, name:"caesareum16", index:36285, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_17, name:"caesareum17", index:36294, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_18, name:"caesareum18", index:36303, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_19, name:"caesareum19", index:36312, delayed:true, system:false, compact:true},
  {id: PACK_CAESAREUM_20, name:"caesareum20", index:36321, delayed:true, system:false, compact:true},
  // LibMaina1..a5 — after Caesareum, before Assyrian@37000 (compact: 2 imgs each).
  {id: PACK_LIB_MAIN_1, name:"LibMaina1", index:36990, delayed:true, system:false, compact:true}, // 2
  {id: PACK_LIB_MAIN_2, name:"LibMaina2", index:36992, delayed:true, system:false, compact:true},
  {id: PACK_LIB_MAIN_3, name:"LibMaina3", index:36994, delayed:true, system:false, compact:true},
  {id: PACK_LIB_MAIN_4, name:"LibMaina4", index:36996, delayed:true, system:false, compact:true},
  {id: PACK_LIB_MAIN_5, name:"LibMaina5", index:36998, delayed:true, system:false, compact:true},
  // LtHouse1..9 stages (1 img); LtHouse10 beacon anim (11). Before obelisk@51000.
  {id: PACK_LTHOUSE_1, name:"LtHouse1", index:50900, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_2, name:"LtHouse2", index:50901, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_3, name:"LtHouse3", index:50902, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_4, name:"LtHouse4", index:50903, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_5, name:"LtHouse5", index:50904, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_6, name:"LtHouse6", index:50905, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_7, name:"LtHouse7", index:50906, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_8, name:"LtHouse8", index:50907, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_9, name:"LtHouse9", index:50908, delayed:true, system:false, compact:true},
  {id: PACK_LTHOUSE_10, name:"LtHouse10", index:50909, delayed:true, system:false, compact:true}, // 11
  // Obelisk/sphinx: dense indices via compact:true (drop SYSTEM.BMP slots). Do not set
  // compact on classic Pharaoh packs — mission maps store absolute image IDs.
  // EXTRA: 16 entries (id1 = ladder); X3 stages a–d: 1 each; X5 stages a–f: 1 each.
  {id: PACK_OBELISK_EXTRA, name:"obelisk_extra", index:51000, delayed:true, system:false, compact:true}, // 16
  {id: PACK_OBELISK_X3_A, name:"obelisk3x3a", index:51016, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X3_B, name:"obelisk3x3b", index:51017, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X3_C, name:"obelisk3x3c", index:51018, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X3_D, name:"obelisk3x3d", index:51019, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_A, name:"obelisk5x5a", index:51020, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_B, name:"obelisk5x5b", index:51021, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_C, name:"obelisk5x5c", index:51022, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_D, name:"obelisk5x5d", index:51023, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_E, name:"obelisk5x5e", index:51024, delayed:true, system:false, compact:true},
  {id: PACK_OBELISK_X5_F, name:"obelisk5x5f", index:51025, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_1_A, name:"sphinx1a", index:53000, delayed:true, system:false, compact:true}, // 2 textures
  {id: PACK_SPHINX_1_B, name:"sphinx1b", index:53002, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_1_C, name:"sphinx1c", index:53004, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_1_D, name:"sphinx1d", index:53006, delayed:true, system:false, compact:true}, // broken asset — keep slot
  {id: PACK_SPHINX_2_A, name:"sphinx2a", index:53008, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_2_B, name:"sphinx2b", index:53010, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_2_C, name:"sphinx2c", index:53012, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_3_A, name:"sphinx3a", index:53014, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_3_B, name:"sphinx3b", index:53016, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_3_C, name:"sphinx3c", index:53018, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_4_A, name:"sphinx4a", index:53020, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_4_B, name:"sphinx4b", index:53022, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_4_C, name:"sphinx4c", index:53024, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_5_A, name:"sphinx5a", index:53026, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_5_B, name:"sphinx5b", index:53028, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_5_C, name:"sphinx5c", index:53030, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_6_A, name:"sphinx6a", index:53032, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_6_B, name:"sphinx6b", index:53034, delayed:true, system:false, compact:true},
  {id: PACK_SPHINX_6_C, name:"sphinx6c", index:53036, delayed:true, system:false, compact:true},
  {id: PACK_SUN_TEMPLE_EXTRA, name:"sun_temple_extra", index:55000, delayed:true, system:false, compact:true}, // 15
  {id: PACK_SUN_TEMPLE_1, name:"suntemple1", index:55015, delayed:true, system:false, compact:true}, // 2
  {id: PACK_SUN_TEMPLE_2, name:"suntemple2", index:55017, delayed:true, system:false, compact:true},
  {id: PACK_SUN_TEMPLE_3, name:"suntemple3", index:55019, delayed:true, system:false, compact:true},
  {id: PACK_TOMB_SETI, name:"TombSeti", index:56000, delayed:true, system:false}, // 56000 --> 56000 + 201 + 221
  {id: PACK_TOMB_SETI_FINAL, name:"TombSetiFin", index:56500, delayed:true, system:false}, // 56500 --> 56500 + 201 + 221
  {id: PACK_TOMB_THUTMOS, name:"TombThut", index:57000, delayed:true, system:false}, // 57000 --> 57000 + 201 + 157
  {id: PACK_TOMB_THUTMOS_FINAL, name:"TombThutFin", index:57400, delayed:true, system:false}, // 57400 --> 57400 + 201 + 157
  {id: PACK_TOMB_TUTANKHAMUN, name:"TombTut", index:57800, delayed:true, system:false}, // 57800 --> 57800 + 201 + 181
  {id: PACK_TOMB_TUTANKHAMUN_FINAL, name:"TombTutFin", index:58200, delayed:true, system:false}, // 58200 --> 58200 + 201 + 181
  {id: PACK_ENEMY_ASSYRIAN, name:"Assyrian", index:37000, delayed:true, system:false}, // 37000 --> 37000 + 898 + 201
  {id: PACK_ENEMY_CANAANITE, name:"Canaanite", index:38100, delayed:true, system:false}, // 38100 --> 38100 + 858 + 201
  {id: PACK_ENEMY_EGYPTIAN, name:"Egyptian", index:39200, delayed:true, system:false}, // 39200 --> 39200 + 778 + 201
  {id: PACK_ENEMY_BARBARIAN, name:"Enemy_1", index:40000, delayed:true, system:false}, // 40000 --> 40000 + 728 + 201
  {id: PACK_ENEMY_HITTITE, name:"Hittite", index:41000, delayed:true, system:false}, // 41000 --> 41000 + 866 + 201
  {id: PACK_ENEMY_HYKSOS, name:"Hyksos", index:42100, delayed:true, system:false}, // 42100 --> 42100 + 898 + 201
  {id: PACK_ENEMY_KUSHITE, name:"Kushite", index:43200, delayed:true, system:false}, // 43200 --> 43200 + 857 + 201
  {id: PACK_ENEMY_LIBIAN, name:"Libian", index:44300, delayed:true, system:false}, // 44300 --> 44300 + 858 + 201
  {id: PACK_ENEMY_NUBIAN, name:"Nubian", index:45400, delayed:true, system:false}, // 45400 --> 45400 + 825 + 201
  {id: PACK_ENEMY_PERSIAN, name:"Persian", index:46500, delayed:true, system:false}, // 46500 --> 46500 + 866 + 201
  {id: PACK_ENEMY_PHOENICIAN, name:"Phoenician", index:47600, delayed:true, system:false}, // 47600 --> 47600 + 834 + 201
  {id: PACK_ENEMY_ROMAN, name:"Roman", index:48700, delayed:true, system:false}, // 48700 --> 48700 + 874 + 201
  {id: PACK_ENEMY_SEAPEOPLE, name:"SeaPeople", index:49800, delayed:true, system:false}, // 49000 --> 49850 + 833 + 201
  {id: PACK_TOMB_RAMSES, name:"TombRam", index:59000, delayed:true, system:false}, // 59000 --> 59000 + 269 + 201
  {id: PACK_TOMB_RAMSES_FINAL, name:"TombRamFin", index:59500, delayed:true, system:false}, // 59500 --> 59500 + 269 + 201
  {id: PACK_CUSTOM, name:"pharaoh_custom_pack", index:60000, system:false, custom:true},  // 60000 -->
  {id: PACK_CUSTOM_FONT, name:"pharaoh_fonts_pack", index:25500, system:false, custom:true},  // 25500 --> 25500
  {id: PACK_CUSTOM_HOUSE, name:"pharaoh_houses_pack", index:60200, system:false, custom:true},  // 60200 -->
]
