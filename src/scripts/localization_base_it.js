log_info("akhenaten: localization_base_it config started")

localization_base_it = [
    { group:2, id:0, text: "Opzioni" }
    { group:2, id:9, text: "Salva automaticamente - SÌ" }
    { group:2, id:10, text: "Salva automaticamente - NO" }
    { group:3, id:0, text: "Aiuto" }
    { group:3, id:8, text: "Guida Editor di missioni" }
    { group:4, id:0, text: "Supervisori" }
    { group:4, id:1, text: "Supervisore del lavoro" }
    { group:4, id:2, text: "Supervisore militare" }
    { group:4, id:3, text: "Supervisore politico" }
    { group:4, id:4, text: "Supervisore dei livelli" }
    { group:4, id:5, text: "Supervisore commerciale" }
    { group:4, id:6, text: "Supervisore dei granai" }
    { group:4, id:7, text: "Supervisore della sanità" }
    { group:4, id:8, text: "Supervisore all'istruzione" }
    { group:4, id:9, text: "Supervisore all'intrattenimento" }
    { group:4, id:10, text: "Supervisore dei templi" }
    { group:4, id:11, text: "Supervisore finanziario" }
    { group:4, id:12, text: "Supervisore capo" }
    { group:4, id:13, text: "Supervisore ai monumenti" }
    { group:5, id:1, text: "Abbandoni il Regno?" }
    { group:5, id:3, text: "Paghi per aprire questa via commerciale terrestre?" }
    { group:5, id:4, text: "Apri via commerciale" }
    { group:5, id:5, text: "Paghi per aprire questa via commerciale fluviale?" }
    { group:5, id:6, text: "Richiesta del Faraone" }
    { group:5, id:9, text: "Non hai abbastanza merci per soddisfare la richiesta" }
    { group:5, id:11, text: "Non hai alcuna compagnia da inviare" }
    { group:5, id:13, text: "Ordina al tuo supervisore militare di assegnare alcune compagnie operative a servizio del Regno" }
    { group:5, id:15, text: "Invii dei soccorsi?" }
    { group:5, id:17, text: "Sei sicuro di voler demolire questo forte?" }
    { group:5, id:18, text: "CD mancante" }
    { group:5, id:19, text: "Inserisci il CD di \"La Regina del Nilo - Cleopatra\" nel lettore CD-ROM" }
    { group:5, id:21, text: "Distruggi i ponti con attenzione. Le comunità isolate periscono in fretta, se sono tagliate fuori dalle strade principali del Regno." }
    { group:5, id:24, text: "Versione vecchia" }
    { group:5, id:25, text: "Questo file è di una versione vecchia e non può essere caricato" }
    { group:5, id:26, text: "Troppi arredi funebri!" }
    { group:5, id:27, text: "Non puoi avere più di 5 arredi funebri in questo scenario!" }
    { group:5, id:28, text: "Attenzione!" }
    { group:5, id:29, text: "Questo arredo funebre non è disponibile in questo scenario!" }
    { group:5, id:30, text: "Merci insufficienti!" }
    { group:5, id:31, text: "Non hai abbastanza merci di questo tipo nei magazzini!" }
    { group:5, id:32, text: "Operazione completata!" }
    { group:5, id:33, text: "Non occorrono altri arredi funebri per questo bene!" }
    { group:5, id:34, text: "Max Città" }
    { group:5, id:35, text: "È stato raggiunto il numero massimo di città" }
    { group:5, id:36, text: "Occorre un mezzo di trasporto" }
    { group:5, id:37, text: "Queste truppe devono essere caricate su una nave da trasporto per servire il Regno nel conflitto attuale" }
    { group:5, id:38, text: "Occorrono truppe di terra" }
    { group:5, id:39, text: "Occorrono truppe che viaggiano via terra per servire il Regno nel conflitto attuale" }
    { group:5, id:40, text: "Non occorrono truppe" }
    { group:5, id:41, text: "Non occorrono truppe di terra o di mare" }
    { group:5, id:42, text: "Truppe nel Regno" }
    { group:5, id:43, text: "Queste truppe non sono in città" }
    { group:5, id:44, text: "Nave da guerra nel Regno" }
    { group:5, id:45, text: "Questa nave da guerra non è in città" }
    { group:5, id:46, text: "Impossibile modificare prezzo" }
    { group:5, id:47, text: "Questa merce non è disponibile in questo scenario!" }
    { group:5, id:48, text: "Questo edificio non può funzionare." }
    { group:5, id:49, text: "La città non può produrre o importare tela." }
    { group:5, id:50, text: "Questo edificio non può funzionare." }
    { group:5, id:51, text: "La città non può produrre o importare birra." }
    { group:5, id:52, text: "Questo edificio non può funzionare." }
    { group:5, id:53, text: "La città non può produrre o importare papiro." }
    { group:5, id:54, text: "Le camere mortuarie non possono funzionare." }
    { group:5, id:55, text: "La città non può produrre o importare tela. Gli obitori sono stati rimossi." }
    { group:5, id:56, text: "La taverna senet non può funzionare." }
    { group:5, id:57, text: "La città non può produrre o importare birra. Le taverne senet sono state rimosse." }
    { group:5, id:58, text: "Le Scuole degli scribi non possono funzionare." }
    { group:5, id:59, text: "La città non può produrre o importare papiro. Le Scuole degli Scribi sono state rimosse." }
    { group:5, id:60, text: "Le biblioteche non possono funzionare." }
    { group:5, id:61, text: "La città non può produrre o importare papiro. Le biblioteche sono state rimosse." }
    { group:5, id:62, text: "Questo edificio non può funzionare." }
    { group:5, id:63, text: "La città non può produrre o importare rame." }
    { group:5, id:64, text: "Le armerie non possono funzionare." }
    { group:5, id:65, text: "La città non può produrre o importare rame. Le armerie sono state rimosse." }
    { group:5, id:66, text: "Questo edificio non può funzionare." }
    { group:5, id:67, text: "La città non può produrre o importare legno." }
    { group:5, id:68, text: "Le fabbriche di bighe non possono funzionare." }
    { group:5, id:69, text: "La città non può produrre o importare legno. Le fabbriche di carri sono state rimosse." }
    { group:5, id:70, text: "Questo edificio non può funzionare." }
    { group:5, id:71, text: "La città non ha un reclutatore." }
    { group:5, id:72, text: "Forte: i fanti non possono operare." }
    { group:5, id:73, text: "Questa città non ha un reclutatore. Forte: la fanteria è stata rimossa." }
    { group:5, id:74, text: "Forte: gli arcieri non possono operare." }
    { group:5, id:75, text: "Questa città non ha un reclutatore. Forte: gli arcieri sono stati rimossi." }
    { group:5, id:76, text: "Forte: gli aurighi non possono operare." }
    { group:5, id:77, text: "Questa città non ha un reclutatore. Forte: gli aurighi sono stati rimossi." }
    { group:5, id:78, text: "Le accademie non possono funzionare." }
    { group:5, id:79, text: "Questa città non ha un reclutatore. Le accademie sono state rimosse." }
    { group:5, id:80, text: "Questo edificio non può funzionare." }
    { group:5, id:81, text: "La città non può produrre o importare armi." }
    { group:5, id:82, text: "Questo edificio non può funzionare." }
    { group:5, id:83, text: "La città non può produrre o importare bighe." }
    { group:5, id:84, text: "Forte: i fanti non possono operare." }
    { group:5, id:85, text: "Questa città non ha un armaiolo. Forte: i fanti sono stati rimossi." }
    { group:5, id:86, text: "Forte: gli aurighi non possono operare." }
    { group:5, id:87, text: "Questa città non ha una fabbrica di bighe. Forte: gli aurighi sono stati rimossi." }
    { group:5, id:89, text: "Ti occorre una piazza delle festività per indire una festività." }
    { group:5, id:91, text: "Stai per cancellare la dinastia selezionata e le relative partite salvate. Continuo?" }
    { group:5, id:92, text: "Dinastia esistente" }
    { group:5, id:93, text: "Questo nome è già in uso. Scegline un altro." }
    { group:5, id:95, text: "Devi selezionare una dinastia" }
    { group:5, id:96, text: "Attenzione" }
    { group:5, id:97, text: "Non hai deben a sufficienza per indire una festività." }
    { group:5, id:98, text: "Richiesta del Faraone" }
    { group:5, id:99, text: "Non hai alcuna compagnia di marina da inviare" }
    { group:5, id:100, text: "Richiesta del Faraone" }
    { group:5, id:101, text: "Ordina al tuo supervisore militare di assegnare alcune compagnie marine a servizio del Regno" }
    { group:5, id:102, text: "Invia forze" }
    { group:5, id:103, text: "Per le forze selezionate sono possibili destinazioni multiple. Comunica al tuo supervisore politico dove inviarle." }
    { group:5, id:104, text: "Demolizione monumento" }
    { group:5, id:105, text: "Sei sicuro di voler demolire questo monumento?" }
    { group:5, id:106, text: "Demolizione complesso templi" }
    { group:5, id:107, text: "Vuoi davvero demolire questo complesso templi?" }
    { group:5, id:108, text: "Impossibile salvare" }
    { group:5, id:109, text: "Punti preda/predatore in locazioni non valide." }
    { group:5, id:110, text: "File esistente" }
    { group:5, id:111, text: "Sovrascrivo file esistente?" }
    { group:5, id:112, text: "Nessun venditore" }
    { group:5, id:113, text: "Al momento non ci sono città che desiderino vendere questo bene." }
    { group:5, id:114, text: "Nessun compratore" }
    { group:5, id:115, text: "Al momento non ci sono città che desiderino comprare questo bene." }
    { group:5, id:116, text: "Nessuna via commerciale" }
    { group:5, id:117, text: "Consulta la mappa per aprire una via commerciale ed esportare questo bene." }
    { group:5, id:118, text: "Consulta la mappa per aprire una via commerciale e importare questo bene." }
    { group:5, id:119, text: "Attenzione" }
    { group:5, id:120, text: "Non hai deben sufficienti per aprire una via commerciale" }
    { group:5, id:121, text: "Impossibile salvare" }
    { group:5, id:122, text: "Troppi tipi di cibo (max 4)." }
    { group:5, id:123, text: "Impossibile modificare mappa del mondo" }
    { group:5, id:124, text: "Per modificare la mappa del mondo occorre una risoluzione minima di 800x600." }
    { group:5, id:125, text: " Impossibile abbandonare mappa del mondo" }
    { group:5, id:126, text: "Troppi tipi di cibo (max 4)." }
    { group:5, id:127, text: "Impossibile salvare" }
    { group:5, id:128, text: "Alcuni punti di pesca non sono validi." }
    { group:5, id:129, text: "Impossibile salvare" }
    { group:5, id:130, text: "Punti di ingresso/uscita non validi." }
    { group:5, id:131, text: "Impossibile salvare" }
    { group:5, id:132, text: "Punti di ingresso/uscita fiume non validi." }
    { group:5, id:133, text: "Impossibile salvare" }
    { group:5, id:134, text: "Alcuni punti di invasione (su terra) non sono validi." }
    { group:5, id:135, text: "Impossibile salvare" }
    { group:5, id:136, text: "Alcuni punti di invasione (dal mare) non sono validi." }
    { group:5, id:137, text: "Faraon" }
    { group:5, id:138, text: "Inserisci il CD di \"La Regina del Nilo - Cleopatra\"" }
    { group:5, id:139, text: "Lo zoo non può funzionare" }
    { group:5, id:140, text: "La città non può produrre o importare selvaggina o paglia. Lo zoo è stato tolto." }
    { group:5, id:141, text: "Nessuna missione vinta dalla famiglia." }
    { group:5, id:142, text: "Scegli \"Inizia storia di famiglia\" se non conosci Faraon. Vuoi proseguire nella scelta di una missione? " }
    { group:6, id:2, text: "Mesi per completare la missione" }
    { group:6, id:3, text: "Mesi alla vittoria" }
    { group:6, id:4, text: "Tabelle" }
    { group:6, id:5, text: "Hai già vinto questa missione e hai scelto di continuare a governare" }
    { group:6, id:6, text: "Le tombe vanno posizionate sulle rupi, facendo attenzione che le entrate diano su un terreno aperto" }
    { group:7, id:0, text: "File" }
    { group:7, id:1, text: "Nuova mappa" }
    { group:7, id:2, text: "Carica mappa" }
    { group:7, id:3, text: "Salva mappa" }
    { group:7, id:4, text: "Esci dall'Editor" }
    { group:8, id:1, text: "Db" }
    { group:8, id:2, text: "Persona" }
    { group:8, id:3, text: "Persone" }
    { group:8, id:4, text: "altro mese" }
    { group:8, id:5, text: "mesi" }
    { group:8, id:6, text: "granaio contiene" }
    { group:8, id:7, text: "granai contengono" }
    { group:8, id:8, text: "Anno" }
    { group:8, id:9, text: "Anni" }
    { group:8, id:10, text: "Unità" }
    { group:8, id:11, text: "Unità" }
    { group:8, id:12, text: "Impiegato" }
    { group:8, id:13, text: "Impiegati" }
    { group:8, id:14, text: "altra persona" }
    { group:8, id:15, text: "altre persone" }
    { group:8, id:16, text: "unità." }
    { group:8, id:18, text: "Scuola degli scribi" }
    { group:8, id:19, text: "Scuole degli scribi" }
    { group:8, id:20, text: "Accademia" }
    { group:8, id:21, text: "Accademie" }
    { group:8, id:22, text: "Biblioteca" }
    { group:8, id:23, text: "Biblioteche" }
    { group:8, id:24, text: "Medico" }
    { group:8, id:25, text: "Medici" }
    { group:8, id:26, text: "Dentista" }
    { group:8, id:27, text: "Dentisti" }
    { group:8, id:28, text: "Farmacia" }
    { group:8, id:29, text: "Farmacie" }
    { group:8, id:30, text: "Camera mortuaria" }
    { group:8, id:31, text: "Camere mortuarie" }
    { group:8, id:32, text: "Oracolo" }
    { group:8, id:33, text: "Oracoli" }
    { group:8, id:34, text: "Baraccone" }
    { group:8, id:35, text: "Baracconi" }
    { group:8, id:36, text: "Palco" }
    { group:8, id:37, text: "Palchi" }
    { group:8, id:38, text: "Teatro" }
    { group:8, id:39, text: "Teatri" }
    { group:8, id:40, text: "Gioco senet" }
    { group:8, id:41, text: "Giochi senet" }
    { group:8, id:42, text: "Messaggio" }
    { group:8, id:43, text: "Messaggi" }
    { group:8, id:44, text: "Giorno" }
    { group:8, id:45, text: "Giorni" }
    { group:8, id:46, text: "Soldato" }
    { group:8, id:47, text: "Soldati" }
    { group:8, id:48, text: "Compagnia" }
    { group:8, id:49, text: "Compagnie" }
    { group:8, id:50, text: "Nave da guerra" }
    { group:8, id:51, text: "Navi da guerra" }
    { group:8, id:52, text: "Camera mortuaria" }
    { group:8, id:53, text: "Camere mortuarie" }
    { group:8, id:54, text: "carica" }
    { group:8, id:55, text: "carichi" }
    { group:8, id:56, text: "blocco" }
    { group:8, id:57, text: "blocchi" }
    { group:8, id:58, text: "trasporto" }
    { group:8, id:59, text: "trasporti" }
    { group:9, id:0, text: "Faraon (Espansione La Regina del Nilo - Cleopatra)" }
    { group:9, id:1, text: "Versione 2.0" }
    { group:9, id:2, text: "Copyright 1999-2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Versione Beta per: BreakAway Games Tester" }
    { group:9, id:4, text: "test1 string" }
    { group:9, id:5, text: "Scrivi qui il tuo nome" }
    { group:9, id:6, text: "La mia città egiziana" }
    { group:9, id:7, text: "Scenario1" }
    { group:9, id:8, text: "Editor missioni di Faraon" }
    { group:9, id:9, text: "Demo di Faraon" }
    { group:10, id:0, text: "Resetta" }
    { group:10, id:1, text: "Elimina punti predatori" }
    { group:10, id:2, text: "Elimina pesci" }
    { group:10, id:3, text: "Elimina invasioni" }
    { group:10, id:4, text: "Elimina punti di sbarco" }
    { group:10, id:5, text: "Elimina punti di preda" }
    { group:10, id:6, text: "Carica da BMP" }
    { group:10, id:7, text: "Salva in BMP" }
    { group:10, id:8, text: "Modifica regno" }
    { group:10, id:9, text: "Salva regno" }
    { group:10, id:10, text: "Aggiorna mappa" }
    { group:11, id:0, text: "Preparazione..." }
    { group:11, id:1, text: "test_string ˆ,Œ,œ,¡,°,¿,A,À,Á,Â,Ä, E,È,É,Ê,I,Ì,Í,Î,Ï,N,Ñ,O,Ò,Ó,Ô,Ö, U,Ù,Ú,Û,Ü,ß,a,à,á,â,ä,c,ç, e,è,é,ê,i,ì,í,î,ï,n,ñ,o,ò,ó,ô,ö,u,ù,ú,û,ü,..." }
    { group:11, id:2, text: "Caricamento..." }
    { group:11, id:3, text: "Preparazione dati..." }
    { group:11, id:4, text: "Caricamento suoni..." }
    { group:11, id:5, text: "Tempo accelerato" }
    { group:11, id:6, text: "Clicca col destro per continuare" }
    { group:11, id:7, text: "Carico sfondi..." }
    { group:11, id:8, text: "Carico animazioni..." }
    { group:11, id:9, text: "Carico monumenti..." }
    { group:11, id:10, text: "Carico nemici..." }
    { group:11, id:11, text: "Carico configurazione..." }
    { group:12, id:0, text: "Indietro" }
    { group:12, id:2, text: "per adempiere" }
    { group:12, id:3, text: "Scarse scorte di cibo sono un problema." }
    { group:12, id:4, text: "La disoccupazione elevata è un problema." }
    { group:12, id:5, text: "Una tassazione elevata è un problema." }
    { group:12, id:6, text: "I salari bassi sono un problema" }
    { group:12, id:7, text: "Gli abitanti delle case più disagiate vogliono servizi migliori" }
    { group:13, id:0, text: "Clicca per continuare" }
    { group:13, id:1, text: "Clicca col destro per uscire" }
    { group:13, id:2, text: "Gioco in pausa (premi 'P' per continuare)" }
    { group:13, id:3, text: "Clicca col destro per continuare" }
    { group:13, id:4, text: "Annulla" }
    { group:13, id:5, text: "Continua" }
    { group:13, id:6, text: "Non disponibile nel demo!!." }
    { group:13, id:7, text: "Clicca per iniziare" }
    { group:13, id:8, text: "Scegli un nome egizio" }
    { group:14, id:8, text: "Fuoco" }
    { group:14, id:9, text: "Danni" }
    { group:14, id:10, text: "Crimine" }
    { group:14, id:11, text: "Generale" }
    { group:14, id:12, text: "Giocoliere" }
    { group:14, id:13, text: "Musicante" }
    { group:14, id:14, text: "Danzatore" }
    { group:14, id:15, text: "Senet" }
    { group:14, id:16, text: "Guardiani zoo" }
    { group:14, id:17, text: "Generale" }
    { group:14, id:18, text: "Scuole" }
    { group:14, id:19, text: "Biblioteca" }
    { group:14, id:20, text: "Guadi" }
    { group:14, id:21, text: "Dentista" }
    { group:14, id:22, text: "Medico" }
    { group:14, id:23, text: "Farmacia" }
    { group:14, id:24, text: "Mortuaria" }
    { group:14, id:25, text: "Proventi tasse" }
    { group:14, id:26, text: "Bazar" }
    { group:14, id:27, text: "Desiderabilità" }
    { group:14, id:28, text: "Fertilità" }
    { group:14, id:29, text: "Lavoro" }
    { group:14, id:30, text: "Nativi" }
    { group:14, id:31, text: "Problemi" }
    { group:14, id:32, text: "Problemi" }
    { group:14, id:33, text: "Grano" }
    { group:14, id:34, text: "Ceci" }
    { group:14, id:35, text: "Melograni" }
    { group:14, id:36, text: "Fichi" }
    { group:14, id:37, text: "Carne" }
    { group:14, id:38, text: "Cacciagione" }
    { group:14, id:39, text: "Vasellame" }
    { group:14, id:40, text: "Gioielli" }
    { group:14, id:41, text: "Tela" }
    { group:14, id:42, text: "Birra" }
    { group:14, id:43, text: "Malattia" }
    { group:14, id:44, text: "Ambiente infetto" }
    { group:14, id:45, text: "Acqua" }
    { group:14, id:46, text: "Ambiente vuoto" }
    { group:14, id:47, text: "Irrigazione" }
    { group:14, id:48, text: "Malaria" }
    { group:14, id:49, text: "Difese cittadine" }
    { group:14, id:50, text: "Magistrato" }
    { group:14, id:51, text: "Nascondi rupi" }
    { group:15, id:0, text: "Accetta le merci" }
    { group:15, id:1, text: "Non accettare le merci" }
    { group:15, id:2, text: "Vai a prendere le merci" }
    { group:16, id:0, text: "Costruzioni" }
    { group:16, id:1, text: "Fabbrica" }
    { group:16, id:2, text: "Controllo" }
    { group:16, id:3, text: "Gfx" }
    { group:16, id:4, text: "Struttura" }
    { group:16, id:5, text: "Rete" }
    { group:16, id:6, text: "Casuale" }
    { group:16, id:7, text: "Figura" }
    { group:16, id:8, text: "Animazione" }
    { group:16, id:9, text: "Sticky***" }
    { group:16, id:10, text: "RM_build***" }
    { group:16, id:11, text: "Costruzioni - acqua" }
    { group:16, id:12, text: "Costruzioni - accesso" }
    { group:16, id:13, text: "Costruzioni - dalla capitale" }
    { group:16, id:14, text: "Costruzioni - danno" }
    { group:16, id:15, text: "Costruzioni - popolazione" }
    { group:16, id:16, text: "Desiderabilità" }
    { group:16, id:17, text: "Altezza" }
    { group:16, id:18, text: "River sticky***" }
    { group:16, id:19, text: "Barb sticky***" }
    { group:16, id:20, text: "Danni" }
    { group:16, id:21, text: "Nof figs***" }
    { group:16, id:22, text: "Vecchio tipo" }
    { group:16, id:23, text: "Influenza" }
    { group:16, id:24, text: "Wall sticky***" }
    { group:16, id:25, text: "Road net" }
    { group:16, id:26, text: "District" }
    { group:17, id:0, text: "Nord" }
    { group:17, id:1, text: "Nord-est" }
    { group:17, id:2, text: "Est" }
    { group:17, id:3, text: "Sud-est" }
    { group:17, id:4, text: "Sud" }
    { group:17, id:5, text: "Sud-ovest" }
    { group:17, id:6, text: "Ovest" }
    { group:17, id:7, text: "Nord-ovest" }
    { group:18, id:0, text: "No" }
    { group:18, id:1, text: "Sì" }
    { group:18, id:2, text: "Annulla" }
    { group:18, id:3, text: "OK" }
    { group:18, id:4, text: "Attiva" }
    { group:18, id:5, text: "Ferma" }
    { group:18, id:6, text: "N/D" }
    { group:18, id:7, text: "Altro" }
    { group:18, id:8, text: "e" }
    { group:18, id:9, text: "Riprova" }
    { group:18, id:10, text: "Termina" }
    { group:18, id:11, text: "Ignora" }
    { group:19, id:0, text: "Devi costruire su un terreno libero" }
    { group:19, id:1, text: "Crediti esauriti!" }
    { group:19, id:2, text: "Puoi avere un solo edificio di questo tipo" }
    { group:19, id:3, text: "Sviluppo delle case NO" }
    { group:19, id:4, text: "Sviluppo delle case SI" }
    { group:19, id:5, text: "Sviluppo delle strade NO" }
    { group:19, id:6, text: "Sviluppo delle strade SI" }
    { group:19, id:7, text: "Mostra persone NO" }
    { group:19, id:8, text: "Mostra persone SI" }
    { group:19, id:9, text: "Questo edificio ha bisogno di accesso alla strada" }
    { group:19, id:10, text: "Questa struttura non è vicina all'acqua!" }
    { group:19, id:11, text: "Non disponibile in questa missione!" }
    { group:19, id:12, text: "Non ancora disponibile!!" }
    { group:19, id:13, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build a large temple" }
    { group:19, id:14, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build an oracle" }
    { group:19, id:15, text: "Alla tua città servono più lavoratori." }
    { group:19, id:16, text: "La popolazione mangia più di quanto produce" }
    { group:19, id:17, text: "Costruisci i bazar per distribuire il cibo qui depositato" }
    { group:19, id:18, text: "Costruisci le fattorie sui prati (cerca l'erba gialla)" }
    { group:19, id:19, text: "Costruisci le cave di argilla vicino all'acqua." }
    { group:19, id:20, text: "Costruisci vicino a una zona rocciosa." }
    { group:19, id:21, text: "Crea i taglialegna vicino agli alberi." }
    { group:19, id:22, text: "Costruisci vicino a una zona rocciosa." }
    { group:19, id:23, text: "Esplora il corso del fiume per trovare la posizione adatta." }
    { group:19, id:24, text: "Questo edificio ha bisogno di minerale di rame" }
    { group:19, id:25, text: "Questo edificio ha bisogno di orzo" }
    { group:19, id:26, text: "Questo edificio ha bisogno di lino" }
    { group:19, id:27, text: "Questo edificio ha bisogno di argilla." }
    { group:19, id:28, text: "Questo edificio ha bisogno di gemme" }
    { group:19, id:29, text: "Crea una rotta commerciale per importare quanto serve." }
    { group:19, id:30, text: "Ordina al supervisore commerciale di importarlo." }
    { group:19, id:31, text: "Costruisci una miniera di rame" }
    { group:19, id:32, text: "Costruisci una coltivazione di orzo" }
    { group:19, id:33, text: "Costruisci una coltivazione di lino" }
    { group:19, id:34, text: "Costruisci una cava d'argilla." }
    { group:19, id:35, text: "Costruisci una miniera di gemme" }
    { group:19, id:36, text: "Occorre l'accesso a una pompa idraulica per funzionare" }
    { group:19, id:37, text: "Deve essere vicino all'acqua per riempirsi." }
    { group:19, id:38, text: "Usa i canali d'irrigaz. per collegarlo alla pompa idraulica" }
    { group:19, id:39, text: "Deve essere vicino alle mura per inviare una pattuglia." }
    { group:19, id:40, text: "Occorre un reclutatore per reclutare i soldati" }
    { group:19, id:41, text: "Alcuni soldati hanno bisogno di armi." }
    { group:19, id:42, text: "Apri una scuola di giocolieri per inviare gli animatori qui" }
    { group:19, id:43, text: "Costruisci un conservatorio per avere i musicanti qui" }
    { group:19, id:44, text: "Costruisci una scuola di danza" }
    { group:19, id:45, text: "Costruisci una taverna senet per ospitare i giochi" }
    { group:19, id:46, text: "Non disponibile nella versione demo." }
    { group:19, id:47, text: "Puoi costruire torri solo su mura spesse" }
    { group:19, id:48, text: "Troppo vicino al nemico!" }
    { group:19, id:49, text: "Il morale della compagnia è troppo basso per rispondere" }
    { group:19, id:50, text: "Il tuo esercito ha il pieno supporto dei forti" }
    { group:19, id:53, text: "Non puoi demolire il ponte se c'è gente sopra" }
    { group:19, id:54, text: "Questo lago non è collegato al mare." }
    { group:19, id:55, text: "Impossibile usare la modalità a finestre." }
    { group:19, id:56, text: "Costruisci le piantagioni di canne vicino alle paludi" }
    { group:19, id:57, text: "I carpentieri necessitano legna per costruire le navi da guerra" }
    { group:19, id:58, text: "Per convertire l'oro in deben occorre un Palazzo" }
    { group:19, id:59, text: "Non puoi costruire sui terreni destinati al pascolo." }
    { group:19, id:60, text: "Alcuni appezzamenti sono troppo lontani dalla strada" }
    { group:19, id:61, text: "Parte della città è isolata dalla strada del Regno" }
    { group:19, id:62, text: "Se non ripristini l'accesso, quel settore rimarrà stagnante" }
    { group:19, id:63, text: "Limite di dati - consulta il Readme" }
    { group:19, id:64, text: "Puoi costruire blocchi stradali solo sulle strade" }
    { group:19, id:65, text: "Disponi l'altro approdo per il traghetto" }
    { group:19, id:66, text: "Non c'è un valido punto d'attracco per questo traghetto" }
    { group:19, id:67, text: "Il Regno ha il suo massimo numero (4) di cibi diversi." }
    { group:19, id:68, text: "Non puoi aggiungere la carne se non produca o importi paglia." }
    { group:19, id:69, text: "Non puoi produrre carne in città. Prodotto rimosso." }
    { group:19, id:70, text: "Puoi avere un solo tipo di roccia speciale nel Regno." }
    { group:19, id:71, text: "Prima devi costruire un complesso templi" }
    { group:19, id:72, text: "Un complesso templi può avere un solo oracolo e un solo altare." }
    { group:19, id:73, text: "Devi disporre oracoli e altari su un complesso templi." }
    { group:19, id:74, text: "L'edificio richiede acqua. Costruisci su zona erbosa." }
    { group:19, id:75, text: "Devi disporre questo divertimento su un incrocio." }
    { group:19, id:76, text: "Prima devi completare un tempio!" }
    { group:19, id:77, text: "Ti occorrono 500 papiri per costruire una biblioteca." }
    { group:19, id:78, text: "Per questo edificio occorrono delle canne" }
    { group:19, id:79, text: "Costruisci un raccoglitore di canne" }
    { group:19, id:80, text: "Per questo edificio occorre della paglia" }
    { group:19, id:81, text: "Costruisci una coltivazione di grano" }
    { group:19, id:82, text: "La tua città ha il supporto dei moli per navi da guerra" }
    { group:19, id:83, text: "Servono 100 blocchi di granito per un obelisco piccolo" }
    { group:19, id:84, text: "Servono 200 blocchi di granito per un obelisco grande" }
    { group:19, id:85, text: "Alcuni monumenti non possono essere costruiti. Sono stati rimossi!" }
    { group:19, id:86, text: "Puoi costruire un solo obelisco alla volta" }
    { group:19, id:87, text: "Non puoi riscuotere tasse senza un Palazzo." }
    { group:19, id:88, text: "Servono 220 blocchi d'arenaria per un Tempio del Sole" }
    { group:19, id:89, text: "Puoi costruire un solo tempio del sole alla volta" }
    { group:19, id:90, text: "Ci sono già pochi posti di lavoro per questa popolazione." }
    { group:19, id:91, text: "I nostri livelli di cibo sono bassi." }
    { group:19, id:92, text: "La popolazione mangia già più di quanto produce." }
    { group:19, id:93, text: "La salute cittadina è disastrosa. Pestilenza imminente." }
    { group:19, id:94, text: "La salute è terribile, può dilagare una pestilenza." }
    { group:19, id:95, text: "La salute sta peggiorando, c'è rischio di pestilenza." }
    { group:19, id:96, text: "La salute sta peggiorando, può esserci una pestilenza." }
    { group:19, id:97, text: "La salute sta migliorando, ma la pestilenza è in agguato." }
    { group:19, id:98, text: "La salute migliora, ma c'è ancora rischio di pestilenza." }
    { group:19, id:99, text: "La salute migliora, ma la pestilenza è in agguato." }
    { group:19, id:100, text: "Il palazzo è stato svaligiato!" }
    { group:19, id:101, text: "Parte dei tuoi risparmi è stata rubata dalla tua magione!" }
    { group:19, id:102, text: "Non abbiamo truppe per difenderci dagli attacchi." }
    { group:19, id:103, text: "Sei odiato in tutta la città." }
    { group:19, id:104, text: "La gente è molto arrabbiata con te." }
    { group:19, id:105, text: "La gente è arrabbiata con te." }
    { group:19, id:106, text: "La gente è davvero scontenta di te." }
    { group:19, id:107, text: "La gente è scontenta di te." }
    { group:19, id:108, text: "La gente è stufa di te." }
    { group:19, id:109, text: "La gente è indifferente verso di te." }
    { group:19, id:110, text: "La gente è contenta di te." }
    { group:19, id:111, text: "La gente è molto contenta di te." }
    { group:19, id:112, text: "La gente è contentissima di te." }
    { group:19, id:113, text: "La gente ti ama." }
    { group:19, id:114, text: "La gente ti venera come un dio." }
    { group:19, id:115, text: "Perché non c'è cibo a sufficienza." }
    { group:19, id:116, text: "Perché non ci sono sufficienti posti di lavoro." }
    { group:19, id:117, text: "Perché le tasse sono troppo alte." }
    { group:19, id:118, text: "Perché i salari sono bassi." }
    { group:19, id:119, text: "Perché ci sono troppe catapecchie." }
    { group:19, id:120, text: "Molta gente si sta trasferendo in città" }
    { group:19, id:121, text: "La mancanza di case limita l'immigrazione" }
    { group:19, id:122, text: "I bassi stipendi scoraggiano l'immigrazione" }
    { group:19, id:123, text: "La scarsità di lavoro previene l'immigrazione" }
    { group:19, id:124, text: "La mancanza di cibo limita l'immigrazione" }
    { group:19, id:125, text: "Le tasse elevate scoraggiano l'immigrazione" }
    { group:19, id:126, text: "La presenza di ghetti ostacola l'immigrazione" }
    { group:19, id:127, text: "Il basso morale cittadino previene l'immigrazione" }
    { group:19, id:128, text: "La mancanza di case porta la gente fuori città." }
    { group:19, id:129, text: "I salari bassi portano la gente fuori città." }
    { group:19, id:130, text: "La disoccupazione porta la gente fuori città." }
    { group:19, id:131, text: "La mancanza di cibo porta la gente fuori città." }
    { group:19, id:132, text: "La gente preferisce andarsene che non pagare tasse elevate." }
    { group:19, id:133, text: "Le catapecchie incoraggiano la gente ad andarsene." }
    { group:19, id:134, text: "L'umore cittadino è così basso che la gente se ne va." }
    { group:19, id:135, text: "Occorre della birra perché l'edificio funzioni" }
    { group:19, id:136, text: "Costruisci una distilleria" }
    { group:19, id:137, text: "Occorre del papiro perché l'edificio funzioni" }
    { group:19, id:138, text: "Costruisci una fabbrica di papiro" }
    { group:19, id:139, text: "Occorre della tela perché l'edificio funzioni" }
    { group:19, id:140, text: "Costruisci una tessitoria" }
    { group:19, id:141, text: "Occorre del legno perché l'edificio funzioni" }
    { group:19, id:142, text: "Costruisci un taglialegna" }
    { group:19, id:143, text: "Occorrono paglia e argilla perché l'edificio funzioni" }
    { group:19, id:144, text: "Stabilisci una via commerciale per importare l'argilla" }
    { group:19, id:145, text: "Ordina al supervisore commerciale di importare argilla" }
    { group:19, id:146, text: "Stabilisci una via commerciale per importare la paglia" }
    { group:19, id:147, text: "Ordina al supervisore commerciale di importare paglia" }
    { group:19, id:148, text: "Per questo monumento occorrono pietra e calcare" }
    { group:19, id:149, text: "Costruisci una cava di pietra" }
    { group:19, id:150, text: "Stabilisci una via commerciale per importare la pietra" }
    { group:19, id:151, text: "Ordina al supervisore commerciale di importare la pietra" }
    { group:19, id:152, text: "Costruisci una cava di calcare" }
    { group:19, id:153, text: "Stabilisci una via commerciale per importare il calcare" }
    { group:19, id:154, text: "Ordina al supervisore commerciale di importare calcare" }
    { group:19, id:155, text: "Per questo monumento occorre della pietra" }
    { group:19, id:156, text: "Per questo monumento occorre calcare" }
    { group:19, id:157, text: "Per questo monumento occorrono mattoni e calcare" }
    { group:19, id:158, text: "Costruisci una fabbrica di mattoni" }
    { group:19, id:159, text: "Stabilisci una via commerciale per importare mattoni" }
    { group:19, id:160, text: "Ordina al supervisore commerciale di importare mattoni" }
    { group:19, id:161, text: "Per questo monumento occorrono mattoni" }
    { group:19, id:162, text: "Per questo monumento occorre arenaria" }
    { group:19, id:163, text: "Costruisci una cava di arenaria" }
    { group:19, id:164, text: "Ordina al supervisore commerciale di importare birra" }
    { group:19, id:165, text: "Stabilisci una via commerciale per importare birra" }
    { group:19, id:166, text: "Ordina al supervisore commerciale di importare orzo" }
    { group:19, id:167, text: "Stabilisci una via commerciale per importare orzo" }
    { group:19, id:168, text: "Ordina al supervisore commerciale di importare canne" }
    { group:19, id:169, text: "Stabilisci una via commerciale per importare canne" }
    { group:19, id:170, text: "Ordina al supervisore commerciale di importare papiro" }
    { group:19, id:171, text: "Stabilisci una via commerciale per importare papiro" }
    { group:19, id:172, text: "Ordina al supervisore commerciale di importare lino" }
    { group:19, id:173, text: "Stabilisci una via commerciale per importare lino" }
    { group:19, id:174, text: "Ordina al supervisore commerciale di importare tela" }
    { group:19, id:175, text: "Stabilisci una via commerciale per importare tela" }
    { group:19, id:176, text: "Le camere mortuarie non possono lavorare, sono state rimosse. La città non può produrre o importare tela." }
    { group:19, id:177, text: "La taverna senet non può lavorare, è stata rimossa. La città non può produrre o importare birra." }
    { group:19, id:178, text: "Le scuole degli scribi non possono lavorare, sono state rimosse. La città non può produrre o importare papiro." }
    { group:19, id:179, text: "Le biblioteche non possono lavorare, sono state rimosse. La città non può produrre o importare papiro." }
    { group:19, id:180, text: "Le armerie non possono lavorare, sono state rimosse. La città non può produrre o importare rame." }
    { group:19, id:181, text: "Le fabbriche di bighe non possono lavorare, sono state rimosse. La città non può produrre o importare legno." }
    { group:19, id:182, text: "Forte: la fanteria non può operare ed è stata rimossa. La città non ha un reclutatore." }
    { group:19, id:183, text: "Forte: gli arcieri non possono operare e sono stati rimossi. La città non ha un reclutatore." }
    { group:19, id:184, text: "Forte: gli aurighi non possono operare e sono stati rimossi. La città non ha un reclutatore." }
    { group:19, id:185, text: "Le accademie non possono operare e sono state rimosse. La città non può produrre o importare legno." }
    { group:19, id:186, text: "Forte: la fanteria non può operare ed è stata rimossa. La città non può produrre o importare armi." }
    { group:19, id:187, text: "Forte: gli aurighi non possono operare e sono stati rimossi. La città non può produrre o importare aurighi." }
    { group:19, id:188, text: "Servono 240 unità di arenaria per un mausoleo." }
    { group:19, id:189, text: "Costruisci una distilleria oppure importa la birra." }
    { group:19, id:190, text: "Crea una distilleria o una via commerciale per importare birra." }
    { group:19, id:191, text: "Crea una fabbrica di papiro oppure ordina di importarlo." }
    { group:19, id:192, text: "Crea una fabbrica di papiro o apri una via commerciale per importarlo." }
    { group:19, id:193, text: "Crea una tessitoria oppure ordina di importare la tela." }
    { group:19, id:194, text: "Crea una tessitoria o una via commerciale per importare la tela." }
    { group:19, id:195, text: "L'ufficio degli esattori delle tasse è stato rapinato!" }
    { group:19, id:196, text: "Un Palazzo di giustizia è stato depredato!" }
    { group:19, id:197, text: "La tua magione è stata distrutta!" }
    { group:19, id:198, text: "Il Palazzo è stato distrutto!" }
    { group:19, id:199, text: "L'ufficio di un esattore delle tasse è stato distrutto!" }
    { group:19, id:200, text: "Un Palazzo di giustizia è stato distrutto!" }
    { group:19, id:201, text: "Un minatore d'oro è stato attaccato e derubato!" }
    { group:19, id:202, text: "Costruisci un granaio per custodire il prossimo raccolto" }
    { group:19, id:203, text: "Costruisci dei granai per custodire il prossimo raccolto" }
    { group:19, id:204, text: "Puoi avere al massimo 10 moli attivi" }
    { group:19, id:205, text: "I santuari devono essere entro due spazi dalla strada." }
    { group:19, id:206, text: "Costruisci una Scuola dei giocolieri per avere giocolieri" }
    { group:19, id:207, text: "Costruisci un conservatorio per avere musicanti" }
    { group:19, id:208, text: "Costruisci una Scuola di danza per avere danzatori" }
    { group:19, id:209, text: "Questa compagnia non può giungere a destinazione" }
    { group:19, id:210, text: "Partita salvata." }
    { group:19, id:211, text: "Costruire su terreno libero da ostacoli" }
    { group:19, id:212, text: "La strada rialzata deve portare all'acqua" }
    { group:19, id:213, text: "Costruisci la piazza delle festività su un incrocio" }
    { group:19, id:214, text: "Non ci sarà alcuna immigrazione in presenza di nemici" }
    { group:19, id:215, text: "Trucchi abilitati" }
    { group:19, id:216, text: "Trucchi disabilitati" }
    { group:19, id:217, text: "Lo straripamento sarà perfetto" }
    { group:19, id:218, text: "Lo straripamento sarà eccellente" }
    { group:19, id:219, text: "Lo straripamento sarà buono" }
    { group:19, id:220, text: "Lo straripamento sarà mediocre" }
    { group:19, id:221, text: "Lo straripamento sarà scarso" }
    { group:19, id:222, text: "Non ci sarà straripamento" }
    { group:19, id:223, text: "Aumento dei prezzi" }
    { group:19, id:224, text: "Caduta dei prezzi" }
    { group:19, id:225, text: "Salari abbassati nel regno" }
    { group:19, id:226, text: "Salari aumentati nel regno" }
    { group:19, id:227, text: "Commercio con la città diminuito" }
    { group:19, id:228, text: "Commercio con la città aumentato" }
    { group:19, id:229, text: "Reputazione nel regno sale" }
    { group:19, id:230, text: "Raggiunto obiettivo popolazione" }
    { group:19, id:231, text: "Ricevuta benedizione minore" }
    { group:19, id:232, text: "la festività inizia" }
    { group:19, id:233, text: "Soddisfazione richiesta possibile: merci inviate automaticamente" }
    { group:19, id:234, text: "Zoo rimosso. La città non può produrre o importare selvaggina o paglia." }
    { group:19, id:235, text: "Questo edificio richiede selvaggina per funzionare" }
    { group:19, id:236, text: "Costruisci un casotto da caccia" }
    { group:19, id:237, text: "Costruisci un casotto da caccia o importa la selvaggina" }
    { group:19, id:238, text: "Crea un casotto da caccia o importa selvaggina." }
    { group:19, id:239, text: "Questo monumento richiede il rame" }
    { group:19, id:240, text: "Questo monumento richiede il marmo" }
    { group:19, id:241, text: "Puoi costruire una sola Biblioteca di Alessandria!" }
    { group:19, id:242, text: "Puoi costruire un solo Faro di Pharos!" }
    { group:19, id:243, text: "Puoi costruire un solo Caesareum!" }
    { group:19, id:244, text: "La malattia colpisce" }
    { group:19, id:245, text: "La malaria colpisce" }
    { group:19, id:246, text: "Questo monumento richiede granito" }
    { group:19, id:247, text: "Costruzione possibile solo su terreno roccioso" }
    { group:19, id:248, text: "Il Faro di Pharos non può essere demolito" }
    { group:19, id:249, text: "I ladri di tombe hanno saccheggiato un antico monumento!" }
    { group:19, id:250, text: "Il mausoleo di Alessandro Magno è stato saccheggiato!" }
    { group:19, id:251, text: "I ladri di tombe hanno rubato gli arredi funebri!" }
    { group:19, id:252, text: "Un ladro di tombe è stato catturato" }
    { group:19, id:253, text: "Questo edificio richiede vasellame e olio per funzionare" }
    { group:19, id:254, text: "Crea un vasaio" }
    { group:19, id:255, text: "Crea una via commerciale per importare vasellame" }
    { group:19, id:256, text: "Ordina al supervisore commerciale di importare vasellame" }
    { group:19, id:257, text: "Crea una via commerciale per importare olio" }
    { group:19, id:258, text: "Ordina al supervisore commerciale di importare olio" }
    { group:19, id:259, text: "Questo edificio richiede l'henna per funzionare" }
    { group:19, id:260, text: "Costruisci una fattoria di henna" }
    { group:19, id:261, text: "Ordina al supervisore commerciale di importare henna" }
    { group:19, id:262, text: "Crea una via commerciale per importare henna" }
    { group:19, id:263, text: "Questo edificio richiede l'olio per funzionare" }
    { group:19, id:264, text: "Questo edificio richiede il vasellame per funzionare" }
    { group:19, id:265, text: "Crea una fabbr. di pittura o una via comm. per importarla" }
    { group:19, id:266, text: "Crea una fabbr. di pittura o ordina l'importazione" }
    { group:19, id:267, text: "Costruisci una fabbrica di pittura" }
    { group:19, id:268, text: "Questo edificio richiede argilla e pittura per funzionare" }
    { group:19, id:269, text: "Impiegati richiesti" }
    { group:19, id:270, text: "Deve essere costruita interamente sull rupi" }
    { group:19, id:271, text: "...con l'ingresso che dà su un terreno aperto." }
    { group:20, id:0, text: "AC" }
    { group:20, id:1, text: "DC" }
    { group:21, id:0, text: "Elefantine" }
    { group:21, id:1, text: "Abedju" }
    { group:21, id:2, text: "Oasi di Bahariya" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apollinopolis" }
    { group:21, id:5, text: "Bubastis" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Byblos" }
    { group:21, id:8, text: "Dahshur" }
    { group:21, id:9, text: "Oasi di Dakhla" }
    { group:21, id:10, text: "Abusir" }
    { group:21, id:11, text: "Oasi di Dunqul" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "Oasi di Farafra" }
    { group:21, id:14, text: "Gaza" }
    { group:21, id:15, text: "Semna" }
    { group:21, id:16, text: "Herakleopolis" }
    { group:21, id:17, text: "Kahun" }
    { group:21, id:18, text: "Mirgissa" }
    { group:21, id:19, text: "Itjtawy" }
    { group:21, id:20, text: "Dendera" }
    { group:21, id:21, text: "Gerico" }
    { group:21, id:22, text: "Coptos" }
    { group:21, id:23, text: "Kerma" }
    { group:21, id:24, text: "Oasi di Kharga" }
    { group:21, id:25, text: "Hermopolis" }
    { group:21, id:26, text: "Cnosso" }
    { group:21, id:27, text: "Cirene" }
    { group:21, id:28, text: "Meidum" }
    { group:21, id:29, text: "Memphis" }
    { group:21, id:30, text: "Beni Hasan" }
    { group:21, id:31, text: "Micene" }
    { group:21, id:32, text: "Hierakonpolis" }
    { group:21, id:33, text: "Naqada" }
    { group:21, id:34, text: "Heliopolis" }
    { group:21, id:35, text: "Buto" }
    { group:21, id:36, text: "Punt" }
    { group:21, id:37, text: "Qanta" }
    { group:21, id:38, text: "Giza" }
    { group:21, id:39, text: "Avaris" }
    { group:21, id:40, text: "Saqqara" }
    { group:21, id:41, text: "Lykopolis" }
    { group:21, id:42, text: "     Mersa Gawasis" }
    { group:21, id:43, text: "Oasi di Selima" }
    { group:21, id:44, text: "Serabit Khadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Sharuhen" }
    { group:21, id:47, text: "Thinis" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toshka" }
    { group:21, id:50, text: "Tiro" }
    { group:21, id:51, text: "Tebe" }
    { group:21, id:52, text: "Pelusium" }
    { group:21, id:53, text: "Alessandria" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medina" }
    { group:21, id:56, text: "Abu Simbel" }
    { group:21, id:57, text: "Actium" }
    { group:21, id:58, text: "Roma" }
    { group:21, id:59, text: "Tanis" }
    { group:21, id:60, text: "Pi-Yer" }
    { group:21, id:61, text: "Siwi Oasis" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Piramesse" }
    { group:21, id:64, text: "Atene" }
    { group:21, id:65, text: "Cleoantonopolis" }
    { group:22, id:0, text: "\"Compagnia vuota\"" }
    { group:22, id:1, text: "\"I Leoni\"" }
    { group:22, id:2, text: "\"I Coccodrilli\"" }
    { group:22, id:3, text: "\"I Cobra\"" }
    { group:22, id:4, text: "\"Gli Scorpioni\"" }
    { group:22, id:5, text: "\"I Falchi\"" }
    { group:22, id:6, text: "\"Gli Arieti\"" }
    { group:22, id:7, text: "\"I Leopardi\"" }
    { group:22, id:8, text: "\"I Ragni\"" }
    { group:22, id:9, text: "\"I Gatti\"" }
    { group:22, id:10, text: "\"Le Iene\"" }
    { group:23, id:0, text: "Niente" }
    { group:23, id:1, text: "Grano" }
    { group:23, id:2, text: "Carne" }
    { group:23, id:3, text: "Lattuga" }
    { group:23, id:4, text: "Ceci" }
    { group:23, id:5, text: "Melograni" }
    { group:23, id:6, text: "Fichi" }
    { group:23, id:7, text: "Pesce" }
    { group:23, id:8, text: "Cacciagione" }
    { group:23, id:9, text: "Paglia" }
    { group:23, id:10, text: "Armi" }
    { group:23, id:11, text: "Argilla" }
    { group:23, id:12, text: "Mattoni" }
    { group:23, id:13, text: "Vasellame" }
    { group:23, id:14, text: "Orzo" }
    { group:23, id:15, text: "Birra" }
    { group:23, id:16, text: "Lino" }
    { group:23, id:17, text: "Tela" }
    { group:23, id:18, text: "Gemme" }
    { group:23, id:19, text: "Beni lusso" }
    { group:23, id:20, text: "Legno" }
    { group:23, id:21, text: "Oro" }
    { group:23, id:22, text: "Canne" }
    { group:23, id:23, text: "Papiro" }
    { group:23, id:24, text: "Pietra" }
    { group:23, id:25, text: "Calcare" }
    { group:23, id:26, text: "Granito" }
    { group:23, id:27, text: "Alabastro" }
    { group:23, id:28, text: "Carri" }
    { group:23, id:29, text: "Rame" }
    { group:23, id:30, text: "Arenaria" }
    { group:23, id:31, text: "Olio" }
    { group:23, id:32, text: "Henna" }
    { group:23, id:33, text: "Pittura" }
    { group:23, id:34, text: "Lampade" }
    { group:23, id:35, text: "Marmo" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Truppe" }
    { group:23, id:38, text: "Gioielli (beni di lusso)" }
    { group:23, id:39, text: "Gioielli" }
    { group:23, id:40, text: "Vino (beni di lusso)" }
    { group:23, id:41, text: "Vino" }
    { group:23, id:42, text: "Avorio (beni di lusso)" }
    { group:23, id:43, text: "Avorio" }
    { group:23, id:44, text: "Ebano (beni di lusso)" }
    { group:23, id:45, text: "Ebano" }
    { group:23, id:46, text: "Incenso (beni di lusso)" }
    { group:23, id:47, text: "Incenso" }
    { group:23, id:48, text: "Olio d'oliva (beni di lusso)" }
    { group:23, id:49, text: "Olio d'oliva" }
    { group:23, id:50, text: "Pelli di leopardo (beni di lusso)" }
    { group:23, id:51, text: "Pelli di leopardo" }
    { group:23, id:52, text: "Profumo (beni di lusso)" }
    { group:23, id:53, text: "Profumo" }
    { group:23, id:54, text: "Gioelli (beni di lusso)" }
    { group:23, id:55, text: "cesti di grano" }
    { group:23, id:56, text: "quarti di carne" }
    { group:23, id:57, text: "cespi di lattuga" }
    { group:23, id:58, text: "giare di ceci" }
    { group:23, id:59, text: "melograni" }
    { group:23, id:60, text: "giare di fichi" }
    { group:23, id:61, text: "secchi di pesce" }
    { group:23, id:62, text: "parti di selvaggina" }
    { group:23, id:63, text: "balle di paglia" }
    { group:23, id:64, text: "armi" }
    { group:23, id:65, text: "sacchi di argilla" }
    { group:23, id:66, text: "mattoni" }
    { group:23, id:67, text: "vasi" }
    { group:23, id:68, text: "fasci di orzo" }
    { group:23, id:69, text: "fiaschi di birra" }
    { group:23, id:70, text: "balle di lino" }
    { group:23, id:71, text: "rotoli di tela" }
    { group:23, id:72, text: "gemme" }
    { group:23, id:73, text: "sacchetti di beni preziosi" }
    { group:23, id:74, text: "assi di legno" }
    { group:23, id:75, text: "oro" }
    { group:23, id:76, text: "canne" }
    { group:23, id:77, text: "fogli di papiro" }
    { group:23, id:78, text: "blocchi di pietra" }
    { group:23, id:79, text: "blocchi di calcare" }
    { group:23, id:80, text: "blocchi di granito" }
    { group:23, id:81, text: "tela inutilizzata" }
    { group:23, id:82, text: "Carri" }
    { group:23, id:83, text: "lingotti di rame" }
    { group:23, id:84, text: "blocchi di arenaria" }
    { group:23, id:85, text: "giare d'olio" }
    { group:23, id:86, text: "balle di henna" }
    { group:23, id:87, text: "giare di pittura" }
    { group:23, id:88, text: "lampade" }
    { group:23, id:89, text: "blocchi di marmo" }
    { group:23, id:90, text: "deben" }
    { group:23, id:91, text: "truppe" }
    { group:24, id:0, text: "Settimana 1" }
    { group:24, id:1, text: "Settimana 2" }
    { group:24, id:2, text: "Settimana 3" }
    { group:24, id:3, text: "Settimana 4" }
    { group:24, id:4, text: "Settimana 5" }
    { group:24, id:5, text: "Settimana 6" }
    { group:24, id:6, text: "Settimana 7" }
    { group:24, id:7, text: "Settimana 8" }
    { group:24, id:8, text: "Settimana 9" }
    { group:24, id:9, text: "Settimana 10" }
    { group:24, id:10, text: "Settimana 11" }
    { group:24, id:11, text: "Settimana 12" }
    { group:24, id:12, text: "Settimana 13" }
    { group:24, id:13, text: "Settimana 14" }
    { group:24, id:14, text: "Settimana 15" }
    { group:24, id:15, text: "Settimana 16" }
    { group:26, id:0, text: "Bianco" }
    { group:26, id:1, text: "Rosso" }
    { group:26, id:2, text: "Blu" }
    { group:26, id:3, text: "Verde" }
    { group:26, id:4, text: "Arancio" }
    { group:26, id:5, text: "Argento" }
    { group:26, id:6, text: "Porpora" }
    { group:26, id:7, text: "Giallo" }
    { group:26, id:8, text: "Nero" }
    { group:27, id:0, text: "Per. predinastico" }
    { group:27, id:1, text: "Periodo arcaico" }
    { group:27, id:2, text: "Vecchio regno" }
    { group:27, id:3, text: "Medio regno" }
    { group:27, id:4, text: "Nuovo regno" }
    { group:27, id:5, text: "Valle dei Re" }
    { group:27, id:6, text: "Ramses II" }
    { group:27, id:7, text: "Antichi conquist." }
    { group:27, id:8, text: "Cit. di Cleopatra" }
    { group:28, id:0, text: "In nessun luogo" }
    { group:28, id:1, text: "Annulla" }
    { group:28, id:2, text: "Fattoria" }
    { group:28, id:3, text: "Materie prime" }
    { group:28, id:4, text: "Gilde dei Costruttori" }
    { group:28, id:5, text: "Strada" }
    { group:28, id:6, text: "Muro in fango" }
    { group:28, id:7, text: "Pompa idraulica" }
    { group:28, id:8, text: "Canale di irrigazione" }
    { group:28, id:9, text: "Cava" }
    { group:28, id:10, text: "Casa1" }
    { group:28, id:11, text: "Casa2" }
    { group:28, id:12, text: "Casa3" }
    { group:28, id:13, text: "Casa4" }
    { group:28, id:14, text: "Casa5" }
    { group:28, id:15, text: "Casa6" }
    { group:28, id:16, text: "Casa7" }
    { group:28, id:17, text: "Casa8" }
    { group:28, id:18, text: "Casa9" }
    { group:28, id:19, text: "Casa10" }
    { group:28, id:20, text: "Casa11" }
    { group:28, id:21, text: "Casa12" }
    { group:28, id:22, text: "Casa13" }
    { group:28, id:23, text: "Casa14" }
    { group:28, id:24, text: "Casa15" }
    { group:28, id:25, text: "Casa16" }
    { group:28, id:26, text: "Casa17" }
    { group:28, id:27, text: "Casa18" }
    { group:28, id:28, text: "Casa19" }
    { group:28, id:29, text: "Casa20" }
    { group:28, id:30, text: "Palco" }
    { group:28, id:31, text: "Baraccone" }
    { group:28, id:32, text: "Taverna senet" }
    { group:28, id:33, text: "Padiglione" }
    { group:28, id:34, text: "Conservatorio" }
    { group:28, id:35, text: "Scuola di danza" }
    { group:28, id:36, text: "Scuola dei giocolieri" }
    { group:28, id:37, text: "Maestro senet" }
    { group:28, id:38, text: "Piazza" }
    { group:28, id:39, text: "Giardini" }
    { group:28, id:40, text: "Aurighi" }
    { group:28, id:41, text: "Statua piccola" }
    { group:28, id:42, text: "Statua media" }
    { group:28, id:43, text: "Statua grande" }
    { group:28, id:44, text: "Arcieri" }
    { group:28, id:45, text: "Fanteria" }
    { group:28, id:46, text: "Farmacia" }
    { group:28, id:47, text: "Camera mortuaria" }
    { group:28, id:48, text: "Monumenti" }
    { group:28, id:49, text: "Dentista" }
    { group:28, id:50, text: "Deposito merci" }
    { group:28, id:51, text: "Scuola degli scribi" }
    { group:28, id:52, text: "Guadi" }
    { group:28, id:53, text: "Biblioteca" }
    { group:28, id:54, text: "Niente" }
    { group:28, id:55, text: "Stazione di polizia" }
    { group:28, id:56, text: "Triumphal arch (not used?)" }
    { group:28, id:57, text: "Forti" }
    { group:28, id:58, text: "Corpo di Guardia in fango" }
    { group:28, id:59, text: "Torre in fango" }
    { group:28, id:60, text: "Tempio di Osiride" }
    { group:28, id:61, text: "Tempio di Ra" }
    { group:28, id:62, text: "Tempio di Ptah" }
    { group:28, id:63, text: "Tempio di Seth" }
    { group:28, id:64, text: "Tempio di Bast" }
    { group:28, id:65, text: "Complesso templi di Osiride" }
    { group:28, id:66, text: "Complesso templi di Ra" }
    { group:28, id:67, text: "Complesso templi di Ptah" }
    { group:28, id:68, text: "Complesso templi di Seth" }
    { group:28, id:69, text: "Complesso templi di Bast" }
    { group:28, id:70, text: "Bazar" }
    { group:28, id:71, text: "Granaio" }
    { group:28, id:72, text: "Deposito merci" }
    { group:28, id:73, text: "Depositi merci" }
    { group:28, id:74, text: "Cantiere" }
    { group:28, id:75, text: "Porto" }
    { group:28, id:76, text: "Banchina da pesca" }
    { group:28, id:77, text: "Magione singola" }
    { group:28, id:78, text: "Magione familiare" }
    { group:28, id:79, text: "Magione dinastica" }
    { group:28, id:80, text: "Mission post (not used?)" }
    { group:28, id:81, text: "Centro di architettura" }
    { group:28, id:82, text: "Ponte" }
    { group:28, id:83, text: "Ponte navale" }
    { group:28, id:84, text: "Palazzo del villaggio" }
    { group:28, id:85, text: "Palazzo cittadino" }
    { group:28, id:86, text: "Esattore" }
    { group:28, id:87, text: "Esattore" }
    { group:28, id:88, text: "Niente" }
    { group:28, id:89, text: "Niente" }
    { group:28, id:90, text: "Pompa idraulica" }
    { group:28, id:91, text: "Ornamento" }
    { group:28, id:92, text: "Pozzo" }
    { group:28, id:93, text: "Niente" }
    { group:28, id:94, text: "Accademia" }
    { group:28, id:95, text: "Reclutatore" }
    { group:28, id:96, text: "Templi" }
    { group:28, id:97, text: "Complesso templi" }
    { group:28, id:98, text: "Oracolo" }
    { group:28, id:99, text: "Rovine in fiamme" }
    { group:28, id:100, text: "Orzo" }
    { group:28, id:101, text: "Lino" }
    { group:28, id:102, text: "Grano" }
    { group:28, id:103, text: "Lattuga" }
    { group:28, id:104, text: "Melograni" }
    { group:28, id:105, text: "Ceci" }
    { group:28, id:106, text: "Cava di pietra" }
    { group:28, id:107, text: "Cava di calcare" }
    { group:28, id:108, text: "Taglialegna" }
    { group:28, id:109, text: "Cava d'argilla" }
    { group:28, id:110, text: "Distilleria" }
    { group:28, id:111, text: "Tessitoria" }
    { group:28, id:112, text: "Armeria" }
    { group:28, id:113, text: "Gioielleria" }
    { group:28, id:114, text: "Vasaio" }
    { group:28, id:115, text: "Casotto da caccia" }
    { group:28, id:116, text: "Niente" }
    { group:28, id:117, text: "Niente" }
    { group:28, id:118, text: "Niente" }
    { group:28, id:119, text: "Niente" }
    { group:28, id:120, text: "Plateau (not used?)" }
    { group:28, id:121, text: "Crack (not used?)" }
    { group:28, id:122, text: "Anti plateau (not used?)" }
    { group:28, id:123, text: "Niente" }
    { group:28, id:124, text: "Niente" }
    { group:28, id:125, text: "Niente" }
    { group:28, id:126, text: "Niente" }
    { group:28, id:127, text: "Niente" }
    { group:28, id:128, text: "Niente" }
    { group:28, id:129, text: "Niente" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Approdo" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Blocco stradale" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Santuario di Osiride" }
    { group:28, id:141, text: "Santuario di Ra" }
    { group:28, id:142, text: "Santuario di Ptah" }
    { group:28, id:143, text: "Santuario di Seth" }
    { group:28, id:144, text: "Santuario di Bast" }
    { group:28, id:145, text: "Santuario di" }
    { group:28, id:146, text: "Santuario di" }
    { group:28, id:147, text: "Santuario di" }
    { group:28, id:148, text: "Santuario di" }
    { group:28, id:149, text: "Santuario di" }
    { group:28, id:150, text: "Santuari" }
    { group:28, id:151, text: "Tempio di Osiride" }
    { group:28, id:152, text: "Tempio di Ra" }
    { group:28, id:153, text: "Tempio di Ptah" }
    { group:28, id:154, text: "Tempio di Seth" }
    { group:28, id:155, text: "Tempio di Bast" }
    { group:28, id:156, text: "God 5" }
    { group:28, id:157, text: "God 6" }
    { group:28, id:158, text: "God 7" }
    { group:28, id:159, text: "God 8" }
    { group:28, id:160, text: "God 9" }
    { group:28, id:161, text: "Miniera d'oro" }
    { group:28, id:162, text: "Miniera di gemme" }
    { group:28, id:163, text: "Roccia normale" }
    { group:28, id:164, text: "Roccia mineraria" }
    { group:28, id:165, text: "Inutilizzato" }
    { group:28, id:166, text: "Inutilizzato" }
    { group:28, id:167, text: "Stazione dei vigili del fuoco" }
    { group:28, id:168, text: "Muro in mattoni" }
    { group:28, id:169, text: "Mura" }
    { group:28, id:170, text: "Corpo di Guardia in mattoni" }
    { group:28, id:171, text: "Corpo di Guardia" }
    { group:28, id:172, text: "Torre in mattoni" }
    { group:28, id:173, text: "Torre" }
    { group:28, id:174, text: "Strutture in fango" }
    { group:28, id:175, text: "Strutture in mattoni" }
    { group:28, id:176, text: "Strutture di difesa" }
    { group:28, id:177, text: "Gilda dei carpentieri" }
    { group:28, id:178, text: "Gilda dei muratori" }
    { group:28, id:179, text: "Gilda degli scalpellini" }
    { group:28, id:180, text: "Serbatoio d'acqua" }
    { group:28, id:181, text: "Molo navi trasporto truppe" }
    { group:28, id:182, text: "Molo delle navi da guerra" }
    { group:28, id:183, text: "Piramide" }
    { group:28, id:184, text: "Palazzo di giustizia" }
    { group:28, id:185, text: "Accademia militare 2" }
    { group:28, id:186, text: "Accademia militare 3" }
    { group:28, id:187, text: "Palazzo del villaggio" }
    { group:28, id:188, text: "Palazzo cittadino" }
    { group:28, id:189, text: "Palazzo cittadino grande" }
    { group:28, id:190, text: "Bazar 2" }
    { group:28, id:191, text: "Granaio 2" }
    { group:28, id:192, text: "Banchina 2" }
    { group:28, id:193, text: "Deposito merci 2" }
    { group:28, id:194, text: "Allevamento bestiame" }
    { group:28, id:195, text: "Raccoglitore di canne" }
    { group:28, id:196, text: "Coltivazione di fichi" }
    { group:28, id:197, text: "Paludi" }
    { group:28, id:198, text: "Dune di sabbia" }
    { group:28, id:199, text: "Campo di lavoro" }
    { group:28, id:200, text: "Corpo di Guardia in fango" }
    { group:28, id:201, text: "Corpo di Guardia in mattoni" }
    { group:28, id:202, text: "Corpo di Guardia" }
    { group:28, id:203, text: "Fabbrica di papiro" }
    { group:28, id:204, text: "Fabbrica di mattoni" }
    { group:28, id:205, text: "Fabbrica di bighe" }
    { group:28, id:206, text: "Medico" }
    { group:28, id:207, text: "Segnaposto4" }
    { group:28, id:208, text: "Segnaposto5" }
    { group:28, id:209, text: "Piazza delle festività" }
    { group:28, id:210, text: "Sfinge" }
    { group:28, id:211, text: "Potenziamento complesso templi" }
    { group:28, id:212, text: "Potenziamento complesso templi" }
    { group:28, id:213, text: "Segnaposto10" }
    { group:28, id:214, text: "Punto di sbarco" }
    { group:28, id:215, text: "Cava di alabastro (non usata?)" }
    { group:28, id:216, text: "Cava di granito" }
    { group:28, id:217, text: "Miniera di rame" }
    { group:28, id:218, text: "temp" }
    { group:28, id:219, text: "temp" }
    { group:28, id:220, text: "temp" }
    { group:28, id:221, text: "Cava di arenaria" }
    { group:28, id:222, text: "Mausoleo" }
    { group:28, id:223, text: "Rupe" }
    { group:28, id:224, text: "Henna" }
    { group:28, id:225, text: "Biblioteca di Alessandria" }
    { group:28, id:226, text: "Zoo" }
    { group:28, id:227, text: "Caesareum" }
    { group:28, id:228, text: "Faro di Pharos" }
    { group:28, id:229, text: "Tomba reale piccola" }
    { group:28, id:230, text: "Abu Simbel" }
    { group:28, id:231, text: "Gilda degli artigiani" }
    { group:28, id:232, text: "Fabbrica di lampade" }
    { group:28, id:233, text: "Fabbrica di pittura" }
    { group:28, id:234, text: "Tomba reale media" }
    { group:28, id:235, text: "Tomba reale grande" }
    { group:28, id:236, text: "Tomba reale enorme" }
    { group:29, id:0, text: "Capanno rozzo" }
    { group:29, id:1, text: "Capanno robusto" }
    { group:29, id:2, text: "Baracca rozza" }
    { group:29, id:3, text: "Baracca normale" }
    { group:29, id:4, text: "Casa modesta" }
    { group:29, id:5, text: "Casa normale" }
    { group:29, id:6, text: "Abitazione modesta" }
    { group:29, id:7, text: "Abitazione spaziosa" }
    { group:29, id:8, text: "Appartamento modesto" }
    { group:29, id:9, text: "Appartamento spazioso" }
    { group:29, id:10, text: "Residenza normale" }
    { group:29, id:11, text: "Residenza spaziosa" }
    { group:29, id:12, text: "Residenza elegante" }
    { group:29, id:13, text: "Residenza lussuosa" }
    { group:29, id:14, text: "Villa normale" }
    { group:29, id:15, text: "Villa spaziosa" }
    { group:29, id:16, text: "Villa elegante" }
    { group:29, id:17, text: "Villa lussuosa" }
    { group:29, id:18, text: "Tenuta modesta" }
    { group:29, id:19, text: "Tenuta lussuosa" }
    { group:29, id:20, text: "Capanni rozzi" }
    { group:29, id:21, text: "Capanni robusti" }
    { group:29, id:22, text: "Baracche rozze" }
    { group:29, id:23, text: "Baracche normali" }
    { group:29, id:24, text: "Case modeste" }
    { group:29, id:25, text: "Case normali" }
    { group:29, id:26, text: "Abitazioni modeste" }
    { group:29, id:27, text: "Abitazioni spaziose" }
    { group:29, id:28, text: "Appartamenti modesti" }
    { group:29, id:29, text: "Appartamenti spaziosi" }
    { group:29, id:30, text: "Residenze normali" }
    { group:29, id:31, text: "Residenze spaziose" }
    { group:29, id:32, text: "Residenze eleganti" }
    { group:29, id:33, text: "Residenze lussuose" }
    { group:29, id:34, text: "Ville normali" }
    { group:29, id:35, text: "Ville spaziose" }
    { group:29, id:36, text: "Ville eleganti" }
    { group:29, id:37, text: "Ville lussuose" }
    { group:29, id:38, text: "Tenute modeste" }
    { group:29, id:39, text: "Tenute lussuose" }
    { group:29, id:40, text: "Capanni rozzi:" }
    { group:29, id:41, text: "Capanni robusti:" }
    { group:29, id:42, text: "Baracche rozze:" }
    { group:29, id:43, text: "Baracche normali:" }
    { group:29, id:44, text: "Case modeste:" }
    { group:29, id:45, text: "Case normali:" }
    { group:29, id:46, text: "Abitazioni modeste:" }
    { group:29, id:47, text: "Abitazioni spaziose:" }
    { group:29, id:48, text: "Appartamenti modesti:" }
    { group:29, id:49, text: "Appartamenti spaziosi:" }
    { group:29, id:50, text: "Residenze normali:" }
    { group:29, id:51, text: "Residenze spaziose:" }
    { group:29, id:52, text: "Residenze eleganti:" }
    { group:29, id:53, text: "Residenze lussuose:" }
    { group:29, id:54, text: "Ville normali:" }
    { group:29, id:55, text: "Ville spaziose:" }
    { group:29, id:56, text: "Ville eleganti:" }
    { group:29, id:57, text: "Ville lussuose:" }
    { group:29, id:58, text: "Tenute modeste:" }
    { group:29, id:59, text: "Tenute lussuose:" }
    { group:30, id:0, text: "Faraon/La Regina del Nilo" }
    { group:30, id:1, text: "Gioca Demo di Faraon" }
    { group:30, id:2, text: "Visita il sito web di Faraon" }
    { group:30, id:3, text: "Editor di missioni" }
    { group:30, id:4, text: "Esci" }
    { group:30, id:5, text: "Famiglie più importanti" }
    { group:31, id:0, text: "Inserisci il nome della famiglia" }
    { group:31, id:1, text: "Clicca col destro per continuare" }
    { group:32, id:0, text: "Anziano villaggio" }
    { group:32, id:1, text: "Nobile del villaggio" }
    { group:32, id:2, text: "Studioso reale" }
    { group:32, id:3, text: "Scriba reale" }
    { group:32, id:4, text: "Giudice reale" }
    { group:32, id:5, text: "Sindaco reale" }
    { group:32, id:6, text: "Governatore reale" }
    { group:32, id:7, text: "Nomarca" }
    { group:32, id:8, text: "Cancelliere" }
    { group:32, id:9, text: "Consigliere" }
    { group:32, id:10, text: "Faraone" }
    { group:32, id:11, text: "O Anziano del villaggio" }
    { group:32, id:12, text: "O Nobile del villaggio" }
    { group:32, id:13, text: "O Studioso reale" }
    { group:32, id:14, text: "O Scriba reale" }
    { group:32, id:15, text: "O Giudice reale" }
    { group:32, id:16, text: "O Sindaco reale" }
    { group:32, id:17, text: "O Governatore reale" }
    { group:32, id:18, text: "O Nomarca" }
    { group:32, id:19, text: "O Cancelliere" }
    { group:32, id:20, text: "O Consigliere" }
    { group:32, id:21, text: "O Faraone" }
    { group:32, id:22, text: "Missione banale" }
    { group:32, id:23, text: "Missione molto semplice" }
    { group:32, id:24, text: "Missione facile" }
    { group:32, id:25, text: "Missione abbastanza facile" }
    { group:32, id:26, text: "Missione media" }
    { group:32, id:27, text: "Missione abbastanza difficile" }
    { group:32, id:28, text: "Missione difficile" }
    { group:32, id:29, text: "Missione molto difficile" }
    { group:32, id:30, text: "Missione estremamente difficile" }
    { group:32, id:31, text: "Missione quasi impossibile" }
    { group:33, id:0, text: "Mappa minuscola" }
    { group:33, id:1, text: "Mappa piccola" }
    { group:33, id:2, text: "Mappa media" }
    { group:33, id:3, text: "Mappa grande" }
    { group:33, id:4, text: "Mappa enorme" }
    { group:33, id:5, text: "Mappa immensa" }
    { group:33, id:6, text: "Annulla" }
    { group:34, id:0, text: "Nessun invasore" }
    { group:34, id:1, text: "Es. nemico" }
    { group:34, id:2, text: "Esercito egizio" }
    { group:34, id:3, text: "Esercito Faraone" }
    { group:34, id:4, text: "Es. beduino" }
    { group:35, id:0, text: "Città egiziana caduta" }
    { group:35, id:1, text: "Città straniera conquistata" }
    { group:35, id:2, text: "Via commerciale ora disponibile" }
    { group:35, id:3, text: "Via commerciale chiusa" }
    { group:35, id:4, text: "Città commerciale sotto assedio" }
    { group:36, id:0, text: "Attacca catena alimentare" }
    { group:36, id:1, text: "Attacca depositi dell'oro" }
    { group:36, id:2, text: "Attacca edifici migliori" }
    { group:36, id:3, text: "Attacca truppe" }
    { group:36, id:4, text: "Attacco casuale" }
    { group:37, id:0, text: "Hyksos" }
    { group:37, id:1, text: "Popolo del mare" }
    { group:37, id:2, text: "Ittiti" }
    { group:37, id:3, text: "Mitanni" }
    { group:37, id:4, text: "Kushiti" }
    { group:37, id:5, text: "Libici" }
    { group:37, id:6, text: "Nubiani" }
    { group:37, id:7, text: "Canaaniti" }
    { group:37, id:8, text: "Assiri" }
    { group:37, id:9, text: "Romani" }
    { group:37, id:10, text: "Fenici" }
    { group:37, id:11, text: "Persiani" }
    { group:37, id:12, text: "Egizi" }
    { group:37, id:13, text: "Beduini" }
    { group:37, id:14, text: "Un soldato hyksos" }
    { group:37, id:15, text: "Un soldato del popolo del mare" }
    { group:37, id:16, text: "Un soldato ittita" }
    { group:37, id:17, text: "Un soldato mitanno" }
    { group:37, id:18, text: "Un soldato kushita" }
    { group:37, id:19, text: "Un soldato libico" }
    { group:37, id:20, text: "Un soldato nubiano" }
    { group:37, id:21, text: "Un soldato canaanita" }
    { group:37, id:22, text: "Un soldato assiro" }
    { group:37, id:23, text: "Un soldato romano" }
    { group:37, id:24, text: "Un soldato fenicio" }
    { group:37, id:25, text: "Un soldato persiano" }
    { group:37, id:26, text: "Un soldato egizio" }
    { group:37, id:27, text: "Un soldato beduino" }
    { group:37, id:28, text: "un esercito hyksos" }
    { group:37, id:29, text: "un esercito del popolo del mare" }
    { group:37, id:30, text: "un esercito ittita" }
    { group:37, id:31, text: "un esercito mitanno" }
    { group:37, id:32, text: "un esercito kushita" }
    { group:37, id:33, text: "un esercito libico" }
    { group:37, id:34, text: "un esercito nubiano" }
    { group:37, id:35, text: "un esercito canaanita" }
    { group:37, id:36, text: "un esercito assiro" }
    { group:37, id:37, text: "un esercito romano" }
    { group:37, id:38, text: "un esercito fenicio" }
    { group:37, id:39, text: "un esercito persiano" }
    { group:37, id:40, text: "un esercito egizio" }
    { group:37, id:41, text: "un esercito beduino" }
    { group:38, id:0, text: "Eventi speciali" }
    { group:38, id:1, text: "Terremoto" }
    { group:38, id:2, text: "Rivolta dei gladiatori" }
    { group:38, id:3, text: "Cambio di Faraone" }
    { group:38, id:4, text: "Problema via marittima" }
    { group:38, id:5, text: "Problema via terrestre" }
    { group:38, id:6, text: "Il Faraone aumenta i salari" }
    { group:38, id:7, text: "Il Faraone diminuisce i salari" }
    { group:38, id:8, text: "Acqua inquinata" }
    { group:38, id:9, text: "Una miniera d'oro crolla" }
    { group:38, id:10, text: "Allagatamento cava argilla" }
    { group:38, id:11, text: "In uso" }
    { group:38, id:12, text: "Sincronizzazione" }
    { group:38, id:13, text: "Casuale" }
    { group:39, id:0, text: "La nostra città" }
    { group:39, id:1, text: "Città commerciale Faraone" }
    { group:39, id:2, text: "Città Faraone" }
    { group:39, id:3, text: "Città commerciale egiziana" }
    { group:39, id:4, text: "Città egiziana" }
    { group:39, id:5, text: "Città commerciale straniera" }
    { group:39, id:6, text: "Città straniera" }
    { group:40, id:0, text: "Nessuna" }
    { group:40, id:1, text: "Minore" }
    { group:40, id:2, text: "Media" }
    { group:40, id:3, text: "Maggiore" }
    { group:41, id:0, text: "In nessun luogo" }
    { group:41, id:1, text: "Niente" }
    { group:41, id:2, text: "Niente" }
    { group:41, id:3, text: "Niente" }
    { group:41, id:4, text: "Niente" }
    { group:41, id:5, text: "Strada" }
    { group:41, id:6, text: "Muro in fango" }
    { group:41, id:7, text: "Canale di irrigazione" }
    { group:41, id:8, text: "Pompa idraulica" }
    { group:41, id:9, text: "Niente" }
    { group:41, id:10, text: "Capanno rozzo" }
    { group:41, id:11, text: "Capanno robusto" }
    { group:41, id:12, text: "Baracca rozza" }
    { group:41, id:13, text: "Baracca normale" }
    { group:41, id:14, text: "Casa modesta" }
    { group:41, id:15, text: "Casa normale" }
    { group:41, id:16, text: "Abitazione modesta" }
    { group:41, id:17, text: "Abitazione spaziosa" }
    { group:41, id:18, text: "Appartamento modesto" }
    { group:41, id:19, text: "Appartamento spazioso" }
    { group:41, id:20, text: "Residenza normale" }
    { group:41, id:21, text: "Residenza spaziosa" }
    { group:41, id:22, text: "Residenza elegante" }
    { group:41, id:23, text: "Residenza lussuosa" }
    { group:41, id:24, text: "Villa normale" }
    { group:41, id:25, text: "Villa spaziosa" }
    { group:41, id:26, text: "Villa elegante" }
    { group:41, id:27, text: "Villa lussuosa" }
    { group:41, id:28, text: "Tenuta modesta" }
    { group:41, id:29, text: "Tenuta lussuosa" }
    { group:41, id:30, text: "Padiglione della musica" }
    { group:41, id:31, text: "Baraccone" }
    { group:41, id:32, text: "Taverna senet" }
    { group:41, id:33, text: "Palco della danza" }
    { group:41, id:34, text: "Conservatorio" }
    { group:41, id:35, text: "Scuola di danza" }
    { group:41, id:36, text: "Scuola dei giocolieri" }
    { group:41, id:37, text: "Allenamento aurighi" }
    { group:41, id:38, text: "Piazza" }
    { group:41, id:39, text: "Giardini" }
    { group:41, id:40, text: "Forte di fanteria" }
    { group:41, id:41, text: "Statua piccola" }
    { group:41, id:42, text: "Statua media" }
    { group:41, id:43, text: "Statua grande" }
    { group:41, id:44, text: "Arcieri" }
    { group:41, id:45, text: "Fanteria" }
    { group:41, id:46, text: "Farmacia" }
    { group:41, id:47, text: "Camera mortuaria" }
    { group:41, id:48, text: "Monumenti" }
    { group:41, id:49, text: "Dentista" }
    { group:41, id:50, text: "Centro di distribuzione" }
    { group:41, id:51, text: "Scuola degli scribi" }
    { group:41, id:52, text: "Guadi" }
    { group:41, id:53, text: "Biblioteca" }
    { group:41, id:54, text: "Niente" }
    { group:41, id:55, text: "Stazione di polizia" }
    { group:41, id:56, text: "Triumphal arch (not used?)" }
    { group:41, id:57, text: "Forte" }
    { group:41, id:58, text: "Corpo di Guardia in fango" }
    { group:41, id:59, text: "Torre in fango" }
    { group:41, id:60, text: "Tempio di Osiride" }
    { group:41, id:61, text: "Tempio di Ra" }
    { group:41, id:62, text: "Tempio di Ptah" }
    { group:41, id:63, text: "Tempio di Seth" }
    { group:41, id:64, text: "Tempio di Bast" }
    { group:41, id:65, text: "Complesso templi di Osiride" }
    { group:41, id:66, text: "Complesso templi di Ra" }
    { group:41, id:67, text: "Complesso templi di Ptah" }
    { group:41, id:68, text: "Complesso templi di Seth" }
    { group:41, id:69, text: "Complesso templi di Bast" }
    { group:41, id:70, text: "Bazar" }
    { group:41, id:71, text: "Granaio" }
    { group:41, id:72, text: "Deposito merci" }
    { group:41, id:73, text: "Depositi merci" }
    { group:41, id:74, text: "Cantiere" }
    { group:41, id:75, text: "Porto" }
    { group:41, id:76, text: "Banchina da pesca" }
    { group:41, id:77, text: "Magione personale" }
    { group:41, id:78, text: "Magione famigliare" }
    { group:41, id:79, text: "Magione dinastica" }
    { group:41, id:80, text: "Missione" }
    { group:41, id:81, text: "Centro di architettura" }
    { group:41, id:82, text: "Ponte piccolo" }
    { group:41, id:83, text: "Ponte grande" }
    { group:41, id:84, text: "Palazzo del villaggio" }
    { group:41, id:85, text: "Palazzo cittadino" }
    { group:41, id:86, text: "Esattore" }
    { group:41, id:87, text: "Esattore" }
    { group:41, id:88, text: "Capanna dei nativi" }
    { group:41, id:89, text: "Punto d'incontro dei nativi" }
    { group:41, id:90, text: "Pompa idraulica" }
    { group:41, id:91, text: "Ornamento" }
    { group:41, id:92, text: "Pozzo" }
    { group:41, id:93, text: "Niente" }
    { group:41, id:94, text: "Accademia" }
    { group:41, id:95, text: "Reclutatore" }
    { group:41, id:96, text: "Niente" }
    { group:41, id:97, text: "Niente" }
    { group:41, id:98, text: "Oracolo" }
    { group:41, id:99, text: "Rovine in fiamme" }
    { group:41, id:100, text: "Coltivazione d'orzo" }
    { group:41, id:101, text: "Coltivazione di lino" }
    { group:41, id:102, text: "Coltivazione di grano" }
    { group:41, id:103, text: "Coltivazione di lattuga" }
    { group:41, id:104, text: "Coltivazione di melograni" }
    { group:41, id:105, text: "Coltivazione di ceci" }
    { group:41, id:106, text: "Cava di pietra" }
    { group:41, id:107, text: "Cava di calcare" }
    { group:41, id:108, text: "Taglialegna" }
    { group:41, id:109, text: "Cava d'argilla" }
    { group:41, id:110, text: "Distilleria" }
    { group:41, id:111, text: "Tessitoria" }
    { group:41, id:112, text: "Armeria" }
    { group:41, id:113, text: "Gioielleria" }
    { group:41, id:114, text: "Vasaio" }
    { group:41, id:115, text: "Casotto da caccia" }
    { group:41, id:116, text: "Erba" }
    { group:41, id:117, text: "Alberi" }
    { group:41, id:118, text: "Acqua" }
    { group:41, id:119, text: "Boscaglia" }
    { group:41, id:120, text: "Larve" }
    { group:41, id:121, text: "Roccia" }
    { group:41, id:122, text: "Prato" }
    { group:41, id:123, text: "Plateau (not used?)" }
    { group:41, id:124, text: "Anti Plateau (not used?)" }
    { group:41, id:125, text: "Strada" }
    { group:41, id:126, text: "Punto di invasione" }
    { group:41, id:127, text: "Punto di ingresso" }
    { group:41, id:128, text: "Punto di uscita" }
    { group:41, id:129, text: "Ramp (not used?)" }
    { group:41, id:130, text: "Ingresso fiume" }
    { group:41, id:131, text: "Uscita fiume" }
    { group:41, id:132, text: "Punto di pesca" }
    { group:41, id:133, text: "Punto predatori" }
    { group:41, id:134, text: "Pianura inondata" }
    { group:41, id:135, text: "Irrigazione" }
    { group:41, id:136, text: "Approdo" }
    { group:41, id:137, text: "Sistema di strade" }
    { group:41, id:138, text: "Nessun accesso" }
    { group:41, id:139, text: "Punto di preghiera" }
    { group:41, id:140, text: "Santuario di Osiride" }
    { group:41, id:141, text: "Santuario di Ra" }
    { group:41, id:142, text: "Santuario di Ptah" }
    { group:41, id:143, text: "Santuario di Seth" }
    { group:41, id:144, text: "Santuario di Bast" }
    { group:41, id:145, text: "Shrine God5" }
    { group:41, id:146, text: "Shrine God6" }
    { group:41, id:147, text: "Shrine God7" }
    { group:41, id:148, text: "Shrine God8" }
    { group:41, id:149, text: "Shrine God9" }
    { group:41, id:150, text: "Santuario" }
    { group:41, id:151, text: "Temp Small5" }
    { group:41, id:152, text: "Temp Small6" }
    { group:41, id:153, text: "Temp Small7" }
    { group:41, id:154, text: "Temp Small8" }
    { group:41, id:155, text: "Temp Small9" }
    { group:41, id:156, text: "Temp Large5" }
    { group:41, id:157, text: "Temp Large6" }
    { group:41, id:158, text: "Temp Large7" }
    { group:41, id:159, text: "Temp Large8" }
    { group:41, id:160, text: "Temp Large9" }
    { group:41, id:161, text: "Miniera d'oro" }
    { group:41, id:162, text: "Miniera di gemme" }
    { group:41, id:163, text: "Roccia normale" }
    { group:41, id:164, text: "Minerale d'oro" }
    { group:41, id:165, text: "Minerale gemma" }
    { group:41, id:166, text: "Roccia finita" }
    { group:41, id:167, text: "Stazione dei vigili del fuoco" }
    { group:41, id:168, text: "Muro in mattoni" }
    { group:41, id:169, text: "Mura" }
    { group:41, id:170, text: "Corpo di Guardia in mattoni" }
    { group:41, id:171, text: "Corpo di Guardia" }
    { group:41, id:172, text: "Torre in mattoni" }
    { group:41, id:173, text: "Torre" }
    { group:41, id:174, text: "Strutture in fango" }
    { group:41, id:175, text: "Strutture in mattoni" }
    { group:41, id:176, text: "Strutture di difesa" }
    { group:41, id:177, text: "Gilda dei carpentieri" }
    { group:41, id:178, text: "Gilda dei muratori" }
    { group:41, id:179, text: "Gilda degli scalpellini" }
    { group:41, id:180, text: "Serbatoio d'acqua" }
    { group:41, id:181, text: "Molo commerciale" }
    { group:41, id:182, text: "Molo delle navi da guerra" }
    { group:41, id:183, text: "Piramide" }
    { group:41, id:184, text: "Palazzo di giustizia" }
    { group:41, id:185, text: "Accademia militare 2" }
    { group:41, id:186, text: "Accademia militare 3" }
    { group:41, id:187, text: "Palazzo del villaggio" }
    { group:41, id:188, text: "Palazzo cittadino" }
    { group:41, id:189, text: "Palazzo cittadino grande" }
    { group:41, id:190, text: "Bazar 2" }
    { group:41, id:191, text: "Granaio 2" }
    { group:41, id:192, text: "Banchina 2" }
    { group:41, id:193, text: "Deposito merci 2" }
    { group:41, id:194, text: "Allevamento bestiame" }
    { group:41, id:195, text: "Raccoglitore di canne" }
    { group:41, id:196, text: "Coltivazione di fichi" }
    { group:41, id:197, text: "Paludi" }
    { group:41, id:198, text: "Duna di sabbia" }
    { group:41, id:199, text: "Campo di lavoro" }
    { group:41, id:200, text: "Corpo di Guardia in fango" }
    { group:41, id:201, text: "Corpo di Guardia in mattoni" }
    { group:41, id:202, text: "Corpo di Guardia" }
    { group:41, id:203, text: "Fabbrica di papiro" }
    { group:41, id:204, text: "Fabbrica di mattoni" }
    { group:41, id:205, text: "Fabbrica di bighe" }
    { group:41, id:206, text: "Medico" }
    { group:41, id:207, text: "Placeholder4" }
    { group:41, id:208, text: "Placeholder5" }
    { group:41, id:209, text: "Piazza delle festività" }
    { group:41, id:210, text: "Sfinge" }
    { group:41, id:211, text: "Potenziamento complesso templi" }
    { group:41, id:212, text: "Potenziamento complesso templi" }
    { group:41, id:213, text: "Placeholder10" }
    { group:41, id:214, text: "Punto di sbarco" }
    { group:41, id:215, text: "unused 1474" }
    { group:41, id:216, text: "Cava di granito" }
    { group:41, id:217, text: "Miniera di rame" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Cava di arenaria" }
    { group:41, id:222, text: "Mausoleo" }
    { group:41, id:223, text: "Rupe" }
    { group:41, id:224, text: "Fattoria di henna" }
    { group:41, id:225, text: "Biblioteca di Alessandria" }
    { group:41, id:226, text: "Zoo" }
    { group:41, id:227, text: "Caesareum" }
    { group:41, id:228, text: "Faro di Pharos" }
    { group:41, id:229, text: "Tomba reale piccola" }
    { group:41, id:230, text: "Abu Simbel" }
    { group:41, id:231, text: "Gilda degli artigiani" }
    { group:41, id:232, text: "Fabbrica di lampade" }
    { group:41, id:233, text: "Fabbrica di pittura" }
    { group:41, id:234, text: "Tomba reale media" }
    { group:41, id:235, text: "Tomba reale grande" }
    { group:41, id:236, text: "Tomba reale enorme" }
    { group:42, id:1, text: "Pieno schermo" }
    { group:42, id:2, text: "Finestra" }
    { group:42, id:3, text: "Risoluzione 640 x 480" }
    { group:42, id:4, text: "Risoluzione 800 x 600" }
    { group:42, id:5, text: "Risoluzione 1024 x 768" }
    { group:42, id:6, text: "Annulla" }
    { group:43, id:0, text: "Salvataggio della città" }
    { group:43, id:1, text: "Carico partita salvata" }
    { group:43, id:2, text: "Il file non esiste" }
    { group:43, id:3, text: "Salva mappa" }
    { group:43, id:4, text: "Carica una mappa" }
    { group:43, id:5, text: "Continua?" }
    { group:43, id:6, text: "Cancella file" }
    { group:43, id:7, text: "Aggiungi" }
    { group:44, id:0, text: "Aggiungi" }
    { group:44, id:1, text: "Modifica" }
    { group:44, id:2, text: "Elimina" }
    { group:44, id:3, text: "Generale" }
    { group:44, id:4, text: "Importa mappa" }
    { group:44, id:5, text: "Acquisti" }
    { group:44, id:6, text: "non libero" }
    { group:44, id:7, text: "OK" }
    { group:44, id:8, text: "Grafica semplice" }
    { group:44, id:9, text: "Città" }
    { group:44, id:10, text: "Regione" }
    { group:44, id:11, text: "Indicatore battaglia" }
    { group:44, id:12, text: "libero" }
    { group:44, id:13, text: "Data iniziale." }
    { group:44, id:14, text: "Richiesta del Faraone" }
    { group:44, id:15, text: "Invasioni" }
    { group:44, id:16, text: "OK" }
    { group:44, id:17, text: "Annulla" }
    { group:44, id:18, text: "Stato attuale del regno" }
    { group:44, id:19, text: "Nessuna richiesta" }
    { group:44, id:20, text: "Nessuna invasione" }
    { group:44, id:21, text: "Missione non ancora completata" }
    { group:44, id:22, text: "Programmazione di un'invasione" }
    { group:44, id:23, text: "Spazio libero" }
    { group:44, id:24, text: "in" }
    { group:44, id:25, text: "Richiesta non programmata" }
    { group:44, id:26, text: "Invasione non programmata" }
    { group:44, id:27, text: "da" }
    { group:44, id:28, text: "Via terrestre" }
    { group:44, id:29, text: "Via marittima" }
    { group:44, id:30, text: "Indicatore esercito" }
    { group:44, id:31, text: "Indicatore nemico" }
    { group:44, id:32, text: "Via" }
    { group:44, id:33, text: "Domanda" }
    { group:44, id:34, text: "Costo" }
    { group:44, id:35, text: "Risorse" }
    { group:44, id:36, text: "Vendite" }
    { group:44, id:37, text: "Breve descrizione" }
    { group:44, id:38, text: "Breve descrizione della missione per i giocatori. Storia, obiettivi, consigli, ecc." }
    { group:44, id:39, text: "Fondi iniziali" }
    { group:44, id:40, text: "Richieste" }
    { group:44, id:41, text: "Il nemico è" }
    { group:44, id:42, text: "Invasioni" }
    { group:44, id:43, text: "La capitale fornisce il grano?" }
    { group:44, id:44, text: "Edifici consentiti" }
    { group:44, id:45, text: "Condizioni di vittoria" }
    { group:44, id:46, text: "Modifica" }
    { group:44, id:47, text: "Edifici consentiti" }
    { group:44, id:48, text: "Condizioni di vittoria" }
    { group:44, id:49, text: "Eventi speciali" }
    { group:44, id:50, text: "Cultura necessaria" }
    { group:44, id:51, text: "Prosperità necessaria" }
    { group:44, id:52, text: "Numero di monumenti" }
    { group:44, id:53, text: "Livello del regno necessario" }
    { group:44, id:54, text: "Limite di tempo (sconfitta)" }
    { group:44, id:55, text: "Sopravvivenza (vittoria)" }
    { group:44, id:56, text: "Popolazione per la vittoria" }
    { group:44, id:57, text: "Serve punto terremoto" }
    { group:44, id:58, text: "Punto terremoto OK" }
    { group:44, id:59, text: "0 punti d'ingresso" }
    { group:44, id:60, text: "0 punti persone" }
    { group:44, id:61, text: "0 punti d'uscita" }
    { group:44, id:62, text: "Punti persone impostati" }
    { group:44, id:63, text: "0 punti d'invasione" }
    { group:44, id:64, text: "1 punto d'invasione" }
    { group:44, id:65, text: "punti d'invasione" }
    { group:44, id:66, text: "0 punti fiume" }
    { group:44, id:67, text: "Punti fiume impostati" }
    { group:44, id:68, text: "Dono del Faraone" }
    { group:44, id:69, text: "Indicatore battaglia" }
    { group:44, id:70, text: "Percorso" }
    { group:44, id:71, text: "Ordine" }
    { group:44, id:72, text: "Desideri" }
    { group:44, id:73, text: "Regno" }
    { group:44, id:74, text: "Pietre miliari a" }
    { group:44, id:75, text: "Salva" }
    { group:44, id:76, text: "Terreno impostato" }
    { group:44, id:77, text: "Clima umido" }
    { group:44, id:78, text: "Clima normale" }
    { group:44, id:79, text: "Clima arido" }
    { group:44, id:80, text: "Relitti attivi?" }
    { group:44, id:81, text: "Espansione a" }
    { group:44, id:82, text: "Posizioni espanse" }
    { group:44, id:83, text: "Imposta i livelli di domanda/offerta" }
    { group:44, id:84, text: "Nessuno/a" }
    { group:44, id:85, text: "basso" }
    { group:44, id:86, text: "medio" }
    { group:44, id:87, text: "alto" }
    { group:44, id:88, text: "Condizioni iniziali" }
    { group:44, id:89, text: "Modifica data di inizio" }
    { group:44, id:90, text: "Voce 90 - indicatore" }
    { group:44, id:91, text: "Pietra miliare - 25%" }
    { group:44, id:92, text: "Pietra miliare - 50%" }
    { group:44, id:93, text: "Pietra miliare - 75%" }
    { group:44, id:94, text: "Cambiamenti di domanda" }
    { group:44, id:95, text: "Eventi" }
    { group:44, id:96, text: "Aggiungi evento" }
    { group:44, id:97, text: "Elimina evento" }
    { group:44, id:98, text: "in cammino" }
    { group:44, id:99, text: "scende" }
    { group:44, id:100, text: "sale" }
    { group:44, id:101, text: "domanda per questa merce" }
    { group:44, id:102, text: "inutilizzato 1601" }
    { group:44, id:103, text: "scende di" }
    { group:44, id:104, text: "sale di" }
    { group:44, id:105, text: "evento attivazione non valido" }
    { group:44, id:106, text: "CONSIGLIO: usa i tasti virgola e punto per spostarti rapidamente tra questo e gli altri oggetti." }
    { group:44, id:107, text: "Gioco aperto (senza sconfitta/vittoria)" }
    { group:44, id:108, text: "Livello iniziale" }
    { group:44, id:109, text: "Terreno" }
    { group:44, id:110, text: "Nemici" }
    { group:44, id:111, text: "Invasioni" }
    { group:44, id:112, text: "Nessuna attività militare" }
    { group:44, id:113, text: "Poca attività militare" }
    { group:44, id:114, text: "Attività militare di rilievo" }
    { group:44, id:115, text: "Molta attività militare" }
    { group:44, id:116, text: "Città sotto attacco" }
    { group:44, id:117, text: "Livello" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "Forniture da capitale?" }
    { group:44, id:120, text: "Dimensione mappa" }
    { group:44, id:121, text: "Territorio minuscolo" }
    { group:44, id:122, text: "Territorio piccolo" }
    { group:44, id:123, text: "Territorio medio" }
    { group:44, id:124, text: "Territorio grande" }
    { group:44, id:125, text: "Territorio grandissimo" }
    { group:44, id:126, text: "Territorio enorme" }
    { group:44, id:127, text: "Condizioni di vittoria" }
    { group:44, id:128, text: "Nessuno/a" }
    { group:44, id:129, text: "Cultura" }
    { group:44, id:130, text: "Prosperità" }
    { group:44, id:131, text: "Monumento" }
    { group:44, id:132, text: "  Regno" }
    { group:44, id:133, text: "Popolazione" }
    { group:44, id:134, text: "Massimo di anni" }
    { group:44, id:135, text: "Anni di sopravvivenza" }
    { group:44, id:136, text: "Vai alla città" }
    { group:44, id:137, text: "Serve ingresso fiume" }
    { group:44, id:138, text: "Serve uscita fiume" }
    { group:44, id:139, text: "Evento" }
    { group:44, id:140, text: "mese" }
    { group:44, id:141, text: "tra" }
    { group:44, id:142, text: "e" }
    { group:44, id:143, text: "città" }
    { group:44, id:144, text: "dai punti" }
    { group:44, id:145, text: "ai" }
    { group:44, id:146, text: "quantità" }
    { group:44, id:147, text: "scala" }
    { group:44, id:148, text: "di" }
    { group:44, id:149, text: "entro" }
    { group:44, id:150, text: "mesi" }
    { group:44, id:151, text: "Evento soddisfazione" }
    { group:44, id:152, text: "Evento rifiuto" }
    { group:44, id:153, text: "Evento ritardo" }
    { group:44, id:154, text: "Evento forfeit" }
    { group:44, id:155, text: "Evento battaglia persa" }
    { group:44, id:156, text: "Prossimo evento" }
    { group:44, id:157, text: "Evento singolo" }
    { group:44, id:158, text: "Evento ricorrente" }
    { group:44, id:159, text: "Solo attivato" }
    { group:44, id:160, text: "Attivato da favore" }
    { group:44, id:161, text: "Faraon" }
    { group:44, id:162, text: "Città" }
    { group:44, id:163, text: "Navi da guerra" }
    { group:44, id:164, text: "Impostazioni divinità" }
    { group:44, id:165, text: "Nessun dio patrono" }
    { group:44, id:166, text: "Aggiungi via" }
    { group:44, id:167, text: "Modifica via" }
    { group:44, id:168, text: "Elimina via" }
    { group:44, id:169, text: "Via generale" }
    { group:44, id:170, text: "Via marittima" }
    { group:44, id:171, text: "Via terrestre" }
    { group:44, id:172, text: "Spaziatura" }
    { group:44, id:173, text: "Lunghezza via" }
    { group:44, id:174, text: "Nome" }
    { group:44, id:175, text: "Livello" }
    { group:44, id:176, text: "Complesso templi" }
    { group:44, id:177, text: "Interesse su debito" }
    { group:44, id:178, text: "Impostazioni campi di limo" }
    { group:44, id:179, text: "Data inizio straripamento:" }
    { group:44, id:180, text: "Inizio giugno" }
    { group:44, id:181, text: "Fine giugno" }
    { group:44, id:182, text: "Inizio luglio" }
    { group:44, id:183, text: "Fine luglio" }
    { group:44, id:184, text: "Inizio agosto" }
    { group:44, id:185, text: "Fine agosto" }
    { group:44, id:186, text: "Inizio settembre" }
    { group:44, id:187, text: "Fine settembre" }
    { group:44, id:188, text: "Durata straripamento:" }
    { group:44, id:189, text: "Due mesi" }
    { group:44, id:190, text: "Tre mesi" }
    { group:44, id:191, text: "Quattro mesi" }
    { group:44, id:192, text: "Qualità straripamento:" }
    { group:44, id:193, text: "Assente" }
    { group:44, id:194, text: "Scadente" }
    { group:44, id:195, text: "Mediocre" }
    { group:44, id:196, text: "Buona" }
    { group:44, id:197, text: "Eccellente" }
    { group:44, id:198, text: "Perfetta" }
    { group:44, id:199, text: "Nessuno straripamento" }
    { group:44, id:200, text: "Straripamento perfetto" }
    { group:44, id:201, text: "Scegli monumenti:" }
    { group:44, id:202, text: "Faraone attuale:" }
    { group:44, id:203, text: "Incarnazione giocatore:" }
    { group:44, id:204, text: "Imposta prezzi" }
    { group:44, id:205, text: "Acquisti" }
    { group:44, id:206, text: "Vendite" }
    { group:44, id:207, text: "Accetta" }
    { group:44, id:208, text: "Rifiuta" }
    { group:44, id:209, text: "Ritarda" }
    { group:44, id:210, text: "Livello abitazioni" }
    { group:44, id:211, text: "Prezzi predefiniti" }
    { group:44, id:212, text: "Divinità" }
    { group:44, id:213, text: "1 carro o blocco di pietra = 100 unità" }
    { group:44, id:214, text: "Modifica questa mappa" }
    { group:44, id:215, text: "Gioca questa missione" }
    { group:44, id:216, text: "Liv. difficoltà" }
    { group:44, id:217, text: "Esci" }
    { group:44, id:218, text: "Inizia missione" }
    { group:44, id:219, text: "Annulla" }
    { group:44, id:220, text: "Mostra risultati precedenti" }
    { group:44, id:221, text: "Mostra descrizione missione" }
    { group:44, id:222, text: "Il regno" }
    { group:44, id:223, text: "Predefinita" }
    { group:44, id:224, text: "Punto ingresso OK" }
    { group:44, id:225, text: "Punto uscita OK" }
    { group:44, id:226, text: "1 punto fiume OK" }
    { group:44, id:227, text: "Gioc. contro Egitto:" }
    { group:45, id:0, text: "Opzioni velocità" }
    { group:45, id:1, text: "Annulla" }
    { group:45, id:2, text: "Gioco" }
    { group:45, id:3, text: "Scorrimento" }
    { group:45, id:4, text: "OK" }
    { group:45, id:5, text: "Opzioni sonore" }
    { group:45, id:6, text: "Musica disattivata" }
    { group:45, id:7, text: "Musica attivata" }
    { group:46, id:0, text: "Opzioni sonore" }
    { group:46, id:1, text: "Musica disattivata" }
    { group:46, id:2, text: "Musica attivata" }
    { group:46, id:3, text: "Dialogo disattivato" }
    { group:46, id:4, text: "Dialogo attivato" }
    { group:46, id:5, text: "Effetti sonori disattivati" }
    { group:46, id:6, text: "Effetti sonori attivati" }
    { group:46, id:7, text: "Suoni della città disattivati" }
    { group:46, id:8, text: "Suoni della città attivati" }
    { group:46, id:9, text: "Annulla" }
    { group:46, id:10, text: "Stato attuale dell'audio" }
    { group:46, id:11, text: "Volume" }
    { group:46, id:12, text: "OK" }
    { group:47, id:0, text: "Una città straniera" }
    { group:47, id:1, text: "La nostra città!" }
    { group:47, id:2, text: "Questa rotta commerciale non è ancora aperta" }
    { group:47, id:3, text: "Costo per aprirla" }
    { group:47, id:4, text: "Acquisti" }
    { group:47, id:5, text: "Vendite" }
    { group:47, id:6, text: "per aprire una via commerciale terrestre" }
    { group:47, id:7, text: "per aprire una via commerciale fluviale" }
    { group:47, id:8, text: "Al supervisore commerciale" }
    { group:47, id:9, text: "Clicca su una città per ottenere informazioni." }
    { group:47, id:10, text: "Acquistato" }
    { group:47, id:11, text: "Venduto" }
    { group:47, id:12, text: "di" }
    { group:47, id:13, text: "Una città egiziana" }
    { group:47, id:14, text: "Una città catturata" }
    { group:47, id:15, text: "Un esercito nemico, che minaccia una città del Regno" }
    { group:47, id:16, text: "Il tuo esercito, in marcia per liberare una città del Regno" }
    { group:47, id:17, text: "Il tuo esercito, di ritorno nella tua città" }
    { group:47, id:18, text: "Il luogo di recenti scontri con barbari invasori" }
    { group:47, id:19, text: "La città del Faraone" }
    { group:48, id:0, text: "Pennello minuscolo" }
    { group:48, id:1, text: "Pennello piccolo" }
    { group:48, id:2, text: "Pennello medio" }
    { group:48, id:3, text: "Pennello grande" }
    { group:48, id:4, text: "Pennello enorme" }
    { group:48, id:5, text: "Punto d'ingresso" }
    { group:48, id:6, text: "Punto d'uscita" }
    { group:48, id:7, text: "Innalza terreno" }
    { group:48, id:8, text: "Abbassa terreno" }
    { group:48, id:9, text: "Rampa d'accesso" }
    { group:48, id:10, text: "Punto invasione 1 (terra)" }
    { group:48, id:11, text: "Punto invasione 2 (terra)" }
    { group:48, id:12, text: "Punto invasione 3 (terra)" }
    { group:48, id:13, text: "Punto invasione 4 (terra)" }
    { group:48, id:14, text: "Punto invasione 5 (terra)" }
    { group:48, id:15, text: "Punto invasione 6 (terra)" }
    { group:48, id:16, text: "Punto invasione 7 (terra)" }
    { group:48, id:17, text: "Punto invasione 8 (terra)" }
    { group:48, id:18, text: "Entrata fiume" }
    { group:48, id:19, text: "Uscita fiume" }
    { group:48, id:20, text: "Capanna dei nativi" }
    { group:48, id:21, text: "Centro dei nativi" }
    { group:48, id:22, text: "Campo dei nativi" }
    { group:48, id:23, text: "Punto di pesca 1" }
    { group:48, id:24, text: "Punto di pesca 2" }
    { group:48, id:25, text: "Punto di pesca 3" }
    { group:48, id:26, text: "Punto di pesca 4" }
    { group:48, id:27, text: "Punto di pesca 5" }
    { group:48, id:28, text: "Punto di pesca 6" }
    { group:48, id:29, text: "Punto di pesca 7" }
    { group:48, id:30, text: "Punto di pesca 8" }
    { group:48, id:31, text: "Punto predatori 1" }
    { group:48, id:32, text: "Punto predatori 2" }
    { group:48, id:33, text: "Punto predatori 3" }
    { group:48, id:34, text: "Punto predatori 4" }
    { group:48, id:35, text: "Acqua" }
    { group:48, id:36, text: "Campo di limo" }
    { group:48, id:37, text: "Canale irrigazione" }
    { group:48, id:38, text: "Paludi" }
    { group:48, id:39, text: "Punto di preda 1" }
    { group:48, id:40, text: "Punto di preda 2" }
    { group:48, id:41, text: "Punto di preda 3" }
    { group:48, id:42, text: "Punto di preda 4" }
    { group:48, id:43, text: "Roccia normale" }
    { group:48, id:44, text: "Roccia mineraria" }
    { group:48, id:45, text: "Roccia normale" }
    { group:48, id:46, text: "Roccia speciale" }
    { group:48, id:47, text: "Dune di sabbia" }
    { group:48, id:48, text: "Punto invasione 9 (mare)" }
    { group:48, id:49, text: "Punto invasione 10 (mare)" }
    { group:48, id:50, text: "Punto invasione 11 (mare)" }
    { group:48, id:51, text: "Punto invasione 12 (mare)" }
    { group:48, id:52, text: "Punto invasione 13 (mare)" }
    { group:48, id:53, text: "Punto invasione 14 (mare)" }
    { group:48, id:54, text: "Punto invasione 15 (mare)" }
    { group:48, id:55, text: "Punto invasione 16 (mare)" }
    { group:48, id:56, text: "Punto di sbarco 1" }
    { group:48, id:57, text: "Punto di sbarco 2" }
    { group:48, id:58, text: "Punto di sbarco 3" }
    { group:48, id:59, text: "Predatore tipo 1" }
    { group:48, id:60, text: "Predatore tipo 2" }
    { group:49, id:0, text: "Erba" }
    { group:49, id:1, text: "Alberi" }
    { group:49, id:2, text: "Acqua" }
    { group:49, id:3, text: "Terremoto" }
    { group:49, id:4, text: "Boscaglia" }
    { group:49, id:5, text: "Rocce" }
    { group:49, id:6, text: "Prato" }
    { group:49, id:7, text: "Altopiano" }
    { group:49, id:8, text: "Dimensione pennello" }
    { group:49, id:9, text: "Rampa d'accesso" }
    { group:49, id:10, text: "Strada" }
    { group:49, id:11, text: "Innalza terreno" }
    { group:49, id:12, text: "Abbassa terreno" }
    { group:49, id:13, text: "Punto d'invasione" }
    { group:49, id:14, text: "Punto di migrazione" }
    { group:49, id:15, text: "Punto d'ingresso" }
    { group:49, id:16, text: "Punto d'uscita" }
    { group:49, id:17, text: "Punto fiume" }
    { group:49, id:18, text: "Ingresso fiume" }
    { group:49, id:19, text: "Uscita fiume" }
    { group:49, id:20, text: "Nativi" }
    { group:49, id:21, text: "Capanna dei nativi" }
    { group:49, id:22, text: "Centro dei nativi" }
    { group:49, id:23, text: "Campo dei nativi" }
    { group:49, id:24, text: "Acque pescose" }
    { group:49, id:25, text: "Punto predatori" }
    { group:49, id:26, text: "Campo di limo" }
    { group:49, id:27, text: "Irrigazione" }
    { group:49, id:28, text: "Preda" }
    { group:49, id:29, text: "Paludi" }
    { group:49, id:30, text: "Dune di sabbia" }
    { group:49, id:31, text: "Punto di sbarco" }
    { group:49, id:32, text: "Predatore" }
    { group:49, id:33, text: "Rupe" }
    { group:50, id:0, text: "Supervisore del lavoro" }
    { group:50, id:1, text: "Produzione e distribuzione cibo" }
    { group:50, id:2, text: "Industria e commercio" }
    { group:50, id:3, text: "Intrattenimento" }
    { group:50, id:4, text: "Religione" }
    { group:50, id:5, text: "Istruzione" }
    { group:50, id:6, text: "Igiene e sanità" }
    { group:50, id:7, text: "Infrastrutture" }
    { group:50, id:8, text: "Governo" }
    { group:50, id:9, text: "Armamento" }
    { group:50, id:10, text: "Necessario" }
    { group:50, id:11, text: "Presente" }
    { group:50, id:12, text: "Forza lavoro impiegata" }
    { group:50, id:13, text: "Forza lavoro disoccupata (" }
    { group:50, id:14, text: "Salario/10" }
    { group:50, id:15, text: "Deben" }
    { group:50, id:16, text: "meno della tariffa del Regno di" }
    { group:50, id:17, text: "più della tariffa del Regno di" }
    { group:50, id:18, text: "(il Regno paga" }
    { group:50, id:19, text: "Costo annuale stimato:" }
    { group:50, id:20, text: "Bloccato" }
    { group:50, id:21, text: "Priorità" }
    { group:50, id:22, text: "Settore" }
    { group:50, id:23, text: "Necessario" }
    { group:50, id:24, text: "Presente" }
    { group:50, id:25, text: "Livello di priorità." }
    { group:50, id:26, text: "Nessuna priorità." }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Stato dell'esercito" }
    { group:51, id:1, text: "Vai alla" }
    { group:51, id:2, text: "compagnia" }
    { group:51, id:3, text: "Ritorna" }
    { group:51, id:4, text: "al forte" }
    { group:51, id:5, text: "Regno" }
    { group:51, id:6, text: "imperiale" }
    { group:51, id:7, text: "in" }
    { group:51, id:8, text: "Non sono segnalate minacce per la città." }
    { group:51, id:9, text: "Allarme! Truppe nemiche si avvicinano alla città." }
    { group:51, id:10, text: "I nostri nemici sono in vista della città." }
    { group:51, id:11, text: "Un battaglione di truppe Faraon è alle tue porte." }
    { group:51, id:12, text: "Non abbiamo alcuna richiesta di aiuto in tutto il Regno." }
    { group:51, id:13, text: "Alcune nostre truppe sono richieste altrove nel Regno." }
    { group:51, id:14, text: "Battaglione in marcia per salvare una città del Regno." }
    { group:51, id:15, text: "Il nostro battaglione sta tornando in città." }
    { group:51, id:16, text: "Non hai alcuna compagnia da comandare. Devi prima costruire un forte per ospitare una nuova compagnia." }
    { group:51, id:17, text: "Esperienza" }
    { group:51, id:18, text: "Compagnia" }
    { group:51, id:19, text: "Stato navi" }
    { group:51, id:20, text: "nave da guerra" }
    { group:51, id:21, text: "al porto" }
    { group:51, id:22, text: "Forza" }
    { group:51, id:23, text: "Scafo" }
    { group:51, id:24, text: "Stato equipaggio" }
    { group:51, id:25, text: "Non hai alcuna nave da guerra da comandare. Devi prima costruire un molo per una nuova nave da guerra." }
    { group:51, id:26, text: "Alcune nostre navi sono richieste altrove." }
    { group:51, id:27, text: "La compagnia sta navigando per salvare una città egizia." }
    { group:51, id:28, text: "La compagnia sta tornando alla nostra città via mare." }
    { group:51, id:29, text: "all'estero" }
    { group:51, id:30, text: "Invia" }
    { group:51, id:31, text: "ora" }
    { group:51, id:32, text: "e" }
    { group:52, id:0, text: "Livello del Regno" }
    { group:52, id:1, text: "Risparmi di" }
    { group:52, id:2, text: "Dona alla città" }
    { group:52, id:3, text: "Deben al mese" }
    { group:52, id:4, text: "Salario dell'Anziano del villaggio:" }
    { group:52, id:5, text: "Salario del Nobile del villaggio:" }
    { group:52, id:6, text: "Salario dello Studioso reale:" }
    { group:52, id:7, text: "Salario dello Scriba reale:" }
    { group:52, id:8, text: "Salario del Giudice reale:" }
    { group:52, id:9, text: "Salario del Sindaco reale:" }
    { group:52, id:10, text: "Salario del Governatore reale:" }
    { group:52, id:11, text: "Salario del Nomarca:" }
    { group:52, id:12, text: "Salario del Cancelliere:" }
    { group:52, id:13, text: "Salario del Consigliere:" }
    { group:52, id:14, text: "Salario del Faraone:" }
    { group:52, id:15, text: "Decidi il salario" }
    { group:52, id:16, text: "Dai soldi alla città" }
    { group:52, id:17, text: "La donazione è" }
    { group:52, id:18, text: "Cedi soldi" }
    { group:52, id:19, text: "Tutti" }
    { group:52, id:20, text: "Richieste attuali" }
    { group:52, id:22, text: "\"Il popolo vuole consegnare i tuoi resti agli sciacalli.\"" }
    { group:52, id:23, text: "\"Anche i buffoni si fanno beffe di te e il tuo nome è pronunciato con disprezzo.\"" }
    { group:52, id:24, text: "\"Si mormora che la tua presenza causi la malaria.\"" }
    { group:52, id:25, text: "\"I farmacisti affermano che il tuo nome è più amaro di qualsiasi erba medicinale.\"" }
    { group:52, id:26, text: "\"Le mamme usano il tuo nome per spaventare i loro figli.\"" }
    { group:52, id:27, text: "\"Pronunciare il tuo nome è segno di scortesia.\"" }
    { group:52, id:28, text: "\"La tua reputazione è zero, la tua famiglia si vergogna.\"" }
    { group:52, id:29, text: "\"Il tuo nome si conosce in entrambi i Regni e fa molto ridere.\"" }
    { group:52, id:30, text: "\"La gente che conta conosce te e la tua storia, ma tende a insultarti.\"" }
    { group:52, id:31, text: "\"Pochi conoscono le tue gesta, comunque poco impressionanti.\"" }
    { group:52, id:32, text: "\"I pochi che conoscono il tuo nome non ti considerano molto.\"" }
    { group:52, id:33, text: "\"I tuoi modesti risultati non sono famosi, ma chi li conosce li apprezza.\"" }
    { group:52, id:34, text: "\"La gente che conta conosce la tua storia e generalmente approva i tuoi risultati.\"" }
    { group:52, id:35, text: "\"Il tuo nome è benconosciuto e applaudito in entrambi i Regni.\"" }
    { group:52, id:36, text: "\"La tua reputazione è buona e, spesso, sei contattato da parenti semi-sconosciuti.\"" }
    { group:52, id:37, text: "\"Il suono del tuo nome rincuora chi lo sente.\"" }
    { group:52, id:38, text: "\"Tutte le mamme del Regno chiamano i loro figli con il tuo nome.\"" }
    { group:52, id:39, text: "\"Molte città egizie pensano di indire una festività in tuo onore.\"" }
    { group:52, id:40, text: "\"La danza più popolare in tutto l'Egitto illustra le tue imprese.\"" }
    { group:52, id:41, text: "\"I musici compongono canzoni in tuo onore e il tuo nome è iscritto su ogni pubblica piazza.\"" }
    { group:52, id:42, text: "\"Tutti gli Egizi desiderano servirti per l'eternità\"" }
    { group:52, id:43, text: "in deposito merci" }
    { group:52, id:44, text: "nella tesoreria cittadina" }
    { group:52, id:45, text: "Persone" }
    { group:52, id:46, text: "Armi" }
    { group:52, id:47, text: "Clicca qui per inviare la richiesta." }
    { group:52, id:49, text: "Invia un dono" }
    { group:52, id:51, text: "Una tavoletta babilonese" }
    { group:52, id:52, text: "Tappeti persiani" }
    { group:52, id:53, text: "Antiche iscrizioni" }
    { group:52, id:54, text: "Avorio africano" }
    { group:52, id:55, text: "Un gruppo di schiavi addestrati" }
    { group:52, id:56, text: "Stalloni arabi" }
    { group:52, id:57, text: "Uno schiavo educato" }
    { group:52, id:58, text: "Guardie del corpo libiche" }
    { group:52, id:59, text: "Pantere e giraffe" }
    { group:52, id:60, text: "Uno scrigno di zaffiri" }
    { group:52, id:61, text: "Un carro colmo d'oro" }
    { group:52, id:62, text: "Una nave di cedro libanese" }
    { group:52, id:71, text: "Attenzione: concederti un salario superiore al tuo livello non impressionerà nessuno." }
    { group:52, id:72, text: "Invia truppe per proteggere" }
    { group:52, id:73, text: "Una piccola forza attaccherà in" }
    { group:52, id:74, text: "Una forza di medie dimensioni attaccherà in" }
    { group:52, id:75, text: "Una grande forza attaccherà in" }
    { group:52, id:76, text: "Sei libero di decidere autonomamente il tuo salario" }
    { group:52, id:77, text: "Il Palazzo ora ti proibisce di percepire un salario, in quanto continui a governare per tua libera scelta." }
    { group:52, id:78, text: "Devi costruire una magione per ottenere un salario personale." }
    { group:52, id:79, text: "deben persi quest'anno per furti." }
    { group:52, id:80, text: "Invia truppe marittime per proteggere" }
    { group:52, id:81, text: "Supervisore politico per" }
    { group:53, id:0, text: "Supervisore livelli" }
    { group:53, id:1, text: "Cultura" }
    { group:53, id:2, text: "Prosperità" }
    { group:53, id:3, text: "Monumento" }
    { group:53, id:4, text: "Regno" }
    { group:53, id:5, text: "richiesto" }
    { group:53, id:6, text: "Popolazione:" }
    { group:53, id:7, text: "Nessun obiettivo di popolazione" }
    { group:53, id:8, text: "Clicca su un livello per ottenere informazioni." }
    { group:53, id:9, text: "Hai troppo pochi giocolieri in città. Creane altri per aumentare il livello attuale." }
    { group:53, id:10, text: "Hai troppo pochi musicanti in città. Creane altri per aumentare il livello attuale." }
    { group:53, id:11, text: "Hai troppo pochi danzatori in città. Creane altri per aumentare il livello attuale." }
    { group:53, id:12, text: "Hai troppo poche taverne senet in città. Costruiscine altre per aumentare il livello attuale." }
    { group:53, id:13, text: "Ci sono pochi zoo in città. Se possibile costruiscine altri per migliorare il livello." }
    { group:53, id:14, text: "Nella tua città ci sono pochi luoghi di culto. Costruiscine altri per aumentare questo livello." }
    { group:53, id:15, text: "Hai troppo poche Scuole degli Scribi in città. Costruiscine altre per aumentare il livello attuale." }
    { group:53, id:16, text: "Hai poche biblioteche nella tua città. Se ne costruirai altre, migliorerai questo livello." }
    { group:53, id:17, text: "Case con disponibilità dentista insufficienti. Una maggiore disponibilità migliorerà il livello attuale." }
    { group:53, id:18, text: "Case con disponibilità medici insufficienti. Una maggiore disponibilità migliorerà il livello attuale." }
    { group:53, id:19, text: "Case con disponibilità camere mortuarie insufficienti. Una maggiore disponibilità migliorerà il livello attuale." }
    { group:53, id:20, text: "- Livello in aumento." }
    { group:53, id:21, text: "- Livello in diminuzione." }
    { group:53, id:22, text: "- Livello stabile." }
    { group:53, id:23, text: "La qualità generale delle abitazioni delle tue città mantiene basso questo livello. Migliorando le abitazioni potrai aumentare il valore." }
    { group:53, id:24, text: "Nell'ultimo anno la città ha perso dei soldi - questo ha ridotto il suo livello di prosperità." }
    { group:53, id:25, text: "L'elevata disoccupazione della tua città provoca un basso livello di prosperità." }
    { group:53, id:26, text: "Pagare salari inferiori alle tariffe del Regno rovina la fama di prosperità della tua città." }
    { group:53, id:27, text: "L'alta concentrazione di mendicanti e ambulanti danno alla tua città un'apparenza povera." }
    { group:53, id:28, text: "La tua incapacità a pagare i tributi annuali al Faraone segna la tua città come fallimentare." }
    { group:53, id:29, text: "La mancanza di varietà di cibo danneggia il livello di prosperità." }
    { group:53, id:30, text: "La mancanza di lavoro danneggia il livello di prosperità." }
    { group:53, id:31, text: "La città è più prospera quando le entrate dell'esportazione superano quelle dell'importazione." }
    { group:53, id:32, text: "Il livello della tua città sta diminuendo. Paga i tributi annuali, assegnati un salario ragionevole e rispondi alle richieste del Faraone e delle altre città del Regno." }
    { group:53, id:33, text: "Il tuo salario è così elevato da far infuriare il Faraone e abbassare il livello del Regno." }
    { group:53, id:34, text: "La tua continua inadempienza al pagamento dei tributi abbassa il livello della tua città." }
    { group:53, id:35, text: "La richiesta che non hai soddisfatto danneggia il prestigio della tua città in tutto il Regno." }
    { group:53, id:36, text: "Il salario che ti sei assegnato, troppo superiore al tuo livello, riduce la tua reputazione nel Regno." }
    { group:53, id:37, text: "Per due anni di seguito non hai pagato i tributi e il livello della tua città ne patisce." }
    { group:53, id:38, text: "La mancata soddisfazione della recente richiesta, per volontà o impossibilità, danneggia la tua posizione. Se l'avessi soddisfatta, il livello del Regno sarebbe aumentato." }
    { group:53, id:39, text: "Il tuo salario è troppo elevato per la tua posizione. Se lo riduci un po', il livello del Regno aumenterà." }
    { group:53, id:40, text: "Quest'anno, non hai potuto pagare i tributi e il tuo livello del regno è sceso. Alla fine dell'anno, tieni sempre un po' di soldi nel tesoro per pagare regolarmente i tributi." }
    { group:53, id:41, text: "Il tuo salario è troppo elevato per la tua posizione. Faresti bene a ridurlo un po'." }
    { group:53, id:42, text: "La lentezza con cui cerchi di raggiungere gli obiettivi ha ridotto il tuo livello del Regno." }
    { group:53, id:43, text: "La tua insistenza nell'assegnarti un salario superiore alla tua posizione è guardata con sospetto." }
    { group:53, id:44, text: "Il tuo livello del Regno è aumentato rispetto allo scorso anno." }
    { group:53, id:45, text: "Il tuo livello del Regno è rimasto immutato rispetto allo scorso anno." }
    { group:53, id:46, text: "Il livello di pace aumenta per ogni anno senza rivolte o invasioni che abbiano provocato danni alla città." }
    { group:53, id:47, text: "Questa provincia ha vissuto un breve periodo di pace, ma i cittadini non si sentono ancora sicuri. Servono altri anni di tranquillità." }
    { group:53, id:48, text: "Gli abitanti di questa provincia si sentono ragionevolmente sicuri e con il passare del tempo le cose miglioreranno ancora." }
    { group:53, id:49, text: "Questa provincia è rispettosa delle leggi e, con il passare del tempo, diverrà un luogo pacifico." }
    { group:53, id:50, text: "In generale questa provincia è tranquilla, i problemi sono molto limitati. La popolazione è decisamente soddisfatta!" }
    { group:53, id:51, text: "La tranquillità e la sicurezza della tua provincia sono leggendarie. Gli altri governatori stanno pensando di venire a vivere da te!" }
    { group:53, id:52, text: "I recenti tumulti in città hanno influenzato negativamente il livello di pace." }
    { group:53, id:53, text: "I soldati nemici nella tua provincia non aiutano certo il tuo livello di pace!" }
    { group:53, id:54, text: "I vicini battaglioni del Faraone spaventano la tua gente e danneggiano il tuo livello di Pace." }
    { group:53, id:55, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:56, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:57, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:58, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:59, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:60, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:61, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:62, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:63, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:64, text: "Il supervisore ai monumenti e il capo cantiere (clicca col destro su un monumento) possono consigliarti." }
    { group:53, id:65, text: "Questa città è la più acculturata di tutto l'Egitto!" }
    { group:53, id:66, text: "L'incredibile prosperità di questa città è la favola di tutto l'Egitto!" }
    { group:53, id:67, text: "Questa città ha i monumenti più belli di tutto l'Egitto!" }
    { group:53, id:68, text: "Il tuo Regno ha il livello più elevato di tutto l'Egitto!" }
    { group:53, id:69, text: "Supervisore commerciale" }
    { group:54, id:1, text: "clicca su un bene da commerciare, accumulare o per variarne la produzione" }
    { group:54, id:2, text: "Mostra prezzi" }
    { group:54, id:3, text: "Accumulo" }
    { group:54, id:4, text: "Non in commercio" }
    { group:54, id:5, text: "Importazione fino a" }
    { group:54, id:6, text: "Esportazione oltre" }
    { group:54, id:7, text: "Non ci sono industrie nella città" }
    { group:54, id:8, text: "Industria in funzione nella città" }
    { group:54, id:9, text: "Industrie in funzione nella città" }
    { group:54, id:10, text: "Industria momentaneamente chiusa nella città" }
    { group:54, id:11, text: "Industrie momentaneamente chiuse nella città" }
    { group:54, id:12, text: "Funzionanti" }
    { group:54, id:13, text: "Industria inattiva nella città" }
    { group:54, id:14, text: "Industrie inattive nella città" }
    { group:54, id:15, text: "immagazzinati nel deposito merci della città." }
    { group:54, id:16, text: "L'industria è in funzione" }
    { group:54, id:17, text: "L'industria non è in funzione" }
    { group:54, id:18, text: "Non in commercio" }
    { group:54, id:19, text: "Importazione fino a" }
    { group:54, id:20, text: "Esportazione oltre" }
    { group:54, id:21, text: "Prezzi medi egizi" }
    { group:54, id:22, text: "Acquisto" }
    { group:54, id:23, text: "Vendita" }
    { group:54, id:24, text: "Non ci sono rotte commerciali aperte per queste merci." }
    { group:54, id:25, text: "Queste merci sono disponibili solo dietro importazione." }
    { group:54, id:26, text: "Accumulo di risorse" }
    { group:54, id:27, text: "Clicca qui per disattivare l'accumulo" }
    { group:54, id:28, text: "Risorsa utilizzata e commerciata" }
    { group:54, id:29, text: "Clicca qui per accumularla" }
    { group:54, id:30, text: "Vai alla mappa del Regno" }
    { group:54, id:31, text: "Disponibile per l'importazione" }
    { group:54, id:32, text: "Disponibile per l'esportazione" }
    { group:54, id:33, text: "Disponibile per l'import/export" }
    { group:54, id:34, text: "Apri via commerciale per importare" }
    { group:54, id:35, text: "Apri via commerciale per esportare" }
    { group:54, id:36, text: "Apri via commerciale import/export" }
    { group:54, id:37, text: "Importa il necessario" }
    { group:54, id:38, text: "Esporta solo le eccedenze" }
    { group:54, id:39, text: "Clicca per importare" }
    { group:54, id:40, text: "Clicca per esportare" }
    { group:54, id:41, text: "Nessun venditore per questa risorsa" }
    { group:54, id:42, text: "Nessun acquirente per questa risorsa" }
    { group:54, id:43, text: "Importa quando necessario" }
    { group:54, id:44, text: "Esporta eccedenze" }
    { group:54, id:45, text: "multiplo" }
    { group:54, id:46, text: "Mostra stato commercio" }
    { group:54, id:47, text: "per arma" }
    { group:54, id:48, text: "per carro" }
    { group:54, id:49, text: "per blocco" }
    { group:54, id:50, text: "per 100 pezzi" }
    { group:55, id:0, text: "Popolazione - storia" }
    { group:55, id:1, text: "Popolazione - censimento" }
    { group:55, id:2, text: "Popolazione - società" }
    { group:55, id:3, text: "Storia" }
    { group:55, id:4, text: "Censimento" }
    { group:55, id:5, text: "Società" }
    { group:55, id:6, text: "Popolazione cittadina nel tempo." }
    { group:55, id:7, text: "Composizione della popolazione per età (in anni)." }
    { group:55, id:8, text: "Composizione della popolazione per guadagni." }
    { group:55, id:9, text: "Abitanti dei capanni" }
    { group:55, id:10, text: "Abitanti delle tenute" }
    { group:55, id:11, text: "La capitale fornisce tutto il cibo per questa città" }
    { group:55, id:12, text: "- cibo per" }
    { group:55, id:13, text: "- un po' di cibo per il mese prossimo" }
    { group:55, id:14, text: "- non c'è cibo per il mese prossimo" }
    { group:55, id:15, text: "- pochissimo cibo per il mese prossimo" }
    { group:55, id:16, text: "Le abitazioni correnti possono contenere" }
    { group:55, id:17, text: "altre persone." }
    { group:55, id:18, text: "immigrati arrivati questo mese." }
    { group:55, id:19, text: "immigrato arrivato questo mese." }
    { group:55, id:20, text: "La mancanza di case limita l'immigrazione." }
    { group:55, id:21, text: "I salari bassi riducono l'immigrazione nella nostra città." }
    { group:55, id:22, text: "La disoccupazione riduce il numero degli immigrati." }
    { group:55, id:23, text: "La mancanza di cibo nei granai limita l'immigrazione." }
    { group:55, id:24, text: "Le tasse elevate tengono lontana la gente dalla nostra città." }
    { group:55, id:25, text: "In generale, la gente arriva o intende venire nella nostra città." }
    { group:55, id:26, text: "In generale, la gente si allontana dalla nostra città." }
    { group:55, id:27, text: "La mancanza di lavoro spinge la gente a emigrare." }
    { group:55, id:28, text: "La gente si trasferisce altrove in cerca di salari più alti." }
    { group:55, id:29, text: "A causa delle tasse elevate molte persone lasciano la città." }
    { group:55, id:30, text: "In generale, la popolazione della tua città è stabile." }
    { group:55, id:31, text: "I numeri degli immigrati e degli emigranti si equivalgono." }
    { group:55, id:32, text: "Le pessime case scoraggiano gli immigranti, anche se la città è ricca." }
    { group:55, id:33, text: "Nessuno vuole vivere nella nostra città." }
    { group:55, id:34, text: "Produciamo o importiamo cibo a sufficienza per circa" }
    { group:55, id:35, text: "     persone." }
    { group:55, id:36, text: "Mangiamo molto più di quanto produciamo." }
    { group:55, id:37, text: "Consumiamo più di quanto produciamo, aspettati una riduzione della città" }
    { group:55, id:38, text: "Mangiamo molto più di quanto produciamo, ma la città tende a crescere." }
    { group:55, id:39, text: "Al momento, mangiamo più di quanto produciamo." }
    { group:55, id:40, text: "Mangiamo più di quanto produciamo, probabilmente la città si ridurrà." }
    { group:55, id:41, text: "Mangiamo più di quanto produciamo, ma la popolazione tende a crescere." }
    { group:55, id:42, text: "Al momento, mangiamo un po' più di quanto produciamo." }
    { group:55, id:43, text: "Mangiamo un po' più di quanto produciamo, quindi la città si ridurrà." }
    { group:55, id:44, text: "Mangiamo un po' più di quanto produciamo, ma la città tende a crescere." }
    { group:55, id:45, text: "Al momento, produciamo il minimo per sfamare tutti." }
    { group:55, id:46, text: "La produzione copre i consumi, ma la città tende a ridursi." }
    { group:55, id:47, text: "La produzione copre i consumi, la città tende a crescere." }
    { group:55, id:48, text: "Al momento, produciamo un po' più di quanto mangiamo." }
    { group:55, id:49, text: "Produciamo un po' in eccedenza, ma la città tende a ridursi." }
    { group:55, id:50, text: "Produciamo un po' in eccedenza, la popolazione tende a crescere." }
    { group:55, id:51, text: "Al momento, produciamo molto più di quanto mangiamo." }
    { group:55, id:52, text: "Produciamo più di quanto mangiamo, ma la città tende a ridursi." }
    { group:55, id:53, text: "Produciamo più di quanto mangiamo e la popolazione tende a crescere." }
    { group:56, id:0, text: "Supervisore della sanità" }
    { group:56, id:1, text: "libero" }
    { group:56, id:2, text: "Nessuna" }
    { group:56, id:3, text: "Funzionanti" }
    { group:56, id:4, text: "Cure per" }
    { group:56, id:5, text: "Copertura cittadina" }
    { group:56, id:6, text: "pazienti" }
    { group:56, id:7, text: "Ad alcune zone della città occorre la disponibilità di medici." }
    { group:56, id:8, text: "Alcune zone della città vogliono più medici." }
    { group:56, id:9, text: "Alcune zone bene della città vogliono i dentisti. Un dentista di zona aumenta lo status del vicinato." }
    { group:56, id:10, text: "Più zone della città richiedono dentisti. Man mano che la tua città diventa più ricca, i cittadini che possono permettersi dei denti d'avorio sono sempre di più." }
    { group:56, id:11, text: "Alcune zone della città richiedono la disponibilità di una farmacia." }
    { group:56, id:12, text: "Sempre più persone richiedono farmacie." }
    { group:56, id:13, text: "Lo sviluppo in alcuni quartieri è danneggiato dalla mancanza di copertura da parte delle camere mortuarie." }
    { group:56, id:14, text: "I cittadini richiedono più camere mortuarie per preparare i loro morti all'altro mondo." }
    { group:56, id:15, text: "Al momento non ci sono richieste per strutture sanitarie o mediche. Con lo sviluppo della città, però, la gente si aspetta la disponibilità di cure mediche e, in seguito, di cure dentistiche e poi ancora altri medici!" }
    { group:56, id:16, text: "Nella tua piccola città non si è ancora manifestato alcun problema sanitario." }
    { group:56, id:17, text: "La tua città è in condizioni igieniche terribili Presto scoppieranno delle pestilenze!" }
    { group:56, id:18, text: "L'igiene cittadina è terribile! La malattia è quasi inevitabile." }
    { group:56, id:19, text: "L'igiene cittadina è pessima. Più addetti alla salute pubblica possono migliorare la situazione." }
    { group:56, id:20, text: "L'igiene cittadina è scarsa. Più cibo e strutture mediche possono migliorarla." }
    { group:56, id:21, text: "L'igiene cittadina è sotto la media. Assicurati che i cittadini abbiano cibo e disponibilità di cure mediche." }
    { group:56, id:22, text: "L'igiene cittadina è nella media. Le infezioni sono sotto controllo e la gente mangia a sufficienza." }
    { group:56, id:23, text: "L'igiene cittadina è buona. I cittadini soffrono solo di disturbi minori." }
    { group:56, id:24, text: "L'igiene cittadina è eccellente. Le strutture funzionano al meglio." }
    { group:56, id:25, text: "L'igiene cittadina è eccellente. Le cure sono dispensate all'istante." }
    { group:56, id:26, text: "L'igiene cittadina è quasi perfetta, le strutture mediche sono in pratica vuote." }
    { group:56, id:27, text: "L'igiene cittadina è perfetta. I tuoi medici passano il tempo giocando nelle Taverne." }
    { group:56, id:28, text: "L'igiene cittadina è disastrosa." }
    { group:56, id:29, text: "L'igiene cittadina è terribile." }
    { group:56, id:30, text: "L'igiene cittadina è pessima." }
    { group:56, id:31, text: "L'igiene cittadina è carente." }
    { group:56, id:32, text: "L'igiene cittadina è insufficiente." }
    { group:56, id:33, text: "L'igiene cittadina è media." }
    { group:56, id:34, text: "L'igiene cittadina è buona." }
    { group:56, id:35, text: "L'igiene cittadina è molto buona." }
    { group:56, id:36, text: "L'igiene cittadina è eccellente." }
    { group:56, id:37, text: "L'igiene cittadina è quasi perfetta." }
    { group:56, id:38, text: "L'igiene cittadina è perfetta." }
    { group:56, id:39, text: "Medici" }
    { group:56, id:40, text: "Dentisti" }
    { group:56, id:41, text: "Farmacie" }
    { group:56, id:42, text: "Camere mortuarie" }
    { group:56, id:43, text: "Scarsa" }
    { group:56, id:44, text: "Molto scadente" }
    { group:56, id:45, text: "Scadente" }
    { group:56, id:46, text: "Sotto la media" }
    { group:56, id:47, text: "Media" }
    { group:56, id:48, text: "Media" }
    { group:56, id:49, text: "Sopra la media" }
    { group:56, id:50, text: "Buona" }
    { group:56, id:51, text: "Molto buona" }
    { group:56, id:52, text: "Eccellente" }
    { group:56, id:53, text: "Perfetta" }
    { group:56, id:54, text: "O" }
    { group:56, id:55, text: "Poche" }
    { group:56, id:56, text: "Alcune" }
    { group:56, id:57, text: "Parecchie" }
    { group:56, id:58, text: "Molte" }
    { group:56, id:59, text: "Farmacie funzionano per proteggere la città dalla malaria." }
    { group:56, id:60, text: "pestilenze riportate in questo mese." }
    { group:56, id:61, text: "varietà di cibo nella tua città." }
    { group:57, id:0, text: "Supervisore all'istruzione" }
    { group:57, id:1, text: "Funzionanti" }
    { group:57, id:2, text: "Possono educare" }
    { group:57, id:3, text: "Copertura cittadina" }
    { group:57, id:4, text: "Bambini" }
    { group:57, id:5, text: "Giovani" }
    { group:57, id:6, text: "Persone" }
    { group:57, id:7, text: "Nessuna" }
    { group:57, id:8, text: "Scarsa" }
    { group:57, id:9, text: "Molto scadente" }
    { group:57, id:10, text: "Scadente" }
    { group:57, id:11, text: "Sotto la media" }
    { group:57, id:12, text: "Media" }
    { group:57, id:13, text: "Media" }
    { group:57, id:14, text: "Sopra la media" }
    { group:57, id:15, text: "Buona" }
    { group:57, id:16, text: "Molto buona" }
    { group:57, id:17, text: "Eccellente" }
    { group:57, id:18, text: "Perfetta" }
    { group:57, id:19, text: "Ad alcune zone della città ora occorre la disponibilità delle Scuole degli Scribi. La mancanza di accesso all'educazione impedisce che parte della città sviluppi abitazioni migliori." }
    { group:57, id:20, text: "Alcuni quartieri richiedono una migliore disponibilità di Scuole degli Scribi. Alcune abitazioni hanno accesso alle scuole cittadine, altre no, e ciò impedisce il loro sviluppo." }
    { group:57, id:21, text: "Per alcune aree della città è richiesto un accesso alla biblioteca. Per diventare scribi, i tuoi cittadini devono cosultare i libri." }
    { group:57, id:22, text: "Ci sono zone della città che chiedono un migliore accesso alle biblioteche. Gli scribi più facoltosi non vogliono camminare molto." }
    { group:57, id:23, text: "Una migliore disponibilità di scuole e biblioteche migliorerà alcune zone della città. La gente non deve camminare così tanto per imparare!" }
    { group:57, id:24, text: "Per ora nessun cittadino richiede strutture educative. Man mano che la città cresce, la gente si aspetterà scuole degli scribi e in seguito biblioteche." }
    { group:57, id:25, text: "Tutti coloro che richiedono un'educazione hanno ciò che desiderano, le strutture educative della tua città sono perfette." }
    { group:57, id:26, text: "Tutti i quartieri che hanno richiesto strutture educative sono stati soddisfatti, ma ulteriori scuole degli scribi ridurrebbero l'esubero di studenti per classe." }
    { group:57, id:27, text: "Tutti coloro che richiedono un'educazione hanno ciò che desiderano, ma potresti costruire più biblioteche per la tua città." }
    { group:57, id:28, text: "Scuole degli scribi" }
    { group:57, id:29, text: "Biblioteca" }
    { group:58, id:0, text: "Supervisore all'intrattenimento" }
    { group:58, id:1, text: "Funzionanti" }
    { group:58, id:2, text: "Spettacoli" }
    { group:58, id:3, text: "Servono" }
    { group:58, id:4, text: "Copertura cittadina" }
    { group:58, id:5, text: "Persone" }
    { group:58, id:6, text: "N/D" }
    { group:58, id:7, text: "In questo momento i tuoi cittadini hanno altre necessità che non il divertirsi. Con la crescita della città, però, ti chiederanno qualcosa per alleviare la monotonia della loro vita di tutti i giorni." }
    { group:58, id:8, text: "I cittadini in cerca di divertimento ora hanno tutto quello che desiderano: in futuro, però, dovrai fornire loro forme d' intrattenimento sempre nuove, senza mai fermarti!" }
    { group:58, id:9, text: "Molti abitanti si lamentano di non avere un accesso ottimale alle strutture ricreative. Ci sono zone della città che hanno bisogno di intrattenimenti più vari, per potersi sviluppare ulteriormente." }
    { group:58, id:10, text: "Alcune zone della città si lamentano per le difficoltà di accesso alle strutture ricreative. Costruendo nuovi centri d' intrattenimento contribuirai al loro sviluppo." }
    { group:58, id:11, text: "Alcuni cittadini lamentano un scarsa disponibilità di divertimenti nelle loro zone. Può essere necessario offrire più varietà o forse costruire più scuole di artisti." }
    { group:58, id:12, text: "In alcune strade mancano musicanti o giocolieri e, quindi, non possono funzionare al meglio. Più attori servono a migliorare certe zone della città che richiedono maggiori divertimenti." }
    { group:58, id:13, text: "Le tue strade necessitano di spettacoli più numerosi! Fornendo dei danzatori puoi migliorare la qualità del divertimento in alcune parti della città." }
    { group:58, id:14, text: "Quando una taverna senet ha impiegati e birra, il maestro senet circolerà nel quartiere per richiamare gli avventori." }
    { group:58, id:15, text: "dall'ultima festività" }
    { group:58, id:16, text: "Indìci una nuova festività" }
    { group:58, id:17, text: "Festività" }
    { group:58, id:18, text: "I festaioli più incalliti non hanno ancora dormito dall'ultima festività." }
    { group:58, id:19, text: "La gente sorride ancora quando ricorda la tua ultima festività." }
    { group:58, id:20, text: "La memoria dell'ultima festività comincia a svanire dalle menti della gente." }
    { group:58, id:21, text: "I cittadini non si ricordano più quando si sono tenuti le ultime festività in città." }
    { group:58, id:22, text: "La popolazione si lamenta per la scarsità delle festività nella tua città." }
    { group:58, id:23, text: "La gente non può sopportare un altro anno senza una festività." }
    { group:58, id:24, text: "\"Vogliamo una vacanza!\" la gente grida in strada." }
    { group:58, id:30, text: "costi" }
    { group:58, id:31, text: "Festività normale" }
    { group:58, id:32, text: "Festività grandiosa" }
    { group:58, id:33, text: "Festività maggiore" }
    { group:58, id:34, text: "Preparativi per la festività di" }
    { group:58, id:35, text: "Nessuna" }
    { group:58, id:36, text: "Scarsa" }
    { group:58, id:37, text: "Molto scadente" }
    { group:58, id:38, text: "Scadente" }
    { group:58, id:39, text: "Sotto la media" }
    { group:58, id:40, text: "Media" }
    { group:58, id:41, text: "Media" }
    { group:58, id:42, text: "Sopra la media" }
    { group:58, id:43, text: "Buona" }
    { group:58, id:44, text: "Molto buona" }
    { group:58, id:45, text: "Eccellente" }
    { group:58, id:46, text: "Perfetta" }
    { group:58, id:47, text: "Teatri dei giocolieri" }
    { group:58, id:48, text: "Teatri dei musicanti" }
    { group:58, id:49, text: "Teatri dei danzatori" }
    { group:58, id:50, text: "Taverne senet" }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Indìci una festività" }
    { group:58, id:53, text: "Festività per" }
    { group:58, id:54, text: "prossimo mese" }
    { group:58, id:55, text: "Teatri" }
    { group:58, id:56, text: "Zoo" }
    { group:59, id:0, text: "Supervisore dei templi" }
    { group:59, id:1, text: "Templi" }
    { group:59, id:2, text: "Complessi" }
    { group:59, id:3, text: "Appagamento" }
    { group:59, id:4, text: "N/D" }
    { group:59, id:5, text: "Tempio" }
    { group:59, id:6, text: "mesi" }
    { group:59, id:7, text: "festività" }
    { group:59, id:8, text: "senza" }
    { group:59, id:9, text: "I tuoi cittadini iniziano a mostrare interesse per la religione. La mancanza di accesso a luoghi di culto impedisce l'ulteriore sviluppo della città." }
    { group:59, id:10, text: "Sempre più cittadini ti chiedono almeno un luogo di culto nel loro quartiere, per far sì che gli dei li guardino con occhi benevoli." }
    { group:59, id:11, text: "I cittadini di alcuni quartieri vogliono un accesso alla religione più vicino a casa. La mancanza di diversità religiosa è un limite allo sviluppo di alcune aree." }
    { group:59, id:12, text: "Alcuni cittadini vogliono una terza religione stabilita nelle loro vicinanze. Credono che ciò possa servire ad attirare scribi di migliore qualità." }
    { group:59, id:13, text: "Fino a questo momento i tuoi cittadini si sono preoccupati di altri aspetti della vita della città, ma con il passare del tempo vorranno accessi sempre più facili ai templi." }
    { group:59, id:14, text: "La religione nella tua città è fiorente: i bisogni di ognuno sono soddisfatti e i sacerdoti comunicano che gli dei sono compiaciuti." }
    { group:59, id:15, text: "La scontentezza di Osiride è pericolosa. Può distruggere le messi e svuotare i granai e persino annullare l'Inondazione." }
    { group:59, id:16, text: "Quando il potente Ra, padre del Faraone, è scontento, la tua città subirà gravi conseguenze. Quando Ra è arrabbiato, l'armonia con il Regno è in pericolo." }
    { group:59, id:17, text: "Ptah, la cui protezione occorre ai tuoi artigiani, è infelice. Riconquista il suo favore, o piangi con i tuoi artigiani per la perdita di industrie e prodotti." }
    { group:59, id:18, text: "I soldati più coraggiosi tremano di fronte alla collera di Seth. Riconquista la fiducia del dio o vedrai il tuo battaglione spazzato dal campo!" }
    { group:59, id:19, text: "Quando la gentile Bast si altera, la gente non è più al sicuro nelle proprie case. Placa subito la dea, o patirai distruzione e pestilenze!" }
    { group:59, id:20, text: "Furibondo" }
    { group:59, id:21, text: "Furioso" }
    { group:59, id:22, text: "Adirato" }
    { group:59, id:23, text: "Offeso" }
    { group:59, id:24, text: "Dispiaciuto" }
    { group:59, id:25, text: "Indifferente" }
    { group:59, id:26, text: "Compiaciuto" }
    { group:59, id:27, text: "Felice" }
    { group:59, id:28, text: "Contento" }
    { group:59, id:29, text: "Deliziato" }
    { group:59, id:30, text: "Esaltato" }
    { group:59, id:31, text: "Hai disattivato gli effetti degli dèi: anche se saranno arrabbiati o compiaciuti non verrai mai a saperlo." }
    { group:59, id:32, text: "Osiride è il dio delle inondazioni del Nilo e di tutta la vita che nasce dal mondo inferiore. Grazie a lui, la tua città riceve la benedizione dell'inondazione annuale, che riporta la fertilità alle tue terre. Egli può favorire il raccolto in altri modi. Con un altare di Sebek - dio della fertilità - i sacerdoti di Osiride aiutano i tuoi cittadini a sfruttare meglio le loro scorte di cibo, mentre un Oracolo di Min - dio della rigenerazione - infonde più vita agli animali intorno alla tua città. Questo Oracolo rende i greggi e i pesci più resistenti e favorisce la rinascita di alcune piante." }
    { group:59, id:33, text: "In qualità di dio del Regno, Ra favorisce il commercio e i viaggi in tutto il mondo conosciuto e può anche aiutarti a rafforzare i tuoi avamposti in tutto l'Egitto. Un altare di Ma'at - dea della giustizia - aiuta a diminuire il crimine in città, mentre un Oracolo di Horus - dio del Faraone - rende i tuoi impiegati più ligi al loro dovere. Nel nome del Faraone, essi saranno più spronati a lavorare per il bene dell'Egitto." }
    { group:59, id:34, text: "Ptah è il patrono degli artigiani e aiuta a terminare più in fretta il loro lavoro. Un altare di Amon - dio del sole - migliora la capacità di costruire monumenti, mentre un Oracolo di Thoth - dio della saggezza e dell'apprendimento - favorisce l'educazione della tua gente." }
    { group:59, id:35, text: "Quando Seth è appagato, i tuoi nemici sono i suoi nemici. Egli può rendere i tuoi novellini abili come veterani e può persino colpire i tuoi nemici di suo pugno. Egli è tanto potente che la sua influenza si estende oltre i confini del Regno. Naturalmente, se Seth non è appagato, la tua città potrebbe subire la sua grande potenza distruttiva." }
    { group:59, id:36, text: "In qualità di dea della casa, Bast può migliorare la qualità di vita in città. Ella è così potente da riuscire ad appagare anche gli altri dei. Naturalmente, se non è appagata, la tua città conoscerà miseria e sofferenza. Un altare di Iside - dea della guarigione - assicura che i tuoi cittadini restino in buona salute e può persino aiutarli a superare le malattie, mentre un oracolo di Hathor - dea della gioia, amore e festività - può rallegrare la tua gente anche se versa in cattive condizioni." }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Sacerdotessa" }
    { group:60, id:0, text: "Supervisore finanziario" }
    { group:60, id:2, text: "Il tesoro cittadino dispone di" }
    { group:60, id:3, text: "La città ha un debito di" }
    { group:60, id:4, text: "produce una cifra stimata in" }
    { group:60, id:5, text: "di persone che pagano le tasse" }
    { group:60, id:6, text: "Ultimo anno" }
    { group:60, id:7, text: "Finora quest'anno" }
    { group:60, id:8, text: "Tasse incamerate" }
    { group:60, id:9, text: "Introiti esportazioni" }
    { group:60, id:10, text: "Entrate" }
    { group:60, id:11, text: "Costi importazioni" }
    { group:60, id:12, text: "Stipendi" }
    { group:60, id:13, text: "Costruzione" }
    { group:60, id:14, text: "Interesse allo" }
    { group:60, id:15, text: "Salario personale" }
    { group:60, id:16, text: "Furti" }
    { group:60, id:17, text: "Spese" }
    { group:60, id:18, text: "Entrate/uscite nette" }
    { group:60, id:19, text: "Bilancio" }
    { group:60, id:20, text: "Doni" }
    { group:60, id:21, text: "Tributi" }
    { group:60, id:22, text: "Richieste e festività" }
    { group:60, id:23, text: "in tasse mancate" }
    { group:60, id:24, text: "Oro estratto" }
    { group:61, id:13, text: "Si produce molto più cibo di quello consumato" }
    { group:61, id:14, text: "Si produce appena più cibo di quello consumato" }
    { group:61, id:15, text: "Il cibo prodotto è sufficiente per sfamare tutti." }
    { group:61, id:16, text: "IMPORTANTE: mangiamo più di quanto produciamo" }
    { group:61, id:17, text: "GRAVE: mangiamo più di quanto produciamo" }
    { group:61, id:18, text: "URGENTE: mangiamo molto più di quanto produciamo" }
    { group:61, id:19, text: "Inutilizzato" }
    { group:61, id:20, text: "Sei odiato da tutti" }
    { group:61, id:21, text: "La gente è molto arrabbiata -" }
    { group:61, id:22, text: "La gente è arrabbiata -" }
    { group:61, id:23, text: "La gente è davvero scontenta -" }
    { group:61, id:24, text: "La gente è scontenta -" }
    { group:61, id:25, text: "La gente è stufa -" }
    { group:61, id:26, text: "La gente è indifferente verso di te -" }
    { group:61, id:27, text: "La gente si compiace di te" }
    { group:61, id:28, text: "La gente si compiace molto di te" }
    { group:61, id:29, text: "La gente è estremamente compiaciuta di te" }
    { group:61, id:30, text: "La gente ti ama" }
    { group:61, id:31, text: "La gente ti idolatra come un dio" }
    { group:61, id:32, text: "scarsità di cibo." }
    { group:61, id:33, text: "scarsità di lavoro." }
    { group:61, id:34, text: "tasse elevate." }
    { group:61, id:35, text: "salari troppo bassi." }
    { group:61, id:36, text: "troppe catapecchie." }
    { group:61, id:37, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. I tuoi cittadini non sono felici per la mancanza di cibo, ma anche tasse elevate, salari bassi e mancanza di lavoro possono contribuire al malumore." }
    { group:61, id:38, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. I tuoi cittadini non sono felici per la mancanza di lavoro, ma anche tasse elevate, salari bassi, differenze sociali e mancanza di cibo possono contribuire al malumore." }
    { group:61, id:39, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. I tuoi cittadini non sono felici per le tasse elevate, ma anche salari bassi, differenze sociali e mancanza di cibo o lavoro possono contribuire al malumore." }
    { group:61, id:40, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. I tuoi cittadini non sono felici per i salari bassi (rispetto a quelli dei lavoratori in altre città egiziane), ma anche tasse elevate, differenze sociali e mancanza di cibo o lavoro possono contribuire al malumore." }
    { group:61, id:41, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. I tuoi cittadini non sono felici per le differenze sociali, ma anche tasse elevate, salari bassi e mancanza di cibo o lavoro possono contribuire al malumore." }
    { group:61, id:42, text: "Il malumore genera un alto tasso di criminalità, tiene lontani gli immigrati e può anche allontanare gli attuali cittadini. Differenze sociali, tasse elevate, salari bassi e mancanza di cibo o lavoro contribuiscono al malumore." }
    { group:61, id:43, text: "La guerra tiene lontani gli immigranti!" }
    { group:61, id:44, text: "Molta gente si sta trasferendo in città" }
    { group:61, id:45, text: "La mancanza di case limita l'immigrazione" }
    { group:61, id:46, text: "I bassi stipendi scoraggiano l'immigrazione" }
    { group:61, id:47, text: "La scarsità di lavoro previene l'immigrazione" }
    { group:61, id:48, text: "La mancanza di cibo limita l'immigrazione" }
    { group:61, id:49, text: "Le tasse elevate scoraggiano l'immigrazione" }
    { group:61, id:50, text: "Le zone diroccate della città scoraggiano gli immigranti." }
    { group:61, id:51, text: "La bassa attitudine previene l'immigrazione" }
    { group:61, id:52, text: "La gente lascia la città per mancanza di case." }
    { group:61, id:53, text: "La gente lascia la città per i salari bassi." }
    { group:61, id:54, text: "La gente lascia la città per mancanza di lavoro." }
    { group:61, id:55, text: "La gente lascia la città per mancanza di cibo." }
    { group:61, id:56, text: "La gente lascia la città per le tasse elevate o diseguali" }
    { group:61, id:57, text: "Le catapecchie incoraggiano la gente ad andarsene." }
    { group:61, id:58, text: "La gente lascia la città per il malcontento generale." }
    { group:61, id:59, text: "Sono attesi leggeri cambiamenti" }
    { group:61, id:60, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Affinché la tua città cresca e prosperi, devi costruire nuove case." }
    { group:61, id:61, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Se vuoi attirare più gente in città, devi aumentare i salari." }
    { group:61, id:62, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Devi creare più posti di lavoro impiantando qualche industria, se vuoi attirare più gente in città." }
    { group:61, id:63, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Devi produrre più cibo, se vuoi attirare più gente in città." }
    { group:61, id:64, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Devi abbassare le tasse, se vuoi attirare più gente in città." }
    { group:61, id:65, text: "Generalmente occorre aumentare la popolazione, cosicché la tua città cresca e prosperi. I nuovi abitanti sono attirati da case disponibili e dalla contentezza generale." }
    { group:61, id:66, text: "Generalmente occorre aumentare la popolazione, cosicché la tua città cresca e prosperi. Dato che ci sono case disponibili e i cittadini sono contenti, i nuovi abitanti stanno arrivando in massa." }
    { group:61, id:67, text: "Quando c'è troppa disparità tra ricchi e poveri, nessuno vuole venire nella tua città. Offri migliori servizi ai quartieri più poveri così da equilibrare i ricchi e i meno abbienti." }
    { group:61, id:68, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città. Devi migliorare l'umore della città, se vuoi attirare più gente in città." }
    { group:61, id:69, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città (e gli attuali cittadini non andranno in cerca di pascoli più verdi). Devi costruire più case per far crescere e prosperare la tua città." }
    { group:61, id:70, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, questi rimarranno in città. Aumenta i salari, se vuoi incoraggiare la gente a restare." }
    { group:61, id:71, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, questi rimarranno in città. Crea più posti di lavoro costruendo qualche industria, se vuoi incoraggiare la gente a restare." }
    { group:61, id:72, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, questi rimarranno in città. Dato il numero dei tuoi cittadini, devi produrre più cibo, se vuoi incoraggiare la gente a restare." }
    { group:61, id:73, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, questi rimarranno in città. Devi ridurre le tasse, se vuoi incoraggiare la gente a restare." }
    { group:61, id:74, text: "Quando c'è troppa disparità tra ricchi e poveri, la gente tende a cercare nuove opportunità altrove. Offri migliori servizi ai quartieri più poveri così da equilibrare i ricchi e i meno abbienti." }
    { group:61, id:75, text: "Finché ci sono abitazioni disponibili e i cittadini sono contenti di te, arriverà sempre nuova gente per stabilirsi in città (e gli attuali cittadini non andranno in cerca di pascoli più verdi). Devi migliorare l'umore cittadino, se vuoi che la gente resti in città." }
    { group:61, id:76, text: "URGENTE: La città ha una disoccupazione del" }
    { group:61, id:77, text: "GRAVE: La città ha una disoccupazione del" }
    { group:61, id:78, text: "IMPORTANTE: La città ha una disoccupazione del" }
    { group:61, id:79, text: "La città ha una disoccupazione del" }
    { group:61, id:80, text: "URGENTE: La città è a corto di" }
    { group:61, id:81, text: "GRAVE:  La città è a corto di" }
    { group:61, id:82, text: "IMPORTANTE: La città è a corto di" }
    { group:61, id:83, text: "La città è a corto di" }
    { group:61, id:84, text: "La città non ha problemi di impiego" }
    { group:61, id:85, text: "La disoccupazione elevata costringe la tua gente a cercare lavoro altrove. Costruisci altre industrie per creare più posti di lavoro." }
    { group:61, id:86, text: "La disoccupazione elevata può costringere la tua gente a cercare lavoro altrove. Puoi creare più lavoro costruendo altre industrie." }
    { group:61, id:87, text: "La disoccupazione elevata può costringere la tua gente a cercare lavoro altrove. Puoi creare più lavoro costruendo altre industrie." }
    { group:61, id:88, text: "Questo livello di disoccupazione è tollerabile, ma se aumenta troppo, la gente potrebbe cercare lavoro altrove. Puoi creare più lavoro costruendo altre industrie." }
    { group:61, id:89, text: "Una grave mancanza di lavoratori come questa può fermare tutte le attività della città. Chiudi le industrie non necessarie, oppure attira altri lavoratori con disponibilità di case e una popolazione felice." }
    { group:61, id:90, text: "Una grave mancanza di lavoratori impedisce ai tuoi cittadini di svolgere le loro funzioni quotidiane. Chiudi le industrie non necessarie, oppure attira altri lavoratori con disponibilità di case e una popolazione felice." }
    { group:61, id:91, text: "Senza un numero sufficiente di lavoratori, i tuoi cittadini hanno difficoltà a svolgere le loro funzioni quotidiane." }
    { group:61, id:92, text: "La mancanza di lavoratori può ridurre le merci e i servizi in tutta la città. Assicura una maggiore efficienza chiudendo le industrie non necessarie, oppure attira altri lavoratori con disponibilità di case e una popolazione felice." }
    { group:61, id:93, text: "Un alto tasso di disoccupazione può costringere i cittadini alla ricerca di lavoro altrove, mentre la mancanza di lavoratori può ridurre le merci e i servizi in tutta la città." }
    { group:61, id:94, text: "La Capitale fa fronte alle nostre necessità" }
    { group:61, id:95, text: "URGENTE: I nostri livelli di cibo sono bassi" }
    { group:61, id:96, text: "GRAVE: I nostri livelli di cibo sono bassi" }
    { group:61, id:97, text: "IMPORTANTE: I nostri livelli di cibo sono bassi" }
    { group:61, id:98, text: "Rifornimenti per" }
    { group:61, id:99, text: "Se i tuoi cittadini saltano troppi pasti, si ammalano (oppure lasciano la città in cerca di un luogo migliore). Assicurati che la gente non mangi più di quanto produca e di disporre di granai a sufficienza per conservare il raccolto." }
    { group:61, id:100, text: "Se i tuoi cittadini saltano troppi pasti, si ammalano (oppure lasciano la città in cerca di un luogo migliore). Assicurati che la gente non mangi più di quanto produca e di disporre di granai a sufficienza per conservare il raccolto." }
    { group:61, id:101, text: "Se i tuoi cittadini saltano troppi pasti, si ammalano (oppure lasciano la città in cerca di un luogo migliore). Assicurati che la gente non mangi più di quanto produca e di disporre di granai a sufficienza per conservare il raccolto." }
    { group:61, id:102, text: "Se i tuoi cittadini saltano troppi pasti, si ammalano (oppure lasciano la città in cerca di un luogo migliore). Assicurati che la gente non mangi più di quanto produca e di disporre di granai a sufficienza per conservare il raccolto." }
    { group:61, id:103, text: "URGENTE: Sanità terribile, pestilenza imminente." }
    { group:61, id:104, text: "URGENTE: Igiene terribile, pestilenza probabile." }
    { group:61, id:105, text: "GRAVE: Igiene pessima, rischio di pestilenza." }
    { group:61, id:106, text: "IMPORTANTE: Igiene scarsa, pestilenza prossima." }
    { group:61, id:107, text: "L'igiene cittadina è insufficiente." }
    { group:61, id:108, text: "L'igiene cittadina è media." }
    { group:61, id:109, text: "L'igiene cittadina è buona." }
    { group:61, id:110, text: "L'igiene cittadina è molto buona." }
    { group:61, id:111, text: "L'igiene cittadina è eccellente." }
    { group:61, id:112, text: "L'igiene cittadina è quasi perfetta." }
    { group:61, id:113, text: "L'igiene cittadina è perfetta." }
    { group:61, id:114, text: "Con così tanta gente in cattiva salute, la tua città patirà probabilmente una pestilenza, in grado di decimare i cittadini. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi e assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:115, text: "Con così tanta gente ammalata, la tua città patirà probabilmente una pestilenza, in grado di decimare i cittadini. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi; assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:116, text: "Con così tanta gente ammalata in città, medici e farmacie non riescono a fare molto. La tua città corre il rischio di una pestilenza, in grado di devastare la popolazione. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi e assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:117, text: "Con così tanta gente ammalata in città, medici e farmacie non riescono a fare molto. La tua città potrebbe essere colpita da una pestilenza, in grado di devastare la popolazione. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi; assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:118, text: "Se la salute peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi e assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:119, text: "Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Costruisci ambulatori per i medici e camere mortuarie, per le persone che al momento non hanno accesso a tali servizi; assicurati che i cittadini dispongano di cibo a sufficienza." }
    { group:61, id:120, text: "L'igiene e la buona salute sono necessarie per limitare la malaria e le malattie e specialmente per evitare le pestilenze. Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Medici e imbalsamatori, forniti dai relativi edifici, aiutano a mantenere un buono stato di salute così come una buona scorta di varietà di cibo." }
    { group:61, id:121, text: "L'igiene e la buona salute sono necessarie per limitare la malaria e le malattie e specialmente per evitare le pestilenze. Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Medici e imbalsamatori, forniti dai relativi edifici, aiutano a mantenere un buono stato di salute, così come una buona scorta di varietà di cibo." }
    { group:61, id:122, text: "L'igiene e la buona salute sono necessarie per limitare la malaria e le malattie e specialmente per evitare le pestilenze. Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Medici e imbalsamatori, forniti dai relativi edifici, aiutano a mantenere un buono stato di salute, così come una buona scorta di varietà di cibo." }
    { group:61, id:123, text: "L'igiene e la buona salute sono necessarie per limitare la malaria e le malattie e specialmente per evitare le pestilenze. Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Medici e imbalsamatori, forniti dai relativi edifici, aiutano a mantenere un buono stato di salute, così come una buona scorta di varietà di cibo." }
    { group:61, id:124, text: "L'igiene e la buona salute sono necessarie per limitare la malaria e le malattie e specialmente per evitare le pestilenze. Se la salute della gente peggiora, la città potrebbe patire una pestilenza, in grado di devastare la popolazione. Medici e imbalsamatori, forniti dai relativi edifici, aiutano a mantenere un buono stato di salute, così come una buona scorta di varietà di cibo." }
    { group:61, id:125, text: "IMPORTANTE: Parecchi dei non sono appagati" }
    { group:61, id:126, text: "GRAVE: Parecchi dei potrebbero colpirci" }
    { group:61, id:127, text: "IMPORTANTE: Tre dei non sono appagati" }
    { group:61, id:128, text: "GRAVE: Tre dei non sono appagati" }
    { group:61, id:129, text: "IMPORTANTE: Due dei non sono appagati" }
    { group:61, id:130, text: "GRAVE: Due dei non sono appagati" }
    { group:61, id:131, text: "IMPORTANTE: Un dio non è appagato" }
    { group:61, id:132, text: "GRAVE: Un dio non è appagato" }
    { group:61, id:133, text: "Tutti gli dei sono adeguatamente appagati" }
    { group:61, id:134, text: "Tutti gli dei sono appagati. Uno è felice" }
    { group:61, id:135, text: "Tutti gli dei sono appagati. Due sono felici" }
    { group:61, id:136, text: "Tutti gli dei sono appagati. Tre sono felici" }
    { group:61, id:137, text: "Tutti gli dei sono appagati. Molti sono felici" }
    { group:61, id:138, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:139, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:140, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:141, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:142, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:143, text: "Gli Dei ostili possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:144, text: "Gli Dei arrabbiati possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:145, text: "Gli Dei arrabbiati possono usare i propri poteri per devastare la tua città. Per appagarli, costruisci templi a loro dedicati e indìci festività in loro onore." }
    { group:61, id:146, text: "Se un dio diventa ostile, può usare i suoi poteri per devastare la tua città." }
    { group:61, id:147, text: "Gli Dei benevolenti possono usare i propri poteri per benedire la tua città in molti modi. Con il crescere della tua città, assicurati di appagare gli dei dedicando loro dei templi e continuando a indire festività in loro onore." }
    { group:61, id:148, text: "Gli Dei benevolenti possono usare i propri poteri per benedire la tua città in molti modi. Con il crescere della tua città, assicurati di appagare gli dei dedicando loro dei templi e continuando a indire festività in loro onore." }
    { group:61, id:149, text: "Gli Dei benevolenti possono usare i propri poteri per benedire la tua città in molti modi. Con il crescere della tua città, assicurati di appagare gli dei dedicando loro dei templi e continuando a indire festività in loro onore." }
    { group:61, id:150, text: "Gli Dei benevolenti possono usare i propri poteri per benedire la tua città in molti modi. Con il crescere della tua città, assicurati di appagare gli dei dedicando loro dei templi e continuando a indire festività in loro onore." }
    { group:61, id:151, text: "GRAVE: impossibile riscuotere molte tasse!" }
    { group:61, id:152, text: "Il bilancio annuale è salito di" }
    { group:61, id:153, text: "Stiamo andando bene come l'anno scorso." }
    { group:61, id:154, text: "Il bilancio annuale è sceso di" }
    { group:61, id:155, text: "Stai perdendo molti soldi perché la tua città non ha esattori delle tasse a sufficienza. Crea più esattori, specialmente nelle zone più ricche e assicurati che tutti abbiano accesso all'esattore (tramite lo schema delle tasse)." }
    { group:61, id:156, text: "Se finisci i soldi, puoi comunque disporre di un credito fino a 5.000 deben. Rimanere in debito per un periodo troppo lungo può generare serie ripercussioni. Tasse, esportazioni e oro sono i metodi migliori per portare contante in città. Puoi sempre trasferire dei soldi dal tuo conto personale al tesoro cittadino." }
    { group:61, id:157, text: "Se finisci i soldi, puoi comunque disporre di un credito fino a 5.000 deben. Rimanere in debito per un periodo troppo lungo può generare serie ripercussioni. Tasse, esportazioni e oro sono i metodi migliori per portare contante in città. Naturalmente, puoi sempre trasferire dei soldi dal tuo conto personale al tesoro cittadino." }
    { group:61, id:158, text: "Se continui a perdere soldi, puoi comunque disporre di un credito fino a 5.000 deben. Rimanere in debito per un periodo troppo lungo può generare serie ripercussioni. Tasse, esportazioni e oro sono i metodi migliori per portare contante in città. Naturalmente, puoi sempre trasferire dei soldi dal tuo conto personale al tesoro cittadino." }
    { group:61, id:159, text: "URGENTE: Molti furti recenti," }
    { group:61, id:160, text: "GRAVE: Parecchi furti recenti," }
    { group:61, id:161, text: "IMPORTANTE: Alcuni furti recenti," }
    { group:61, id:162, text: "Furti molto rari." }
    { group:61, id:163, text: "Nessun furto segnalato." }
    { group:61, id:164, text: "db rubati." }
    { group:61, id:165, text: "Tutti questi furti possono danneggiare molto il tesoro cittadino e persino i tuoi risparmi personali! Un numero adeguato di stazioni di polizia e palazzi di giustizia possono servire a contenere il crimine e i conestabili cattureranno tutti i ladri che incontrano. Ovviamente, mantenere la tua gente felice è il miglior modo di prevenire qualsiasi sorta di crimine." }
    { group:61, id:166, text: "Furti frequenti possono danneggiare molto il tesoro cittadino e persino i tuoi risparmi personali! Un numero adeguato di stazioni di polizia e palazzi di giustizia possono servire a contenere il crimine e i conestabili cattureranno tutti i ladri che incontrano. Ovviamente, mantenere la tua gente felice è il miglior modo di prevenire qualsiasi sorta di crimine." }
    { group:61, id:167, text: "Furti frequenti possono danneggiare molto le finanze cittadine e persino i tuoi risparmi personali! Un numero adeguato di stazioni di polizia e palazzi di giustizia possono servire a contenere il crimine e i conestabili cattureranno tutti i ladri che incontrano. Ovviamente, mantenere la tua gente felice è il miglior modo di prevenire qualsiasi sorta di crimine." }
    { group:61, id:168, text: "Furti frequenti possono danneggiare molto le finanze cittadine e persino i tuoi risparmi personali! Un numero adeguato di stazioni di polizia e palazzi di giustizia possono servire a contenere il crimine e i conestabili cattureranno tutti i ladri che incontrano. Ovviamente, mantenere la tua gente felice è il miglior modo di prevenire qualsiasi sorta di crimine." }
    { group:61, id:169, text: "I furti possono danneggiare le finanze cittadine e persino i tuoi risparmi personali! Un numero adeguato di stazioni di polizia e palazzi di giustizia possono servire a contenere il crimine e i conestabili cattureranno tutti i ladri che incontrano. Ovviamente, mantenere la tua gente felice è il miglior modo di prevenire qualsiasi sorta di crimine." }
    { group:61, id:170, text: "Non hai compagnie da comandare" }
    { group:61, id:171, text: "Non sono segnalate minacce." }
    { group:61, id:172, text: "I nemici si stanno avvicinando alla città." }
    { group:61, id:173, text: "I nemici stanno attaccando la città." }
    { group:61, id:174, text: "Truppe nemiche alle nostre porte" }
    { group:61, id:175, text: "Le nostre truppe servono altrove." }
    { group:61, id:176, text: "Ci sono delle nostre truppe in altri luoghi." }
    { group:61, id:177, text: "Non ci sono forze militari a nostra disposizione. Al momento non ce n'è bisogno, la situazione è sicura." }
    { group:61, id:178, text: "Se i nemici avanzassero verso la nostra città, riceversti senz'altro un messaggio. Gli eserciti nemici compaiono anche sulla mappa del mondo, quindi puoi vederli avanzare e intanto preparare la città al loro arrivo." }
    { group:61, id:179, text: "Un esercito nemico sta avanzando per attaccare la città! Potrebbe essere difficile, se non impossibile, costruire edifici sotto attacco; quindi, prepara le difese costruendo mura, torri, corpi di guardia e forti prima del suo arrivo." }
    { group:61, id:180, text: "È sempre un bene tenersi pronti a sostenere un attacco, invece di reclutare le truppe all'ultimo momento. Speriamo di avere abbastanza difese per proteggere la città." }
    { group:61, id:181, text: "È sempre un bene tenersi pronti a sostenere un attacco, invece di reclutare le truppe all'ultimo momento. Speriamo di avere abbastanza difese per proteggere la città." }
    { group:61, id:182, text: "Abbiamo ricevuto una richiesta di truppe da un comandante egizio. Di solito, è bene onorare tali richieste, se vuoi rimanere in buoni rapporti con il resto del Regno. Consulta il supervisore politico e quello militare per inviare le truppe." }
    { group:61, id:183, text: "Alcune delle nostre truppe stanno servendo l'Egitto in campagne militari lontane. Di solito, è bene aiutare il Regno inviando truppe quando necessario, se vuoi rimanere in buoni rapporti con il resto del Regno." }
    { group:61, id:184, text: "Ci sono molte richieste pendenti alla nostra città." }
    { group:61, id:185, text: "Ci sono molte richieste da soddisfare." }
    { group:61, id:186, text: "Ci sono alcune richieste da soddisfare." }
    { group:61, id:187, text: "Non ci sono richieste pendenti alla nostra città." }
    { group:61, id:188, text: "Mancare di rispondere alle richieste del Faraone o dei vicini può sortire una serie di effetti negativi. Se non aiuti i tuoi compagni egizi nel momento del bisogno, essi potrebbero perire in povertà o cadere nelle mani dei nemici. Se vuoi rimanere in buoni rapporti con i tuoi connazionali, di solito è bene onorare le loro richieste di buon grado e immediatamente." }
    { group:61, id:189, text: "Mancare di rispondere alle richieste del Faraone o dei vicini può sortire una serie di effetti negativi. Se non aiuti i tuoi compagni egizi nel momento del bisogno, essi potrebbero perire in povertà o cadere nelle mani dei nemici. Se vuoi rimanere in buoni rapporti con i tuoi connazionali, di solito è bene onorare le loro richieste di buon grado e immediatamente." }
    { group:61, id:190, text: "Se non aiuti i tuoi connazionali nel momento del bisogno, essi potrebbero perire in povertà, cadere nelle mani dei nemici o patire altre sorti indesiderate. Ciò può influenzare negativamente il commercio, i prezzi e il tuo livello nel Regno. Se vuoi rimanere in buoni rapporti con i tuoi connazionali, di solito è bene onorare le loro richieste di buon grado e immediatamente." }
    { group:61, id:191, text: "Se vuoi rimanere in buoni rapporti con i tuoi connazionali, di solito è bene onorare le loro richieste con buona volontà e prontezza. Se non li aiuti, essi potrebbero perire in povertà, cadere nelle mani dei nemici o patire altre sorti indesiderate. Ciò può influenzare negativamente il commercio, i prezzi e persino il tuo livello nel Regno." }
    { group:61, id:192, text: "Quest'anno non ci sarà alcuna inondazione" }
    { group:61, id:193, text: "Quest'anno l'inondazione sarà scarsa " }
    { group:61, id:194, text: "Quest'anno l'inondazione sarà mediocre" }
    { group:61, id:195, text: "Quest'anno l'inondazione sarà buona" }
    { group:61, id:196, text: "Quest'anno l'inondazione sarà eccellente" }
    { group:61, id:197, text: "L'inondazione di quest'anno sarà perfetta" }
    { group:61, id:198, text: "La scarsa inondazione di quest'anno farà in modo che il fertile fango del Nilo non venga depositato sui tuoi campi. Se la tua città per il cibo dipende dall'agricoltura dei campi inondati, tale fatto può mettere a rischio la vita di numerosi cittadini. Ricorri al culto di Osiride, dio del Nilo, per evitare che l'anno prossimo si verifichi la stessa situazione." }
    { group:61, id:199, text: "La scarsità di inondazione di quest'anno farà in modo che poco fango fertile del Nilo venga depositato sui tuoi campi. Se la tua città per il cibo dipende dall'agricoltura dei campi inondati, tale fatto può mettere a rischio la vita di numerosi cittadini. Appaga Osiride, dio del Nilo, per evitare che l'anno prossimo si verifichi la stessa situazione." }
    { group:61, id:200, text: "La mediocre inondazione di quest'anno farà in modo che solo parte del fango fertile del Nilo venga depositato sui tuoi campi. Se la tua città per il cibo dipende dall'agricoltura dei campi inondati, tale fatto può mettere a rischio la vita di numerosi cittadini. Migliora il culto di Osiride, dio del Nilo, per evitare che l'anno prossimo si verifichi la stessa situazione." }
    { group:61, id:201, text: "La buona inondazione di quest'anno farà in modo che il Nilo depositi il suo fango fertile sui tuoi campi. Assicurati che Osiride, dio del Nilo, sia costantemente appagato perché anche l'anno prossimo si verifichi la stessa situazione." }
    { group:61, id:202, text: "Se la tua città dipende per il cibo dall'agricoltura dei campi inondati, la ricchezza del fango fertile depositato sui tuoi campi merita i dovuti ringraziamenti. Assicurati che Osiride, dio del Nilo, sia sempre felice, cosicché che il prossimo anno continui a benedire la tua città." }
    { group:61, id:203, text: "Se la tua città dipende per il cibo dall'agricoltura dei campi inondati, la grande ricchezza del fango fertile depositato sui tuoi campi merita i dovuti ringraziamenti. Prega Osiride, dio del Nilo, cosicché il prossimo anno continui a benedire la tua città." }
    { group:61, id:204, text: "L'inondazione è prevista all'inizio di giugno" }
    { group:61, id:205, text: "L'inondazione è prevista alla fine di giugno" }
    { group:61, id:206, text: "L'inondazione è prevista all'inizio di luglio" }
    { group:61, id:207, text: "L'inondazione è prevista alla fine di luglio" }
    { group:61, id:208, text: "L'inondazione è prevista all'inizio di agosto" }
    { group:61, id:209, text: "L'inondazione è prevista alla fine di agosto" }
    { group:61, id:210, text: "L'inondazione è prevista all'inizio di settembre" }
    { group:61, id:211, text: "L'inondazione è prevista alla fine di settembre" }
    { group:61, id:212, text: "Se i tuoi cittadini salteranno troppi pasti, si ammaleranno (o lasceranno la città in cerca di luoghi migliori). Per nutrire una popolazione così vasta, devi produrre più cibo costruendo più fattorie, casotti da caccia, moli di pescatori o allevamenti di bestiame, oppure importare altro cibo. Puoi anche usare l'irrigazione per aumentare la produzione agricola." }
    { group:61, id:213, text: "Se i tuoi cittadini salteranno troppi pasti, si ammaleranno (o lasceranno la città in cerca di luoghi migliori). Per nutrire una popolazione così vasta, devi produrre più cibo costruendo più fattorie, casotti da caccia o allevamenti di bestiame, oppure importare altro cibo." }
    { group:61, id:214, text: "Se i tuoi cittadini salteranno troppi pasti, si ammaleranno (o lasceranno la città in cerca di luoghi migliori). Per nutrire una popolazione così vasta, devi produrre più cibo costruendo più fattorie, casotti da caccia o allevamenti di bestiame, oppure importare altro cibo." }
    { group:61, id:215, text: "Se i tuoi cittadini salteranno troppi pasti, si ammaleranno (o lasceranno la città in cerca di luoghi migliori). Hai già una perfetta combinazione di fattorie, allevamenti di bestiame, casotti da caccia e cibo importato per nutrire la tua popolazione." }
    { group:61, id:216, text: "Se i tuoi cittadini continuano a mangiare bene, rimarranno in salute (e non lasceranno la città in cerca di pasti migliori). Hai un po' più fattorie, allevamenti di bestiame, casotti da caccia di quelli che occorrono per nutrire la tua popolazione." }
    { group:61, id:217, text: "Se i tuoi cittadini continuano a mangiare bene, rimarranno in salute (e non lasceranno la città in cerca di pasti migliori). Hai molte più fattorie, allevamenti di bestiame, casotti da caccia di quelli che occorrono per nutrire la tua popolazione." }
    { group:61, id:218, text: "Clicca su qualsiasi voce per ulteriori informazioni e consigli" }
    { group:62, id:0, text: "Vittoria" }
    { group:62, id:1, text: "Licenziato!" }
    { group:62, id:2, text: "Hai completato la missione con successo!" }
    { group:62, id:3, text: "Avanti" }
    { group:62, id:4, text: "Continua a governare per altri 2 anni." }
    { group:62, id:5, text: "Continua per altri 5 anni." }
    { group:62, id:6, text: "Nuova partita" }
    { group:62, id:7, text: "Alla città" }
    { group:62, id:8, text: "Congratulazioni!" }
    { group:62, id:9, text: "Hai finito le missioni del periodo predinastico. Per aumentare la sfida, clicca ancora su \"Gioca Demo\" e passa al periodo Arcaico." }
    { group:62, id:10, text: "Obiettivi" }
    { group:62, id:11, text: "Popolazione di" }
    { group:62, id:12, text: "Livello culturale" }
    { group:62, id:13, text: "Livello di prosperità" }
    { group:62, id:14, text: "Livello di monumenti" }
    { group:62, id:15, text: "Livello del regno" }
    { group:62, id:16, text: "Sono confuso. Nonostante la fiducia del popolo egizio, pare che gli dei abbiano abbandonato la tua causa. La tua città disonora l'Egitto. Persino il tuo posto nell'altro mondo è in discussione. È una fine ben triste per un inizio così promettente. Un altro prenderà il tuo posto. - Il Faraone" }
    { group:62, id:17, text: "Costruisci delle Stazioni dei vigili del fuoco." }
    { group:62, id:18, text: "Costruisci dei Centri di architettura" }
    { group:62, id:19, text: "Costruisci un granaio e riempilo di cacciagione" }
    { group:62, id:20, text: "Obiettivo rimasto: Rifornisci le case con cibo dei bazar." }
    { group:62, id:21, text: "Costruisci delle case." }
    { group:62, id:22, text: "Costruisci dei baracconi e delle Scuole di giocolieri." }
    { group:62, id:23, text: "Costruisci dei templi e santuari di Bast." }
    { group:62, id:24, text: "Estrai dell'oro." }
    { group:62, id:25, text: "Costruisci delle farmacie e medici" }
    { group:62, id:32, text: "Costruisci una masataba." }
    { group:62, id:34, text: "Clicca sull'ankh per rivedere gli obiettivi della missione" }
    { group:62, id:35, text: "Il tuo ruolo nella storia è assicurato. Gli egiziani ti proclamano un dio." }
    { group:62, id:36, text: "Accetta lo stato di divinità!" }
    { group:62, id:37, text: "Rigioca missione" }
    { group:62, id:38, text: "Tempo scaduto!" }
    { group:62, id:39, text: "Hai perso questa missione. Puoi abbassare il livello di difficoltà per avere più tempo, oppure ritentare direttamente." }
    { group:62, id:40, text: "Difficoltà inferiore" }
    { group:63, id:0, text: "Messaggi" }
    { group:63, id:1, text: "Al momento non hai messaggi da leggere. Man mano che la tua città cresce, o quando altre città ti richiederanno dei beni, i relativi messaggi saranno inviati qui" }
    { group:63, id:2, text: "Data" }
    { group:63, id:3, text: "Oggetto" }
    { group:63, id:4, text: "Clicca col sinistro su un messaggio per leggerlo. Clicca col destro per cancellarlo." }
    { group:63, id:5, text: "Per" }
    { group:63, id:6, text: "Cancella messaggi aperti" }
    { group:64, id:0, text: "Nessuno" }
    { group:64, id:1, text: "Immigrante" }
    { group:64, id:2, text: "Emigrante" }
    { group:64, id:3, text: "Vagabondo" }
    { group:64, id:4, text: "Trainatore" }
    { group:64, id:5, text: "Cittadino" }
    { group:64, id:6, text: "Esplosione" }
    { group:64, id:7, text: "Esattore" }
    { group:64, id:8, text: "Architetto" }
    { group:64, id:9, text: "Magazziniere" }
    { group:64, id:10, text: "Vigile del fuoco" }
    { group:64, id:11, text: "Arciere" }
    { group:64, id:12, text: "Auriga" }
    { group:64, id:13, text: "Fanteria" }
    { group:64, id:14, text: "Messaggero" }
    { group:64, id:15, text: "Giocoliere" }
    { group:64, id:16, text: "Musicante" }
    { group:64, id:17, text: "Danzatore" }
    { group:64, id:18, text: "Animatore senet" }
    { group:64, id:19, text: "Carovana di mercanti da" }
    { group:64, id:20, text: "Nave commerciale da" }
    { group:64, id:21, text: "Carovana di mercanti da" }
    { group:64, id:22, text: "Contestatore" }
    { group:64, id:23, text: "Criminale" }
    { group:64, id:24, text: "Ladro di tombe" }
    { group:64, id:25, text: "Nave da pesca" }
    { group:64, id:26, text: "Commerciante" }
    { group:64, id:27, text: "Sacerdote" }
    { group:64, id:28, text: "Scolaro" }
    { group:64, id:29, text: "Insegnante" }
    { group:64, id:30, text: "Libraio" }
    { group:64, id:31, text: "Dentista" }
    { group:64, id:32, text: "Medico" }
    { group:64, id:33, text: "Erborista" }
    { group:64, id:34, text: "Imbalsamatore" }
    { group:64, id:35, text: "Lavoratore" }
    { group:64, id:36, text: "Indicatore di mappa" }
    { group:64, id:37, text: "Relitti" }
    { group:64, id:38, text: "Portuale" }
    { group:64, id:39, text: "Cliente" }
    { group:64, id:40, text: "Scriba" }
    { group:64, id:41, text: "Indigeno" }
    { group:64, id:42, text: "Sentinella" }
    { group:64, id:43, text: "Nemico" }
    { group:64, id:44, text: "Nemico" }
    { group:64, id:45, text: "Nemico" }
    { group:64, id:46, text: "Nemico" }
    { group:64, id:47, text: "Nemico" }
    { group:64, id:48, text: "Nemico" }
    { group:64, id:49, text: "Barbarian (not used?)" }
    { group:64, id:50, text: "Barbarian (not used?)" }
    { group:64, id:51, text: "Barbarian (not used?)" }
    { group:64, id:52, text: "Barbarian (not used?)" }
    { group:64, id:53, text: "Nemico" }
    { group:64, id:54, text: "Nemico" }
    { group:64, id:55, text: "Nemico" }
    { group:64, id:56, text: "Nemico" }
    { group:64, id:57, text: "Nemico" }
    { group:64, id:58, text: "Native Trader (not used?)" }
    { group:64, id:59, text: "Freccia" }
    { group:64, id:60, text: "Giavellotto" }
    { group:64, id:61, text: "Dardo" }
    { group:64, id:62, text: "Balestra" }
    { group:64, id:63, text: "Creatura" }
    { group:64, id:64, text: "Missionario" }
    { group:64, id:65, text: "Gabbiano" }
    { group:64, id:66, text: "Fattorino" }
    { group:64, id:67, text: "Naufragio" }
    { group:64, id:68, text: "Uccelli" }
    { group:64, id:69, text: "Struzzo" }
    { group:64, id:70, text: "Antilope" }
    { group:64, id:71, text: "Lancia" }
    { group:64, id:72, text: "Corridore" }
    { group:64, id:73, text: "Cacciatore" }
    { group:64, id:74, text: "Lancia da cacciatore" }
    { group:64, id:75, text: "Boscaiolo" }
    { group:64, id:76, text: "Traghetto" }
    { group:64, id:77, text: "Mercantile" }
    { group:64, id:78, text: "Nave da guerra" }
    { group:64, id:79, text: "Carpentiere" }
    { group:64, id:80, text: "Muratore" }
    { group:64, id:81, text: "Mastro scalpellino" }
    { group:64, id:82, text: "Coccodrillo" }
    { group:64, id:83, text: "Iena" }
    { group:64, id:84, text: "Ippopotamo" }
    { group:64, id:85, text: "Lavoratore" }
    { group:64, id:86, text: "Slitta" }
    { group:64, id:87, text: "Trasportatore d'acqua" }
    { group:64, id:88, text: "Conestabile" }
    { group:64, id:89, text: "Magistrato" }
    { group:64, id:90, text: "Raccoglitore di canne" }
    { group:64, id:91, text: "Celebratore" }
    { group:64, id:92, text: "Mercantile nemico" }
    { group:64, id:93, text: "Nave da guerra nemica" }
    { group:64, id:94, text: "Lamentatore" }
    { group:64, id:95, text: "Pesce" }
    { group:64, id:96, text: "Porta slitta" }
    { group:64, id:97, text: "Attore" }
    { group:64, id:98, text: "Cittadino piagato" }
    { group:64, id:99, text: "Fanteria beduina" }
    { group:64, id:100, text: "\"\"\"Nave da guerra egizia\"\"\"" }
    { group:64, id:101, text: "Egyptian transport" }
    { group:64, id:102, text: "Aspide" }
    { group:64, id:103, text: "Leone" }
    { group:64, id:104, text: "Scorpione" }
    { group:64, id:105, text: "Guardiano dello zoo" }
    { group:64, id:106, text: "Rana" }
    { group:64, id:107, text: "Locusta" }
    { group:64, id:108, text: "Artigiano della tomba" }
    { group:64, id:109, text: "Mummia" }
    { group:64, id:110, text: "unused section 65 - was c3 walker names" }
    { group:65, id:0, text: "unused section 65 - was c3 walker names" }
    { group:66, id:0, text: "Sistema di aiuto attivo." }
    { group:66, id:1, text: "Questa terra è vicina a una fonte d'acqua e permette l'utilizzo di pozzi di qualsiasi dimensione" }
    { group:66, id:2, text: "Questa dimora non ha accesso ad acqua potabile" }
    { group:66, id:3, text: "Questa dimora ha solo un accesso base all'acqua potabile" }
    { group:66, id:4, text: "Questa casa non ha scorte di cibo" }
    { group:66, id:5, text: "Questa casa esaurirà presto le sue limitate scorte di cibo" }
    { group:66, id:6, text: "Questa casa ha cibo a sufficienza per un mese" }
    { group:66, id:7, text: "Questa casa non ha alcun problema nel recuperare il cibo che le serve" }
    { group:66, id:8, text: "Questa casa non riceve consegne di acqua potabile" }
    { group:66, id:9, text: "Questa casa è stata da poco visitata da un trasportatore d'acqua. Avrà acqua potabile per molto tempo" }
    { group:66, id:10, text: "Questa casa ha una provvista di acqua potabile" }
    { group:66, id:11, text: "Se un trasportatore d'acqua non passa entro breve, questa casa esaurirà la sua provvista d'acqua" }
    { group:66, id:12, text: "Questa casa non ha accesso ad alcun tempio o santuario" }
    { group:66, id:13, text: "Questa casa ha accesso al tempio di un solo dio." }
    { group:66, id:14, text: "Questa casa ha accesso a templi di 2 diversi dei." }
    { group:66, id:15, text: "Questa casa ha accesso a templi di 3 diversi dei." }
    { group:66, id:16, text: "Questa casa ha accesso a templi di 4 diversi dei." }
    { group:66, id:17, text: "Questa casa ha accesso ai templi di tutti gli dei." }
    { group:66, id:18, text: "Questa casa ha accesso a un santuario e ai templi di tutti gli dei" }
    { group:66, id:46, text: "Questo edificio non corre pericolo di andare a fuoco." }
    { group:66, id:47, text: "Questo edificio ha una modesta possibilità di incendiarsi." }
    { group:66, id:48, text: "Questo edificio corre il pericolo di andare a fuoco." }
    { group:66, id:49, text: "Questo edificio è a rischio d'incendio." }
    { group:66, id:50, text: "Questo edificio corre un grave pericolo di andare a fuoco." }
    { group:66, id:51, text: "Questo edificio può andare a fuoco da un momento all'altro!" }
    { group:66, id:58, text: "Questo è un quartiere molto rispettoso della legge dove non sono segnalati crimini." }
    { group:66, id:59, text: "In questo quartiere avvengono solo dei crimini occasionali." }
    { group:66, id:60, text: "In quest'area il crimine è scarso, ma alcuni residenti si sono lamentati." }
    { group:66, id:61, text: "In questo quartiere di recente sono avvenuti molti crimini, tutto sommato, però, é un'area abbastanza tranquilla" }
    { group:66, id:62, text: "Questa è una zona ad alta criminalità. I residenti sono infelici, le strade di notte non sono sicure." }
    { group:66, id:63, text: "L'intera zona è una polveriera! Il crimine è endemico, potrebbe succedere di tutto" }
    { group:66, id:83, text: "Questa casa non ha accesso al teatro di danza" }
    { group:66, id:84, text: "Questa casa è stata da poco visitata da un danzatore. Avrà accesso al teatro di danza per molto tempo" }
    { group:66, id:85, text: "Questa casa ha accesso al teatro di danza" }
    { group:66, id:86, text: "Questa casa non è stata visitata da un danzatore da molto tempo. Presto perderà l'accesso alla danza" }
    { group:66, id:91, text: "Nessun cittadino vuole vivere qui" }
    { group:66, id:92, text: "I tuoi cittadini non vedono fattori negativi o positivi collegati a quest'area." }
    { group:66, id:93, text: "Questo terreno è desiderabile" }
    { group:66, id:94, text: "Questo edificio attualmente non ha accesso alla forza lavoro necessaria." }
    { group:66, id:95, text: "Questo edificio attualmente ha un accesso limitato alla forza lavoro necessaria." }
    { group:66, id:96, text: "Questo edificio attualmente ha uno scarso accesso alla forza lavoro necessaria." }
    { group:66, id:97, text: "Questo edificio attualmente dispone di un accesso alla forza lavoro necessaria." }
    { group:66, id:98, text: "Questo edificio attualmente ha un buon accesso alla forza lavoro necessaria." }
    { group:66, id:99, text: "Questo edificio attualmente ha un accesso eccellente alla forza lavoro necessaria." }
    { group:66, id:104, text: "Questo capanno cerca cibo tra i rifiuti..." }
    { group:66, id:105, text: "Questa terra è molto fertile. Le messi qui coltivate saranno robuste e abbondanti." }
    { group:66, id:106, text: "Questa terra è abbastanza fertile. Le messi qui coltivate saranno abbastanza in salute." }
    { group:66, id:107, text: "Questa terra è moderatamente fertile. Le messi qui coltivate non raggiungeranno il loro pieno potenziale." }
    { group:66, id:108, text: "Questa terra non è molto fertile. Le messi qui cresceranno a stento." }
    { group:66, id:109, text: "Questa terra non è fertile. Qui non possono crescere messi." }
    { group:66, id:110, text: " cesti di grano sono conservati in questo edificio." }
    { group:66, id:111, text: " cesto di grano è conservato in questo edificio." }
    { group:66, id:112, text: " giare di frutta sono conservate in questo edificio." }
    { group:66, id:113, text: " giara di frutta è conservata in questo edificio." }
    { group:66, id:114, text: " giare di verdura sono conservate in questo edificio." }
    { group:66, id:115, text: " giara di verdura è conservata in questo edificio." }
    { group:66, id:116, text: " quarti di carne sono conservati in questo edificio." }
    { group:66, id:117, text: " quarto di carne è conservato in questo edificio." }
    { group:66, id:118, text: " vasi sono conservati in questo edificio." }
    { group:66, id:119, text: " vaso è conservato in questo edificio." }
    { group:66, id:120, text: " sacchetti di gioielli (beni di lusso) sono conservati in questo edificio." }
    { group:66, id:121, text: " sacchetto di gioielli (beni di lusso) è conservato in questo edificio." }
    { group:66, id:122, text: " rotoli di tela sono conservati in questo edificio." }
    { group:66, id:123, text: " rotolo di tela è conservato in questo edificio." }
    { group:66, id:124, text: " fiaschi di birra sono conservati in questo edificio." }
    { group:66, id:125, text: " fiasco di birra è conservato in questo edificio." }
    { group:66, id:126, text: "Questo edificio non conserva alcuna merce." }
    { group:66, id:136, text: "Questo edificio non presenta probabilità di malaria." }
    { group:66, id:137, text: "Questo edificio presenta un rischio di malaria trascurabile." }
    { group:66, id:138, text: "Questo edificio presenta qualche rischio di malaria." }
    { group:66, id:139, text: "Questo edificio è a rischio di malaria." }
    { group:66, id:140, text: "Questo edificio sarà presto colpito dalla malaria." }
    { group:66, id:141, text: "Questa casa ha i seguenti problemi" }
    { group:66, id:142, text: "Questa industria ha i seguenti problemi" }
    { group:66, id:143, text: "Rischio di crollo" }
    { group:66, id:144, text: "Rischio di incendio" }
    { group:66, id:145, text: "Rischio di malattia" }
    { group:66, id:146, text: "Vacante" }
    { group:66, id:147, text: "Rischio di malaria" }
    { group:66, id:148, text: "Malattia imperversante" }
    { group:66, id:149, text: "Potenziale rischio di crimine" }
    { group:66, id:150, text: "Peggiorerà presto" }
    { group:66, id:151, text: "Mancano materie prime" }
    { group:66, id:152, text: "Nessun lavoratore" }
    { group:66, id:153, text: "Pochi lavoratori" }
    { group:66, id:154, text: "In naftalina" }
    { group:66, id:155, text: "Nessun accesso al lavoro" }
    { group:66, id:156, text: "Infestate dalle rane" }
    { group:66, id:157, text: "Nessuno vive in questa dimora" }
    { group:66, id:158, text: "Questa casa non ha accesso al palazzo di giustizia" }
    { group:66, id:159, text: "Questa casa è stata recentemente visitata da un magistrato. Avrà accesso al palazzo di giustizia per lungo tempo" }
    { group:66, id:160, text: "Questa casa ha accesso al palazzo di giustizia" }
    { group:66, id:161, text: "In questa casa è molto che non giunge un magistrato. Presto perderà l'accesso al palazzo di giustizia" }
    { group:66, id:162, text: "Questa zona è una delle meno desiderabili" }
    { group:66, id:163, text: "Nessuno sarebbe felice di vivere qui, ma ci sono posti peggiori" }
    { group:66, id:164, text: "La gente non ha particolari commenti sulla desiderabilità della zona" }
    { group:66, id:165, text: "Questa zona è meglio di altre, anche se non è il massimo" }
    { group:66, id:166, text: "L'opinione generale è che la zona sia carina" }
    { group:66, id:167, text: "Questa è una delle migliori zone della città" }
    { group:66, id:168, text: "Questa casa non ha accesso a uno zoo" }
    { group:66, id:169, text: "Questa casa è stata da poco visitata da un guardiano dello zoo. Avrà accesso a uno zoo per molto tempo." }
    { group:66, id:170, text: "Questa casa ha accesso a uno zoo" }
    { group:66, id:171, text: "Questa casa non è stata visitata recentemente da un guardiano dello zoo. Presto perderà l'accesso allo zoo." }
    { group:66, id:172, text: "Questa casa è infestata dalle rane" }
    { group:67, id:0, text: "Edifici consentiti" }
    { group:67, id:1, text: "Materie prime" }
    { group:67, id:2, text: "Miniera d'oro" }
    { group:67, id:3, text: "Pompa idraulica" }
    { group:67, id:4, text: "Canale di irrigazione" }
    { group:67, id:5, text: "Banchina da pesca" }
    { group:67, id:6, text: "Campo di lavoro" }
    { group:67, id:7, text: "Granaio" }
    { group:67, id:8, text: "Bazar" }
    { group:67, id:9, text: "Deposito merci" }
    { group:67, id:10, text: "Porto" }
    { group:67, id:11, text: "Giocolieri" }
    { group:67, id:12, text: "Musica" }
    { group:67, id:13, text: "Danza" }
    { group:67, id:14, text: "Giochi senet" }
    { group:67, id:15, text: "Piazza delle festività" }
    { group:67, id:16, text: "Scuola degli scribi" }
    { group:67, id:17, text: "Biblioteca" }
    { group:67, id:18, text: "Serbatoio d'acqua" }
    { group:67, id:19, text: "Dentista" }
    { group:67, id:20, text: "Farmacia" }
    { group:67, id:21, text: "Medico" }
    { group:67, id:22, text: "Camera mortuaria" }
    { group:67, id:23, text: "Esattore" }
    { group:67, id:24, text: "Palazzo di giustizia" }
    { group:67, id:25, text: "Palazzo" }
    { group:67, id:26, text: "Magione" }
    { group:67, id:27, text: "Blocco stradale" }
    { group:67, id:28, text: "Ponte" }
    { group:67, id:29, text: "Approdo" }
    { group:67, id:30, text: "Giardini" }
    { group:67, id:31, text: "Piazza" }
    { group:67, id:32, text: "Statue" }
    { group:67, id:33, text: "Mura" }
    { group:67, id:34, text: "Torre" }
    { group:67, id:35, text: "Corpo di Guardia" }
    { group:67, id:36, text: "Reclutatore" }
    { group:67, id:37, text: "Forte: Fanteria" }
    { group:67, id:38, text: "Forte: Arcieri" }
    { group:67, id:39, text: "Forte: Aurighi" }
    { group:67, id:40, text: "Accademia" }
    { group:67, id:41, text: "Armeria" }
    { group:67, id:42, text: "Fabbrica di bighe" }
    { group:67, id:43, text: "Molo delle navi da guerra" }
    { group:67, id:44, text: "Molo commerciale" }
    { group:67, id:45, text: "Zoo" }
    { group:68, id:0, text: "Testo dell'aiuto via mouse" }
    { group:68, id:1, text: "Mostra la pagina dell'aiuto relativa a questo pannello" }
    { group:68, id:2, text: "Esci da questo pannello" }
    { group:68, id:3, text: "Carica questa partita salvata" }
    { group:68, id:4, text: "Salva la partita in corso in questo file" }
    { group:68, id:5, text: "Annulla l'operazione" }
    { group:68, id:6, text: "Scorri la lista delle partite salvate" }
    { group:68, id:7, text: "Clicca sul nome di un file per selezionarlo" }
    { group:68, id:8, text: "aiuto via mouse libero" }
    { group:68, id:9, text: "aiuto via mouse libero" }
    { group:68, id:10, text: "Nasconde il pannello di controllo per creare un'area di gioco più ampia" }
    { group:68, id:11, text: "Seleziona una tabella di sommario sulla città" }
    { group:68, id:12, text: "Mostra il pannello di controllo completo" }
    { group:68, id:13, text: "Carica questa partita" }
    { group:68, id:14, text: "Salva la partita in corso in questo file" }
    { group:68, id:15, text: "Annulla l'operazione" }
    { group:68, id:16, text: "Scorre la lista delle missioni" }
    { group:68, id:17, text: "Clicca sul nome di un file per selezionarlo" }
    { group:68, id:18, text: "aiuto via mouse libero" }
    { group:68, id:19, text: "aiuto via mouse libero" }
    { group:68, id:20, text: "Costruisci un'abitazione" }
    { group:68, id:21, text: "Costruisci una strada" }
    { group:68, id:22, text: "Libera il terreno" }
    { group:68, id:23, text: "Fattorie e strutture alimentari" }
    { group:68, id:24, text: "Strutture industriali" }
    { group:68, id:25, text: "Strutture di deposito e di distribuzione" }
    { group:68, id:26, text: "Strutture d'intrattenimento" }
    { group:68, id:27, text: "Strutture religiose" }
    { group:68, id:28, text: "Strutture educative" }
    { group:68, id:29, text: "Strutture sanitarie" }
    { group:68, id:30, text: "Strutture municipali" }
    { group:68, id:31, text: "Strutture militari" }
    { group:68, id:32, text: "ANNULLA l'ultima azione (disponibile solo quando l'icona è attiva)" }
    { group:68, id:33, text: "Visualizza i messaggi" }
    { group:68, id:34, text: "Passa in rassegna gli ultimi problemi cittadini" }
    { group:68, id:35, text: "Rivedi la tua missione" }
    { group:68, id:36, text: "Clicca nella mappa generale per raggiungere quartieri lontani della città" }
    { group:68, id:37, text: "aiuto via mouse libero" }
    { group:68, id:38, text: "aiuto via mouse libero" }
    { group:68, id:39, text: "aiuto via mouse libero" }
    { group:68, id:40, text: "aiuto via mouse libero" }
    { group:68, id:41, text: "Visita i supervisori" }
    { group:68, id:42, text: "Vai alla mappa del Regno" }
    { group:68, id:43, text: "Rivedi la tua missione" }
    { group:68, id:44, text: "Orienta la tua visuale verso nord" }
    { group:68, id:45, text: "Ruota la vista in senso orario" }
    { group:68, id:46, text: "Ruota la vista in senso antiorario" }
    { group:68, id:47, text: "aiuto via mouse libero" }
    { group:68, id:48, text: "aiuto via mouse libero" }
    { group:68, id:49, text: "aiuto via mouse libero" }
    { group:68, id:50, text: "aiuto via mouse libero" }
    { group:68, id:52, text: "Impostazione del sonoro e della velocità" }
    { group:68, id:53, text: "Accedi all'aiuto del gioco" }
    { group:68, id:54, text: "Accedi alle schermate dei supervisori" }
    { group:68, id:55, text: "aiuto via mouse libero" }
    { group:68, id:56, text: "aiuto via mouse libero" }
    { group:68, id:57, text: "aiuto via mouse libero" }
    { group:68, id:58, text: "aiuto via mouse libero" }
    { group:68, id:59, text: "aiuto via mouse libero" }
    { group:68, id:60, text: "aiuto via mouse libero" }
    { group:68, id:64, text: "aiuto via mouse libero" }
    { group:68, id:65, text: "aiuto via mouse libero" }
    { group:68, id:66, text: "aiuto via mouse libero" }
    { group:68, id:67, text: "aiuto via mouse libero" }
    { group:68, id:68, text: "aiuto via mouse libero" }
    { group:68, id:69, text: "aiuto via mouse libero" }
    { group:68, id:70, text: "Visita il supervisore commerciale" }
    { group:68, id:71, text: "Visita il supervisore del lavoro" }
    { group:68, id:72, text: "Visita il supervisore militare" }
    { group:68, id:73, text: "Visita il supervisore politico" }
    { group:68, id:74, text: "Visita il supervisore dei livelli" }
    { group:68, id:75, text: "Visita il supervisore commerciale" }
    { group:68, id:76, text: "Visita il supervisore dei granai" }
    { group:68, id:77, text: "Visita il supervisore della sanità" }
    { group:68, id:78, text: "Visita il supervisore all'istruzione" }
    { group:68, id:79, text: "Visita il supervisore all'intrattenimento" }
    { group:68, id:80, text: "Visita il supervisore dei templi" }
    { group:68, id:81, text: "Visita il supervisore finanziario" }
    { group:68, id:82, text: "Visita il supervisore capo" }
    { group:68, id:83, text: "Visita il supervisore ai monumenti" }
    { group:68, id:84, text: "Torna alla vista principale" }
    { group:68, id:85, text: "aiuto via mouse libero" }
    { group:68, id:86, text: "aiuto via mouse libero" }
    { group:68, id:87, text: "aiuto via mouse libero" }
    { group:68, id:88, text: "aiuto via mouse libero" }
    { group:68, id:89, text: "aiuto via mouse libero" }
    { group:68, id:90, text: "aiuto via mouse libero" }
    { group:68, id:91, text: "aiuto via mouse libero" }
    { group:68, id:92, text: "Clicca qui per impostare una priorità per questa categoria di lavoro" }
    { group:68, id:93, text: "Stabilisci un livello di salario annuale su dieci lavoratori" }
    { group:68, id:94, text: "Clicca qui per rimuovere ogni priorità per questo compito" }
    { group:68, id:95, text: "Clicca su un numero per impostare un livello di priorità; tutte le altre priorità verranno modificate di conseguenza" }
    { group:68, id:96, text: "Clicca qui per donare soldi alla città" }
    { group:68, id:97, text: "Clicca qui per decidere il tuo stipendio" }
    { group:68, id:98, text: "Esci dallo schermo dei salari" }
    { group:68, id:99, text: "Seleziona questo livello di salario" }
    { group:68, id:100, text: "Esci dallo schermo delle donazioni" }
    { group:68, id:101, text: "Dona questi soldi alla città, prelevandoli dai tuoi risparmi" }
    { group:68, id:102, text: "Stabilisci quanto donare" }
    { group:68, id:103, text: "Regola la cifra esatta che intendi donare" }
    { group:68, id:104, text: "Clicca qui per informazioni sul livello culturale" }
    { group:68, id:105, text: "Clicca qui per informazioni sul livello di prosperità" }
    { group:68, id:106, text: "Clicca qui per consigli sul tuo livello dei monumenti" }
    { group:68, id:107, text: "Clicca qui per consigli sul tuo livello del regno" }
    { group:68, id:108, text: "Mostra i prezzi di importazione / esportazione di tutte le merci" }
    { group:68, id:109, text: "Clicca qui per lo stato delle industrie" }
    { group:68, id:110, text: "Imposta la quantità di questa merce che vuoi immagazzinare prima di esportarla" }
    { group:68, id:111, text: "Attiva e disattiva la produzione cittadina di quest'attività" }
    { group:68, id:112, text: "Regola lo stato commerciale di questo oggetto" }
    { group:68, id:113, text: "Seleziona questo grafico" }
    { group:68, id:114, text: "Informazioni sulle festività" }
    { group:68, id:115, text: "Indìci una festività in onore di questo dio" }
    { group:68, id:116, text: "Non organizzare una festività" }
    { group:68, id:117, text: "Dedica una festività a Osiride" }
    { group:68, id:118, text: "Dedica una festività a Ra" }
    { group:68, id:119, text: "Dedica una festività a Ptah" }
    { group:68, id:120, text: "Dedica una festività a Seth" }
    { group:68, id:121, text: "Dedica una festività a Bast" }
    { group:68, id:122, text: "Regola il livello delle tasse cittadine" }
    { group:68, id:123, text: "Clicca qui per parlare con questa persona" }
    { group:68, id:124, text: "Informazioni dettagliate su questa casa" }
    { group:68, id:125, text: "Scorre la lista dei messaggi registrati" }
    { group:68, id:126, text: "Messaggio letto in precedenza. @L Clicca col sinistro per leggerlo. @L Clicca col destro per cancellarlo>" }
    { group:68, id:127, text: "Messaggio non ancora letto. @L Clicca col sinistro per leggerlo. @L Clicca col destro per cancellarlo." }
    { group:68, id:128, text: "Torna alla schermata precedente dell'aiuto" }
    { group:68, id:129, text: "Esci dall'aiuto di Faraon" }
    { group:68, id:130, text: "Elenca tutti gli aiuti su quest'argomento" }
    { group:68, id:131, text: "Cancella questo messaggio" }
    { group:68, id:132, text: "Clicca qui per recarti dove si è verificato il problema" }
    { group:68, id:133, text: "Invia un dono per l'Egitto" }
    { group:68, id:134, text: "Clicca qui per cambiare la formazione della compagnia" }
    { group:68, id:135, text: "Disoccupazione" }
    { group:68, id:140, text: "Clicca qui per impartire gli ordini ai mercantili" }
    { group:68, id:141, text: "Clicca qui per impartire gli ordini alle navi da guerra" }
    { group:68, id:142, text: "Livello tasse" }
    { group:68, id:143, text: "Mostra stato dell'esercito" }
    { group:68, id:144, text: "Mostra stato della marina" }
    { group:68, id:145, text: "Vai alla mappa del regno" }
    { group:68, id:146, text: "Imposta parametri missione" }
    { group:68, id:147, text: "Terreno normale" }
    { group:68, id:148, text: "Alberi" }
    { group:68, id:149, text: "Acqua e terre umide" }
    { group:68, id:150, text: "Prato" }
    { group:68, id:151, text: "Strada" }
    { group:68, id:152, text: "Roccia e dune" }
    { group:68, id:153, text: "Punti del fiume" }
    { group:68, id:154, text: "Punti di invasione" }
    { group:68, id:155, text: "Punti persone" }
    { group:68, id:156, text: "Punti animali" }
    { group:68, id:157, text: "Pennelli" }
    { group:68, id:158, text: "Aggiungi città, regione o grafica" }
    { group:68, id:159, text: "Modifica città, regione o grafica" }
    { group:68, id:160, text: "Elimina città, regione o grafica" }
    { group:68, id:161, text: "Mostra menu principale" }
    { group:68, id:162, text: "Aggiungi via commerciale o di invasione" }
    { group:68, id:163, text: "Modifica via commerciale o di invasione" }
    { group:68, id:164, text: "Torna alla mappa di default" }
    { group:68, id:165, text: "Torna alla visuale regionale" }
    { group:68, id:166, text: "Modifica prezzi di importazione/esportazione" }
    { group:68, id:167, text: "Modifica livello, fondi, data di partenza e Faraone attuale" }
    { group:68, id:168, text: "Scorri opzioni climatiche" }
    { group:68, id:169, text: "Pianifica eventi" }
    { group:68, id:170, text: "Scegli un nemico" }
    { group:68, id:171, text: "Definisci divinità" }
    { group:68, id:172, text: "Imposta edifici disponibili" }
    { group:68, id:173, text: "Imposta requisiti di livello e scegli monumenti" }
    { group:68, id:174, text: "Determina lunghezza e qualità straripamento" }
    { group:68, id:175, text: "Ruota visuale" }
    { group:68, id:176, text: "Modifica grafica" }
    { group:68, id:177, text: "Predatori" }
    { group:68, id:178, text: "Età dei monumenti" }
    { group:69, id:0, text: "necessari)" }
    { group:69, id:1, text: "Efficienza" }
    { group:69, id:2, text: "Rischio di crollo assente" }
    { group:69, id:3, text: "Rischio di crollo minimo" }
    { group:69, id:4, text: "Rischio di crollo basso" }
    { group:69, id:5, text: "Rischio di crollo" }
    { group:69, id:6, text: "Rischio di crollo elevato" }
    { group:69, id:7, text: "Rischio di crollo molto elevato" }
    { group:69, id:8, text: "Crollo imminente" }
    { group:69, id:9, text: "Rischio d'incendio assente" }
    { group:69, id:10, text: "Rischio d'incendio minimo" }
    { group:69, id:11, text: "Rischio d'incendio basso" }
    { group:69, id:12, text: "Rischio d'incendio" }
    { group:69, id:13, text: "Rischio d'incendio elevato" }
    { group:69, id:14, text: "Rischio d'incendio molto elevato" }
    { group:69, id:15, text: "Incendio imminente" }
    { group:69, id:21, text: "Funziona a malapena. Assegna più lavoratori a questo settore." }
    { group:69, id:22, text: "Funziona male. Assegna più lavoratori a questo settore." }
    { group:69, id:23, text: "Operativa, ma puoi assegnare più lavoratori a questo settore." }
    { group:69, id:24, text: "Funziona a ritmo ridotto. Sono arrivati pochi lavoratori." }
    { group:69, id:26, text: "Personale insufficiente. Può inviare merci, ma non riceverne." }
    { group:69, id:27, text: "Solo personale essenziale. Non può né inviare né ricevere merci." }
    { group:70, id:0, text: "Nessuna persona in questo luogo." }
    { group:70, id:1, text: "libero" }
    { group:70, id:2, text: "libero" }
    { group:70, id:3, text: "libero" }
    { group:70, id:4, text: "libero" }
    { group:70, id:5, text: "libero" }
    { group:70, id:6, text: "libero" }
    { group:70, id:7, text: "libero" }
    { group:70, id:8, text: "libero" }
    { group:70, id:9, text: "libero" }
    { group:70, id:10, text: "Niente" }
    { group:70, id:11, text: "Alberi e foreste" }
    { group:70, id:12, text: "Rocce" }
    { group:70, id:13, text: "Acqua" }
    { group:70, id:14, text: "Alberi" }
    { group:70, id:15, text: "Fessure nel terreno" }
    { group:70, id:16, text: "Strada" }
    { group:70, id:17, text: "Canale di irrigazione" }
    { group:70, id:18, text: "Macerie di edifici distrutti" }
    { group:70, id:19, text: "Mura" }
    { group:70, id:20, text: "Terreno deserto" }
    { group:70, id:21, text: "Ponte" }
    { group:70, id:22, text: "Giardini" }
    { group:70, id:23, text: "Piazza" }
    { group:70, id:24, text: "Alla Capitale" }
    { group:70, id:25, text: "Al Regno" }
    { group:70, id:26, text: "Roccia mineraria" }
    { group:70, id:27, text: "Roccia normale" }
    { group:70, id:28, text: "Roccia speciale" }
    { group:70, id:29, text: "Pianura inondabile" }
    { group:70, id:30, text: "Pianura inondata" }
    { group:70, id:31, text: "Paludi" }
    { group:70, id:32, text: "Dune di sabbia" }
    { group:70, id:33, text: "Muro in mattoni" }
    { group:70, id:34, text: "Mura" }
    { group:70, id:35, text: "Prato" }
    { group:70, id:36, text: "Rupi" }
    { group:70, id:37, text: "Gli alberi sono terreno insuperabile, ma si possono abbattere. Sono vitali per l'industria del legno e i taglialegna devono essere vicini a essi per produrre il legno. I boschi si rinnovano dopo un po' di tempo." }
    { group:70, id:38, text: "Le rocce sono terreno insuperabile, ma si possono asportare. Potresti trovare calcare, arenaria o granito da estrarre, oppure roccia normale senza valore. Controlla le tue risorse per scoprirlo." }
    { group:70, id:39, text: "Solo le navi possono viaggiare sull'acqua; in certi punti la si può attraversare usando ponti o traghetti. I porti permettono il commercio col resto del regno. Le cave d'argilla devono essere adiacenti all'acqua." }
    { group:70, id:40, text: "Terreno insuperabile, che può essere ripulito per far espandere la città. I taglialegna devono essere vicini agli alberi per raccogliere la legna." }
    { group:70, id:41, text: "Queste crepe sono state provocate da dei terremoti. Non possono essere superate o colmate e la gente preferisce non doverci vivere accanto." }
    { group:70, id:42, text: "Le strade sono fondamentali per una vita cittadina ordinata: i cittadini usciranno dalle loro case solo se vi potranno accedere." }
    { group:70, id:43, text: "I canali di irrigazione migliorano la fertilità di tutte le fattorie che si trovano entro due blocchi." }
    { group:70, id:44, text: "Queste macerie annerite riducono il valore dei terreni vicini." }
    { group:70, id:45, text: "Le mura proteggono i cittadini inermi dai razziatori e dagli invasori. Possono sopportare solo un certo ammontare di danni e le mura più spesse resistono di più." }
    { group:70, id:46, text: "Qui puoi costruire quello che vuoi. Cacciatori e soldati - amici o nemici - possono transitare liberamente." }
    { group:70, id:47, text: "Questo ponte è un'importante via di collegamento, ma apre la strada anche a predatori e invasori." }
    { group:70, id:48, text: "I giardini aumentano il valore della zona in cui si trovano." }
    { group:70, id:49, text: "La gente adora le piazze!" }
    { group:70, id:50, text: "Questa strada ci collega al resto dell'Egitto e deve rimanere sempre aperta perché immigranti e mercanti possano raggiungere la nostra città." }
    { group:70, id:51, text: "Questa è la strada che ci collega alle regioni più distanti del Regno. È una strada reale e, come tale, occorre mantenerla percorribile e sicura." }
    { group:70, id:52, text: "Questa è una roccia mineraria. Qui puoi estrarre oro o rame, secondo il minerale presente." }
    { group:70, id:53, text: "Questa è una roccia normale. Secondo le risorse della tua città, qui dovresti essere in grado di estrarre roccia da costruzioni o persino gemme." }
    { group:70, id:54, text: "Questa è una roccia normale." }
    { group:70, id:55, text: "Questa zona offre un terreno molto fertile, ora che l'acqua si è ritirata." }
    { group:70, id:56, text: "Questa zona offrirà un terreno molto fertile, quando l'acqua si ritirerà." }
    { group:70, id:57, text: "Le zone paludose sono troppo instabili per sostenere degli edifici, ma possono essere attraversate dai cittadini con molta attenzione. Qui crescono le canne, ma stai attento ai coccodrilli!" }
    { group:70, id:58, text: "Le sabbie di questa zona sono troppo instabili per sostenere delle strutture, ma possono essere attraversate  dai cittadini con molta attenzione." }
    { group:70, id:59, text: "Questo è un muro in mattoni. Rallenta i nemici più di un muro in fango, ma non può sostituire una compagnia di soldati!" }
    { group:70, id:60, text: "Questo è un semplice muro in fango. Rallenterà gli invasori per un po', ma non si può considerare una difesa robusta." }
    { group:70, id:61, text: "Questa terra consente la crescita di messi diverse. Più belli sono i fiori, più fertile è il terreno." }
    { group:70, id:62, text: "Queste massicce rupi sono l'ideale per costruire certi monumenti. La gente non può attraversare queste zone impervie, che non permettono neppure lo sfruttamento minerario." }
    { group:71, id:0, text: "Palco dell'orchestra" }
    { group:71, id:1, text: "La gente viene qui per guardare i giocolieri e ascoltare musica." }
    { group:71, id:2, text: "Questa piazza non ospita mai divertimenti. Ha bisogno di giocolieri e musicanti per offrire divertimento." }
    { group:71, id:3, text: "Questa piazza offre ai cittadini eccellenti giocolieri e ottima musica." }
    { group:71, id:4, text: "Questa piazza offre musica per il divertimento dei cittadini. Cerca dei giocolieri per offrire ulteriore divertimento." }
    { group:71, id:5, text: "Questa piazza offre giocolieri per il divertimento dei cittadini. Cerca dei musicanti per offrire ulteriore divertimento." }
    { group:71, id:6, text: "Questa piazza è morta. Non ha impiegati e non offre alcun divertimento alla comunità locale." }
    { group:71, id:7, text: "Nessuno spettacolo musicale" }
    { group:71, id:8, text: "I musicanti suoneranno ancora per" }
    { group:71, id:9, text: "Nessuno spettacolo di giocolieri" }
    { group:71, id:10, text: "I giocolieri daranno spettacolo ancora per" }
    { group:72, id:0, text: "Baraccone" }
    { group:72, id:1, text: "I cittadini possono assistere a giocolieri e altri divertimenti." }
    { group:72, id:2, text: "Questa piazza non ospita mai divertimenti. Ha bisogno di giocolieri per offrire divertimento." }
    { group:72, id:3, text: "Questa piazza offre lo spettacolo dei giocolieri che normalmente attira un buon pubblico." }
    { group:72, id:4, text: "La piazza è animata solo dal vento. Senza lavoratori, non offre alcuno spettacolo." }
    { group:72, id:5, text: "Nessuno spettacolo di giocolieri" }
    { group:72, id:6, text: "Lo spettacolo continua ancora per" }
    { group:72, id:7, text: "Spettacolo: \"Acrobazie del grande Mefisto\", di Mefisto" }
    { group:72, id:8, text: "Spettacolo: \"Le sabbie del tempo\", di Ferrodhotep" }
    { group:72, id:9, text: "Spettacolo: \"Un fiume di lacrime\", di Waseth" }
    { group:72, id:10, text: "Spettacolo: \"La piramide di 10.000 Deben\", di Desenseth" }
    { group:72, id:11, text: "Spettacolo: \"Rock del coccodrillo\", di El-Tonjon" }
    { group:73, id:0, text: "Taverna senet" }
    { group:73, id:1, text: "Giochi di abilità e brivido per tutta la famiglia." }
    { group:73, id:2, text: "Questa taverna senet ha dei giocatori, ma occorre della birra per rallegrare gli spiriti." }
    { group:73, id:3, text: "Questa taverna senet ospita sempre dei giochi, per il buonumore della popolazione locale." }
    { group:73, id:4, text: "Nessuno visita questa taverna senet. Senza impiegati, la comunità non può divertirsi." }
    { group:73, id:5, text: "Nessun gioco in atto" }
    { group:73, id:6, text: "I giochi continueranno per" }
    { group:73, id:7, text: "Birra nei magazzini," }
    { group:74, id:0, text: "Padiglione" }
    { group:74, id:1, text: "Danze, musica e giocolieri... cosa può desiderare di più un cittadino?" }
    { group:74, id:2, text: "Questo padiglione non offre spettacoli. Occorrono danzatori, musicanti e giocolieri per attirare il pubblico." }
    { group:74, id:3, text: "Questo padiglione offre danze sfrenate, musica fantastica e giocolieri spericolati con gran piacere degli astanti." }
    { group:74, id:4, text: "Questo padiglione ha danzatori e musicanti. I giocolieri aggiungerebbero un po' di varietà agli spettacoli." }
    { group:74, id:5, text: "Questo padiglione ha danzatori e giocolieri. I musicanti completerebbero gli spettacoli." }
    { group:74, id:6, text: "Questo padiglione ha musicanti e giocolieri, ma il pubblico richiede anche dei danzatori." }
    { group:74, id:7, text: "Questo padiglione ha dei giocolieri. Occorrono musicanti e danzatori per riempire gli altri palchi." }
    { group:74, id:8, text: "Questo padiglione ha dei musicanti, ma nessun danzatore o giocoliere." }
    { group:74, id:9, text: "Questo padiglione ha dei danzatori, ma nessun musicante o giocoliere." }
    { group:74, id:10, text: "Questo padiglione è chiuso. Senza impiegati non ha alcuna ragione d'essere." }
    { group:74, id:11, text: "Nessuno spettacolo di giocolieri" }
    { group:74, id:12, text: "Gli spettacoli di giocolieri continueranno per" }
    { group:74, id:13, text: "Nessuno spettacolo musicale" }
    { group:74, id:14, text: "Gli spettacoli musicali continueranno per" }
    { group:74, id:15, text: "Nessuno spettacolo di danza" }
    { group:74, id:16, text: "Gli spettacoli di danza continueranno per" }
    { group:75, id:0, text: "Conservatorio" }
    { group:75, id:1, text: "Gli egiziani sono sempre contenti di ascoltare la musica di nuovi artisti." }
    { group:75, id:2, text: "Siamo lieti di annunciare che, grazie al perfetto numero di impiegati, stiamo istruendo quattro musicanti al mese." }
    { group:75, id:3, text: "Non abbiamo personale sufficiente; quindi, possiamo istruire al massimo due musicanti al mese." }
    { group:75, id:4, text: "Abbiamo metà del personale; quindi, riusciamo a istruire un solo musicante al mese." }
    { group:75, id:5, text: "Abbiamo davvero bisogno di altro personale, ma cercheremo di istruire almeno un musicante nei prossimi due mesi." }
    { group:75, id:6, text: "Sono l'unico impiegato. Non posso lavorare in queste condizioni! Al massimo, posso istruire un musicante in tre mesi." }
    { group:75, id:7, text: "Senza istruttori, questa scuola di musica non può fornire alcun musicante." }
    { group:76, id:0, text: "Scuola di danza" }
    { group:76, id:1, text: "I danzatori (e le danzatrici) ispirano il pubblico con movimenti e passi aggraziati." }
    { group:76, id:2, text: "Siamo lieti di annunciare che, grazie al perfetto numero di impiegati, stiamo istruendo quattro danzatori al mese." }
    { group:76, id:3, text: "Non abbiamo personale sufficiente; quindi, possiamo istruire al massimo due danzatori al mese." }
    { group:76, id:4, text: "Abbiamo metà del personale; quindi, riusciamo a istruire un solo danzatore al mese." }
    { group:76, id:5, text: "Abbiamo davvero bisogno di altro personale, ma cercheremo di istruire almeno un danzatore nei prossimi due mesi." }
    { group:76, id:6, text: "Sono l'unico impiegato. Non posso lavorare in queste condizioni! Al massimo, posso istruire un danzatore in tre mesi." }
    { group:76, id:7, text: "Senza istruttori, questa scuola di danza non può fornire alcun danzatore." }
    { group:77, id:0, text: "Scuola dei giocolieri" }
    { group:77, id:1, text: "Nuovi giocolieri e nuovi trucchi sono sempre richiesti." }
    { group:77, id:2, text: "Siamo lieti di annunciare che, grazie al perfetto numero di impiegati, stiamo istruendo quattro giocolieri al mese." }
    { group:77, id:3, text: "Non abbiamo personale sufficiente; quindi, possiamo istruire al massimo due giocolieri al mese." }
    { group:77, id:4, text: "Abbiamo metà del personale; quindi, riusciamo a istruire un solo giocoliere al mese." }
    { group:77, id:5, text: "Abbiamo davvero bisogno di altro personale, ma cercheremo di istruire almeno un giocoliere nei prossimi due mesi." }
    { group:77, id:6, text: "Sono l'unico impiegato. Non posso lavorare in queste condizioni! Al massimo, posso istruire un giocoliere in tre mesi." }
    { group:77, id:7, text: "La scuola è deserta. Senza istruttori, non si possono istruire i giocolieri." }
    { group:78, id:0, text: "Istruttori senet" }
    { group:78, id:1, text: "I maestri strateghi che lavorano qui possono istruire maestri senet per gestire le famose taverne della città." }
    { group:78, id:2, text: "Siamo lieti di annunciare che, grazie al perfetto numero di impiegati, stiamo istruendo quattro maestri senet al mese." }
    { group:78, id:3, text: "Non abbiamo personale sufficiente; quindi, possiamo istruire al massimo due maestri senet al mese." }
    { group:78, id:4, text: "Abbiamo metà del personale; quindi, riusciamo a istruire un solo maestro senet al mese." }
    { group:78, id:5, text: "Abbiamo davvero bisogno di altro personale, ma cercheremo di istruire almeno un maestro senet nei prossimi due mesi." }
    { group:78, id:6, text: "Sono l'unico impiegato. Non posso lavorare in queste condizioni! Al massimo, posso istruire un maestro senet in tre mesi." }
    { group:78, id:7, text: "Senza istruttori, non si possono istruire nuovi maestri senet. Le taverne senet della città potrebbero patirne." }
    { group:79, id:0, text: "Giardini" }
    { group:80, id:0, text: "Statua" }
    { group:80, id:1, text: "I monumenti dedicati agli dei e ai Faraoni del passato aumentano il prestigio del quartiere. La gente è contenta di avere vicino delle statue... meglio se grandi." }
    { group:80, id:2, text: "Arco di trionfo" }
    { group:80, id:3, text: "Questo magnifico edificio commemora le storiche vittorie contro i nemici dell'Egitto. Non vi è nulla di più prestigioso." }
    { group:81, id:0, text: "Farmacia" }
    { group:81, id:1, text: "Le farmacie aumentano l'igiene e la salute dei cittadini che vi hanno accesso. Le zone ricche vogliono una farmacia." }
    { group:81, id:2, text: "Questa farmacia non è operativa e non è di alcuna utilità per la comunità locale." }
    { group:81, id:3, text: "Questa farmacia è operativa e fornisce pozioni e unguenti alla comunità locale." }
    { group:82, id:0, text: "Camera mortuaria" }
    { group:82, id:1, text: "Anche se nessuno vuole viverci vicino, le camere mortuarie salvano le vite quando si diffonde una malattia. La città dovrebbe riuscire a imbalsamare tutti i morti." }
    { group:82, id:2, text: "Questa camera mortuaria non è operativa e non è di alcuna utilità per la comunità locale." }
    { group:82, id:3, text: "Questa camera mortuaria è operativa e mummifica i locali con molta professionalità." }
    { group:82, id:4, text: "Senza il lino non possiamo preparare i morti al viaggio verso l'eternità." }
    { group:83, id:0, text: "Medico" }
    { group:83, id:1, text: "Un melograno al giorno toglie il medico di torno. I medici migliorano la salute e l'igiene." }
    { group:83, id:2, text: "Questo medico non è operativo." }
    { group:83, id:3, text: "Il medico è operativo e la comunità locale è in salute e piena forma." }
    { group:84, id:0, text: "Dentista" }
    { group:84, id:1, text: "La sabbia arriva dappertutto, anche nei cibi. L'abrasione continua porta molto lavoro ai dentisti." }
    { group:84, id:2, text: "Questo dentista non è operativo e non è di alcuna utilità per la comunità locale." }
    { group:84, id:3, text: "Questo dentista è operativo e i denti della comunità locale brillano con orgoglio." }
    { group:85, id:0, text: "Scuola degli Scribi" }
    { group:85, id:1, text: "I bambini più piccoli devono frequentare delle scuole nel vicinato per imparare a leggere e scrivere se vogliono diventare come i loro genitori." }
    { group:85, id:2, text: "Questa scuola non è operativa e non è di alcuna utilità alla cittadinanza." }
    { group:85, id:3, text: "Questa scuola è operativa. I bambini del luogo parlano e leggono correttamente." }
    { group:86, id:0, text: "Sinistra" }
    { group:86, id:1, text: "Alto" }
    { group:86, id:2, text: "Destra" }
    { group:86, id:3, text: "Basso" }
    { group:87, id:0, text: "Biblioteca" }
    { group:87, id:1, text: "Qui sono conservate le opere letterarie di tutto il Regno. Gli studiosi ripetono sempre che le biblioteche sono fondamentali per ogni città importante." }
    { group:87, id:2, text: "Gli scaffali di questa biblioteca sono vuoti e inutili per i cittadini." }
    { group:87, id:3, text: "Questa biblioteca è operativa: i suoi scaffali traboccano di sapere." }
    { group:88, id:0, text: "Stazione di polizia" }
    { group:88, id:1, text: "Le stazioni di polizia inviano conestabili per le strade per mantenere la pace. L'ordine civico è possibile solo quando i conestabili controllano le strade regolarmente." }
    { group:88, id:2, text: "Il nostro conestabile è fuori a controllare le strade." }
    { group:88, id:3, text: "Il nostro conestabile si sta preparando a uscire." }
    { group:88, id:4, text: "Al momento, i turni sono al completo. I nostri conestabili sono sempre in servizio sulle strade." }
    { group:88, id:5, text: "Siamo un po' a corto di conestabili. Abbiamo dei buchi di un paio di giorni." }
    { group:88, id:6, text: "Ci manca del personale e c'è un pericoloso vuoto di una settimana nel foglio di servizio." }
    { group:88, id:7, text: "Abbiamo pochi uomini. Spesso nessun conestabile lascia la stazione per due settimane di seguito." }
    { group:88, id:8, text: "Stiamo lavorando come possiamo. Spesso passa più di un mese prima di mandare un conestabile in strada." }
    { group:88, id:9, text: "Senza personale, questa stazione non è altro che un bersaglio per i vandali." }
    { group:88, id:10, text: "furti quest'anno." }
    { group:88, id:11, text: "oro rubato quest'anno." }
    { group:89, id:0, text: "Forte" }
    { group:89, id:1, text: "Questo forte è stato maledetto da Seth e passerà un po' di tempo prima che qualche soldato si avventuri da queste parti." }
    { group:89, id:2, text: "I forti usano i soldati forniti dal reclutatore. Con un'accademia militare, le truppe sarebbero meglio addestrate." }
    { group:90, id:0, text: "Corpo di guardia" }
    { group:90, id:1, text: "Le mura devono essere dotate di un portale, in modo che emigranti, immigranti e commercianti si possano muovere liberamente." }
    { group:91, id:0, text: "Torre" }
    { group:91, id:1, text: "Costruisci torri nelle mura a intervalli regolari o almeno nei punti più vulnerabili. Quando sono collegate a delle strade, le torri ricevono le guardie dal reclutatore. Le torri di guardia scagliano giavellotti contro gli invasori e controllano le mura." }
    { group:91, id:2, text: "Senza personale non possiamo fornire guardie per le torri o per il controllo delle mura." }
    { group:91, id:3, text: "I nostri uomini sono all'erta e pronti a respingere il nemico." }
    { group:91, id:4, text: "Abbiamo del personale ordinario, ma ci mancano le guardie fornite dal reclutatore per difendere la città." }
    { group:92, id:0, text: "Tempio di Osiride (Agricoltura)" }
    { group:92, id:1, text: "Osiride porta fertilità alla terra e fa crescere le messi. Appagalo, se non vuoi patire la fame." }
    { group:93, id:0, text: "Tempio di Ra (il Regno)" }
    { group:93, id:1, text: "I mercanti sanno bene quanto convenga compiacere Ra. Il commercio è più sicuro e conveniente con la sua benedizione e la fama della tua città è più grande." }
    { group:94, id:0, text: "Tempio di Ptah (Artigiani)" }
    { group:94, id:1, text: "Operai e artigiani adorano Ptah per alleviare la loro fatica. Quando Ptah è arrabbiato, nessuna industria può sfuggire alla catastrofe." }
    { group:95, id:0, text: "Tempio di Seth (Distruzione)" }
    { group:95, id:1, text: "Seth protegge i soldati e aumenta il loro valore in combattimento. Nessun uomo osa combattere senza la benedizione di Seth." }
    { group:96, id:0, text: "Tempio di Bast (Casa)" }
    { group:96, id:1, text: "Quando Bast è dispiaciuta, nessuno è più al sicuro in casa propria. Alcuni imputano a Bast anche le malattie." }
    { group:97, id:1, text: "I nostri bazar rendono disponibile i nostri prodotti ai clienti danarosi. Ogni casa necessita di un accesso al bazar, anche se nessuno vuole vivere vicino a uno di essi." }
    { group:97, id:2, text: "Questo bazar non è operativo e non fornisce alcuna merce alla comunità locale." }
    { group:97, id:3, text: "Questo bazar è operativo." }
    { group:97, id:4, text: "Questo bazar ha dei commercianti, ma al momento stanno cercando cibo e prodotti da vendere." }
    { group:97, id:5, text: "Rifornimenti di cibo per" }
    { group:97, id:6, text: "Ordini speciali" }
    { group:97, id:7, text: "Istruzioni bazar" }
    { group:97, id:8, text: "Compra" }
    { group:97, id:9, text: "Non comprare" }
    { group:97, id:10, text: "Il negoziante è qui, in attesa di cibo." }
    { group:97, id:11, text: "Il negoziante è fuori a distribuire merci." }
    { group:97, id:12, text: "Il negoziante sta tornando per prendere altre merci." }
    { group:98, id:1, text: "I granai pieni sono fondamentali per mantenere la pancia dei cittadini piena e attirare nuovi abitanti. Un granaio può conservare qualsiasi tipo di cibo." }
    { group:98, id:5, text: "Ordini speciali" }
    { group:98, id:6, text: "Istruzioni al granaio" }
    { group:98, id:7, text: "Svuotare il granaio" }
    { group:98, id:8, text: "Interrompere lo svuotamento del granaio" }
    { group:98, id:9, text: "Stiamo provando a mandare il cibo da un'altra parte" }
    { group:99, id:0, text: "Deposito merci" }
    { group:99, id:1, text: "Le merci hanno bisogno di un deposito. Le carovane visitano i depositi merci per comprare e vendere e anche i bazar attingono a queste riserve." }
    { group:99, id:2, text: "Ordini speciali" }
    { group:99, id:3, text: "Istruzioni deposito merci" }
    { group:99, id:4, text: "INIZIO svuotamento deposito merci" }
    { group:99, id:5, text: "FINE svuotamento deposito merci" }
    { group:99, id:6, text: "Stiamo provando a mandare le merci da un'altra parte" }
    { group:99, id:7, text: "Non accettare" }
    { group:99, id:8, text: "Non accettare" }
    { group:99, id:9, text: "Ricevimento merci" }
    { group:99, id:10, text: "Ricevimento cibo" }
    { group:99, id:11, text: "Centro commerciale" }
    { group:99, id:12, text: "Trasforma nel centro commerciale" }
    { group:99, id:13, text: "ATTENZIONE Questo deposito merci è pieno. Non può accettare altre merci." }
    { group:99, id:14, text: "ATTENZIONE Questo deposito merci è quasi pieno. Può accettare solo merci già esistenti, ma nessun nuovo tipo." }
    { group:99, id:15, text: "Il nostro carro è qui, in attesa di istruzioni." }
    { group:99, id:16, text: "Il nostro carro sta trasportando della merce." }
    { group:99, id:17, text: "Il nostro carro sta ritornando dopo una consegna." }
    { group:99, id:18, text: "Accetta" }
    { group:99, id:19, text: "Procura" }
    { group:99, id:20, text: "Vuota cibo" }
    { group:99, id:21, text: "Vuota" }
    { group:99, id:22, text: "Il deposito merci è vuoto." }
    { group:99, id:23, text: "blocco di" }
    { group:99, id:24, text: "blocchi di" }
    { group:99, id:25, text: "fino a 1/4" }
    { group:99, id:26, text: "fino a 1/2" }
    { group:99, id:27, text: "fino a 3/4" }
    { group:99, id:28, text: "tutto" }
    { group:99, id:29, text: " " }
    { group:99, id:30, text: "  " }
    { group:99, id:31, text: "cibo" }
    { group:99, id:32, text: "Riempi" }
    { group:99, id:33, text: "Il nostro carrettiere è fuori a prendere le merci" }
    { group:100, id:0, text: "Cantiere" }
    { group:100, id:1, text: "Con lavoratori a sufficienza, il Cantiere costruisce ogni sorta di navi per i moli della città. Le navi da guerra e da trasporto richiedono 100 assi di legno." }
    { group:100, id:2, text: "Produzione completa: " }
    { group:100, id:3, text: " " }
    { group:100, id:4, text: "Al momento, non ci sono moli che ci richiedono delle navi." }
    { group:100, id:5, text: "Stiamo costruendo una nave ordinata da un molo cittadino." }
    { group:100, id:6, text: "Stiamo riparando una nave." }
    { group:100, id:7, text: "Riserva legno," }
    { group:100, id:8, text: "Ci occorre del legno per riparare e costruire navi." }
    { group:100, id:9, text: "Ci manca il legno necessario a completare la nave ordinata da un molo cittadino." }
    { group:100, id:10, text: "Abbiamo diverse navi in attesa di riparazione, ma ci manca il legno per ripararle." }
    { group:101, id:0, text: "Porto" }
    { group:101, id:1, text: "I mercantili di tutto il molo attraccano qui per consegnare le merci importate e caricare quelle da esportare. Non puoi commerciare via mare senza gli scali." }
    { group:101, id:2, text: "Senza portuali non è possibile scaricare e caricare le navi attraccate." }
    { group:101, id:3, text: "Ci stiamo occupando delle navi attraccate, ci potrebbe però volere un po' di tempo perché abbiamo pochi portuali." }
    { group:101, id:4, text: "Ci stiamo occupando delle navi attraccate, anche se i nostri ranghi non sono completi e così ci vorrà un tempo leggermente superiore rispetto al solito." }
    { group:101, id:5, text: "Ci stiamo occupando delle navi attraccate e con tutti i nostri portuali al lavoro stiamo funzionando a pieno regime." }
    { group:101, id:6, text: "Le navi che attraccano qui non trovano nessuno per caricare o scaricare le loro merci." }
    { group:101, id:7, text: "Qui lavorano pochissimi portuali, perciò ci vuole molto tempo per caricare e scaricare le navi che arrivano al molo." }
    { group:101, id:8, text: "Siamo a corto di personale, per cui ci vuole più tempo del normale per le operazioni di carico e di scarico delle navi attraccate." }
    { group:101, id:9, text: "Abbiamo tutti i portuali necessari per svolgere velocemente le operazioni di carico e di scarico." }
    { group:102, id:0, text: "Banchina da pesca" }
    { group:102, id:1, text: "Le barche arrivano qui dal cantiere per recuperare l'equipaggio e iniziare l'attività di pesca. Ogni banchina può servire una sola barca da pesca." }
    { group:102, id:2, text: "Al momento stiamo aspettando che il cantiere ci costruisca una nave da pesca." }
    { group:102, id:3, text: "La nostra barca sta veleggiando verso le zone di pesca." }
    { group:102, id:4, text: "La nostra barca sta attualmente pescando nella propria zona di pesca." }
    { group:102, id:5, text: "La nostra barca sta facendo ritorno alla banchina." }
    { group:102, id:6, text: "Stiamo rifornendo la barca da pesca per un altro viaggio." }
    { group:102, id:7, text: "La nostra barca sta tornando dalla zona di pesca, con il suo carico di pesci." }
    { group:102, id:8, text: "I nostri pescatori stanno aspettando la scoperta di qualche zona di pesca nella provincia. Non ci sono pesci ed essi non riescono a guadagnarsi da vivere." }
    { group:102, id:9, text: "Il supervisore commerciale ha fermato l'industria della pesca." }
    { group:102, id:10, text: "La nostra barca da pesca non può uscire nelle acque inquinate!" }
    { group:103, id:0, text: "Magione" }
    { group:103, id:1, text: "La tua casa è uno degli indirizzi più ambiti della città. La tua magione ti dà il diritto di ricevere un salario." }
    { group:103, id:2, text: "Deben al mese" }
    { group:103, id:3, text: "Salario da Anziano del villaggio" }
    { group:103, id:4, text: "Salario da Nobile del villaggio" }
    { group:103, id:5, text: "Salario da Studioso reale" }
    { group:103, id:6, text: "Salario da Scriba reale" }
    { group:103, id:7, text: "Salario da Giudice reale" }
    { group:103, id:8, text: "Salario da Sindaco reale" }
    { group:103, id:9, text: "Salario da Governatore reale" }
    { group:103, id:10, text: "Salario da Nomarca" }
    { group:103, id:11, text: "Salario da Cancelliere" }
    { group:103, id:12, text: "Salario da Consigliere" }
    { group:103, id:13, text: "Salario da Faraone" }
    { group:104, id:0, text: "Centro di architettura" }
    { group:104, id:1, text: "Gli architetti egizi sono tra i più bravi del mondo. La manutenzione costante previene il crollo degli edifici." }
    { group:104, id:2, text: "Il nostro architetto è molto impegnato." }
    { group:104, id:3, text: "Il nostro architetto si sta preparando a uscire." }
    { group:104, id:4, text: "Non abbiamo neanche un minuto libero: i nostri architetti sono sempre impegnati a ispezionare e riparare i danni agli edifici della città." }
    { group:104, id:5, text: "Ci vorranno un giorno o due prima che i nostri architetti escano di nuovo in strada." }
    { group:104, id:6, text: "Ci manca del personale, perciò ci vorrà una settimana prima di riprendere con le ispezioni delle case." }
    { group:104, id:7, text: "Abbiamo pochissimi ingegneri, tra i giri d'ispezione c'è un periodo scoperto di due settimane." }
    { group:104, id:8, text: "Siamo ridotti all'osso: riusciamo a malapena a far uscire un architetto al mese." }
    { group:104, id:9, text: "Senza architetti, questo stesso edificio rischia di crollare da un momento all'altro." }
    { group:105, id:0, text: "Palazzo" }
    { group:105, id:1, text: "Il Palazzo è uno degli edifici più ambiti della città e punto fondamentale dell'economia cittadina. Trasforma l'oro in deben e custodisce parte dei fondi cittadini." }
    { group:106, id:0, text: "Esattoria" }
    { group:106, id:1, text: "Anche se non è uno degli impiegati più popolari in città, l'esattore lavora per il bene del Regno e tutti i benefici che ne derivano." }
    { group:106, id:2, text: "Il tesoro è di" }
    { group:106, id:3, text: "L'esattore è fuori al lavoro." }
    { group:106, id:4, text: "L'esattore si sta preparando a uscire." }
    { group:106, id:5, text: "Al momento stiamo lavorando con il massimo dell'efficienza, tutti gli esattori della città controllano che le tasse dovute siano pagate." }
    { group:106, id:6, text: "Stiamo attraversando un momento critico, tra un giorno o due potremo inviare tutti gli esattori per riscuotere le tasse." }
    { group:106, id:7, text: "C'è scarsità di personale e dobbiamo attendere una settimana prima che gli esattori tornino al lavoro." }
    { group:106, id:8, text: "Abbiamo davvero bisogno di personale, passeranno due settimane prima di riprendere il lavoro con regolarità." }
    { group:106, id:9, text: "Con così poca gente, i cittadini possono evadere le tasse in tutta tranquillità." }
    { group:106, id:10, text: "Quest'ufficio, privo com'è di esattori, non contribuisce per niente al tesoro cittadino." }
    { group:106, id:11, text: "Alla tua città occorre un Palazzo per riscuotere le tasse." }
    { group:106, id:12, text: "Alla tua città occorre un Palazzo del Lavoro per riscuotere le tasse." }
    { group:107, id:0, text: "Pompa idraulica" }
    { group:107, id:1, text: "Il solleva acqua distribuisce grandi quantità d'acqua quando è collegato ai canali di irrigazione." }
    { group:107, id:2, text: "Questo solleva acqua non funziona. Consulta il supervisore del lavoro per assegnare più lavoratori ai servizi d'acqua." }
    { group:107, id:3, text: "Per poter funzionare, questa pompa idraulica deve essere vicina all'acqua o collegata tramite un canale di irrigazione a una pompa funzionante." }
    { group:108, id:0, text: "Serbatoio d'acqua" }
    { group:108, id:1, text: "I trasportatori d'acqua prendono l'acqua potabile dalle cisterne e migliorano la salute nonché l'umore di tutti coloro che visitano." }
    { group:108, id:2, text: "Il nostro personale è sempre in giro a distribuire acqua alla popolazione." }
    { group:108, id:3, text: "Siamo a corto di trasportatori d'acqua. Abbiamo dei buchi di un giorno o due." }
    { group:108, id:4, text: "Siamo a corto di personale e abbiamo pericolosi buchi anche di una settimana prima di completare il ciclo di consegne." }
    { group:108, id:5, text: "Abbiamo troppo pochi impiegati. A volte, non possiamo consegnare acqua per due settimane di seguito." }
    { group:108, id:6, text: "Lavoriamo in condizioni disastrose. Spesso passa un mese intero senza che possiamo consegnare dell'acqua." }
    { group:108, id:7, text: "Senza personale, questo servizio è utile quanto un buco nella sabbia." }
    { group:110, id:0, text: "Oracolo" }
    { group:110, id:1, text: "Questo santuario aumenta il prestigio delle case vicine e rende onore agli dei. Ma non impiega sacerdoti o fornisce l'accesso a una divinità particolare." }
    { group:111, id:0, text: "Rovine in fiamme" }
    { group:111, id:1, text: "I vigili del fuoco non sono riusciti ad arrivare in tempo per salvare l'edificio. Quando il fuoco si estinguerà, rimarranno solo delle macerie carbonizzate." }
    { group:112, id:0, text: "Coltivazione di grano" }
    { group:112, id:1, text: "Il grano deve essere conservato nei granai per sfamare la gente, o nei depositi se deve essere esportato." }
    { group:112, id:2, text: "Produzione completa: " }
    { group:112, id:3, text: " " }
    { group:112, id:4, text: "Il supervisore commerciale ha fermato le coltivazioni di grano." }
    { group:112, id:5, text: "Questa fattoria non ha braccianti. Il terreno è inutilizzato." }
    { group:112, id:6, text: "Questa fattoria ha tutti i braccianti di cui ha bisogno e sfrutta al massimo il suo terreno." }
    { group:112, id:7, text: "Questa fattoria funziona a ritmo ridotto, con più braccianti potrebbe risultare più produttiva." }
    { group:112, id:8, text: "In questa fattoria mancano dei braccianti. Quelli che si sono ci mettono molto tempo a ottenere un raccolto." }
    { group:112, id:9, text: "Qui lavorano pochi contadini e la produzione di grano è bassa." }
    { group:112, id:10, text: "Questa fattoria non ha braccianti e la produzione è virtualmente ferma." }
    { group:112, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:112, id:12, text: "Terra fertile: " }
    { group:112, id:13, text: " " }
    { group:112, id:14, text: "Il prossimo raccolto di grano è a" }
    { group:113, id:0, text: "Coltivazione di lattuga" }
    { group:113, id:1, text: "La lattuga è importante per una dieta salutare. I granai conservano la lattuga per il consumo locale, mentre i depositi merci contengono il surplus destinato all'esportazione." }
    { group:113, id:2, text: "Produzione completa: " }
    { group:113, id:3, text: " " }
    { group:113, id:4, text: "Il supervisore commerciale ha fermato le coltivazioni di lattuga." }
    { group:113, id:5, text: "Questa fattoria non ha braccianti. Non è stato piantato niente." }
    { group:113, id:6, text: "Questa fattoria ha tutti gli impiegati che occorrono. Qui la lattuga cresce in abbondanza." }
    { group:113, id:7, text: "La fattoria lavora al di sotto della sua massima capacità; quindi, la produzione di lattuga è un po' lenta." }
    { group:113, id:8, text: "Questa fattoria non ha personale a sufficienza. La lattuga impiega molto più tempo a crescere." }
    { group:113, id:9, text: "Qui ci sono pochissimi braccianti: ci vorrà molto tempo prima di ottenere del cibo." }
    { group:113, id:10, text: "Visti i braccianti assolutamente insufficienti, ben difficilmente qui crescerà qualcosa di commestibile." }
    { group:113, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:113, id:12, text: "Terra fertile: " }
    { group:113, id:13, text: " " }
    { group:113, id:14, text: "Il prossimo raccolto di lattuga è a" }
    { group:114, id:0, text: "Coltivazione di melograni" }
    { group:114, id:1, text: "I melograni contribuiscono a una dieta equilibrata per tutti i cittadini. I granai conservano i melograni per il consumo locale, i depositi merci contengono il surplus destinato all'esportazione." }
    { group:114, id:2, text: "Produzione completa: " }
    { group:114, id:3, text: " " }
    { group:114, id:4, text: "Il supervisore commerciale ha fermato le coltivazioni di melograni." }
    { group:114, id:5, text: "Questo frutteto non ha braccianti. Non è stato raccolto niente." }
    { group:114, id:6, text: "Questo orto ha tutti i braccianti che servono. Gli alberi sono carichi di succulenti melograni." }
    { group:114, id:7, text: "Questo orto lavora sotto la sua capacità massima, la produzione di melograni è rallentata." }
    { group:114, id:8, text: "Questo orto non ha braccianti a sufficienza. Produce melograni molto lentamente." }
    { group:114, id:9, text: "In questo orto lavorano ben pochi braccianti. Il raccolto di melograni sarà molto in ritardo." }
    { group:114, id:10, text: "Con così pochi braccianti, ci vorranno dei secoli prima di vedere un melograno." }
    { group:114, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:114, id:12, text: "Terra fertile: " }
    { group:114, id:13, text: " " }
    { group:114, id:14, text: "Il prossimo raccolto di melograni è a" }
    { group:115, id:0, text: "Coltivazione di lino" }
    { group:115, id:1, text: "Il lino è il materiale grezzo per tessuti pregiati. Le botteghe lavorano e filano il lino per creare la tela per l'imbalsamazione o per l'esportazione." }
    { group:115, id:2, text: "Produzione completa: " }
    { group:115, id:3, text: " " }
    { group:115, id:4, text: "Il supervisore commerciale ha fermato le coltivazioni di lino." }
    { group:115, id:5, text: "Questa fattoria non ha impiegati. La produzione di lino è ferma." }
    { group:115, id:6, text: "Questa fattoria ha tutti i braccianti che servono. I campi sono blu per il gran numero di fiori di lino." }
    { group:115, id:7, text: "La fattoria lavora al di sotto della sua massima capacità, quindi la produzione di lino è un po' lenta." }
    { group:115, id:8, text: "Questa fattoria non ha personale a sufficienza. La produzione di lino è più lenta." }
    { group:115, id:9, text: "Qui ci sono pochissimi braccianti. La produzione di lino è molto più lenta." }
    { group:115, id:10, text: "Con così pochi contadini, il suolo è diventato praticamente sterile." }
    { group:115, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:115, id:12, text: "Terra fertile: " }
    { group:115, id:13, text: " " }
    { group:115, id:14, text: "Il prossimo raccolto di lino è a" }
    { group:116, id:0, text: "Raccoglitore di canne" }
    { group:116, id:1, text: "Da qui i raccoglitori di canne si avventurano nelle paludi per raccogliere le canne del papiro, senza le quali l'istruzione sarebbe impossibile." }
    { group:116, id:2, text: "Canne raccolte" }
    { group:116, id:3, text: " " }
    { group:116, id:4, text: "Il supervisore commerciale ha fermato la raccolta delle canne." }
    { group:116, id:5, text: "Questo luogo non impiega nessuno per raccogliere le canne." }
    { group:116, id:6, text: "Questo luogo ha tutti i lavoratori che occorrono. Nessuna canna è al sicuro." }
    { group:116, id:7, text: "Questo posto è sotto il suo potenziale di impiego; quindi, la raccolta è un po' rallentata." }
    { group:116, id:8, text: "Questo posto non ha abbastanza raccoglitori, la raccolta delle canne va a rilento." }
    { group:116, id:9, text: "Con così pochi lavoratori, le canne si raccolgono molto lentamente." }
    { group:116, id:10, text: "Con così pochi lavoratori, le canne praticamente non vengono raccolte." }
    { group:116, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:116, id:12, text: "Terra fertile: " }
    { group:116, id:13, text: " " }
    { group:116, id:14, text: "La prossima raccolta di canne è a" }
    { group:117, id:0, text: "Allevamento bestiame" }
    { group:117, id:1, text: "I cittadini ben nutriti esigono la carne nella loro dieta. La carne può essere conservata nei granai per il consumo locale oppure nei depositi merci per l'esportazione." }
    { group:117, id:2, text: "Produzione completa: " }
    { group:117, id:3, text: " " }
    { group:117, id:4, text: "Il supervisore commerciale ha fermato l'allevamento di bestiame." }
    { group:117, id:5, text: "Questo allevamento non ha impiegati. Gli animali sono fuggiti o sono morti." }
    { group:117, id:6, text: "Questo allevamento ha tutti gli impiegati che occorrono. Con la paglia necessaria, può produrre molta carne." }
    { group:117, id:7, text: "Questo allevamento deve assumere più lavoranti, se vuole produrre con efficienza." }
    { group:117, id:8, text: "Questo allevamento è a corto di personale. Non può raggiungere la piena efficienza." }
    { group:117, id:9, text: "In questo allevamento lavorano pochissime persone. La produzione di carne è molto lenta." }
    { group:117, id:10, text: "Con così pochi lavoranti, questo allevamento può allevare ben poche mandrie." }
    { group:117, id:11, text: "Questo allevamento è stato sconvolto dalla recente invasione di locuste. Le mandrie non possono prosperare finché non si riprende." }
    { group:117, id:12, text: "Terra fertile: " }
    { group:117, id:13, text: " " }
    { group:118, id:0, text: "Cava di pietra" }
    { group:118, id:1, text: "Qui puoi estrarre la pietra. Con tutti i monumenti che sorgeranno in Egitto, puoi sempre trovare un acquirente, sempre che a te non serva." }
    { group:118, id:2, text: "Produzione completa: " }
    { group:118, id:3, text: " " }
    { group:118, id:4, text: "Il supervisore commerciale ha fermato l'estrazione della pietra." }
    { group:118, id:5, text: "Questa cava non ha operai. La produzione di marmo è ferma." }
    { group:118, id:6, text: "Questa cava ha tutti i lavoratori che occorrono e produce varie tonnellate di pietra." }
    { group:118, id:7, text: "Questa cava funziona a ritmo ridotto: la produzione di marmo procede a un ritmo leggermente inferiore al normale." }
    { group:118, id:8, text: "Questa cava è a corto di personale e l'estrazione della pietra impiega più tempo del dovuto." }
    { group:118, id:9, text: "In questa cava lavorano pochissime persone. La produzione è molto lenta." }
    { group:118, id:10, text: "Con così pochi lavoratori, la produzione di questa cava è praticamente ferma. Produrrà ben poco per il prossimo anno." }
    { group:119, id:0, text: "Cava di calcare" }
    { group:119, id:1, text: "Qui puoi estrarre il calcare da usare per i monumenti o per l'esportazione." }
    { group:119, id:2, text: "Produzione completa: " }
    { group:119, id:3, text: " " }
    { group:119, id:4, text: "Il supervisore commerciale ha fermato l'estrazione di calcare." }
    { group:119, id:5, text: "Questa cava non ha lavoratori e quindi non estrae calcare." }
    { group:119, id:6, text: "Questa cava ha tutti i lavoratori che occorrono. La produzione è al massimo." }
    { group:119, id:7, text: "Questa cava funziona a ritmo ridotto. La produzione sarebbe migliore con più lavoratori." }
    { group:119, id:8, text: "Questo edificio è a corto di personale. La produzione di calcare va a rilento." }
    { group:119, id:9, text: "In questo edificio lavorano pochissime persone. La produzione è molto rallentata." }
    { group:119, id:10, text: "Con così pochi lavoratori, l'estrazione di calcare è quasi impossibile." }
    { group:120, id:0, text: "Taglialegna" }
    { group:120, id:1, text: "Il legno ha molti usi, dalla costruzione dei monumenti a quella delle navi ed è sempre richiesto in tutto il Regno." }
    { group:120, id:2, text: "Unità" }
    { group:120, id:3, text: "Legno grezzo." }
    { group:120, id:4, text: "Il supervisore commerciale ha ordinato di sospendere il taglio degli alberi." }
    { group:120, id:5, text: "Questa fabbrica non ha lavoratori e non contribuisce all'economia cittadina." }
    { group:120, id:6, text: "Questo edificio ha tutti i taglialegna che occorrono: la produzione di legname procede velocemente." }
    { group:120, id:7, text: "Questo deposito funziona a ritmo ridotto, la produzione di legname è leggermente inferiore alla norma." }
    { group:120, id:8, text: "In questo deposito manca del personale, si tagliano meno alberi di quanti sarebbe possibile." }
    { group:120, id:9, text: "Qui ci sono pochi taglialegna e come risultato la produzione di legname procede a rilento." }
    { group:120, id:10, text: "Questo deposito, praticamente senza taglialegna, ha una produzione quasi azzerata." }
    { group:121, id:0, text: "Cava d'argilla" }
    { group:121, id:1, text: "Fabbrica l'argilla per esportarla o per rifornire i vasai. I vasi sono sempre utili e rendono bene anche per il commercio." }
    { group:121, id:2, text: "Produzione completa: " }
    { group:121, id:3, text: " " }
    { group:121, id:4, text: "Il supervisore commerciale ha ordinato di sospendere l'estrazione di argilla." }
    { group:121, id:5, text: "Questa cava non ha operai. La produzione è ferma." }
    { group:121, id:6, text: "Questa cava ha tutti gli operai di cui ha bisogno: la produzione di argilla procede velocemente." }
    { group:121, id:7, text: "Questa cava funziona a ritmo ridotto: per questo la produzione di argilla risulta leggermente inferiore alla norma." }
    { group:121, id:8, text: "In questa cava manca del personale, l'estrazione di argilla non è veloce come dovrebbe essere." }
    { group:121, id:9, text: "Qui ci sono pochi operai e come risultato la produzione di argilla procede a rilento." }
    { group:121, id:10, text: "Questa cava, praticamente senza operai, ha una produzione pari a zero. Nel prossimo anno da qui arriverà pochissima argilla." }
    { group:122, id:0, text: "Distilleria" }
    { group:122, id:1, text: "I distillatori trasformano l'orzo in birra, senza la quale le taverne sarebbero vuote e le festività noiose. La birra è un bene molto richiesto." }
    { group:122, id:2, text: "Produzione completa: " }
    { group:122, id:3, text: " " }
    { group:122, id:4, text: "Il supervisore commerciale ha fermato la produzione di birra." }
    { group:122, id:5, text: "Questa distilleria non ha impiegati. La produzione è ferma." }
    { group:122, id:6, text: "Questa distilleria ha tutti gli impiegati che occorrono e lavora al massimo." }
    { group:122, id:7, text: "Questa distilleria lavora a ritmo ridotto. La produzione di birra va a rilento." }
    { group:122, id:8, text: "Questa distilleria è a corto di personale e produce birra più lentamente di quanto dovrebbe." }
    { group:122, id:9, text: "In questa distilleria lavorano pochissime persone. La produzione di birra è molto lenta." }
    { group:122, id:10, text: "Con così pochi lavoratori, la produzione di questa distilleria è praticamente ferma. Produrrà poca birra per il prossimo anno." }
    { group:122, id:11, text: "Questa distilleria non può produrre birra finché non riceve una fornitura d'orzo da un deposito merci o una coltivazione." }
    { group:122, id:12, text: "Orzo conservato," }
    { group:123, id:0, text: "Tessitoria" }
    { group:123, id:1, text: "Qui il lino viene trasformato in tela, necessaria alle camere mortuarie per l'imbalsamazione. Il lino può anche essere esportato con buon profitto." }
    { group:123, id:2, text: "Produzione completa: " }
    { group:123, id:3, text: " " }
    { group:123, id:4, text: "Il supervisore commerciale ha deciso di fermare la produzione di tela." }
    { group:123, id:5, text: "Questa tessitoria non ha lavoratori e non produce tela." }
    { group:123, id:6, text: "Questa tessitoria lavora al massimo e produce grandi quantità di tela." }
    { group:123, id:7, text: "Questa tessitoria potrebbe sfruttare più lavoratori per produrre al massimo." }
    { group:123, id:8, text: "Questa tessitoria è a corto di manodopera e produce tela più lentamente di quanto potrebbe fare." }
    { group:123, id:9, text: "Qui lavorano pochissime persone e la produzione di tela va a rilento." }
    { group:123, id:10, text: "Con così pochi addetti, la produzione è agli sgoccioli. Produrrà ben poca tela per il prossimo anno." }
    { group:123, id:11, text: "Questa fabbrica non produrrà tela senza una fornitura di lino da un deposito o da una fattoria." }
    { group:123, id:12, text: "Tela immagazzinata," }
    { group:124, id:0, text: "Armeria" }
    { group:124, id:1, text: "Gli armaioli trasformano il rame in armi che puoi vendere con profitto o usare per equipaggiare le tue compagnie." }
    { group:124, id:2, text: "Produzione completa: " }
    { group:124, id:3, text: " " }
    { group:124, id:4, text: "Il supervisore commerciale ha ordinato di sospendere la produzione di armi." }
    { group:124, id:5, text: "Quest'armeria non ha operai. La produzione è ferma." }
    { group:124, id:6, text: "Quest'armeria ha tutti gli operai di cui ha bisogno: la produzione di armi procede a ritmo spedito." }
    { group:124, id:7, text: "Quest'armeria funziona a ritmo ridotto, per cui la produzione di armi risulta essere leggermente inferiore alla media." }
    { group:124, id:8, text: "In quest'armeria manca del personale, la produzione di armi non è veloce come dovrebbe essere." }
    { group:124, id:9, text: "Qui ci sono pochi operai e come risultato la produzione di armi procede a rilento." }
    { group:124, id:10, text: "Quest'armeria ha ben pochi lavoratori e produce pochissime armi." }
    { group:124, id:11, text: "Per produrre armi, questa fabbrica ha bisogno di rame, da un deposito merci o una miniera di rame." }
    { group:124, id:12, text: "Rame in magazzino," }
    { group:125, id:0, text: "Gioielleria" }
    { group:125, id:1, text: "Gli artigiani di questa industria creano splendidi gioielli (beni di lusso) con le gemme. Alcuni cittadini vogliono i gioielli per se stessi, ma puoi esportare qualsiasi eccedenza." }
    { group:125, id:2, text: "Produzione completa: " }
    { group:125, id:3, text: " " }
    { group:125, id:4, text: "Il supervisore commerciale ha fermato la produzione di gioielli." }
    { group:125, id:5, text: "Questo laboratorio non ha gioiellieri. La produzione è ferma." }
    { group:125, id:6, text: "Questo laboratorio ha il massimo di impiegati e produce gioielli (beni di lusso) in gran quantità." }
    { group:125, id:7, text: "Questo laboratorio cerca artigiani. La produzione di gioielli (beni di lusso) migliorerà quando li avrà trovati." }
    { group:125, id:8, text: "Questo laboratorio è a corto di personale e impiega più di quanto dovrebbe per produrre gioielli (beni di lusso)." }
    { group:125, id:9, text: "Qui lavorano pochissimi artigiani. La produzione di gioielli (beni di lusso) è molto lenta." }
    { group:125, id:10, text: "Con così pochi artigiani, questo gioielliere produrrà ben pochi beni di lusso per il prossimo anno." }
    { group:125, id:11, text: "Per realizzare gioielli, questo laboratorio necessita di una fornitura di gemme da un deposito o da una miniera." }
    { group:125, id:12, text: "Gemme in magazzino," }
    { group:126, id:0, text: "Vasaio" }
    { group:126, id:1, text: "Qui i vasai formano l'argilla in vasi che i cittadini usano per conservare i beni. Esporta i vasi o distribuiscili tramite i bazar, cosicché la gente possa costruire abitazioni migliori." }
    { group:126, id:2, text: "Produzione completa: " }
    { group:126, id:3, text: " " }
    { group:126, id:4, text: "Il supervisore commerciale ha ordinato di sospendere la produzione di vasellame." }
    { group:126, id:5, text: "Quest'armeria non ha operai. La produzione è ferma." }
    { group:126, id:6, text: "Questa fabbrica ha tutti gli operai di cui ha bisogno: la produzione di vettovaglie procede a ritmo spedito." }
    { group:126, id:7, text: "Questa fabbrica funziona a ranghi ridotti: la produzione di vettovaglie è pertanto leggermente inferiore al normale." }
    { group:126, id:8, text: "In questa fabbrica manca del personale, la produzione di vettovaglie non è veloce come dovrebbe essere." }
    { group:126, id:9, text: "Qui ci sono pochi operai e come risultato la produzione di vettovaglie procede a rilento." }
    { group:126, id:10, text: "Con così pochi impiegati, questo vasaio non produrrà quasi alcun vaso per il prossimo anno." }
    { group:126, id:11, text: "Per produrre vasi, questo laboratorio necessita di una fornitura d'argilla da un deposito merci o da una cava d'argilla." }
    { group:126, id:12, text: "Argilla in magazzino," }
    { group:127, id:0, text: "Abitazione" }
    { group:127, id:1, text: "Modalità test NO" }
    { group:127, id:2, text: "Modalità test SI" }
    { group:127, id:3, text: "Desiderabilità" }
    { group:127, id:4, text: "Ent***" }
    { group:127, id:5, text: "H2O" }
    { group:127, id:6, text: "Religione" }
    { group:127, id:7, text: "Educazione" }
    { group:127, id:8, text: "Accesso al bazar" }
    { group:127, id:9, text: "Accesso al dentista" }
    { group:127, id:10, text: "Accesso al medico" }
    { group:127, id:11, text: "Salute" }
    { group:127, id:12, text: "Tipi di cibo" }
    { group:127, id:13, text: "Vettovaglie necessarie" }
    { group:127, id:14, text: "Occorre tela" }
    { group:127, id:15, text: "Occorrono beni di lusso" }
    { group:127, id:16, text: "Occorre birra" }
    { group:127, id:17, text: "Ora" }
    { group:127, id:18, text: "si evolve in" }
    { group:127, id:19, text: "ha bisogno" }
    { group:127, id:20, text: "occupanti" }
    { group:127, id:21, text: "troppi." }
    { group:127, id:22, text: "spazio extra per" }
    { group:127, id:23, text: "Non visitato da un esattore. Non paga tasse." }
    { group:127, id:24, text: "Generati" }
    { group:127, id:25, text: "finora in tasse." }
    { group:127, id:26, text: "I residenti non hanno segnalato alcun crimine." }
    { group:127, id:27, text: "Questo è un quartiere tranquillo." }
    { group:127, id:28, text: "Ogni tanto qui avviene qualche crimine, ma niente di serio." }
    { group:127, id:29, text: "Il crimine qui sta diventando un problema." }
    { group:127, id:30, text: "L'elevata criminalità infastidisce gli abitanti." }
    { group:127, id:31, text: "Un quartiere senza legge. I residenti sono terrorizzati." }
    { group:127, id:32, text: "Questo è un luogo in cui si annidano molti ladri." }
    { group:127, id:33, text: "I capanni non miglioreranno finché non riceveranno cibo da un bazar." }
    { group:127, id:34, text: "Abitazione LIBERA" }
    { group:127, id:35, text: "Abitazione LIBERA" }
    { group:127, id:36, text: "Abitazione LIBERA" }
    { group:127, id:37, text: "Abitazione LIBERA" }
    { group:127, id:38, text: "Abitazione LIBERA" }
    { group:127, id:39, text: "Abitazione LIBERA" }
    { group:127, id:40, text: "Questa casa peggiorerà presto, la scarsa qualità della vita in questo quartiere la sta facendo decadere." }
    { group:127, id:42, text: "Questa casa peggiorerà presto, perché non è stata visitata da un portatore d'acqua da molto tempo" }
    { group:127, id:43, text: "Questa casa peggiorerà presto, perché in questo quartiere non ci sono intrattenimenti." }
    { group:127, id:44, text: "Questa casa peggiorerà presto, perché nei dintorni è molto difficile trovare qualche passatempo." }
    { group:127, id:45, text: "Questa casa peggiorerà presto, perché gli intrattenimenti sono troppo scadenti in questo quartiere." }
    { group:127, id:46, text: "Questa casa peggiorerà presto. Nei dintorni si trova qualche passatempo, ma non a sufficienza." }
    { group:127, id:47, text: "Questa casa peggiorerà presto. Gli intrattenimenti in zona sono abbondanti, ma non vari." }
    { group:127, id:48, text: "Questa casa presto peggiorerà. Nelle vicinanze è possibile trovare divertimento in abbondanza, ma le strade sono troppo affollate o manca la dovuta varietà per le classi di scribi." }
    { group:127, id:49, text: "Questa casa presto peggiorerà, in quanto non riceve da molto tempo un rifornimento di cibo dal bazar locale." }
    { group:127, id:50, text: "Questa casa presto peggiorerà, perché al momento ha accesso a un solo tipo di cibo dal bazar locale. Il fatto scoraggia i cittadini più abbienti." }
    { group:127, id:51, text: "Questa casa presto peggiorerà, perché al momento ha accesso a solo due tipi di cibo dal bazar locale. Questo scoraggia gli scribi." }
    { group:127, id:52, text: "Questa casa presto peggiorerà. Ha perso l'accesso al bazar." }
    { group:127, id:53, text: "Questa casa presto peggiorerà. Anche se ha accesso al bazar, quest'ultimo trova difficile recuperare il cibo." }
    { group:127, id:54, text: "Questa casa presto peggiorerà, perché ha perso le strutture di istruzione di base come la scuola degli scribi o la biblioteca." }
    { group:127, id:55, text: "Questa casa peggiorerà presto. Il suo accesso alle strutture educative è stato diminuito, o non ha più accesso alla sua biblioteca." }
    { group:127, id:56, text: "Questa casa presto peggiorerà. Il suo accesso all'istruzione si è degradato, in quanto ha perso l'accesso alla sua scuola di scribi." }
    { group:127, id:57, text: "Questa casa presto peggiorerà. Il suo precedente e ottimo accesso scolastico è peggiorato con la mancanza di una istruzione avanzata." }
    { group:127, id:58, text: "Questa casa presto peggiorerà, perché non ha accesso ai magistrati del palazzo di giustizia." }
    { group:127, id:59, text: "Questa casa presto peggiorerà. Ha finito i vasi e il bazar locale non riesce a procurarli con continuità." }
    { group:127, id:60, text: "Questa casa peggiorerà presto, perché non ha più accesso a nessuna delle strutture religiose locali." }
    { group:127, id:61, text: "Questa casa peggiorerà presto. Il suo accesso alle strutture religiose è stato ridotto e ora può utilizzare il tempio di una sola religione." }
    { group:127, id:62, text: "Questa casa peggiorerà presto. Il suo accesso alla religione, in precedenza eccellente, è peggiorato: ora può utilizzare templi di due sole religioni." }
    { group:127, id:63, text: "Questa casa presto peggiorerà, perché ha perso l'accesso al dentista." }
    { group:127, id:64, text: "Questa casa presto peggiorerà, perché ora ha un pessimo accesso all'igiene. Non solo le manca l'accesso a un becchino, ma l'accesso al medico certo non è perfetto." }
    { group:127, id:65, text: "Questa casa presto peggiorerà, perché ha perso delle cure sanitarie. I medici vanno bene, ma manca l'accesso a una camera mortuaria locale." }
    { group:127, id:66, text: "Questa casa presto peggiorerà, perché ha perso delle cure sanitarie. Le camere mortuarie, vanno bene ma manca l'accesso a un medico." }
    { group:127, id:67, text: "Questa casa presto peggiorerà, perché ha finito le scorte di tela e il bazar locale non riesce a fornirla con continuità." }
    { group:127, id:68, text: "Inutilizzato" }
    { group:127, id:69, text: "Questa casa presto peggiorerà, perché ha finito le scorte di birra e il bazar locale non riesce a fornirla con continuità." }
    { group:127, id:70, text: "Questa dimora non può svilupparsi finché non migliora la desiderabilità della zona." }
    { group:127, id:71, text: "Questa casa presto peggiorerà perché non ha accesso neppure a una forma primitiva di sorgente d'acqua." }
    { group:127, id:72, text: "Questa casa non può svilupparsi perché non ha accesso alla fornitura d'acqua." }
    { group:127, id:73, text: "Questa casa non può migliorare, perché in questo quartiere non ci sono intrattenimenti." }
    { group:127, id:74, text: "Questa casa non può migliorare, perché nei dintorni è molto difficile trovare qualche passatempo." }
    { group:127, id:75, text: "Questa casa non può migliorare, perché gli intrattenimenti sono troppo scadenti in questo quartiere." }
    { group:127, id:76, text: "Questa casa non può migliorare, perché anche se nei dintorni si trova qualche passatempo, essi non sono sufficienti." }
    { group:127, id:77, text: "Questa casa non può migliorare, gli intrattenimenti in zona sono abbondanti, ma non sono vari." }
    { group:127, id:78, text: "Questa casa non può svilupparsi. Nelle vicinanze è possibile trovare divertimento in abbondanza, ma le strade sono troppo affollate o manca la dovuta varietà per le classi di scribi." }
    { group:127, id:79, text: "Questa casa non può svilupparsi, in quanto non riceve da molto tempo un rifornimento di cibo dal bazar locale." }
    { group:127, id:80, text: "Questa casa non può svilupparsi perché manca l'accesso a un secondo tipo di cibo, fornito dal bazar locale, per incoraggiare gli egizi più ricchi a entrare." }
    { group:127, id:81, text: "Questa casa non può svilupparsi perché manca l'accesso a un terzo tipo di cibo, fornito dal bazar locale, per incoraggiare gli egizi più ricchi a entrare." }
    { group:127, id:82, text: "Questa casa non può svilupparsi perché non ha accesso a un bazar locale." }
    { group:127, id:83, text: "Questa casa non può svilupparsi. Anche se ha accesso al bazar locale, esso trova difficile recuperare il cibo." }
    { group:127, id:84, text: "Questa casa non può svilupparsi, perché non ha le strutture di istruzione di base come la scuola degli scribi o la biblioteca." }
    { group:127, id:85, text: "Questa casa non può migliorare, il suo accesso alle strutture educative deve essere migliorato con la creazione di una biblioteca." }
    { group:127, id:86, text: "Questa casa non può migliorare, il suo accesso alle strutture educative deve essere migliorato con l'accesso a una scuola di scribi." }
    { group:127, id:87, text: "-" }
    { group:127, id:88, text: "Questa casa non può svilupparsi, perché non ha accesso ai magistrati del palazzo di giustizia." }
    { group:127, id:89, text: "Questa casa non può svilupparsi. Occorrono forniture di vasi dal bazar locale prima che le classi più ricche decidano di entrare." }
    { group:127, id:90, text: "Questa casa non può migliorare, perché non ha accesso ad alcun tipo di struttura religiosa." }
    { group:127, id:91, text: "Questa casa non può migliorare, perché ha accesso al tempio di una sola religione. Visto che i suoi abitanti lavorano sodo, si aspettano di poter adorare più dei." }
    { group:127, id:92, text: "Questa casa non può migliorare, perché ha accesso al tempio di due sole religioni. Visto che i suoi abitanti lavorano sodo, si aspettano di poter adorare più dei." }
    { group:127, id:93, text: "Questa casa non può svilupparsi perché non ha l'accesso al dentista." }
    { group:127, id:94, text: "Questa casa non può svilupparsi perché non ha cure sanitarie. Non ha accesso al medico e alla camera mortuaria." }
    { group:127, id:95, text: "Questa casa non può svilupparsi perché non ha maggiori cure sanitarie. I medici vanno bene, ma manca l'accesso a una camera mortuaria locale." }
    { group:127, id:96, text: "Questa casa non può svilupparsi perché vuole maggiori cure sanitarie. Esiste un accesso alla camera mortuaria locale, ma manca l'accesso a una farmacia." }
    { group:127, id:97, text: "Questa casa non può svilupparsi. Occorrono forniture di tela dal bazar locale prima che le classi più ricche decidano di entrare." }
    { group:127, id:98, text: "Inutilizzato" }
    { group:127, id:99, text: "Questa casa non può svilupparsi. Occorrono forniture di birra dal bazar locale prima che le classi più ricche decidano di entrare." }
    { group:127, id:100, text: "Gli abitanti di questo palazzo sono la crema della società egiziana. Non desiderano nulla. È già difficile soddisfare le loro esigenze!" }
    { group:127, id:101, text: "Questo edifico si tramuterà presto in uno più avanzato, in seguito al miglioramento delle condizioni del vicinato." }
    { group:127, id:102, text: "Un edificio vicino(" }
    { group:127, id:103, text: "sta avendo un effetto negativo sulla desiderabilità del luogo." }
    { group:127, id:104, text: "Questa casa si svilupperebbe subito, se avesse lo spazio per farlo." }
    { group:127, id:105, text: "Inutilizzato" }
    { group:127, id:106, text: "Inutilizzato" }
    { group:127, id:107, text: "Casa infettata per" }
    { group:127, id:108, text: "Questa casa non può svilupparsi. Occorrono beni di lusso come" }
    { group:127, id:109, text: "Casa infestata dalle rane per altri" }
    { group:127, id:110, text: "Questa casa presto peggiorerà perché la città ha un solo tipo di beni di lusso." }
    { group:127, id:111, text: "e i suoi esigenti residenti si lamentano della mancanza di scelta." }
    { group:127, id:112, text: "Questa casa presto peggiorerà. Occorrono beni di lusso, come i gioielli," }
    { group:127, id:113, text: "per soddisfare i gusti opulenti degli scribi." }
    { group:127, id:114, text: "Questa casa non può svilupparsi, non ha" }
    { group:127, id:115, text: "ma occorre un altro tipo di beni di lusso, come l'ebano, l'avorio o l'incenso." }
    { group:127, id:116, text: "per soddisfare i gusti opulenti degli scribi." }
    { group:128, id:0, text: "Lotto vacante" }
    { group:128, id:1, text: "Qui, ancora non è stata costruita nemmeno una tenda. Probabilmente gli immigranti arriveranno presto, se la città può offrire cibo e lavoro." }
    { group:128, id:2, text: "Questo lotto è troppo lontano dalle strade. Se non costruirai una via di comunicazione, tornerà a essere normale campagna." }
    { group:129, id:0, text: "da" }
    { group:129, id:1, text: "Capacità" }
    { group:129, id:2, text: "Acquisti" }
    { group:129, id:3, text: "Vendite" }
    { group:129, id:4, text: "Acquistato" }
    { group:129, id:5, text: "Venduto" }
    { group:129, id:6, text: "Alla fonda, in attesa di un molo libero." }
    { group:129, id:7, text: "Attraccata, in fase di commercio delle merci." }
    { group:129, id:8, text: "Di ritorno a casa." }
    { group:129, id:9, text: "In direzione degli approdi cittadini." }
    { group:129, id:10, text: "Commercio." }
    { group:129, id:11, text: "Di ritorno a casa." }
    { group:129, id:12, text: "Diretto ai depositi cittadini" }
    { group:129, id:13, text: "Nessun commercio qui, sta semplicemente passando." }
    { group:129, id:14, text: "da" }
    { group:129, id:15, text: "Verso" }
    { group:129, id:16, text: "Verso" }
    { group:129, id:17, text: "Raccolta" }
    { group:129, id:18, text: "Ritorno con" }
    { group:129, id:19, text: "unità di" }
    { group:129, id:20, text: "unità di" }
    { group:129, id:21, text: "Trasporto" }
    { group:130, id:0, text: "(non utilizzato)" }
    { group:131, id:0, text: "Capanna dei nativi" }
    { group:131, id:1, text: "Does this text appear anywhere?" }
    { group:132, id:0, text: "Punto d'incontro dei nativi" }
    { group:132, id:1, text: "Is this entry used anywhere?" }
    { group:133, id:0, text: "Raccolti semplici" }
    { group:133, id:1, text: "This entry is probably unused." }
    { group:134, id:0, text: "Missione" }
    { group:134, id:1, text: "Where did this text appear?" }
    { group:135, id:0, text: "Accademia militare" }
    { group:135, id:1, text: "Quando i soldati finiscono il loro primo periodo di addestramento, cercano di migliorare in questa accademia, ma non possono riuscirci finché essa non riceverà personale a sufficienza." }
    { group:135, id:2, text: "Senza personale, non è possibile addestrare meglio i soldati. Dovranno andare direttamente al forte e sperare che le cose vadano bene." }
    { group:135, id:3, text: "Abbiamo dato ai novellini le giuste qualità per eccellere nell'esercito egizio." }
    { group:136, id:0, text: "Reclutatore" }
    { group:136, id:1, text: "Nessuno può entrare nell'esercito senza passare per la base di addestramento delle reclute." }
    { group:136, id:2, text: "Scorte d'armi" }
    { group:136, id:3, text: "Senza il personale, non possiamo addestrare alcuna recluta. Che Seth ci aiuti in caso di guerra!" }
    { group:136, id:4, text: "Non stiamo addestrando nessuno, perché né i forti né le torri ci hanno chiesto dei nuovi soldati." }
    { group:136, id:5, text: "Possiamo addestrare nuovi arcieri, ma ci occorrono armi per la fanteria e i carri da guerra." }
    { group:136, id:6, text: "Addestriamo i soldati a ritmo ridotto. Senza armi, non possiamo addestrare fanteria e aurighi." }
    { group:136, id:7, text: "Siamo a corto di personale e senza armi! Possiamo addestrare gli arcieri, ma molto lentamente." }
    { group:136, id:8, text: "Senza personale e senza armi, possiamo addestrare solo qualche arciere occasionale." }
    { group:136, id:9, text: "Stiamo addestrando soldati a pieno ritmo, abbiamo armi a sufficienza per qualunque cosa." }
    { group:136, id:10, text: "L'addestramento dei soldati è rallentato dalla mancanza di personale, anche se abbiamo tutte le armi necessarie." }
    { group:136, id:11, text: "Ci mancano istruttori e l'addestramento è molto lento, abbiamo però armi sufficienti per tutti i soldati." }
    { group:136, id:12, text: "Senza personale, addestrare i soldati è impossibile, non importa quante armi siano a disposizione." }
    { group:136, id:13, text: "Carri in magazzino" }
    { group:136, id:14, text: "Carro in magazzino" }
    { group:136, id:15, text: "Armi in magazzino" }
    { group:137, id:0, text: "Piazza" }
    { group:137, id:1, text: "Le piazze migliorano le strade lastricate senza aumentare il traffico." }
    { group:138, id:0, text: "\"I Leoni\"" }
    { group:138, id:1, text: "\"I Coccodrilli\"" }
    { group:138, id:2, text: "\"I Cobra\"" }
    { group:138, id:3, text: "\"Gli Scorpioni\"" }
    { group:138, id:4, text: "\"I Falchi\"" }
    { group:138, id:5, text: "\"Gli Arieti\"" }
    { group:138, id:6, text: "\"Le Iene\"" }
    { group:138, id:7, text: "\"Gli Scarabei\"" }
    { group:138, id:8, text: "\"Gli Sciacalli\"" }
    { group:138, id:9, text: "\"I Migliori\"" }
    { group:138, id:10, text: "Al momento, questa compagnia non ha soldati. Diventerà un'unità da combattimento solo quando disporrà di nuove leve addestrate dal reclutatore." }
    { group:138, id:11, text: "Al momento, questa compagnia non ha soldati. Esiste solo il nome. Senza un reclutatore in città, non può ricevere nuove truppe." }
    { group:138, id:12, text: "Tieni il campo in formazione serrata" }
    { group:138, id:13, text: "La compagnia tiene il campo e combatte solo se attaccata. I soldati godono di vantaggi ma sono più vulnerabili agli attacchi con armi da tiro." }
    { group:138, id:14, text: "Tieni il campo in formazione aperta." }
    { group:138, id:15, text: "La compagnia combatte solo se attaccata. I soldati occupano più spazio, combattono con minor efficienza ma sono meno vulnerabili alle armi da tiro." }
    { group:138, id:16, text: "Attacca un nemico vicino" }
    { group:138, id:17, text: "Con questo ordine, la compagnia attacca in formazione qualsiasi nemico che sia così stolto da avvicinarsi." }
    { group:138, id:18, text: "Attacco libero" }
    { group:138, id:19, text: "Con questo ordine, la compagnia rompe la formazione e attacca qualsiasi nemico riesca a trovare." }
    { group:138, id:20, text: "Carica" }
    { group:138, id:21, text: "Con questo ordine, la compagnia si getta con furia contro le fila nemiche." }
    { group:138, id:22, text: "Con questo ordine, la compagnia abbandona il campo e ritorna al suo forte per sostituire i caduti, riposarsi e risollevare il morale." }
    { group:138, id:23, text: "Soldati nella compagnia" }
    { group:138, id:24, text: "Salute dei soldati" }
    { group:138, id:25, text: "Esperienza" }
    { group:138, id:26, text: "Perfetta" }
    { group:138, id:27, text: "Molto buona" }
    { group:138, id:28, text: "Buona" }
    { group:138, id:29, text: "Media" }
    { group:138, id:30, text: "Scadente" }
    { group:138, id:31, text: "Molto scadente" }
    { group:138, id:32, text: "Spaventoso" }
    { group:138, id:33, text: "Aurighi" }
    { group:138, id:34, text: "Fanteria" }
    { group:138, id:35, text: "Arcieri" }
    { group:138, id:36, text: "Morale" }
    { group:138, id:37, text: "Atterriti!" }
    { group:138, id:38, text: "Terrorizzati" }
    { group:138, id:39, text: "Spaventatissimi" }
    { group:138, id:40, text: "Molto spaventati" }
    { group:138, id:41, text: "Spaventati" }
    { group:138, id:42, text: "Molto scossi" }
    { group:138, id:43, text: "Scossi" }
    { group:138, id:44, text: "Scadente" }
    { group:138, id:45, text: "Scoraggiati" }
    { group:138, id:46, text: "Sotto la media" }
    { group:138, id:47, text: "Media" }
    { group:138, id:48, text: "Sopra la media" }
    { group:138, id:49, text: "Coraggiosi" }
    { group:138, id:50, text: "Quasi spavaldi" }
    { group:138, id:51, text: "Spavaldi" }
    { group:138, id:52, text: "Fieri" }
    { group:138, id:53, text: "Molto fieri" }
    { group:138, id:54, text: "Forti" }
    { group:138, id:55, text: "Fortissimi" }
    { group:138, id:56, text: "Eccellente" }
    { group:138, id:57, text: "Perfetta" }
    { group:138, id:58, text: "Ritorna al forte" }
    { group:138, id:59, text: "Maledetta da Seth!" }
    { group:138, id:60, text: "Novellini" }
    { group:138, id:61, text: "Abili" }
    { group:138, id:62, text: "Veterani" }
    { group:138, id:63, text: "Maestri" }
    { group:138, id:64, text: "Élite" }
    { group:138, id:65, text: "I migliori" }
    { group:138, id:66, text: "Punti ferita" }
    { group:138, id:67, text: "Attacco corpo a corpo" }
    { group:138, id:68, text: "Armatura corpo a corpo" }
    { group:138, id:69, text: "Armatura contro proiettili" }
    { group:138, id:70, text: "Attacco a distanza" }
    { group:138, id:71, text: "Gittata proiettili" }
    { group:138, id:72, text: "Rateo di fuoco dei proiettili" }
    { group:138, id:73, text: "Compagnia" }
    { group:138, id:74, text: "Compagnia di fanteria" }
    { group:138, id:75, text: "Compagnia di arcieri" }
    { group:138, id:76, text: "Compagnia di carri da guerra" }
    { group:138, id:77, text: "Clic per ruotare fronte della compagnia" }
    { group:138, id:78, text: "Ordini compagnia e orientamento" }
    { group:139, id:0, text: "Mura in fango" }
    { group:139, id:1, text: "Le mura bloccano gli assalti contro la città, ma possono essere distrutte. Le mura più spesse sono più robuste e possono essere pattugliate dalle guardie." }
    { group:140, id:0, text: "Macerie" }
    { group:140, id:1, text: "Sono le rovine dell'edificio di prima. Questi ammassi di macerie non migliorano certo la zona." }
    { group:141, id:0, text: "Canale di irrigazione" }
    { group:141, id:1, text: "Questo canale di irrigazione trasporta l'acqua per aiutare a fertilizzare le coltivazioni." }
    { group:141, id:2, text: "Questo canale di irrigazione non porta l'acqua alle zone meno fertili perché non ha una sorgente d'acqua alla quale attingere." }
    { group:142, id:0, text: "Nuova rotta commerciale stabilita." }
    { group:142, id:1, text: "Per commerciare queste nuove merci, ordina al supervisore commerciale di impostare il loro stato su Importazione o Esportazione." }
    { group:142, id:2, text: "Vuoi visitare il supervisore?" }
    { group:142, id:3, text: "RICORDA! Alla tua città occorre un porto prima che le navi mercantili possano solcare le rotte marine." }
    { group:143, id:0, text: "Accetta le merci" }
    { group:143, id:1, text: "Non accettare le merci" }
    { group:143, id:2, text: "Richiesta di cibo" }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Bianco" }
    { group:144, id:3, text: "Bianco" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Bianco" }
    { group:144, id:6, text: "Bianco" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "Bianco" }
    { group:144, id:9, text: "Bianco" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "Bianco" }
    { group:144, id:12, text: "Bianco" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "Bianco" }
    { group:144, id:15, text: "Bianco" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "Bianco" }
    { group:144, id:18, text: "Bianco" }
    { group:144, id:19, text: "VII la fine del periodo arcaico" }
    { group:144, id:20, text: "Behdet (Apollinopolis): Acque pericolose" }
    { group:144, id:21, text: "Abydos (Abedju): La necropoli" }
    { group:144, id:22, text: "La nascita del vecchio regno" }
    { group:144, id:23, text: "Oasi di Selima: Assicura le rotte delle carovane" }
    { group:144, id:24, text: "Abu (Elefantine): Procura nuova ricchezza" }
    { group:144, id:25, text: "IX (Il vecchio regno)" }
    { group:144, id:26, text: "Bianco" }
    { group:144, id:27, text: "Bianco" }
    { group:144, id:28, text: "Il vecchio regno" }
    { group:144, id:29, text: "Serabit Khadim: L'aspro Sinai" }
    { group:144, id:30, text: "Meidum: Una tomba tutta tua" }
    { group:144, id:31, text: "Età delle Piramidi" }
    { group:144, id:32, text: "Buhen: Domare i nubiani" }
    { group:144, id:33, text: "Dahshur meridionale: Un nuovo tipo di piramide" }
    { group:144, id:34, text: "XII (Il vecchio regno)" }
    { group:144, id:35, text: "Bianco" }
    { group:144, id:36, text: "Bianco" }
    { group:144, id:37, text: "Età delle Piramidi" }
    { group:144, id:38, text: "Iunet (Dendera): La minaccia dei Kush" }
    { group:144, id:39, text: "On (Heliopolis): Le cave di Tura" }
    { group:144, id:40, text: "XIV (Il vecchio regno)" }
    { group:144, id:41, text: "vuoto" }
    { group:144, id:42, text: "vuoto" }
    { group:144, id:43, text: "L'apice del vecchio regno" }
    { group:144, id:44, text: "Oasi di Bahariya: I soldati di Ra" }
    { group:144, id:45, text: "Djedu (Abusir): Il culto di Ra" }
    { group:144, id:46, text: "Il declino del vecchio regno" }
    { group:144, id:47, text: "Oasi di Dunqul: Scaccia gli sciacalli" }
    { group:144, id:48, text: "Oasi di Dakhla: Ordine e caos" }
    { group:144, id:49, text: "Il primo periodo di mezzo" }
    { group:144, id:50, text: "Thinis: La guerra per il trono" }
    { group:144, id:51, text: "Waset (Tebe): La minaccia alla gloria" }
    { group:144, id:52, text: "La nascita del regno di mezzo" }
    { group:144, id:53, text: "Kebet (Coptos): Combatti per la pace" }
    { group:144, id:54, text: "Menat Khufu (Beni Hasan): Fame!" }
    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "vuoto" }
    { group:144, id:57, text: "vuoto" }
    { group:144, id:58, text: "Il regno di mezzo" }
    { group:144, id:59, text: "Iken (Mirgissa): Espandi i confini" }
    { group:144, id:60, text: "Sawu (Mersa Gawasis): Nuovi commerci" }
    { group:144, id:61, text: "Il regno di mezzo" }
    { group:144, id:62, text: "Heh (Semna): Nemici vecchi e nuovi" }
    { group:144, id:63, text: "Bubastis: Il gioiello del Nilo" }
    { group:144, id:64, text: "Il secondo periodo di mezzo" }
    { group:144, id:65, text: "Khmun (Hermopolis): Vendetta" }
    { group:144, id:66, text: "Sauty (Lykopolis): Ispirazione" }
    { group:144, id:67, text: "Nuovo regno: Pace o conquista?" }
    { group:144, id:68, text: "Byblos: Invade la Palestina" }
    { group:144, id:69, text: "Baki (Kuban): L'età d'oro" }
    { group:144, id:70, text: "Livello finale (XXIV)" }
    { group:144, id:71, text: "Rowarty (Avaris): Il dominio del mondo" }
    { group:144, id:72, text: "Hetepsenusret (Kahun): La grande piramide" }
    { group:145, id:0, text: "Questa missione non ha condizioni di vittoria. Si tratta solo di costruire la città e basta." }
    { group:146, id:0, text: "Confermare che la nuova risoluzione sia stata impostata correttamente (se riesci a leggere il messaggio, va tutto bene). Questo messaggio scomparirà tra dieci secondi." }
    { group:146, id:1, text: "Posizione del Regno non ancora scelta." }
    { group:146, id:2, text: "Sto usando la locazione standard" }
    { group:146, id:3, text: "Portami allo schermo del Regno!" }
    { group:147, id:0, text: "Ben fatto! Fornendo del cibo alla tua gente e proteggendo le loro case dai crolli e dal fuoco hai portato questa nuova civiltà oltre il primo passo lungo il corso della storia." }
    { group:147, id:1, text: "Eccellente. Hai costruito la tua prima vera città in una terra che non perdona, servendo i bisogni fisici e spirituali dei tuoi cittadini e hai aiutato la confederazione Thinita a unificare una terra divisa." }
    { group:147, id:2, text: "Superbo! I tuoi cittadini desiderano averti come loro protettore e le città vicine ti salutano come loro salvatore nei momenti del bisogno." }
    { group:147, id:3, text: "Ben fatto! Grazie alle tue doti, la civiltà egizia è avanzata molto in fretta e continuerà a evolversi nei decenni a seguire." }
    { group:147, id:4, text: "Congratulazioni. Hai costruito una capitale degna della meraviglia dei morti e dei vivi. Sviluppando il commercio, hai portato la tua città alla ribalta mondiale." }
    { group:147, id:5, text: "Il Faraone plaude le tue doti. Grazie alla tua gestione, hai protetto la città dai Beduini e hai fornito a tutto l'Egitto di che difendersi." }
    { group:147, id:6, text: "Il Faraone è compiaciuto. Hai dominato mari e fiumi e hai saputo sfruttare tali risorse. La potente flotta ora solca le acque e protegge i confini." }
    { group:147, id:7, text: "Il Faraone è soddisfatto. Hai sfruttato al meglio mari e fiumi, difendendo i nostri confini con una piccola flotta. Hai inoltre onorato la nobiltà fornendo loro le tombe in cui abitare nell'al di là." }
    { group:147, id:8, text: "Ben fatto! Sei riuscito a proteggere una via commerciale e a costruire una città florida in grado di soddisfare anche i cittadini più esigenti. I tuoi risultati sono davvero degni di nota." }
    { group:147, id:9, text: "Ben fatto! Hai fondato una città florida, presa ad esempio da altre connazionali e guardata con invidia dai nubiani." }
    { group:147, id:10, text: "Le tue gesta sono senza pari. Grazie alla tua saggezza, ora una gigantesca piramide, come mai si sono viste prima, si erge verso il cielo e garantisce l'immortalità al nostro Faraone." }
    { group:147, id:11, text: "Sei riuscito a superare i pericoli del Sinai e a portare in Egitto prezioso rame e turchesi. Le tue imprese saranno ricordate per generazioni." }
    { group:147, id:12, text: "Eccellente. La necropoli reale che hai costruito è davvero splendida e gi anni di servizio e impegno ora sono ricompensati con una tomba personale." }
    { group:147, id:13, text: "Grazie alla tua abilità, ora l'Egitto dichiara sua parte della Nubia. Fondando la tua città, hai dimostrato la potenza e la ricchezza dell'Egitto a tutti i nubiani." }
    { group:147, id:14, text: "Il Faraone si complimenta. La piramide sghemba che hai costruito è magnifica e oscura tutti i monumenti del passato." }
    { group:147, id:15, text: "Fantastico. Hai ricoperto un ruolo molto importante in un momento storico, la costruzione della prima vera piramide. Dopo la piramide di Snofru, tutti gli altri seguiranno il tuo esempio." }
    { group:147, id:16, text: "Straordinario. Nonostante le condizioni avverse e i continui attacchi dei Kushiti, hai costruito una bella città e hai esteso i confini meridionali dell'Egitto." }
    { group:147, id:17, text: "Le miniere che hai costruito a Tura hanno fornito tutto il calcare richiesto da Khufu... per ora. Con un'economia più forte, basata sulle miniere di Tura, la tua città ha raggiunto nuove vette sociali e culturali." }
    { group:147, id:18, text: "L'Egitto si inchina alla tua bravura. Hai costruito l'enorme piramide di Khufu e l'hai rifornita di ogni arredo funebre, inoltre hai onorato Khafra costruendo il luogo del suo eterno riposo e la possente sfinge." }
    { group:147, id:19, text: "Ben fatto. Hai sfruttato bene pochissime risorse e hai portato il potere di Ra ai confini del Regno." }
    { group:147, id:20, text: "Superbo. Il glorioso Tempio del Sole che hai costruito onora sia Ra che il Faraone." }
    { group:147, id:21, text: "Sei riuscito ad assistere la tua gente anche se l'Egitto crolla a pezzi tutto intorno. L'abilità della tua famiglia sarà molto utile negli anni bui che seguiranno." }
    { group:147, id:22, text: "Mentre l'Egitto va in pezzi, sei riuscito a mantenere intatta la tua città. Le tue abilità saranno molto utili negli anni bui che seguiranno." }
    { group:147, id:23, text: "Anche in un momento di grande agitazione, la tua famiglia è riuscita a riportare Thinis al suo originario splendore. Il tuo ardore militare ha sconfitto tutti i nemici, un risultato che non sarà dimenticato." }
    { group:147, id:24, text: "Grazie alla tua diligenza, hai nutrito la gente affamata in tempo di guerra e hai fornito i rinforzi necessari per distruggere il nemico. Le tue gesta non saranno mai dimenticate." }
    { group:147, id:25, text: "Il tuo continuo impegno ha creato una nuova splendida città per il Regno. Inoltre hai sfamato la gente in tempo di necessità. I tuoi sforzi riceveranno la giusta ricompensa." }
    { group:147, id:26, text: "Le splendide piramidi e gli obelischi che hai costruito per me sono eterni monumenti del mio Regno e per questo io ti sono molto grato. La tua dedizione sarà ricompensata." }
    { group:147, id:27, text: "Grazie alla tua generosa dedizione dimostrata, ora l'Egitto ti accetta come degno Faraone e spera che la tua dinastia produca regnanti di pari qualità." }
    { group:147, id:28, text: "Tutti si inchinano alla tua gloria, o Faraone. Hai conquistato la Nubia settentrionale e hai costruito un porto sul Mar Rosso, assicurando inoltre un'ottima scorta di rame per il nostro esercito." }
    { group:147, id:29, text: "Saluti al sommo Faraone. Il commercio con il Mar Rosso è florido e la tua saggezza ha fornito anche un ottimo centro commerciale in Nubia." }
    { group:147, id:30, text: "Seth ti reputa certo suo figlio, o potente Faraone. Sei riuscito a scacciare i nubiani e ad assicurare per sempre il confine meridionale." }
    { group:147, id:31, text: "La splendente città di Bubastis ti fa onore, Grande Faraone e tutto l'Egitto è in festa! Gli hyksos sono stati scacciati e, sotto la tua guida, la terra è di nuovo nostra." }
    { group:147, id:32, text: "L'Egitto gioisce! Gli hyksos sono stati scacciati e ora, sotto la tua guida, la terra egizia è di nuovo nostra." }
    { group:147, id:33, text: "Sei riuscito a ispirare i tuoi generali, promettendo loro la vita eterna. Gli hyksos e i loro terribili carri sono stati scacciati." }
    { group:147, id:34, text: "Potente Faraone, scacciando gli Ittiti, l'Egitto è ora divenuto un grande impero! La tua spada concede il dono della civiltà egizia a tutto il mondo." }
    { group:147, id:35, text: "Supremo Faraone, la tua saggezza ha portato l'Egitto in una nuova età dell'oro!" }
    { group:147, id:36, text: "Saluti al potente Faraone! La tua dinastia non ha pari e d'ora innanzi tutti gli Egizi pronunceranno il tuo nome con il più sentito rispetto." }
    { group:147, id:37, text: "Saluti al potente Faraone! La tua dinastia non ha pari e tutti gli Egizi, da qui fino alla fine dei tempi, pronunceranno il tuo nome con grande venerazione." }
    { group:147, id:38, text: "Ben fatto. La tomba di Thutmose I è completa, uno splendido traguardo! Il Faraone è certo che una tomba così bella e decorata sarà apprezzata dagli dei e faciliterà il suo viaggio nell'aldilà." }
    { group:147, id:39, text: "Un'impresa fantastica! È raro che dei lavoratori sottoposti a così grande pressione riescano a produrre un'opera d'arte del genere. La tomba di Tutankhamun è ora sigillata per l'eternità. Speriamo che i ladri sacrileghi non scoprano mai il luogo del suo eterno riposo!" }
    { group:147, id:40, text: "Un eccellente lavoro, sei riuscito a preservare la tomba reale e a completare la costruzione di quella nuova come ti era stato ordinato. Il Faraone Seti è molto soddisfatto del lavoro fatto dai tuoi operai." }
    { group:147, id:41, text: "Bel lavoro! Il nostro grande Faraone Ramses II non ha certo sbagliato ad assegnarti lo sviluppo commerciale e militare di queste terre. Ma il pericolo è sempre in agguato! Gli eserciti ittiti sono di nuovo in marcia per sconfigere il nostro legittimo dominio su questa ricca regione." }
    { group:147, id:42, text: "Il forte pugno del Faraone ha di nuovo battuto gli odiati Ittiti. Grande è il trionfo del nostro valoroso comandante Ramses II! La tua splendida vittoria in questa dura lotta sarà certo ricordata per sempre negli annali della storia." }
    { group:147, id:43, text: "Ottimo lavoro! Ramses II si compiace del colossale monumento che hai costruito in suo onore ad Abu Simbel." }
    { group:147, id:44, text: "Ottimo! Nonostante la lunga serie di piaghe e sfortune, la grande tomba del nostro anziano Faraone ora è pronta ad accoglierlo. Il suo splendore testimonia il nostro apprezzamento per Ramses II, certamente uno dei più grandi capi d'Egitto." }
    { group:147, id:45, text: "Il sole ha disperso le nuvole tempestose che avvolgevano l'Egitto. Quale gioia! Il vile capo dei Libu e i suoi alleati del mare sono fuggiti durante la notte. Il loro infausto piano di occupare le nostre spiagge è stato sventato. Inoltre, per nostra fortuna, molte delle loro donne e bambini ora sono nostri prigionieri." }
    { group:147, id:46, text: "Benissimo! Il tuo coraggio e decisione in battaglia hanno ispirato le truppe a dare il massimo. I maledetti Assiri sono stati malamente scacciati dal suolo egizio. La fama delle tue gesta è giunta fino al Faraone ed egli ne è molto compiaciuto." }
    { group:147, id:47, text: "Salute all'eroe di Tanis, protettore dell'Egitto! Le tue gloriose vittorie in mare e su terraferma hanno assicurato l'indipendenza dell'Egitto. I Persiani, un tempo potenti, ora tremano al suono del nome del nostro Faraone Achoris." }
    { group:147, id:48, text: "Hai fatto un buon lavoro. La tua saggezza e l'attenta pianificazione hanno reso Alessandria il centro del commercio in tutto il Mediterraneo. È una sfortuna che Alessandro Magno non potrà mai vedere la capitale del suo impero. Almeno abbiamo la soddisfazione di sapere che ora giace al sicuro tra le sue mura." }
    { group:147, id:49, text: "La metropoli di Alessandria ora brilla come un faro per tutto il mondo! La sua grande biblioteca è un incomparabile centro di istruzione e il torreggiante faro di Pharos è ormai una delle più grandi meraviglie del mondo." }
    { group:147, id:50, text: "Le tue legioni hanno schiacciato la feccia di Tolomeo XIII. Il suo corpo è stato ripescato dalle acque del Nilo. L'assedio è stato tolto e Cleopatra ora siede di nuovo sul trono. Per celebrare la vittoria e intensificare il legame che li unisce, Cesare e Cleopatra si imbarcheranno per una crociera sul Nilo sulla lussuosa chiatta reale." }
    { group:147, id:51, text: "Gli splendori di Alessandria e il fato dell'Egitto sono in buone mani, sotto la tua supervisione. Come ci aspettavamo, quando hai benedetto Marco Antonio con la tua presenza, egli ti ha reso omaggio pur chiedendoti i fondi necessari al raggiungimento dei suoi scopi. In effetti, si è innamorato di te, tanto da restare ad Alessandria come tuo fedele compagno e amante." }
    { group:147, id:52, text: "Grazie alle grandi ricchezze di Cleopatra e al genio tattico di Antonio, la flotta e le legioni di Ottaviano sono state distrutte. I Romani attendono impazienti il trionfale ritorno di Antonio e Cleopatra. Mano nella mano, Roma e Alessandria regneranno sul Mediterraneo per molte altre generazioni." }
    { group:147, id:53, text: "Vittoria su scenario personalizzato" }
    { group:147, id:54, text: "Ti sei comportato bene, ma ti attendono altre numerose sfide lungo il cammino per diventare Faraone!" }
    { group:148, id:5, text: "Finanze cittadine finali" }
    { group:148, id:6, text: "Monumenti eretti" }
    { group:148, id:7, text: "Missione completata in" }
    { group:148, id:8, text: "Livello di difficoltà minore:" }
    { group:148, id:9, text: "Punteggio:" }
    { group:148, id:10, text: "Congratulazioni. Ora puoi ricominciare e tentare di migliorare il tuo punteggio cliccando sul pulsante 'Scegli una missione'." }
    { group:148, id:11, text: "Il tuo punteggio è stato migliore l'ultima volta che hai giocato questa stessa missione." }
    { group:148, id:12, text: "Bel lavoro! Hai battuto il punteggio precedente per questa missione!" }
    { group:148, id:13, text: "Hai completato la missine con successo, ma [player_name] ancora detiene il record su questa città." }
    { group:148, id:14, text: "Ora detieni il punteggio più alto per questa missione! Hai battuto il punteggio di [player_name]." }
    { group:148, id:15, text: "mesi" }
    { group:148, id:16, text: "Hai barato! Il tuo punteggio non è degno di entrare nell'elenco delle migliori famiglie." }
    { group:149, id:0, text: "Richiesta generale" }
    { group:149, id:1, text: "Città egiziana sotto attacco" }
    { group:149, id:2, text: "Battaglia distante" }
    { group:149, id:3, text: "Festività" }
    { group:149, id:4, text: "Costruzione" }
    { group:149, id:5, text: "Carestia" }
    { group:149, id:6, text: "Minaccia" }
    { group:150, id:0, text: "Città egiziana salvata" }
    { group:150, id:1, text: "Battaglia lontana vinta" }
    { group:150, id:2, text: "Battaglia lontana persa" }
    { group:150, id:3, text: "Riconoscimento" }
    { group:151, id:0, text: "Amenemhet I" }
    { group:151, id:1, text: "Amenemhet II" }
    { group:151, id:2, text: "Amenemhet III" }
    { group:151, id:3, text: "Amenemhet IV" }
    { group:151, id:4, text: "Anedjib" }
    { group:151, id:5, text: "Den" }
    { group:151, id:6, text: "Djedefra" }
    { group:151, id:7, text: "Djedkara Izezi" }
    { group:151, id:8, text: "Djer" }
    { group:151, id:9, text: "Djet" }
    { group:151, id:10, text: "Djoser" }
    { group:151, id:11, text: "Hetepsekhemwy" }
    { group:151, id:12, text: "Hor" }
    { group:151, id:13, text: "Hor-Aha" }
    { group:151, id:14, text: "Huni" }
    { group:151, id:15, text: "Inyotef I" }
    { group:151, id:16, text: "Inyotef II" }
    { group:151, id:17, text: "Inyotef III" }
    { group:151, id:18, text: "Khaba" }
    { group:151, id:19, text: "Khasekhemwy" }
    { group:151, id:20, text: "Khendjer" }
    { group:151, id:21, text: "Khephren" }
    { group:151, id:22, text: "Khety" }
    { group:151, id:23, text: "Khufu" }
    { group:151, id:24, text: "Menes" }
    { group:151, id:25, text: "Menkauhor" }
    { group:151, id:26, text: "Menkaura" }
    { group:151, id:27, text: "Mentuhotep I" }
    { group:151, id:28, text: "Mentuhotep II" }
    { group:151, id:29, text: "Mentuhotep III" }
    { group:151, id:30, text: "Mentuhotep IV" }
    { group:151, id:31, text: "Merenra" }
    { group:151, id:32, text: "Regina Merneith" }
    { group:151, id:33, text: "Narmer" }
    { group:151, id:34, text: "Nebka" }
    { group:151, id:35, text: "Neferhotep I" }
    { group:151, id:36, text: "Neferirkara" }
    { group:151, id:37, text: "Neuserra" }
    { group:151, id:38, text: "Ninetjer" }
    { group:151, id:39, text: "Nitiqret" }
    { group:151, id:40, text: "Pepi I" }
    { group:151, id:41, text: "Pepi II" }
    { group:151, id:42, text: "Peribsen" }
    { group:151, id:43, text: "Qa'a" }
    { group:151, id:44, text: "Raneferef" }
    { group:151, id:45, text: "Reneb" }
    { group:151, id:46, text: "Sahura" }
    { group:151, id:47, text: "Sekhemkhet" }
    { group:151, id:48, text: "Semerkhet" }
    { group:151, id:49, text: "Sened" }
    { group:151, id:50, text: "Senusret I" }
    { group:151, id:51, text: "Senusret II" }
    { group:151, id:52, text: "Senusret III" }
    { group:151, id:53, text: "Shepseskaf" }
    { group:151, id:54, text: "Shepseskara" }
    { group:151, id:55, text: "Snofru" }
    { group:151, id:56, text: "Sobekhotep III" }
    { group:151, id:57, text: "Regina Sobknefru" }
    { group:151, id:58, text: "Teti" }
    { group:151, id:59, text: "Unas" }
    { group:151, id:60, text: "Userkaf" }
    { group:151, id:61, text: "Userkara" }
    { group:151, id:62, text: "Weneg" }
    { group:151, id:63, text: "Ahmose I" }
    { group:151, id:64, text: "Amenhotep I" }
    { group:151, id:65, text: "Thutmose I" }
    { group:151, id:66, text: "Thutmose II" }
    { group:151, id:67, text: "Hatshepsut" }
    { group:151, id:68, text: "Thutmose III" }
    { group:151, id:69, text: "Amenhotep II" }
    { group:151, id:70, text: "Thutmose IV" }
    { group:151, id:71, text: "Amenhotep III" }
    { group:151, id:72, text: "Akhenaten" }
    { group:151, id:73, text: "Neferneferuaten" }
    { group:151, id:74, text: "Smenkhkare" }
    { group:151, id:75, text: "Tutankhamun" }
    { group:151, id:76, text: "Ay" }
    { group:151, id:77, text: "Horemheb" }
    { group:151, id:78, text: "Ramses I" }
    { group:151, id:79, text: "Sethos I" }
    { group:151, id:80, text: "Ramses II" }
    { group:151, id:81, text: "Merneptah" }
    { group:151, id:82, text: "Amenmes" }
    { group:151, id:83, text: "Sethos II" }
    { group:151, id:84, text: "Siptah" }
    { group:151, id:85, text: "Regina Twosret" }
    { group:151, id:86, text: "Setnakhte" }
    { group:151, id:87, text: "Ramses III" }
    { group:151, id:88, text: "Ramses IV" }
    { group:151, id:89, text: "Ramses V" }
    { group:151, id:90, text: "Ramses VI" }
    { group:151, id:91, text: "Ramses VII" }
    { group:151, id:92, text: "Ramses VIII" }
    { group:151, id:93, text: "Ramses IX" }
    { group:151, id:94, text: "Ramses X" }
    { group:151, id:95, text: "Ramses XI" }
    { group:151, id:96, text: "Piye" }
    { group:151, id:97, text: "Shabaka" }
    { group:151, id:98, text: "Shebitku" }
    { group:151, id:99, text: "Taharka" }
    { group:151, id:100, text: "Tantamani" }
    { group:151, id:101, text: "Nepherites I" }
    { group:151, id:102, text: "Psammuthis" }
    { group:151, id:103, text: "Nefaarud I" }
    { group:151, id:104, text: "Hakor" }
    { group:151, id:105, text: "Naktnebef" }
    { group:151, id:106, text: "Alessandro Magno" }
    { group:151, id:107, text: "Filippo Arrhidaeus" }
    { group:151, id:108, text: "Alessandro IV" }
    { group:151, id:109, text: "Tolomeo I" }
    { group:151, id:110, text: "Tolomeo II" }
    { group:151, id:111, text: "Tolomeo III" }
    { group:151, id:112, text: "Tolomeo IV" }
    { group:151, id:113, text: "Tolomeo V" }
    { group:151, id:114, text: "Tolomeo VI" }
    { group:151, id:115, text: "Tolomeo VII" }
    { group:151, id:116, text: "Tolomeo VIII" }
    { group:151, id:117, text: "Tolomeo IX" }
    { group:151, id:118, text: "Tolomeo X" }
    { group:151, id:119, text: "Tolomeo XI" }
    { group:151, id:120, text: "Tolomeo XII" }
    { group:151, id:121, text: "Regina Berenice IV" }
    { group:151, id:122, text: "Tolomeo XIII" }
    { group:151, id:123, text: "Cleopatra VII" }
    { group:151, id:124, text: "Tolomeo XV" }
    { group:152, id:0, text: "Nessuna" }
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
    { group:154, id:0, text: "Casotto da caccia" }
    { group:154, id:1, text: "Qui i cacciatori recuperano cibo cacciando gli animali selvatici. Il casotto può distribuire cacciagione ai depositi merci o ai granai." }
    { group:154, id:2, text: "Produzione completa: " }
    { group:154, id:3, text: " " }
    { group:154, id:4, text: "Il supervisore commerciale ha ordinato di sospendere la caccia." }
    { group:154, id:5, text: "Questo casotto da caccia non ha cacciatori. Caccia annullata." }
    { group:154, id:6, text: "Questo casotto da caccia ha tutti i cacciatori che occorrono. I cacciatori stanno stanando tutti gli animali che trovano." }
    { group:154, id:7, text: "Questo casotto da caccia sta lavorando a ritmo ridotto. La raccolta di cibo va a rilento." }
    { group:154, id:8, text: "Questo casotto da caccia è a corto di addetti e raccoglie cibo con più lentezza di quanto dovrebbe." }
    { group:154, id:9, text: "Qui lavorano pochissime persone. La raccolta di carne è molto lenta." }
    { group:154, id:10, text: "Con così pochi cacciatori in questo casotto da caccia, si trovano ben pochi animali per non parlare di quelli abbattuti. Sarà una stagione difficile." }
    { group:154, id:11, text: "I cacciatori di questo casotto da caccia sono alla ricerca di prede." }
    { group:154, id:12, text: "La carne impiega troppo tempo per tornare al casotto. Prova a posizionare il casotto più vicino agli animali selvatici." }
    { group:154, id:13, text: "Carne conservata," }
    { group:155, id:0, text: "Blocco stradale" }
    { group:155, id:1, text: "Disponi dei blocchi stradali per ridurre i percorsi delle sentinelle. La gente con destinazioni specifiche (come i carrettieri o i clienti dei bazar) possono passare liberamente." }
    { group:156, id:0, text: "Evento libero" }
    { group:156, id:1, text: "Richiesta" }
    { group:156, id:2, text: "Invasione" }
    { group:156, id:3, text: "Terremoto" }
    { group:156, id:4, text: "Rivolta" }
    { group:156, id:5, text: "Successione di Faraone" }
    { group:156, id:6, text: "Problema nella via marittima" }
    { group:156, id:7, text: "Problema nella via terrestre" }
    { group:156, id:8, text: "Aumento salari" }
    { group:156, id:9, text: "Diminuzione salari" }
    { group:156, id:10, text: "Acqua inquinata" }
    { group:156, id:11, text: "Crollo di miniera d'oro" }
    { group:156, id:12, text: "Allagamento cava di argilla" }
    { group:156, id:13, text: "Aumento di domanda" }
    { group:156, id:14, text: "Calo nella domanda" }
    { group:156, id:15, text: "Aumento dei prezzi" }
    { group:156, id:16, text: "Caduta dei prezzi" }
    { group:156, id:17, text: "Aumento del regno" }
    { group:156, id:18, text: "Riduzione del regno" }
    { group:156, id:19, text: "Cambio livello città" }
    { group:156, id:20, text: "Evento messaggio" }
    { group:156, id:21, text: "Inondazione fallita" }
    { group:156, id:22, text: "Inondazione perfetta" }
    { group:156, id:23, text: "Dono" }
    { group:156, id:24, text: "Piaga delle locuste" }
    { group:156, id:25, text: "Piaga delle rane" }
    { group:156, id:26, text: "Tempesta di grandine" }
    { group:156, id:27, text: "Fiume di sangue" }
    { group:156, id:28, text: "Ondata di crimine" }
    { group:156, id:29, text: "Mummia" }
    { group:157, id:0, text: "Osiride" }
    { group:157, id:1, text: "Ra" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Seth" }
    { group:157, id:4, text: "Bast" }
    { group:157, id:5, text: "Hermie" }
    { group:157, id:6, text: "Janus" }
    { group:158, id:0, text: "Dio dell'agricoltura e del Nilo" }
    { group:158, id:1, text: "Dio del Regno" }
    { group:158, id:2, text: "Dio degli artigiani" }
    { group:158, id:3, text: "Dio della distruzione" }
    { group:158, id:4, text: "Dea della casa" }
    { group:158, id:5, text: "(Protettore dei dentisti)" }
    { group:158, id:6, text: "(Tutto)" }
    { group:159, id:0, text: "Approdo traghetto" }
    { group:159, id:1, text: "ATTENZIONE! Questo approdo non è collegato all'altra sponda del fiume. Solo gli emigranti possono passare." }
    { group:159, id:2, text: "ATTENZIONE! L'approdo sull'altra sponda non è collegato a una strada. Solo gli emigranti possono passare." }
    { group:159, id:3, text: "ATTENZIONE! L'approdo sull'altra sponda ha dei problemi con gli addetti. Solo gli emigranti possono passare." }
    { group:160, id:0, text: "Gennaio" }
    { group:160, id:1, text: "Febbraio" }
    { group:160, id:2, text: "Marzo" }
    { group:160, id:3, text: "Aprile" }
    { group:160, id:4, text: "Maggio" }
    { group:160, id:5, text: "Giugno" }
    { group:160, id:6, text: "Luglio" }
    { group:160, id:7, text: "Agosto" }
    { group:160, id:8, text: "Settembre" }
    { group:160, id:9, text: "Ottobre" }
    { group:160, id:10, text: "Novembre" }
    { group:160, id:11, text: "Dicembre" }
    { group:161, id:0, text: "Santuario di Osiride (Agric.)" }
    { group:161, id:1, text: "Osiride porta fertilità alla terra e fa crescere le messi. Appagalo o preparati a soffrire la fame." }
    { group:161, id:2, text: "Santuario di Ra (Il Regno)" }
    { group:161, id:3, text: "I mercanti sanno bene quanto convenga compiacere Ra. Il commercio è più sicuro e conveniente con la sua benedizione e la fama della tua città è più grande." }
    { group:161, id:4, text: "Santuario di Ptah (Artigiani)" }
    { group:161, id:5, text: "Operai e artigiani adorano Ptah per alleviare la loro fatica. Quando Ptah è arrabbiato, nessuna industria può sfuggire alla catastrofe." }
    { group:161, id:6, text: "Santuario di Seth (Distruzione)" }
    { group:161, id:7, text: "Seth protegge i soldati e aumenta il loro valore in combattimento. Nessun uomo osa combattere senza la benedizione di Seth." }
    { group:161, id:8, text: "Santuario di Bast (Casa)" }
    { group:161, id:9, text: "Quando Bast è dispiaciuta, nessuno è più al sicuro in casa propria. Alcuni imputano a Bast anche le malattie." }
    { group:162, id:0, text: "Miniera d'oro" }
    { group:162, id:1, text: "L'estrazione dell'oro è il modo più veloce per riempire i forzieri cittadini. Fortunata la città che dispone di tale risorsa, perché la sua ricchezza è garantita." }
    { group:162, id:2, text: "Produzione completa: " }
    { group:162, id:3, text: " " }
    { group:162, id:4, text: "Il supervisore commerciale ha dato lo stop all'estrazione dell'oro." }
    { group:162, id:5, text: "Questo miniera non ha operai. L'estrazione di oro è ferma." }
    { group:162, id:6, text: "Questa miniera ha tutti gli addetti che occorrono e lavora a ritmo serrato per estrarre l'oro." }
    { group:162, id:7, text: "Questa miniera lavora a ritmo ridotto. La produzione potrebbe migliorare con più lavoratori." }
    { group:162, id:8, text: "Questa miniera è a corto di personale. Produce meno oro di quanto potrebbe." }
    { group:162, id:9, text: "Pochissime persone lavorano in questo edificio. La produzione è lenta." }
    { group:162, id:10, text: "Con così pochi lavoratori, l'estrazione è quasi ferma. Produrrà ben poco oro." }
    { group:163, id:0, text: "Miniera di gemme" }
    { group:163, id:1, text: "Estrai le gemme per esportarle o per produrre gioielli, i beni di lusso fondamentali della tua città." }
    { group:163, id:2, text: "Produzione completa: " }
    { group:163, id:3, text: " " }
    { group:163, id:4, text: "Il supervisore commerciale ha deciso che la città ha gemme a sufficienza e ha fermato le miniere." }
    { group:163, id:5, text: "Questa miniera non ha operai. L'estrazione di ferro è ferma." }
    { group:163, id:6, text: "Questa miniera ha tutti gli addetti che occorrono e lavora a ritmo serrato per estrarre gemme." }
    { group:163, id:7, text: "Questa miniera lavora a ritmo ridotto. La produzione potrebbe migliorare con più lavoratori." }
    { group:163, id:8, text: "Questa miniera è a corto di personale. Produce meno gemme di quanto potrebbe." }
    { group:163, id:9, text: "Pochissime persone lavorano in questo edificio. La produzione è lenta." }
    { group:163, id:10, text: "Con così pochi lavoratori, l'estrazione di gemme è quasi ferma." }
    { group:164, id:0, text: "Stazione dei vigili del fuoco" }
    { group:164, id:1, text: "Le stazioni dei vigili del fuoco inviano gli addetti a prevenire gli incendi e spegnere quelli già scoppiati." }
    { group:164, id:2, text: "Il nostro vigile del fuoco sta controllando la città." }
    { group:164, id:3, text: "Il nostro vigile del fuoco si sta preparando a lavorare." }
    { group:164, id:4, text: "Al momento i turni sono completi. I nostri vigili del fuoco sono sempre in giro per le strade." }
    { group:164, id:5, text: "Siamo un po' a corto di vigili del fuoco. Abbiamo dei buchi di un paio di giorni." }
    { group:164, id:6, text: "Ci manca del personale e c'è un pericoloso vuoto di una settimana nel foglio di servizio." }
    { group:164, id:7, text: "Abbiamo troppo pochi uomini. Spesso nessun vigile del fuoco lascia la stazione per due settimane di seguito." }
    { group:164, id:8, text: "Stiamo lavorando con poliziotti virtuali. Spesso passa più di un mese prima di mandare un vigile del fuoco in strada." }
    { group:164, id:9, text: "Senza personale, questa stazione non può fare altro che restare a guardare." }
    { group:165, id:0, text: "Mura in mattoni" }
    { group:165, id:1, text: "Le mura impediscono ai nemici di invadere la città. I nemici possono distruggere le mura. Quelle più spesse sono più resistenti e permettono alle guardie delle torri di controllare la situazione lungo tutto il perimetro." }
    { group:166, id:0, text: "Mura" }
    { group:166, id:1, text: "Le mura bloccano gli assalti contro la città, ma possono essere distrutte. Le mura più spesse sono più robuste e possono essere pattugliate dalle guardie." }
    { group:167, id:0, text: "Corpo di Guardia in mattoni" }
    { group:167, id:1, text: "Le mura devono essere dotate di un portale, in modo che emigranti, immigranti e commercianti si possano muovere liberamente." }
    { group:168, id:0, text: "Corpo di Guardia" }
    { group:168, id:1, text: "Le mura devono essere dotate di un portale, in modo che emigranti, immigranti e commercianti si possano muovere liberamente." }
    { group:169, id:0, text: "Torre in mattoni" }
    { group:169, id:1, text: "Costruisci torri nelle mura a intervalli regolari o almeno nei punti più vulnerabili. Quando sono collegate a delle strade, le torri ricevono le guardie dal reclutatore. Le torri di guardia scagliano giavellotti contro gli invasori e controllano le mura." }
    { group:169, id:2, text: "Senza personale non possiamo fornire guardie sulle torri o per il controllo delle mura." }
    { group:169, id:3, text: "I nostri uomini sono all'erta e pronti a respingere il nemico." }
    { group:169, id:4, text: "Abbiamo del personale ordinario, ma ci mancano le guardie fornite dal reclutatore per difendere la città." }
    { group:170, id:0, text: "Torre" }
    { group:170, id:1, text: "Costruisci torri nelle mura a intervalli regolari o almeno nei punti più vulnerabili. Quando sono collegate a delle strade, le torri ricevono le guardie dal reclutatore. Le torri di guardia scagliano giavellotti contro gli invasori e controllano le mura." }
    { group:170, id:2, text: "Senza personale non possiamo fornire guardie sulle torri o per il controllo delle mura." }
    { group:170, id:3, text: "I nostri uomini sono all'erta e pronti a respingere il nemico." }
    { group:170, id:4, text: "Abbiamo del personale ordinario, ma ci mancano le guardie fornite dal reclutatore per difendere la città." }
    { group:171, id:0, text: "Gilda dei carpentieri" }
    { group:171, id:1, text: "I carpentieri si radunano qui per scambiarsi pareri, trovare lavoro e discutere dei loro problemi." }
    { group:171, id:2, text: "Produzione completa: " }
    { group:171, id:3, text: " " }
    { group:171, id:4, text: "Questa gilda è stata chiusa dal supervisore commerciale." }
    { group:171, id:5, text: "Questa gilda non ha impiegati. La produzione è ferma." }
    { group:171, id:6, text: "Questa gilda ha tutti gli impiegati che occorrono e lavora al massimo." }
    { group:171, id:7, text: "Questa gilda lavora a ritmo ridotto. Il lavoro va a rilento." }
    { group:171, id:8, text: "Questa gilda è a corto di personale e fornisce meno carpentieri di quanto potrebbe." }
    { group:171, id:9, text: "In questa gilda lavorano pochissime persone. La lista di attesa per i carpentieri è molto lunga." }
    { group:171, id:10, text: "Con così pochi lavoratori, pare che occorra un'eternità per fornire dei carpentieri." }
    { group:171, id:11, text: "Il laboratorio ha bisogno di altro legno." }
    { group:171, id:12, text: "Legno in magazzino," }
    { group:172, id:0, text: "Gilda dei muratori" }
    { group:172, id:1, text: "I muratori si radunano qui per scambiarsi pareri, trovare lavoro e discutere dei loro problemi." }
    { group:172, id:2, text: "Produzione completa: " }
    { group:172, id:3, text: " " }
    { group:172, id:4, text: "Questa gilda è stata chiusa dal supervisore commerciale." }
    { group:172, id:5, text: "Questa gilda non ha impiegati. La posa dei mattoni è impossibile." }
    { group:172, id:6, text: "Questa gilda ha tutti gli impiegati che occorrono e i muratori lavorano con il massimo dell'efficienza." }
    { group:172, id:7, text: "Questa gilda lavora a ritmo ridotto. Il lavoro va a rilento." }
    { group:172, id:8, text: "Questa gilda è a corto di personale e fornisce meno muratori di quanto potrebbe." }
    { group:172, id:9, text: "In questa gilda lavorano pochissime persone. Molti attendono dei muratori." }
    { group:172, id:10, text: "Con così pochi lavoratori, pare che occorra un'eternità per fornire dei muratori." }
    { group:172, id:11, text: "Il laboratorio ha bisogno di altri mattoni." }
    { group:172, id:12, text: "Mattoni in magazzino," }
    { group:173, id:0, text: "Gilda degli scalpellini" }
    { group:173, id:1, text: "I muratori si radunano qui per scambiarsi pareri, trovare lavoro e discutere dei loro problemi." }
    { group:173, id:2, text: "Produzione completa: " }
    { group:173, id:3, text: " " }
    { group:173, id:4, text: "Questa gilda è stata chiusa dal supervisore commerciale." }
    { group:173, id:5, text: "Questa gilda non ha impiegati. La lavorazione della pietra è ferma." }
    { group:173, id:6, text: "Questa gilda ha tutti gli impiegati che occorrono, gli scalpellini lavorano con il massimo dell'efficienza." }
    { group:173, id:7, text: "Questa gilda lavora a ritmo ridotto. Il lavoro va a rilento." }
    { group:173, id:8, text: "Questa gilda è a corto di personale e fornisce meno scalpellini di quanto potrebbe." }
    { group:173, id:9, text: "Qui lavora davvero poca gente. C'è grande richiesta di scalpellini." }
    { group:173, id:10, text: "Con così pochi lavoratori, pare che occorra un'eternità per fornire degli scalpellini." }
    { group:173, id:11, text: "Questa gilda fornisce abili artigiani per i monumenti. Non ha bisogno di una fornitura di pietra." }
    { group:173, id:12, text: "Pietra in magazzino," }
    { group:174, id:0, text: " Molo delle navi da trasporto truppe " }
    { group:174, id:1, text: "Le navi da trasporto, costruite dai carpentieri, approdano qui, tra una missione e l'altra. Il tuo battaglione ha bisogno di navi da trasporto per navigare sul Nilo." }
    { group:174, id:2, text: "Il nostro trasporto è nel porto." }
    { group:174, id:3, text: "Il nostro trasporto è partito per un viaggio." }
    { group:175, id:0, text: "Molo delle navi da guerra" }
    { group:175, id:1, text: "Qui nascono le navi da battaglia. Qualsiasi città sul Nilo deve avere almeno un paio di navi da guerra sempre pronte." }
    { group:175, id:2, text: "La nostra nave da guerra è nel porto." }
    { group:175, id:3, text: "La nostra nave da guerra è fuori per difendere la città contro gli invasori." }
    { group:176, id:0, text: "Palazzo di giustizia" }
    { group:176, id:1, text: "Il palazzo di giustizia invia i magistrati che aiutano a ridurre il crimine assicurando che le colpe siano comunicate alla cittadinanza. Le segrete del tribunale contengono parte del tesoro cittadino." }
    { group:176, id:2, text: "Questo palazzo di giustizia non ha impiegati, i tuoi cittadini risolvono le dispute come possono." }
    { group:176, id:3, text: "Ci sono così pochi impiegati in questo palazzo di giustizia che le decisioni legali sembrano quasi casuali." }
    { group:176, id:4, text: "Con solo la metà degli impiegati necessari, questo palazzo di giustizia prende decisioni affrettate." }
    { group:176, id:5, text: "Dato che è a corto di personale, questo palazzo di giustizia ha alcuni casi in arretrato." }
    { group:176, id:6, text: "Questo palazzo di giustizia ha tutti gli impiegati che occorrono per ascoltare le lamentele dei cittadini e, quindi, decidere velocemente e con saggezza." }
    { group:176, id:7, text: "Il magistrato è fuori per risolvere le dispute." }
    { group:176, id:8, text: "Il magistrato è nei suoi appartamenti." }
    { group:176, id:9, text: "Il tesoro è di" }
    { group:177, id:0, text: "Questa coltivazione è irrigata." }
    { group:177, id:1, text: "Questa coltivazione non è irrigata." }
    { group:177, id:2, text: "La prossima inondazione arriverà entro" }
    { group:177, id:3, text: "Ora che il fiume si è ritirato, questa zona offre un terreno molto fertile." }
    { group:177, id:4, text: "Quando il fiume si ritirerà, questa zona offrirà un terreno molto fertile." }
    { group:177, id:5, text: "Questa fattoria ha bisogno di lavoranti, che possono essere addestrati nei campi di lavoro." }
    { group:177, id:6, text: "Questa fattoria ha i lavoranti che occorrono, tutti al lavoro nei campi." }
    { group:178, id:0, text: "completo." }
    { group:178, id:1, text: "I manovali stanno finendo la parte esterna della piramide." }
    { group:178, id:2, text: "Il lavoro è" }
    { group:178, id:3, text: "I manovali stanno ripulendo il cantiere per la piramide." }
    { group:178, id:4, text: "I manovali stanno ripulendo il cantiere per la mastaba." }
    { group:178, id:5, text: "I lavoratori stanno tagliando i canali nella pietra per contenere l'acqua." }
    { group:178, id:6, text: "I canali alla base della piramide sono stati riempiti d'acqua." }
    { group:178, id:7, text: "L'acqua viene prosciugata dalla zona della piramide e  vengono effettuate le marcature per il livellamento" }
    { group:178, id:8, text: "La roccia viene tagliata per livellare il suolo" }
    { group:178, id:9, text: "I canali sono stati riempiti di macerie" }
    { group:178, id:10, text: "La base è stata livellata, inizia la costruzione della tomba" }
    { group:178, id:11, text: "La base è stata livellata, viene posto il tetto sulla tomba" }
    { group:178, id:12, text: "Capo cantiere" }
    { group:178, id:13, text: "Mi occorre della manovalanza per terminare il lavoro. Devi costruire dei campi di lavoro." }
    { group:178, id:14, text: "Non ci sono scalpellini disponibili per lavorare a questo monumento. Se vuoi proseguire nei lavori, costruisci subito una Gilda degli scalpellini!" }
    { group:178, id:15, text: "Come posso assumere dei muratori se in città non c'è una Gilda dei muratori?" }
    { group:178, id:16, text: "Per terminare questo monumento devo poter accedere alla Gilda dei carpentieri." }
    { group:178, id:17, text: "Sto aspettando che arrivino i manovali. Forse dovresti visitare i campi di lavoro e verificare eventuali problemi." }
    { group:178, id:18, text: "Sto aspettando che arrivino gli scalpellini. Forse, se visiti la loro gilda, puoi scoprire se ci sono dei problemi." }
    { group:178, id:19, text: "Sto aspettando che arrivino i muratori. Dovresti visitare la loro gilda, magari ci sono dei problemi." }
    { group:178, id:20, text: "Ho bisogno di un carpentiere. Subito. Forse c'è qualche problema alla gilda dei carpentieri." }
    { group:178, id:21, text: "I miei lavoratori stanno aspettando che un carpentiere costruisca una rampa per raggiungere il livello superiore." }
    { group:178, id:22, text: "I miei scalpellini hanno bisogno di una fornitura di pietra per questo monumento." }
    { group:178, id:23, text: "I miei scalpellini hanno bisogno di una fornitura di calcare per questo monumento." }
    { group:178, id:24, text: "I miei scalpellini hanno bisogno di una fornitura di arenaria per questo monumento." }
    { group:178, id:25, text: "I miei scalpellini hanno bisogno di una fornitura di granito per questo monumento." }
    { group:178, id:26, text: "Se non importerai del marmo, i nostri scalpellini non potranno completare questo monumento." }
    { group:178, id:27, text: "I miei scalpellini hanno bisogno di una fornitura di mattoni per questo monumento." }
    { group:178, id:28, text: "I miei scalpellini hanno bisogno di una fornitura di legno per questo monumento." }
    { group:178, id:29, text: "I nostri scalpellini sarebbero pronti a posare le lastre del tetto, se solo avessero del rame. Estrai altro rame o importane da un'altra città." }
    { group:178, id:30, text: "Capo cantiere" }
    { group:178, id:31, text: "Ho bisogno di altri manovali per continuare i lavori. Devi costruire dei campi di lavoro." }
    { group:178, id:32, text: "Senza una gilda degli scalpellini, non ci sono scalpellini per costruire questo monumento." }
    { group:178, id:33, text: "I lavoratori stanno ripulendo e livellando il sito della costruzione. In seguito, avremo bisogno di molti mattoni e calcare per completare il monumento." }
    { group:178, id:34, text: "Tutto sembra procedere per il meglio, la piramide continua a crescere sempre più in alto." }
    { group:178, id:35, text: "Gli scalpellini stanno rifinendo la piramide. Per finire il lavoro non ci occorrono altri mattoni o calcare." }
    { group:178, id:36, text: "I lavoratori stanno ripulendo e livellando il sito della costruzione. In seguito, avremo bisogno di molta pietra per completare il monumento." }
    { group:178, id:37, text: "Tutto sembra procedere per il meglio, la piramide continua a crescere gradino dopo gradino." }
    { group:178, id:38, text: "Finalmente, la piramide è finita!" }
    { group:178, id:39, text: "I lavoratori stanno ripulendo il sito della costruzione. In seguito, avremo bisogno di molti mattoni per la mastaba." }
    { group:178, id:40, text: "Tutto sembra procedere per il meglio, la mastaba sarà finita molto presto." }
    { group:178, id:41, text: "La mastaba è terminata." }
    { group:178, id:42, text: "Finalmente abbiamo tutto il granito che ci serve. Non appena i carpentieri finiscono di costruire l'impalcatura, gli scalpellini possono iniziare a scolpire l'obelisco." }
    { group:178, id:43, text: "I miei scalpellini stanno lavorando all'obelisco." }
    { group:178, id:44, text: "L'obelisco è terminato!" }
    { group:178, id:45, text: "Gli scalpellini stanno creando la forma grezza della sfinge." }
    { group:178, id:46, text: "Gli scalpellini stanno rifinendo la sfinge." }
    { group:178, id:47, text: "I lavoratori stanno terminando e dipingendo la sfinge." }
    { group:178, id:48, text: "La sfinge è terminata!" }
    { group:178, id:49, text: "La carpenteria è" }
    { group:178, id:50, text: "Il lavoro degli scalpellini è" }
    { group:178, id:51, text: "In questo periodo dell'anno, la maggior parte dei contadini è al lavoro nei campi." }
    { group:178, id:52, text: "L'accesso al monumento è bloccato." }
    { group:178, id:53, text: "Ora che abbiamo arenaria a sufficienza, possiamo iniziare la costruzione del tempio del sole. I miei lavoratori stanno ripulendo il sito." }
    { group:178, id:54, text: "Quando i miei carpentieri finiscono le impalcature, gli scalpellini possono iniziare a scolpire l'obelisco centrale." }
    { group:178, id:55, text: "I miei scalpellini stanno costruendo l'obelisco centrale. Quando hanno finito, ci occorrerà dell'arenaria per costruire il resto del tempio del sole." }
    { group:178, id:56, text: "Non appena finiamo il vestibolo, le mura e il tempio anteriore, il monumento sarà completo." }
    { group:178, id:57, text: "Il tempio del sole è finito!" }
    { group:178, id:58, text: "Ora che abbiamo arenaria a sufficienza, possiamo iniziare la costruzione. I miei lavoratori stanno ripulendo il sito." }
    { group:178, id:59, text: "I miei scalpellini stanno lavorando sodo per completare il mausoleo. Se l'arenaria non ci manca, non dovrebbero esserci problemi." }
    { group:178, id:60, text: "Il mausoleo è finito." }
    { group:178, id:61, text: "Percentuale completamento [monument_name]: [percent_complete]" }
    { group:178, id:62, text: "Nessuna fase terminata." }
    { group:178, id:63, text: "I lavoranti stanno ultimando e dipingendo la sfinge." }
    { group:178, id:64, text: "[number_courses_complete] fasi terminate." }
    { group:178, id:65, text: "La fase attuale richiede [quantity_needed_current_course_main] ([number_loads_current_course_main]) per essere completata." }
    { group:178, id:66, text: "La fase attuale richiede [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) per essere completata." }
    { group:178, id:67, text: "La fase attuale richiede [quantity_needed_current_course_main] ([number_loads_current_course_main]) e [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) per essere completata." }
    { group:178, id:68, text: "Il resto [monument_name] richiede ancora [quantity_needed_remainder_main] ([number_loads_remainder_main])." }
    { group:178, id:69, text: "Il resto [monument_name] richiede ancora [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:70, text: "Il resto [monument_name] richiede ancora [quantity_needed_remainder_main] ([number_loads_remainder_main]) e [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:71, text: "Il monumento [monument_name] è ora completo e contiene un totale di [quantity_total_main]." }
    { group:178, id:72, text: "Il monumento [monument_name] è ora completo e contiene un totale di [quantity_total_main] e [quantity_total_secondary]." }
    { group:178, id:73, text: "della mastaba" }
    { group:178, id:74, text: "della piramide" }
    { group:178, id:75, text: "della piramide a gradini" }
    { group:178, id:76, text: "della piramide sghemba" }
    { group:178, id:77, text: "della piramide in mattoni" }
    { group:178, id:78, text: "dell'obelisco" }
    { group:178, id:79, text: "della sfinge" }
    { group:178, id:80, text: "del tempio del sole" }
    { group:178, id:81, text: "della Biblioteca di Alessandria" }
    { group:178, id:82, text: "Abu Simbel" }
    { group:178, id:83, text: "Tomba reale piccola" }
    { group:178, id:84, text: "Tomba reale media" }
    { group:178, id:85, text: "Tomba reale grande" }
    { group:178, id:86, text: "Tomba reale enorme" }
    { group:178, id:87, text: "del Caesareum" }
    { group:178, id:88, text: "del faro" }
    { group:178, id:89, text: "del mausoleo" }
    { group:178, id:90, text: "blocchi di pietra" }
    { group:178, id:91, text: "blocchi di calcare" }
    { group:178, id:92, text: "blocchi di granito" }
    { group:178, id:93, text: "blocchi di arenaria" }
    { group:178, id:94, text: "mattoni" }
    { group:178, id:95, text: "blocchi di marmo" }
    { group:178, id:96, text: "lingotti di rame" }
    { group:178, id:97, text: "Questo mausoleo richiede i servizi di un carpentiere." }
    { group:178, id:98, text: "Il supervisore commerciale si rifiuta di consegnare la pietra ai miei lavoratori. Dice che gli hai ordinato di accumularla. Io non gli credo, ma forse faresti meglio a consultarlo di persona." }
    { group:178, id:99, text: "Il tuo supervisore commerciale dice che gli hai ordinato di accumulare il calcare. Se non lo consulti, i miei lavoratori non avranno il materiale da costruzione." }
    { group:178, id:100, text: "Hai davvero ordinato al supervisore commerciale di accumulare l'arenaria? Così non autorizzerà alcuna consegna dai magazzini." }
    { group:178, id:101, text: "Puoi chiedere al tuo supervisore commerciale di fermare l'accumulo di marmo bianco? Ne abbiamo davvero bisogno per il monumento." }
    { group:178, id:102, text: "Il supervisroe commerciale dice che gli hai ordinato di accumulare granito. Se non gli parli subito, i lavoratori non potranno ricevere le consegne di granito." }
    { group:178, id:103, text: "Il tuo supervisore commerciale osa darti la colpa per il blocco dei lavori! Afferma che gli hai ordinato di accumulare i mattoni." }
    { group:178, id:104, text: "Il supervisore commerciale mi ha detto che hai ordinato di accumulare rame. Sono certo che hai avuto le tue buone ragioni per farlo, ma i miei uomini non possono continuare a lavorare sul monumento senza questa risorsa." }
    { group:178, id:105, text: "Il Faraone non sarà contento, se le sue gesta non saranno raccontate in modo elegante. Senza una Gilda degli artigiani, chi potrà dipingere gli affreschi nelle tombe?" }
    { group:178, id:106, text: "Una tomba davvero spoglia, vero? E rimarrà così, se non arriveranno presto degli artigiani! Ho sempre pensato che fossero pigri. Meglio se ti informi sui motivi del loro ritardo." }
    { group:178, id:107, text: "Senza il marmo i nostri abili scalpellini non possono fare nulla. È un vero peccato, io preferirei vederli al lavoro. Sarà meglio che importi del marmo in fretta." }
    { group:178, id:108, text: "Il tetto farà acqua come un colabrodo se non ci consegnano del rame. Se non puoi estrarlo faresti meglio a importarlo. Se arriva entro breve, il monumento sarà completato in fretta!" }
    { group:178, id:109, text: "I lavoratori stanno ripulendo e livellando il terreno. Questo è il momento ideale per accumulare un po' di marmo." }
    { group:178, id:110, text: "Il lavoro procede bene. I lavoratori hanno tutto il materiale che occorre." }
    { group:178, id:111, text: "È incredibile, ma il supervisore commerciale mi ha detto che il marmo si trova in accumulo nei depositi merci. Come possiamo continuare a lavorare senza forniture di marmo?" }
    { group:178, id:112, text: "Una fonte certa mi ha informato che il granito è in accumulo. Credi che possa evocare il materiale da costruzione dalle acque del Nilo? Farai meglio a rendere immediatamente disponibile il granito ai miei lavoratori." }
    { group:178, id:113, text: "Senza le forniture di rame come possiamo completare il tetto di questa grande struttura? Pare incredibile, ma il supervisore commerciale mi ha detto che lo sta accumulando." }
    { group:178, id:114, text: "Stiamo aspettando che i manovali preparino il terreno." }
    { group:178, id:115, text: "Ora che il terreno è pronto, gli scalpellini possono gettare le fondamenta." }
    { group:178, id:116, text: "Le fondamenta sono complete, dunque possiamo lavorare sul pavimento." }
    { group:178, id:117, text: "Ora che il pavimento c'è, possiamo erigere alcune colonne." }
    { group:178, id:118, text: "Il prossimo passo è la costruzione del tetto: le colonne sono state erette." }
    { group:178, id:119, text: "Adesso ci serve un po' di rame, per far brillare il tetto come il sole." }
    { group:178, id:120, text: "Stiamo dando i tocchi finali alla biblioteca." }
    { group:178, id:121, text: "La biblioteca di Alessandria è finita ed è il centro culturale del mondo conosciuto." }
    { group:178, id:122, text: "I manovali stanno lavorando duramente per preparare il terreno per il Caesareum." }
    { group:178, id:123, text: "Ora che il terreno è pronto, gli scalpellini stanno costruendo solide fondamenta." }
    { group:178, id:124, text: "I nostri scalpellini sono stanchi dopo aver costruito le fondamenta. Ma il lavoro non conosce soste: è in corso la costruzione del tempio." }
    { group:178, id:125, text: "Dopo aver terminato il tempio centrale, sono iniziati i lavori sul patio!" }
    { group:178, id:126, text: "Dal patio al portico! I nostri abili scalpellini hanno terminato il patio e hanno iniziato a lavorare sul portico. " }
    { group:178, id:127, text: "Gli scalpellini hanno iniziato a posare il tetto sui pilastri del portico." }
    { group:178, id:128, text: "Le varie sezioni del tetto sono tutte al loro posto sopra il portico" }
    { group:178, id:129, text: "Il maestoso ingresso del Caesareum è pronto." }
    { group:178, id:130, text: "Gli scalpellini hanno finito di costruire l'interno del Caesareum e sono passati agli obelischi di granito che adornano l'esterno dell'edificio." }
    { group:178, id:131, text: "Il Caesareum è completo e celebra l'unione tra Roma e l'Egitto" }
    { group:178, id:132, text: "I manovali hanno iniziato il difficile lavoro di preparazione del terreno." }
    { group:178, id:133, text: "Gli scalpellini sono impegnati a gettare le fondamenta del Faro." }
    { group:178, id:134, text: "Le fondamenta sono quasi complete e la posa del pavimento in legno è in corso" }
    { group:178, id:135, text: "Ora che il pavimento a parquet è finito, gli scalpellini sono passati al primo livello del Faro." }
    { group:178, id:136, text: "Gli scalpellini non hanno molto tempo di ammirare com'è venuto il primo livello: presto inizieranno i lavori sul secondo livello ottagonale." }
    { group:178, id:137, text: "Il Faro sta venendo su molto bene. Il livello ottagonale è finito e presto gli scalpellini passeranno alla cupola." }
    { group:178, id:138, text: "Ora anche l'ultimo pezzo del Faro è al suo posto, ma il monumento non sarà finito se non quando avranno tolto i ponteggi. Stanno iniziando ora." }
    { group:178, id:139, text: "Quasi tutti i ponteggi sono stati tolti: il Faro è quasi completo." }
    { group:178, id:140, text: "Il faro di Pharos è finito e arde come una stella nel Mediterraneo Orientale." }
    { group:178, id:141, text: "Gli operai sono impegnati a lavorare su Abu Simbel. Controlla che i carpentieri abbiano tanto legno, affinché possano costruire i ponteggi senza ritardi." }
    { group:178, id:142, text: "Le impressionanti figure del nostro Ramses II salutano tutti coloro che giungono in Egitto da sud." }
    { group:178, id:143, text: "Artigiani e scalpellini rifiutano di entrare nella Tomba reale senza lampade. Laggiù è buio pesto!" }
    { group:178, id:144, text: "Artigiani e scalpellini sono intenti nel loro lavoro: la Tomba reale sta prendendo rapidamente forma. Ricorda di garantire alla gilda degli artigiani un regolare invio di argilla e di vernice per assicurare il fluido procedimento dei lavori." }
    { group:178, id:145, text: "La Tomba reale è terminata. Tutto ciò che manca sono le provviste che serviranno ai morti nell'aldilà." }
    { group:178, id:146, text: "La Tomba reale nascosta è pronta per il Faraone. Che Horus la sorvegli sempre e abbatta chiunque osi violarla!" }
    { group:178, id:147, text: "Lampade:" }
    { group:178, id:148, text: "I lavoratori non possono arrivare all'entrata della tomba. Verifica cosa li blocca!" }
    { group:178, id:149, text: "Gli operai non possono raggiungere il punto dove sorgerà il monumento. Controlla che cosa blocca la strada." }
    { group:179, id:0, text: "Campo di lavoro" }
    { group:179, id:1, text: "Questo edificio ospita dei lavoranti che possono lavorare nei campi o per i monumenti." }
    { group:179, id:2, text: "Questo edificio ha bisogno di lavoratori per addestrare i lavoranti." }
    { group:179, id:3, text: "Stiamo addestrando i lavoranti il più in fretta possibile." }
    { group:179, id:4, text: "I nostri lavoranti sono fuori in cerca di lavoro." }
    { group:179, id:5, text: "I nostri lavoranti sono fuori al lavoro nei campi." }
    { group:179, id:6, text: "I nostri lavoranti sono fuori al lavoro per i monumenti." }
    { group:179, id:7, text: "I nostri lavoranti sono fuori al lavoro nei campi e per i monumenti." }
    { group:180, id:0, text: "Fabbrica di mattoni" }
    { group:180, id:1, text: "Here's where bricks are made from clay and straw." }
    { group:180, id:2, text: "Produzione completa: " }
    { group:180, id:3, text: " " }
    { group:180, id:4, text: "Il supervisore commerciale ha fermato la produzione di mattoni." }
    { group:180, id:5, text: "Questo laboratorio non ha operai. La produzione è ferma." }
    { group:180, id:6, text: "Questo laboratorio ha tutti gli addetti che occorrono e lavora a ritmo serrato per produrre mattoni." }
    { group:180, id:7, text: "Questo laboratorio lavora a ritmo ridotto. La produzione va a rilento." }
    { group:180, id:8, text: "Questo laboratorio è a corto di personale. Produce con più lentezza di quanto dovrebbe." }
    { group:180, id:9, text: "Pochissime persone lavorano in questo laboratorio. La produzione è lenta." }
    { group:180, id:10, text: "Con così pochi lavoratori, la produzione è quasi ferma. Produrrà ben poco per il prossimo anno." }
    { group:180, id:11, text: "Per produrre mattoni, questo laboratorio ha bisogno di argilla dai depositi o dalle cave." }
    { group:180, id:12, text: "Per produrre mattoni, questo laboratorio ha bisogno di paglia dai depositi o dalle coltivazioni di grano." }
    { group:180, id:13, text: "Argilla:" }
    { group:180, id:14, text: "Paglia:" }
    { group:181, id:0, text: "Coltivazione d'orzo" }
    { group:181, id:1, text: "L'orzo è l'ingrediente principale per la birra, senza la quale la civiltà non può esistere." }
    { group:181, id:2, text: "Produzione completa: " }
    { group:181, id:3, text: " " }
    { group:181, id:4, text: "Il supervisore commerciale ha bloccato la coltivazione di orzo." }
    { group:181, id:5, text: "Questa fattoria non ha braccianti. Il terreno è inutilizzato." }
    { group:181, id:6, text: "Questa fattoria ha tutti i braccianti di cui ha bisogno e sfrutta al massimo il suo terreno." }
    { group:181, id:7, text: "Questa fattoria funziona a ritmo ridotto: con più braccianti potrebbe risultare più produttiva." }
    { group:181, id:8, text: "Questa fattoria è a corto di braccianti, essi impiegano molto tempo per coltivare l'orzo." }
    { group:181, id:9, text: "Qui lavorano così pochi braccianti, che avremo orzo a sufficienza solo per la birra leggera." }
    { group:181, id:10, text: "Questa fattoria non ha braccianti e la produzione è virtualmente ferma." }
    { group:181, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:181, id:12, text: "Terra fertile: " }
    { group:181, id:13, text: " " }
    { group:181, id:14, text: "Il prossimo raccolto di orzo è a" }
    { group:182, id:0, text: "Coltivazione di ceci" }
    { group:182, id:1, text: "I ceci sono una buona fonte di proteine e sono molto popolari in tutte le diete." }
    { group:182, id:2, text: "Produzione completa: " }
    { group:182, id:3, text: " " }
    { group:182, id:4, text: "Il supervisore commerciale ha bloccato la coltivazione di ceci." }
    { group:182, id:5, text: "Questa fattoria non ha braccianti. Il terreno è inutilizzato." }
    { group:182, id:6, text: "Questa fattoria ha tutti i braccianti di cui ha bisogno e sfrutta al massimo il suo terreno." }
    { group:182, id:7, text: "Questa fattoria funziona a ritmo ridotto: con più braccianti potrebbe risultare più produttiva." }
    { group:182, id:8, text: "Questa fattoria è a corto di braccianti, essi impiegano molto tempo per crescere i ceci." }
    { group:182, id:9, text: "Qui lavorano pochissimi braccianti, la produzione è lenta." }
    { group:182, id:10, text: "Questa fattoria non ha braccianti e la produzione è virtualmente ferma." }
    { group:182, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:182, id:12, text: "Terra fertile: " }
    { group:182, id:13, text: " " }
    { group:182, id:14, text: "Il prossimo raccolto di ceci è a" }
    { group:183, id:0, text: "Coltivazione di fichi" }
    { group:183, id:1, text: "I fichi sono fondamentali in ogni dieta equilibrata." }
    { group:183, id:2, text: "Produzione completa: " }
    { group:183, id:3, text: " " }
    { group:183, id:4, text: "Il supervisore commerciale ha bloccato la coltivazione di fichi." }
    { group:183, id:5, text: "Questa fattoria non ha braccianti. Il terreno è inutilizzato." }
    { group:183, id:6, text: "Questa fattoria ha tutti i braccianti di cui ha bisogno e sfrutta al massimo il suo terreno." }
    { group:183, id:7, text: "Questa fattoria funziona a ritmo ridotto: con più braccianti potrebbe risultare più produttiva." }
    { group:183, id:8, text: "Questa fattoria è a corto di braccianti, essi impiegano molto tempo per crescere i fichi." }
    { group:183, id:9, text: "Qui lavorano pochissimi braccianti, la produzione è lenta." }
    { group:183, id:10, text: "Questa fattoria non ha braccianti e la produzione è virtualmente ferma." }
    { group:183, id:11, text: "Il terreno di questa fattoria è stato devastato dal recente sciame di locuste, ci vorrà quindi del tempo prima che torni produttivo." }
    { group:183, id:12, text: "Terra fertile: " }
    { group:183, id:13, text: " " }
    { group:183, id:14, text: "Il prossimo raccolto è a" }
    { group:184, id:0, text: "Trasporto" }
    { group:184, id:1, text: "Nave da guerra" }
    { group:184, id:2, text: "Resistenza scafo" }
    { group:184, id:3, text: "Molto forte" }
    { group:184, id:4, text: "Forte" }
    { group:184, id:5, text: "Buona" }
    { group:184, id:6, text: "Media" }
    { group:184, id:7, text: "Decente" }
    { group:184, id:8, text: "Debole" }
    { group:184, id:9, text: "Mantieni posizione" }
    { group:184, id:10, text: "Con questo ordine, la nave rimane nella sua posizione, bloccando il passaggio di tutte le navi nemiche finché rimane a galla." }
    { group:184, id:11, text: "Attacca nemici vicini" }
    { group:184, id:12, text: "Con questo ordine, la nave da guerra controlla una piccola area. Si sposta per attaccare soldati o navi nemiche che entrano nel suo raggio d'azione." }
    { group:184, id:13, text: "Cerca e distruggi nemici" }
    { group:184, id:14, text: "Con questo ordine, la nave da guerra cerca in lungo e in largo soldati o navi nemiche, attaccando tutto ciò che può raggiungere." }
    { group:184, id:15, text: "Riparazione" }
    { group:184, id:16, text: "La nave ritorna al cantiere per la riparazione. I capitani di navi molto danneggiate si dirigeranno in riparazione di propria iniziativa." }
    { group:184, id:17, text: "Torna al molo" }
    { group:184, id:18, text: "Con questo ordine, la nave torna al suo molo di appartenenza, dove l'equipaggio può riposare corpo e spirito." }
    { group:184, id:19, text: "Mantieni posizione" }
    { group:184, id:20, text: "Con questo ordine, la nave rimane in posizione a tutti i costi. Se viene attaccata, non rimarrà a galla per molto tempo." }
    { group:184, id:21, text: "Evita nemici" }
    { group:184, id:22, text: "Il capitano di questa nave ha l'ordine di evitare i nemici. Salvo contrordine, cercherà di sfuggire al contatto con il nemico e di proteggere le truppe che trasporta." }
    { group:184, id:23, text: "Imbarco" }
    { group:184, id:24, text: "Con questo ordine, il capitano caricherà una compagnia di soldati per il trasporto." }
    { group:184, id:25, text: "Sbarco" }
    { group:184, id:26, text: "Con questo ordine, il capitano farà sbarcare su terraferma una compagnia di soldati." }
    { group:184, id:27, text: "Stato equipaggio" }
    { group:184, id:28, text: "Riposato" }
    { group:184, id:29, text: "Stanco" }
    { group:184, id:30, text: "Esausto" }
    { group:184, id:31, text: "Compagnia di arcieri," }
    { group:184, id:32, text: "Compagnia di carri da guerra," }
    { group:184, id:33, text: "Compagnia di fanti," }
    { group:184, id:34, text: "a bordo" }
    { group:185, id:0, text: "Fabbrica bighe" }
    { group:185, id:1, text: "Qui gli esperti artigiani producono le \"ruote da guerra\", una delle armi egizie più terrificanti." }
    { group:185, id:2, text: "Produzione completa: " }
    { group:185, id:3, text: " " }
    { group:185, id:4, text: "Il supervisore commerciale ha deciso di fermare la produzione di carri da guerra." }
    { group:185, id:5, text: "Questo costruttore di bighe non ha impiegati e non può produrre bighe." }
    { group:185, id:6, text: "Questo costruttore di bighe ha tutto il personale che occorre e produce molte bighe di alta qualità." }
    { group:185, id:7, text: "Questo costruttore di bighe potrebbe utilizzare più lavoratori per raggiungere il pieno potenziale." }
    { group:185, id:8, text: "Questo costruttore di bighe è a corto di personale e produce bighe con più lentezza di quanto dovrebbe." }
    { group:185, id:9, text: "Qui lavorano pochissime persone, la produzione di bighe è molto lenta." }
    { group:185, id:10, text: "Con così pochi impiegati, la produzione di carri da guerra è agli sgoccioli. Produrrà ben poco per il prossimo anno." }
    { group:185, id:11, text: "Questa fabbrica non produrrà carri da guerra senza carichi di legno provenienti dal deposito merci o da quello della legna." }
    { group:185, id:12, text: "Legno in magazzino," }
    { group:187, id:0, text: "Sconosciuto" }
    { group:187, id:1, text: "Divinità locale" }
    { group:187, id:2, text: "Dio patrono" }
    { group:188, id:0, text: "Piazza delle festività" }
    { group:188, id:1, text: "Quando ordini al supervisore dei templi di indire una festività in onore di uno degli dei, i cittadini si radunano qui per parteciparvi." }
    { group:188, id:2, text: "Indìci una festività per rendere la gente felice e appagare gli dei." }
    { group:188, id:3, text: "Festività in corso" }
    { group:189, id:0, text: "Altare di Sebek" }
    { group:189, id:1, text: "Oracolo di Min" }
    { group:189, id:2, text: "Altare di Ma'at" }
    { group:189, id:3, text: "Oracolo di Horus" }
    { group:189, id:4, text: "Altare di Amon" }
    { group:189, id:5, text: "Oracolo di Thoth" }
    { group:189, id:6, text: "Altare di Anubis" }
    { group:189, id:7, text: "Oracolo di Sekhmet" }
    { group:189, id:8, text: "Altare di Iside" }
    { group:189, id:9, text: "Oracolo di Hathor" }
    { group:190, id:0, text: "Fabbrica di papiro" }
    { group:190, id:1, text: "Qui le canne vengono unite per fabbricare il papiro, necessario alle istituzioni scolastiche per scrivere informazioni e diffondere la conoscenza. Il Papiro può anche essere esportato con profitto." }
    { group:190, id:2, text: "Produzione completa: " }
    { group:190, id:3, text: " " }
    { group:190, id:4, text: "Il supervisore commerciale ha deciso di chiudere la produzione di papiro." }
    { group:190, id:5, text: "Questo laboratorio non ha operai. La produzione è ferma." }
    { group:190, id:6, text: "Questo laboratorio ha tutti gli addetti che occorrono e lavora a ritmo serrato per produrre papiri di alta qualità." }
    { group:190, id:7, text: "Questo laboratorio lavora a ritmo ridotto. La produzione va a rilento." }
    { group:190, id:8, text: "Questo laboratorio è a corto di personale. Produce con più lentezza di quanto dovrebbe." }
    { group:190, id:9, text: "Pochissime persone lavorano in questo laboratorio. La produzione di papiro è lenta." }
    { group:190, id:10, text: "Con così pochi lavoratori, la produzione di papiro è quasi ferma. Produrrà ben poco per il prossimo anno." }
    { group:190, id:11, text: "Questo laboratorio non produrrà papiro senza un carico di canne, da un deposito merci o da un raccoglitore di canne." }
    { group:190, id:12, text: "Canne in magazzino," }
    { group:191, id:0, text: "Finestra trucchi" }
    { group:191, id:1, text: "Disabilita trucchi" }
    { group:192, id:0, text: "Cava di granito" }
    { group:192, id:1, text: "Per gli obelischi occorrono i blocchi di robusto granito che qui puoi estrarre dalle viscere della terra." }
    { group:192, id:2, text: "Produzione completa: " }
    { group:192, id:3, text: " " }
    { group:192, id:4, text: "Il supervisore commerciale ha bloccato l'estrazione di granito." }
    { group:192, id:5, text: "Questo edificio non ha addetti. La produzione è ferma." }
    { group:192, id:6, text: "Questo edificio ha tutti gli addetti che occorrono e lavora a ritmo serrato per produrre granito." }
    { group:192, id:7, text: "Questo edificio lavora a ritmo ridotto. La produzione potrebbe migliorare con più lavoratori." }
    { group:192, id:8, text: "Questa cava è a corto di personale. Produce granito con più lentezza di quanto dovrebbe." }
    { group:192, id:9, text: "Pochissime persone lavorano in questo edificio. La produzione di granito è bassa." }
    { group:192, id:10, text: "Con così pochi lavoratori, la produzione di granito è quasi ferma. Produrrà ben poco per il prossimo anno." }
    { group:193, id:0, text: "Miniera di rame" }
    { group:193, id:1, text: "Facile da lavorare e duraturo, il rame è ottimo per le armi e per l'esportazione." }
    { group:193, id:2, text: "Produzione completa: " }
    { group:193, id:3, text: " " }
    { group:193, id:4, text: "Il supervisore commerciale ha ordinato il blocco all'estrazione di rame." }
    { group:193, id:5, text: "Questa miniera non ha operai. L'estrazione è ferma." }
    { group:193, id:6, text: "Questa miniera ha tutti gli impiegati che occorrono e lavora a pieno ritmo per estrarre il rame." }
    { group:193, id:7, text: "Questa miniera lavora a ritmo ridotto. La produzione potrebbe migliorare con più lavoratori." }
    { group:193, id:8, text: "Questa miniera è a corto di personale. Produce rame con più lentezza di quanto dovrebbe." }
    { group:193, id:9, text: "Pochissime persone lavorano in questa miniera. La produzione di rame è lenta." }
    { group:193, id:10, text: "Con così pochi lavoratori, l'estrazione del rame è quasi ferma. Produrrà ben poco per il prossimo anno." }
    { group:194, id:0, text: "Cava di arenaria" }
    { group:194, id:1, text: "Solo l'arenaria offre le giuste proprietà per costruire mausolei e templi del sole." }
    { group:194, id:2, text: "Produzione completa: " }
    { group:194, id:3, text: " " }
    { group:194, id:4, text: "Il supervisore commerciale ha bloccato l'estrazione di arenaria." }
    { group:194, id:5, text: "Questa cava non ha lavoratori. La produzione è ferma." }
    { group:194, id:6, text: "Questa cava ha tutti gli addetti che occorrono e lavora a ritmo serrato per produrre arenaria." }
    { group:194, id:7, text: "Questa cava lavora a ritmo ridotto. La produzione potrebbe migliorare con più lavoratori." }
    { group:194, id:8, text: "Questa cava è a corto di personale. Produce arenaria con più lentezza di quanto dovrebbe." }
    { group:194, id:9, text: "Pochissime persone lavorano in questo edificio. La produzione di arenaria è lenta." }
    { group:194, id:10, text: "Con così pochi lavoratori, la produzione di arenaria è quasi ferma. Produrrà ben poco per il prossimo anno." }
    { group:195, id:0, text: "Abu" }
    { group:195, id:1, text: "Abydos" }
    { group:195, id:2, text: "Oasi di Bahariya" }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubastis" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Byblos" }
    { group:195, id:8, text: "Dahshur" }
    { group:195, id:9, text: "Oasi di Dakhla" }
    { group:195, id:10, text: "Djedu" }
    { group:195, id:11, text: "Oasi di Dunqul" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "Oasi di Farafra" }
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
    { group:195, id:24, text: "Oasi di Kharga" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knossos" }
    { group:195, id:27, text: "Kyrene" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mycenae" }
    { group:195, id:32, text: "Nekhen" }
    { group:195, id:33, text: "Nubt (Ombos)" }
    { group:195, id:34, text: "Attiva" }
    { group:195, id:35, text: "Perwadjyt" }
    { group:195, id:36, text: "Pwenet" }
    { group:195, id:37, text: "Qadesh" }
    { group:195, id:38, text: "Rostja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Saqqara" }
    { group:195, id:41, text: "Sauty" }
    { group:195, id:42, text: "Sawu" }
    { group:195, id:43, text: "Oasi di Selima" }
    { group:195, id:44, text: "Serabit Khadim" }
    { group:195, id:45, text: "Shaat" }
    { group:195, id:46, text: "Sharuhen" }
    { group:195, id:47, text: "Thinis" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toshka" }
    { group:195, id:50, text: "Tyre" }
    { group:195, id:51, text: "Waset" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alessandria" }
    { group:195, id:54, text: "Sumur" }
    { group:195, id:55, text: "Deir el-Medina" }
    { group:195, id:56, text: "Abu Simbel" }
    { group:195, id:57, text: "Actium" }
    { group:195, id:58, text: "Roma" }
    { group:195, id:59, text: "Tanis" }
    { group:195, id:60, text: "Pi-Yer" }
    { group:195, id:61, text: "Oasi di Siwi" }
    { group:195, id:62, text: "Maritis" }
    { group:195, id:63, text: "Piramesse" }
    { group:195, id:64, text: "Atene" }
    { group:195, id:65, text: "Cleoantonopolis" }
    { group:198, id:0, text: "Nessuna" }
    { group:198, id:1, text: "Piramide sghemba piccola" }
    { group:198, id:2, text: "Piramide sghemba media" }
    { group:198, id:3, text: "Piramide in matt. di fango piccola" }
    { group:198, id:4, text: "Piramide in mattoni di fango media" }
    { group:198, id:5, text: "Piramide in matt. di fango grande" }
    { group:198, id:6, text: "Compl. di piramidi in matt. di fango" }
    { group:198, id:7, text: "Gran compl. di pir. in matt. di fango" }
    { group:198, id:8, text: "Piramide a gradini piccola" }
    { group:198, id:9, text: "Piramide a gradini media" }
    { group:198, id:10, text: "Piramide a gradini grande" }
    { group:198, id:11, text: "Complesso di piramidi a gradini" }
    { group:198, id:12, text: "Grande compl. di piram. a gradoni" }
    { group:198, id:13, text: "Piramide piccola" }
    { group:198, id:14, text: "Piramide media" }
    { group:198, id:15, text: "Piramide grande" }
    { group:198, id:16, text: "Complesso di piramidi" }
    { group:198, id:17, text: "Grande complesso di piramidi" }
    { group:198, id:18, text: "Mastaba piccola" }
    { group:198, id:19, text: "Mastaba media" }
    { group:198, id:20, text: "Mastaba grande" }
    { group:198, id:21, text: "Sfinge" }
    { group:198, id:22, text: "Obelisco piccolo" }
    { group:198, id:23, text: "Obelisco grande" }
    { group:198, id:24, text: "Tempio del sole" }
    { group:198, id:25, text: "Mausoleo" }
    { group:198, id:26, text: "Mausoleo" }
    { group:198, id:27, text: "Mausoleo" }
    { group:198, id:28, text: "Faro di Pharos" }
    { group:198, id:29, text: "Biblioteca di Alessandria" }
    { group:198, id:30, text: "Caesareum" }
    { group:198, id:31, text: "Colossi" }
    { group:198, id:32, text: "Tempio di Luxor" }
    { group:198, id:33, text: "Tomba reale piccola" }
    { group:198, id:34, text: "Tomba reale media" }
    { group:198, id:35, text: "Tomba reale grande" }
    { group:198, id:36, text: "Tomba reale enorme" }
    { group:198, id:37, text: "Abu Simbel" }
    { group:199, id:0, text: "Supervisore ai monumenti" }
    { group:199, id:1, text: "in magazzino" }
    { group:199, id:2, text: "dei lavori." }
    { group:199, id:3, text: "Clicca sugli arredi funerari da consegnare." }
    { group:199, id:4, text: "Quantità da inviare" }
    { group:199, id:5, text: "Tutti" }
    { group:199, id:6, text: "Clicca per inviare" }
    { group:199, id:7, text: "Annulla" }
    { group:199, id:8, text: "Aumenta quantità" }
    { group:199, id:9, text: "Diminuisci quantità" }
    { group:199, id:10, text: "Invia arredi funerari" }
    { group:199, id:11, text: "Livello monumenti" }
    { group:199, id:12, text: "Non occorre inviare alcun arredo funerario." }
    { group:199, id:13, text: "Visita il luogo di costruzione per ulteriori dettagli." }
    { group:199, id:14, text: "Il lavoro alla piramide non è iniziato. Ti occorrono degli operai" }
    { group:199, id:15, text: "e, per completarlo, grandi quantità di pietra e calcare." }
    { group:199, id:16, text: "La piramide è al" }
    { group:199, id:17, text: "La piramide ora è completata!" }
    { group:199, id:18, text: "La piramide è finita e attende l'arrivo delle sacre spoglie." }
    { group:199, id:19, text: "Il lavoro alla pir. di mattoni non è iniziato. Servono operai" }
    { group:199, id:20, text: "e per completarlo grandi quantità di mattoni e calcare." }
    { group:199, id:21, text: "La piramide di mattoni è al" }
    { group:199, id:22, text: "La piramide di mattoni è ora completata!" }
    { group:199, id:23, text: "La piramide di mattoni è finita e attende l'arrivo delle sacre spoglie." }
    { group:199, id:24, text: "Il lavoro con la pir. a gradini non è iniziato. Servono operai" }
    { group:199, id:25, text: "e per completarlo grandi quantità di pietra." }
    { group:199, id:26, text: "La piramide a gradini è al" }
    { group:199, id:27, text: "La piramide a gradini è ora completata!" }
    { group:199, id:28, text: "La piramide a gradini è finita e attende l'arrivo delle sacre spoglie." }
    { group:199, id:29, text: "Il lavoro con la pir. sghemba non è iniziato. Servono operai" }
    { group:199, id:30, text: "e, per completarlo, grandi quantità di pietra e calcare." }
    { group:199, id:31, text: "La piramide sghemba è al" }
    { group:199, id:32, text: "La piramide sghemba è ora completata!" }
    { group:199, id:33, text: "La piramide sghemba è finita e attende l'arrivo delle sacre spoglie." }
    { group:199, id:34, text: "Il lavoro con la mastaba non è iniziato. Servono operai" }
    { group:199, id:35, text: "e, per completarlo, una grande quantità di mattoni." }
    { group:199, id:36, text: "La mastaba è al" }
    { group:199, id:37, text: "La mastaba è ora completata!" }
    { group:199, id:38, text: "La mastaba è finita e attende l'arrivo delle sacre spoglie." }
    { group:199, id:39, text: "Il lavoro con la sfinge non è iniziato. Servono carpentieri," }
    { group:199, id:40, text: "legno e pietra." }
    { group:199, id:41, text: "La sfinge è al" }
    { group:199, id:42, text: "La sfinge è ora completata!" }
    { group:199, id:43, text: "Il lavoro con l'obelisco non è iniziato. Ti occorreranno" }
    { group:199, id:44, text: "blocchi di granito. Al momento, hai" }
    { group:199, id:45, text: "L'obelisco è al" }
    { group:199, id:46, text: "L'obelisco è ora completato!" }
    { group:199, id:47, text: "Il lavoro al tempio del sole non è iniziato. Ti occorreranno" }
    { group:199, id:48, text: "blocchi di arenaria. Al momento, hai" }
    { group:199, id:49, text: "Il tempio del Sole è al" }
    { group:199, id:50, text: "Il tempio del Sole è completato!" }
    { group:199, id:51, text: "Il lavoro al mausoleo non è iniziato. Ti occorreranno" }
    { group:199, id:52, text: "blocchi di arenaria. Al momento, hai" }
    { group:199, id:53, text: "Il mausoleo è al" }
    { group:199, id:54, text: "Il mausoleo è ora completato!" }
    { group:199, id:55, text: "Il mausoleo è finito e attende l'arrivo delle sacre spoglie." }
    { group:199, id:56, text: "Clicca per visitare il luogo di costruzione." }
    { group:199, id:57, text: "blocco in magazzino" }
    { group:199, id:58, text: "blocchi in magazzino" }
    { group:199, id:59, text: "La costruzione della biblioteca di Alessandria non è ancora iniziata" }
    { group:199, id:60, text: "Ti occorrono lavoratori, marmo e rame" }
    { group:199, id:61, text: "La biblioteca di Alessandria è al" }
    { group:199, id:62, text: "La biblioteca di Alessandria ora è terminata!" }
    { group:199, id:63, text: "La costruzione del Casareum non è ancora iniziata" }
    { group:199, id:64, text: "Ti occorrono lavoratori, marmo e granito" }
    { group:199, id:65, text: "Il Caesareum è al" }
    { group:199, id:66, text: "Il Caesareum ora è completato!" }
    { group:199, id:67, text: "La costruzione del faro di Pharos non è ancora iniziata" }
    { group:199, id:68, text: "Ti occorrono lavoratori e marmo" }
    { group:199, id:69, text: "Il faro di Pharos è al" }
    { group:199, id:70, text: "Il faro di Pharos ora è completato!" }
    { group:199, id:71, text: "La costruzione di Abu Simbel non è ancora iniziata" }
    { group:199, id:72, text: "Ti occorrono carpentieri, scalpellini e legno" }
    { group:199, id:73, text: "Abu Simbel è al" }
    { group:199, id:74, text: "Abu Simbel ora è completato!" }
    { group:199, id:75, text: "La costruzione della Tomba piccola non è ancora iniziata: ti servono " }
    { group:199, id:76, text: "scalpellini, artigiani, argilla, pittura e lampade" }
    { group:199, id:77, text: "La Tomba reale piccola è al" }
    { group:199, id:78, text: "La Tomba reale piccola ora è completata!" }
    { group:199, id:79, text: "La costruzione della Tomba media non è ancora iniziata. Ti servono " }
    { group:199, id:80, text: "scalpellini, artigiani, argilla, pittura e lampade" }
    { group:199, id:81, text: "La Tomba reale media è al" }
    { group:199, id:82, text: "La Tomba reale media ora è completata!" }
    { group:199, id:83, text: "Il lavoro alla Tomba reale grande non è iniziato. Servono scalpellini," }
    { group:199, id:84, text: "artigiani, argilla, pittura e lampade" }
    { group:199, id:85, text: "La Tomba grande reale è al" }
    { group:199, id:86, text: "La Tomba reale grande è terminata!" }
    { group:199, id:87, text: "Il lavoro alla Tomba enorme non è iniziato. Servono scalpellini, " }
    { group:199, id:88, text: "artigiani, argilla, pittura e lampade" }
    { group:199, id:89, text: "La Tomba reale enorme è al" }
    { group:199, id:90, text: "La Tomba reale enorme è terminata!" }
    { group:200, id:0, text: "Fase Uno: Procura il granito per stabilire una struttura di massima" }
    { group:200, id:1, text: "Fase Due: I carpentieri usano il legno per costruire le impalcature" }
    { group:200, id:2, text: "Fase Tre: Gli scalpellini scolpiscono la forma finale, lavorando dall'alto verso il basso" }
    { group:200, id:3, text: "Stato:" }
    { group:200, id:4, text: "Non iniziato" }
    { group:200, id:5, text: "Incompleto" }
    { group:200, id:6, text: "Completo" }
    { group:200, id:7, text: "Avanzamento generale:" }
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
    { group:205, id:0, text: "Forse se gli rubo qualcosa, quella barba finta si accorgerà di me!" }
    { group:205, id:1, text: "Io prendo quello che mi pare! Non mi fermerete!" }
    { group:205, id:2, text: "Il furto è di gran lunga più profittevole del lavoro in questa città." }
    { group:205, id:3, text: "Rubare, rubare, rubare. Questo so fare!" }
    { group:206, id:0, text: "(Cough, cough) Ohhh, il mio stomaco! Oh, la mia testa!" }
    { group:207, id:0, text: "La peste può colpire in qualsiasi momento! Spero che si mantenga nelle parti più povere della città." }
    { group:207, id:1, text: "È scandaloso che una persona della mia levatura debba conoscere la fame!" }
    { group:207, id:2, text: "Non credo che questa città possa reggere un attacco e io ho molto da perdere." }
    { group:207, id:3, text: "Come possono così pochi lavoratori soddisfare i miei bisogni?" }
    { group:207, id:4, text: "Sto meglio di un dio! Spero che non ci attacchino." }
    { group:207, id:5, text: "Mi vergogno di vivere qui. Spero che i nemici non si avvantaggino della nostra reputazione!" }
    { group:207, id:6, text: "Ma guarda quanti fannulloni! Perché non lavorano?" }
    { group:207, id:7, text: "Come posso dichiararmi soddisfatto se non c'è nulla che possa divertirmi?" }
    { group:207, id:8, text: "Questa città è il massimo, almeno credo." }
    { group:207, id:9, text: "Questa città non potrebbe essere meglio!" }
    { group:207, id:10, text: "Queste feste sarebbero migliori se fossero esclusivamente a inviti" }
    { group:210, id:0, text: "Gli uccelli sono scaltri. Se non li avvicini nel modo giusto, volano via." }
    { group:210, id:1, text: "Guarda quegli uccelli meravigliosi: pronti da fare arrosto!" }
    { group:211, id:0, text: "Un'altra giornata ideale per la pesca. Spero che il bottino sia ricco come al solito." }
    { group:211, id:1, text: "Ne abbiamo già presi molti, ma dovevi vedere quello che ci è scappato!" }
    { group:211, id:2, text: "Fai in fretta! Non possiamo tornare al lavoro finché non prendi il nostro carico." }
    { group:215, id:0, text: "Paludi, paludi, paludi, Il giunco cresce soltanto nelle paludi." }
    { group:215, id:1, text: "Da questo giunco ricaverò degli ottimi papiri." }
    { group:216, id:0, text: "Al monumento attendono i miei servigi!" }
    { group:216, id:1, text: "Questo monumento sarebbe molto basso, senza le mie rampe e impalcature." }
    { group:217, id:0, text: "Ora tocca ai muratori al monumento!" }
    { group:217, id:1, text: "Con i miei mattoni il monumento sarà più forte." }
    { group:218, id:0, text: "Sto andando al monumento per scolpire le pietre." }
    { group:218, id:1, text: "Le mie pietre sopravviveranno ai secoli." }
    { group:219, id:0, text: "Si è ammalata così tanta gente. Spero che si riprenda presto, o saremo colpiti da una pestilenza." }
    { group:219, id:1, text: "Sono affamata. Molti clienti reclamano cibo, ma io riesco a stento a nutrire me stessa." }
    { group:219, id:2, text: "Le nostre difese sono deboli. Potrebbero invaderci facilmente." }
    { group:219, id:3, text: "Devo essere più cortese con i miei aiutanti. Con tutti questi nuovi lavori, posso perderli con facilità." }
    { group:219, id:4, text: "Se non tributeremo agli dei più rispetto, non tarderanno a infliggerci un tremendo castigo." }
    { group:219, id:5, text: "Presto pagheremo lo scotto per la cattiva reputazione di questa città!" }
    { group:219, id:6, text: "Sono fortunato ad avere un lavoro. So di molte persone che sono disoccupate." }
    { group:219, id:7, text: "Qui non succede niente di niente. Vorrei che ci fossero più spettacoli da vedere." }
    { group:219, id:8, text: "Non voglio lagnarmi di questa città... però potrei." }
    { group:219, id:9, text: "Questa città è il massimo." }
    { group:219, id:10, text: "Il bazar ha bisogno di merci e io le procurerò." }
    { group:219, id:11, text: "Queste merci saranno benvenute nel bazar." }
    { group:226, id:0, text: "Mai visti tanti malati. Spero che non scoppi una pestilenza." }
    { group:226, id:1, text: "E' dura prendere queste clave quando sei piegato dai morsi della fame." }
    { group:226, id:2, text: "Forse potrei scagliare queste palle contro i nemici se attaccano. Non mi pare ci sia molto di più per difendere la città." }
    { group:226, id:3, text: "Vedo dovunque offerte di lavoro! Non dovrò fare giochi di prestigio per averne uno." }
    { group:226, id:4, text: "Mi aspetto il peggio. Gli Dei penseranno che ci siamo dimenticati di loro." }
    { group:226, id:5, text: "Questa città ha una reputazione peggiore della mia. Spero che non ci attacchino." }
    { group:226, id:6, text: "Vorrei ci fossero più lavori in questa città. Quando faccio il mio numero nessuno può pagare." }
    { group:226, id:7, text: "Io so fare solo il giocoliere. Vorrei ci fossero altri artisti in città." }
    { group:226, id:8, text: "Questa città non è poi tanto male." }
    { group:226, id:9, text: "Non farei il giocoliere in nessun altro posto." }
    { group:226, id:10, text: "Mi piace lavorare per questa gente allegra. Sono tutti così felici!" }
    { group:227, id:10, text: "Queste festività sono fantastiche! Tutti cantano." }
    { group:229, id:0, text: "La salute pubblica è in pericolo. Il rischio di una pestilenza è alto." }
    { group:229, id:1, text: "Sono affamato come un ippopotamo, ma non c'è molto cibo in giro." }
    { group:229, id:2, text: "Dovrei imparare l'arte della guerra, con delle difese così deboli, siamo tutti in pericolo." }
    { group:229, id:3, text: "La mancanza di lavoro può causare davvero grossi guai in una città." }
    { group:229, id:4, text: "A dire la verità, io non tratterei gli dei così male." }
    { group:229, id:5, text: "La reputazione della città non è un gran che. Potremmo essere attaccati." }
    { group:229, id:6, text: "Per molti, trovare un lavoro è una fatica senza risultati." }
    { group:229, id:7, text: "Questa città dovrebbe accorgersi che manca il divertimento." }
    { group:229, id:8, text: "Non mi dispiace vivere qui." }
    { group:229, id:9, text: "Questa città ha conquistato il mio cuore. Adoro vivere qui." }
    { group:229, id:10, text: "Birra, birra per tutti! Birra filtrata, senza sedimenti!" }
    { group:235, id:0, text: "La città presto imparerà che la malasanità porta alla pestilenza." }
    { group:235, id:1, text: "La mia mente si nutre di conoscenza, ma il mio corpo anela il cibo." }
    { group:235, id:2, text: "Gli invasori non avranno problemi a penetrare le nostre difese." }
    { group:235, id:3, text: "La mancanza di lavoratori si sente in tutta la città e i servizi sono scarsi." }
    { group:235, id:4, text: "Il comportamento sacrilego della città scatenerà l'ira degli dei!" }
    { group:235, id:5, text: "Ah, reputazione, reputazione. La nostra reputazione scandalosa provocherà un attacco." }
    { group:235, id:6, text: "L'istruzione non può rimediare alla mancanza di lavoro." }
    { group:235, id:7, text: "Noiosa, piatta, tediosa, monotona, uffa... che razza di città." }
    { group:235, id:8, text: "Questa città è nella media." }
    { group:235, id:9, text: "Questa città è promossa a pieni voti!" }
    { group:235, id:10, text: "Durante le festività si imparano molte cose sulla natura umana." }
    { group:240, id:0, text: "Pare che la salute peggiori in tutta la città." }
    { group:240, id:1, text: "A giudicare dal numero di ammalati in città, presto mi ritroverò con le mani piene." }
    { group:240, id:2, text: "Sono alla fame. Tra poco, sarò più magro di una mummia." }
    { group:240, id:3, text: "La città non è protetta da alcuna difesa, i nemici possono spazzarci via." }
    { group:240, id:4, text: "Se mai volessi lasciare l'attività di imbalsamatore, ora è il momento giusto per farlo. C'è un sacco di lavoro in città." }
    { group:240, id:5, text: "Gli Dei potrebbero infuriarsi se questa città non rende loro omaggio." }
    { group:240, id:6, text: "La cattiva reputazione della città potrebbe essere la nostra morte. Potremmo essere attaccati in qualsiasi momento." }
    { group:240, id:7, text: "Quando vedo così tanti disoccupati, sono contento di avere molto lavoro." }
    { group:240, id:8, text: "la città è noiosa come un cadavere. Vorrei che fosse un po' più vitale." }
    { group:240, id:9, text: "Qui la vita non è male, più o meno come da qualsiasi altra parte." }
    { group:240, id:10, text: "Mi dispiace per i miei clienti, non possono più godersi questa fantastica città!" }
    { group:247, id:0, text: "La mia abilità con pittura e stucchi è richiesta al monumento!" }
    { group:247, id:1, text: "Io narro le gesta d'Egitto sui muri delle tombe reali!" }
    { group:248, id:0, text: "L'oro è per i vivi, non per i morti!" }
    { group:248, id:1, text: "Pensa quanto potrò ricavare dalla vendita di quei tesori!" }
    { group:249, id:0, text: "Combatteremo alla morte per difendere la nostra bella città!" }
    { group:249, id:1, text: "Il nemico è troppo forte per noi! Se ci ritiriamo, potremo combattere un altro giorno." }
    { group:249, id:2, text: "I nemici stanno venendo da questa parte!" }
    { group:249, id:3, text: "Siamo pericolosi come coccodrilli, pronti a colpire gli invasori quando arriveranno." }
    { group:249, id:4, text: "Se e quando il nemico arriverà, noi saremo pronti." }
    { group:250, id:0, text: "Remate in fretta! Dobbiamo proteggere la nostra nave a ogni costo!" }
    { group:250, id:1, text: "Il nemico è qui! Tutti ai posti di manovra." }
    { group:250, id:2, text: "Venite pure! Siamo pronti a ricevervi." }
    { group:250, id:3, text: "In caso di bisogno, siamo pronti a servire." }
    { group:251, id:0, text: "Chariot Exact 1" }
    { group:252, id:0, text: "Nessun nemico in vista, comunque siamo sempre all'erta." }
    { group:252, id:1, text: "Siamo acquattati come aspidi, pronti a colpire il nemico di sorpresa." }
    { group:252, id:2, text: "E lo chiami esercito?! Nessun problema a sbarazzarcene." }
    { group:252, id:3, text: "Il nemico è davvero feroce! Faccio il possibile per sconfiggerlo." }
    { group:253, id:0, text: "Tempio del Sole" }
    { group:253, id:1, text: "Fase 1" }
    { group:253, id:2, text: "L'obelisco grezzo è stato posizionato" }
    { group:253, id:3, text: "e i lavoratori stanno ripulendo lo spiazzo" }
    { group:253, id:4, text: "Fase 2" }
    { group:253, id:5, text: "I carpentieri stanno alzando le impalcature attorno" }
    { group:253, id:6, text: "all'obelisco" }
    { group:253, id:7, text: "Fase 3" }
    { group:253, id:8, text: "Gli scalpellini stanno rifinendo" }
    { group:253, id:9, text: "l'obelisco" }
    { group:253, id:10, text: "Fase 4" }
    { group:253, id:11, text: "Il vestibolo, le mura, la piazza e" }
    { group:253, id:12, text: "il tempio anteriore sono in costruzione" }
    { group:253, id:13, text: "Un solo scalpellino attende della pietra" }
    { group:253, id:14, text: "scalpellini attendono della pietra." }
    { group:253, id:15, text: "Il tempio del sole è" }
    { group:253, id:16, text: "percentuale completata" }
    { group:253, id:17, text: "blocchi di pietra sono necessari per" }
    { group:253, id:18, text: "finire la costruzione del tempio del sole." }
    { group:291, id:0, text: "Mausoleo" }
    { group:291, id:1, text: "Fase 1" }
    { group:291, id:2, text: "Le fondamenta sono state poste" }
    { group:291, id:3, text: "e i lavoratori stanno ripulendo lo spiazzo" }
    { group:291, id:4, text: "Fase 2" }
    { group:291, id:5, text: "Gli scalpellini stanno costruendo la parte inferiore" }
    { group:291, id:6, text: "del mausoleo" }
    { group:291, id:7, text: "Fase 3" }
    { group:291, id:8, text: "Gli scalpellini stanno costruendo la parte superiore" }
    { group:291, id:9, text: "del mausoleo" }
    { group:291, id:10, text: "Un singolo scalpellino attende della pietra" }
    { group:291, id:11, text: "scalpellini attendono della pietra" }
    { group:291, id:12, text: "Il mausoleo è" }
    { group:291, id:13, text: "percentuale completata" }
    { group:291, id:14, text: "blocchi di pietra sono necessari per" }
    { group:291, id:15, text: "finire la costruzione del mausoleo" }
    { group:292, id:0, text: "Crea Famiglia" }
    { group:292, id:1, text: "Elimina" }
    { group:292, id:2, text: "Avanti" }
    { group:292, id:3, text: "Diario di Famiglia" }
    { group:292, id:4, text: "Torna al menu principale" }
    { group:293, id:0, text: "Riprendi Storia di Famiglia" }
    { group:293, id:1, text: "Scegli una missione" }
    { group:293, id:2, text: "Carica partita salvata" }
    { group:293, id:3, text: "Missioni personalizzate" }
    { group:293, id:4, text: "Torna al Diario di Famiglia" }
    { group:293, id:5, text: "famiglia di [player_name]" }
    { group:293, id:6, text: "Studia la storia" }
    { group:293, id:7, text: "Inizia Storia di Famiglia" }
    { group:294, id:0, text: "Periodo predinastico" }
    { group:294, id:1, text: "Durante il periodo predinastico, i clan votati a governare l'Egitto compiono i primi e incerti passi verso la civilizzazione." }
    { group:294, id:2, text: "La tua famiglia inizia nel periodo predinastico alla guida di una tribù nomade verso la scoperta della civiltà. Il tuo carisma è fondamentale per porre le prime basi solide della grandiosità egizia, per ora ancora lontana." }
    { group:294, id:3, text: "Il periodo predinastico è l'alba della storia egizia e della tua famiglia." }
    { group:294, id:4, text: "Periodo arcaico" }
    { group:294, id:5, text: "Con il passare del tempo, i villaggi fondati durante il periodo predinastico si uniscono per formare un regno, con tanto di capitale e i suoi primi monumenti funebri." }
    { group:294, id:6, text: "Durante il periodo arcaico, i villaggi formati nel predinastico gradualmente si uniscono per formare un unico regno. La giovane civiltà fonda la sua capitale, assicura i confini, impara a sfruttare le acque e costruisce le prime tombe monumentali." }
    { group:294, id:7, text: "La tua storia di famiglia deve essere vissuta nell'ordine! Non puoi regnare nel periodo arcaico se prima non hai imparato le arti insegnate nel predinastico." }
    { group:294, id:8, text: "Vecchio regno" }
    { group:294, id:9, text: "L'Egitto trova la sua età dell'oro, con ricchezza, gloria e potenza, erigendo nuovi e strabilianti monumenti in tutto il mondo. Sì, dopo aver raggiunto queste altezze vertiginose, l'Egitto è caduto in guerra." }
    { group:294, id:10, text: "Durante il vecchio regno, l'Egitto giunge a una nuova vetta di potenza, ricchezza e gloria. Eppure, mentre in tutto il mondo sorgono incredibili monumenti, i veggenti predicono un triste destino per le Due Terre." }
    { group:294, id:11, text: "Non puoi saltare in avanti quando stai creando la tua storia di famiglia. Prima di accedere al vecchio regno devi completare il periodo arcaico." }
    { group:294, id:12, text: "Medio regno" }
    { group:294, id:13, text: "Fin dal suo doloroso inizio, il Medio regno si dimostra un periodo di grandi opportunità per la scalata al potere della tua famiglia." }
    { group:294, id:14, text: "Il regno di mezzo, iniziato nel dolore, rivela nuove opportunità per la tua famiglia. Sotto la tua guida, l'Egitto troverà nuova gloria, potenza e molto altro ancora." }
    { group:294, id:15, text: "La storia di famiglia deve procedere in modo ordinato. Il regno di mezzo non può iniziare prima della fine del vecchio regno!" }
    { group:294, id:16, text: "Nuovo regno" }
    { group:294, id:17, text: "Un nuovo e feroce nemico, dotato di un'arma ingegnosa e fulminea, porta la fine del Medio regno. Dopo questa distruzione, l'Egitto è risorto." }
    { group:294, id:18, text: "Nuovi e strani nemici, con un'arma terribile e inarrestabile, segnano la fine del regno di mezzo nonché l'inizio del glorioso nuovo regno." }
    { group:294, id:19, text: "Non puoi allontanarti dal percorso della tua storia di famiglia! La tua famiglia non può passare al Nuovo Regno fino a quando non avrai terminato i periodi precedenti." }
    { group:294, id:20, text: "Valle dei Re" }
    { group:294, id:21, text: "Con lo sviluppo di una nuova necropoli nella Valle dei Re, la preparazione dei Faraoni per il loro viaggio nell'aldilà subisce una svolta." }
    { group:294, id:22, text: "Per quanto monumentali, le piramidi dei tuoi antenati si sono erose con il passare dei secoli, le camere funerarie sono state profanate e i tesori saccheggiati dai ladri (che certo subiranno la punizione degli dei per l'eternità!). Abbandonerai le piramidi e costruirai una nuova necropoli nella valle nascosta di fronte a Tebe, scavando nuove tombe tra le pareti di roccia e creando la Valle dei Re, lontano dalle grinfie dei ladri. O almeno così speri." }
    { group:294, id:23, text: "Nella tua storia di famiglia c'è un momento giusto per tutto. Non potrai costruire le magnifiche tombe della Valle dei Re fino a quando non avrai terminato gli splendori del Nuovo Regno." }
    { group:294, id:24, text: "Ramses II" }
    { group:294, id:25, text: "Ramses II conquista la più grande vittoria dell'Egitto e commemora la propria grandezza con incredibili monumenti." }
    { group:294, id:26, text: "Ramses II è il terzo Faraone della dinastia iniziata con suo nonno, Ramses I, un consigliere non di sangue reale che reclamò il trono quando Horemheb morì senza un erede. Devi ottenere ottimi risultati militari e costruire grandi monumenti che convincano i tuoi sudditi della tua divinità, incutere terrore nei tuoi nemici e lasciare testimonianza del nome e della gloria di Ramses il Grande a tutte le future generazioni." }
    { group:294, id:27, text: "La storia di famiglia deve essere seguita in modo ordinato. Non potrai governare come Ramses II fino a quando non avrai costruito le gloriose tombe nella Valle dei Re. Non puoi scegliere Ramses II finché la tua famiglia non ha completato la prima missione" }
    { group:294, id:28, text: "I Conquistatori" }
    { group:294, id:29, text: "Potenti guerrieri da terre lontane giungono per conquistare le ricchezze dell'Egitto. Dopo aver sventato questa minaccia e aver accolto la gloria di Alessandro, puoi raggiungere l'area \"Scegli una missione\" per riprovare l'intera campagna o una delle sue missioni." }
    { group:294, id:30, text: "L'Egitto ha molti vicini invidiosi che guardano alla fortuna del suo impero come un branco di iene radunato per assalire un leone. Riuscirai a creare e comandare le flotte e gli eserciti necessari per sconfiggere tali gravi minacce e difendere il delta del Nilo contro una serie di invasioni del Popolo del mare, Assiri e Persiani? L'Egitto conta su di te!" }
    { group:294, id:31, text: "Affrontando questa parte dello scenario, apriresti un vuoto nella tua storia di famiglia. Non puoi sconfiggere gli antichi conquistatori prima di aver vissuto nei panni di Ramses II." }
    { group:294, id:32, text: "Città di Cleopatra" }
    { group:294, id:33, text: "I Tolomei di Grecia ridanno gloria alla terra dei Faraoni e respingono la minaccia di Roma." }
    { group:294, id:34, text: "Alessandro Magno in persona ha scelto il luogo in cui sorgerà Alessandria, la città sul Mediterraneo che ora devi costruire. Dopo 300 anni di regno tolemaico, culminante con Cleopatra VII, Alessandria diventerà la più grande città del mondo, superiore persino a Roma in popolazione e ricchezza. Dovrai costruire il mausoleo di Alessandro, la grande biblioteca, il faro di Pharos e il Caesareum. Ma cosa faranno nel frattempo le potenti legioni romane? Verranno usate pro o contro l'Egitto di Cleopatra?" }
    { group:294, id:35, text: "La vita di Cleopatra non può essere aggiunta alla tua storia di famiglia prima che tu abbia sconfitto gli antichi conquistatori." }
    { group:294, id:36, text: "Inizia" }
    { group:294, id:37, text: "Gioca" }
    { group:294, id:38, text: "Missioni singole" }
    { group:294, id:39, text: "Campagne" }
    { group:294, id:40, text: "Puoi rigiocare le missioni solo se le hai già completate con successo." }
    { group:294, id:41, text: "Faraone" }
    { group:294, id:42, text: "La Regina del Nilo" }
    { group:295, id:0, text: "la festività solleva l'umore dei cittadini, la città dovrebbe indirne un'altra entro breve." }
    { group:295, id:1, text: "Sono passati un po' di mesi dall'ultima festività. Ora è il momento di indirne un'altra." }
    { group:295, id:2, text: "È un po' di tempo che non ci sono festività, la gente inizia a lamentarsi." }
    { group:295, id:3, text: "È passato più di un anno dall'ultima festività. La gente è annoiata e stanca." }
    { group:295, id:4, text: "Sono passati due anni dall'ultima festività. La gente ha davvero bisogno di una pausa." }
    { group:295, id:5, text: "Sono passati più di due anni dall'ultima festività! La gente si sente disperata." }
    { group:295, id:6, text: "La gente ricorda con nostalgia i 'bei tempi', quando le festività riuscivano a sollevare il morale." }
    { group:295, id:7, text: "È stata una festività incredibile! Occorre molto tempo per prepararne una simile." }
    { group:295, id:8, text: "I preparativi per le festività sono molto lunghi, forse è il caso di ordinarne una adesso." }
    { group:295, id:9, text: "La scorsa festività è stata indetta molto tempo fa, è il momento di prepararne un'altra." }
    { group:295, id:10, text: "la festività normale è quasi pronta. La gente anticipa i giorni di festa del mese prossimo." }
    { group:295, id:11, text: "I preparativi per la festività normale sono in corso. Mancano solo due mesi prima della grande festa." }
    { group:295, id:12, text: "I preparativi lunghi tre mesi per la festività normale inizieranno il mese prossimo." }
    { group:295, id:13, text: "Gli organizzatori stanno approvando i piani della festività normale che si terrà tra quattro mesi." }
    { group:295, id:14, text: "la festività normale sarà pronta tra cinque mesi. Gli organizzatori stanno valutando le offerte." }
    { group:295, id:15, text: "Gli organizzatori credono di riuscire a preparare la festività normale in sei mesi." }
    { group:295, id:16, text: "Gli organizzatori hanno promesso che la festività normale sarà pronta in sette mesi." }
    { group:295, id:17, text: "la festività normale non sarà pronta prima di otto mesi. L'organizzazione è appena all'inizio." }
    { group:295, id:18, text: "Gli organizzatori sono così occupati che la festività non sarà pronta prima di nove mesi." }
    { group:295, id:19, text: "Ancora una? Passeranno dieci mesi prima che siano pronti per un'altra festività normale." }
    { group:295, id:20, text: "la festività grandiosa è quasi pronta. La gente è molto eccitata all'idea delle prossime feste!" }
    { group:295, id:21, text: "I preparativi della festività grandiosa sono in corso e abbiamo due mesi prima che tutto sia pronto." }
    { group:295, id:22, text: "la festività grandiosa è in fase d'allestimento. Tra tre mesi avremo una festa memorabile." }
    { group:295, id:23, text: "Gli organizzatori si sono pronunciati: tra quattro mesi avremo una festa davvero grandiosa." }
    { group:295, id:24, text: "Giocolieri e attori si stanno esercitando: la festività grandiosa sarà pronta in cinque mesi." }
    { group:295, id:25, text: "Gli organizzatori confermano che la festività grandiosa sarà pronta tra sei mesi, come promesso." }
    { group:295, id:26, text: "Gli organizzatori stanno valutando varie ipotesi per la festività grandiosa prevista tra sette mesi." }
    { group:295, id:27, text: "Alcuni acrobati stanno studiando gli spettacoli per la festività grandiosa che si terrà tra otto mesi." }
    { group:295, id:28, text: "Dobbiamo preparare ancora molte cose, la festività grandiosa non sarà pronta prima di nove mesi." }
    { group:295, id:29, text: "Nessuno ha molto tempo da dedicare alla festività grandiosa, quindi non ci sarà prima di dieci mesi." }
    { group:295, id:30, text: "Gli organizzatori devono pianificare la festività grandiosa con undici mesi di anticipo." }
    { group:295, id:31, text: "la festività grandiosa è quasi pronta. Ancora un mese e ci sarà birra per tutti!" }
    { group:295, id:32, text: "Tra due mesi i preparativi per la festività grandiosa saranno finiti. Tutti non ne vedono l'ora!" }
    { group:295, id:33, text: "la festività grandiosa è in fase d'allestimento. La gente ha solo tre mesi per fare i preparativi." }
    { group:295, id:34, text: "la festività grandiosa è in preparazione, ma occorrono ancora quattro mesi!" }
    { group:295, id:35, text: "Gli organizzatori della festività grandiosa possono iniziare il prossimo mese e saranno pronti tra 5." }
    { group:295, id:36, text: "I giocolieri hanno molte sorprese ma le riveleranno solo durante la festività, tra sei mesi." }
    { group:295, id:37, text: "I musicisti stanno scrivendo nuove canzoni per la festività grandiosa, tra sette mesi." }
    { group:295, id:38, text: "I danzatori provano nuovi passi, vogliono essere pronti per la festività grandiosa, tra otto mesi." }
    { group:295, id:39, text: "Gli organizzatori hanno pensato a nuovi spettacoli da inserire nella festività grandiosa, tra nove mesi." }
    { group:295, id:40, text: "Gli organizzatori stanno facendo gli straordinari, la festività grandiosa sarà pronta tra dieci mesi." }
    { group:295, id:41, text: "Gli organizzatori credono di riuscire a preparare la festività grandiosa in undici mesi." }
    { group:295, id:42, text: "Gli organizzatori sono costretti a pianificare la festività grandiosa con un anno di anticipo." }
    { group:296, id:0, text: "Case Eterne in Egitto" }
    { group:296, id:1, text: "Missione" }
    { group:296, id:2, text: "Migliore Famiglia" }
    { group:296, id:3, text: "Livello di difficoltà" }
    { group:296, id:4, text: "Punteggio" }
    { group:296, id:5, text: "Casa di" }
    { group:296, id:6, text: "Non ci sono migliori punteggi" }
    { group:297, id:0, text: "I primi antenati della tua famiglia si misero in risalto apprendendo i rudimenti del comando." }
    { group:297, id:1, text: "Dopo aver trasferito la famiglia a Thinis, i tuoi antenati aiutarono la confederazione thinita a unificare l'alto e il basso Egitto." }
    { group:297, id:2, text: "I miti familiari dicono che il tuo clan scoprì nuove importanti tecniche e imparò a sfruttare l'inondazione del Nilo." }
    { group:297, id:3, text: "Quando Narmer nominò un tuo antenato architetto reale, la tua famiglia entrò per la prima volta negli annali storici." }
    { group:297, id:4, text: "La tua famiglia ebbe un ruolo importante nella fondazione della prima capitale egizia e nella costruzione della mastaba." }
    { group:297, id:5, text: "Secondo la leggenda, la tua famiglia fondò le miniere di rame a Timna, rivelatesi fondamentali, quando il Faraone Den riuscì a tenere a bada i Beduini." }
    { group:297, id:6, text: "Per la prima volta, uno dei tuoi antenati preferì le acque alla terraferma e imparò le arti marinare, comprese quelle del combattimento navale." }
    { group:297, id:7, text: "Per la prima volta, uno dei tuoi antenati preferì le acque alla terraferma e imparò le arti marinare in tempo di pace." }
    { group:297, id:8, text: "La tua gente fondò un importante avamposto militare lontano dalla civiltà, aprendo una via commerciale verso l'Africa, tuttora usata." }
    { group:297, id:9, text: "Per il piacere del Faraone Nebka, la tua famiglia estrasse i ricchi minerali presso la prima cataratta, senza i quali era impossibile costruire molte tombe e quindi preparare i nobili alla vita dell'aldilà." }
    { group:297, id:10, text: "I tuoi antenati riuscirono a realizzare la visione del Consigliere Imhotep e costruirono la prima piramide di pietra per ospitare la mummia di Djoser." }
    { group:297, id:11, text: "I tuoi valorosi antenati strapparono al Sinai rame e molte gemme di valore, nonostante i suoi feroci custodi." }
    { group:297, id:12, text: "La gloria del tuo clan è testimoniata dalla tomba di famiglia a Meidum, che tuttora ricorda a tutti il valore della tua stirpe." }
    { group:297, id:13, text: "La fortezza eretta a Buhen e l'impegno con cui la tua gente ha sconfitto il nemico, portarono la potenza egizia alla seconda cataratta, nella terra strappata ai nubiani." }
    { group:297, id:14, text: "Mentre altri si preoccupavano di estendere i confini del Regno, il tuo antenato costruì una tomba magnifica, la piramide sghemba di Snofru." }
    { group:297, id:15, text: "Mentre i veggenti già chiamavano tiranno il figlio di Snofru, i tuoi antenati completavano la prima vera piramide d'Egitto, per conservare la mummia del Faraone." }
    { group:297, id:16, text: "Nonostante la tirannia di Khufu, il tuo antenato servì fedelmente il governatore locale e difese i confini egizi dagli invasori kushiti." }
    { group:297, id:17, text: "Al sicuro dalla minaccia kushita, il tuo progenitore aprì delle cave a Tura per soddisfare l'insaziabile desiderio di calcare del Faraone Khufu." }
    { group:297, id:18, text: "Il tuo antenato diventò Nomarca sotto Khufu e Khafra e, con grande forza di volontà, eresse la grande piramide e la sfinge guardiana." }
    { group:297, id:19, text: "Il Faraone dichiarò Ra supremo tra gli dei e incaricò il tuo antenato di estendere il culto del sole nell'ostile deserto occidentale, ai confini del Regno." }
    { group:297, id:20, text: "Il Faraone Userkaf dichiarò Ra supremo tra gli dei e ordinò al tuo antenato di costruire il più grande tempio del sole sul delta, una regione priva di materiale da costruzione." }
    { group:297, id:21, text: "Mentre i nemici dell'Egitto dilagavano come vermi in un cadavere, la tua famiglia giunse al titolo di cancelliere e impedì che gli avversari del Regno avessero la meglio." }
    { group:297, id:22, text: "Mentre i nemici dell'Egitto dilagavano come vermi in un cadavere, la tua famiglia giunse al titolo di cancelliere e dimostrò di saper governare con saggezza mentre tutto il resto crollava." }
    { group:297, id:23, text: "I tuoi antenati si dichiararono fedeli ai legittimi Inyotef e riportarono Thinis all gloria di un tempo, nonostante gli attacchi degli eserciti ribelli." }
    { group:297, id:24, text: "Due fazioni erano in lotta per conquistare l'Egitto, anche se il suo ventre era vuoto. Il tuo antenato salvò molti dalla carestia e fornì il massimo del supporto alla legittima dinastia." }
    { group:297, id:25, text: "Mentuhotep nominò la tua famiglia consigliere e si basò molto sul loro aiuto per schiacciare definitivamente i ribelli ed evitare un'ulteriore divisione del Regno." }
    { group:297, id:26, text: "Mentuhotep nominò la tua famiglia Consigliere e la sua riunificazione deve molto alla splendida città che la tua gente costruì dal nulla." }
    { group:297, id:27, text: "Finalmente, un membro della tua famiglia compì il suo destino e divenne Faraone. Il tuo clan diventò una dinastia reale, costruì una nuova capitale e convinse l'opposizione con grandi opere." }
    { group:297, id:28, text: "Il tuo divino antenato sconfisse i nostri antichi nemici nella Nubia settentrionale, si fece rispettare dai kushiti e fondò un porto importantissimo sul Mar Rosso." }
    { group:297, id:29, text: "Il porto sul Mar Rosso costruito dal tuo antenato portò moltissima ricchezza alla tua gente e la tomba della tua famiglia sopravviverà al passare dei secoli." }
    { group:297, id:30, text: "Il tuo illustre antenato, che ora riposa nel suo favoloso mausoleo, sconfisse la flotta nubiana e conquistò una loro splendida città." }
    { group:297, id:31, text: "La città di Bubastis è tuttora il gioiello della corona dei due regni. Il tuo antenato costruì una città che ancora oggi è l'orgoglio di tutto l'Egitto." }
    { group:297, id:32, text: "Trasformando i carri degli hyksos in una nuova arma e utilizzandola contro tutti i nemici del Regno, il tuo antenato si guadagnò un posto imperituro nella storia d'Egitto." }
    { group:297, id:33, text: "La tua famiglia è sempre stata benedetta dalla saggezza. Il tuo antenato riuscì a ispirare i suoi generali, convincendoli a opere sovrumane." }
    { group:297, id:34, text: "Hai fondato il nuovo regno, hai reso sicure le foreste di Byblos e ti sei fatto rispettare dai feroci Ittiti e dal misterioso Popolo del mare." }
    { group:297, id:35, text: "Hai arricchito tutte le città del Regno e le hai protette contro nemici vecchi e nuovi." }
    { group:297, id:36, text: "Il tuo Regno è stato il più glorioso della storia d'Egitto. I nostri confini abbracciano il mondo conosciuto e la nostra gente vive nel lusso." }
    { group:297, id:37, text: "Dopo aver sconfitto tutti i nemici e aver portato grande prosperità al Regno, hai costruito una piramide la cui imponenza supera quella del leggendario Khufu." }
    { group:297, id:38, text: "Con la fondazione di Deir el-Medina, i Faraoni possono riposare per l'eternità, senza paura di essere disturbati dai temuti predoni di tombe." }
    { group:297, id:39, text: "In poco tempo, la tomba di Tutankamen venne costruita e dotata di tantissime provviste per i morti." }
    { group:297, id:40, text: "La tomba di Seth I è una vera meraviglia, resa ancora più notevole dal numero di predoni di tombe che dovettero essere soppressi per costruirla. Peccato che gli occhi del mondo non potranno ammirare la sua eterna bellezza." }
    { group:297, id:41, text: "Il porto di Sumur ora brulica di attività per soddisfare le richieste di legname e altri beni preziosi" }
    { group:297, id:42, text: "L'Egitto ottenne la sua più grande vittoria nella battaglia di Qadesh, riaffermando il suo dominio sulla terra di Amurra. La minaccia degli ittiti venne debellata una volta per tutte." }
    { group:297, id:43, text: "I Colossi di Abu Simbel testimonieranno per sempre il potere e la gloria d'Egitto" }
    { group:297, id:44, text: "Le spoglie mortali di Ramses II ora riposano nella sua splendida tomba. Nella sua nuova vita eterna continuerà certamente a guidare i passi dell'Egitto verso una sempre maggiore gloria." }
    { group:297, id:45, text: "I pericolosi briganti venuti dal mare, che cercarono incautamente di conquistare le terre d'Egitto, vennero respinti con la forza. I confini egiziani erano tornati nuovamente sicuri." }
    { group:297, id:46, text: "Gli avamposti fortificati sparsi per l'Egitto resistettero a numerose ondate di attacchi assiri, impedendo ai vili nemici di penetrare ulteriormente nelle Due Terre." }
    { group:297, id:47, text: "La gente di Achoris parlò a lungo di come venne decimata la flotta persiana e distrutta la fanteria nemica. Fu un duro colpo per i sogni di conquista persiani." }
    { group:297, id:48, text: "In soli dieci anni, Alessandria si espanse a macchia d'olio, trasformandosi in una vivacissima metropoli mentre prima era poco più di un villaggio di pescatori." }
    { group:297, id:49, text: "Ad Alessandria si costruì la grande biblioteca e il Faro di Pharos, aumentando la sua importanza in tutto il mondo." }
    { group:297, id:50, text: "Le legioni romane di Mitridate sottomisero il fratello ribelle di Cleopatra, Tolomeo XIII, in una grande battaglia lungo le rive del lago Mariut." }
    { group:297, id:51, text: "Il glorioso sviluppo di Alessandria proseguì quando al suo gruppo di magnifici monumenti venne aggiunto il Caesareum e un altro tempio mortuario." }
    { group:297, id:52, text: "La forza combinata della flotta egizia e delle forze di Antonio abbatté Ottaviano. L'Egitto e Roma si unirono alla pari per regnare sul mondo conosciuto." }
    { group:298, id:0, text: "Livello finale di cultura" }
    { group:298, id:1, text: "Livello finale di prosperità" }
    { group:298, id:2, text: "Livello monumenti finale" }
    { group:298, id:3, text: "Livello finale del regno" }
    { group:298, id:4, text: "Popolazione finale" }
    { group:298, id:5, text: "Finanze cittadine finali" }
    { group:298, id:6, text: "Missione completata in" }
    { group:298, id:7, text: "Livello di difficoltá:" }
    { group:298, id:8, text: "Punteggio finale:" }
    { group:298, id:9, text: "anni" }
    { group:299, id:0, text: "Risultato diretto" }
    { group:299, id:1, text: "Incidentale" }
    { group:299, id:2, text: "Nonostante" }
    { group:299, id:3, text: "Nessun motivo" }
    { group:299, id:4, text: "Continuo/Ciclico" }
    { group:299, id:5, text: "Come richiesto" }
    { group:299, id:6, text: "Automatico" }
    { group:299, id:7, text: "Diretto" }
    { group:299, id:8, text: "Incidentale" }
    { group:299, id:9, text: "Nonostante" }
    { group:299, id:10, text: "Nessuno" }
    { group:299, id:11, text: "Ciclo" }
    { group:299, id:12, text: "Richiesto" }
    { group:299, id:13, text: "Auto" }
    { group:304, id:0, text: "Avanti" }
    { group:304, id:1, text: "Indietro" }
    { group:305, id:0, text: "La tua famiglia non ha mai affrontato questa sfida. Per vedere gli obiettivi di missione, clicca sul pulsante sottostante." }
    { group:306, id:0, text: "Fattoria di henna" }
    { group:306, id:1, text: "La miglior henna viene coltivata qui e inviata alla fabbrica di pittura, che realizza le pregiate vernici usate per decorare le pareti delle tombe." }
    { group:306, id:2, text: "Produzione completa: " }
    { group:306, id:3, text: " " }
    { group:306, id:4, text: "Il tuo supervisore commerciale ha stabilito che la produzione di henna dovrebbe essere fermata." }
    { group:306, id:5, text: "Senza lavoratori, questa fattoria non può produrre henna." }
    { group:306, id:6, text: "Questa fattoria ha tutti i lavoratori che occorrono. Sono nei campi a badare alle piante." }
    { group:306, id:7, text: "Questa fattoria potrebbe produrre più henna se avesse più lavoratori." }
    { group:306, id:8, text: "Questa fattoria non ha abbastanza lavoratori per badare a un intero campo di henna." }
    { group:306, id:9, text: "Qui lavorano pochissime persone. Il raccolto di henna ne soffrirà." }
    { group:306, id:10, text: "Questa fattoria è in gran parte abbandonata. Servono più lavoratori per aumentare la produzione di henna." }
    { group:306, id:11, text: "Le locuste hanno divorato tutto ciò che cresceva qui. La terrad ha bisogno di tempo per riprendersi." }
    { group:306, id:12, text: "Terra fertile: " }
    { group:306, id:13, text: " " }
    { group:306, id:14, text: "Il prossimo raccolto di henna è a" }
    { group:307, id:0, text: "0,0,0,0   // missione 0" }
    { group:307, id:1, text: "0,0,0,0" }
    { group:307, id:2, text: "0,0,0,0" }
    { group:307, id:3, text: "0,0,0,0   // Nekhen: prima missione con stipendio personale" }
    { group:307, id:4, text: "1,0,0,0" }
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
    { group:307, id:37, text: "1,0,0,0   // Ultima missione del gioco originale" }
    { group:307, id:38, text: "0,0,0,1   // Thutmose" }
    { group:307, id:39, text: "0,0,V,1   // Tutankhamun" }
    { group:307, id:40, text: "0,0,V,1   // Sethos" }
    { group:307, id:41, text: "0,0,0,0   // Sumer" }
    { group:307, id:42, text: "1,1,0,0   // Qadesh" }
    { group:307, id:43, text: "1,1,0,0   // Abu Simbel" }
    { group:307, id:44, text: "1,1,V,0   // Ramses nella Valle" }
    { group:307, id:45, text: "0,0,0,0   // Pi-Yer" }
    { group:307, id:46, text: "0,0,0,0   // Migdol" }
    { group:307, id:47, text: "0,0,0,0   // Tanis" }
    { group:307, id:48, text: "0,0,0,1   // Alessandria (di Alessandro)" }
    { group:307, id:49, text: "1,1,A,1   // Alessandria (di Tolomeo)" }
    { group:307, id:50, text: "0,0,0,0   // Cesare e Cleopatra" }
    { group:307, id:51, text: "1,1,A,0   // Il retaggio di Cleopatra" }
    { group:307, id:52, text: "1,1,0,0   // Actium" }
    { group:308, id:0, text: "Zoo" }
    { group:308, id:1, text: "Allo zoo, i cittadini possono ammirare animali esotici provenienti da zone più o meno lontane." }
    { group:308, id:2, text: "Questo zoo ha i suoi guardiani, ma ha bisogno di carne perché gli animali ci possano vivere." }
    { group:308, id:3, text: "Questo zoo dispone di lavoratori, ma senza paglia non può ospitare animali." }
    { group:308, id:4, text: "La gente ha paura di visitare uno zoo senza guardiani. Fino a quando lo zoo non troverà nuovi lavoratori, non apporterà alcun beneficio." }
    { group:308, id:5, text: "Senza animali, lo zoo è soltanto una serie di gabbie vuote." }
    { group:308, id:6, text: "Selvaggina:" }
    { group:308, id:7, text: "Paglia:" }
    { group:309, id:0, text: "Il pericolo di malattie è così grave che anche le iene sono preoccupate." }
    { group:309, id:1, text: "Come nutrire gli animali se non c'è cibo nemmeno per noi?" }
    { group:309, id:2, text: "Le nostre difese sono deboli. Dovrei usare gli ippopotami come soldati?" }
    { group:309, id:3, text: "Persino gli elefanti non ricordano una simile mancanza di lavoratori." }
    { group:309, id:4, text: "Quando gli dei si arrabbiano, nessuno vorrebbe avere un collo da giraffa!" }
    { group:309, id:5, text: "Il Faraone è infelice. Che gli animali dello zoo non diventino doni esotici!" }
    { group:309, id:6, text: "Acchiappare un lavoro in città è più difficile che catturare un leone!" }
    { group:309, id:7, text: "I divertimenti in città sono peggio di una discarica." }
    { group:309, id:8, text: "Vivere qui è meglio che dormire in una tana di leoni." }
    { group:309, id:9, text: "Vivere qui mi rende felice come un ippopotamo coperto di fango." }
    { group:310, id:0, text: "Messaggi popup" }
    { group:310, id:1, text: "I mess. scelti appaiono in cima allo schermo" }
    { group:310, id:2, text: "Messaggi straripamento" }
    { group:310, id:3, text: "Messaggi popolazione" }
    { group:310, id:4, text: "Soddisfazione possibile" }
    { group:310, id:5, text: "La tua fama aumenta" }
    { group:310, id:6, text: "Festività" }
    { group:310, id:7, text: "Benedizioni minori" }
    { group:310, id:8, text: "Cambiamento di prezzo" }
    { group:310, id:9, text: "Livello commerciale cambia" }
    { group:310, id:10, text: "Cambiamento di stipendio" }
    { group:310, id:11, text: "La malattia colpisce" }
    { group:310, id:12, text: "Malaria" }
    { group:310, id:13, text: "Impiegati richiesti" }
    { group:310, id:14, text: "OK" }
    { group:310, id:15, text: "Annulla" }
    { group:311, id:0, text: "Selezionare era monumenti" }
    { group:311, id:1, text: "Piramidi" }
    { group:311, id:2, text: "Valle dei Re" }
    { group:311, id:3, text: "Alessandria" }
    { group:311, id:4, text: "Abu Simbel" }
    { group:312, id:0, text: "Gilda degli artigiani" }
    { group:312, id:1, text: "Gli artigiani si radunano qui per preparare gli stucchi dall'argilla e per mescolare le vernici prima di iniziare a decorare le tombe." }
    { group:312, id:2, text: "In questa gilda non ci sono lavoratori, dunque non possono addestrare gli artigiani." }
    { group:312, id:3, text: "Questa gilda ospita un completo gruppo di artigiani che si accingono a decorare gli interni delle tombe." }
    { group:312, id:4, text: "A questa gilda mancano uno o due artigiani. La decorazione delle tombe è leggermente rallentata." }
    { group:312, id:5, text: "Questa gilda sta facendo il possibile per inviare degli artigiani alla tomba e ne addestra meno di quanti potrebbe." }
    { group:312, id:6, text: "Questa gilda ha bisogno di molti più lavoratori. I pochi artigiani che vi lavorano stanno facendo il possibile per decorare la tomba, ma gli serve aiuto." }
    { group:312, id:7, text: "La vernice delle tombe ha parecchio tempo per asciugarsi. Se questa gilda non troverà altri lavoratori, potrebbe volerci un'eternità per decorare la tomba." }
    { group:312, id:8, text: "Gli artigiani devono decorare una tomba, ma sarà difficile riuscirci senza la vernice, fornita da una fabbrica di pittura o un deposito merci." }
    { group:312, id:9, text: "La gilda non invierà altri artigiani alla tomba fino a quando non riceverà argilla." }
    { group:312, id:10, text: "Pittura:" }
    { group:312, id:11, text: "Argilla:" }
    { group:313, id:0, text: "Fabbrica di pittura" }
    { group:313, id:1, text: "Qui, l'henna viene macinata e trasformata in vernice, che gli artigiani usano per decorare sontuosamente le pareti delle tombe reali." }
    { group:313, id:2, text: "Produzione completa: " }
    { group:313, id:3, text: " " }
    { group:313, id:4, text: "Il tuo supervisore commerciale ha fermato la produzione di vernice." }
    { group:313, id:5, text: "Questa fabbrica di pittura è rimasta senza manodopera, dunque non può più produrre vernice." }
    { group:313, id:6, text: "Grazie al pieno complemento di lavoratori, questa fabbrica di pittura produce vernice con la massima efficienza possibile." }
    { group:313, id:7, text: "In questa fabbrica di pittura non c'è molta manodopera, dunque la produzione di vernice ne risente." }
    { group:313, id:8, text: "Questa fabbrica di pittura ha pochi lavoratori e produce con più lentezza di quanto dovrebbe" }
    { group:313, id:9, text: "Questa fabbrica di pittura richiede molti più lavoratori. La produzione di vernice è ai minimi termini." }
    { group:313, id:10, text: "In questa fabbrica di pittura lavorano solo poche persone. Questa ridotta forza lavoro stenta a garantire una seppur minima produzione di vernice." }
    { group:313, id:11, text: "Questo esercizio ha bisogno di ricevere henna da una fattoria o un deposito merci per produrre vernice." }
    { group:313, id:12, text: "Henna:" }
    { group:314, id:0, text: "Fabbrica di lampade" }
    { group:314, id:1, text: "Qui, i lavoratori riempiono appositi recipienti di olio per produrre lampade." }
    { group:314, id:2, text: "Produzione completa: " }
    { group:314, id:3, text: " " }
    { group:314, id:4, text: "Il tuo supervisore commerciale ha fermato la produzione di lampade." }
    { group:314, id:5, text: "Questa fabbrica di lampade non produce nulla a causa dell'assenza di manodopera." }
    { group:314, id:6, text: "Grazie al pieno complemento di manodopera, questa fabbrica di lampade non fa alcuna fatica a produrre tante lampade." }
    { group:314, id:7, text: "Questa fabbrica di lampade ha qualche posto vacante, la produzione è un po' rallentata" }
    { group:314, id:8, text: "In questo esercizio lavora poca gente: la produzione di lampade è scarsa." }
    { group:314, id:9, text: "Questa fabbrica di lampade ha bisogno di molti altri impiegati. Il poco personale che c'è fa il possibile, ma la produzione di lampade è rallentata notevolmente." }
    { group:314, id:10, text: "Questa fabbrica di pittura produce una modestissima quantità di lampade. Per aumentare la produzione ha bisogno di molti altri lavoratori." }
    { group:314, id:11, text: "Questa fabbrica richiede forniture d'olio dai depositi merci" }
    { group:314, id:12, text: "Questa fabbrica di lampade richiede forniture di vasellame, dai depositi merci o dai vasai" }
    { group:314, id:13, text: "Olio:" }
    { group:314, id:14, text: "Vasell.:" }
]
