log_info("akhenaten: eventmsg italian started")

eventmsg_it = [
  { key:PHRASE_egyptian_city_attacked_title_P, text: "Città egizia sotto attacco" }
  { key:PHRASE_egyptian_city_attacked_title_C, text: "Città egizia sotto attacco" }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: "[greeting] [player_name],[reason_phrase] gli infedeli stanno attaccando. Il potente Faraone ti ordina di inviare truppe alla città egizia di [city_name] per combattere il nemico. Devi inviare delle truppe entro [travel_time] mesi." }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] [city_name], una città egizia, è sotto attacco e ha bisogno del tuo aiuto. Devi inviare delle truppe entro [travel_time] mesi." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_P, text: "[greeting] [player_name], le divine armate del Faraone stanno ancora combattendo gli invasori di [city_name]. Devi inviare rinforzi entro i prossimi sei mesi, pena l'incorrere nell'ira del Faraone." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_C, text: "[greeting] [player_name], hai dimenticato [city_name]? Invia le tue truppe entro i prossimi sei mesi, o patirai terribili conseguenze." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_P, text: "[greeting] [player_name], il Faraone sta diventando impaziente nell'attesa delle tue truppe. Invia i rinforzi a [city_name] in fretta, o sarà troppo tardi." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_C, text: "[greeting] [player_name], [city_name] potrebbe presto soccombere ai suoi nemici. Invia le tue truppe in fretta, se vuoi aiutare [city_name] nel momento del bisogno." }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "perché le tue truppe hanno sconfitto i nemici del Faraone a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "le tue truppe hanno sconfitto i nemici del Faraone a [city_name]. Per questo motivo," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "sebbene le tue truppe abbiano sconfitto i nemici del Faraone a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "perché le tue truppe hanno combattuto bene contro il nemico a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "le tue truppe hanno combattuto bene contro il nemico a [city_name]. In più," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "sebbene le tue truppe abbiano combattuto bene contro il nemico a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "perché hai ritardato a inviare le truppe per aiutare l'esercito del Faraone a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "L'esercito del Faraone ha perso la battaglia a [city_name], perché le tue truppe sono arrivate troppo tardi. Inoltre," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "le tue truppe sono arrivate troppo tardi per aiutare l'esercito del Faraone nella battaglia contro il nemico a [city_name], comunque il tuo impegno è stato apprezzato. Come risultato" }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "perché hai atteso troppo prima di inviare le truppe a difendere [city_name]," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "le tue truppe non sono arrivate in tempo per agevolare la difesa di [city_name]. Inoltre," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "le tue truppe sono arrivate troppo tardi per aiutare [city_name], ma dato che ti sei impegnato e hai dimostrato di essere pronto a sacrificare i tuoi soldati," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "perché hai negato al Faraone le truppe necessarie a combattere il nemico a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "il Faraone ha saputo che hai negato l'invio di truppe necessarie per combattere il nemico a [city_name]. In più," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "sebbene tu abbia negato al Faraone le truppe necessarie per combattere il nemico a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "perché ti sei rifiutato di inviare le truppe richieste per sconfiggere i barbari a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: "[city_name] lamenta il mancato invio di truppe necessarie per sconfiggere il suo nemico. Inoltre," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "sebbene ti sia rifiutato di inviare le truppe necessarie per sconfiggere i barbari a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "perché le truppe che hai inviato a [city_name] erano troppo deboli per sconfiggere il nemico," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "le deboli truppe che hai inviato per aiutare il Faraone sono state sconfitte a [city_name]. Inoltre," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "nonostante il fatto che le tue truppe fossero troppo deboli per aiutare il Faraone a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "perché le truppe che hai inviato a [city_name] non erano abbastanza forti per sconfiggere gli attaccanti," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "le tue deboli forze sono state sconfitte a [city_name]. In più," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "sebbene le tue truppe non abbiano vinto lo scontro a [city_name]," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "per soddisfare il loro desiderio di conquista," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "i tuoi guai non sono ancora finiti, infatti" }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: "" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "nel proseguimento di una lunga faida sanguinosa," }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "i tuoi guai non sono ancora finiti, infatti" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: "" }
  { key:PHRASE_distant_battle_title_P, text: "Battaglia lontana" }
  { key:PHRASE_distant_battle_title_C, text: "Battaglia lontana" }
  { key:PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] l'esercito egizio sta combattendo una dura guerra. Il Faraone ti ordina di inviare le tue truppe alla lontana città di [city_name] per schierarti al loro fianco. Invia le tue truppe entro [travel_time] mesi." }
  { key:PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] l'esercito egizio è impegnato in battaglia presso la lontana città di [city_name] e ti chiede di predisporre dei rinforzi. Invia le tue truppe di rinforzo entro [travel_time] mesi." }
  { key:PHRASE_distant_battle_first_reminder_P, text: "[greeting] [player_name], la battaglia sanguinosa continua a infuriare a [city_name], e il Faraone ha ancora bisogno delle tue truppe. Inviale entro i prossimi sei mesi, se vuoi che giungano in tempo. La non ottemperanza porterà disastrose conseguenze." }
  { key:PHRASE_distant_battle_first_reminder_C, text: "[greeting] [player_name], la battaglia presso [city_name] infuria tuttora. Se vuoi che le tue truppe arrivino in tempo, devi inviarle entro sei mesi. Questa è la tua occasione di condividere la gloria di una grande vittoria." }
  { key:PHRASE_distant_battle_last_reminder_P, text: "[greeting] [player_name], l'esercito egizio sta ancora guerreggiando a [city_name], e il nobile Faraone richiede i tuoi rinforzi immediati. Non è bene rischiare l'ira del Faraone mentre è concentrato sull'arte della guerra." }
  { key:PHRASE_distant_battle_last_reminder_C, text: "[greeting] [player_name], la battaglia a [city_name] continua. Se invierai le tue truppe in fretta, l'Egitto potrà gioire di una nuova gloriosa vittoria." }
  { key:PHRASE_distant_battle_comply_reason_P_A, text: "perché la vittoria del Faraone a [city_name] è dipesa dalle tue truppe," }
  { key:PHRASE_distant_battle_comply_reason_P_B, text: "le tue truppe hanno aiutato il Faraone nella sua vittoria presso [city_name]. Oh, ancora una cosa," }
  { key:PHRASE_distant_battle_comply_reason_P_C, text: "anche se le tue truppe hanno aiutato il Faraone nella sua vittoria presso [city_name]," }
  { key:PHRASE_distant_battle_comply_reason_C_A, text: "perché le tue truppe sono risultate vincenti a [city_name]," }
  { key:PHRASE_distant_battle_comply_reason_C_B, text: "le tue truppe si sono dimostrate fondamentali nella battaglia presso [city_name]. Inoltre," }
  { key:PHRASE_distant_battle_comply_reason_C_C, text: "sebbene le tue truppe abbiano fornito un aiuto fondamentale per la vittoria a [city_name]," }
  { key:PHRASE_distant_battle_too_late_reason_P_A, text: "perché le tue truppe non sono arrivate in tempo per aiutare il Faraone a [city_name]," }
  { key:PHRASE_distant_battle_too_late_reason_P_B, text: "le tue truppe sono arrivate troppo tardi per aiutare il Faraone a [city_name]. In più," }
  { key:PHRASE_distant_battle_too_late_reason_P_C, text: "sebbene le tue truppe siano giunte troppo tardi per aiutare il Faraone a [city_name], il tuo impegno e sacrificio per il bene del regno è stato comunque apprezzato. Come risultato," }
  { key:PHRASE_distant_battle_too_late_reason_C_A, text: "perché le tue truppe sono arrivate troppo tardi nella battaglia di [city_name]," }
  { key:PHRASE_distant_battle_too_late_reason_C_B, text: "le tue truppe sono arrivate troppo tardi nella battaglia di [city_name]. Inoltre," }
  { key:PHRASE_distant_battle_too_late_reason_C_C, text: "sebbene le tue truppe siano arrivate troppo tardi nella battaglia di [city_name], il tuo impegno e sacrificio per il bene del regno è stato comunque apprezzato. Come risultato," }
  { key:PHRASE_distant_battle_refuse_reason_P_A, text: "perché hai palesemente ignorato la richiesta del Faraone di inviare truppe in aiuto del suo esercito a [city_name]," }
  { key:PHRASE_distant_battle_refuse_reason_P_B, text: "hai bellamente ignorato la richiesta del Faraone di inviare truppe in aiuto al suo esercito presso [city_name]. Sei stato poco saggio, comunque," }
  { key:PHRASE_distant_battle_refuse_reason_P_C, text: "sebbene tu non abbia soddisfatto la richiesta del Faraone di inviare truppe in suo aiuto presso [city_name]," }
  { key:PHRASE_distant_battle_refuse_reason_C_A, text: "perché ti sei rifiutato di inviare le truppe necessarie al combattimento presso [city_name]," }
  { key:PHRASE_distant_battle_refuse_reason_C_B, text: "hai rifiutato di inviare le truppe necessarie per la battaglia presso [city_name], lasciando loro poche speranze di vittoria. Per questo motivo," }
  { key:PHRASE_distant_battle_refuse_reason_C_C, text: "sebbene tu abbia rifiutato di inviare le truppe necessarie per la battaglia presso [city_name]," }
  { key:PHRASE_distant_battle_lost_battle_reason_P_A, text: "perché le truppe che hai inviato a [city_name] erano troppo deboli per combattere l'avversario del Faraone," }
  { key:PHRASE_distant_battle_lost_battle_reason_P_B, text: "le truppe che hai inviato a [city_name] sono state sconfitte dal nemico del Faraone. Inoltre," }
  { key:PHRASE_distant_battle_lost_battle_reason_P_C, text: "sebbene le truppe che hai inviato a [city_name] siano state sconfitte dal nemico del Faraone," }
  { key:PHRASE_distant_battle_lost_battle_reason_C_A, text: "perché le truppe che hai inviato a [city_name] non avevano forza a sufficienza per contrastare il nemico," }
  { key:PHRASE_distant_battle_lost_battle_reason_C_B, text: "le truppe che hai inviato a [city_name] non avevano forza a sufficienza per sconfiggere il nemico. Inoltre, sappi che" }
  { key:PHRASE_distant_battle_lost_battle_reason_C_C, text: "sebbene le truppe che hai inviato a [city_name] non siano riuscite a sconfiggere il nemico," }
  { key:PHRASE_distant_battle_no_reason_P_A, text: "ascolta le urla di battaglia, perché   " }
  { key:PHRASE_distant_battle_no_reason_P_B, text: "i nostri guai non sono finiti" }
  { key:PHRASE_distant_battle_no_reason_P_C, text: "" }
  { key:PHRASE_distant_battle_no_reason_C_A, text: "avverti i tuoi soldati, perché" }
  { key:PHRASE_distant_battle_no_reason_C_B, text: "i guai non sono finiti, perché" }
  { key:PHRASE_distant_battle_no_reason_C_C, text: "" }
  { key:PHRASE_general_request_title_P, text: "Il Faraone richiede merci" }
  { key:PHRASE_general_request_title_C, text: "Una città richiede merci" }
  { key:PHRASE_general_request_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] il nobile Faraone ti chiede di inviare [amount] [item] a [city_name] entro [time_allotted] mesi. Se soddisferai la sua richiesta, il Faraone accrescerà la stima nei tuoi confronti." }
  { key:PHRASE_general_request_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] ti chiede di inviare [amount] [item] entro [time_allotted] mesi. Aiutando [city_name] potremmo ricevere futuri benefici." }
  { key:PHRASE_general_request_reminder_P, text: "[greeting] [player_name], il Faraone si chiede perché [city_name] non ha ricevuto [amount] [item]. Hai ancora 6 mesi per soddisfare la richiesta del Faraone." }
  { key:PHRASE_general_request_reminder_C, text: "[greeting] [player_name], [city_name] attende con ansia l'arrivo di [amount] [item]. Ti restano 6 mesi per provvedere." }
  { key:PHRASE_general_request_overdue_P, text: "[greeting] [player_name], vuoi provocare il Faraone? Non hai inviato [amount] [item] a [city_name] in tempo. Il Faraone potrebbe ritenersi soddisfatto se mostrassi un minimo di impegno nel soddisfare tale richiesta." }
  { key:PHRASE_general_request_overdue_C, text: "[greeting] [player_name], il tuo tempo è scaduto e ancora non hai inviato [amount] [item] a [city_name], come precedentemente richiesto. [city_name] potrebbe rivedere la sua opinione se mostrassi un minimo di impegno nel soddisfare tale richiesta." }
  { key:PHRASE_general_request_warning_P, text: "[greeting] [player_name], ti restano solo sei mesi per soddisfare la richiesta del Faraone di inviare [amount] [item] a [city_name]. Ignorala a tuo rischio e pericolo." }
  { key:PHRASE_general_request_warning_C, text: "[greeting] [player_name], invia [amount] [item] a [city_name] entro sei mesi, non rischiare di crearti un nemico alle porte di casa." }
  { key:PHRASE_general_request_comply_reason_P_A, text: "perché hai soddisfatto la richiesta del Faraone di inviare [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_comply_reason_P_B, text: "hai soddisfatto la richiesta del Faraone di inviare [amount] [item] a [city_name]. A proposito," }
  { key:PHRASE_general_request_comply_reason_P_C, text: "hai soddisfatto la richiesta del Faraone di inviare [amount] [item] a [city_name], comunque," }
  { key:PHRASE_general_request_comply_reason_C_A, text: "perché hai inviato [amount] [item] a [city_name], come aveva richiesto," }
  { key:PHRASE_general_request_comply_reason_C_B, text: "[city_name] ha ricevuto [amount] [item] come aveva richiesto. Devi anche sapere che" }
  { key:PHRASE_general_request_comply_reason_C_C, text: "anche se hai inviato [amount] [item] a [city_name], come aveva richiesto," }
  { key:PHRASE_general_request_too_late_reason_P_A, text: "perché hai tardato a soddisfare le richiesta del Faraone di [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_P_B, text: "La richiesta del Faraone di [amount] [item] non è stata soddisfatta perché ti sei mosso troppo tardi. In più," }
  { key:PHRASE_general_request_too_late_reason_P_C, text: "hai tardato a soddisfare la richiesta del Faraone di [amount] [item], comunque il tuo impegno è stato apprezzato. Come risultato," }
  { key:PHRASE_general_request_too_late_reason_C_A, text: "perché hai tardato a soddisfare la richiesta di [city_name] per [amount] [item]," }
  { key:PHRASE_general_request_too_late_reason_C_B, text: "hai tardato a inviare [amount] [item] a [city_name]. Devi anche sapere che" }
  { key:PHRASE_general_request_too_late_reason_C_C, text: "nonostante tu abbia tardato a inviare [amount] [item] a [city_name], il tuo impegno è stato apprezzato. Come risultato," }
  { key:PHRASE_general_request_refuse_reason_P_A, text: "perché hai ignorato la richiesta del Faraone per [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_P_B, text: "hai ignorato la richiesta del Faraone per [amount] [item], ed egli ne è dispiaciuto. Inoltre," }
  { key:PHRASE_general_request_refuse_reason_P_C, text: "anche se hai ignorato la richiesta del Faraone per [amount] [item]," }
  { key:PHRASE_general_request_refuse_reason_C_A, text: "perché non hai inviato [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_refuse_reason_C_B, text: "non hai inviato [amount] [item] a [city_name], e la città ne è dispiaciuta. Nel frattempo," }
  { key:PHRASE_general_request_refuse_reason_C_C, text: "nonostante tu non abbia inviato [amount] [item] a [city_name]," }
  { key:PHRASE_general_request_no_reason_P_A, text: "per aumentare le scorte della sua tenuta,    " }
  { key:PHRASE_general_request_no_reason_P_B, text: "pare che l'avidità del Faraone non abbia mai fine, infatti" }
  { key:PHRASE_general_request_no_reason_P_C, text: "" }
  { key:PHRASE_general_request_no_reason_C_A, text: "per soddisfare i bisogni dei cittadini," }
  { key:PHRASE_general_request_no_reason_C_B, text: "pare che non debba mai finire, infatti" }
  { key:PHRASE_general_request_no_reason_C_C, text: "" }
  { key:PHRASE_great_festival_title_P, text: "Festività per [god]" }
  { key:PHRASE_great_festival_title_C, text: "Festività grandiosa per [god]" }
  { key:PHRASE_great_festival_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] il Faraone vuole indire una festività grandiosa per [god] a [city_name] e ha bisogno di rifornimenti dalla tua città. Hai [time_allotted] mesi per inviare [amount] carri di [item]." }
  { key:PHRASE_great_festival_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] ti chiede di inviare [amount] [item] per la festività grandiosa di [god]. La città ha bisogno delle tue merci entro [time_allotted] mesi." }
  { key:PHRASE_great_festival_reminder_P, text: "[greeting] [player_name], ti restano solo 6 mesi per inviare [amount] [item] a [city_name] per la festività grandiosa di [god]. Il Faraone sarà molto dispiaciuto se non soddisferai tale richiesta." }
  { key:PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], la festività grandiosa di [god] a [city_name] è imminente, e tu non hai ancora inviato [amount] [item]. Ti restano solo sei mesi per inviare le merci." }
  { key:PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], il tempo è scaduto, e il Faraone ha dovuto celebrare la festività grandiosa di [god] senza i tuoi rifornimenti. Invia [amount] [item] a [city_name] comunque, e forse il nobile Faraone avrà modo di perdonarti." }
  { key:PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] si è dispiaciuta di doversi procurare le merci per la festività grandiosa di [god] altrove. Puoi riparare all'offesa cercando di inviare comunque [amount] [item]." }
  { key:PHRASE_great_festival_warning_P, text: "[greeting] [player_name], ti restano solo 6 mesi per inviare al Faraone [amount] [item] presso [city_name], necessari per la festività grandiosa di [god]. La maledizione si abbatta su colui che osa sfidare la furia fiammeggiante del Faraone!" }
  { key:PHRASE_great_festival_warning_C, text: "[greeting] [player_name], hai profondamente deluso [city_name]. Invia [amount] [item] entro i prossimi sei mesi, se vuoi continuare a mantenere dei buoi rapporti con la città." }
  { key:PHRASE_great_festival_comply_reason_P_A, text: "perché hai onorato il Faraone e [god] inviando [amount] [item] a [city_name] in tempo per la festività grandiosa," }
  { key:PHRASE_great_festival_comply_reason_P_B, text: "hai onorato il Faraone e la divinità [god] inviando [amount] [item] a [city_name] in tempo per la festività grandiosa. Inoltre," }
  { key:PHRASE_great_festival_comply_reason_P_C, text: "sebbene tu abbia onorato il Faraone e la divinità [god] inviando [amount] [item] a [city_name] in tempo per la festività grandiosa," }
  { key:PHRASE_great_festival_comply_reason_C_A, text: "perché hai aiutato [city_name] a celebrare la festività grandiosa di [god], inviando [amount] [item]," }
  { key:PHRASE_great_festival_comply_reason_C_B, text: "hai aiutato [city_name] a celebrare la festività grandiosa per [god], inviando [amount] [item], un gesto molto apprezzato. Inoltre," }
  { key:PHRASE_great_festival_comply_reason_C_C, text: "anche se hai aiutato [city_name] a celebrare la sua festività grandiosa per [god], inviando [amount] [item]," }
  { key:PHRASE_great_festival_too_late_reason_P_A, text: "perché hai inviato troppo tardi [amount] [item] per la festività grandiosa di [god] tenuto dal Faraone a [city_name]," }
  { key:PHRASE_great_festival_too_late_reason_P_B, text: "hai inviato [amount] [item] troppo tardi per la festività grandiosa di [god], tenuto dal Faraone a [city_name]. In più," }
  { key:PHRASE_great_festival_too_late_reason_P_C, text: "anche se la spedizione di [amount] [item] è arrivata troppo tardi per la festività grandiosa di [god] tenuta dal Faraone a [city_name], dato che ti sei comunque impegnato," }
  { key:PHRASE_great_festival_too_late_reason_C_A, text: "perché la spedizione di [amount] [item] richiesta da [city_name] per la festività grandiosa di [god] non è arrivata in tempo," }
  { key:PHRASE_great_festival_too_late_reason_C_B, text: "la spedizione di [amount] [item] richiesta da [city_name] per la festività grandiosa di [god] non è arrivata in tempo. Inoltre," }
  { key:PHRASE_great_festival_too_late_reason_C_C, text: "anche se la spedizione di [amount] [item] inviata a [city_name] non è arrivata in tempo per la festività grandiosa di [god], dato che hai fatto del tuo meglio," }
  { key:PHRASE_great_festival_refuse_reason_P_A, text: "perché non hai soddisfatto la richiesta di [amount] [item] del Faraone per la festività grandiosa di [god] a [city_name]," }
  { key:PHRASE_great_festival_refuse_reason_P_B, text: "hai ignorato la richiesta del Faraone di [amount] [item] per la festività grandiosa di [god] da celebrare a [city_name]. Inoltre," }
  { key:PHRASE_great_festival_refuse_reason_P_C, text: "nonostante tu abbia ignorato la richiesta del Faraone di [amount] [item] per la festività grandiosa di [god] da celebrare a [city_name]," }
  { key:PHRASE_great_festival_refuse_reason_C_A, text: "perché hai snobbato [city_name] e la sua richiesta di [amount] [item] per la festività grandiosa di [god]," }
  { key:PHRASE_great_festival_refuse_reason_C_B, text: "hai snobbato [city_name] e la sua richiesta di [amount] [item] per la festività grandiosa di [god]. Inoltre," }
  { key:PHRASE_great_festival_refuse_reason_C_C, text: "anche se hai snobbato [city_name] e la sua richiesta di [amount] [item] per la festività grandiosa di [god]," }
  { key:PHRASE_great_festival_no_reason_P_A, text: "perché il Faraone vuole onorare la divinità," }
  { key:PHRASE_great_festival_no_reason_P_B, text: "perché [god] è ancora insoddisfatto," }
  { key:PHRASE_great_festival_no_reason_P_C, text: "" }
  { key:PHRASE_great_festival_no_reason_C_A, text: "perché [city_name] è benedetta da [god]," }
  { key:PHRASE_great_festival_no_reason_C_B, text: "perché [god] è ancora insoddisfatto," }
  { key:PHRASE_great_festival_no_reason_C_C, text: "" }
  { key:PHRASE_project_title_P, text: "Costruzione per il Faraone" }
  { key:PHRASE_project_title_C, text: "Progetto di costruzione" }
  { key:PHRASE_project_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] il Faraone sta costruendo un monumento così grande che ti chiede di inviare [amount] [item] a [city_name] entro [time_allotted] mesi. Ti ricordo che tutti i monumenti accrescono la Gloria dell'Egitto." }
  { key:PHRASE_project_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] ti chiede di inviare [amount] [item] entro [time_allotted] mesi per la costruzione di un grande monumento in città." }
  { key:PHRASE_project_reminder_P, text: "[greeting] [player_name], il Faraone è sul punto di adirarsi. Ancora non hai inviato [amount] [item] a [city_name] per il suo progetto di costruzione. Ti restano sei mesi per soddisfare la richiesta del Faraone." }
  { key:PHRASE_project_reminder_C, text: "[greeting] [player_name], [city_name] ha bisogno di [amount] [item] per completare il suo progetto di costruzione. Invia i rifornimenti entro 6 mesi, o il governatore della città si riterrà offeso." }
  { key:PHRASE_project_overdue_P, text: "[greeting] [player_name], il Faraone è disgustato dalla tua insolenza. Non hai inviato [amount] [item] a [city_name] in tempo per completare il progetto di costruzione. Se riuscirai a inviarli, forse potrai salvare la faccia." }
  { key:PHRASE_project_overdue_C, text: "[greeting] [player_name], [city_name] sta pensando di denunciarti al Faraone. Dato che non hai inviato [amount] [item] in tempo, forse non riuscirà a completare il suo monumento. Se li invierai comunque, [city_name] forse riuscirà a terminare la costruzione e tacerà nei confronti della tua negligenza." }
  { key:PHRASE_project_warning_P, text: "[greeting] [player_name], un progetto incompleto può solo frustrare il nobile Faraone. Ti restano sei mesi per inviare [amount] [item] a [city_name] per il suo progetto di costruzione. Se fallisci, il Faraone sfogherà la sua frustrazione su di te." }
  { key:PHRASE_project_warning_C, text: "[greeting] [player_name], ti restano solo sei mesi per inviare [amount] [item] a [city_name] per il suo progetto di costruzione. Se non invierai le merci, la città potrebbe vendicarsi aspramente." }
  { key:PHRASE_project_comply_reason_P_A, text: "perché i [amount] [item] che hai inviato sono stati fondamentali per completare in tempo la costruzione del Faraone a [city_name]," }
  { key:PHRASE_project_comply_reason_P_B, text: "la spedizione di [amount] [item] è stata fondamentale per terminare la costruzione del Faraone a [city_name]. Inoltre," }
  { key:PHRASE_project_comply_reason_P_C, text: "anche se la spedizione di [amount] [item] è stata essenziale per terminare la costruzione del Faraone a [city_name]," }
  { key:PHRASE_project_comply_reason_C_A, text: "perché hai aiutato [city_name] a completare il suo progetto in tempo, inviando [amount] [item]," }
  { key:PHRASE_project_comply_reason_C_B, text: "hai aiutato [city_name] a rispettare i tempi inviando [amount] [item]. Per questo motivo," }
  { key:PHRASE_project_comply_reason_C_C, text: "anche se hai aiutato [city_name] a completare il suo progetto per tempo inviando [amount] [item]," }
  { key:PHRASE_project_too_late_reason_P_A, text: "perché hai ostacolato il progetto del Faraone a [city_name], ritardando l'invio di [amount] [item]," }
  { key:PHRASE_project_too_late_reason_P_B, text: "La costruzione del Faraone a [city_name] si è fermata perché hai atteso troppo prima di inviare [amount] [item], come invece richiesto. Inoltre," }
  { key:PHRASE_project_too_late_reason_P_C, text: "anche se hai ritardato la costruzione del Faraone a [city_name] attendendo troppo a lungo prima di inviare [amount] [item], il tuo impegno è stato comunque apprezzato, quindi" }
  { key:PHRASE_project_too_late_reason_C_A, text: "perché hai temporeggiato e non hai inviato a [city_name] [amount] [item]," }
  { key:PHRASE_project_too_late_reason_C_B, text: "hai tardato a inviare presso [city_name] la spedizione di [amount] [item] richiesta. Per questo motivo," }
  { key:PHRASE_project_too_late_reason_C_C, text: "anche se hai tardato a inviare presso [city_name] la spedizione di [amount] [item] richiesta, il tuo impegno è stato apprezzato, quindi" }
  { key:PHRASE_project_refuse_reason_P_A, text: "perché non hai risposto alla richiesta del Faraone per [amount] [item] per il suo importante progetto a [city_name]," }
  { key:PHRASE_project_refuse_reason_P_B, text: "hai stupidamente ignorato la richiesta del Faraone di [amount] [item] per il suo importante progetto a [city_name].  Inoltre," }
  { key:PHRASE_project_refuse_reason_P_C, text: "anche se hai stupidamente ignorato la richiesta del Faraone di [amount] [item] per il suo progetto a [city_name]," }
  { key:PHRASE_project_refuse_reason_C_A, text: "perché hai snobbato [city_name] e la sua richiesta di [amount] [item]," }
  { key:PHRASE_project_refuse_reason_C_B, text: "hai snobbato [city_name] e la sua richiesta di [amount] [item]. In più," }
  { key:PHRASE_project_refuse_reason_C_C, text: "anche se hai snobbato [city_name] e la sua richiesta di [amount] [item]," }
  { key:PHRASE_project_no_reason_P_A, text: "per celebrare le sue numerose vittorie," }
  { key:PHRASE_project_no_reason_P_B, text: "perché c'è ancora molto lavoro da fare" }
  { key:PHRASE_project_no_reason_P_C, text: "" }
  { key:PHRASE_project_no_reason_C_A, text: "per onorare la gloria dell'Egitto," }
  { key:PHRASE_project_no_reason_C_B, text: "perché c'è ancora molto da fare" }
  { key:PHRASE_project_no_reason_C_C, text: "" }
  { key:PHRASE_famine_title_P, text: "Carestia" }
  { key:PHRASE_famine_title_C, text: "Carestia" }
  { key:PHRASE_famine_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] la carestia opprime [city_name]. Il Faraone ti chiede di offrire il tuo aiuto. Hai [time_allotted] mesi per inviare [amount] [item] per alleviare le sofferenze della città." }
  { key:PHRASE_famine_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] la carestia ha colpito [city_name], e la sua gente muore di fame. Invia [amount] [item] entro [time_allotted] mesi. Molte vite sono in pericolo!" }
  { key:PHRASE_famine_reminder_P, text: "[greeting] [player_name], il Faraone si chiede se tu abbia un cuore. Ancora non hai inviato [amount] [item] a [city_name], e la sua gente è ancora nel bisogno. Ti restano sei mesi per soddisfare la richiesta del Faraone." }
  { key:PHRASE_famine_reminder_C, text: "[greeting] [player_name], la gente di [city_name] sta morendo di fame, e tu non hai ancora inviato [amount] [item]. Invia i rifornimenti entro sei mesi, o le sofferenze degli affamati diverranno lamenti funebri." }
  { key:PHRASE_famine_overdue_P, text: "[greeting] [player_name], il Faraone ti ritiene un indegno serpente strisciante. Non hai fatto nulla per alleviare la sofferenza dei tuoi compatrioti. Puoi ancora inviare [amount] [item] a [city_name], così forse potrai riabilitare la tua persona agli occhi del Faraone." }
  { key:PHRASE_famine_overdue_C, text: "[greeting] [player_name], le grida affamate dei tuoi connazionali sono indirizzate a orecchie insensibili. Non hai inviato [amount] [item] a [city_name] in tempo. Meglio tardi che mai... se invierai ugualmente il cibo, forse potrai procurare un minimo di sollievo - se ci sarà ancora qualcuno che potrà beneficiarne." }
  { key:PHRASE_famine_warning_P, text: "[greeting] [player_name], se non invierai [amount] [item] a [city_name] entro sei mesi, infliggerai ulteriori sofferenze. Il Faraone maledirà la tua negligenza." }
  { key:PHRASE_famine_warning_C, text: "[greeting] [player_name], la gente di [city_name] si chiede se tu abbia un cuore. Ti restano solo 6 mesi per inviare [amount] [item] per alleviare la sua sofferenza. Se ti rifiuti, la morte di molti innocenti peserà sulla tua coscienza." }
  { key:PHRASE_famine_comply_reason_P_A, text: "perché hai inviato con prontezza [amount] [item] in risposta alla richiesta della città di [city_name], come il Faraone aveva ordinato," }
  { key:PHRASE_famine_comply_reason_P_B, text: "hai inviato prontamente [amount] [item] in risposta alla richiesta di [city_name], come il Faraone aveva ordinato. Sei stato saggio. Ora," }
  { key:PHRASE_famine_comply_reason_P_C, text: "anche se hai inviato prontamente [amount] [item] a [city_name], come ordinato dal Faraone, tuttavia" }
  { key:PHRASE_famine_comply_reason_C_A, text: "perché la spedizione di [amount] [item] ha riempito le pance dei cittadini [city_name] durante la carestia," }
  { key:PHRASE_famine_comply_reason_C_B, text: "la spedizione di [amount] [item] inviata a [city_name] ha riempito le pance dei suoi cittadini durante la carestia. Inoltre, il consigliere ha detto che" }
  { key:PHRASE_famine_comply_reason_C_C, text: "anche se la spedizione di [amount] [item] inviata alla gente di [city_name] ha aiutato ad allontanare la carestia, tuttavia" }
  { key:PHRASE_famine_too_late_reason_P_A, text: "perché hai causato lunghe sofferenze al popolo del Faraone a [city_name], attendendo troppo a lungo prima di inviare [amount] [item]," }
  { key:PHRASE_famine_too_late_reason_P_B, text: "hai causato sofferenza alla gente di [city_name], facendole attendere troppo a lungo la spedizione di [amount] [item] che stava aspettando. Inoltre, i consiglieri dicono che" }
  { key:PHRASE_famine_too_late_reason_P_C, text: "anche se hai causato sofferenza alla gente di [city_name], attendendo troppo a lungo prima di inviare la spedizione di [amount] [item] che le era necessaria, hai comunque dimostrato buona volontà, quindi" }
  { key:PHRASE_famine_too_late_reason_C_A, text: "perché hai impiegato troppo tempo per inviare la spedizione di [amount] [item] necessaria per alleviare le sofferenze di [city_name]," }
  { key:PHRASE_famine_too_late_reason_C_B, text: "hai atteso troppo prima di inviare la spedizione di [amount] [item] per alleviare i tormenti degli abitanti di [city_name], e la loro sofferenza è stata grande. Inoltre," }
  { key:PHRASE_famine_too_late_reason_C_C, text: "anche se hai atteso troppo prima di inviare la spedizione di [amount] [item] agli abitanti di [city_name], il cibo ha comunque limitato le conseguenze della carestia, quindi" }
  { key:PHRASE_famine_refuse_reason_P_A, text: "perché hai deluso il Faraone e la sua gente a [city_name] durante la carestia, negando loro l'invio di [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_P_B, text: "hai voltato le spalle al Faraone e alla sua gente di [city_name] durante la carestia, negando una spedizione di [amount] [item]. Sei stato stupido. Inoltre, i consiglieri dicono che" }
  { key:PHRASE_famine_refuse_reason_P_C, text: "hai voltato le spalle al Faraone e alla gente di [city_name] durante la carestia, negando la spedizione di [amount] [item], ma nonostante questo" }
  { key:PHRASE_famine_refuse_reason_C_A, text: "perché hai voltato la schiena alla gente di [city_name] durante la carestia e le hai negato [amount] [item]," }
  { key:PHRASE_famine_refuse_reason_C_B, text: "hai voltato le spalle alla gente di [city_name] durante la carestia e le hai negato [amount] [item]. I consiglieri dicono inoltre che" }
  { key:PHRASE_famine_refuse_reason_C_C, text: "anche se hai voltato le spalle alla gente di [city_name] durante la carestia e le hai negato [amount] [item]," }
  { key:PHRASE_famine_no_reason_P_A, text: "La fortuna ha distolto il suo sguardo dal popolo del Faraone, e" }
  { key:PHRASE_famine_no_reason_P_B, text: "i guai non cessano mai, infatti" }
  { key:PHRASE_famine_no_reason_P_C, text: "" }
  { key:PHRASE_famine_no_reason_C_A, text: "la gente di [city_name] sta perdendo la speranza, perché" }
  { key:PHRASE_famine_no_reason_C_B, text: "i guai non cessano mai, infatti" }
  { key:PHRASE_famine_no_reason_C_C, text: "" }
  { key:PHRASE_threat_title_P, text: "Estorsione dal Faraone" }
  { key:PHRASE_threat_title_C, text: "Estorsione da un'altra città" }
  { key:PHRASE_threat_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] il Faraone ti ordina di inviare [amount] [item] a [city_name] entro [time_allotted] mesi. Altrimenti attaccherà la tua ridente città." }
  { key:PHRASE_threat_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] ti ordina di inviare [amount] [item] entro [time_allotted]. Se non farai pervenire la merce, [city_name] invierà le sue armate contro la tua ridente città." }
  { key:PHRASE_threat_reminder_P, text: "[greeting] [player_name], il nobile Faraone sta radunando il suo esercito e presto gli ordinerà di attaccare. Se vuoi evitare dei guai, invia [amount] [item] a [city_name] entro 6 mesi." }
  { key:PHRASE_threat_reminder_C, text: "[greeting] [player_name], l'esercito di [city_name] non vede l'ora di impugnare le armi. Se invierai [amount] [item] entro 6 mesi, la città cesserà l'aggressione. I suoi soldati, comunque, saranno molto delusi." }
  { key:PHRASE_threat_overdue_P, text: "[greeting] [player_name], il tuo tempo è scaduto e il Faraone ha sete di sangue. Hai ancora la possibilità di tenere il suo esercito lontano se invii [amount] [item] a [city_name] il più presto possibile." }
  { key:PHRASE_threat_overdue_C, text: "[greeting] [player_name], [city_name] si prepara alla guerra e le urla di battaglia echeggiano in tutte le sue strade. Invia [amount] [item] a [city_name] il più presto possibile e forse potrà mostrare un po' di pietà." }
  { key:PHRASE_threat_warning_P, text: "[greeting] [player_name], il glorioso Faraone ha intenzione di prendersi con la forza ciò che non vuoi concedergli di tua volontà. Il suo esercito è pronto, ma tu puoi ancora salvare la tua città inviandogli [amount] [item] entro 6 mesi. Altrimenti subirai un bagno di sangue." }
  { key:PHRASE_threat_warning_C, text: "[greeting] [player_name], le forze di conquista di [city_name] sono pronte a marciare. Se invierai [amount] [item] entro 6 mesi, gli attaccanti potrebbero decidere di non colpire la tua città." }
  { key:PHRASE_threat_comply_reason_P_A, text: "perché hai ceduto al Faraone e hai inviato [amount] [item] a [city_name]," }
  { key:PHRASE_threat_comply_reason_P_B, text: "hai ceduto al Faraone e hai inviato [amount] [item] a [city_name]. Inoltre, i consiglieri dicono che" }
  { key:PHRASE_threat_comply_reason_P_C, text: "anche se hai fatto ciò che il Faraone ti ha chiesto per la città di [city_name]," }
  { key:PHRASE_threat_comply_reason_C_A, text: "perché hai accettato la richiesta di [city_name] e hai inviato [amount] [item]," }
  { key:PHRASE_threat_comply_reason_C_B, text: "hai accettato la richiesta di [city_name] e hai inviato [amount] [item]. Inoltre, pare che" }
  { key:PHRASE_threat_comply_reason_C_C, text: "anche se hai ceduto alle richieste di [city_name] e hai inviato [amount] [item], tuttavia" }
  { key:PHRASE_threat_too_late_reason_P_A, text: "il ritardo dell'invio di [amount] [item] a [city_name], come da ordini del Faraone, mette a dura prova la sua pazienza e per questo motivo" }
  { key:PHRASE_threat_too_late_reason_P_B, text: "il ritardo dell'invio di [amount] [item] a [city_name], secondo gli ordini del Faraone, mette a dura prova la sua pazienza. Un'altra notizia:" }
  { key:PHRASE_threat_too_late_reason_P_C, text: "il ritardo dell'invio di [amount] [item] a [city_name], come da ordini del Faraone, mette a dura prova la sua pazienza, comunque, il tuo impegno è apprezzato. Quindi," }
  { key:PHRASE_threat_too_late_reason_C_A, text: "perché hai sottostimato la minaccia di [city_name] e non hai inviato [amount] [item] in fretta," }
  { key:PHRASE_threat_too_late_reason_C_B, text: "forse hai sottostimato la minaccia di [city_name], dato che non hai inviato [amount] [item] in fretta. Ma questo riguarda il passato, ora" }
  { key:PHRASE_threat_too_late_reason_C_C, text: "hai sfidato la fortuna ritardando l'invio di [amount] [item] a [city_name], come ti era stato richiesto. Tuttavia, dato che ci sei comunque riuscito," }
  { key:PHRASE_threat_refuse_reason_P_A, text: "perché hai ignorato l'ordine del Faraone di inviare [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_P_B, text: "hai ignorato l'ordine del Faraone di inviare [amount] [item] a [city_name]. Inoltre," }
  { key:PHRASE_threat_refuse_reason_P_C, text: "nonostante la tua insensibilità alle minacce del Faraone, che aveva richiesto l'invio di [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_A, text: "perché hai volontariamente sfidato la sorte quando ti sei rifiutato di inviare [amount] [item] a [city_name]," }
  { key:PHRASE_threat_refuse_reason_C_B, text: "hai volontariamente sfidato la sorte quando ti sei rifiutato di inviare [amount] [item] a [city_name]. Devi inoltre sapere che" }
  { key:PHRASE_threat_refuse_reason_C_C, text: "anche se hai volontariamente sfidato la sorte quando ti sei rifiutato di inviare [amount] [item] a [city_name]," }
  { key:PHRASE_threat_no_reason_P_A, text: "perché è di cattivo umore," }
  { key:PHRASE_threat_no_reason_P_B, text: "in quanto il cattivo umore del Faraone non si è ancora risollevato," }
  { key:PHRASE_threat_no_reason_P_C, text: "" }
  { key:PHRASE_threat_no_reason_C_A, text: "perché [city_name] anela alla gloria," }
  { key:PHRASE_threat_no_reason_C_B, text: "pare che [city_name] non sia mai soddisfatta," }
  { key:PHRASE_threat_no_reason_C_C, text: "" }
  { key:PHRASE_eg_city_falls_title, text: "Città egizia caduta" }
  { key:PHRASE_eg_city_falls_initial_announcement, text: "[greeting] [player_name], [reason_phrase] la possente città [city_name] è caduta per mano dei nemici." }
  { key:PHRASE_eg_city_falls_reason_A, text: "perché [city_name] è caduta sotto le forze degli invasori," }
  { key:PHRASE_eg_city_falls_reason_B, text: "[city_name] è caduta per mano degli invasori. Inoltre," }
  { key:PHRASE_eg_city_falls_reason_C, text: "anche se [city_name] è caduta per mano degli invasori," }
  { key:PHRASE_eg_city_falls_no_reason_A, text: "la disgrazia si è abbattuta su [city_name]:" }
  { key:PHRASE_eg_city_falls_no_reason_B, text: "pare che i guai di [city_name] non abbiano mai fine, infatti" }
  { key:PHRASE_eg_city_falls_no_reason_C, text: "" }
  { key:PHRASE_foreign_city_conquered_title, text: "Città straniera conquistata" }
  { key:PHRASE_foreign_city_conquered_initial_announcement, text: "[greeting] [player_name], [reason_phrase] l'Egitto ha conquistato la famosa città di [city_name], espandendo ulteriormente la sua influenza!" }
  { key:PHRASE_foreign_city_conquered_reason_A, text: "perché la città straniera di [city_name] è stata conquistata dalle nostre truppe," }
  { key:PHRASE_foreign_city_conquered_reason_B, text: "la città straniera di [city_name] è stata conquistata dalle nostre truppe! Ora," }
  { key:PHRASE_foreign_city_conquered_reason_C, text: "anche se la città straniera di [city_name] è stata conquistata dalle nostre truppe," }
  { key:PHRASE_foreign_city_conquered_no_reason_A, text: "grazie alla potenza del nostro esercito," }
  { key:PHRASE_foreign_city_conquered_no_reason_B, text: "la forza del nostro regno continua a crescere. Ora" }
  { key:PHRASE_foreign_city_conquered_no_reason_C, text: "" }
  { key:PHRASE_route_opened_title, text: "Nuova via commerciale disponibile" }
  { key:PHRASE_route_opened_initial_announcement, text: "[greeting] [player_name], [reason_phrase] ora può essere aperta una nuova via commerciale per [city_name]." }
  { key:PHRASE_route_opened_reason_A, text: "perché una nuova via commerciale per [city_name] è ora disponibile," }
  { key:PHRASE_route_opened_reason_B, text: "una nuova via commerciale per [city_name] è ora disponibile, e" }
  { key:PHRASE_route_opened_reason_C, text: "anche se ora è possibile commerciare con [city_name]," }
  { key:PHRASE_route_opened_no_reason_A, text: "grazie alla nostra attività diplomatica," }
  { key:PHRASE_route_opened_no_reason_B, text: "c'è aria di cambiamento, infatti" }
  { key:PHRASE_route_opened_no_reason_C, text: "" }
  { key:PHRASE_route_closed_title, text: "Via commerciale interrotta" }
  { key:PHRASE_route_closed_initial_announcement, text: "[greeting] [player_name], [reason_phrase] la via commerciale per [city_name] è stata chiusa." }
  { key:PHRASE_route_closed_reason_A, text: "perché la via commerciale per [city_name] si è interrotta," }
  { key:PHRASE_route_closed_reason_B, text: "la via commerciale per [city_name] si è interrotta e, per di più," }
  { key:PHRASE_route_closed_reason_C, text: "anche se la via commerciale per [city_name] si è interrotta," }
  { key:PHRASE_route_closed_no_reason_A, text: "a causa dell'instabilità politica," }
  { key:PHRASE_route_closed_no_reason_B, text: "...si poteva prevedere. Pare" }
  { key:PHRASE_route_closed_no_reason_C, text: "" }
  { key:PHRASE_trade_city_siege_title, text: "Città commerciale sotto assedio" }
  { key:PHRASE_trade_city_siege_announcement, text: "[greeting] [player_name], [reason_phrase] un malaugurato assedio stringe [city_name] in una morsa." }
  { key:PHRASE_trade_city_siege_reason_A, text: "perché [city_name] è sotto assedio," }
  { key:PHRASE_trade_city_siege_reason_B, text: "[city_name] è sotto assedio, e" }
  { key:PHRASE_trade_city_siege_reason_C, text: "anche se [city_name] è sotto assedio," }
  { key:PHRASE_trade_city_siege_no_reason_A, text: "gli esploratori militari riportano terribili notizie. Pare" }
  { key:PHRASE_trade_city_siege_no_reason_B, text: "pare che i suoi guai non finiscano mai, infatti" }
  { key:PHRASE_trade_city_siege_no_reason_C, text: "" }
  { key:PHRASE_eg_city_saved_title, text: "Città egizia salvata" }
  { key:PHRASE_eg_city_saved_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [city_name] è stata salvata dai nostri nemici." }
  { key:PHRASE_eg_city_saved_reason_A, text: "perché [city_name] è stata salvata dai nostri nemici," }
  { key:PHRASE_eg_city_saved_reason_B, text: "[city_name] è stata salvata dai nostri nemici! Ora," }
  { key:PHRASE_eg_city_saved_reason_C, text: "anche se [city_name] è stata salvata dagli assalti degli invasori," }
  { key:PHRASE_eg_city_saved_no_reason_A, text: "grazie a un coraggioso intervento dell'esercito egizio," }
  { key:PHRASE_eg_city_saved_no_reason_B, text: "il vento di guerra soffia impetuoso, infatti ora" }
  { key:PHRASE_eg_city_saved_no_reason_C, text: "" }
  { key:PHRASE_battle_won_title, text: "Battaglia vittoriosa" }
  { key:PHRASE_battle_won_initial_announcement, text: "[greeting] [player_name], [reason_phrase] l'esercito egizio ha vinto!" }
  { key:PHRASE_battle_won_reason_A, text: "perché le nostre forze hanno trionfato nella lontana battaglia di [city_name]," }
  { key:PHRASE_battle_won_reason_B, text: "perché le nostre forze hanno trionfato nella lontana battaglia di [city_name]. Ora" }
  { key:PHRASE_battle_won_reason_C, text: "anche se le nostre forze hanno trionfato nella battaglia di [city_name]" }
  { key:PHRASE_battle_won_no_reason_A, text: "grazie al valore delle nostre truppe presso la lontana città di [city_name]," }
  { key:PHRASE_battle_won_no_reason_B, text: "le meraviglie non finiscono mai, infatti a [city_name]" }
  { key:PHRASE_battle_won_no_reason_C, text: "" }
  { key:PHRASE_battle_lost_title, text: "Esercito egizio sconfitto" }
  { key:PHRASE_battle_lost_initial_announcement, text: "[greeting] [player_name], [reason_phrase] l'esercito egizio è stato sconfitto a [city_name]." }
  { key:PHRASE_battle_lost_reason_A, text: "perché l'Egitto ha perso la battaglia a [city_name]," }
  { key:PHRASE_battle_lost_reason_B, text: "l'Egitto ha perso la battaglia di [city_name]. In più," }
  { key:PHRASE_battle_lost_reason_C, text: "anche se l'Egitto ha perso la battaglia di [city_name]," }
  { key:PHRASE_battle_lost_no_reason_A, text: "grande sfortuna ha colpito le nostre truppe, infatti" }
  { key:PHRASE_battle_lost_no_reason_B, text: "la guerra è davvero imprevedibile. Sfortunatamente" }
  { key:PHRASE_battle_lost_no_reason_C, text: "" }
  { key:PHRASE_acknowledgement_title, text: "Conferma di pace" }
  { key:PHRASE_acknowledgement_initial_announcement, text: "[greeting] [player_name], [reason_phrase] la tua città è salva... per ora." }
  { key:PHRASE_acknowledgement_reason_A, text: "perché hai vergognosamente ceduto alla minaccia," }
  { key:PHRASE_acknowledgement_reason_B, text: "hai vergognosamente ceduto alla minaccia," }
  { key:PHRASE_acknowledgement_reason_C, text: "anche se hai vergognosamente ceduto alla minaccia," }
  { key:PHRASE_acknowledgement_no_reason_A, text: "grazie a un cambiamento d'idea," }
  { key:PHRASE_acknowledgement_no_reason_B, text: "nulla è per certo, ma" }
  { key:PHRASE_acknowledgement_no_reason_C, text: "" }
  { key:PHRASE_pharaoh_attacks_you_title, text: "L'esercito del Faraone attacca" }
  { key:PHRASE_pharaoh_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone è in marcia e raggiungerà la tua città entro [time_until_attack] mesi." }
  { key:PHRASE_pharaoh_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone si sta avvicinando e arriverà nella tua città entro due anni." }
  { key:PHRASE_pharaoh_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone è pronto alla battaglia e raggiungerà la tua città entro un anno." }
  { key:PHRASE_pharaoh_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone è prossimo alla battaglia e raggiungerà la tua città entro sei mesi." }
  { key:PHRASE_pharaoh_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone scalpita e arriverà nella tua città entro un mese." }
  { key:PHRASE_pharaoh_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone è in città." }
  { key:PHRASE_pharaoh_attacks_you_reason_A, text: "perché la tua città è stata attaccata dall'esercito del Faraone," }
  { key:PHRASE_pharaoh_attacks_you_reason_B, text: "la tua città è stata attaccata dall'esercito del Faraone. In più" }
  { key:PHRASE_pharaoh_attacks_you_reason_C, text: "anche se la tua città è stata attaccata dall'esercito del Faraone," }
  { key:PHRASE_pharaoh_attacks_you_no_reason_A, text: "a volte il Faraone agisce secondo linee di pensiero imperscrutabili." }
  { key:PHRASE_pharaoh_attacks_you_no_reason_B, text: "il Faraone è imprevedibile. Ora," }
  { key:PHRASE_pharaoh_attacks_you_no_reason_C, text: "perché il tuo carisma è decaduto," }
  { key:PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text: "la tua reputazione nel regno è nulla. Forse, con qualche dono all'Egitto, le cose possono tornare come prima." }
  { key:PHRASE_eg_city_attacks_you_title, text: "L'esercito egizio attacca" }
  { key:PHRASE_eg_city_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] un esercito egizio si sta preparando all'attacco e raggiungerà la tua città entro [time_until_attack] mesi." }
  { key:PHRASE_eg_city_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] un esercito egizio è già in marcia e raggiungerà la tua città entro due anni." }
  { key:PHRASE_eg_city_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] entro un anno, la tua città subirà un massacro per mano di un esercito egizio." }
  { key:PHRASE_eg_city_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] un esercito egizio si sta avvicinando e raggiungerà la tua città entro sei mesi." }
  { key:PHRASE_eg_city_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] un esercito egizio si avvicina ai tuoi confini e sarà nella tua città entro un mese." }
  { key:PHRASE_eg_city_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [reason_phrase] l'esercito egizio è in città." }
  { key:PHRASE_eg_city_attacks_you_reason_A, text: "perché la tua città è stata attaccata dall'esercito egizio," }
  { key:PHRASE_eg_city_attacks_you_reason_B, text: "l'esercito egizio ha attaccato la tua città! In più," }
  { key:PHRASE_eg_city_attacks_you_reason_C, text: "anche se la tua città è stata attaccata dall'esercito egizio," }
  { key:PHRASE_eg_city_attacks_you_no_reason_A, text: "attento:" }
  { key:PHRASE_eg_city_attacks_you_no_reason_B, text: "la guerra incombe su di noi, infatti" }
  { key:PHRASE_eg_city_attacks_you_no_reason_C, text: "perché la tua reputazione nel regno è molto compromessa," }
  { key:PHRASE_eg_city_attacks_you_because_of_low_kingdom, text: "la tua reputazione nel regno è nulla. Forse con qualche dono all'Egitto le cose possono tornare come prima." }
  { key:PHRASE_foreign_army_attacks_you_title, text: "Invasione di un esercito straniero" }
  { key:PHRASE_foreign_army_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] si sta avvicinando e raggiungerà la tua città entro [time_until_attack] mesi." }
  { key:PHRASE_foreign_army_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] entro due anni [a_foreign_army] sarà alle tue porte." }
  { key:PHRASE_foreign_army_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] è pronto all'invasione e raggiungerà la tua città in un anno." }
  { key:PHRASE_foreign_army_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] raggiungerà la tua città entro sei mesi. Preparati allo scontro." }
  { key:PHRASE_foreign_army_attacks_you_1month_Warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] arriverà in città entro un mese, determinato alla conquista." }
  { key:PHRASE_foreign_army_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [a_foreign_army] ci sta attaccando e vuole distruggere la città." }
  { key:PHRASE_foreign_army_attacks_you_reason_A, text: "perché la tua città è stata attaccata da [a_foreign_army]," }
  { key:PHRASE_foreign_army_attacks_you_reason_B, text: "la tua città è stata attaccata da [a_foreign_army] e ora" }
  { key:PHRASE_foreign_army_attacks_you_reason_C, text: "anche se la tua città è stata attaccata da [a_foreign_army]," }
  { key:PHRASE_foreign_army_attacks_you_no_reason_A, text: "a causa delle loro mire espansionistiche," }
  { key:PHRASE_foreign_army_attacks_you_no_reason_B, text: "pare che i guai siano sempre in agguato, infatti" }
  { key:PHRASE_foreign_army_attacks_you_no_reason_C, text: "" }
  { key:PHRASE_rating_change_title_I, text: "La tua reputazione è cresciuta" }
  { key:PHRASE_rating_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] sei diventato più popolare e il tuo livello di reputazione nel regno è aumentato." }
  { key:PHRASE_rating_change_reason_I_A, text: "perché la tua reputazione nel regno è recentemente aumentata," }
  { key:PHRASE_rating_change_reason_I_B, text: "" }
  { key:PHRASE_rating_change_reason_I_C, text: "la tua reputazione è migliorata, ma" }
  { key:PHRASE_rating_change_no_reason_I_A, text: "perché il periodo è favorevole," }
  { key:PHRASE_rating_change_no_reason_I_B, text: "la tua reputazione nel regno è aumentata. Ora" }
  { key:PHRASE_rating_change_no_reason_I_C, text: "i sacrifici della tua città in combattimento sono molto apprezzati da tutti gli Egizi. Come risultato" }
  { key:PHRASE_rating_change_title_D, text: "La tua reputazione è diminuita" }
  { key:PHRASE_rating_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] gli Egizi non sono soddisfatti di te e il tuo livello di reputazione nel regno è diminuito." }
  { key:PHRASE_rating_change_reason_D_A, text: "perché il tuo livello di reputazione nel regno è diminuito," }
  { key:PHRASE_rating_change_reason_D_B, text: "la tua popolarità scema in tutto il regno e ora" }
  { key:PHRASE_rating_change_reason_D_C, text: "anche se la tua popolarità diminuisce in tutto il regno," }
  { key:PHRASE_rating_change_no_reason_D_A, text: "a causa dell'insoddisfazione nel regno," }
  { key:PHRASE_rating_change_no_reason_D_B, text: "questa è una cattiva notizia, infatti" }
  { key:PHRASE_rating_change_no_reason_D_C, text: "i tuoi connazionali non approvano i tuoi metodi violenti. Come risultato" }
  { key:PHRASE_price_change_title_I, text: "Aumento di prezzo" }
  { key:PHRASE_price_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] il prezzo di [item] è aumentato. L'importazione di tale merce è ora più costosa, ma puoi ottenere maggiori profitti con la sua esportazione." }
  { key:PHRASE_price_change_reason_I_A, text: "perché il prezzo di [item] è aumentato," }
  { key:PHRASE_price_change_reason_I_B, text: "il prezzo di [item] è aumentato, e in più" }
  { key:PHRASE_price_change_reason_I_C, text: "anche se i prezzi sono aumentati," }
  { key:PHRASE_price_change_no_reason_I_A, text: "a causa della riduzione di scorte in tutto il mondo," }
  { key:PHRASE_price_change_no_reason_I_B, text: "in quanto il mercato continua a cambiare" }
  { key:PHRASE_price_change_no_reason_I_C, text: "" }
  { key:PHRASE_price_change_title_D, text: "Diminuzione di prezzo" }
  { key:PHRASE_price_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] il prezzo di [item] è diminuito. Ciò ridurrà i profitti derivati dalla sua esportazione." }
  { key:PHRASE_price_change_reason_D_A, text: "perché il prezzo di [item] è diminuito," }
  { key:PHRASE_price_change_reason_D_B, text: "i prezzi sono crollati e, in più," }
  { key:PHRASE_price_change_reason_D_C, text: "anche se i prezzi sono crollati," }
  { key:PHRASE_price_change_no_reason_D_A, text: "a causa di una sovrabbondanza in tutto il regno," }
  { key:PHRASE_price_change_no_reason_D_B, text: "in quanto il mercato continua a cambiare" }
  { key:PHRASE_price_change_no_reason_D_C, text: "" }
  { key:PHRASE_demand_change_title_I, text: "Commercio in crescita" }
  { key:PHRASE_demand_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] [city_name] ha ora intenzione di incrementare il commercio di [item]." }
  { key:PHRASE_demand_change_reason_I_A, text: "perché [city_name] vuole commerciare ancora più [item]," }
  { key:PHRASE_demand_change_reason_I_B, text: "[city_name] ora desidera commerciare più [item]. Inoltre," }
  { key:PHRASE_demand_change_reason_I_C, text: "anche se [city_name] desidera commerciare più [item]," }
  { key:PHRASE_demand_change_no_reason_I_A, text: "perché [city_name] sta crescendo," }
  { key:PHRASE_demand_change_no_reason_I_B, text: "i tempi cambiano e" }
  { key:PHRASE_demand_change_no_reason_I_C, text: "" }
  { key:PHRASE_demand_change_title_D, text: "Commercio in diminuzione" }
  { key:PHRASE_demand_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] [city_name] ha deciso di ridurre il commercio di [item]." }
  { key:PHRASE_demand_change_reason_D_A, text: "perché [city_name] non commercia più [item] come prima," }
  { key:PHRASE_demand_change_reason_D_B, text: "[city_name] ha ridotto il suo livello di commercio" }
  { key:PHRASE_demand_change_reason_D_C, text: "anche se [city_name] ha ridotto il suo livello di commercio," }
  { key:PHRASE_demand_change_no_reason_D_A, text: "perché i cittadini di [city_name] intendono risparmiare," }
  { key:PHRASE_demand_change_no_reason_D_B, text: "i tempi cambiano e" }
  { key:PHRASE_demand_change_no_reason_D_C, text: "" }
  { key:PHRASE_earthquake_title, text: "Terremoto!" }
  { key:PHRASE_earthquake_initial_announcement, text: "[greeting] [player_name], [reason_phrase] la sabbia si agita sotto i tuoi piedi. La nostra terra non sarà più come prima. Fai ciò che puoi per riparare i danni inflitti alla tua città e alla tua gente dal terremoto." }
  { key:PHRASE_earthquake_reason_A, text: "a causa di un terribile terremoto," }
  { key:PHRASE_earthquake_reason_B, text: "oltre al terribile terremoto," }
  { key:PHRASE_earthquake_reason_C, text: "nonostante il terribile terremoto" }
  { key:PHRASE_earthquake_no_reason_A, text: "la città è spaventata perché" }
  { key:PHRASE_earthquake_no_reason_B, text: "la disgrazia ha colpito di nuovo la città, infatti" }
  { key:PHRASE_earthquake_no_reason_C, text: "" }
  { key:PHRASE_stormy_seas_title, text: "Tempeste" }
  { key:PHRASE_stormy_seas_initial_announcement, text: "[greeting] [player_name], [reason_phrase] i mari tempestosi minacciano di affondare le navi mercantili. Potrebbero trascorrere mesi prima che i venti si calmino e i mercanti solchino nuovamente le acque. Fino ad allora, non potremo commerciare via acqua." }
  { key:PHRASE_stormy_seas_reason_A, text: "a causa di tempeste improvvise," }
  { key:PHRASE_stormy_seas_reason_B, text: "anche se siamo stati danneggiati dalle recenti tempeste," }
  { key:PHRASE_stormy_seas_reason_C, text: "nonostante le terribili tempeste" }
  { key:PHRASE_stormy_seas_no_reason_A, text: "le tempeste infuriano e" }
  { key:PHRASE_stormy_seas_no_reason_B, text: "i nostri guai sono solo all'inizio, infatti" }
  { key:PHRASE_stormy_seas_no_reason_C, text: "" }
  { key:PHRASE_sandstorm_title, text: "Tempeste di sabbia" }
  { key:PHRASE_sandstorm_initial_announcement, text: "[greeting] [player_name], [reason_phrase] vortici di sabbia hanno oscurato le strade, facendole sparire nella polvere. I mercanti non vogliono rischiare di perdersi e non affrontano più i viaggi. Finché i venti non si calmeranno, nessun mercante vorrà guidare alcuna carovana." }
  { key:PHRASE_sandstorm_reason_A, text: "perché durante le tempeste di sabbia i mercanti non intendono rischiare un viaggio e il commercio via terra si è interrotto," }
  { key:PHRASE_sandstorm_reason_B, text: "le tempeste di sabbia hanno bloccato i mercanti lungo il loro cammino. Inoltre," }
  { key:PHRASE_sandstorm_reason_C, text: "nonostante le recenti tempeste di sabbia che hanno danneggiato il commercio," }
  { key:PHRASE_sandstorm_no_reason_A, text: "a causa dei forti venti," }
  { key:PHRASE_sandstorm_no_reason_B, text: "il deserto è un luogo pericoloso, infatti" }
  { key:PHRASE_sandstorm_no_reason_C, text: "" }
  { key:PHRASE_wage_change_title_I, text: "I lavoratori gioiscono per l'aumento" }
  { key:PHRASE_wage_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] i salari sono aumentati in tutto il regno. Se i tuoi lavoratori non verranno pagati come tutti gli altri, essi potrebbero cercare migliori opportunità altrove." }
  { key:PHRASE_wage_change_reason_I_A, text: "perché i salari sono aumentati in tutto il regno," }
  { key:PHRASE_wage_change_reason_I_B, text: "i salari sono aumentati in tutto il regno e" }
  { key:PHRASE_wage_change_reason_I_C, text: "anche se i salari sono aumentati in tutto il regno," }
  { key:PHRASE_wage_change_no_reason_I_A, text: "i tempi cambiano e ora" }
  { key:PHRASE_wage_change_no_reason_I_B, text: "alcuni gioiscono, altri piangono, infatti" }
  { key:PHRASE_wage_change_no_reason_I_C, text: "" }
  { key:PHRASE_wage_change_title_D, text: "I salari crollano" }
  { key:PHRASE_wage_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] i salari sono crollati in tutto il regno d'Egitto. Pare che ovunque tutti lavorino per meno." }
  { key:PHRASE_wage_change_reason_D_A, text: "perché i salari sono crollati," }
  { key:PHRASE_wage_change_reason_D_B, text: "i salari sono crollati e, in più," }
  { key:PHRASE_wage_change_reason_D_C, text: "anche se i salari sono crollati," }
  { key:PHRASE_wage_change_no_reason_D_A, text: "per ridurre i costi," }
  { key:PHRASE_wage_change_no_reason_D_B, text: "alcuni si infuriano, ma i nomarchi gioiscono, infatti" }
  { key:PHRASE_wage_change_no_reason_D_C, text: "" }
  { key:PHRASE_bad_water_title, text: "Acqua contaminata" }
  { key:PHRASE_bad_water_initial_announcement, text: "[greeting] [player_name], [reason_phrase] alcuni tuoi cittadini si sono ammalati a causa dell'acqua contaminata. Devi solo sperare che la malattia non si diffonda." }
  { key:PHRASE_bad_water_reason_A, text: "a causa di una recente contaminazione dell'acqua," }
  { key:PHRASE_bad_water_reason_B, text: "la recente contaminazione dell'acqua è stata una disgrazia. Ora," }
  { key:PHRASE_bad_water_reason_C, text: "anche se l'acqua è stata recentemente contaminata," }
  { key:PHRASE_bad_water_no_reason_A, text: "la sfortuna ha scelto la tua città e" }
  { key:PHRASE_bad_water_no_reason_B, text: ", ciò è davvero una sfortuna. Pare che" }
  { key:PHRASE_bad_water_no_reason_C, text: "" }
  { key:PHRASE_goldmine_cavein_title, text: "Miniera d'oro crollata" }
  { key:PHRASE_goldmine_cavein_initial_announcement, text: "[greeting] [player_name], [reason_phrase] una miniera d'oro è crollata. I nostri architetti non hanno potuto fare niente. Devi solo sperare che i minatori siano riusciti a uscire in tempo." }
  { key:PHRASE_goldmine_cavein_reason_A, text: "perché una miniera d'oro è crollata," }
  { key:PHRASE_goldmine_cavein_reason_B, text: "il recente crollo di una miniera d'oro è stata una vera disgrazia. Ora," }
  { key:PHRASE_goldmine_cavein_reason_C, text: "anche se recentemente è crollata una miniera d'oro," }
  { key:PHRASE_goldmine_cavein_no_reason_A, text: "a causa dell'instabilità della sabbia," }
  { key:PHRASE_goldmine_cavein_no_reason_B, text: "senza preavviso," }
  { key:PHRASE_goldmine_cavein_no_reason_C, text: "" }
  { key:PHRASE_landslide_title, text: "Frana" }
  { key:PHRASE_landslide_initial_announcement, text: "[greeting] [player_name], [reason_phrase] una terribile frana di pietre ha interrotto una via commerciale. Potrebbero passare dei mesi prima che la strada venga ripulita e i mercanti possano ricominciare a percorrerla." }
  { key:PHRASE_landslide_reason_A, text: "a causa di una recente frana di pietre," }
  { key:PHRASE_landslide_reason_B, text: "la recente frana è stata devastante. Ora," }
  { key:PHRASE_landslide_reason_C, text: "anche se ultimamente si sono verificate terribili frane," }
  { key:PHRASE_landslide_no_reason_A, text: "ci sono brutte notizie:" }
  { key:PHRASE_landslide_no_reason_B, text: "senza preavviso" }
  { key:PHRASE_landslide_no_reason_C, text: "" }
  { key:PHRASE_flood_fails_title, text: "Previsione straripamento: negativa" }
  { key:PHRASE_flood_fails_initial_announcement, text: "[greeting] [player_name], [reason_phrase] i sacerdoti ci portano brutte notizie... essi temono che il prossimo straripamento non porti alcun beneficio. Consulta periodicamente il Nilometro. Se la previsione non dovesse migliorare, la città potrebbe doversi preparare al peggio." }
  { key:PHRASE_flood_fails_reason_A, text: "perché si prevede che lo straripamento non ci sarà," }
  { key:PHRASE_flood_fails_reason_B, text: "si prevede che lo straripamento non ci sarà e" }
  { key:PHRASE_flood_fails_reason_C, text: "anche se si prevede che lo straripamento non ci sarà," }
  { key:PHRASE_flood_fails_no_reason_A, text: "a causa della siccità in Africa," }
  { key:PHRASE_flood_fails_no_reason_B, text: "i nostri guai sono solo all'inizio, infatti" }
  { key:PHRASE_flood_fails_no_reason_C, text: "" }
  { key:PHRASE_perfect_flood_title, text: "Previsione straripamento: ideale" }
  { key:PHRASE_perfect_flood_initial_announcement, text: "[greeting] [player_name], [reason_phrase] questa è davvero una benedizione, si prevede che il prossimo straripamento sarà molto fruttuoso. Consulta periodicamente il Nilometro. Se la previsione dovesse peggiorare, la città potrebbe trovarsi impreparata." }
  { key:PHRASE_perfect_flood_reason_A, text: "perché si prevede uno straripamento perfetto," }
  { key:PHRASE_perfect_flood_reason_B, text: "si prevede che lo straripamento sarà perfetto e" }
  { key:PHRASE_perfect_flood_reason_C, text: "anche se si prevede che lo straripamento sarà perfetto," }
  { key:PHRASE_perfect_flood_no_reason_A, text: "si prevede l'arrivo dei monsoni in Africa, quindi" }
  { key:PHRASE_perfect_flood_no_reason_B, text: "siamo davvero fortunati, infatti" }
  { key:PHRASE_perfect_flood_no_reason_C, text: "" }
  { key:PHRASE_bedouin_attacks_you_title, text: "L'esercito beduino attacca" }
  { key:PHRASE_bedouin_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] un esercito beduino si sta avvicinando alla città e attaccherà entro [time_until_attack] mesi." }
  { key:PHRASE_bedouin_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] un esercito beduino si avvicina e raggiungerà la città entro due anni." }
  { key:PHRASE_bedouin_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] un esercito beduino si avvicina velocemente e raggiungerà la città entro un anno." }
  { key:PHRASE_bedouin_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] un esercito beduino si sta preparando ad attaccare e raggiungerà la città entro sei mesi." }
  { key:PHRASE_bedouin_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] un esercito beduino è ormai prossimo alla città e attaccherà entro un mese." }
  { key:PHRASE_bedouin_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [reason_phrase] un esercito beduino sta per attaccarci!" }
  { key:PHRASE_bedouin_attacks_you_reason_A, text: "perché la tua città ha sconfitto l'esercito beduino," }
  { key:PHRASE_bedouin_attacks_you_reason_B, text: "la tua città ha sconfitto l'esercito beduino. Inoltre," }
  { key:PHRASE_bedouin_attacks_you_reason_C, text: "anche se la tua città ha sconfitto l'esercito beduino," }
  { key:PHRASE_bedouin_attacks_you_no_reason_A, text: "per soddisfare la sua sete di ricchezze," }
  { key:PHRASE_bedouin_attacks_you_no_reason_B, text: "i nostri guai sono immensi, infatti" }
  { key:PHRASE_bedouin_attacks_you_no_reason_C, text: "" }
  { key:PHRASE_gift_title_P, text: "Un dono del Faraone" }
  { key:PHRASE_gift_title_C, text: "Un dono da un tuo vicino" }
  { key:PHRASE_gift_granted_P, text: "[greeting] [player_name], [reason_phrase] il Faraone ti fa dono di [amount] [item] che provengono da [city_name]." }
  { key:PHRASE_gift_granted_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] desidera offrirti in dono [amount] [item]." }
  { key:PHRASE_gift_cash_granted_P, text: "[greeting] [player_name], [reason_phrase] il Faraone ti fa dono di [amount] deben provenienti dalla città di [city_name]." }
  { key:PHRASE_gift_cash_granted_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] desidera offrirti in dono [amount] deben." }
  { key:PHRASE_gift_partial_space_P, text: "[greeting] [player_name], [reason_phrase] il Faraone ha deciso di donarti [amount] [item] provenienti dalla città di [city_name]. Al momento non hai abbastanza spazio per stipare le merci nei tuoi depositi o granai, ma puoi accomodarne almeno la metà." }
  { key:PHRASE_gift_partial_space_C, text: "[greeting] [player_name], [reason_phrase] la città di [city_name] desidera farti dono di [amount] [item].  Al momento non hai spazio a sufficienza nei tuoi depositi e granai per incamerare questo dono, ma puoi accomodarne almeno la metà." }
  { key:PHRASE_gift_insufficient_space_P, text: "[greeting] [player_name], [reason_phrase] il Faraone ha deciso di donarti [amount] [item] provenienti dalla città di [city_name], ma nei tuoi granai e depositi non hai spazio sufficiente per accomodarlo. Se vuoi riceverlo devi liberare dello spazio e il prossimo mese ti sarà inviato di nuovo." }
  { key:PHRASE_gift_insufficient_space_C, text: "[greeting] [player_name], [reason_phrase], la città di [city_name] desidera donarti [amount] [item], ma nei tuoi granai e depositi non hai spazio sufficiente per accomodarlo. Libera dello spazio e il prossimo mese ti sarà inviato di nuovo." }
  { key:PHRASE_gift_last_chance_P, text: "[greeting] [player_name], per ordine del Faraone, la città di [city_name] ha cercato di farti pervenire in dono [amount] [item], ma ancora non hai spazio sufficiente nei granai o depositi per accomodarli. I suoi emissari si sono trattenuti fin troppo a lungo, e ora sono impazienti di andarsene. Per ora, accetta parte di questo dono, ma il resto dovrà tornare indietro." }
  { key:PHRASE_gift_last_chance_C, text: "[greeting] [player_name], la città di [city_name] ha cercato di farti pervenire in dono [amount] [item], ma ancora non hai spazio sufficiente nei granai o depositi per accomodarli. I suoi emissari si sono trattenuti fin troppo a lungo, e ora sono impazienti di andarsene. Per ora, accetta parte di questo dono, ma il resto dovrà tornare indietro." }
  { key:PHRASE_gift_forfeited_P, text: "[greeting] [player_name], non c'è ancora spazio sufficiente per ricevere il dono di [amount] [item] provenienti da [city_name], quindi la carovana tornerà indietro." }
  { key:PHRASE_gift_forfeited_C, text: "[greeting] [player_name], non c'è ancora spazio sufficiente per ricevere il dono di [amount] [item] provenienti da [city_name], quindi la carovana tornerà indietro." }
  { key:PHRASE_gift_accepted_P, text: "Per ordine del Faraone, i tuoi depositi e granai sono stati completamente riforniti di [item] della città di [city_name]." }
  { key:PHRASE_gift_accepted_C, text: "I tuoi depositi e granai sono stati completamente riforniti di [item] della città di [city_name]." }
  { key:PHRASE_gift_cash_accepted_P, text: "Per ordine del Faraone, [amount_granted] deben sono stati aggiunti al tuo tesoro." }
  { key:PHRASE_gift_cash_accepted_C, text: "Grazie a [city_name], [amount_granted] deben sono stati aggiunti al tuo tesoro." }
  { key:PHRASE_gift_postponed_P, text: "Gli emissari di [city_name] ritorneranno tra un mese con la consegna dei carri di [item]." }
  { key:PHRASE_gift_postponed_C, text: "Gli emissari di [city_name] ritorneranno tra un mese con la consegna dei carri di [item]." }
  { key:PHRASE_gift_refused_P, text: "Hai rifiutato il dono di [item] proveniente da [city_name], ma sono sicuro che ad altri farà piacere." }
  { key:PHRASE_gift_refused_C, text: "Hai rifiutato il dono di [item] proveniente da [city_name], ma sono sicuro che ad altri farà piacere." }
  { key:PHRASE_gift_accepted_reason_P_A, text: "perché hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_accepted_reason_P_B, text: "sull'onda del recente dono ricevuto da [city_name]," }
  { key:PHRASE_gift_accepted_reason_P_C, text: "anche se hai accettato il dono di [amount] [item] proveniente da [city_name]," }
  { key:PHRASE_gift_accepted_reason_C_A, text: "poiché hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_accepted_reason_C_B, text: "sull'onda del recente dono ricevuto da [city_name]," }
  { key:PHRASE_gift_accepted_reason_C_C, text: "anche se hai accettato il dono di [amount] [item] proveniente da [city_name]," }
  { key:PHRASE_gift_forfeited_reason_P_A, text: "poiché non hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_forfeited_reason_P_B, text: "non hai accettato il dono di [amount] [item] proveniente da [city_name]. Inoltre," }
  { key:PHRASE_gift_forfeited_reason_P_C, text: "anche se non hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_forfeited_reason_C_A, text: "poiché non hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_forfeited_reason_C_B, text: "non hai accettato il dono di [amount] [item] proveniente da [city_name]. Inoltre," }
  { key:PHRASE_gift_forfeited_reason_C_C, text: "anche se non hai accettato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_refused_reason_P_A, text: "poiché hai rifiutato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_refused_reason_P_B, text: "hai rifiutato il dono di [amount] [item] proveniente da [city_name]. Ora," }
  { key:PHRASE_gift_refused_reason_P_C, text: "anche se hai rifiutato il dono di [amount] [item] proveniente da [city_name]," }
  { key:PHRASE_gift_refused_reason_C_A, text: "poiché hai rifiutato il dono di [amount] [item] proveniente da [city_name]" }
  { key:PHRASE_gift_refused_reason_C_B, text: "hai rifiutato il dono di [amount] [item] proveniente da [city_name]. Ora," }
  { key:PHRASE_gift_refused_reason_C_C, text: "sebbene tu abbia rifiutato il dono di [amount] [item] proveniente da [city_name]," }
  { key:PHRASE_gift_no_reason_P_A, text: "poiché poteva farti comodo" }
  { key:PHRASE_gift_no_reason_P_B, text: "perché la generosità del Faraone non ha limite," }
  { key:PHRASE_gift_no_reason_P_C, text: "i sacrifici della tua città in combattimento sono molto apprezzati dal Faraone. Come risultato" }
  { key:PHRASE_gift_no_reason_C_A, text: "poiché poteva farti comodo" }
  { key:PHRASE_gift_no_reason_C_B, text: "perché gli Egizi aiutano sempre i loro connazionali," }
  { key:PHRASE_gift_no_reason_C_C, text: "i sacrifici della tua città in combattimento sono molto apprezzati dal popolo egizio. Come risultato" }
  { key:PHRASE_pharaoh_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] l'esercito del Faraone è arrivato per prendere la tua città con la forza." }
  { key:PHRASE_eg_city_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] un esercito egizio è approdato e sta invadendo la città proprio mentre stiamo parlando!" }
  { key:PHRASE_foreign_army_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] è approdato e sta attaccando la città! Che Seth ci aiuti." }
  { key:PHRASE_bedouin_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] una forza di invasione beduina è approdata sulle nostre spiagge!" }
  { key:PHRASE_pyramid_congratulations_title, text: "Piramide completata!" }
  { key:PHRASE_pyramid_congratulations, text: "[greeting] [player_name], questo è un successo spettacolare! Dopo interminabili mesi di lavoro, la piramide è finalmente completa!" }
  { key:PHRASE_stepped_pyramid_congratulations_title, text: "Piramide a gradoni terminata!" }
  { key:PHRASE_stepped_pyramid_congratulations, text: "[greeting] [player_name], finalmente la piramide a gradoni è terminata! Questo monumento ricorderà per sempre la tua grande abilità." }
  { key:PHRASE_bent_pyramid_congratulations_title, text: "Piramide sghemba terminata!" }
  { key:PHRASE_bent_pyramid_congratulations, text: "[greeting] [player_name], la costruzione della piramide sghemba è finalmente terminata! Questo è un grande risultato per la tua città." }
  { key:PHRASE_mudbrick_pyramid_congratulations_title, text: "Piramide di mattoni terminata!" }
  { key:PHRASE_mudbrick_pyramid_congratulations, text: "[greeting] [player_name], gli scalpellini hanno terminato le ultime rifiniture sulla lucida superficie di calcare e la piramide di mattoni è finalmente completa!" }
  { key:PHRASE_mastaba_congratulations_title, text: "Mastaba terminata!" }
  { key:PHRASE_mastaba_congratulations, text: "[greeting] [player_name], l'ultimo mattone è stato finalmente posto e il lavoro sulla Mastaba è ora terminato!" }
  { key:PHRASE_sphinx_congratulations_title, text: "Sfinge terminata!" }
  { key:PHRASE_sphinx_congratulations, text: "[greeting] [player_name], finalmente gli scalpellini hanno finito di scolpire la possente sfinge. Questo monumento sorveglierà l'Egitto per i secoli a venire." }
  { key:PHRASE_obelisk_congratulations_title, text: "Obelisco terminato!" }
  { key:PHRASE_obelisk_congratulations, text: "[greeting] [player_name], gli scalpellini hanno appena dato il tocco finale all'obelisco e finalmente è completo." }
  { key:PHRASE_sun_temple_congratulations_title, text: "Tempio del Sole terminato!" }
  { key:PHRASE_sun_temple_congratulations, text: "[greeting] [player_name], dopo molti mesi di fatica, il lavoro al Tempio del Sole è giunto al termine. Questo è un grande risultato per la tua città!" }
  { key:PHRASE_alex_library_congratulations_title, text: "Biblioteca di Alessandria finita!" }
  { key:PHRASE_alex_library_congratulations, text: "[greeting] [player_name], dopo molto lavoro, finalmente le splendide porte della grande biblioteca di Alessandria possono essere aperte a tutti gli studiosi del mondo." }
  { key:PHRASE_abu_simbel_congratulations_title, text: "Abu Simbel completato!" }
  { key:PHRASE_abu_simbel_congratulations, text: "[greeting] [player_name], questo è davvero un grande trionfo! I tuoi capaci artigiani hanno creato un monumento eterno, che testimonia la gloria del nostro Faraone e la potenza d'Egitto." }
  { key:PHRASE_caesareum_congratulations_title, text: "Caesareum completato!" }
  { key:PHRASE_caesareum_congratulations, text: "[greeting] [player_name], il sacro tempio e i lussureggianti giardini del Caesareum sono finalmente completi! In tutta la regione non si parla d'altro che della sua bellezza." }
  { key:PHRASE_lighthouse_congratulations_title, text: "Faro di Pharos completato!" }
  { key:PHRASE_lighthouse_congratulations, text: "[greeting] [player_name], dopo molta fatica e sangue versato, i lavoratori hanno finalmente posto l'ultimo blocco di marmo dello splendido faro di Pharos! Il suo potente raggio di luce attira già i commercianti da tutto il mondo." }
  { key:PHRASE_mausoleum_congratulations_title, text: "Mausoleo terminato!" }
  { key:PHRASE_mausoleum_congratulations, text: "[greeting] [player_name], il sacro mausoleo è finalmente terminato! Questo è un ottimo risultato per la tua città." }
  { key:PHRASE_smalltomb_congratulations_title, text: "Tomba reale piccola completata!" }
  { key:PHRASE_smalltomb_congratulations, text: "[greeting] [player_name], la costruzione della piccola tomba reale è completata. Noi tutti speriamo che i lavoratori debbano attendere ancora molti anni prima di costruirne un'altra." }
  { key:PHRASE_medtomb_congratulations_title, text: "Tomba reale media completata!" }
  { key:PHRASE_medtomb_congratulations, text: "[greeting] [player_name], finalmente la tomba reale media è finita e approviggionata. Sarà un ottimo punto di partenza per il viaggio nell'aldilà del nostro Faraone recentemente scomparso." }
  { key:PHRASE_largetomb_congratulations_title, text: "Tomba reale grande terminata!" }
  { key:PHRASE_largetomb_congratulations, text: "[greeting] [player_name], dopo molti anni di duro lavoro sotto terra, i tuoi lavoratori hanno completato la tomba reale più bella che sia mai stata costruita! È davvero uno splendido risultato." }
  { key:PHRASE_grandtomb_congratulations_title, text: "Tomba reale enorme terminata!" }
  { key:PHRASE_grandtomb_congratulations, text: "[greeting] [player_name], dopo molto e duro lavoro, la gigantesca tomba reale è finalmente completa - appena in tempo, in quanto il nostro nobile faraone è in fin di vita. Questa splendida tomba è il luogo ideale per affrontare il viaggio nell'aldilà." }
  { key:PHRASE_troopcarryover_title, text: "Soldati fedeli si uniscono a te." }
  { key:PHRASE_troopcarryover_initial_announcement, text: "I tuoi migliori soldati della precedente missione desiderano unirsi a te. Costruisci [reason_phrase] per questi guerrieri ed essi ritorneranno." }
  { key:PHRASE_troopcarryover_inf_only, text: "un forte di fanteria" }
  { key:PHRASE_troopcarryover_arch_only, text: "un forte di arcieri" }
  { key:PHRASE_troopcarryover_char_only, text: "un forte di carri da guerra" }
  { key:PHRASE_troopcarryover_inf_arch, text: "forti di fanteria e arcieri" }
  { key:PHRASE_troopcarryover_inf_char, text: "forti di fanteria e carri da guerra" }
  { key:PHRASE_troopcarryover_arch_char, text: "forti di arcieri e carri da guerra" }
  { key:PHRASE_troopcarryover_all_three, text: "forti di fanteria, arcieri e carri da guerra" }
  { key:PHRASE_pyramid_speedup_title, text: "Benedizione sulla costruzione" }
  { key:PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] si compiace della tua devozione e desidera aiutarti nel tuo progetto di costruzione. Ora i tuoi lavoratori possono temporaneamente farsi da parte mentre [reason_phrase] impone la sua grazia su di te." }
  { key:PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] accetta la tua devozione aiutandoti nella costruzione del monumento. Ora i tuoi lavoratori possono temporaneamente farsi da parte mentre giunge il benevolo dono di [reason_phrase]." }
  { key:PHRASE_pyramid_speedup_Osiris, text: "Osiride" }
  { key:PHRASE_pyramid_speedup_Ra, text: "Ra" }
  { key:PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
  { key:PHRASE_pyramid_speedup_Seth, text: "Seth" }
  { key:PHRASE_pyramid_speedup_Bast, text: "Bast" }
]
