log_info("akhenaten: localization_fr config started")

localization_fr = [
  { key:"#TR_NO_PATCH_TITLE", text:"Patch 1.0.1.0 manquant"},
  { key:"#TR_NO_PATCH_MESSAGE",text: ""},
  { key:"#TR_MISSING_FONTS_TITLE", text:"Polices manquantes"},
  { key:"#TR_MISSING_FONTS_MESSAGE",text: ""},
  { key:"#TR_NO_EDITOR_TITLE", text:"Éditeur manquant"},
  { key:"#TR_NO_EDITOR_MESSAGE",text: ""},
  { key:"#TR_INVALID_LANGUAGE_TITLE", text:"Répertoire de langue invalide"},
  { key:"#TR_INVALID_LANGUAGE_MESSAGE", text:"Le répertoire que vous avez sélectionné ne contient pas de pack de langue valide. Veuillez consulter les erreurs dans le fichier de log."},
  { key:"#dock_order_trade", text:"Commercer"},
  { key:"#dock_order_dont_trade", text:"Ne pas commercer"},
  { key:"#dock_order_accept_all", text:"Tout accepter"},
  { key:"#dock_orders_hint", text:"Les navires n'utilisent ce quai que si au moins une de leurs marchandises est réglée sur Commercer."},
  { key:"#dock_orders_closed", text:"Ce quai n'accepte aucune marchandise — les navires n'y accosteront pas."},
  { key:"#TR_BUTTON_OK", text:"OK"},
  { key:"#TR_BUTTON_CANCEL", text:"Annuler"},
  { key:"#TR_BUTTON_RESET_DEFAULTS", text:"Réinitialiser"},
  { key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Contrôles du clavier"},
  { key:"#TR_BUTTON_NEXT",text: "+"},
  { key:"#TR_BUTTON_PREV",text: "-"},
  { key:"#TR_CONFIG_TITLE", text:"Options de configuration d'Ozzy"},
  { key:"#TR_CONFIG_LANGUAGE_LABEL", text:"Langue :"},
  { key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(par défaut)"},
  { key:"#TR_CONFIG_PAGE_LABEL", text:"Page"},
  { key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"Configuration de l'interface"},
  { key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Configuration du jeu"},
  { key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"},
  { key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"},
  { key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"},
  { key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Jouer la vidéo d'introduction"},
  { key:"#TR_CONFIG_SIDEBAR_INFO", text:"Informations supplémentaires dans le panneau latéral"},
  { key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"Activer le défilement doux"},
  { key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Améliore le retour visuel durant le dégagement du terrain"},
  { key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Permet de construire tous les temples successivement"},
  { key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Voir la zone d'effet en plaçant des réservoirs, des fontaines et des puits"},
  { key:"#TR_CONFIG_SHOW_DELIVERY_PATHS", text:"Afficher les chemins de livraison récents en maintenant Alt sur un grenier ou une loge de chasse"},
  { key:"#delivery_path_no_road", text:"Pas d'accès à la route — livraison impossible"},
  { key:"#delivery_path_understaffed", text:"Aucun entrepôt acceptant — sous-effectif"},
  { key:"#delivery_path_no_destination", text:"Aucune destination acceptant cette marchandise"},
  { key:"#delivery_path_no_route", text:"Destination trouvée, mais aucun chemin routier"},
  { key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Voir la taille des constructions durant le glissement de la souris"},
  { key:"#TR_CONFIG_HIGHLIGHT_LEGIONS", text:"Mettre en surbrillance les légions au survol du curseur"},
  { key:"#TR_CONFIG_ROTATE_MANUALLY", text:"Rotation corps de garde et l'arc de triomphe par raccourci clavier"},
  { key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Corrige le bug d'immigration en mode très difficile"},
  { key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Corrige le bug des fantômes de 100 ans"},
  { key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Corrige \"Nouvel Empereur\" et la survie des parties créees avec l'éditeur"},
  { key:"#TR_CONFIG_DRAW_WALKER_WAYPOINTS", text:"Affiche l'itinéraire du marcheur en cliquant droit sur un bâtiment"},
  { key:"#TR_CONFIG_ZOOM_STEPPED", text:"Active le zoom (peut être lent et utilise plus de RAM)"},
  { key:"#TR_CONFIG_COMPLETE_RATING_COLUMNS", text:"Corrige les colonnes d'évaluation incomplètes"},
  { key:"#TR_CONFIG_GRANDFESTIVAL", text:"Les grandes fêtes permettent une bénédiction supplémentaire d'un dieu"},
  { key:"#TR_CONFIG_JEALOUS_GODS", text:"Déactive la jalousie des dieux"},
  { key:"#TR_CONFIG_GLOBAL_LABOUR", text:"Active la main-d'œuvre globale"},
  { key:"#TR_CONFIG_NOBLES_DONT_PROVIDE_LABOR", text:"Les manoirs et plus ne fournissent pas de main-d'œuvre"},
  { key:"#TR_CONFIG_SCHOOL_WALKERS", text:"Augmente la couverture des écoliers"},
  { key:"#TR_CONFIG_RETIRE_AT_60", text:"Change l'âge de retraitre des citoyens de 50 à 60"},
  { key:"#TR_CONFIG_FIXED_WORKERS", text:"Réserve de travailleurs fixe — 38% des plébéiens"},
  { key:"#workers_staffing_tooltip", text:"%d / %d employés"},
  { key: "#figure_antelope_hunter", text: "Chasseur d'antilopes" },
  { key: "#figure_antelope_hunter_javelin", text: "Javelot de chasseur" },
  { key: "#figure_birds_hunter", text: "Chasseur d'oiseaux" },
  { key: "#antelope_hunter_hunting", text: "Les antilopes ne font pas le poids face à nous !" },
  { key: "#antelope_hunter_back", text: "Ce soir, il y aura des steaks pour tout le monde." },
  { key: "#antelope_hunter_city_is_good", text: "Cette ville est bonne !" },
  { key: "#hunter_ostrich_investigate", text: "Des traces dans le sable... une autruche est passée récemment." },
  { key: "#hunter_ostrich_chase", text: "La voilà ! Ses pattes sont rapides, mais mes flèches le sont davantage." },
  { key: "#hunter_ostrich_hunting", text: "Les autruches sont presque invisibles quand elles mettent la tête dans le sable." },
  { key: "#hunter_ostrich_back", text: "Ça, ce sont de GROSSES cuisses !" },
  { key: "#hunter_ostrich_reroute_packed", text: "Charge lourde, mauvais chemin. Je trouverai un autre retour." },
  { key: "#hunter_ostrich_look_packed", text: "Il me faut un sentier libre vers la cabane avec cet oiseau sur le dos." },
  { key: "#hunter_ostrich_unloading", text: "Gibier frais pour la cabane. Ça sent déjà mieux que l'orge." },
  { key: "#hunter_ostrich_disease_risk", text: "Ça sent la maladie ici. Mauvais temps pour chasser." },
  { key: "#hunter_ostrich_no_food_in_city", text: "Greniers vides ? Alors je ferais mieux de ramener un gros oiseau." },
  { key: "#hunter_ostrich_city_have_no_army", text: "Pas de forts ? Un raid de crocodiles, et cette ville est le dîner." },
  { key: "#hunter_ostrich_need_workers", text: "Il faut plus de bras. Je ne peux pas remplir toutes les marmites seul." },
  { key: "#hunter_ostrich_gods_are_angry", text: "Les dieux ont l'air en colère. Même les autruches le sentent." },
  { key: "#hunter_ostrich_city_is_bad", text: "Le pharaon n'est pas content de nous. Cela ne finit jamais bien." },
  { key: "#hunter_ostrich_much_unemployment", text: "Trop de gens oisifs. Au moins, la chasse nourrit encore quelqu'un." },
  { key: "#hunter_ostrich_low_entertainment", text: "Pas de fêtes depuis longtemps. Un festin d'autruche remonterait le moral." },
  { key: "#hunter_ostrich_city_is_good", text: "Cette ville est fantastique !" },
  { key: "#hunter_ostrich_city_is_amazing", text: "La meilleure ville pour laquelle j'ai chassé. Qu'elle le reste !" },
  { key: "#hunt_bird_birds_are_wily", text: "Ces oiseaux sont rusés !" },
  { key: "#hunt_bird_birds_ready_for_roasting", text: "Ces oiseaux sont prêts à rôtir !" },
  { key:"#TR_CONFIG_EXTRA_FORTS", text:"Autorise la construction de 4 forts supplémentaires"},
  { key:"#TR_CONFIG_WOLVES_BLOCK", text:"Bloque la construction autour des loups"},
  { key:"#TR_CONFIG_DYNAMIC_GRANARIES", text:"Bloque les routes des greniers non connectées"},
  { key:"#TR_CONFIG_MORE_STOCKPILE", text:"Les maisons stockent plus de marchandises du marché"},
  { key:"#TR_CONFIG_NO_BUYER_DISTRIBUTION", text:"Les vendeuses du marché ne distribuent pas les marchandises"},
  { key:"#TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS", text:"Destruction immédiate des bâtiments"},
  { key:"#TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD", text:"Les charretiers peuvent faire du hors route"},
  { key:"#TR_CONFIG_GRANARIES_GET_DOUBLE", text:"Double la capacité des charretiers sortant des greniers"},
  { key:"#TR_CONFIG_BAZAAR_MULTI_BUYERS", text:"Les bazars peuvent envoyer deux acheteuses à la fois (nourriture + biens)"},
  { key:"#TR_CONFIG_AUTO_RESOLVE_INVASIONS", text:"Résolution auto des invasions : gel à l'entrée, combat rapide en 8 jours (murs/tours ignorés ; Pharaon inclus ; pas les soulèvements)"},
  { key:"#TR_CONFIG_FLOOD_BASINS", text:"Enhanced : digues / bassins (fermez le contour — meilleurs rendements après la crue)"},
  { key:"#TR_CONFIG_FOOD_MILL", text:"Enhanced : variété alimentaire au bazar + moulin (graphisme provisoire)"},
  { key:"#TR_CONFIG_INDUSTRY_OFFICE", text:"Enhanced : bureau d'industrie — arrêt des ateliers dans le rayon (papyrus + scribes)"},
  { key:"#TR_CONFIG_TRADER_CAPACITY_1600", text:"Plus grande capacité des marchands (1600 par visite ; pas la limite annuelle d'empire)"},
  { key:"#TR_CONFIG_TRADER_PER_GOOD_1600", text:"New Era : jusqu'à 1600 de chaque bien par visite (pas la limite annuelle ; pas seulement le total)"},
  { key:"#trader_capacity_per_good", text:"Capacité (par bien)"},
  { key:"#TR_CONFIG_LABOR_CATEGORY_SPLIT", text:"Enhanced : séparer entrepôts/docks de l'industrie dans le conseiller au travail"},
  { key:"#TR_CONFIG_WALKER_SPAWN_BOOST", text:"Enhanced : marcheurs de service plus fréquents (sous-effectif moins dur)"},
  { key:"#TR_CONFIG_WALKER_MOVE_BOOST", text:"Enhanced : citoyens plus rapides / attente charrette plus courte"},
  { key:"#TR_CONFIG_FESTIVAL_CALENDAR", text:"Enhanced : rites calendaires saisonniers (thèmes de festival)"},
  { key:"#TR_CONFIG_LOCAL_CULTS", text:"Enhanced : cultes locaux via autel/oracle du complexe"},
  { key:"#labor_category_storage", text:"Stockage et distribution"},
  { key:"#labor_category_industry", text:"Industrie"},
  { key:"#labor_category_industry_commerce", text:"Industrie et commerce"},
  { key:"#labor_category_culture", text:"Culture"},
  { key:"#TR_CONFIG_HISTORICAL_ECONOMY", text:"Enhanced : économie historique — deben comme unité de compte ; partie des salaires en grain des greniers"},
  { key:"#finance_deben_unit_of_account", text:"poids-deben"},
  { key:"#finance_historical_economy_hint", text:"Les debens mesurent la valeur (poids de métal). Une partie du travail est payée en grain des greniers si disponible."},
  { key:"#finance_wages_paid_in_grain", text:"Salaires en grain (éq. deben)"},
  { key:"#building_food_mill", text:"Moulin (prov.)"},
  { key:"#building_food_mill_info", text:"Entrepôt alimentaire pour les bazars. Les fermes remplissent les greniers ; mettez le moulin en GET depuis grenier/entrepôt. Les bazars préfèrent un moulin pourvu et peuvent prendre plusieurs types en une visite. Graphisme provisoire (cubes verts)."},
  { key:"#food_mill_no_road_access", text:"Ce moulin n'a pas d'accès à la route. Les ouvriers ne peuvent pas apporter de nourriture."},
  { key:"#food_mill_storing", text:"Stockage"},
  { key:"#food_mill_space_for", text:"Place pour"},
  { key:"#food_mill_units", text:"unités"},
  { key:"#food_mill_quality_now", text:"Qualité alimentaire :"},
  { key:"#food_mill_variety_none", text:"aucune (vide)"},
  { key:"#food_mill_variety_bland", text:"Fade"},
  { key:"#food_mill_variety_plain", text:"Simple"},
  { key:"#food_mill_variety_appetizing", text:"Appétissante"},
  { key:"#food_mill_variety_tasty", text:"Savoureuse"},
  { key:"#bazaar_desired_variety", text:"Types d'aliments souhaités :"},
  { key:"#bazaar_min_variety", text:"Variété min. du moulin :"},
  { key:"#bazaar_waiting_mill_variety", text:"En attente de variété alimentaire au moulin."},
  { key:"#building_dike", text:"Digue"},
  { key:"#building_dike_info", text:"Remblai de terre pour l'irrigation en bassins sur la plaine inondable. Fermez un contour autour des fermes — meilleurs rendements après l'inondation."},
  { key:"#terrain_dike_sealed", text:"Bassin fermé"},
  { key:"#terrain_dike_breached", text:"Aucun bassin fermé adjacent — fermez un contour autour des fermes pour retenir le don de la crue."},
  { key:"#terrain_dike_tiles", text:"cases"},
  { key:"#terrain_dike_farms", text:"fermes"},
  { key:"#terrain_dike_bonus_hint", text:"Tant que le contour est fermé : fertilité et croissance des fermes améliorées."},
  { key:"#farm_in_flood_basin", text:"Dans un bassin inondable — meilleurs rendements après la crue tant que le contour reste fermé."},
  { key:"#overlay_flood_basin", text:"Bassins inondables"},
  { key:"#overlay_flood_basin_off", text:"Bassins inondables (Enhanced) désactivés"},
  { key:"#overlay_flood_basin_open", text:"Plaine inondable ouverte — pas de bassin fermé"},
  { key:"#overlay_flood_basin_none", text:"Pas de bassin inondable ici"},
  { key:"#warning_auto_resolve_orders_blocked", text:"Impossible de faire marcher les compagnies sur une vague d'invasion gelée"},
  { key:"#warning_auto_resolve_queue_full", text:"Trop d'invasions en attente — cette vague combat sur la carte"},
  { key:"#follow_walker", text:"Suivre le marcheur"},
  { key:"#stop_following", text:"Arrêter"},
  { key:"#warning_follow_walker_lost", text:"Marcheur suivi perdu"},
  { key:"#invasion_quick_battle_title", text:"Combat rapide"},
  { key:"#invasion_quick_battle_hint", text:"Les envahisseurs attendent au point d'entrée. Recrutez si besoin. Combattez maintenant ou attendez le minuteur."},
  { key:"#invasion_quick_battle_resolve", text:"Combattre"},
  { key:"#invasion_quick_battle_wait", text:"Attendre"},
  { key:"#invasion_quick_battle_strength", text:"Vos forces : {player}   Ennemi : {enemy}"},
  { key:"#invasion_quick_battle_days", text:"Combat dans {days} jours"},
  { key:"#invasion_quick_battle_queue", text:"({n} en file)"},
  { key:"#invasion_quick_battle_head", text:"Vague #{id} ({i}/{n})"},
  { key:"#invasion_quick_battle_none", text:"Aucun combat en attente"},
  { key:"#TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD", text:"Les sentinelles de la tour n'ont plus besoin de route"},
  { key:"#TR_CONFIG_FARMS_DELIVER_CLOSE", text:"Fermes et Quais ne livrent plus qu'aux grenier à proximité"},
  { key:"#TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES", text:"La nourriture n'est pas livrée depuis/vers les greniers"},
  { key:"#TR_CONFIG_ALL_HOUSES_MERGE", text:"Toutes les maisons fusionnent"},
  { key:"#TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY", text:"Les mines coûtent de l'argent au lieu d'être détruites."},
  { key:"#TR_CONFIG_MULTIPLE_BARRACKS", text:"Autorise la construction de plusieurs casernes."},
  { key:"#TR_CONFIG_NOT_ACCEPTING_WAREHOUSES", text:"Les entrepôts n'acceptent rien une fois construits"},
  { key:"#TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS", text:"Les maisons ne s'étendent pas sur les jardins"},
  { key:"#TR_HOTKEY_TITLE", text:"Configuration Raccourcis clavier"},
  { key:"#TR_HOTKEY_LABEL", text:"Raccourcis clavier"},
  { key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Alternative"},
  { key:"#TR_HOTKEY_HEADER_ARROWS", text:"Flèches directionnelles"},
  { key:"#TR_HOTKEY_HEADER_GLOBAL", text:"Contrôles globaux"},
  { key:"#TR_HOTKEY_HEADER_CITY", text:"Contrôles de la cité"},
  { key:"#TR_HOTKEY_HEADER_ADVISORS", text:"Rapports des conseillers"},
  { key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"Cartes de visualisation"},
  { key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"Points d'intérêt de la cité"},
  { key:"#TR_HOTKEY_HEADER_EDITOR", text:"Editeur"},
  { key:"#TR_HOTKEY_HEADER_BUILD", text:"Raccourcis de construction"},
  { key:"#TR_HOTKEY_ARROW_UP", text:"Haut"},
  { key:"#TR_HOTKEY_ARROW_DOWN", text:"Bas"},
  { key:"#TR_HOTKEY_ARROW_LEFT", text:"Gauche"},
  { key:"#TR_HOTKEY_ARROW_RIGHT", text:"Droite"},
  { key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Basculer en plein écran"},
  { key:"#TR_HOTKEY_CENTER_WINDOW", text:"Centrer la fenêtre"},
  { key:"#TR_HOTKEY_RESIZE_TO_640", text:"Redimensionner en 640x480"},
  { key:"#TR_HOTKEY_RESIZE_TO_800", text:"Redimensionner en 800x600"},
  { key:"#TR_HOTKEY_RESIZE_TO_1024", text:"Redimensionner en 1024x768"},
  { key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"Capturer l'écran de jeu"},
  { key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Capturer la cité entière"},
  { key:"#TR_HOTKEY_LOAD_FILE", text:"Charger une partie"},
  { key:"#TR_HOTKEY_SAVE_FILE", text:"Sauvegarder une partie"},
  { key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Augmenter la vitesse du jeu"},
  { key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Diminuer la vitesse du jeu"},
  { key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"Activer la pause"},
  { key:"#TR_GAME_PAUSED", text:"Jeu en pause (touche '{0}' pour continuer)"},
  { key:"#TR_HOTKEY_CYCLE_LEGION", text:"Parcourir les légions en boucle"},
  { key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Tourner la carte vers la gauche"},
  { key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Tourner la carte vers la droite"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Main-d'œuvre"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Légion"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Empereur"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Évaluation"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Commerce"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"Population"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Hygiène"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Éducation"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Loisirs"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Religion"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Finances"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Conseiller personnel"},
  { key:"#TR_HOTKEY_SHOW_ADVISOR_HOUSING", text:"Conseiller en logement"},
  { key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"Basculer sur la carte précédente"},
  {key:"#TR_HOTKEY_TOGGLE_FLAT_BUILDINGS", text:"Vue plate des bâtiments"},
  { key: "#sidebar_flat_buildings", text: "Vue plate" },
  { key: "#sidebar_flat_buildings_on", text: "Vue plate : ON" },
  { key: "#TR_CONFIG_FLAT_BUILDINGS", text: "Vue plate des bâtiments (Shift+F) — aplatir les bâtiments hauts pour voir les routes derrière" },
  { key: "#TR_TOOLTIP_FLAT_BUILDINGS", text: "Vue plate des bâtiments (Shift+F). Quand activée : Ctrl+clic droit relève un bâtiment." },
  { key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Eau"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Incendies"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Dégats"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Criminalité"},
  { key:"#TR_HOTKEY_ROTATE_BUILDING", text:"Rotation de bâtiment"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Problèmes"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_MALARIA_RISK", text:"Risque de paludisme"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_DISEASE", text:"Maladie"},
  { key:"#TR_HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS", text:"Masquer les falaises"},
  { key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Aller au point d'intérêt 1"},
  { key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Aller au point d'intérêt 2"},
  { key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Aller au point d'intérêt 3"},
  { key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Aller au point d'intérêt 4"},
  { key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"Définir comme point d'intérêt 1"},
  { key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"Définir comme point d'intérêt 2"},
  { key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"Définir comme point d'intérêt 3"},
  { key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"Définir comme point d'intérêt 4"},
  { key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Afficher les infos de bataille"},
  { key:"#TR_HOTKEY_EDIT_TITLE", text:"Appuyez sur une touche"},
  { key:"#TR_HOTKEY_DUPLICATE_TITLE", text:"Raccourci déjà utilisé"},
  { key:"#TR_HOTKEY_DUPLICATE_MESSAGE", text:"Cette touche est déjà assignée à «{0}»."},
  { key:"#TR_BUILDING_ROADBLOCK", text:"Barrages"},
  { key:"#TR_BUILDING_ROADBLOCK_DESC", text:"Barrages arrêtent les citoyens errants"},
  { key:"#TR_HEADER_HOUSING", text:"Logement"},
  { key:"#TR_ADVISOR_HOUSING_ROOM", text:"Le logement en ville a de la place pour"},
  { key:"#TR_ADVISOR_HOUSING_NO_ROOM", text:"Il n'y a plus de chambre disponible dans les logements."},
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY", text:"Résidences exigeant de la poterie"},
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE", text:"Résidences exigeantes en mobilier"},
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_OIL", text:"Résidences exigeantes en huile"},
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_WINE", text:"Résidences exigeant du vin"},
  { key:"#TR_ADVISOR_TOTAL_NUM_HOUSES", text:"Total des résidences :"},
  { key:"#TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY", text:"Capacité totale :"},
  { key:"#TR_ADVISOR_TOTAL_HOUSING_CAPACITY", text:"Capacité totale :"},
  { key:"#TR_ADVISOR_ADVISOR_HEADER_HOUSING", text:"Population - Logement"},
  { key:"#TR_ADVISOR_BUTTON_GRAPHS", text:"Graphiques"},
  { key:"#TR_ADVISOR_HOUSING_PROSPERITY_RATING", text:"La cote de prospérité du logement est"},
  { key:"#TR_ADVISOR_PERCENTAGE_IN_MANORS", text:"Pourcentage de votre population dans les villas et palais est"},
  { key:"#TR_ADVISOR_PERCENTAGE_IN_SHANTIES", text:"Pourcentage de votre population dans les tentes et cabanes est"},
  { key:"#TR_ADVISOR_AVERAGE_TAX", text:"Le revenu fiscal moyen par résidence est"},
  { key:"#tax_rate_of", text:"Taux d'imposition de"},
  { key:"#palace_vaults_hold", text:"Les coffres contiennent"},
  { key:"#debens", text:"Debens"},
  { key:"#building_no_road_access", text:"ATTENTION : Ce bâtiment n'est pas adjacent à une route"},
  { key:"#building_no_people_in_city", text:"Personne dans la ville !"},
  { key:"#building_no_workers_nearby", text:"Aucun travailleur n'habite à proximité"},
  { key:"#building_labor_could_shift", text:"Le Contremaître pourrait réaffecter de la main-d'œuvre"},
  { key:"#building_poor_worker_access", text:"ATTENTION : Accès médiocre aux travailleurs"},
  { key:"#TR_ADVISOR_AVERAGE_AGE", text:"L'âge moyen de votre population est"},
  { key:"#TR_ADVISOR_PERCENT_IN_WORKFORCE", text:"Pourcentage de votre population active est"},
  { key:"#TR_ADVISOR_BIRTHS_LAST_YEAR", text:"Naissances l'an dernier :"},
  { key:"#TR_ADVISOR_DEATHS_LAST_YEAR", text:"Morts l'an dernier :"},
  { key:"#TR_ADVISOR_TOTAL_POPULATION", text:"résidents total"}
  { key:"#mansion_protected_by_police", text:"Protégé par la police"}
  { key:"#mansion_not_protected_theft", text:"Non protégé — des voleurs peuvent dérober vos économies"}

  { key: "#overlay_menu_normal", text: "Normal" }
  { key: "#overlay_menu_risks", text: "Risques" }
  { key: "#overlay_menu_water", text: "Eau" }
  { key: "#overlay_menu_entertainment", text: "Divertissement" }
  { key: "#overlay_menu_religion", text: "Religion" }
  { key: "#overlay_menu_education", text: "Éducation" }
  { key: "#overlay_menu_health", text: "Santé" }
  { key: "#overlay_menu_administration", text: "Administration" }
  { key: "#overlay_menu_food", text: "Nourriture" }
  { key: "#overlay_menu_other", text: "Autre" }

  { key: "#overlay_fire", text: "Feu" }
  { key: "#overlay_damage", text: "Dégâts" }
  { key: "#overlay_architect_reach", text: "Portée de l'architecte" }
  { key: "#overlay_architect_reach_hint", text: "Cliquez sur un poste d'architecte" }
  { key: "#overlay_architect_reach_tile", text: "Dans la zone de patrouille" }
  { key: "#overlay_crime", text: "Criminalité" }
  { key: "#overlay_entertainment", text: "Divertissement" }
  { key: "#overlay_booth", text: "Jongleur" }
  { key: "#overlay_bandstand", text: "Musicien" }
  { key: "#overlay_pavilion", text: "Danseur" }
  { key: "#overlay_senet_house", text: "Joueurs de senet" }
  { key: "#overlay_education", text: "Éducation" }
  { key: "#overlay_scribal_school", text: "Écoles de scribes" }
  { key: "#overlay_library", text: "Bibliothèque" }
  { key: "#overlay_academy", text: "Académie" }
  { key: "#overlay_apothecary", text: "Apothicaire" }
  { key: "#overlay_dentist", text: "Dentiste" }
  { key: "#overlay_physician", text: "Médecin" }
  { key: "#overlay_mortuary", text: "Mortuaire" }
  { key: "#overlay_tax_income", text: "Revenus fiscaux" }
  { key: "#overlay_bazaar_access", text: "Accès au bazar" }
  { key: "#overlay_desirability", text: "Attractivité" }
  { key: "#overlay_fertility", text: "Fertilité" }
  { key: "#overlay_magistrate", text: "Magistrat" }
  { key: "#overlay_food_stocks", text: "Réserves alimentaires" }
  { key: "#overlay_labor", text: "Main-d'œuvre" }
  { key: "#overlay_labor_access", text: "Accès à la main-d'œuvre" }
  { key: "#overlay_native", text: "Natif" }
  { key: "#overlay_problems", text: "Problèmes" }
  { key: "#overlay_routing", text: "Itinéraires" }
  { key: "#overlay_malaria_risk", text: "Risque de paludisme" }
  { key: "#overlay_health", text: "Santé" }
  { key: "#overlay_criminal", text: "Criminel" }
  { key: "#overlay_osiris", text: "Osiris" }
  { key: "#overlay_ra", text: "Râ" }
  { key: "#overlay_ptah", text: "Ptah" }
  { key: "#overlay_seth", text: "Seth" }
  { key: "#overlay_bast", text: "Bastet" }
  { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "Chômage" }
  { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "Évaluation de la culture" }
  { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "Évaluation de la prospérité" }
  { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "Évaluation des monuments" }
  { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "Évaluation du royaume" }
  { key:"#editor_generate_map", text:"Générer la carte" }
  { key:"#TR_CONFIG_IRONWILL", text:"Mode Volonté de fer — sauvegarde uniquement en quittant vers le menu principal (bloque Sauvegarder, Ctrl+S, auto-sauvegarde, sauvegarde/chargement rapide)" }
  { key:"#TR_CONFIG_UNLOCK_ALL_CAMPAIGNS", text:"Débloquer toutes les périodes de campagne dans l'Histoire familiale" }
  { key:"#ironwill_briefing_label", text:"Volonté de fer" }
  { key:"#ironwill_save_blocked", text:"Volonté de fer : sauvegarde uniquement en quittant vers le menu" }
  { key:"#ironwill_load_blocked", text:"Volonté de fer : chargement uniquement depuis le menu principal (Continuer)" }
  { key:"#ironwill_save_failed", text:"Échec du point de sauvegarde Volonté de fer — toujours dans la cité" }
  { key:"#TR_BUTTON_PAUSE", text:"Pause" }
  { key:"#TR_BUTTON_RESUME", text:"Reprendre" }
  { key:"#TR_CONFIG_HIDE_NEW_GAME_TOP_MENU", text:"Masquer le bouton Nouvelle partie du menu" }
  { key:"#TR_CONFIG_SAVE_YEAR_KINGDOME_RATING", text:"Enregistrer la note du royaume à la mise à jour annuelle" }
  { key:"#TR_CONFIG_BUILDING_MOTHBALL_BUTTON", text:"Afficher le bouton de mise en veille dans les fenêtres des bâtiments" }
  { key:"#TR_CONFIG_PROMPT_SAVE_ON_EXIT", text:"Proposer de sauvegarder à la fermeture du jeu (Alt+F4)" }
  { key:"#TR_CONFIG_SMOOTH_ZOOM", text:"Activer le zoom fluide" }
  { key:"#TR_CONFIG_SHOW_BUILDING_ROAD_ACCESS", text:"Afficher la case d'accès à la route en plaçant ou survolant un bâtiment (classique : une case)" }
  { key:"#TR_CONFIG_PAUSE_SIM_WHILE_BUILDING", text:"Mettre la simulation en pause pendant le placement des bâtiments" }
  { key:"#TR_CONFIG_DOCK_DOUBLE_HAUL", text:"Doubler la charge des dockers (800 par trajet)" }
  { key:"#TR_CONFIG_DOCK_SMART_ROUTING", text:"Routage intelligent des quais : choisit le quai selon commandes/marchandises, bascule vers un meilleur quai libre (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_FOLLOWER_RUNAWAY", text:"Les suiveurs fuient vers la sortie de la carte à la mort de leur chef (ânes de caravane, porteurs ; pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_ROBBER_REMAKE", text:"Refonte des voleurs : vol à l'apparition, toujours vers le palais, vols dans les manoirs (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_TOMB_ROBBER_REMAKE", text:"Refonte des pilleurs de tombes : apparition mensuelle, fuite/arrestation, pénalité fixe au royaume (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_PROTESTOR_HUNT_NOBLES", text:"Les manifestants s'en prennent aux nobles et aux manoirs/domaines (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_FISHING_BOAT_REMAKE", text:"Refonte des bateaux de pêche : plus rapides avec personnel, demi-charge, zones fixes, perte du port en douceur (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_BAZAAR_BUYER_SPAWN_TIMER", text:"Les acheteuses du bazar suivent le minuteur de main-d'œuvre au lieu du décalage original de 8 jours (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_BAZAAR_DEMAND_FROM_TRADER", text:"Demande de biens au bazar uniquement quand une vendeuse visite les maisons, au lieu du balayage original de rayon 10 (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_MARKET_DISTRIBUTE_REMAKE", text:"Refonte de la distribution du marché : un type de nourriture par visite, remplissage selon le multiplicateur de stock (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_LIBRARY_SERVICE_CAP", text:"Refonte de la bibliothèque : le bibliothécaire sert jusqu'à max_service habitants par tournée, seulement les maisons proches d'une route (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_DENTIST_SERVICE_CAP", text:"Refonte du dentiste : un dentiste sert jusqu'à max_serve_clients habitants par mois et ne rafraîchit que les maisons sous la moitié de couverture (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_DENTIST_TOOTHACHE", text:"Refonte du dentiste : les nobles ont mal aux dents, les dentistes cherchent et soignent les maisons nobles (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_PHYSICIAN_SERVICE_CAP", text:"Refonte du médecin : sert jusqu'à max_serve_clients habitants par mois, ne rafraîchit que les maisons sous la moitié de couverture et améliore la santé au lieu de réduire le risque de malaria (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_APOTHECARY_REMAKE", text:"Refonte de l'apothicaire : l'herboriste porte la santé des maisons à 50 et réduit le risque de malaria de 30 (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_MORTUARY_SERVICE_CAP", text:"Refonte de la maison des morts : l'embaumeur sert jusqu'à max_serve_clients habitants par mois et ne rafraîchit que les maisons sous la moitié de couverture (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_MORTUARY_LINEN_UPKEEP", text:"Refonte de la maison des morts : les maisons des morts pourvues en personnel consomment aussi du lin chaque mois (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_MORTUARY_MOTHBALLED_LINEN", text:"Refonte de la maison des morts : pas d'embaumeurs tant que le lin est en veille (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_FORT_ROTATION", text:"Refonte du fort : la touche de rotation déplace le terrain de manœuvre autour du fort (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_FORT_REFUND_CARRY_TROOPS", text:"Refonte du fort : démolir un fort rend les troupes reportées de la mission précédente (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_STATUE_VARIANTS", text:"Refonte des statues : aspect de départ aléatoire, touches de rotation et de variante séparées, aspects supplémentaires (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_GUILD_STATUE_SERVICE", text:"Refonte des guildes : les ouvriers inoccupés entretiennent les statues (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_MASTABA_CLAY_DELIVERY", text:"Refonte du mastaba : les entrepôts livrent l'argile listée dans les phases de briques (l'original ne transportait que des briques)" }
  { key:"#TR_CONFIG_RECRUIT_NEAREST_FORT", text:"Refonte du recruteur : les recrues vont au fort le plus proche au lieu des chars d'abord, puis l'infanterie, puis les archers (pas dans le Pharaon original)" }
  { key:"#TR_CONFIG_BAST_LION_RAID", text:"Malédiction majeure de Bastet : raid de lions depuis les temples/le zoo (TEMP Amélioré)" }
  { key:"#TR_CONFIG_SETH_ASP_RAID", text:"Malédiction majeure de Seth : raid d'aspics depuis les temples quand aucune compagnie n'est à maudire (TEMP Amélioré)" }
  { key:"#TR_CONFIG_PTAH_SCORPION_RAID", text:"Malédiction majeure de Ptah : raid de scorpions depuis les temples quand aucune industrie n'est à détruire (TEMP Amélioré)" }
  { key:"#TR_CONFIG_INVASION_BRIBE", text:"Soudoyer les envahisseurs : payer des debens pour faire reculer une invasion étrangère/de Pharaon (pas l'armée du royaume ni les soulèvements)" }
  { key:"#invasion_bribe_button", text:"Soudoyer" }
  { key:"#invasion_bribe_cost_line", text:"Pot-de-vin : {cost} Db   Trésor : {treasury}" }
  { key:"#local_cult_anubis", text:"Anubis" }
  { key:"#local_cult_thoth", text:"Thot" }
  { key:"#local_cult_hathor", text:"Hathor" }
  { key:"#local_cult_inactive", text:"Construisez l'autel ou l'oracle correspondant sur le complexe hôte" }
  { key:"#local_cults_header", text:"Cultes locaux" }
  { key:"#festival_calendar_upcoming", text:"Rite à venir" }
  { key:"#building_industry_office", text:"Bureau de l'industrie (temp)" }
  { key:"#building_industry_office_info", text:"Les scribes gèrent l'industrie voisine tant qu'ils ont du papyrus. Les cubes verts marquent l'emprise en attendant les graphismes." }
  { key:"#industry_office_managing", text:"Ateliers gérés :" }
  { key:"#industry_office_needs_papyrus", text:"Besoin de papyrus" }
  { key:"#industry_office_needs_workers", text:"Besoin de scribes (ouvriers)" }
  { key:"#industry_office_inactive", text:"Bureau inactif" }
  { key:"#industry_office_working", text:"Émission des ordres de production" }
  { key:"#industry_office_mothball_all", text:"Tout mettre en veille" }
  { key:"#industry_office_unmothball_all", text:"Tout reprendre" }
  { key:"#cannot_demolish_flooded_farm", text:"Impossible de démolir une ferme tant que la plaine inondable est sous l'eau" }
  { key:"#monument_not_demolishable", text:"Les monuments ne peuvent pas être démolis" }
  { key:"#TR_CONFIG_FARM_HARVEST_FERTILITY", text:"Récolte de la plaine inondable selon la fertilité (refonte ; l'original utilise seulement la progression)" }
  { key:"#TR_CONFIG_FARM_MEADOW_HARVEST_RETRY", text:"Les fermes de prairie récoltent aussi le jour 1 (refonte ; l'original seulement le jour 0)" }
  { key:"#TR_CONFIG_INDUSTRY_NEARBY_HOUSES", text:"Accès à la main-d'œuvre de l'industrie depuis les maisons dans le rayon nearby_houses_radius (hebdomadaire ; refonte ; l'original utilise les recruteurs)" }
  { key:"#TR_CONFIG_DISASTER_EVENTS_USE_AMOUNT", text:"Les crues d'argile / effondrements de mine d'or détruisent des bâtiments lors de l'événement" }
  { key:"#TR_CONFIG_FIX_IRRIGATION_RANGE", text:"Corriger la portée de l'irrigation" }
  { key:"#TR_CONFIG_FIX_FARM_PRODUCING", text:"Corriger la production des fermes" }
  { key:"#TR_CONFIG_EMPIRE_MAP_RUNS_SIMULATION", text:"La cité continue de tourner quand la carte de l'empire est ouverte" }
  { key:"#TR_CONFIG_CAMERA_KEEP_INERTIA", text:"Garder l'inertie de la caméra" }
  { key:"#TR_CONFIG_UNDERSTAFFED_ACCEPT_GOODS", text:"Les bâtiments en sous-effectif acceptent les marchandises" }
  { key:"#TR_CONFIG_MULTIPLE_TEMPLE_COMPLEXES", text:"Plusieurs complexes de temples" }
  { key:"#TR_CONFIG_MULTIPLE_MONUMENTS", text:"Plusieurs monuments" }
  { key:"#TR_CONFIG_SOIL_DEPLETION", text:"Épuisement des sols" }
  { key:"#TR_CONFIG_MULTIPLE_GATHERERS", text:"Plusieurs cueilleurs" }
  { key:"#TR_CONFIG_WOOD_CUTTER_SINGLE_GATHERER", text:"Bûcherons : un bûcheron + apparition sur n'importe quel arbre (refonte ; original 1/2/3 selon le personnel, arbres adultes seulement)" }
  { key:"#TR_CONFIG_FIREMAN_RETURNING", text:"Le pompier revient après avoir éteint un feu" }
  { key:"#TR_CONFIG_ARCHITECT_PATROL_MOST_DAMAGED", text:"Les architectes vont vers les bâtiments les plus endommagés" }
  { key:"#TR_CONFIG_OG_ARCHITECT", text:"Architecte du Pharaon original (réduit les dégâts, répare les murs)" }
  { key:"#TR_CONFIG_OG_FIREMAN", text:"Pompier du Pharaon original (réduit le risque d'incendie, détecte les feux de plus loin)" }
  { key:"#TR_CONFIG_OG_WAREHOUSEMAN", text:"Charrette d'entrepôt du Pharaon original (quantités, disparition sans cible, particularité des greniers)" }
  { key:"#TR_CONFIG_OG_TRADER", text:"Caravane commerciale du Pharaon original (capacité fixe de 800, achat et vente à chaque tour)" }
  { key:"#TR_CONFIG_CART_SPEED_DEPENDS_QUANTITY", text:"La vitesse des charrettes dépend de la quantité transportée" }
  { key:"#TR_CONFIG_CH_CITIZEN_ROAD_OFFSET", text:"Décalages différents pour les citoyens sur la route" }
  { key:"#TR_CONFIG_CH_WORK_CAMP_ONE_WORKER_PER_MONTH", text:"Le camp de travail produit un ouvrier par mois" }
  { key:"#TR_CONFIG_CH_CLAY_PIT_FIRE_RISK_REDUCED", text:"Risque d'incendie réduit pour les carrières d'argile" }
  { key:"#TR_CONFIG_CITY_HAS_ANIMALS", text:"La cité a des animaux" }
  { key:"#TR_CONFIG_GOLDMINE_REDUCED_PRODUCTION", text:"La mine d'or produit à 1/10 du rythme des ouvriers" }
  { key:"#TR_CONFIG_NEW_TAX_COLLECTION_SYSTEM", text:"Nouveau système de collecte des impôts" }
  { key:"#TR_CONFIG_SMALL_HUT_NOT_CREATE_EMIGRANT", text:"Les petites huttes ne créent pas d'émigrants" }
  { key:"#TR_CONFIG_DELIVERY_BOY_GOES_TO_MARKET_ALONE", text:"Le porteur va seul au marché" }
  { key:"#TR_CONFIG_RELIGION_COVERAGE_INFLUENCE_SENTIMENT", text:"La couverture religieuse influence l'humeur" }
  { key:"#TR_CONFIG_MONUMENTS_INFLUENCE_SENTIMENT", text:"Les monuments influencent l'humeur" }
  { key:"#TR_CONFIG_SHRINE_HOUSE_ACCESS", text:"Les sanctuaires donnent l'accès à la religion aux maisons voisines sans prêtres" }
  { key:"#TR_CONFIG_WELL_RADIUS_DEPENDS_MOISTURE", text:"Le rayon des puits dépend de l'humidité" }
  { key:"#TR_CONFIG_ENTER_POINT_ON_NEAREST_TILE", text:"Entrée du bâtiment sur la case la plus proche" }
  { key:"#TR_CONFIG_FISHING_WHARF_SPAWN_BOATS", text:"Le quai de pêche génère des bateaux" }
  { key:"#TR_CONFIG_CITY_FLOTSAM_ENABLED", text:"Épaves flottantes activées" }
  { key:"#TR_CONFIG_COPPER_NEAR_MOUNTAINS", text:"La mine de cuivre peut être construite près des montagnes" }
  { key:"#TR_CONFIG_RECRUITER_NOT_NEED_FORTS", text:"Le recruteur n'a pas besoin de forts" }
  { key:"#TR_CONFIG_BUILDING_CLOSEST_ROAD", text:"Case d'accès du bâtiment sur la route la plus proche" }
  { key:"#TR_CONFIG_FLOODPLAIN_RANDOM_GROW", text:"Croissance aléatoire de la plaine inondable" }
  { key:"#TR_CONFIG_DRAW_FPS", text:"Afficher les FPS" }
  { key:"#TR_CONFIG_SHOW_CURRENT_SELECT_TILE", text:"Afficher la case sous le curseur sur la carte" }
  { key:"#TR_CONFIG_SHOW_INPUT_NEAR_CURSOR", text:"Afficher les touches et boutons de souris appuyés près du curseur" }
  { key:"#TR_CONFIG_ROAD_PREVIEW_IN_MAP_ORDER", text:"Dessiner l'aperçu de construction de route dans l'ordre de rendu de la carte" }
  { key:"#TR_CONFIG_HIGHLIGHT_TOP_MENU_HOVER", text:"Surligner les éléments du menu supérieur" }
  { key:"#TR_CONFIG_EMPIRE_CITY_OLD_NAMES", text:"Afficher les anciens noms des cités sur la carte de l'empire" }
  { key:"#TR_CONFIG_DRAW_CLOUD_SHADOWS", text:"Dessiner les ombres des nuages (expérimental)" }
  { key:"#TR_CONFIG_CONSERVATORY_HELPS_DANCE_SCHOOL", text:"Le conservatoire aide l'école de danse (réduit le délai d'apparition)" }
  { key:"#TR_CONFIG_JUGGLER_SCHOOL_ONE_WALKER", text:"L'école de jongleurs attend le jongleur précédent (l'original permet le chevauchement)" }
  { key:"#TR_CONFIG_JEWELS_WORKSHOPS_CULTURE_BONUS", text:"Les ateliers de bijoux donnent un bonus de culture (+1 tous les 3 ateliers)" }
  { key:"#TR_CONFIG_OVERLAY_SHOW_GRAY_BUILDINGS", text:"Afficher en gris les bâtiments non concernés sur les cartes de visualisation" }
  { key:"#TR_CONFIG_BREWERY_REQUIRES_WATER", text:"La brasserie nécessite un accès à l'eau" }
  { key:"#needs_water_access", text:"Cette brasserie a besoin d'un accès à l'eau" }
  { key:"#brewery_needs_water", text:"Cette brasserie a besoin d'eau avant de pouvoir brasser de la bière" }
  { key:"#TR_CONFIG_CARTPUSHERS_YIELD_BY_ID", text:"Les charretiers livrent selon l'identifiant de l'ouvrier" }
  { key:"#TR_CONFIG_REBALANCE_WORKSHOP_OUTPUT", text:"La production des ateliers dépend de la difficulté" }
  { key:"#TR_CONFIG_SPHINX_ARTISANS", text:"Le Sphinx est peint par les artisans après la taille (original : taille seulement)" }
  { key:"#TR_CONFIG_CHARIOTS_WORKSHOP_NEEDS_WEAPONS", text:"L'atelier de chars nécessite aussi des armes (l'original n'utilise que du bois)" }
  { key:"#TR_CONFIG_PREVENT_DELETE_NEAR_BURNING_RUINS", text:"Empêcher la démolition des bâtiments près des ruines en feu" }
  { key:"#TR_CONFIG_DISABLE_NILOMETER_POPUPS", text:"Désactiver les messages de prévision de crue du nilomètre" }
  { key:"#TR_CONFIG_ENHANCED_NILOMETER", text:"Amélioré : affichage du nilomètre (qualité de la crue, phase, infos sur la plaine inondable)" }
  { key:"#TR_CONFIG_ENHANCED_SHRINE_INFO", text:"Amélioré : afficher la description des sanctuaires dans la fenêtre d'examen" }
  { key:"#flood_phase_imminent", text:"Crue imminente" }
  { key:"#flood_phase_flooding", text:"Crue en cours" }
  { key:"#flood_phase_inundated", text:"Inondé" }
  { key:"#flood_phase_contracting", text:"Décrue" }
  { key:"#flood_phase_resting", text:"Repos après la crue" }
  { key:"#flood_phase_farmable", text:"Plaine inondable cultivable" }
  { key:"#nilometer_last_prefix", text:"Dernière crue :" }
  { key:"#nilometer_hud_tooltip", text:"Nilomètre — prévision de la prochaine crue et phase actuelle de la plaine inondable" }
  { key:"#TR_CONFIG_HEADER_SCENARIO_CHANGES", text:"Changer de scénario" }
  { key:"#TR_CONFIG_HEADER_RESOURCES", text:"Changer les ressources" }
  { key:"#TR_CONFIG_ANIMALS", text:"Changer les animaux" }
  { key:"#TR_CONFIG_FLOTSAM", text:"Débris" }
  { key:"#TR_GAMEPLAY_GOD_DISABLED", text:"Dieu désactivé" }
  { key:"#TR_HOTKEY_QUICKSAVE", text:"Sauvegarde rapide" }
  { key:"#TR_HOTKEY_QUICKLOAD", text:"Chargement rapide" }
  { key:"#quicksave_ok", text:"Sauvegarde rapide effectuée" }
  { key:"#quickload_ok", text:"Chargement rapide effectué" }
  { key:"#quicksave_missing", text:"Aucune sauvegarde rapide" }
  { key:"#quicksave_failed", text:"Échec de la sauvegarde rapide" }
  { key:"#quickload_failed", text:"Échec du chargement rapide" }
  { key:"#TR_HOTKEY_COPY_BUILD", text:"Copier le bâtiment sous le curseur" }
  { key:"#grain_stocks_none", text:"Cette maison n'a plus de réserves de grain" }
  { key:"#grain_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de grain" }
  { key:"#grain_stocks_medium", text:"Cette maison a assez de grain pour au moins le mois à venir" }
  { key:"#grain_stocks_high", text:"Cette maison n'a aucun problème pour obtenir le grain dont elle a besoin" }
  { key:"#chickpeas_stocks_none", text:"Cette maison n'a plus de réserves de pois chiches" }
  { key:"#chickpeas_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de pois chiches" }
  { key:"#chickpeas_stocks_medium", text:"Cette maison a assez de pois chiches pour au moins le mois à venir" }
  { key:"#chickpeas_stocks_high", text:"Cette maison n'a aucun problème pour obtenir les pois chiches dont elle a besoin" }
  { key:"#pomegranates_stocks_none", text:"Cette maison n'a plus de réserves de grenades" }
  { key:"#pomegranates_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de grenades" }
  { key:"#pomegranates_stocks_medium", text:"Cette maison a assez de grenades pour au moins le mois à venir" }
  { key:"#pomegranates_stocks_high", text:"Cette maison n'a aucun problème pour obtenir les grenades dont elle a besoin" }
  { key:"#figs_stocks_none", text:"Cette maison n'a plus de réserves de figues" }
  { key:"#figs_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de figues" }
  { key:"#figs_stocks_medium", text:"Cette maison a assez de figues pour au moins le mois à venir" }
  { key:"#figs_stocks_high", text:"Cette maison n'a aucun problème pour obtenir les figues dont elle a besoin" }
  { key:"#meat_stocks_none", text:"Cette maison n'a plus de réserves de viande" }
  { key:"#meat_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de viande" }
  { key:"#meat_stocks_medium", text:"Cette maison a assez de viande pour au moins le mois à venir" }
  { key:"#meat_stocks_high", text:"Cette maison n'a aucun problème pour obtenir la viande dont elle a besoin" }
  { key:"#game_stocks_none", text:"Cette maison n'a plus de réserves de gibier" }
  { key:"#game_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de gibier" }
  { key:"#game_stocks_medium", text:"Cette maison a assez de gibier pour au moins le mois à venir" }
  { key:"#game_stocks_high", text:"Cette maison n'a aucun problème pour obtenir le gibier dont elle a besoin" }
  { key:"#pottery_stocks_none", text:"Cette maison n'a plus de réserves de poteries" }
  { key:"#pottery_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de poteries" }
  { key:"#pottery_stocks_medium", text:"Cette maison a assez de poteries pour au moins le mois à venir" }
  { key:"#pottery_stocks_high", text:"Cette maison n'a aucun problème pour obtenir les poteries dont elle a besoin" }
  { key:"#jewelry_stocks_none", text:"Cette maison n'a plus de réserves de bijoux" }
  { key:"#jewelry_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de bijoux" }
  { key:"#jewelry_stocks_medium", text:"Cette maison a assez de bijoux pour au moins le mois à venir" }
  { key:"#jewelry_stocks_high", text:"Cette maison n'a aucun problème pour obtenir les bijoux dont elle a besoin" }
  { key:"#linen_stocks_none", text:"Cette maison n'a plus de réserves de lin" }
  { key:"#linen_stocks_low", text:"Cette maison aura bientôt épuisé ses maigres réserves de lin" }
  { key:"#linen_stocks_medium", text:"Cette maison a assez de lin pour au moins le mois à venir" }
  { key:"#linen_stocks_high", text:"Cette maison n'a aucun problème pour obtenir le lin dont elle a besoin" }
  { key:"#empty_housing_vacant", text:"Personne n'habite ici." }
  { key:"#irrigation_none", text:"Cette terre n'est pas irriguée" }
  { key:"#irrigation_low", text:"Cette terre est peu irriguée" }
  { key:"#irrigation_medium", text:"Cette terre est moyennement irriguée" }
  { key:"#irrigation_high", text:"Cette terre est bien irriguée" }
  { key:"#overlay_water_crossings_ferry", text:"Traversée en bac" }
  { key:"#overlay_water_crossings_bridge", text:"Traversée par pont" }
  { key:"#overlay_city_defenses_structure", text:"Structure de défense de la cité" }
  { key:"#overlay_hide_cliffs_hint", text:"Les falaises sont temporairement aplanies" }
  { key:"#overlay_grain", text:"Céréales" }
  { key:"#overlay_chickpeas", text:"Pois chiches" }
  { key:"#overlay_pomegranates", text:"Grenades" }
  { key:"#overlay_figs", text:"Figues" }
  { key:"#overlay_meat", text:"Viande" }
  { key:"#overlay_game", text:"Gibier" }
  { key:"#overlay_pottery", text:"Poterie" }
  { key:"#overlay_jewelry", text:"Bijoux" }
  { key:"#overlay_linen", text:"Toile" }
  { key:"#overlay_beer", text:"Bière" }
  { key:"#overlay_disease", text:"Maladie" }
  { key:"#overlay_infected_housing", text:"Epidémie" }
  { key:"#overlay_malaria", text:"Malaria" }
  { key:"#overlay_water_crossings", text:"Gués" }
  { key:"#overlay_empty_housing", text:"Logement vide" }
  { key:"#overlay_irrigation", text:"Irrigation" }
  { key:"#overlay_city_defenses", text:"Défenses" }
  { key:"#overlay_hide_cliffs", text:"Falaises off" }
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_LINEN", text:"Résidences réclamant du lin" }
  { key:"#TR_ADVISOR_RESIDENCES_DEMANDING_BEER", text:"Résidences réclamant de la bière" }
  { key:"#main_menu_mods", text:"Mods" }
  { key:"#main_menu_editor", text:"Éditeur" }
  { key:"#main_menu_free_play", text:"Partie libre" }
  { key:"#advisor_imperial_political_overseer_for", text:"Conseiller politique pour" }
  { key:"#warship_moving_to_position", text:"En route vers la position" }
  { key:"#warship_moving_to_position_text", text:"Le navire se dirige vers la position indiquée et y restera jusqu'à nouvel ordre." }
  { key:"#main_menu_update_downloading", text:"Téléchargement de la mise à jour..." }
  { key:"#main_menu_update_opening_page", text:"Ouverture de la page de téléchargement..." }
  { key:"#main_menu_update_now", text:"mettre à jour" }
  { key:"#main_menu_update_later", text:"plus tard" }
  { key:"#main_menu_loading_commits", text:"Chargement des derniers commits..." }
  { key:"#main_menu_new_build", text:"Nouvelle version : ${commit} (vous avez ${local})" }
  { key:"#main_menu_updated", text:"À jour" }
  { key:"#main_menu_build_up_to_date", text:"Version ${build} (à jour)" }
  { key:"#message_dialog_distant_battle", text:"Bataille distante" }
  { key:"#mods_window_title", text:"Mods" }
  { key:"#mods_window_unpack_scripts", text:"Extraire les scripts" }
  { key:"#mods_window_refresh_list", text:"Actualiser la liste" }
  { key:"#mods_window_hint", text:"Clic droit pour quitter, double-clic pour activer/désactiver un mod" }
  { key:"#records_not_played_yet", text:"pas encore joué" }
  { key:"#report_bug_title", text:"Signaler un bug" }
  { key:"#report_bug_field_title", text:"Titre" }
  { key:"#report_bug_field_description", text:"Description" }
  { key:"#report_bug_submit_question", text:"Envoyer ?" }
  { key:"#report_bug_error_no_title", text:"Veuillez saisir un titre." }
  { key:"#report_bug_error_short_description", text:"Veuillez rédiger une description (au moins 10 caractères)." }
  { key:"#report_bug_sending", text:"Envoi..." }
  { key:"#report_bug_sent", text:"Signalé ! Merci." }
  { key:"#report_bug_error", text:"Erreur :" }
  { key:"#report_bug_tooltip", text:"Signaler un bug" }
  { key:"#scenario_selection_file_schema", text:"Schéma de fichier :" }
  { key:"#features_god_enabled", text:"Dieu activé" }
  { key:"#features_city_allow", text:"Autorisé dans la cité" }
  { key:"#features_prev_page", text:"Préc." }
  { key:"#features_next_page", text:"Suiv." }
  { key:"#mission2_store_figs", text:"Construire un grenier et le remplir de figues." }
  { key:"#message_population_title", text:"Cap de population" }
  { key:"#message_population_100", text:"100 personnes se sont installées dans votre village" }
  { key:"#message_population_500", text:"Votre petite ville compte désormais cinq cents habitants" }
  { key:"#message_population_1000", text:"Mille personnes vivent désormais dans votre cité." }
  { key:"#message_population_2000", text:"Avec deux mille habitants, votre cité gagne en importance." }
  { key:"#message_population_3000", text:"La population de votre cité atteint trois mille habitants pour la première fois de son histoire." }
  { key:"#message_population_5000", text:"Votre cité devient importante. Cinq mille personnes y vivent désormais." }
  { key:"#message_population_10000", text:"Avec dix mille habitants, votre cité fait partie des plus grandes d'Égypte." }
  { key:"#message_population_15000", text:"Les nouvelles cités peuvent rivaliser avec la vôtre, qui compte désormais quinze mille citoyens." }
  { key:"#message_population_20000", text:"Les autres gouverneurs et nomarques sont impressionnés : votre cité abrite vingt mille personnes !" }
  { key:"#message_population_25000", text:"Les quelques immigrants qui ont fondé votre cité il y a tant d'années n'auraient jamais imaginé qu'elle compterait vingt-cinq mille habitants !" }
  { key:"#mission0_goal_create_housing", text:"Construire des maisons." }
  { key:"#mission0_goal_build_granary", text:"Construire un grenier et le remplir de gibier." }
  { key:"#mission1_goal_build_mines", text:"Extraire de l'or." }
  { key:"#mission1_goal_build_temples", text:"Eriger des temples et des sanctuaires en l'honneur de Bastet." }
  { key:"#mission1_goal_build_entertainment", text:"Construire des étals et des écoles de jongleurs." }
  { key:"#exit_this_panel", text:"Quitter ce panneau" }
  { key:"#display_options_title", text:"Affichage" }
  { key:"#display_options_ui_scale", text:"Échelle de l'interface" }
  { key:"#display_options_restart_required", text:"Redémarrez le jeu pour appliquer correctement l'échelle de l'interface." }
  { key:"#popup_dialog_quit", text:"Quitter" }
  { key:"#popup_dialog_open_trade", text:"Ouvrir une route de commerce" }
  { key:"#popup_dialog_send_goods", text:"Distribuer les biens ?" }
  { key:"#popup_dialog_not_enough_goods", text:"Requête du pharaon" }
  { key:"#popup_dialog_no_legions_available", text:"Requête du pharaon" }
  { key:"#popup_dialog_no_legions_selected", text:"Requête du pharaon" }
  { key:"#popup_dialog_send_troops", text:"Requête du pharaon" }
  { key:"#popup_dialog_delete_fort", text:"Destruction d'un fort" }
  { key:"#popup_dialog_delete_bridge", text:"Destruction d'un pont" }
  { key:"#popup_dialog_quit_without_saving", text:"Quitter" }
  { key:"#popup_dialog_map_file_missing", text:"Fichier de carte manquant" }
  { key:"#exit_without_saving", text:"Quitter sans enregistrer ?" }
  { key:"#popup_dialog_no_festival_square", text:"Fête : pas de place des fêtes" }
  { key:"#popup_dialog_delete_dynasty", text:"Supprimer cette dynastie ?" }
  { key:"#popup_dialog_no_dynasty", text:"Aucune dynastie" }
  { key:"#popup_dialog_no_player_name", text:"Veuillez saisir un nom de famille." }
  { key:"#replay_mission", text:"Rejouer la mission" }
  { key:"#mission_won_culture_rating", text:"Niveau final de culture" }
  { key:"#mission_won_prosperity_rating", text:"Niveau final de prospérité" }
  { key:"#mission_won_kingdom_rating", text:"Niveau final de royaume" }
  { key:"#mission_won_population", text:"Population totale" }
  { key:"#mission_won_monument_rating", text:"Niveau final de monument" }
  { key:"#ui_gift_to_kingdome_window_title", text:"Faire une offrande au peuple d'Egypte" }
  { key:"#ui_unable_to_fulfill_request", text:"Impossible de satisfaire la requête." }
  { key:"#ui_gift_time_since_last", text:"Pas de cadeau depuis :" }
  { key:"#ui_gift_label_modest", text:"Modeste :" }
  { key:"#ui_gift_label_generous", text:"Généreux :" }
  { key:"#ui_gift_label_lavish", text:"Somptueux :" }
  { key:"#ui_gift_dispatch_modest", text:"Expédier un cadeau modeste" }
  { key:"#ui_gift_dispatch_generous", text:"Expédier un cadeau généreux" }
  { key:"#ui_gift_dispatch_lavish", text:"Expédier un cadeau somptueux" }
  { key:"#ui_gift_cannot_afford_savings", text:"Vous n'avez pas assez d'économies personnelles pour faire une offrande pour l'Egypte. Essayez de vous accorder un salaire plus élevé !" }
  { key:"#ui_mission_choice_prompt", text:"Cliquez sur une cité" }
  { key:"#granary_info_title", text:"Grenier" }
  { key:"#granary_no_road_access", text:"ATTENTION. Ce bâtiment doit être situé à proximité d'une route." }
  { key:"#granary_kingdom_supplies_grain", text:"Ce grenier est inutile. L'Egypte pourvoie notre cité en céréales. Tous nos produits alimentaires sont placés directement dans les entrepôts disponibles." }
  { key:"#granary_storing", text:"Stockage" }
  { key:"#granary_space_for", text:"Espace pour" }
  { key:"#granary_units", text:"unités." }
  { key:"#chief_overseer", text:"Responsable" }
  { key:"#chief_adv_sentiment", text:"Opinion" }
  { key:"#chief_adv_migration", text:"Migration" }
  { key:"#chief_adv_workers", text:"Emploi" }
  { key:"#chief_adv_foodstocks", text:"Nourriture" }
  { key:"#chief_adv_foodconsumption", text:"Denrée (Prod.)" }
  { key:"#chief_adv_health", text:"Hygiène" }
  { key:"#chief_adv_religion", text:"Religion" }
  { key:"#chief_adv_finance", text:"Finances" }
  { key:"#chief_adv_crime", text:"Criminalité" }
  { key:"#chief_adv_military", text:"Militaire" }
  { key:"#chief_adv_kingdom", text:"Royaume" }
  { key:"#chief_adv_nilometr", text:"Nilomètre" }
  { key:"#trade_overseer", text:"Chef du commerce" }
  { key:"#building_have_no_access", text:"ATTENTION. Ce bâtiment doit être situé à proximité d'une route." }
  { key:"#bazaar_info_title", text:"Bazar" }
  { key:"#well_info_title", text:"Puits" }
  { key:"#well_info_necessary", text:"Les citoyens qui ne se font pas livrer leur eau peuvent la tirer de puits. Cependant, les quartiers ne disposant que de puits ne sont pas les plus recherchés." }
  { key:"#well_info_unneeded_fountain", text:"Ce puits est inutile, car toutes les maisons qu'il dessert sont alimentées par un point d'eau." }
  { key:"#well_info_unneeded_no_houses", text:"Ce puits est inutile car aucune maison ne se trouve à proximité." }
  { key:"#visit_rating_advisor", text:"Consulter le chef des niveaux" }
  { key:"#hunting_lodge", text:"Pavillon de chasse" }
  { key:"#hunting_lodge_info", text:"C'est là que les chasseurs rassemblent le gibier qu'ils ont chassé dans les environs. Le gibier est ensuite distribué aux entrepôts ou aux greniers locaux." }
  { key:"#hunting_lodge_production_is", text:"Production à" }
  { key:"#hunting_lodge_complete", text:"terminée." }
  { key:"#hunting_lodge_mothballed", text:"La production de poteries a été interrompue sur ordre du chef du commerce." }
  { key:"#hunting_lodge_no_workers", text:"Ce pavillon n'emploie personne. La chasse est annulée." }
  { key:"#hunting_lodge_workers_full", text:"Ce pavillon dispose de toute la main-d'œuvre nécessaire. Les chasseurs traquent tout le gibier qu'ils trouvent." }
  { key:"#hunting_lodge_workers_below_max", text:"Ce pavillon fonctionne en dessous de sa capacité maximale. La collecte de nourriture sera par conséquent ralentie." }
  { key:"#hunting_lodge_workers_understaffed", text:"Ce pavillon ne dispose pas d'une main-d'œuvre suffisante. La collecte de viande est plus lente que prévu." }
  { key:"#hunting_lodge_workers_few", text:"Seuls quelques employés travaillent ici. La collecte de viande est donc véritablement lente." }
  { key:"#hunting_lodge_workers_hardly", text:"Seuls quelques employés travaillent ici. On ne chasse donc que très peu d'animaux. La saison pourrait être extrêmement rude et sèche." }
  { key:"#hunting_lodge_hunters_seeking", text:"Les chasseurs de ce pavillon sont à la recherche de proies." }
  { key:"#hunting_lodge_too_far", text:"Le transport de la viande jusqu'au pavillon est trop long. Il devrait se trouver à proximité du terrain de chasse." }
  { key:"#hunting_lodge_stored_meat", text:"Viande stockée," }
  { key:"#gardens_describe", text:"Un petit coin de calme et de verdure pour qui veut s'isoler du vacarme de la cité. Tout le monde apprécie la présence d'un jardin dans son voisinage." }
  { key:"#popup_dialog_proceed", text:"Continuer ?" }
  { key:"#autosave_slots", text:"Emplacements d'auto-sauvegarde" }
  { key:"#immigration_people_wont_come", text:"Les gens ne veulent pas venir dans votre cité" }
  { key:"#abu_simbel_not_demolishable", text:"Abou Simbel ne peut pas être démoli" }
  { key:"#figure_scriber", text:"Scribe" }
  { key:"#pharaoh_inspecting_city", text:"Je marche parmi mon peuple. Qu'il voie son Pharaon." }
  { key:"#pharaoh_disease_risk", text:"La fièvre dans mes rues ? Mes médecins vont y remédier." }
  { key:"#pharaoh_no_food_in_city", text:"Des greniers vides sous mon règne ? C'est inacceptable." }
  { key:"#pharaoh_city_have_no_army", text:"Pas de forts ? Un seul raid et ma cité tombe. Levez les étendards." }
  { key:"#pharaoh_gods_are_angry", text:"Les dieux nous désapprouvent. Même Pharaon doit écouter les temples." }
  { key:"#pharaoh_low_entertainment", text:"Pas de fête depuis une éternité. Mon peuple mérite musique et vin." }
  { key:"#pharaoh_city_is_good", text:"Une belle cité. Ordre, pain et loyauté — comme il se doit." }
  { key:"#pharaoh_city_is_amazing", text:"Cette cité brille comme le Nil à l'aube. L'Égypte entière en est fière !" }
  { key:"#plagued_i_feel_awful", text:"Je me sens mal... tout tourne et me brûle." }
  { key:"#plagued_fever_spreads", text:"La fièvre se répand. Écartez-vous — je ne peux pas m'arrêter de marcher." }
  { key:"#plagued_no_food_in_city", text:"Des greniers vides et une fièvre brûlante. Quelle façon de mourir de faim." }
  { key:"#plagued_city_have_no_army", text:"Pas de forts ? La maladie aura cette cité avant n'importe quel ennemi." }
  { key:"#plagued_gods_are_angry", text:"Les dieux sont en colère. Est-ce leur malédiction qui rampe en moi ?" }
  { key:"#plagued_low_entertainment", text:"Pas de fête depuis une éternité... seulement des toux dans les rues." }
  { key:"#plagued_city_is_good", text:"La cité semblait aller bien. Pourquoi cette fièvre m'a-t-elle choisi ?" }
  { key:"#plagued_city_is_amazing", text:"On dit que c'est la meilleure cité — alors pourquoi je meurs dans ses rues ?" }
  { key:"#protestor_we_want_justice", text:"Nous voulons la justice ! Écoutez nos voix dans la rue !" }
  { key:"#protestor_tax_too_high", text:"Ces impôts nous saignent ! Ça suffit !" }
  { key:"#protestor_wages_too_low", text:"Nos salaires ne paient pas le pain. Un salaire juste, ou on reste là !" }
  { key:"#protestor_no_jobs", text:"Pas de travail, pas d'espoir — et vous voulez qu'on se taise ?" }
  { key:"#protestor_no_food_in_city", text:"Des greniers vides ! Combien de temps devrons-nous mourir de faim en silence ?" }
  { key:"#protestor_city_have_no_army", text:"Pas de forts ? On nous laisse sans défense et écrasés d'impôts !" }
  { key:"#protestor_gods_are_angry", text:"Même les dieux désapprouvent. Cette cité a perdu son chemin !" }
  { key:"#protestor_low_entertainment", text:"Pas de fêtes, seulement la faim et les impôts. Quelle vie est-ce là ?" }
  { key:"#protestor_city_is_good", text:"On dit que la cité va bien. Bien pour qui ?" }
  { key:"#protestor_city_is_amazing", text:"Une cité magnifique ? Dites-le aux ventres vides et aux bourses vides !" }
  { key:"#rioter_burn_it_down", text:"Brûlons tout ! Cette cité écoutera le feu !" }
  { key:"#rioter_tax_too_high", text:"Les percepteurs d'abord — puis le reste de votre jolie cité !" }
  { key:"#rioter_wages_too_low", text:"Affamez-nous avec des miettes et nous casserons ce que nous ne pouvons acheter !" }
  { key:"#rioter_no_jobs", text:"Pas de travail ? Alors on s'en fait un — avec des torches !" }
  { key:"#rioter_no_food_in_city", text:"Des greniers vides ! Nous prendrons ce qu'il nous faut dans vos réserves !" }
  { key:"#rioter_city_have_no_army", text:"Pas de forts ? Plus rien entre nous et le palais !" }
  { key:"#rioter_gods_are_angry", text:"Les dieux enragent — nous aussi ! Détruisons tout !" }
  { key:"#rioter_low_entertainment", text:"Pas de fêtes ? Voilà le spectacle — regardez les bâtiments tomber !" }
  { key:"#rioter_city_is_good", text:"Une bonne cité ? Bonne pour les riches. Pas pour nous !" }
  { key:"#rioter_city_is_amazing", text:"De superbes rues à brûler. Regardez-les flamber ce soir !" }
  { key:"#robber_maybe_stealing_will_get_attention", text:"Peut-être qu'en volant, on me remarquera enfin !" }
  { key:"#robber_i_take_what_i_want", text:"Je prends ce que je veux !" }
  { key:"#robber_more_profitable_than_other_jobs", text:"Plus rentable que les autres métiers de cette cité." }
  { key:"#robber_take_take_take", text:"Prendre, prendre, prendre !" }
  { key:"#robber_tax_too_high", text:"Les impôts vous dépouillent — moi, je dépouille le palais !" }
  { key:"#robber_wages_too_low", text:"Salaires trop bas ? Mes mains trouvent mieux payé." }
  { key:"#robber_no_jobs", text:"Pas de travail honnête ? Très bien. Le travail malhonnête paie." }
  { key:"#robber_no_food_in_city", text:"Des greniers vides ? L'or remplit toujours les poches." }
  { key:"#robber_city_have_no_army", text:"Pas de forts ? Les rues sont tranquilles pour un voleur discret." }
  { key:"#robber_gods_are_angry", text:"Les dieux en colère ? Parfait — on accusera le ciel, pas moi." }
  { key:"#robber_low_entertainment", text:"Pas de fêtes ? Voler, c'est mon divertissement." }
  { key:"#robber_city_is_good", text:"Jolie cité. Jolies bourses à alléger." }
  { key:"#robber_city_is_amazing", text:"La meilleure cité à dévaliser — des bourses bien pleines partout !" }
  { key:"#slave_break_our_chains", text:"Brisons nos chaînes ! Plus de maîtres !" }
  { key:"#slave_tax_too_high", text:"Ils vous taxent — ils nous fouettent. Révoltez-vous !" }
  { key:"#slave_wages_too_low", text:"Les hommes libres meurent de faim avec des miettes. Les esclaves prennent ce qu'il leur faut !" }
  { key:"#slave_no_jobs", text:"Pas de travail pour les hommes libres ? Alors qu'ils rejoignent la révolte !" }
  { key:"#slave_no_food_in_city", text:"Des greniers vides pendant que nous crevons de faim enchaînés. Assez !" }
  { key:"#slave_city_have_no_army", text:"Pas de forts ? Rien ne nous empêche d'atteindre le palais !" }
  { key:"#slave_gods_are_angry", text:"Même les dieux haïssent cette cité. Frappez avec nous !" }
  { key:"#slave_low_entertainment", text:"Pas de fêtes pour les esclaves — seulement la torche !" }
  { key:"#slave_city_is_good", text:"Bonne cité pour les hommes libres. Nous prenons notre part maintenant !" }
  { key:"#slave_city_is_amazing", text:"De superbes rues à libérer — ou à brûler !" }
  { key:"#soldier_no_enemies_sighted", text:"Aucun ennemi en vue. La garde est calme." }
  { key:"#soldier_ready_approaching_enemy", text:"Prêts ! L'ennemi approche — tenez la formation !" }
  { key:"#soldier_no_trouble_defeating_army", text:"Nous n'aurons aucun mal à vaincre cette armée." }
  { key:"#soldier_enemy_is_fierce", text:"Cet ennemi est redoutable. Tenez bon pour Pharaon !" }
  { key:"#soldier_disease_risk", text:"La fièvre dans les rangs. Dur de marcher avec les mains qui tremblent." }
  { key:"#soldier_no_food_in_city", text:"Des greniers vides ? Un soldat affamé se bat mal." }
  { key:"#soldier_gods_are_angry", text:"Les dieux semblent en colère. Mauvais présage avant la bataille." }
  { key:"#soldier_low_entertainment", text:"Pas de fête depuis une éternité. Même les soldats ont besoin d'un jour de repos." }
  { key:"#soldier_city_is_good", text:"Une cité solide. Elle mérite d'être défendue." }
  { key:"#soldier_city_is_amazing", text:"La meilleure cité que j'aie gardée. Pour Pharaon !" }
  { key:"#tower_sentry_no_enemies_sighted", text:"Aucun ennemi en vue. Le rempart est calme." }
  { key:"#tower_sentry_ready_approaching_enemy", text:"Prêts ! L'ennemi approche — tirez !" }
  { key:"#tower_sentry_no_trouble_defeating_army", text:"Depuis la tour, nous n'aurons aucun mal à vaincre cette armée." }
  { key:"#tower_sentry_enemy_is_fierce", text:"Cet ennemi est redoutable. Tenez le rempart pour Pharaon !" }
  { key:"#tower_sentry_disease_risk", text:"La fièvre sur les remparts. Dur de monter la garde avec les mains qui tremblent." }
  { key:"#tower_sentry_no_food_in_city", text:"Des greniers vides ? Une sentinelle affamée surveille mal." }
  { key:"#tower_sentry_gods_are_angry", text:"Les dieux semblent en colère. Mauvais présage pour la garde." }
  { key:"#tower_sentry_low_entertainment", text:"Pas de fête depuis une éternité. Même les sentinelles ont besoin d'un jour loin du rempart." }
  { key:"#tower_sentry_city_is_good", text:"Une cité solide. Elle mérite d'être gardée depuis cette tour." }
  { key:"#tower_sentry_city_is_amazing", text:"La meilleure cité que j'aie surveillée. Pour Pharaon !" }
  { key:"#stonemason_ready", text:"La pierre est prête. Élevons le monument !" }
  { key:"#stonemason_going_to_work", text:"En route pour le chantier — ces blocs ne vont pas se poser tout seuls." }
  { key:"#stonemason_working_ground", text:"Je pose la pierre sur un sol solide. Doucement." }
  { key:"#stonemason_working_wall", text:"Encore une assise de pierre sur le mur !" }
  { key:"#stonemason_work_complete", text:"Assez de travail pour l'instant. Retour à la guilde." }
  { key:"#stonemason_looking_for_work", text:"Je cherche le prochain endroit où poser la pierre." }
  { key:"#stonemason_disease_risk", text:"La fièvre sur le chantier. Dur de soulever la pierre avec les mains qui tremblent." }
  { key:"#stonemason_no_food_in_city", text:"Des greniers vides ? Un maçon affamé pose des assises de travers." }
  { key:"#stonemason_city_have_no_army", text:"Pas de forts ? Un seul raid et ce monument n'est plus que gravats." }
  { key:"#stonemason_gods_are_angry", text:"Les dieux semblent en colère. Même la bonne pierre se fend sous leur regard." }
  { key:"#stonemason_low_entertainment", text:"Pas de fête depuis une éternité. Même les maçons ont besoin d'un jour loin de l'échafaudage." }
  { key:"#stonemason_city_is_good", text:"Cette cité est solide ! De bonnes fondations pour de grands monuments." }
  { key:"#stonemason_city_is_amazing", text:"La meilleure cité pour laquelle j'aie bâti. Ces pierres tiendront pour l'éternité !" }
  { key:"#reed_to_the_marsh_i_march", text:"En route pour le marais !" }
  { key:"#reed_will_make_some_fine_papyrus", text:"Ces roseaux feront un excellent papyrus." }
  { key:"#reed_disease_risk", text:"La fièvre dans les marais. Dur de couper les roseaux avec les mains qui tremblent." }
  { key:"#reed_no_food_in_city", text:"Des greniers vides ? Un cueilleur de roseaux affamé fait des bottes de travers." }
  { key:"#reed_city_have_no_army", text:"Pas de forts ? Un seul raid et ces marais appartiendront aux envahisseurs." }
  { key:"#reed_gods_are_angry", text:"Les dieux semblent en colère. Même les bons roseaux se fanent sous leur regard." }
  { key:"#reed_low_entertainment", text:"Pas de fête depuis une éternité. Même les travailleurs des marais ont besoin d'un jour loin de la boue." }
  { key:"#reed_city_is_good", text:"Cette cité est solide ! De bons roseaux pour un beau papyrus." }
  { key:"#reed_city_is_amazing", text:"La meilleure cité pour laquelle j'aie récolté. Ces roseaux feront des rouleaux pour l'éternité !" }
  { key:"#noble_taking_a_stroll", text:"Une promenade tranquille. Que le petit peuple s'écarte." }
  { key:"#noble_returning_home", text:"Retour à mon manoir. Ces rues poussiéreuses fatiguent une personne de qualité." }
  { key:"#noble_disease_risk", text:"La fièvre dans les rues ? Tenez la populace loin de ma cour." }
  { key:"#noble_no_food_in_city", text:"Des greniers vides ? Un noble ne devrait jamais dîner d'excuses." }
  { key:"#noble_city_have_no_army", text:"Pas de forts ? Un seul raid et mon domaine part en cendres. Inacceptable." }
  { key:"#noble_gods_are_angry", text:"Les dieux semblent en colère. Ni le lin ni l'or ne peuvent soudoyer le ciel." }
  { key:"#noble_low_entertainment", text:"Pas de fête depuis une éternité. Un noble a besoin de musique, de vin et de spectacle." }
  { key:"#noble_city_is_good", text:"Une cité correcte. Mes voisins ont presque l'air respectables." }
  { key:"#noble_city_is_amazing", text:"La plus belle cité pour un manoir ! Même Pharaon envierait ces rues." }
  { key:"#mummy_risen", text:"Le sceau est brisé. Je marche de nouveau." }
  { key:"#mummy_walks_streets", text:"Ces rues connaîtront la malédiction." }
  { key:"#mummy_attacking", text:"La chair est tendre. Les bandelettes se souviennent comment frapper." }
  { key:"#mummy_disease_risk", text:"Votre cité sent déjà la tombe. Je me sens chez moi." }
  { key:"#mummy_no_food_in_city", text:"Des greniers vides ? Les vivants ont faim ; les morts endurent." }
  { key:"#mummy_city_have_no_army", text:"Pas de forts ? Alors plus rien ne me sépare de vos maisons." }
  { key:"#mummy_need_workers", text:"Si peu d'ouvriers... et tant de tombes encore vides." }
  { key:"#mummy_gods_are_angry", text:"Les dieux se détournent. Un temps parfait pour une malédiction." }
  { key:"#mummy_city_is_bad", text:"La faveur de Pharaon s'efface. Mes bandelettes se resserrent de joie." }
  { key:"#mummy_much_unemployment", text:"Des mains oisives ? Des âmes oisives ? Je peux me servir des deux." }
  { key:"#mummy_low_entertainment", text:"Pas de fêtes ? Alors ma procession fera l'affaire." }
  { key:"#mummy_city_is_good", text:"Une cité bien rangée. Dommage qu'elle doive retourner à la poussière." }
  { key:"#mummy_city_is_amazing", text:"Quelle gloire ! Je hanterai chacune de ces splendides rues." }
  { key:"#figure_barbarian_archer", text:"Archer barbare ennemi" }
  { key:"#figure_barbarian_sword", text:"Épéiste barbare ennemi" }
  { key:"#figure_barbarian_transport_ship", text:"Navire de transport barbare ennemi" }
  { key:"#figure_canaanite_archer", text:"Archer cananéen ennemi" }
  { key:"#figure_canaanite_sword", text:"Épéiste cananéen ennemi" }
  { key:"#figure_canaanite_transport_ship", text:"Navire de transport cananéen ennemi" }
  { key:"#figure_canaanite_war_ship", text:"Navire de guerre cananéen ennemi" }
  { key:"#figure_canaanite_chariot", text:"Char cananéen ennemi" }
  { key:"#figure_kushite_spearman", text:"Lancier koushite ennemi" }
  { key:"#figure_kushite_axeman", text:"Hachier koushite ennemi" }
  { key:"#figure_kushite_transport_ship", text:"Navire de transport koushite ennemi" }
  { key:"#figure_kushite_war_ship", text:"Navire de guerre koushite ennemi" }
  { key:"#figure_kushite_chariot", text:"Char koushite ennemi" }
  { key:"#figure_hittite_archer", text:"Archer hittite ennemi" }
  { key:"#figure_hittite_spearman", text:"Lancier hittite ennemi" }
  { key:"#figure_hittite_transport_ship", text:"Navire de transport hittite ennemi" }
  { key:"#figure_hittite_war_ship", text:"Navire de guerre hittite ennemi" }
  { key:"#figure_hittite_chariot", text:"Char hittite ennemi" }
  { key:"#figure_persian_archer", text:"Archer perse ennemi" }
  { key:"#figure_persian_spearman", text:"Lancier perse ennemi" }
  { key:"#figure_persian_transport_ship", text:"Navire de transport perse ennemi" }
  { key:"#figure_persian_war_ship", text:"Navire de guerre perse ennemi" }
  { key:"#figure_persian_chariot", text:"Char perse ennemi" }
  { key:"#figure_assyrian_archer", text:"Archer assyrien ennemi" }
  { key:"#figure_assyrian_sword", text:"Épéiste assyrien ennemi" }
  { key:"#figure_assyrian_transport_ship", text:"Navire de transport assyrien ennemi" }
  { key:"#figure_assyrian_war_ship", text:"Navire de guerre assyrien ennemi" }
  { key:"#figure_assyrian_chariot", text:"Char assyrien ennemi" }
  { key:"#figure_egyptian_galera", text:"Galère égyptienne ennemie" }
  { key:"#figure_libian_archer", text:"Archer libyen ennemi" }
  { key:"#figure_libian_swordman", text:"Épéiste libyen ennemi" }
  { key:"#figure_libian_transport_ship", text:"Navire de transport libyen ennemi" }
  { key:"#figure_libian_war_ship", text:"Navire de guerre libyen ennemi" }
  { key:"#figure_libian_chariot", text:"Char libyen ennemi" }
  { key:"#figure_nubian_archer", text:"Archer nubien ennemi" }
  { key:"#figure_nubian_axeman", text:"Hachier nubien ennemi" }
  { key:"#figure_nubian_transport_ship", text:"Navire de transport nubien ennemi" }
  { key:"#figure_nubian_war_ship", text:"Navire de guerre nubien ennemi" }
  { key:"#figure_nubian_chariot", text:"Char nubien ennemi" }
  { key:"#figure_phoenician_spearman", text:"Lancier phénicien ennemi" }
  { key:"#figure_phoenician_swordman", text:"Épéiste phénicien ennemi" }
  { key:"#figure_phoenician_transport_ship", text:"Navire de transport phénicien ennemi" }
  { key:"#figure_phoenician_war_ship", text:"Navire de guerre phénicien ennemi" }
  { key:"#figure_phoenician_chariot", text:"Char phénicien ennemi" }
  { key:"#figure_roman_archer", text:"Archer romain ennemi" }
  { key:"#figure_roman_legioner", text:"Légionnaire romain ennemi" }
  { key:"#figure_roman_transport_ship", text:"Navire de transport romain ennemi" }
  { key:"#figure_roman_war_ship", text:"Navire de guerre romain ennemi" }
  { key:"#figure_roman_chariot", text:"Char romain ennemi" }
  { key:"#figure_seapeople_archer", text:"Archer des Peuples de la mer ennemi" }
  { key:"#figure_seapeople_swordman", text:"Épéiste des Peuples de la mer ennemi" }
  { key:"#figure_seapeople_transport_ship", text:"Navire de transport des Peuples de la mer ennemi" }
  { key:"#figure_seapeople_war_ship", text:"Navire de guerre des Peuples de la mer ennemi" }
  { key:"#figure_seapeople_chariot", text:"Char des Peuples de la mer ennemi" }
  { key:"#figure_hyksos_archer", text:"Archer hyksos ennemi" }
  { key:"#figure_hyksos_swordman", text:"Épéiste hyksos ennemi" }
  { key:"#figure_hyksos_transport_ship", text:"Navire de transport hyksos ennemi" }
  { key:"#figure_hyksos_war_ship", text:"Navire de guerre hyksos ennemi" }
  { key:"#figure_hyksos_chariot", text:"Char hyksos ennemi" }
  { key:"#house_low_desirabilty", text:"Cette maison va bientôt régresser. L'attrait décroissant pour ce secteur entraîne le déclin de cette demeure." }
  { key:"#lacks_access_primitive_water", text:"Cette maison va bientôt régresser, car elle n'a même pas accès à un point d'eau rudimentaire." }
  { key:"#not_visited_by_water_carrier", text:"Cette maison va bientôt régresser, car elle n'est même pas visitée par un porteur d'eau" }
  { key:"#no_entertainment_to_be_found", text:"Cette maison va bientôt régresser, car il n'y a rien pour se divertir dans ce secteur." }
  { key:"#any_entertainment_in_location", text:"Cette maison va bientôt régresser, car il y a très peu de distractions dans ce secteur." }
  { key:"#too_little_entertainment_in_location", text:"Cette maison va bientôt régresser, car il n'y a pas assez de distractions dans ce secteur." }
  { key:"#some_entertainment_found_location", text:"Cette maison va bientôt régresser. Il est possible de se divertir dans ce secteur, mais pas suffisamment." }
  { key:"#good_entertainment_found_location", text:"Cette maison va bientôt régresser. Il est possible de se divertir dans ce secteur, mais cela manque un peu de variété." }
  { key:"#excellent_entertainment_found_location", text:"Cette maison va bientôt régresser. L'endroit offre d'excellentes possibilités de divertissement, mais il est trop fréquenté et pas assez varié pour les scribes" }
  { key:"#one_food_type_need", text:"Cette maison va bientôt régresser, car elle n'a pas récemment reçu de nourriture par les bazars" }
  { key:"#two_food_types_need", text:"Cette maison va bientôt régresser, car elle n'a actuellement accès qu'à une sorte de nourriture par son bazar local. De quoi décourager les plus riches citoyens." }
  { key:"#three_food_types_need", text:"Cette maison va bientôt régresser, car elle n'a actuellement accès qu'à deux sortes de nourriture par son bazar local. De quoi décourager les scribes." }
  { key:"#no_bazaar_access", text:"Cette maison va bientôt régresser, car elle a perdu tout accès à un bazar." }
  { key:"#low_bazaar_access", text:"Cette maison va bientôt régresser. Bien qu'elle ait accès à un bazar, ce dernier n'est pas suffisamment alimenté en nourriture." }
  { key:"#lost_basic_educational_facilities ", text:"Cette maison va bientôt régresser, car elle n'a plus ni école de scribes, ni bibliothèque." }
  { key:"#lost_access_to_library ", text:"Cette maison va bientôt régresser. Son accès à l'éducation a diminué car elle a perdu son accès à une bibliothèque." }
  { key:"#lost_access_to_scribal_school ", text:"Cette maison va bientôt régresser. Son accès à l'éducation a diminué car elle a perdu son accès à une école de scribes." }
  { key:"#lost_access_to_higher_education ", text:"Cette maison va bientôt régresser. Son accès à l'éducation, auparavant excellent, a diminué car elle a perdu tout accès à l'éducation supérieure." }
  { key:"#no_access_to_magistrates", text:"Cette maison va bientôt régresser, car elle n'a pas accès à des magistrats de palais de justice." }
  { key:"#run_out_of_pottery", text:"Cette maison va bientôt régresser. Elle ne dispose plus de poteries, et les livraisons de son bazar local sont irrégulières." }
  { key:"#lost_all_access_to_local_religious", text:"Cette maison va bientôt régresser, car elle a perdu tout accès à des lieux de culte." }
  { key:"#access_to_one_local_religious", text:"Cette maison va bientôt régresser. Son accès à des lieux de culte a été réduit au point de ne pouvoir adorer qu'une seule divinité." }
  { key:"#access_to_two_local_religious", text:"Cette maison va bientôt régresser. Son accès à des lieux de culte a été réduit et seuls les temples de deux divinités sont maintenant à proximité." }
  { key:"#lost_dentist_access", text:"Cette maison va bientôt régresser, car elle a perdu tout accès à un dentiste." }
  { key:"#no_access_to_physician", text:"Cette maison va bientôt régresser, car elle bénéficie désormais d'une hygiène déplorable. Non seulement elle n'a pas accès à un lieu d'embaumement, mais son accès à un médecin est loin d'être parfait." }
  { key:"#no_access_to_mortuary", text:"Cette maison va bientôt régresser, car elle a perdu toute hygiène. Elle a accès à un nombre suffisant de médecins, mais à aucune salle des embaumeurs." }
  { key:"#hard_access_to_physician", text:"Cette maison va bientôt régresser, car elle a perdu toute hygiène. Elle a accès à une salle des embaumeurs, mais les médecins se font rare." }
  { key:"#run_out_of_linen", text:"Cette maison va bientôt régresser, car elle n'a plus de toile et les livraisons de son bazar local sont irrégulières." }
  { key:"#run_out_of_beer", text:"Cette maison va bientôt régresser, car elle n'a plus de bière et son bazar local ne reçoit que des livraisons irrégulières." }
  { key:"#cannot_evolve_cause_low_desirability", text:"Cette demeure ne peut pas évoluer tant que les environs n'ont pas suffisamment d'attrait." }
  { key:"#cannot_evolve_most_primitive_water_source", text:"Cette maison ne peut pas évoluer tant qu'elle n'a pas accès à une source d'eau de base." }
  { key:"#cannot_evolve_access_to_water_carrier", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès aux services d'un porteur d'eau" }
  { key:"#cannot_evolve_no_entertainment", text:"Cette maison ne peut pas évoluer, car il n'y a rien pour se divertir dans ce secteur." }
  { key:"#cannot_evolve_hardly_any_entertainment", text:"Cette maison ne peut pas évoluer, car il y a très peu de distractions dans ce secteur." }
  { key:"#cannot_evolve_too_little_entertainment", text:"Cette maison ne peut pas évoluer, car il n'y a pas assez de distractions dans ce secteur." }
  { key:"#cannot_evolve_some_entertainment", text:"Cette maison ne peut pas évoluer. Il est possible de se divertir dans ce secteur, mais pas suffisamment." }
  { key:"#cannot_evolve_good_entertainment", text:"Cette maison ne peut pas évoluer. Il est possible de se divertir dans ce secteur, mais cela manque un peu de variété." }
  { key:"#cannot_evolve_excellent_entertainment", text:"Cette maison ne peut pas évoluer. L'endroit offre d'excellentes possibilités de divertissement, mais il est trop fréquenté et pas assez varié pour les scribes." }
  { key:"#cannot_evolve_needs_supply_food", text:"Cette maison ne peut pas évoluer, car elle doit recevoir de la nourriture d'un bazar local." }
  { key:"#cannot_evolve_needs_second_type_food", text:"Cette maison ne peut pas évoluer, car il lui faut une deuxième sorte de nourriture, fournie par un bazar local, pour que des Egyptiens plus riches veuillent s'y installer." }
  { key:"#cannot_evolve_needs_third_type_food", text:"Cette maison ne peut pas évoluer, car il lui faut une troisième sorte de nourriture, fournie par un bazar local, pour que des Egyptiens d'une classe supérieure veuillent s'y installer." }
  { key:"#cannot_evolve_needs_access_bazaar", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès à un bazar local." }
  { key:"#cannot_evolve_needs_low_access_bazaar", text:"Cette maison ne peut pas évoluer. Bien qu'elle ait accès à un bazar local, ce dernier n'est pas régulièrement approvisionné en nourriture." }
  { key:"#cannot_evolve_needs_basic_education", text:"Cette maison ne peut pas évoluer, car elle n'a accès ni à une école de scribes, ni à une bibliothèque." }
  { key:"#cannot_evolve_needs_library_education", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès à une bibliothèque." }
  { key:"#cannot_evolve_needs_school_education", text:"Cette maison ne peut pas évoluer, car elle doit avoir accès à une école de scribes." }
  { key:"#cannot_evolve_needs_academy_education", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès à une académie militaire." }
  { key:"#cannot_evolve_needs_magistrate", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès à un magistrat d'un palais de justice local." }
  { key:"#cannot_evolve_needs_pottery", text:"Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de poteries de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
  { key:"#cannot_evolve_needs_religious", text:"Cette maison ne peut pas évoluer, car elle n'a accès à aucun lieu de culte." }
  { key:"#cannot_evolve_needs_religious_two_gods", text:"Cette maison ne peut pas évoluer, car elle a uniquement accès aux temples dédiés à une seule divinité. Les habitants des classes supérieures désirent adorer plusieurs divinités." }
  { key:"#cannot_evolve_needs_religious_three_gods", text:"Cette maison ne peut pas évoluer, car elle a uniquement accès aux temples dédiés à deux divinités. Les habitants des classes supérieures désirent adorer plus de divinités." }
  { key:"#cannot_evolve_needs_dentist", text:"Cette maison ne peut pas évoluer, car elle n'a pas accès à un dentiste." }
  { key:"#cannot_evolve_needs_physician", text:"Cette maison ne peut pas évoluer, car elle n'a pas d'hygiène effective. Elle n'a en effet accès ni à un médecin, ni à une salle des embaumeurs." }
  { key:"#cannot_evolve_needs_mortuary_has_physician", text:"Cette maison ne peut pas évoluer, car elle doit avoir plus d'hygiène. Elle a accès à un nombre suffisant de médecins, mais à aucune salle des embaumeurs." }
  { key:"#cannot_evolve_needs_physician_mortuary_has", text:"Cette maison ne peut pas évoluer, car elle doit avoir plus d'hygiène. Elle a accès à une salle des embaumeurs, mais il faut construire une pharmacie dans les environs." }
  { key:"#cannot_evolve_needs_linen", text:"Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de toile de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
  { key:"#cannot_evolve_needs_beer", text:"Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de bières de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
  { key:"#cannot_evolve_needs_jewlery", text:"Cette maison ne peut pas évoluer. Elle doit recevoir des articles de luxe comme" }
  { key:"#trader_from", text:"de" }
  { key:"#trader_capacity", text:"Capacité" }
  { key:"#trader_buys", text:"Achats" }
  { key:"#trader_sells", text:"Ventes" }
  { key:"#trader_bought", text:"Acheté" }
  { key:"#trader_sold", text:"Vendu" }
  { key:"#trader_returning_home", text:"Sur le retour" }
  { key:"#trader_trading_goods", text:"En train de commercer" }
  { key:"#trader_heading_storage", text:"En direction des entrepôts de la cité" }
  { key:"#trader_nothing_to_trage", text:"Rien à échanger ici, juste de passage" }
  { key:"#trader_ship_waiting_free_dock", text:"A jeté l'ancre en attente d'un dock libre." }
  { key:"#trader_ship_docking_trading", text:"A quai, en train d'acheter et de revendre des biens." }
  { key:"#trader_ship_returning_home", text:"Sur le retour" }
  { key:"#trader_ship_sailing_dock", text:"En route vers les docks de la cité." }
  { key:"#building_employee", text:"employé" }
  { key:"#building_employee_needed", text:"requis" }
  { key:"#AD", text:"aprJC" }
  { key:"#BC", text:"avJC" }
  { key:"#trader_city_not_trades", text:"Notre long et dangereux périple n'a servi à rien ! Cette cité ne pratique aucune activité commerciale." }
  { key:"#trader_buy_for_less_sell_for_more", text:"Acheter bas, revendre haut. Telle est ma devise !" }
  { key:"#trader_its_my_life", text:"Une vraie vie de marchand s'offre à moi !" }
  { key:"#trader_i_ll_be_a_hero", text:"Je serai accueilli en héros lorsque je ramènerai ces marchandises dans ma terre natale." }
  { key:"#trader_you_talk_a_fine_bargain", text:"Tu es dur en affaire, l'ami. J'aurai du mal à faire mes frais." }
  { key:"#donkey_cicero_breathe", text:"Tant que je respire, j'espère. Et tant que je transporte des poteries." }
  { key:"#donkey_cicero_books", text:"Une pièce sans livres est comme un corps sans âme. Une caravane sans grain, c'est pire." }
  { key:"#donkey_cicero_garden", text:"Si tu as un jardin et une bibliothèque, tu as tout ce qu'il te faut. Moi, j'ai un bât. C'est presque pareil." }
  { key:"#donkey_cicero_gratitude", text:"La gratitude est la mère de toutes les vertus. Une carotte aiderait aussi." }
  { key:"#donkey_cicero_friendship", text:"L'amitié augmente le bonheur et diminue le malheur. Marcher moins vite que le marchand de tête aussi." }
  { key:"#donkey_cicero_money", text:"Rien n'est si solidement établi que l'argent ne puisse le détruire. Demandez à mes plaies de bât." }
  { key:"#donkey_cicero_memory", text:"La vie des morts réside dans la mémoire des vivants. Je me souviens encore de cette oasis." }
  { key:"#donkey_cicero_moderation", text:"Ne tombe jamais dans l'excès, que la modération soit ton guide. Surtout pour le poids de la cargaison." }
  { key:"#donkey_cicero_mistakes", text:"Tout homme peut se tromper, mais seul un idiot persiste dans son erreur. Je me suis trompé de chemin une fois. Une seule." }
  { key:"#donkey_cicero_history", text:"Ignorer ce qui s'est passé avant ta naissance, c'est rester toujours un enfant. Ou un âne. Attends." }
  { key:"#donkey_cicero_laws", text:"En temps de guerre, les lois se taisent. Pas les ânes. Hi-han." }
  { key:"#donkey_cicero_not_alone", text:"Nous ne sommes pas nés pour nous seuls. Évidemment. Moi, je suis né pour ce chargement." }
  { key:"#donkey_cicero_meta", text:"On me dit bête de somme, et pourtant je cite Cicéron. Qui est le philosophe, maintenant ?" }
  { key:"#donkey_cicero_runaway", text:"Je fuis, donc je suis. Cicéron comprendrait. Probablement." }
  { key:"#flotsam_plato_unexamined", text:"Une vie sans examen ne vaut pas d'être vécue. Un courant sans examen, c'est comme ça que j'ai atterri ici." }
  { key:"#flotsam_plato_cave", text:"Les prisonniers de la caverne ne voient que des ombres. Moi, je vois la berge — à l'envers." }
  { key:"#flotsam_plato_wise", text:"Les sages parlent parce qu'ils ont quelque chose à dire. Le bois flotté, lui, flotte." }
  { key:"#flotsam_plato_courage", text:"Le courage, c'est savoir ce qu'il ne faut pas craindre. Je ne crains pas le Nil. Je suis du Nil." }
  { key:"#flotsam_plato_knowledge", text:"Le savoir acquis par la contrainte ne tient pas. La cargaison non plus, apparemment." }
  { key:"#flotsam_plato_opinion", text:"L'opinion est l'intermédiaire entre le savoir et l'ignorance. Je suis l'intermédiaire entre le navire et la rive." }
  { key:"#flotsam_plato_love", text:"Au contact de l'amour, tout homme devient poète. Au contact d'un récif, tout navire devient épave." }
  { key:"#flotsam_plato_justice", text:"La justice réside d'abord dans le cœur des citoyens. Et aussi : le liège, ça aide." }
  { key:"#flotsam_plato_music", text:"La musique donne une âme à l'univers. Le Nil me donne une destination que je n'ai pas choisie." }
  { key:"#flotsam_plato_ignorance", text:"L'ignorance est la racine et la tige de tous les maux. Le mauvais calfatage aussi." }
  { key:"#flotsam_plato_excess", text:"L'excès provoque un changement dans le sens opposé. Demandez à ce tonneau." }
  { key:"#flotsam_plato_war", text:"Seuls les morts ont vu la fin de la guerre. Nous autres avons vu la fin de la coque." }
  { key:"#flotsam_plato_meta", text:"On me traite de débris. Je cite Platon. Qui est le philosophe, maintenant ?" }
  { key:"#frog_joke_ribbit", text:"Croâ. C'est tout. Ah non — aussi, votre maison est à moi maintenant." }
  { key:"#frog_joke_plague", text:"Ils appellent ça une plaie. Moi, j'appelle ça une réunion de famille." }
  { key:"#frog_joke_pad", text:"J'ai demandé un nénuphar. On m'a donné une brique crue. C'est presque pareil." }
  { key:"#frog_joke_pharaoh", text:"Pharaon dit qu'il faut sauter au travail. Ha, je saute déjà." }
  { key:"#frog_joke_flies", text:"Que commandent les grenouilles au bazar ? Tout ce qui les asticote." }
  { key:"#frog_joke_happy", text:"Pourquoi les grenouilles sont-elles si joyeuses ? Elles mangent tout ce qui les embête. Deux fois." }
  { key:"#frog_joke_croak", text:"Je suis venue ici pour coasser et gober des mouches. Et je n'ai plus de mouches." }
  { key:"#frog_joke_swarm", text:"Une grenouille, c'est mignon. Dix, c'est une réunion. Vingt, c'est une politique." }
  { key:"#frog_joke_happiness", text:"L'humeur de la cité vient de baisser. De rien." }
  { key:"#frog_joke_nile", text:"Le Nil monte. Moi aussi. Surtout sur votre pas de porte." }
  { key:"#frog_joke_amphibious", text:"Amphibie, ça veut dire terre et eau. Votre garde-manger compte pour les deux." }
  { key:"#frog_joke_meta", text:"Je suis un présage biblique avec un numéro de comique. Croâ." }
  { key:"#TR_CONFIG_HEADER_LANGUAGES", text:"Langue du jeu" }
  { key:"#hunter_ostrich_good_city", text:"Je me plais ici, mais il y a toujours moyen de faire mieux." }
  { key:"#immigrant_im_new_here", text:"Je viens d'arriver dans cette ville. J'ai hâte de voir ce qu'elle peut m'apporter." }
  { key:"#immigrant_heard_there_is_a_job_here", text:"Il paraît qu'on y trouve très facilement du travail." }
  { key:"#immigrant_city_has_plenty_of_food", text:"On m'a dit que la ville regorgeait de nourriture." }
  { key:"#immigrant_disease_risk", text:"La maladie dans les rues ? J'espérais une cité plus saine." }
  { key:"#immigrant_city_have_no_army", text:"Pas de forts ? Je croyais avoir laissé le danger derrière moi." }
  { key:"#immigrant_need_workers", text:"Tant d'ateliers vides. Tant mieux — il y aura du travail pour moi." }
  { key:"#immigrant_gods_are_angry", text:"Même les dieux semblent agités. Mauvais présage pour un nouvel arrivant." }
  { key:"#immigrant_city_is_bad", text:"La faveur de Pharaon semble bien mince. Me suis-je trompé de cité ?" }
  { key:"#immigrant_much_unemployment", text:"Tant de gens désœuvrés. Y aura-t-il encore une place pour moi ?" }
  { key:"#immigrant_low_entertainment", text:"Pas de fête depuis une éternité. Un accueil bien terne pour les nouveaux venus." }
  { key:"#immigrant_city_is_good", text:"Voilà un bel endroit pour repartir de zéro !" }
  { key:"#immigrant_city_is_amazing", text:"Quelle cité ! Je suis heureux d'avoir fait le voyage." }
  { key:"#emigrant_no_job_in_city", text:"Il n'y a pas de travail ici. Je vais chercher ailleurs." }
  { key:"#emigrant_no_food_in_city", text:"Je n'ai pas assez à manger ici. Je quitte cet endroit maudit !" }
  { key:"#emigrant_tax_too_high", text:"Les impôts sont trop élevés ici. Je pensais même qu'il fallait payer pour partir." }
  { key:"#emigrant_salary_too_low", text:"Je ne gagne pas assez d'argent pour vivre ici." }
  { key:"#emigrant_no_house_for_me", text:"Les maisons sont surpeuplées. Je ne peux pas rester ici sans logement." }
  { key:"#emigrant_disease_risk", text:"Cet endroit empeste la maladie. Je ne vais pas attendre la peste." }
  { key:"#emigrant_city_have_no_army", text:"Pas de forts ? Un seul raid et il ne resterait rien de nous. Je m'en vais." }
  { key:"#emigrant_need_workers", text:"On réclame des ouvriers, mais il n'y a pas de travail pour moi. Il est temps de partir." }
  { key:"#emigrant_gods_are_angry", text:"Les dieux semblent furieux. Je préfère prier dans un endroit plus sûr." }
  { key:"#emigrant_city_is_bad", text:"Cette cité a une réputation déplorable. Je ne veux pas y être enterré." }
  { key:"#emigrant_low_entertainment", text:"Pas de fête depuis une éternité. Même la route qui sort de la ville est plus animée." }
  { key:"#emigrant_city_is_good", text:"Une cité assez agréable — pour quelqu'un d'autre. Ma charrette est chargée." }
  { key:"#emigrant_city_is_amazing", text:"Une cité extraordinaire, paraît-il. Pas assez pour me retenir." }
  { key:"#recruiter_disease_in_city", text:"Les gens sont tous malades. Attention à la peste !" }
  { key:"#recruiter_no_food_in_city", text:"Je meurs de faim. La nourriture compte plus que la main-d'œuvre." }
  { key:"#recruiter_city_not_safety", text:"Notre ville risque d'être attaquée. J'embaucherai alors des étrangers plutôt que des Egyptiens." }
  { key:"#recruiter_need_workers", text:"Sans main-d'œuvre, je ne peux pas travailler." }
  { key:"#recruiter_gods_are_angry", text:"J'espère que les dieux ne nous puniront pas. Nous devons nous préoccuper davantage d'eux." }
  { key:"#recruiter_enemies_attack", text:"Les ennemis peuvent attaquer à tout moment. Personne ne nous respecte." }
  { key:"#recruiter_i_looking_for_the_workers", text:"Avec tous ces chômeurs, mon travail ne devrait pas être très difficile." }
  { key:"#recruiter_boring", text:"Cet endroit est ennuyeux. Je devrais embaucher plus d'artistes." }
  { key:"#recruiter_living_here", text:"J'aime cet endroit. Les choses pourraient être pires." }
  { key:"#recruiter_city_is_amazing", text:"C'est la plus belle ville au monde !" }
  { key:"#recruiter_i_want_to_leave_city", text:"Toute la ville me connaît. Beaucoup de gens me demandent du travail." }
  { key:"#recruiter_much_unemployments", text:"Je propose de nombreuses offres d'emploi, mais personne n'est disponible." }
  { key:"#recruiter_no_jobs", text:"Pas de travail pour eux, pas d'ouvriers pour moi. Quelque chose cloche ici." }
  { key:"#recruiter_no_some_workers", text:"Je cherche encore quelques ouvriers pour pourvoir les postes." }
  { key:"#recruiter_need_more_workers", text:"Il nous faut beaucoup plus d'ouvriers. Ma liste ne cesse de s'allonger." }
  { key:"#barge_have_no_place_for_dock", text:"Je pourrais peut-être visiter cette cité pendant que l'on décharge mon navire." }
  { key:"#barge_docked_wait_for_dockpushers", text:"Nous attendons une cargaison pour notre navire." }
  { key:"#barge_city_not_trades", text:"Je ne connais pas la raison de notre présence ici. Cette cité ne pratique aucun commerce et les environs n'offrent aucune distraction." }
  { key:"#barge_i_like_to_trage", text:"J'adore faire des affaire ! J'ai hâte de vendre mes marchandises." }
  { key:"#barge_amazing_trades", text:"Quel magnifique voyage !" }
  { key:"#dancer_i_like_festivals", text:"Beaucoup de gens sont malades dans la cité. J'espère que je ne vais rien attraper !" }
  { key:"#dancer_desease_can_start_at_any_moment", text:"Je ne suis pas très agile le ventre vide !" }
  { key:"#dancer_no_food_in_city", text:"Les ennemis n'auront pas de mal à prendre notre cité. Elle n'est pas défendue." }
  { key:"#dancer_city_not_safety_workers_leaving", text:"Encore un partenaire de moins ! J'ai horreur de danser seul." }
  { key:"#dancer_need_workers", text:"Nous ferions mieux d'apaiser les dieux rapidement !" }
  { key:"#dancer_gods_are_angry", text:"La réputation de cette cité est pire que celle d'un jongleur ! Pourvu que l'on ne nous attaque pas." }
  { key:"#dancer_city_is_bad", text:"Il y a tant de personnes sans travail qu'on manque de trébucher dessus !" }
  { key:"#dancer_much_unemployments", text:"(bâillement) Qu'on me divertisse !" }
  { key:"#dancer_salary_too_low", text:"Cette cité est ni plus ni moins valable qu'une autre, j'imagine." }
  { key:"#dancer_city_is_good", text:"Cette cité est fantastique !" }
  { key:"#dancer_city_is_amazing", text:"Ces fêtards sont tellement enthousiastes qu'ils me donnent envie de sauter plus haut." }
  { key:"#homeless_i_was_kicked_out_of_my_home", text:"J'ai été expulsé de ma maison." }
  { key:"#homeless_i_cant_find_a_place_to_live", text:"Je n'ai nulle part où aller !" }
  { key:"#homeless_no_job_in_city", text:"Pas de travail et pas de toit. Cette cité n'a rien pour moi." }
  { key:"#homeless_no_food_in_city", text:"Je meurs de faim et je suis sans abri. Je ne peux pas rester ici." }
  { key:"#homeless_tax_too_high", text:"Les impôts m'ont pris ma maison. Maintenant ils veulent le reste de ma dignité." }
  { key:"#homeless_salary_too_low", text:"Les salaires d'ici ne me paieraient même pas un coin pour dormir." }
  { key:"#homeless_found_new_house", text:"Une maison avec de la place ! La chance tourne peut-être." }
  { key:"#homeless_no_house_for_me", text:"Il n'y a plus de place pour moi dans cette cité. Je m'en vais." }
  { key:"#homeless_need_workers", text:"Ils manquent d'ouvriers, et pourtant je dors dans la rue. Allez comprendre." }
  { key:"#homeless_city_is_bad", text:"La faveur de Pharaon n'est que cendres. Pas étonnant que j'aie perdu mon toit." }
  { key:"#homeless_gods_are_angry", text:"Les dieux sont en colère. D'abord les temples souffrent — puis les gens comme moi." }
  { key:"#homeless_city_bad_reputation", text:"La réputation de cette cité est aussi vide que ma natte." }
  { key:"#homeless_city_is_good", text:"La cité semble bien aller pour les autres. Il me faut juste une porte qui s'ouvre pour moi." }
  { key:"#buyer_goto_store", text:"Je pars au grenier et à l'entrepôt. Souhaitez-moi de bonnes jambes !" }
  { key:"#buyer_back_to_market", text:"Retour au bazar avec un plein chargement. Ne traînez pas, les garçons !" }
  { key:"#buyer_city_has_low_health", text:"Les gens sont malades — et ils veulent quand même de la nourriture fraîche sur leur table." }
  { key:"#buyer_no_food_in_city", text:"Des greniers vides ! Comment suis-je censée remplir ces paniers ?" }
  { key:"#buyer_city_have_no_army", text:"Pas de forts ? Des pillards pourraient voler tous les paniers sur la route." }
  { key:"#buyer_much_unemployments", text:"Tant de bras inoccupés, et personne ne m'aide à porter les marchandises." }
  { key:"#buyer_gods_are_angry", text:"Les dieux semblent en colère. Même le bazar ne peut pas marchander avec eux." }
  { key:"#buyer_city_is_bad_reputation", text:"La réputation de cette cité est si mauvaise que les marchands n'y risquent pas leurs charrettes." }
  { key:"#buyer_too_much_unemployments", text:"Le chômage est élevé. Les gens affamés font de piètres clients." }
  { key:"#buyer_low_entertainment", text:"Pas de fête depuis une éternité. Un peu de musique raccourcirait ces trajets." }
  { key:"#buyer_city_is_good", text:"Cette cité va bien — routes courtes et étals pleins." }
  { key:"#buyer_city_is_amazing", text:"La meilleure cité pour une acheteuse du bazar ! Tout ce qu'il me faut est au coin de la rue." }
  { key:"#marketboy_these_baskets_are_too_heavy", text:"Ces paniers sont trop lourds pour un garçon comme moi !" }
  { key:"#marketboy_bossy_lady_makes_me_carry_goods", text:"Ma patronne me fait porter des marchandises toute la journée !" }
  { key:"#marketboy_one_day_ill_run_the_bazaar", text:"Aujourd'hui je porte des paniers, mais un jour je dirigerai le bazar." }
  { key:"#marketboy_runaway", text:"Elle m'a laissé en plan ! Très bien — je rapporte ces paniers moi-même." }
  { key:"#marketboy_disease_risk", text:"Tout le monde tousse. Je peux poser les paniers et me laver les mains ?" }
  { key:"#marketboy_no_food_in_city", text:"Des greniers vides ? Alors pourquoi je trimballe de la nourriture dans toute la ville ?" }
  { key:"#marketboy_city_have_no_army", text:"Pas de forts ? Si des pillards arrivent, ils prendront mes paniers en premier !" }
  { key:"#marketboy_need_workers", text:"Le bazar a besoin de plus de bras. Les miens sont déjà pleins !" }
  { key:"#marketboy_gods_are_angry", text:"Les dieux semblent en colère. Peut-être qu'ils n'aiment pas les fruits abîmés non plus." }
  { key:"#marketboy_city_is_bad", text:"Cette cité semble mesquine. Même les chiens aboient après mes paniers." }
  { key:"#marketboy_much_unemployment", text:"Tant de gens désœuvrés — et personne ne propose de m'aider à porter !" }
  { key:"#marketboy_low_entertainment", text:"Pas de fête depuis une éternité. Un défilé, au moins, raccourcirait le trajet." }
  { key:"#marketboy_city_is_good", text:"Cette cité, ça va. Des routes courtes et une acheteuse qui connaît le chemin." }
  { key:"#marketboy_city_is_amazing", text:"La meilleure cité pour porter des paniers ! Un jour, j'aurai mon propre étal." }
  { key:"#engineer_extreme_damage_level", text:"Les habitants souffrent plus que les bâtiments. J'espère que la situation va s'améliorer" }
  { key:"#engineer_i_am_works", text:"Ces murs ne s'effondreront pas tant que je veille." }
  { key:"#engineer_no_food_in_city", text:"Les maisons ne souffrent pas de la faim mais moi si !" }
  { key:"#engineer_city_not_safety", text:"Comment lutter contre une invasion ? Les défenses de la ville sont ridicules." }
  { key:"#engineer_high_damage_level", text:"Qu'importe si ces bâtiments s'écroulent ! Aucun travailleur n'y habite." }
  { key:"#engineer_gods_are_angry", text:"Même le meilleur des architectes ne peut rien contre la colère des dieux." }
  { key:"#engineer_city_has_bad_reputation", text:"La réputation de la ville est faible. Je redoute une invasion." }
  { key:"#engineer_need_more_workers", text:"Je crois que beaucoup de personnes sont sans emploi." }
  { key:"#engineer_low_entertainment", text:"Euh... Même les architectes s'amusent quelquefois." }
  { key:"#engineer_city_is_bad", text:"Les conditions de vie pourraient être pires." }
  { key:"#engineer_life_here_could_be_worse", text:"Les conditions de vie pourraient être pires." }
  { key:"#engineer_city_is_good", text:"Cette ville propose tout ce dont rêve un architecte !" }
  { key:"#engineer_so_many_places_in_poor_condition", text:"Je suis débordé ! Il y a tant d'endroits qui nécessitent des réparations." }
  { key:"#engineer_city_is_amazing", text:"J'espère que l'on appréciera mon travail pour la ville." }
  { key:"#brick_bricklaying_time_at_monument", text:"Tout le monde au monument pour poser des briques !" }
  { key:"#brick_monument_will_be_strong", text:"Ce monument sera solide !" }
  { key:"#brick_waiting_for_bricks", text:"J'attends toujours ces briques. Allez, les paysans, plus vite !" }
  { key:"#brick_looking_for_spot", text:"Je cherche la prochaine portion de mur à élever." }
  { key:"#brick_work_statue", text:"Un peu de mortier et cette statue aura de nouveau fière allure." }
  { key:"#brick_return_to_guild", text:"Retour à la guilde. Mes bras ont bien mérité du repos." }
  { key:"#brick_leaving_site", text:"Plus rien à faire ici — je quitte le chantier." }
  { key:"#brick_disease_risk", text:"Cet endroit sent la maladie. Dur de poser des briques quand les mains tremblent." }
  { key:"#brick_no_food_in_city", text:"Des greniers vides ? Un briquetier affamé monte des murs de travers." }
  { key:"#brick_city_have_no_army", text:"Pas de forts ? Un seul raid et ce monument sera en ruine avant d'être fini." }
  { key:"#brick_gods_are_angry", text:"Les dieux semblent en colère. Même les briques crues se fendent sous leur regard." }
  { key:"#brick_low_entertainment", text:"Pas de fête depuis une éternité. Même les briquetiers ont besoin d'un jour loin de l'échafaudage." }
  { key:"#brick_city_is_good", text:"Cette cité est solide ! De bonnes fondations pour de grands monuments." }
  { key:"#brick_city_is_amazing", text:"La meilleure cité pour laquelle j'aie bâti. Ces murs tiendront pour l'éternité !" }
  { key:"#carpenter_work_my_tools_need_for_monument", text:"On a besoin de mes outils au monument !" }
  { key:"#carpenter_this_monument_will_be_short", text:"Ce monument ne prendra pas longtemps — le bois est prêt." }
  { key:"#carpenter_work_wall", text:"L'échafaudage d'abord. Ensuite, le vrai travail commence là-haut." }
  { key:"#carpenter_looking_for_spot", text:"Je cherche la prochaine poutre à poser." }
  { key:"#carpenter_return_to_guild", text:"Retour à la guilde. Encore de la sciure dans les cheveux." }
  { key:"#carpenter_work_garden", text:"Un peu de menuiserie et ce jardin aura fière allure." }
  { key:"#carpenter_disease_risk", text:"Cet endroit sent la maladie. Dur de tenir un ciseau avec les mains qui tremblent." }
  { key:"#carpenter_no_food_in_city", text:"Des greniers vides ? Un charpentier affamé coupe le bois de travers." }
  { key:"#carpenter_city_have_no_army", text:"Pas de forts ? Un seul raid et cet échafaudage finira en bois de chauffage." }
  { key:"#carpenter_gods_are_angry", text:"Les dieux semblent en colère. Même le bon cèdre gauchit sous leur regard." }
  { key:"#carpenter_low_entertainment", text:"Pas de fête depuis une éternité. Même les charpentiers ont besoin d'un jour loin de l'échafaudage." }
  { key:"#carpenter_city_is_good", text:"Cette cité est solide ! Un bon travail du bois mérite de bonnes fondations." }
  { key:"#carpenter_city_is_amazing", text:"La meilleure cité pour laquelle j'aie bâti. Ces poutres tiendront pour l'éternité !" }
  { key:"#fireman_desease_can_start_at_any_moment", text:"J'espère que la peste ne va pas nous frapper car une telle épidémie se propage très rapidement." }
  { key:"#fireman_no_food_in_city", text:"La ville brûle mais je n'arrive pas à oublier ma faim." }
  { key:"#fireman_city_not_safety_workers_leaving", text:"En cas d'invasion, la ville entière risque de partir en fumée." }
  { key:"#fireman_need_workers", text:"Je crains que certains de ces bâtiments à demi occupés ne prennent feu. Il nous faudrait plus de travailleurs." }
  { key:"#fireman_gods_are_angry", text:"Les dieux peuvent nous châtier si nous ne les respectons pas assez." }
  { key:"#fireman_hight_fire_level", text:"Je n'apprécie guère la mauvaise réputation de cette ville. Nous risquons d'être attaqués." }
  { key:"#fireman_need_more_workers", text:"Beaucoup de volontaires veulent devenir pompiers. Ils cherchent tous du travail." }
  { key:"#fireman_low_entertainment", text:"Ce métier est éprouvant. J'aimerais me détendre avec un joli spectacle, mais la ville manque de distractions." }
  { key:"#fireman_gods_are_pleasures", text:"Cette ville me plaît." }
  { key:"#fireman_city_is_amazing", text:"Cette ville est agréable." }
  { key:"#fireman_fighting_fire", text:"Je n'ai pas le temps de discuter, je dois éteindre ce feu." }
  { key:"#fireman_going_to_fire", text:"Ce feu pourrait détruire la ville si je n'agis pas rapidement !" }
  { key:"#fireman_fighting_fire_also", text:"Aïe, ça brûle !" }
  { key:"#cartpusher_have_no_place_for_goods", text:"Ces marchandises ne bougeront pas tant que personne ne les déchargera." }
  { key:"#cartpusher_i_have_time_for_rest", text:"Personne ne voudra de ces marchandises ! D'accord, je prends le reste." }
  { key:"#cartpusher_road_too_long", text:"Je dois traverser la ville avec ces marchandises. Cela me prendra toute la journée !" }
  { key:"#cartpusher_i_have_no_destination", text:"Nous avons trop de travail. Il nous faut de l'aide." }
  { key:"#cartpusher_back_to_home", text:"J'attendrai jusqu'à ce qu'un endroit ce libère pour ces marchandises." }
  { key:"#cartpusher_delivering_items", text:"C'est ici ? Je ne pourrai bientôt plus porter ces marchandises." }
  { key:"#cartpusher_disease_risk", text:"Cet endroit sent la maladie. Dur de pousser une charrette quand on a de la fièvre." }
  { key:"#cartpusher_no_food_in_city", text:"Des greniers vides ? Alors pourquoi je transporte tout ça ?" }
  { key:"#cartpusher_city_have_no_army", text:"Pas de forts ? Un seul raid et ma charrette devient butin de guerre." }
  { key:"#cartpusher_gods_are_angry", text:"Les dieux semblent en colère. Même les roues grincent comme un présage." }
  { key:"#cartpusher_low_entertainment", text:"Pas de fête depuis une éternité. Le dos d'un charretier a aussi besoin de vacances." }
  { key:"#cartpusher_city_is_good", text:"Cette cité est solide ! Routes courtes et entrepôts pleins." }
  { key:"#cartpusher_city_is_amazing", text:"La meilleure cité pour laquelle j'aie transporté. Ces charges roulent presque toutes seules !" }
  { key:"#docker_need_more_help", text:"Nous faisons plus que notre part de travail. Il nous faut de l'aide." }
  { key:"#docker_wait_until_space_opens_up", text:"J'attendrai jusqu'à ce qu'un endroit ce libère pour ces marchandises." }
  { key:"#docker_cant_haul_goods_much_farther", text:"J'arrive bientôt ? Je ne peux plus porter ces marchandises bien loin." }
  { key:"#docker_disease_risk", text:"Ce quai sent la maladie. Dur de décharger quand l'air est vicié." }
  { key:"#docker_no_food_in_city", text:"Des greniers vides ? Les navires arrivent affamés, et nous aussi." }
  { key:"#docker_city_have_no_army", text:"Pas de forts ? Un seul raid et ce port est pillé." }
  { key:"#docker_gods_are_angry", text:"Les dieux semblent en colère. Même le fleuve semble couler dans le mauvais sens." }
  { key:"#docker_low_entertainment", text:"Pas de fête depuis une éternité. Les dockers ont aussi besoin d'une permission à terre." }
  { key:"#docker_city_is_good", text:"Ce port tourne bien ! Courts trajets et entrepôts pleins." }
  { key:"#docker_city_is_amazing", text:"Le meilleur port où j'aie travaillé. Ces caisses débarquent presque toutes seules !" }
  { key:"#enemy_chariot_attacking", text:"En avant ! Écrasez-les sous les roues !" }
  { key:"#enemy_chariot_marching", text:"La poussière de nos roues étouffera cette cité." }
  { key:"#enemy_chariot_waiting", text:"Tenez la ligne. La charge arrive bientôt." }
  { key:"#enemy_chariot_leaving", text:"Repli ! Vivons pour charger à nouveau." }
  { key:"#enemy_chariot_city_will_fall", text:"Vos murs n'arrêteront pas les chars." }
  { key:"#enemy_chariot_no_match", text:"L'infanterie ne fait pas le poids contre nous !" }
  { key:"#enemy_chariot_for_glory", text:"Pour la gloire et le butin !" }
  { key:"#enemy_archer_shooting", text:"Tirez ! Remplissez le ciel de flèches !" }
  { key:"#enemy_archer_marching", text:"Arcs prêts. Leurs rues seront rouges de sang." }
  { key:"#enemy_archer_waiting", text:"Attendez. Laissez-les approcher à portée." }
  { key:"#enemy_archer_leaving", text:"Repli ! Gardez les flèches pour un autre jour." }
  { key:"#enemy_archer_city_will_fall", text:"Vos murs ne sont rien face à une pluie de flèches." }
  { key:"#enemy_archer_arrows_ready", text:"Flèche encochée. Qui meurt en premier ?" }
  { key:"#enemy_archer_for_glory", text:"Pour la gloire — et un tir net !" }
  { key:"#enemy_sword_attacking", text:"Le fer et le sang ! Abattez-les !" }
  { key:"#enemy_sword_marching", text:"Avancez. Leur cité brûlera avant la nuit." }
  { key:"#enemy_sword_waiting", text:"Attendez. Au signal, nous frappons." }
  { key:"#enemy_sword_leaving", text:"Repli ! Nous reviendrons avec plus de lames." }
  { key:"#enemy_sword_no_army", text:"Pas de forts ? Cette cité est déjà à nous." }
  { key:"#enemy_sword_no_food", text:"Ils meurent de faim. Des cibles faciles font un butin facile." }
  { key:"#enemy_sword_disease", text:"Leurs rues empestent la maladie. Encore plus facile." }
  { key:"#enemy_sword_need_workers", text:"Ils ne peuvent même pas faire tourner leurs ateliers. Pitoyable." }
  { key:"#enemy_sword_gods_angry", text:"Leurs dieux se sont détournés. Nous aussi — après avoir pris l'or." }
  { key:"#enemy_sword_city_is_bad", text:"La faveur de Pharaon n'est que cendres. Personne ne pleurera cet endroit." }
  { key:"#enemy_sword_low_entertainment", text:"Pas de fêtes, pas de courage. Ils céderont à la première charge." }
  { key:"#enemy_sword_city_is_good", text:"Une cité bien rangée. Dommage que nous soyons là pour la détruire." }
  { key:"#enemy_sword_city_is_amazing", text:"Si prospère. Le butin sera magnifique." }
  { key:"#enemy_sword_for_glory", text:"Pour la gloire et l'épée !" }
  { key:"#enemy_spearman_shooting", text:"Lancez ! Que les lances trouvent leur cible !" }
  { key:"#enemy_spearman_marching", text:"En avant. Nos lances éclairciront leurs rangs." }
  { key:"#enemy_spearman_waiting", text:"Attendez. Préparez le prochain jet." }
  { key:"#enemy_spearman_leaving", text:"Repli ! Gardez les lances pour un autre jour." }
  { key:"#enemy_spearman_city_will_fall", text:"Cette cité tombera sous nos lances." }
  { key:"#enemy_spearman_spears_ready", text:"Lances prêtes ! Personne ne tiendra." }
  { key:"#enemy_spearman_for_glory", text:"Pour la gloire et la lance !" }
  { key:"#enemy_transport_created", text:"Larguez les amarres ! Leur côte est à prendre." }
  { key:"#enemy_transport_sailing", text:"Ramez régulièrement. Nous toucherons terre bientôt." }
  { key:"#enemy_transport_disembarking", text:"Sur le rivage ! Videz la cale de son acier !" }
  { key:"#enemy_transport_idle", text:"La coque attend. Les troupes sont prêtes pour la plage." }
  { key:"#enemy_transport_no_army", text:"Pas de navires de guerre chez eux ? Ces eaux sont à nous." }
  { key:"#enemy_transport_no_food", text:"Une cité affamée. Notre débarquement sera facile." }
  { key:"#enemy_transport_disease", text:"La maladie sur leurs quais. Des proies faciles à terre." }
  { key:"#enemy_transport_need_workers", text:"Ils ne peuvent même pas faire tourner leurs chantiers. Port pitoyable." }
  { key:"#enemy_transport_gods_angry", text:"Leurs dieux les abandonnent. La marée est avec nous." }
  { key:"#enemy_transport_city_is_bad", text:"La faveur de Pharaon n'est que cendres. Aucune flotte ne les sauvera." }
  { key:"#enemy_transport_low_entertainment", text:"Pas de fêtes, pas de courage. Ils céderont sur la plage." }
  { key:"#enemy_transport_city_is_good", text:"Un beau port. Dommage que nous soyons là pour le prendre." }
  { key:"#enemy_transport_city_is_amazing", text:"Des quais riches. Le butin remplira nos cales." }
  { key:"#enemy_transport_for_glory", text:"Pour la gloire — et une tête de pont !" }
  { key:"#enemy_warship_created", text:"Hissez les voiles ! Leur port est à nous." }
  { key:"#enemy_warship_idle", text:"Gardez la position. Surveillez leur flotte." }
  { key:"#enemy_warship_pursuing", text:"Pourchassez-les ! Aucun navire ne s'échappe." }
  { key:"#enemy_warship_attacking", text:"Feu ! Éperonnez-les et coulez-les !" }
  { key:"#enemy_warship_no_army", text:"Pas de forts sur la rive ? Leurs quais sont sans défense." }
  { key:"#enemy_warship_no_food", text:"Ils meurent de faim. Un butin facile nous attend." }
  { key:"#enemy_warship_disease", text:"La peste dans leur cité. Des proies faciles." }
  { key:"#enemy_warship_need_workers", text:"Manque de main-d'œuvre. Leurs murs vont s'effondrer." }
  { key:"#enemy_warship_gods_angry", text:"Même leurs dieux se sont détournés." }
  { key:"#enemy_warship_city_is_bad", text:"Une cité faible. Parfaite pour un raid." }
  { key:"#enemy_warship_low_entertainment", text:"Pas de fêtes. Leur moral est déjà brisé." }
  { key:"#enemy_warship_city_is_good", text:"Des quais riches. De belles cargaisons en vue." }
  { key:"#enemy_warship_city_is_amazing", text:"Quelle prospérité. Le butin sera magnifique." }
  { key:"#enemy_warship_for_glory", text:"Pour la gloire et la mer !" }
  { key:"#ferry_landing_ok", text:"Cet embarcadère est relié à l'autre rive et pourvu en personnel. Les marcheurs peuvent traverser." }
  { key:"#ferry_boat_ready", text:"Prêt à l'embarcadère. Qui traverse ?" }
  { key:"#ferry_boat_going", text:"Larguez ! Prochaine rive en vue." }
  { key:"#ferry_boat_at_destination", text:"Nous sommes arrivés. Descendez prudemment sur le quai." }
  { key:"#ferry_boat_returning", text:"On rentre. Attention au courant." }
  { key:"#ferry_boat_waiting", text:"En attente d'un bac de destination de l'autre côté de l'eau." }
  { key:"#ferry_boat_disease_risk", text:"Cette traversée sent la maladie. Dur de manier la perche quand l'air est vicié." }
  { key:"#ferry_boat_no_food_in_city", text:"Des greniers vides ? Les passagers affamés veulent quand même traverser." }
  { key:"#ferry_boat_city_have_no_army", text:"Pas de forts ? Un seul raid et ce bac est pillé." }
  { key:"#ferry_boat_gods_are_angry", text:"Les dieux semblent en colère. Même le courant tire dans le mauvais sens." }
  { key:"#ferry_boat_low_entertainment", text:"Pas de fête depuis une éternité. Les passeurs ont aussi besoin d'une permission à terre." }
  { key:"#ferry_boat_city_is_good", text:"Cette traversée tourne bien ! Courts trajets et embarcadères pleins." }
  { key:"#ferry_boat_city_is_amazing", text:"Le meilleur bac où j'aie travaillé. Ces embarcadères vous accueillent presque !" }
  { key:"#governor_city_left_much_nobles", text:"Trop de nobles quittent cette cité !" }
  { key:"#governor_festival_was_near", text:"Ah, cette fête était splendide ! Les rues en sont encore toutes chaudes." }
  { key:"#governor_disease_risk", text:"La maladie dans les rues. La cité d'un gouverneur ne devrait pas sentir la fièvre." }
  { key:"#governor_no_food_in_city", text:"Des greniers vides ? Les nobles ne resteront pas là où le pain manque." }
  { key:"#governor_city_have_no_army", text:"Pas de forts ? Un seul raid et ce palais est pillé." }
  { key:"#governor_gods_are_angry", text:"Les dieux semblent en colère. Même la cour murmure de mauvais présages." }
  { key:"#governor_low_entertainment", text:"Pas de fête depuis une éternité. Même les gouverneurs ont besoin de divertissement." }
  { key:"#governor_city_is_good", text:"Une cité solide ! L'ordre dans les rues et des pièces dans les coffres." }
  { key:"#governor_city_is_amazing", text:"La plus belle cité que j'aie gouvernée. Pharaon lui-même en serait fier !" }
  { key:"#fishing_boat_ready", text:"Bateau prêt au quai. L'équipage attend la marée." }
  { key:"#fishing_boat_going_to_fish", text:"Cap sur les zones de pêche." }
  { key:"#fishing_boat_fishing", text:"On remonte le poisson. Tenez bien les filets !" }
  { key:"#fishing_boat_going_to_wharf", text:"Retour au quai, cales vides." }
  { key:"#fishing_boat_at_wharf", text:"Amarré au quai. Réapprovisionnement pour une autre sortie." }
  { key:"#fishing_boat_returning_with_fish", text:"Retour avec une pleine prise !" }
  { key:"#fishing_boat_looking_for_spot", text:"À la recherche d'un coin de pêche. Ces eaux sont traîtres." }
  { key:"#fishing_boat_disease_risk", text:"Le port empeste la maladie. Dur de pêcher quand l'équipage est faible." }
  { key:"#fishing_boat_no_food_in_city", text:"Les greniers de la cité sont vides ? Tant mieux — ils voudront notre poisson." }
  { key:"#fishing_boat_city_have_no_army", text:"Pas de forts ? Des pillards pourraient s'emparer de chaque bateau sur ce rivage." }
  { key:"#fishing_boat_need_workers", text:"Les quais ont besoin de bras. Un bateau seul ne peut pas nourrir la cité." }
  { key:"#fishing_boat_gods_are_angry", text:"Les dieux sont en colère. Même les poissons évitent nos filets." }
  { key:"#fishing_boat_city_is_bad", text:"La faveur de Pharaon n'est que cendres. Aucune flotte ne pleurera cet endroit." }
  { key:"#fishing_boat_much_unemployment", text:"Des gens désœuvrés à terre, et toujours pas assez d'équipages pour les bateaux." }
  { key:"#fishing_boat_low_entertainment", text:"Pas de fête depuis une éternité. Les pêcheurs ont aussi besoin d'une permission à terre." }
  { key:"#fishing_boat_city_is_good", text:"De belles eaux et un quai animé. Pas un mauvais mouillage." }
  { key:"#fishing_boat_city_is_amazing", text:"La meilleure pêche que j'aie connue. Les filets sont pleins avant midi !" }
  { key:"#funeral_walker_ready", text:"La procession est prête. Nous marchons pour les défunts honorés." }
  { key:"#funeral_walker_going_to_tomb", text:"Vers la tombe. Dégagez le chemin et tenez bien les lampes." }
  { key:"#funeral_walker_arrived", text:"Nous sommes arrivés. Que la tombe les accueille en paix." }
  { key:"#funeral_walker_lost_path", text:"La route nous a trahis. Nous devons retenter le chemin." }
  { key:"#funeral_walker_disease_risk", text:"La maladie arpente les rues. Même un enterrement semble bondé." }
  { key:"#funeral_walker_no_food_in_city", text:"Des greniers vides, et nous enterrons toujours. Les vivants maigrissent." }
  { key:"#funeral_walker_city_have_no_army", text:"Pas de forts ? Des pillards pourraient profaner chaque tombe que nous entretenons." }
  { key:"#funeral_walker_need_workers", text:"Trop peu de bras. Les processions attendent pendant que les monuments restent inachevés." }
  { key:"#funeral_walker_gods_are_angry", text:"Les dieux sont en colère. Quel enterrement pourrait les apaiser maintenant ?" }
  { key:"#funeral_walker_city_is_bad", text:"La faveur de Pharaon n'est que cendres. Même les tombes semblent abandonnées." }
  { key:"#funeral_walker_much_unemployment", text:"Des gens désœuvrés, et pourtant peu marchent sur la route funéraire." }
  { key:"#funeral_walker_low_entertainment", text:"Pas de fête depuis une éternité. Le deuil emplit chaque place." }
  { key:"#funeral_walker_city_is_good", text:"Une belle cité pour les vivants — et un repos digne pour les morts." }
  { key:"#funeral_walker_city_is_amazing", text:"Quelle splendeur ! Même les tombes brillent d'honneur." }
  { key:"#malaria_problem", text:"(Not used)" }
  { key:"#malaria_not_a_problem", text:"Personne ne souffre de la malaria ici." }
  { key:"#malaria_outbreak_could_strike", text:"Si rien n'est fait, nous risquons une épidémie de malaria." }
  { key:"#herbalist_no_food_in_city", text:"Des greniers vides ? Dur de soigner quand la cité meurt de faim." }
  { key:"#herbalist_city_have_no_army", text:"Pas de forts ? Un seul raid et mes herbes partent en cendres." }
  { key:"#herbalist_gods_are_angry", text:"Les dieux semblent en colère. Même les bons remèdes échouent sous leur regard." }
  { key:"#herbalist_low_entertainment", text:"Pas de fête depuis une éternité. Même les herboristes ont besoin d'un jour sans tournée." }
  { key:"#herbalist_city_is_good", text:"Cette cité est assez saine ! Courtes tournées et maisons solides." }
  { key:"#herbalist_city_is_amazing", text:"La meilleure cité que j'aie soignée. Ces rues guérissent presque toutes seules !" }
  { key:"#policeman_desease_can_start_at_any_moment", text:"Beaucoup de personnes sont malades et faibles. Je crains pour notre avenir." }
  { key:"#policeman_no_food_in_city", text:"Je n'ai rien avalé depuis des jours. Je serai bientôt obligé de voler pour manger !" }
  { key:"#policeman_city_not_safety", text:"En cas d'invasion, je serai le seul capable de défendre la ville." }
  { key:"#policeman_need_workers", text:"Si mon métier ne me passionnait pas autant, je choisirais un des nombreux postes vacants." }
  { key:"#policeman_gods_are_angry", text:"Si je dirigeais la ville, je m'occuperais davantage des dieux." }
  { key:"#policeman_no_army", text:"Notre ville est une proie facile pour nos ennemis. Nous avons une mauvaise réputation." }
  { key:"#policeman_much_unemployments", text:"Je n'aime pas tous ces gens désœuvrés. Je ne peux pas me promener sans en rencontrer !" }
  { key:"#policeman_low_entertainment", text:"Cette ville semble morte. Il n'y a aucune animation." }
  { key:"#policeman_city_is_good", text:"Cette ville n'est pas parfaite, mais elle me plaît." }
  { key:"#policeman_city_is_amazing", text:"Je ne me suis jamais senti aussi en sécurité pendant ma ronde. Cette cité est formidable !" }
  { key:"#policeman_very_low_crime_level", text:"Si l'on trouvait des beignets dans ce bazar, cette cité serait parfaite." }
  { key:"#policeman_low_crime_level", text:"Les gens sont sympathiques. Personne ne se plaint de violences." }
  { key:"#policeman_usual_crime_level", text:"On nous signale quelques crimes de-ci de-là, mais rien d'anormal." }
  { key:"#policeman_need_more_workers", text:"Moi-même, je ne m'aventure pas dans cet endroit de la ville !" }
  { key:"#policeman_iam_too_busy_that_talk", text:"Je suis trop occupé pour bavarder, revenez plus tard." }
  { key:"#policeman_i_hope_my_work_is_need", text:"Je veillerai à la sécurité de la ville !" }
  { key:"#policeman_no_army_2", text:"Je ne suis pas payé pour combattre les envahisseurs !" }
  { key:"#policeman_enemies_are_coming_2", text:"Ces vauriens ne prendront pas la ville pendant ma garde !" }
  { key:"#policeman_enemies_are_coming", text:"Nous risquons d'être vite envahis si personne ne m'aide !" }
  { key:"#hunter_antelope_investigate", text:"Des traces de sabots dans la poussière... une antilope est passée par ici." }
  { key:"#hunter_antelope_chase", text:"La voilà qui bondit ! Rapide comme le vent, mais mon javelot l'est plus encore." }
  { key:"#hunter_antelope_hunting", text:"Les antilopes ne font pas le poids ! Ces cornes ne les sauveront pas." }
  { key:"#hunter_antelope_back", text:"Ce soir, c'est steak à volonté !" }
  { key:"#hunter_antelope_reroute_packed", text:"Carcasse lourde, mauvaise piste. Je vais trouver un autre chemin vers le pavillon." }
  { key:"#hunter_antelope_look_packed", text:"Il me faut un chemin dégagé pour rentrer avec cette antilope sur les épaules." }
  { key:"#hunter_antelope_unloading", text:"De l'antilope fraîche pour le pavillon. Les cuisiniers seront contents." }
  { key:"#hunter_antelope_disease_risk", text:"Cet endroit sent la maladie. Même les troupeaux s'en éloignent." }
  { key:"#hunter_antelope_no_food_in_city", text:"Des greniers vides ? Alors j'ai intérêt à rapporter une belle antilope." }
  { key:"#hunter_antelope_city_have_no_army", text:"Pas de forts ? Un seul raid et cette cité est aussi perdue qu'une gazelle acculée." }
  { key:"#hunter_antelope_need_workers", text:"Il nous faut plus de bras. Je ne peux pas remplir toutes les marmites de gibier tout seul." }
  { key:"#hunter_antelope_gods_are_angry", text:"Les dieux semblent en colère. Les troupeaux sont agités, eux aussi." }
  { key:"#hunter_antelope_city_is_bad", text:"Pharaon n'est pas content de nous. Ça ne finit jamais bien." }
  { key:"#hunter_antelope_much_unemployment", text:"Trop de gens désœuvrés. Au moins, la chasse nourrit encore quelqu'un." }
  { key:"#hunter_antelope_low_entertainment", text:"Pas de fête depuis une éternité. Un festin d'antilope remonterait le moral de tous." }
  { key:"#hunter_antelope_city_is_good", text:"Cette cité est bien ! De beaux terrains de chasse tout près." }
  { key:"#hunter_antelope_city_is_amazing", text:"La meilleure cité pour laquelle j'aie chassé. Les antilopes sautent presque dans la marmite !" }
  { key:"#hunter_birds_investigate", text:"Des plumes dans les roseaux... une volée se nourrissait ici." }
  { key:"#hunter_birds_chase", text:"Les voilà qui s'envolent ! Mes flèches en feront tomber quelques-uns." }
  { key:"#hunter_birds_hunting", text:"Ces oiseaux sont rusés !" }
  { key:"#hunter_birds_back", text:"Ces oiseaux sont prêts à rôtir !" }
  { key:"#hunter_birds_reroute_packed", text:"Filet lourd d'oiseaux, mauvais chemin. Je vais trouver un autre trajet de retour." }
  { key:"#hunter_birds_look_packed", text:"Il me faut une piste dégagée jusqu'au pavillon avec cette prise." }
  { key:"#hunter_birds_unloading", text:"Des volailles fraîches pour le pavillon. Les cuisiniers vont avoir du travail." }
  { key:"#hunter_birds_disease_risk", text:"Cet endroit sent la maladie. Même les oiseaux l'évitent." }
  { key:"#hunter_birds_no_food_in_city", text:"Des greniers vides ? Alors j'ai intérêt à rapporter un sac plein d'oiseaux." }
  { key:"#hunter_birds_city_have_no_army", text:"Pas de forts ? Un seul raid et cette cité est aussi impuissante qu'un oiseau cloué au sol." }
  { key:"#hunter_birds_gods_are_angry", text:"Les dieux semblent en colère. Les volées sont agitées, elles aussi." }
  { key:"#hunter_birds_low_entertainment", text:"Pas de fête depuis une éternité. Un festin d'oiseaux rôtis remonterait le moral de tous." }
  { key:"#hunter_birds_city_is_good", text:"Cette cité est bien ! De beaux marais pour chasser les oiseaux tout près." }
  { key:"#hunter_birds_city_is_amazing", text:"La meilleure cité pour laquelle j'aie chassé. Les oiseaux volent presque dans la marmite !" }
  { key:"#lumberjack_hunting", text:"Une dure journée d'abattage m'attend." }
  { key:"#lumberjack_back", text:"Je devrais obtenir un très bon prix pour ce bois." }
  { key:"#lumberjack_disease_risk", text:"La fièvre dans la cité. Dur de manier la hache avec les mains qui tremblent." }
  { key:"#lumberjack_no_food_in_city", text:"Des greniers vides ? Un bûcheron affamé coupe le bois de travers." }
  { key:"#lumberjack_city_have_no_army", text:"Pas de forts ? Un seul raid et ces arbres serviront de bois de chauffage aux envahisseurs." }
  { key:"#lumberjack_gods_are_angry", text:"Les dieux semblent en colère. Même le bon cèdre gauchit sous leur regard." }
  { key:"#lumberjack_low_entertainment", text:"Pas de fête depuis une éternité. Même les bûcherons ont besoin d'un jour loin des arbres." }
  { key:"#lumberjack_city_is_good", text:"Cette cité est solide ! Du bon bois mérite de bonnes fondations." }
  { key:"#lumberjack_city_is_amazing", text:"La meilleure cité pour laquelle j'aie coupé du bois. Ces poutres tiendront pour l'éternité !" }
  { key:"#musician_i_like_festivals", text:"Ces foules de fête sont merveilleuses ! Tout le monde chante en chœur." }
  { key:"#musician_city_heath_too_low", text:"Si l'hygiène ne s'améliore pas dans cette cité, il ne me restera plus qu'à jouer des chants funèbres." }
  { key:"#musician_no_food_in_city", text:"J'aimerais chanter pour payer mon repas, mais cette cité n'a pas assez de nourriture." }
  { key:"#musician_city_not_safety_workers_leaving", text:"Je pourrais peut-être frapper les ennemis à la tête avec ma sistre. Cette cité est bien défendue." }
  { key:"#musician_need_workers", text:"Toutes mes représentations sont des solos. Cette cité n'a pas suffisamment de main-d'œuvre." }
  { key:"#musician_gods_are_angry", text:"J'espère que ma musique apaisera les dieux. Leur colère pourrait bientôt s'abattre sur nous." }
  { key:"#musician_city_is_bad_reputation", text:"Notre terrible réputation risque de provoquer une attaque !" }
  { key:"#musician_much_unemployments", text:"Pour la dernière fois, je n'embauche plus d'ouvriers ! Il y a tant de gens qui cherchent du travail." }
  { key:"#musician_no_entertainment", text:"Même les artistes aiment qu'on les divertisse ! Il n'y a pas assez de loisirs par ici." }
  { key:"#musician_no_entertainment_need", text:"Même les artistes aiment qu'on les divertisse ! Il n'y a pas assez de loisirs par ici." }
  { key:"#musician_city_not_bad", text:"Cette cité pourrait être pire, je pense." }
  { key:"#musician_city_is_good", text:"J'espère continuer encore longtemps à jouer de la belle musique dans cette cité." }
  { key:"#senet_i_like_festivals", text:"Les jeux de la fête sont les meilleurs. Tout le monde veut un match." }
  { key:"#taxman_desease_can_start_at_any_moment", text:"Il semble qu'une maladie affecte la population. J'espère que la peste ne va pas s'installer ." }
  { key:"#taxman_no_food_in_city", text:"Les habitants devraient payer leurs impôts en nourriture. J'ai si faim !" }
  { key:"#taxman_city_have_no_army", text:"Notre ville n'est pas en mesure de se défendre !" }
  { key:"#taxman_need_more_tax_collectors", text:"Les impôts ne peuvent pas améliorer la situation économique. Il faut plus de travailleurs !" }
  { key:"#taxman_gods_are_angry", text:"Nous avons une grande dette envers les dieux, et ils risquent de nous la faire payer très cher !" }
  { key:"#taxman_city_is_bad", text:"Notre réputation est si faible qu'une invasion semble imminente." }
  { key:"#taxman_much_unemployments", text:"Ces maisons abritent des chômeurs ! Comment pourraient-ils payer leurs impôts ?" }
  { key:"#taxman_low_entertainment", text:"J'aime percevoir les impôts, mais un peu d'amusement ne me dérangerait pas." }
  { key:"#taxman_city_is_good", text:"La vie est assez agréable ici." }
  { key:"#taxman_city_is_amazing", text:"Je ne souhaiterais pas vivre ailleurs !" }
  { key:"#taxman_need_workers", text:"Nous pourrions augmenter le budget de la ville en embauchant plus de percepteurs." }
  { key:"#taxman_high_taxes", text:"Plus les gens ont de l'argent et une belle maison, plus ils rechignent à payer leurs impôts." }
  { key:"#taxman_much_pooh_houses", text:"Je déteste percevoir les impôts de ces pauvres gens. C'est une perte de temps." }
  { key:"#worker_desease_can_start_at_any_moment", text:"Beaucoup de gens tombent malades. J'espère que ça va s'améliorer." }
  { key:"#worker_no_food_in_city", text:"Je meurs de faim. C'est dur de travailler le ventre vide." }
  { key:"#worker_enemies_in_city", text:"J'espère que nos ennemis n'ont pas l'intention de nous envahir, nous serions perdus." }
  { key:"#worker_need_workers", text:"On cherche de la main-d'œuvre partout ! Peut-être y-a-t'il une place de pompier disponible !" }
  { key:"#worker_gods_are_angry", text:"J'espère que les dieux vont se montrer cléments." }
  { key:"#worker_city_is_bad", text:"Il semblerait que la ville ait mauvaise réputation. Nous risquons d'être attaqués !" }
  { key:"#worker_much_unemployments", text:"J'ai de la chance de pouvoir travailler, ce qui n'est pas le cas de tout le monde." }
  { key:"#worker_low_entertainment", text:"Je passe mon temps à travailler. Il n'y a rien d'autre à faire ici." }
  { key:"#worker_city_is_good", text:"Je me sens bien ici, mais je pense pouvoir trouver mieux." }
  { key:"#worker_city_is_amazing", text:"J'espère rester ici toute ma vie !" }
  { key:"#worker_unused", text:"(Non utilisé)" }
  { key:"#worker_going_to_workplace", text:"Je suis prêt à travailler, mais je n'arrive pas à rejoindre la ferme !" }
  { key:"#worker_farm_is_flooded", text:"Mes champs sont inondés, je travaille pour ne pas perdre la main." }
  { key:"#doctor_concerned_about_plague", text:"Je suis très occupé. Beaucoup de malades viennent me voir." }
  { key:"#doctor_no_food_in_city", text:"Je souffre d'avoir constamment faim." }
  { key:"#doctor_defenses_are_weak", text:"Il faudrait que la ville renforce ses défenses pour se protéger contre les ennemis." }
  { key:"#doctor_need_more_workers", text:"Beaucoup de personnes travaillent très dur. La ville devrait embaucher davantage." }
  { key:"#doctor_gods_are_angry", text:"Je pense que nous ne respectons pas assez les dieux. Nous risquons de le regretter." }
  { key:"#doctor_reputation_is_low", text:"Nous risquons d'être attaqués à cause de notre réputation." }
  { key:"#doctor_unemployment_is_high", text:"Attendre en vain du travail nuit à la santé des habitants !" }
  { key:"#doctor_low_entertainment", text:"Certaines personnes ont demandé une consultation car ils n'avaient rien d'autre à faire !" }
  { key:"#doctor_city_is_ok", text:"Je me sens bien ici, mais je pense pouvoir trouver mieux." }
  { key:"#doctor_city_is_the_best", text:"Les habitants de cette ville sont en bonne santé." }
  { key:"#doctor_plague_could_strike_us_dead", text:"La peste peut nous frapper à tout moment !" }
  { key:"#water_desease_can_start_at_any_moment", text:"J'hésite à m'aventurer dans les environs. Les gens sont malades et risquent de m'infecter." }
  { key:"#water_no_food_in_city", text:"La faim me rend si faible. Je croule sous le poids de cette eau." }
  { key:"#water_city_have_no_army", text:"Je crois que les habitants seraient livrés à eux-mêmes en cas d'attaque ennemie." }
  { key:"#water_need_workers", text:"Il y a tant de travail, mais personne n'est disponible." }
  { key:"#water_gods_are_angry", text:"Si j'étais un dieu, je n'apprécierais guère le peu d'attention que cette ville me porte." }
  { key:"#water_city_is_bad", text:"Les autres villes se moquent de nous et envisagent de nous attaquer." }
  { key:"#water_much_unemployments", text:"Je rencontre de nombreuses personnes sans travail lorsque j'effectue mes livraisons." }
  { key:"#water_low_entertainment", text:"Porter de l'eau n'est pas très amusant. Si seulement on avait quelques distractions." }
  { key:"#water_city_is_good", text:"J'aime cette ville, mais si j'en étais le responsable, les choses seraient différentes." }
  { key:"#water_city_is_amazing", text:"C'est le plus bel endroit sur terre." }
  { key:"#osiris_city_low_health", text:"Les gens qui viennent au temple paraissent malades. J'espère qu'il ne s'agit pas d'une épidémie." }
  { key:"#osiris_no_food_in_city", text:"Je n'ai pas assez de nourriture pour Osiris ou moi-même !" }
  { key:"#osiris_city_not_safety", text:"Si seulement Osiris pouvait défendre notre ville. Le gouverneur semble incapable de le faire." }
  { key:"#osiris_need_workers", text:"J'espère que d'autres travailleurs vont arriver. Il risque d'y avoir une pénurie de main-d'œuvre." }
  { key:"#osiris_gods_are_angry", text:"Cette ville aurait intérêt à ne pas négliger les dieux." }
  { key:"#osiris_low_sentiment", text:"La réputation est importante. Sinon, la ville risque d'être envahie par l'ennemi." }
  { key:"#osiris_much_unemployments", text:"Un nombre croissant de gens prient Osiris pour trouver du travail." }
  { key:"#osiris_low_entertainment", text:"J'ai besoin de détente. Je suis fatigué de prier Osiris, il me faut du repos." }
  { key:"#osiris_city_is_good", text:"Je n'ai pas à me plaindre de cette ville." }
  { key:"#osiris_city_is_amazing", text:"Seul l'au-delà est comparable à cette ville." }
  { key:"#osiris_god_love_festival", text:"Osiris aime contempler son peuple pendant les fêtes." }
  { key:"#osiris_city_low_mood", text:"Notre ville est la honte du Royaume." }
  { key:"#osiris_disease_in_city", text:"La maladie arpente les rues. Osiris veille sur les vivants et les morts." }
  { key:"#osiris_need_entertainment", text:"Un peu de musique élèverait les prières autant que les esprits." }
  { key:"#ra_city_low_health", text:"Les gens qui viennent au temple paraissent malades. J'espère qu'il ne s'agit pas d'une épidémie." }
  { key:"#ra_no_food_in_city", text:"Je n'ai pas assez de nourriture pour Rê ou moi-même !" }
  { key:"#ra_city_not_safety", text:"Si seulement Rê pouvait défendre notre ville. Le gouverneur semble incapable de le faire." }
  { key:"#ra_need_workers", text:"J'espère que d'autres travailleurs vont arriver. Il risque d'y avoir une pénurie de main-d'œuvre." }
  { key:"#ra_gods_are_angry", text:"Cette ville aurait intérêt à ne pas négliger les dieux." }
  { key:"#ra_low_sentiment", text:"La réputation est importante. Sinon, la ville risque d'être envahie par l'ennemi." }
  { key:"#ra_much_unemployments", text:"Un nombre croissant de gens prient Rê pour trouver du travail." }
  { key:"#ra_low_entertainment", text:"J'ai besoin de détente. Je suis fatigué de prier Rê, il me faut du repos." }
  { key:"#ra_city_is_good", text:"Je n'ai pas à me plaindre de cette ville." }
  { key:"#ra_city_is_amazing", text:"Seul l'au-delà est comparable à cette ville." }
  { key:"#ra_god_love_festival", text:"Rê aime contempler son peuple pendant les fêtes." }
  { key:"#ra_city_low_mood", text:"Notre ville est la honte du Royaume." }
  { key:"#ra_disease_in_city", text:"La maladie se répand sous le soleil de Rê. Les temples doivent aider." }
  { key:"#ra_need_entertainment", text:"Même les prêtres de Rê ont besoin de divertissement après de longues journées de rituels." }
  { key:"#ptah_city_low_health", text:"Les mauvaises conditions d'hygiène risquent de provoquer la peste si elles ne s'améliorent pas." }
  { key:"#ptah_no_food_in_city", text:"Le bruit de mon estomac vide m'empêche de faire mon devoir envers Ptah." }
  { key:"#ptah_city_not_safety", text:"Nos défenses seront inutiles en cas d'attaque ennemie." }
  { key:"#ptah_need_workers", text:"Ptah est triste de voir que l'industrie stagne du fait du manque de main-d'œuvre." }
  { key:"#ptah_gods_are_angry", text:"Les dieux puniront cette cité si elle continue à les ignorer." }
  { key:"#ptah_low_sentiment", text:"Notre mauvaise réputation risque d'encourager les ennemis." }
  { key:"#ptah_much_unemployments", text:"Ptah souhaite que toutes les personnes sans emploi de la cité trouvent un travail productif." }
  { key:"#ptah_low_entertainment", text:"J'aime m'amuser, comme tout le monde. J'aimerais que cette cité ait davantage de loisirs." }
  { key:"#ptah_city_is_good", text:"Cette cité a ses problèmes, mais il fait bon y vivre." }
  { key:"#ptah_city_is_amazing", text:"C'est la meilleure cité de toute l'Egypte !" }
  { key:"#ptah_god_love_festival", text:"Ptah sait que les ouvriers aiment les vacances." }
  { key:"#ptah_city_low_mood", text:"La main de Ptah ne peut pas plus. Les industries de cette cité ont besoin d'une main-d'œuvre supplémentaire !" }
  { key:"#ptah_disease_in_city", text:"La peste menace les ateliers. Ptah ne peut pas façonner la santé à partir de la négligence." }
  { key:"#ptah_need_entertainment", text:"Artisans et prêtres ont besoin de plus que du travail et des prières." }
  { key:"#seth_city_low_health", text:"La peste risque de faire des ravages dans la cité si l'hygiène ne s'améliore pas." }
  { key:"#seth_no_food_in_city", text:"Je meurs de faim toute la journée. Il me faut de la nourriture." }
  { key:"#seth_city_not_safety", text:"Nous devons compter sur Seth pour nous protéger au combat. Notre cité n'est pas prête à se défendre." }
  { key:"#seth_need_workers", text:"Les services souffrent du manque de main-d'œuvre !" }
  { key:"#seth_gods_are_angry", text:"Cette cité devrait arrêter de provoquer la colère des dieux en restant inactive." }
  { key:"#seth_low_sentiment", text:"Nous saurons bientôt le peu de cas que les autres font de notre cité lorsqu'ils la balaieront de la carte." }
  { key:"#seth_much_unemployments", text:"Les foules de personnes sans travail emplissent les rues." }
  { key:"#seth_low_entertainment", text:"Cet endroit est tellement ennuyeux !" }
  { key:"#seth_city_is_good", text:"Cette cité me convient." }
  { key:"#seth_city_is_amazing", text:"Cette cité n'a pas d'égal dans toute l'Egypte !" }
  { key:"#seth_god_love_festival", text:"Même les guerriers de Seth ont besoin d'une fête de temps en temps." }
  { key:"#seth_city_low_mood", text:"Gloire à l'horizon ! Les ennemis approchent de la ville à grands pas." }
  { key:"#seth_disease_in_city", text:"La maladie affaiblit les guerriers. Seth ne peut pas défendre seul une cité malade." }
  { key:"#seth_need_entertainment", text:"Même les prêtres de Seth ont besoin de plus que d'exercices et de présages." }
  { key:"#bast_city_low_health", text:"Bastet hait de voir tant de gens malades. Pourvu que la peste de s'installe pas." }
  { key:"#bast_no_food_in_city", text:"C'est difficile de trouver de la nourriture dans cette cité. La famine touche tout le monde." }
  { key:"#bast_city_not_safety", text:"Les pauvres défenses de notre cité incitent nos ennemis à nous attaquer." }
  { key:"#bast_need_workers", text:"Notre cité ne peut fonctionner correctement avec si peu de main-d'œuvre." }
  { key:"#bast_gods_are_angry", text:"Les dieux se désintéressent de cette cité. Nous devrions leur montrer plus de respect." }
  { key:"#bast_low_sentiment", text:"La réputation de cette cité est terrible. Nous risquons de subir une invasion à tout moment." }
  { key:"#bast_much_unemployments", text:"Même Bastet peut réjouir le cœur de tant de personnes sans travail." }
  { key:"#bast_low_entertainment", text:"Bastet est horrifiée par le manque de loisirs dans cette cité." }
  { key:"#bast_need_entertainment", text:"Que peut faire une prêtresse ? Il y a si peu de loisirs ici." }
  { key:"#bast_city_is_good", text:"Cette cité n'est pas désagréable." }
  { key:"#bast_city_is_amazing", text:"Cette cité est la meilleure !" }
  { key:"#bast_god_love_festival", text:"Bastet adore les fêtes." }
  { key:"#bast_city_low_mood", text:"Les habitants de cette cité sont extrêmement mécontents. La criminalité risque de se développer." }
  { key:"#bast_disease_in_city", text:"Bastet me donne le pouvoir de guérir les malades avant qu'une épidémie ne se déclare." }
  { key:"#mission2_pottery_step1", text:"Remplir un entrepôt de poteries." }
  { key:"#mission2_pottery_step2", text:"Améliorez l'esthétique de la cité et relisez vos objectifs" }
  { key:"#mission3_brew_beer", text:"Brasser de la bière." }
  { key:"#reach_modest_houses_number", text:"Faire évoluer 10 maisons en Ferme modeste" }
  { key:"#build_tax_collector", text:"Construire un percepteur" }
  { key:"#market_buyer_returning_to", text:"Vers:" }
  { key:"#market_buyer_collecting", text:"Collecte" }
  { key:"#tutorial_goal_education", text:"Construire un appartement spacieux dans la cité." }
  { key:"#tutorial_goal_scribal_school", text:"Fabriquer des papyrus et construire une école." }
  { key:"#tutorial_goal_import_bricks", text:"Importer des briques." }
  { key:"#mission4_goal_spacious_apartment", text:"1/4 Faire évoluer une maison en Appartement spacieux (nourriture, eau, poterie, divertissement)" }
  { key:"#mission4_goal_reed_gatherer", text:"2/4 Construire un cueilleur de roseaux près d'un marais" }
  { key:"#mission4_goal_papyrus_maker", text:"2/4 Construire une fabrique de papyrus et l'approvisionner en roseaux" }
  { key:"#mission4_goal_scribal_school", text:"2/4 Construire une école de scribes, puis stocker 100 papyrus dans un entrepôt" }
  { key:"#mission4_goal_store_papyrus", text:"2/4 Stocker 100 papyrus dans un entrepôt pour débloquer le commerce" }
  { key:"#mission4_goal_import_bricks", text:"3/4 Perwadjyt (300 db) ne vend que des briques — importez-en 100. Nekhen (550) achète du papyrus" }
  { key:"#mission4_goal_build_mastaba", text:"4/4 Construire une guilde de briquetiers et placer un petit mastaba" }
  { key:"#mission4_goal_export_papyrus", text:"Ouvrir Nekhen (550 db), exporter du papyrus, puis atteindre les notes (1500 / 15 / 20 / 9 / 40)" }
  { key:"#mission5_goal_food", text:"1/6 Construire un pavillon de chasse, un grenier et un bazar — la nourriture vient du gibier et des importations" }
  { key:"#mission5_goal_water", text:"1/6 Ajouter l'approvisionnement en eau, plus une caserne de pompiers, un poste d'architecte et un poste de police" }
  { key:"#mission5_goal_mines", text:"2/6 Construire des mines de cuivre et de pierres précieuses et un entrepôt" }
  { key:"#mission5_goal_stock_copper", text:"2/6 Stocker 5 cuivre dans un entrepôt — Pharaon le demande avant le mois 8 de l'année 0" }
  { key:"#mission5_goal_military_industry", text:"3/6 Construire un armurier et un recruteur avant les raids libyens de l'année 2" }
  { key:"#mission5_goal_fort", text:"3/6 Construire un fort d'infanterie ou d'archers — les raids commencent l'année 2, mois 7 (9, puis 16, puis 24)" }
  { key:"#mission5_goal_gems_trade", text:"4/6 Ouvrir Noubt (850 db) ou Thinis (800 db) pour la nourriture ; stocker 15 pierres précieuses avant l'année 2, mois 4" }
  { key:"#mission5_goal_deben", text:"5/6 Garder 885 debens au trésor — Pharaon les demande avant l'année 2, mois 8" }
  { key:"#mission5_goal_weapons", text:"5/6 Produire des armes — Pharaon en demande 11 avant l'année 7, mois 3" }
  { key:"#mission5_goal_win", text:"6/6 Atteindre les objectifs : 2000 habitants, 15 de prospérité, 70 de royaume ; faire évoluer les maisons avec du divertissement" }
  { key:"#none", text:"Rien" }
  { key:"#grain", text:"Céréales" }
  { key:"#meat", text:"Viande" }
  { key:"#lettuce", text:"Laitue" }
  { key:"#chickpeas", text:"Pois chiches" }
  { key:"#pomegranates", text:"Grenades" }
  { key:"#figs", text:"Figues" }
  { key:"#fish", text:"Poisson" }
  { key:"#gamemeat", text:"Gibier" }
  { key:"#straw", text:"Paille" }
  { key:"#weapons", text:"Armes" }
  { key:"#clay", text:"Argile" }
  { key:"#bricks", text:"Briques" }
  { key:"#pottery", text:"Poterie" }
  { key:"#barley", text:"Orge" }
  { key:"#beer", text:"Bière" }
  { key:"#flax", text:"Lin" }
  { key:"#linen", text:"Toile" }
  { key:"#gems", text:"Gemmes" }
  { key:"#luxury_goods", text:"Articles de luxe" }
  { key:"#timber", text:"Bois" }
  { key:"#gold", text:"Or" }
  { key:"#reeds", text:"Roseaux" }
  { key:"#papyrus", text:"Papyrus" }
  { key:"#stone", text:"Pierre" }
  { key:"#limestone", text:"Calcaire" }
  { key:"#granite", text:"Granit" }
  { key:"#chariots", text:"Char" }
  { key:"#copper", text:"Cuivre" }
  { key:"#sandstone", text:"Grès" }
  { key:"#oil", text:"Huile" }
  { key:"#henna", text:"Henné" }
  { key:"#paint", text:"Peinture" }
  { key:"#lamps", text:"Lampes" }
  { key:"#marble", text:"Marbre" }
  { key:"#deben", text:"debens" }
  { key:"#troops", text:"Troupes" }
  { key:"#jewelry_luxury", text:"Bijoux (articles de luxe)" }
  { key:"#jewelry", text:"Bijoux" }
  { key:"#wine_luxury", text:"Vin (articles de luxe)" }
  { key:"#wine", text:"Vin" }
  { key:"#ivory_luxury", text:"Ivoire (articles de luxe)" }
  { key:"#ivory", text:"Ivoire" }
  { key:"#ebony_luxury", text:"Ebène (articles de luxe)" }
  { key:"#ebony", text:"Ebène" }
  { key:"#incense_luxury", text:"Encens (articles de luxe)" }
  { key:"#incense", text:"Encens" }
  { key:"#olive_oil_luxury", text:"Huile d'olive (articles de luxe)" }
  { key:"#olive_oil", text:"Huile d'olive" }
  { key:"#leopard_skins_luxury", text:"Peaux de léopard (articles de luxe)" }
  { key:"#leopard_skins", text:"Peaux de léopard" }
  { key:"#perfume_luxury", text:"Parfum (articles de luxe)" }
  { key:"#perfume", text:"Parfum" }
  { key:"#bandstand_none", text:"Cette maison n'a pas accès à un théâtre de musiciens." }
  { key:"#bandstand_medium", text:"Un musicien est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux théâtres de musiciens." }
  { key:"#bandstand_high", text:"Cette maison a accès à un théâtre de musiciens." }
  { key:"#bandstand_low", text:"Aucun musicien n'est passé près de cette maison depuis longtemps. Celle-ci perdra bientôt son accès aux théâtres de musiciens." }
  { key:"#goods_are_finished", text:"Mes marchandises se vendent comme des petits pains ! Je retourne en prendre au bazar." }
  { key:"#we_are_selling_goods", text:"Je fais tout ce que je peux pour satisfaire mes clients." }
  { key:"#seller_city_has_low_health", text:"Les gens sont malades — dur de vendre quand personne ne veut sortir de chez soi." }
  { key:"#seller_no_food_in_city", text:"Des étals vides et des ventres vides. Qu'est-ce que je suis censée vendre ?" }
  { key:"#seller_city_have_no_army", text:"Pas de forts ? Des pillards vont piller ce bazar avant la fin de ma tournée." }
  { key:"#seller_much_unemployments", text:"Des gens désœuvrés traînent, mais leurs bourses sont vides." }
  { key:"#seller_gods_are_angry", text:"Les dieux semblent en colère. Même les meilleures affaires ne les apaiseront pas." }
  { key:"#seller_city_is_bad_reputation", text:"La réputation de cette cité est si mauvaise que les clients se méfient des prix." }
  { key:"#seller_too_much_unemployments", text:"Trop de chômeurs. Les gens affamés font de piètres clients." }
  { key:"#seller_low_entertainment", text:"Pas de fête depuis une éternité. Un défilé attirerait des acheteurs vers mes paniers." }
  { key:"#seller_city_is_good", text:"Cette cité va bien — rues courtes et clients fidèles." }
  { key:"#seller_city_is_amazing", text:"La meilleure cité pour vendre ! Mes paniers se vident tout seuls." }
  { key:"#scriber_dicease_can_start", text:"Beaucoup de mes clients sont malades. J'espère que ce n'est pas trop grave." }
  { key:"#scriber_these_festivals", text:"Ces fêtes ! J'en ai lu de plus grandioses — une de plus ne ferait pas de mal ici." }
  { key:"#scriber_plague_could_break_out", text:"Beaucoup de mes clients sont malades. J'espère que ce n'est pas trop grave." }
  { key:"#scriber_no_food_in_city", text:"Je meurs de faim. J'ai du mal à soulever les manuscrits le ventre creux." }
  { key:"#scriber_defenses_are_weak", text:"J'espère que nos ennemis n'ont pas l'intention de nous envahir, nous serions perdus." }
  { key:"#scriber_need_more_workers", text:"On cherche de la main-d'œuvre partout ! Peut-être y-a-t'il une place de porteur d'eau disponible !" }
  { key:"#scriber_gods_are_angry", text:"J'espère que les dieux vont épargner ma bibliothèque." }
  { key:"#scriber_reputation_is_low", text:"Il semblerait que la ville ait mauvaise réputation. Nous risquons d'être attaqués !" }
  { key:"#scriber_much_unemployments", text:"Il y a beaucoup de chômeurs dans la cité. Au moins, ils ont tout le temps de lire." }
  { key:"#scriber_high_unemployment", text:"Il y a beaucoup de chômeurs dans la cité. Au moins, ils ont tout le temps de lire." }
  { key:"#scriber_low_entertainment", text:"Je passe mon temps à travailler. Il n'y a rien d'autre à faire ici." }
  { key:"#scriber_city_is_ok", text:"Je me sens bien ici, mais je pense pouvoir trouver mieux." }
  { key:"#scriber_city_is_amazing", text:"J'espère rester ici toute ma vie !" }
  { key:"#teacher_festival_info", text:"Les fêtes enseignent autant que le papyrus — la cité en mériterait une autre." }
  { key:"#teacher_low_entertainment", text:"Pas de spectacle depuis une éternité. Même les élèves se lassent des hiéroglyphes." }
  { key:"#teacher_desease_can_start_at_any_moment", text:"La maladie dans les rues. Dur d'enseigner quand les jeunes ont de la fièvre." }
  { key:"#teacher_no_food_in_city", text:"Des greniers vides ? Les élèves affamés apprennent mal." }
  { key:"#teacher_city_not_safety", text:"Pas de forts ? Les écoles ne protègent guère des envahisseurs." }
  { key:"#teacher_need_workers", text:"Il nous faut plus d'ouvriers — l'éducation seule ne pourvoira pas tous les postes." }
  { key:"#teacher_gods_are_angry", text:"Les dieux semblent en colère. Même les textes les plus sages mettent en garde contre leur courroux." }
  { key:"#teacher_low_rating", text:"Notre réputation auprès de Pharaon est mauvaise. L'histoire ne sera pas tendre." }
  { key:"#teacher_much_unemployments", text:"Tant de chômeurs. Au moins, ils ont le temps d'étudier." }
  { key:"#teacher_city_is_good", text:"Cette cité est un bon endroit pour apprendre et enseigner." }
  { key:"#teacher_city_much_better", text:"Ici, tout va bien mieux que dans les cités dont j'ai lu l'histoire." }
  { key:"#teacher_city_is_amazing", text:"La meilleure cité où j'aie enseigné. Ces élèves écriront l'histoire !" }
  { key:"#tomb_artisan_ready", text:"Argile et peinture prêtes. Décorons la tombe !" }
  { key:"#tomb_artisan_going_to_work", text:"En route pour la tombe — les murs attendent leurs couleurs." }
  { key:"#tomb_artisan_decorating", text:"Pinceau ferme. Ces murs parleront pour l'éternité." }
  { key:"#tomb_artisan_return_home", text:"Décoration terminée pour l'instant. Retour à la guilde." }
  { key:"#tomb_artisan_disease_risk", text:"La fièvre dans les puits funéraires. Dur de peindre avec les mains qui tremblent." }
  { key:"#tomb_artisan_no_food_in_city", text:"Des greniers vides ? Un artisan affamé peint des lignes de travers." }
  { key:"#tomb_artisan_city_have_no_army", text:"Pas de forts ? Un seul raid et ces tombes sont pillées." }
  { key:"#tomb_artisan_gods_are_angry", text:"Les dieux semblent en colère. Même la peinture sacrée pourrait se craqueler." }
  { key:"#tomb_artisan_low_entertainment", text:"Pas de fête depuis une éternité. Même les peintres de tombes ont besoin de la lumière du jour." }
  { key:"#tomb_artisan_city_is_good", text:"Cette cité est solide ! De belles tombes pour de grands souverains." }
  { key:"#tomb_artisan_city_is_amazing", text:"La meilleure cité pour laquelle j'aie peint. Ces murs dureront pour l'éternité !" }
  { key:"#tomb_robber_gold_should_be_for_living", text:"De l'or dans les tombes ? Il devrait servir aux vivants !" }
  { key:"#tomb_robber_just_think_of_the_fortune", text:"Pensez à la fortune qui attend dans cette tombe !" }
  { key:"#tomb_robber_tax_too_high", text:"Les impôts vous dépouillent — moi, je dépouille les morts !" }
  { key:"#tomb_robber_wages_too_low", text:"Salaires trop bas ? Les tombes paient mieux qu'un travail honnête." }
  { key:"#tomb_robber_no_jobs", text:"Pas de travail honnête ? Très bien. Piller les tombes, ça paie." }
  { key:"#tomb_robber_no_food_in_city", text:"Des greniers vides ? L'or remplit toujours les poches." }
  { key:"#tomb_robber_city_have_no_army", text:"Pas de forts ? Des nuits tranquilles parmi les tombes." }
  { key:"#tomb_robber_gods_are_angry", text:"Les dieux en colère ? Parfait — on accusera le ciel, pas moi." }
  { key:"#tomb_robber_low_entertainment", text:"Pas de fêtes ? Piller les tombes, c'est mon divertissement." }
  { key:"#tomb_robber_city_is_good", text:"Jolie cité. Jolies tombes à alléger." }
  { key:"#tomb_robber_city_is_amazing", text:"La meilleure cité à piller — des tombes bien garnies partout !" }
  { key:"#dentist_concerned_about_plague", text:"Les gens ont tellement peur d'attraper la peste qu'ils en négligent l'hygiène dentaire." }
  { key:"#dentist_no_food_in_city", text:"J'ai eu tellement peu à manger ses derniers temps. Mes dents en sont tout abîmées." }
  { key:"#dentist_defenses_are_weak", text:"Les défenses de la cité sont irrégulières. Nos ennemis risquent de nous attaquer." }
  { key:"#dentist_need_more_workers", text:"La main-d'œuvre de cette cité est comme la bouche d'un vieil homme. Tant de trous à combler !" }
  { key:"#dentist_gods_are_angry", text:"Nous devrions montrer plus de respect envers les dieux." }
  { key:"#dentist_reputation_is_low", text:"Notre réputation est terrible. Nous risquons d'être attaqués." }
  { key:"#dentist_much_unemployments", text:"Je n'ai jamais vu autant de personnes sans travail !" }
  { key:"#dentist_low_entertainment", text:"Je m'ennuie ! Je crois que je vais encore me brosser les dents." }
  { key:"#dentist_city_is_ok", text:"Cette cité est correcte." }
  { key:"#dentist_city_is_amazing", text:"Cette cité rayonne dans toute l'Egypte." }
  { key:"#zookeeper_danger_of_plague", text:"La peste dans les rues ? Je ne vais pas risquer de ramener la maladie aux animaux." }
  { key:"#zookeeper_no_food_in_city", text:"Des greniers vides pour les gens — et il faut toujours nourrir les cages. Ça ne peut pas durer." }
  { key:"#zookeeper_defenses_are_weak", text:"Des ennemis aux portes ? Gardez les cages fermées et les visiteurs à l'intérieur." }
  { key:"#zookeeper_need_more_workers", text:"Du travail partout — même le zoo aurait besoin de plus de gardiens." }
  { key:"#zookeeper_gods_are_angry", text:"Des dieux en colère rendent les bêtes nerveuses. Nous devrions montrer plus de respect." }
  { key:"#zookeeper_reputation_is_low", text:"La réputation de notre cité est aussi sauvage qu'un lion affamé. Nous pourrions être attaqués." }
  { key:"#zookeeper_high_unemployment", text:"Tant de bras inoccupés. Au moins, les animaux ne se plaignent jamais des heures sup." }
  { key:"#zookeeper_low_entertainment", text:"Pas de fête depuis une éternité. Le zoo est le seul spectacle qui reste en ville." }
  { key:"#zookeeper_city_is_ok", text:"Cette cité va assez bien — les animaux semblent contents, et moi aussi." }
  { key:"#zookeeper_city_is_amazing", text:"La meilleure cité dont un gardien puisse rêver. Même les lions ronronnent pour Pharaon !" }
  { key:"#warship_well_fight_to_the_death", text:"Nous nous battrons jusqu'à la mort ! Pour Pharaon et le fleuve !" }
  { key:"#warship_enemy_is_too_much_for_us", text:"Cet ennemi est trop fort pour nous. Repli vers le quai !" }
  { key:"#warship_enemies_coming_this_way", text:"Des ennemis arrivent par ici ! Préparez les archers !" }
  { key:"#warship_ready_to_attack_invaders", text:"Prêts à attaquer les envahisseurs. Le Nil est à nous." }
  { key:"#warship_ready_if_foes_come", text:"Prêts si l'ennemi vient. Notre coque est solide." }
  { key:"#transport_must_protect_our_ship", text:"Nous devons protéger notre navire et les troupes à bord." }
  { key:"#transport_enemy_is_here", text:"L'ennemi est là ! Protégez le transport !" }
  { key:"#transport_were_prepared", text:"Nous sommes prêts. Les troupes peuvent embarquer sur ordre." }
  { key:"#transport_ready_if_need_arises", text:"Prêts en cas de besoin. Les soldats de Pharaon attendent." }
  { key:"#embalmer_concerned_about_plague", text:"Il y a trop de malades, je suis débordé !" }
  { key:"#embalmer_no_food_in_city", text:"Je meurs de faim. Je vais bientôt ressembler à une momie !" }
  { key:"#embalmer_defenses_weak", text:"J'espère que nos ennemis n'ont pas l'intention de nous envahir, nous serions perdus." }
  { key:"#embalmer_need_more_workers", text:"On cherche de la main-d'œuvre partout ! Peut-être y-a-t'il une place de tisserand disponible !" }
  { key:"#embalmer_gods_are_angry", text:"J'espère que les dieux vont se montrer cléments." }
  { key:"#embalmer_reputation_is_low", text:"Il semblerait que la ville ait mauvaise réputation. Nous risquons d'être attaqués !" }
  { key:"#embalmer_unemployment_is_high", text:"J'ai la chance de pouvoir travailler, ce qui n'est pas le cas de tout le monde." }
  { key:"#embalmer_low_entertainment", text:"Je passe mon temps à travailler. Il n'y a rien d'autre à faire ici." }
  { key:"#embalmer_city_is_ok", text:"Autant vivre ici. C'est à peu près aussi bien qu'ailleurs." }
  { key:"#embalmer_city_is_the_best", text:"J'espère rester ici toute ma vie !" }
  { key:"#embalmer_health_worsening", text:"L'hygiène semble empirer dans toute la cité." }
  { key:"#drunkard_need_drink", text:"Je suis sec comme le désert. C'est l'heure de boire un coup !" }
  { key:"#drunkard_going_to_tavern", text:"Maison de senet, me voilà ! Ne commencez pas sans moi." }
  { key:"#drunkard_time_for_beer", text:"Ah, la bière ! Le seul fleuve où ça ne me dérange pas de me noyer." }
  { key:"#drunkard_feeling_dizzy", text:"La rue n'arrête pas de bouger. Ou c'est moi ?" }
  { key:"#drunkard_oh_my_stomach", text:"Ouh... mon estomac. Trop de bière, pas assez de bon sens." }
  { key:"#drunkard_going_home", text:"À la maison... si je me souviens quelle porte est la mienne." }
  { key:"#drunkard_disease_risk", text:"Tout le monde est malade. La bière est le seul remède auquel je crois." }
  { key:"#drunkard_no_food_in_city", text:"Pas de nourriture en ville ? Très bien — la bière, c'est un repas, en plissant les yeux." }
  { key:"#drunkard_city_have_no_army", text:"Pas de forts ? Si des envahisseurs arrivent, cachez-moi derrière une jarre de bière." }
  { key:"#drunkard_need_workers", text:"Pas assez d'ouvriers ? Embauchez-moi — j'irai chercher la bière." }
  { key:"#drunkard_gods_are_angry", text:"Les dieux sont en colère. Servez-leur une tournée, ils se calmeront peut-être." }
  { key:"#drunkard_city_is_bad", text:"La réputation de cette cité est pire que ma gueule de bois." }
  { key:"#drunkard_much_unemployment", text:"Tant de gens désœuvrés. Parfait pour trinquer !" }
  { key:"#drunkard_low_entertainment", text:"Pas de fêtes ? Alors la maison de senet est le seul spectacle en ville." }
  { key:"#drunkard_city_is_good", text:"Cette cité n'est pas mal. Courte marche jusqu'à la bière, longue marche pour rentrer." }
  { key:"#drunkard_city_is_amazing", text:"La meilleure cité pour un buveur ! Que les jarres ne soient jamais vides." }
  { key:"#magistrate_i_hope_we_are_ready", text:"Les enterrements me dépriment." }
  { key:"#magistrate_no_criminals_in_city", text:"Les gens sont sympathiques. Personne ne se plaint de violences." }
  { key:"#magistrate_all_good_in_city", text:"On nous signale quelques crimes de-ci de-là, mais rien d'anormal." }
  { key:"#magistrate_streets_still_arent_safety", text:"Moi-même, je ne m'aventure pas dans cet endroit de la ville !" }
  { key:"#magistrate_disease_in_city", text:"Beaucoup de personnes sont malades et faibles. Je crains pour notre avenir." }
  { key:"#magistrate_no_food_in_city", text:"Je n'ai rien avalé depuis des jours. Je serai bientôt obligé de voler pour manger !" }
  { key:"#magistrate_city_not_safety", text:"En cas d'invasion, je serai le seul capable de défendre la ville." }
  { key:"#magistrate_need_workers", text:"Si la justice ne me passionnait pas autant, je choisirais un des nombreux postes vacants." }
  { key:"#magistrate_gods_are_angry", text:"Si j'étais le magistrat de la ville, je m'occuperais davantage des dieux." }
  { key:"#magistrate_city_bad_reputation", text:"Notre ville est une proie facile pour nos ennemis. Nous avons une mauvaise réputation." }
  { key:"#magistrate_much_unemployments", text:"Je n'aime pas tous ces gens désœuvrés. Je ne peux pas me rendre au travail sans en rencontrer !" }
  { key:"#magistrate_no_entertainment_need", text:"Cette ville semble morte. Il n'y a aucune animation." }
  { key:"#magistrate_city_not_bad", text:"Cette ville n'est pas parfaite, mais elle me plaît." }
  { key:"#magistrate_city_is_amazing", text:"J'aime rendre la justice dans cette ville !" }
  { key:"#magistrate_not_used", text:"(Non utilisé)" }
  { key:"#magistrate_need_embalmers", text:"Les enterrements me dépriment." }
  { key:"#magistrate_courthouse_in_peace", text:"Les gens sont sympathiques. Personne ne se plaint de violences." }
  { key:"#magistrate_i_have_only_minor_cases", text:"On nous signale quelques crimes de-ci de-là, mais rien d'anormal." }
  { key:"#magistrate_i_am_overwhelmed", text:"Moi-même, je ne m'aventure pas dans cet endroit de la ville !" }
  { key:"#goto_site_of_event", text:"Aller vers le site" }
  { key:"#hold_festival_to", text:"Organiser une fête pour" }
  { key:"#god_osiris", text:"Osiris" }
  { key:"#god_ra", text:"Rê" }
  { key:"#god_ptah", text:"Ptah" }
  { key:"#god_seth", text:"Seth" }
  { key:"#god_bast", text:"Bastet" }
  { key:"#god_to_osiris", text:"Osiris" }
  { key:"#god_to_ra", text:"Rê" }
  { key:"#god_to_ptah", text:"Ptah" }
  { key:"#god_to_seth", text:"Seth" }
  { key:"#god_to_bast", text:"Bastet" }
  { key:"#difficulty_settings", text:"Réglages de difficulté" }
  { key:"#difficulty_row_difficulty", text:"Difficulté" }
  { key:"#difficulty_row_gods", text:"Effets des dieux" }
  { key:"#difficulty_right_click_to_continue", text:"Clic droit pour continuer" }
  { key:"#difficulty_very_easy", text:"Très facile" }
  { key:"#difficulty_easy", text:"Facile" }
  { key:"#difficulty_normal", text:"Normal" }
  { key:"#difficulty_hard", text:"Difficile" }
  { key:"#difficulty_very_hard", text:"Très difficile" }
  { key:"#difficulty_gods_effects_off", text:"Pas d'influence des dieux" }
  { key:"#difficulty_gods_effects_on", text:"Influence des dieux" }
  { key:"#food_stocks_not_provided", text:"Les habitants de cette hutte en sont à fouiller dans les détritus..." }
  { key:"#food_stocks_none", text:"Cette maison n'a pas de réserve de nourriture." }
  { key:"#food_stocks_low", text:"Cette maison aura bientôt épuisé sa réserve de nourriture." }
  { key:"#food_stocks_medium", text:"Cette maison dispose de réserves de nourriture pour les mois à venir." }
  { key:"#food_stocks_high", text:"Cette maison n'a pas de mal à obtenir la nourriture dont elle a besoin." }
  { key:"#beer_stocks_none", text:"Cette maison n'a plus de réserves de bière" }
  { key:"#beer_stocks_low", text:"Cette maison aura bientôt bu ses maigres réserves de bière" }
  { key:"#beer_stocks_medium", text:"Cette maison a assez de bière pour au moins le mois à venir" }
  { key:"#beer_stocks_high", text:"Cette maison n'a aucun problème pour obtenir la bière dont elle a besoin" }
  { key:"#apothecary_access_none", text:"Cette maison n'a pas accès à une pharmacie." }
  { key:"#apothecary_access_high", text:"Un herboriste est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux pharmacies." }
  { key:"#apothecary_access_medium", text:"Cette maison a accès à une pharmacie." }
  { key:"#apothecary_access_low", text:"A moins qu'un herboriste ne passe ici bientôt, cette maison perdra son accès à la pharmacie." }
  { key:"#magistrate_access_none", text:"Cette maison n'a pas accès à un palais de justice." }
  { key:"#magistrate_access_high", text:"Cette maison a été récemment visitée par un magistrat. Elle aura bientôt accès à un palais de justice." }
  { key:"#magistrate_access_medium", text:"Cette maison a accès à un palais de justice." }
  { key:"#magistrate_access_low", text:"Cette maison n'a pas été visitée par un magistrat depuis longtemps. Elle n'aura bientôt plus accès à un palais de justice." }
  { key:"#booth_access_none", text:"Cette maison n'a pas accès à un numéro de jongleur." }
  { key:"#booth_access_high", text:"Un jongleur est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux numéros de jongleurs." }
  { key:"#booth_access_medium", text:"Cette maison a accès à un numéro de jongleur." }
  { key:"#booth_access_low", text:"Aucun jongleur n'est passé près de cette maison depuis longtemps. Celle-ci perdra bientôt son accès aux numéros de jongleurs." }
  { key:"#health_risk_none", text:"Ce bâtiment est tout à fait salubre." }
  { key:"#health_risk_negligible", text:"Ce bâtiment a des problèmes mineurs de salubrité." }
  { key:"#health_risk_some", text:"Ce bâtiment présente des signes d'insalubrité." }
  { key:"#health_risk_high", text:"Ce bâtiment n'est pas salubre" }
  { key:"#health_diseased", text:"Ce bâtiment est totalement insalubre." }
  { key:"#malaria_risk_negligible", text:"Ce bâtiment est à la limite d'une zone de malaria." }
  { key:"#malaria_risk_some", text:"Ce bâtiment est dans une zone à risque de malaria." }
  { key:"#malaria_risk_present", text:"Ce bâtiment est dans une zone de malaria." }
  { key:"#malaria_risk_imminent", text:"Les habitants de ce bâtiment seront vite atteints par la malaria." }
  { key:"#malaria_risk_critical", text:"Risque de malaria." }
  { key:"#damage_risk_perfect", text:"Ce bâtiment est en parfaite condition structurelle." }
  { key:"#damage_risk_negligible", text:"Ce bâtiment est légèrement endommagé." }
  { key:"#damage_risk_low", text:"Ce bâtiment est endommagé." }
  { key:"#damage_risk_some", text:"Ce bâtiment est branlant." }
  { key:"#damage_risk_many", text:"Ce bâtiment est branlant et plein de fissures." }
  { key:"#damage_risk_critical", text:"Ce bâtiment tient debout car il n'y a pas de vent aujourd'hui." }
  { key:"#fire_risk_none", text:"Ce bâtiment ne risque pas de prendre feu." }
  { key:"#fire_risk_negligible", text:"Ce bâtiment présente un faible risque d'incendie." }
  { key:"#fire_risk_low", text:"Ce bâtiment pourrait éventuellement prendre feu." }
  { key:"#fire_risk_some", text:"Ce bâtiment risque de prendre feu." }
  { key:"#fire_risk_high", text:"Ce bâtiment est très susceptible de prendre feu." }
  { key:"#fire_risk_critical", text:"Ce bâtiment risque de prendre feu très prochainement !" }
  { key:"#tax_income_not_registered", text:"Cette maison n'est pas dans une région administrée, et ne paye donc pas d'impôts." }
  { key:"#tax_income_none_yet", text:"Aucun impôt collecté dans cette maison cette année." }
  { key:"#tax_income_collected", text:"debens collectés jusqu'à présent." }
  { key:"#entertainment_access_none", text:"Cette demeure n'a accès à aucune forme de loisirs." }
  { key:"#entertainment_access_barely", text:"Cette demeure peut difficilement avoir accès à des lieux de divertissement." }
  { key:"#entertainment_access_very_limited", text:"Cette demeure a un accès très limité à des lieux de divertissement." }
  { key:"#entertainment_access_limited", text:"Cette demeure a un accès limité à des lieux de divertissement." }
  { key:"#entertainment_access_some", text:"Cette demeure a accès à des lieux de divertissement." }
  { key:"#entertainment_access_several", text:"Cette demeure a accès à plusieurs lieux de divertissement." }
  { key:"#entertainment_access_reasonable", text:"Cette demeure peut correctement accéder à des lieux de divertissement." }
  { key:"#entertainment_access_good", text:"Cette demeure a facilement accès à des lieux de divertissement." }
  { key:"#entertainment_access_very_good", text:"Cette demeure a très facilement accès à des lieux de divertissement." }
  { key:"#entertainment_access_excellent", text:"Cette demeure dispose d'un accès excellent à des lieux de divertissement." }
  { key:"#entertainment_access_max", text:"Cette demeure a aisément accès à toutes les formes de divertissements imaginables." }
  { key:"#senet_access_none", text:"Cette maison n'a pas accès à une taverne de jeux." }
  { key:"#senet_access_high", text:"Un maître de senet est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux tavernes de jeux." }
  { key:"#senet_access_medium", text:"Cette maison a accès à une taverne de jeux." }
  { key:"#senet_access_low", text:"Aucun maître de senet n'est passé près de cette maison depuis longtemps. Celle-ci perdra bientôt son accès aux tavernes de jeux." }
  { key:"#overlay_zoo", text:"Zoo" }
  { key:"#pavilion_access_none", text:"Cette maison n'a pas accès à un théâtre de danse." }
  { key:"#pavilion_access_high", text:"Un danseur est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux théâtres de danse." }
  { key:"#pavilion_access_medium", text:"Cette maison a accès à un théâtre de danse." }
  { key:"#pavilion_access_low", text:"Aucun danseur n'est passé près de cette maison depuis longtemps. Celle-ci perdra bientôt son accès aux théâtres de danse." }
  { key:"#mortuary_access_none", text:"Cette maison n'a pas accès à une salle des embaumeurs." }
  { key:"#mortuary_access_high", text:"Un embaumeur est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux salles d'embaumeurs." }
  { key:"#mortuary_access_medium", text:"Cette maison a accès à une salle des embaumeurs." }
  { key:"#mortuary_access_low", text:"A moins qu'un embaumeur ne passe ici bientôt, cette maison perdra son accès aux salles d'embaumeurs." }
  { key:"#dentist_access_none", text:"Cette maison n'a pas accès à un cabinet dentaire." }
  { key:"#dentist_access_high", text:"Un dentiste est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux cabinets dentaires." }
  { key:"#dentist_access_medium", text:"Cette maison a accès à un cabinet dentaire." }
  { key:"#dentist_access_low", text:"A moins qu'un dentiste ne passe ici bientôt, cette maison perdra son accès aux cabinets dentaires." }
  { key:"#physician_access_none", text:"Aucun accès à des dispensaires." }
  { key:"#physician_access_low", text:"Aucun médecin n'est passé près de cette maison depuis longtemps." }
  { key:"#physician_access_medium", text:"Un médecin est déjà passé devant cette maison." }
  { key:"#physician_access_high", text:"Un médecin est passé récemment devant cette maison." }
  { key:"#education_access_none", text:"Cette maison n'a aucun accès aux écoles de scribes ou aux bibliothèques." }
  { key:"#education_access_school_or_library", text:"Cette maison a accès à une école de scribe ou à une bibliothèque." }
  { key:"#education_access_school_and_library", text:"Cette maison a accès à une école de scribe et à une bibliothèque." }
  { key:"#education_access_academy_district", text:"Cette maison a accès à une école de scribe et à une bibliothèque. Les enfants qui y habitent sont également dans le quartier de l'académie." }
  { key:"#religion_access_none", text:"Cette maison n'a accès à aucun temple." }
  { key:"#religion_access_one", text:"Cette maison a accès au temple d'une seule divinité." }
  { key:"#religion_access_two", text:"Cette maison a accès aux temples de deux divinités." }
  { key:"#religion_access_three", text:"Cette maison a accès aux temples de trois divinités." }
  { key:"#religion_access_four", text:"Cette maison a accès aux temples de quatre divinités." }
  { key:"#religion_access_all", text:"Cette maison a accès aux temples de toutes les divinités." }
  { key:"#religion_access_shrine_and_all", text:"Cette maison a accès à un sanctuaire et aux temples de toutes les divinités." }
  { key:"#school_access_none", text:"Cette maison n'a pas accès à une école de scribes." }
  { key:"#school_access_high", text:"Un érudit est passé récemment près de cette maison. Celle-ci dispose d'un accès durable à l'école de scribes." }
  { key:"#school_access_medium", text:"Cette maison a accès à une école de scribe." }
  { key:"#school_access_low", text:"A moins qu'un érudit ne passe ici bientôt, cette maison perdra son accès à l'école de scribes." }
  { key:"#library_access_none", text:"Cette maison n'a pas accès à une bibliothèque." }
  { key:"#library_access_high", text:"Un bibliothécaire est passé récemment près de cette maison. Elle gardera donc un accès à la bibliothèque pendant longtemps." }
  { key:"#library_access_medium", text:"Cette maison a accès à une bibliothèque." }
  { key:"#library_access_low", text:"A moins qu'un bibliothécaire ne passe ici bientôt, cette maison perdra son accès à la bibliothèque." }
  { key:"#library_read_about_festivals", text:"J'ai lu des récits de fêtes dans des cités lointaines. Il nous en faudrait une ici." }
  { key:"#library_people_are_sick", text:"Les gens sont malades. Même les papyrus médicaux ont l'air inquiets." }
  { key:"#library_no_food_in_city", text:"Dur de se concentrer sur les rouleaux quand la cité a faim." }
  { key:"#library_defenses_are_weak", text:"Nos défenses sont aussi minces que du papyrus. Un seul raid et la bibliothèque brûle." }
  { key:"#library_need_more_workers", text:"Sans plus d'ouvriers, même les rayonnages resteront sans lecteurs." }
  { key:"#library_gods_are_angry", text:"Les textes mettent en garde contre la colère des dieux. Nous devrions les écouter." }
  { key:"#library_reputation_is_low", text:"Une cité à la mauvaise réputation garde rarement longtemps ses bibliothèques." }
  { key:"#library_high_unemployment", text:"Tant de bras inoccupés. Au moins, ils ont le temps d'emprunter un rouleau." }
  { key:"#library_low_entertainment", text:"Parfois, les yeux ont besoin de repos loin des hiéroglyphes. Je veux un spectacle !" }
  { key:"#library_city_is_ok", text:"Cette cité va bien — comparable à celles que j'ai cataloguées." }
  { key:"#library_city_is_amazing", text:"Cette cité mérite sa place dans les plus belles histoires !" }
  { key:"#academy_access_none", text:"Cette maison n'a pas accès à une académie." }
  { key:"#academy_access_high", text:"Un professeur est passé récemment près de cette maison. Elle gardera donc un accès à l'académie pendant longtemps." }
  { key:"#academy_access_medium", text:"Cette maison a accès à une académie." }
  { key:"#academy_access_low", text:"A moins qu'un professeur ne passe ici bientôt, cette maison perdra son accès à l'académie." }
  { key:"#top_menu_file", text:"Fichier" }
  { key:"#top_menu_file_tooltip", text:"Charger, enregistrer, nouvelle partie et quitter" }
  { key:"#top_menu_options", text:"Options" }
  { key:"#top_menu_options_tooltip", text:"Réglages de l'affichage, du son, de la vitesse et de la difficulté" }
  { key:"#top_menu_help", text:"Aide" }
  { key:"#top_menu_help_tooltip", text:"Obtenir de l'aide, des conseils et des informations sur le jeu" }
  { key:"#top_menu_overseers", text:"Conseillers" }
  { key:"#top_menu_overseers_tooltip", text:"Consultez vos conseillers sur l'état de la cité" }
  { key:"#top_menu_funds", text:"Db" }
  { key:"#top_menu_population", text:"Pop" }
  { key:"#top_menu_new_game", text:"Nouvelle partie" }
  { key:"#top_menu_load_game", text:"Charger" }
  { key:"#top_menu_save_game", text:"Enregistrer" }
  { key:"#top_menu_exit_game", text:"Quitter" }
  { key:"#top_menu_delete_game", text:"Supprimer une partie" }
  { key:"#top_menu_display_settings", text:"Affichage" }
  { key:"#top_menu_sound_settings", text:"Son" }
  { key:"#top_menu_speed_settings", text:"Vitesse" }
  { key:"#top_menu_pyramid_speedup_off", text:"Pyram. accélér. - OFF" }
  { key:"#top_menu_pyramid_speedup_on", text:"Pyram. accélér. - ON" }
  { key:"#top_menu_difficulty", text:"Difficulté" }
  { key:"#top_menu_cities_egyptian", text:"Cités - Egypte" }
  { key:"#top_menu_cities_classical", text:"Cités - Epoque classique" }
  { key:"#top_menu_popup_messages", text:"Messages" }
  { key:"#top_menu_help_item", text:"Aide" }
  { key:"#top_menu_mouse_help_off", text:"Pas de bulles d'aide" }
  { key:"#top_menu_mouse_help_some", text:"Quelques bulles d'aide" }
  { key:"#top_menu_mouse_help_full", text:"Toutes les bulles d'aide" }
  { key:"#top_menu_warnings_off", text:"Pas d'avertissements" }
  { key:"#top_menu_warnings_on", text:"Avertissements" }
  { key:"#top_menu_about", text:"A propos de Pharaon" }
  { key:"#top_menu_advisor_labor", text:"Chef de la main-d'œuvre" }
  { key:"#top_menu_advisor_military", text:"Chef militaire" }
  { key:"#top_menu_advisor_imperial", text:"Chef politique" }
  { key:"#top_menu_advisor_ratings", text:"Chef des niveaux" }
  { key:"#top_menu_advisor_trade", text:"Chef du commerce" }
  { key:"#top_menu_advisor_population", text:"Chef de la nourriture" }
  { key:"#top_menu_advisor_health", text:"Chef de l'hygiène" }
  { key:"#top_menu_advisor_education", text:"Chef de l'éducation" }
  { key:"#top_menu_advisor_entertainment", text:"Chef des loisirs" }
  { key:"#top_menu_advisor_religion", text:"Chef des temples" }
  { key:"#top_menu_advisor_financial", text:"Chef des finances" }
  { key:"#top_menu_advisor_chief", text:"Responsable" }
  { key:"#monthly_autosave_on", text:"Enregistrement mensuel auto" }
  { key:"#monthly_autosave_off", text:"Pas d'enregistrement auto" }
  { key:"#top_menu_funds_tooltip", text:"Fonds actuels de la cité" }
  { key:"#top_menu_population_tooltip", text:"Population actuelle de la cité" }
  { key:"#top_menu_date_tooltip", text:"Date" }
  { key:"#month_jan", text:"Jan" }
  { key:"#month_feb", text:"Fév" }
  { key:"#month_mar", text:"Mar" }
  { key:"#month_apr", text:"Avr" }
  { key:"#month_may", text:"Mai" }
  { key:"#month_jun", text:"Jun" }
  { key:"#month_jul", text:"Jul" }
  { key:"#month_aug", text:"Aoû" }
  { key:"#month_sep", text:"Sep" }
  { key:"#month_oct", text:"Oct" }
  { key:"#month_nov", text:"Nov" }
  { key:"#month_dec", text:"Déc" }
  { key:"#top_menu_debug", text:"Débogage" }
  { key:"#top_menu_debug_render", text:"Rendu" }
  { key:"#top_menu_cheat_console", text:"Console de triche" }
  { key:"#top_menu_properties_on", text:"Propriétés ON" }
  { key:"#top_menu_properties_off", text:"Propriétés OFF" }
  { key:"#top_menu_terrain_paint_on", text:"Peinture du terrain ON" }
  { key:"#top_menu_terrain_paint_off", text:"Peinture du terrain OFF" }
  { key:"#top_menu_write_video_on", text:"Enregistrer la vidéo ON" }
  { key:"#top_menu_write_video_off", text:"Enregistrer la vidéo OFF" }
  { key:"#top_menu_buildings_on", text:"Bâtiments ON" }
  { key:"#top_menu_buildings_off", text:"Bâtiments OFF" }
  { key:"#top_menu_js_debugger_on", text:"Débogueur JS ON" }
  { key:"#top_menu_js_debugger_off", text:"Débogueur JS OFF" }
  { key:"#top_menu_editor_new_map", text:"Nouvelle carte" }
  { key:"#top_menu_editor_load_map", text:"Charger la carte" }
  { key:"#top_menu_editor_save_map", text:"Enregistrer la carte" }
  { key:"#top_menu_editor_exit", text:"Quitter l'éditeur" }
  { key:"#top_menu_editor_resets", text:"Réinitialiser" }
  { key:"#top_menu_editor_clear_herds", text:"Effacer les points de prédateurs" }
  { key:"#top_menu_editor_clear_fish", text:"Effacer les points de pêche" }
  { key:"#top_menu_editor_clear_invasions", text:"Effacer les points d'invasions" }
  { key:"#top_menu_editor_empire", text:"Royaume" }
  { key:"#top_menu_editor_empire_choose", text:"Modifier le royaume" }
  { key:"#sidebar_speed_header", text:"Vitesse" }
  { key:"#no_requests", text:"Aucune requête n'est formulée pour le moment." }
  { key:"#crete", text:"CRETE" }
  { key:"#cyprus", text:"CHYPRE" }
  { key:"#eastern_africa", text:"AFRIQUE ORIENTALE" }
  { key:"#eastern_desert", text:"DESERT ORIENTAL" }
  { key:"#greece", text:"GRECE" }
  { key:"#libya", text:"LIBYE" }
  { key:"#lower_egypt", text:"BASSE-EGYPTE" }
  { key:"#delta", text:"DELTA" }
  { key:"#fayuum", text:"FAYOUM" }
  { key:"#nubia", text:"NUBIE" }
  { key:"#palestine", text:"PALESTINE" }
  { key:"#sinai", text:"SINAI" }
  { key:"#syria", text:"SYRIE" }
  { key:"#upper_egypt", text:"HAUTE-EGYPTE" }
  { key:"#western_desert", text:"DESERT OCCIDENTAL" }
  { key:"#lebanon", text:"LIBAN" }
  { key:"#canaan", text:"CANAAN" }
]
