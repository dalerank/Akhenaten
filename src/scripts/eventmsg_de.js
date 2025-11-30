log_info("akhenaten: eventmsg german started")

eventmsg_de = [
  { key:PHRASE_egyptian_city_attacked_title_P, text: "Ägyptische Stadt wird angegriffen" }
  { key:PHRASE_egyptian_city_attacked_title_C, text: "Ägyptische Stadt wird angegriffen" }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] Ungläubige greifen an. Der allmächtige Pharao befiehlt Euch, Truppen zur ägyptischen Stadt [city_name] zu entsenden, um den Feind zu bekämpfen. Ihr solltet Truppen innerhalb von [travel_time] Monaten entsenden." }
  { key:PHRASE_egyptian_city_attacked_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] [city_name], eine ägyptische Stadt, wird angegriffen und braucht Eure Hilfe. Ihr solltet Truppen innerhalb von [travel_time] Monaten entsenden." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_P, text: "[greeting] [player_name], die Armeen des göttlichen Pharaos kämpfen noch immer gegen Angreifer bei [city_name]. Entsendet Verstärkung innerhalb der nächsten sechs Monate, oder riskiert, Pharaos Zorn zu erregen." }
  { key:PHRASE_egyptian_city_attacked_first_reminder_C, text: "[greeting] [player_name], habt Ihr [city_name] vergessen? Entsendet Truppen innerhalb der nächsten sechs Monate, oder die Konsequenzen könnten verheerend sein." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_P, text: "[greeting] [player_name], Pharao wird ungeduldig beim Warten auf Eure Truppen. Entsendet bald Truppen nach [city_name], oder es wird zu spät sein." }
  { key:PHRASE_egyptian_city_attacked_last_reminder_C, text: "[greeting] [player_name], [city_name] könnte bald gegen seine Feinde verlieren. Entsendet schnell Truppen, wenn Ihr [city_name] in seiner Stunde der Not helfen wollt." }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_A, text: "weil Eure Truppen Pharaos Feinde bei [city_name] besiegten," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_B, text: "Eure Truppen besiegten Pharaos Feinde bei [city_name]. Übrigens," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_P_C, text: "obwohl Eure Truppen Pharaos Feinde bei [city_name] besiegten," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_A, text: "weil Eure Truppen den Feind bei [city_name] fähig besiegten," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_B, text: "Eure Truppen besiegten den Feind bei [city_name] fähig. Zusätzlich," }
  { key:PHRASE_egyptian_city_attacked_comply_reason_C_C, text: "obwohl Eure Truppen den Feind bei [city_name] fähig besiegten," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_A, text: "weil Ihr gezögert habt, Eure Truppen zu entsenden, um Pharaos Armee im Kampf gegen den Feind bei [city_name] zu helfen," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_B, text: "Pharaos Armee verlor die Schlacht bei [city_name], weil Eure Truppen zu spät ankamen. Außerdem," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_P_C, text: "Eure Truppen kamen zu spät, um Pharaos Armee im Kampf gegen den Feind bei [city_name] zu helfen, aber Eure Bemühung wurde nicht ungewürdigt gelassen. Infolgedessen" }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_A, text: "weil Ihr zu lange gewartet habt, um Eure Truppen zur Verteidigung von [city_name] zu entsenden," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_B, text: "Eure Truppen kamen nicht rechtzeitig an, um [city_name] zu verteidigen. Außerdem," }
  { key:PHRASE_egyptian_city_attacked_too_late_reason_C_C, text: "Eure Truppen kamen zu spät, um [city_name] zu helfen, aber da Ihr Euch bemüht und bereit wart, Eure eigenen Soldaten zu opfern," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_A, text: "weil Ihr Pharao die Truppen verweigert habt, die er brauchte, um den Feind bei [city_name] zu bekämpfen," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_B, text: "Pharao hat erfahren, dass Ihr Euch geweigert habt, die Truppen zu entsenden, die er brauchte, um den Feind bei [city_name] zu bekämpfen. Zusätzlich," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_P_C, text: "obwohl Ihr Pharao die Truppen verweigert habt, die er brauchte, um den Feind bei [city_name] zu bekämpfen," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_A, text: "weil Ihr Euch geweigert habt, die angeforderten Truppen zu entsenden, um die Plünderer bei [city_name] zu besiegen," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_B, text: "[city_name] verzweifelt daran, dass Ihr Euch geweigert habt, die angeforderten Truppen zu entsenden, um ihre Feinde zu besiegen. Außerdem," }
  { key:PHRASE_egyptian_city_attacked_refuse_reason_C_C, text: "obwohl Ihr Euch geweigert habt, die angeforderten Truppen zu entsenden, um die Plünderer bei [city_name] zu besiegen," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_A, text: "weil die Truppen, die Ihr Pharao bei [city_name] entsandt habt, zu schwach waren, um den Feind niederzuschlagen," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_B, text: "die schwachen Truppen, die Ihr entsandt habt, um Pharao zu helfen, wurden bei [city_name] besiegt. Außerdem," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_P_C, text: "trotz der Tatsache, dass Eure Truppen zu schwach waren, um Pharao bei [city_name] zu helfen," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_A, text: "weil die Truppen, die Ihr nach [city_name] entsandt habt, nicht mächtig genug waren, um die Angreifer zu besiegen," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_B, text: "Eure schwachen Streitkräfte wurden bei [city_name] besiegt. Zusätzlich," }
  { key:PHRASE_egyptian_city_attacked_lost_battle_reason_C_C, text: "obwohl Eure Truppen bei [city_name] nicht siegreich waren," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_A, text: "um ihren Drang nach mehr Land zu befriedigen," }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_B, text: "Eure Probleme sind noch nicht vorbei, denn" }
  { key:PHRASE_egyptian_city_attacked_no_reason_P_C, text: "" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_A, text: "in Verfolgung einer lang anhaltenden Fehde," }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_B, text: "Eure Probleme sind noch nicht vorbei, denn" }
  { key:PHRASE_egyptian_city_attacked_no_reason_C_C, text: "" }
  
  { key: PHRASE_distant_battle_title_P, text: "Ferne Schlacht" }
  { key: PHRASE_distant_battle_title_C, text: "Ferne Schlacht" }
  { key: PHRASE_distant_battle_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] die ägyptische Armee ist in eine heftige Schlacht verwickelt. Der gebieterische Pharao verlangt, dass Ihr Truppen zur fernen Stadt [city_name] entsendet, um ins Gefecht einzutreten. Entsendet Truppen innerhalb von [travel_time] Monaten." }
  { key: PHRASE_distant_battle_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] die ägyptische Armee ist in Kampfhandlungen bei der fernen Stadt [city_name] verwickelt und verlangt, dass Ihr dorthin Verstärkung entsendet. Entsendet Truppen zu ihrer Hilfe innerhalb von [travel_time] Monaten." }
  { key: PHRASE_distant_battle_first_reminder_P, text: "[greeting] [player_name], die blutige Schlacht dauert bei [city_name] an, und Pharao braucht noch immer Eure Truppen. Entsendet sie innerhalb der nächsten sechs Monate, wenn sie rechtzeitig ankommen sollen. Dies nicht zu tun könnte kostspielig sein. " }
  { key: PHRASE_distant_battle_first_reminder_C, text: "[greeting] [player_name], die Schlacht um [city_name] tobt weiter. Entsendet Truppen innerhalb der nächsten sechs Monate, wenn sie rechtzeitig ankommen sollen. Dies könnte Eure Chance sein, an einem ruhmreichen Sieg teilzuhaben." }
  { key: PHRASE_distant_battle_last_reminder_P, text: "[greeting] [player_name], die ägyptische Armee führt noch immer Krieg bei [city_name], und der edle Pharao verlangt, dass Ihr sehr bald Verstärkung entsendet. Erzürnt Pharao nicht, während er in Kampfstimmung ist." }
  { key: PHRASE_distant_battle_last_reminder_C, text: "[greeting] [player_name], die Schlacht um [city_name] dauert an. Wenn Ihr sehr bald Truppen zu ihrer Hilfe entsendet, könnte Ägypten noch einen ruhmreichen Sieg erringen." }
  { key: PHRASE_distant_battle_comply_reason_P_A, text: "weil Pharaos Sieg bei [city_name] von Euren Truppen abhing," }
  { key: PHRASE_distant_battle_comply_reason_P_B, text: "Eure Truppen halfen Pharao, den Sieg bei [city_name] zu erringen. Oh, und noch etwas," }
  { key: PHRASE_distant_battle_comply_reason_P_C, text: "obwohl Eure Truppen Pharao halfen, den Sieg bei [city_name] zu erringen," }
  { key: PHRASE_distant_battle_comply_reason_C_A, text: "weil Eure Truppen halfen, den Tag bei [city_name] zu gewinnen," }
  { key: PHRASE_distant_battle_comply_reason_C_B, text: "Eure Truppen erwiesen sich als entscheidend, um den Tag bei [city_name] zu gewinnen. Außerdem," }
  { key: PHRASE_distant_battle_comply_reason_C_C, text: "obwohl Eure Truppen sich als entscheidend erwiesen, um den Tag bei [city_name] zu gewinnen," }
  { key: PHRASE_distant_battle_too_late_reason_P_A, text: "weil Eure Truppen nicht rechtzeitig waren, um Pharao bei [city_name] zu helfen," }
  { key: PHRASE_distant_battle_too_late_reason_P_B, text: "Eure Truppen waren nicht rechtzeitig, um Pharao bei [city_name] zu helfen. Zusätzlich," }
  { key: PHRASE_distant_battle_too_late_reason_P_C, text: "obwohl Eure Truppen zu spät waren, um Pharao bei [city_name] zu helfen, wird Eure Bereitschaft, Opfer für das Königreich zu bringen, sehr geschätzt. Infolgedessen," }
  { key: PHRASE_distant_battle_too_late_reason_C_A, text: "weil Eure Truppen zu spät waren, um bei der Schlacht um [city_name] zu helfen," }
  { key: PHRASE_distant_battle_too_late_reason_C_B, text: "Eure Truppen waren zu spät, um bei der Schlacht um [city_name] zu helfen. Außerdem," }
  { key: PHRASE_distant_battle_too_late_reason_C_C, text: "obwohl Eure Truppen zu spät waren, um bei der Schlacht um [city_name] zu helfen, wird Eure Bereitschaft, Opfer für das Königreich zu bringen, sehr geschätzt. Infolgedessen," }
  { key: PHRASE_distant_battle_refuse_reason_P_A, text: "weil Ihr Pharaos Forderung, Truppen zu entsenden, um seiner Armee bei [city_name] zu helfen, unverblümt verweigert habt," }
  { key: PHRASE_distant_battle_refuse_reason_P_B, text: "Ihr habt Pharaos Forderung, Truppen zu entsenden, um seiner Armee bei [city_name] zu helfen, unverblümt verweigert. Das war unklug, aber auf jeden Fall," }
  { key: PHRASE_distant_battle_refuse_reason_P_C, text: "obwohl Ihr Pharaos Forderung nach Truppen, um seiner Armee bei [city_name] zu helfen, verweigert habt," }
  { key: PHRASE_distant_battle_refuse_reason_C_A, text: "weil Ihr Euch geweigert habt, die benötigten Truppen zur Schlacht bei [city_name] zu entsenden," }
  { key: PHRASE_distant_battle_refuse_reason_C_B, text: "Ihr habt Euch geweigert, die benötigten Truppen zur Schlacht bei [city_name] zu entsenden, was für sie unglücklich war. Nebenbei," }
  { key: PHRASE_distant_battle_refuse_reason_C_C, text: "obwohl Ihr Euch geweigert habt, die benötigten Truppen zur Schlacht bei [city_name] zu entsenden," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_A, text: "weil die Truppen, die Ihr nach [city_name] entsandt habt, zu schwach waren, um Pharaos Widersacher zu bekämpfen," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_B, text: "die Truppen, die Ihr nach [city_name] entsandt habt, wurden von Pharaos Feind besiegt. Zusätzlich," }
  { key: PHRASE_distant_battle_lost_battle_reason_P_C, text: "obwohl die Truppen, die Ihr nach [city_name] entsandt habt, von Pharaos Feind besiegt wurden," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_A, text: "weil die Truppen, die Ihr nach [city_name] entsandt habt, Stärke und Kraft fehlten, um den Feind zu besiegen," }
  { key: PHRASE_distant_battle_lost_battle_reason_C_B, text: "den Truppen, die Ihr nach [city_name] entsandt habt, fehlten Stärke und Kraft, um unseren Erzfeind zu besiegen. Seid auch darüber informiert, dass" }
  { key: PHRASE_distant_battle_lost_battle_reason_C_C, text: "obwohl die Truppen, die Ihr nach [city_name] entsandt habt, nicht in der Lage waren, den Feind zu besiegen," }
  { key: PHRASE_distant_battle_no_reason_P_A, text: "hört den Schlachtruf, denn" }
  { key: PHRASE_distant_battle_no_reason_P_B, text: "unsere Probleme dauern an" }
  { key: PHRASE_distant_battle_no_reason_P_C, text: "" }
  { key: PHRASE_distant_battle_no_reason_C_A, text: "alarmiert Eure Soldaten, denn" }
  { key: PHRASE_distant_battle_no_reason_C_B, text: "die Schwierigkeiten sind nicht vorbei, denn" }
  { key: PHRASE_distant_battle_no_reason_C_C, text: "" }
  
  { key:PHRASE_general_request_title_P, text:"Pharao fordert Waren" }
  { key:PHRASE_general_request_title_C, text:"Eine Stadt fordert Waren" }
  { key:PHRASE_general_request_initial_announcement_P,text: "[greeting] [player_name], [reason_phrase] der unvergleichliche Pharao möchte, dass Ihr [amount] [item] nach [city_name] innerhalb von [time_allotted] Monaten entsendet. Die Erfüllung der Forderung könnte Pharaos Wertschätzung einbringen." }
  { key:PHRASE_general_request_initial_announcement_C,text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] fordert, dass Ihr [amount] [item] in [time_allotted] Monaten entsendet. [city_name] zu helfen könnte uns später Vorteile bringen." }
  { key:PHRASE_general_request_reminder_P, text: "[greeting] [player_name], Pharao fragt sich, warum [city_name] noch nicht [amount] [item] erhalten hat. Ihr habt noch 6 Monate Zeit, um Pharaos Forderung zu erfüllen." }
  { key:PHRASE_general_request_reminder_C, text: "[greeting] [player_name], [city_name] wartet ängstlich auf die Ankunft von [amount] [item]. Ihr habt noch 6 Monate Zeit zur Erfüllung." }
  { key:PHRASE_general_request_overdue_P, text: "[greeting] [player_name], wollt Ihr Pharao provozieren? Ihr habt nicht rechtzeitig [amount] [item] nach [city_name] gesendet. Selbst ein verspäteter Versuch, diese Forderung zu erfüllen, könnte Pharao etwas besänftigen." }
  { key:PHRASE_general_request_overdue_C, text: "[greeting] [player_name], Eure Zeit ist abgelaufen, und Ihr habt noch immer nicht die [amount] [item] nach [city_name] gesendet, wie sie es forderten. Selbst ein verspäteter Versuch, diese Forderung zu erfüllen, könnte [city_name] etwas zufriedenstellen." }
  { key:PHRASE_general_request_warning_P, text: "[greeting] [player_name], Ihr habt nur noch sechs Monate Zeit, um Pharaos Forderung zu erfüllen, dass Ihr [amount] [item] nach [city_name] entsendet. Verweigert es ihm auf Eure Gefahr." }
  { key:PHRASE_general_request_warning_C, text: "[greeting] [player_name], entsendet [amount] [item] nach [city_name] innerhalb von sechs Monaten, oder riskiert, aus Nachbarn Feinde zu machen." }
  { key:PHRASE_general_request_comply_reason_P_A, text:"weil Ihr Pharaos Forderung erfüllt habt, dass [amount] [item] nach [city_name] gesendet werden," }
  { key:PHRASE_general_request_comply_reason_P_B, text:"Ihr habt Pharaos Forderung erfüllt, dass [amount] [item] nach [city_name] gesendet werden. Übrigens," }
  { key:PHRASE_general_request_comply_reason_P_C, text:"Ihr habt Pharaos Forderung erfüllt, dass [amount] [item] nach [city_name] gesendet werden, jedoch," }
  { key:PHRASE_general_request_comply_reason_C_A, text:"weil Ihr [amount] [item] nach [city_name] gesendet habt, wie sie es forderten," }
  { key:PHRASE_general_request_comply_reason_C_B, text:"[city_name] erhielt die [amount] [item], wie sie es forderten. Ihr solltet auch wissen, dass" }
  { key:PHRASE_general_request_comply_reason_C_C, text:"obwohl Ihr [amount] [item] nach [city_name] gesendet habt, wie sie es forderten," }
  { key:PHRASE_general_request_too_late_reason_P_A, text:"weil Ihr die Erfüllung von Pharaos Forderung nach [amount] [item] verzögert habt," }
  { key:PHRASE_general_request_too_late_reason_P_B, text:"Pharaos Forderung nach [amount] [item] blieb unerfüllt, weil Ihr zu spät wart. Zusätzlich," }
  { key:PHRASE_general_request_too_late_reason_P_C, text:"Ihr habt die Erfüllung von Pharaos Forderung nach [amount] [item] verzögert, aber dennoch wurde Eure Bemühung geschätzt. Infolgedessen," }
  { key:PHRASE_general_request_too_late_reason_C_A, text:"weil Ihr mit der Erfüllung der Forderung von [city_name] nach [amount] [item] säumig wart," }
  { key:PHRASE_general_request_too_late_reason_C_B, text:"Ihr wart säumig bei der Lieferung von [amount] [item] nach [city_name]. Ihr solltet auch wissen, dass" }
  { key:PHRASE_general_request_too_late_reason_C_C, text:"trotz der Tatsache, dass Ihr bei der Lieferung von [amount] [item] nach [city_name] säumig wart, wurde Eure Bemühung geschätzt. Infolgedessen," }
  { key:PHRASE_general_request_refuse_reason_P_A, text:"weil Ihr Pharaos Forderung nach [amount] [item] ignoriert habt," }
  { key:PHRASE_general_request_refuse_reason_P_B, text:"Ihr habt Pharaos Forderung nach [amount] [item] ignoriert, und er wird nicht erfreut sein. Zusätzlich," }
  { key:PHRASE_general_request_refuse_reason_P_C, text:"obwohl Ihr Pharaos Forderung nach [amount] [item] ignoriert habt," }
  { key:PHRASE_general_request_refuse_reason_C_A, text:"weil Ihr [amount] [item] nicht nach [city_name] gesendet habt," }
  { key:PHRASE_general_request_refuse_reason_C_B, text:"Ihr habt es versäumt, [amount] [item] nach [city_name] zu senden, und sie schätzen dies nicht. In der Zwischenzeit," }
  { key:PHRASE_general_request_refuse_reason_C_C, text:"trotz der Tatsache, dass Ihr es versäumt habt, [amount] [item] nach [city_name] zu senden," }
  { key:PHRASE_general_request_no_reason_P_A, text:"um die Bestände seines Anwesens aufzufüllen," }
  { key:PHRASE_general_request_no_reason_P_B, text:"Pharaos Gier scheint kein Ende zu nehmen, denn" }
  { key:PHRASE_general_request_no_reason_P_C, text: "" }
  { key:PHRASE_general_request_no_reason_C_A, text:"um die Bedürfnisse der Bürger zu befriedigen," }
  { key:PHRASE_general_request_no_reason_C_B, text:"dies scheint kein Ende zu nehmen, denn" }
  { key:PHRASE_general_request_no_reason_C_C, text: "" }
  
  
    { key: PHRASE_great_festival_title_P, text: "Fest zu [god]" }
  { key: PHRASE_great_festival_title_C, text: "Großes Fest zu [god]" }
  { key: PHRASE_great_festival_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] Pharao plant ein Großes Fest zu [god] in [city_name] und benötigt Waren aus Eurer Stadt. Ihr habt [time_allotted] Monate Zeit, um [amount] [item] zu senden." }
  { key: PHRASE_great_festival_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] fordert, dass Ihr [amount] [item] für ein Großes Fest zu [god] entsendet. Die Stadt benötigt diese Waren innerhalb von [time_allotted] Monaten." }
  { key: PHRASE_great_festival_reminder_P, text: "[greeting] [player_name], Ihr habt noch sechs Monate Zeit, um [amount] [item] nach [city_name] für das Große Fest zu [god] zu senden. Pharao wird unzufrieden sein, wenn Ihr seiner Forderung nicht nachkommt." }
  { key: PHRASE_great_festival_reminder_C, text: "[greeting] [player_name], das Große Fest zu [god] in [city_name] rückt schnell näher, und Ihr habt die [amount] [item] nicht gesendet. Ihr habt noch 6 Monate Zeit, um die Waren zu senden." }
  { key: PHRASE_great_festival_overdue_P, text: "[greeting] [player_name], Ihr habt Eure Frist verpasst, und Pharao musste das Große Fest zu [god] ohne Eure Lieferungen abhalten. Sendet trotzdem [amount] [item] nach [city_name], und der erzürnte Pharao mag noch ein Maß an Vergebung finden." }
  { key: PHRASE_great_festival_overdue_C, text: "[greeting] [player_name], [city_name] ist unzufrieden, dass sie Waren anderswo beschaffen mussten für ihr Großes Fest zu [god]. Ihr könntet ein gewisses Maß an Akzeptanz gewinnen, wenn Ihr noch versucht, die [amount] [item] zu senden." }
  { key: PHRASE_great_festival_warning_P, text: "[greeting] [player_name], Ihr habt nur noch 6 Monate Zeit, um Pharao [amount] [item] nach [city_name] zu senden, die er für das Große Fest zu [god] benötigte. Wehe dem, der die Hitze von Pharaos feurigem Zorn spürt!" }
  { key: PHRASE_great_festival_warning_C, text: "[greeting] [player_name], [city_name] ist frustriert über Euch. Sendet [amount] [item] in den nächsten 6 Monaten, wenn Ihr Hoffnung haben wollt, gute Beziehungen aufrechtzuerhalten." }
  { key: PHRASE_great_festival_comply_reason_P_A, text: "weil Ihr Pharao und [god] geehrt habt, indem Ihr rechtzeitig [amount] [item] nach [city_name] für das Große Fest gesendet habt," }
  { key: PHRASE_great_festival_comply_reason_P_B, text: "Ihr habt gnädigerweise Pharao und [god] geehrt, indem Ihr rechtzeitig [amount] [item] nach [city_name] für das Große Fest gesendet habt. Außerdem," }
  { key: PHRASE_great_festival_comply_reason_P_C, text: "obwohl Ihr gnädigerweise Pharao und [god] geehrt habt, indem Ihr rechtzeitig [amount] [item] nach [city_name] für das Große Fest gesendet habt," }
  { key: PHRASE_great_festival_comply_reason_C_A, text: "weil Ihr [city_name] geholfen habt, sein Großes Fest zu [god] zu feiern, indem Ihr [amount] [item] gesendet habt," }
  { key: PHRASE_great_festival_comply_reason_C_B, text: "Ihr habt [city_name] geholfen, sein Großes Fest zu [god] zu feiern, indem Ihr [amount] [item] gesendet habt, was sehr geschätzt wurde. Zusätzlich," }
  { key: PHRASE_great_festival_comply_reason_C_C, text: "obwohl Ihr [city_name] geholfen habt, sein Großes Fest zu [god] zu feiern, indem Ihr [amount] [item] gesendet habt," }
  { key: PHRASE_great_festival_too_late_reason_P_A, text: "weil Ihr [amount] [item] zu spät für Pharaos Großes Fest zu [god] bei [city_name] gesendet habt," }
  { key: PHRASE_great_festival_too_late_reason_P_B, text: "Ihr habt [amount] [item] zu spät für Pharaos Großes Fest zu [god] bei [city_name] gesendet. Zusätzlich," }
  { key: PHRASE_great_festival_too_late_reason_P_C, text: "obwohl die [amount] [item] zu spät für Pharaos Großes Fest zu [god] bei [city_name] ankamen, da Ihr Euch bemüht habt," }
  { key: PHRASE_great_festival_too_late_reason_C_A, text: "weil die von [city_name] für das Große Fest zu [god] benötigten [amount] [item] nicht rechtzeitig ankamen," }
  { key: PHRASE_great_festival_too_late_reason_C_B, text: "die von [city_name] für das Große Fest zu [god] benötigten [amount] [item] kamen nicht rechtzeitig an. Außerdem," }
  { key: PHRASE_great_festival_too_late_reason_C_C, text: "obwohl die [amount] [item], die Ihr nach [city_name] gesendet habt, nicht rechtzeitig für das Große Fest zu [god] ankamen, da Ihr Euer Bestes getan habt," }
  { key: PHRASE_great_festival_refuse_reason_P_A, text: "weil Ihr es vernachlässigt habt, Pharaos Forderung nach [amount] [item] für das Große Fest zu [god] bei [city_name] zu erfüllen," }
  { key: PHRASE_great_festival_refuse_reason_P_B, text: "Ihr habt es vernachlässigt, Pharaos Forderung nach [amount] [item] für das Große Fest zu [god] bei [city_name] zu erfüllen. Außerdem," }
  { key: PHRASE_great_festival_refuse_reason_P_C, text: "trotz Eures Versagens bei der Erfüllung von Pharaos Forderung nach [amount] [item] für das Große Fest zu [god] bei [city_name]," }
  { key: PHRASE_great_festival_refuse_reason_C_A, text: "weil Ihr [city_name] und seine Forderung nach [amount] [item] für das Große Fest zu [god] missachtet habt," }
  { key: PHRASE_great_festival_refuse_reason_C_B, text: "Ihr habt [city_name] und seine Forderung nach [amount] [item] für das Große Fest zu [god] missachtet. Außerdem," }
  { key: PHRASE_great_festival_refuse_reason_C_C, text: "obwohl Ihr [city_name] und seine Forderung nach [amount] [item] für das Große Fest zu [god] missachtet habt," }
  { key: PHRASE_great_festival_no_reason_P_A, text: "weil Pharao die Gottheit ehren möchte," }
  { key: PHRASE_great_festival_no_reason_P_B, text: "weil [god] noch immer unzufrieden ist," }
  { key: PHRASE_great_festival_no_reason_P_C, text: "" }
  { key: PHRASE_great_festival_no_reason_C_A, text: "weil [city_name] von [god] gesegnet ist," }
  { key: PHRASE_great_festival_no_reason_C_B, text: "weil [god] noch immer unzufrieden ist," }
  { key: PHRASE_great_festival_no_reason_C_C, text: "" }
  
  { key: PHRASE_project_title_P, text: "Bau für Pharao" }
  { key: PHRASE_project_title_C, text: "Bauprojekt" }
  { key: PHRASE_project_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] Pharao baut etwas so Gewaltiges, dass er Euch braucht, um [amount] [item] nach [city_name] innerhalb von [time_allotted] Monaten zu senden. Was auch immer das Projekt ist, es wird sicher zu Ägyptens Ruhm beitragen." }
  { key: PHRASE_project_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] fordert, dass Ihr [amount] [item] innerhalb von [time_allotted] Monaten für ein großes Bauprojekt in der Stadt entsendet." }
  { key: PHRASE_project_reminder_P, text: "[greeting] [player_name], Pharao steht kurz davor, in Rage zu geraten. Ihr habt noch immer nicht die [amount] [item] nach [city_name] für sein Bauprojekt gesendet. Ihr habt 6 Monate Zeit, um Pharaos Forderung nachzukommen." }
  { key: PHRASE_project_reminder_C, text: "[greeting] [player_name], [city_name] benötigt [amount] [item], wenn es sein Bauprojekt vollenden soll. Sendet die Lieferungen innerhalb von 6 Monaten, oder die Stadtführer könnten verärgert werden." }
  { key: PHRASE_project_overdue_P, text: "[greeting] [player_name], Pharao ist angewidert von Eurer Unverschämtheit. Ihr habt nicht rechtzeitig [amount] [item] nach [city_name] gesendet, damit er sein Bauprojekt vollenden konnte. Wenn Ihr sie trotzdem noch senden könnt, könntet Ihr vielleicht das Gesicht wahren." }
  { key: PHRASE_project_overdue_C, text: "[greeting] [player_name], [city_name] erwägt, Euch bei Pharao zu melden. Weil Ihr nicht rechtzeitig [amount] [item] gesendet habt, kann es sein Bauprojekt möglicherweise nicht vollenden. Wenn Ihr sie trotzdem sendet, könnte [city_name] noch in der Lage sein, dieses Projekt zu beenden, und könnte über Eure Untätigkeit schweigen." }
  { key: PHRASE_project_warning_P, text: "[greeting] [player_name], ein unvollständiges Projekt wird Pharao nur blamieren. Ihr habt noch 6 Monate Zeit, um [amount] [item] nach [city_name] für sein Bauprojekt zu senden. Wenn Ihr ihn enttäuscht, wird Pharao seine Schande mit Euch teilen." }
  { key: PHRASE_project_warning_C, text: "[greeting] [player_name], Ihr habt nur noch 6 Monate Zeit, um [amount] [item] nach [city_name] für ihr Bauprojekt zu senden. Wenn Ihr die Waren nicht sendet, ist nicht abzusehen, was die Stadt als Vergeltung tun könnte." }
  { key: PHRASE_project_comply_reason_P_A, text: "weil die [amount] [item], die Ihr gesendet habt, wesentlich für den rechtzeitigen Abschluss von Pharaos Bauprojekt in [city_name] waren," }
  { key: PHRASE_project_comply_reason_P_B, text: "die [amount] [item], die Ihr gesendet habt, waren wesentlich für den rechtzeitigen Abschluss von Pharaos Bauprojekt in [city_name]. Außerdem," }
  { key: PHRASE_project_comply_reason_P_C, text: "obwohl die [amount] [item], die Ihr gesendet habt, wesentlich für den rechtzeitigen Abschluss von Pharaos Bauprojekt in [city_name] waren," }
  { key: PHRASE_project_comply_reason_C_A, text: "weil Ihr [city_name] geholfen habt, sein Projekt erfolgreich termingerecht abzuschließen, indem Ihr [amount] [item] gesendet habt," }
  { key: PHRASE_project_comply_reason_C_B, text: "Ihr habt [city_name] geholfen, sein Projekt im Zeitplan zu halten, indem Ihr [amount] [item] gesendet habt. Nebenbei," }
  { key: PHRASE_project_comply_reason_C_C, text: "obwohl Ihr [city_name] geholfen habt, sein Projekt erfolgreich termingerecht abzuschließen, indem Ihr [amount] [item] gesendet habt," }
  { key: PHRASE_project_too_late_reason_P_A, text: "weil Ihr Pharaos Bauprojekt bei [city_name] verzögert habt, indem Ihr zu lange gewartet habt, um [amount] [item] zu senden," }
  { key: PHRASE_project_too_late_reason_P_B, text: "Pharaos Bauprojekt bei [city_name] ist ins Stocken geraten, weil Ihr zu lange gewartet habt, um die [amount] [item] zu senden, um die er bat. Außerdem," }
  { key: PHRASE_project_too_late_reason_P_C, text: "trotz der Tatsache, dass Ihr Pharaos Bauprojekt bei [city_name] verzögert habt, indem Ihr zu lange gewartet habt, um [amount] [item] zu senden, wurde Eure Bemühung geschätzt, und daher" }
  { key: PHRASE_project_too_late_reason_C_A, text: "weil Ihr gezögert habt und [city_name] nicht [amount] [item] gesendet habt," }
  { key: PHRASE_project_too_late_reason_C_B, text: "Ihr habt gezögert, [city_name] die [amount] [item] zu senden, die sie benötigten. Nebenbei" }
  { key: PHRASE_project_too_late_reason_C_C, text: "obwohl Ihr gezögert habt, [city_name] die [amount] [item] zu senden, die sie benötigten, wurde Eure Bemühung geschätzt, und daher" }
  { key: PHRASE_project_refuse_reason_P_A, text: "weil Ihr Pharaos Forderung nach [amount] [item] für sein wichtiges Projekt bei {city_name] abgelehnt habt," }
  { key: PHRASE_project_refuse_reason_P_B, text: "Ihr habt unklugerweise Pharaos Forderung nach [amount] [item] für sein wichtiges Projekt bei {city_name] abgelehnt. Außerdem," }
  { key: PHRASE_project_refuse_reason_P_C, text: "obwohl es unklug war, Pharaos Forderung nach [amount] [item] für sein wichtiges Projekt bei {city_name] abzulehnen, wie Ihr es tatet," }
  { key: PHRASE_project_refuse_reason_C_A, text: "weil Ihr [city_name] und ihre Forderung nach [amount] [item] verschmäht habt," }
  { key: PHRASE_project_refuse_reason_C_B, text: "Ihr habt [city_name] und ihre Forderung nach [amount] [item] verschmäht. Zusätzlich," }
  { key: PHRASE_project_refuse_reason_C_C, text: "obwohl Ihr [city_name] und ihre Forderung nach [amount] [item] verschmäht habt," }
  { key: PHRASE_project_no_reason_P_A, text: "um seine vielen Errungenschaften zu feiern," }
  { key: PHRASE_project_no_reason_P_B, text: "weil noch viel Arbeit zu erledigen ist" }
  { key: PHRASE_project_no_reason_P_C, text: "" }
  { key: PHRASE_project_no_reason_C_A, text: "um die Herrlichkeit Ägyptens zu ehren," }
  { key: PHRASE_project_no_reason_C_B, text: "weil noch viel zu tun ist" }
  { key: PHRASE_project_no_reason_C_C, text: "" }
  
  { key:PHRASE_famine_title_P, text: "Hungersnot" }
  { key:PHRASE_famine_title_C, text: "Hungersnot" }
  { key:PHRASE_famine_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] Hungersnot erfasst [city_name]. Pharao verlangt, dass Ihr Hilfe leistet. Ihr habt [time_allotted], um [amount] [item] in die Stadt zu senden, um ihr Leid zu lindern." }
  { key:PHRASE_famine_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] Hungersnot hat [city_name] getroffen, und seine Menschen verhungern. Sendet [amount] [item] innerhalb von [time_allotted] Monaten. Leben stehen auf dem Spiel!" }
  { key:PHRASE_famine_reminder_P, text: "[greeting] [player_name], Pharao fragt sich, ob Ihr ein Herz habt. Ihr habt noch immer nicht die [amount] [item] nach [city_name] gesendet, und seine Menschen sind in Not. Ihr habt nur noch 6 Monate Zeit, um Pharaos Forderung nachzukommen." }
  { key:PHRASE_famine_reminder_C, text: "[greeting] [player_name], die Menschen von [city_name] klagen vor Hunger, und Ihr habt noch immer nicht die [amount] [item] gesendet. Sendet die Lieferungen innerhalb von 6 Monaten, oder das Wehklagen des Hungers wird durch Klagelieder für die Toten ersetzt." }
  { key:PHRASE_famine_overdue_P, text: "[greeting] [player_name], Pharao hält Euch für so gemein wie eine Viper. Ihr habt nichts getan, um den Hunger Eurer Landsleute zu lindern. Ihr könnt noch immer [amount] [item] nach [city_name] senden und die Chance haben, Euer Ansehen in Pharaos Augen wiederherzustellen." }
  { key:PHRASE_famine_overdue_C, text: "[greeting] [player_name], die erbärmlichen Schreie des Verhungerns sind offenbar auf taube Ohren gestoßen. Ihr habt die [amount] [item] nicht rechtzeitig nach [city_name] gesendet. Besser spät als nie... wenn Ihr die Nahrung trotzdem sendet, könnt Ihr noch etwas Erleichterung verschaffen, falls noch jemand übrig ist, der davon profitieren kann." }
  { key:PHRASE_famine_warning_P, text: "[greeting] [player_name], wenn Ihr nicht [amount] [item] nach [city_name] innerhalb von 6 Monaten sendet, werdet Ihr überhaupt nichts Gutes tun. Pharao wird Eure Lieblosigkeit missbilligen, wenn Ihr es versäumt, die Waren zu senden." }
  { key:PHRASE_famine_warning_C, text: "[greeting] [player_name], die Menschen von [city_name] fragen sich, ob Euer Herz grausam ist. Ihr habt nur noch 6 Monate Zeit, um [amount] [item] zu senden, um ihr Leiden zu lindern. Verweigert es ihnen, und ihre Tode werden auf Eurem Haupt lasten." }
  { key:PHRASE_famine_comply_reason_P_A, text: "weil Ihr schnell [amount] [item] als Antwort auf die Bedürfnisse von [city_name] gesendet habt, wie Pharao befahl," }
  { key:PHRASE_famine_comply_reason_P_B, text: "Ihr habt schnell [amount] [item] als Antwort auf die Bedürfnisse von [city_name] gesendet, wie Pharao befahl. Das war weise. Nun," }
  { key:PHRASE_famine_comply_reason_P_C, text: "obwohl Ihr prompt die [amount] [item] als Antwort auf die Bedürfnisse von [city_name] gesendet habt, wie Pharao befahl, dennoch" }
  { key:PHRASE_famine_comply_reason_C_A, text: "weil die [amount] [item], die Ihr gesendet habt, die Bäuche von [city_name] während der Hungersnot füllten," }
  { key:PHRASE_famine_comply_reason_C_B, text: "die [amount] [item], die Ihr nach [city_name] gesendet habt, füllten die Bäuche seiner Menschen während der Hungersnot. Zusätzlich berichten Wesire, dass" }
  { key:PHRASE_famine_comply_reason_C_C, text: "obwohl die [amount] [item], die Ihr den Menschen von [city_name] gesendet habt, ihnen halfen, mit der jüngsten Hungersnot fertig zu werden, dennoch" }
  { key:PHRASE_famine_too_late_reason_P_A, text: "weil Ihr Pharaos Menschen bei [city_name] zu lange leiden ließet, indem Ihr mit dem Senden von [amount] [item] wartetet," }
  { key:PHRASE_famine_too_late_reason_P_B, text: "Ihr ließet Pharaos Menschen bei [city_name] zu lange leiden, indem Ihr mit dem Senden der [amount] [item], die sie benötigten, wartetet. Außerdem berichten Wesire, dass" }
  { key:PHRASE_famine_too_late_reason_P_C, text: "obwohl Ihr Pharaos Menschen bei [city_name] zu lange leiden ließet, indem Ihr mit dem Senden der [amount] [item], die sie benötigten, wartetet, erwies es sich doch als etwas hilfreich, und daher" }
  { key:PHRASE_famine_too_late_reason_C_A, text: "weil Ihr zu lange brauchtet, um [amount] [item] zur Hilfe für die Menschen von [city_name] zu entsenden," }
  { key:PHRASE_famine_too_late_reason_C_B, text: "Ihr brauchtet viel zu lange, um [amount] [item] zur Hilfe für die Menschen von [city_name] zu entsenden, und ihr Leiden war groß. Obendrein," }
  { key:PHRASE_famine_too_late_reason_C_C, text: "obwohl Ihr zu lange brauchtet, um [amount] [item] zu den Menschen von [city_name] zu entsenden, half die Nahrung, die Nachwirkungen der Hungersnot etwas zu lindern, und daher" }
  { key:PHRASE_famine_refuse_reason_P_A, text: "weil Ihr Pharao und seine Menschen bei [city_name] während der Hungersnot verschmähtet, indem Ihr Euch weigerten, [amount] [item] zu senden," }
  { key:PHRASE_famine_refuse_reason_P_B, text: "Ihr habt Pharao und seine Menschen bei [city_name] während der Hungersnot verschmäht, indem Ihr Euch weigerten, [amount] [item] zu senden. Das war unklug. Außerdem berichten Wesire, dass" }
  { key:PHRASE_famine_refuse_reason_P_C, text: "Ihr habt Pharao und seine Menschen bei [city_name] während der Hungersnot verschmäht, indem Ihr Euch weigerten, [amount] [item] zu senden, aber trotzdem" }
  { key:PHRASE_famine_refuse_reason_C_A, text: "weil Ihr den Menschen von [city_name] während der Hungersnot den Rücken kehrtet und [amount] [item] vorenthieltet," }
  { key:PHRASE_famine_refuse_reason_C_B, text: "Ihr habt den Menschen von [city_name] während der Hungersnot den Rücken gekehrt und [amount] [item] vorenthalten. Wesire berichten auch, dass" }
  { key:PHRASE_famine_refuse_reason_C_C, text: "obwohl Ihr den Menschen von [city_name] während der Hungersnot den Rücken kehrtet und [amount] [item] vorenthieltet," }
  { key:PHRASE_famine_no_reason_P_A, text: "Das Schicksal lächelt Pharaos Menschen nicht zu, und" }
  { key:PHRASE_famine_no_reason_P_B, text: "die Probleme häufen sich weiter an, da" }
  { key:PHRASE_famine_no_reason_P_C, text: "" }
  { key:PHRASE_famine_no_reason_C_A, text: "die Menschen von [city_name] verlieren die Hoffnung, denn" }
  { key:PHRASE_famine_no_reason_C_B, text: "die Probleme häufen sich weiter an, da" }
  { key:PHRASE_famine_no_reason_C_C, text: "" }
  
  
    { key:PHRASE_threat_title_P, text: "Erpressung durch Pharao" }
  { key:PHRASE_threat_title_C, text: "Erpressung durch eine andere Stadt" }
  { key:PHRASE_threat_initial_announcement_P, text: "[greeting] [player_name], [reason_phrase] Pharao befiehlt Euch, [amount] [item] nach [city_name] in [time_allotted] Monaten zu senden. Andernfalls wird er Eure schöne Stadt angreifen." }
  { key:PHRASE_threat_initial_announcement_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] verlangt, dass Ihr [amount] [item] in [time_allotted] Monaten entsendet. Wenn Ihr die Forderung verweigert, wird [city_name] seine Armeen gegen Eure schöne Stadt entsenden." }
  { key:PHRASE_threat_reminder_P, text: "[greeting] [player_name], der stolze Pharao sammelt seine Truppen und wird ihnen bald befehlen anzugreifen. Ihr solltet die [amount] [item] innerhalb von 6 Monaten nach [city_name] senden, um die Unannehmlichkeiten abzuwenden." }
  { key:PHRASE_threat_reminder_C, text: "[greeting] [player_name], die Armee von [city_name] rüstet sich zum Krieg und erwartet einen guten Kampf. Wenn Ihr die [amount] [item] innerhalb von 6 Monaten entsendet, wird die Stadt ihre Aggression einstellen. Ihre Soldaten werden allerdings sehr enttäuscht sein." }
  { key:PHRASE_threat_overdue_P, text: "[greeting] [player_name], Eure Zeit ist abgelaufen, und Pharao dürstet nach Blut. Ihr könnt noch eine Chance haben, seine Streitkräfte in Schach zu halten, wenn Ihr die [amount] [item] so schnell wie möglich nach [city_name] entsendet." }
  { key:PHRASE_threat_overdue_C, text: "[greeting] [player_name], Schlachtrufe sind überall in [city_name] zu hören, während es sich vorbereitet, Eure Stadt zu zerstören. Entsendet die [amount] [item] so schnell wie möglich nach [city_name], und sie mögen etwas Gnade zeigen." }
  { key:PHRASE_threat_warning_P, text: "[greeting] [player_name], der ruhmgierige Pharao ist begierig darauf, mit Gewalt zu nehmen, was Ihr ihm nicht bereitwillig gegeben habt. Seine Armee ist gut vorbereitet, aber Ihr könnt Eure Stadt vor Gemetzel retten, wenn Ihr ihm [amount] [item] innerhalb von 6 Monaten entsendet. Andernfalls bereitet Euer Volk auf Blutvergießen vor." }
  { key:PHRASE_threat_warning_C, text: "[greeting] [player_name], die Eroberungsstreitkräfte von [city_name] sind bereit zu marschieren. Wenn Ihr [amount] [item] innerhalb von 6 Monaten entsendet, könnten die angreifenden Streitkräfte Eure Stadt unversehrt lassen." }
  { key:PHRASE_threat_comply_reason_P_A, text: "weil Ihr Pharao nachgegeben und [amount] [item] nach [city_name] gesendet habt," }
  { key:PHRASE_threat_comply_reason_P_B, text: "Ihr habt Pharao nachgegeben und [amount] [item] bezüglich [city_name] gesendet. Außerdem berichten Wesire, dass" }
  { key:PHRASE_threat_comply_reason_P_C, text: "obwohl Ihr getan habt, was Pharao für [city_name] verlangte," }
  { key:PHRASE_threat_comply_reason_C_A, text: "weil Ihr Euch den Befehlen von [city_name] gebeugt und [amount] [item] gesendet habt," }
  { key:PHRASE_threat_comply_reason_C_B, text: "Ihr habt Euch den Befehlen von [city_name] gebeugt und [amount] [item] gesendet. Zusätzlich scheint es, dass" }
  { key:PHRASE_threat_comply_reason_C_C, text: "obwohl Ihr den Forderungen von [city_name] nach [amount] [item] nachgegeben habt, dennoch" }
  { key:PHRASE_threat_too_late_reason_P_A, text: "die Verzögerung beim Senden von [amount] [item] nach [city_name], wie Pharao es verlangte, strapaziert seine Geduld, und aus diesem Grund" }
  { key:PHRASE_threat_too_late_reason_P_B, text: "die Verzögerung beim Senden von [amount] [item] nach [city_name], wie Pharao es verlangte, strapaziert seine Geduld. Zu anderen Angelegenheiten:" }
  { key:PHRASE_threat_too_late_reason_P_C, text: "die Verzögerung beim Senden von [amount] [item] nach [city_name], wie Pharao es verlangte, strapaziert seine Geduld, aber dennoch wird Eure Bemühung geschätzt. Daher" }
  { key:PHRASE_threat_too_late_reason_C_A, text: "weil Ihr die Drohung von [city_name] unterschätzt und [amount] [item] nicht schnell entsandt habt," }
  { key:PHRASE_threat_too_late_reason_C_B, text: "Ihr müsst die Drohung von [city_name] unterschätzt haben, da Ihr [amount] [item] nicht schnell entsandt habt. Aber das ist Vergangenheit, nun" }
  { key:PHRASE_threat_too_late_reason_C_C, text: "Ihr seid große Risiken eingegangen, indem Ihr die [amount] [item] nicht umgehend nach [city_name] entsandt habt, wie sie es verlangten. Da Ihr es dennoch geschafft habt nachzukommen," }
  { key:PHRASE_threat_refuse_reason_P_A, text: "weil Ihr Pharaos Befehl trotzt habt, [amount] [item] nach [city_name] zu senden," }
  { key:PHRASE_threat_refuse_reason_P_B, text: "Ihr habt Pharaos Befehl trotzt, [amount] [item] nach [city_name] zu senden. Zusätzlich," }
  { key:PHRASE_threat_refuse_reason_P_C, text: "trotz Eurer Weigerung, Pharaos Drohung zu befolgen, die verlangte, dass Ihr [amount] [item] nach [city_name] entsendet," }
  { key:PHRASE_threat_refuse_reason_C_A, text: "weil Ihr wissentlich Gefahr heraufbeschworen habt, als Ihr Euch weigerten, [amount] [item] nach [city_name] zu senden," }
  { key:PHRASE_threat_refuse_reason_C_B, text: "Ihr habt wissentlich Gefahr heraufbeschworen, als Ihr Euch weigerten, [amount] [item] nach [city_name] zu senden. Ihr solltet auch wissen, dass" }
  { key:PHRASE_threat_refuse_reason_C_C, text: "obwohl Ihr gewiss Gefahr heraufbeschworen habt, als Ihr Euch weigerten, [amount] [item] nach [city_name] zu senden," }
  { key:PHRASE_threat_no_reason_P_A, text: "weil er übler Laune ist," }
  { key:PHRASE_threat_no_reason_P_B, text: "da Pharaos üble Laune kein Ende zu haben scheint," }
  { key:PHRASE_threat_no_reason_P_C, text: "" }
  { key:PHRASE_threat_no_reason_C_A, text: "weil [city_name] nach Ruhm giert," }
  { key:PHRASE_threat_no_reason_C_B, text: "es scheint, [city_name] wird niemals zufrieden sein," }
  { key:PHRASE_threat_no_reason_C_C, text: "" }
  
  { key:PHRASE_eg_city_falls_title, text: "Ägyptische Stadt fällt" }
  { key:PHRASE_eg_city_falls_initial_announcement, text: "[greeting] [player_name], [reason_phrase] die mächtige Stadt [city_name] ist unseren Feinden zum Opfer gefallen." }
  { key:PHRASE_eg_city_falls_reason_A, text: "weil [city_name] eindringenden Streitkräften zum Opfer gefallen ist," }
  { key:PHRASE_eg_city_falls_reason_B, text: "[city_name] ist eindringenden Streitkräften zum Opfer gefallen. Darüber hinaus," }
  { key:PHRASE_eg_city_falls_reason_C, text: "obwohl [city_name] eindringenden Streitkräften zum Opfer gefallen ist," }
  { key:PHRASE_eg_city_falls_no_reason_A, text: "wehe [city_name]:" }
  { key:PHRASE_eg_city_falls_no_reason_B, text: "es scheint, die Schwierigkeiten in [city_name] werden nie enden, denn" }
  { key:PHRASE_eg_city_falls_no_reason_C, text: "" }
  
  { key:PHRASE_foreign_city_conquered_title, text: "Fremde Stadt erobert" }
  { key:PHRASE_foreign_city_conquered_initial_announcement, text: "[greeting] [player_name], [reason_phrase] Ägypten hat erfolgreich die berühmte Stadt [city_name] erobert und unseren Einfluss noch weiter ausgedehnt!" }
  { key:PHRASE_foreign_city_conquered_reason_A, text: "weil die fremde Stadt [city_name] von unseren Truppen unterworfen wurde," }
  { key:PHRASE_foreign_city_conquered_reason_B, text: "die fremde Stadt [city_name] wurde von unseren Truppen unterworfen! Nun," }
  { key:PHRASE_foreign_city_conquered_reason_C, text: "obwohl die fremde Stadt [city_name] von unseren Truppen unterworfen wurde," }
  { key:PHRASE_foreign_city_conquered_no_reason_A, text: "aufgrund unserer Waffenstärke," }
  { key:PHRASE_foreign_city_conquered_no_reason_B, text: "die Stärke unseres Königreichs wächst weiter. Nun" }
  { key:PHRASE_foreign_city_conquered_no_reason_C, text: "" }
  
  { key:PHRASE_route_opened_title, text: "Neue Handelsroute verfügbar" }
  { key:PHRASE_route_opened_initial_announcement, text: "[greeting] [player_name], [reason_phrase] eine neue Handelsroute nach [city_name] kann nun eröffnet werden." }
  { key:PHRASE_route_opened_reason_A, text: "weil eine neue Handelsroute nach [city_name] verfügbar geworden ist," }
  { key:PHRASE_route_opened_reason_B, text: "eine neue Handelsroute nach [city_name] ist verfügbar geworden, und" }
  { key:PHRASE_route_opened_reason_C, text: "obwohl Handel mit [city_name] möglich geworden ist," }
  { key:PHRASE_route_opened_no_reason_A, text: "aufgrund diplomatischer Aktivität," }
  { key:PHRASE_route_opened_no_reason_B, text: "Wandel liegt in der Luft, denn" }
  { key:PHRASE_route_opened_no_reason_C, text: "" }
  
  { key:PHRASE_route_closed_title, text: "Handelsroute schließt" }
  { key:PHRASE_route_closed_initial_announcement, text: "[greeting] [player_name], [reason_phrase] die Handelsroute nach [city_name] wurde geschlossen." }
  { key:PHRASE_route_closed_reason_A, text: "weil die Handelsroute nach [city_name] geschlossen wurde," }
  { key:PHRASE_route_closed_reason_B, text: "die Handelsroute nach [city_name] wurde geschlossen, und darüber hinaus," }
  { key:PHRASE_route_closed_reason_C, text: "obwohl die Handelsroute nach [city_name] geschlossen wurde," }
  { key:PHRASE_route_closed_no_reason_A, text: "aufgrund politischer Instabilität," }
  { key:PHRASE_route_closed_no_reason_B, text: "...dies hätte vorhergesehen werden sollen. Es scheint" }
  { key:PHRASE_route_closed_no_reason_C, text: "" }
  
  { key:PHRASE_trade_city_siege_title, text: "Handelsstadt wird belagert" }
  { key:PHRASE_trade_city_siege_announcement, text: "[greeting] [player_name], [reason_phrase] eine schwächende Belagerung trifft nun [city_name]." }
  { key:PHRASE_trade_city_siege_reason_A, text: "weil [city_name] belagert wird," }
  { key:PHRASE_trade_city_siege_reason_B, text: "[city_name] wird belagert, und" }
  { key:PHRASE_trade_city_siege_reason_C, text: "obwohl [city_name] belagert wird," }
  { key:PHRASE_trade_city_siege_no_reason_A, text: "Militärkundschafter haben schreckliche Nachrichten zu berichten. Es scheint" }
  { key:PHRASE_trade_city_siege_no_reason_B, text: "es gibt kein erkennbares Ende ihrer Schwierigkeiten, denn" }
  { key:PHRASE_trade_city_siege_no_reason_C, text: "" }
  
  { key:PHRASE_eg_city_saved_title, text: "Ägyptische Stadt gerettet" }
  { key:PHRASE_eg_city_saved_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [city_name] wurde vor unseren Feinden gerettet. " }
  { key:PHRASE_eg_city_saved_reason_A, text: "weil [city_name] vor unseren Feinden gerettet wurde," }
  { key:PHRASE_eg_city_saved_reason_B, text: "[city_name] wurde vor unseren Feinden gerettet! Nun," }
  { key:PHRASE_eg_city_saved_reason_C, text: "obwohl [city_name] vor unseren Feinden gerettet wurde," }
  { key:PHRASE_eg_city_saved_no_reason_A, text: "aufgrund einer tapferen Anstrengung seitens der ägyptischen Armee," }
  { key:PHRASE_eg_city_saved_no_reason_B, text: "die Gezeiten des Krieges schwingen hin und her, denn nun" }
  { key:PHRASE_eg_city_saved_no_reason_C, text: "" }
  
  
    { key:PHRASE_battle_won_title, text: "Sieg in der Schlacht" }
  { key:PHRASE_battle_won_initial_announcement, text: "[greeting] [player_name], [reason_phrase] die ägyptische Armee war siegreich!" }
  { key:PHRASE_battle_won_reason_A, text: "weil unsere Streitkräfte in der fernen Schlacht um [city_name] triumphierten," }
  { key:PHRASE_battle_won_reason_B, text: "unsere Streitkräfte triumphierten in der fernen Schlacht um [city_name]. Nun" }
  { key:PHRASE_battle_won_reason_C, text: "obwohl unsere Streitkräfte in der Schlacht um [city_name] triumphierten" }
  { key:PHRASE_battle_won_no_reason_A, text: "aufgrund der Vitalität gut ausgebildeter Truppen bei der fernen Stadt [city_name]," }
  { key:PHRASE_battle_won_no_reason_B, text: "es scheint, die Wunder werden nie enden, denn bei [city_name]" }
  { key:PHRASE_battle_won_no_reason_C, text: "" }
  
  { key:PHRASE_battle_lost_title, text: "Ägyptische Armee besiegt" }
  { key:PHRASE_battle_lost_initial_announcement, text: "[greeting] [player_name], [reason_phrase] die ägyptische Armee wurde bei [city_name] besiegt. " }
  { key:PHRASE_battle_lost_reason_A, text: "weil Ägypten eine Schlacht gegen seine Feinde bei [city_name] verloren hat," }
  { key:PHRASE_battle_lost_reason_B, text: "Ägypten hat eine Schlacht gegen seine Feinde bei [city_name] verloren. Darüber hinaus," }
  { key:PHRASE_battle_lost_reason_C, text: "obwohl Ägypten die Schlacht gegen seine Feinde bei [city_name] verloren hat," }
  { key:PHRASE_battle_lost_no_reason_A, text: "großes Unglück hat die Truppen heimgesucht, denn" }
  { key:PHRASE_battle_lost_no_reason_B, text: "Krieg ist so schrecklich unvorhersehbar. Unglücklicherweise" }
  { key:PHRASE_battle_lost_no_reason_C, text: "" }
  
  { key:PHRASE_acknowledgement_title, text: "Befolgung anerkannt" }
  { key:PHRASE_acknowledgement_initial_announcement, text: "[greeting] [player_name], [reason_phrase] Eure Stadt ist sicher... vorerst." }
  { key:PHRASE_acknowledgement_reason_A, text: "weil Ihr einer Drohung unterwürfig nachgegeben habt," }
  { key:PHRASE_acknowledgement_reason_B, text: "Ihr habt einer Drohung unterwürfig nachgegeben," }
  { key:PHRASE_acknowledgement_reason_C, text: "obwohl Ihr einer Drohung unterwürfig nachgegeben habt," }
  { key:PHRASE_acknowledgement_no_reason_A, text: "aufgrund eines Sinneswandels," }
  { key:PHRASE_acknowledgement_no_reason_B, text: "nichts ist jemals gewiss, aber" }
  { key:PHRASE_acknowledgement_no_reason_C, text: "" }
  
  { key: PHRASE_pharaoh_attacks_you_title, text: "Pharaos Armee greift an" }
  { key: PHRASE_pharaoh_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee ist unterwegs und wird Eure Stadt in [time_until_attack] Monaten erreichen." }
  { key: PHRASE_pharaoh_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee rückt immer näher und wird Eure Stadt in zwei Jahren erreichen." }
  { key: PHRASE_pharaoh_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee ist kampfbereit und wird Eure Stadt in einem Jahr erreichen." }
  { key: PHRASE_pharaoh_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee erwartet sehnsüchtig, Euch anzugreifen und wird Eure Stadt in sechs Monaten erreichen." }
  { key: PHRASE_pharaoh_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee ist nur noch einen Monat davon entfernt, die Stadt zu erreichen!" }
  { key: PHRASE_pharaoh_attacks_you_city_attacked_alert, text: "[greeting] [player_name], Pharaos Armee ist über uns!" }
  { key: PHRASE_pharaoh_attacks_you_reason_A, text: "weil Eure Stadt von Pharaos Armee angegriffen wurde," }
  { key: PHRASE_pharaoh_attacks_you_reason_B, text: "Eure Stadt wurde von Pharaos Armee angegriffen. Darüber hinaus" }
  { key: PHRASE_pharaoh_attacks_you_reason_C, text: "obwohl Eure Stadt von Pharaos Armee angegriffen wurde," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_A, text: "manchmal handelt Pharao aus Gründen, die nur ihm bekannt sind. " }
  { key: PHRASE_pharaoh_attacks_you_no_reason_B, text: "Pharao ist unberechenbar. Nun," }
  { key: PHRASE_pharaoh_attacks_you_no_reason_C, text: "weil Euer Ansehen im Königreich so tief gefallen ist," }
  { key: PHRASE_pharaoh_attacks_you_because_of_low_kingdom, text: "Euer Ansehen im Königreich ist vollständig gefallen. Vielleicht können noch mehr Geschenke an das ägyptische Volk die Dinge zum Besseren wenden, obwohl selbst jetzt" }
  
  { key: PHRASE_eg_city_attacks_you_title, text: "Ägyptische Armee greift an" }
  { key: PHRASE_eg_city_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] eine ägyptische Armee bereitet ihren Angriff vor und wird Eure Stadt in [time_until_attack] Monaten erreichen." }
  { key: PHRASE_eg_city_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] eine ägyptische Armee hat ihren Marsch begonnen und wird Eure Stadt in zwei Jahren erreichen." }
  { key: PHRASE_eg_city_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] Eure Stadt wird den Ansturm einer ägyptischen Armee in einem Jahr erleiden." }
  { key: PHRASE_eg_city_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] eine ägyptische Armee nähert sich und wird Eure Stadt in sechs Monaten erreichen." }
  { key: PHRASE_eg_city_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] eine ägyptische Armee nähert sich Euren Grenzen und wird Eure Stadt in einem Monat erreichen." }
  { key: PHRASE_eg_city_attacks_you_city_attacked_alert, text: "[greeting] [player_name], eine Invasionstruppe ägyptischer Soldaten ist über uns!" }
  { key: PHRASE_eg_city_attacks_you_reason_A, text: "weil Eure Stadt von einer ägyptischen Armee angegriffen wurde," }
  { key: PHRASE_eg_city_attacks_you_reason_B, text: "die ägyptische Armee hat Eure Stadt angegriffen! Zusätzlich" }
  { key: PHRASE_eg_city_attacks_you_reason_C, text: "obwohl Eure Stadt von der ägyptischen Armee angegriffen wurde," }
  { key: PHRASE_eg_city_attacks_you_no_reason_A, text: "Vorsicht:" }
  { key: PHRASE_eg_city_attacks_you_no_reason_B, text: "die Zeit für den Krieg ist gekommen, denn" }
  { key: PHRASE_eg_city_attacks_you_no_reason_C, text: "weil Euer Ruf im Königreich so niedrig ist," }
  { key: PHRASE_eg_city_attacks_you_because_of_low_kingdom, text: "Euer Ansehen im Königreich ist vollständig gefallen. Vielleicht können noch mehr Geschenke an das ägyptische Volk die Dinge zum Besseren wenden, obwohl selbst jetzt" }
  
  { key: PHRASE_foreign_army_attacks_you_title, text: "Fremde Armee fällt ein" }
  { key: PHRASE_foreign_army_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] nähert sich und wird Eure Stadt in [time_until_attack] Monaten erreichen." }
  { key: PHRASE_foreign_army_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] in zwei Jahren wird [a_foreign_army] vor Euren Toren stehen." }
  { key: PHRASE_foreign_army_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] ist begierig einzufallen und wird Eure Stadt in einem Jahr erreichen." }
  { key: PHRASE_foreign_army_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] wird Eure Stadt in sechs Monaten erreichen. Seid auf ihre Ankunft vorbereitet." }
  { key: PHRASE_foreign_army_attacks_you_1month_Warning, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] wird in einem Monat in der Stadt eintreffen, auf Eroberung aus." }
  { key: PHRASE_foreign_army_attacks_you_city_attacked_alert, text: "[greeting] [player_name], [a_foreign_army] ist über uns, und sie sind entschlossen, die Stadt zu zerstören!" }
  { key: PHRASE_foreign_army_attacks_you_reason_A, text: "weil Eure Stadt von [a_foreign_army] angegriffen wurde," }
  { key: PHRASE_foreign_army_attacks_you_reason_B, text: "Eure Stadt wurde von [a_foreign_army] angegriffen, und nun" }
  { key: PHRASE_foreign_army_attacks_you_reason_C, text: "obwohl Eure Stadt von [a_foreign_army] angegriffen wurde," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_A, text: "wegen ihrer Träume vom Imperium," }
  { key: PHRASE_foreign_army_attacks_you_no_reason_B, text: "es scheint, es gibt immer Ärger, denn" }
  { key: PHRASE_foreign_army_attacks_you_no_reason_C, text: "" }
  
  { key: PHRASE_rating_change_title_I, text: "Ansehen im Königreich steigt" }
  { key: PHRASE_rating_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] Ihr seid unter Euren ägyptischen Mitbürgern beliebter geworden, und Euer Ansehen im Königreich ist gestiegen." }
  { key: PHRASE_rating_change_reason_I_A, text: "weil Euer Ruf im Königreich kürzlich gestiegen ist," }
  { key: PHRASE_rating_change_reason_I_B, text: "Euer Ruf im Königreich hat sich verbessert. Nun" }
  { key: PHRASE_rating_change_reason_I_C, text: "Euer Ruf hat sich verbessert, aber" }
  { key: PHRASE_rating_change_no_reason_I_A, text: "weil die Zeiten gut sind," }
  { key: PHRASE_rating_change_no_reason_I_B, text: "dies sind gute Nachrichten, denn" }
  { key: PHRASE_rating_change_no_reason_I_C, text: "die Opfer Eurer Stadt im Kampf werden vom ägyptischen Volk sehr geschätzt. Infolgedessen" }
  { key: PHRASE_rating_change_title_D, text: "Ansehen im Königreich fällt" }
  { key: PHRASE_rating_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] das ägyptische Volk ist unzufrieden mit Euch, und Euer Ansehen im Königreich ist gefallen." }
  { key: PHRASE_rating_change_reason_D_A, text: "weil Euer Ansehen im Königreich so tief gefallen ist," }
  { key: PHRASE_rating_change_reason_D_B, text: "Eure Beliebtheit fällt im ganzen Königreich, und nun" }
  { key: PHRASE_rating_change_reason_D_C, text: "obwohl Ihr im Königreich immer unbeliebter werdet," }
  { key: PHRASE_rating_change_no_reason_D_A, text: "wegen Unzufriedenheit im Königreich," }
  { key: PHRASE_rating_change_no_reason_D_B, text: "dies sind schlechte Nachrichten, denn" }
  { key: PHRASE_rating_change_no_reason_D_C, text: "Eure Landsleute billigen Eure gewalttätigen Wege nicht. Infolgedessen" }
  
  { key:PHRASE_price_change_title_I, text: "Preiserhöhung" }
  { key:PHRASE_price_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] der Preis für [item] ist gestiegen. Der Import dieser Ware ist nun kostspieliger, aber höhere Gewinne können durch den Export erzielt werden." }
  { key:PHRASE_price_change_reason_I_A, text: "weil der Preis für [item] gestiegen ist," }
  { key:PHRASE_price_change_reason_I_B, text: "der Preis für [item] ist gestiegen, und darüber hinaus" }
  { key:PHRASE_price_change_reason_I_C, text: "obwohl die Preise gestiegen sind," }
  { key:PHRASE_price_change_no_reason_I_A, text: "wegen verringerten Vorräten in der ganzen Welt," }
  { key:PHRASE_price_change_no_reason_I_B, text: "während sich der Markt weiter verändert" }
  { key:PHRASE_price_change_no_reason_I_C, text: "" }
  { key:PHRASE_price_change_title_D, text: "Preissenkung" }
  { key:PHRASE_price_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] der Preis für [item] ist gefallen. Dies wird die Gewinne verringern, die durch den Export erzielt werden können." }
  { key:PHRASE_price_change_reason_D_A, text: "weil der Preis für [item], den Ihr handeln könnt, gefallen ist," }
  { key:PHRASE_price_change_reason_D_B, text: "die Preise sind gefallen, und darüber hinaus" }
  { key:PHRASE_price_change_reason_D_C, text: "obwohl die Preise gefallen sind," }
  { key:PHRASE_price_change_no_reason_D_A, text: "wegen eines Überangebots im ganzen Königreich," }
  { key:PHRASE_price_change_no_reason_D_B, text: "während sich der Markt weiter verändert" }
  { key:PHRASE_price_change_no_reason_D_C, text: "" }
  
  { key: PHRASE_demand_change_title_I, text: "Erhöhter Handel" }
  { key: PHRASE_demand_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] [city_name] ist nun bereit, noch mehr [item] zu handeln." }
  { key: PHRASE_demand_change_reason_I_A, text: "weil [city_name] bereit ist, mehr [item] zu handeln," }
  { key: PHRASE_demand_change_reason_I_B, text: "[city_name] wünscht nun, mehr [item] zu handeln. Darüber hinaus," }
  { key: PHRASE_demand_change_reason_I_C, text: "obwohl [city_name] mehr [item] handeln möchte," }
  { key: PHRASE_demand_change_no_reason_I_A, text: "weil [city_name] wächst," }
  { key: PHRASE_demand_change_no_reason_I_B, text: "die Zeiten ändern sich, und" }
  { key: PHRASE_demand_change_no_reason_I_C, text: "" }
  { key: PHRASE_demand_change_title_D, text: "Verringerter Handel" }
  { key: PHRASE_demand_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] [city_name] hat entschieden, dass sie die Menge an [item], die sie mit Euch handeln wollen, verringern müssen." }
  { key: PHRASE_demand_change_reason_D_A, text: "weil [city_name] nicht so viel [item] handelt," }
  { key: PHRASE_demand_change_reason_D_B, text: "[city_name] handelt nicht so viel, und" }
  { key: PHRASE_demand_change_reason_D_C, text: "obwohl [city_name] nicht so viel handelt," }
  { key: PHRASE_demand_change_no_reason_D_A, text: "weil die Bürger von [city_name] sparen," }
  { key: PHRASE_demand_change_no_reason_D_B, text: "die Zeiten ändern sich, und" }
  { key: PHRASE_demand_change_no_reason_D_C, text: "" }
  
  { key: PHRASE_earthquake_title, text: "Erdbeben!" }
  { key: PHRASE_earthquake_initial_announcement, text: "[greeting] [player_name], [reason_phrase] der Sand hat sich unter unseren Füßen verschoben. Unser Land wird nie mehr dasselbe sein. Tut, was Ihr könnt, um den Schaden zu reparieren, den das Erdbeben Eurer Stadt und Eurem Volk zugefügt hat." }
  { key: PHRASE_earthquake_reason_A, text: "wegen eines schrecklichen Erdbebens," }
  { key: PHRASE_earthquake_reason_B, text: "zusätzlich zu dem schrecklichen Erdbeben," }
  { key: PHRASE_earthquake_reason_C, text: "trotz des schrecklichen Erdbebens" }
  { key: PHRASE_earthquake_no_reason_A, text: "die Stadt ist verängstigt, weil" }
  { key: PHRASE_earthquake_no_reason_B, text: "Schwierigkeiten verfolgen die Stadt erneut, denn" }
  { key: PHRASE_earthquake_no_reason_C, text: "" }
  
  { key: PHRASE_stormy_seas_title, text: "Unwetter" }
  { key: PHRASE_stormy_seas_initial_announcement, text: "[greeting] [player_name], [reason_phrase] raue Gewässer drohen Handelsschiffe auseinanderzureißen. Es könnten Monate vergehen, bis die Winde sich beruhigen und Händler es wagen, ihre Frachten wieder zu riskieren. Bis dahin können wir nicht auf dem Wasserweg handeln." }
  { key: PHRASE_stormy_seas_reason_A, text: "wegen unergründlich heftiger Stürme," }
  { key: PHRASE_stormy_seas_reason_B, text: "während wir von jüngsten Stürmen heimgesucht wurden," }
  { key: PHRASE_stormy_seas_reason_C, text: "trotz der schrecklichen Stürme" }
  { key: PHRASE_stormy_seas_no_reason_A, text: "Stürme toben und" }
  { key: PHRASE_stormy_seas_no_reason_B, text: "unsere Schwierigkeiten haben gerade erst begonnen, denn" }
  { key: PHRASE_stormy_seas_no_reason_C, text: "" }
  
  { key: PHRASE_sandstorm_title, text: "Sandstürme" }
  { key: PHRASE_sandstorm_initial_announcement, text: "[greeting] [player_name], [reason_phrase] treibender Sand hat die Straßen verdeckt und sie an einigen Stellen vollständig bedeckt. Händler riskieren nicht, sich unter solchen Bedingungen zu verirren und wagen sich nicht hinaus. Bis die Winde nachlassen, wird kein Händler durchkommen können." }
  { key: PHRASE_sandstorm_reason_A, text: "weil Händler es nicht wagen, sich während eines Sandsturms auf den Weg zu machen, und der Landhandel zum Erliegen gekommen ist," }
  { key: PHRASE_sandstorm_reason_B, text: "Sandstürme haben Händler auf ihren Wegen gestoppt. Außerdem" }
  { key: PHRASE_sandstorm_reason_C, text: "trotz der jüngsten Sandstürme, die den Handel behindert haben," }
  { key: PHRASE_sandstorm_no_reason_A, text: "aufgrund starker Winde," }
  { key: PHRASE_sandstorm_no_reason_B, text: "die Wüste ist ein gefährlicher Ort, denn" }
  { key: PHRASE_sandstorm_no_reason_C, text: "" }
  
  { key: PHRASE_wage_change_title_I, text: "Arbeiter freuen sich über Erhöhung" }
  { key: PHRASE_wage_change_initial_announcement_I, text: "[greeting] [player_name], [reason_phrase] die Löhne sind im ganzen Königreich gestiegen. Eure eigenen Arbeiter könnten zu grüneren Weiden aufbrechen, wenn sie nicht so viel bezahlt werden wie ihre Pendants in anderen Städten." }
  { key: PHRASE_wage_change_reason_I_A, text: "weil die Löhne im ganzen Königreich gestiegen sind," }
  { key: PHRASE_wage_change_reason_I_B, text: "die Löhne sind im ganzen Königreich gestiegen, und" }
  { key: PHRASE_wage_change_reason_I_C, text: "obwohl die Löhne im ganzen Königreich gestiegen sind," }
  { key: PHRASE_wage_change_no_reason_I_A, text: "die Zeiten ändern sich, und nun" }
  { key: PHRASE_wage_change_no_reason_I_B, text: "einige jubeln, andere murren, denn" }
  { key: PHRASE_wage_change_no_reason_I_C, text: "" }
  { key: PHRASE_wage_change_title_D, text: "Löhne fallen" }
  { key: PHRASE_wage_change_initial_announcement_D, text: "[greeting] [player_name], [reason_phrase] die Löhne sind im ganzen Königreich Ägypten gefallen. Es scheint, überall werden Menschen für weniger arbeiten." }
  { key: PHRASE_wage_change_reason_D_A, text: "weil die Löhne gefallen sind," }
  { key: PHRASE_wage_change_reason_D_B, text: "die Löhne sind gefallen, und darüber hinaus," }
  { key: PHRASE_wage_change_reason_D_C, text: "obwohl die Löhne gefallen sind," }
  { key: PHRASE_wage_change_no_reason_D_A, text: "um zu versuchen, Kosten zu senken," }
  { key: PHRASE_wage_change_no_reason_D_B, text: "einige sind verärgert, aber Nomarchen jubeln, denn" }
  { key: PHRASE_wage_change_no_reason_D_C, text: "" }
  
  { key: PHRASE_bad_water_title, text: "Verseuchtes Wasser" }
  { key: PHRASE_bad_water_initial_announcement, text: "[greeting] [player_name], [reason_phrase] einige Eurer Bürger sind erkrankt, verursacht durch etwas im Wasser. Hofft nur, dass sich das Problem nicht verschlimmert." }
  { key: PHRASE_bad_water_reason_A, text: "wegen der jüngsten Wasserverseuchung," }
  { key: PHRASE_bad_water_reason_B, text: "die jüngste Wasserverseuchung war höchst unglücklich. Nun," }
  { key: PHRASE_bad_water_reason_C, text: "obwohl das Wasser kürzlich verseucht war," }
  { key: PHRASE_bad_water_no_reason_A, text: "Pech verfolgt die Stadt, und" }
  { key: PHRASE_bad_water_no_reason_B, text: ", dies ist in der Tat unglücklich. Es scheint" }
  { key: PHRASE_bad_water_no_reason_C, text: "" }
  
  { key: PHRASE_goldmine_cavein_title, text: "Goldmine stürzt ein" }
  { key: PHRASE_goldmine_cavein_initial_announcement, text: "[greeting] [player_name], [reason_phrase] eine Goldmine ist eingestürzt. Unsere Architekten waren machtlos, es zu verhindern. Hofft nur, dass die Arbeiter rechtzeitig aus der Mine herauskamen." }
  { key: PHRASE_goldmine_cavein_reason_A, text: "weil eine Goldmine eingestürzt ist," }
  { key: PHRASE_goldmine_cavein_reason_B, text: "der jüngste Einsturz der Goldmine war höchst unglücklich. Nun," }
  { key: PHRASE_goldmine_cavein_reason_C, text: "obwohl kürzlich eine Goldmine eingestürzt ist," }
  { key: PHRASE_goldmine_cavein_no_reason_A, text: "aufgrund sich verschiebender Sande," }
  { key: PHRASE_goldmine_cavein_no_reason_B, text: "ohne Vorwarnung," }
  { key: PHRASE_goldmine_cavein_no_reason_C, text: "" }
  
  { key: PHRASE_landslide_title, text: "Erdrutsch" }
  { key: PHRASE_landslide_initial_announcement, text: "[greeting] [player_name], [reason_phrase] ein schrecklicher Erdrutsch hat eine Handelsroute unterbrochen. Es könnten Monate vergehen, bis die Straße geräumt ist und Händler sich wieder auf den Weg machen." }
  { key: PHRASE_landslide_reason_A, text: "wegen des jüngsten Erdrutsches," }
  { key: PHRASE_landslide_reason_B, text: "die jüngsten Erdrutsche waren verheerend. Nun," }
  { key: PHRASE_landslide_reason_C, text: "obwohl es kürzlich schreckliche Erdrutsche gegeben hat," }
  { key: PHRASE_landslide_no_reason_A, text: "es gibt schreckliche Nachrichten:" }
  { key: PHRASE_landslide_no_reason_B, text: "ohne Vorwarnung" }
  { key: PHRASE_landslide_no_reason_C, text: "" }
  
  { key: PHRASE_flood_fails_title, text: "Flut wird wahrscheinlich ausbleiben" }
  { key: PHRASE_flood_fails_initial_announcement, text: "[greeting] [player_name], [reason_phrase] Priester bringen schlechte Nachrichten... sie fürchten, die nächste Überschwemmung wird mit ziemlicher Sicherheit ausbleiben! Konsultiert regelmäßig den Nilmesser... wenn sich die Vorhersage der Priester nicht verbessert, sollte die Stadt besser auf das Schlimmste vorbereitet sein." }
  { key: PHRASE_flood_fails_reason_A, text: "weil die Flut voraussichtlich ausbleiben wird" }
  { key: PHRASE_flood_fails_reason_B, text: "die Flut wird voraussichtlich ausbleiben, und" }
  { key: PHRASE_flood_fails_reason_C, text: "obwohl die Flut voraussichtlich ausbleiben sollte," }
  { key: PHRASE_flood_fails_no_reason_A, text: "aufgrund von Dürre in Afrika," }
  { key: PHRASE_flood_fails_no_reason_B, text: "unsere Schwierigkeiten haben gerade erst begonnen, denn" }
  { key: PHRASE_flood_fails_no_reason_C, text: "" }
  
  { key : PHRASE_perfect_flood_title, text: "Perfekte Flut erwartet" }
  { key : PHRASE_perfect_flood_initial_announcement, text: "[greeting] [player_name], [reason_phrase] dies ist in der Tat ein Segen, denn die Wahrscheinlichkeit einer ertragreichen Flut ist recht hoch! Konsultiert regelmäßig den Nilmesser. Sollte sich die Vorhersage verschlechtern, könnte die Stadt unvorbereitet dastehen." }
  { key : PHRASE_perfect_flood_reason_A, text: "weil die Flut als ertragreich erwartet wurde," }
  { key : PHRASE_perfect_flood_reason_B, text: "die Flut wurde als ertragreich erwartet, und" }
  { key : PHRASE_perfect_flood_reason_C, text: "obwohl die Flut als ertragreich erwartet wurde," }
  { key : PHRASE_perfect_flood_no_reason_A, text: "die Monsune in Afrika werden erwartet, daher" }
  { key : PHRASE_perfect_flood_no_reason_B, text: "wir haben wahrhaft Glück, denn" }
  { key : PHRASE_perfect_flood_no_reason_C, text: "" }
  
  { key: PHRASE_bedouin_attacks_you_title, text: "Beduinenarmee greift an" }
  { key: PHRASE_bedouin_attacks_you_initial_announcement, text: "[greeting] [player_name], [reason_phrase] eine Beduinenarmee nähert sich der Stadt und wird in [time_until_attack] Monaten angreifen." }
  { key: PHRASE_bedouin_attacks_you_2year_reminder, text: "[greeting] [player_name], [reason_phrase] eine Beduinenarmee rückt immer näher und wird die Stadt in zwei Jahren erreichen." }
  { key: PHRASE_bedouin_attacks_you_1year_reminder, text: "[greeting] [player_name], [reason_phrase] eine Beduinenarmee ist gut unterwegs und wird die Stadt in einem Jahr erreichen." }
  { key: PHRASE_bedouin_attacks_you_6month_warning, text: "[greeting] [player_name], [reason_phrase] eine Beduinenarmee ist bereit, Krieg zu führen und wird die Stadt in sechs Monaten erreichen." }
  { key: PHRASE_bedouin_attacks_you_1month_warning, text: "[greeting] [player_name], [reason_phrase] eine Beduinenarmee ist sehr nahe und wird die Stadt in einem Monat erreichen." }
  { key: PHRASE_bedouin_attacks_you_city_attacked_alert, text: "[greeting] [player_name], eine angreifende Beduinenarmee ist über uns!" }
  { key: PHRASE_bedouin_attacks_you_reason_A, text: "weil Eure Stadt die Beduinenarmee erfolgreich abgewehrt hat," }
  { key: PHRASE_bedouin_attacks_you_reason_B, text: "Eure Stadt hat die Beduinenarmee erfolgreich abgewehrt. Darüber hinaus," }
  { key: PHRASE_bedouin_attacks_you_reason_C, text: "obwohl Eure Stadt die Beduinenarmee erfolgreich abgewehrt hat," }
  { key: PHRASE_bedouin_attacks_you_no_reason_A, text: "um ihre Gier nach Reichtümern zu befriedigen," }
  { key: PHRASE_bedouin_attacks_you_no_reason_B, text: "unsere Schwierigkeiten sind groß, denn" }
  { key: PHRASE_bedouin_attacks_you_no_reason_C, text: "" }
  
  { key: PHRASE_gift_title_P, text: "Ein Geschenk von Pharao" }
  { key: PHRASE_gift_title_C, text: "Ein Geschenk von einem Nachbarn" }
  { key: PHRASE_gift_granted_P, text: "[greeting] [player_name], [reason_phrase] der Pharao hat verfügt, dass Ihr ein Geschenk von [amount] [item] aus [city_name] erhaltet." }
  { key: PHRASE_gift_granted_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] möchte Euch ein Geschenk von [amount] [item] gewähren." }
  { key: PHRASE_gift_cash_granted_P, text: "[greeting] [player_name], [reason_phrase] der Pharao hat verfügt, dass Ihr ein Geschenk von [amount] Deben aus [city_name] erhaltet." }
  { key: PHRASE_gift_cash_granted_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] möchte Euch ein Geschenk von [amount] Deben gewähren." }
  { key: PHRASE_gift_partial_space_P, text: "[greeting] [player_name], [reason_phrase] der Pharao hat verfügt, dass Ihr ein Geschenk von [amount] [item] aus [city_name] erhaltet. Ihr habt derzeit nicht genug Platz in Euren Lagerhöfen oder Getreidespeichern, um dieses Geschenk unterzubringen, aber Ihr könnt zumindest die Hälfte davon quetschen." }
  { key: PHRASE_gift_partial_space_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] möchte Euch ein Geschenk von [amount] [item] gewähren. Ihr habt derzeit nicht genug Platz in Euren Lagerhöfen oder Getreidespeichern, um dieses Geschenk unterzubringen, aber Ihr könnt zumindest die Hälfte davon quetschen." }
  { key: PHRASE_gift_insufficient_space_P, text: "[greeting] [player_name], [reason_phrase] Pharao hat verfügt, dass Ihr ein Geschenk von [amount] [item] aus [city_name] erhaltet, aber es gibt nicht genug Platz in Euren Lagerhöfen und Getreidespeichern. Schafft Platz und es wird nächsten Monat erneut geliefert." }
  { key: PHRASE_gift_insufficient_space_C, text: "[greeting] [player_name], [reason_phrase] die Stadt [city_name] möchte Euch ein Geschenk von [amount] [item] gewähren, aber es gibt unzureichenden Platz in Euren Lagerhöfen und Getreidespeichern, um es unterzubringen. Schafft Platz und es wird nächsten Monat erneut geliefert." }
  { key: PHRASE_gift_last_chance_P, text: "[greeting] [player_name], auf Befehl Pharaos hat die Stadt [city_name] versucht, Euch ein Geschenk von [amount] [item] zu gewähren, aber Ihr habt noch immer nicht ausreichend Platz in Euren Lagerhöfen und Getreidespeichern, um alles unterzubringen. Ihr habt seine Gesandten zu lange warten lassen, und sie sind ungeduldig geworden. Akzeptiert jetzt dieses teilweise Geschenk, denn sie werden nicht wieder zurückkehren." }
  { key: PHRASE_gift_last_chance_C, text: "[greeting] [player_name], die Stadt [city_name] hat versucht, Euch ein Geschenk von [amount] [item] zu gewähren, aber Ihr habt noch immer nicht ausreichend Platz in Euren Lagerhöfen und Getreidespeichern, um alles unterzubringen. Ihr habt ihre Gesandten zu lange warten lassen, und sie sind ungeduldig geworden. Akzeptiert jetzt dieses teilweise Geschenk, denn sie werden nicht wieder zurückkehren." }
  { key: PHRASE_gift_forfeited_P, text: "[greeting] [player_name], es gibt noch immer unzureichenden Platz für Euch, um das Geschenk von [amount] [item] aus [city_name] zu empfangen, und daher ist es verfallen." }
  { key: PHRASE_gift_forfeited_C, text: "[greeting] [player_name], es gibt noch immer unzureichenden Platz für Euch, um das Geschenk von [amount] [item] aus [city_name] zu empfangen, und daher ist es verfallen." }
  { key: PHRASE_gift_accepted_P, text: "Auf Befehl des Pharaos wurden die Lagerhöfe und Getreidespeicher Eurer Stadt mit so vielen [item] aus [city_name] gefüllt, wie sie aufnehmen können." }
  { key: PHRASE_gift_accepted_C, text: "Die Lagerhöfe und Getreidespeicher Eurer Stadt wurden mit so vielen [item] aus [city_name] gefüllt, wie sie aufnehmen können." }
  { key: PHRASE_gift_cash_accepted_P, text: "Auf Befehl des Pharaos wurden [amount_granted] Deben zu Eurer Schatzkammer hinzugefügt." }
  { key: PHRASE_gift_cash_accepted_C, text: "Dank [city_name] wurden [amount_granted] Deben zu Eurer Schatzkammer hinzugefügt." }
  { key: PHRASE_gift_postponed_P, text: "Gesandte aus [city_name] werden in einem Monat mit Eurer Lieferung von [item] zurückkehren." }
  { key: PHRASE_gift_postponed_C, text: "Gesandte aus [city_name] werden in einem Monat mit Eurer Lieferung von [item] zurückkehren." }
  { key: PHRASE_gift_refused_P, text: "Obwohl Ihr dieses Geschenk von [item] aus [city_name] abgelehnt habt, bin ich sicher, jemand anderes könnte unsere Hilfe gebrauchen." }
  { key: PHRASE_gift_refused_C, text: "Obwohl Ihr dieses Geschenk von [item] aus [city_name] abgelehnt habt, bin ich sicher, jemand anderes könnte unsere Hilfe gebrauchen." }
  { key: PHRASE_gift_accepted_reason_P_A, text: "weil Ihr ein Geschenk von [amount] [item] aus [city_name] angenommen habt" }
  { key: PHRASE_gift_accepted_reason_P_B, text: "im Zuge Eures kürzlichen Geschenks aus [city_name]," }
  { key: PHRASE_gift_accepted_reason_P_C, text: "obwohl Ihr das Geschenk von [amount] [item] aus [city_name] angenommen habt," }
  { key: PHRASE_gift_accepted_reason_C_A, text: "weil Ihr ein Geschenk von [amount] [item] aus [city_name] angenommen habt" }
  { key: PHRASE_gift_accepted_reason_C_B, text: "im Zuge Eures kürzlichen Geschenks aus [city_name]," }
  { key: PHRASE_gift_accepted_reason_C_C, text: "obwohl Ihr das Geschenk von [amount] [item] aus [city_name] angenommen habt," }
  { key: PHRASE_gift_forfeited_reason_P_A, text: "weil Ihr ein Geschenk von [amount] [item] aus [city_name] nicht angenommen habt" }
  { key: PHRASE_gift_forfeited_reason_P_B, text: "Ihr habt ein Geschenk von [amount] [item] aus [city_name] nicht angenommen. Außerdem," }
  { key: PHRASE_gift_forfeited_reason_P_C, text: "obwohl Ihr das Geschenk von [amount] [item] aus [city_name] nicht angenommen habt" }
  { key: PHRASE_gift_forfeited_reason_C_A, text: "weil Ihr das Geschenk von [amount] [item] aus [city_name] nicht angenommen habt" }
  { key: PHRASE_gift_forfeited_reason_C_B, text: "Ihr habt das Geschenk von [amount] [item] aus [city_name] nicht angenommen. Außerdem," }
  { key: PHRASE_gift_forfeited_reason_C_C, text: "obwohl Ihr das Geschenk von [amount] [item] aus [city_name] nicht angenommen habt" }
  { key: PHRASE_gift_refused_reason_P_A, text: "weil Ihr ein Geschenk von [amount] [item] aus [city_name] abgelehnt habt" }
  { key: PHRASE_gift_refused_reason_P_B, text: "Ihr habt ein Geschenk von [amount] [item] aus [city_name] abgelehnt. Nun," }
  { key: PHRASE_gift_refused_reason_P_C, text: "obwohl Ihr ein Geschenk von [amount] [item] aus [city_name] abgelehnt habt," }
  { key: PHRASE_gift_refused_reason_C_A, text: "weil Ihr ein Geschenk von [amount] [item] aus [city_name] abgelehnt habt" }
  { key: PHRASE_gift_refused_reason_C_B, text: "Ihr habt ein Geschenk von [amount] [item] aus [city_name] abgelehnt. Nun," }
  { key: PHRASE_gift_refused_reason_C_C, text: "obwohl Ihr ein Geschenk von [amount] [item] aus [city_name] abgelehnt habt," }
  { key: PHRASE_gift_no_reason_P_A, text: "weil Ihr etwas Hilfe gebrauchen könntet" }
  { key: PHRASE_gift_no_reason_P_B, text: "weil Pharaos Wohlwollen grenzenlos ist," }
  { key: PHRASE_gift_no_reason_P_C, text: "die Opfer Eurer Stadt im Kampf werden von Pharao sehr geschätzt. Infolgedessen" }
  { key: PHRASE_gift_no_reason_C_A, text: "weil Ihr etwas Hilfe gebrauchen könntet" }
  { key: PHRASE_gift_no_reason_C_B, text: "weil Ägypter ihren Landsleuten immer helfen," }
  { key: PHRASE_gift_no_reason_C_C, text: "die Opfer Eurer Stadt im Kampf werden vom ägyptischen Volk sehr geschätzt. Infolgedessen" }
  
  { key: PHRASE_pharaoh_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] Pharaos Armee ist angekommen, um Eure Stadt mit Gewalt einzunehmen." }
  { key: PHRASE_eg_city_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] eine ägyptische Armee ist gelandet und fällt gerade in die Stadt ein!" }
  { key: PHRASE_foreign_army_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] [a_foreign_army] ist gelandet und greift sogar jetzt die Stadt an! Möge Seth uns erretten." }
  { key: PHRASE_bedouin_attacks_you_disembarked_alert, text: "[greeting] [player_name], [reason_phrase] eine feindliche Beduinen-Invasionstruppe ist an unseren Küsten gelandet!" }
  
  { key: PHRASE_pyramid_congratulations_title, text: "Pyramide fertiggestellt!" }
  { key: PHRASE_pyramid_congratulations, text: "[greeting] [player_name], dies ist eine spektakuläre Leistung! Nach unzähligen Monaten Arbeit ist die Pyramide endlich vollendet!" }
  { key: PHRASE_stepped_pyramid_congratulations_title, text: "Stufenpyramide fertiggestellt!" }
  { key: PHRASE_stepped_pyramid_congratulations, text: "[greeting] [player_name], endlich ist die Stufenpyramide vollendet! Dieses Monument wird für immer als Zeugnis Eurer Fähigkeiten stehen." }
  { key: PHRASE_bent_pyramid_congratulations_title, text: "Knickpyramide fertiggestellt!" }
  { key: PHRASE_bent_pyramid_congratulations, text: "[greeting] [player_name], der Bau der Knickpyramide ist endlich abgeschlossen! Dies ist eine gewaltige Leistung für Eure Stadt." }
  { key: PHRASE_mudbrick_pyramid_congratulations_title, text: "Ziegelpyramide fertiggestellt!" }
  { key: PHRASE_mudbrick_pyramid_congratulations, text: "[greeting] [player_name], Steinmetze haben ihre letzten Feinarbeiten an der glänzenden Außenverkleidung aus feinem Kalkstein vollendet, und die Ziegelpyramide ist endlich fertig!" }
  { key: PHRASE_mastaba_congratulations_title, text: "Mastaba fertiggestellt!" }
  { key: PHRASE_mastaba_congratulations, text: "[greeting] [player_name], der letzte Ziegel wurde an seinen Platz gelegt, und die Arbeit an der Mastaba ist nun abgeschlossen!" }
  { key: PHRASE_sphinx_congratulations_title, text: "Sphinx fertiggestellt!" }
  { key: PHRASE_sphinx_congratulations, text: "[greeting] [player_name], endlich haben die Steinmetze die mächtige Sphinx fertig gemeißelt. Dieses Monument wird über Ägypten für alle Zeitalter wachen." }
  { key: PHRASE_obelisk_congratulations_title, text: "Obelisk fertiggestellt!" }
  { key: PHRASE_obelisk_congratulations, text: "[greeting] [player_name], Steinmetze haben ihre letzten Feinarbeiten am Obelisken angebracht, und endlich ist er vollendet." }
  { key: PHRASE_sun_temple_congratulations_title, text: "Sonnentempel fertiggestellt!" }
  { key: PHRASE_sun_temple_congratulations, text: "[greeting] [player_name], nach vielen Monaten Mühe ist die Arbeit am Sonnentempel endlich abgeschlossen. Dies ist eine großartige Leistung für Eure Stadt!" }
  { key: PHRASE_alex_library_congratulations_title, text: "Bibliothek von Alexandria fertiggestellt!" }
  { key: PHRASE_alex_library_congratulations, text: "[greeting] [player_name], nach viel harter Arbeit sind die wunderschön handgefertigten Türen der prächtigen Großen Bibliothek von Alexandria bereit, weit für die Gelehrten der Welt geöffnet zu werden." }
  { key: PHRASE_abu_simbel_congratulations_title, text: "Abu Simbel fertiggestellt!" }
  { key: PHRASE_abu_simbel_congratulations, text: "[greeting] [player_name], dies ist eine wahrhaft spektakuläre Leistung! Eure qualifizierten Arbeiter haben ein ewiges Monument geschaffen, das von der Herrlichkeit unseres Pharaos und der Macht Ägyptens kündet." }
  { key: PHRASE_caesareum_congratulations_title, text: "Caesareum fertiggestellt!" }
  { key: PHRASE_caesareum_congratulations, text: "[greeting] [player_name], der heilige Tempel und die prächtigen Gartenhöfe des Caesareums sind endlich vollendet! Die Kunde seiner herrlichen Schönheit verbreitet sich bereits in der ganzen Region." }
  { key: PHRASE_lighthouse_congratulations_title, text: "Pharos-Leuchtturm fertiggestellt!" }
  { key: PHRASE_lighthouse_congratulations, text: "[greeting] [player_name], nach viel Schweiß und nicht wenig vergossenem Blut haben Arbeiter sorgfältig den letzten Marmorblock für den wunderbaren Pharos-Leuchtturm platziert! Schon jetzt zieht sein hoch aufragendes helles Leuchtfeuer Händler von überall her an." }
  { key: PHRASE_mausoleum_congratulations_title, text: "Mausoleum fertiggestellt!" }
  { key: PHRASE_mausoleum_congratulations, text: "[greeting] [player_name], das heilige Mausoleum ist endlich vollendet! Dies ist eine bemerkenswerte Leistung für Eure Stadt." }
  { key: PHRASE_smalltomb_congratulations_title, text: "Kleines Grabmal fertiggestellt!" }
  { key: PHRASE_smalltomb_congratulations, text: "[greeting] [player_name], der Bau des kleinen königlichen Grabmals ist abgeschlossen. Hoffentlich werden es viele Jahre sein, bis Eure Arbeiter ein weiteres vorbereiten müssen." }
  { key: PHRASE_medtomb_congratulations_title, text: "Mittleres Grabmal fertiggestellt!" }
  { key: PHRASE_medtomb_congratulations, text: "[greeting] [player_name], endlich ist das mittlere königliche Grabmal fertig und vollständig mit Vorräten bestückt. Es wird mit Sicherheit einen idealen Übergang ins Jenseits für unseren kürzlich verstorbenen Pharao bieten." }
  { key: PHRASE_largetomb_congratulations_title, text: "Großes Grabmal fertiggestellt!" }
  { key: PHRASE_largetomb_congratulations, text: "[greeting] [player_name], nach vielen Jahren harter Arbeit in den Tiefen der Erde haben Eure Arbeiter die Arbeit am prächtigsten Grabmal bis heute vollendet! Es ist wahrhaft eine wunderbare Leistung." }
  { key: PHRASE_grandtomb_congratulations_title, text: "Großartiges Grabmal fertiggestellt!" }
  { key: PHRASE_grandtomb_congratulations, text: "[greeting] [player_name], nach viel anstrengender Arbeit ist das großartige königliche Grabmal vollendet - und keine Sekunde zu früh, da unser verehrter Pharao nach manchen Berichten auf seinen letzten Beinen ist. Dieses prächtige Grabmal ist perfekt, um seine bevorstehende Reise ins Jenseits zu fördern." }
  
  { key: PHRASE_troopcarryover_title, text: "Treue Soldaten schließen sich Euch wieder an" }
  { key: PHRASE_troopcarryover_initial_announcement, text: "Eure besten Soldaten aus der vorherigen Mission möchten sich Euch wieder anschließen. Baut [reason_phrase] für diese Krieger und sie werden zurückkehren." }
  { key: PHRASE_troopcarryover_inf_only, text: "ein Infanteriefort" }
  { key: PHRASE_troopcarryover_arch_only, text: "ein Bogenschützenfort" }
  { key: PHRASE_troopcarryover_char_only, text: "ein Streitwagenfort" }
  { key: PHRASE_troopcarryover_inf_arch, text: "Infanterie- und Bogenschützenforts" }
  { key: PHRASE_troopcarryover_inf_char, text: "Infanterie- und Streitwagenforts" }
  { key: PHRASE_troopcarryover_arch_char, text: "Bogenschützen- und Streitwagenforts" }
  { key: PHRASE_troopcarryover_all_three, text: "Infanterie-, Bogenschützen- und Streitwagenforts" }
  { key: PHRASE_pyramid_speedup_title, text: "Ein Bausegen" }
  { key: PHRASE_pyramid_speedup_announcement, text: "[reason_phrase] ist erfreut über Eure Hingabe und möchte Eurem Monument-Bauprojekt einen großen Schub geben. Es ist Zeit für Eure Arbeiter, vorübergehend zur Seite zu treten, während dieser reichliche Segen vom verehrten [reason_phrase] empfangen wird." }
  { key: PHRASE_pyramid_minor_speedup_announcement, text: "[reason_phrase] würdigt Eure Anbetung, indem er Eurem Monument-Bauprojekt hilft. Es ist Zeit für Eure Arbeiter, eine kurze Pause zu nehmen, während dieses wohlwollende Geschenk von [reason_phrase] eintrifft." }
  { key: PHRASE_pyramid_speedup_Osiris, text: "Osiris" }
  { key: PHRASE_pyramid_speedup_Ra, text: "Ra" }
  { key: PHRASE_pyramid_speedup_Ptah, text: "Ptah" }
  { key: PHRASE_pyramid_speedup_Seth, text: "Seth" }
  { key: PHRASE_pyramid_speedup_Bast, text: "Bast" }
]
