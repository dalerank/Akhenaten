log_info("akhenaten: localization_de config started")

localization_base_de = [
    { group:1, id:0, text: "Datei" }
    { group:1, id:1, text: "Neues Spiel" }
    { group:1, id:2, text: "Mission wiederholen" }
    { group:1, id:3, text: "Spiel laden" }
    { group:1, id:4, text: "Spiel speichern" }
    { group:1, id:5, text: "Spiel beenden" }
    { group:1, id:6, text: "Spiel löschen" }
    { group:2, id:0, text: "Optionen" }
    { group:2, id:1, text: "Anzeigeeinstellungen" }
    { group:2, id:2, text: "Toneinstellungen" }
    { group:2, id:3, text: "Geschwindigkeitseinstellungen" }
    { group:2, id:4, text: "Pyramiden-Beschleunigung - AUS" }
    { group:2, id:5, text: "Pyramiden-Beschleunigung - AN" }
    { group:2, id:6, text: "Schwierigkeitsgrad" }
    { group:2, id:7, text: "Städte - Ägyptisch" }
    { group:2, id:8, text: "Städte - Klassisch" }
    { group:2, id:9, text: "Autospeichern - AN" }
    { group:2, id:10, text: "Autospeichern - AUS" }
    { group:2, id:11, text: "Popup-Nachrichten" }
    { group:3, id:0, text: "Hilfe" }
    { group:3, id:1, text: "Hilfe" }
    { group:3, id:2, text: "Maushilfe - AUS" }
    { group:3, id:3, text: "Maushilfe - ETWAS" }
    { group:3, id:4, text: "Maushilfe - VOLL" }
    { group:3, id:5, text: "Warnungen - AUS" }
    { group:3, id:6, text: "Warnungen - AN" }
    { group:3, id:7, text: "Über" }
    { group:3, id:8, text: "Missions-Editor Anleitung" }
    { group:4, id:0, text: "Aufseher" }
    { group:4, id:1, text: "Aufseher der Arbeiter" }
    { group:4, id:2, text: "Aufseher des Militärs" }
    { group:4, id:3, text: "Politischer Aufseher" }
    { group:4, id:4, text: "Bewertungsaufseher" }
    { group:4, id:5, text: "Aufseher des Handels" }
    { group:4, id:6, text: "Aufseher der Getreidespeicher" }
    { group:4, id:7, text: "Aufseher der öffentlichen Gesundheit" }
    { group:4, id:8, text: "Aufseher der Bildung" }
    { group:4, id:9, text: "Aufseher der Unterhaltung" }
    { group:4, id:10, text: "Aufseher der Tempel" }
    { group:4, id:11, text: "Aufseher der Schatzkammer" }
    { group:4, id:12, text: "Oberaufseher" }
    { group:4, id:13, text: "Aufseher der Monumente" }
    { group:5, id:0, text: "Beenden" }
    { group:5, id:1, text: "Das Königreich verlassen?" }
    { group:5, id:2, text: "Handelsroute öffnen" }
    { group:5, id:3, text: "Für diese Landhandelsroute bezahlen?" }
    { group:5, id:4, text: "Handelsroute öffnen" }
    { group:5, id:5, text: "Für diese Wasserhandelsroute bezahlen?" }
    { group:5, id:6, text: "Pharaonische Anfrage" }
    { group:5, id:7, text: "Waren versenden?" }
    { group:5, id:8, text: "Pharaonische Anfrage" }
    { group:5, id:9, text: "Ihr habt nicht genug, um die Anfrage zu erfüllen" }
    { group:5, id:10, text: "Pharaonische Anfrage" }
    { group:5, id:11, text: "Ihr habt keine Kompanien zum Entsenden" }
    { group:5, id:12, text: "Pharaonische Anfrage" }
    { group:5, id:13, text: "Weist Euren Aufseher des Militärs an, einige einsatzbereite Kompanien dem Königreich zuzuweisen" }
    { group:5, id:14, text: "Pharaonische Anfrage" }
    { group:5, id:15, text: "Hilfstruppen entsenden?" }
    { group:5, id:16, text: "Abriss eines Forts" }
    { group:5, id:17, text: "Seid Ihr sicher, dass Ihr dieses Fort außer Dienst stellen wollt?" }
    { group:5, id:18, text: "CD fehlt" }
    { group:5, id:19, text: "Bitte legt Eure Cleopatra-CD ins CD-ROM-Laufwerk ein" }
    { group:5, id:20, text: "Abriss einer Brücke" }
    { group:5, id:21, text: "Reißt Brücken mit Bedacht ab. Isolierte Gemeinden gehen bald zugrunde, wenn sie vom Königreichsweg abgeschnitten sind." }
    { group:5, id:22, text: "Beenden" }
    { group:5, id:23, text: "Beenden ohne zu speichern?" }
    { group:5, id:24, text: "Alte Version" }
    { group:5, id:25, text: "Diese Datei ist eine alte Version und kann nicht geladen werden" }
    { group:5, id:26, text: "Zu viele Grabbeigaben!" }
    { group:5, id:27, text: "Ihr könnt nicht mehr als 5 Grabbeigaben für dieses Szenario haben!" }
    { group:5, id:28, text: "Warnung!" }
    { group:5, id:29, text: "Diese Grabbeigabe ist in diesem Szenario nicht verfügbar!" }
    { group:5, id:30, text: "Nicht genug Waren!" }
    { group:5, id:31, text: "Ihr habt nicht genug Waren dieses Typs auf Lager!" }
    { group:5, id:32, text: "Abgeschlossen!" }
    { group:5, id:33, text: "Ihr benötigt keine weiteren Grabbeigaben für diese Ware!" }
    { group:5, id:34, text: "Max. Städte" }
    { group:5, id:35, text: "Die maximale Anzahl an Städten wurde erreicht" }
    { group:5, id:36, text: "Transport benötigt" }
    { group:5, id:37, text: "Diese Truppen müssen ein Transportschiff besteigen, um dem Königreich im aktuellen Konflikt zu dienen." }
    { group:5, id:38, text: "Landtruppen benötigt" }
    { group:5, id:39, text: "Nur auf dem Landweg reisende Truppen werden benötigt, um dem Königreich im aktuellen Konflikt zu dienen." }
    { group:5, id:40, text: "Keine Truppen benötigt" }
    { group:5, id:41, text: "Es gibt keine Anfragen für Truppen, weder auf dem Land- noch auf dem Seeweg" }
    { group:5, id:42, text: "Truppen im Königreich" }
    { group:5, id:43, text: "Diese Truppen sind nicht in der Stadt" }
    { group:5, id:44, text: "Kriegsschiff im Königreich" }
    { group:5, id:45, text: "Dieses Kriegsschiff ist nicht in der Stadt" }
    { group:5, id:46, text: "Preis kann nicht geändert werden!" }
    { group:5, id:47, text: "Diese Ware ist in diesem Szenario nicht verfügbar!" }
    { group:5, id:48, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:49, text: "Die Stadt kann kein Leinen produzieren oder importieren." }
    { group:5, id:50, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:51, text: "Die Stadt kann kein Bier produzieren oder importieren." }
    { group:5, id:52, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:53, text: "Die Stadt kann keinen Papyrus produzieren oder importieren." }
    { group:5, id:54, text: "Leichenhallen können nicht arbeiten." }
    { group:5, id:55, text: "Die Stadt kann kein Leinen produzieren oder importieren. Leichenhallen wurden entfernt." }
    { group:5, id:56, text: "Senet-Haus kann nicht arbeiten." }
    { group:5, id:57, text: "Die Stadt kann kein Bier produzieren oder importieren. Senet-Häuser wurden entfernt." }
    { group:5, id:58, text: "Schreiberschulen können nicht arbeiten." }
    { group:5, id:59, text: "Die Stadt kann keinen Papyrus produzieren oder importieren. Schreiberschulen wurden entfernt." }
    { group:5, id:60, text: "Bibliotheken können nicht arbeiten." }
    { group:5, id:61, text: "Die Stadt kann keinen Papyrus produzieren oder importieren. Bibliotheken wurden entfernt." }
    { group:5, id:62, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:63, text: "Die Stadt kann kein Kupfer produzieren oder importieren." }
    { group:5, id:64, text: "Waffenschmiede können nicht arbeiten." }
    { group:5, id:65, text: "Die Stadt kann kein Kupfer produzieren oder importieren. Waffenschmiede wurden entfernt." }
    { group:5, id:66, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:67, text: "Die Stadt kann kein Holz produzieren oder importieren." }
    { group:5, id:68, text: "Wagenbauer können nicht arbeiten." }
    { group:5, id:69, text: "Die Stadt kann kein Holz produzieren oder importieren. Wagenbauer wurden entfernt." }
    { group:5, id:70, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:71, text: "Diese Stadt hat keinen Rekrutierer." }
    { group:5, id:72, text: "Fort: Infanterie kann nicht arbeiten." }
    { group:5, id:73, text: "Diese Stadt hat keinen Rekrutierer. Fort: Infanterie wurde entfernt." }
    { group:5, id:74, text: "Fort: Bogenschützen kann nicht arbeiten." }
    { group:5, id:75, text: "Diese Stadt hat keinen Rekrutierer. Fort: Bogenschützen wurde entfernt." }
    { group:5, id:76, text: "Fort: Streitwagenkämpfer kann nicht arbeiten." }
    { group:5, id:77, text: "Diese Stadt hat keinen Rekrutierer. Fort: Streitwagenkämpfer wurde entfernt." }
    { group:5, id:78, text: "Akademien können nicht arbeiten." }
    { group:5, id:79, text: "Diese Stadt hat keinen Rekrutierer. Akademien wurden entfernt." }
    { group:5, id:80, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:81, text: "Die Stadt kann keine Waffen produzieren oder importieren." }
    { group:5, id:82, text: "Dieses Gebäude kann nicht arbeiten." }
    { group:5, id:83, text: "Die Stadt kann keine Streitwagen produzieren oder importieren." }
    { group:5, id:84, text: "Fort: Infanterie kann nicht arbeiten." }
    { group:5, id:85, text: "Diese Stadt hat keine Waffenschmiede. Fort: Infanterie wurde entfernt." }
    { group:5, id:86, text: "Fort: Streitwagenkämpfer kann nicht arbeiten." }
    { group:5, id:87, text: "Diese Stadt hat keinen Wagenbauer. Fort: Streitwagenkämpfer wurde entfernt." }
    { group:5, id:88, text: "Fest: Kein Festplatz." }
    { group:5, id:89, text: "Ihr benötigt einen Festplatz, um ein Fest abzuhalten." }
    { group:5, id:90, text: "Dynastie löschen?" }
    { group:5, id:91, text: "Dies löscht die gewählte Dynastie und alle ihre gespeicherten Spiele. Wollt Ihr das wirklich tun?" }
    { group:5, id:92, text: "Dynastie existiert" }
    { group:5, id:93, text: "Dieser Name wird bereits verwendet. Wählt einen anderen Namen." }
    { group:5, id:94, text: "Keine Dynastie" }
    { group:5, id:95, text: "Ihr müsst eine Dynastie auswählen" }
    { group:5, id:96, text: "Warnung" }
    { group:5, id:97, text: "Ihr habt nicht genug Deben, um ein Fest abzuhalten." }
    { group:5, id:98, text: "Pharaonische Anfrage" }
    { group:5, id:99, text: "Ihr habt keine wassergebundenen Kompanien zum Entsenden." }
    { group:5, id:100, text: "Pharaonische Anfrage" }
    { group:5, id:101, text: "Weist Euren Aufseher des Militärs an, einige einsatzbereite wassergebundene Kompanien dem Königreich zuzuweisen" }
    { group:5, id:102, text: "Truppen entsenden" }
    { group:5, id:103, text: "Mehrere Ziele sind für die ausgewählten Streitkräfte möglich. Weist Euren politischen Aufseher an, wohin diese Truppen entsandt werden sollen." }
    { group:5, id:104, text: "Abriss eines Monuments" }
    { group:5, id:105, text: "Seid Ihr sicher, dass Ihr dieses Monument abreißen wollt?" }
    { group:5, id:106, text: "Abriss eines Tempelkomplexes" }
    { group:5, id:107, text: "Sollen wir diesen Tempelkomplex wirklich abreißen?" }
    { group:5, id:108, text: "Kann nicht speichern" }
    { group:5, id:109, text: "Beute-/Raubtier-Punkte an ungültigen Orten." }
    { group:5, id:110, text: "Datei existiert" }
    { group:5, id:111, text: "Existierende Datei überschreiben?" }
    { group:5, id:112, text: "Keine Verkäufer" }
    { group:5, id:113, text: "Es gibt derzeit keine Städte, die diese Ware verkaufen möchten." }
    { group:5, id:114, text: "Keine Käufer" }
    { group:5, id:115, text: "Es gibt derzeit keine Städte, die diese Ware kaufen möchten." }
    { group:5, id:116, text: "Keine offene Handelsroute" }
    { group:5, id:117, text: "Besucht die Weltkarte, um eine Handelsroute zum Export dieser Ware zu öffnen." }
    { group:5, id:118, text: "Besucht die Weltkarte, um eine Handelsroute zum Import dieser Ware zu öffnen." }
    { group:5, id:119, text: "Warnung" }
    { group:5, id:120, text: "Ihr habt nicht genug Deben, um eine Handelsroute zu öffnen." }
    { group:5, id:121, text: "Kann nicht speichern" }
    { group:5, id:122, text: "Zu viele Nahrungsmittelarten (max. 4)." }
    { group:5, id:123, text: "Weltkarte kann nicht bearbeitet werden" }
    { group:5, id:124, text: "Die Bearbeitung der Weltkarte erfordert eine Bildschirmauflösung von 800x600 oder höher." }
    { group:5, id:125, text: "Weltkarte kann nicht verlassen werden" }
    { group:5, id:126, text: "Zu viele Nahrungsmittelarten (max. 4)." }
    { group:5, id:127, text: "Kann nicht speichern" }
    { group:5, id:128, text: "Einige Fischereipunkte befinden sich an ungültigen Orten." }
    { group:5, id:129, text: "Kann nicht speichern" }
    { group:5, id:130, text: "Eingangs-/Ausgangspunkte an ungültigen Orten." }
    { group:5, id:131, text: "Kann nicht speichern" }
    { group:5, id:132, text: "Flusseingangs-/Flussausgangspunkte an ungültigen Orten." }
    { group:5, id:133, text: "Kann nicht speichern" }
    { group:5, id:134, text: "Einige Invasionspunkte (Land) befinden sich an ungültigen Orten." }
    { group:5, id:135, text: "Kann nicht speichern" }
    { group:5, id:136, text: "Einige Invasionspunkte (Wasser) befinden sich an ungültigen Orten." }
    { group:5, id:137, text: "Pharao" }
    { group:5, id:138, text: "Bitte legt Eure Cleopatra-CD ein." }
    { group:5, id:139, text: "Zoo kann nicht arbeiten." }
    { group:5, id:140, text: "Die Stadt kann weder Wildfleisch noch Stroh produzieren oder importieren. Zoo wurde entfernt." }
    { group:5, id:141, text: "Keine von der Familie gewonnenen Missionen" }
    { group:5, id:142, text: "Bitte 'Familiengeschichte beginnen', wenn Ihr neu bei Pharao seid. Fortfahren und Mission wählen?" }
    { group:6, id:0, text: "Db" }
    { group:6, id:1, text: "Bev" }
    { group:6, id:2, text: "Monate bis Missionsende" }
    { group:6, id:3, text: "Monate bis zum Sieg" }
    { group:6, id:4, text: "Überlagerungen" }
    { group:6, id:5, text: "Ihr habt diese Mission bereits gewonnen und habt euch entschieden, weiter zu regieren" }
    { group:6, id:6, text: "Platziert Gräber über Klippen und stellt sicher, dass der Eingang auf freiem Land herausragt" }
    { group:7, id:0, text: "Datei" }
    { group:7, id:1, text: "Neue Karte" }
    { group:7, id:2, text: "Karte laden" }
    { group:7, id:3, text: "Karte speichern" }
    { group:7, id:4, text: "Editor beenden" }
    { group:8, id:0, text: "Deben" }
    { group:8, id:1, text: "Deben" }
    { group:8, id:2, text: "Person" }
    { group:8, id:3, text: "Personen" }
    { group:8, id:4, text: "Monat" }
    { group:8, id:5, text: "Monate" }
    { group:8, id:6, text: "Getreidespeicher enthält" }
    { group:8, id:7, text: "Getreidespeicher enthalten" }
    { group:8, id:8, text: "Jahr" }
    { group:8, id:9, text: "Jahre" }
    { group:8, id:10, text: "Einheit" }
    { group:8, id:11, text: "Einheiten" }
    { group:8, id:12, text: "Angestellter" }
    { group:8, id:13, text: "Angestellte" }
    { group:8, id:14, text: "weitere Person" }
    { group:8, id:15, text: "weitere Personen" }
    { group:8, id:16, text: "Einheit." }
    { group:8, id:17, text: "Einheiten." }
    { group:8, id:18, text: "Schreiberschule" }
    { group:8, id:19, text: "Schreiberschulen" }
    { group:8, id:20, text: "Akademie" }
    { group:8, id:21, text: "Akademien" }
    { group:8, id:22, text: "Bibliothek" }
    { group:8, id:23, text: "Bibliotheken" }
    { group:8, id:24, text: "Arzt" }
    { group:8, id:25, text: "Ärzte" }
    { group:8, id:26, text: "Zahnarzt" }
    { group:8, id:27, text: "Zahnärzte" }
    { group:8, id:28, text: "Apotheke" }
    { group:8, id:29, text: "Apotheken" }
    { group:8, id:30, text: "Leichenhalle" }
    { group:8, id:31, text: "Leichenhallen" }
    { group:8, id:32, text: "Orakel" }
    { group:8, id:33, text: "Orakel" }
    { group:8, id:34, text: "Bude" }
    { group:8, id:35, text: "Buden" }
    { group:8, id:36, text: "Musikpavillon" }
    { group:8, id:37, text: "Musikpavillons" }
    { group:8, id:38, text: "Bühne" }
    { group:8, id:39, text: "Bühnen" }
    { group:8, id:40, text: "Senet-Spiel" }
    { group:8, id:41, text: "Senet-Spiele" }
    { group:8, id:42, text: "Nachricht" }
    { group:8, id:43, text: "Nachrichten" }
    { group:8, id:44, text: "Tag" }
    { group:8, id:45, text: "Tage" }
    { group:8, id:46, text: "Soldat" }
    { group:8, id:47, text: "Soldaten" }
    { group:8, id:48, text: "Kompanie" }
    { group:8, id:49, text: "Kompanien" }
    { group:8, id:50, text: "Kriegsschiff" }
    { group:8, id:51, text: "Kriegsschiffe" }
    { group:8, id:52, text: "Leichenhalle" }
    { group:8, id:53, text: "Leichenhallen" }
    { group:8, id:54, text: "Ladung" }
    { group:8, id:55, text: "Ladungen" }
    { group:8, id:56, text: "Block" }
    { group:8, id:57, text: "Blöcke" }
    { group:8, id:58, text: "Transport" }
    { group:8, id:59, text: "Transporte" }
    { group:9, id:0, text: "Pharao (Cleopatra Erweiterung)" }
    { group:9, id:1, text: "Version 2.1" }
    { group:9, id:2, text: "Copyright 1999-2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Beta-Release für: BreakAway Games Tester" }
    { group:9, id:4, text: "test1 string" }
    { group:9, id:5, text: "Euer Name hier" }
    { group:9, id:6, text: "Meine ägyptische Stadt" }
    { group:9, id:7, text: "Szenario1" }
    { group:9, id:8, text: "Pharao Aufgaben-Editor" }
    { group:9, id:9, text: "Pharao Demo" }
    { group:10, id:0, text: "Zurücksetzen" }
    { group:10, id:1, text: "Killer-Pkt. löschen" }
    { group:10, id:2, text: "Fische löschen" }
    { group:10, id:3, text: "Invasionen löschen" }
    { group:10, id:4, text: "Ausschiffer-Pkt. löschen" }
    { group:10, id:5, text: "Beute-Pkt. löschen" }
    { group:10, id:6, text: "Aus BMP laden" }
    { group:10, id:7, text: "Als BMP speichern" }
    { group:10, id:8, text: "Königreich bearbeiten" }
    { group:10, id:9, text: "Königreich speichern" }
    { group:10, id:10, text: "Karte aktualisieren" }
    { group:11, id:0, text: "Einrichtung ..." }
    { group:11, id:1, text: "test_string €,Њ,њ,Ў,°,ї,A,А,Б,В,Д, E,И,Й,К,I,М,Н,О,П,N,С,O,Т,У,Ф,Ц, U,Щ,Ъ,Ы,Ь,Я,a,а,б,в,д,c,з, e,и,й,к,i,м,н,о,п,n,с,o,т,у,ф,ц,u,щ,ъ,ы,ь,..." }
    { group:11, id:2, text: "Laden ..." }
    { group:11, id:3, text: "Daten vorbereiten ..." }
    { group:11, id:4, text: "Töne laden ..." }
    { group:11, id:5, text: "Beschleunigte Zeit" }
    { group:11, id:6, text: "Rechtsklick zum Fortfahren" }
    { group:11, id:7, text: "Hintergründe laden ..." }
    { group:11, id:8, text: "Animationen laden ..." }
    { group:11, id:9, text: "Monumente laden ..." }
    { group:11, id:10, text: "Feinde laden ..." }
    { group:11, id:11, text: "Einstellungen laden ..." }
    { group:12, id:0, text: "Zurück" }
    { group:12, id:1, text: "Zum Ereignisort gehen" }
    { group:12, id:2, text: "um zu erfüllen" }
    { group:12, id:3, text: "Niedrige Nahrungsvorräte sind ein Problem" }
    { group:12, id:4, text: "Hohe Arbeitslosigkeit ist ein Problem" }
    { group:12, id:5, text: "Hohe Steuersätze sind ein Problem" }
    { group:12, id:6, text: "Niedrige Löhne sind ein Problem" }
    { group:12, id:7, text: "Bewohner einfacher Häuser wollen bessere Bedingungen" }
    { group:13, id:0, text: "Klick zum Fortfahren" }
    { group:13, id:1, text: "Rechtsklick zum Fortfahren" }
    { group:13, id:2, text: "Spiel pausiert ('P'-Taste zum Fortfahren)" }
    { group:13, id:3, text: "Rechtsklick zum Fortfahren" }
    { group:13, id:4, text: "Abbrechen" }
    { group:13, id:5, text: "Fortfahren" }
    { group:13, id:6, text: "In der Demo nicht verfügbar!" }
    { group:13, id:7, text: "Klick zum Starten" }
    { group:13, id:8, text: "Wählt einen ägyptischen Namen:" }
    { group:14, id:0, text: "Normal" }
    { group:14, id:1, text: "Risiken" }
    { group:14, id:2, text: "Wasser" }
    { group:14, id:3, text: "Unterhaltung" }
    { group:14, id:4, text: "Religion" }
    { group:14, id:5, text: "Bildung" }
    { group:14, id:6, text: "Gesundheit" }
    { group:14, id:7, text: "Verwaltung" }
    { group:14, id:8, text: "Feuer" }
    { group:14, id:9, text: "Schaden" }
    { group:14, id:10, text: "Verbrechen" }
    { group:14, id:11, text: "Gesamt" }
    { group:14, id:12, text: "Gaukler" }
    { group:14, id:13, text: "Musiker" }
    { group:14, id:14, text: "Tänzer" }
    { group:14, id:15, text: "Senet-Spieler" }
    { group:14, id:16, text: "Zoowärter" }
    { group:14, id:17, text: "Gesamt" }
    { group:14, id:18, text: "Schreiberschulen" }
    { group:14, id:19, text: "Bibliothek" }
    { group:14, id:20, text: "Wasserüberquerungen" }
    { group:14, id:21, text: "Zahnarzt" }
    { group:14, id:22, text: "Arzt" }
    { group:14, id:23, text: "Apotheke" }
    { group:14, id:24, text: "Leichenhalle" }
    { group:14, id:25, text: "Steuereinkommen" }
    { group:14, id:26, text: "Basar-Zugang" }
    { group:14, id:27, text: "Attraktivität" }
    { group:14, id:28, text: "Fruchtbarkeit" }
    { group:14, id:29, text: "Arbeit" }
    { group:14, id:30, text: "Einheimisch" }
    { group:14, id:31, text: "Probleme" }
    { group:14, id:32, text: "Probleme" }
    { group:14, id:33, text: "Getreide" }
    { group:14, id:34, text: "Kichererbsen" }
    { group:14, id:35, text: "Granatäpfel" }
    { group:14, id:36, text: "Feigen" }
    { group:14, id:37, text: "Fleisch" }
    { group:14, id:38, text: "Wild" }
    { group:14, id:39, text: "Keramik" }
    { group:14, id:40, text: "Schmuck" }
    { group:14, id:41, text: "Leinen" }
    { group:14, id:42, text: "Bier" }
    { group:14, id:43, text: "Krankheit" }
    { group:14, id:44, text: "Infizierte Häuser" }
    { group:14, id:45, text: "Wasser" }
    { group:14, id:46, text: "Leere Häuser" }
    { group:14, id:47, text: "Bewässerung" }
    { group:14, id:48, text: "Malaria" }
    { group:14, id:49, text: "Stadtverteidigung" }
    { group:14, id:50, text: "Richter" }
    { group:14, id:51, text: "Klippen ausblenden" }
    { group:15, id:0, text: "Waren annehmen" }
    { group:15, id:1, text: "Waren ablehnen" }
    { group:15, id:2, text: "Waren holen" }
    { group:16, id:0, text: "Gebäude" }
    { group:16, id:1, text: "Stoff" }
    { group:16, id:2, text: "Steuerung" }
    { group:16, id:3, text: "Grafik" }
    { group:16, id:4, text: "Struktur" }
    { group:16, id:5, text: "Netz" }
    { group:16, id:6, text: "Zufall" }
    { group:16, id:7, text: "Figur" }
    { group:16, id:8, text: "Anim" }
    { group:16, id:9, text: "Haftend" }
    { group:16, id:10, text: "RM_build" }
    { group:16, id:11, text: "Gebäude - Wasserversorgung" }
    { group:16, id:12, text: "Gebäude - Zugang" }
    { group:16, id:13, text: "Gebäude - von der Hauptstadt" }
    { group:16, id:14, text: "Gebäude - Schaden" }
    { group:16, id:15, text: "Gebäude - Bevölkerung" }
    { group:16, id:16, text: "Attraktivität" }
    { group:16, id:17, text: "Höhe" }
    { group:16, id:18, text: "Fluss haftend" }
    { group:16, id:19, text: "Barb haftend" }
    { group:16, id:20, text: "Schaden" }
    { group:16, id:21, text: "Nof figs" }
    { group:16, id:22, text: "Alter Typ" }
    { group:16, id:23, text: "Einfluss" }
    { group:16, id:24, text: "Mauer haftend" }
    { group:16, id:25, text: "Straßennetz" }
    { group:16, id:26, text: "Bezirk" }
    { group:17, id:0, text: "Norden" }
    { group:17, id:1, text: "Nordosten" }
    { group:17, id:2, text: "Osten" }
    { group:17, id:3, text: "Südosten" }
    { group:17, id:4, text: "Süden" }
    { group:17, id:5, text: "Südwesten" }
    { group:17, id:6, text: "Westen" }
    { group:17, id:7, text: "Nordwesten" }
    { group:18, id:0, text: "Nein" }
    { group:18, id:1, text: "Ja" }
    { group:18, id:2, text: "Abbrechen" }
    { group:18, id:3, text: "OK" }
    { group:18, id:4, text: "AN" }
    { group:18, id:5, text: "AUS" }
    { group:18, id:6, text: "N/V" }
    { group:18, id:7, text: "Mehr erfahren" }
    { group:18, id:8, text: "und" }
    { group:18, id:9, text: "Wiederholen" }
    { group:18, id:10, text: "Abbrechen" }
    { group:18, id:11, text: "Ignorieren" }
    { group:19, id:0, text: "Muss auf freiem Land gebaut werden" }
    { group:19, id:1, text: "Kein Guthaben mehr!" }
    { group:19, id:2, text: "Ihr könnt nur ein Gebäude dieses Typs haben" }
    { group:19, id:3, text: "Hausentwicklung AUS" }
    { group:19, id:4, text: "Hausentwicklung AN" }
    { group:19, id:5, text: "Straßenentwicklung AUS" }
    { group:19, id:6, text: "Straßenentwicklung AN" }
    { group:19, id:7, text: "Personen anzeigen AUS" }
    { group:19, id:8, text: "Personen anzeigen AN" }
    { group:19, id:9, text: "Dieses Gebäude benötigt Straßenzugang" }
    { group:19, id:10, text: "Dieses Gebäude ist nicht am Wasser!" }
    { group:19, id:11, text: "In dieser Aufgabe nicht verfügbar!" }
    { group:19, id:12, text: "Noch nicht verfügbar!" }
    { group:19, id:13, text: "unbenutzt - Alabaster1" }
    { group:19, id:14, text: "unbenutzt - Alabaster2" }
    { group:19, id:15, text: "Eure Stadt benötigt mehr Arbeiter" }
    { group:19, id:16, text: "Die Leute essen mehr Nahrung als sie produzieren" }
    { group:19, id:17, text: "Baut Basare, um die hier gelagerte Nahrung zu verteilen" }
    { group:19, id:18, text: "Baut Farmen auf Wiesen (sucht nach gelbem Gras)" }
    { group:19, id:19, text: "Baut Lehmgruben in Wassernähe" }
    { group:19, id:20, text: "Baut dies neben felsigen Gebieten" }
    { group:19, id:21, text: "Baut Holzfäller neben Bäumen" }
    { group:19, id:22, text: "Baut dies neben felsigen Gebieten" }
    { group:19, id:23, text: "Erkundet entlang des Flusses, um einen geeigneten Ort zu finden" }
    { group:19, id:24, text: "Dieses Gebäude benötigt Kupfererz" }
    { group:19, id:25, text: "Dieses Gebäude benötigt Gerste" }
    { group:19, id:26, text: "Dieses Gebäude benötigt Flachs" }
    { group:19, id:27, text: "Dieses Gebäude benötigt Lehm" }
    { group:19, id:28, text: "Dieses Gebäude benötigt Edelsteine" }
    { group:19, id:29, text: "Richtet eine Handelsroute ein, um es zu importieren" }
    { group:19, id:30, text: "Weist den Aufseher des Handels an, es zu importieren" }
    { group:19, id:31, text: "Baut eine Kupfermine" }
    { group:19, id:32, text: "Baut eine Gerstenfarm" }
    { group:19, id:33, text: "Baut eine Flachsfarm" }
    { group:19, id:34, text: "Baut eine Lehmgrube" }
    { group:19, id:35, text: "Baut eine Edelsteinmine" }
    { group:19, id:36, text: "Benötigt Zugang zu einem vollen Wasserlift zum Betrieb" }
    { group:19, id:37, text: "Muss am Wasser stehen, um sich zu füllen" }
    { group:19, id:38, text: "Verwendet Bewässerungsgräben, um dies mit einem Wasserlift zu verbinden" }
    { group:19, id:39, text: "Muss neben einer Mauer stehen, um eine Patrouille auszusenden" }
    { group:19, id:40, text: "Benötigt einen funktionierenden Rekrutierer, um Soldaten einzuziehen" }
    { group:19, id:41, text: "Einige Soldaten benötigen Waffenvorräte" }
    { group:19, id:42, text: "Baut eine Gauklerschule, um Künstler hierher zu schicken" }
    { group:19, id:43, text: "Baut ein Konservatorium, um Musiker hierher zu haben" }
    { group:19, id:44, text: "Baut eine Tanzschule" }
    { group:19, id:45, text: "Baut ein Senet-Haus, um Spiele zu veranstalten" }
    { group:19, id:46, text: "unbenutzt - Demo1" }
    { group:19, id:47, text: "Ihr könnt Türme nur auf dicken Mauern bauen" }
    { group:19, id:48, text: "Zu nah an feindlichen Truppen!" }
    { group:19, id:49, text: "Die Moral der Kompanie ist zu niedrig zum Reagieren!" }
    { group:19, id:50, text: "Eure Armee hat ihre vollständige Anzahl an Forts" }
    { group:19, id:51, text: "Monatliche Autospeicherung AN" }
    { group:19, id:52, text: "Monatliche Autospeicherung AUS" }
    { group:19, id:53, text: "Kann Brücke mit Leuten darauf nicht abreißen" }
    { group:19, id:54, text: "Dieser Binnensee hat keinen Zugang zum Meer." }
    { group:19, id:55, text: "Fenster-Modus kann nicht gesetzt werden." }
    { group:19, id:56, text: "Baut Schilfsammler nahe Marschland." }
    { group:19, id:57, text: "Schiffsbauer benötigen Holz für Kriegsschiffe" }
    { group:19, id:58, text: "Benötigt einen Palast, um das Gold in Deben umzuwandeln" }
    { group:19, id:59, text: "Ihr könnt nicht über Tierzuchtgebiete bauen." }
    { group:19, id:60, text: "Einige Parzellen sind zu weit von einer Straße entfernt" }
    { group:19, id:61, text: "Ein Teil der Stadt ist vom Königreichsweg abgeschnitten" }
    { group:19, id:62, text: "Bis ihr den Zugang wiederherstellt, wird dieser Sektor stagnieren" }
    { group:19, id:63, text: "Datenlimit erreicht - siehe README" }
    { group:19, id:64, text: "Ihr könnt Straßensperren nur auf Straßen bauen" }
    { group:19, id:65, text: "Bitte platziert die andere Fähranleger" }
    { group:19, id:66, text: "Es gibt keinen gültigen Platz für diesen Fähranleger" }
    { group:19, id:67, text: "Das Königreich hat bereits seine maximalen vier Nahrungsmittelarten." }
    { group:19, id:68, text: "Ihr dürft Fleisch nur hinzufügen, wenn ihr Stroh produzieren oder importieren könnt." }
    { group:19, id:69, text: "Ihr könnt kein Fleisch in der Stadt produzieren. Es wurde entfernt." }
    { group:19, id:70, text: "Ihr dürft nur eine spezielle Gesteinsart im Königreich haben." }
    { group:19, id:71, text: "Ihr müsst zuerst einen Tempelkomplex bauen" }
    { group:19, id:72, text: "Ein Tempelkomplex kann nur ein Orakel und einen Altar haben." }
    { group:19, id:73, text: "Ihr müsst Orakel und Altäre auf einem Tempelkomplex platzieren." }
    { group:19, id:74, text: "Diese Struktur benötigt Grundwasser. Baut auf einem grasbewachsenen Gebiet." }
    { group:19, id:75, text: "Ihr müsst diesen Unterhaltungsort über einer Kreuzung platzieren." }
    { group:19, id:76, text: "Ihr müsst zuerst einen fertigen Tempel haben!" }
    { group:19, id:77, text: "Ihr benötigt 500 Papyrus, um eine Bibliothek zu bauen." }
    { group:19, id:78, text: "Dieses Gebäude benötigt Schilf" }
    { group:19, id:79, text: "Baut einen Schilfsammler" }
    { group:19, id:80, text: "Dieses Gebäude benötigt Stroh" }
    { group:19, id:81, text: "Baut eine Getreidefarm" }
    { group:19, id:82, text: "Eure Stadt hat ihre vollständige Anzahl an Kriegsschiffwerften" }
    { group:19, id:83, text: "Ihr benötigt 100 Granitblöcke, um einen kleinen Obelisken zu bauen" }
    { group:19, id:84, text: "Ihr benötigt 200 Granitblöcke, um einen großen Obelisken zu bauen" }
    { group:19, id:85, text: "Einige der gewählten Monumente können nicht mehr gebaut werden. Sie wurden entfernt!" }
    { group:19, id:86, text: "Ihr dürft nur einen Obelisken gleichzeitig bauen" }
    { group:19, id:87, text: "Eure Stadt kann ohne Palast keine Steuern erheben." }
    { group:19, id:88, text: "Ihr benötigt 220 Sandsteinblöcke, um einen Sonnentempel zu bauen" }
    { group:19, id:89, text: "Ihr könnt nur einen Sonnentempel gleichzeitig im Bau haben" }
    { group:19, id:90, text: "Es gibt bereits zu wenig Arbeit für die bestehende Bevölkerung." }
    { group:19, id:91, text: "Unsere Nahrungsvorräte sind niedrig." }
    { group:19, id:92, text: "Die Leute essen bereits mehr Nahrung als sie produzieren." }
    { group:19, id:93, text: "Die Gesundheit der Stadt ist erschreckend geworden. Seuche steht unmittelbar bevor." }
    { group:19, id:94, text: "Die Gesundheit der Stadt ist schrecklich und Seuche ist sehr wahrscheinlich." }
    { group:19, id:95, text: "Die Gesundheit der Stadt verschlechtert sich, es besteht ernsthaftes Seuchenrisiko." }
    { group:19, id:96, text: "Die Gesundheit der Stadt wird schlechter, und Seuche könnte zuschlagen." }
    { group:19, id:97, text: "Seuche ist noch wahrscheinlich, aber die Gesundheitsbedingungen verbessern sich." }
    { group:19, id:98, text: "Es besteht noch ein gewisses Seuchenrisiko, aber die Gesundheit verbessert sich." }
    { group:19, id:99, text: "Die Gesundheit verbessert sich, aber Seuche könnte noch zuschlagen." }
    { group:19, id:100, text: "Der Palast wurde ausgeraubt!" }
    { group:19, id:101, text: "Ein Dieb hat Familienersparnisse aus Eurem Anwesen gestohlen!" }
    { group:19, id:102, text: "Wir haben keine Truppen zur Verteidigung gegen den bevorstehenden Angriff." }
    { group:19, id:103, text: "Ihr werdet in der ganzen Stadt verabscheut" }
    { group:19, id:104, text: "Die Leute sind sehr verärgert über Euch" }
    { group:19, id:105, text: "Die Leute sind verärgert über Euch" }
    { group:19, id:106, text: "Die Leute sind sehr unzufrieden mit Euch" }
    { group:19, id:107, text: "Die Leute sind unzufrieden mit Euch" }
    { group:19, id:108, text: "Die Leute sind verärgert über Euch" }
    { group:19, id:109, text: "Die Leute sind Euch gegenüber gleichgültig" }
    { group:19, id:110, text: "Die Leute sind zufrieden mit Euch" }
    { group:19, id:111, text: "Die Leute sind sehr zufrieden mit Euch" }
    { group:19, id:112, text: "Die Leute sind äußerst zufrieden mit Euch" }
    { group:19, id:113, text: "Die Leute lieben Euch" }
    { group:19, id:114, text: "Die Leute verehren Euch wie einen Gott" }
    { group:19, id:115, text: "weil es nicht genug zu essen gibt." }
    { group:19, id:116, text: "weil es nicht genug Arbeit gibt." }
    { group:19, id:117, text: "weil die Steuern so hoch sind." }
    { group:19, id:118, text: "weil die Löhne niedrig sind." }
    { group:19, id:119, text: "weil es zu viele Slums gibt." }
    { group:19, id:120, text: "Leute wandern in die Stadt ein" }
    { group:19, id:121, text: "Mangel an Wohnraum verhindert Einwanderung" }
    { group:19, id:122, text: "Niedrige Löhne schrecken Einwanderer ab" }
    { group:19, id:123, text: "Mangel an Arbeit schreckt Einwanderung ab" }
    { group:19, id:124, text: "Mangel an Nahrung schreckt Einwanderung ab" }
    { group:19, id:125, text: "Hohe Steuern verhindern Einwanderung" }
    { group:19, id:126, text: "Einige Slums verhindern Einwanderung" }
    { group:19, id:127, text: "Niedrige Stadtstimmung verhindert Einwanderung" }
    { group:19, id:128, text: "Mangel an Wohnraum vertreibt Leute aus der Stadt." }
    { group:19, id:129, text: "Niedrige Löhne veranlassen Leute, die Stadt zu verlassen." }
    { group:19, id:130, text: "Hohe Arbeitslosigkeit bringt Leute dazu, die Stadt zu verlassen." }
    { group:19, id:131, text: "Mangel an Nahrung vertreibt hungrige Leute aus der Stadt." }
    { group:19, id:132, text: "Die Leute würden lieber gehen als hohe Steuern zahlen." }
    { group:19, id:133, text: "Die Slums der Stadt ermutigen Leute zu gehen." }
    { group:19, id:134, text: "Die Stadtstimmung ist so schlecht, dass Leute gehen." }
    { group:19, id:135, text: "Dieses Gebäude benötigt Bier zum Funktionieren" }
    { group:19, id:136, text: "Baut eine Brauerei" }
    { group:19, id:137, text: "Dieses Gebäude benötigt Papyrus zum Funktionieren" }
    { group:19, id:138, text: "Baut einen Papyrusmacher" }
    { group:19, id:139, text: "Dieses Gebäude benötigt Leinen zum Funktionieren" }
    { group:19, id:140, text: "Baut einen Weber" }
    { group:19, id:141, text: "Dieses Gebäude benötigt Holz zum Funktionieren" }
    { group:19, id:142, text: "Baut einen Holzfäller" }
    { group:19, id:143, text: "Dieses Gebäude benötigt Lehm und Stroh" }
    { group:19, id:144, text: "Richtet eine Handelsroute ein, um Lehm zu importieren" }
    { group:19, id:145, text: "Weist den Aufseher des Handels an, Lehm zu importieren" }
    { group:19, id:146, text: "Richtet eine Handelsroute ein, um Stroh zu importieren" }
    { group:19, id:147, text: "Weist den Aufseher des Handels an, Stroh zu importieren" }
    { group:19, id:148, text: "Dieses Monument benötigt einfachen Stein und Kalkstein" }
    { group:19, id:149, text: "Baut einen Einfachen Steinbruch" }
    { group:19, id:150, text: "Richtet eine Handelsroute ein, um einfachen Stein zu importieren" }
    { group:19, id:151, text: "Weist den Aufseher des Handels an, einfachen Stein zu importieren" }
    { group:19, id:152, text: "Baut einen Kalksteinbruch" }
    { group:19, id:153, text: "Richtet eine Handelsroute ein, um Kalkstein zu importieren" }
    { group:19, id:154, text: "Weist den Aufseher des Handels an, Kalkstein zu importieren" }
    { group:19, id:155, text: "Dieses Monument benötigt einfachen Stein" }
    { group:19, id:156, text: "Dieses Monument benötigt Kalkstein" }
    { group:19, id:157, text: "Dieses Monument benötigt Ziegel und Kalkstein" }
    { group:19, id:158, text: "Baut eine Ziegelei" }
    { group:19, id:159, text: "Richtet eine Handelsroute ein, um Ziegel zu importieren" }
    { group:19, id:160, text: "Weist den Aufseher des Handels an, Ziegel zu importieren" }
    { group:19, id:161, text: "Dieses Monument benötigt Ziegel" }
    { group:19, id:162, text: "Dieses Monument benötigt Sandstein" }
    { group:19, id:163, text: "Baut einen Sandsteinbruch" }
    { group:19, id:164, text: "Weist den Aufseher des Handels an, Bier zu importieren" }
    { group:19, id:165, text: "Richtet eine Handelsroute ein, um Bier zu importieren" }
    { group:19, id:166, text: "Weist den Aufseher des Handels an, Gerste zu importieren" }
    { group:19, id:167, text: "Richtet eine Handelsroute ein, um Gerste zu importieren" }
    { group:19, id:168, text: "Weist den Aufseher des Handels an, Schilf zu importieren" }
    { group:19, id:169, text: "Richtet eine Handelsroute ein, um Schilf zu importieren" }
    { group:19, id:170, text: "Weist den Aufseher des Handels an, Papyrus zu importieren" }
    { group:19, id:171, text: "Richtet eine Handelsroute ein, um Papyrus zu importieren" }
    { group:19, id:172, text: "Weist den Aufseher des Handels an, Flachs zu importieren" }
    { group:19, id:173, text: "Richtet eine Handelsroute ein, um Flachs zu importieren" }
    { group:19, id:174, text: "Weist den Aufseher des Handels an, Leinen zu importieren" }
    { group:19, id:175, text: "Richtet eine Handelsroute ein, um Leinen zu importieren" }
    { group:19, id:176, text: "Leichenhallen können nicht arbeiten und wurden entfernt. Die Stadt kann kein Leinen produzieren oder importieren." }
    { group:19, id:177, text: "Senet-Haus kann nicht arbeiten und wurde entfernt. Die Stadt kann kein Bier produzieren oder importieren." }
    { group:19, id:178, text: "Schreiberschulen können nicht arbeiten und wurden entfernt. Die Stadt kann keinen Papyrus produzieren oder importieren." }
    { group:19, id:179, text: "Bibliotheken können nicht arbeiten und wurden entfernt. Die Stadt kann keinen Papyrus produzieren oder importieren." }
    { group:19, id:180, text: "Waffenschmiede können nicht arbeiten und wurden entfernt. Die Stadt kann kein Kupfer produzieren oder importieren." }
    { group:19, id:181, text: "Wagenbauer kann nicht arbeiten und wurde entfernt. Die Stadt kann kein Holz produzieren oder importieren." }
    { group:19, id:182, text: "Fort: Infanterie kann nicht arbeiten und wurde entfernt. Die Stadt hat keinen Rekrutierer." }
    { group:19, id:183, text: "Fort: Bogenschützen kann nicht arbeiten und wurde entfernt. Die Stadt hat keinen Rekrutierer." }
    { group:19, id:184, text: "Fort: Streitwagenkämpfer kann nicht arbeiten und wurde entfernt. Die Stadt hat keinen Rekrutierer." }
    { group:19, id:185, text: "Akademien können nicht arbeiten und wurden entfernt. Die Stadt kann kein Holz produzieren oder importieren." }
    { group:19, id:186, text: "Fort: Infanterie kann nicht arbeiten und wurde entfernt. Die Stadt kann keine Waffen produzieren oder importieren." }
    { group:19, id:187, text: "Fort: Streitwagenkämpfer kann nicht arbeiten und wurde entfernt. Die Stadt kann keine Streitwagen produzieren oder importieren." }
    { group:19, id:188, text: "Ihr benötigt 240 Sandsteinblöcke, um ein Mausoleum zu bauen" }
    { group:19, id:189, text: "Baut eine Brauerei oder ordnet an, dass Bier importiert wird." }
    { group:19, id:190, text: "Baut eine Brauerei oder richtet eine Handelsroute ein, um Bier zu importieren." }
    { group:19, id:191, text: "Baut einen Papyrusmacher oder ordnet an, dass er importiert wird." }
    { group:19, id:192, text: "Baut einen Papyrusmacher oder öffnet eine Handelsroute, um Papyrus zu importieren." }
    { group:19, id:193, text: "Baut einen Weber oder ordnet an, dass Leinen importiert wird." }
    { group:19, id:194, text: "Baut einen Weber oder richtet eine Handelsroute ein, um Leinen zu importieren." }
    { group:19, id:195, text: "Diebe haben gerade ein Steuereintreiberbüro ausgeraubt!" }
    { group:19, id:196, text: "Diebe haben gerade ein Gerichtsgebäude ausgeraubt!" }
    { group:19, id:197, text: "Euer Anwesen wurde zerstört und geplündert!" }
    { group:19, id:198, text: "Der Palast wurde zerstört und geplündert!" }
    { group:19, id:199, text: "Ein Steuereintreiberbüro wurde zerstört und geplündert!" }
    { group:19, id:200, text: "Ein Gerichtsgebäude wurde zerstört und geplündert!" }
    { group:19, id:201, text: "Ein Goldgräber wurde angegriffen und ausgeraubt!" }
    { group:19, id:202, text: "Baut einen Getreidespeicher, um die bevorstehende Ernte zu lagern" }
    { group:19, id:203, text: "Baut Getreidespeicher, um die bevorstehende Ernte zu lagern" }
    { group:19, id:204, text: "Ihr dürft nur 10 Docks gleichzeitig aktiv haben" }
    { group:19, id:205, text: "Schreine müssen innerhalb von zwei Feldern einer Straße sein, um die Stadt zu beeinflussen" }
    { group:19, id:206, text: "Baut eine Gauklerschule, um Künstler für diesen Ort bereitzustellen" }
    { group:19, id:207, text: "Baut ein Konservatorium, um Musiker für diesen Ort bereitzustellen" }
    { group:19, id:208, text: "Baut eine Tanzschule, um Tänzer für diesen Ort auszubilden" }
    { group:19, id:209, text: "Diese Kompanie kann ihr beabsichtigtes Ziel nicht erreichen" }
    { group:19, id:210, text: "Spiel gespeichert." }
    { group:19, id:211, text: "Muss auf hindernisfreiem Land gebaut werden" }
    { group:19, id:212, text: "Der Aufweg des Monuments muss zum Wasser führen" }
    { group:19, id:213, text: "Baut den Festplatz über einer Straßenkreuzung" }
    { group:19, id:214, text: "Niemand wandert ein, während Feinde unseren Boden verschmutzen" }
    { group:19, id:215, text: "Cheats aktiviert" }
    { group:19, id:216, text: "Cheats deaktiviert" }
    { group:19, id:217, text: "Flut wird perfekt sein" }
    { group:19, id:218, text: "Flut wird ausgezeichnet sein" }
    { group:19, id:219, text: "Flut wird gut sein" }
    { group:19, id:220, text: "Flut wird mittelmäßig sein" }
    { group:19, id:221, text: "Flut wird schlecht sein" }
    { group:19, id:222, text: "Flut wird ausbleiben" }
    { group:19, id:223, text: "Preiserhöhung" }
    { group:19, id:224, text: "Preissenkung" }
    { group:19, id:225, text: "Löhne im Königreich gesenkt" }
    { group:19, id:226, text: "Löhne im Königreich erhöht" }
    { group:19, id:227, text: "Handel mit Stadt nimmt ab" }
    { group:19, id:228, text: "Handel mit Stadt nimmt zu" }
    { group:19, id:229, text: "Ansehen im Königreich steigt" }
    { group:19, id:230, text: "Bevölkerungsmeilenstein erreicht" }
    { group:19, id:231, text: "Segen eines niederen Gottes erhalten" }
    { group:19, id:232, text: "Fest beginnt" }
    { group:19, id:233, text: "Erfüllung nun möglich: Waren automatisch versandt" }
    { group:19, id:234, text: "Der Zoo kann nicht arbeiten und wurde entfernt. Die Stadt kann weder Stroh noch Wildfleisch produzieren oder importieren." }
    { group:19, id:235, text: "Dieses Gebäude benötigt Wildfleisch zum Funktionieren" }
    { group:19, id:236, text: "Baut eine Jagdhütte" }
    { group:19, id:237, text: "Baut eine Jagdhütte oder ordnet an, dass Wildfleisch importiert wird." }
    { group:19, id:238, text: "Baut eine Jagdhütte oder importiert Wildfleisch." }
    { group:19, id:239, text: "Dieses Monument benötigt Kupfer" }
    { group:19, id:240, text: "Dieses Monument benötigt Marmor" }
    { group:19, id:241, text: "Ihr könnt nur eine Bibliothek von Alexandria bauen!" }
    { group:19, id:242, text: "Ihr könnt nur einen Pharos-Leuchtturm bauen!" }
    { group:19, id:243, text: "Ihr könnt nur ein Caesareum bauen!" }
    { group:19, id:244, text: "Krankheit bricht aus" }
    { group:19, id:245, text: "Malaria bricht aus" }
    { group:19, id:246, text: "Dieses Monument benötigt Granit" }
    { group:19, id:247, text: "Muss vollständig über Felsen gebaut werden" }
    { group:19, id:248, text: "Pharos-Leuchtturm kann nicht abgerissen werden" }
    { group:19, id:249, text: "Grabräuber haben ein altes Grab geplündert!" }
    { group:19, id:250, text: "Das Mausoleum Alexanders des Großen wurde geplündert!" }
    { group:19, id:251, text: "Grabräuber haben Grabbeigaben gestohlen!" }
    { group:19, id:252, text: "Ein Grabräuber wurde festgenommen" }
    { group:19, id:253, text: "Dieses Gebäude benötigt Öl und Keramik zum Funktionieren" }
    { group:19, id:254, text: "Baut einen Töpfer" }
    { group:19, id:255, text: "Richtet eine Handelsroute ein, um Keramik zu importieren" }
    { group:19, id:256, text: "Weist den Aufseher des Handels an, Keramik zu importieren" }
    { group:19, id:257, text: "Richtet eine Handelsroute ein, um Öl zu importieren" }
    { group:19, id:258, text: "Weist den Aufseher des Handels an, Öl zu importieren" }
    { group:19, id:259, text: "Dieses Gebäude benötigt Henna zum Funktionieren" }
    { group:19, id:260, text: "Baut eine Hennafarm" }
    { group:19, id:261, text: "Weist den Aufseher des Handels an, Henna zu importieren" }
    { group:19, id:262, text: "Richtet eine Handelsroute ein, um Henna zu importieren" }
    { group:19, id:263, text: "Dieses Gebäude benötigt Öl zum Funktionieren" }
    { group:19, id:264, text: "Dieses Gebäude benötigt Keramik zum Funktionieren" }
    { group:19, id:265, text: "Baut einen Farbhersteller oder richtet eine Handelsroute ein, um Farbe zu importieren" }
    { group:19, id:266, text: "Baut einen Farbhersteller oder weist den Aufseher des Handels an, sie zu importieren" }
    { group:19, id:267, text: "Baut einen Farbhersteller" }
    { group:19, id:268, text: "Dieses Gebäude benötigt Lehm und Farbe zum Funktionieren" }
    { group:19, id:269, text: "Angestellte benötigt" }
    { group:19, id:270, text: "Muss vollständig über Klippen gebaut werden" }
    { group:19, id:271, text: "... mit Eingang auf freiem Land." }
    { group:20, id:0, text: "v. Chr." }
    { group:20, id:1, text: "n. Chr." }
    { group:21, id:0, text: "Elephantine" }
    { group:21, id:1, text: "Abydos" }
    { group:21, id:2, text: "Bahariya-Oase" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apollinopolis" }
    { group:21, id:5, text: "Bubastis" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Byblos" }
    { group:21, id:8, text: "Dahschur" }
    { group:21, id:9, text: "Dakhla-Oase" }
    { group:21, id:10, text: "Abusir" }
    { group:21, id:11, text: "Dunqul-Oase" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "Farafra-Oase" }
    { group:21, id:14, text: "Gaza" }
    { group:21, id:15, text: "Semna" }
    { group:21, id:16, text: "Herakleopolis" }
    { group:21, id:17, text: "Kahun" }
    { group:21, id:18, text: "Mirgissa" }
    { group:21, id:19, text: "Itjtawy" }
    { group:21, id:20, text: "Dendera" }
    { group:21, id:21, text: "Jericho" }
    { group:21, id:22, text: "Coptos" }
    { group:21, id:23, text: "Kerma" }
    { group:21, id:24, text: "Kharga-Oase" }
    { group:21, id:25, text: "Hermopolis" }
    { group:21, id:26, text: "Knossos" }
    { group:21, id:27, text: "Kyrene" }
    { group:21, id:28, text: "Meidum" }
    { group:21, id:29, text: "Memphis" }
    { group:21, id:30, text: "Beni Hasan" }
    { group:21, id:31, text: "Mykene" }
    { group:21, id:32, text: "Hierakonpolis" }
    { group:21, id:33, text: "Naqada" }
    { group:21, id:34, text: "Heliopolis" }
    { group:21, id:35, text: "Buto" }
    { group:21, id:36, text: "Punt" }
    { group:21, id:37, text: "Qanta" }
    { group:21, id:38, text: "Gizeh" }
    { group:21, id:39, text: "Auaris" }
    { group:21, id:40, text: "Sakkara" }
    { group:21, id:41, text: "Lykopolis" }
    { group:21, id:42, text: "Mersa Gawasis" }
    { group:21, id:43, text: "Selima-Oase" }
    { group:21, id:44, text: "Serabit Khadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Scharuhen" }
    { group:21, id:47, text: "Thinis" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toschka" }
    { group:21, id:50, text: "Tyros" }
    { group:21, id:51, text: "Theben" }
    { group:21, id:52, text: "Pelusion" }
    { group:21, id:53, text: "Alexandria" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medina" }
    { group:21, id:56, text: "Abu Simbel" }
    { group:21, id:57, text: "Actium" }
    { group:21, id:58, text: "Rom" }
    { group:21, id:59, text: "Tanis" }
    { group:21, id:60, text: "Pi-Yer" }
    { group:21, id:61, text: "Siwa-Oase" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Pi-Ramesse" }
    { group:21, id:64, text: "Athen" }
    { group:21, id:65, text: "Cleoantonopolis" }
    { group:22, id:0, text: "'Leere Kompanie'" }
    { group:22, id:1, text: "'Die Löwen'" }
    { group:22, id:2, text: "'Die Krokodile'" }
    { group:22, id:3, text: "'Die Kobras'" }
    { group:22, id:4, text: "'Die Skorpione'" }
    { group:22, id:5, text: "'Die Falken'" }
    { group:22, id:6, text: "'Die Widder'" }
    { group:22, id:7, text: "'Die Leoparden'" }
    { group:22, id:8, text: "'Die Spinnen'" }
    { group:22, id:9, text: "'Die Katzen'" }
    { group:22, id:10, text: "'Die Hyänen'" }
    { group:23, id:0, text: "Nichts" }
    { group:23, id:1, text: "Getreide" }
    { group:23, id:2, text: "Fleisch" }
    { group:23, id:3, text: "Salat" }
    { group:23, id:4, text: "Kichererbsen" }
    { group:23, id:5, text: "Granatäpfel" }
    { group:23, id:6, text: "Feigen" }
    { group:23, id:7, text: "Fisch" }
    { group:23, id:8, text: "Wildfleisch" }
    { group:23, id:9, text: "Stroh" }
    { group:23, id:10, text: "Waffen" }
    { group:23, id:11, text: "Lehm" }
    { group:23, id:12, text: "Ziegel" }
    { group:23, id:13, text: "Keramik" }
    { group:23, id:14, text: "Gerste" }
    { group:23, id:15, text: "Bier" }
    { group:23, id:16, text: "Flachs" }
    { group:23, id:17, text: "Leinen" }
    { group:23, id:18, text: "Edelsteine" }
    { group:23, id:19, text: "Luxusgüter" }
    { group:23, id:20, text: "Holz" }
    { group:23, id:21, text: "Gold" }
    { group:23, id:22, text: "Schilf" }
    { group:23, id:23, text: "Papyrus" }
    { group:23, id:24, text: "Einfacher Stein" }
    { group:23, id:25, text: "Kalkstein" }
    { group:23, id:26, text: "Granit" }
    { group:23, id:27, text: "Unused12" }
    { group:23, id:28, text: "Streitwagen" }
    { group:23, id:29, text: "Kupfer" }
    { group:23, id:30, text: "Sandstein" }
    { group:23, id:31, text: "Öl" }
    { group:23, id:32, text: "Henna" }
    { group:23, id:33, text: "Farbe" }
    { group:23, id:34, text: "Lampen" }
    { group:23, id:35, text: "Marmor" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Truppen" }
    { group:23, id:38, text: "Schmuck (Luxusgüter)" }
    { group:23, id:39, text: "Schmuck" }
    { group:23, id:40, text: "Wein (Luxusgüter)" }
    { group:23, id:41, text: "Wein" }
    { group:23, id:42, text: "Elfenbein (Luxusgüter)" }
    { group:23, id:43, text: "Elfenbein" }
    { group:23, id:44, text: "Ebenholz (Luxusgüter)" }
    { group:23, id:45, text: "Ebenholz" }
    { group:23, id:46, text: "Weihrauch (Luxusgüter)" }
    { group:23, id:47, text: "Weihrauch" }
    { group:23, id:48, text: "Olivenöl (Luxusgüter)" }
    { group:23, id:49, text: "Olivenöl" }
    { group:23, id:50, text: "Leopardenfelle (Luxusgüter)" }
    { group:23, id:51, text: "Leopardenfelle" }
    { group:23, id:52, text: "Parfüm (Luxusgüter)" }
    { group:23, id:53, text: "Parfüm" }
    { group:23, id:54, text: "Dieser Platz bleibt frei" }
    { group:23, id:55, text: "Körbe Getreide" }
    { group:23, id:56, text: "Fleischstücke" }
    { group:23, id:57, text: "Salatköpfe" }
    { group:23, id:58, text: "Krüge Kichererbsen" }
    { group:23, id:59, text: "Granatäpfel" }
    { group:23, id:60, text: "Krüge Feigen" }
    { group:23, id:61, text: "Eimer Fisch" }
    { group:23, id:62, text: "Portionen Wild" }
    { group:23, id:63, text: "Ballen Stroh" }
    { group:23, id:64, text: "Waffen" }
    { group:23, id:65, text: "Säcke Lehm" }
    { group:23, id:66, text: "Ziegel" }
    { group:23, id:67, text: "Keramikstücke" }
    { group:23, id:68, text: "Pakete Gerste" }
    { group:23, id:69, text: "Krüge Bier" }
    { group:23, id:70, text: "Ballen Flachs" }
    { group:23, id:71, text: "Rollen Leinen" }
    { group:23, id:72, text: "Edelsteine" }
    { group:23, id:73, text: "Beutel Luxusgüter" }
    { group:23, id:74, text: "Holzbretter" }
    { group:23, id:75, text: "Gold" }
    { group:23, id:76, text: "Schilf" }
    { group:23, id:77, text: "Papyrusblätter" }
    { group:23, id:78, text: "Blöcke einfachen Stein" }
    { group:23, id:79, text: "Kalksteinblöcke" }
    { group:23, id:80, text: "Granitblöcke" }
    { group:23, id:81, text: "unbenutzte Zeile812" }
    { group:23, id:82, text: "Streitwagen" }
    { group:23, id:83, text: "Kupferbarren" }
    { group:23, id:84, text: "Sandsteinblöcke" }
    { group:23, id:85, text: "Krüge Öl" }
    { group:23, id:86, text: "Ballen Henna" }
    { group:23, id:87, text: "Krüge Farbe" }
    { group:23, id:88, text: "Lampen" }
    { group:23, id:89, text: "Marmorblöcke" }
    { group:23, id:90, text: "Deben" }
    { group:23, id:91, text: "Truppen" }
    { group:24, id:0, text: "Woche 1" }
    { group:24, id:1, text: "Woche 2" }
    { group:24, id:2, text: "Woche 3" }
    { group:24, id:3, text: "Woche 4" }
    { group:24, id:4, text: "Woche 5" }
    { group:24, id:5, text: "Woche 6" }
    { group:24, id:6, text: "Woche 7" }
    { group:24, id:7, text: "Woche 8" }
    { group:24, id:8, text: "Woche 9" }
    { group:24, id:9, text: "Woche 10" }
    { group:24, id:10, text: "Woche 11" }
    { group:24, id:11, text: "Woche 12" }
    { group:24, id:12, text: "Woche 13" }
    { group:24, id:13, text: "Woche 14" }
    { group:24, id:14, text: "Woche 15" }
    { group:24, id:15, text: "Woche 16" }
    { group:25, id:0, text: "Jan" }
    { group:25, id:1, text: "Feb" }
    { group:25, id:2, text: "Mär" }
    { group:25, id:3, text: "Apr" }
    { group:25, id:4, text: "Mai" }
    { group:25, id:5, text: "Jun" }
    { group:25, id:6, text: "Jul" }
    { group:25, id:7, text: "Aug" }
    { group:25, id:8, text: "Sep" }
    { group:25, id:9, text: "Okt" }
    { group:25, id:10, text: "Nov" }
    { group:25, id:11, text: "Dez" }
    { group:26, id:0, text: "Leer" }
    { group:26, id:1, text: "Rot" }
    { group:26, id:2, text: "Blau" }
    { group:26, id:3, text: "Grün" }
    { group:26, id:4, text: "Orange" }
    { group:26, id:5, text: "Silber" }
    { group:26, id:6, text: "Violett" }
    { group:26, id:7, text: "Gelb" }
    { group:26, id:8, text: "Schwarz" }
    { group:27, id:0, text: "Prädynastische Zeit" }
    { group:27, id:1, text: "Archaische Zeit" }
    { group:27, id:2, text: "Altes Reich" }
    { group:27, id:3, text: "Mittleres Reich" }
    { group:27, id:4, text: "Neues Reich" }
    { group:27, id:5, text: "Tal der Könige" }
    { group:27, id:6, text: "Ramses II" }
    { group:27, id:7, text: "Antike Eroberer" }
    { group:27, id:8, text: "Kleopatras Hauptstadt" }
    { group:28, id:0, text: "Nirgendwo" }
    { group:28, id:1, text: "Rückgängig" }
    { group:28, id:2, text: "Farm" }
    { group:28, id:3, text: "Rohstoffe" }
    { group:28, id:4, text: "Baugilden" }
    { group:28, id:5, text: "Straße" }
    { group:28, id:6, text: "Lehmmauer" }
    { group:28, id:7, text: "Wasserlift" }
    { group:28, id:8, text: "Bewässerungsgraben" }
    { group:28, id:9, text: "Graben" }
    { group:28, id:10, text: "Haus1" }
    { group:28, id:11, text: "Haus2" }
    { group:28, id:12, text: "Haus3" }
    { group:28, id:13, text: "Haus4" }
    { group:28, id:14, text: "Haus5" }
    { group:28, id:15, text: "Haus6" }
    { group:28, id:16, text: "Haus7" }
    { group:28, id:17, text: "Haus8" }
    { group:28, id:18, text: "Haus9" }
    { group:28, id:19, text: "Haus10" }
    { group:28, id:20, text: "Haus11" }
    { group:28, id:21, text: "Haus12" }
    { group:28, id:22, text: "Haus13" }
    { group:28, id:23, text: "Haus14" }
    { group:28, id:24, text: "Haus15" }
    { group:28, id:25, text: "Haus16" }
    { group:28, id:26, text: "Haus17" }
    { group:28, id:27, text: "Haus18" }
    { group:28, id:28, text: "Haus19" }
    { group:28, id:29, text: "Haus20" }
    { group:28, id:30, text: "Musikpavillon" }
    { group:28, id:31, text: "Bude" }
    { group:28, id:32, text: "Senet-Haus" }
    { group:28, id:33, text: "Pavillon" }
    { group:28, id:34, text: "Konservatorium" }
    { group:28, id:35, text: "Tanzschule" }
    { group:28, id:36, text: "Gauklerschule" }
    { group:28, id:37, text: "Senet-Meister" }
    { group:28, id:38, text: "Platz" }
    { group:28, id:39, text: "Gärten" }
    { group:28, id:40, text: "Streitwagenkämpfer" }
    { group:28, id:41, text: "Kleine Statue" }
    { group:28, id:42, text: "Mittlere Statue" }
    { group:28, id:43, text: "Große Statue" }
    { group:28, id:44, text: "Bogenschützen" }
    { group:28, id:45, text: "Infanterie" }
    { group:28, id:46, text: "Apotheke" }
    { group:28, id:47, text: "Leichenhalle" }
    { group:28, id:48, text: "Monumente" }
    { group:28, id:49, text: "Zahnarzt" }
    { group:28, id:50, text: "Lagerplatz" }
    { group:28, id:51, text: "Schreiberschule" }
    { group:28, id:52, text: "Wasserüberquerungen" }
    { group:28, id:53, text: "Bibliothek" }
    { group:28, id:54, text: "Fort" }
    { group:28, id:55, text: "Polizeistation" }
    { group:28, id:56, text: "unbenutzt 921" }
    { group:28, id:57, text: "Fort" }
    { group:28, id:58, text: "Lehm-Torhaus" }
    { group:28, id:59, text: "Lehm-Turm" }
    { group:28, id:60, text: "Tempel des Osiris" }
    { group:28, id:61, text: "Tempel des Ra" }
    { group:28, id:62, text: "Tempel des Ptah" }
    { group:28, id:63, text: "Tempel des Seth" }
    { group:28, id:64, text: "Tempel der Bast" }
    { group:28, id:65, text: "Tempelkomplex des Osiris" }
    { group:28, id:66, text: "Tempelkomplex des Ra" }
    { group:28, id:67, text: "Tempelkomplex des Ptah" }
    { group:28, id:68, text: "Tempelkomplex des Seth" }
    { group:28, id:69, text: "Tempelkomplex der Bast" }
    { group:28, id:70, text: "Basar" }
    { group:28, id:71, text: "Getreidespeicher" }
    { group:28, id:72, text: "Lagerplatz" }
    { group:28, id:73, text: "Lagerplätze" }
    { group:28, id:74, text: "Schiffsbauer" }
    { group:28, id:75, text: "Dock" }
    { group:28, id:76, text: "Fischerkai" }
    { group:28, id:77, text: "Persönliches Anwesen" }
    { group:28, id:78, text: "Familienanwesen" }
    { group:28, id:79, text: "Dynastieanwesen" }
    { group:28, id:80, text: "unbenutzt 945" }
    { group:28, id:81, text: "Architektenposten" }
    { group:28, id:82, text: "Brücke" }
    { group:28, id:83, text: "unbenutzt 948" }
    { group:28, id:84, text: "Dorfpalast" }
    { group:28, id:85, text: "Stadtpalast" }
    { group:28, id:86, text: "Steuereintreiber" }
    { group:28, id:87, text: "Steuereintreiber" }
    { group:28, id:88, text: "Nichts" }
    { group:28, id:89, text: "Nichts" }
    { group:28, id:90, text: "Wasserlift" }
    { group:28, id:91, text: "Verschönerung" }
    { group:28, id:92, text: "Brunnen" }
    { group:28, id:93, text: "Nichts" }
    { group:28, id:94, text: "Akademie" }
    { group:28, id:95, text: "Rekrutierer" }
    { group:28, id:96, text: "Tempel" }
    { group:28, id:97, text: "Tempelkomplex" }
    { group:28, id:98, text: "Orakel" }
    { group:28, id:99, text: "Brennende Ruine" }
    { group:28, id:100, text: "Gerste" }
    { group:28, id:101, text: "Flachs" }
    { group:28, id:102, text: "Getreide" }
    { group:28, id:103, text: "Salat" }
    { group:28, id:104, text: "Granatäpfel" }
    { group:28, id:105, text: "Kichererbsen" }
    { group:28, id:106, text: "Einfacher Steinbruch" }
    { group:28, id:107, text: "Kalksteinbruch" }
    { group:28, id:108, text: "Holzfäller" }
    { group:28, id:109, text: "Lehmgrube" }
    { group:28, id:110, text: "Brauerei" }
    { group:28, id:111, text: "Weber" }
    { group:28, id:112, text: "Waffenschmiede" }
    { group:28, id:113, text: "Juwelier" }
    { group:28, id:114, text: "Töpfer" }
    { group:28, id:115, text: "Jagdhütte" }
    { group:28, id:116, text: "Nichts" }
    { group:28, id:117, text: "Nichts" }
    { group:28, id:118, text: "Nichts" }
    { group:28, id:119, text: "Nichts" }
    { group:28, id:120, text: "unbenutzt 985" }
    { group:28, id:121, text: "Riss (nicht benutzt?)" }
    { group:28, id:122, text: "unbenutzt 987" }
    { group:28, id:123, text: "Nichts" }
    { group:28, id:124, text: "Nichts" }
    { group:28, id:125, text: "Nichts" }
    { group:28, id:126, text: "Nichts" }
    { group:28, id:127, text: "Nichts" }
    { group:28, id:128, text: "Nichts" }
    { group:28, id:129, text: "Nichts" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Fähranleger" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Straßensperre" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Schrein des Osiris" }
    { group:28, id:141, text: "Schrein des Ra" }
    { group:28, id:142, text: "Schrein des Ptah" }
    { group:28, id:143, text: "Schrein des Seth" }
    { group:28, id:144, text: "Schrein der Bast" }
    { group:28, id:145, text: "Schrein des " }
    { group:28, id:146, text: "Schrein des" }
    { group:28, id:147, text: "Schrein des " }
    { group:28, id:148, text: "Schrein des " }
    { group:28, id:149, text: "Schrein des" }
    { group:28, id:150, text: "Schreine" }
    { group:28, id:151, text: "Tempel des Osiris" }
    { group:28, id:152, text: "Tempel des Ra" }
    { group:28, id:153, text: "Tempel des Ptah" }
    { group:28, id:154, text: "Tempel des Seth" }
    { group:28, id:155, text: "Tempel der Bast" }
    { group:28, id:156, text: "Gott 5" }
    { group:28, id:157, text: "Gott 6" }
    { group:28, id:158, text: "Gott 7" }
    { group:28, id:159, text: "Gott 8" }
    { group:28, id:160, text: "Gott 9" }
    { group:28, id:161, text: "Goldmine" }
    { group:28, id:162, text: "Edelsteinmine" }
    { group:28, id:163, text: "Gewöhnlicher Fels" }
    { group:28, id:164, text: "Erzführender Fels" }
    { group:28, id:165, text: "Unbenutzt 1030" }
    { group:28, id:166, text: "Unbenutzt 1031" }
    { group:28, id:167, text: "Feuerwache" }
    { group:28, id:168, text: "Ziegelmauer" }
    { group:28, id:169, text: "Mauer" }
    { group:28, id:170, text: "Ziegel-Torhaus" }
    { group:28, id:171, text: "Torhaus" }
    { group:28, id:172, text: "Ziegel-Turm" }
    { group:28, id:173, text: "Turm" }
    { group:28, id:174, text: "Lehm-Strukturen" }
    { group:28, id:175, text: "Ziegel-Strukturen" }
    { group:28, id:176, text: "Verteidigungsanlagen" }
    { group:28, id:177, text: "Zimmerergilde" }
    { group:28, id:178, text: "Maurergilde" }
    { group:28, id:179, text: "Steinmetzgilde" }
    { group:28, id:180, text: "Wasserversorgung" }
    { group:28, id:181, text: "Transportkai" }
    { group:28, id:182, text: "Kriegsschiffwerft" }
    { group:28, id:183, text: "Pyramide" }
    { group:28, id:184, text: "Gerichtsgebäude" }
    { group:28, id:185, text: "Militärakademie 2" }
    { group:28, id:186, text: "Militärakademie 3" }
    { group:28, id:187, text: "Dorfpalast" }
    { group:28, id:188, text: "Stadtpalast" }
    { group:28, id:189, text: "Großstadtpalast" }
    { group:28, id:190, text: "Basar 2" }
    { group:28, id:191, text: "Getreidespeicher 2" }
    { group:28, id:192, text: "Dock 2" }
    { group:28, id:193, text: "Lagerplatz 2" }
    { group:28, id:194, text: "Viehranch" }
    { group:28, id:195, text: "Schilfsammler" }
    { group:28, id:196, text: "Feigenfarm" }
    { group:28, id:197, text: "Marschland" }
    { group:28, id:198, text: "Sanddünen" }
    { group:28, id:199, text: "Arbeitslager" }
    { group:28, id:200, text: "Lehm-Torhaus" }
    { group:28, id:201, text: "Ziegel-Torhaus" }
    { group:28, id:202, text: "Torhaus" }
    { group:28, id:203, text: "Papyrusmacher" }
    { group:28, id:204, text: "Ziegelei" }
    { group:28, id:205, text: "Wagenbauer" }
    { group:28, id:206, text: "Arzt" }
    { group:28, id:207, text: "unbenutzt 1072" }
    { group:28, id:208, text: "unbenutzt 1073" }
    { group:28, id:209, text: "Festplatz" }
    { group:28, id:210, text: "Sphinx" }
    { group:28, id:211, text: "Tempelkomplex-Erweiterung" }
    { group:28, id:212, text: "Tempelkomplex-Erweiterung" }
    { group:28, id:213, text: "unbenutzt 1078" }
    { group:28, id:214, text: "Ausschiffer-Punkt" }
    { group:28, id:215, text: "unbenutzt 1080" }
    { group:28, id:216, text: "Granitbruch" }
    { group:28, id:217, text: "Kupfermine" }
    { group:28, id:218, text: "temp1" }
    { group:28, id:219, text: "temp2" }
    { group:28, id:220, text: "temp3" }
    { group:28, id:221, text: "Sandsteinbruch" }
    { group:28, id:222, text: "Mausoleum" }
    { group:28, id:223, text: "Klippe" }
    { group:28, id:224, text: "Henna" }
    { group:28, id:225, text: "Bibliothek von Alexandria" }
    { group:28, id:226, text: "Zoo" }
    { group:28, id:227, text: "Caesareum" }
    { group:28, id:228, text: "Pharos-Leuchtturm" }
    { group:28, id:229, text: "Kleines königliches Grab" }
    { group:28, id:230, text: "Abu Simbel" }
    { group:28, id:231, text: "Handwerkergilde" }
    { group:28, id:232, text: "Lampenmacher" }
    { group:28, id:233, text: "Farbhersteller" }
    { group:28, id:234, text: "Mittleres königliches Grab" }
    { group:28, id:235, text: "Großes königliches Grab" }
    { group:28, id:236, text: "Prächtiges königliches Grab" }
    { group:29, id:0, text: "Primitive Hütte" }
    { group:29, id:1, text: "Stabile Hütte" }
    { group:29, id:2, text: "Ärmliche Baracke" }
    { group:29, id:3, text: "Einfache Baracke" }
    { group:29, id:4, text: "Raues Häuschen" }
    { group:29, id:5, text: "Gewöhnliches Häuschen" }
    { group:29, id:6, text: "Bescheidenes Gehöft" }
    { group:29, id:7, text: "Geräumiges Gehöft" }
    { group:29, id:8, text: "Bescheidene Wohnung" }
    { group:29, id:9, text: "Geräumige Wohnung" }
    { group:29, id:10, text: "Einfache Residenz" }
    { group:29, id:11, text: "Geräumige Residenz" }
    { group:29, id:12, text: "Elegante Residenz" }
    { group:29, id:13, text: "Vornehme Residenz" }
    { group:29, id:14, text: "Einfaches Anwesen" }
    { group:29, id:15, text: "Geräumiges Anwesen" }
    { group:29, id:16, text: "Elegantes Anwesen" }
    { group:29, id:17, text: "Stattliches Anwesen" }
    { group:29, id:18, text: "Bescheidenes Landgut" }
    { group:29, id:19, text: "Palastartiges Landgut" }
    { group:29, id:20, text: "Primitive Hütten" }
    { group:29, id:21, text: "Stabile Hütten" }
    { group:29, id:22, text: "Ärmliche Baracken" }
    { group:29, id:23, text: "Einfache Baracken" }
    { group:29, id:24, text: "Raue Häuschen" }
    { group:29, id:25, text: "Gewöhnliche Häuschen" }
    { group:29, id:26, text: "Bescheidene Gehöfte" }
    { group:29, id:27, text: "Geräumige Gehöfte" }
    { group:29, id:28, text: "Bescheidene Wohnungen" }
    { group:29, id:29, text: "Geräumige Wohnungen" }
    { group:29, id:30, text: "Einfache Residenzen" }
    { group:29, id:31, text: "Geräumige Residenzen" }
    { group:29, id:32, text: "Elegante Residenzen" }
    { group:29, id:33, text: "Vornehme Residenzen" }
    { group:29, id:34, text: "Einfache Anwesen" }
    { group:29, id:35, text: "Geräumige Anwesen" }
    { group:29, id:36, text: "Elegante Anwesen" }
    { group:29, id:37, text: "Stattliche Anwesen" }
    { group:29, id:38, text: "Bescheidene Landgüter" }
    { group:29, id:39, text: "Palastartige Landgüter" }
    { group:29, id:40, text: "Primitive Hütten:" }
    { group:29, id:41, text: "Stabile Hütten:" }
    { group:29, id:42, text: "Ärmliche Baracken:" }
    { group:29, id:43, text: "Einfache Baracken:" }
    { group:29, id:44, text: "Raue Häuschen:" }
    { group:29, id:45, text: "Gewöhnliche Häuschen:" }
    { group:29, id:46, text: "Bescheidene Gehöfte:" }
    { group:29, id:47, text: "Geräumige Gehöfte:" }
    { group:29, id:48, text: "Bescheidene Wohnungen:" }
    { group:29, id:49, text: "Geräumige Wohnungen:" }
    { group:29, id:50, text: "Einfache Residenzen:" }
    { group:29, id:51, text: "Geräumige Residenzen:" }
    { group:29, id:52, text: "Elegante Residenzen:" }
    { group:29, id:53, text: "Vornehme Residenzen:" }
    { group:29, id:54, text: "Einfache Anwesen:" }
    { group:29, id:55, text: "Geräumige Anwesen:" }
    { group:29, id:56, text: "Elegante Anwesen:" }
    { group:29, id:57, text: "Stattliche Anwesen:" }
    { group:29, id:58, text: "Bescheidene Landgüter:" }
    { group:29, id:59, text: "Palastartige Landgüter:" }
    { group:30, id:0, text: "Pharao/Cleopatra spielen" }
    { group:30, id:1, text: "Pharao Demo spielen" }
    { group:30, id:2, text: "  Activision Webseite " }
    { group:30, id:3, text: "Missions-Editor" }
    { group:30, id:4, text: "Beenden " }
    { group:30, id:5, text: "Größte Familien" }
    { group:31, id:0, text: "Gebt einen Familiennamen ein" }
    { group:31, id:1, text: "Rechtsklick zum Fortfahren" }
    { group:32, id:0, text: "Dorfältester" }
    { group:32, id:1, text: "Dorfadeliger" }
    { group:32, id:2, text: "Königlicher Gelehrter" }
    { group:32, id:3, text: "Königlicher Schreiber" }
    { group:32, id:4, text: "Königlicher Richter" }
    { group:32, id:5, text: "Königlicher Bürgermeister" }
    { group:32, id:6, text: "Königlicher Gouverneur" }
    { group:32, id:7, text: "Nomarch" }
    { group:32, id:8, text: "Kanzler" }
    { group:32, id:9, text: "Wesir" }
    { group:32, id:10, text: "Pharao" }
    { group:32, id:11, text: "O Dorfältester" }
    { group:32, id:12, text: "O Dorfadeliger" }
    { group:32, id:13, text: "O Königlicher Gelehrter" }
    { group:32, id:14, text: "O Königlicher Schreiber" }
    { group:32, id:15, text: "O Königlicher Richter" }
    { group:32, id:16, text: "O Königlicher Bürgermeister" }
    { group:32, id:17, text: "O Königlicher Gouverneur" }
    { group:32, id:18, text: "O Nomarch" }
    { group:32, id:19, text: "O Kanzler" }
    { group:32, id:20, text: "O Wesir" }
    { group:32, id:21, text: "O Großer Pharao" }
    { group:32, id:22, text: "Triviale Mission" }
    { group:32, id:23, text: "Sehr einfache Mission" }
    { group:32, id:24, text: "Leichte Mission" }
    { group:32, id:25, text: "Etwas leichte Mission" }
    { group:32, id:26, text: "Standard-Mission" }
    { group:32, id:27, text: "Etwas schwere Mission" }
    { group:32, id:28, text: "Schwere Mission" }
    { group:32, id:29, text: "Sehr schwere Mission" }
    { group:32, id:30, text: "Extrem schwere Mission" }
    { group:32, id:31, text: "Praktisch unmögliche Mission" }
    { group:33, id:0, text: "Winzige Karte" }
    { group:33, id:1, text: "Kleine Karte" }
    { group:33, id:2, text: "Mittlere Karte" }
    { group:33, id:3, text: "Große Karte" }
    { group:33, id:4, text: "Riesige Karte" }
    { group:33, id:5, text: "Enorme Karte" }
    { group:33, id:6, text: "Abbrechen" }
    { group:34, id:0, text: "Keine Invasoren" }
    { group:34, id:1, text: "Feindliche Armee" }
    { group:34, id:2, text: "Ägyptische Armee" }
    { group:34, id:3, text: "Armee des Pharaos" }
    { group:34, id:4, text: "Beduinen-Armee" }
    { group:35, id:0, text: "Ägyptische Stadt fällt" }
    { group:35, id:1, text: "Fremde Stadt erobert" }
    { group:35, id:2, text: "Handelsroute jetzt verfügbar" }
    { group:35, id:3, text: "Handelsroute wird geschlossen" }
    { group:35, id:4, text: "Handelsstadt unter Belagerung" }
    { group:36, id:0, text: "Nahrungskette angreifen" }
    { group:36, id:1, text: "Goldvorräte angreifen" }
    { group:36, id:2, text: "Beste Gebäude angreifen" }
    { group:36, id:3, text: "Truppen angreifen" }
    { group:36, id:4, text: "Zufälliger Angriff" }
    { group:37, id:0, text: "Hyksos" }
    { group:37, id:1, text: "Seevölker" }
    { group:37, id:2, text: "Hethiter" }
    { group:37, id:3, text: "Mitanni" }
    { group:37, id:4, text: "Kuschiten" }
    { group:37, id:5, text: "Libyer" }
    { group:37, id:6, text: "Nubier" }
    { group:37, id:7, text: "Kanaaniter" }
    { group:37, id:8, text: "Assyrer" }
    { group:37, id:9, text: "Römer" }
    { group:37, id:10, text: "Phönizier" }
    { group:37, id:11, text: "Perser" }
    { group:37, id:12, text: "Ägypter" }
    { group:37, id:13, text: "Beduinen" }
    { group:37, id:14, text: "Ein Hyksos-Soldat" }
    { group:37, id:15, text: "Ein Soldat der Seevölker" }
    { group:37, id:16, text: "Ein hethitischer Soldat" }
    { group:37, id:17, text: "Ein Mitanni-Soldat" }
    { group:37, id:18, text: "Ein kuschiitischer Soldat" }
    { group:37, id:19, text: "Ein libyscher Soldat" }
    { group:37, id:20, text: "Ein nubischer Soldat" }
    { group:37, id:21, text: "Ein kanaanitischer Soldat" }
    { group:37, id:22, text: "Ein assyrischer Soldat" }
    { group:37, id:23, text: "Ein römischer Soldat" }
    { group:37, id:24, text: "Ein phönizischer Soldat" }
    { group:37, id:25, text: "Ein persischer Soldat" }
    { group:37, id:26, text: "Ein ägyptischer Soldat" }
    { group:37, id:27, text: "Ein Beduinen-Soldat" }
    { group:37, id:28, text: "eine Hyksos-Armee" }
    { group:37, id:29, text: "eine Armee der Seevölker" }
    { group:37, id:30, text: "eine hethitische Armee" }
    { group:37, id:31, text: "eine Mitanni-Armee" }
    { group:37, id:32, text: "eine kuschitische Armee" }
    { group:37, id:33, text: "eine libysche Armee" }
    { group:37, id:34, text: "eine nubische Armee" }
    { group:37, id:35, text: "eine kanaanitische Armee" }
    { group:37, id:36, text: "eine assyrische Armee" }
    { group:37, id:37, text: "eine römische Armee" }
    { group:37, id:38, text: "eine phönizische Armee" }
    { group:37, id:39, text: "eine persische Armee" }
    { group:37, id:40, text: "eine ägyptische Armee" }
    { group:37, id:41, text: "eine Beduinen-Armee" }
    { group:38, id:0, text: "Spezielle Ereignisse" }
    { group:38, id:1, text: "Erdbeben" }
    { group:38, id:2, text: "Gladiatorenaufstand" }
    { group:38, id:3, text: "Wechsel des Pharaos" }
    { group:38, id:4, text: "Seehandelsproblem" }
    { group:38, id:5, text: "Landhandelsproblem" }
    { group:38, id:6, text: "Pharao erhöht Löhne" }
    { group:38, id:7, text: "Pharao senkt Löhne" }
    { group:38, id:8, text: "Verseuchtes Wasser" }
    { group:38, id:9, text: "Goldminen-Einsturz" }
    { group:38, id:10, text: "Lehmgruben überflutet" }
    { group:38, id:11, text: "In Verwendung" }
    { group:38, id:12, text: "Zeitpunkt" }
    { group:38, id:13, text: "Zufällig" }
    { group:39, id:0, text: "Unsere Stadt" }
    { group:39, id:1, text: "Pharao-Handelsstadt" }
    { group:39, id:2, text: "Pharao-Stadt" }
    { group:39, id:3, text: "Ägyptische Handelsstadt" }
    { group:39, id:4, text: "Ägyptische Stadt" }
    { group:39, id:5, text: "Fremde Handelsstadt" }
    { group:39, id:6, text: "Fremde Stadt" }
    { group:40, id:0, text: "Keine" }
    { group:40, id:1, text: "Gering" }
    { group:40, id:2, text: "Durchschnittlich" }
    { group:40, id:3, text: "Groß" }
    { group:41, id:0, text: "Nirgendwo" }
    { group:41, id:1, text: "Nichts" }
    { group:41, id:2, text: "Nichts" }
    { group:41, id:3, text: "Nichts" }
    { group:41, id:4, text: "Nichts" }
    { group:41, id:5, text: "Straße" }
    { group:41, id:6, text: "Lehmmauer" }
    { group:41, id:7, text: "Bewässerungsgraben" }
    { group:41, id:8, text: "Wasserlift" }
    { group:41, id:9, text: "Nichts" }
    { group:41, id:10, text: "Primitive Hütte" }
    { group:41, id:11, text: "Stabile Hütte" }
    { group:41, id:12, text: "Ärmliche Baracke" }
    { group:41, id:13, text: "Einfache Baracke" }
    { group:41, id:14, text: "Raues Häuschen" }
    { group:41, id:15, text: "Gewöhnliches Häuschen" }
    { group:41, id:16, text: "Bescheidenes Gehöft" }
    { group:41, id:17, text: "Geräumiges Gehöft" }
    { group:41, id:18, text: "Bescheidene Wohnung" }
    { group:41, id:19, text: "Geräumige Wohnung" }
    { group:41, id:20, text: "Einfache Residenz" }
    { group:41, id:21, text: "Geräumige Residenz" }
    { group:41, id:22, text: "Elegante Residenz" }
    { group:41, id:23, text: "Vornehme Residenz" }
    { group:41, id:24, text: "Einfaches Anwesen" }
    { group:41, id:25, text: "Geräumiges Anwesen" }
    { group:41, id:26, text: "Elegantes Anwesen" }
    { group:41, id:27, text: "Stattliches Anwesen" }
    { group:41, id:28, text: "Bescheidenes Landgut" }
    { group:41, id:29, text: "Palastartiges Landgut" }
    { group:41, id:30, text: "Musikpavillon" }
    { group:41, id:31, text: "Bude" }
    { group:41, id:32, text: "Senet-Haus" }
    { group:41, id:33, text: "Pavillon" }
    { group:41, id:34, text: "Konservatorium" }
    { group:41, id:35, text: "Tanzschule" }
    { group:41, id:36, text: "Gauklerschule" }
    { group:41, id:37, text: "Streitwagen-Training" }
    { group:41, id:38, text: "Platz" }
    { group:41, id:39, text: "Gärten" }
    { group:41, id:40, text: "Infanterie-Fort" }
    { group:41, id:41, text: "Kleine Statue" }
    { group:41, id:42, text: "Mittlere Statue" }
    { group:41, id:43, text: "Große Statue" }
    { group:41, id:44, text: "Bogenschützen" }
    { group:41, id:45, text: "Infanterie" }
    { group:41, id:46, text: "Apotheke" }
    { group:41, id:47, text: "Leichenhalle" }
    { group:41, id:48, text: "Monumente" }
    { group:41, id:49, text: "Zahnarzt" }
    { group:41, id:50, text: "Verteilzentrum" }
    { group:41, id:51, text: "Schreiberschule" }
    { group:41, id:52, text: "Wasserüberquerungen" }
    { group:41, id:53, text: "Bibliothek" }
    { group:41, id:54, text: "Nichts" }
    { group:41, id:55, text: "Polizeistation" }
    { group:41, id:56, text: "unbenutzt 1315" }
    { group:41, id:57, text: "Forts" }
    { group:41, id:58, text: "Lehm-Torhaus" }
    { group:41, id:59, text: "Lehm-Turm" }
    { group:41, id:60, text: "Tempel des Osiris" }
    { group:41, id:61, text: "Tempel des Ra" }
    { group:41, id:62, text: "Tempel des Ptah" }
    { group:41, id:63, text: "Tempel des Seth" }
    { group:41, id:64, text: "Tempel der Bast" }
    { group:41, id:65, text: "Tempelkomplex des Osiris" }
    { group:41, id:66, text: "Tempelkomplex des Ra" }
    { group:41, id:67, text: "Tempelkomplex des Ptah" }
    { group:41, id:68, text: "Tempelkomplex des Seth" }
    { group:41, id:69, text: "Tempelkomplex der Bast" }
    { group:41, id:70, text: "Basar" }
    { group:41, id:71, text: "Getreidespeicher" }
    { group:41, id:72, text: "Lagerplatz" }
    { group:41, id:73, text: "Lagerplätze" }
    { group:41, id:74, text: "Schiffsbauer" }
    { group:41, id:75, text: "Dock" }
    { group:41, id:76, text: "Fischerkai" }
    { group:41, id:77, text: "Persönliches Anwesen" }
    { group:41, id:78, text: "Familienanwesen" }
    { group:41, id:79, text: "Dynastieanwesen" }
    { group:41, id:80, text: "unbenutzt 1339" }
    { group:41, id:81, text: "Architektenposten" }
    { group:41, id:82, text: "Kleine Brücke" }
    { group:41, id:83, text: "Große Brücke" }
    { group:41, id:84, text: "Dorfpalast" }
    { group:41, id:85, text: "Stadtpalast" }
    { group:41, id:86, text: "Steuereintreiber" }
    { group:41, id:87, text: "Steuereintreiber" }
    { group:41, id:88, text: "unbenutzt 1347" }
    { group:41, id:89, text: "unbenutzt 1348" }
    { group:41, id:90, text: "Wasserlift" }
    { group:41, id:91, text: "Verschönerung" }
    { group:41, id:92, text: "Brunnen" }
    { group:41, id:93, text: "Nichts" }
    { group:41, id:94, text: "Akademie" }
    { group:41, id:95, text: "Rekrutierer" }
    { group:41, id:96, text: "Nichts" }
    { group:41, id:97, text: "Nichts" }
    { group:41, id:98, text: "Orakel" }
    { group:41, id:99, text: "Brennende Ruine" }
    { group:41, id:100, text: "Gerstenfarm" }
    { group:41, id:101, text: "Flachsfarm" }
    { group:41, id:102, text: "Getreidefarm" }
    { group:41, id:103, text: "Salatfarm" }
    { group:41, id:104, text: "Granatapfelfarm" }
    { group:41, id:105, text: "Kichererbsenfarm" }
    { group:41, id:106, text: "Einfacher Steinbruch" }
    { group:41, id:107, text: "Kalksteinbruch" }
    { group:41, id:108, text: "Holzfäller" }
    { group:41, id:109, text: "Lehmgrube" }
    { group:41, id:110, text: "Brauerei" }
    { group:41, id:111, text: "Weber" }
    { group:41, id:112, text: "Waffenschmiede" }
    { group:41, id:113, text: "Juwelier" }
    { group:41, id:114, text: "Töpfer" }
    { group:41, id:115, text: "Jagdhütte " }
    { group:41, id:116, text: "Gras " }
    { group:41, id:117, text: "Bäume " }
    { group:41, id:118, text: "Wasser " }
    { group:41, id:119, text: "Erdbeben " }
    { group:41, id:120, text: "Gestrüpp " }
    { group:41, id:121, text: "Felsen " }
    { group:41, id:122, text: "Wiese " }
    { group:41, id:123, text: "unbenutzt 1382" }
    { group:41, id:124, text: "unbenutzt 1383" }
    { group:41, id:125, text: "Straße " }
    { group:41, id:126, text: "Invasionspunkt " }
    { group:41, id:127, text: "Eingangspunkt " }
    { group:41, id:128, text: "Ausgangspunkt " }
    { group:41, id:129, text: "unbenutzt 1388 " }
    { group:41, id:130, text: "Flusseingang " }
    { group:41, id:131, text: "Flussausgang " }
    { group:41, id:132, text: "Fischereipunkt " }
    { group:41, id:133, text: "Killer-Punkt " }
    { group:41, id:134, text: "Überschwemmungsgebiet " }
    { group:41, id:135, text: "Bewässerung " }
    { group:41, id:136, text: "Fähranleger " }
    { group:41, id:137, text: "Straßensystem " }
    { group:41, id:138, text: "Straßensperre " }
    { group:41, id:139, text: "Karten-Beutepunkt " }
    { group:41, id:140, text: "Schrein des Osiris" }
    { group:41, id:141, text: "Schrein des Ra" }
    { group:41, id:142, text: "Schrein des Ptah" }
    { group:41, id:143, text: "Schrein des Seth" }
    { group:41, id:144, text: "Schrein der Bast" }
    { group:41, id:145, text: "Schrein Gott5" }
    { group:41, id:146, text: "Schrein Gott6" }
    { group:41, id:147, text: "Schrein Gott7" }
    { group:41, id:148, text: "Schrein Gott8" }
    { group:41, id:149, text: "Schrein Gott9" }
    { group:41, id:150, text: "Schrein" }
    { group:41, id:151, text: "Temp Klein5" }
    { group:41, id:152, text: "Temp Klein6" }
    { group:41, id:153, text: "Temp Klein7" }
    { group:41, id:154, text: "Temp Klein8" }
    { group:41, id:155, text: "Temp Klein9" }
    { group:41, id:156, text: "Temp Groß5" }
    { group:41, id:157, text: "Temp Groß6" }
    { group:41, id:158, text: "Temp Groß7" }
    { group:41, id:159, text: "Temp Groß8" }
    { group:41, id:160, text: "Temp Groß9" }
    { group:41, id:161, text: "Goldmine" }
    { group:41, id:162, text: "Edelsteinmine" }
    { group:41, id:163, text: "Gewöhnlicher Fels" }
    { group:41, id:164, text: "Gold-Fels" }
    { group:41, id:165, text: "Edelstein-Fels" }
    { group:41, id:166, text: "Veredelungs-Fels" }
    { group:41, id:167, text: "Feuerwache" }
    { group:41, id:168, text: "Ziegelmauer" }
    { group:41, id:169, text: "Mauer" }
    { group:41, id:170, text: "Ziegel-Torhaus" }
    { group:41, id:171, text: "Torhaus" }
    { group:41, id:172, text: "Ziegel-Turm" }
    { group:41, id:173, text: "Turm" }
    { group:41, id:174, text: "Lehm-Strukturen" }
    { group:41, id:175, text: "Ziegel-Strukturen" }
    { group:41, id:176, text: "Verteidigungsanlagen" }
    { group:41, id:177, text: "Zimmerergilde" }
    { group:41, id:178, text: "Maurergilde" }
    { group:41, id:179, text: "Steinmetzgilde" }
    { group:41, id:180, text: "Wasserversorgung" }
    { group:41, id:181, text: "Transportkai" }
    { group:41, id:182, text: "Kriegsschiffwerft" }
    { group:41, id:183, text: "Pyramide" }
    { group:41, id:184, text: "Gerichtsgebäude" }
    { group:41, id:185, text: "Militärakademie 2" }
    { group:41, id:186, text: "Militärakademie 3" }
    { group:41, id:187, text: "Dorfpalast" }
    { group:41, id:188, text: "Stadtpalast" }
    { group:41, id:189, text: "Großstadtpalast" }
    { group:41, id:190, text: "Basar 2" }
    { group:41, id:191, text: "Getreidespeicher 2" }
    { group:41, id:192, text: "Dock 2" }
    { group:41, id:193, text: "Lagerplatz 2" }
    { group:41, id:194, text: "Viehfarm" }
    { group:41, id:195, text: "Schilfsammler" }
    { group:41, id:196, text: "Feigenfarm" }
    { group:41, id:197, text: "Marschland" }
    { group:41, id:198, text: "Sanddüne" }
    { group:41, id:199, text: "Arbeitslager" }
    { group:41, id:200, text: "Lehm-Torhaus" }
    { group:41, id:201, text: "Ziegel-Torhaus" }
    { group:41, id:202, text: "Torhaus" }
    { group:41, id:203, text: "Papyrusmacher" }
    { group:41, id:204, text: "Ziegelhersteller" }
    { group:41, id:205, text: "Wagenbauer" }
    { group:41, id:206, text: "Arzt" }
    { group:41, id:207, text: "unbenutzt 1466" }
    { group:41, id:208, text: "unbenutzt 1467" }
    { group:41, id:209, text: "Festplatz" }
    { group:41, id:210, text: "Sphinx" }
    { group:41, id:211, text: "Tempelkomplex-Erweiterung" }
    { group:41, id:212, text: "Tempelkomplex-Erweiterung" }
    { group:41, id:213, text: "unbenutzt 1472" }
    { group:41, id:214, text: "Ausschiffer-Punkt" }
    { group:41, id:215, text: "unbenutzt 1474" }
    { group:41, id:216, text: "Granitbruch" }
    { group:41, id:217, text: "Kupfermine" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Sandsteinbruch" }
    { group:41, id:222, text: "Mausoleum" }
    { group:41, id:223, text: "Klippe" }
    { group:41, id:224, text: "Hennafarm" }
    { group:41, id:225, text: "Bibliothek von Alexandria" }
    { group:41, id:226, text: "Zoo" }
    { group:41, id:227, text: "Caesareum" }
    { group:41, id:228, text: "Pharos-Leuchtturm" }
    { group:41, id:229, text: "Kleines königliches Grab" }
    { group:41, id:230, text: "Abu Simbel" }
    { group:41, id:231, text: "Handwerkergilde" }
    { group:41, id:232, text: "Lampenmacher" }
    { group:41, id:233, text: "Farbhersteller" }
    { group:41, id:234, text: "Mittleres königliches Grab" }
    { group:41, id:235, text: "Großes königliches Grab" }
    { group:41, id:236, text: "Prächtiges königliches Grab" }
    { group:42, id:0, text: "Anzeigeoptionen" }
    { group:42, id:1, text: "Vollbild" }
    { group:42, id:2, text: "Fenster-Modus" }
    { group:42, id:3, text: "640 x 480 Auflösung" }
    { group:42, id:4, text: "800 x 600 Auflösung" }
    { group:42, id:5, text: "1024 x 768 Auflösung" }
    { group:42, id:6, text: "Abbrechen" }
    { group:43, id:0, text: "Eure Stadt wird gespeichert" }
    { group:43, id:1, text: "Gespeichertes Spiel wird geladen" }
    { group:43, id:2, text: "Datei existiert nicht" }
    { group:43, id:3, text: "Mission wird gespeichert" }
    { group:43, id:4, text: "Mission wird geladen" }
    { group:43, id:5, text: "Fortfahren?" }
    { group:43, id:6, text: "Datei löschen" }
    { group:44, id:0, text: "Objekt hinzufügen" }
    { group:44, id:1, text: "Objekte bearbeiten" }
    { group:44, id:2, text: "Objekt löschen" }
    { group:44, id:3, text: "Allgemein" }
    { group:44, id:4, text: "Karte importieren" }
    { group:44, id:5, text: "Kauft" }
    { group:44, id:6, text: "nicht frei" }
    { group:44, id:7, text: "Ok" }
    { group:44, id:8, text: "Einfache Grafik" }
    { group:44, id:9, text: "Stadt" }
    { group:44, id:10, text: "Region" }
    { group:44, id:11, text: "Schlachtmarkierung" }
    { group:44, id:12, text: "frei" }
    { group:44, id:13, text: "Startdatum" }
    { group:44, id:14, text: "Pharao-Anfragen" }
    { group:44, id:15, text: "Invasionen" }
    { group:44, id:16, text: "Annehmen" }
    { group:44, id:17, text: "Abbrechen" }
    { group:44, id:18, text: "Aktueller Zustand des Königreichs" }
    { group:44, id:19, text: "Keine Anfragen" }
    { group:44, id:20, text: "Keine Invasionen" }
    { group:44, id:21, text: "Mission noch nicht gewonnen" }
    { group:44, id:22, text: "Eine Invasion planen" }
    { group:44, id:23, text: "Freier Platz" }
    { group:44, id:24, text: "in" }
    { group:44, id:25, text: "Anfrage abbestellen" }
    { group:44, id:26, text: "Invasion abbestellen" }
    { group:44, id:27, text: "von" }
    { group:44, id:28, text: "Landroute" }
    { group:44, id:29, text: "Seeroute" }
    { group:44, id:30, text: "Armee-Markierung" }
    { group:44, id:31, text: "Feind-Markierung" }
    { group:44, id:32, text: "Route" }
    { group:44, id:33, text: "Forderung" }
    { group:44, id:34, text: "Kosten" }
    { group:44, id:35, text: "Ressourcen" }
    { group:44, id:36, text: "Verkauft" }
    { group:44, id:37, text: "Kurzbeschreibung" }
    { group:44, id:38, text: "Kurzbeschreibung dieser Mission für Spieler. Geschichte, Ziele und Tipps etc." }
    { group:44, id:39, text: "Anfangskapital" }
    { group:44, id:40, text: "Anfragen" }
    { group:44, id:41, text: "Feind ist" }
    { group:44, id:42, text: "Invasionen" }
    { group:44, id:43, text: "Hauptstadt liefert Getreide?" }
    { group:44, id:44, text: "Erlaubte Gebäude" }
    { group:44, id:45, text: "Siegbedingungen" }
    { group:44, id:46, text: "Anpassen" }
    { group:44, id:47, text: "Erlaubte Strukturen" }
    { group:44, id:48, text: "Siegbedingungen" }
    { group:44, id:49, text: "Spezielle Ereignisse" }
    { group:44, id:50, text: "Benötigte Kultur" }
    { group:44, id:51, text: "Benötigter Wohlstand" }
    { group:44, id:52, text: "Anzahl Monumente" }
    { group:44, id:53, text: "Benötigtes Königreich" }
    { group:44, id:54, text: "Zeitlimit (Verlustzeit)" }
    { group:44, id:55, text: "Überleben (Gewinnzeit)" }
    { group:44, id:56, text: "Gewinn-Bevölkerung" }
    { group:44, id:57, text: "Benötige Erdbeben-Punkt" }
    { group:44, id:58, text: "Erdbeben-Punkt gesetzt" }
    { group:44, id:59, text: "Kein Eingangspunkt" }
    { group:44, id:60, text: "Keine Bevölkerungspunkte" }
    { group:44, id:61, text: "Kein Ausgangspunkt" }
    { group:44, id:62, text: "Bevölkerungspunkte gesetzt" }
    { group:44, id:63, text: "Keine Invasionspunkte" }
    { group:44, id:64, text: "1 Invasionspunkt" }
    { group:44, id:65, text: "Invasionspunkte" }
    { group:44, id:66, text: "Keine Flusspunkte" }
    { group:44, id:67, text: "Flusspunkte gesetzt" }
    { group:44, id:68, text: "Pharao-Geschenk" }
    { group:44, id:69, text: "Schlachtmarkierung" }
    { group:44, id:70, text: "Pfad" }
    { group:44, id:71, text: "Befehl" }
    { group:44, id:72, text: "Möchte" }
    { group:44, id:73, text: "Königreich" }
    { group:44, id:74, text: "Meilensteine bei" }
    { group:44, id:75, text: "Speichern" }
    { group:44, id:76, text: "Gelände gesetzt" }
    { group:44, id:77, text: "Feuchtes Klima" }
    { group:44, id:78, text: "Normales Klima" }
    { group:44, id:79, text: "Trockenes Klima" }
    { group:44, id:80, text: "Treibgut an?" }
    { group:44, id:81, text: "Expansion bei" }
    { group:44, id:82, text: "Erweiterte Positionen" }
    { group:44, id:83, text: "Angebots-/Nachfrageniveaus festlegen" }
    { group:44, id:84, text: "Keine" }
    { group:44, id:85, text: "Niedrig" }
    { group:44, id:86, text: "Mittel" }
    { group:44, id:87, text: "Hoch" }
    { group:44, id:88, text: "Startbedingungen" }
    { group:44, id:89, text: "Startdatum anpassen" }
    { group:44, id:90, text: "Eintrag 90 - nur als Markierung verwendet" }
    { group:44, id:91, text: "Meilenstein - 25%" }
    { group:44, id:92, text: "Meilenstein - 50%" }
    { group:44, id:93, text: "Meilenstein - 75%" }
    { group:44, id:94, text: "Nachfrageänderungen" }
    { group:44, id:95, text: "Ereignisse" }
    { group:44, id:96, text: "Ereignis hinzufügen" }
    { group:44, id:97, text: "Ereignis löschen" }
    { group:44, id:98, text: "in Route" }
    { group:44, id:99, text: "fällt" }
    { group:44, id:100, text: "steigt" }
    { group:44, id:101, text: "Nachfrage nach dieser Ware" }
    { group:44, id:102, text: "unbenutzt 1601" }
    { group:44, id:103, text: "fällt um" }
    { group:44, id:104, text: "steigt um" }
    { group:44, id:105, text: "ungültiges Auslöse-Ereignis" }
    { group:44, id:106, text: "TIPP: Verwendet die Komma- und Punkt-Tasten, um schnell durch diese und andere Objekte zu navigieren." }
    { group:44, id:107, text: "Freies Spiel (Kein Sieg/Niederlage)" }
    { group:44, id:108, text: "Anfangsrang" }
    { group:44, id:109, text: "Gelände" }
    { group:44, id:110, text: "Feinde" }
    { group:44, id:111, text: "Invasionen" }
    { group:44, id:112, text: "Keine militärische Aktivität" }
    { group:44, id:113, text: "Kleinere Scharmützel" }
    { group:44, id:114, text: "Etwas militärische Aktivität" }
    { group:44, id:115, text: "Viel militärische Aktivität" }
    { group:44, id:116, text: "Stadt wird angegriffen" }
    { group:44, id:117, text: "Rang" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "Hauptstadt ernährt?" }
    { group:44, id:120, text: "Kartengröße" }
    { group:44, id:121, text: "Winzige Landschaft" }
    { group:44, id:122, text: "Kleine Landschaft" }
    { group:44, id:123, text: "Durchschnittliche Landschaft" }
    { group:44, id:124, text: "Große Landschaft" }
    { group:44, id:125, text: "Sehr großes Land" }
    { group:44, id:126, text: "Enormes Land" }
    { group:44, id:127, text: "Siegbedingungen" }
    { group:44, id:128, text: "Keine" }
    { group:44, id:129, text: "Kultur" }
    { group:44, id:130, text: "Wohlstand" }
    { group:44, id:131, text: "Monument" }
    { group:44, id:132, text: "Königreich" }
    { group:44, id:133, text: "Bevölkerung" }
    { group:44, id:134, text: "Jahre maximal" }
    { group:44, id:135, text: "Überlebensjahre" }
    { group:44, id:136, text: "Zur Stadt gehen" }
    { group:44, id:137, text: "Benötige Flusseingang" }
    { group:44, id:138, text: "Benötige Flussausgang" }
    { group:44, id:139, text: "Ereignis" }
    { group:44, id:140, text: "Monat" }
    { group:44, id:141, text: "zwischen" }
    { group:44, id:142, text: "und" }
    { group:44, id:143, text: "Städte" }
    { group:44, id:144, text: "von Markierungen" }
    { group:44, id:145, text: "nach" }
    { group:44, id:146, text: "Menge" }
    { group:44, id:147, text: "Skala" }
    { group:44, id:148, text: "von" }
    { group:44, id:149, text: "innerhalb" }
    { group:44, id:150, text: "Monate" }
    { group:44, id:151, text: "Erfüllen-Ereignis" }
    { group:44, id:152, text: "Ablehnen-Ereignis" }
    { group:44, id:153, text: "Zu spät-Ereignis" }
    { group:44, id:154, text: "Verwirken-Ereignis" }
    { group:44, id:155, text: "Schlacht verloren-Ereignis" }
    { group:44, id:156, text: "Nächstes Ereignis" }
    { group:44, id:157, text: "Einmaliges Ereignis" }
    { group:44, id:158, text: "Wiederkehrendes Ereignis" }
    { group:44, id:159, text: "Nur ausgelöst" }
    { group:44, id:160, text: "Ausgelöst durch Gunst" }
    { group:44, id:161, text: "Pharao" }
    { group:44, id:162, text: "Stadt" }
    { group:44, id:163, text: "Kriegsschiffe" }
    { group:44, id:164, text: "Götter-Einstellungen" }
    { group:44, id:165, text: "Kein Schutzgott" }
    { group:44, id:166, text: "Route hinzufügen" }
    { group:44, id:167, text: "Route bearbeiten" }
    { group:44, id:168, text: "Route löschen" }
    { group:44, id:169, text: "Allgemeine Route" }
    { group:44, id:170, text: "Seehandelsroute" }
    { group:44, id:171, text: "Landhandelsroute" }
    { group:44, id:172, text: "Abstand" }
    { group:44, id:173, text: "Routenlänge" }
    { group:44, id:174, text: "Name" }
    { group:44, id:175, text: "Rang" }
    { group:44, id:176, text: "Tempelkomplex" }
    { group:44, id:177, text: "Zinssatz auf Schulden" }
    { group:44, id:178, text: "Überschwemmungsgebiets-Einstellungen" }
    { group:44, id:179, text: "Überschwemmung beginnt:" }
    { group:44, id:180, text: "Anfang Juni" }
    { group:44, id:181, text: "Ende Juni" }
    { group:44, id:182, text: "Anfang Juli" }
    { group:44, id:183, text: "Ende Juli" }
    { group:44, id:184, text: "Anfang August" }
    { group:44, id:185, text: "Ende August" }
    { group:44, id:186, text: "Anfang September" }
    { group:44, id:187, text: "Ende September" }
    { group:44, id:188, text: "Überschwemmung dauert:" }
    { group:44, id:189, text: "Zwei Monate" }
    { group:44, id:190, text: "Drei Monate" }
    { group:44, id:191, text: "Vier Monate" }
    { group:44, id:192, text: "Überschwemmungsqualität:" }
    { group:44, id:193, text: "Keine" }
    { group:44, id:194, text: "Schlecht" }
    { group:44, id:195, text: "Mittelmäßig" }
    { group:44, id:196, text: "Gut" }
    { group:44, id:197, text: "Ausgezeichnet" }
    { group:44, id:198, text: "Perfekt" }
    { group:44, id:199, text: "Flut fehlgeschlagen" }
    { group:44, id:200, text: "Perfekte Flut" }
    { group:44, id:201, text: "Monumente auswählen" }
    { group:44, id:202, text: "Aktueller Pharao:" }
    { group:44, id:203, text: "Spieler-Inkarnation:" }
    { group:44, id:204, text: "Königreichspreise festlegen" }
    { group:44, id:205, text: "Kauft" }
    { group:44, id:206, text: "Verkauft" }
    { group:44, id:207, text: "Annehmen" }
    { group:44, id:208, text: "Ablehnen" }
    { group:44, id:209, text: "Verschieben" }
    { group:44, id:210, text: "Wohnniveau" }
    { group:44, id:211, text: "Preise zurücksetzen" }
    { group:44, id:212, text: "Gott" }
    { group:44, id:213, text: "1 Karrenladung oder Steinblock = 100 Einheiten" }
    { group:44, id:214, text: "Diese Karte bearbeiten" }
    { group:44, id:215, text: "Diese Mission spielen" }
    { group:44, id:216, text: "Schwierigkeitsgrad" }
    { group:44, id:217, text: "Beenden" }
    { group:44, id:218, text: "Mission starten" }
    { group:44, id:219, text: "Abbrechen" }
    { group:44, id:220, text: "Vorherige Ergebnisse anzeigen" }
    { group:44, id:221, text: "Missionsziele anzeigen" }
    { group:44, id:222, text: "Königreichs-Editor" }
    { group:44, id:223, text: "Zurücksetzen" }
    { group:44, id:224, text: "Eingangspunkt gesetzt" }
    { group:44, id:225, text: "Ausgangspunkt gesetzt" }
    { group:44, id:226, text: "1 Flusspunkt gesetzt" }
    { group:44, id:227, text: "Spieler kämpft gegen Ägypten als" }
    { group:45, id:0, text: "Geschwindigkeitsoptionen" }
    { group:45, id:1, text: "Abbrechen" }
    { group:45, id:2, text: "Spielgeschwindigkeit" }
    { group:45, id:3, text: "Scrollgeschwindigkeit" }
    { group:45, id:4, text: "OK" }
    { group:46, id:0, text: "Tonoptionen" }
    { group:46, id:1, text: "Musik ist aus" }
    { group:46, id:2, text: "Musik ist an" }
    { group:46, id:3, text: "Sprache ist aus" }
    { group:46, id:4, text: "Sprache ist an" }
    { group:46, id:5, text: "Soundeffekte sind aus" }
    { group:46, id:6, text: "Soundeffekte sind an" }
    { group:46, id:7, text: "Stadtgeräusche sind aus" }
    { group:46, id:8, text: "Stadtgeräusche sind an" }
    { group:46, id:9, text: "Abbrechen" }
    { group:46, id:10, text: "Aktueller Audiostatus" }
    { group:46, id:11, text: "Lautstärke" }
    { group:46, id:12, text: "OK" }
    { group:47, id:0, text: "Eine entfernte Stadt" }
    { group:47, id:1, text: "Unsere Stadt!" }
    { group:47, id:2, text: "Diese Handelsroute ist noch nicht eingerichtet" }
    { group:47, id:3, text: "Kosten zum Öffnen" }
    { group:47, id:4, text: "Kauft" }
    { group:47, id:5, text: "Verkauft" }
    { group:47, id:6, text: " um Landhandelsroute zu öffnen" }
    { group:47, id:7, text: " um Wasserhandelsroute zu öffnen" }
    { group:47, id:8, text: "Zum Aufseher des Handels" }
    { group:47, id:9, text: "Klickt auf eine Stadt, um Informationen zu erhalten" }
    { group:47, id:10, text: "Gekauft" }
    { group:47, id:11, text: "Verkauft" }
    { group:47, id:12, text: "von" }
    { group:47, id:13, text: "Eine ägyptische Stadt" }
    { group:47, id:14, text: "Eine eroberte Stadt" }
    { group:47, id:15, text: "Eine feindliche Armee, die eine Stadt des Königreichs bedroht" }
    { group:47, id:16, text: "Eure Armee, die marschiert, um eine Stadt des Königreichs zu entsetzen" }
    { group:47, id:17, text: "Eure Armee, die zu Eurer Stadt zurückkehrt" }
    { group:47, id:18, text: "Der Schauplatz eines kürzlichen Scharmützels durch einfallende Barbaren" }
    { group:47, id:19, text: "Die Stadt des Pharaos" }
    { group:48, id:0, text: "Kleinster Pinsel" }
    { group:48, id:1, text: "Kleiner Pinsel" }
    { group:48, id:2, text: "Mittlerer Pinsel" }
    { group:48, id:3, text: "Großer Pinsel" }
    { group:48, id:4, text: "Größter Pinsel" }
    { group:48, id:5, text: "Eingangspunkt" }
    { group:48, id:6, text: "Ausgangspunkt" }
    { group:48, id:7, text: "Land anheben" }
    { group:48, id:8, text: "Land absenken" }
    { group:48, id:9, text: "Zugangsrampe" }
    { group:48, id:10, text: "Invasionspkt. 1 (Land)" }
    { group:48, id:11, text: "Invasionspkt. 2 (Land)" }
    { group:48, id:12, text: "Invasionspkt. 3 (Land)" }
    { group:48, id:13, text: "Invasionspkt. 4 (Land)" }
    { group:48, id:14, text: "Invasionspkt. 5 (Land)" }
    { group:48, id:15, text: "Invasionspkt. 6 (Land)" }
    { group:48, id:16, text: "Invasionspkt. 7 (Land)" }
    { group:48, id:17, text: "Invasionspkt. 8 (Land)" }
    { group:48, id:18, text: "Flusseingang" }
    { group:48, id:19, text: "Flussausgang" }
    { group:48, id:20, text: "Einheimischen-Hütte" }
    { group:48, id:21, text: "Einheimischen-Zentrum" }
    { group:48, id:22, text: "Einheimischen-Feld" }
    { group:48, id:23, text: "Fischereipunkt 1" }
    { group:48, id:24, text: "Fischereipunkt 2" }
    { group:48, id:25, text: "Fischereipunkt 3" }
    { group:48, id:26, text: "Fischereipunkt 4" }
    { group:48, id:27, text: "Fischereipunkt 5" }
    { group:48, id:28, text: "Fischereipunkt 6" }
    { group:48, id:29, text: "Fischereipunkt 7" }
    { group:48, id:30, text: "Fischereipunkt 8" }
    { group:48, id:31, text: "Killer-Spawn 1" }
    { group:48, id:32, text: "Killer-Spawn 2" }
    { group:48, id:33, text: "Killer-Spawn 3" }
    { group:48, id:34, text: "Killer-Spawn 4" }
    { group:48, id:35, text: "Wasser" }
    { group:48, id:36, text: "Überschwemmungsgebiet" }
    { group:48, id:37, text: "Bewässerungsgraben" }
    { group:48, id:38, text: "Marschland" }
    { group:48, id:39, text: "Beute-Spawn 1" }
    { group:48, id:40, text: "Beute-Spawn 2" }
    { group:48, id:41, text: "Beute-Spawn 3" }
    { group:48, id:42, text: "Beute-Spawn 4" }
    { group:48, id:43, text: "Gewöhnlicher Fels" }
    { group:48, id:44, text: "Erzführender Fels" }
    { group:48, id:45, text: "Gewöhnlicher Fels" }
    { group:48, id:46, text: "Spezieller Fels" }
    { group:48, id:47, text: "Sanddünen" }
    { group:48, id:48, text: "Invasionspkt. 9 (See)" }
    { group:48, id:49, text: "Invasionspkt. 10 (See)" }
    { group:48, id:50, text: "Invasionspkt. 11 (See)" }
    { group:48, id:51, text: "Invasionspkt. 12 (See)" }
    { group:48, id:52, text: "Invasionspkt. 13 (See)" }
    { group:48, id:53, text: "Invasionspkt. 14 (See)" }
    { group:48, id:54, text: "Invasionspkt. 15 (See)" }
    { group:48, id:55, text: "Invasionspkt. 16 (See)" }
    { group:48, id:56, text: "Ausschiffer-Pkt. 1" }
    { group:48, id:57, text: "Ausschiffer-Pkt. 2" }
    { group:48, id:58, text: "Ausschiffer-Pkt. 3" }
    { group:48, id:59, text: "Killer-Typ 1" }
    { group:48, id:60, text: "Killer-Typ 2" }
    { group:49, id:0, text: "Gras" }
    { group:49, id:1, text: "Bäume" }
    { group:49, id:2, text: "Wasser" }
    { group:49, id:3, text: "Erdbeben" }
    { group:49, id:4, text: "Gestrüpp" }
    { group:49, id:5, text: "Felsen" }
    { group:49, id:6, text: "Wiese" }
    { group:49, id:7, text: "Plateau" }
    { group:49, id:8, text: "Pinselgröße" }
    { group:49, id:9, text: "Zugangsrampe" }
    { group:49, id:10, text: "Straße" }
    { group:49, id:11, text: "Land anheben" }
    { group:49, id:12, text: "Land absenken" }
    { group:49, id:13, text: "Invasionspunkt" }
    { group:49, id:14, text: "Migrationspunkt" }
    { group:49, id:15, text: "Eingangspunkt" }
    { group:49, id:16, text: "Ausgangspunkt" }
    { group:49, id:17, text: "Flusspunkt" }
    { group:49, id:18, text: "Fluss EIN" }
    { group:49, id:19, text: "Fluss AUS" }
    { group:49, id:20, text: "Einheimische" }
    { group:49, id:21, text: "Einheimischen-Hütte" }
    { group:49, id:22, text: "Einheimischen-Zentrum" }
    { group:49, id:23, text: "Einheimischen-Feld" }
    { group:49, id:24, text: "Fischereigewässer" }
    { group:49, id:25, text: "Killer-Punkt" }
    { group:49, id:26, text: "Überschwemmungsgebiet" }
    { group:49, id:27, text: "Bewässerung" }
    { group:49, id:28, text: "Beute" }
    { group:49, id:29, text: "Marschland" }
    { group:49, id:30, text: "Sanddünen" }
    { group:49, id:31, text: "Ausschiffer-Punkt" }
    { group:49, id:32, text: "Killer-Typ" }
    { group:49, id:33, text: "Klippe" }
    { group:50, id:0, text: "Aufseher der Arbeiter" }
    { group:50, id:1, text: "Nahrungsproduktion und -verteilung" }
    { group:50, id:2, text: "Industrie und Handel" }
    { group:50, id:3, text: "Unterhaltung" }
    { group:50, id:4, text: "Religion" }
    { group:50, id:5, text: "Bildung" }
    { group:50, id:6, text: "Gesundheit und Hygiene" }
    { group:50, id:7, text: "Infrastruktur" }
    { group:50, id:8, text: "Regierung" }
    { group:50, id:9, text: "Militär" }
    { group:50, id:10, text: "Benötigt" }
    { group:50, id:11, text: "Vorhanden" }
    { group:50, id:12, text: "Beschäftigte Arbeitskräfte" }
    { group:50, id:13, text: "Arbeitslose Arbeitskräfte (" }
    { group:50, id:14, text: "Lohn/10" }
    { group:50, id:15, text: "Deben" }
    { group:50, id:16, text: "weniger als Königreichssatz von" }
    { group:50, id:17, text: "mehr als Königreichssatz von" }
    { group:50, id:18, text: "(Königreich zahlt" }
    { group:50, id:19, text: "Prognostizierte Lohnsumme dieses Jahr:" }
    { group:50, id:20, text: "Gesperrt" }
    { group:50, id:21, text: "Priorität" }
    { group:50, id:22, text: "Sektor" }
    { group:50, id:23, text: "Benötigt" }
    { group:50, id:24, text: "Vorhanden" }
    { group:50, id:25, text: "Prioritätsstufe" }
    { group:50, id:26, text: "Keine Priorität" }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Armeestatus" }
    { group:51, id:1, text: "Gehe zu" }
    { group:51, id:2, text: "Kompanie" }
    { group:51, id:3, text: "Zurück" }
    { group:51, id:4, text: "zum Fort" }
    { group:51, id:5, text: "Königreich" }
    { group:51, id:6, text: "Dienst" }
    { group:51, id:7, text: "in" }
    { group:51, id:8, text: "Wir haben keine Berichte über Bedrohungen für die Stadt." }
    { group:51, id:9, text: "Wir erhalten Berichte über Feinde, die sich der Stadt nähern." }
    { group:51, id:10, text: "Unsere Feinde sind in Sichtweite der Stadt." }
    { group:51, id:11, text: "Ein Bataillon der Truppen des Pharaos steht vor unseren Toren!" }
    { group:51, id:12, text: "Wir haben keine Anfragen für militärische Hilfe im Ausland." }
    { group:51, id:13, text: "Einige unserer Truppen werden im Ausland benötigt." }
    { group:51, id:14, text: "Unser Bataillon marschiert, um für das Königreich zu kämpfen." }
    { group:51, id:15, text: "Unser Bataillon kehrt zu unserer Stadt zurück." }
    { group:51, id:16, text: "Ihr habt keine Kompanien zu befehligen. Ihr müsst zuerst ein Fort bauen, um eine neue Kompanie unterzubringen." }
    { group:51, id:17, text: "Kompanie" }
    { group:51, id:18, text: "Erfahrung" }
    { group:51, id:19, text: "Marinestatus" }
    { group:51, id:20, text: "Kriegsschiff" }
    { group:51, id:21, text: "zur Werft" }
    { group:51, id:22, text: "Rumpf" }
    { group:51, id:23, text: "Stärke" }
    { group:51, id:24, text: "Besatzungsstatus" }
    { group:51, id:25, text: "Ihr habt keine Kriegsschiffe zu befehligen. Ihr müsst zuerst eine Werft für ein neues Kriegsschiff bauen." }
    { group:51, id:26, text: "Teile unserer Marine werden anderswo benötigt" }
    { group:51, id:27, text: "Unsere Kompanie segelt, um eine ägyptische Stadt zu retten" }
    { group:51, id:28, text: "Unsere Kompanie segelt zurück zu unserer Stadt" }
    { group:51, id:29, text: "im Ausland" }
    { group:51, id:30, text: "Entsenden" }
    { group:51, id:31, text: "jetzt" }
    { group:51, id:32, text: " und " }
    { group:52, id:0, text: "Königreich-Bewertung" }
    { group:52, id:1, text: "Ersparnisse von" }
    { group:52, id:2, text: "An Stadt geben" }
    { group:52, id:3, text: "Deben pro Monat" }
    { group:52, id:4, text: "Gehalt des Dorfältesten von" }
    { group:52, id:5, text: "Gehalt des Dorfadeligen von" }
    { group:52, id:6, text: "Gehalt des Königlichen Gelehrten von" }
    { group:52, id:7, text: "Gehalt des Königlichen Schreibers von" }
    { group:52, id:8, text: "Gehalt des Königlichen Richters von" }
    { group:52, id:9, text: "Gehalt des Königlichen Bürgermeisters von" }
    { group:52, id:10, text: "Gehalt des Königlichen Gouverneurs von" }
    { group:52, id:11, text: "Gehalt des Nomarchen von" }
    { group:52, id:12, text: "Gehalt des Kanzlers von" }
    { group:52, id:13, text: "Gehalt des Wesirs von" }
    { group:52, id:14, text: "Gehalt des Pharaos von" }
    { group:52, id:15, text: "Gehaltshöhe festlegen" }
    { group:52, id:16, text: "Geld an die Stadt geben" }
    { group:52, id:17, text: "Spende beträgt" }
    { group:52, id:18, text: "Geld geben" }
    { group:52, id:19, text: "Alles" }
    { group:52, id:20, text: "Aktuelle Anfragen" }
    { group:52, id:21, text: "Es gibt derzeit keine ausstehenden Anfragen." }
    { group:52, id:22, text: "Die öffentliche Meinung würde Eure Überreste den Schakalen überlassen." }
    { group:52, id:23, text: "Ihr seid beliebt bei Gauklern, die Euch in ihren Komödien verwenden." }
    { group:52, id:24, text: "Es wird weithin geglaubt, dass Eure bloße Anwesenheit Malaria verursacht." }
    { group:52, id:25, text: "Apotheker sind sich einig, dass Euer Name bitterer ist als jedes bekannte Kraut." }
    { group:52, id:26, text: "Mütter verwenden Euren Namen, um ihre kleinen Kinder zu erschrecken." }
    { group:52, id:27, text: "Euer Name wird in feiner Gesellschaft nie erwähnt." }
    { group:52, id:28, text: "Euer Ruf ist niedrig, und selbst Eure eigene Familie meidet Euch." }
    { group:52, id:29, text: "Euer Name ist bekannt, aber lächerlich gemacht, in den Zwei Ländern." }
    { group:52, id:30, text: "Leute, die zählen, kennen Euren Namen und Eure Geschichte, obwohl sie dazu neigen, Euch herabzuwürdigen." }
    { group:52, id:31, text: "Wenige Leute im Königreich kennen Eure Aufzeichnungen, und die, die es tun, sind unbeeindruckt." }
    { group:52, id:32, text: "Die wenigen Menschen, die Euren Namen erkennen, haben keine Meinung von Euch." }
    { group:52, id:33, text: "Eure mageren Leistungen sind nicht berühmt, aber die, die Euch kennen, mögen Euch im Allgemeinen." }
    { group:52, id:34, text: "Leute, die zählen, kennen Eure Geschichte und billigen im Allgemeinen, was Ihr getan habt." }
    { group:52, id:35, text: "Euer Name ist weithin anerkannt und bejubelt in den Zwei Ländern." }
    { group:52, id:36, text: "Euer Ruf ist gut, und Ihr werdet oft von längst verlorenen Verwandten angesprochen." }
    { group:52, id:37, text: "Die Erwähnung Eures Namens erhellt die Herzen derer, die ihn hören." }
    { group:52, id:38, text: "Mütter im ganzen Königreich benennen ihre Kinder nach Euch." }
    { group:52, id:39, text: "Viele ägyptische Städte erwägen, Festivals zu Euren Ehren abzuhalten." }
    { group:52, id:40, text: "Der beliebteste Tanz, der Ägypten erfasst, interpretiert die Geschichte Eures Lebens." }
    { group:52, id:41, text: "Musiker komponieren Lieder für Euch, und Euer Name ist auf jedem öffentlichen Platz eingemeißelt." }
    { group:52, id:42, text: "Alle Menschen Ägyptens wünschen, Euch ewig im Schilffeld zu dienen." }
    { group:52, id:43, text: "in Lagerplätzen" }
    { group:52, id:44, text: "in Stadtkassen" }
    { group:52, id:45, text: "Personen" }
    { group:52, id:46, text: "Waffen" }
    { group:52, id:47, text: "Klickt hier, um Anfrage zu versenden" }
    { group:52, id:48, text: "Anfrage kann nicht erfüllt werden" }
    { group:52, id:49, text: "Ein Geschenk senden" }
    { group:52, id:50, text: "Zeit seit letztem Geschenk" }
    { group:52, id:51, text: "Eine babylonische Tafel" }
    { group:52, id:52, text: "Persische Teppiche" }
    { group:52, id:53, text: "Antike Schnitzereien" }
    { group:52, id:54, text: "Afrikanisches Elfenbein" }
    { group:52, id:55, text: "Eine Truppe aufführender Sklaven" }
    { group:52, id:56, text: "Arabische Hengste" }
    { group:52, id:57, text: "Ein gebildeter Sklave" }
    { group:52, id:58, text: "Libysche Leibwächter" }
    { group:52, id:59, text: "Geparden und Giraffen" }
    { group:52, id:60, text: "Eine Truhe voll Saphire" }
    { group:52, id:61, text: "Ein goldener Streitwagen" }
    { group:52, id:62, text: "Ein libanesisches Zedernschiff" }
    { group:52, id:63, text: "Bescheiden:" }
    { group:52, id:64, text: "Großzügig:" }
    { group:52, id:65, text: "Verschwenderisch:" }
    { group:52, id:66, text: "Bescheidenes Geschenk senden" }
    { group:52, id:67, text: "Großzügiges Geschenk senden" }
    { group:52, id:68, text: "Verschwenderisches Geschenk senden" }
    { group:52, id:69, text: "Dem Volk Ägyptens geben" }
    { group:52, id:70, text: "Ihr habt nicht genug persönliche Ersparnisse, um ein Geschenk an Ägypten zu machen. Versucht, Euch ein größeres Gehalt zu zahlen!" }
    { group:52, id:71, text: "Warnung: Euch selbst ein Gehalt zu zahlen, das über Eurem aktuellen Rang liegt, wird niemanden beeindrucken." }
    { group:52, id:72, text: "Truppen zum Schutz entsenden nach" }
    { group:52, id:73, text: "Eine kleine Streitmacht wird angreifen in" }
    { group:52, id:74, text: "Eine durchschnittliche Streitmacht wird angreifen in" }
    { group:52, id:75, text: "Eine große Streitmacht wird angreifen in" }
    { group:52, id:76, text: "Ihr könnt derzeit Eure eigene Gehaltshöhe frei festlegen" }
    { group:52, id:77, text: "Der Palast verbietet es Euch, jetzt ein Gehalt zu beziehen, da Ihr aus freiem Willen weiterhin regiert." }
    { group:52, id:78, text: "Ihr müsst ein Anwesen bauen, um ein persönliches Gehalt zu beziehen." }
    { group:52, id:79, text: "Deben dieses Jahr durch Diebstahl verloren." }
    { group:52, id:80, text: "Seestreitkräfte entsenden nach" }
    { group:52, id:81, text: "Politischer Aufseher für " }
    { group:53, id:0, text: "Bewertungsaufseher" }
    { group:53, id:1, text: "Kultur" }
    { group:53, id:2, text: "Wohlstand" }
    { group:53, id:3, text: "Monument" }
    { group:53, id:4, text: "Königreich" }
    { group:53, id:5, text: "Benötigt" }
    { group:53, id:6, text: "Bevölkerung:" }
    { group:53, id:7, text: "Keine Zielbevölkerung" }
    { group:53, id:8, text: "Klickt auf eine Bewertungszahl für Informationen darüber" }
    { group:53, id:9, text: "Es gibt zu wenige Gaukler in der Stadt. Wenn möglich, fügt mehr Gauklerbühnen hinzu, um diese Bewertung zu verbessern." }
    { group:53, id:10, text: "Es gibt zu wenige Musiker in der Stadt. Wenn möglich, fügt mehr Musikerbühnen hinzu, um diese Bewertung zu verbessern." }
    { group:53, id:11, text: "Es gibt zu wenige Tänzer in der Stadt. Wenn möglich, fügt mehr Tänzerbühnen hinzu, um diese Bewertung zu verbessern." }
    { group:53, id:12, text: "Es gibt zu wenige Senet-Häuser in der Stadt. Wenn möglich, baut Senet-Häuser, um diese Bewertung zu verbessern." }
    { group:53, id:13, text: "Es gibt zu wenige Zoos in der Stadt. Wenn möglich, baut Zoos, um diese Bewertung zu verbessern." }
    { group:53, id:14, text: "Es gibt zu wenige Gotteshäuser in der Stadt. Mehr zu bauen würde diese Bewertung verbessern." }
    { group:53, id:15, text: "Es gibt zu wenige Schreiberschulen in der Stadt. Mehr zu bauen würde diese Bewertung verbessern." }
    { group:53, id:16, text: "Es gibt zu wenige Bibliotheken in der Stadt. Wenn möglich, baut mehr, um diese Bewertung zu verbessern." }
    { group:53, id:17, text: "Nicht genug Häuser haben Zugang zu einem Zahnarzt. Besserer Zugang würde diese Bewertung verbessern." }
    { group:53, id:18, text: "Nicht genug Häuser haben Zugang zu einem Arzt. Besserer Zugang würde diese Bewertung verbessern." }
    { group:53, id:19, text: "Nicht genug Häuser haben Zugang zu einer Leichenhalle. Besserer Zugang würde diese Bewertung verbessern." }
    { group:53, id:20, text: "Bewertung steigt." }
    { group:53, id:21, text: "Bewertung fällt." }
    { group:53, id:22, text: "Bewertung stagniert." }
    { group:53, id:23, text: "Die Gesamtqualität der Wohnungen Eurer Stadt hält diese Bewertung zurück. Verbessert die Wohnungen in Eurer Stadt, um sie zu erhöhen." }
    { group:53, id:24, text: "Letztes Jahr verlor Eure Stadt Geld - dies reduzierte den Wohlstand der Stadt." }
    { group:53, id:25, text: "Hohe Arbeitslosigkeit in Eurer Stadt hemmt Eure Wohlstandsbewertung." }
    { group:53, id:26, text: "Weniger als den Königreichslohn zu zahlen trübt das Bild Eurer Stadt als wohlhabende." }
    { group:53, id:27, text: "Die hohe Konzentration von Slumbewohnern in Eurer Stadt verleiht ihr das Aussehen einer armen." }
    { group:53, id:28, text: "Eure Unfähigkeit, den jährlichen Tribut zu zahlen, kennzeichnet Eure Stadt als Versagen." }
    { group:53, id:29, text: "unbenutzt 2041 - war Mangel an Nahrungsvielfalt beeinflusst Wohlstand." }
    { group:53, id:30, text: "Arbeitskräftemangel reduziert Wohlstand." }
    { group:53, id:31, text: "Die Stadt ist wohlhabender, wenn Exporte mehr einbringen als Importe kosten." }
    { group:53, id:32, text: "Eure Königreichsbewertung ist niedriger als letztes Jahr. Zahlt Euren jährlichen Tribut, bezieht ein bescheidenes Gehalt und erfüllt Anfragen des Pharaos oder anderer Städte im Königreich." }
    { group:53, id:33, text: "Das lächerlich hohe Gehalt, das Ihr Euch selbst zahlt, zeigt Eure völlige mangelnde Hingabe zum Königreich und reduziert diese Bewertung." }
    { group:53, id:34, text: "Eure anhaltende Unfähigkeit, jährlichen Tribut zu leisten, senkt Euren Ruf im ganzen Königreich und reduziert diese Bewertung." }
    { group:53, id:35, text: "Die Art, wie Ihr auf bestimmte Ereignisse reagiert habt, hat Eurem Ruf im ganzen Königreich stark geschadet und diese Bewertung gesenkt." }
    { group:53, id:36, text: "Das Gehalt, das Ihr Euch selbst zahlt und Euren Rang weit übersteigt, reduziert Euren Ruf im Königreich." }
    { group:53, id:37, text: "Zum zweiten Jahr in Folge habt Ihr keinen Tribut gezahlt, und Eure Königreichsbewertung leidet darunter." }
    { group:53, id:38, text: "Eure Reaktion auf bestimmte Ereignisse hat Eurem Ansehen im Königreich ein wenig geschadet." }
    { group:53, id:39, text: "Euer Gehalt ist zu hoch für Euren aktuellen Stand. Eure Königreichsbewertung wird steigen, wenn Ihr es etwas reduziert." }
    { group:53, id:40, text: "Ihr konntet Euren Tribut dieses Jahr nicht zahlen, was Eure Königreichsbewertung reduzierte. Behaltet etwas Geld in Eurer Schatzkammer am Jahresende, damit Ihr Eure jährliche Zahlung leisten könnt." }
    { group:53, id:41, text: "Euer Gehalt ist zu hoch für Euren aktuellen Stand. Ihr tätet gut daran, es zu reduzieren." }
    { group:53, id:42, text: "Euer langsamer Fortschritt beim rechtzeitigen Erreichen Eurer Ziele hat Eure Königreichsbewertung reduziert." }
    { group:53, id:43, text: "Eure Dreistigkeit, Euch ein Gehalt zu zahlen, das höher ist, als Euer Rang Euch zusteht, wird missbilligt." }
    { group:53, id:44, text: "Eure Königreichsbewertung ist höher als letztes Jahr. Ihr könnt Eurem Politischen Aufseher anweisen, ein Geschenk an Ägypten zu geben, und diese Bewertung wird noch mehr steigen." }
    { group:53, id:45, text: "Eure Königreichsbewertung ist unverändert gegenüber letztem Jahr. Ihr könnt Eurem Politischen Aufseher anweisen, ein Geschenk an Ägypten zu geben, und diese Bewertung wird steigen." }
    { group:53, id:46, text: "unbenutzt - war Friedensbewertungsbericht1" }
    { group:53, id:47, text: "unbenutzt - war Friedensbewertungsbericht2." }
    { group:53, id:48, text: "unbenutzt - war Friedensbewertungsbericht3" }
    { group:53, id:49, text: "unbenutzt - war Friedensbewertungsbericht4." }
    { group:53, id:50, text: "unbenutzt - war Friedensbewertungsbericht5" }
    { group:53, id:51, text: "unbenutzt - war Friedensbewertungsbericht6" }
    { group:53, id:52, text: "unbenutzt - war Friedensbewertungsbericht7" }
    { group:53, id:53, text: "unbenutzt - war Friedensbewertungsbericht8" }
    { group:53, id:54, text: "unbenutzt - war Friedensbewertungsbericht9" }
    { group:53, id:55, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:56, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:57, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:58, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:59, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:60, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:61, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:62, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:63, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:64, text: "Denkt daran, den Aufseher der Monumente anzuweisen, alle notwendigen Grabbeigaben zu entsenden. Besucht auch die Monumentbaustelle für einen detaillierten Fortschrittsbericht." }
    { group:53, id:65, text: "Diese Stadt ist kultivierter als jede in Ägypten!" }
    { group:53, id:66, text: "Der erstaunliche Wohlstand dieser Stadt ist Stadtgespräch in Ägypten!" }
    { group:53, id:67, text: "Diese Stadt hat die prächtigsten Monumente in ganz Ägypten!" }
    { group:53, id:68, text: "Euer Königreich ist das bestbewertete in ganz Ägypten!" }
    { group:54, id:0, text: "Aufseher des Handels" }
    { group:54, id:1, text: "Klickt auf einen Artikel, um zu handeln, einzulagern oder den Industriestatus zu ändern" }
    { group:54, id:2, text: "Preise anzeigen" }
    { group:54, id:3, text: "Einlagernd" }
    { group:54, id:4, text: "Nicht handelnd" }
    { group:54, id:5, text: "Importieren, um zu erhalten" }
    { group:54, id:6, text: "Exportieren, wenn über" }
    { group:54, id:7, text: "Keine Industrien in der Stadt" }
    { group:54, id:8, text: "arbeitende Industrie in der Stadt" }
    { group:54, id:9, text: "arbeitende Industrien in der Stadt" }
    { group:54, id:10, text: "Industrie in der Stadt, derzeit stillgelegt" }
    { group:54, id:11, text: "Industrien in der Stadt, derzeit stillgelegt" }
    { group:54, id:12, text: "arbeitend" }
    { group:54, id:13, text: "untätige Industrien in der Stadt" }
    { group:54, id:14, text: "untätige Industrie in der Stadt" }
    { group:54, id:15, text: "gelagert in den Lagerplätzen der Stadt" }
    { group:54, id:16, text: "Industrie ist EIN" }
    { group:54, id:17, text: "Industrie ist AUS" }
    { group:54, id:18, text: "Nicht handelnd" }
    { group:54, id:19, text: "Importieren, um zu erhalten" }
    { group:54, id:20, text: "Exportieren, wenn über" }
    { group:54, id:21, text: "Preise in ganz Ägypten" }
    { group:54, id:22, text: "Käufer zahlen" }
    { group:54, id:23, text: "Verkäufer erhalten" }
    { group:54, id:24, text: "Es gibt keine offenen Handelsrouten für diese Waren" }
    { group:54, id:25, text: "Diese Waren sind nur durch Import erhältlich" }
    { group:54, id:26, text: "Ressource einlagern" }
    { group:54, id:27, text: "Klickt hier, um Einlagerung auszuschalten" }
    { group:54, id:28, text: "Diese Ressource verwenden und handeln" }
    { group:54, id:29, text: "Klickt hier, um sie einzulagern" }
    { group:54, id:30, text: "Zur Weltkarte gehen" }
    { group:54, id:31, text: "Zum Import verfügbar" }
    { group:54, id:32, text: "Exportierbar" }
    { group:54, id:33, text: "Zum Import oder Export verfügbar" }
    { group:54, id:34, text: "Handelsroute zum Import öffnen" }
    { group:54, id:35, text: "Handelsroute zum Export öffnen" }
    { group:54, id:36, text: "Handelsrouten zum Import/Export öffnen" }
    { group:54, id:37, text: "Importieren nach Bedarf" }
    { group:54, id:38, text: "Überschüsse exportieren" }
    { group:54, id:39, text: "Klicken zum Importieren" }
    { group:54, id:40, text: "Klicken zum Exportieren" }
    { group:54, id:41, text: "Keine Verkäufer für diese Ressource" }
    { group:54, id:42, text: "Keine Käufer für diese Ressource" }
    { group:54, id:43, text: "Aufseher Importniveau setzen lassen" }
    { group:54, id:44, text: "Aufseher Exportniveau setzen lassen" }
    { group:54, id:45, text: "mehrfach" }
    { group:54, id:46, text: "Zurück zum Handelsstatus" }
    { group:54, id:47, text: "pro Waffe" }
    { group:54, id:48, text: "pro Streitwagen" }
    { group:54, id:49, text: "pro Block" }
    { group:54, id:50, text: "pro 100 Stück" }
    { group:55, id:0, text: "Bevölkerung - Geschichte" }
    { group:55, id:1, text: "Bevölkerung - Zensus" }
    { group:55, id:2, text: "Bevölkerung - Gesellschaft" }
    { group:55, id:3, text: "Geschichte" }
    { group:55, id:4, text: "Zensus" }
    { group:55, id:5, text: "Gesellschaft" }
    { group:55, id:6, text: "Stadtbevölkerung im Zeitverlauf" }
    { group:55, id:7, text: "Bevölkerungszusammensetzung nach Alter (in Jahren)" }
    { group:55, id:8, text: "Bevölkerungszusammensetzung nach Einkommen" }
    { group:55, id:9, text: "Hüttenbewohner" }
    { group:55, id:10, text: "Landgutbewohner" }
    { group:55, id:11, text: "Die Hauptstadt liefert die gesamte Nahrung für diese Stadt" }
    { group:55, id:12, text: " Nahrung für" }
    { group:55, id:13, text: " etwas Nahrung für den kommenden Monat" }
    { group:55, id:14, text: " keine Nahrung für den kommenden Monat" }
    { group:55, id:15, text: " sehr wenig Nahrung für den kommenden Monat" }
    { group:55, id:16, text: "Derzeitige Wohnungen können fassen" }
    { group:55, id:17, text: "mehr Personen" }
    { group:55, id:18, text: "Neuankömmlinge kamen diesen Monat" }
    { group:55, id:19, text: "Neuankömmling kam diesen Monat" }
    { group:55, id:20, text: "Mangel an freien Wohnungen begrenzt Einwanderung." }
    { group:55, id:21, text: "Niedrige Löhne reduzieren Einwanderung in unsere Stadt." }
    { group:55, id:22, text: "Arbeitslosigkeit reduziert Eure Anzahl an Einwanderern." }
    { group:55, id:23, text: "Mangel an Nahrung in Euren Getreidespeichern reduziert Einwanderung." }
    { group:55, id:24, text: "Hohe Steuern halten einige Menschen von unserer Stadt fern." }
    { group:55, id:25, text: "Insgesamt kommen Menschen in unsere Stadt oder wollen kommen." }
    { group:55, id:26, text: "Insgesamt verlassen Menschen unsere Stadt." }
    { group:55, id:27, text: "Mangel an Arbeitsplätzen treibt Menschen fort." }
    { group:55, id:28, text: "Menschen gehen anderswohin auf der Suche nach höheren Löhnen." }
    { group:55, id:29, text: "Menschen verlassen die Stadt wegen Eures hohen Steuersatzes." }
    { group:55, id:30, text: "Insgesamt ist Eure Stadtbevölkerung statisch." }
    { group:55, id:31, text: "Es gibt ein Gleichgewicht zwischen Menschen, die in die Stadt kommen und sie verlassen." }
    { group:55, id:32, text: "Schlechte Wohnungen, trotz des Reichtums Eurer Stadt, entmutigen Einwanderer." }
    { group:55, id:33, text: "Niemand will in unserer Stadt leben." }
    { group:55, id:34, text: "Wir produzieren oder importieren genug Nahrung für etwa  " }
    { group:55, id:35, text: "Personen." }
    { group:55, id:36, text: "Wir essen viel mehr, als wir produzieren!" }
    { group:55, id:37, text: "Wir essen viel mehr, als wir produzieren, also erwartet, dass unsere Stadt schrumpft." }
    { group:55, id:38, text: "Wir produzieren viel zu wenig Nahrung. Unsere wachsende Stadt wird noch mehr brauchen." }
    { group:55, id:39, text: "Wir essen mehr, als wir produzieren." }
    { group:55, id:40, text: "Wir essen mehr, als wir produzieren, aber unsere schrumpfende Stadt wird weniger essen." }
    { group:55, id:41, text: "Wir produzieren zu wenig Nahrung. Unsere wachsende Stadt wird noch mehr brauchen." }
    { group:55, id:42, text: "Gerade jetzt essen wir etwas mehr, als wir produzieren. " }
    { group:55, id:43, text: "Wir essen etwas mehr, als wir produzieren, also erwartet, dass unsere Stadt schrumpft." }
    { group:55, id:44, text: "Wir essen etwas mehr, als wir produzieren. Unsere wachsende Stadt wird mehr brauchen." }
    { group:55, id:45, text: "Gerade jetzt produzieren wir gerade genug, um alle zu ernähren." }
    { group:55, id:46, text: "Wir produzieren keine zusätzliche Nahrung, und unsere schrumpfende Stadt wird noch weniger essen. " }
    { group:55, id:47, text: "Jetzt produzieren wir gerade genug Nahrung, aber unsere wachsende Stadt wird mehr brauchen." }
    { group:55, id:48, text: "Gerade jetzt produzieren wir etwas mehr, als wir essen." }
    { group:55, id:49, text: "Wir produzieren etwas zusätzliche Nahrung. Unsere schrumpfende Stadt wird noch weniger essen." }
    { group:55, id:50, text: "Wir produzieren etwas überschüssige Nahrung, und unsere wachsende Stadt wird sie brauchen." }
    { group:55, id:51, text: "Gerade jetzt produzieren wir viel mehr, als wir essen." }
    { group:55, id:52, text: "Wir produzieren viel zusätzliche Nahrung. Unsere schrumpfende Stadt wird noch weniger brauchen." }
    { group:55, id:53, text: "Wir produzieren viel zusätzliche Nahrung, aber unsere wachsende Stadt wird mehr brauchen." }
    { group:56, id:0, text: "Aufseher der öffentlichen Gesundheit" }
    { group:56, id:1, text: "Frei" }
    { group:56, id:2, text: "Keine" }
    { group:56, id:3, text: "Arbeitend" }
    { group:56, id:4, text: "Pflege für" }
    { group:56, id:5, text: "Stadtabdeckung" }
    { group:56, id:6, text: "Patienten" }
    { group:56, id:7, text: "Bestimmte Bereiche der Stadt benötigen jetzt Zugang zu Ärzten." }
    { group:56, id:8, text: "Einige Regionen der Stadt wollen mehr Ärzte." }
    { group:56, id:9, text: "Bestimmte wohlhabende Bereiche der Stadt wollen Zahnärzte. Ein örtlicher Zahnarzt wird das Ansehen der Nachbarschaft erhöhen." }
    { group:56, id:10, text: "Mehr Bereiche der Stadt benötigen jetzt Zahnärzte. Da Eure Stadt wohlhabender wird, können sich mehr und mehr Bewohner neue Elfenbeinzähne leisten." }
    { group:56, id:11, text: "Einige Teile der Stadt verlangen Zugang zu einer Apotheke." }
    { group:56, id:12, text: "Immer mehr Menschen wollen bequeme medizinische Einrichtungen (Apotheken)." }
    { group:56, id:13, text: "Die Entwicklung in einigen Vierteln wird durch schlechte stadtweite Leichenhallen-Abdeckung zurückgehalten." }
    { group:56, id:14, text: "Bürger benötigen mehr Leichenhallen, um ihre Toten richtig auf das Jenseits vorzubereiten." }
    { group:56, id:15, text: "Niemand bittet noch um Gesundheits- oder Sanitäreinrichtungen. Wenn sich die Stadt jedoch entwickelt, erwarten die Menschen Zugang zu Gesundheitsversorgung, dann Zahnärzten und dann noch mehr medizinischen Einrichtungen!" }
    { group:56, id:16, text: "Eure kleine Siedlung hat noch keine Probleme mit der Gesundheit gemeldet." }
    { group:56, id:17, text: "Die Gesundheit der Stadt ist entsetzlich! Seuche ist in solch schockierenden Bedingungen sicher." }
    { group:56, id:18, text: "Die Gesundheit der Stadt ist schrecklich! Krankheit ist fast unvermeidlich." }
    { group:56, id:19, text: "Die Gesundheit der Stadt ist schlecht. Mehr Gesundheitsarbeiter könnten die Situation verbessern." }
    { group:56, id:20, text: "Die Gesundheit der Stadt ist dürftig. Reichlich Nahrung und Gesundheitseinrichtungen würden sie verbessern." }
    { group:56, id:21, text: "Die Gesundheit der Stadt ist unterdurchschnittlich. Stellt sicher, dass Bürger Nahrung und Zugang zu Gesundheitsdienstleistern haben." }
    { group:56, id:22, text: "Die Gesundheit der Stadt ist durchschnittlich. Üble Einflüsse sind unter Kontrolle, und die Menschen bekommen genug zu essen." }
    { group:56, id:23, text: "Die Gesundheit der Stadt ist gut. Bürger neigen nur zu kleineren Beschwerden." }
    { group:56, id:24, text: "Die Gesundheit der Stadt ist sehr gut. Örtliche Pfleger kommen gut zurecht." }
    { group:56, id:25, text: "Die Gesundheit der Stadt ist ausgezeichnet, ohne Wartezeiten für den Besuch örtlicher Gesundheitseinrichtungen." }
    { group:56, id:26, text: "Die Gesundheit der Stadt ist fast perfekt, mit praktisch leeren Gesundheitseinrichtungen." }
    { group:56, id:27, text: "Die Gesundheit der Stadt ist perfekt. Eure Gesundheitsarbeiter verbringen die meisten Tage mit Senet spielen. " }
    { group:56, id:28, text: "Die Gesundheit der Stadt ist entsetzlich." }
    { group:56, id:29, text: "Die Gesundheit der Stadt ist schrecklich." }
    { group:56, id:30, text: "Die Gesundheit der Stadt ist schlecht." }
    { group:56, id:31, text: "Die Gesundheit der Stadt ist dürftig." }
    { group:56, id:32, text: "Die Gesundheit der Stadt ist unterdurchschnittlich." }
    { group:56, id:33, text: "Die Gesundheit der Stadt ist durchschnittlich." }
    { group:56, id:34, text: "Die Gesundheit der Stadt ist gut." }
    { group:56, id:35, text: "Die Gesundheit der Stadt ist sehr gut." }
    { group:56, id:36, text: "Die Gesundheit der Stadt ist ausgezeichnet." }
    { group:56, id:37, text: "Die Gesundheit der Stadt ist fast perfekt." }
    { group:56, id:38, text: "Die Gesundheit der Stadt ist perfekt." }
    { group:56, id:39, text: "Ärzte" }
    { group:56, id:40, text: "Zahnärzte" }
    { group:56, id:41, text: "Apotheken" }
    { group:56, id:42, text: "Leichenhallen" }
    { group:56, id:43, text: "Dürftig" }
    { group:56, id:44, text: "Sehr schlecht" }
    { group:56, id:45, text: "Schlecht" }
    { group:56, id:46, text: "Unterdurchschnittlich" }
    { group:56, id:47, text: "Durchschnittlich" }
    { group:56, id:48, text: "Durchschnittlich" }
    { group:56, id:49, text: "Überdurchschnittlich" }
    { group:56, id:50, text: "Gut" }
    { group:56, id:51, text: "Sehr gut" }
    { group:56, id:52, text: "Ausgezeichnet" }
    { group:56, id:53, text: "Perfekt" }
    { group:56, id:54, text: "Keine" }
    { group:56, id:55, text: "Ein paar" }
    { group:56, id:56, text: "Einige" }
    { group:56, id:57, text: "Mehrere" }
    { group:56, id:58, text: "Viele" }
    { group:56, id:59, text: "Apotheken arbeiten derzeit daran, die Stadt vor Malaria zu schützen." }
    { group:56, id:60, text: "Ausbrüche wurden diesen Monat gemeldet." }
    { group:56, id:61, text: "Nahrungssorten in Eurer Stadt." }
    { group:57, id:0, text: "Aufseher des Lernens" }
    { group:57, id:1, text: "Arbeitend" }
    { group:57, id:2, text: "Kann bilden" }
    { group:57, id:3, text: "Stadtabdeckung" }
    { group:57, id:4, text: "Kinder" }
    { group:57, id:5, text: "Junge Menschen" }
    { group:57, id:6, text: "Personen" }
    { group:57, id:7, text: "Keine" }
    { group:57, id:8, text: "Dürftig" }
    { group:57, id:9, text: "Sehr schlecht" }
    { group:57, id:10, text: "Schlecht" }
    { group:57, id:11, text: "Unterdurchschnittlich" }
    { group:57, id:12, text: "Durchschnittlich" }
    { group:57, id:13, text: "Durchschnittlich" }
    { group:57, id:14, text: "Überdurchschnittlich" }
    { group:57, id:15, text: "Gut" }
    { group:57, id:16, text: "Sehr gut" }
    { group:57, id:17, text: "Ausgezeichnet" }
    { group:57, id:18, text: "Perfekt" }
    { group:57, id:19, text: "Bestimmte Bereiche der Stadt benötigen jetzt Schreiberschul-Zugang. Schlechte Bildung hindert einige Bewohner daran, ihre Wohnungen zu verbessern." }
    { group:57, id:20, text: "Einige Nachbarschaften verlangen besseren Schreiberschul-Zugang. Einige Häuser haben Zugang zu Stadtschulen, andere nicht, und dies behindert ihre Entwicklung." }
    { group:57, id:21, text: "Bibliothekszugang wird jetzt in bestimmten Bereichen der Stadt benötigt. Menschen brauchen Zugang zu Literatur, wenn sie als Schreiber arbeiten sollen." }
    { group:57, id:22, text: "Einige Bereiche der Stadt wollen besseren Bibliothekszugang. Schreiber der Oberschicht schätzen es nicht, so weit zur Bibliothek laufen zu müssen." }
    { group:57, id:23, text: "Besserer Schreiberschul- und Bibliothekszugang würde einige Bereiche der Stadt aufwerten. Menschen sollten nicht so weit für Bildung laufen müssen!" }
    { group:57, id:24, text: "Niemand bittet noch um Bildungseinrichtungen. Wenn die Stadt jedoch an Ansehen gewinnt, erwarten die Menschen Schreiberschulen, gefolgt später von Forderungen nach Bibliotheken." }
    { group:57, id:25, text: "Alle Häuser, die sie wollen, haben Bildungseinrichtungen. Schreiberschulen und Bibliotheken sind zahlreich, und niemand beklagt sich über Überfüllung." }
    { group:57, id:26, text: "Alle Häuser, die sie wollen, haben Bildungseinrichtungen, aber mehr Schreiberschulen zu bauen würde Klassengrößen reduzieren und die Stadtkultur verbessern." }
    { group:57, id:27, text: "Alle Häuser, die sie wollen, haben Bildungseinrichtungen, aber mehr Bibliotheken zu bauen würde Überfüllung reduzieren und die Stadtkultur erhöhen." }
    { group:57, id:28, text: "Schreiberschulen " }
    { group:57, id:29, text: "Bibliothek" }
    { group:58, id:0, text: "Aufseher der Unterhaltung" }
    { group:58, id:1, text: "Arbeitend" }
    { group:58, id:2, text: "Aufführungen" }
    { group:58, id:3, text: "Kann unterhalten" }
    { group:58, id:4, text: "Stadtabdeckung" }
    { group:58, id:5, text: "Personen" }
    { group:58, id:6, text: "N/A" }
    { group:58, id:7, text: "Niemand sucht noch Unterhaltung. Wenn Eure Stadt jedoch wächst, werden die Menschen Vergnügungen wie Jonglieren, Musik und Tanz wollen." }
    { group:58, id:8, text: "Es gibt derzeit genug Unterhaltung, um jeden zufriedenzustellen. Wenn die Stadt jedoch wächst, werden die Menschen mehr und bessere Formen der Unterhaltung fordern." }
    { group:58, id:9, text: "Einige Bewohner wollen mehr Freizeiteinrichtungen. Mehr Auswahl bei Unterhaltung würde sie motivieren, ihre Häuser aufzurüsten." }
    { group:58, id:10, text: "Teile der Stadt murren, dass sie keinen Zugang zu Erholung haben. Mehr Unterhaltungsorte zu bauen würde diesen ärmeren Gebieten bei der Entwicklung helfen." }
    { group:58, id:11, text: "Einige Menschen jammern über unzureichende Unterhaltung in ihren Nachbarschaften. Ihr müsst vielleicht mehr Vielfalt bieten oder vielleicht mehr Künstlerschulen bauen, um Künstler für Orte bereitzustellen, denen sie fehlen." }
    { group:58, id:12, text: "Einige Buden oder Musikpavillons haben leere Bühnen. Mehr Gaukler oder Musiker würden Nachbarschaften zufriedenstellen, die sich über schlechte Unterhaltung beschweren." }
    { group:58, id:13, text: "Eure Pavillons brauchen mehr Tänzer. Ein neues Konservatorium könnte die lokalen Unterhaltungsniveaus in Teilen der Stadt steigern." }
    { group:58, id:14, text: "Solange das Senet-Haus sowohl Angestellte als auch Bier hat, wird der Senet-Meister durch die Nachbarschaft zirkulieren, um die Menschen daran zu erinnern, dass Spiele laufen." }
    { group:58, id:15, text: "seit letztem Festival" }
    { group:58, id:16, text: "Neues Festival abhalten" }
    { group:58, id:17, text: "Festivals" }
    { group:58, id:18, text: "Die härtesten Festgänger haben den letzten Rausch noch nicht ausgeschlafen." }
    { group:58, id:19, text: "Die Menschen lächeln noch, wenn sie sich an Euer letztes Festival erinnern." }
    { group:58, id:20, text: "Die Erinnerung an das frühere Festival verblasst aus den Köpfen der Menschen." }
    { group:58, id:21, text: "Die Menschen können sich nicht an das letzte Festival erinnern, das in der Stadt abgehalten wurde." }
    { group:58, id:22, text: "Bürger murren über den Mangel an Festivals in Eurer Stadt." }
    { group:58, id:23, text: "Euer Volk kann die Aussicht auf ein weiteres Jahr ohne Festival nicht ertragen." }
    { group:58, id:24, text: "Deprimierte Bewohner zweifeln daran, dass sie ein weiteres Festival erleben werden." }
    { group:58, id:25, text: "Festival für Osiris abhalten" }
    { group:58, id:26, text: "Festival für Ra abhalten" }
    { group:58, id:27, text: "Festival für Ptah abhalten" }
    { group:58, id:28, text: "Festival für Seth abhalten" }
    { group:58, id:29, text: "Festival für Bast abhalten" }
    { group:58, id:30, text: "kostet" }
    { group:58, id:31, text: "Einfaches Festival" }
    { group:58, id:32, text: "Verschwenderisches Festival" }
    { group:58, id:33, text: "Großartiges Festival" }
    { group:58, id:34, text: "Festival wird vorbereitet für " }
    { group:58, id:35, text: "Keine" }
    { group:58, id:36, text: "Dürftig" }
    { group:58, id:37, text: "Sehr schlecht" }
    { group:58, id:38, text: "Schlecht" }
    { group:58, id:39, text: "Unterdurchschnittlich" }
    { group:58, id:40, text: "Durchschnittlich" }
    { group:58, id:41, text: "Durchschnittlich" }
    { group:58, id:42, text: "Überdurchschnittlich" }
    { group:58, id:43, text: "Gut" }
    { group:58, id:44, text: "Sehr gut" }
    { group:58, id:45, text: "Ausgezeichnet" }
    { group:58, id:46, text: "Perfekt" }
    { group:58, id:47, text: "Gauklerbühnen" }
    { group:58, id:48, text: "Musikerbühnen" }
    { group:58, id:49, text: "Tänzerbühnen" }
    { group:58, id:50, text: "Senet-Häuser " }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Ein Festival anordnen" }
    { group:58, id:53, text: "Festivalbestellung für" }
    { group:58, id:54, text: "nächsten Monat" }
    { group:58, id:55, text: "Bühnen" }
    { group:58, id:56, text: "Zoos" }
    { group:59, id:0, text: "Aufseher der Tempel" }
    { group:59, id:1, text: "Tempel" }
    { group:59, id:2, text: "Komplexe" }
    { group:59, id:3, text: "Besänftigung" }
    { group:59, id:4, text: "N/A" }
    { group:59, id:5, text: "Tempel" }
    { group:59, id:6, text: "Monate" }
    { group:59, id:7, text: "Festival" }
    { group:59, id:8, text: "seit" }
    { group:59, id:9, text: "Bewohner beginnen, spirituelle Bedürfnisse zu spüren. Das Fehlen naher Gotteshäuser hält die Stadtentwicklung zurück." }
    { group:59, id:10, text: "Immer mehr Menschen fürchten, dass ohne mindestens ein Gotteshaus in ihren Nachbarschaften sich die Götter verschmäht fühlen werden." }
    { group:59, id:11, text: "Gehobenere Bewohner wollen Zugang zu einer anderen Religion nahe ihres Zuhauses. Mangel an religiöser Vielfalt begrenzt die Stadtentwicklung in bestimmten Gebieten." }
    { group:59, id:12, text: "Anspruchsvolle Bürger sagen, dass ihre Nachbarschaften eine bessere Klasse von Schreibern anziehen würden, wenn sie leichten Zugang zu einer dritten Religion hätten." }
    { group:59, id:13, text: "Bisher sind die Menschen zu sehr mit physischen Bedürfnissen beschäftigt, um an Religion zu denken. Wenn Eure Stadt jedoch wächst, werden sie leichten Zugang zu einer Vielfalt von Tempeln wollen." }
    { group:59, id:14, text: "Die religiösen Überzeugungen aller werden bedient, und die Priester berichten, dass die Götter mit der Spiritualität der Stadt zufrieden sind." }
    { group:59, id:15, text: "Osiris' Missfallen ist gefährlich. Er kann Eure Ernten zerstören und Eure Getreidespeicher leeren, oder sogar die Überschwemmung zurückhalten." }
    { group:59, id:16, text: "Wenn der mächtige Ra, Vater des Pharaos, unzufrieden wird, wird er die Nachbarn Eurer Stadt sein Gefühl teilen lassen. Ras Zorn gefährdet die Harmonie mit dem Königreich.  " }
    { group:59, id:17, text: "Ptah, dessen Wohlwollen Eure Hersteller benötigen, wird unglücklich. Gewinnt seine Gunst zurück, oder bereitet Eure Arbeiter auf den Verlust ganzer Industrien und Produkte vor." }
    { group:59, id:18, text: "Die tapfersten Soldaten zittern vor dem Zorn von Seth. Repariert schnell die Meinung des Gottes über Eure Stadt, oder seht zu, wie Euer Bataillon hinweggefegt wird!" }
    { group:59, id:19, text: "Wenn die gütige Bast verärgert wird, sind die Menschen nicht sicher in ihren eigenen Häusern. Besänftigt die Göttin schnell, oder Zerstörung und Seuche werden folgen!" }
    { group:59, id:20, text: "Wütend" }
    { group:59, id:21, text: "Zornig" }
    { group:59, id:22, text: "Verärgert" }
    { group:59, id:23, text: "Nachtragend" }
    { group:59, id:24, text: "Unzufrieden" }
    { group:59, id:25, text: "Apathisch" }
    { group:59, id:26, text: "Freundlich" }
    { group:59, id:27, text: "Wohlwollend" }
    { group:59, id:28, text: "Mitfühlend" }
    { group:59, id:29, text: "Zustimmend" }
    { group:59, id:30, text: "Wohlwollend" }
    { group:59, id:31, text: "unbenutzt - war Gott-Umschalter" }
    { group:59, id:32, text: "Osiris ist der Gott der Nilflut und allen Lebens, das aus der Unterwelt entspringt. Mit seinem Wohlwollen kann Eure Stadt den Segen einer reichhaltigen jährlichen Überschwemmung erhalten, die lebensspendendes fruchtbares Erdreich auf Eure Felder bringt. Er kann auch die Ernte zur Erntezeit auf andere Weise verbessern. Ein Altar von Sebek - Gott der Fruchtbarkeit - bedeutet, dass Priester des Osiris Euren Bürgern helfen können, ihre Nahrung und andere Vorräte etwas weiter zu strecken, während ein Orakel von Min - Gott der Regeneration - die Tierwelt in und um Eure Stadt mit größerer Vitalität erfüllt. Sein Orakel macht Tierherden und Fischkolonien widerstandsfähiger und beschleunigt sogar das Nachwachsen einiger Pflanzen. " }
    { group:59, id:33, text: "Als Gott des Königreichs erleichtert Ra Handel und Reisen in der bekannten Welt und kann sogar helfen, Euren Ruf in ganz Ägypten zu stärken. Ein Altar der Ma'at - Göttin der Gerechtigkeit - hilft, Verbrechen in Eurer Stadt zu verhindern, während ein Orakel von Horus - Gott des Pharaos - Eure Angestellten williger macht, ihre täglichen Arbeiten zu verrichten. Im Namen des Pharaos werden sie inspiriert, für das Gemeinwohl Ägyptens zu arbeiten." }
    { group:59, id:34, text: "Ptah ist der Schutzgott der Handwerker und hilft vielen von ihnen, ihre Aufgaben schneller zu beenden. Ein Altar von Amon - Gott der Sonne - verbessert die Fähigkeit Eurer Stadt, Monumente zu bauen, während ein Orakel von Thoth - Gott der Weisheit und des Lernens - die Bildung Eures Volkes erleichtern kann." }
    { group:59, id:35, text: "Wenn Seth besänftigt ist, sind Eure Feinde seine Feinde. Er kann Euren grünsten Soldaten helfen, wie erfahrene Veteranen zu kämpfen, und sogar Eure Feinde durch seine eigene Hand niederschlagen. So mächtig ist er, dass sein Einfluss sich sogar auf Schlachten erstreckt, die weit entfernt ausgefochten werden. Wenn Seth natürlich nicht besänftigt ist, kann Eure Stadt die volle Macht seiner zerstörerischen Kräfte aus erster Hand erfahren." }
    { group:59, id:36, text: "Als Göttin des Heims kann Bast die Lebensqualität in Eurer Stadt verbessern und kann Euren Bürgern ermöglichen, einen viel höheren Lebensstandard zu genießen, als es sonst der Fall wäre. So groß ist ihre Macht, dass sie sogar helfen kann, die anderen Götter glücklich zu halten. Wenn sie natürlich nicht besänftigt ist, wird Eure Stadt wahres Elend und Leid kennen. Ein Altar der Isis - Göttin der Heilung - kann helfen zu gewährleisten, dass Eure Bürger bei guter Gesundheit bleiben, und ihnen sogar helfen, wenn sie krank werden, während ein Orakel von Hathor - Göttin der Freude, Liebe und Festivität - helfen kann, Euer Volk trotz welcher Probleme sie auch haben mögen, etwas glücklicher zu halten.    " }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Priesterin" }
    { group:60, id:0, text: "Aufseher der Schatzkammer" }
    { group:60, id:1, text: "Steuersatz von" }
    { group:60, id:2, text: "Stadtkasse hat Vermögen von" }
    { group:60, id:3, text: "Stadt hat Schulden von" }
    { group:60, id:4, text: "ergibt geschätzte" }
    { group:60, id:5, text: "der Bevölkerung für Steuer registriert" }
    { group:60, id:6, text: "Letztes Jahr" }
    { group:60, id:7, text: "Bisher dieses Jahr" }
    { group:60, id:8, text: "Steuern in" }
    { group:60, id:9, text: "Exporte bringen ein" }
    { group:60, id:10, text: "Einnahmen" }
    { group:60, id:11, text: "Importe kosten" }
    { group:60, id:12, text: "Löhne" }
    { group:60, id:13, text: "Bau" }
    { group:60, id:14, text: "Zinsen bei" }
    { group:60, id:15, text: "Persönliches Gehalt" }
    { group:60, id:16, text: "Diebstahl" }
    { group:60, id:17, text: "Ausgaben" }
    { group:60, id:18, text: "Netto-Zu-/Abfluss" }
    { group:60, id:19, text: "Saldo" }
    { group:60, id:20, text: "Geschenke" }
    { group:60, id:21, text: "Tribut" }
    { group:60, id:22, text: "Anfragen und Festivals" }
    { group:60, id:23, text: "dieses Jahr nicht eingesammelt" }
    { group:60, id:24, text: "Abgebautes Gold" }
    { group:61, id:0, text: "Oberaufseher" }
    { group:61, id:1, text: "Stadtstimmung" }
    { group:61, id:2, text: "Migration" }
    { group:61, id:3, text: "Beschäftigung" }
    { group:61, id:4, text: "Nahrungsvorräte" }
    { group:61, id:5, text: "Nahrungsproduktion" }
    { group:61, id:6, text: "Gesundheit" }
    { group:61, id:7, text: "Religion" }
    { group:61, id:8, text: "Finanzen" }
    { group:61, id:9, text: "Verbrechen" }
    { group:61, id:10, text: "Militär" }
    { group:61, id:11, text: "Königreich" }
    { group:61, id:12, text: "Nilometer" }
    { group:61, id:13, text: "Wir produzieren viel mehr, als wir essen" }
    { group:61, id:14, text: "Wir produzieren etwas mehr, als wir essen" }
    { group:61, id:15, text: "Wir produzieren gerade genug, um alle zu ernähren" }
    { group:61, id:16, text: "WICHTIG: Wir essen etwas mehr, als wir produzieren" }
    { group:61, id:17, text: "ERNST: Wir essen mehr, als wir produzieren" }
    { group:61, id:18, text: "DRINGEND: Wir essen viel mehr, als wir produzieren" }
    { group:61, id:19, text: "UNBENUTZT 2426" }
    { group:61, id:20, text: "Ihr werdet allgemein verabscheut" }
    { group:61, id:21, text: "Die Menschen sind sehr wütend auf Euch" }
    { group:61, id:22, text: "Die Menschen sind wütend auf Euch" }
    { group:61, id:23, text: "Die Menschen sind sehr verärgert über Euch" }
    { group:61, id:24, text: "Die Menschen sind verärgert über Euch" }
    { group:61, id:25, text: "Die Menschen sind genervt von Euch" }
    { group:61, id:26, text: "Die Menschen sind Euch gleichgültig gegenüber" }
    { group:61, id:27, text: "Die Menschen sind zufrieden mit Euch." }
    { group:61, id:28, text: "Die Menschen sind sehr zufrieden mit Euch." }
    { group:61, id:29, text: "Die Menschen sind äußerst zufrieden mit Euch." }
    { group:61, id:30, text: "Die Menschen lieben Euch." }
    { group:61, id:31, text: "Die Menschen verehren Euch als Gott." }
    { group:61, id:32, text: "wegen Nahrungsmangels." }
    { group:61, id:33, text: "wegen Arbeitsmangels." }
    { group:61, id:34, text: "wegen hoher Steuern." }
    { group:61, id:35, text: "weil die Löhne niedrig sind." }
    { group:61, id:36, text: "wegen so vieler Slums. " }
    { group:61, id:37, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Der Nahrungsmangel der Stadt ist die Hauptursache für Unzufriedenheit, aber hohe Steuern, niedrige Löhne, soziale Ungleichheit und Arbeitsmangel können die Stadtstimmung ebenfalls senken." }
    { group:61, id:38, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Der Mangel an Arbeitsplätzen hier verärgert die Menschen mehr als alles andere, aber hohe Steuern, niedrige Löhne, soziale Ungleichheit und Nahrungsmangel können die Stadtstimmung ebenfalls senken." }
    { group:61, id:39, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Der hohe Steuersatz liegt Euren Bürgern am meisten am Herzen, aber niedrige Löhne, soziale Ungleichheit und Mangel an Nahrung und Arbeitsplätzen können die Stadtstimmung ebenfalls herabziehen." }
    { group:61, id:40, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Ihre armseligen Löhne (verglichen mit dem, was Arbeiter anderswo in Ägypten verdienen) sind ihre Hauptbeschwerde, aber hohe Steuern, soziale Ungleichheit und Mangel an Nahrung und Arbeitsplätzen können die Stadtstimmung ebenfalls senken." }
    { group:61, id:41, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Weitverbreitete soziale Ungleichheit verärgert die Menschen am meisten, aber hohe Steuern, niedrige Löhne und Mangel an Nahrung und Arbeitsplätzen können die Stadtstimmung ebenfalls drücken." }
    { group:61, id:42, text: "Niedrige Stadtstimmung trägt zu höheren Kriminalitätsraten bei, verhindert, dass Siedler in Eure Stadt kommen, und kann sogar dazu führen, dass Eure derzeitigen Bürger aufbrechen und gehen. Niedrige Löhne, hohe Steuern, soziale Ungleichheit und Mangel an Nahrung und Arbeitsplätzen tragen alle zu niedriger Stadtstimmung bei." }
    { group:61, id:43, text: "Krieg schreckt Einwanderer ab!" }
    { group:61, id:44, text: "Menschen wandern in die Stadt ein" }
    { group:61, id:45, text: "Mangel an Wohnungen verhindert Einwanderung" }
    { group:61, id:46, text: "Niedrige Löhne verhindern Einwanderung" }
    { group:61, id:47, text: "Mangel an Arbeitsplätzen verhindert Einwanderung" }
    { group:61, id:48, text: "Mangel an Nahrung verhindert Einwanderung" }
    { group:61, id:49, text: "Hohe Steuern verhindern Einwanderung" }
    { group:61, id:50, text: "Die Slumgebiete der Stadt entmutigen Einwanderung" }
    { group:61, id:51, text: "Schlechte Stadtstimmung verhindert Einwanderung" }
    { group:61, id:52, text: "Mangel an freien Wohnungen treibt Menschen weg" }
    { group:61, id:53, text: "Niedrige Löhne veranlassen Menschen, die Stadt zu verlassen" }
    { group:61, id:54, text: "Arbeitslosigkeit bringt Menschen dazu, die Stadt zu verlassen" }
    { group:61, id:55, text: "Menschen, die gehen, nennen Hunger als Grund" }
    { group:61, id:56, text: "Unfaire oder übermäßige Besteuerung treibt Menschen weg" }
    { group:61, id:57, text: "Einige Slums ermutigen Menschen zum Gehen" }
    { group:61, id:58, text: "Menschen gehen wegen schlechter Stadtstimmung" }
    { group:61, id:59, text: "Wenig Veränderung erwartet" }
    { group:61, id:60, text: "Solange es freie Wohnungen gibt und die Einwohner Eurer Stadt mit Euch zufrieden sind, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Schafft mehr Wohngebiete, damit Eure Stadt wachsen und gedeihen kann." }
    { group:61, id:61, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Erhöht die Löhne, wenn Ihr mehr Menschen in die Stadt locken wollt." }
    { group:61, id:62, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Schafft einige Arbeitsplätze, indem Ihr mehr Industrien baut, wenn Ihr mehr Menschen in die Stadt ziehen wollt." }
    { group:61, id:63, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Produziert mehr Nahrung als derzeit, wenn Ihr mehr Menschen in die Stadt ziehen wollt." }
    { group:61, id:64, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Niedrigere Steuern würden mehr Menschen in die Stadt ziehen." }
    { group:61, id:65, text: "Normalerweise wollt Ihr die Bevölkerung erhöhen, damit Eure Stadt wachsen und gedeihen kann. Neue Siedler werden von freien Wohnungen und höherer Stadtstimmung angezogen." }
    { group:61, id:66, text: "Normalerweise wollt Ihr die Bevölkerung erhöhen, damit Eure Stadt wachsen und gedeihen kann. Da freie Wohnungen verfügbar sind und Euer Volk mit seinem Leben hier zufrieden ist, strömen neue Siedler in die Stadt." }
    { group:61, id:67, text: "Wenn es zu große Unterschiede zwischen Arm und Reich gibt, wird niemand in Eure Stadt kommen wollen. Bietet bessere Dienstleistungen für Eure ärmeren Nachbarschaften, um mehr Gleichgewicht zwischen Wohlhabenden und Menschen bescheidenerer Mittel zu schaffen." }
    { group:61, id:68, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen. Erhöht Eure Stadtstimmung, um Menschen in die Stadt zu ziehen." }
    { group:61, id:69, text: "Solange ausreichend Wohnraum verfügbar ist und die Einwohner Eurer Stadt zufrieden sind, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen (und Eure eigenen Bürger werden nicht in grünere Gefilde aufbrechen!). Baut mehr Wohnungen, damit Eure Stadt wachsen und gedeihen kann." }
    { group:61, id:70, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden sie in Eurer Stadt bleiben. Erhöht die Löhne, wenn Ihr die Menschen zum Bleiben ermutigen wollt." }
    { group:61, id:71, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden sie in Eurer Stadt bleiben. Schafft mehr Arbeitsplätze, indem Ihr mehr Industrien baut, wenn Ihr die Menschen zum Bleiben ermutigen wollt." }
    { group:61, id:72, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden sie in Eurer Stadt bleiben. Angesichts der Größe Eurer aktuellen Bevölkerung müsst Ihr mehr Nahrung produzieren als derzeit, wenn Ihr die Menschen zum Bleiben ermutigen wollt." }
    { group:61, id:73, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden sie in Eurer Stadt bleiben. Niedrigere Steuern werden die Menschen zum Bleiben ermutigen." }
    { group:61, id:74, text: "Wenn es zu große Unterschiede zwischen Arm und Reich gibt, neigen Menschen dazu, anderswo nach Möglichkeiten zu suchen. Bietet bessere Dienstleistungen für Eure ärmeren Nachbarschaften, um mehr Gleichgewicht zwischen Wohlhabenden und Menschen bescheidenerer Mittel zu schaffen." }
    { group:61, id:75, text: "Solange die Einwohner Eurer Stadt mit Euch zufrieden sind und ausreichend Wohnraum verfügbar ist, werden mehr Menschen kommen, um sich in Eurer Stadt niederzulassen (und Eure eigenen Bürger werden nicht in grünere Gefilde aufbrechen!). Ihr müsst Eure Stadtstimmung erhöhen, wenn Ihr wollt, dass die Menschen hier bleiben." }
    { group:61, id:76, text: "DRINGEND:   Die Stadt hat Arbeitslosigkeit von" }
    { group:61, id:77, text: "ERNST:  Die Stadt hat Arbeitslosigkeit von" }
    { group:61, id:78, text: "WICHTIG:Die Stadt hat Arbeitslosigkeit von" }
    { group:61, id:79, text: "Die Stadt hat Arbeitslosigkeit von" }
    { group:61, id:80, text: "DRINGEND:   Der Stadt fehlen" }
    { group:61, id:81, text: "ERNST:  Der Stadt fehlen" }
    { group:61, id:82, text: "WICHTIG:Der Stadt fehlen" }
    { group:61, id:83, text: "Der Stadt fehlen" }
    { group:61, id:84, text: "Die Stadt hat keine Beschäftigungsprobleme" }
    { group:61, id:85, text: "Hohe Arbeitslosigkeit wird Euer Volk dazu bringen, anderswo nach Arbeit zu suchen. Baut mehr Industrie, um einige Arbeitsplätze zu schaffen." }
    { group:61, id:86, text: "Hohe Arbeitslosigkeit kann Euer Volk dazu bringen, anderswo nach Arbeit zu suchen. Ihr könnt mehr Arbeitsplätze schaffen, indem Ihr zusätzliche Industrien baut." }
    { group:61, id:87, text: "Hohe Arbeitslosigkeit kann Euer Volk dazu bringen, anderswo nach Arbeit zu suchen. Ihr könnt mehr Arbeitsplätze schaffen, indem Ihr zusätzliche Industrien baut." }
    { group:61, id:88, text: "Dieses Maß an Arbeitslosigkeit ist erträglich, aber wenn sie zu hoch wird, könnte Euer Volk anderswo nach Arbeit suchen. Ihr könnt zusätzliche Arbeitsplätze schaffen, indem Ihr mehr Industrien baut." }
    { group:61, id:89, text: "Ein schwerer Arbeitskräftemangel wie dieser wird Eure Stadt zum Stillstand bringen. Legt unnötige Industrien still, oder lockt mehr Arbeiter mit freien Wohnungen und einer glücklichen Bevölkerung an." }
    { group:61, id:90, text: "Ein schwerer Arbeitskräftemangel wird Eure Bürger daran hindern, ihre täglichen Aufgaben zu erfüllen. Legt unnötige Industrien still, oder lockt mehr Arbeiter mit freien Wohnungen und einer glücklichen Bevölkerung an." }
    { group:61, id:91, text: "Ohne genug Arbeiter haben Eure Bürger Schwierigkeiten, ihre täglichen Aufgaben auszuführen." }
    { group:61, id:92, text: "Arbeitskräftemangel kann zu einer Verringerung von Waren und Dienstleistungen in der ganzen Stadt führen. Macht Eure Stadt effizienter, indem Ihr unnötige Industrien stilllegt, oder lockt mehr Arbeiter mit freien Wohnungen und einer glücklichen Bevölkerung an." }
    { group:61, id:93, text: "Hohe Arbeitslosigkeit kann dazu führen, dass Eure sonst glücklichen Bürger die Stadt auf der Suche nach Arbeit verlassen, während Arbeitskräftemangel zu einer Verringerung von Waren und Dienstleistungen in der ganzen Stadt führen kann." }
    { group:61, id:94, text: "Die Hauptstadt versorgt all unsere Bedürfnisse" }
    { group:61, id:95, text: "DRINGEND:    Unsere Nahrungsvorräte sind niedrig" }
    { group:61, id:96, text: "ERNST:   Unsere Nahrungsvorräte sind niedrig" }
    { group:61, id:97, text: "WICHTIG: Unsere Nahrungsvorräte sind niedrig" }
    { group:61, id:98, text: "Vorräte für" }
    { group:61, id:99, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Stellt sicher, dass Euer Volk nicht mehr isst, als es produziert, und dass Ihr ausreichende Getreidespeicher habt, um die geernteten Früchte zu lagern." }
    { group:61, id:100, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Stellt sicher, dass Euer Volk nicht mehr isst, als es produziert, und dass Ihr ausreichende Getreidespeicher habt, um die geernteten Früchte zu lagern." }
    { group:61, id:101, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Stellt sicher, dass Euer Volk nicht mehr isst, als es produziert, und dass Ihr ausreichende Getreidespeicher habt, um die geernteten Früchte zu lagern." }
    { group:61, id:102, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Stellt sicher, dass Euer Volk nicht mehr isst, als es produziert, und dass Ihr ausreichende Getreidespeicher habt, um die geernteten Früchte zu lagern." }
    { group:61, id:103, text: "DRINGEND: Gesundheit der Stadt ist entsetzlich-Seuche ist unmittelbar bevorstehend." }
    { group:61, id:104, text: "DRINGEND: Gesundheit der Stadt ist schrecklich-Seuche ist wahrscheinlich." }
    { group:61, id:105, text: "ERNST: Gesundheit der Stadt ist schlecht-es besteht Seuchengefahr." }
    { group:61, id:106, text: "WICHTIG: Gesundheit der Stadt ist dürftig - etwas Seuchengefahr." }
    { group:61, id:107, text: "Gesundheit der Stadt ist unterdurchschnittlich." }
    { group:61, id:108, text: "Gesundheit der Stadt ist durchschnittlich." }
    { group:61, id:109, text: "Gesundheit der Stadt ist gut." }
    { group:61, id:110, text: "Gesundheit der Stadt ist sehr gut." }
    { group:61, id:111, text: "Gesundheit der Stadt ist ausgezeichnet." }
    { group:61, id:112, text: "Gesundheit der Stadt ist fast perfekt." }
    { group:61, id:113, text: "Gesundheit der Stadt ist perfekt." }
    { group:61, id:114, text: "Bei so vielen Menschen in so schlechter Gesundheit ist eine weit verbreitete Seuche fast sicher, die die Stadt dezimieren wird. Baut Arztpraxen und Leichenhallen für die Menschen, die derzeit keinen Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten haben, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:115, text: "Mit so vielen ungesunden Menschen wird wahrscheinlich bald eine weit verbreitete Seuche zuschlagen und könnte die Stadt dezimieren. Baut Arztpraxen und Leichenhallen für die Menschen, die derzeit keinen Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten haben, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:116, text: "Mit so vielen ungesunden Menschen in der Stadt ist es schwer für Apotheker und Ärzte, Schritt zu halten. Eure Stadt läuft Gefahr einer weit verbreiteten Seuche, die ihre Bevölkerung verwüsten kann. Baut Arztpraxen und Leichenhallen für die Menschen, die derzeit keinen Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten haben, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:117, text: "Mit so vielen ungesunden Menschen in der Stadt ist es schwer für Apotheker und Ärzte, Schritt zu halten. Eure Stadt könnte von einer Seuche heimgesucht werden, die die Bevölkerung verwüsten kann. Baut Arztpraxen und Leichenhallen für die Menschen, die derzeit keinen Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten haben, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:118, text: "Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte die Stadt von einer Seuche verwüstet werden. Baut Arztpraxen und Leichenhallen für die Unglücklichen, die derzeit keinen Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten haben, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:119, text: "Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte die Stadt an einer Seuche leiden, die die Bevölkerung dezimieren kann. Baut Arztpraxen und Leichenhallen für die Unglücklichen, denen der Zugang zu den von Ärzten und Einbalsamierern angebotenen Diensten fehlt, und stellt sicher, dass Eure Bürger ausreichende Nahrungsvorräte haben." }
    { group:61, id:120, text: "Gute Gesundheit ist wichtig, um Malaria und Krankheiten einzudämmen, und besonders um Seuchen in der ganzen Stadt zu verhindern. Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte eine Seuche die Bevölkerung der Stadt verwüsten. Ärzte und Einbalsamierer, bereitgestellt durch Arztpraxen und Leichenhallen, helfen, die Stadt gesund zu halten, ebenso wie eine gute Versorgung mit mehreren Nahrungsarten." }
    { group:61, id:121, text: "Gute Gesundheit ist wichtig, um Malaria und Krankheiten einzudämmen, und besonders um Seuchen in der ganzen Stadt zu verhindern. Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte eine Seuche die Bevölkerung der Stadt verwüsten. Ärzte und Einbalsamierer, bereitgestellt durch Arztpraxen und Leichenhallen, helfen, die Stadt gesund zu halten, ebenso wie eine gute Versorgung mit mehreren Nahrungsarten." }
    { group:61, id:122, text: "Gute Gesundheit ist wichtig, um Malaria und Krankheiten einzudämmen, und besonders um Seuchen in der ganzen Stadt zu verhindern. Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte eine Seuche die Bevölkerung der Stadt verwüsten. Ärzte und Einbalsamierer, bereitgestellt durch Arztpraxen und Leichenhallen, helfen, die Stadt gesund zu halten, ebenso wie eine gute Versorgung mit mehreren Nahrungsarten." }
    { group:61, id:123, text: "Gute Gesundheit ist wichtig, um Malaria und Krankheiten einzudämmen, und besonders um Seuchen in der ganzen Stadt zu verhindern. Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte eine Seuche die Bevölkerung der Stadt verwüsten. Ärzte und Einbalsamierer, bereitgestellt durch Arztpraxen und Leichenhallen, helfen, die Stadt gesund zu halten, ebenso wie eine gute Versorgung mit mehreren Nahrungsarten." }
    { group:61, id:124, text: "Gute Gesundheit ist wichtig, um Malaria und Krankheiten einzudämmen, und besonders um Seuchen in der ganzen Stadt zu verhindern. Wenn sich die Gesundheit ihrer Bevölkerung verschlechtert, könnte eine Seuche die Bevölkerung der Stadt verwüsten. Ärzte und Einbalsamierer, bereitgestellt durch Arztpraxen und Leichenhallen, helfen, die Stadt gesund zu halten, ebenso wie eine gute Versorgung mit mehreren Nahrungsarten." }
    { group:61, id:125, text: "WICHTIG: Mehrere Götter sind nicht besänftigt" }
    { group:61, id:126, text: "ERNST: Mehrere Götter könnten uns niederschlagen" }
    { group:61, id:127, text: "WICHTIG: Drei Götter sind nicht besänftigt" }
    { group:61, id:128, text: "ERNST: Drei Götter sind nicht besänftigt" }
    { group:61, id:129, text: "WICHTIG: Zwei Götter sind nicht besänftigt" }
    { group:61, id:130, text: "ERNST: Zwei Götter sind nicht besänftigt" }
    { group:61, id:131, text: "WICHTIG: Ein Gott ist nicht besänftigt" }
    { group:61, id:132, text: "ERNST: Ein Gott ist nicht besänftigt" }
    { group:61, id:133, text: "Alle Götter sind ausreichend besänftigt" }
    { group:61, id:134, text: "Alle Götter sind besänftigt. Einer ist besonders glücklich" }
    { group:61, id:135, text: "Alle Götter sind besänftigt. Zwei sind besonders glücklich" }
    { group:61, id:136, text: "Alle Götter sind besänftigt. Drei sind besonders glücklich" }
    { group:61, id:137, text: "Alle Götter sind besänftigt. Mehrere sind besonders glücklich" }
    { group:61, id:138, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:139, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:140, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:141, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:142, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:143, text: "Feindliche Götter können ihre Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:144, text: "Ein zorniger Gott kann seine Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:145, text: "Ein zorniger Gott kann seine Kräfte einsetzen, um Eure Stadt zu verwüsten. Um sie zu besänftigen, baut ihnen Tempel und haltet Festivals zu ihren Ehren ab." }
    { group:61, id:146, text: "Wenn Götter feindlich werden, könnten sie ihre Kräfte einsetzen, um Eure Stadt zu verwüsten.  " }
    { group:61, id:147, text: "Wohlwollende Götter können ihre Kräfte einsetzen, um Eure Stadt auf verschiedene Weisen zu segnen. Haltet die Götter besänftigt, indem Ihr ihnen Tempel widmet, und haltet weiterhin Festivals zu ihren Ehren ab, während Eure Stadt wächst." }
    { group:61, id:148, text: "Wohlwollende Götter können ihre Kräfte einsetzen, um Eure Stadt auf verschiedene Weisen zu segnen. Haltet die Götter besänftigt, indem Ihr ihnen Tempel widmet, und haltet weiterhin Festivals zu ihren Ehren ab, während Eure Stadt wächst." }
    { group:61, id:149, text: "Wohlwollende Götter können ihre Kräfte einsetzen, um Eure Stadt auf verschiedene Weisen zu segnen. Haltet die Götter besänftigt, indem Ihr ihnen Tempel widmet, und haltet weiterhin Festivals zu ihren Ehren ab, während Eure Stadt wächst." }
    { group:61, id:150, text: "Wohlwollende Götter können ihre Kräfte einsetzen, um Eure Stadt auf verschiedene Weisen zu segnen. Haltet die Götter besänftigt, indem Ihr ihnen Tempel widmet, und haltet weiterhin Festivals zu ihren Ehren ab, während Eure Stadt wächst." }
    { group:61, id:151, text: "ERNST: Wir sammeln die meisten geschuldeten Steuern nicht ein!" }
    { group:61, id:152, text: "Dieses Jahr sind die Vermögenswerte gestiegen um " }
    { group:61, id:153, text: "Wir machen es ungefähr so gut wie letztes Jahr." }
    { group:61, id:154, text: "Dieses Jahr sind die Vermögenswerte gefallen um " }
    { group:61, id:155, text: "Ihr verzichtet auf eine erhebliche Summe Geld, weil Eure Stadt nicht genug Steuereintreiber auf den Straßen hat. Baut mehr Steuereintreiber, besonders in Gebieten mit höherem Wohnniveau, und verwendet die Steuer-Überlagerung, um sicherzustellen, dass jeder von einem Steuereintreiber besucht wird." }
    { group:61, id:156, text: "Wenn Euch das Geld ausgeht, wird Eure Schatzkammer bis zu 5.000 Deben leihen. Jedoch hat es sehr ernste Konsequenzen, längere Zeit verschuldet zu bleiben. Steuern, Exporte und Goldabbau sind die besten Wege, um Einnahmen für die Stadt zu bringen. Klickt 'Hilfe' in der Menüleiste und wählt 'Schulden', um mehr zu erfahren." }
    { group:61, id:157, text: "Wenn Euch das Geld ausgeht, wird Eure Schatzkammer bis zu 5.000 Deben leihen. Jedoch hat es sehr ernste Konsequenzen, längere Zeit verschuldet zu bleiben. Steuern, Exporte und Goldabbau sind die besten Wege, um Einnahmen für die Stadt zu bringen. Klickt 'Hilfe' in der Menüleiste und wählt 'Schulden', um mehr zu erfahren." }
    { group:61, id:158, text: "Wenn Ihr weiterhin Geld verliert, müsst Ihr Eure Kreditlinie anzapfen. Die Stadtkasse kann bis zu 5.000 Deben leihen, aber verschuldet zu bleiben hat ernste Konsequenzen. Steuern, Exporte und Goldabbau sind die besten Wege, um Einnahmen für die Stadt zu bringen. Klickt 'Hilfe' in der Menüleiste und wählt 'Schulden', um mehr zu erfahren." }
    { group:61, id:159, text: "DRINGEND: Viele kürzliche Diebstähle," }
    { group:61, id:160, text: "ERNST: Mehrere kürzliche Diebstähle," }
    { group:61, id:161, text: "WICHTIG: Einige kürzliche Diebstähle," }
    { group:61, id:162, text: "Sehr wenige Diebstähle." }
    { group:61, id:163, text: "Keine Diebstähle gemeldet" }
    { group:61, id:164, text: "db gestohlen." }
    { group:61, id:165, text: "So viel Diebstahl kann Eure Stadtkasse oder sogar Eure eigenen Familienersparnisse ernsthaft leeren! Eine angemessene Anzahl von Gerichtsgebäuden und Polizeistationen hilft, Verbrechen zu verhindern, und Konstable überwältigen jeden Dieb, dem sie begegnen. Euer Volk glücklich zu halten ist der beste Weg, um Verbrechen von vornherein abzuschrecken." }
    { group:61, id:166, text: "Häufige Diebstähle können Eure Stadtkasse oder sogar Eure eigenen Familienersparnisse leeren! Angemessene Gerichtsgebäude und Polizeistationen helfen, Verbrechen zu verhindern, und Konstable werden jeden Dieb überwältigen, dem sie begegnen. Natürlich ist es der beste Weg, Euer Volk glücklich zu halten, um Verbrechen von vornherein abzuschrecken." }
    { group:61, id:167, text: "Häufige Diebstähle können die Finanzen Eurer Stadt und sogar die Ersparnisse Eurer eigenen Familie schwächen! Angemessene Gerichtsgebäude und Polizeistationen helfen, Verbrechen zu verhindern, und Konstable werden jeden Dieb überwältigen, dem sie begegnen. Natürlich ist es der beste Weg, Euer Volk glücklich zu halten, um Verbrechen von vornherein abzuschrecken." }
    { group:61, id:168, text: "Häufige Diebstähle können die Finanzen Eurer Stadt und sogar die Ersparnisse Eurer eigenen Familie schwächen! Angemessene Gerichtsgebäude und Polizeistationen helfen, Verbrechen zu verhindern, und Konstable werden jeden Dieb überwältigen, dem sie begegnen. Natürlich ist es der beste Weg, Euer Volk glücklich zu halten, um Verbrechen von vornherein abzuschrecken." }
    { group:61, id:169, text: "Diebstahl kann die Finanzen Eurer Stadt und sogar Eure Familienersparnisse schädigen! Eine angemessene Anzahl von Gerichtsgebäuden und Polizeistationen hilft, Verbrechen zu verhindern, und Konstable werden jeden Dieb überwältigen, dem sie begegnen. Natürlich ist es der beste Weg, Euer Volk glücklich zu halten, um sicherzustellen, dass sie sich nicht dem Verbrechen zuwenden." }
    { group:61, id:170, text: "Ihr habt keine Kompanien zu befehligen" }
    { group:61, id:171, text: "Wir haben keine gemeldeten Bedrohungen" }
    { group:61, id:172, text: "Feinde nähern sich der Stadt" }
    { group:61, id:173, text: "Feinde greifen die Stadt an" }
    { group:61, id:174, text: "Feindliche Truppen vor unseren Toren" }
    { group:61, id:175, text: "Unsere Truppen werden anderswo benötigt" }
    { group:61, id:176, text: "Wir haben Truppen anderswo" }
    { group:61, id:177, text: "Es stehen uns keine Streitkräfte zur Verfügung. Derzeit besteht kein Bedarf, da alles sicher ist." }
    { group:61, id:178, text: "Wenn Feinde auf unsere Stadt vorrücken würden, würdet Ihr sicherlich eine Nachricht erhalten. Feindliche Armeen erscheinen auch auf der Weltkarte, sodass Ihr ihren Vormarsch beobachten und hoffentlich die Stadt bereit haben könnt, wenn sie ankommen." }
    { group:61, id:179, text: "Eine feindliche Armee rückt vor, um die Stadt anzugreifen! Es kann schwierig oder unmöglich sein, Gebäude während eines Angriffs zu errichten, also bereitet Eure Verteidigung vor, indem Ihr jetzt Mauern, Türme, Torhäuser und Forts baut, solange Ihr noch könnt.  " }
    { group:61, id:180, text: "Es ist immer am besten, auf Angriffe vorbereitet zu sein, anstatt zu versuchen, in letzter Minute Truppen einzuberufen. Hoffentlich haben wir angemessene Verteidigungen, um die Stadt zu schützen." }
    { group:61, id:181, text: "Es ist immer am besten, auf Angriffe vorbereitet zu sein, anstatt zu versuchen, in letzter Minute Truppen einzuberufen. Hoffentlich haben wir angemessene Verteidigungen, um die Stadt zu schützen." }
    { group:61, id:182, text: "Wir haben eine Anfrage nach Truppen von einem ägyptischen Kameraden erhalten. Es ist normalerweise am besten, solche Anfragen zu erfüllen, wenn Ihr in gutem Einvernehmen mit dem Rest des Königreichs bleiben wollt. Konsultiert den Politischen Aufseher sowie den Aufseher des Militärs, um Truppen zu entsenden." }
    { group:61, id:183, text: "Einige unserer Truppen dienen Ägypten in weit entfernten Militärkampagnen. Es ist generell gut, das Königreich zu unterstützen, indem man Truppen schickt, um bei Bedarf auszuhelfen, wenn Ihr Euren guten Namen in ganz Ägypten bewahren wollt." }
    { group:61, id:184, text: "Es gibt viele ausstehende Anfragen an unsere Stadt." }
    { group:61, id:185, text: "Es gibt mehrere ausstehende Anfragen an unsere Stadt." }
    { group:61, id:186, text: "Es gibt einige ausstehende Anfragen an unsere Stadt." }
    { group:61, id:187, text: "Es gibt keine ausstehenden Anfragen an unsere Stadt." }
    { group:61, id:188, text: "Das Versäumnis, Anfragen des Pharaos oder Eurer Nachbarn zu erfüllen, kann verschiedene negative Auswirkungen haben. Wenn Ihr Euren ägyptischen Mitbürgern in ihrer Notzeit nicht helft, könnten sie der Armut erliegen oder in die Hände unserer Feinde fallen. Um in gutem Einvernehmen mit Euren Landsleuten zu bleiben, antwortet auf solche Anfragen bereitwillig und prompt." }
    { group:61, id:189, text: "Das Versäumnis, Anfragen des Pharaos oder Eurer Nachbarn zu erfüllen, kann verschiedene negative Auswirkungen haben. Wenn Ihr Euren ägyptischen Mitbürgern in ihrer Notzeit nicht helft, könnten sie der Armut erliegen oder in die Hände unserer Feinde fallen. Um in gutem Einvernehmen mit Euren Landsleuten zu bleiben, antwortet auf solche Anfragen bereitwillig und prompt." }
    { group:61, id:190, text: "Wenn Ihr Euren ägyptischen Mitbürgern in ihrer Notzeit nicht helft, könnten sie der Armut erliegen, in die Hände ihrer Feinde fallen oder ein anderes unerwünschtes Schicksal erleiden. Dies könnte sich nachteilig auf Handel, Preise, sogar Euren Königreichsstatus auswirken. Um in gutem Einvernehmen mit Euren Landsleuten zu bleiben, ist es am besten, auf Anfragen bereitwillig und prompt zu reagieren." }
    { group:61, id:191, text: "Um in gutem Einvernehmen mit Euren Landsleuten zu bleiben, reagiert bereitwillig und prompt auf alle Anfragen, die sie in ihrer Notzeit stellen könnten. Wenn Ihr versagt, könnten sie der Armut erliegen, in die Hände ihrer Feinde fallen oder ein anderes unerwünschtes Schicksal erleiden. Dies könnte nachteilige Auswirkungen auf Handel, Preise, sogar Euren Königreichsstatus haben. " }
    { group:61, id:192, text: "Die nächste Flut wird wahrscheinlich gänzlich ausfallen" }
    { group:61, id:193, text: "Die nächste Flut wird wahrscheinlich schlecht sein" }
    { group:61, id:194, text: "Die nächste Flut wird wahrscheinlich mittelmäßig sein" }
    { group:61, id:195, text: "Die nächste Flut sollte gut sein" }
    { group:61, id:196, text: "Die nächste Flut sollte ausgezeichnet sein" }
    { group:61, id:197, text: "Die nächste Flut sollte perfekt sein" }
    { group:61, id:198, text: "Priester, die das Nilometer interpretieren, warnen, dass die Flut dieses Jahres völlig ausfallen könnte, und der reiche, fruchtbare Schlamm des Nils Eure Felder nicht erneuern wird. Wenn Eure Stadt vom Anbau auf dem Überschwemmungsgebiet für ihre Nahrung abhängt, könnte dies das Überleben Eurer Bürger gefährden. Die Verehrung von Osiris, dem Gott der Nilflut, kann helfen, dies nächstes Jahr zu vermeiden." }
    { group:61, id:199, text: "Seher sagen eine schlechte Flut für dieses Jahr voraus. Sie befürchten, dass sehr wenig reicher, fruchtbarer Schlamm des Nils Eure Felder erneuern wird. Wenn Eure Stadt vom Anbau auf dem Überschwemmungsgebiet für ihre Nahrung abhängt, könnte dies das Überleben Eurer Bürger gefährden. Die Besänftigung von Osiris, dem Gott der Nilflut, kann helfen, dies nächstes Jahr zu vermeiden." }
    { group:61, id:200, text: "Omen deuten auf eine mittelmäßige Flut für dieses Jahr hin. Wenn sie recht haben, wird der Nil nur etwas reichen, fruchtbaren Schlamm auf Euren Feldern ablagern. Wenn Eure Stadt vom Anbau auf dem Überschwemmungsgebiet für ihre Nahrung abhängt, gefährdet dies das Überleben Eurer Bürger. Verstärkte Verehrung von Osiris, dem Gott der Nilflut, wird helfen sicherzustellen, dass dies nächstes Jahr nicht wieder geschieht." }
    { group:61, id:201, text: "Wenn Seher die Nilometer richtig lesen, wird die gute Flut, die für dieses Jahr erwartet wird, den reichen und fruchtbaren Schlamm des Nils auf die Felder Eurer Stadt ablagern. Stellt sicher, dass Osiris, der Gott der Nilflut, besänftigt bleibt, oder er könnte beschließen, diesen Segen nächstes Jahr zurückzuhalten." }
    { group:61, id:202, text: "Wenn Eure Stadt vom Anbau auf dem Überschwemmungsgebiet für ihre Nahrung abhängt, ist die Menge an reichem und fruchtbarem Schlamm, die Omen zufolge durch eine ausgezeichnete Flut auf Euren Feldern abgelagert werden könnte, ein Segen, der nicht als selbstverständlich angesehen werden sollte. Stellt sicher, dass Osiris, der Gott der Nilflut, glücklich gehalten wird, damit er diesen Segen wieder gewährt." }
    { group:61, id:203, text: "Wenn Eure Stadt vom Anbau auf dem Überschwemmungsgebiet für ihre Nahrung abhängt, ist der reichliche fruchtbare Schlamm, den Priester hoffen, dass er dieses Jahr durch die perfekte Flut auf Euren Feldern abgelagert wird, ein unermesslicher Segen, der nicht als selbstverständlich angesehen werden sollte. Betet zu Osiris, dem Gott der Nilflut, dass dies in Zukunft wieder geschehen möge." }
    { group:61, id:204, text: "Die Flut wird voraussichtlich Anfang Juni kommen" }
    { group:61, id:205, text: "Die Flut wird voraussichtlich Ende Juni kommen" }
    { group:61, id:206, text: "Die Flut wird voraussichtlich Anfang Juli kommen" }
    { group:61, id:207, text: "Die Flut wird voraussichtlich Ende Juli kommen" }
    { group:61, id:208, text: "Die Flut wird voraussichtlich Anfang August kommen" }
    { group:61, id:209, text: "Die Flut wird voraussichtlich Ende August kommen" }
    { group:61, id:210, text: "Die Flut wird voraussichtlich Anfang September kommen" }
    { group:61, id:211, text: "Die Flut wird voraussichtlich Ende September kommen" }
    { group:61, id:212, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Um eine Bevölkerung dieser Größe zu ernähren, produziert mehr Nahrung, indem Ihr mehr Farmen, Jagdhütten, Fischereikais oder Viehfarmen baut, oder importiert mehr Nahrung. Ihr könnt auch Bewässerung verwenden, um den Ertrag des Landes zu erhöhen, das Ihr derzeit bewirtschaftet." }
    { group:61, id:213, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Um eine Bevölkerung dieser Größe zu ernähren, baut mehr Farmen, Jagdhütten oder Viehfarmen, oder importiert mehr Nahrung." }
    { group:61, id:214, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Um eine Bevölkerung dieser Größe zu ernähren, baut mehr Farmen, Jagdhütten oder Viehfarmen, oder importiert mehr Nahrung." }
    { group:61, id:215, text: "Wenn Eure Bürger zu viele Mahlzeiten verpassen, werden sie ungesund (oder sie verlassen die Stadt auf der Suche nach einem besseren Lebensstil). Ihr habt ungefähr die richtige Mischung aus Farmen, Viehfarmen, Jagdhütten und importierter Nahrung, um eine Bevölkerung dieser Größe zu ernähren." }
    { group:61, id:216, text: "Wenn Eure Bürger weiterhin gut essen, werden sie wahrscheinlich gesund bleiben (und die Stadt nicht auf der Suche nach einer besseren Ernährung verlassen). Ihr habt ein paar mehr Farmen, Viehfarmen und Jagdhütten, als Ihr benötigt, um eine Bevölkerung dieser Größe zu ernähren." }
    { group:61, id:217, text: "Wenn Eure Bürger weiterhin gut essen, werden sie wahrscheinlich gesund bleiben (und die Stadt nicht auf der Suche nach einer besseren Ernährung verlassen). Ihr habt weit mehr Farmen, Viehfarmen und Jagdhütten, als Ihr benötigt, um eine Bevölkerung dieser Größe zu ernähren. " }
    { group:61, id:218, text: "Klickt auf ein Element für zusätzliche Informationen und Ratschläge  " }
    { group:62, id:0, text: "Sieg" }
    { group:62, id:1, text: "Niederlage!" }
    { group:62, id:2, text: "Klicken zum Fortfahren" }
    { group:62, id:3, text: "Fortfahren" }
    { group:62, id:4, text: "Weitere 2 Jahre regieren" }
    { group:62, id:5, text: "Weitere 5 Jahre fortfahren" }
    { group:62, id:6, text: "Neues Spiel" }
    { group:62, id:7, text: "Zur Stadt" }
    { group:62, id:8, text: "Gratulation!" }
    { group:62, id:9, text: "unbenutzt 2636 (Demo-Nachricht) " }
    { group:62, id:10, text: "Ziele" }
    { group:62, id:11, text: "Bevölkerung von" }
    { group:62, id:12, text: "Kulturbewertung von" }
    { group:62, id:13, text: "Wohlstandsbewertung von" }
    { group:62, id:14, text: "Monumentbewertung von" }
    { group:62, id:15, text: "Königreichsbewertung von" }
    { group:62, id:16, text: "Was für ein dunkles Ende eines so vielversprechenden Beginns! Euer Versagen entehrt Ägypten und Eure Vorfahren und befleckt die Namen noch ungeborener Nachkommen. Ihr hättet Euch der Elite anschließen können, die im Schilffeld Unsterblichkeit erreicht. Stattdessen werdet Ihr unbetrauert in den Schatten übergehen. Andere werden vortreten, um die Herausforderung des Pharaos anzunehmen... " }
    { group:62, id:17, text: "Baut einige Feuerwachen" }
    { group:62, id:18, text: "Baut einige Architektenposten" }
    { group:62, id:19, text: "Baut einen Getreidespeicher, den Jäger mit Wild füllen können" }
    { group:62, id:20, text: "Versorgt Häuser mit Nahrung von einem Basar" }
    { group:62, id:21, text: "Schafft ein Wohngebiet und beobachtet, wie Einwanderer ankommen" }
    { group:62, id:22, text: "Baut Buden und Gauklerschulen, um die Stadtkultur zu erhöhen" }
    { group:62, id:23, text: "Baut einige Tempel und Schreine für Bast" }
    { group:62, id:24, text: "Baut etwas Gold für die Schatzkammer des Palastes ab" }
    { group:62, id:25, text: "Baut Apotheken und Arztpraxen, um die Gesundheit zu verbessern" }
    { group:62, id:32, text: "Baut eine Mastaba und überprüft dann die Missionsziele" }
    { group:62, id:34, text: "Klickt auf das Ankh-Symbol, um Eure Missionsziele zu überprüfen" }
    { group:62, id:35, text: "Euer Platz in der Geschichte ist gesichert. Das ägyptische Volk erklärt Euch zum Gott." }
    { group:62, id:36, text: "Gottesstatus annehmen!" }
    { group:62, id:37, text: "Mission wiederholen" }
    { group:62, id:38, text: "Zeit abgelaufen!" }
    { group:62, id:39, text: "Ihr habt diese Mission verloren. Ihr könnt den Schwierigkeitsgrad senken, um zusätzliche Zeit zu erhalten, oder Ihr könnt die Mission erneut versuchen." }
    { group:62, id:40, text: "Schwierigkeitsgrad senken" }
    { group:63, id:0, text: "Nachrichten" }
    { group:63, id:1, text: "Ihr habt derzeit keine Nachrichten zum Lesen. Wenn Eure Stadt wächst oder andere Städte Euch um Waren bitten, werden hier Nachrichten veröffentlicht" }
    { group:63, id:2, text: "Datum" }
    { group:63, id:3, text: "Betreff" }
    { group:63, id:4, text: "Linksklick auf eine Nachricht, um sie zu lesen. Rechtsklick auf eine Nachricht, um sie zu löschen." }
    { group:63, id:5, text: "An" }
    { group:63, id:6, text: "Geöffnete Nachrichten löschen" }
    { group:64, id:0, text: "Niemand" }
    { group:64, id:1, text: "Einwanderer" }
    { group:64, id:2, text: "Auswanderer" }
    { group:64, id:3, text: "Obdachloser" }
    { group:64, id:4, text: "Lieferant" }
    { group:64, id:5, text: "Bürger" }
    { group:64, id:6, text: "Explosion" }
    { group:64, id:7, text: "Steuereintreiber" }
    { group:64, id:8, text: "Architekt" }
    { group:64, id:9, text: "Lagerarbeiter" }
    { group:64, id:10, text: "Feuerwehrmann" }
    { group:64, id:11, text: "Bogenschütze" }
    { group:64, id:12, text: "Streitwagenlenker" }
    { group:64, id:13, text: "Infanterist" }
    { group:64, id:14, text: "Fahnenträger" }
    { group:64, id:15, text: "Gaukler" }
    { group:64, id:16, text: "Musiker" }
    { group:64, id:17, text: "Tänzer" }
    { group:64, id:18, text: "Senet-Spieler" }
    { group:64, id:19, text: "Karawane von Händlern aus" }
    { group:64, id:20, text: "Handelsschiff aus" }
    { group:64, id:21, text: "Karawane von Händlern aus" }
    { group:64, id:22, text: "Protestler" }
    { group:64, id:23, text: "Krimineller" }
    { group:64, id:24, text: "Grabräuber" }
    { group:64, id:25, text: "Fischerboot" }
    { group:64, id:26, text: "Basarhändler" }
    { group:64, id:27, text: "Priester" }
    { group:64, id:28, text: "Schulkind" }
    { group:64, id:29, text: "Lehrer" }
    { group:64, id:30, text: "Bibliothekar" }
    { group:64, id:31, text: "Zahnarzt" }
    { group:64, id:32, text: "Arzt" }
    { group:64, id:33, text: "Kräuterkundiger" }
    { group:64, id:34, text: "Einbalsamierer" }
    { group:64, id:35, text: "Arbeiter" }
    { group:64, id:36, text: "Kartenflagge" }
    { group:64, id:37, text: "Treibgut" }
    { group:64, id:38, text: "Hafenarbeiter" }
    { group:64, id:39, text: "Basarkäufer" }
    { group:64, id:40, text: "Schreiber" }
    { group:64, id:41, text: "Eingeborener (nicht verwendet?)" }
    { group:64, id:42, text: "Wache" }
    { group:64, id:43, text: "Feind" }
    { group:64, id:44, text: "Feind" }
    { group:64, id:45, text: "Feind" }
    { group:64, id:46, text: "Feind" }
    { group:64, id:47, text: "Feind" }
    { group:64, id:48, text: "Feind" }
    { group:64, id:49, text: "unbenutzt 2722" }
    { group:64, id:50, text: "unbenutzt 2723" }
    { group:64, id:51, text: "unbenutzt 2724" }
    { group:64, id:52, text: "unbenutzt 2725" }
    { group:64, id:53, text: "Feind" }
    { group:64, id:54, text: "Feind" }
    { group:64, id:55, text: "Feind" }
    { group:64, id:56, text: "Feind" }
    { group:64, id:57, text: "Feind" }
    { group:64, id:58, text: "unbenutzt 2731" }
    { group:64, id:59, text: "Pfeil" }
    { group:64, id:60, text: "Speer" }
    { group:64, id:61, text: "Bolzen" }
    { group:64, id:62, text: "Balliste" }
    { group:64, id:63, text: "Kreatur" }
    { group:64, id:64, text: "Missionar" }
    { group:64, id:65, text: "Möwen" }
    { group:64, id:66, text: "Lieferbote" }
    { group:64, id:67, text: "Schiffswrack" }
    { group:64, id:68, text: "Vögel" }
    { group:64, id:69, text: "Strauß" }
    { group:64, id:70, text: "Antilope" }
    { group:64, id:71, text: "Speer" }
    { group:64, id:72, text: "Wagenrennen-Fahrer" }
    { group:64, id:73, text: "Jäger" }
    { group:64, id:74, text: "Speer des Jägers" }
    { group:64, id:75, text: "Holzfäller" }
    { group:64, id:76, text: "Fährboot" }
    { group:64, id:77, text: "Transportschiff" }
    { group:64, id:78, text: "Kriegsschiff" }
    { group:64, id:79, text: "Zimmermann" }
    { group:64, id:80, text: "Maurer" }
    { group:64, id:81, text: "Steinmetz" }
    { group:64, id:82, text: "Krokodil" }
    { group:64, id:83, text: "Hyäne" }
    { group:64, id:84, text: "Nilpferd" }
    { group:64, id:85, text: "Arbeiter" }
    { group:64, id:86, text: "Schlitten" }
    { group:64, id:87, text: "Wasserträger" }
    { group:64, id:88, text: "Konstable" }
    { group:64, id:89, text: "Magistrat" }
    { group:64, id:90, text: "Schilfsammler" }
    { group:64, id:91, text: "Festpriester" }
    { group:64, id:92, text: "Feindliches Transportschiff" }
    { group:64, id:93, text: "Feindliches Kriegsschiff" }
    { group:64, id:94, text: "Trauergänger" }
    { group:64, id:95, text: "Fisch" }
    { group:64, id:96, text: "Schlittenzieher" }
    { group:64, id:97, text: "Schausteller" }
    { group:64, id:98, text: "Verseuchter Bürger" }
    { group:64, id:99, text: "Beduinen-Infanterie" }
    { group:64, id:100, text: "Ägyptisches Kriegsschiff" }
    { group:64, id:101, text: "Ägyptisches Transportschiff" }
    { group:64, id:102, text: "Kobra" }
    { group:64, id:103, text: "Löwe" }
    { group:64, id:104, text: "Skorpion" }
    { group:64, id:105, text: "Zoowärter" }
    { group:64, id:106, text: "Frosch" }
    { group:64, id:107, text: "Heuschrecke" }
    { group:64, id:108, text: "Grabhandwerker" }
    { group:64, id:109, text: "Mumie" }
    { group:65, id:0, text: "unbenutzte Sektion 65 - war c3 Walker-Namen" }
    { group:66, id:0, text: "Intelligente Overlay-Hilfe." }
    { group:66, id:1, text: "Dieses Land hat eine Grundwasserversorgung für Brunnen und Wasserversorgung" }
    { group:66, id:2, text: "Diese Wohnung hat keinen Zugang zu Trinkwasser" }
    { group:66, id:3, text: "Diese Wohnung hat nur einfachen Trinkwasserzugang" }
    { group:66, id:4, text: "Dieses Haus hat keine Nahrungsvorräte" }
    { group:66, id:5, text: "Dieses Haus wird bald seine begrenzten Nahrungsvorräte aufgebraucht haben" }
    { group:66, id:6, text: "Dieses Haus hat Nahrungsvorräte für mindestens den kommenden Monat" }
    { group:66, id:7, text: "Dieses Haus hat keine Probleme, die Nahrung zu bekommen, die es zum Überleben braucht" }
    { group:66, id:8, text: "Dieses Haus erhält keine Lieferungen von sauberem Trinkwasser" }
    { group:66, id:9, text: "Dieses Haus wurde kürzlich von einem Wasserträger besucht. Es wird für lange Zeit sauberes Trinkwasser haben" }
    { group:66, id:10, text: "Dieses Haus hat Vorräte an sauberem Trinkwasser" }
    { group:66, id:11, text: "Wenn nicht bald ein Wasserträger vorbeikommt, wird dieses Haus seine Vorräte an sauberem Trinkwasser aufbrauchen" }
    { group:66, id:12, text: "Dieses Haus hat keinen Zugang zu Tempeln oder Schreinen" }
    { group:66, id:13, text: "Dieses Haus hat nur Zugang zu einem Tempel eines einzelnen Gottes" }
    { group:66, id:14, text: "Dieses Haus hat Zugang zu Tempeln von 2 verschiedenen Göttern" }
    { group:66, id:15, text: "Dieses Haus hat Zugang zu Tempeln von 3 verschiedenen Göttern" }
    { group:66, id:16, text: "Dieses Haus hat Zugang zu Tempeln von 4 verschiedenen Göttern" }
    { group:66, id:17, text: "Dieses Haus hat Zugang zu Tempeln aller Götter" }
    { group:66, id:18, text: "Dieses Haus hat Zugang zu einem Schrein und Tempeln aller Götter" }
    { group:66, id:19, text: "Dieses Haus hat keinen Zugang zu einer Schreibschule" }
    { group:66, id:20, text: "Dieses Haus wurde kürzlich von einem Gelehrten besucht. Es wird für lange Zeit Zugang zur Schreibschule haben" }
    { group:66, id:21, text: "Dieses Haus hat Zugang zur Schreibschule" }
    { group:66, id:22, text: "Wenn nicht bald ein Gelehrter vorbeikommt, wird dieses Haus den Zugang zur Schreibschule verlieren" }
    { group:66, id:23, text: "Dieses Haus hat keinen Zugang zu einer Bibliothek" }
    { group:66, id:24, text: "Dieses Haus wurde kürzlich von einem Bibliothekar besucht. Es wird für lange Zeit Bibliothekszugang haben" }
    { group:66, id:25, text: "Dieses Haus hat Bibliothekszugang" }
    { group:66, id:26, text: "Wenn nicht bald ein Bibliothekar vorbeikommt, wird dieses Haus den Bibliothekszugang verlieren" }
    { group:66, id:27, text: "Dieses Haus hat keinen Zugang zu einer Akademie" }
    { group:66, id:28, text: "Dieses Haus wurde kürzlich von einem Lehrer besucht. Es wird für lange Zeit Akademiezugang haben" }
    { group:66, id:29, text: "Dieses Haus hat Akademiezugang" }
    { group:66, id:30, text: "Wenn nicht bald ein Lehrer vorbeikommt, wird dieses Haus den Akademiezugang verlieren" }
    { group:66, id:31, text: "Dieses Haus hat keinen Zugang zu einer Zahnarztpraxis" }
    { group:66, id:32, text: "Dieses Haus wurde kürzlich von einem Zahnarzt besucht. Es wird für lange Zeit Zahnarztzugang haben" }
    { group:66, id:33, text: "Dieses Haus hat Zahnarztzugang" }
    { group:66, id:34, text: "Wenn nicht bald ein Zahnarzt vorbeikommt, wird dieses Haus den Zugang zur Zahnarztpraxis verlieren" }
    { group:66, id:35, text: "Dieses Haus hat keinen Zugang zu einer Apotheke" }
    { group:66, id:36, text: "Dieses Haus wurde kürzlich von einem Kräuterkundigen besucht. Es wird für lange Zeit Apothekenzugang haben" }
    { group:66, id:37, text: "Dieses Haus hat Apothekenzugang" }
    { group:66, id:38, text: "Wenn nicht bald ein Kräuterkundiger vorbeikommt, wird dieses Haus den Apothekenzugang verlieren" }
    { group:66, id:39, text: "Dieses Haus hat keinen Zugang zu einer Leichenhalle" }
    { group:66, id:40, text: "Dieses Haus wurde kürzlich von einem Einbalsamierer besucht. Es wird für lange Zeit Leichenhallenzugang haben" }
    { group:66, id:41, text: "Dieses Haus hat Leichenhallenzugang" }
    { group:66, id:42, text: "Wenn nicht bald ein Einbalsamierer vorbeikommt, wird dieses Haus den Leichenhallenzugang verlieren" }
    { group:66, id:43, text: "Dieses Haus ist nicht für Steuern registriert und zahlt daher keine Steuern" }
    { group:66, id:44, text: "Bisher dieses Jahr keine Steuern von diesem Haus eingezogen." }
    { group:66, id:45, text: " Deben bisher dieses Jahr eingezogen." }
    { group:66, id:46, text: "Dieses Gebäude hat keine Brandgefahr" }
    { group:66, id:47, text: "Dieses Gebäude hat eine vernachlässigbare Brandgefahr" }
    { group:66, id:48, text: "Dieses Gebäude hat etwas Brandgefahr" }
    { group:66, id:49, text: "Dieses Gebäude hat Brandgefahr" }
    { group:66, id:50, text: "Dieses Gebäude ist eine Brandfalle" }
    { group:66, id:51, text: "Dieses Gebäude könnte jeden Moment in Brand geraten!" }
    { group:66, id:52, text: "Dieses Gebäude ist in perfektem baulichem Zustand" }
    { group:66, id:53, text: "Dieses Gebäude hat eine vernachlässigbare Einsturzgefahr" }
    { group:66, id:54, text: "Dieses Gebäude hat eine geringe Einsturzgefahr" }
    { group:66, id:55, text: "Dieses Gebäude hat einige bauliche Mängel" }
    { group:66, id:56, text: "Dieses Gebäude hat viele bauliche Mängel und Risse" }
    { group:66, id:57, text: "Dieses Gebäude ist instabil und wird wahrscheinlich bald einstürzen" }
    { group:66, id:58, text: "Dies ist eine sehr gesetzestreue Nachbarschaft, ohne jegliche gemeldete Verbrechen" }
    { group:66, id:59, text: "Es gibt nur gelegentlich Verbrechen in dieser Gegend" }
    { group:66, id:60, text: "Dies ist ein Gebiet mit niedriger Kriminalität, aber ein paar Bewohner haben sich beschwert" }
    { group:66, id:61, text: "Mehrere Verbrechen wurden hier kürzlich gemeldet, aber insgesamt ist diese Nachbarschaft einigermaßen sicher" }
    { group:66, id:62, text: "Dies ist ein Gebiet mit hoher Kriminalität. Bewohner sind unglücklich und die Straßen sind nachts nicht sicher" }
    { group:66, id:63, text: "Diese ganze Gegend ist ein Pulverfass der Unruhe! Verbrechen ist endemisch und alles könnte passieren" }
    { group:66, id:64, text: "Diese Wohnung hat überhaupt keinen Zugang zu Unterhaltung" }
    { group:66, id:65, text: "Diese Wohnung hat kaum Zugang zu Unterhaltung" }
    { group:66, id:66, text: "Diese Wohnung hat sehr begrenzten Zugang zu Unterhaltungsangeboten" }
    { group:66, id:67, text: "Diese Wohnung hat begrenzten Zugang zu Unterhaltungsangeboten" }
    { group:66, id:68, text: "Diese Wohnung hat etwas Zugang zu Unterhaltungsangeboten" }
    { group:66, id:69, text: "Diese Wohnung hat Zugang zu mehreren Unterhaltungsangeboten" }
    { group:66, id:70, text: "Diese Wohnung hat angemessenen Zugang zu Unterhaltungsangeboten" }
    { group:66, id:71, text: "Diese Wohnung hat guten Zugang zu Unterhaltungsangeboten" }
    { group:66, id:72, text: "Diese Wohnung hat sehr guten Zugang zu Unterhaltungsangeboten" }
    { group:66, id:73, text: "Diese Wohnung hat ausgezeichneten Zugang zu Unterhaltungsangeboten" }
    { group:66, id:74, text: "Diese Wohnung hat Zugang zu aller Unterhaltung, die sie sich wünschen könnte" }
    { group:66, id:75, text: "Dieses Haus hat keinen Zugang zu einem Gaukler" }
    { group:66, id:76, text: "Dieses Haus wurde kürzlich von einem Gaukler besucht. Es wird für lange Zeit Gauklerzugang haben" }
    { group:66, id:77, text: "Dieses Haus hat Gauklerzugang" }
    { group:66, id:78, text: "Dieses Haus wurde eine Weile nicht von einem Gaukler besucht. Es wird bald den Gauklerzugang verlieren" }
    { group:66, id:83, text: "Dieses Haus hat keinen Zugang zu einer Tanzbühne" }
    { group:66, id:84, text: "Dieses Haus wurde kürzlich von einem Tänzer besucht. Es wird für lange Zeit Tanzbühnenzugang haben" }
    { group:66, id:85, text: "Dieses Haus hat Tanzbühnenzugang" }
    { group:66, id:86, text: "Dieses Haus wurde eine Weile nicht von einem Tänzer besucht. Es wird bald den Tanzzugang verlieren" }
    { group:66, id:87, text: "Dieses Haus hat keinen Zugang zu einem Senet-Haus" }
    { group:66, id:88, text: "Dieses Haus wurde kürzlich von einem Senet-Meister besucht. Es wird für lange Zeit Senet-Haus-Zugang haben" }
    { group:66, id:89, text: "Dieses Haus hat Senet-Haus-Zugang" }
    { group:66, id:90, text: "Dieses Haus wurde eine Weile nicht von einem Senet-Meister besucht. Es wird bald den Senet-Haus-Zugang verlieren" }
    { group:66, id:91, text: "ALT: Keine Bürger wollen hier leben" }
    { group:66, id:92, text: "ALT: Eure Bürger sehen keine positiven oder negativen Faktoren in Verbindung mit dieser Gegend" }
    { group:66, id:93, text: "ALT: Dieses Land ist eine begehrte Gegend" }
    { group:66, id:94, text: "Dieses Gebäude hat derzeit keinen Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:95, text: "Dieses Gebäude hat derzeit sehr wenig Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:96, text: "Dieses Gebäude hat derzeit schlechten Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:97, text: "Dieses Gebäude hat derzeit etwas Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:98, text: "Dieses Gebäude hat derzeit guten Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:99, text: "Dieses Gebäude hat derzeit ausgezeichneten Zugang zu Menschen, die es mit Arbeitskraft versorgen" }
    { group:66, id:100, text: "Dieses Haus hat keinen Zugang zu Schreibschulen oder Bibliotheken" }
    { group:66, id:101, text: "Dieses Haus hat Zugang zu einer Schreibschule oder zu einer Bibliothek" }
    { group:66, id:102, text: "Dieses Haus hat Zugang zu sowohl einer Schreibschule als auch einer Bibliothek" }
    { group:66, id:103, text: "Dieses Haus hat Zugang zu Schreibschule und Bibliothek. Seine Kinder sind auch in einem Akademiebezirk" }
    { group:66, id:104, text: "Diese Hütte sammelt ihre eigene Nahrung..." }
    { group:66, id:105, text: "Dieses Land ist überaus fruchtbar. Hier angebaute Pflanzen werden groß und stark." }
    { group:66, id:106, text: "Dieses Land ist ziemlich fruchtbar. Hier angebaute Pflanzen werden tendenziell recht gesund sein." }
    { group:66, id:107, text: "Dieses Land ist mäßig fruchtbar. Hier angebaute Pflanzen werden ihr volles Potenzial nicht erreichen." }
    { group:66, id:108, text: "Dieses Land ist nicht sehr fruchtbar. Pflanzen werden hier kaum wachsen." }
    { group:66, id:109, text: "Dieses Land ist unfruchtbar. Hier können keine Pflanzen wachsen." }
    { group:66, id:110, text: " Körbe Getreide sind in diesem Gebäude gelagert." }
    { group:66, id:111, text: " Korb Getreide ist in diesem Gebäude gelagert." }
    { group:66, id:112, text: " Krüge Obst sind in diesem Gebäude gelagert." }
    { group:66, id:113, text: " Krug Obst ist in diesem Gebäude gelagert." }
    { group:66, id:114, text: " Krüge Gemüse sind in diesem Gebäude gelagert." }
    { group:66, id:115, text: " Krug Gemüse ist in diesem Gebäude gelagert." }
    { group:66, id:116, text: " Stücke Fleisch sind in diesem Gebäude gelagert." }
    { group:66, id:117, text: " Stück Fleisch ist in diesem Gebäude gelagert." }
    { group:66, id:118, text: " Töpferwaren sind in diesem Gebäude gelagert." }
    { group:66, id:119, text: " Töpferware ist in diesem Gebäude gelagert." }
    { group:66, id:120, text: " Beutel Schmuck (Luxusgüter) sind in diesem Gebäude gelagert." }
    { group:66, id:121, text: " Beutel Schmuck (Luxusgüter) ist in diesem Gebäude gelagert." }
    { group:66, id:122, text: " Rollen Leinen sind in diesem Gebäude gelagert." }
    { group:66, id:123, text: " Rolle Leinen ist in diesem Gebäude gelagert." }
    { group:66, id:124, text: " Krüge Bier sind in diesem Gebäude gelagert." }
    { group:66, id:125, text: " Krug Bier ist in diesem Gebäude gelagert." }
    { group:66, id:126, text: "Dieses Gebäude lagert keine Waren." }
    { group:66, id:127, text: "Dieses Gebäude hat keine Krankheitsgefahr." }
    { group:66, id:128, text: "Dieses Gebäude hat eine vernachlässigbare Krankheitsgefahr." }
    { group:66, id:129, text: "Dieses Gebäude hat etwas Krankheitsgefahr." }
    { group:66, id:130, text: "Dieses Gebäude hat Krankheitsgefahr" }
    { group:66, id:131, text: "Dieses Gebäude ist krankheitsverseucht." }
    { group:66, id:132, text: "Kein Arztzugang." }
    { group:66, id:133, text: "Dieses Haus wurde eine Weile nicht von einem Arzt besucht." }
    { group:66, id:134, text: "Dieses Haus wurde von einem Arzt besucht." }
    { group:66, id:135, text: "Dieses Haus wurde kürzlich von einem Arzt besucht." }
    { group:66, id:136, text: "Dieses Gebäude hat keine Malariagefahr." }
    { group:66, id:137, text: "Dieses Gebäude hat eine vernachlässigbare Malariagefahr." }
    { group:66, id:138, text: "Dieses Gebäude hat etwas Malariagefahr." }
    { group:66, id:139, text: "Dieses Gebäude hat Malariagefahr" }
    { group:66, id:140, text: "Dieses Gebäude wird bald Malaria haben." }
    { group:66, id:141, text: "Dieses Haus hat folgende Probleme:" }
    { group:66, id:142, text: "Diese Industrie hat folgende Probleme:" }
    { group:66, id:143, text: "Einsturzgefahr" }
    { group:66, id:144, text: "Brandgefahr" }
    { group:66, id:145, text: "Krankheitsgefahr" }
    { group:66, id:146, text: "Leer" }
    { group:66, id:147, text: "Malariagefahr" }
    { group:66, id:148, text: "Erkrankt" }
    { group:66, id:149, text: "Mögliche Kriminalitätsgefahr" }
    { group:66, id:150, text: "Wird bald absteigen" }
    { group:66, id:151, text: "Fehlen Rohstoffe" }
    { group:66, id:152, text: "Keine Arbeitskräfte" }
    { group:66, id:153, text: "Teilweise Arbeitskräfte" }
    { group:66, id:154, text: "Industrie stillgelegt" }
    { group:66, id:155, text: "Sucht nach Arbeitern" }
    { group:66, id:156, text: "Von Fröschen befallen" }
    { group:66, id:157, text: "Niemand lebt in dieser Wohnung" }
    { group:66, id:158, text: "Dieses Haus hat keinen Zugang zu einem Gerichtsgebäude" }
    { group:66, id:159, text: "Dieses Haus wurde kürzlich von einem Magistrat besucht. Es wird für lange Zeit Gerichtsgebäudezugang haben" }
    { group:66, id:160, text: "Dieses Haus hat Gerichtsgebäudezugang" }
    { group:66, id:161, text: "Dieses Haus wurde eine Weile nicht von einem Magistrat besucht. Es wird bald den Gerichtsgebäudezugang verlieren" }
    { group:66, id:162, text: "Dies ist einer der unattraktivsten Orte in der Stadt" }
    { group:66, id:163, text: "Niemand würde hier bevorzugt leben, aber es gibt schlimmere Orte" }
    { group:66, id:164, text: "Die Menschen haben keine starken Gefühle über die Attraktivität dieser Gegend" }
    { group:66, id:165, text: "Diese Gegend ist besser als einige andere, obwohl nicht besonders attraktiv" }
    { group:66, id:166, text: "Die meisten Menschen würden dies als angenehmen Ort zum Leben empfinden" }
    { group:66, id:167, text: "Dies ist eine der vornehmsten Adressen in Eurer Stadt" }
    { group:66, id:168, text: "Dieses Haus hat keinen Zugang zu einem Zoo" }
    { group:66, id:169, text: "Dieses Haus wurde kürzlich von einem Zoowärter besucht. Es wird für lange Zeit Zoozugang haben" }
    { group:66, id:170, text: "Dieses Haus hat Zoozugang" }
    { group:66, id:171, text: "Dieses Haus wurde eine Weile nicht von einem Zoowärter besucht. Es wird bald den Zoozugang verlieren" }
    { group:66, id:172, text: "Dieses Haus ist von Fröschen befallen" }
    { group:67, id:0, text: "Erlaubte Gebäude" }
    { group:67, id:1, text: "Rohstoffe" }
    { group:67, id:2, text: "Goldmine" }
    { group:67, id:3, text: "Wasserheber" }
    { group:67, id:4, text: "Bewässerungsgraben" }
    { group:67, id:5, text: "Fischereiwerft" }
    { group:67, id:6, text: "Arbeitslager" }
    { group:67, id:7, text: "Getreidespeicher" }
    { group:67, id:8, text: "Basar" }
    { group:67, id:9, text: "Lagerhof" }
    { group:67, id:10, text: "Dock" }
    { group:67, id:11, text: "Jonglieren" }
    { group:67, id:12, text: "Musik" }
    { group:67, id:13, text: "Tanzen" }
    { group:67, id:14, text: "Senet-Spiele" }
    { group:67, id:15, text: "Festplatz" }
    { group:67, id:16, text: "Schreibschule" }
    { group:67, id:17, text: "Bibliothek" }
    { group:67, id:18, text: "Wasserversorgung" }
    { group:67, id:19, text: "Zahnarzt" }
    { group:67, id:20, text: "Apotheke" }
    { group:67, id:21, text: "Arzt" }
    { group:67, id:22, text: "Leichenhalle" }
    { group:67, id:23, text: "Steuereintreiber" }
    { group:67, id:24, text: "Gerichtsgebäude" }
    { group:67, id:25, text: "Palast" }
    { group:67, id:26, text: "Villa" }
    { group:67, id:27, text: "Straßensperre" }
    { group:67, id:28, text: "Brücke" }
    { group:67, id:29, text: "Fähranleger" }
    { group:67, id:30, text: "Gärten" }
    { group:67, id:31, text: "Platz" }
    { group:67, id:32, text: "Statuen" }
    { group:67, id:33, text: "Mauer" }
    { group:67, id:34, text: "Turm" }
    { group:67, id:35, text: "Torhaus" }
    { group:67, id:36, text: "Rekrutierer" }
    { group:67, id:37, text: "Fort: Infanterie" }
    { group:67, id:38, text: "Fort: Bogenschützen" }
    { group:67, id:39, text: "Fort: Streitwagenkämpfer" }
    { group:67, id:40, text: "Akademie" }
    { group:67, id:41, text: "Waffenschmied" }
    { group:67, id:42, text: "Streitwagenbauer" }
    { group:67, id:43, text: "Kriegsschiffwerft" }
    { group:67, id:44, text: "Transportschiffwerft" }
    { group:67, id:45, text: "Zoo" }
    { group:68, id:0, text: "Dies ist der Text für die Maushilfe" }
    { group:68, id:1, text: "Die relevante Hilfeseite für dieses Panel anzeigen" }
    { group:68, id:2, text: "Dieses Panel verlassen" }
    { group:68, id:3, text: "Diesen Spielstand laden" }
    { group:68, id:4, text: "Das aktuelle Spiel in diese Datei speichern" }
    { group:68, id:5, text: "Diese Operation abbrechen" }
    { group:68, id:6, text: "Durch Spielstände scrollen" }
    { group:68, id:7, text: "Auf einen Dateinamen klicken, um ihn auszuwählen" }
    { group:68, id:8, text: "Maushilfe frei" }
    { group:68, id:9, text: "Maushilfe frei" }
    { group:68, id:10, text: "Das Bedienfeld ausblenden, um einen größeren Spielbereich zu sehen" }
    { group:68, id:11, text: "Einen Stadt-Overlay-Bericht auswählen" }
    { group:68, id:12, text: "Das vollständige Bedienfeld anzeigen" }
    { group:68, id:13, text: "Dieses Spiel laden" }
    { group:68, id:14, text: "Das aktuelle Spiel in diese Datei speichern" }
    { group:68, id:15, text: "Diese Operation abbrechen" }
    { group:68, id:16, text: "Durch Missionen scrollen" }
    { group:68, id:17, text: "Auf einen Dateinamen klicken, um ihn auszuwählen" }
    { group:68, id:18, text: "Maushilfe frei" }
    { group:68, id:19, text: "Maushilfe frei" }
    { group:68, id:20, text: "Wohngebäude bauen" }
    { group:68, id:21, text: "Straßen bauen" }
    { group:68, id:22, text: "Land roden" }
    { group:68, id:23, text: "Landwirtschafts- und Nahrungsgebäude" }
    { group:68, id:24, text: "Industriegebäude" }
    { group:68, id:25, text: "Lager- und Verteilungsgebäude" }
    { group:68, id:26, text: "Unterhaltungsgebäude" }
    { group:68, id:27, text: "Religiöse Gebäude" }
    { group:68, id:28, text: "Bildungsgebäude" }
    { group:68, id:29, text: "Gesundheits- und Sanitärgebäude" }
    { group:68, id:30, text: "Städtische Gebäude" }
    { group:68, id:31, text: "Militärgebäude" }
    { group:68, id:32, text: "Eure letzte Aktion RÜCKGÄNGIG machen (nur verfügbar, wenn das Symbol aufleuchtet)" }
    { group:68, id:33, text: "Nachrichten anzeigen" }
    { group:68, id:34, text: "Durch aktuelle Problemstellen in der Stadt wechseln" }
    { group:68, id:35, text: "Eure Mission überprüfen" }
    { group:68, id:36, text: "Auf diese Übersichtskarte klicken, um zu entfernten Teilen Eurer Stadt zu gelangen" }
    { group:68, id:37, text: "Maushilfe frei" }
    { group:68, id:38, text: "Maushilfe frei" }
    { group:68, id:39, text: "Maushilfe frei" }
    { group:68, id:40, text: "Maushilfe frei" }
    { group:68, id:41, text: "Eure Aufseher besuchen" }
    { group:68, id:42, text: "Zur Weltkarte gehen" }
    { group:68, id:43, text: "Eure Mission überprüfen" }
    { group:68, id:44, text: "Eure Ansicht nach Norden ausrichten" }
    { group:68, id:45, text: "Die Ansicht im Uhrzeigersinn drehen" }
    { group:68, id:46, text: "Die Ansicht gegen den Uhrzeigersinn drehen" }
    { group:68, id:47, text: "Maushilfe frei" }
    { group:68, id:48, text: "Maushilfe frei" }
    { group:68, id:49, text: "Maushilfe frei" }
    { group:68, id:50, text: "Maushilfe frei" }
    { group:68, id:51, text: "Laden, Speichern, Neues Spiel und Beenden" }
    { group:68, id:52, text: "Ton- und Geschwindigkeitsoptionen" }
    { group:68, id:53, text: "Spielhilfe aufrufen" }
    { group:68, id:54, text: "Direkt zu bestimmten Aufseherberichten gehen" }
    { group:68, id:55, text: "Maushilfe frei" }
    { group:68, id:56, text: "Maushilfe frei" }
    { group:68, id:57, text: "Maushilfe frei" }
    { group:68, id:58, text: "Maushilfe frei" }
    { group:68, id:59, text: "Maushilfe frei" }
    { group:68, id:60, text: "Maushilfe frei" }
    { group:68, id:61, text: "Aktuelle Stadtfinanzen" }
    { group:68, id:62, text: "Aktuelle Stadtbevölkerung" }
    { group:68, id:63, text: "Das aktuelle Datum!" }
    { group:68, id:64, text: "Maushilfe frei" }
    { group:68, id:65, text: "Maushilfe frei" }
    { group:68, id:66, text: "Maushilfe frei" }
    { group:68, id:67, text: "Maushilfe frei" }
    { group:68, id:68, text: "Maushilfe frei" }
    { group:68, id:69, text: "Maushilfe frei" }
    { group:68, id:70, text: "Euren Handelsaufseher besuchen" }
    { group:68, id:71, text: "Euren Arbeiteraufseher besuchen" }
    { group:68, id:72, text: "Euren Militäraufseher besuchen" }
    { group:68, id:73, text: "Euren Politischen Aufseher besuchen" }
    { group:68, id:74, text: "Euren Bewertungsaufseher besuchen" }
    { group:68, id:75, text: "Euren Handelsaufseher besuchen" }
    { group:68, id:76, text: "Euren Getreidespeicheraufseher besuchen" }
    { group:68, id:77, text: "Euren Aufseher der öffentlichen Gesundheit besuchen" }
    { group:68, id:78, text: "Euren Bildungsaufseher besuchen" }
    { group:68, id:79, text: "Euren Unterhaltungsaufseher besuchen" }
    { group:68, id:80, text: "Euren Tempelaufseher besuchen" }
    { group:68, id:81, text: "Euren Schatzmeister besuchen" }
    { group:68, id:82, text: "Euren Oberaufseher besuchen" }
    { group:68, id:83, text: "Euren Monumentaufseher besuchen" }
    { group:68, id:84, text: "Zur Hauptstadtansicht zurückkehren" }
    { group:68, id:85, text: "Maushilfe frei" }
    { group:68, id:86, text: "Maushilfe frei" }
    { group:68, id:87, text: "Maushilfe frei" }
    { group:68, id:88, text: "Maushilfe frei" }
    { group:68, id:89, text: "Maushilfe frei" }
    { group:68, id:90, text: "Maushilfe frei" }
    { group:68, id:91, text: "Maushilfe frei" }
    { group:68, id:92, text: "Hier klicken, um eine Priorität für diese Arbeitskategorie festzulegen" }
    { group:68, id:93, text: "Den jährlichen Lohn für je 10 Arbeiter festlegen" }
    { group:68, id:94, text: "Hier klicken, um jede festgelegte Priorität für diese Aufgabe zu entfernen" }
    { group:68, id:95, text: "Auf eine Nummer klicken, um eine Prioritätsstufe festzulegen. Alle anderen Aufgabenprioritäten werden sich entsprechend anpassen" }
    { group:68, id:96, text: "Hier klicken, um der Stadt Geld zu spenden" }
    { group:68, id:97, text: "Hier klicken, um Euer persönliches Gehalt festzulegen" }
    { group:68, id:98, text: "Den Gehaltsbildschirm verlassen" }
    { group:68, id:99, text: "Diese Gehaltsstufe auswählen" }
    { group:68, id:100, text: "Den Spendenbildschirm verlassen" }
    { group:68, id:101, text: "Dieses Geld aus den Ersparnissen Eurer Familie an die Stadt spenden" }
    { group:68, id:102, text: "Den zu spendenden Betrag festlegen." }
    { group:68, id:103, text: "Den genauen Betrag anpassen, den Ihr spenden möchtet" }
    { group:68, id:104, text: "Hier klicken für Ratschläge über Eure Kulturbewertung" }
    { group:68, id:105, text: "Hier klicken für Ratschläge über Eure Wohlstandsbewertung" }
    { group:68, id:106, text: "Hier klicken für Ratschläge über Eure Monumentbewertung" }
    { group:68, id:107, text: "Hier klicken für Ratschläge über Eure Königreichsbewertung" }
    { group:68, id:108, text: "Zeigt die Import-/Exportpreise aller Waren" }
    { group:68, id:109, text: "Hier klicken für Industriestatus" }
    { group:68, id:110, text: "Die Menge dieser Ware festlegen, die Ihr behalten möchtet, bevor etwas exportiert wird" }
    { group:68, id:111, text: "Produktion für diese Aktivität in der ganzen Stadt ein- oder ausschalten" }
    { group:68, id:112, text: "Den Handelsstatus dieses Artikels anpassen" }
    { group:68, id:113, text: "Dieses Diagramm auswählen" }
    { group:68, id:114, text: "Festivalinformationen" }
    { group:68, id:115, text: "Ein Festival zu Ehren dieses Gottes veranstalten" }
    { group:68, id:116, text: "Kein Festival organisieren" }
    { group:68, id:117, text: "Ein Festival für Osiris veranstalten" }
    { group:68, id:118, text: "Ein Festival für Ra veranstalten" }
    { group:68, id:119, text: "Ein Festival für Ptah veranstalten" }
    { group:68, id:120, text: "Ein Festival für Seth veranstalten" }
    { group:68, id:121, text: "Ein Festival für Bast veranstalten" }
    { group:68, id:122, text: "Stadtsteuersatz anpassen" }
    { group:68, id:123, text: "Hier klicken, um mit dieser Person zu sprechen" }
    { group:68, id:124, text: "Erweiterte Informationen über dieses Haus" }
    { group:68, id:125, text: "Durch gespeicherte Nachrichten scrollen" }
    { group:68, id:126, text: "Bereits gelesene Nachricht. @L Linksklick auf diese Nachricht, um sie zu lesen. @L Rechtsklick, um sie zu löschen" }
    { group:68, id:127, text: "Ungelesene Nachricht. @L Linksklick auf diese Nachricht, um sie zu lesen. @L Rechtsklick, um sie zu löschen" }
    { group:68, id:128, text: "Bringt Euch zurück zum vorherigen Hilfebildschirm" }
    { group:68, id:129, text: "Pharao-Hilfe verlassen" }
    { group:68, id:130, text: "Durch die Hilfe zu diesem Thema scrollen" }
    { group:68, id:131, text: "Diese Nachricht löschen" }
    { group:68, id:132, text: "Hier klicken, um zu dieser Problemstelle zu gehen" }
    { group:68, id:133, text: "Geschenk für Ägypten senden" }
    { group:68, id:134, text: "Hier klicken, um die Formation der Kompanie zu ändern" }
    { group:68, id:135, text: "Arbeitslosigkeit" }
    { group:68, id:136, text: "Kulturbewertung" }
    { group:68, id:137, text: "Wohlstandsbewertung" }
    { group:68, id:138, text: "Monumentbewertung" }
    { group:68, id:139, text: "Königreichsbewertung" }
    { group:68, id:140, text: "Hier klicken, um Transportbefehle zu erteilen" }
    { group:68, id:141, text: "Hier klicken, um Kriegsschiffbefehle zu erteilen" }
    { group:68, id:142, text: "Steuersatz" }
    { group:68, id:143, text: "Armeestatus anzeigen" }
    { group:68, id:144, text: "Marinestatus anzeigen" }
    { group:68, id:145, text: "Zur Königreichskarte gehen" }
    { group:68, id:146, text: "Missionskriterien festlegen" }
    { group:68, id:147, text: "Ebenes Land" }
    { group:68, id:148, text: "Bäume" }
    { group:68, id:149, text: "Wasser und Feuchtgebiete" }
    { group:68, id:150, text: "Wiese" }
    { group:68, id:151, text: "Straße" }
    { group:68, id:152, text: "Felsen und Dünen" }
    { group:68, id:153, text: "Flusspunkte" }
    { group:68, id:154, text: "Invasionspunkte" }
    { group:68, id:155, text: "Personenpunkte" }
    { group:68, id:156, text: "Tierpunkte" }
    { group:68, id:157, text: "Pinsel" }
    { group:68, id:158, text: "Stadt, Region oder Grafik hinzufügen" }
    { group:68, id:159, text: "Stadt, Region oder Grafik bearbeiten" }
    { group:68, id:160, text: "Stadt, Region oder Grafik löschen" }
    { group:68, id:161, text: "Hauptmenü anzeigen" }
    { group:68, id:162, text: "Handels- oder Invasionsroute hinzufügen" }
    { group:68, id:163, text: "Handels- oder Invasionsroute bearbeiten" }
    { group:68, id:164, text: "Auf Standardkarte zurücksetzen" }
    { group:68, id:165, text: "Zur Regionsansicht zurückkehren" }
    { group:68, id:166, text: "Preise für Importe und Exporte anpassen" }
    { group:68, id:167, text: "Rang, Finanzierung, Startdatum und aktuellen Pharao anpassen" }
    { group:68, id:168, text: "Durch Klimaoptionen wechseln" }
    { group:68, id:169, text: "Ereignisse planen" }
    { group:68, id:170, text: "Einen Feind auswählen" }
    { group:68, id:171, text: "Götter definieren" }
    { group:68, id:172, text: "Verfügbare Gebäude festlegen" }
    { group:68, id:173, text: "Bewertungsanforderungen festlegen und Monumente auswählen" }
    { group:68, id:174, text: "Länge und Qualität der Flut bestimmen" }
    { group:68, id:175, text: "Ansicht drehen" }
    { group:68, id:176, text: "Grafik ändern" }
    { group:68, id:177, text: "Killertypen" }
    { group:68, id:178, text: "Monument-Ära" }
    { group:69, id:0, text: "benötigt)" }
    { group:69, id:1, text: "Effizienz" }
    { group:69, id:2, text: "Keine Einsturzgefahr" }
    { group:69, id:3, text: "Sehr geringe Einsturzgefahr" }
    { group:69, id:4, text: "Geringe Einsturzgefahr" }
    { group:69, id:5, text: "Etwas Einsturzgefahr" }
    { group:69, id:6, text: "Hohe Einsturzgefahr" }
    { group:69, id:7, text: "Sehr hohe Einsturzgefahr" }
    { group:69, id:8, text: "Einsturz steht unmittelbar bevor" }
    { group:69, id:9, text: "Keine Brandgefahr" }
    { group:69, id:10, text: "Sehr geringe Brandgefahr" }
    { group:69, id:11, text: "Geringe Brandgefahr" }
    { group:69, id:12, text: "Etwas Brandgefahr" }
    { group:69, id:13, text: "Hohe Brandgefahr" }
    { group:69, id:14, text: "Sehr hohe Brandgefahr" }
    { group:69, id:15, text: "Extreme Brandgefahr" }
    { group:69, id:16, text: "Keine Menschen in der Stadt!" }
    { group:69, id:17, text: "Keine Arbeiter leben in der Nähe" }
    { group:69, id:18, text: "Der Arbeiteraufseher könnte etwas Arbeitskraft umverteilen" }
    { group:69, id:19, text: "Der Arbeiteraufseher könnte etwas Arbeitskraft umverteilen" }
    { group:69, id:20, text: "WARNUNG: Schlechter Zugang zu Arbeitern" }
    { group:69, id:21, text: "Arbeitet kaum. Unser Sektor braucht dringend mehr Arbeiter" }
    { group:69, id:22, text: "Arbeitet schlecht. Unser Sektor braucht viel mehr Arbeiter" }
    { group:69, id:23, text: "Arbeitet gut, aber unser Sektor könnte wirklich mehr Arbeiter gebrauchen" }
    { group:69, id:24, text: "Arbeitet mit reduzierter Kapazität. Kaum Arbeiter sind kürzlich eingetroffen" }
    { group:69, id:25, text: "WARNUNG: Dieses Gebäude grenzt nicht an eine Straße" }
    { group:69, id:26, text: "Unterbesetzt. Kann nur Waren versenden, wird keine Waren empfangen" }
    { group:69, id:27, text: "Nur Notbesetzung. Wird keine Waren versenden oder empfangen" }
    { group:70, id:0, text: "Keine Menschen in dieser Gegend." }
    { group:70, id:1, text: "frei" }
    { group:70, id:2, text: "frei" }
    { group:70, id:3, text: "frei" }
    { group:70, id:4, text: "frei" }
    { group:70, id:5, text: "frei" }
    { group:70, id:6, text: "frei" }
    { group:70, id:7, text: "frei" }
    { group:70, id:8, text: "frei" }
    { group:70, id:9, text: "frei" }
    { group:70, id:10, text: "Nichts" }
    { group:70, id:11, text: "Bäume und Waldland" }
    { group:70, id:12, text: "Felsen" }
    { group:70, id:13, text: "Wasser" }
    { group:70, id:14, text: "Bäume" }
    { group:70, id:15, text: "Risse im Land" }
    { group:70, id:16, text: "Straße" }
    { group:70, id:17, text: "Bewässerungsgraben" }
    { group:70, id:18, text: "Schutt von zerstörten Gebäuden" }
    { group:70, id:19, text: "Mauer" }
    { group:70, id:20, text: "Leeres Land" }
    { group:70, id:21, text: "Brücke" }
    { group:70, id:22, text: "Gärten" }
    { group:70, id:23, text: "Platz" }
    { group:70, id:24, text: "Zur Hauptstadt" }
    { group:70, id:25, text: "Zum Königreich" }
    { group:70, id:26, text: "Erzhaltiger Felsen" }
    { group:70, id:27, text: "Normaler Felsen" }
    { group:70, id:28, text: "Besonderer Felsen" }
    { group:70, id:29, text: "Überschwemmungsgebiet" }
    { group:70, id:30, text: "Überflutetes Überschwemmungsgebiet" }
    { group:70, id:31, text: "Marschland" }
    { group:70, id:32, text: "Sanddünen" }
    { group:70, id:33, text: "Ziegelmauer" }
    { group:70, id:34, text: "Mauer" }
    { group:70, id:35, text: "Wiese" }
    { group:70, id:36, text: "Klippen" }
    { group:70, id:37, text: "Bäume sind unpassierbar, können aber gerodet werden. Holzfäller sollten angemessen nahe an Bäumen sein. Waldland wächst mit der Zeit nach. (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament)." }
    { group:70, id:38, text: "Felsen sind unpassierbar und können nicht gerodet werden. Vielleicht habt Ihr das Glück, Kalkstein, Sandstein oder Granit für den Abbau zu haben, obwohl es gewöhnlicher Felsen ohne Wert sein könnte. Überprüft Eure Ressourcen, um es herauszufinden." }
    { group:70, id:39, text: "Nur Schiffe und Boote fahren auf Wasser, aber Fähren und Brücken können Menschen erlauben, an bestimmten Punkten zu überqueren. Docks können lebenswichtigen Handel mit dem Rest des Königreichs ermöglichen. Lehmgruben müssen an Wasser angrenzen." }
    { group:70, id:40, text: "Unpassierbares Gelände, das gerodet werden kann, um die Stadtexpansion zu ermöglichen. Holzfäller müssen in der Nähe von Bäumen sein, um Holz zu ernten. (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament)." }
    { group:70, id:41, text: "Diese Schluchten wurden durch Erdbeben verursacht. Sie können nicht passiert oder ausgefüllt werden, und Menschen bevorzugen es, nicht neben ihnen zu leben." }
    { group:70, id:42, text: "Menschen verlassen ihre Gebäude nur auf Straßen und können nur zwischen Überschwemmungsgebieten und trockenem Land dort überqueren, wo Straßen die Passage erlauben. (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament)." }
    { group:70, id:43, text: "Bewässerungsgräben verbessern die Fruchtbarkeit aller Farmen innerhalb von zwei Feldern." }
    { group:70, id:44, text: "Diese zerbröckelten Überreste alter Gebäude senken die Attraktivität des Landes in ihrer Umgebung." }
    { group:70, id:45, text: "Mauern schützen hilflose Bürger vor Plünderern und Invasoren. Sie können nur eine bestimmte Menge an Schlägen aushalten, und dickere Mauern halten länger." }
    { group:70, id:46, text: "Offenes Land ist erstklassiges Baugelände. Migranten, Soldaten und einige Ressourcensammler können darauf gehen. (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament). " }
    { group:70, id:47, text: "Diese Brücke erschließt neues Land für unsere Stadt, ermöglicht aber auch Raubtieren oder Invasoren, das Wasser zu überqueren!" }
    { group:70, id:48, text: "Gärten verbessern die lokale Umgebung." }
    { group:70, id:49, text: "Menschen bevorzugen Plätze!" }
    { group:70, id:50, text: "Diese Straße verbindet uns mit dem Rest Ägyptens und muss offen gehalten werden, damit Einwanderer und Händler in unserer Stadt ankommen können. " }
    { group:70, id:51, text: "Dies ist die Straße zu den weiteren Regionen des Königreichs. Es ist eine königliche Straße und als solche muss die Durchgangsfreiheit darauf aufrechterhalten werden." }
    { group:70, id:52, text: "Dies ist erzhaltiger Felsen. Ihr könnt hier entweder Gold oder Kupfer abbauen, je nachdem, welches Metall vorhanden ist.  " }
    { group:70, id:53, text: "Dies ist normaler Felsen. Abhängig von den Ressourcen Eurer Stadt könntet Ihr hier Baustein oder sogar Edelsteine abbauen. " }
    { group:70, id:54, text: "Dies ist besonderer Felsen. (dieser Text sollte nirgendwo erscheinen) " }
    { group:70, id:55, text: "Dieses Gebiet bietet höchst fruchtbares Land, jetzt da der Fluss zurückgewichen ist." }
    { group:70, id:56, text: "Dieses Gebiet wird höchst fruchtbares Land bieten, sobald der Fluss zurückweicht." }
    { group:70, id:57, text: "Sumpfige Gebiete sind zu matschig, um Gebäude zu tragen, können aber von vorsichtigen Bürgern durchquert werden. Schilf wächst hier, aber hütet Euch vor Krokodilen! (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament)." }
    { group:70, id:58, text: "Der wandernde Sand hier kann keine Gebäude tragen, aber Migranten, Soldaten und andere können darauf gehen. (Um ein Gebäude auszuwählen, rechtsklickt auf sein Fundament). " }
    { group:70, id:59, text: "Dies ist eine Ziegelmauer. Sie hält Invasoren länger auf als eine Lehmmauer, ist aber kein Ersatz für eine Kompanie ausgebildeter Soldaten!" }
    { group:70, id:60, text: "Dies ist eine einfache Lehmmauer. Sie wird Invasoren für kurze Zeit aufhalten, aber Ihr solltet sie nicht als starke Verteidigung betrachten." }
    { group:70, id:61, text: "Dieses Land erlaubt allen Arten von Pflanzen zu wachsen. Je üppiger die Blumen hier wachsen, desto fruchtbarer ist es." }
    { group:70, id:62, text: "Diese massiven Klippen sind ideale Orte, um bestimmte Monumente zu bauen. Menschen können dieses steile Gelände nicht überschreiten, noch kann etwas daraus abgebaut werden." }
    { group:71, id:0, text: "Musikpavillon" }
    { group:71, id:1, text: "Menschen kommen hierher, um die neuesten Gaukeltricks zu sehen und Musik zu hören." }
    { group:71, id:2, text: "Dieser Platz hat nie Vorstellungen. Er braucht Gaukler und Musiker, um ihn zu beleben." }
    { group:71, id:3, text: "Dieser Platz bietet seiner Gemeinschaft sowohl aufregendes Gaukeln als auch Musik von örtlichen Musikern." }
    { group:71, id:4, text: "Dieser Platz bietet Musik zur Unterhaltung der örtlichen Gemeinschaft. Er sucht Gaukler, um ein paar Vorstellungen zu veranstalten." }
    { group:71, id:5, text: "Dieser Platz zeigt Gaukeleien. Er könnte das Publikum besser erfreuen, wenn er Musiker hätte, die spielen." }
    { group:71, id:6, text: "Dieser Platz ist tot. Ohne Angestellte bietet er keine Freizeitdienste für die örtliche Gemeinschaft." }
    { group:71, id:7, text: "Keine aktuellen Musikvorstellungen" }
    { group:71, id:8, text: "Die Musiker werden spielen für weitere" }
    { group:71, id:9, text: "Keine aktuellen Gaukelvorstellungen" }
    { group:71, id:10, text: "Aktuelle Gaukler werden erstaunen für weitere" }
    { group:72, id:0, text: "Bude" }
    { group:72, id:1, text: "Bürger genießen geschickte Gaukelvorstellungen und allgemeinen Unsinn hier." }
    { group:72, id:2, text: "Dieser Platz hat nie Vorstellungen. Er braucht echte Gaukler, um Unterhaltung zu bieten." }
    { group:72, id:3, text: "Dieser Platz zeigt derzeit Vorstellungen von örtlichen Gauklern, die normalerweise ein gutes Publikum anziehen." }
    { group:72, id:4, text: "Brisen sind das Einzige, was sich auf diesem Platz regt. Ohne Arbeiter bietet er keine Vorstellungen für die Einheimischen." }
    { group:72, id:5, text: "Keine aktuellen Gaukelvorstellungen" }
    { group:72, id:6, text: "Aktuelle Vorstellung läuft für weitere" }
    { group:72, id:7, text: "Zeigt: 'Gaukeln vom Großen Mephisto' von Mephisto" }
    { group:72, id:8, text: "Zeigt: 'Die Sande der Zeit' von Eisenstabhotep" }
    { group:72, id:9, text: "Zeigt: 'Weine mir einen Fluss' von Waseth" }
    { group:72, id:10, text: "Zeigt: 'Die 10.000 Deben Pyramide' von Desenseth" }
    { group:72, id:11, text: "Zeigt: El-Tonjons 'Krokodilsfelsen'" }
    { group:73, id:0, text: "Senet-Haus" }
    { group:73, id:1, text: "Spiele von Geschick und Glück können das Schicksal der Spieler machen oder zerstören." }
    { group:73, id:2, text: "Dieses Senet-Haus hat Spieler, aber eine zuverlässige Bierversorgung würde die Spiele beleben." }
    { group:73, id:3, text: "Dieses Senet-Haus hat ständige Spiele, sehr zur Freude der örtlichen Bevölkerung." }
    { group:73, id:4, text: "Niemand besucht dieses Senet-Haus. Ohne Arbeiter zieht die örtliche Gemeinschaft keine Unterhaltung daraus." }
    { group:73, id:5, text: "Keine Spiele im Gange" }
    { group:73, id:6, text: "Aktuelle Spiele werden dauern" }
    { group:73, id:7, text: "Gelagertes Bier," }
    { group:74, id:0, text: "Pavillon" }
    { group:74, id:1, text: "Tanzen, Musik und Gaukeln...was könnte ein Bürger mehr wünschen?" }
    { group:74, id:2, text: "Dieser Platz hat keine Vorstellungen. Er braucht Tänzer, Musiker und Gaukler, um Menschenmengen anzuziehen." }
    { group:74, id:3, text: "Dieser Platz ist in ständiger Bewegung mit Tanzen, Musik und Gaukeln, die die örtliche Gemeinschaft sehr erfreuen." }
    { group:74, id:4, text: "Dieser Platz hat Tänzer und Musiker für die Einheimischen, aber einige Gaukler wären höchst willkommen." }
    { group:74, id:5, text: "Dieser Platz hat Tänzer und Gaukler. Er braucht Musiker, um vollständige Unterhaltung zu bieten." }
    { group:74, id:6, text: "Dieser Platz hat Musiker und Gaukler, aber die Musik schreit nach Tänzern, um die Vorstellung zu vervollständigen." }
    { group:74, id:7, text: "Dieser Platz hat Gaukelvorstellungen, aber er braucht Musiker und Tänzer, um die sonst leeren Bühnen zu füllen." }
    { group:74, id:8, text: "Dieser Platz hat Musiker, aber keine Gaukler oder Tänzer." }
    { group:74, id:9, text: "Dieser Platz hat Tänzer, die etwas Musik sehr willkommen heißen würden. Gaukeln wäre auch schön." }
    { group:74, id:10, text: "Dieser Platz ist geschlossen. Ohne Angestellte, die ihn betreiben, ist er als Freizeiteinrichtung nutzlos." }
    { group:74, id:11, text: "Keine aktuellen Gaukelvorstellungen" }
    { group:74, id:12, text: "Gaukeln wird fortgesetzt für weitere" }
    { group:74, id:13, text: "Keine aktuellen Musicals" }
    { group:74, id:14, text: "Musikvorstellungen laufen für weitere" }
    { group:74, id:15, text: "Kein aktuelles Tanzen" }
    { group:74, id:16, text: "Tanzvorstellungen laufen für weitere" }
    { group:75, id:0, text: "Konservatorium" }
    { group:75, id:1, text: "Ägyptische Menschen sind immer begierig, die neuesten Darbietungen von neuen Musikern zu hören." }
    { group:75, id:2, text: "Wir freuen uns bekannt zu geben, dass wir bei voller Besetzung bis zu vier neue Musiker jeden Monat ausbilden." }
    { group:75, id:3, text: "Wir sind leicht unterbesetzt und können daher höchstens zwei neue Musiker jeden Monat ausbilden." }
    { group:75, id:4, text: "Wir sind halb besetzt und können daher nur einen Musiker im kommenden Monat ausbilden." }
    { group:75, id:5, text: "Wir haben so wenige Angestellte, dass wir Schwierigkeiten haben werden, einen neuen Musiker über die nächsten zwei Monate hervorzubringen." }
    { group:75, id:6, text: "Ich habe keine Mitarbeiter außer mir selbst. Man kann nicht erwarten, dass ich unter diesen Bedingungen arbeite! Bestenfalls kann ich einen Musiker in drei Monaten ausbilden." }
    { group:75, id:7, text: "Ohne Ausbildungspersonal kann diese Schule keine neuen Musiker ausbilden." }
    { group:76, id:0, text: "Tanzschule" }
    { group:76, id:1, text: "Tänzer erfreuen das Publikum mit anmutigen und verlockenden neuen Bewegungen." }
    { group:76, id:2, text: "Wir freuen uns bekannt zu geben, dass wir bei voller Besetzung bis zu vier neue Tänzer jeden Monat bereitstellen können." }
    { group:76, id:3, text: "Wir sind leicht unterbesetzt und können daher höchstens zwei neue Tänzer jeden Monat ausbilden." }
    { group:76, id:4, text: "Wir sind halb besetzt, daher können wir nur einen Tänzer im kommenden Monat ausbilden." }
    { group:76, id:5, text: "Wir brauchen so dringend Ausbilder, dass wir kaum einen neuen Tänzer über die nächsten zwei Monate bewältigen können." }
    { group:76, id:6, text: "Ich habe keine Mitarbeiter außer mir selbst. Man kann nicht erwarten, dass ich unter diesen Bedingungen arbeite! Bestenfalls kann ich einen Tänzer in drei Monaten unterrichten." }
    { group:76, id:7, text: "Ohne Ausbilder kann diese Tanzschule keine neuen Tänzer unterrichten." }
    { group:77, id:0, text: "Gauklerschule" }
    { group:77, id:1, text: "Neue Gaukler mit erfinderischen neuen Routinen sind immer gefragt." }
    { group:77, id:2, text: "Wir freuen uns bekannt zu geben, dass wir bei voller Besetzung bis zu vier neue Gaukler jeden Monat ausbilden." }
    { group:77, id:3, text: "Wir sind leicht unterbesetzt und können daher höchstens zwei neue Gaukler jeden Monat hervorbringen." }
    { group:77, id:4, text: "Wir sind halb besetzt und können daher nur einen Gaukler im kommenden Monat ausbilden." }
    { group:77, id:5, text: "Wir brauchen dringend Angestellte. Es wird schwierig sein, einen neuen Gaukler über die nächsten zwei Monate hervorzubringen." }
    { group:77, id:6, text: "Ich habe keine Mitarbeiter außer mir selbst. Man kann nicht erwarten, dass ich unter diesen Bedingungen arbeite! Bestenfalls kann ich einen Gaukler in drei Monaten ausbilden." }
    { group:77, id:7, text: "Diese Schule ist verlassen. Ohne Mentoren in ihrer Beschäftigung werden keine neuen Gaukler produziert." }
    { group:78, id:0, text: "Senet-Ausbilder? War Stierkampf-Trainer" }
    { group:78, id:1, text: "Die Meisterstrategen, die hier arbeiten, bilden erfahrene Senet-Meister aus, um die immer beliebten Senet-Häuser der Stadt zu leiten." }
    { group:78, id:2, text: "Wir freuen uns bekannt zu geben, dass wir bei voller Besetzung bis zu vier Senet-Meister jeden Monat bereitstellen können." }
    { group:78, id:3, text: "Wir sind leicht unterbesetzt und können daher höchstens zwei neue Senet-Meister jeden Monat bereitstellen." }
    { group:78, id:4, text: "Wir sind halb besetzt und können daher nur einen Senet-Meister im kommenden Monat ausbilden." }
    { group:78, id:5, text: "Wir brauchen dringend Angestellte und werden Schwierigkeiten haben, einen neuen Senet-Meister über die nächsten zwei Monate hervorzubringen." }
    { group:78, id:6, text: "Ich habe keine Mitarbeiter außer mir selbst. Man kann nicht erwarten, dass ich unter diesen Bedingungen arbeite! Bestenfalls kann ich einen Senet-Meister in drei Monaten verfeinern." }
    { group:78, id:7, text: "Ohne Lehrer werden keine neuen Senet-Meister ausgebildet. Senet-Häuser in der ganzen Stadt könnten als Folge leiden." }
    { group:79, id:0, text: "Gärten" }
    { group:79, id:1, text: "Dieses angenehme Grundstück verschafft Bürgern Erleichterung von Lärm, Hitze und Schmutz der Stadt mit einer kühlen Oase grünen Raums. Jeder möchte einen Garten nebenan." }
    { group:80, id:0, text: "Statue" }
    { group:80, id:1, text: "Monumente für Götter und vergangene Pharaonen erhöhen das Prestige einer Nachbarschaft. Menschen sind stolz, Statuen in der Nähe zu haben...und je größer, desto besser." }
    { group:80, id:2, text: "Triumphbogen" }
    { group:80, id:3, text: "Dieses prachtvolle Bauwerk gedenkt historischer Siege über Ägyptens Feinde. Nichts könnte prestigeträchtiger sein." }
    { group:81, id:0, text: "Apotheke" }
    { group:81, id:1, text: "Apotheken verbessern die Gesundheit der Bürger, wenn sie Hausbesuche in den Nachbarschaften auf ihrer Route machen. Wohlhabende Gebiete wollen eine Apotheke in der Nähe." }
    { group:81, id:2, text: "Diese Apotheke ist nicht funktionsfähig und tut nichts für die Gesundheit der örtlichen Gemeinschaft." }
    { group:81, id:3, text: "Diese Apotheke ist funktionsfähig und versorgt die örtliche Gemeinschaft mit Tränken und Salben." }
    { group:82, id:0, text: "Leichenhalle" }
    { group:82, id:1, text: "Obwohl niemand in der Nähe wohnen möchte, retten Leichenhallen Leben, wenn Krankheit zuschlägt. Die Stadt sollte die Kapazität haben, alle ihre Toten einzubalsamieren." }
    { group:82, id:2, text: "Diese Leichenhalle ist nicht funktionsfähig und kann die Körper verstorbener Bewohner nicht für das Jenseits vorbereiten." }
    { group:82, id:3, text: "Diese Leichenhalle ist funktionsfähig und mumifiziert verstorbene Nachbarn schnell und professionell." }
    { group:82, id:4, text: "Ohne Leinen können wir die Toten nicht auf ihre Reise durch die Ewigkeit vorbereiten." }
    { group:83, id:0, text: "Arzt" }
    { group:83, id:1, text: "Ein Granatapfel am Tag hält den Arzt fern, so heißt es. Ärzte verbessern die Gesundheit, während sie ihre Runden machen." }
    { group:83, id:2, text: "Diese Arztpraxis ist nicht funktionsfähig und tut nichts für die Gesundheit der Gemeinschaft." }
    { group:83, id:3, text: "Diese Arztpraxis ist funktionsfähig, und die örtliche Gemeinschaft ist gesund und fit." }
    { group:84, id:0, text: "Zahnarzt" }
    { group:84, id:1, text: "Sand gelangt überall hin, auch ins Essen. Ständiger Abrieb sorgt für viel Arbeit für ägyptische Zahnärzte." }
    { group:84, id:2, text: "Diese Zahnarztpraxis ist nicht funktionsfähig, und die Zähne der Nachbarn zeigen den Mangel an Pflege." }
    { group:84, id:3, text: "Diese Zahnarztpraxis ist funktionsfähig, und die Zähne der örtlichen Gemeinschaft glänzen vor Stolz." }
    { group:85, id:0, text: "Schreibschule" }
    { group:85, id:1, text: "Kinder der Wohlhabenden müssen Schulen in der Nachbarschaft besuchen, um Lesen und Schreiben zu lernen, wenn sie den Status ihrer Eltern erreichen wollen." }
    { group:85, id:2, text: "Diese Schule kann derzeit niemanden unterrichten. Es fehlt an Angestellten, Papyrus oder beidem." }
    { group:85, id:3, text: "Diese Schule ermöglicht es Kindern, einem Leben körperlicher Plackerei zu entkommen, solange sie sowohl Angestellte als auch Papyrus hat." }
    { group:86, id:0, text: "Links" }
    { group:86, id:1, text: "Oben" }
    { group:86, id:2, text: "Rechts" }
    { group:86, id:3, text: "Unten" }
    { group:87, id:0, text: "Bibliothek" }
    { group:87, id:1, text: "Literarische Werke aller Art werden hier produziert und gelagert. Schreiber bestehen darauf, dass Bibliotheken für eine wichtige Stadt entscheidend sind." }
    { group:87, id:2, text: "Diese Bibliothek fehlt es an Angestellten, Papyrus oder beidem. Sie kann der Gemeinschaft nicht dienen." }
    { group:87, id:3, text: "Solange diese Bibliothek Angestellte und Papyrus hat, kann sie der Gemeinschaft dienen." }
    { group:88, id:0, text: "Polizeistation" }
    { group:88, id:1, text: "Polizeistationen schicken Konstable in die Stadt, um den Frieden zu wahren. Öffentliche Ordnung ist gesichert, wenn Konstable die Stadt gleichmäßig patrouillieren." }
    { group:88, id:2, text: "Unser Konstable ist auf Patrouille." }
    { group:88, id:3, text: "Unser Konstable bereitet sich auf seinen Dienst vor." }
    { group:88, id:4, text: "Derzeit ist unser Dienstplan voll. Unsere Konstable sind immer wachsam gegenüber Anzeichen von Verbrechen." }
    { group:88, id:5, text: "Wir haben einen kleinen Mangel an Konstablen. Wir haben Lücken von vielleicht ein oder zwei Tagen in unserer Abdeckung." }
    { group:88, id:6, text: "Wir sind unterbesetzt. Kriminelle werden durch Lücken von bis zu einer Woche in unserem Dienstplan ermutigt." }
    { group:88, id:7, text: "Wir haben viel zu wenige Leute. Kriminelle könnten bis zu zwei Wochen am Stück ungehindert operieren." }
    { group:88, id:8, text: "Wir arbeiten nur mit Schreibtischpersonal. Wir gehen häufig einen vollen Monat, ohne einen Konstable auf die Straßen zu schicken." }
    { group:88, id:9, text: "Ohne Personal ist diese Station kaum mehr als ein Ziel für Vandalen." }
    { group:88, id:10, text: " Diebstähle dieses Jahr." }
    { group:88, id:11, text: " Gold gestohlen dieses Jahr." }
    { group:89, id:0, text: "Fort" }
    { group:89, id:1, text: "Dieses Fort ist von Seth verflucht, und es wird noch einige Zeit dauern, bis sich Soldaten wieder hierher wagen." }
    { group:89, id:2, text: "Forts ziehen Soldaten vom Rekrutierer der Stadt. Eine Militärakademie würde besser ausgebildete Truppen bereitstellen." }
    { group:90, id:0, text: "Torhaus" }
    { group:90, id:1, text: "Mauern brauchen ein Torhaus, damit Migranten und Händler frei kommen und gehen können." }
    { group:91, id:0, text: "Turm" }
    { group:91, id:1, text: "Baut Türme in regelmäßigen Abständen in Mauern oder zumindest in verwundbaren Bereichen. Wenn sie mit Straßen verbunden sind, erhalten Türme Wachen vom Rekrutierer der Stadt. Turmwachen lassen Speere auf nahegelegene Invasoren regnen und patrouillieren dicke genug Mauern." }
    { group:91, id:2, text: "Ohne Arbeiter können wir keine Turmwachen stationieren oder jemanden einstellen, um die Mauern zu patrouillieren." }
    { group:91, id:3, text: "Unsere Männer sind auf voller Stärke, wachsam und bereit, jede Bedrohung abzuwehren." }
    { group:91, id:4, text: "Wir haben Wartungspersonal, aber wir brauchen Wachen von einem Rekrutierer, um die Stadt zu verteidigen." }
    { group:92, id:0, text: "Tempel des Osiris (Landwirtschaft)" }
    { group:92, id:1, text: "Osiris bringt Fruchtbarkeit ins Land und lässt die Pflanzen wachsen. Besänftigt ihn, oder bereitet Euch darauf vor, hungrig zu bleiben." }
    { group:93, id:0, text: "Tempel des Ra (Das Königreich)" }
    { group:93, id:1, text: "Händler kennen den Wert darin, Ra zu gefallen. Handel ist sicherer und profitabler mit Ras Segen, und das Ansehen Eurer Stadt ist größer." }
    { group:94, id:0, text: "Tempel des Ptah (Handwerker)" }
    { group:94, id:1, text: "Arbeiter und Handwerker verehren Ptah, um ihre Plackerei zu erleichtern. Wenn Ptah verärgert ist, ist keine Industrie vor Katastrophen sicher." }
    { group:95, id:0, text: "Tempel des Seth (Zerstörung)" }
    { group:95, id:1, text: "Seth wacht über Soldaten und ermutigt Tapferkeit im Kampf. Kein Mann wagt es, ohne den Segen von Seth zu kämpfen." }
    { group:96, id:0, text: "Tempel der Bast (Heim)" }
    { group:96, id:1, text: "Wenn Bast missfällt, ist niemandes Heim sicher. Einige geben Bast auch die Schuld für Krankheiten." }
    { group:97, id:0, text: "Basar" }
    { group:97, id:1, text: "Unsere Basare machen die Fülle des Königreichs für jeden nahegelegenen Bürger verfügbar. Jedes Heim braucht Basarzugang, obwohl niemand nebenan wohnen möchte." }
    { group:97, id:2, text: "Dieser Basar ist nicht funktionsfähig und liefert nichts an die örtliche Gemeinschaft." }
    { group:97, id:3, text: "Dieser Basar ist funktionsfähig und versorgt die Bedürfnisse der örtlichen Heime." }
    { group:97, id:4, text: "Dieser Basar hat Händler, aber sie suchen derzeit nach Nahrung oder Waren zum Verkaufen." }
    { group:97, id:5, text: "Nahrungsvorräte für" }
    { group:97, id:6, text: "Spezialbestellungen" }
    { group:97, id:7, text: "Basaranweisungen" }
    { group:97, id:8, text: "Kaufen" }
    { group:97, id:9, text: "Nicht kaufen" }
    { group:97, id:10, text: "Der Basarhändler ist hier und wartet auf Nahrung." }
    { group:97, id:11, text: "Der Basarhändler ist unterwegs und verteilt Waren." }
    { group:97, id:12, text: "Der Basarhändler kehrt zurück, um aufzustocken." }
    { group:98, id:0, text: "Getreidespeicher" }
    { group:98, id:1, text: "Volle Getreidespeicher sind lebenswichtig, um die Bäuche der Menschen zu füllen, und helfen, neue Bürger anzuziehen. Ein Getreidespeicher kann jede Art von Nahrung lagern." }
    { group:98, id:2, text: "Lagert" }
    { group:98, id:3, text: "Platz für" }
    { group:98, id:4, text: "Dieser Getreidespeicher wird nicht benötigt. Ägypten versorgt unsere Stadt mit allem Getreide, das sie braucht. Jede Nahrung, die wir produzieren, geht direkt in alle Lagerhöfe mit leerem Platz." }
    { group:98, id:5, text: "Spezialbestellungen" }
    { group:98, id:6, text: "Getreidespeicheranweisungen" }
    { group:98, id:7, text: "Getreidespeicher leeren" }
    { group:98, id:8, text: "Leeren des Getreidespeichers stoppen" }
    { group:98, id:9, text: "Versucht, Nahrung anderswohin zu senden" }
    { group:99, id:0, text: "Lagerhof" }
    { group:99, id:1, text: "Alle Arten von Waren brauchen Lagerung. Karawanen handeln an Lagerhöfen, Docks tauschen Exporte gegen Importe an nahegelegenen Höfen aus, und Basare lagern hier auch auf." }
    { group:99, id:2, text: "Spezialbestellungen" }
    { group:99, id:3, text: "Lagerhofanweisungen" }
    { group:99, id:4, text: "Lagerhof leeren STARTEN" }
    { group:99, id:5, text: "Lagerhof leeren STOPPEN" }
    { group:99, id:6, text: "Versucht, Waren anderswohin zu senden" }
    { group:99, id:7, text: "Keine akzeptieren" }
    { group:99, id:8, text: "Nicht akzeptieren" }
    { group:99, id:9, text: "Holt Waren" }
    { group:99, id:10, text: "Holt Nahrung" }
    { group:99, id:11, text: "Handelszentrum" }
    { group:99, id:12, text: "Zum Handelszentrum werden" }
    { group:99, id:13, text: "WARNUNG: Dieser Lagerhof ist vollständig voll. Er kann keine weiteren Waren akzeptieren." }
    { group:99, id:14, text: "WARNUNG: Dieser Lagerhof wird voll. Er kann nur Waren bereits vorhandener Typen akzeptieren. Keine neuen Warenarten werden überhaupt eingecheckt." }
    { group:99, id:15, text: "Unser Lieferant ist bereit für neue Aufträge." }
    { group:99, id:16, text: "Unser Lieferant bringt Waren woanders hin." }
    { group:99, id:17, text: "Unser Lieferant ist auf dem Rückweg." }
    { group:99, id:18, text: "Akzeptieren" }
    { group:99, id:19, text: "Holen" }
    { group:99, id:20, text: "Nahrung leeren" }
    { group:99, id:21, text: "Leeren " }
    { group:99, id:22, text: "Dieser Lagerhof ist leer." }
    { group:99, id:23, text: "Block von" }
    { group:99, id:24, text: "Blöcke von " }
    { group:99, id:25, text: "bis zu 1/4 von" }
    { group:99, id:26, text: "bis zu 1/2 von" }
    { group:99, id:27, text: "bis zu 3/4 von" }
    { group:99, id:28, text: "alles" }
    { group:99, id:29, text: "Hof" }
    { group:99, id:30, text: "Getreidespeicher" }
    { group:99, id:31, text: "Maximum " }
    { group:99, id:32, text: "Füllen" }
    { group:99, id:33, text: "Unser Lieferant ist unterwegs, um Waren zu holen" }
    { group:100, id:0, text: "Schiffsbauer" }
    { group:100, id:1, text: "Mit genügend Arbeitern baut der Schiffsbauer Militärschiffe und Fischerboote für die Werften der Stadt. Holz wird benötigt, um Kriegsschiffe und Transportschiffe zu bauen; keine Rohstoffe werden benötigt, um Fischerboote zu bauen." }
    { group:100, id:2, text: "Produktion ist" }
    { group:100, id:3, text: "abgeschlossen." }
    { group:100, id:4, text: "Es gibt derzeit keine Werften, die eines unserer Schiffe verlangen." }
    { group:100, id:5, text: "Wir bauen ein Militärschiff oder Fischerboot auf Bestellung für eine Werft in der Stadt." }
    { group:100, id:6, text: "Wir reparieren ein Militärschiff." }
    { group:100, id:7, text: "Gelagertes Holz," }
    { group:100, id:8, text: "Wir brauchen Holz, um Militärschiffe zu reparieren und zu bauen." }
    { group:100, id:9, text: "Eine Kriegsschiff- oder Transportwerft hat uns beauftragt, ein Schiff zu bauen, aber uns fehlt das nötige Holz." }
    { group:100, id:10, text: "Wir haben Schiffe in der Warteschlange zur Reparatur, aber kein Holz, um sie zu reparieren." }
    { group:101, id:0, text: "Dock" }
    { group:101, id:1, text: "Handelsschiffe aus der ganzen Welt legen hier an, um Importe zu liefern und Exporte abzuholen. Ihr könnt ohne Docks keinen Seehandel betreiben." }
    { group:101, id:2, text: "Ohne Hafenarbeiter können wir das angedockte Schiff nicht bedienen." }
    { group:101, id:3, text: "Wir bedienen das angedockte Schiff. Mit so wenigen Hafenarbeitern könnte dies jedoch sehr lange dauern." }
    { group:101, id:4, text: "Wir bedienen das angedockte Schiff, obwohl dies etwas länger dauern wird, als wenn wir voll besetzt wären." }
    { group:101, id:5, text: "Mit voller Besetzung können wir das angedockte Schiff schnell und effizient bedienen." }
    { group:101, id:6, text: "Jedes Schiff, das hier anlegt, wird keine Arbeiter finden, um seine Fracht zu laden oder zu entladen." }
    { group:101, id:7, text: "Die wenigen hier beschäftigten Hafenarbeiter würden lange brauchen, um Schiffe zu be- und entladen, die im Hafen ankommen." }
    { group:101, id:8, text: "Wir sind unterbesetzt, daher wird es etwas länger als normal dauern, Schiffe zu be- und entladen, die im Hafen ankommen." }
    { group:101, id:9, text: "Mit voller Besetzung warten unsere Hafenarbeiter nur darauf, dass ihr Schiff einläuft." }
    { group:102, id:0, text: "Fischereiwerft" }
    { group:102, id:1, text: "Boote fahren vom Schiffsbauer hierher, um Besatzungen aufzunehmen und mit dem Fischen in örtlichen Gewässern zu beginnen. Jede Werft kann ein Fischerboot bedienen." }
    { group:102, id:2, text: "Wir warten derzeit darauf, dass ein Schiffsbauer uns ein Fischerboot baut." }
    { group:102, id:3, text: "Unser Fischerboot fährt zu den Fischgründen hinaus." }
    { group:102, id:4, text: "Unser Boot ist jetzt bei den Fischgründen und holt Fische ein." }
    { group:102, id:5, text: "Unser Boot fährt jetzt zur Werft." }
    { group:102, id:6, text: "Wir bestücken unser Fischerboot für eine weitere ausgehende Fahrt." }
    { group:102, id:7, text: "Unser Fischerboot fährt von den Fischgründen mit seinem Fang zurück." }
    { group:102, id:8, text: "Unsere Fischer hoffen, dass eines Tages jemand Fischgründe in diesem Gebiet entdeckt. Sie können mit den erschöpften Gewässern nicht viel verdienen." }
    { group:102, id:9, text: "Euer Handelsaufseher befahl einen Stopp des Fischens." }
    { group:102, id:10, text: "Unser Fischerboot fährt nicht in dieses verschmutzte Wasser hinaus!" }
    { group:103, id:0, text: "Villa" }
    { group:103, id:1, text: "Euer Heim ist eine der begehrtesten Adressen der Stadt. Eure Villa gibt Euch die Autorität, ein Gehalt zu beziehen. " }
    { group:103, id:2, text: "Deben pro Monat" }
    { group:103, id:3, text: "Gehalt des Dorfältesten von" }
    { group:103, id:4, text: "Gehalt des Dorfadligen von" }
    { group:103, id:5, text: "Gehalt des Königlichen Gelehrten von" }
    { group:103, id:6, text: "Gehalt des Königlichen Schreibers von" }
    { group:103, id:7, text: "Gehalt des Königlichen Richters von" }
    { group:103, id:8, text: "Gehalt des Königlichen Bürgermeisters von" }
    { group:103, id:9, text: "Gehalt des Königlichen Gouverneurs von" }
    { group:103, id:10, text: "Gehalt des Nomarchen von" }
    { group:103, id:11, text: "Gehalt des Kanzlers von" }
    { group:103, id:12, text: "Gehalt des Wesirs von" }
    { group:103, id:13, text: "Gehalt des Pharaos von" }
    { group:104, id:0, text: "Architektenposten" }
    { group:104, id:1, text: "Ägyptische Architekten sind die fortschrittlichsten, die die Welt je gekannt hat. Ihre Wachsamkeit verhindert, dass Gebäude einstürzen." }
    { group:104, id:2, text: "Unser Architekt ist fleißig bei der Arbeit." }
    { group:104, id:3, text: "Unser Architekt bereitet sich auf die Abreise vor." }
    { group:104, id:4, text: "Derzeit haben wir keine Ausfallzeit. Unsere Architekten sind ständig unterwegs, um die größeren Gebäude der Stadt zu inspizieren und zu reparieren." }
    { group:104, id:5, text: "Wir haben ein oder zwei Tage, bevor unsere überarbeiteten Architekten wieder auf den Straßen sind." }
    { group:104, id:6, text: "Wir sind unterbesetzt, daher haben wir eine Woche Wartezeit, bevor unsere zurückkehrenden Architekten wieder im Dienst sind." }
    { group:104, id:7, text: "Wir sind stark unterbesetzt und haben zwei Wochen Lücke zwischen den Runden jedes Architekten." }
    { group:104, id:8, text: "Wir arbeiten mit Notbesetzung. Wir können kaum einen Architekten pro Monat ins Feld schicken." }
    { group:104, id:9, text: "Ohne Architekten ist die Nachbarschaft dem wandernden Sand ausgeliefert." }
    { group:105, id:0, text: "Palast" }
    { group:105, id:1, text: "Der Palast gehört zu den begehrtesten Gebäuden Eurer Stadt und ist der Eckpfeiler der Stadtwirtschaft. Er verwandelt Goldklumpen in Deben und lagert einige der Stadtmittel." }
    { group:105, id:2, text: "Tresore enthalten" }
    { group:105, id:3, text: "Euren Bewertungsaufseher besuchen?" }
    { group:106, id:0, text: "Steuereintreiberbüro" }
    { group:106, id:1, text: "Obwohl nicht die beliebtesten Arbeiter in der Stadt, ermöglichen Steuereintreiber unser großes Königreich und all die Vorteile, die uns zufließen." }
    { group:106, id:2, text: "Tresore enthalten" }
    { group:106, id:3, text: "Unser Eintreiber prüft die Konten der Einheimischen." }
    { group:106, id:4, text: "Unser Eintreiber bereitet sich auf die Abreise vor." }
    { group:106, id:5, text: "Derzeit arbeiten wir mit vollständiger Effizienz, unsere Eintreiber stellen sicher, dass alle fälligen Steuern auf ihren Routen bezahlt werden." }
    { group:106, id:6, text: "Wir haben ein oder zwei Tage Leerlaufzeit, bevor zurückkehrende Eintreiber wieder auf die Straßen gehen." }
    { group:106, id:7, text: "Wir sind unterbesetzt und haben eine Woche Wartezeit, bevor Eintreiber wieder im Dienst sind." }
    { group:106, id:8, text: "Wir sind stark unterbesetzt und haben zwei Wochen zwischen Eintreibungspatrouillen." }
    { group:106, id:9, text: "Mit so wenigen Menschen in diesem Büro können die örtlichen Bürger einen Großteil ihrer Steuerrechnungen umgehen." }
    { group:106, id:10, text: "Ohne Eintreibungspersonal trägt dieses Büro nichts zur Stadtkasse bei." }
    { group:106, id:11, text: "Eure Stadt braucht einen Palast, bevor Ihr Steuern eintreiben könnt." }
    { group:106, id:12, text: "Eure Stadt braucht einen funktionierenden Palast, um Steuern einzutreiben." }
    { group:107, id:0, text: "Wasserheber" }
    { group:107, id:1, text: "Dieser Wasserheber kann große Wassermengen pumpen, wenn Bewässerungsgräben mit seinen vorderen oder hinteren Schleusen verbunden sind." }
    { group:107, id:2, text: "Dieser Wasserheber funktioniert nicht. Bittet Euren Arbeiteraufseher, mehr Arbeiter für Wasserdienste zuzuweisen." }
    { group:107, id:3, text: "Dieser Wasserheber muss an Wasser angrenzen oder durch einen Bewässerungsgraben mit einem funktionierenden Wasserheber verbunden sein, bevor er funktioniert." }
    { group:108, id:0, text: "Wasserversorgung" }
    { group:108, id:1, text: "Wasserträger holen sauberes Wasser aus dieser begehrten Quelle und verbessern Gesundheit und Glück, wenn sie es zu Häusern auf ihren Routen liefern. " }
    { group:108, id:2, text: "Unser Personal trägt ständig sauberes Wasser zur örtlichen Bevölkerung." }
    { group:108, id:3, text: "Wir haben einen kleinen Mangel an Wasserträgern. Wir haben Lücken von vielleicht ein oder zwei Tagen in unserer Abdeckung." }
    { group:108, id:4, text: "Wir sind unterbesetzt und haben gefährliche Lücken von bis zu einer Woche in unserem Wasserlieferzyklus." }
    { group:108, id:5, text: "Wir haben viel zu wenige Arbeiter. Manchmal wird bis zu zwei Wochen am Stück kein Wasser geliefert." }
    { group:108, id:6, text: "Wir arbeiten nur mit Notbesetzung. Wir gehen häufig einen vollen Monat, ohne Wasser zu liefern." }
    { group:108, id:7, text: "Ohne Lieferpersonal könnte diese Einrichtung genauso gut ein trockenes Loch im Boden sein." }
    { group:109, id:0, text: "Brunnen" }
    { group:109, id:1, text: "Bürger ohne saubere Wasserlieferungen können Wasser aus Brunnen ziehen, aber Brunnenwasser-Nachbarschaften sind nicht die gesündesten oder begehrtesten Wohnorte." }
    { group:109, id:2, text: "Dieser Brunnen wird nicht benötigt. Alle Häuser, die er versorgt, bekommen Lieferungen von einer Wasserversorgung." }
    { group:109, id:3, text: "Das Wasser dieses Brunnens wird verschwendet, da es keine Häuser in seinem Versorgungsbereich gibt." }
    { group:110, id:0, text: "Orakel? Gehört Schrein hierher?" }
    { group:110, id:1, text: "Dieser Schrein macht nahegelegene Heime begehrter und erfreut alle Götter. Er beschäftigt jedoch keine Priester oder bietet Häusern Zugang zu einem bestimmten Gott." }
    { group:111, id:0, text: "Brennende Ruine" }
    { group:111, id:1, text: "Feuerwehrleute konnten nicht rechtzeitig hierher kommen, um das Gebäude zu retten. Wenn die Feuer ausgebrannt sind, bleibt nur Schutt an dieser Stelle übrig." }
    { group:112, id:0, text: "Getreidefarm" }
    { group:112, id:1, text: "Getreide muss in Getreidespeichern gelagert werden, um Euer Volk zu ernähren, oder in Lagerhöfen, wenn es für den Export bestimmt ist." }
    { group:112, id:2, text: "Produktion ist" }
    { group:112, id:3, text: "abgeschlossen." }
    { group:112, id:4, text: "Euer Handelsaufseher befahl einen Stopp der Getreidelandwirtschaft." }
    { group:112, id:5, text: "Diese Farm hat keine Arbeiter. Selbst Unkraut hat Schwierigkeiten, hier zu wachsen." }
    { group:112, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Sie erzielt maximalen Ertrag, gegeben ihre aktuelle Fruchtbarkeit." }
    { group:112, id:7, text: "Diese Farm könnte produktiver sein, wenn sie mehr Arbeiter hätte." }
    { group:112, id:8, text: "Diese Farm ist unterbesetzt. Ihre Arbeiter bauen nicht so viel Nahrung an, wie sie könnten." }
    { group:112, id:9, text: "Hier arbeiten sehr wenige Bauern. Die Getreideproduktion ist dementsprechend spärlich." }
    { group:112, id:10, text: "Mit kaum Arbeitern auf dieser Farm wird sie diese Saison sehr wenig Getreide produzieren." }
    { group:112, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet und wird einige Zeit brauchen, um sich zu erholen." }
    { group:112, id:12, text: "Land ist" }
    { group:112, id:13, text: "fruchtbar." }
    { group:112, id:14, text: "Die nächste Getreideernte ist in" }
    { group:113, id:0, text: "Salatfarm" }
    { group:113, id:1, text: "Salat trägt zur ausgewogenen Ernährung bei, die Euer Volk für Glück und Gesundheit braucht. Getreidespeicher lagern Salat für den örtlichen Verbrauch, und Lagerhöfe nehmen Überschüsse für den Export." }
    { group:113, id:2, text: "Produktion ist" }
    { group:113, id:3, text: "abgeschlossen." }
    { group:113, id:4, text: "Der Handelsaufseher verfügte, dass die Salatlandwirtschaft eingestellt werden sollte." }
    { group:113, id:5, text: "Diese Farm hat keine Arbeiter. Nichts wurde gepflanzt." }
    { group:113, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Sie baut so viel Salat an, wie ihre Fruchtbarkeit erlaubt." }
    { group:113, id:7, text: "Diese Farm arbeitet unter maximaler Kapazität, daher ist ihre Ernte kleiner als sie sein könnte." }
    { group:113, id:8, text: "Diese Farm ist unterbesetzt. Ihre Salatköpfe sind kleiner und weniger zahlreich, als sie sein könnten." }
    { group:113, id:9, text: "Hier arbeiten sehr wenige Bauern. Die Salaternte wird stark darunter leiden." }
    { group:113, id:10, text: "Mit fast keinen Bauern, die sich um die Ernte kümmern, wird dies kein Rekordjahr für Salat." }
    { group:113, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet und wird einige Zeit brauchen, um sich zu erholen." }
    { group:113, id:12, text: "Land ist" }
    { group:113, id:13, text: "fruchtbar." }
    { group:113, id:14, text: "Die nächste Salaternte ist in" }
    { group:114, id:0, text: "Granatapfelfarm" }
    { group:114, id:1, text: "Granatäpfel verbessern die ausgewogene Ernährung, die Menschen für Gesundheit und Glück brauchen. Getreidespeicher lagern Granatäpfel für den örtlichen Verbrauch, und Lagerhöfe können Überschüsse exportieren." }
    { group:114, id:2, text: "Produktion ist" }
    { group:114, id:3, text: "abgeschlossen." }
    { group:114, id:4, text: "Der Granatapfelanbau wurde auf Befehl des Handelsaufsehers eingestellt." }
    { group:114, id:5, text: "Dieser Obstgarten hat keine Arbeiter, und die Bäume sind fruchtlos und verkrüppelt." }
    { group:114, id:6, text: "Dieser Obstgarten hat alle Arbeiter, die er braucht. Die Bäume tragen so viel Frucht, wie die Fruchtbarkeit des Landes erlaubt." }
    { group:114, id:7, text: "Dieser Obstgarten arbeitet unter maximaler Kapazität, daher ist die Ernte dieses Jahr etwas leichter als sie sein sollte." }
    { group:114, id:8, text: "Dieser Obstgarten ist unterbesetzt. Er produziert weniger Granatäpfel, als er könnte." }
    { group:114, id:9, text: "Sehr wenige Menschen arbeiten in diesem Obstgarten. Die Granatapfelernte wird klein sein." }
    { group:114, id:10, text: "Mit kaum Arbeitern in diesem Obstgarten wird die Granatapfelernte ziemlich enttäuschend sein." }
    { group:114, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet und wird einige Zeit brauchen, um sich zu erholen." }
    { group:114, id:12, text: "Land ist" }
    { group:114, id:13, text: "fruchtbar." }
    { group:114, id:14, text: "Die nächste Granatapfelernte ist in" }
    { group:115, id:0, text: "Flachsfarm" }
    { group:115, id:1, text: "Flachs geht zu einem Weber, der die Fasern verarbeitet und zu Leinen webt, das Leichenhallen zum Einbalsamieren verwenden, oder für den Export." }
    { group:115, id:2, text: "Produktion ist" }
    { group:115, id:3, text: "abgeschlossen." }
    { group:115, id:4, text: "Euer Handelsaufseher befahl einen Stopp des Flachsanbaus." }
    { group:115, id:5, text: "Diese Farm hat keine Arbeiter. Kein Flachs kann hier wachsen." }
    { group:115, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Die Felder sind mit blauen Flachsblumen bedeckt." }
    { group:115, id:7, text: "Diese Farm arbeitet unter maximaler Kapazität. Die Flachsproduktion könnte mit mehr Arbeitern besser sein." }
    { group:115, id:8, text: "Diese Farm ist unterbesetzt. Flachspflanzen sind nicht so dicht oder so robust, wie sie sein könnten." }
    { group:115, id:9, text: "Hier arbeiten sehr wenige Menschen. Die Flachsernte wird darunter leiden." }
    { group:115, id:10, text: "Mit kaum Arbeitern auf dieser Farm ist der Boden größtenteils kahl." }
    { group:115, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet und wird einige Zeit brauchen, um sich zu erholen." }
    { group:115, id:12, text: "Land ist" }
    { group:115, id:13, text: "fruchtbar." }
    { group:115, id:14, text: "Die nächste Flachsernte ist in" }
    { group:116, id:0, text: "Schilfsammler" }
    { group:116, id:1, text: "Schilfsammler wagen sich von hier in die Sümpfe, um Schilf für Papyrus zu sammeln, ohne das Bildung unmöglich wäre." }
    { group:116, id:2, text: "Gelagertes Schilf" }
    { group:116, id:3, text: "abgeschlossen." }
    { group:116, id:4, text: "Die Schilfgewinnung wurde auf Befehl des Handelsaufsehers eingestellt." }
    { group:116, id:5, text: "Dieser Ort hat keine Arbeiter, um Schilf zu sammeln. " }
    { group:116, id:6, text: "Dieser Ort hat alle Arbeiter, die er braucht. Kein Schilf ist sicher. " }
    { group:116, id:7, text: "Dieser Ort liegt unter seinem Arbeitspotenzial, daher ist das Schilfsammeln etwas verlangsamt." }
    { group:116, id:8, text: "Dieser Ort ist unterbesetzt, daher geht das Schilfschneiden langsam voran. " }
    { group:116, id:9, text: "Sehr wenige Menschen arbeiten hier, und wenig Schilf wird geschnitten." }
    { group:116, id:10, text: "Mit so wenigen hier beschäftigten Sammlern wird fast kein Schilf geerntet." }
    { group:116, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet und wird einige Zeit brauchen, um sich zu erholen." }
    { group:116, id:12, text: "Land ist" }
    { group:116, id:13, text: "fruchtbar." }
    { group:116, id:14, text: "Die nächste Schilfgewinnung ist in" }
    { group:117, id:0, text: "Viehfarm" }
    { group:117, id:1, text: "Gut genährte Bürger wollen Fleisch in ihrer Ernährung. Fleisch kann in Getreidespeichern für den örtlichen Verbrauch gelagert werden oder zu Lagerhöfen für den Export gebracht werden." }
    { group:117, id:2, text: "Produktion ist" }
    { group:117, id:3, text: "abgeschlossen." }
    { group:117, id:4, text: "Auf Erlass des Handelsaufsehers wurde die Viehzucht eingestellt." }
    { group:117, id:5, text: "Diese Farm hat keine Arbeiter. Alle Tiere sind entkommen oder gestorben." }
    { group:117, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Mit Stroh kann sie reichlich Fleisch liefern." }
    { group:117, id:7, text: "Diese Farm muss mehr Arbeiter einstellen, wenn sie effizient Fleisch produzieren soll. " }
    { group:117, id:8, text: "Diese Farm ist unterbesetzt. Sie kann ihre potenzielle Leistung nicht erreichen." }
    { group:117, id:9, text: "Sehr wenige Menschen arbeiten auf dieser Farm. Ihre potenzielle Fleischproduktion ist niedrig." }
    { group:117, id:10, text: "Mit kaum Arbeitern kann diese Farm nur sehr wenige Rinder aufziehen." }
    { group:117, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm verwüstet. Rinder können hier nicht gedeihen, bis es sich erholt." }
    { group:117, id:12, text: "Land ist" }
    { group:117, id:13, text: "fruchtbar." }
    { group:118, id:0, text: "Steinbruch für einfachen Stein" }
    { group:118, id:1, text: "Schneidet einfachen Stein aus der Erde hier. Mit Monumenten, die überall in Ägypten aufragen, könnt Ihr normalerweise einen Käufer für guten Baustein finden, auch wenn Ihr selbst keine Verwendung dafür habt. " }
    { group:118, id:2, text: "Produktion ist" }
    { group:118, id:3, text: "abgeschlossen." }
    { group:118, id:4, text: "Der Handelsaufseher befahl einen Stopp des Steinbruchbetriebs." }
    { group:118, id:5, text: "Dieser Steinbruch hat keine Arbeiter, um Felsen aus der Erde zu schneiden." }
    { group:118, id:6, text: "Dieser Steinbruch hat alle Arbeiter, die er braucht, und produziert viele Tonnen einfachen Steins." }
    { group:118, id:7, text: "Dieser Steinbruch arbeitet unter maximaler Kapazität aufgrund eines kleinen Arbeitermangels." }
    { group:118, id:8, text: "Dieser Steinbruch ist unterbesetzt und braucht länger, um Steinblöcke zu produzieren, als er sollte." }
    { group:118, id:9, text: "Sehr wenige Menschen arbeiten in diesem Steinbruch. Die Produktion ist sehr langsam als Folge." }
    { group:118, id:10, text: "Mit kaum Arbeitern in diesem Steinbruch steht die Produktion praktisch still. Er wird in den kommenden Jahren wenig produzieren." }
    { group:119, id:0, text: "Kalksteinbruch" }
    { group:119, id:1, text: "Schneidet feinen Kalkstein zur Verwendung im Monumentbau oder für den Export." }
    { group:119, id:2, text: "Produktion ist" }
    { group:119, id:3, text: "abgeschlossen." }
    { group:119, id:4, text: "Euer Handelsaufseher befahl einen Stopp des Kalksteinabbaus." }
    { group:119, id:5, text: "Dieser Steinbruch hat keine Arbeiter und produziert daher keinen Kalkstein." }
    { group:119, id:6, text: "Dieser Steinbruch hat alle Arbeiter, die er braucht, und produziert so viel Kalkstein wie möglich." }
    { group:119, id:7, text: "Dieser Steinbruch arbeitet unter maximaler Kapazität. Die Produktion könnte mit mehr Arbeitern größer sein." }
    { group:119, id:8, text: "Dieses Gebäude ist unterbesetzt. Es dauert länger als es sollte, Kalksteinblöcke zu schneiden." }
    { group:119, id:9, text: "Sehr wenige Menschen arbeiten in diesem Gebäude. Die Produktion ist viel zu langsam als Folge." }
    { group:119, id:10, text: "Mit kaum Arbeitern hier ist die Kalksteinproduktion fast nicht existent. " }
    { group:120, id:0, text: "Holzfäller" }
    { group:120, id:1, text: "Holz hat viele Verwendungszwecke, von Monumentbau bis Schiffbau, und ist im ganzen Königreich sehr gefragt." }
    { group:120, id:2, text: "Enthält" }
    { group:120, id:3, text: "Rohholz." }
    { group:120, id:4, text: "Das Baumfällen wurde auf Befehl des Handelsaufsehers eingestellt." }
    { group:120, id:5, text: "Diese Einrichtung hat keine Arbeiter und trägt nichts zur Stadtwirtschaft bei." }
    { group:120, id:6, text: "Dieses Gebäude hat alle Arbeiter, die es braucht. Es erntet Holz mit maximaler Effizienz." }
    { group:120, id:7, text: "Dieser Holzfäller ist nicht voll besetzt, und die Holzproduktion ist niedriger als sie sein könnte." }
    { group:120, id:8, text: "Diese Industrie ist unterbesetzt und braucht länger, um Holz zu schneiden, als sie sollte." }
    { group:120, id:9, text: "Sehr wenige Menschen arbeiten auf diesem Hof. Die Holzproduktion ist sehr langsam als Folge." }
    { group:120, id:10, text: "Mit kaum Baumfällern steht die Holzproduktion hier praktisch still." }
    { group:121, id:0, text: "Lehmgrube" }
    { group:121, id:1, text: "Baut Lehm für den Handel ab oder um Töpfer zu versorgen. Menschen finden endlose Verwendungszwecke für Töpferwaren, und Ihr könnt sie oft profitabel mit anderen Städten handeln." }
    { group:121, id:2, text: "Produktion ist" }
    { group:121, id:3, text: "abgeschlossen." }
    { group:121, id:4, text: "Euer Handelsaufseher stoppte das Lehmgraben." }
    { group:121, id:5, text: "Diese Grube hat keine Arbeiter, um Lehm zu graben." }
    { group:121, id:6, text: "Diese Grube hat alle Arbeiter, die sie braucht, und produziert große Mengen Lehm." }
    { group:121, id:7, text: "Diese Grube arbeitet unter maximaler Kapazität. Die Lehmproduktion wird dadurch etwas langsamer sein." }
    { group:121, id:8, text: "Diese Grube ist unterbesetzt und braucht länger, um Lehm zu produzieren, als sie sollte." }
    { group:121, id:9, text: "So wenige Menschen arbeiten in dieser Grube, dass die Lehmproduktion extrem langsam ist." }
    { group:121, id:10, text: "Mit kaum Gräbern in dieser Grube wird sie im kommenden Jahr sehr wenig Lehm produzieren." }
    { group:122, id:0, text: "Brauerei" }
    { group:122, id:1, text: "Brauer verwandeln Gerste in Bier, ohne das die Senet-Häuser leer und die Stadtfeste langweilig wären. Bier ist eine weit verbreitete Handelsware." }
    { group:122, id:2, text: "Produktion ist" }
    { group:122, id:3, text: "abgeschlossen." }
    { group:122, id:4, text: "Ein Erlass vom Handelsaufseher befahl einen Stopp des Brauens." }
    { group:122, id:5, text: "Diese Brauerei hat keine Angestellten. Es wird kein Bier von hier geben." }
    { group:122, id:6, text: "Mit voller Besetzung arbeitet diese Brauerei mit Höchstgeschwindigkeit, um Ägyptens Durst zu stillen." }
    { group:122, id:7, text: "Diese Brauerei arbeitet unter maximaler Kapazität. Die Bierproduktion ist etwas langsamer als sie sein könnte." }
    { group:122, id:8, text: "Diese Brauerei ist unterbesetzt und braucht viel länger, um Bier zu produzieren, als sie sollte." }
    { group:122, id:9, text: "Sehr wenige Menschen arbeiten in dieser Brauerei. Die Bierproduktion ist sehr langsam als Folge." }
    { group:122, id:10, text: "Mit kaum Brauern im Personal wird diese Brauerei im kommenden Jahr fast kein Bier produzieren." }
    { group:122, id:11, text: "Diese Brauerei kann kein Bier herstellen, bis sie eine Lieferung Gerste von einem Lagerhof oder einer Farm erhält." }
    { group:122, id:12, text: "Gelagerte Gerste," }
    { group:123, id:0, text: "Weber" }
    { group:123, id:1, text: "Hier wird Flachs zu Leinen verarbeitet, das Leichenhallen zum Einbalsamieren benötigen. Leinen kann auch profitabel gehandelt werden." }
    { group:123, id:2, text: "Produktion ist" }
    { group:123, id:3, text: "abgeschlossen." }
    { group:123, id:4, text: "Euer Handelsaufseher verfügte, dass die Leinenproduktion eingestellt wird." }
    { group:123, id:5, text: "Dieser Weber hat keine Arbeiter und kann daher überhaupt kein Leinen produzieren." }
    { group:123, id:6, text: "Dieser Weber ist voll besetzt und produziert reichlich hochwertiges Leinen." }
    { group:123, id:7, text: "Dieser Weber könnte mehr Arbeiter gebrauchen, um sein volles Potenzial für die Leinenproduktion zu erreichen." }
    { group:123, id:8, text: "Dieser Weber ist unterbesetzt und produziert Leinen langsamer als er sollte." }
    { group:123, id:9, text: "Sehr wenige Menschen arbeiten bei diesem Weber. Die Leinenproduktion ist langsam als Folge." }
    { group:123, id:10, text: "Mit kaum Angestellten kann dieser Weber im kommenden Jahr fast kein Leinen produzieren." }
    { group:123, id:11, text: "Diese Werkstatt wird kein Leinen produzieren ohne eine Lieferung Flachs, ob von einem Lagerhof oder einer Farm." }
    { group:123, id:12, text: "Gelagerter Flachs," }
    { group:124, id:0, text: "Waffenschmied" }
    { group:124, id:1, text: "Waffenschmiede verwandeln Kupfer in Speere, die Ihr für einen hübschen Gewinn handeln oder zur Ausrüstung Eurer eigenen Kompanien verwenden könnt." }
    { group:124, id:2, text: "Produktion ist" }
    { group:124, id:3, text: "abgeschlossen." }
    { group:124, id:4, text: "Euer Handelsaufseher befahl einen Stopp der Waffenproduktion." }
    { group:124, id:5, text: "Dieser Waffenschmied hat keine Angestellten und wird daher keine Waffen produzieren." }
    { group:124, id:6, text: "Diese Werkstatt hat alle Angestellten, die sie braucht, und produziert so viele Waffen wie möglich." }
    { group:124, id:7, text: "Dieser Waffenschmied ist nicht voll besetzt, daher ist die Waffenproduktion etwas langsamer als sie sein könnte." }
    { group:124, id:8, text: "Diese Werkstatt ist unterbesetzt. Sie braucht länger, um Waffen zu produzieren, als sie sollte." }
    { group:124, id:9, text: "Sehr wenige Menschen arbeiten bei diesem Waffenschmied. Die Waffenproduktion ist sehr langsam." }
    { group:124, id:10, text: "Mit kaum Angestellten trägt dieser Waffenschmied nur sehr wenige Waffen zu den Bemühungen der Stadt bei." }
    { group:124, id:11, text: "Dieser Waffenschmied braucht Kupfer von einem Lagerhof oder einer Kupfermine, um Waffen zu produzieren." }
    { group:124, id:12, text: "Gelagertes Kupfer," }
    { group:125, id:0, text: "Juwelier" }
    { group:125, id:1, text: "Die Handwerker hier verwandeln Edelsteine in Schmuck (ein Luxusgut). Einige Bürger wollen Schmuck für sich selbst, und Ihr könnt oft Überschüsse exportieren, obwohl er selten viel wert ist." }
    { group:125, id:2, text: "Produktion ist" }
    { group:125, id:3, text: "abgeschlossen." }
    { group:125, id:4, text: "Der Handelsaufseher befiehlt einen Stopp der Schmuckproduktion." }
    { group:125, id:5, text: "Dieser Juwelier hat keine Angestellten und produziert nichts." }
    { group:125, id:6, text: "Diese Einrichtung ist voll besetzt und stellt so viel Schmuck wie möglich her." }
    { group:125, id:7, text: "Diese Einrichtung hat einige offene Stellen. Die Schmuckproduktion wird sich verbessern, wenn sie besetzt sind." }
    { group:125, id:8, text: "Diese Einrichtung ist unterbesetzt und braucht länger, um Schmuck zu produzieren, als sie sollte." }
    { group:125, id:9, text: "Sehr wenige Handwerker arbeiten hier. Die Schmuckproduktion ist sehr langsam als Folge." }
    { group:125, id:10, text: "Mit kaum Handwerkern wird dieser Juwelier im kommenden Jahr wenige Luxusgüter produzieren." }
    { group:125, id:11, text: "Diese Werkstatt braucht eine Lieferung Edelsteine von einem Lagerhof oder einer Edelsteinmine, um Schmuck zu produzieren." }
    { group:125, id:12, text: "Gelagerte Edelsteine," }
    { group:126, id:0, text: "Töpfer" }
    { group:126, id:1, text: "Hier formen Töpfer Lehm zu Töpfen, die Bürger zur Lagerung von Waren verwenden. Handelt mit Töpferwaren oder lasst Eure Basare sie verteilen, damit Menschen bessere Wohnungen bauen können." }
    { group:126, id:2, text: "Produktion ist" }
    { group:126, id:3, text: "abgeschlossen." }
    { group:126, id:4, text: "Die Töpferwarenproduktion wurde auf Befehl des Handelsaufsehers eingestellt." }
    { group:126, id:5, text: "Dieser Töpfer hat keine Angestellten. Er wird keinen einzigen Topf herstellen." }
    { group:126, id:6, text: "Dieser Töpfer hat alle Angestellten, die er braucht, und produziert so viele Töpferwaren wie möglich." }
    { group:126, id:7, text: "Dieser Töpfer hat einige offene Stellen. Die Töpferwarenproduktion wird dadurch etwas leiden." }
    { group:126, id:8, text: "Diese Werkstatt ist unterbesetzt, und es dauert länger, Töpferwaren zu produzieren, als es sollte." }
    { group:126, id:9, text: "Sehr wenige Menschen arbeiten hier, daher ist die Töpferwarenproduktion sehr langsam." }
    { group:126, id:10, text: "Mit kaum Angestellten wird dieser Töpfer im kommenden Jahr fast keine Töpferwaren produzieren." }
    { group:126, id:11, text: "Diese Werkstatt braucht Lehm, der ihr geliefert wird, von einem Lagerhof oder einer Lehmgrube, um Töpferwaren zu produzieren." }
    { group:126, id:12, text: "Gelagerter Lehm," }
    { group:127, id:0, text: "Wohngebäude" }
    { group:127, id:1, text: "Testmodus AUSschalten" }
    { group:127, id:2, text: "Testmodus EINschalten" }
    { group:127, id:3, text: "Attraktivität" }
    { group:127, id:4, text: "Unt" }
    { group:127, id:5, text: "H2O" }
    { group:127, id:6, text: "Religion" }
    { group:127, id:7, text: "Bildung" }
    { group:127, id:8, text: "Basarzugang" }
    { group:127, id:9, text: "Zahnarztzugang" }
    { group:127, id:10, text: "Arztzugang" }
    { group:127, id:11, text: "Gesundheit" }
    { group:127, id:12, text: "Nahrungsarten" }
    { group:127, id:13, text: "Töpferwaren benötigt" }
    { group:127, id:14, text: "Leinen benötigt" }
    { group:127, id:15, text: "Luxusgüter benötigt" }
    { group:127, id:16, text: "Bier benötigt" }
    { group:127, id:17, text: "Jetzt" }
    { group:127, id:18, text: "entwickelt sich bei" }
    { group:127, id:19, text: "benötigt" }
    { group:127, id:20, text: "Bewohner" }
    { group:127, id:21, text: " zu viele." }
    { group:127, id:22, text: "Extra Platz für" }
    { group:127, id:23, text: "Nicht von einem Steuereintreiber besucht. Zahlt keine Steuern" }
    { group:127, id:24, text: "Erzeugt" }
    { group:127, id:25, text: "bisher an Steuern." }
    { group:127, id:26, text: "Bewohner berichten überhaupt keine Verbrechen." }
    { group:127, id:27, text: "Dies ist eine friedliche Nachbarschaft." }
    { group:127, id:28, text: "Es gibt etwas Kriminalität hier, nichts Ernstes." }
    { group:127, id:29, text: "Kriminalität wird zu einem Problem." }
    { group:127, id:30, text: "Hohe Kriminalitätsraten erschrecken die Einheimischen." }
    { group:127, id:31, text: "Ein gesetzloses Gebiet. Menschen fürchten um ihre Sicherheit." }
    { group:127, id:32, text: "Dies ist eine Brutstätte für Diebe." }
    { group:127, id:33, text: "Hütten brauchen Nahrung von einem Basar und attraktive Umgebung, bevor sie sich verbessern. " }
    { group:127, id:34, text: "Wohngebäude FREI" }
    { group:127, id:35, text: "Wohngebäude FREI" }
    { group:127, id:36, text: "Wohngebäude FREI" }
    { group:127, id:37, text: "Wohngebäude FREI" }
    { group:127, id:38, text: "Wohngebäude FREI" }
    { group:127, id:39, text: "Wohngebäude FREI" }
    { group:127, id:40, text: "Dieses Haus wird sich bald zurückentwickeln. Die sinkende Attraktivität, in dieser Gegend zu leben, zieht es herunter" }
    { group:127, id:42, text: "Dieses Haus wird sich bald zurückentwickeln, da es nicht von einem Wasserträger besucht wird" }
    { group:127, id:43, text: "Dieses Haus wird sich bald zurückentwickeln, da keine Unterhaltung an diesem Standort zu finden ist" }
    { group:127, id:44, text: "Dieses Haus wird sich bald zurückentwickeln, da es kaum Unterhaltung an diesem Standort gibt" }
    { group:127, id:45, text: "Dieses Haus wird sich bald zurückentwickeln, da es zu wenig Unterhaltung an diesem Standort gibt" }
    { group:127, id:46, text: "Dieses Haus wird sich bald zurückentwickeln. Es gibt etwas Unterhaltung an diesem Standort, aber nicht genug" }
    { group:127, id:47, text: "Dieses Haus wird sich bald zurückentwickeln. Es gibt gute Unterhaltung an diesem Standort, aber nicht genug Vielfalt" }
    { group:127, id:48, text: "Dieses Haus wird sich bald zurückentwickeln. Es gibt ausgezeichnete Unterhaltung an diesem Standort, aber die Stätten sind zu überfüllt oder haben nicht genug Vielfalt für die anspruchsvollen Schreiberklassen" }
    { group:127, id:49, text: "Dieses Haus wird sich bald zurückentwickeln, da es kürzlich keine Nahrungslieferungen von einem örtlichen Basar erhalten hat" }
    { group:127, id:50, text: "Dieses Haus wird sich bald zurückentwickeln, da es derzeit nur Zugang zu einer einzigen Nahrungsart von seinem örtlichen Basar hat. Dies entmutigt die wohlhabenderen Bürger." }
    { group:127, id:51, text: "Dieses Haus wird sich bald zurückentwickeln, da es derzeit nur zwei Nahrungsarten von seinem örtlichen Basar bekommt. Dies entmutigt die Schreiberklassen." }
    { group:127, id:52, text: "Dieses Haus wird sich bald zurückentwickeln. Es hat den Zugang zu einem Basar verloren." }
    { group:127, id:53, text: "Dieses Haus wird sich bald zurückentwickeln. Obwohl es Zugang zu einem Basar hat, hat der Basar selbst Schwierigkeiten, Nahrungsvorräte zu bekommen." }
    { group:127, id:54, text: "Dieses Haus wird sich bald zurückentwickeln, da es alle grundlegenden Bildungseinrichtungen verloren hat, die entweder von einer Schreibschule oder einer Bibliothek bereitgestellt werden." }
    { group:127, id:55, text: "Dieses Haus wird sich bald zurückentwickeln. Sein Bildungszugang wurde herabgestuft, da es den Zugang zu seiner Bibliothek verloren hat." }
    { group:127, id:56, text: "Dieses Haus wird sich bald zurückentwickeln. Sein Bildungszugang wurde herabgestuft, da es den Zugang zu seiner Schreibschule verloren hat." }
    { group:127, id:57, text: "Dieses Haus wird sich bald zurückentwickeln. Sein zuvor ausgezeichneter Bildungszugang wurde herabgestuft, als es den Zugang zu höherer Bildung verlor." }
    { group:127, id:58, text: "Dieses Haus wird sich bald zurückentwickeln, da es keinen Zugang zu Richtern von Gerichtshöfen hat." }
    { group:127, id:59, text: "Dieses Haus wird sich bald zurückentwickeln. Es hat keine Töpferwaren mehr, und sein örtlicher Basar hat bestenfalls eine unregelmäßige Versorgung." }
    { group:127, id:60, text: "Dieses Haus wird sich bald zurückentwickeln, da es allen Zugang zu örtlichen religiösen Einrichtungen verloren hat." }
    { group:127, id:61, text: "Dieses Haus wird sich bald zurückentwickeln. Sein Zugang zu örtlichen religiösen Einrichtungen wurde auf den Tempel nur eines Gottes reduziert." }
    { group:127, id:62, text: "Dieses Haus wird sich bald zurückentwickeln. Seine zuvor ausgezeichneten religiösen Einrichtungen wurden auf die Tempel von nur zwei Göttern reduziert." }
    { group:127, id:63, text: "Dieses Haus wird sich bald zurückentwickeln, da es den Zahnarztzugang verloren hat." }
    { group:127, id:64, text: "Dieses Haus wird sich bald zurückentwickeln, da es jetzt eine jämmerliche Gesundheitsversorgung hat. Es fehlt nicht nur der Zugang zu einem Leichenwärter, sondern auch der Arztzugang ist weniger als perfekt." }
    { group:127, id:65, text: "Dieses Haus wird sich bald zurückentwickeln, da seine Gesundheitsversorgung gekürzt wurde. Die Arztabdeckung ist gut, aber es gibt keinen örtlichen Zugang zu einer Leichenhalle." }
    { group:127, id:66, text: "Dieses Haus wird sich bald zurückentwickeln, da seine Gesundheitsversorgung gekürzt wurde. Es gibt örtlichen Zugang zu einer Leichenhalle, aber eine Arztpraxis ist schwer zu finden." }
    { group:127, id:67, text: "Dieses Haus wird sich bald zurückentwickeln, da es kein Leinen mehr hat und sein örtlicher Basar bestenfalls eine unregelmäßige Versorgung hat." }
    { group:127, id:68, text: "unbenutzt8" }
    { group:127, id:69, text: "Dieses Haus wird sich bald zurückentwickeln, da es kein Bier mehr hat und sein örtlicher Basar bestenfalls eine unregelmäßige Versorgung hat." }
    { group:127, id:70, text: "Diese Behausung kann sich nicht entwickeln, bis sich die Attraktivität des Gebiets verbessert." }
    { group:127, id:71, text: "Dieses Haus kann sich nicht entwickeln, da es nicht einmal Zugang zur primitivsten Wasserquelle hat." }
    { group:127, id:72, text: "Dieses Haus kann sich nicht entwickeln, da es keinen Zugang zu den Diensten eines Wasserträgers hat " }
    { group:127, id:73, text: "Dieses Haus kann sich nicht entwickeln, da keine Unterhaltung an diesem Standort zu finden ist." }
    { group:127, id:74, text: "Dieses Haus kann sich nicht entwickeln, da es kaum Unterhaltung an diesem Standort zu finden gibt." }
    { group:127, id:75, text: "Dieses Haus kann sich nicht entwickeln, da es zu wenig Unterhaltung an diesem Standort zu finden gibt." }
    { group:127, id:76, text: "Dieses Haus kann sich nicht entwickeln, da es etwas Unterhaltung an diesem Standort zu finden gibt, aber nicht genug." }
    { group:127, id:77, text: "Dieses Haus kann sich nicht entwickeln, da es gute Unterhaltung an diesem Standort zu finden gibt, aber nicht genug Vielfalt." }
    { group:127, id:78, text: "Dieses Haus kann sich nicht entwickeln, da es ausgezeichnete Unterhaltung an diesem Standort zu finden gibt, aber die Stätten zu überfüllt sind oder nicht genug Vielfalt für die anspruchsvollen Schreiberklassen haben." }
    { group:127, id:79, text: "Dieses Haus kann sich nicht entwickeln, da es eine Nahrungsversorgung von einem örtlichen Basar benötigt." }
    { group:127, id:80, text: "Dieses Haus kann sich nicht entwickeln, da es eine zweite Nahrungsart benötigt, die von einem örtlichen Basar geliefert wird, um wohlhabendere Ägypter zum Einzug zu ermutigen." }
    { group:127, id:81, text: "Dieses Haus kann sich nicht entwickeln, da es eine dritte Nahrungsart benötigt, die von einem örtlichen Basar geliefert wird, um eine höhere Klasse von Ägyptern zum Einzug zu ermutigen." }
    { group:127, id:82, text: "Dieses Haus kann sich nicht entwickeln, da es keinen Zugang zu einem örtlichen Basar hat." }
    { group:127, id:83, text: "Dieses Haus kann sich nicht entwickeln. Obwohl es Zugang zu einem örtlichen Basar hat, hat der Basar selbst Schwierigkeiten, Nahrungsvorräte zu bekommen." }
    { group:127, id:84, text: "Dieses Haus kann sich nicht entwickeln, da es keine grundlegenden Bildungseinrichtungen hat, die von einer Schreibschule oder einer Bibliothek bereitgestellt werden." }
    { group:127, id:85, text: "Dieses Haus kann sich nicht entwickeln, da sein Bildungszugang durch Zugang zu einer Bibliothek verbessert werden muss." }
    { group:127, id:86, text: "Dieses Haus kann sich nicht entwickeln, da sein Bildungszugang durch Zugang zu einer Schreibschule verbessert werden muss." }
    { group:127, id:87, text: "unbenutzte Zeile, die Evolution berichtet, die durch fehlenden Akademiezugang gestoppt wurde." }
    { group:127, id:88, text: "Dieses Haus kann sich nicht entwickeln, da es keinen Zugang zu einem örtlichen Richter von einem Gerichtshof hat." }
    { group:127, id:89, text: "Dieses Haus kann sich nicht entwickeln. Es benötigt Vorräte an Töpferwaren, die ihm von seinem örtlichen Basar bereitgestellt werden, bevor eine wohlhabendere Bürgerklasse einzieht." }
    { group:127, id:90, text: "Dieses Haus kann sich nicht entwickeln, da es keinen Zugang zu örtlichen religiösen Einrichtungen hat." }
    { group:127, id:91, text: "Dieses Haus hat nur Zugang zu Tempeln eines einzelnen Gottes. Es wird sich nicht verbessern, bis die Bewohner anderen Göttern huldigen können." }
    { group:127, id:92, text: "Dieses Haus hat nur Zugang zu Tempeln von zwei Göttern. Es wird sich nicht verbessern, bis die Bewohner anderen Göttern huldigen können." }
    { group:127, id:93, text: "Dieses Haus kann sich nicht entwickeln, da es keinen örtlichen Zugang zu einem Zahnarzt hat." }
    { group:127, id:94, text: "Dieses Haus kann sich nicht entwickeln, da es effektiv keine Gesundheitsversorgung hat. Es hat keinen Zugang zu einem Arzt oder einer Leichenhalle." }
    { group:127, id:95, text: "Dieses Haus kann sich nicht entwickeln, da es größere Gesundheitsversorgung wünscht. Die Arztabdeckung ist gut, aber es gibt keinen örtlichen Zugang zu einer Leichenhalle." }
    { group:127, id:96, text: "Dieses Haus kann sich nicht entwickeln, da es größere Gesundheitsversorgung wünscht. Es gibt örtlichen Zugang zu einer Leichenhalle, aber Zugang zu einem Arzt wird benötigt." }
    { group:127, id:97, text: "Dieses Haus kann sich nicht entwickeln. Es benötigt Vorräte an Leinen, die ihm von seinem örtlichen Basar bereitgestellt werden, bevor eine wohlhabendere Bürgerklasse einzieht." }
    { group:127, id:98, text: "unbenutzt9" }
    { group:127, id:99, text: "Dieses Haus kann sich nicht entwickeln. Es benötigt Vorräte an Bier, die ihm von seinem örtlichen Basar bereitgestellt werden, bevor eine wohlhabendere Bürgerklasse einzieht." }
    { group:127, id:100, text: "Die Bewohner dieses Palastes sind auf dem Gipfel der ägyptischen Gesellschaft. Sie wollen nichts. Allein ihre Bedürfnisse zu befriedigen ist eine bemerkenswerte Leistung!" }
    { group:127, id:101, text: "Die örtlichen Bedingungen verbessern sich, und die Eigentümer dieser Behausung modernisieren sie gerade jetzt." }
    { group:127, id:102, text: "Ein nahegelegenes Gebäude (" }
    { group:127, id:103, text: "hat einen nachteiligen Effekt auf die Attraktivität des Standorts." }
    { group:127, id:104, text: "Diese Behausung würde sich bald zu einer von größerer Statur entwickeln, wenn sie mehr Platz zum Expandieren hätte." }
    { group:127, id:105, text: "unbenutzt10" }
    { group:127, id:106, text: "unbenutzt11" }
    { group:127, id:107, text: "Haus infiziert für weitere" }
    { group:127, id:108, text: "Dieses Haus kann sich nicht entwickeln. Bevor eine wohlhabendere Bürgerklasse einzieht, muss der örtliche Basar diese Behausung mit Luxusgütern versorgen, wie" }
    { group:127, id:109, text: "Haus von Fröschen befallen für weitere" }
    { group:127, id:110, text: "Dieses Haus wird sich bald zurückentwickeln, da seine anspruchsvollen Bewohner eine zweite Art von Luxusgut wollen, wie" }
    { group:127, id:111, text: "(unbenutzt)" }
    { group:127, id:112, text: "Dieses Haus wird sich bald zurückentwickeln. Die müßigen Schreiber, die hier leben, brauchen einen Basar, der Luxusgüter bereitstellt, wie" }
    { group:127, id:113, text: "(unbenutzt)" }
    { group:127, id:114, text: "Um sich zu entwickeln, muss ein Basar dieses Haus mit einer zweiten Art von Luxusgut versorgen, wie" }
    { group:127, id:115, text: "(unbenutzt)" }
    { group:127, id:116, text: "(unbenutzt)" }
    { group:128, id:0, text: "Unbewohnt" }
    { group:128, id:1, text: "Dieses Grundstück ist im Moment leer. Entweder wurde das Land noch nicht bebaut, oder die vorherigen Bewohner des bestehenden Heims sind erkrankt und gestorben.  " }
    { group:128, id:2, text: "Dieses Grundstück ist zu weit von der nächsten Straße entfernt. Wenn nicht bald eine neue Straße in der Nähe gebaut wird, wird die Fläche zu offenem Land zurückfallen." }
    { group:129, id:0, text: "von" }
    { group:129, id:1, text: "Kapazität" }
    { group:129, id:2, text: "Kauft" }
    { group:129, id:3, text: "Verkauft" }
    { group:129, id:4, text: "Gekauft" }
    { group:129, id:5, text: "Verkauft" }
    { group:129, id:6, text: "Vor Anker, wartet auf freies Dock" }
    { group:129, id:7, text: "Angedockt, kauft und verkauft Waren" }
    { group:129, id:8, text: "Kehrt nach Hause zurück" }
    { group:129, id:9, text: "Fährt zu den Docks der Stadt" }
    { group:129, id:10, text: "Handelt Waren" }
    { group:129, id:11, text: "Kehrt nach Hause zurück" }
    { group:129, id:12, text: "Unterwegs zu Lagerhöfen der Stadt" }
    { group:129, id:13, text: "Nichts zu handeln hier, nur auf der Durchreise" }
    { group:129, id:14, text: "von" }
    { group:129, id:15, text: "Geht nach" }
    { group:129, id:16, text: "Kehrt zurück nach" }
    { group:129, id:17, text: "Sammelt" }
    { group:129, id:18, text: "Kehrt zurück mit" }
    { group:129, id:19, text: "Einheit von" }
    { group:129, id:20, text: "Einheiten von" }
    { group:129, id:21, text: "Trägt" }
    { group:130, id:0, text: "(nicht benutzt)" }
    { group:131, id:0, text: "Eingeborenen-Hütte" }
    { group:131, id:1, text: "Erscheint dieser Text irgendwo?" }
    { group:132, id:0, text: "Eingeborenen-Versammlungshütte" }
    { group:132, id:1, text: "Wird dieser Eintrag irgendwo benutzt?" }
    { group:133, id:0, text: "Einfache Feldfrüchte" }
    { group:133, id:1, text: "Dieser Eintrag wird wahrscheinlich nicht benutzt." }
    { group:134, id:0, text: "Missionsposten" }
    { group:134, id:1, text: "Wo erschien dieser Text?" }
    { group:135, id:0, text: "Militärakademie" }
    { group:135, id:1, text: "Wenn neue Soldaten ihre Grundausbildung beim Rekrutierer beenden, versuchen sie, sich in Qualität und Fähigkeit in dieser Akademie zu verbessern, können es aber nicht, bis sie ihre volle Personalquote erhält." }
    { group:135, id:2, text: "Ohne Personal können wir die Fähigkeiten der neuen Soldaten der Stadt nicht verfeinern. Sie müssen direkt zu ihren Forts gehen und auf das Beste hoffen." }
    { group:135, id:3, text: "Wir geben grünen Soldaten vom Rekrutierer der Stadt den zusätzlichen Vorteil, den sie brauchen, um in der heutigen ägyptischen Armee hervorzustechen." }
    { group:136, id:0, text: "Rekrutierer" }
    { group:136, id:1, text: "Niemand kann der ägyptischen Armee beitreten, ohne zuerst hier durchzugehen; es ist die Ausbildungsschule der Stadt für neue Rekruten." }
    { group:136, id:2, text: "Waffen gelagert" }
    { group:136, id:3, text: "Ohne Personal können wir keinen einzigen neuen Rekruten ausbilden. Seth helfe uns in Kriegszeiten!" }
    { group:136, id:4, text: "Wir bilden derzeit keine Rekruten aus, da wir keine Anfragen von Forts oder Türmen der Stadt für neue Männer haben." }
    { group:136, id:5, text: "Wir können neue Bogenschützen schnell genug ausbilden, aber wir brauchen Waffen, um Infanterie oder Streitwagen zum Bataillon der Stadt hinzuzufügen." }
    { group:136, id:6, text: "Uns fehlen Angestellte, daher können wir Soldaten mit reduzierter Rate ausbilden. Ohne gelagerte Waffen können wir weder Infanterie noch Streitwagenfahrer ausbilden." }
    { group:136, id:7, text: "Wir sind unterbesetzt und haben keine Waffen! Wir können Bogenschützen ausbilden, aber nur langsam." }
    { group:136, id:8, text: "Mit Notbesetzung und ohne Waffenversorgung können wir kaum den gelegentlichen Bogenschützen ausbilden." }
    { group:136, id:9, text: "Wir bilden neue Soldaten mit maximaler Effizienz aus, und wir haben die Waffen, um jede Art von Soldat auszubilden." }
    { group:136, id:10, text: "Wir bilden neue Soldaten mit reduzierter Geschwindigkeit aus aufgrund von Personalmangel, obwohl wir die Waffen haben, um jede Art von Soldat auszubilden." }
    { group:136, id:11, text: "Wir sind unterbesetzt und bilden neue Soldaten langsam aus, aber wir haben die Waffen, um jede Art von Soldat auszubilden." }
    { group:136, id:12, text: "Mit Notbesetzung bilden wir neue Soldaten extrem langsam aus, obwohl wir die Waffen haben, um jede Art von Soldat auszubilden." }
    { group:136, id:13, text: "Streitwagen gelagert" }
    { group:136, id:14, text: "Streitwagen gelagert" }
    { group:136, id:15, text: "Waffe gelagert" }
    { group:137, id:0, text: "Platz" }
    { group:137, id:1, text: "Plätze machen gewöhnliche gepflasterte Straßen attraktiver, ohne den Verkehr zu beeinflussen." }
    { group:138, id:0, text: "'Die Löwen'" }
    { group:138, id:1, text: "'Die Krokodile'" }
    { group:138, id:2, text: "'Die Kobras'" }
    { group:138, id:3, text: "'Die Skorpione'" }
    { group:138, id:4, text: "'Die Falken'" }
    { group:138, id:5, text: "'Die Widder'" }
    { group:138, id:6, text: "'Die Hyänen'" }
    { group:138, id:7, text: "'Die Skarabäen'" }
    { group:138, id:8, text: "'Die Schakale'" }
    { group:138, id:9, text: "'Die Ottern'" }
    { group:138, id:10, text: "Es sind derzeit keine Soldaten diesem Fort zugewiesen. Entweder sind sie im Ausland im Dienst, oder sie müssen noch vom Rekrutierer ankommen." }
    { group:138, id:11, text: "Diese Kompanie hat keine Soldaten und trägt nichts zu unserer Macht bei. Ohne funktionierenden Rekrutierer, um neue Truppen auszuheben, wird sie eine hohle Einheit bleiben." }
    { group:138, id:12, text: "Position halten in enger Formation" }
    { group:138, id:13, text: "Die Kompanie hält ihre Position und kämpft nur, wenn sie angegriffen wird. Ihre Soldaten erhalten Kampfvorteile, sind aber verwundbarer gegenüber Geschossfeuer." }
    { group:138, id:14, text: "Position halten in lockerer Formation" }
    { group:138, id:15, text: "Die Kompanie kämpft nur, wenn sie angegriffen wird. Soldaten decken mehr Boden ab und sind weniger verwundbar gegenüber Geschossfeuer, aber ihre Kampffähigkeiten leiden." }
    { group:138, id:16, text: "Nahe Feinde angreifen" }
    { group:138, id:17, text: "Unter diesem Befehl greift die Kompanie in Formation jeden Feind an, der töricht genug ist, in ihre Nähe zu kommen." }
    { group:138, id:18, text: "Aufräumen" }
    { group:138, id:19, text: "Wenn so befohlen, löst die Kompanie die Formation auf, um jeden Feind zu suchen und anzugreifen, den sie finden kann." }
    { group:138, id:20, text: "Angriff" }
    { group:138, id:21, text: "Eine Kompanie mit diesem Befehl gibt Vorsicht auf und wendet all ihre Macht auf, um feindliche Reihen zu brechen." }
    { group:138, id:22, text: "Wenn so befohlen, verlässt die Kompanie das Feld und kehrt zu ihrem Fort zurück, um gefallene Kameraden zu ersetzen, sich auszuruhen und ihre Moral wiederherzustellen." }
    { group:138, id:23, text: "Soldaten in der Kompanie" }
    { group:138, id:24, text: "Gesundheit der Soldaten" }
    { group:138, id:25, text: "Erfahrung" }
    { group:138, id:26, text: "Perfekt" }
    { group:138, id:27, text: "Sehr gut" }
    { group:138, id:28, text: "Gut" }
    { group:138, id:29, text: "Durchschnittlich" }
    { group:138, id:30, text: "Schlecht" }
    { group:138, id:31, text: "Sehr schlecht" }
    { group:138, id:32, text: "Entsetzlich" }
    { group:138, id:33, text: "Streitwagenfahrer" }
    { group:138, id:34, text: "Infanterie" }
    { group:138, id:35, text: "Bogenschützen" }
    { group:138, id:36, text: "Moral" }
    { group:138, id:37, text: "In Panik!" }
    { group:138, id:38, text: "Verängstigt" }
    { group:138, id:39, text: "Extrem verängstigt" }
    { group:138, id:40, text: "Sehr verängstigt" }
    { group:138, id:41, text: "Verängstigt" }
    { group:138, id:42, text: "Schwer erschüttert" }
    { group:138, id:43, text: "Erschüttert" }
    { group:138, id:44, text: "Schlecht" }
    { group:138, id:45, text: "Ziemlich schlecht" }
    { group:138, id:46, text: "Unterdurchschnittlich" }
    { group:138, id:47, text: "Durchschnittlich" }
    { group:138, id:48, text: "Überdurchschnittlich" }
    { group:138, id:49, text: "Ermutigt" }
    { group:138, id:50, text: "Ziemlich wagemutig" }
    { group:138, id:51, text: "Wagemutig" }
    { group:138, id:52, text: "Kühn" }
    { group:138, id:53, text: "Sehr kühn" }
    { group:138, id:54, text: "Stark" }
    { group:138, id:55, text: "Extrem stark" }
    { group:138, id:56, text: "Ausgezeichnet" }
    { group:138, id:57, text: "Perfekt" }
    { group:138, id:58, text: "Zurück zum Fort" }
    { group:138, id:59, text: "Von Seth verflucht!" }
    { group:138, id:60, text: "Unerfahren" }
    { group:138, id:61, text: "Geübt" }
    { group:138, id:62, text: "Veteran" }
    { group:138, id:63, text: "Meister" }
    { group:138, id:64, text: "Elite" }
    { group:138, id:65, text: "Die Besten" }
    { group:138, id:66, text: "Trefferpunkte" }
    { group:138, id:67, text: "Nahkampfangriff" }
    { group:138, id:68, text: "Nahkampfrüstung" }
    { group:138, id:69, text: "Rüstung gegen Geschosse" }
    { group:138, id:70, text: "Fernkampfangriff" }
    { group:138, id:71, text: "Fernkampfreichweite" }
    { group:138, id:72, text: "Fernkampffeuerrate" }
    { group:138, id:73, text: "Kompanie" }
    { group:138, id:74, text: "Infanterie-Kompanie" }
    { group:138, id:75, text: "Bogenschützen-Kompanie" }
    { group:138, id:76, text: "Streitwagen-Kompanie" }
    { group:138, id:77, text: "Hier klicken, um die Linie der Kompanie zu drehen" }
    { group:138, id:78, text: "Befehle und Ausrichtung der Kompanie" }
    { group:139, id:0, text: "Lehmmauer" }
    { group:139, id:1, text: "Mauern verhindern das Vordringen von Invasoren in eine Stadt. Invasoren können Mauern zerstören. Dickere Mauern sind stärker und erlauben Wachen von verbundenen Türmen, sie zu patrouillieren." }
    { group:140, id:0, text: "Schutt" }
    { group:140, id:1, text: "Dies sind die Ruinen des oben genannten Gebäudes. Heruntergekommene Stätten wie diese tun wenig, um den Standort zu verbessern." }
    { group:141, id:0, text: "Bewässerungsgraben" }
    { group:141, id:1, text: "Dieser Bewässerungsgraben bewegt Wasser, um Ackerland zu düngen" }
    { group:141, id:2, text: "Dieser Bewässerungsgraben transportiert kein Wasser zu weniger fruchtbaren Gebieten, da er keine Wasserquelle hat, aus der er schöpfen kann." }
    { group:142, id:0, text: "Neue Handelsroute etabliert." }
    { group:142, id:1, text: "Um diese neu verfügbaren Waren zu handeln, sagt Eurem Handelsaufseher, er soll den Status der Waren auf Import oder Export setzen." }
    { group:142, id:2, text: "Aufseher besuchen?" }
    { group:142, id:3, text: "DENKT DARAN! Eure Stadt braucht ein Dock, bevor Handelsschiffe diese neue Seeroute befahren können." }
    { group:143, id:0, text: "Waren akzeptieren" }
    { group:143, id:1, text: "Waren ablehnen" }
    { group:143, id:2, text: "Nahrung anfordern" }
    { group:144, id:0, text: "Klickt auf eine Stadt, um sie zu regieren " }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Leer" }
    { group:144, id:3, text: "Leer" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Leer" }
    { group:144, id:6, text: "Leer" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "leer" }
    { group:144, id:9, text: "leer" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "leer" }
    { group:144, id:12, text: "leer" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "leer" }
    { group:144, id:15, text: "leer" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "leer" }
    { group:144, id:18, text: "leer" }
    { group:144, id:19, text: "Das Ende der Archaischen Periode" }
    { group:144, id:20, text: "Behdet (Apollinopolis): Gefährliche Gewässer" }
    { group:144, id:21, text: "Abedju (Abydos): Die Nekropole" }
    { group:144, id:22, text: "Die Geburt des Alten Reiches" }
    { group:144, id:23, text: "Selima-Oase: Sichert die Karawanenwege" }
    { group:144, id:24, text: "Abu (Elephantine): Beschafft neuen Reichtum" }
    { group:144, id:25, text: "IX (Das Alte Reich)" }
    { group:144, id:26, text: "leer" }
    { group:144, id:27, text: "leer" }
    { group:144, id:28, text: "Das Alte Reich" }
    { group:144, id:29, text: "Serabit Khadim: Der harte Sinai" }
    { group:144, id:30, text: "Meidum: Ein eigenes Grabmal" }
    { group:144, id:31, text: "Das Zeitalter der Pyramiden" }
    { group:144, id:32, text: "Buhen: Die Nubier zähmen" }
    { group:144, id:33, text: "Süd-Dahschur: Eine neue Art von Pyramide" }
    { group:144, id:34, text: "XII (Das Alte Reich)" }
    { group:144, id:35, text: "leer" }
    { group:144, id:36, text: "leer" }
    { group:144, id:37, text: "Das Zeitalter der Pyramiden" }
    { group:144, id:38, text: "Iunet (Dendera): Eine Bedrohung aus Kusch" }
    { group:144, id:39, text: "On (Heliopolis): Die Steinbrüche von Tura" }
    { group:144, id:40, text: "XIV (Das Alte Reich)" }
    { group:144, id:41, text: "leer" }
    { group:144, id:42, text: "leer" }
    { group:144, id:43, text: "Der Höhepunkt des Alten Reiches" }
    { group:144, id:44, text: "Bahariya-Oase: Die Soldaten des Ra" }
    { group:144, id:45, text: "Djedu (Abusir): Ra verehren" }
    { group:144, id:46, text: "Der Niedergang des Alten Reiches" }
    { group:144, id:47, text: "Dunqul-Oase: Vertreibt die Schakale" }
    { group:144, id:48, text: "Dachla-Oase: Ordnung im Chaos" }
    { group:144, id:49, text: "Die Erste Zwischenzeit" }
    { group:144, id:50, text: "Thinis: Der Krieg um den Thron" }
    { group:144, id:51, text: "Waset (Theben): Bedrohter Ruhm" }
    { group:144, id:52, text: "Die Geburt des Mittleren Reiches" }
    { group:144, id:53, text: "Kebet (Coptos): Für den Frieden kämpfen" }
    { group:144, id:54, text: "Menat Khufu (Beni Hasan): Hunger" }
    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "leer" }
    { group:144, id:57, text: "leer" }
    { group:144, id:58, text: "Das Mittlere Reich" }
    { group:144, id:59, text: "Iken (Mirgissa): Die Grenze verschieben" }
    { group:144, id:60, text: "Sawu (Mersa Gawasis): Neue Händler" }
    { group:144, id:61, text: "Das Mittlere Reich" }
    { group:144, id:62, text: "Heh (Semna): Alte Feinde...und neue" }
    { group:144, id:63, text: "Bubastis: Ägyptens Kronjuwel" }
    { group:144, id:64, text: "Die Zweite Zwischenzeit" }
    { group:144, id:65, text: "Khmun (Hermopolis): Vergeltung" }
    { group:144, id:66, text: "Sauty (Lykopolis): Inspiration" }
    { group:144, id:67, text: "Neues Reich: Eroberung oder Frieden?" }
    { group:144, id:68, text: "Byblos: Fällt in Palästina ein" }
    { group:144, id:69, text: "Baki (Kuban): Ein goldenes Zeitalter" }
    { group:144, id:70, text: "Letzte Mission" }
    { group:144, id:71, text: "Rowarty (Avaris): Die Welt gehört uns" }
    { group:144, id:72, text: "Hetepsenusret (Kahun): Die große Pyramide" }
    { group:145, id:0, text: "Diese Mission hat keine Sieg- oder Niederlagebedingungen. Es geht ums Städtebauen, pur und einfach." }
    { group:146, id:0, text: "Bitte bestätigt, dass Eure neue Auflösung korrekt eingestellt wurde (wenn Ihr dies lesen könnt, wurde sie es!) Diese Nachricht läuft in 10 Sekunden aus." }
    { group:146, id:1, text: "Königreich-Standort nicht gewählt." }
    { group:146, id:2, text: "Ich verwende den Standardstandort." }
    { group:146, id:3, text: "Bringt mich zum Königreich-Bildschirm!" }
    { group:147, id:0, text: "Gut gemacht! Indem Ihr die Bäuche Eures Volkes mit nahrhafter Nahrung gefüllt und ihre Häuser vor Feuer und Einsturz geschützt habt, habt Ihr dieser jungen Zivilisation geholfen, ihren ersten Schritt auf dem langen Weg der Geschichte zu machen." }
    { group:147, id:1, text: "Ausgezeichnet. Ihr habt die erste wahre Stadt in diesem unbarmherzigen Land gebaut, habt für die körperlichen und spirituellen Bedürfnisse Eurer Bürger gesorgt und habt der Thinitischen Konföderation geholfen, das geteilte Land zu vereinen.  " }
    { group:147, id:2, text: "Hervorragend! Eure eigenen Bürger beginnen, Euch als ihren Versorger zu sehen, und benachbarte Städte preisen Euch ebenfalls als Versorger in Zeiten der Not." }
    { group:147, id:3, text: "Gut gemacht! Dank Eurer fähigen Führung hat sich die ägyptische Zivilisation erheblich entwickelt und wird dies in den kommenden Jahrzehnten weiterhin tun." }
    { group:147, id:4, text: "Gratulation. Ihr habt eine Hauptstadt gebaut, die sowohl der Lebenden als auch der Toten würdig ist. Und durch die Entwicklung von Handelsbeziehungen mit anderen Städten habt Ihr Eure Stadt auf die Weltbühne gebracht." }
    { group:147, id:5, text: "Pharao applaudiert Euch. Durch Euer geschicktes Management habt Ihr Eure Stadt erfolgreich gegen Beduinenangriffe verteidigt und Ägypten die Mittel zur Selbstverteidigung gegeben." }
    { group:147, id:6, text: "Pharao ist erfreut. Ihr habt die Meere und den Fluss gemeistert und die Ressourcen, die sie bieten, gut genutzt. Die mächtige Marine, die Ihr gebaut habt, patrouilliert die Wasserwege und sichert unsere Grenzen." }
    { group:147, id:7, text: "Pharao lächelt über Eure Errungenschaften. Ihr habt das Beste aus dem gemacht, was Fluss und Meer zu bieten haben, unsere Grenzen mit einer kleinen, aber fähigen Flotte von Schiffen verteidigt. Ihr habt auch den Adel geehrt, indem Ihr ihnen Grabmäler zur Verfügung gestellt habt, um ihre Körper zu beherbergen." }
    { group:147, id:8, text: "Gut gemacht! Ihr habt die doppelte Herausforderung gemeistert, eine wichtige Handelsroute zu sichern und eine prosperierende Stadt zu bauen, die selbst für die anspruchsvollsten Bürger sorgt. Eure Leistung ist wirklich bemerkenswert." }
    { group:147, id:9, text: "Gut gemacht! Ihr habt eine blühende Stadt etabliert, die andere ägyptische Städte als Vorbild ansehen und auf die Nubien neidisch blickt. " }
    { group:147, id:10, text: "Die Leistung, die Ihr vollbracht habt, ist unübertroffen. Mit Eurer Weisheit streckt sich eine massive Pyramide, anders als alles, was zuvor gesehen wurde, zum Himmel und garantiert unserem geliebten Pharao Unsterblichkeit." }
    { group:147, id:11, text: "Ihr habt es geschafft, die Gefahren des Sinai zu überwinden und Ägypten mit reichlich wertvollem Kupfer und Türkis versorgt. Eure Taten werden für Generationen in Erinnerung bleiben." }
    { group:147, id:12, text: "Ausgezeichnet. Die königliche Nekropole, die Ihr zu bauen versucht habt, ist wahrlich prächtig. Ihr und die Jahre treuen Dienstes Eurer Familie wurden reich mit einem eigenen heiligen Grabmal belohnt." }
    { group:147, id:13, text: "Dank Eures Geschicks beansprucht Ägypten nun einen Teil Nubiens als sein eigenes. Durch die Stadt, die Ihr gegründet habt, habt Ihr Ägyptens Stärke, Reichtum und Pracht den eroberten Nubiern demonstriert." }
    { group:147, id:14, text: "Pharao lobt Euch. Die Knickpyramide, die Ihr zu seiner Ehre gebaut habt, ist großartig und überstrahlt jedes in der Vergangenheit gebaute Monument." }
    { group:147, id:15, text: "Herausragend. Ihr habt eine integrale Rolle in einem Meilenstein gespielt: dem Bau der ersten echten Pyramide. Mit der Vollendung von Snofrus Pyramide habt Ihr den Standard des Pyramidenbaus gesetzt, dem alle anderen folgen werden." }
    { group:147, id:16, text: "Außergewöhnlich. Trotz schlechter Bedingungen und ständiger Angriffe von wilden Kuschiten habt Ihr eine feine Stadt gebaut und Ägyptens Südgrenze gestärkt." }
    { group:147, id:17, text: "Prächtig. Die Minen, die Ihr in Tura eingerichtet habt, haben all den Kalkstein geliefert, den Khufu benötigt hat . . . bisher. Mit der starken Wirtschaft basierend auf den produktiven Tura-Minen hat Eure Stadt neue kulturelle und soziale Höhen erreicht." }
    { group:147, id:18, text: "Alle in Ägypten verneigen sich vor Euren Errungenschaften. Ihr habt Khufus massive Pyramide gebaut und sie mit den reichsten Grabbeigaben ausgestattet, und habt Khafra große Ehre erwiesen, seine letzte Ruhestätte und seine beeindruckende Sphinx gebaut." }
    { group:147, id:19, text: "Gut gemacht. Ihr habt das Beste aus begrenzten Ressourcen gemacht und Ras Macht an diesen abgelegenen Ort gebracht." }
    { group:147, id:20, text: "Hervorragend. Der herrliche Sonnentempel, den Ihr gebaut habt, ehrt sowohl Ra als auch Pharao." }
    { group:147, id:21, text: "Ihr habt es geschafft, für Euer Volk zu sorgen, während Ägypten um Euch herum zerbröckelt. Das Geschick Eurer Familie wird Ägypten in den schwierigen kommenden Zeiten gut dienen." }
    { group:147, id:22, text: "Während Ägypten um Euch herum auseinanderfällt, habt Ihr es geschafft, Eure Stadt zusammenzuhalten. Diese Fähigkeiten werden Ägypten in den schwierigen kommenden Zeiten gut dienen." }
    { group:147, id:23, text: "Selbst in Zeiten großer Unruhe haben die beträchtlichen Führungsfähigkeiten Eurer Familie Thinis zu seinem früheren Ruhm zurückgeführt. Euer mutiges Militär hat den Inyotefs geholfen, ihre Rivalen zu besiegen, eine Leistung, die nicht bald vergessen wird." }
    { group:147, id:24, text: "Durch Euren Fleiß habt Ihr ein hungriges Volk während einer Zeit des Krieges ernährt und die notwendigen Verstärkungen geliefert, um diesen Feind ein für alle Mal zu besiegen. Eure Errungenschaften werden nicht bald vergessen werden." }
    { group:147, id:25, text: "Eure unermüdlichen Bemühungen haben dem Königreich eine schöne und stattliche neue Stadt gegeben. Ihr habt auch viel für ganz Ägypten getan, hungrige Menschen in ihrer Zeit der Not ernährt. Eure beträchtlichen Bemühungen sollen nicht unbelohnt bleiben." }
    { group:147, id:26, text: "Die feinen Pyramiden und Obelisken, die Ihr für mich gebaut habt, stehen als Zeugnis meiner Herrschaft, und dafür bin ich zutiefst dankbar. Eure Hingabe soll belohnt werden." }
    { group:147, id:27, text: "Durch Eure selbstlose Hingabe, für Euer Volk zu sorgen, akzeptiert Ägypten Euch nun als rechtmäßigen Pharao und blickt auf Eure Dynastie, um ebenso gütige und einfallsreiche Erben hervorzubringen. " }
    { group:147, id:28, text: "Alle verneigen sich vor Eurer Herrlichkeit, mächtiger Pharao. Ihr habt erfolgreich Nordnubien erobert, während Ihr gleichzeitig unserem Hafen am Roten Meer die Ressourcen gegeben habt, die er zum Gedeihen brauchte, und sicherstellt, dass unsere Streitkräfte eine zuverlässige Kupferquelle haben werden." }
    { group:147, id:29, text: "Es lebe der weise und einfallsreiche Pharao. Der neue Handelshafen am Roten Meer blüht, und Eure Unterstützung half, einen ebenso starken Handelsposten in Nubien zu etablieren." }
    { group:147, id:30, text: "Seth muss wahrlich über Euch lächeln, Kriegerischster Pharao. Ihr habt die Nubier erfolgreich vertrieben und Eure Südgrenze versiegelt." }
    { group:147, id:31, text: "Die glänzende Stadt Bubastis macht Euch, Fähigster Pharao, und ganz Ägypten Ehre." }
    { group:147, id:32, text: "Ägypten jubelt! Die Hyksos wurden aus unserem Land vertrieben, und unter Eurer Führung wird Ägypten zurückerobert. " }
    { group:147, id:33, text: "Ihr habt Eure Generäle erfolgreich mit Versprechen ewigen Lebens zu großen Siegen auf dem Feld inspiriert. Die Hyksos und ihre furchterregenden Streitwagen wurden aus Ägypten vertrieben." }
    { group:147, id:34, text: "Allmächtiger Pharao, indem Ihr die Hethiter zurückgeschlagen habt, ist Ägypten zu einem mächtigen Reich gewachsen! Euer Schwert hat der Welt das Geschenk der ägyptischen Zivilisation gegeben." }
    { group:147, id:35, text: "Friedlichster Pharao, Euer beruhigender Einfluss hat Ägypten an die Schwelle neuer Größe gebracht!" }
    { group:147, id:36, text: "Es lebe der mächtige Pharao! Eure Dynastie hat kein Ebenbild, und Ägypter von jetzt bis zum Ende der Zeit werden Euren Namen mit größter Ehrfurcht aussprechen." }
    { group:147, id:37, text: "Es lebe der mächtige Pharao! Eure Dynastie ist ohne Gleichen, und Ägypter von jetzt bis zum Ende der Zeit werden Euren Namen mit größter Ehrfurcht aussprechen." }
    { group:147, id:38, text: "Gut gemacht. Das Grabmal für Thutmosis I. ist fertig, eine außergewöhnliche Leistung! Pharao ist zuversichtlich, dass ein so schön verziertes Grabmal die Götter erfreuen und seine Reise ins Jenseits beschleunigen wird." }
    { group:147, id:39, text: "Eine beeindruckende Leistung! Es ist in der Tat selten, wenn Arbeiter unter solchem Druck so feine Handwerkskunst produzieren können. Tutanchamuns Grab ist nun sicher für alle Ewigkeit versiegelt. Lasst uns hoffen, dass ketzerische Räuber niemals seine Ruhestätte entdecken!" }
    { group:147, id:40, text: "Eine ausgezeichnete Arbeit! Ihr habt es geschafft, die königlichen Gräber im Tal angemessen zu bewachen und das neue Grabmal wie befohlen fertigzustellen. Pharao Sethos ist höchst erfreut über die exquisite Handwerkskunst Eurer Arbeiter." }
    { group:147, id:41, text: "Gute Arbeit! Unser großer Pharao, Ramses II., hat sich nicht geirrt, als er Euch wählte, die kommerzielle und militärische Entwicklung dieses Landes zu überwachen. Aber Gefahr liegt in der Luft! Hethitische Armeen sind wieder auferstanden, um unsere rechtmäßige Kontrolle über diese wertvollste Region anzufechten. " }
    { group:147, id:42, text: "Die Hand des Pharao hat die abscheulichen Hethiter erneut geschlagen. Groß ist die Freude über unseren weisesten und mutigsten Anführer, Ramses II.! Euer prächtiger Sieg in dieser hart umkämpften Schlacht wird sicherlich für immer in den Annalen der Geschichte verzeichnet werden." }
    { group:147, id:43, text: "Gute Arbeit! Ramses II. ist sehr erfreut über das kolossale Monument, das Ihr zu seiner Ehre in Abu Simbel geschaffen habt." }
    { group:147, id:44, text: "Gut gemacht! Trotz einer scheinbar endlosen Serie niederträchtiger Plagen und Unglücksfälle ist das großartige Grabmal für unseren alternden Pharao vollständig vorbereitet. Seine Pracht spricht gut für unsere Wertschätzung von Ramses II., sicherlich einem von Ägyptens größten Anführern." }
    { group:147, id:45, text: "Die Sonne hat die Gewitterwolke gehoben, die über Ägypten lag. Groß ist die Freude! Der niederträchtige Häuptling der Libu und seine Verbündeten aus dem Meer sind unter dem Schutz der Nacht geflohen. Ihr schlecht durchdachter Plan, sich entlang unserer Küsten anzusiedeln, wurde zerschmettert. Es ist in der Tat glücklich für uns, dass so viele ihrer Frauen und Kinder jetzt unsere beschämten Gefangenen sind." }
    { group:147, id:46, text: "Gut gemacht! Euer persönlicher Mut und Eure Standhaftigkeit in der Schlacht inspirierten Eure Truppen, ihr Äußerstes zu leisten. Die verfluchten Assyrer wurden ungnädig aus Ägyptens Boden vertrieben. Kunde von Eurer Tat hat den Pharao erreicht und er ist in der Tat erfreut." }
    { group:147, id:47, text: "Heil dem Helden von Tanis, Beschützer Ägyptens! Eure glorreichen Siege zu Land und zu Wasser haben Ägyptens fortgesetzte Unabhängigkeit gesichert. Die einst mächtigen Perser zittern nun, bevor sie den Namen von Pharao Achoris aussprechen." }
    { group:147, id:48, text: "Ihr habt gut gearbeitet. Eure weise Führung und sorgfältige Planung haben Alexandria positioniert, das Zentrum des mediterranen Handels zu sein. Es ist höchst bedauerlich, dass Alexander der Große niemals die Hauptstadt seines Reiches sah. Zumindest haben wir die Befriedigung zu wissen, dass er nun sicher darin begraben ist." }
    { group:147, id:49, text: "Die Metropole Alexandria erstrahlt nun als Leuchtfeuer für die Welt! Ihre Große Bibliothek ist unübertroffen als Zentrum für scholastisches Lernen, und der hoch aufragende Pharos-Leuchtturm ist bereits eines der wahren Weltwunder." }
    { group:147, id:50, text: "Eure mächtigen Legionen haben Ptolemäus XIII.s Gesindel zermalmt. Sein ertrunkener Körper wurde aus dem Nil gebaggert als Beweis seines Todes. Die Belagerung wurde aufgehoben und Kleopatra ist nun sicher auf ihrem Thron. Um den Sieg zu feiern und ihre Beziehung weiter zu festigen, sind Caesar und Kleopatra nun auf eine Reise den Nil hinauf auf der luxuriösen königlichen Barke begeben." }
    { group:147, id:51, text: "Die Pracht Alexandrias und das Schicksal Ägyptens sind in guten Händen unter Eurer Leitung. Wie erwartet, als Ihr Marcus Antonius endlich mit Eurer Gegenwart gesegnet habt, erwies er Euch gebührende Huldigung, während er Eure finanzielle Unterstützung suchte, um seine Ziele zu fördern. Tatsächlich wurde er so von Euch bezaubert, dass er nach Alexandria kam, um Euer Gefährte und Liebhaber zu sein." }
    { group:147, id:52, text: "Mit Kleopatras tiefer Schatzkammer und Antonius' Genie für Taktik wurde Octavians Flotte und veterane Legionen in alle Winde zerstreut. Römer warten ungeduldig auf die triumphale Rückkehr von Antonius und Kleopatra. Hand in Hand werden Rom und Alexandria das Mittelmeer für viele weitere Generationen regieren." }
    { group:147, id:53, text: "Benutzerdefinierter Missionssieg" }
    { group:147, id:54, text: "Ihr habt gut gearbeitet, aber viele weitere Herausforderungen erwarten Euch auf Eurer Suche, ...Pharao zu werden! " }
    { group:148, id:0, text: "Endgültige Kulturbewertung" }
    { group:148, id:1, text: "Endgültige Wohlstandsbewertung" }
    { group:148, id:2, text: "Endgültige Monumentbewertung" }
    { group:148, id:3, text: "Endgültige Königreichsbewertung" }
    { group:148, id:4, text: "Endgültige Bevölkerung" }
    { group:148, id:5, text: "Endgültige Stadtmittel" }
    { group:148, id:6, text: "Errichtete Monumente" }
    { group:148, id:7, text: "Mission wurde abgeschlossen in" }
    { group:148, id:8, text: "Leichtester Schwierigkeitsgrad:" }
    { group:148, id:9, text: "Punktzahl:" }
    { group:148, id:10, text: "Gratulation. Ihr könnt zurückgehen und versuchen, Eure Punktzahl zu schlagen, indem Ihr den 'Eine Mission wählen'-Button klickt." }
    { group:148, id:11, text: "Ihr habt es beim letzten Mal besser gemacht, als Ihr diese Mission gespielt habt. " }
    { group:148, id:12, text: "Großartige Arbeit! Ihr habt Eure letzte Punktzahl für diese Mission geschlagen!" }
    { group:148, id:13, text: "Ihr habt diese Mission erfolgreich abgeschlossen, aber [player_name] regiert noch immer unangefochten in dieser Stadt." }
    { group:148, id:14, text: "Ihr haltet nun die Höchstpunktzahl für diese Mission! Ihr habt [player_name]s Leistung übertroffen." }
    { group:148, id:15, text: "Monate" }
    { group:148, id:16, text: "Ihr habt geschummelt! Eure Punktzahl ist nicht würdig, in die Besten Familien aufgenommen zu werden." }
    { group:149, id:0, text: "Allgemeine Anfrage" }
    { group:149, id:1, text: "Ägyptische Stadt unter Angriff" }
    { group:149, id:2, text: "Ferne Schlacht" }
    { group:149, id:3, text: "Fest" }
    { group:149, id:4, text: "Bau" }
    { group:149, id:5, text: "Hungersnot" }
    { group:149, id:6, text: "Bedrohung" }
    { group:150, id:0, text: "Ägyptische Stadt gerettet" }
    { group:150, id:1, text: "Ferne Schlacht gewonnen" }
    { group:150, id:2, text: "Ferne Schlacht verloren" }
    { group:150, id:3, text: "Bestätigung" }
    { group:151, id:0, text: "Amenemhet I." }
    { group:151, id:1, text: "Amenemhet II." }
    { group:151, id:2, text: "Amenemhet III." }
    { group:151, id:3, text: "Amenemhet IV." }
    { group:151, id:4, text: "Anedjib" }
    { group:151, id:5, text: "Den" }
    { group:151, id:6, text: "Djedefra" }
    { group:151, id:7, text: "Djedkara Isesi" }
    { group:151, id:8, text: "Djer" }
    { group:151, id:9, text: "Djet" }
    { group:151, id:10, text: "Djoser" }
    { group:151, id:11, text: "Hetepsechemui " }
    { group:151, id:12, text: "Hor" }
    { group:151, id:13, text: "Hor-Aha" }
    { group:151, id:14, text: "Huni" }
    { group:151, id:15, text: "Inyotef I." }
    { group:151, id:16, text: "Inyotef II." }
    { group:151, id:17, text: "Inyotef III." }
    { group:151, id:18, text: "Chaba" }
    { group:151, id:19, text: "Chasechemui" }
    { group:151, id:20, text: "Chendjer" }
    { group:151, id:21, text: "Chephren" }
    { group:151, id:22, text: "Cheti" }
    { group:151, id:23, text: "Cheops" }
    { group:151, id:24, text: "Menes" }
    { group:151, id:25, text: "Menkauhor" }
    { group:151, id:26, text: "Mykerinos" }
    { group:151, id:27, text: "Mentuhotep I." }
    { group:151, id:28, text: "Mentuhotep II." }
    { group:151, id:29, text: "Mentuhotep III." }
    { group:151, id:30, text: "Mentuhotep IV." }
    { group:151, id:31, text: "Merenre" }
    { group:151, id:32, text: "Königin Merneith" }
    { group:151, id:33, text: "Narmer" }
    { group:151, id:34, text: "Nebka" }
    { group:151, id:35, text: "Neferhotep I. " }
    { group:151, id:36, text: "Neferirkare" }
    { group:151, id:37, text: "Neuserre" }
    { group:151, id:38, text: "Ninetjer" }
    { group:151, id:39, text: "Nitokris" }
    { group:151, id:40, text: "Pepi I." }
    { group:151, id:41, text: "Pepi II." }
    { group:151, id:42, text: "Peribsen" }
    { group:151, id:43, text: "Qa'a" }
    { group:151, id:44, text: "Raneferef" }
    { group:151, id:45, text: "Raneb" }
    { group:151, id:46, text: "Sahure" }
    { group:151, id:47, text: "Sechemchet" }
    { group:151, id:48, text: "Semerchet" }
    { group:151, id:49, text: "Sened" }
    { group:151, id:50, text: "Sesostris I." }
    { group:151, id:51, text: "Sesostris II." }
    { group:151, id:52, text: "Sesostris III." }
    { group:151, id:53, text: "Schepseskaf" }
    { group:151, id:54, text: "Schepseskare" }
    { group:151, id:55, text: "Snofru" }
    { group:151, id:56, text: "Sobekhotep III." }
    { group:151, id:57, text: "Königin Nofrusobek" }
    { group:151, id:58, text: "Teti" }
    { group:151, id:59, text: "Unas" }
    { group:151, id:60, text: "Userkaf" }
    { group:151, id:61, text: "Userkare" }
    { group:151, id:62, text: "Weneg" }
    { group:151, id:63, text: "Ahmose I." }
    { group:151, id:64, text: "Amenophis I." }
    { group:151, id:65, text: "Thutmosis I." }
    { group:151, id:66, text: "Thutmosis II." }
    { group:151, id:67, text: "Hatschepsut" }
    { group:151, id:68, text: "Thutmosis III." }
    { group:151, id:69, text: "Amenophis II." }
    { group:151, id:70, text: "Thutmosis IV." }
    { group:151, id:71, text: "Amenophis III." }
    { group:151, id:72, text: "Echnaton" }
    { group:151, id:73, text: "Neferneferuaten" }
    { group:151, id:74, text: "Semenchkare" }
    { group:151, id:75, text: "Tutanchamun" }
    { group:151, id:76, text: "Eje" }
    { group:151, id:77, text: "Haremhab" }
    { group:151, id:78, text: "Ramses I." }
    { group:151, id:79, text: "Sethos I." }
    { group:151, id:80, text: "Ramses II." }
    { group:151, id:81, text: "Merenptah" }
    { group:151, id:82, text: "Amenmesse" }
    { group:151, id:83, text: "Sethos II." }
    { group:151, id:84, text: "Siptah" }
    { group:151, id:85, text: "Königin Tausret" }
    { group:151, id:86, text: "Sethnacht" }
    { group:151, id:87, text: "Ramses III." }
    { group:151, id:88, text: "Ramses IV." }
    { group:151, id:89, text: "Ramses V." }
    { group:151, id:90, text: "Ramses VI." }
    { group:151, id:91, text: "Ramses VII." }
    { group:151, id:92, text: "Ramses VIII." }
    { group:151, id:93, text: "Ramses IX." }
    { group:151, id:94, text: "Ramses X." }
    { group:151, id:95, text: "Ramses XI." }
    { group:151, id:96, text: "Pije" }
    { group:151, id:97, text: "Schabaka" }
    { group:151, id:98, text: "Schebitku" }
    { group:151, id:99, text: "Taharqa" }
    { group:151, id:100, text: "Tanotamun" }
    { group:151, id:101, text: "Nepherites I." }
    { group:151, id:102, text: "Psammuthis" }
    { group:151, id:103, text: "Hakor" }
    { group:151, id:104, text: "Achoris" }
    { group:151, id:105, text: "Nektanebos" }
    { group:151, id:106, text: "Alexander der Große" }
    { group:151, id:107, text: "Philipp Arrhidaios" }
    { group:151, id:108, text: "Alexander IV." }
    { group:151, id:109, text: "Ptolemaios I." }
    { group:151, id:110, text: "Ptolemaios II." }
    { group:151, id:111, text: "Ptolemaios III." }
    { group:151, id:112, text: "Ptolemaios IV." }
    { group:151, id:113, text: "Ptolemaios V." }
    { group:151, id:114, text: "Ptolemaios VI." }
    { group:151, id:115, text: "Ptolemaios VII." }
    { group:151, id:116, text: "Ptolemaios VIII." }
    { group:151, id:117, text: "Ptolemaios IX." }
    { group:151, id:118, text: "Ptolemaios X." }
    { group:151, id:119, text: "Ptolemaios XI." }
    { group:151, id:120, text: "Ptolemaios XII." }
    { group:151, id:121, text: "Königin Berenike IV." }
    { group:151, id:122, text: "Ptolemaios XIII." }
    { group:151, id:123, text: "Kleopatra VII." }
    { group:151, id:124, text: "Ptolemaios XV." }
    { group:152, id:0, text: "Keine" }
    { group:152, id:1, text: "I" }
    { group:152, id:2, text: "II" }
    { group:152, id:3, text: "III" }
    { group:152, id:4, text: "IV" }
    { group:152, id:5, text: "V" }
    { group:152, id:6, text: "VI" }
    { group:152, id:7, text: "VII" }
    { group:152, id:8, text: "VIII" }
    { group:152, id:9, text: "IX" }
    { group:152, id:10, text: "X" }
    { group:152, id:11, text: "XI" }
    { group:152, id:12, text: "XII" }
    { group:152, id:13, text: "XIII" }
    { group:152, id:14, text: "XIV" }
    { group:152, id:15, text: "XV" }
    { group:152, id:16, text: "XVI" }
    { group:152, id:17, text: "XVII" }
    { group:152, id:18, text: "XVIII" }
    { group:152, id:19, text: "XIX" }
    { group:152, id:20, text: "XX" }
    { group:152, id:21, text: "XXI" }
    { group:152, id:22, text: "XXII" }
    { group:152, id:23, text: "XXIII" }
    { group:152, id:24, text: "XXIV" }
    { group:152, id:25, text: "XXV" }
    { group:152, id:26, text: "XXVI" }
    { group:152, id:27, text: "XXVII" }
    { group:152, id:28, text: "XVIII" }
    { group:152, id:29, text: "XXIX" }
    { group:152, id:30, text: "XXX" }
    
    { group:154, id:0, text: "Jagdhütte" }
    { group:154, id:1, text: "Von hier aus aufspüren und jagen Jäger lokale Wildtiere. Die Jagdhütte verteilt dann Wildfleisch an örtliche Lagerhöfe oder Getreidespeicher." }
    { group:154, id:2, text: "Produktion ist" }
    { group:154, id:3, text: "abgeschlossen." }
    { group:154, id:4, text: "Der Handelsaufseher verfügte, dass die Jagd eingestellt werden sollte." }
    { group:154, id:5, text: "Diese Hütte hat keine Arbeiter. Die Jagd ist abgesagt." }
    { group:154, id:6, text: "Diese Hütte hat alle Arbeiter, die sie braucht. Die Jäger verfolgen jede Herde, die sie finden können." }
    { group:154, id:7, text: "Diese Hütte arbeitet unter maximaler Kapazität. Die Nahrungssammlung wird dadurch langsamer sein." }
    { group:154, id:8, text: "Diese Hütte ist unterbesetzt, und es dauert länger, Fleisch zu sammeln, als es sollte." }
    { group:154, id:9, text: "Sehr wenige Menschen arbeiten hier. Die Fleischsammlung ist wahrlich langsam." }
    { group:154, id:10, text: "Mit kaum Jägern, die hier arbeiten, tollen Beutetiere unbehelligt herum. Es könnte eine sehr hungrige Trockenzeit werden..." }
    { group:154, id:11, text: "Die Jäger dieser Hütte sind unterwegs auf der Suche nach Beute." }
    { group:154, id:12, text: "Es dauert zu lange, bis Fleisch zur Hütte zurückkommt. Versucht, sie näher an Wildtiere zu platzieren." }
    { group:154, id:13, text: "Gelagertes Fleisch," }
    { group:155, id:0, text: "Straßensperre" }
    { group:155, id:1, text: "Platziert Straßensperren, um die Patrouillenrouten von Wanderern einzuschränken. Menschen mit bestimmten Zielen (wie Lieferanten oder Basarkäufer) können frei passieren." }
    { group:156, id:0, text: "Freies Ereignis" }
    { group:156, id:1, text: "Anfrage" }
    { group:156, id:2, text: "Invasion" }
    { group:156, id:3, text: "Erdbeben" }
    { group:156, id:4, text: "Aufstand" }
    { group:156, id:5, text: "Pharao-Wechsel" }
    { group:156, id:6, text: "Seehandelsproblem" }
    { group:156, id:7, text: "Landhandelsproblem" }
    { group:156, id:8, text: "Lohnerhöhung" }
    { group:156, id:9, text: "Lohnsenkung" }
    { group:156, id:10, text: "Verschmutztes Wasser" }
    { group:156, id:11, text: "Goldmineneinbruch" }
    { group:156, id:12, text: "Lehmgrubenflut" }
    { group:156, id:13, text: "Nachfrageanstieg" }
    { group:156, id:14, text: "Nachfragerückgang" }
    { group:156, id:15, text: "Preiserhöhung" }
    { group:156, id:16, text: "Preissenkung" }
    { group:156, id:17, text: "Königreichszuwachs" }
    { group:156, id:18, text: "Königreichsrückgang" }
    { group:156, id:19, text: "Stadtstatusänderung" }
    { group:156, id:20, text: "Nachrichtenereignis" }
    { group:156, id:21, text: "Missglückte Flut" }
    { group:156, id:22, text: "Perfekte Flut" }
    { group:156, id:23, text: "Geschenk" }
    { group:156, id:24, text: "Heuschreckenplage" }
    { group:156, id:25, text: "Froschplage" }
    { group:156, id:26, text: "Hagelsturm" }
    { group:156, id:27, text: "Blutfluss" }
    { group:156, id:28, text: "Verbrechenswelle" }
    { group:156, id:29, text: "Mumie" }
    { group:157, id:0, text: "Osiris" }
    { group:157, id:1, text: "Ra" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Seth" }
    { group:157, id:4, text: "Bast" }
    { group:157, id:5, text: "Hermie" }
    { group:157, id:6, text: "Janus" }
    { group:158, id:0, text: "Gott der Landwirtschaft und der Nilflut" }
    { group:158, id:1, text: "Gott des Königreichs" }
    { group:158, id:2, text: "Gott der Handwerker" }
    { group:158, id:3, text: "Gott der Zerstörung" }
    { group:158, id:4, text: "Göttin des Heims" }
    { group:158, id:5, text: "(Zahnheilkunde)" }
    { group:158, id:6, text: "(Alles)" }
    { group:159, id:0, text: "Fähranleger" }
    { group:159, id:1, text: "WARNUNG! Dieser Fähranleger fehlt eine verknüpfte Stelle über den Fluss. Niemand kann übersetzen." }
    { group:159, id:2, text: "WARNUNG! Der zugehörige Anlegeplatz dieser Fähre fehlt Straßenzugang. Nur Migranten können übersetzen." }
    { group:159, id:3, text: "WARNUNG! Der zugehörige Anlegeplatz dieser Fähre hat Arbeitsprobleme. Nur Migranten können übersetzen." }
    { group:160, id:0, text: "Januar" }
    { group:160, id:1, text: "Februar" }
    { group:160, id:2, text: "März" }
    { group:160, id:3, text: "April" }
    { group:160, id:4, text: "Mai" }
    { group:160, id:5, text: "Juni" }
    { group:160, id:6, text: "Juli" }
    { group:160, id:7, text: "August" }
    { group:160, id:8, text: "September" }
    { group:160, id:9, text: "Oktober" }
    { group:160, id:10, text: "November" }
    { group:160, id:11, text: "Dezember" }
    { group:161, id:0, text: "Schrein des Osiris (Landwirtschaft)" }
    { group:161, id:1, text: "Osiris bringt Fruchtbarkeit ins Land und lässt die Pflanzen wachsen. Besänftigt ihn, oder bereitet Euch darauf vor, hungrig zu bleiben." }
    { group:161, id:2, text: "Schrein des Ra (Das Königreich)" }
    { group:161, id:3, text: "Händler kennen den Wert darin, Ra zu gefallen. Handel ist sicherer und profitabler mit Ras Segen, und das Ansehen Eurer Stadt ist größer." }
    { group:161, id:4, text: "Schrein des Ptah (Handwerker)" }
    { group:161, id:5, text: "Arbeiter und Handwerker verehren Ptah, um ihre Plackerei zu erleichtern. Wenn Ptah verärgert ist, ist keine Industrie vor Katastrophen sicher." }
    { group:161, id:6, text: "Schrein des Seth (Zerstörung)" }
    { group:161, id:7, text: "Seth wacht über Soldaten und ermutigt Tapferkeit im Kampf. Kein Mann wagt es, ohne den Segen von Seth zu kämpfen." }
    { group:161, id:8, text: "Schrein der Bast (Heim)" }
    { group:161, id:9, text: "Wenn Bast missfällt, ist niemandes Heim sicher. Einige geben Bast auch die Schuld für Krankheiten." }
    { group:162, id:0, text: "Goldmine" }
    { group:162, id:1, text: "Goldabbau ist der direkteste Weg, die Schatzkammer Eurer Stadt zu füllen. Glücklich ist die Stadt, die diese kostbare Ressource hat, denn ihr Reichtum ist gesichert." }
    { group:162, id:2, text: "Produktion ist" }
    { group:162, id:3, text: "abgeschlossen." }
    { group:162, id:4, text: "Der Handelsaufseher befahl ein Ende des Goldabbaus." }
    { group:162, id:5, text: "Diese Mine hat keine Arbeiter. Überhaupt kein Erz kann abgebaut werden." }
    { group:162, id:6, text: "Diese Mine hat alle Arbeiter, die sie braucht, und produziert ein kleines Vermögen an Gold." }
    { group:162, id:7, text: "Diese Mine arbeitet unter maximaler Kapazität. Sie würde mehr Gold liefern, wenn es mehr Bergleute gäbe." }
    { group:162, id:8, text: "Diese Mine ist unterbesetzt. Sie produziert weniger Gold, als sie könnte." }
    { group:162, id:9, text: "Sehr wenige Menschen arbeiten hier. Die Goldproduktion ist ziemlich anämisch." }
    { group:162, id:10, text: "Mit kaum Arbeitern hier hat der Bergbau fast gestoppt. Sehr wenig Gold wird daraus kommen." }
    { group:163, id:0, text: "Edelsteinmine" }
    { group:163, id:1, text: "Baut Edelsteine für den Export ab oder um Schmuck zu produzieren, das grundlegende Luxusgut Eurer Stadt." }
    { group:163, id:2, text: "Produktion ist" }
    { group:163, id:3, text: "abgeschlossen." }
    { group:163, id:4, text: "Euer Handelsaufseher entschied, dass die Stadt genug Edelsteine hat, und stoppte den Abbau." }
    { group:163, id:5, text: "Diese Mine hat keine Arbeiter. Edelsteine bleiben für immer im Felsen eingeschlossen." }
    { group:163, id:6, text: "Diese Mine hat alle Arbeiter, die sie braucht, und produziert glitzernde Haufen von Edelsteinen." }
    { group:163, id:7, text: "Diese Mine hat einige offene Stellen, und die Edelsteinproduktion ist weniger effizient, als sie sein könnte." }
    { group:163, id:8, text: "Diese Mine ist unterbesetzt. Sie produziert erheblich weniger Edelsteine, als sie könnte." }
    { group:163, id:9, text: "Sehr wenige Bergleute arbeiten hier. Edelsteine aus dem Felsen zu lösen, ist wahrlich langsam." }
    { group:163, id:10, text: "Mit kaum Arbeitern hier werden fast keine Edelsteine abgebaut." }
    { group:164, id:0, text: "Feuerwache" }
    { group:164, id:1, text: "Feuerwachen schicken Brandmeister in die Stadt, um Brände zu verhindern und die auszulöschen, die ausbrechen. " }
    { group:164, id:2, text: "Unser Brandmeister patrouilliert die Straßen." }
    { group:164, id:3, text: "Unser Brandmeister bereitet sich auf seinen Dienst vor." }
    { group:164, id:4, text: "Derzeit ist unser Dienstplan voll. Unsere Brandmeister sind immer dort draußen und wittern Anzeichen von Feuer." }
    { group:164, id:5, text: "Wir haben einen kleinen Mangel an Brandmeistern. Wir haben Lücken von vielleicht ein oder zwei Tagen in unserer Abdeckung." }
    { group:164, id:6, text: "Wir sind unterbesetzt. Es gibt Verzögerungen von bis zu einer Woche bei Feuervorbeugungspatrouillen." }
    { group:164, id:7, text: "Wir haben viel zu wenige Leute. Oft verlassen keine Brandmeister die Feuerwache für bis zu zwei Wochen am Stück." }
    { group:164, id:8, text: "Wir arbeiten nur mit Schreibtischpersonal. Wir gehen häufig einen vollen Monat, ohne einen Brandmeister auf die Straßen zu schicken." }
    { group:164, id:9, text: "Ohne Personal ist diese Feuerwache kaum mehr als ein Feuer, das darauf wartet zu passieren." }
    { group:165, id:0, text: "Ziegelmauer" }
    { group:165, id:1, text: "Mauern verhindern das Vordringen von Invasoren in eine Stadt. Invasoren können Mauern zerstören. Dickere Mauern sind stärker und erlauben Wachen von verbundenen Türmen, sie zu patrouillieren. " }
    { group:166, id:0, text: "Mauer" }
    { group:166, id:1, text: "Mauern verhindern das Vordringen von Invasoren in eine Stadt. Invasoren können Mauern zerstören. Dickere Mauern sind stärker und erlauben Wachen von verbundenen Türmen, sie zu patrouillieren." }
    { group:167, id:0, text: "Ziegeltorhaus" }
    { group:167, id:1, text: "Mauern brauchen ein Torhaus, damit Migranten und Händler frei kommen und gehen können." }
    { group:168, id:0, text: "Torhaus" }
    { group:168, id:1, text: "Mauern brauchen ein Torhaus, damit Migranten und Händler frei kommen und gehen können." }
    { group:169, id:0, text: "Ziegelturm" }
    { group:169, id:1, text: "Baut Türme in regelmäßigen Abständen in Eure Mauern oder zumindest in verwundbaren Bereichen. Wenn sie mit Straßen verbunden sind, erhalten Türme Wachen vom Rekrutierer der Stadt. Turmwachen lassen Speere auf nahegelegene Invasoren regnen und patrouillieren dicke genug Mauern." }
    { group:169, id:2, text: "Ohne Arbeiter können wir die Türme nicht besetzen oder Wachen einstellen, um die Mauern zu patrouillieren." }
    { group:169, id:3, text: "Unsere Männer sind wachsam und bereit, jeden Angriff abzuwehren." }
    { group:169, id:4, text: "Wir haben Wartungspersonal, aber wir brauchen Wachen von einem Rekrutierer, um die Stadt zu verteidigen." }
    { group:170, id:0, text: "Turm" }
    { group:170, id:1, text: "Baut Türme in regelmäßigen Abständen in Eure Mauern oder zumindest in verwundbaren Bereichen. Wenn sie mit Straßen verbunden sind, erhalten Türme Wachen vom Rekrutierer der Stadt. Turmwachen lassen Speere auf nahegelegene Invasoren regnen und patrouillieren dicke genug Mauern." }
    { group:170, id:2, text: "Ohne Arbeiter können wir unsere Türme nicht besetzen oder Wachen einstellen, um die Mauern zu patrouillieren." }
    { group:170, id:3, text: "Unsere Männer sind wachsam und bereit, jeden Angriff abzuwehren." }
    { group:170, id:4, text: "Wir haben Wartungspersonal, aber wir brauchen Wachen von einem Rekrutierer, um die Stadt zu verteidigen." }
    { group:171, id:0, text: "Zimmerergilde" }
    { group:171, id:1, text: "Zimmerer versammeln sich hier, um Geschichten und Tipps über ihren Beruf auszutauschen, Arbeitsaufträge zu finden und ihre Probleme auszuhämmern." }
    { group:171, id:2, text: "Produktion ist" }
    { group:171, id:3, text: "abgeschlossen." }
    { group:171, id:4, text: "Diese Gilde wurde von Eurem Handelsaufseher geschlossen" }
    { group:171, id:5, text: "Diese Gilde hat keine Angestellten. Zimmererdienste sind nicht verfügbar." }
    { group:171, id:6, text: "Diese Gilde hat alle Angestellten, die sie braucht. Zimmerer können mit maximaler Effizienz arbeiten." }
    { group:171, id:7, text: "Diese Gilde arbeitet unter maximaler Kapazität. Die Arbeit wird dadurch etwas langsamer sein." }
    { group:171, id:8, text: "Diese Gilde ist unterbesetzt und liefert weniger Zimmerer, als sie könnte." }
    { group:171, id:9, text: "Sehr wenige Menschen arbeiten hier. Es gibt eine erhebliche Wartezeit für die Dienste eines Zimmerers." }
    { group:171, id:10, text: "Mit kaum Angestellten in dieser Gilde scheint es ewig zu dauern, bis ein Zimmerer auftaucht." }
    { group:171, id:11, text: "Diese Werkstatt braucht Holz, das ihr geliefert wird." }
    { group:171, id:12, text: "Gelagertes Holz," }
    { group:172, id:0, text: "Maurergilde" }
    { group:172, id:1, text: "Maurer versammeln sich hier, um Geschichten und Tipps über ihren Beruf auszutauschen, Arbeitsaufträge zu finden und Pläne für die Zukunft zu schmieden. " }
    { group:172, id:2, text: "Produktion ist" }
    { group:172, id:3, text: "abgeschlossen." }
    { group:172, id:4, text: "Diese Gilde wurde von Eurem Handelsaufseher geschlossen" }
    { group:172, id:5, text: "Diese Gilde hat keine Angestellten. Es können keine Ziegel verlegt werden." }
    { group:172, id:6, text: "Diese Gilde hat alle Angestellten, die sie braucht. Maurer können mit maximaler Effizienz arbeiten." }
    { group:172, id:7, text: "Diese Gilde arbeitet unter maximaler Kapazität. Die Arbeit wird dadurch etwas langsamer sein." }
    { group:172, id:8, text: "Diese Gilde ist unterbesetzt und liefert weniger Maurer, als sie könnte." }
    { group:172, id:9, text: "Sehr wenige Menschen arbeiten hier. Es gibt eine erhebliche Wartezeit für Maurerdienste." }
    { group:172, id:10, text: "Mit kaum Angestellten in dieser Gilde scheint es ewig zu dauern, bis ein Maurer auftaucht." }
    { group:172, id:11, text: "Diese Gilde stellt Facharbeiter für den Monumentbau zur Verfügung. Sie benötigt keine eigene Ziegellieferung." }
    { group:172, id:12, text: "Gelagerte Ziegel," }
    { group:173, id:0, text: "Steinmetzgilde" }
    { group:173, id:1, text: "Steinmetze treffen sich hier, um Geschichten und Tipps über ihren Beruf auszutauschen, Arbeitsaufträge zu finden und Pläne für die Zukunft auszuarbeiten. " }
    { group:173, id:2, text: "Produktion ist" }
    { group:173, id:3, text: "abgeschlossen." }
    { group:173, id:4, text: "Diese Gilde wurde von Eurem Handelsaufseher geschlossen" }
    { group:173, id:5, text: "Diese Gilde hat keine Angestellten. Steinmetzarbeiten sind nicht möglich." }
    { group:173, id:6, text: "Diese Gilde hat alle Angestellten, die sie braucht. Steinmetze können mit maximaler Effizienz arbeiten." }
    { group:173, id:7, text: "Diese Gilde arbeitet unter maximaler Kapazität. Die Arbeit wird dadurch etwas langsamer sein." }
    { group:173, id:8, text: "Diese Gilde ist unterbesetzt und stellt weniger Steinmetze zur Verfügung, als sie könnte." }
    { group:173, id:9, text: "Sehr wenige Menschen arbeiten hier. Es gibt eine lange Wartezeit für Steinmetzarbeiten." }
    { group:173, id:10, text: "Mit kaum Angestellten in dieser Gilde scheint es ewig zu dauern, bis ein Steinmetz zum Dienst erscheint." }
    { group:173, id:11, text: "Diese Gilde stellt Facharbeiter für den Monumentbau zur Verfügung. Sie benötigt keine eigene Steinlieferung." }
    { group:173, id:12, text: "Gelagerter Stein," }
    { group:174, id:0, text: "Transportwerft" }
    { group:174, id:1, text: "Transportschiffe, gebaut von Schiffsbauern, legen hier zwischen Einsätzen an. Euer Bataillon braucht Transportschiffe, um den Nil zu befahren." }
    { group:174, id:2, text: "Unser Transportschiff ist im Hafen." }
    { group:174, id:3, text: "Unser Transportschiff ist unterwegs beim Transportieren." }
    { group:175, id:0, text: "Kriegsschiffwerft" }
    { group:175, id:1, text: "Ein Kriegsschiff liegt hier zwischen Schlachten vor Anker. Jede Stadt am Nil sollte mindestens ein paar Verteidigungsschiffe bereit haben." }
    { group:175, id:2, text: "Unser Kriegsschiff ist im Hafen." }
    { group:175, id:3, text: "Unser Kriegsschiff ist draußen und verteidigt die Stadt gegen Invasionen." }
    { group:176, id:0, text: "Gerichtshof" }
    { group:176, id:1, text: "Gerichtshöfe entsenden Richter, die helfen, Verbrechen zu reduzieren, indem sie sicherstellen, dass alle Beschwerden eine faire Anhörung bekommen. Gerichtshoftresore halten einen Teil Eurer Stadtschatzkammer." }
    { group:176, id:2, text: "Dieser Gerichtshof hat überhaupt keine Arbeiter, also lösen örtliche Bürger ihre eigenen Streitigkeiten auf welche Weise auch immer sie können." }
    { group:176, id:3, text: "Es gibt so wenige verfügbare Richter, dass rechtliche Entscheidungen den Klägern fast zufällig erscheinen." }
    { group:176, id:4, text: "Mit nur halb der benötigten Arbeiter urteilt dieser Gerichtshof manchmal voreilig." }
    { group:176, id:5, text: "Da er etwas unterbesetzt ist, hat dieser Gerichtshof einen kleinen Rückstau an Fällen zu hören." }
    { group:176, id:6, text: "Der Gerichtshof hat alle Mitarbeiter, die er braucht, um Bürgerbeschwerden schnell zu hören und sorgfältige Entscheidungen zu fällen." }
    { group:176, id:7, text: "Der Richter ist unterwegs, Streitigkeiten zu lösen." }
    { group:176, id:8, text: "Der Richter ist in seinen Kammern." }
    { group:176, id:9, text: "Tresor enthält" }
    { group:177, id:0, text: "Dieses Ackerland ist bewässert." }
    { group:177, id:1, text: "Dieses Ackerland ist nicht bewässert." }
    { group:177, id:2, text: "Die nächsten Fluten kommen in" }
    { group:177, id:3, text: "Dieses Gebiet bietet hochfruchtbares Land, nachdem der Fluss zurückgegangen ist." }
    { group:177, id:4, text: "Dieses Gebiet wird hochfruchtbares Land bieten, sobald der Fluss zurückgeht." }
    { group:177, id:5, text: "Diese Farm braucht Arbeiter, die in einem Arbeitslager ausgebildet werden können." }
    { group:177, id:6, text: "Diese Farm hat eine vollständige Mannschaft von Arbeitern, die die Felder bearbeiten." }
    { group:178, id:0, text: "abgeschlossen. " }
    { group:178, id:1, text: "Arbeiter beenden jetzt die Außenseite der Pyramide." }
    { group:178, id:2, text: "Diese Aufgabe ist" }
    { group:178, id:3, text: "Zuerst müssen Arbeiter den Pyramidenstandort bis auf das Grundgestein räumen. Mehr Bauern aus Arbeitslagern könnten den Nivellierungsprozess beschleunigen." }
    { group:178, id:4, text: "Zuerst müssen Arbeiter den Mastaba-Standort bis auf das Grundgestein räumen. Mehr Bauern aus Arbeitslagern könnten den Nivellierungsprozess beschleunigen." }
    { group:178, id:5, text: "Arbeiter schneiden jetzt Rillen ins Grundgestein, um Wasser zu halten. Mehr Bauern aus Arbeitslagern würden diese Arbeit beschleunigen." }
    { group:178, id:6, text: "Jetzt füllen wir die Rillen im Grundgestein mit Wasser. Mehr Bauern aus Arbeitslagern könnten dies schneller machen." }
    { group:178, id:7, text: "Arbeiter markieren den Wasserspiegel und lassen dann das Wasser aus den Rillen ab.    " }
    { group:178, id:8, text: "Wir schneiden das Grundgestein sehr sorgfältig bis zu den Wasserspiegelmarken ab. Niemand wird diese Arbeit je sehen, aber sie stellt sicher, dass das Monument für immer Bestand hat." }
    { group:178, id:9, text: "Die Wasserspiegelrillen werden mit Geröll gefüllt. Es muss fest verdichtet werden, damit das Monument sich nicht mit der Zeit setzt." }
    { group:178, id:10, text: "Die Standortvorbereitung ist fertig! Wir haben das Land nivelliert, und jetzt sind wir bereit, das Grabmal zu bauen." }
    { group:178, id:11, text: "Die Basis wurde nivelliert und ein Dach wird auf das Grabmal gesetzt. Jetzt gibt es eine Ruhestätte, die für die Ewigkeit geeignet ist." }
    { group:178, id:12, text: "Bauvorarbeiter" }
    { group:178, id:13, text: "Denkt Ihr, Götter vom Himmel werden dieses Monument bauen? Baut einige Arbeitslager, damit ich etwas Bauernarbeit bekommen kann, und zwar schnell!" }
    { group:178, id:14, text: "Es gibt keine verfügbaren Steinmetze, um an diesem Monument zu arbeiten. Wenn Ihr Fortschritt wollt, baut sofort eine Steinmetzgilde!" }
    { group:178, id:15, text: "Ich nehme an, die Ziegel für dieses Projekt werden sich magisch selbst zusammensetzen. Das muss Euer Plan sein, da Ihr keine Maurergilde gebaut habt." }
    { group:178, id:16, text: "Ohne eine Zimmerergilde in der Stadt, um Rampen oder Gerüste zu bauen, hoffe ich, dass Ihr ein sehr kurzes Monument plant!  " }
    { group:178, id:17, text: "Keine Bauern haben sich zum Dienst gemeldet. Ich würde herausfinden, warum, wenn ich Ihr wäre. Vielleicht sind Eure Arbeitslager eher wie Schlaflager." }
    { group:178, id:18, text: "Beeindruckender Steinhaufen, nicht wahr? Und das ist alles, was es je sein wird, es sei denn, einige Steinmetze tauchen auf. Die Steinmetzgilde in dieser Stadt wird keine Preise für Produktivität gewinnen..." }
    { group:178, id:19, text: "Unter uns gesagt, die Maurergilde in dieser Stadt muss eine Art Freizeitclub sein. Sie schickt mir keine Maurer, das ist sicher." }
    { group:178, id:20, text: "Ich brauche hier einen Zimmerer, und ich brauche ihn jetzt! Warum wendet Ihr Eure Führungsfähigkeiten nicht bei dieser nichtsnutzigen Zimmerergilde an?" }
    { group:178, id:21, text: "Sehr viele Menschen stehen herum und warten darauf, dass ein Zimmerer auftaucht. Er lässt sich wirklich Zeit.  " }
    { group:178, id:22, text: "Ein Steinmetz ohne Stein ist traurig anzusehen. Gewinnt oder importiert mehr gewöhnlichen Stein, oder dieses Monument wird nie Gestalt annehmen." }
    { group:178, id:23, text: "Ihr solltet besser mehr Kalkstein gewinnen oder importieren, wenn Steinmetze ein Monument zu unseren Lebzeiten bauen sollen." }
    { group:178, id:24, text: "Es sei denn, die Stadt importiert oder gewinnt mehr Sandstein, wird unser Steinmetz einen frühen Ruhestand genießen." }
    { group:178, id:25, text: "Es wird nicht viel von einem Monument, mit der dürftigen Granitversorgung, die ich sehe. Gewinnt oder importiert mehr davon." }
    { group:178, id:26, text: "Es sei denn, Ihr importiert mehr Marmor, werden unsere Steinmetze nie in der Lage sein, dieses Monument zu beenden." }
    { group:178, id:27, text: "Unsere Maurer brauchen viel mehr Ziegel, als sie bekommen. Wenn wir sie nicht herstellen können, könnt Ihr vielleicht einige importieren." }
    { group:178, id:28, text: "Meine Zimmerer beklagen den Holzmangel. Fällt mehr Bäume oder erhöht die Importe." }
    { group:178, id:29, text: "Unsere Maurer sind bereit, Kupfer zum Dach hinzuzufügen, wenn es nur ankommen würde. Baut mehr ab oder importiert es." }
    { group:178, id:30, text: "Arbeiter räumen und nivellieren jetzt gerade den Bauplatz. Dies wäre eine gute Zeit, etwas gewöhnlichen Stein und Kalkstein anzuhäufen. Wir werden reichlich brauchen." }
    { group:178, id:31, text: "Alles scheint gut zu laufen, und die Pyramide steigt immer höher und höher." }
    { group:178, id:32, text: "Die Maurer machen jetzt die feinen Steinarbeiten. Wir werden keinen Kalkstein mehr brauchen, um diese Arbeit zu beenden." }
    { group:178, id:33, text: "Arbeiter räumen und nivellieren jetzt gerade den Bauplatz. Danach werden wir reichlich Ziegel und Kalkstein brauchen, um dieses Monument fertigzustellen." }
    { group:178, id:34, text: "Alles scheint gut zu laufen, und die Pyramide steigt immer höher und höher." }
    { group:178, id:35, text: "Die Maurer machen jetzt die feinen Steinarbeiten. Wir werden keine Ziegel oder Kalkstein mehr brauchen, um diese Arbeit zu beenden." }
    { group:178, id:36, text: "Arbeiter räumen und nivellieren jetzt gerade den Bauplatz. Danach werden wir reichlich gewöhnlichen Stein brauchen, um dieses Monument zu bauen." }
    { group:178, id:37, text: "Alles scheint gut zu laufen, und die Pyramide steigt Stufe für Stufe." }
    { group:178, id:38, text: "Endlich ist die Pyramide fertig!" }
    { group:178, id:39, text: "Arbeiter räumen jetzt gerade den Bauplatz. Danach werden wir reichlich Ziegel für die Mastaba brauchen." }
    { group:178, id:40, text: "Alles scheint gut zu laufen. Diese Mastaba wird im Handumdrehen fertig sein." }
    { group:178, id:41, text: "Die Mastaba ist fertig." }
    { group:178, id:42, text: "Endlich haben wir den ganzen Granit, den wir brauchen. Sobald meine Zimmerer fertig sind, das Gerüst zu bauen, können Steinmetze beginnen, den Obelisken zu schnitzen." }
    { group:178, id:43, text: "Meine Steinmetze arbeiten hart daran, den mächtigen Obelisken zu schnitzen." }
    { group:178, id:44, text: "Der Obelisk ist fertig!" }
    { group:178, id:45, text: "Maurer erstellen die grobe Form der Sphinx." }
    { group:178, id:46, text: "Maurer machen feine Schnitzereien an der Sphinx." }
    { group:178, id:47, text: "Arbeiter vollenden und bemalen die Sphinx." }
    { group:178, id:48, text: "Die Sphinx ist fertig!" }
    { group:178, id:49, text: "Zimmererarbeit ist " }
    { group:178, id:50, text: "Maurerarbeit ist " }
    { group:178, id:51, text: "Alle Bauern der Stadt werden auf den Überschwemmungsebenen-Farmen benötigt, wodurch ihnen nur drei Monate im Jahr bleiben, um an diesem Projekt zu arbeiten. Baut mehr Arbeitslager in der Nähe des Monumentstandorts, um die Dinge zu beschleunigen." }
    { group:178, id:52, text: "Arbeiter können nicht zum Bereitstellungsbereich des Monuments gelangen. Seht nach, was die Planken blockiert, die ihn markieren." }
    { group:178, id:53, text: "Jetzt, wo wir genug Sandstein haben, können wir mit der Arbeit am Sonnentempel beginnen. Meine Arbeiter räumen gerade den Platz." }
    { group:178, id:54, text: "Sobald meine Zimmerer fertig sind, das Gerüst zu bauen, können Maurer beginnen, den zentralen Obelisken für den Sonnentempel zu schnitzen." }
    { group:178, id:55, text: "Meine Maurer schnitzen jetzt den zentralen Obelisken. Wenn sie fertig sind, werden wir mehr Sandstein brauchen, um den Rest des Sonnentempels fertigzustellen." }
    { group:178, id:56, text: "Sobald wir das Vestibül, die Mauer und den Vortempel fertigstellen, wird dieses Monument fertig sein." }
    { group:178, id:57, text: "Der Sonnentempel ist fertig! " }
    { group:178, id:58, text: "Jetzt, wo wir genug Sandstein haben, können wir mit diesem Monument beginnen. Meine Arbeiter räumen gerade den Platz." }
    { group:178, id:59, text: "Maurer arbeiten hart daran, dieses Mausoleum fertigzustellen. Alles läuft nach Plan, und ich erwarte keine Probleme." }
    { group:178, id:60, text: "Das Mausoleum ist fertig." }
    { group:178, id:61, text: "Das/Die [monument_name] ist zu [percent_complete] fertig." }
    { group:178, id:62, text: "Noch wurde keine Schicht vollständig verlegt. " }
    { group:178, id:63, text: "Eine Schicht wurde vollständig verlegt. " }
    { group:178, id:64, text: "[number_courses_complete] Schichten wurden vollständig verlegt. " }
    { group:178, id:65, text: "Die aktuelle Schicht benötigt [quantity_needed_current_course_main] ([number_loads_current_course_main]) zur Fertigstellung." }
    { group:178, id:66, text: "Die aktuelle Schicht benötigt [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) zur Fertigstellung." }
    { group:178, id:67, text: "Die aktuelle Schicht benötigt [quantity_needed_current_course_main] ([number_loads_current_course_main]) und [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) zur Fertigstellung." }
    { group:178, id:68, text: "Der Rest des/der [monument_name] wird zusätzlich [quantity_needed_remainder_main] ([number_loads_remainder_main]) benötigen. " }
    { group:178, id:69, text: "Der Rest des/der [monument_name] wird zusätzlich [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary]) benötigen." }
    { group:178, id:70, text: "Der Rest des/der [monument_name] wird zusätzlich [quantity_needed_remainder_main] ([number_loads_remainder_main]) und [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary]) benötigen." }
    { group:178, id:71, text: "Das/Die [monument_name] ist jetzt fertig und enthält insgesamt [quantity_total_main]." }
    { group:178, id:72, text: "Das/Die [monument_name] ist jetzt fertig und enthält insgesamt [quantity_total_main] und [quantity_total_secondary]." }
    { group:178, id:73, text: "Mastaba" }
    { group:178, id:74, text: "Pyramide" }
    { group:178, id:75, text: "Stufenpyramide" }
    { group:178, id:76, text: "Knickpyramide" }
    { group:178, id:77, text: "Ziegelpyramide" }
    { group:178, id:78, text: "Obelisk" }
    { group:178, id:79, text: "Sphinx" }
    { group:178, id:80, text: "Sonnentempel" }
    { group:178, id:81, text: "Bibliothek von Alexandria" }
    { group:178, id:82, text: "Abu Simbel" }
    { group:178, id:83, text: "Kleines königliches Grabmal" }
    { group:178, id:84, text: "Mittleres königliches Grabmal" }
    { group:178, id:85, text: "Großes königliches Grabmal" }
    { group:178, id:86, text: "Prächtiges königliches Grabmal" }
    { group:178, id:87, text: "Caesareum" }
    { group:178, id:88, text: "Leuchtturm" }
    { group:178, id:89, text: "Mausoleum" }
    { group:178, id:90, text: "Blöcke gewöhnlichen Steins" }
    { group:178, id:91, text: "Blöcke Kalkstein" }
    { group:178, id:92, text: "Blöcke Granit" }
    { group:178, id:93, text: "Blöcke Sandstein" }
    { group:178, id:94, text: "Ziegel" }
    { group:178, id:95, text: "Blöcke Marmor" }
    { group:178, id:96, text: "Barren Kupfer" }
    { group:178, id:97, text: "Dieses Mausoleum benötigt die Dienste eines Zimmerers. " }
    { group:178, id:98, text: "Der Handelsaufseher weigert sich, gewöhnlichen Stein an meine Arbeiter freizugeben. Er behauptet, Ihr hättet befohlen, ihn zu lagern. Ich glaube ihm nicht, aber vielleicht solltet Ihr ihn zurechtweisen." }
    { group:178, id:99, text: "Euer Handelsaufseher sagt, dass Ihr ihm befohlen habt, Kalkstein zu lagern. Es sei denn, Ihr habt ein Gespräch mit ihm, werden meine Arbeiter nie Lieferungen bekommen. " }
    { group:178, id:100, text: "Habt Ihr wirklich den Handelsaufseher angewiesen, Sandstein zu lagern? Er wird keine Lieferungen aus den Lagerhöfen genehmigen." }
    { group:178, id:101, text: "Könntet Ihr Euren Handelsaufseher bitten, aufzuhören, weißen Marmor zu lagern? Wir könnten ihn am Monument wirklich gebrauchen." }
    { group:178, id:102, text: "Euer Handelsaufseher sagt, dass Ihr ihm befohlen habt, Granit zu lagern. Es sei denn, Ihr habt ein Gespräch mit ihm, werden meine Arbeiter nie Lieferungen bekommen. " }
    { group:178, id:103, text: "Euer Handelsaufseher wagt es, Euch für den Arbeits-Stillstand zu beschuldigen! Er behauptet, dass Ihr befohlen habt, Ziegel zu lagern." }
    { group:178, id:104, text: "Der Handelsaufseher sagte mir, dass Ihr ihm befohlen habt, Kupfer zu lagern. Ich bin sicher, Ihr habt einen guten Grund dafür, aber meine Männer können nicht ohne das Gut am Monument weiterarbeiten." }
    { group:178, id:105, text: "Der Pharao wird nicht im Geringsten amüsiert sein, wenn seine Lebensgeschichte nicht auf die eleganteste Art erzählt wird. Ohne Handwerkergilde, von wem erwartet Ihr, dass er das Grab illustriert?" }
    { group:178, id:106, text: "Ein ziemlich trostlos aussehendes Grab, nicht wahr? So wird es bleiben, es sei denn, einige Handwerker tauchen bald auf! Ich dachte immer, sie waren eine faule Truppe. Ihr solltet besser sehen, was die Verzögerung ist." }
    { group:178, id:107, text: "Ohne Marmor haben unsere talentierten Steinmetze nichts zu tun. Das ist wirklich schade, da ich sie wirklich viel beschäftigter sehen möchte. Ihr solltet besser dafür sorgen, dass etwas Marmor schnell importiert wird." }
    { group:178, id:108, text: "Das Dach darauf wird wie ein Sieb lecken, wenn wir kein Kupfer bekommen. Wenn Ihr es nicht abbauen könnt, dann solltet Ihr besser welches importieren. Je eher ich es bekomme, desto eher wird dieses Monument fertig sein!" }
    { group:178, id:109, text: "Arbeiter räumen und nivellieren das Land. Jetzt wäre eine ausgezeichnete Zeit, eine gute Marmorversorgung anzuhäufen." }
    { group:178, id:110, text: "Die Arbeit geht gut voran. Die Arbeiter haben alle Materialien, die sie brauchen." }
    { group:178, id:111, text: "Es ist kaum zu glauben, aber der Handelsaufseher informiert mich, dass Marmor in unseren Lagerhöfen gelagert wird. Ohne Marmor, wie könnt Ihr erwarten, dass die Arbeit weitergeht?" }
    { group:178, id:112, text: "Ich habe von einer zuverlässigen Quelle erfahren, dass Granit gelagert wird. Erwartet Ihr, dass ich beschwöre, was ich aus dem Sand des Nils brauche? Ihr solltet besser dafür sorgen, dass etwas Granit sofort meinen Steinmetzen zur Verfügung gestellt wird." }
    { group:178, id:113, text: "Ohne eine Kupferversorgung, wie könnt Ihr erwarten, dass das Dach dieser großen Struktur fertiggestellt wird? So unglaublich es scheinen mag, Euer Handelsaufseher hat mir gesagt, dass er es lagert." }
    { group:178, id:114, text: "Wir warten darauf, dass Bauern das Land räumen." }
    { group:178, id:115, text: "Jetzt, wo das Land geräumt ist, setzen Steinmetze das Fundament an seinen Platz." }
    { group:178, id:116, text: "Das Fundament ist fertig, also können wir jetzt am Boden arbeiten." }
    { group:178, id:117, text: "Wir errichten jetzt einige Säulen, nachdem der Boden verlegt ist." }
    { group:178, id:118, text: "Ein Dach zu bauen ist der nächste Schritt. Die Säulen sind fertig." }
    { group:178, id:119, text: "Jetzt brauchen wir etwas Kupfer, um das Dach fertigzustellen, damit es wie die Sonne glänzt." }
    { group:178, id:120, text: "Wir geben der Bibliothek jetzt nur noch den letzten Schliff." }
    { group:178, id:121, text: "Alexandrias Bibliothek ist fertig und ist das Zentrum des Lernens in der bekannten Welt." }
    { group:178, id:122, text: "Bauern arbeiten hart daran, das Land für das Caesareum zu räumen." }
    { group:178, id:123, text: "Jetzt, wo das Land fertig ist, sind die Steinmetze damit beschäftigt, ein solides Fundament zu legen." }
    { group:178, id:124, text: "Unsere müden Steinmetze haben das Fundament fertig verlegt. Keine Rast für die Erschöpften allerdings: der Bau des Tempels ist im Gange." }
    { group:178, id:125, text: "Mit dem zentralen Tempel fertig, hat die Arbeit am Patio begonnen!" }
    { group:178, id:126, text: "Von Patios zu Portiken! Unsere geschickten Steinmetze haben den Patio fertiggestellt und mit der Arbeit am Portikus begonnen. " }
    { group:178, id:127, text: "Die Steinmetze haben begonnen, das Dach auf die Säulen des Portikus zu setzen." }
    { group:178, id:128, text: "Alle Dachsektionen sind an Ort und Stelle auf den Portiken." }
    { group:178, id:129, text: "Der majestätische Eingang des Caesareums ist fertig." }
    { group:178, id:130, text: "Steinmetze haben das Innere des Caesareums fertiggestellt und ihre Aufmerksamkeit den Granitobelisken zugewandt, die die Außenseite des Gebäudes schmücken." }
    { group:178, id:131, text: "Das Caesareum ist fertig und feiert die Union zwischen Ägypten und Rom." }
    { group:178, id:132, text: "Bauern haben die beschwerliche Aufgabe begonnen, das Land zu räumen." }
    { group:178, id:133, text: "Die Steinmetze legen eifrig das Fundament für den Leuchtturm." }
    { group:178, id:134, text: "Das Fundament ist fast fertig und der Parkettboden wird verlegt." }
    { group:178, id:135, text: "Mit dem Parkettboden fertig, haben die Steinmetze ihre Aufmerksamkeit der ersten Ebene des Leuchtturms zugewandt." }
    { group:178, id:136, text: "Die Steinmetze haben nicht viel Zeit, ihre Arbeit an der ersten Ebene zu bewundern, denn die Arbeit an der zweiten achteckigen Ebene wird bald beginnen." }
    { group:178, id:137, text: "Der Leuchtturm nimmt wirklich Gestalt an. Die achteckige Ebene ist fertig, und die Steinmetze werden bald die Kuppel beginnen." }
    { group:178, id:138, text: "Das letzte Stück des Leuchtturms wurde an seinen Platz gelegt, aber das Monument wird nicht fertig sein, bis das Gerüst entfernt ist. Diese Arbeit beginnt jetzt." }
    { group:178, id:139, text: "Das meiste Gerüst wurde entfernt, und der Leuchtturm ist fast fertig." }
    { group:178, id:140, text: "Der Pharos-Leuchtturm ist fertig und strahlt als Leuchtfeuer über das östliche Mittelmeer." }
    { group:178, id:141, text: "Arbeiter sind damit beschäftigt, an Abu Simbel zu arbeiten. Stellt sicher, dass die Zimmerer reichlich Holz haben, damit sie Gerüste rechtzeitig bauen können." }
    { group:178, id:142, text: "Die beeindruckenden Figuren unseres Ramses II. begrüßen alle, die sich Ägypten vom Süden nähern." }
    { group:178, id:143, text: "Die Handwerker und Maurer weigern sich, einen Fuß in das königliche Grabmal zu setzen ohne Lampen. Es ist schrecklich dunkel da drin!" }
    { group:178, id:144, text: "Die Handwerker und Maurer sind geschäftig bei ihrem Handwerk, und die Arbeit am königlichen Grabmal geht gut voran. Denkt daran, die Handwerkergilde mit Ton und Farbe versorgt zu halten, um zu helfen, dass alles reibungslos läuft." }
    { group:178, id:145, text: "Das königliche Grabmal ist fertig. Alles, was jetzt noch fehlt, sind die Grabbeigaben, die der Verstorbene im Schilffeld brauchen wird." }
    { group:178, id:146, text: "Das verborgene königliche Grabmal ist jetzt bereit für den Pharao. Möge Horus das Grab bewachen und jeden niederschlagen, der es zu schänden wagt!" }
    { group:178, id:147, text: "Lampen:" }
    { group:178, id:148, text: "Arbeiter können nicht zum Eingang des Grabes gelangen. Seht nach, was den Weg blockiert." }
    { group:178, id:149, text: "Arbeiter können nicht zum Bereitstellungsbereich des Monuments gelangen. Seht nach, was ihren Zugang blockiert." }
    { group:179, id:0, text: "Arbeitslager" }
    { group:179, id:1, text: "Dieses Arbeitslager beherbergt Arbeiter, die entweder auf Überschwemmungsebenen-Farmen oder an Monumenten arbeiten können." }
    { group:179, id:2, text: "Dieses Arbeitslager braucht Arbeiter, um die hier ansässigen Handarbeiter zu unterstützen. " }
    { group:179, id:3, text: "Wir liefern so viel ungelernte Arbeit, wie menschenmöglich ist." }
    { group:179, id:4, text: "Unsere Arbeiter sind unterwegs auf der Suche nach Arbeit." }
    { group:179, id:5, text: "Unsere Arbeiter sind unterwegs und arbeiten auf Überschwemmungsebenen-Farmen." }
    { group:179, id:6, text: "Unsere Arbeiter sind unterwegs und arbeiten an Monumenten." }
    { group:179, id:7, text: "Unsere Arbeiter sind unterwegs und arbeiten sowohl auf Überschwemmungsebenen-Farmen als auch an Monumenten." }
    { group:180, id:0, text: "Ziegelei" }
    { group:180, id:1, text: "Ton und Stroh werden hier kombiniert, um robuste, dauerhafte Ziegel zu formen." }
    { group:180, id:2, text: "Produktion ist" }
    { group:180, id:3, text: "abgeschlossen." }
    { group:180, id:4, text: "Euer Handelsaufseher befahl einen Stopp der Ziegelproduktion." }
    { group:180, id:5, text: "Diese Ziegelei hat keine Angestellten. Nicht ein einziger Ziegel kann hergestellt werden." }
    { group:180, id:6, text: "Diese Werkstatt hat alle Angestellten, die sie braucht. Sie produziert tonnenweise Ziegel." }
    { group:180, id:7, text: "Diese Ziegelei hat einige unbesetzte Stellen, was die Ziegelproduktion etwas verlangsamt." }
    { group:180, id:8, text: "Diese Werkstatt ist unterbesetzt, und es dauert länger, Ziegel zu produzieren, als es sollte." }
    { group:180, id:9, text: "Sehr wenige Menschen arbeiten hier. Die Ziegelproduktion ist viel langsamer, als sie sein könnte." }
    { group:180, id:10, text: "Mit kaum Arbeitern wird diese Ziegelei sehr wenige Ziegel im kommenden Jahr produzieren." }
    { group:180, id:11, text: "Diese Werkstatt braucht Ton, der ihr geliefert wird, von einem Lagerhof oder einer Tongrube, um Ziegel zu produzieren." }
    { group:180, id:12, text: "Diese Werkstatt braucht Stroh, das ihr geliefert wird, von einem Lagerhof oder einer Getreidefarm, um Ziegel zu produzieren." }
    { group:180, id:13, text: "Ton: " }
    { group:180, id:14, text: "Stroh: " }
    { group:181, id:0, text: "Gerstenfarm" }
    { group:181, id:1, text: "Gerste ist eine Schlüsselzutat für Bier, ohne das unsere Zivilisation sicherlich nicht existieren würde." }
    { group:181, id:2, text: "Produktion ist" }
    { group:181, id:3, text: "abgeschlossen." }
    { group:181, id:4, text: "Euer Handelsaufseher befahl, dass die Gerstenlandwirtschaft eingestellt werden sollte." }
    { group:181, id:5, text: "Diese Farm hat keine Arbeiter. Das Land liegt brach." }
    { group:181, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Sie erhält maximalen Ertrag, gegeben ihre Fruchtbarkeit." }
    { group:181, id:7, text: "Diese Farm hat einige offene Stellen. Sie könnte mit mehr Arbeitern mehr Gerste anbauen." }
    { group:181, id:8, text: "Diese Farm ist unterbesetzt. Die Gerstenernte könnte viel besser sein, als sie ist." }
    { group:181, id:9, text: "So wenige Bauern arbeiten hier, dass wir kaum genug Gerste für 'Leicht'-Bier haben." }
    { group:181, id:10, text: "Mit kaum Arbeitern auf dieser Farm könnten Ägypter bald darauf reduziert werden, Wasser zu trinken." }
    { group:181, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm befallen und wird einige Zeit brauchen, um sich zu erholen." }
    { group:181, id:12, text: "Land ist" }
    { group:181, id:13, text: "fruchtbar." }
    { group:181, id:14, text: "Die nächste Gerstenernte ist in" }
    { group:182, id:0, text: "Kichererbsenfarm" }
    { group:182, id:1, text: "Kichererbsen sind eine vielseitige Proteinquelle und sehr beliebt in der Ernährung Eures Volkes." }
    { group:182, id:2, text: "Produktion ist" }
    { group:182, id:3, text: "abgeschlossen." }
    { group:182, id:4, text: "Euer Handelsaufseher befahl einen Stopp der Kichererbsenlandwirtschaft." }
    { group:182, id:5, text: "Diese Farm hat keine Arbeiter. Das Land liegt brach." }
    { group:182, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Sie erhält maximalen Ertrag, gegeben ihre Fruchtbarkeit." }
    { group:182, id:7, text: "Diese Farm würde gerne mehr Arbeiter einstellen. Sie könnte mehr Kichererbsen anbauen, als sie tut." }
    { group:182, id:8, text: "Diese Farm ist unterbesetzt. Ihre Arbeiter bauen weniger Kichererbsen an, als das Land hervorbringen könnte." }
    { group:182, id:9, text: "Es gibt sehr wenige Bauern, die hier arbeiten. Die Kichererbsenproduktion ist weit vom Maximum entfernt." }
    { group:182, id:10, text: "Mit kaum Arbeitern auf dieser Farm wird die Kichererbsenernte vernachlässigbar sein." }
    { group:182, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm befallen und wird einige Zeit brauchen, um sich zu erholen." }
    { group:182, id:12, text: "Land ist" }
    { group:182, id:13, text: "fruchtbar." }
    { group:182, id:14, text: "Die nächste Kichererbsenernte ist in" }
    { group:183, id:0, text: "Feigenfarm" }
    { group:183, id:1, text: "Feigen spielen eine wichtige Rolle in der ausgewogenen Ernährung, die Menschen für Gesundheit und Glück brauchen." }
    { group:183, id:2, text: "Produktion ist" }
    { group:183, id:3, text: "abgeschlossen." }
    { group:183, id:4, text: "Euer Handelsaufseher befahl einen Stopp der Feigenlandwirtschaft." }
    { group:183, id:5, text: "Dieser Hain hat keine Arbeiter. Die Bäume sind wild und unfruchtbar." }
    { group:183, id:6, text: "Dieser Hain hat alle Arbeiter, die er braucht. Er erhält maximalen Ertrag für seine Fruchtbarkeit." }
    { group:183, id:7, text: "Dieser Hain könnte mehr Arbeiter gebrauchen. Er würde mehr Feigen produzieren." }
    { group:183, id:8, text: "Dieser Hain ist unterbesetzt. Seine Arbeiter ernten weniger Feigen, als sie sonst könnten." }
    { group:183, id:9, text: "Es gibt sehr wenige Bauern, die hier arbeiten. Die Feigenproduktion ist weit vom Maximum entfernt." }
    { group:183, id:10, text: "Mit kaum Arbeitern auf dieser Farm wird sie kaum eine Feige geben." }
    { group:183, id:11, text: "Das Land dieser Farm wurde durch den jüngsten Heuschreckenschwarm befallen und wird einige Zeit brauchen, um sich zu erholen." }
    { group:183, id:12, text: "Land ist" }
    { group:183, id:13, text: "fruchtbar." }
    { group:183, id:14, text: "Die nächste Feigenernte ist in" }
    { group:184, id:0, text: "Transportschiff" }
    { group:184, id:1, text: "Kriegsschiff" }
    { group:184, id:2, text: "Rumpfstärke" }
    { group:184, id:3, text: "Sehr stark" }
    { group:184, id:4, text: "Stark" }
    { group:184, id:5, text: "Gut" }
    { group:184, id:6, text: "Durchschnittlich" }
    { group:184, id:7, text: "Ordentlich" }
    { group:184, id:8, text: "Schwach" }
    { group:184, id:9, text: "Position halten" }
    { group:184, id:10, text: "Wenn so befohlen, bleibt das Schiff in Position und blockiert die Durchfahrt aller feindlichen Schiffe, solange es über Wasser bleibt." }
    { group:184, id:11, text: "Nahe Feinde angreifen " }
    { group:184, id:12, text: "Unter diesem Befehl bewacht das Kriegsschiff ein kleines Gebiet. Es bewegt sich, um alle feindlichen Soldaten oder Schiffe anzugreifen, die in Reichweite kommen." }
    { group:184, id:13, text: "Alle Feinde suchen und zerstören" }
    { group:184, id:14, text: "Mit diesem Befehl sucht das Kriegsschiff weit und breit nach feindlichen Schiffen und Soldaten und greift alle an, die es erreichen kann." }
    { group:184, id:15, text: "Reparieren" }
    { group:184, id:16, text: "Das Schiff kehrt zu einem Schiffsbauer für Reparaturen zurück. Kapitäne von schwer beschädigten Schiffen werden aus eigener Initiative zur Reparatur einlaufen." }
    { group:184, id:17, text: "Zur Werft zurückkehren" }
    { group:184, id:18, text: "Dies weist das Schiff an, zu seiner Ausgangswerft zurückzukehren, wo die Mannschaft sich ausruhen und ihre Geister wiederbeleben kann." }
    { group:184, id:19, text: "Position halten" }
    { group:184, id:20, text: "Wenn so befohlen, bleibt das Schiff um jeden Preis in Position. Es könnte nicht lange über Wasser bleiben, wenn es angegriffen wird." }
    { group:184, id:21, text: "Feinden ausweichen" }
    { group:184, id:22, text: "Der Kapitän dieses Schiffes hat den Dauerbefehl auszuweichen. Wenn nicht anders befohlen, vermeidet er Feindkontakt um jeden Preis." }
    { group:184, id:23, text: "Einsteigen" }
    { group:184, id:24, text: "Dieser Befehl weist den Kapitän des Schiffes an, eine Kompanie Soldaten zum Transport aufzunehmen." }
    { group:184, id:25, text: "Aussteigen" }
    { group:184, id:26, text: "Dieser Befehl sagt dem Kapitän, eine Kompanie Soldaten an Land abzusetzen." }
    { group:184, id:27, text: "Mannschaftsermüdung" }
    { group:184, id:28, text: "Ausgeruht" }
    { group:184, id:29, text: "Müde" }
    { group:184, id:30, text: "Erschöpft " }
    { group:184, id:31, text: "Bogenschützenkompanie," }
    { group:184, id:32, text: "Streitwagenkompanie," }
    { group:184, id:33, text: "Infanteriekompanie," }
    { group:184, id:34, text: "an Bord" }
    { group:185, id:0, text: "Streitwagenwerkstatt" }
    { group:185, id:1, text: "Experten-Handwerker produzieren hier 'Kriegsräder', eine von Ägyptens tödlichsten Waffen." }
    { group:185, id:2, text: "Produktion ist" }
    { group:185, id:3, text: "abgeschlossen." }
    { group:185, id:4, text: "Euer Handelsaufseher verfügte, dass die Streitwagenproduktion eingestellt werden sollte." }
    { group:185, id:5, text: "Dieser Streitwagenmacher hat keine Angestellten und wird überhaupt keine Kriegsräder produzieren." }
    { group:185, id:6, text: "Dieser Streitwagenmacher ist voll besetzt und produziert viele hochwertige Streitwagen." }
    { group:185, id:7, text: "Dieser Streitwagenmacher könnte mehr Arbeiter gebrauchen, um sein volles Potential für Streitwagenproduktion zu erreichen." }
    { group:185, id:8, text: "Dieser Streitwagenmacher ist unterbesetzt und produziert Streitwagen langsamer, als er sollte." }
    { group:185, id:9, text: "Sehr wenige Menschen arbeiten bei diesem Streitwagenmacher. Die Streitwagenproduktion ist dadurch langsam." }
    { group:185, id:10, text: "Mit kaum Angestellten wird dieser Streitwagenmacher sehr wenige Streitwagen im kommenden Jahr produzieren." }
    { group:185, id:11, text: "Diese Werkstatt wird keine Streitwagen ohne eine Holzlieferung produzieren, sei es von einem Lagerhof oder einem Holzfäller." }
    { group:185, id:12, text: "Gelagertes Holz," }
    { group:187, id:0, text: "Unbekannt" }
    { group:187, id:1, text: "Lokale Gottheit" }
    { group:187, id:2, text: "Schutzgott" }
    { group:188, id:0, text: "Festplatz" }
    { group:188, id:1, text: "Wenn Ihr Eurem Tempelaufseher beauftragt, ein Fest zu Ehren einer der Götter zu veranstalten, versammeln sich die Bürger hier zur Teilnahme. " }
    { group:188, id:2, text: "Haltet ein Fest ab, um die Menschen glücklich zu machen und die Götter zu besänftigen" }
    { group:188, id:3, text: "Ein Fest findet derzeit statt" }
    { group:189, id:0, text: "Altar des Sobek" }
    { group:189, id:1, text: "Orakel des Min" }
    { group:189, id:2, text: "Altar der Ma'at" }
    { group:189, id:3, text: "Orakel des Horus" }
    { group:189, id:4, text: "Altar des Amun" }
    { group:189, id:5, text: "Orakel des Thot" }
    { group:189, id:6, text: "Altar des Anubis" }
    { group:189, id:7, text: "Orakel der Sachmet" }
    { group:189, id:8, text: "Altar der Isis" }
    { group:189, id:9, text: "Orakel der Hathor" }
    { group:190, id:0, text: "Papyruswerkstatt" }
    { group:190, id:1, text: "Hier werden Schilfpflanzen zusammengebunden, um Papyrus herzustellen, den Bildungseinrichtungen zum Niederschreiben von Informationen und Teilen von Wissen benötigen. Papyrus kann auch profitabel gehandelt werden." }
    { group:190, id:2, text: "Produktion ist" }
    { group:190, id:3, text: "abgeschlossen." }
    { group:190, id:4, text: "Euer Handelsaufseher verfügte, dass die Papyrusproduktion eingestellt werden sollte." }
    { group:190, id:5, text: "Diese Papyruswerkstatt hat keine Angestellten und wird dadurch keine Produkte liefern." }
    { group:190, id:6, text: "Diese Papyruswerkstatt ist voll besetzt und produziert reichlich hochwertigen Papyrus." }
    { group:190, id:7, text: "Diese Papyruswerkstatt könnte mehr Arbeiter gebrauchen, um ihr volles Potential für Papyrusproduktion zu erreichen." }
    { group:190, id:8, text: "Diese Papyruswerkstatt ist unterbesetzt und produziert Papyrus langsamer, als sie sollte." }
    { group:190, id:9, text: "Sehr wenige Menschen arbeiten in dieser Werkstatt. Die Papyrusproduktion ist dadurch langsam." }
    { group:190, id:10, text: "Mit kaum Angestellten wird diese Papyruswerkstatt wenig Papyrus im kommenden Jahr produzieren." }
    { group:190, id:11, text: "Diese Werkstatt wird keinen Papyrus ohne eine Schilflieferung produzieren, sei es von einem Lagerhof oder einem Schilfsammler." }
    { group:190, id:12, text: "Gelagertes Schilf," }
    { group:191, id:0, text: "Cheat-Dialog" }
    { group:191, id:1, text: "Cheats deaktivieren" }
    { group:192, id:0, text: "Granitsteinbruch" }
    { group:192, id:1, text: "Obelisken verwenden die schweren Blöcke aus robustem Granit, die Ihr aus den Knochen der Erde hier herausschlagt." }
    { group:192, id:2, text: "Produktion ist" }
    { group:192, id:3, text: "abgeschlossen." }
    { group:192, id:4, text: "Euer Handelsaufseher befahl, dass kein Granit mehr abgebaut werden sollte." }
    { group:192, id:5, text: "Dieser Steinbruch hat keine Arbeiter. Die Produktion ist eingestellt." }
    { group:192, id:6, text: "Dieser Steinbruch hat alle Arbeiter, die er braucht, und arbeitet auf Hochtouren, um Granit zu produzieren." }
    { group:192, id:7, text: "Dieser Steinbruch arbeitet unter maximaler Kapazität. Die Produktion könnte mit mehr Arbeitern etwas effizienter sein." }
    { group:192, id:8, text: "Dieser Steinbruch ist unterbesetzt. Es dauert länger, Granit zu produzieren, als es sollte." }
    { group:192, id:9, text: "Sehr wenige Menschen arbeiten hier. Der Steinbruch liefert sehr wenig Granit." }
    { group:192, id:10, text: "Mit kaum Arbeitern hier hat die Produktion fast gestoppt. Er wird wenig im kommenden Jahr produzieren." }
    { group:193, id:0, text: "Kupfermine" }
    { group:193, id:1, text: "Leicht zu bearbeiten und haltbar, Kupfer macht feine Waffen und einen wertvollen Export." }
    { group:193, id:2, text: "Produktion ist" }
    { group:193, id:3, text: "abgeschlossen." }
    { group:193, id:4, text: "Euer Handelsaufseher befahl einen Stopp des Kupferabbaus." }
    { group:193, id:5, text: "Diese Mine hat keine Arbeiter. Die Produktion ist eingestellt." }
    { group:193, id:6, text: "Diese Mine hat alle Arbeiter, die sie braucht, und produziert reichlich Kupfer." }
    { group:193, id:7, text: "Diese Mine arbeitet unter maximaler Kapazität. Die Produktion könnte mit mehr Arbeitern etwas effizienter sein." }
    { group:193, id:8, text: "Diese Mine ist unterbesetzt. Es dauert länger, Kupfer zu produzieren, als es sollte." }
    { group:193, id:9, text: "Sehr wenige Menschen arbeiten in diesem Gebäude. Die Produktion ist dadurch langsam." }
    { group:193, id:10, text: "Mit kaum Arbeitern hier hat die Produktion fast gestoppt. Sie wird wenig im kommenden Jahr produzieren." }
    { group:194, id:0, text: "Sandsteinsteinbruch" }
    { group:194, id:1, text: "Nur Sandstein hat die richtigen Eigenschaften für Mausoleen und Sonnentempel." }
    { group:194, id:2, text: "Produktion ist" }
    { group:194, id:3, text: "abgeschlossen." }
    { group:194, id:4, text: "Euer Handelsaufseher befahl, dass kein Sandstein mehr abgebaut werden sollte." }
    { group:194, id:5, text: "Dieser Steinbruch hat keine Arbeiter. Die Produktion ist eingestellt." }
    { group:194, id:6, text: "Dieser Steinbruch hat alle Arbeiter, die er braucht, und arbeitet auf Hochtouren, um Sandstein zu produzieren." }
    { group:194, id:7, text: "Dieser Steinbruch arbeitet unter maximaler Kapazität. Die Produktion könnte mit mehr Arbeitern etwas effizienter sein." }
    { group:194, id:8, text: "Dieser Steinbruch ist unterbesetzt. Es dauert länger, Sandstein zu produzieren, als es sollte." }
    { group:194, id:9, text: "Sehr wenige Menschen arbeiten in diesem Gebäude. Die Produktion ist extrem langsam dadurch." }
    { group:194, id:10, text: "Mit kaum Arbeitern hier hat die Produktion fast gestoppt. Er wird wenig im kommenden Jahr produzieren." }
    { group:195, id:0, text: "Abu" }
    { group:195, id:1, text: "Abedju" }
    { group:195, id:2, text: "Bahariya-Oase" }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubastis" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Byblos" }
    { group:195, id:8, text: "Dahschur" }
    { group:195, id:9, text: "Dachla-Oase" }
    { group:195, id:10, text: "Djedu" }
    { group:195, id:11, text: "Dunqul-Oase" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "Farafra-Oase" }
    { group:195, id:14, text: "Gaza" }
    { group:195, id:15, text: "Heh" }
    { group:195, id:16, text: "Henen-nesw" }
    { group:195, id:17, text: "Hetepsenusret" }
    { group:195, id:18, text: "Iken" }
    { group:195, id:19, text: "Itjtawy" }
    { group:195, id:20, text: "Iunet" }
    { group:195, id:21, text: "Jericho" }
    { group:195, id:22, text: "Kebet" }
    { group:195, id:23, text: "Kerma" }
    { group:195, id:24, text: "Charga-Oase" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knossos" }
    { group:195, id:27, text: "Kyrene" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mykene" }
    { group:195, id:32, text: "Nechen" }
    { group:195, id:33, text: "Nubt" }
    { group:195, id:34, text: "On" }
    { group:195, id:35, text: "Perwadjyt" }
    { group:195, id:36, text: "Punt" }
    { group:195, id:37, text: "Qadesch" }
    { group:195, id:38, text: "Rostja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Sakkara" }
    { group:195, id:41, text: "Sauty" }
    { group:195, id:42, text: "Sawu" }
    { group:195, id:43, text: "Selima-Oase" }
    { group:195, id:44, text: "Serabit Khadim" }
    { group:195, id:45, text: "Schaat" }
    { group:195, id:46, text: "Scharuhen" }
    { group:195, id:47, text: "Thinis" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toschka" }
    { group:195, id:50, text: "Tyrus" }
    { group:195, id:51, text: "Waset" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alexandria" }
    { group:195, id:54, text: "Sumur" }
    { group:195, id:55, text: "Deir el-Medina" }
    { group:195, id:56, text: "Abu Simbel" }
    { group:195, id:57, text: "Actium" }
    { group:195, id:58, text: "Rom" }
    { group:195, id:59, text: "Tanis" }
    { group:195, id:60, text: "Pi-Yer" }
    { group:195, id:61, text: "Siwa-Oase" }
    { group:195, id:62, text: "Maritis" }
    { group:195, id:63, text: "Piramesse" }
    { group:195, id:64, text: "Athen" }
    { group:195, id:65, text: "Kleoantinopolis" }
    { group:196, id:0, text: "KRETA" }
    { group:196, id:1, text: "ZYPERN" }
    { group:196, id:2, text: "OSTAFRIKA" }
    { group:196, id:3, text: "ÖSTLICHE WÜSTE" }
    { group:196, id:4, text: "GRIECHENLAND" }
    { group:196, id:5, text: "LIBYEN" }
    { group:196, id:6, text: "UNTERÄGYPTEN" }
    { group:196, id:7, text: "DELTA" }
    { group:196, id:8, text: "FAYUUM" }
    { group:196, id:9, text: "NUBIEN" }
    { group:196, id:10, text: "PALÄSTINA" }
    { group:196, id:11, text: "SINAI" }
    { group:196, id:12, text: "SYRIEN" }
    { group:196, id:13, text: "OBERÄGYPTEN" }
    { group:196, id:14, text: "WESTLICHE WÜSTE" }
    { group:196, id:15, text: "LIBANON" }
    { group:196, id:16, text: "KANAAN" }   
    { group:198, id:0, text: "Keine " }
    { group:198, id:1, text: "Kleine Knickpyramide" }
    { group:198, id:2, text: "Mittlere Knickpyramide" }
    { group:198, id:3, text: "Kleine Lehmziegelpyramide" }
    { group:198, id:4, text: "Mittlere Lehmziegelpyramide" }
    { group:198, id:5, text: "Große Lehmziegelpyramide" }
    { group:198, id:6, text: "Lehmziegelpyramiden-Komplex" }
    { group:198, id:7, text: "Prächtiger Lehmziegelpyramiden-Komplex" }
    { group:198, id:8, text: "Kleine Stufenpyramide" }
    { group:198, id:9, text: "Mittlere Stufenpyramide" }
    { group:198, id:10, text: "Große Stufenpyramide" }
    { group:198, id:11, text: "Stufenpyramiden-Komplex" }
    { group:198, id:12, text: "Prächtiger Stufenpyramiden-Komplex" }
    { group:198, id:13, text: "Kleine Pyramide" }
    { group:198, id:14, text: "Mittlere Pyramide" }
    { group:198, id:15, text: "Große Pyramide" }
    { group:198, id:16, text: "Pyramiden-Komplex" }
    { group:198, id:17, text: "Prächtiger Pyramiden-Komplex" }
    { group:198, id:18, text: "Kleine Mastaba" }
    { group:198, id:19, text: "Mittlere Mastaba" }
    { group:198, id:20, text: "Große Mastaba" }
    { group:198, id:21, text: "Sphinx" }
    { group:198, id:22, text: "Kleiner Obelisk" }
    { group:198, id:23, text: "Großer Obelisk" }
    { group:198, id:24, text: "Sonnentempel" }
    { group:198, id:25, text: "Mausoleum" }
    { group:198, id:26, text: "Mausoleum" }
    { group:198, id:27, text: "Mausoleum" }
    { group:198, id:28, text: "Pharos-Leuchtturm" }
    { group:198, id:29, text: "Bibliothek von Alexandria" }
    { group:198, id:30, text: "Caesareum" }
    { group:198, id:31, text: "Kolosse" }
    { group:198, id:32, text: "Tempel von Luxor" }
    { group:198, id:33, text: "Kleines königliches Grabmal" }
    { group:198, id:34, text: "Mittleres königliches Grabmal" }
    { group:198, id:35, text: "Großes königliches Grabmal" }
    { group:198, id:36, text: "Prächtiges königliches Grabmal" }
    { group:198, id:37, text: "Abu Simbel" }
    { group:199, id:0, text: "Monumentaufseher" }
    { group:199, id:1, text: "im Lager" }
    { group:199, id:2, text: "Fertig" }
    { group:199, id:3, text: "Klickt auf Grabbeigaben, um sie zu liefern." }
    { group:199, id:4, text: "Zu liefernde Menge" }
    { group:199, id:5, text: "Alle" }
    { group:199, id:6, text: "Klicken zum Entsenden" }
    { group:199, id:7, text: "Abbrechen" }
    { group:199, id:8, text: "Menge erhöhen" }
    { group:199, id:9, text: "Menge verringern" }
    { group:199, id:10, text: "Grabbeigaben entsenden" }
    { group:199, id:11, text: "Monumentbewertung" }
    { group:199, id:12, text: "Es müssen keine Grabbeigaben entsendet werden." }
    { group:199, id:13, text: "Besucht die Baustelle für weitere Details." }
    { group:199, id:14, text: "Die Arbeit an dieser Pyramide hat nicht begonnen. Ihr braucht Bauernarbeit, um " }
    { group:199, id:15, text: "dieses Projekt zu beginnen, und reichlich gewöhnlichen Stein und Kalkstein, um es fertigzustellen." }
    { group:199, id:16, text: "Diese Pyramide ist " }
    { group:199, id:17, text: "Diese Pyramide ist jetzt fertig! " }
    { group:199, id:18, text: "Diese Pyramide ist fertig. Sie wird für immer die heiligen Überreste beherbergen." }
    { group:199, id:19, text: "Die Arbeit an dieser Ziegelpyramide hat nicht begonnen. Ihr braucht Bauernarbeit, um " }
    { group:199, id:20, text: "dieses Projekt zu beginnen, und reichlich Ziegel und Kalkstein, um es fertigzustellen." }
    { group:199, id:21, text: "Diese Ziegelpyramide ist   " }
    { group:199, id:22, text: "Diese Ziegelpyramide ist jetzt fertig!" }
    { group:199, id:23, text: "Diese Pyramide ist fertig. Sie wird für immer die heiligen Überreste beherbergen." }
    { group:199, id:24, text: "Die Arbeit an dieser Stufenpyramide hat nicht begonnen. Ihr braucht Bauernarbeit," }
    { group:199, id:25, text: "um dieses Projekt zu beginnen, und reichlich gewöhnlichen Stein, um es fertigzustellen." }
    { group:199, id:26, text: "Diese Stufenpyramide ist " }
    { group:199, id:27, text: "Diese Stufenpyramide ist jetzt fertig!" }
    { group:199, id:28, text: "Diese Stufenpyramide ist fertig. Sie wird für immer die heiligen Überreste beherbergen." }
    { group:199, id:29, text: "Die Arbeit an dieser Knickpyramide hat nicht begonnen. Ihr braucht Bauernarbeit, um " }
    { group:199, id:30, text: "dieses Projekt zu beginnen, und reichlich gewöhnlichen Stein und Kalkstein, um es fertigzustellen." }
    { group:199, id:31, text: "Diese Knickpyramide ist" }
    { group:199, id:32, text: "Diese Knickpyramide ist jetzt fertig!" }
    { group:199, id:33, text: "Diese Knickpyramide ist fertig. Sie wird für immer die heiligen Überreste beherbergen." }
    { group:199, id:34, text: "Die Arbeit an dieser Mastaba hat noch nicht begonnen. Ihr braucht Bauernarbeit, um" }
    { group:199, id:35, text: "dieses Projekt zu beginnen, und eine gute Ziegelversorgung, um es fertigzustellen." }
    { group:199, id:36, text: "Diese Mastaba ist " }
    { group:199, id:37, text: "Diese Mastaba ist jetzt fertig!" }
    { group:199, id:38, text: "Diese Mastaba ist fertig und wird für immer die heiligen Überreste beherbergen." }
    { group:199, id:39, text: "Die Arbeit an dieser Sphinx hat noch nicht begonnen. Ihr braucht Zimmerer, Steinmetze, " }
    { group:199, id:40, text: "Holz und gewöhnlichen Stein, um dieses Projekt zu beginnen." }
    { group:199, id:41, text: "Diese Sphinx ist " }
    { group:199, id:42, text: "Diese Sphinx ist jetzt fertig!" }
    { group:199, id:43, text: "Die Arbeit an diesem Obelisken hat noch nicht begonnen. Ihr werdet " }
    { group:199, id:44, text: "Blöcke Granit brauchen, um dieses Projekt zu beginnen. Ihr habt " }
    { group:199, id:45, text: "Dieser Obelisk ist" }
    { group:199, id:46, text: "Dieser Obelisk ist jetzt fertig!" }
    { group:199, id:47, text: "Die Arbeit an diesem Sonnentempel hat noch nicht begonnen. Ihr werdet " }
    { group:199, id:48, text: "Blöcke Sandstein brauchen, um dieses Projekt zu beginnen. Ihr habt " }
    { group:199, id:49, text: "Dieser Sonnentempel ist" }
    { group:199, id:50, text: "Dieser Sonnentempel ist jetzt fertig!" }
    { group:199, id:51, text: "Die Arbeit an diesem Mausoleum hat noch nicht begonnen. Ihr werdet " }
    { group:199, id:52, text: "Blöcke Sandstein brauchen, um dieses Projekt zu beginnen. Ihr habt" }
    { group:199, id:53, text: "Dieses Mausoleum ist" }
    { group:199, id:54, text: "Dieses Mausoleum ist jetzt fertig!" }
    { group:199, id:55, text: "Dieses Mausoleum ist fertig und wird für immer die heiligen Überreste beherbergen. " }
    { group:199, id:56, text: "Klicken, um die Baustelle zu besuchen." }
    { group:199, id:57, text: "Block gelagert" }
    { group:199, id:58, text: "Blöcke gelagert" }
    { group:199, id:59, text: "Die Arbeit an Alexandrias Bibliothek hat nicht begonnen. Ihr werdet Bauernarbeit brauchen," }
    { group:199, id:60, text: "um dieses Projekt zu beginnen, und eine Versorgung mit Marmor und Kupfer, um es fertigzustellen." }
    { group:199, id:61, text: "Die Bibliothek von Alexandria ist" }
    { group:199, id:62, text: "Die Bibliothek von Alexandria ist jetzt fertig!" }
    { group:199, id:63, text: "Die Arbeit am Caesareum hat nicht begonnen. Ihr werdet Bauernarbeit brauchen, " }
    { group:199, id:64, text: "um dieses Projekt zu beginnen, und eine Versorgung mit Marmor und Granit, um es fertigzustellen." }
    { group:199, id:65, text: "Das Caesareum ist" }
    { group:199, id:66, text: "Das Caesareum ist jetzt fertig!" }
    { group:199, id:67, text: "Die Arbeit am Pharos-Leuchtturm hat nicht begonnen. Ihr werdet Bauern-" }
    { group:199, id:68, text: "arbeit brauchen, um dieses Projekt zu beginnen, und eine Marmorversorgung, um es fertigzustellen." }
    { group:199, id:69, text: "Der Pharos-Leuchtturm ist" }
    { group:199, id:70, text: "Der Pharos-Leuchtturm ist jetzt fertig!" }
    { group:199, id:71, text: "Die Arbeit an Abu Simbel hat nicht begonnen. Ihr werdet Zimmerer, Steinmetze " }
    { group:199, id:72, text: "und eine Holzversorgung brauchen, um dieses Projekt zu beginnen." }
    { group:199, id:73, text: "Abu Simbel ist" }
    { group:199, id:74, text: "Abu Simbel ist jetzt fertig!" }
    { group:199, id:75, text: "Die Arbeit am kleinen Grabmal hat nicht begonnen. Ihr werdet Steinmetze," }
    { group:199, id:76, text: "Handwerker, Ton, Farbe und Lampen brauchen, um dieses Projekt zu beginnen." }
    { group:199, id:77, text: "Das kleine königliche Grabmal ist" }
    { group:199, id:78, text: "Das kleine königliche Grabmal ist jetzt fertig!" }
    { group:199, id:79, text: "Die Arbeit am mittleren Grabmal hat nicht begonnen. Ihr werdet " }
    { group:199, id:80, text: "Steinmetze, Handwerker, Ton, Farbe und Lampen brauchen, um dieses Projekt zu beginnen." }
    { group:199, id:81, text: "Das mittlere königliche Grabmal ist" }
    { group:199, id:82, text: "Das mittlere königliche Grabmal ist jetzt fertig!" }
    { group:199, id:83, text: "Die Arbeit am großen Grabmal hat nicht begonnen. Ihr werdet Steinmetze," }
    { group:199, id:84, text: "Handwerker, Ton, Farbe und Lampen brauchen, um dieses Projekt zu beginnen." }
    { group:199, id:85, text: "Das große königliche Grabmal ist" }
    { group:199, id:86, text: "Das große königliche Grabmal ist jetzt fertig!" }
    { group:199, id:87, text: "Die Arbeit am prächtigen Grabmal hat nicht begonnen. Ihr werdet Steinmetze," }
    { group:199, id:88, text: "Handwerker, Ton, Farbe und Lampen brauchen, um dieses Projekt zu beginnen." }
    { group:199, id:89, text: "Das prächtige königliche Grabmal ist" }
    { group:199, id:90, text: "Das prächtige königliche Grabmal ist jetzt fertig!" }
    { group:200, id:0, text: "Phase Eins: Beschafft Granit, um die grobe Struktur zu platzieren" }
    { group:200, id:1, text: "Phase Zwei: Zimmerer verwenden Holz, um Gerüste zu bauen" }
    { group:200, id:2, text: "Phase Drei: Steinmetze schnitzen die endgültige Form, von oben nach unten arbeitend" }
    { group:200, id:3, text: "Status:" }
    { group:200, id:4, text: "Nicht begonnen" }
    { group:200, id:5, text: "Unvollständig" }
    { group:200, id:6, text: "Abgeschlossen" }
    { group:200, id:7, text: "Gesamtfortschritt:" }
    { group:201, id:0, text: "Generic1" }
    { group:201, id:1, text: "Generic2" }
    { group:201, id:2, text: "Generic3" }
    { group:201, id:3, text: "Generic4" }
    { group:201, id:4, text: "Generic5" }
    { group:201, id:5, text: "Generic6" }
    { group:201, id:6, text: "Generic7" }
    { group:201, id:7, text: "Generic8" }
    { group:201, id:8, text: "Generic9" }
    { group:201, id:9, text: "Generic10" }        
    { group:205, id:0, text: "Vielleicht wird ein Diebstahl aus seiner Schatzkammer die Aufmerksamkeit dieses falschen Bartes erlangen! // Karrensch ieber" }
    { group:205, id:1, text: "Ich nehme mir, was ich will! Versucht nicht, mich aufzuhalten!" }
    { group:205, id:2, text: "Diebstahl ist viel profitabler als andere Jobs in dieser Stadt!" }
    { group:205, id:3, text: "Nehmen, nehmen, nehmen. Das ist alles, was ich jemals tue." }
    { group:206, id:0, text: "Ohhh, mein Magen! Oh, mein Kopf! 											// Arbeitsuchender" }
    { group:207, id:0, text: "Eine Seuche könnte jederzeit ausbrechen! Ich hoffe, sie bleibt in den armen Teilen der Stadt!" }
    { group:207, id:1, text: "Dass eine Person meiner Qualität Hunger kennen könnte, ist skandalös!" }
    { group:207, id:2, text: "Ich glaube nicht, dass diese Stadt einen Angriff bewältigen könnte, und ich habe so sehr viel zu verlieren." }
    { group:207, id:3, text: "Wie können so wenige Arbeiter meine Bedürfnisse angemessen erfüllen?" }
    { group:207, id:4, text: "Ich werde weit besser behandelt als die Götter! Ich hoffe, sie schlagen nicht gegen uns zu." }
    { group:207, id:5, text: "Ich schäme mich, hier zu leben. Ich hoffe, unsere Feinde nutzen unseren Ruf nicht aus!" }
    { group:207, id:6, text: "Seht all diese Müßiggänger! Warum suchen sie sich keine Arbeit?" }
    { group:207, id:7, text: "Wie kann ich einen vornehmen Lebensstil führen, wenn ich nicht richtig unterhalten werde?" }
    { group:207, id:8, text: "Diese Stadt ist akzeptabel, nehme ich an." }
    { group:207, id:9, text: "Diese Stadt könnte nicht besser sein!" }
    { group:207, id:10, text: "Diese Feste wären so viel besser, wenn sie nur auf Einladung wären." }    
    { group:210, id:0, text: "Vögel sind listig. Sie werden wegfliegen, wenn Ihr ihnen nicht genau richtig nahekommt." }
    { group:210, id:1, text: "Seht diese schönen Vögel, bereit zum Braten!" }
    { group:211, id:0, text: "Ein weiterer perfekter Tag zum Fischen. Ich hoffe, der Fang ist so reichlich wie üblich." }
    { group:211, id:1, text: "Unser Laderaum quillt über, aber Ihr hättet den sehen sollen, der entkommen ist!" }
    { group:211, id:2, text: "Bewegt Euch schneller! Wir können nicht zurück zur Arbeit, bis Ihr uns entladen habt." }    
    { group:215, id:0, text: "Zum Sumpf marschiere ich für das Schilf, das wir brauchen." }
    { group:215, id:1, text: "Dieses Schilf wird feinen Papyrus ergeben." }
    { group:216, id:0, text: "Meine Dienste werden am Monument benötigt!" }
    { group:216, id:1, text: "Dieses Monument wäre sehr kurz ohne meine Rampen und Gerüste." }
    { group:217, id:0, text: "Es ist Zeit zum Ziegelverlegen am Monument!" }
    { group:217, id:1, text: "Mit meinen Ziegeln wird dieses Monument stark sein." }
    { group:218, id:0, text: "Ich gehe zum Monument, um die Steine zu formen." }
    { group:218, id:1, text: "Meine Steinarbeiten werden durch die Zeitalter überdauern." }
    { group:219, id:0, text: "So viele Menschen sind erkrankt. Ich hoffe, sie erholen sich bald, sonst könnte eine Seuche ausbrechen." }
    { group:219, id:1, text: "Ich verhungere. Die meisten meiner Kunden verlangen Essen, und ich kann mich selbst kaum ernähren." }
    { group:219, id:2, text: "Unsere Verteidigungen sind dürftig. Wir könnten leicht überfallen werden." }
    { group:219, id:3, text: "Ich sollte besser extra nett zu meinen Helfern sein. Mit so vielen offenen Stellen in der Stadt könnte ich sie leicht verlieren." }
    { group:219, id:4, text: "Wenn wir den Göttern nicht bald mehr Respekt zollen, werden sie eine elende Strafe austeilen." }
    { group:219, id:5, text: "Ich würde nicht im Traum daran denken, meinen Ruf so weit abrutschen zu lassen wie der dieser Stadt. Wir könnten bald den Preis zahlen." }
    { group:219, id:6, text: "Ich habe Glück, einen Job zu haben. Ich kenne viele Leute, die arbeitslos sind." }
    { group:219, id:7, text: "Hier passiert überhaupt nichts. Ich wünschte, es gäbe mehr Shows zu sehen. " }
    { group:219, id:8, text: "Ich werde mich über diese Stadt nicht beschweren... aber ich könnte." }
    { group:219, id:9, text: "Diese Stadt ist spitze!" }
    { group:219, id:10, text: "Der Basar braucht einige Waren, und ich werde sie besorgen." }
    { group:219, id:11, text: "Diese Waren werden willkommene Ergänzungen für den Basar sein." }
    { group:222, id:0, text: "Ich nehme diese Lieferungen nicht weiter mit, bis jemand verfügbar ist, sie zu entladen." }
    { group:222, id:1, text: "Niemand kann diese Waren annehmen! Das ist okay, ich kann die Rast gebrauchen." }
    { group:222, id:2, text: "Ich muss quer durch die ganze Stadt mit diesen Waren. Es wird den ganzen Tag dauern!" }
    { group:223, id:0, text: "Wir tun mehr als unseren Anteil an Arbeit. Wir brauchen mehr Hilfe." }
    { group:223, id:1, text: "Ich werde hier warten, bis etwas Platz für dieses Zeug frei wird." }
    { group:223, id:2, text: "Bin ich schon da? Ich kann diese Waren nicht viel weiter schleppen." }   
    { group:226, id:0, text: "Ich habe noch nie so viele kranke Menschen gesehen. Ich hoffe, es bricht keine Seuche aus." }
    { group:226, id:1, text: "Es ist schwer, diese Keulen zu fangen, wenn man sich vor Hungerqualen krümmt." }
    { group:226, id:2, text: "Vielleicht kann ich diese Keulen auf den Feind werfen, sollte er angreifen. Wenig anderes verteidigt diese Stadt." }
    { group:226, id:3, text: "Ich sehe überall freie Stellen! Ich frage mich, ob ich mehr als einen Job jonglieren könnte." }
    { group:226, id:4, text: "Ich erwarte das Schlimmste. Die Götter müssen denken, wir hätten sie vergessen." }
    { group:226, id:5, text: "Diese Stadt hat einen schlechteren Ruf als ich. Ich hoffe, niemand greift uns an." }
    { group:226, id:6, text: "Ich wünschte, es gäbe mehr Jobs in dieser Stadt. Keiner der Leute, die ich unterhalte, kann mich bezahlen." }
    { group:226, id:7, text: "Ich kann nur so viel jonglieren. Ich wünschte, es gäbe andere Unterhalter in der Stadt." }
    { group:226, id:8, text: "Diese Stadt ist nicht zu schlecht.  " }
    { group:226, id:9, text: "Es gibt keinen Ort, an dem ich lieber jonglieren würde." }
    { group:226, id:10, text: "Ich liebe es, diese Festmenschenmengen zu bespielen. Alle sind so glücklich!" }
    { group:227, id:10, text: "Diese Feste sind großartig! Alle singen mit." }    
    { group:229, id:0, text: "Die Gesundheit der Menschen ist in Gefahr. Das Risiko einer Seuche ist groß." }
    { group:229, id:1, text: "Ich bin hungrig wie ein Nilpferd, aber es gibt wenig Essen zu finden." }
    { group:229, id:2, text: "Ich sollte die Kriegskunst lernen. Mit unseren so schwachen Verteidigungen sind wir in Gefahr." }
    { group:229, id:3, text: "Der Arbeitermangel könnte echte Probleme in der Stadt verursachen." }
    { group:229, id:4, text: "Um die Wahrheit zu sagen, würde ich es nicht wagen, die Götter so schlecht zu behandeln." }
    { group:229, id:5, text: "Der Ruf dieser Stadt ist bestenfalls durchwachsen. Wir könnten angegriffen werden." }
    { group:229, id:6, text: "Für die meisten ist die Jobsuche in dieser Stadt eine triviale Beschäftigung, die im Scheitern endet." }
    { group:229, id:7, text: "Diese Stadt sollte den Mangel an Unterhaltung begreifen!" }
    { group:229, id:8, text: "Es tut mir nicht leid, hier zu leben." }
    { group:229, id:9, text: "Diese Stadt hat ein Monopol auf mein Herz. Ich liebe es hier!" }
    { group:229, id:10, text: "Holt Euer Bier hier! Warmes, abgestandenes, erfrischendes Bier! Wenig Bodensatz!" }    
    { group:235, id:0, text: "Die Stadt könnte bald lernen, dass schlechte Gesundheit zu einer schrecklichen Seuche führen kann." }
    { group:235, id:1, text: "Mein Geist wird mit Wissen genährt, aber mein Körper hungert nach Nahrung." }
    { group:235, id:2, text: "Invasoren hätten keine Probleme, unsere spärlichen Verteidigungen zu durchbrechen!" }
    { group:235, id:3, text: "Die Knappheit an Arbeitern hallt durch die ganze Stadt und begrenzt ihre Dienste." }
    { group:235, id:4, text: "Die sakrilegischen Wege der Stadt könnten die Götter veranlassen, uns zu schlagen!" }
    { group:235, id:5, text: "Ach, Ruf, Ruf. Unser skandalöser Ruf lädt zum Angriff ein." }
    { group:235, id:6, text: "Selbst Bildung wird das Arbeitslosenproblem dieser Stadt nicht heilen." }
    { group:235, id:7, text: "Langweilig, öde, ermüdend, monoton, gähn. Diese Stadt ist alles fünf." }
    { group:235, id:8, text: "Diese Stadt ist durch und durch durchschnittlich." }
    { group:235, id:9, text: "Diese Stadt verdient Bestnoten!" }
    { group:235, id:10, text: "Man kann viel über die menschliche Natur bei einem Fest lernen." }
    { group:240, id:0, text: "Nach der Anzahl kranker Menschen in dieser Stadt zu urteilen, könnte ich bald alle Hände voll zu tun haben!" }
    { group:240, id:1, text: "Ich bin ausgehungert. Bald werde ich dünner sein als eine Mumie!" }
    { group:240, id:2, text: "Die Stadt ist nicht sicher in Verteidigungen eingewickelt. Ein Feind könnte uns leicht besiegen." }
    { group:240, id:3, text: "Wenn ich jemals das Einbalsamieren hinter mir lassen wollte, jetzt ist meine Chance. So viele freie Stellen!" }
    { group:240, id:4, text: "Die Götter könnten bald unsere Stadt aufrollen, wenn wir ihnen nicht mehr Respekt zollen." }
    { group:240, id:5, text: "Der schlechte Ruf der Stadt könnte unser aller Tod sein. Wir könnten jeden Moment angegriffen werden." }
    { group:240, id:6, text: "Wenn ich so viele Menschen ohne Arbeit sehe, macht mich das froh, dass ich einen Job habe." }
    { group:240, id:7, text: "Diese Stadt ist so tot wie die Körper, mit denen ich den ganzen Tag arbeite. Ich wünschte, die Stadt wäre lebendig mit Unterhaltung." }
    { group:240, id:8, text: "Ich könnte genauso gut hier leben. Es ist ungefähr so gut wie überall sonst." }
    { group:240, id:9, text: "Ich fühle wahres Mitleid mit meinen Klienten. Sie sind nicht da, um diese unglaubliche Stadt zu genießen!" }
    { group:240, id:10, text: "Die Gesundheit scheint sich in der ganzen Stadt zu verschlechtern." }             
    { group:247, id:0, text: "Meine Mal- und Putzkünste werden am Monument benötigt!" }
    { group:247, id:1, text: "Ich halte die Geschichten Ägyptens an den Wänden der königlichen Gräber fest." }
    { group:248, id:0, text: "Gold sollte für die Lebenden sein, nicht für die Toten!" }
    { group:248, id:1, text: "Denkt nur an das Vermögen, das ich haben werde, wenn ich all diese Schätze verkaufe!" }
    { group:249, id:0, text: "Wir werden bis zum Tod kämpfen, um unsere schöne Stadt zu verteidigen!" }
    { group:249, id:1, text: "Der Feind ist zu viel für uns! Wenn wir ihnen entkommen, werden wir bereit sein, einen anderen Tag zu kämpfen." }
    { group:249, id:2, text: "Feinde kommen in diese Richtung!" }
    { group:249, id:3, text: "Wir sind so gefährlich wie ein Krokodil, bereit, unsere Invasoren anzugreifen, wenn sie ankommen." }
    { group:249, id:4, text: "Wenn und wann unsere Feinde kommen, werden wir für sie bereit sein." }
    { group:250, id:0, text: "Rudert härter! Wir müssen unser Schiff um jeden Preis schützen!" }
    { group:250, id:1, text: "Der Feind ist hier! Alle Mann bereitmachen für Manöver." }
    { group:250, id:2, text: "Nur her mit dem Angriff! Wir sind vorbereitet." }
    { group:250, id:3, text: "Wir sind bereit zu dienen, wenn der Bedarf entsteht." }
    { group:251, id:0, text: "Streitwagen Exakt 1" }
    { group:252, id:0, text: "Keine Feinde wurden gesichtet, aber wir sind trotzdem bereit." }
    { group:252, id:1, text: "Wir sind aufgerollt wie eine Kobra, begierig, den nahenden Feind zu schlagen." }
    { group:252, id:2, text: "Ihr nennt das eine Armee?! Wir werden keine Probleme haben, diese zusammengewürfelte Truppe zu besiegen." }
    { group:252, id:3, text: "Dieser Feind ist wild! Ich tue alles, was ich kann, um sie zu besiegen." }
    { group:253, id:0, text: "Sonnentempel" }
    { group:253, id:1, text: "Phase 1" }
    { group:253, id:2, text: "Der grobe Obelisk wurde platziert " }
    { group:253, id:3, text: "und Arbeiter räumen den Platz" }
    { group:253, id:4, text: "Phase 2" }
    { group:253, id:5, text: "Zimmerer stellen Gerüste um " }
    { group:253, id:6, text: "den Obelisken auf" }
    { group:253, id:7, text: "Phase 3" }
    { group:253, id:8, text: "Steinmetze schnitzen die endgültige Form " }
    { group:253, id:9, text: "des Obelisken" }
    { group:253, id:10, text: "Phase 4" }
    { group:253, id:11, text: "Das Vestibül, die Mauer, der Platz und " }
    { group:253, id:12, text: "der Vortempel werden gebaut" }
    { group:253, id:13, text: "Ein einsamer Steinmetz wartet auf Stein." }
    { group:253, id:14, text: "Steinmetze warten auf Stein." }
    { group:253, id:15, text: "Der Sonnentempel ist" }
    { group:253, id:16, text: "Prozent fertig" }
    { group:253, id:17, text: "Blöcke Stein werden benötigt, um " }
    { group:253, id:18, text: "den Bau des Sonnentempels zu beenden." }
    { group:291, id:0, text: "Mausoleum" }
    { group:291, id:1, text: "Phase 1" }
    { group:291, id:2, text: "Das Fundament wurde gelegt" }
    { group:291, id:3, text: "und Arbeiter räumen den Platz" }
    { group:291, id:4, text: "Phase 2" }
    { group:291, id:5, text: "Maurer bauen den unteren Teil" }
    { group:291, id:6, text: "des Mausoleums" }
    { group:291, id:7, text: "Phase 3" }
    { group:291, id:8, text: "Steinmetze bauen den oberen" }
    { group:291, id:9, text: "Teil des Mausoleums" }
    { group:291, id:10, text: "Ein einsamer Steinmetz wartet auf Stein" }
    { group:291, id:11, text: "Steinmetze warten auf Stein" }
    { group:291, id:12, text: "Das Mausoleum ist" }
    { group:291, id:13, text: "Prozent fertig" }
    { group:291, id:14, text: "Blöcke Stein werden benötigt, um" }
    { group:291, id:15, text: "den Bau des Mausoleums zu beenden" }
    { group:292, id:0, text: "Familie erstellen" }
    { group:292, id:1, text: "Familie löschen" }
    { group:292, id:2, text: "Fortfahren" }
    { group:292, id:3, text: "Familienregister" }
    { group:292, id:4, text: "Zum Hauptmenü zurückkehren" }
    { group:293, id:0, text: "Familiengeschichte fortsetzen" }
    { group:293, id:1, text: "Eine Mission wählen" }
    { group:293, id:2, text: "Gespeichertes Spiel laden" }
    { group:293, id:3, text: "Benutzerdefinierte Missionen" }
    { group:293, id:4, text: "Zum Familienregister zurückkehren" }
    { group:293, id:5, text: "[player_name]-Familie" }
    { group:293, id:6, text: "Geschichte erkunden" }
    { group:293, id:7, text: "Familiengeschichte beginnen" }
    { group:294, id:0, text: "Prädynastische Zeit" }
    { group:294, id:1, text: "Während der prädynastischen Zeit machen die Clans, die schließlich Ägypten regieren werden, ihre ersten wackligen Schritte auf dem Weg zur Zivilisation. " }
    { group:294, id:2, text: "Eure Familie beginnt die prädynastische Zeit mit der Führung einer kleinen Nomadenschar durch ihre Entdeckung der Künste der Zivilisation. Eure Führung hilft, Ägypten auf seinen Kurs zur endgültigen Größe zu bringen, die noch nur schwach erblickt wird.  " }
    { group:294, id:3, text: "Die prädynastische Zeit ist die Morgendämmerung der ägyptischen Geschichte und der Eurer Familie.  " }
    { group:294, id:4, text: "Archaische Zeit" }
    { group:294, id:5, text: "Allmählich verschmelzen die während der prädynastischen Zeit gegründeten Dörfer zu einem vereinten Königreich mit einer großartigen Hauptstadt und ihren ersten monumentalen Gräbern. " }
    { group:294, id:6, text: "Während der archaischen Zeit vereinen sich die Dörfer, die in der prädynastischen Zeit entstanden, allmählich zum großen Königreich Ägypten. Die junge Zivilisation gründet eine Hauptstadt, sichert ihre Grenzen, meistert die Gewässer und baut ihre ersten monumentalen Gräber.  " }
    { group:294, id:7, text: "Eure Familiengeschichte muss der Reihe nach gelebt werden! Leider könnt Ihr die archaische Zeit nicht regieren, bis Ihr zuerst die in der prädynastischen Zeit entdeckten Künste erlernt habt." }
    { group:294, id:8, text: "Altes Reich" }
    { group:294, id:9, text: "Ägypten tritt in ein goldenes Zeitalter von Reichtum, Macht und Ruhm ein und errichtet erstaunliche neue Monumente in der ganzen Welt. Doch nachdem es diese schwindelerregenden Höhen erreicht hat, fiel Ägypten in Krieg. " }
    { group:294, id:10, text: "Ägypten steigt zu beispielloser Macht, Reichtum und Ruhm während des Alten Reiches. Doch selbst als unglaubliche neue Monumente im ganzen Niltal aufsteigen, machen Seher beunruhigende Vorhersagen über das Schicksal der Zwei Länder.  " }
    { group:294, id:11, text: "Ihr könnt nicht vorspringen, während Ihr Eure Familiengeschichte schmiedet. Bevor Ihr ins Alte Reich eintreten könnt, müsst Ihr zuerst die archaische Zeit abschließen." }
    { group:294, id:12, text: "Mittleres Reich" }
    { group:294, id:13, text: "Aus seiner schmerzvollen Entstehung erweist sich das Mittlere Reich als eine Zeit großer Gelegenheit für den Aufstieg Eurer Familie in der Welt." }
    { group:294, id:14, text: "Das Mittlere Reich, in Zwietracht geboren, erweist sich als eine Zeit großer Gelegenheit für Eure Familie. Mit Eurer Führung gewinnt Ägypten seinen früheren Glanz zurück...und mehr.  " }
    { group:294, id:15, text: "Die Familiengeschichte muss sich der Reihe nach entfalten. Das Mittlere Reich kann nicht beginnen, bis das Alte Reich endet!" }
    { group:294, id:16, text: "Neues Reich" }
    { group:294, id:17, text: "Ein wilder neuer Feind, der eine geniale und unaufhaltsame neue Waffe benutzt, fegt das Mittlere Reich hinweg. Aus dieser Zerstörung wird Ägypten erneut wiedergeboren." }
    { group:294, id:18, text: "Seltsame neue Feinde mit einer furchterregenden Superwaffe bringen das Mittlere Reich zu seinem Ende und bereiten den Weg für das großartige folgende Neue Reich. " }
    { group:294, id:19, text: "Ihr könnt nicht vom Pfad Eurer Familiengeschichte abweichen! Eure Familie kann das Neue Reich nicht erleben, bis Ihr die vorherigen Perioden abschließt." }
    { group:294, id:20, text: "Tal der Könige" }
    { group:294, id:21, text: "Die Entwicklung einer neuen Nekropole im Tal der Könige bot eine neue Möglichkeit, die Pharaonen auf ihre Reisen ins Jenseits vorzubereiten." }
    { group:294, id:22, text: "So großartig sie sind, die Pyramiden Eurer Vorfahren sind über die Jahrhunderte erodiert, die Gräber darin wurden geschändet, und die verborgenen Schätze von Räubern geplündert, die die Götter sicherlich für alle Ewigkeit bestrafen werden! Ihr werdet auf Pyramiden verzichten und eine neue Nekropole in einem schwer erreichbaren Wadi gegenüber von Theben beginnen, Gräber in die Klippen graben, um ein Tal der Könige zu schaffen, sicher vor Räubern. Oder ist es das?" }
    { group:294, id:23, text: "Es gibt eine richtige Zeit für alles in Eurer Familiengeschichte. Ihr könnt die großartigen Gräber des Tals der Könige nicht bauen, bis Ihr die Pracht des Neuen Reiches vollendet habt." }
    { group:294, id:24, text: "Ramses II." }
    { group:294, id:25, text: "Ramses II. erringt Ägyptens größten Sieg und gedenkt seiner Größe mit atemberaubenden Monumenten." }
    { group:294, id:26, text: "Ramses II. ist der dritte in einer dynastischen Linie, die von seinem Großvater Ramses I. begonnen wurde, einem Wesir nicht-königlichen Blutes, der den Thron beanspruchte, als Haremhab keinen Nachkommen hinterließ. Ihr müsst militärische Triumphe erreichen und große Monumente errichten, die Eure Untertanen von Eurem gottähnlichen Status überzeugen, Eure Feinde mit Verzweiflung erfüllen und Ramses des Großen Namen und den Ruhm Ägyptens für kommende Generationen verkünden." }
    { group:294, id:27, text: "Die Familiengeschichte muss der Reihe nach abgeschlossen werden. Ihr könnt nicht als Ramses II. regieren, bis Ihr die herrlichen Gräber im Tal der Könige gebaut habt." }
    { group:294, id:28, text: "Antike Eroberer" }
    { group:294, id:29, text: "Mächtige Krieger aus fernen Ländern stürmen herein, um zu versuchen, Dominanz über die Reichtümer Ägyptens auszuüben. Nachdem Ihr diese Bedrohungen abgewehrt und den Ruhm Alexanders willkommen geheißen habt, könnt Ihr zum Bereich 'Eine Mission wählen' gehen, um die gesamte Kampagne oder einzelne Missionen zu wiederholen." }
    { group:294, id:30, text: "Ägypten hat viele neidische Nachbarn, und sie betrachten unser reiches Imperium so, wie ein Hyänenrudel um die Beute eines Löwen drängt. Könnt Ihr die Armeen und Flotten bauen und befehligen, die notwendig sind, um diese ernsten Bedrohungen zu besiegen und das Nildelta gegen aufeinanderfolgende Invasionen durch die Seevölker, Assyrer und Perser zu verteidigen? Ägypten blickt auf Euch für Schutz!" }
    { group:294, id:31, text: "Dies jetzt zu spielen würde eine Lücke in Eurer Familiengeschichte schaffen. Ihr könnt die antiken Eroberer nicht überwinden, bis Ihr als Ramses II. gelebt habt." }
    { group:294, id:32, text: "Kleopatras Hauptstadt" }
    { group:294, id:33, text: "Die Ptolemäer aus Griechenland stellen den Ruhm dem Land der Pharaonen wieder her und wehren die Bedrohung aus Rom ab." }
    { group:294, id:34, text: "Alexander der Große selbst hat den zukünftigen Standort von Alexandria abgeschritten - die Hafenstadt am Mittelmeer, die Ihr nun bauen müsst. Unter der 300-jährigen Herrschaft der Ptolemäer, die mit Kleopatra VII. endet, wird Alexandria zur größten Stadt der Welt werden, Rom an Bevölkerung und Reichtum übertreffend. Alexanders Mausoleum, die Große Bibliothek, der Pharos-Leuchtturm und das Caesareum sind die Projekte Eurer Stadt. Aber was ist mit Roms mächtigen Legionen? Werden sie für oder gegen Kleopatras Ägypten eingesetzt?" }
    { group:294, id:35, text: "Eure Familiengeschichte kann das Leben Kleopatras nicht ihren Annalen hinzufügen, bis Ihr die antiken Eroberer besiegt habt." }
    { group:294, id:36, text: "Beginnen" }
    { group:294, id:37, text: "Spielen" }
    { group:294, id:38, text: "Einzelne Missionen" }
    { group:294, id:39, text: "Kampagnen" }
    { group:294, id:40, text: "Ihr könnt Missionen nur wiederholen, nachdem Ihr sie erfolgreich abgeschlossen habt." }
    { group:294, id:41, text: "Pharao" }
    { group:294, id:42, text: "Kleopatra" }
    { group:295, id:0, text: "Dieses Fest hat alle in so gute Stimmung versetzt, die Stadt sollte bald ein weiteres abhalten." }
    { group:295, id:1, text: "Es sind ein paar Monate seit dem letzten Fest vergangen. Dies wäre eine gute Zeit für ein weiteres." }
    { group:295, id:2, text: "Es gab schon seit geraumer Zeit keine Feste, und die Leute beginnen sich zu beschweren." }
    { group:295, id:3, text: "Es ist mehr als ein Jahr seit dem letzten Fest vergangen. Die Leute fühlen sich gelangweilt und überarbeitet." }
    { group:295, id:4, text: "Es ist fast zwei Jahre seit dem letzten Fest vergangen. Die Leute brauchen dringend eine Pause." }
    { group:295, id:5, text: "Mehr als zwei Jahre sind ohne Feste vergangen! Die Leute beginnen hoffnungslos zu werden." }
    { group:295, id:6, text: "Die Leute reden wehmütig von 'den guten alten Zeiten', als Feste die Monotonie erleichterten." }
    { group:295, id:7, text: "Das war so ein wunderbares Fest! Es braucht viel Zeit, eine solche Gala vorzubereiten." }
    { group:295, id:8, text: "Feste brauchen so viel Zeit und Mühe zur Vorbereitung, dass es klug wäre, jetzt eines anzuordnen." }
    { group:295, id:9, text: "Das letzte Fest ist lange genug her, dass es gerade an der Zeit ist, ein weiteres anzuordnen." }
    { group:295, id:10, text: "Das einfache Fest ist fast fertig. Die Leute reden alle über den Feiertag nächsten Monat." }
    { group:295, id:11, text: "Das einfache Fest wird vorbereitet. Nur noch zwei Monate bis alle einen Feiertag bekommen!" }
    { group:295, id:12, text: "Die Vorbereitungen für das in drei Monaten stattfindende einfache Fest beginnen nächsten Monat." }
    { group:295, id:13, text: "Festorganisatoren festigen die Pläne für das in vier Monaten kommende einfache Fest." }
    { group:295, id:14, text: "Das einfache Fest wird in fünf Monaten stattfinden. Organisatoren prüfen Vorschläge." }
    { group:295, id:15, text: "Planer sind zuversichtlich, dass sie in sechs weiteren Monaten für ein einfaches Fest bereit sein werden." }
    { group:295, id:16, text: "Gehetzte Organisatoren versprechen, dass Euer einfaches Fest in sieben Monaten abgehalten wird." }
    { group:295, id:17, text: "Das einfache Fest wird erst in acht Monaten stattfinden. Die Planung hat kaum begonnen." }
    { group:295, id:18, text: "Festorganisatoren sind so beschäftigt, dass Euer angefragtes einfaches Fest neun Monate entfernt ist." }
    { group:295, id:19, text: "Schon wieder eines? Es wird zehn Monate dauern, bis Organisatoren ein einfaches Fest abhalten können." }
    { group:295, id:20, text: "Das üppige Fest ist fast fertig. Die Leute sind aufgeregt über die Feier nächsten Monat!" }
    { group:295, id:21, text: "Das üppige Fest wird vorbereitet, und wir haben nur noch zwei Monate zur Vorbereitung." }
    { group:295, id:22, text: "Das üppige Fest wird vorbereitet. In drei Monaten werden wir eine denkwürdige Feier haben." }
    { group:295, id:23, text: "Planer sind auf Kurs, und das üppige Fest wird sicherlich in vier Monaten stattfinden." }
    { group:295, id:24, text: "Unterhalter polieren ihre Acts für das in fünf Monaten stattfindende üppige Fest." }
    { group:295, id:25, text: "Planer bestätigen, dass das neue üppige Fest wie versprochen in sechs Monaten stattfinden wird." }
    { group:295, id:26, text: "Organisatoren wägen öffentliche Vorschläge für das in sieben Monaten kommende üppige Fest ab." }
    { group:295, id:27, text: "Einige Unterhalter arbeiten neue Routinen für das üppige Fest in acht Monaten aus." }
    { group:295, id:28, text: "Mit so viel verbleibender Planung wird das üppige Fest erst in neun Monaten stattfinden." }
    { group:295, id:29, text: "Da niemand sich ihm noch widmen kann, wird das üppige Fest in zehn Monaten stattfinden." }
    { group:295, id:30, text: "Planer sind so beschäftigt, dass sie das neue üppige Fest elf Monate voraus planen müssen." }
    { group:295, id:31, text: "Das prächtige Fest ist fast fertig. In einem weiteren Monat gibt es frisches Bier für alle." }
    { group:295, id:32, text: "Die Vorbereitung des prächtigen Festes hat noch zwei Monate. Die Vorfreude ist unerträglich!" }
    { group:295, id:33, text: "Das prächtige Fest wird vorbereitet. Die Leute haben nur noch drei Monate, um Pläne zu machen." }
    { group:295, id:34, text: "Das prächtige Fest wird vorbereitet. Niemand will die vier Monate warten, die Planer brauchen!" }
    { group:295, id:35, text: "Organisatoren können nächsten Monat mit den Vorbereitungen beginnen, was ein prächtiges Fest in fünf Monaten ermöglicht." }
    { group:295, id:36, text: "Jongleure werden beim prächtigen Fest, nur sechs Monate entfernt, echte Überraschungen enthüllen." }
    { group:295, id:37, text: "Musiker schreiben alle neue Lieder für das prächtige Fest, jetzt nur noch sieben Monate entfernt." }
    { group:295, id:38, text: "Tänzer sind beim Proben gewagter neuer Bewegungen für das prächtige Fest in acht Monaten zu sehen." }
    { group:295, id:39, text: "Planer haben genug Ideen und Energie gesammelt, um ein prächtiges Fest in neun Monaten zu veranstalten." }
    { group:295, id:40, text: "Festorganisatoren machen Überstunden, um das neue prächtige Fest in zehn Monaten vorzubereiten." }
    { group:295, id:41, text: "Planer sind zuversichtlich, dass sie ein prächtiges Fest in elf Monaten angemessen veranstalten können." }
    { group:295, id:42, text: "Organisatoren sind so überarbeitet, dass das von Euch bestellte prächtige Fest in einem Jahr stattfinden wird." }
    { group:296, id:0, text: "Ewige Häuser Ägyptens" }
    { group:296, id:1, text: "Mission" }
    { group:296, id:2, text: "Beste Familie" }
    { group:296, id:3, text: "Schwierigkeitsgrad" }
    { group:296, id:4, text: "Punktzahl" }
    { group:296, id:5, text: "Haus" }
    { group:296, id:6, text: "Es gibt keine Höchstpunktzahlen." }
    { group:297, id:0, text: "Euer frühester aufgezeichneter Vorfahre gelangte zu Prominenz und erlernte die Grundlagen der Führung." }
    { group:297, id:1, text: "Nachdem Eure Familie nach Thinis umgesiedelt wurde, half Euer Vorfahr der Thinnitischen Konföderation, Ober- und Unterägypten zu vereinen." }
    { group:297, id:2, text: "Familienmythen besagen, dass Euer Clan wichtige neue Technologien entdeckte und lernte, die Nilschwemme auszunutzen. " }
    { group:297, id:3, text: "Eure Familie trat erstmals in die offiziellen ägyptischen Geschichtsbücher ein, als Narmer einen Vorfahren zur Position des königlichen Architekten ernannte." }
    { group:297, id:4, text: "Eure Familie hatte eine wichtige Rolle bei der Gründung von Ägyptens erster Hauptstadt und dem Bau der dortigen Mastaba. " }
    { group:297, id:5, text: "Der Legende nach eröffnete Eure Familie die Kupferminen in Timna, die sich als Schlüssel zu Pharao Dens Erfolg erwiesen, die Beduinen in Schach zu halten." }
    { group:297, id:6, text: "Zum ersten Mal wählte einer Eurer Vorfahren die Gewässer über trockenes Land und erlernte alle maritimen Fähigkeiten - einschließlich Kriegsführung." }
    { group:297, id:7, text: "Zum ersten Mal wählte einer Eurer Vorfahren die Gewässer über trockenes Land und erlernte die maritimen Fähigkeiten der Friedenszeit." }
    { group:297, id:8, text: "Euer Volk errichtete einen wichtigen militärischen Außenposten weit von der Zivilisation entfernt und eröffnete Handelsrouten nach Afrika, die bis heute Bestand haben. " }
    { group:297, id:9, text: "Auf Wunsch von Pharao Nebka erntete Eure Familie den Mineralreichtum des Ersten Katarakts, ohne den viele Gräber nicht hätten entstehen können und viele Adlige das Schilffeld verwehrt geblieben wäre." }
    { group:297, id:10, text: "Euer Vorfahr erreichte stolz die Vision des Wesirs Imhotep und baute Ägyptens erste Steinpyramide, um Djosers Mumie zu beherbergen.  " }
    { group:297, id:11, text: "Euer heroischer Vorfahr rang wertvolle Edelsteine und Kupfer aus dem feindseligen Sinai und seinen wilden Bewohnern, die ihr Äußerstes taten, um die Bemühung zu vereiteln. " }
    { group:297, id:12, text: "Das sich verbessernde Schicksal Eures Clans wird durch das Familiengrab in Meidum bezeugt, das bis heute als Zeugnis der Wichtigkeit der Blutlinie für Ägypten steht. " }
    { group:297, id:13, text: "Die in Buhen errichtete Festung und die Endgültigkeit, mit der Eure Verwandten den dortigen Feind zerschlugen, projizierte ägyptische Macht zum Zweiten Katarakt, in die von den feindseligen Nubiern beanspruchten Länder.  " }
    { group:297, id:14, text: "Während andere sich damit beschäftigten, die Grenzen des Königreichs zu erweitern, baute Euer Vorfahr das großartigste je erdachte Grab - Snofrus Knickpyramide." }
    { group:297, id:15, text: "Noch während Snofru einen Erben willkommen hieß, den königliche Seher als Tyrannen brandmarkten, vollendeten Eure eigenen Vorfahren die erste perfekte Pyramide der Welt, um Pharaos Überreste zu beherbergen. " }
    { group:297, id:16, text: "Trotz Khufus aufkommender Tyrannei diente Euer Vorfahr ihm loyal als königlicher Gouverneur und verteidigte Ägyptens Grenzen vor den kuschitischen Invasoren. " }
    { group:297, id:17, text: "Geschützt vor der kuschitischen Bedrohung, eröffnete Euer Erzeuger produktive Steinbrüche in Tura, um Khufus unerklärliche Nachfrage nach scheinbar grenzenlosen Mengen Kalkstein zu befriedigen.  " }
    { group:297, id:18, text: "Euer Vorfahr stieg zum Nomarchen für Khufu und Chephren auf und errichtete durch eine Willenskraft, die Pharaos eigener ebenbürtig war, die ewige Große Pyramide und ihre Wächtersphinx.  " }
    { group:297, id:19, text: "Pharao erklärte Ra zum Höchsten unter den Göttern und beauftragte Euren Vorfahren, die Vorherrschaft des Sonnenkultes auf die feindseligen Ödlande der Westlichen Wüste am Rande des Königreichs auszudehnen." }
    { group:297, id:20, text: "Pharao Userkaf erklärte Ra zum Höchsten über die Götter und beauftragte Euren Vorfahren, den großartigsten Sonnentempel von allen im üppigen Delta zu bauen, einer Region ohne Baustein." }
    { group:297, id:21, text: "Während Ägyptens Feinde wie Käfer zu einem verwesenden Körper schwärmten, erreichte Eure Familie den Rang des Kanzlers und verhinderte, dass die Feinde des Königreichs ihre Lebensadern durchtrennten." }
    { group:297, id:22, text: "Während Ägyptens Feinde wie Käfer zu einem verwesenden Körper schwärmten, erreichte Eure Familie den Rang des Kanzlers und zeigte die Fähigkeit, fähig zu regieren, während alles andere zerbröckelte.  " }
    { group:297, id:23, text: "Eure Vorfahren gaben ihre Treue den rechtmäßigen Intefs und stellten Thinis' Ruhm wieder her, trotz der konzertierten Bemühungen rebellischer Armeen, diese Errungenschaft zu vereiteln." }
    { group:297, id:24, text: "Zwei Fraktionen kämpften um das Herz Ägyptens, während ihr Bauch leer blieb. Euer Vorfahr rettete viele vor dem Verhungern, während er der rechtmäßigen Dynastie entscheidende Unterstützung leistete." }
    { group:297, id:25, text: "Mentuhotep verlieh Eurer Familie den Rang des Wesirs und verließ sich stark auf ihre Unterstützung, um die Bemühungen verbleibender Rebellen und möchtegern Usurpatoren zu zerschlagen, die Wiedervereinigung zu verhindern. " }
    { group:297, id:26, text: "Mentuhotep verlieh Eurer Familie den Rang des Wesirs, und seine Wiedervereinigungsbemühung profitierte stark vom widergespiegelten Ruhm der stattlichen Stadt, die Ihr aus dem Staub erhoben habt. " }
    { group:297, id:27, text: "Endlich erfüllte ein Mitglied Eurer Familie das Schicksal und wurde Pharao. Euer Clan wurde zu einer königlichen Dynastie, baute eine neue Hauptstadt und brachte die Opposition mit Mitgefühl und guten Taten zum Schweigen." }
    { group:297, id:28, text: "Euer göttlicher Vorfahr besiegte unsere alten Feinde in Nordnubien, flößte den Kuschiten Respekt für Eure Dynastie ein und errichtete einen wichtigen Rotmeerhafen." }
    { group:297, id:29, text: "Der Produktionshafen Eures göttlichen Vorfahren am Roten Meer brachte ungeahnten neuen Reichtum und Luxus zu Eurem Volk, und Euer Familiengrab wird durch die Zeitalter überdauern." }
    { group:297, id:30, text: "Euer erlauchter Vorfahr, der heute in einem fabelhaften Mausoleum ruht, zerschlug die nubische Marine und eroberte eine ihrer schönsten Städte. " }
    { group:297, id:31, text: "Die Stadt Bubastis bleibt bis heute das Juwel in der Doppelkrone. Euer Vorfahr baute eine Stadt, auf die ganz Ägypten mit Stolz blickt." }
    { group:297, id:32, text: "Die gefürchteten Streitwagen der Hyksos in eine ägyptische Waffe zu verwandeln und sie gegen Feinde in unserem belagerten Königreich einzusetzen, war eine brillante Errungenschaft, die die Geschichte nie vergessen wird." }
    { group:297, id:33, text: "Wahrlich, Eure Familie ist seit langem mit Weisheit gesegnet. Die Strategie Eures Vorfahren, Ägyptens größte Generäle zu übermenschlichen Anstrengungen zu inspirieren, zahlte sich großzügig aus." }
    { group:297, id:34, text: "Ihr gründetet ein Neues Reich, sichertet die Wälder von Byblos für alle Zeit und lehrtet wilde Hethiter und geheimnisvolle Seevölker gleichermaßen, Ägyptens Grenzen zu respektieren." }
    { group:297, id:35, text: "Ihr erschuft ungeahnten Reichtum für Euer Neues Reich, während Ihr ägyptische Städte vor alten und neuen Feinden verteidigtet.   " }
    { group:297, id:36, text: "Eure Herrschaft war die größte, die Ägypten je erlebt hat. Unsere Grenzen umspannten die bekannte Welt, und unser Volk genoss unvorstellbare Luxusgüter." }
    { group:297, id:37, text: "Nachdem Ihr jeden Feind besiegt und unermesslichen Wohlstand ins Königreich gebracht hattet, bautet Ihr dann eine Pyramide, die sogar die des legendären Khufu übertraf.  " }
    { group:297, id:38, text: "Mit der Gründung von Deir el-Medina können die Pharaonen für die Ewigkeit mit wenig Furcht ruhen, von gefürchteten Grabräubern gestört zu werden." }
    { group:297, id:39, text: "Mit wenig Zeit im Vorrat wurde Tutanchamuns Grab errichtet und mit üppigen Grabbeigaben versehen." }
    { group:297, id:40, text: "Sethos I. Grabmal ist ein Wunder, das durch die Wellen von Grabräubern, die unterdrückt werden mussten, um es zu bauen, noch bemerkenswerter wird. Es ist schade, dass die Augen der Welt nicht auf seine ewige Schönheit blicken können werden." }
    { group:297, id:41, text: "Der Hafen von Sumur wimmelt nun vom Handel, während er arbeitet, um den Durst unserer Heimat nach Holz und anderen kostbaren Gütern zu stillen." }
    { group:297, id:42, text: "Ägypten erlebte seinen größten Sieg in der Schlacht von Qadesch und bekräftigte seine Vorherrschaft über das Land Amurra. Die hethitische Bedrohung wurde ein für alle Mal zerschlagen." }
    { group:297, id:43, text: "Die Kolosse von Abu Simbel werden für immer von der Macht und dem Ruhm Ägyptens sprechen." }
    { group:297, id:44, text: "Die sterblichen Überreste Ramses' II. ruhen gut in seinem prächtigen Grab. In seinem ewigen Leben wird er sicherlich fortfahren, Ägyptens Hand zu führen." }
    { group:297, id:45, text: "Die gefährlichen Räuber vom Meer, die törichterweise versuchten, sich auf den Ländern Ägyptens niederzulassen, wurden mit Gewalt zurückgetrieben. Ägyptens Grenzen waren wieder sicher." }
    { group:297, id:46, text: "Der befestigte Außenposten im Hinterland Ägyptens widerstand Welle um Welle assyrischer Angriffe und stellte sicher, dass der niederträchtige Feind nicht weiter in die Zwei Länder eindrang." }
    { group:297, id:47, text: "Die Menschen von Achoris werden lange die Geschichte der Dezimierung der persischen Flotte und Vernichtung ihrer Infanterie erzählen. Ein schwerer Schlag wurde den Eroberungsträumen der Perser versetzt." }
    { group:297, id:48, text: "In nur einem Dutzend Jahren entsprang Alexandria dem Land und entwickelte sich zu einer blühenden Metropole, wo nur wenige Jahre zuvor ein armes Fischerdorf stand." }
    { group:297, id:49, text: "Alexandria wurde mit der Großen Bibliothek und dem Pharos-Leuchtturm geschmückt, und ihre Prominenz in der ganzen Welt nahm zu." }
    { group:297, id:50, text: "Mithradates' römische Legionen schlugen Kleopatras rebellisches Geschwister Ptolemaios XIII. in einer großen Schlacht an den Ufern des Mariutsees nieder." }
    { group:297, id:51, text: "Die herrliche Entwicklung Alexandrias setzte sich fort, als das Caesareum und ein weiterer Totentempel ihrer Liste wunderbarer Stätten hinzugefügt wurden." }
    { group:297, id:52, text: "Die kombinierte Stärke von Ägyptens Flotte und Antonius' Streitkräften zerschmetterte Octavian, und Ägypten und Rom wurden als Gleiche vereint, um über die bekannte Welt zu herrschen." }
    { group:298, id:0, text: "Abschließende Kulturbewertung war" }
    { group:298, id:1, text: "Abschließende Wohlstandsbewertung war" }
    { group:298, id:2, text: "Abschließende Monumentbewertung war" }
    { group:298, id:3, text: "Abschließende Reichsbewertung war" }
    { group:298, id:4, text: "Endgültige Bevölkerungszahl war" }
    { group:298, id:5, text: "Endgültige Stadtfinanzen waren" }
    { group:298, id:6, text: "Mission wurde abgeschlossen in" }
    { group:298, id:7, text: "Niedrigster verw. Schwierigkeitsgrad:" }
    { group:298, id:8, text: "Endgültige Punktzahl war:" }
    { group:298, id:9, text: "Jahre" }
    { group:299, id:0, text: "Direktes Ergebnis" }
    { group:299, id:1, text: "Nebensächlich" }
    { group:299, id:2, text: "Trotz" }
    { group:299, id:3, text: "Keine Ursache" }
    { group:299, id:4, text: "Fortlaufend/Zyklisch" }
    { group:299, id:5, text: "Spezifisch nach Bedarf" }
    { group:299, id:6, text: "Automatisch" }
    { group:299, id:7, text: "Direkt" }
    { group:299, id:8, text: "Übrigens" }
    { group:299, id:9, text: "Trotz" }
    { group:299, id:10, text: "Keine" }
    { group:299, id:11, text: "Zyklus" }
    { group:299, id:12, text: "Spez" }
    { group:299, id:13, text: "Auto" }
    { group:304, id:0, text: "Nächste Seite" }
    { group:304, id:1, text: "Vorherige Seite" }
    { group:305, id:0, text: "Eure Familie hat sich dieser Herausforderung noch nie gestellt. Um die Missionsziele anzuzeigen, klickt auf die Schaltfläche unten." }
    { group:306, id:0, text: "Hennafarm" }
    { group:306, id:1, text: "Das feinste Henna wird hier angebaut und an den Farbenmacher geschickt, der die leuchtenden Farben herstellt, die Grabwände verzieren." }
    { group:306, id:2, text: "Produktion ist" }
    { group:306, id:3, text: "abgeschlossen." }
    { group:306, id:4, text: "Euer Handelsaufseher hat verfügt, dass die Hennaproduktion eingestellt werden sollte." }
    { group:306, id:5, text: "Ohne Arbeiter kann diese Farm unmöglich Henna anbauen." }
    { group:306, id:6, text: "Diese Farm hat alle Arbeiter, die sie braucht. Sie sind auf den Feldern und kümmern sich um die Pflanzen." }
    { group:306, id:7, text: "Diese Farm könnte mehr Henna ernten, wenn sie mehr Arbeiter hätte." }
    { group:306, id:8, text: "Diese Farm hat nicht genug Arbeiter, um ein ganzes Hennafeld zu betreuen." }
    { group:306, id:9, text: "Es arbeiten sehr wenige Menschen hier. Die Henna-Ernte wird dadurch leiden." }
    { group:306, id:10, text: "Der Großteil dieser Farm ist unfruchtbar. Sie braucht mehr Arbeiter, bevor sie mehr Henna anbauen kann." }
    { group:306, id:11, text: "Heuschrecken haben alles verschlungen, was hier wuchs, und das Land braucht etwas Zeit zur Erholung." }
    { group:306, id:12, text: "Land ist" }
    { group:306, id:13, text: "fruchtbar." }
    { group:306, id:14, text: "Die nächste Henna-Ernte ist in" }
    { group:307, id:0, text: "0,0,0,0   // mission 0" }
    { group:307, id:1, text: "0,0,0,0" }
    { group:307, id:2, text: "0,0,0,0" }
    { group:307, id:3, text: "0,0,0,0   // Nekhen: first mission with personal salary" }
    { group:307, id:4, text: "1,0,0,0  " }
    { group:307, id:5, text: "1,0,0,0" }
    { group:307, id:6, text: "1,0,0,0" }
    { group:307, id:7, text: "1,0,0,0" }
    { group:307, id:8, text: "1,0,0,0" }
    { group:307, id:9, text: "1,0,0,0" }
    { group:307, id:10, text: "1,0,0,0" }
    { group:307, id:11, text: "1,0,0,0" }
    { group:307, id:12, text: "1,0,0,0" }
    { group:307, id:13, text: "1,0,0,0" }
    { group:307, id:14, text: "1,0,0,0" }
    { group:307, id:15, text: "1,0,0,0" }
    { group:307, id:16, text: "1,0,0,0" }
    { group:307, id:17, text: "1,0,0,0" }
    { group:307, id:18, text: "1,0,0,0" }
    { group:307, id:19, text: "1,0,0,0" }
    { group:307, id:20, text: "1,0,0,0" }
    { group:307, id:21, text: "1,0,0,0" }
    { group:307, id:22, text: "1,0,0,0" }
    { group:307, id:23, text: "1,0,0,0" }
    { group:307, id:24, text: "1,0,0,0" }
    { group:307, id:25, text: "1,0,0,0" }
    { group:307, id:26, text: "1,0,0,0" }
    { group:307, id:27, text: "1,0,0,0" }
    { group:307, id:28, text: "1,0,0,0" }
    { group:307, id:29, text: "1,0,0,0" }
    { group:307, id:30, text: "1,0,0,0" }
    { group:307, id:31, text: "1,0,0,0" }
    { group:307, id:32, text: "1,0,0,0" }
    { group:307, id:33, text: "1,0,0,0" }
    { group:307, id:34, text: "1,0,0,0" }
    { group:307, id:35, text: "1,0,0,0" }
    { group:307, id:36, text: "1,0,0,0" }
    { group:307, id:37, text: "1,0,0,0   // Last mission in original game" }
    { group:307, id:38, text: "0,0,0,1   // Thutmose" }
    { group:307, id:39, text: "0,0,V,1   // Tutankhamun" }
    { group:307, id:40, text: "0,0,V,1   // Seti" }
    { group:307, id:41, text: "0,0,0,0   // Sumer" }
    { group:307, id:42, text: "1,1,0,0   // Qadesh" }
    { group:307, id:43, text: "1,1,0,0   // Abu Simbel" }
    { group:307, id:44, text: "1,1,V,0   // Ramses in the Valley" }
    { group:307, id:45, text: "0,0,0,0   // Pi-Yer" }
    { group:307, id:46, text: "0,0,0,0   // Migdol" }
    { group:307, id:47, text: "0,0,0,0   // Tanis" }
    { group:307, id:48, text: "0,0,0,1   // Alexandria (Alexander's)" }
    { group:307, id:49, text: "1,1,A,1   // Alexandria (Ptolemy's)" }
    { group:307, id:50, text: "0,0,0,0   // Caesar and Cleopatra" }
    { group:307, id:51, text: "1,1,A,0   // Cleopatra's Legacy" }
    { group:307, id:52, text: "1,1,0,0   // Actium" }
    { group:308, id:0, text: "Zoo" }
    { group:308, id:1, text: "Exotische Tiere aus nah und fern erfreuen Scharen von Bürgern im Zoo." }
    { group:308, id:2, text: "Dieser Zoo hat Tierpfleger, aber benötigt eine Wildbrätversorgung, bevor Tiere ihn Heimat nennen können." }
    { group:308, id:3, text: "Dieser Zoo hat Angestellte, aber ohne Stroh kann er keine Tiere beherbergen." }
    { group:308, id:4, text: "Die Menschen haben Angst, einen Zoo ohne Tierpfleger zu besuchen. Bis der Zoo Angestellte findet, wird er der Nachbarschaft keinen Nutzen bringen." }
    { group:308, id:5, text: "Ohne Tiere ist dieser Zoo nichts als leere Käfige." }
    { group:308, id:6, text: "Wildbrät:" }
    { group:308, id:7, text: "Stroh:" }
    { group:309, id:0, text: "Die Gefahr von Krankheiten ist so groß, dass selbst die lachenden Hyänen traurig sind." }
    { group:309, id:1, text: "Wie sollen wir die Tiere füttern, wenn wir uns selbst nicht ernähren können?" }
    { group:309, id:2, text: "Unsere Verteidigungen sind schrecklich schwach. Vielleicht sollte ich das Nilpferd zum Kämpfen trainieren?" }
    { group:309, id:3, text: "Selbst ein Elefant kann sich nicht erinnern, wann der Arbeitermangel schlimmer war." }
    { group:309, id:4, text: "Wenn ein Gott zornig ist, willst du nicht, dass dein Hals wie der einer Giraffe herausragt!" }
    { group:309, id:5, text: "Pharao ist so unglücklich. Ich hoffe, die Zootiere werden nicht für exotische Geschenke benötigt!" }
    { group:309, id:6, text: "Einen Job in dieser Stadt zu finden ist schwieriger, als einen wilden Löwen zu fangen." }
    { group:309, id:7, text: "Die Unterhaltungssituation in dieser Stadt stinkt schlimmer als die Affenkäfige." }
    { group:309, id:8, text: "Hier zu leben ist besser, als im Löwengehege zu schlafen." }
    { group:309, id:9, text: "Ich bin glücklicher als ein schlammbedecktes Nilpferd, in dieser Stadt zu leben." }
    { group:310, id:0, text: "Popup-Nachrichten" }
    { group:310, id:1, text: "Ausgewählte Nachrichten erscheinen nur oben auf dem Bildschirm" }
    { group:310, id:2, text: "Flut-Nachrichten" }
    { group:310, id:3, text: "Bevölkerungs-Nachrichten" }
    { group:310, id:4, text: "Erfüllung jetzt möglich" }
    { group:310, id:5, text: "Reichsansehen steigt" }
    { group:310, id:6, text: "Feste" }
    { group:310, id:7, text: "Kleine Segnungen" }
    { group:310, id:8, text: "Preisänderungen" }
    { group:310, id:9, text: "Handelsniveau-Änderungen" }
    { group:310, id:10, text: "Lohnänderungen" }
    { group:310, id:11, text: "Krankheit bricht aus" }
    { group:310, id:12, text: "Malaria" }
    { group:310, id:13, text: "Angestellte benötigt" }
    { group:310, id:14, text: "Ok" }
    { group:310, id:15, text: "Abbrechen" }
    { group:311, id:0, text: "Monument-Ära wählen" }
    { group:311, id:1, text: "Pyramiden" }
    { group:311, id:2, text: "Tal der Könige" }
    { group:311, id:3, text: "Alexandria" }
    { group:311, id:4, text: "Abu Simbel" }
    { group:312, id:0, text: "Handwerkergilde" }
    { group:312, id:1, text: "Handwerker treffen sich hier, um Putz aus Ton herzustellen und ihre Farben zu mischen, bevor sie losziehen, um ein Grab zu verzieren. " }
    { group:312, id:2, text: "Diese Gilde hat keine Angestellten und kann keine Handwerker entsenden." }
    { group:312, id:3, text: "Diese Gilde hat eine volle Palette von Handwerkern, die keine Zeit verschwenden, Grabinnenräume zu verzieren." }
    { group:312, id:4, text: "Dieser Gilde fehlen ein oder zwei Handwerker. Die Grabmalerei hat sich etwas verlangsamt." }
    { group:312, id:5, text: "Diese Gilde tut ihr Bestes, um Handwerker für das Grab bereitzustellen, und liefert weniger Grabhandwerker, als sie könnte." }
    { group:312, id:6, text: "Diese Gilde braucht viel mehr Arbeiter. Die wenigen einsamen Handwerker, die hier arbeiten, tun, was sie können, um das Grab zu verzieren, aber sie brauchen mehr Hilfe." }
    { group:312, id:7, text: "Farbe in den Gräbern hat viel Zeit zum Trocknen. Wenn diese Gilde nicht mehr Arbeiter findet, könnte das Grab eine Ewigkeit brauchen, um verziert zu werden." }
    { group:312, id:8, text: "Handwerker sind hart bedrängt, ein Grab ohne die Farbe zu verzieren, die es von einem Farbenmacher oder Lagerhof benötigt." }
    { group:312, id:9, text: "Die Gilde wird keine Handwerker zum Grab entsenden, bis sie eine Tonversorgung erhält." }
    { group:312, id:10, text: "Farbe:" }
    { group:312, id:11, text: "Ton:" }
    { group:313, id:0, text: "Farbenwerkstatt" }
    { group:313, id:1, text: "Hier wird Henna zerkleinert und zu Farbe verarbeitet, die Handwerker verwenden, um die Wände von königlichen Grabmälern üppig zu verzieren." }
    { group:313, id:2, text: "Produktion ist" }
    { group:313, id:3, text: "abgeschlossen." }
    { group:313, id:4, text: "Euer Handelsaufseher hat die Farbenproduktion gestoppt." }
    { group:313, id:5, text: "Der Stab dieser Farbenwerkstatt ist vollständig vertrocknet. Ohne Arbeiter kann keine Farbe hergestellt werden." }
    { group:313, id:6, text: "Mit voller Belegschaft produziert diese Farbenwerkstatt Farbe so schnell und effizient wie möglich." }
    { group:313, id:7, text: "Der Personalstand dieser Farbenwerkstatt ist etwas dünn, daher ist die Farbenproduktion beeinträchtigt." }
    { group:313, id:8, text: "Diese Farbenwerkstatt ist unterbesetzt und produziert Farbe langsamer, als sie sollte." }
    { group:313, id:9, text: "Diese Farbenwerkstatt braucht viel mehr Arbeiter. Die Farbenproduktion hier hat sich auf ein Kriechen verlangsamt." }
    { group:313, id:10, text: "Nur wenige Arbeiter sind bei dieser Farbenwerkstatt beschäftigt. Der kleine Stab kann kaum Farbe produzieren." }
    { group:313, id:11, text: "Diese Werkstatt braucht Henna von einer Hennafarm oder einem Lagerhof, bevor sie Farbe herstellen kann. " }
    { group:313, id:12, text: "Henna:" }
]