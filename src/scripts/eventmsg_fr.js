log_info("akhenaten: eventmsg french started")

eventmsg_fr = [
  { key:PHRASE_egyptian_city_attacked_title_P, text: "Une cité est attaquée" }
  { key:PHRASE_egyptian_city_attacked_title_C, text: "Une cité est attaquée" }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: 	"[greeting] [player_name],[reason_phrase] des infidèles passent à l'attaque. Le pharaon tout puissant vous ordonne d'envoyer des troupes à [city_name], une ville égyptienne, pour repousser l'ennemi. Envoyez des troupes dans les [travel_time] mois." }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: 	"[greeting] [player_name], [reason_phrase]  [city_name], une ville égyptienne, est attaquée et a besoin de votre aide. Envoyez des troupes dans les [travel_time] mois." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_P, text: 	"[greeting] [player_name], les armées du divin pharaon combattent les agresseurs à [city_name]. Envoyez des renforts dans les six mois ou vous devrez faire face à la colère du pharaon." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_C, text: 	"[greeting] [player_name], avez-vous oublié [city_name] ? Envoyez-y des troupes dans les 6 mois ou les conséquences seront terribles." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_P, text: 	"[greeting] [player_name], le pharaon s'impatiente du retard de vos troupes. Envoyez immédiatement des troupes à [city_name] avant qu'il ne soit trop tard." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_C, text: 	"[greeting] [player_name], [city_name] risque de bientôt se rendre. Envoyez des troupes rapidement pour secourir [city_name]." }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "dans la mesure où vos troupes ont vaincu les ennemis du pharaon à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "vos troupes ont vaincu les ennemis du pharaon à [city_name]. Malheureusement," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "bien que vos troupes aient vaincu les ennemis du pharaon à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "dans la mesure où vos troupes ont mis l'ennemi en déroute à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "dans la mesure où vos troupes ont mis l'ennemi en déroute à [city_name]. En outre," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "bien que vos troupes aient mis l'ennemi en déroute à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "en raison de votre indolence devant les demandes de renforts des armées du pharaon à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "les armées du pharaon ont perdu la bataille à [city_name], vos troupes étant arrivées trop tard. Désormais," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "vos troupes sont arrivées trop tard pour aider les armées du pharaon à [city_name]. Cependant, votre effort n'est pas passé inaperçu. Par conséquent," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "dans la mesure où vous avez trop attendu pour envoyer des renforts à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "vos troupes ne sont pas arrivées à temps pour aider à défendre [city_name]. Par conséquent," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "vos troupes sont arrivées trop tard à [city_name], mais compte tenu de votre effort et de votre volonté à ne reculer devant aucun sacrifice," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "étant donné votre refus de fournir au pharaon les troupes dont il avait besoin à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "le pharaon a appris votre refus de fournir les troupes dont il avait besoin pour combattre l'ennemi à [city_name]. De plus," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "et ce, malgré votre refus de fournir au pharaon les troupes dont il avait besoin pour repousser l'ennemi à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "étant donné votre refus de fournir les troupes requises pour vaincre les maraudeurs à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: 	"[city_name] est effondré d'apprendre votre refus de fournir les troupes nécessaires à la défaite de leurs ennemis. Par conséquent," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "et que vous ayez également refusé d'envoyer les troupes nécessaires pour vaincre les maraudeurs à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "étant donné que les troupes envoyées au pharaon à [city_name] étaient trop faibles pour vaincre les ennemis," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "les troupes affaiblies que vous avez envoyées pour aider le pharaon ont été vaincues à [city_name]. Par conséquent," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "en dépit de la faiblesse de vos troupes venues en aide au pharaon à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "étant donné que les troupes envoyées à [city_name] ne sont pas parvenues à battre les assaillants," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "vos troupes affaiblies ont été vaincues à [city_name]. En outre," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "bien que vos troupes ne soient pas sorties victorieuses à [city_name]," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "pour satisfaire leur besoin d'expansion," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "vos problèmes ne sont pas encore résolus, étant donné que" }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: 	"" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "suite à une vieille querelle," }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "vos problèmes ne sont pas encore résolus, étant donné que" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: 	"" }

  { key: PHRASE_distant_battle_title_P, text: "Bataille distante" }
  { key: PHRASE_distant_battle_title_C, text: "Bataille distante" }
  { key: PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] l'armée égyptienne est prise dans un combat sans merci. L'impérieux pharaon exige l'envoi de troupes à [city_name], une ville lointaine, pour participer au combat. Envoyez des troupes dans les [travel_time] mois." }
  { key: PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] l'armée égyptienne est aux prises avec l'ennemi dans la ville lointaine de [city_name] et vous demande d'envoyer des renforts. Envoyez des troupes dans les [travel_time] mois." }
  { key: PHRASE_distant_battle_first_reminder_P, text: 	"[greeting] [player_name], une bataille sanglante se poursuit à [city_name] et le pharaon a toujours besoin de vos troupes. Envoyez-les dans les 6 mois pour qu'elles arrivent à temps. Sinon, il vous en coûtera cher." }
  { key: PHRASE_distant_battle_first_reminder_C, text: 	"[greeting] [player_name], la bataille pour [city_name] fait rage. Envoyez des troupes dans les six mois pour qu'elles arrivent à temps. Vous aurez ainsi la possibilité de participer à une victoire glorieuse." }
  { key: PHRASE_distant_battle_last_reminder_P, text: 	"[greeting] [player_name], l'armée égyptienne guerroie toujours à [city_name] et le noble pharaon exige l'envoi de renforts au plus vite. Ne contrariez pas le pharaon lorsqu'il est d'humeur guerrière." }
  { key: PHRASE_distant_battle_last_reminder_C, text: 	"[greeting] [player_name], la bataille pour [city_name] se poursuit. Si vous envoyez rapidement des troupes à leur secours, l'Egypte pourrait remporter une victoire glorieuse." }
  { key: PHRASE_distant_battle_comply_reason_P_A, text: "dans la mesure où la victoire du pharaon à [city_name] dépend de vos troupes," }
  { key: PHRASE_distant_battle_comply_reason_P_B, text: "vos troupes ont permis au pharaon de devenir victorieux à [city_name]. Cependant" }
  { key: PHRASE_distant_battle_comply_reason_P_C, text: "bien que vos troupes aient permis au pharaon de devenir victorieux à [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_A, text: "dans la mesure où vos troupes ont aidé à remporter la victoire à [city_name]," }
  { key: PHRASE_distant_battle_comply_reason_C_B, text: "vos troupes ont été l'élément déterminant de la victoire à [city_name]. Par conséquent," }
  { key: PHRASE_distant_battle_comply_reason_C_C, text: "bien que vos troupes aient été l'élément déterminant de la victoire à [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_A, text: "dans la mesure où vos troupes ne sont pas parvenues à secourir le pharaon à [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_P_B, text: "vos troupes ne sont pas parvenues à secourir le pharaon à [city_name]. En outre," }
  { key: PHRASE_distant_battle_too_late_reason_P_C, text: "bien que vos troupes soient arrivées trop tard pour venir en aide au pharaon à [city_name], votre volonté à ne refuser aucun sacrifice pour le royaume a été fort appréciée. Par conséquent," }
  { key: PHRASE_distant_battle_too_late_reason_C_A, text: "dans la mesure où vos troupes sont arrivées après la bataille à [city_name]," }
  { key: PHRASE_distant_battle_too_late_reason_C_B, text: "vos troupes sont arrivées après la bataille à [city_name]. En outre," }
  { key: PHRASE_distant_battle_too_late_reason_C_C, text: "bien que vos troupes soient arrivées après la bataille à [city_name], votre volonté à ne refuser aucun sacrifice pour le royaume a été fort appréciée. Par conséquent," }
  { key: PHRASE_distant_battle_refuse_reason_P_A, text: "dans la mesure où vous avez ignoré ouvertement la requête de renforts du pharaon pour son armée à [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_P_B, text: "dans la mesure où vous avez ignoré ouvertement la requête de renforts du pharaon pour son armée à [city_name]. Cela était fort imprudent, mais en tout cas," }
  { key: PHRASE_distant_battle_refuse_reason_P_C, text: "bien que vous ayez ignoré la requête de renforts du pharaon pour son armée à [city_name]," }
  { key: PHRASE_distant_battle_refuse_reason_C_A, text: "étant donné que vous avez refusé d'envoyer à [city_name] les troupes requises lors de la bataille," }
  { key: PHRASE_distant_battle_refuse_reason_C_B, text: "vous avez refusé d'envoyer à [city_name] les troupes requises lors de la bataille, ce qui a eu des conséquences désastreuses. Par conséquent," }
  { key: PHRASE_distant_battle_refuse_reason_C_C, text: "bien que vous ayez refusé d'envoyer à [city_name] les troupes requises lors de la bataille," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_A, text: "dans la mesure où les troupes que vous avez envoyées à [city_name] étaient trop faibles pour inquiéter les adversaires du pharaon," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_B, text: "les troupes que vous avez envoyées à [city_name] ont été vaincues par l'ennemi du pharaon. En outre," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_C, text: "bien que les troupes que vous avez envoyées à [city_name] aient été vaincues par l'ennemi du pharaon," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_A, text: "dans la mesure où les troupes envoyées à [city_name] n'avaient ni la force, ni l'énergie nécessaires pour terrasser l'ennemi," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_B, text: "les troupes envoyées à [city_name] n'avaient pas la force et l'énergie nécessaires pour terrasser nos ennemis héréditaires. Aussi prenez garde," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_C, text: "bien que les troupes envoyées à [city_name] n'aient pas été assez fortes pour terrasser l'ennemi," }
  { key: PHRASE_distant_battle_no_reason_P_A, text: "ralliez-vous au cri de guerre, étant donné que"			 }
  { key: PHRASE_distant_battle_no_reason_P_B, text: "nos problèmes continuent," }
  { key: PHRASE_distant_battle_no_reason_P_C, text: 	"" }
  { key: PHRASE_distant_battle_no_reason_C_A, text: "alertez vos soldats, étant donné que" }
  { key: PHRASE_distant_battle_no_reason_C_B, text: "ce n'est pas encore fini, car" }
  { key: PHRASE_distant_battle_no_reason_C_C, text: 	"" }

  { key:PHRASE_general_request_title_P, text:"Requête du pharaon" }
  { key:PHRASE_general_request_title_C, text:"Requête d'une ville" }
  { key:PHRASE_general_request_initial_announcement_P,text:	"[greeting] [player_name], [reason_phrase] le pharaon sans égal vous demande d'envoyer [amount] charrettes en [item] à [city_name] dans les [time_allotted] mois. La satisfaction de cette requête pourra vous apporter la reconnaissance du pharaon." }
  { key:PHRASE_general_request_initial_announcement_C,text:	"[greeting] [player_name], [reason_phrase] la cité de [city_name] vous demande d'envoyer [amount] charrettes en [item] dans les [time_allotted] mois. Aider [city_name] pourrait entraîner des conséquences favorables pour l'avenir." }
  { key:PHRASE_general_request_reminder_P, text:	"[greeting] [player_name], le pharaon se demande pourquoi [city_name] n'a pas reçu [amount] charrettes en [item]. Il vous reste six mois pour satisfaire la requête du pharaon." }
  { key:PHRASE_general_request_reminder_C, text:	"[greeting] [player_name], [city_name] attend avec impatience l'arrivée de [amount] charrettes en [item]. Il vous reste 6 mois pour y parvenir." }
  { key:PHRASE_general_request_overdue_P, text:	"[greeting] [player_name], essayez-vous de provoquer le pharaon ? Vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name] dans les temps. Une réponse même tardive à sa requête apaisera le courroux du pharaon." }
  { key:PHRASE_general_request_overdue_C, text:	"[greeting] [player_name], le temps imparti est écoulé et vous n'avez toujours pas envoyé les [amount] charrettes en [item] à [city_name]. Une réponse même tardive à sa requête pourrait l'apaiser quelque peu." }
  { key:PHRASE_general_request_warning_P, text:	"[greeting] [player_name], il ne vous reste que 6 mois pour satisfaire la requête du pharaon. Vous devez envoyer [amount] charrettes en [item] à [city_name]. Mieux vaut s'exécuter." }
  { key:PHRASE_general_request_warning_C, text:	"[greeting] [player_name], envoyez à [city_name] [amount] charrettes en [item] dans les 6 mois ou vous aurez des ennemis à votre porte." }
  { key:PHRASE_general_request_comply_reason_P_A, text:"dans la mesure où les [amount] charrettes en [item] demandées par le pharaon ont été envoyées à [city_name]," }
  { key:PHRASE_general_request_comply_reason_P_B, text:"les [amount] charrettes en [item] demandées par le pharaon ont été envoyées à [city_name]. A l'occasion," }
  { key:PHRASE_general_request_comply_reason_P_C, text:"vous avez satisfait le pharaon en envoyant les [amount]charrettes en [item] demandées, cependant," }
  { key:PHRASE_general_request_comply_reason_C_A, text:"dans la mesure où vous avez envoyé [amount] charrettes en [item] à [city_name], comme demandé," }
  { key:PHRASE_general_request_comply_reason_C_B, text:	"[city_name] a reçu [amount] charrettes en [item], comme demandé. Vous devez également savoir que" }
  { key:PHRASE_general_request_comply_reason_C_C, text:"bien que vous ayez envoyé [amount] charrettes en [item] à [city_name], comme demandé," }
  { key:PHRASE_general_request_too_late_reason_P_A, text:"dans la mesure où vous avez retardé la livraison de [amount] charrettes en [item] demandées par le pharaon," }
  { key:PHRASE_general_request_too_late_reason_P_B, text:"la requête du pharaon de [amount] charrettes en [item] n'a pas été remplie compte tenu de votre retard. En outre," }
  { key:PHRASE_general_request_too_late_reason_P_C, text:"vous avez retardé la livraison de [amount] charrettes en [item] demandées par le pharaon, mais néanmoins votre effort a été apprécié. Par conséquent," }
  { key:PHRASE_general_request_too_late_reason_C_A, text:"dans la mesure où vous avez répondu tardivement à la requête de [city_name] pour l'envoi de [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_general_request_too_late_reason_C_B, text:"vous avez répondu tardivement à la requête de [city_name] pour l'envoi de [amount] charrettes en [item]. Prenez garde à ce que" }
  { key:PHRASE_general_request_too_late_reason_C_C, text:"malgré le fait que vous ayez répondu tardivement à la requête de [city_name] pour l'envoi de [amount]  charrettes en [item], votre effort a été apprécié. Par conséquent," }
  { key:PHRASE_general_request_refuse_reason_P_A, text:"dans la mesure où vous avez ignoré la requête du pharaon pour la livraison de [amount] charrettes en [item]," }
  { key:PHRASE_general_request_refuse_reason_P_B, text:"vous avez ignoré la requête du pharaon pour la livraison de [amount] charrettes en [item] et il va être mécontent. En outre," }
  { key:PHRASE_general_request_refuse_reason_P_C, text:"même si vous ignorez la requête du pharaon pour la livraison de [amount] charrettes en [item]," }
  { key:PHRASE_general_request_refuse_reason_C_A, text:"dans la mesure où vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_general_request_refuse_reason_C_B, text:"vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name] et ils sont mécontents. En attendant," }
  { key:PHRASE_general_request_refuse_reason_C_C, text:"malgré le fait que vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_general_request_no_reason_P_A, text:"afin de développer les réserves de son domaine," 			 }
  { key:PHRASE_general_request_no_reason_P_B, text:"la cupidité du pharaon semble être sans limite, étant donné que" }
  { key:PHRASE_general_request_no_reason_P_C, text:	"" }
  { key:PHRASE_general_request_no_reason_C_A, text:"afin de satisfaire les besoins des citoyens," }
  { key:PHRASE_general_request_no_reason_C_B, text:"il semble n'y avoir aucune limite, étant donné que" }
  { key:PHRASE_general_request_no_reason_C_C, text:	"" }

  { key: PHRASE_great_festival_title_P, text: "Fête dédiée à [god]" }
  { key: PHRASE_great_festival_title_C, text: "Grande fête pour [god]" }
  { key: PHRASE_great_festival_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] le pharaon prépare une grande fête dédiée à [god] qui aura lieu à [city_name] et nécessite des biens en provenance de votre cité. Vous disposez de [time_allotted] mois pour envoyer [amount] charrettes en [item]." }
  { key: PHRASE_great_festival_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] la cité de [city_name] vous demande d'envoyer [amount] charrettes en [item] pour une grande fête dédiée à [god]. La cité doit recevoir ces biens dans les [time_allotted] mois." }
  { key: PHRASE_great_festival_reminder_P, text: "[greeting] [player_name], il vous reste six mois pour envoyer [amount] charrettes en [item] à [city_name] pour la grande fête dédiée à [god]. Le pharaon ne verra pas d'un bon œil le non respect de cette requête." }
  { key: PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], la grande fête dédiée à [god] et tenue à [city_name] approche rapidement. Vous n'avez toujours pas envoyé les [amount] charrettes en [item]. Il vous reste 6 mois pour envoyer ces biens." }
  { key: PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], vous n'avez pas respecté le temps imparti et le pharaon a dû tenir la grande fête dédiée à [god] sans les biens requis. Envoyez malgré tout [amount] charrettes en [item] à [city_name] pour calmer la colère du pharaon." }
  { key: PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] n'apprécie pas d'avoir dû se procurer des biens auprès d'une autre source pour leur grande fête dédiée à [god]. Ils montreront peut-être une certaine indulgence si vous leur envoyez tout de même [amount] charrettes en [item]." }
  { key: PHRASE_great_festival_warning_P, text: "[greeting] [player_name], il vous reste 6 mois pour faire parvenir au pharaon [amount] charrettes en [item] à [city_name] pour la grande fête dédiée à [god]. Malheur à celui qui subira la rage du pharaon !" }
  { key: PHRASE_great_festival_warning_C, text: "[greeting] [player_name], [city_name] a perdu patience à votre égard. Envoyez [amount] charrettes en [item] dans les 6 mois pour préserver un semblant de bonnes relations." }
  { key: PHRASE_great_festival_comply_reason_P_A, text: "dans la mesure où vous avez honoré le pharaon et [god] en envoyant ponctuellement [amount] charrettes en [item] à [city_name] pour la grande fête," }
  { key: PHRASE_great_festival_comply_reason_P_B, text: "vous avez gracieusement honoré le pharaon et [god] en envoyant ponctuellement [amount] charrettes en [item] à [city_name] pour la grande fête. Par conséquent," }
  { key: PHRASE_great_festival_comply_reason_P_C, text: "vous avez gracieusement honoré le pharaon et [god] en envoyant ponctuellement [amount] charrettes en [item] à [city_name] pour la grande fête," }
  { key: PHRASE_great_festival_comply_reason_C_A, text: "dans la mesure où vous avez aidé [city_name] à célébrer sa grande fête dédiée à [god] en envoyant [amount] charrettes en [item]," }
  { key: PHRASE_great_festival_comply_reason_C_B, text: "dans la mesure où vous avez aidé [city_name] à célébrer sa grande fête dédiée à [god] en envoyant [amount] charrettes en [item], ce qui a été très apprécié. En outre," }
  { key: PHRASE_great_festival_comply_reason_C_C, text: "bien que vous ayez aidé [city_name] à célébrer sa grande fête dédiée à [god] en envoyant [amount] charrettes en [item]," }
  { key: PHRASE_great_festival_too_late_reason_P_A, text: "dans la mesure où vous n'avez pas envoyé à temps les [amount] charrettes en [item] pour la grande fête du pharaon dédiée à [god] et tenue à [city_name]," }
  { key: PHRASE_great_festival_too_late_reason_P_B, text: "vous n'avez pas envoyé à temps les [amount] charrettes en [item] pour la grande fête du pharaon dédiée à [god] et tenue à [city_name]. En outre," }
  { key: PHRASE_great_festival_too_late_reason_P_C, text: "bien que les [amount] charrettes en [item] ne soient pas arrivées à temps pour la grande fête du pharaon dédiée à [god] et tenue à [city_name], votre effort sera pris en compte," }
  { key: PHRASE_great_festival_too_late_reason_C_A, text: "dans la mesure où les [amount] charrettes en [item] requises par [city_name] pour la grande fête dédiée à [god] ne sont pas arrivées à temps," }
  { key: PHRASE_great_festival_too_late_reason_C_B, text: "les [amount] charrettes en [item] requises par [city_name] pour la grande fête dédiée à [god] ne sont pas arrivées à temps. Par conséquent," }
  { key: PHRASE_great_festival_too_late_reason_C_C, text: "bien que les [amount] charrettes en [item] requises par [city_name] pour la grande fête dédiée à [god] ne soient pas arrivées à temps, et compte tenu du fait que vous avez fait de votre mieux," }
  { key: PHRASE_great_festival_refuse_reason_P_A, text: "dans la mesure où vous avez négligé de satisfaire à la requête du pharaon exigeant [amount] charrettes en [item] pour la grande fête organisée dédiée à [god] et tenue à [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_P_B, text: "vous avez négligé de satisfaire à la requête du pharaon exigeant [amount] charrettes en [item] pour la grande fête organisée dédiée à [god] et tenue à [city_name]. Par conséquent," }
  { key: PHRASE_great_festival_refuse_reason_P_C, text: "malgré votre négligence à satisfaire à la requête du pharaon exigeant [amount] charrettes en [item] pour la grande fête organisée dédiée à [god] et tenue à [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_C_A, text: "dans la mesure où vous avez fait affront à [city_name] en ignorant sa requête de [amount] charrettes en [item] pour la grande fête dédiée à [god]," }
  { key: PHRASE_great_festival_refuse_reason_C_B, text: "vous avez fait affront à [city_name] en ignorant sa requête de [amount] charrettes en [item] pour la grande fête dédiée à [god]. Par conséquent," }
  { key: PHRASE_great_festival_refuse_reason_C_C, text: "bien que vous ayez fait affront à [city_name] en ignorant sa requête de [amount] charrettes en [item] pour la grande fête dédiée à [god]," }
  { key: PHRASE_great_festival_no_reason_P_A, text: "dans la mesure où le pharaon cherche à honorer la divinité," }
  { key: PHRASE_great_festival_no_reason_P_B, text: "dans la mesure où [god] est mécontent," }
  { key: PHRASE_great_festival_no_reason_P_C, text:  "" }
  { key: PHRASE_great_festival_no_reason_C_A, text: "dans la mesure où [city_name] est béni par [god]," }
  { key: PHRASE_great_festival_no_reason_C_B, text: "dans la mesure où [god] est encore mécontent," }
  { key: PHRASE_great_festival_no_reason_C_C, text:  "" }

  { key: PHRASE_project_title_P, text: 						"Construction pour Pharaon" }
  { key: PHRASE_project_title_C, text: 						"Projet de construction" }
  { key: PHRASE_project_initial_announcement_P, text:		"[greeting] [player_name], [reason_phrase] ce que le pharaon construit est si imposant qu'il vous demande d'envoyer [amount] charrettes en [item] à [city_name] dans les [time_allotted] mois. Quelle que soit la nature de ce projet, il est assurément à la gloire de l'Egypte." }
  { key: PHRASE_project_initial_announcement_C, text:		"[greeting] [player_name], [reason_phrase] la cité de [city_name] vous demande d'envoyer [amount] charrettes en [item] dans les [time_allotted] mois pour un grand projet de construction au sein de la cité." }
  { key: PHRASE_project_reminder_P, text: 					"[greeting] [player_name], le pharaon est fou de rage. Vous n'avez toujours pas envoyé les [amount] charrettes en [item] à [city_name] pour son projet de construction. Vous avez 6 mois pour satisfaire la requête du pharaon." }
  { key: PHRASE_project_reminder_C, text: 					"[greeting] [player_name], [city_name] nécessite [amount] charrettes en [item] pour achever son projet de construction. Envoyez ce que l'on vous demande dans les 6 mois. Sinon, les responsables de la ville seront mécontents." }
  { key: PHRASE_project_overdue_P, text: 					"[greeting] [player_name], le pharaon en a assez de vos insolences. Vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name] à temps pour lui permettre de terminer son projet de construction. Si vous parvenez à les envoyer, vous arriverez peut-être à sauver la face." }
  { key: PHRASE_project_overdue_C, text: 					"[greeting] [player_name], [city_name] envisage de se plaindre auprès du pharaon car vous avez compromis la réalisation du projet en n'envoyant pas à temps les [amount] charrettes en [item]. Si vous parvenez à les envoyer, [city_name] pourra peut-être terminer ce projet et fermer les yeux." }
  { key: PHRASE_project_warning_P, text: 					"[greeting] [player_name], un projet incomplet ne fera qu'embarrasser le pharaon. Il vous reste 6 mois pour envoyer [amount] charrettes en [item] à [city_name] pour son projet de construction. En cas d'échec, le pharaon saura vous faire partager son désespoir." }
  { key: PHRASE_project_warning_C, text: 					"[greeting] [player_name], il ne vous reste que 6 mois pour envoyer [amount] charrettes en [item] à [city_name] pour son projet de construction. Si vous ne faites pas parvenir les biens convenus, mieux vaut ne pas imaginer les représailles pouvant être exercées par cette ville." }
  { key: PHRASE_project_comply_reason_P_A, text:  	  		"dans la mesure où les [amount] charrettes en [item] que vous avez envoyées sont essentielles à la réalisation du projet de construction du pharaon à [city_name]," }
  { key: PHRASE_project_comply_reason_P_B, text:	  		"les [amount] charrettes en [item] que vous avez envoyées sont essentielles à la réalisation du projet de construction du pharaon à [city_name]. Par conséquent" }
  { key: PHRASE_project_comply_reason_P_C, text:	  		"bien que les [amount] charrettes en [item] que vous avez envoyées soient essentielles à la réalisation du projet de construction du pharaon à [city_name]," }
  { key: PHRASE_project_comply_reason_C_A, text:  	  			"dans la mesure où vous avez aidé [city_name] à achever son projet dans les temps en envoyant [amount] charrettes en [item]," }
  { key: PHRASE_project_comply_reason_C_B, text:	  "vous avez aidé [city_name] à réaliser son projet dans les temps en envoyant [amount] charrettes en [item]. Malheureusement," }
  { key: PHRASE_project_comply_reason_C_C, text:	  "bien que vous ayez aidé [city_name] à achever son projet dans les temps en envoyant [amount] charrettes en [item]," }
  { key: PHRASE_project_too_late_reason_P_A, text:   "dans la mesure où vous avez interrompu le projet de construction du pharaon à [city_name] en attendant trop longtemps pour envoyer [amount] charrettes en [item]," }
  { key: PHRASE_project_too_late_reason_P_B, text:	  "le projet de construction du pharaon à [city_name] a été interrompu dans la mesure où vous avez attendu trop longtemps pour envoyer les [amount] charrettes en [item] requises. Par conséquent," }
  { key: PHRASE_project_too_late_reason_P_C, text:	  "bien que vous ayez interrompu le projet de construction du pharaon à [city_name] en attendant trop longtemps pour envoyer [amount] charrettes en [item], votre effort a été apprécié, et par conséquent," }
  { key: PHRASE_project_too_late_reason_C_A, text:  	"dans la mesure où vous avez tergiversé et n'avez pas envoyé à [city_name] les [amount] charrettes en [item]," }
  { key: PHRASE_project_too_late_reason_C_B, text:	  "vous avez tergiversé et n'avez pas envoyé à [city_name] les [amount] charrettes en [item] demandées. Malheureusement," }
  { key: PHRASE_project_too_late_reason_C_C, text:	  "bien que vous ayez tergiversé sur l'envoi à [city_name] des [amount] charrettes en [item] demandées, votre effort a été apprécié, et par conséquent," }
  { key: PHRASE_project_refuse_reason_P_A, text:	"dans la mesure où vous avez décliné la requête du pharaon relative à l'envoi de [amount] charrettes en [item] indispensables à la réalisation de son projet important à [city_name]," }
  { key: PHRASE_project_refuse_reason_P_B, text:	  "vous avez imprudemment décliné la requête du pharaon relative à l'envoi de [amount] charrettes en [item] pour son important projet à [city_name]. Par conséquent," }
  { key: PHRASE_project_refuse_reason_P_C, text:	  "bien qu'il soit très imprudent de décliner la requête du pharaon relative à l'envoi de [amount] charrettes en [item] pour son important projet à [city_name] comme vous l'avez fait," }
  { key: PHRASE_project_refuse_reason_C_A, text: 	"dans la mesure où vous avez repoussé [city_name] et sa requête de [amount] charrettes en [item]," }
  { key: PHRASE_project_refuse_reason_C_B, text:	  "vous avez repoussé [city_name] et sa requête de [amount] charrettes en [item]. En outre," }
  { key: PHRASE_project_refuse_reason_C_C, text:	  "bien que vous ayez repoussé [city_name] et sa requête de [amount] charrettes en [item]," }
  { key: PHRASE_project_no_reason_P_A, text:  	 	"pour célébrer ses nombreux haut faits," }
  { key: PHRASE_project_no_reason_P_B, text:	  "dans la mesure où il reste encore beaucoup de travail à faire" }
  { key: PHRASE_project_no_reason_P_C, text:	  "" }
  { key: PHRASE_project_no_reason_C_A, text:  	  "pour célébrer la gloire de l'Egypte," }
  { key: PHRASE_project_no_reason_C_B, text:	  "dans la mesure où il reste encore beaucoup à faire" }
  { key: PHRASE_project_no_reason_C_C, text:	  "" }

  { key:PHRASE_famine_title_P, text: 					"Famine" }
  { key:PHRASE_famine_title_C, text: 					"Famine" }
  { key:PHRASE_famine_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] la famine assaille [city_name]. Le pharaon exige que vous lui portiez secours. Vous disposez de [time_allotted] mois pour envoyer [amount] charrettes en [item] à la cité pour la soulager." }
  { key:PHRASE_famine_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] la famine a frappé [city_name] et ses citoyens meurent de faim. Envoyez [amount] charrettes en [item] dans les [time_allotted] mois. Des vies sont en jeu !" }
  { key:PHRASE_famine_reminder_P, text: 				"[greeting] [player_name], le pharaon se demande si vous avez un cœur. Vous n'avez toujours pas envoyé les [amount] charrettes en [item] à [city_name] alors que ses citoyens sont dans le besoin. Il ne vous reste que 6 mois pour satisfaire la requête du pharaon." }
  { key:PHRASE_famine_reminder_C, text: 				"[greeting] [player_name], le peuple de [city_name] se meurt de faim et vous n'avez toujours pas envoyé les [amount] charrettes en [item]. Envoyez les marchandises dans les 6 mois ou vous aurez de nombreuses morts sur la conscience." }
  { key:PHRASE_famine_overdue_P, text: 				"[greeting] [player_name], le pharaon pense que votre avarice est sans bornes. Vous n'avez rien fait pour soulager la faim de vos compatriotes. Envoyez toujours vos [amount] charrettes en [item] à [city_name] et vous pourrez éventuellement être réhabilité auprès du pharaon." }
  { key:PHRASE_famine_overdue_C, text: 				"[greeting] [player_name], les cris des affamés semblent résonner en vain. Vous n'avez pas envoyé les [amount] charrettes en [item] à [city_name] dans les temps. Comme il vaut toujours mieux tard que jamais, vous pouvez encore les envoyer en supposant qu'il reste encore quelqu'un à secourir." }
  { key:PHRASE_famine_warning_P, text: 				"[greeting] [player_name], si vous n'envoyez pas [amount] charrettes en [item] à [city_name] dans les 6 mois, votre conscience s'alourdira. Le pharaon verra d'un mauvais œil votre manque de compassion si vous n'envoyez pas les marchandises." }
  { key:PHRASE_famine_warning_C, text: 				"[greeting] [player_name], tout [city_name] se demande si votre cœur est de pierre. Il ne vous reste que 6 mois pour envoyer [amount] charrettes en [item] pour soulager ses souffrances. En refusant, vous condamnez à mort ses habitants." }
  { key:PHRASE_famine_comply_reason_P_A, text:  			"dans la mesure où vous avez envoyé les [amount] charrettes en [item] pour secourir [city_name], comme demandé par le pharaon," }
  { key:PHRASE_famine_comply_reason_P_B, text:	  		"vous avez envoyé les [amount] charrettes en [item] en réponse aux besoins de [city_name], comme demandé par le pharaon. Sage décision. Maintenant," }
  { key:PHRASE_famine_comply_reason_P_C, text:	  "bien que vous ayez été prompt à envoyer les [amount] charrettes en [item] en réponse aux besoins de [city_name], comme demandé par le pharaon, néanmoins" }
  { key:PHRASE_famine_comply_reason_C_A, text: 	"dans la mesure où les [amount] charrettes en [item] que vous avez envoyées ont permis de rassasier [city_name] pendant la famine," }
  { key:PHRASE_famine_comply_reason_C_B, text:	  "les [amount] charrettes en [item] que vous avez envoyées, ont permis de rassasier [city_name] pendant la famine.  En outre, les vizirs signalent que" }
  { key:PHRASE_famine_comply_reason_C_C, text:	  "bien que les [amount] charrettes en [item] que vous avez envoyées à [city_name] ont permis à son peuple de faire face à la famine, néanmoins" }
  { key:PHRASE_famine_too_late_reason_P_A, text:	"dans la mesure où vous avez laissé les sujets du pharaon, à [city_name], souffrir trop longtemps avant d'envoyer [amount] charrettes en [item]," }
  { key:PHRASE_famine_too_late_reason_P_B, text:	  "vous avez laissé les sujets du pharaon, à [city_name], souffrir trop longtemps avant d'envoyer les [amount] charrettes en [item] requises. Par conséquent, les vizirs signalent que" }
  { key:PHRASE_famine_too_late_reason_P_C, text:	  "bien que vous ayez laissé les sujets du pharaon à [city_name] souffrir trop longtemps avant d'envoyer les [amount] charrettes en [item] requises, votre effort a quand même été d'une certaine aide, et par conséquent," }
  { key:PHRASE_famine_too_late_reason_C_A, text:  	 	"dans la mesure où vous avez mis trop de temps pour envoyer [amount] charrettes en [item] en vue de soulager [city_name]," }
  { key:PHRASE_famine_too_late_reason_C_B, text:	  "vous avez mis trop de temps pour envoyer [amount] charrettes en [item] en vue de soulager [city_name] et la souffrance du peuple a été grande. Pour cette raison," }
  { key:PHRASE_famine_too_late_reason_C_C, text:	  "bien que vous ayez mis trop de temps pour envoyer [amount] charrettes en [item] en vue de soulager [city_name], elles ont quand même permis d'alléger les conséquences de la famine, et par conséquent," }
  { key:PHRASE_famine_refuse_reason_P_A, text:  	 	"dans la mesure où vous avez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item]," }
  { key:PHRASE_famine_refuse_reason_P_B, text:	  "dans la mesure où vous avez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item]. Cela était fort imprudent. Par conséquent, les vizirs signalent que" }
  { key:PHRASE_famine_refuse_reason_P_C, text:	  "vous avez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item], mais malgré cela" }
  { key:PHRASE_famine_refuse_reason_C_A, text:			"dans la mesure où vous avez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item]," }
  { key:PHRASE_famine_refuse_reason_C_B, text:	  "vous avez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item]. Les vizirs signalent également que" }
  { key:PHRASE_famine_refuse_reason_C_C, text:	  "bien que où vous ayez tourné le dos au peuple de [city_name] pendant la famine et retenu [amount] charrettes en [item]," }
  { key:PHRASE_famine_no_reason_P_A, text:  	 	"Le sort semble être défavorable au peuple du pharaon et" }
  { key:PHRASE_famine_no_reason_P_B, text:	  "les problèmes continuent de s'accroître, pendant que" }
  { key:PHRASE_famine_no_reason_P_C, text:	  "" }
  { key:PHRASE_famine_no_reason_C_A, text:  	"le peuple de [city_name] perd espoir, étant donné que" }
  { key:PHRASE_famine_no_reason_C_B, text:	  "les problèmes continuent de s'accroître, pendant que" }
  { key:PHRASE_famine_no_reason_C_C, text:	  "" }

  { key:PHRASE_threat_title_P, text: 					"Extorsions par Pharaon" }
  { key:PHRASE_threat_title_C, text: 					"Extorsions par une cité" }
  { key:PHRASE_threat_initial_announcement_P, text:	"[greeting] [player_name], [reason_phrase] le pharaon sans égal vous ordonne d'envoyer [amount] charrettes en [item] à [city_name] dans les [time_allotted] mois. Sinon, il attaquera votre cité." }
  { key:PHRASE_threat_initial_announcement_C, text:	"[greeting] [player_name], [reason_phrase] la cité de [city_name] vous demande d'envoyer [amount] charrettes en [item] en [time_allotted] mois. Si vous ignorez cette requête, cette cité fera marcher ses armées contre la vôtre." }
  { key:PHRASE_threat_reminder_P, text: 				"[greeting] [player_name], le fier pharaon rassemble ses troupes et passera bientôt à l'attaque. Envoyez les [amount] charrettes en [item] à [city_name] dans les 6 mois pour prévenir des développements désagréables." }
  { key:PHRASE_threat_reminder_C, text: 				"[greeting] [player_name], l'armée envoyée par [city_name] se réjouit d'avance d'un combat facile. Si vous envoyez [amount] charrettes en [item] dans les 6 mois, cette cité ne vous agressera plus. Ses soldats risquent cependant d'être déçus." }
  { key:PHRASE_threat_overdue_P, text: 				"[greeting] [player_name], le temps imparti est écoulé et le pharaon sanguinaire trépigne d'impatience. Vous pouvez encore le contenir en envoyant les [amount] charrettes en [item] à [city_name] aussi vite que possible." }
  { key:PHRASE_threat_overdue_C, text: 				"[greeting] [player_name], le cri de guerre retentit dans [city_name] en prévision de l'anéantissement de votre cité. Si vous envoyez [amount] charrettes en [item] à [city_name] aussi vite que possible, cette cité fera peut-être preuve de merci." }
  { key:PHRASE_threat_warning_P, text: 				"[greeting] [player_name], le pharaon vaniteux veut prendre de force ce que vous lui refusez. Son armée est bien préparée, mais vous pouvez encore épargner un massacre à votre cité en envoyant [amount] charrettes en [item] dans les 6 mois. Sinon, le sang coulera dans votre cité." }
  { key:PHRASE_threat_warning_C, text: 				"[greeting] [player_name], [city_name] est prête à déchaîner ses forces conquérantes. Si vous envoyez [amount] charrettes en [item] dans les 6 mois, il est possible que les agresseurs se retirent sans saccager votre cité." }
  { key:PHRASE_threat_comply_reason_P_A, text: 			"dans la mesure où vous vous êtes plié aux ordres du pharaon et avez envoyé [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_threat_comply_reason_P_B, text:	  "vous vous êtes plié aux ordres du pharaon et avez envoyé [amount] charrettes en [item] à[city_name]. Les vizirs signalent également que" }
  { key:PHRASE_threat_comply_reason_P_C, text:	  "bien que vous ayez répondu promptement aux ordres du pharaon à [city_name]," }
  { key:PHRASE_threat_comply_reason_C_A, text:  "dans la mesure où vous vous êtes plié aux ordres émis par [city_name] et avez envoyé [amount] charrettes en [item]," }
  { key:PHRASE_threat_comply_reason_C_B, text:	  "vous vous êtes plié aux ordres émis par [city_name] et avez envoyé [amount] charrettes en [item]. En outre, il semble que" }
  { key:PHRASE_threat_comply_reason_C_C, text:	  "bien que vous ayez cédé aux demandes de [city_name] pour [amount] charrettes en [item], néanmoins" }
  { key:PHRASE_threat_too_late_reason_P_A, text:  	 "le retard dans l'envoi des [amount] charrettes en [item] à [city_name] requises par le pharaon, a mis à l'épreuve sa patience, et pour cette raison," }
  { key:PHRASE_threat_too_late_reason_P_B, text:	  "le retard dans l'envoi des [amount] charrettes en [item] à [city_name] requises par le pharaon, a mis à l'épreuve sa patience. En d'autres termes :" }
  { key:PHRASE_threat_too_late_reason_P_C, text:	  "le retard dans l'envoi des [amount] charrettes en [item] à [city_name] requises par le pharaon, a mis à l'épreuve sa patience, mais néanmoins, votre effort est apprécié. Par conséquent," }
  { key:PHRASE_threat_too_late_reason_C_A, text: 		"dans la mesure où vous avez sous-estimé la menace posée par [city_name] et n'avez pas envoyé [amount] charrettes en [item] rapidement," }
  { key:PHRASE_threat_too_late_reason_C_B, text:	  "vous devez avoir sous-estimé la menace posée par [city_name], puisque vous n'avez pas envoyé [amount] charrettes en [item] rapidement. Tout ceci fait désormais parti du passé, maintenant" }
  { key:PHRASE_threat_too_late_reason_C_C, text:	  "vous avez fait preuve de beaucoup de chance dans votre négligence à ne pas envoyer immédiatement les [amount] charrettes en [item] requises à [city_name]. Néanmoins, puisque vous avez pu satisfaire à cette requête," }
  { key:PHRASE_threat_refuse_reason_P_A, text:		"dans la mesure où vous avez défié l'ordre du pharaon et n'avez pas envoyé [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_threat_refuse_reason_P_B, text:	  "vous avez défié l'ordre du pharaon et n'avez pas envoyé [amount] charrettes en [item] à [city_name]. En outre," }
  { key:PHRASE_threat_refuse_reason_P_C, text:	  "malgré la menace du pharaon, vous avez refusé d'envoyer [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_A, text:		"dans la mesure où vous avez joué avec le feu en refusant d'envoyer [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_B, text:	  "vous avez joué avec le feu en refusant d'envoyer [amount] charrettes en [item] à [city_name]. Vous devriez par conséquent être conscient que" }
  { key:PHRASE_threat_refuse_reason_C_C, text:	  "bien que vous ayez joué avec le feu en refusant d'envoyer [amount] charrettes en [item] à [city_name]," }
  { key:PHRASE_threat_no_reason_P_A, text:  	 	"dans la mesure où il est de terrible humeur," }
  { key:PHRASE_threat_no_reason_P_B, text:	  "la mauvaise humeur du pharaon semblant ne pas connaître de limite," }
  { key:PHRASE_threat_no_reason_P_C, text:	  "" }
  { key:PHRASE_threat_no_reason_C_A, text:  	 	 				"dans la mesure où [city_name] est assoiffé de gloire," }
  { key:PHRASE_threat_no_reason_C_B, text:	  "il semble que [city_name] ne soit jamais satisfait," }
  { key:PHRASE_threat_no_reason_C_C, text:	  "" }

  { key:PHRASE_eg_city_falls_title, text: 						"Chute d'une cité amie" }
  { key:PHRASE_eg_city_falls_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] cette grande ville ([city_name]) est tombée aux mains de nos ennemis." }
  { key:PHRASE_eg_city_falls_reason_A, text:  	 					"dans la mesure où [city_name] a succombé aux envahisseurs," }
  { key:PHRASE_eg_city_falls_reason_B, text:	  "[city_name] a succombé aux envahisseurs. Par ailleurs," }
  { key:PHRASE_eg_city_falls_reason_C, text:	  "bien que [city_name] ait succombé aux envahisseurs," }
  { key:PHRASE_eg_city_falls_no_reason_A, text:  		"le malheur s'est abattu à [city_name] :" }
  { key:PHRASE_eg_city_falls_no_reason_B, text:	  "il semble que les problèmes à [city_name] ne soient pas près de se terminer, étant donné que" }
  { key:PHRASE_eg_city_falls_no_reason_C, text:	  "" }

  { key:PHRASE_foreign_city_conquered_title, text: 					"Ville étrangère conquise" }
  { key:PHRASE_foreign_city_conquered_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] l'Egypte a conquis [city_name], étendant notre influence toujours plus loin !" }
  { key:PHRASE_foreign_city_conquered_reason_A, text: 				"dans la mesure où [city_name], ville étrangère, a été subjuguée par nos troupes," }
  { key:PHRASE_foreign_city_conquered_reason_B, text:	  "[city_name], ville étrangère, a été subjuguée par nos troupes ! Maintenant," }
  { key:PHRASE_foreign_city_conquered_reason_C, text:	  "bien que [city_name], ville étrangère, ait été subjuguée par nos troupes," }
  { key:PHRASE_foreign_city_conquered_no_reason_A, text:  	"grâce au succès de nos armes," }
  { key:PHRASE_foreign_city_conquered_no_reason_B, text:	  "la puissance de notre royaume continue de s'accroître. Maintenant" }
  { key:PHRASE_foreign_city_conquered_no_reason_C, text:	  "" }

  { key:PHRASE_route_opened_title, text: 						"Nouvelle route commerciale" }
  { key:PHRASE_route_opened_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] une nouvelle route commerciale vers [city_name] est donc à présent ouverte." }
  { key:PHRASE_route_opened_reason_A, text:  	 				"dans la mesure où une nouvelle route commerciale vers [city_name] est désormais disponible," }
  { key:PHRASE_route_opened_reason_B, text:	  				"une nouvelle route commerciale vers [city_name] est désormais disponible, et" }
  { key:PHRASE_route_opened_reason_C, text:	  				"bien que le commerce soit désormais possible avec [city_name]," }
  { key:PHRASE_route_opened_no_reason_A, text:  	 			"en raison de l'activité diplomatique," }
  { key:PHRASE_route_opened_no_reason_B, text:	  "il y a du changement dans l'air, étant donné que" }
  { key:PHRASE_route_opened_no_reason_C, text:	  "" }

  { key:PHRASE_route_closed_title, text:  					"Route commerciale fermée" }
  { key:PHRASE_route_closed_initial_announcement, text:     "[greeting] [player_name], [reason_phrase] votre route commerciale vers [city_name] est désormais coupée." }
  { key:PHRASE_route_closed_reason_A, text:   	 					"dans la mesure où votre route commerciale vers [city_name] est fermée," }
  { key:PHRASE_route_closed_reason_B, text: 	  "la route commerciale vers [city_name] est fermée, et de plus," }
  { key:PHRASE_route_closed_reason_C, text: 	  "bien que la route commerciale vers [city_name] soit fermée," }
  { key:PHRASE_route_closed_no_reason_A, text:   	 				"en raison de l'instabilité politique," }
  { key:PHRASE_route_closed_no_reason_B, text: 	  "cela était prévisible. Il semble que" }
  { key:PHRASE_route_closed_no_reason_C, text: 	  "" }

  { key:PHRASE_trade_city_siege_title, text:  							"Une cité marchande est assiégée" }
  { key:PHRASE_trade_city_siege_announcement, text: 			"[greeting] [player_name], [reason_phrase] un siège épuisant frappe désormais [city_name]." }
  { key:PHRASE_trade_city_siege_reason_A, text:   						"comme [city_name] est assiégée," }
  { key:PHRASE_trade_city_siege_reason_B, text: 	  "[city_name] est assiégée, et" }
  { key:PHRASE_trade_city_siege_reason_C, text: 	  "bien que [city_name] soit assiégée," }
  { key:PHRASE_trade_city_siege_no_reason_A, text:   		"les éclaireurs de l'armée apportent de terribles nouvelles. Il semble que" }
  { key:PHRASE_trade_city_siege_no_reason_B, text: 	  "leurs malheurs ne semblent pas près de finir, car" }
  { key:PHRASE_trade_city_siege_no_reason_C, text: 	  "" }

  { key:PHRASE_eg_city_saved_title, text: 					"Cité égyptienne sauvée" }
  { key:PHRASE_eg_city_saved_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [city_name] a été sauvé de nos ennemis." }
  { key:PHRASE_eg_city_saved_reason_A, text:  	 				"dans la mesure où [city_name] a été sauvé de nos ennemis," }
  { key:PHRASE_eg_city_saved_reason_B, text:	  "[city_name] a été sauvé de nos ennemis ! Maintenant," }
  { key:PHRASE_eg_city_saved_reason_C, text:	  "bien que [city_name] ait été sauvé de nos ennemis," }
  { key:PHRASE_eg_city_saved_no_reason_A, text:  			"grâce à un effort vaillant de la part de l'armée égyptienne," }
  { key:PHRASE_eg_city_saved_no_reason_B, text:	  "les combats font rage par vagues successives et pour le moment" }
  { key:PHRASE_eg_city_saved_no_reason_C, text:	  "" }

  { key:PHRASE_battle_won_title, text:  					"Victoire" }
  { key:PHRASE_battle_won_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] l'armée égyptienne a été victorieuse !" }
  { key:PHRASE_battle_won_reason_A, text:   	 		"dans la mesure où nos forces ont triomphé lors de la bataille de [city_name]," }
  { key:PHRASE_battle_won_reason_B, text: 	  "nos forces ont triomphé lors de la bataille de [city_name]. Maintenant" }
  { key:PHRASE_battle_won_reason_C, text: 	  "bien que nos forces aient triomphé lors de la bataille de [city_name]" }
  { key:PHRASE_battle_won_no_reason_A, text:   		"en raison de la vigueur des troupes bien entraînées à [city_name], une cité lointaine," }
  { key:PHRASE_battle_won_no_reason_B, text: 	  "il semble que les miracles existent toujours, car à [city_name]" }
  { key:PHRASE_battle_won_no_reason_C, text: 	  "" }

  { key:PHRASE_battle_lost_title, text:  					"Armée égyptienne vaincue" }
  { key:PHRASE_battle_lost_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] l'armée égyptienne a été vaincue à [city_name]." }
  { key:PHRASE_battle_lost_reason_A, text:   	 					"dans la mesure où l'Egypte a perdu une bataille contre ses ennemis à [city_name]," }
  { key:PHRASE_battle_lost_reason_B, text: 	  "l'Egypte a perdu une bataille contre ses ennemis à [city_name]. De plus," }
  { key:PHRASE_battle_lost_reason_C, text: 	  "bien que l'Egypte ait perdu une bataille contre ses ennemis à [city_name]," }
  { key:PHRASE_battle_lost_no_reason_A, text:   	"un grand malheur s'est abattu sur les troupes," }
  { key:PHRASE_battle_lost_no_reason_B, text: 	  "la guerre est si imprévisible. Malheureusement" }
  { key:PHRASE_battle_lost_no_reason_C, text: 	  "" }

  { key:PHRASE_acknowledgement_title, text: 					"Soumission" }
  { key:PHRASE_acknowledgement_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] votre cité est à l'abri du danger... pour l'instant." }
  { key:PHRASE_acknowledgement_reason_A, text:  	 			"dans la mesure où vous vous êtes docilement soumis face à la menace," }
  { key:PHRASE_acknowledgement_reason_B, text:	  				"vous vous êtes docilement soumis face à la menace," }
  { key:PHRASE_acknowledgement_reason_C, text:	  				"bien que vous vous soyez docilement soumis face à la menace," }
  { key:PHRASE_acknowledgement_no_reason_A, text:				"suite à un changement d'humeur," }
  { key:PHRASE_acknowledgement_no_reason_B, text:	  			"rien n'est vraiment certain, mais" }
  { key:PHRASE_acknowledgement_no_reason_C, text:	  			"" }

  { key: PHRASE_pharaoh_attacks_you_title, text: 					"Le pharaon attaque" }
  { key: PHRASE_pharaoh_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] l'armée du pharaon approche et atteindra votre cité dans [time_until_attack] mois." }
  { key: PHRASE_pharaoh_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] l'armée du pharaon se rapproche lentement et atteindra votre cité dans deux ans." }
  { key: PHRASE_pharaoh_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] l'armée du pharaon est prête à se battre et atteindra votre cité dans un an." }
  { key: PHRASE_pharaoh_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] l'armée du pharaon est impatiente d'en découdre et atteindra votre cité dans six mois." }
  { key: PHRASE_pharaoh_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] l'armée du pharaon n'est plus qu'à un mois de marche de votre cité !" }
  { key: PHRASE_pharaoh_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], l'armée du pharaon est sur nous !" }
  { key: PHRASE_pharaoh_attacks_you_reason_A, text:  	 	 		"dans la mesure où votre cité a été attaquée par l'armée du pharaon," }
  { key: PHRASE_pharaoh_attacks_you_reason_B, text:	  				"votre cité a été attaquée par l'armée du pharaon. De plus" }
  { key: PHRASE_pharaoh_attacks_you_reason_C, text:	  				"bien que votre cité ait été attaquée par l'armée du pharaon," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_A, text:  	 		"le pharaon agit parfois pour des raisons qu'il est le seul à connaître." }
  { key: PHRASE_pharaoh_attacks_you_no_reason_B, text:	  			"le pharaon est imprévisible. Maintenant," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_C, text:	  			"dans la mesure où votre influence dans le royaume est désormais si faible," }
  { key: PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text:		"votre réputation dans le royaume s'est totalement effondrée. Peut-être que de nouveaux dons au peuple égyptien pourraient encore redresser la situation, mais déjà" }

  { key: PHRASE_eg_city_attacks_you_title, text: 					"L'armée égyptienne attaque" }
  { key: PHRASE_eg_city_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] une armée égyptienne prépare son attaque et atteindra votre cité dans [time_until_attack] mois." }
  { key: PHRASE_eg_city_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] une armée égyptienne est en marche et atteindra votre cité dans deux ans." }
  { key: PHRASE_eg_city_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] votre cité subira l'assaut d'une armée égyptienne dans un an." }
  { key: PHRASE_eg_city_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] une armée égyptienne se rapproche et atteindra votre cité dans six mois." }
  { key: PHRASE_eg_city_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] une armée égyptienne approche de vos frontières et atteindra votre cité dans un mois." }
  { key: PHRASE_eg_city_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], une force d'invasion composée de troupes égyptiennes est sur nous !" }
  { key: PHRASE_eg_city_attacks_you_reason_A, text:  	 	 		"dans la mesure où votre cité a été attaquée par l'armée égyptienne," }
  { key: PHRASE_eg_city_attacks_you_reason_B, text:	  				"l'armée égyptienne a attaqué votre cité ! En outre" }
  { key: PHRASE_eg_city_attacks_you_reason_C, text:	  				"bien que votre cité ait été attaquée par l'armée égyptienne," }
  { key: PHRASE_eg_city_attacks_you_no_reason_A, text:  	 		"prenez garde :" }
  { key: PHRASE_eg_city_attacks_you_no_reason_B, text:	  			"le moment de batailler est venu, car" }
  { key: PHRASE_eg_city_attacks_you_no_reason_C, text:	  			"dans la mesure où votre réputation dans le royaume est si mauvaise," }
  { key: PHRASE_eg_city_attacks_you_because_of_low_kingdom, text:		"votre réputation dans le royaume s'est totalement effondrée. Peut-être que de nouveaux dons au peuple égyptien pourraient encore redresser la situation, mais déjà" }

  { key: PHRASE_foreign_army_attacks_you_title, text: 					"Une armée ennemie avance" }
  { key: PHRASE_foreign_army_attacks_you_initial_announcement, text:	"[greeting] [player_name], [reason_phrase] [a_foreign_army] approche et atteindra votre cité dans [time_until_attack] mois." }
  { key: PHRASE_foreign_army_attacks_you_2year_reminder, text: 			"[greeting] [player_name], [reason_phrase] dans deux ans [a_foreign_army] sera à vos portes." }
  { key: PHRASE_foreign_army_attacks_you_1year_reminder, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] cherche à vous envahir et atteindra votre cité dans un an." }
  { key: PHRASE_foreign_army_attacks_you_6month_warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] atteindra votre cité dans 6 mois. Préparez votre défense." }
  { key: PHRASE_foreign_army_attacks_you_1month_Warning, text: 			"[greeting] [player_name], [reason_phrase] [a_foreign_army] conquérante atteindra la cité dans 1 mois." }
  { key: PHRASE_foreign_army_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], [a_foreign_army] est sur nous et elle est déterminée à détruire la cité!" }
  { key: PHRASE_foreign_army_attacks_you_reason_A, text:  	 	 		"dans la mesure où votre cité a été attaquée par [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_reason_B, text:	  			"votre cité a été attaquée par [a_foreign_army], et maintenant" }
  { key: PHRASE_foreign_army_attacks_you_reason_C, text:	  			"bien que votre cité ait été attaquée par [a_foreign_army]," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_A, text:  	 		"du fait de leur rêve de conquête d'un Empire," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_B, text:	  "il semble qu'il y ait toujours des problèmes, car" }
  { key: PHRASE_foreign_army_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_rating_change_title_I, text: 					"Niveau du royaume en hausse" }
  { key: PHRASE_rating_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] vous êtes devenu plus populaire parmi le peuple égyptien et votre niveau de royaume a augmenté." }
  { key: PHRASE_rating_change_reason_I_A, text:  	 	 		"dans la mesure où votre réputation dans le royaume a augmenté récemment," }
  { key: PHRASE_rating_change_reason_I_B, text:	  "votre réputation dans le royaume s'est accrue. Maintenant" }
  { key: PHRASE_rating_change_reason_I_C, text:	  "votre réputation s'est accrue, mais" }
  { key: PHRASE_rating_change_no_reason_I_A, text:		"dans la mesure où le temps travaille pour nous," }
  { key: PHRASE_rating_change_no_reason_I_B, text:	  "c'est une bonne nouvelle, car" }
  { key: PHRASE_rating_change_no_reason_I_C, text:	  "les sacrifices de votre cité lors du combat ont été très appréciés par le peuple égyptien. Par conséquent," }
  { key: PHRASE_rating_change_title_D, text: 					"l'influence du royaume chute" }
  { key: PHRASE_rating_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] le peuple égyptien est mécontent et le niveau du royaume descend en flèche." }
  { key: PHRASE_rating_change_reason_D_A, text:  	 	 		"dans la mesure où le niveau de royaume est descendu si bas," }
  { key: PHRASE_rating_change_reason_D_B, text:	  				"votre popularité a chuté dans tout le royaume, et maintenant" }
  { key: PHRASE_rating_change_reason_D_C, text:	  				"bien que votre popularité baisse sans cesse dans le royaume," }
  { key: PHRASE_rating_change_no_reason_D_A, text:  			"en raison du mécontentement dans le royaume," }
  { key: PHRASE_rating_change_no_reason_D_B, text:	  "c'est une mauvaise nouvelle, car" }
  { key: PHRASE_rating_change_no_reason_D_C, text:	  "vos concitoyens n'approuvent pas vos actes de violence. Par conséquent" }

  { key:PHRASE_price_change_title_I, text: 					"Hausse des prix" }
  { key:PHRASE_price_change_initial_announcement_I, text:		"[greeting] [player_name], [reason_phrase] les besoins coissants en [item] ont augmenté le prix. Si l'importation de ce bien est devenue plus coûteuse, son exportation est également devenue plus rentable." }
  { key:PHRASE_price_change_reason_I_A, text:  	 	 		"dans la mesure où le prix et les besoins en [item] ont augmenté," }
  { key:PHRASE_price_change_reason_I_B, text:	  "le prix et les besoins en [item] ont augmenté, et de plus" }
  { key:PHRASE_price_change_reason_I_C, text:	  "bien que les prix aient augmenté," }
  { key:PHRASE_price_change_no_reason_I_A, text:   	"en raison d'une offre limitée dans le monde entier," }
  { key:PHRASE_price_change_no_reason_I_B, text:	  "étant donné que le marché continue d'évoluer" }
  { key:PHRASE_price_change_no_reason_I_C, text:	  "" }
  { key:PHRASE_price_change_title_D, text: 					"Baisse des prix" }
  { key:PHRASE_price_change_initial_announcement_D, text:		"[greeting] [player_name], [reason_phrase] les besoins en [item] ont baissé. Ceci va réduire la rentabilité à l'exportation." }
  { key:PHRASE_price_change_reason_D_A, text:  	 	 	"les prix ont chuté dans la mesure où les besoins en [item] ont baissé," }
  { key:PHRASE_price_change_reason_D_B, text:	  "les prix ont baissé, et de plus" }
  { key:PHRASE_price_change_reason_D_C, text:	  "bien que les prix aient baissé," }
  { key:PHRASE_price_change_no_reason_D_A, text:  		"dans la mesure où il y a une surabondance dans le royaume," }
  { key:PHRASE_price_change_no_reason_D_B, text:	  "étant donné que le marché continue de se développer" }
  { key:PHRASE_price_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_demand_change_title_I, text: 					"Commerce en hausse" }
  { key: PHRASE_demand_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] [city_name] veut désormais développer le négoce en [item]." }
  { key: PHRASE_demand_change_reason_I_A, text:  	 			"dans la mesure où [city_name] veut développer les échanges en [item]," }
  { key: PHRASE_demand_change_reason_I_B, text:	  "[city_name] souhaite à présent développer le négoce en [item]. De plus," }
  { key: PHRASE_demand_change_reason_I_C, text:	  "bien que [city_name] souhaite à présent développer le négoce en [item]," }
  { key: PHRASE_demand_change_no_reason_I_A, text:  	"dans la mesure où [city_name] se développe," }
  { key: PHRASE_demand_change_no_reason_I_B, text:	  "les temps changent, et" }
  { key: PHRASE_demand_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_demand_change_title_D, text: 					"Commerce en baisse" }
  { key: PHRASE_demand_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] [city_name] a décidé de réduire le volume des échanges en [item] avec vous." }
  { key: PHRASE_demand_change_reason_D_A, text:  	 			"dans la mesure où [city_name] ne fait plus autant d'échanges en [item]," }
  { key: PHRASE_demand_change_reason_D_B, text:	  "[city_name] ne fait plus autant de commerce, et" }
  { key: PHRASE_demand_change_reason_D_C, text:	  "bien que [city_name] ne fasse plus autant de commerce," }
  { key: PHRASE_demand_change_no_reason_D_A, text:			"dans la mesure où [city_name] fait des économies," }
  { key: PHRASE_demand_change_no_reason_D_B, text:	  "les temps changent, et" }
  { key: PHRASE_demand_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_earthquake_title, text: 					"Tremblement de terre !" }
  { key: PHRASE_earthquake_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] le sable a bougé sous nos pieds. Notre pays ne sera plus jamais le même. Faites votre possible pour réparer les dommages causés à votre cité et à votre peuple par le tremblement de terre." }
  { key: PHRASE_earthquake_reason_A, text:  	 	 					"en raison d'un terrible tremblement de terre," }
  { key: PHRASE_earthquake_reason_B, text:	  "en plus d'un terrible tremblement de terre," }
  { key: PHRASE_earthquake_reason_C, text:	  "malgré un terrible tremblement de terre" }
  { key: PHRASE_earthquake_no_reason_A, text:  	 						"la cité vit dans la crainte, car" }
  { key: PHRASE_earthquake_no_reason_B, text:	  "des problèmes ébranlent une nouvelle fois la cité, car" }
  { key: PHRASE_earthquake_no_reason_C, text:	  "" }

  { key: PHRASE_stormy_seas_title, text: 					"Tempêtes" }
  { key: PHRASE_stormy_seas_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] la mer démontée menace d'engloutir des navires commerciaux. Il faudra compter plusieurs mois avant une accalmie et avant de trouver des marchands prêts à se risquer sur la grande bleue. En attendant, il est impossible de faire du commerce par mer." }
  { key: PHRASE_stormy_seas_reason_A, text:  	 	 					"en raison de tempêtes incroyablement fortes," }
  { key: PHRASE_stormy_seas_reason_B, text:	  "alors que nous avons été ennuyés par de récentes tempêtes," }
  { key: PHRASE_stormy_seas_reason_C, text:	  "malgré les terribles tempêtes" }
  { key: PHRASE_stormy_seas_no_reason_A, text:  	 					"la tempête fait rage et" }
  { key: PHRASE_stormy_seas_no_reason_B, text:	  "nos problèmes ne font que commencer, car" }
  { key: PHRASE_stormy_seas_no_reason_C, text:	  "" }
                         
  { key: PHRASE_sandstorm_title, text: 						"Tempêtes de sable" }
  { key: PHRASE_sandstorm_initial_announcement, text: 		"[greeting] [player_name], [reason_phrase] des nuages de sable obscurcissent les routes, les recouvrant complètement à certains endroits. Les marchands ne vont pas se risquer à sortir dans ces conditions. Tant que le vent ne sera pas tombé, aucun marchand ne sortira." }
  { key: PHRASE_sandstorm_reason_A, text:  	 				"dans la mesure où les marchands ne vont pas sortir pendant une tempête de sable et du fait de l'interruption du commerce terrestre," }
  { key: PHRASE_sandstorm_reason_B, text:	  "les tempêtes de sable empêchent les marchands de poursuivre leur chemin. Par conséquent," }
  { key: PHRASE_sandstorm_reason_C, text:	  "malgré les récentes tempêtes de sable qui ont entravé le commerce," }
  { key: PHRASE_sandstorm_no_reason_A, text:  	 						"en raison de vents forts," }
  { key: PHRASE_sandstorm_no_reason_B, text:	  "le désert est un endroit dangereux, car" }
  { key: PHRASE_sandstorm_no_reason_C, text:	  "" }

  { key: PHRASE_wage_change_title_I, text: 					"Hausse des salaires" }
  { key: PHRASE_wage_change_initial_announcement_I, text: 	"[greeting] [player_name], [reason_phrase] les salaires ont augmenté dans tout le royaume. Vos ouvriers risquent de rechercher de meilleurs emplois s'ils sont moins bien payés que leurs homologues des autres cités." }
  { key: PHRASE_wage_change_reason_I_A, text:  	 	 		"dans la mesure où les salaires ont été augmentés dans tout le royaume," }
  { key: PHRASE_wage_change_reason_I_B, text:	  "les salaires ont augmenté dans tout le royaume et" }
  { key: PHRASE_wage_change_reason_I_C, text:	  "bien que les salaires aient augmenté dans tout le royaume," }
  { key: PHRASE_wage_change_no_reason_I_A, text:  	"les temps changent, et maintenant" }
  { key: PHRASE_wage_change_no_reason_I_B, text:	  "certains se réjouissent, d'autres se plaignent, car" }
  { key: PHRASE_wage_change_no_reason_I_C, text:	  "" }
  { key: PHRASE_wage_change_title_D, text: 					"Baisse des salaire" }
  { key: PHRASE_wage_change_initial_announcement_D, text: 	"[greeting] [player_name], [reason_phrase] les salaires ont baissé dans tout le royaume d'Egypte. Partout le peuple travaille pour une somme moindre." }
  { key: PHRASE_wage_change_reason_D_A, text:  	 	 				"dans la mesure où les salaires ont baissé," }
  { key: PHRASE_wage_change_reason_D_B, text:	  "les salaires ont baissé, et de plus," }
  { key: PHRASE_wage_change_reason_D_C, text:	  "bien que les salaires aient baissé," }
  { key: PHRASE_wage_change_no_reason_D_A, text:  		"pour tenter de réduire les coûts," }
  { key: PHRASE_wage_change_no_reason_D_B, text:	  "certains sont en colère, mais les nomarques, quant à eux, jubilent, car" }
  { key: PHRASE_wage_change_no_reason_D_C, text:	  "" }

  { key: PHRASE_bad_water_title, text: 					"Eau contaminée" }
  { key: PHRASE_bad_water_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] certains citoyens sont devenus malades à cause de l'eau. Il ne vous reste plus qu'à espérer que le problème ne va pas s'aggraver." }
  { key: PHRASE_bad_water_reason_A, text:  	 	 				"en raison d'une contamination récente de l'eau," }
  { key: PHRASE_bad_water_reason_B, text:	  "la contamination récente de l'eau s'est révélée des plus inopportune. Maintenant," }
  { key: PHRASE_bad_water_reason_C, text:	  "bien que l'eau ait été récemment contaminée," }
  { key: PHRASE_bad_water_no_reason_A, text:  		"la cité est victime de malchance, et" }
  { key: PHRASE_bad_water_no_reason_B, text:	  ", ceci est vraiment malheureux. Il semble que" }
  { key: PHRASE_bad_water_no_reason_C, text:	  "" }

  { key: PHRASE_goldmine_cavein_title, text: 					"Une mine s'effondre" }
  { key: PHRASE_goldmine_cavein_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] une mine d'or s'est effondrée. Nos architectes n'ont rien pu faire. Il ne vous reste plus qu'à espérer que les mineurs ont pu s'échapper à temps." }
  { key: PHRASE_goldmine_cavein_reason_A, text:  	 	 			"suite à l'effondrement d'une mine d'or" }
  { key: PHRASE_goldmine_cavein_reason_B, text:	  "le récent effondrement d'une mine d'or s'est révélé des plus inopportun. Maintenant," }
  { key: PHRASE_goldmine_cavein_reason_C, text:	  "bien qu'une mine d'or se soit effondrée récemment," }
  { key: PHRASE_goldmine_cavein_no_reason_A, text: 		"en raison de l'instabilité du sable," }
  { key: PHRASE_goldmine_cavein_no_reason_B, text:	  "sans aucun avertissement," }
  { key: PHRASE_goldmine_cavein_no_reason_C, text:	  "" }

  { key: PHRASE_landslide_title, text: 					"Glissement de terrain" }
  { key: PHRASE_landslide_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] un énorme glissement de terrain a coupé une route commerciale. Il faudra compter plusieurs mois pour la rouvrir aux marchands." }
  { key: PHRASE_landslide_reason_A, text:  	 	 				"suite à un glissement de terrain récent," }
  { key: PHRASE_landslide_reason_B, text:	  "les récents glissements de terrain ont été dévastateurs. Maintenant," }
  { key: PHRASE_landslide_reason_C, text:	  "bien qu'il y ait eu récemment de terribles glissements de terrain," }
  { key: PHRASE_landslide_no_reason_A, text:  	 					"les nouvelles sont effroyables :" }
  { key: PHRASE_landslide_no_reason_B, text:	  "sans aucun avertissement" }
  { key: PHRASE_landslide_no_reason_C, text:	  "" }

  { key: PHRASE_flood_fails_title, text: 					"Absence de crue probable" }
  { key: PHRASE_flood_fails_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] les prêtres sont porteurs de nouvelles alarmantes... ils craignent que la prochaine inondation soit inexistante ! Consultez le nilomètre régulièrement... si la prédiction des prêtres se confirme, la cité devra se préparer au pire." }
  { key: PHRASE_flood_fails_reason_A, text:  	 	 					"dans la mesure où il a des risques que la crue soit inexistante," }
  { key: PHRASE_flood_fails_reason_B, text:	  "il a des risques que la crue soit inexistante, et" }
  { key: PHRASE_flood_fails_reason_C, text:	  "bien qu'il y ait des risques que la crue soit inexistante," }
  { key: PHRASE_flood_fails_no_reason_A, text:		"en raison de la sécheresse en Afrique," }
  { key: PHRASE_flood_fails_no_reason_B, text:	  "nos problèmes ne font que commencer, étant donné que" }
  { key: PHRASE_flood_fails_no_reason_C, text:	  "" }

  { key : PHRASE_perfect_flood_title, text: 					"Crue parfaite attendue" }
  { key : PHRASE_perfect_flood_initial_announcement, text: 	"[greeting] [player_name], [reason_phrase] c'est un don du ciel, les chances que la crue soit importante sont optimales ! Consultez le nilomètre périodiquement. Si la prédiction se noircit, la cité n'aura pas le temps de se préparer." }
  { key : PHRASE_perfect_flood_reason_A, text:  	 	 				"dans la mesure où il a des chances que l'inondation soit fertile," }
  { key : PHRASE_perfect_flood_reason_B, text:	  "il a des chances que l'inondation soit fertile et" }
  { key : PHRASE_perfect_flood_reason_C, text:	  "bien qu'il y ait des chances que l'inondation soit fertile," }
  { key : PHRASE_perfect_flood_no_reason_A, text:  	 					"les moussons d'Afrique sont attendues, par conséquent" }
  { key : PHRASE_perfect_flood_no_reason_B, text:	  "nous avons vraiment de la chance, car" }
  { key : PHRASE_perfect_flood_no_reason_C, text:	  "" }

  { key: PHRASE_bedouin_attacks_you_title, text: 					"L'armée bédouine attaque" }
  { key: PHRASE_bedouin_attacks_you_initial_announcement, text:		"[greeting] [player_name], [reason_phrase] une armée bédouine approche de la cité et l'attaquera dans [time_until_attack] mois." }
  { key: PHRASE_bedouin_attacks_you_2year_reminder, text:			"[greeting] [player_name], [reason_phrase] une armée bédouine se rapproche inexorablement et atteindra la cité dans deux ans." }
  { key: PHRASE_bedouin_attacks_you_1year_reminder, text:			"[greeting] [player_name], [reason_phrase] une armée bédouine est en marche et atteindra la cité dans 1 an." }
  { key: PHRASE_bedouin_attacks_you_6month_warning, text:			"[greeting] [player_name], [reason_phrase] une armée bédouine est sur le pied de guerre et atteindra la cité dans six mois." }
  { key: PHRASE_bedouin_attacks_you_1month_warning, text:			"[greeting] [player_name], [reason_phrase] une armée bédouine est toute proche et atteindra la cité dans un mois." }
  { key: PHRASE_bedouin_attacks_you_city_attacked_alert, text:  	"[greeting] [player_name], une armée bédouine est sur nous !" }
  { key: PHRASE_bedouin_attacks_you_reason_A, text:  	 	 		"dans la mesure où votre cité a réussi à repousser l'armée bédouine," }
  { key: PHRASE_bedouin_attacks_you_reason_B, text:	  				"votre cité a réussi à repousser l'armée bédouine. De plus," }
  { key: PHRASE_bedouin_attacks_you_reason_C, text:	  "bien que votre cité ait réussi à repousser l'armée bédouine," }
  { key: PHRASE_bedouin_attacks_you_no_reason_A, text:  	"motivée par la promesse de butin," }
  { key: PHRASE_bedouin_attacks_you_no_reason_B, text:	  "nos problèmes sont de taille, car" }
  { key: PHRASE_bedouin_attacks_you_no_reason_C, text:	  "" }

  { key: PHRASE_gift_title_P, text: 				"Un don de Pharaon" }
  { key: PHRASE_gift_title_C, text: 				"Un don d'un voisin" }
  { key: PHRASE_gift_granted_P, text:				"[greeting] [player_name], [reason_phrase] le pharaon a décidé de vous faire don de [amount] charrettes en [item] en provenance de [city_name]." }
  { key: PHRASE_gift_granted_C, text:				"[greeting] [player_name], [reason_phrase] [city_name] souhaite vous faire don de [amount] charrettes en [item]." }
  { key: PHRASE_gift_cash_granted_P, text:			"[greeting] [player_name], [reason_phrase] le pharaon a décidé de vous faire don de [amount] debens en provenance de [city_name]." }
  { key: PHRASE_gift_cash_granted_C, text:			"[greeting] [player_name], [reason_phrase] la cité de [city_name] souhaite vous faire don de [amount] debens." }
  { key: PHRASE_gift_partial_space_P, text:			"[greeting] [player_name], [reason_phrase] le pharaon a décidé de vous faire don de [amount] charrettes en [item] en provenance de [city_name]. Vous ne disposez pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour recevoir ce don. Cependant, vous pouvez en accepter la moitié en faisant un effort." }
  { key: PHRASE_gift_partial_space_C, text:			"[greeting] [player_name], [reason_phrase] souhaite vous faire don de [amount] charrettes en [item]. Vous ne disposez pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour recevoir ce don. Cependant, vous pouvez en accepter la moitié en faisant un effort." }
  { key: PHRASE_gift_insufficient_space_P, text: 	"[greeting] [player_name], [reason_phrase] le pharaon a décidé de vous faire don de [amount] charrettes en [item] en provenance de [city_name]. Cependant, vous ne disposez pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour recevoir ce don. Faites de la place et il sera livré de nouveau le mois prochain." }
  { key: PHRASE_gift_insufficient_space_C, text: 	"[greeting] [player_name], [reason_phrase] [city_name] souhaite vous faire don de [amount] charrettes en [item]. Cependant, vous ne disposez pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour recevoir ce don. Faites de la place et il sera livré de nouveau le mois prochain." }
  { key: PHRASE_gift_last_chance_P, text: 			"[greeting] [player_name] , par ordre du pharaon, [city_name] a tenté de vous faire parvenir un don de [amount] charrettes en [item]. Cependant, vous ne disposez toujours pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour le recevoir dans son intégralité. Vous avez trop fait attendre les émissaires et ces derniers s'impatientent. Acceptez un don partiel dès maintenant, car ils risquent de ne plus revenir."  }
  { key: PHRASE_gift_last_chance_C, text: 			"[greeting] [player_name], [city_name] a tenté de vous faire parvenir un don de [amount] charrettes en [item]. Cependant, vous ne disposez toujours pas de suffisamment d'espace dans vos entrepôts ou dans vos greniers pour le recevoir dans son intégralité. Les émissaires s'impatientent. Acceptez un don partiel dès maintenant, car ils risquent de ne plus revenir." }
  { key: PHRASE_gift_forfeited_P, text: 			"[greeting] [player_name], vous manquez toujours d'espace pour recevoir le don de [amount] charrettes en [item] en provenance de [city_name]. Ce don vous est désormais refusé." }
  { key: PHRASE_gift_forfeited_C, text: 			"[greeting] [player_name], vous manquez toujours d'espace pour recevoir le don de [amount] charrettes en [item] en provenance de [city_name]. Ce don vous est désormais refusé." }
  { key: PHRASE_gift_accepted_P, text: 				"Par ordre du pharaon, les entrepôts et les greniers de votre cité ont été pleinement ravitaillés en [item] en provenance de [city_name]." }
  { key: PHRASE_gift_accepted_C, text: 				"Les entrepôts et les greniers de votre cité ont été pleinement ravitaillés en [item] en provenance de [city_name]." }
  { key: PHRASE_gift_cash_accepted_P, text: 		"Par ordre du pharaon, [amount_granted] debens ont été versés dans votre trésor." }
  { key: PHRASE_gift_cash_accepted_C, text: 		"Grâce à [city_name], [amount_granted] debens ont été versés dans votre trésor." }
  { key: PHRASE_gift_postponed_P, text:				"Les émissaires en provenance de [city_name] reviendront dans un mois pour l'approvisionnement en [item]." }
  { key: PHRASE_gift_postponed_C, text: 			"Les émissaires en provenance de [city_name] reviendront dans un mois pour l'approvisionnement en [item]." }
  { key: PHRASE_gift_refused_P, text: 				"Bien que vous ayez refusé ce don en [item] en provenance de [city_name], je suis sûr que d'autres seront moins difficiles." }
  { key: PHRASE_gift_refused_C, text: 				"Bien que vous ayez refusé ce don en [item] en provenance de [city_name], je suis sûr que d'autres seront moins difficiles." }
  { key: PHRASE_gift_accepted_reason_P_A, text:  	 		"parce que vous avez accepté un don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_accepted_reason_P_B, text:	  "dans le sillage du dernier don en provenance de [city_name]," }
  { key: PHRASE_gift_accepted_reason_P_C, text:	  "bien que vous ayez accepté un don de [amount] charrettes en [item] en provenance de [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_A, text:  	 		"parce que vous avez accepté un don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_accepted_reason_C_B, text:	  "dans le sillage du dernier don en provenance de [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_C, text:	  "bien que vous ayez accepté un don de [amount] charrettes en [item] en provenance de [city_name]," }
  { key: PHRASE_gift_forfeited_reason_P_A, text:  	 		"dans la mesure où vous avez refusé un don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_P_B, text:	  "vous avez refusé un don de [amount] charrettes en [item] en provenance de [city_name]. Par conséquent," }
  { key: PHRASE_gift_forfeited_reason_P_C, text:	  "bien que vous ayez refusé le don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_A, text:  	 		"dans la mesure où vous avez refusé le don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_forfeited_reason_C_B, text:	  "vous avez refusé le don de [amount] charrettes en [item] en provenance de [city_name]. Par conséquent," }
  { key: PHRASE_gift_forfeited_reason_C_C, text:	  "bien que vous ayez refusé le don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_refused_reason_P_A, text:  	 		"dans la mesure où vous avez refusé un don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_refused_reason_P_B, text:	  "vous avez refusé un don en [item] de [amount]unités en provenance de [city_name]. Maintenant," }
  { key: PHRASE_gift_refused_reason_P_C, text:	  "bien que vous ayez refusé un don de [amount] charrettes en [item] en provenance de [city_name]," }
  { key: PHRASE_gift_refused_reason_C_A, text:  	 		"dans la mesure où vous avez refusé un don de [amount] charrettes en [item] en provenance de [city_name]" }
  { key: PHRASE_gift_refused_reason_C_B, text:	  "vous avez refusé un don de [amount] charrettes en [item] en provenance de [city_name]. Maintenant," }
  { key: PHRASE_gift_refused_reason_C_C, text:	  "bien que vous ayez refusé un don en [item] de [amount] en provenance de [city_name]," }
  { key: PHRASE_gift_no_reason_P_A, text:  					"dans la mesure où vous avez besoin d'aide" }
  { key: PHRASE_gift_no_reason_P_B, text:	  "dans la mesure où la bienveillance du pharaon est sans limite," }
  { key: PHRASE_gift_no_reason_P_C, text:	  "les sacrifices des hommes de votre cité lors de la bataille ont été fort appréciés par le pharaon. Par conséquent," }
  { key: PHRASE_gift_no_reason_C_A, text:  					"dans la mesure où vous avez besoin d'aide" }
  { key: PHRASE_gift_no_reason_C_B, text:	  "dans la mesure où les Egyptiens viennent toujours en aide à leurs compatriotes," }
  { key: PHRASE_gift_no_reason_C_C, text:	  "les sacrifices des hommes de votre cité lors de la bataille ont été fort appréciés par le peuple égyptien. Par conséquent" }

  { key: PHRASE_pharaoh_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] l'armée du pharaon s'apprête à prendre votre cité par la force." }
  { key: PHRASE_eg_city_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] une armée égyptienne a débarqué et envahit la cité en ce moment même !" }
  { key: PHRASE_foreign_army_attacks_you_disembarked_alert, text:  	"[greeting] [player_name], [reason_phrase] [a_foreign_army] a débarqué et attaque la cité en ce moment même ! Que Seth vienne à notre aide !" }
  { key: PHRASE_bedouin_attacks_you_disembarked_alert, text:  		"[greeting] [player_name], [reason_phrase] une armée bédouine ennemie a accosté sur nos côtes !" }

  { key: PHRASE_pyramid_congratulations_title, text:			"Pyramide achevée !" }
  { key: PHRASE_pyramid_congratulations, text:					"[greeting] [player_name], ceci est incontestablement une œuvre majestueuse ! Après de nombreux mois de labeur, la pyramide est finalement achevée !" }
  { key: PHRASE_stepped_pyramid_congratulations_title, text:	"Pyramide achevée !" }
  { key: PHRASE_stepped_pyramid_congratulations, text:			"[greeting] [player_name], la pyramide à degrés est enfin terminée ! Ce monument restera à jamais la manifestation de votre grandeur." }
  { key: PHRASE_bent_pyramid_congratulations_title, text:		"Pyramide achevée !" }
  { key: PHRASE_bent_pyramid_congratulations, text:				"[greeting] [player_name], la construction de la pyramide penchée est enfin terminée ! Elle représente une œuvre majeure pour votre cité." }
  { key: PHRASE_mudbrick_pyramid_congratulations_title, text:	"Pyramide achevée !" }
  { key: PHRASE_mudbrick_pyramid_congratulations, text:			"[greeting] [player_name], les tailleurs apportent la touche finale à la pyramide en polissant la dernière couche de calcaire : la pyramide en briques est désormais achevée !" }
  { key: PHRASE_mastaba_congratulations_title, text:			"Mastaba achevé !" }
  { key: PHRASE_mastaba_congratulations, text:					"[greeting] [player_name], la dernière brique a été posée sur le mastaba : celui-ci est désormais achevé !" }
  { key: PHRASE_sphinx_congratulations_title, text:				"Sphinx achevé !" }
  { key: PHRASE_sphinx_congratulations, text:					"[greeting] [player_name], les tailleurs de pierre ont enfin fini de tailler l'imposant sphinx. Ce monument surveillera l'Egypte pour la fin des temps." }
  { key: PHRASE_obelisk_congratulations_title, text:			"Obélisque achevé !" }
  { key: PHRASE_obelisk_congratulations, text:					"[greeting] [player_name], les tailleurs de pierre ont apporté la touche finale à l'obélisque : celui-ci est enfin terminé." }
  { key: PHRASE_sun_temple_congratulations_title, text:			"Temple solaire achevé !" }
  { key: PHRASE_sun_temple_congratulations, text:				"[greeting] [player_name], après plusieurs mois de dur labeur, la construction du temple solaire arrive finalement à son terme. Ceci représente une œuvre majeure pour votre cité !" }
  { key: PHRASE_alex_library_congratulations_title, text:		"Bibliothèque d'Alexandrie achevée !" }
  { key: PHRASE_alex_library_congratulations, text:				"[greeting] [player_name], après un travail acharné, les magnifiques portes de la grande bibliothèque d'Alexandrie sont prêtes à s'ouvrir aux érudits du monde entier." }
  { key: PHRASE_abu_simbel_congratulations_title, text:			"Temple d'Abou Simbel fini" }
  { key: PHRASE_abu_simbel_congratulations, text:				"[greeting] [player_name], quel ouvrage magnifique ! Vos talentueux ouvriers ont créé un monument éternel qui célèbre la gloire de notre pharaon et la puissance de l'Egypte." }
  { key: PHRASE_caesareum_congratulations_title, text:			"Caesareum achevé !" }
  { key: PHRASE_caesareum_congratulations, text:				"[greeting] [player_name], le temple sacré et les jardins resplendissants du Caesareum sont enfin terminés ! Des commentaires sur sa grande beauté se répandent déjà dans toute la région." }
  { key: PHRASE_lighthouse_congratulations_title, text:			"Phare de Pharos achevé !" }
  { key: PHRASE_lighthouse_congratulations, text:    "[greeting] [player_name], la sueur et le sang ont coulé, mais les ouvriers ont achevé la construction du magnifique phare de Pharos ! Sa tour attire déjà les marchands du monde entier." }
  { key: PHRASE_mausoleum_congratulations_title, text:			"Mausolée achevé !" }
  { key: PHRASE_mausoleum_congratulations, text:				"[greeting] [player_name], le mausolée sacré est finalement terminé ! Cette œuvre est majeure pour votre cité." }
  { key: PHRASE_smalltomb_congratulations_title, text:			"Petite tombe achevée !" }
  { key: PHRASE_smalltomb_congratulations, text:				"[greeting] [player_name], la construction de la petite tombe royale est terminée. Espérons que vos ouvriers n'auront pas à en construire une autre avant de nombreuses années." }
  { key: PHRASE_medtomb_congratulations_title, text:			"Tombe moyenne achevée !" }
  { key: PHRASE_medtomb_congratulations, text:				"[greeting] [player_name], la construction de la tombe royale moyenne est enfin terminée et ce monument est rempli d'offrandes funéraires. Elle est prête à accompagner notre pharaon défunt dans son voyage vers l'au-delà." }
  { key: PHRASE_largetomb_congratulations_title, text:			"Grande tombe terminée !" }
  { key: PHRASE_largetomb_congratulations, text:				"[greeting] [player_name], après de longues années de dur labeur au fond de la terre, vos ouvriers ont terminé la plus belle tombe jamais construite ! Quelle superbe récompense !" }
  { key: PHRASE_grandtomb_congratulations_title, text:			"Très grande tombe terminée !" }
  { key: PHRASE_grandtomb_congratulations, text:				"[greeting] [player_name], après bien des efforts, la très grande tombe est terminée, et ce n'est pas trop tôt car il paraît que le pharaon est épuisé. Ce magnifique ouvrage sera parfait pour accompagner notre souverain le long de son voyage dans l'au-delà." }

  { key: PHRASE_troopcarryover_title, text:   "Retour d'anciens soldats" }
  { key: PHRASE_troopcarryover_initial_announcement, text: "Les meilleurs soldats de la mission précédente souhaitent rejoindre vos factions. Construisez [reason_phrase] pour ces guerriers et ils reviendront." }
  { key: PHRASE_troopcarryover_inf_only, text: "un fort de fantassins" }
  { key: PHRASE_troopcarryover_arch_only, text: "un fort d'archers" }
  { key: PHRASE_troopcarryover_char_only, text: "un fort de conducteurs de chars" }
  { key: PHRASE_troopcarryover_inf_arch, text: "des forts de fantassins et d'archers" }
  { key: PHRASE_troopcarryover_inf_char, text: "des forts de fantassins et de conducteurs de chars" }
  { key: PHRASE_troopcarryover_arch_char, text: "des forts d'archers et de conducteurs de chars" }
  { key: PHRASE_troopcarryover_all_three, text: "des forts de fantassins, d'archers et de conducteurs de chars" }
  { key: PHRASE_pyramid_speedup_title, text: "Une construction bénie" }
  { key: PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] se réjouit de votre dévotion et souhaite encourager votre projet de construction. [reason_phrase] va donner sa bénédiction ; en attendant, vos ouvriers peuvent prendre un peu de repos." }
  { key: PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] récompense votre dévotion en contribuant à votre projet de construction. [reason_phrase] va donner sa bénédiction ; en attendant, vos ouvriers peuvent prendre un peu de repos." }
  { key: PHRASE_pyramid_speedup_Osiris, text: "Osiris" }
  { key: PHRASE_pyramid_speedup_Ra, text: "Rê" }
  { key: PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
  { key: PHRASE_pyramid_speedup_Seth, text: "Seth" }
  { key: PHRASE_pyramid_speedup_Bast, text: "Bastet" }
]

