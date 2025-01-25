log_info("akhenaten: imagepaks started")

imagepaks = [
  {id: PACK_UNLOADED, name:"Pharaoh_Unloaded", index:0, size:682 , system:true},  // 0     --> 682
  {id: PACK_SPR_MAIN, name:"SprMain", index:700, system:false}, // 700   --> 11007
  {id: PACK_GENERAL, name:"Pharaoh_General", index:11706, system:false}, // 11706 --> 11866
  {id: PACK_TERRAIN, name:"Pharaoh_Terrain", index:14252, system:false}, // 14252 --> 15767 (+64)
  {id: PACK_SPR_AMBIENT, name:"SprAmbient", index:15831, system:false}, // 15831 --> 18765
  {id: PACK_MASTABA, name:"mastaba", index:25000, system:false}, // 25000 --> 25000 + 228 + 201
  {id: PACK_TEMPLE_RA, name:"Temple_ra", index:32000, system:false}, // 32000 --> 32000 + 201 + 38
  {id: PACK_TEMPLE_NILE, name:"Temple_nile", index:32250, system:false}, // 32250 --> 32250 + 201 + 38
  {id: PACK_TEMPLE_PTAH, name:"Temple_ptah", index:32500, system:false}, // 32500 --> 32500 + 201 + 38
  {id: PACK_TEMPLE_SETH, name:"Temple_seth", index:32750, system:false}, // 32750 --> 32750 + 201 + 38
  {id: PACK_TEMPLE_BAST, name:"Temple_bast", index:33000, system:false}, // 33000 --> 33000 + 201 + 38
  {id: PACK_EXPANSION, name:"Expansion", index:23035, system:false}, // 23035 --> 23935
  {id: PACK_EMPIRE, name:"Empire", index:20305, system:false}, // 20305 --> 20506 (+177)
  {id: PACK_EXPANSION_SPR, name:"SprMain2", index:20683, system:false}, // 20683 --> 23035
  {id: PACK_LIB_EXTRA, name:"LibExtra", index:24000, size:27, system:false}, // 24000 --> 24000 + 201 + 27
  {id: PACK_LIB_EXTRA_2, name:"LibExtra2", index:24230, size:27, system:false}, // 24230 --> 24230 + 201 + 27
  {id: PACK_LIB_MAUS_CARRYOVER, name:"MausCarryover", index:24460, size:9, system:false}, // 24460 --> 24460 + 201 + 9
  {id: PACK_LIB_MAUSOLEUM_0, name:"mausoleum0_extra", index:24690, size:16, system:false}, // 24690 --> 24690 + 201 + 16  
  {id: PACK_LIB_MAUSOLEUM_1, name:"mausoleum1_extra", index:24910, size:16, system:false}, // 24910 --> 24910 + 201 + 16
  {id: PACK_LIB_MAUSOLEUM_2, name:"mausoleum2_extra", index:25130, size:16, system:false}, // 25130 --> 25130 + 201 + 16
  {id: PACK_PYRAMID, name:"Pyramid", index:34000, size:228, system:false}, // 34000 --> 34000 + 201 + 228
  {id: PACK_BENT_PYRAMID, name:"bent_pyramid", index:34450, size:228, system:false}, // 34250 --> 34250 + 201 + 228
  {id: PACK_MUDBRICK_PYRAMID, name:"mudbrick_pyramid", index:34900, size:228, system:false}, // 34900 --> 34900 + 201 + 228
  {id: PACK_STEPPED_PYRAMID, name:"stepped_pyramid", index:35350, system:false}, // 35350 --> 35350 + 201 + 228
  {id: PACK_ABUSIMBEL, name:"AbuSimbel", index:35850, size:70, system:false}, // 35850 --> 35850 + 201 + 70
  {id: PACK_CAESAREUM_1, name:"caesareum1", index:36150, size:9, system:false}, // 36150 --> 36150 + 201 + 9
  {id: PACK_CAESAREUM_2, name:"caesareum2", index:36360, size:9, system:false}, // 36360 --> 36360 + 201 + 9
  {id: PACK_CAESAREUM_3, name:"caesareum3", index:36570, size:9, system:false}, // 36570 --> 36570 + 201 + 9
  {id: PACK_CAESAREUM_4, name:"caesareum4", index:36780, size:9, system:false}, // 36780 --> 36780 + 201 + 9
  {id: PACK_OBELISK_EXTRA, name:"obelisk_extra", index:51000, size:16, system:false}, // 51000 --> 51000 + 201 + 16
  {id: PACK_OBELISK_X3_A, name:"obelisk3x3a", index:51220, size:1, system:false}, // 51220 --> 51220 + 201 + 1
  {id: PACK_OBELISK_X3_B, name:"obelisk3x3b", index:51430, size:1, system:false}, // 51430 --> 51430 + 201 + 1
  {id: PACK_OBELISK_X3_C, name:"obelisk3x3c", index:51640, size:1, system:false}, // 51640 --> 51640 + 201 + 1
  {id: PACK_OBELISK_X5_A, name:"obelisk5x5a", index:51850, size:1, system:false}, // 51850 --> 51850 + 201 + 1
  {id: PACK_OBELISK_X5_B, name:"obelisk5x5b", index:52000, size:1, system:false}, // 52000 --> 52000 + 201 + 1
  {id: PACK_OBELISK_X5_C, name:"obelisk5x5c", index:52220, size:1, system:false}, // 52220 --> 52000 + 201 + 1
  {id: PACK_OBELISK_X5_D, name:"obelisk5x5d", index:52430, size:1, system:false}, // 52430 --> 36067 + 201 + 1
  {id: PACK_OBELISK_X5_E, name:"obelisk5x5e", index:52640, size:1, system:false}, // 52430 --> 36068 + 201 + 1
  {id: PACK_OBELISK_X5_F, name:"obelisk5x5f", index:51850, size:1, system:false}, // 52430 --> 36069 + 201 + 1
  {id: PACK_SPHINX_1_A, name:"sphinx1a", index:53000, size:2, system:false}, // 53000 --> 53000 + 201 + 2
  {id: PACK_SPHINX_1_B, name:"sphinx1b", index:53430, size:2, system:false}, // 53430 --> 53430 + 201 + 2
  {id: PACK_SPHINX_1_C, name:"sphinx1c", index:53640, size:2, system:false}, // 53640 --> 53640 + 201 + 2
  {id: PACK_SPHINX_1_D, name:"sphinx1d", index:53850, size:2, system:false}, // 53850 --> 53850 + 201 + 2
  {id: PACK_SPHINX_2_A, name:"sphinx2a", index:54000, size:2, system:false}, // 54000 --> 54000 + 201 + 2
  {id: PACK_SPHINX_2_B, name:"sphinx2b", index:54220, size:2, system:false}, // 54220 --> 54220 + 201 + 2
  {id: PACK_SPHINX_2_C, name:"sphinx2c", index:54430, size:2, system:false}, // 36082 --> 36084 + 201 + 2
  {id: PACK_SUN_TEMPLE_EXTRA, name:"sun_temple_extra", index:55000, size:15, system:false}, // 55000 --> 55000 + 201 + 15
  {id: PACK_SUN_TEMPLE_1, name:"suntemple1", index:55220, size:2, system:false}, // 55220 --> 55220 + 201 + 2
  {id: PACK_SUN_TEMPLE_2, name:"suntemple2", index:55440, size:2, system:false}, // 55440 --> 55440 + 201 + 2
  {id: PACK_SUN_TEMPLE_3, name:"suntemple3", index:55660, size:2, system:false}, // 55660 --> 55660 + 201 + 2
  {id: PACK_TOMB_SETI, name:"TombSeti", index:56000, size:221, system:false}, // 56000 --> 56000 + 201 + 221
  {id: PACK_TOMB_SETI_FINAL, name:"TombSetiFin", index:56500, size:221, system:false}, // 56500 --> 56500 + 201 + 221
  {id: PACK_TOMB_THUTMOS, name:"TombThut", index:57000, size:157, system:false}, // 57000 --> 57000 + 201 + 157
  {id: PACK_TOMB_THUTMOS_FINAL, name:"TombThutFin", index:57400, size:157, system:false}, // 57400 --> 57400 + 201 + 157
  {id: PACK_TOMB_TUTANKHAMUN, name:"TombTut", index:57800, size:181, system:false}, // 57800 --> 57800 + 201 + 181
  {id: PACK_TOMB_TUTANKHAMUN_FINAL, name:"TombTutFin", index:58200, size:181, system:false}, // 58200 --> 58200 + 201 + 181
  {id: PACK_ENEMY_ASSYRIAN, name:"Assyrian", index:37000, size:898, system:false}, // 37000 --> 37000 + 898 + 201
  {id: PACK_ENEMY_CANAANITE, name:"Canaanite", index:38100, size:858, system:false}, // 38100 --> 38100 + 858 + 201
  {id: PACK_ENEMY_EGYPTIAN, name:"Egyptian", index:39200, size:778, system:false}, // 39200 --> 39200 + 778 + 201
  {id: PACK_ENEMY_BARBARIAN, name:"Enemy_1", index:40000, size:728, system:false}, // 40000 --> 40000 + 728 + 201
  {id: PACK_ENEMY_HITTITE, name:"Hittite", index:41000, size:866, system:false}, // 41000 --> 41000 + 866 + 201
  {id: PACK_ENEMY_HYKSOS, name:"Hyksos", index:42100, size:898, system:false}, // 42100 --> 42100 + 898 + 201
  {id: PACK_ENEMY_KUSHITE, name:"Kushite", index:43200, size:857, system:false}, // 43200 --> 43200 + 857 + 201
  {id: PACK_ENEMY_LIBIAN, name:"Libian", index:44300, size:858, system:false}, // 44300 --> 44300 + 858 + 201
  {id: PACK_ENEMY_NUBIAN, name:"Nubian", index:45400, size:825, system:false}, // 45400 --> 45400 + 825 + 201
  {id: PACK_ENEMY_PERSIAN, name:"Persian", index:46500, size:866, system:false}, // 46500 --> 46500 + 866 + 201
  {id: PACK_ENEMY_PHOENICIAN, name:"Phoenician", index:47600, size:834, system:false}, // 47600 --> 47600 + 834 + 201
  {id: PACK_ENEMY_ROMAN, name:"Roman", index:48700, size:874, system:false}, // 48700 --> 48700 + 874 + 201
  {id: PACK_ENEMY_SEAPEOPLE, name:"SeaPeople", index:49800, system:false}, // 49000 --> 49850 + 833 + 201
  {id: PACK_TOMB_RAMSES, name:"TombRam", index:59000, size:269, system:false}, // 59000 --> 50000 + 269 + 201 
  {id: PACK_TOMB_RAMSES_FINAL, name:"TombRamFin", index:59500, size:269, system:false}, // 59500 --> 50500 + 269 + 201 
  //{id: PACK_CUSTOM, name:"Pharaoh_Custom", index:30000, system:false, custom:true},  // 30000 -->
]
