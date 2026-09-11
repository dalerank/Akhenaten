log_info("akhenaten: localization_it config started")

localization_it = [
  {key:"#TR_NO_PATCH_TITLE", text:"Patch non installata"}
  {key:"#TR_NO_PATCH_MESSAGE", text:"La tua installazione di Faraon non ha la patch installata. "}
  {key:"#TR_MISSING_FONTS_TITLE", text:"Font mancanti"}
  {key:"#TR_MISSING_FONTS_MESSAGE", text:"L'installazione di Faraon richiede file di font aggiuntivi. "}
  {key:"#TR_NO_EDITOR_TITLE", text:"Editor non installato"}
  {key:"#TR_NO_EDITOR_MESSAGE", text:"La tua installazione di Faraon non contiene i file dell'editor. "}
  {key:"#editor_generate_map", text:"Genera mappa"}
  {key:"#TR_INVALID_LANGUAGE_TITLE", text:"Cartella della lingua non valida"}
  {key:"#TR_INVALID_LANGUAGE_MESSAGE", text:"La cartella selezionata non contiene un pacchetto di lingua corretto. Per favore controlla il log degli errori."}
  {key:"#TR_BUTTON_OK", text:"OK"}
  {key:"#TR_CONFIG_IRONWILL", text:"Modalità Ironwill — salva solo uscendo al menu principale (blocca Salva, Ctrl+S, salvataggio automatico, quicksave/quickload)"}
  {key:"#TR_CONFIG_UNLOCK_ALL_CAMPAIGNS", text:"Sblocca tutti i periodi della campagna nella Storia della famiglia"}
  {key:"#ironwill_briefing_label", text:"Ironwill"}
  {key:"#ironwill_save_blocked", text:"Ironwill: salvataggio solo uscendo al menu"}
  {key:"#ironwill_load_blocked", text:"Ironwill: carica solo dal menu principale (Continua)"}
  {key:"#ironwill_save_failed", text:"Salvataggio Ironwill non riuscito — ancora in città"}
  {key:"#TR_BUTTON_CANCEL", text:"Cancella"}
  {key:"#TR_BUTTON_PAUSE", text:"Pausa"}
  {key:"#TR_BUTTON_RESUME", text:"Riprendi"}
  {key:"#TR_GAME_PAUSED", text:"Gioco in pausa (premi '{0}' per continuare)"}
  {key:"#TR_BUTTON_RESET_DEFAULTS", text:"Ripristina il default"}
  {key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Configura tasti rapidi"}
  {key:"#TR_BUTTON_NEXT", text:"+"}
  {key:"#TR_BUTTON_PREV", text:"-"}
  {key:"#TR_CONFIG_TITLE", text:"Opzioni di configurazione"}
  {key:"#TR_CONFIG_LANGUAGE_LABEL", text:"Lingua:"}
  {key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(default)"}
  {key:"#TR_CONFIG_PAGE_LABEL", text:"Pagina"}
  {key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"Modifiche all'interfaccia utente"}
  {key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Modifiche al gioco"}
  {key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"}
  {key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"}
  {key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"}
  {key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Riproduce il video introduttivo"}
  {key:"#TR_CONFIG_HIDE_NEW_GAME_TOP_MENU", text:"Nascondi il pulsante Nuova partita nel menu in alto"}
  {key:"#TR_CONFIG_SAVE_YEAR_KINGDOME_RATING", text:"Salva il Livello del Regno all'aggiornamento annuale"}
  {key:"#TR_CONFIG_SIDEBAR_INFO", text:"Informazioni extra nel pannello di controllo"}
  {key:"#TR_CONFIG_BUILDING_MOTHBALL_BUTTON", text:"Mostra il pulsante di sospensione nelle finestre degli edifici"}
  {key:"#TR_CONFIG_PROMPT_SAVE_ON_EXIT", text:"Chiedi se salvare all'uscita dal gioco (Alt+F4)"}
  {key:"#dock_order_trade", text:"Commercia"}
  {key:"#dock_order_dont_trade", text:"Non commerciare"}
  {key:"#dock_order_accept_all", text:"Accetta tutto"}
  {key:"#dock_orders_hint", text:"Le navi usano questo molo solo se almeno una delle loro merci è impostata su Commercia."}
  {key:"#dock_orders_closed", text:"Questo molo non accetta merci — le navi non ormeggeranno qui."}
  {key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"Abilita lo scorrimento continuo"}
  {key:"#TR_CONFIG_SMOOTH_ZOOM", text:"Abilita zoom fluido"}
  {key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Migliora l'aspetto liberando il terreno"}
  {key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Consente la costruzione di tutti i templi in successione"}
  {key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Mostra la copertura di cisterne, fontane e pozzi"}
  {key:"#TR_CONFIG_SHOW_BUILDING_ROAD_ACCESS", text:"Mostra la casella di accesso stradale in posa o al passaggio del mouse (classico: una casella)"}
  {key:"#TR_CONFIG_SHOW_DELIVERY_PATHS", text:"Mostra i percorsi di consegna recenti tenendo premuto Alt su un granaio o un casotto da caccia"}
  {key:"#delivery_path_no_road", text:"Nessun accesso stradale — consegna impossibile"}
  {key:"#delivery_path_understaffed", text:"Nessun deposito accetta merci — personale insufficiente"}
  {key:"#delivery_path_no_destination", text:"Nessuna destinazione accetta questa merce"}
  {key:"#delivery_path_no_route", text:"Destinazione trovata, ma nessuna strada"}
  {key:"#TR_CONFIG_FLAT_BUILDINGS", text:"Vista piatta edifici (Shift+F) — appiattisci edifici alti per vedere le strade dietro"}
  {key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Mostra le dimensioni della costruzione durante il trascinamento"}
  {key:"#TR_CONFIG_PAUSE_SIM_WHILE_BUILDING", text:"Pausa della simulazione mentre posizioni gli edifici"}
  {key:"#TR_CONFIG_HIGHLIGHT_LEGIONS", text:"Evidenzia la legione al passaggio del cursore"}
  {key:"#TR_CONFIG_ROTATE_MANUALLY", text:"Ruota Corpo di Guardia e Arco di Trionfo con un tasto rapido"}
  {key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Corregge il bug dell'immigrazione al livello molto difficile"}
  {key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Corregge il bug dei centenari"}
  {key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Elimina le complicazioni al cambio di Imperatore"}
  {key:"#TR_CONFIG_DRAW_WALKER_WAYPOINTS", text:"Disegna i punti di passaggio dei passanti sulla mappa tematica dopo il clic destro su un edificio"}
  {key:"#TR_CONFIG_ZOOM_STEPPED", text:"Attiva lo zoom (può rallentare, usa più RAM)"}
  {key:"#TR_CONFIG_COMPLETE_RATING_COLUMNS", text:"Correggi le colonne delle valutazioni incomplete con obiettivi bassi"}
  {key:"#TR_CONFIG_GRANDFESTIVAL", text:"Le festività maggiori concedono una benedizione extra da un dio"}
  {key:"#TR_CONFIG_JEALOUS_GODS", text:"Disattiva la gelosia degli dèi"}
  {key:"#TR_CONFIG_GLOBAL_LABOUR", text:"Attiva bacino di manodopera globale"}
  {key:"#TR_CONFIG_SCHOOL_WALKERS", text:"Estendi il raggio d'azione degli scolari"}
  {key:"#TR_CONFIG_RETIRE_AT_60", text:"Porta l'età della pensione dei cittadini da 50 a 60"}
  {key:"#TR_CONFIG_FIXED_WORKERS", text:"Manodopera fissa — 38% dei popolani"}
  {key:"#workers_staffing_tooltip", text:"%d / %d impiegati"}
  {key:"#TR_CONFIG_EXTRA_FORTS", text:"Consenti la costruzione di 4 forti aggiuntivi"}
  {key:"#TR_CONFIG_WOLVES_BLOCK", text:"Impedisci di costruire vicino ai lupi"}
  {key:"#TR_CONFIG_DYNAMIC_GRANARIES", text:"Blocca le strade dei granai non collegate"}
  {key:"#TR_CONFIG_MORE_STOCKPILE", text:"Le case accumulano più merci dal bazar"}
  {key:"#TR_CONFIG_NO_BUYER_DISTRIBUTION", text:"Le venditrici del bazar che acquistano non distribuiscono merci"}
  {key:"#TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS", text:"Demolisci subito gli edifici"}
  {key:"#TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD", text:"I carrettieri dei granai in raccolta possono uscire dalle strade"}
  {key:"#TR_CONFIG_GRANARIES_GET_DOUBLE", text:"Raddoppia la capacità dei carrettieri dei granai in prelievo"}
  {key:"#TR_CONFIG_DOCK_DOUBLE_HAUL", text:"Raddoppia la quantità trasportata dai portuali (200 per viaggio)"}
  {key:"#TR_CONFIG_BAZAAR_MULTI_BUYERS", text:"I bazar possono inviare due acquirenti insieme (cibo + merci)"}
  {key:"#TR_CONFIG_TRADER_CAPACITY_1600", text:"Capacità dei mercanti maggiore (1600 per visita; non il limite annuale dell'impero)"}
  {key:"#TR_CONFIG_TRADER_PER_GOOD_1600", text:"Nuova era: i mercanti comprano/vendono fino a 1600 unità per merce a visita (non è un limite annuale né solo sul carico totale)"}
  {key:"#trader_capacity_per_good", text:"Capacità (per merce)"}
  {key:"#TR_CONFIG_BAST_LION_RAID", text:"Maledizione maggiore di Bast: incursione di leoni da templi/zoo (TEMP Enhanced)"}
  {key:"#TR_CONFIG_SETH_ASP_RAID", text:"Maledizione maggiore di Seth: incursione di aspidi dai templi quando non c'è una compagnia da maledire (TEMP Enhanced)"}
  {key:"#TR_CONFIG_PTAH_SCORPION_RAID", text:"Maledizione maggiore di Ptah: incursione di scorpioni dai templi quando non c'è industria da distruggere (TEMP Enhanced)"}
  {key:"#TR_CONFIG_AUTO_RESOLVE_INVASIONS", text:"Risoluzione auto invasioni: gelo all'ingresso, battaglia rapida in 8 giorni"}
  {key:"#TR_CONFIG_INVASION_BRIBE", text:"Corrompi gli invasori: paga in Db per far ritirare un'invasione straniera o del Faraone (non l'esercito del regno né le rivolte)"}
  {key:"#invasion_bribe_button", text:"Corrompi"}
  {key:"#invasion_bribe_cost_line", text:"Tangente: {cost} Db   Tesoro: {treasury}"}
  {key:"#TR_CONFIG_FLOOD_BASINS", text:"Migliorato: dighe sul campo di limo / irrigazione a bacino (chiudi le fattorie per raccolti migliori dopo l'inondazione)"}
  {key:"#TR_CONFIG_FOOD_MILL", text:"Avanzato: varietà di cibo al bazar + edificio Mulino alimentare (grafica provvisoria)"}
  {key:"#TR_CONFIG_INDUSTRY_OFFICE", text:"Enhanced: Ufficio dell'Industria — sospende le officine nel raggio (papiro + scribi)"}
  {key:"#TR_CONFIG_LABOR_CATEGORY_SPLIT", text:"Enhanced: separa depositi merci/moli dall'Industria nel supervisore del lavoro"}
  {key:"#TR_CONFIG_WALKER_SPAWN_BOOST", text:"Enhanced: ricomparsa più rapida degli addetti ai servizi (carenza di personale meno penalizzante)"}
  {key:"#TR_CONFIG_WALKER_MOVE_BOOST", text:"Migliorato: cittadini più veloci / attesa dei carri più breve"}
  {key:"#TR_CONFIG_FESTIVAL_CALENDAR", text:"Migliorato: riti del calendario stagionale (temi di festività extra)"}
  {key:"#TR_CONFIG_LOCAL_CULTS", text:"Migliorato: culti locali tramite altare/oracolo del complesso templi"}
  {key:"#local_cult_anubis", text:"Anubis"}
  {key:"#local_cult_thoth", text:"Thoth"}
  {key:"#local_cult_hathor", text:"Hathor"}
  {key:"#local_cult_inactive", text:"Costruisci l'altare o l'oracolo corrispondente nel complesso ospitante"}
  {key:"#local_cults_header", text:"Culti locali"}
  {key:"#festival_calendar_upcoming", text:"Prossimo rito"}
  {key:"#labor_category_storage", text:"Deposito e distribuzione"}
  {key:"#labor_category_industry", text:"Industria"}
  {key:"#labor_category_industry_commerce", text:"Industria e commercio"}
  {key:"#labor_category_culture", text:"Cultura"}
  {key:"#TR_CONFIG_HISTORICAL_ECONOMY", text:"Enhanced: economia storica — deben come unità di conto; parte dei salari in grano dai granai"}
  {key:"#finance_deben_unit_of_account", text:"peso-deben"}
  {key:"#finance_historical_economy_hint", text:"I deben misurano il valore (peso del metallo). Parte del lavoro è pagata in grano dai granai se disponibile."}
  {key:"#finance_wages_paid_in_grain", text:"Salari in grano (eq. deben)"}
  {key:"#building_food_mill", text:"Mulino alimentare (temp)"}
  {key:"#building_food_mill_info", text:"Smistamento del cibo per i bazar. Le fattorie riempiono i granai; imposta il mulino su PRELEVA cibo dai granai o dai depositi. I bazar preferiscono un mulino con personale e possono prendere più tipi di cibo in una sola visita. La grafica è provvisoria (cubi verdi)."}
  {key:"#building_industry_office", text:"Ufficio dell'industria (temp)"}
  {key:"#building_industry_office_info", text:"Gli scribi gestiscono le industrie vicine finché hanno papiro. I cubi verdi segnano l'ingombro in attesa della grafica."}
  {key:"#industry_office_managing", text:"Officine gestite:"}
  {key:"#industry_office_needs_papyrus", text:"Serve papiro"}
  {key:"#industry_office_needs_workers", text:"Servono scribi (lavoratori)"}
  {key:"#industry_office_inactive", text:"Ufficio inattivo"}
  {key:"#industry_office_working", text:"Emette ordini di produzione"}
  {key:"#industry_office_mothball_all", text:"Sospendi tutto"}
  {key:"#industry_office_unmothball_all", text:"Riattiva tutto"}
  {key:"#food_mill_no_road_access", text:"Questo mulino non ha accesso stradale. I lavoratori non possono portarvi il cibo."}
  {key:"#food_mill_storing", text:"In deposito"}
  {key:"#food_mill_space_for", text:"Spazio per"}
  {key:"#food_mill_units", text:"unità"}
  {key:"#food_mill_quality_now", text:"Qualità del cibo ora:"}
  {key:"#food_mill_variety_none", text:"nessuna (vuoto)"}
  {key:"#food_mill_variety_bland", text:"Insipida"}
  {key:"#food_mill_variety_plain", text:"Semplice"}
  {key:"#food_mill_variety_appetizing", text:"Appetitoso"}
  {key:"#food_mill_variety_tasty", text:"Gustoso"}
  {key:"#bazaar_desired_variety", text:"Tipi di cibo desiderati:"}
  {key:"#bazaar_min_variety", text:"Varietà minima del mulino:"}
  {key:"#bazaar_waiting_mill_variety", text:"In attesa della varietà di cibo dal mulino."}
  {key:"#building_dike", text:"Argine"}
  {key:"#building_dike_info", text:"Argine di terra per l'irrigazione a bacino del campo di limo. Chiudi un perimetro attorno alle fattorie per migliorare i raccolti dopo l'inondazione."}
  {key:"#terrain_dike_sealed", text:"Bacino chiuso"}
  {key:"#terrain_dike_breached", text:"Nessun bacino chiuso adiacente — traccia un perimetro chiuso attorno alle fattorie sul campo di limo per trattenere il dono della piena."}
  {key:"#terrain_dike_tiles", text:"caselle"}
  {key:"#terrain_dike_farms", text:"fattorie"}
  {key:"#terrain_dike_bonus_hint", text:"Fertilità e crescita delle colture migliorano finché è chiusa."}
  {key:"#farm_in_flood_basin", text:"Nel bacino d'inondazione: raccolti migliori dopo la piena, finché l'argine resta sigillato."}
  {key:"#overlay_flood_basin", text:"Bacini d'inondazione"}
  {key:"#overlay_flood_basin_off", text:"I bacini d'inondazione (Enhanced) sono disattivati"}
  {key:"#overlay_flood_basin_open", text:"Campo di limo aperto — non in un bacino chiuso"}
  {key:"#overlay_flood_basin_none", text:"Nessun bacino di piena qui"}
  {key:"#warning_auto_resolve_orders_blocked", text:"Non si possono far marciare le compagnie su un'onda d'invasione congelata"}
  {key:"#warning_auto_resolve_queue_full", text:"Troppe invasioni in coda — questa onda combatte sulla mappa"}
  {key:"#follow_walker", text:"Segui il camminatore"}
  {key:"#stop_following", text:"Stop"}
  {key:"#warning_follow_walker_lost", text:"Camminatore seguito perso"}
  {key:"#invasion_quick_battle_title", text:"Battaglia rapida"}
  {key:"#invasion_quick_battle_hint", text:"Gli invasori attendono all'ingresso. Recluta se serve. Combatti ora o attendi il timer."}
  {key:"#invasion_quick_battle_resolve", text:"Combatti"}
  {key:"#invasion_quick_battle_wait", text:"Attendi"}
  {key:"#invasion_quick_battle_strength", text:"Le tue forze: {player}   Nemico: {enemy}"}
  {key:"#invasion_quick_battle_days", text:"Battaglia tra {days} giorni"}
  {key:"#invasion_quick_battle_queue", text:"({n} in coda)"}
  {key:"#invasion_quick_battle_head", text:"Ondata #{id} ({i}/{n})"}
  {key:"#invasion_quick_battle_none", text:"Nessuna battaglia in attesa"}
  {key:"#TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD", text:"Le sentinelle delle torri non richiedono strade dalle caserme"}
  {key:"#TR_CONFIG_FARMS_DELIVER_CLOSE", text:"Fattorie e moli consegnano solo ai granai vicini"}
  {key:"#TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES", text:"Il cibo non viene consegnato ai granai in raccolta"}
  {key:"#TR_CONFIG_ALL_HOUSES_MERGE", text:"Tutte le case si uniscono"}
  {key:"#TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE", text:"Una via commerciale aperta conta come un tipo di vino diverso"}
  {key:"#TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY", text:"Le cave d'argilla e le miniere di ferro, invece di crollare a caso, costano denaro"}
  {key:"#TR_CONFIG_DISASTER_EVENTS_USE_AMOUNT", text:"Alluvione dell'argilla / crollo dell'oro distruggono la quantità di costruzioni indicata dall'evento"}
  {key:"#TR_CONFIG_MULTIPLE_BARRACKS", text:"Consenti la costruzione di più caserme."}
  {key:"#TR_CONFIG_NOT_ACCEPTING_WAREHOUSES", text:"I depositi non accettano nulla appena costruiti"}
  {key:"#TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS", text:"Le case non si espandono sui giardini"}
  {key:"#TR_CONFIG_FIX_IRRIGATION_RANGE", text:"Correggi il raggio d'irrigazione"}
  {key:"#TR_CONFIG_FIX_FARM_PRODUCING", text:"Correggi la produzione delle fattorie"}
  {key:"#TR_CONFIG_EMPIRE_MAP_RUNS_SIMULATION", text:"Continua la simulazione della città con la mappa dell'impero aperta"}
  {key:"#TR_CONFIG_CAMERA_KEEP_INERTIA", text:"Inerzia della telecamera"}
  {key:"#TR_CONFIG_UNDERSTAFFED_ACCEPT_GOODS", text:"Con personale insufficiente accetta le merci"}
  {key:"#TR_CONFIG_MULTIPLE_TEMPLE_COMPLEXES", text:"Complessi templi multipli"}
  {key:"#TR_CONFIG_MULTIPLE_MONUMENTS", text:"Monumenti multipli"}
  {key:"#TR_CONFIG_SOIL_DEPLETION", text:"Impoverimento del suolo"}
  {key:"#TR_CONFIG_MULTIPLE_GATHERERS", text:"Raccoglitori multipli"}
  {key:"#TR_CONFIG_FIREMAN_RETURNING", text:"Il pompiere rientra dopo aver spento l'incendio"}
  {key:"#TR_CONFIG_ARCHITECT_PATROL_MOST_DAMAGED", text:"Gli architetti vanno agli edifici più danneggiati"}
  {key:"#TR_CONFIG_CART_SPEED_DEPENDS_QUANTITY", text:"La velocità del carro dipende dalla quantità di merce"}
  {key:"#TR_CONFIG_CH_CITIZEN_ROAD_OFFSET", text:"Usa offset diversi per i cittadini sulla strada"}
  {key:"#TR_CONFIG_CH_WORK_CAMP_ONE_WORKER_PER_MONTH", text:"Il campo di lavoro genera un lavoratore al mese"}
  {key:"#TR_CONFIG_CH_CLAY_PIT_FIRE_RISK_REDUCED", text:"Rischio d'incendio ridotto per la cava d'argilla"}
  {key:"#TR_CONFIG_CITY_HAS_ANIMALS", text:"La città ha animali"}
  {key:"#TR_CONFIG_GOLDMINE_TWICE_PRODUCTION", text:"Miniera d'oro a produzione doppia"}
  {key:"#TR_CONFIG_NEW_TAX_COLLECTION_SYSTEM", text:"Nuovo sistema di riscossione delle tasse"}
  {key:"#TR_CONFIG_SMALL_HUT_NOT_CREATE_EMIGRANT", text:"Le capanne piccole non generano emigranti"}
  {key:"#TR_CONFIG_DELIVERY_BOY_GOES_TO_MARKET_ALONE", text:"Il fattorino va al bazar da solo"}
  {key:"#TR_CONFIG_RELIGION_COVERAGE_INFLUENCE_SENTIMENT", text:"La copertura religiosa influenza l'umore"}
  {key:"#TR_CONFIG_MONUMENTS_INFLUENCE_SENTIMENT", text:"I monumenti influenzano l'umore della città"}
  {key:"#TR_CONFIG_WELL_RADIUS_DEPENDS_MOISTURE", text:"Il raggio del pozzo dipende dall'umidità"}
  {key:"#TR_CONFIG_ENTER_POINT_ON_NEAREST_TILE", text:"Ingresso dell'edificio sulla casella più vicina"}
  {key:"#TR_CONFIG_FISHING_WHARF_SPAWN_BOATS", text:"La banchina da pesca genera barche"}
  {key:"#TR_CONFIG_CITY_FLOTSAM_ENABLED", text:"Relitti in città attivi"}
  {key:"#TR_CONFIG_COPPER_NEAR_MOUNTAINS", text:"La miniera di rame si può costruire vicino alle montagne"}
  {key:"#TR_CONFIG_RECRUITER_NOT_NEED_FORTS", text:"Il reclutatore non richiede forti"}
  {key:"#TR_CONFIG_BUILDING_CLOSEST_ROAD", text:"Accesso della costruzione alla strada più vicina"}
  {key:"#TR_CONFIG_FLOODPLAIN_RANDOM_GROW", text:"Crescita casuale sul campo di limo"}
  {key:"#TR_CONFIG_DRAW_FPS", text:"Mostra FPS"}
  {key:"#TR_CONFIG_SHOW_CURRENT_SELECT_TILE", text:"Mostra sulla mappa la casella sotto il cursore"}
  {key:"#TR_CONFIG_SHOW_INPUT_NEAR_CURSOR", text:"Mostra tasti e pulsanti premuti vicino al cursore"}
  {key:"#TR_CONFIG_ROAD_PREVIEW_IN_MAP_ORDER", text:"Disegna l'anteprima delle strade nell'ordine di rendering della mappa"}
  {key:"#TR_CONFIG_HIGHLIGHT_TOP_MENU_HOVER", text:"Evidenzia le voci del menu in alto"}
  {key:"#TR_CONFIG_EMPIRE_CITY_OLD_NAMES", text:"Mostra i nomi antichi delle città sulla mappa dell'impero"}
  {key:"#TR_CONFIG_DRAW_CLOUD_SHADOWS", text:"Disegna le ombre delle nuvole (sperimentale)"}
  {key:"#TR_CONFIG_CONSERVATORY_HELPS_DANCE_SCHOOL", text:"Il conservatorio aiuta la scuola di danza (riduce il ritardo di uscita)"}
  {key:"#TR_CONFIG_JEWELS_WORKSHOPS_CULTURE_BONUS", text:"Le gioiellerie danno un bonus alla cultura (+1 ogni 3 officine)"}
  {key:"#TR_CONFIG_OVERLAY_SHOW_GRAY_BUILDINGS", text:"Mostra in grigio gli edifici non visualizzati nelle tabelle"}
  {key:"#TR_CONFIG_BREWERY_REQUIRES_WATER", text:"La distilleria richiede accesso all'acqua"}
  {key:"#TR_CONFIG_CARTPUSHERS_YIELD_BY_ID", text:"I carrettieri consegnano le merci in base all'ID del lavoratore"}
  {key:"#TR_CONFIG_REBALANCE_WORKSHOP_OUTPUT", text:"La produzione delle officine varia con la difficoltà"}
  {key:"#TR_CONFIG_PREVENT_DELETE_NEAR_BURNING_RUINS", text:"Impedisci di demolire edifici vicino a rovine in fiamme"}
  {key:"#TR_CONFIG_DISABLE_NILOMETER_POPUPS", text:"Disattiva i messaggi del nilometro sulla previsione della piena"}
  {key:"#TR_CONFIG_ENHANCED_NILOMETER", text:"Migliorato: HUD del nilometro (qualità della piena, fase, info sul campo di limo)"}
  {key:"#TR_CONFIG_ENHANCED_SHRINE_INFO", text:"Migliorato: mostra la descrizione del santuario nella finestra di esame"}
  {key:"#flood_phase_imminent", text:"Inondazione imminente"}
  {key:"#flood_phase_flooding", text:"Inondazione"}
  {key:"#flood_phase_inundated", text:"Inondato"}
  {key:"#flood_phase_contracting", text:"Le acque si ritirano"}
  {key:"#flood_phase_resting", text:"Piena stazionaria"}
  {key:"#flood_phase_farmable", text:"Campo di limo coltivabile"}
  {key:"#nilometer_last_prefix", text:"Ultima piena:"}
  {key:"#nilometer_hud_tooltip", text:"Nilometro — previsione della prossima piena e fase attuale del campo di limo"}
  {key:"#TR_CONFIG_HEADER_SCENARIO_CHANGES", text:"Modifiche agli scenari"}
  {key:"#TR_CONFIG_HEADER_RESOURCES", text:"Modifica risorse"}
  {key:"#TR_CONFIG_ANIMALS", text:"Cambia animali"}
  {key:"#TR_CONFIG_FLOTSAM", text:"Relitti"}
  {key:"#TR_GAMEPLAY_GOD_DISABLED", text:"Divinità disattivata"}
  {key:"#TR_HOTKEY_TITLE", text:"Configurazione delle scorciatoie da tastiera"}
  {key:"#TR_HOTKEY_LABEL", text:"Tasto"}
  {key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Alternativa"}
  {key:"#TR_HOTKEY_HEADER_ARROWS", text:"Frecce"}
  {key:"#TR_HOTKEY_HEADER_GLOBAL", text:"Scorciatoie globali"}
  {key:"#TR_HOTKEY_HEADER_CITY", text:"Scorciatoie per la città"}
  {key:"#TR_HOTKEY_HEADER_ADVISORS", text:"Consiglieri"}
  {key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"Tabelle"}
  {key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"Segnaposto sulla mappa"}
  {key:"#TR_HOTKEY_HEADER_EDITOR", text:"Editor"}
  {key:"#TR_HOTKEY_HEADER_BUILD", text:"Scorciatoie per costruzione"}
  {key:"#TR_HOTKEY_ARROW_UP", text:"Su"}
  {key:"#TR_HOTKEY_ARROW_DOWN", text:"Giù"}
  {key:"#TR_HOTKEY_ARROW_LEFT", text:"Sinistra"}
  {key:"#TR_HOTKEY_ARROW_RIGHT", text:"Destra"}
  {key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Tutto schermo"}
  {key:"#TR_HOTKEY_CENTER_WINDOW", text:"Centra la finestra"}
  {key:"#TR_HOTKEY_RESIZE_TO_640", text:"Finestra a 640x480"}
  {key:"#TR_HOTKEY_RESIZE_TO_800", text:"Finestra a 800x600"}
  {key:"#TR_HOTKEY_RESIZE_TO_1024", text:"Finestra a 1024x768"}
  {key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"Salva l'immagine"}
  {key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Salva l'immagine dell'intera città"}
  {key:"#TR_HOTKEY_LOAD_FILE", text:"Carica file"}
  {key:"#TR_HOTKEY_SAVE_FILE", text:"Salva file"}
  {key:"#TR_HOTKEY_QUICKSAVE", text:"Salvataggio rapido"}
  {key:"#TR_HOTKEY_QUICKLOAD", text:"Caricamento rapido"}
  {key:"#quicksave_ok", text:"Salvataggio rapido eseguito"}
  {key:"#quickload_ok", text:"Caricamento rapido eseguito"}
  {key:"#quicksave_missing", text:"Nessun salvataggio rapido"}
  {key:"#quicksave_failed", text:"Salvataggio rapido fallito"}
  {key:"#quickload_failed", text:"Quickload non riuscito"}
  {key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Aumenta la velocità"}
  {key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Diminuisce la velocità"}
  {key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"Pausa"}
  {key:"#TR_HOTKEY_CYCLE_LEGION", text:"Scorre le legioni"}
  {key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Ruota la mappa a sinistra"}
  {key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Ruota la mappa a destra"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Consigliere del lavoro"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Consigliere militare"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Consigliere dell'Impero"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Consigliere dei livelli"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Consigliere commerciale"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"Consigliere della popolazione"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Consigliere della sanità"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Consigliere dell'educazione"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Consigliere degli intrattenimenti"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Consigliere religioso"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Consigliere finanziario"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Consigliere capo"}
  {key:"#TR_HOTKEY_SHOW_ADVISOR_HOUSING", text:"Supervisore delle abitazioni"}
  {key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"Cambia la tabella corrente"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Tabella acqua"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Tabella fuoco"}
  {key:"#TR_HOTKEY_TOGGLE_FLAT_BUILDINGS", text:"Vista piatta edifici"}
  {key:"#TR_TOOLTIP_FLAT_BUILDINGS", text:"Vista piatta edifici (Shift+F). Quando attiva: Ctrl+clic destro solleva un edificio."}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Tabella danni"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Tabella crimine"}
  {key:"#TR_HOTKEY_ROTATE_BUILDING", text:"Ruota costruzione"}
  {key:"#TR_HOTKEY_COPY_BUILD", text:"Copia l'edificio sotto il cursore"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Tabella problemi"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_MALARIA_RISK", text:"Tabella rischio malaria"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_DISEASE", text:"Tabella malattia"}
  {key:"#TR_HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS", text:"Nascondi scogliere"}
  {key:"#grain_stocks_none", text:"Questa casa non ha scorte di grano"}
  {key:"#grain_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di grano"}
  {key:"#grain_stocks_medium", text:"Questa casa ha scorte di grano per almeno il mese a venire"}
  {key:"#grain_stocks_high", text:"Questa casa non ha problemi a procurarsi il grano di cui ha bisogno"}
  {key:"#chickpeas_stocks_none", text:"Questa casa non ha scorte di ceci"}
  {key:"#chickpeas_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di ceci"}
  {key:"#chickpeas_stocks_medium", text:"Questa casa ha scorte di ceci sufficienti almeno per il mese prossimo"}
  {key:"#chickpeas_stocks_high", text:"Questa casa non ha problemi a ottenere i ceci di cui ha bisogno"}
  {key:"#pomegranates_stocks_none", text:"Questa casa non ha scorte di melograni"}
  {key:"#pomegranates_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di melograni"}
  {key:"#pomegranates_stocks_medium", text:"Questa casa ha scorte di melagrane per almeno il mese a venire"}
  {key:"#pomegranates_stocks_high", text:"Questa casa non ha problemi a procurarsi i melograni di cui ha bisogno"}
  {key:"#figs_stocks_none", text:"Questa casa non ha scorte di fichi"}
  {key:"#figs_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di fichi"}
  {key:"#figs_stocks_medium", text:"Questa casa ha scorte di fichi sufficienti almeno per il mese prossimo"}
  {key:"#figs_stocks_high", text:"Questa casa non ha problemi a ottenere i fichi di cui ha bisogno"}
  {key:"#meat_stocks_none", text:"Questa casa non ha scorte di carne"}
  {key:"#meat_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di carne"}
  {key:"#meat_stocks_medium", text:"Questa casa ha scorte di carne per almeno il mese a venire"}
  {key:"#meat_stocks_high", text:"Questa casa non ha problemi a procurarsi la carne di cui ha bisogno"}
  {key:"#game_stocks_none", text:"Questa casa non ha scorte di cacciagione"}
  {key:"#game_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di cacciagione"}
  {key:"#game_stocks_medium", text:"Questa casa ha scorte di cacciagione sufficienti almeno per il mese prossimo"}
  {key:"#game_stocks_high", text:"Questa casa non ha problemi a ottenere la cacciagione di cui ha bisogno"}
  {key:"#pottery_stocks_none", text:"Questa casa non ha scorte di vasellame"}
  {key:"#pottery_stocks_low", text:"Questa casa esaurirà presto le sue scorte limitate di vasellame"}
  {key:"#pottery_stocks_medium", text:"Questa casa ha scorte di vasellame per almeno il mese a venire"}
  {key:"#pottery_stocks_high", text:"Questa casa non ha problemi a procurarsi il vasellame di cui ha bisogno"}
  {key:"#jewelry_stocks_none", text:"Questa casa non ha scorte di gioielli"}
  {key:"#jewelry_stocks_low", text:"Questa casa esaurirà presto le sue scorte limitate di gioielli"}
  {key:"#jewelry_stocks_medium", text:"Questa casa ha scorte di gioielli sufficienti almeno per il mese prossimo"}
  {key:"#jewelry_stocks_high", text:"Questa casa non ha problemi a ottenere i gioielli di cui ha bisogno"}
  {key:"#linen_stocks_none", text:"Questa casa non ha scorte di tela"}
  {key:"#linen_stocks_low", text:"Questa casa esaurirà presto le sue scorte limitate di tela"}
  {key:"#linen_stocks_medium", text:"Questa casa ha scorte di tela per almeno il mese a venire"}
  {key:"#linen_stocks_high", text:"Questa casa non ha problemi a procurarsi la tela di cui ha bisogno"}
  {key:"#empty_housing_vacant", text:"Nessuno vive in questa abitazione"}
  {key:"#irrigation_none", text:"Questa terra non è irrigata"}
  {key:"#irrigation_low", text:"Questo terreno ha un'irrigazione limitata"}
  {key:"#irrigation_medium", text:"Questa terra è moderatamente irrigata"}
  {key:"#irrigation_high", text:"Questa terra è ben irrigata"}
  {key:"#overlay_water_crossings_ferry", text:"Traghetto"}
  {key:"#overlay_water_crossings_bridge", text:"Passaggio a ponte"}
  {key:"#overlay_city_defenses_structure", text:"Struttura difensiva della città"}
  {key:"#overlay_hide_cliffs_hint", text:"Le rupi sono temporaneamente appiattite"}
  {key:"#overlay_grain", text:"Grano"}
  {key:"#overlay_chickpeas", text:"Ceci"}
  {key:"#overlay_pomegranates", text:"Melograni"}
  {key:"#overlay_figs", text:"Fichi"}
  {key:"#overlay_meat", text:"Carne"}
  {key:"#overlay_game", text:"Gioco"}
  {key:"#overlay_pottery", text:"Vasellame"}
  {key:"#overlay_jewelry", text:"Gioielli"}
  {key:"#overlay_linen", text:"Tela"}
  {key:"#overlay_beer", text:"Birra"}
  {key:"#overlay_disease", text:"Malattia"}
  {key:"#overlay_infected_housing", text:"Ambiente infetto"}
  {key:"#overlay_malaria", text:"Malaria"}
  {key:"#overlay_water_crossings", text:"Guadi"}
  {key:"#overlay_empty_housing", text:"Ambiente vuoto"}
  {key:"#overlay_irrigation", text:"Irrigazione"}
  {key:"#overlay_city_defenses", text:"Difese cittadine"}
  {key:"#overlay_hide_cliffs", text:"Nascondi rupi"}
  {key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Va al segnaposto 1"}
  {key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Va al segnaposto 2"}
  {key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Va al segnaposto 3"}
  {key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Va al segnaposto 4"}
  {key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"Fissa il segnaposto 1"}
  {key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"Fissa il segnaposto 2"}
  {key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"Fissa il segnaposto 3"}
  {key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"Fissa il segnaposto 4"}
  {key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Informazioni sulla battaglia"}
  {key:"#TR_HOTKEY_EDIT_TITLE", text:"Premi un nuovo tasto"}
  {key:"#TR_HOTKEY_DUPLICATE_TITLE", text:"Tasto già assegnato"}
  {key:"#TR_HOTKEY_DUPLICATE_MESSAGE", text:"Questo tasto è già assegnato a '{0}'."}
  {key:"#TR_BUILDING_ROADBLOCK", text:"Blocco stradale"}
  {key:"#TR_BUILDING_ROADBLOCK_DESC", text:"Il blocco stradale ferma i cittadini che vagabondano."}
  {key:"#TR_HEADER_HOUSING", text:"Abitazione"}
  {key:"#TR_ADVISOR_HOUSING_ROOM", text:"Le abitazioni della città hanno posto per"}
  {key:"#TR_ADVISOR_HOUSING_NO_ROOM", text:"Non c'è più posto nelle abitazioni della città."}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY", text:"Abitazioni che richiedono vasellame"}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE", text:"Abitazioni che richiedono mobili"}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_OIL", text:"Abitazioni che richiedono olio"}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_LINEN", text:"Abitazioni che richiedono tela"}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_WINE", text:"Residenze che chiedono vino"}
  {key:"#TR_ADVISOR_RESIDENCES_DEMANDING_BEER", text:"Abitazioni che richiedono birra"}
  {key:"#TR_ADVISOR_TOTAL_NUM_HOUSES", text:"Abitazioni totali:"}
  {key:"#TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY", text:"Capacità disponibile:"}
  {key:"#TR_ADVISOR_TOTAL_HOUSING_CAPACITY", text:"Capacità totale:"}
  {key:"#TR_ADVISOR_ADVISOR_HEADER_HOUSING", text:"Popolazione - Abitazione"}
  {key:"#TR_ADVISOR_BUTTON_GRAPHS", text:"Grafici"}
  {key:"#TR_ADVISOR_HOUSING_PROSPERITY_RATING", text:"Il livello di prosperità delle abitazioni è"}
  {key:"#TR_ADVISOR_PERCENTAGE_IN_MANORS", text:"La percentuale della popolazione in ville e palazzi è"}
  {key:"#TR_ADVISOR_PERCENTAGE_IN_SHANTIES", text:"La percentuale della popolazione in tende e capanne è"}
  {key:"#TR_ADVISOR_AVERAGE_TAX", text:"La media dei proventi tasse per abitazione è"}
  {key:"#TR_ADVISOR_AVERAGE_AGE", text:"L'età media della tua popolazione è"}
  {key:"#TR_ADVISOR_PERCENT_IN_WORKFORCE", text:"La percentuale della tua popolazione nella forza lavoro è"}
  {key:"#TR_ADVISOR_BIRTHS_LAST_YEAR", text:"Nascite nell'ultimo anno:"}
  {key:"#TR_ADVISOR_DEATHS_LAST_YEAR", text:"Morti nell'ultimo anno:"}
  {key:"#TR_ADVISOR_TOTAL_POPULATION", text:"residenti in totale"}
  {key:"#main_menu_mods", text:"Mod"}
  {key:"#main_menu_editor", text:"Editor"}
  {key:"#advisor_imperial_political_overseer_for", text:"Supervisore politico di"}
  {key:"#warship_moving_to_position", text:"In movimento verso la posizione"}
  {key:"#warship_moving_to_position_text", text:"La nave sta raggiungendo la posizione che hai indicato e vi resterà finché non le darai altri ordini."}
  {key:"#main_menu_update_downloading", text:"Scarico l'aggiornamento..."}
  {key:"#main_menu_update_opening_page", text:"Apro la pagina di scaricamento..."}
  {key:"#main_menu_update_now", text:"aggiorna ora"}
  {key:"#main_menu_update_later", text:"più tardi"}
  {key:"#main_menu_loading_commits", text:"Carico le ultime modifiche..."}
  {key:"#main_menu_new_build", text:"Nuova versione: ${commit} (hai la ${local})"}
  {key:"#main_menu_updated", text:"Aggiornato"}
  {key:"#main_menu_build_up_to_date", text:"Versione ${build} (aggiornata)"}
  {key:"#message_dialog_distant_battle", text:"Battaglia lontana"}
  {key:"#mods_window_title", text:"Mod"}
  {key:"#mods_window_unpack_scripts", text:"Estrai gli script"}
  {key:"#mods_window_refresh_list", text:"Aggiorna elenco"}
  {key:"#mods_window_hint", text:"Tasto destro per uscire, doppio clic per attivare o spegnere una mod"}
  {key:"#records_not_played_yet", text:"mai giocato"}
  {key:"#report_bug_title", text:"Segnala un problema"}
  {key:"#report_bug_field_title", text:"Titolo"}
  {key:"#report_bug_field_description", text:"Descrizione"}
  {key:"#report_bug_submit_question", text:"Invio?"}
  {key:"#report_bug_error_no_title", text:"Manca il titolo."}
  {key:"#report_bug_error_short_description", text:"Serve una descrizione (almeno 10 caratteri)."}
  {key:"#report_bug_sending", text:"Invio in corso..."}
  {key:"#report_bug_sent", text:"Segnalato, grazie."}
  {key:"#report_bug_error", text:"Errore:"}
  {key:"#report_bug_tooltip", text:"Segnala un problema"}
  {key:"#scenario_selection_file_schema", text:"Schema del file:"}
  {key:"#features_god_enabled", text:"Dio attivo"}
  {key:"#features_city_allow", text:"La città permette"}
  {key:"#features_prev_page", text:"Prec"}
  {key:"#features_next_page", text:"Succ"}
  {key:"#mission2_store_figs", text:"Costruisci un Granaio e riempilo di fichi"}
  {key:"#message_population_title", text:"Traguardo di popolazione"}
  {key:"#message_population_100", text:"100 persone si sono trasferite nel tuo villaggio"}
  {key:"#message_population_500", text:"La tua città in crescita ospita ora cinquecento abitanti"}
  {key:"#message_population_1000", text:"Mille persone ora chiamano casa la tua città."}
  {key:"#message_population_2000", text:"Con duemila residenti, la tua città sta acquistando importanza."}
  {key:"#message_population_3000", text:"La popolazione della tua città ha raggiunto le tremila unità per la prima volta nella storia."}
  {key:"#message_population_5000", text:"La tua città sta diventando piuttosto grande.  Ora ci vivono cinquemila persone."}
  {key:"#message_population_10000", text:"Una popolazione di diecimila abitanti colloca la tua città ai vertici dell'Egitto."}
  {key:"#message_population_15000", text:"Nuove città possono rivaleggiare con la tua, che ora ospita quindicimila cittadini."}
  {key:"#message_population_20000", text:"Altri governatori e nomarchi sono stupiti che la tua città ospiti ventimila persone!"}
  {key:"#message_population_25000", text:"I pochi immigranti che fondarono la tua città tanti anni fa non avrebbero mai immaginato che sarebbe arrivata a venticinquemila persone!"}
  {key:"#mission0_goal_create_housing", text:"Crea una zona di abitazioni e osserva l'arrivo degli immigranti"}
  {key:"#mission0_goal_build_granary", text:"Costruisci un Granaio che i cacciatori possano riempire di selvaggina"}
  {key:"#mission1_goal_build_mines", text:"Estrai oro per il tesoro del palazzo"}
  {key:"#mission1_goal_build_temples", text:"Costruisci alcuni Templi e Santuari dedicati a Bast"}
  {key:"#mission1_goal_build_entertainment", text:"Costruisci Baracconi e Scuole dei giocolieri per aumentare la Cultura della città"}
  {key:"#exit_this_panel", text:"Esci da questo pannello"}
  {key:"#display_options_title", text:"Opzioni video"}
  {key:"#popup_dialog_quit", text:"Esci"}
  {key:"#popup_dialog_open_trade", text:"Apri via commerciale"}
  {key:"#popup_dialog_send_goods", text:"Inviare le merci?"}
  {key:"#popup_dialog_not_enough_goods", text:"Richiesta del Faraone"}
  {key:"#popup_dialog_no_legions_available", text:"Richiesta del Faraone"}
  {key:"#popup_dialog_no_legions_selected", text:"Richiesta del Faraone"}
  {key:"#popup_dialog_send_troops", text:"Richiesta del Faraone"}
  {key:"#popup_dialog_delete_fort", text:"Demolizione di un forte"}
  {key:"#popup_dialog_delete_bridge", text:"Demolizione di un ponte"}
  {key:"#popup_dialog_quit_without_saving", text:"Esci"}
  {key:"#popup_dialog_map_file_missing", text:"File della mappa mancante"}
  {key:"#exit_without_saving", text:"Uscire senza salvare?"}
  {key:"#popup_dialog_no_festival_square", text:"Festività: nessuna Piazza delle festività."}
  {key:"#popup_dialog_delete_dynasty", text:"Eliminare la dinastia?"}
  {key:"#popup_dialog_no_dynasty", text:"Nessuna dinastia"}
  {key:"#popup_dialog_no_player_name", text:"Inserisci il nome della famiglia."}
  {key:"#replay_mission", text:"Rigioca missione"}
  {key:"#mission_won_culture_rating", text:"Valutazione finale Cultura"}
  {key:"#mission_won_prosperity_rating", text:"Livello di Prosperità finale"}
  {key:"#mission_won_kingdom_rating", text:"Livello del Regno finale"}
  {key:"#mission_won_population", text:"Popolazione finale"}
  {key:"#mission_won_monument_rating", text:"Livello monumenti finale"}
  {key:"#ui_gift_to_kingdome_window_title", text:"Dona al popolo d'Egitto"}
  {key:"#ui_unable_to_fulfill_request", text:"Impossibile soddisfare la richiesta"}
  {key:"#ui_gift_time_since_last", text:"Tempo dall'ultimo dono"}
  {key:"#ui_gift_label_modest", text:"Modesto:"}
  {key:"#ui_gift_label_generous", text:"Generoso:"}
  {key:"#ui_gift_label_lavish", text:"Sontuoso:"}
  {key:"#ui_gift_dispatch_modest", text:"Invia dono modesto"}
  {key:"#ui_gift_dispatch_generous", text:"Invia dono generoso"}
  {key:"#ui_gift_dispatch_lavish", text:"Invia dono sontuoso"}
  {key:"#ui_gift_cannot_afford_savings", text:"Non hai abbastanza risparmi personali per fare un dono all'Egitto. Prova ad aumentarti lo stipendio!"}
  {key:"#ui_mission_choice_prompt", text:"Scegli una città da governare "}
  {key:"#granary_info_title", text:"Granaio"}
  {key:"#granary_no_road_access", text:"ATTENZIONE: questo edificio non è adiacente a una strada"}
  {key:"#granary_kingdom_supplies_grain", text:"Questo granaio non è necessario. L'Egitto fornisce alla nostra città tutto il grano che le serve. Il cibo che produciamo finirà direttamente nei depositi merci con spazio libero."}
  {key:"#granary_storing", text:"In deposito"}
  {key:"#granary_space_for", text:"Spazio per"}
  {key:"#granary_units", text:"unità."}
  {key:"#chief_overseer", text:"Supervisore capo"}
  {key:"#chief_adv_sentiment", text:"Umore della città"}
  {key:"#chief_adv_migration", text:"Migrazione"}
  {key:"#chief_adv_workers", text:"Occupazione"}
  {key:"#chief_adv_foodstocks", text:"Scorte di cibo"}
  {key:"#chief_adv_foodconsumption", text:"Produzione alimentare"}
  {key:"#chief_adv_health", text:"Salute"}
  {key:"#chief_adv_religion", text:"Religione"}
  {key:"#chief_adv_finance", text:"Finanze"}
  {key:"#chief_adv_crime", text:"Crimine"}
  {key:"#chief_adv_military", text:"Armamento"}
  {key:"#chief_adv_kingdom", text:"Regno"}
  {key:"#chief_adv_nilometr", text:"Nilometro"}
  {key:"#trade_overseer", text:"Supervisore commerciale"}
  {key:"#building_have_no_access", text:"ATTENZIONE: questo edificio non è adiacente a una strada"}
  {key:"#bazaar_info_title", text:"Bazar"}
  {key:"#well_info_title", text:"Pozzo"}
  {key:"#well_info_necessary", text:"I cittadini senza consegne di acqua pulita possono attingere ai pozzi, ma i quartieri serviti solo dai pozzi non sono i luoghi più salubri né più ambiti in cui vivere."}
  {key:"#well_info_unneeded_fountain", text:"Questo pozzo non è necessario. Tutte le case che serve ricevono consegne da un serbatoio d'acqua."}
  {key:"#well_info_unneeded_no_houses", text:"L'acqua di questo pozzo va sprecata, poiché non ci sono case entro il suo raggio d'azione."}
  {key:"#visit_rating_advisor", text:"Visita il supervisore dei livelli?"}
  {key:"#tax_rate_of", text:"Livello tasse del"}
  {key:"#palace_vaults_hold", text:"Il tesoro è di"}
  {key:"#debens", text:"Deben"}
  {key:"#building_no_road_access", text:"ATTENZIONE: questa costruzione non è adiacente a una strada"}
  {key:"#building_no_people_in_city", text:"Non c'è nessuno in città!"}
  {key:"#building_no_workers_nearby", text:"Nessun lavoratore vive nelle vicinanze"}
  {key:"#building_labor_could_shift", text:"Il Supervisore dei lavoratori potrebbe spostare della manodopera"}
  {key:"#building_poor_worker_access", text:"ATTENZIONE: scarso accesso ai lavoratori"}
  {key:"#gardens_describe", text:"Questo piacevole spazio offre ai cittadini sollievo dal rumore, dal caldo e dallo sporco della città con una fresca oasi di verde.  Tutti vogliono un giardino accanto a casa."}
  {key:"#popup_dialog_proceed", text:"Continua?"}
  {key:"#autosave_slots", text:"Slot di salvataggio automatico"}
  {key:"#immigration_people_wont_come", text:"Le persone non vogliono venire nella tua città"}
  {key:"#mansion_protected_by_police", text:"Protetto dalla polizia"}
  {key:"#mansion_not_protected_theft", text:"Non protetto — i ladri possono rubare i risparmi"}
  {key:"#abu_simbel_not_demolishable", text:"Abu Simbel non può essere demolito"}
  {key:"#pharaoh_inspecting_city", text:"Cammino tra il mio popolo. Che vedano il loro Faraone."}
  {key:"#pharaoh_disease_risk", text:"Febbre nelle mie strade? I miei medici sistemeranno la cosa."}
  {key:"#pharaoh_no_food_in_city", text:"Granai vuoti sotto il mio regno? Non lo tollererò."}
  {key:"#pharaoh_city_have_no_army", text:"Nessun forte? Una sola incursione e la mia città cade. Alzate gli stendardi."}
  {key:"#pharaoh_gods_are_angry", text:"Gli dei ci guardano con disappunto. Anche il Faraone deve ascoltare i templi."}
  {key:"#pharaoh_low_entertainment", text:"Nessuna festività da un'eternità. Il mio popolo merita musica e vino."}
  {key:"#pharaoh_city_is_good", text:"Una bella città. Ordine, pane e lealtà: come dev'essere."}
  {key:"#pharaoh_city_is_amazing", text:"Questa città splende come il Nilo all'alba. L'Egitto stesso ne è fiero!"}
  {key:"#plagued_i_feel_awful", text:"Mi sento malissimo... tutto gira e brucia."}
  {key:"#plagued_fever_spreads", text:"La febbre si diffonde. State indietro, non posso fermarmi."}
  {key:"#plagued_no_food_in_city", text:"Granai vuoti e febbre alta. Che modo di morire di fame."}
  {key:"#plagued_city_have_no_army", text:"Nessun forte? La malattia prenderà questa città prima di qualunque nemico."}
  {key:"#plagued_gods_are_angry", text:"Gli dei sono adirati. È la loro maledizione che mi striscia dentro?"}
  {key:"#plagued_low_entertainment", text:"Nessuna festività da un'eternità... solo colpi di tosse per le strade."}
  {key:"#plagued_city_is_good", text:"La città sembrava a posto. Perché questa febbre ha scelto me?"}
  {key:"#plagued_city_is_amazing", text:"La chiamano la città migliore: e allora perché sto morendo per le sue strade?"}
  {key:"#protestor_we_want_justice", text:"Vogliamo giustizia! Ascoltate le nostre voci per strada!"}
  {key:"#protestor_tax_too_high", text:"Queste tasse ci dissanguano! Basta!"}
  {key:"#protestor_wages_too_low", text:"I nostri stipendi non comprano il pane. Paga giusta o non ci muoviamo!"}
  {key:"#protestor_no_jobs", text:"Niente lavoro, niente speranza: e pretendi il silenzio?"}
  {key:"#protestor_no_food_in_city", text:"Granai vuoti! Per quanto ancora dovremo patire la fame in silenzio?"}
  {key:"#protestor_city_have_no_army", text:"Nessun forte? Ci lasciano indifesi e oberati di tasse!"}
  {key:"#protestor_gods_are_angry", text:"Persino gli dèi sono corrucciati. Questa città ha perso la retta via!"}
  {key:"#protestor_low_entertainment", text:"Niente festività, solo fame e tasse. Che vita è questa?"}
  {key:"#protestor_city_is_good", text:"Dicono che la città vada bene. Bene per chi?"}
  {key:"#protestor_city_is_amazing", text:"Città meravigliosa? Ditelo agli stomaci vuoti e alle borse vuote!"}
  {key:"#rioter_burn_it_down", text:"Bruciate tutto! Questa città ascolterà il fuoco!"}
  {key:"#rioter_tax_too_high", text:"Prima gli esattori, poi il resto della tua bella città!"}
  {key:"#rioter_wages_too_low", text:"Ci affamate con gli avanzi? Allora distruggiamo ciò che non possiamo comprare!"}
  {key:"#rioter_no_jobs", text:"Niente lavoro? Allora ce lo creiamo noi — con le torce!"}
  {key:"#rioter_no_food_in_city", text:"Granai vuoti! Prenderemo ciò che ci serve dalle tue scorte!"}
  {key:"#rioter_city_have_no_army", text:"Nessun forte? Niente si frappone tra noi e il palazzo!"}
  {key:"#rioter_gods_are_angry", text:"Gli dèi sono adirati, e anche noi! Abbattiamo tutto!"}
  {key:"#rioter_low_entertainment", text:"Niente festività? Ecco uno spettacolo: guardate cadere gli edifici!"}
  {key:"#rioter_city_is_good", text:"Bella città? Bella per i ricchi. Non per noi!"}
  {key:"#rioter_city_is_amazing", text:"Che strade stupende da bruciare. Stanotte le vedrai ardere!"}
  {key:"#robber_maybe_stealing_will_get_attention", text:"Forse rubando otterrò un po' di attenzione!"}
  {key:"#robber_i_take_what_i_want", text:"Prendo ciò che voglio!"}
  {key:"#robber_more_profitable_than_other_jobs", text:"Più redditizio di altri lavori in questa città."}
  {key:"#robber_take_take_take", text:"Prendi, prendi, prendi!"}
  {key:"#robber_tax_too_high", text:"Le tasse prendono da te, io prendo dal palazzo!"}
  {key:"#robber_wages_too_low", text:"Stipendi troppo bassi? Le mie mani trovano paghe migliori."}
  {key:"#robber_no_jobs", text:"Niente lavoro onesto? Bene. Quello disonesto rende."}
  {key:"#robber_no_food_in_city", text:"Granai vuoti? L'oro riempie ancora le tasche."}
  {key:"#robber_city_have_no_army", text:"Nessun forte? Strade facili per un ladro silenzioso."}
  {key:"#robber_gods_are_angry", text:"Gli dèi sono adirati? Ottima copertura: la colpa è del cielo, non mia."}
  {key:"#robber_low_entertainment", text:"Niente festività? Rubare è il mio intrattenimento."}
  {key:"#robber_city_is_good", text:"Bella città. E belle borse da alleggerire."}
  {key:"#robber_city_is_amazing", text:"La miglior città da derubare, borse gonfie ovunque!"}
  {key:"#slave_break_our_chains", text:"Spezzate le catene! Basta padroni!"}
  {key:"#slave_tax_too_high", text:"A voi le tasse — a noi la frusta. Ribellatevi!"}
  {key:"#slave_wages_too_low", text:"Gli uomini liberi muoiono di fame con gli avanzi. Gli schiavi prendono ciò che serve!"}
  {key:"#slave_no_jobs", text:"Niente lavoro per gli uomini liberi? Allora gli uomini liberi si uniscono alla rivolta!"}
  {key:"#slave_no_food_in_city", text:"Granai vuoti mentre noi moriamo di fame in catene. Basta!"}
  {key:"#slave_city_have_no_army", text:"Nessun forte? Niente ci separa dal palazzo!"}
  {key:"#slave_gods_are_angry", text:"Persino gli dèi odiano questa città. Ribellatevi con noi!"}
  {key:"#slave_low_entertainment", text:"Niente festività per gli schiavi, solo la torcia!"}
  {key:"#slave_city_is_good", text:"Bella città, per chi è libero. Ora ci prendiamo la nostra parte!"}
  {key:"#slave_city_is_amazing", text:"Strade splendide da liberare — o da bruciare!"}
  {key:"#soldier_no_enemies_sighted", text:"Nessun nemico in vista. La guardia è tranquilla."}
  {key:"#soldier_ready_approaching_enemy", text:"Pronti! Nemico in avvicinamento: mantenete la formazione!"}
  {key:"#soldier_no_trouble_defeating_army", text:"Non avremo problemi a sconfiggere questo esercito."}
  {key:"#soldier_enemy_is_fierce", text:"Questo nemico è feroce. Tenete duro per il Faraone!"}
  {key:"#soldier_disease_risk", text:"Febbre tra i ranghi. Difficile marciare con le mani che tremano."}
  {key:"#soldier_no_food_in_city", text:"Granai vuoti? Un soldato affamato combatte male."}
  {key:"#soldier_gods_are_angry", text:"Gli dèi sembrano adirati. Cattivo presagio prima della battaglia."}
  {key:"#soldier_low_entertainment", text:"Nessuna festività da secoli. Anche i soldati hanno bisogno di un giorno libero dalla guardia."}
  {key:"#soldier_city_is_good", text:"Una città solida. Vale la pena difenderla."}
  {key:"#soldier_city_is_amazing", text:"La città migliore che abbia mai difeso. Per il Faraone!"}
  {key:"#tower_sentry_no_enemies_sighted", text:"Nessun nemico in vista. Le mura sono tranquille."}
  {key:"#tower_sentry_ready_approaching_enemy", text:"Pronti! Il nemico avanza: scoccate le frecce!"}
  {key:"#tower_sentry_no_trouble_defeating_army", text:"Dalla torre non avremo problemi a sconfiggere questo esercito."}
  {key:"#tower_sentry_enemy_is_fierce", text:"Questo nemico è feroce. Tenete le mura per il Faraone!"}
  {key:"#tower_sentry_disease_risk", text:"Febbre sulle mura. Difficile fare la guardia con le mani che tremano."}
  {key:"#tower_sentry_no_food_in_city", text:"Granai vuoti? Una sentinella affamata fa la guardia male."}
  {key:"#tower_sentry_gods_are_angry", text:"Gli dèi sembrano adirati. Cattivo presagio per la guardia."}
  {key:"#tower_sentry_low_entertainment", text:"Non si celebrano festività da secoli. Anche le sentinelle hanno bisogno di un giorno lontano dalle mura."}
  {key:"#tower_sentry_city_is_good", text:"Una città solida. Vale la pena vegliarla da questa torre."}
  {key:"#tower_sentry_city_is_amazing", text:"La città migliore che abbia sorvegliato. Per il Faraone!"}
  {key:"#stonemason_ready", text:"Pietra pronta. È ora di innalzare il monumento!"}
  {key:"#stonemason_going_to_work", text:"Al cantiere: quei blocchi non si posano da soli."}
  {key:"#stonemason_working_ground", text:"Poso la pietra su terreno solido. Piano, ora."}
  {key:"#stonemason_working_wall", text:"Un altro filare di pietra e il muro sale!"}
  {key:"#stonemason_work_complete", text:"Per ora il lavoro è finito. Torno alla gilda."}
  {key:"#stonemason_looking_for_work", text:"Cerco il prossimo posto dove posare la pietra."}
  {key:"#stonemason_disease_risk", text:"Febbre nel cantiere. Difficile sollevare pietre con le mani che tremano."}
  {key:"#stonemason_no_food_in_city", text:"Granai vuoti? Uno scalpellino affamato posa i blocchi storti."}
  {key:"#stonemason_city_have_no_army", text:"Nessun forte? Un'incursione e questo monumento sarà macerie."}
  {key:"#stonemason_gods_are_angry", text:"Gli dèi sembrano adirati. Anche la pietra buona si crepa sotto il loro sguardo."}
  {key:"#stonemason_low_entertainment", text:"Niente festività da secoli. Anche gli scalpellini hanno bisogno di un giorno lontano dalle impalcature."}
  {key:"#stonemason_city_is_good", text:"Questa città è solida! Buone fondamenta per grandi monumenti."}
  {key:"#stonemason_city_is_amazing", text:"La città migliore per cui abbia lavorato. Queste pietre dureranno per sempre!"}
  {key:"#reed_to_the_marsh_i_march", text:"In marcia verso la palude!"}
  {key:"#reed_will_make_some_fine_papyrus", text:"Da queste canne verrà un ottimo papiro."}
  {key:"#reed_disease_risk", text:"Febbre nelle paludi. Difficile tagliare le canne con le mani che tremano."}
  {key:"#reed_no_food_in_city", text:"Granai vuoti? Un raccoglitore di canne affamato taglia fasci storti."}
  {key:"#reed_city_have_no_army", text:"Nessun forte? Un'incursione e queste paludi saranno degli invasori."}
  {key:"#reed_gods_are_angry", text:"Gli dèi sembrano adirati. Perfino le canne migliori appassiscono sotto il loro sguardo."}
  {key:"#reed_low_entertainment", text:"Nessuna festività da secoli. Anche chi lavora nella palude ha bisogno di un giorno lontano dal fango."}
  {key:"#reed_city_is_good", text:"Questa città è solida! Buone canne per un papiro pregiato."}
  {key:"#reed_city_is_amazing", text:"La città migliore per cui abbia mai raccolto. Queste canne diventeranno rotoli per sempre!"}
  {key:"#noble_taking_a_stroll", text:"Una passeggiata tranquilla. Il popolino faccia largo."}
  {key:"#noble_returning_home", text:"Torno alla mia residenza. Queste strade polverose stancano una persona di rango."}
  {key:"#noble_disease_risk", text:"Febbre per le strade? Tenete la plebaglia lontana dal mio cortile."}
  {key:"#noble_no_food_in_city", text:"Granai vuoti? Un nobile non dovrebbe mai cenare a scuse."}
  {key:"#noble_city_have_no_army", text:"Nessun forte? Una scorreria e la mia tenuta è cenere. Inaccettabile."}
  {key:"#noble_gods_are_angry", text:"Gli dèi sembrano adirati. Nemmeno tela e oro possono corrompere il cielo."}
  {key:"#noble_low_entertainment", text:"Nessuna festività da secoli. Un nobile ha bisogno di musica, vino e spettacolo."}
  {key:"#noble_city_is_good", text:"Una città decorosa. I miei vicini sembrano quasi rispettabili."}
  {key:"#noble_city_is_amazing", text:"La città migliore per una villa! Persino il Faraone invidierebbe queste strade."}
  {key:"#figure_antelope_hunter", text:"Cacciatore di antilopi"}
  {key:"#figure_antelope_hunter_javelin", text:"Giavellotto del cacciatore"}
  {key:"#figure_birds_hunter", text:"Cacciatore di uccelli"}
  {key:"#mummy_risen", text:"Il sigillo è infranto. Torno a camminare."}
  {key:"#mummy_walks_streets", text:"Queste strade conosceranno la maledizione."}
  {key:"#mummy_attacking", text:"La carne è molle. Le bende ricordano come si colpisce."}
  {key:"#mummy_disease_risk", text:"La tua città puzza già di tomba. Mi sento a casa."}
  {key:"#mummy_no_food_in_city", text:"Granai vuoti? I vivi soffrono la fame; i morti resistono."}
  {key:"#mummy_city_have_no_army", text:"Nessun forte? Allora niente si frappone tra me e le tue case."}
  {key:"#mummy_need_workers", text:"Così pochi lavoratori... e così tante tombe ancora vuote."}
  {key:"#mummy_gods_are_angry", text:"Gli dèi voltano le spalle. Tempo perfetto per una maledizione."}
  {key:"#mummy_city_is_bad", text:"Il favore del Faraone svanisce. Le mie bende si stringono di gioia."}
  {key:"#mummy_much_unemployment", text:"Mani oziose? Anime oziose? Mi servono entrambe."}
  {key:"#mummy_low_entertainment", text:"Niente festività? Allora dovrà bastare la mia processione."}
  {key:"#mummy_city_is_good", text:"Una città in ordine. Peccato che debba ridursi in polvere."}
  {key:"#mummy_city_is_amazing", text:"Che gloria! Infesterò ogni splendida strada."}
  {key:"#figure_barbarian_archer", text:"Arciere barbaro nemico"}
  {key:"#figure_barbarian_sword", text:"Spadaccino barbaro nemico"}
  {key:"#figure_barbarian_transport_ship", text:"Nave da trasporto barbara nemica"}
  {key:"#figure_canaanite_archer", text:"Arciere cananeo nemico"}
  {key:"#figure_canaanite_sword", text:"Spadaccino cananeo nemico"}
  {key:"#figure_canaanite_transport_ship", text:"Nave da trasporto cananea nemica"}
  {key:"#figure_canaanite_war_ship", text:"Nave da guerra cananea nemica"}
  {key:"#figure_canaanite_chariot", text:"Carro cananeo nemico"}
  {key:"#figure_kushite_spearman", text:"Lanciere kushita nemico"}
  {key:"#figure_kushite_axeman", text:"Asciere kushita nemico"}
  {key:"#figure_kushite_transport_ship", text:"Nave da trasporto kushita nemica"}
  {key:"#figure_kushite_war_ship", text:"Nave da guerra kushita nemica"}
  {key:"#figure_kushite_chariot", text:"Carro kushita nemico"}
  {key:"#figure_hittite_archer", text:"Arciere ittita nemico"}
  {key:"#figure_hittite_spearman", text:"Lanciere ittita nemico"}
  {key:"#figure_hittite_transport_ship", text:"Nave da trasporto ittita nemica"}
  {key:"#figure_hittite_war_ship", text:"Nave da guerra ittita nemica"}
  {key:"#figure_hittite_chariot", text:"Carro ittita nemico"}
  {key:"#figure_persian_archer", text:"Arciere persiano nemico"}
  {key:"#figure_persian_spearman", text:"Lanciere persiano nemico"}
  {key:"#figure_persian_transport_ship", text:"Nave da trasporto persiana nemica"}
  {key:"#figure_persian_war_ship", text:"Nave da guerra persiana nemica"}
  {key:"#figure_persian_chariot", text:"Carro persiano nemico"}
  {key:"#figure_assyrian_archer", text:"Arciere assiro nemico"}
  {key:"#figure_assyrian_sword", text:"Spadaccino assiro nemico"}
  {key:"#figure_assyrian_transport_ship", text:"Nave da trasporto assira nemica"}
  {key:"#figure_assyrian_war_ship", text:"Nave da guerra assira nemica"}
  {key:"#figure_assyrian_chariot", text:"Carro assiro nemico"}
  {key:"#figure_egyptian_galera", text:"Galera egizia nemica"}
  {key:"#figure_libian_archer", text:"Arciere libico nemico"}
  {key:"#figure_libian_swordman", text:"Spadaccino libico nemico"}
  {key:"#figure_libian_transport_ship", text:"Nave da trasporto libica nemica"}
  {key:"#figure_libian_war_ship", text:"Nave da guerra libica nemica"}
  {key:"#figure_libian_chariot", text:"Carro libico nemico"}
  {key:"#figure_nubian_archer", text:"Arciere nubiano nemico"}
  {key:"#figure_nubian_axeman", text:"Guerriero nubiano con ascia nemico"}
  {key:"#figure_nubian_transport_ship", text:"Nave da trasporto nubiana nemica"}
  {key:"#figure_nubian_war_ship", text:"Nave da guerra nubiana nemica"}
  {key:"#figure_nubian_chariot", text:"Carro nubiano nemico"}
  {key:"#figure_phoenician_spearman", text:"Lanciere fenicio nemico"}
  {key:"#figure_phoenician_swordman", text:"Spadaccino fenicio nemico"}
  {key:"#figure_phoenician_transport_ship", text:"Nave da trasporto fenicia nemica"}
  {key:"#figure_phoenician_war_ship", text:"Nave da guerra fenicia nemica"}
  {key:"#figure_phoenician_chariot", text:"Carro fenicio nemico"}
  {key:"#figure_roman_archer", text:"Arciere romano nemico"}
  {key:"#figure_roman_legioner", text:"Legionario romano nemico"}
  {key:"#figure_roman_transport_ship", text:"Nave da trasporto romana nemica"}
  {key:"#figure_roman_war_ship", text:"Nave da guerra romana nemica"}
  {key:"#figure_roman_chariot", text:"Carro romano nemico"}
  {key:"#figure_seapeople_archer", text:"Arciere nemico dei Popoli del Mare"}
  {key:"#figure_seapeople_swordman", text:"Spadaccino nemico dei Popoli del Mare"}
  {key:"#figure_seapeople_transport_ship", text:"Nave da trasporto nemica dei Popoli del Mare"}
  {key:"#figure_seapeople_war_ship", text:"Nave da guerra nemica dei Popoli del Mare"}
  {key:"#figure_seapeople_chariot", text:"Carro nemico dei Popoli del Mare"}
  {key:"#figure_hyksos_archer", text:"Arciere hyksos nemico"}
  {key:"#figure_hyksos_swordman", text:"Spadaccino hyksos nemico"}
  {key:"#figure_hyksos_transport_ship", text:"Nave da trasporto hyksos nemica"}
  {key:"#figure_hyksos_war_ship", text:"Nave da guerra hyksos nemica"}
  {key:"#figure_hyksos_chariot", text:"Carro hyksos nemico"}
  {key:"#house_low_desirabilty", text:"Questa casa peggiorerà presto. La desiderabilità in calo di questa zona la sta trascinando in basso"}
  {key:"#lacks_access_primitive_water", text:"Questa casa peggiorerà presto, poiché non ha accesso nemmeno alla più primitiva fonte d'acqua."}
  {key:"#not_visited_by_water_carrier", text:"Questa casa peggiorerà presto, perché non viene visitata da un trasportatore d'acqua"}
  {key:"#no_entertainment_to_be_found", text:"Questa casa peggiorerà presto, poiché in questa zona non si trova alcun intrattenimento"}
  {key:"#any_entertainment_in_location", text:"Questa casa peggiorerà presto, perché nella zona non c'è quasi nessun intrattenimento"}
  {key:"#too_little_entertainment_in_location", text:"Questa casa peggiorerà presto, perché nella zona c'è troppo poco intrattenimento"}
  {key:"#some_entertainment_found_location", text:"Questa casa peggiorerà presto. Nei dintorni c'è un po' di intrattenimento, ma non basta"}
  {key:"#good_entertainment_found_location", text:"Questa casa peggiorerà presto. Nella zona c'è un buon intrattenimento, ma non abbastanza varietà"}
  {key:"#excellent_entertainment_found_location", text:"Questa casa peggiorerà presto. Nella zona c'è un intrattenimento eccellente, ma i locali sono troppo affollati o manca la varietà che pretendono le esigenti classi degli scribi"}
  {key:"#one_food_type_need", text:"Questa casa peggiorerà presto, poiché di recente non ha ricevuto alcuna scorta di cibo da un bazar locale"}
  {key:"#two_food_types_need", text:"Questa casa peggiorerà presto, perché al momento ha accesso a un solo tipo di cibo dal bazar locale. Questo scoraggia i cittadini più ricchi."}
  {key:"#three_food_types_need", text:"Questa casa peggiorerà presto, poiché al momento riceve solo due tipi di cibo dal Bazar locale. Questo scoraggia la classe degli scribi."}
  {key:"#no_bazaar_access", text:"Questa casa peggiorerà presto. Ha perso l'accesso a un bazar."}
  {key:"#low_bazaar_access", text:"Questa casa peggiorerà presto. Pur avendo accesso a un Bazar, il Bazar stesso fatica a rifornirsi di cibo."}
  {key:"#lost_basic_educational_facilities ", text:"Questa casa peggiorerà presto, perché ha perso ogni istruzione di base fornita da una Scuola degli scribi o da una Biblioteca."}
  {key:"#lost_access_to_library ", text:"Questa casa peggiorerà presto. Il suo accesso all'istruzione è peggiorato, perché ha perso l'accesso alla Biblioteca."}
  {key:"#lost_access_to_scribal_school ", text:"Questa casa peggiorerà presto. Il suo accesso all'istruzione è peggiorato, perché ha perso l'accesso alla scuola degli scribi."}
  {key:"#lost_access_to_higher_education ", text:"Questa casa peggiorerà presto. Il suo accesso all'istruzione, prima eccellente, è peggiorato con la perdita dell'accesso all'istruzione superiore."}
  {key:"#no_access_to_magistrates", text:"Questa casa peggiorerà presto, perché non ha accesso ai magistrati dei palazzi di giustizia."}
  {key:"#run_out_of_pottery", text:"Questa casa peggiorerà presto. Ha esaurito il vasellame e il Bazar locale ne ha, nella migliore delle ipotesi, una fornitura irregolare."}
  {key:"#lost_all_access_to_local_religious", text:"Questa casa peggiorerà presto, perché ha perso ogni accesso alle strutture religiose locali."}
  {key:"#access_to_one_local_religious", text:"Questa casa peggiorerà presto. Il suo accesso alle strutture religiose locali si è ridotto al Tempio di un solo dio."}
  {key:"#access_to_two_local_religious", text:"Questa casa peggiorerà presto. Le sue strutture religiose, un tempo eccellenti, si sono ridotte ai Templi di due soli dei."}
  {key:"#lost_dentist_access", text:"Questa casa peggiorerà presto, perché ha perso l'accesso al dentista."}
  {key:"#no_access_to_physician", text:"Questa casa peggiorerà presto, perché ora i servizi sanitari sono pessimi. Non solo le manca l'accesso a un imbalsamatore, ma anche l'accesso al medico non è perfetto."}
  {key:"#no_access_to_mortuary", text:"Questa casa peggiorerà presto, poiché i servizi sanitari sono venuti meno. La copertura del medico è buona, ma non c'è accesso a una camera mortuaria nelle vicinanze."}
  {key:"#hard_access_to_physician", text:"Questa casa peggiorerà presto, perché i servizi sanitari sono venuti a mancare. C'è accesso a una camera mortuaria, ma è difficile trovare un ambulatorio del medico."}
  {key:"#run_out_of_linen", text:"Questa casa peggiorerà presto, poiché ha esaurito la tela e il Bazar locale ne ha, nella migliore delle ipotesi, una fornitura irregolare."}
  {key:"#run_out_of_beer", text:"Questa casa peggiorerà presto, perché ha finito la birra e il bazar locale ne ha al più una fornitura irregolare."}
  {key:"#cannot_evolve_cause_low_desirability", text:"Questa abitazione non può migliorare finché non aumenta la desiderabilità della zona."}
  {key:"#cannot_evolve_most_primitive_water_source", text:"Questa casa non può migliorare, perché non ha accesso nemmeno alla più primitiva fonte d'acqua."}
  {key:"#cannot_evolve_access_to_water_carrier", text:"Questa casa non può migliorare, perché non ha accesso ai servizi di un trasportatore d'acqua "}
  {key:"#cannot_evolve_no_entertainment", text:"Questa casa non può migliorare, perché nella zona non c'è alcun intrattenimento."}
  {key:"#cannot_evolve_hardly_any_entertainment", text:"Questa casa non può migliorare, poiché nella zona non si trova quasi alcun intrattenimento."}
  {key:"#cannot_evolve_too_little_entertainment", text:"Questa casa non può migliorare, perché nella zona si trova troppo poco intrattenimento."}
  {key:"#cannot_evolve_some_entertainment", text:"Questa casa non può migliorare, poiché in questa zona c'è dell'intrattenimento, ma non a sufficienza."}
  {key:"#cannot_evolve_good_entertainment", text:"Questa casa non può migliorare, perché nella zona c'è un buon intrattenimento, ma non abbastanza varietà."}
  {key:"#cannot_evolve_excellent_entertainment", text:"Questa casa non può migliorare: nella zona si trova un intrattenimento eccellente, ma i locali sono troppo affollati o poco vari per gli esigenti ceti degli scribi."}
  {key:"#cannot_evolve_needs_supply_food", text:"Questa casa non può migliorare, perché ha bisogno di cibo da un Bazar locale."}
  {key:"#cannot_evolve_needs_second_type_food", text:"Questa casa non può migliorare, perché le serve un secondo tipo di cibo, fornito da un Bazar locale, per attirare Egizi più ricchi."}
  {key:"#cannot_evolve_needs_third_type_food", text:"Questa casa non può migliorare, perché ha bisogno di un terzo tipo di cibo, fornito da un bazar vicino, per attirare una classe più elevata di egizi."}
  {key:"#cannot_evolve_needs_access_bazaar", text:"Questa casa non può migliorare, poiché non ha accesso a un bazar locale."}
  {key:"#cannot_evolve_needs_low_access_bazaar", text:"Questa casa non può migliorare. Pur avendo accesso a un bazar locale, il bazar stesso fatica a rifornirsi di cibo."}
  {key:"#cannot_evolve_needs_basic_education", text:"Questa casa non può migliorare, poiché non dispone dell'istruzione di base fornita da una Scuola degli scribi o da una Biblioteca."}
  {key:"#cannot_evolve_needs_library_education", text:"Questa casa non può migliorare, perché il suo accesso all'istruzione va migliorato con l'accesso a una biblioteca."}
  {key:"#cannot_evolve_needs_school_education", text:"Questa casa non può migliorare: il suo accesso all'istruzione deve essere migliorato con una Scuola degli scribi."}
  {key:"#cannot_evolve_needs_academy_education", text:"riga inutilizzata: segnala l'evoluzione bloccata dalla mancanza di accesso all'Accademia."}
  {key:"#cannot_evolve_needs_magistrate", text:"Questa casa non può migliorare, perché non ha accesso a un magistrato di un Palazzo di giustizia."}
  {key:"#cannot_evolve_needs_pottery", text:"Questa casa non può migliorare. Ha bisogno di forniture di vasellame dal bazar vicino, prima che vi si trasferisca una classe più ricca di cittadini."}
  {key:"#cannot_evolve_needs_religious", text:"Questa casa non può migliorare, poiché non ha accesso ad alcuna struttura religiosa locale."}
  {key:"#cannot_evolve_needs_religious_two_gods", text:"Questa casa ha accesso ai templi di un solo dio. Non migliorerà finché i residenti non potranno rendere omaggio ad altre divinità."}
  {key:"#cannot_evolve_needs_religious_three_gods", text:"Questa casa ha accesso ai Templi di soli due dèi. Non migliorerà finché i residenti non potranno rendere omaggio ad altri dèi."}
  {key:"#cannot_evolve_needs_dentist", text:"Questa casa non può migliorare, perché non ha accesso locale a un dentista."}
  {key:"#cannot_evolve_needs_physician", text:"Questa casa non può migliorare: di fatto non ha alcuna assistenza sanitaria. Non ha accesso né a un Medico né a una Camera mortuaria."}
  {key:"#cannot_evolve_needs_mortuary_has_physician", text:"Questa casa non può migliorare, perché richiede più assistenza sanitaria. La copertura del Medico è buona, ma manca l'accesso a una Camera mortuaria."}
  {key:"#cannot_evolve_needs_physician_mortuary_has", text:"Questa casa non può migliorare, perché vuole più assistenza sanitaria. C'è accesso a una Camera mortuaria, ma serve l'accesso a un Medico."}
  {key:"#cannot_evolve_needs_linen", text:"Questa casa non può migliorare. Ha bisogno di forniture di tela dal bazar vicino, prima che vi si trasferisca una classe più ricca di cittadini."}
  {key:"#cannot_evolve_needs_beer", text:"Questa casa non può migliorare. Ha bisogno che il bazar locale le fornisca birra prima che vi si trasferisca una classe di cittadini più ricca."}
  {key:"#cannot_evolve_needs_jewlery", text:"Questa casa non può migliorare. Prima che vi si trasferisca una classe di cittadini più ricca, il bazar locale deve rifornire l'abitazione di beni di lusso, come"}
  {key:"#trader_from", text:"da"}
  {key:"#trader_capacity", text:"Capacità"}
  {key:"#trader_buys", text:"Acquisti"}
  {key:"#trader_sells", text:"Vende"}
  {key:"#trader_bought", text:"Acquistato"}
  {key:"#trader_sold", text:"Venduto"}
  {key:"#trader_returning_home", text:"Di ritorno a casa."}
  {key:"#trader_trading_goods", text:"Commercio"}
  {key:"#trader_heading_storage", text:"Verso i Depositi merci della città"}
  {key:"#trader_nothing_to_trage", text:"Niente da commerciare qui, sono solo di passaggio"}
  {key:"#trader_ship_waiting_free_dock", text:"All'ancora, in attesa di un Molo libero"}
  {key:"#trader_ship_docking_trading", text:"Attraccata, compra e vende merci"}
  {key:"#trader_ship_returning_home", text:"Di ritorno a casa"}
  {key:"#trader_ship_sailing_dock", text:"In direzione degli approdi cittadini."}
  {key:"#building_employee", text:"Impiegato"}
  {key:"#building_employee_needed", text:"richiesto"}
  {key:"#AD", text:"d.C."}
  {key:"#BC", text:"a.C."}
  {key:"#trader_city_not_trades", text:"Il nostro lungo e pericoloso viaggio fin qui è stato inutile! Questa città non commercia."}
  {key:"#trader_buy_for_less_sell_for_more", text:"Compra a poco, vendi a molto.  È il mio motto!"}
  {key:"#trader_its_my_life", text:"La vita del mercante fa per me!"}
  {key:"#trader_i_ll_be_a_hero", text:"Sarò un eroe quando porterò queste merci nella mia terra natale."}
  {key:"#trader_you_talk_a_fine_bargain", text:"Sai contrattare bene, amico mio.  A malapena rientrerò nei costi."}
  {key:"#donkey_cicero_breathe", text:"Finché respiro, spero. Anche mentre trasporto vasellame."}
  {key:"#donkey_cicero_books", text:"Una stanza senza libri è come un corpo senz'anima. Una carovana senza grano è peggio."}
  {key:"#donkey_cicero_garden", text:"Se hai un giardino e una biblioteca, hai tutto ciò che ti serve. Io ho una sella. Ci siamo quasi."}
  {key:"#donkey_cicero_gratitude", text:"La gratitudine è la madre di tutte le virtù. Anche una carota aiuterebbe."}
  {key:"#donkey_cicero_friendship", text:"L'amicizia accresce la felicità e allevia la sventura. E anche camminare più lenti del mercante in testa."}
  {key:"#donkey_cicero_money", text:"Niente è così saldo che il denaro non possa distruggerlo. Chiedi alle mie piaghe da basto."}
  {key:"#donkey_cicero_memory", text:"La vita dei morti è riposta nella memoria dei vivi. Io ricordo ancora quell'oasi."}
  {key:"#donkey_cicero_moderation", text:"Mai eccedere: la moderazione sia la tua guida. Soprattutto col peso del carico."}
  {key:"#donkey_cicero_mistakes", text:"Chiunque può sbagliare, ma solo uno sciocco persevera nell'errore. Ho sbagliato strada una volta. Una."}
  {key:"#donkey_cicero_history", text:"Ignorare ciò che è accaduto prima della tua nascita significa restare per sempre un bambino. O un asino. Aspetta."}
  {key:"#donkey_cicero_laws", text:"Le leggi tacciono in tempo di guerra. Gli asini no. I-oh."}
  {key:"#donkey_cicero_not_alone", text:"Non siamo nati solo per noi stessi. Evidentemente. Io sono nato per questa soma."}
  {key:"#donkey_cicero_meta", text:"Mi chiamano bestia da soma, eppure cito Cicerone. Chi è il filosofo adesso?"}
  {key:"#donkey_cicero_runaway", text:"Fuggo, dunque sono. Cicerone capirebbe. Forse."}
  {key:"#flotsam_plato_unexamined", text:"Una vita senza ricerca non è degna di essere vissuta. È una corrente senza ricerca che mi ha portato qui."}
  {key:"#flotsam_plato_cave", text:"I prigionieri nella caverna vedono solo ombre. Io vedo la riva — a testa in giù."}
  {key:"#flotsam_plato_wise", text:"I saggi parlano perché hanno qualcosa da dire. Il legno alla deriva si limita a galleggiare."}
  {key:"#flotsam_plato_courage", text:"Il coraggio è sapere ciò che non si deve temere. Io non temo il Nilo. Io sono del Nilo."}
  {key:"#flotsam_plato_knowledge", text:"Il sapere imposto con la forza non attecchisce. E a quanto pare nemmeno il carico."}
  {key:"#flotsam_plato_opinion", text:"L'opinione sta a metà tra il sapere e l'ignoranza. Io sto a metà tra la nave e la riva."}
  {key:"#flotsam_plato_love", text:"Al tocco dell'amore ognuno diventa poeta. Al tocco di uno scoglio ognuno diventa relitto."}
  {key:"#flotsam_plato_justice", text:"La giustizia risiede prima di tutto nel cuore dei cittadini. E poi: il sughero aiuta."}
  {key:"#flotsam_plato_music", text:"La musica dà un'anima all'universo. Il Nilo mi dà una destinazione che non ho scelto."}
  {key:"#flotsam_plato_ignorance", text:"L'ignoranza è la radice di ogni male. E anche il calafataggio scadente."}
  {key:"#flotsam_plato_excess", text:"L'eccesso produce un cambiamento in direzione opposta. Chiedilo a questo barile."}
  {key:"#flotsam_plato_war", text:"Solo i morti hanno visto la fine della guerra. Noi altri abbiamo visto la fine dello scafo."}
  {key:"#flotsam_plato_meta", text:"Mi chiamano relitto. Io cito Platone. Chi è il filosofo adesso?"}
  {key:"#frog_joke_ribbit", text:"Cra cra. Tutto qui. No, aspetta: anche la tua casa adesso è mia."}
  {key:"#frog_joke_plague", text:"La chiamano piaga. Io la chiamo riunione di famiglia."}
  {key:"#frog_joke_pad", text:"Avevo chiesto una foglia di ninfea. Mi hanno dato un mattone di fango. Ci siamo quasi."}
  {key:"#frog_joke_pharaoh", text:"Il Faraone dice di saltare al lavoro. La battuta si ritorce su di lui: io salto già."}
  {key:"#frog_joke_flies", text:"Cosa ordinano le rane al bazar? Tutto ciò che gli ronza intorno."}
  {key:"#frog_joke_happy", text:"Perché le rane sono così felici? Si mangiano i loro assilli. Due volte."}
  {key:"#frog_joke_croak", text:"Sono venuto qui per gracidare e masticare mosche. E le mosche sono finite."}
  {key:"#frog_joke_swarm", text:"Una rana è carina. Dieci sono un'assemblea. Venti sono una legge."}
  {key:"#frog_joke_happiness", text:"La felicità della città è appena calata. Non c'è di che."}
  {key:"#frog_joke_nile", text:"Il Nilo si alza. Anch'io. Di solito sulla tua soglia."}
  {key:"#frog_joke_amphibious", text:"Anfibio significa terra e acqua. La tua dispensa vale per entrambe."}
  {key:"#frog_joke_meta", text:"Sono un presagio biblico con la battuta pronta. Cra cra."}
  {key:"#TR_CONFIG_HEADER_LANGUAGES", text:"Lingua del gioco"}
  {key:"#hunter_ostrich_good_city", text:"Qui mi trovo bene, ma c'è sempre margine di miglioramento."}
  {key:"#immigrant_im_new_here", text:"Sono nuovo qui.  Chissà cosa offrirà la città a una persona come me."}
  {key:"#immigrant_heard_there_is_a_job_here", text:"Ho sentito che qui c'è lavoro per chiunque ne voglia."}
  {key:"#immigrant_city_has_plenty_of_food", text:"Dicono che in questa città ci sia cibo in abbondanza per tutti."}
  {key:"#immigrant_disease_risk", text:"Malattia per le strade? Speravo che questa città fosse più sana."}
  {key:"#immigrant_city_have_no_army", text:"Nessun forte? Credevo di essermi lasciato il pericolo alle spalle."}
  {key:"#immigrant_need_workers", text:"Quante officine vuote. Meglio così: significa lavoro per me."}
  {key:"#immigrant_gods_are_angry", text:"Persino gli dèi sembrano inquieti. Cattivo presagio per un nuovo arrivato."}
  {key:"#immigrant_city_is_bad", text:"Il favore del Faraone sembra scarso. Ho sbagliato città?"}
  {key:"#immigrant_much_unemployment", text:"Folle di gente in ozio. Ci sarà ancora posto per me?"}
  {key:"#immigrant_low_entertainment", text:"Niente festività da secoli. Un'accoglienza fiacca per i nuovi arrivati."}
  {key:"#immigrant_city_is_good", text:"Sembra un buon posto per ricominciare!"}
  {key:"#immigrant_city_is_amazing", text:"Che città! Sono contento di aver fatto il viaggio."}
  {key:"#emigrant_no_job_in_city", text:"Qui non trovo lavoro. Cercherò altrove."}
  {key:"#emigrant_no_food_in_city", text:"Non c'è abbastanza cibo per me. Me ne vado da questo deserto!"}
  {key:"#emigrant_tax_too_high", text:"Le tasse qui sono troppo alte. Mi stupisce che non me ne abbiano fatta pagare una per andarmene."}
  {key:"#emigrant_salary_too_low", text:"Non posso vivere con quello che mi pagano qui."}
  {key:"#emigrant_no_house_for_me", text:"Le case che ho visto sono stipate di gente. Non posso restare qui senza un posto in cui vivere."}
  {key:"#emigrant_disease_risk", text:"Questo posto puzza di malattia. Non resto ad aspettare la peste."}
  {key:"#emigrant_city_have_no_army", text:"Nessun forte? Una scorreria e di noi non resterebbe nulla. Io me ne vado."}
  {key:"#emigrant_need_workers", text:"Invocano lavoratori, eppure per me non c'è lavoro. È ora di andare."}
  {key:"#emigrant_gods_are_angry", text:"Gli dèi sembrano furiosi. Preferisco pregare in un posto più sicuro."}
  {key:"#emigrant_city_is_bad", text:"Il nome di questa città è nel fango. Non voglio essere sepolto con la sua reputazione."}
  {key:"#emigrant_low_entertainment", text:"Nessuna festività da un'eternità. Perfino la strada che porta fuori città è più allegra."}
  {key:"#emigrant_city_is_good", text:"Città abbastanza gradevole, ma per qualcun altro. Il mio carro è già carico."}
  {key:"#emigrant_city_is_amazing", text:"Città straordinaria, dicono. Non abbastanza per trattenermi."}
  {key:"#recruiter_disease_in_city", text:"Vedo malati dappertutto. Potrebbe scoppiare una peste!"}
  {key:"#recruiter_no_food_in_city", text:"Sto morendo di fame. Preferirei cercare cibo invece che lavoratori. "}
  {key:"#recruiter_city_not_safety", text:"Le difese cittadine sono così deboli che presto coprirò i posti con stranieri invece che con egizi."}
  {key:"#recruiter_need_workers", text:"Senza lavoratori disponibili, il mio compito è impossibile."}
  {key:"#recruiter_gods_are_angry", text:"Spero che gli dei non scatenino la loro ira. Dobbiamo prestare loro più attenzione."}
  {key:"#recruiter_enemies_attack", text:"I nemici potrebbero attaccare da un momento all'altro. La nostra reputazione è bassa e nessuno ci rispetta."}
  {key:"#recruiter_i_looking_for_the_workers", text:"Con tanta gente in gamba senza lavoro, il mio compito dovrebbe essere facile."}
  {key:"#recruiter_boring", text:"Che noia qui. Vorrei poter assumere più artisti."}
  {key:"#recruiter_living_here", text:"Non mi dispiace vivere qui. Le cose potrebbero certamente andare peggio."}
  {key:"#recruiter_city_is_amazing", text:"Questa città è la migliore!"}
  {key:"#recruiter_i_want_to_leave_city", text:"Sono la persona più richiesta della città. Tanta gente cerca lavoro."}
  {key:"#recruiter_much_unemployments", text:"La mia lista di posti vacanti è enorme e non trovo lavoratori per occuparli."}
  {key:"#recruiter_no_jobs", text:"Niente lavoro per loro, niente lavoratori per me. Qui qualcosa non funziona."}
  {key:"#recruiter_no_some_workers", text:"Sto ancora cercando qualche lavoratore per coprire i posti."}
  {key:"#recruiter_need_more_workers", text:"Servono molti più lavoratori. La mia lista continua ad allungarsi."}
  {key:"#barge_have_no_place_for_dock", text:"Chissà se questa città ha qualcosa da vedere mentre scaricano la mia nave."}
  {key:"#barge_docked_wait_for_dockpushers", text:"Aspettiamo che il carico venga portato alla nostra nave."}
  {key:"#barge_city_not_trades", text:"Non so perché siamo venuti. Questa città non commercia mai, e la sosta a terra è noiosa."}
  {key:"#barge_i_like_to_trage", text:"Adoro l'arte della trattativa! Non vedo l'ora di scambiare le mie merci."}
  {key:"#barge_amazing_trades", text:"Che viaggio fruttuoso!"}
  {key:"#dancer_i_like_festivals", text:"Molte persone si sono ammalate in città. Spero di non prendermi nulla!"}
  {key:"#dancer_desease_can_start_at_any_moment", text:"Non riesco a saltare e volteggiare bene senza cibo a sufficienza!"}
  {key:"#dancer_no_food_in_city", text:"Gli invasori conquisterebbero la nostra città senza fatica. Nessuno la difende."}
  {key:"#dancer_city_not_safety_workers_leaving", text:"Un'altra compagna di danza persa per la carenza di lavoratori! Odio danzare da sola."}
  {key:"#dancer_need_workers", text:"Dovremmo fare di più per placare gli dèi, e in fretta!"}
  {key:"#dancer_gods_are_angry", text:"La reputazione di questa città è peggiore di quella di un giocoliere! Spero che non ci attacchino."}
  {key:"#dancer_city_is_bad", text:"Se non fossi così leggera nei passi, inciamperei in tutti questi disoccupati!"}
  {key:"#dancer_much_unemployments", text:"(Sbadiglio) Ho bisogno di essere intrattenuta!"}
  {key:"#dancer_salary_too_low", text:"Questa città vale più o meno quanto qualsiasi altra, immagino."}
  {key:"#dancer_city_is_good", text:"Questa città è fantastica!"}
  {key:"#dancer_city_is_amazing", text:"La folla delle festività è così entusiasta che mi viene voglia di saltare più in alto."}
  {key:"#homeless_i_was_kicked_out_of_my_home", text:"Sono stato cacciato di casa, e non per colpa mia."}
  {key:"#homeless_i_cant_find_a_place_to_live", text:"Non riesco a trovare un posto dove vivere!"}
  {key:"#homeless_no_job_in_city", text:"Niente lavoro e niente tetto. Questa città non ha nulla per me."}
  {key:"#homeless_no_food_in_city", text:"Muoio di fame e non ho un tetto. Non posso restare qui."}
  {key:"#homeless_tax_too_high", text:"Le tasse mi hanno portato via la casa. Ora vogliono quel che resta della mia dignità."}
  {key:"#homeless_salary_too_low", text:"Le paghe qui non bastano nemmeno per un angolo dove dormire."}
  {key:"#homeless_found_new_house", text:"Una casa con posto libero! Forse la fortuna sta girando."}
  {key:"#homeless_no_house_for_me", text:"Non c'è più posto per me in questa città. Me ne vado."}
  {key:"#homeless_need_workers", text:"Servono lavoratori, eppure io dormo per strada. Dov'è la logica?"}
  {key:"#homeless_city_is_bad", text:"Il favore del Faraone è cenere. Non c'è da stupirsi se ho perso la casa."}
  {key:"#homeless_gods_are_angry", text:"Gli dèi sono adirati. Prima ne soffrono i templi, poi la gente come me."}
  {key:"#homeless_city_bad_reputation", text:"La reputazione di questa città è vuota quanto il mio giaciglio."}
  {key:"#homeless_city_is_good", text:"La città sembra andare bene per gli altri. A me basterebbe una porta che si apra."}
  {key:"#buyer_goto_store", text:"Vado al granaio e al deposito merci. Auguratemi gambe forti!"}
  {key:"#buyer_back_to_market", text:"Si torna al bazar a pieno carico. Non attardatevi, ragazzi!"}
  {key:"#buyer_city_has_low_health", text:"La gente è malata, eppure pretende ancora cibo fresco in tavola."}
  {key:"#buyer_no_food_in_city", text:"Granai vuoti! Come faccio a riempire questi cesti?"}
  {key:"#buyer_city_have_no_army", text:"Nessun forte? I predoni potrebbero rubare ogni cesto sulla strada."}
  {key:"#buyer_much_unemployments", text:"Tante mani inoperose, eppure nessuno mi aiuta a trasportare le merci."}
  {key:"#buyer_gods_are_angry", text:"Gli dèi sembrano adirati. Nemmeno il bazar può trattare con loro."}
  {key:"#buyer_city_is_bad_reputation", text:"La reputazione di questa città è così bassa che i mercanti non rischiano qui i loro carri."}
  {key:"#buyer_too_much_unemployments", text:"La disoccupazione è alta. La gente affamata è un pessimo cliente."}
  {key:"#buyer_low_entertainment", text:"Nessuna festività da un'eternità. Un po' di musica renderebbe più brevi questi viaggi."}
  {key:"#buyer_city_is_good", text:"Questa città va bene: strade corte e scaffali pieni."}
  {key:"#buyer_city_is_amazing", text:"La città migliore per un cliente del bazar! Tutto ciò che mi serve è dietro l'angolo."}
  {key:"#marketboy_these_baskets_are_too_heavy", text:"Questi cesti sono troppo pesanti per un ragazzino come me!"}
  {key:"#marketboy_bossy_lady_makes_me_carry_goods", text:"Quella donna autoritaria mi fa portare merci tutto il giorno!"}
  {key:"#marketboy_one_day_ill_run_the_bazaar", text:"Ora porto solo ceste, ma un giorno gestirò il bazar."}
  {key:"#marketboy_runaway", text:"Mi ha lasciato indietro! E va bene: questi cesti me li porto a casa da solo."}
  {key:"#marketboy_disease_risk", text:"Tossiscono tutti. Posso posare i cesti e lavarmi le mani?"}
  {key:"#marketboy_no_food_in_city", text:"Granai vuoti? E allora perché trasporto cibo per tutta la città?"}
  {key:"#marketboy_city_have_no_army", text:"Nessun forte? Se arrivano i predoni, i primi a sparire saranno i miei cesti!"}
  {key:"#marketboy_need_workers", text:"Il bazar ha bisogno di più braccia. Le mie sono già cariche!"}
  {key:"#marketboy_gods_are_angry", text:"Gli dèi sembrano adirati. Forse non gradiscono nemmeno la frutta ammaccata."}
  {key:"#marketboy_city_is_bad", text:"Questa città è ostile. Perfino i cani abbaiano ai miei cesti."}
  {key:"#marketboy_much_unemployment", text:"Quanta gente in ozio — e nessuno che si offra di dare una mano!"}
  {key:"#marketboy_low_entertainment", text:"Nessuna festività da secoli. Almeno una parata renderebbe più corto questo giro."}
  {key:"#marketboy_city_is_good", text:"Questa città va bene. Strade corte e un acquirente che conosce la strada."}
  {key:"#marketboy_city_is_amazing", text:"La città migliore per correre con le ceste! Un giorno il banco sarà mio."}
  {key:"#engineer_extreme_damage_level", text:"Molte persone sono messe molto peggio delle costruzioni. Spero che non peggiori ancora."}
  {key:"#engineer_i_am_works", text:"Questi muri non crolleranno finché ci sono io."}
  {key:"#engineer_no_food_in_city", text:"La fame non intacca la solidità di questi edifici, ma di certo intacca la mia!"}
  {key:"#engineer_city_not_safety", text:"Come possiamo difenderci? Le difese della città sono ridicole."}
  {key:"#engineer_high_damage_level", text:"Che importa se questi edifici crollano? Tanto non ci lavora nessuno."}
  {key:"#engineer_gods_are_angry", text:"Se gli dèi sono adirati, nemmeno il miglior architetto può riparare i danni che causano."}
  {key:"#engineer_city_has_bad_reputation", text:"La reputazione della nostra città è così bassa che temo l'attacco dei nemici."}
  {key:"#engineer_need_more_workers", text:"Secondo i miei calcoli, molta gente è senza lavoro."}
  {key:"#engineer_low_entertainment", text:"Che noia. Anche gli architetti vogliono un po' di svago ogni tanto."}
  {key:"#engineer_city_is_bad", text:"Si potrebbe vivere molto peggio di così."}
  {key:"#engineer_life_here_could_be_worse", text:"La vita qui potrebbe andare molto peggio."}
  {key:"#engineer_city_is_good", text:"Questa città ha tutto ciò che il cuore di un architetto possa desiderare!"}
  {key:"#engineer_so_many_places_in_poor_condition", text:"Ci sono così tanti edifici in cattive condizioni che non riesco a stare dietro a tutto."}
  {key:"#engineer_city_is_amazing", text:"Spero che mi venga riconosciuto il merito per l'ottimo stato di questa città."}
  {key:"#brick_bricklaying_time_at_monument", text:"È ora di posare mattoni al monumento!"}
  {key:"#brick_monument_will_be_strong", text:"Questo monumento sarà solido!"}
  {key:"#brick_waiting_for_bricks", text:"Aspetto ancora quei mattoni. Contadini, sbrigatevi!"}
  {key:"#brick_looking_for_spot", text:"Cerco il prossimo tratto di muro da innalzare."}
  {key:"#brick_work_statue", text:"Un po' di malta e questa statua tornerà a essere fiera."}
  {key:"#brick_return_to_guild", text:"Torno alla gilda. Le mie braccia hanno bisogno di riposo."}
  {key:"#brick_leaving_site", text:"Niente altro da fare qui — lascio il cantiere."}
  {key:"#brick_disease_risk", text:"Questo posto puzza di malattia. È difficile posare mattoni con le mani che tremano."}
  {key:"#brick_no_food_in_city", text:"Granai vuoti? Un muratore affamato tira su muri storti."}
  {key:"#brick_city_have_no_army", text:"Nessun forte? Una sola incursione e questo monumento sarà macerie prima di essere finito."}
  {key:"#brick_gods_are_angry", text:"Gli dèi sembrano adirati. Persino i mattoni di fango si crepano sotto il loro sguardo."}
  {key:"#brick_low_entertainment", text:"Niente festività da secoli. Anche i muratori hanno bisogno di un giorno lontano dall'impalcatura."}
  {key:"#brick_city_is_good", text:"Questa città è solida! Buone fondamenta per grandi monumenti."}
  {key:"#brick_city_is_amazing", text:"La città migliore per cui abbia costruito. Queste mura dureranno per sempre!"}
  {key:"#carpenter_work_my_tools_need_for_monument", text:"I miei attrezzi servono al monumento!"}
  {key:"#carpenter_this_monument_will_be_short", text:"Questo monumento non richiederà molto: il legname è pronto."}
  {key:"#carpenter_work_wall", text:"Prima l'impalcatura. Poi il vero lavoro comincia lassù."}
  {key:"#carpenter_looking_for_spot", text:"Cerco la prossima trave da mettere in posa."}
  {key:"#carpenter_return_to_guild", text:"Torno alla gilda. Di nuovo segatura tra i capelli."}
  {key:"#carpenter_work_garden", text:"Un po' di falegnameria e questo giardino sarà come si deve."}
  {key:"#carpenter_disease_risk", text:"Questo posto sa di malattia. Difficile tenere lo scalpello con le mani che tremano."}
  {key:"#carpenter_no_food_in_city", text:"Granai vuoti? Un carpentiere affamato taglia il legname storto."}
  {key:"#carpenter_city_have_no_army", text:"Nessun forte? Un'incursione e questa impalcatura è legna da ardere."}
  {key:"#carpenter_gods_are_angry", text:"Gli dèi sembrano adirati. Persino il buon cedro si deforma sotto il loro sguardo."}
  {key:"#carpenter_low_entertainment", text:"Non si celebrano festività da secoli. Anche i carpentieri hanno bisogno di un giorno lontano dall'impalcatura."}
  {key:"#carpenter_city_is_good", text:"Questa città è solida! Un buon lavoro di carpenteria merita buone fondamenta."}
  {key:"#carpenter_city_is_amazing", text:"La città migliore per cui abbia lavorato. Queste travi dureranno per sempre!"}
  {key:"#fireman_desease_can_start_at_any_moment", text:"Spero che non scoppi una pestilenza. Le pestilenze si diffondono come il fuoco."}
  {key:"#fireman_no_food_in_city", text:"Anche quando divampano gli incendi, riesco solo a pensare a quanta fame ho."}
  {key:"#fireman_city_not_safety_workers_leaving", text:"Se i nemici invadono, l'intera città potrebbe andare a fuoco."}
  {key:"#fireman_need_workers", text:"Temo che qualcuno di questi edifici mezzi vuoti possa prendere fuoco. Vorrei ci fossero più lavoratori."}
  {key:"#fireman_gods_are_angry", text:"L'ira infuocata degli dèi si abbatterà su di noi se non mostriamo più rispetto."}
  {key:"#fireman_hight_fire_level", text:"Non mi sognerei mai di far scendere così in basso la mia reputazione. La cattiva reputazione della nostra città invita all'attacco."}
  {key:"#fireman_need_more_workers", text:"Si sono presentati altri volontari per i pompieri. Questa gente ha bisogno di lavoro."}
  {key:"#fireman_low_entertainment", text:"Spegnere gli incendi è un lavoro duro e mi piacerebbe rinfrescarmi con un bello spettacolo.  Qui non ce n'è abbastanza."}
  {key:"#fireman_gods_are_pleasures", text:"Sono soddisfatto di questa città."}
  {key:"#fireman_city_is_amazing", text:"Questa città non scotta affatto."}
  {key:"#fireman_fighting_fire", text:"Non posso parlare adesso.  Sono impegnato a spegnere questo incendio."}
  {key:"#fireman_going_to_fire", text:"Questo incendio può bruciare l'intera città se non agisco in fretta!"}
  {key:"#fireman_fighting_fire_also", text:"Ooh, come scotta!"}
  {key:"#cartpusher_have_no_place_for_goods", text:"Non porto oltre queste merci finché non c'è qualcuno che le scarichi."}
  {key:"#cartpusher_i_have_time_for_rest", text:"Nessuno può accettare queste merci! Fa niente, un po' di riposo mi ci vuole."}
  {key:"#cartpusher_road_too_long", text:"Devo attraversare tutta la città con queste merci. Ci vorrà un giorno intero!"}
  {key:"#cartpusher_i_have_no_destination", text:"Stiamo facendo più del nostro dovere.  Ci serve più aiuto."}
  {key:"#cartpusher_back_to_home", text:"Aspetto qui finché non si libera dello spazio per questa roba."}
  {key:"#cartpusher_delivering_items", text:"Sono arrivato?  Non posso trasportare queste merci ancora per molto."}
  {key:"#cartpusher_disease_risk", text:"Questo posto puzza di malattia. Difficile spingere un carro con la febbre addosso."}
  {key:"#cartpusher_no_food_in_city", text:"Granai vuoti? Allora per cosa sto trasportando tutto questo?"}
  {key:"#cartpusher_city_have_no_army", text:"Nessun forte? Basta un'incursione e il mio carro è bottino di guerra."}
  {key:"#cartpusher_gods_are_angry", text:"Gli dèi sembrano adirati. Persino le ruote cigolano come un presagio."}
  {key:"#cartpusher_low_entertainment", text:"Niente festività da un'eternità. Anche la schiena di un carrettiere ha bisogno di riposo."}
  {key:"#cartpusher_city_is_good", text:"Questa città è solida! Strade brevi e depositi pieni."}
  {key:"#cartpusher_city_is_amazing", text:"La miglior città per cui abbia trasportato. Questi carichi quasi si spingono da soli!"}
  {key:"#docker_need_more_help", text:"Stiamo facendo più della nostra parte di lavoro. Ci serve più aiuto."}
  {key:"#docker_wait_until_space_opens_up", text:"Aspetto qui finché non si libera un po' di spazio per questa roba."}
  {key:"#docker_cant_haul_goods_much_farther", text:"Sono arrivato? Non riesco a trascinare queste merci ancora per molto."}
  {key:"#docker_disease_risk", text:"Questo molo puzza di malattia. Difficile trasportare il carico con quest'aria malsana."}
  {key:"#docker_no_food_in_city", text:"Granai vuoti? Le navi arrivano affamate, e anche noi."}
  {key:"#docker_city_have_no_army", text:"Nessun forte? Basta un'incursione e questo porto diventa bottino."}
  {key:"#docker_gods_are_angry", text:"Gli dèi sembrano adirati. Persino il fiume tira dalla parte sbagliata."}
  {key:"#docker_low_entertainment", text:"Niente festività da secoli. Anche i portuali hanno bisogno di una licenza."}
  {key:"#docker_city_is_good", text:"Questo porto funziona a meraviglia! Trasporti brevi e depositi pieni."}
  {key:"#docker_city_is_amazing", text:"Il porto migliore in cui abbia lavorato. Queste casse sbarcano quasi da sole!"}
  {key:"#enemy_chariot_attacking", text:"Avanti! Schiacciateli sotto le ruote!"}
  {key:"#enemy_chariot_marching", text:"La polvere delle nostre ruote soffocherà questa città."}
  {key:"#enemy_chariot_waiting", text:"Tenete la linea. La carica è vicina."}
  {key:"#enemy_chariot_leaving", text:"Ritirata! Vivremo per cavalcare ancora."}
  {key:"#enemy_chariot_city_will_fall", text:"Le vostre mura non fermeranno i carri."}
  {key:"#enemy_chariot_no_match", text:"La fanteria non è all'altezza!"}
  {key:"#enemy_chariot_for_glory", text:"Per la gloria e il bottino!"}
  {key:"#enemy_archer_shooting", text:"Scoccate! Riempite il cielo di frecce!"}
  {key:"#enemy_archer_marching", text:"Archi pronti. Le loro strade si tingeranno di rosso."}
  {key:"#enemy_archer_waiting", text:"Fermi. Tendete gli archi al segnale."}
  {key:"#enemy_archer_leaving", text:"Ritirata! Faremo piovere morte un altro giorno."}
  {key:"#enemy_archer_city_will_fall", text:"Questa città cadrà sotto le nostre frecce."}
  {key:"#enemy_archer_arrows_ready", text:"Archi pronti! Nessuno scamperà."}
  {key:"#enemy_archer_for_glory", text:"Per la gloria — e un tiro pulito!"}
  {key:"#enemy_sword_attacking", text:"Acciaio e sangue! Abbatteteli!"}
  {key:"#enemy_sword_marching", text:"Avanti. La loro città brucerà prima di sera."}
  {key:"#enemy_sword_waiting", text:"Fermi. Al segnale, colpiamo."}
  {key:"#enemy_sword_leaving", text:"Ritirata! Torneremo con più lame."}
  {key:"#enemy_sword_no_army", text:"Nessun forte? Questa città è già nostra."}
  {key:"#enemy_sword_no_food", text:"Stanno morendo di fame. Prede deboli, bottino facile."}
  {key:"#enemy_sword_disease", text:"Le loro strade puzzano di malattia. Ancora più facile."}
  {key:"#enemy_sword_need_workers", text:"Non riescono nemmeno a far funzionare le officine. Patetici."}
  {key:"#enemy_sword_gods_angry", text:"I loro dèi hanno voltato le spalle. Lo faremo anche noi, dopo aver preso l'oro."}
  {key:"#enemy_sword_city_is_bad", text:"Il favore del Faraone è cenere. Nessuno piangerà questo posto."}
  {key:"#enemy_sword_low_entertainment", text:"Niente festività, niente spirito. Cederanno alla prima carica."}
  {key:"#enemy_sword_city_is_good", text:"Una città ordinata. Peccato che siamo qui per distruggerla."}
  {key:"#enemy_sword_city_is_amazing", text:"Così prospera. Il bottino sarà magnifico."}
  {key:"#enemy_sword_for_glory", text:"Per la gloria e per la spada!"}
  {key:"#enemy_spearman_shooting", text:"Lanciate! Che le lance trovino il bersaglio!"}
  {key:"#enemy_spearman_marching", text:"Avanzate. Le nostre lance diraderanno le loro file."}
  {key:"#enemy_spearman_waiting", text:"Fermi. Preparate il prossimo lancio."}
  {key:"#enemy_spearman_leaving", text:"Ritirata! Teniamo le lance per un altro giorno."}
  {key:"#enemy_spearman_city_will_fall", text:"Questa città cadrà sotto le nostre lance."}
  {key:"#enemy_spearman_spears_ready", text:"Lance pronte! Nessuno resisterà."}
  {key:"#enemy_spearman_for_glory", text:"Per la gloria e per la lancia!"}
  {key:"#enemy_transport_created", text:"Mollate gli ormeggi! La loro costa è nostra."}
  {key:"#enemy_transport_sailing", text:"Tenete saldi i remi. Presto toccheremo terra."}
  {key:"#enemy_transport_disembarking", text:"A riva! Svuotate la stiva del suo acciaio!"}
  {key:"#enemy_transport_idle", text:"Scafo in attesa. Truppe pronte per lo sbarco."}
  {key:"#enemy_transport_no_army", text:"Nessuna loro nave da guerra? Queste acque sono nostre."}
  {key:"#enemy_transport_no_food", text:"Una città affamata. Il nostro sbarco sarà facile."}
  {key:"#enemy_transport_disease", text:"Malattia sui loro moli. A terra c'è preda facile."}
  {key:"#enemy_transport_need_workers", text:"Non riescono nemmeno a presidiare i moli. Porto penoso."}
  {key:"#enemy_transport_gods_angry", text:"I loro dèi li abbandonano. La marea è dalla nostra parte."}
  {key:"#enemy_transport_city_is_bad", text:"Il favore del Faraone è cenere. Nessuna flotta li salverà."}
  {key:"#enemy_transport_low_entertainment", text:"Niente festività, niente spirito. Cederanno già sulla spiaggia."}
  {key:"#enemy_transport_city_is_good", text:"Un bel porto. Peccato che siamo qui per prenderlo."}
  {key:"#enemy_transport_city_is_amazing", text:"Banchine ricche. Il bottino riempirà le nostre stive."}
  {key:"#enemy_transport_for_glory", text:"Per la gloria — e per una testa di ponte!"}
  {key:"#enemy_warship_created", text:"Issate le vele! Il loro porto è nostro."}
  {key:"#enemy_warship_idle", text:"Mantieni posizione. Occhio alla loro flotta."}
  {key:"#enemy_warship_pursuing", text:"Inseguiteli! Nessuna nave sfugge."}
  {key:"#enemy_warship_attacking", text:"Fuoco! Speronateli e affondateli!"}
  {key:"#enemy_warship_no_army", text:"Nessun forte sulla costa? I loro moli sono indifesi."}
  {key:"#enemy_warship_no_food", text:"Stanno morendo di fame. Ci attende un bottino facile."}
  {key:"#enemy_warship_disease", text:"Peste nella loro città. Preda facile."}
  {key:"#enemy_warship_need_workers", text:"Mancanza di manodopera. Le loro mura crolleranno."}
  {key:"#enemy_warship_gods_angry", text:"Persino i loro dèi hanno voltato le spalle."}
  {key:"#enemy_warship_city_is_bad", text:"Una città debole. Perfetta per un'incursione."}
  {key:"#enemy_warship_low_entertainment", text:"Nessuna festività. Il morale è già a pezzi."}
  {key:"#enemy_warship_city_is_good", text:"Approdi ricchi. Carichi preziosi in vista."}
  {key:"#enemy_warship_city_is_amazing", text:"Quanta prosperità. Il bottino sarà magnifico."}
  {key:"#enemy_warship_for_glory", text:"Per la gloria e per il mare!"}
  {key:"#ferry_boat_ready", text:"Pronto all'approdo. Chi attraversa?"}
  {key:"#ferry_boat_going", text:"Si molla! Prossima riva in vista."}
  {key:"#ferry_boat_at_destination", text:"Siamo arrivati. Scendete con attenzione sul molo."}
  {key:"#ferry_boat_returning", text:"Si torna indietro. State lontani dalla corrente."}
  {key:"#ferry_boat_waiting", text:"In attesa di una destinazione sull'altra sponda."}
  {key:"#ferry_boat_disease_risk", text:"Questa traversata sa di malattia. Difficile spingere con la pertica in un'aria così viziata."}
  {key:"#ferry_boat_no_food_in_city", text:"Granai vuoti? I passeggeri affamati vogliono comunque attraversare."}
  {key:"#ferry_boat_city_have_no_army", text:"Nessun forte? Un'incursione e questo traghetto diventa bottino."}
  {key:"#ferry_boat_gods_are_angry", text:"Gli dèi sembrano adirati. Perfino la corrente tira dalla parte sbagliata."}
  {key:"#ferry_boat_low_entertainment", text:"Nessuna festività da secoli. Anche i traghettatori hanno diritto a una licenza a terra."}
  {key:"#ferry_boat_city_is_good", text:"Questa traversata fila liscia! Viaggi brevi e approdi pieni."}
  {key:"#ferry_boat_city_is_amazing", text:"Il miglior traghetto su cui abbia lavorato. Questi approdi ti salutano quasi!"}
  {key:"#governor_city_left_much_nobles", text:"Troppi nobili stanno lasciando questa città!"}
  {key:"#governor_festival_was_near", text:"Ah, che festività splendida! Nelle strade se ne sente ancora il calore."}
  {key:"#governor_disease_risk", text:"Malattia per le strade. La città di un governatore non dovrebbe puzzare di febbre."}
  {key:"#governor_no_food_in_city", text:"Granai vuoti? I nobili non restano dove scarseggia il pane."}
  {key:"#governor_city_have_no_army", text:"Nessun forte? Una scorreria e questo palazzo è bottino."}
  {key:"#governor_gods_are_angry", text:"Gli dèi sembrano adirati. Perfino a corte si sussurra di cattivi presagi."}
  {key:"#governor_low_entertainment", text:"Nessuna festività da secoli. Anche i governatori hanno bisogno di svago."}
  {key:"#governor_city_is_good", text:"Una città solida! Ordine nelle strade e monete nelle casse."}
  {key:"#governor_city_is_amazing", text:"La città più bella che abbia mai governato. Il Faraone stesso ne andrebbe fiero!"}
  {key:"#fishing_boat_ready", text:"Barca pronta all'approdo. L'equipaggio aspetta la marea."}
  {key:"#fishing_boat_going_to_fish", text:"In navigazione verso i banchi di pesca."}
  {key:"#fishing_boat_fishing", text:"Si tira su il pesce. Tenete ferme le reti!"}
  {key:"#fishing_boat_going_to_wharf", text:"Torno al molo con le stive vuote."}
  {key:"#fishing_boat_at_wharf", text:"Ormeggiati alla banchina. Ci riforniamo per un altro viaggio."}
  {key:"#fishing_boat_returning_with_fish", text:"Si rientra con una pesca abbondante!"}
  {key:"#fishing_boat_looking_for_spot", text:"Cerco un posto per pescare. Queste acque sono insidiose."}
  {key:"#fishing_boat_disease_risk", text:"Il porto puzza di malattia. Difficile pescare con l'equipaggio debole."}
  {key:"#fishing_boat_no_food_in_city", text:"Granai cittadini vuoti? Meglio così: vorranno il nostro pescato."}
  {key:"#fishing_boat_city_have_no_army", text:"Nessun forte? I predoni potrebbero prendersi ogni barca su questa riva."}
  {key:"#fishing_boat_need_workers", text:"I moli hanno bisogno di braccia. Una barca da sola non sfama la città."}
  {key:"#fishing_boat_gods_are_angry", text:"Gli dèi sono adirati. Perfino i pesci evitano le nostre reti."}
  {key:"#fishing_boat_city_is_bad", text:"Il favore del Faraone è cenere. Nessuna flotta piangerà questo posto."}
  {key:"#fishing_boat_much_unemployment", text:"Gente in ozio a terra, e ancora equipaggi insufficienti per le barche."}
  {key:"#fishing_boat_low_entertainment", text:"Non si celebrano festività da secoli. Anche i pescatori hanno bisogno di una licenza a terra."}
  {key:"#fishing_boat_city_is_good", text:"Acque buone e un molo affollato. Non è un cattivo posto."}
  {key:"#fishing_boat_city_is_amazing", text:"La pesca migliore che io conosca. Le reti si riempiono prima di mezzogiorno!"}
  {key:"#funeral_walker_ready", text:"La processione è pronta. Camminiamo per i defunti onorati."}
  {key:"#funeral_walker_going_to_tomb", text:"Alla tomba. Tenete libera la strada e ferme le lampade."}
  {key:"#funeral_walker_arrived", text:"Siamo arrivati. Che la tomba li accolga in pace."}
  {key:"#funeral_walker_lost_path", text:"La strada ci ha traditi. Dobbiamo riprovare il cammino."}
  {key:"#funeral_walker_disease_risk", text:"La malattia cammina per le strade. Persino un funerale sembra affollato."}
  {key:"#funeral_walker_no_food_in_city", text:"Granai vuoti, e noi continuiamo a seppellire. I vivi si fanno magri."}
  {key:"#funeral_walker_city_have_no_army", text:"Nessun forte? I predoni potrebbero profanare ogni tomba di cui ci prendiamo cura."}
  {key:"#funeral_walker_need_workers", text:"Troppe poche braccia. Le processioni aspettano e i monumenti restano incompiuti."}
  {key:"#funeral_walker_gods_are_angry", text:"Gli dèi sono adirati. Quale sepoltura potrà placarli ora?"}
  {key:"#funeral_walker_city_is_bad", text:"Il favore del Faraone è cenere. Persino le tombe sembrano abbandonate."}
  {key:"#funeral_walker_much_unemployment", text:"Gente inoperosa a riva, eppure in pochi percorreranno la via funebre."}
  {key:"#funeral_walker_low_entertainment", text:"Nessuna festività da secoli. Il lutto riempie ogni piazza."}
  {key:"#funeral_walker_city_is_good", text:"Una bella città per i vivi, e un degno riposo per i morti."}
  {key:"#funeral_walker_city_is_amazing", text:"Che splendore! Persino le tombe brillano d'onore."}
  {key:"#malaria_problem", text:"(Non usato)"}
  {key:"#malaria_not_a_problem", text:"Qui la malaria non sembra essere un problema."}
  {key:"#malaria_outbreak_could_strike", text:"Un'epidemia di malaria potrebbe scoppiare se non si fa qualcosa."}
  {key:"#herbalist_no_food_in_city", text:"Granai vuoti? Difficile curare quando la città muore di fame."}
  {key:"#herbalist_city_have_no_army", text:"Nessun forte? Una scorreria e le mie erbe sono cenere."}
  {key:"#herbalist_gods_are_angry", text:"Gli dèi sembrano adirati. Perfino i buoni rimedi falliscono sotto il loro sguardo."}
  {key:"#herbalist_low_entertainment", text:"Nessuna festività da secoli. Anche gli erboristi hanno bisogno di un giorno senza giro."}
  {key:"#herbalist_city_is_good", text:"Questa città è abbastanza sana! Percorsi brevi e case robuste."}
  {key:"#herbalist_city_is_amazing", text:"La città migliore che abbia mai curato. Queste strade guariscono quasi da sole!"}
  {key:"#policeman_desease_can_start_at_any_moment", text:"Con tanta gente così debole e malaticcia, temo per il futuro."}
  {key:"#policeman_no_food_in_city", text:"Non mangio da così tanto che persino io sto pensando di rubare del cibo!"}
  {key:"#policeman_city_not_safety", text:"Se arrivano gli invasori, pare che toccherà a me difendere la città."}
  {key:"#policeman_need_workers", text:"Se non mi piacesse il pericolo del lavoro di guardia, prenderei subito uno dei tanti impieghi disponibili."}
  {key:"#policeman_gods_are_angry", text:"Se comandassi io, presterei più attenzione agli dèi."}
  {key:"#policeman_no_army", text:"Ho sentito che la nostra città è una preda facile per gli invasori. Abbiamo una cattiva reputazione."}
  {key:"#policeman_much_unemployments", text:"Non mi piace vedere tanti disoccupati a bighellonare. Non riesco a fare il giro senza inciamparci!"}
  {key:"#policeman_low_entertainment", text:"Questa città è noiosa. Non trovo un solo spettacolo decente da vedere."}
  {key:"#policeman_city_is_good", text:"Questa città non è perfetta, ma quale città lo è?"}
  {key:"#policeman_city_is_amazing", text:"Non mi sono mai sentito così sicuro in ronda. Questa città è straordinaria!"}
  {key:"#policeman_very_low_crime_level", text:"Se solo il bazar vendesse ciambelle, questa città sarebbe perfetta."}
  {key:"#policeman_low_crime_level", text:"Qui sono tutti cordiali. Nessuno denuncia crimini."}
  {key:"#policeman_usual_crime_level", text:"Qualche crimine qua, qualche crimine là, ma niente fuori dall'ordinario."}
  {key:"#policeman_need_more_workers", text:"Nemmeno a me piace passare in questa parte della città!"}
  {key:"#policeman_iam_too_busy_that_talk", text:"Ho davvero troppo da fare per parlare adesso - chiedimelo di nuovo più tardi."}
  {key:"#policeman_i_hope_my_work_is_need", text:"Farò la mia parte perché questa città sia sicura!"}
  {key:"#policeman_no_army_2", text:"Combattere gli invasori non era tra i miei compiti!"}
  {key:"#policeman_enemies_are_coming_2", text:"Questi furfanti non prenderanno la città finché ci sono io!"}
  {key:"#policeman_enemies_are_coming", text:"Il nemico potrebbe presto vincere, se non ricevo aiuto! "}
  {key:"#hunter_ostrich_investigate", text:"Tracce nella sabbia... un struzzo è passato di recente."}
  {key:"#hunter_ostrich_chase", text:"Eccolo! Le zampe sono veloci, ma le mie frecce di più."}
  {key:"#hunter_ostrich_hunting", text:"Gli struzzi sono quasi invisibili quando nascondono la testa nella sabbia."}
  {key:"#hunter_ostrich_back", text:"Queste sì che sono cosce GROSSE!"}
  {key:"#hunter_ostrich_reroute_packed", text:"Carico pesante, strada sbagliata. Troverò un altro ritorno."}
  {key:"#hunter_ostrich_look_packed", text:"Mi serve un sentiero libero verso la capanna con questo uccello sulla schiena."}
  {key:"#hunter_ostrich_unloading", text:"Selvaggina fresca per la capanna. Profuma già meglio dell'orzo."}
  {key:"#hunter_ostrich_disease_risk", text:"Qui odora di malattia. Brutto tempo per cacciare."}
  {key:"#hunter_ostrich_no_food_in_city", text:"Granai vuoti? Allora è meglio riportare un grande uccello."}
  {key:"#hunter_ostrich_city_have_no_army", text:"Niente forti? Un'incursione di coccodrilli e questa città è la cena."}
  {key:"#hunter_ostrich_need_workers", text:"Servono più braccia. Non posso riempire ogni pentola da solo."}
  {key:"#hunter_ostrich_gods_are_angry", text:"Gli dei sembrano arrabbiati. Persino gli struzzi lo sentono."}
  {key:"#hunter_ostrich_city_is_bad", text:"Il faraone non è contento di noi. Non finisce mai bene."}
  {key:"#hunter_ostrich_much_unemployment", text:"Troppa gente oziosa. Almeno la caccia nutre ancora qualcuno."}
  {key:"#hunter_ostrich_low_entertainment", text:"Niente feste da un pezzo. Un banchetto di struzzo rallegrerebbe tutti."}
  {key:"#hunter_ostrich_city_is_good", text:"Questa città è fantastica!"}
  {key:"#hunter_ostrich_city_is_amazing", text:"La migliore città per cui abbia cacciato. Che resti così!"}
  {key:"#hunter_antelope_investigate", text:"Impronte di zoccoli nella polvere... di qui è passata un'antilope."}
  {key:"#hunter_antelope_chase", text:"Eccola che salta! Veloce come il vento, ma il mio giavellotto è più veloce."}
  {key:"#hunter_antelope_hunting", text:"Le antilopi non sono all'altezza di noi! Quelle corna non le salveranno."}
  {key:"#hunter_antelope_back", text:"Stasera ci sarà carne per tutti."}
  {key:"#hunter_antelope_reroute_packed", text:"Carcassa pesante, sentiero sbagliato. Troverò un'altra via per il casotto."}
  {key:"#hunter_antelope_look_packed", text:"Con questa antilope sulle spalle mi serve una strada libera per tornare."}
  {key:"#hunter_antelope_unloading", text:"Antilope fresca per la capanna. I cuochi saranno contenti."}
  {key:"#hunter_antelope_disease_risk", text:"Questo posto sa di malattia. Persino le mandrie stanno alla larga."}
  {key:"#hunter_antelope_no_food_in_city", text:"Granai vuoti? Allora è meglio che riporti indietro un'antilope grassa."}
  {key:"#hunter_antelope_city_have_no_army", text:"Nessun forte? Un'incursione e questa città è spacciata come una gazzella in trappola."}
  {key:"#hunter_antelope_need_workers", text:"Servono più braccia. Non posso riempire ogni pentola di selvaggina da solo."}
  {key:"#hunter_antelope_gods_are_angry", text:"Gli dei sembrano adirati. Anche le mandrie sono inquiete."}
  {key:"#hunter_antelope_city_is_bad", text:"Il Faraone non è contento di noi. Non finisce mai bene."}
  {key:"#hunter_antelope_much_unemployment", text:"Troppa gente in ozio. Almeno la caccia sfama ancora qualcuno."}
  {key:"#hunter_antelope_low_entertainment", text:"Niente festività da secoli. Un banchetto di antilope tirerebbe su tutti."}
  {key:"#hunter_antelope_city_is_good", text:"Questa città è buona! Ottime terre di caccia qui vicino."}
  {key:"#hunter_antelope_city_is_amazing", text:"La città migliore per cui abbia cacciato. Le antilopi saltano praticamente da sole nella pentola!"}
  {key:"#hunter_birds_investigate", text:"Piume tra le canne... qui si nutriva uno stormo."}
  {key:"#hunter_birds_chase", text:"Eccoli in volo! Le mie frecce ne faranno cadere qualcuno."}
  {key:"#hunter_birds_hunting", text:"Questi uccelli sono furbi!"}
  {key:"#hunter_birds_back", text:"Questi uccelli sono pronti per essere arrostiti!"}
  {key:"#hunter_birds_reroute_packed", text:"Una rete pesante di uccelli e la strada sbagliata. Troverò un'altra via per tornare."}
  {key:"#hunter_birds_look_packed", text:"Con questa preda mi serve un sentiero libero fino alla capanna."}
  {key:"#hunter_birds_unloading", text:"Selvaggina fresca per il capanno. I cuochi avranno da fare."}
  {key:"#hunter_birds_disease_risk", text:"Questo posto sa di malattia. Perfino gli uccelli stanno alla larga."}
  {key:"#hunter_birds_no_food_in_city", text:"Granai vuoti? Allora è meglio che torni con una sacca piena di uccelli."}
  {key:"#hunter_birds_city_have_no_army", text:"Nessun forte? Una sola incursione e questa città sarà indifesa come un uccello a terra."}
  {key:"#hunter_birds_gods_are_angry", text:"Gli dei sembrano adirati. Anche gli stormi sono inquieti."}
  {key:"#hunter_birds_low_entertainment", text:"Nessuna festività da un'eternità. Un banchetto di uccelli arrosto tirerebbe su tutti."}
  {key:"#hunter_birds_city_is_good", text:"Questa città è buona! Qui vicino ci sono belle paludi per la caccia agli uccelli."}
  {key:"#hunter_birds_city_is_amazing", text:"La città migliore per cui abbia cacciato. Gli uccelli volano quasi da soli nella pentola!"}
  {key:"#lumberjack_hunting", text:"Vado per una dura giornata di taglio."}
  {key:"#lumberjack_back", text:"Questo legname verrà messo a buon uso, ne sono certo."}
  {key:"#lumberjack_disease_risk", text:"Febbre in città. Difficile menare l'ascia con le mani che tremano."}
  {key:"#lumberjack_no_food_in_city", text:"Granai vuoti? Un taglialegna affamato taglia legname storto."}
  {key:"#lumberjack_city_have_no_army", text:"Nessun forte? Basta un'incursione e questi alberi diventano legna da ardere per gli invasori."}
  {key:"#lumberjack_gods_are_angry", text:"Gli dèi sembrano adirati. Perfino il buon cedro si deforma sotto il loro sguardo."}
  {key:"#lumberjack_low_entertainment", text:"Niente festività da un'eternità. Anche i boscaioli hanno bisogno di un giorno lontano dagli alberi."}
  {key:"#lumberjack_city_is_good", text:"Questa città è solida! Il buon legname merita buone fondamenta."}
  {key:"#lumberjack_city_is_amazing", text:"La miglior città per cui abbia tagliato legna. Queste travi dureranno per sempre!"}
  {key:"#musician_i_like_festivals", text:"Che folla meravigliosa a queste festività! Cantano tutti insieme."}
  {key:"#musician_city_heath_too_low", text:"Se la salute non migliora in questa città, suonerò solo canti funebri."}
  {key:"#musician_no_food_in_city", text:"Canterei per la cena, ma questa città non ha cibo a sufficienza."}
  {key:"#musician_city_not_safety_workers_leaving", text:"Forse potrei colpire gli invasori in testa col mio sistro.  La città non è ben difesa."}
  {key:"#musician_need_workers", text:"Tutte le mie esibizioni sono a solo.  Questa città non ha abbastanza lavoratori."}
  {key:"#musician_gods_are_angry", text:"Spero che la mia musica plachi gli dèi. La loro ira potrebbe presto abbattersi su di noi."}
  {key:"#musician_city_is_bad_reputation", text:"La nostra pessima reputazione potrebbe provocare un attacco!"}
  {key:"#musician_much_unemployments", text:"Per l'ultima volta, non assumo altri aiutanti! C'è così tanta gente in cerca di lavoro."}
  {key:"#musician_no_entertainment", text:"Anche un intrattenitore ama essere intrattenuto! Qui non c'è abbastanza da fare."}
  {key:"#musician_no_entertainment_need", text:"Anche un intrattenitore ama essere intrattenuto! Qui non c'è abbastanza da fare."}
  {key:"#musician_city_not_bad", text:"Questa città potrebbe andare molto peggio, immagino."}
  {key:"#musician_city_is_good", text:"Spero che continueremo a fare bella musica in questa città ancora a lungo."}
  {key:"#senet_i_like_festivals", text:"I giochi delle festività sono i migliori. Tutti vogliono una partita."}
  {key:"#taxman_desease_can_start_at_any_moment", text:"Sembra che una malattia stia mettendo a dura prova la salute della gente. Prego che non arrivi la peste."}
  {key:"#taxman_no_food_in_city", text:"Vorrei che la gente potesse pagare le tasse in cibo. Ho una fame!"}
  {key:"#taxman_city_have_no_army", text:"La nostra città non sembra in grado di difendersi!"}
  {key:"#taxman_need_more_tax_collectors", text:"Nessuna somma di tasse farà funzionare bene questa città. Servono più lavoratori!"}
  {key:"#taxman_gods_are_angry", text:"Abbiamo un grande debito con gli dèi, e non voglio essere qui quando verranno a riscuotere!"}
  {key:"#taxman_city_is_bad", text:"Ho sentito che un'invasione è imminente, vista la nostra posizione in Egitto."}
  {key:"#taxman_much_unemployments", text:"Molte di queste case hanno lavoratori disoccupati! Come possono pagare le tasse?"}
  {key:"#taxman_low_entertainment", text:"Per quanto mi piaccia riscuotere le tasse, vorrei anche vedere un po' di intrattenimento professionale."}
  {key:"#taxman_city_is_good", text:"Qui non si vive poi così male."}
  {key:"#taxman_city_is_amazing", text:"Preferirei vivere qui che in qualunque altro posto!"}
  {key:"#taxman_need_workers", text:"Questa città incasserebbe molto di più se solo assumesse qualche esattore in più."}
  {key:"#taxman_high_taxes", text:"Sembra che più belle sono le case, più la gente si lamenta di pagare la propria parte."}
  {key:"#taxman_much_pooh_houses", text:"Odio riscuotere le tasse da queste case malandate. Non vale il mio tempo."}
  {key:"#worker_desease_can_start_at_any_moment", text:"C'è tanta gente malata. Spero che le cose non peggiorino."}
  {key:"#worker_no_food_in_city", text:"Sono affamato. È dura lavorare a stomaco vuoto."}
  {key:"#worker_enemies_in_city", text:"Spero che i nostri nemici non sappiano quanto sarebbe facile invaderci."}
  {key:"#worker_need_workers", text:"Ci sono posti di lavoro ovunque! Forse posso trovarne uno come vigile del fuoco!"}
  {key:"#worker_gods_are_angry", text:"Spero che gli dèi non scatenino la loro ira.  "}
  {key:"#worker_city_is_bad", text:"Ho sentito che la nostra città non ha una buona reputazione. Potremmo essere attaccati!"}
  {key:"#worker_much_unemployments", text:"Mi terrò stretto questo lavoro. Conosco molte persone che sono senza impiego."}
  {key:"#worker_low_entertainment", text:"Non faccio altro che lavorare. In questa città non c'è nient'altro da fare."}
  {key:"#worker_city_is_good", text:"Mi trovo bene qui, ma c'è sempre spazio per migliorare."}
  {key:"#worker_city_is_amazing", text:"Spero di vivere qui per sempre!"}
  {key:"#worker_unused", text:"(non usato)"}
  {key:"#worker_going_to_workplace", text:"Sono pronto a lavorare!"}
  {key:"#worker_farm_is_flooded", text:"Con i campi sott'acqua, ora lavoro per la gloria eterna."}
  {key:"#doctor_concerned_about_plague", text:"Con una salute cittadina così misera, ho un gran daffare. Eppure la peste incombe."}
  {key:"#doctor_no_food_in_city", text:"Avere sempre fame non mi fa bene."}
  {key:"#doctor_defenses_are_weak", text:"Consiglierei a questa città di rafforzare le difese, così i nemici non ci faranno danni."}
  {key:"#doctor_need_more_workers", text:"Ho visto molti lavoratori spinti al limite. A questa città servirebbero più impiegati."}
  {key:"#doctor_gods_are_angry", text:"Non credo che stiamo portando abbastanza rispetto agli dei. È un comportamento terribilmente rischioso."}
  {key:"#doctor_reputation_is_low", text:"La nostra pessima reputazione invita gli altri ad attaccarci."}
  {key:"#doctor_unemployment_is_high", text:"Restare in ozio ad aspettare un lavoro fa male alla salute della nostra gente!"}
  {key:"#doctor_low_entertainment", text:"C'è gente che viene a farsi visitare solo perché non ha niente di meglio da fare!"}
  {key:"#doctor_city_is_ok", text:"Questa città è abbastanza buona, direi."}
  {key:"#doctor_city_is_the_best", text:"Non riesco a immaginare un posto più sano in cui vivere."}
  {key:"#doctor_plague_could_strike_us_dead", text:"La peste potrebbe stroncarci da un momento all'altro!"}
  {key:"#water_desease_can_start_at_any_moment", text:"Ho paura di entrare in certi quartieri. La gente è malata e non voglio prendermi niente."}
  {key:"#water_no_food_in_city", text:"Sono debole per la fame. Sto quasi crollando sotto il peso di tutta quest'acqua."}
  {key:"#water_city_have_no_army", text:"Sembra che toccherà ai cittadini difendere questa città, se venisse attaccata."}
  {key:"#water_need_workers", text:"Lavoro ovunque, e nemmeno un lavoratore per farlo."}
  {key:"#water_gods_are_angry", text:"Se fossi un dio, non sarei contento della poca attenzione che questa città mi riserva."}
  {key:"#water_city_is_bad", text:"Ho sentito che le altre città ridono di noi e progettano di invaderci."}
  {key:"#water_much_unemployments", text:"Vedo tanta gente senza lavoro mentre faccio le mie consegne."}
  {key:"#water_low_entertainment", text:"Trasportare acqua non è intrattenimento. Vorrei che qui ci fossero veri svaghi."}
  {key:"#water_city_is_good", text:"Mi piace vivere qui, ma se comandassi io in città farei alcune cose in modo diverso."}
  {key:"#water_city_is_amazing", text:"Non c'è posto migliore su questa terra."}
  {key:"#osiris_city_low_health", text:"La città è piena di malati. Spero non scoppi una pestilenza."}
  {key:"#osiris_no_food_in_city", text:"Nessun sacerdote di Osiride dovrebbe soffrire la fame!"}
  {key:"#osiris_city_not_safety", text:"La nostra città è quasi indifesa. Spero che nessuno ci attacchi."}
  {key:"#osiris_need_workers", text:"Senza lavoratori, potremmo non riuscire a tributare a Osiride il rispetto che merita."}
  {key:"#osiris_gods_are_angry", text:"Osiride non è l'unico dio che l'incuria fa adirare."}
  {key:"#osiris_low_sentiment", text:"La nostra città è lo zimbello dell'Egitto. Siamo pronti per essere attaccati."}
  {key:"#osiris_much_unemployments", text:"La disoccupazione è un problema serio in questa città. Spero che presto si aprano altri posti di lavoro."}
  {key:"#osiris_low_entertainment", text:"Anche un sacerdote ha bisogno di più che preghiere per divertirsi."}
  {key:"#osiris_city_is_good", text:"Questa città è accettabile."}
  {key:"#osiris_city_is_amazing", text:"Osiride è fiero di essere venerato in una città così bella."}
  {key:"#osiris_god_love_festival", text:"Le festività scaldano il cuore di Osiride."}
  {key:"#osiris_city_low_mood", text:"Osiride potrebbe punire la città per la sua negligenza con una piena scarsa."}
  {key:"#osiris_disease_in_city", text:"La malattia cammina per le strade. Osiride veglia sui vivi e sui morti."}
  {key:"#osiris_need_entertainment", text:"Un po' di musica solleverebbe le preghiere oltre che gli animi."}
  {key:"#ra_city_low_health", text:"Chi viene al Tempio non sembra in salute. Spero che la malattia non peggiori."}
  {key:"#ra_no_food_in_city", text:"Non ho cibo a sufficienza per nutrire Ra né me stesso!"}
  {key:"#ra_city_not_safety", text:"Vorrei che toccasse a Ra difendere la nostra città. Non credo che questa città lo faccia bene."}
  {key:"#ra_need_workers", text:"Spero che questa città trovi presto più lavoratori. I servizi potrebbero risentirne."}
  {key:"#ra_gods_are_angry", text:"Questa città farebbe bene a portare più rispetto agli dèi."}
  {key:"#ra_low_sentiment", text:"La reputazione è importante. Senza, la città è esposta a conquiste ostili."}
  {key:"#ra_much_unemployments", text:"Non ho mai sentito così tante persone chiedere a Ra se troveranno finalmente un lavoro."}
  {key:"#ra_low_entertainment", text:"Mi serve più intrattenimento. Compiacere Ra tutto il giorno non è facile, e ho bisogno di rilassarmi."}
  {key:"#ra_city_is_good", text:"Non ho lamentele di rilievo su questa città."}
  {key:"#ra_city_is_amazing", text:"L'unico posto migliore di questa città è il Campo dei Giunchi."}
  {key:"#ra_god_love_festival", text:"Ra ama vedere il suo popolo durante la festività."}
  {key:"#ra_city_low_mood", text:"La nostra città è una vergogna per il resto del Regno."}
  {key:"#ra_disease_in_city", text:"La malattia si diffonde sotto il sole di Ra. I templi devono intervenire."}
  {key:"#ra_need_entertainment", text:"Anche i sacerdoti di Ra hanno bisogno di svago dopo lunghe giornate di riti."}
  {key:"#ptah_city_low_health", text:"La cattiva salute potrebbe portare alla peste, se non si fa nulla per le condizioni della città."}
  {key:"#ptah_no_food_in_city", text:"I brontolii del mio stomaco vuoto mi distraggono dai miei doveri verso Ptah."}
  {key:"#ptah_city_not_safety", text:"Le nostre difese piene di falle saranno inutili se qualcuno decidesse di attaccarci."}
  {key:"#ptah_need_workers", text:"Rattrista Ptah vedere le industrie ferme per la mancanza di lavoratori."}
  {key:"#ptah_gods_are_angry", text:"Gli dèi potrebbero infliggere una giusta punizione, se la città continuerà a ignorarli."}
  {key:"#ptah_low_sentiment", text:"La nostra cattiva fama potrebbe incoraggiare gli invasori."}
  {key:"#ptah_much_unemployments", text:"Ptah vorrebbe che tutti i disoccupati della città trovassero un lavoro produttivo."}
  {key:"#ptah_low_entertainment", text:"Anche a me piace divertirmi, come a tutti. Vorrei che ci fossero più intrattenitori in questa città."}
  {key:"#ptah_city_is_good", text:"Questa città ha i suoi problemi, ma è un buon posto in cui vivere."}
  {key:"#ptah_city_is_amazing", text:"Questa è la città meglio costruita di tutto l'Egitto!"}
  {key:"#ptah_god_love_festival", text:"Ptah sa che le festività rendono più felici i lavoratori."}
  {key:"#ptah_city_low_mood", text:"La mano di Ptah può fare solo fino a un certo punto. Le industrie di questa città hanno bisogno di più lavoratori!"}
  {key:"#ptah_disease_in_city", text:"La pestilenza minaccia le botteghe. Ptah non può forgiare salute dall'incuria."}
  {key:"#ptah_need_entertainment", text:"Artigiani e sacerdoti hanno bisogno di più che lavoro e preghiera."}
  {key:"#seth_city_low_health", text:"Una pestilenza potrebbe devastare la città se la salute non migliora."}
  {key:"#seth_no_food_in_city", text:"Tutto il giorno combatto contro la fame. Mi serve più cibo."}
  {key:"#seth_city_not_safety", text:"Dovremo affidarci a Seth per proteggerci in battaglia. La città non è preparata a difendersi."}
  {key:"#seth_need_workers", text:"I servizi sono in sofferenza perché non si trovano lavoratori!"}
  {key:"#seth_gods_are_angry", text:"Questa città dovrebbe smettere di provocare l'ira degli dèi con la sua inerzia."}
  {key:"#seth_low_sentiment", text:"Presto scopriremo quanto poco gli altri stimino la nostra città, quando piomberanno qui a distruggerla."}
  {key:"#seth_much_unemployments", text:"Le legioni dei disoccupati intasano le strade."}
  {key:"#seth_low_entertainment", text:"È incredibile quanto ci si annoi qui!"}
  {key:"#seth_city_is_good", text:"Questa città mi si addice abbastanza."}
  {key:"#seth_city_is_amazing", text:"Questa città non ha rivali in tutto l'Egitto!"}
  {key:"#seth_god_love_festival", text:"Anche i guerrieri di Seth hanno bisogno di qualche festività."}
  {key:"#seth_city_low_mood", text:"La gloria è all'orizzonte! I nemici si avvicinano rapidamente alla città."}
  {key:"#seth_disease_in_city", text:"La malattia indebolisce i guerrieri. Seth non può difendere da solo una città malata."}
  {key:"#seth_need_entertainment", text:"Anche i sacerdoti di Seth hanno bisogno di più che esercitazioni e presagi."}
  {key:"#bast_city_low_health", text:"Bast piange nel vedere tanta gente malata. Spero che la pestilenza non colpisca."}
  {key:"#bast_no_food_in_city", text:"È difficile trovare cibo a sufficienza in questa città. La fame colpisce tutti."}
  {key:"#bast_city_not_safety", text:"Le misere difese della nostra città invitano i nemici ad attaccarci."}
  {key:"#bast_need_workers", text:"La nostra città non può funzionare bene con così tanti posti vacanti."}
  {key:"#bast_gods_are_angry", text:"Gli dèi stanno voltando le spalle a questa città. Dovremmo portare loro più rispetto."}
  {key:"#bast_low_sentiment", text:"La reputazione della città è pessima. Un'invasione può arrivare da un momento all'altro."}
  {key:"#bast_much_unemployments", text:"Nemmeno Bast può alleggerire il cuore di tanti disoccupati."}
  {key:"#bast_low_entertainment", text:"Bast è inorridita dalla mancanza di intrattenimento in questa città."}
  {key:"#bast_need_entertainment", text:"Che deve fare una sacerdotessa? Qui c'è ben poco svago."}
  {key:"#bast_city_is_good", text:"Questa città non è un brutto posto in cui vivere."}
  {key:"#bast_city_is_amazing", text:"Questa città è la migliore di tutte!"}
  {key:"#bast_god_love_festival", text:"Bast adora una bella festività."}
  {key:"#bast_city_low_mood", text:"La gente della città è profondamente scontenta. Presto potrebbe darsi al crimine."}
  {key:"#bast_disease_in_city", text:"Bast mi concede il potere di curare i malati prima che diffondano la malattia."}
  {key:"#hunt_bird_birds_are_wily", text:"Questi uccelli sono furbi!"}
  {key:"#hunt_bird_birds_ready_for_roasting", text:"Questi uccelli sono pronti per l'arrosto!"}
  {key:"#mission2_pottery_step1", text:"Riempi un Deposito merci di vasellame"}
  {key:"#mission2_pottery_step2", text:"Abbellisci la città, poi rileggi le istruzioni della missione"}
  {key:"#mission3_brew_beer", text:"Produci birra da distribuire nei Bazar"}
  {key:"#reach_modest_houses_number", text:"Porta 10 case ad abitazione modesta"}
  {key:"#build_tax_collector", text:"Costruisci un esattore"}
  {key:"#market_buyer_returning_to", text:"Verso"}
  {key:"#market_buyer_collecting", text:"Raccolta"}
  {key:"#tutorial_goal_education", text:"Fai evolvere una casa in 'appartamento spazioso'"}
  {key:"#tutorial_goal_scribal_school", text:"Produci del papiro e costruisci una Scuola degli scribi"}
  {key:"#tutorial_goal_import_bricks", text:"Importa dei mattoni per poter costruire una mastaba"}
  {key:"#mission4_goal_spacious_apartment", text:"1/4 Fai evolvere una casa in un Appartamento spazioso (cibo, acqua, vasellame, intrattenimento)"}
  {key:"#mission4_goal_reed_gatherer", text:"2/4 Costruisci un raccoglitore di canne vicino alle paludi"}
  {key:"#mission4_goal_papyrus_maker", text:"2/4 Costruisci una fabbrica di papiro e riforniscila di canne"}
  {key:"#mission4_goal_scribal_school", text:"2/4 Costruisci una scuola degli scribi, poi conserva 100 unità di papiro in un deposito"}
  {key:"#mission4_goal_store_papyrus", text:"2/4 Immagazzina 100 papiri in un Deposito merci per sbloccare il commercio"}
  {key:"#mission4_goal_import_bricks", text:"3/4 Perwadjyt (300 db) vende solo mattoni — importane 100. Nekhen (550) compra papiro"}
  {key:"#mission4_goal_build_mastaba", text:"4/4 Costruisci una Gilda dei muratori e posiziona una Mastaba piccola"}
  {key:"#mission4_goal_export_papyrus", text:"Apri Nekhen (550 db), esporta papiro, poi raggiungi i livelli (1500 / 15 / 20 / 9 / 40)"}
  {key:"#mission5_goal_food", text:"1/6 Costruisci un casotto da caccia, un granaio e un bazar — il cibo viene dalla cacciagione e dalle importazioni"}
  {key:"#mission5_goal_water", text:"1/6 Aggiungi un serbatoio d'acqua più stazione dei vigili del fuoco, centro di architettura e stazione di polizia"}
  {key:"#mission5_goal_mines", text:"2/6 Costruisci miniere di rame e di gemme e un deposito merci"}
  {key:"#mission5_goal_stock_copper", text:"2/6 Conserva 5 unità di rame in un deposito — richiesta del Faraone entro il mese 8 dell'anno 0"}
  {key:"#mission5_goal_military_industry", text:"3/6 Costruisci un'Armeria e un Reclutatore prima delle scorrerie libiche dell'anno 2"}
  {key:"#mission5_goal_fort", text:"3/6 Costruisci un forte di fanteria o arcieri — incursioni dall'anno 2 mese 7 (9, poi 16, poi 24)"}
  {key:"#mission5_goal_gems_trade", text:"4/6 Apri Nubt (850 db) o Thinis (800 db) per il cibo; accumula 15 gemme entro l'anno 2 mese 4"}
  {key:"#mission5_goal_deben", text:"5/6 Tieni 885 deben nel tesoro — il Faraone li richiede entro l'anno 2, mese 8"}
  {key:"#mission5_goal_weapons", text:"5/6 Produci armi — il Faraone ne richiede 11 entro l'anno 7, mese 3"}
  {key:"#mission5_goal_win", text:"6/6 Raggiungi gli obiettivi: 2000 di popolazione, 15 di prosperità, 70 di regno; fai migliorare le abitazioni con l'intrattenimento"}
  {key:"#none", text:"Niente"}
  {key:"#grain", text:"Grano"}
  {key:"#meat", text:"Carne"}
  {key:"#lettuce", text:"Lattuga"}
  {key:"#chickpeas", text:"Ceci"}
  {key:"#pomegranates", text:"Melograni"}
  {key:"#figs", text:"Fichi"}
  {key:"#fish", text:"Pesce"}
  {key:"#gamemeat", text:"Cacciagione"}
  {key:"#straw", text:"Paglia"}
  {key:"#weapons", text:"Armi"}
  {key:"#clay", text:"Argilla"}
  {key:"#bricks", text:"Mattoni"}
  {key:"#pottery", text:"Vasellame"}
  {key:"#barley", text:"Orzo"}
  {key:"#beer", text:"Birra"}
  {key:"#flax", text:"Lino"}
  {key:"#linen", text:"Tela"}
  {key:"#gems", text:"Gemme"}
  {key:"#luxury_goods", text:"Beni lusso"}
  {key:"#timber", text:"Legname"}
  {key:"#gold", text:"Oro"}
  {key:"#reeds", text:"Canne"}
  {key:"#papyrus", text:"Papiro"}
  {key:"#stone", text:"Pietra"}
  {key:"#limestone", text:"Calcare"}
  {key:"#granite", text:"Granito"}
  {key:"#chariots", text:"Carri"}
  {key:"#copper", text:"Rame"}
  {key:"#sandstone", text:"Arenaria"}
  {key:"#oil", text:"Olio"}
  {key:"#henna", text:"Henné"}
  {key:"#paint", text:"Vernice"}
  {key:"#lamps", text:"Lampade"}
  {key:"#marble", text:"Marmo"}
  {key:"#deben", text:"Db"}
  {key:"#troops", text:"Truppe"}
  {key:"#jewelry_luxury", text:"Gioielli (beni di lusso)"}
  {key:"#jewelry", text:"Gioielli"}
  {key:"#wine_luxury", text:"Vino (beni di lusso)"}
  {key:"#wine", text:"Vino"}
  {key:"#ivory_luxury", text:"Avorio (beni di lusso)"}
  {key:"#ivory", text:"Avorio"}
  {key:"#ebony_luxury", text:"Ebano (beni di lusso)"}
  {key:"#ebony", text:"Ebano"}
  {key:"#incense_luxury", text:"Incenso (beni di lusso)"}
  {key:"#incense", text:"Incenso"}
  {key:"#olive_oil_luxury", text:"Olio d'oliva (beni di lusso)"}
  {key:"#olive_oil", text:"Olio d'oliva"}
  {key:"#leopard_skins_luxury", text:"Pelli di leopardo (beni di lusso)"}
  {key:"#leopard_skins", text:"Pelli di leopardo"}
  {key:"#perfume_luxury", text:"Profumo (beni di lusso)"}
  {key:"#perfume", text:"Profumo"}
  {key:"#bandstand_none", text:"Questa casa non ha accesso a un palco dei musicanti"}
  {key:"#bandstand_medium", text:"Questa casa è stata visitata di recente da un musicante. Avrà accesso al musicante ancora per molto"}
  {key:"#bandstand_high", text:"Questa casa ha accesso al musicante"}
  {key:"#bandstand_low", text:"Questa casa non riceve la visita di un musicante da un po'. Presto perderà l'accesso al musicante"}
  {key:"#goods_are_finished", text:"Le mie scorte sono andate a ruba! Torno al bazar a prenderne altre."}
  {key:"#we_are_selling_goods", text:"Faccio del mio meglio per dare alla gente ciò che vuole."}
  {key:"#seller_city_has_low_health", text:"La gente è malata — difficile vendere quando nessuno vuole uscire di casa."}
  {key:"#seller_no_food_in_city", text:"Scaffali vuoti e stomaci vuoti. Che cosa dovrei vendere?"}
  {key:"#seller_city_have_no_army", text:"Nessun forte? I predoni saccheggeranno questo bazar prima che io finisca il giro."}
  {key:"#seller_much_unemployments", text:"C'è gente sfaccendata in giro, ma con le borse vuote."}
  {key:"#seller_gods_are_angry", text:"Gli dèi sembrano adirati. Nemmeno i migliori affari li placheranno."}
  {key:"#seller_city_is_bad_reputation", text:"La reputazione di questa città è così bassa che i clienti non si fidano dei prezzi."}
  {key:"#seller_too_much_unemployments", text:"Troppa gente senza lavoro. Chi ha fame è un pessimo cliente."}
  {key:"#seller_low_entertainment", text:"Niente festività da secoli. Una parata porterebbe acquirenti ai miei cesti."}
  {key:"#seller_city_is_good", text:"Questa città va bene — strade corte e clienti costanti."}
  {key:"#seller_city_is_amazing", text:"La città migliore in cui vendere! I miei cesti si svuotano da soli."}
  {key:"#scriber_dicease_can_start", text:"La gente è malata. I miei papiri medici dicono che il male potrebbe presto trasformarsi in peste!"}
  {key:"#scriber_these_festivals", text:"Queste festività! Ne ho lette di più grandiose: qui ce ne vorrebbe un'altra."}
  {key:"#scriber_plague_could_break_out", text:"La gente è malata. I miei papiri medici dicono che la malattia potrebbe presto trasformarsi in peste!"}
  {key:"#scriber_no_food_in_city", text:"Sono affamato. È dura sollevare i miei rotoli a stomaco vuoto."}
  {key:"#scriber_defenses_are_weak", text:"Persino il nemico più sprovveduto riuscirebbe a superare le nostre difese!"}
  {key:"#scriber_need_more_workers", text:"Se non arrivano presto altri lavoratori, la città ne soffrirà di sicuro."}
  {key:"#scriber_gods_are_angry", text:"La letteratura è piena di storie di dèi adirati e delle loro vendette."}
  {key:"#scriber_reputation_is_low", text:"La storia insegna che una città come la nostra pagherà gravi conseguenze per la sua cattiva reputazione."}
  {key:"#scriber_much_unemployments", text:"Ci sono molti disoccupati in città. Almeno hanno tutto il tempo per leggere."}
  {key:"#scriber_high_unemployment", text:"Ci sono molti disoccupati in città. Almeno hanno tutto il tempo per leggere."}
  {key:"#scriber_low_entertainment", text:"A volte i miei occhi vorrebbero posarsi su qualcosa che non siano geroglifici. Voglio vedere uno spettacolo!"}
  {key:"#scriber_city_is_ok", text:"Questa città è paragonabile ad altre di cui ho letto."}
  {key:"#scriber_city_is_amazing", text:"Questa città è la migliore che la storia abbia mai conosciuto!"}
  {key:"#teacher_festival_info", text:"Le festività insegnano quanto il papiro: alla città ne servirebbe un'altra."}
  {key:"#teacher_low_entertainment", text:"Nessuno spettacolo da secoli. Anche gli allievi si stancano dei soli geroglifici."}
  {key:"#teacher_desease_can_start_at_any_moment", text:"Malattia per le strade. È difficile insegnare quando i ragazzi hanno la febbre."}
  {key:"#teacher_no_food_in_city", text:"Granai vuoti? Gli studenti affamati imparano male."}
  {key:"#teacher_city_not_safety", text:"Nessun forte? Le scuole sono un riparo misero contro gli invasori."}
  {key:"#teacher_need_workers", text:"Servono più lavoratori: l'istruzione da sola non riempie ogni posto."}
  {key:"#teacher_gods_are_angry", text:"Gli dèi sembrano adirati. Anche i testi più saggi mettono in guardia dalla loro ira."}
  {key:"#teacher_low_rating", text:"La nostra posizione presso il Faraone è scarsa. La storia non sarà clemente."}
  {key:"#teacher_much_unemployments", text:"Quanti disoccupati. Almeno hanno tempo per studiare."}
  {key:"#teacher_city_is_good", text:"Questa città è un buon posto per imparare e insegnare."}
  {key:"#teacher_city_much_better", text:"Qui le cose vanno molto meglio che nelle città di cui ho letto."}
  {key:"#teacher_city_is_amazing", text:"La città migliore in cui abbia insegnato. Questi allievi scriveranno la storia!"}
  {key:"#tomb_artisan_ready", text:"Argilla e colori pronti. È ora di decorare la tomba!"}
  {key:"#tomb_artisan_going_to_work", text:"Vado alla tomba: le pareti aspettano il colore."}
  {key:"#tomb_artisan_decorating", text:"Pennello fermo. Queste pareti parleranno per l'eternità."}
  {key:"#tomb_artisan_return_home", text:"Decorazioni finite per ora. Torno alla gilda."}
  {key:"#tomb_artisan_disease_risk", text:"Febbre nei pozzi. Difficile dipingere con le mani che tremano."}
  {key:"#tomb_artisan_no_food_in_city", text:"Granai vuoti? Un artigiano affamato dipinge linee storte."}
  {key:"#tomb_artisan_city_have_no_army", text:"Nessun forte? Una sola incursione e queste tombe saranno saccheggiate."}
  {key:"#tomb_artisan_gods_are_angry", text:"Gli dei sembrano adirati. Persino le pitture sacre possono incrinarsi."}
  {key:"#tomb_artisan_low_entertainment", text:"Nessuna festività da un'eternità. Anche i pittori di tombe hanno bisogno di luce."}
  {key:"#tomb_artisan_city_is_good", text:"Questa città è solida! Tombe eccellenti per sovrani eccellenti."}
  {key:"#tomb_artisan_city_is_amazing", text:"La città migliore per cui abbia dipinto. Queste pareti dureranno per sempre!"}
  {key:"#tomb_robber_gold_should_be_for_living", text:"Oro nelle tombe? Dovrebbe essere per i vivi!"}
  {key:"#tomb_robber_just_think_of_the_fortune", text:"Pensa alla fortuna che aspetta in quella tomba!"}
  {key:"#tomb_robber_tax_too_high", text:"Le tasse prendono da voi — io prendo dai morti!"}
  {key:"#tomb_robber_wages_too_low", text:"Stipendi troppo bassi? Le tombe pagano meglio del lavoro onesto."}
  {key:"#tomb_robber_no_jobs", text:"Niente lavoro onesto? Bene. Saccheggiare tombe rende."}
  {key:"#tomb_robber_no_food_in_city", text:"Granai vuoti? L'oro riempie comunque le tasche."}
  {key:"#tomb_robber_city_have_no_army", text:"Nessun forte? Notti facili tra le tombe."}
  {key:"#tomb_robber_gods_are_angry", text:"Dèi adirati? Ottima copertura: la colpa è del cielo, non mia."}
  {key:"#tomb_robber_low_entertainment", text:"Niente festività? Saccheggiare tombe è il mio intrattenimento."}
  {key:"#tomb_robber_city_is_good", text:"Bella città. Belle tombe da alleggerire."}
  {key:"#tomb_robber_city_is_amazing", text:"La città migliore da depredare — tombe ricche ovunque!"}
  {key:"#dentist_concerned_about_plague", text:"La gente è così preoccupata di prendere la peste che trascura i denti."}
  {key:"#dentist_no_food_in_city", text:"Ho mangiato così poco ultimamente...che triste spreco di denti perfetti."}
  {key:"#dentist_defenses_are_weak", text:"Le difese della città sono piene di falle. I nostri nemici potrebbero farne quel che vogliono."}
  {key:"#dentist_need_more_workers", text:"La forza lavoro di questa città è come la bocca di un vecchio: quanti buchi da riempire!"}
  {key:"#dentist_gods_are_angry", text:"Mi preoccupano i molari di questa città - cioè, la morale! Dobbiamo portare più rispetto agli dèi."}
  {key:"#dentist_reputation_is_low", text:"La nostra reputazione è marcia. Potremmo essere attaccati."}
  {key:"#dentist_much_unemployments", text:"Non ho mai visto così tanta gente senza lavoro!"}
  {key:"#dentist_low_entertainment", text:"Che noia! Tanto vale lavarmi di nuovo i denti."}
  {key:"#dentist_city_is_ok", text:"Questa città va bene. Solo qualche carie!"}
  {key:"#dentist_city_is_amazing", text:"Questa città ha il sorriso più smagliante di tutto l'Egitto."}
  {key:"#zookeeper_danger_of_plague", text:"Pestilenza per le strade? Non rischio di portare la malattia agli animali."}
  {key:"#zookeeper_no_food_in_city", text:"Granai vuoti per la gente, e le gabbie da sfamare lo stesso. Non può durare."}
  {key:"#zookeeper_defenses_are_weak", text:"Nemici alle porte? Tenete le gabbie chiuse e i visitatori al riparo."}
  {key:"#zookeeper_need_more_workers", text:"Lavoro dappertutto: persino lo zoo avrebbe bisogno di più guardiani."}
  {key:"#zookeeper_gods_are_angry", text:"Dèi adirati fanno bestie inquiete. Dovremmo mostrare più rispetto."}
  {key:"#zookeeper_reputation_is_low", text:"La reputazione della nostra città è selvaggia come un leone affamato. Potremmo essere attaccati."}
  {key:"#zookeeper_high_unemployment", text:"Quante braccia in ozio. Almeno gli animali non si lamentano mai degli straordinari."}
  {key:"#zookeeper_low_entertainment", text:"Non si celebrano festività da secoli. Lo zoo è l'unico spettacolo rimasto in città."}
  {key:"#zookeeper_city_is_ok", text:"Questa città va bene — gli animali sembrano contenti, e anch'io."}
  {key:"#zookeeper_city_is_amazing", text:"La città migliore che un guardiano possa desiderare. Persino i leoni fanno le fusa per il Faraone!"}
  {key:"#warship_well_fight_to_the_death", text:"Combatteremo fino alla morte! Per il Faraone e per il fiume!"}
  {key:"#warship_enemy_is_too_much_for_us", text:"Questo nemico è troppo forte per noi. Ritirata al molo!"}
  {key:"#warship_enemies_coming_this_way", text:"Nemici in arrivo! Preparate gli arcieri!"}
  {key:"#warship_ready_to_attack_invaders", text:"Pronti ad attaccare gli invasori. Il Nilo è nostro."}
  {key:"#warship_ready_if_foes_come", text:"Pronti se arrivano i nemici. Il nostro scafo è robusto."}
  {key:"#transport_must_protect_our_ship", text:"Dobbiamo proteggere la nostra nave e le truppe a bordo."}
  {key:"#transport_enemy_is_here", text:"Il nemico è qui! Proteggete il trasporto!"}
  {key:"#transport_were_prepared", text:"Siamo pronti. Le truppe possono imbarcarsi al tuo ordine."}
  {key:"#transport_ready_if_need_arises", text:"Pronti in caso di bisogno. I soldati del Faraone attendono."}
  {key:"#embalmer_concerned_about_plague", text:"A giudicare dal numero di malati in questa città, presto avrò un gran daffare!"}
  {key:"#embalmer_no_food_in_city", text:"Sono affamato. Tra poco sarò più magro di una mummia!"}
  {key:"#embalmer_defenses_weak", text:"La città non è ben avvolta nelle sue difese. Un nemico potrebbe sconfiggerci facilmente."}
  {key:"#embalmer_need_more_workers", text:"Se mai avessi voluto lasciare l'imbalsamazione, questa è l'occasione. Quanti posti vacanti!"}
  {key:"#embalmer_gods_are_angry", text:"Gli dei potrebbero presto disfare la nostra città se non portiamo loro più rispetto."}
  {key:"#embalmer_reputation_is_low", text:"La cattiva reputazione della città potrebbe essere la fine per tutti noi. Potremmo essere attaccati da un momento all'altro."}
  {key:"#embalmer_unemployment_is_high", text:"Quando vedo tanta gente senza lavoro, sono contento di averne uno."}
  {key:"#embalmer_low_entertainment", text:"Questa città è morta come i corpi con cui lavoro tutto il giorno. Vorrei che fosse viva di intrattenimento."}
  {key:"#embalmer_city_is_ok", text:"Tanto vale vivere qui. Vale più o meno quanto ogni altro posto."}
  {key:"#embalmer_city_is_the_best", text:"Mi dispiace davvero per i miei clienti. Non sono più qui a godersi questa città incredibile!"}
  {key:"#embalmer_health_worsening", text:"La salute sembra peggiorare in tutta la città."}
  {key:"#drunkard_need_drink", text:"Sono secco come il deserto. È ora di bere!"}
  {key:"#drunkard_going_to_tavern", text:"Taverna senet, arrivo! Non cominciate senza di me."}
  {key:"#drunkard_time_for_beer", text:"Ah, la birra! L'unico fiume in cui non mi dispiace annegare."}
  {key:"#drunkard_feeling_dizzy", text:"La strada continua a muoversi. O sono solo io?"}
  {key:"#drunkard_oh_my_stomach", text:"Uff... il mio stomaco. Troppa birra e poco cervello."}
  {key:"#drunkard_going_home", text:"A casa... se ricordo quale porta è la mia."}
  {key:"#drunkard_disease_risk", text:"Sono tutti malati. La birra è l'unica medicina di cui mi fido."}
  {key:"#drunkard_no_food_in_city", text:"Niente cibo in città? Va bene — la birra è un pasto, se strizzi gli occhi."}
  {key:"#drunkard_city_have_no_army", text:"Nessun forte? Se arrivano gli invasori, nascondetemi dietro una giara di birra."}
  {key:"#drunkard_need_workers", text:"Non ci sono abbastanza lavoratori? Assumetemi — penso io alla birra."}
  {key:"#drunkard_gods_are_angry", text:"Gli dèi sono adirati. Offri loro un giro e forse si calmeranno."}
  {key:"#drunkard_city_is_bad", text:"La fama di questa città è peggiore dei miei postumi."}
  {key:"#drunkard_much_unemployment", text:"Quanta gente in ozio. Compagnia di bevute perfetta!"}
  {key:"#drunkard_low_entertainment", text:"Niente festività? Allora la taverna senet è l'unico spettacolo in città."}
  {key:"#drunkard_city_is_good", text:"Questa città non è male. Poca strada fino alla birra, tanta per tornare a casa."}
  {key:"#drunkard_city_is_amazing", text:"La città migliore per un bevitore! Che le giare non si svuotino mai."}
  {key:"#magistrate_i_hope_we_are_ready", text:"Spero di meritarmi un corteo funebre quando sarà il momento."}
  {key:"#magistrate_no_criminals_in_city", text:"Tutto tranquillo al palazzo di giustizia. Qui non c'è crimine."}
  {key:"#magistrate_all_good_in_city", text:"Mi occupo solo di casi minori. Niente di troppo grave!"}
  {key:"#magistrate_streets_still_arent_safety", text:"Riesco a malapena a smaltire i miei casi, eppure le strade non sono ancora sicure."}
  {key:"#magistrate_disease_in_city", text:"Le condizioni sanitarie di questa città sono criminali. La pestilenza è la pena adatta al crimine."}
  {key:"#magistrate_no_food_in_city", text:"Ho così fame che un buon pasto ti comprerà qualunque verdetto desideri."}
  {key:"#magistrate_city_not_safety", text:"Che difese pietose! I nostri nemici potrebbero entrare in città e prenderne il controllo."}
  {key:"#magistrate_need_workers", text:"Non ho mai visto tanti posti di lavoro liberi!"}
  {key:"#magistrate_gods_are_angry", text:"Gli dèi ci giudicheranno colpevoli di negligenza se non cominciamo a prestare loro più attenzione."}
  {key:"#magistrate_city_bad_reputation", text:"La nostra città è giudicata tra le peggiori del Regno. Temo l'esecuzione della nostra punizione."}
  {key:"#magistrate_much_unemployments", text:"I disoccupati hanno troppo tempo libero, e questo è pericoloso."}
  {key:"#magistrate_no_entertainment_need", text:"Questa città è colpevole di scarso intrattenimento!"}
  {key:"#magistrate_city_not_bad", text:"Questa città è in equilibrio: niente di troppo buono, ma niente di troppo brutto."}
  {key:"#magistrate_city_is_amazing", text:"Giudico questa città la migliore."}
  {key:"#magistrate_not_used", text:"(non usato)"}
  {key:"#magistrate_need_embalmers", text:"Spero di meritarmi un corteo funebre quando sarà il momento."}
  {key:"#magistrate_courthouse_in_peace", text:"Al palazzo di giustizia è tutto tranquillo. Qui non c'è crimine."}
  {key:"#magistrate_i_have_only_minor_cases", text:"Mi occupo solo di casi minori. Niente di troppo grave!"}
  {key:"#magistrate_i_am_overwhelmed", text:"Riesco a stento a smaltire i miei casi, eppure le strade restano insicure."}
  {key:"#goto_site_of_event", text:"Vai al luogo dell'evento"}
  {key:"#hold_festival_to", text:"Festività in onore di"}
  {key:"#god_osiris", text:"Osiride"}
  {key:"#god_ra", text:"Ra"}
  {key:"#god_ptah", text:"Ptah"}
  {key:"#god_seth", text:"Seth"}
  {key:"#god_bast", text:"Bast"}
  {key:"#god_to_osiris", text:"Osiride"}
  {key:"#god_to_ra", text:"Ra"}
  {key:"#god_to_ptah", text:"Ptah"}
  {key:"#god_to_seth", text:"Seth"}
  {key:"#god_to_bast", text:"Bast"}
  {key:"#difficulty_settings", text:"Impostazioni difficoltà"}
  {key:"#difficulty_row_difficulty", text:"Difficoltà"}
  {key:"#difficulty_row_gods", text:"Effetti degli dei"}
  {key:"#difficulty_right_click_to_continue", text:"Clicca col tasto destro per continuare"}
  {key:"#difficulty_very_easy", text:"Molto facile"}
  {key:"#difficulty_easy", text:"Facile"}
  {key:"#difficulty_normal", text:"Normale"}
  {key:"#difficulty_hard", text:"Difficile"}
  {key:"#difficulty_very_hard", text:"Molto difficile"}
  {key:"#difficulty_gods_effects_off", text:"Effetti degli dèi OFF"}
  {key:"#difficulty_gods_effects_on", text:"Effetti degli dei ON"}
  {key:"#food_stocks_not_provided", text:"Questa capanna si procura il cibo da sé..."}
  {key:"#food_stocks_none", text:"Questa casa non ha scorte di cibo"}
  {key:"#food_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di cibo"}
  {key:"#food_stocks_medium", text:"Questa casa ha scorte di cibo sufficienti almeno per il mese a venire"}
  {key:"#food_stocks_high", text:"Questa casa non ha problemi a procurarsi il cibo che le serve per sopravvivere"}
  {key:"#beer_stocks_none", text:"Questa casa non ha scorte di birra"}
  {key:"#beer_stocks_low", text:"Questa casa consumerà presto le sue scorte limitate di birra"}
  {key:"#beer_stocks_medium", text:"Questa casa ha scorte di birra per almeno il mese a venire"}
  {key:"#beer_stocks_high", text:"Questa casa non ha problemi a ottenere la birra di cui ha bisogno"}
  {key:"#apothecary_access_none", text:"Questa casa non ha accesso a una farmacia"}
  {key:"#apothecary_access_high", text:"Questa casa ha ricevuto di recente la visita di un erborista. Avrà accesso alla farmacia a lungo"}
  {key:"#apothecary_access_medium", text:"Questa casa ha accesso alla farmacia"}
  {key:"#apothecary_access_low", text:"Se un erborista non passa presto, questa casa perderà l'accesso alla Farmacia"}
  {key:"#magistrate_access_none", text:"Questa casa non ha accesso a un palazzo di giustizia"}
  {key:"#magistrate_access_high", text:"Questa casa è stata visitata di recente da un magistrato. Avrà accesso al Palazzo di giustizia ancora a lungo"}
  {key:"#magistrate_access_medium", text:"Questa casa ha accesso al Palazzo di giustizia"}
  {key:"#magistrate_access_low", text:"Questa casa non è visitata da un magistrato da un po'. Perderà presto l'accesso al Palazzo di giustizia"}
  {key:"#booth_access_none", text:"Questa casa non ha accesso a un giocoliere"}
  {key:"#booth_access_high", text:"Questa casa ha ricevuto di recente la visita di un giocoliere. Avrà accesso al giocoliere a lungo"}
  {key:"#booth_access_medium", text:"Questa casa ha accesso al giocoliere"}
  {key:"#booth_access_low", text:"Da tempo un giocoliere non passa da questa casa. Presto perderà l'accesso al giocoliere"}
  {key:"#health_risk_none", text:"Questo edificio non ha alcuna probabilità di malattia."}
  {key:"#health_risk_negligible", text:"Questo edificio presenta un rischio di malattia trascurabile."}
  {key:"#health_risk_some", text:"Questo edificio ha un certo rischio di malattia."}
  {key:"#health_risk_high", text:"Questo edificio ha un rischio di malattia"}
  {key:"#health_diseased", text:"Questa costruzione è infestata dalle malattie."}
  {key:"#malaria_risk_negligible", text:"Questo edificio presenta un rischio di malaria trascurabile."}
  {key:"#malaria_risk_some", text:"Questo edificio ha un certo rischio di malaria."}
  {key:"#malaria_risk_present", text:"Questo edificio è a rischio di malaria"}
  {key:"#malaria_risk_imminent", text:"Questo edificio avrà presto la malaria."}
  {key:"#malaria_risk_critical", text:"Rischio di malaria"}
  {key:"#damage_risk_perfect", text:"Questo edificio è in perfette condizioni strutturali"}
  {key:"#damage_risk_negligible", text:"Questo edificio ha un rischio di crollo trascurabile"}
  {key:"#damage_risk_low", text:"Questa costruzione ha un rischio di crollo basso"}
  {key:"#damage_risk_some", text:"Questo edificio presenta alcuni difetti strutturali"}
  {key:"#damage_risk_many", text:"Questo edificio ha molte crepe e difetti strutturali"}
  {key:"#damage_risk_critical", text:"Questo edificio è instabile e rischia di crollare presto"}
  {key:"#fire_risk_none", text:"Questo edificio non ha alcuna probabilità di prendere fuoco"}
  {key:"#fire_risk_negligible", text:"Questo edificio presenta un rischio di incendio trascurabile"}
  {key:"#fire_risk_low", text:"Questo edificio ha un certo rischio di incendio"}
  {key:"#fire_risk_some", text:"Questo edificio ha un rischio di incendio"}
  {key:"#fire_risk_high", text:"Questa costruzione è a rischio d'incendio altissimo"}
  {key:"#fire_risk_critical", text:"Questo edificio potrebbe incendiarsi da un momento all'altro!"}
  {key:"#tax_income_not_registered", text:"Questa casa non è registrata al fisco, quindi non paga tasse"}
  {key:"#tax_income_none_yet", text:"Nessuna tassa riscossa da questa casa finora quest'anno."}
  {key:"#tax_income_collected", text:" db raccolti finora quest'anno."}
  {key:"#entertainment_access_none", text:"Questa abitazione non ha accesso ad alcun intrattenimento"}
  {key:"#entertainment_access_barely", text:"Questa abitazione ha a malapena accesso all'intrattenimento"}
  {key:"#entertainment_access_very_limited", text:"Questa abitazione ha un accesso molto limitato ai luoghi di intrattenimento"}
  {key:"#entertainment_access_limited", text:"Questa dimora ha un accesso limitato ai luoghi d'intrattenimento"}
  {key:"#entertainment_access_some", text:"Questa abitazione ha un discreto accesso ai luoghi di intrattenimento"}
  {key:"#entertainment_access_several", text:"Questa abitazione ha accesso a parecchi luoghi di intrattenimento"}
  {key:"#entertainment_access_reasonable", text:"Questa abitazione ha un discreto accesso ai luoghi di intrattenimento"}
  {key:"#entertainment_access_good", text:"Questa abitazione ha buon accesso ai luoghi di intrattenimento"}
  {key:"#entertainment_access_very_good", text:"Questa abitazione ha un accesso molto buono ai luoghi di intrattenimento"}
  {key:"#entertainment_access_excellent", text:"Questa abitazione ha un accesso eccellente ai luoghi di intrattenimento"}
  {key:"#entertainment_access_max", text:"Questa abitazione ha accesso a tutto l'intrattenimento che potrebbe desiderare"}
  {key:"#senet_access_none", text:"Questa casa non ha accesso a una taverna senet"}
  {key:"#senet_access_high", text:"Questa casa ha ricevuto di recente la visita di un maestro senet. Avrà accesso alla taverna senet a lungo"}
  {key:"#senet_access_medium", text:"Questa casa ha accesso alla taverna senet"}
  {key:"#senet_access_low", text:"Da tempo un maestro senet non passa da questa casa. Presto perderà l'accesso alla Taverna senet"}
  {key:"#overlay_zoo", text:"Zoo"}
  {key:"#pavilion_access_none", text:"Questa casa non ha accesso a un teatro delle danze"}
  {key:"#pavilion_access_high", text:"Un danzatore è passato di recente da questa casa. Avrà accesso al palco delle danze a lungo"}
  {key:"#pavilion_access_medium", text:"Questa casa ha accesso al palco delle danze"}
  {key:"#pavilion_access_low", text:"Questa casa non riceve la visita di un danzatore da un po'. Presto perderà l'accesso alla danza"}
  {key:"#mortuary_access_none", text:"Questa casa non ha accesso a una camera mortuaria"}
  {key:"#mortuary_access_high", text:"Questa casa è stata visitata di recente da un imbalsamatore. Avrà accesso alla camera mortuaria a lungo"}
  {key:"#mortuary_access_medium", text:"Questa casa ha accesso alla Camera mortuaria"}
  {key:"#mortuary_access_low", text:"Se un imbalsamatore non passa presto, questa casa perderà l'accesso alla camera mortuaria"}
  {key:"#dentist_access_none", text:"Questa casa non ha accesso a uno studio del Dentista"}
  {key:"#dentist_access_high", text:"Un dentista è passato di recente da questa casa. Avrà accesso al dentista a lungo"}
  {key:"#dentist_access_medium", text:"Questa casa ha accesso al dentista"}
  {key:"#dentist_access_low", text:"Se un dentista non passerà presto, questa casa perderà l'accesso allo studio dentistico"}
  {key:"#physician_access_none", text:"Nessun accesso al medico."}
  {key:"#physician_access_low", text:"Questa casa non viene visitata da un medico da un po'."}
  {key:"#physician_access_medium", text:"Da questa casa è passato un medico."}
  {key:"#physician_access_high", text:"Da questa casa è passato di recente un medico."}
  {key:"#education_access_none", text:"Questa casa non ha accesso ad alcuna Scuola degli scribi o Biblioteca"}
  {key:"#education_access_school_or_library", text:"Questa casa ha accesso a una Scuola degli scribi o a una Biblioteca"}
  {key:"#education_access_school_and_library", text:"Questa casa ha accesso sia a una Scuola degli scribi sia a una Biblioteca"}
  {key:"#education_access_academy_district", text:"Questa casa ha accesso alla scuola degli scribi e alla biblioteca. I suoi bambini sono anche in un distretto dell'accademia"}
  {key:"#religion_access_none", text:"Questa casa non ha accesso a templi o santuari"}
  {key:"#religion_access_one", text:"Questa casa ha accesso al tempio di un solo dio"}
  {key:"#religion_access_two", text:"Questa casa ha accesso ai Templi di 2 dèi diversi"}
  {key:"#religion_access_three", text:"Questa casa ha accesso ai templi di 3 divinità diverse"}
  {key:"#religion_access_four", text:"Questa casa ha accesso ai Templi di 4 dèi diversi"}
  {key:"#religion_access_all", text:"Questa casa ha accesso ai Templi di tutti gli dei"}
  {key:"#religion_access_shrine_and_all", text:"Questa casa ha accesso a un Santuario e a Templi di tutti gli dèi"}
  {key:"#school_access_none", text:"Questa casa non ha accesso a una scuola degli scribi"}
  {key:"#school_access_high", text:"Questa casa ha ricevuto di recente la visita di uno studioso. Avrà accesso alla scuola degli scribi a lungo"}
  {key:"#school_access_medium", text:"Questa casa ha accesso alla scuola degli scribi"}
  {key:"#school_access_low", text:"Se uno studioso non passa presto, questa casa perderà l'accesso alla Scuola degli scribi"}
  {key:"#library_access_none", text:"Questa casa non ha accesso a una biblioteca"}
  {key:"#library_access_high", text:"Questa casa è stata visitata di recente da un libraio. Avrà accesso alla Biblioteca ancora a lungo"}
  {key:"#library_access_medium", text:"Questa casa ha accesso alla Biblioteca"}
  {key:"#library_access_low", text:"Se un libraio non passa presto, questa casa perderà l'accesso alla Biblioteca"}
  {key:"#library_read_about_festivals", text:"Ho letto di festività in città lontane. Ce ne vorrebbe una anche qui."}
  {key:"#library_people_are_sick", text:"La gente è malata. Persino i papiri medici sembrano preoccupati."}
  {key:"#library_no_food_in_city", text:"È difficile concentrarsi sui rotoli quando la città ha fame."}
  {key:"#library_defenses_are_weak", text:"Le nostre difese sono sottili come il papiro. Una scorreria e la biblioteca brucia."}
  {key:"#library_need_more_workers", text:"Senza più lavoratori, nemmeno gli scaffali verranno letti."}
  {key:"#library_gods_are_angry", text:"I testi avvertono che gli dèi sono adirati. Faremmo bene ad ascoltarli."}
  {key:"#library_reputation_is_low", text:"Una città con una cattiva reputazione conserva di rado a lungo le sue biblioteche."}
  {key:"#library_high_unemployment", text:"Quante mani inoperose. Almeno hanno il tempo di prendere in prestito un rotolo."}
  {key:"#library_low_entertainment", text:"A volte gli occhi hanno bisogno di riposarsi dai geroglifici. Voglio uno spettacolo!"}
  {key:"#library_city_is_ok", text:"Questa città va bene: paragonabile ad altre che ho catalogato."}
  {key:"#library_city_is_amazing", text:"Questa città merita un posto nelle storie migliori!"}
  {key:"#academy_access_none", text:"Questa casa non ha accesso a un'Accademia"}
  {key:"#academy_access_high", text:"Da questa casa è passato di recente un insegnante. Avrà accesso all'accademia per molto tempo"}
  {key:"#academy_access_medium", text:"Questa casa ha accesso all'Accademia"}
  {key:"#academy_access_low", text:"Se un insegnante non passa presto, questa casa perderà l'accesso all'Accademia"}
  {key:"#top_menu_file", text:"File"}
  {key:"#top_menu_file_tooltip", text:"Carica, salva, nuova partita ed esci"}
  {key:"#top_menu_options", text:"Opzioni"}
  {key:"#top_menu_options_tooltip", text:"Impostazioni di grafica, audio, velocità e difficoltà"}
  {key:"#top_menu_help", text:"Aiuto"}
  {key:"#top_menu_help_tooltip", text:"Ottieni aiuto, suggerimenti e informazioni sul gioco"}
  {key:"#top_menu_overseers", text:"Supervisori"}
  {key:"#top_menu_overseers_tooltip", text:"Consulta i tuoi supervisori sullo stato della città"}
  {key:"#top_menu_funds", text:"Db"}
  {key:"#top_menu_population", text:"Pop."}
  {key:"#top_menu_new_game", text:"Nuova partita"}
  {key:"#top_menu_load_game", text:"Carica partita"}
  {key:"#top_menu_save_game", text:"Salva partita"}
  {key:"#top_menu_exit_game", text:"Esci dal gioco"}
  {key:"#top_menu_delete_game", text:"Elimina partita"}
  {key:"#top_menu_display_settings", text:"Impostazioni video"}
  {key:"#top_menu_sound_settings", text:"Impostazioni audio"}
  {key:"#top_menu_speed_settings", text:"Impostazioni velocità"}
  {key:"#top_menu_pyramid_speedup_off", text:"Accelera piramide - NO"}
  {key:"#top_menu_pyramid_speedup_on", text:"Piramide accelerata - ATTIVA"}
  {key:"#top_menu_difficulty", text:"Difficoltà"}
  {key:"#top_menu_cities_egyptian", text:"Città - Egizie"}
  {key:"#top_menu_cities_classical", text:"Città - Classiche"}
  {key:"#top_menu_popup_messages", text:"Messaggi popup"}
  {key:"#top_menu_help_item", text:"Aiuto"}
  {key:"#top_menu_mouse_help_off", text:"Aiuto mouse - OFF"}
  {key:"#top_menu_mouse_help_some", text:"Aiuto mouse - PARZIALE"}
  {key:"#top_menu_mouse_help_full", text:"Aiuto mouse - COMPLETO"}
  {key:"#top_menu_warnings_off", text:"Avvisi - OFF"}
  {key:"#top_menu_warnings_on", text:"Avvisi - ON"}
  {key:"#top_menu_about", text:"Informazioni"}
  {key:"#top_menu_advisor_labor", text:"Supervisore del lavoro"}
  {key:"#top_menu_advisor_military", text:"Supervisore militare"}
  {key:"#top_menu_advisor_imperial", text:"Supervisore politico"}
  {key:"#top_menu_advisor_ratings", text:"Supervisore valutazioni"}
  {key:"#top_menu_advisor_trade", text:"Supervisore commerciale"}
  {key:"#top_menu_advisor_population", text:"Supervisore dei granai"}
  {key:"#top_menu_advisor_health", text:"Supervisore della sanità"}
  {key:"#top_menu_advisor_education", text:"Supervisore all'istruzione"}
  {key:"#top_menu_advisor_entertainment", text:"Supervisore all'intrattenimento"}
  {key:"#top_menu_advisor_religion", text:"Supervisore dei templi"}
  {key:"#top_menu_advisor_financial", text:"Supervisore finanziario"}
  {key:"#top_menu_advisor_chief", text:"Supervisore capo"}
  {key:"#monthly_autosave_on", text:"Salvataggio automatico mensile ATTIVO"}
  {key:"#monthly_autosave_off", text:"Salvataggio automatico mensile OFF"}
  {key:"#top_menu_funds_tooltip", text:"Fondi attuali della città"}
  {key:"#top_menu_population_tooltip", text:"Popolazione attuale della città"}
  {key:"#top_menu_date_tooltip", text:"La data attuale!"}
  {key:"#month_jan", text:"Gen"}
  {key:"#month_feb", text:"Feb"}
  {key:"#month_mar", text:"Mar"}
  {key:"#month_apr", text:"Apr"}
  {key:"#month_may", text:"Maggio"}
  {key:"#month_jun", text:"Giu"}
  {key:"#month_jul", text:"Lug"}
  {key:"#month_aug", text:"Ago"}
  {key:"#month_sep", text:"Set"}
  {key:"#month_oct", text:"Ott"}
  {key:"#month_nov", text:"Nov"}
  {key:"#month_dec", text:"Dic"}
  {key:"#top_menu_debug", text:"Debug"}
  {key:"#top_menu_debug_render", text:"Render"}
  {key:"#top_menu_cheat_console", text:"Console dei trucchi"}
  {key:"#top_menu_properties_on", text:"Proprietà ON"}
  {key:"#top_menu_properties_off", text:"Proprietà OFF"}
  {key:"#top_menu_terrain_paint_on", text:"Disegno terreno ON"}
  {key:"#top_menu_terrain_paint_off", text:"Pittura terreno NO"}
  {key:"#top_menu_write_video_on", text:"Registrazione video ATTIVA"}
  {key:"#top_menu_write_video_off", text:"Registrazione video OFF"}
  {key:"#top_menu_buildings_on", text:"Costruzioni ON"}
  {key:"#top_menu_buildings_off", text:"Costruzioni OFF"}
  {key:"#top_menu_js_debugger_on", text:"Debugger JS ON"}
  {key:"#top_menu_js_debugger_off", text:"JS debugger OFF"}
  {key:"#top_menu_editor_new_map", text:"Nuova mappa"}
  {key:"#top_menu_editor_load_map", text:"Carica mappa"}
  {key:"#top_menu_editor_save_map", text:"Salva mappa"}
  {key:"#top_menu_editor_exit", text:"Esci dall'Editor"}
  {key:"#top_menu_editor_resets", text:"Resetta"}
  {key:"#top_menu_editor_clear_herds", text:"Elimina punti predatori"}
  {key:"#top_menu_editor_clear_fish", text:"Elimina pesci"}
  {key:"#top_menu_editor_clear_invasions", text:"Elimina invasioni"}
  {key:"#top_menu_editor_empire", text:"Regno"}
  {key:"#top_menu_editor_empire_choose", text:"Modifica regno"}
  {key:"#sidebar_speed_header", text:"Velocità"}
  {key:"#sidebar_flat_buildings", text:"Vista piatta"}
  {key:"#sidebar_flat_buildings_on", text:"Vista piatta: ON"}
  {key:"#no_requests", text:"Al momento non ci sono richieste in sospeso."}
  {key:"#overlay_menu_normal", text:"Normale"}
  {key:"#overlay_menu_risks", text:"Rischi"}
  {key:"#overlay_menu_water", text:"Acqua"}
  {key:"#overlay_menu_entertainment", text:"Divertimento"}
  {key:"#overlay_menu_religion", text:"Religione"}
  {key:"#overlay_menu_education", text:"Istruzione"}
  {key:"#overlay_menu_health", text:"Salute"}
  {key:"#overlay_menu_administration", text:"Amministrazione"}
  {key:"#overlay_menu_food", text:"Cibo"}
  {key:"#overlay_menu_other", text:"Altro"}
  {key:"#overlay_fire", text:"Fuoco"}
  {key:"#overlay_damage", text:"Danni"}
  {key:"#overlay_architect_reach", text:"Portata architetto"}
  {key:"#overlay_architect_reach_hint", text:"Clicca un ufficio architetto"}
  {key:"#overlay_architect_reach_tile", text:"Nella zona di pattuglia"}
  {key:"#overlay_crime", text:"Criminalità"}
  {key:"#overlay_entertainment", text:"Intrattenimento"}
  {key:"#overlay_booth", text:"Giullare"}
  {key:"#overlay_bandstand", text:"Musicista"}
  {key:"#overlay_pavilion", text:"Danzatore"}
  {key:"#overlay_senet_house", text:"Giocatori di senet"}
  {key:"#overlay_education", text:"Istruzione"}
  {key:"#overlay_scribal_school", text:"Scuole di scribi"}
  {key:"#overlay_library", text:"Biblioteca"}
  {key:"#overlay_academy", text:"Accademia"}
  {key:"#overlay_apothecary", text:"Speziale"}
  {key:"#overlay_dentist", text:"Dentista"}
  {key:"#overlay_physician", text:"Medico"}
  {key:"#overlay_mortuary", text:"Obitorio"}
  {key:"#overlay_tax_income", text:"Entrate fiscali"}
  {key:"#overlay_bazaar_access", text:"Accesso al bazar"}
  {key:"#overlay_desirability", text:"Desiderabilità"}
  {key:"#overlay_fertility", text:"Fertilità"}
  {key:"#overlay_magistrate", text:"Magistrato"}
  {key:"#overlay_food_stocks", text:"Scorte alimentari"}
  {key:"#overlay_labor", text:"Lavoro"}
  {key:"#overlay_labor_access", text:"Accesso al lavoro"}
  {key:"#overlay_native", text:"Nativo"}
  {key:"#overlay_problems", text:"Problemi"}
  {key:"#overlay_routing", text:"Percorsi"}
  {key:"#overlay_malaria_risk", text:"Rischio malaria"}
  {key:"#overlay_health", text:"Salute"}
  {key:"#overlay_criminal", text:"Criminale"}
  {key:"#overlay_osiris", text:"Osiride"}
  {key:"#overlay_ra", text:"Ra"}
  {key:"#overlay_ptah", text:"Ptah"}
  {key:"#overlay_seth", text:"Seth"}
  {key:"#overlay_bast", text:"Bastet"}
  {key:"#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text:"Disoccupazione"}
  {key:"#TR_PALACE_TOOLTIP_CULTURE_RATING", text:"Valutazione della cultura"}
  {key:"#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text:"Valutazione della prosperità"}
  {key:"#TR_PALACE_TOOLTIP_MONUMENT_RATING", text:"Valutazione dei monumenti"}
  {key:"#TR_PALACE_TOOLTIP_KINGDOM_RATING", text:"Valutazione del regno"}
  {key:"#crete", text:"CRETA"}
  {key:"#cyprus", text:"CIPRO"}
  {key:"#eastern_africa", text:"AFRICA ORIENTALE"}
  {key:"#eastern_desert", text:"DESERTO ORIENTALE"}
  {key:"#greece", text:"GRECIA"}
  {key:"#libya", text:"LIBIA"}
  {key:"#lower_egypt", text:"BASSO EGITTO"}
  {key:"#delta", text:"DELTA"}
  {key:"#fayuum", text:"FAYUUM"}
  {key:"#nubia", text:"NUBIA"}
  {key:"#palestine", text:"PALESTINA"}
  {key:"#sinai", text:"SINAI"}
  {key:"#syria", text:"SIRIA"}
  {key:"#upper_egypt", text:"ALTO EGITTO"}
  {key:"#western_desert", text:"DESERTO OCCIDENTALE"}
  {key:"#lebanon", text:"LIBANO"}
  {key:"#canaan", text:"CANAAN"}
]
