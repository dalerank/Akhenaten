log_info("akhenaten: localization_ru config started")

localization_ru = [
	{ key:"#TR_NO_PATCH_TITLE", text:""}
    { key:"#TR_NO_PATCH_MESSAGE", text:""}
    { key:"#TR_NO_EDITOR_TITLE", text:"Редактор карт не установлен"}
    { key:"#TR_NO_EDITOR_MESSAGE", text:"Файлы редактора карт в вашей версии игры отсутствуют."}
    { key:"#TR_INVALID_LANGUAGE_TITLE", text:"Неправильная языковая директория"}
    { key:"#TR_INVALID_LANGUAGE_MESSAGE", text:"В указанной папке языковые пакеты отсутствуют. Пожалуйста, проверьте записи журнала игры (log)."}
    { key:"#TR_BUTTON_OK", text:"Ок"}
    { key:"#TR_BUTTON_CANCEL", text:"Отмена"}
    { key:"#TR_BUTTON_RESET_DEFAULTS", text:"По умолчанию"}
    { key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"Горячие клавиши"}
    { key:"#TR_CONFIG_TITLE", text:"Настройки Ozzy"}
    { key:"#TR_CONFIG_LANGUAGE_LABEL", text:"Язык:"}
    { key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(по умолчанию)"}
    { key:"#TR_CONFIG_PAGE_LABEL", text:"Страница"}
    { key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"Изменения пользовательского интерфейса"}
    { key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"Изменения игрового процесса"}
    { key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Изменения логики богов"}
    { key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Изменения логики зданий"}
    { key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Изменения логики ресурсов"}
    { key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"Проигрывать вступительные видеоролики"}
    { key:"#TR_CONFIG_SIDEBAR_INFO", text:"Дополнительная информация на панели управления"}
    { key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"Включить плавную прокрутку карты"}
    { key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"Улучшить наглядность очистки земли"}
    { key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"Разрешить строительство каждого храма по очереди"}
    { key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"Отображать область водоснабжения при строительстве зданий водоснабжения"}
    { key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"Отображать размер здания при строительстве с зажатой клавишей мыши"}
    { key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"Исправлять ошибку иммиграции на 'Очень сложной' сложности игры"}
    { key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"Исправлять ошибку '100-летних призраков' населения"}
    { key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"Исправлять запросы Императора и время выживания в польз. миссиях"}
    { key:"#TR_CONFIG_DRAW_WALKER_WAYPOINTS", text:"Отображать маршрут ходоков по правому щелчку на здании"}
    { key:"#TR_CONFIG_ZOOM_STEPPED", text:"Включить функцию зума (возможно замедление)"}
    { key:"#TR_CONFIG_COMPLETE_RATING_COLUMNS", text:"Исправить незавершенные колонны рейтинга"}
    { key:"#TR_CONFIG_GRANDFESTIVAL", text:"Великий фестиваль разрешает дополнительное благословение от божества"}
    { key:"#TR_CONFIG_JEALOUS_GODS", text:"Отключить ревность божеств"}
    { key:"#TR_CONFIG_GLOBAL_LABOUR", text:"Включить глобальный пул работников"}
    { key:"#TR_CONFIG_SCHOOL_WALKERS", text:"Увеличить зону покрытия школ"}
    { key:"#TR_CONFIG_RETIRE_AT_60", text:"Изменить возраст выхода на пенсию с 50 до 60 лет"}
    { key:"#TR_CONFIG_FIXED_WORKERS", text:"Фиксированный размер пула работников в 38% от населения"}
    { key:"#TR_CONFIG_EXTRA_FORTS", text:"Разрешить строительство 4-х дополнительных фортов"}
    { key:"#TR_CONFIG_WOLVES_BLOCK", text:"Запретить строительство около волков"}
    { key:"#TR_CONFIG_DYNAMIC_GRANARIES", text:"Блокировать тупиковые выходы из амбара"}
    { key:"#TR_CONFIG_MORE_STOCKPILE", text:"Дома запасают больше товаров с рынка"}
    { key:"#TR_CONFIG_NO_BUYER_DISTRIBUTION", text:"Закупщицы с рынка не продают товары"}
    { key:"#TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS", text:"Мгновенное разрушение зданий"}
    { key:"#TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD", text:"Тележки в амбар могут покидать дорогу"}
    { key:"#TR_CONFIG_GRANARIES_GET_DOUBLE", text:"Удвоить вместимость тележек распределяющих еду между амбарами"}
    { key:"#TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD", text:"Башенные часовые не нуждаются в дороге"}
    { key:"#TR_CONFIG_FARMS_DELIVER_CLOSE", text:"Фермы и причалы доставляют еду только в близкорасположенные амбары"}
    { key:"#TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES", text:"Не доставлять еду в амбары с включенной доставкой"}
    { key:"#TR_CONFIG_ALL_HOUSES_MERGE", text:"Разрешить слияние всех домов"}
    { key:"#TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE", text:"Торговые пути увеличивают разнообразие вина"}
    { key:"#TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY", text:"Вместо разрушения, разрушающаяся шахта заберет часть денег"}
    { key:"#TR_CONFIG_MULTIPLE_BARRACKS", text:"Разрешить постройку нескольких казарм"}
    { key:"#TR_HOTKEY_TITLE", text:"Настройки горячих клавиш Ozzy"}
    { key:"#TR_HOTKEY_LABEL", text:"Основная"}
    { key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"Альтернативная"}
    { key:"#TR_HOTKEY_HEADER_ARROWS", text:"Кнопки стрелок"}
    { key:"#TR_HOTKEY_HEADER_GLOBAL", text:"Глобальные горячие клавиши"}
    { key:"#TR_HOTKEY_HEADER_CITY", text:"Городские горячие клавиши"}
    { key:"#TR_HOTKEY_HEADER_ADVISORS", text:"Советники"}
    { key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"Слои"}
    { key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"Закладки городской карты"}
    { key:"#TR_HOTKEY_HEADER_EDITOR", text:"Редактор"}
    { key:"#TR_HOTKEY_ARROW_UP", text:"Вверх"}
    { key:"#TR_HOTKEY_ARROW_DOWN", text:"Вниз"}
    { key:"#TR_HOTKEY_ARROW_LEFT", text:"Влево"}
    { key:"#TR_HOTKEY_ARROW_RIGHT", text:"Вправо"}
    { key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"Переключить на полный экран"}
    { key:"#TR_HOTKEY_CENTER_WINDOW", text:"Окно по центру"}
    { key:"#TR_HOTKEY_RESIZE_TO_640", text:"Задать размер окна 640x480"}
    { key:"#TR_HOTKEY_RESIZE_TO_800", text:"Задать размер окна 800x600"}
    { key:"#TR_HOTKEY_RESIZE_TO_1024", text:"Задать размер окна 1024x768"}
    { key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"Сохранить скриншот"}
    { key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"Сохранить скриншот всего города"}
    { key:"#TR_HOTKEY_LOAD_FILE", text:"Загрузить файл"}
    { key:"#TR_HOTKEY_SAVE_FILE", text:"Сохранить файл"}
    { key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"Увеличить скорость игры"}
    { key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"Уменьшить скорость игры"}
    { key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"Пауза"}
    { key:"#TR_HOTKEY_CYCLE_LEGION", text:"Следующий легион"}
    { key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"Повернуть карту влево"}
    { key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"Повернуть карту вправо"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"Советник по труду"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"Военный советник"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"Советник по делам империи"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"Советник по рейтингам"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"Торговый советник"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"Советник по населению"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"Советник по здоровью"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"Советник по образованию"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"Советник по развлечениям"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"Советник по религии"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"Финансовый советник"}
    { key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"Главный советник"}
    { key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"Переключить текущий слой"}
    { key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"Включить слой водоснабжения"}
    { key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"Включить слой риска пожара"}
    { key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"Включить слой риска разрушения"}
    { key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"Включить слой риска преступлений"}
    { key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"Слой проблем"}
    { key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"Перейти к закладке 1"}
    { key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"Перейти к закладке 2"}
    { key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"Перейти к закладке 3"}
    { key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"Перейти к закладке 4"}
    { key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"Назначить закладку 1"}
    { key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"Назначить закладку 2"}
    { key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"Назначить закладку 3"}
    { key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"Назначить закладку 4"}
    { key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"Информация боя"}
    { key:"#TR_HOTKEY_EDIT_TITLE", text:"Нажмите клавишу"}
    { key:"#TR_BUILDING_ROADBLOCK", text:"Дорожный блок"}
    { key:"#TR_BUILDING_ROADBLOCK_DESC", text:"Блокирует проход бесцельно бродящим ходокам"}
	{ key:"#TR_CONFIG_HEADER_LANGUAGES", lang:"en", text: "Язык игры"}

    {key: "#mission2_store_figs", text:"Постройте зернохранилище и заполните его инжиром"}

    {key: "#lacks_access_primitive_water", text: "Этот дом скоро деградирует, так как ему не хватает доступа даже к самому примитивному источнику воды."}

    { key: "#trader_city_not_trades", text: "Наш долгий и опасный путь сюда был напрасным! Этот город не будет торговать." }
    { key: "#trader_buy_for_less_sell_for_more", text: "Покупай дёшево, продавай дорого. Это мой девиз!" }
    { key: "#trader_its_my_life", text: "Торговая жизнь для меня!" }
    { key: "#trader_i_ll_be_a_hero", text: "Я буду героем, когда привезу эти товары обратно на свою родину." }
    { key: "#trader_you_talk_a_fine_bargain", text: "Вы торгуетесь мастерски, мой друг. Я едва отобью свои расходы." }

    { key: "#recruiter_sick_people", text: "Я вижу больных людей повсюду. Может вспыхнуть чума!" }
    { key: "#recruiter_starving", text: "Я голодаю. Я предпочёл бы искать еду, а не работников. " }
    { key: "#recruiter_city_defenses_weak", text: "Городская оборона настолько слаба, что скоро я мог бы заполнять вакансии иностранцами вместо египтян." }
    { key: "#recruiter_without_workers", text: "Без доступных работников моя работа невозможна." }
    { key: "#recruiter_gods_unleash_fury", text: "Я надеюсь, боги не развяжут свою ярость. Нам нужно уделять им больше внимания." }
    { key: "#recruiter_enemies_attack", text: "Враги могут атаковать в любое время. Наша репутация низкая, и никто нас не уважает." }
    { key: "#recruiter_able_people_out_of_work", text: "С таким количеством способных людей без работы моя работа должна быть лёгкой." }
    { key: "#recruiter_boring", text: "Здесь скучно. Я бы хотел нанять больше артистов." }
    { key: "#recruiter_living_here", text: "Я не против жить здесь. Всё могло быть, конечно, хуже." }
    { key: "#recruiter_best_city", text: "Этот город лучший!" }
    { key: "#recruiter_most_popular", text: "Я самый популярный человек в городе. Многим людям нужна работа." }
    { key: "#recruiter_list_of_job_openings", text: "Мой список вакансий огромен, и я не могу найти ни одного работника, чтобы заполнить должности." }
]