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

    { key: "#immigrant_im_new_here", text: "Я здесь новенький. Интересно, что город предложит такому человеку, как я." }
    { key: "#immigrant_heard_there_is_a_job_here", text: "Я слышал, здесь есть работа для любого, кто её хочет." }
    { key: "#immigrant_city_has_plenty_of_food", text: "Люди говорят, что в этом городе много еды на всех." }

    { key: "#emigrant_no_job_in_city", text: "Я не могу найти здесь работу. Я буду искать в другом месте." }
    { key: "#emigrant_no_food_in_city", text: "Здесь недостаточно еды, чтобы мне есть. Я уезжаю из этой пустыни!" }
    { key: "#emigrant_tax_too_high", text: "Налоги здесь слишком высоки. Я удивлён, что меня не обложили налогом за отъезд." }
    { key: "#emigrant_salary_too_low", text: "Я не могу жить на то, что мне здесь платят." }
    { key: "#emigrant_no_house_for_me", text: "Дома, которые я видел, переполнены людьми. Я не могу остаться здесь без места для жизни." }

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

    { key: "#barge_have_no_place_for_dock", text: "Интересно, есть ли в этом городе какие-нибудь достопримечательности, которые я мог бы увидеть, пока они разгружают мой корабль." }
    { key: "#barge_docked_wait_for_dockpushers", text: "Мы ждём, когда груз доставят на наш корабль." }
    { key: "#barge_city_not_trades", text: "Не знаю, зачем мы приехали. Этот город никогда не торгует, а береговой отпуск скучный." }
    { key: "#barge_i_like_to_trage", text: "Я люблю искусство сделки! Не могу дождаться, чтобы обменять свои припасы." }
    { key: "#barge_amazing_trades", text: "Какое обильное путешествие!" }

    { key: "#dancer_i_like_festivals", text: "Многие люди заболели в городе. Надеюсь, я ничего не подхвачу!" }
    { key: "#dancer_desease_can_start_at_any_moment", text: "Я не могу хорошо прыгать и танцевать без достаточного количества еды!" }
    { key: "#dancer_no_food_in_city", text: "Захватчикам было бы нетрудно захватить наш город. Ничто его не защищает." }
    { key: "#dancer_city_not_safety_workers_leaving", text: "Ещё один танцевальный партнёр потерян из-за нехватки работников! Я ненавижу танцевать одна." }
    { key: "#dancer_need_workers", text: "Мы должны сделать больше, чтобы умилостивить богов - и быстро!" }
    { key: "#dancer_gods_are_angry", text: "Репутация этого города хуже, чем у жонглёра! Надеюсь, мы не будем атакованы." }
    { key: "#dancer_city_is_bad", text: "Если бы я не была так легка на ногах, я бы спотыкалась обо всех этих безработных людей!" }
    { key: "#dancer_much_unemployments", text: "(Зевок) Мне нужно развлечься!" }
    { key: "#dancer_salary_too_low", text: "Этот город примерно так же хорош, как любой другой город, полагаю." }
    { key: "#dancer_city_is_good", text: "Этот город фантастический!" }
    { key: "#dancer_city_is_amazing", text: "Эти фестивальные толпы такие восторженные, что заставляют меня прыгать выше." }

    { key: "#homeless_i_was_kicked_out_of_my_home", text: "Меня выгнали из моего дома, и это не моя вина." }
    { key: "#homeless_i_cant_find_a_place_to_live", text: "Я не могу найти место для жизни!" }

    { key: "#marketboy_these_baskets_are_too_heavy", text: "Эти корзины слишком тяжелы для такого маленького ребёнка, как я!" }
    { key: "#marketboy_bossy_lady_makes_me_carry_goods", text: "Эта властная дама заставляет меня носить товары весь день!" }
    { key: "#marketboy_one_day_ill_run_the_bazaar", text: "Может быть, я сейчас просто ношу корзины, но однажды я буду управлять базаром." }

    { key: "#engineer_extreme_damage_level", text: "Многие люди в гораздо худшем состоянии, чем здания. Надеюсь, всё не станет хуже." }
    { key: "#engineer_starvation_might_not_affect_strength", text: "Голодание может не влиять на прочность этих зданий, но оно точно влияет на мою!" }
    { key: "#engineer_how_to_defend_ourselves", text: "Как мы должны защищаться? Оборона города смехотворна." }
    { key: "#engineer_why_does_it_matter_if_buildings_collapse", text: "Какая разница, если эти здания рухнут? В них всё равно нет работников." }
    { key: "#engineer_if_gods_are_angry", text: "Если боги сердиты, даже лучший архитектор не сможет исправить ущерб, который они причиняют." }
    { key: "#engineer_our_city_reputation_is_low", text: "Репутация нашего города настолько низка, что боюсь, наши враги нападут." }
    { key: "#engineer_by_estimation_a_lot_of_people_are_out_of_work", text: "По моим оценкам, много людей без работы." }
    { key: "#engineer_ho_hum_even_architects_like_fun", text: "Хо хум. Даже архитекторам нравится немного веселья время от времени." }
    { key: "#engineer_life_here_could_be_worse", text: "Жизнь здесь могла быть намного хуже." }
    { key: "#engineer_this_city_has_everything", text: "В этом городе есть всё, чего может желать сердце архитектора!" }
    { key: "#engineer_there_are_so_many_places_in_poor_condition", text: "Здесь так много мест в плохом состоянии, что я едва успеваю." }
    { key: "#engineer_i_hope_i_m_credited_for_great_condition", text: "Надеюсь, меня отметят за отличное состояние этого города." }

    { key: "#fireman_desease_can_start_at_any_moment", text: "Надеюсь, чума не вспыхнет. Чума может распространяться как лесной пожар." }
    { key: "#fireman_no_food_in_city", text: "Даже когда пожары горят, всё, о чём я могу думать, это насколько я голоден." }
    { key: "#fireman_city_not_safety_workers_leaving", text: "Если наши враги вторгнутся, весь город может сгореть дотла." }
    { key: "#fireman_need_workers", text: "Боюсь, что некоторые из этих полупустых зданий могут загореться. Хотел бы я, чтобы было больше работников." }
    { key: "#fireman_hight_fire_level", text: "Огненный гнев богов обрушится на нас, если мы не проявим больше уважения." }
    { key: "#fireman_gods_are_angry", text: "Я и не мечтал бы позволить своей репутации упасть так низко. Плохая репутация нашего города приглашает к нападению." }
    { key: "#fireman_need_more_workers", text: "У меня было больше людей-добровольцев в пожарную службу. Этим людям нужна работа." }
    { key: "#fireman_low_entertainment", text: "Пожаротушение - тяжёлая работа, и я бы с удовольствием остыл с хорошим шоу. Здесь этого недостаточно." }
    { key: "#fireman_gods_are_pleasures", text: "Я доволен этим городом." }
    { key: "#fireman_city_is_amazing", text: "Этот город классный." }
    { key: "#fireman_fighting_fire", text: "Я не могу говорить сейчас. Я занят тушением этого пожара." }
    { key: "#fireman_going_to_fire", text: "Этот пожар может сжечь весь город дотла, если я не буду действовать быстро!" }
    { key: "#fireman_fighting_fire_also", text: "Ух, это горячо!" }   

    { key: "#malaria_problem", text: "(Не используется)" }
    { key: "#malaria_not_a_problem", text: "Малярия, похоже, здесь не проблема." }
    { key: "#malaria_outbreak_could_strike", text: "Вспышка малярии может произойти, если ничего не сделать." }    

    { key: "#policeman_desease_can_start_at_any_moment", text: "С таким количеством слабых и больных людей я боюсь за будущее." }
    { key: "#policeman_no_food_in_city", text: "Я так долго не ел, что даже я подумываю о краже еды!" }
    { key: "#policeman_city_not_safety", text: "Если захватчики придут, похоже, мне придётся защищать город." }
    { key: "#policeman_need_workers", text: "Если бы я не наслаждался опасностью полицейской работы, я бы быстро взял одну из многих доступных работ." }
    { key: "#policeman_gods_are_angry", text: "Если бы я управлял делами, я бы уделял больше внимания богам." }
    { key: "#policeman_no_army", text: "Я слышал, наш город - лёгкая цель для захватчиков. У нас плохая репутация." }
    { key: "#policeman_much_unemployments", text: "Мне не нравится видеть столько безработных бездельников. Я не могу ходить по своему участку, не споткнувшись о них!" }
    { key: "#policeman_low_entertainment", text: "Этот город скучен. Я не могу найти хороших шоу для просмотра." }
    { key: "#policeman_city_is_good", text: "Этот город не идеален, но какой город идеален?" }
    { key: "#policeman_very_low_crime_level", text: "Если бы только базар торговал пончиками, этот город был бы идеальным." }
    { key: "#policeman_low_crime_level", text: "Здесь все дружелюбны. Никто не сообщает о преступлениях." }
    { key: "#policeman_usual_crime_level", text: "Несколько преступлений здесь, несколько преступлений там, но ничего необычного." }
    { key: "#policeman_need_more_workers", text: "Даже я не люблю ходить в этой части города!" }
    { key: "#policeman_iam_too_busy_that_talk", text: "Я действительно слишком занят, чтобы говорить сейчас - спросите меня позже." }
    { key: "#policeman_i_hope_my_work_is_need", text: "Я сделаю свою часть, чтобы убедиться, что этот город безопасен!" }
    { key: "#policeman_no_army_2", text: "Борьба с захватчиками не входила в мои должностные обязанности!" }
    { key: "#policeman_enemies_are_coming_2", text: "Эти негодяи не захватят город на моей смене!" }
    { key: "#policeman_enemies_are_coming", text: "Враг может вскоре победить, если я не получу помощи! " }

    { key: "#hunter_ostrich_hunting", text: "Страусы почти невидимы, когда прячут голову в песок. // охотник на страусов" }
    { key: "#hunter_ostrich_back", text: "Ну и ну, это БОЛЬШИЕ ножки!" }
    { key: "#hunter_ostrich_city_is_good", text: "Этот город классный." }
]