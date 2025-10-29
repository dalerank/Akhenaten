log_info("akhenaten: eventmsg enlish started")

eventmsg_en = [
  { key:PHRASE_egyptian_city_attacked_title_P, text: "Egyptian City Under Attack" }
  { key:PHRASE_egyptian_city_attacked_title_C, text: "Egyptian City Under Attack" }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: 	"[greeting] [player_name],[reason_phrase] infidels are attacking. All-powerful Pharaoh orders you to send troops to the Egyptian city of [city_name] to battle the foe.  You should dispatch troops within [travel_time] months." }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: 	"[greeting] [player_name], [reason_phrase] [city_name], an Egyptian city, is under attack, and needs your help. You should dispatch troops within [travel_time] months." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_P, text: 	"[greeting] [player_name], the divine Pharaoh's armies are still battling aggressors at [city_name].  Dispatch reinforcements within the next six months, or risk incurring Pharaoh's wrath." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_C, text: 	"[greeting] [player_name], have you forgotten [city_name]? Send troops witin the next six months, or the consequences could be dire." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_P, text: 	"[greeting] [player_name], Pharaoh grows impatient waiting for your troops.  Send troops to [city_name] soon, or it will be too late." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_C, text: 	"[greeting] [player_name], [city_name] may soon lose to its enemies.  Send troops quickly if you want to help [city_name] in its hour of need." }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "because your troops vanquished Pharaoh's enemies at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "your troops vanquished Pharaoh's enemies at [city_name].  Incidentally," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "although your troops vanquished Pharaoh's enemies at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "because your troops capably dispatched the foe at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "your troops capably dispatched the foe at [city_name].  Additionally," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "although your troops capably dispatched the foe at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "because you dallied in sending your troops to help Pharaoh's army battle the foe at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "Pharaoh's army lost the battle at [city_name], because your troops arrived too late,.  Also," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "your troops arrived too late to help Pharaoh's army battle the foe at [city_name], but your effort was not unappreciated.  As a result" }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "because you waited too long to send your troops to defend [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "your troops did not arrive in time to help defend [city_name].  Also," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "your troops arrived too late to help [city_name], but since you made the effort, and were willing to sacrifice your own soldiers," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "because you denied Pharaoh the troops he needed to fight the enemy at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "Pharaoh has learned that you refused to send the troops he needed to fight the enemy at [city_name].  In addition," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "although you denied Pharaoh the troops he needed to fight the enemy at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "because you refused to send the requested troops to defeat the marauders at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: 	"[city_name] despairs that you have refused to send the requested troops to defeat their enemies.  Also," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "although you refused to send the requested troops to defeat the marauders at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "because the troops you sent Pharaoh at [city_name] were too weak to strike down the enemy," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "the weak troops you sent to help Pharaoh were defeated at [city_name].  Also," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "despite the fact that your troops were too weak to help Pharaoh at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "because the troops you sent to [city_name] were not powerful enough to defeat the attackers," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "your weak forces were defeated at [city_name].  In addition," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "although your troops were not victorious at [city_name]," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "to satisfy their urge for more land," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "your troubles are still not over, for" }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: 	"" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "in pursuit of a long-standing feud," }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "your troubles are still not over, for" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: 	"" }

  { key: PHRASE_distant_battle_title_P, text: "Distant Battle" }
  { key: PHRASE_distant_battle_title_C, text: "Distant Battle" }
  { key: PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] the Egyptian army is engaged in a fierce battle. Imperious Pharaoh demands that you send troops to the distant city of [city_name] to enter into the fray. Dispatch troops within [travel_time] months." }
  { key: PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] the Egyptian army is engaged in combat at the distant city of [city_name], and requires you to dispatch reinforcements there.  Send troops to their aid within [travel_time] months." }
  { key: PHRASE_distant_battle_first_reminder_P, text: 	"[greeting] [player_name], the bloody battle continues at [city_name], and Pharaoh still needs your troops. Dispatch them within the next six months if they are to arrive in time. Failure to do so could be costly. " }
  { key: PHRASE_distant_battle_first_reminder_C, text: 	"[greeting] [player_name], the battle for [city_name] rages on. Dispatch troops within the next six months if they are to arrive in time.  This could be your chance to share in a glorious victory." }
  { key: PHRASE_distant_battle_last_reminder_P, text: 	"[greeting] [player_name], the Egyptian army still wages war at [city_name], and noble Pharaoh demands that you send reinforcements very soon. Do not anger Pharaoh while he is in the mood to fight." }
  { key: PHRASE_distant_battle_last_reminder_C, text: 	"[greeting] [player_name], the battle for [city_name] continues. If you dispatch troops to their aid very soon, Egypt may yet win a glorious victory." }
  { key: PHRASE_distant_battle_comply_reason_P_A, text: "because Pharaoh's victory at [city_name] depended upon your troops," }
  { key: PHRASE_distant_battle_comply_reason_P_B, text: "your troops helped Pharaoh achieve victory at [city_name].  Oh, and one more thing," }
  { key: PHRASE_distant_battle_comply_reason_P_C, text: "even though your troops helped Pharaoh achieve victory at [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_A, text: "because your troops helped win the day at [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_B, text: "your troops proved vital to winning the day at [city_name].  Also," }
  { key: PHRASE_distant_battle_comply_reason_C_C, text: "although your troops proved vital to winning the day at [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_A, text: "because your troops were not in time to help Pharaoh at [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_B, text: "your troops were not in time to help Pharaoh at [city_name].  In addition," }
  { key: PHRASE_distant_battle_too_late_reason_P_C, text: "although your troops were too late to help Pharaoh at [city_name], your willingness to make sacrifices for the kingdom is greatly appreciated.  As a result," }
  { key: PHRASE_distant_battle_too_late_reason_C_A, text: "because your troops were too late to help fight the Battle of [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_C_B, text: "your troops were too late to help fight the Battle of [city_name].  Furthermore," }
  { key: PHRASE_distant_battle_too_late_reason_C_C, text: "although your troops were too late to help fight the Battle of [city_name], your willingness to make sacrifices for the kingdom is greatly appreciated.  As a result," }
  { key: PHRASE_distant_battle_refuse_reason_P_A, text: "because you blatantly denied Pharaoh's request to send troops to help his army at [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_P_B, text: "you blatantly denied Pharaoh's request to send troops to help his army at [city_name].  This was unwise, but in any event," }
  { key: PHRASE_distant_battle_refuse_reason_P_C, text: "although you denied Pharaoh's request for troops to help his army at [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_C_A, text: "because you refused to send the needed troops to the battle at [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_C_B, text: "you refused to send the needed troops to the battle at [city_name], which was unfortunate for them.  Incidentally," }
  { key: PHRASE_distant_battle_refuse_reason_C_C, text: "although you refused to send the needed troops to the battle at [city_name]," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_A, text: "because the troops you sent to [city_name] were too feeble to combat Pharaoh's adversary," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_B, text: "the troops you sent to [city_name] were defeated by Pharaoh's enemy.  Additionally," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_C, text: "although the troops you sent to [city_name] were defeated by Pharaoh's enemy," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_A, text: "because the troops you sent to [city_name] lacked strength and sinew to dispatch the enemy," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_B, text: "the troops you sent to [city_name] lacked strength and sinew to dispatch our nemesis.  Also be aware that" }
  { key: PHRASE_distant_battle_lost_battle_reason_C_C, text: "although the troops you sent to [city_name] were not able to dispatch the enemy," }
  { key: PHRASE_distant_battle_no_reason_P_A, text: "heed the battle cry, for"			 }
  { key: PHRASE_distant_battle_no_reason_P_B, text: "our troubles continue" }
  { key: PHRASE_distant_battle_no_reason_P_C, text: 	"" }
  { key: PHRASE_distant_battle_no_reason_C_A, text: "alert your soldiers, for" }
  { key: PHRASE_distant_battle_no_reason_C_B, text: "the trouble is not over, for" }
  { key: PHRASE_distant_battle_no_reason_C_C, text: 	"" }

  { key:PHRASE_general_request_title_P, text:"Pharaoh Requests Goods" }
  { key:PHRASE_general_request_title_C, text:"A City Requests Goods" }
  { key:PHRASE_general_request_initial_announcement_P,text:	"[greeting] [player_name], [reason_phrase] matchless Pharaoh wants you to send [amount] [item] to [city_name] within [time_allotted] months. Complying with the request could earn Pharaoh's esteem." }
  { key:PHRASE_general_request_initial_announcement_C,text:	"[greeting] [player_name], [reason_phrase] the city of [city_name] requests that you send [amount] [item] in [time_allotted] months. Helping [city_name] could bring us benefits later." }
  { key:PHRASE_general_request_reminder_P, text:	"[greeting] [player_name], Pharaoh wonders why [city_name] has not received [amount] [item].  You have 6 months left to comply with Pharaoh's request." }
  { key:PHRASE_general_request_reminder_C, text:	"[greeting] [player_name], [city_name] anxiously awaits the arrival of [amount] [item].  You have 6 months left to comply." }
  { key:PHRASE_general_request_overdue_P, text:	"[greeting] [player_name], do you want to provoke Pharaoh? You did not send [amount] [item] to [city_name] in time. Even a belated attempt at fulfilling this request may appease Pharaoh somewhat." }
  { key:PHRASE_general_request_overdue_C, text:	"[greeting] [player_name], your time has run out, and you still have not sent the [amount] [item] to [city_name] as they requested. Even a belated attempt at fulfilling this request may satisfy [city_name] somewhat." }
  { key:PHRASE_general_request_warning_P, text:	"[greeting] [player_name], you have only six months left to fulfill Pharaoh's request that you send [amount] [item] to [city_name]. Deny him at your peril." }
  { key:PHRASE_general_request_warning_C, text:	"[greeting] [player_name], send [city_name] [amount] [item] within six months, or risk making enemies out of neighbors." }
  { key:PHRASE_general_request_comply_reason_P_A, text:"because you satisfied Pharaoh's request that [amount] [item] be sent to [city_name]," }
  { key:PHRASE_general_request_comply_reason_P_B, text:"you satisfied Pharaoh's request that [amount] [item] be sent to [city_name].  By the way," }
  { key:PHRASE_general_request_comply_reason_P_C, text:"you did satisfy Pharaoh's request that [amount] [item] be sent to [city_name], however," }
  { key:PHRASE_general_request_comply_reason_C_A, text:"because you have sent [amount] [item] to [city_name], as they requested," }
  { key:PHRASE_general_request_comply_reason_C_B, text:	"[city_name] received the [amount] [item] as they requested.  You should also know that" }
  { key:PHRASE_general_request_comply_reason_C_C, text:"even though you sent [amount] [item] to [city_name], as they requested," }
  { key:PHRASE_general_request_too_late_reason_P_A, text:"because you delayed fulfilling Pharaoh's request for [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_P_B, text:"Pharaoh's request for [amount] [item] was unfulfilled because you were too late.  Additionally," }
  { key:PHRASE_general_request_too_late_reason_P_C, text:"you delayed fulfilling Pharaoh's request for [amount] [item], but nevertheless your effort was appreciated.  As a result," }
  { key:PHRASE_general_request_too_late_reason_C_A, text:"because you were tardy in fulfilling the request of [city_name] for [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_C_B, text:"you were tardy in delivering [amount] [item] to [city_name].  You should also be aware that" }
  { key:PHRASE_general_request_too_late_reason_C_C, text:"despite the fact that you were tardy in delivering [amount] [item] to [city_name], your effort was appreciated.  As a result," }
  { key:PHRASE_general_request_refuse_reason_P_A, text:"because you ignored Pharaoh's request for [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_P_B, text:"you ignored Pharaoh's request for [amount] [item], and he will not be pleased.  Additionally," }
  { key:PHRASE_general_request_refuse_reason_P_C, text:"even though you ignored Pharaoh's request for [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_C_A, text:"because you did not send [amount] [item] to [city_name]," }
  { key:PHRASE_general_request_refuse_reason_C_B, text:"you failed to send [amount] [item] to [city_name], and they do not appreciate this.  Meanwhile," }
  { key:PHRASE_general_request_refuse_reason_C_C, text:"despite the fact that you failed to send [amount] [item] to [city_name]," }
  { key:PHRASE_general_request_no_reason_P_A, text:"to supplement his estate's stocks," 			 }
  { key:PHRASE_general_request_no_reason_P_B, text:"there seems to be no end to Pharaoh's greed, for" }
  { key:PHRASE_general_request_no_reason_P_C, text:	"" }
  { key:PHRASE_general_request_no_reason_C_A, text:"to satisfy citizens' needs," }
  { key:PHRASE_general_request_no_reason_C_B, text:"there seems to be no end to this, for" }
  { key:PHRASE_general_request_no_reason_C_C, text:	"" }

  { key: PHRASE_great_festival_title_P, text: "Festival to [god]" }
  { key: PHRASE_great_festival_title_C, text: "Great Festival to [god]" }
  { key: PHRASE_great_festival_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] Pharaoh is planning a Great Festival to [god] in [city_name] and needs goods from your city. You have [time_allotted] months to send [amount] [item]." }
  { key: PHRASE_great_festival_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] the city of [city_name] requests that you send [amount] [item] for a Great Festival to [god]. The city requires these goods within [time_allotted] months." }
  { key: PHRASE_great_festival_reminder_P, text: "[greeting] [player_name], you have six months left to send [amount] [item] to [city_name] for the Great Festival to [god]. Pharaoh will be displeased if you do not comply with his request." }
  { key: PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], the Great Festival to [god] in [city_name] fast approaches, and you have not sent the [amount] [item]. You have 6 months left to send goods." }
  { key: PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], you missed your deadline, and Pharaoh had to hold the Great Festival to [god] without your supplies. Send [amount] [item] to [city_name] anyway, and the incensed Pharaoh may yet find a measure of forgiveness." }
  { key: PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] is displeased that they had to procure goods from elsewhere for their Great Festival to [god]. You might gain some measure of acceptance if you still try to send the [amount] [item]." }
  { key: PHRASE_great_festival_warning_P, text: "[greeting] [player_name], you have only 6 months left to send Pharaoh [amount] [item] to [city_name] that he needed for the Great Festival to [god]. Woe be to the one who feels the heat of Pharaoh's fiery rage!" }
  { key: PHRASE_great_festival_warning_C, text: "[greeting] [player_name], [city_name] is frustrated with you. Send [amount] [item] in the next 6 months if you are to have any hope of maintaining good relations." }
  { key: PHRASE_great_festival_comply_reason_P_A, text: "because you honored Pharaoh and [god] by sending [amount] [item] to [city_name] in time for the Great Festival," }
  { key: PHRASE_great_festival_comply_reason_P_B, text: "you graciously honored Pharaoh and [god] by sending [amount] [item] to [city_name] in time for the Great Festival.  Also," }
  { key: PHRASE_great_festival_comply_reason_P_C, text: "although you graciously honored Pharaoh and [god] by sending [amount] [item] to [city_name] in time for the Great Festival," }
  { key: PHRASE_great_festival_comply_reason_C_A, text: "because you helped [city_name] celebrate its Great Festival to [god] by sending [amount] [item]," }
  { key: PHRASE_great_festival_comply_reason_C_B, text: "you helped [city_name] celebrate its Great Festival to [god] by sending [amount] [item], which was much appreciated.  Additionally," }
  { key: PHRASE_great_festival_comply_reason_C_C, text: "although you helped [city_name] celebrate its Great Festival to [god] by sending [amount] [item]," }
  { key: PHRASE_great_festival_too_late_reason_P_A, text: "because you sent [amount] [item] too late for Pharaoh's Great Festival to [god] at [city_name]," }
  { key: PHRASE_great_festival_too_late_reason_P_B, text: "you sent [amount] [item] too late for Pharaoh's Great Festival to [god] at [city_name].  Additionally," }
  { key: PHRASE_great_festival_too_late_reason_P_C, text: "even though the [amount] [item] arrived too late for Pharaoh's Great Festival to [god] at [city_name], since you made the effort," }
  { key: PHRASE_great_festival_too_late_reason_C_A, text: "because the [amount] [item] required by [city_name] for the Great Festival to [god] did not arrive in time," }
  { key: PHRASE_great_festival_too_late_reason_C_B, text: "the [amount] [item] required by [city_name] for the Great Festival to [god] did not arrive in time.  Also," }
  { key: PHRASE_great_festival_too_late_reason_C_C, text: "even though the [amount] [item] you sent to [city_name] did not arrive in time for the Great Festival to [god], since you did your best," }
  { key: PHRASE_great_festival_refuse_reason_P_A, text: "because you neglected to fulfill Pharaoh's request for [amount] [item] for the Great Festival to [god] at [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_P_B, text: "you neglected to fulfill Pharaoh's request for [amount] [item] for the Great Festival to [god] at [city_name].  Also," }
  { key: PHRASE_great_festival_refuse_reason_P_C, text: "despite your failure in fulfilling Pharaoh's request for [amount] [item] for the Great Festival to [god] at [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_C_A, text: "because you disregarded [city_name] and its request for [amount] [item] for the Great Festival to [god]," }
  { key: PHRASE_great_festival_refuse_reason_C_B, text: "you disregarded [city_name] and its request for [amount] [item] for the Great Festival to [god].  Also," }
  { key: PHRASE_great_festival_refuse_reason_C_C, text: "although you disregarded [city_name] and its request for [amount] [item] for the Great Festival to [god]," }
  { key: PHRASE_great_festival_no_reason_P_A, text: "because Pharaoh seeks to honor the deity," }
  { key: PHRASE_great_festival_no_reason_P_B, text: "because [god] is still dissatisfied," }
  { key: PHRASE_great_festival_no_reason_P_C, text:  "" }
  { key: PHRASE_great_festival_no_reason_C_A, text: "because [city_name] is blessed by [god]," }
  { key: PHRASE_great_festival_no_reason_C_B, text: "because [god] is still dissatisfied," }
  { key: PHRASE_great_festival_no_reason_C_C, text:  "" }

  { key: PHRASE_project_title_P, text: 						"Construction for Pharaoh" }
  { key: PHRASE_project_title_C, text: 						"Construction Project" }
  { key: PHRASE_project_initial_announcement_P, text:		"[greeting] [player_name], [reason_phrase] Pharaoh is building something so massive that he needs you to send [amount] [item] to [city_name] within [time_allotted] months. Whatever the project is, it is sure to add to Egypt's glory." }
  { key: PHRASE_project_initial_announcement_C, text:		"[greeting] [player_name], [reason_phrase] the city of [city_name] requests that you send [amount] [item] within [time_allotted] months for a major construction project in the city." }
  { key: PHRASE_project_reminder_P, text: 					"[greeting] [player_name], Pharaoh is about to fly into a rage. You still have not sent the [amount] [item] to [city_name] for his construction project. You have 6 months to comply with Pharaoh's request." }
  { key: PHRASE_project_reminder_C, text: 					"[greeting] [player_name], [city_name] needs [amount] [item] if it is to complete its construction project. Send the supplies within 6 months, or the city's leaders may become disgruntled." }
  { key: PHRASE_project_overdue_P, text: 					"[greeting] [player_name], Pharaoh is disgusted with your insolence. You did not send [amount] [item] to [city_name] in time for him to complete his construction project. If you can still manage to send them anyway, you might be able to save face." }
  { key: PHRASE_project_overdue_C, text: 					"[greeting] [player_name], [city_name] is considering reporting you to Pharaoh. Because you did not send [amount] [item] in time, it may not be able to complete its construction project. If you send them anyway, [city_name] may yet be able to finish this project, and might keep quiet about your inaction." }
  { key: PHRASE_project_warning_P, text: 					"[greeting] [player_name], an incomplete project will only embarrass Pharaoh. You have 6 months left to send [amount] [item] to [city_name] for his construction project. If you fail him, Pharaoh will share his shame with you." }
  { key: PHRASE_project_warning_C, text: 					"[greeting] [player_name], you have only 6 months left to send [amount] [item] to [city_name] for their construction project. If you don't send the goods, there's no telling what the city might do in retaliation." }
  { key: PHRASE_project_comply_reason_P_A, text:  	  		"because the [amount] [item] you sent were essential to the timely completion of Pharaoh's construction project in [city_name]," }
  { key: PHRASE_project_comply_reason_P_B, text:	  		"the [amount] [item] you sent were essential to the timely completion of Pharaoh's construction project in [city_name].  Also," }
  { key: PHRASE_project_comply_reason_P_C, text:	  		"even though the [amount] [item] you sent were essential to the timely completion of Pharaoh's construction project in [city_name]," }
  { key: PHRASE_project_comply_reason_C_A, text:  	  			"because you helped [city_name] successfully complete its project on schedule by sending [amount] [item]," }
  { key: PHRASE_project_comply_reason_C_B, text:	  "you helped [city_name] to keep its project on schedule by sending [amount] [item].  Incidentally," }
  { key: PHRASE_project_comply_reason_C_C, text:	  "although you helped [city_name] successfully complete its project on schedule by sending [amount] [item]," }
  { key: PHRASE_project_too_late_reason_P_A, text:   "because you stalled Pharaoh's construction project at [city_name] by waiting too long to send [amount] [item]," }
  { key: PHRASE_project_too_late_reason_P_B, text:	  "Pharaoh's construction project at [city_name] has stalled because you waited too long to send the [amount] [item] he asked for.  Also," }
  { key: PHRASE_project_too_late_reason_P_C, text:	  "despite the fact that you stalled Pharaoh's construction project at [city_name] by waiting too long to send [amount] [item], your effort was appreciated, and so" }
  { key: PHRASE_project_too_late_reason_C_A, text:  	"because you procrastinated and did not send [city_name] [amount] [item]," }
  { key: PHRASE_project_too_late_reason_C_B, text:	  "you procrastinated in sending [city_name] the [amount] [item] they needed.  Incidentally" }
  { key: PHRASE_project_too_late_reason_C_C, text:	  "even though you procrastinated in sending [city_name] the [amount] [item] they needed, your effort was appreciated, and so" }
  { key: PHRASE_project_refuse_reason_P_A, text:	"because you declined Pharaoh's request for [amount] [item] for his important project at {city_name]," }
  { key: PHRASE_project_refuse_reason_P_B, text:	  "you unwisely declined Pharaoh's request for [amount] [item] for his important project at {city_name].  Also," }
  { key: PHRASE_project_refuse_reason_P_C, text:	  "although it was unwise to decline Pharaoh's request for [amount] [item] for his important project at {city_name] as you did," }
  { key: PHRASE_project_refuse_reason_C_A, text: 	"because you spurned [city_name] and their request for [amount] [item]," }
  { key: PHRASE_project_refuse_reason_C_B, text:	  "you have spurned [city_name] and their request for [amount] [item].  Additionally," }
  { key: PHRASE_project_refuse_reason_C_C, text:	  "though you spurned [city_name] and their request for [amount] [item]," }
  { key: PHRASE_project_no_reason_P_A, text:  	 	"to celebrate his many achievements," }
  { key: PHRASE_project_no_reason_P_B, text:	  "because there is still much work to be done" }
  { key: PHRASE_project_no_reason_P_C, text:	  "" }
  { key: PHRASE_project_no_reason_C_A, text:  	  "to honor the glory of Egypt," }
  { key: PHRASE_project_no_reason_C_B, text:	  "because there is still much to be done" }
  { key: PHRASE_project_no_reason_C_C, text:	  "" }

  { key:PHRASE_famine_title_P, text: 					"Famine" }
  { key:PHRASE_famine_title_C, text: 					"Famine" }
  { key:PHRASE_famine_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] famine grips [city_name]. Pharaoh requires you to provide succor. You have [time_allotted] to send [amount] [item] to the city to ease its suffering." }
  { key:PHRASE_famine_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] famine has struck [city_name], and its people are starving. Send [amount] [item] within [time_allotted] months. Lives are at stake!" }
  { key:PHRASE_famine_reminder_P, text: 				"[greeting] [player_name], Pharaoh questions whether or not you have a heart.  You still have not sent the [amount] [item] to [city_name], and its people are in need. You only have 6 months left to comply with Pharaoh's request." }
  { key:PHRASE_famine_reminder_C, text: 				"[greeting] [player_name], the people of [city_name] are wailing with hunger, and you still have not sent the [amount] [item]. Send the supplies within 6 months, or wails of hunger will be replaced with laments for the dead." }
  { key:PHRASE_famine_overdue_P, text: 				"[greeting] [player_name], Pharaoh thinks you are as mean as an asp. You have done nothing to alleviate your compatriots' hunger. You can still send [amount] [item] to [city_name] and stand a chance of rehabilitating your image in Pharaoh's eyes." }
  { key:PHRASE_famine_overdue_C, text: 				"[greeting] [player_name], the pitiful cries of starvation have apparently fallen on deaf ears. You did not sent the [amount] [item] to [city_name] in time. Better late than never...if you send the food anyway, you may yet provide some relief, if there is anyone left to benefit from it." }
  { key:PHRASE_famine_warning_P, text: 				"[greeting] [player_name], if you do not send [amount] [item] to [city_name] within 6 months, you will do no good at all. Pharaoh will frown upon your unkindness if you neglect to send the goods." }
  { key:PHRASE_famine_warning_C, text: 				"[greeting] [player_name], the people of [city_name] wonder if your heart is cruel.  You have only 6 months left to send [amount] [item] to ease their suffering. Deny them, and their deaths will be on your head." }
  { key:PHRASE_famine_comply_reason_P_A, text:  			"because you quickly sent [amount] [item] in response to the needs of [city_name], as Pharaoh ordered," }
  { key:PHRASE_famine_comply_reason_P_B, text:	  		"you quickly sent [amount] [item] in response to the needs of [city_name], as Pharaoh ordered.  This was wise.  Now," }
  { key:PHRASE_famine_comply_reason_P_C, text:	  "though you were prompt in sending the [amount] [item] in response to the needs of [city_name], as Pharaoh ordered, still" }
  { key:PHRASE_famine_comply_reason_C_A, text: 	"because the [amount] [item] you sent filled the bellies of [city_name] during the famine," }
  { key:PHRASE_famine_comply_reason_C_B, text:	  "the [amount] [item] you sent to [city_name] filled the bellies of its people during the famine.  Additionally, viziers report that" }
  { key:PHRASE_famine_comply_reason_C_C, text:	  "though the [amount] [item] you sent to the people of [city_name] helped them cope with the recent famine, still" }
  { key:PHRASE_famine_too_late_reason_P_A, text:	"because you allowed Pharaoh's people at [city_name] to suffer too long by waiting to send [amount] [item]," }
  { key:PHRASE_famine_too_late_reason_P_B, text:	  "you allowed Pharaoh's people at [city_name] to suffer too long by waiting to send the [amount] [item] they needed.  Also, viziers report that" }
  { key:PHRASE_famine_too_late_reason_P_C, text:	  "although you allowed Pharaoh's people at [city_name] to suffer too long by waiting to send the [amount] [item] they needed, it did prove to be of some help, and so" }
  { key:PHRASE_famine_too_late_reason_C_A, text:  	 	"because you took too long to dispatch [amount] [item] to provide relief to the people of [city_name]," }
  { key:PHRASE_famine_too_late_reason_C_B, text:	  "you took far too long to dispatch [amount] [item] to provide relief to the people of [city_name], and their suffering was great.  On top of that," }
  { key:PHRASE_famine_too_late_reason_C_C, text:	  "although you took too long to dispatch [amount] [item] to the people of [city_name], the food did help alleviate the after effects of the famine somewhat, and so" }
  { key:PHRASE_famine_refuse_reason_P_A, text:  	 	"because you shunned Pharaoh and his people at [city_name] during the famine by denying to send [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_P_B, text:	  "you shunned Pharaoh and his people at [city_name] during the famine by denying to send [amount] [item].  This was unwise.  Also, viziers report that" }
  { key:PHRASE_famine_refuse_reason_P_C, text:	  "you shunned Pharaoh and his people at [city_name], during the famine by denying to send [amount] [item], but despite this" }
  { key:PHRASE_famine_refuse_reason_C_A, text:			"because you turned your back on the people of [city_name] during the famine and withheld [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_C_B, text:	  "you turned your back on the people of [city_name] during the famine and withheld [amount] [item].  Viziers also report that" }
  { key:PHRASE_famine_refuse_reason_C_C, text:	  "even though you turned your back on the people of [city_name] during the famine and withheld [amount] [item]," }
  { key:PHRASE_famine_no_reason_P_A, text:  	 	"Fortune frowns on Pharaoh's people, and" }
  { key:PHRASE_famine_no_reason_P_B, text:	  "troubles continue to mount, as" }
  { key:PHRASE_famine_no_reason_P_C, text:	  "" }
  { key:PHRASE_famine_no_reason_C_A, text:  	"the people of [city_name] are losing hope, for" }
  { key:PHRASE_famine_no_reason_C_B, text:	  "troubles continue to mount, as" }
  { key:PHRASE_famine_no_reason_C_C, text:	  "" }

  { key:PHRASE_threat_title_P, text: 					"Extortion by Pharaoh" }
  { key:PHRASE_threat_title_C, text: 					"Extortion by another city" }
  { key:PHRASE_threat_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] Pharaoh orders you to send [amount] [item] to [city_name] in [time_allotted] months. Otherwise, he will attack your fair city." }
  { key:PHRASE_threat_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] the city of [city_name] demands that you send [amount] [item] in [time_allotted] months. If you deny the request, [city_name] will send its armies against your fair city." }
  { key:PHRASE_threat_reminder_P, text: 				"[greeting] [player_name], prideful Pharaoh is rallying his troops and will soon order them to attack. You should send the [amount] [item] to [city_name] within 6 months to avert the unpleasantries." }
  { key:PHRASE_threat_reminder_C, text: 				"[greeting] [player_name], the army of [city_name] girds for war, anticipating a good fight. If you send the [amount] [item] within 6 months, the city will cease its aggression. Its soldiers, though, will be quite disappointed." }
  { key:PHRASE_threat_overdue_P, text: 				"[greeting] [player_name], your time has run out, and Pharaoh thirsts for blood. You may still have a chance to keep his forces at bay if you send the [amount] [item] to [city_name] as soon as you can." }
  { key:PHRASE_threat_overdue_C, text: 				"[greeting] [player_name], battle cries can be heard throughout [city_name] as it prepares to destroy your city. Send the [amount] [item] to [city_name] as soon as you can, and they may show some mercy." }
  { key:PHRASE_threat_warning_P, text: 				"[greeting] [player_name], vainglorious Pharaoh is eager to take by force what you would not willingly give him. His army is well-prepared, but you can save your city from carnage if you send him [amount] [item] within 6 months. Otherwise, prepare your people for bloodshed." }
  { key:PHRASE_threat_warning_C, text: 				"[greeting] [player_name], the conquering forces of [city_name] are ready to march. If you send [amount] [item] within 6 months, the attacking forces may leave your city unharmed." }
  { key:PHRASE_threat_comply_reason_P_A, text: 			"because you gave in to Pharaoh and sent [amount] [item] to [city_name]," }
  { key:PHRASE_threat_comply_reason_P_B, text:	  "you have given in to Pharaoh and sent [amount] [item] to regarding [city_name].  Also, viziers report that" }
  { key:PHRASE_threat_comply_reason_P_C, text:	  "even though you have done what Pharaoh demanded for [city_name]," }
  { key:PHRASE_threat_comply_reason_C_A, text:  "because you bowed to the orders of [city_name] and sent [amount] [item]," }
  { key:PHRASE_threat_comply_reason_C_B, text:	  "you bowed to the orders of [city_name] and sent [amount] [item].  Additionally, it seems that" }
  { key:PHRASE_threat_comply_reason_C_C, text:	  "even though you gave into the demands of [city_name] for [amount] [item], nevertheless" }
  { key:PHRASE_threat_too_late_reason_P_A, text:  	 "the delay in sending [amount] [item] to [city_name] as Pharaoh demanded tries his patience, and because of this" }
  { key:PHRASE_threat_too_late_reason_P_B, text:	  "the delay in sending [amount] [item] to [city_name] as Pharaoh demanded tries his patience.  On to other matters:" }
  { key:PHRASE_threat_too_late_reason_P_C, text:	  "the delay in sending [amount] [item] to [city_name] as Pharaoh demanded tries his patience, but nevertheless, your effort is appreciated.  Therefore" }
  { key:PHRASE_threat_too_late_reason_C_A, text: 		"because you underestimated the threat of [city_name] and did not dispatch [amount] [item] quickly," }
  { key:PHRASE_threat_too_late_reason_C_B, text:	  "you must have underestimated the threat of [city_name], since you did not dispatch [amount] [item] quickly.  But that's in the past, now" }
  { key:PHRASE_threat_too_late_reason_C_C, text:	  "you took great chances by not promptly dispatching the [amount] [item] to [city_name] as they demanded. Nevertheless, since you did manage to comply," }
  { key:PHRASE_threat_refuse_reason_P_A, text:		"because you defied Pharaoh's order to send [amount] [item] to [city_name]," }
  { key:PHRASE_threat_refuse_reason_P_B, text:	  "you defied Pharaoh's order to send [amount] [item] to [city_name].  Additionally," }
  { key:PHRASE_threat_refuse_reason_P_C, text:	  "despite your refusal to heed Pharaoh's threat, demanding that you send [amount] [item] to [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_A, text:		"because you knowingly courted danger when you refused to send [amount] [item] to [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_B, text:	  "you knowingly courted danger when you refused to send [amount] [item] to [city_name].  You should also be aware that" }
  { key:PHRASE_threat_refuse_reason_C_C, text:	  "although you certainly courted danger when you refused to send [amount] [item] to [city_name]," }
  { key:PHRASE_threat_no_reason_P_A, text:  	 	"because he is in a foul mood," }
  { key:PHRASE_threat_no_reason_P_B, text:	  "as Pharaoh's foul mood seems to be without end," }
  { key:PHRASE_threat_no_reason_P_C, text:	  "" }
  { key:PHRASE_threat_no_reason_C_A, text:  	 	 				"because [city_name] lusts for glory," }
  { key:PHRASE_threat_no_reason_C_B, text:	  "it seems [city_name] shall never be satisfied," }
  { key:PHRASE_threat_no_reason_C_C, text:	  "" }

  { key:PHRASE_eg_city_falls_title, text: 						"Egyptian City Falls" }
  { key:PHRASE_eg_city_falls_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] the mighty city of [city_name] has fallen to our enemies." }
  { key:PHRASE_eg_city_falls_reason_A, text:  	 					"because [city_name] has fallen to invading forces," }
  { key:PHRASE_eg_city_falls_reason_B, text:	  "[city_name] has fallen to invading forces.  What's more," }
  { key:PHRASE_eg_city_falls_reason_C, text:	  "even though [city_name] has fallen to invading forces," }
  { key:PHRASE_eg_city_falls_no_reason_A, text:  		"woe is [city_name]:" }
  { key:PHRASE_eg_city_falls_no_reason_B, text:	  "it seems the troubles in [city_name] will never end, for" }
  { key:PHRASE_eg_city_falls_no_reason_C, text:	  "" }

  { key:PHRASE_foreign_city_conquered_title, text: 					"Foreign City Conquered" }
  { key:PHRASE_foreign_city_conquered_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] Egypt has successfully conquered the renowned city of [city_name], expanding our influence still further!" }
  { key:PHRASE_foreign_city_conquered_reason_A, text: 				"because the foreign city of [city_name] has been subjugated by our troops," }
  { key:PHRASE_foreign_city_conquered_reason_B, text:	  "the foreign city of [city_name] has been subjugated by our troops!  Now," }
  { key:PHRASE_foreign_city_conquered_reason_C, text:	  "even though the foreign city of [city_name] has been subjugated by our troops," }
  { key:PHRASE_foreign_city_conquered_no_reason_A, text:  	"because of our strength in arms," }
  { key:PHRASE_foreign_city_conquered_no_reason_B, text:	  "the strength of our kingdom continues to grow.  Now" }
  { key:PHRASE_foreign_city_conquered_no_reason_C, text:	  "" }

  { key:PHRASE_route_opened_title, text: 						"New Trade Route Available" }
  { key:PHRASE_route_opened_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] a new trade route, to [city_name] can now be opened." }
  { key:PHRASE_route_opened_reason_A, text:  	 				"because a new trade route to [city_name] has become available," }
  { key:PHRASE_route_opened_reason_B, text:	  				"a new trade route to [city_name] has become available, and" }
  { key:PHRASE_route_opened_reason_C, text:	  				"even though trade has become possible with [city_name]," }
  { key:PHRASE_route_opened_no_reason_A, text:  	 			"due to diplomatic activity," }
  { key:PHRASE_route_opened_no_reason_B, text:	  "change is in the air, for" }
  { key:PHRASE_route_opened_no_reason_C, text:	  "" }

  { key:PHRASE_route_closed_title, text:  					"Trade Route Closes" }
  { key:PHRASE_route_closed_initial_announcement, text:     "[greeting] [player_name], [reason_phrase] the trade route to [city_name] has been shut down." }
  { key:PHRASE_route_closed_reason_A, text:   	 					"because the trade route to [city_name] has closed," }
  { key:PHRASE_route_closed_reason_B, text: 	  "the trade route to [city_name] has closed, and what's more," }
  { key:PHRASE_route_closed_reason_C, text: 	  "although the trade route to [city_name] has closed," }
  { key:PHRASE_route_closed_no_reason_A, text:   	 				"because of political instability," }
  { key:PHRASE_route_closed_no_reason_B, text: 	  "..this should have been forseen.  It seems" }
  { key:PHRASE_route_closed_no_reason_C, text: 	  "" }

  { key:PHRASE_trade_city_siege_title, text:  							"Trade City Under Siege" }
  { key:PHRASE_trade_city_siege_announcement, text: 			"[greeting] [player_name], [reason_phrase] a debilitating siege now strikes at [city_name]." }
  { key:PHRASE_trade_city_siege_reason_A, text:   						"because [city_name] is under siege," }
  { key:PHRASE_trade_city_siege_reason_B, text: 	  "[city_name] is under siege, and" }
  { key:PHRASE_trade_city_siege_reason_C, text: 	  "even though [city_name] is under siege," }
  { key:PHRASE_trade_city_siege_no_reason_A, text:   		"military scouts have terrible news to report.  It seems" }
  { key:PHRASE_trade_city_siege_no_reason_B, text: 	  "there is no apparent end to their troubles, for" }
  { key:PHRASE_trade_city_siege_no_reason_C, text: 	  "" }

  { key:PHRASE_eg_city_saved_title, text: 					"Egyptian City Saved" }
  { key:PHRASE_eg_city_saved_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [city_name] has been saved from our enemies. " }
  { key:PHRASE_eg_city_saved_reason_A, text:  	 				"because [city_name] has been saved from our enemies," }
  { key:PHRASE_eg_city_saved_reason_B, text:	  "[city_name] has been saved from our enemies!  Now," }
  { key:PHRASE_eg_city_saved_reason_C, text:	  "even though [city_name] has been saved from our enemies," }
  { key:PHRASE_eg_city_saved_no_reason_A, text:  			"due to a valiant effort on the part of the Egyptian army," }
  { key:PHRASE_eg_city_saved_no_reason_B, text:	  "the tides of war swing back and forth, for now" }
  { key:PHRASE_eg_city_saved_no_reason_C, text:	  "" }

  { key:PHRASE_battle_won_title, text:  					"Victory in Battle" }
  { key:PHRASE_battle_won_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] the Egyptian army was victorious!" }
  { key:PHRASE_battle_won_reason_A, text:   	 		"because our forces triumphed at the distant Battle of [city_name]," }
  { key:PHRASE_battle_won_reason_B, text: 	  "our forces were triumphant at the distant Battle of [city_name].  Now" }
  { key:PHRASE_battle_won_reason_C, text: 	  "even though our forces were triumphant at the Battle of [city_name]" }
  { key:PHRASE_battle_won_no_reason_A, text:   		"due to the vigor of well-trained troops at the distant city of [city_name]," }
  { key:PHRASE_battle_won_no_reason_B, text: 	  "it seems wonders will never cease, for at [city_name]" }
  { key:PHRASE_battle_won_no_reason_C, text: 	  "" }

  { key:PHRASE_battle_lost_title, text:  					"Egyptian Army Defeated" }
  { key:PHRASE_battle_lost_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] the Egyptian army was defeated at [city_name]. " }
  { key:PHRASE_battle_lost_reason_A, text:   	 					"because Egypt lost a battle to her enemies at [city_name]," }
  { key:PHRASE_battle_lost_reason_B, text: 	  "Egypt has lost a battle to her enemies at [city_name].  What's more," }
  { key:PHRASE_battle_lost_reason_C, text: 	  "even though Egypt lost the battle to her enemies at [city_name]," }
  { key:PHRASE_battle_lost_no_reason_A, text:   	"great misfortune has befallen the troops, for" }
  { key:PHRASE_battle_lost_no_reason_B, text: 	  "war is so terribly unpredictable.  Unfortunately" }
  { key:PHRASE_battle_lost_no_reason_C, text: 	  "" }

  { key:PHRASE_acknowledgement_title, text: 					"Compliance Acknowledged" }
  { key:PHRASE_acknowledgement_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] your city is safe...for now." }
  { key:PHRASE_acknowledgement_reason_A, text:  	 			"because you submissively gave in to a threat," }
  { key:PHRASE_acknowledgement_reason_B, text:	  				"you submissively gave in to a threat," }
  { key:PHRASE_acknowledgement_reason_C, text:	  				"even though you submissively gave in to a threat," }
  { key:PHRASE_acknowledgement_no_reason_A, text:				"due to a change of heart," }
  { key:PHRASE_acknowledgement_no_reason_B, text:	  			"nothing is ever certain, but" }
  { key:PHRASE_acknowledgement_no_reason_C, text:	  			"" }

  { key: PHRASE_pharaoh_attacks_you_title, text: 					"Pharaoh's Army Attacks" }
  { key: PHRASE_pharaoh_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] Pharaoh's army is on the move and will reach your city in [time_until_attack] months." }
  { key: PHRASE_pharaoh_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] Pharaoh's army draws ever closer, and will reach your city in two years." }
  { key: PHRASE_pharaoh_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] Pharaoh's army is honed for battle and will reach your city in one year." }
  { key: PHRASE_pharaoh_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] Pharaoh's army is eagerly anticipating attacking you and will reach your city in six months." }
  { key: PHRASE_pharaoh_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] Pharaoh's army is only one month away from reaching the city!." }
  { key: PHRASE_pharaoh_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], Pharaoh's army is upon us!" }
  { key: PHRASE_pharaoh_attacks_you_reason_A, text:  	 	 		"because your city was attacked by Pharaoh's army," }
  { key: PHRASE_pharaoh_attacks_you_reason_B, text:	  				"your city has been attacked by Pharaoh's army.  What's more" }
  { key: PHRASE_pharaoh_attacks_you_reason_C, text:	  				"even though your city has been attacked by Pharaoh's army," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_A, text:  	 		"sometimes Pharaoh acts for reasons only known to him. " }
  { key: PHRASE_pharaoh_attacks_you_no_reason_B, text:	  			"Pharaoh is unpredictable.  Now," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_C, text:	  			"because your standing in the Kingdom has fallen so low," }
  { key: PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text:		"your standing in the Kingdom has fallen completely. Perhaps more gifts to the Egyptian people can yet turn things around, though even now" }

  { key: PHRASE_eg_city_attacks_you_title, text: 					"Egyptian Army Attacks" }
  { key: PHRASE_eg_city_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] an Egyptian army is preparing its attack and will reach your city in [time_until_attack] months." }
  { key: PHRASE_eg_city_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] an Egyptian army has begun its march and will reach your city in two years.				" }
  { key: PHRASE_eg_city_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] your city will suffer the onslaught of an Egyptian army in one year." }
  { key: PHRASE_eg_city_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] an Egyptian army is drawing near and will reach your city in six months.	" }
  { key: PHRASE_eg_city_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] an Egyptian army is approaching your borders and will reach your city in one month." }
  { key: PHRASE_eg_city_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], an invasion force of Egyptian troops is upon us!" }
  { key: PHRASE_eg_city_attacks_you_reason_A, text:  	 	 		"because your city was attacked by Egyptian army," }
  { key: PHRASE_eg_city_attacks_you_reason_B, text:	  				"the Egyptian army has attacked your city!  Additionally" }
  { key: PHRASE_eg_city_attacks_you_reason_C, text:	  				"even though your city has been attacked by the Egyptian army," }
  { key: PHRASE_eg_city_attacks_you_no_reason_A, text:  	 		"beware:" }
  { key: PHRASE_eg_city_attacks_you_no_reason_B, text:	  			"the time for war has come, for" }
  { key: PHRASE_eg_city_attacks_you_no_reason_C, text:	  			"because your reputation in the Kingdom is so low," }
  { key: PHRASE_eg_city_attacks_you_because_of_low_kingdom, text:		"your standing in the Kingdom has fallen completely. Perhaps more gifts to the Egyptian people can yet turn things around, though even now" }

  { key: PHRASE_foreign_army_attacks_you_title, text: 					"Foreign Army Invades" }
  { key: PHRASE_foreign_army_attacks_you_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [a_foreign_army] is approaching and will reach your city in [time_until_attack] months." }
  { key: PHRASE_foreign_army_attacks_you_2year_reminder, text: 			"[greeting] [player_name], [reason_phrase] in two years' time [a_foreign_army] will be at your gates." }
  { key: PHRASE_foreign_army_attacks_you_1year_reminder, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] is eager to invade and will reach your city in one year." }
  { key: PHRASE_foreign_army_attacks_you_6month_warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] will reach your city in six months. Be prepared for their arrival." }
  { key: PHRASE_foreign_army_attacks_you_1month_Warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] will arrive in the city in one month, bent on conquest." }
  { key: PHRASE_foreign_army_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], [a_foreign_army] is upon us, and they are determined to destroy the city!" }
  { key: PHRASE_foreign_army_attacks_you_reason_A, text:  	 	 		"because your city was attacked by [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_reason_B, text:	  			"your city has been attacked by [a_foreign_army], and now" }
  { key: PHRASE_foreign_army_attacks_you_reason_C, text:	  			"although your city has been attacked by [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_A, text:  	 		"because of their dreams of empire," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_B, text:	  "it seems there's always trouble, for" }
  { key: PHRASE_foreign_army_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_rating_change_title_I, text: 					"Kingdom Standing Climbs" }
  { key: PHRASE_rating_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] you have become more popular among your fellow Egyptians, and your Kingdom rating has risen." }
  { key: PHRASE_rating_change_reason_I_A, text:  	 	 		"because your reputation in the Kingdom recently increased," }
  { key: PHRASE_rating_change_reason_I_B, text:	  "your reputation in the Kingdom has improved.  Now" }
  { key: PHRASE_rating_change_reason_I_C, text:	  "your reputation has improved, but" }
  { key: PHRASE_rating_change_no_reason_I_A, text:		"because times are good," }
  { key: PHRASE_rating_change_no_reason_I_B, text:	  "this is good news, for" }
  { key: PHRASE_rating_change_no_reason_I_C, text:	  "your city's sacrifices in combat are greatly appreciated by the Egytian people.  As a result" }
  { key: PHRASE_rating_change_title_D, text: 					"Kingdom Standing Falls" }
  { key: PHRASE_rating_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] the Egyptian people are displeased with you, and your Kingdom rating has fallen." }
  { key: PHRASE_rating_change_reason_D_A, text:  	 	 		"because your Kingdom rating has fallen so low," }
  { key: PHRASE_rating_change_reason_D_B, text:	  				"your popularity falls throughout the kingdom, and now" }
  { key: PHRASE_rating_change_reason_D_C, text:	  				"even though you're becoming less and less popular in the kingdom," }
  { key: PHRASE_rating_change_no_reason_D_A, text:  			"because of dissatisfaction in the Kingdom," }
  { key: PHRASE_rating_change_no_reason_D_B, text:	  "this is bad news, for" }
  { key: PHRASE_rating_change_no_reason_D_C, text:	  "your countrymen do not approve of your violent ways.  As a result" }

  { key:PHRASE_price_change_title_I, text: 					"A Price Increase" }
  { key:PHRASE_price_change_initial_announcement_I, text:		"[greeting] [player_name], [reason_phrase] the price of [item] has risen. Importing this good is now more costly, but higher profits can be made from exporting it." }
  { key:PHRASE_price_change_reason_I_A, text:  	 	 		"because the price of [item] has risen," }
  { key:PHRASE_price_change_reason_I_B, text:	  "the price of [item] risen, and what's more" }
  { key:PHRASE_price_change_reason_I_C, text:	  "event though prices have risen," }
  { key:PHRASE_price_change_no_reason_I_A, text:   	"because of reduced supplies throughout the world," }
  { key:PHRASE_price_change_no_reason_I_B, text:	  "as the market continues to change" }
  { key:PHRASE_price_change_no_reason_I_C, text:	  "" }
  { key:PHRASE_price_change_title_D, text: 					"A Price Cut" }
  { key:PHRASE_price_change_initial_announcement_D, text:		"[greeting] [player_name], [reason_phrase] the price of [item] has fallen. This will reduce the profits to be made by exporting it." }
  { key:PHRASE_price_change_reason_D_A, text:  	 	 	"because the price of [item] you can trade has fallen," }
  { key:PHRASE_price_change_reason_D_B, text:	  "prices have fallen, and what's more" }
  { key:PHRASE_price_change_reason_D_C, text:	  "although prices have fallen," }
  { key:PHRASE_price_change_no_reason_D_A, text:  		"because of an overabundance across the Kingdom," }
  { key:PHRASE_price_change_no_reason_D_B, text:	  "as the market continues to change" }
  { key:PHRASE_price_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_demand_change_title_I, text: 					"Increased Trading" }
  { key: PHRASE_demand_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] [city_name] is now willing to trade even more [item]." }
  { key: PHRASE_demand_change_reason_I_A, text:  	 			"because [city_name] is willing to trade more [item]," }
  { key: PHRASE_demand_change_reason_I_B, text:	  "[city_name] now wishes to trade more [item].  What's more," }
  { key: PHRASE_demand_change_reason_I_C, text:	  "even though [city_name] wishes to trade more [item]," }
  { key: PHRASE_demand_change_no_reason_I_A, text:  	"because [city_name] is growing," }
  { key: PHRASE_demand_change_no_reason_I_B, text:	  "times change, and" }
  { key: PHRASE_demand_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_demand_change_title_D, text: 					"Decreased trading" }
  { key: PHRASE_demand_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] [city_name] has decided that they must reduce the quantity of [item] which they are willing to trade with you." }
  { key: PHRASE_demand_change_reason_D_A, text:  	 			"because [city_name] is not trading as much [item]," }
  { key: PHRASE_demand_change_reason_D_B, text:	  "[city_name] is no trading as much, and" }
  { key: PHRASE_demand_change_reason_D_C, text:	  "even though [city_name] is not trading as much," }
  { key: PHRASE_demand_change_no_reason_D_A, text:			"because the citizens of [city_name] are cutting back," }
  { key: PHRASE_demand_change_no_reason_D_B, text:	  "times change, and" }
  { key: PHRASE_demand_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_earthquake_title, text: 					"Earthquake!" }
  { key: PHRASE_earthquake_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase]  the sand has shifted beneath our feet. Our land will never be the same. Do what you can to repair the damage the earthquake did to your city and to your people." }
  { key: PHRASE_earthquake_reason_A, text:  	 	 					"because of a terrible earthquake," }
  { key: PHRASE_earthquake_reason_B, text:	  "in addition to the terrible earthquake," }
  { key: PHRASE_earthquake_reason_C, text:	  "in spite of the terrible earthquake" }
  { key: PHRASE_earthquake_no_reason_A, text:  	 						"the city is frightened because" }
  { key: PHRASE_earthquake_no_reason_B, text:	  "trouble once more stalks the city, for" }
  { key: PHRASE_earthquake_no_reason_C, text:	  "" }

  { key: PHRASE_stormy_seas_title, text: 					"Tempests" }
  { key: PHRASE_stormy_seas_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] rough waters threaten to tear trading ships apart. It could be months before the winds calm and merchants dare to risk their cargoes again. Until then, we cannot trade by water." }
  { key: PHRASE_stormy_seas_reason_A, text:  	 	 					"because of unfathomably fierce storms," }
  { key: PHRASE_stormy_seas_reason_B, text:	  "while we've have been plagued by recent storms," }
  { key: PHRASE_stormy_seas_reason_C, text:	  "despite the terrible storms" }
  { key: PHRASE_stormy_seas_no_reason_A, text:  	 					"storms are raging and" }
  { key: PHRASE_stormy_seas_no_reason_B, text:	  "our troubles have only begun, for" }
  { key: PHRASE_stormy_seas_no_reason_C, text:	  "" }
                         
  { key: PHRASE_sandstorm_title, text: 						"Sandstorms" }
  { key: PHRASE_sandstorm_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] driving sands have obscured the roads, completely covering them over in some spots. Merchants aren't risking losing their way in such conditions and aren't venturing out. Until the winds abate, no merchants will be able to get through." }
  { key: PHRASE_sandstorm_reason_A, text:  	 				"because merchants will not dare to set forth during a sandstorm and land trade has stopped," }
  { key: PHRASE_sandstorm_reason_B, text:	  "sandstorms have stopped merchants in their tracks.  Also" }
  { key: PHRASE_sandstorm_reason_C, text:	  "despite the recent sandstorms which have hindered trade," }
  { key: PHRASE_sandstorm_no_reason_A, text:  	 						"due to high winds," }
  { key: PHRASE_sandstorm_no_reason_B, text:	  "the desert is a dangerous place, for" }
  { key: PHRASE_sandstorm_no_reason_C, text:	  "" }

  { key: PHRASE_wage_change_title_I, text: 					"Workers Rejoice at Raise" }
  { key: PHRASE_wage_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] wages have increased throughout the Kingdom. Your own workers may depart for greener pastures if they're not paid as much as their counterparts in other cities." }
  { key: PHRASE_wage_change_reason_I_A, text:  	 	 		"because wages have increased throughout the Kingdom," }
  { key: PHRASE_wage_change_reason_I_B, text:	  "wages have increased throughout the Kingdom, and" }
  { key: PHRASE_wage_change_reason_I_C, text:	  "even though wages have increased throughout the Kingdom," }
  { key: PHRASE_wage_change_no_reason_I_A, text:  	"times change, and now" }
  { key: PHRASE_wage_change_no_reason_I_B, text:	  "some rejoice, others gripe, for" }
  { key: PHRASE_wage_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_wage_change_title_D, text: 					"Wages Fall" }
  { key: PHRASE_wage_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] wages have fallen throughout the Kingdom of Egypt.  It seems everywhere people will work for less." }
  { key: PHRASE_wage_change_reason_D_A, text:  	 	 				"because wages have fallen," }
  { key: PHRASE_wage_change_reason_D_B, text:	  "wages have fallen, and what's more," }
  { key: PHRASE_wage_change_reason_D_C, text:	  "even though wages have fallen," }
  { key: PHRASE_wage_change_no_reason_D_A, text:  		"to try to cut costs," }
  { key: PHRASE_wage_change_no_reason_D_B, text:	  "some are upset, but nomarchs rejoice, for" }
  { key: PHRASE_wage_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_bad_water_title, text: 					"Contaminated Water" }
  { key: PHRASE_bad_water_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] some of your citizens have taken ill, caused by something in the water. Just hope that the problem does not escalate." }
  { key: PHRASE_bad_water_reason_A, text:  	 	 				"because of recent water contamination," }
  { key: PHRASE_bad_water_reason_B, text:	  "the recent water contamination was most unfortunate.  Now," }
  { key: PHRASE_bad_water_reason_C, text:	  "even though the water was contaminated recently," }
  { key: PHRASE_bad_water_no_reason_A, text:  		"bad luck is stalking the city, and" }
  { key: PHRASE_bad_water_no_reason_B, text:	  ", this is indeed unfortunate.  It seems" }
  { key: PHRASE_bad_water_no_reason_C, text:	  "" }

  { key: PHRASE_goldmine_cavein_title, text: 					"Gold Mine Caves In" }
  { key: PHRASE_goldmine_cavein_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] a gold mine has collapsed. Our architects were powerless to stop it it. Just hope the workers made it out of the mine in time." }
  { key: PHRASE_goldmine_cavein_reason_A, text:  	 	 			"because a gold mine collapsed," }
  { key: PHRASE_goldmine_cavein_reason_B, text:	  "the recent gold mine collapse was most unfortunate.  Now," }
  { key: PHRASE_goldmine_cavein_reason_C, text:	  "even though a gold mine collapsed recently," }
  { key: PHRASE_goldmine_cavein_no_reason_A, text: 		"due to shifting sands," }
  { key: PHRASE_goldmine_cavein_no_reason_B, text:	  "without warning," }
  { key: PHRASE_goldmine_cavein_no_reason_C, text:	  "" }

  { key: PHRASE_landslide_title, text: 					"Landslide" }
  { key: PHRASE_landslide_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] a terrible landslide has severed a trade route.  It could be months before the road is cleared and merchants sally forth again." }
  { key: PHRASE_landslide_reason_A, text:  	 	 				"because of the recent landslide," }
  { key: PHRASE_landslide_reason_B, text:	  "the recent landslides were devastating.  Now," }
  { key: PHRASE_landslide_reason_C, text:	  "even though there have been terrible landslides recently," }
  { key: PHRASE_landslide_no_reason_A, text:  	 					"there is horrible news:" }
  { key: PHRASE_landslide_no_reason_B, text:	  "without warning" }
  { key: PHRASE_landslide_no_reason_C, text:	  "" }

  { key: PHRASE_flood_fails_title, text: 					"Flood Likely to Fail" }
  { key: PHRASE_flood_fails_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] priests bring bad news...they fear the next Inundation will almost certainly fail!  Consult the Nilometer regularly...if the priests' prediction does not improve, the city had better be prepared for the worst." }
  { key: PHRASE_flood_fails_reason_A, text:  	 	 					"because the flood is expected to fail" }
  { key: PHRASE_flood_fails_reason_B, text:	  "the flood is expected to fail, and" }
  { key: PHRASE_flood_fails_reason_C, text:	  "even though the flood was expected to fail," }
  { key: PHRASE_flood_fails_no_reason_A, text:		"due to drought in Africa," }
  { key: PHRASE_flood_fails_no_reason_B, text:	  "our troubles have only begun, for" }
  { key: PHRASE_flood_fails_no_reason_C, text:	  "" }

  { key : PHRASE_perfect_flood_title, text: 					"Perfect Flood Expected" }
  { key : PHRASE_perfect_flood_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] this is indeed a blessing, for the likelihood of a bountiful flood is quite high!  Consult the Nilometer periodically.  If the prediction should worsen, the city could find itself unprepared." }
  { key : PHRASE_perfect_flood_reason_A, text:  	 	 				"because the flood was expected to be bountiful," }
  { key : PHRASE_perfect_flood_reason_B, text:	  "the flood was expected to be bountiful, and" }
  { key : PHRASE_perfect_flood_reason_C, text:	  "even though the flood was expected to be bountiful," }
  { key : PHRASE_perfect_flood_no_reason_A, text:  	 					"the monsoons in Africa are expected to come, so" }
  { key : PHRASE_perfect_flood_no_reason_B, text:	  "we are indeed fortunate, for" }
  { key : PHRASE_perfect_flood_no_reason_C, text:	  "" }

  { key: PHRASE_bedouin_attacks_you_title, text: 					"Bedouin Army Attacks" }
  { key: PHRASE_bedouin_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] a Bedouin army is approaching the city and will attack in [time_until_attack] months." }
  { key: PHRASE_bedouin_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] a Bedouin army moves ever closer and will reach ther city in two years.				" }
  { key: PHRASE_bedouin_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] a Bedouin army is well on its way and will reach the city in one year." }
  { key: PHRASE_bedouin_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] a Bedouin army is prepared to wage war and will reach the city in six months.	" }
  { key: PHRASE_bedouin_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] a Bedouin army is very near and will reach the city in one month." }
  { key: PHRASE_bedouin_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], an attacking Bedouin army is upon us!" }
  { key: PHRASE_bedouin_attacks_you_reason_A, text:  	 	 		"because your city successfully fought off the Bedouin army," }
  { key: PHRASE_bedouin_attacks_you_reason_B, text:	  				"your city successfully fought off the Bedouin army.  What's more," }
  { key: PHRASE_bedouin_attacks_you_reason_C, text:	  "even though your city successfully fought off the Bedouin army," }
  { key: PHRASE_bedouin_attacks_you_no_reason_A, text:  	"to satisfy their lust for riches," }
  { key: PHRASE_bedouin_attacks_you_no_reason_B, text:	  "our troubles are great, for" }
  { key: PHRASE_bedouin_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_gift_title_P, text: 				"A Gift from Pharaoh" }
  { key: PHRASE_gift_title_C, text: 				"A Gift from a Neighbor" }
  { key: PHRASE_gift_granted_P, text:				"[greeting] [player_name], [reason_phrase] the Pharaoh has decreed that you receive a gift of [amount] [item] from [city_name]." }
  { key: PHRASE_gift_granted_C, text:				"[greeting] [player_name], [reason_phrase] the city of [city_name] wishes to grant you a gift of [amount] [item]." }
  { key: PHRASE_gift_cash_granted_P, text:			"[greeting] [player_name], [reason_phrase] the Pharaoh has decreed that you receive a gift of [amount] debens from [city_name]." }
  { key: PHRASE_gift_cash_granted_C, text:			"[greeting] [player_name], [reason_phrase] the city of [city_name] wishes to grant you a gift of [amount] debens." }
  { key: PHRASE_gift_partial_space_P, text:			"[greeting] [player_name], [reason_phrase] the Pharaoh has decreed that you receive a gift of [amount] [item] from [city_name].  You do not currently have enough space in your Storage Yards or Granaries to accomodate this gift, but you can squeeze in at least half of it." }
  { key: PHRASE_gift_partial_space_C, text:			"[greeting] [player_name], [reason_phrase] the city of [city_name] wishes to grant you a gift of [amount] [item].  You do not currently have enough space in your Storage Yards or Granaries to accomodate this gift, but you can squeeze in at least half of it." }
  { key: PHRASE_gift_insufficient_space_P, text: 	"[greeting] [player_name], [reason_phrase] Pharaoh has decreed that you receive a gift of [amount] [item] from [city_name], but there isn't enough space in your Storage Yards and Granaries.  Make some room and it will be delivered again next month." }
  { key: PHRASE_gift_insufficient_space_C, text: 	"[greeting] [player_name], [reason_phrase] the city of [city_name] wishes to grant you a gift of [amount] [item], but there is insufficient space in your Storage Yards and Granaries to accomodate it.  Make some room and it will be delivered again next month." }
  { key: PHRASE_gift_last_chance_P, text: 			"[greeting] [player_name], per order of Pharaoh, the city of [city_name] has been trying to grant you a gift of [amount] [item], but you still do not have sufficient space in your Storage Yards and Granaries to accomodate all of it.  You have kept its emissaries waiting too long, and they have grown impatient.  Accept this partial gift now, for they will not return again."  }
  { key: PHRASE_gift_last_chance_C, text: 			"[greeting] [player_name], the city of [city_name] has been trying to grant you a gift of [amount] [item], but you still do not have sufficient space in your Storage Yards and Granaries to accomodate all of it.  You have kept its emissaries waiting too long, and they have grown impatient.  Accept this partial gift now, for they will not return again." }
  { key: PHRASE_gift_forfeited_P, text: 			"[greeting] [player_name], there is still insufficient space for you to receive the gift of [amount] [item] from [city_name], and so it is forfeit." }
  { key: PHRASE_gift_forfeited_C, text: 			"[greeting] [player_name], there is still insufficient space for you to receive the gift of [amount] [item] from [city_name], and so it is forfeit." }
  { key: PHRASE_gift_accepted_P, text: 				"Per order of the Pharaoh, your city's Storage Yards and Granaries have been filled with as many of the [item] from [city_name] as they can accomodate." }
  { key: PHRASE_gift_accepted_C, text: 				"Your city's Storage Yards and Granaries have been filled with as many of the [item] from [city_name] as they can accomodate." }
  { key: PHRASE_gift_cash_accepted_P, text: 		"Per order of the Pharaoh, [amount_granted] debens have been added to your treasury." }
  { key: PHRASE_gift_cash_accepted_C, text: 		"Thanks to [city_name], [amount_granted] debens have been added to your treasury." }
  { key: PHRASE_gift_postponed_P, text:				"Emissaries from [city_name] will return in one month with your delivery of [item]." }
  { key: PHRASE_gift_postponed_C, text: 			"Emissaries from [city_name] will return in one month with your delivery of [item]." }
  { key: PHRASE_gift_refused_P, text: 				"Though you have refused this gift of [item] from [city_name], I'm sure someone else could use our help." }
  { key: PHRASE_gift_refused_C, text: 				"Though you have refused this gift of [item] from [city_name], I'm sure someone else could use our help." }
  { key: PHRASE_gift_accepted_reason_P_A, text:  	 		"because you accepted a gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_accepted_reason_P_B, text:	  "in the wake of your recent gift from [city_name]," }
  { key: PHRASE_gift_accepted_reason_P_C, text:	  "even though you accepted the gift of [amount] [item] from [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_A, text:  	 		"because you accepted a gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_accepted_reason_C_B, text:	  "in the wake of your recent gift from [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_C, text:	  "even though you accepted the gift of [amount] [item] from [city_name]," }
  { key: PHRASE_gift_forfeited_reason_P_A, text:  	 		"because you did not accept a gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_forfeited_reason_P_B, text:	  "you did not accept a gift of [amount] [item] from [city_name].  Also," }
  { key: PHRASE_gift_forfeited_reason_P_C, text:	  "though you did not accept the gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_A, text:  	 		"because you did not accept the gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_B, text:	  "you did not accept the gift of [amount] [item] from [city_name].  Also," }
  { key: PHRASE_gift_forfeited_reason_C_C, text:	  "even though you did not accept the gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_refused_reason_P_A, text:  	 		"because you refused a gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_refused_reason_P_B, text:	  "you refused a gift of [amount] [item] from [city_name].  Now," }
  { key: PHRASE_gift_refused_reason_P_C, text:	  "although you refused a gift of [amount] [item] from [city_name]," }
  { key: PHRASE_gift_refused_reason_C_A, text:  	 		"because you refused a gift of [amount] [item] from [city_name]" }
  { key: PHRASE_gift_refused_reason_C_B, text:	  "you refused a gift of [amount] [item] from [city_name].  Now," }
  { key: PHRASE_gift_refused_reason_C_C, text:	  "although you refused a gift of [amount] [item] from [city_name]," }
  { key: PHRASE_gift_no_reason_P_A, text:  					"because you could use some help" }
  { key: PHRASE_gift_no_reason_P_B, text:	  "because Pharaoh's benevolence is boundless," }
  { key: PHRASE_gift_no_reason_P_C, text:	  "your city's sacrifices in combat are greatly appreciated by Pharaoh.  As a result" }
  { key: PHRASE_gift_no_reason_C_A, text:  					"because you could use some help" }
  { key: PHRASE_gift_no_reason_C_B, text:	  "because Egyptians always help their fellow countrymen," }
  { key: PHRASE_gift_no_reason_C_C, text:	  "your city's sacrifices in combat are greatly appreciated by the Egytian people.  As a result" }

  { key: PHRASE_pharaoh_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] Pharaoh's army has arrived to claim your city by force." }
  { key: PHRASE_eg_city_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] an Egyptian army has landed and is invading the city as we speak!" }
  { key: PHRASE_foreign_army_attacks_you_disembarked_alert, text:  	"[greeting] [player_name], [reason_phrase] [a_foreign_army] has landed and is even now attacking the city! May Seth deliver us." }
  { key: PHRASE_bedouin_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] a hostile Bedouin invasion force has landed on our shores!" }

  { key: PHRASE_pyramid_congratulations_title, text:			"Pyramid finished!" }
  { key: PHRASE_pyramid_congratulations, text:					"[greeting] [player_name], this is a spectacular accomplishment! After countless months of labor the Pyramid is finally complete!" }
  { key: PHRASE_stepped_pyramid_congratulations_title, text:	"Stepped Pyramid finished!" }
  { key: PHRASE_stepped_pyramid_congratulations, text:			"[greeting] [player_name], at long last the Stepped Pyramid is complete!  This monument will forever stand as a testament to your abilities." }
  { key: PHRASE_bent_pyramid_congratulations_title, text:		"Bent Pyramid finished!" }
  { key: PHRASE_bent_pyramid_congratulations, text:				"[greeting] [player_name], construction of the Bent Pyramid is finally complete! This is a stupendous achievement for your city." }
  { key: PHRASE_mudbrick_pyramid_congratulations_title, text:	"Brick Pyramid finished!" }
  { key: PHRASE_mudbrick_pyramid_congratulations, text:			"[greeting] [player_name], masons have completed their finishing touches on the gleaming outer casing of fine limestone, and the Brick Pyramid is finally done!" }
  { key: PHRASE_mastaba_congratulations_title, text:			"Mastaba finished!" }
  { key: PHRASE_mastaba_congratulations, text:					"[greeting] [player_name], the last brick has been laid in place, and work on the Mastaba is now complete!" }
  { key: PHRASE_sphinx_congratulations_title, text:				"Sphinx finished!" }
  { key: PHRASE_sphinx_congratulations, text:					"[greeting] [player_name], at long last the masons have finished carving the mighty Sphinx.  This monument will watch over Egypt for all the ages." }
  { key: PHRASE_obelisk_congratulations_title, text:			"Obelisk finished!" }
  { key: PHRASE_obelisk_congratulations, text:					"[greeting] [player_name], masons have put their finishing touches on the Obelisk, and at long last it is complete." }
  { key: PHRASE_sun_temple_congratulations_title, text:			"Sun Temple finished!" }
  { key: PHRASE_sun_temple_congratulations, text:				"[greeting] [player_name], after many months of toil, work on the Sun Temple has finally come to a close.  This is a great accomplishment for your city!" }
  { key: PHRASE_alex_library_congratulations_title, text:		"Alexandria Library finished!" }
  { key: PHRASE_alex_library_congratulations, text:				"[greeting] [player_name], after much hard labor the beautiful hand-crafted doors of Alexandria's magnificent Great Library are ready to be opened wide to the scholars of the world." }
  { key: PHRASE_abu_simbel_congratulations_title, text:			"Abu Simbel finished!" }
  { key: PHRASE_abu_simbel_congratulations, text:				"[greeting] [player_name], this is a truly spectacular achievement!  Your skilled laborers have created an eternal monument that boasts of the glory of our pharaoh and the might of Egypt." }
  { key: PHRASE_caesareum_congratulations_title, text:			"Caesareum finished!" }
  { key: PHRASE_caesareum_congratulations, text:				"[greeting] [player_name], the holy temple and resplendent gardened courtyards of the Caesareum are at long last complete! Word of its magnificent beauty is already spreading throughout the region." }
  { key: PHRASE_lighthouse_congratulations_title, text:			"Pharos Lighthouse finished!" }
  { key: PHRASE_lighthouse_congratulations, text:    "[greeting] [player_name], after much sweat and not a little shed blood, workmen have carefully placed the final block of marble for the wondrous Pharos Lighthouse!  Already its towering bright beacon is attracting traders from all over." }
  { key: PHRASE_mausoleum_congratulations_title, text:			"Mausoleum finished!" }
  { key: PHRASE_mausoleum_congratulations, text:				"[greeting] [player_name], the sacred Mausoleum is finally complete!  This is a remarkable achievement for your city." }
  { key: PHRASE_smalltomb_congratulations_title, text:			"Small Burial Tomb finished!" }
  { key: PHRASE_smalltomb_congratulations, text:				"[greeting] [player_name], construction of the small Royal Burial Tomb is complete.  Hopefully it will be many years until your workers will have to prepare another." }
  { key: PHRASE_medtomb_congratulations_title, text:			"Med. Burial Tomb finished!" }
  { key: PHRASE_medtomb_congratulations, text:				"[greeting] [player_name], at long last the medium Royal Burial Tomb is finished and fully stocked with provisions.  It is bound to provide an ideal conduit to the afterlife for our recently departed pharaoh." }
  { key: PHRASE_largetomb_congratulations_title, text:			"Large Burial Tomb finished!" }
  { key: PHRASE_largetomb_congratulations, text:				"[greeting] [player_name], after many years of hard labor in the bowels of the earth your workers have completed work on the most magnificent burial tomb to date!  It is truly a marvelous accomplishment." }
  { key: PHRASE_grandtomb_congratulations_title, text:			"Grand Burial Tomb finished!" }
  { key: PHRASE_grandtomb_congratulations, text:				"[greeting] [player_name], after much strenuous work the grand Royal Burial Tomb is complete - and none too soon, as our esteemed pharaoh is, by some accounts, on his last legs.  This magnificent tomb is perfect to further his approaching journey into the afterlife." }

  { key: PHRASE_troopcarryover_title, text:   "Loyal Soldiers Rejoin You" }
  { key: PHRASE_troopcarryover_initial_announcement, text: "Your best soldiers from the previous mission wish to rejoin you.  Build [reason_phrase] for these warriors and they will return." }
  { key: PHRASE_troopcarryover_inf_only, text: "an infantry fort" }
  { key: PHRASE_troopcarryover_arch_only, text: "an archers fort" }
  { key: PHRASE_troopcarryover_char_only, text: "a charioteer fort" }
  { key: PHRASE_troopcarryover_inf_arch, text: "infantry and archer forts" }
  { key: PHRASE_troopcarryover_inf_char, text: "infantry and charioteer forts" }
  { key: PHRASE_troopcarryover_arch_char, text: "archer and charioteer forts" }
  { key: PHRASE_troopcarryover_all_three, text: "infantry, archer, and charioteer forts" }
  { key: PHRASE_pyramid_speedup_title, text: "A Construction Blessing" }
  { key: PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] is pleased by your devotion and wishes to give a major boost to your monument construction project.  It is time for your workers to temporarily stand aside while this bountiful blessing from the revered [reason_phrase] is received." }
  { key: PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] acknowledges your worship by aiding your monument construction project.  It is time for your workers to take a short rest while this benevolent gift from [reason_phrase] arrives." }
  { key: PHRASE_pyramid_speedup_Osiris, text: "Osiris" }
  { key: PHRASE_pyramid_speedup_Ra, text: "Ra" }
  { key: PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
  { key: PHRASE_pyramid_speedup_Seth, text: "Seth" }
  { key: PHRASE_pyramid_speedup_Bast, text: "Bast" }
]