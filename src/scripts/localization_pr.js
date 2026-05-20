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
     { key: "#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Mapa de Água"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Mapa de Fogo"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Mapa de Avarias"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Mapa de Criminalidade"},
     { key: "#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Mapa de Problemas"},
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
     { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "Unemployment" }
     { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "Culture rating" }
     { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "Prosperity rating" }
     { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "Monument rating" }
     { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "Kingdom rating" }
]