log_info("akhenaten: eventmsg enlish started")

eventmsg_sp = [
  { key:PHRASE_egyptian_city_attacked_title_P, text: "Ciudad egipcia bajo ataque" }
  { key:PHRASE_egyptian_city_attacked_title_C, text: "Ciudad egipcia bajo ataque" }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: 	"[greeting] [player_name],[reason_phrase] los infieles están atacando. El todopoderoso Faraón te ordena enviar tropas a la ciudad egipcia de [city_name] para combatir al enemigo.  Debes despachar tropas en un plazo de [travel_time] meses." }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: 	"[greeting] [player_name], [reason_phrase] [city_name], una ciudad egipcia, está bajo ataque y necesita tu ayuda. Debes despachar tropas en un plazo de [travel_time] meses." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_P, text: 	"[greeting] [player_name], el divino Faraón sigue combatiendo a los agresores en [city_name].  Despacha refuerzos en los próximos seis meses, o arriesgas incurrir en la ira del Faraón." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_C, text: 	"[greeting] [player_name], ¿has olvidado [city_name]? Envía tropas dentro de los próximos seis meses, o las consecuencias podrían ser terribles." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_P, text: 	"[greeting] [player_name], el Faraón se impacienta esperando a tus tropas.  Envía tropas a [city_name] pronto, o será demasiado tarde." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_C, text: 	"[greeting] [player_name], [city_name] podría pronto caer ante sus enemigos.  Envía tropas rápidamente si quieres ayudar a [city_name] en su hora de necesidad." }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "porque tus tropas derrotaron a los enemigos del Faraón en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "tus tropas derrotaron a los enemigos del Faraón en [city_name].  Por cierto," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "aunque tus tropas derrotaron a los enemigos del Faraón en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "porque tus tropas eliminaron con eficacia al enemigo en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "tus tropas eliminaron con eficacia al enemigo en [city_name].  Además," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "aunque tus tropas eliminaron con eficacia al enemigo en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "porque tardaste demasiado en enviar tus tropas a ayudar al ejército del Faraón a combatir al enemigo en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "el ejército del Faraón perdió la batalla en [city_name], porque tus tropas llegaron demasiado tarde,.  Además," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "tus tropas llegaron demasiado tarde para ayudar al ejército del Faraón a combatir al enemigo en [city_name], pero tu esfuerzo fue muy apreciado.  Como resultado" }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "porque esperaste demasiado para enviar tus tropas a defender [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "tus tropas no llegaron a tiempo para ayudar a defender [city_name].  Además," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "tus tropas llegaron demasiado tarde para ayudar a [city_name], pero como hiciste el esfuerzo y estabas dispuesto a sacrificar a tus propios soldados," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "porque negaste al Faraón las tropas que necesitaba para luchar contra el enemigo en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "el Faraón se ha enterado de que te negaste a enviar las tropas que necesitaba para luchar contra el enemigo en [city_name].  Además," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "aunque negaste al Faraón las tropas que necesitaba para luchar contra el enemigo en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "porque te negaste a enviar las tropas solicitadas para derrotar a los saqueadores en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: 	"[city_name] se lamenta de que te hayas negado a enviar las tropas solicitadas para derrotar a sus enemigos.  Además," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "aunque te negaste a enviar las tropas solicitadas para derrotar a los saqueadores en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "porque las tropas que enviaste al Faraón en [city_name] eran demasiado débiles para derrotar al enemigo," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "las débiles tropas que enviaste para ayudar al Faraón fueron derrotadas en [city_name].  Además," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "a pesar de que tus tropas eran demasiado débiles para ayudar al Faraón en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "porque las tropas que enviaste a [city_name] no eran lo bastante poderosas para derrotar a los atacantes," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "tus débiles fuerzas fueron derrotadas en [city_name].  Además," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "aunque tus tropas no resultaron victoriosas en [city_name]," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "para satisfacer su afán de más tierras," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "tus problemas aún no han terminado, pues" }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: 	"" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "en persecución de una enemistad de larga data," }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "tus problemas aún no han terminado, pues" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: 	"" }

  { key: PHRASE_distant_battle_title_P, text: "Batalla lejana" }
  { key: PHRASE_distant_battle_title_C, text: "Batalla lejana" }
  { key: PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] el ejército egipcio está inmerso en una feroz batalla. El imperioso Faraón exige que envíes tropas a la lejana ciudad de [city_name] para entrar en la contienda. Despacha tropas en un plazo de [travel_time] meses." }
  { key: PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] el ejército egipcio está librando combate en la lejana ciudad de [city_name], y necesita que despaches refuerzos allí.  Envía tropas en su ayuda en un plazo de [travel_time] meses." }
  { key: PHRASE_distant_battle_first_reminder_P, text: 	"[greeting] [player_name], la sangrienta batalla continúa en [city_name], y el Faraón sigue necesitando tus tropas. Despáchalas en los próximos seis meses si quieren llegar a tiempo. No hacerlo podría salir caro. " }
  { key: PHRASE_distant_battle_first_reminder_C, text: 	"[greeting] [player_name], la batalla por [city_name] sigue en curso. Despacha tropas en los próximos seis meses si quieren llegar a tiempo.  Esta podría ser tu oportunidad de compartir una gloriosa victoria." }
  { key: PHRASE_distant_battle_last_reminder_P, text: 	"[greeting] [player_name], el ejército egipcio sigue librando la guerra en [city_name], y el noble Faraón exige que envíes refuerzos muy pronto. No enfades al Faraón mientras está con ganas de luchar." }
  { key: PHRASE_distant_battle_last_reminder_C, text: 	"[greeting] [player_name], la batalla por [city_name] continúa. Si envías tropas en su ayuda muy pronto, Egipto aún podría lograr una gloriosa victoria." }
  { key: PHRASE_distant_battle_comply_reason_P_A, text: "porque la victoria del Faraón en [city_name] dependió de tus tropas," }
  { key: PHRASE_distant_battle_comply_reason_P_B, text: "tus tropas ayudaron al Faraón a lograr la victoria en [city_name].  Ah, y una cosa más," }
  { key: PHRASE_distant_battle_comply_reason_P_C, text: "aunque tus tropas ayudaron al Faraón a lograr la victoria en [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_A, text: "porque tus tropas ayudaron a ganar la jornada en [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_B, text: "tus tropas resultaron vitales para ganar la jornada en [city_name].  Además," }
  { key: PHRASE_distant_battle_comply_reason_C_C, text: "aunque tus tropas resultaron vitales para ganar la jornada en [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_A, text: "porque tus tropas no llegaron a tiempo para ayudar al Faraón en [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_B, text: "tus tropas no llegaron a tiempo para ayudar al Faraón en [city_name].  Además," }
  { key: PHRASE_distant_battle_too_late_reason_P_C, text: "aunque tus tropas llegaron demasiado tarde para ayudar al Faraón en [city_name], tu disposición a hacer sacrificios por el reino es muy apreciada.  Como resultado," }
  { key: PHRASE_distant_battle_too_late_reason_C_A, text: "porque tus tropas llegaron demasiado tarde para participar en la batalla de [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_C_B, text: "tus tropas llegaron demasiado tarde para participar en la batalla de [city_name].  Además," }
  { key: PHRASE_distant_battle_too_late_reason_C_C, text: "aunque tus tropas llegaron demasiado tarde para participar en la batalla de [city_name], tu disposición a hacer sacrificios por el reino es muy apreciada.  Como resultado," }
  { key: PHRASE_distant_battle_refuse_reason_P_A, text: "porque desobedeciste descaradamente la petición del Faraón de enviar tropas para ayudar a su ejército en [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_P_B, text: "desobedeciste descaradamente la petición del Faraón de enviar tropas para ayudar a su ejército en [city_name].  Fue una imprudencia, pero en cualquier caso," }
  { key: PHRASE_distant_battle_refuse_reason_P_C, text: "aunque desobedeciste la petición del Faraón de tropas para ayudar a su ejército en [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_C_A, text: "porque te negaste a enviar las tropas necesarias a la batalla en [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_C_B, text: "te negaste a enviar las tropas necesarias a la batalla en [city_name], lo cual fue desafortunado para ellos.  Por cierto," }
  { key: PHRASE_distant_battle_refuse_reason_C_C, text: "aunque te negaste a enviar las tropas necesarias a la batalla en [city_name]," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_A, text: "porque las tropas que enviaste a [city_name] eran demasiado débiles para combatir al adversario del Faraón," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_B, text: "las tropas que enviaste a [city_name] fueron derrotadas por el enemigo del Faraón.  Además," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_C, text: "aunque las tropas que enviaste a [city_name] fueron derrotadas por el enemigo del Faraón," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_A, text: "porque las tropas que enviaste a [city_name] carecían de fuerza y vigor para vencer al enemigo," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_B, text: "las tropas que enviaste a [city_name] carecían de fuerza y vigor para derrotar a nuestro enemigo.  Ten también en cuenta que" }
  { key: PHRASE_distant_battle_lost_battle_reason_C_C, text: "aunque las tropas que enviaste a [city_name] no lograron derrotar al enemigo," }
  { key: PHRASE_distant_battle_no_reason_P_A, text: "atiende al grito de batalla, pues"			 }
  { key: PHRASE_distant_battle_no_reason_P_B, text: "nuestros problemas continúan" }
  { key: PHRASE_distant_battle_no_reason_P_C, text: 	"" }
  { key: PHRASE_distant_battle_no_reason_C_A, text: "alerta a tus soldados, pues" }
  { key: PHRASE_distant_battle_no_reason_C_B, text: "los problemas no han terminado, pues" }
  { key: PHRASE_distant_battle_no_reason_C_C, text: 	"" }

  { key:PHRASE_general_request_title_P, text:"El Faraón solicita bienes" }
  { key:PHRASE_general_request_title_C, text:"Una ciudad solicita bienes" }
  { key:PHRASE_general_request_initial_announcement_P,text:	"[greeting] [player_name], [reason_phrase] incomparable Faraón desea que envíes [amount] [item] a [city_name] en un plazo de [time_allotted] meses. Cumplir la petición podría granjearte la estima del Faraón." }
  { key:PHRASE_general_request_initial_announcement_C,text:	"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] solicita que envíes [amount] [item] en [time_allotted] meses. Ayudar a [city_name] podría traernos beneficios más adelante." }
  { key:PHRASE_general_request_reminder_P, text:	"[greeting] [player_name], el Faraón se pregunta por qué [city_name] no ha recibido [amount] [item].  Te quedan 6 meses para cumplir la petición del Faraón." }
  { key:PHRASE_general_request_reminder_C, text:	"[greeting] [player_name], [city_name] aguarda con impaciencia la llegada de [amount] [item].  Te quedan 6 meses para cumplir." }
  { key:PHRASE_general_request_overdue_P, text:	"[greeting] [player_name], ¿quieres provocar al Faraón? No enviaste [amount] [item] a [city_name] a tiempo. Incluso un intento tardío de cumplir esta petición podría apaciguar algo al Faraón." }
  { key:PHRASE_general_request_overdue_C, text:	"[greeting] [player_name], se te ha acabado el tiempo y aún no has enviado a [city_name] los [amount] [item] que solicitaron. Incluso un intento tardío de cumplir esta petición podría satisfacer algo a [city_name]." }
  { key:PHRASE_general_request_warning_P, text:	"[greeting] [player_name], solo te quedan seis meses para cumplir la petición del Faraón de enviar [amount] [item] a [city_name]. Negársela es jugar con fuego." }
  { key:PHRASE_general_request_warning_C, text:	"[greeting] [player_name], envía a [city_name] [amount] [item] en un plazo de seis meses, o arriesgas convertir a tus vecinos en enemigos." }
  { key:PHRASE_general_request_comply_reason_P_A, text:"porque cumpliste la petición del Faraón de enviar [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_comply_reason_P_B, text:"cumpliste la petición del Faraón de enviar [amount] [item] a [city_name].  Por cierto," }
  { key:PHRASE_general_request_comply_reason_P_C, text:"sí cumpliste la petición del Faraón de enviar [amount] [item] a [city_name], sin embargo," }
  { key:PHRASE_general_request_comply_reason_C_A, text:"porque has enviado [amount] [item] a [city_name], tal como lo solicitaron," }
  { key:PHRASE_general_request_comply_reason_C_B, text:	"[city_name] recibió los [amount] [item] tal como los solicitaron.  También debes saber que" }
  { key:PHRASE_general_request_comply_reason_C_C, text:"aunque enviaste [amount] [item] a [city_name], tal como lo solicitaron," }
  { key:PHRASE_general_request_too_late_reason_P_A, text:"porque retrasaste el cumplimiento de la petición del Faraón de [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_P_B, text:"la petición del Faraón de [amount] [item] no se cumplió porque llegaste tarde.  Además," }
  { key:PHRASE_general_request_too_late_reason_P_C, text:"retrasaste el cumplimiento de la petición del Faraón de [amount] [item], pero aun así tu esfuerzo fue apreciado.  Como resultado," }
  { key:PHRASE_general_request_too_late_reason_C_A, text:"porque te retrasaste en cumplir la petición de [city_name] de [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_C_B, text:"te retrasaste en entregar [amount] [item] a [city_name].  También debes tener en cuenta que" }
  { key:PHRASE_general_request_too_late_reason_C_C, text:"a pesar de que te retrasaste en entregar [amount] [item] a [city_name], tu esfuerzo fue apreciado.  Como resultado," }
  { key:PHRASE_general_request_refuse_reason_P_A, text:"porque ignoraste la petición del Faraón de [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_P_B, text:"ignoraste la petición del Faraón de [amount] [item], y no se sentirá complacido.  Además," }
  { key:PHRASE_general_request_refuse_reason_P_C, text:"aunque ignoraste la petición del Faraón de [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_C_A, text:"porque no enviaste [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_refuse_reason_C_B, text:"no enviaste [amount] [item] a [city_name], y no lo aprecian.  Mientras tanto," }
  { key:PHRASE_general_request_refuse_reason_C_C, text:"a pesar de que no enviaste [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_no_reason_P_A, text:"para complementar las reservas de su hacienda," 			 }
  { key:PHRASE_general_request_no_reason_P_B, text:"no parece haber fin a la codicia del Faraón, pues" }
  { key:PHRASE_general_request_no_reason_P_C, text:	"" }
  { key:PHRASE_general_request_no_reason_C_A, text:"para satisfacer las necesidades de los ciudadanos," }
  { key:PHRASE_general_request_no_reason_C_B, text:"no parece haber fin a esto, pues" }
  { key:PHRASE_general_request_no_reason_C_C, text:	"" }

  { key: PHRASE_great_festival_title_P, text: "Festival a [god]" }
  { key: PHRASE_great_festival_title_C, text: "Gran Festival a [god]" }
  { key: PHRASE_great_festival_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] el Faraón planea un Gran Festival en honor a [god] en [city_name] y necesita bienes de tu ciudad. Tienes [time_allotted] meses para enviar [amount] [item]." }
  { key: PHRASE_great_festival_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] solicita que envíes [amount] [item] para un Gran Festival en honor a [god]. La ciudad necesita estos bienes en un plazo de [time_allotted] meses." }
  { key: PHRASE_great_festival_reminder_P, text: "[greeting] [player_name], te quedan seis meses para enviar [amount] [item] a [city_name] para el Gran Festival en honor a [god]. El Faraón se disgustará si no cumples su petición." }
  { key: PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], se acerca el Gran Festival en honor a [god] en [city_name] y aún no has enviado los [amount] [item]. Te quedan 6 meses para enviar los bienes." }
  { key: PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], has perdido el plazo, y el Faraón tuvo que celebrar el Gran Festival en honor a [god] sin tus suministros. Envía de todos modos [amount] [item] a [city_name], y es posible que el enfurecido Faraón aún encuentre cierta clemencia." }
  { key: PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] está disgustada por tener que conseguir bienes en otra parte para su Gran Festival en honor a [god]. Podrías ganar algo de aceptación si aún intentas enviar los [amount] [item]." }
  { key: PHRASE_great_festival_warning_P, text: "[greeting] [player_name], solo te quedan 6 meses para enviar al Faraón [amount] [item] a [city_name], que necesitaba para el Gran Festival en honor a [god]. ¡Ay de quien sienta el ardor de la ira del Faraón!" }
  { key: PHRASE_great_festival_warning_C, text: "[greeting] [player_name], [city_name] está frustrada contigo. Envía [amount] [item] en los próximos 6 meses si quieres tener alguna esperanza de mantener buenas relaciones." }
  { key: PHRASE_great_festival_comply_reason_P_A, text: "porque honraste al Faraón y a [god] enviando [amount] [item] a [city_name] a tiempo para el Gran Festival," }
  { key: PHRASE_great_festival_comply_reason_P_B, text: "honraste generosamente al Faraón y a [god] enviando [amount] [item] a [city_name] a tiempo para el Gran Festival.  Además," }
  { key: PHRASE_great_festival_comply_reason_P_C, text: "aunque honraste generosamente al Faraón y a [god] enviando [amount] [item] a [city_name] a tiempo para el Gran Festival," }
  { key: PHRASE_great_festival_comply_reason_C_A, text: "porque ayudaste a [city_name] a celebrar su Gran Festival en honor a [god] enviando [amount] [item]," }
  { key: PHRASE_great_festival_comply_reason_C_B, text: "ayudaste a [city_name] a celebrar su Gran Festival en honor a [god] enviando [amount] [item], lo que se agradeció mucho.  Además," }
  { key: PHRASE_great_festival_comply_reason_C_C, text: "aunque ayudaste a [city_name] a celebrar su Gran Festival en honor a [god] enviando [amount] [item]," }
  { key: PHRASE_great_festival_too_late_reason_P_A, text: "porque enviaste [amount] [item] demasiado tarde para el Gran Festival del Faraón en honor a [god] en [city_name]," }
  { key: PHRASE_great_festival_too_late_reason_P_B, text: "enviaste [amount] [item] demasiado tarde para el Gran Festival del Faraón en honor a [god] en [city_name].  Además," }
  { key: PHRASE_great_festival_too_late_reason_P_C, text: "aunque los [amount] [item] llegaron demasiado tarde para el Gran Festival del Faraón en honor a [god] en [city_name], como hiciste el esfuerzo," }
  { key: PHRASE_great_festival_too_late_reason_C_A, text: "porque los [amount] [item] que exigía [city_name] para el Gran Festival en honor a [god] no llegaron a tiempo," }
  { key: PHRASE_great_festival_too_late_reason_C_B, text: "los [amount] [item] que exigía [city_name] para el Gran Festival en honor a [god] no llegaron a tiempo.  Además," }
  { key: PHRASE_great_festival_too_late_reason_C_C, text: "aunque los [amount] [item] que enviaste a [city_name] no llegaron a tiempo para el Gran Festival en honor a [god], como hiciste lo posible," }
  { key: PHRASE_great_festival_refuse_reason_P_A, text: "porque descuidaste cumplir la petición del Faraón de [amount] [item] para el Gran Festival en honor a [god] en [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_P_B, text: "descuidaste cumplir la petición del Faraón de [amount] [item] para el Gran Festival en honor a [god] en [city_name].  Además," }
  { key: PHRASE_great_festival_refuse_reason_P_C, text: "a pesar de tu incumplimiento de la petición del Faraón de [amount] [item] para el Gran Festival en honor a [god] en [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_C_A, text: "porque desatendiste a [city_name] y su petición de [amount] [item] para el Gran Festival en honor a [god]," }
  { key: PHRASE_great_festival_refuse_reason_C_B, text: "desatendiste a [city_name] y su petición de [amount] [item] para el Gran Festival en honor a [god].  Además," }
  { key: PHRASE_great_festival_refuse_reason_C_C, text: "aunque desatendiste a [city_name] y su petición de [amount] [item] para el Gran Festival en honor a [god]," }
  { key: PHRASE_great_festival_no_reason_P_A, text: "porque el Faraón busca honrar a la deidad," }
  { key: PHRASE_great_festival_no_reason_P_B, text: "porque [god] sigue descontenta," }
  { key: PHRASE_great_festival_no_reason_P_C, text:  "" }
  { key: PHRASE_great_festival_no_reason_C_A, text: "porque [city_name] está bendecida por [god]," }
  { key: PHRASE_great_festival_no_reason_C_B, text: "porque [god] sigue descontenta," }
  { key: PHRASE_great_festival_no_reason_C_C, text:  "" }

  { key: PHRASE_project_title_P, text: 						"Construcción para el Faraón" }
  { key: PHRASE_project_title_C, text: 						"Proyecto de construcción" }
  { key: PHRASE_project_initial_announcement_P, text:		"[greeting] [player_name], [reason_phrase] el Faraón está levantando algo tan colosal que necesita que envíes [amount] [item] a [city_name] en un plazo de [time_allotted] meses. Sea cual sea el proyecto, sin duda sumará gloria a Egipto." }
  { key: PHRASE_project_initial_announcement_C, text:		"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] solicita que envíes [amount] [item] en un plazo de [time_allotted] meses para un importante proyecto de construcción en la ciudad." }
  { key: PHRASE_project_reminder_P, text: 					"[greeting] [player_name], el Faraón está a punto de enfurecerse. Aún no has enviado los [amount] [item] a [city_name] para su proyecto de construcción. Tienes 6 meses para cumplir la petición del Faraón." }
  { key: PHRASE_project_reminder_C, text: 					"[greeting] [player_name], [city_name] necesita [amount] [item] para completar su proyecto de construcción. Envíe los suministros en un plazo de 6 meses, o los líderes de la ciudad podrían perder la paciencia." }
  { key: PHRASE_project_overdue_P, text: 					"[greeting] [player_name], el Faraón está indignado por su insolencia. No envió [amount] [item] a [city_name] a tiempo para que él completara su proyecto de construcción. Si todavía logra enviarlos, quizá pueda salvar las apariencias." }
  { key: PHRASE_project_overdue_C, text: 					"[greeting] [player_name], [city_name] está considerando informar al Faraón sobre usted. Como no envió [amount] [item] a tiempo, es posible que la ciudad no pueda completar su proyecto de construcción. Si los envía de todos modos, [city_name] quizá todavía pueda terminar este proyecto y tal vez guarde silencio sobre su inacción." }
  { key: PHRASE_project_warning_P, text: 					"[greeting] [player_name], un proyecto inacabado solo avergonzará al Faraón. Le quedan 6 meses para enviar [amount] [item] a [city_name] para su proyecto de construcción. Si le falla, el Faraón compartirá su vergüenza con usted." }
  { key: PHRASE_project_warning_C, text: 					"[greeting] [player_name], solo le quedan 6 meses para enviar [amount] [item] a [city_name] para su proyecto de construcción. Si no envía los bienes, nadie sabe lo que la ciudad podría hacer como represalia." }
  { key: PHRASE_project_comply_reason_P_A, text:  	  		"porque los [amount] [item] que envió fueron esenciales para terminar a tiempo el proyecto de construcción del Faraón en [city_name]," }
  { key: PHRASE_project_comply_reason_P_B, text:	  		"los [amount] [item] que envió fueron esenciales para terminar a tiempo el proyecto de construcción del Faraón en [city_name].  Además," }
  { key: PHRASE_project_comply_reason_P_C, text:	  		"aunque los [amount] [item] que envió fueron esenciales para terminar a tiempo el proyecto de construcción del Faraón en [city_name]," }
  { key: PHRASE_project_comply_reason_C_A, text:  	  			"porque ayudó a [city_name] a completar con éxito su proyecto en plazo al enviar [amount] [item]," }
  { key: PHRASE_project_comply_reason_C_B, text:	  "ayudó a [city_name] a mantener su proyecto en plazo al enviar [amount] [item].  Por cierto," }
  { key: PHRASE_project_comply_reason_C_C, text:	  "aunque ayudó a [city_name] a completar con éxito su proyecto en plazo al enviar [amount] [item]," }
  { key: PHRASE_project_too_late_reason_P_A, text:   "porque retrasó el proyecto de construcción del Faraón en [city_name] al esperar demasiado para enviar [amount] [item]," }
  { key: PHRASE_project_too_late_reason_P_B, text:	  "el proyecto de construcción del Faraón en [city_name] se ha estancado porque esperó demasiado para enviar los [amount] [item] que pidió.  Además," }
  { key: PHRASE_project_too_late_reason_P_C, text:	  "a pesar de que retrasó el proyecto de construcción del Faraón en [city_name] al esperar demasiado para enviar [amount] [item], su esfuerzo fue apreciado, y por ello" }
  { key: PHRASE_project_too_late_reason_C_A, text:  	"porque dilató el envío de [amount] [item] a [city_name]," }
  { key: PHRASE_project_too_late_reason_C_B, text:	  "dilató el envío a [city_name] de los [amount] [item] que necesitaban.  Por cierto," }
  { key: PHRASE_project_too_late_reason_C_C, text:	  "aunque dilató el envío a [city_name] de los [amount] [item] que necesitaban, su esfuerzo fue apreciado, y por ello" }
  { key: PHRASE_project_refuse_reason_P_A, text:	"porque rechazó la petición del Faraón de [amount] [item] para su importante proyecto en {city_name]," }
  { key: PHRASE_project_refuse_reason_P_B, text:	  "rechazó de forma imprudente la petición del Faraón de [amount] [item] para su importante proyecto en {city_name].  Además," }
  { key: PHRASE_project_refuse_reason_P_C, text:	  "aunque fue imprudente rechazar la petición del Faraón de [amount] [item] para su importante proyecto en {city_name] como lo hizo," }
  { key: PHRASE_project_refuse_reason_C_A, text: 	"porque desdeñó a [city_name] y su petición de [amount] [item]," }
  { key: PHRASE_project_refuse_reason_C_B, text:	  "ha desdeñado a [city_name] y su petición de [amount] [item].  Además," }
  { key: PHRASE_project_refuse_reason_C_C, text:	  "aunque desdeñó a [city_name] y su petición de [amount] [item]," }
  { key: PHRASE_project_no_reason_P_A, text:  	 	"para celebrar sus muchos logros," }
  { key: PHRASE_project_no_reason_P_B, text:	  "porque aún queda mucho trabajo por hacer" }
  { key: PHRASE_project_no_reason_P_C, text:	  "" }
  { key: PHRASE_project_no_reason_C_A, text:  	  "para honrar la gloria de Egipto," }
  { key: PHRASE_project_no_reason_C_B, text:	  "porque aún queda mucho por hacer" }
  { key: PHRASE_project_no_reason_C_C, text:	  "" }

  { key:PHRASE_famine_title_P, text: 					"Hambruna" }
  { key:PHRASE_famine_title_C, text: 					"Hambruna" }
  { key:PHRASE_famine_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] una hambruna azota [city_name]. El Faraón le exige que socorra a su pueblo. Tiene [time_allotted] para enviar [amount] [item] a la ciudad y aliviar su sufrimiento." }
  { key:PHRASE_famine_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] una hambruna ha golpeado [city_name], y su pueblo se está muriendo de hambre. Envíe [amount] [item] en un plazo de [time_allotted] meses. ¡Hay vidas en juego!" }
  { key:PHRASE_famine_reminder_P, text: 				"[greeting] [player_name], el Faraón se pregunta si usted tiene corazón.  Todavía no ha enviado los [amount] [item] a [city_name], y su pueblo está necesitado. Solo le quedan 6 meses para cumplir la petición del Faraón." }
  { key:PHRASE_famine_reminder_C, text: 				"[greeting] [player_name], el pueblo de [city_name] se lamenta de hambre, y usted todavía no ha enviado los [amount] [item]. Envíe los suministros en un plazo de 6 meses, o los lamentos de hambre se convertirán en lamentos por los muertos." }
  { key:PHRASE_famine_overdue_P, text: 				"[greeting] [player_name], el Faraón lo considera tan cruel como un áspid. No ha hecho nada para aliviar el hambre de sus compatriotas. Todavía puede enviar [amount] [item] a [city_name] y tener la oportunidad de recuperar su imagen a los ojos del Faraón." }
  { key:PHRASE_famine_overdue_C, text: 				"[greeting] [player_name], los lastimeros gritos de hambre aparentemente han caído en oídos sordos. No envió los [amount] [item] a [city_name] a tiempo. Más vale tarde que nunca... si envía el alimento de todos modos, quizá todavía proporcione algo de alivio, si queda alguien que pueda beneficiarse de él." }
  { key:PHRASE_famine_warning_P, text: 				"[greeting] [player_name], si no envía [amount] [item] a [city_name] en un plazo de 6 meses, no servirá de nada. El Faraón desaprobará su crueldad si descuida enviar los bienes." }
  { key:PHRASE_famine_warning_C, text: 				"[greeting] [player_name], el pueblo de [city_name] se pregunta si su corazón es cruel.  Solo le quedan 6 meses para enviar [amount] [item] y aliviar su sufrimiento. Si se los niega, sus muertes recaerán sobre usted." }
  { key:PHRASE_famine_comply_reason_P_A, text:  			"porque envió rápidamente [amount] [item] para atender las necesidades de [city_name], como ordenó el Faraón," }
  { key:PHRASE_famine_comply_reason_P_B, text:	  		"envió rápidamente [amount] [item] para atender las necesidades de [city_name], como ordenó el Faraón.  Esto fue sensato.  Ahora," }
  { key:PHRASE_famine_comply_reason_P_C, text:	  "aunque fue diligente al enviar los [amount] [item] para atender las necesidades de [city_name], como ordenó el Faraón, aun así" }
  { key:PHRASE_famine_comply_reason_C_A, text: 	"porque los [amount] [item] que envió llenaron los estómagos de [city_name] durante la hambruna," }
  { key:PHRASE_famine_comply_reason_C_B, text:	  "los [amount] [item] que envió a [city_name] llenaron los estómagos de su pueblo durante la hambruna.  Además, los visires informan de que" }
  { key:PHRASE_famine_comply_reason_C_C, text:	  "aunque los [amount] [item] que envió al pueblo de [city_name] les ayudaron a sobrellevar la reciente hambruna, aun así" }
  { key:PHRASE_famine_too_late_reason_P_A, text:	"porque permitió que el pueblo del Faraón en [city_name] sufriera demasiado al esperar para enviar [amount] [item]," }
  { key:PHRASE_famine_too_late_reason_P_B, text:	  "permitió que el pueblo del Faraón en [city_name] sufriera demasiado al esperar para enviar los [amount] [item] que necesitaba.  Además, los visires informan de que" }
  { key:PHRASE_famine_too_late_reason_P_C, text:	  "aunque permitió que el pueblo del Faraón en [city_name] sufriera demasiado al esperar para enviar los [amount] [item] que necesitaba, sirvieron de cierta ayuda, y por ello" }
  { key:PHRASE_famine_too_late_reason_C_A, text:  	 	"porque tardó demasiado en despachar [amount] [item] para aliviar al pueblo de [city_name]," }
  { key:PHRASE_famine_too_late_reason_C_B, text:	  "tardó muchísimo en despachar [amount] [item] para aliviar al pueblo de [city_name], y su sufrimiento fue enorme.  Por encima de eso," }
  { key:PHRASE_famine_too_late_reason_C_C, text:	  "aunque tardó demasiado en despachar [amount] [item] al pueblo de [city_name], el alimento ayudó algo a paliar las secuelas de la hambruna, y por ello" }
  { key:PHRASE_famine_refuse_reason_P_A, text:  	 	"porque desdeñó al Faraón y a su pueblo en [city_name] durante la hambruna al negarse a enviar [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_P_B, text:	  "desdeñó al Faraón y a su pueblo en [city_name] durante la hambruna al negarse a enviar [amount] [item].  Esto fue imprudente.  Además, los visires informan de que" }
  { key:PHRASE_famine_refuse_reason_P_C, text:	  "desdeñó al Faraón y a su pueblo en [city_name], durante la hambruna, al negarse a enviar [amount] [item], pero a pesar de ello" }
  { key:PHRASE_famine_refuse_reason_C_A, text:			"porque le dio la espalda al pueblo de [city_name] durante la hambruna y retuvo [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_C_B, text:	  "le dio la espalda al pueblo de [city_name] durante la hambruna y retuvo [amount] [item].  Los visires también informan de que" }
  { key:PHRASE_famine_refuse_reason_C_C, text:	  "aunque le dio la espalda al pueblo de [city_name] durante la hambruna y retuvo [amount] [item]," }
  { key:PHRASE_famine_no_reason_P_A, text:  	 	"La fortuna se muestra adversa con el pueblo del Faraón, y" }
  { key:PHRASE_famine_no_reason_P_B, text:	  "las desgracias siguen aumentando, como" }
  { key:PHRASE_famine_no_reason_P_C, text:	  "" }
  { key:PHRASE_famine_no_reason_C_A, text:  	"el pueblo de [city_name] está perdiendo la esperanza, pues" }
  { key:PHRASE_famine_no_reason_C_B, text:	  "las desgracias siguen aumentando, como" }
  { key:PHRASE_famine_no_reason_C_C, text:	  "" }

  { key:PHRASE_threat_title_P, text: 					"Extorsión por parte del Faraón" }
  { key:PHRASE_threat_title_C, text: 					"Extorsión por parte de otra ciudad" }
  { key:PHRASE_threat_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] el Faraón le ordena enviar [amount] [item] a [city_name] en [time_allotted] meses. De lo contrario, atacará su digna ciudad." }
  { key:PHRASE_threat_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] exige que envíe [amount] [item] en [time_allotted] meses. Si rechaza la petición, [city_name] enviará sus ejércitos contra su digna ciudad." }
  { key:PHRASE_threat_reminder_P, text: 				"[greeting] [player_name], el orgulloso Faraón está reuniendo a sus tropas y pronto les ordenará atacar. Debería enviar los [amount] [item] a [city_name] en un plazo de 6 meses para evitar los disgustos." }
  { key:PHRASE_threat_reminder_C, text: 				"[greeting] [player_name], el ejército de [city_name] se prepara para la guerra, deseoso de una buena batalla. Si envía los [amount] [item] en un plazo de 6 meses, la ciudad cesará su agresión. Sus soldados, eso sí, se llevarán una gran decepción." }
  { key:PHRASE_threat_overdue_P, text: 				"[greeting] [player_name], se le ha acabado el tiempo, y el Faraón ansía sangre. Quizá todavía tenga la oportunidad de contener a sus fuerzas si envía los [amount] [item] a [city_name] lo antes posible." }
  { key:PHRASE_threat_overdue_C, text: 				"[greeting] [player_name], se oyen gritos de guerra por toda [city_name] mientras se prepara para destruir su ciudad. Envíe los [amount] [item] a [city_name] lo antes posible, y quizá muestren cierta clemencia." }
  { key:PHRASE_threat_warning_P, text: 				"[greeting] [player_name], el vanaglorioso Faraón está deseoso de tomar por la fuerza lo que usted no le entregaría de buen grado. Su ejército está bien preparado, pero puede salvar su ciudad de la masacre si le envía [amount] [item] en un plazo de 6 meses. De lo contrario, prepare a su pueblo para el derramamiento de sangre." }
  { key:PHRASE_threat_warning_C, text: 				"[greeting] [player_name], las fuerzas conquistadoras de [city_name] están listas para marchar. Si envía [amount] [item] en un plazo de 6 meses, las fuerzas atacantes quizá abandonen su ciudad sin causar daños." }
  { key:PHRASE_threat_comply_reason_P_A, text: 			"porque cedió ante el Faraón y envió [amount] [item] a [city_name]," }
  { key:PHRASE_threat_comply_reason_P_B, text:	  "ha cedido ante el Faraón y ha enviado [amount] [item] en relación con [city_name].  Además, los visires informan de que" }
  { key:PHRASE_threat_comply_reason_P_C, text:	  "aunque ha hecho lo que el Faraón exigía en relación con [city_name]," }
  { key:PHRASE_threat_comply_reason_C_A, text:  "porque se plegó a las órdenes de [city_name] y envió [amount] [item]," }
  { key:PHRASE_threat_comply_reason_C_B, text:	  "se plegó a las órdenes de [city_name] y envió [amount] [item].  Además, parece que" }
  { key:PHRASE_threat_comply_reason_C_C, text:	  "aunque cedió a las exigencias de [city_name] de [amount] [item], aun así" }
  { key:PHRASE_threat_too_late_reason_P_A, text:  	 "la demora en enviar [amount] [item] a [city_name], como exigía el Faraón, pone a prueba su paciencia, y por ello" }
  { key:PHRASE_threat_too_late_reason_P_B, text:	  "la demora en enviar [amount] [item] a [city_name], como exigía el Faraón, pone a prueba su paciencia.  Pasando a otros asuntos:" }
  { key:PHRASE_threat_too_late_reason_P_C, text:	  "la demora en enviar [amount] [item] a [city_name], como exigía el Faraón, pone a prueba su paciencia, pero aun así su esfuerzo es apreciado.  Por tanto," }
  { key:PHRASE_threat_too_late_reason_C_A, text: 		"porque subestimó la amenaza de [city_name] y no despachó [amount] [item] con rapidez," }
  { key:PHRASE_threat_too_late_reason_C_B, text:	  "debió de subestimar la amenaza de [city_name], ya que no despachó [amount] [item] con rapidez.  Pero eso ya es agua pasada, ahora" }
  { key:PHRASE_threat_too_late_reason_C_C, text:	  "corrió grandes riesgos al no despachar sin demora los [amount] [item] a [city_name] como exigían. Sin embargo, como sí logró cumplir," }
  { key:PHRASE_threat_refuse_reason_P_A, text:		"porque desobedeció la orden del Faraón de enviar [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_P_B, text:	  "desobedeció la orden del Faraón de enviar [amount] [item] a [city_name].  Además," }
  { key:PHRASE_threat_refuse_reason_P_C, text:	  "a pesar de su negativa a atender la amenaza del Faraón, que exigía el envío de [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_A, text:		"porque coqueteó a sabiendas con el peligro al negarse a enviar [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_B, text:	  "coqueteó a sabiendas con el peligro al negarse a enviar [amount] [item] a [city_name].  Debería saber también que" }
  { key:PHRASE_threat_refuse_reason_C_C, text:	  "aunque sin duda coqueteó con el peligro al negarse a enviar [amount] [item] a [city_name]," }
  { key:PHRASE_threat_no_reason_P_A, text:  	 	"porque está de un humor terrible," }
  { key:PHRASE_threat_no_reason_P_B, text:	  "como el mal humor del Faraón parece no tener fin," }
  { key:PHRASE_threat_no_reason_P_C, text:	  "" }
  { key:PHRASE_threat_no_reason_C_A, text:  	 	 				"porque [city_name] anhela la gloria," }
  { key:PHRASE_threat_no_reason_C_B, text:	  "parece que [city_name] nunca quedará satisfecha," }
  { key:PHRASE_threat_no_reason_C_C, text:	  "" }

  { key:PHRASE_eg_city_falls_title, text:  					"Ciudad egipcia caída" }
  { key:PHRASE_eg_city_falls_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] la poderosa ciudad de [city_name] ha caído en manos de nuestros enemigos." }
  { key:PHRASE_eg_city_falls_reason_A, text:  	 					"porque [city_name] ha caído ante fuerzas invasoras," }
  { key:PHRASE_eg_city_falls_reason_B, text:	  "[city_name] ha caído ante fuerzas invasoras.  Lo que es peor," }
  { key:PHRASE_eg_city_falls_reason_C, text:	  "aunque [city_name] ha caído ante fuerzas invasoras," }
  { key:PHRASE_eg_city_falls_no_reason_A, text:  		"ay de [city_name]:" }
  { key:PHRASE_eg_city_falls_no_reason_B, text:	  "parece que los problemas de [city_name] nunca terminarán, pues" }
  { key:PHRASE_eg_city_falls_no_reason_C, text:	  "" }

  { key:PHRASE_foreign_city_conquered_title, text: 					"Ciudad extranjera conquistada" }
  { key:PHRASE_foreign_city_conquered_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] Egipto ha conquistado con éxito la renombrada ciudad de [city_name], ¡ampliando aún más nuestra influencia!" }
  { key:PHRASE_foreign_city_conquered_reason_A, text: 				"porque la ciudad extranjera de [city_name] ha sido sometida por nuestras tropas," }
  { key:PHRASE_foreign_city_conquered_reason_B, text:	  "la ciudad extranjera de [city_name] ha sido sometida por nuestras tropas!  Ahora," }
  { key:PHRASE_foreign_city_conquered_reason_C, text:	  "aunque la ciudad extranjera de [city_name] ha sido sometida por nuestras tropas," }
  { key:PHRASE_foreign_city_conquered_no_reason_A, text:  	"por nuestra fuerza en las armas," }
  { key:PHRASE_foreign_city_conquered_no_reason_B, text:	  "la fuerza de nuestro reino sigue creciendo.  Ahora" }
  { key:PHRASE_foreign_city_conquered_no_reason_C, text:	  "" }

  { key:PHRASE_route_opened_title, text: 						"Nueva ruta comercial disponible" }
  { key:PHRASE_route_opened_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] ya se puede abrir una nueva ruta comercial hacia [city_name]." }
  { key:PHRASE_route_opened_reason_A, text:  	 				"porque se ha habilitado una nueva ruta comercial hacia [city_name]," }
  { key:PHRASE_route_opened_reason_B, text:	  				"se ha habilitado una nueva ruta comercial hacia [city_name], y" }
  { key:PHRASE_route_opened_reason_C, text:	  				"aunque ya es posible comerciar con [city_name]," }
  { key:PHRASE_route_opened_no_reason_A, text:  	 			"debido a la actividad diplomática," }
  { key:PHRASE_route_opened_no_reason_B, text:	  "hay cambios en el aire, pues" }
  { key:PHRASE_route_opened_no_reason_C, text:	  "" }

  { key:PHRASE_route_closed_title, text:  					"Cierre de ruta comercial" }
  { key:PHRASE_route_closed_initial_announcement, text:     "[greeting] [player_name], [reason_phrase] la ruta comercial hacia [city_name] ha sido clausurada." }
  { key:PHRASE_route_closed_reason_A, text:   	 					"porque la ruta comercial hacia [city_name] se ha cerrado," }
  { key:PHRASE_route_closed_reason_B, text: 	  "la ruta comercial hacia [city_name] se ha cerrado, y, además," }
  { key:PHRASE_route_closed_reason_C, text: 	  "aunque la ruta comercial hacia [city_name] se ha cerrado," }
  { key:PHRASE_route_closed_no_reason_A, text:   	 				"debido a la inestabilidad política," }
  { key:PHRASE_route_closed_no_reason_B, text: 	  "..esto debería haberse previsto.  Parece que" }
  { key:PHRASE_route_closed_no_reason_C, text: 	  "" }

  { key:PHRASE_trade_city_siege_title, text:  							"Ciudad comercial sitiada" }
  { key:PHRASE_trade_city_siege_announcement, text: 			"[greeting] [player_name], [reason_phrase] un debilitante asedio azota ahora a [city_name]." }
  { key:PHRASE_trade_city_siege_reason_A, text:   						"porque [city_name] está sitiada," }
  { key:PHRASE_trade_city_siege_reason_B, text: 	  "[city_name] está sitiada, y" }
  { key:PHRASE_trade_city_siege_reason_C, text: 	  "aunque [city_name] está sitiada," }
  { key:PHRASE_trade_city_siege_no_reason_A, text:   		"los exploradores militares traen terribles noticias.  Parece que" }
  { key:PHRASE_trade_city_siege_no_reason_B, text: 	  "no hay fin aparente a sus problemas, pues" }
  { key:PHRASE_trade_city_siege_no_reason_C, text: 	  "" }

  { key:PHRASE_eg_city_saved_title, text: 					"Ciudad egipcia salvada" }
  { key:PHRASE_eg_city_saved_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [city_name] ha sido salvada de nuestros enemigos. " }
  { key:PHRASE_eg_city_saved_reason_A, text:  	 				"porque [city_name] ha sido salvada de nuestros enemigos," }
  { key:PHRASE_eg_city_saved_reason_B, text:	  "[city_name] ha sido salvada de nuestros enemigos!  Ahora," }
  { key:PHRASE_eg_city_saved_reason_C, text:	  "aunque [city_name] ha sido salvada de nuestros enemigos," }
  { key:PHRASE_eg_city_saved_no_reason_A, text:  			"gracias al valiente esfuerzo del ejército egipcio," }
  { key:PHRASE_eg_city_saved_no_reason_B, text:	  "la marea de la guerra sube y baja, por ahora" }
  { key:PHRASE_eg_city_saved_no_reason_C, text:	  "" }

  { key:PHRASE_battle_won_title, text:  					"Victoria en batalla" }
  { key:PHRASE_battle_won_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] ¡el ejército egipcio ha salido victorioso!" }
  { key:PHRASE_battle_won_reason_A, text:   	 		"porque nuestras fuerzas triunfaron en la lejana batalla de [city_name]," }
  { key:PHRASE_battle_won_reason_B, text: 	  "nuestras fuerzas triunfaron en la lejana batalla de [city_name].  Ahora" }
  { key:PHRASE_battle_won_reason_C, text: 	  "aunque nuestras fuerzas triunfaron en la batalla de [city_name]" }
  { key:PHRASE_battle_won_no_reason_A, text:   		"gracias al vigor de tropas bien entrenadas en la lejana ciudad de [city_name]," }
  { key:PHRASE_battle_won_no_reason_B, text: 	  "parece que los milagros nunca cesarán, pues en [city_name]" }
  { key:PHRASE_battle_won_no_reason_C, text: 	  "" }

  { key:PHRASE_battle_lost_title, text:  					"El ejército egipcio ha sido derrotado" }
  { key:PHRASE_battle_lost_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] el ejército egipcio fue derrotado en [city_name]. " }
  { key:PHRASE_battle_lost_reason_A, text:   	 					"porque Egipto perdió una batalla contra sus enemigos en [city_name]," }
  { key:PHRASE_battle_lost_reason_B, text: 	  "Egipto ha perdido una batalla contra sus enemigos en [city_name].  Además," }
  { key:PHRASE_battle_lost_reason_C, text: 	  "aunque Egipto perdió la batalla contra sus enemigos en [city_name]," }
  { key:PHRASE_battle_lost_no_reason_A, text:   	"una gran desgracia ha caído sobre las tropas, pues" }
  { key:PHRASE_battle_lost_no_reason_B, text: 	  "la guerra es terriblemente impredecible.  Lamentablemente" }
  { key:PHRASE_battle_lost_no_reason_C, text: 	  "" }

  { key:PHRASE_acknowledgement_title, text: 					"Sumisión reconocida" }
  { key:PHRASE_acknowledgement_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] tu ciudad está a salvo... por ahora." }
  { key:PHRASE_acknowledgement_reason_A, text:  	 			"porque cediste sumisamente ante una amenaza," }
  { key:PHRASE_acknowledgement_reason_B, text:	  				"cediste sumisamente ante una amenaza," }
  { key:PHRASE_acknowledgement_reason_C, text:	  				"aunque cediste sumisamente ante una amenaza," }
  { key:PHRASE_acknowledgement_no_reason_A, text:				"debido a un cambio de actitud," }
  { key:PHRASE_acknowledgement_no_reason_B, text:	  			"nada es nunca seguro, pero" }
  { key:PHRASE_acknowledgement_no_reason_C, text:	  			"" }

  { key: PHRASE_pharaoh_attacks_you_title, text: 					"El ejército del Faraón ataca" }
  { key: PHRASE_pharaoh_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] el ejército del Faraón se ha puesto en marcha y llegará a tu ciudad en [time_until_attack] meses." }
  { key: PHRASE_pharaoh_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] el ejército del Faraón se acerca cada vez más y llegará a tu ciudad dentro de dos años." }
  { key: PHRASE_pharaoh_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] el ejército del Faraón está preparado para la batalla y llegará a tu ciudad dentro de un año." }
  { key: PHRASE_pharaoh_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] el ejército del Faraón anhela atacarte y llegará a tu ciudad dentro de seis meses." }
  { key: PHRASE_pharaoh_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] ¡el ejército del Faraón está a solo un mes de llegar a la ciudad!." }
  { key: PHRASE_pharaoh_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], ¡el ejército del Faraón se nos echa encima!" }
  { key: PHRASE_pharaoh_attacks_you_reason_A, text:  	 	 		"porque tu ciudad fue atacada por el ejército del Faraón," }
  { key: PHRASE_pharaoh_attacks_you_reason_B, text:	  				"tu ciudad ha sido atacada por el ejército del Faraón.  Además" }
  { key: PHRASE_pharaoh_attacks_you_reason_C, text:	  				"aunque tu ciudad ha sido atacada por el ejército del Faraón," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_A, text:  	 		"a veces el Faraón actúa por razones que solo él conoce. " }
  { key: PHRASE_pharaoh_attacks_you_no_reason_B, text:	  			"el Faraón es impredecible.  Ahora," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_C, text:	  			"porque tu posición en el Reino ha caído tan bajo," }
  { key: PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text:		"tu posición en el Reino se ha desplomado por completo. Quizá más regalos para el pueblo egipcio aún puedan cambiar las cosas, aunque incluso ahora" }

  { key: PHRASE_eg_city_attacks_you_title, text: 					"El ejército egipcio ataca" }
  { key: PHRASE_eg_city_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] un ejército egipcio prepara su ataque y llegará a tu ciudad dentro de [time_until_attack] meses." }
  { key: PHRASE_eg_city_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] un ejército egipcio ha iniciado su marcha y llegará a tu ciudad dentro de dos años.				" }
  { key: PHRASE_eg_city_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] tu ciudad sufrirá el embate de un ejército egipcio dentro de un año." }
  { key: PHRASE_eg_city_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] un ejército egipcio se acerca y llegará a tu ciudad dentro de seis meses.	" }
  { key: PHRASE_eg_city_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] un ejército egipcio se aproxima a tus fronteras y llegará a tu ciudad dentro de un mes." }
  { key: PHRASE_eg_city_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], ¡una fuerza invasora de tropas egipcias se nos echa encima!" }
  { key: PHRASE_eg_city_attacks_you_reason_A, text:  	 	 		"porque tu ciudad fue atacada por el ejército egipcio," }
  { key: PHRASE_eg_city_attacks_you_reason_B, text:	  				"¡el ejército egipcio ha atacado tu ciudad!  Además" }
  { key: PHRASE_eg_city_attacks_you_reason_C, text:	  				"aunque tu ciudad ha sido atacada por el ejército egipcio," }
  { key: PHRASE_eg_city_attacks_you_no_reason_A, text:  	 		"cuidado:" }
  { key: PHRASE_eg_city_attacks_you_no_reason_B, text:	  			"ha llegado la hora de la guerra, pues" }
  { key: PHRASE_eg_city_attacks_you_no_reason_C, text:	  			"porque tu reputación en el Reino es tan baja," }
  { key: PHRASE_eg_city_attacks_you_because_of_low_kingdom, text:		"tu posición en el Reino se ha desplomado por completo. Quizá más regalos para el pueblo egipcio aún puedan cambiar las cosas, aunque incluso ahora" }

  { key: PHRASE_foreign_army_attacks_you_title, text: 					"Invasión de ejército extranjero" }
  { key: PHRASE_foreign_army_attacks_you_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [a_foreign_army] se acerca y llegará a tu ciudad dentro de [time_until_attack] meses." }
  { key: PHRASE_foreign_army_attacks_you_2year_reminder, text: 			"[greeting] [player_name], [reason_phrase] dentro de dos años [a_foreign_army] estará a tus puertas." }
  { key: PHRASE_foreign_army_attacks_you_1year_reminder, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] ansía invadir y llegará a tu ciudad dentro de un año." }
  { key: PHRASE_foreign_army_attacks_you_6month_warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] llegará a tu ciudad dentro de seis meses. Prepárate para su llegada." }
  { key: PHRASE_foreign_army_attacks_you_1month_Warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] llegará a la ciudad dentro de un mes, decidido a conquistarla." }
  { key: PHRASE_foreign_army_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], [a_foreign_army] se nos echa encima, ¡y están decididos a destruir la ciudad!" }
  { key: PHRASE_foreign_army_attacks_you_reason_A, text:  	 	 		"porque tu ciudad fue atacada por [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_reason_B, text:	  			"tu ciudad ha sido atacada por [a_foreign_army], y ahora" }
  { key: PHRASE_foreign_army_attacks_you_reason_C, text:	  			"aunque tu ciudad ha sido atacada por [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_A, text:  	 		"debido a sus sueños de imperio," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_B, text:	  "parece que siempre hay problemas, pues" }
  { key: PHRASE_foreign_army_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_rating_change_title_I, text: 					"Aumenta la posición en el Reino" }
  { key: PHRASE_rating_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] te has vuelto más popular entre tus compatriotas egipcios, y tu calificación en el Reino ha subido." }
  { key: PHRASE_rating_change_reason_I_A, text:  	 	 		"porque tu reputación en el Reino aumentó recientemente," }
  { key: PHRASE_rating_change_reason_I_B, text:	  "tu reputación en el Reino ha mejorado.  Ahora" }
  { key: PHRASE_rating_change_reason_I_C, text:	  "tu reputación ha mejorado, pero" }
  { key: PHRASE_rating_change_no_reason_I_A, text:		"porque los tiempos son buenos," }
  { key: PHRASE_rating_change_no_reason_I_B, text:	  "estas son buenas noticias, pues" }
  { key: PHRASE_rating_change_no_reason_I_C, text:	  "los sacrificios de tu ciudad en combate son muy apreciados por el pueblo egipcio.  Como resultado" }
  { key: PHRASE_rating_change_title_D, text: 					"Cae la posición en el Reino" }
  { key: PHRASE_rating_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] el pueblo egipcio no está contento contigo, y tu calificación en el Reino ha caído." }
  { key: PHRASE_rating_change_reason_D_A, text:  	 	 		"porque tu calificación en el Reino ha caído tanto," }
  { key: PHRASE_rating_change_reason_D_B, text:	  				"tu popularidad disminuye en todo el reino, y ahora" }
  { key: PHRASE_rating_change_reason_D_C, text:	  				"aunque cada vez eres menos popular en el reino," }
  { key: PHRASE_rating_change_no_reason_D_A, text:  			"debido al descontento en el Reino," }
  { key: PHRASE_rating_change_no_reason_D_B, text:	  "estas son malas noticias, pues" }
  { key: PHRASE_rating_change_no_reason_D_C, text:	  "tus compatriotas no aprueban tus métodos violentos.  Como resultado" }

  { key:PHRASE_price_change_title_I, text: 					"Aumento de precios" }
  { key:PHRASE_price_change_initial_announcement_I, text:		"[greeting] [player_name], [reason_phrase] el precio de [item] ha subido. Importar este bien ahora es más caro, pero se pueden obtener mayores beneficios exportándolo." }
  { key:PHRASE_price_change_reason_I_A, text:  	 	 		"porque el precio de [item] ha subido," }
  { key:PHRASE_price_change_reason_I_B, text:	  "el precio de [item] ha subido, y además" }
  { key:PHRASE_price_change_reason_I_C, text:	  "aunque los precios han subido," }
  { key:PHRASE_price_change_no_reason_I_A, text:   	"debido a la reducción de suministros en todo el mundo," }
  { key:PHRASE_price_change_no_reason_I_B, text:	  "mientras el mercado sigue cambiando" }
  { key:PHRASE_price_change_no_reason_I_C, text:	  "" }
  { key:PHRASE_price_change_title_D, text: 					"Bajada de precios" }
  { key:PHRASE_price_change_initial_announcement_D, text:		"[greeting] [player_name], [reason_phrase] el precio de [item] ha bajado. Esto reducirá los beneficios que se obtienen al exportarlo." }
  { key:PHRASE_price_change_reason_D_A, text:  	 	 	"porque el precio de [item] que puedes comerciar ha bajado," }
  { key:PHRASE_price_change_reason_D_B, text:	  "los precios han bajado, y además" }
  { key:PHRASE_price_change_reason_D_C, text:	  "aunque los precios han bajado," }
  { key:PHRASE_price_change_no_reason_D_A, text:  		"debido a un exceso generalizado en el Reino," }
  { key:PHRASE_price_change_no_reason_D_B, text:	  "mientras el mercado sigue cambiando" }
  { key:PHRASE_price_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_demand_change_title_I, text: 					"Aumento del comercio" }
  { key: PHRASE_demand_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] [city_name] está dispuesta ahora a comerciar aún más [item]." }
  { key: PHRASE_demand_change_reason_I_A, text:  	 			"porque [city_name] está dispuesta a comerciar más [item]," }
  { key: PHRASE_demand_change_reason_I_B, text:	  "[city_name] desea ahora comerciar más [item].  Además," }
  { key: PHRASE_demand_change_reason_I_C, text:	  "aunque [city_name] desea comerciar más [item]," }
  { key: PHRASE_demand_change_no_reason_I_A, text:  	"porque [city_name] está creciendo," }
  { key: PHRASE_demand_change_no_reason_I_B, text:	  "los tiempos cambian, y" }
  { key: PHRASE_demand_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_demand_change_title_D, text: 					"Disminución del comercio" }
  { key: PHRASE_demand_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] [city_name] ha decidido que debe reducir la cantidad de [item] que está dispuesta a comerciar contigo." }
  { key: PHRASE_demand_change_reason_D_A, text:  	 			"porque [city_name] no comercia tanto [item]," }
  { key: PHRASE_demand_change_reason_D_B, text:	  "[city_name] no comercia tanto, y" }
  { key: PHRASE_demand_change_reason_D_C, text:	  "aunque [city_name] no comercia tanto," }
  { key: PHRASE_demand_change_no_reason_D_A, text:			"porque los ciudadanos de [city_name] están recortando gastos," }
  { key: PHRASE_demand_change_no_reason_D_B, text:	  "los tiempos cambian, y" }
  { key: PHRASE_demand_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_earthquake_title, text: 					"¡Terremoto!" }
  { key: PHRASE_earthquake_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase]  la arena se ha movido bajo nuestros pies. Nuestra tierra nunca volverá a ser la misma. Haz lo que puedas para reparar los daños que el terremoto causó en tu ciudad y en tu pueblo." }
  { key: PHRASE_earthquake_reason_A, text:  	 	 					"a causa de un terrible terremoto," }
  { key: PHRASE_earthquake_reason_B, text:	  "además del terrible terremoto," }
  { key: PHRASE_earthquake_reason_C, text:	  "a pesar del terrible terremoto" }
  { key: PHRASE_earthquake_no_reason_A, text:  	 						"la ciudad está asustada porque" }
  { key: PHRASE_earthquake_no_reason_B, text:	  "los problemas acechan de nuevo a la ciudad, pues" }
  { key: PHRASE_earthquake_no_reason_C, text:	  "" }

  { key: PHRASE_stormy_seas_title, text: 					"Tempestades" }
  { key: PHRASE_stormy_seas_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] las aguas agitadas amenazan con destrozar los barcos mercantes. Podrían pasar meses antes de que los vientos se calmen y los mercaderes se atrevan a arriesgar de nuevo sus cargamentos. Mientras tanto, no podemos comerciar por agua." }
  { key: PHRASE_stormy_seas_reason_A, text:  	 	 					"a causa de tormentas inconcebiblemente feroces," }
  { key: PHRASE_stormy_seas_reason_B, text:	  "mientras nos han azotado tormentas recientes," }
  { key: PHRASE_stormy_seas_reason_C, text:	  "a pesar de las terribles tormentas" }
  { key: PHRASE_stormy_seas_no_reason_A, text:  	 					"las tormentas arrecian y" }
  { key: PHRASE_stormy_seas_no_reason_B, text:	  "nuestros problemas acaban de empezar, pues" }
  { key: PHRASE_stormy_seas_no_reason_C, text:	  "" }
                         
  { key: PHRASE_sandstorm_title, text: 						"Tormentas de arena" }
  { key: PHRASE_sandstorm_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] las arenas arrastradas han cubierto los caminos, borrándolos por completo en algunos tramos. Los mercaderes no se arriesgan a perderse en tales condiciones y no se aventuran a salir. Hasta que los vientos amainen, ningún mercader podrá pasar." }
  { key: PHRASE_sandstorm_reason_A, text:  	 				"porque los mercaderes no se atreven a partir durante una tormenta de arena y el comercio terrestre se ha detenido," }
  { key: PHRASE_sandstorm_reason_B, text:	  "las tormentas de arena han detenido en seco a los mercaderes.  Además" }
  { key: PHRASE_sandstorm_reason_C, text:	  "a pesar de las recientes tormentas de arena que han obstaculizado el comercio," }
  { key: PHRASE_sandstorm_no_reason_A, text:  	 						"debido a los fuertes vientos," }
  { key: PHRASE_sandstorm_no_reason_B, text:	  "el desierto es un lugar peligroso, pues" }
  { key: PHRASE_sandstorm_no_reason_C, text:	  "" }

  { key: PHRASE_wage_change_title_I, text: 					"Los trabajadores celebran el aumento" }
  { key: PHRASE_wage_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] los salarios han aumentado en todo el Reino. Tus propios trabajadores podrían marcharse a pastos más verdes si no cobran lo mismo que sus homólogos de otras ciudades." }
  { key: PHRASE_wage_change_reason_I_A, text:  	 	 		"porque los salarios han aumentado en todo el Reino," }
  { key: PHRASE_wage_change_reason_I_B, text:	  "los salarios han aumentado en todo el Reino, y" }
  { key: PHRASE_wage_change_reason_I_C, text:	  "aunque los salarios han aumentado en todo el Reino," }
  { key: PHRASE_wage_change_no_reason_I_A, text:  	"los tiempos cambian, y ahora" }
  { key: PHRASE_wage_change_no_reason_I_B, text:	  "unos se alegran, otros se quejan, pues" }
  { key: PHRASE_wage_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_wage_change_title_D, text: 					"Bajan los salarios" }
  { key: PHRASE_wage_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] los salarios han bajado en todo el Reino de Egipto.  Parece que en todas partes la gente trabajará por menos." }
  { key: PHRASE_wage_change_reason_D_A, text:  	 	 				"porque los salarios han bajado," }
  { key: PHRASE_wage_change_reason_D_B, text:	  "los salarios han bajado, y además," }
  { key: PHRASE_wage_change_reason_D_C, text:	  "aunque los salarios han bajado," }
  { key: PHRASE_wage_change_no_reason_D_A, text:  		"para intentar reducir costes," }
  { key: PHRASE_wage_change_no_reason_D_B, text:	  "algunos están molestos, pero los nomarcas se alegran, pues" }
  { key: PHRASE_wage_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_bad_water_title, text: 					"Agua Contaminada" }
  { key: PHRASE_bad_water_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] algunos de tus ciudadanos han enfermado por algo que hay en el agua. Solo espero que el problema no se agrave." }
  { key: PHRASE_bad_water_reason_A, text:  	 	 				"debido a la reciente contaminación del agua," }
  { key: PHRASE_bad_water_reason_B, text:	  "la reciente contaminación del agua fue muy lamentable.  Ahora," }
  { key: PHRASE_bad_water_reason_C, text:	  "aunque el agua se contaminó recientemente," }
  { key: PHRASE_bad_water_no_reason_A, text:  		"la mala suerte acecha a la ciudad, y" }
  { key: PHRASE_bad_water_no_reason_B, text:	  ", esto es realmente lamentable.  Parece que" }
  { key: PHRASE_bad_water_no_reason_C, text:	  "" }

  { key: PHRASE_goldmine_cavein_title, text: 					"Derrumbe de la Mina de Oro" }
  { key: PHRASE_goldmine_cavein_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] una mina de oro se ha derrumbado. Nuestros arquitectos no pudieron impedirlo. Solo espero que los trabajadores hayan logrado salir de la mina a tiempo." }
  { key: PHRASE_goldmine_cavein_reason_A, text:  	 	 			"porque una mina de oro se derrumbó," }
  { key: PHRASE_goldmine_cavein_reason_B, text:	  "el reciente derrumbe de la mina de oro fue muy lamentable.  Ahora," }
  { key: PHRASE_goldmine_cavein_reason_C, text:	  "aunque una mina de oro se derrumbó recientemente," }
  { key: PHRASE_goldmine_cavein_no_reason_A, text: 		"debido al desplazamiento de las arenas," }
  { key: PHRASE_goldmine_cavein_no_reason_B, text:	  "sin previo aviso," }
  { key: PHRASE_goldmine_cavein_no_reason_C, text:	  "" }

  { key: PHRASE_landslide_title, text: 					"Deslizamiento de Tierra" }
  { key: PHRASE_landslide_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] un terrible deslizamiento de tierra ha cortado una ruta comercial.  Podrían pasar meses antes de que se despeje el camino y los mercaderes vuelvan a partir." }
  { key: PHRASE_landslide_reason_A, text:  	 	 				"debido al reciente deslizamiento de tierra," }
  { key: PHRASE_landslide_reason_B, text:	  "los recientes deslizamientos de tierra fueron devastadores.  Ahora," }
  { key: PHRASE_landslide_reason_C, text:	  "aunque recientemente ha habido terribles deslizamientos de tierra," }
  { key: PHRASE_landslide_no_reason_A, text:  	 					"hay noticias terribles:" }
  { key: PHRASE_landslide_no_reason_B, text:	  "sin previo aviso" }
  { key: PHRASE_landslide_no_reason_C, text:	  "" }

  { key: PHRASE_flood_fails_title, text: 					"Es probable que la inundación fracase" }
  { key: PHRASE_flood_fails_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] los sacerdotes traen malas noticias... ¡temen que la próxima Inundación casi con toda seguridad fracase! Consulte el Nilómetro con regularidad... si la predicción de los sacerdotes no mejora, la ciudad más vale que se prepare para lo peor." }
  { key: PHRASE_flood_fails_reason_A, text:  	 	 					"porque se espera que la inundación fracase" }
  { key: PHRASE_flood_fails_reason_B, text:	  "se espera que la inundación fracase, y" }
  { key: PHRASE_flood_fails_reason_C, text:	  "aunque se esperaba que la inundación fracasara," }
  { key: PHRASE_flood_fails_no_reason_A, text:		"debido a la sequía en África," }
  { key: PHRASE_flood_fails_no_reason_B, text:	  "nuestros problemas acaban de empezar, pues" }
  { key: PHRASE_flood_fails_no_reason_C, text:	  "" }

  { key : PHRASE_perfect_flood_title, text: 					"Se espera una inundación perfecta" }
  { key : PHRASE_perfect_flood_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] esto es, en efecto, una bendición, ¡pues es muy probable que la inundación sea abundante! Consulte el Nilómetro periódicamente.  Si la predicción empeora, la ciudad podría encontrarse desprevenida." }
  { key : PHRASE_perfect_flood_reason_A, text:  	 	 				"porque se esperaba que la inundación fuera abundante," }
  { key : PHRASE_perfect_flood_reason_B, text:	  "se esperaba que la inundación fuera abundante, y" }
  { key : PHRASE_perfect_flood_reason_C, text:	  "aunque se esperaba que la inundación fuera abundante," }
  { key : PHRASE_perfect_flood_no_reason_A, text:  	 					"se espera que lleguen los monzones a África, así que" }
  { key : PHRASE_perfect_flood_no_reason_B, text:	  "somos, en efecto, afortunados, pues" }
  { key : PHRASE_perfect_flood_no_reason_C, text:	  "" }

  { key: PHRASE_bedouin_attacks_you_title, text: 					"Ataque del Ejército Beduino" }
  { key: PHRASE_bedouin_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] un ejército beduino se acerca a la ciudad y atacará dentro de [time_until_attack] meses." }
  { key: PHRASE_bedouin_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] un ejército beduino avanza cada vez más cerca y llegará a la ciudad dentro de dos años.				" }
  { key: PHRASE_bedouin_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] un ejército beduino ya está en camino y llegará a la ciudad dentro de un año." }
  { key: PHRASE_bedouin_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] un ejército beduino está preparado para hacer la guerra y llegará a la ciudad dentro de seis meses.	" }
  { key: PHRASE_bedouin_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] un ejército beduino está muy cerca y llegará a la ciudad dentro de un mes." }
  { key: PHRASE_bedouin_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], ¡un ejército beduino atacante está sobre nosotros!" }
  { key: PHRASE_bedouin_attacks_you_reason_A, text:  	 	 		"porque tu ciudad logró repeler con éxito al ejército beduino," }
  { key: PHRASE_bedouin_attacks_you_reason_B, text:	  				"tu ciudad logró repeler con éxito al ejército beduino.  Además," }
  { key: PHRASE_bedouin_attacks_you_reason_C, text:	  "aunque tu ciudad logró repeler con éxito al ejército beduino," }
  { key: PHRASE_bedouin_attacks_you_no_reason_A, text:  	"para saciar su afán de riquezas," }
  { key: PHRASE_bedouin_attacks_you_no_reason_B, text:	  "nuestros problemas son grandes, pues" }
  { key: PHRASE_bedouin_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_gift_title_P, text: 				"Un Regalo del Faraón" }
  { key: PHRASE_gift_title_C, text: 				"Un Regalo de un Vecino" }
  { key: PHRASE_gift_granted_P, text:				"[greeting] [player_name], [reason_phrase] el Faraón ha decretado que recibas un regalo de [amount] [item] de [city_name]." }
  { key: PHRASE_gift_granted_C, text:				"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] desea concederte un regalo de [amount] [item]." }
  { key: PHRASE_gift_cash_granted_P, text:			"[greeting] [player_name], [reason_phrase] el Faraón ha decretado que recibas un regalo de [amount] debenes de [city_name]." }
  { key: PHRASE_gift_cash_granted_C, text:			"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] desea concederte un regalo de [amount] debenes." }
  { key: PHRASE_gift_partial_space_P, text:			"[greeting] [player_name], [reason_phrase] el Faraón ha decretado que recibas un regalo de [amount] [item] de [city_name].  Actualmente no tienes espacio suficiente en tus Almacenes o Graneros para acomodar este regalo, pero puedes guardar al menos la mitad." }
  { key: PHRASE_gift_partial_space_C, text:			"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] desea concederte un regalo de [amount] [item].  Actualmente no tienes espacio suficiente en tus Almacenes o Graneros para acomodar este regalo, pero puedes guardar al menos la mitad." }
  { key: PHRASE_gift_insufficient_space_P, text: 	"[greeting] [player_name], [reason_phrase] el Faraón ha decretado que recibas un regalo de [amount] [item] de [city_name], pero no hay suficiente espacio en tus Almacenes y Graneros.  Haz sitio y se volverá a entregar el próximo mes." }
  { key: PHRASE_gift_insufficient_space_C, text: 	"[greeting] [player_name], [reason_phrase] la ciudad de [city_name] desea concederte un regalo de [amount] [item], pero no hay suficiente espacio en tus Almacenes y Graneros para acomodarlo.  Haz sitio y se volverá a entregar el próximo mes." }
  { key: PHRASE_gift_last_chance_P, text: 			"[greeting] [player_name], por orden del Faraón, la ciudad de [city_name] ha estado intentando concederte un regalo de [amount] [item], pero aún no tienes suficiente espacio en tus Almacenes y Graneros para acomodarlo todo.  Has hecho esperar demasiado a sus emisarios, y se han impacientado.  Acepta ahora este regalo parcial, pues no volverán nunca más." }
  { key: PHRASE_gift_last_chance_C, text: 			"[greeting] [player_name], la ciudad de [city_name] ha estado intentando concederte un regalo de [amount] [item], pero aún no tienes suficiente espacio en tus Almacenes y Graneros para acomodarlo todo.  Has hecho esperar demasiado a sus emisarios, y se han impacientado.  Acepta ahora este regalo parcial, pues no volverán nunca más." }
  { key: PHRASE_gift_forfeited_P, text: 			"[greeting] [player_name], aún no hay espacio suficiente para que recibas el regalo de [amount] [item] de [city_name], por lo que se pierde." }
  { key: PHRASE_gift_forfeited_C, text: 			"[greeting] [player_name], aún no hay espacio suficiente para que recibas el regalo de [amount] [item] de [city_name], por lo que se pierde." }
  { key: PHRASE_gift_accepted_P, text: 				"Por orden del Faraón, tus Almacenes y Graneros se han llenado con todo el [item] de [city_name] que han podido acomodar." }
  { key: PHRASE_gift_accepted_C, text: 				"Tus Almacenes y Graneros se han llenado con todo el [item] de [city_name] que han podido acomodar." }
  { key: PHRASE_gift_cash_accepted_P, text: 		"Por orden del Faraón, se han añadido [amount_granted] debenes a tu tesoro." }
  { key: PHRASE_gift_cash_accepted_C, text: 		"Gracias a [city_name], se han añadido [amount_granted] debenes a tu tesoro." }
  { key: PHRASE_gift_postponed_P, text:				"Los emisarios de [city_name] regresarán dentro de un mes con la entrega de [item]." }
  { key: PHRASE_gift_postponed_C, text: 			"Los emisarios de [city_name] regresarán dentro de un mes con la entrega de [item]." }
  { key: PHRASE_gift_refused_P, text: 				"Aunque has rechazado este regalo de [item] de [city_name], estoy seguro de que alguien más podría necesitar nuestra ayuda." }
  { key: PHRASE_gift_refused_C, text: 				"Aunque has rechazado este regalo de [item] de [city_name], estoy seguro de que alguien más podría necesitar nuestra ayuda." }
  { key: PHRASE_gift_accepted_reason_P_A, text:  	 		"porque aceptaste un regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_accepted_reason_P_B, text:	  "a raíz de tu reciente regalo de [city_name]," }
  { key: PHRASE_gift_accepted_reason_P_C, text:	  "aunque aceptaste el regalo de [amount] [item] de [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_A, text:  	 		"porque aceptaste un regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_accepted_reason_C_B, text:	  "a raíz de tu reciente regalo de [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_C, text:	  "aunque aceptaste el regalo de [amount] [item] de [city_name]," }
  { key: PHRASE_gift_forfeited_reason_P_A, text:  	 		"porque no aceptaste un regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_P_B, text:	  "no aceptaste un regalo de [amount] [item] de [city_name].  Además," }
  { key: PHRASE_gift_forfeited_reason_P_C, text:	  "aunque no aceptaste el regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_A, text:  	 		"porque no aceptaste el regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_B, text:	  "no aceptaste el regalo de [amount] [item] de [city_name].  Además," }
  { key: PHRASE_gift_forfeited_reason_C_C, text:	  "aunque no aceptaste el regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_refused_reason_P_A, text:  	 		"porque rechazaste un regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_refused_reason_P_B, text:	  "rechazaste un regalo de [amount] [item] de [city_name].  Ahora," }
  { key: PHRASE_gift_refused_reason_P_C, text:	  "aunque rechazaste un regalo de [amount] [item] de [city_name]," }
  { key: PHRASE_gift_refused_reason_C_A, text:  	 		"porque rechazaste un regalo de [amount] [item] de [city_name]" }
  { key: PHRASE_gift_refused_reason_C_B, text:	  "rechazaste un regalo de [amount] [item] de [city_name].  Ahora," }
  { key: PHRASE_gift_refused_reason_C_C, text:	  "aunque rechazaste un regalo de [amount] [item] de [city_name]," }
  { key: PHRASE_gift_no_reason_P_A, text:  					"porque podrías necesitar algo de ayuda" }
  { key: PHRASE_gift_no_reason_P_B, text:	  "porque la benevolencia del Faraón es infinita," }
  { key: PHRASE_gift_no_reason_P_C, text:	  "los sacrificios de tu ciudad en combate son muy apreciados por el Faraón.  En consecuencia" }
  { key: PHRASE_gift_no_reason_C_A, text:  					"porque podrías necesitar algo de ayuda" }
  { key: PHRASE_gift_no_reason_C_B, text:	  "porque los egipcios siempre ayudan a sus compatriotas," }
  { key: PHRASE_gift_no_reason_C_C, text:	  "los sacrificios de tu ciudad en combate son muy apreciados por el pueblo egipcio.  En consecuencia" }

  { key: PHRASE_pharaoh_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] el ejército del Faraón ha llegado para reclamar tu ciudad por la fuerza." }
  { key: PHRASE_eg_city_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] un ejército egipcio ha desembarcado e invade la ciudad mientras hablamos." }
  { key: PHRASE_foreign_army_attacks_you_disembarked_alert, text:  	"[greeting] [player_name], [reason_phrase] [a_foreign_army] ha desembarcado y ya está atacando la ciudad. Que Seth nos proteja." }
  { key: PHRASE_bedouin_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] una fuerza invasora beduina hostil ha desembarcado en nuestras costas." }

  { key: PHRASE_pyramid_congratulations_title, text:			"¡Pirámide terminada!" }
  { key: PHRASE_pyramid_congratulations, text:					"[greeting] [player_name], ¡esto es un logro espectacular! Tras incontables meses de trabajo, ¡la Pirámide por fin está completa!" }
  { key: PHRASE_stepped_pyramid_congratulations_title, text:	"¡Pirámide escalonada terminada!" }
  { key: PHRASE_stepped_pyramid_congratulations, text:			"[greeting] [player_name], ¡por fin la Pirámide escalonada está completa!  Este monumento será por siempre un testimonio de tu capacidad." }
  { key: PHRASE_bent_pyramid_congratulations_title, text:		"¡Pirámide acodada terminada!" }
  { key: PHRASE_bent_pyramid_congratulations, text:				"[greeting] [player_name], ¡la construcción de la Pirámide acodada por fin está completa! Es un logro asombroso para tu ciudad." }
  { key: PHRASE_mudbrick_pyramid_congratulations_title, text:	"¡Pirámide de adobe terminada!" }
  { key: PHRASE_mudbrick_pyramid_congratulations, text:			"[greeting] [player_name], los canteros han dado los toques finales al reluciente revestimiento exterior de caliza fina, ¡y la Pirámide de adobe por fin está terminada!" }
  { key: PHRASE_mastaba_congratulations_title, text:			"¡Mastaba terminada!" }
  { key: PHRASE_mastaba_congratulations, text:					"[greeting] [player_name], se ha colocado el último ladrillo y ¡la Mastaba ya está completa!" }
  { key: PHRASE_sphinx_congratulations_title, text:				"¡Esfinge terminada!" }
  { key: PHRASE_sphinx_congratulations, text:					"[greeting] [player_name], por fin los canteros han terminado de tallar la poderosa Esfinge.  Este monumento velará por Egipto durante todas las edades." }
  { key: PHRASE_obelisk_congratulations_title, text:			"¡Obelisco terminado!" }
  { key: PHRASE_obelisk_congratulations, text:					"[greeting] [player_name], los canteros han dado los toques finales al Obelisco, y por fin está completo." }
  { key: PHRASE_sun_temple_congratulations_title, text:			"¡Templo del Sol terminado!" }
  { key: PHRASE_sun_temple_congratulations, text:				"[greeting] [player_name], tras muchos meses de esfuerzo, las obras del Templo del Sol por fin han concluido.  ¡Es un gran logro para tu ciudad!" }
  { key: PHRASE_alex_library_congratulations_title, text:		"¡Biblioteca de Alejandría terminada!" }
  { key: PHRASE_alex_library_congratulations, text:				"[greeting] [player_name], tras mucho trabajo duro, las hermosas puertas labradas a mano de la magnífica Gran Biblioteca de Alejandría están listas para abrirse de par en par a los eruditos del mundo." }
  { key: PHRASE_abu_simbel_congratulations_title, text:			"¡Abu Simbel terminado!" }
  { key: PHRASE_abu_simbel_congratulations, text:				"[greeting] [player_name], tras años de trabajo, los templos de Abu Simbel por fin están completos. ¡Un logro digno de los grandes faraones!" }
  { key: PHRASE_caesareum_congratulations_title, text:			"¡Cesáreo terminado!" }
  { key: PHRASE_caesareum_congratulations, text:				"[greeting] [player_name], ¡por fin el santo templo y los resplandecientes patios ajardinados del Cesáreo están completos! La noticia de su magnífica belleza ya se extiende por toda la región." }
  { key: PHRASE_lighthouse_congratulations_title, text:			"¡Faro de Faros terminado!" }
  { key: PHRASE_lighthouse_congratulations, text:    "[greeting] [player_name], tras mucho sudor y no poca sangre derramada, los obreros han colocado con cuidado el último bloque de mármol del maravilloso Faro de Faros.  Su imponente y brillante baliza ya atrae a mercaderes de todas partes." }
  { key: PHRASE_mausoleum_congratulations_title, text:			"¡Mausoleo terminado!" }
  { key: PHRASE_mausoleum_congratulations, text:				"[greeting] [player_name], ¡el sagrado Mausoleo por fin está completo!  Es un logro notable para tu ciudad." }
  { key: PHRASE_smalltomb_congratulations_title, text:			"¡Tumba funeraria pequeña terminada!" }
  { key: PHRASE_smalltomb_congratulations, text:				"[greeting] [player_name], la construcción de la pequeña Tumba Real está completa.  Ojalá pasen muchos años antes de que tus trabajadores tengan que preparar otra." }
  { key: PHRASE_medtomb_congratulations_title, text:			"¡Tumba funeraria mediana terminada!" }
  { key: PHRASE_medtomb_congratulations, text:				"[greeting] [player_name], por fin la Tumba Real mediana está terminada y totalmente abastecida. Sin duda será un camino ideal hacia el más allá para nuestro difunto faraón." }
  { key: PHRASE_largetomb_congratulations_title, text:			"¡Tumba funeraria grande terminada!" }
  { key: PHRASE_largetomb_congratulations, text:				"[greeting] [player_name], tras muchos años de duro trabajo en las entrañas de la tierra, tus trabajadores han completado la más magnífica tumba funeraria hasta la fecha.  Es verdaderamente un logro maravilloso." }
  { key: PHRASE_grandtomb_congratulations_title, text:			"¡Gran tumba funeraria terminada!" }
  { key: PHRASE_grandtomb_congratulations, text:				"[greeting] [player_name], tras mucho trabajo agotador, la gran Tumba Real está completa, y no llega demasiado pronto, pues según algunos, nuestro estimado faraón está en sus últimos días.  Esta magnífica tumba es perfecta para facilitar su próximo viaje al más allá." }

  { key: PHRASE_troopcarryover_title, text:   "Los Soldados Leales Se Unen a Ti" }
  { key: PHRASE_troopcarryover_initial_announcement, text: "Tus mejores soldados de la misión anterior desean volver a unirse a ti.  Construye [reason_phrase] para estos guerreros y regresarán." }
  { key: PHRASE_troopcarryover_inf_only, text: "un fuerte de infantería" }
  { key: PHRASE_troopcarryover_arch_only, text: "un fuerte de arqueros" }
  { key: PHRASE_troopcarryover_char_only, text: "un fuerte de carros" }
  { key: PHRASE_troopcarryover_inf_arch, text: "fuertes de infantería y de arqueros" }
  { key: PHRASE_troopcarryover_inf_char, text: "fuertes de infantería y de carros" }
  { key: PHRASE_troopcarryover_arch_char, text: "fuertes de arqueros y de carros" }
  { key: PHRASE_troopcarryover_all_three, text: "fuertes de infantería, de arqueros y de carros" }
  { key: PHRASE_pyramid_speedup_title, text: "Una Bendición para la Construcción" }
  { key: PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] se complace con tu devoción y desea impulsar notablemente tu proyecto de construcción de monumentos.  Es hora de que tus trabajadores se aparten temporalmente mientras se recibe esta generosa bendición del venerado [reason_phrase]." }
  { key: PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] reconoce tu devoción ayudando a tu proyecto de construcción de monumentos.  Es hora de que tus trabajadores descansen un momento mientras llega este benevolente regalo de [reason_phrase]." }
  { key: PHRASE_pyramid_speedup_Osiris, text: "Osiris" }
  { key: PHRASE_pyramid_speedup_Ra, text: "Ra" }
  { key: PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
  { key: PHRASE_pyramid_speedup_Seth, text: "Seth" }
  { key: PHRASE_pyramid_speedup_Bast, text: "Bast" }
]
