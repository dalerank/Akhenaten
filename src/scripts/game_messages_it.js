log_info("akhenaten: messages config started")

game_messages_it {
    message_potter_history {
        id: 1,

        size [30, 28]
        title { text: "Vasaio" }
        advisor: ADVISOR_TRADE
        content {
            text: "I vasai hanno bisogno di una fornitura di argilla per lavorare. Alcune città possono produrre argilla autonomamente, costruendo delle @92cave&d'argilla. Altre, invece, devono importarla da un'altra città (clicca @47qui per ulteriori informazioni sul commercio ). @PI carrettieri portano l'argilla dalle cave ai vasai, se presenti in città, altrimenti ai @4depositi&merci. Il vasaio conserva sempre dell'argilla nel suo magazzino privato, così da poter lavorare almeno per un po' anche se altre forniture d'argilla dovessero giungere in ritardo. @PI vasai richiedono l'accesso a una strada e manodopera. La produzione è maggiore se dispongono di tutti gli addetti che richiedono, ma saranno comunque operativi (anche se con efficienza ridotta) anche con un numero minimo di addetti. Se il vasaio sta producendo vasi, lo vedrai al lavoro. I carrettieri impiegati dal vasaio portano i prodotti finiti ai depositi merci o alla @473fabbrica&di&lampade (che richiede olio e vasellame per produrre lampade). @PIl vasellame è un bene importante per la città. Le @56case richiedono i vasi per evolvere a livelli superiori, quindi la scorta di vasi deve essere continuamente rifornita per evitare che le abitazioni, invece, devolvano. La domanda di vasi è sempre presente: le case devono sostituire i vasi rotti o usurati. Vedi i @2bazar per ulteriori informazioni su come portare i prodotti presso le case dei cittadini. @PIl vasellame è fondamentale anche per costruire le @478Tombe&Reali. Quando una Fabbrica di lampade riempie d'olio i vasi, li trasforma in potenti lampade che illuminano il cammino di chi lavora nelle tombe. @PI vasi possono essere anche importati o esportati. Vedi il @47commercio per ulteriori informazioni su come aprire le vie commerciali. Se la tua città commercia vasellame, considera prima di tutto la domanda dei tuoi cittadini. Il tuo @24supervisore&commerciale sa quanti vasi devono essere tenuti come scorta per l'uso cittadino nei depositi merci; puoi anche delegare le operazioni al supervisore stesso.  @PLa gente non vuole vivere vicino a una rumorosa e polverosa fabbrica di vasi; infatti, i suoi effetti sulla desiderabilità della zona sono negativi. @L@LPer ulteriori informazioni sul vasellame dell'antico Egitto, clicca @198qui."
        }
    }

    message_bazaar_history {
        id: 2,

        size [30, 28]
        title { text: "Bazar" }
        content {
            text: "Senza i bazar, la gente non potrebbe avere accesso al cibo e prodotti conservati nei @3granai e @4depositi&merci. Solo i bazar possono distribuire le merci nelle case dei cittadini. @PPer funzionare al meglio, i bazar richiedono l'accesso a una strada e personale al completo. Operano anche con personale ridotto, ma la sua efficienza è molto inferiore. @POgni bazar impiega due compratori (responsabili degli acquisti), uno per comprare il cibo dai granai, l'altro per acquistare i prodotti dai depositi merci. Ogni compratore è specializzato: il compratore del cibo non può procurare i prodotti dai depositi merci e quello dei prodotti non può accedere ai granai. Entrambi, però, possono comprare più prodotti per volta. Ad esempio, un compratore che si reca al granaio può acquistare grano e melograni. Non può, comunque, comprare grano e vasi, dato che i vasi non sono conservati nei granai.  @PQuando un compratore trova la merce che gli occorre, i suoi sottoposti lo aiutano a trasportarla fino al bazar. @PI compratori dei bazar sono @42'passanti&con&meta'. Essi passano la giornata girando per la città fra bazar, granai e depositi merci. Per ogni andata è obbligatorio un ritorno e non tratteranno affari con più di tre fornitori entro la loro portata. Se ne scoprite uno fermo da qualche parte, quando invece dovrebbe lavorare, probabilmente il suo tragitto è troppo lungo oppure deve trattare con troppi fornitori.  @PL'altro impiegato del bazar, il venditore del bazar, prende i prodotti incamerati dai compratori e li distribuisce nel quartiere. Quando un venditore passa entro due spazi da un'abitazione, egli la rifornisce dei prodotti richiesti, se ne ha con sé. Inoltre, scopre quali sono i prodotti richiesti dai clienti e riporta gli ordini al compratore in modo che li procuri. La priorità principale è rifornire le case con i prodotti che le impediscano di devolvere (vedi la sezione @56desiderabilità&delle&case). Quando tali bisogni principali sono soddisfatti, le case cercano di ottenere altri prodotti che consentano, invece, lo sviluppo. @PIl venditore dei bazar è, invece, un 'passante senza meta'. Il suo lavoro è quello di girare nel quartiere e servire i suoi clienti, senza una destinazione specifica. Se una certa parte di zona residenziale non riceve i prodotti, osserva il percorso dei venditori. Essi non seguono un percorso predefinito. Ogni volta che incontrano un incrocio, devono decidere quale direzione prendere e difficilmente sarà sempre la stessa. Pianifica la disposizione delle strade con molta attenzione e usa i @358blocchi&stradali per guidare i venditori di bazar. I bazar più evoluti (contraddistinti da un edificio al posto di una tenda) inviano due addetti alle consegne invece di uno solo.  @PLe richieste di beni basilari, come cibo e vasellame, devono essere soddisfatte prima che possa crescere la domanda di altri prodotti, come birra o tela. I compratori dei bazar ignoreranno i depositi merci stracolmi di tela, se i cittadini hanno un bisogno disperato di vasi. È quindi molto importante mantenere la fornitura di prodotti costante. Ricorda che quando le case si evolvono, normalmente ospitano più persone e quindi hanno bisogno di più prodotti. A volte, dovrai aggiungere altri bazar per mantenere il quartiere ben rifornito. Clicca con il pulsante destro del mouse su una casa per sapere quali sono le richieste dei cittadini in quel dato momento. @PPer essere certi che i cittadini ottengano il cibo e i prodotti richiesti, costruisci granai e depositi merci vicino ai bazar. Usa gli ordini speciali dei granai e depositi merci per fare in modo che contengano i prodotti e il cibo richiesto dai bazar. @PSe vuoi avere maggiore controllo su un bazar, clicca sul pulsante Ordini speciali per vedere quali sono i prodotti che può contenere. Clicca su un prodotto per ordinare al bazar di comprarlo o meno. @PAi cittadini fa sicuramente piacere vivere nei pressi di un bazar, ma non troppo vicino. Sono luoghi rumorosi, spesso ricettacoli di personaggi non desiderati; inoltre, a volte, emanano cattivo odore. @L@LPer avere un'idea dei colori, suoni e odori dei bazar dell'antico Egitto, clicca @199qui."
        }
    }

    message_building_granary {
        id: 3,

        size [30, 28]
        title { text: "Granaio" }
        content {
            text: "I granai conservano il cibo per i cittadini. I @2compratori&dei&bazar  prendono il cibo dai granai e lo distribuiscono alla popolazione. @PI granai richiedono l'accesso a una strada e manodopera. Puoi sapere cosa  contiene un granaio osservando le aperture di riempimento. Clicca su un granaio  con il pulsante destro del mouse per sapere esattamente la quantità di cibo  contenuta per ciascun tipo. @PLe @45fattorie&di&cibo, i @84moli&da&pesca, gli @360allevamenti&di&bestiame e  i @359casotti&da&caccia impiegano addetti alle consegne per portare i loro  prodotti ai granai. In genere, è bene che i granai siano vicini ai produttori di  cibo. Se un addetto alle consegne deve camminare a lungo e, nel frattempo, il  suo datore di lavoro finisce un altro lotto di produzione prima che sia  ritornato, la produzione si ferma fino al suo arrivo. @PSe tutti i granai sono pieni, gli addetti alle consegne aspetteranno finché  non si libera un po' di posto, a meno che tu non abbia ordinato ai  @4depositi&merci di accettare un tipo particolare di cibo. @PPer gestire il flusso di cibo in città, puoi usare gli ordini speciali per i  granai. Clicca su un granaio con il pulsante destro del mouse e poi su Ordini  speciali: compariranno, così, tutti i prodotti che il granaio può accettare.  Clicca su un prodotto per modificare la sua gestione da parte del granaio. Le  possibilità sono: @L@LAccetta tutto/Riempi granaio @LPer limitare la quantità accettata di un tipo di cibo, puoi usare il comando  'riempi'. Puoi ordinare al granaio di arrivare fino a 1/4, 1/2 o 3/4 della sua  capacità. Se non vuoi limitare la quantità accettata dal granaio, usa il comando  'accetta tutto'. Questa opzione è molto utile quando decidi di conservare pari  percentuali di ciascun tipo di cibo.   @L@LNon accettare  @LUsa questo comando per ordinare al granaio di non accettare più un certo tipo  di cibo. Il granaio non accetterà più consegne di quel cibo, ma i compratori dei  bazar e i carrettieri di altri granai continueranno ad attingere alle sue  riserve finché la scorta non sarà finita. Usa questa opzione per far sì che gli  addetti alle consegne saltino un granaio e ne cerchino uno più lontano, o per  impedire che un cibo da esportare venga consumato localmente.   @L@LProcura cibo @LSe un granaio ha una minima quantità di un tipo di cibo che vuoi invece  rendere disponibile, usa il comando 'procura cibo'. I carrettieri del granaio  cercheranno quel cibo presso altri granai o nei depositi merci fino alla  soddisfazione della richiesta. Puoi ordinare a un granaio di arrivare fino a  1/4, 1/2, 3/4 o a piena capacità. Con questa opzione, puoi fare in modo che i  granai più lontani dai fornitori di cibo possano comunque rifornire la loro  scorta. @L@LVuota cibo @LCon questo comando, i carrettieri di un granaio cercheranno di eliminare la  scorta di un tipo di cibo, cercando altri granai o depositi merci che possano  accettare le loro consegne. Se un granaio ha l'ordine di svuotare un tipo di  cibo, non accetterà consegne dello stesso tipo di cibo che cerca di spedire  altrove. Usa questo comando se hai deciso di demolire un granaio, o se vuoi  rimuovere un tipo di cibo lì contenuto. @L@LI granai sono polverosi, spesso infestati e, comunque, non graditi dai  vicini. I cittadini non sopportano di vivere nelle loro vicinanze. @L@LClicca @5qui per ulteriori informazioni sui granai dell'antico Egitto."
        }
    }

    message_building_storage_yard {
        id: 4,

        size [30, 28]
        title { text: "Deposito merci" }
        content {
            text: "I depositi merci conservano tutti i prodotti finiti e i materiali  grezzi in eccesso. Inoltre, conservano il cibo che ordini loro di incamerare  (vedi Ordini speciali, in seguito) e i prodotti importati o da esportare (vedi  la sezione @47commercio ).   @PPer funzionare, i depositi merci richiedono l'accesso a una strada e mano  d'opera. Essi funzionano alla massima efficienza quando il personale è al  completo. Possono funzionare anche con personale ridotto, ma potrebbero non  essere in grado di accettare alcune merci. @POgni deposito merci è diviso in otto sezioni e può conservare fino a otto tipi  diversi di prodotti. Ciascuna sezione accetta un solo tipo di prodotto, ma più  sezioni possono accettare lo stesso tipo. La quantità di prodotto conservabile  dipende dalle dimensioni di ciascun oggetto. Quelli più grandi possono essere  conservati in quantità minore. Ad esempio, la stessa sezione di un deposito  merci può conservare molti blocchi di pietra. @PGli edifici che richiedono l'accesso a un deposito merci sono molti. Le  @46industrie consegnano i loro prodotti al deposito più vicino e i bazar vi si  recano per recuperare i prodotti richiesti dai loro clienti. I depositi, a loro  volta, consegnano materiali grezzi o altre merci agli edifici più vicini. I  carrettieri dei depositi merci possono percorrere, con malavoglia, distanze  superiori, ma, mentre sono in viaggio, le industrie potrebbero fermarsi per  mancanza di materia prima. È dunque una buona idea costruire i depositi merci  vicino alle fabbriche che ne hanno bisogno. @PClicca su un deposito merci con il pulsante destro del mouse per sapere le  quantità esatte di prodotto conservate e se può accettarne ancora. Se un  deposito merci non può più accettare consegne di un tipo di prodotto, il  prodotto sarà mostrato in giallo. @PPuoi controllare il flusso di prodotti da e per i depositi merci utilizzando  gli ordini speciali. Quando clicchi sul pulsante Ordini speciali, compare un  pannello che elenca prodotti e merci al momento disponibili in città. A volte,  potrai leggere decine di prodotti. Utilizza i pulsanti di scorrimento in cima  alla tabella per vedere tutte le merci elencate. @PClicca su una voce per comunicare al deposito gli ordini, che possono essere: @L@LAccetta tutto/Riempi @LPer limitare la quantità di prodotto accettata da un deposito merci, usa il  comando Riempi. Puoi ordinare al deposito di conservare fino a 1/4, 1/2 o 3/4  della sua capacità. Se non vuoi limitare la quantità di un prodotto, ordina al  deposito di accettare tutto. Questa opzione è utile se desideri che un deposito  merci conservi una quantità pari di prodotti diversi o se vuoi che conservi cibo  per l'esportazione. @L@LNon accettare @LUsa questo comando per ordinare a un deposito merci di non accettare un tipo  di prodotto. Il deposito merci non accetterà più consegne di quel prodotto, ma i  compratori dei bazar, i mercanti e le industrie possono comunque utilizzare la  quantità già accumulata finché non si esaurisce. Usa questo comando per far sì  che gli addetti alle consegne saltino un deposito merci e ne visitino uno più  lontano. A meno che non ordini diversamente, i depositi merci non accettano  cibo, che invece è consegnato presso i granai.  @L@LProcura @LSe un deposito merci contiene una scorta troppo ridotta di un particolare  prodotto, usa il comando Procura. Il carrettiere del deposito merci cercherà il  prodotto in altri depositi fino a soddisfare la richiesta. Puoi ordinare al  deposito merci di arrivare fino a 1/4, 1/2, 3/4 o a piena capacità. Con questa  opzione, puoi assicurarti che i depositi merci situati in periferia abbiano  comunque una buona scorta di prodotti. @L@LVuota @LCon questo comando, il carrettiere del deposito merci cercherà di esaurire la  scorta di un determinato prodotto, cercando industrie e altri depositi merci che  accettino il prodotto. Usa questo comando se hai deciso di demolire un deposito  merci, o se vuoi eliminare un tipo di prodotto che conserva. @L@LI depositi merci sono fondamentali per distribuire i prodotti ai cittadini.  I @2bazar prendono i prodotti richiesti dai loro clienti dai depositi merci.  Inoltre, sono fondamentali per il commercio. I prodotti importati sono  conservati nei depositi, così come quelli da esportare, in attesa che i mercanti  di altre città vengano a prenderli. @L@LPer avere ulteriori informazioni sui depositi merci dell'antico Egitto,  clicca @6qui."
        }
    }

    message_granary_history_2 {
        id: 5

        size [30, 20]
        title { text: "Granaio" }
        content {
            text: "Dato che le coltivazioni erano praticamente impossibili durante lo  straripamento, i granai erano fondamentali per assicurare che gli Egizi  potessero disporre di cibo durante tutto l'arco dell'anno. I granai non  conservavano solo grano e altro cibo, ma anche farina macinata.  @L@LI granai si sono evoluti con il tempo. Nel periodo arcaico, i granai egizi  erano di forma conica sormontati da una cupola. Erano costruiti in legno o  mattoni; quelli più grandi avevano una scala che portava all'apertura per il  riempimento. Durante il Medio Regno, i granai erano di forma rettangolare e  avevano un tetto piatto sul quale erano praticati i fori per il riempimento,  proprio come quelli utilizzati per il nostro gioco. Un terzo tipo di granaio era  utilizzato solo per conservare i semi da utilizzare per la stagione di crescita.  Questi granai erano trapezoidali (ben diversi dai granai usati per conservare il  cibo), cosicché il grano per la semina non venisse mangiato per errore. @L@LLa maggior parte dei granai era gestita dal governo. I soldati, manovali e  altri lavoratori non agricoli prendevano il cibo da questi granai. Alcuni tra i  cittadini più ricchi avevano un granaio personale; anche alcuni contadini  avevano un piccolo granaio dove conservare la parte di raccolto che potevano  tenere per se stessi."
        }
    }

    message_storage_yard_history {
        id: 6

        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Deposito merci", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "Situati presso il Nilo e le principali vie commerciali, i depositi  merci conservavano le eccedenze di prodotti destinate al commercio. Dato che la  pioggia era scarsa, la maggior parte dei depositi dell'antico Egitto erano dei  cortili senza un tetto. Venivano controllati dagli scribi che ne mantenevano un  attento inventario."
        }
    }

    message_keyboard_commands {
        id: 7

        size [30, 28]
        title { text: "Comandi da tastiera" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Molti comandi di Faraon possono essere impartiti da tastiera. Questi  comandi sono: @L@LTasto    Comando @LA      Ordina alla nave da guerra selezionata @Pdi attaccare tutti i nemici. @L@LC      Mostra la tabella Rischi: Crimine,  @Pod ordina la carica alla compagnia di carri @Pda guerra selezionata. @L@LD      Mostra la tabella Rischi: Danni. @L@LE      Ordina alla nave da trasporto truppe @Pdi evitare i nemici. @L@LF      Mostra la tabella Rischi: Incendi, @Pod ordina alla compagnia selezionata di @Ptornare al forte. @L@LH      Nasconde le rupi. @L@POrdina al la nave selezionata di @Pmantenere la posizione. @L@LL      Centra la visuale su una diversa @Pcompagnia militare ogni volta che è @Ppremuto. @L@PSe una compagnia è selezionata, 'L' @Pimpartisce l'ordine 'mantieni @Pposizione in formazione aperta'. @L@LM     Quando selezioni un monumento dalla @Plista degli edifici, la sua immagine si @Paggancia al puntatore e mostra quanto @Pterreno occupa. Se tieni premuto il  @Ptasto 'M', l'impronta del monumento  @Primane sul posto; quindi, puoi spostare @P la visuale senza muovere l'impronta @Pdal luogo scelto. @PRilascia il tasto 'M' per tornare al @Pfunzionamento normale, oppure clicca per @Pposizionare il monumento nel luogo scelto. @L@P       Premendo il tasto 'M' quando è @Pselezionata una compagnia militare, si @Pimpartisce l'ordine 'attacco libero'. @L@LN      Ordina a una compagnia o nave da @Pguerra selezionata di attaccare i nemici @Pvicini. @L@LP      Mette in pausa il trascorrere del @Ptempo di gioco. Quando il gioco è in pausa, @Pnon puoi costruire. @L@LR      Quando posizioni una statua, una @Pguarnigione o un complesso di templi, il  @Ptasto 'R' ruota la struttura di un quarto  @Pdi giro in senso orario. Le statue @Pmostreranno stili diversi. @L@P       Quando è selezionata una compagnia, @Pil tasto 'R' ordina il cambiamento di @Porientamento. Il tasto 'R', inoltre, @Pordina a una nave da guerra o da @Ptrasporto di tornare al cantiere per @Ple riparazioni. @L@LT      Mostra la tabella Rischi: Problemi. @L@PQuando è selezionata una compagnia @Pmilitare, 'T' impartisce l'ordine @P'mantieni posizione in formazione @Pserrata'. @L@LW     Mostra la tabella idrico. @L@PSe è selezionata una nave da guerra o @Pda trasporto, 'W' ordina alla nave di @Ptornare al suo molo. @L@LX     Mostra lo schema delle tasse @L@LY     Mostra i rischi: la tabella Malaria @L@LZ     Mostra i rischi: la tabella Malattia @L@LBarra spaziatrice   Premi la barra spaziatrice @Pper passare dall'ultimo schermo selezionato @Palla normale visuale della città. @L@LESC    esce dal gioco. @L@LParentesi quadra aperta @Priduce la velocità di gioco del 10%. @L@LParentesi quadra chiusa @Paumenta la velocità di gioco del 10%. @L@LTAB   Supervisore del lavoro @L@L1     Supervisore militare @L@L2     Supervisore politico @L@L3     Supervisore dei livelli @L@L4     Supervisore commerciale @L@L5     Supervisore dei granai @L@L6     Supervisore sanitario @L@L7     Supervisore all'istruzione @L@L8     Supervisore all'intrattenimento @L@L9     Supervisore religioso @L@L0     Supervisore finanziario @L@Lè     Supervisore capo @L@L+     Supervisore dei monumenti @L@LCTRL+F1 @Pcrea un segnalibro F1 nella locazione attuale @L@LCTRL+F2 @Pcrea un segnalibro F2 nella locazione attuale @L@LCTRL+F3 @Pcrea un segnalibro F3 nella locazione attuale @L@LF1    Passa al segnalibro F1 @L@LF2    Passa al segnalibro F2 @L@LF3    Passa al segnalibro F3 @L@LF6    Passa alla visuale in finestra @L@LF7    Imposta risoluzione schermo a 640x480 @L@LF8    Imposta risoluzione schermo a 800x600 @L@LF9    Imposta risoluzione schermo a 1024x768"
        }
    }

    message_work_camp_history {
        id: 8
        
        size [30, 28]
        title { text: "Campo di lavoro" }
        content {
            text: "I contadini si radunano nei campi di lavoro per ottenere  l'assegnazione nelle @45fattorie&dei&campi&di&limo o presso i @370monumenti.  Durante la stagione della crescita, la maggior parte dei contadini è assegnata  alle coltivazioni. Durante lo straripamento, invece, lavorano alla costruzione  di monumenti. Se non c'è alcun monumento da costruire, durante lo straripamento  i contadini non hanno altro da fare che divertirsi nelle taverne senet. Se la  tua città ha molti campi di lavoro rispetto alla terra coltivabile, noterai una  netta distinzione di ritmo comandato dallo straripamento. @PI campi di lavoro richiedono l'accesso a una strada e manodopera. È meglio  posizionare tali campi nelle vicinanze di fattorie e monumenti, cosicché i  contadini non debbano camminare troppo. In verità, esiste un limite alla  distanza percorsa per raggiungere il posto di lavoro. Se i campi di lavoro sono  molti, i monumenti si costruiscono più in fretta, in quanto i lavoratori  disponibili durante la stagione della crescita saranno più numerosi. @PIl numero di fattorie supportate da un campo di lavoro dipende principalmente  dal circondario. Un campo di lavoro con personale al completo fornisce un  lavoratore alla settimana (quattro al mese). Questo lavoratore si reca presso il  più vicino campo di limo che necessita di manodopera; qui rimarrà per i  successivi sei mesi. @PQuando una fattoria è a metà del periodo lavorativo di un contadino, il campo  di lavoro si accorgerà che ha bisogno di un altro contadino se non vuole  interrompere la coltivazione - ricorda che la stagione della crescita dura nove  mesi nella maggior parte delle regioni. Se utilizzi un solo campo di lavoro per  rifornire molte fattorie, alcune potrebbero non ricevere contadini e altre  potrebbero avere difficoltà a mantenere un numero costante di lavoratori. @PCon uno o due campi di lavoro, puoi mantenere in funzione molte fattorie dei  campi di limo, ma molte non raggiungeranno il loro pieno potenziale e i  contadini saranno disponibili al lavoro nei cantieri solo durante lo  straripamento. @PIn pratica, un campo di lavoro può supportare da 2 a 4 fattorie senza  interrompere la coltivazione e fornendo anche qualche manovale per la  costruzione dei monumenti. Aggiungendo altri campi di lavoro, puoi distribuire  meglio il carico di lavoro e liberare più manovali per la costruzione dei  monumenti durante la stagione della crescita. @L@LPer ulteriori informazioni sulla vita lavorativa dell'antico Egitto, clicca  @155qui."
        }
    }

    message_frequently_asked_questions {
        id: 9
        
        size [30, 28]
        title { text: "Domande ricorrenti" }
        content {
            text: "Denaro @PD: Voglio che la mia città abbia un sacco di soldi. Qual è il modo migliore  per far traboccare i forzieri cittadini? @PR: Devi semplicemente fare in modo che la città incassi più di quanto spende.  @PAssicurati che quasi tutti i cittadini paghino le tasse. L'aumento delle tasse  contribuisce a riempire i forzieri, ma il denaro può non essere sufficiente a  bilanciare la diminuzione dell'@39umore&cittadino. Inoltre, apri delle @47vie  commerciali non appena ti è possibile ed esporta tutto ciò che puoi (consulta la  @32mappa &del&mondo per sapere quando la città si avvicina ai suoi limiti  annuali).  @PLa riduzione delle spese aiuta ad aumentare i profitti. Gli edifici costano  denaro, ovviamente, ma devi anche considerare le spese derivate dai salari e dai  servizi resi ai lavoratori. Costruire una città troppo in fretta può farti  indebitare a causa dei costi dei salari e delle spese ausiliarie. @L@PD: Perché la mia città non può riscuotere le tasse? @PR: Accertati di aver costruito il Palazzo. Le città non possono riscuotere le  tasse finché non è stato costruito il Palazzo. @L@PD: Sto lavorando duro, ma nessuno mi paga. Perché? @PR: Una lagnanza comune. In Faraon, non puoi ottenere un salario finché non hai  costruito la tua magione. @L@PD: Come faccio a pagare le tasse? E cosa succede se non le pago? @PR: Il tuo ministero del tesoro paga automaticamente le tue tasse alla fine  dell'anno, sempre che tu abbia fondi sufficienti. Assicurati che alla fine  dell'anno nei forzieri cittadini ci siano dei soldi. Se i tuoi forzieri sono  vuoti, non puoi pagare le tasse e il tuo @35livello&del&Regno diminuirà. Se non  puoi pagare le tasse per due anni di seguito, il tuo livello del Regno scenderà  ulteriormente e, se i tuoi debiti aumentano, la penale sarà molto severa. Leggi  la sezione che riguarda i @48debiti. @L@LAddetti alle consegne @PD: Uno dei miei depositi merci (o granai o fabbriche) crea degli addetti che  scompaiono non appena lasciano l'edificio. Cosa c'è che non va? @PR: Questi addetti non possono raggiungere la loro destinazione. La tua rete  stradale deve essere incompleta, oppure ci sono due strade adiacenti allo stesso  edificio, una che porta a una destinazione valida e l'altra no. Gli addetti che  non possono raggiungere una destinazione valida soffrono di frustrazione e  cessano di esistere. L'edificio per cui lavorano continua a inviare altri  addetti nella speranza che riescano dove i loro predecessori hanno fallito.  Leggi il file di Aiuto e cerca la parte che riguarda le @57strade, in  particolare la sezione che tratta di 'edifici su due strade'. @L@PD: Come può accadere che un edificio con un accesso valido ai lavoratori non  riesca a trovare degli impiegati? @PR: Probabilmente hai costruito un @358blocco stradale troppo vicino  all'edificio. Osserva l'edificio e assicurati che i suoi addetti escano sul lato  esatto del blocco stradale. A volte, infatti, gli edifici inviano i loro addetti  nella direzione sbagliata. Ciò è particolarmente fastidioso quando capita a chi  sta cercando lavoro, poiché l'edificio per cui lavorano crede che vi abbiano  accesso, mentre un blocco stradale li ferma. Ricostruisci il blocco stradale a  uno spazio di distanza. @L@LReligione @PD: Vorrei indire una festività, ma non mi è permesso. Perché? @PR: Ci sono molti motivi per cui non ti è permesso indire una festività. La tua  città ha una piazza delle festività? Niente piazza, niente festività. Hai già  celebrato due festività negli scorsi 12 mesi? Una città può celebrare solo due  festività in 1 anno. Se vuoi indire una festività grandiosa, assicurati di avere  in serbo birra a sufficienza. Infine, controlla le finanze cittadine. Se la  città non può permettersi di pagare una festività, non puoi indirla. @L@PD: Il dio patrono della mia città ce l'ha con me. Cosa devo fare per  appagarlo? @PR: Il dio patrono di una città richiede maggiori attenzioni delle divinità  locali. Assicurati di avere più templi e santuari dedicati a lui rispetto alle  altre divinità della città, oppure considera l'opportunità di costruire un  complesso di templi in suo onore. @L@LIntrattenimento @PD: Non riesco a trovare una zona adatta per la mia zona dedicata  all'intrattenimento. Quale può essere il problema? @PR: Con l'eccezione delle taverne Senet, le zone di divertimento devono essere  poste sugli incroci, sia a 'T' che a '+'. Inoltre, attorno all'incrocio ci deve  essere abbastanza spazio da alloggiare baracconi e palchi vari. @L@PD: In città ho molte zone di divertimento, ma nessun intrattenitore. Perché  non si esibiscono? @PR: Assicurati di avere dei centri di addestramento in città. Gli artisti  devono imparare il loro mestiere prima di poter intrattenere le masse. @L@PD: Perché la mia taverna Senet non funziona? @PR: Come stiamo a birra? Assicurati che la taverna Senet abbia birra da servire  ai suoi clienti. @L@LFattorie @PD: Perché le fattorie sui campi di limo non producono cibo? @PR: Assicurati che vicino alle fattorie ci sia un campo di lavoro. I campi  bonificati sono coltivati dai contadini che provengono dai campi di lavoro. @L@PD: Quante fattorie sui campi bonificati può supportare un solo campo di  lavoro? @PR: Dipende. Leggi la sezione @8campi&di&lavoro del file di Aiuto per una  completa spiegazione. @L@PD: Ho costruito un molo da pesca, ma non ha una barca. Perché? @PR: Le barche da pesca sono costruite dai cantieri navali. Assicurati di averne  uno attivo in città. @L@LStrutture distributive @PD: I bazar continuano a esaurire cibo e prodotti. Cosa posso fare per  mantenerli riforniti? @PR: Assicurati di costruire un granaio e un deposito merci vicino al bazar. Se  un compratore di un bazar deve camminare molto, il suo bazar è destinato a  terminare un prodotto mentre costui è in viaggio. Usa gli ordini speciali per i  granai e i depositi merci per assicurarti che siano sempre riforniti di tutte i  prodotti. @L@PD: Come posso sfruttare al meglio i depositi merci? @PR: Per ottenere il massimo dai @4depositi&merci, considera attentamente il  loro posizionamento in città e fai buon uso dei loro ordini speciali. I depositi  merci devono essere vicini agli edifici che richiedono i loro prodotti, come i  bazar, i moli, i cantieri dei monumenti e le industrie.  @L@LMonumenti @PD: Cosa posso fare per velocizzare la costruzione di un monumento? @PR: Costruisci vicino ai cantieri molti campi di lavoro, le gilde di  costruttori necessarie e i depositi merci che accettano solo i materiali da  costruzione. Se la costruzione di un monumento rallenta per una qualsiasi  ragione, consulta il capo cantiere cliccando con il pulsante destro del mouse  sul cantiere del monumento. Egli potrà dirti qual è l'ostacolo che lo osteggia.  Inoltre, se in città ci sono più cantieri all'opera, i manovali e i lavoratori  potrebbero non essere d'accordo su dove iniziare e, quindi, rimanere tutti  fermi. @L@PD: Mi occorre una particolare risorsa per costruire il mio monumento, ma la  mia città non può produrla e nessuno vuole vendermela. È un errore di  programmazione? @PR: In alcune missioni, la via commerciale che ti occorre diventa disponibile  solo quando hai soddisfatto le richieste di altre città (in particolare quelle  di aiuti militari). Se non soddisfi la prima richiesta, normalmente hai la  possibilità di rimediare e, quindi, aprire l'agognata via commerciale. Se  continui a non soddisfare le richieste, potresti fallire la missione. Le  missioni non presentano sempre tutti gli elementi della soluzione... a volte  devi guadagnarteli e il successo non è sempre garantito.  @L@LCommercio @PD: Ho aperto una via commerciale, ma la mia città non sta importando o  esportando alcunché. Cosa devo fare per iniziare un commercio? @PR: Visita il supervisore commerciale e ordinagli quali prodotti comprare o  vendere. Inoltre, assicurati di avere un deposito merci in città e un molo,  qualora il tuo socio in affari arrivi con una nave. @L@PD: Sto cercando di importare cibo. Ho una via commerciale aperta e ho  ordinato al mio supervisore commerciale di importarlo, ma senza risultato. La  gente è affamata - cosa posso fare? @L@PR: Assicurati che i tuoi depositi merci abbiano l'ordine di accettare il  cibo che vuoi importare. Ricorda che, all'inizio, i depositi merci hanno  istruzione di non accettare alcun tipo di cibo. L@PD: Ho lasciato che il mio @24supervisore&commerciale decidesse il livello di  prodotti commerciati da conservare nei depositi merci. Come posso accertarmi che  prenda delle sagge decisioni? @PR: Quando ordini al tuo supervisore commerciale di gestire il commercio, egli  controlla l'ammontare della popolazione cittadina, quali sono le sue industrie e  quali monumenti sono in fase di costruzione. Analizzando tali fattori, egli  stabilisce i bisogni della tua città. Per sapere quali sono le sue decisioni,  clicca sui pulsanti relativi ai prodotti. Quando compare il pulsante che ti  permette di impostare il livello, la quantità mostrata è quella scelta dal  supervisore commerciale.  @L@LAbitazioni @PD: Le zone residenziali che scelgo continuano a scomparire. Cosa sta  succedendo? @PR: Tutte le abitazioni devono trovarsi entro due spazi da una strada. Se sono  più lontane, scompaiono. Inoltre, gli immigranti devono essere in grado di  raggiungere le case. Assicurati di avere un cammino libero tra i punti di  ingresso e di uscita (la @57strada&del&Regno ) degli immigranti e le tue case."
        }
    }

    message_table_of_contents {
        id: 10
        
        size [30, 28]
        image { id: 47, pos [15, 15] }
        title { text: "Sommario" }
        subtitle { text: "Clicca su una voce per richiamare l'aiuto" }
        content {
            text: "@9Domande&ricorrenti @L@LArgomenti&aiuto @L@L@56Abitazioni @L@492Abu&Simbel @L@88Accademia @L@44Acqua&potabile @L@360Allevamento&bestiame @L@81Architettura,&centro&di @L@98Armeria @L@374Arredi&funebri @L@L@71Baraccone @L@2Bazar @L@2Bazar,&ordini&speciali @L@70Biblioteca @L@488Biblioteca&di&Alessandria @L@358Blocco&stradale @L@L@490Caesareum @L@L@66Camera&mortuaria @L@8Campo&di&lavoro @L@94Canne,&raccolta&di @L@82Cantiere&navale @L@369capo&cantiere @L@359Casotto&da&caccia @L@92Cava&d'argilla @L@95Cava&di&arenaria @L@95Cava&di&calcare @L@95Cava&di&granito @L@95Cava&di&pietra @L@95Cave @L@75Centri&di&addestramento @L@75Centri&di&addestramento&(artisti) @L@45Cibo @L@47Commercio @L@87Compagnia,&ordini @L@37Compagnie @L@354Complesso&templi&di&Bast @L@350Complesso&templi&di&Osiride @L@352Complesso&templi&di&Ptah @L@351Complesso&templi&di&Ra @L@353Complesso&templi&di&Seth @L@36Crimine @L@L@17Data&,indicatore @L@48Debiti @L@48Denaro @L@15Denaro,&indicatore @L@63Dentista @L@4Deposito&merci @L@56Desirabilità @L@85Difesa,&strutture&di @L@96Distilleria @L@L@33Edifici,&pulsanti @L@80Esattoria @L@L@98Fabbrica&di&carri&da&guerra @L@473Fabbrica&di&lampade @L@364Fabbrica&di&mattoni @L@97Fabbrica&di&papiro @L@470Fabbrica&di&pittura @L@65Farmacie @L@489Faro&del&Faraone @L@90Fattoria&di&ceci @L@89Fattoria&di&grano @L@91Fattoria&di&henna @L@90Fattoria&di&lattuga @L@91Fattoria&di&lino @L@90Fattoria&di&melograni @L@91Fattoria&d'orzo @L@45Fattorie (vedi anche fattorie specifiche) @L@29Festività @L@366Festività,&piazza&delle @L@61Fornitura&idrica @L@37Forte @L@L@79Giardino @L@363Gilda&degli&scalpellini @L@363Gilda&dei&carpentieri @L@363Gilda&dei&muratori @L@363Gilde&dei&costruttori @L@99Gioielliere @L@3Granaio @L@3Granaio,&ordini&speciali @L@85Guarnigione @L@52Guerra @L@L@43Impiego @L@46Industria @L@49Intrattenimento @L@59Irrigazione @L@50Istruzione @L@L@477Ladri&di&tombe @L@40Lavoratori @L@35Livelli @L@35Livello&culturale @L@35Livello&dei&monumenti @L@35Livello&del&Regno @L@35Livello&di&prosperità @L@L@78Magione @L@32Mappa&del&Regno @L@371Mastaba @L@368Mausoleo @L@64Medico @L@13Menu&Aiuto @L@11Menu&file @L@12Menu&Opzioni @L@14Menu&Supervisori @L@34Messaggi @L@361Miniera&di&gemme @L@93Miniera&di&rame @L@93Miniera&d'oro @L@84Molo&da&pesca @L@356Molo&nave&da&guerra @L@357Molo&nave&da&trasporto @L@370Monumenti,&costruzione @L@85Mura @L@L@365Nave&da&guerra @L@367Nave&da&trasporto&truppe @L@L@372Obelisco @L@L@73Padiglione @L@77Palazzo @L@76Palazzo&di&giustizia @L@72Palco @L@19Pannello&di&controllo,&visualizzazione @L@42Passanti @L@494Piaghe&principali @L@79Piazza @L@375Piramide&a&gradoni @L@55Piramide&di&mattoni @L@54Piramide&romboidale @L@38Piramide,&vera @L@58Ponte @L@39Popolazione,&crescita @L@16Popolazione,&indicatore @L@83Porto @L@62Pozzo @L@L@88Reclutamento @L@51Religione @L@L@53Sanità @L@67Santuario @L@18Tabelle @L@41Scribi @L@68Scuola&degli&scribi @L@362Sfinge @L@79Statua @L@355Stazione&dei&pompieri @L@86Stazione&di&polizia @L@57Strada&del&Regno @L@57Strade @L@28Supervisore&all'intrattenimento @L@27Supervisore&all'istruzione @L@31Supervisore&capo @L@24Supervisore&commerciale @L@25Supervisore&dei&granai @L@23Supervisore&dei&livelli @L@373Supervisore&dei&monumenti @L@20Supervisore&del&lavoro @L@30Supervisore&finanziario @L@21Supervisore&militare @L@22Supervisore&politico @L@29Supervisore&religioso @L@26Supervisore&sanitario @L@L@94Taglialegna @L@7Tastiera,&comandi&da @L@74Taverna&senet @L@67Tempio @L@69Tempio&del&sole @L@60Tessitoria @L@478Tombe&reali @L@85Torre @L@58Traghetto @L@48Tributo @L@L@39Umore&cittadino @L@L@1Vasaio @L@L@479Zoo @L@LStoria @L@152Abitazioni @L@493Abu&Simbel @L@472Artigiani @L@186Allevamento&e&pesca @L@190Argilla @L@196Armi @L@395Arredi&funebri @L@176Arte&pubblica @L@L@166Bambini @L@380Bast,&Iside&e&Hathor @L@199Bazar @L@197Beni&di&lusso @L@481Biblioteca&di&Alessandria @L@164Biblioteca&e&letteratura @L@194Birra @L@L@383Caccia @L@L@482Caesareum @L@188Canne @L@389Carpentieri @L@193Cave @L@177Commercio @L@L@171Danza @L@158Dentisti @L@6Deposito&merci @L@182Difesa,&strutture&di @L@L@184Esercito @L@L@195Fabbricazione&del&papiro @L@175Faraone,&casa&del @L@487Faro&del&Faraone @L@159Farmacia @L@150Fattorie @L@393Festività @L@187Frutta&e&verdura @L@L@176Giardini&e&arte&pubblica @L@169Giocolieri @L@382Gioielleria @L@174Governo&e&burocrazia @L@5Granaio @L@185Grano&e&orzo @L@L@469Henna @L@L@161Imbalsamazione @L@388Immigrazione @L@151Industria @L@165Intrattenimento @L@154Irrigazione @L@L@474Lampade @L@155Lavoro @L@183Legge @L@192Legno&e&suo&utilizzo @L@189Lino @L@L@381Malaria @L@394Mastaba @L@390Mattoni @L@160Medicina @L@396Monumenti,&altri @L@386Muratori @L@170Musica @L@L@179Navi&e&cantieri&navali @L@181Nemici @L@157Nilo @L@L@397Obelisco @L@476Olio @L@191Oro&e&miniere&d'oro @L@376Osiride,&Sebek&e&Min @L@L@495Piaghe&principali @L@392Piramidi @L@167Popolazione @L@156Pozzi&e&serbatoi&d'acqua @L@378Ptah,&Amon&e&Thoth @L@L@377Ra,&Ma'at&e&Horus @L@399Religione @L@L@384Sacerdoti @L@162Santuari&e&templi @L@385Scalpellini @L@387Scribi @L@163Scuola&e&istruzione @L@172Senet @L@379Seth,&Anubis&e&Sekhmet @L@391Sfinge @L@168Società @L@153Strade @L@L@173Tasse&e&denaro @L@398Tela&e&tessitura @L@L@475Valle&dei&Re @L@L@198Vasellame @L@L@480Zoo"
        }
    }
    
    message_file_menu {
        id: 11
        
        size [30, 28]
        title { text: "Menu File" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Dal menu File, puoi iniziare una nuova partita, rigiocare una  missione, caricare una partita precedentemente salvata, salvare la partita in  corso, eliminarne una precedentemente salvata e uscire dal gioco."
        }
    }
    
    message_optons_menu {
        id: 12
        
        size [30, 28]
        title { text: "Menu Opzioni" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Usa il menu Opzioni per modificare le impostazioni audio e video di Faraon. Usa l'opzione Schermo per modificare la visualizzazione e l'opzione Sonoro per modificare il volume dei suoni, del parlato e della musica. L'impostazione Velocità modifica la velocità con cui trascorre il tempo di gioco. Con l'opzione Città, puoi scegliere quali nomi di città utilizzare (classici o egizi). Probabilmente, puoi sentirti più a tuo agio con i nomi classici, ma i nomi egizi sono più fedeli allo spirito di gioco. @PPer controllare il modo in cui ricevi messaggi durante il gioco, modifica le impostazioni dei Messaggi a comparsa. La maggior parte dei messaggi che riceverai apparirà in una schermata a comparsa, che metterà il gioco in pausa fino a quando non la chiuderai. Le impostazioni dei Messaggi a comparsa ti permettono in questo modo di scegliere quali categorie di messaggi vuoi ricevere. Sfruttandone l'elenco, seleziona i tipi di messaggi che non vuoi ricevere cliccando sul nome della categoria, che si colorerà di giallo. Di conseguenza, tutti i messaggi di quella categoria verranno visualizzati in un apposito spazio nella parte superiore del video e appariranno anche nel tuo @34Elenco&messaggi. Così, non sarai costretto a bloccare la gestione della città per leggere i messaggi. Se sceglierai dalla lista 'Soddisfazione ora possibile', i beni richiesti verranno automaticamente inviati dai depositi merci della città quando saranno pronti. Per saperne di più sulla richiesta di merci, leggi la trattazione del @22supervisore&politico. @PDa questo menu, puoi attivare o disattivare il salvataggio automatico. In questo modo, la partita viene salvata ogni sei mesi di gioco, permettendoti un recupero conveniente se ti dimentichi di salvare manualmente o se hai dei problemi con il computer. Il salvataggio automatico riscrive sempre lo stesso file, quindi non c'è pericolo di riempire il disco di salvataggi non desiderati. Puoi disattivare tale funzione se vuoi eliminare la breve interruzione al gioco ogni volta che la partita viene salvata automaticamente. @Per modificare il livello di difficoltà durante il gioco usa l'opzione Difficoltà. Tieni a mente che il punteggio della missione è legato al livello di difficoltà scelto. Se cambi tale livello durante una partita, il tuo punteggio sarà interamente calcolato basandosi sul livello più facile tra quelli scelti. @PInfine, l'opzione Velocità Monumento ti permette di sfruttare l'aiuto divino per costruire certi @370monumenti. Attivando questa opzione, una divinità potrebbe decidere di aiutarti a costruire il tuo monumento. Gli Dei amano lavorarne solo alcuni tipi, in particolar modo le piramidi e le mastaba."
        }
    }

    message_help_menu {
        id: 13
        
        size [30, 28]
        title { text: "Menu Aiuto" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Il menu Aiuto elenca tutti gli argomenti che ti possono essere utili per giocare a Faraon. Puoi anche selezionare alcune sezioni storiche, presenti verso la fine del sommario. @PL''Aiuto mouse' è fornito dai piccoli riquadri che compaiono quando sposti il puntatore su vari oggetti. 'Completo' mostra tali riquadri per qualsiasi funzione di gioco; 'Parziale' disabilita l'aiuto mouse con poche eccezioni, come le @18viste&schermo e il rapporto ottenibile dal Palazzo. 'Nessuno' disabilita completamente l'aiuto mouse. @PGli 'Avvisi' sono i brevi messaggi che compaiono nella parte superiore della tabella. Puoi disabilitarli quando hai familiarizzato a sufficienza con il gioco."
        }
    }
    
    message_overseers {
        id: 14,
        
        size [30, 28]
        title { text: "Supervisori" }
        subtitle {
            text: "Controlli di gioco"
        }
        content {
            text: "Usa il menu supervisori o clicca sul pulsante supervisori per  consultare un supervisore. Il menu è utile se hai deciso di nascondere il  pannello di controllo. I supervisori offrono informazioni fondamentali  sull'attuale stato della città."
        }
    }
    
    message_game_control_money_display_window {
        id: 15,
        
        size [30, 28]
        title {
            text: "Finestra finanze",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Qui vengono mostrati i deben nel tesoro della tua città. Per  ulteriori informazioni sugli aspetti finanziari, vedi @48denaro."
        }
    }
    
    message_game_control_population_display {
        id: 16,
        
        size [30, 28]
        title {
            text: "Finestra popolazione",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Questa finestra mostra quanti cittadini vivono nella tua città. Segui  questo collegamento per ulteriori informazioni sulla @39popolazione e la sua  funzione nel gioco."
        }
    }
   
    message_game_control_date_display {
        id: 17,
        
        size [30, 28]
        title {
            text: "Finestra datario",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Questa finestra mostra il mese e l'anno correnti. Per semplicità, si  utilizza un calendario moderno. Se il tempo si muove troppo in fretta o troppo  lentamente, puoi usare le Impostazioni Velocità."
        }
    }
    
    message_overlay_selector {
        id: 18,
        
        size [30, 28]
        title {
            text: "Selettore tabelle",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il selettore delle tabelle ti permette di osservare la tua città applicando diversi filtri. Queste tabelle sono fondamentali per una buona pianificazione e gestione dei servizi cittadini. @PQuando scegli una tabella, vedrai soltanto gli edifici e i cittadini relativi al tipo di vista impostata. Tutti gli altri edifici saranno normalmente sostituiti da colonne. Nella maggior parte dei casi, le colonne indicano l'accesso a un dato servizio o a una certa funzione della città. Tanto più alta è la colonna, tanto migliore è l'accesso offerto a quel servizio. @PLe eccezioni alla regola sono la tabella Rischi, la tabella Problemi, la tabella Desiderabilità e la tabella Nascondi rupi. Nella tabella Rischi, le case e gli altri edifici sono comunque sostituiti da colonne, ma il livello di rischio è indicato dalla loro altezza e dalla maggiore tendenza alla colorazione rossa. @PLa tabella Problemi mostra gli edifici che non funzionano correttamente o che stanno per manifestare qualche grave problema. Alla sommità di questi edifici apparirà un'icona che indica il tipo di problema. Questa tabella mostra anche i trasportatori che si sono fermati perché non hanno nessun posto dove portare le merci o il cibo. @PLa tabella Desiderabilità trasforma la città in un mare di blocchi multicolore. I blocchi dorati indicano le locazioni che i cittadini trovano più desiderabili. Tanto più questi blocchi tendono al marrone, tanto meno desiderabili sono le zone indicate. Per saperne di più sulla desiderabilità, clicca @56qui. @PSe le rupi impediscono la visuale, usa la tabella Nascondi rupi per spianarle temporaneamente. Se hai costruito qualche Tomba Reale all'interno delle rupi, potrai vederla dopo aver selezionato la tabella Nascondi rupi. @PInfine, la tabella dei pozzi d'acqua funziona in modo un po' diverso. L'accesso all'acqua viene indicato da colonne blu di altezza crescente con la qualità dell'accesso. Questa tabella mostra anche quali territori possono supportare strutture che hanno qualche nesso con l'acqua e quali hanno accesso all'acqua potabile dei pozzi. I quadrati di colore blu scuro indicano le case a cui arriva l'acqua dei pozzi, mentre i quadrati di colore azzurro indicano i terreni ricchi di falde acquifere sufficienti per crearvi un @62pozzo, un @61serbatoio&d'acqua o un altro edificio che richieda accesso alle acquee sotterranee. @PIl modo migliore di familiarizzare con gli schermi è provarli. Quando capisci le informazioni che riportano, sarai in grado di pianificare la tua città in modo più efficiente."
        }
    }

    message_control_panel_toggle {
        id: 19,
        
        size [30, 28]
        title {
            text: "Interruttore pannello di controllo",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Questo pulsante ti permette di far comparire o nascondere il pannello  di controllo. Con il pannello nascosto puoi vedere meglio la tua città, ma i  controlli di gioco sono più scomodi. Con l'interruttore puoi decidere di volta  in volta se averli o non averli a portata di click."
        }
    }

    message_overseer_workers {
        id: 20,
        
        size [30, 28]
        title {
            text: "Supervisore del lavoro",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il tuo supervisore del lavoro registra tutto quanto concerne la forza  lavoro: numero di posti disponibili per settore d'impiego, numero di disoccupati  e attuale riferimento per i salari. Ti aiuterà a gestire tutte le situazioni che  riguardano i tuoi lavoratori. @PCon il supervisore del lavoro puoi stabilire gli stipendi medi in città. Su  questo pannello puoi tenere d'occhio gli stipendi che paghi e confrontarli con  quelli prevalenti in Egitto. Usa i pulsanti di scorrimento per modificare i  salari. Se aumenti i salari oltre il livello medio egizio, aumenterai anche  l'@39umore e incoraggerai @39l'immigrazione. Se paghi meno, risparmierai denaro,  ma l'umore si abbasserà drasticamente fino a causare l'emigrazione. @PPuoi consultare il supervisore del lavoro per stabilire le priorità  lavorative. Se non ne assegni alcuna, il supervisore le assegnerà come meglio  crede. In genere cercherà prima di coprire il lavoro che produce cibo e poi  quello industriale. Se vuoi stabilire una nuova priorità, ad esempio militare,  clicca sulla voce relativa e comparirà un altro pannello. Per stabilire una  priorità militare, clicca sul numero uno. Comparirà l'icona di un lucchetto per  indicare che hai stabilito la priorità militare. La prossima categoria scelta,  diventerà automaticamente la numero due. Puoi assegnare priorità a qualsiasi  settore lavorativo.  @PUn solo avviso: quando imposti una priorità, il supervisore del lavoro cerca  di coprire prima di tutto i posti disponibili in quel settore. Ciò potrebbe  lasciare alcuni settori privi di lavoratori. La tua città potrebbe non resistere  a lungo se vi sono dei settori lavorativi completamente scoperti. @PPer ulteriori informazioni sull'aspetto del lavoro nel gioco, clicca @43qui. @L@LPer un breve riassunto storico sulla forza lavoro dell'antico Egitto, clicca  @155qui."
        }
    }

    message_overseer_military {
        id: 21,
        
        size [30, 28]
        title {
            text: "Supervisore militare",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il Lo supervisore militare controlla le tue unità militari di terra e  di mare. @PQuando consulti il supervisore militare, egli ti aggiorna sul numero e  condizione delle tue compagnie. Per passare dalle unità di terra a quelle marine  e viceversa, clicca sul pulsante nell'angolo a destra in basso della tabella. @PPuoi controllare qualsiasi unità cliccando sul pulsante 'Vai a'. Puoi anche  ritirare qualsiasi unità nel suo forte o al suo molo ciccando sul pulsante  'Ritorna'. @PA volte, il Faraone o un'altra città richiedono l'utilizzo delle tue unità per  una battaglia. Clicca sul pulsante 'In servizio al Regno' per inviare le truppe  sul luogo della battaglia. Aiutare altre città o il Faraone può comportare dei  benefici. Il tuo livello del Regno può aumentare, oppure puoi ottenere commerci  più lucrativi con altre città. Negare il rinforzo delle tue truppe a chi lo  richiede può invece portare a rabbia e insoddisfazione nei tuoi confronti. @PIl tuo supervisore militare ti aggiorna sulle attività militari che hanno  luogo dentro e intorno la tua città. Ti dirà se ci sono nemici in avvicinamento  o se qualcuno ha richiesto un aiuto militare. @L@LGli antichi Egizi disponevano di un esercito e una flotta possenti. Clicca  @181qui per ulteriori informazioni sulle antiche tecniche di guerra."
        }
    }

    message_overseer_political {
        id: 22,
        
        size [30, 28]
        title {
            text: "Supervisore politico",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il supervisore politico gestisce le tue relazioni con il Faraone e  con i governanti delle altre città. @PIl supervisore politico tiene traccia di tutte le richieste di provviste da  parte del Faraone o altre città. Può dirti quante merci sono disponibili nei  tuoi @4depositi&merci e ti avviserà quando sarai in grado di soddisfare le  richieste. Tu puoi ordinare al supervisore politico di inviare le merci.  Generalmente è consigliabile soddisfare le richieste del Faraone o di altre  città il più presto possibile. Ignorare una richiesta può ridurre il commercio o  addirittura scatenare un attacco contro la tua città. Inviare le merci in  ritardo è meglio che non inviarle del tutto. @PIl supervisore politico ti aiuta a gestire il tuo tesoro personale. Può  comunicarti quanto hai guadagnato e il tuo stipendio attuale. Se vuoi, puoi  consultarlo per modificare il tuo stipendio. Devi solo cliccare sul pulsante che  mostra il tuo stipendio attuale e comparirà una schermata che elenca vari titoli  e gli stipendi relativi. Da questa schermata puoi scegliere un nuovo livello di  stipendio. Tieni a mente che i tuoi colleghi egizi non vedono di buon occhio chi  si concede uno stipendio superiore a quello relativo al proprio titolo. @PSe vuoi spendere un po' dei tuoi risparmi, il supervisore politico gestirà  tutte le transazioni. Puoi decidere di inviare un dono al Faraone (o, se tu sei  il Faraone, al Regno in generale), oppure puoi rimpolpare le finanze cittadine. @PIl Faraone e gli altri governanti apprezzano molto i doni personali. Inviando  qualche regalo ogni tanto, puoi accrescere il tuo status - e quindi ottenere un  aumento del livello del Regno. Secondo le tue disponibilità, puoi scegliere tra  tre doni diversi, ma non occorre essere troppo generosi. Se invii dei doni  troppo spesso, i beneficiari lo riterranno un atto dovuto e si arrabbieranno se  non ne ricevono più. Inoltre si aspettano che ogni regalo sia più prezioso del  precedente. Quando decidi di inviare un regalo, il supervisore politico farà in  modo che arrivi intatto a destinazione. @PPuoi anche donare parte dei tuoi risparmi al tesoro cittadino. Ciò può  rappresentare una buona idea, soprattutto se il tuo intervento può impedire che  la città si copra di debiti. I debiti possono rovinare una città. Il Faraone e  gli altri governanti ti presteranno dei soldi ma tutto ha un prezzo. Per  ulteriori informazioni sul tesoro cittadino, clicca @48qui. @PInfine, il supervisore politico conosce il tuo livello del Regno e la  predisposizione del Faraone nei tuoi confronti. Per ottenere una valutazione  generale e obiettiva, il @23supervisore&dei&livelli è la migliore fonte di  informazioni."
        }
    }
    
    message_overseer_ratings {
        id: 23,
        
        size [30, 28]
        title {
            text: "Supervisore dei livelli",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il supervisore dei livelli ti mostra i livelli del Regno, Cultura,  Prosperità e Monumenti, nonché l'obiettivo di popolazione. Quando clicchi su un  livello, il supervisore ti informerà sul metodo migliore per migliorarlo, o ti  comunicherà quale impedimento lo ostacola. Puoi vedere quanto ti manca per  raggiungere i livelli obiettivo osservando le barre sopra ciascun livello.  Quando raggiungi un obiettivo assegnato all'inizio della missione, la colonna  relativa è chiusa. @PSe nella tua città è presente un @77Palazzo&del&governo puoi verificare i tuoi  livelli semplicemente mantenendo il puntatore sul Palazzo: comparirà un piccolo  schermo che mostrerà tutti i livelli e il tasso di disoccupazione. @PPer ulteriori informazioni sui livelli e la loro funzione nel gioco, clicca  @35qui."
        }
    }

    message_overseer_commerce {
        id: 24,
        
        size [30, 28]
        title {
            text: "Supervisore commerciale",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il tuo supervisore commerciale è una persona molto indaffarata. Oltre  a individuare le città con sui puoi @47commerciare, conosce anche il contenuto  di tutti i tuoi @4depositi&merci e lo stato delle tue @46industrie. @PQuando consulti il supervisore commerciale, vedrai un elenco dei beni prodotti  dalla tua città e quelli importati. Cliccando su un bene, puoi leggere un breve  rapporto sullo stato di quella particolare industria. Puoi sapere quanti edifici  sono dedicati alla produzione di una merce e quanti di questi edifici sono  attualmente al lavoro. @PSempre da questo pannello, puoi impartire ordini relativi alle varie merci. Se  disponi di una via commerciale per una merce (ulteriori informazioni più  avanti), puoi ordinare al supervisore commerciale di importarla o esportarla. Se  la esporti, dovrai indicare anche la quantità da tenere come scorta nei depositi  merci. Ciò è particolarmente importante se esporti oggetti come il vasellame. La  domanda di vasellame dei tuoi cittadini è normalmente alta, quindi devi fare in  modo di tenerne una scorta consistente. @PPuoi anche chiudere un'industria. Se vuoi smettere di produrre una merce, puoi  scegliere di sospendere l'industria. Gli edifici che creano il prodotto finale  vengono chiusi ma non vengono distrutti. Gli edifici che producono il materiale  grezzo per il prodotto finale non sono influenzati. Gli edifici 'sospesi'  licenzieranno i loro lavoratori. Questo è un buon modo per liberare forza lavoro  nei periodi di necessità. Puoi riattivare l'industria in qualsiasi momento. @PL'ultimo pulsante del pannello ti permette di accumulare i beni nei depositi  merci. Quando accumuli la merce, non puoi commerciarla e i tuoi cittadini non  possono averla disponibile. L'accumulo è particolarmente utile quando devi  adempiere una richiesta. Cliccando di nuovo sullo stesso pulsante, puoi  disattivare l'accumulo e commerciare la merce di nuovo. Se già commerciavi il  bene prima di attivare l'accumulo, devi ordinare al supervisore commerciale di  riprendere l'attività. @PDal pannello del supervisore commerciale puoi richiamare la  @32mappa&del&Regno. La mappa mostra le altre città della tua regione. Cliccando  su ciascuna città puoi sapere se è intenzionata a commerciare con te o meno. Se  la città è disponibile al commercio, i beni che compra e vende sono elencati in  fondo alla tabella. I pallini vicini al simbolo di un bene indicano la quantità  venduta o comprata in un anno dalla città - un pallino indica fino a 15 carri,  due pallini fino a 25 carri e tre pallini fino a 40 carri. @PÈ presente anche il costo di apertura di una via commerciale. Clicca su questo  pulsante e il tuo tesoro spenderà il necessario per aprire un nuovo commercio.  Dopo l'apertura della via commerciale, consulta di nuovo il tuo supervisore  commerciale per comunicargli quali beni importare o esportare. @PIl supervisore commerciale conosce anche i prezzi di vendita e di acquisto.  Clicca sul pulsante 'Mostra prezzi' e comparirà un pannello che elenca tutti i  beni del Regno. Noterai che i venditori ricevono meno di quanto pagano gli  acquirenti. La differenza è dovuta alla spesa delle carovane e delle navi  commerciali che intraprendono lunghi viaggi in nome del libero commercio. @PLe sezioni relative all'@46industria, @45cibo e @47commercio ti aiuteranno a  comprendere i meccanismi fondamentali del commercio."
        }
    }
    
    message_overseer_granaries {
        id: 25,
        
        size [30, 28]
        title {
            text: "Supervisore dei granai",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Cibo e popolazione sono strettamente collegati. Il supervisore dei  granai tiene traccia della popolazione e del fabbisogno di cibo. @PIl supervisore presenta le informazioni sotto forma di tre grafici diversi. Il  primo grafico mostra la storia della popolazione, ovvero il numero di cittadini  nel tempo. A destra del grafico storico ce ne sono altri due più piccoli, il  censimento e il societario. Clicca su uno di questi grafici per ingrandirlo e  posizionarlo al centro della tabella.  @PIl grafico del censimento raggruppa la popolazione secondo l'età e risulta  utile per prevedere la disponibilità di forza lavoro, dato che i vecchi e i  bambini non lavorano ma continuano a consumare cibo, bere birra e spaccare vasi!  @PIl grafico societario raggruppa la popolazione secondo la rendita, mostrata in  termini di tipo di abitazione. I residenti più ricchi (gli scribi) non si  sporcano le mani con il lavoro manuale, quindi, man mano che la tua popolazione  diventa più ricca, la sua forza lavoro tende a diminuire. Anche se non  contribuiscono alla forza lavoro, gli scribi pagano tasse consistenti. @PSotto i grafici ci sono alcune linee assai utili. La prima linea indica il  numero di persone sostenibili con l'attuale produzione di cibo e gli effetti  prodotti nell'immediato futuro. Il supervisore dei granai può anche dirti quanti  granai sono presenti in città e il loro contenuto in termini di mesi di  sostentamento. Può anche dirti quanti tipi di cibo i tuoi cittadini consumano.  Inoltre, sa se le persone arrivano in città o se ne vanno e quanti immigrati  sono giunti nel mese precedente. @PLe sezioni relative alla @39popolazione e al @45cibo possono aiutarti a  comprendere meglio l'importanza del supervisore dei granai."
        }
    }
    
    message_overseer_public_health {
        id: 26,
        
        size [30, 28]
        title {
            text: "Supervisore sanitario",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il tuo supervisore sanitario ti informa sul numero di camere  mortuarie, medici e dentisti attivi nella tua città. Per ciascuno di questi  servizi, il supervisore sa quanti cittadini servono e può darti un'idea generale  sulla copertura. Può anche dirti il numero di farmacie presenti in città. Per  informazioni più specifiche sulla copertura in determinate zone della città, usa  la @18Tabella&Igiene. @PIl tuo supervisore sanitario è a conoscenza di rischi per la salute pubblica,  come la malaria o una pestilenza, che possono colpire la città. Dato che una  dieta bilanciata è fondamentale per la salute, ti può informare sui tipi di cibo  consumati dai tuoi cittadini. Inoltre, tiene traccia dell'atteggiamento generale  dei cittadini nei confronti di tali servizi.  @PLa sezione @53Igiene ti aiuterà a comprendere gli effetti della salute nel  gioco."
        }
    }
    
    message_overseer_learning {
        id: 27,
        
        size [30, 28]
        title {
            text: "Supervisore all'istruzione",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Il supervisore all'istruzione ti informa sul numero di scuole degli  scribi e biblioteche presenti in città. Ti dirà quante persone sono servite da  queste istituzioni e se la copertura è adeguata o meno. Per controllare meglio  la copertura in determinate zone della tua città, usa lo @18tabella&Educazione. @PIl supervisore all'istruzione ti dirà anche qual è la domanda dei cittadini  nei confronti dell'educazione. Per ulteriori informazioni, vedi la sezione  @50educazione."
        }
    }

    message_overseer_diversions {
        id: 28,
        
        size [30, 28]
        title { text: "Supervisore all'intrattenimento" }
        subtitle { text: "Controlli di gioco"  }
        content {
            text: "Il supervisore all'intrattenimento sa quanti sono i palchi dei giocolieri, musici e danzatori attivi in città. Il numero di palchi è più importante del numero di @71palchi, @72palchi&dell'orchestra e @73padiglioni esistenti, quindi si limiterà a tale informazione. Inoltre, riporta il numero di @74Taverne&Senet e @479Zoo funzionanti. Ti comunica la stima della popolazione che può beneficiare dell'intrattenimento e controlla il livello di soddisfazione dei cittadini. @PSe vuoi avere ulteriori informazioni sul ruolo dell'@49intrattenimento, consulta la relativa sezione. @L@LPer ulteriori informazioni sull'intrattenimento nell'antico Egitto, clicca @165qui."
        }
    }

    message_overseer_temples {
        id: 29,
        
        size [30, 28]
        title {
            text: "Supervisore religioso",
        }
        subtitle {
            text: "Controlli di gioco",
        }
        content {
            text: "Appagare tutti gli dei può diventare un compito difficile. Il supervisore religioso ti aiuta nell'impegnativo compito di mantenerli soddisfatti. @PQuando consulti il supervisore religioso, egli ti mostra tutti gli dei che influenzano la tua città. Ti può dire qual è il dio patrono, ovvero la divinità da trattare con maggiore considerazione. Vicino al nome di ciascun dio, riporta il numero di templi grandi e piccoli presenti in città. Ti può dire anche il numero di santuari e quanti mesi sono trascorsi dall'ultima festività in onore di ciascun dio. Infine, può informarti sull'umore di ogni divinità. @PQuando vuoi proclamare una festività, il supervisore religioso ti aiuta a pianificarla. Clicca sul pulsante 'Nuova festività'. Scegli quale dio onorare e la dimensione della festività. Ricorda che prima di poter indire una festività grandiosa devi costruire un Piazza delle festività. Le festività grandiose richiedono anche una buona provvista di birra. @PIl supervisore religioso ti informerà sui gusti dei tuoi cittadini in fatto di divinità. @PPer capire a fondo l'importanza degli dei nel gioco, leggi le sezioni  @51religione e @35livelli."
        }
    }

    message_overseer_treasury {
        id: 30,
        
        size [30, 28]
        title { text: "Supervisore finanziario" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Il tuo supervisore finanziario tiene traccia di tutti i deben che  entrano ed escono dai forzieri cittadini. Esaminando i suoi documenti puoi  individuare dove è possibile tagliare i costi o aumentare i margini. @PIn cima alla tabella del supervisore finanziario puoi trovare un breve  rapporto sulle tasse. Usa i pulsanti di scorrimento per modificare l'ammontare  delle tasse. L'impostazione di base è del 7% e dai tuoi cittadini è considerata  ragionevole. Aumentarla molto oltre tale valore li farà arrabbiare e scoraggerà  l'immigrazione. Se mantieni le tasse elevate per molto tempo, i tuoi cittadini  diventeranno sempre più arrabbiati. Per ulteriori informazioni sull'umore dei  cittadini, clicca @39qui. @PIl rapporto mostra anche le tasse raccolte, quanti cittadini sono registrati e  quanto denaro non è stato raccolto per numero insufficiente di esattori. Per  stabilire quali zone della città non sono coperte dagli esattori, usa lo  @18tabella&Tasse. @PDopo il rapporto informativo si trovano i conti. Le voci in cima all'elenco  descrivono le entrate derivate dalle tasse, doni ed esportazioni. @PSotto la magra lista delle entrate, si trova il lungo elenco delle spese. In  generale, stipendi e costi di costruzione sono le voci più importanti, ma anche  i costi di importazione possono diventare abbastanza pesanti. @PLa parte sinistra dell'elenco mostra i conti dell'anno precedente. Puoi usarli  come termine di paragone per individuare quali costi sono aumentati. @PPer ulteriori consigli finanziari puoi consultare la sezione @48denaro.  Un'altra sezione utile è quella degli @80esattori."
        }
    }

    message_chief_overseer {
        id: 31,
        
        size [30, 28]
        title { text: "Supervisore capo" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Il supervisore capo si riunisce con gli altri supervisori e fornisce  un quadro generale sulla situazione cittadina. È il riferimento fondamentale per  stabilire quali siano le necessità della tua città. Le situazioni urgenti  appaiono in giallo. I problemi gravi appaiono in bianco. Clicca su un problema  per ottenere consigli su come affrontarlo e accedere ai collegamenti con altri  supervisori che possono aiutarti su problemi più specifici. @PIl tuo supervisore capo ti informa sulle previsioni di straripamento del Nilo.  Il 'Nilometro' stima la bontà della prossima inondazione. @PDevi porre molta attenzione ai consigli del supervisore capo. Considerando i  suoi avvertimenti, puoi salvare la tua città da possibili disastri."
        }
    }

    message_world_map {
        id: 32,
        
        size [30, 28]
        title { text: "Mappa del Regno" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "La mappa del Regno mostra le città più importanti della tua regione.  La sua funzione principale è quella di individuare possibili interlocutori  @47commerciali. @PClicca sul nome di una città per sapere se è intenzionata a commerciare con  te. Se la città vuole commerciare, sotto il suo nome compaiono i prodotti  acquistati e venduti, oltre al costo di apertura di una via commerciale. Clicca  sul pulsante 'Apri via commerciale' per iniziare le trattative. @PSpesso riceverai richieste di merci da altre città o sentirai voci di  battaglie che infuriano in altri luoghi. La mappa del Regno è un riferimento  fondamentale per capire se tali luoghi sono vicini o lontani dalla tua città. Se  un invasore sta attaccando una città vicina, dovrai stare in guardia e fare  attenzione che il nemico non capiti dalle tue parti. @PPer ulteriori informazioni sull'uso della mappa del Regno, leggi le sezioni  @47commercio, @52guerra&e&pace e @24Supervisore&commerciale."
        }
    }

    message_building_buttons {
        id: 33,
        
        size [30, 28]
        title { text: "Pulsanti di costruzione" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Questi pulsanti ti permettono di posizionare le costruzioni sulla  mappa. Il prezzo di ogni struttura è mostrato sul suo pulsante. Quando scegli  una struttura da costruire, vicino al tuo puntatore compare la sua immagine  semi-trasparente. Quando sposti il puntatore su un territorio edificabile,  l'immagine è verde; su un terreno non adatto, l'immagine diventa un rombo rosso. @L@LPuoi accedere alla sezione di aiuto per ciascun edificio cliccando sulle  strutture esistenti con il pulsante destro del mouse, oppure selezionando la  sezione 'Strutture' dal @10sommario."
        }
    }
    
    message_game_control_messages {
        id: 34,
        
        size [30, 28]
        title { text: "Messaggi degli scribi" }
        subtitle { text: "Controlli di gioco" }
        content {
            text: "Quando si verifica un evento importante in città o in un altro punto del regno, riceverai un messaggio informativo. Alcuni di questi messaggi sono urgenti e richiedono una pronta risposta da parte tua. Potrebbe trattarsi di una richiesta del Faraone, oppure di altre città, oppure potrebbe indicarti un particolare problema nella tua città. @PQuando arriva un nuovo messaggio, si illumina il pulsante Messaggi del pannello di controllo e si sente un segnale acustico. Clicca sul pulsante per leggere il messaggio. Se è molto importante, ti verrà consegnato di persona e comparirà automaticamente sul video. Se si tratta di un problema che si è verificato in qualche punto della città, puoi cliccare sul pulsante di allarme, nel messaggio stesso, per raggiungere il punto indicato. @PAltri messaggi contengono istruzioni che ti aiuteranno a gestire la città con più efficienza. Si tratta di utili indicazioni che spiegano importanti concetti del gioco e ti spiegano alcuni obiettivi a breve termine. Raggiungendo gli obiettivi a breve termine citati in questi messaggi speciali, potrai superare una missione e passare alla prossima fase. Questi messaggi sono contraddistinti da una pergamena blu nell'elenco messaggi. @PPuoi cancellare i messaggi che hai letto cliccando con il pulsante destro sul loro titolo nell'elenco messaggi. Un pulsante alla base del pannello ti permette di cancellare in una sola volta tutti i messaggi aperti in precedenza, tranne quelli che non hai ancora letto o quelli indicati dalla pergamena blu. Una volta cancellato, un messaggio è perso per sempre. Puoi, naturalmente, tenere i messaggi per poterli consultare in futuro. @PI giocatori esperti possono trovare utile disattivare certi messaggi a comparsa sfruttando il @12Menu&Opzioni. Se attivi quest'opzione, i messaggi appariranno nella parte superiore della tabella e verranno anche aggiunti alla tua Cartella dei messaggi."
        }
    }

    message_ratings {
        id: 35,
        
        size [30, 28]
        title { text: "Livelli" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "I livelli indicano la qualità di una città o la tua bravura a governare. All'inizio di ogni missione ti sono attribuiti degli obiettivi di livello. Per misurare il successo di una città si usano quattro livelli diversi: Cultura, Prosperità, Regno e Monumenti. @L@LCULTURA @PIl livello cultura indica l'accesso dei tuoi cittadini all'@49intrattenimento, @50educazione, @53igiene e @51religione. Tale livello non misura solo il numero di edifici ad essi relativi, ma anche la varietà di opzioni. Per raggiungere un alto livello di cultura, cerca di fornire ai tuoi cittadini il maggior numero possibile di opzioni. Ciò comporta un facile accesso a diverse forme d'intrattenimento, servizi sanitari (con l'eccezione delle farmacie che non sono prese in considerazione) e strutture religiose. @PPer continuare a far crescere questo livello, è necessario garantire ai cittadini più ricchi l'accesso alle biblioteche e alle scuole degli scribi, ma non è tutto qui. La gente impara meglio quando si trova in edifici tranquilli e poco affollati, dunque il livello di cultura riflette la qualità dell'educazione indicando quante persone frequentano ogni scuola e ogni biblioteca. Può capitare che ci siano sufficienti strutture educative per ogni casa della città e, nonostante questo, avere problemi di sovraffollamento. @PPer raggiungere il più alto livello di cultura, controlla se puoi costruire uno @479zoo. La sua costruzione è necessaria se vuoi superare quota 75 in Cultura. Clicca sul pulsante Intrattenimento per vedere se lo zoo figura fra le tue opzioni. @L@LPROSPERITÀ @PIl livello di prosperità misura la ricchezza generale della città e la sua solidità finanziaria. Questa è molto più di una semplice valutazione delle casse cittadine: prende in considerazione la ricchezza dei singoli cittadini, tenendo conto del valore delle loro proprietà e del livello di disoccupazione @PSe la tua città guadagna anno dopo anno, il tuo livello di prosperità continuerà a salire, se non accade altro che possa frenarlo. Un alto tasso di disoccupazione, abitazioni di scarsa qualità, salari bassi e mancanza di varietà di cibo sono tutti ostacoli alla prosperità. Anche il mancato pagamento delle tasse al regno influisce negativamente. Se nella tua città è presente un complesso di templi o una taverna senet, il tuo livello di prosperità cresce, perché la gente crede che la loro città sia importante. Anche il completamento di un monumento aumenta enormemente il tuo livello di prosperità. Invece, quando la tua città chiude l'anno in rosso o perde dei soldi, il livello di prosperità ne soffre. Comunque, se hai perso del denaro a causa dei costi di costruzione, il livello di prosperità non ne è influenzato, perché le spese di costruzione migliorano la città.    @L@LREGNO @PIl livello del regno indica la tua reputazione, soprattutto nei confronti del resto dell'Egitto. Una pronta risposta alle richieste di un alleato aiuta ad aumentare questo livello. Il mancato adempimento alle richieste o al pagamento di un @48tributo&annuo a causa di un deficit monetario danneggia il livello del regno. Se il tuo livello del regno diminuisce troppo, la tua pessima reputazione può provocare un attacco da parte del Faraone o di una città vicina. @PDi solito, inizierai ogni missione con un livello di 50, che è un valore neutro. La gente al di fuori della tua città non ha mai sentito parlare di te, e i pochi che ne hanno sentito parlare non hanno particolari opinioni. Se non farai nulla per aumentarlo, con il trascorrere del tempo il tuo livello del regno diminuirà e si spargerà la voce che sei poco importante al di fuori dei tuoi confini. Il livello cala più velocemente se perdi o ignori battaglie lontane, se non soddisfi le richieste di beni o di altre cose provenienti dal resto del regno e se resterai in @48debito per un periodo qualunque. Inoltre, riscuotere un salario inadatto al tuo rango non migliorerà di sicuro la situazione. @PIl tuo livello del regno si ridurrà anche se i @477predoni&di&tombe ruberanno gli @374arredi&funebri da una tomba nonostante la tua sorveglianza. La gente dell'Egitto penserà infatti che non porti il dovuto rispetto per i morti. @PPer aumentare il livello del regno, soddisfa velocemente le richieste del Faraone e di altre città egiziane, soprattutto quando ti chiedono aiuto militare. Vincere una battaglia può fare miracoli per la tua reputazione. A volte, anche perdere una battaglia può essere un piccolo aiuto, dato che almeno hai provato ad aiutare i tuoi connazionali nel momento del bisogno. @PSe vuoi aumentare velocemente la tua reputazione, usa i risparmi della tua famiglia per comperare un dono per l'Egitto. Il tuo supervisore politico invierà il dono al Faraone, oppure ad altri capi egiziani, o alla gente dell'Egitto, a seconda dell'alternativa che riterrà più opportuna. Il tuo livello del regno salirà immediatamente di alcuni punti, ma non cedere alla tentazione di spendere tutti i tuoi risparmi in regali. Infatti, questo sistema perde efficacia se vi fai ricorso troppo di frequente, perché dopo un po' i destinatari si aspetteranno omaggi del genere. Così, il tuo livello del regno potrà addirittura scendere se smetterai di inviare doni, o se ne invierai di meno preziosi rispetto a quelli che i destinatari hanno cominciato ad aspettarsi. Fare più di un regalo del genere all'anno potrebbe essere inutile, se non addirittura controproducente. @PCatturare un predone di tombe è un gesto apprezzato dagli egiziani. Il tuo livello del regno aumenterà leggermente per ogni predone di tombe catturato dai tuoi conestabili. @PLa naturale tendenza discendente del livello del regno può ridursi se accetterai un salario personale al di sotto di quello previsto per il tuo rango. Rinunciare totalmente a un salario è ancora meglio per la tua reputazione di altruistico servitore dello stato, ma non è la migliore strategia per aumentare la ricchezza della tua famiglia! @L@LMONUMENTI @PIl livello dei monumenti considera sia le dimensioni sia il significato di tutti i monumenti della città, contando anche la durata dei lavori. Se terminerai tutti i monumenti richiesti e ti ricorderai di inviare tutti i necessari arredi funebri per i morti, non avrai problemi a raggiungere il livello di monumenti fissato come obiettivo. @L@LUna breve consultazione con il tuo @23supervisore&dei&livelli ti fornirà un quadro della situazione. Quando clicchi su un livello, il tuo supervisore ti dirà come procedere per migliorarlo."
        }
    }

    message_city_crime {
        id: 36
        
        size [30, 28]
        title { text: "Crimine" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "Il crimine nasce da un basso @39umore&cittadino. La gente può essere infelice per tante ragioni: salari bassi, tasse elevate, mancanza di cibo e di lavoro. Però, è necessaria una forte insoddisfazione perché scoppino ondate di crimine. @PDunque, il miglior modo di prevenire il crimine è tenere soddisfatti i cittadini. Fornire cibo e servizi in abbondanza ha un notevole effetto sul loro umore, ma si può prevenire il crimine anche costruendo @76palazzi&di&giustizia e @86stazioni&di&polizia in città. La presenza di queste due strutture, infatti, scoraggia i potenziali criminali. @PPerò, anche nonostante l'impegno più accanito, può capitare che certe zone della città creino ugualmente nuovi criminali, soprattutto quelle fortemente industrializzate. Se si verifica un'ondata di crimine, un conestabile di una stazione di polizia cercherà di catturare tutti i criminali che potrà. @PSe un criminale riesce a sfuggire al conestabile, si dirigerà verso uno degli edifici cittadini dove tieni i soldi, senza fare molte distinzioni fra il tesoro della città e i risparmi della tua famiglia. Quando avrà derubato l'edificio, si nasconderà e non ruberà più... almeno per un po'. @PIl crimine può anche creare @477predoni&di&tombe, ma soltanto se la tua città è l'estrema dimora delle più grandi personalità egiziane e ospita una tomba (Piramide, Mastaba, Mausoleo o Tomba Reale). I predoni di tombe sono abili soprattutto nel violare le Tombe Reali e nel saccheggiare i loro tesori. @PA volte, perfino i cittadini più felici possono cadere vittime dell'avidità. Queste persone si riuniscono con i loro amici e discutono dei preziosi beni lasciati nelle tombe assieme ai cadaveri dei nobili. Quando il desiderio di ricchezza ha la meglio su di loro, sorge un'ondata di crimine e questi cittadini diventano predoni di tombe! Dato che non puoi controllare i pensieri dei tuoi cittadini, non puoi sapere quando si svilupperà un'ondata di crimine. Comunque, i conestabili saranno pronti a reagire risolutamente contro chiunque osi violare una tomba sottraendone il prezioso contenuto."
        }
    }

    message_fort_and_company {
        id: 37,
        
        size [30, 28]
        title {
            text: "Compagnie e forti",
        }
        content {
            text: "Ciascun soldato è assegnato a una compagnia e ognuna di queste ha il  suo forte. I tipi di compagnie e forti sono: @L@LFanteria @LLa fanteria costituisce gran parte di qualsiasi esercito. Specialisti del  combattimento ravvicinato, essi sono sempre in prima linea. Si muovono a una  velocità media. Lasciano il reclutamento armati di lance. @L@LArcieri @LCon le frecce, gli arcieri attaccano il nemico da una maggiore distanza, ma,  se vengono impegnati in un combattimento ravvicinato, non valgono molto e durano  ben poco. Si muovono un po' più lentamente dei loro colleghi di fanteria. Gli  arcieri fabbricano da soli i propri archi e le frecce. @L@LCarri da guerra @LPer qualsiasi soldato, non v'è nulla di più pauroso che vedere una linea di  carri da guerra prepararsi all'attacco. I carri sono fondamentali per rompere le  formazioni protettive del nemico e, quando il fronte è spezzato, è più facile  distruggerlo. Ciascun guidatore riceve un carro quando lascia il reclutamento. @L@LQuando non combattono, i soldati preferiscono restare nel loro forte, a meno  che non ordini loro di uscire. Nei forti, i soldati possono godere della  compagnia dei loro commilitoni. Le lunghe campagne lontano dal forte abbassano  il morale della compagnia. @PI forti non richiedono strade o manodopera. Hanno un effetto molto negativo  sulla desiderabilità, quindi è meglio posizionarli fuori della città. @P@87Compagnia,&ordini @P@52Guerra @L@LPer ulteriori informazioni sull'arte della guerra nell'antico Egitto, clicca  @184qui."
        }
    }
    
    message_true_pyramid {
        id: 38,
        
        size [30, 28]
        title {
            text: "Vera piramide",
        }
        content {
            text: "La vera piramide è formata da un interno in @95pietra&normale e una  copertura di @95calcare, liscia e lucida. Gli @363scalpellini posano la pietra e  ne lucidano la superficie, mentre i @363carpentieri preparano le rampe  necessarie alla costruzione, quando la piramide si ergerà sempre più in alto.  Quando un @4deposito merci ha accumulato quattro blocchi di pietra, i manovali  trainano la slitta carica di tali blocchi fino al cantiere, dove sono attesi  dagli scalpellini. @PLe dimensioni della vera piramide sono piccola, media, grande, complesso di  piramidi e grande complesso di piramidi. @P@370Monumenti,&costruzione @P@373Supervisore&dei&monumenti @P@369Capo&cantiere @L@LSe vuoi sapere di più sulla storia della vera piramide, clicca @392qui."
        }
    }

    message_population_groth_and_sentiment {
        id: 39,
        
        size [30, 28]
        title {
            text: "Popolazione e umore cittadino",
            pos [15, 5]
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "L'umore cittadino è un indicatore della qualità di vita in città. I  fattori che contribuiscono a mantenerlo in buono stato sono: salari alti, tasse  basse, disponibilità di cibo e di lavoro. Tutti i cittadini si aspettano di  essere ben nutriti, di ottenere un lavoro e, inoltre, di essere ricompensati in  modo congruo e di pagare tasse ragionevoli. @PI cittadini sanno a quanto ammontano le tasse in altre città egizie. Se la  media del Regno cambia, ti sarà inviato un messaggio con la notifica del  cambiamento. @PPuoi far pagare tasse alte senza riscontri particolarmente negativi, se la  città è un ottimo luogo in cui vivere. Ai cittadini non pesa pagare qualcosa di  più in cambio di molto cibo, lavoro e buoni salari. I cittadini si arrabbiano,  però, se pensano che le condizioni di vita siano ingiuste. Se metà di loro paga  tasse elevate e l'altra metà non ne paga affatto, l'umore cittadino è destinato  a precipitare. @PSe non riesci a soddisfare le loro aspettative, in giro si spargerà ben presto  la voce. Se la tua città ha una cattiva reputazione, così come viene espressa  dal basso umore dei suoi residenti, gli immigranti potenziali decideranno di  rimanere dove sono o di trovarsi un'altra nuova casa. Se la reputazione della  tua città scade troppo in fretta, alcuni dei residenti potrebbero decidere di  andare in cerca di una vita migliore. @PIl tuo supervisore capo conosce i sentimenti dei cittadini. Leggi il rapporto  sull'umore cittadino e compi i passi necessari per migliorare le condizioni di  vita in città. @L@167Popolazione @L@388Immigrazione"
        }
    }
    
    message_game_concept_workers {
        id: 40,
        
        size [30, 28]
        title { text: "Lavoratori" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "La maggior parte degli edifici necessita di impiegati. Quando  costruisci un nuovo edificio che richiede degli impiegati, verrà inviato un  rappresentante alla ricerca di lavoratori nel vicinato. Se s'imbatte in  abitazioni occupate e se in città vive gente in cerca di lavoro, l'edificio che  lo ha inviato otterrà i suoi lavoratori. Se non riesce a trovare personale per  l'edificio che lo ha inviato, continuerà la sua ricerca. @L@LPer ulteriori informazioni sulla vita lavorativa dell'antico Egitto, clicca  @155qui."
        }
    }

    message_game_concept_scribes {
        id: 41,
        
        size [30, 28]
        title { text: "Scribi" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "Quando la tua città sarà in grado di offrire i beni migliori, ottimi  servizi e, cosa più importante, istruzione, alcuni cittadini diventeranno  scribi. Gli scribi non lavorano, ma pagano molte tasse. Puoi osservarli quando  vanno a zonzo per la città in cerca di divertimento. @PQuando compaiono i primi scribi, la domanda di beni può aumentare, ma la forza  lavoro diminuisce. Se in città non arrivano nuovi immigranti per occupare i  posti vacanti, devi cercare di attirarli. @P@387Scribi @P@168Società"
        }
    }

    message_game_concept_walkers {
        id: 42,
        
        size [30, 28]
        title {
            text: "Passanti",
        }
        content {
            text: "Praticamente tutte le persone che camminano per le strade della città si spostano con un obiettivo in mente. Alcune devono spostare merci di vario tipo, altre si occupano di fornire servizi alle case o agli edifici che visitano, altre ancora sono in arrivo o in partenza dalla tua città. Soltanto pochissimi fortunati possono concedersi il lusso di passeggiare senza alcun particolare obiettivo. @PQuesti passanti possono essere divisi in due gruppi: coloro che hanno una meta e coloro che ne sono privi. Ciascuno di essi presenta un comportamento diverso. @L@LPassanti con meta @LColoro che camminano con una meta, lasciano il luogo d'impiego sapendo dove andare. Essi consultano la mappa e individuano il cammino più breve per giungere a destinazione. Fra di essi troviamo compratori dei bazar, emigranti, immigrati e addetti alle consegne. @L@LPassanti senza meta @LColoro che si spostano senza meta, portano i loro beni e servizi di casa in casa e alcuni direttamente alle strutture cittadine. @PI passanti senza meta lasciano il loro edificio senza una destinazione specifica. Usciti dall'edificio, provano ogni volta una strada diversa. Da qui in poi, i loro spostamenti sono assolutamente imprevedibili. @POgni volta che i passanti senza meta arrivano a un incrocio, devono decidere quale direzione prendere. Non decidono sempre per la stessa: le abitazioni che hanno visitato in precedenza potrebbero non vederli per parecchio tempo. @PIl miglior modo di convogliare queste persone è pianificare attentamente la città. Dato che gli incroci concedono loro parecchia libertà, mantenendo basso il numero delle intersezioni puoi guidarli meglio dove preferisci. @PI @358blocchi&stradali sono un altro strumento utile per controllarli. Quando un passante senza meta incontra un blocco stradale, torna indietro. Coloro che sanno dove vogliono andare, invece, vi passano attraverso. @PCome esempi di passanti senza meta, si possono citare i venditori dei bazar, i trasportatori d'acqua, i sacerdoti e i medici. @PIn alcune circostanze, certi passanti senza meta si comportano come se avessero una precisa destinazione. Per esempio, i vigili del fuoco che si apprestano a domare un incendio o i conestabili intenti a difendere la città, si comportano come passanti con una meta precisa per fronteggiare certi pericoli. Però, in tutti gli altri casi agiscono come passanti senza meta. @L@LLa vita dei passanti @LI passanti senza meta hanno una giornata lavorativa di durata limitata. I loro spostamenti proseguono per un dato intervallo di tempo, trascorso il quale spariscono dalle strade per un po'. Se il loro datore di lavoro ha molto personale sottomano, invia in strada un altro passante senza meta quasi immediatamente. Invece, se l'edificio è a corto di forza lavoro, di solito passa del tempo prima che ne esca un nuovo passante senza meta.   @PI passanti con meta devono lavorare fino a quando non hanno terminato il loro incarico, anche se ciò significa attraversare tutta la città.   @PColoro che possono avere o non avere una meta, hanno una giornata lavorativa di durata limitata. Il tempo trascorso negli spostamenti verso la meta va sottratto al tempo che possono trascorrere girando senza meta. Questo fenomeno si nota soprattutto con gli animatori: i loro spettacoli vengono accorciati se il viaggio verso la meta è lungo. @PInfine, ricorda che la banchina che separa una pianura inondata dalla terra asciutta è ripida, fangosa e infida. Nessuno può raggiungere o lasciare una pianura inondata fino a quando non verrà costruita una @57strada che lo consenta. @L@LPredatori @LNon tutte le creature che si muovono nei pressi della città sono pervasi da sentimenti amichevoli. Per esempio, gli animali da preda in agguato vicino alla città non ci penseranno due volte a uccidere chiunque capiti nei loro paraggi. I conestabili faranno il possibile per uccidere questi animali, ma forse il sistema migliore è ricorrere all'intervento militare. Gli animali potenzialmente pericolosi sono: iene, ippopotami, coccodrilli, aspidi, scorpioni e leoni."
        }
    }

    message_employment_unemployment {
        id: 43,
        
        size [30, 28]
        title { text: "Lavoro e disoccupazione" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "Praticamente ogni edificio della città ha bisogno di impiegati. La  città non può provvedere ai suoi abitanti senza una forza lavoro. @PLa prima volta che costruisci un edificio che necessita di lavoratori, un  addetto al reclutamento vaga per le strade alla ricerca di potenziali impiegati.  Se transita nei pressi di qualche casa e, se la città dispone di persone in  cerca di lavoro, la sua ricerca ha successo e l'edificio che lo ha inviato avrà  i suoi impiegati. @PIl compito dell'addetto al reclutamento non è sempre così facile. Una delle  sfide più difficili per un governante è quella di bilanciare la forza lavoro con  il numero di posti disponibili. In un mondo perfetto, una città avrebbe l'esatto  numero di lavori per la gente che li richiede. Ma è difficile che questo accada  nella realtà. Una città avrà sempre troppi disoccupati o posti di lavoro  insufficienti, oppure troppi posti vacanti e pochi disoccupati. @PLa disoccupazione non fa bene alla città. I lavoratori disoccupati che non  hanno nulla da fare, potrebbero essere vittima di frustrazione e abbassare così  l'@39umore&cittadino. Potrebbero addirittura darsi al @36crimine. Il miglior  modo di affrontare la disoccupazione è quello di creare nuovi posti di lavoro.  In generale, la città non sarà danneggiata da qualche prodotto o servizio  superfluo. Qualche fattoria in più, più divertimenti e nuove scuole, biblioteche  o templi non possono fare che bene. Riducendo la disoccupazione, puoi aumentare  i livelli di prosperità e cultura. @PUn altro modo - anche se crudele - di fronteggiare la disoccupazione è quello  di ridurre la popolazione. Ad esempio, puoi distruggere le case spingendo  all'emigrazione. Anche questo sistema può avere effetti positivi sulla tua  città. Se distruggi le case di livello più basso, il valore generale delle  abitazioni aumenta. Tale aumento può accrescere il livello di prosperità. @PL'altro problema di impiego riguarda la mancanza di lavoratori, oppure la  sovrabbondanza di posti vacanti. La soluzione ideale per risolvere la mancanza  di lavoratori è quella di attirare nuovi immigranti. Costruisci nuove zone  residenziali o incoraggia lo sviluppo delle zone esistenti per ottenere  strutture più capaci. Assicurati anche che l'@39umore&cittadino sia alto.  Aumentare i salari oltre la media del Regno o abbassare le tasse possono essere  due metodi validi per attirare nuovi immigranti. @PMentre attendi un nuovo flusso di immigrazione, lavora insieme al tuo  @24Supervisore&commerciale e al @20supervisore&del&lavoro per alleviare il  problema della mancanza di lavoratori. Visita il supervisore commerciale e  chiudi tutte le industrie che puoi per un certo periodo di tempo. In questo modo  puoi liberare forza lavoro e impiegarla in altri posti. Se non vuoi chiudere  completamente un'industria, puoi demolirne solo alcuni edifici.   @PConsulta il supervisore del lavoro per impostare le relative priorità.  Impostando la massima priorità ai lavori fondamentali, assicura che i cittadini  ricevano ciò che occorre per vivere. @PUn altro metodo, poco ortodosso e ancor meno conveniente, per rimediare alla  mancanza di lavoratori è quello di indurre le case degli @41scribi a devolvere  in case di @40lavoratori. Danneggerai il livello di prosperità e diminuirai il  ricavo delle tasse, ma la forza lavoro aumenterà - al costo dei sogni e speranze  dei tuoi cittadini più facoltosi! @PAnche se la disoccupazione è una situazione stressante, una piccola quantità  di disoccupati è ciò che occorre per espandere la città, in quanto ti rende  disponibile la forza lavoro necessaria per nuovi edifici. Una disoccupazione  superiore al 5% causa invece dei problemi."
        }
    }
    
    message_drinking_water {
        id: 44,
        
        size [30, 28]
        title { text: "Acqua potabile" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "Una delle prime esigenze dei tuoi cittadini è l'accesso ad acqua potabile pulita. Le loro case non miglioreranno affatto senza almeno un po' di acqua. @PI @62pozzi e i @61serbatoi&d'acqua forniscono l'acqua ai cittadini. I pozzi sono le fonti d'acqua più rudimentali. Sono accettate dai tuoi cittadini quando la città è ai propri albori, ma la gente non si accontenterà dei pozzi molto a lungo e presto ti chiederà l'acqua dei serbatoi. @PI serbatoi d'acqua impiegano dei trasportatori per portare il prezioso liquido nelle case dei cittadini. Quando un trasportatore passa nei pressi di una casa, quella casa ha accesso all'acqua potabile. Tieni d'occhio i trasportatori d'acqua: essi sono @42passanti&senza&meta e possono non seguire sempre lo stesso percorso. Le case che precedentemente avevano accesso all'acqua possono perderlo, specialmente se modifichi la rete stradale in quei dintorni. @PSe la @56desiderabilità della zona circostante è sufficientemente alta, i lavoratori del serebatoio d'acqua si industrieranno per migliorare il suo aspetto e la sua efficienza. I trasportatori d'acqua dei serbatoi migliorati visiteranno più frequentemente la zona circostante. @PI pozzi e i serbatoi d'acqua devono essere costruiti su un terreno che sorge su una fonte d'acqua sotterranea, la cui presenza è indicata dalle macchie d'erba. @PLeggi la parte che riguarda la @53salute&pubblica per ulteriori informazioni sui benefici dell'acqua potabile."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,
        
        size [30, 28]
        title { text: "Cibo e fattorie" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "La via che porta al cuore dei tuoi cittadini passa attraverso le loro  pance. Fornendo loro cibo abbondante - e diversificato - puoi migliorare  l'@39umore&cittadino e la @53salute&pubblica.  @PIn Faraon sono previsti molti tipi di coltivazioni, tra cui @89grano,  @90melograni, @90ceci, @90lattuga e @90fichi. Inoltre, esistono due tipi di  fattorie: le fattorie dei campi di limo e le fattorie dei prati. Entrambe  richiedono l'accesso a una strada e forza lavoro, ma le somiglianze finiscono  qui. Le fattorie non sono le uniche fonti di cibo. Anche la @359caccia, la  @84pesca e l'@360allevamenteo&delle&mandrie contribuiscono a riempire i granai  cittadini. @L@LFattorie dei campi di limo @LPer capire come funzionano le fattorie dei campi coltivati, devi prima  comprendere il comportamento del Nilo. Ogni anno, di solito tra giugno e  settembre, il Nilo allaga le sue sponde. I campi di limo sono completamente  sommersi e non vi si può piantare nulla. Dopo pochi mesi, il Nilo inizia a  retrocedere, lasciando sul terreno un fango fertilizzante. Quando un campo  inondato riemerge, può essere nuovamente utilizzato per le coltivazioni. @G56 @PIl Nilo non straripa esattamente nello stesso momento dell'anno o esattamente  allo stesso modo. Alcune inondazioni sono migliori di altre. I Sacerdoti usano  il Nilometro per determinare la bontà del futuro straripamento e riportano le  loro previsioni al @31supervisore&capo. Onorando Osiride, dio dell'agricoltura e  del Nilo (vedi @51religione), puoi assicurarti ottime inondazioni ogni anno. @PPuoi costruire fattorie (strade e canali di irrigazione) sui campi coltivati  in qualsiasi mese dell'anno con l'eccezione del periodo di straripamento. Quando  costruisci una fattoria sui campi di limo, comparirà solo il campo, privo di  edifici, in quanto il Nilo distrugge qualsiasi edificio costruito sulle sue  rive. Poiché non possono costruire le loro case sui campi di limo, i contadini  hanno bisogno di un luogo dove radunarsi e ottenere la possibilità di lavorare.  I @8campi&di&lavoro assolvono tale funzione. I campi di lavoro inviano i  braccianti nelle fattorie per piantare e raccogliere le messi: le fattorie  resterebbero inutilizzate se non esistessero i campi di lavoro. Esiste un limite  sulla distanza coperta dai braccianti per raggiungere il posto di lavoro, quindi  non posizionare i campi di lavoro troppo lontano dai campi di limo. @PIl periodo migliore per costruire le fattorie è subito dopo la retrocessione  del Nilo. Potrai sfruttare al massimo la stagione della crescita fino  all'inondazione successiva, e la fattoria produrrà messi abbondanti. Le fattorie  costruite in altri periodi dell'anno produrranno di meno. @PIl fattore da considerare quando si costruisce una fattoria è la fertilità del  suolo. Il terreno più scuro e l'erba più rigogliosa segnano le zone più fertili.  Tale terreno, di solito, si trova nelle vicinanze del fiume. Allontanandoti dal  fiume, la terra diventa meno fertile. Le fattorie costruite sul terreno più  fertile producono più delle altre. Sui campi bonificati puoi costruire canali di  irrigazione per portare l'acqua nelle zone più lontane dal fiume, migliorando  quindi la fertilità del suolo, che potrebbe non essere rivitalizzato durante le  inondazioni più scarse. @PDato l'andamento annuale del Nilo, le fattorie dei campi di limo possono  produrre un solo raccolto all'anno. La sopravvivenza di una città può dipendere  dal numero di braccianti che raccolgono le messi e dalla disponibilità di spazio  pronto per conservarle. @L@LFattorie dei prati @LI campi bonificati non sono gli unici terreni fertili, anche se sono i più  estesi. Le fattorie possono anche essere costruite sui prati, contrassegnati da  vegetazione gialla. Più è densa la vegetazione, maggiore sarà la fertilità del  suolo e, quindi, il raccolto. Queste fattorie dispongono di un edificio proprio,  quindi non richiedono i braccianti dei campi di lavoro. Dato che la terra non è  inondata, queste fattorie lavorano tutto l'anno. Comunque, i prati sono meno  fertili dei campi di limo e le fattorie dei prati tendono a produrre raccolti  inferiori. Le fattorie dei prati possono quasi sempre avvantaggiarsi dei canali  di irrigazione. @L@LCaccia e pesca @LI cacciatori e i pescatori sfruttano le abbondanti risorse naturali  dell'Egitto. Entrambi partono dalle loro basi, catturano le loro prede e,  quindi, ritornano alla base per preparare il cibo. @PLa base dei cacciatori è il casotto da caccia. Dal casotto essi partono per la  caccia. I cacciatori cercano stormi di folaghe, struzzi, o branchi di antilopi.  Se noti alcuni di questi animali intorno alla tua città, costruisci un casotto  da caccia nei loro pressi. @PI pescatori si ritrovano ai moli di pesca dove si scambiano racconti  incredibili su ciò che si sono lasciati sfuggire. I moli, naturalmente, si  trovano sull'acqua e i pescatori richiedono i servizi dei cantieri navali per  costruire le loro barche. Quando hanno una barca, possono uscire a pesca. Non  tutte le città possono supportare la caccia o la pesca. Se noti dei pesci che  balzano fuori dell'acqua, la città può avere un'industria basata sul pesce.   @PBranchi e stormi sono limitati. La caccia e la pesca possono fornire cibo per  una popolazione ridotta, ma una popolazione più vasta non può sopravvivere solo  grazie al pesce e alla selvaggina. @L@LAllevamento bestiame @LGli allevamenti di bestiame sono un'eccellente fonte di cibo. Si possono  allestire su qualsiasi tipo di terreno - non solo quello fertile - risparmiando  così la terra coltivabile per la produzione di altro cibo. Le mandrie consumano  paglia, il prodotto di scarto delle @89fattorie&di&grano. Il numero di  allevamenti di bestiame che una città può avere è limitato solo dalla quantità  di paglia che la città può fornire al bestiame. @L@LDistribuzione del cibo @LI @3granai e i @2bazar sono gli intermediari tra i produttori di cibo e gli  abitanti della città. I granai contengono il cibo destinato alla popolazione e i  bazar lo distribuiscono casa per casa. @PQuando un produttore di cibo ha un quantitativo disponibile, un carrettiere  porta il cibo al granaio. I compratori dei bazar vanno al granaio per procurarsi  il cibo che i loro clienti richiedono. Essi possono trasportare più di un tipo  di cibo per volta. Quando i compratori ritornano al bazar con i loro prodotti, i  venditori dei bazar vagano nel circondario, portando il cibo alla popolazione. @PÈ molto importante avere granai e bazar a sufficienza. Se tutti i granai sono  pieni, il carrettiere porta il cibo a un @4deposito&merci, se quest'ultimo ha  l'ordine di accettare cibo. I compratori dei bazar non andranno nei depositi in  cerca di cibo (anche se vi si recheranno per cercare altri prodotti o cibo  importato). I compratori dei bazar prendono la maggior parte del cibo dai  granai. @PIl posizionamento di bazar e granai può essere difficoltoso. I granai devono  essere ubicati vicino ai produttori di cibo, così che i carrettieri non debbano  camminare a lungo. I bazar devono essere vicini ai granai, così che i compratori  possano mantenere i bazar ben riforniti. I bazar devono inoltre essere posti  vicino alle case che servono. Tutte queste strutture rendono le zone  residenziali indesiderabili, quindi il loro posizionamento è sempre il risultato  di un compromesso. @PCon il crescere della tua città, potresti essere costretto a costruire granai  lontano dai produttori di cibo per far sì che i bazar della periferia possano  ottenere il cibo di cui hanno bisogno. In questo caso, usa gli ordini speciali  dei granai per assicurarti che ricevano il cibo. @L@LImportare il cibo @LAlcune città non possono produrre cibo a sufficienza per sfamare i cittadini,  oppure possono produrne una varietà limitata, quindi hanno bisogno di importarlo  da altre città. Il cibo importato è consegnato ai depositi merci, dove i  compratori dei bazar possono trovarlo e portarlo in negozio. @L@LGli argomenti correlati sono raggiungibili tramite gli hyperlink presenti  nel testo (le parole che fungono da hyperlink sono di colore diverso). Leggendo  le informazioni su questi argomenti potrai comprendere meglio il concetto di  produzione e distribuzione del cibo. @L@LSe vuoi conoscere la storia del cibo nell'antico Egitto, clicca @150qui.  Puoi ottenere altre informazioni sugli effetti del Nilo cliccando @157qui."
        }
    }

    message_game_concept_industry {
        id: 46
        
        size [30, 28]
        title { text: "Industria" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "L'industria è probabilmente il più grande settore impiegatizio di una città. I cittadini usano alcuni dei prodotti industriali per migliorare la qualità di vita. Altri prodotti possono essere @47commerciati per trarne profitto.   @PLe industrie di una città sono molteplici ma tutte condividono aspetti simili. Hanno bisogno di manodopera e, infatti la mancanza di lavoratori può comprometterne l'efficienza. Tutte le industrie richiedono l'accesso a una strada, così che i lavoratori possano raggiungerle. @PAlcune industrie producono materiali grezzi che possono essere lavorati dalle fabbriche per creare prodotti finiti. Queste industrie sono le @92cave&d'argilla, le @361miniere&di&gemme, le @93miniere&di&rame, i @94taglialegna e i @94raccoglitori&di&canne. Anche le @91fattorie&d'orzo, le @91fattorie&di&henna e le @91fattorie&di&lino producono materiali grezzi per l'industria. In più, le @89fattorie&di&grano, oltre a produrre cibo, producono anche la paglia. Un produttore di materiali grezzi in genere può supportare due fabbriche di prodotti finiti. I materiali grezzi possono essere commerciati, ma non permettono margini elevati quanto i prodotti finiti. @PLe industrie che trasformano i materiali grezzi in altri prodotti (a volte chiamate fabbriche o laboratori) sono le @96distillerie, gli @99orafi, le @60tessitorie, le @97fabbriche&di&papiro, i @1vasai, le @364fabbriche&di&mattoni, le @473fabbriche&di&lampade, le @470fabbriche&di&vernici, le @98armerie e le @98fabbriche&di&carri&da&guerra. I loro prodotti finiti possono essere usati in città oppure commerciati sul mercato libero. @P@95Le cave e le @93miniere&d'oro sono diverse dalle altre industrie, in quanto i loro prodotti grezzi sono anche prodotti finiti. I @82cantieri&navali costruiscono un prodotto finito (le navi) lavorando un materiale grezzo (il legno), ma le navi non possono essere commerciate sul mercato libero. @PGli addetti alle consegne portano i prodotti alla corretta destinazione. Gli addetti impiegati dai produttori di materiali grezzi cercano prima di tutto di portare il loro carico alle fabbriche che ne hanno bisogno, preferendo quelle più vicine. Se nessuna industria ha bisogno del materiale, l'addetto alle consegne si dirige al più vicino @4deposito&merci che abbia spazio per contenerlo. Se nessun deposito merci è disponibile, l'addetto si ferma finché non si libera un po' di spazio. Gli unici addetti alle consegne che si comportano diversamente sono il carrettiere delle miniere d'oro gli addetti al trasporto dei blocchi di pietra. Il carrettiere delle miniere d'oro porta l'oro esclusivamente a Palazzo, mai il deposito merci. Dato che la pietra non può essere trasformata in un altro prodotto, questa viene portata direttamente a un deposito merci. @G74 @PAlcuni edifici cittadini hanno bisogno di prodotti industriali per funzionare. Tra questi ci sono le @70biblioteche, le @68scuole&degli&scribi, le @74taverne&Senet, i @88reclutatori, le @66camere&mortuarie, la @363gilda&degli&artigiani e la @363gilda&dei&carpentieri. Gli addetti alle consegne dei produttori cercano di portare i loro carichi agli edifici che ne hanno bisogno. Se nessuno è disponibile, porteranno il carico al deposito merci o rimarranno fermi finché non si libera un po' di spazio. I carrettieri percepiscono comunque il loro salario, anche se rimangono fermi senza fare niente. @PPer verificare se le tue industrie hanno dei problemi, usa la @18tabella&Problemi. questa tabella ti mostra quali edifici industriali non funzionano a dovere e perché.  @PCliccando con il pulsante destro del mouse su un edificio puoi sapere qual è il suo stato di produzione. Puoi sapere se l'edificio ha tutti gli impiegati e a che punto del processo produttivo si trova. Se ci sono dei problemi, il pannello ti dirà quali sono.   @PClicca su uno degli hyperlink qui sopra (gli hyperlink sono le parole in blu) per sapere di più su ogni industria. @L@LClicca @151qui per leggere la storia dell'industria nell'antico Egitto."
        }
    }

    message_game_concept_trade {
        id: 47,
        
        size [30, 28]
        title {
            text: "Commercio",
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "Nessuna città è completamente autosufficiente. Il commercio porta nella tua comunità i prodotti che questa non è in grado di produrre. L'esportazione dei prodotti porta molti soldi - spesso più di quanti si possano guadagnare con le tasse. Data la sua importanza, la tua città dovrebbe iniziare a commerciare non appena ha soddisfatto i bisogni primari dei suoi cittadini. @PLa @32mappa&del&Regno mostra quali città commerceranno con te. Le città interessate sono indicate da una bandiera. Clicca su una di queste città per sapere quali prodotti vogliono comprare o vendere. I puntini blu mostrati in un angolo del simbolo del prodotto indicano la quantità che si desidera importare o esportare in un anno. Un puntino significa che la merce non è molto trattata, mentre tre puntini indicano una forte propensione al commercio di quel prodotto. Questi livelli possono modificarsi secondo i cambiamenti di offerta, domanda e pressioni politiche in Egitto.  @PClicca sul pulsante 'Apri via commerciale' per spendere i fondi necessari a stringere un nuovo accordo. Aprire una via commerciale può costare molto, ma con il tempo può portare molto profitto. @PQuando hai aperto una via commerciale, visita il tuo @24supervisore&commerciale per dare inizio alle trattative. Clicca sul pulsante 'Mostra prezzi' per sapere i prezzi di vendita e di acquisto di ciascun prodotto. Noterai che i prodotti si vendono per somme inferiori al prezzo di acquisto. La differenza di prezzo copre le spese dei mercanti che giungono in città. @L@LImportazione @LPer importare un prodotto, clicca sul bene che preferisci. Quando l'hai selezionato, hai due possibilità. Puoi decidere personalmente la quantità da tenere nei magazzini e ordinare al supervisore commerciale di comportarsi di conseguenza; oppure, puoi far sì che sia il supervisore commerciale a decidere tutto. Costui continuerà a importare il prodotto finché le quantità in magazzino non giungono al livello impostato, oppure finché il socio in affari non raggiunge il suo limite annuale.  @PAlcuni beni richiesti dalla tua città possono solo essere importati, per esempio il marmo bianco usato per costruire monumenti e l'olio per le @473lampade. Per far raggiungere alle @56case della città il livello più elevato, dovrai anche importare beni di lusso. @PLe importazioni possono diventare molto costose, quindi tieni sotto controllo i tuoi @4depositi&merci. Se noti che i depositi merci sono colmi di un certo prodotto importato, risparmia i soldi e non importarlo più finché le scorte non si esauriscono. Inoltre, importare i materiali grezzi è meno costoso che importare i prodotti finiti. Sul ungo termine, la città risparmierà dei soldi se le sue fabbriche producono prodotti finiti lavorando materiali grezzi importati. @L@LEsportazione @LPer esportare un prodotto, clicca sul bene che vuoi esportare. Quindi, decidi la quantità da tenere come scorta oppure lascia che sia il supervisore commerciale a farlo. Le eccedenze saranno esportate fino al raggiungimento della quota annuale del tuo cliente. Tieni a mente che alcuni dei prodotti che esporti sono desiderati anche dai tuoi cittadini, quindi assicurati di tenerne una scorta per le loro esigenze. Controlla spesso i bazar e le case dei tuoi cittadini per sapere se dispongono di una fornitura sufficiente del prodotto che esporti. Inoltre, assicurati che gli edifici che richiedono una certo prodotto finito ne abbiano una scorta sufficiente. Se le case o altri edifici fanno fatica a procurarsi un prodotto, probabilmente la città ne sta esportando troppo. @LA volte una città può importare o esportare lo stesso prodotto. Ciò permette una maggiore flessibilità per la pianificazione industriale. Se vuoi aumentare le entrate cittadine, dedica la forza lavoro alla produzione del prodotto da esportare. Se invece vuoi utilizzare la forza lavoro per un altro scopo, allora importa il prodotto. La città non può mai importare e contemporaneamente esportare uno stesso prodotto, e non può trarre profitto importando un prodotto e, quindi, esportandolo in un'altra città. I compratori pagano più di quanto i venditori ricevono, quindi la città perderebbe solo denaro se operasse da semplice intermediaria. D'altra parte, importare materiale grezzo ed esportare il relativo prodotto finito è normalmente un'ottima operazione commerciale. @PI mercanti giungono nella tua città con una carovana o con una nave. Prima che tu possa commerciare con loro, devi costruire un deposito merci. Oltre al deposito merci, devi costruire anche un @83molo. Le navi mercantili conducono le trattative presso i moli: al loro arrivo i carrettieri del molo scaricheranno i prodotti e li porteranno nei depositi merci."
        }
    }
    
    message_game_concept_money {
        id: 48,
        
        size [30, 28]
        title {
            text: "Denaro",
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "Non puoi costruire una città senza il denaro, e la quantità conservata nei suoi forzieri è un buon indicatore del suo successo. La città guadagna soldi imponendo le tasse, esportando prodotti, ricevendo doni e, se possibile, estraendo l'oro. Questi ovvi argomenti sono illustrati verso la fine della sezione. Per prima cosa, devi imparare tutti i trucchi della gestione finanziaria.  @L@LDebiti @LLa prima volta che rimani senza, altri governanti egizi potrebbero concederti un dono una-tantum di qualche deben. Questo fatto non ti penalizza in alcun modo e i governanti non si aspettano di essere ripagati. Consideralo un avvertimento, però, perché forse è il caso che la tua città amministri meglio i suoi fondi. @PSe spendi tutti i soldi ricevuti in dono una-tantum, o se non ricevi alcun aiuto gratuito, le tue finanze possono accumulare fino a 5.000 deben di debito. I numeri gialli indicano che la tua città ha un debito. @PBrevi e sporadiche occasioni di debito sono spesso inevitabili e non ti danneggeranno se riporti velocemente in positivo il tuo bilancio. I debiti prolungati possono invece costarti la partita. @L@LConseguenze dei debiti @LOgni mese che il tuo tesoro è in debito ti costa degli interessi, che sono automaticamente aggiunti al tuo debito. Maggiore è il debito, maggiori saranno gli interessi da pagare e il tuo debito crescerà ulteriormente.  @POgni qual volta che la tua città giunge alla fine dell'anno lamentando dei debiti, non puoi pagare le tasse annuali (vedi poi). Non pagare le tasse non ti costa soldi, ma diminuisce un po' il tuo @35livello&del&Regno. L'effetto peggiora se non paghi le tasse per più anni consecutivi. @PSe non riesci a riequilibrare il tuo bilancio (anche per poco) per i 12 mesi successivi al primo debito, il tuo livello del Regno ne soffrirà, in quanto gli altri governanti egizi perderanno fiducia nella tua abilità di amministratore. La tua prima penalità per un debito mancato, anche se dolorosa, probabilmente non causerà danni irreparabili. Se ancora non hai raggiunto un bilancio positivo allo scadere del secondo anno, il tuo livello del Regno diminuirà notevolmente e negli anni a seguire sarà sempre peggio. @L@LRipagare i debiti @LI debiti sono chiaramente un problema serio e, se non puoi evitarli, devi cercare di ripagarli il più presto possibile. I metodi per aumentare gli introiti sono descritti più avanti, ma soprattutto devi evitare di spendere il tuo credito limitato per qualsiasi cosa che non porti profitto. Le esattorie, le industrie che producono per l'esportazione e le nuove vie commerciali con città che comprano i tuoi prodotti possono rivelarsi delle spese sagge.  @L@LTributo annuale @LAlla fine dell'anno, la tua città deve pagare una tassa al Regno, ovvero il 'tributo'. L'ammontare del tributo dipende dalla tua liquidità, quindi inizierà con poco e aumenterà man mano che la città crescerà come popolazione e ricchezza. Visita il tuo @30supervisore&finanziario per sapere a quanto ammonta il tributo da pagare.  @PSe finisci l'anno con dei deben nei forzieri cittadini, il pagamento del tributo è automatico. Non puoi decidere altrimenti. Ogni volta che termini l'anno con dei debiti, però, la tua città non può pagare il suo tributo e il tuo @35livello&del&Regno precipita. La penalità per un anno di tributo mancato non è eccessiva, ma cresce sempre di più con il secondo e gli anni successivi. Questo fatto riflette lo scadere della tua reputazione di amministratore tra la tua gente.  @L@LTasse @LLe tasse caricano sui cittadini gli oneri dei servizi forniti dalla città. I cittadini non lamenteranno il pagamento delle tasse se non sono troppo esose. Il livello iniziale del 9% è una buona percentuale, ma puoi modificarla, aumentandola o diminuendola, quando vuoi. Per modificare il livello, visita il tuo supervisore finanziario oppure clicca con il pulsante destro del mouse sul Palazzo. La diminuzione delle tasse porta gioia e apprezzamento. L'aumento provoca lamentele e può portare all'esodo di massa dei tuoi cittadini. @PA volte l'aumento delle tasse può essere necessario. Se ti accorgi che la tua città sta per indebitarsi, puoi aumentare le tasse per scongiurare l'evento. Ma per risolvere il problema una volta per tutte, è meglio trovare una soluzione a lungo termine più adeguata. Un livello di tassazione elevato può peggiorare l'@39umore&cittadino. @PAnche se ai cittadini non importa pagare le tasse, certo non si recano spontaneamente all'esattoria. Per riscuotere le tasse, la città deve avere un @77Palazzo e, quindi, una @80esattoria. @PIl supervisore finanziario conosce la percentuale di popolazione registrata come contribuente, e qual è l'introito mancato per insufficienza di esattori. Usa la @18tabella&Tasse per individuare le zone della città che sta evadendo le tasse. Inoltre, assicurati di riscuotere i tributi in modo equilibrato. Se una parte degli abitanti paga tutte le tasse e un'altra non ne paga per niente, l'@39umore&cittadino precipiterà e il @36crimine potrebbe insorgere. @L@LCommercio @LIl denaro derivato dall'esportazione è probabilmente la principale fonte di guadagno della città. Apri una via commerciale non appena ti è possibile. È molto importante che tu conosca bene i meccanismi di esportazione, quindi, se ci sono dei problemi, leggi le informazioni sul @47commercio. @L@LEstrazione dell'oro @LAlcune città coniano il proprio denaro. Se scopri delle pepite di metallo incastonate in una zona rocciosa, potresti essere in grado di costruire una @93miniera&d'oro. Non esaltarti troppo in fretta; il minerale potrebbe rivelarsi @93rame, comunque abbastanza prezioso, ma certo non ambito quanto l'oro. Clicca sul pulsante industria del Pannello di controllo, quindi seleziona i materiali grezzi per scoprire quali sono i metalli preziosi che la tua città può estrarre.  @PLe miniere d'oro funzionano come le altre @46industrie, ma il loro prodotto viene consegnato al Palazzo, dove viene trasformato in deben, e non è mai portato nei depositi merci. @L@LRisparmi di famiglia e salario @LAnche tu, come il resto dei cittadini, puoi guadagnare dei soldi. Sei pagato per il tuo impegno come governante e puoi percepire un salario non appena costruisci una @78magione. Il tuo salario è pagato con le finanze cittadine ed è commisurato alla tua esperienza. Puoi decidere di modificare il tuo salario, ma se pretendi più di quanto ti è dovuto, il tuo @35livello&del&Regno potrebbe crollare. Puoi anche percepire uno stipendio inferiore o non percepirlo affatto, cosa che può impressionare le persone e aumentare così il tuo livello del Regno. Se la tua città lamenta delle difficoltà finanziarie, rinunciare al salario è un buon metodo per ridurre i costi. @PPuoi trasferire i risparmi di famiglia nei forzieri cittadini in qualsiasi momento - un buon modo per annullare o evitare un debito. Non puoi invece trasferire il denaro cittadino sul tuo conto. Sarebbe davvero troppo! @PI risparmi di famiglia possono anche acquistare un 'dono per l'Egitto'. Tale donazione alla gente d'Egitto o, a discrezione del tuo supervisore, ad altri governanti egizi, aumenterà immediatamente il tuo livello del Regno, anche se di poco. Fai attenzione quando usi questo stratagemma. Quando la catena dei doni è iniziata, i beneficiari tendono ad aspettarseli con continuità. Negare ciò che si aspettano può danneggiare il tuo livello del Regno. @PPer ulteriori informazioni sui tuoi risparmi personali, puoi leggere la sezione che tratta del @22supervisore&politico."
        }
    }

    message_game_concept_entertainment {
        id: 49,
        
        size [30, 28]
        title {
            text: "Intrattenimento",
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "Il troppo lavoro e l'assenza di svaghi ha reso Imhotep un ragazzo annoiato. Offri alla tua città un po' di divertimento, così da renderla un luogo piacevole. @P@71Baracconi, @72palchi, @73padiglioni, @74taverne&Senet e @479zoo offrono il divertimento che la gente desidera. Quando la tua città è ancora agli inizi, i cittadini si accontentano di piccoli divertimenti, quali i baracconi. Quando la tua città cresce, così crescerà anche la domanda di divertimento e i cittadini si aspetteranno svaghi di ogni tipo. Il tuo @28supervisore all'intrattenimento ti aiuterà a capire i gusti dei tuoi cittadini. @PLa maggior parte degli artisti deve prima essere addestrata nei @75centri&di&addestramento. I giocolieri si esercitano nelle scuole dei giocolieri, i musicanti nei conservatori e i danzatori nelle scuole di danza. Quando sono formati, gli artisti usciranno dai centri di addestramento e si dirigeranno nelle zone di divertimento. I maestri Senet non sono addestrati in alcun centro. @PI tuoi cittadini capiranno di avere accesso ai divertimenti quando vedranno gli artisti passare vicino alle loro case (clicca @42qui per ulteriori informazioni sui passanti). Gli artisti passanti provengono dalle zone di divertimento in attività. Gli artisti, inoltre, transitano per le strade quando si recano dai centri di addestramento alle zone di divertimento. Tieni questi fatti bene a mente quando pianifichi le tue costruzioni. Se posizioni una zona di divertimento e i centri di addestramento alle estremità opposte di un quartiere, un artista dovrà per forza passare vicino alle case per raggiungere la zona di divertimento, portando con sé i benefici dell'allegria. Fai però attenzione a non posizionare i Centri di addestramento troppo lontani dalle zone di divertimento: se un artista deve camminare molto, il suo spettacolo durerà poco e la zona di divertimento sarà spesso inattiva, senza alcun beneficio per nessuno.   @PLa taverna Senet e lo zoo richiedono entrambi una certa scorta di beni. La taverna Senet ha bisogno di @96birra per dissetare i suoi clienti, mentre lo zoo ha bisogno di @89paglia e di @359carne per nutrire a dovere gli animali. @L@LClicca @165qui per ulteriori informazioni sui divertimenti dell'antico Egitto."
        }
    }

    message_game_concept_education {
        id: 50,
        
        size [30, 28]
        title {
            text: "Istruzione",
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "L'istruzione è un privilegio dei ricchi. Costoro sanno che gli  insegnamenti delle @68scuole&degli&scribi sono la strada che conduce a una vita  migliore per i loro figli e inoltre apprezzano molto la possibilità di accedere  alle @70biblioteche. @PLe Scuole degli scribi e le biblioteche non possono funzionare senza il  @97papiro. Prima di poter costruire una biblioteca, i tuoi @4depositi&merci  devono contenere papiro sufficiente a riempire i suoi scaffali di pergamene. I  @42passanti di entrambe le strutture portano con loro i papiri per diffondere  gli insegnamenti. La città deve fabbricare o @47importare il papiro per  mantenere in funzione tali strutture. @PVisita il tuo @27supervisore all'istruzione per assicurarti che la tua città  risponda alle esigenze educative dei cittadini.  @PLa presenza di biblioteche e scuole sufficienti contribuisce al tuo  @35livello&culturale. @L@LScopri gli altri modi in cui gli antichi Egizi passavano il tempo, cliccando  @165qui."
        }
    }

    message_game_concept_relition {
        id: 51,
        
        size [30, 28]
        title {
            text: "Religione",
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "In Egitto ci sono cinque divinità principali: Osiride, dio  dell'agricoltura e del Nilo, Ptah, dio degli artigiani, Ra, dio del Regno, Seth,  dio della distruzione e Bast, dea della casa. Appagare gli dei porta dei  benefici, ignorarli provoca gravi conseguenze. Il tuo @29supervisore&religioso e  dei @29templi conosce l'umore degli dei, quindi consultalo spesso. @PMolte città hanno degli dei patroni. Un dio patrono si aspetta molto dalla  città sua protetta, comunque ben più delle altre divinità locali. Le divinità  locali richiedono meno di un dio patrono, ma possono influenzare la città allo  stesso modo, nel bene e nel male. Alcuni dei sono sconosciuti in una città e,  quindi, possono essere ignorati senza conseguenze. @PIl miglior modo per appagare gli dei è quello di dedicare loro molti  @67templi&e&santuari. Il dio patrono si aspetta di avere più santuari degli  altri dei. Ogni divinità locale si aspetta meno templi e santuari del dio  patrono, ma pretende di essere rispettata al pari delle altre.  @PGli Dei possono anche essere appagati con delle festività, meglio se  grandiose. Le festività speciali e grandiose sono degli ottimi rimedi se una  particolare divinità si infuria con la città. Indici una festività in onore  della divinità offesa e la divinità si sentirà più sollevata, concedendoti più  tempo per erigere templi e santuari in suo onore, prima di scatenare la sua ira.  Visita il tuo @29supervisore&religioso per predisporre una festività. Nota che  finché non hai costruito una piazza delle festività, la città non può  celebrarne alcuna. Le festività grandiose richiedono inoltre che la città abbia  abbastanza @96birra nei suoi @4depositi&merci. Dato l'enorme impegno richiesto  dalla preparazione di una festività, una città può celebrarne solo due in un  periodo di 12 mesi. @POltre ai templi e ai santuari, puoi anche costruire un complesso di templi,  generalmente dedicato al dio patrono. Ogni città può avere un solo complesso di  templi. A volte, puoi costruire un complesso di templi per una divinità locale  se questa è divenuta particolarmente importante. Fai attenzione, però: il dio  patrono della città può diventare molto invidioso se un complesso di templi è  dedicato a un altro dio. @PI complessi di templi sono molto costosi, ma valgono bene la spesa. Un  complesso di templi in città comporta numerosi benefici e aumenta il  @35livello&di&prosperità. Con un costo ulteriore, puoi anche aggiungere un  oracolo e un altare. I complessi e le loro strutture aggiuntive sono: @L@L@350complesso&templi&di&Osiride: @P Altare di Sebek @P Oracolo di Min @L@351 Complesso&templi&di&Ra @P Altare di Ma'at @P Oracolo di Horus @L@352 Complesso&templi&di&Ptah @P Altare di Amon @P Oracolo di Thoth @L@353 Complesso&templi&di&Seth @P Altare di Anubis @P Oracolo di Sekhmet @L@354 Complesso&templi&di&Bast @P Altare di Iside @P Oracolo di Hathor @L@LOffrire ai cittadini più luoghi di culto a dei diversi contribuisce ad  aumentare il @35livello&culturale della città. @L@LPer ulteriori informazioni sulla religione dell'antico Egitto, clicca  @399qui."
        }
    }

    message_game_concept_war {
        id: 52
        
        size [30, 28]
        title {
            text: "Guerra"
        }
        subtitle {
            text: "Concetto di gioco",
        }
        content {
            text: "La guerra è una minaccia costante in tutto l'Egitto. A volte, gli  invasori di altri paesi giungono in Egitto spinti da sogni di gloria. Altre  volte, le diatribe lungo i confini egizi causano lotte tra città o persino vere  e proprie guerre civili. Occasionalmente, il Faraone stesso decide di dichiarare  guerra a un nemico giurato o ai suoi alleati ribelli. @PPuoi fare molte cose per preparare e proteggere la città dagli orrori della  guerra. Costruisci @85strutture&di&difesa per sigillare i confini alle forze  degli invasori. Costruisci @37forti, @356navi&da&guerra e @357navi&da&trasporto  per attaccare i nemici che oltrepassano i confini della città. @PIl tuo @21supervisore&militare ti avvertirà degli attacchi imminenti e in più  riceverai @34messaggi con le informazioni sui movimenti del nemico. Puoi  tracciare il cammino di un nemico in avvicinamento sulla @32mappa&del&Regno. @PFai attenzione a non provocare alcun attacco. Se gestisci male la tua città o  scateni l'ira degli altri governanti egizi, il tuo @35livello&del&Regno  sprofonderà. Se il livello del Regno scende troppo, la tua città potrebbe essere  attaccata. @PLa guerra non si limita a interessare i dintorni della tua città. In diverse  occasioni, l'Egitto è impegnato in battaglie su tutto il suo territorio e anche  oltre. A volte, un'altra città o il Faraone stesso può richiedere l'aiuto di  truppe o navi per sconfiggere un nemico. Invia le truppe per tale servizio del  Regno visitando il tuo supervisore militare, selezionando le compagnie o le navi  per il servizio estero e inviandole come richiesto. Se più di una città richiede  il tuo aiuto, dovrai visitare il tuo @22supervisore&politico per scegliere la  città più appropriata. @L@LPer ulteriori informazioni sui nemici dell'antico Egitto, clicca @181qui."
        }
    }

    message_tutorial_health {
        id: 53
        
        size [30, 28]
        title { text: "Sanità" }
        subtitle { text: "Concetto di gioco" }
        content {
            text: "La scarsa igiene pubblica può scoraggiare gli immigranti e può  causare la morte dei tuoi cittadini. Fai in modo che i tuoi cittadini siano  sempre in forma. Se non prendi le dovute precauzioni, essi potrebbero patire le  conseguenze di molti disastri sanitari. @PPer mantenere i tuoi cittadini in salute, assicurati che abbiano accesso a  cibo in abbondanza e a un @64medico. Meglio, quindi, se la loro dieta alimentare  è diversificata. Anche l'accesso alle @66camere&mortuarie migliora l'igiene  generale. L'acqua potabile dei @61serbatoi&d'acqua e l'accesso a una  @65farmacia aiutano a ridurre il rischio di malaria. La salute generale della città è determinata dalla salute dei singoli cittadini, quindi assicurati di provvedere accessi adeguati alle cure mediche per tutti gli abitanti. @POltre alla malaria, la città può essere colpita dalla malattia e dalla  pestilenza. Con una attenta pianificazione e una cura costante della salute  pubblica, questi disastri sanitari possono essere evitati. @L@LMalattia @LLa malattia affligge le case che non sono regolarmente visitate da un dottore  e che non hanno un'adeguata fornitura di cibo. La malattia colpisce le case  individualmente e non si diffonde altrove. Comunque, se un intero quartiere gode  di uno scarso accesso al medico e al cibo, la malattia potrebbe colpire più di  una casa. @PUsa lo @18tabella&Rischi per individuare le case inclini alla malattia.  Costruisci più ambulatori medici in tali aree e assicurati che i @2bazar  riforniscano le case con cibo. Puoi usare la @18tabella&Medico per sapere quali  case hanno accesso a un medico e la @18tabella&Bazar per individuare quelle  visitate dai venditori. @L@LMalaria @LLa malaria è uno dei rischi della vita nei pressi di corsi d'acqua. Le case  vicine ai fiumi e alle paludi sono quelle più a rischio. Come la malattia, la  malaria colpisce le case individualmente ma, diversamente dalla stessa, la  malaria può diffondersi nel vicinato. Per combattere il rischio di malaria,  costruisci molte farmacie nelle zone più a rischio e assicurati che le case  ricevano l'acqua da un serbatoio d'acqua. Usa lo @18tabella&Malaria per  individuare le case più a rischio di malaria. @L@LPestilenza @LLe pestilenze scoppiano quando la salute pubblica è scarsa, indipendentemente  dalla salute delle case singole. L'unica cosa che puoi fare per evitare le  pestilenze è mantenere la salute pubblica su livelli accettabili. Non bisogna confondere le piaghe con le @494Piaghe&principali, che sono provocate da fattori esterni al tuo controllo, ma non al livello igienico generale della città. @PQuando scoppia una pestilenza, il contagio inizia da una casa. Uno degli  abitanti colpiti, cammina per le strade in preda al delirio, infettando tutte le  case a cui si avvicina. Nel giro di un mese soccomberà alla mortale malattia. Un  erborista di una farmacia può sanare tutti gli infetti che incontra. @PNessuna tabella può mostrarti quale casa ospiterà la prima vittima della  pestilenza, perché essa non è legata alle condizioni di una particolare casa o  un quartiere. @L@PSe una casa si infetta, tutta la gente che la abita morirà. La casa rimane  infetta per due mesi, durante i quali nessun immigrante potrà usarla. Dopo due  mesi, la casa viene purificata e diventa di nuovo vivibile. Saranno presenti  anche tutti gli oggetti posseduti dalla precedente famiglia. @PAnche se incluso tra gli edifici sanitari, l'ambulatorio del dentista  contribuisce solo ad aumentare il valore di una zona e non ha alcun effetto  sulla salute pubblica. @PIl tuo @26supervisore&sanitario ti aiuterà a tenere in forma i tuoi  cittadini."
        }
    }

    message_bent_pyramid {
        id: 54,
        
        size [30, 28]
        title {
            text: "Piramide sghemba",
        }
        content {
            text: "Ispirati dal sole, gli architetti che idearono la piramide sghemba  volevano creare un gigantesco obelisco con i lati obliqui, per rappresentare un  raggio di sole. Affinché brillasse di luce solare, i lati della piramide  venivano lucidati. @PPer costruire una piramide sghemba, ti occorrono forniture di @95pietra e  @95calcare, nonché i manovali dei @8campi&di&lavoro. Quando nei @4depositi&merci  sono pronti almeno quattro blocchi di pietra o di calcare, i manovali li  caricano su una slitta che trainano presso il cantiere. Per posare le pietre a  regola d'arte, sono necessari i servizi della @363gilda&degli&scalpellini. La  @363gilda&dei&carpentieri costruisce le rampe con il legno che viene portato  presso la loro sede. @PLe piramidi sghembe sono di due dimensioni. Per ulteriori informazioni  consulta le sezioni @370costruzione&dei&monumenti, @373supervisore&dei&monumenti  e @369capo&cantiere. @L@LSe vuoi sapere di più sulla storia della piramide sghemba, clicca @392qui."
        }
    }

    message_brick_core_pyramid {
        id: 55,
        
        size [30, 28]
        title {
            text: "Piramide con interno in mattoni",
        }
        content {
            text: "Le piramidi con l'interno in mattoni sono le più complicate da  costruire. Esse richiedono tre tipi di materiale da costruzione e i servizi di  tutte e tre le gilde di costruttori. Ti occorrono @364mattoni, @95calcare e  @94legno e i servizi della @363gilda&dei&muratori, @363gilda&degli&scalpellini e  @363gilda&dei&carpentieri. Ti sono, inoltre, necessari i manovali dei  @8campi&di&lavoro per prelevare pietre e mattoni dai @4depositi&merci e quindi  trasportarle al cantiere. @PLe piramidi con l'interno in mattoni possono essere piccole, medie, grandi,  complesso di piramidi e grande complesso di piramidi. @PPer ulteriori informazioni, consulta le sezioni @370Costruzione&dei&monumenti,  @373Supervisore&dei&monumenti e @369Capo&cantiere. @L@LSe vuoi sapere di più sulla storia delle piramidi in mattoni, clicca  @392qui."
        }
    }

    message_housing_and_desirability {
        id: 56
        
        size [35, 32]
        title { text: "Abitazioni e desiderabilità" }
        content {
            text: "Il primo passo per costruire un quartiere è quello di scegliere una  zona residenziale. Ricorda che le case devono sorgere entro due spazi da una  strada. Quando hai scelto la zona, gli immigranti arriveranno per stabilirsi in  semplici capanne. Si nutriranno con ciò che offre la natura spontaneamente. Con  il passare del tempo, i cittadini si aspettano che la città soddisfi i loro  bisogni. Se soddisfi le loro richieste, i cittadini miglioreranno  automaticamente le condizioni delle loro case. La qualità delle case influenza i  @35livelli della città, evita che i cittadini emigrino e attira nuovi  immigranti. @PI bisogni fondamentali dei cittadini sono la disponibilità di  @44acqua&potabile e @45cibo dai @2bazar. Quando soddisfi tali richieste, vedrai  le capanne trasformarsi in abitazioni più stabili. @PDopo l'acqua e il cibo, i cittadini richiedono altri beni e servizi. Essi  desiderano @1vasellame, @96birra e @60tela da tenere in casa. I cittadini più  ricchi desiderano, inoltre, dei @99beni&di&lusso, come i gioielli. Se i loro  gusti diventano più raffinati, essi richiederanno anche un secondo tipo di beni  di lusso, generalmente importato. Oltre a tali beni, i residenti si aspettano  una disponibilità di servizi, come l'accesso a quelli @51religiosi, di  @49intrattenimento, @50istruzione e @53cure&mediche. Se fornisci tali beni e  servizi, i cittadini si sentiranno invogliati a migliorare le loro abitazioni,  che diventeranno strutture sempre più grandi e stabili. @PI residenti desiderano, inoltre, vivere in quartieri di prestigio. A questo  scopo, puoi piantare dei @79giardini e costruire @79statue, oppure pavimentare  le strade con i raffinati tasselli delle @79piazze. I cittadini apprezzeranno di  certo l'impegno con cui intendi migliorare il loro quartiere e, in cambio,  cercheranno di adeguare le loro abitazioni al prestigio del circondario. @PSe i cittadini desiderano vivere in quartieri di prestigio, è anche vero che  odiano vivere in quartieri poveri e malcurati. I cittadini si infuriano se le  loro case sono vicine a industrie o fattorie; preferiscono vivere lontano dagli  odori e dai rumori emessi da tali strutture. Inoltre, i cittadini ritengono che  le industrie rovinino il panorama. Se devi posizionare delle case vicino alle  industrie (e a volte sarà necessario per fornire il personale adeguato), cerca  di compensare la scarsa desiderabilità con giardini, statue, piazze e un buon  accesso a tutti i beni e servizi richiesti. In altre parole, dovrai rassegnarti:  non è possibile costruire una città senza la ricchezza derivata dalle industrie. @PI vantaggi delle case di buona qualità sono numerosi. Le abitazioni più  evolute hanno un effetto positivo sul @35livello&di&prosperità. Le case più  grandi ospitano più cittadini, la qual cosa permette un incremento della  popolazione - quindi la forza lavoro - senza dover designare altre zone  residenziali. Quando le case raggiungono i livelli più alti, i residenti  diventano @41scribi, ovvero cittadini che non lavorano, ma che pagano tasse in  abbondanza. @PPer sapere cosa occorre a ciascun edificio per evolversi, cliccaci sopra con  il pulsante destro del mouse. I suoi inquilini ti diranno senza riserve cosa  desiderano. @L@LGli antichi egizi vivevano in abitazioni di varie forme e qualità. Per  saperne di più, clicca @152qui."
        }
    }
    
    message_game_concept_roads {
        id: 57,
        
        size [30, 28]
        title {
            text: "Strade",
        }
        content {
            text: "Le strade nascono come sentieri polverosi. Con il migliorare delle  condizioni cittadine, i residenti si preoccupano di pavimentarle. Quando una  strada è pavimentata, sopra di essa puoi posizionare le @79piazze.  @PLe strade concepite con efficienza sono fondamentali per far funzionare la  città nel migliore dei modi. I @42passanti che forniscono i servizi alla città  si spostano meglio su tratti rettilinei, piuttosto che su strade tortuose e  costellate di incroci. @PPraticamente tutte le strutture cittadine richiedono l'accesso a una strada.  Le uniche eccezioni sono rappresentate dai giardini, dalle statue e dai forti. I  santuari, le mura e le abitazioni non richiedono un accesso diretto, ma devono  trovarsi entro due spazi da una strada per usufruire dei servizi dei passanti. @PI passanti possono attraversare il confine (sponda) tra un campo di limo e la  terra asciutta solo dove è presente una strada. Tali sponde sono ripide, fangose  e traditrici: solo una strada permette un passaggio sicuro. @PTutte le strade permettono un traffico uguale e i passanti si spostano sempre  alla stessa velocità, indipendentemente dalla pavimentazione. @L@LLa strada del Regno @LLa strada che attraversa il tuo territorio all'inizio di ogni missione si  chiama strada del Regno ed è speciale. Lungo questa strada giungono carovane di  mercanti e immigranti, mentre gli emigranti ne usufruiscono per lasciare la  città. Ogni parte della città deve avere accesso alla strada del Regno. Se isoli  una parte della città da tale via di comunicazione, essa non si evolverà. Tutti  gli addetti alle consegne diretti alle parti isolate si fermano finché l'accesso  non viene ripristinato. A volte, gli architetti reali devono rimuovere la  struttura che blocca l'accesso. @PCiò non significa che tutti devono avere un accesso fisico alla strada del  Regno: l'accesso può essere presente con una strada o attraverso uno spazio di  terreno libero e praticabile. @PQuesto è tutto ciò che devi sapere sulla strada del Regno. Altri dettagli che  riguardano l'accesso degli edifici potrebbero comunque risultare utili solo in  rare occasioni, quando, ad esempio, perdi l'accesso alla strada del Regno senza  un ostacolo individuabile. @PQuando costruisci un nuovo edificio, la struttura cerca automaticamente  l'accesso alla strada del Regno, sia tramite la rete stradale che attraverso un  terreno libero praticabile. La maggior parte delle volte, l'edificio si  costruisce su una strada esistente; quindi, l'accesso alla strada del Regno è  verificato tramite tale strada. Altre volte, però, puoi costruire qualcosa che  non si trova su una strada. In questi casi, la nuova struttura cerca l'accesso  attraverso un terreno libero. Se in seguito colleghi tale edificio con una  strada, esso ridefinisce il suo punto di accesso usando la nuova strada. Così,  se questa non riesce a trovare un percorso che la colleghi alla strada del Regno  (magari bloccata proprio dall'edificio che hai costruito), l'edificio collegato  perde l'accesso alla strada del Regno. @PPer ulteriori informazioni sui 'punti di accesso', consulta la sezione  seguente. @PUn'ultima nota sulla strada del Regno: non vi è nulla di speciale sull'intero  tratto di strada - ciò che importa sono i punti in cui entra ed esce dal tuo  territorio. Puoi spostare tratti della strada del Regno proprio come faresti con  le altre strade della città, ma solo se non blocchi l'accesso a questi due punti  fondamentali di entrata e uscita. @L@LEdifici su due strade @LA volte, puoi posizionare un edificio adiacente a due strade che possono  essere non connesse, o che lo sono ma lontano dall'edificio. Anche se le strade  sono due, i passanti non potranno sfruttare un doppio punto di ingresso. Ogni  edificio può avere un solo punto di accesso e, quindi, una sola strada  percorribile. @PAd esempio, supponi di costruire un deposito merci adiacente a una strada  lungo il suo lato sud. Le fabbriche, le carovane e i compratori dei bazar che si  trovano a sud dell'edificio si comporteranno nei suoi confronti come puoi  aspettarti. Supponiamo ora che tu intenda fare in modo che anche le industrie a  nord del deposito possano utilizzarlo. Se costruisci un'altra strada a nord del  deposito, potresti aspettarti che le industrie settentrionali la utilizzino per  interagire con il deposito, mentre quelle a sud continueranno a utilizzare la  strada meridionale. L'edificio può avere, però, un solo punto di accesso, quindi  le industrie a nord non avranno alcuna possibilità, a meno che non connetti la  strada a nord con quella a sud. @PQuando un edificio è adiacente a due o più strade, esso sceglie il suo punto  di accesso preferendo la strada più trafficata. Tornando all'esempio precedente,  se la strada a sud fa parte della rete principale e quella a nord è collegata  solo a una industria separata dal resto della città, il punto di accesso del  deposito sarà sulla strada a sud. Se, invece, la prima strada a sud conduce a  una piccola fattoria e la strada a nord connette al centro cittadino, il punto  di accesso sarà su quest'ultima. @PPer evitare dei comportamenti imprevedibili, non costruire edifici adiacenti a  due strade non connesse. Se vuoi, puoi connettere le strade; altrimenti, tieni  presente che una sola sarà quella utilizzata per interagire con l'edificio. Per  determinare quale strada fornisce l'accesso a un edificio, osserva il  comportamento dei passanti. @L@LClicca @153qui per ripercorrere la storia delle strade nell'antico Egitto."
        }
    }

    message_game_concept_water_crossings {
        id: 58,
        
        size [30, 28]
        title {
            text: "Attraversamento dell'acqua",
        }
        content {
            text: "Esistono due sistemi per attraversare un corso d'acqua: i ponti e i  traghetti. I ponti possono attraversare solo corsi ridotti. Le navi non possono  navigare sotto un ponte, quindi accertati di costruirli solo dove non c'è  traffico navale. I @Pponti possono essere costruiti esclusivamente su tratti di  spiaggia rettilinei (entrambe le sponde). Quando scegli un luogo adatto per il  ponte, ne vedrai l'impronta verde e il costo (i prezzi dei ponti dipendono dalla  loro lunghezza). Se il luogo scelto non è adatto, vedrai dei quadrati rossi. I  ponti non richiedono manodopera, ma necessitano dell'accesso a una strada. @PI traghetti fanno la spola tra due approdi e funzionano come i ponti, anche se  sono più versatili. I traghetti non bloccano il percorso di altre navi, che  quindi possono andare e venire come preferiscono. @PCome i ponti, gli approdi dei traghetti devono essere posizionati su tratti di  spiaggia rettilinei. Quando scegli un luogo adatto, vedrai un quadrato verde.  Non occorre posizionare il secondo approdo direttamente di fronte al primo. Puoi  scegliere tra diversi luoghi dell'altra sponda, sempre a patto che il tratto di  costa sia rettilineo. I quadrati verdi segnalano i luoghi adatti. @PDato che gli immigranti e gli emigranti usano le loro barche, possono usare i  traghetti non appena sono disponibili. Gli approdi dei traghetti devono disporre  di manodopera per trasportare i cittadini da una sponda all'altra. I  @42passanti con meta, come gli addetti alle consegne, i  compratori dei bazar e gli artisti che si recano nelle zone d'intrattenimento,  possono usare i traghetti. Gli altri passanti non possono usare i traghetti. @PPer trasportare gli immigranti, i traghetti non hanno bisogno dell'accesso a  una strada. Per arrivare ai traghetti, gli immigranti tagliano per i campi.  L'accesso a una strada è invece necessario per trasportare gli altri cittadini. @L@LDato che il @157Nilo divide il paese a metà, gli antichi egizi usavano ogni  tipo di imbarcazione per trasportare merci e persone. Per ulteriori informazioni  sulla costruzione della barche egizie, clicca @179qui."
        }
    }
    
    message_game_concept_irrigation {
        id: 59,
        
        size [30, 28]
        title {
            text: "Irrigazione",
        }
        content {
            text: "I trabocchi e i canali di irrigazione portano i benefici del Nilo a  zone di terreno più vaste. L'irrigazione delle coltivazioni aumenta la fertilità  del suolo. @PPer portare i benefici dell'irrigazione a una fattoria, posiziona un canale di  irrigazione entro due spazi da essa. Gli effetti dell'irrigazione non sono  cumulativi; con un solo canale di irrigazione puoi portare il massimo dei  benefici in qualsiasi coltivazione. @PLe fattorie dei campi di limo sono a livello dell'acqua e i canali di  irrigazione possono dunque essere connessi direttamente al Nilo. Le fattorie dei  prati, invece, non sono a livello dell'acqua. Per irrigare una fattoria dei  prati, devi costruire un trabocco. @PI trabocchi portano l'acqua a un livello superiore. Si possono costruire sul  terreno adiacente a uno specchio d'acqua o a un campo di limo. Per i trabocchi  costruiti vicino a un campo di limo, devi anche costruire un canale di  irrigazione dal Nilo nella parte frontale del trabocco, per rifornirlo d'acqua. @PPer irrigare una fattoria dei prati, collega un altro canale di irrigazione  alla parte posteriore del trabocco. I canali di irrigazione girano attorno agli  ostacoli sul loro percorso, ma non attorno alle strade. Se necessario, i canali  di irrigazione passano sotto le strade. @PAumentando la fertilità del suolo, aumenta anche la quantità di cibo prodotta.  La fertilità non influenza la durata del periodo di crescita. @PAnche le fattorie irrigate devono essere costruite su terra coltivabile.  L'irrigazione può aumentare la fertilità del suolo, ma non può rendere fertile  un terreno sterile. @PPer ulteriori informazioni, consulta la sezione sulle @45coltivazioni. @L@LNell'antico Egitto, la scoperta delle tecniche di irrigazione aumentò molto  la quantità di terreno coltivabile. Per ulteriori informazioni sull'irrigazione,  clicca @154qui."
        }
    }
    
    message_building_weaver {
        id: 60,
        
        size [30, 28]
        title {
            text: "Tessitoria",
        }
        content {
            text: "I tessitori trasformano il lino in tela. Il lino si coltiva nelle  @91fattorie&di&lino, oppure si @47importa da un'altra città. I tessitori  richiedono manodopera e accesso a una strada. Possono mantenere una piccola  scorta di lino per continuare a lavorare per un po' anche in caso di  interruzione dei rifornimenti. @PLa tela è un prodotto importante per tutta la città. È fondamentale per il  procedimento di imbalsamazione, quindi le @66camere&mortuarie ne hanno bisogno  di continui rifornimenti per funzionare con efficienza. Inoltre, anche i  cittadini desiderano avere una scorta di tela in casa, per cucire i propri  abiti. @L@LPer sapere di più sull'importanza della tela nell'antico Egitto e sul  relativo artigianato, clicca @398qui."
        }
    }
    
    message_building_water_supply {
        id: 61,
        
        size [30, 28]
        title {
            text: "Fornitura idrica",
        }
        content {
            text: "I serbatoi e i portatori d'acqua forniscono l'@44acqua&potabile ai cittadini. L'acqua dei serbatoi è una delle prime necessità dei cittadini, fondamentale per far evolvere le loro @56case. @PI serbatoi d'acqua richiedono manodopera e accesso a una strada e devono sorgere sul terreno erboso, segno della presenza di una sorgente sotterranea. Non puoi posizionarli sul terreno desertico. @PQuando un serbatoio d'acqua è operativo, da qui partono i portatori d'acqua, che camminano nel quartiere distribuendo l'acqua nelle case che visitano. È una buona idea controllare il percorso dei portatori d'acqua, così da assicurarsi che tutte le case ricevano la loro provvista d'acqua potabile. Usa la @18tabella&Idrica per individuare le case che non vengono rifornite. I trasportatori d'acqua sono @42passanti&senza&meta. @PI trasportatori d'acqua lavoreranno di più se i loro serbatoi d'acqua sono stati migliorati. Quando la desiderabilità della zona circostante è sufficientemente alta, i lavoratori del serbatoio d'acqua miglioreranno quest'ultimo. I trasportatori d'acqua dei serbatoi migliorati visiteranno più frequentemente la zona circostante. @PSolo le case hanno bisogno dell'acqua dei serbatoi e la gente desidera vivere vicino a uno di essi (consulta la sezione @56desirabilità per ulteriori informazioni).  @L@LClicca @156qui per ulteriori informazioni sulla distribuzione dell'acqua nell'antico Egitto."
        }
    }

    message_building_well {
        id: 62,
        
        size [30, 28]
        title {
            text: "Pozzo",
        }
        content {
            text: "I pozzi sono risorse rudimentali per accedere all'@44acqua&potabile. Solo i quartieri più poveri possono ritenersi soddisfatti di un semplice accesso a un pozzo. Affinché le case possano svilupparsi in strutture più convenienti, è fondamentale l'accesso ai @61serbatoi&d'acqua. @PI pozzi non richiedono manodopera o accesso a una strada. Devono essere posizionati sul terreno erboso, che indica la presenza di una sorgente sotterranea. Hanno un effetto parzialmente positivo sulla @56desirabilità. @PUsa la @18tabella&Idrico per individuare le case che non hanno accesso a un pozzo. @L@LPer ulteriori informazioni sui pozzi nell'antico Egitto, clicca @156qui."
        }
    }

    message_building_dentist {
        id: 63,
        
        size [30, 28]
        title {
            text: "Dentista",
        }
        content {
            text: "I cittadini più ricchi apprezzano la possibilità di consumare cibi  solidi e quindi richiedono l'accesso a un dentista per mantenere i denti sani o  sostituire quelli caduti. In un paese dove la sabbia inevitabilmente si mischia  al cibo, i dentisti hanno sempre del lavoro da svolgere. I dentisti aumentano la  @56desirabilità di un quartiere, ma non hanno alcun effetto sulla @53sanità. @PUsa la @18tabella&Sanitario per individuare i dentisti che lavorano nella tua  città. @L@LClicca @158qui per ulteriori informazioni sul ruolo dei dentisti nell'antico  Egitto."
        }
    }

    message_building_physician {
        id: 64,
        
        size [30, 28]
        title {
            text: "Medico",
        }
        content {
            text: "I medici mantengono un buon livello di @53salute&pubblica. Le loro  visite aiutano a diminuire il rischio di malattie. @PAi cittadini piace avere un ambulatorio medico nei paraggi e, senza di essi,  l'@56evoluzione&delle&abitazioni è limitata. @PGli ambulatori medici richiedono manodopera e accesso a una strada. @PVisita il tuo @26supervisore&sanitario per stabilire la copertura medica  cittadina. @L@LClicca @160qui per ulteriori informazioni sulle pratiche mediche dell'antico  Egitto."
        }
    }

    message_building_apothecary {
        id: 65,
        
        size [30, 28]
        title {
            text: "Farmacia",
        }
        content {
            text: "Le farmacie impiegano degli erboristi che rimuovono dalla  circolazione tutti i @53cittadini&infettati che incontrano lungo il loro  cammino. Le farmacie sono anche importanti per ridurre il rischio di @53malaria. @PLe farmacie richiedono l'accesso a una strada e manodopera. Per seguire il  percorso degli erboristi, usa la @18tabella&Sanitario. Potrai vedere tutti gli  erboristi e le farmacie presenti in città, oltre a verificare l'accesso di ogni  abitazione ai loro servizi. @PPer ulteriori informazioni, consulta il tuo @26supervisore&sanitario. @L@LPer ulteriori informazioni sulle pratiche farmaceutiche dell'antico Egitto,  clicca @159qui."
        }
    }

    message_building_mortuary {
        id: 66,
        
        size [30, 28]
        title {
            text: "Camera mortuaria",
        }
        content {
            text: "Gli imbalsamatori delle camere mortuarie preparano i defunti per il  loro viaggio nell'aldilà. @PLe camere mortuarie migliorano la @53salute&pubblica prendendosi cura dei  morti. Come la maggior parte degli edifici, le camere mortuarie richiedono  l'accesso a una strada e manodopera. In più, richiedono forniture di @60tela,  fabbricata in città o @47importata da un'altra città. Gli imbalsamatori usano la  tela per fasciare i defunti dopo il procedimento di imbalsamazione. @PAnche se i cittadini richiedono l'accesso alle camere mortuarie, nessuno è  felice di vivere accanto a tali strutture. Le camere mortuarie sono evitate a  causa dei cattivi odori che emanano. @PPer individuare le camere mortuarie presenti in città, usa la  @18tabella&Sanitario. Vedrai gli imbalsamatori che si prendono cura dei defunti  o che camminano in città. Il tuo @26supervisore&sanitario può fornirti ulteriori  informazioni sui servizi delle camere mortuarie. @L@LL'imbalsamazione era parte integrante delle credenze religiose dell'antico  Egitto. Clicca @161qui per ulteriori informazioni su questa antica pratica."
        }
    }

    message_building_shrine_and_temple {
        id: 67,
        
        size [30, 28]
        title {
            text: "Santuari e templi",
        }
        content {
            text: "Non puoi appagare gli dei senza santuari e templi. Le divinità locali  e gli dei patroni richiedono attenzione, mentre i cittadini richiedono accesso  alle strutture religiose. Per ulteriori informazioni sugli effetti degli dei  sulla città, consulta la sezione @51Religione. Per informazioni specifiche sugli  effetti di particolari divinità, scegli dall'elenco seguente: @L@P@350Complesso&templi&di&Osiride @P@351Complesso&templi&di&Ra @P@352Complesso&templi&di&Ptah @P@353Complesso&templi&di&Seth @P@354Complesso&templi&di&Bast @L@PI santuari sono piccoli monumenti dedicati a una divinità. Non richiedono  l'accesso a una strada, ma devono trovarsi entro due spazi da essa per usufruire  dei servizi di vigili del fuoco e degli architetti. Non richiedono manodopera  e non producono passanti, quindi non consentono l'accesso alla religione. Il  loro unico scopo è quello di appagare gli dei. @PPer fornire ai cittadini luoghi di culto e per appagare ulteriormente gli dei,  devi costruire dei templi. Questi richiedono l'accesso a una strada e impiegano  sacerdoti. Quando un tempio è in funzione, vedrai i sacerdoti predicare la  religione presso i cittadini. Come i santuari, i templi sono dedicati a divinità  specifiche. @G73 @PTempli e santuari aumentano il @56valore&della&proprietà del quartiere in cui  si trovano. I santuari e i templi contribuiscono anche al @3livello&culturale  cittadino.  @L@LLa religione era un aspetto fondamentale della vita nell'antico Egitto. Per  ulteriori informazioni su tale importante componente della cultura egizia,  clicca @399qui."
        }
    }

    message_building_scribal_school {
        id: 68,
        
        size [30, 28]
        title {
            text: "Scuola degli scribi",
        }
        content {
            text: "Le scuole degli scribi istruiscono i figli delle famiglie più ricche.  @PLe scuole richiedono l'accesso a una strada e manodopera. Inoltre,  richiedono forniture di @97papiro. Quando una scuola è operativa, gli insegnanti  camminano per strada istruendo i giovani nelle loro case. Ogni volta che un  insegnante lascia la scuola per dirigersi a casa di un allievo, porta con sé  alcuni rotoli di papiro, perché l'allievo si possa esercitare nella scrittura.  Le scuole degli scribi possono conservare una piccola scorta di papiro. Per  mantenere gli studi in corso, assicurati che l'industria del papiro della città  sia produttiva o che la sua @47importazione sia costante. @PIl tuo @27supervisore&all'istruzione sa quante sono le scuole operative in  città. Lo @18tabella&Istruzione ti mostra dove sono situate le scuole e quali  case hanno accesso agli insegnanti. Le scuole degli scribi contribuiscono al  @35livello&culturale cittadino. @L@LGli antichi egizi consideravano l'istruzione una funzione fondamentale per  il raggiungimento del successo. Clicca @163qui per ulteriori informazioni su  questa antica istituzione egizia."
        }
    }

    message_building_sun_temple {
        id: 69,
        
        size [30, 28]
        title {
            text: "Tempio del sole",
        }
        content {
            text: "I templi del sole rendono omaggio al culto del sole, tenuto in grande  considerazione da molti Faraoni. @PPer costruire un tempio del sole, ti occorrono @95arenaria e @94legno, più i  servizi della @363gilda&dei&carpentieri, @363gilda&degli&scalpellini e dei  @8campi&di&lavoro. @PI templi del sole si costruiscono iniziando con un obelisco. Prima di  costruirlo, occorre che nei @4depositi&merci sia contenuta una quantità  sufficiente di arenaria. Quando l'arenaria è sufficiente, il tempio del sole può  essere posizionato. Selezionalo dall'elenco Strutture religiose: Monumenti e,  quindi, scegli un luogo in cui erigerlo. Se il luogo è adatto, vedrai l'impronta  verde del monumento. Se una parte dell'impronta è rossa, alcuni ostacoli del  terreno ne impediscono la costruzione in quel luogo. Clicca per iniziare la  costruzione dell'obelisco del tempio del sole. @PQuando la pietra viene posizionata, i carpentieri costruiscono le impalcature  attorno all'obelisco. Poi, gli scalpellini decorano i fianchi dell'obelisco.  Quando questo è terminato, essi iniziano a lavorare sul resto del tempio. Prima  costruiscono un vestibolo e poi le mura di pietra. Dopo il completamento delle  mura, gli scalpellini costruiscono il tempio anteriore. Per completare tali  operazioni, gli scalpellini richiedono diverse slitte cariche di arenaria,  trainate dai manovali. Mentre sono al lavoro sul tempio anteriore, mura e  vestibolo, gli scalpellini posizionano delle piastrelle decorative tra le mura. @PQuando il tempio anteriore è completo e tutte le piastrelle sono posate, il  tempio è finito. @PPer informazioni sull'avanzamento della costruzione, visita il  @369capo&cantiere. Può anche essere utile una visita al  @373supervisore&dei&monumenti. @L@LPuoi apprendere ulteriori informazioni sulla storia dei templi del sole e  altri monumenti cliccando @396qui."
        }
    }

    message_building_library {
        id: 70,
        
        size [30, 28]
        title {
            text: "Biblioteca",
        }
        content {
            text: "I cittadini più raffinati richiedono l'accesso a una biblioteca. Le  biblioteche aumentano il valore della proprietà e aumentano il  @35livello&culturale della città. @PLe biblioteche sarebbero edifici inutili se i loro scaffali non contenessero  pergamene. Prima di poter costruire una biblioteca, i @4depositi&merci devono  contenere una buona provvista di @97papiro. Quando la biblioteca è costruita, le  occorre una scorta di papiro per funzionare a dovere. @PLe biblioteche richiedono, inoltre, l'accesso a una strada e manodopera.  Quando la biblioteca ha la scorta che le occorre, invia un bibliotecario  nell'area circostante. Ogni volta che il bibliotecario lascia la biblioteca,  prende con sé delle pergamene da distribuire ai cittadini. @PPer controllare il numero delle biblioteche in città, visita il tuo  @27supervisore&all'istruzione. Per individuare la posizione delle biblioteche,  usa la @18tabella&Istruzione. Tramite questo, puoi vedere le biblioteche e  seguire i bibliotecari lungo il loro cammino. @L@LPuoi ottenere ulteriori informazioni storiche sulla letteratura e sulle  biblioteche dell'antico Egitto cliccando @164qui."
        }
    }

    message_building_booth {
        id: 71,
        
        size [30, 28]
        title {
            text: "Baraccone",
        }
        content {
            text: "I baracconi sono le @49zone&di&intrattenimento più piccole ed  economiche. Un baraccone contiene un palco che ospita i giocolieri, che possono  intrattenere il pubblico con i loro spettacoli artistici. @PI baracconi richiedono un tipo particolare di accesso a una strada: essi  devono essere posizionati su un incrocio, a croce o a 'T'. I baracconi  richiedono impiegati e artisti addestrati. Gli impiegati controllano la folla e  assistono i giocolieri, mentre questi si esibiscono. I giocolieri si addestrano  nelle @75scuole&dei&giocolieri e possono esibirsi anche sui @72palchi e nei  @73padiglioni. @PPer @56evolversi, le case richiedono l'accesso all'intrattenimento e i  giocolieri portano i loro benefici a tutte le case presso cui passano. La  presenza di un baraccone in un quartiere, ne aumenta la desiderabilità. I  baracconi attivi aumentano il @35livello&culturale cittadino.  @PVisitando il tuo @28supervisore&all'intrattenimento, puoi sapere quanti sono i  giocolieri che lavorano in città. La @18tabella&Intrattenimento ti mostra dove  si esibiscono e il percorso che effettuano. @L@LGli antichi egizi erano dei veri pionieri per questo tipo d'intrattenimento.  Clicca @169qui per saperne di più."
        }
    }

    message_building_bandstand {
        id: 72,
        
        size [30, 28]
        title {
            text: "Palco",
        }
        content {
            text: "I palchi delle orchestre sono zone di intrattenimento di media  grandezza che contengono due palchi: uno per i giocolieri e l'altro per gli  spettacoli musicali. Il palco dei giocolieri è in un angolo della zona, mentre i  musicanti si esibiscono in un altro angolo. @PI palchi devono essere posizionati sugli incroci, a croce o a 'T'. Richiedono  personale, oltre a giocolieri e musicanti addestrati. Gli artisti si addestrano  nei @75centri&di&addestramento. @PPer @56evolversi, le case richiedono l'accesso all'intrattenimento; giocolieri  e musicanti portano i loro benefici a tutte le case presso cui passano. La  presenza di un palco nel quartiere ne aumenta la desiderabilità. I palchi  operativi aumentano il @35livello&culturale cittadino.  @PVisitando il tuo @28supervisore&all'intrattenimento puoi sapere quanti sono  gli artisti che lavorano in città. Lo @18tabella&Intrattenimento ti mostra dove  si esibiscono e il percorso che effettuano. @L@LGli antichi egizi erano musicanti famosi. Se vuoi saperne di più, clicca  @170qui. Per ulteriori informazioni sui giocolieri, clicca invece @169qui."
        }
    }

    message_building_pavilion {
        id: 73,
        
        size [30, 28]
        title {
            text: "Padiglione",
        }
        content {
            text: "Sono le zone d'intrattenimento più grandi e contengono tre palchi:  uno per i giocolieri, uno per i concerti musicali e uno per la danza. Nessun  cittadino può lamentare il fatto di vivere vicino a un Padiglione. @PI Padiglioni devono trovarsi sugli incroci, a croce o a 'T'. Richiedono  personale, oltre a giocolieri, musicanti e danzatori addestrati. Gli artisti si  addestrano nei @75centri&di&addestramento. @PPer @56evolversi, le case richiedono l'accesso all'intrattenimento e gli  artisti portano i loro benefici a tutte le case presso cui passano. La presenza  di un Padiglione nel quartiere ne aumenta la desiderabilità. I Padiglioni  operativi aumentano il @35livello&culturale cittadino.  @PVisitando il tuo @28supervisore&all'intrattenimento, puoi sapere quanti sono  gli artisti che lavorano in città. Lo @18tabella&Intrattenimento ti mostra dove  si esibiscono e il percorso che effettuano. @L@LLeggi ulteriori informazioni sulla danza egizia cliccando @171qui. Se vuoi  sapere di più sulla loro musica, clicca @170qui; se, invece, vuoi altre  informazioni sui giocolieri, clicca @169qui."
        }
    }

    message_building_senet_house {
        id: 74,
        
        size [30, 28]
        title {
            text: "Taverna senet",
        }
        content {
            text: "Le taverne senet offrono ai cittadini un luogo in cui giocare a  senet, una sfida che si ispira al viaggio verso l'aldilà. Davanti a boccali di  birra schiumante, i cittadini trascorrono il tempo libero in totale  rilassamento. @POltre al personale e all'accesso a una strada, le taverne senet richiedono una  fornitura di @96birra per soddisfare i loro clienti. @PVisita il @28supervisore&all'intrattenimento per sapere quante sono le taverne  senet operative in città. Usa la @18tabella&Intrattenimento per vedere quali  case hanno accesso a una taverna senet. @PAlla gente non piace molto vivere vicino a una taverna senet (clicca @56qui  per ulteriori informazioni sulla desiderabilità). I clienti tendono a diventare  rumorosi e poco civili - specialmente quando perdono al gioco. @L@LIl senet era ben più di un gioco. Per saperne di più, clicca @172qui."
        }
    }

    message_building_trading_centers {
        id: 75,
        
        size [30, 28]
        title {
            text: "Centri di addestramento",
        }
        content {
            text: "Per imparare il loro lavoro, giocolieri, danzatori e musicanti devono  addestrarsi. Ciascuna disciplina ha il suo centro di addestramento: i giocolieri  vanno alla scuola dei giocolieri, i musicanti ai conservatori e i danzatori alla  scuola di danza. @PCiascun edificio richiede l'accesso a una strada e manodopera. Quando gli  artisti completano il loro addestramento, si dirigono alla più vicina zona  d'intrattenimento che ne richieda i servizi. Quando i giocolieri camminano in  tale zona, le case presso cui passano ricevono l'accesso alla relativa forma  d'intrattenimento. @PQuando gli artisti arrivano nelle loro zone, inscenano uno spettacolo per un  certo numero di giorni. Clicca su una zona d'intrattenimento con il tasto destro  del mouse per sapere quali artisti stanno intrattenendo il pubblico e per quanti  giorni durerà lo spettacolo. Se un centro di addestramento è vicino a una zona  d'intrattenimento, lo spettacolo durerà di più. Quando lo spettacolo finisce,  gli artisti ritornano a casa. A meno che non siano stati addestrati altri  artisti, la zona d'intrattenimento sarà vuota e non fornirà alcuno spettacolo  per i cittadini. @PI cittadini non si lamentano se vivono vicino a una scuola di giocolieri, le  loro peripezie sono divertenti sia durante la pratica che durante lo spettacolo.  A nessuno, invece, piace vivere vicino alle scuole di danza o ai conservatori.  Gli artisti vanno e vengono a tutte le ore e i musicanti alle prime armi non  producono suoni molto apprezzati. @PPer osservare il movimento degli artisti dalle scuole alle zone  d'intrattenimento, usa la @18tabella&Intrattenimento. @L@LGli Egizi trovarono molti modi per divertirsi. Clicca @165qui per saperne di  più."
        }
    }

    message_building_courthouse {
        id: 76,
        
        size [30, 28]
        title {
            text: "Palazzo di giustizia",
        }
        content {
            text: "I palazzi di giustizia sono strutture municipali assai versatili.  Oltre a ridurre il @36crimine nel quartiere, conservano anche una parte del  tesoro cittadino. I cittadini apprezzano la sicurezza nonché il lustro portati  dalla loro presenza. @PI palazzi di giustizia richiedono l'accesso a una strada e manodopera prima  di poter inviare i magistrati a controllare le vie cittadine. La presenza di un  magistrato in un quartiere, riduce il rischio di crimine. I magistrati  costituiscono solo una misura preventiva; se il crimine appare, il magistrato  non può fare nulla per impedire i misfatti. @PNei palazzi di giustizia è conservata una parte del @48denaro cittadino. Non è  possibile sapere quanto denaro è conservato in ciascun edificio. Il tuo  @30supervisore&finanziario è più adatto a gestire questo genere di faccende e  sarà suo compito calcolare di volta in volta l'esatto ammontare.  @L@LI palazzi di giustizia erano luoghi molto affacendati. Per ulteriori  informazioni sulla legge dell'antico Egitto, clicca @183qui."
        }
    }
    
    message_building_palace {
        id: 77,
        
        size [30, 28]
        title {
            text: "Il Palazzo",
        }
        content {
            text: "Il Palazzo è la sede del potere. @PIl Palazzo è una risorsa fondamentale per la tua città e dovresti cercare di  costruirlo il più presto possibile. Puoi costruire un solo Palazzo per città.  Secondo le dimensioni della città, puoi costruire un Palazzo del villaggio, un  Palazzo cittadino o un Grande Palazzo cittadino. @PPer riscuotere le tasse, la città deve avere un Palazzo. I tuoi cittadini  dubiteranno del tuo potere finché non stabilirai una fisica presenza del potere  centralizzato. Dal Palazzo puoi modificare la percentuale delle tasse. Clicca  sul Palazzo con il pulsante destro del mouse e usa i pulsanti di scorrimento  nella parte superiore della tabella per modificare la percentuale di tassazione.  Per ulteriori informazioni sulle tasse, clicca @48qui. @PI sotterranei del Palazzo contengono una parte del tesoro cittadino. Lo  schermo che compare quando clicchi con il pulsante destro del mouse ti comunica  a quanto ammonta il denaro conservato. Consulta la sezione @48Denaro per  ulteriori informazioni sulla distribuzione del tesoro cittadino. @PIl Palazzo ti fornisce anche una visuale schematica dello stato della città.  Sposta il puntatore su tale edificio e dopo pochi secondi vedrai comparire un  riquadro che riassume la tassazione, livelli e disoccupazione. @PSe la tua città è così fortunata da avere vicino una @93miniera&d'oro, il  Palazzo ha un'ulteriore funzione vitale. L'oro estratto nelle miniere è portato  a Palazzo, dove viene raffinato e trasformato in denaro. I deben così prodotti  sono aggiunti automaticamente al tesoro cittadino. L'oro non è mai commerciato e  viene portato esclusivamente a Palazzo. @PSe il Faraone ti onora di una sua visita, egli sarà alloggiato a Palazzo. @PLa sede del governo è una delle costruzioni più belle e prestigiose della  città. I cittadini desiderano vivere nelle sue vicinanze - alcuni pensano che in  questo modo cresca anche il loro prestigio. @PIl Palazzo richiede l'accesso a una strada e manodopera. Il Palazzo  richiede, inoltre, l'accesso a una sorgente d'acqua sotterranea per soddisfare i  bisogni dei dignitari in visita. Per questo motivo, almeno una parte del Palazzo  deve occupare un tratto di terreno erboso.  @L@LPer ulteriori informazioni sul governo e la burocrazia dell'antico Egitto,  clicca @174qui."
        }
    }

    message_building_mansion {
        id: 78,
        
        size [30, 28]
        title {
            text: "Magione",
        }
        content {
            text: "Per consolidare il tuo potere e prestigio, devi costruirti una casa  degna del tuo stato. La tua magione contiene la fortuna di famiglia; senza una  magione, non ti è permesso percepire un @48salario. I cittadini vogliono essere  certi che la tua posizione sia ben salda prima di concederti uno stipendio.  @PIl tuo salario dipende dalla tua esperienza. Se credi di meritare uno  stipendio più o meno consistente, puoi modificare il tuo livello di salario.  Clicca sulla magione con il pulsante destro del mouse, comparirà una tabella che  mostra il tuo livello di salario scritto su un pulsante. Clicca sul pulsante e  potrai vedere i vari stipendi percepiti nel Regno in relazione al titolo dei  governanti. Scegli un nuovo salario da questo elenco e percepirai il denaro  indicato. Ma stai attento: se ti paghi più di quanto meriti, il fatto avrà  ripercussioni negative sul @35livello&del&Regno. Puoi modificare il tuo salario  anche consultando il @30supervisore&finanziario. @PLa tua residenza richiede l'accesso a una strada e una sorgente di acqua  sotterranea. Quindi, almeno una parte della magione deve sorgere sul terreno  erboso. Tutti desiderano essere tuoi vicini: la tua magione contribuisce  notevolmente alla desiderabilità della zona. @PSecondo il tuo livello e le possibilità della città, puoi costruire una  magione personale, familiare o una magione super-lusso dinastica. @L@LI Faraoni vivevano in abitazioni colossali, tali da oscurare qualsiasi altro  tipo di abitazione. Per ulteriori informazioni su queste incredibili abitazioni,  clicca @175qui."
        }
    }
    
    message_building_garden_plaze_statue {
        id: 79,
        
        size [30, 28]
        title {
            text: "Giardini, piazze e statue",
        }
        content {
            text: "L'abbondanza di merci e servizi è fondamentale, ma i cittadini non ameranno davvero le loro case se la città è priva di abbellimenti. Le piazze, i giardini e le statue migliorano l'aspetto di un quartiere e ne aumentano il valore. Nessuna delle strutture di abbellimento richiede manodopera e possono essere costruite selezionando il relativo pulsante dal riquadro Abbellimenti dell'elenco delle strutture municipali.  @PI giardini sono luoghi dove la gente può riposarsi dopo le fatiche quotidiane. Se decidi di dedicare molto terreno a un solo giardino, questo sarà meraviglioso. I giardini non richiedono l'accesso a una strada. @PLe statue sono monumenti alla gloria d'Egitto. Esse sono di tre dimensioni: piccole, medie e grandi. Per costruirle, scegli la dimensione e trova un luogo adatto. Mantenendo il puntatore sul luogo scelto, premi il tasto 'R': potrai scegliere tra quattro tipi di statue e il loro orientamento. Quando la statua che desideri ha il fronte nella direzione voluta, clicca per posizionarla. Le statue non richiedono l'accesso a una strada. @G72 @PLe piazze sono tratti di @57strada più belli degli altri. Possono essere costruite solo su strade che i cittadini hanno lastricato. I cittadini lastricano le strade quando il loro quartiere è sufficientemente @56desiderabile e le piazze aumentano la desiderabilità ulteriormente. La costruzione delle piazze avviene come quella delle strade. Clicca sul pulsante Piazza, quindi clicca sulla strada lastricata che vuoi ricoprire di piastrelle. Le piazze non modificano la funzione delle strade, né la loro capacità. Puoi piastrellarne lunghi tratti tenendo premuto il pulsante del mouse e trascinando il puntatore, ma fai attenzione al costo. @L@LI giardini erano quasi una necessità per gli antichi egizi. Clicca @176qui per ulteriori informazioni su tali aree verdeggianti e sull'arte pubblica."
        }
    }
    
    message_building_tax_collector {
        id: 80,
        
        size [30, 28]
        title {
            text: "Esattore",
        }
        content {
            text: "Gli esattori girano per la città per assicurarsi che i residenti paghino le tasse. @PGli esattori lavorano per l'esattoria, che richiede accesso a una strada e manodopera. In più, affinché gli esattori possano svolgere il loro dovere, la città deve possedere un @77Palazzo. @PUna parte del tesoro cittadino è conservata nelle varie esattorie.  @PL'impostazione della percentuale di tassazione è un argomento delicato. Devi bilanciare le necessità delle tue finanze con la pazienza dei tuoi cittadini. La gente non sopporterà di pagare tasse elevate per molto tempo e non esiterà ad andarsene in cerca di altre meno ingorde. Se una parte della popolazione paga tasse elevate e la restante non ne paga affatto, l'@39umore&cittadino crollerà e il rischio di @36crimine aumenterà. Consulta il tuo @30supervisore&finanziario, alla voce @48denaro, per ottenere consigli sull'impostazione della percentuale di tasse. @L@LGli antichi egizi pagavano le tasse al Faraone per contribuire ai fondi del governo. Clicca @173qui per ulteriori informazioni sulle tasse dell'antico Egitto."
        }
    }

    message_building_architect_post {
        id: 81,
        
        size [30, 28]
        title {
            text: "Centro di architettura",
        }
        content {
            text: "Le grandi strutture, come depositi merci, miniere, granai, templi e  complessi di templi sono inclini al crollo. Gli architetti girano per la città e  riparano eventuali danni prima che accada il disastro. Gli architetti lavorano  per i centri di architettura. @G68 @PI centri di architettura richiedono l'accesso a una strada e manodopera.  @PPuoi individuare gli edifici che rischiano di crollare usando la @18tabella  Rischi:&Danni. Se noti che un certo edificio o gruppo di edifici ha un alto  rischio di crollo, costruisci lì vicino un centro di architettura cosicché possa  sfruttare i servizi degli architetti. @PI crolli possono avere effetti catastrofici. Se un @3granaio o un  @4deposito&merci crolla, il cibo e le merci lì contenute saranno  irrimediabilmente persi."
        }
    }

    message_building_whipwright {
        id: 82,
        
        size [30, 28]
        title {
            text: "Cantiere navale",
        }
        content {
            text: "I cantieri navali forniscono le barche per scopo commerciale e  militare. Essi costruiscono le barche da pesca per i @84moli&da&pesca, navi da  guerra per o @356moli&delle&navi&da&guerra e navi da trasporto truppe per i  @357moli&delle&navi&da&trasporto. I cantieri navali devono essere costruiti su  tratti di costa rettilinei. Se il posto desiderato è adatto, vedrai l'impronta  dell'edificio diventare verde. @PCostruisci i cantieri navali su tratti di fiume o mare navigabili. I cantieri  situati su stretti corsi d'acqua non possono inviare le navi ai moli che le  attendono. Una simile situazione può vanificare completamente il tuo impegno  marittimo, in quanto i cantieri continuano a produrre navi che scompaiono non  appena si accorgono di non poter raggiungere i loro moli. @PI cantieri navali richiedono manodopera e l'accesso a una strada. Inoltre,  richiedono forniture di legno per costruire le navi da guerra e da trasporto  truppe. Il legno non è necessario per costruire le barche da pesca. I cantieri  navali ricevono l'ordine di costruzione direttamente dai moli. Quando  l'imbarcazione è completa, essa naviga dal cantiere fino a raggiungere il molo  di appartenenza. A meno che tu non debba costruire molte navi in fretta, un solo  cantiere è più che sufficiente per soddisfare i tuoi bisogni. @PSe una nave da guerra o da trasporto viene danneggiata in battaglia, inviala  al molo per farla riparare. Le navi gravemente danneggiate si dirigono al molo  automaticamente. Se il cantiere ha legno a sufficienza, riparerà le navi. @PI cantieri navali non costruiscono i @58traghetti: sono gli stessi  traghettatori che forniscono le loro barche per trasportare merci e cittadini da  una sponda all'altra.  @PI cantieri navali producono molto rumore; quindi, nessuno desidera vivere  nelle loro vicinanze. @L@LL'antico Egitto costruiva navi di varie forme e dimensioni. Per ulteriori  informazioni su tale antica industria, clicca @179qui."
        }
    }
    
    message_building_dock {
        id: 83,
        
        size [30, 28]
        title {
            text: "Porto",
        }
        content {
            text: "Parte del commercio con @47altre città si svolge via acqua. Le grandi  imbarcazioni commerciali navigano sul Nilo, ma non porteranno alcun prodotto  alla tua città se non trovano un porto. Costruisci un porto sulla costa a cui le  chiatte potranno attraccare. Assicurati di scegliere un tratto di costa sul Nilo  o sul mare, dove navigano le chiatte da trasporto merci. Se il porto si trova su  uno stretto corso d'acqua, le navi commerciali non potranno raggiungerlo. @PPer funzionare con efficienza, i porti devono avere l'accesso a una strada e  manodopera. Quando una nave attracca, i carrettieri del porto scaricano le sue  merci e le portano nei @4depositi&merci; qui, i carrettieri caricano le merci da  esportare e le portano al porto. È una buona idea costruire depositi merci  vicino al porto, così da accorciare il percorso dei carrettieri. @PI porti hanno un effetto negativo sulla @56desirabilità della zona. @L@LPer ulteriori informazioni sul commercio nell'antico Egitto, clicca  @177qui."
        }
    }

    message_building_fishing_wharf {
        id: 84,
        
        size [30, 28]
        title {
            text: "Molo da pesca",
        }
        content {
            text: "Se vedi dei pesci che ogni tanto saltano fuori dall'acqua, i  pescatori possono pescarli e trasformali in cibo. Per fare questo, la città ha  bisogno di una o più barche da pesca. @PLe barche da pesca sono ormeggiate ai moli da pesca. I moli da pesca devono  essere costruiti su tratti di spiaggia rettilinei e metà della struttura deve  essere posizionata sull'acqua. Assicurati che le barche da pesca possano  navigare nei pressi del molo. Se posizioni un molo da pesca su un corso d'acqua  troppo ridotto, le barche da pesca non potranno raggiungerlo. Una situazione del  genere può vanificare completamente il tuo impegno marittimo, in quanto i  cantieri continuano a produrre barche che scompaiono non appena si accorgono di  non poter raggiungere il molo. @PSe in città c'è un @82cantiere&navale, la costruzione del molo da pesca  comunica direttamente l'ordine di costruire una barca da pesca. Il cantiere non  ha bisogno di materiale grezzo per costruire le barche da pesca. @PLe riserve di pesce sono limitate, ma non possono essere mai esaurite. Una  popolazione numerosa non può sopravvivere nutrendosi esclusivamente di pesce. @PI moli da pesca sono luoghi maleodoranti e rendono il vicinato  @56indesiderabile. @L@LClicca @186qui per ulteriori informazioni sulla pesca nell'antico Egitto."
        }
    }

    message_building_defensive_structures {
        id: 85,
        
        size [30, 28]
        title {
            text: "Strutture di difesa",
        }
        content {
            text: "L'@37esercito e la @356marina difendono la città quando i nemici ne  hanno già varcato i confini. La costruzione di strutture di difesa può impedire  ai nemici di mettere piede sul tuo territorio. @L@LMura @LLa struttura di difesa più semplice è costituita dalle mura. Per costruirle,  selezionale dall'elenco Strutture militari: Strutture di difesa. Per costruire  lunghi tratti di mura in un colpo solo clicca con il mouse e trascina il  puntatore, come se costruissi una strada. @PLe mura che sono spesse un solo strato rallentano i nemici per breve tempo.  Per difendere meglio la tua città dagli attacchi, costruisci mura spesse diversi  strati. I nemici che attaccano delle mura spesse impiegano molto più tempo a  creare una breccia. @PLe mura sono costruite con qualsiasi tipo di materiale disponibile; quindi,  non richiedono pietra estratta o importata. Il costo della loro costruzione è  comunque elevato: decidi con attenzione il perimetro che vuoi difendere. @PLe mura non richiedono l'accesso a una strada e rendono il vicinato meno  desiderabile. @L@LTorri @LCostruendo le torri, puoi dotare le mura anche di potenzialità offensive. Le  torri sono occupate dalle guardie addestrate al @88reclutamento per scagliare  giavellotti contro i nemici così coraggiosi da avvicinarsi entro la loro  portata. @PSe le mura sono abbastanza spesse da poterci camminare sopra, le torri inviano  delle sentinelle che sorvegliano il perimetro delle mura stesse e che scagliano  frecce contro i nemici in avvicinamento. @PLe torri si costruiscono nelle mura che sono spesse almeno due strati. Esse  richiedono l'accesso a una strada, impiegati e sentinelle dall'ufficio di  reclutamento. Non costruire mura così spesse da impedire alle guardie di colpire  i nemici! @L@LGuarnigioni @PPer quanto possa sembrarti sconfortante, non puoi circondare completamente una  città di mura. Per lasciar passare carovane e immigranti ti occorrono delle  guarnigioni. @PCostruisci le guarnigioni dove le strade principali incrociano le mura  cittadine. Mantenendo il puntatore sul luogo scelto, premi il tasto 'R' per  cambiare l'orientamento della guarnigione. Quando sono posizionate, le  guarnigioni si collegano automaticamente alle mura adiacenti. In caso di  attacco, le guardie chiudono i cancelli per tenere fuori il nemico. @PCome i blocchi stradali, le guarnigioni permettono il passaggio dei passanti con meta, mentre bloccano i passanti senza meta (clicca @42qui per ulteriori informazioni sui passanti). @PPer ulteriori informazioni, consulta la sezione sulla @52guerra. @L@LNell'antico Egitto le città erano ben difese. Clicca @182qui per accedere a  ulteriori informazioni."
        }
    }

    message_building_police_station {
        id: 86,
        
        size [30, 28]
        title {
            text: "Stazione di polizia",
        }
        content {
            text: "I conestabili riducono il rischio di crimine pattugliando le strade  della tua città. @PI conestabili sono inviati dalle stazioni di polizia, che richiedono l'accesso  a una strada e manodopera. Quando una stazione è funzionante, sul suo tetto  puoi vedere una bandiera sventolante. @PLa presenza di un conestabile in un quartiere riduce il rischio di crimine  nella zona. Se tale funzione preventiva fallisce, il conestabile può combattere  il crimine attivamente. Se un conestabile trova un ladro per la strada, egli lo  arresta prima che possa compiere altri atti criminosi. I conestabili rappresentano anche una delle tue migliori armi contro i @477predoni&di&tombe. @PI conestabili sono attivi anche contro le minacce di invasione e gli attacchi  di animali feroci. Un solo conestabile, però, non può fare molto contro un  branco di animali feroci o un esercito nemico; combatterà fino alla morte, ma  probabilmente non riuscirà ad avere la meglio sul nemico. L'unica possibilità di  vittoria contro nemici così potenti si ha quando i conestabili lavorano in  gruppo. Comunque, la lotta contro l'invasore è compito dei soldati, in grado  anche di avere la meglio sugli animali feroci. @G55 @PPer individuare quali quartieri sono più a rischio di criminalità, usa lo  @18tabella&Rischi. la tabella Rischi può aiutarti a determinare saggiamente il  posizionamento delle stazioni di polizia. @PAnche se tutti i cittadini desiderano vivere in un quartiere controllato da un  conestabile, nessuno desidera vivere nei pressi di una stazione di polizia. I  conestabili vanno e vengono a qualsiasi ora del giorno e, spesso, sono in  compagnia di personaggi malfamati. @L@LPuoi ottenere maggiori informazioni sulla legge dell'antico Egitto cliccando  @183qui."
        }
    }

    message_company_orders {
        id: 87,
        
        size [30, 28]
        title {
            text: "Ordini alle compagnie",
        }
        content {
            text: "Per posizionare una @37compagnia sul campo, o semplicemente per  ordinarle di muoversi, clicca su di essa e, quindi, sulla destinazione. Lo  stendardo della compagnia comparirà sul luogo di arrivo e la compagnia marcerà  verso di esso, se i soldati ne hanno la possibilità. Nota che le sponde fangose  e scivolose che separano i campi di limo dalla terra asciutta sono un terreno  insuperabile, tranne nei punti in cui è presente una strada. @PA una compagnia puoi impartire i seguenti ordini:  @L@LMantieni posizione in formazione serrata @LIn questa formazione, i soldati si mettono uno vicino all'altro. Dato che  hanno l'ordine di mantenere la posizione, non la lasceranno nemmeno per  attaccare un nemico. Essi attaccheranno solo i nemici che giungono a loro  portata. La formazione serrata riduce la zona difendibile e rende i soldati un  facile bersaglio per gli arcieri nemici,ma anche più efficaci in difesa nei  combattimenti corpo a corpo. @L@LMantieni posizione in formazione aperta @LQuesto ordine può essere impartito solo ai fanti e agli arcieri, non ai  guidatori di carri da guerra. I soldati in formazione aperta si allargano per  difendere un'area maggiore. Essi attaccheranno solo i nemici che giungono alla  loro portata. Questa formazione rende i soldati meno vulnerabili alle frecce  nemiche, ma non offre molta protezione in caso di attacco corpo a corpo, in  quanto ogni soldato può difendere solo se stesso. @L@LAttacca nemico vicino @LCon questo ordine, una compagnia si muove per attaccare i nemici che si  trovano più vicini. L'attacco continua finché il nemico verrà ucciso o si  ritirerà, o finché non impartirai un ordine diverso... o finché il morale della  tua compagnia sconfitta crollerà e i soldati ritorneranno al forte. @L@LAttacco libero @LCon questo ordine, i soldati cercano i nemici in un'area più vasta e li  attaccano. Le compagnie con l'ordine di attacco libero sono le più aggressive e  rompono qualsiasi formazione per sfogare la loro furia contro il nemico. La  foga, comunque, riduce la possibilità di difesa; quindi, questo ordine è adatto  solo quando il nemico è in inferiore numericamente.  @L@LCarica @LL'ordine di carica può essere impartito solo ai carri da guerra. La carica  rompe la formazione di difesa e il nemico diventa più vulnerabile agli attacchi.  I carri da guerra con questo ordine spronano i cavalli al galoppo e si lanciano  a grande velocità per una buona distanza. A lungo andare, però, i carri  rallentano, i cavalli si stancano e hanno bisogno di riposare: usa questo ordine  con la dovuta parsimonia. @L@LRitorna al forte @LClicca su Ritorna al forte quando i soldati hanno compiuto il loro dovere e  hanno sconfitto il nemico. Qui, possono riposare fino alla prossima battaglia.  Se il morale è basso, i soldati ritorneranno al forte di loro iniziativa.  @L@LOltre a impartire gli ordini sopra elencati, puoi ordinare l'attacco  cliccando su una tua compagnia e, quindi, sul nemico. La tua compagnia inseguirà  il nemico fino alla morte o fino a che non impartisci un altro ordine. @L@LPer ulteriori informazioni sull'arte della guerra nell'antico Egitto, clicca  @184qui."
        }
    }

    message_building_recruiter_academy {
        id: 88,
        
        size [30, 28]
        title {
            text: "Reclutamento e accademia",
        }
        content {
            text: "Gli uomini che vogliono combattere per la loro città si recano presso  il reclutamento per arruolarsi. Per ricevere un migliore addestramento, possono  andare all'accademia. Il reclutamento e l'accademia richiedono l'accesso a una  strada e manodopera. @PLa funzione del reclutamento è molto semplice: esso arruola gli uomini  nell'@37esercito della tua città e li equipaggia con armi che sono loro  necessarie. Per equipaggiare i futuri soldati, il reclutamento ha bisogno di un  magazzino di armi, importate da un'@47altra&città o costruite da un'@98armeria.  Per arruolare i guidatori di carri, il reclutamento ha bisogno dei carri da  guerra della @98fabbrica&dei&carri&da&guerra o di importazione. Gli uomini che  desiderano essere arcieri si equipaggiano con arco e frecce di loro proprietà.  Il reclutamento, inoltre, assegna gli arruolati ai turni di guardia sulle mura o  sulle @85torri. @PI nuovi soldati lasciano il reclutamento con armi e sogni di gloria, ma con  null'altro. L'accademia addestra questi novelli fanti, arcieri e guidatori di  carri nella nobile arte della guerra. Le sentinelle imparano il mestiere sul  posto di lavoro e, quindi, non frequentano l'accademia. Quando i soldati sono  addestrati, si recano ai loro forti. @PSe in città non è presente alcuna accademia, i soldati che escono dal  reclutamento si dirigono direttamente al forte della loro compagnia. @G57 @PA causa del rude comportamento dei soldati, il reclutamento e l'accademia  hanno effetti negativi sulla @56desirabilità. @L@LLeggi maggiori informazioni sulla guerra nell'antico Egitto cliccando  @184qui."
        }
    }

    message_building_grain_farm {
        id: 89,
        
        size [30, 28]
        title {
            text: "Fattoria di grano",
        }
        content {
            text: "Il grano non è diverso da altri tipi di cibo della città, ma le fattorie di grano forniscono un materiale grezzo come prodotto secondario: la paglia. La paglia serve da cibo per il bestiame nei relativi @360allevamenti ed è uno dei prodotti grezzi necessari alla fabbricazione di @364mattoni. La paglia (insieme alla selvaggina) si usa anche per nutrire gli animali allo @479zoo.  @PLa paglia si raccoglie nello stesso periodo del grano. Un addetto alle consegne la porta direttamente ad allevamenti di bestiame, fabbriche di mattoni, zoo o @4depositi&merci nello stesso momento in cui il suo collega consegna il grano al granaio o al deposito merci. @PLe fattorie di grano sono indesiderabili e abbassano il valore della proprietà. @PAltri argomenti collegati utili sono @45cibo&e&fattorie, @2bazar e @3granaio. @L@LClicca @185qui per ulteriori informazioni sul grano nell'antico Egitto."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,
        
        size [30, 28]
        title {
            text: "Fattoria di frutta e verdura",
        }
        content {
            text: "Frutta e verdura sono in grado di sostenere tutti i cittadini e  costituiscono un elemento fondamentale per una dieta salutare. Diverse regioni  d'Egitto possono produrre frutta e verdura diverse. Tra le coltivazioni  disponibili per i tuoi cittadini ci sono melograni, fichi, ceci e lattuga. @PLe fattorie di frutta e verdura funzionano come le altre fattorie di cibo.  Esse coltivano solo cibo. Consulta la sezione sulla @45coltivazione per sapere  come sfruttare al meglio le tue fattorie. @PEntrambi i tipi di fattorie richiedono manodopera e accesso a una strada.  Per le fattorie dei campi di limo, la forza lavoro proviene dai  @8campi&di&lavoro; assicurati, dunque, di costruirne uno o più in prossimità di  tali fattorie. @L@LGli antichi egizi mangiavano cibi molto diversi e apprezzavano una cucina  varia e gustosa. Clicca @187qui per ulteriori informazioni sui menù egizi."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,
        
        size [30, 28]
        title {
            text: "Fattorie di orzo, lino e henna",
        }
        content {
            text: "Le fattorie di orzo, lino e henna sono un po' diverse da quelle di @89grano e @90frutta&e&verdura. Le fattorie di orzo, lino e henna non producono cibo, ma materiali grezzi che sono lavorati per diventare prodotti finiti di maggior valore. L'orzo viene trasformato in @96birra, il lino è tessuto e trasformato in @60tela e infine l'henna si utilizza per produrre @470pittura. @PLe fattorie di orzo, lino e henna, comunque, si costruiscono e funzionano come le altre fattorie. Possono essere posizionate su qualsiasi campo di limo, oppure sui prati, contrassegnati da fiori gialli. Se scegli un luogo appropriato, vedrai l'impronta verde della fattoria prima di poterla posizionare. Le fattorie devono essere adiacenti a una strada e richiedono manodopera. Le fattorie dei campi di limo non impiegano direttamente dei lavoranti, ma ricevono la forza lavoro dai @8campi&di&lavoro. Prima di costruire una fattoria, leggi la sezione sulla @45coltivazione. @PQuando l'orzo, il lino e l'henna sono raccolti, essi vengono portati alla fabbrica più vicina (una distilleria per l'orzo, una tessitoria per il lino o una fabbrica di pittura per l'henna). Una volta giunto qui, l'orzo, il lino e l'henna vengono lavorati e trasformati in prodotti finiti che saranno distribuiti ai cittadini, usati nella @363gilda&degli&artigiani o @47commerciati per trarne profitto. Se le fabbriche non hanno spazio dove tenerli, o se non sono presenti tali fabbriche in città, l'orzo, il lino e l'henna sono portati ai @4depositi&merci. @PQueste fattorie hanno effetti negativi sulla @56desirabilità della zona. @L@LPer ulteriori informazioni sulla storia della coltivazione dell'orzo, clicca @185qui. Per maggiori informazioni sulle coltivazioni di lino nell'antico Egitto, clicca @189qui. Per ulteriori informazioni sulle coltivazioni di henna, clicca @469qui."
        }
    }

    message_building_clay_pit {
        id: 92,
        
        size [30, 28]
        title {
            text: "Cava d'argilla",
        }
        content {
            text: "Le cave d'argilla producono l'argilla da trasformare in @1vasellame o, insieme alla @89paglia, da usare per la fabbricazione di @364mattoni. Può anche essere inviata a una @363gilda&degli&artigiani per essere convertita in stucco. @PLe cave d'argilla devono avere l'accesso a una strada e manodopera. Possono essere posizionate solo vicino all'acqua. @PQuando i cavatori estraggono argilla sufficiente a riempire un carro, la cava invia un addetto alle consegne per portarla ovunque sia necessaria. L'addetto alle consegne porta l'argilla alle fabbriche di mattoni, ai vasai o alle gilde degli artigiani che ne hanno bisogno, favorendo sempre lo stabilimento più vicino. Se nessuno di essi ha bisogno del materiale grezzo, l'addetto alle consegne porta l'argilla al più vicino @4deposito&merci che possa accettarlo. Se nessuno accetta l'argilla, l'addetto alle consegne attende finché non si libera spazio. @PLe cave d'argilla sono buchi orrendi e umidi scavati nella terra e nessun cittadino per bene desidera vivere vicino a tale spiacevole vista. @L@LGli antichi egizi facevano un ottimo uso dei ricchi depositi di fango lasciati dal Nilo durante il ritiro delle acque. Clicca @190qui per ulteriori informazioni su questo utilissimo materiale."
        }
    }

    message_building_gold_copper_mine {
        id: 93,
        
        size [30, 28]
        title {
            text: "Miniere d'oro e di rame",
        }
        content {
            text: "L'oro e il rame sono metalli pregiati. Una città con depositi di  metalli nella sua zona è molto fortunata. Se vedi delle rocce punteggiate di  riflessi metallici, clicca sul pulsante Strutture industriali del pannello di  controllo, quindi seleziona Materiali grezzi per sapere se gli esploratori hanno  scoperto minerali d'oro o di rame - o entrambi.  @PL'oro è un bene raro e prezioso e deve essere estratto ogni volta che ne hai  la possibilità. L'oro è @48denaro e le miniere d'oro forniscono alla città la  possibilità di coniarne di proprio. Diversamente da altri beni, l'oro non viene  mai consegnato ai @4depositi&merci. L'oro va direttamente al @77Palazzo, che lo  trasforma in deben da aggiungere al tesoro cittadino. @G54 @L@LRame @LIl rame è prezioso quanto l'oro, anche se viene utilizzato in modo più  convenzionale. È uno dei pochi materiali grezzi che puoi esportare con buon  profitto.  @Pnella fase iniziale di vita della città, il rame è molto utile per fabbricare  le @98armi, altrimenti molto costose da importare. La tua città avrà spesso  bisogno di armi per equipaggiare i suoi soldati. Clicca @52qui per passare alla  sezione sulla guerra. @L@LLe miniere di metalli devono essere adiacenti alle zone rocciose che sono  costellate di pepite metalliche. Tali miniere richiedono manodopera e accesso  a una strada ed entrambe sono tra gli edifici meno desiderati in città. @L@LGli antichi egizi tenevano l'oro in grande considerazione e compivano molti  sforzi per estrarlo dalla roccia. Clicca @191qui per ulteriori informazioni  sull'oro e sui suoi usi nell'antico Egitto."
        }
    }
    
    message_building_woodcutter_and_reed_gatherer {
        id: 94,
        
        size [30, 28]
        title { text: "Taglialegna e raccoglitori di canne" }
        content {
            text: "I taglialegna e i raccoglitori di canne raccolgono materiali grezzi  utilizzati dalle industrie. Il legno ha molti utilizzi. I carpentieri lo usano  per costruire rampe e impalcature per i monumenti, le fabbriche di carri da  guerra per costruire i loro mortali veicoli e i cantieri navali per costruire  navi da guerra e da trasporto truppe. Le canne si usano per fabbricare il  @97papiro.  @PI taglialegna possono essere disposti ovunque, ma è meglio che siano vicini  agli alberi per ridurre il percorso dei boscaioli. I taglialegna richiedono  l'accesso a una strada e manodopera. Quando l'edificio è in piena operatività,  i taglialegna si addentrano nella foresta e tagliano gli alberi. @G58 @PI raccoglitori di canne funzionano nello stesso modo dei taglialegna. È bene  disporli vicino ai campi di canne, anche se possono sorgere ovunque. I campi di  canne sono di colore verde scuro, macchiato di verde chiaro e di giallo. Come i  taglialegna, i raccoglitori di canne richiedono l'accesso a una strada e mano  d'opera. Quando hanno tutto ciò che occorre, i raccoglitori si addentrano nelle  paludi. @PDevi fare molta attenzione quando pianifichi la costruzione di taglialegna e  raccolte di canne. Alberi e canne ricrescono con il tempo, ma entrambi possono  essere sovra-sfruttati. Se costruisci troppi taglialegna o raccolte di canne,  corri il rischio di esaurire la risorsa. Le tue industrie di raccolta si  fermeranno immediatamente e rimarranno in attesa che alberi e canne ricrescano. @PIl legno è uno dei beni più preziosi dell'antico Egitto. Cerca di non  distruggere le foreste quando decidi di liberare il terreno - se lo fai, la  città dovrà rinunciare a una grande fonte di guadagno. Le paludi non possono  essere bonificate (liberate) e alcuni erboristi le indicano come principali  fonti di malaria. @L@LClicca @192qui per ulteriori informazioni sull'importanza del legno  nell'antico Egitto. Clicca @188qui per scoprire i vari usi delle canne."
        }
    }

    message_building_stone_quarries {
        id: 95,
        
        size [30, 28]
        title {
            text: "Cave di pietra",
        }
        content {
            text: "I cavatori estraggono grossi blocchi di pietra in quattro diversi  tipi di cava: @L@PCava di pietra normale @PCava di calcare @PCava di granito @PCava di arenaria @L@LSe nell'area cittadina si trovano grandi zone rocciose, probabilmente potrai  costruire delle cave per estrarre la pietra. Alcune zone, però, contengono  roccia non adatta alle costruzioni oppure ne hanno troppo poca da supportare  tale industria. In queste zone, la roccia è solo una seccatura, perché il  terreno roccioso non può essere liberato, attraversato o utilizzato per  costruzioni. Clicca sul pulsante Strutture industriali e controlla l'elenco dei  materiali grezzi disponibili. Ti verranno mostrati quali tipi di pietra, se  presenti, possono essere estratti nella zona della città. @PDevi costruire le cave adiacenti alle zone rocciose. Se scegli un luogo  adatto, vedrai l'impronta verde della cava che vuoi posizionare. Altrimenti,  comparirà un quadrato rosso. @PLa pietra non può essere trasformata in altri prodotti. È, comunque, il  materiale per i monumenti e ne occorrono quantità davvero ingenti, anche per la  costruzione dei più piccoli. @PLe cave, ricavate dai fianchi delle zone rocciose, sono inclini al crollo.  Assicurati di costruire un @81centro&di&architettura vicino a esse, per impedire  eventuali disastri. @PLe cave richiedono lavoratori e l'accesso a una strada. A causa del fracasso  che producono, sono edifici indesiderabili. @L@LL'estrazione della pietra nell'antico Egitto era un lavoro molto lungo. Per  ulteriori informazioni, clicca @193qui."
        }
    }

    message_building_brewery {
        id: 96,
        
        size [30, 28]
        title {
            text: "Distilleria",
        }
        content {
            text: "Per iniziare la distillazione, le distillerie richiedono l'accesso a  una strada, manodopera e una fornitura di orzo. Le @91fattorie&d'orzo  producono l'orzo necessario, altrimenti importabile da @47un'altra&città. Una  sola fattoria d'orzo può normalmente supportare due distillerie. Le distillerie  possono incamerare una modesta quantità d'orzo per continuare a lavorare nel  periodo che intercorre tra due raccolti. @PQuando le distillerie hanno ciò che occorre, distillano la birra. Puoi subito  capire se una distilleria sta lavorando se vedi i suoi addetti al lavoro. Al  termine della distillazione, l'addetto alle consegne cerca di consegnare la  birra prima alle @74taverne&senet, altrimenti, la porta in un @4deposito&merci,  dove può essere prelevata dai compratori dei bazar e distribuita ai loro clienti  oppure @47commerciata con un discreto profitto. La birra è uno dei prodotti che  i tuoi cittadini richiedono per sviluppare le loro case in  @56abitazioni&migliori.  @PLa birra viene inoltre servita durante le @51festività&grandiose.  @L@LPer ulteriori informazioni sulla birra nell'antico Egitto, clicca @194qui."
        }
    }

    message_building_papyrus_maker {
        id: 97,
        
        size [30, 28]
        title {
            text: "Fabbrica di papiro",
        }
        content {
            text: "Le fabbriche di papiro richiedono manodopera, accesso a una strada  e forniture di @94canne dai raccoglitori di canne, o altrimenti importate da  un'@47altra&città. Le fabbriche di papiro possono incamerare una ridotta  quantità di canne per continuare a lavorare tra una consegna e l'altra. @PQuando un carro di papiro è pronto, un addetto alle consegne cerca di portarlo  a una @68scuola&degli&scribi o a una @70biblioteca che lo richieda. Se nessuna  struttura educativa lo richiede, l'addetto alle consegne porta il papiro in un  @4deposito&merci, pronto per essere @47commerciato con buon profitto. @G69 @PAi cittadini non piace vivere vicino a una fabbrica di papiro. Il continuo  martellamento fa venire il mal di testa. @L@LPer maggiori informazioni sulla fabbricazione del papiro nell'antico Egitto,  clicca @195qui."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,
        
        size [30, 28]
        title {
            text: "  Armeria e fabbrica di carri da guerra",
        }
        content {
            text: "Le armerie e le fabbriche di carri da guerra producono  l'equipaggiamento da guerra necessario alle compagnie militari.  @PUsando il rame delle @93miniere&di&rame o importato da un'@47altra@città,  l'armeria costruisce le armi. Queste sono portate al @88reclutamento, che le usa  per equipaggiare le compagnie di @37fanti, o in un @45deposito&merci, se il  reclutamento ne ha già a sufficienza in magazzino o se tale struttura non  esiste. @PLa fabbrica di carri da guerra usa il legno dei @94taglialegna o di  @47importazione per fabbricare splendidi carri da combattimento. La fabbrica  invia i suoi prodotti al reclutamento per equipaggiare i  @37guidatori&di&carri&da&guerra. Se il reclutamento ne ha già in magazzino, o se  la città non ha un ufficio di reclutamento, i carri da guerra sono portati nei  depositi merci. @PArmerie e fabbriche di carri da guerra richiedono l'accesso a una strada e  manodopera. Entrambi sono edifici @56indesiderabili. @L@LPer maggiori informazioni sulle armi dell'antico Egitto, clicca @196qui."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,
        
        size [30, 28]
        title {
            text: "Gioielli e beni di lusso",
        }
        content {
            text: "Con le forniture di @361gemme, i gioiellieri creano raffinati  gioielli, un bene di lusso. Le gemme possono essere estratte nelle miniere o  importate da un'@47altra città.  @PI gioiellieri richiedono l'accesso a una strada e manodopera. Essi hanno un  effetto negativo sulla @56desirabilità.  @PI gioielli non sono un bene molto profittevole per l'esportazione. La maggior  parte del costo di importazione deriva dal trasporto e non dal materiale. Ecco  perché importare tale bene ti può costare una fortuna e la sua esportazione non  costituisce una buona fonte di guadagno. @PI gioielli sono solo uno dei beni di lusso richiesti dai tuoi cittadini. I  residenti più ricchi desidereranno un altro bene di lusso importato. @L@LL'antico Egitto è famoso per i suoi splendidi @382gioielli. Per ulteriori  informazioni su altri beni di lusso dell'antico Egitto, clicca @197qui."
        }
    }

    message_population_milestone_100 {
        id: 100,
        
        size [30, 20]
        title { text: "Censimento" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "Nel tuo villaggio ci sono 100 persone." }
    }

    message_population_milestone_500 {
        id: 101,
        
        size [30, 20]
        title { text: "Censimento" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "La tua cittadina ora ospita 500 abitanti." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,
        
        size [30, 20]
        title { text: "Censimento" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "La tua città ora ospita 1.000 persone." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@17" }
        content { text: "Con 2.000 abitanti, la tua città sta diventando sempre più  importante." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@17" }
        content { text: "La tua città ha raggiunto i 3.000 abitanti." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@18" }
        content { text: "La tua città sta diventando piuttosto grande. Ora gli abitanti sono  5.000." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@18" }
        content { text: "Con 10.000 abitanti, la tua città è tra le più grandi d'Egitto." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@18" }
        content { text: "La tua città ha quasi eguali, infatti ora ospita 15.000 abitanti." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@19" }
        content { text: "Gli altri governanti e nomarchi invidiano la tua città, che ora  ospita 20.000 abitanti!" }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Censimento" }
        video { text: "@19" }
        content { text: "I pochi immigrati che fondarono la tua città molti anni fa, non  potevano certo immaginare che un giorno avrebbe contato ben 25.000 abitanti!" }
    }

    message_the_control_panel {
        id: 110,
        
        size [30, 20]
        title { text: "Il Pannello di controllo"  }
        content {
            text: "Tramite questo pannello puoi accedere a tutti i controlli per  costruire e migliorare la tua città. Il modo più immediato per comprenderne il  funzionamento è quello di cliccare sui vari pulsanti - prova, non farai alcun  danno! Se l'Aiuto via mouse è su ON (sotto la voce 'Aiuto' sulla barra dei  menu), posiziona il puntatore su un qualsiasi elemento del pannello e ne vedrai  una breve descrizione. Per accedere a una descrizione dettagliata di tutte le  funzioni di Faraon, seleziona la voce 'Aiuto' dalla barra dei menu."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        urgent: 1,
        title { text: "Incendio in città" }
        content {
            text: "Le fiamme consumano interi settori della tua città. Clicca su  'Tabelle: Rischi' per prevedere un possibile incendio e costruisci una stazione  dei pompieri vicino alle strutture più a rischio."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1
        
        size [30, 20]
        urgent: 1
        title { text: "Edificio crollato" }
        content {
            text: "Senza l'adeguata manutenzione fornita dagli architetti, alcune tra le  strutture più grandi della tua città possono crollare. Clicca su 'Tabelle:  Rischi' per individuare quali edifici rischiano di crollare e costruisci dei  centri di architettura nei loro pressi."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,
        
        size [30, 20]
        title { text: "Nave incagliata" }
        content { text: "Alcuni capitani con poca esperienza imparano a conoscere i campi  bonificati nel modo peggiore, ovvero quando le loro navi si incagliano." }
    }

    message_out_of_money {
        id: 115,
        
        size [30, 20]
        title { text: "Senza denaro!" }
        content { text: "I tuoi forzieri hanno finito i deben. Ti vengono concessi fondi  addizionali, ma non ci sarà un altro benefattore pronto a salvarti di nuovo.  Utilizza questo regalo per sostenere delle imprese redditizie." }
    }

    message_debt_again {
        id: 116,
        
        size [30, 20]
        title { text: "Debiti!" }
        content { text: "Le tue finanze fanno acqua. Hai ancora un credito di 5.000 deben, ma  ricorda che i @48debiti possono rovinare la tua famiglia, se non li estingui in  fretta." }
    }

    message_out_of_money_again {
        id: 117,
        
        size [30, 20]
        title { text: "Senza denaro!" }
        content { text: "I forzieri cittadini sono asciutti, nobile Faraone. I tuoi fedeli  nomarchi hanno donato tutti i deben che potevano, ma non possono permettersi di  intervenire un'altra volta." }
    }

    message_wrath_of_the_emperor {
        id: 118,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Ira dell'Imperatore" }
        video { text: "@12" }
    }

    message_attack_called_off {
        id: 120,
        type: 2,
        
        size [30, 20]
        title { text: "Dal comandante degli invasori..." }
        content {
            text: "Sono appena giunti nuovi ordini. Pare che tu abbia riguadagnato un  po' di rispetto in Egitto e la tua distruzione non sia più necessaria. Ti  saluto... per ora."
        }
    }
    message_debt_anniversary {
        id: 121,
        
        size [30, 20]
        urgent: 1,
        title { text: "Scadenza debito" }
        content {
            text: "Le tue finanze sono ancora in pericolo. Ogni anno consecutivo di  debito danneggia la tua reputazione e quindi il tuo @35livello&del&Regno. Forse  dovresti rileggere la parte di manuale che tratta il @48denaro."
        }
    }

    message_barbarians_attack {
        id: 122
        type: 2
        message_type: 7
        
        size [30, 20]
        urgent: 1,
        title { text: "Barbarians attack!" }
        video { text: "smk\\Spy_Barbarian.smk" }
    }

    message_legion_attacks {
        id: 123
        type: 2
        message_type: 7
        
        size [30, 20]
        urgent: 1,
        title { text: "Legion attacks" }
    }

    message_distant_battle {
        id: 124
        type: MESSAGE_ARCH_MESSAGE
        message_type: MESSAGE_TYPE_DISTANT_BATTLE
        
        title { text: "Distant battle" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_enemies_closing {
        id: 125
        type: 2
        
        size [30, 20]
        title { text: "Enemies closing" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_enemies_at_the_door {
        id: 126
        type: 2
        
        size [30, 20]
        urgent: 1
        title { text: "Enemies at the door" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_template_request {
        id: 130,
        type: 2
        message_type: 2
        size [30, 20]
        title { text: "xxxxx" }
        content { text: "xxxxx" }
    }

    // Shared shell for city_message_post_full eventmsg (title/body from event phrases).
    message_template_general {
        id: 131,
        type: 2
        message_type: 2
        size [30, 20]
        title { text: "" }
        content { text: "" }
    }

    message_wrath_of_bast_3 {
        id: 134,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Bast" }
        video { text: "@20" }
        content { text: "Vergogna! Bast non apprezza la tua indifferenza. Per dimostrarti che non puoi mantenere la salute cittadina senza porle il dovuto rispetto, ha trasformato l'acqua del fiume in sangue, avvelenando le riserve d'acqua. Ora puoi solo sperare che i tuoi cittadini resistano fino a quando l'acqua non sarà tornata pura." }
    }

    message_city_unemployment {
        id: 135,
        type: 2,
        
        size [30, 20]
        title { text: "Disoccupazione cittadina" }
        content { text: "C'è troppo poco lavoro per impiegare tutti i tuoi cittadini. A meno  che non crei altri posti di lavoro, i disoccupati potrebbero darsi al crimine,  oppure cercare fortuna in altre parti del Regno." }
    }

    message_employees_needed {
        id: 136,
        
        size [30, 20]
        title { text: "Cercasi lavoratori" }
        content { text: "I cittadini in età lavorativa sono troppo pochi per coprire tutti i  posti vacanti in città. A meno che non trovi altri lavoratori in fretta, i  servizi cittadini verranno meno e le industrie ne soffriranno." }
    }

    message_common_festival {
        id: 137,
        
        size [30, 20]
        title { text: "Festività normale" }
        content { text: "Tutti apprezzano la possibilità di uscire presto dal lavoro per  ritrovarsi sulla piazza delle festività, e la divinità festeggiata non può che  esserne lieta." }
    }

    message_lavish_festival {
        id: 138,
        
        size [30, 20]
        title { text: "Festività speciale" }
        content { text: "È iniziata la giornata di festa. Tutti i cittadini si stanno  allegramente dirigendo verso la piazza delle festività. La divinità  festeggiata apprezza molto la tua dedizione." }
    }

    message_grand_festival {
        id: 139,
        
        size [30, 20]
        title { text: "Festività grandiosa" }
        content { text: "L'attesissima festività di due giorni è finalmente iniziata! Tutti si  stanno dirigendo verso la piazza delle festività in cerca di birra e  divertimento. La divinità onorata di certo sorriderà alla tua città." }
    }

    message_wrath_of_osiris {
        id: 140
        type: 2
        
        size [30, 20]
        title { text: "Ira di Osiride" }
        video { text: "@24" }
        content { text: "Osiride lamenta l'apparente mancanza di dedizione di questa città. A  meno che non l'appaghi in fretta, il prossimo straripamento sarà peggiore di  quanto previsto... potrebbe addirittura non arrivare mai!" }
    }

    message_wrath_of_ptah {
        id: 141
        type: 2
        
        size [30, 20]
        title { text: "Ira di Ptah" }
        video { text: "@22" }
        content { text: "Hai suscitato l'ira di Ptah! La tua città al momento non ha industrie  da punire, ma fai molta attenzione a questa divinità quando inizierai a estrarre  minerali, pietra e a fabbricare prodotti." }
    }
    
    message_wrath_of_ptah_2 {
        id: 142
        type: 2
        
        size [30, 20]
        title { text: "Ira di Ptah" }
        video { text: "@22" }
        content { text: "Ptah si è offeso di fronte alla tua presunzione: davvero credi la tua  città possa essere operosa senza portargli il dovuto rispetto? Come monito, ha  distrutto alcuni edifici industriali." }
    }

    message_wrath_of_seth_noeffect {
        id: 143
        type: 2
        
        size [30, 20]
        title { text: "Ira di Seth" }
        video { text: "@21" }
        content { text: "La tua città è sfuggita all'ira di Seth in quanto non hai ancora  strutture militari da distruggere. Fai comunque attenzione a non provocare il  dio della distruzione, la sua rabbia assume molte forme e la sua memoria è  formidabile." }
    }

    message_wrath_of_bast {
        id: 144,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Bast" }
        video { text: "@20" }
        content { text: "Notizie terribili! Dato che la tua città non le porta il rispetto  dovuto, Bast, dea della famiglia, ha distrutto alcune case!" }
    }
    message_blessing_from_ptah {
    id: 145,
        type: 2,
        
        size [30, 20]
        title { text: "A blessing from Ptah" }
        video { text: "@22" }
        content { text: "Ptah sought a Storage Yard with room for more gems, clay, pottery, flax, linen, or jewelry. Had he found one, he would have increased your city's stores." }
    }
    message_wrath_of_osiris_2 {
        id: 147
        type: 2
        
        size [30, 20]
        title { text: "Ira di Osiride" }
        video { text: "@24" }
        content { text: "Giorno infelice! Furioso per il tuo rifiuto di omaggiare il dovuto  rispetto, Osiride invia una piaga di locuste per distruggere le tue messi." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Ptah" }
        video { text: "@22" }
        content {
            text: "Ptah è indignato per il tuo rifiuto di onorarlo degnamente. Egli invia la piaga delle rane per sconvolgere la tua città. La loro pelle viscida e il loro putrido odore costringeranno molta gente a fuggire dalla propria casa."
        }
    }

    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2
        
        size [30, 20]
        title { text: "Ira di Seth" }
        video { text: "@21" }
        content { text: "Furioso per il tuo rifiuto di onorarlo, Seth evoca una tempesta di grandine sulla tua città, ferendo e uccidendo chiunque vi si trovi!" }
    }

    message_farming {
    id: 150,
        
        size [30, 20]
        image { id: 81, pos [15, 15] }
        title { text: "Farming" }
        subtitle { text: "History" }
        content {
            text: "Farming and agriculture were the basis of the Egyptian economy. Abundant crops allowed Egypt to @177trade with neighbors, bringing new goods into Egypt. @L@LThe key to successful farming was the Inundation, called akhet. Every year, the Nile flooded its banks, refertilizing the soil. As long as the Inundation occurred, the Egyptians could count on having plenty of food to eat. In years of low or no Inundation, famine struck Egypt, which was sometimes enough to topple governments. @L@LTo take advantage of the restoring Inundation, dykes were built around farms to capture the water as it rose. As the Nile receded (called peret), the water, along with its nutrients, slowly soaked into the soil. After about six weeks, the farmer opened the dykes and let the rest of the water drain out. Of course, being submerged in water made the ground quite soft. Before he could sow his seed, the farmer had to wait for the land to dry out a little and become firm. @L@LFinally, during shemu, the crops were harvested. Crops meant for Egyptian consumption were stored in @5granaries. Food for export was stored in @6Storage&Yards until it could be loaded onto barges.  @L@LEstate owners or the government owned farms and employed laborers to do many of the most arduous tasks on the land. Farming was not easy work, and much of the work was done by hand. The tools farmers had at their disposal included the hoe, the hand-held plough, and the sickle. Domesticated oxen eased some of the plowing. @L@LFarming produced both raw materials and foodstuffs. @185Grain&and&barley were key food crops, and @189flax, which was manufactured into @398linen, was the most important raw material crop. @L@LFarming and agriculture were also integral to the Eygptian afterlife. Once the deceased has been granted entry into the afterlife, he finds himself working the soil in the Field of Reeds."
        }
    }

    message_industry {
        id: 151,
        
        size [30, 20]
        image { id: 82, pos [15, 15] }
        title { text: "Industria" }
        subtitle { text: "Storia" }
        content {
            text: "Con l'avvento del Vecchio Regno, la fabbricazione di manufatti si era  ormai spostata dalle case e si era concentrata in laboratori, in grado di  fornire tutti gli accessori utilizzati quotidianamente. Ciascun laboratorio si  specializzava e funzionava più o meno come una moderna catena di montaggio. Ogni  lavorante era responsabile solo di un particolare aspetto del prodotto finito, e  nessuno prendeva parte a tutte le fasi di lavorazione. Gli utensili utilizzati  nei laboratori erano di proprietà dello stato, così come i prodotti realizzati.  Gli artigiani guadagnavano il loro stipendio, normalmente costituito di cibo e  oggetti di prima necessità. @L@LL'industria egizia era florida e produceva numerosi oggetti. Gli Egizi  potevano diventare @198vasai, @398tessitori, gioiellieri, tintori,  @389carpentieri e fonditori, così come panettieri o @194birrai."
        }
    }
    message_housing {
        id: 152,
        
        size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Abitazioni" }
        subtitle { text: "Storia" }
        content {
            text: "Gli Egizi costruivano le loro case con mattoni, legno, fango e, in  alcuni casi, pietra. Il tipo di abitazione e la dimensione dipendevano dalla  ricchezza del cittadino e dal quartiere. Quindi, i cittadini di campagna che  praticavano l'agricoltura vivevano in strutture di mattoni o fango pressato,  composte di due, tre o quattro stanze. Le abitazioni di città della classe  lavoratrice erano abbastanza piccole, e nelle città più affollate si costruivano  case di due piani per due famiglie per risparmiare spazio. Gli impiegati  vivevano in abitazioni di mattoni composte di 3-7 stanze. @L@LI cittadini più ricchi avevano case più grandi e spaziose. I funzionari di  governo più anziani avevano case di 60-70 stanze, con alti soffitti supportati  da colonne in legno, stanze conviviali dove intrattenere gli ospiti, grandi  magazzini e stanze per la servitù. L'abitazione più lussuosa in assoluto era il  @175Palazzo&del&Faraone.  @L@LLa maggior parte delle città egizie cresceva in modo organico in qualsiasi  direzione disponibile. Alcune città erano invece pianificate, come, ad esempio,  gli insediamenti per lavoratori costruiti a Deir el-Medina. @L@LLe città egizie erano per lo più circondate da mura. Per ulteriori  informazioni sulle strutture difensive, cliccate @182qui."
        }
    }
    message_roads {
        id: 153,
        
        size [30, 20]
        image {
            id: 84,
            pos [15, 15]
        }
        title {
            text: "Strade",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il @157Nilo era la principale via di collegamento dell'intero Egitto.  Imbarcazioni di ogni tipo e dimensione trasportavano persone, merci e materiali  vari da un luogo all'altro. Naturalmente, gli antichi egizi disponevano anche di  strade su terraferma. Queste non erano normalmente pavimentate, ma erano  piuttosto sentieri battuti. In molte città, le strade si aggrovigliavano in ogni  direzione. Nelle città pianificate, come l'insediamento a Deir el-Medina, le  strade erano disposte come una griglia ordinata. @L@LVi erano anche alcune vie commerciali, ma anche queste non erano pavimentate  - ed erano abbastanza pericolose da percorrere. Per ulteriori informazioni sui  pericoli del commercio, cliccate @177qui."
        }
    }
    message_irrigation {
        id: 154,
        
        size [30, 20]
        image {
            id: 27,
            pos [15, 15]
        }
        title {
            text: "Irrigazione",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli Egizi aumentavano la disponibilità di terreno coltivabile con  l'irrigazione. Già nella IX dinastia (2000 a.C.) iniziarono a costruire una rete  di canali e fossati. Alcuni canali paiono addirittura precedenti, ma questi  venivano usati solo per il trasporto. I canali di irrigazione estendevano i  benefici del fiume, portando il fango fertilizzante in zone lontane dalle sue  sponde. @L@LFin dall'inizio della storia egizia, i contadini che volevano irrigare la  loro terra non avevano la vita facile. Essi irrigavano a mano, trasportando due  secchi d'argilla o cuoio appesi a un bastone da spalla, pieni d'acqua attinta al  fiume o presso qualche altra fonte d'acqua. I contadini tornavano con i loro  secchi alla fattoria che era divisa da piccole dighe. Le dighe trattenevano  l'acqua, massimizzando i benefici acquisiti con tanta fatica.  @L@LAlla fine della XVIII dinastia (circa nel 1300 a.C.), fu introdotto il  shaduf, una specie di bilanciere. Lo shaduf arrivò in Egitto probabilmente dalla  Mesopotamia, dove era in uso fin dal 2370 a.C.. Disposto sulla sponda del fiume  o presso un pozzo, lo shaduf era costituito da una grossa trave in legno che  poteva muoversi come un'altalena. A una estremità, verso l'acqua, si trovava il  secchio, all'altra un peso, in mattoni, che bilanciava quello del secchio pieno  d'acqua. In questo modo si poteva abbassare il secchio in acqua e poi  recuperarlo senza fatica grazie al bilanciamento del peso. L'acqua veniva infine  rovesciata direttamente in un canale. @L@LL'introduzione dello shaduf in Egitto aumentò la terra coltivabile del 15  percento. Inoltre, dato che la terra irrigata in questo modo non era mai  sommersa dalle acque del Nilo, essa poteva fornire due raccolti in un anno,  invece di uno solo."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2
        
        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Lavoro" }
        subtitle { text: "Storia" }
        content { text: "I contadini si caricavano di gran parte del lavoro più duro  dell'antico Egitto. Essi coltivavano la terra e raccoglievano le messi durante  la stagione di crescita. Durante lo straripamento, essi venivano impiegati a  svolgere dei lavori per lo stato. Per lo più, lavoravano alla costruzione di  piramidi e altre strutture, ma potevano anche essere impiegati per la  manutenzione delle infrastrutture, come le @153strade e i  @154canali&di&irrigazione. @L@LAnche se il loro lavoro era difficile, non si può dire che fossero soggetti  a una forma di sopruso. La giornata di lavoro tipica durava otto ore con una  pausa per il pranzo. La settimana durava otto giorni, con due giorni di riposo  al suo termine. Oltre a questi fine settimana, il lavoro si interrompeva a ogni  festività. I lavoratori potevano astenersi dal lavoro se in famiglia c'era  qualche malato o un decesso. @L@LLa presenza sul posto di lavoro era registrata con cura, così come le  giustificazioni addotte per le assenze. Alcune ragioni al giorno d'oggi  probabilmente non sarebbero accettate. Un impiegato, ad esempio, poteva non  essere presente sul posto di lavoro perché era andato a bere qualcosa con un suo  amico. @L@LNonostante ciò che si crede comunemente, gli schiavi venivano impiegati  assai raramente per le costruzioni ordinate dallo stato. A volte gli schiavi  lavoravano nelle cave, ma per la maggior parte lavoravano nelle case. @L@LSe i lavoratori non venivano trattati bene, potevano dichiarare lo sciopero.  Durante il Regno di Ramses III, circa nel 1152 a.C., i lavoratori di Deir el- Medina incrociarono le braccia per protesta formale contro i ritardi dei  pagamenti. Il loro sciopero ebbe successo, e i ritardi vennero tutti  recuperati." }
    }
    message_clean_water {
        id: 156
        
        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Pozzi e cisterne", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "Fornire l'acqua a tutta la popolazione dell'antico Egitto non era un  compito facile. Le principali fonti d'acqua erano il Nilo e il suo bacino.  Lontano dal Nilo c'erano alcune oasi, ma la maggior parte della terra era arida. @L@LPer far arrivare l'acqua alle zone circostanti, nei villaggi furono  costruite delle cisterne. I portatori d'acqua trasportavano secchi pieni d'acqua  del Nilo e li rovesciavano nelle cisterne. @L@LGli Egizi sapevano anche come scavare dei pozzi. Per ottenere il loro pozzo,  gli operai di un insediamento vicino a Giza dovettero scavare attraverso 100  metri di roccia. La maggior parte dei pozzi era protetta da un casotto. Da qui,  le persone scendevano lungo una scala fino al livello dell'acqua e riempivano le  loro brocche."
        }
    }
    message_nile {
        id: 157,
        
        size [30, 20]
        image {
            id: 87,
            pos [15, 15]
        }
        title {
            text: "Il Nilo",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Senza il Nilo, la civiltà egizia semplicemente non sarebbe esistita.  In una regione in cui le piogge sono scarse, il Nilo fornisce una continua fonte  d'acqua per le persone e il terreno. Con l'inondazione dei campi su base più o  meno costante, il Nilo inoltre fertilizza il suolo. @L@LL'importanza del Nilo era assai palese per gli antichi egizi. Per loro, il  Nilo rinvigoriva la terra dopo ogni straripamento e così anche le tradizioni  religiose ne furono influenzate, in particolare sull'esistenza di un aldilà. @L@LIl calendario egizio era diviso in stagioni che prendevano il nome dai vari  stati del fiume. Il periodo di straripamento, cioè quando il Nilo allagava i  campi circostanti, si chiamava akhet. L'inondazione avveniva a causa dei monsoni  che ogni anno soffiavano alle fonti del Nilo Blu, sull'altopiano etiopico. Il  ritiro delle acque, o proyet, segnava il momento in cui il Nilo restituiva la  terra emersa. Il tempo del raccolto era chiamato shomu, a volte tradotto anche  con la parola siccità."
        }
    }
    message_dentistry {
        id: 158,
        
        size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Dentisti" }
        subtitle { text: "Storia" }
        content {
            text: "L'odontoiatria era uno dei molti campi in cui un dottore egizio  poteva specializzarsi. Alcuni antichi resti provano che i dentisti non avevano  vita facile. Il decadimento dei denti era accelerato dalla sabbia onnipresente.  La sabbia arrivava dappertutto, anche nel cibo, e la sua abrasione sui denti  rovinava in fretta lo smalto protettivo. Le carie dei denti spesso comportavano  degli ascessi, che potevano far cadere i denti o portare anche alla morte. @L@LI papiri medici illustrano come i dentisti affrontavano il loro lavoro. Ad  esempio, se un dente cadeva, il dentista lo legava a un dente vicino con filo  argento o d'oro. Ci sono anche delle ricette per riempire i denti cavi, con  resina e malachite, ma gli archeologi non hanno mai trovato un dente che riporti  tracce di tali componenti. @L@LIn compenso, gli archeologi hanno trovato degli strumenti che pensano  servissero da spazzolini. Per ora, tra le varie scoperte, non sono ancora stati  rinvenuti degli antichi fili interdentali."
        }
    }
    message_apothecary {
        id: 159,
        
        size [30, 20]
        image {
            id: 89,
            pos [15, 15]
        }
        title {
            text: "Farmacie",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Le antiche pratiche mediche e farmaceutiche egizie sono ben  documentate. La religione era comunque coinvolta nella guarigione delle malattie  e tutte le cure prescritte comportavano preghiere e incantesimi. I papiri medici  descrivono cure specifiche, alcune delle quali piuttosto originali secondo i  nostri standard. Per curare l'indigestione, ad esempio, si macinava un dente di  maiale e la polvere veniva introdotta in quattro torte. Il paziente doveva  mangiare una di queste torte al giorno, e alla fine l'indigestione sarebbe  passata. Una cura contro la calvizie prevedeva vertebre di corvo, uno zoccolo  d'asino bruciato e il grasso di un serpente nero."
        }
    }
    message_medicine {
        id: 160,
        
        size [30, 20]
        image {
            id: 90,
            pos [15, 15]
        }
        title {
            text: "Medicina",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Come altre componenti della società egizia, la professione medica era  assai segmentata e burocratizzata. L'organizzazione prevedeva delle linee  gerarchiche, con dottori che detenevano titoli come anziano, ispettore,  supervisore e maestro dei medici. Il dottore di rango più elevato era il 'capo  dei medici del nord e del sud'. @L@LI dottori acquisivano la loro conoscenza studiando testi e organi di  animali, ma non osservando i procedimenti di imbalsamazione. La medicina era  nettamente separata dai riti funerari. @L@LLa buona salute era legata al concetto di metu. Il cuore era il centro del  corpo e tutte le parti del corpo erano collegate al cuore tramite i metu, o  canali. I metu erano molto più di un sistema sanguigno, in quanto includevano  qualsiasi sistema del corpo umano. La malattia si verificava quando una parte  dei metu era bloccata. @L@LPer curare una malattia, i dottori prescrivevano medicine e preghiere. Per  ulteriori informazioni sulle pratiche farmaceutiche, vedi le @159farmacie. @L@LGLi antichi egizi, tra le altre malattie, soffrivano di poliomelite,  tubercolosi e malaria. Inoltre, erano inclini a soffrire di malanni portati da  vermi parassiti."
        }
    }
    message_embalmers {
        id: 161,
        
        size [30, 20]
        image {
            id: 23,
            pos [15, 15]
        }
        title {
            text: "Imbalsamatori",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'imbalsamazione era la procedura fondamentale dei riti funerari  egizi. Il ka, o spirito, del deceduto richiedeva un luogo dove vivere  nell'aldilà, e quindi aveva bisogno del suo corpo. Durante il procedimento di  imbalsamazione, il corpo veniva prima bagnato nelle acque del Nilo, per  simboleggiare la rinascita. Poi venivano rimossi gli organi interni e quindi  conservati in piccole giare. L'unico organo scartato era il cervello (che veniva  aspirato dal naso) in quanto gli antichi egizi credevano che non avesse alcuna  funzione. Le giare venivano seppellite con il corpo. @L@LDopo la rimozione degli organi interni, l'imbalsamatore riempiva le cavità  del corpo con profumi, oli e tela di lino, quindi lo richiudeva. In seguito, il  corpo veniva ricoperto di natron, un tipo di sale. Dopo 70 giorni, il corpo  veniva ancora sciacquato, avvolto in bende di lino e ricoperto di catrame. Il  catrame aiutava a uccidere i batteri e i funghi che altrimenti ne avrebbero  causato la decomposizione. @L@LDato l'alto costo dell'imbalsamazione, solo i cittadini più ricchi potevano  permettersela."
        }
    }
    message_shrine_and_temple {
        id: 162,
        
        size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Santuari e templi", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "I templi erano considerati la residenza degli dei, e ciascuno era  dotato di schiere di @384sacerdoti al servizio della divinità. I cittadini  avevano la loro parte nel servizio agli dei con le offerte, ma raramente  potevano vedere la statua di un dio, presente all'interno di ogni tempio. Essi  potevano scorgerla solo durante le festività, quando il dio era trasportato per  le strade cittadine su una piccola nave cerimoniale. @L@LGli Egizi si rivolgevano agli dei per ottenere consigli. Tutti erano i  benvenuti nel cortile di fronte al tempio, e da qui potevano dialogare con gli  dei su argomenti che li preoccupavano o chiedere perdono per gli errori  commessi. I sacerdoti, nascosti nel tempio, rispondevano ai questuanti. I  cittadini potevano anche consultare gli dei nei giorni di festa a loro dedicati. @L@LOltre a rendere omaggio ai templi, molti egizi avevano dei santuari in casa.  Spesso il santuario era dedicato a Bes, la dea protettrice della casa. Ma anche  gli individui avevano il loro santo protettore. Nei famosi registri di Deir el- Medina, i lavoratori erano a volte assenti per celebrare la 'festività del loro  dio'. @L@LIl concetto di patrono si estendeva anche a città, villaggi e regioni. Come  conseguenza, spesso, durante la storia egizia, troviamo dei cambi di divinità  venerate in diversi periodi storici. Per ulteriori informazioni sull'evoluzione  della religione, cliccate @399qui."
        }
    }
    message_school_and_eduction {
        id: 163,
        
        size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "Scuole ed educazione", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "L'educazione dell'antico Egitto era estremamente pratica. Ogni  individuo era educato per una precisa professione. Per molti, l'educazione era  sinonimo di apprendistato, e i figli generalmente diventavano apprendisti dei  padri per imparare il loro mestiere. Anche alcune ragazze erano apprendisti, per  diventare, ad esempio, danzatrici, cantanti o tessitrici, ma, per la maggior  parte, imparavano l'arte di gestire la famiglia. @L@LGli scribi ricevevano un tipo di educazione più formale. Le scuole degli  scribi, chiamate Per-Ankh o 'casa della vita', erano collegate ai templi. Qui, i  futuri scribi imparavano le lingue scritte, prima lo ieratico e più tardi il  demotico, entrambe utilizzate quotidianamente. Gli scribi imparavano la loro  arte copiando i manoscritti sulle ostraca, o vecchi pezzi di pietra. Solo quando  erano divenuti padroni del loro mestiere, potevano cimentarsi con i papiri. La  disciplina era durissima, e i casi di punizioni fisiche erano assai frequenti.  L'educazione degli scribi era generalmente impartita tra i 10 e i 20 anni di  età."
        }
    }
    message_library_and_literature {
        id: 164,
        
        size [30, 20]
        image {
            id: 91,
            pos [15, 15]
        }
        title {
            text: "Biblioteche",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Grazie alla lingua scritta, gli Egizi registrarono molte delle loro  storie, poemi e inni. Questi testi erano conservati in biblioteche collegate  alle Per-Ankh (Casa della Vita) o alle @163Scuole degli Scribi, adiacenti al  tempio.  @L@LLa letteratura egizia nacque dalla tradizione orale, e per la maggior parte  veniva trascritta come se si trattasse di appunti per un cantastorie. Gran parte  degli Egizi era analfabeta, e molti @387scribi erano dei cantastorie che usavano  gli scritti per ricordarsi le storie, gli inni o i poemi. Chi sapeva leggere, e  in particolare chi frequentava la corte del Faraone, poteva accedere alle  biblioteche e consultare i papiri in prima persona. Alcuni tra i cittadini più  ricchi possedevano delle biblioteche personali. @L@LL'antica letteratura egizia può essere divisa in molti generi diversi, tra  cui l'autobiografia, racconti avventurosi, leggende popolari, mitologia, lamenti  funebri, poesia e inni. Di questi generi, l'autobiografia è il più antico e  deriva dalla tradizione di scolpire le tombe con le imprese compiute dai  defunti. Anche la satira era un genere assai popolare."
        }
    }
    message_history_entertainment {
        id: 165,
        
        size [30, 20]
        image {
            id: 92,
            pos [15, 15]
        }
        title {
            text: "Divertimento",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli antichi egizi potevano scegliere tra diversi tipi di  divertimento. Gli sport erano assai comuni, specialmente quelli in acqua, come  il canottaggio e il nuoto (i più ricchi potevano permettersi una piscina  privata). Gli Egizi sono inoltre la prima società che si è dedicata alla pesca  come sport. @L@LIl pugilato era uno sport che attirava molte persone, con incontri  organizzati per divertire il Faraone. Tra gli altri sport troviamo la pallamano,  una specie di hockey su prato, la ginnastica, il tiro con l'arco e il  sollevamento pesi. @L@LPer gli eruditi, la lettura era un passatempo diffuso: la prima storia corta  conosciuta è in antico egizio. La poesia era popolare, ma non c'è alcuna traccia  di commedie egiziane. Per ulteriori informazioni sulla lettura, scrittura e  letteratura, si vedano le @164biblioteche. @L@LAnche le @393festività erano una parte importante della vita egizia."
        }
    }
    message_children {
        id: 166,
        
        size [30, 20]
        image {
            id: 93,
            pos [15, 15]
        }
        title {
            text: "Bambini",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Nell'antico Egitto, i bambini erano considerati una benedizione, in  quanto rappresentavano la continuazione della vita. I matrimoni avvenivano  abbastanza presto, così da permettere una nutrita schiera di figli. I bambini  più poveri seguivano i loro genitori nei campi e aiutavano a mietere il  raccolto. I bambini di classe più agiata passavano il tempo a casa con la madre.  Quando erano cresciuti a sufficienza, i ragazzi di ceto alto andavano a scuola e  quindi diventavano apprendisti dei loro padri. @L@LI bambini egizi avevano molti giochi e giocattoli, tra cui palloni, bambole,  trottole e animali in legno. Inoltre, potevano divertirsi come facevano i loro  genitori, con il nuoto o la pesca. @L@LBambini e genitori avevano anche degli animali domestici. Cani e gatti erano  assai diffusi, così come le scimmie ammaestrate, uccelli, gazzelle e, per i più  ricchi e coraggiosi, leoni."
        }
    }
    message_history_population {
        id: 167,
        
        size [30, 20]
        image {
            id: 94,
            pos [15, 15]
        }
        title {
            text: "Popolazione egizia",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'antico Egitto è, sotto molti punti di vista, simile alla società  moderna. Molte persone vivevano in centri urbani, dove l'industria forniva loro  il lavoro. I contadini vivevano in villaggi rurali più piccoli. Ovviamente, il  grosso della popolazione viveva vicino al fiume. @L@LLa dimensione della popolazione egizia è cresciuta con il tempo, soprattutto  con lo sviluppo dell'@154irrigazione. Durante il periodo pre-dinastico, la  popolazione è stimata intorno alle 350.000 anime. Alla fine del II millennio  a.C., quando le pratiche di irrigazione si erano diffuse e avevano aumentato la  disponibilità di terra coltivabile, si stima che la popolazione avesse raggiunto  i 3 milioni di anime."
        }
    }
    message_history_society {
        id: 168,
        
        size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Società egizia", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "La società egizia era altamente stratificata con classi nettamente  separate. Per la maggior parte, le persone continuavano ad appartenere alla  classe in cui erano nate, anche se vi erano alcuni casi in cui alcuni individui  accedevano alla classe superiore con un matrimonio. @L@LGli appartenenti alla classe più bassa erano i contadini. Essi avevano la  vita più faticosa e sacrificata, costantemente al lavoro nelle fattorie o nei  cantieri di costruzione. I resti confermano che in maggioranza soffrivano di  problemi alla schiena, e alcune vertebre erano addirittura fuse insieme, come  risultato del duro lavoro. Vivevano in semplici abitazioni di poche stanze, ed  erano seppelliti in tombe altrettanto semplici, dato che non potevano  permettersi l'imbalsamazione. @L@LLa classe media era formata da artigiani, mercanti e altri individui che  lavoravano nelle industrie. Vivevano in case più grandi e alcuni di loro  potevano permettersi tombe in pietra o addirittura l'imbalsamazione. @L@LLa classe più ricca era costituita dagli alti funzionari del Regno. Essi  potevano permettersi i lussi più sfrenati, tra cui l'imbalsamazione e tombe  monumentali. La loro dieta era più ricca e varia di quella degli altri egiziani.  Dall'esame di alcuni resti mummificati, si è scoperto che il 10-20% soffriva di  arteriosclerosi - indurimento delle arterie - il che indica un grande consumo di  grasso animale e, forse, una vita stressante. I ricchi venivano spesso  raffigurati con grandi pancioni, per indicare il loro stato di benessere."
        }
    }
    message_history_juggling {
        id: 169,
        
        size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Giocolieri", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "Gli antichi egizi sono i primi a presentare dei giocolieri. Su una  tomba del Medio Regno, a Beni Hassan, alcuni dipinti illustrano giovani donne  che danno prova di vari giochi di abilità, tra cui il lancio di palle a cavallo  di maiali. @L@LIl significato di tali spettacoli nell'antico Egitto non è chiaro. Potevano  avere qualche implicazione religiosa, oppure appartenere alla sola sfera del  divertimento."
        }
    }
    message_history_music {
        id: 170,
        
        size [30, 20]
        image {
            id: 96,
            pos [15, 15]
        }
        title {
            text: "Musica",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli Egizi suonavano tutta una serie di strumenti musicali, tra cui  flauti (di molte forme e dimensioni), arpe, lire, liuti, tamburelli e altri  strumenti a percussione. I cantanti erano parte integrante della musica egizia,  e la maggior parte degli inni e dei poemi registrati su papiri doveva essere  cantata e suonata. @L@LGli strumenti a percussione erano utilizzati specialmente per accompagnare  le @171danze. Molti danzatori, o danzatrici, mentre ballavano suonavano anche  una specie di nacchere. @L@LGli Egizi suonavano anche le trombe. Le trombe erano uno strumento militare  (forse anche gli Egizi avevano la loro sveglia speciale) e spesso si trovano  nelle tombe di re o capi militari. Nella tomba di Tutankhamun sono state trovate  due trombe. Per capire quale potesse essere il loro suono, nel 1939 si è tentato  di suonarne una. Dopo qualche nota, la tromba cadde a pezzi (e venne  immediatamente ricomposta). La tromba era spesso associata a @376Osiride, dio  dell'agricoltura e del Nilo. @L@LAltri strumenti avevano anche un significato religioso. Il sistrum, una  specie di grosso sonaglio, era associato ad Hathor, dea della gioia, dell'amore  e delle festività. I flauti erano associati ad Amon, dio del sole."
        }
    }
    message_history_dance {
        id: 171,
        
        size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Danza", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "L'antica danza egizia si era evoluta dai rituali di propiziazione  eseguiti dai cacciatori. Il capo danzatore, chiamato il sacerdote-danzatore, era  responsabile della corretta esecuzione. @L@LPiù tardi, la danza divenne parte integrante delle festività e altre  cerimonie religiose, nonché forma di puro divertimento. I danzatori  professionisti si esibivano nelle piazze cittadine e potevano essere chiamati  per ravvivare le feste private. I danzatori erano spesso accompagnati con della  @170musica. Per lo più i danzatori professionisti erano in realtà danzatrici,  contraddistinte dal simbolo di Bes, dea della musica e della danza, tatuato  sulle cosce.  @L@LAlcuni cittadini danzavano anche come passatempo, anche se tale tipo di  passatempo era principalmente riservato alle classi inferiori. Maggiore era  l'importanza di un cittadino egizio, minore era la sua inclinazione alla danza.  Inoltre, uomini e donne non danzavano mai assieme. Le donne danzavano con altre  donne e gli uomini con altri uomini. @L@LPare che i passi di danza prendessero nome direttamente da ciò che  rappresentavano, come, ad esempio, 'un animale a spasso', 'la cattura di una  nave' e 'il pollo ballerino'."
        }
    }
    message_history_senet {
        id: 172,
        
        size [30, 20]
        image {
            id: 98,
            pos [15, 15]
        }
        title {
            text: "Taverne Senet",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il Senet era il gioco da tavolo più famoso dell'antico Egitto. La  plancia era rettangolare e divisa in 3 percorsi da 10 caselle l'uno. Si giocava  in due, e ciascun giocatore aveva almeno cinque pedine. Il movimento era  determinato dal lancio di quattro bastoncini. Le regole del Senet non sono state  registrate, quindi nessuno sa con precisione come si giocasse. Gli storici,  comunque, sono tutti d'accordo sul fatto che rappresentasse il viaggio verso  l'aldilà. Il backgammon e l'hopscotch sono discendenti del Senet. @L@LIl Senet, insieme ad altri giochi, era uno dei passatempi adottati nelle  taverne. Dopo una dura giornata di lavoro, molti egizi si ritiravano nella  taverna locale, dove si serviva @194birra e si poteva chiacchierare in libertà.  Uomini e donne - in particolare chi ancora non era spostato - frequentavano  spesso posti del genere."
        }
    }
    message_history_taxation_and_money {
        id: 173,
        
        size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Tasse", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "Gli antichi egizi pagavano le tasse al Faraone. Dato che gli Egizi  non avevano moneta, le tasse erano pagate in merci. Ad esempio, un contadino  doveva pagare al Faraone una certa quantità di grano. Gli scribi venivano  spediti in tutte le fattorie per determinare il dovuto di ciascuna."
        }
    }
    message_history_government_and_bureaucracy {
        id: 174,
        
        size [30, 20]
        image {
            id: 40,
            pos [15, 15]
        }
        title {
            text: "Governo e burocrazia",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il governo dell'antico Egitto era estremamente burocratizzato. Ogni  possibile compito veniva espletato da un funzionario dotato di titolo  altisonante. A capo di tutto e tutti c'era, ovviamente, il Faraone. Il braccio  del Faraone era il suo supervisore, responsabile dell'adempimento di tutti gli  ordini del Faraone. Sotto il supervisore c'erano i nomarchi (governatori  locali), i cancellieri, i viceré, i supervisori, i sindaci, ecc... E dato che  l'antico Egitto era una teocrazia, i sacerdoti avevano la loro parte di  responsabilità. @L@LMolti individui avevano più di una carica. Ad esempio, Imhotep, che servì  sotto Djoser I come supervisore della costruzione della piramide a gradoni,  aveva, tra gli altri, i titoli di Consigliere, Gran Sacerdote di Ptah e  Supervisore dei Lavori."
        }
    }
    message_history_pharaohs_home {
        id: 175,
        
        size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "La casa del Faraone", pos [125, 15] }
        subtitle { text: "Storia" }
        content {
            text: "La casa del Faraone era l'edificio più imponente della città. Se la  maggior parte delle case avevano al massimo due stanze, alcune magioni dei  Faraoni ne avevano a decine ed erano arredate e decorate con i migliori oggetti  dell'artigianato di tutto il Regno. @L@LCome per i funzionari di @174governo, gli Egizi impiegati dal Faraone  avevano dei titoli ed erano responsabili di compiti assai specifici. Tra gli  impiegati del Faraone, c'erano il Sovrintendente agli Affari di Casa, il Capo  Manicure e il Maggiordomo Reale. @L@LUn maggiordomo reale, di nome Nefer-Peret, aveva responsabilità molto  particolari. Nefer-Peret era responsabile della cura di quattro mucche  palestinesi, due egizie, un toro e un secchio di bronzo (niente meno)."
        }
    }
    message_history_gardens_and_public_art {
        id: 176,
        
        size [30, 20]
        image {
            id: 38,
            pos [15, 15]
        }
        title {
            text: "Giardini e arte pubblica",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Nell'antico Egitto i giardini erano molto popolari e molte case ne  avevano uno adiacente. Oltre a crescere @187frutta&e&verdura per complementare  la dieta quotidiana, i giardini offrivano un riparo dal sole cocente. Molti  giardini avevano alberi curati appositamente per fornire ombra. @L@LLe opere d'arte erano principalmente i monumenti e i templi cittadini. La  loro realizzazione richiedeva così tanto tempo e cure che il resto della città  poteva sembrare trascurato."
        }
    }
    message_history_trade {
        id: 177,
        
        size [30, 20]
        image {
            id: 30,
            pos [15, 15]
        }
        title {
            text: "Commercio",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Anche se l'antico Egitto era colmo di risorse naturali, tuttavia  mancavano alcuni tipi di merce. Gli Egizi aprirono vie commerciali con molte  regioni circostanti, tra cui la Nubia, il Libano, la Siria, il Punt (che alcuni  storici individuano nella costa della Somalia) e l'Egeo. Alcuni credono che il  commercio egizio si estendesse fino alle coste dell'attuale Turchia. @L@LIl Nilo, ovviamente, giocava un ruolo importante nel commercio. Il fiume era  navigabile fino alla prima cataratta, ovvero fino alle prime cascate rocciose.  Il Nilo fungeva quindi da 'autostrada' e facilitava il collegamento con la  Nubia. @L@LIl Nilo inoltre contribuiva alla produzione del prodotto egizio per  eccellenza: il grano. Lo straripamento era molto più affidabile delle piogge in  Libano o in Siria. Finché l'inondazione si verificava, l'Egitto aveva molto  grano in eccesso, un lusso che spesso il Libano e la Siria non potevano  permettersi. Tra le altre esportazioni dell'Egitto, troviamo tela di lino,  papiro, lenticchie, pesce essiccato, vasi d'oro e d'argento, pelli di bue e  corda. @L@LIn cambio, l'Egitto riceveva tutta un'altra serie di prodotti. Tra i  principali, citiamo l'oro della Nubia, il legno del Libano e l'olio d'oliva  della Siria. Gli Egizi importavano anche beni di lusso, come la mirra, il vino e  il bestiame. A volte gli Egizi importavano anche armi. @L@LLe carovane cariche di merce erano bersagli ambiti dai predoni. Per  proteggersi, le carovane assoldavano delle scorte armate che le accompagnassero  durante il viaggio. Per la presenza di tali scorte armate, alcuni storici  ritengono che gli Egizi non commerciassero liberamente con gli stati confinanti,  ma piuttosto che li costringessero a consegnare i loro prodotti. Anche se le  richieste forzose potevano giocare un ruolo importante nel commercio egizio,  alcuni papiri testimoniano normali negoziazioni tra l'Egitto e altre nazioni. @L@LAlcune missioni commerciali particolarmente importanti venivano celebrate  con iscrizioni e opere d'arte. Hatshepsut, un Faraone donna, inviò una flotta di  navi a Punt per procurarsi mirra, incenso, avorio e altre merci ricercate. Il  viaggio ebbe un successo tale che fu celebrato sui muri del tempo di Hatshepsut,  a Deir el-Bahri."
        }
    }
    message_history_ships_and_ship_making {
        id: 179,
        
        size [30, 20]
        image {
            id: 101,
            pos [15, 15]
        }
        title {
            text: "Navi e cantieri",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il Nilo ispirò i costruttori di barche per generazioni. Nel periodo  pre-dinastico, gli antichi egizi legavano fasci di canne di papiro per costruire  zattere spinte con dei lunghi pali. Con l'avvento delle costruzioni delle  piramidi, sorsero i primi cantieri navali. Le navi erano importanti per il  trasporto dei pesanti materiali necessari alla costruzione delle piramidi. @L@LCome altre industrie egizie, i cantieri erano di proprietà del governo.  Forniti di tutti gli strumenti adatti al loro lavoro, i costruttori creavano lo  scafo della nave accoppiando assi di legno e assicurandole con colla e corda  speciale che si ritirava con l'umidità. Quando le corde si ritiravano, lo scafo  era tenuto insieme alla perfezione. Gli scafi delle navi più grandi erano  dogati. Quando lo scafo era completo, i costruttori aggiungevano tutto il resto,  tra cui l'albero per la vela e i fori per i remi. Alcune tra le navi più grandi  avevano anche delle cabine. @L@LLe navi avevano un ponte molto largo, ed erano progettate con una linea di  galleggiamento molto alta. Il Nilo, anche se semplice da navigare, presentava  qualche secca o fondale basso, e le navi potevano arenarsi con facilità. @L@LI cantieri costruivano navi di grandi dimensioni. Una di queste, usata per  trasportare gli obelischi al tempio di Hatshepsut, era lunga 82 metri. Uno dei  più famosi ritrovamenti archeologici è la chiatta di Khufu. Ritrovata in circa  1.224 pezzi lungo il perimetro sud dell'omonima piramide, la chiatta fu  ricostruita nella prima metà degli anni '60. La nave era lunga oltre 43 metri e  larga 6, con sedute per 10 rematori più altri due al timone. Gli storici non  sanno esattamente quale fosse il significato della nave. Alcuni credono che  rappresentasse la nave solare di Horus. Altri pensano che fosse la chiatta che  trasportò i resti di Khufu alla piramide, oppure che quest'ultimo la utilizzasse  quando era in vita. A prescindere da ciò, la nave offre una chiara visione delle  tecniche utilizzate negli antichi cantieri navali egizi."
        }
    }
    message_history_enemies {
        id: 181,
        
        size [30, 20]
        image {
            id: 102,
            pos [15, 15]
        }
        title {
            text: "Nemici",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'Egitto era in frequente contatto con i suoi vicini e a volte le  relazioni non erano molto amichevoli. L'Egitto fu invaso diverse volte nel corso  della sua storia e quindi governato da stranieri. Questi stranieri, però,  assumevano il titolo di Faraone e fino all'invasione persiana, gli Egizi  riuscirono sempre a riottenere la loro terra. Ma non era sempre l'Egitto a  essere sotto attacco. Durante il Nuovo Regno, l'Egitto cercò di espandere i  propri confini invadendo le nazioni circostanti. @L@LTra le popolazioni attaccate ci furono i nubiani e i kush. L'Egitto invase  la Nubia abbastanza presto (circa nel 2900 a.C.), più che altro per sfruttare le  sue ricche miniere d'oro e di rame. Più tardi, la Nubia contraccambiò il favore  e l'Egitto fu governato da parecchi Faraoni nubiani. @L@LL'Egitto entrò in guerra anche con diverse popolazioni oltre la penisola del  Sinai. Tra questi ci furono i canaaniti, i filistei, i beduini (allora presenti  nella moderna Siria) e gli ittiti. Ma la popolazione più importante fu quella  degli hyksos. Durante il secondo periodo del Medio regno, gli hyksos governarono  l'Egitto. Mantennero molte delle pratiche culturali, ma introdussero numerose  innovazioni, come i carri trainati dai cavalli. Gli hyksos guidarono l'Egitto  per circa 100 anni finché Ahmose I li sconfisse e riprese il potere. @L@LA occidente, l'Egitto entrò in guerra con le tribù del Libano, in  particolare i tehenu e i temehu. Questi cercarono di penetrare nel territorio  del delta egiziano, ma furono sconfitti da Sethos I. Per tenere a bada le tribù  occidentali, furono costruiti dei @182forti. @L@LInfine, il potente Impero Romano raggiunse la terra d'Egitto durante il  regno dei Tolomei. La scarsa forza militare egizia e la sua ricchezza in oro e  risorse naturali (per non parlare della fuggevole Cleopatra VII) attirarono  l'attenzione di Giulio Cesare e dei suoi successori. L'arrivo delle legioni di  Cesare sul suolo egizio segnò l'inizio della fine del lungo dominio egizio sul  Mediterraneo e infine ridusse l'orgoglioso Egitto a un semplice stato vassallo. @L@LClicca @184qui per ulteriori informazioni sull'esercito egizio."
        }
    }
    message_history_defensive_structures {
        id: 182,
        
        size [30, 20]
        image {
            id: 103,
            pos [15, 15]
        }
        title {
            text: "Strutture di difesa",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'Egitto proteggeva le sue città con torri e mura. Le mura erano  generalmente in mattoni ed erano disposte a cerchio o a quadrato attorno alla  città. Gli scavi a Elefantine, situata in Egitto meridionale, vicino al confine  nubiano, hanno rivelato un muro spesso e curvo, inframezzato da torri semi- circolari.  @L@LL'Egitto difendeva i suoi confini con una serie di fortezze. Tra le più  famose citiamo il 'Muro del Principe', una serie di 13 fortezze costruite lungo  la sponda orientale del Nilo."
        }
    }
    message_history_law {
        id: 183,
        
        size [30, 20]
        image {
            id: 104,
            pos [15, 15]
        }
        title {
            text: "Legge egizia",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli Egizi che lamentavano dei torti potevano rivolgersi ai  magistrati. Secondo la gravità del torto, il caso poteva essere esaminato dal  magistrato locale o dal supervisore in persona. I magistrati locali a volte  erano ufficiali cittadini di grado non elevato, come il capo dei lavoratori. Gli  scribi presenziavano alla discussione e registravano partecipanti, testimoni,  prove e punizioni. @L@LTutti erano soggetti alla legge, sia le classi povere che quelle ricche. In  una scena scolpita sulla Mastaba (cappella funeraria) di un supervisore del  Vecchio Regno, si vedono dei governatori locali puniti per aver trattenuto parte  delle tasse. Anche le donne partecipavano attivamente ai processi. In un caso,  una donna ottenne la proprietà che era stata illegalmente affidata ai suoi  parenti. In un altro, una donna fu trovata colpevole per aver rubato uno  strumento e un contenitore da un santuario di Amun. @L@LLe punizioni potevano essere molto severe e spesso contemplavano pene  fisiche o lavori forzati. Durante la XVIII dinastia del Nuovo Regno, la  punizione per aver rubato delle pelli era cento frustate e cinque ferite aperte.  Alcuni crimini particolarmente atroci erano punibili con il taglio del naso e  l'espulsione dall'Egitto. @L@LLa legge egizia non era strettamente codificata, e le pene venivano inflitte  caso per caso. Tuttora esistono alcuni elenchi di casi e relative punizioni, in  voga nel Nuovo Regno, ma spesso le voci sono contraddittorie. @L@LLa giustizia era un concetto importante anche nell'aldilà. Prima che una  persona potesse entrare nell'altro mondo, doveva effettuare una 'confessione al  negativo', elencando tutte le cose che non aveva fatto durante la vita. Dopo  tale confessione, il cuore della persona veniva pesato con una piuma tolta dal  copricapo di Ma'at. Se il cuore pesava come la piuma, la persona poteva entrare  nell'aldilà; se era invece più pesante della piuma, esso veniva mangiato dal  mostro Ammit e la persona non aveva la possibilità di entrare nell'altro mondo."
        }
    }
    message_history_military {
        id: 184,
        
        size [30, 20]
        image {
            id: 105,
            pos [15, 15]
        }
        title {
            text: "Esercito",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'esercito egizio si sviluppò lungo i vari millenni di governo  Faraonico. Nel Vecchio Regno, gli eserciti erano radunati solo in caso di  necessità ed erano normalmente composti dai nobili e dai loro seguaci oppure da  stranieri. Il Vecchio Regno non aveva un esercito di soldati professionisti. Gli  uomini che servivano nell'esercito provenivano da qualsiasi tipo di professione  e, probabilmente, vi ritornavano quando i combattimenti terminavano. @L@LCon il Nuovo Regno, invece, la struttura dell'esercito era cambiata. Esso  era diviso in unità di fanti e auriga. La fanteria era inoltre divisa in due  parti: chi era specializzato nei combattimenti corpo a corpo e chi con le armi  da tiro. I carri venivano utilizzati per il combattimento a distanza su largo  raggio. I soldati con archi e frecce salivano sui carri e da lì puntavano contro  l'esercito nemico. Anche i combattimenti navali erano frequenti, anche se la  marina non era una divisione a sé stante. Essa faceva parte delle forze di  terra, e i soldati imbarcati erano descritti con gli stessi termini utilizzati  per i fanti. Gli stranieri formavano una gran parte dell'esercito. Nubiani,  libici, asiatici e cariani combattevano tutti dalla parte dell'Egitto. @L@LNel Vecchio Regno, l'esercito egizio era organizzato in battaglioni. Nel  Nuovo Regno, i battaglioni furono separati in divisioni, che prendevano il nome  dagli dei. Scribi e amministratori seguivano l'esercito in battaglia,  probabilmente per tenere traccia delle azioni. @L@LCliccate @196qui per ulteriori informazioni sulle armi a disposizione  dell'esercito egizio."
        }
    }
    message_history_grain_and_barley {
        id: 185,
        
        size [30, 20]
        image {
            id: 106,
            pos [15, 15]
        }
        title {
            text: "Grano e orzo",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Le coltivazioni di grano e orzo producevano la materia prima per il  cibo principale dell'antico Egitto: il pane. Il grano veniva trasformato in  farina e quindi cotto in pagnotte. Per ulteriori informazioni sul pane ottenuto  con l'orzo, si veda la @194Birra. @L@LGli Egizi usavano tre tipi di grano, ma prima di diventare farina dovevano  essere lavorati. Nella trebbiatura, le spighe venivano disposte al suolo per  essere calpestate da grossi e pesanti animali. Con questo passaggio si  separavano i grani dalle spighe. Poi, il grano veniva ulteriormente ripulito  dalle parti spurie con dei setacci o gettandolo in aria. Il vento portava via le  parti più leggere, mentre i grani, più pesanti, ricadevano al suolo. Dopo questo  procedimento, il grano veniva portato nei @5granai. Qui i chicci venivano  macinati e la farina conservata per usi futuri. @L@LPer fare il pane, si preparava una pagnotta e la si metteva in contenitori  di ceramica di forme diverse. La forma più popolare era il cono. La pagnotta  veniva cotta in un forno circondato da cenere e carboni ardenti. Il pane era  cotto sia in casa che nei forni dei panettieri. Gli archeologi affermano che i  panettieri non erano certo tra le persone più in salute, dato l'alto  quantitativo di cenere nell'aria."
        }
    }
    message_history_cattle_ranching_and_fishing {
        id: 186,
        
        size [30, 20]
        image {
            id: 13,
            pos [15, 15]
        }
        title {
            text: "Bestiame e pesca",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli Egizi allevavano numerosi animali da trasformare in cibo. I tipi  prevalenti erano animali dotati di lunghe corna. Questi erano guardati da  pastori che numerosi dipinti funerari ritraggono come alti, magri e sbarbati. Il  bestiame veniva condotto nei pascoli per nutrirsi. A volte, gli animali venivano  condotti sui campi appena falciati per mangiare la paglia e altre parti di  scarto. @L@LGli Egizi allevavano anche pecore, capre e maiali, nonché oche e altri  volatili. Venivano allevati anche i cavalli, non per il cibo, ma per il traino  dei carri dei nobili egizi. Il cavallo fu introdotto in Egitto dagli hyksos, uno  dei popoli @181invasori dell'Egitto. @L@LIl pesce forniva una fonte di cibo alternativa, anche se pare che fosse  mangiato principalmente dalle classi più povere. Gli Egizi pescavano in modi  diversi. Alcuni salivano sulle canoe e pescavano con una canna, per catturare un  pesce alla volta. A volte si costruivano delle trappole per catturare grandi  quantità di pesce. Il metodo di pesca più efficiente era la rete a strascico.  Dato che la pesca era assai abbondante, per portare la rete a riva occorrevano  ben due barche cariche di pescatori. @L@LLa professione di pescatore era anche pericolosa. Una specie di pesce gatto  era dotato di un aculeo velenoso sulla pinna dorsale e i coccodrilli si  aggiravano ovunque. I pescatori sulle barche erano abbastanza al sicuro, ma se  la barca si rovesciava, i coccodrilli non tardavano ad arrivare."
        }
    }
    message_history_fruits_and_vegetables {
        id: 187,
        
        size [30, 20]
        image {
            id: 107,
            pos [15, 15]
        }
        title {
            text: "Frutta e verdura",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "@185Grano e orzo erano il cibo principale degli antichi egizi, ma  essi coltivavano anche molti tipi di frutta e verdura. Fagioli, ceci, lenticchie  e piselli erano molto popolari, così come aglio, cipolle, porri, lattuga e  cocomeri. Tra i vari tipi di frutta, citiamo fichi, datteri, uva e melograni. I  datteri in particolare erano diffusi tra le classi più povere ed erano  utilizzati per insaporire la birra. Gli Egizi inoltre speziavano il cibo con  cannella, coriandolo, cumino, aneto e senape."
        }
    }
    message_history_reeds {
        id: 188,
        
        size [30, 20]
        image {
            id: 108,
            pos [15, 15]
        }
        title {
            text: "Papiro",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Alte a volte più di otto metri, le canne di papiro non erano  utilizzate solo per fabbricare la carta. Il papiro veniva trasformato in diversi  oggetti di uso casalingo, come stuoini, sandali e corda. Il midollo poteva anche  essere mangiato. A volte, si usava lo stelo della pianta come sostituto del  legno, e gli steli più grossi si potevano legare insieme per fabbricare una  specie di zattera. Il papiro è arrivato quasi all'estinzione, ma oggi gode di un  periodo di rinascita. Il papiro viene nuovamente raccolto e lavorato per  fabbricare la carta - questa volta da vendere ai turisti."
        }
    }
    message_history_flax {
        id: 189,
        
        size [30, 20]
        image {
            id: 109,
            pos [15, 15]
        }
        title {
            text: "Lino",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il lino era coltivato per fabbricare la @398tela che rappresentava,  nell'antico Egitto, l'industria tessile principale. Dato che il gambo era la  parte più importante, ogni pianta doveva essere strappata dal suolo, invece che  essere tagliata, per cui il raccolto era un processo assai lento. Dopo il  raccolto, le radici e i semi venivano rimossi, mentre i gambi venivano distesi a  seccare. Poi, i gambi si immergevano in acqua per due settimane, e quindi  battuti contro le pietre per separare le singole fibre. Le fibre venivano  portate ai tessitori che le trasformavano in tessuto."
        }
    }
    message_history_clay {
        id: 190,
        
        size [30, 20]
        image {
            id: 110,
            pos [15, 15]
        }
        title {
            text: "Argilla",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Nell'antico Egitto, l'argilla si otteneva facilmente, e la sua  qualità variava di regione in regione. Lungo il Nilo, gli anni di inondazione  avevano creato dei ricchi depositi di fango, pronto da asportare e trasformare  in vasellame. Nelle regioni desertiche, si potevano trovare delle vene di scisti  e micascisti nella roccia calcarea. L'argilla del deserto risultava in vasi più  robusti e dava loro un colore rosa o azzurro. I vasi fabbricati con l'argilla  del Nilo tendevano invece al rosso o al nero. Entrambi i tipi di argilla erano  lavorati nello stesso modo per fabbricare @198vasellame."
        }
    }
    message_history_gold_and_gold_mining {
        id: 191,
        
        size [30, 20]
        image {
            id: 22,
            pos [15, 15]
        }
        title {
            text: "Oro e miniere d'oro",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "L'oro si trovava principalmente nel deserto orientale egiziano e in  Nubia. L'estrazione dell'oro poteva essere un compito molto difficile. Nel  deserto orientale, ad esempio, le vene d'oro erano contenute nel granito. Il  granito veniva ridotto in polvere e quindi immerso in acqua per separare l'oro  dalla roccia. Questo procedimento era ovviamente molto lento. Nonostante ciò,  l'oro era abbondante ed era, in effetti, più facile da estrarre dell'argento. @L@LPer prepararlo alla lavorazione, esso veniva prima fuso presso le miniere.  Dopo la fusione, veniva versato in acqua. Durante il raffreddamento, l'oro si  coagulava in pepite che venivano portate agli orafi per la lavorazione. @L@LCome accadeva per ogni altro bene, l'inventario dell'oro era mantenuto dagli  scribi. Ogni mattina, essi lo pesavano con attenzione presso gli orafi, e il  lavoro di quest'ultimi era controllato con molta attenzione, per assicurarsi che  non lo rubassero.  @L@LAnche se l'oro era più abbondante dell'argento, certo non ne avanzavano  grandi quantità. Come risultato, la maggior parte degli oggetti non era  fabbricata in oro pieno, ma soltanto placcata."
        }
    }
    message_history_wood_and_its_uses {
        id: 192,
        
        size [30, 20]
        image {
            id: 111,
            pos [15, 15]
        }
        title {
            text: "Legno e suoi utilizzi",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "In Egitto, gli alberi nativi non erano abbondanti. Anche se il suolo  dei campi di limo era fertile a sufficienza per crescere gli alberi, lo  straripamento stesso li avrebbe sradicati prima che potessero crescere. Tra gli  alberi che riuscivano a crescere in Egitto, troviamo il sicomoro, le palme da  dattero e il rafano. Ciascuno di essi aveva un preciso significato religioso ed  era ritenuto dimora degli dei. @L@LDato tale significato, i taglialegna dovevano ricevere un permesso speciale  prima di abbatterli. Gli alberi tagliati fornivano un legno fragile che aveva  limitati usi pratici. L'Egitto importava molto legno dal Libano, dalla Siria e  da Israele. Quando l'Egitto conquistò questi paesi, durante il Nuovo Regno, fece  razzia di legno senza curarsene troppo, riducendo drasticamente la riserva di  alberi. @L@LIl legno era utilizzato per mobili, sarcofagi e costruzioni. Gli artigiani  del legno erano molto abili nel ricavare pezzi finemente lavorati con tanto di  intarsi e incisioni."
        }
    }
    message_history_quarries {
        id: 193,
        
        size [30, 20]
        image {
            id: 112,
            pos [15, 15]
        }
        title {
            text: "Cave",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli Egizi estraevano diversi tipi di roccia per la costruzione di  piramidi, templi e monumenti; tra questi vi erano il calcare, il granito,  l'arenaria, il basalto, l'ardesia, l'alabastro e il porfido. I cavatori erano  equipaggiati con picconi e ceselli per estrarre la roccia dura, e seghe di rame  per estrarre quella più tenera. @L@LLa maggior parte delle cave funzionava nel periodo di inondazione, quando i  progetti di costruzione erano al loro massimo svolgimento. Alcune cave  funzionavano tutto l'anno, soprattutto se era in corso una costruzione molto  grande, come una piramide. @L@LPer trasportare i blocchi a destinazione, questi venivano caricati su delle  slitte trascinate da squadre di manovali. Per facilitare il trasporto, spesso si  posavano anche dei tronchi che fungessero da rulli. In altri casi, si inumidiva  il suolo davanti alla slitta per diminuire l'attrito. @L@LNelle cave, gli schiavi costituivano parte della forza lavoro, anche se per  lo più era costituita da cittadini egizi."
        }
    }
    message_history_beer {
        id: 194,
        
        size [30, 20]
        image {
            id: 113,
            pos [15, 15]
        }
        title {
            text: "Birra",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La birra era la bevanda preferita degli antichi egizi. Ancora oggi si  discute sui vari particolari di tale industria. Come si otteneva la birra? Era  insaporita con della frutta? Era birra di orzo o di grano? E per il malto? La  ricerca è tuttora impegnata ad appianare tali dubbi. @L@LBasandoci sulle illustrazioni trovate nelle tombe egizie, un metodo era  costituito dalla cottura di una pagnotta speciale. Il pane veniva poi  sbriciolato e messo in un setacciato. Poi, si utilizzava l'acqua per formare una  poltiglia che si lasciava in seguito fermentare. Le donne erano le prime  impiegate nella fabbricazione della birra e i papiri parlano di 17 tipi di  bevanda. @L@LGli Egizi bevevano la birra in boccali particolari. Questi erano dotati di  un becco ad angolo, più o meno come se fosse una cannuccia. Alla fine del becco  c'era un filtro, che separava il materiale solido da quello liquido. Oltre a  bere la birra a casa, gli Egizi la bevevano anche nelle taverne. Per ulteriori  informazioni sulle taverne, cliccate @172qui."
        }
    }
    message_history_papyrus_making {
        id: 195,
        
        size [30, 20]
        image {
            id: 48,
            pos [15, 15]
        }
        title {
            text: "Fabbricazione dei papiri",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La fabbricazione dei papiri era un procedimento impegnativo. Prima di  tutto, occorreva rimuovere la scorza per esporre il midollo. I midolli venivano  posti su un pezzo di tessuto uno di fianco all'altro, leggermente sovrapposti.  Quando si raggiungeva la larghezza desiderata, si disponevano altre strisce di  midollo sopra le precedenti, ma ad angolo retto. Quindi si posava un secondo  pezzo di tessuto, e il midollo veniva battuto con pesanti pezzi di legno o dei  martelli. La battitura dei midolli formava un composto omogeneo. Il papiro  veniva in seguito appeso ad asciugare al sole e spesso la superficie veniva  lucidata con una pietra."
        }
    }
    message_history_weapons {
        id: 196,
        
        size [30, 20]
        image {
            id: 114,
            pos [15, 15]
        }
        title {
            text: "Armi",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "In battaglia, gli antichi egizi impiegavano armi diverse. Per i  combattimenti corpo a corpo i soldati usavano mazze, daghe o spade larghe e  asce. L'arma principale per il combattimento a distanza era l'arco, anche se  venivano utilizzate anche delle fionde. L'armamento egizio si sviluppò con il  tempo, in particolare con l'invasione degli hyksos. Gli hyksos introdussero i  cavalli e i carri da guerra."
        }
    }
    message_history_luxury_goods {
        id: 197,
        
        size [30, 20]
        image {
            id: 115,
            pos [15, 15]
        }
        title {
            text: "Oggetti di lusso",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Cibo, bevande e vestiti erano sufficienti per i contadini, ma le  classi più agiate richiedevano prodotti diversi per mantenere il loro stile di  vita. Tra questi, i principali erano i prodotti di bellezza. Uomini e donne si  truccavano gli occhi, con il nero di khol o la malachite. Gli Egizi credevano  che il trucco degli occhi, oltre a migliorare il loro aspetto, proteggesse la  vista. Le donne usavano l'henna come smalto per unghie a volte come tintura per  i capelli. @L@LPer gli antichi egizi, la pulizia era importante, e oltre a bagni regolari,  si profumavano con essenze e oli vari. A questo scopo, si usavano sia la mirra  che l'incenso. @L@LLegato al concetto di pulizia era l'uso delle parrucche. La maggior parte  degli Egizi teneva i capelli corti, probabilmente per prevenire i parassiti, e  si adornava il capo con parrucche. Le parrucche erano di vario genere, e le  donne ne avevano più di una. Esse erano fatte di capelli umani, legati alla base  della parrucca con stringhe minute. @L@L@382Per i ricchi, i gioielli erano un altro importante genere di lusso."
        }
    }
    message_history_pottery {
        id: 198,
        
        size [30, 20]
        image {
            id: 25,
            pos [15, 15]
        }
        title {
            text: "Vasellame",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Ben poche case erano prive di vasellame. La fabbricazione dei vasi,  una delle industrie più antiche, nasceva nelle case, dove le donne fabbricavano  i contenitori necessari per cucinare. Come altre industrie egizie, tale pratica  si trasformò poi in una professione svolta in laboratori specializzati. @L@LLa prima fase della fabbricazione richiedeva la preparazione  dell'@190argilla. Questa doveva essere impastata e mischiata con paglia per  aumentare la coesione dell'amalgama. Gli uomini impastavano con mani e piedi,  camminando sopra l'argilla per renderla lavorabile. L'argilla veniva poi posta  su una ruota, per darle una forma. @L@LLa ruota dei vasai si sviluppò con il tempo. Nella sua prima forma, il  vasaio l'azionava con una mano mentre plasmava l'argilla con l'altra. Dato che  il vasaio non poteva azionare la ruota con buona velocità, i vasi dovevano  essere lisciati a mano in un secondo tempo. Durante il Nuovo Regno, si aggiunse  un'altra persona con il compito di azionare la ruota mentre il vasaio lavorava  con entrambe le mani. Questa innovazione comportava prodotti meglio rifiniti.  Alla fine del Nuovo Regno, il vasaio girava la ruota da solo, ma questa volta  con i piedi, e i prodotti migliorarono ancora. @L@LQuando il contenitore aveva assunto la forma desiderata, veniva posto a  essiccare. I vasi erano decorati durante il periodo di asciugatura. Dopo  l'essiccazione, venivano cotti in un forno. Il forno era abbastanza grande, con  un focolare alla base. Il focolare era separato dalla parte superiore da una  grata d'argilla. I vasi erano posti su tale grata. La parte superiore era  sigillata, tranne un foro per lasciare uscire il fumo. Al termine della cottura,  il prodotto era finito e veniva riposto per usi futuri."
        }
    }
    message_history_bazaar {
        id: 199,
        
        size [30, 20]
        image {
            id: 116,
            pos [15, 15]
        }
        title {
            text: "Bazar",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "I bazar erano luoghi affollati e rumorosi. I negozianti, uomini o  donne, mettevano in mostra le loro merci e i clienti arrivavano con altre da  barattare. I bazar si trovavano generalmente lungo il Nilo, per sfruttare la  vicinanza dei moli dove attraccavano le barche con la nuova mercanzia. @L@LScene di bazar erano spesso dipinte sui muri delle tombe. La tomba della V  Dinastia di Khnumhotep e Niankhkhnum, addetti alla manicure del Faraone,  illustra una scena spettacolare, completa di scimmia ammaestrata che morde la  caviglia a un ladro di passaggio."
        }
    }
    message_history_nubt {
        id: 200,
        type: 3,
        size [40, 30]
        title {
            text: "Nubt",

        }
        subtitle {
            text: "È nato un villaggio",

        }
        content {
            text: "@PBenvenuto nell'antico Egitto, terra dei Faraoni! Qui potrai vivere  da protagonista la storia di una tra le più grandi civiltà di tutti i tempi, una  civiltà capace di rimanere in auge per 15 secoli e 24 generazioni. Dovrai  guidare una famiglia, di generazione in generazione, partendo dalle sue radici  nell'Egitto preistorico e passando per l'alba della sua civiltà... fino alla  fondazione di un grandissimo impero... e quindi spingerti oltre. @PLa tua storia inizia sulle rive del Nilo, nella regione di Nubt, dove una  piccola confederazione di clan cerca di sopravvivere in un ambiente ostile. La  tua famiglia è a capo dell'insediamento e tu ne sei la guida. @PLe prime cose che occorrono sono le case, perché gli abitanti possano trovare  un posto dove vivere, e poi una serie di sentieri, cosicché sia possibile  seguire dei cammini liberi e veloci."
        }
    }
    message_history_thinis_2 {
        id: 201,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",

        }
        subtitle {
            text: "L'alba della civiltà",

        }
        content {
            text: "@PDopo molti anni e con il passare delle generazioni, la tua famiglia  si è spostata nella regione di Thinis, nell'Alto Egitto. Qui, un manipolo di  signori locali sta cercando di estendere la sua influenza sul Basso Egitto e su  tutte le terre lungo il Nilo, per unificarle sotto una sola casata, con un solo  capo supremo. @PLa fondazione di Thinis, una città florida come non se ne sono mai viste,  aumenterà l'influenza della confederazione Thinita, così da avere un ruolo  fondamentale sul dominio del Basso Egitto, tale da suscitare invidia in tutte le  altre fazioni. Ciò significa offrire agli abitanti vari divertimenti, nonché  costruire magnifici templi dedicati al culto delle divinità locali. @PPer costruire una città così importante occorrono molti soldi. A Thinis puoi  trovare ricchi depositi d'oro, e l'estrazione di tale prezioso minerale deve  rappresentare la tua priorità assoluta."
        }
    }
    message_history_perwadjyt {
        id: 202,
        type: 3,
        size [40, 30]
        title {
            text: "Perwadjyt",

        }
        subtitle {
            text: "La discontinuità del Nilo",

        }
        content {
            text: "I nobili Thiniti sono ancora in lotta per unificare le terre del Nilo  sotto un unico regnante. Per sostenere la loro causa, tutti sperano che tu  riesca a stabilire una fiorente comunità a Perwadjyt, nell'umida regione del  Delta, nel Basso Egitto, estendendo così la loro influenza lungo tutto il corso  del sacro fiume. Per supportare una popolazione più grande di quella di un  villaggio, devi imparare a sfruttare l'agricoltura. @LI contadini egizi hanno appena iniziato a sfruttare il suolo reso fertile  dalle inondazioni del Nilo per crescere ogni tipo di messi. Ma il Nilo, a volte,  può essere rischioso. I pericoli che si annidano nelle sue acque e sulle sue  rive sono molti, come i pericolosissimi coccodrilli, gli ippopotami e le zanzare  portatrici di malaria."
        }
    }
    message_history_nekhen {
        id: 203,
        type: 3,
        size [40, 30]
        title {
            text: "Nekhen",

        }
        subtitle {
            text: "Il primo Faraone",

        }
        content {
            text: "La gente che vive sulle rive del Nilo sta imparando a sopravvivere in  un ambiente ostile e, nel frattempo, un regnante locale di nome Narmer è asceso  al potere. Narmer regna su gran parte del territorio, ma la piena unificazione  dei due regni non è ancora compiuta. Per commemorare la propria ascesa al  potere, Narmer desidera che tu, con la tua famiglia, ti trasferisca per  governare una nuova città a Nekhen. Questa città dovrà avere templi dedicati a  molte divinità e numerose aree d'intrattenimento."
        }
    }
    message_history_men_nefer {
        id: 204,
        type: 3,
        size [40, 30]
        title {
            text: "Men-nefer",

        }
        subtitle {
            text: "La fondazione della capitale",

        }
        content {
            text: "Dopo una lunga lotta, il re Hor-Aha è riuscito a unificare i regni  dell'Alto e del Basso Egitto, proclamandosi così Faraone di tutto l'Egitto! Come  segno del suo potere assoluto e della sua dinastia, Hor-Aha ha ordinato la  fondazione di una imponente città capitale a Men-nefer, dalla quale possa  governare la sua nuova nazione. Data la fedeltà dimostrata dalla tua famiglia  per numerose generazioni, il Faraone ti ha scelto come artefice della sua  splendida città. La capitale è il simbolo del Regno, quindi i suoi cittadini  devono godere di una qualità di vita superiore. A questo scopo, dovrai  commerciare con altre città del Regno e dovrai fornire una buona istruzione ad  almeno parte dei tuoi cittadini. Devi anche costruire una mastaba per i nobili  della città."
        }
    }
    message_history_timna {
        id: 205,
        type: 3,
        size [40, 30]
        title {
            text: "Timna",

        }
        subtitle {
            text: "Una spedizione verso il Sinai",

        }
        content {
            text: "Un nuovo Faraone, Den, è sul trono d'Egitto. Ora è molto preoccupato,  i nemici iniziano a minacciare i nostri confini e la nostra nazione non dispone  di rame a sufficienza per fabbricare le armi per le truppe. Il Faraone Den ha  ordinato una spedizione mineraria nelle impervie terre del Sinai, oltre i nostri  confini e nel cuore del territorio beduino. La zona conosciuta col nome di Timna  è ricca di oro e rame, nonché preziosi turchesi, ma, per il resto, è  assolutamente arida. Le condizioni saranno molto dure e tu dovrai esportare  dall'Egitto diversi merci, forse anche cibo e tela. Il Faraone richiede  frequenti spedizioni dal Sinai e ti chiederà denaro, rame, gemme e armi. Per  supportare la spedizione, puoi utilizzare le merci in surplus. Dovrai stare  sempre in guardia, dal momento che i Beduini del deserto sono avversari  formidabili e non permettono che degli stranieri invadano il loro territorio,  per non parlare del saccheggio delle loro risorse minerarie. @PPer alleggerire il fardello di tali condizioni di vita per i tuoi cittadini,  costruisci un padiglione presso un importante crocevia. I cittadini potranno  rilassarsi con i giocolieri e della buona musica e, se costruisci anche una  scuola di danza, questo nuovo tipo di spettacolo offrirà grande divertimento."
        }
    }
    message_history_behdet {
        id: 206,
        type: 3,
        size [40, 30]
        title {
            text: "Behdet",

        }
        subtitle {
            text: "La flotta del Faraone",

        }
        content {
            text: "Le truppe del Faraone non hanno rivali in tutto il mondo conosciuto,  ma il nuovo Faraone, Khasekhemwy della seconda dinastia, ora richiede una  potente flotta basata a Behdet. Per dominare i mari, occorre una flotta di navi  da guerra, ma il legno è scarso in quanto il nostro clima permette l'esistenza  di ben poche zone boscose. Il legno di cedro può essere importato da Byblos, nel  territorio libanese a nord est. Per fortuna, le esportazioni del nostro papiro  possono compensare l'alto costo di tale legname."
        }
    }
    message_history_abedju {
        id: 207,
        type: 3,
        size [40, 30]
        title {
            text: "Abjedu",

        }
        subtitle {
            text: "La sfida dei mari",

        }
        content {
            text: "Abjedu, il luogo dove sono sepolti i nostri padri, è diventato una  grande necropoli costellata di sacre tombe. Ora, molti nobili desiderano  eleggerlo come loro ultimo luogo di riposo. Per onorarli, il nuovo Faraone  Khasekhemwy della seconda dinastia ha ordinato la costruzione di tre sacre tombe  mastaba (una più grande delle altre due) per la nobiltà del luogo. @L@LIl Faraone ha anche richiesto la costruzione di una potente flotta di stanza  a Behdet. Anche Abjedu deve fornire una piccola flotta di navi da guerra,  cosicché le nostre spiagge restino assolutamente sicure. Ciò non sarà facile,  dal momento che il legno è scarso, in quanto il nostro clima permette  l'esistenza di poche aree boscose. Il legno di cedro può essere importato da  Byblos, nel territorio libanese a nord est. Per fortuna, le esportazioni del  nostro papiro possono compensare l'alto costo di tale legname."
        }
    }
    message_history_selima {
        id: 208,
        type: 3,
        size [40, 30]
        title {
            text: "Selima",

        }
        subtitle {
            text: "La via dell'Africa",

        }
        content {
            text: "@PÈ stato annunciato un nuovo Faraone, Nebka, fondatore della terza  dinastia di regnanti egizi. Nebka ha conferito all'Egitto un'ottima  organizzazione, ordinando la divisione del Regno in distretti, o 'nome',  ciascuno governato da un signore chiamato 'Nomarca'. Anche se il sistema può  apparire rigido, l'Egitto è cresciuto e continua a prosperare, con ottimi  risultati anche nei campi dell'architettura e dell'arte.  @L@PLe carovane di  mercanti, in viaggio di oasi in oasi nel cuore del territorio africano, hanno  fornito beni esotici, alcuni rari e preziosi, tenuti in gran conto dalla nostra  gente. Sfortunatamente, queste carovane sono continuamente attaccate dai  guerrieri libici e anche dai Beduini del deserto orientale. Per rendere sicure  le vie commerciali, il Faraone Nebka desidera che tu stabilisca una postazione  militare nell'Oasi di Selima, crocevia delle carovane, ben oltre i confini del  nostro Regno.   @L@PLì potrai trovare del legname adatto alla costruzione delle navi, da vendere  per ricavare i fondi necessari alla stazione militare. Per forgiare le armi,  puoi ottenere del rame dalle nuove miniere di Timna, nel territorio del Sinai. @L@PDall'Oasi di Selima, puoi importare ebano della nazione africana di Kerma.  Quando avrai stabilito l'avamposto militare, da qui potrai fornire l'ebano a  tutte le città del Regno."
        }
    }
    message_history_abu {
        id: 209,
        type: 3,
        size [40, 30]
        title {
            text: "Abu",

        }
        subtitle {
            text: "Il confine nubiano",

        }
        content {
            text: "@PÈ stato annunciato un nuovo Faraone, Nebka, fondatore della terza  dinastia di regnanti egizi. Nebka ha conferito all'Egitto un'ottima  organizzazione, ordinando la divisione del Regno in distretti, o 'nome',  ciascuno governato da un signore chiamato 'Nomarca'. Anche se il sistema può  apparire rigido, l'Egitto è cresciuto e continua a prosperare, con ottimi  risultati anche nei campi dell'architettura e dell'arte.   @PIl Faraone desidera estendere i confini del proprio Regno verso sud, in Nubia.  Egli ordina di fondare una città presso la prima cataratta del Nilo, sull'isola  di Abu, così da sfruttare i ricchi depositi di gemme, granito e arenaria che lì  si trovano.   @PLa necropoli di Abjedu richiede molti materiali di questo tipo, in quanto la  nobiltà desidera costruire tombe sempre più lussuose. Anche la capitale Men- nefer può aver bisogno di mattoni per costruire le tombe e il Faraone Nebka  sosterrà le richieste per questi e altri materiali da costruzione.   @PIl Faraone Nebka ha inoltre ordinato che uno dei tuoi pari stabilisca un  avamposto militare nell'Oasi di Selima, per difendere la via delle carovane che  si dirigono all'interno dell'Africa. Quando sarà operativo, potrai contattare  Selima per trovare il prezioso ebano, un altro materiale da costruzione molto  richiesto."
        }
    }
    message_history_saqqara {
        id: 210,
        type: 3,
        size [40, 30]
        title {
            text: "Saqqara",

        }
        subtitle {
            text: "La prima piramide",

        }
        content {
            text: "L'ascesa del Faraone Djoser al trono d'Egitto ci ha portato in una  nuova era di saggezza, istruzione e opere d'arte. Occorre stabilire il cimitero  reale a Saqqara, così che serva come eterno luogo di riposo per nobili quali  Hezyre e Khabausokar, i fidati consiglieri del Faraone.   @PTale luogo deve, però, contenere anche un monumento tanto imponente come mai  il mondo ne abbia visti prima. Io, Imhotep primo consigliere del Faraone, ho  ideato un nuovo tipo di tomba per il Faraone. Invece della bassa struttura in  mattoni tipica delle mastaba, la nuova tomba si ergerà verso il cielo, come se  fosse composta di molte mastaba, costruite una sopra l'altra. Inoltre, questa  'piramide a gradoni' sarà completamente in pietra, così che possa vincere il  trascorrere dei secoli. Al suo interno, un sarcofago di granito conterrà il  corpo del Faraone per tutto il suo eterno riposo. @PI sacerdoti della necropoli di Abjedu hanno perfezionato l'arte di utilizzare  la tela per imbalsamare i defunti, così tutti gli Egizi avranno accesso alla  vita oltre la vita.  @PIl nostro avamposto nell'oasi di Selima è tuttora fiorente, da lì potrai  importare l'ebano d'Africa.  @PIl Faraone ti ha concesso una generosa somma di denaro per iniziare il  progetto. Non lo deludere."
        }
    }
    message_history_serabit_khadim {
        id: 211,
        type: 3,
        size [40, 30]
        title {
            text: "Serabit Khadim",

        }
        subtitle {
            text: "I Beduini dell'est",

        }
        content {
            text: "Come Den prima di lui, il Faraone Huni ha ordinato una spedizione  nelle lande inospitali del Sinai per recuperare turchesi e rame. Egli desidera  dirigere tale spedizione, verso il luogo chiamato Serabit Khadim, dove si  trovano i resti di un precedente insediamento egizio. La loro attuale condizione  è sconosciuta, ma potrebbero fornire un minimo di protezione per la spedizione.   @PDevi sapere che la prima spedizione inviata laggiù non è mai tornata e anche  la seconda, inviata a recuperarla, non ci ha più fornito notizie. Comunque, se  vogliamo armare i nostri soldati in modo adeguato, il nostro Regno ha bisogno di  rame per fabbricare le armi e questo metallo purtroppo, è scarso. @PPreparati, sarai sotto costante minaccia di attacco da parte dei Beduini del  deserto e dei Canaaniti, nostri nemici. Estrai tutto il rame e le gemme che puoi  e assicurati di soddisfare le richieste del Faraone. Puoi ricorrere agli orafi  per sfruttare le gemme che avanzano e fabbricare gioielli per la gente del  luogo."
        }
    }
    message_history_meidum {
        id: 212,
        type: 3,
        size [40, 30]
        title {
            text: "Meidum",

        }
        subtitle {
            text: "La necropoli reale",

        }
        content {
            text: "Il Faraone Huni desidera trascorrere il suo eterno riposo in una  piramide a gradoni, come Djoser prima di lui. Egli inoltre desidera essere  circondato dalle tombe dei suoi nobili e ha scelto Meidum, nel Basso Egitto,  come sito adatto a ospitare la necropoli reale.   @PCome segno di ringraziamento per i numerosi anni in cui la tua famiglia ha  servito il Regno, Huni ti ha concesso l'ingresso a Meidum, in una tomba  personale. Ecco, dunque, l'onore concesso alla tua famiglia. @PPer assicurarsi che saggezza e istruzione si mantengano nei secoli, il Faraone  Huni invita a costruire biblioteche reali. Quando saranno riempite di pergamene  e papiri, forniranno un'ottima risorsa per l'istruzione delle classi sociali più  elevate. @PIl Faraone ha inviato un suo assistente in una spedizione verso Serabit  Khadim, nelle aspre terre del Sinai, per recuperare preziosi turchesi. Se la  spedizione avesse successo, potrai rivolgerti a tale città per importare le  gemme. Gli orafi usano le gemme per creare gioielli, un bene di lusso che sarà  molto apprezzato dai tuoi cittadini. @PLa città di Behdet, una volta fiorente, ha ora iniziato la sua fase di declino  e non esporta più tutti i beni per cui era così famosa."
        }
    }
    message_history_buhen {
        id: 213,
        type: 3,
        size [40, 30]
        title {
            text: "Buhen",

        }
        subtitle {
            text: "Espansione in Nubia",

        }
        content {
            text: "Il nostro nuovo Faraone, Snofru, intende fare in modo che la propria  dinastia, la quarta, sia ricordata come la più grande di ogni tempo. Il Faraone  desidera espandere ulteriormente i confini verso sud. Ha dunque deciso di  invadere la Nubia e di fondare una città fortificata a Buhen, oltre alla seconda  cataratta del Nilo. Qui dovrai inoltre erigere un grande obelisco di granito,  perché sia chiaro che il territorio ora appartiene all'Egitto e al suo Faraone.  A sud, non troverai granito; quindi, dovrai importarlo da Abu. @PA Buhenm, incontrerai i fieri ed esperti guerrieri nubiani, che combatteranno  fino alla morte per respingere l'invasore: ma non disperare, dopo anni di  faticoso addestramento presso l'Accademia militare, anche il nostro esercito è  più che esperto. In più, i nostri genieri hanno ideato alcune strutture di  difesa, come le torri, le mura e le guarnigioni fortificate. Tali strutture  saranno fondamentali per tenere a bada l'esercito nubiano. Potrebbero, inoltre,  occorrere delle navi da trasporto per facilitare lo spostamento dei soldati  lungo il fiume.  @PVerso nord, abbiamo instaurato una relazione diplomatica con gli Enkomi,  sull'isola di Cipro. Questa terra prende il nome dall'abbondanza di rame, che  ora potremo acquistare da loro. Comunque, abbiamo da poco stabilito una comunità  mineraria a Serabit Khadim, nelle terre del Sinai e, dunque, siamo in grado di  rifornire il Regno di rame a un prezzo molto più basso. Le forniture da Serabit  Khadim sono spesso irregolari, a causa delle continue incursioni di Beduini e  Canaaniti e non siamo certi che le forze egizie possano resistere ancora per  molto.  @PLa tomba del Faraone, un monumento unico, è in fase di costruzione a Dahshur.  Di quando in quando, il Faraone potrebbe chiederti di contribuire fornendo  pietra calcarea per completare il suo progetto."
        }
    }
    message_history_south_dahshur {
        id: 214,
        type: 3,
        size [40, 30]
        title {
            text: "A sud di Dahshur",

        }
        subtitle {
            text: "La piramide sghemba di Snofru",

        }
        content {
            text: "@PIl nostro nuovo Faraone, Snofru, intende fare in modo che la  propria dinastia, la quarta, sia ricordata come la più grande di tutti i tempi.  I suoi architetti hanno ideato una tomba ancora più spettacolare di quella di  Huni e il Faraone desidera che tu ne supervisioni la costruzione. Dovrai  stabilire un insediamento a sud di Dahshur, il luogo scelto per la sua piramide  sghemba. Una volta operativa, la città fornirà la forza lavoro necessaria al  completamento del suo ambizioso progetto. @PLa piramide sghemba deve essere costituita da una struttura interna in pietra,  successivamente rivestita con calcare bianco perché risplenda sotto il sole del  deserto. Troverai calcare a sufficienza a Dahshur, ma dovrai importare la  pietra. @PIl Faraone desidera che i confini si estendano ancora più a sud; quindi, ha  inviato il suo esercito a invadere la Nubia e fondare una città fortificata a  Buhen, oltre alla seconda cataratta del Nilo. @PVerso nord, l'Egitto ha intrapreso una relazione diplomatica con gli Enkomi,  sull'isola di Cipro. L'isola deve il suo nome all'abbondanza di rame che ora noi  importiamo in modo massiccio. @PPuoi ottenere delle pietre preziose dal recente avamposto di Serabit Khadim,  nel Sinai. Ultimamente, le forniture sono irregolari, a causa delle continue  incursioni di Beduini e Canaaniti; non siamo certi che le forze egizie possano  resistere ancora per molto."
        }
    }
    message_history_north_dahshur {
        id: 215,
        type: 3,
        size [40, 30]
        title {
            text: "A nord di Dahshur",

        }
        subtitle {
            text: "La vera piramide",

        }
        content {
            text: "@PIl Faraone Snofru ha portato l'ordine in Egitto e ora il Regno  fiorisce sotto il suo saggio e benevolo governo. Snofru desidera iniziare la  costruzione di un altro progetto a Dahshur, ancora più ambizioso della  precedente piramide sghemba. Gli architetti, i supervisori e gli ingegneri reali  credono di riuscire a costruire un edificio i cui lati siano inclinati a un  angolo continuo, culminante con una punta perfetta. Se riusciranno, questa sarà  la prima vera piramide, l'ideale dimora del Faraone Snofru per tutta l'eternità!    @PLa moglie del Faraone, la regina Hetehpheres, ha recentemente dato alla luce  un figlio che è stato chiamato 'Khufu'. La nostra gente non anticipa certo con  gioia il momento in cui sarà lui a regnare, infatti i veggenti di Horus, dio del  Faraone, hanno predetto che non mostrerà la stessa benevolenza del padre. Anche  se riuscirà in molte imprese, essi temono che l'Egitto cadrà sotto una  estenuante tirannia.  @PPuoi acquistare il legno da Byblos, dato che i carpentieri dovranno costruire  molte rampe così che i manovali possano raggiungere la cima della grande  piramide."
        }
    }
    message_history_iunet {
        id: 216,
        type: 3,
        size [40, 30]
        title {
            text: "Iunet",

        }
        subtitle {
            text: "La difesa dell'Egitto",

        }
        content {
            text: "@PIl Faraone Khufu è salito al trono e, così come avevano predetto i  veggenti di Horus e Ra, la nostra gente ha già iniziato a soffrire a causa della  sua oppressione.  @PKhufu ha ordinato che il governatore reale raggiunga immediatamente Iunet per  difendere il territorio dagli invasori kushiti. Iunet può supportare una piccola  industria di pesca, in grado di sfamare l'insediamento per un po' di tempo. Se i  Kushiti giungono dall'acqua, però, il fiume diventerà poco sicuro per le barche  da pesca e le spiagge dovrebbero essere meglio sfruttate per creare una flotta  di navi da guerra. Se il cibo scarseggia, è possibile allevare del bestiame per  produrre carne, anche se le mandrie richiedono molta paglia, difficile da  crescere in questa regione. Per ottenere la paglia, dovrai rivolgerti ad altre  città e commerciare anche per procurarti i mattoni per la tua mastaba. @PLa città di Byblos nel Libano, terra dei cedri, ha iniziato a commerciare con  il potente impero dell'est. Gli Assiri e gli Ur della Mesopotamia (la terra tra  i due fiumi) sono ricchi d'avorio che potrai ottenere commerciando con Byblos.  Con l'arrivo di merci rare ed esotiche come l'avorio, Iunet certo fiorirà in un  istante. @PNella capitale, gli Egizi si divertono con un nuovo gioco da tavolo che si  chiama senet. Di solito si gioca di fronte a un boccale di birra, in luoghi  pubblici chiamati taverne senet. Tali luoghi possono offrire alla gente di Iunet  un piacevole diversivo dall'autorità tirannica di Khufu. @PIl Faraone ha ordinato la predisposizione di innumerevoli cave a On, nella  regione del Delta, per produrre una grande quantità di calcare bianco. Solo gli  dei sanno come intenderà impiegarlo. Si dice che stia pensando a un progetto di  costruzione colossale sull'altopiano vicino a Rostja, così grandioso da  offuscare la fama che suo padre (il saggio e benevolo Snofru) si era meritato  per aver costruito ben due nobili piramidi."
        }
    }
    message_history_on {
        id: 217,
        type: 3,
        size [40, 30]
        title {
            text: "On",

        }
        subtitle {
            text: "L'avorio dell'est",

        }
        content {
            text: "@PIl Faraone Khufu è salito al trono e, come avevano predetto i saggi  di Horus e Ra, la nostra gente soffre a causa della sua oppressione. Si dice che  stia pensando a un progetto di costruzione colossale sull'altopiano vicino a  Rostja, così grandioso da offuscare la fama che suo padre (il saggio e benevolo  Snofru) si era meritato per aver costruito ben due nobili piramidi. @PIl Faraone Khufu ha ordinato la predisposizione di molte cave a Tura, nella  regione del Delta, dove si trovano ricchi depositi di calcare bianco. Devi,  inoltre, costruire tre mastaba per i nobili della regione, così che il Faraone  possa premiare la loro devozione. Gli insediamenti di cavatori si chiameranno  'On' e dovranno servire a produrre grandi quantità di calcare bianco per molti  anni... solo gli dei sanno cosa intenda farsene. @PLa città di Byblos nel Libano, terra dei cedri, ha iniziato a commerciare con  il potente impero dell'est. Gli Assiri e gli Ur della Mesopotamia, la terra tra  i due fiumi, sono ricchi d'avorio che potrai ottenere commerciando con Byblos.  Con l'arrivo di merci rare ed esotiche come l'avorio, Iunet certo fiorirà in un  istante. @PKhufu ha inoltre inviato un governatore reale a Iunet, per difendere le nostre  terre dagli invasori kushiti. I consiglieri reali commiserano il governatore cui  è capitato tale difficile e oneroso incarico.  @PNella capitale, gli Egizi si divertono con un nuovo gioco da tavolo che si  chiama senet. Di solito, si gioca di fronte a un boccale di birra, in luoghi  pubblici chiamati taverne senet. Tali luoghi possono offrire alla gente di On un  piacevole diversivo dall'autorità tirannica di Khufu."
        }
    }
    message_history_rostja {
        id: 218,
        type: 3,
        size [40, 30]
        title {
            text: "Rostja",

        }
        subtitle {
            text: "La grande piramide e la sfinge",

        }
        content {
            text: "Finalmente, il Faraone Khufu ha rivelato i propri piani e le proprie  sconfinate aspirazioni: essi peseranno per molto tempo sulle spalle della nostra  gente. Il Faraone benedice e maledice allo stesso tempo la tua famiglia, perché,  anche se ti sei guadagnato il livello di Nomarca, il primo compito che ti viene  affidato è quello di portare a termine il progetto di costruzione più ambizioso  di tutti i tempi.   @PIl luogo dell'eterno riposo del Faraone sarà un gigantesco complesso di  piramidi, lontano da ogni città, sull'altopiano vicino a Rostja. Il suo  sarcofago sarà di robusto granito e la sua chiatta funebre di prezioso legno del  Libano. Vicino al complesso di piramidi del Faraone, dovrai costruire una  piramide più piccola per suo figlio, il principe Khafra, la cui tirannia  rivaleggia con quella del padre, ma i cui successi ne sono ben lungi. Khafra  richiede, inoltre, che la sua immagine sia scolpita nella pietra di Rostja,  sulla sommità di un'enorme statua chiamata 'sfinge', con il corpo di leone e la  testa di un uomo. @PPer supportare questo enorme impegno edilizio, dovrai fondare un grande  insediamento a Rostja. Le altre condizioni sono a tua discrezione, in quanto il  tuo unico obiettivo è quello di completare questi tre grandi progetti e di  onorare la fiducia del Faraone.   @PTi verranno inviate alcune lastre di calcare bianco necessarie per le  rifiniture delle piramidi, ma dovrai acquistare tutto il resto con i fondi della  città. @PIl Faraone affida a te, stimato Nomarca reale, questi tre compiti sacri. Tu  dovrai dimostrare la tua incrollabile devozione al Faraone ed esaudire i suoi  desideri... a qualunque costo."
        }
    }
    message_history_bahariya_oasis {
        id: 219,
        type: 3,
        size [40, 30]
        title {
            text: "Oasi di Bahariya",

        }
        subtitle {
            text: "Il deserto occidentale",

        }
        content {
            text: "@PI regni di Khufu e Khafra sono finiti e, con loro, anche la quarta  dinastia di famiglie regnanti sull'Egitto. Khentkaues, una parente lontana della  casa reale, ha dato alla luce il nuovo Faraone chiamato 'Userkaf': la stirpe di  sangue reale, così, ha modo di proseguire. Con Userkaf comincia la quinta  dinastia, dando inizio a un'era che promette molti cambiamenti. @PUserkaf ha in qualche modo decentralizzato il governo del Regno e ha affidato  più potere alle autorità locali. Ora i Nomarchi come te sono liberi di gestire i  propri affari. Il Faraone non cercherà di imitare i propri predecessori con  monumentali progetti di costruzione; infatti, ha in mente per te un altro  compito. @PIl Faraone ha deciso che Ra, dio del sole e del Regno, è il re degli dei e  intende proclamare il suo dominio in tutto il territorio. La terra d'Egitto è  già costellata di molti Templi del Sole, ma il Faraone desidera estendere la sua  influenza fino ai confini del Regno. @PEcco perché dovrai costruire un insediamento fortificato nell'Oasi di  Bahariya, nel cuore del deserto occidentale. Usa saggiamente la poca acqua che  troverai, in quanto, essendo così lontana dal Nilo, di solito è ambita da ogni  sorta di bestie feroci. Inoltre, dovrai fare attenzione agli attacchi dei  guerrieri libici e dei Beduini del deserto, che ultimamente intaccano la  ricchezza delle nostre carovane. Pianifica le tue difese con attenzione e  sfrutta tutte le risorse, come il legno o la selvaggina, che troverai  nell'oasi."
        }
    }
    message_history_djedu {
        id: 220,
        type: 3,
        size [40, 30]
        title {
            text: "Djedu",

        }
        subtitle {
            text: "Il Tempio del Sole",

        }
        content {
            text: "@PI regni di Khufu e Khafra sono finiti e, con loro, anche la quarta  dinastia di famiglie regnanti sull'Egitto. Khentkaues, una parente lontana della  casa reale, ha dato alla luce il nuovo Faraone chiamato 'Userkaf': la stirpe di  sangue reale, così, ha modo di proseguire. Con Userkaf comincia la quinta  dinastia, dando inizio a un'era che promette molti cambiamenti. @PUserkaf ha, in qualche modo, decentralizzato il governo del Regno e ha  affidato più potere alle autorità locali. Ora i Nomarchi come te sono liberi di  gestire i propri affari. Il Faraone non cercherà di imitare i propri  predecessori con progetti monumentali di costruzione; infatti, ha in mente per  te un altro compito. @PIl Faraone ha deciso che Ra, dio del sole e del Regno, è il re degli dei e  intende proclamare il suo dominio in tutto il territorio. La terra d'Egitto è  già costellata di molti Templi del Sole, ma il Faraone desidera che il più  grande si trovi a Djedu, nell'umida regione del Delta del Basso Egitto. @PCome gli altri territori del Delta, Djedu è ricca di selvaggina, pesce, altri  animali selvatici e vegetazione, ma non offre alcuna risorsa mineraria. Ecco  perché l'arenaria necessaria alla costruzione del tempio dovrà essere importata  dalle cave di On. Qui è possibile allevare il bestiame per produrre carne, ma le  mandrie necessitano di molta paglia. @PPer preparare un terreno adatto alla costruzione del Tempio del Sole, dovrai  ripulirlo. Per prima cosa, assicurati di vendere una buona quantità del prezioso  legno che potrai tagliare, in quanto una volta ammassato non sarai più in grado  di procurartene altro. Behdet e Abjedu hanno sempre bisogno di legno e  selvaggina; quindi, entra in commercio con loro per compensare le spese  necessarie alla costruzione del tempio."
        }
    }
    message_history_dunqul {
        id: 221,
        type: 3,
        size [40, 30]
        title {
            text: "Dunqul",

        }
        subtitle {
            text: "La minaccia kushita",

        }
        content {
            text: "@PPepy è salito al trono e ha conferito alla tua famiglia lo stato di  Cancelliere. L'autorità centralizzata continua ad affievolirsi, man mano che i  capi locali diventano più potenti. I raccolti in alcune regioni sono molto al di  sotto della normalità e lo spettro della carestia inizia a mietere le prime  vittime. Men-nefer, un tempo una splendida città, ha iniziato il proprio  declino. I veggenti prevedono l'approssimarsi di tempi difficili. @PI nostri vicini più potenti si fanno sempre più baldanzosi man mano che cresce  la debolezza dell'Egitto. L'avamposto di Buhen è sotto assedio da parte dei  feroci guerrieri kushiti giunti da Kerma, la più grande città non egizia di  tutta l'Africa. I Kushiti esigono tributi e la più piccola provocazione può  portare a un attacco in piena regola. Anche la Nubia ha dichiarato guerra e  vuole rientrare in possesso dei propri territori. @PPerché l'Egitto sopravviva, devi fare il possibile per preservare le vie  commerciali e mantenere i rifornimenti attivi. Mantieni in funzione la stazione  commerciale dell'Oasi di Selima. Pepy, anticipando il suo viaggio nell'aldilà,  ti farà frequenti richieste di pietra per costruire la sua piramide e anche  altre città, carenti di cibo, cercheranno la tua assistenza. @PUsa le tue risorse con cautela. Nell'oasi puoi trovare molto legno prezioso,  ma parte della foresta dovrà essere distrutta per accedere alla magra provvista  d'acqua."
        }
    }
    message_history_dakhla {
        id: 222,
        type: 3,
        size [40, 30]
        title {
            text: "Dakhla",

        }
        subtitle {
            text: "Il sentiero delle carovane",

        }
        content {
            text: "@PPepy è salito al trono e ha conferito alla tua famiglia lo stato di  Cancelliere. Il suo Regno quasi centenario è il più lungo mai registrato nella  storia umana, ma è costato molto caro. L'autorità centralizzata continua ad  affievolirsi, man mano che i capi locali diventano più potenti. I raccolti in  alcune regioni sono molto al di sotto della normalità e lo spettro della  carestia inizia a mietere le prime vittime. Men-nefer, un tempo una splendida  città, ha iniziato il proprio declino. I veggenti prevedono l'approssimarsi di  tempi difficili. @PI nostri vicini più potenti si fanno sempre più baldanzosi man mano che cresce  la debolezza dell'Egitto. L'avamposto di Buhen è sotto assedio da parte dei  feroci guerrieri kushiti giunti da Kerma, la più grande città non egizia di  tutta l'Africa. I Kushiti esigono tributi e la più piccola provocazione può  portare a un attacco in piena regola. Anche la Nubia ha dichiarato guerra e  vuole rientrare in possesso dei propri territori.  @PCerca di aumentare la stabilità del Regno fondando un centro amministrativo  nell'Oasi di Dakhla. L'oasi possiede molti alberi, che però bloccano l'accesso  alla limitata riserva d'acqua. Da questa importante località, puoi importare  l'ebano dell'Africa centrale. Pepy, anticipando il suo viaggio nell'aldilà, ti  chiederà spesso dei mattoni per costruire il suo monumento. Altre città, carenti  di cibo, cercheranno il tuo aiuto."
        }
    }
    message_history_thinis {
        id: 223,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",

        }
        subtitle {
            text: "La guerra civile",

        }
        content {
            text: "L'antico splendore di vita è stato dimenticato per sempre e tutti  temono che l'Egitto non ritroverà più la gloria del passato. Osiride ha voltato  le spalle alla sua gente e una serie di scarse inondazioni l'hanno ridotta alla  fame. Il potere dei Faraoni, un tempo indiscusso, è ormai svanito, sostituito da  quello di signorotti locali attaccabrighe. @PIn mezzo a questo caos, due nobili famiglie cercano di prendere il controllo  dell'Egitto. I signori di Henen-nesw reclamano il trono come legittimi eredi.  Essi sono molto crudeli e fanno ben poco per lenire il dolore del popolo. A sud,  una nuova famiglia, la casa Inyotef, è salita al potere nella zona di Waset.  Questa famiglia ha fatto il possibile per riunificare tutto il sud e ora Henen- nesw combatte contro il Waset in una mortale guerra civile per controllare tutto  il paese. @PPer mostrare la loro benevolenza verso gli Egizi, gli Inyotef ti hanno  affidato il compito di ricostruire la città conquistata di Thinis, una delle più  antiche d'Egitto. Due tra i più famosi e splendidi edifici di Thinis sono  sopravvissuti alla distruzione: il Complesso dei templi di Osiride e la magione.  Gli Inyotef hanno deciso che, se questi edifici dovessero andare distrutti, non  fornirebbero alcun finanziamento per la loro ricostruzione. I dominatori di  Waset considerano la ricostruzione di Thinis un progetto di primaria importanza  e quindi hanno già stanziato un buon finanziamento - anche in questi tempi  turbolenti. Riporta Thinis al suo antico splendore, crea una flotta e un  esercito per difenderla dai frequenti attacchi degli Henen-nesw, comprese le  città di Sauty, Nekhen e Khmun. Fai attenzione agli Henen-nesw: potrebbero  chiederti dei tributi per mettere alla prova la tua fedeltà - e i tuoi deben.  Inoltre, fai attenzione ai Nubiani, sempre in agguato e decisi a sfruttare  questo periodo di debolezza."
        }
    }
    message_history_waset {
        id: 224,
        type: 3,
        size [40, 30]
        title {
            text: "Waset",

        }
        subtitle {
            text: "La guerra civile",

        }
        content {
            text: "L'antico splendore di vita è stato dimenticato per sempre e tutti  temono che l'Egitto non ritroverà più la gloria del passato. Osiride ha voltato  le spalle alla sua gente e una serie di scarse inondazioni l'hanno ridotta alla  fame. Il potere dei Faraoni, un tempo indiscusso, è ormai svanito, sostituito da  quello di signorotti locali attaccabrighe. @PIn mezzo a questo caos, due nobili famiglie cercano di prendere il controllo  dell'Egitto. I signori di Henen-nesw reclamano il trono come legittimi eredi.  Essi sono molto crudeli e fanno ben poco per lenire il dolore del popolo. A sud,  una nuova famiglia, la casa Inyotef, è salita al potere nella zona di Waset.  Questa famiglia ha fatto il possibile per riunificate tutto il sud e ora Henen- nesw combatte contro il Waset in una mortale guerra civile per controllare tutto  il paese. @PGli Inyotef, occupati a combattere gli Henen-nesw, ti hanno affidato il  compito di costruire la loro città di Waset. Se gli Inyotef vogliono vincere la  lotta contro i dominatori Henen-nesw e consolidare la loro reputazione in  Egitto, Waset dovrà essere la pietra portante (alla quale altre città possano  affidarsi), in grado di fornire soccorsi o soldati a chi li dovesse richiedere.  Waset, che diventerà la capitale del Regno se gli Inyotef vinceranno la guerra,  dovrà quindi essere una grande città. Sfruttando le poche risorse a tua  disposizione, devi costruire un Tempio del Sole e una piramide così da mostrare  a tutti gli Egizi la gloria degli Inyotef. @PWaset non sarà immune agli attacchi. I dominatori Henen-nesw e i loro seguaci,  potrebbero minacciarla più volte e gli Henen-nesw stessi potrebbero estorcere  denaro dai tuoi forzieri. Per proteggere la città da questi possibili rischi,  devi creare una flotta e un esercito potenti, a disposizione anche di altre  città alleate."
        }
    }
    message_history_kebet {
        id: 225,
        type: 3,
        size [40, 30]
        title {
            text: "Kebet",

        }
        subtitle {
            text: "La riunificazione",

        }
        content {
            text: "I successi ottenuti dalla tua famiglia durante la guerra civile non  sono rimasti senza compenso. Io, Faraone Mentuhotep, ho concesso alla tua  famiglia il rango di Consigliere. Non esiste nessun altro in tutto l'Egitto di  cui mi possa fidare. Ora che i due regni dell'Alto e del Basso Egitto sono di  nuovo uniti e la capitale Waset è florida, ho bisogno di te per consolidare la  mia posizione in tutto il Regno. @PAnche se unito, l'Egitto è incline alle lotte intestine, specialmente nelle  zone un tempo fedeli agli Henen-nesw. Per consolidare l'unificazione, voglio che  tu ricostruisca e difenda Kebet. Kebet dovrà essere una città splendida così che  dimostri a tutti gli Egizi che nulla è impossibile con il mio Regno. La città è  spesso attaccata da altre della fazione avversaria, in particolare Khmun e,  quindi, devi assolutamente difenderla. @PLa carestia è ancora in agguato e spesso altre città del Regno ti chiederanno  del cibo. Soddisfa le richieste il più in fretta possibile, così l'Egitto  ammirerà la mia benevolenza e l'impegno del mio più fidato consigliere. @PSo che ti chiedo molto, ma nessun altro sarebbe in grado di portare a termine  tale compito."
        }
    }
    message_history_menat_khufu {
        id: 226,
        type: 3,
        size [40, 30]
        title {
            text: "Menat Khufu",

        }
        subtitle {
            text: "La riunificazione",

        }
        content {
            text: "I successi ottenuti dalla tua famiglia durante la guerra civile non  sono rimasti senza compenso. Io, Faraone Mentuhotep, ho concesso alla tua  famiglia il rango di Consigliere. Non esiste nessun altro in tutto l'Egitto di  cui mi possa fidare. Ora che i due regni dell'Alto e del Basso Egitto sono di  nuovo uniti e la capitale Waset è florida, ho bisogno di te per consolidare la  mia posizione in tutto il Regno. @PAnche se unito, l'Egitto è incline alle lotte intestine, specialmente nelle  zone un tempo fedeli agli Henen-nesw. Per consolidare l'unificazione, voglio che  tu ricostruisca e difenda Menat Khufu, che è stata quasi completamente distrutta  durante la guerra civile. Menat Khufu dovrà essere una città così splendida da  dimostrare a tutti gli Egizi che nulla è impossibile con il mio Regno. @PLa carestia è ancora in agguato e spesso altre città del Regno ti chiederanno  del cibo. Soddisfa le richieste il più in fretta possibile, così l'Egitto  ammirerà la mia benevolenza e l'impegno del mio più fidato consigliere. @PHo anche un'altra richiesta: voglio che tu costruisca una piramide di mattoni  ricoperta di lastre di calcare: sarà la mia ultima dimora per tutta l'eternità.  Ti chiedo, infine, di erigere alcuni obelischi di granito per ricordare a tutti  le mie opere di bene. @PSo che ti chiedo molto, ma nessun altro sarebbe in grado di portare a termine  tale compito."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itjtawy", pos [50, 80] }
        subtitle { text: "Una nuova capitale", pos [10, 30] }
        content {
            text: "O potente Faraone, favorito di Ra, la buona fortuna ti rallegri! La  tua ascesa al trono è il coronamento del sogno di tutti gli Egizi! Non esiste  ricompensa più grande, da parte di uomini e dei. Con l'ascesa della tua  famiglia, l'Egitto potrà nuovamente rinascere e forse così dimenticheremo gli  orrori della guerra civile. @PPer commemorare questo nuovo inizio, devi costruire una nuova splendida  capitale. Itjtawy, con le sue abbondanti risorse naturali, è il luogo ideale.  Sfruttando ciò che la terra ha da offrire, puoi costruire una splendida città,  degna del tuo valore e incrollabile dedizione. @PPer assicurarti che le opere della tua dinastia siano ricordate per sempre,  devi costruire due colossali piramidi di mattoni, per te e per la tua famiglia,  oltre a una sfinge che vigili sulla tua tomba. Una famiglia con alle spalle una  lunga tradizione di successi non merita di meno. @PRicorda, però, che alcune zone del paese mettono in dubbio la legittimità  della tua ascesa. Molti soffrono ancora gli effetti della carestia e lamentano  l'usurpazione del trono. Se riuscirai a risollevare questa gente dalla miseria e  la aiuterai a ricostruire le proprie case, te ne guadagnerai certamente la  fedeltà. Dovrai provvedere a loro come ai tuoi nuovi sudditi, per evitare che i  più disperati impugnino le armi e si uniscano in rivolta."
        }
    }
    message_history_iken {
        id: 228,
        type: 3,
        size [40, 30]
        title {
            text: "Iken",

        }
        subtitle {
            text: "Verso la Nubia",

        }
        content {
            text: "Ora che l'Egitto è saldamente unito sotto il tuo dominio, i tuoi  cortigiani e io per primo, il tuo consigliere, ti raccomandiamo di estendere i  confini meridionali ancora più a sud, verso la Nubia. Il letto del fiume secco  ad Allaqi è ricco d'oro e una possente città a Iken, che puoi eleggere come tua  residenza, scoraggerà eventuali attacchi da parte dei Nubiani. Ma devi fare  attenzione ai Kushiti. Sono avversari molto più pericolosi dei Nubiani e  useranno le loro spade per costringerti, o mio Faraone, ad abbandonare il loro  Regno. @PPer contrassegnare il nuovo territorio nubiano, devi costruire un grande  obelisco che attesti le grandi imprese del popolo egizio. L'obelisco mostrerà ai  Nubiani i vantaggi del dominio egizio e fungerà da costante ricordo della nostra  presenza. @PLa tua attenzione non deve focalizzarsi solo su Iken: non devi dimenticare i  piani relativi alla fondazione di una città portuale sul Mar Rosso, a Sawu. Sawu  avrà bisogno dell'aiuto del Faraone e non esiterà a chiedertelo. Se Sawu  riuscirà a fiorire, fornirà a Iken il rame necessario a forgiare le armi."
        }
    }
    message_history_sawu {
        id: 229,
        type: 3,
        size [40, 30]
        title {
            text: "Sawu",

        }
        subtitle {
            text: "Sulle spiagge del Mar Rosso",

        }
        content {
            text: "Ora che l'Egitto è fermamente unito sotto il tuo dominio, dobbiamo  sviluppare una serie di relazioni commerciali con tutte le città del mondo, così  da accrescere la nostra ricchezza, o Re delle Due Terre.  @PLa tua gente prospera e richiede beni di lusso. Stanchi dei soliti gioielli,  un bene di lusso sempre disponibile, i tuoi cittadini desiderano qualcosa di più  raro e costoso, come l'incenso. La tua corte e io per primo, il tuo consigliere,  ti raccomandiamo di fondare un porto sul Mar Rosso presso Sawu. Sawu offre una  via commerciale verso la lontana Pwenet, da cui è possibile importare il miglior  incenso del mondo, anche se con spese ingenti.   @POltre ad alcuni filoni d'oro e di rame, Sawu produce anche altre materie  prime, ma può prosperare solo come produttore di beni finiti. Importando la  materia prima ed esportando prodotti finiti, Sawu riuscirà a ricavare buoni  profitti. @PMentre tu sei occupato con Sawu, uno dei nostri più abili Nomarchi sta  preparando un nuovo centro commerciale in Nubia. La sua città, Iken,  probabilmente verrà attaccata, quindi, mio amato Faraone, preparati a inviare  tutte le risorse di cui avrà bisogno. @PSotto il tuo governo, Sawu diventerà una delle città più belle del Regno,  adatta a essere luogo prescelto per il tuo riposo eterno e per quello della tua  famiglia. Mentre ti occupi della costruzione del porto, non dimenticarti dei  preparativi per l'aldilà. Un mausoleo e una piccola piramide di mattoni saranno  un'ottima abitazione per anticipare il passaggio verso i Campi di Canne."
        }
    }
    message_history_heh {
        id: 230,
        type: 3,
        size [40, 30]
        title {
            text: "Heh",

        }
        subtitle {
            text: "La sfida",

        }
        content {
            text: "Venerabile Faraone, tutto ciò che hai creato è ora sotto minaccia! La  flotta nubiana è sul Nilo e colpisce il cuore del nostro paese saccheggiando e  distruggendo i nostri villaggi e città. I Nubiani attaccano anche le nostre navi  commerciali e rubano le merci. Per aiutare le città del nord a respingere gli  attacchi, devi preparare soldati e navi da guerra da inviare a chi ne farà  richiesta.   @PPer impedire che i Nubiani solchino nuovamente le nostre acque, il tuo  supervisore militare raccomanda di costruire una serie di forti a Heh, tra la  seconda e la terza cataratta del Nilo. I forti fungeranno da sbarramento e  respingeranno ogni avanzata nubiana. @PLa definitiva sconfitta dei Nubiani dipende dalla cattura della città di Baki.  Baki è ricca di risorse e la sua conquista danneggerà l'economia nubiana. Quando  avrai preso il controllo di Baki, potrai importare l'arenaria necessaria alla  costruzione del tuo mausoleo. Il tuo mausoleo a Heh contribuirà a rammentare ai  Nubiani il tuo dominio su di loro. @PLe sfide da accettare e vincere per difendere gli Egizi sono molte. Fai  attenzione, o Horus vivente, alla tempesta che si innalza ad est. Il frastuono  dei cavalli al galoppo si ode in tutta Canaan e i veloci carri da guerra  seminano morte e distruzione lungo la loro folle corsa. Questi carri  formidabili, mai visti prima, sono guidati dai guerrieri Hyksos. Le nuvole della  tempesta sono già state avvistate all'orizzonte e tu devi prepararti ad  affrontare il pericolo imminente."
        }
    }
    message_history_bubastis {
        id: 231,
        type: 3,
        size [40, 30]
        title {
            text: "Bubastis",

        }
        subtitle {
            text: "La città di Bast",

        }
        content {
            text: "Grande Faraone, dopo aver consolidato le vie commerciali, dobbiamo  mostrare all'Egitto i vantaggi del successo e della ricchezza. Bubastis è un  luogo perfetto per una città del genere: possiamo proteggere le nostre preziose  vie commerciali orientali e rendere omaggio a Bast, che ha sempre protetto  l'Egitto. @PLa città di Bast dovrà essere la gemma dell'Egitto. Dovrà essere bella come un  fiore di loto, ricca di spettacoli, scuole, biblioteche e luoghi di culto. Ai  suoi cittadini non dovrà mancare alcun genere di beni, compreso l'incenso  importato. Quando sarà completa, Bubastis sarà il gioiello sulla corona dei  regni gemelli. @PMentre costruisci questa città gloriosa, fai attenzione al tuono dei cavalli  provenienti dall'est. Il frastuono dei cavalli al galoppo si ode in tutta Canaan  e i veloci carri da guerra seminano morte e distruzione lungo la loro folle  corsa. Questi carri formidabili, mai visti prima, sono guidati dai guerrieri  Hyksos. Le nuvole della tempesta sono già state avvistate all'orizzonte e tu  devi prepararti ad affrontare il pericolo imminente."
        }
    }
    message_history_khmun {
        id: 232,
        type: 3,
        size [40, 30]
        title {
            text: "Khmun",

        }
        subtitle {
            text: "L'Egitto riconquistato",

        }
        content {
            text: "Potente Faraone, l'Egitto urla la sua richiesta d'aiuto. I minacciosi  Hyksos hanno invaso la nostra terra e stabilito la loro capitale a Rowarty. Da  qui, hanno interrotto molte delle nostre vie commerciali, impedendo l'afflusso  dei rifornimenti. Dobbiamo fermarli prima che sia troppo tardi. @PSe ti aggrada, grande Faraone, possiamo riprendere la città di Khmun, che è  stata violata dagli invasori. Dobbiamo anche radunare un grande esercito e una  grande flotta, dato che dovremo inviare truppe e provviste verso i nostri  compatrioti del nord, specialmente verso Rowarty, per aiutarla a respingere le  incursioni degli Hyksos. Molti si rivolgeranno a te, figlio di Ra, per chiedere  aiuto. E ora anche noi abbiamo una nuova arma. I nostri saggi capi militari  hanno imparato a utilizzare il carro da guerra e ora siamo pronti per assalire  il nemico e scacciarlo. Dopo aver allontanato i pericolosi Hyksos, il nostro  supervisore militare raccomanda la costruzione di un forte nel Sinai a Sharuhen,  per impedire un'ulteriore invasione dall'est. @PMa il pericolo non è individuabile solo nel nord! Alcuni rapporti dal confine  meridionale ci informano che i Nubiani sfruttano di nuovo un nostro momento di  debolezza. Hanno riconquistato le città di Iken e Heh. Anche se la situazione a  sud è preoccupante, dobbiamo prima scacciare gli Hyksos. @PGli Hyksos sono invasori sacrileghi. Abbiamo appena scoperto che hanno violato  la piramide di Khmun. Hanno rubato tutti gli arredi sacri necessari al Faraone  lì sepolto. Dobbiamo inviare altri arredi funebri così che al Faraone non manchi  più nulla nell'aldilà."
        }
    }
    message_history_sauty {
        id: 233,
        type: 3,
        size [40, 30]
        title {
            text: "Sauty",

        }
        subtitle {
            text: "L'Egitto riconquistato",

        }
        content {
            text: "O Re delle Due Terre, l'Egitto urla la sua richiesta d'aiuto. I  pericolosi Hyksos hanno invaso la nostra terra e hanno stabilito la loro  capitale a Rowarty. Da Rowarty, hanno interrotto molte delle nostre vie  commerciali impedendo l'afflusso dei rifornimenti. Dobbiamo fermarli prima che  sia troppo tardi. @PQui a Sauty, siamo al sicuro da attacchi immediati, anche se gli Hyksos osano  chiederci tributi. Sarà necessario disporre di truppe e armi da inviare ai  nostri compatrioti del nord per aiutarli a respingere le incursioni degli  Hyksos. Molti si rivolgeranno a te, figlio di Ra, per chiedere aiuto. E ora  anche noi abbiamo una nuova arma. I nostri saggi capi militari hanno imparato a  utilizzare il carro da guerra e ora possiamo assalire il nemico e scacciarlo. @PMa il pericolo non è individuabile solo nel nord! Alcuni rapporti dal confine  meridionale ci informano che i Nubiani sfruttano di nuovo un nostro momento di  debolezza. Hanno riconquistato le città di Iken e Heh. @PAffinché l'Egitto sopravviva in questo periodo turbolento, i nostri generali e  ammiragli dovranno dare il massimo. Per ispirare i due migliori di loro, hai  promesso di costruire due piramidi possenti quanto la tua. Con la tua promessa  nel cuore, ora combattono il nemico con grande coraggio e con tutte le proprie  forze.   @PSe ti aggrada, potente Faraone, puoi costruire tre magnifiche piramidi a  Sauty, una per te e le altre due per i tuoi generali. Le tre piramidi  occuperanno molto spazio; quindi, dovrai fare a meno di qualche risorsa per  erigerle. Inoltre, dovrai estendere i confini della città oltre il Nilo per  recuperare i beni necessari a una città sempre più prospera."
        }
    }
    message_history_byblos {
        id: 234,
        type: 3,
        size [40, 30]
        title {
            text: "Byblos",

        }
        subtitle {
            text: "Espansione e conquista",

        }
        content {
            text: "L'Egitto è risorto dal precedente periodo buio con un nuovo vigore.  Byblos, con le sue verdi foreste e ricche miniere di rame, è finalmente nostra!  Con la tua presenza, la città prospererà sicuramente e riusciremo a fondare un  Nuovo Regno. @PAh, ma quale allarmante scoperta abbiamo effettuato dopo la conquista di  Byblos! Un nuovo e feroce popolo, gli Ittiti, ha invaso gran parte dell'Asia e  alcuni dicono che il loro impero sia potente quanto il nostro. Ora hanno rivolto  l'attenzione verso Byblos, desiderosi delle sue ricchezze. Se non ci prepareremo  al loro attacco, potremmo perdere tale splendida città.  @PDurante la preparazione alla guerra, dobbiamo anche palesare il potere egizio  su Byblos. Con la tua benedizione, o Faraone, erigeremo tre obelischi, uno più  grande degli altri due, che proclamino il tuo dominio e la tua gloria fino ai  confini dell'impero. Questi spettacolari monumenti ricorderanno ai cittadini chi  è il loro signore. @PMentre ci occuperemo di Byblos, altre regioni egizie saranno esposte a  ulteriori attacchi. I Nubiani si sono spostati a nord, fino alla prima cataratta  e noi dobbiamo aiutare i nostri compatrioti a scacciarli. Alcuni rapporti da  Rowarty citano un nuovo misterioso nemico, il Popolo del Mare: devono essere  abbattuti. Per mostrare la tua potenza, prepara truppe e navi da guerra da  inviare in caso di necessità."
        }
    }
    message_history_baki {
        id: 235,
        type: 3,
        size [40, 30]
        title {
            text: "Baki",

        }
        subtitle {
            text: "La gloria d'Egitto",

        }
        content {
            text: "Con la cacciata degli Hyksos, la nostra terra assiste a una nuova  rinascita, un Nuovo Regno che offusca i passati splendori. Nobile Faraone, Baki  è un luogo ideale per dare inizio al Nuovo Regno. Da lì potremo usare i ricchi  depositi d'oro per dare corpo alla tua nuova visione dell'Egitto.  @PL'Egitto è al suo massimo splendore, ma restano alcuni noiosi problemi da  risolvere. Molte città del Regno stanno ancora cercando di risollevarsi dopo gli  attacchi degli Hyksos e potrebbero aver bisogno del tuo aiuto. In altre regioni,  i vecchi nemici dell'Egitto continuano ad attaccarci e un nuovo nemico, il  Popolo del Mare, ha iniziato le sue scorrerie sulla costa settentrionale. Devi  prepararti a difendere le città egizie dai nostri nemici, vecchi e nuovi. @PMan mano che l'Egitto cresce in potenza, molte città desiderano commerciare  con noi. Alcune di queste conoscono i nostri usi, fino a considerarsi egizie e  temono il nostro potere, mentre altre ci sono sconosciute e commerciano con noi  per la prima volta. Per la gloria d'Egitto, sfrutta tali relazioni per fornire  al nostro popolo tutto ciò di cui ha bisogno. @PPer varcare la soglia di una nuova era, i tuoi architetti reali desiderano  costruire per te due nuovi piramidi e un mausoleo, o Faraone. Tali monumenti  riflettono certamente la grandiosità e la prosperità che hai conferito  all'Egitto."
        }
    }
    message_history_rowarty {
        id: 236,
        type: 3,
        size [40, 30]
        title {
            text: "Rowarty",

        }
        subtitle {
            text: "Il Popolo del Mare",

        }
        content {
            text: "O Horus dorato, il nostro dominio asiatico è forte e incontrastato e  i nostri confini si estendono nuovamente fino in Nubia. Ma i pericoli sulla  costa settentrionale continuano a crescere. Il Popolo del Mare è sempre più  aggressivo e continua a razziare le nostre città. Solo la presenza del Faraone  potrà sconfiggere questi feroci avversari. Se ordini una flotta, supportata da  un forte esercito, riusciremo certamente a sconfiggere il Popolo del Mare. @PMentre ti occupi del Popolo del Mare, i tuoi coraggiosi Nomarchi portano  attacchi in tutto il mondo. Se avranno successo, l'Egitto dominerà il mondo dal  grande fiume Eufrate fino alla città kushita di Kerma, a sud. Quando tu e i tuoi  Nomarchi otterrete la vittoria, la tua dinastia sarà ricordata come la più  grande di tutti i tempi. @PLa tua fama sconfinata ci ha fatto guadagnare un nuovo centro commerciale,  Micene. Il re di questa città ha appreso dello splendore dell'Egitto e desidera  commerciare con noi. Se vuoi aprire questa nuova via commerciale, o Faraone, i  tuoi cittadini potranno ottenere i beni più lussuosi ed esotici che abbiano mai  visto. @PPer ospitare la tua famiglia nell'aldilà, occorre costruire due possenti  mausolei e una gigantesca piramide di mattoni. Questi monumenti ricorderanno a  tutti la tua potenza e le opere non solo sul campo di battaglia."
        }
    }
    message_history_hetepsensusret {
        id: 237,
        type: 3,
        size [40, 30]
        title {
            text: "Hetepsensusret",

        }
        subtitle {
            text: "La Gloria del Faraone",

        }
        content {
            text: "Benevolo Faraone, tu hai portato la pace e la prosperità in tutta la  nazione. Sotto il tuo saggio governo, l'Egitto è di nuovo un paese forte e  glorioso. Tutti i Nomarchi ti sono fedeli e il nostro paese non soffre più di  alcuna minaccia. @POra che hai compiuto ciò che la tua famiglia desiderava da generazioni, è il  tempo di commemorare le grandi opere della tua nobile dinastia. L'unico modo per  farlo è quello di costruire la più imponente piramide di tutto l'Egitto, più  grande persino di quella di Khufu, a Rostja. Altri della tua famiglia si sono  sacrificati, lungo il cammino verso la gloria. Anche loro devono essere  ricordati e onorati, con un mausoleo di arenaria per ringraziarli del loro  incrollabile supporto. @LIl luogo ideale per tali monumenti è Hetepsensusret, nella ricca regione di  Fayuum. Da qui, mentre costruisci la grande piramide, puoi gestire tutti gli  affari di stato e rispondere alle eventuali richieste effettuate dalle città del  Regno."
        }
    }
    message_history_perwadjyt_3 {
        id: 238,
        type: 3,
        size [40, 30]
        title {
            text: "Perwadjyt",

        }
        subtitle {
            text: "Le rive del Nilo",

        }
        content {
            text: "@PCon l'aiuto della tua famiglia, il re Thinita Hor-Aha è riuscito a  unificare i due regni dell'Alto e del Basso Egitto, proclamandosi Faraone di  tutto l'Egitto e fondando la grande capitale a Men-nefer.    @PIl tuo clan si è nuovamente spostato, questa volta nelle regioni paludose del  delta nel Basso Egitto, nella regione di Perwadjyt. Le navi da guerra Canaanite  minacciano il delta e presto verrà il momento di contrastarle con le tue. @PLa tua famiglia ha raggiunto lo stato di nobiltà. Come tale, prima di passare  da questo mondo all'al di là, dovrai costruire una tomba di famiglia - una  mastaba - per custodire il tuo corpo durante il viaggio nell'altro mondo. @PMa prima di tutto dovrai costruire alcune fattorie lungo le rive del Nilo, per  sfruttare il suolo reso fertile dagli straripamenti annuali. La tua popolazione  potrà così crescere e prosperare, fino a diventare abbastanza numerosa da  potersi cimentare nell'arduo compito di costruzione del sacro monumento. Fai  attenzione, i pericoli che si nascondono tra le acque benefiche del Nilo sono  molti: mortali coccodrilli, ippopotami e zanzare portatrici di malaria. @L@LLe coltivazioni lungo il Nilo  @PDovrai costruire le fattorie esattamente sui terreni inondati, così da  sfruttare al massimo i benefici del suolo fertilizzato dal Nilo. Diversamente  dalla maggior parte delle strutture di lavoro, le fattorie e le coltivazioni non  richiedono un accesso agli impiegati, piuttosto una forza lavoro stabile di  braccianti, forniti dai campi di lavoro, che si occupino dei tuoi campi.  Costruisci i campi di lavoro abbastanza vicini alle fattorie, così i contadini  non dovranno camminare troppo a lungo per raggiungerli. @G56 @L@LIl raccolto annuale @L@POgni anno, il Nilo inonda le sue rive, ricostituendo la fertilità del suolo  con il suo fango. I contadini raccolgono le messi appena prima dello  straripamento e, quindi, le portano ai tuoi granai. Dato che c'è un solo  raccolto all'anno, assicurati di avere abbastanza granai da conservare cibo  sufficiente per tutta la tua popolazione."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Cibo o carestia?", pos [0, 15] }
        content {
            text: "@PUna popolazione in crescita ha bisogno di una riserva di cibo  costante, nonché di strutture adatte alla sua conservazione e distribuzione.  Puoi cacciare alcuni animali, come gli struzzi locali. I granai conservano carne  e altri tipi di cibo, mente i bazar distribuiscono il cibo agli abitanti del  villaggio. Come la maggior parte delle strutture di lavoro, questi edifici  devono essere situati a portata di mano dalle abitazioni e la città deve  disporre di sufficienti impiegati e lavoratori per farli funzionare al meglio. @L@LLa caccia @L@PCostruisci un casotto da caccia vicino alle mandrie di struzzi e i  cacciatori partiranno a caccia di prede. Se avranno successo, porteranno le  carcasse ai casotti per macellarle, quindi un carrettiere le porterà al granaio  più vicino. @PI lavoratori dei bazar soddisfano i vari bisogni delle persone che vivono  vicino ai negozi, prendono il cibo dai granai e lo distribuiscono alle case del  vicinato. @G60 @PPuoi costruire granai e bazar, cliccando sul pulsante relativo alle strutture  di deposito e distribuzione. @G77 @L@PInfine, l'obiettivo della tua missione è trasformare le capanne in  abitazioni migliori. Per far ciò, occorre fornire loro cibo dai bazar. Inoltre,  assicurati che non siano troppo vicine alle industrie, che possono danneggiare  l'evoluzione delle case diminuendo la desiderabilità della zona.   @L@LSupervisori @L@POra è disponibile un supervisore dei granai, in grado di fornire  informazioni e suggerimenti. Più tardi, avrai numerosi altri supervisori che ti  aiuteranno a governare la città. @G76   @L@PPer consultarli, clicca sull'icona 'Supervisori', oppure clicca con il  pulsante destro del mouse su un edificio appropriato."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Divertimento", pos [0, 15] }
        content {
            text: "Con il crescere della tua città, alcuni cittadini possono desiderare  dei passatempi e qualche forma di divertimento. Una grande varietà di  divertimenti è il segno che contraddistingue una città culturalmente avanzata,  ma al momento puoi fornire solo dei giocolieri. @L@LZone di divertimento e giocolieri @PI giocolieri hanno bisogno di spazi in cui esibirsi, il più piccolo dei quali  si chiama 'baraccone'. Costruisci un baraccone su un incrocio importante, non  distante da una scuola dei giocolieri, necessaria per addestrare le nuove leve.  Entrambi hanno bisogno di accesso agli impiegati e di addetti sufficienti a  farle funzionare. @PI giocolieri addestrati nella scuola si dirigeranno nei baracconi più vicini  per inscenare i loro spettacoli, fornendo così un minimo di divertimento alla  zona circostante. @G61 @L@LConsulta il supervisore all'intrattenimento per saperne di più sulle  necessità di svago nella tua città. Clicca sulla tabella di intrattenimento per  verificare quali siano le case che hanno accesso a tale forma di svago."
        }
    }
    message_gold_and_crime {
        id: 241,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Estrazione dell'oro" }
        content {
            text: "@L@L Estrazione dell'oro @L@PEsplorate le zone rocciose alla ricerca di oro, riconoscibile da macchie  scintillanti tra le rocce. Per estrarre l'oro, dovete costruire delle miniere  vicino alle vene e ai depositi. @G53 @L@LIl Palazzo @L@PPer trasformare l'oro in soldi, occorre costruire un Palazzo, grazie al  quale è possibile anche custodire i lingotti ricavati. Il Palazzo è la sede del  governo cittadino, e deve essere costruito vicino a una riserva d'acqua (zone  erbose). @PQuando il vostro Palazzo sarà in funzione, i minatori vi porteranno l'oro da  convertire in soldi. La valuta si chiama 'deben'. @G54 @L@LCrimine @L@PCon una grande riserva d'oro, cresce il rischio dei furti. I connestabili di  polizia aiutano a ridurre le perdite per furti, pattugliando le strade per  prevenire il crimine, e catturando i criminali che incontrano. @G55 @L@PIl modo migliore di prevenire il crimine, comunque, è mantenere la  popolazione felice, fornendo cibo, salute, igiene e posti di lavoro."
        }
    }
    message_farming_along_the_nile {
        id: 242,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Fattorie lungo il Nilo",

        }
        content {
            text: "Fattorie lungo il Nilo @L@PPer sfruttare l'incredibile fertilità del suolo, devi costruire le fattorie  direttamente sui campi bonificati. Diversamente dalle altre strutture di lavoro,  le fattorie dei campi bonificati non richiedono un accesso diretto agli  impiegati, ma necessitano di una cospicua forza lavoro di braccianti, forniti  dai campi di lavoro, per curare i poderi. Costruisci i campi di lavoro  abbastanza vicini alle fattorie site sui campi bonificati, così i contadini non  dovranno camminare molto per raggiungerle. @G56 @L@POgni anno il Nilo allaga le sue sponde, rivitalizzando il suolo con fango  ricco e fertile. I contadini recuperano il raccolto annuale appena prima dello  straripamento e lo portano ai granai. Dato che c'è un solo raccolto all'anno,  assicurati che la tua città abbia granai a sufficienza per conservare una scorta  di cibo adatta a una popolazione in crescita."
        }
    }
    message_developing_culture {
        id: 243,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Sviluppo culturale",

        }
        content {
            text: "Birra @LI tuoi connazionali hanno perfezionato l'arte di distillazione della birra,  divenuta una bevanda assai popolare in tutto l'Egitto! Con i rifornimenti di  orzo ricevuti dalle fattorie locali, le distillerie fabbricano la birra e la  consegnano ai depositi merci perché venga in seguito distribuita dagli addetti  dei bazar (come accade per il cibo e il vasellame). @L@LMolte divinità @LIl dio patrono della regione è Ra, ma Osiride e Bast sono venerati come  divinità locali. Assicurati che la città abbia più templi e santuari dedicati a  Ra, ma non trascurare le divinità locali! Per soddisfare i tuoi preziosi  cittadini, assicurati che essi abbiano accesso ai vari templi dedicati alle  diverse divinità. @L@LPiù divertimenti @LGli Egizi più raffinati amano ascoltare musica nel tempo libero e si divertono  molto con i giocolieri. I giocolieri da soli possono esibirsi in un piccolo  baraccone, mentre giocolieri e musicanti possono esibirsi insieme sul palco  dell'orchestra. Costruisci un palco presso un incrocio, e lì vicino un  conservatorio per addestrare i musicanti. L'accesso a diversi tipi  d'intrattenimento migliora molto la qualità della vita in qualsiasi città. @L@LLegge e ordine pubblico @LUn magistrato che cammina per la città aiuta a diminuire il rischio di  crimine, ascoltando le lamentele e assicurandosi che i facinorosi vengano tenuti  sotto controllo."
        }
    }
    message_getting_started {
        id: 244,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Come iniziare",

        }
        content {
            text: "Inizia designando le zone devolute alle abitazioni e all'industria.  Ora dovresti saper individuare le esigenze della tua gente, oltre ai bisogni  primari del cibo e dell'acqua. Devi rifornire le case di vasellame e birra, e  occuparti del divertimento e dell'accesso ai servizi religiosi prima di passare  all'istruzione e al commercio."
        }
    }
    message_soldiers_and_forts {
        id: 245
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Soldati e forti",
        }
        content {
            text: "Per coscrivere le truppe, costruisci un forte e un reclutatore. Il  reclutatore invierà al forte nuovi coscritti, uno dopo l'altro, finché non sarà  al completo. Esistono due tipi di forte, fanteria e arcieri, e ciascun forte  contiene sedici soldati, collettivamente chiamati 'compagnia'. Se dei soldati  muoiono in battaglia, il reclutatore provvederà ad arruolare nuovi coscritti.  @G57 @L@LArmi @PGli arcieri sono equipaggiati con archi e frecce propri, ma la fanteria deve  essere dotata di lance dalla punta in rame. Con una fornitura di rame, l'armeria  può forgiare tali armi. Queste sono poi inviate al reclutatore, così che possa  consegnarle a ogni nuovo soldato. @L@LObiettivi e loro descrizioni @PD'ora in avanti, il tuo primo obiettivo non comparirà più in cima allo  schermo. Clicca sul simbolo dell''ankh' sul pannello di controllo per rileggere  la descrizione degli obiettivi di missione, quindi visita i tuoi supervisori per  controllare i progressi fatti."
        }
    }
    message_trade_on_the_water {
        id: 246,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Sulla battigia",

        }
        content {
            text: "Commercio via acqua @LIl commercio può anche avvenire via fiume o via mare, se la città ne ha la  possibilità. Per aprire una via commerciale navigabile, consulta la mappa del  mondo. Per questo tipo di commercio, la tua città deve disporre di un molo. @L@LPescare sul Nilo @LIl Nilo è una buona riserva di pesce, un cibo assai popolare in Egitto. In  più, una dieta diversificata aiuta a migliorare la salute e l'umore dei  cittadini. Per raccogliere questo ricco bottino, ti occorrono delle barche da  pesca. @L@LCostruire barche e navi @LIl cantiere navale costruisce navi da guerra e barche da pesca. Ciascuna barca  deve possedere un molo. Ogni volta che un molo è privo della sua barca, il  cantiere navale inizierà a costruirne una. Se non esiste un molo in attesa della  sua imbarcazione, il cantiere non costruirà alcuna barca o nave.  @LAnche se un solo cantiere può costruire tutte le imbarcazioni che servono in  città, più cantieri possono rimpiazzare le imbarcazioni perdute con maggiore  rapidità. Il cantiere non ha bisogno di materiale per realizzare una barca da  pesca, ma gli occorre una fornitura di legno per costruire le imbarcazioni  militari, come le navi da guerra o da trasporto truppe. @LLe imbarcazioni militari, i mercantili e le barche da pesca sono molto larghe  e piuttosto profonde per navigare sul Nilo e le acque della costa. Non possono  navigare lungo canali stretti e in verità non possono risalire molto il corso  dei fiumi. Nulla può impedirti di costruire cantieri o moli in tali luoghi, ma  se lo fai, le barche non potranno spostarsi da tali impianti e non saranno in  grado di assolvere al loro compito. @LQuando osservi la spiaggia in cerca di luoghi idonei, tieni a mente che tutte  le navi richiedono un passaggio libero tra il loro porto e la loro destinazione.  Non puoi, ad esempio, costruire un molo da pesca su un lago interno e aspettarti  che le sue barche raggiungano il Nilo, anche se il lago è collegato a fiume da  un piccolo corso d'acqua."
        }
    }
    message_at_the_waters_edge {
        id: 247,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Sulla battigia",

        }
        content {
            text: "Commercio via acqua @LIl commercio può anche avvenire via fiume o via mare, se la città ne ha la  possibilità. Per aprire una via commerciale navigabile, consulta la mappa del  mondo. Per questo tipo di commercio, la tua città deve disporre di un molo. @L@LPescare sul Nilo @LIl Nilo è una buona riserva di pesce, un cibo assai popolare in Egitto. In  più, una dieta diversificata aiuta a migliorare la salute e l'umore dei  cittadini. Per raccogliere questo ricco bottino, ti occorrono delle barche da  pesca. @L@LCostruire barche e navi @LIl cantiere navale costruisce navi da guerra e barche da pesca. Ciascuna barca  deve possedere un molo. Ogni volta che un molo è privo della sua barca, il  cantiere navale inizierà a costruirne una. Se non esiste un molo in attesa della  sua imbarcazione, il cantiere non costruirà alcuna barca o nave.  @LAnche se un solo cantiere può costruire tutte le imbarcazioni che servono in  città, più cantieri possono rimpiazzare le imbarcazioni perdute con maggiore  rapidità. Il cantiere non ha bisogno di materiale per realizzare una barca da  pesca, ma gli occorre una fornitura di legno per costruire le imbarcazioni  militari, come le navi da guerra o da trasporto truppe. @LLe imbarcazioni militari, i mercantili e le barche da pesca sono molto larghe  e piuttosto profonde per navigare sul Nilo e le acque della costa. Non possono  navigare lungo canali stretti e in verità non possono risalire molto il corso  dei fiumi. Nulla può impedirti di costruire cantieri o moli in tali luoghi, ma  se lo fai, le barche non potranno spostarsi da tali impianti e non saranno in  grado di assolvere al loro compito. @LQuando osservi la spiaggia in cerca di luoghi idonei, tieni a mente che tutte  le navi richiedono un passaggio libero tra il loro porto e la loro destinazione.  Non puoi, ad esempio, costruire un molo da pesca su un lago interno e aspettarti  che le sue barche raggiungano il Nilo, anche se il lago è collegato a fiume da  un piccolo corso d'acqua. @L@LFabbricare mattoni @LI mattoni sono un materiale da costruzione poco costoso, utilizzato per la  creazione di certi tipi di tombe. Per fabbricare i mattoni, servono le fabbriche  e le forniture di argilla e paglia."
        }
    }
    message_the_finer_things_tutorial {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Le cose più belle",

        }
        content {
            text: "Complessi di templi @LCon il crescere della devozione nei confronti del loro patrono, gli Egizi  richiedono luoghi di culto sempre più grandi. La maggior parte delle città erige  un complesso di templi dedicato alla divinità preferita, così che possano  pienamente meritare la sua benevolenza. Una volta costruito, il complesso di  templi può essere ampliato con l'aggiunta di un oracolo e un altare, ciascuno  dedicato ad altre divinità minori. Anche queste divinità faranno sentire la loro  benefica influenza sulla città. @L@LBeni di lusso @LOltre ai gioielli realizzati localmente, gli Egizi considerano di grande  valore anche altri beni di lusso, disponibili solo tramite importazione. Una  città deve avere accesso a più di un bene di lusso per poter diventare davvero  civilizzata.  @L@LProcurare il legno @G58 @LIl legno è una merce rara e preziosa in una terra arida come quelle egizia. Le  regioni su cui si estendono delle foreste sono molto fortunate. Per procurarti  tutto il legno possibile, costruisci un taglialegna che invierà i suoi uomini ad  abbattere gli alberi. Il legno è utilizzato per costruire le navi da guerra, da  trasporto e alcune strutture di supporto ai monumenti."
        }
    }
    message_housing_and_roads {
        id: 249,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Abitazioni e strade" }
        content { text: "@PLe prime cose di cui questo villaggio necessita sono le abitazioni,  per offrire ai coloni un luogo adatto in cui vivere, e una rete stradale, per  far sì che gli abitanti possano spostarsi agevolmente. @PCostruisci zone residenziali e presto vedrai molte persone giungere nel tuo  villaggio. @G50 @L@LStrade @L@PClicca e trascina il puntatore per costruire lunghi tratti di strada. @G51 @PA ogni incrocio, gli addetti alle consegne devono scegliere quale direzione  prendere, quindi ogni intersezione diminuisce il tuo controllo sul loro  percorso. @G52 @PProgetta le strade con molta attenzione: cerca di avere il minor numero di  incroci possibile, così da assicurarti che le persone vadano dove desideri tu.  @PLa strada che gli immigranti percorrono per arrivare alla tua città si chiama  strada del Regno. Gli immigranti richiedono un passaggio libero dalla strada del  Regno alle zone residenziali. Se isoli qualche quartiere dal suo collegamento  fondamentale con il resto del mondo, ne decreterai la fine. @L@LPer uscire da una qualsiasi schermata contenente un messaggio (come questa),  clicca con il pulsante destro del mouse." }
    }
    message_basic_healthcare {
        id: 250
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Salute e igiene" }
        content { text: "La tua città soffre di problemi di salute, come spesso capita quando  la popolazione cresce. Malaria e altre malattie sono i pericoli principali,  mentre le epidemie estese sopravvengono quando le condizioni di salute sono  particolarmente inadeguate.  @PSe una casa diventa infettata per malaria o malattia, i suoi occupanti  moriranno e la casa non potrà più essere occupata per un certo periodo di tempo.  @G64 @L@LMalaria @L@PLa malaria è comune nelle zone paludose e lungo i corsi d'acqua. I rischi:  la tabella Malaria mostra quali sono le case a rischio di tale malattia. @PL'accesso a una fonte d'acqua pulita, e i repellenti per gli insetti  disponibili in farmacia, aiutano a ridurre i rischi di malaria. Come altri  edifici, la farmacia funziona quando ha una strada e addetti. @G63 @L@LMalattia @L@PI medici riducono il rischio di malattie somministrando medicine alle case  che servono. Anche un buon rifornimento di cibo può aiutare a prevenire le  malattie. I rischi: la tabella Malattia mostra quali case rischiano di essere  colpite dalle malattie." }
    }
    message_requests_from_other_cities {
        id: 251
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Richieste di altre città"
            pos [0, 20]
        }
        content {
            text: "Una delle tue città amiche è in difficoltà e ti ha fatto una  richiesta. Se vuoi rimanere in buoni rapporti con il resto del Regno, è bene che  tu risponda alle richieste con buone intenzioni e prontezza. @G65 @PSe hai una buona riserva di un dato bene, consulta il tuo supervisore per  inviare una spedizione alla città che ti ha contattato."
        }
    }
    message_fire_in_the_village {
        id: 252,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Incendio nel villaggio!" }
        content { text: "Un incendio è scoppiato nel villaggio! @L@LMessaggi @L@PQuando senti le campane che hanno suonato alla comparsa di questo pannello,  ciò significa che c'è un messaggio per te. Per leggerlo, clicca sul pulsante  messaggi. Alcuni messaggi urgenti (come questo) compaiono prima di essere  registrati insieme agli altri. Le notifiche meno urgenti, che normalmente  segnalano eventi che non richiedono immediata attenzione, finiscono direttamente  nella cassetta dei messaggi senza essere mostrati in modo particolare, quindi  fai attenzione al suono delle campane. @G66  @L@LPer scongiurare incendi futuri, puoi costruire una stazione dei pompieri.  @PCome la maggior parte degli edifici che non sono abitazioni, la stazione dei  pompieri ha bisogno di addetti per funzionare. Per arruolare dei vigili del  fuoco, dalla centrale viene inviato un messo nelle case abitate più vicine. Una  volta trovato del personale sufficiente, la stazione dei pompieri può inviare  vigili del fuoco per controllare il villaggio.  @PI vigili del fuoco ispezionano gli edifici e cercano rischi di incendio, e  riducono la possibilità di incendi lungo tutto il loro percorso. I pompieri  possono fornire i loro servizi a qualsiasi edificio entro due spazi di una  strada. @PSe viene segnalato un incendio, i pompieri arrivano sul posto per spegnere le  fiamme con secchi d'acqua, quindi ritornano al lavoro di controllo. @G67 @L@PSe un edificio è consumato dalle fiamme, clicca con il pulsante destro sulle  macerie per sapere quale fosse la sua funzione." }
    }
    message_tutorial_collapsed_building {
        id: 253,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Edificio crollato" }
        content { text: "Alcune grandi strutture possono collassare se non ricevono  manutenzioni. Per fare in modo che tale evento non si verifichi, costruisci un  centro di ingegneria. Come la stazione dei pompieri, questa struttura invia  degli ispettori che controllano le strade e riparano gli edifici danneggiati.  @G68 @L@PLa tabella dei 'rischi' ti mostra quali edifici sono in pericolo di  crollo o incendi." }
    }
    message_tutorial_education {
        id: 254
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Dei non appagati", pos [0, 15] }
        content {
            text: "I tuoi cittadini sono preoccupati perché non tutti gli dei sono  compiaciuti. Alcuni hanno avuto visioni di prossime calamità. Mantieni gli dei  soddisfatti con templi e festività a loro dedicati, o correrai il rischio della  loro ira."
        }
    }
    message_tutorial_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Riserva d'acqua",

        }
        content {
            text: "Ben fatto! Sei riuscito a fornire alla tua città una buona scorta di  cibo. Ora devi fornire acqua potabile da una riserva d'acqua, assai più gradita  di quella dei pozzi.    @L@LRiserva d'acqua @LCome i pozzi, queste devono essere costruite su terraferma, sopra una vena  d'acqua sotterranea, la cui presenza è indicata da una macchia d'erba. Le  riserve d'acqua richiedono l'accesso a impiegati da parte delle case  circostanti.  @G70 @LUna volta impiantata e funzionante, la riserva d'acqua invierà portatori  d'acqua con secchi di acqua potabile presso le case del vicinato. "
        }
    }

    message_tutorial_municipal_structures {
    id: 256,
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Municipal Structures" }
        content {
            text: "Great job! You've gotten some industry up and running, and now you can think about making a few improvements to your city. Beautification can be used to make some neighborhoods more desirable, while other Municipal Structures can help things run more efficiently.   @L@LGardens, Statues and Plazas@G72 @PBy making the area surrounding them more attractive, Gardens, Statues and Plazas can help houses to evolve.  Several Garden plots can be placed next to each other to form larger parks. Place Plazas on paved roads to enhance their appearance and improve the desirability of nearby land.  @L@LRoad Blocks @G62 @PRoad Blocks can be used to guide your city's walkers.  Some walkers have a specific destination in mind, while others do not.  They simply roam the streets, bestowing their benefits on any buildings they happen to pass.  Road Blocks prevent the passage of these walkers, but allow those with a specific destination to pass through and complete their errands. @L@LWater Crossings @G71 @PFerries can help your city run more smoothly. Carefully placed water crossings let the inhabitants of your city reach otherwise inaccessible parts of the landscape to find prey or other valuable resources. In some cases, they can improve the timeliness of certain delivery people by shortening their journeys."
        }
    }
    message_tutorial_monuments_and_more {
        id: 257
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Monumenti e altro"
        }
        content {
            text: "A questo punto della demo, puoi provare qualche altra possibilità che  Faraon ti mette a disposizione. Assicurati di consultare i tuoi supervisori per  ottenere aiuto e informazioni sulla tua città. @L@LMonumenti @L@POra puoi iniziare a costruire la tua tomba dotata di mastaba! Per completare  questo compito 'monumentale', ti occorreranno dei mattoni, muratori e contadini  manovali (forniti dai campi di lavoro). @G75 @L@LAltre amenità casalinghe @L@POltre al vasellame, le case egizie richiedono tela e birra. La birra si  fabbrica nelle distillerie, con l'orzo coltivato nei campi. La tela è fabbricata  dai tessitori di lino, un'altra coltivazione locale. Come il cibo e il  vasellame, birra e lino sono distribuiti nelle case dai lavoratori nei bazar. @L@LLegge e ordine pubblico @L@PI magistrati che dal Palazzo di giustizia vanno in strada e controllano le  strade, aiutano a ridurre il rischio del crimine, ascoltando le lamentele e  soggiogando le teste calde. @L@LSalute e igiene @L@PPer assicurare l'igiene, ogni città ha bisogno di più imbalsamatori, utili  anche a fornire rituali funebri di prestigio. La camera mortuaria utilizza la  tela fabbricata dai tessitori, e offre servizi di imbalsamazione a tutto il  vicinato. Anche i dentisti aiutano ad assicurare un buon livello di igiene. @L@LEducazione @L@PScuole e biblioteche non possono istruire le persone senza i papiri. I  raccoglitori di canne forniscono il materiale grezzo ai fabbricanti di papiri,  che vengono distribuiti direttamente alle istituzioni educative. @G69 @L@LNavi da guerra @L@PPotrebbe accadere di dover difendere la tua città con robuste navi da  guerra. Prima di tutto, ti occorre un taglialegna per fornire il legno ai  cantieri, dove verranno realizzate le navi per i relativi moli. @G58 @L@LTasse @L@PAnche se non puoi ancora aumentare gli incassi con il commercio e  l'esportazione, puoi spremere qualche deben alla tua popolazione con le tasse.  Crea esattori a sufficienza per coprire tutta la città, specialmente le case più  lussuose appartenenti agli abitanti più facoltosi."
        }
    }
    message_tutorial_the_gods_of_egypt {
        id: 258
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Culto degli dei" }
        content {
            text: "Una città egizia non può fiorire senza luoghi di culto, in forma di  templi e santuari. Questi devono essere situati vicino alle case che servono, e  ciascuno deve essere dedicato a una divinità tra cinque a scelta:  @L@POsiride - dio del Nilo @PRa - dio del Regno @PPtah - dio degli artigiani @PSeth - dio della distruzione @PBast - dea della casa @L@POgni città ha diverse tendenze religiose e in ciascuna una divinità ha il  sopravvento sulle altre - il dio patrono - mentre altri dei sono venerati come  semplici 'divinità locali' (e altri ancora sono del tutto sconosciuti). Il dio  patrono di Thinis è Bast. @PUn dio patrono può facilmente arrabbiarsi, se ritiene di non ricevere il  dovuto rispetto. Anche una divinità locale può diventare ostile, se i tempi e i  santuari a lui dedicati non sono sufficienti a servire tutta la popolazione. @PQuando un tempio ha accesso a una strada e addetti a sufficienza, da qui  possono uscire sacerdoti che garantiscono al vicinato l'accesso al culto. @G73  @L@LSupervisore religioso @L@PConsulta il tuo supervisore religioso per verificare lo stato di culto di  ciascuna divinità in ogni città, e per assicurarti che tutti siano  sufficientemente appagati. I fulmini indicano che il dio è ostile verso la tua  città, mentre le stelle indicano che è benevolente. Più sono i simboli, maggiore  è la possibilità che la tua città si accorga della presenza del dio (nel bene e  nel male!)."
        }
    }
    message_tutorial_industry {
        id: 259
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Industria" }
        content { text: "Ora che la tua gente ha cibo e acqua, devi migliorare il loro stile  di vita con altre amenità, come il vasellame. @L@LIndustria & vasellame @L@PCostruisci una cava d'argilla vicino all'acqua, e una fabbrica di vasi nelle  immediate vicinanze. Assicurati che abbiano accesso ai lavoratori e non passerà  molto tempo, prima di poter vedere un carro che consegna l'argilla al vasaio,  che fabbricherà i vasi per la tua città.  @PCostruisci un deposito merci per conservare i prodotti finiti e l'eccesso di  argilla che il vasaio non ha utilizzato (una cava d'argilla normalmente fornisce  materiale sufficiente per due vasai).   @PI negozianti dei bazar prendono i vasi dal deposito merci e li distribuiscono  esattamente come fanno con il cibo. @G74 @LLe industrie come quella del vasellame forniscono anche posti di lavoro.  Consulta il supervisore del lavoro (ora disponibile) per sapere come allocare la  forza lavoro." }
    }
    message_tutorial_trade_with_other_cities {
        id: 260
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Commercio con altre città" }
        content { text: "Ora che sei riuscito a istruire la tua gente, potresti guadagnare  qualche deben vendendo il papiro in eccedenza alle città confinanti. Dovrai  anche importare mattoni da Perwadjyt per costruire la sacra tomba mastaba.  Quando sei pronto, clicca sull'icona della mappa del regno per  scoprire quali altre città esistono nel mondo conosciuto e per iniziare  l'attività del commercio." }
    }

    message_tutorial_flooded_clay_pit {
        id: 271
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Cava d'argilla inondata" }
        content { text: "Una delle tue cave d'argilla è stata allagata. Abbiamo dovuto  distruggerla per evitare che altre crollassero." }
    }
    
    message_kingdom_road_blocked {
        id: 279
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Urgente: Strada Interrotta" }
        content { text: "La strada che porta al Regno è bloccata. Devi aprirti un varco  immediatamente." }
    }
    
    message_wrath_of_ra {
        id: 280
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira di Ra" }
        video { text: "@23" }
        content { text: "Ra punisce la tua arroganza minando la tua reputazione nel Regno.  Come tu hai snobbato il dio, così gli altri snobberanno te." }
    }

    message_wrath_of_seth {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira di Seth" }
        video { text: "@21" }
        content { text: "La tua mancanza di rispetto per Seth incita il dio a distruggere  tutte le tue navi!" }
    }

    message_wrath_of_seth_2 {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira di Seth" }
        video { text: "@21" }
        content { text: "La tua mancanza di rispetto per Seth incita il dio a distruggere  tutte le tue navi!" }
    }

    message_the_world_map {
        id: 282
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Mappa del Regno",

        }
        content {
            text: "La mappa del Regno mostra le città più importanti della tua regione.  La sua funzione principale è quella di individuare possibili interlocutori  @47commerciali. @PClicca sul nome di una città per sapere se è intenzionata a commerciare con  te. Se la città vuole commerciare, sotto il suo nome compaiono i prodotti  acquistati e venduti, oltre al costo di apertura di una via commerciale. Clicca  sul pulsante 'Apri via commerciale' per iniziare le trattative. @PSpesso riceverai richieste di merci da altre città o sentirai voci di  battaglie che infuriano in altri luoghi. La mappa del Regno è un riferimento  fondamentale per capire se tali luoghi sono vicini o lontani dalla tua città. Se  un invasore sta attaccando una città vicina, dovrai stare in guardia e fare  attenzione che il nemico non capiti dalle tue parti. @PPer ulteriori informazioni sull'uso della mappa del Regno, leggi le sezioni  @47commercio, @52guerra&e&pace e @24Supervisore&commerciale."
        }
    }

    message_tutorial_monuments {
        id: 283
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monumenti" }
        content {
            text: "Con una fornitura di mattoni, ora sei pronto a iniziare i lavori per  la mastaba. La maggior parte dei monumenti richiede i servizi di operai comuni e  specializzati. @L@LGilde&dei&costruttori @LLe gilde dei costruttori forniscono gli specialisti necessari alla costruzione  dei monumenti. La mastaba è completamente di mattoni e richiede solo i servizi  della gilda dei muratori. Puoi impiegare quante gilde di muratori desideri,  secondo le possibilità economiche, ma assicurati che ricevano un'adeguata  fornitura di mattoni affinché proseguano nei lavori. @PQuando la gilda dei costruttori dispone di manodopera, invierà i muratori al  cantiere, dove attenderanno le consegne di mattoni trasportate dai manovali. @L@LLavoro dei manovali @LQuando in un cantiere ci sono dei muratori in attesa di consegne di materiale,  gruppi di manovali sono assegnati al trasporto dei mattoni. Dato che gli stessi  operai devono anche curare le coltivazioni nei campi di limo, puoi accorgerti  che il lavoro del cantiere rallenta quando le acque straripate si ritirano. Puoi  costruire più campi di lavoro, in modo che i contadini in eccesso possano  dedicarsi alla costruzione dei monumenti durante tutto l'anno. @G75 @L@LInizia cliccando sull'icona Strutture religiose, quindi individua un luogo  adatto a ospitare questo grosso edificio."
        }
    }
    
    message_the_finer_things {
        id: 284
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Le cose più belle"
        }
        content {
            text: " Complessi di templi @LCon il crescere della devozione nei confronti del loro patrono, gli Egizi  richiedono luoghi di culto sempre più grandi. La maggior parte delle città erige  un complesso di templi dedicato alla divinità preferita, così che possano  pienamente meritare la sua benevolenza. Una volta costruito, il complesso di  templi può essere ampliato con l'aggiunta di un oracolo e un altare, ciascuno  dedicato ad altre divinità minori. Anche queste divinità faranno sentire la loro  benefica influenza sulla città. @L@LGioielli @LCon una fornitura di gemme, gli orafi della tua città possono creare splendidi  gioielli. I gioielli sono un tipo di bene di lusso, richiesto dai cittadini di  classe sociale più elevata.  @L@LBeni di lusso @LOltre ai gioielli realizzati localmente, gli Egizi considerano di grande  valore anche altri beni di lusso, disponibili solo tramite importazione. Una  città deve avere accesso a più di un bene di lusso per poter diventare davvero  civilizzata.  @L@LEstrarre la pietra @LPer estrarre la pietra, un materiale da costruzione molto ricercato,  costruisci una cava nei pressi di una zona rocciosa. I cavatori consegneranno i  blocchi di pietra, uno alla volta, al deposito merci. Usa degli architetti per  assicurarti che le cave non corrano il rischio di crolli!"
        }
    }

    message_innovations {
        id: 285
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Innovazioni"
        }        
        content {
            text: "Fattorie sui prati @LAlcuni terreni sono sufficientemente fertili da sostenere delle coltivazioni,  anche se non si trovano nei campi bonificati. Puoi identificare queste zone  erbose grazie alle piante alte e gialle che vi crescono. Alcune fattorie  stabilite sui prati possono produrre più di un raccolto per anno, anche se la  quantità di prodotto è di norma inferiore a quella di una fattoria sita nei  campi bonificati. @G59   @L@LIrrigazione @LUsa l'irrigazione per aumentare la fertilità del suolo di qualsiasi fattoria.  I canali di irrigazione nei campi bonificati possono essere collegati  direttamente al Nilo, ma per portare l'acqua sulla terra asciutta ti occorrono  dei trabocchi.   @L@LTrabocchi @LI trabocchi si possono costruire al confine con un campo bonificato, oppure  sulla costa, dove è possibile attingere all'acqua del fiume direttamente. Per  portare l'acqua alle coltivazioni dell'interno, collega un canale di irrigazione  al retro del trabocco.  @L@LScalpellini e carpentieri  @LPer erigere la piramide a gradoni occorrono due nuovi tipi di gilde di  costruttori: la gilda degli scalpellini e quella dei carpentieri. Gli  scalpellini attendono presso il cantiere i blocchi di pietra trasportati dai  manovali. Essi hanno bisogno di rampe per raggiungere i livelli più alti della  struttura. Quando occorre innalzare la piramide a gradoni di un altro livello,  un carpentiere trasporta il legno dalla gilda al cantiere e quindi costruisce la  rampa per i manovali. @L@LConservare i morti @LOgni città ha bisogno di imbalsamatori per assicurare l'igiene e per offrire  agli abitanti più esigenti i migliori rituali funebri. La camere mortuarie usano  la tela, fabbricata dalle tessitorie, e offrono servizi di imbalsamazione alle  case della zona circostante."
        }
    }

    message_troops_return_failed {
        id: 287
        type: 2
        
        size [30, 20]
        title { text: "Compagnia ritornata" }
        content { text: "Con la protezione della notte, i pochi sopravvissuti della tua  sfortunata compagnia ritornano al magro conforto dei forti cittadini,  determinati a non patire mai più una simile umiliazione in battaglia." }
    }
    message_troops_return_victorious {
        id: 288
        type: 2
        
        size [30, 20]
        title {
            text: "Tornano gli eroi!"
        }
        content {
            text: "I tuoi soldati vittoriosi sono tornati a casa. Il loro numero è un  poco ridotto rispetto a quello di partenza, ma il sacrificio dei loro  commilitoni ha reso un grande servigio a tutto l'Egitto!"
        }
    }
    message_city_retaken {
        id: 289,
        type: 2,
        
        size [30, 20]
        title { text: "City retaken" }
    }
    message_osiris_is_upset {
        id: 290
        type: 2
        
        size [30, 20]
        title { text: "Osiride è contrariato" }
        content { text: "Se non fai qualcosa per appagarlo, il signore del Nilo punirà la tua  città e lo straripamento del prossimo anno distruggerà tutti gli edifici che  incontrerà sul suo cammino!" }
    }
    message_ra_is_upset_2 {
        id: 291
        type: 2
        
        size [30, 20]
        title { text: "Ra è infuriato" }
        video { text: "@23" }
        content { text: "Arrabbiato per la tua mancanza di rispetto, Ra infama la tua  reputazione agli occhi di tutto il Regno." }
    }
    message_ptah_is_upset {
        id: 292
        type: 2
        
        size [30, 20]
        title { text: "Ptah è contrariato" }
        video { text: "@22" }
        content { text: "Costernato per il tuo disinteresse, Ptah ha distrutto uno dei tuoi  depositi merci." }
    }
    message_seth_is_upset {
        id: 293
        type: 2
        
        size [30, 20]
        title { text: "Seth è contrariato" }
        video { text: "@21" }
        content { text: "Seth ha distrutto la tua migliore compagnia e il suo forte." }
    }
    message_bast_is_upset {
        id: 294
        type: 2
        
        size [30, 20]
        title { text: "Bast è contrariata" }
        video { text: "@20" }
        content { text: "La dea Bast è dispiaciuta della mancanza di rispetto della tua città,  e ha scatenato una nuvola pestilenziale suoi tuoi cittadini." }
    }
    message_blessing_from_osiris {
        id: 295
        type: 2
        
        size [30, 20]
        title { text: "Benedizione di Osiride" }
        video { text: "@24" }
        content { text: "Osiride, dio del Nilo, benedice la tua città per la sua sincera  devozione. Durante questa stagione, tutte le fattorie dei campi bonificati  raccoglieranno il doppio!" }
    }
    message_construction_blessing {
        id: 1012
        type: 2

        size [30, 20]
        title { text: "A Construction Blessing" }
        content { text: "The gods are pleased by your devotion and give a major boost to your monument. Let your workers stand aside while this blessing is received." }
    }
    message_construction_blessing_minor {
        id: 1013
        type: 2

        size [30, 20]
        title { text: "A Construction Blessing" }
        content { text: "The gods acknowledge your worship by aiding your monument. Let your workers rest briefly while this gift arrives." }
    }
    message_blessing_trade_from_ra {
        id: 296
        type: 2
        
        size [30, 20]
        title { text: "Benedizione di Ra" }
        video { text: "@23" }
        content { text: "Ra ricompensa i suoi fedeli! Per i prossimi 12 mesi la tua città può  vendere i prodotti esportati con una maggiorazione del 50%." }
    }
    message_blessing_trade_from_ptah {
        id: 297
        type: 2
        
        size [30, 20]
        title { text: "Benedizione di Ptah" }
        video { text: "@22" }
        content { text: "Ptah ha scelto un deposito merci e ha aumentato la quantità di gemme,  argilla, vasellame, lino, tela e gioielli lì contenuti." }
    }
    message_blessing_trade_from_seth {
        id: 298
        type: 2
        
        size [30, 20]
        title { text: "Benedizione di Seth" }
        video { text: "@21" }
        content { text: "Seth apprezza il tuo timore la tua obbedienza, quindi abbatterà il  prossimo nemico che oserà violare la tua città." }
    }
    message_blessing_from_bast {
        id: 299,
        type: 2,
        
        size [30, 20]
        title { text: "Benedizione di Bast" }
        video { text: "@20" }
        content { text: "Dato che questa città le è così fedele, Bast benedice le sue case e  bazar con abbondanza di cibi e prodotti!" }
    }
    message_the_gods_are_wrathful {
        id: 300
        type: 2
        
        size [30, 20]
        title { text: "Gli Dei sono adirati" }
        content { text: "Almeno un dio è adirato con la città. La tua gente ti scongiura di  costruire più templi... oppure di indire qualche festività." }
    }
    message_illness {
        id: 301,
        type: 2,
        
        size [30, 20]
        title { text: "Illness" }
        video { text: "smk\\sick.smk" }
    }
    message_disease {
        id: 302,
        type: 2,
        
        size [30, 20]
        title { text: "Disease" }
        video { text: "smk\\sick.smk" }
    }
    message_pestilence {
        id: 303,
        type: 2,
        
        size [30, 20]
        title { text: "Pestilence" }
        video { text: "smk\\sick.smk" }
    }
    message_the_spirit_of_seth {
        id: 304,
        type: 2,
        
        size [30, 20]
        title {
            text: "Lo spirito di Seth",
        }
        video {
            text: "@21"
        }
        content {
            text: "Seth ricorda la sua promessa di proteggerti ed è felice di punire chi  è stato così stolto da minacciare la tua città."
        }
    }
    message_the_emperors_respect {
        id: 305,
        type: 2,
        
        size [30, 20]
        title {
            text: "The Emperor's respect",
        }
    }
    message_the_emperors_respect_1 {
        id: 306,
        type: 2,
        
        size [30, 20]
        title { text: "The Emperor's respect" }
    }
    message_the_emperors_respect_2 {
        id: 307,
        type: 2,
        
        size [30, 20]
        title { text: "The Emperor's respect" }
    }
    message_working_hippodrome {
        id: 308,
        type: 2,
        
        size [30, 20]
        title { text: "Working hippodrome" }
        video { text: "smk\\\\1st_chariot.smk" }
    }
    message_compliance_now_possible {
        id: 309,
        type: 2,
        message_type: 2,
        
        size [30, 20]
        title { text: "Richiesta soddisfabile" }
        content { text: "Il tuo supervisore politico ti informa che la città ora dispone di  deben a sufficienza per soddisfare le recente richiesta." }
    }
    message_tutorial_finances {
        id: 310,
        type: 2,
        message_type: 4
        size [40, 30]
        title { text: "Finanze" }
        content {
            text: "Tasse @LUna grande città deve poter trovare fonti di reddito addizionali, oltre ai  suoi fondi iniziali. Un metodo per raggiungere questo scopo è quello di imporre  le tasse. Per imporre le tasse, la tua città deve avere un Palazzo e degli  esattori. Assicurati di creare abbastanza esattori da coprire tutta la città, in  particolare i quartieri alti. Ricorda che, se in una casa la qualità di vita è  buona, i suoi occupanti pagheranno più tasse. @L@LIl tuo salario @LSe costruisci una magione per te stesso, puoi richiedere un salario che verrà  sottratto dai fondi cittadini. I fondi personali sono custoditi dalla tua  famiglia e possono essere utilizzati quando la situazione lo richiede, anche in  missioni successive. Fai attenzione, comunque, in quanto un salario troppo  elevato rispetto al tuo livello può avere effetti negativi sulla tua reputazione  nel Regno."
        }
    }
    message_mission_defeat {
        id: 311,
        type: 2,
        
        size [30, 20]
        title { text: "Sconfitta!" }
        content { text: "Oh, triste giorno! Eppure la tua ignobile fine era impensabile. Hai  deluso la tua gente, i tuoi antenati e i tuoi discendenti. Ora l'Egitto attende  un altro campione che prenda il tuo posto..." }
    }
    message_mission_victory {
        id: 312,
        type: 2,
        
        size [30, 20]
        title { text: "The Winner" }
        video { text: "smk\\win_game.smk" }
        content { text: "This is the happiest day of your career! The only challenge left to  you is ruling the Empire itself. Rome knows no greater governor." }
    }
    message_enemy_rome_army_attacks {
        id: 313
        type: 2
        message_type: 7
        
        size [30, 20]
        title { text: "Enemy army attacks" }
        video { text: "smk\\spy_army.smk" }
        content { text: " Enemies of Rome are at the outskirts of your city. Expect them to  drop in for an urn or two of wine - and whatever else strikes their fancy!" }
    }
    message_storage_yards_ready_to_fulfill_request {
        id: 314,
        type: 2,
        message_type: 2,
        
        size [30, 20]
        title {
            text: "Richiesta soddisfabile",
        }
        content {
            text: "Il tuo supervisore politico ti informa che ora i depositi cittadini  contengono merci a sufficienza per soddisfare le recente richiesta."
        }
    }
    message_kingdom_road_obstructed {
        id: 315,
        type: 2,
        
        size [30, 20]
        title {
            text: "Urgente: strada bloccata",
        }
        content {
            text: "Gli architetti hanno dovuto demolire una recente costruzione per  rendere di nuovo agibile il passaggio verso la @57strada&del&Regno. Devi  rimuovere le macerie immediatamente."
        }
    }
    message_no_working_dock {
        id: 316,
        type: 2,
        
        size [30, 20]
        title { text: "Nessun porto operativo" }
        content { text: "Anche se hai ordinato al supervisore commerciale di iniziare il  commercio con un mercante marittimo, costui non può attraccare alla tua città!  Devi quindi costruire un porto e dotarlo di lavoratori. Quando il tuo porto sarà  in funzione, le navi potranno attraccare e iniziare così il commercio." }
    }
    message_fishing_boats_cant_navigate {
        id: 317,
        type: 2,
        
        size [30, 20]
        title { text: "Le barche da pesca non possono navigare" }
        content { text: "I nostri pescatori ci informano che un ponte blocca il loro percorso!  Le barche, infatti, non possono passare sotto i ponti. Rimuovi il ponte per far  sì che le barche possano rifornire di pesce la tua città." }
    }
    message_health {
        id: 318,
        type: 3,
        
        size [30, 20]
        title {
            text: "Sanità",
        }
        content {
            text: "Alla gente piace sentirsi in forma. Se si nutre adeguatamente e viene  regolarmente visitata da un dottore, godrà di ottima salute. Se la salute viene  a mancare, avranno più probabilità di ammalarsi. @PGli ospedali servono in caso di malattia. Tutti gli ammalati hanno bisogno di  un ospedale. Se nell'ospedale non c'è spazio sufficiente ad accoglierli, essi  muoiono. @PLe cliniche prevengono la malattia e gli ospedali la curano. @L@LA volte può scoppiare una pestilenza e si sa che Bast non perdona le città  che non le portano rispetto. In tali occasioni, una buona disponibilità di  ospedali è l'unico rimedio. Il tuo supervisore sanitario può dirti se la  disponibilità degli ospedali è più o meno sufficiente."
        }
    }
    message_messages_await_you {
        id: 319,
        type: 3,
        
        size [30, 20]
        title {
            text: "Messaggi in attesa",
        }
        content {
            text: "Il suono della fanfara serve a indicare che il tuo scriba ha ricevuto  un altro messaggio per te e lo ha riposto nel suo registro. @L@LAlcuni messaggi, come questo, si aprono automaticamente. Si tratta di  messaggi urgenti e il tuo scriba ritiene che dovresti leggerli subito. Se vuoi,  puoi leggerli in un secondo momento, cliccando sul pulsante messaggi. @PI messaggi importanti, ma non urgenti, vengono segnalati con una fanfara più  potente, ma non compaiono automaticamente. La maggior parte dei messaggi tratta  argomenti meno importanti ed è accompagnata da una fanfara più regolare. Puoi  leggerli quando ti fa più comodo. @L@LTutti i messaggi sono conservati dal tuo scriba, quindi puoi farvi  riferimento in qualsiasi momento. Se vuoi, puoi anche cancellarli. Se desideri  ulteriori informazioni, seleziona le voce Aiuto dalla Barra dei menu e clicca su  'Messaggi dal tuo scriba' (verso la fine del sommario)."
        }
    }
    message_local_uprising {
        id: 320,
        message_type: 7
        
        size [30, 20]
        urgent: 1
        title { text: "Rivolta locale" }
        content { text: "Ispirati da Seth, alcuni cittadini hanno dato sfogo alle loro  lamentele da troppo tempo trattenute!!" }
    }
    message_small_blessing_from_osiris {
        id: 321
        type: 2
        
        size [30, 20]
        title { text: "Piccola benedizione di Osiride" }
        video { text: "@24" }
        content { text: "La devozione della tua città nei confronti di Osiride, dio del Nilo,  non è passata inosservata. Se Osiride continuerà a essere così onorato, lo  straripamento del prossimo anno sarà perfetto e depositerà moltissimo fango  fertile lungo le rive del Nilo." }
    }
    message_minor_blessing_from_ra {
        id: 322
        type: 2
        
        size [30, 20]
        title { text: "Piccola benedizione di Ra" }
        video { text: "@23"}
        content { text: "Compiaciuto del tuo rispetto, Ra eleva leggermente la tua reputazione  in tutto il Regno." }
    }
    message_minor_blessing_from_ptah {
        id: 323
        type: 2
        
        size [30, 20]
        title { text: "Piccola benedizione di Ptah" }
        video { text: "@22" }
        content { text: "Ptah è compiaciuto della tua attenzione, quindi si assicura che i  cantieri navali, le tessitorie o gli orafi della città abbiano tutto il  materiale grezzo che serve loro." }
    }
    message_minor_blessing_from_seth {
        id: 324
        type: 2
        
        title { text: "Piccola benedizione di Seth" }
        video { text: "@21" }
        content { text: "Per ricompensare la tua obbedienza, Seth promette di proteggere i  tuoi soldati inviati in battaglie lontane." }
    }
    message_small_blessing_from_bast {
        id: 325
        type: 2
        
        size [30, 20]
        title { text: "Piccola benedizione di Bast" }
        video { text: "@20" }
        content { text: "Bast ha piacere che la tua città la onori. Ha così indetto una  festività, così che tutti gli dei possano notare la tua dedizione." }
    }
    message_disease_strikes {
        id: 326,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "La malattia colpisce",
        }
        content {
            text: "La malattia ha colpito una casa dotata di scarso accesso alle cure  mediche. Gli abitanti muoiono e tu non puoi aiutarli. Migliora le zone meno  salubri per impedire che capiti di nuovo."
        }
    }
    message_a_plague {
        id: 327,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Una pestilenza",
        }
        content {
            text: "La peste devasta la città! Temevamo che potesse accadere, data la  scarsa @53sanità&pubblica. Prega che le nostre farmacie riescano a contenerla."
        }
    }
    message_malaria {
        id: 328,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Malaria",
        }
        content {
            text: "Alcune case sono infettate dalla malaria. Migliori condizioni  sanitarie possono impedire questo inutile spreco di vite umane!"
        }
    }
    message_blessing_reputation_from_ra {
        id: 329,
        type: 2,
        
        size [30, 20]
        title { text: "Benedizione di Ra" }
        video { text: "@23" }
        content {
            text: "Tu hai reso onore a Ra, quindi la tua reputazione in tutto il Regno è  nettamente migliorata!"
        }
    }
    message_minor_blessing_trading_from_ra {
        id: 331,
        type: 2,
        
        size [30, 20]
        title { text: "Piccola benedizione di Ra" }
        video { text: "@23" }
        content { text: "Per ricompensare il tuo comportamento rispettoso, Ra induce i  commercianti tuoi interlocutori a comprare più prodotti." }
    }
    message_wrath_of_ra_2 {
        id: 332,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Ra" }
        video { text: "@23" }
        content { text: "Hai provocato l'ira di Ra! Il dio ha diminuito l'importanza delle tue  merci e i tuoi soci in affari compreranno molto meno di prima." }
    }
    message_wrath_of_ra_3 {
        id: 333,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Ra" }
        video { text: "@23" }
        content { text: "Come hai abbandonato Ra, così i tuoi soci in affari abbandoneranno  te. Nessuna nave mercantile o carovana visiterà la tua città per un anno  intero." }
    }
    message_ra_is_upset {
        id: 334,
        type: 2,
        
        size [30, 20]
        image { id: 224, pos [15, 15] }
        title { text: "Ra è arrabbiato!" }
        video { text: "@23" }
        content { text: "Come hai snobbato Ra, così i tuoi soci in affari snobberanno i  prodotti della tua città. Essi hanno infatti deciso di acquistare quantitativi  di merci inferiori rispetto al passato." }
    }
    message_wrath_of_bast_2 {
        id: 335,
        type: 2,

        size [30, 20]
        title { text: "Ira di Bast", }
        content { text: "L'ira di Bast è su di te. Sorridi pure, se vuoi, in quanto al momento  non ha alcun potere su di te... ma la prossima volta potresti non essere così  fortunato!" }
    }
    message_wrath_of_ra_4 {
        id: 336,
        type: 2,
        
        size [30, 20]
        title {
            text: "Ira di Seth",
        }
        content {
            text: " L'amara rabbia di Seth è su di te. Ridi pure, se vuoi, dato che non  hai eserciti di alcun valore, ma Seth non si lascia insultare così facilmente.  Fai attenzione!"
        }
    }
    message_wrath_of_osiris_3 {
        id: 337,
        type: 2,
        
        size [30, 20]
        title {
            text: "Ira di Osiride",
        }
        video {
            text: "@24"
        }
        content {
            text: "Osiride è molto arrabbiato, ma non ha il potere di punire la tua  città. Questa volta sei stato fortunato, ma la prossima..."
        }
    }
    message_blessing_inundation_from_osiris {
        id: 340,
        type: 2,
        
        size [30, 28]
        title { text: "Osiride ti benedice" }
        video { text: "@24" }
        content { text: "Osiride ricompensa chi lo onora. Il prossimo straripamento sarà più  benefico di quanto previsto." }
    }
    message_wrath_of_osiris_4 {
        id: 341,
        type: 2,
        
        size [30, 20]
        title { text: "Ira di Osiride" }
        video { text: "@24" }
        content { text: "Osiride ti ricorda di portargli rispetto. Il prossimo straripamento  sarà meno efficace di quanto previsto." }
    }
    message_mediocre_inundation_seers {
        id: 342,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "I sacerdoti predicono che lo straripamento del prossimo anno sarà  scarso." }
    }
    message_poor_inundation_seers {
        id: 343,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "I sacerdoti predicono che lo straripamento del prossimo anno sarà  scarso." }
    }
    message_no_inundation {
        id: 344,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "Brutte notizie! I sacerdoti temono che quest'anno non ci sarà alcuno  straripamento del Nilo!" }
    }
    message_poor_inundation {   
        id: 345,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "I sacerdoti predicono uno scarso straripamento del Nilo per il  prossimo anno. Per impedire che tale disastroso evento si verifichi in futuro  devi cercare di compiacere Osiride." }
    }
    message_mediocre_inundation {
        id: 346,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "Sfortunatamente, sembra che lo straripamento del prossimo anno sarà  mediocre. Se la città onorerà meglio Osiride, forse tale calamità non si  ripeterà per l'anno seguente." }
    }
    message_good_inundation {
        id: 347,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "I sacerdoti di Osiride predicono un buono straripamento del Nilo per  il prossimo anno." }
    }
    message_excellent_inundation {
        id: 348,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "I sacerdoti si rallegrano, il prossimo anno si verificherà un  eccellente straripamento del Nilo!" }
    }
    message_perfect_inundation {
        id: 349,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Previsioni straripamento" }
        content { text: "La città è benedetta. I nostri sacerdoti predicono uno straripamento  perfetto del Nilo per il prossimo anno! Continuando a onorare Osiride, la città  potrà essere favorita allo stesso modo anche per l'anno seguente!" }
    }
    message_temple_complex_to_osiris {
        id: 350,
        
        size [30, 20]
        title {
            text: "Complesso templi di Osiride",
        }
        subtitle {
            text: "Religione",
        }
        content {
            text: "Quando costruisci un complesso templi dedicato a Osiride, il dio è  più propenso a favorire straripamenti migliori anno per anno. In un complesso  templi di Osiride puoi costruire le seguenti strutture: @L@LAltare di Sebek, dio della fertilità @LSebek dona ai sacerdoti di Osiride il potere di estendere le scorte di cibo e  merci della città. Quando i sacerdoti di Osiride camminano per la città, la  gente nelle case visitate si accontenta di meno. @L@LOracolo di Min, dio della rigenerazione @LSe la tua città onora Min con un oracolo, il dio velocizza la ricrescita di  alberi e canne, aumenta il ritmo di riproduzione degli animali da preda e  migliora la pesca e la caccia. @L@LLa gente adora vivere vicino a un complesso di templi. Per ulteriori  informazioni sulla religione, clicca @51qui. @L@LLeggi altre informazioni su Osiride, Sebek e Min cliccando @376qui."
        }
    }
    message_temple_complex_to_ra {
        id: 351,
        
        size [30, 20]
        title {
            text: "Complesso templi di Ra",
        }
        content {
            text: "Ra sorride alla città quando questa gli dedica un complesso templi ed  egli si assicura che anche altri nel Regno le sorridano. La costruzione di un  complesso templi di Ra aumenta il livello del Regno e, se la città si trova in  debito, ti concede un interesse inferiore. La costruzione di un altare e un  oracolo all'interno del complesso templi di Ra ti aiuta a gestire meglio gli  affari cittadini: @L@LAltare di Ma'at, dea della giustizia @LTramite i sacerdoti di Ra, Ma'at benedice la tua città con un effetto  tranquillizzante. Quando passano vicino alle case, i sacerdoti di Ra dissuadono  i potenziali ladri che vi risiedono. La sola presenza dell'altare riduce il  rischio generale di crimine. @L@LOracolo di Horus, dio dei Faraoni @LQuesto oracolo aumenta la fedeltà della tua gente alla città e al Regno,  incoraggiandola ad accettare salari inferiori senza influire negativamente sul  loro umore. @L@LLa gente adora vivere vicino a un complesso templi. Per ulteriori  informazioni sulla religione, clicca @51qui. @L@LLeggi altre informazioni su Ra, Ma'at e Horus cliccando @377qui."
        }
    }
    message_temple_complex_to_ptah {
        id: 352,
        
        size [30, 20]
        title {
            text: "Complesso templi di Ptah",
        }
        content {
            text: "Quando dedichi un complesso templi a Ptah, egli velocizza la  produzione di alcune industrie, come le miniere d'oro, di rame e di gemme, le  cave d'argilla, i cantieri navali, i gioiellieri e i tessitori. L'altare e  l'oracolo nel complesso templi di Ptah velocizzano la produzione di altre  industrie e migliorano l'efficacia degli insegnanti: @L@LAltare di Amon, dio del sole @LOnorato della tua attenzione, Amon velocizza le cave, i taglialegna e le  fabbriche di mattoni. @L@LOracolo di Thoth, dio della saggezza e dell'istruzione @LLa missione di Thoth è portare la luce del sapere al maggior numero di  persone. Quando costruisci un oracolo di Thoth, i bibliotecari e gli insegnanti  usano meno papiro per istruire gli abitanti della città. @L@LLa gente adora vivere vicino a un complesso templi. Per ulteriori  informazioni sulla religione, clicca @51qui. @L@LLeggi altre informazioni su Ptah, Amon e Thoth cliccando @378qui."
        }        
    }
    message_temple_complex_to_seth {
        id: 353,
        
        size [30, 20]
        title { text: "Complesso templi di Seth" }
        content { text: "Quando una città ha un complesso templi a lui dedicato, Seth instilla  grande coraggio nei suoi soldati, concedendo loro maggiore esperienza e  proteggendoli nelle battaglie. Le aggiunte nel complesso templi di Seth sono:  @L@LAltare di Anubis, dio della morte @LAnubis concede un accesso all'aldilà più semplice per tutti i cittadini. Con  la sua benedizione, le camere mortuarie hanno bisogno di meno tela per preparare  i defunti al lungo viaggio.   @L@LOracolo di Sekhmet, dea della guerra @LSekhmet concede ai sacerdoti di Seth il potere di ridurre il rischio di  crimine nelle case che visitano e di arrestare i criminali che incontrano.  @L@LLa gente adora vivere vicino a un complesso templi. Per ulteriori  informazioni sulla religione, clicca @51qui. @L@LLeggi maggiori informazioni su Seth, Anubis e Sekhmet cliccando @379qui." }
    }
    message_temple_complex_to_bast {
        id: 354,
        
        size [30, 20]
        title { text: "Complesso templi di Bast" }
        content { text: "La presenza di un complesso templi di Bast porta fortuna alla città.  Bast mantiene i cittadini felici facendo in modo che si accontentino di meno.  Come risultato della sua benevolenza, la velocità con cui i cittadini consumano  cibo e beni viene ridotta e gli effetti degli artisti, insegnanti e addetti alla  salute pubblica dura di più. Anche le divinità sue sorelle migliorano la qualità  di vita dei tuoi cittadini: @L@LAltare di Iside, dea della guarigione @LTramite le sacerdotesse di Bast, Iside impone le sue mani guaritrici su tutta  la popolazione, rimuovendo i cittadini infetti dalle strade e purificando le  abitazioni infette che visitano. Iside, inoltre, si incarica di migliorare il  livello generale di salute. @L@LOracolo di Hathor, dea della gioia, dell'amore e delle festività @LHathor, onorata dall'oracolo che le hai dedicato, migliorerà  l'@39umore&cittadino. @L@LLa gente adora vivere vicino a un complesso templi. Per ulteriori  informazioni sulla religione, clicca @51qui. @L@LLeggi maggiori informazioni su Bast, Iside e Hathor cliccando @380qui." }
    }
    message_building_firehouse {
        id: 355,
        
        size [30, 20]
        title {
            text: "Stazione dei pompieri",
        }
        content {
            text: "Alcuni edifici della città possono incendiarsi. I più inclini  all'incendio sono le case malcurate e alcune industrie come i vasai. Se non fai  nulla per fermare le fiamme, esse si propagheranno in tutta la città,  distruggendone interi settori in poco tempo. Per evitare tale disastro,  costruisci delle stazioni dei pompieri vicino agli edifici che corrono  maggiormente il rischio di incendio. I vigili del fuoco delle stazioni dei  pompieri camminano per le strade (clicca @42qui per ulteriori informazioni sui  passanti) e riducono il rischio che le case visitate prendano fuoco. @PIn caso di incendio, i vigili del fuoco più vicini si recano sul posto per  spegnere le fiamme. Se un vigile del fuoco deve camminare a lungo, le fiamme  potrebbero comunque propagarsi e i loro effetti distruttivi sarebbero comunque  gravi. @G67 @Pla @18tabella&Incendi è una guida utile alla prevenzione degli incendi. Tale  tabella mostra i vigili del fuoco al lavoro, ma individua soprattutto gli  edifici più inclini alle fiamme. Usa questa informazione per stabilire  l'ubicazione delle stazioni dei pompieri. @PLe stazioni dei pompieri richiedono l'accesso a una strada e manodopera per  funzionare con efficienza. Ai residenti non piace vivere vicino a una stazione  dei pompieri."
        }
    }
    message_building_warship_wharf {
        id: 356,
        
        size [30, 20]
        title {
            text: "Molo delle navi da guerra",
        }
        content {
            text: "I moli delle navi da guerra ormeggiano le navi da guerra. La prima  cosa che fa un molo non appena costruito è ordinare una nave da guerra al  @82cantiere&navale.  @PUn molo delle navi da guerra richiede l'accesso a una strada e manodopera.  Deve trovarsi su un tratto di costa rettilineo e le navi devono poterlo  raggiungere facilmente. I cittadini non desiderano vivere vicino ai moli. Alcuni  marinai, dopo tutto, non godono di buona reputazione. @PQuando un nave da guerra non è impegnata nell'azione bellica, il suo  equipaggio preferisce rimanere al sicuro presso il molo. Qui, infatti, può  riposarsi fino alla battaglia successiva. @PLeggi la sezione sulle @365navi&da&guerra per sapere come manovrarle in  battaglia. @L@LLa tradizione militare dell'antico Egitto è piena di eventi. Clicca @184qui  per saperne di più."
        }
    }
    message_building_transport_wharf {
        id: 357,
        
        size [30, 20]
        title {
            text: "Molo delle navi da trasporto truppe",
        }
        content {
            text: "I moli delle navi da trasporto truppe ormeggiano le navi da trasporto  truppe. La prima cosa che fa un molo delle navi da trasporto truppe appena  costruito è ordinare una nave da trasporto truppe al @82cantiere&navale.  @PI moli delle navi da trasporto truppe richiedono l'accesso a una strada e mano  d'opera. Devono essere posizionati su un tratto di costa rettilineo e le navi  devono essere in grado di raggiungerlo facilmente. I tuoi cittadini non  desiderano vivere vicino ai moli.  @PLeggi la sezione sulle @367navi&da&trasporto&truppe per sapere come manovrarle  in battaglia. @L@LLa tradizione militare dell'antico Egitto è piena di eventi. Clicca @181qui  per saperne di più."
        }
    }
    message_building_roadblock {
        id: 358,
        
        size [30, 20]
        title {
            text: "Blocco stradale",
        }
        content {
            text: "I blocchi stradali ti aiutano a controllare il cammino dei  @42passanti&senza&meta. Quando questi ultimi incontrano un blocco stradale, invertono la direzione di marcia. I blocchi stradali non hanno alcun effetto sui passanti con meta. @PCostruisci un blocco stradale ovunque i passanti senza meta non devono andare - ad esempio, sulla strada che porta alle strutture industriali. Fai attenzione, però, a non isolare completamente alcune zone cittadine. Lo stesso blocco che impedisce a un venditore del bazar di andare nella zona industriale impedisce il passaggio anche agli architetti, vigili del fuoco e conestabili. Inoltre, ferma gli addetti alla ricerca di lavoratori che dalla zona industriale si spostano nei quartieri residenziali alla ricerca di impiegati. @G62 @PQuando costruisci un nuovo blocco stradale vicino a un edificio esistente, è bene osservare un attimo l'edificio per verificare che il suo passante esca dalla parte giusta del blocco. A volte, gli impiegati dell'edificio non capiscono le tue intenzioni e inviano i loro passanti nella direzione sbagliata. Tale situazione è particolarmente seccante con gli addetti alla ricerca di personale, poiché la struttura che li impiega crede di avere accesso alla forza lavoro, ma il blocco stradale impedisce agli addetti di raggiungerla. L'unico rimedio e ricostruire il blocco un po' più distante. @PI blocchi stradali non richiedono manodopera e l'unica loro restrizione è la costruzione su una strada. Non hanno alcun effetto sulla desiderabilità."
        }
    }
    message_building_hunting_lodge {
        id: 359,
        
        size [30, 20]
        title {
            text: "Casotto da caccia",
        }
        content {
            text: "Costruisci un casotto da caccia per inviare i cacciatori alla ricerca delle loro prede. Struzzi, folaghe e antilopi sono le prede designate. @PPuoi costruire casotti da caccia ovunque, ma è bene che siano vicini alle prede, che a loro volta tendono a rimanere nei loro territori. I casotti da caccia richiedono l'accesso a una strada e manodopera. Quando sono in funzione, puoi vedere un cacciatore nel suo cortile mentre si esercita con l'arco. @PI cacciatori si inoltrano nei campi dove si trovano le loro prede. Quando un cacciatore uccide la sua preda, egli porta la carcassa al casotto da caccia dove viene trasformata in carne commestibile. Quando è pronto un carro di carne, questo viene portato in un @3granaio o in un @4deposito&merci (se hanno il permesso di accettare la cacciagione). @G60 @PLa cacciagione può essere una parte importante della dieta dei tuoi cittadini, in quanto fornisce un po' di varietà. La città, però, non può essere in grado di sostenersi solo con la cacciagione. I branchi e gli stormi sono limitati, quindi la caccia da sola non può provvedere a tutto il fabbisogno di cibo della città. Per ulteriori informazioni sul cibo, consulta la sezione sulle @45coltivazioni&e&cibo. @PLa selvaggina (insieme alla paglia) si usa anche per nutrire gli animali allo @479zoo.  @PI casotti da caccia hanno un effetto negativo sulla @56desiderabilità. @L@LNell'antico Egitto, la cacciagione era parte integrante della dieta quotidiana e la caccia era uno sport assai diffuso. Clicca @383qui per saperne di più."
        }
    }
    message_building_cattle_ranch {
        id: 360,
        
        size [30, 20]
        title {
            text: "Allevamento bestiame",
        }
        content {
            text: "Alleva il bestiame negli allevamenti per fornire la carne ai tuoi cittadini. @PGli allevamenti di bestiame devono essere disposti vicino a una strada e richiedono manodopera. Essi necessitano anche della paglia, delle @89fattorie&di&grano o di @47importazione. Gli allevamenti di bestiame non devono essere costruiti su terreno fertile e non richiedono nemmeno l'accesso all'acqua. @PLeggi la sezione sulle @45coltivazioni&e&cibo per conoscere meglio la dieta dei tuoi cittadini. @PGli allevamenti di bestiame emanano cattivo odore e, quindi, i cittadini non gradiscono la loro vicinanza. @L@LGli antichi egizi allevavano diversi animali per procurarsi il cibo. Clicca @186qui per saperne di più."
        }
    }
    message_building_gemstone_mine {
        id: 361,
        
        size [30, 20]
        title {
            text: "Miniera di gemme",
        }
        content {
            text: "Le gemme sono estratte dalle zone rocciose. Osservando una zona  rocciosa, non vi è modo di sapere a priori se contiene gemme o meno. Se queste  possono essere estratte, le miniere di gemme saranno presenti nell'elenco  Strutture industriali: Materiali grezzi. Come le @95cave, le miniere di gemme  devono essere adiacenti alle zone rocciose, richiedono manodopera e l'accesso  a una strada. Esse sono inclini ai crolli, quindi assicurati di costruire un  @81centro&di&architettura nelle loro vicinanze. @PLe miniere di gemme sono luoghi polverosi e i cittadini non vogliono vivere  nei loro pressi. @L@LPer ottenere ulteriori informazioni sulle gemme nell'antico Egitto, clicca  @382qui."
        }
    }
    message_building_sphinx {
        id: 362,
        
        size [30, 20]
        title {
            text: "Sfinge",
        }
        content {
            text: "La sfinge è una statua scolpita e dipinta protettrice delle piramidi. @PPer costruire una sfinge, devi prima trovare un luogo adatto. Seleziona la  voce Sfinge dall'elenco Strutture religiose: Monumenti. Apparirà l'impronta  della sfinge; mentre la sposti sulla mappa, può apparire completamente verde  oppure verde con qualche quadrato rosso. Quando è tutta verde, significa che il  luogo scelto è adatto. Clicca con il pulsante del mouse e sul posto comparirà la  pietra adatta. Se l'impronta presenta dei quadrati rossi, significa che alcuni  ostacoli del terreno ti impediscono di costruirla in quel punto. @POra gli @363scalpellini e i @363carpentieri possono iniziare i lavori, se  disponi del legno necessario. I carpentieri costruiscono le impalcature  necessarie agli scalpellini per scolpire le parti più alte della sfinge. @PClicca sulla sfinge con il pulsante destro del mouse per parlare con il  @369capo&cantiere e ottenere un rapporto sull'avanzamento lavori. @L@LClicca @391qui per alcune interessanti informazioni sulla sfinge più  famosa."
        }
    }
    message_construction_guilds {
        id: 363,
        
        size [30, 20]
        title {
            text: "Gilde dei costruttori",
        }
        content {
            text: "Senza le gilde dei costruttori, non saresti in grado di costruire gli  splendidi monumenti che rendono onore all'Egitto e al Faraone. @PEsistono quattro diverse gilde di costruttori specializzati: i carpentieri, i  muratori, gli scalpellini e gli artigiani. I manovali dei @8campi&di&lavoro  forniscono la forza lavoro, ma gli esperti delle gilde trasformano cumuli di  materiale grezzo nei più grandi e complessi edifici dell'antico Egitto, come le  piramidi, le @362sfingi, le @371mastaba, i @69templi&del&sole, i @368mausolei e  gli @392obelischi. Ciascun monumento richiede i servizi di una o più gilde di  costruttori. @PLe gilde di costruttori richiedono l'accesso a una strada e alla manodopera.  Le gilde dei carpentieri richiedono anche forniture di legno. Alle gilde degli  artigiani occorrono pittura e argilla (per gli stucchi) per aggiungere il tocco  finale alle camere di sepoltura. I muratori e gli scalpellini attendono l'arrivo  dei materiali grezzi presso il cantiere di costruzione. @PA causa del fracasso, i cittadini non desiderano vivere nei pressi delle gilde  di costruttori. @L@LPer saperne di più su questi costruttori specializzati dell'antico Egitto,  consulta le sezioni su @386muratori, @385scalpellini, @389carpentieri e  @472artigiani."
        }
    }
    message_building_brickworks {
        id: 364,
        
        size [30, 20]
        title {
            text: "Fabbrica di mattoni",
        }
        content {
            text: "Le fabbriche di mattoni trasformano l'@92argilla e la @89paglia in  mattoni. I mattoni sono usati per costruire diversi tipi di monumenti e possono,  inoltre, essere @47esportati con profitto. @PQuando una fabbrica di mattoni ha manodopera e l'accesso a una strada, per  funzionare le occorrono ancora delle forniture di materiali grezzi. Le fabbriche  di mattoni richiedono paglia e argilla. La paglia è prodotta nelle  @89fattorie&di&grano e l'argilla viene estratta nelle @92cave&d'argilla. In  alternativa, entrambi i materiali grezzi possono essere @47importati.  @PQuando una fabbrica di mattoni sta producendo, puoi vedere gli artigiani al  lavoro in cortile. Quando è pronto un carico di mattoni, questo viene consegnato  a un @4deposito&merci. @PLe fabbriche di mattoni sono @56indesiderabili. @L@LClicca @390qui per ulteriori informazioni sui mattoni nell'antico Egitto."
        }
    }
    message_building_warship {
        id: 365,
        
        size [30, 20]
        title {
            text: "Nave da guerra",
        }
        content {
            text: "Le navi da guerra sorvegliano gli specchi d'acqua, speronando o  colpendo le navi nemiche che intendono arrecare danno alla città. Le navi da  guerra possono attaccare i soldati sulle rive con le armi da lancio, purché  siano entro la loro portata. Le navi da guerra sono ormeggiate nei  @356moli&delle&navi&guerra. Puoi distinguerle dalle navi da trasporto truppe per  la mancanza della cabina posteriore e la forma più affusolata. @L@LPriorità d'attacco @LIndipendentemente dagli ordini che impartisci a una nave da guerra, il suo  capitano esaminerà sempre le seguenti situazioni prima di attaccare il nemico.  Ecco le priorità del capitano, in ordine di importanza: @L@LNavi da trasporto truppe cariche di soldati @LIl capitano sa che la sua missione fallisce se lascia che i soldati  raggiungano la terraferma. Se nelle acque della città ci sono delle navi da  trasporto truppe cariche di soldati, egli le attaccherà per prime, prima che gli  invasori possano sbarcare. @L@LNemici sbarcati sulla spiaggia @LSe il capitano non riesce a impedire lo sbarco dei nemici, navigherà vicino  alla riva per colpire con le frecce tutti i soldati possibili appena sbarcati. @L@LNavi da guerra @LLe navi da guerra nemiche costituiscono la terza priorità. Se non ci sono navi  da trasporto truppe cariche di soldati o soldati sulle rive, il capitano  cercherà di speronare le navi da guerra nemiche presenti. @L@LNavi da trasporto truppe vuote  @LLe navi da trasporto truppe vuote sono l'ultima priorità del capitano. Egli le  assalirà se non c'è niente altro da attaccare. @L@LIl tuo capitano reagisce velocemente a ogni cambio di situazione.  Abbandonerà qualsiasi scontro, se si sviluppa una nuova situazione di maggiore  priorità. Ad esempio, se mentre sta attaccando una nave da guerra arriva una  nave da trasporto truppe carica di soldati, egli abbandonerà lo scontro con la  nave da guerra per attaccare il trasporto appena giunto.  @L@LOrdini alla nave da guerra @LPuoi impartire ordini alla nave da guerra cliccandoci sopra con il pulsante  destro del mouse. Le navi da guerra possono eseguire questi ordini: @L@LMantieni posizione @LCon questo ordine, la nave da guerra non si muove dalla posizione in cui si  trova. Si difenderà voltandosi per affrontare le navi da guerra nemiche  (minimizzando i danni di eventuali speronamenti) e attaccherà i nemici entro la  sua portata con le armi da lancio. Se più navi da guerra sono allineate e  rispondono allo stesso ordine, formano una barriera con l'intento di fermare il  nemico. @L@LAttacca nemici vicini @LCon questo ordine, la nave da guerra attacca i nemici che si trovano entro un  raggio limitato dalla sua posizione.   @L@LCerca e distruggi tutti i nemici @LCon questo comando, la nave da guerra sorveglia le acque e cerca eventuali  nemici da attaccare. @L@LRiparazione @LSe la nave da guerra riporta danni in seguito a uno scontro, cliccando su  questo pulsante essa ritornerà al cantiere navale per le riparazioni. Quando il  cantiere termina le riparazioni, la nave tornerà al suo molo. Se la nave è  seriamente danneggiata, il suo capitano si dirigerà al cantiere di sua  iniziativa. I cantieri navali richiedono il legno per effettuare le riparazioni. @L@LRitorna al molo @LCliccando su questa opzione, la nave da guerra ritorna al suo molo. @L@LPer ordinarle di muoversi, clicca su di essa e, quindi, sulla sua  destinazione. Quando arriva a destinazione, essa eseguirà l'ultimo ordine  impartito. Se clicchi su un nemico, la nave da guerra lo inseguirà e lo  attaccherà finché non l'avrà distrutto o non sarà fuori portata. @L@LClicca @184qui per ulteriori informazioni sui combattimenti nell'antico  Egitto."
        }
    }
    message_building_festival_square {
        id: 366,
        
        size [30, 20]
        title {
            text: "Piazza delle festività",
        }
        content {
            text: "Prima di poter celebrare una festività (vedi la sezione @51religione  per ulteriori informazioni sulle festività), la tua città deve avere una piazza  delle festività. Questa deve trovarsi su un incrocio, ma non richiede mano  d'opera. Ogni città può avere una sola piazza delle festività, che rende molto  @56desiderabile il quartiere. @PQuando non vi è alcuna festività in corso, la piazza è praticamente deserta,  anche se non influenza in alcun modo il traffico sulle strade su cui è  costruita. Quando la festività inizia, la gente di tutta la città si raduna qui  per festeggiare.   @PGli antichi egizi indivano festività per celebrare molti eventi. Clicca  @393qui per saperne di più."
        }
    }
    message_figure_transport_ship {
        id: 367,
        
        size [30, 20]
        title {
            text: "Nave da trasporto truppe",
        }
        subtitle {
            text: "Nave da trasporto truppe",
        }
        content {
            text: "Le navi da trasporto truppe trasportano l'esercito attraverso fiumi o mari fino alle terre più lontane. Qualsiasi compagnia può imbarcarsi su un trasporto, ma ogni trasporto può imbarcare una sola compagnia alla volta. Le navi da trasporto truppe sono ormeggiate ai @357moli&delle&navi&da&trasporto&truppe. Puoi distinguerle dalle navi da guerra per la presenza della cabina posteriore e la loro foggia particolare. @L@LOrdini alle navi da trasporto truppe @LAlle navi da trasporto truppe puoi impartire ordini speciali. Per muovere un trasporto da un punto a un altro, clicca su di esso e, quindi, sul punto di arrivo. Clicca su un trasporto truppe con il pulsante destro del mouse per impartirgli uno dei seguenti ordini: @L@LMantieni posizione @LCon questo comando la nave da trasporto truppe rimane dov'è. Se viene attaccata, il capitano ruoterà la nave per ridurre i danni, ma non la sposterà per evitare l'attacco. Questa opzione deve essere usata con molta cautela, perché le navi da trasporto truppe non sono equipaggiate per difendersi al meglio.   @L@LEvita nemici @LLe navi da trasporto truppe, soprattutto quelle cariche di soldati, sono preziose e vulnerabili. Clicca sul pulsante Evita nemici per concedere al suo capitano il massimo della libertà per evitare gli attacchi. Il capitano della nave, così, cercherà sempre di schivare i nemici, a meno che non gli ordini diversamente. @L@LImbarca/Sbarca @LPer imbarcare una compagnia di soldati sulla nave da trasporto, clicca prima sul pulsante Imbarca, poi sulla compagnia di soldati che vuoi trasportare via acqua. I soldati saliranno a bordo della nave e questa mostrerà lo stendardo della compagnia. Quando clicchi su una nave da trasporto truppe con il pulsante destro del mouse, compariranno le informazioni sulla compagnia imbarcata. @PPer riportare i soldati sulla spiaggia, clicca su Sbarca; poi, sposta il puntatore sul luogo in cui vuoi posizionare la compagnia. @PL'opzione Imbarca/Sbarca cambia stato secondo la presenza o meno di soldati a bordo.   @L@LRiparazione  @LSe la nave da trasporto truppe è danneggiata, clicca sul pulsante Riparazione per farla ritornare al @82cantiere navale. Se lo scafo della nave è seriamente danneggiato, il suo capitano porterà la nave al cantiere di sua iniziativa. I cantieri navali richiedono il legno per effettuare le riparazioni. @L@LRitorna al molo @LClicca su questo pulsante per far tornare la nave da trasporto truppe al suo @357molo."
        }
    }
    message_building_mausoleum {
        id: 368,
        
        size [30, 20]
        title {
            text: "Mausoleo",
        }
        content {
            text: "I mausolei sono grandi tombe usate per seppellire i Faraoni e i  nobili. @PPer costruire un mausoleo, occorrono forniture di arenaria e legno, oltre ai  servizi di almeno una @363gilda&dei&carpentieri, una @363gilda&degli&scalpellini  e un @8campo&di&lavoro. @PPer posizionare un mausoleo, occorre prima una quantità di arenaria  sufficiente conservata nei @4depositi&merci della città. Se la quantità è  sufficiente, puoi selezionare la voce Mausoleo dall'elenco Strutture religiose:  Monumenti. Posiziona il mausoleo usando come guida il colore della sua impronta  (se è tutta verde, il luogo è adatto alla struttura; se ci sono dei quadrati  rossi, sul terreno ci sono ostacoli che ne impediscono il posizionamento).  Quando hai scelto il luogo per l'edificio, i manovali dei campi di lavoro  arriveranno a liberare il terreno e a porre le fondamenta. @PQuando le fondamenta sono a posto, gli scalpellini inizieranno il loro lavoro.  Ogni volta che un deposito merci accumula quattro blocchi di arenaria, i  manovali li caricheranno sulle slitte e li traineranno al cantiere. Gli  scalpellini posizionano le pietre fino al completamento del primo livello. Poi,  i carpentieri installano le rampe cosicché gli scalpellini possano lavorare al  secondo piano del mausoleo. Quando anche il secondo piano è terminato, il  mausoleo è finito. @L@LPuoi accedere a ulteriori informazioni su queste tombe cliccando @396qui."
        }
    }
    message_figure_construction_foreman {
        id: 369,
        
        size [30, 20]
        title {
            text: "Capo cantiere",
        }
        content {
            text: "Quando inizia la costruzione di un monumento, il capo cantiere ti  fornisce un rapporto dettagliato sull'avanzamento lavori. Egli tiene traccia di  tutto il materiale occorrente per completare il monumento. Se la costruzione non  procede come dovrebbe, egli può spiegarti il motivo. Per visitare il capo  cantiere, clicca sul cantiere con il pulsante destro del mouse."
        }
    }
    message_building_monument_construction {
        id: 370,
        
        size [30, 20]
        title {
            text: "Costruzione dei monumenti",
        }
        content {
            text: "Per completare con successo la maggior parte delle missioni, devi  costruire almeno un monumento. Alcune missioni richiedono la costruzione di più  monumenti. Puoi costruire i monumenti nell'ordine che preferisci. @PPer la maggior parte dei monumenti, i lavoratori delle  @363gilde&dei&costruttori attendono presso il cantiere che i manovali dei  @8campi&di&lavoro consegnino il materiale necessario dopo averlo prelevato dai  @4depositi&merci. I manovali percorreranno il cammino necessario per raggiungere  il cantiere. La @362sfinge e l'@372obelisco si costruiscono in modi leggermente  differenti dagli altri monumenti. @G75 @PI lavoratori della tua città possono lavorare a più di un monumento  contemporaneamente e tu potresti essere tentato di costruirne più di uno in uno  stesso momento. Ma fai attenzione, perché un ragionamento del genere non è poi  così saggio. L'inefficienza può causare dei notevoli rallentamenti, se gli  @363scalpellini e i manovali non riescono a coordinare i loro sforzi. I manovali  potrebbero consegnare i blocchi da costruzione presso un cantiere, mentre gli  scalpellini li attendono, senza nulla da fare, in un altro cantiere.   @PUna situazione del genere deprime il tuo @373supervisore&dei&monumenti, ma  riconciliare gli ordini inflessibili dei manovali con il carattere indipendente  degli scalpellini è un compito estremamente arduo. È dunque meglio evitare un  conflitto simile, ordinando la costruzione dei monumenti in modo sequenziale,  invece che in contemporanea. @PData la loro immane grandezza, alcuni monumenti possono risultare molto  difficili da posizionare in città. Per i monumenti più grandi, non riuscirai  neppure e vederne l'impronta intera in un colpo solo. @PPer inquadrare la posizione di un monumento, premi il tasto 'M'. L'impronta  del monumento si congelerà nel posto scelto e tu potrai spostare la visuale per  la città come al solito. Per posizionare il monumento nel luogo scelto, sempre  che sia adatto, clicca con il pulsante del mouse. Per continuare a cercare un  luogo adatto,premi nuovamente il tasto 'M'. L'impronta del monumento riprenderà  a seguire lo spostamento del puntatore. @PIn aggiunta, alcuni monumenti devono essere costruiti dentro le rupi. Questi monumenti sono @492Abu&Simbel e le @478Tombe&Reali. @PPer ulteriori informazioni sui monumenti, consulta le sezioni specifiche  dedicate a ciascuno: sono elencate nel menu Aiuto. @L@LPer ulteriori informazioni sulla storia dei monumenti, clicca su uno dei seguenti collegamenti: @391Sfinge, @392Piramidi, @394Mastaba, @493Abu&Simbel, @481Biblioteca&di&Alessandria, @482Caesareum, @475Valle&dei&Re o @396altri&monumenti."
        }
    }
    message_building_mastaba {
        id: 371,
        
        size [30, 20]
        title {
            text: "Mastaba",
        }
        content {
            text: "Le mastaba sono splendide tombe costruite per i nobili. A volte puoi  scegliere la mastaba come luogo del tuo eterno riposo. @PPer costruire una mastaba, ti occorrono molti @364mattoni e i servizi della  @363gilda&dei&muratori. Ti occorreranno anche i manovali dei @8campi&di&lavoro. @PLa prima fase della costruzione è la scelta di un luogo appropriato. Se  l'impronta della mastaba è verde, il luogo è adatto; se contiene dei quadrati  rossi, alcuni ostacoli del terreno ne impediscono la costruzione in quel luogo.  Clicca con il pulsante del mouse quando l'impronta è completamente verde e la  posizione della mastaba sarà fissata. Gli angoli della costruzione saranno  contrassegnati con dei paletti. @PDopo aver designato il posto, i muratori e i manovali iniziano il loro lavoro.  I manovali trainano slitte cariche  di mattoni e i muratori li posano con grande perizia. @PIl defunto ha bisogno di molte cose nei campi di canne, quindi dovrai  rifornire la mastaba con @374arredi&funebri. Il tuo  @373supervisore&dei&monumenti ti dirà quali beni sono necessari. Consulta il  @369capo&cantiere per un aggiornamento sullo stato dei lavori. Clicca @370qui  per ulteriori informazioni sulla costruzione dei monumenti. @L@LClicca @394qui per conoscere meglio le mastaba dell'antico Egitto."
        }
    }
    message_building_obelisk {
        id: 372,
        
        size [30, 20]
        title {
            text: "Obelisco",
        }
        content {
            text: "Gli obelischi simboleggiano i raggi del sole e sui loro fianchi sono  scolpite le memorie delle più grandi imprese. @PGli obelischi si costruiscono con grandi quantità di @95granito e tutto il  granito necessario alla costruzione di un obelisco deve già essere presente nei  @4depositi&merci prima ancora di poter posizionare il monumento. @PSposta il puntatore sulla mappa per scegliere il luogo in cui sorgerà  l'obelisco. Se vedi un'impronta dell'obelisco completamente verde, il luogo è  adatto; se l'impronta contiene dei quadrati rossi, alcuni ostacoli del terreno  ne impediscono la costruzione in quel punto. @PDopo aver scelto un luogo idoneo, il granito viene portato al cantiere.  Quindi, i carpentieri della @363gilda&dei&carpentieri costruiscono le  impalcature intorno al monumento e gli @363scalpellini arrivano al monumento per  scolpirne i fianchi. Per costruire un obelisco, non ti occorrono i servizi dei  manovali. @PClicca sul monumento con il pulsante destro del mouse per visitare il  @369capo&cantiere. Egli ti aggiornerà sullo stato dei lavori del monumento. @L@LGli obelischi si ergono contro il cielo da migliaia di anni. Clicca @397qui  per ulteriori informazioni su questo antico monumento."
        }
    }
    message_overseer_monuments {
        id: 373,
        
        size [30, 20]
        title {
            text: "Supervisore dei monumenti",
        }
        content {
            text: "Il tuo supervisore dei monumenti può dirti cosa impedisce l'inizio  dei lavori. Inoltre, gestisce l'invio degli @374arredi&funebri ovunque siano  necessari. Per ottenere un rapporto sull'andamento della costruzione, clicca sul  monumento con il pulsante destro del mouse per comunicare con il capo  cantiere."
        }
    }
    message_burial_provisions {
        id: 374,
        
        size [30, 20]
        title {
            text: "Arredi funebri",
        }
        content {
            text: "Per essere certi che il defunto abbia tutto ciò di cui ha bisogno  nell'aldilà, devi rifornire le tombe di arredi funebri, gli oggetti che il  defunto usava quando era in vita. A volte, ti può capitare di dover fornire dei  materiali per la costruzione di richieste speciali, come un'arca funebre o un  sarcofago. I monumenti non sono completi finché non sono riforniti con gli  arredi funebri. Il @373supervisore&dei&monumenti ha l'elenco di tutti gli  oggetti necessari e le relative quantità. Quando sei pronto a inviarli, ordina  al supervisore dei monumenti di inviare gli oggetti alla tomba. @PNon occore che tu abbia tutti gli oggetti pronti nei @4depositi&merci prima di  inviarli. Puoi mandarli in diverse spedizioni parziali fino al raggiungimento  del totale. @PLa tua città potrebbe aver bisogno di @47importare alcuni arredi funebri. @L@LGli antichi egizi seppellivano molti oggetti insieme ai loro morti. Clicca  @395qui per sapere quali oggetti erano necessari per la vita nell'aldilà."
        }
    }
    message_building_stepped_pyramid {
        id: 375,
        
        size [30, 20]
        title {
            text: "Piramide a gradoni",
        }
        content {
            text: "Le piramidi a gradoni, le prime costruite in Egitto, sono gigantesche  scalinate verso il sole. Sono realizzate completamente con @95pietra&normale,  anche se il legno è indispensabile per erigere le rampe necessarie a raggiungere  i livelli più alti della piramide. Per costruire le rampe e posare le pietre, ti  occorrono i servizi della @363gilda&dei&carpentieri e della  @363gilda&degli&scalpellini. I manovali sono, inoltre, necessari per trainare le  slitte cariche di pietre fino al cantiere. Quando i @4depositi&merci contengono  almeno quattro blocchi di pietra e gli scalpellini sono pronti, i manovali  iniziano il loro faticoso cammino verso il cantiere del monumento. @PLe piramidi a gradoni sono di cinque diverse dimensioni: piccole, medie,  grandi, complesso di piramidi o grande complesso di piramidi. Visita il  @369capo&costrutore e il @373supervisore&dei&monumenti per ulteriori  informazioni. Anche la sezione sulla @370costruzione&dei&monumenti potrebbe  risultarti utile. @L@LClicca @392qui per conoscere meglio l'innovazione del famoso consigliere  Imhotep: la piramide a gradoni."
        }
    }
    message_osiris_sebek_min {
        id: 376,
        
        size [30, 20]
        image {
            id: 42,
            pos [15, 15]
        }
        title {
            text: "Osiride, Sebek e Min",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Il ruolo religioso di Osiride cambiò con il passare dei millenni.  Insieme a sua moglie e sorella Iside e suo fratello Seth, era uno dei primi dei  e membro dell'Eanneade (si veda @399religione per ulteriori informazioni  sull'Eanneade).  @L@LIl mito di Osiride lo lega all'agricoltura, al Nilo e alle pratiche  funerarie. Ra-Atum diede a Osiride il governo dell'antico Egitto. Osiride sposò  sua sorella, Iside, e insegnò alle genti molte cose,tra cui la più importante,  l'arte dell'agricoltura. Dopo aver istruito gli Egizi, Osiride abbandonò  l'Egitto per civilizzare il resto del mondo, lasciando il suo posto a Iside.  Iside governò bene in sua assenza, ma al ritorno di Osiride, suo fratello Seth  tramò contro di lui. Seth invitò Osiride a un banchetto sontuoso durante il  quale gli mostrò uno splendido feretro. Egli offrì il feretro a chiunque,  provandolo, lo trovasse adatto alle proprie dimensioni. Quando Osiride entrò nel  feretro, Seth chiuse il coperchio e scagliò la bara nel Nilo. Iside riuscì a  ripescare la bara dal Nilo, ma Seth se ne accorse e fece Osiride a pezzi. Iside,  pianse disperata e le sue lacrime causarono l'inondazione. Alla fine, Iside  raccolse i pezzi di Osiride tranne i genitali, che erano stati mangiati dal  pesce oxyrhynchus. Iside bendò Osiride con la tela, trasformandolo in una specie  di mummia. Per motivi facilmente immaginabili, agli Egizi non era permesso  mangiare il pesce oxyrhynchus. Infine, Osiride divenne dio dell'aldilà e supremo  giudice che concedeva l'ingresso all'altro mondo. @L@LSebek, il dio coccodrillo, era un dio della fertilità che era venerato  principalmente nel Faiyum, anche se era conosciuto in tutto l'Egitto. Il suo  nome significa 'protettore'. Anche Min, dio della rigenerazione, era associato  alla fertilità maschile ed era adorato in tutto l'Egitto."
        }
    }
    message_ra_maat_horus {
        id: 377,
        
        size [30, 20]
        image {
            id: 18,
            pos [15, 15]
        }
        title {
            text: "Ra, Ma'at e Horus",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Ra è considerato il capo degli dei durante tutta la storia  dell'Egitto. Come padre di tutti gli dei nell'Eanneade, era il dio creatore ed  era associato al sole. @L@LMa'at era le dea della giustizia, associata ai concetti di verità e ordine.  La piuma di struzzo che porta sul capo è quella utilizzata per pesare il cuore  prima che chiunque possa entrare nell'aldilà. @L@LHorus era più precisamente associato ai Faraoni. Era il figlio di Iside e  Osiride e vendicò la morte di suo padre denunciando Seth. Horus era  rappresentato da un falco."
        }
    }
    message_ptah_amon_thoth {
        id: 378,
        
        size [30, 20]
        image {
            id: 3,
            pos [15, 15]
        }
        title {
            text: "Ptah, Amon e Thoth",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Ptah, il dio degli artigiani, era associato ai Faraoni di Memphis, i  primi a riunificare l'Egitto (si veda @399religione per ulteriori informazioni  sui Faraoni di Memphis e le credenze religiose). Era particolarmente venerato  dagli artigiani di Deir El-Medina, che costruirono le tombe nella Valle dei Re e  Valle delle Regine. @L@LAmon era il dio sole, in particolare associato all'alba. Divenne molto  importante durante la XII Dinastia, quando i re tebani assunsero il controllo  dell'Egitto. @L@LThoth era il dio della saggezza e dell'istruzione, considerato lo scriba  degli altri dei. Era particolarmente associato alla città di Hermopolis."
        }
    }
    message_seth_anubis_sekhmet {
        id: 379,
        
        size [30, 20]
        image {
            id: 117,
            pos [15, 15]
        }
        title {
            text: "Seth, Anubis e Sekhmet",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Seth, fratello di @376Osiride, era il dio della distruzione. In  origine, Seth era il protettore del Basso Egitto. Quando l'Alto Egitto divenne  più importante, il suo patrono, @377Horus, ebbe il sopravvento e Seth assunse  connotazioni negative. @L@LAnubis, dio della morte, era il dio imbalsamatore. Simboleggiato dallo  sciacallo, Anubis era il protettore dei morti. @L@LSekhmet era la dea della guerra, raffigurata con la testa di leone. Moglie  di Ptah, ella distruggeva ciò che lui creava. Gli Egizi la veneravano nella  speranza di pacificarla così che non scatenasse la sua furia."
        }
    }
    message_bast_isis_hathor {
        id: 380,
        
        size [30, 20]
        image {
            id: 28,
            pos [15, 15]
        }
        title {
            text: "Bast, Isis e Hathor",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Bast, una donna dalla testa di gatto o una leonessa, era la dea della  casa e dei gatti, del fuoco e delle donne incinte. Ella proteggeva la casa con  mezzi pacifici o più aggressivi. Era anche la dea patrona di Bubastis. @L@LIside, moglie di @376Osiride e madre di @377Horus, mise insieme il corpo  fatto a pezzi di Osiride. Per questo motivo, era ritenuta la dea della  guarigione. Era rappresentata come una donna, spesso in compagnia di suo figlio. @L@LHathor era la dea della gioia, dell'amore e delle festività. Rappresentata  con una mucca, era la dea protettrice di Dendera, Memphis, Cusae e Gebelein."
        }
    }
    message_history_malaria {
        id: 381,
        
        size [30, 20]
        image {
            id: 118,
            pos [15, 15]
        }
        title {
            text: "Malaria",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La malaria era uno dei rischi della vita vicino alle paludi. La  malaria è causata da quattro parassiti diffusi dalla zanzara anofele, attiva  principalmente di notte. I sintomi della malaria sono la febbre, seguita da  dolori muscolari, sudorazione e stanchezza. Uno dei quattro parassiti può  portare a casi così gravi da causare la morte. @L@LPer evitare la possibilità di morsi fatali,e comunque fastidiosi, delle  zanzare, gli antichi egizi utilizzavano delle zanzariere sopra i letti. Erodoto,  storico greco, notò inoltre che gli Egizi più ricchi dormivano nelle torri,  credendo che le zanzare non potessero giungere a grandi altezze."
        }
    }
    message_history_jewelry {
        id: 382,
        
        size [30, 20]
        image {
            id: 33,
            pos [15, 15]
        }
        title {
            text: "Gioielleria",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli orafi prendevano le pietre preziose e fabbricavano collane,  cinture e altri tipi di ornamento. Per legare le collane, gli orafi prima  praticavano un foro nella pietra con un trapano a mano e poi vi facevano passare  un filo. Gli orafi erano anche in grado di usare gemme negli intarsi. @L@LDai dipinti sui muri tombali, pare che l'industria orafa impiegasse spesso  dei nani."
        }
    }
    message_history_hunting {
        id: 383,
        
        size [30, 20]
        image {
            id: 119,
            pos [15, 15]
        }
        title {
            text: "Caccia",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Rispetto al cibo derivato dalle coltivazioni e dall'allevamento, la  caccia contribuiva ben poco alle riserve di cibo. Eppure, era un diffuso  passatempo delle classi più agiate, e molti Faraoni davano sfoggio alle loro  abilità di cacciatori. Gazzelle, antilopi, ibex, buoi, pecore e struzzi erano le  prede principali, ma alcuni cacciavano anche iene, leoni e leopardi per  divertimento o, nel caso dei leopardi e dei leoni, per le pelli. I cacciatori  usavano arco e frecce, lance o giavellotti. @L@LGli Egizi erano anche appassionati di caccia agli animali lungo i corsi  d'acqua, come le oche e gli ippopotami. Gruppi di uomini cacciavano gli  ippopotami con lance speciali cui era agganciata una corda. Dopo aver colpito  più volte un ippopotamo, gli uomini lo trascinavano a riva con le corde. @L@LLe oche si cacciavano con bastoni da lancio, simili ai boomerang  australiani. Gli aiutanti, o altri membri della famiglia, raccoglievano la  selvaggina colpita. Gli uccelli venivano anche cacciati con delle reti distese  sui campi. La rete era punteggiata di bocconi di cibo adatto agli uccelli.  Quando questi arrivavano sulla rete, gli uomini la richiudevano e gli uccelli  restavano in trappola."
        }
    }
    message_history_priests {
        id: 384,
        
        size [30, 20]
        image {
            id: 120,
            pos [15, 15]
        }
        title {
            text: "Sacerdoti",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Una parte considerevole della popolazione egizia era costituita da  sacerdoti. Il loro ruolo si estendeva ben oltre le funzioni religiose. Dato che  l'Egitto era una teocrazia, i sacerdoti spesso assumevano cariche amministrative  e a volte anche giudiziarie. @L@LI sacerdoti si contraddistinguevano per la loro pulizia. Prima di entrare  nel tempio, essi effettuavano un bagno di purificazione e si rasavano il capo  per evitare di portare impurità. Secondo il dio servito, i sacerdoti non  potevano mangiare certi tipi di cibo; inoltre vestivano in modi particolari e  portavano sempre sandali. I sacerdoti di grado più elevato a volte si vestivano  con pelli di leopardo. @L@LIl loro primo dovere religioso era la cura e il nutrimento del proprio dio.  Ciascun tempio aveva una statua del dio patrono e ogni sacerdote del tempio  doveva fare in modo che il dio fosse sempre soddisfatto. Alcuni sacerdoti  avevano il compito di nutrire il dio, utilizzando il cibo donato come offerta  dai cittadini. Il dio si sarebbe così nutrito dell'essenza del cibo mentre i  preti avrebbero mangiato ciò che rimaneva. I sacerdoti purificavano il dio con  acqua, lo vestivano e cercavano di procurargli del divertimento. A volte, il dio  veniva portato all'esterno del tempio in processione per le strade cittadine (si  vedano le @393festività per ulteriori informazioni). @L@LI sacerdoti erano divisi in classi. Il più importante era il Gran Sacerdote,  chiamato anche Primo Profeta, che era nominato dal Faraone. Il Gran Sacerdote  era l'autorità assoluta all'interno del tempio e spesso fungeva da consigliere  per il Faraone. Sotto il Gran Sacerdote c'erano i suoi secondi, chiamati anche  Secondi Profeti, che supervisionavano attività particolari del tempio e dei suoi  dintorni, come i laboratori o le fattorie. Sotto di loro c'erano i sacerdoti  responsabili di funzioni all'interno del tempio, come le abluzioni del dio e il  suo divertimento. Per lo più i sacerdoti lavoravano a turni di un mese su tre."
        }
    }
    message_history_stonemasons {
        id: 385,
        
        size [30, 20]
        image {
            id: 121,
            pos [15, 15]
        }
        title {
            text: "Gilda degli scalpellini",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli scalpellini supervisionavano il lavoro nelle @193cave e la  costruzione delle @392piramidi o altri monumenti. Anche se sapevano  perfettamente come estrarre la pietra dalle cave, non erano loro a effettuare i  lavori più faticosi, ma solo i contadini e, a volte, gli schiavi. Gli  scalpellini erano solo dei supervisori. Oltre ai grandi progetti di costruzione,  gli scalpellini prestavano la propria esperienza anche per lavori più piccoli,  come la disposizione delle fondamenta di una casa."
        }
    }
    message_history_bricklayers {
        id: 386,
        
        size [30, 20]
        image {
            id: 122,
            pos [15, 15]
        }
        title {
            text: "Gilda dei muratori",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La posa dei mattoni non è molto cambiata nel corso dei millenni. Il  materiale è più o meno sempre lo stesso: @390mattoni e malta. Nell'antico  Egitto, la malta era costituita da una mistura di argilla, sabbia e paglia. I  muratori stendevano la malta con una cazzuola di legno e quindi disponevano i  mattoni. Per assicurarsi che i muri fossero dritti usavano fili a piombo."
        }
    }
    message_history_scribes {
        id: 387,
        
        size [30, 20]
        image {
            id: 21,
            pos [15, 15]
        }
        title {
            text: "Scribi",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli scribi, o sesh, erano presenti a tutti i livelli sociali e  curavano praticamente qualsiasi azione del governo. Gli antichi egizi annotavano  quasi tutto, e gli scribi erano gli unici in grado di assolvere tale compito.  Gli scribi annotavano l'ammontare delle tasse dovute da una certa persona,  registravano importazioni ed esportazioni e accompagnavano i soldati in  battaglia per tenere traccia degli eventi. Per i privati, gli scribi compilavano  documenti legali, come i testamenti, e leggevano o scrivevano le lettere  personali. @L@LGli strumenti dello scriba erano il papiro, una tavoletta con due impasti di  inchiostro (generalmente nero e rosso), un vaso d'acqua e dei pennelli di canna.  Lo scriba bagnava il pennello nell'acqua e quindi strofinava sulla pasta  d'inchiostro. Quindi scriveva sul papiro. @L@LGli scribi che sapevano tracciare i geroglifici erano ben pochi. I  geroglifici erano riservati ai monumenti e ai templi. Normalmente, nella vita di  tutti i giorni, si utilizzava una versione semplificata, chiamata ieratico.  @L@LLa lingua scritta consisteva di 700 segni e simboli modulari che  rappresentavano suoni e concetti. Le vocali non esistevano, quindi gli storici  possono solo cercare di indovinare come fossero pronunciate le varie parole."
        }
    }
    message_history_immigration {
        id: 388,
        
        size [30, 20]
        image {
            id: 123,
            pos [15, 15]
        }
        title {
            text: "Immigrazione",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Grazie allo straripamento del Nilo, l'Egitto poteva contare su  un'economia e una produzione di cibo abbastanza stabili. I paesi vicini lo  sapevano bene, e molti abitanti di quest'ultimi immigravano in Egitto. @L@LAlcuni immigranti giungevano in Egitto per commerciare. Alcuni scavi  archeologici hanno rivelato l'esistenza di insediamenti non egizi in alcune  città portuali, come Memphis. Questi mercanti sono raffigurati nelle tombe del  Medio e del Nuovo Regno. L'Egitto era meta anche di altri stranieri, come i  libici. Nella XII dinastia, i libici occupavano ormai vaste aree del delta  occidentale e parte di quello orientale. @L@LAltri erano giunti in Egitto con intenzioni tutt'altro che nobili. Gli  @181invasori spesso restavano in Egitto, anche dopo il crollo del potere che  avevano instaurato. Pare che molti di quelli rimasti godessero degli stessi  diritti degli Egizi, ed alcuni addirittura ricoprivano cariche governative."
        }
    }
    message_history_carpenters {
        id: 389,
        
        size [30, 20]
        image {
            id: 124,
            pos [15, 15]
        }
        title {
            text: "Carpenteria",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "I carpentieri fabbricavano molti oggetti necessari agli Egizi. Il  @192legno autoctono era scarso, quindi i carpentieri dovevano essere molto  efficienti con il poco legno a loro disposizione. Veniva utilizzato anche il  legno d'importazione, ma era costoso e quindi disponibile solo per i cittadini  più ricchi. @L@LI carpentieri erano equipaggiati con asce, seghe e azze per trasformare i  tronchi in assi utilizzabili. Con le asce, i carpentieri tagliavano i rami dai  tronchi e spezzavano il legno per farne delle travi. Le seghe si usavano per  ricavare le assi, e le azze per rifinirle. @L@LTra i prodotti finiti citiamo le casse, i letti, le porte e gli stipiti, le  sedie e, soprattutto, i sarcofagi. Per tenere insieme i vari pezzi, al posto dei  chiodi venivano usati dei pioli. Alcuni prodotti erano davvero oggetti d'arte,  con intagli e intarsi che decoravano la superficie. @L@LI carpentieri erano necessari anche per costruire le case più grandi. I  soffitti delle case più ricche erano spesso supportati da colonne in legno  decorato. @L@LLa normale carpenteria non è cambiata molto nel corso della storia egizia, e  neppure gli strumenti utilizzati. L'innovazione principale è stata forse il  trapano. Durante il Nuovo Regno, si usava un trapano ad arco per praticare i  fori dove poi si inserivano i pioli."
        }
    }
    message_history_bricks {
        id: 390,
        
        size [30, 20]
        image {
            id: 125,
            pos [15, 15]
        }
        title {
            text: "Mattoni",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Per gli antichi egizi, i mattoni erano il materiale di costruzione  ideale. Dato che non conducevano calore, le case in mattoni restavano più  fresche durante le estati impietose. I mattoni si fabbricavano con argilla e  paglia. L'argilla veniva inumidita, mischiata alla paglia e quindi immersa in  acqua. Qui la paglia iniziava a sciogliersi, producendo una secrezione che  poteva tenere insieme i mattoni. I mattoni erano poi lasciati ad asciugare al  sole. Quando erano pronti, i @386muratori potevano iniziare il loro lavoro."
        }
    }
    message_history_sphinx {
        id: 391,
        
        size [30, 20]
        image {
            id: 8,
            pos [15, 15]
        }
        title {
            text: "Sfinge",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La sfinge, nell'antico Egitto associata al dio Amun, aveva il corpo  di un leone e la testa di un re. In Egitto vi erano molte sfingi, ma la più  famosa di tutte è la Grande Sfinge di Giza.  @L@LCostruita intorno al 2500 a.C., la Grande Sfinge, seduta su una vecchia cava  di pietra, pare essere di guardia alla piramide di Khefren. Si crede che il suo  viso sia quello di Khefren stesso. La sfinge è lunga circa 60 metri e alta 20. È  stata scolpita in roccia arenaria. @L@LLa sfinge è rimasta sepolta nella sabbia per gran parte della sua esistenza.  La leggenda dice che Thutmose IV, prima di diventare Faraone, stava cacciando  nella zona della sfinge quando cadde addormentato proprio sul luogo dove si  trovava. Nel sonno, la sfinge disse a Thutmose che se l'avesse dissepolta,  sarebbe diventato Faraone. Thutmose seguì le istruzioni della sfinge e divenne  Faraone nel 1425 a.C.. Il Faraone trascrisse la storia su una stele che piantò  tra le zampe della sfinge stessa. @L@LLa Grande Sfinge si ritrovò nuovamente seppellita finché non venne  riscoperta nel 1930. I vari tentativi di mantenere la sfinge conservata al  meglio hanno dato risultati alterni."
        }
    }
    message_history_pyramids {
        id: 392,
        
        size [30, 20]
        image {
            id: 39,
            pos [15, 15]
        }
        title {
            text: "Piramidi",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Ormai sono secoli che ci si chiede come si costruivano le piramidi.  Tuttora sembra incredibile che gli antichi egizi, sprovvisti di moderni  verricelli, gru, ruspe e trattori abbiano costruito tali monumenti. @L@LLa costruzione di una piramide iniziava con un meticoloso progetto. Il  Consigliere, secondo in comando solo al Faraone, supervisionava i lavori insieme  all'Architetto Reale (medjeh nesu, in antico Egizio) che si occupava del  progetto. L'Architetto Reale era responsabile della scelta del materiale e del  suo trasporto fino al cantiere. @L@LDopo aver scelto il luogo, gli astronomi determinavano l'asse nord-sud della  piramide. Quindi, alcuni assistenti segnavano i lati della futura piramide con  una corda speciale, così spessa che non si sarebbe ristretta tanto da vanificare  le attente misurazioni. Quindi si livellava il terreno, probabilmente  utilizzando dei canali pieni d'acqua per determinare eventuali pendenze. @L@LAl termine di tali lavori, la costruzione poteva iniziare. La cerimonia di  apertura era presieduta dal Faraone che segnava i quattro angoli della piramide  con dei picchetti, stendeva una corda tra questi, e posava un mattone  cerimoniale come prima pietra del monumento. @L@LA questo punto, entravano in gioco gli @385scalpellini e i @155manovali. Gli  scalpellini ricavavano le camere sotterranee, tra cui la camera di sepoltura.  Quando queste erano pronte, iniziava il faticoso compito di trasportare i  blocchi di pietra, alcuni pesanti fino a 2,5 tonnellate, fino al cantiere. I  blocchi erano trasportati su slitte, e per raggiungere le parti più alte della  piramide probabilmente si utilizzavano delle rampe. Oltre alle pietre grezze che  costituivano l'interno della piramide, la struttura era ricoperta di pietre  assai meglio rifinite. @L@LAlcune piramidi si ergevano solitarie, ma più spesso facevano parte di un  complesso più vasto. Il complesso di piramidi era adiacente a una valle dei  templi che si trovava vicino all'acqua o a campi coltivati. Dalla valle dei  templi, un camminamento portava al tempio funebre, situato a est della piramide. @L@LLa forma delle piramidi si è evoluta con il progredire delle tecniche di  costruzione e degli utensili a disposizione. La prima piramide, la Piramide a  Gradoni di Djoser, non presenta pareti rifinite. Costruita intorno al 2620 a.C.,  la piramide a gradoni è composta di una serie di blocchi quadrati disposti l'uno  sull'altro. La prima vera piramide è quella di Snofru, costruita intorno al 2550  a.C.. Uno strato esterno rifinito inglobava i gradoni della piramide, e questa  pratica venne presto adottata per tutte le piramidi. La piramide più grande è  quella di Khufu, che misura 230x230 metri ed è alta 146 metri. Una piramide  unica del suo genere è la Piramide Sghemba di Sneferu. L'angolazione dei lati  della piramide cambia a circa due terzi dell'altezza. Si crede che gli  architetti la ritenessero troppo pesante e incline al crollo. E dato che la  primissima piramide di Sneferu era crollata, probabilmente il Faraone accettò il  cambiamento al volo senza aver troppo da ridire."
        }
    }
    message_history_festivals {
        id: 393,
        
        size [30, 20]
        image {
            id: 126,
            pos [15, 15]
        }
        title {
            text: "Festività",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Le festività degli antichi egizi erano feste gioiose dove il cibo era  abbondante e la birra scorreva a fiumi. Le feste erano indette per diversi  motivi: per onorare un dio, per segnare il periodo del raccolto e per celebrare  la lunga vita del Faraone. Anche gli ultimi cinque giorni dell'anno egizio erano  giorni di festa, e durante tutto l'anno le festività non mancavano. @L@LEra durante le festività degli dei che i cittadini avevano accesso alle loro  divinità. Al centro di ogni celebrazione c'era la processione del dio. Durante  la festa, la statua del dio che risiedeva nel tempio, nascosta alla vista del  pubblico, veniva adornata e rivestita per essere esposta lungo le strade  cittadine, trasportata dai sacerdoti su una barca cerimoniale. I sacerdoti si  riposavano di quando in quando e in quei momenti venivano compiuti dei riti  religiosi. Durante il Nuovo Regno, i cittadini potevano interrogare gli dei  mentre i sacerdoti si riposavano. I sacerdoti si inchinavano se il dio  rispondeva positivamente oppure si muovevano indietro se la risposta era  negativa. Al termine della festa, il dio ritornava nella sua casa al tempio. @L@LA volte, gli dei compivano un lungo tragitto ed erano trasportati su una  barca vera. Ad esempio, durante la festività di opet, Amun viaggiava da Karnak a  Luxor, molto più a sud, e per effettuare il viaggio era trasportato lungo il  Nilo. Opet era una delle festività più allegre e durava da 11 a 27 giorni. @L@LSe il Faraone era abbastanza in salute da essere in carica per 30 anni, si  celebrava la festa di heb-sed. Celebrata ogni tre anni a partire dal trentesimo  anno di carica, la festività vedeva il Faraone impegnato in una corsa rituale  per dimostrare che era ancora in grado di governare. Alcuni Faraoni non  aspettavano 30 anni per celebrare la festa di heb-sed, ma la indicevano molto  prima. @L@LSenza dubbio, gli Egizi di tutte le estrazioni sociali erano ben lieti di  partecipare a una festività, in quanto si mangiava e beveva in abbondanza. Le  festività offrivano anche un periodo di riposo dalle fatiche quotidiane."
        }
    }
    message_history_mastaba {
        id: 394,
        
        size [30, 20]
        image {
            id: 127,
            pos [15, 15]
        }
        title {
            text: "Mastaba",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "I primi Faraoni del Vecchio Regno erano seppelliti sotto le Mastaba.  Le Mastaba coprivano il pozzo che portava alla camera mortuaria. All'inizio,  erano strutture basse, molto semplici, con poche iscrizioni, ma poi si  svilupparono in altre più grandi, complete di cappella. Le Mastaba precorrevano  le piramidi, e la Piramide a Gradoni di Djoser, probabilmente ha origine in tale  usanza."
        }
    }
    message_history_burial_provisions {
        id: 395,
        
        size [30, 20]
        image {
            id: 26,
            pos [15, 15]
        }
        title {
            text: "Arredi funebri",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Le tombe erano rifornite di tutto ciò che il deceduto poteva aver  bisogno nell'aldilà. Con il nome di arredi funebri si intendono utensili, cibo,  profumi, gioielli, strumenti musicali, trucco - praticamente tutto ciò che il  defunto usava in vita. Le tombe contenevano anche gli shabti, o 'risponditori'.  Queste statuette erano incluse nelle tombe nel caso in cui al defunto fosse  richiesto di effettuare un lavoro nell'aldilà. Lo shabti avrebbe fatto il lavoro  al posto del defunto."
        }
    }
    message_history_other_monuments {
        id: 396,
        
        size [30, 20]
        image {
            id: 1,
            pos [15, 15]
        }
        title {
            text: "Altri monumenti",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Oltre a @397obelischi, @394Mastabe, @392piramidi e @391sfingi,  nell'antico Egitto si erigevano anche altri monumenti. Tra questi ci sono i  mausolei e il Tempio del Sole.  @L@LNell'antico Egitto, il sole era il creatore della vita, e i templi del sole  abbondavano, soprattutto durante la V dinastia. I templi del sole più famosi  sono ad Abu Ghurab, a circa un chilometro a nord-est della Piramide di Sahure.  Qui si trovano due templi del sole, antichi teatri di sacrifici animali. @L@LI mausolei e le cappelle erano spesso costruiti sulle tombe per servire da  luoghi in cui le famiglie dei defunti potevano portare le loro offerte. Le  offerte assicuravano che il defunto continuasse a essere felice nell'aldilà.  Chiunque ne avesse la possibilità, costruiva tali cappelle per un membro della  famiglia e infatti i mausolei privati abbondano in tutto l'Egitto."
        }
    }
    message_history_obelisk {
        id: 397,
        
        size [30, 20]
        image {
            id: 17,
            pos [15, 15]
        }
        title {
            text: "Obelischi",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli obelischi erano associati al sole, del quale rappresentavano i  raggi o la terra primordiale sulla quale esso splendeva. Realizzati in granito e  ricchi di geroglifici, gli obelischi si trovavano all'esterno dei templi,  generalmente a coppie. @L@LLa forma dell'obelisco veniva realizzata nelle cave, e uno non ancora  terminato, ad Aswan, rivela molti particolari sulla tecnica di estrazione di un  blocco di pietra così grande. I manovali usavano dei magli di dolerite per  ricavare lentamente la forma desiderata. L'obelisco di Aswan fu abbandonato  perché si aprì una crepa al centro del blocco. @L@LDopo l'estrazione dell'obelisco, nessuno sa con precisione come si facesse a  innalzarlo. Alcune prove tentate in epoca moderna, ma con mezzi antichi, hanno  tutte portato al fallimento."
        }
    }
    message_history_linen_and_weaving {
        id: 398,
        
        size [30, 20]
        image {
            id: 24,
            pos [15, 15]
        }
        title {
            text: "Tela e tessitori",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Realizzata con il @189lino, la tela era il prodotto tessile  predominante nell'antico Egitto. Alcuni tessuti erano realizzati con lana o  canapa, ma questi erano considerati di qualità inferiore. @L@LPer realizzare il tessuto, le fibre di lino dovevano prima essere divise in  fili. Seduti di fronte a montagne di lino, i filatori intrecciavano le fibre e  le avvolgevano in gomitoli. Poi, le trecce venivano attaccate ai telai per la  tessitura. @L@LGli Egizi usavano un telaio orizzontale disposto sul pavimento. Gli  artigiani tessevano con due fili paralleli. Due tessitori sedevano ai lati del  telaio e si scambiavano la navetta avanti e indietro. @L@LDurante il Nuovo Regno, apparve il telaio verticale, che consentiva le  operazioni su comodi sgabelli. @L@LLa maggior parte dei tessitori era costituita da donne; spesso facevano  parte dell'harem del Faraone."
        }
    }
    message_history_religion {
        id: 399,
        
        size [30, 20]
        image {
            id: 43,
            pos [15, 15]
        }
        title {
            text: "Religione",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La religione egizia offriva un corposo pantheon popolato di dei  principali e secondari. Le città, e persino gli individui, avevano un dio  patrono, e tale pratica determinava quali dei fossero più importanti. @L@LUna delle prime strutture religiose era l'Eanneade, o gruppo di nove dei.  Risalente alla città di Heliopolis, il primo dell'Eanneade era Atum, che si fuse  con Ra per diventare Ra-Atum. Ra-Atum, divinità maschile, riuscì comunque a  procreare due gemelli dotati di una sola mano, Shu e Tefnut. Shu era dio  dell'aria, e Tefnut era la dea dell'ordine mondiale. Shu e Tefnut ebbero quattro  figli: Iside, Osiride, Nephthys e Seth. A completare il gruppo, troviamo Horus,  figlio di Iside e Osiride. Ra si separò nuovamente da Atum e divenne il capo  dell'Eanneade. Tale struttura divina era predominante in epoca pre-dinastica, e  Ra continuò a essere uno degli dei principali degli antichi egizi  @L@LQuando Hor-Aha, spesso conosciuto come Menes, unificò l'Alto e il Basso  Egitto, il suo credo personale in Ptah, come dio creatore, modificò tale  struttura. Menes riteneva che gli dei dell'Eanneade fossero tutte manifestazioni  di Ptah. Eppure, Ra era ancora il dio predominante. @L@LUn'altra teoria ebbe origine nella città egizia di Hermopolis. Gli  hermopolitani credevano nell'Ogdoad, o gruppo di otto dei. Nell'Ogdoad, coppie  di dei, maschio e femmina, rappresentavano i diversi aspetti del mondo. Nun e  Naunent rappresentavano l'acqua, Huh e Hauhet rappresentavano l'infinito, Kuk e  Kauket erano gli dei dell'oscurità, infine Amon e Amaunet erano gli dei  dell'aria. @L@LNel Nuovo Regno, Amon sostituì Ra come divinità principale. Il predominio di  Amon continuò fino al Regno di Akhenaten. Akhenaten cercò di introdurre in  Egitto il monoteismo, affermando che Aten, personificazione del disco solare,  era l'unico dio. Durante il suo Regno, conosciuto come periodo Armana, Ahkenaten  chiuse i templi degli altri dei. Alla sua morte, però, il politeismo fu ben  presto reintrodotto, e i templi degli altri dei furono riaperti."
        }
    }
    message_mission_naqada {
        id: 400,
        type: 3,
        size [40, 30]
        title {
            text: "Naqada",

        }
        subtitle {
            text: "È nato un villaggio",

        }
        content {
            text: "@P Benvenuto nell'antico Egitto, terra dei Faraoni! Qui potrai vivere  da protagonista la storia di una tra le più grandi civiltà di tutti i tempi, una  civiltà capace di rimanere in auge per 15 secoli e 24 generazioni. Dovrai  guidare una famiglia, di generazione in generazione, partendo dalle sue radici  nell'Egitto preistorico e passando per l'alba della sua civiltà... fino alla  fondazione di un grandissimo impero... e quindi spingerti oltre. @PLa tua storia inizia sulle rive del Nilo, nella regione di Naqada, dove una  piccola confederazione di clan cerca di sopravvivere in un ambiente ostile. La  tua famiglia è a capo dell'insediamento e tu ne sei la guida."
        }
    }
    message_mission_thinis_2 {
        id: 401,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",

        }
        subtitle {
            text: "L'alba della civiltà",

        }
        content {
            text: "@PDopo molti anni e con il passare delle generazioni, la tua famiglia  si è spostata nella regione di Thinis, nell'Alto Egitto. Qui, un manipolo di  signori locali sta cercando di estendere la sua influenza sul Basso Egitto, e su  tutte le terre lungo il Nilo, per unificarle sotto una sola casata, con un solo  capo supremo. @PLa fondazione di Thinis, una città florida come non se ne sono mai viste,  aumenterà l'influenza della confederazione Thinita, così da avere un ruolo  fondamentale sul dominio del Basso Egitto, tale da suscitare invidia in tutte le  altre fazioni. Ciò significa offrire agli abitanti vari divertimenti, nonché  costruire templi magnificenti dedicati al culto delle divinità locali. @PPer costruire una città così importante occorrono molti soldi. A Thinis puoi  trovare ricchi depositi d'oro e l'estrazione di tale prezioso minerale deve  rappresentare la tua priorità assoluta."
        }
    }
    message_mission_buto_2 {
        id: 402,
        type: 3,
        size [40, 30]
        title {
            text: "Buto",

        }
        content {
            text: "I nobili Thiniti sono ancora in lotta per unificare le terre del Nilo  sotto un unico regnante. Per sostenere la loro causa, tutti sperano che tu  riesca a stabilire una fiorente comunità a Buto, nell'umida regione del Delta,  nel Basso Egitto, estendendo così la loro influenza lungo tutto il corso del  sacro fiume. Per supportare una popolazione più grande di quella di un  villaggio, devi imparare a sfruttare l'agricoltura. @LI contadini egizi hanno appena iniziato a sfruttare il suolo reso fertile  dalle inondazioni del Nilo per crescere ogni tipo di messi. Ma il Nilo, a volte,  può essere rischioso. I pericoli che si annidano nelle sue acque e sulle sue  rive sono molti, come i pericolosissimi coccodrilli, gli ippopotami e le zanzare  portatrici di malaria."
        }
    }
    message_mission_hierakonpolis {
        id: 403,
        type: 3,
        size [40, 30]
        title {
            text: "Hierakonpolis",

        }
        subtitle {
            text: "Il primo faraone",

        }
        content {
            text: "La gente che vive sulle rive del Nilo sta imparando a sopravvivere in  un ambiente ostile e, nel frattempo, un regnante locale di nome Narmer è asceso  al potere. Narmer regna su gran parte del territorio, ma la piena unificazione  dei due regni non è ancora compiuta. Per commemorare la propria ascesa al  potere, Narmer desidera che tu, con la tua famiglia, ti trasferisca per  governare una nuova città a Hierakonpolis. Questa città dovrà avere templi  dedicati a molte divinità e numerose aree di intrattenimento."
        }
    }
    message_mission_memphis {
        id: 404,
        type: 3,
        size [40, 30]
        title {
            text: "Memphis",

        }
        subtitle {
            text: "La fondazione della capitale",

        }
        content {
            text: "Dopo una lunga lotta, il re Hor-Aha è riuscito a unificare i regni  dell'Alto e del Basso Egitto, proclamandosi così faraone di tutto l'Egitto! Come  segno del suo potere assoluto e della sua dinastia, Hor-Aha ha ordinato la  fondazione di una imponente città capitale a Memphis, dalla quale possa  governare la sua nuova nazione. Data la fedeltà dimostrata dalla tua famiglia  per numerose generazioni, il faraone ti ha scelto come artefice della sua  splendida città. La capitale è il simbolo del Regno, quindi i suoi cittadini  devono godere di una qualità di vita superiore. A questo scopo, dovrai  commerciare con altre città del Regno e dovrai fornire una buona istruzione ad  almeno parte dei tuoi cittadini. Devi anche costruire una mastaba per i nobili  della città."
        }
    }
    message_mission_timna {
        id: 405,
        type: 3,
        size [40, 30]
        title {
            text: "Timna"
        }
        subtitle {
            text: "Una spedizione verso il Sinai"
        }
        content {
            text: "Un nuovo faraone, Den, è sul trono d'Egitto. Ora è molto preoccupato,  i nemici iniziano a minacciare i nostri confini e la nostra nazione non dispone  di rame a sufficienza per fabbricare le armi per le truppe. Il faraone Den ha  ordinato una spedizione mineraria nelle impervie terre del Sinai, oltre i nostri  confini e nel cuore del territorio beduino. La zona conosciuta col nome di Timna  è ricca di oro e rame, nonché preziosi turchesi, ma, per il resto, è  assolutamente arida. Le condizioni saranno molto dure e tu dovrai esportare  dall'Egitto diversi merci, forse anche cibo e tela. Il faraone richiede  frequenti spedizioni dal Sinai e ti chiederà denaro, rame, gemme e armi. Per  supportare la spedizione, puoi utilizzare le merci in surplus. Dovrai stare  sempre in guardia, dal momento che i Beduini del deserto sono avversari  formidabili e non permettono che degli stranieri invadano il loro territorio,  per non parlare del saccheggio delle loro risorse minerarie. @PPer alleggerire il fardello di tali condizioni di vita per i tuoi cittadini,  costruisci un padiglione presso un importante crocevia. I cittadini potranno  rilassarsi con i giocolieri e della buona musica e, se costruisci anche una  scuola di danza, questo nuovo tipo di spettacolo offrirà grande divertimento."
        }
    }
    message_mission_apollinopolis {
        id: 406,
        type: 3,
        size [40, 30]
        title {
            text: "Apollinopolis"
        }
        subtitle {
            text: "La flotta del faraone",
        }
        content {
            text: "Le truppe del faraone non hanno rivali in tutto il mondo conosciuto,  ma il nuovo faraone, Khasekhemwy della seconda dinastia, ora richiede una  potente flotta basata a Apollinopolis. Per dominare i mari, occorre una flotta  di navi da guerra, ma il legno è scarso in quanto il nostro clima permette  l'esistenza di ben poche zone boscose. Il legno di cedro può essere importato da  Byblos, nel territorio libanese a nord est. Per fortuna, le esportazioni del  nostro papiro possono compensare l'alto costo di tale legname."
        }
    }
    message_mission_abydos {
        id: 407,
        type: 3,
        size [40, 30]
        title {
            text: "Abydos",
        }
        subtitle {
            text: "La sfida dei mari",

        }
        content {
            text: "Abydos, il luogo dove sono sepolti i nostri padri, è diventato una  grande necropoli costellata di sacre tombe. Ora, molti nobili desiderano  eleggerlo come loro ultimo luogo di riposo. Per onorarli, il nuovo faraone  Khasekhemwy della seconda dinastia ha ordinato la costruzione di tre sacre tombe  mastaba (una più grande delle altre due) per la nobiltà del luogo. @L@LIl faraone ha anche richiesto la costruzione di una potente flotta di stanza  ad Apollinopolis. Anche Abydos deve fornire una piccola flotta di navi da  guerra, cosicché le nostre spiagge restino assolutamente sicure. Ciò non sarà  facile, dal momento che il legno è scarso, in quanto il nostro clima permette  l'esistenza di poche aree boscose. Il legno di cedro può essere importato da  Byblos, nel territorio libanese a nord est. Per fortuna, le esportazioni del  nostro papiro possono compensare l'alto costo di tale legname."
        }
    }
    message_mission_selima {
        id: 408,
        type: 3,
        size [40, 30]
        title {
            text: "Selima",

        }
        subtitle {
            text: "La via dell'Africa",

        }
        content {
            text: "@PÈ stato annunciato un nuovo faraone, Nebka, fondatore della terza  dinastia di regnanti egizi. Nebka ha conferito all'Egitto un'ottima  organizzazione, ordinando la divisione del Regno in distretti, o 'nome',  ciascuno governato da un signore chiamato 'Nomarca'. Anche se il sistema può  apparire rigido, l'Egitto è cresciuto e continua a prosperare, con ottimi  risultati anche nei campi dell'architettura e dell'arte.  @L@PLe carovane di  mercanti, in viaggio di oasi in oasi nel cuore del territorio africano, hanno  fornito beni esotici, alcuni rari e preziosi, tenuti in gran conto dalla nostra  gente. Sfortunatamente, queste carovane sono continuamente attaccate dai  guerrieri libici e anche dai Beduini del deserto orientale. Per rendere sicure  le vie commerciali, il faraone Nebka desidera che tu stabilisca una postazione  militare nell'Oasi di Selima, crocevia delle carovane, ben oltre i confini del  nostro Regno.   @L@PLì potrai trovare del legname adatto alla costruzione delle navi, da vendere  per ricavare i fondi necessari alla stazione militare. Per forgiare le armi,  puoi ottenere del rame dalle nuove miniere di Timna, nel territorio del Sinai. @L@PDall'Oasi di Selima, puoi importare ebano della nazione africana di Kerma.  Quando avrai stabilito l'avamposto militare, da qui potrai fornire l'ebano a  tutte le città del Regno."
        }
    }
    message_mission_elephantine {
        id: 409,
        type: 3,
        size [40, 30]
        title {
            text: "Elephantine",

        }
        subtitle {
            text: "Il confine nubiano",

        }
        content {
            text: "@PÈ stato annunciato un nuovo faraone, Nebka, fondatore della terza  dinastia di regnanti egizi. Nebka ha conferito all'Egitto un'ottima  organizzazione, ordinando la divisione del Regno in distretti, o 'nome',  ciascuno governato da un signore chiamato 'Nomarca'. Anche se il sistema può  apparire rigido, l'Egitto è cresciuto e continua a prosperare, con ottimi  risultati anche nei campi dell'architettura e dell'arte.   @PIl faraone desidera estendere i confini del proprio Regno verso sud, in Nubia.  Egli ordina di fondare una città presso la prima cataratta del Nilo, sull'isola  di Elephantine, così da sfruttare i ricchi depositi di gemme, granito e arenaria  che lì si trovano.   @PLa necropoli di Abydos richiede molti materiali di questo tipo, in quanto la  nobiltà desidera costruire tombe sempre più lussuose. Anche la capitale Menphis  può aver bisogno di mattoni per costruire le tombe e il faraone Nebka sosterrà  le richieste per questi e altri materiali da costruzione.   @PIl faraone Nebka ha inoltre ordinato che uno dei tuoi pari stabilisca un  avamposto militare nell'Oasi di Selima, per difendere la via delle carovane che  si dirigono all'interno dell'Africa. Quando sarà operativo, potrai contattare  Selima per trovare il prezioso ebano, un altro materiale da costruzione molto  richiesto."
        }
    }
    message_mission_saqqara {
        id: 410,
        type: 3,
        size [40, 30]
        title {
            text: "Saqqara",

        }
        subtitle {
            text: "La prima piramide",

        }
        content {
            text: "L'ascesa del faraone Djoser al trono d'Egitto ci ha portato in una  nuova era di saggezza, istruzione e opere d'arte. Occorre stabilire il cimitero  reale a Saqqara, così che serva come eterno luogo di riposo per nobili quali  Hezyre e Khabausokar, i fidati consiglieri del faraone.   @PTale luogo deve, però, contenere anche un monumento tanto imponente come mai  il mondo ne abbia visti prima. Io, Imhotep primo consigliere del faraone, ho  ideato un nuovo tipo di tomba per il faraone. Invece della bassa struttura in  mattoni tipica delle mastaba, la nuova tomba si ergerà verso il cielo, come se  fosse composta di molte mastaba, costruite una sopra l'altra. Inoltre, questa  'piramide a gradoni' sarà completamente in pietra, così che possa vincere il  trascorrere dei secoli. Al suo interno, un sarcofago di granito conterrà il  corpo del faraone per tutto il suo eterno riposo. @PI sacerdoti della necropoli di Abydos hanno perfezionato l'arte di utilizzare  la tela per imbalsamare i defunti, così tutti gli Egizi avranno accesso alla  vita oltre la vita.  @PIl nostro avamposto nell'oasi di Selima è tuttora fiorente, da lì potrai  importare l'ebano d'Africa.  @PIl faraone ti ha concesso una generosa somma di denaro per iniziare il  progetto. Non lo deludere."
        }
    }
    message_mission_serabit_khadim {
        id: 411,
        type: 3,
        size [40, 30]
        title {
            text: "Serabit Khadim",

        }
        subtitle {
            text: "I Beduini dell'est",

        }
        content {
            text: "Come Den prima di lui, il faraone Huni ha ordinato una spedizione  nelle lande inospitali del Sinai per recuperare turchesi e rame. Egli desidera  dirigere tale spedizione, verso il luogo chiamato Serabit Khadim, dove si  trovano i resti di un precedente insediamento egizio. La loro attuale condizione  è sconosciuta, ma potrebbero fornire un minimo di protezione per la spedizione.   @PDevi sapere che la prima spedizione inviata laggiù non è mai tornata e anche  la seconda, inviata a recuperarla, non ci ha più fornito notizie. Comunque, se  vogliamo armare i nostri soldati in modo adeguato, il nostro Regno ha bisogno di  rame per fabbricare le armi e questo metallo purtroppo, è scarso. @PPreparati, sarai sotto costante minaccia di attacco da parte dei Beduini del  deserto e dei Canaaniti, nostri nemici. Estrai tutto il rame e le gemme che puoi  e assicurati di soddisfare le richieste del faraone. Puoi ricorrere agli orafi  per sfruttare le gemme che avanzano e fabbricare gioielli per la gente del  luogo."
        }
    }
    message_mission_meidum {
        id: 412,
        type: 3,
        size [40, 30]
        title {
            text: "Meidum",

        }
        subtitle {
            text: "La necropoli reale",

        }
        content {
            text: "Il faraone Huni desidera trascorrere il suo eterno riposo in una  piramide a gradoni, come Djoser prima di lui. Egli inoltre desidera essere  circondato dalle tombe dei suoi nobili e ha scelto Meidum, nel Basso Egitto,  come sito adatto a ospitare la necropoli reale.   @PCome segno di ringraziamento per i numerosi anni in cui la tua famiglia ha  servito il Regno, Huni ti ha concesso l'ingresso a Meidum, in una tomba  personale. Ecco, dunque, l'onore concesso alla tua famiglia. @PPer assicurarsi che saggezza e istruzione si mantengano nei secoli, il faraone  Huni invita a costruire biblioteche reali. Quando saranno riempite di pergamene  e papiri, forniranno un'ottima risorsa per l'istruzione delle classi sociali più  elevate. @PIl faraone ha inviato un suo assistente in una spedizione verso Serabit  Khadim, nelle aspre terre del Sinai, per recuperare preziosi turchesi. Se la  spedizione avesse successo, potrai rivolgerti a tale città per importare le  gemme. Gli orafi usano le gemme per creare gioielli, un bene di lusso che sarà  molto apprezzato dai tuoi cittadini. @PLa città di Apollinopolis, una volta fiorente, ha ora iniziato la sua fase di  declino e non esporta più tutti i beni per cui era così famosa."
        }
    }
    message_mission_buhen {
        id: 413,
        type: 3,
        size [40, 30]
        title {
            text: "Buhen",

        }
        subtitle {
            text: "Espansione in Nubia",

        }
        content {
            text: "Il nostro nuovo faraone, Snofru, intende fare in modo che la propria  dinastia, la quarta, sia ricordata come la più grande di ogni tempo. Il faraone  desidera espandere ulteriormente i confini verso sud. Ha dunque deciso di  invadere la Nubia e di fondare una città fortificata a Buhen, oltre alla seconda  cataratta del Nilo. Qui dovrai inoltre erigere un grande obelisco di granito,  perché sia chiaro che il territorio ora appartiene all'Egitto e al suo faraone.  A sud, non troverai granito; quindi, dovrai importarlo da Elephantine. @PA Buhenm, incontrerai i fieri ed esperti guerrieri nubiani, che combatteranno  fino alla morte per respingere l'invasore: ma non disperare, dopo anni di  faticoso addestramento presso l'Accademia militare, anche il nostro esercito è  più che esperto. In più, i nostri genieri hanno ideato alcune strutture di  difesa, come le torri, le mura e le guarnigioni fortificate. Tali strutture  saranno fondamentali per tenere a bada l'esercito nubiano. Potrebbero, inoltre,  occorrere delle navi da trasporto per facilitare lo spostamento dei soldati  lungo il fiume.  @PVerso nord, abbiamo instaurato una relazione diplomatica con gli Enkomi,  sull'isola di Cipro. Questa terra prende il nome dall'abbondanza di rame, che  ora potremo acquistare da loro. Comunque, abbiamo da poco stabilito una comunità  mineraria a Serabit Khadim, nelle terre del Sinai e, dunque, siamo in grado di  rifornire il Regno di rame a un prezzo molto più basso. Le forniture da Serabit  Khadim sono spesso irregolari, a causa delle continue incursioni di Beduini e  Canaaniti e non siamo certi che le forze egizie possano resistere ancora per  molto.  @PLa tomba del faraone, un monumento unico, è in fase di costruzione a Dahshur.  Di quando in quando, il faraone potrebbe chiederti di contribuire fornendo  pietra calcarea per completare il suo progetto."
        }
    }
    message_mission_south_dahshur {
        id: 414,
        type: 3,
        size [40, 30]
        title {
            text: "A sud di Dahshur",

        }
        subtitle {
            text: "La piramide sghemba di Snofru",

        }
        content {
            text: "@PIl nostro nuovo faraone, Snofru, intende fare in modo che la  propria dinastia, la quarta, sia ricordata come la più grande di tutti i tempi.  I suoi architetti hanno ideato una tomba ancora più spettacolare di quella di  Huni e il faraone desidera che tu ne supervisioni la costruzione. Dovrai  stabilire un insediamento a sud di Dahshur, il luogo scelto per la sua piramide  sghemba. Una volta operativa, la città fornirà la forza lavoro necessaria al  completamento del suo ambizioso progetto. @PLa piramide sghemba deve essere costituita da una struttura interna in pietra,  successivamente rivestita con calcare bianco perché risplenda sotto il sole del  deserto. Troverai calcare a sufficienza a Dahshur, ma dovrai importare la  pietra. @PIl faraone desidera che i confini si estendano ancora più a sud; quindi, ha  inviato il suo esercito a invadere la Nubia e fondare una città fortificata a  Buhen, oltre alla seconda cataratta del Nilo. @PVerso nord, l'Egitto ha intrapreso una relazione diplomatica con gli Enkomi,  sull'isola di Cipro. L'isola deve il suo nome all'abbondanza di rame che ora noi  importiamo in modo massiccio. @PPuoi ottenere delle pietre preziose dal recente avamposto di Serabit Khadim,  nel Sinai. Ultimamente, le forniture sono irregolari, a causa delle continue  incursioni di Beduini e Canaaniti; non siamo certi che le forze egizie possano  resistere ancora per molto."
        }
    }
    message_mission_north_dahshur {
        id: 415,
        type: 3,
        size [40, 30]
        title {
            text: "A nord di Dahshur",

        }
        subtitle {
            text: "La vera piramide",

        }
        content {
            text: "@PIl faraone Snofru ha portato l'ordine in Egitto e ora il Regno  fiorisce sotto il suo saggio e benevolo governo. Snofru desidera iniziare la  costruzione di un altro progetto a Dahshur, ancora più ambizioso della  precedente piramide sghemba. Gli architetti, i supervisori e gli ingegneri reali  credono di riuscire a costruire un edificio i cui lati siano inclinati a un  angolo continuo, culminante con una punta perfetta. Se riusciranno, questa sarà  la prima vera piramide, l'ideale dimora del faraone Snofru per tutta l'eternità!    @PLa moglie del faraone, la regina Hetehpheres, ha recentemente dato alla luce  un figlio che è stato chiamato 'Khufu'. La nostra gente non anticipa certo con  gioia il momento in cui sarà lui a regnare, infatti i veggenti di Horus, dio del  faraone, hanno predetto che non mostrerà la stessa benevolenza del padre. Anche  se riuscirà in molte imprese, essi temono che l'Egitto cadrà sotto una  estenuante tirannia.  @PPuoi acquistare il legno da Byblos, dato che i carpentieri dovranno costruire  molte rampe così che i manovali possano raggiungere la cima della grande  piramide."
        }
    }
    message_mission_dendera {
        id: 416,
        type: 3,
        size [40, 30]
        title {
            text: "Dendera",

        }
        subtitle {
            text: "La difesa dell'Egitto",

        }
        content {
            text: "@PIl faraone Khufu è salito al trono e, così come avevano predetto i  veggenti di Horus e Ra, la nostra gente ha già iniziato a soffrire a causa della  sua oppressione.  @PKhufu ha ordinato che il governatore reale raggiunga immediatamente Dendera  per difendere il territorio dagli invasori kushiti. Dendera può supportare una  piccola industria di pesca, in grado di sfamare l'insediamento per un po' di  tempo. Se i Kushiti giungono dall'acqua, però, il fiume diventerà poco sicuro  per le barche da pesca e le spiagge dovrebbero essere meglio sfruttate per  creare una flotta di navi da guerra. Se il cibo scarseggia, è possibile allevare  del bestiame per produrre carne, anche se le mandrie richiedono molta paglia,  difficile da crescere in questa regione. Per ottenere la paglia, dovrai  rivolgerti ad altre città e commerciare anche per procurarti i mattoni per la  tua mastaba. @PLa città di Byblos nel Libano, terra dei cedri, ha iniziato a commerciare con  il potente impero dell'est. Gli Assiri e gli Ur della Mesopotamia (la terra tra  i due fiumi) sono ricchi d'avorio che potrai ottenere commerciando con Byblos.  Con l'arrivo di merci rare ed esotiche come l'avorio, Dendera certo fiorirà in  un istante. @PNella capitale, gli Egizi si divertono con un nuovo gioco da tavolo che si  chiama senet. Di solito si gioca di fronte a un boccale di birra, in luoghi  pubblici chiamati taverne senet. Tali luoghi possono offrire alla gente di  Dendera un piacevole diversivo dall'autorità tirannica di Khufu. @PIl faraone ha ordinato la predisposizione di innumerevoli cave a Heliopolis,  nella regione del Delta, per produrre una grande quantità di calcare bianco.  Solo gli dei sanno come intenderà impiegarlo. Si dice che stia pensando a un  progetto di costruzione colossale sull'altopiano vicino a Giza, così grandioso  da offuscare la fama che suo padre (il saggio e benevolo Snofru) si era meritato  per aver costruito ben due nobili piramidi."
        }
    }
    message_mission_heliopolis {
        id: 417,
        type: 3,
        size [40, 30]
        title {
            text: "Heliopolis",

        }
        subtitle {
            text: "L'avorio dell'est",

        }
        content {
            text: "@PIl faraone Khufu è salito al trono e, come avevano predetto i saggi  di Horus e Ra, la nostra gente soffre a causa della sua oppressione. Si dice che  stia pensando a un progetto di costruzione colossale sull'altopiano vicino a  Giza, così grandioso da offuscare la fama che suo padre (il saggio e benevolo  Snofru) si era meritato per aver costruito ben due nobili piramidi. @PIl faraone Khufu ha ordinato la predisposizione di molte cave a Tura, nella  regione del Delta, dove si trovano ricchi depositi di calcare bianco. Devi,  inoltre, costruire tre mastaba per i nobili della regione, così che il faraone  possa premiare la loro devozione. Gli insediamenti di cavatori si chiameranno  'Heliopolis' e dovranno servire a produrre grandi quantità di calcare bianco per  molti anni... solo gli dei sanno cosa intenda farsene. @PLa città di Byblos nel Libano, terra dei cedri, ha iniziato a commerciare con  il potente impero dell'est. Gli Assiri e gli Ur della Mesopotamia, la terra tra  i due fiumi, sono ricchi d'avorio che potrai ottenere commerciando con Byblos.  Con l'arrivo di merci rare ed esotiche come l'avorio, 'Heliopolis' certo fiorirà  in un istante. @PKhufu ha inoltre inviato un governatore reale a Dendera, per difendere le  nostre terre dagli invasori kushiti. I consiglieri reali commiserano il  governatore cui è capitato tale difficile e oneroso incarico.  @PNella capitale, gli Egizi si divertono con un nuovo gioco da tavolo che si  chiama senet. Di solito, si gioca di fronte a un boccale di birra, in luoghi  pubblici chiamati taverne senet. Tali luoghi possono offrire alla gente di  Heliopolis un piacevole diversivo dall'autorità tirannica di Khufu."
        }
    }
    message_mission_giza {
        id: 418,
        type: 3,
        size [40, 30]
        title {
            text: "Giza",

        }
        subtitle {
            text: "La grande piramide e la sfinge",

        }
        content {
            text: "Finalmente, il faraone Khufu ha rivelato i propri piani e le proprie  sconfinate aspirazioni: essi peseranno per molto tempo sulle spalle della nostra  gente. Il faraone benedice e maledice allo stesso tempo la tua famiglia, perché,  anche se ti sei guadagnato il livello di Nomarca, il primo compito che ti viene  affidato è quello di portare a termine il progetto di costruzione più ambizioso  di tutti i tempi.   @PIl luogo dell'eterno riposo del faraone sarà un gigantesco complesso di  piramidi, lontano da ogni città, sull'altopiano vicino a Giza. Il suo sarcofago  sarà di robusto granito e la sua chiatta funebre di prezioso legno del Libano.  Vicino al complesso di piramidi del faraone, dovrai costruire una piramide più  piccola per suo figlio, il principe Khafra, la cui tirannia rivaleggia con  quella del padre, ma i cui successi ne sono ben lungi. Khafra richiede, inoltre,  che la sua immagine sia scolpita nella pietra di Giza, sulla sommità di  un'enorme statua chiamata 'sfinge', con il corpo di leone e la testa di un uomo. @PPer supportare questo enorme impegno edilizio, dovrai fondare un grande  insediamento a Giza. Le altre condizioni sono a tua discrezione, in quanto il  tuo unico obiettivo è quello di completare questi tre grandi progetti e di  onorare la fiducia del faraone.   @PTi verranno inviate alcune lastre di calcare bianco necessarie per le  rifiniture delle piramidi, ma dovrai acquistare tutto il resto con i fondi della  città. @PIl faraone affida a te, stimato Nomarca reale, questi tre compiti sacri. Tu  dovrai dimostrare la tua incrollabile devozione al faraone ed esaudire i suoi  desideri... a qualunque costo."
        }
    }
    message_mission_bahariya_oasis {
        id: 419,
        type: 3,
        size [40, 30]
        title {
            text: "Oasi di Bahariya",

        }
        subtitle {
            text: "Il deserto occidentale",

        }
        content {
            text: "@PI regni di Khufu e Khafra sono finiti e, con loro, anche la quarta  dinastia di famiglie regnanti sull'Egitto. Khentkaues, una parente lontana della  casa reale, ha dato alla luce il nuovo faraone chiamato 'Userkaf': la stirpe di  sangue reale, così, ha modo di proseguire. Con Userkaf comincia la quinta  dinastia, dando inizio a un'era che promette molti cambiamenti. @PUserkaf ha in qualche modo decentralizzato il governo del Regno e ha affidato  più potere alle autorità locali. Ora i Nomarchi come te sono liberi di gestire i  propri affari. Il faraone non cercherà di imitare i propri predecessori con  monumentali progetti di costruzione; infatti, ha in mente per te un altro  compito. @PIl faraone ha deciso che Ra, dio del sole e del Regno, è il re degli dei e  intende proclamare il suo dominio in tutto il territorio. La terra d'Egitto è  già costellata di molti Templi del Sole, ma il faraone desidera estendere la sua  influenza fino ai confini del Regno. @PEcco perché dovrai costruire un insediamento fortificato nell'Oasi di  Bahariya, nel cuore del deserto occidentale. Usa saggiamente la poca acqua che  troverai, in quanto, essendo così lontana dal Nilo, di solito è ambita da ogni  sorta di bestie feroci. Inoltre, dovrai fare attenzione agli attacchi dei  guerrieri libici e dei Beduini del deserto, che ultimamente intaccano la  ricchezza delle nostre carovane. Pianifica le tue difese con attenzione e  sfrutta tutte le risorse, come il legno o la selvaggina, che troverai  nell'oasi."
        }
    }
    message_mission_abusir {
        id: 420,
        type: 3,
        size [40, 30]
        title {
            text: "Abusir",

        }
        subtitle {
            text: "Il Tempio del Sole",

        }
        content {
            text: "@PI regni di Khufu e Khafra sono finiti e, con loro, anche la quarta  dinastia di famiglie regnanti sull'Egitto. Khentkaues, una parente lontana della  casa reale, ha dato alla luce il nuovo faraone chiamato 'Userkaf': la stirpe di  sangue reale, così, ha modo di proseguire. Con Userkaf comincia la quinta  dinastia, dando inizio a un'era che promette molti cambiamenti. @PUserkaf ha, in qualche modo, decentralizzato il governo del Regno e ha  affidato più potere alle autorità locali. Ora i Nomarchi come te sono liberi di  gestire i propri affari. Il faraone non cercherà di imitare i propri  predecessori con progetti monumentali di costruzione; infatti, ha in mente per  te un altro compito. @PIl faraone ha deciso che Ra, dio del sole e del Regno, è il re degli dei e  intende proclamare il suo dominio in tutto il territorio. La terra d'Egitto è  già costellata di molti Templi del Sole, ma il faraone desidera che il più  grande si trovi a Abusir, nell'umida regione del Delta del Basso Egitto. @PCome gli altri territori del Delta, Abusir è ricca di selvaggina, pesce, altri  animali selvatici e vegetazione, ma non offre alcuna risorsa mineraria. Ecco  perché l'arenaria necessaria alla costruzione del tempio dovrà essere importata  dalle cave di Heliopolis. Qui è possibile allevare il bestiame per produrre  carne, ma le mandrie necessitano di molta paglia. @PPer preparare un terreno adatto alla costruzione del Tempio del Sole, dovrai  ripulirlo. Per prima cosa, assicurati di vendere una buona quantità del prezioso  legno che potrai tagliare, in quanto una volta ammassato non sarai più in grado  di procurartene altro. Heliopolis e Abydos hanno sempre bisogno di legno e  selvaggina; quindi, entra in commercio con loro per compensare le spese  necessarie alla costruzione del tempio."
        }
    }
    message_mission_dunqul {
        id: 421,
        type: 3,
        size [40, 30]
        title {
            text: "Dunqul",

        }
        subtitle {
            text: "La minaccia kushita",

        }
        content {
            text: "@PPepy è salito al trono e ha conferito alla tua famiglia lo stato di  Cancelliere. L'autorità centralizzata continua ad affievolirsi, man mano che i  capi locali diventano più potenti. I raccolti in alcune regioni sono molto al di  sotto della normalità e lo spettro della carestia inizia a mietere le prime  vittime. Menphis, un tempo una splendida città, ha iniziato il proprio declino.  I veggenti prevedono l'approssimarsi di tempi difficili. @PI nostri vicini più potenti si fanno sempre più baldanzosi man mano che cresce  la debolezza dell'Egitto. L'avamposto di Buhen è sotto assedio da parte dei  feroci guerrieri kushiti giunti da Kerma, la più grande città non egizia di  tutta l'Africa. I Kushiti esigono tributi e la più piccola provocazione può  portare a un attacco in piena regola. Anche la Nubia ha dichiarato guerra e  vuole rientrare in possesso dei propri territori. @PPerché l'Egitto sopravviva, devi fare il possibile per preservare le vie  commerciali e mantenere i rifornimenti attivi. Mantieni in funzione la stazione  commerciale dell'Oasi di Selima. Pepy, anticipando il suo viaggio nell'aldilà,  ti farà frequenti richieste di pietra per costruire la sua piramide e anche  altre città, carenti di cibo, cercheranno la tua assistenza. @PUsa le tue risorse con cautela. Nell'oasi puoi trovare molto legno prezioso,  ma parte della foresta dovrà essere distrutta per accedere alla magra provvista  d'acqua."
        }
    }
    message_mission_dakhla {
        id: 422,
        type: 3,
        size [40, 30]
        title {
            text: "Dakhla",

        }
        subtitle {
            text: "Il sentiero delle carovane",

        }
        content {
            text: "@PPepy è salito al trono e ha conferito alla tua famiglia lo stato di  Cancelliere. L'autorità centralizzata continua ad affievolirsi, man mano che i  capi locali diventano più potenti. I raccolti in alcune regioni sono molto al di  sotto della normalità e lo spettro della carestia inizia a mietere le prime  vittime. Menphis, un tempo una splendida città, ha iniziato il proprio declino.  I veggenti prevedono l'approssimarsi di tempi difficili. @PI nostri vicini più potenti si fanno sempre più baldanzosi man mano che cresce  la debolezza dell'Egitto. L'avamposto di Buhen è sotto assedio da parte dei  feroci guerrieri kushiti giunti da Kerma, la più grande città non egizia di  tutta l'Africa. I Kushiti esigono tributi e la più piccola provocazione può  portare a un attacco in piena regola. Anche la Nubia ha dichiarato guerra e  vuole rientrare in possesso dei propri territori.  @PCerca di aumentare la stabilità del Regno fondando un centro amministrativo  nell'Oasi di Dakhla. L'oasi possiede molti alberi, che però bloccano l'accesso  alla limitata riserva d'acqua. Da questa importante locazione, puoi importare  l'ebano dell'Africa centrale. Pepy, anticipando il suo viaggio nell'aldilà, ti  chiederà spesso dei mattoni per costruire il suo monumento. Altre città, carenti  di cibo, cercheranno il tuo aiuto."
        }
    }
    message_mission_thinis {
        id: 423,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",

        }
        subtitle {
            text: "La guerra civile",

        }
        content {
            text: "L'antico splendore di vita è stato dimenticato per sempre e tutti  temono che l'Egitto non ritroverà più la gloria del passato. Osiride ha voltato  le spalle alla sua gente e una serie di scarsi straripamenti l'hanno ridotta  alla fame. Il potere dei Faraoni, un tempo indiscusso, è ormai svanito,  sostituito da quello di signorotti locali attaccabrighe. @PIn mezzo a questo caos, due nobili famiglie cercano di prendere il controllo  dell'Egitto. I signori di Heraklopolis reclamano il trono come legittimi eredi.  Essi sono molto crudeli e fanno ben poco per lenire il dolore del popolo. A sud,  una nuova famiglia, la casa Inyotef, è salita al potere nella zona di Tebe.  Questa famiglia ha fatto il possibile per riunificare tutto il sud e ora  Herakleopolis combatte contro Tebe in una mortale guerra civile per controllare  tutto il paese. @PPer mostrare la loro benevolenza verso gli Egizi, gli Inyotef ti hanno  affidato il compito di ricostruire la città conquistata di Thinis, una delle più  antiche d'Egitto. Due tra i più famosi e splendidi edifici di Thinis sono  sopravvissuti alla distruzione: il Complesso dei templi di Osiride e la magione.  Gli Inyotef hanno deciso che, se questi edifici dovessero andare distrutti, non  fornirebbero alcun finanziamento per la loro ricostruzione. I dominatori di Tebe  considerano la ricostruzione di Thinis un progetto di primaria importanza e  quindi hanno già stanziato un buon finanziamento - anche in questi tempi  turbolenti. Riporta Thinis al suo antico splendore, crea una flotta e un  esercito per difenderla dai frequenti attacchi degli Herakleopoli, comprese le  città di Lykopolia, Hierakonopolis e Hermopolis. Fai attenzione agli  Herakleopoli: potrebbero chiederti dei tributi per mettere alla prova la tua  fedeltà - e i tuoi deben. Inoltre, fai attenzione ai Nubiani, sempre in agguato  e decisi a sfruttare questo periodo di debolezza."
        }
    }
    message_mission_thebes {
        id: 424,
        type: 3,
        size [40, 30]
        title {
            text: "Waset",

        }
        subtitle {
            text: "La guerra civile",

        }
        content {
            text: "L'antico splendore di vita è stato dimenticato per sempre e tutti  temono che l'Egitto non ritroverà più la gloria del passato. Osiride ha voltato  le spalle alla sua gente e una serie di scarsi straripamenti l'hanno ridotta  alla fame. Il potere dei Faraoni, un tempo indiscusso, è ormai svanito,  sostituito da quello di signorotti locali attaccabrighe. @PIn mezzo a questo caos, due nobili famiglie cercano di prendere il controllo  dell'Egitto. I signori di Herakleopolis reclamano il trono come legittimi eredi.  Essi sono molto crudeli e fanno ben poco per lenire il dolore del popolo. A sud,  una nuova famiglia, la casa Inyotef, è salita al potere nella zona di Tebe.  Questa famiglia ha fatto il possibile per riunificate tutto il sud e ora  Herakleopolis combatte contro Tebe in una mortale guerra civile per controllare  tutto il paese. @PGli Inyotef, occupati a combattere gli Herakleopoli, ti hanno affidato il  compito di costruire la loro città di Tebe. Se gli Inyotef vogliono vincere la  lotta contro i dominatori di Herakleopolis e consolidare la loro reputazione in  Egitto, Tebe dovrà essere la pietra portante (alla quale altre città possano  affidarsi), in grado di fornire soccorsi o soldati a chi li dovesse richiedere.  Tebe, che diventerà la capitale del Regno se gli Inyotef vinceranno la guerra,  dovrà quindi essere una grande città. Sfruttando le poche risorse a tua  disposizione, devi costruire un Tempio del Sole e una piramide così da mostrare  a tutti gli Egizi la gloria degli Inyotef. @PTebe non sarà immune agli attacchi. I dominatori di Herakleopolis e i loro  seguaci, potrebbero minacciarla più volte e gli di Herakleopoli stessi  potrebbero estorcere denaro dai tuoi forzieri. Per proteggere la città da questi  possibili rischi, devi creare una flotta e un esercito potenti, a disposizione  anche di altre città alleate."
        }
    }
    message_mission_coptos {
        id: 425,
        type: 3,
        size [40, 30]
        title {
            text: "Coptos",

        }
        subtitle {
            text: "La riunificazione",

        }
        content {
            text: "I successi ottenuti dalla tua famiglia durante la guerra civile non  sono rimasti senza compenso. Io, faraone Mentuhotep, ho concesso alla tua  famiglia il rango di Consigliere. Non esiste nessun altro in tutto l'Egitto di  cui mi possa fidare. Ora che i due regni dell'Alto e del Basso Egitto sono di  nuovo uniti e la capitale Tebe è florida, ho bisogno di te per consolidare la  mia posizione in tutto il Regno. @PAnche se unito, l'Egitto è incline alle lotte intestine, specialmente nelle  zone un tempo fedeli agli di Herakleopoli. Per consolidare l'unificazione,  voglio che tu ricostruisca e difenda Coptos. Coptos dovrà essere una città  splendida così che dimostri a tutti gli Egizi che nulla è impossibile con il mio  Regno. La città è spesso attaccata da altre della fazione avversaria, in  particolare Hermopolis e, quindi, devi assolutamente difenderla. @PLa carestia è ancora in agguato e spesso altre città del Regno ti chiederanno  del cibo. Soddisfa le richieste il più in fretta possibile, così l'Egitto  ammirerà la mia benevolenza e l'impegno del mio più fidato consigliere. @PSo che ti chiedo molto, ma nessun altro sarebbe in grado di portare a termine  tale compito."
        }
    }
    message_mission_beni_hasan {
        id: 426,
        type: 3,
        size [40, 30]
        title {
            text: "Beni Hasan",

        }
        subtitle {
            text: "La riunificazione",

        }
        content {
            text: "I successi ottenuti dalla tua famiglia durante la guerra civile non  sono rimasti senza compenso. Io, faraone Mentuhotep, ho concesso alla tua  famiglia il rango di Consigliere. Non esiste nessun altro in tutto l'Egitto di  cui mi possa fidare. Ora che i due regni dell'Alto e del Basso Egitto sono di  nuovo uniti e la capitale Tebe è florida, ho bisogno di te per consolidare la  mia posizione in tutto il Regno. @PAnche se unito, l'Egitto è incline alle lotte intestine, specialmente nelle  zone un tempo fedeli agli Herakleopoli. Per consolidare l'unificazione, voglio  che tu ricostruisca e difenda Beni Hesan, che è stata quasi completamente  distrutta durante la guerra civile. Beni Hesan dovrà essere una città così  splendida da dimostrare a tutti gli Egizi che nulla è impossibile con il mio  Regno. @PLa carestia è ancora in agguato e spesso altre città del Regno ti chiederanno  del cibo. Soddisfa le richieste il più in fretta possibile, così l'Egitto  ammirerà la mia benevolenza e l'impegno del mio più fidato consigliere. @PTi chiedo di erigere alcuni obelischi di granito per ricordare a tutti le mie  opere di bene. @PSo che ti chiedo molto, ma nessun altro sarebbe in grado di portare a termine  tale compito."
        }
    }
    message_mission_itjtawy {
        id: 427,
        type: 3,
        size [40, 30]
        title {
            text: "Itjtawy",

        }
        subtitle {
            text: "Una nuova capitale",

        }
        content {
            text: "O potente faraone, favorito di Ra, la buona fortuna ti rallegri! La  tua ascesa al trono è il coronamento del sogno di tutti gli Egizi! Non esiste  ricompensa più grande, da parte di uomini e dei. Con l'ascesa della tua  famiglia, l'Egitto potrà nuovamente rinascere e forse così dimenticheremo gli  orrori della guerra civile. @PPer commemorare questo nuovo inizio, devi costruire una nuova splendida  capitale. Itjtawy, con le sue abbondanti risorse naturali, è il luogo ideale.  Sfruttando ciò che la terra ha da offrire, puoi costruire una splendida città,  degna del tuo valore e incrollabile dedizione. @PPer assicurarti che le opere della tua dinastia siano ricordate per sempre,  devi costruire due colossali piramidi di mattoni, per te e per la tua famiglia,  oltre a una sfinge che vigili sulla tua tomba. Una famiglia con alle spalle una  lunga tradizione di successi non merita di meno. @PRicorda, però, che alcune zone del paese mettono in dubbio la legittimità  della tua ascesa. Molti soffrono ancora gli effetti della carestia e lamentano  l'usurpazione del trono. Se riuscirai a risollevare questa gente dalla miseria e  la aiuterai a ricostruire le proprie case, te ne guadagnerai certamente la  fedeltà. Dovrai provvedere a loro come ai tuoi nuovi sudditi, per evitare che i  più disperati impugnino le armi e si uniscano in rivolta."
        }
    }
    message_mission_mirgissa {
        id: 428,
        type: 3,
        size [40, 30]
        title {
            text: "Mirgissa",

        }
        subtitle {
            text: "Verso la Nubia",

        }
        content {
            text: "Ora che l'Egitto è saldamente unito sotto il tuo dominio, i tuoi  cortigiani e io per primo, il tuo consigliere, ti raccomandiamo di estendere i  confini meridionali ancora più a sud, verso la Nubia. Il letto del fiume secco  ad Allaqi è ricco d'oro e una possente città a Mirgissa, che puoi eleggere come  tua residenza, scoraggerà eventuali attacchi da parte dei Nubiani. Ma devi fare  attenzione ai Kushiti. Sono avversari molto più pericolosi dei Nubiani e  useranno le loro spade per costringerti, o mio faraone, ad abbandonare il loro  Regno. @PPer contrassegnare il nuovo territorio nubiano, devi costruire un grande  obelisco che attesti le grandi imprese del popolo egizio. L'obelisco mostrerà ai  Nubiani i vantaggi del dominio egizio e fungerà da costante ricordo della nostra  presenza. @PLa tua attenzione non deve focalizzarsi solo su Mirgissa: non devi dimenticare  i piani relativi alla fondazione di una città portuale sul Mar Rosso, a Mersa.  Mersa avrà bisogno dell'aiuto del faraone e non esiterà a chiederlo. Se Mersa  riuscirà a fiorire, fornirà a Mergissa il rame necessario a forgiare le armi."
        }
    }
    message_mission_mersa_gawasis {
        id: 429,
        type: 3,
        size [40, 30]
        title {
            text: "Mersa Gawasis",

        }
        subtitle {
            text: "Sulle spiagge del Mar Rosso",

        }
        content {
            text: "Ora che l'Egitto è fermamente unito sotto il tuo dominio, dobbiamo  sviluppare una serie di relazioni commerciali con tutte le città del mondo, così  da accrescere la nostra ricchezza, o Re delle Due Terre.  @PLa tua gente prospera e richiede beni di lusso. Stanchi dei soliti gioielli,  un bene di lusso sempre disponibile, i tuoi cittadini desiderano qualcosa di più  raro e costoso, come l'incenso. La tua corte e io per primo, il tuo consigliere,  ti raccomandiamo di fondare un porto sul Mar Rosso presso Mersa. Mersa offre una  via commerciale verso la lontana Punt, da cui è possibile importare il miglior  incenso del mondo, anche se con spese ingenti.   @POltre ad alcuni filoni d'oro e di rame, Mersa produce anche altre materie  prime, ma può prosperare solo come produttore di beni finiti. Importando la  materia prima ed esportando prodotti finiti, Mersa riuscirà a ricavare buoni  profitti. @PMentre tu sei occupato con Mersa, uno dei nostri più abili Nomarchi sta  preparando un nuovo centro commerciale in Nubia. La sua città, Mergissa,  probabilmente verrà attaccata, quindi, mio amato faraone, preparati a inviare  tutte le risorse di cui avrà bisogno. @PSotto il tuo governo, Mersa diventerà una delle città più belle del Regno,  adatta a essere luogo prescelto per il tuo riposo eterno e per quello della tua  famiglia. Mentre ti occupi della costruzione del porto, non dimenticarti dei  preparativi per l'aldilà. Un mausoleo e una piccola piramide di mattoni saranno  un'ottima abitazione per anticipare il passaggio verso i Campi di Canne."
        }
    }
    message_mission_semna {
        id: 430,
        type: 3,
        size [40, 30]
        title {
            text: "Semna",

        }
        subtitle {
            text: "La sfida",

        }
        content {
            text: "Venerabile faraone, tutto ciò che hai creato è ora sotto minaccia! La  flotta nubiana è sul Nilo e colpisce il cuore del nostro paese saccheggiando e  distruggendo i nostri villaggi e città. I Nubiani attaccano anche le nostre navi  commerciali e rubano le merci. Per aiutare le città del nord a respingere gli  attacchi, devi preparare soldati e navi da guerra da inviare a chi ne farà  richiesta.   @PPer impedire che i Nubiani solchino nuovamente le nostre acque, il tuo  supervisore militare raccomanda di costruire una serie di forti a Semna, tra la  seconda e la terza cataratta del Nilo. I forti fungeranno da sbarramento e  respingeranno ogni avanzata nubiana. @PLa definitiva sconfitta dei Nubiani dipende dalla cattura della città di  Kuban. Kuban è ricca di risorse e la sua conquista danneggerà l'economia  nubiana. Quando avrai preso il controllo di Kuban, potrai importare l'arenaria  necessaria alla costruzione del tuo mausoleo. Il tuo mausoleo a Semma  contribuirà a rammentare ai Nubiani il tuo dominio su di loro. @PLe sfide da accettare e vincere per difendere gli Egizi sono molte. Fai  attenzione, o Horus vivente, alla tempesta che si innalza a est. Il frastuono  dei cavalli al galoppo si ode in tutta Canaan e i veloci carri da guerra  seminano morte e distruzione lungo la loro folle corsa. Questi carri  formidabili, mai visti prima, sono guidati dai guerrieri Hyksos. Le nuvole della  tempesta sono già state avvistate all'orizzonte e tu devi prepararti ad  affrontare il pericolo imminente."
        }
    }
    message_mission_bubastis {
        id: 431,
        type: 3,
        size [40, 30]
        title {
            text: "Bubastis",

        }
        subtitle {
            text: "La città di Bast",

        }
        content {
            text: "Grande faraone, dopo aver consolidato le vie commerciali, dobbiamo  mostrare all'Egitto i vantaggi del successo e della ricchezza. Bubastis è un  luogo perfetto per una città del genere: possiamo proteggere le nostre preziose  vie commerciali orientali e rendere omaggio a Bast, che ha sempre protetto  l'Egitto. @PLa città di Bast dovrà essere la gemma dell'Egitto. Dovrà essere bella come un  fiore di loto, ricca di spettacoli, scuole, biblioteche e luoghi di culto. Ai  suoi cittadini non dovrà mancare alcun genere di beni, compreso l'incenso  importato. Quando sarà completa, Bubastis sarà il gioiello sulla corona dei  regni gemelli. @PMentre costruisci questa città gloriosa, fai attenzione al tuono dei cavalli  provenienti dall'est. Il frastuono dei cavalli al galoppo si ode in tutta Canaan  e i veloci carri da guerra seminano morte e distruzione lungo la loro folle  corsa. Questi carri formidabili, mai visti prima, sono guidati dai guerrieri  Hyksos. Le nuvole della tempesta sono già state avvistate all'orizzonte e tu  devi prepararti ad affrontare il pericolo imminente."
        }
    }
    message_mission_hermopolis {
        id: 432,
        type: 3,
        size [40, 30]
        title {
            text: "Hermopolis",

        }
        subtitle {
            text: "L'Egitto riconquistato",

        }
        content {
            text: "Potente faraone, l'Egitto urla la sua richiesta d'aiuto. I minacciosi  Hyksos hanno invaso la nostra terra e stabilito la loro capitale a Avaris. Da  qui, hanno interrotto molte delle nostre vie commerciali, impedendo l'afflusso  dei rifornimenti. Dobbiamo fermarli prima che sia troppo tardi. @PSe ti aggrada, grande faraone, possiamo riprendere la città di Hermopolis, che  è stata violata dagli invasori. Dobbiamo anche radunare un grande esercito e una  grande flotta, dato che dovremo inviare truppe e provviste verso i nostri  compatrioti del nord, specialmente verso Avaris, per aiutarla a respingere le  incursioni degli Hyksos. Molti si rivolgeranno a te, figlio di Ra, per chiedere  aiuto. E ora anche noi abbiamo una nuova arma. I nostri saggi capi militari  hanno imparato a utilizzare il carro da guerra e ora siamo pronti per assalire  il nemico e scacciarlo. Dopo aver allontanato i pericolosi Hyksos, il nostro  supervisore militare raccomanda la costruzione di un forte nel Sinai a Sharuhen,  per impedire un'ulteriore invasione dall'est. @PMa il pericolo non è individuabile solo nel nord! Alcuni rapporti dal confine  meridionale ci informano che i Nubiani sfruttano di nuovo un nostro momento di  debolezza. Hanno riconquistato le città di Mirgissa e Semna. Anche se la  situazione a sud è preoccupante, dobbiamo prima scacciare gli Hyksos. @PGli Hyksos sono invasori sacrileghi. Abbiamo appena scoperto che hanno violato  la piramide di Hermopolis. Hanno rubato tutti gli arredi sacri necessari al  faraone lì sepolto. Dobbiamo inviare altri arredi funebri così che al faraone  non manchi più nulla nell'aldilà."
        }
    }
    message_mission_lykopolis {
        id: 433,
        type: 3,
        size [40, 30]
        title {
            text: "Lykopolis",

        }
        subtitle {
            text: "L'Egitto riconquistato",

        }
        content {
            text: "O Re delle Due Terre, l'Egitto urla la sua richiesta d'aiuto. I  pericolosi Hyksos hanno invaso la nostra terra e hanno stabilito la loro  capitale a Avaris. Da Avaris, hanno interrotto molte delle nostre vie  commerciali impedendo l'afflusso dei rifornimenti. Dobbiamo fermarli prima che  sia troppo tardi. @PQui a Lykopolis, siamo al sicuro da attacchi immediati, anche se gli Hyksos  osano chiederci tributi. Sarà necessario disporre di truppe e armi da inviare ai  nostri compatrioti del nord per aiutarli a respingere le incursioni degli  Hyksos. Molti si rivolgeranno a te, figlio di Ra, per chiedere aiuto. E ora  anche noi abbiamo una nuova arma. I nostri saggi capi militari hanno imparato a  utilizzare il carro da guerra e ora possiamo assalire il nemico e scacciarlo. @PMa il pericolo non è individuabile solo nel nord! Alcuni rapporti dal confine  meridionale ci informano che i Nubiani sfruttano di nuovo un nostro momento di  debolezza. Hanno riconquistato le città di Mirgissa e Semna. @PAffinché l'Egitto sopravviva in questo periodo turbolento, i nostri generali e  ammiragli dovranno dare il massimo. Per ispirare i due migliori di loro, hai  promesso di costruire due piramidi possenti quanto la tua. Con la tua promessa  nel cuore, ora combattono il nemico con grande coraggio e con tutte le proprie  forze.   @PSe ti aggrada, potente faraone, puoi costruire tre magnifiche piramidi a  Lykopolis, una per te e le altre due per i tuoi generali. Le tre piramidi  occuperanno molto spazio; quindi, dovrai fare a meno di qualche risorsa per  erigerle. Inoltre, dovrai estendere i confini della città oltre il Nilo per  recuperare i beni necessari a una città sempre più prospera."
        }
    }
    message_mission_byblos {
        id: 434,
        type: 3,
        size [40, 30]
        title {
            text: "Byblos",

        }
        subtitle {
            text: "Espansione e conquista",

        }
        content {
            text: "L'Egitto è risorto dal precedente periodo buio con un nuovo vigore.  Byblos, con le sue verdi foreste e ricche miniere di rame, è finalmente nostra!  Con la tua presenza, la città prospererà sicuramente e riusciremo a fondare un  Nuovo Regno. @PAh, ma quale allarmante scoperta abbiamo effettuato dopo la conquista di  Byblos! Un nuovo e feroce popolo, gli Ittiti, ha invaso gran parte dell'Asia e  alcuni dicono che il loro impero sia potente quanto il nostro. Ora hanno rivolto  l'attenzione verso Byblos, desiderosi delle sue ricchezze. Se non ci prepareremo  al loro attacco, potremmo perdere tale splendida città.  @PDurante la preparazione alla guerra, dobbiamo anche palesare il potere egizio  su Byblos. Con la tua benedizione, o faraone, erigeremo tre obelischi, uno più  grande degli altri due, che proclamino il tuo dominio e la tua gloria fino ai  confini dell'impero. Questi spettacolari monumenti ricorderanno ai cittadini chi  è il loro signore. @PMentre ci occuperemo di Byblos, altre regioni egizie saranno esposte a  ulteriori attacchi. I Nubiani si sono spostati a nord, fino alla prima cataratta  e noi dobbiamo aiutare i nostri compatrioti a scacciarli. Alcuni rapporti da  Avaris citano un nuovo misterioso nemico, il Popolo del Mare: devono essere  abbattuti. Per mostrare la tua potenza, prepara truppe e navi da guerra da  inviare in caso di necessità."
        }
    }
    message_mission_kuban {
        id: 435,
        type: 3,
        size [40, 30]
        title {
            text: "Kuban",

        }
        subtitle {
            text: "La gloria d'Egitto",

        }
        content {
            text: "Con la cacciata degli Hyksos, la nostra terra assiste a una nuova  rinascita, un Nuovo Regno che offusca i passati splendori. Nobile faraone, Kuban  è un luogo ideale per dare inizio al Nuovo Regno. Da lì potremo usare i ricchi  depositi d'oro per dare corpo alla tua nuova visione dell'Egitto.  @PL'Egitto è al suo massimo splendore, ma restano alcuni noiosi problemi da  risolvere. Molte città del Regno stanno ancora cercando di risollevarsi dopo gli  attacchi degli Hyksos e potrebbero aver bisogno del tuo aiuto. In altre regioni,  i vecchi nemici dell'Egitto continuano ad attaccarci e un nuovo nemico, il  Popolo del Mare, ha iniziato le sue scorrerie sulla costa settentrionale. Devi  prepararti a difendere le città egizie dai nostri nemici, vecchi e nuovi. @PMan mano che l'Egitto cresce in potenza, molte città desiderano commerciare  con noi. Alcune di queste conoscono i nostri usi, fino a considerarsi egizie e  temono il nostro potere, mentre altre ci sono sconosciute e commerciano con noi  per la prima volta. Per la gloria d'Egitto, sfrutta tali relazioni per fornire  al nostro popolo tutto ciò di cui ha bisogno. @PPer varcare la soglia di una nuova era, i tuoi architetti reali desiderano  costruire per te due nuovi piramidi e un mausoleo, o faraone. Tali monumenti  riflettono certamente la grandiosità e la prosperità che hai conferito  all'Egitto."
        }
    }
    message_mission_avarist {
        id: 436,
        type: 3,
        size [40, 30]
        title {
            text: "Rowarty",

        }
        subtitle {
            text: "Il Popolo del Mare",

        }
        content {
            text: "O Horus dorato, il nostro dominio asiatico è forte e incontrastato e  i nostri confini si estendono nuovamente fino in Nubia. Ma i pericoli sulla  costa settentrionale continuano a crescere. Il Popolo del Mare è sempre più  aggressivo e continua a razziare le nostre città. Solo la presenza del faraone  potrà sconfiggere questi feroci avversari. Se ordini una flotta, supportata da  un forte esercito, riusciremo certamente a sconfiggere il Popolo del Mare. @PMentre ti occupi del Popolo del Mare, i tuoi coraggiosi Nomarchi portano  attacchi in tutto il mondo. Se avranno successo, l'Egitto dominerà il mondo dal  grande fiume Eufrate fino alla città kushita di Kerma, a sud. Quando tu e i tuoi  Nomarchi otterrete la vittoria, la tua dinastia sarà ricordata come la più  grande di tutti i tempi. @PLa tua fama sconfinata ci ha fatto guadagnare un nuovo centro commerciale,  Micene. Il re di questa città ha appreso dello splendore dell'Egitto e desidera  commerciare con noi. Se vuoi aprire questa nuova via commerciale, o faraone, i  tuoi cittadini potranno ottenere i beni più lussuosi ed esotici che abbiano mai  visto. @PPer ospitare la tua famiglia nell'aldilà, occorre costruire un possente  mausoleo e una coppia di gigantesche piramidi di mattoni. Questi monumenti  ricorderanno a tutti la tua potenza e le opere non solo sul campo di battaglia."
        }
    }
    message_mission_kahun {
        id: 437,
        type: 3,
        size [40, 30]
        title {
            text: "Kahun",

        }
        subtitle {
            text: "La Gloria del faraone",

        }
        content {
            text: "Benevolo faraone, tu hai portato la pace e la prosperità in tutta la  nazione. Sotto il tuo saggio governo, l'Egitto è di nuovo un paese forte e  glorioso. Tutti i Nomarchi ti sono fedeli e il nostro paese non soffre più  alcuna minaccia. @POra che hai compiuto ciò che la tua famiglia desiderava da generazioni, è il  tempo di commemorare le grandi opere della tua nobile dinastia. L'unico modo per  farlo è quello di costruire la più imponente piramide di tutto l'Egitto, più  grande persino di quella di Khufu, a Giza. Altri della tua famiglia si sono  sacrificati, lungo il cammino verso la gloria. Anche loro devono essere  ricordati e onorati, con un mausoleo di arenaria per ringraziarli del loro  incrollabile supporto. @LIl luogo ideale per tali monumenti è Kahun, nella ricca regione di Fayuum. Da  qui, mentre costruisci la grande piramide, puoi gestire tutti gli affari di  stato e rispondere alle eventuali richieste effettuate dalle città del Regno."
        }
    }
    message_mission_buto {
        id: 438,
        type: 3,
        size [40, 30]
        title {
            text: "Buto",

        }
        content {
            text: "@PCon l'aiuto della tua famiglia, il re Thinita Hor-Aha è riuscito a  unificare i due regni dell'Alto e del Basso Egitto, proclamandosi Faraone di  tutto l'Egitto e fondando la grande capitale a Men-nefer.    @PIl tuo clan si è nuovamente spostato, questa volta nelle aree paludose del  delta nel Basso Egitto, nella regione di Buto. Le navi da guerra Canaanite  minacciano il delta e presto verrà il momento di contrastarle con le tue. @PLa tua famiglia ha raggiunto lo stato di nobiltà. Come tale, prima di passare  da questo mondo all'al di là, dovrai costruire una tomba di famiglia - una  mastaba - per custodire il tuo corpo durante il viaggio nell'altro mondo. @PMa prima di tutto dovrai edificare alcune fattorie lungo le rive del Nilo, per  sfruttare il suolo reso fertile dagli straripamenti annuali. La tua popolazione  potrà così crescere e prosperare, fino a diventare abbastanza numerosa da  potersi cimentare nell'arduo compito di costruzione del sacro monumento. Fai  attenzione, i pericoli che si nascondono tra le acque benefiche del Nilo sono  molti: mortali coccodrilli, ippopotami e zanzare portatrici di malaria. @L@LLe coltivazioni lungo il Nilo  @PDovrai costruire le fattorie esattamente sui terreni inondati, così da  sfruttare al massimo i benefici del suolo fertilizzato dal Nilo. Diversamente  dalla maggior parte delle strutture di lavoro, le fattorie e le coltivazioni non  richiedono un accesso agli impiegati, piuttosto una forza lavoro stabile di  braccianti, forniti dai campi di lavoro, che si occupino dei campi. Costruisci i  campi di lavoro abbastanza vicini alle fattorie, così i contadini non dovranno  camminare troppo a lungo per raggiungerli. @G56 @L@LIl raccolto annuale @L@POgni anno, il Nilo inonda le sue rive, ricostituendo la fertilità del suolo  con il suo fango. I contadini raccolgono le messi appena prima dello  straripamento e, quindi, le portano ai tuoi granai. Dato che c'è un solo  raccolto all'anno, assicurati di avere abbastanza granai da conservare cibo  sufficiente per tutta la tua popolazione."
        }
    }
    message_mission_pi_yer {
        id: 439,
        type: 3,
        size [40, 30]
        title {
            text: "Pi-Yer",

        }
        subtitle {
            text: "L'arrivo del Popolo del mare",

        }
        content {
            text: "@PLe agitazioni sono sempre più frequenti e gravi in occidente.  Secondo gli esploratori, alcune tribù di barbari che parlano una lingua  incomprensibile, sono approdate alle spiagge occidentali della Cirenaica. Per di  più, essi sono diventati amici di Maraye, il figlio di Did, re dei Libici, i  primi nemici del Faraone. @PAl Faraone Merneptah è giunta voce che questi barbari presto si dirigeranno a  est, con donne, bambini e tutte le loro masserizie, verso il fertile delta del  Nilo (in pratica a casa nostra!) in cerca di un luogo in cui stabilirsi. Ci  sono già stati dei piccoli scontri presso le oasi settentrionali di Siwi e  Farafra. Sul loro cammino ora si trova la città di Pi-yer. In breve tempo questa  orda di selvaggi busserà alle nostre porte. Il Faraone ha deciso che, se  dovessero arrivare, occorre impedire che penetrino ulteriormente nel nostro  regno! @PDovrai importare il legno per costruire robuste navi da guerra e il rame per  fabbricare le armi. Per tua fortuna, gli Ittiti, tempo fa in agitazione, ora  vivono pacificamente, grazie alla grande vittoria a Qadesh di Ramses II, sire  dell'amato Merneptah. Fortifica la tua città e prepara le tue truppe a una  battaglia mortale."
        }
    }
    message_mission_migdol {
        id: 440,
        type: 3,
        size [40, 30]
        title {
            text: "Migdol",

        }
        subtitle {
            text: "Respingere gli Assiri",

        }
        content {
            text: "@PFin dai tempi del grande Shabaka, unificatore dell'Alto e Basso  Egitto e sire del Faraone Taharqa, il conflitto con gli Assiri non è mai  cessato. Fino alla sua morte, il Faraone Shabaka ha sempre creduto opportuno  aiutare i nostri fratelli in Palestina, che soffrivano sotto lo spietato regno  degli Assiri. Presta attenzione! I soldati del sacrilego re Asarhaddon sono di  nuovo in marcia e, come al solito, i loro occhi mirano alle fertili terre  dell'Egitto. Ora è il tuo momento di gloria! Come sindaco reale di Migdol,  dovrai difenderti da una serie di attacchi portati dai nostri maledetti  avversari. La tua fortezza si trova sulla parte orientale del delta del Nilo e  rappresenta una prima linea di difesa esterna. @PSarà estremamente importante addestrare i soldati e stabilire rapporti  commerciali per ottenere armi o materiali grezzi per fabbricarle. @PNon fallire! Una strenua difesa è fondamentale per assicurare l'indipendenza  dell'Egitto. Se riuscirai a resistere per soli sette anni, la vittoria sarà  assicurata. Taharqa, il grande Faraone, secondo figlio di Shabaka, ti guarderà  con attenzione!"
        }
    }
    message_mission_tanis {
        id: 441,
        type: 3,
        size [40, 30]
        title {
            text: "Tanis",

        }
        subtitle {
            text: "La rinascita della marina",

        }
        content {
            text: "@PPer molte generazioni gli Egizi hanno sofferto la prepotenza della  Persia. Ma il dominio di Babilonia sulle nostre terre non è più forte come una  volta. Mentre i nostri maledetti oppressori sono stati occupati in faccende  politiche con la Grecia, una serie di rivolte in Egitto hanno allentato la presa  degli odiati Persiani. Ora però, al Faraone Achoris è giunta voce che una flotta  comandata dall'ammiraglio Conon (un Greco prezzolato dai Persiani) è stata  inviata da Artaserse II ed è diretta ai nostri lidi. Il Faraone Achoris ha  saggiamente deciso che occorre una forte presenza navale sul Nilo per  scongiurare l'incursione. Come governatore reale di Tanis per i prossimi dieci  anni, devi costruire navi robuste e addestrare le truppe per controbattere gli  attacchi dal mare e dalla terraferma. @PDovrai stabilire un rapporto commerciale con Enkomi e importare legno robusto  per costruire una flotta. Da Enkomi, sull'isola di Cipro, puoi importare anche  il rame. Questa rotta commerciale non è sicura, dato che corre lungo la costa  levantina, sotto il controllo del nostro nemico. Fornendo al Faraone il  materiale richiesto, riuscirai anche ad aumentare i tuoi guadagni. @PMa sappi che in questi tempi pericolosi i fondi sono limitati. Per riuscire,  devi condurre i tuoi affari con saggezza e comandare le tue truppe con molta  abilità."
        }
    }
    message_mission_alexandria_2 {
        id: 442,
        type: 3,
        size [40, 30]
        title {
            text: "Alessandria",

        }
        subtitle {
            text: "Alessandro Magno",

        }
        content {
            text: "@PIl grande Alessandro, figlio di Filippo II di Macedonia e flagello  dell'impero babilonese, ha onorato le terre d'Egitto con la sua presenza. Con la  sua venuta, l'ultimo corrotto satrapo persiano è fuggito all'istante. Dopo aver  condotto il suo sacrificio ad Apis presso Memphis, Alessandro è stato accettato  come Faraone. La gente è al colmo della gioia! Prima di partire per il suo  viaggio verso l'oracolo di Amun, nell'oasi di Siwi, il nostro capo ha deciso di  fondare una nuova città, destinata a diventare la capitale del suo vasto impero  in perenne espansione. Nella sua infinita saggezza, ti ha nominato sindaco di  questa futura città! @PIl grande Alessandro ti ha concesso un capitale generoso per iniziare la  costruzione e ti ha accreditato i servizi del famoso architetto greco  Dinocrates. Entro dodici anni, si aspetta che la potenza militare, commerciale e  culturale della città sia ai massimi livelli, in quanto per quel tempo ha deciso  di ritornare.  @PIl nostro capo ha inoltre tracciato la posizione delle due strade principali  della sua città. La strada Canopus corre da est a ovest; l'altra strada è  perpendicolare alla Canopus e si dirige nell'entroterra da Capo Lochias e verso  sud dal lago Mariut. @PCome fidato supervisore di questo progetto, devi costruire in fretta un porto  e stabilire vie commerciali per guadagnare altri fondi. Devono esserci molti  clienti per i nostri prodotti, specialmente per il grano, l'orzo, il papiro e la  tela. Non tralasciare gli aspetti culturali di questa città, né quelli militari,  dato che ancora ci sono dei vandali che vagano per l'Egitto cercando di  depredarlo delle sue ricchezze."
        }
    }
    message_mission_ptolemy_alexandria {
        id: 443,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alessandria di Tolomeo",

        }
        subtitle {
            text: "Un raggio di luce",

        }
        content {
            text: "@PIl retaggio di Alessandro Magno vive tuttora nella nostra  orgogliosa città. Anche se i suoi resti mortali riposano nel mausoleo di  Alessandria, la sua grande città continua a prosperare. Ora spetta a te, Tolomeo  I Soter, portare avanti il compito iniziato dal nobile Alessandro. Dal tempo  della sua fondazione, circa 30 anni fa, la città è diventata un potente centro  commerciale, in grado di fornire cibo e beni di lusso a tutta l'area  circostante. Per continuare il progresso economico e per assicurare un passaggio  sicuro alle molte navi che entrano nella grande baia, devi costruire un grande  faro sull'isola di Pharos, vicino all'entrata della baia. Il raggio di luce  proiettato da questa struttura guiderà le navi distanti dalla costa verso la  baia, evitando che si schiantino contro le barriere di sabbia. @PPer quanto il commercio sia importante, comunque, non puoi ignorare gli  obiettivi intellettuali e culturali della nostra società. Sotto il tuo comando,  ora Alessandria può diventare la capitale intellettuale di tutto il mondo  conosciuto. Raccogli le opere di conoscenza dalle terre vicine e lontane e  costruisci una grande biblioteca per custodirle. Come le formiche sono attirate  dal miele, così gli studiosi di tutto il mondo giungeranno presso il nostro  incomparabile centro di conoscenza e istruzione.   @PPer costruire questi grandi monumenti dovrai importare i materiali da  costruzione, come il marmo bianco, adatti a queste grandi strutture. Enkomi,  sull'isola di Cipro, è un luogo ideale per recuperarli. @PInfine, non trascurare l'aspetto militare. Le agitazioni e le incursioni  possono avvenire in qualsiasi luogo. Potrebbe essere necessario inviare truppe  presso frontiere lontane, per proteggere gli interessi dell'Egitto e il suo  onore."
        }
    }
    message_mission_maritis {
        id: 444,
        type: 3,
        size [40, 30]
        title {
            text: "Maritis",

        }
        subtitle {
            text: "Cesare e Cleopatra",

        }
        content {
            text: "@PL'indelicata oppressione dell'impero romano diventa ogni giorno più  massiccia e dilaga senza sosta. La nostra terra è stata invasa anche dai terribili dissidi politici di Roma. Con il recente assassinio di Pompeo sulle spiagge d'Egitto, Giulio Cesare ha ora il completo controllo delle possenti legioni  romane, egli ha volto le sue mire alle ricchezze d'Egitto e alla bellezza del  nostro fuggevole Faraone, Cleopatra VII, figlia di Aulete. Il nostro  astuto comandante è difficile da battere sul campo dell'intelligenza. Se Cesare  desidera usarla per aumentare l'influenza di Roma in Egitto, Cleopatra lo userà  a sua volta per mantenere il potere dinastico sul nostro impero. @PL'arrivo di Cesare ad Alessandria con i suoi impopolari Romani ha causato una  rivolta da parte dei suoi orgogliosi cittadini. Una folla di agitatori, condotta  dal fratello minore di Cleopatra, Tolomeo XIII, ha stretto Cesare nelle  residenze reali della città. Sono scoppiati scontri sanguinosi che hanno causato  numerose vittime. Nel tentativo di mantenere una via di fuga dal mare, Cesare ha  bruciato la flotta egizia mentre era all'ancora nella baia di Alessandria.  Purtroppo le fiamme si sono estese ai magazzini sulla spiaggia e hanno bruciato  grandi quantità di pergamene appartenenti alla grande biblioteca.   @PPer evadere dalla trappola in cui si trova, Cesare ha richiamato il fedele  Mitradate e le sue truppe dalla Siria, così che possa salvarlo. Dopo aver  distrutto la fortezza di Migdol, Mitradate ha proseguito in marcia forzata  attorno al delta del Nilo, per avvicinarsi ad Alessandria da sud est. Le sue  forze di punta al momento sono accampate vicino al piccolo villaggio di Maritis,  sulle sponde orientali del lago Mariut, e si stanno preparando all'ultima tappa  del loro viaggio.  @PIl terribile Tolomeo XIII ha saputo dell'arrivo dei rinforzi. Per tutta  risposta ha spostato il grosso della sua numerosa armata al confine sud- orientale di Alessandria. Si sta preparando una battaglia decisiva sulle sponde  orientali del lago Mariut. Riuscirai, comandando le legioni romane di Mitradate,  a sconfiggere l'esercito egizio ribelle di Tolomeo e raggiungere Cesare e  Cleopatra ad Alessandria? Il loro destino è nelle tue mani."
        }
    }
    message_mission_cleopatra_alexandria {
        id: 445,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alessandria di Cleopatra",

        }
        subtitle {
            text: "L'eredità di una regina",

        }
        content {
            text: "@PLa violenta morte di Cesare, per mano armata di un gruppo di  assassini, ha gettato il mondo romano nel caos e ti ha portato, nostro Faraone,  Cleopatra VII, al lutto e alla disperazione. Il tuo amato, mentore, confidente e  potente alleato non è più. Ottaviano, il suo giovane nipote d'adozione, è stato  nominato suo erede ma è Marco Antonio, l'esperto consigliere di Cesare,  l'attuale capo dello stato, cosa certo non gradita dal giovane Ottaviano.  Ovviamente, il testamento di Cesare non menzionava vostro figlio, Cesare  Tolomeo, da tutti conosciuto come Cesarione. Desiderando sicurezza per te stessa  e tuo figlio e cercando, come sempre, di mantenere il potere dell'Egitto, sei  partita da Roma alla volta di Alessandria. @PNonostante la grande distanza tra le due città, non puoi lasciarti alle spalle  le liti interne. Gli uomini potenti lottano per ottenere più potere - il tuo  supporto e disponibilità di ricchezze può essere di grande aiuto a qualsiasi  fazione. È molto importante che tu supporti un nuovo vincitore; se ti schieri  con un perdente, l'Egitto vedrebbe la sua fine. La drammatica conclusione tra le  fazioni romane rivali è da poco occorsa a Filippi, dove Marco Antonio ha  sconfitto una volta per tutte i suoi avversari Bruto e Cassio. Antonio,  Ottaviano e Lipido hanno costituito un triumvirato spartendosi il regno: Antonio  ha scelto la porzione orientale che contiene l'Egitto. @PPoco tempo dopo la battaglia, Marco Antonio ti ha convocato a Tarso, in Asia  Minore, così che tu possa spiegargli perché hai impiegato tutto questo tempo per  schierarti con i Cesariani. Non sei abituata a lasciarti comandare come un cane  fedele, quindi hai rifiutato di rispondere. Dopo tutto, sai meglio di chiunque  altro che è bene incontrarsi con i Romani alle proprie condizioni! @PE così tu, Faraone Cleopatra, sei ritornata a casa, ad Alessandria d'Egitto.  Ora è il momento di estendere la gloria di questa magnifica città, fondata da  Alessandro Magno, la cui tomba è ancora affollata meta di numerosi visitatori.  La famosa biblioteca di Alessandria continua ad attirare studiosi di tutto il  mondo; il potente raggio di luce del Faro del Faraone fende tuttora la notte e  guida i navigatori attraverso le infide acque della baia. Ora puoi rinvigorire  la bellezza della città costruendo un grande Caesareum in onore del tuo  precedente amante e di tuo figlio. In più, devi assicurare il tuo passaggio  nell'aldilà costruendo un altro mausoleo, così che tu possa essere degnamente  onorata dopo il lungo viaggio nei Campi di Canne. @PSe Marco Antonio ti dovesse chiamare un'altra volta, mostrerai un po' più di  tatto?"
        }
    }
    message_mission_actium {
        id: 446,
        type: 3,
        size [40, 30]
        title {
            text: "Actium",

        }
        subtitle {
            text: "Antonio e Cleopatra",

        }
        content {
            text: "@POh nobile Faraone Cleopatra VII, consorte di Cesare e ora di  Antonio, il destino d'Egitto è nelle tue mani, ma le tue mani ora cercano quelle  di un Romano, Marco Antonio - ed egli è completamente preso dalla lotta per il  controllo di Roma e delle sue legioni.   @POccorrendogli le vaste ricchezze egizie, ma desiderando anche il tuo amore e  affetto, Antonio ha acconsentito di sposarti. Sfortunatamente, tale notizia ha  scandalizzato Roma! Come ben sapevi, Antonio era ancora sposato con Ottavia,  sorella di Ottaviano, vero erede di Cesare e, con Antonio, potere supremo di  Roma. Ma dopo la notizia sulle tendenze poligame di Antonio, questa relazione è  diventata insostenibile. Ottaviano pensa che Antonio abbia disonorato sua  sorella, con tutta la famiglia, e il prestigio di Roma. Per sistemare questa  faccenda d'onore e per terminare la lotta di potere che sconvolge Roma,  Ottaviano ha sfidato in battaglia il tuo amato Antonio. Con questo pensiero in  mente, Antonio, insieme a te e accompagnato dalla flotta egizia, si è accampato  in Grecia vicino ad Actium. Questo luogo offre un buon punto di ancoraggio e di  riparo per le navi.   @PDevi costituire in fretta un esercito, soprattutto navale. Ottaviano ha  giurato di tornare nel settembre dell'anno 31. @POra il tuo fato, quello di Marco Antonio, dell'Egitto e di Roma dipendono  dalla potenza delle armate."
        }
    }
    message_mission_thutmose_valley {
        id: 447,
        type: 3,
        size [40, 30]
        title {
            text: "Thutmose nella Valle",

        }
        subtitle {
            text: "La prima tomba",

        }
        content {
            text: "@PDopo molte vittorie in terre lontane in difesa degli Egizi, il  Faraone Thutmose, come gli altri prima di lui, sta pensando alla preparazione  per il suo viaggio nell'aldilà. Per assicurarsi un viaggio coronato dal  successo, il Faraone desidera che tu inizi la costruzione della sua tomba il più  presto possibile. Costruisci un villaggio sulla sponda occidentale del Nilo per  creare un bacino di forza lavoro. Individua un luogo opportuno per la sua tomba,  tra le rupi a occidente del villaggio. Ti occorreranno abili scalpellini per  ricavare le varie stanze dalla viva roccia, e artigiani di talento per decorare  e dipingere la tomba reale. @PPer fornire la luce agli uomini che lavorano sotto terra dovrai creare delle  fabbriche di lampade. Rifornisci tali fabbriche con il vasellame e olio di  importazione da usare come combustibile. Pianta campi di henna per ottenere le  pitture che useranno gli artigiani."
        }
    }
    message_mission_tutankhamun_valley {
        id: 448,
        type: 3,
        size [40, 30]
        title {
            text: "Tut nella Valle",

        }
        subtitle {
            text: "La morte di Tutankhamun",

        }
        content {
            text: "@PUna terribile tragedia ha colpito il nostro tanto amato quanto  giovane Faraone Tutankhamun! Il suo regno, da subito destinato a grande gloria,  è stato impietosamente stroncato dalla mano del fato. I lavoratori di Deir el- Medina devono nuovamente preparare il luogo di riposo eterno per il Faraone.  Data la morte prematura, è fondamentale che tu sproni i lavoratori affinché si  impegnino al massimo. La tomba di Tuthankhamen deve essere rifornita per il  viaggio nell'aldilà e pronta per ricevere le spoglie regali entro pochi anni. La  velocità è estremamente importante!"
        }
    }
    message_mission_seti_valley {
        id: 449,
        type: 3,
        size [40, 30]
        title {
            text: "Seti nella Valle",

        }
        subtitle {
            text: "Una tomba per il Faraone",

        }
        content {
            text: "@PIl nostro potente Faraone Seti, figlio di Ramses I, ha deciso che ora è il momento di prepararsi per il suo viaggio  nell'aldilà. Per questa ragione dovrai iniziare gli scavi della tomba reale  nella Valle dei Re. I lavoratori non devono risparmiare alcuno sforzo. Occorre  prendere misure adeguate per assicurare che questa nuova opera d'arte non abbia  paragoni per molti secoli a venire. @PMentre la costruzione del progetto reale è in corso, devi anche occuparti dei  vandali! Ci sono già state delle voci che denunciano bande di avidi criminali  che intendono arricchirsi depredando le tombe e disturbando la pace eterna dei  Faraoni d'Egitto. Non permettere che tali sacrilegi macchino le tombe reali  della Valle, altrimenti la considerazione che il regno ha di te ne soffrirà  alquanto."
        }
    }
    message_mission_sumur {
        id: 450,
        type: 3,
        size [40, 30]
        title {
            text: "Sumur",

        }
        subtitle {
            text: "Terre levantine",

        }
        content {
            text: "@PSalute a te governatore reale, reggente levantino e fedele  servitore del nostro Faraone, figlio di Ra. Siamo tutti fortunati a vivere in  questi tempi in cui il benevolo abbraccio d'Egitto si estende dalla lontana  Nubia fino alle terre levantine. Infinita è la saggezza del nostro nuovo  Faraone, il nobile Ramses II, e grande è la sua visione, in quanto egli stesso  ti ha inviato a governare queste splendide terre, ora sotto il dominio egizio.  @PQuesta regione, anche se minacciata da molti pericoli, possiede molte  ricchezze da sfruttare. Le verdi colline sono costellate di alberi, il cui legno  è il materiale ideale per fabbricare carri e da impiegare in ogni tipo di  costruzione. La stessa cosa vale per il rame, anche se non così abbondante, che  può essere utilizzato per fabbricare armi robuste. Legno e rame, così rari nella  nostra madre patria, saranno certo benvenuti una volta spediti in grande  quantità. Spetta a te dunque costruire un grande porto commerciale grazie al  quale esportare questi beni fondamentali. Il Faraone e tutti gli Egizi te ne  saranno estremamente grati! @PMa fai attenzione! Assicurati che i tuoi soldati siano equipaggiati con carri  e armi robuste, gli Ittiti, anche se battuti da Seti, padre dell'attuale  Faraone, sono ancora pericolosi e possono sfidare la nostra autorità in questa  ricca terra. Per sedare le ribellioni occorre una forte presenza militare, per  altro utile anche in futuro. @PInfine, per ricordare alle genti di queste terre a chi devono rendere omaggio,  il faraone Ramses II ritiene opportuno che tu eriga un obelisco che celebri la  sua gloria."
        }
    }
    message_mission_qadesh {
        id: 451,
        type: 3,
        size [40, 30]
        title {
            text: "Qadesh",

        }
        subtitle {
            text: "La battaglia di Qadesh",

        }
        content {
            text: "@PLa terra di Amurra, vicina alla costa levantina, trema sotto gli  zoccoli e i piedi delle tue potenti legioni, nobile Faraone. Questa regione è  tanto ricca di risorse quanto di discordie. Le armate Ittite, guidate dal  perfido re Mutwatalli, ancora una volta cercano di contrastare il nostro dominio  in questa terra, nostra per diritto. Le spie catturate ci hanno detto che i  soldati sono ancora lontani, a nord, e per ora non presentano alcun pericolo. Ma  dobbiamo crederlo? Il guerriero saggio non abbandona mai lo scudo in battaglia. @PPer sedare eventuali ribellioni tu, nobile Faraone Ramses II, figlio di Ra,  sei arrivato alla città fortificata di Qadesh. Presso di essa si trovano già due  accampamenti di temibili carri da guerra. Ma non solo. Ai tuoi comandi si  trovano altre truppe di veterani - i soldati recentemente impiegati vicino a  Sumur. Ma fai attenzione! Forse è meglio ritardare il loro schieramento finché  la situazione non lo richieda: saggio è il guerriero che può contare su soldati  fidati al culmine della battaglia. @PQuando il nemico sarà sconfitto, sarà necessario rinforzare la stagnante  economia di Qadesh così che anch'essa possa contribuire alla gloria d'Egitto.  Estrai le gemme, assumi abili gioiellieri e fabbrica oggetti preziosi per tutti  i fedeli servitori del Faraone. Beni di lusso di così rara bellezza saranno  certo richiesti!"
        }
    }
    message_mission_abu_simbel {
        id: 452,
        type: 3,
        size [40, 30]
        title {
            text: "Abu Simbel",

        }
        subtitle {
            text: "I colossi di Abu Simbel",

        }
        content {
            text: "@PLa gloria del nostro Faraone, Ramses II, pervade l'Egitto. Affinché  l'eredità del suo regno viva per sempre, è stato deciso di costruire in Nubia un  grande monumento e un tempio in suo onore – e il Faraone stesso ha scelto un  luogo ideale per tale immensa costruzione. Dovrai supervisionare la costruzione  di quattro enormi statue sedute che raffigurano sua maestà, con l'arenaria  rosata delle sponde occidentali del Nilo, ad Abu Simbel. Le pareti del  monumento, intagliate nella viva roccia, proclameranno le eroiche gesta del  Faraone nel suo grande trionfo a Qadesh. Questo enorme monumento, oltre a  celebrare le imprese del nostro capo supremo, servirà anche a ricordare alle  genti della Nubia la grandezza e la potenza dell'Egitto, in quanto, anche se la  Nubia è ricca d'oro e altre rare gemme, il suo popolo non ha mai gradito la  sottomissione al dominio egizio. Per questo motivo dovrai sempre essere pronto a  difenderti e in grado di inviare delle truppe se il Faraone dovesse richiederle. @PL'arenaria può essere esportata in altre parti del regno, così come tutti gli  altri beni e materiali che riuscirai a produrre sfruttando le abbondanti risorse  della regione. Tuttavia, troverai ben poco legno. Senza dubbio dovrai stabilire  una via commerciale per importarlo, in quanto servirà per le grandi impalcature  necessarie alla costruzione dell'immenso monumento."
        }
    }
    message_mission_ramses_valley {
        id: 453,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses nella Valle",

        }
        subtitle {
            text: "Una tomba impareggiabile",

        }
        content {
            text: "@PSono trascorsi molti e gloriosi anni da quando il nostro Faraone,  il nobile Ramses II, ha accettato le insegne del comando da suo padre, Seti I.  Con la benedizione di Ra, continuerà a regnare ancora per molto tempo. Tuttavia,  è giunto il momento di iniziare gli scavi e preparare il luogo dell'eterno  riposo per il nostro capo supremo. Egli ha fornito all'architetto reale un  progetto per la tomba più grande mai costruita, superiore persino a quella del  suo sire. Ora tocca a te assicurare che le sue richieste siano soddisfatte. @PFai attenzione! Tra i lavoratori e gli schiavi, locali e in tutto il Basso  Egitto, serpeggia il sentimento della rivolta. Essi seguono un uomo cresciuto  alla corte del nostro Faraone e hanno minacciato di chiedere l'intervento del  loro dio. Grazie all'aiuto divino, essi sperano di fuggire. Proprio in questo  momento, i sacerdoti e gli uomini di religione stanno discutendo la pericolosità  di tale minaccia. Mentre attendiamo con pazienza la loro valutazione, è comunque  prudente prepararsi al peggio."
        }
    }
    message_mission_pi_yer_2 {
        id: 454,
        type: 3,
        size [40, 30]
        title {
            text: "Pi-Yer",

        }
        subtitle {
            text: "L'arrivo del Popolo del Mare",

        }
        content {
            text: "@PLe agitazioni sono sempre più frequenti e gravi in occidente.  Secondo gli esploratori, alcune tribù di barbari, che parlano una lingua  incomprensibile, sono approdate alle spiagge occidentali della Cirenaica. Per di  più, essi sono diventati amici di Maraye, il figlio di Did, re dei Libici, i  primi nemici del Faraone. @PAl Faraone Merneptah è giunta voce che questi barbari presto si dirigeranno a  est, con donne, bambini e tutte le loro masserizie, verso il fertile delta del  Nilo (in pratica a casa nostra!) in cerca di un luogo in cui stabilirsi. Ci  sono già stati dei piccoli scontri presso le oasi settentrionali di Siwi e  Farafra. Sul loro cammino ora si trova la città di Pi-yer. In breve tempo questa  orda di selvaggi busserà alle nostre porte. Il Faraone ha deciso che, se  dovessero arrivare, occorre impedire che penetrino ulteriormente nel nostro  regno! @PDovrai importare il legno per costruire robuste navi da guerra e il rame per  fabbricare le armi. Per tua fortuna, gli Ittiti, tempo fa in agitazione, ora  vivono pacificamente, grazie alla grande vittoria a Qadesh di Ramses II, sire  dell'amato Merneptah. Fortifica la tua città e prepara le tue truppe a una  battaglia mortale."
        }
    }
    message_mission_pelusium {
        id: 455,
        type: 3,
        size [40, 30]
        title {
            text: "Pelusium",

        }
        subtitle {
            text: "Respingere gli Assiri",

        }
        content {
            text: "@PFin dai tempi del grande Shabaka, unificatore dell'Alto e Basso  Egitto e sire del Faraone Taharqa, il conflitto con gli Assiri non è mai  cessato. Fino alla sua morte, il Faraone Shabaka ha sempre creduto opportuno  aiutare i nostri fratelli in Palestina, che soffrivano sotto lo spietato regno  degli Assiri. Presta attenzione! I soldati del sacrilego re Asarhaddon sono di  nuovo in marcia e, come al solito, i loro occhi mirano alle fertili terre  dell'Egitto. Ora è il tuo momento di gloria! Come sindaco reale di Pelusium,  dovrai difenderti da una serie di attacchi portati dai nostri maledetti  avversari. La tua fortezza si trova sulla parte orientale del delta del Nilo e  rappresenta una prima linea di difesa esterna. @PSarà estremamente importante addestrare i soldati e stabilire rapporti  commerciali per ottenere armi o materiali grezzi per fabbricarle. @PNon fallire! Una strenua difesa è fondamentale per assicurare l'indipendenza  dell'Egitto. Se riuscirai a resistere per soli sette anni, la vittoria sarà  assicurata. Taharqa, il grande Faraone, secondo figlio di Shabaka, ti guarderà  con attenzione!"
        }
    }
    message_mission_tanis_2 {
        id: 456,
        type: 3,
        size [40, 30]
        title {
            text: "Tanis",

        }
        subtitle {
            text: "La rinascita della marina",

        }
        content {
            text: "@PPer molte generazioni gli Egizi hanno sofferto la prepotenza della  Persia. Ma il dominio di Babilonia sulle nostre terre non è più forte come una  volta. Mentre i nostri maledetti oppressori sono stati occupati in faccende  politiche con la Grecia, una serie di rivolte in Egitto hanno allentato la presa  degli odiati Persiani. Ora però, al Faraone Achoris è giunta voce che una flotta  comandata dall'ammiraglio Conon (un Greco prezzolato dai Persiani) è stata  inviata da Artaserse II ed è diretta ai nostri lidi. Il Faraone Achoris ha  saggiamente deciso che occorre una forte presenza navale sul Nilo per  scongiurare l'incursione. Come governatore reale di Tanis per i prossimi dieci  anni, devi costruire navi robuste e addestrare le truppe per controbattere gli  attacchi dal mare e dalla terraferma. @PDovrai stabilire un rapporto commerciale con Enkomi e importare legno robusto  per costruire una flotta. Da Enkomi, sull'isola di Cipro, puoi importare anche  il rame. Questa via commerciale non è sicura, dato che corre lungo la costa  levantina, sotto il controllo del nostro nemico. Fornendo al Faraone il  materiale richiesto, riuscirai anche ad aumentare i tuoi guadagni. @PMa sappi che in questi tempi pericolosi i fondi sono limitati. Per riuscire,  devi condurre i tuoi affari con saggezza e comandare le tue truppe con molta  abilità."
        }
    }
    message_mission_alexandria {
        id: 457,
        type: 3,
        size [40, 30]
        title {
            text: "Alessandria",

        }
        subtitle {
            text: "Alessandro Magno",

        }
        content {
            text: "@PIl grande Alessandro, figlio di Filippo II di Macedonia e flagello  dell'impero babilonese, ha onorato le terre d'Egitto con la sua presenza. Con la  sua venuta, l'ultimo corrotto satrapo persiano è fuggito all'istante. Dopo aver  condotto il suo sacrificio ad Apis presso Memphis, Alessandro è stato accettato  come Faraone. La gente è al colmo della gioia! Prima di partire per il suo  viaggio verso l'oracolo di Amun, nell'oasi di Siwi, il nostro capo ha deciso di  fondare una nuova città, destinata a diventare la capitale del suo vasto impero  in perenne espansione. Nella sua infinita saggezza, ti ha nominato sindaco di  questa futura città! @PIl grande Alessandro ti ha concesso un capitale generoso per iniziare la  costruzione e ti ha accreditato i servizi del famoso architetto greco  Dinocrates. Entro dodici anni, si aspetta che la potenza militare, commerciale e  culturale della città sia ai massimi livelli, in quanto per quel tempo ha deciso  di ritornare.  @PIl nostro capo ha inoltre tracciato la posizione delle due strade principali  della sua città. La strada Canopus corre da est a ovest; l'altra strada è  perpendicolare alla Canopus e si dirige nell'entroterra da Capo Lochias e verso  sud dal lago Mariut. @PCome fidato supervisore di questo progetto, devi costruire in fretta un porto  e stabilire rotte commerciali per guadagnare altri fondi. Devono esserci molti  clienti per i nostri prodotti, specialmente per il grano, l'orzo, il papiro e la  tela. Non tralasciare gli aspetti culturali di questa città, né quelli militari,  dato che ancora ci sono dei vandali che vagano per l'Egitto cercando di  depredarlo delle sue ricchezze."
        }
    }
    message_mission_ptolemy_alexandria_2 {
        id: 458,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alessandria di Tolomeo",

        }
        subtitle {
            text: "Un raggio di luce",

        }
        content {
            text: "@PIl retaggio di Alessandro Magno vive tuttora nella nostra  orgogliosa città. Anche se i suoi resti mortali riposano nel mausoleo di  Alessandria, la sua grande città continua a prosperare. Ora spetta a te, Tolomeo  I Soter, portare avanti il compito iniziato dal nobile Alessandro. Dal tempo  della sua fondazione, circa 30 anni fa, la città è diventata un potente centro  commerciale, in grado di fornire cibo e beni di lusso a tutta l'area  circostante. Per continuare il progresso economico e per assicurare un passaggio  sicuro alle molte navi che entrano nella grande baia, devi costruire un grande  faro sull'isola di Pharos, vicino all'entrata della baia. Il raggio di luce  proiettato da questa struttura guiderà le navi distanti dalla costa verso la  baia, evitando che si schiantino sulle barriere di sabbia. @PPer quanto il commercio sia importante, comunque, non puoi ignorare gli  obiettivi intellettuali e culturali della nostra società. Sotto il tuo comando,  ora Alessandria può diventare la capitale intellettuale di tutto il mondo  conosciuto. Raccogli le opere di conoscenza dalle terre vicine e lontane e  costruisci una grande biblioteca per custodirle. Come le formiche sono attirate  dal miele, così gli studiosi di tutto il mondo giungeranno presso il nostro  incomparabile centro di conoscenza e istruzione.   @PPer costruire questi grandi monumenti dovrai importare i materiali da  costruzione, come il marmo bianco, adatti a queste grandi strutture. Enkomi,  sull'isola di Cipro, è un luogo ideale per recuperarli. @PInfine, non trascurare l'aspetto militare. Le agitazioni e le incursioni  possono avvenire in qualsiasi luogo. Potrebbe essere necessario inviare truppe  presso frontiere lontane, per proteggere gli interessi dell'Egitto e il suo  onore."
        }
    }
    message_mission_maritis_2 {
        id: 459,
        type: 3,
        size [40, 30]
        title {
            text: "Maritis",

        }
        subtitle {
            text: "Cesare e Cleopatra",

        }
        content {
            text: "@PL'indelicata oppressione dell'impero romano diventa ogni giorno più  massiccia e dilaga senza sosta. La nostra terra è stata invasa anche dai terribili  dissidi politici di Roma. Con il recente assassinio di Pompeo sulle spiagge d'Egitto, Giulio Cesare ha ora il completo controllo delle possenti legioni  romane, egli ha volto le sue mire alle ricchezze d'Egitto e alla bellezza del  nostro fuggevole Faraone, Cleopatra VII, figlia di Tolomeo XII Aulete. Il nostro  astuto comandante è difficile da battere sul campo dell'intelligenza. Se Cesare  desidera usarla per aumentare l'influenza di Roma in Egitto, Cleopatra lo userà  a sua volta per mantenere il potere dinastico sul nostro impero. @PL'arrivo di Cesare ad Alessandria con i suoi impopolari Romani ha causato una  rivolta da parte dei suoi orgogliosi cittadini. Una folla di agitatori, condotta  dal fratello minore di Cleopatra, Tolomeo XIII, ha stretto Cesare nelle  residenze reali della città. Sono scoppiati scontri sanguinosi che hanno causato  numerose vittime. Nel tentativo di mantenere una via di fuga dal mare, Cesare ha  bruciato la flotta egizia mentre era all'ancora nella baia di Alessandria.  Purtroppo le fiamme si sono estese ai magazzini sulla spiaggia e hanno bruciato  grandi quantità di pergamene appartenenti alla grande biblioteca.   @PPer evadere dalla trappola in cui si trova, Cesare ha richiamato il fedele  Mitradate e le sue truppe dalla Siria, così che possa salvarlo. Dopo aver  distrutto la fortezza di Pelusium, Mitradate ha proseguito in marcia forzata  attorno al delta del Nilo, per avvicinarsi ad Alessandria da sud est. Le sue  forze di punta al momento sono accampate vicino al piccolo villaggio di Maritis,  sulle sponde orientali del lago Mariut, e si stanno preparando all'ultima tappa  del loro viaggio.  @PIl terribile Tolomeo XIII ha saputo dell'arrivo dei rinforzi. Per tutta  risposta ha spostato il grosso della sua numerosa armata al confine sud- orientale di Alessandria. Si sta preparando una battaglia decisiva sulle sponde  orientali del lago Mariut. Riuscirai, comandando le legioni romane di Mitradate,  a sconfiggere l'esercito egizio ribelle di Tolomeo e raggiungere Cesare e  Cleopatra ad Alessandria? Il loro destino è nelle tue mani."
        }
    }
    message_mission_cleopatra_alexandria_2 {
        id: 460,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alessandria di Cleopatra",

        }
        subtitle {
            text: "L'eredità di una regina",

        }
        content {
            text: "@PLa violenta morte di Cesare, per mano armata di un gruppo di  assassini, ha gettato il mondo romano nel caos e ti ha portato, nostro Faraone,  Cleopatra VII, al lutto e alla disperazione. Il tuo amato, mentore, confidente e  potente alleato non è più. Ottaviano, il suo giovane nipote d'adozione, è stato  nominato suo erede ma è Marco Antonio, l'esperto consigliere di Cesare,  l'attuale capo dello stato, cosa certo non gradita dal giovane Ottaviano.  Ovviamente, il testamento di Cesare non menzionava vostro figlio, Cesare  Tolomeo, da tutti conosciuto come Cesarione. Desiderando sicurezza per te stessa  e tuo figlio e cercando, come sempre, di mantenere il potere dell'Egitto, sei  partita da Roma alla volta di Alessandria. @PNonostante la grande distanza tra le due città, non puoi lasciarti alle spalle  le liti interne. Gli uomini potenti lottano per ottenere più potere - il tuo  supporto e disponibilità di ricchezze può essere di grande aiuto a qualsiasi  fazione. È molto importante che tu supporti un nuovo vincitore; se ti schieri  con un perdente, l'Egitto vedrebbe la sua fine. La drammatica conclusione tra le  fazioni romane rivali è da poco occorsa a Filippi, dove Marco Antonio ha  sconfitto una volta per tutte i suoi avversari Bruto e Cassio. Antonio,  Ottaviano e Lipido hanno costituito un triumvirato spartendosi il regno: Antonio  ha scelto la porzione orientale che contiene l'Egitto. @PPoco tempo dopo la battaglia, Marco Antonio ti ha convocato a Tarso, in Asia  Minore, così che tu possa spiegargli perché hai impiegato tutto questo tempo per  schierarti con i Cesariani. Non sei abituata a lasciarti comandare come un cane  fedele, quindi hai rifiutato di rispondere. Dopo tutto, sai meglio di chiunque  altro che è bene incontrarsi con i Romani alle proprie condizioni! @PE così tu, Faraone Cleopatra, sei ritornata a casa, ad Alessandria d'Egitto.  Ora è il momento di estendere la gloria di questa magnifica città, fondata da  Alessandro Magno, la cui tomba è ancora affollata meta di numerosi visitatori.  La famosa biblioteca di Alessandria continua ad attirare studiosi di tutto il  mondo; il potente raggio di luce del Faro del Faraone fende tuttora la notte e  guida i navigatori attraverso le infide acque della baia. Ora puoi rinvigorire  la bellezza della città costruendo un grande Caesareum in onore del tuo  precedente amante e di tuo figlio. In più, devi assicurare il tuo passaggio  nell'aldilà costruendo un altro mausoleo, così che tu possa essere degnamente  onorata dopo il lungo viaggio nei Campi di Canne. @PSe Marco Antonio ti dovesse chiamare un'altra volta, mostrerai un po' più di  tatto?"
        }
    }
    message_mission_actium_2 {
        id: 461,
        type: 3,
        size [40, 30]
        title {
            text: "Actium",

        }
        subtitle {
            text: "Antonio e Cleopatra",

        }
        content {
            text: "@POh nobile Faraone Cleopatra VII, consorte di Cesare e ora di  Antonio, il destino d'Egitto è nelle tue mani, ma le tue mani ora cercano quelle  di un Romano, Marco Antonio - ed egli è completamente preso dalla lotta per il  controllo di Roma e delle sue legioni.   @POccorrendogli le vaste ricchezze egizie, ma desiderando anche il tuo amore e  affetto, Antonio ha acconsentito di sposarti. Sfortunatamente, tale notizia ha  scandalizzato Roma! Come ben sapevi, Antonio era ancora sposato con Ottavia,  sorella di Ottaviano, vero erede di Cesare e, con Antonio, potere supremo di  Roma. Ma dopo la notizia sulle tendenze poligame di Antonio, questa relazione è  diventata insostenibile. Ottaviano pensa che Antonio abbia disonorato sua  sorella, con tutta la famiglia, e il prestigio di Roma. Per sistemare questa  faccenda d'onore e per terminare la lotta di potere che sconvolge Roma,  Ottaviano ha sfidato in battaglia il tuo amato Antonio. Con questo pensiero in  mente, Antonio, insieme a te e accompagnato dalla flotta egizia, si è accampato  in Grecia vicino ad Actium. Questo luogo offre un buon punto di ancoraggio e di  riparo per le navi.   @PDevi costituire in fretta un esercito, soprattutto navale. Ottaviano ha  giurato di tornare nel settembre dell'anno 31. @POra il tuo fato, quello di Marco Antonio, dell'Egitto e di Roma dipendono  dalla potenza delle armate."
        }
    }
    message_mission_deir_el_medina {
        id: 462,
        type: 3,
        size [40, 30]
        title {
            text: "Deir el Medina",

        }
        subtitle {
            text: "La prima tomba",

        }
        content {
            text: "@PDopo molte vittorie in terre lontane in difesa degli Egizi, il  Faraone Thutmose, come gli altri prima di lui, sta pensando alla preparazione  per il suo viaggio nell'aldilà. Per assicurarsi un viaggio coronato dal  successo, il Faraone desidera che tu inizi la costruzione della sua tomba il più  presto possibile. Costruisci un villaggio sulla sponda occidentale del Nilo per  creare un bacino di forza lavoro. Individua un luogo opportuno per la sua tomba,  tra le rupi a occidente del villaggio. Ti occorreranno abili scalpellini per  ricavare le varie stanze dalla viva roccia, e artigiani di talento per decorare  e dipingere la tomba reale. @PPer fornire la luce agli uomini che lavorano sotto terra dovrai creare delle  fabbriche di lampade. Rifornisci tali fabbriche con il vasellame e olio di  importazione da usare come combustibile. Pianta campi di henna per ottenere le  pitture che useranno gli artigiani."
        }
    }
    message_mission_tutankhamun_valley_2 {
        id: 463,
        type: 3,
        size [40, 30]
        title {
            text: "Tut nella Valle",

        }
        subtitle {
            text: "La morte di Tutankhamun",

        }
        content {
            text: "@PUna terribile tragedia ha colpito il nostro tanto amato quanto  giovane Faraone Tutankhamun! Il suo regno, da subito destinato a grande gloria,  è stato impietosamente stroncato dalla mano del fato. I lavoratori di Deir el- Medina devono nuovamente preparare il luogo di riposo eterno per il Faraone.  Data la morte prematura, è fondamentale che tu sproni i lavoratori affinché si  impegnino al massimo. La tomba di Tuthankhamen deve essere rifornita per il  viaggio nell'aldilà e pronta per ricevere le spoglie regali entro pochi anni. La  velocità è estremamente importante!"
        }
    }
    message_mission_seti_valley_2 {
        id: 464,
        type: 3,
        size [40, 30]
        title {
            text: "Seti nella Valle",

        }
        subtitle {
            text: "Una tomba per il Faraone",

        }
        content {
            text: "@PIl nostro potente Faraone Seti, figlio di Ramses I, ha deciso che ora è il momento di prepararsi per il suo viaggio  nell'aldilà. Per questa ragione dovrai iniziare gli scavi della tomba reale  nella Valle dei Re. I lavoratori non devono risparmiare alcuno sforzo. Occorre  prendere misure adeguate per assicurare che questa nuova opera d'arte non abbia  paragoni per molti secoli a venire. @PMentre la costruzione del progetto reale è in corso, devi anche occuparti dei  vandali! Ci sono già state delle voci che denunciano bande di avidi criminali  che intendono arricchirsi depredando le tombe e disturbando la pace eterna dei  Faraoni d'Egitto. Non permettere che tali sacrilegi macchino le tombe reali  della Valle, altrimenti la considerazione che il regno ha di te ne soffrirà  alquanto."
        }
    }
    message_mission_sumur_2 {
        id: 465,
        type: 3,
        size [40, 30]
        title {
            text: "Sumur",

        }
        subtitle {
            text: "Terre levantine",

        }
        content {
            text: "@PSalute a te governatore reale, reggente levantino e fedele  servitore del nostro Faraone, figlio di Ra. Siamo tutti fortunati a vivere in  questi tempi in cui il benevolo abbraccio d'Egitto si estende dalla lontana  Nubia fino alle terre levantine. Infinita è la saggezza del nostro nuovo  Faraone, il nobile Ramses II, e grande è la sua visione, in quanto egli stesso  ti ha inviato a governare queste splendide terre, ora sotto il dominio egizio.  @PQuesta regione, anche se minacciata da molti pericoli, possiede molte  ricchezze da sfruttare. Le verdi colline sono costellate di alberi, il cui legno  è il materiale ideale per fabbricare carri e da impiegare in ogni tipo di  costruzione. La stessa cosa vale per il rame, anche se non così abbondante, che  può essere utilizzato per fabbricare armi robuste. Legno e rame, così rari nella  nostra madre patria, saranno certo benvenuti una volta spediti in grande  quantità. Spetta a te dunque costruire un grande porto commerciale grazie al  quale esportare questi beni fondamentali. Il Faraone e tutti gli Egizi te ne  saranno estremamente grati! @PMa fai attenzione! Assicurati che i tuoi soldati siano equipaggiati con carri  e armi robuste, gli Ittiti, anche se battuti da Seti, padre dell'attuale  Faraone, sono ancora pericolosi e possono sfidare la nostra autorità in questa  ricca terra. Per sedare le ribellioni occorre una forte presenza militare, per  altro utile anche in futuro. @PInfine, per ricordare alle genti di queste terre a chi devono rendere omaggio,  il faraone Ramses II ritiene opportuno che tu eriga un obelisco che celebri la  sua gloria."
        }
    }
    message_mission_qadesh_2 {
        id: 466,
        type: 3,
        size [40, 30]
        title {
            text: "Qadesh",

        }
        subtitle {
            text: "La battaglia di Qadesh",

        }
        content {
            text: "@PLa terra di Amurra, vicina alla costa levantina, trema sotto gli  zoccoli e i piedi delle tue potenti legioni, nobile Faraone. Questa regione è  tanto ricca di risorse quanto di discordie. Le armate Ittite, guidate dal  perfido re Mutwatalli, ancora una volta cercano di contrastare il nostro dominio  in questa terra, nostra per diritto. Le spie catturate ci hanno detto che i  soldati sono ancora lontani, a nord, e per ora non presentano alcun pericolo. Ma  dobbiamo crederlo? Il guerriero saggio non abbandona mai lo scudo in battaglia. @PPer sedare eventuali ribellioni tu, nobile Faraone Ramses II, figlio di Ra,  sei arrivato alla città fortificata di Qadesh. Presso di essa si trovano già due  accampamenti di temibili carri da guerra. Ma non solo. Ai tuoi comandi si  trovano altre truppe di veterani – i soldati recentemente impiegati vicino a  Sumur. Ma fai attenzione! Forse è meglio ritardare il loro schieramento finché  la situazione non lo richieda: saggio è il guerriero che può contare su soldati  fidati al culmine della battaglia. @PQuando il nemico sarà sconfitto, sarà necessario rinforzare la stagnante  economia di Qadesh così che anch'essa possa contribuire alla gloria d'Egitto.  Estrai le gemme, assumi abili gioiellieri e fabbrica oggetti preziosi per tutti  i fedeli servitori del Faraone. Beni di lusso di così rara bellezza saranno  certo richiesti!"
        }
    }
    message_mission_abu_simbel_2 {
        id: 467,
        type: 3,
        size [40, 30]
        title {
            text: "Abu Simbel",

        }
        subtitle {
            text: "I colossi di Abu Simbel",

        }
        content {
            text: "@PLa gloria del nostro Faraone, Ramses II, pervade l'Egitto. Affinché  l'eredità del suo regno viva per sempre, è stato deciso di costruire in Nubia un  grande monumento e un tempio in suo onore - e il Faraone stesso ha scelto un  luogo ideale per tale immensa costruzione. Dovrai supervisionare la costruzione  di quattro enormi statue sedute che raffigurano sua maestà, con l'arenaria  rosata delle sponde occidentali del Nilo, ad Abu Simbel. Le pareti del  monumento, intagliate nella viva roccia, proclameranno le eroiche gesta del  Faraone nel suo grande trionfo a Qadesh. Questo enorme monumento, oltre a  celebrare le imprese del nostro capo supremo, servirà anche a ricordare alle  genti della Nubia la grandezza e la potenza dell'Egitto, in quanto, anche se la  Nubia è ricca d'oro e altre rare gemme, il suo popolo non ha mai gradito la  sottomissione al dominio egizio. Per questo motivo dovrai sempre essere pronto a  difenderti e in grado di inviare delle truppe se il Faraone dovesse richiederle. @PL'arenaria può essere esportata in altre parti del regno, così come tutti gli  altri beni e materiali che riuscirai a produrre sfruttando le abbondanti risorse  della regione. Tuttavia, troverai ben poco legno. Senza dubbio dovrai stabilire  una via commerciale per importarlo, in quanto servirà per le grandi impalcature  necessarie alla costruzione dell'immenso monumento."
        }
    }
    message_mission_ramses_valley_2 {
        id: 468,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses nella Valle",

        }
        subtitle {
            text: "Una tomba impareggiabile",

        }
        content {
            text: "@PSono trascorsi molti e gloriosi anni da quando il nostro Faraone,  il nobile Ramses II, ha accettato le insegne del comando da suo padre, Seti I.  Con la benedizione di Ra, continuerà a regnare ancora per molto tempo. Tuttavia,  è giunto il momento di iniziare gli scavi e preparare il luogo dell'eterno  riposo per il nostro capo supremo. Egli ha fornito all'architetto reale un  progetto per la tomba più grande mai costruita, superiore persino a quella del  suo sire. Ora tocca a te assicurare che le sue richieste siano soddisfatte. @PFai attenzione! Tra i lavoratori e gli schiavi, locali e in tutto il Basso  Egitto, serpeggia il sentimento della rivolta. Essi seguono un uomo cresciuto  alla corte del nostro Faraone e hanno minacciato di chiedere l'intervento del  loro dio. Grazie all'aiuto divino, essi sperano di fuggire. Proprio in questo  momento, i sacerdoti e gli uomini di religione stanno discutendo la pericolosità  di tale minaccia. Mentre attendiamo con pazienza la loro valutazione, è comunque  prudente prepararsi al peggio."
        }
    }
    message_mission_henna {
        id: 469,
        
        size [30, 20]
        image {
            id: 1008,
            pos [15, 15]
        }
        title {
            text: "Henna",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Per oltre tre millenni, varie popolazioni hanno usato gli arbusti di  henna per ottenerne pigmenti. L'henna (il cui nome scientifico è Lausonia  inermis) appartiene alla famiglia delle Lythraceae ed è nativa dell'Africa  settentrionale e del Medio Oriente. Quando viene schiacciata, le foglie e i rami  producono una tintura rossastra che, opportunamente trattata, si utilizza per  colorare i capelli, le unghie e la pelle. Ancora oggi, l'henna si utilizza  comunemente per molti rituali religiosi e funebri in Asia, in Medio Oriente e in  Africa, e costituisce il colorante principale per i popolari tatuaggi  temporanei. L'henna è un importante ingrediente anche di molte tinture per  capelli."
        }
    }
    message_mission_paint_maker {
        id: 470,
        
        size [30, 28]
        title {
            text: "Fabbriche di pittura",
        }
        content {
            text: "Le fabbriche di pittura richiedono forniture di @469henna per la  propria produzione. I rami schiacciati di henna si utilizzano per creare diverse  tinture, indispensabili per produrre le pitture. L'henna si coltiva nelle  @91fattorie&di&henna o può essere importato tramite una @47via&commerciale. @PQuando una fabbrica di pittura dispone di personale, dell'accesso a una strada  e di una fornitura di henna, puoi vedere i produttori di pittura al lavoro.  Quando la produzione è completa, la pittura viene consegnata ai  @4depositi&merci. La pittura sarà poi utilizzata dagli @363artigiani per  dipingere le @478tombe&reali. @PA causa del rumore e degli spiacevoli odori, alla gente non piace vivere  vicino a queste fabbriche. @L@LClicca @472qui per avere ulteriori informazioni sulla pittura nell'antico  Egitto."
        }
    }
    message_illness_video {
        id: 471,
        type: 2,
        
        size [30, 20]
        title {
            text: "Malattia",
        }
        video {
            text: "smk\\sick.smk"
        }
    }
    message_history_artisans {
        id: 472,
        
        size [30, 20]
        image {
            id: 1004,
            pos [15, 15]
        }
        title {
            text: "Artigiani",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La maggior parte delle strutture dell'antico Egitto impiegava  artigiani per il tocco finale, ma soltanto nelle tombe del Nuovo Regno, nella  @475Valle&dei&Re, questi artisti dal talento straordinario hanno dato prova  della loro abilità. Praticamente ogni centimetro delle pareti e dei soffitti di  queste camere sotterranee celebrava la grandezza del defunto, grazie ai  geroglifici e ad altri dipinti. @PNonostante la stravaganza e il dettaglio delle illustrazioni, gli antichi  artisti potevano contare su ben pochi colori e su pennelli rudimentali, ricavati  da @94canne o da legno fibroso, come quello di palma. I pigmenti erano  normalmente preparati in piccole botteghe con tinture vegetali (come  l'@469henna) o con altre risorse minerali (come carbonato di calcio, carbone,  ruggine, azzurrite e malachite) ridotte in polvere. Per diventare pitture, le  polveri dovevano poi essere mescolate con un collante vegetale o animale. @PMolti artisti specializzati hanno collaborato per creare splendide immagini a bassorilievo nelle tombe. Come prima cosa, hanno preparato gli stucchi da una miscela di @190argilla, acqua e agente sbiancante, poi li hanno applicati sulle pareti delle tombe. Fatto questo, hanno tracciato un abbozzo di disegno in rosso sui muri appena stuccati. Un esperto disegnatore  rifiniva poi l'immagine in dettaglio, normalmente in nero. Un maestro pittore vi  apportava delle correzioni e aggiungeva altri dettagli per guidare lo scultore  del bassorilievo che l'avrebbe seguito. La pittura veniva poi applicata a grandi  linee con colori piatti. I dettagli finali (i rilievi e i dettagli interni)  venivano dipinti da un altro artista."
        }
    }
    message_building_lamp_maker {
        id: 473,
        
        size [30, 28]
        title {
            text: "Fabbriche di lampade",
        }
        content {
            text: "La fabbrica di lampade produce lampade capaci di guidare i lavoratori negli oscuri passaggi di una @478Tomba&Reale.  @PPer produrre lampade, la fabbrica di lampade ha bisogno di vasellame e olio. Il vasellame può essere fornito da un @1vasaio o essere importato da un @47partner&commerciale. L'@476olio si può solo importare. @PUna fabbrica di lampade deve aver accesso alle strade e a una vicina fonte di manodopera. Quando avrà ricevuto olio e vasellame a sufficienza, potrai vedere i fabbricanti di lampade intenti a riempire il vasellame di olio per produrre lampade. @PLe fabbriche di lampade hanno effetti negativi sulla @56desiderabilità di una  zona, quindi non posizionarle vicino ad aree residenziali in via di sviluppo. @L@LClicca @474qui per avere ulteriori informazioni sulle lampade nell'antico  Egitto."
        }
    }
    message_history_lamps {
        id: 474,
        
        size [30, 20]
        image {
            id: 1003,
            pos [15, 15]
        }
        title {
            text: "Lampade",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli antichi Egizi fabbricavano piccole lampade di ceramica che  bruciavano @476olio naturale o grasso animale. Queste lampade fornivano luce a  tutti i lavoratori impegnati negli oscuri recessi delle tombe reali."
        }
    }
    message_history_valley_of_the_kings {
        id: 475,
        
        size [30, 20]
        image {
            id: 1011,
            pos [15, 15]
        }
        title {
            text: "Valle dei Re",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "@PLa Valle dei Re è stata per cinque secoli, all'incirca dal 1539 al  1075 a.C., la necropoli dei Faraoni, tra cui Thutmose I, Tutankhamun e Ramses il  Grande (Ramses II). Situata sulla sponda occidentale del Nilo, di fronte al  complesso dei templi di Tebe, la Valle giace ai piedi della montagna el-Qurn, di  forma quasi piramidale, l'ultima a ricevere la benedizione di Ra, prima del  calar del sole. Tra la Valle e il Nilo si trovano i templi funebri dedicati ai  Faraoni che intendevano godere dell'aldilà nelle tombe della Valle. Un vicino  villaggio, Deir el-Medina, ospitava centinaia di lavoratori e le loro famiglie. @PI lavoratori che costruivano le tombe reali erano degli specialisti dediti al  loro importante compito. Gli scalpellini scolpivano gradini e passaggi nelle  pareti di calcare. Pilastri in pietra si ergevano per sorreggere i tetti delle  camere più grandi. Le stanze ricavate dalla roccia venivano lisciate e stuccate  prima che gli artigiani arrivassero per decorare soffitti e pareti con  bassorilievi e affreschi che avrebbero accompagnato il Faraone nell'aldilà. Il  re defunto era alloggiato nel suo sarcofago e quindi sigillato nella tomba con  tutti i tesori che ne testimoniavano lo stato di divinità. Proprio per questi  tesori, le tombe venivano spesso depredate, di frequente proprio dalle stesse  persone che avevano il compito di sorvegliarle. @PGli archeologi europei scoprirono la Valle dei Re nei primi anni del 1800. Nel  1922, Howard Carter penetrò nella tomba ancora sigillata di Tutankhamun e scoprì  molti tesori, tra cui un sarcofago d'oro. Con il passare dei secoli, gli  straripamenti del Nilo hanno inondato molte tombe e vi hanno depositato fango e  detriti. Probabilmente nella Valle esistono altri passaggi, e forse anche tombe,  non ancora scoperti."
        }
    }
    message_history_oil {
        id: 476,
        
        size [30, 20]
        image {
            id: 1009,
            pos [15, 15]
        }
        title {
            text: "Olio",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "La maggior parte dell'olio usato dagli Egizi era importata dalla  Grecia, da Cipro e dalla Fenicia. Gli oli naturali avevano molti usi, ad esempio  come combustibile per le @474lampade e per la cucina. Gli oli si estraevano da  diverse risorse naturali (utilizzate ancora oggi), come il sesamo, i semi di  lino, le olive e i grassi animali."
        }
    }
    message_figure_tomb_robber {
        id: 477,
        
        size [30, 28]
        title {
            text: "Saccheggiatori di tombe",
        }
        content {
            text: "@PDove c'è una tomba, ci sono dei tesori! Il predone di tombe è un tipo di criminale che appare quando il @39Morale&cittadino è molto scarso. Comunque, costui entrerà in azione soltanto se ci sono ricchezze da rubare. Dunque, se la vostra città non ospita alcuna tomba (Piramide, @371Mastaba, @368Mausoleo o @478Tomba&Reale), non la degnerà delle sue attenzioni, cosa che farà anche se non ci sono @374arredi&funebri da rubare, sia perché la tomba non le richiede, sia perché non le hai ancora inviate. @PA volte, i predoni di tombe colpiscono anche quando in una città non c'è traccia di crimine. Se ai predoni professionisti giunge la voce che nelle tombe della tua città si trovano beni particolarmente preziosi, daranno vita a un'ondata di crimine. Non c'è modo di prevedere quando si verificherà un'ondata di crimine. @PTutti i predoni di tombe sono accomunati dallo stesso obiettivo: privare i Faraoni eternamente dormienti di tutte le ricchezze depositate nella loro tomba perché potessero usarle nell'aldilà. Per riuscire nel proprio intento, il predone di tombe deve raggiungere una tomba senza essere catturato. Se incontrerà un conestabile o dei soldati, di solito verrà prontamente 'trattenuto', anche se un individuo particolarmente agile può riuscire a scappare. Se il predone riesce a raggiungere un monumento funebre, ne uscirà di soppiatto con una parte delle ricchezze ivi depositate e il tuo @35Livello&del&regno ne risentirà negativamente. Infatti, chi vorrebbe essere governato da qualcuno che non è in grado di proteggere le tombe dei suoi antenati? @PI predoni di tombe non hanno preferenze sul tipo di tomba da saccheggiare e nemmeno remore a derubare un monumento che già esisteva quando tu hai assunto il potere. Fortunatamente, queste tombe pre-esistenti sono sigillate molto accuratamente e un predone di tombe non riuscirà a rubare nulla. Però, il popolo egiziano ne risentirà molto quando scoprirà che una delle sue tombe più antiche è stata minacciata; dunque, il tuo livello del regno scenderà notevolmente. @PAttento! Se il predone di tombe riuscirà a fuggire con le ricchezze della tomba, dovrai sostituire ogni oggetto rubato prima di poter completare la missione. @PPer saperne di più sul crimine nella tua città, clicca @36qui. @L@LPer avere ulteriori informazioni sulle tombe reali dell'antico Egitto nella  Valle dei Re, clicca @475qui."
        }
    }
    message_building_royal_burial_tomb {
        id: 478,
        
        size [30, 28]
        title {
            text: "Tombe reali",
        }
        content {
            text: "@PA partire dal Nuovo Regno, gli antichi Egizi iniziarono a seppellire i Faraoni e i nobili in tombe sempre più elaborate, ricavate dalla roccia viva e situate in una valle quasi inaccessibile. @PPer poter iniziare i lavori di una tomba reale, devi innanzitutto trovare un  luogo adatto. Scegli 'Tomba reale' dall'elenco Strutture religiose:  Monumenti. Comparirà una grande impronta.  La maggior parte del monumento deve trovarsi all'interno delle rupi, eccezion fatta per il piccolo ingresso, che spunta sul fianco di essa. Sposta il profilo dell'edificio lungo le rupi per trovare un luogo adatto. Quando l'intero profilo diventa verde, significa che puoi costruire in quel punto. Se dovesse essere rosso in qualunque punto, significa che non hai ancora trovato una posizione adatta a quel monumento. @PScoprirai che è più facile disporre una Tomba Reale spianando temporaneamente le rupi. Per farlo, premi 'H' oppure scegli 'Nascondi rupi' dall'elenco delle @18tabelle. Per riportare le rupi alla loro normale altezza, premi ancora 'H' o seleziona 'Normale' dall'elenco degli schermi. Se devi disporre una tomba particolarmente grande, prova a premere il tasto 'M', che blocca il profilo dove si trova e ti permette di modificare il punto d'osservazione per scoprire se hai scelto un sito adatto. In caso affermativo, dovrai semplicemente premere il pulsante del mouse per confermare la posizione del monumento. Altrimenti, premi ancora 'M' per sbloccare il profilo e continuare la ricerca. @PDopo aver scelto un sito, dovrai inviare alla tomba un carico di lampade prima che si possano iniziare i lavori. Le lampade vengono prodotte dalla @473fabbrica&di&lampade e possono anche essere importate da un @47partner&commerciale. Quando avrai depositato 400 lampade in un @4deposito&merci, un manovale porterà un carico di lampade verso il sito di costruzione. @PQuando saranno arrivate le lampade per illuminare il loro cammino, gli @363scalpellini inizieranno a scavare nella roccia viva le numerose stanze della tomba. Ultimato questo lavoro, verranno richiamati abili @363artigiani che inizieranno a stuccare e a dipingere i muri. Questi artigiani avranno bisogno di @92argilla per gli stucchi e della vernice prodotta da una @470fabbrica&di&pittura. Questi beni verranno inviati direttamente alla gilda degli artigiani dagli stessi produttori o da un deposito merci. Se la tua città non può produrre uno o più di questi beni, potrai sempre @47importarli. @PClicca con il pulsante destro su una Tomba Reale per chiedere al suo @369Capo&cantiere un rapporto sui lavori. @L@LClicca @475qui per saperne di più sulla Valle dei Re e sulle sue Tombe Reali."
        }
    }
    message_building_zoo {
        id: 479,
        
        size [30, 28]
        title {
            text: "Zoo",
        }
        content {
            text: "Gli zoo sono una popolare forma di @49intrattenimento per ogni città. Uno zoo ha bisogno di essere collegato alle strade e di lavoratori che badino agli animali, oltre a un afflusso di @89paglia e @359carne per cibare gli animali. La paglia può essere raccolta nelle coltivazioni di grano, mentre i cacciatori di un casotto da caccia possono procurare la carne. Puoi anche creare una @47via&commerciale per importare questi beni. @PConsulta il @28supervisore&dell'intrattenimento per sapere quanti zoo sono presenti in città e usa la tabella intrattenimento per sapere quali abitazioni vi hanno accesso. @PNonostante gli zoo siano delle fonti di intrattenimento, i cittadini non  gradiscono vivere nelle loro vicinanze, a causa dei forti rumori, lamenti e  odori che emanano. Clicca @56qui per avere ulteriori informazioni sulla  desiderabilità delle strutture. @L@LPer avere ulteriori informazioni sugli zoo nell'antico Egitto, clicca  @480qui."
        }
    }
    message_history_zoo {
        id: 480,
        
        size [30, 20]
        image {
            id: 1005,
            pos [15, 15]
        }
        title {
            text: "Zoo",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Gli antichi Egizi erano affascinati dal divertimento e dalle  stranezze e negli zoo potevano trovare entrambe le cose. Man mano che il potere  e l'influenza dell'Egitto si estendevano in più continenti, molti Faraoni  iniziarono a ricevere strane ed esotiche creature come doni o tributi dai  governanti di terre lontane. Questi animali erano presentati al Faraone e quindi  tenuti in speciali giardini zoologici, inevitabilmente poco lontani dalla  residenza del Faraone. I primi zoo egizi erano principalmente intesi come  spettacolo per il popolo, ma anche come luogo di studio. Si tramanda che la  grande biblioteca di Alessandria comprendesse sia un giardino botanico che uno  zoologico."
        }
    }
    message_history_alexandria_and_its_library {
        id: 481,
        
        size [30, 20]
        image {
            id: 1001,
            pos [15, 15]
        }
        title {
            text: "Alessandria e la sua biblioteca",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Fin dall'inizio, Alessandro Magno sperava che Alessandria, la città  sul delta del Nilo da lui fondata e pianificata, diventasse un centro  commerciale e culturale per tutto il Mediterraneo. Trascorsi meno di  cinquant'anni dalla sua fondazione nel 331 a.C., la città era diventata ormai  una metropoli, tappa fondamentale per il commercio, soprattutto grazie alla  famosa biblioteca che ospitava. @PSubito dopo l'improvvisa morte di Alessandro nel 323 a.C., il suo impero si  dissolse in tre grandi regioni. Uno dei suoi più cari amici e abili generali,  Tolomeo, era a quel tempo il governatore dell'Egitto. Egli prese le redini  dell'antica terra e divenne infine Faraone (col nome di Tolomeo I Soter),  continuando così la presenza greca in Egitto, iniziata con Alessandro. Fu  proprio Tolomeo che intercettò la processione funebre di Alessandro, diretta in  Macedonia, e portò le sue spoglie mortali ad Alessandria per la sepoltura. @POltre alla gloria personale e alla vita nel lusso, comunque, i primi regnanti  tolemaici erano anche interessati a migliorare il livello culturale della loro  città. Alessandria, la nuova capitale d'Egitto, era già il centro commerciale  del mondo conosciuto; essi volevano che ne diventasse anche il centro  intellettuale. Per questo motivo, fu concepita e costruita la grande biblioteca  di Alessandria che divenne il primo centro di istruzione e ricerca scolastica  dell'umanità. Le brillanti menti dell'antichità qui posero le fondamenta per lo  studio sistematico dell'astronomia, della geografia, della letteratura, della  matematica, della medicina e della fisica. Fu qui che Euclide definì la sua  geometria ed Eratostene misurò con grande precisione la circonferenza della  Terra, dichiarando che l'India poteva essere raggiunta dalla Spagna navigando  verso Ovest. @PI Tolomei impiegarono molto tempo ed energia, per non parlare di capitali, per  ottenere le copie di ogni importante manoscritto conosciuto. Per questa ragione  era stata promulgata una legge per la quale qualsiasi carovana che entrava in  Alessandria doveva essere perquisita, - non per sospetti di contrabbando, ma per  trovare documenti istruttivi. Qualsiasi mappa o pergamena ritrovata veniva  inviata alla biblioteca affinché gli scribi la ricopiassero. Così il tempio  della scolarizzazione alessandrino arrivò a contenere oltre 700.000 pergamene  tutte catalogate, incluse opere d'arte ormai perdute e altre di letteratura e  scienza, come i classici di Omero, Aristotele, Sofocle, Eschilo ed Euripide. @PMa non si trattava solo di scritture e istruzione. La leggendaria biblioteca  vantava anche un giardino botanico e un museo oltre a un tempio dedicato alle  nove muse (divinità greche delle arti e delle scienze). Una breve passeggiata  lungo la palizzata dei giardini portava allo zoo, contenente senza dubbio  diverse specie di animali esotici. Gli scienziati e gli studiosi che camminavano  all'ombra dei portici erano innumerevoli. @PLe circostanze della scomparsa della grande biblioteca non sono completamente  chiare: una buona parte delle sue opere fu evidentemente distrutta durante un  incendio occorso quando Giulio Cesare diede alle fiamme le navi del fratello di  Cleopatra VII. Nel IV secolo d.C., con l'estendersi dell'influenza cristiana, la  maggior parte dei manoscritti della biblioteca fu distrutta con lo scopo di  eliminare tutte le testimonianze di paganesimo ed eresia. Più tardi, nel 640  d.C., gli Arabi invasero la città ormai semi-abbandonata e probabilmente  bruciarono tutte le pergamene che trovarono utilizzandole come combustibile.  Delle 123 commedie di Sofocle, che si credeva fossero qui custodite, oggi ne  rimangono soltanto sette."
        }
    }
    message_history_caesareum {
        id: 482,
        
        size [30, 20]
        image {
            id: 1002,
            pos [15, 15]
        }
        title {
            text: "Caesareum",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Cleopatra VII iniziò la costruzione del Caesareum, che in origine  consisteva di un piccolo tempio o altare al centro di un santuario,  apparentemente inteso per onorare il culto di Marcantonio. Il suo suicidio,  seguito a breve da quello di Cleopatra, però, ci fa intendere che questo  monumento fu completato dal loro rivale, Ottaviano (Cesare Augusto), che terminò  la costruzione e la dedicò al proprio culto. Due obelischi (generalmente  chiamati gli Aghi di Cleopatra, anche se lei non poteva averci a che fare),  rimasero per secoli a segnare la spiaggia orientale di Alessandria. Questi  obelischi, trasferiti ad Alessandria da Heliopolis per ordine di Ottaviano,  continuarono a segnare l'entrata al Caesareum anche molto dopo che tutto il  resto era ormai andato distrutto. Gli obelischi ora sono stati rimossi (uno si  trova al Central Park di New York, l'altro lungo le rive del Tamigi a Londra). @PI dettagli sulle effettive strutture del Caesareum sono sconosciuti. Ciò che  sappiamo deriva da brevi accenni di qualche antico scrittore. La sua  architettura, come quella degli altri grandi monumenti di Alessandria, era in  stile greco. Sicuramente conteneva un santuario centrale inserito tra cortili a  cielo aperto e circondato da 'stoà' (colonnati) che probabilmente servivano  anche da mura esterne del monumento. Le stanze e i portici inseriti tra le stoà  contenevano pergamene e potevano essere sfruttati come pacifici luoghi di  raccoglimento e di studio."
        }
    }
    message_plague_of_locusts {
        id: 483,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Piaga delle locuste",
        }
        content {
            text: "Abbiamo avuto notizie di uno sciame di locuste impazzite che divorano le messi in tutto l'Egitto. Per il prossimo raccolto, fai attenzione alle devastazioni che potrebbero portare."
        }
    }
    message_plague_of_frogs {
        id: 484,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Piaga delle rane",
        }
        content {
            text: "Una terribile maledizione si è abbattuta sulla tua terra! Una  moltitudine di rane insozza le nostre strade e abitazioni, costringendo gli abitanti a fuggire!"
        }
    }
    message_hailstorm {
        id: 485,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Tempesta di grandine",
        }
        content {
            text: "La morte e la distruzione cavalcano le ali del vento! Una terribile  grandinata ha rovesciato una mortale pioggia di ghiaccio. Che gli dei abbiano  pietà di coloro che non hanno trovato riparo da questa malvagia maledizione, dal momento che hanno poche speranze di sopravvivere"
        }
    }
    message_river_of_blood {
        id: 486,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Fiume di sangue",
        }
        content {
            text: "La maledizione ci affligge! Le acque, una volta fonte di vita e di  nutrimento, ora sono avvelenate col sangue. Quanto tempo dovrà trascorrere prima  che tale maledizione sia finalmente scacciata?"
        }
    }
    message_history_pharos_lighthouse {
        id: 487,
        
        size [30, 20]
        image {
            id: 1006,
            pos [15, 15]
        }
        title {
            text: "Il faro di Pharos",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "@PAnche se la posizione di Alessandria era ideale come porto  commerciale, con ampie coste e una grande baia naturale, i suoi punti di  ingresso erano minati da pericolosi banchi di sabbia. Si pensò così di erigere  un alto faro sull'isola di Pharos (da cui il nome di questo tipo di  costruzione), vicino all'entrata della baia, in modo da guidare i marinai e da  aggiungere lustro alla già meravigliosa fama di Alessandria. @PIl faro fu costruito principalmente con marmo bianco proconnesiano, per lo più  importato dalle Isole dei Principi, al largo delle coste della moderna Turchia.  Fu costruito su tre grandi piani: la base, o piano inferiore, era quadrangolare,  il piano intermedio era ottagonale, mentre quello più alto era cilindrico. Una  gigantesca scalinata a spirale permetteva agli animali da soma di portare il  legname fino in cima, per alimentare il fuoco che bruciava in continuazione.  Sulla sommità della straordinaria struttura si trovava (secondo alcuni  resoconti) una statua di Poseidone; secondo altri si trattava di una statua di  Zeus - o forse era una statua che li ritraeva entrambi. @PLa costruzione del faro di Alessandria fu iniziata dal primo Tolomeo (Aulete),  ma non fu terminata fino al 283 a.C., durante il regno del figlio, Tolomeo  Philadelphus. Secondo tutte le testimonianze si trattava di una vista  spettacolare, più che degna di diventare la settima meraviglia del mondo antico. @PLa fine di questo monumento avvenne non per mano dell'uomo, ma a causa di una  serie di terremoti che sconvolsero la regione. Il piano più alto rovinò al suolo  durante un forte terremoto nell'anno 303 d.C. Comunque, non fu che fino al  grande disastro dell'8 Agosto 1303 (che scosse tutta le regione del Mediterraneo  orientale) che gran parte della struttura crollò, inghiottita dalle acque  circostanti. Oggi, al posto del faro, sull'isola di Pharos si trova un forte,  costruito dal sultano mamelucco Qait Bey."
        }
    }
    message_building_alexandria_library {
        id: 488,
        
        size [30, 28]
        title {
            text: "Biblioteca di Alessandria",
        }
        content {
            text: "Studiosi e uomini di scienza provenienti da ogni parte del mondo  visitano la maestosa biblioteca di Alessandria, il più grande deposito di  conoscenza di tutta l'umanità. @PPer costruire la biblioteca di Alessandria, devi prima individuare un luogo  opportuno. Scegli la biblioteca di Alessandria fra le strutture religiose nella lista dei monumenti. Se il profilo che vedi è completamente verde, significa che hai scelto un luogo adatto a costruirla.  @PPer costruire la biblioteca di Alessandria, avrai bisogno dell'impegno di manovali provenienti dai @8Campi&di lavoro, di scalpellini usciti dalle @363gilde&degli&scalpellini e di carpentieri usciti dalle @363gilde&dei&carpentieri. Questi ultimi, per costruire i ponteggi avranno bisogno di @94legno, che può essere importato se la tua città non lo produce. Dovrai anche @47importare marmo bianco da un partner&commerciale. Per terminare il monumento, ti servirà una certa quantità di @93rame, proveniente dalle miniere della tua città o importato da un partner commerciale. @PClicca con il pulsante destro del mouse sulla biblioteca di Alessandria  durante la sua costruzione per ottenere dal @369capo&cantiere un rapporto sui  lavori. @L@PClicca @481qui per avere ulteriori informazioni storiche sulla grande  biblioteca di Alessandria."
        }
    }
    message_building_pharos_lighthouse {
        id: 489,
        
        size [30, 28]
        title {
            text: "Faro di Pharos",
        }
        content {
            text: "Lo spettacolare faro di Alessandria guida notte e giorno i marinai  impegnati nelle pericolose acque della sua baia. @PIl faro può essere costruito solo sul terreno roccioso dell'isola di Pharos,  nella baia di Alessandria. Seleziona 'Faro di Pharos' dalla lista Strutture  religiose: Monumenti, e quindi sposta il cursore su una porzione di terreno  segnato dalla roccia sull'isola di Pharos, vicino all'entrata della baia. Quando  l'impronta del monumento è completamente verde, significa che hai individuato un  luogo adatto a supportare l'incredibile peso della monumentale struttura. @PQuando il terreno sarà liberato, dovrai importare del marmo. Questo bene può  essere ottenuto tramite una @47via&commerciale con un'altra città. Gli @363scalpellini provenienti da una @363gilda&degli&scalpellini si occuperanno di disporre con attenzione il marmo bianco che i manovali usciti dal @8Campo&di&Lavoro avranno prelevato da un @4deposito&merci. I manovali trasporteranno il marmo bianco quando ce ne saranno almeno quattro blocchi in un dato deposito merci. Una volta iniziati i lavori, sarà necessario disporre di @363carpentieri usciti da una gilda dei carpentieri e di molto @94legno per costruire i ponteggi. @PClicca con il pulsante destro del mouse sul faro di Pharos mentre è in  costruzione per ottenere un rapporto sull'avanzamento dei lavori dal suo  @369capo&cantiere. @LClicca @487qui per avere ulteriori informazioni sul faro di Pharos ad  Alessandria."
        }
    }
    message_building_caesareum {
        id: 490,
        
        size [30, 28]
        title {
            text: "Caesareum",
        }
        content {
            text: "Una delle principali perle architettoniche di Alessandria è il Caesareum, un gigantesco tempio in riva al mare che funge anche da riferimento per tutti i marinai che entrano nell'enorme porto della città. @PPer costruire il Caesareum, selezionalo fra le strutture religiose nella lista dei monumenti, nel pannello di controllo. Fatto ciò, vedrai apparire il suo profilo. Esplora lo scenario per cercare una zona sufficientemente ampia di terreno sgombro e disponi il monumento. Quando il profilo sarà tutto verde, avrai trovato il luogo adatto a costruire.  @PDopo aver determinato il luogo di costruzione, i lavori potranno iniziare. I manovali di un @8Campo&di lavoro inizieranno a preparare il terreno, portando alla luce lo strato roccioso sottostante. Una volta preparato il terreno, gli @363scalpellini di una gilda degli scalpellini dispongono il marmo bianco, che i manovali hanno prelevato da un @4deposito&merci. Il marmo bianco deve essere @47importato da un partner commerciale. I manovali inizieranno a trasportarlo fino al luogo di costruzione non appena in un deposito merci ce ne saranno quattro blocchi. @PPer costruire i ponteggi, sono necessari anche i @363carpentieri di una gilda dei carpentieri e una provvista di @94legno. Se la tua città non può procurarsi autonomamente il legno, lo dovrai importare. Quando i lavori saranno quasi ultimati, ti servirà anche una certa quantità di granito preso da un deposito merci. Il granito può essere importato, se la tua città non lo può @95estrarlo per conto proprio. @PClicca con il pulsante destro del mouse sul Caesareum durante la costruzione per chiedere al suo @369capo cantiere un rapporto sui lavori. @LClicca @482qui per avere ulteriori informazioni storiche sul Caesareum."
        }
    }
    message_crime_wave {
        id: 491,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Ondata di crimine",
        }
        content {
            text: "Che gli dei abbiano pietà di noi! Una banda di avidi criminali in cerca di ricchezze ha invaso le strade della nostra bella città. Devi fermarli, prima che i tesori dei nostri nobili defunti vadano persi per sempre."
        }
    }
    message_building_abu_simbel {
        id: 492,
        
        size [30, 28]
        title {
            text: "Abu Simbel",
        }
        content {
            text: "@PIl tempio di Abu Simbel è l'enorme monumento che Ramses II ha  ricavato dalla roccia arenaria nubiana. @PPer iniziare la costruzione di Abu Simbel, selezionalo fra le strutture religiose nella lista dei monumenti: ne vedrai così apparire il profilo. Il corpo del monumento deve essere ricavato all'interno delle rupi, mentre l'ingresso deve trovarsi su un terreno sgombro. Quando il profilo sarà tutto verde, avrai trovato un luogo adatto alla costruzione. Premi il pulsante del mouse per confermare la scelta del posto. @PScoprirai che è meglio spianare temporaneamente le rupi mentre cerchi un punto adatto a costruire il monumento. Per farlo, premi 'H' oppure scegli 'Nascondi rupi' dall'elenco delle @18tabelle. Per riportare le rupi alla loro normale altezza, premi ancora 'H' o seleziona 'Normale' dall'elenco degli schermi.@PUna volta scelto il luogo, ti servirà una forza lavoro adatta, composta dagli @363scalpellini di una gilda degli scalpellini per scavare la roccia, nonché dai @363carpentieri di una gilda dei carpentieri per costruire i necessari ponteggi. Per costruirli, i ponteggi avranno bisogno di @192legno, che può essere importato sfruttando una @47via&commerciale o raccolto direttamente sul posto da un @94Taglia&legna. @PClicca con il pulsante destro sul monumento di Abu Simbel per chiedere al suo @369Capo&cantiere un rapporto sui lavori.                         @L@LClicca @493qui per avere ulteriori informazioni sul più famoso monumento di  Ramses II."
        }
    }
    message_history_abu_simbel {
        id: 493,
        
        size [30, 20]
        image {
            id: 1007,
            pos [15, 15]
        }
        title {
            text: "Abu Simbel",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "@PRamses il Grande (Ramses II) regnò in Egitto circa dal 1279 al 1212  a.C. Questo Faraone è famoso per i numerosi monumenti costruiti durante il suo  regno, il più grande dei quali è Abu Simbel. @PA circa 480 km a sud di Waset (Tebe), nella provincia nubiana, gli scalpellini di Ramses ricavarono dalla roccia una serie di quattro statue sedute, raffiguranti il Faraone stesso, appoggiate alle pareti verticali in arenaria rosa, di fianco alla valle del Nilo. Ciascuna statua è alta più di 20 metri: solo la grande  sfinge di Giza è più imponente. Le figure sedute si trovano ai lati di una  galleria d'entrata che porta a un santuario interno, ricavato a oltre 50 metri  dalla parete esterna. Il tempio è rivolto a Est ed è studiato in modo che due  volte all'anno la luce del sole nascente penetri nel santuario, illuminando così  tre statue più piccole raffiguranti Ramses, Amon e Ra. Nel santuario si trova  anche una statua di Ptah, ma dato che tale divinità è associata al mondo  sotterraneo, la sua effigie non viene toccata dai raggi di luce. I rilievi  all'interno del tempio commemorano le vittorie militari di Ramses. Lì vicino, un  altro tempio scavato nella roccia rende omaggio alla dea Hathor e alla moglie  favorita di Ramses, la regina Nefertari. L'intero complesso doveva incutere  timore ai Nubiani e facilitare così la raccolta dei tributi. @PAbu Simbel fu completato circa nell'anno 1256 a.C. Con il passare dei  millenni, le sabbie lo ricoprirono. Nel 1817, l'archeologo Giovanni Belzoni  scoprì questo incredibile monumento. Nuovamente minacciato a metà degli anni  '60, questa volta dalle acque che si levavano dietro la grande diga di Aswan,  Abu Simbel fu estratto dalla roccia e ricostruito con grande precisione su un  terreno più elevato - un miracolo di ingegneria che certamente avrebbe  impressionato anche gli antichi Egizi."
        }
    }
    message_tutorial_major_plagues {
        id: 494
        
        size [30, 28]
        title { text: "Piaghe principali" }
        content { text: "Una città può essere colpita da numerose calamità, indipendentemente dalla sua ricchezza e dalle sue dimensioni, e le piaghe principali sono fra gli eventi peggiori. Ricorda, però, che non si tratta delle @53piaghe. Queste ultime si verificano quando il livello igienico della città è particolarmente basso, mentre le piaghe principali possono colpire senza alcun motivo preciso. @PTutte le piaghe principali abbassano il @39morale&cittadino. Le altre conseguenze nefaste sono descritte qui di seguito: @L@LFiume di sangue @LQuando il fiume di sangue colpisce la città, il suo fiume e le sue acque si trasformano in sangue per molti mesi, cessando di essere @44acque&potabili e utili ad altri scopi. Anche una parte dell'acqua conservata nelle case diventerà contaminata e imbevibile: gli effetti saranno più devastanti per chi abita più vicino al fiume, che correrà anche un rischio più alto di ammalarsi o di venir colpito dalla malaria (per saperne di più sulle malattie e sulla malaria, consulta la sezione @53salute&cittadina). Per tutta la durata della piaga, @84molo&da&pesca, @59Pompe&idrauliche, @94Piantagioni&di&canne, @62Pozzi e @61Serbatoi&d'acqua smetteranno di lavorare. Questo cataclisma può essere scatenato sulla città da una dea @354Bast irritata, oppure può verificarsi senza nessun motivo particolare. @L@LRane @LQuando la piaga delle rane colpisce la tua città, un'orda di rane ne invaderà i confini e infesterà ogni casa. Nessuno può vivere in una casa infestata dalle rane: i residenti saranno costretti a fuggire e nessuno potrà tornare indietro per molti mesi. Per bloccare le rane, puoi provare a costruire una cinta muraria o a disporre edifici in modo strategico. Questa piaga può essere provocata da @352Ptah se gli avrai mancato di rispetto, oppure le rane potrebbero colpire di loro iniziativa. @L@LTempesta di grandine @LLa tempesta di grandine è micidiale e può uccidere chiunque cammini per le strade della tua città, senza alcuna discriminazione. Può colpire i soldati (anche quelli nemici) e gli animali con la stessa facilità con cui può falciare i normali cittadini. La tempesta di grandine provoca anche violente agitazioni del fiume, provocando l'affondamento di molte navi. Se trascurerai @353Seth, egli potrà scatenare questo incubo sulla tua città, che però può anche essere dovuto a cause naturali. @L@LLocuste @L@LLocuste @LLe locuste caleranno in massa sulla tua terra divorando tutte le piante coltivate nelle tue @45fattorie. Tutto ciò che cresce nella pianura fluviale e nelle praterie verrà divorato subito prima che sia possibile raccoglierlo, privando per un anno la tua città dei benefici del raccolto. Se hai provocato la furia di @350Osiride, egli potrà scatenare questa piaga sulla tua città, ma le locuste possono apparire anche per conto proprio. @L@Lper avere ulteriori informazioni sulle piaghe principali che hanno afflitto  la terra dei Faraoni, clicca @495qui." }
    }
    message_history_major_plagues {
        id: 495,
        
        size [30, 20]
        image {
            id: 1010,
            pos [15, 15]
        }
        title {
            text: "Piaghe principali",
            pos [125, 15]
        }
        subtitle {
            text: "Storia",
        }
        content {
            text: "Nel XIII secolo a.C., durante il regno di Sethos I e di suo figlio  Ramses il Grande (Ramses II), gli Ebrei d'Egitto erano schiavi impiegati nella  costruzione dei monumenti. Secondo il biblico libro dell'Esodo, il loro dio  apparve a uno dei figli di Israele, il profeta Mosè, e promise il suo aiuto per  liberarli. Guidato dal suo dio, Mosè chiese al Faraone, in dieci diverse  occasioni, di lasciare libera la sua gente e Ramses si rifiutò sempre. Ogni  rifiuto comportò la maledizione di una piaga diversa che afflisse il Faraone e  gli Egizi, lasciando intoccata la gente di Israele. Con la prima, l'acqua del  fiume si trasformò in sangue, uccidendo i pesci e diventando non potabile. Dopo  il secondo rifiuto del Faraone, giunsero le rane dagli acquitrini e dal fiume a  infestare le case dei villaggi. La settima piaga fu la tempesta di grandine che  uccise uomini e animali e distrusse le messi di orzo e lino. Secondo il libro  dell'Esodo, dopo l'ottavo rifiuto di Ramses, giunsero gli sciami di locuste che  con il loro numero oscurarono la terra e divorarono tutto ciò che la grandine  aveva risparmiato. Ramses acconsentì a liberare gli Israeliti dopo che la decima  piaga ebbe ucciso tutti i primogeniti di uomini e animali, anche se, in seguito  ad un ripensamento, Ramses inviò il suo esercito all'inseguimento degli Ebrei  attraverso il Mar Rosso. @PAnche se queste piaghe non compaiono nelle cronache egizie, catastrofi del  genere sono presenti in altri resoconti storici e preistorici. Persino in tempi  moderni, nel cuore del XX secolo, le tempeste di grandine e le locuste sono  piaghe che affliggono l'umanità."
        }
    }
    message_mummy_attacks {
        id: 496,
        type: 2,
        
        size [30, 20]
        urgent: 1
        title { text: "La mummia attacca!" }
        content { text: "Una mummia è risorta e ora cammina per le strade cittadine. Ferma questa maledizione prima che contagi tutta la città!" }
    }
    message_wrath_of_bast_lions {
        id: 497,
        type: 2,

        size [30, 20]
        title { text: "Wrath of Bast" }
        video { text: "@20" }
        content { text: "Bast's patience is spent. From her temples — and even from the zoo, if you keep one — she unleashes a pride of lions into your streets. Citizens and soldiers alike scatter as the hunt begins — honor the Goddess of the Home before more blood stains the roads." }
    }
    message_invasion_quick_battle {
        id: 498,
        type: 7,
        size [30, 16]
        title { text: "Enemy at the Gates" }
        content { text: "An invading force has reached the city gates and awaits battle. Your generals will resolve the fight by army strength in a few days — or you may order them to engage now. Company micro is suspended for this wave. @PClick Go to Problem to reopen the quick-battle panel." }
    }
    message_invasion_auto_resolve_win {
        id: 499,
        type: 2,
        size [30, 16]
        title { text: "Victory!" }
        content { text: "Your generals have resolved the battle. The invaders are defeated. Some of your soldiers were lost in the fighting." }
    }
    message_invasion_auto_resolve_lose {
        id: 500,
        type: 2,
        size [30, 16]
        title { text: "Defeat" }
        content { text: "Your generals report defeat. The invading force was too strong. Many of your soldiers have fallen — but the enemy withdraws from the field." }
    }
    message_invasion_bribe_withdraw {
        id: 531,
        type: 2,
        size [30, 16]
        title { text: "Tribute Accepted" }
        content { text: "The invaders accepted your tribute and withdrew. Your treasury is lighter — but the city stands." }
    }
    message_wrath_of_seth_asps {
        id: 501,
        type: 2,

        size [30, 20]
        title { text: "Wrath of Seth" }
        video { text: "@21" }
        content { text: "Seth's fury finds no company to curse — so he sends asps from his temples into your streets. Citizens flee as the snakes hunt. Appease the God of Destruction before more blood is spilled." }
    }
    message_wrath_of_ptah_scorpions {
        id: 509,
        type: 2,

        size [30, 20]
        title { text: "Wrath of Ptah" }
        video { text: "@22" }
        content { text: "Ptah finds no workshops to smash — so he sends scorpions from his temples into your streets. Citizens scatter as the sting of the craftsman's wrath finds them. Honor the God of Crafts before more blood stains the roads." }
    }

    // Random / .map table events (price_change / demand_change / random_event).
    // Titles align with localization group 19 banner strings used by OG Popup Messages.
    message_kingdome_raises_wages {
        id: 502,
        type: 2,
        size [30, 20]
        title { text: "Wages raised in kingdom" }
        content { text: "Wages have increased throughout the Kingdom. Your own workers may depart for greener pastures if they are not paid as much as their counterparts in other cities." }
    }
    message_kingdome_lowers_wages {
        id: 503,
        type: 2,
        size [30, 20]
        title { text: "Wages lowered in kingdom" }
        content { text: "Wages have fallen throughout the Kingdom of Egypt. It seems everywhere people will work for less." }
    }
    message_price_increased {
        id: 504,
        type: 2,
        size [30, 20]
        title { text: "Price increase" }
        content { text: "The price of a trade good has risen." }
    }
    message_price_decreased {
        id: 505,
        type: 2,
        size [30, 20]
        title { text: "Price decrease" }
        content { text: "The price of a trade good has fallen." }
    }
    message_increased_trading {
        id: 506,
        type: 2,
        size [30, 20]
        title { text: "Trade increases with city" }
        content { text: "A trade city will buy or sell more of a good this year." }
    }
    message_decreased_trading {
        id: 507,
        type: 2,
        size [30, 20]
        title { text: "Trade decreases with city" }
        content { text: "A trade city will buy or sell less of a good this year." }
    }
    message_trade_stopped {
        id: 508,
        type: 2,
        size [30, 20]
        title { text: "Trade stopped" }
        content { text: "A trade city will no longer trade a good this year." }
    }

    // Monument completion popups (keys match city_message_post from mastaba/pyramid).
    // Eventmsg PHRASE_* strings are for the event system; these are lang message ids.
    pyramid_congratulations {
        id: 520,
        size [30, 18]
        title { text: "Pyramid finished!" }
        content {
            text: "This is a spectacular accomplishment! After countless months of labor the Pyramid is finally complete!"
        }
    }
    stepped_pyramid_congratulations {
        id: 521,
        size [30, 18]
        title { text: "Stepped Pyramid finished!" }
        content {
            text: "At long last the Stepped Pyramid is complete! This monument will forever stand as a testament to your abilities."
        }
    }
    bent_pyramid_congratulations {
        id: 522,
        size [30, 18]
        title { text: "Bent Pyramid finished!" }
        content {
            text: "Construction of the Bent Pyramid is finally complete! This is a stupendous achievement for your city."
        }
    }
    sun_temple_congratulations {
        id: 523,
        size [30, 18]
        title { text: "Sun Temple finished!" }
        content {
            text: "After many months of toil, work on the Sun Temple has finally come to a close. This is a great accomplishment for your city!"
        }
    }
    abu_simbel_congratulations {
        id: 525,
        size [30, 18]
        title { text: "Abu Simbel finished!" }
        content {
            text: "This is a truly spectacular achievement! Your skilled laborers have created an eternal monument that boasts of the glory of our pharaoh and the might of Egypt."
        }
    }
    caesareum_congratulations {
        id: 526,
        size [30, 18]
        title { text: "Caesareum finished!" }
        content {
            text: "The holy temple and resplendent gardened courtyards of the Caesareum are at long last complete! Word of its magnificent beauty is already spreading throughout the region."
        }
    }
    alex_library_congratulations {
        id: 527,
        size [30, 18]
        title { text: "Alexandria Library finished!" }
        content {
            text: "After much hard labor the beautiful hand-crafted doors of Alexandria's magnificent Great Library are ready to be opened wide to the scholars of the world."
        }
    }
    lighthouse_congratulations {
        id: 529,
        size [30, 18]
        title { text: "Pharos Lighthouse finished!" }
        content {
            text: "After much sweat and not a little shed blood, workmen have carefully placed the final block of marble for the wondrous Pharos Lighthouse! Already its towering bright beacon is attracting traders from all over."
        }
    }
    mausoleum_congratulations {
        id: 530,
        size [30, 18]
        title { text: "Mausoleum finished!" }
        content {
            text: "The sacred Mausoleum is finally complete! This is a remarkable achievement for your city."
        }
    }
    mudbrick_pyramid_congratulations {
        id: 528,
        size [30, 18]
        title { text: "Brick Pyramid finished!" }
        content {
            text: "Masons have completed their finishing touches on the gleaming outer casing of fine limestone, and the Brick Pyramid is finally done!"
        }
    }
    message_dike_breach {
        id: 524,
        type: 2,
        size [30, 16]
        title { text: "Dike breach" }
        content { text: "The wrath of Osiris has torn gaps in your floodplain embankments. Sealed basins are breached — repair the dikes before the next inundation if you want to hold the flood's gift." }
    }
}
