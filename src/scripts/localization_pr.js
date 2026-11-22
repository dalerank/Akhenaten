log_info("akhenaten: localization_pr config started")

localization_pr = [
     { key: "#TR_NO_PATCH_TITLE", text:""},
     { key: "#TR_NO_PATCH_MESSAGE", text:""},
     { key: "#TR_MISSING_FONTS_TITLE", text:"Fontes faltando"},
     { key: "#TR_MISSING_FONTS_MESSAGE", text:"" },
     { key: "#TR_NO_EDITOR_TITLE", text:"Editor não instalado"},
     { key: "#TR_NO_EDITOR_MESSAGE", text:"" },
     { key: "#TR_INVALID_LANGUAGE_TITLE", text:"Pasta de idioma inválida"},
     { key: "#TR_INVALID_LANGUAGE_MESSAGE", text:"A pasta selecionada não contém um pacote de idioma válido. Verifique o arquivo de registro para ver os erros"},
     { key: "#dock_order_trade", text:"Comerciar"},
     { key: "#dock_order_dont_trade", text:"Não comerciar"},
     { key: "#dock_order_accept_all", text:"Aceitar tudo"},
     { key: "#dock_orders_hint", text:"Navios só usam este cais se pelo menos uma das mercadorias estiver em Comerciar."},
     { key: "#dock_orders_closed", text:"Este cais não aceita mercadorias — navios não atracarão aqui."},
     { key: "#TR_BUTTON_OK", text:"OK"},
     { key: "#TR_BUTTON_CANCEL", text:"Cancelar"},
     { key: "#TR_BUTTON_RESET_DEFAULTS", text:"Redefinir padrões"},
     { key: "#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Configurar atalhos"},
     { key: "#TR_CONFIG_TITLE", text:"Opções de Configurações"},
     { key: "#TR_CONFIG_LANGUAGE_LABEL", text:"Idioma:"},
     { key: "#TR_CONFIG_LANGUAGE_DEFAULT", text:"(padrão)"},
     { key: "#TR_CONFIG_HEADER_UI_CHANGES", text:"Mudanças de interface"},
     { key: "#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Mudanças de jogabilidade"},
     { key: "#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"},
     { key: "#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"},
     { key: "#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"},
     { key: "#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Tocar vídeos de abertura"},
     { key: "#TR_CONFIG_SIDEBAR_INFO", text:"Informação extra no painel de controle"},
     { key: "#TR_CONFIG_SMOOTH_SCROLLING", text:"Ativar rolagem suave"},
     { key: "#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Ativar indicador visual ao limpar o terreno"},
     { key: "#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Permitir construir cada templo em sequência"},
     { key: "#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Mostrar alcance ao construir reservatórios, fontes e poços"},
     { key: "#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Mostrar o tamanho da construção ao arrastar"},
     { key: "#TR_CONFIG_HIGHLIGHT_LEGIONS", text:"Realçar legiões focadas pelo mouse"},
     { key: "#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Consertar falha durante a imigração na dificuldade máxima"},
     { key: "#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Consertar falha dos 'fantasmas' de 100 anos"},
     { key: "#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Consertar falha na mudança de Imperador e tempo de sobrevivência"},
     { key: "#TR_CONFIG_AUTO_RESOLVE_INVASIONS", text:"Auto-resolver invasões: congelar na entrada, batalha rápida em 8 dias"},
     { key: "#TR_CONFIG_HISTORICAL_ECONOMY", text:"Enhanced: economia histórica — deben como unidade de conta; parte dos salários em grão dos celeiros"},
     { key: "#finance_deben_unit_of_account", text:"peso-deben"},
     { key: "#finance_historical_economy_hint", text:"Os deben medem valor (peso de metal). Parte do trabalho é paga em grão dos celeiros se houver."},
     { key: "#finance_wages_paid_in_grain", text:"Salários em grão (eq. deben)"},
     { key: "#warning_auto_resolve_orders_blocked", text:"Não é possível marchar companhias sobre uma onda de invasão congelada"},
     { key: "#warning_auto_resolve_queue_full", text:"Demasiadas invasões pendentes — esta onda combate no mapa"},
     { key: "#follow_walker", text:"Seguir caminhante"},
     { key: "#stop_following", text:"Parar"},
     { key: "#warning_follow_walker_lost", text:"Caminhante seguido perdido"},
     { key: "#invasion_quick_battle_title", text:"Batalha rápida"},
     { key: "#invasion_quick_battle_hint", text:"Os invasores aguardam na entrada. Recrute se precisar. Combata agora ou espere o temporizador."},
     { key: "#invasion_quick_battle_resolve", text:"Combater"},
     { key: "#invasion_quick_battle_wait", text:"Esperar"},
     { key: "#invasion_quick_battle_strength", text:"Suas forças: {player}   Inimigo: {enemy}"},
     { key: "#invasion_quick_battle_days", text:"Batalha em {days} dias"},
     { key: "#invasion_quick_battle_queue", text:"({n} na fila)"},
     { key: "#invasion_quick_battle_head", text:"Onda #{id} ({i}/{n})"},
     { key: "#invasion_quick_battle_none", text:"Sem batalha pendente"},
     { key: "#TR_HOTKEY_TITLE", text:"Configurações de teclas de atalho"},
     { key: "#TR_HOTKEY_LABEL", text:"Teclas de atalho"},
     { key: "#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Alternativa"},
     { key: "#TR_HOTKEY_HEADER_ARROWS", text:"Teclas de seta"},
     { key: "#TR_HOTKEY_HEADER_GLOBAL", text:"Atalhos gerais"},
     { key: "#TR_HOTKEY_HEADER_CITY", text:"Atalhos da cidade"},
     { key: "#TR_HOTKEY_HEADER_ADVISORS", text:"Conselheiros"},
     { key: "#TR_HOTKEY_HEADER_OVERLAYS", text:"Mapa específicos"},
     { key: "#TR_HOTKEY_HEADER_BOOKMARKS", text:"Pontos de referência"},
     { key: "#TR_HOTKEY_HEADER_EDITOR", text:"Editor"},
     { key: "#TR_HOTKEY_ARROW_UP", text:"Cima"},
     { key: "#TR_HOTKEY_ARROW_DOWN", text:"Baixo"},
     { key: "#TR_HOTKEY_ARROW_LEFT", text:"Esquerda"},
     { key: "#TR_HOTKEY_ARROW_RIGHT", text:"Direita"},
     { key: "#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Tela Cheia"},
     { key: "#TR_HOTKEY_CENTER_WINDOW", text:"Centralizar"},
     { key: "#TR_HOTKEY_RESIZE_TO_640", text:"Redimensionar para 640x480"},
     { key: "#TR_HOTKEY_RESIZE_TO_800", text:"Redimensionar para 800x600"},
     { key: "#TR_HOTKEY_RESIZE_TO_1024", text:"Redimensionar para 1024x768"},
     { key: "#TR_HOTKEY_SAVE_SCREENSHOT", text:"Capturar tela"},
     { key: "#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Capturar imagem de cidade"},
     { key: "#TR_HOTKEY_LOAD_FILE", text:"Carregar jogo"},
     { key: "#TR_HOTKEY_SAVE_FILE", text:"Salvar jogo"},
     { key: "#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Aumentar velocidade do jogo"},
     { key: "#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Reduzir velocidade do jogo"},
     { key: "#TR_HOTKEY_TOGGLE_PAUSE", text:"Dar pausa"},
     { key: "#TR_HOTKEY_CYCLE_LEGION", text:"Circular por legiões"},
     { key: "#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Girar no sentido anti-horário"},
     { key: "#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Girar no sentido horário"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Trabalho"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Militar"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Imperial"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Índices"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Comércio Exterior"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"População"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Saúde"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Educação"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Entretenimento"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Religião"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Finanças"},
     { key: "#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Conselheiro Chefe"},
     { key: "#TR_HOTKEY_TOGGLE_OVERLAY", text:"Alternar Mapa Atual/Padrão"},
     {key:"#TR_HOTKEY_TOGGLE_FLAT_BUILDINGS", text:"Vista plana de edifícios"},
     { key: "#sidebar_flat_buildings", text: "Vista plana" },
     { key: "#sidebar_flat_buildings_on", text: "Vista plana: LIGADA" },
     { key: "#TR_CONFIG_FLAT_BUILDINGS", text: "Vista plana de edifícios (Shift+F) — achatar edifícios altos para ver as ruas atrás" },
     { key: "#TR_TOOLTIP_FLAT_BUILDINGS", text: "Vista plana de edifícios (Shift+F). Quando ligada: Ctrl+clique direito levanta um edifício." },
     { key: "#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Mapa de Água"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Mapa de Fogo"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Mapa de Avarias"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Mapa de Criminalidade"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Mapa de Problemas"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_MALARIA_RISK", text:"Mapa de risco de malária"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_DISEASE", text:"Mapa de doença"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_HIDE_CLIFFS", text:"Ocultar penhascos"},
     { key: "#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Ir para marcador 1"},
     { key: "#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Ir para marcador 2"},
     { key: "#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Ir para marcador 3"},
     { key: "#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Ir para marcador 4"},
     { key: "#TR_HOTKEY_SET_BOOKMARK_1", text:"Definir marcador 1"},
     { key: "#TR_HOTKEY_SET_BOOKMARK_2", text:"Definir marcador 2"},
     { key: "#TR_HOTKEY_SET_BOOKMARK_3", text:"Definir marcador 3"},
     { key: "#TR_HOTKEY_SET_BOOKMARK_4", text:"Definir marcador 4"},
     { key: "#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Mostrar informações de batalha"},
     { key: "#TR_HOTKEY_EDIT_TITLE", text:"Nova tecla de atalho"}
     { key: "#mansion_protected_by_police", text:"Protegido pela polícia"}
     { key: "#mansion_not_protected_theft", text:"Sem proteção — ladrões podem roubar as poupanças"}

     { key: "#overlay_menu_normal", text: "Normal" }
     { key: "#overlay_menu_risks", text: "Riscos" }
     { key: "#overlay_menu_water", text: "Água" }
     { key: "#overlay_menu_entertainment", text: "Entretenimento" }
     { key: "#overlay_menu_religion", text: "Religião" }
     { key: "#overlay_menu_education", text: "Educação" }
     { key: "#overlay_menu_health", text: "Saúde" }
     { key: "#overlay_menu_administration", text: "Administração" }
     { key: "#overlay_menu_food", text: "Comida" }
     { key: "#overlay_menu_other", text: "Outro" }

     { key: "#overlay_fire", text: "Fogo" }
     { key: "#overlay_damage", text: "Danos" }
     { key: "#overlay_architect_reach", text: "Alcance do arquiteto" }
     { key: "#overlay_architect_reach_hint", text: "Clique em um posto de arquiteto" }
     { key: "#overlay_architect_reach_tile", text: "Na área de patrulha" }
     { key: "#overlay_crime", text: "Crime" }
     { key: "#overlay_entertainment", text: "Entretenimento" }
     { key: "#overlay_booth", text: "Malabarista" }
     { key: "#overlay_bandstand", text: "Músico" }
     { key: "#overlay_pavilion", text: "Dançarino" }
     { key: "#overlay_senet_house", text: "Jogadores de senet" }
     { key: "#overlay_education", text: "Educação" }
     { key: "#overlay_scribal_school", text: "Escolas de escribas" }
     { key: "#overlay_library", text: "Biblioteca" }
     { key: "#overlay_academy", text: "Academia" }
     { key: "#overlay_apothecary", text: "Boticário" }
     { key: "#overlay_dentist", text: "Dentista" }
     { key: "#overlay_physician", text: "Médico" }
     { key: "#overlay_mortuary", text: "Mortuário" }
     { key: "#overlay_tax_income", text: "Renda fiscal" }
     { key: "#overlay_bazaar_access", text: "Acesso ao bazar" }
     { key: "#overlay_desirability", text: "Desejabilidade" }
     { key: "#overlay_fertility", text: "Fertilidade" }
     { key: "#overlay_magistrate", text: "Magistrado" }
     { key: "#overlay_food_stocks", text: "Estoques de comida" }
     { key: "#overlay_labor", text: "Trabalho" }
     { key: "#overlay_labor_access", text: "Acesso ao trabalho" }
     { key: "#overlay_native", text: "Nativo" }
     { key: "#overlay_problems", text: "Problemas" }
     { key: "#overlay_routing", text: "Rotas" }
     { key: "#overlay_malaria_risk", text: "Risco de malária" }
     { key: "#overlay_health", text: "Saúde" }
     { key: "#overlay_criminal", text: "Criminoso" }
     { key: "#overlay_osiris", text: "Osíris" }
     { key: "#overlay_ra", text: "Rá" }
     { key: "#overlay_ptah", text: "Ptah" }
     { key: "#overlay_seth", text: "Seth" }
     { key: "#overlay_bast", text: "Bastet" }
     { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "Desemprego" }
     { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "Avaliação de cultura" }
     { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "Avaliação de prosperidade" }
     { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "Avaliação de monumentos" }
     { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "Avaliação do reino" }
     { key: "#figure_antelope_hunter", text: "Caçador de antílopes" }
     { key: "#figure_antelope_hunter_javelin", text: "Dardo do caçador" }
     { key: "#figure_birds_hunter", text: "Caçador de aves" }
     { key: "#antelope_hunter_hunting", text: "Antílopes não são páreo para nós!" }
     { key: "#antelope_hunter_back", text: "Esta noite haverá bifes para todos." }
     { key: "#antelope_hunter_city_is_good", text: "Esta cidade é boa!" }
     { key: "#hunter_ostrich_investigate", text: "Pegadas na areia... uma avestruz passou há pouco." }
     { key: "#hunter_ostrich_chase", text: "Lá vai ela! As pernas são rápidas, mas minhas flechas são mais." }
     { key: "#hunter_ostrich_hunting", text: "Avestruzes quase desaparecem quando enfiam a cabeça na areia." }
     { key: "#hunter_ostrich_back", text: "Essas sim são coxas ENORMES!" }
     { key: "#hunter_ostrich_reroute_packed", text: "Carga pesada, caminho errado. Acho outro jeito de voltar." }
     { key: "#hunter_ostrich_look_packed", text: "Preciso de um trilho livre até a cabana com esta ave nas costas." }
     { key: "#hunter_ostrich_unloading", text: "Caça fresca para a cabana. Já cheira melhor que cevada." }
     { key: "#hunter_ostrich_disease_risk", text: "Cheira a doença aqui. Mau tempo para caçar." }
     { key: "#hunter_ostrich_no_food_in_city", text: "Celeiros vazios? Então é melhor eu trazer uma ave grande." }
     { key: "#hunter_ostrich_city_have_no_army", text: "Sem fortes? Um ataque de crocodilos e esta cidade vira jantar." }
     { key: "#hunter_ostrich_need_workers", text: "Precisamos de mais mãos. Não encho todas as panelas sozinho." }
     { key: "#hunter_ostrich_gods_are_angry", text: "Os deuses parecem zangados. Até as avestruzes sentem." }
     { key: "#hunter_ostrich_city_is_bad", text: "O faraó não está satisfeito conosco. Isso nunca acaba bem." }
     { key: "#hunter_ostrich_much_unemployment", text: "Muita gente ociosa. Pelo menos a caça ainda alimenta alguém." }
     { key: "#hunter_ostrich_low_entertainment", text: "Há tempos sem festas. Um banquete de avestruz animaria todos." }
     { key: "#hunter_ostrich_city_is_good", text: "Esta cidade é fantástica!" }
     { key: "#hunter_ostrich_city_is_amazing", text: "A melhor cidade para a qual já cacei. Que continue assim!" }
     { key: "#hunt_bird_birds_are_wily", text: "Estas aves são astutas!" }
     { key: "#hunt_bird_birds_ready_for_roasting", text: "Estas aves estão prontas para assar!" }
]