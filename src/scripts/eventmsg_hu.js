log_info("akhenaten: eventmsg hungarian started")

eventmsg_hu = [
	{ key:PHRASE_egyptian_city_attacked_title_P, text: "Egyiptomi város támadás alatt" }
	{ key:PHRASE_egyptian_city_attacked_title_C, text: "Egyiptomi város támadás alatt" }
	{ key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] hitetlenek támadták meg városunkat. A mindenható fáraó megparancsolja, hogy küldj sereget [city_name] egyiptomi város megsegítésére. Csapataidnak [travel_time] hónapon belül útnak kell indulniuk." }
	{ key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] [city_name] egyiptomi város támadás alatt áll, és segítségre szorul. Küldj sereget [travel_time] hónapon belül." }
	{ key:PHRASE_egyptian_city_attacked_first_reminder_P, text: "[greeting] [player_name], a fenséges fáraó seregei még mindig [city_name] mellett harcolnak a támadókkal. Küldj erősítést a következő hat hónapon belül, különben magadra vonod a fáraó haragját." }
	{ key:PHRASE_egyptian_city_attacked_first_reminder_C, text: "[greeting] [player_name], megfeledkeztél [city_name] városáról? Küldj sereget a következő hat hónapon belül, különben súlyos következményekre számíthatsz." }
	{ key:PHRASE_egyptian_city_attacked_last_reminder_P, text: "[greeting] [player_name], a fáraó egyre türelmetlenebbül várja csapataidat. Küldj sereget [city_name] megsegítésére mielőbb, különben már túl késő lesz." }
	{ key:PHRASE_egyptian_city_attacked_last_reminder_C, text: "[greeting] [player_name], [city_name] hamarosan vereséget szenvedhet ellenségeitől. Küldj sereget azonnal, ha segíteni akarsz a városnak a szükség órájában." }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "mivel csapataid legyőzték a fáraó ellenségeit [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "csapataid legyőzték a fáraó ellenségeit [city_name] mellett. Egyébként," }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "bár csapataid legyőzték a fáraó ellenségeit [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "mivel csapataid sikeresen legyőzték az ellenséget [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "csapataid sikeresen legyőzték az ellenséget [city_name] mellett. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "bár csapataid sikeresen legyőzték az ellenséget [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "mivel túl sokáig késlekedtél csapataid elküldésével, hogy segítsék a fáraó seregét az ellenség elleni harcban [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "a fáraó serege vereséget szenvedett [city_name] mellett, mert csapataid túl későn érkeztek. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "csapataid túl későn érkeztek ahhoz, hogy segítsék a fáraó seregét az ellenség elleni harcban [city_name] mellett, de erőfeszítésedet értékelték. Ennek eredményeként" }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "mivel túl sokáig vártál csapataid elküldésével [city_name] védelmére," }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "csapataid nem érkeztek meg időben, hogy segítsenek megvédeni [city_name] városát. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "csapataid túl későn érkeztek ahhoz, hogy segítsenek [city_name] városának, de mivel megtetted a szükséges erőfeszítést, és hajlandó voltál feláldozni saját katonáidat," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "mivel megtagadtad a fáraótól a csapatokat, amelyekre szüksége volt az ellenség elleni harchoz [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "a fáraó tudomására jutott, hogy megtagadtad a csapatok elküldését, amelyekre szüksége volt az ellenség elleni harchoz [city_name] mellett. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "bár megtagadtad a fáraótól a csapatokat, amelyekre szüksége volt az ellenség elleni harchoz [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "mivel megtagadtad a kért csapatok elküldését, hogy legyőzzék a fosztogatókat [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: "[city_name] városa kétségbeesetten fogadta, hogy megtagadtad a kért csapatok elküldését ellenségeik legyőzésére. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "bár megtagadtad a kért csapatok elküldését, hogy legyőzzék a fosztogatókat [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "mivel a fáraónak [city_name] mellé küldött csapataid túl gyengék voltak az ellenség legyőzéséhez," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "a fáraó megsegítésére küldött gyenge csapataid vereséget szenvedtek [city_name] mellett. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "annak ellenére, hogy csapataid túl gyengék voltak ahhoz, hogy segítsék a fáraót [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "mivel a [city_name] védelmére küldött csapataid nem voltak elég erősek a támadók legyőzéséhez," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "gyenge sereged vereséget szenvedett [city_name] mellett. Emellett," }
	{ key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "bár csapataid nem arattak győzelmet [city_name] mellett," }
	{ key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "hogy még több földet hódítsanak meg," }
	{ key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "megpróbáltatásaidnak még mindig nincs vége, mert" }
	{ key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: "" }
	{ key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "egy régi viszály folytatásaként," }
	{ key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "megpróbáltatásaidnak még mindig nincs vége, mert" }
	{ key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: "" }
	{ key: PHRASE_distant_battle_title_P, text: "Távoli csata" }
	{ key: PHRASE_distant_battle_title_C, text: "Távoli csata" }
	{ key: PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] az egyiptomi sereg heves csatát vív. A hatalmas fáraó megparancsolja, hogy küldj csapatokat a távoli [city_name] városába, hogy csatlakozzanak a harchoz. Indítsd útnak seregedet [travel_time] hónapon belül." }
	{ key: PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] az egyiptomi sereg a távoli [city_name] városánál harcol, és erősítésre van szüksége. Küldj csapatokat segítségükre [travel_time] hónapon belül." }
	{ key: PHRASE_distant_battle_first_reminder_P, text: "[greeting] [player_name], a véres csata tovább dúl [city_name] mellett, és a fáraónak még mindig szüksége van csapataidra. Küldd el őket a következő hat hónapon belül, hogy időben odaérjenek. Ennek elmulasztása súlyos következményekkel járhat." }
	{ key: PHRASE_distant_battle_first_reminder_C, text: "[greeting] [player_name], a [city_name] városáért vívott csata tovább tombol. Küldj csapatokat a következő hat hónapon belül, hogy időben odaérjenek. Ez lehet a lehetőséged, hogy osztozz egy dicsőséges győzelemben." }
	{ key: PHRASE_distant_battle_last_reminder_P, text: "[greeting] [player_name], az egyiptomi sereg még mindig [city_name] mellett harcol, és a nemes fáraó azt követeli, hogy haladéktalanul küldj erősítést. Ne vond magadra a fáraó haragját, amikor a háború hevében áll." }
	{ key: PHRASE_distant_battle_last_reminder_C, text: "[greeting] [player_name], a [city_name] városáért vívott csata tovább folytatódik. Ha nagyon hamar segítségükre küldöd csapataidat, Egyiptom még dicsőséges győzelmet arathat." }
	{ key: PHRASE_distant_battle_comply_reason_P_A, text: "mivel a fáraó [city_name] melletti győzelme csapataidon múlott," }
	{ key: PHRASE_distant_battle_comply_reason_P_B, text: "csapataid hozzásegítették a fáraót a [city_name] melletti győzelemhez. Ja, és még valami," }
	{ key: PHRASE_distant_battle_comply_reason_P_C, text: "bár csapataid hozzásegítették a fáraót a [city_name] melletti győzelemhez," }
	{ key: PHRASE_distant_battle_comply_reason_C_A, text: "mivel csapataid döntő szerepet játszottak a [city_name] melletti győzelem kivívásában," }
	{ key: PHRASE_distant_battle_comply_reason_C_B, text: "csapataid nélkülözhetetlennek bizonyultak a [city_name] melletti győzelem kivívásában. Emellett," }
	{ key: PHRASE_distant_battle_comply_reason_C_C, text: "bár csapataid nélkülözhetetlennek bizonyultak a [city_name] melletti győzelem kivívásában," }
	{ key: PHRASE_distant_battle_too_late_reason_P_A, text: "mivel csapataid nem érkeztek meg időben, hogy segítsék a fáraót [city_name] mellett," }
	{ key: PHRASE_distant_battle_too_late_reason_P_B, text: "csapataid nem érkeztek meg időben, hogy segítsék a fáraót [city_name] mellett. Emellett," }
	{ key: PHRASE_distant_battle_too_late_reason_P_C, text: "bár csapataid túl későn érkeztek, hogy segítsék a fáraót [city_name] mellett, a királyságért hozott áldozatvállalási készségedet nagyra értékelik. Ennek eredményeként," }
	{ key: PHRASE_distant_battle_too_late_reason_C_A, text: "mivel csapataid túl későn érkeztek, hogy részt vegyenek a [city_name] melletti csatában," }
	{ key: PHRASE_distant_battle_too_late_reason_C_B, text: "csapataid túl későn érkeztek, hogy részt vegyenek a [city_name] melletti csatában. Ezenfelül," }
	{ key: PHRASE_distant_battle_too_late_reason_C_C, text: "bár csapataid túl későn érkeztek, hogy részt vegyenek a [city_name] melletti csatában, a királyságért hozott áldozatvállalási készségedet nagyra értékelik. Ennek eredményeként," }
	{ key: PHRASE_distant_battle_refuse_reason_P_A, text: "mivel nyíltan megtagadtad a fáraó kérését, hogy csapatokat küldj serege megsegítésére [city_name] mellett," }
	{ key: PHRASE_distant_battle_refuse_reason_P_B, text: "nyíltan megtagadtad a fáraó kérését, hogy csapatokat küldj serege megsegítésére [city_name] mellett. Ez nem volt bölcs döntés, de mindenesetre," }
	{ key: PHRASE_distant_battle_refuse_reason_P_C, text: "bár megtagadtad a fáraó kérését, hogy csapatokat küldj serege megsegítésére [city_name] mellett," }
	{ key: PHRASE_distant_battle_refuse_reason_C_A, text: "mivel megtagadtad a szükséges csapatok elküldését a [city_name] melletti csatába," }
	{ key: PHRASE_distant_battle_refuse_reason_C_B, text: "megtagadtad a szükséges csapatok elküldését a [city_name] melletti csatába, ami szerencsétlenül érintette őket. Egyébként," }
	{ key: PHRASE_distant_battle_refuse_reason_C_C, text: "bár megtagadtad a szükséges csapatok elküldését a [city_name] melletti csatába," }
	{ key: PHRASE_distant_battle_lost_battle_reason_P_A, text: "mivel a [city_name] mellé küldött csapataid túl gyengék voltak ahhoz, hogy megküzdjenek a fáraó ellenségével," }
	{ key: PHRASE_distant_battle_lost_battle_reason_P_B, text: "a [city_name] mellé küldött csapataid vereséget szenvedtek a fáraó ellenségétől. Emellett," }
	{ key: PHRASE_distant_battle_lost_battle_reason_P_C, text: "bár a [city_name] mellé küldött csapataid vereséget szenvedtek a fáraó ellenségétől," }
	{ key: PHRASE_distant_battle_lost_battle_reason_C_A, text: "mivel a [city_name] mellé küldött csapataid nem voltak elég erősek ahhoz, hogy legyőzzék az ellenséget," }
	{ key: PHRASE_distant_battle_lost_battle_reason_C_B, text: "a [city_name] mellé küldött csapataid nem voltak elég erősek ahhoz, hogy legyőzzék ellenségünket. Arra is ügyelj, hogy" }
	{ key: PHRASE_distant_battle_lost_battle_reason_C_C, text: "bár a [city_name] mellé küldött csapataid nem tudták legyőzni az ellenséget," }
	{ key: PHRASE_distant_battle_no_reason_P_A, text: "halld meg a csatakiáltást, mert" }
	{ key: PHRASE_distant_battle_no_reason_P_B, text: "megpróbáltatásaink folytatódnak" }
	{ key: PHRASE_distant_battle_no_reason_P_C, text: "" }
	{ key: PHRASE_distant_battle_no_reason_C_A, text: "készítsd fel katonáidat, mert" }
	{ key: PHRASE_distant_battle_no_reason_C_B, text: "a baj még nem ért véget, mert" }
	{ key: PHRASE_distant_battle_no_reason_C_C, text: "" }
	{ key:PHRASE_general_request_title_P, text:"A fáraó árut kér" }
	{ key:PHRASE_general_request_title_C, text:"Egy város árut kér" }
	{ key:PHRASE_general_request_initial_announcement_P,text:"[greeting] [player_name], [reason_phrase] a páratlan fáraó azt kívánja, hogy [time_allotted] hónapon belül küldj [amount] [item] árut [city_name] városába. A kérés teljesítésével kivívhatod a fáraó elismerését." }
	{ key:PHRASE_general_request_initial_announcement_C,text:"[greeting] [player_name], [reason_phrase] [city_name] városa azt kéri, hogy [time_allotted] hónapon belül küldj [amount] [item] árut. [city_name] megsegítése később hasznunkra válhat." }
	{ key:PHRASE_general_request_reminder_P,text:"[greeting] [player_name], a fáraó értetlenül áll az előtt, hogy [city_name] még nem kapta meg a kért [amount] [item] árut. Már csak 6 hónapod maradt a fáraó kérésének teljesítésére." }
	{ key:PHRASE_general_request_reminder_C,text:"[greeting] [player_name], [city_name] türelmetlenül várja a [amount] [item] áru érkezését. Már csak 6 hónapod maradt a kérés teljesítésére." }
	{ key:PHRASE_general_request_overdue_P,text:"[greeting] [player_name], fel akarod ingerelni a fáraót? Nem küldted el időben a [amount] [item] árut [city_name] városába. Még egy megkésett szállítmány is némileg enyhítheti a fáraó haragját." }
	{ key:PHRASE_general_request_overdue_C,text:"[greeting] [player_name], lejárt a határidő, és még mindig nem küldted el a kért [amount] [item] árut [city_name] városának. Még egy megkésett szállítmány is némileg enyhítheti elégedetlenségüket." }
	{ key:PHRASE_general_request_warning_P,text:"[greeting] [player_name], már csak hat hónapod maradt, hogy teljesítsd a fáraó kérését, és elküldd [amount] [item] árut [city_name] városába. Saját felelősségedre tagadd meg a kérését." }
	{ key:PHRASE_general_request_warning_C,text:"[greeting] [player_name], küldj [amount] [item] árut [city_name] városába hat hónapon belül, különben könnyen ellenséget csinálhatsz a szomszédodból." }
	{ key:PHRASE_general_request_comply_reason_P_A,text:"mivel teljesítetted a fáraó kérését, és elküldted a [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_general_request_comply_reason_P_B, text:"teljesítetted a fáraó kérését, és elküldted a [amount] [item] árut [city_name] városába. Egyébként," }
	{ key:PHRASE_general_request_comply_reason_P_C, text:"teljesítetted ugyan a fáraó kérését, és elküldted a [amount] [item] árut [city_name] városába, azonban," }
	{ key:PHRASE_general_request_comply_reason_C_A, text:"mivel elküldted a kért [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_general_request_comply_reason_C_B, text:"[city_name] megkapta a kért [amount] [item] árut. Tudnod kell azt is, hogy" }
	{ key:PHRASE_general_request_comply_reason_C_C, text:"annak ellenére, hogy elküldted a kért [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_general_request_too_late_reason_P_A, text:"mivel késlekedtél a fáraó [amount] [item] árura vonatkozó kérésének teljesítésével," }
	{ key:PHRASE_general_request_too_late_reason_P_B, text:"a fáraó [amount] [item] árura vonatkozó kérése nem teljesült, mert túl későn cselekedtél. Emellett," }
	{ key:PHRASE_general_request_too_late_reason_P_C, text:"késlekedtél a fáraó [amount] [item] árura vonatkozó kérésének teljesítésével, de erőfeszítésedet ennek ellenére is értékelték. Ennek eredményeként," }
	{ key:PHRASE_general_request_too_late_reason_C_A, text:"mivel késve teljesítetted [city_name] [amount] [item] árura vonatkozó kérését," }
	{ key:PHRASE_general_request_too_late_reason_C_B, text:"késve szállítottad el a [amount] [item] árut [city_name] városába. Tudnod kell azt is, hogy" }
	{ key:PHRASE_general_request_too_late_reason_C_C, text:"annak ellenére, hogy késve szállítottad el a [amount] [item] árut [city_name] városába, erőfeszítésedet értékelték. Ennek eredményeként," }
	{ key:PHRASE_general_request_refuse_reason_P_A, text:"mivel figyelmen kívül hagytad a fáraó [amount] [item] árura vonatkozó kérését," }
	{ key:PHRASE_general_request_refuse_reason_P_B, text:"figyelmen kívül hagytad a fáraó [amount] [item] árura vonatkozó kérését, és ezért nem lesz elégedett. Emellett," }
	{ key:PHRASE_general_request_refuse_reason_P_C, text:"annak ellenére, hogy figyelmen kívül hagytad a fáraó [amount] [item] árura vonatkozó kérését," }
	{ key:PHRASE_general_request_refuse_reason_C_A, text:"mivel nem küldted el a kért [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_general_request_refuse_reason_C_B, text:"nem küldted el a kért [amount] [item] árut [city_name] városába, amit rossz néven vettek. Mindeközben," }
	{ key:PHRASE_general_request_refuse_reason_C_C, text:"annak ellenére, hogy nem küldted el a kért [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_general_request_no_reason_P_A, text:"birtokainak készletei feltöltésére," }
	{ key:PHRASE_general_request_no_reason_P_B, text:"úgy tűnik, a fáraó mohóságának nincs határa, mert" }
	{ key:PHRASE_general_request_no_reason_P_C, text:"" }
	{ key:PHRASE_general_request_no_reason_C_A, text:"a polgárok szükségleteinek kielégítésére," }
	{ key:PHRASE_general_request_no_reason_C_B, text:"úgy tűnik, ennek soha nincs vége, mert" }
	{ key:PHRASE_general_request_no_reason_C_C, text:"" }
	{ key: PHRASE_great_festival_title_P, text: "Nagy ünnep [god] tiszteletére" }
	{ key: PHRASE_great_festival_title_C, text: "Nagy ünnep [god] tiszteletére" }
	{ key: PHRASE_great_festival_initial_announcement_P, text:"[greeting] [player_name], [reason_phrase] a fáraó nagy ünnepet rendez [god] tiszteletére [city_name] városában, és ehhez árura van szüksége városodból. [time_allotted] hónapod van elküldeni [amount] [item] árut." }
	{ key: PHRASE_great_festival_initial_announcement_C, text:"[greeting] [player_name], [reason_phrase] [city_name] városa [amount] [item] árut kér egy [god] tiszteletére rendezendő nagy ünnephez. A városnak [time_allotted] hónapon belül szüksége van ezekre az árukra." }
	{ key: PHRASE_great_festival_reminder_P, text:"[greeting] [player_name], már csak hat hónapod maradt, hogy elküldd [amount] [item] árut [city_name] városába a [god] tiszteletére rendezendő nagy ünnepre. A fáraó elégedetlen lesz, ha nem teljesíted a kérését." }
	{ key: PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], rohamosan közeleg a [god] tiszteletére rendezendő nagy ünnep [city_name] városában, de még nem küldted el a kért [amount] [item] árut. Már csak 6 hónapod maradt a szállításra." }
	{ key: PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], elmulasztottad a határidőt, ezért a fáraónak a [god] tiszteletére rendezett nagy ünnepet a te szállítmányod nélkül kellett megtartania. Ennek ellenére küldd el a [amount] [item] árut [city_name] városába, és a haragos fáraó talán még megbocsát." }
	{ key: PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] elégedetlen, mert a [god] tiszteletére rendezett nagy ünnephez máshonnan kellett beszerezniük az árut. Talán visszanyerheted jóindulatukat, ha még most is elküldöd a [amount] [item] árut." }
	{ key: PHRASE_great_festival_warning_P, text: "[greeting] [player_name], már csak 6 hónapod maradt, hogy elküldd a fáraó által a [god] tiszteletére rendezendő nagy ünnephez kért [amount] [item] árut [city_name] városába. Jaj annak, akire lesújt a fáraó izzó haragja!" }
	{ key: PHRASE_great_festival_warning_C, text: "[greeting] [player_name], [city_name] egyre elégedetlenebb veled. Küldd el a [amount] [item] árut a következő 6 hónapon belül, ha fenn akarod tartani a jó kapcsolatot." }
	{ key: PHRASE_great_festival_comply_reason_P_A, text: "mivel időben elküldted a [amount] [item] árut [city_name] városába a [god] tiszteletére rendezett nagy ünnepre, és ezzel tiszteletet adtál a fáraónak és [god] istennek," }
	{ key: PHRASE_great_festival_comply_reason_P_B, text: "méltó módon tiszteletet adtál a fáraónak és [god] istennek azzal, hogy időben elküldted a [amount] [item] árut [city_name] városába a nagy ünnepre. Emellett," }
	{ key: PHRASE_great_festival_comply_reason_P_C, text: "bár méltó módon tiszteletet adtál a fáraónak és [god] istennek azzal, hogy időben elküldted a [amount] [item] árut [city_name] városába a nagy ünnepre," }
	{ key: PHRASE_great_festival_comply_reason_C_A, text: "mivel azzal, hogy elküldted a [amount] [item] árut, hozzájárultál [city_name] [god] tiszteletére rendezett nagy ünnepéhez," }
	{ key: PHRASE_great_festival_comply_reason_C_B, text: "segítettél [city_name] városának megtartani a [god] tiszteletére rendezett nagy ünnepet azzal, hogy elküldted a [amount] [item] árut, amit nagyra értékeltek. Emellett," }
	{ key: PHRASE_great_festival_comply_reason_C_C, text: "bár segítettél [city_name] városának megtartani a [god] tiszteletére rendezett nagy ünnepet azzal, hogy elküldted a [amount] [item] árut," }
	{ key: PHRASE_great_festival_too_late_reason_P_A, text: "mivel túl későn küldted el a [amount] [item] árut a fáraó [god] tiszteletére rendezett nagy ünnepére [city_name] városába," }
	{ key: PHRASE_great_festival_too_late_reason_P_B, text: "túl későn küldted el a [amount] [item] árut a fáraó [god] tiszteletére rendezett nagy ünnepére [city_name] városába. Emellett," }
	{ key: PHRASE_great_festival_too_late_reason_P_C, text: "annak ellenére, hogy a [amount] [item] áru túl későn érkezett meg a fáraó [god] tiszteletére rendezett nagy ünnepére [city_name] városába, mivel megtetted a szükséges erőfeszítést," }
	{ key: PHRASE_great_festival_too_late_reason_C_A, text: "mivel a [city_name] által a [god] tiszteletére rendezett nagy ünnephez kért [amount] [item] áru nem érkezett meg időben," }
	{ key: PHRASE_great_festival_too_late_reason_C_B, text: "a [city_name] által a [god] tiszteletére rendezett nagy ünnephez kért [amount] [item] áru nem érkezett meg időben. Emellett," }
	{ key: PHRASE_great_festival_too_late_reason_C_C, text: "annak ellenére, hogy az általad [city_name] városába küldött [amount] [item] áru nem érkezett meg időben a [god] tiszteletére rendezett nagy ünnepre, mivel minden tőled telhetőt megtettél," }
	{ key: PHRASE_great_festival_refuse_reason_P_A, text: "mivel elmulasztottad teljesíteni a fáraó kérését, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre [city_name] városába," }
	{ key: PHRASE_great_festival_refuse_reason_P_B, text: "elmulasztottad teljesíteni a fáraó kérését, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre [city_name] városába. Emellett," }
	{ key: PHRASE_great_festival_refuse_reason_P_C, text: "annak ellenére, hogy nem teljesítetted a fáraó kérését, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre [city_name] városába," }
	{ key: PHRASE_great_festival_refuse_reason_C_A, text: "mivel figyelmen kívül hagytad [city_name] városát és kérésüket, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre," }
	{ key: PHRASE_great_festival_refuse_reason_C_B, text: "figyelmen kívül hagytad [city_name] városát és kérésüket, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre. Emellett," }
	{ key: PHRASE_great_festival_refuse_reason_C_C, text: "bár figyelmen kívül hagytad [city_name] városát és kérésüket, hogy [amount] [item] árut küldj a [god] tiszteletére rendezett nagy ünnepre," }
	{ key: PHRASE_great_festival_no_reason_P_A, text: "mivel a fáraó tiszteletét kívánja leróni az isten előtt," }
	{ key: PHRASE_great_festival_no_reason_P_B, text: "mivel [god] még mindig elégedetlen," }
	{ key: PHRASE_great_festival_no_reason_P_C, text: "" }
	{ key: PHRASE_great_festival_no_reason_C_A, text: "mivel [city_name] élvezi [god] áldását," }
	{ key: PHRASE_great_festival_no_reason_C_B, text: "mivel [god] még mindig elégedetlen," }
	{ key: PHRASE_great_festival_no_reason_C_C, text: "" }
	{ key: PHRASE_project_title_P, text: "Építkezés a fáraónak" }
	{ key: PHRASE_project_title_C, text: "Építési projekt" }
	{ key: PHRASE_project_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] a fáraó olyan hatalmas építkezésbe kezdett, hogy szüksége van [amount] [item] árura [city_name] városában. Küldd el [time_allotted] hónapon belül. Bármi is készül, bizonyosan Egyiptom dicsőségét fogja szolgálni." }
	{ key: PHRASE_project_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] [city_name] városa azt kéri, hogy [time_allotted] hónapon belül küldj [amount] [item] árut egy nagyszabású építkezéshez." }
	{ key: PHRASE_project_reminder_P, text: "[greeting] [player_name], a fáraó már a harag határán áll. Még mindig nem küldted el a [amount] [item] árut [city_name] városába az építkezéséhez. Már csak 6 hónapod maradt a fáraó kérésének teljesítésére." }
	{ key: PHRASE_project_reminder_C, text: "[greeting] [player_name], [city_name] városának szüksége van [amount] [item] árura, hogy befejezhesse építkezését. Küldd el a szállítmányt 6 hónapon belül, különben a város vezetői elégedetlenné válhatnak." }
	{ key: PHRASE_project_overdue_P, text: "[greeting] [player_name], a fáraót felháborítja a szemtelenséged. Nem küldted el időben a [amount] [item] árut [city_name] városába, ezért nem tudta befejezni építkezését. Ha még most is elküldöd, talán mentheted a becsületedet." }
	{ key: PHRASE_project_overdue_C, text: "[greeting] [player_name], [city_name] fontolgatja, hogy panaszt tesz ellened a fáraónál. Mivel nem küldted el időben a [amount] [item] árut, előfordulhat, hogy nem tudják befejezni építkezésüket. Ha mégis elküldöd a szállítmányt, talán be tudják fejezni a munkát, és nem tesznek említést mulasztásodról." }
	{ key: PHRASE_project_warning_P, text: "[greeting] [player_name], egy befejezetlen építkezés csak szégyent hoz a fáraóra. Már csak 6 hónapod maradt, hogy elküldd a [amount] [item] árut [city_name] városába az építkezéséhez. Ha cserbenhagyod, osztozni fogsz a szégyenében." }
	{ key: PHRASE_project_warning_C, text: "[greeting] [player_name], már csak 6 hónapod maradt, hogy elküldd a [amount] [item] árut [city_name] városába az építkezésükhöz. Ha nem küldöd el az árut, nem lehet tudni, hogyan torolják meg a mulasztásodat." }
	{ key: PHRASE_project_comply_reason_P_A, text: "mivel az általad küldött [amount] [item] áru nélkülözhetetlen volt a fáraó [city_name] városában zajló építkezésének időben történő befejezéséhez," }
	{ key: PHRASE_project_comply_reason_P_B, text: "az általad küldött [amount] [item] áru nélkülözhetetlen volt a fáraó [city_name] városában zajló építkezésének időben történő befejezéséhez. Emellett," }
	{ key: PHRASE_project_comply_reason_P_C, text: "annak ellenére, hogy az általad küldött [amount] [item] áru nélkülözhetetlen volt a fáraó [city_name] városában zajló építkezésének időben történő befejezéséhez," }
	{ key: PHRASE_project_comply_reason_C_A, text: "mivel azzal, hogy elküldted a [amount] [item] árut, hozzájárultál ahhoz, hogy [city_name] időben befejezhesse építkezését," }
	{ key: PHRASE_project_comply_reason_C_B, text: "azzal, hogy elküldted a [amount] [item] árut, segítettél [city_name] városának tartani az építkezés ütemtervét. Egyébként," }
	{ key: PHRASE_project_comply_reason_C_C, text: "bár azzal, hogy elküldted a [amount] [item] árut, hozzájárultál ahhoz, hogy [city_name] időben befejezhesse építkezését," }
	{ key: PHRASE_project_too_late_reason_P_A, text: "mivel túl sokáig vártál a [amount] [item] áru elküldésével, és ezzel késleltetted a fáraó [city_name] városában zajló építkezését," }
	{ key: PHRASE_project_too_late_reason_P_B, text: "a fáraó [city_name] városában zajló építkezése megakadt, mert túl sokáig vártál az általa kért [amount] [item] áru elküldésével. Emellett," }
	{ key: PHRASE_project_too_late_reason_P_C, text: "annak ellenére, hogy túl sokáig vártál a [amount] [item] áru elküldésével, és ezzel késleltetted a fáraó [city_name] városában zajló építkezését, erőfeszítésedet értékelték, ezért" }
	{ key: PHRASE_project_too_late_reason_C_A, text: "mivel halogattad, és nem küldted el [city_name] városának a kért [amount] [item] árut," }
	{ key: PHRASE_project_too_late_reason_C_B, text: "halogattad a [city_name] által kért [amount] [item] áru elküldését. Egyébként," }
	{ key: PHRASE_project_too_late_reason_C_C, text: "annak ellenére, hogy halogattad a [city_name] által kért [amount] [item] áru elküldését, erőfeszítésedet értékelték, ezért" }
	{ key: PHRASE_project_refuse_reason_P_A, text: "mivel megtagadtad a fáraó kérését, hogy [amount] [item] árut küldj fontos építkezéséhez [city_name] városába," }
	{ key: PHRASE_project_refuse_reason_P_B, text: "meggondolatlanul megtagadtad a fáraó kérését, hogy [amount] [item] árut küldj fontos építkezéséhez [city_name] városába. Emellett," }
	{ key: PHRASE_project_refuse_reason_P_C, text: "bár nem volt bölcs dolog megtagadni a fáraó kérését, hogy [amount] [item] árut küldj fontos építkezéséhez [city_name] városába," }
	{ key: PHRASE_project_refuse_reason_C_A, text: "mivel semmibe vetted [city_name] városát és kérésüket, hogy [amount] [item] árut küldj," }
	{ key: PHRASE_project_refuse_reason_C_B, text: "semmibe vetted [city_name] városát és kérésüket, hogy [amount] [item] árut küldj. Emellett," }
	{ key: PHRASE_project_refuse_reason_C_C, text: "bár semmibe vetted [city_name] városát és kérésüket, hogy [amount] [item] árut küldj," }
	{ key: PHRASE_project_no_reason_P_A, text: "hogy megünnepelhesse számtalan dicső tettét," }
	{ key: PHRASE_project_no_reason_P_B, text: "mivel még sok munka vár elvégzésre" }
	{ key: PHRASE_project_no_reason_P_C, text: "" }
	{ key: PHRASE_project_no_reason_C_A, text: "Egyiptom dicsőségének öregbítésére," }
	{ key: PHRASE_project_no_reason_C_B, text: "mivel még sok a tennivaló" }
	{ key: PHRASE_project_no_reason_C_C, text: "" }
	{ key:PHRASE_famine_title_P, text: "Éhínség" }
	{ key:PHRASE_famine_title_C, text: "Éhínség" }
	{ key:PHRASE_famine_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] éhínség sújtja [city_name] városát. A fáraó megparancsolja, hogy nyújts segítséget. [time_allotted] áll rendelkezésedre, hogy [amount] [item] árut küldj a városnak, enyhítve szenvedésüket." }
	{ key:PHRASE_famine_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] éhínség sújtja [city_name] városát, és lakói éheznek. Küldj [amount] [item] árut [time_allotted] hónapon belül. Emberéletek forognak kockán!" }
	{ key:PHRASE_famine_reminder_P, text: "[greeting] [player_name], a fáraó kétségbe vonja, hogy van-e szíved. Még mindig nem küldted el a [amount] [item] árut [city_name] városába, pedig lakóinak nagy szükségük van rá. Már csak 6 hónapod maradt a fáraó kérésének teljesítésére." }
	{ key:PHRASE_famine_reminder_C, text: "[greeting] [player_name], [city_name] lakói az éhségtől jajonganak, te pedig még mindig nem küldted el a [amount] [item] árut. Küldd el a szállítmányt 6 hónapon belül, különben az éhség jajszavát a halottak miatti siralom váltja fel." }
	{ key:PHRASE_famine_overdue_P, text: "[greeting] [player_name], a fáraó szerint olyan kegyetlen vagy, mint egy vipera. Semmit sem tettél honfitársaid éhségének enyhítésére. Még mindig elküldheted a [amount] [item] árut [city_name] városába, és talán visszanyerheted a fáraó jóindulatát." }
	{ key:PHRASE_famine_overdue_C, text: "[greeting] [player_name], úgy tűnik, az éhezők kétségbeesett segélykiáltásai süket fülekre találtak. Nem küldted el időben a [amount] [item] árut [city_name] városába. Jobb későn, mint soha... ha még most is elküldöd az élelmet, talán enyhítheted a szenvedést, feltéve, hogy maradt még, akinek segíthetsz." }
	{ key:PHRASE_famine_warning_P, text: "[greeting] [player_name], ha nem küldesz [amount] [item] árut [city_name] városába 6 hónapon belül, semmit sem érsz el. A fáraó rossz néven veszi kegyetlenségedet, ha elmulasztod elküldeni a kért árut." }
	{ key:PHRASE_famine_warning_C, text: "[greeting] [player_name], [city_name] lakói azon tűnődnek, vajon kőből van-e a szíved. Már csak 6 hónapod maradt, hogy elküldd a [amount] [item] árut szenvedésük enyhítésére. Ha megtagadod tőlük, haláluk a te lelkeden szárad." }
	{ key:PHRASE_famine_comply_reason_P_A, text: "mivel a fáraó parancsának megfelelően gyorsan elküldted a [amount] [item] árut [city_name] szükségleteinek enyhítésére," }
	{ key:PHRASE_famine_comply_reason_P_B, text: "a fáraó parancsának megfelelően gyorsan elküldted a [amount] [item] árut [city_name] szükségleteinek enyhítésére. Bölcs döntés volt. Most pedig," }
	{ key:PHRASE_famine_comply_reason_P_C, text: "bár a fáraó parancsának megfelelően gyorsan elküldted a [amount] [item] árut [city_name] szükségleteinek enyhítésére, mégis" }
	{ key:PHRASE_famine_comply_reason_C_A, text: "mivel az általad küldött [amount] [item] áru jóllakatta [city_name] lakóit az éhínség idején," }
	{ key:PHRASE_famine_comply_reason_C_B, text: "az általad [city_name] városába küldött [amount] [item] áru jóllakatta a lakosságot az éhínség idején. Emellett a vezírek jelentése szerint" }
	{ key:PHRASE_famine_comply_reason_C_C, text: "bár az általad [city_name] lakóinak küldött [amount] [item] áru segített átvészelni a közelmúltbeli éhínséget, mégis" }
	{ key:PHRASE_famine_too_late_reason_P_A, text: "mivel túl sokáig hagytad szenvedni a fáraó népét [city_name] városában azzal, hogy késlekedtél a [amount] [item] áru elküldésével," }
	{ key:PHRASE_famine_too_late_reason_P_B, text: "túl sokáig hagytad szenvedni a fáraó népét [city_name] városában azzal, hogy késlekedtél a számukra szükséges [amount] [item] áru elküldésével. Emellett a vezírek jelentése szerint" }
	{ key:PHRASE_famine_too_late_reason_P_C, text: "bár túl sokáig hagytad szenvedni a fáraó népét [city_name] városában azzal, hogy késlekedtél a számukra szükséges [amount] [item] áru elküldésével, a szállítmány végül mégis némi segítséget jelentett, ezért" }
	{ key:PHRASE_famine_too_late_reason_C_A, text: "mivel túl sokáig késlekedtél a [amount] [item] áru elküldésével, hogy enyhítsd [city_name] lakóinak szenvedését," }
	{ key:PHRASE_famine_too_late_reason_C_B, text: "túlságosan sokáig késlekedtél a [amount] [item] áru elküldésével, hogy enyhítsd [city_name] lakóinak szenvedését, ezért megpróbáltatásaik súlyosak voltak. Ráadásul," }
	{ key:PHRASE_famine_too_late_reason_C_C, text: "bár túl sokáig késlekedtél a [amount] [item] áru elküldésével [city_name] lakóinak, az élelem végül némileg enyhítette az éhínség utóhatásait, ezért" }
	{ key:PHRASE_famine_refuse_reason_P_A, text: "mivel cserbenhagytad a fáraót és [city_name] lakóit az éhínség idején azzal, hogy nem küldted el a [amount] [item] árut," }
	{ key:PHRASE_famine_refuse_reason_P_B, text: "cserbenhagytad a fáraót és [city_name] lakóit az éhínség idején azzal, hogy nem küldted el a [amount] [item] árut. Ez nem volt bölcs döntés. Emellett a vezírek jelentése szerint" }
	{ key:PHRASE_famine_refuse_reason_P_C, text: "cserbenhagytad a fáraót és [city_name] lakóit az éhínség idején azzal, hogy nem küldted el a [amount] [item] árut, de ennek ellenére" }
	{ key:PHRASE_famine_refuse_reason_C_A, text: "mivel hátat fordítottál [city_name] lakóinak az éhínség idején, és visszatartottad a [amount] [item] árut," }
	{ key:PHRASE_famine_refuse_reason_C_B, text: "hátat fordítottál [city_name] lakóinak az éhínség idején, és visszatartottad a [amount] [item] árut. A vezírek jelentése szerint továbbá" }
	{ key:PHRASE_famine_refuse_reason_C_C, text: "bár hátat fordítottál [city_name] lakóinak az éhínség idején, és visszatartottad a [amount] [item] árut," }
	{ key:PHRASE_famine_no_reason_P_A, text: "a szerencse elfordult a fáraó népétől, és" }
	{ key:PHRASE_famine_no_reason_P_B, text: "a megpróbáltatások egyre csak halmozódnak, mert" }
	{ key:PHRASE_famine_no_reason_P_C, text: "" }
	{ key:PHRASE_famine_no_reason_C_A, text: "[city_name] lakói kezdik elveszíteni a reményt, mert" }
	{ key:PHRASE_famine_no_reason_C_B, text: "a megpróbáltatások egyre csak halmozódnak, mert" }
	{ key:PHRASE_famine_no_reason_C_C, text: "" }
	{ key:PHRASE_threat_title_P, text: "A fáraó követelése" }
	{ key:PHRASE_threat_title_C, text: "Egy másik város követelése" }
	{ key:PHRASE_threat_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] a fáraó megparancsolja, hogy [time_allotted] hónapon belül küldj [amount] [item] árut [city_name] városába. Ellenkező esetben seregeivel megtámadja virágzó városodat." }
	{ key:PHRASE_threat_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] [city_name] városa azt követeli, hogy [time_allotted] hónapon belül küldj [amount] [item] árut. Ha megtagadod kérésüket, [city_name] seregei megtámadják virágzó városodat." }
	{ key:PHRASE_threat_reminder_P, text: "[greeting] [player_name], a gőgös fáraó seregeket toboroz, és hamarosan megindítja a támadást. Küldd el a [amount] [item] árut [city_name] városába 6 hónapon belül, hogy elkerüld a kellemetlen következményeket." }
	{ key:PHRASE_threat_reminder_C, text: "[greeting] [player_name], [city_name] serege háborúra készül, és alig várja az összecsapást. Ha 6 hónapon belül elküldöd a [amount] [item] árut, a város felhagy a támadási szándékával. Katonáik azonban csalódottak lesznek." }
	{ key:PHRASE_threat_overdue_P, text: "[greeting] [player_name], lejárt a határidő, és a fáraó vért kíván. Talán még távol tarthatod seregeit, ha a lehető leghamarabb elküldöd a [amount] [item] árut [city_name] városába." }
	{ key:PHRASE_threat_overdue_C, text: "[greeting] [player_name], [city_name] minden utcáját csatakiáltások töltik be, miközben seregeik városod elpusztítására készülnek. Küldd el a [amount] [item] árut [city_name] városába mielőbb, és talán irgalmat tanúsítanak." }
	{ key:PHRASE_threat_warning_P, text: "[greeting] [player_name], a hiú fáraó erővel akarja megszerezni azt, amit önként nem adtál oda. Serege készen áll, de még megmentheted városodat a vérontástól, ha 6 hónapon belül elküldöd a [amount] [item] árut. Ellenkező esetben készítsd fel népedet a háborúra." }
	{ key:PHRASE_threat_warning_C, text: "[greeting] [player_name], [city_name] hódító seregei készen állnak az indulásra. Ha 6 hónapon belül elküldöd a [amount] [item] árut, a támadó sereg talán sértetlenül hagyja városodat." }
	{ key:PHRASE_threat_comply_reason_P_A, text: "mivel engedtél a fáraó követelésének, és elküldted a [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_threat_comply_reason_P_B, text: "engedtél a fáraó követelésének, és elküldted a [amount] [item] árut [city_name] városába. Emellett a vezírek jelentése szerint" }
	{ key:PHRASE_threat_comply_reason_P_C, text: "bár teljesítetted a fáraó [city_name] városával kapcsolatos követelését," }
	{ key:PHRASE_threat_comply_reason_C_A, text: "mivel meghajoltál [city_name] parancsai előtt, és elküldted a [amount] [item] árut," }
	{ key:PHRASE_threat_comply_reason_C_B, text: "meghajoltál [city_name] parancsai előtt, és elküldted a [amount] [item] árut. Emellett úgy tűnik, hogy" }
	{ key:PHRASE_threat_comply_reason_C_C, text: "bár engedtél [city_name] [amount] [item] áru iránti követelésének, mégis" }
	{ key:PHRASE_threat_too_late_reason_P_A, text: "a [amount] [item] áru [city_name] városába történő elküldésének késedelme, ahogy azt a fáraó követelte, próbára teszi türelmét, és emiatt" }
	{ key:PHRASE_threat_too_late_reason_P_B, text: "a [amount] [item] áru [city_name] városába történő elküldésének késedelme, ahogy azt a fáraó követelte, próbára teszi türelmét. Térjünk át más ügyekre:" }
	{ key:PHRASE_threat_too_late_reason_P_C, text: "a [amount] [item] áru [city_name] városába történő elküldésének késedelme, ahogy azt a fáraó követelte, próbára teszi türelmét, de ennek ellenére erőfeszítésedet értékeljük. Ezért" }
	{ key:PHRASE_threat_too_late_reason_C_A, text: "mivel alábecsülted [city_name] fenyegetését, és nem küldted el időben a [amount] [item] árut," }
	{ key:PHRASE_threat_too_late_reason_C_B, text: "bizonyára alábecsülted [city_name] fenyegetését, hiszen nem küldted el időben a [amount] [item] árut. De ez már a múlté, most" }
	{ key:PHRASE_threat_too_late_reason_C_C, text: "nagy kockázatot vállaltál azzal, hogy nem küldted el időben a [amount] [item] árut [city_name] városának követelése szerint. Mindazonáltal, mivel végül teljesítetted a kérést," }
	{ key:PHRASE_threat_refuse_reason_P_A, text: "mivel szembeszálltál a fáraó parancsával, hogy küldj [amount] [item] árut [city_name] városába," }
	{ key:PHRASE_threat_refuse_reason_P_B, text: "szembeszálltál a fáraó parancsával, hogy küldj [amount] [item] árut [city_name] városába. Emellett," }
	{ key:PHRASE_threat_refuse_reason_P_C, text: "annak ellenére, hogy megtagadtad a fáraó fenyegetésének figyelembevételét, amelyben [amount] [item] áru küldését követelte [city_name] városába," }
	{ key:PHRASE_threat_refuse_reason_C_A, text: "mivel tudatosan veszélybe sodortad magad azzal, hogy megtagadtad a [amount] [item] áru elküldését [city_name] városába," }
	{ key:PHRASE_threat_refuse_reason_C_B, text: "tudatosan veszélybe sodortad magad azzal, hogy megtagadtad a [amount] [item] áru elküldését [city_name] városába. Azt is tudnod kell, hogy" }
	{ key:PHRASE_threat_refuse_reason_C_C, text: "bár kétségtelenül veszélybe sodortad magad azzal, hogy megtagadtad a [amount] [item] áru elküldését [city_name] városába," }
	{ key:PHRASE_threat_no_reason_P_A, text: "mert rossz kedvében van," }
	{ key:PHRASE_threat_no_reason_P_B, text: "mivel úgy tűnik, a fáraó rossz kedvének nincs vége," }
	{ key:PHRASE_threat_no_reason_P_C, text: "" }
	{ key:PHRASE_threat_no_reason_C_A, text: "mivel [city_name] dicsőségre áhítozik," }
	{ key:PHRASE_threat_no_reason_C_B, text: "úgy tűnik, [city_name] soha nem lesz elégedett," }
	{ key:PHRASE_threat_no_reason_C_C, text: "" }
	{ key:PHRASE_eg_city_falls_title, text: "Egyiptomi város elesik" }
	{ key:PHRASE_eg_city_falls_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a hatalmas [city_name] városa ellenségeink kezére került." }
	{ key:PHRASE_eg_city_falls_reason_A, text: "mivel [city_name] városa az inváziós erők kezére került," }
	{ key:PHRASE_eg_city_falls_reason_B, text: "[city_name] városa az inváziós erők kezére került. Sőt," }
	{ key:PHRASE_eg_city_falls_reason_C, text: "bár [city_name] városa az inváziós erők kezére került," }
	{ key:PHRASE_eg_city_falls_no_reason_A, text: "jaj [city_name] városának:" }
	{ key:PHRASE_eg_city_falls_no_reason_B, text: "úgy tűnik, [city_name] városának bajai soha nem érnek véget, mert" }
	{ key:PHRASE_eg_city_falls_no_reason_C, text: "" }
	{ key:PHRASE_foreign_city_conquered_title, text: "Idegen város meghódítva" }
	{ key:PHRASE_foreign_city_conquered_initial_announcement, text: "[greeting] [player_name], [reason_phrase] Egyiptom sikeresen meghódította a híres [city_name] városát, tovább növelve befolyásunkat!" }
	{ key:PHRASE_foreign_city_conquered_reason_A, text: "mivel a [city_name] idegen várost seregeink meghódították," }
	{ key:PHRASE_foreign_city_conquered_reason_B, text: "a [city_name] idegen várost seregeink meghódították! Most pedig," }
	{ key:PHRASE_foreign_city_conquered_reason_C, text: "bár a [city_name] idegen várost seregeink meghódították," }
	{ key:PHRASE_foreign_city_conquered_no_reason_A, text: "fegyvereink erejének köszönhetően," }
	{ key:PHRASE_foreign_city_conquered_no_reason_B, text: "királyságunk ereje tovább növekszik. Most" }
	{ key:PHRASE_foreign_city_conquered_no_reason_C, text: "" }
	{ key:PHRASE_route_opened_title, text: "Új kereskedelmi útvonal elérhető" }
	{ key:PHRASE_route_opened_initial_announcement, text: "[greeting] [player_name], [reason_phrase] új kereskedelmi útvonal nyitható [city_name] városába." }
	{ key:PHRASE_route_opened_reason_A, text: "mivel új kereskedelmi útvonal vált elérhetővé [city_name] városába," }
	{ key:PHRASE_route_opened_reason_B, text: "új kereskedelmi útvonal vált elérhetővé [city_name] városába, és" }
	{ key:PHRASE_route_opened_reason_C, text: "bár lehetővé vált a kereskedelem [city_name] városával," }
	{ key:PHRASE_route_opened_no_reason_A, text: "a diplomáciai tevékenységnek köszönhetően," }
	{ key:PHRASE_route_opened_no_reason_B, text: "változás szele fúj, mert" }
	{ key:PHRASE_route_opened_no_reason_C, text: "" }
	{ key:PHRASE_route_closed_title, text: "Kereskedelmi útvonal lezárul" }
	{ key:PHRASE_route_closed_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a [city_name] városába vezető kereskedelmi útvonalat lezárták." }
	{ key:PHRASE_route_closed_reason_A, text: "mivel a [city_name] városába vezető kereskedelmi útvonal lezárult," }
	{ key:PHRASE_route_closed_reason_B, text: "a [city_name] városába vezető kereskedelmi útvonal lezárult, és ráadásul" }
	{ key:PHRASE_route_closed_reason_C, text: "bár a [city_name] városába vezető kereskedelmi útvonal lezárult," }
	{ key:PHRASE_route_closed_no_reason_A, text: "a politikai bizonytalanság miatt," }
	{ key:PHRASE_route_closed_no_reason_B, text: "ezt előre kellett volna látni. Úgy tűnik," }
	{ key:PHRASE_route_closed_no_reason_C, text: "" }
	{ key:PHRASE_trade_city_siege_title, text: "Kereskedőváros ostrom alatt" }
	{ key:PHRASE_trade_city_siege_announcement, text: "[greeting] [player_name], [reason_phrase] súlyos ostrom sújtja [city_name] városát." }
	{ key:PHRASE_trade_city_siege_reason_A, text: "mivel [city_name] ostrom alatt áll," }
	{ key:PHRASE_trade_city_siege_reason_B, text: "[city_name] ostrom alatt áll, és" }
	{ key:PHRASE_trade_city_siege_reason_C, text: "bár [city_name] ostrom alatt áll," }
	{ key:PHRASE_trade_city_siege_no_reason_A, text: "a katonai felderítők szörnyű hírekkel szolgálnak. Úgy tűnik," }
	{ key:PHRASE_trade_city_siege_no_reason_B, text: "bajainak látszólag nincs vége, mert" }
	{ key:PHRASE_trade_city_siege_no_reason_C, text: "" }
	{ key:PHRASE_eg_city_saved_title, text: "Egyiptomi város megmentve" }
	{ key:PHRASE_eg_city_saved_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [city_name] megszabadult ellenségeinktől." }
	{ key:PHRASE_eg_city_saved_reason_A, text: "mivel [city_name] megszabadult ellenségeinktől," }
	{ key:PHRASE_eg_city_saved_reason_B, text: "[city_name] megszabadult ellenségeinktől! Most pedig," }
	{ key:PHRASE_eg_city_saved_reason_C, text: "bár [city_name] megszabadult ellenségeinktől," }
	{ key:PHRASE_eg_city_saved_no_reason_A, text: "az egyiptomi hadsereg hősies helytállásának köszönhetően," }
	{ key:PHRASE_eg_city_saved_no_reason_B, text: "a háború hullámai most ide-oda csapódnak" }
	{ key:PHRASE_eg_city_saved_no_reason_C, text: "" }
	{ key:PHRASE_battle_won_title, text: "Győzelem a csatában" }
	{ key:PHRASE_battle_won_initial_announcement, text: "[greeting] [player_name], [reason_phrase] az egyiptomi hadsereg győzelmet aratott!" }
	{ key:PHRASE_battle_won_reason_A, text: "mivel seregeink diadalmaskodtak a távoli [city_name] csatájában," }
	{ key:PHRASE_battle_won_reason_B, text: "seregeink győzelmet arattak a távoli [city_name] csatájában. Most" }
	{ key:PHRASE_battle_won_reason_C, text: "bár seregeink győzelmet arattak a [city_name] csatájában," }
	{ key:PHRASE_battle_won_no_reason_A, text: "a jól képzett katonák erejének köszönhetően a távoli [city_name] városában," }
	{ key:PHRASE_battle_won_no_reason_B, text: "úgy tűnik, a csodáknak nincs vége, hiszen [city_name] városánál" }
	{ key:PHRASE_battle_won_no_reason_C, text: "" }
	{ key:PHRASE_battle_lost_title, text: "Az egyiptomi hadsereg vereséget szenvedett" }
	{ key:PHRASE_battle_lost_initial_announcement, text: "[greeting] [player_name], [reason_phrase] az egyiptomi hadsereg vereséget szenvedett [city_name] városánál." }
	{ key:PHRASE_battle_lost_reason_A, text: "mivel Egyiptom vereséget szenvedett ellenségeitől [city_name] városánál," }
	{ key:PHRASE_battle_lost_reason_B, text: "Egyiptom vereséget szenvedett ellenségeitől [city_name] városánál. Sőt," }
	{ key:PHRASE_battle_lost_reason_C, text: "bár Egyiptom vereséget szenvedett ellenségeitől [city_name] városánál," }
	{ key:PHRASE_battle_lost_no_reason_A, text: "nagy balszerencse sújtotta a katonákat, mert" }
	{ key:PHRASE_battle_lost_no_reason_B, text: "a háború oly kiszámíthatatlan. Sajnos" }
	{ key:PHRASE_battle_lost_no_reason_C, text: "" }
	{ key:PHRASE_acknowledgement_title, text: "A teljesítés nyugtázva" }
	{ key:PHRASE_acknowledgement_initial_announcement, text: "[greeting] [player_name], [reason_phrase] városod biztonságban van... egyelőre." }
	{ key:PHRASE_acknowledgement_reason_A, text: "mivel engedelmesen meghajoltál egy fenyegetés előtt," }
	{ key:PHRASE_acknowledgement_reason_B, text: "engedelmesen meghajoltál egy fenyegetés előtt," }
	{ key:PHRASE_acknowledgement_reason_C, text: "bár engedelmesen meghajoltál egy fenyegetés előtt," }
	{ key:PHRASE_acknowledgement_no_reason_A, text: "megváltozott hozzáállásodnak köszönhetően," }
	{ key:PHRASE_acknowledgement_no_reason_B, text: "semmi sem biztos, de" }
	{ key:PHRASE_acknowledgement_no_reason_C, text: "" }
	{ key: PHRASE_pharaoh_attacks_you_title, text: "A fáraó serege támad" }
	{ key: PHRASE_pharaoh_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a fáraó serege úton van, és [time_until_attack] hónap múlva eléri városodat." }
	{ key: PHRASE_pharaoh_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] a fáraó serege egyre közelebb ér, és két év múlva eléri városodat." }
	{ key: PHRASE_pharaoh_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] a fáraó serege csatára készen áll, és egy év múlva eléri városodat." }
	{ key: PHRASE_pharaoh_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] a fáraó serege türelmetlenül várja a támadást, és hat hónap múlva eléri városodat." }
	{ key: PHRASE_pharaoh_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] a fáraó serege már csak egy hónapnyira van a várostól!." }
	{ key: PHRASE_pharaoh_attacks_you_city_attacked_alert, text: "[greeting] [player_name], a fáraó serege megérkezett!" }
	{ key: PHRASE_pharaoh_attacks_you_reason_A, text: "mivel városodat megtámadta a fáraó serege," }
	{ key: PHRASE_pharaoh_attacks_you_reason_B, text: "városodat megtámadta a fáraó serege. Sőt" }
	{ key: PHRASE_pharaoh_attacks_you_reason_C, text: "bár városodat megtámadta a fáraó serege," }
	{ key: PHRASE_pharaoh_attacks_you_no_reason_A, text: "a fáraó néha olyan okokból cselekszik, amelyeket csak ő ismer." }
	{ key: PHRASE_pharaoh_attacks_you_no_reason_B, text: "a fáraó kiszámíthatatlan. Most pedig" }
	{ key: PHRASE_pharaoh_attacks_you_no_reason_C, text: "mivel a királyságban elfoglalt helyzeted mélypontra süllyedt," }
	{ key: PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text: "a királyságban elfoglalt helyzeted teljesen összeomlott. Talán még több ajándék az egyiptomi nép számára fordíthat a helyzeten, bár még most is" }
	{ key: PHRASE_eg_city_attacks_you_title, text: "Az egyiptomi hadsereg támad" }
	{ key: PHRASE_eg_city_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] egy egyiptomi hadsereg készül a támadásra, és [time_until_attack] hónap múlva eléri városodat." }
	{ key: PHRASE_eg_city_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] egy egyiptomi hadsereg megkezdte menetelését, és két év múlva eléri városodat." }
	{ key: PHRASE_eg_city_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] városod egy év múlva egy egyiptomi hadsereg támadásának lesz kitéve." }
	{ key: PHRASE_eg_city_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] egy egyiptomi hadsereg közeledik, és hat hónap múlva eléri városodat." }
	{ key: PHRASE_eg_city_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] egy egyiptomi hadsereg közeledik határaidhoz, és egy hónap múlva eléri városodat." }
	{ key: PHRASE_eg_city_attacks_you_city_attacked_alert, text: "[greeting] [player_name], egy egyiptomi katonákból álló megszálló sereg érkezett!" }
	{ key: PHRASE_eg_city_attacks_you_reason_A, text: "mivel városodat megtámadta az egyiptomi hadsereg," }
	{ key: PHRASE_eg_city_attacks_you_reason_B, text: "az egyiptomi hadsereg megtámadta városodat! Ezenfelül" }
	{ key: PHRASE_eg_city_attacks_you_reason_C, text: "bár városodat megtámadta az egyiptomi hadsereg," }
	{ key: PHRASE_eg_city_attacks_you_no_reason_A, text: "légy óvatos:" }
	{ key: PHRASE_eg_city_attacks_you_no_reason_B, text: "eljött a háború ideje, mert" }
	{ key: PHRASE_eg_city_attacks_you_no_reason_C, text: "mivel a királyságban olyan alacsony a hírneved," }
	{ key: PHRASE_eg_city_attacks_you_because_of_low_kingdom, text: "a királyságban elfoglalt helyzeted teljesen összeomlott. Talán még több ajándék az egyiptomi nép számára fordíthat a helyzeten, bár még most is" }
	{ key: PHRASE_foreign_army_attacks_you_title, text: "Idegen hadsereg támadása" }
	{ key: PHRASE_foreign_army_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] közeledik, és [time_until_attack] hónap múlva eléri városodat." }
	{ key: PHRASE_foreign_army_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] két év múlva [a_foreign_army] már kapuid előtt áll majd." }
	{ key: PHRASE_foreign_army_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] alig várja, hogy megszálljon, és egy év múlva eléri városodat." }
	{ key: PHRASE_foreign_army_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] hat hónap múlva eléri városodat. Készülj fel az érkezésükre." }
	{ key: PHRASE_foreign_army_attacks_you_1month_Warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] egy hónap múlva érkezik a városba, hódítási szándékkal." }
	{ key: PHRASE_foreign_army_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [a_foreign_army] megérkezett, és elhatározták, hogy elpusztítják a várost!" }
	{ key: PHRASE_foreign_army_attacks_you_reason_A, text: "mivel városodat megtámadta [a_foreign_army]," }
	{ key: PHRASE_foreign_army_attacks_you_reason_B, text: "városodat megtámadta [a_foreign_army], és most" }
	{ key: PHRASE_foreign_army_attacks_you_reason_C, text: "bár városodat megtámadta [a_foreign_army]," }
	{ key: PHRASE_foreign_army_attacks_you_no_reason_A, text: "birodalmi álmaik miatt," }
	{ key: PHRASE_foreign_army_attacks_you_no_reason_B, text: "úgy tűnik, a baj sosem ér véget, mert" }
	{ key: PHRASE_foreign_army_attacks_you_no_reason_C, text: "" }
	{ key: PHRASE_rating_change_title_I, text: "Nő a királyságbeli megítélés" }
	{ key: PHRASE_rating_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] népszerűbbé váltál egyiptomi honfitársaid körében, és a királyságbeli megítélésed javult." }
	{ key: PHRASE_rating_change_reason_I_A, text: "mivel a királyságban nemrég javult a hírneved," }
	{ key: PHRASE_rating_change_reason_I_B, text: "a királyságban javult a megítélésed. Most" }
	{ key: PHRASE_rating_change_reason_I_C, text: "a hírneved javult, de" }
	{ key: PHRASE_rating_change_no_reason_I_A, text: "mivel jó idők járnak," }
	{ key: PHRASE_rating_change_no_reason_I_B, text: "ez jó hír, mert" }
	{ key: PHRASE_rating_change_no_reason_I_C, text: "a városod áldozatait a harcokban nagyra értékeli az egyiptomi nép. Ennek eredményeként" }
	{ key: PHRASE_rating_change_title_D, text: "Csökken a királyságbeli megítélés" }
	{ key: PHRASE_rating_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] az egyiptomi nép elégedetlen veled, és a királyságbeli megítélésed romlott." }
	{ key: PHRASE_rating_change_reason_D_A, text: "mivel a királyságbeli megítélésed olyan mélyre süllyedt," }
	{ key: PHRASE_rating_change_reason_D_B, text: "népszerűséged csökken az egész királyságban, és most" }
	{ key: PHRASE_rating_change_reason_D_C, text: "bár egyre kevésbé vagy népszerű a királyságban," }
	{ key: PHRASE_rating_change_no_reason_D_A, text: "a királyságban tapasztalható elégedetlenség miatt," }
	{ key: PHRASE_rating_change_no_reason_D_B, text: "ez rossz hír, mert" }
	{ key: PHRASE_rating_change_no_reason_D_C, text: "honfitársaid nem helyeslik erőszakos módszereidet. Ennek eredményeként" }
	{ key:PHRASE_price_change_title_I, text: "Áremelkedés" }
	{ key:PHRASE_price_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] [item] ára emelkedett. Ennek az árunak a behozatala most költségesebb, de exportálásával nagyobb haszon érhető el." }
	{ key:PHRASE_price_change_reason_I_A, text: "mivel [item] ára emelkedett," }
	{ key:PHRASE_price_change_reason_I_B, text: "[item] ára emelkedett, és mi több" }
	{ key:PHRASE_price_change_reason_I_C, text: "bár az árak emelkedtek," }
	{ key:PHRASE_price_change_no_reason_I_A, text: "a világon tapasztalható készletcsökkenés miatt," }
	{ key:PHRASE_price_change_no_reason_I_B, text: "ahogy a piac folyamatosan változik" }
	{ key:PHRASE_price_change_no_reason_I_C, text: "" }
	{ key:PHRASE_price_change_title_D, text: "Árcsökkenés" }
	{ key:PHRASE_price_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] [item] ára csökkent. Ez mérsékli az exportálásával elérhető nyereséget." }
	{ key:PHRASE_price_change_reason_D_A, text: "mivel a kereskedhető [item] ára csökkent," }
	{ key:PHRASE_price_change_reason_D_B, text: "az árak csökkentek, és mi több" }
	{ key:PHRASE_price_change_reason_D_C, text: "bár az árak csökkentek," }
	{ key:PHRASE_price_change_no_reason_D_A, text: "a királyságban kialakult túlzott bőség miatt," }
	{ key:PHRASE_price_change_no_reason_D_B, text: "ahogy a piac folyamatosan változik" }
	{ key:PHRASE_price_change_no_reason_D_C, text: "" }
	{ key: PHRASE_demand_change_title_I, text: "Fokozódó kereskedelem" }
	{ key: PHRASE_demand_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] [city_name] mostantól még több [item] kereskedelmére hajlandó." }
	{ key: PHRASE_demand_change_reason_I_A, text: "mivel [city_name] több [item] kereskedelmére hajlandó," }
	{ key: PHRASE_demand_change_reason_I_B, text: "[city_name] most több [item] kereskedelmét kívánja. Sőt" }
	{ key: PHRASE_demand_change_reason_I_C, text: "bár [city_name] több [item] kereskedelmét kívánja," }
	{ key: PHRASE_demand_change_no_reason_I_A, text: "mivel [city_name] fejlődik," }
	{ key: PHRASE_demand_change_no_reason_I_B, text: "az idők változnak, és" }
	{ key: PHRASE_demand_change_no_reason_I_C, text: "" }
	{ key: PHRASE_demand_change_title_D, text: "Csökkenő kereskedelem" }
	{ key: PHRASE_demand_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] [city_name] úgy döntött, hogy csökkentenie kell a veled kereskedni kívánt [item] mennyiségét." }
	{ key: PHRASE_demand_change_reason_D_A, text: "mivel [city_name] már nem kereskedik annyi [item] áruval," }
	{ key: PHRASE_demand_change_reason_D_B, text: "[city_name] már nem kereskedik annyi áruval, és" }
	{ key: PHRASE_demand_change_reason_D_C, text: "bár [city_name] már nem kereskedik annyi [item] áruval," }
	{ key: PHRASE_demand_change_no_reason_D_A, text: "mivel [city_name] lakói visszafogják kiadásaikat," }
	{ key: PHRASE_demand_change_no_reason_D_B, text: "az idők változnak, és" }
	{ key: PHRASE_demand_change_no_reason_D_C, text: "" }
	{ key: PHRASE_earthquake_title, text: "Földrengés!" }
	{ key: PHRASE_earthquake_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a homok megmozdult a lábunk alatt. Földünk soha többé nem lesz ugyanolyan. Tégy meg mindent, hogy helyreállítsd a földrengés által okozott károkat városodban és néped körében." }
	{ key: PHRASE_earthquake_reason_A, text: "egy rettenetes földrengés miatt," }
	{ key: PHRASE_earthquake_reason_B, text: "a rettenetes földrengésen felül," }
	{ key: PHRASE_earthquake_reason_C, text: "a rettenetes földrengés ellenére" }
	{ key: PHRASE_earthquake_no_reason_A, text: "a város retteg, mert" }
	{ key: PHRASE_earthquake_no_reason_B, text: "a baj ismét a várost sújtja, mert" }
	{ key: PHRASE_earthquake_no_reason_C, text: "" }
	{ key: PHRASE_stormy_seas_title, text: "Viharos tengerek" }
	{ key: PHRASE_stormy_seas_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a háborgó vizek azzal fenyegetnek, hogy szétszakítják a kereskedőhajókat. Hónapok telhetnek el, mire a szelek lecsendesednek, és a kereskedők ismét kockára merik tenni rakományaikat. Addig nem kereskedhetünk vízi úton." }
	{ key: PHRASE_stormy_seas_reason_A, text: "a felfoghatatlanul heves viharok miatt," }
	{ key: PHRASE_stormy_seas_reason_B, text: "miközben a közelmúlt viharai sújtanak bennünket," }
	{ key: PHRASE_stormy_seas_reason_C, text: "a rettenetes viharok ellenére" }
	{ key: PHRASE_stormy_seas_no_reason_A, text: "viharok tombolnak, és" }
	{ key: PHRASE_stormy_seas_no_reason_B, text: "gondjaink még csak most kezdődnek, mert" }
	{ key: PHRASE_stormy_seas_no_reason_C, text: "" }
	{ key: PHRASE_sandstorm_title, text: "Homokviharok" }
	{ key: PHRASE_sandstorm_initial_announcement, text: "[greeting] [player_name], [reason_phrase] a sodró homok eltakarta az utakat, néhol teljesen be is temetve azokat. A kereskedők ilyen körülmények között nem kockáztatják, hogy eltévednek, ezért nem indulnak útnak. Amíg a szelek el nem ülnek, egyetlen kereskedő sem tud átjutni." }
	{ key: PHRASE_sandstorm_reason_A, text: "mivel a kereskedők nem mernek útnak indulni homokvihar idején, és a szárazföldi kereskedelem leállt," }
	{ key: PHRASE_sandstorm_reason_B, text: "a homokviharok megállították a kereskedőket útjukon. Továbbá" }
	{ key: PHRASE_sandstorm_reason_C, text: "a közelmúlt homokviharai ellenére, amelyek akadályozták a kereskedelmet," }
	{ key: PHRASE_sandstorm_no_reason_A, text: "az erős szelek miatt," }
	{ key: PHRASE_sandstorm_no_reason_B, text: "a sivatag veszélyes hely, mert" }
	{ key: PHRASE_sandstorm_no_reason_C, text: "" }
	{ key: PHRASE_wage_change_title_I, text: "A munkások örülnek a béremelésnek" }
	{ key: PHRASE_wage_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] a bérek emelkedtek az egész királyságban. Saját munkásaid talán jövedelmezőbb helyekre távoznak, ha nem kapnak annyi fizetést, mint más városokban dolgozó társaik." }
	{ key: PHRASE_wage_change_reason_I_A, text: "mivel a bérek emelkedtek az egész királyságban," }
	{ key: PHRASE_wage_change_reason_I_B, text: "a bérek emelkedtek az egész királyságban, és" }
	{ key: PHRASE_wage_change_reason_I_C, text: "bár a bérek emelkedtek az egész királyságban," }
	{ key: PHRASE_wage_change_no_reason_I_A, text: "az idők változnak, és most" }
	{ key: PHRASE_wage_change_no_reason_I_B, text: "egyesek örülnek, mások panaszkodnak, mert" }
	{ key: PHRASE_wage_change_no_reason_I_C, text: "" }
	{ key: PHRASE_wage_change_title_D, text: "A bérek csökkennek" }
	{ key: PHRASE_wage_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] a bérek csökkentek Egyiptom egész királyságában. Úgy tűnik, mindenhol kevesebbért is hajlandók dolgozni az emberek." }
	{ key: PHRASE_wage_change_reason_D_A, text: "mivel a bérek csökkentek," }
	{ key: PHRASE_wage_change_reason_D_B, text: "a bérek csökkentek, és mi több," }
	{ key: PHRASE_wage_change_reason_D_C, text: "bár a bérek csökkentek," }
	{ key: PHRASE_wage_change_no_reason_D_A, text: "a költségek csökkentése érdekében," }
	{ key: PHRASE_wage_change_no_reason_D_B, text: "egyesek elégedetlenek, de a nomarkhoszok örülnek, mert" }
	{ key: PHRASE_wage_change_no_reason_D_C, text: "" }
	{ key: PHRASE_bad_water_title, text: "Szennyezett víz" }
	{ key: PHRASE_bad_water_initial_announcement, text: "[greeting] [player_name], [reason_phrase] néhány polgárod megbetegedett a vízben lévő szennyeződés miatt. Csak remélni lehet, hogy a probléma nem súlyosbodik." }
	{ key: PHRASE_bad_water_reason_A, text: "a közelmúltbeli vízszennyezés miatt," }
	{ key: PHRASE_bad_water_reason_B, text: "a közelmúltbeli vízszennyezés igen szerencsétlenül érintett bennünket. Most" }
	{ key: PHRASE_bad_water_reason_C, text: "bár a víz nemrég szennyeződött," }
	{ key: PHRASE_bad_water_no_reason_A, text: "a balszerencse leselkedik a városra, és" }
	{ key: PHRASE_bad_water_no_reason_B, text: ", ez valóban sajnálatos. Úgy tűnik" }
	{ key: PHRASE_bad_water_no_reason_C, text: "" }
	{ key: PHRASE_goldmine_cavein_title, text: "Beomlott aranybánya" }
	{ key: PHRASE_goldmine_cavein_initial_announcement, text: "[greeting] [player_name], [reason_phrase] egy aranybánya beomlott. Építészeink tehetetlenek voltak, hogy megakadályozzák. Csak remélni lehet, hogy a munkások időben kijutottak a bányából." }
	{ key: PHRASE_goldmine_cavein_reason_A, text: "mivel egy aranybánya beomlott," }
	{ key: PHRASE_goldmine_cavein_reason_B, text:	  "a legutóbbi aranybánya-beomlás igen sajnálatos volt. Most," }
	{ key: PHRASE_goldmine_cavein_reason_C, text:	  "annak ellenére, hogy nemrég beomlott egy aranybánya," }
	{ key: PHRASE_goldmine_cavein_no_reason_A, text: 		"a homok elmozdulása miatt," }
	{ key: PHRASE_goldmine_cavein_no_reason_B, text:	  "figyelmeztetés nélkül," }
	{ key: PHRASE_goldmine_cavein_no_reason_C, text:	  "" }
	{ key: PHRASE_landslide_title, text: 					"Földcsuszamlás" }
	{ key: PHRASE_landslide_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] egy szörnyű földcsuszamlás elvágott egy kereskedelmi útvonalat. Hónapokba telhet, mire az utat megtisztítják, és a kereskedők ismét útnak indulhatnak." }
	{ key: PHRASE_landslide_reason_A, text:  	 	 				"a közelmúltban történt földcsuszamlás miatt," }
	{ key: PHRASE_landslide_reason_B, text:	  "a közelmúltbeli földcsuszamlások pusztítóak voltak. Most," }
	{ key: PHRASE_landslide_reason_C, text:	  "annak ellenére, hogy a közelmúltban szörnyű földcsuszamlások történtek," }
	{ key: PHRASE_landslide_no_reason_A, text:  	 					"szörnyű hír érkezett:" }
	{ key: PHRASE_landslide_no_reason_B, text:	  "figyelmeztetés nélkül" }
	{ key: PHRASE_landslide_no_reason_C, text:	  "" }
	{ key: PHRASE_flood_fails_title, text: 					"Az áradás valószínűleg elmarad" }
	{ key: PHRASE_flood_fails_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] a papok rossz hírt hoztak...attól tartanak, hogy a következő áradás szinte biztosan elmarad! Rendszeresen ellenőrizd a nilométert...ha a papok jóslata nem javul, a városnak fel kell készülnie a legrosszabbra." }
	{ key: PHRASE_flood_fails_reason_A, text:  	 	 					"mivel az áradás várhatóan elmarad" }
	{ key: PHRASE_flood_fails_reason_B, text:	  "az áradás várhatóan elmarad, és" }
	{ key: PHRASE_flood_fails_reason_C, text:	  "annak ellenére, hogy az áradás várhatóan elmarad," }
	{ key: PHRASE_flood_fails_no_reason_A, text:		"az afrikai szárazság miatt," }
	{ key: PHRASE_flood_fails_no_reason_B, text:	  "gondjaink még csak most kezdődnek, mert" }
	{ key: PHRASE_flood_fails_no_reason_C, text:	  "" }
	{ key : PHRASE_perfect_flood_title, text: 					"Tökéletes áradás várható" }
	{ key : PHRASE_perfect_flood_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] ez valóban áldás, mivel igen nagy az esélye egy bőséges áradásnak! Időnként ellenőrizd a nilométert. Ha a jóslat rosszabbra fordul, a város felkészületlenül találhatja magát." }
	{ key : PHRASE_perfect_flood_reason_A, text:  	 	 				"mivel az áradást bőségesnek várták," }
	{ key : PHRASE_perfect_flood_reason_B, text:	  "az áradást bőségesnek várták, és" }
	{ key : PHRASE_perfect_flood_reason_C, text:	  "annak ellenére, hogy az áradást bőségesnek várták," }
	{ key : PHRASE_perfect_flood_no_reason_A, text:  	 					"várhatóan megérkeznek az afrikai monszunok, ezért" }
	{ key : PHRASE_perfect_flood_no_reason_B, text:	  "valóban szerencsések vagyunk, mert" }
	{ key : PHRASE_perfect_flood_no_reason_C, text:	  "" }
	{ key: PHRASE_bedouin_attacks_you_title, text: 					"Beduin sereg támadása" }
	{ key: PHRASE_bedouin_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] egy beduin sereg közeledik a városhoz, és [time_until_attack] hónap múlva támadni fog." }
	{ key: PHRASE_bedouin_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] egy beduin sereg egyre közelebb kerül, és két év múlva eléri a várost." }
	{ key: PHRASE_bedouin_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] egy beduin sereg már úton van, és egy év múlva eléri a várost." }
	{ key: PHRASE_bedouin_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] egy beduin sereg háborúra készül, és hat hónap múlva eléri a várost." }
	{ key: PHRASE_bedouin_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] egy beduin sereg már nagyon közel van, és egy hónap múlva eléri a várost." }
	{ key: PHRASE_bedouin_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], egy támadó beduin sereg rontott ránk!" }
	{ key: PHRASE_bedouin_attacks_you_reason_A, text:  	 	 		"mivel a városod sikeresen visszaverte a beduin sereget," }
	{ key: PHRASE_bedouin_attacks_you_reason_B, text:	  				"a városod sikeresen visszaverte a beduin sereget. Ráadásul" }
	{ key: PHRASE_bedouin_attacks_you_reason_C, text:	  "annak ellenére, hogy a városod sikeresen visszaverte a beduin sereget," }
	{ key: PHRASE_bedouin_attacks_you_no_reason_A, text:  	"gazdagság utáni vágyukat kielégítendő," }
	{ key: PHRASE_bedouin_attacks_you_no_reason_B, text:	  "gondjaink nagyok, mert" }
	{ key: PHRASE_bedouin_attacks_you_no_reason_C, text:	  "" }
	{ key: PHRASE_gift_title_P, text: 				"A fáraó ajándéka" }
	{ key: PHRASE_gift_title_C, text: 				"Egy szomszéd ajándéka" }
	{ key: PHRASE_gift_granted_P, text:				"[greeting] [player_name], [reason_phrase] a fáraó elrendelte, hogy [city_name] városából [amount] [item] ajándékot kapj." }
	{ key: PHRASE_gift_granted_C, text:				"[greeting] [player_name], [reason_phrase] [city_name] városa szeretne neked [amount] [item] ajándékot adományozni." }
	{ key: PHRASE_gift_cash_granted_P, text:			"[greeting] [player_name], [reason_phrase] a fáraó elrendelte, hogy [city_name] városából [amount] deben pénzajándékot kapj." }
	{ key: PHRASE_gift_cash_granted_C, text:			"[greeting] [player_name], [reason_phrase] [city_name] városa [amount] deben ajándékot szeretne neked adni." }
	{ key: PHRASE_gift_partial_space_P, text:			"[greeting] [player_name], [reason_phrase] a fáraó elrendelte, hogy [city_name] városából [amount] [item] ajándékot kapj. Jelenleg nincs elég helyed a raktárudvarokban vagy magtárakban az ajándék teljes befogadására, de legalább a felét el tudod helyezni." }
	{ key: PHRASE_gift_partial_space_C, text:			"[greeting] [player_name], [reason_phrase] [city_name] városa [amount] [item] ajándékot szeretne neked adományozni. Jelenleg nincs elég helyed a raktárudvarokban vagy magtárakban az ajándék teljes befogadására, de legalább a felét el tudod helyezni." }
	{ key: PHRASE_gift_insufficient_space_P, text: 	"[greeting] [player_name], [reason_phrase] a fáraó elrendelte, hogy [city_name] városából [amount] [item] ajándékot kapj, de nincs elég hely a raktárudvarokban és a magtárakban. Szabadíts fel helyet, és a szállítmányt a következő hónapban ismét elhozzák." }
	{ key: PHRASE_gift_insufficient_space_C, text: 	"[greeting] [player_name], [reason_phrase] [city_name] városa [amount] [item] ajándékot szeretne neked adományozni, de nincs elegendő hely a raktárudvarokban és a magtárakban az elhelyezésére. Szabadíts fel helyet, és a szállítmányt a következő hónapban ismét elhozzák." }
	{ key: PHRASE_gift_last_chance_P, text: 			"[greeting] [player_name], a fáraó parancsára [city_name] városa már megpróbált neked [amount] [item] ajándékot adni, de még mindig nincs elegendő helyed a raktárudvarokban és a magtárakban az egész szállítmány elhelyezésére. Túl sokáig várakoztattad a küldötteiket, és türelmetlenné váltak. Fogadd el most ezt a részleges ajándékot, mert többé nem térnek vissza." }
	{ key: PHRASE_gift_last_chance_C, text: 			"[greeting] [player_name], [city_name] városa már megpróbált neked [amount] [item] ajándékot adni, de még mindig nincs elegendő helyed a raktárudvarokban és a magtárakban az egész szállítmány elhelyezésére. Túl sokáig várakoztattad a küldötteiket, és türelmetlenné váltak. Fogadd el most ezt a részleges ajándékot, mert többé nem térnek vissza." }
	{ key: PHRASE_gift_forfeited_P, text: 			"[greeting] [player_name], még mindig nincs elegendő helyed ahhoz, hogy átvedd a [city_name] városából érkező [amount] [item] ajándékot, ezért az elveszett." }
	{ key: PHRASE_gift_forfeited_C, text: 			"[greeting] [player_name], még mindig nincs elegendő helyed ahhoz, hogy átvedd a [city_name] városából érkező [amount] [item] ajándékot, ezért az elveszett." }
	{ key: PHRASE_gift_accepted_P, text: 				"A fáraó parancsára városod raktárudvarait és magtárait annyi [city_name] városából érkező [item] töltötte meg, amennyit csak be tudtak fogadni." }
	{ key: PHRASE_gift_accepted_C, text: 				"Városod raktárudvarait és magtárait annyi [city_name] városából érkező [item] töltötte meg, amennyit csak be tudtak fogadni." }
	{ key: PHRASE_gift_cash_accepted_P, text: 		"A fáraó parancsára [amount_granted] deben került a kincstáradba." }
	{ key: PHRASE_gift_cash_accepted_C, text: 		"[city_name] jóvoltából [amount_granted] deben került a kincstáradba." }
	{ key: PHRASE_gift_postponed_P, text:				"[city_name] küldöttei egy hónap múlva visszatérnek a [item] szállítmányoddal." }
	{ key: PHRASE_gift_postponed_C, text: 			"[city_name] küldöttei egy hónap múlva visszatérnek a [item] szállítmányoddal." }
	{ key: PHRASE_gift_refused_P, text: 				"Bár visszautasítottad a [city_name] városából érkező [item] ajándékot, biztos vagyok benne, hogy más még hasznát veheti a segítségünknek." }
	{ key: PHRASE_gift_refused_C, text: 				"Bár visszautasítottad a [city_name] városából érkező [item] ajándékot, biztos vagyok benne, hogy más még hasznát veheti a segítségünknek." }
	{ key: PHRASE_gift_accepted_reason_P_A, text:  	 		"mivel elfogadtál [amount] [item] ajándékot [city_name] városától" }
	{ key: PHRASE_gift_accepted_reason_P_B, text:	  "a [city_name] városától kapott legutóbbi ajándékod nyomán," }
	{ key: PHRASE_gift_accepted_reason_P_C, text:	  "annak ellenére, hogy elfogadtad a [city_name] városától kapott [amount] [item] ajándékot," }
	{ key: PHRASE_gift_accepted_reason_C_A, text:  	 		"mivel elfogadtál [amount] [item] ajándékot [city_name] városától" }
	{ key: PHRASE_gift_accepted_reason_C_B, text:	  "a [city_name] városától kapott legutóbbi ajándékod nyomán," }
	{ key: PHRASE_gift_accepted_reason_C_C, text:	  "annak ellenére, hogy elfogadtad a [city_name] városától kapott [amount] [item] ajándékot," }
	{ key: PHRASE_gift_forfeited_reason_P_A, text:  	 		"mivel nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_forfeited_reason_P_B, text:	  "nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot. Ráadásul" }
	{ key: PHRASE_gift_forfeited_reason_P_C, text:	  "bár nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_forfeited_reason_C_A, text:  	 		"mivel nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_forfeited_reason_C_B, text:	  "nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot. Ráadásul" }
	{ key: PHRASE_gift_forfeited_reason_C_C, text:	  "annak ellenére, hogy nem fogadtad el a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_refused_reason_P_A, text:  	 		"mivel visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_refused_reason_P_B, text:	  "visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot. Most" }
	{ key: PHRASE_gift_refused_reason_P_C, text:	  "bár visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot," }
	{ key: PHRASE_gift_refused_reason_C_A, text:  	 		"mivel visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot" }
	{ key: PHRASE_gift_refused_reason_C_B, text:	  "visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot. Most" }
	{ key: PHRASE_gift_refused_reason_C_C, text:	  "bár visszautasítottad a [city_name] városától érkező [amount] [item] ajándékot," }
	{ key: PHRASE_gift_no_reason_P_A, text:  					"mivel segítségre lehet szükséged" }
	{ key: PHRASE_gift_no_reason_P_B, text:	  "mivel a fáraó jóindulata határtalan," }
	{ key: PHRASE_gift_no_reason_P_C, text:	  "városod harcokban hozott áldozatait a fáraó nagyra értékeli. Ennek eredményeként" }
	{ key: PHRASE_gift_no_reason_C_A, text:  					"mivel segítségre lehet szükséged" }
	{ key: PHRASE_gift_no_reason_C_B, text:	  "mivel az egyiptomiak mindig segítik honfitársaikat," }
	{ key: PHRASE_gift_no_reason_C_C, text:	  "városod harcokban hozott áldozatait az egyiptomi nép nagyra értékeli. Ennek eredményeként" }
	{ key: PHRASE_pharaoh_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] a fáraó serege megérkezett, hogy erővel foglalja el városodat." }
	{ key: PHRASE_eg_city_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] egy egyiptomi sereg partra szállt, és éppen most támadja a várost!" }
	{ key: PHRASE_foreign_army_attacks_you_disembarked_alert, text:  	"[greeting] [player_name], [reason_phrase] [a_foreign_army] partra szállt, és máris támadja a várost! Adja Seth, hogy megmeneküljünk." }
	{ key: PHRASE_bedouin_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] egy ellenséges beduin megszálló sereg partra szállt partjainkon!" }
	{ key: PHRASE_pyramid_congratulations_title, text:			"Elkészült a piramis!" }
	{ key: PHRASE_pyramid_congratulations, text:					"[greeting] [player_name], ez lenyűgöző teljesítmény! Hónapok megszámlálhatatlan munkája után a piramis végre elkészült!" }
	{ key: PHRASE_stepped_pyramid_congratulations_title, text:	"Lépcsős piramis elkészült!" }
	{ key: PHRASE_stepped_pyramid_congratulations, text:			"[greeting] [player_name], végre elkészült a lépcsős piramis! Ez az emlékmű örökké képességeid bizonyítékaként fog állni." }
	{ key: PHRASE_bent_pyramid_congratulations_title, text:		"Hajlított piramis elkészült!" }
	{ key: PHRASE_bent_pyramid_congratulations, text:				"[greeting] [player_name], a hajlított piramis építése végre befejeződött! Ez városod lenyűgöző teljesítménye." }
	{ key: PHRASE_mudbrick_pyramid_congratulations_title, text:	"Téglapiramis elkészült!" }
	{ key: PHRASE_mudbrick_pyramid_congratulations, text:			"[greeting] [player_name], a kőművesek befejezték a ragyogó, finom mészkőből készült külső burkolat utolsó simításait, és a téglapiramis végre elkészült!" }
	{ key: PHRASE_mastaba_congratulations_title, text:			"Masztaba elkészült!" }
	{ key: PHRASE_mastaba_congratulations, text:					"[greeting] [player_name], az utolsó tégla is a helyére került, és a masztaba építése most befejeződött!" }
	{ key: PHRASE_sphinx_congratulations_title, text:				"Sfinksz elkészült!" }
	{ key: PHRASE_sphinx_congratulations, text:					"[greeting] [player_name], végre a kőművesek befejezték a hatalmas Szfinx kifaragását. Ez az emlékmű az idők végezetéig őrzi majd Egyiptomot." }
	{ key: PHRASE_obelisk_congratulations_title, text:			"Obeliszk elkészült!" }
	{ key: PHRASE_obelisk_congratulations, text:					"[greeting] [player_name], a kőművesek elvégezték az obeliszk utolsó simításait, és végre elkészült." }
	{ key: PHRASE_sun_temple_congratulations_title, text:			"Naptemplom elkészült!" }
	{ key: PHRASE_sun_temple_congratulations, text:				"[greeting] [player_name], sok hónapnyi kemény munka után a Naptemplom építése végre véget ért. Ez városod nagyszerű teljesítménye!" }
	{ key: PHRASE_alex_library_congratulations_title, text:		"Az alexandriai könyvtár elkészült!" }
	{ key: PHRASE_alex_library_congratulations, text:				"[greeting] [player_name], sok kemény munka után Alexandria pompás Nagy Könyvtárának gyönyörű, kézzel készített ajtói készen állnak arra, hogy szélesre táruljanak a világ tudósai előtt." }
	{ key: PHRASE_abu_simbel_congratulations_title, text:			"Abu Szimbel elkészült!" }
	{ key: PHRASE_abu_simbel_congratulations, text:				"[greeting] [player_name], ez valóban lenyűgöző teljesítmény! Képzett munkásaid egy örök emlékművet alkottak, amely fáraónk dicsőségét és Egyiptom hatalmát hirdeti." }
	{ key: PHRASE_caesareum_congratulations_title, text:			"Caesareum elkészült!" }
	{ key: PHRASE_caesareum_congratulations, text:				"[greeting] [player_name], a Caesareum szent temploma és pompás, kertekkel díszített udvarai végre elkészültek! Csodálatos szépségének híre máris terjed az egész vidéken." }
	{ key: PHRASE_lighthouse_congratulations_title, text:			"Pharoszi világítótorony elkészült!" }
	{ key: PHRASE_lighthouse_congratulations, text:    "[greeting] [player_name], sok verejték és nem kevés kiontott vér után a munkások gondosan a helyére tették a csodálatos pharoszi világítótorony utolsó márványtömbjét! Hatalmas, fénylő jelzőtüze már most kereskedőket vonz a világ minden tájáról." }
	{ key: PHRASE_mausoleum_congratulations_title, text:			"Mauzóleum elkészült!" }
	{ key: PHRASE_mausoleum_congratulations, text:				"[greeting] [player_name], a szent mauzóleum végre elkészült! Ez városod figyelemre méltó teljesítménye." }
	{ key: PHRASE_smalltomb_congratulations_title, text:			"Kis temetkezési sír elkészült!" }
	{ key: PHRASE_smalltomb_congratulations, text:				"[greeting] [player_name], a kis királyi temetkezési sír építése befejeződött. Remélhetőleg még sok év telik el, mire munkásaidnak egy újat kell készíteniük." }
	{ key: PHRASE_medtomb_congratulations_title, text:			"Közepes temetkezési sír elkészült!" }
	{ key: PHRASE_medtomb_congratulations, text:				"[greeting] [player_name], végre elkészült a közepes királyi temetkezési sír, és teljesen fel is töltötték ellátmánnyal. Biztosan ideális utat biztosít majd nemrég elhunyt fáraónk számára a túlvilág felé." }
	{ key: PHRASE_largetomb_congratulations_title, text:			"Nagy temetkezési sír elkészült!" }
	{ key: PHRASE_largetomb_congratulations, text:				"[greeting] [player_name], sok évnyi kemény, a föld mélyén végzett munka után munkásaid elkészítették minden eddiginél pompásabb temetkezési sírunkat! Ez valóban csodálatos teljesítmény." }
	{ key: PHRASE_grandtomb_congratulations_title, text:			"Nagyszabású temetkezési sír elkészült!" }
	{ key: PHRASE_grandtomb_congratulations, text:				"[greeting] [player_name], sok megerőltető munka után elkészült a hatalmas királyi temetkezési sír – éppen időben, hiszen egyes hírek szerint nagyra becsült fáraónk már utolsó napjait éli. Ez a pompás sír tökéletes hely lesz közelgő túlvilági utazásának folytatásához." }
	{ key: PHRASE_troopcarryover_title, text:   "Hűséges katonák csatlakoznak újra" }
	{ key: PHRASE_troopcarryover_initial_announcement, text: "Az előző küldetésből származó legjobb katonáid szeretnének ismét csatlakozni hozzád. Építs [reason_phrase] ezeknek a harcosoknak, és visszatérnek." }
	{ key: PHRASE_troopcarryover_inf_only, text: "egy gyalogos erődöt" }
	{ key: PHRASE_troopcarryover_arch_only, text: "egy íjász erődöt" }
	{ key: PHRASE_troopcarryover_char_only, text: "egy harci szekér erődöt" }
	{ key: PHRASE_troopcarryover_inf_arch, text: "gyalogos- és íjász erődöket" }
	{ key: PHRASE_troopcarryover_inf_char, text: "gyalogos- és harci szekér erődöket" }
	{ key: PHRASE_troopcarryover_arch_char, text: "íjász- és harci szekér erődöket" }
	{ key: PHRASE_troopcarryover_all_three, text: "gyalogos-, íjász- és harci szekér erődöket" }
	{ key: PHRASE_pyramid_speedup_title, text: "Építési áldás" }
	{ key: PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] elégedett odaadásoddal, és jelentős segítséget kíván nyújtani emlékműépítési projektedhez. Eljött az idő, hogy munkásaid ideiglenesen félreálljanak, amíg a tisztelt [reason_phrase] bőséges áldása megérkezik." }
	{ key: PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] elismeri hódolatodat, és segíti emlékműépítési projektedet. Eljött az idő, hogy munkásaid rövid pihenőt tartsanak, amíg [reason_phrase] jóindulatú ajándéka megérkezik." }
	{ key: PHRASE_pyramid_speedup_Osiris, text: "Ozirisz" }
	{ key: PHRASE_pyramid_speedup_Ra, text: "Ré" }
	{ key: PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
	{ key: PHRASE_pyramid_speedup_Seth, text: "Seth" }
	{ key: PHRASE_pyramid_speedup_Bast, text: "Bastet" }
]