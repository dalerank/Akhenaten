log_info("akhenaten: localization_sp config started")

localization_sp = [
     {key:"#TR_NO_PATCH_TITLE", text:""},
     {key:"#TR_NO_PATCH_MESSAGE", text:""},
     {key:"#TR_MISSING_FONTS_TITLE", text:"No se han encontrado archivos de fuente"},
     {key:"#TR_MISSING_FONTS_MESSAGE", text:"" },
     {key:"#TR_NO_EDITOR_TITLE", text:"Editor no instalado"},
     {key:"#TR_NO_EDITOR_MESSAGE", text:"Tu instalación de Caesar 3 no contiene los archivos del editor. "},
     {key:"#TR_INVALID_LANGUAGE_TITLE", text:"Directorio de idioma inválido"},
     {key:"#TR_INVALID_LANGUAGE_MESSAGE", text:"El directorio que has seleccionado no contiene un paquete de idioma válido. Por favor, comprueba el registro de errores."},
     {key:"#TR_BUTTON_OK", text:"Aceptar"},
     {key:"#TR_BUTTON_CANCEL", text:"Cancelar"},
     {key:"#TR_BUTTON_RESET_DEFAULTS", text:"Por defecto"},
     {key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Configurar teclado"},
     {key:"#TR_CONFIG_TITLE", text:"Opciones de configuración de Akhenaten"},
     {key:"#TR_CONFIG_LANGUAGE_LABEL", text:"Idioma:"},
     {key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(por defecto)"},
     {key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"Cambios en la interfaz"},
     {key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Cambios en el juego"},
     {key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"},
     {key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"},
     {key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"},
     {key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Reproducir vídeos al inicio"},
     {key:"#TR_CONFIG_SIDEBAR_INFO", text:"Mostrar información adicional en el panel de control"},
     {key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"Activar desplazamiento suave del mapa"},
     {key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Mejorar el feedback visual al limpiar terreno"},
     {key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Permitir construcción secuencial de templos"},
     {key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Mostrar área cubierta por depósitos, fuentes y pozos al construir"},
     {key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Mostrar medidas de construcción al arrastrar"},
     {key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Corregir bug impidiendo immigración en Muy Difícil"},
     {key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Corregir bug creando fantasmas con 100 años"},
     {key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Corregir cambio de Emperador y supervivencia en misiones del editor"},
     {key:"#TR_HOTKEY_TITLE", text:"Configuración de atajos de teclado de Akhenaten"},
     {key:"#TR_HOTKEY_LABEL", text:"Tecla"},
     {key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Alternativa"},
     {key:"#TR_HOTKEY_HEADER_ARROWS", text:"Teclas de dirección"},
     {key:"#TR_HOTKEY_HEADER_GLOBAL", text:"Teclas de atajo globales"},
     {key:"#TR_HOTKEY_HEADER_CITY", text:"Atajos en la ciudad"},
     {key:"#TR_HOTKEY_HEADER_ADVISORS", text:"Asesores"},
     {key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"Capas"},
     {key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"Atajos de mapa"},
     {key:"#TR_HOTKEY_HEADER_EDITOR", text:"Editor"},
     {key:"#TR_HOTKEY_ARROW_UP", text:"Arriba"},
     {key:"#TR_HOTKEY_ARROW_DOWN", text:"Abajo"},
     {key:"#TR_HOTKEY_ARROW_LEFT", text:"Izquierda"},
     {key:"#TR_HOTKEY_ARROW_RIGHT", text:"Derecha"},
     {key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Activar pantalla completa"},
     {key:"#TR_HOTKEY_CENTER_WINDOW", text:"Centrar pantalla"},
     {key:"#TR_HOTKEY_RESIZE_TO_640", text:"Redimensionar a 640x480"},
     {key:"#TR_HOTKEY_RESIZE_TO_800", text:"Redimensionar a 800x600"},
     {key:"#TR_HOTKEY_RESIZE_TO_1024", text:"Redimensionar a 1024x768"},
     {key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"Capturar pantalla"},
     {key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Capturar ciudad completa"},
     {key:"#TR_HOTKEY_LOAD_FILE", text:"Cargar partida"},
     {key:"#TR_HOTKEY_SAVE_FILE", text:"Guardar partida"},
     {key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Subir velocidad de juego"},
     {key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Bajar velocidad de juego"},
     {key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"Activar pausa"},
     {key:"#TR_HOTKEY_CYCLE_LEGION", text:"Circular entre legiones"},
     {key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Rotar mapa a la izquierda"},
     {key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Rotar mapa a la derecha"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Asesor laboral"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Asesor militar"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Asesor imperial"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Asesor de puntuación"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Asesor de comercio"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"Asesor de población"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Asesor de sanidad"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Asesor de educación"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Asesor de entretenimiento"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Asesor de religión"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Asesor de finanzas"},
     {key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Asesor jefe"},
     {key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"Capa actual"},
     {key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Capa de agua"},
     {key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Capa de riesgo de fuego"},
     {key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Capa de riesgo de daño"},
     {key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Capa de criminalidad"},
     {key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Capa de problemas"},
     {key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Ir a atajo de mapa 1"},
     {key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Ir a atajo de mapa 2"},
     {key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Ir a atajo de mapa 3"},
     {key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Ir a atajo de mapa 4"},
     {key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"Definir atajo de mapa 1"},
     {key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"Definir atajo de mapa 2"},
     {key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"Definir atajo de mapa 3"},
     {key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"Definir atajo de mapa 4"},
     {key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Activar información de batalla"},
     {key:"#TR_HOTKEY_EDIT_TITLE", text:"Presiona nueva tecla"}
     {key:"#mansion_protected_by_police", text:"Protegido por la policía"}
     {key:"#mansion_not_protected_theft", text:"Sin protección: los ladrones pueden robar los ahorros"}

     { key: "#overlay_menu_normal", text: "Normal" }
     { key: "#overlay_menu_risks", text: "Riesgos" }
     { key: "#overlay_menu_water", text: "Agua" }
     { key: "#overlay_menu_entertainment", text: "Entretenimiento" }
     { key: "#overlay_menu_religion", text: "Religión" }
     { key: "#overlay_menu_education", text: "Educación" }
     { key: "#overlay_menu_health", text: "Salud" }
     { key: "#overlay_menu_administration", text: "Administración" }
     { key: "#overlay_menu_food", text: "Comida" }
     { key: "#overlay_menu_other", text: "Otro" }

     { key: "#overlay_fire", text: "Fuego" }
     { key: "#overlay_damage", text: "Daños" }
     { key: "#overlay_crime", text: "Crimen" }
     { key: "#overlay_entertainment", text: "Entretenimiento" }
     { key: "#overlay_booth", text: "Malabarista" }
     { key: "#overlay_bandstand", text: "Músico" }
     { key: "#overlay_pavilion", text: "Bailarín" }
     { key: "#overlay_senet_house", text: "Jugadores de senet" }
     { key: "#overlay_education", text: "Educación" }
     { key: "#overlay_scribal_school", text: "Escuelas de escribas" }
     { key: "#overlay_library", text: "Biblioteca" }
     { key: "#overlay_academy", text: "Academia" }
     { key: "#overlay_apothecary", text: "Boticario" }
     { key: "#overlay_dentist", text: "Dentista" }
     { key: "#overlay_physician", text: "Médico" }
     { key: "#overlay_mortuary", text: "Mortuorio" }
     { key: "#overlay_tax_income", text: "Ingresos fiscales" }
     { key: "#overlay_bazaar_access", text: "Acceso al bazar" }
     { key: "#overlay_desirability", text: "Atractivo" }
     { key: "#overlay_fertility", text: "Fertilidad" }
     { key: "#overlay_magistrate", text: "Magistrado" }
     { key: "#overlay_food_stocks", text: "Reservas de comida" }
     { key: "#overlay_labor", text: "Trabajo" }
     { key: "#overlay_labor_access", text: "Acceso laboral" }
     { key: "#overlay_native", text: "Nativo" }
     { key: "#overlay_problems", text: "Problemas" }
     { key: "#overlay_routing", text: "Rutas" }
     { key: "#overlay_malaria_risk", text: "Riesgo de malaria" }
     { key: "#overlay_health", text: "Salud" }
     { key: "#overlay_criminal", text: "Criminal" }
     { key: "#overlay_osiris", text: "Osiris" }
     { key: "#overlay_ra", text: "Ra" }
     { key: "#overlay_ptah", text: "Ptah" }
     { key: "#overlay_seth", text: "Seth" }
     { key: "#overlay_bast", text: "Bastet" }
     { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "Unemployment" }
     { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "Culture rating" }
     { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "Prosperity rating" }
     { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "Monument rating" }
     { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "Kingdom rating" }
]