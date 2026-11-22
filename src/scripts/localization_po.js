 log_info("akhenaten: localization_po config started")

localization_po = [
 { key:"#TR_NO_PATCH_TITLE", text:""},
 { key:"#TR_NO_PATCH_MESSAGE", text:""},
 { key:"#TR_MISSING_FONTS_TITLE", text:"Brakuje czcionek"},
 { key:"#TR_MISSING_FONTS_MESSAGE", text:"" },
 { key:"#TR_NO_EDITOR_TITLE", text:"Edytor nie jest zainstalowany"},
 { key:"#TR_NO_EDITOR_MESSAGE", text:"" },
 { key:"#TR_INVALID_LANGUAGE_TITLE", text:"Nieprawidłowy folder językowy"},
 { key:"#TR_INVALID_LANGUAGE_MESSAGE", text:""},
 { key:"#dock_order_trade", text:"Handluj"},
 { key:"#dock_order_dont_trade", text:"Nie handluj"},
 { key:"#dock_order_accept_all", text:"Przyjmuj wszystko"},
 { key:"#dock_orders_hint", text:"Statki używają tego doku tylko, gdy przynajmniej jeden ich towar jest ustawiony na Handluj."},
 { key:"#dock_orders_closed", text:"Ten dok nie przyjmuje towarów — statki tu nie cumują."},
 { key:"#TR_BUTTON_OK", text:"OK"},
 { key:"#TR_BUTTON_CANCEL", text:"Anuluj"},
 { key:"#TR_BUTTON_RESET_DEFAULTS", text:"Ustaw domyślne"},
 { key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Skróty klawiszowe"},
 { key:"#TR_CONFIG_TITLE", text:"konfiguracja"},
 { key:"#TR_CONFIG_LANGUAGE_LABEL", text:"Język:"},
 { key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(domyślny)"},
 { key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"Zmiany interfejsu użytkownika"},
 { key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Zmiany gry"},
 { key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"},
 { key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"},
 { key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"},
 { key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Odgrywaj film wprowadzający"},
 { key:"#TR_CONFIG_SIDEBAR_INFO", text:"Dodatkowe informacje w panelu sterowania"},
 { key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"Płynne przewijanie"},
 { key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Pokaż wybrany obszar przy oczyszczaniu terenu"},
 { key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Pozwól na budowę kolejno każdej ze świątyń"},
 { key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Pokaż zasięg przy budowie rezerwuarów, fontann i studni"},
 { key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Pokaż rozmiar budowy przy przeciąganiu kursorem"},
 { key:"#TR_CONFIG_HIGHLIGHT_LEGIONS", text:"Podświetl legion przy najechaniu kursorem"},
 { key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Napraw błąd z imigrację na najwyższym poziomie trudności"},
 { key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Napraw 100-letnie duchy"},
 { key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Napraw zmianę imperatora i czas przetrwania w konstruktorze miast"},
 { key:"#TR_CONFIG_AUTO_RESOLVE_INVASIONS", text:"Auto-rozstrzyganie inwazji: zamrożenie przy wejściu, szybka bitwa w 8 dni"},
 { key:"#TR_CONFIG_HISTORICAL_ECONOMY", text:"Enhanced: historyczna gospodarka — deben jako jednostka rozliczeniowa; część płac ziarnem ze spichlerzy"},
 { key:"#finance_deben_unit_of_account", text:"waga-deben"},
 { key:"#finance_historical_economy_hint", text:"Deben mierzy wartość (waga metalu). Część pracy płaci się ziarnem ze spichlerzy, jeśli jest."},
 { key:"#finance_wages_paid_in_grain", text:"Płace w ziarnie (równ. deben)"},
 { key:"#warning_auto_resolve_orders_blocked", text:"Nie można prowadzić kompanii na zamrożoną falę inwazji"},
 { key:"#warning_auto_resolve_queue_full", text:"Za dużo oczekujących inwazji — ta fala walczy na mapie"},
 { key:"#follow_walker", text:"Śledź piechura"},
 { key:"#stop_following", text:"Stop"},
 { key:"#warning_follow_walker_lost", text:"Utracono śledzonego piechura"},
 { key:"#invasion_quick_battle_title", text:"Szybka bitwa"},
 { key:"#invasion_quick_battle_hint", text:"Najeźdźcy czekają przy wejściu. Rekrutuj w razie potrzeby. Walcz teraz lub poczekaj na timer."},
 { key:"#invasion_quick_battle_resolve", text:"Walcz"},
 { key:"#invasion_quick_battle_wait", text:"Czekaj"},
 { key:"#invasion_quick_battle_strength", text:"Twoje siły: {player}   Wróg: {enemy}"},
 { key:"#invasion_quick_battle_days", text:"Bitwa za {days} dni"},
 { key:"#invasion_quick_battle_queue", text:"({n} w kolejce)"},
 { key:"#invasion_quick_battle_head", text:"Fala #{id} ({i}/{n})"},
 { key:"#invasion_quick_battle_none", text:"Brak oczekującej bitwy"},
 { key:"#TR_HOTKEY_TITLE", text:"Konfiguracja skrótów klawiszowych"},
 { key:"#TR_HOTKEY_LABEL", text:"Skrót klawiszowy"},
 { key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Alternatywny"},
 { key:"#TR_HOTKEY_HEADER_ARROWS", text:"Strzałki kierunkowe"},
 { key:"#TR_HOTKEY_HEADER_GLOBAL", text:"Globalne skróty klawiszowe"},
 { key:"#TR_HOTKEY_HEADER_CITY", text:"Miejskie skróty klawiszowe"},
 { key:"#TR_HOTKEY_HEADER_ADVISORS", text:"Doradcy"},
 { key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"Widoki"},
 { key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"Miejskie miejsca skoku"},
 { key:"#TR_HOTKEY_HEADER_EDITOR", text:"Edytor"},
 { key:"#TR_HOTKEY_ARROW_UP", text:"Góra"},
 { key:"#TR_HOTKEY_ARROW_DOWN", text:"Dół"},
 { key:"#TR_HOTKEY_ARROW_LEFT", text:"Lewo"},
 { key:"#TR_HOTKEY_ARROW_RIGHT", text:"Prawo"},
 { key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Przełącz pełny ekran"},
 { key:"#TR_HOTKEY_CENTER_WINDOW", text:"Wycentruj okno"},
 { key:"#TR_HOTKEY_RESIZE_TO_640", text:"Zmień rozmiar okna do 640x480"},
 { key:"#TR_HOTKEY_RESIZE_TO_800", text:"Zmień rozmiar okna do 800x600"},
 { key:"#TR_HOTKEY_RESIZE_TO_1024", text:"Zmień rozmiar okna do 1024x768"},
 { key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"Zapisz zrzut ekranu"},
 { key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Zapisz zrzut ekranu miasta"},
 { key:"#TR_HOTKEY_LOAD_FILE", text:"Wczytaj plik"},
 { key:"#TR_HOTKEY_SAVE_FILE", text:"Zapisz plik"},
 { key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Zwiększ prędkość gry"},
 { key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Zmniejsz prędkość gry"},
 { key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"Pauza"},
 { key:"#TR_HOTKEY_CYCLE_LEGION", text:"Przełącz między legionami"},
 { key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Obróć mapę w lewo"},
 { key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Obróć mapę w prawo"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Doradca zatrudnienia"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Doradca legionów"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Doradca imperialny"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Doradca wyników"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Doradca handlowy"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"Doradca populacji"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Doradca zdrowia"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Doradca edukacji"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Doradca rozrywki"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Doradca religijny"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Doradca finansowy"},
 { key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Główny doradca"},
 { key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"Przełącz między widokami"},
 {key:"#TR_HOTKEY_TOGGLE_FLAT_BUILDINGS", text:"Płaski widok budynków"},
 { key: "#sidebar_flat_buildings", text: "Płaski widok" },
 { key: "#sidebar_flat_buildings_on", text: "Płaski widok: WŁ" },
 { key: "#TR_CONFIG_FLAT_BUILDINGS", text: "Płaski widok budynków (Shift+F) — spłaszcz wysokie budynki, by widzieć drogi za nimi" },
 { key: "#TR_TOOLTIP_FLAT_BUILDINGS", text: "Płaski widok budynków (Shift+F). Gdy WŁ: Ctrl+PPM podnosi jeden budynek." },
 { key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Pokaż widok wody"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Pokaż widok pożarów"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Pokaż widok zniszczenia"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Pokaż widok zbrodni"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Pokaż widok problemów"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_MALARIA_RISK", text:"Widok ryzyka malarii"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_DISEASE", text:"Widok choroby"},
 { key:"#TR_HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS", text:"Ukryj klify"},
 { key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Przejdź do punktu skoku 1"},
 { key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Przejdź do punktu skoku 2"},
 { key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Przejdź do punktu skoku 3"},
 { key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Przejdź do punktu skoku 4"},
 { key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"Ustaw punkt skoku 1"},
 { key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"Ustaw punkt skoku 2"},
 { key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"Ustaw punkt skoku 3"},
 { key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"Ustaw punkt skoku 4"},
 { key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Przełącz informacje o bitwach"},
 { key:"#TR_HOTKEY_EDIT_TITLE", text:"Wprowadź skrót"},
 { key:"#TR_BUILDING_ROADBLOCK", text:"Blokada drogi"},
 { key:"#TR_BUILDING_ROADBLOCK_DESC", text:"Blokada drogi zatrzymuje przechodniów bez celu."},
 { key:"#TR_HEADER_HOUSING", text:"Domy"},
 { key:"#TR_ADVISOR_HOUSING_ROOM", text:"W miejskich domach jest miejsce dla"},
 { key:"#TR_ADVISOR_HOUSING_NO_ROOM", text:"Brak miejsca w miejskich domach."},
 { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY", text:"Domy wymagające garnków"},
 { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE", text:"Domy wymagające mebli"},
 { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_OIL", text:"Domy wymagające oliwy"},
 { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_WINE", text:"Domy wymagające wina"},
 { key:"#TR_ADVISOR_TOTAL_NUM_HOUSES", text:"Razem domów:"},
 { key:"#TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY", text:"Dostępne zakwaterowanie:"},
 { key:"#TR_ADVISOR_TOTAL_HOUSING_CAPACITY", text:"Całkowite zakwaterowanie:"},
 { key:"#TR_ADVISOR_ADVISOR_HEADER_HOUSING", text:"Populacja - domy"},
 { key:"#TR_ADVISOR_BUTTON_GRAPHS", text:"Wykresy"},
 { key:"#TR_ADVISOR_HOUSING_PROSPERITY_RATING", text:"Bogactwo domów"},
 { key:"#TR_ADVISOR_PERCENTAGE_IN_MANORS", text:"Procent populacji w willach i pałacach"},
 { key:"#TR_ADVISOR_PERCENTAGE_IN_SHANTIES", text:"Procent populacji w namiotach i szałasach"},
 { key:"#TR_ADVISOR_AVERAGE_TAX", text:"Średni podatek na głowę"},
 { key:"#tax_rate_of", text:"Stawka podatkowa"},
 { key:"#palace_vaults_hold", text:"Skarbce zawierają"},
 { key:"#debens", text:"Debenów"},
 { key:"#building_no_road_access", text:"OSTRZEŻENIE: Ten budynek nie przylega do drogi"},
 { key:"#building_no_people_in_city", text:"Brak ludzi w mieście!"},
 { key:"#building_no_workers_nearby", text:"W pobliżu nie mieszkają robotnicy"},
 { key:"#building_labor_could_shift", text:"Nadzorca robotników mógłby przesunąć trochę siły roboczej"},
 { key:"#building_poor_worker_access", text:"OSTRZEŻENIE: Słaby dostęp do robotników"},
 { key:"#TR_ADVISOR_AVERAGE_AGE", text:"Średnia wieku populacji"},
 { key:"#TR_ADVISOR_PERCENT_IN_WORKFORCE", text:"Procent populacji w sile roboczej"},
 { key:"#TR_ADVISOR_BIRTHS_LAST_YEAR", text:"Narodzin w zeszłym roku:"},
 { key:"#TR_ADVISOR_DEATHS_LAST_YEAR", text:"Śmierci w zeszłym roku:"},
 { key:"#TR_ADVISOR_TOTAL_POPULATION", text:"Razem mieszkańców"}
 { key:"#mansion_protected_by_police", text:"Chronione przez policję"}
 { key:"#mansion_not_protected_theft", text:"Bez ochrony — złodzieje mogą ukraść oszczędności"}

 { key: "#overlay_menu_normal", text: "Normalny" }
 { key: "#overlay_menu_risks", text: "Zagrożenia" }
 { key: "#overlay_menu_water", text: "Woda" }
 { key: "#overlay_menu_entertainment", text: "Rozrywka" }
 { key: "#overlay_menu_religion", text: "Religia" }
 { key: "#overlay_menu_education", text: "Edukacja" }
 { key: "#overlay_menu_health", text: "Zdrowie" }
 { key: "#overlay_menu_administration", text: "Administracja" }
 { key: "#overlay_menu_food", text: "Żywność" }
 { key: "#overlay_menu_other", text: "Inne" }

 { key: "#overlay_fire", text: "Pożar" }
 { key: "#overlay_damage", text: "Szkody" }
 { key: "#overlay_architect_reach", text: "Zasięg architekta" }
 { key: "#overlay_architect_reach_hint", text: "Kliknij posterunek architekta" }
 { key: "#overlay_architect_reach_tile", text: "W zasięgu patrolu" }
 { key: "#overlay_crime", text: "Przestępczość" }
 { key: "#overlay_entertainment", text: "Rozrywka" }
 { key: "#overlay_booth", text: "Żongler" }
 { key: "#overlay_bandstand", text: "Muzyk" }
 { key: "#overlay_pavilion", text: "Tancerz" }
 { key: "#overlay_senet_house", text: "Gracze w senet" }
 { key: "#overlay_education", text: "Edukacja" }
 { key: "#overlay_scribal_school", text: "Szkoły pisarzy" }
 { key: "#overlay_library", text: "Biblioteka" }
 { key: "#overlay_academy", text: "Akademia" }
 { key: "#overlay_apothecary", text: "Aptekarz" }
 { key: "#overlay_dentist", text: "Dentysta" }
 { key: "#overlay_physician", text: "Lekarz" }
 { key: "#overlay_mortuary", text: "Kostnica" }
 { key: "#overlay_tax_income", text: "Dochód podatkowy" }
 { key: "#overlay_bazaar_access", text: "Dostęp do bazaru" }
 { key: "#overlay_desirability", text: "Atrakcyjność" }
 { key: "#overlay_fertility", text: "Żyzność" }
 { key: "#overlay_magistrate", text: "Sędzia" }
 { key: "#overlay_food_stocks", text: "Zapasy żywności" }
 { key: "#overlay_labor", text: "Praca" }
 { key: "#overlay_labor_access", text: "Dostęp do pracy" }
 { key: "#overlay_native", text: "Rodzimy" }
 { key: "#overlay_problems", text: "Problemy" }
 { key: "#overlay_routing", text: "Trasy" }
 { key: "#overlay_malaria_risk", text: "Ryzyko malarii" }
 { key: "#overlay_health", text: "Zdrowie" }
 { key: "#overlay_criminal", text: "Przestępca" }
 { key: "#overlay_osiris", text: "Ozyrys" }
 { key: "#overlay_ra", text: "Ra" }
 { key: "#overlay_ptah", text: "Ptah" }
 { key: "#overlay_seth", text: "Set" }
 { key: "#overlay_bast", text: "Bastet" }
 { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "Bezrobocie" }
 { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "Ocena kultury" }
 { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "Ocena dobrobytu" }
 { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "Ocena monumentów" }
 { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "Ocena królestwa" }
 { key: "#figure_antelope_hunter", text: "Myśliwy na antylopy" }
 { key: "#figure_antelope_hunter_javelin", text: "Oszczep myśliwego" }
 { key: "#figure_birds_hunter", text: "Myśliwy na ptaki" }
 { key: "#antelope_hunter_hunting", text: "Antylopy nam nie dorównają!" }
 { key: "#antelope_hunter_back", text: "Dziś wieczorem będą steki dla wszystkich." }
 { key: "#antelope_hunter_city_is_good", text: "To dobre miasto!" }
 { key: "#hunter_ostrich_investigate", text: "Ślady na piasku... niedawno był tu struś." }
 { key: "#hunter_ostrich_chase", text: "Tam ucieka! Nogi ma szybkie, ale moje strzały szybsze." }
 { key: "#hunter_ostrich_hunting", text: "Strusie prawie znikają, gdy chowają głowę w piasek." }
 { key: "#hunter_ostrich_back", text: "No, to dopiero WIELKIE udka!" }
 { key: "#hunter_ostrich_reroute_packed", text: "Ciężki ładunek, zła droga. Znajdę inną drogę powrotną." }
 { key: "#hunter_ostrich_look_packed", text: "Potrzebuję wolnej ścieżki do chaty z tym ptakiem na plecach." }
 { key: "#hunter_ostrich_unloading", text: "Świeża zwierzyna do chaty. Już pachnie lepiej niż jęczmień." }
 { key: "#hunter_ostrich_disease_risk", text: "Tu pachnie chorobą. Zła pogoda na polowanie." }
 { key: "#hunter_ostrich_no_food_in_city", text: "Puste spichlerze? To lepiej przyniosę dużego ptaka." }
 { key: "#hunter_ostrich_city_have_no_army", text: "Brak fortów? Jeden rajd krokodyli i to miasto będzie kolacją." }
 { key: "#hunter_ostrich_need_workers", text: "Trzeba więcej rąk. Sam nie napełnię wszystkich garnków." }
 { key: "#hunter_ostrich_gods_are_angry", text: "Bogowie wyglądają na gniewnych. Nawet strusie to czują." }
 { key: "#hunter_ostrich_city_is_bad", text: "Faraon nie jest z nas zadowolony. To nigdy nie kończy się dobrze." }
 { key: "#hunter_ostrich_much_unemployment", text: "Za dużo bezrobotnych. Przynajmniej polowanie kogoś jeszcze karmi." }
 { key: "#hunter_ostrich_low_entertainment", text: "Od dawna bez świąt. Uczta ze strusia wszystkich by rozweseliła." }
 { key: "#hunter_ostrich_city_is_good", text: "To miasto jest fantastyczne!" }
 { key: "#hunter_ostrich_city_is_amazing", text: "Najlepsze miasto, dla którego polowałem. Oby tak zostało!" }
 { key: "#hunt_bird_birds_are_wily", text: "Te ptaki są przebiegłe!" }
 { key: "#hunt_bird_birds_ready_for_roasting", text: "Te ptaki są gotowe do pieczenia!" }
]