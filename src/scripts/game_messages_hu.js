log_info("akhenaten: messages config started")

game_messages_hu {
    message_potter_history {
        id: 1,

        size [30, 28]
        title { text: "Fazekas" }
        advisor: ADVISOR_TRADE
        content {
            text: "A fazekasoknak agyagellátásra van szükségük a működéshez. Egyes városok saját agyagot termelhetnek @92Agyag&gödrök építésével. Más városoknak kereskedelmi partnertől kell agyagot importálniuk (a kereskedelemről további információért kattints @47ide). @PCordások szállítják az agyagot a fazekasokhoz az Agyaggödrökből, ha a város rendelkezik ilyenekkel, vagy a @4Raktár&udvarokból. A fazekas némi tartalék agyagot is tárol az udvarán, hogy egy ideig tovább dolgozhasson, ha az agyagszállítás valamilyen okból megszakad. @PA fazekasoknak úthálózati kapcsolatra és közeli munkaerőforrásra is szükségük van. A fazekasok akkor a legtermelékenyebbek, ha teljes létszámmal dolgoznak, de létszámhiány esetén is működnek (bár csökkent hatékonysággal). Ha a fazekas kerámiát készít, láthatod, hogy keményen dolgozik. A fazekasnál dolgozó kordások az elkészült kerámiát egy Raktárudvarba vagy egy @473Lámpa&készítőhöz szállítják (akinek kerámiára és olajra van szüksége lámpák előállításához). @PA kerámia fontos árucikk a városban. @56Házaknak kerámiaellátásra van szükségük ahhoz, hogy magasabb szintre fejlődjenek, és a kerámiakészletet folyamatosan pótolni kell, hogy a házak ne süllyedjenek vissza alacsonyabb szintekre. A kerámia iránti kereslet soha nem szűnik meg: a háztartások mindig pótolják az eltört vagy elkopott edényeket. A késztermékek eljuttatásáról a lakosokhoz lásd a @2Piacok részt. @PA kerámia elengedhetetlen a @478Királyi&Temetkezési&Sírok építéséhez is. Amikor egy Lámpakészítő olajjal tölti meg a kerámiát, abból erős fényű lámpa lesz, amely megvilágítja a sírokon dolgozó munkások útját. @PA kerámia importálható vagy exportálható is. A kereskedelmi útvonalak megnyitásáról a @47kereskedelem résznél találsz információt. Ha városod kerámiával kereskedik, ügyelj a lakosok igényeire. A @24Kereskedelmi&felügyelő jelezheti, hogy mennyi kerámiát kell a Raktárudvarokban tárolni a polgárok számára, vagy rábízhatod a mennyiség meghatározását a felügyelőre. @PAz emberek nem szeretnek túl közel élni egy zajos és poros fazekashoz, ezért az csökkenti a környező területek vonzerejét. @L@LHa többet szeretnél megtudni az ókori egyiptomi fazekasságról, kattints @198ide."
        }
    }

    message_bazaar_history {
        id: 2,

        size [30, 28]
        title { text: "Piac" }
        content {
            text: "Piacok nélkül az emberek soha nem juthatnának hozzá a @3Magtárakban és a @4Raktár&udvarokban tárolt élelmiszerekhez és árucikkekhez. Csak a Piacok képesek eljuttatni a szükséges készleteket a lakossághoz. @PA megfelelő működéshez a Piacnak útkapcsolatra és teljes létszámú személyzetre van szüksége. A Piac létszámhiány esetén is működik, de jóval kisebb hatékonysággal. @PMinden Piac két beszerzőt alkalmaz: az egyik a Magtárakból vásárol élelmiszert, a másik a Raktárudvarokból szerzi be az árucikkeket. Mindkét beszerző szakosodott: a magtári beszerző nem tud árukat szerezni egy Raktárudvarból, és fordítva. Mindazonáltal mindkét beszerző egyszerre többféle árut is vásárolhat. Például egy olyan piaci beszerző, aki a Magtárhoz megy, vásárolhat gabonát és gránátalmát. Nem vásárolhat azonban gabonát és kerámiát, mert kerámiát soha nem tárolnak Magtárban. @PAmikor egy piaci beszerző megtalálja a szükséges árukat, segítők sora hordja vissza a rakományt a Piacra. @PA piaci beszerző egy @42'célállomás&járókelő'. Életét azzal tölti, hogy a Piac és a város Magtárai, illetve Raktárudvarai között ingázik. Munkaköre mentesíti attól, hogy az egész városon keresztül gyalogoljon a készletekért, és hatótávolságán belül legfeljebb három ellátási forrással üzletel. Ha azt látod, hogy tétlenül álldogál, miközben lenne munkája, valószínűleg túl hosszú útvonalat vársz el tőle, vagy túl sok beszállítóval kellene kapcsolatot tartania. @PA Piac másik alkalmazottja, a piaci árus, a beszerzők által visszahozott árukat osztja szét a közeli lakónegyedekben. Amikor az árus két mezőn belül elhalad egy lakóház mellett, ellátja azt mindazzal, amire szüksége van, feltéve hogy a megfelelő árucikk rendelkezésére áll. Azt is felméri, milyen árukra van szükségük a vásárlóknak ahhoz, hogy lakóházaik fejlődhessenek, majd ezt jelenti a beszerzőnek, hogy az megszerezhesse a szükséges készleteket. Az elsődleges cél a házak visszafejlődésének megakadályozásához szükséges áruk pótlása (lásd a @56lakóházak&és&vonzerejük bejegyzést). Ha ezek az igények teljesültek, megpróbálják beszerezni a következő árucikket, amely a ház fejlődéséhez szükséges. @PA piaci árus tehát egy 'vándorló járókelő'. Feladata, hogy a közeli utcablokkokban járkáljon és kiszolgálja vásárlóit, nem pedig az, hogy egy meghatározott célállomásra jusson el. Ha egy adott lakónegyed nem kap árukat, figyeld meg, merre jár az árus. Nem követ előre meghatározott útvonalat. Minden alkalommal, amikor egy kereszteződéshez ér, eldönti, merre menjen tovább, és nem mindig ugyanazt az utat választja. Gondosan tervezd meg a város útjait, és használd a @358Út&akadályokat a piaci árusok irányítására. Egy fejlettebb szintre fejlődött Piac (amit az jelez, hogy egyik sátrát egy kis épület váltotta fel) egy helyett két 'vándorló járókelőt' küld ki. @PA lakosság alapvető szükségleteit, például az élelmet és a kerámiát, ki kell elégíteni, mielőtt fejlettebb igényeik, például a sör vagy a vászon kielégítésére kerülne sor. A piaci beszerzők figyelmen kívül hagynak egy vászonnal teli Raktárudvart, ha az általuk ellátott házak éppen kerámiáért kiáltanak. Ezért nagyon fontos, hogy egy árucikkből folyamatos utánpótlást biztosíts, amint a házak elkezdik igényelni azt. Ne feledd, hogy a házak fejlődésük során általában több lakónak adnak otthont, és így több árut is fogyasztanak. Néha további Piacokat kell építened, hogy egy városrész megfelelő ellátását fenntartsd. Jobb egérgombbal kattints egy házra, hogy lásd, lakói éppen mire tartanak igényt. @PA lakók megfelelő élelmiszer- és áruellátásának biztosításához építs Magtárakat és Raktárudvarokat a Piacok közelében. Használd a Magtárak és Raktárudvarok különleges utasításait annak biztosítására, hogy rendelkezzenek a Piacok számára szükséges élelmiszerekkel és árucikkekkel. @PHa nagyobb irányítást szeretnél egy Piac felett, kattints a 'Különleges utasítások' gombra, hogy megjelenjen az összes árucikk listája, amelyet tárolhat. Kattints egy árura annak megadásához, hogy a Piac vásárolja-e vagy sem. @PMiközben a polgároknak Piacok közelében kell élniük ahhoz, hogy hozzáférjenek minden kívánt áruhoz, senki sem szeretne túl közel lakni hozzájuk. Zajos helyek, ahol néha kellemetlen alakok fordulnak meg, és még szaguk is lehet. @L@LAz ókori egyiptomi Piac látványának, hangjainak és illatainak megismeréséhez kattints @199ide."
        }
    }

    message_building_granary {
        id: 3,

        size [30, 28]
        title { text: "Magtár" }
        content {
            text: "A Magtárak tárolják a lakosok által fogyasztott élelmiszereket. A @2Piac&beszerzői a Magtárból gyűjtik össze az élelmiszert, hogy szétosszák a lakosság között. @PA Magtárak működéséhez útkapcsolatra és munkaerőre van szükség. A tárolónyílások megtekintésével láthatod, mit tárol a Magtár. Jobb egérgombbal kattintva egy Magtárra pontosan láthatod, mennyit tartalmaz az egyes élelmiszerekből. @45Élelmiszer&farmok, @84Halász&mólók, @360Marha&telepek és @359Vadász&kunyhók szállítókat alkalmaznak, akik a terményeiket és zsákmányukat a Magtárakba viszik. Általában jó ötlet a Magtárakat az élelmiszer-termelő létesítmények közelében elhelyezni. Ha egy szállítónak olyan messzire kell gyalogolnia, hogy munkaadója újabb adag élelmiszert termel, mielőtt az üres kocsijával visszatérne, akkor a termelőlétesítmény tétlenül fog állni, amíg a szállító el nem viszi az ott felhalmozódott élelmiszert. @PHa minden Magtár megtelt, a szállítók várakozni fognak, amíg hely nem szabadul fel valamelyik Magtárban, kivéve ha utasítottál egy @4Raktár&udvart arra, hogy fogadja az adott élelmiszert. @PA város élelmiszer-ellátásának szabályozásához adj különleges utasításokat a Magtáraknak. Kattints jobb egérgombbal egy Magtárra, majd kattints a Különleges utasítások gombra a kezdéshez. A Magtárban tárolható összes élelmiszer fel lesz sorolva. Egy adott élelmiszerre kattintva megváltoztathatod, hogyan kezelje azt az adott Magtár. A lehetőségek a következők: @L@LMindent elfogad / Magtár feltöltése @LAz egyes élelmiszerekből tárolható mennyiség korlátozásához használd a Feltöltés parancsot. Beállíthatod, hogy a Magtár kapacitásának 1/4-éig, 1/2-éig vagy 3/4-éig töltse fel magát. Ha nem akarod korlátozni egy adott élelmiszer mennyiségét, válaszd a Mindent elfogad lehetőséget. Ez akkor hasznos, ha azt szeretnéd, hogy egy Magtár többféle élelmiszerből azonos mennyiséget tároljon. @L@LNe fogadja el @LEzzel az utasítással megakadályozhatod, hogy egy Magtár egyáltalán elfogadjon egy adott élelmiszert. A Magtár nem vesz át új szállítmányokat az adott élelmiszerből, de a piaci beszerzők és más Magtárak kordásai továbbra is elvihetik onnan a készletet, amíg teljesen ki nem ürül. Használd ezt a lehetőséget, ha azt akarod, hogy a szállítók egy közeli Magtár helyett egy távolabbit használjanak, vagy ha meg akarod akadályozni, hogy egy exportra szánt élelmiszert elfogyasszanak. @L@LLegyen legfeljebb @LHa egy Magtárban kevés van egy olyan élelmiszerből, amelyet szeretnél ott készleten tartani, használd a Legyen legfeljebb parancsot. A Magtár kordása más Magtárakban vagy a város Raktárudvaraiban keresni fogja az adott élelmiszert, amíg a kért mennyiséget el nem éri. Beállíthatod, hogy a Magtár kapacitásának 1/4-éig, 1/2-éig, 3/4-éig vagy teljes kapacitásáig szerezzen be az adott élelmiszerből. Ez lehetővé teszi, hogy a város élelmiszer-termelőitől távol eső Magtárak is feltöltve maradjanak. @L@LÉlelmiszer kiürítése @LHa ezt az utasítást adod ki, a Magtár kordásai megpróbálják kiüríteni a Magtár élelmiszerkészletét, olyan más Magtárakat vagy Raktárudvarokat keresve, amelyek engedélyezték az adott élelmiszer fogadását. Az önmagát kiürítő Magtár nem fogad új szállítmányokat abból az élelmiszerből, amelyet máshová próbál továbbítani. Használd ezt a parancsot, ha úgy döntöttél, hogy lebontod a Magtárat, vagy ha el szeretnéd távolítani az általa tárolt egyik élelmiszertípust. @L@LA Magtárak porosak, gyakran kártevőkkel teli helyek, és egyáltalán nem kellemes szomszédok. A lakosok nem szívesen élnek a közelükben. @L@LAz ókori egyiptomi Magtárakról szóló olvasmányhoz kattints @5ide."
        }
    }

    message_building_storage_yard {
        id: 4,

        size [30, 28]
        title { text: "Raktárudvar" }
        content {
            text: "A Raktárudvarok minden késztermék és felesleges nyersanyag tárolóhelyei. Élelmiszert is tárolhatnak, ha ezt külön engedélyezed számukra (lásd lentebb a Különleges utasítások részt), valamint segítik az importált és exportált áruk kereskedelmét (lásd a @47kereskedelem bejegyzést). @PA működéshez a Raktárudvaroknak útkapcsolatra és közeli munkaerőforrásra van szükségük. A Raktárudvarok akkor a leghatékonyabbak, ha teljes létszámmal működnek. Létszámhiány esetén is üzemelhetnek, de előfordulhat, hogy bizonyos árucikkeket nem fogadnak el. @PMinden Raktárudvar nyolc részre van osztva, és legfeljebb nyolcféle árut képes tárolni. Egy részleg csak egyféle árut fogadhat, de több részleg is tárolhatja ugyanazt az árucikket. Az egyes árukból tárolható mennyiség az adott áru méretétől függ. Minél nagyobb egy áru, annál kevesebb fér el belőle egy Raktárudvarban. Például egy Raktárudvar egyik részében sokkal több kerámiadarab fér el, mint kőtömb. @PSok más épületnek könnyű hozzáférésre van szüksége a Raktárudvarokhoz. Az @46Ipar a legközelebbi Raktárudvarba szállítja termékeit, a piaci beszerzők pedig a legközelebbi Raktárudvarhoz mennek azokért az árukért, amelyekre vásárlóiknak szükségük van. A Raktárudvarok pedig elsősorban a legközelebbi épületekhez szállítják a nyersanyagokat és egyéb szükséges készleteket. A Raktárudvarok kordásai vonakodva ugyan, de szükség esetén nagy távolságokat is megtesznek, azonban az ipari létesítmények tétlenül állhatnak, amíg a szükséges alapanyagokra várnak. Érdemes a Raktárudvarokat minden olyan létesítmény közelében elhelyezni, amelynek szüksége van rájuk. @PKattints jobb egérgombbal egy Raktárudvarra, hogy pontosan lásd, mennyi van benne az egyes árucikkekből, és hogy fogadhat-e még további készleteket. Ha egy Raktárudvar már nem tud többet tárolni egy adott áruból, az adott áru sárgával jelenik meg. @PAz áruk be- és kiáramlását a Különleges utasításokkal szabályozhatod. Amikor a Különleges utasítások gombra kattintasz, megjelenik egy lista a városod számára jelenleg elérhető összes árucikkről. Néha több tucat különböző áru állhat rendelkezésedre. A képernyő tetején található görgetőgombokkal további elérhető árukat tekinthetsz meg. @PKattints egy árucikkre, hogy megadd a Raktárudvar számára, hogyan kezelje azt. A lehetőségek a következők: @L@LMindent elfogad / Feltöltés @LEgyetlen áruból tárolható mennyiség korlátozásához használd a Feltöltés parancsot. Beállíthatod, hogy a Raktárudvar kapacitásának 1/4-éig, 1/2-éig vagy 3/4-éig töltse fel magát. Ha nem akarod korlátozni egy adott áru mennyiségét, válaszd a Mindent elfogad lehetőséget. Ez akkor hasznos, ha azt szeretnéd, hogy egy Raktárudvar többféle áruból azonos mennyiséget tároljon, vagy ha egy udvarban exportálásra szánt élelmiszert akarsz tárolni. @L@LNe fogadja el @LEzzel az utasítással megakadályozhatod, hogy egy Raktárudvar egyáltalán elfogadjon egy adott árut. A Raktárudvar nem vesz át új szállítmányokat az adott áruból, de a piaci beszerzők, kereskedelmi partnerek és a város ipari létesítményei továbbra is felhasználhatják a Raktárudvarban meglévő készletet, amíg az teljesen ki nem fogy. Használd ezt a lehetőséget, ha azt szeretnéd, hogy a szállítók egy közeli Raktárudvar helyett egy távolabbit használjanak. Alapértelmezés szerint a Raktárudvarok nem fogadnak el élelmiszert, így biztosítva, hogy az élelmiszer a Magtárakba kerüljön. @L@LLegyen legfeljebb @LHa egy Raktárudvarban kevés van egy olyan áruból, amelyet szeretnél készleten tartani, használd a Legyen legfeljebb parancsot. A Raktárudvar kordása más Raktárudvarokban keresni fogja az adott árut, amíg a kért mennyiséget el nem éri. Beállíthatod, hogy a Raktárudvar kapacitásának 1/4-éig, 1/2-éig, 3/4-éig vagy teljes kapacitásáig szerezzen be az adott áruból. Ez lehetővé teszi, hogy a távolabbi Raktárudvarok is feltöltve maradjanak. @L@LKiürítés @LHa ezt az utasítást adod ki, a Raktárudvar kordása megpróbálja kiüríteni az adott árucikk készletét, olyan ipari létesítményeket vagy más Raktárudvarokat keresve, amelyek fogadni tudják azt. Használd ezt a parancsot, ha úgy döntöttél, hogy lebontod a Raktárudvart, vagy ha el szeretnéd távolítani az ott tárolt egyik árufajtát. @L@LA Raktárudvarok kulcsszerepet játszanak abban, hogy az áruk eljussanak a város lakóihoz. A @2Piacok közvetlenül a Raktárudvarokból szerzik be a polgárok által igényelt árukat. A Raktárudvarok a kereskedelem szempontjából is nélkülözhetetlenek. Minden importált áru a Raktárudvarokban kerül tárolásra, és minden exportra kijelölt árut ott tartanak addig, amíg más városok kereskedői el nem jönnek érte. @L@LAz ókori egyiptomi Raktárudvarokról szóló olvasmányhoz kattints @6ide."
        }
    }

    message_granary_history_2 {
        id: 5

        size [30, 20]
        title { text: "Magtár" }
        content {
            text: "Mivel az áradás időszakában a földművelés nagyrészt lehetetlen volt, a magtárak létfontosságú szerepet játszottak abban, hogy az ókori egyiptomiak egész évben elegendő élelemhez jussanak. A magtárak nemcsak gabonát és más élelmiszereket tároltak, hanem lisztet is készítettek. @L@LA magtárak az idők során fejlődtek. A korai dinasztikus korban az egyiptomi magtár kúp alakú volt, kupolás tetővel. Fából vagy téglából építették őket, a legnagyobbakhoz pedig létrák vagy lépcsők vezettek a betöltőnyíláshoz. A Középbirodalom idején a magtárak négyszögletes formát kaptak, lapos tetővel és több betöltőnyílással, hasonlóan a játékban ábrázolt épületekhez. A magtárak egy harmadik típusát kizárólag a következő vetési időszakban elültetendő vetőmag tárolására használták. Ezek a magtárak trapéz alakúak voltak, ami jól megkülönböztette őket az élelmiszer tárolására szolgáló magtáraktól, így a vetőmagot nem fogyasztották el tévedésből. @L@LA legtöbb magtárat szigorú állami felügyelet alatt tartották. A katonák, építőmunkások és más, mezőgazdasággal nem foglalkozó dolgozók mind ezekből a magtárakból kapták élelmüket. Néhány gazdag magánszemély saját magtárral rendelkezett, és bizonyos parasztoknak is voltak kisebb magtáraik, amelyekben a termés azon részét tárolták, amelyet megtarthattak maguknak."
        }
    }

    message_storage_yard_history {
        id: 6

        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Raktárudvar", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "A Nílus közelében és a fontos kereskedelmi útvonalak mentén elhelyezkedő Raktárudvarok a felesleges készletek és a kereskedelemre szánt áruk tárolására szolgáltak. Mivel kevés csapadék hullott, az ókori Egyiptomban sok Raktárudvar szabadtéri volt. Írnokok szigorú felügyelete alatt álltak, akik pontos nyilvántartást vezettek a készletekről."
        }
    }

    message_keyboard_commands {
        id: 7

        size [30, 28]
        title { text: "Billentyűparancsok" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A Pharaoh számos parancsa kiadható a billentyűzet segítségével. A parancsok a következők: @L@LBillentyű    Hatás @LA      A kijelölt hadihajót támadásra utasítja @Paz összes ellenség ellen. @L@LC      Megjeleníti a kockázatok: Bűnözés fedvényt, @Pvagy a kijelölt harci szekércsapatot @Ptámadásra utasítja. @L@LD      Megjeleníti a kockázatok: Épületkárok fedvényt. @L@LE      A kijelölt szállítóhajót arra utasítja, @Phogy kerülje el az ellenséget. @L@LF      Megjeleníti a kockázatok: Tűz fedvényt, @Pvagy a kijelölt csapatot visszaküldi a @Perődjébe. @L@LH      Elrejti a sziklafelszínt. @L@P       A kijelölt hajót jelenlegi helyének @Pmegtartására utasítja. @L@LL      Minden megnyomáskor másik @Pkatonai egységre központosítja a nézetet. @L@PHa egy csapat van kijelölve, az 'L' @Pa 'laza alakzatban tartsd a helyed' parancsot adja ki. @L@LM      Amikor egy műemléket választasz ki az @Pépítési listából, annak képe a kurzorhoz kapcsolódik, @Pés megmutatja, mekkora területet foglal majd el @Pa műemlék. Az 'M' billentyű lenyomva tartása @Prögzíti a műemlék 'helyigényét' @Paz adott helyre, így körbenézhetsz @Pa városban anélkül, hogy elmozdítanád a @Pműemlék ideiglenes helyét. Engedd fel @Paz 'M' billentyűt a normál egérműködéshez, @Pvagy kattints a műemlék elhelyezéséhez @Pa kijelölt terület aktuális helyén. @L@P       Ha egy katonai egység van kijelölve, @Paz 'M' billentyű a felszámolási @Pparancsot adja ki. @L@LN      A kijelölt csapatot vagy @Phadihajót a közeli ellenségek megtámadására utasítja. @L@LP      Megállítja az idő múlását a játékban. @PIdőmegállítás közben nem építhetsz. @L@LR      Szobor, kapuház vagy templomkomplexum @Pelhelyezésekor az 'R' elforgatja az @Pépület irányát negyed fordulattal @Paz óramutató járásával megegyező irányba. @PA szobrok többféle @Pstílusban jelennek meg. @L@P       Kijelölt katonai egységnél az @P'R' parancs a katonák irányának @Pmegváltoztatását (elfordítását) adja ki. Az 'R' @Pegy kijelölt szállító- vagy hadihajót is arra utasít, @Phogy térjen vissza a hajóácshoz javításra. @L@LT      Megjeleníti a kockázatok: Problémák @Pfedvényt. @L@P       Kijelölt katonai egységnél a @P'T' parancs a 'szoros alakzatban tartsd a helyed' @Pparancsot adja ki. @L@LW      Megjeleníti a víz fedvényt. @L@PHa egy hadihajó vagy szállítóhajó van @Pkijelölve, a 'W' parancs visszaküldi a hajót @Pa saját kikötőjébe. @L@LX      Megjeleníti az adók fedvényt. @L@LY      Megjeleníti a kockázatok: Malária fedvényt. @L@LZ      Megjeleníti a kockázatok: Betegség fedvényt. @L@LSzóköz   A szóköz billentyűvel válthatsz @Pa legutóbb kiválasztott fedvény és a @Pnormál városnézet között. @L@LEsc    Kilép a játékból. @L@LNyitó zárójel @P10 százalékkal csökkenti a játék sebességét. @L@LZáró zárójel @P10 százalékkal növeli a játék sebességét. @L@LÉkezetes billentyű @P@L@L1       Munkaügyi felügyelő @L@L2      Katonai felügyelő @L@L3      Politikai felügyelő @L@L4      Minősítési felügyelő @L@L5      Kereskedelmi felügyelő @L@L6      Magtárak felügyelője @L@L7      Közegészségügyi felügyelő @L@L8      Oktatási felügyelő @L@L9      Szórakoztatási felügyelő @L@L0      Templomok felügyelője @L@L-      (mínuszjel) Főfelügyelő @L@L=      (egyenlőségjel) Műemlékek felügyelője @L@LCTRL+F1 @Létrehozza az F1 helyjelzőt az aktuális helyen @L@LCTRL+F2 @Létrehozza az F2 helyjelzőt az aktuális helyen @L@LCTRL+F3 @Létrehozza az F3 helyjelzőt az aktuális helyen @L@LF1     Ugrás az F1 helyjelzőhöz @L@LF2     Ugrás az F2 helyjelzőhöz @L@LF3     Ugrás az F3 helyjelzőhöz @L@LF6     Váltás ablakos nézetre @L@LF7     640x480-as képernyőfelbontás beállítása @L@LF8     800x600-as képernyőfelbontás beállítása @L@LF9     1024x768-as képernyőfelbontás beállítása"
        }
    }

    message_work_camp_history {
        id: 8

        size [30, 28]
        title { text: "Munkatábor" }
        content {
            text: "A parasztok a Munkatáborokban gyülekeznek, ahol a közeli @45ártéri&földek művelésére vagy @370műemlékek építésére osztják be őket. A termesztési időszakban a legtöbb paraszt mezőgazdasági munkát végez. Az áradás idején mindenki a város műemléképítési projektjén dolgozik. Ha éppen nincs épülő műemlék, a parasztmunkásoknak nincs más dolguk, mint hogy az áradás alatt sokat játsszanak szenetet. Ha városodban kevés a Munkatábor az ártéri földek számához képest, észreveheted az áradás által meghatározott jellegzetes munkaritmust. @PA Munkatáboroknak útkapcsolatra és saját személyzetre van szükségük. A legjobb, ha a Munkatáborokat a földek és a műemlékek közelében helyezed el, hogy a parasztoknak ne kelljen messzire gyalogolniuk. Valójában korlátozott, milyen messzire hajlandók elmenni a nehéz fizikai munkához. Minél több Munkatábora van a városnak, annál gyorsabban épülhetnek a műemlékek, mert a termesztési időszak alatt több munkás áll rendelkezésre. @PAz egy Munkatábor által ellátható földek száma elsősorban a közelségtől függ. Egy teljes létszámmal működő Munkatábor hetente egy parasztmunkást biztosít (havonta négyet). Ez a munkás elsétál a legközelebbi olyan ártéri földhöz, amely parasztra vár, ahol hat hónapon keresztül dolgozik. @PAmikor egy föld már túl van a paraszt munkaperiódusának felén, a Munkatábor dolgozói észreveszik, hogy újabb parasztra lesz szükség a folyamatos művelés fenntartásához – ne feledd, hogy a termesztési időszak a legtöbb területen kilenc hónapig tart. Ha egyetlen Munkatábort használsz nagyszámú föld ellátására, előfordulhat, hogy néhány föld soha nem kap parasztot, a többiek pedig nehezen tudják folyamatosan fenntartani a paraszti munkaerőt. @PElméletileg hatalmas számú ártéri földet is működtethetnél csupán egy vagy két Munkatáborral, de sok föld nem érné el teljes termelési lehetőségét, és a parasztok csak az áradás idején lennének elérhetők a műemlék építéséhez. @PGyakorlati szempontból egyetlen Munkatábor négy-hat közeli ártéri földet képes megszakítás nélkül ellátni, miközben néhány parasztot továbbra is biztosít a város műemléképítési projektjéhez. További Munkatáborok építése megosztja a terheket, és több parasztot szabadít fel arra, hogy a termesztési időszak alatt a műemléken dolgozzon. @L@LAz ókori egyiptomi munkáséletről további információért kattints @155ide."
        }
    }

    message_frequently_asked_questions {
        id: 9
        
        size [30, 28]
        title { text: "Gyakran Ismételt Kérdések" }
        content {
            text: "Pénz @PQ: Azt akarom, hogy a városomnak legyen pénze – méghozzá rengeteg. Mi a legjobb módja a város kincstárának feltöltésére? @PA: A legegyszerűbb válasz: gondoskodj róla, hogy a város bevételei meghaladják a kiadásait. @PMFigyelj rá, hogy a lakosok szinte mindegyike adót fizessen. Az adókulcs emelése növeli a kincstár bevételeit, de a pénz nem biztos, hogy ellensúlyozza a magasabb adók által okozott rosszabb @39City&Sentimentet. Emellett minél hamarabb nyiss @47kereskedelmi kapcsolatokat, és exportálj, amennyit csak tudsz (a @32World&Map segítségével láthatod, milyen közel van a város az éves kereskedelmi korlátaihoz). @P A kiadások csökkentése szintén növeli a nyereséget. Lassan és körültekintően építsd a várost. Az épületek természetesen pénzbe kerülnek, de számolnod kell az alkalmazottak fizetésével, valamint a számukra biztosított lakhatás és szolgáltatások költségeivel is. Ha túl gyorsan fejleszted a várost, könnyen adósságba kerülhetsz a bérek és a kapcsolódó szolgáltatások miatt. @L@PQ: Miért nem tud a városom adót beszedni? @PA: Győződj meg róla, hogy építettél egy Palotát. A városok nem szedhetnek adót Palota építése nélkül. @L@PQ: Keményen dolgozom, amennyire csak lehet, mégsem kaptam fizetést. Miért? @PA: Bizony gyakori panasz. A Pharaohban nem kaphatsz személyes fizetést, amíg nem építettél egy Kúriát. @L@PQ: Hogyan fizethetek sarcot? Mi történik, ha nem teszem? @PA: A kincstárad automatikusan kifizeti a sarcot az év végén, feltéve, hogy van rá pénzed. Csak arra ügyelj, hogy az év végén legyen pénz a kincstárban. Ha üres a kassza, nem tudsz sarcot fizetni, és a @35Kingdom&rating értéked csökkenni fog. Ha egy második egymást követő évben sem tudsz sarcot fizetni, a Királyság-értéked ismét csökken, és ha az eladósodás tovább folytatódik, a büntetés még súlyosabb lesz. Olvasd el az @48adósságról szóló részt. @L@LÚtvonaljárók @L@PQ: Miért nem talál dolgozókat egy épület, amely azt írja, hogy van munkaerő-hozzáférése? @PA: Valószínűleg túl közel építettél egy @358Útakadályt az épülethez. Figyeld egy pillanatig az épületet, hogy megbizonyosodj róla: a járókelője az Útakadály megfelelő oldalán jelenik-e meg. Néha az épület dolgozója rossz irányba indul el. Ez különösen bosszantó a munkaerőt kereső épületeknél, mert az alkalmazó épület úgy érzékeli, hogy hozzáfér a munkaerőhöz, de az Útakadály megakadályozza, hogy a járókelő valaha is elérje a munkaerőforrást. Építsd újjá az Útakadályt egy mezővel távolabb. @L@LVallás @PQ: Szeretnék fesztivált rendezni, de nem engedi. Miért? @PA: Több oka is lehet annak, hogy nem rendezhetsz fesztivált. Van a városodban Fesztiváltér? Ha nincs tér, nincs fesztivál sem. Rendeztél már két fesztivált az elmúlt 12 hónapban? Egy város csak két fesztivált tarthat bármely 12 hónapos időszakban. Ha nagy fesztivált rendezel, győződj meg róla, hogy elegendő söröd van az eseményhez. Végül ellenőrizd a város kincstárát. Ha a város nem tudja kifizetni a fesztivált, nem rendezhetsz egyet. @L@PQ: A városom védőistene állandóan haragszik rám. Mit kell tennem, hogy kiengeszteljem? @PA: A város védőistene több figyelmet igényel, mint a helyi istenek. Ügyelj rá, hogy több neki szentelt templomod és szentélyed legyen, mint a város többi istenének, és fontold meg egy Nagy Templomkomplexum építését a tiszteletére. @L@LSzórakoztatás @PQ: Nem találok megfelelő helyet a szórakoztató épületnek. Mi lehet a probléma? @PA: A Senet Házak kivételével a szórakoztató épületeket kereszteződésre, vagyis „T” alakú elágazásra vagy útkereszteződésre kell helyezni. Emellett a kereszteződés körül elegendő szabad helynek kell lennie az épületek színpadai számára. @L@PQ: Rengeteg szórakoztató épületem van a városban, még sincsenek előadók. Miért nem rendeznek műsorokat? @PA: Győződj meg róla, hogy építettél Kiképzőközpontokat a városban. Az előadóknak először meg kell tanulniuk a mesterségüket, mielőtt szórakoztathatják a tömegeket. @L@PQ: Miért nem működik a Senet Házam? @PA: A válasz: sör. Győződj meg róla, hogy a Senet Házban van sör a vendégek kiszolgálására. @L@LMezőgazdaság @PQ: Miért nem termelnek a folyó menti földek termést? @PA: Ellenőrizd, hogy van-e Munkahely a földek közelében. A Munkahelyek parasztjai művelik a folyó menti termőföldeket. @L@PQ: Hány folyó menti farmot tud ellátni egy Munkahely? @PA: Ez helyzettől függ. A teljes magyarázatért olvasd el a @8Work&Camps súgóbejegyzést. @L@PQ: Építettem egy Halászkikötőt, de nincs hajója. Miért? @PA: A halászhajókat Hajóács építi. Győződj meg róla, hogy van működő Hajóács a városban. @L@LTárolás és elosztás @PQ: A bazárok állandóan kifogynak az élelmiszerből és az árukból. Mit tehetek, hogy mindig legyen készletük? @PA: Építs Magtárt és Raktárudvart a Bazár közelében. Ha egy bazárvásárlónak hosszú utat kell megtennie, a bazárja biztosan kifogy valamiből, mire visszaér. Használd a Magtár és a Raktárudvar különleges utasításait, hogy ezek az épületek megfelelően fel legyenek töltve készletekkel. @L@PQ: Hogyan használhatom a leghatékonyabban a Raktárudvarokat? @PA: Hogy a legtöbbet hozd ki a @4Storage&Yardsból, gondosan válaszd meg a helyüket a városban, és jól használd a különleges utasításaikat. A Raktárudvarokat olyan épületek közelébe érdemes helyezni, mint a Bazárok, Kikötők, emlékmű-építési helyszínek és iparágak, amelyeknek szükségük van a bennük tárolt készletekre. Használd a Raktárudvar különleges utasításait, hogy a tárolt áruk azok legyenek, amelyekre a közeli épületeknek szükségük van. A Raktárudvarokat érdemes ipari épületek közelében is elhelyezni, hogy csökkentsd az ipari szállítókocsik idejét, amit úton töltenek. Ha a szállító hosszú utat kénytelen megtenni az áruk leszállításához, az iparág távollétében leállhat. @L@LEmlékművek @PQ: Mit tehetek, hogy felgyorsítsam az emlékmű építését? @PA: Építs sok Munkahelyet, a szükséges Építőcéheket, valamint olyan Raktárudvarokat az építési hely közelében, amelyek csak építőanyagokat fogadnak. Ha a városod képes saját maga előállítani az építőanyagokat, gondoskodj róla, hogy elegendő kőbányád és Téglagyárad legyen a Raktárudvarok feltöltéséhez. Arra is ügyelj, hogy a városnak legyen elég fája, hogy az Ácscéh rámpákat és állványzatokat építhessen. Ha a város nem tudja előállítani a szükséges nyersanyagokat, importálj belőlük annyit, amennyit csak tudsz a kereskedelmi partnereidtől. Ha az emlékmű építése bármilyen okból lelassul, jobb gombbal kattints az építési területre, és kérdezd meg az építésvezetőt. Megmondja, mi akadályozza az építkezést. Ha több építési helyszíned is van a városban, előfordulhat, hogy a parasztok és az építőmunkások nem tudnak megegyezni, hol kezdjék a munkát, ezért egyik helyszínen sem dolgoznak. @L@PQ: Egy bizonyos nyersanyagra van szükségem az emlékmű építéséhez, de a városom nem tudja előállítani, és senki sem akarja eladni nekem. Elrontották a küldetés készítői? @PA: Egyes küldetésekben a szükséges kereskedelmi útvonal csak akkor válik elérhetővé, ha teljesíted más városok kéréseit (különösen a katonai segítségkéréseket). Ha az első kérést nem sikerül teljesítened, általában lesz lehetőséged helyrehozni a hibát, és ezáltal megnyitni a létfontosságú kereskedelmi útvonalat. Ha továbbra is kudarcot vallasz ezekben a kérésekben, elveszítheted a küldetést. Minden küldetés tartalmazza az összes szükséges árut… de néha meg kell dolgoznod értük, és a siker nem mindig garantált. @L@L Kereskedelem @PQ: Megnyitottam egy kereskedelmi útvonalat, de a városom semmit sem importál vagy exportál. Hogyan indíthatom be a kereskedelmet? @PA: Látogasd meg a Kereskedelmi felügyelődet, és mondd meg neki, mely termékeket vásárolja vagy adja el. Győződj meg arról is, hogy van Raktárudvar a városban, valamint Kikötő, ha a kereskedelmi partnered vízen érkezik. @L@PQ: Élelmiszert próbálok importálni. Nyitva van a kereskedelmi útvonal, és megmondtam a Kereskedelmi felügyelőnek, hogy importálja, mégsem érkezik étel. Az emberek éheznek – mit tehetek? @PA: Győződj meg róla, hogy a Raktárudvarok engedélyt kaptak az importálni kívánt élelmiszer fogadására. Ne feledd, hogy a Raktárudvarok alapértelmezés szerint nem fogadnak élelmiszert. @L@PQ: Hagytam, hogy a @24Overseer&of&Commerce határozza meg a kereskedelmi áruk szintjét a Raktárudvarokban. Hogyan lehetek biztos benne, hogy jó döntéseket hoz? @PA: Amikor megkéred a Kereskedelmi felügyelőt, hogy kezelje a kereskedelmet, figyelembe veszi a város lakosságának méretét, az iparágakat, amelyekkel a város rendelkezik, valamint az éppen épülő emlékműveket. Csak ezen tényezők elemzése alapján felméri a város szükségleteit. Ha látni szeretnéd az ajánlásait, kattints az árukezelő gombjaira. Amikor megjelenik a gomb, amellyel beállíthatod a szintet, az alapértelmezettként látható mennyiség az az érték, amelyet a Kereskedelmi felügyelő szerint a városnak a Raktárudvarokban kell tartania. @L@LLakónegyedek @PQ: A kijelölt lakóterületeim folyamatosan eltűnnek. Mi történik? @PA: Minden lakóterületnek legfeljebb két mező távolságra kell lennie egy úttól. Ha nem így van, eltűnik. Emellett a bevándorlóknak el kell tudniuk érniük a lakónegyedeket. Győződj meg róla, hogy szabad útvonal van a bevándorlók városba való belépési és kilépési pontjai (a @57Kingdom&Road) és a lakóhelyeid között."
        }
    }

    message_table_of_contents {
        id: 10

        size [30, 28]
        image { id: 47, pos [15, 15] }
        title { text: "Tartalomjegyzék" }
        subtitle { text: "Kattints egy témára a súgó megtekintéséhez" }
        content {
            text: " @9Gyakori&kérdések @L@LSegédtémák @L@492Abu&Simbel @L@88Akadémia @L@488Alexandriai&könyvtár @L@65Patika @L@81Építész&állomás @L@L@72Zenepavilon @L@91Árpafarm @L@2Bazár @L@2Bazár&különleges&rendelések @L@54Hajlított&piramisa @L@71Bódé @L@96Sörfőzde @L@55Téglapiramis @L@363Téglakészítők&céhe @L@364Téglagyár @L@58Híd @L@33Épületgombok @L@374Temetési&kellékek @L@L@490Caesareum @L@363Asztalosok&céhe @L@360Marhafarm @L@98Harckocsikészítő @L@90Csicseriborsó-farm @L@31Főfelügyelő @L@53Városi&egészség @L@39Városi&hangulat @L@92Agyagbánya @L@37Vállalkozások @L@87Vállalati&rendelések @L@369Építésvezető @L@363Építőipari&céhek @L@19Vezérlőpult&kapcsoló @L@93Rézbánya @L@76Bíróság @L@36Bűnözés @L@35Kultúra&értékelés @L@L@17Dátumkijelzés @L@48Adósság @L@85Védelmi&építmények @L@63Fogorvos @L@56Vonzerejűség @L@83Kikötő @L@44Ivóvíz @L@L@50Oktatás @L@43Foglalkoztatás @L@49Szórakozás @L@L@45Mezőgazdaság (lásd még az egyes farmokat) @L@11Fájlmenü @L@355Tűzőrség @L@58Komp @L@366Fesztiváltér @L@29Fesztiválok @L@84Halászkikötő @L@91Lenfarm @L@45Élelem @L@37Erőd @L@L@79Kert @L@85Kapuház @L@361Drágakőbánya @L@93Aranybánya @L@89Gabonafarm @L@3Magtár @L@3Magtár&különleges&rendelések @L@95Gránitbánya @L@L@13Súgómenü @L@91Hennafarm @L@56Lakóházak @L@359Vadászház @L@L@46Ipar @L@59Öntözés @L@L@99Ékszerész @L@L@7Billentyűzet&vezérlés @L@35Birodalmi&értékelés @L@57Birodalmi&út @L@L@473Lámpakészítő @L@90Salátafarm @L@70Könyvtár @L@95Mészkőbánya @L@L@494Nagy&járványok @L@78Palota @L@371Masztaba @L@368Mauzóleum @L@34Üzenetek @L@48Pénz @L@15Pénzkijelzés @L@370Emlékmű&építés @L@35Emlékmű&értékelés @L@66Halotti&templom @L@L@372Obeliszk @L@12Beállítások&menü @L@18Fedvények @L@24Kereskedelmi&felügyelő @L@28Szórakoztatási&felügyelő @L@25Magtárak&felügyelője @L@27Oktatási&felügyelő @L@21Katonai&felügyelő @L@373Emlékművek&felügyelője @L@26Közegészségügyi&felügyelő @L@29Templomok&felügyelője @L@30Kincstári&felügyelő @L@20Munkások&felügyelője @L@14Felügyelők&menüje @L@L@470Festékkészítő @L@77Palota @L@97Papiruszkészítő @L@73Pavilon @L@489Pharoszi&világítótorony @L@64Orvos @L@95Sima&kőbánya @L@79Tér @L@86Rendőrőrs @L@22Politikai&felügyelő @L@90Gránátalma-farm @L@16Népességkijelzés @L@39Népességnövekedés @L@1Fazekas @L@35Jólét&értékelés @L@L@95Kőbánya @L@L@35Értékelések @L@23Értékelési&felügyelő @L@88Toborzó @L@94Nádgyűjtő @L@51Vallás @L@358Útzár @L@57Utak @L@478Királyi&temetkezési&sírkamrák @L@L@95Homokkőbánya @L@68Írnokképző&iskola @L@41Írnokok @L@74Szenet&ház @L@82Hajóács @L@67Szentély @L@362Szfinx @L@79Szobor @L@375Lépcsős&piramisa @L@363Kőfaragók&céhe @L@4Raktárudvar @L@4Raktárudvar&különleges&rendelések @L@69Naptemplom @L@L@80Adószedő&iroda @L@67Templom @L@350Ozirisz&templomegyüttes @L@351Ré&templomegyüttes @L@352Ptah&templomegyüttes @L@353Szet&templomegyüttes @L@354Bast&templomegyüttes @L@477Sírrabló @L@85Torony @L@47Kereskedelem @L@75Képzőközpont @L@367Szállítóhajó @L@357Szállítókikötő @L@75Képzőközpontok (szórakoztatók) @L@48Adó @L@38Valódi&piramisa @L@L@42Járőrök @L@85Fal @L@52Háború @L@365Hadihajó @L@356Hadihajó-kikötő @L@61Vízellátás @L@98Fegyverkovács @L@60Takács @L@62Kút @L@94Favágó @L@8Munkatábor @L@40Munkások @L@32Világtérkép @L@L@479Állatkert @L@L	Történelem @L@L@493Abu&Simbel @L@481Alexandriai&könyvtár @L@159Patika @L@472Kézművesek @L@L@380Bast,&Ízisz&és&Hathor @L@199Bazár @L@194Sör @L@386Téglakészítők @L@390Téglák @L@395Temetési&kellékek @L@L@482Caesareum @L@389Asztalosok @L@186Marhatenyésztés&és&halászat @L@166Gyermekek @L@190Agyag @L@L@171Tánc @L@182Védelmi&építmények @L@158Fogászat @L@L@161Balzsamozás @L@L@181Ellenségek @L@165Szórakozás @L@L@150Mezőgazdaság @L@393Fesztiválok @L@189Len @L@187Gyümölcsök&és&zöldségek @L@L@176Kertek&és&közterületi&művészet @L@191Arany&és&aranybányászat @L@174Kormányzat&és&bürokrácia @L@185Gabona&és&árpa @L@5Magtár @L@L@469Henna @L@152Lakóházak @L@383Vadászat @L@L@388Bevándorlás @L@151Ipar @L@154Öntözés @L@L@382Ékszerek @L@169Zsonglőrködés @L@L@155Munkaerő @L@474Lámpák @L@183Törvények @L@164Könyvtár&és&irodalom @L@398Vászon&és&szövés @L@197Luxuscikkek @L@L@495Nagy&járványok @L@381Malária @L@394Masztaba @L@160Orvoslás @L@184Katonaság @L@170Zene @L@L@157Nílus @L@L@397Obeliszk @L@476Olaj @L@376Ozirisz,&Szobek&és&Min @L@396Egyéb&emlékművek @L@L@195Papiruszkészítés @L@175A&fáraó&otthona @L@487Pharoszi&világítótorony @L@167Népesség @L@198Fazekasság @L@384Papok @L@378Ptah,&Amon&és&Thot @L@176Köztéri&művészet @L@392Piramisok @L@L@193Kőbányák @L@L@377Ré,&Maat&és&Hórusz @L@188Nádak @L@399Vallás @L@153Utak @L@L@163Iskola&és&oktatás @L@387Írnokok @L@379Szet,&Anubisz&és&Szekhmet @L@172Szenet @L@179Hajók&és&hajóépítés @L@162Szentély&és&templom @L@168Társadalom @L@391Szfinx @L@385Kőfaragók @L@6Raktárudvar @L@L@173Adózás&és&pénz @L@177Kereskedelem @L@L@475Királyok&völgye @L@L@196Fegyverek @L@156Kút&és&vízellátás @L@192Fa&és&felhasználása @L@L@480Állatkert"
        }
    }

    message_file_menu {
        id: 11

        size [30, 28]
        title { text: "Fájl menü" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A Fájl menüben új játékot indíthatsz, újrajátszhatod a jelenlegi küldetést, betölthetsz egy korábban mentett játékot, elmentheted az aktuális játékot, törölhetsz egy korábbi mentést, illetve kiléphetsz a Pharaohból."
        }
    }

    message_optons_menu {
        id: 12

        size [30, 28]
        title { text: "Beállítások menü" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A Beállítások menüben módosíthatod a Pharaoh megjelenését és hangjait. A Megjelenítés beállítással a nézetet, a Hang beállítással pedig a hanghatások, a beszéd és a zene hangerejét állíthatod. A Sebesség beállítás szabályozza, milyen gyorsan telik az idő a Pharaohban. A Városok beállításnál kiválaszthatod, hogy a városnevek klasszikus vagy egyiptomi változatát szeretnéd használni. A klasszikus nevek valószínűleg ismerősebbek, de az egyiptomi elnevezések hitelesebb hangulatot kölcsönöznek a játéknak. @PA játék közben érkező üzenetek kezelését az Előugró üzenetek beállításainál szabályozhatod. A legtöbb üzenet felugró ablakban jelenik meg, ilyenkor a játék megáll, amíg be nem zárod az ablakot. Az Előugró üzenetek beállításaival kikapcsolhatod ezt a funkciót bizonyos üzenettípusoknál. A kategórialistából egyszerűen kattints arra a kategóriára, amelynek üzeneteit nem szeretnéd felugró ablakban látni. A kategória neve sárgára vált, az ilyen üzenetek pedig a képernyő tetején megjelenő sávban jelennek meg. Emellett a @34üzenetlistában& is megtalálod őket. Így nem kell megszakítanod a város irányítását az üzenetek miatt. Ha a listában a „Szállítás teljesíthető” lehetőséget választod, a kért árukat a raktárak automatikusan elküldik, amint a szállítmány készen áll. A kérésekkel kapcsolatos további tudnivalókért lásd a @22Politikai felügyelő& leírását. @PEbben a menüben a játék automatikus mentése is be- vagy kikapcsolható. Az automatikus mentés félévente elmenti a játékot, így mindig van egy biztonsági mentésed, ha elfelejtenél kézzel menteni vagy számítógépes hiba lépne fel. Mindig ugyanazt a mentést írja felül, ezért nem fogja teleszemetelni a merevlemezt automatikus mentésekkel. Kikapcsolhatod ezt a funkciót, ha el szeretnéd kerülni a mentések alatti rövid szüneteket. @PA Nehézség beállítással a játék során bármikor módosíthatod a nehézségi szintet. Vedd azonban figyelembe, hogy a küldetés pontszáma a választott nehézségtől függ. Ha a küldetés közben változtatsz rajta, a pontszámot a játszott legkönnyebb nehézségi szint alapján számolja a játék. @PVégül az Emlékmű-gyorsítás lehetővé teszi, hogy az istenek segítségével gyorsabban építs bizonyos @370emlékműveket. Ha bekapcsolod ezt a lehetőséget, egy isten megáldhat azzal, hogy segít az építkezésben. Az istenek azonban csak bizonyos emlékműveken szeretnek dolgozni, mégpedig a piramisokon és a masztabákon."
        }
    }

    message_help_menu {
        id: 13

        size [30, 28]
        title { text: "Súgó menü" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A Súgó menü felsorolja mindazokat a témákat, amelyeket ismerned kell a Pharaoh játékához. A Tartalomjegyzék alsó részéből számos történelmi ismertetőt is kiválaszthatsz. @PAz „Egérsúgó” azoknak a kis buborékoknak a megjelenítését szabályozza, amelyek akkor jelennek meg, amikor a kurzort valamire viszed. A „Teljes” beállítás szinte mindenhez megjeleníti az egérsúgót. A „Részleges” kikapcsolja azt, néhány kivétellel, például a @18fedvényeknél& és a palota jelentéseinél. A „Nincs” teljesen letiltja az egérsúgót. @PA „Figyelmeztetések” a képernyő tetején megjelenő rövid üzenetsávok. Ha már belejöttél a Pharaohba, érdemes lehet kikapcsolni őket."
        }
    }

    message_overseers {
        id: 14,

        size [30, 28]
        title { text: "Felügyelők" }
        subtitle {
            text: "Játékvezérlés"
        }
        content {
            text: "A Felügyelők menüben vagy a Felügyelők gombra kattintva megnyithatod bármelyik felügyelőt. A menü különösen hasznos, ha elrejtetted a vezérlőpanelt. A felügyelők mindig naprakész, létfontosságú információkat nyújtanak városod állapotáról."
        }
    }

    message_game_control_money_display_window {
        id: 15,

        size [30, 28]
        title {
            text: "Pénzkijelző",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "Itt látható a város kincstárában lévő debenek száma. A sárga színnel megjelenő érték adósságot jelez. A bevételekről további információt a @48pénz& bejegyzésben találsz."
        }
    }

    message_game_control_population_display {
        id: 16,

        size [30, 28]
        title {
            text: "Népességkijelző",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "Ez az ablak mutatja, hány ember él a városban. Ne feledd, hogy nem minden lakos számít munkásnak. A @39népesség& bejegyzésből megtudhatod, hogyan működik a népesség a játékban."
        }
    }

    message_game_control_date_display {
        id: 17,

        size [30, 28]
        title {
            text: "Dátumkijelző",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "Ez az ablak az aktuális hónapot és évet mutatja. A könnyebb tájékozódás érdekében a modern naptárat használja. Ha úgy érzed, hogy az idő túl gyorsan vagy túl lassan telik, állítsd a sebességet a @12Beállítások menü& megfelelő pontjában."
        }
    }

    message_overlay_selector {
        id: 18,

        size [30, 28]
        title {
            text: "Fedvényválasztó",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A Fedvényválasztó segítségével különböző szűrőkön keresztül tekintheted meg a várost. A fedvények nélkülözhetetlenek a várostervezéshez és a városi szolgáltatások irányításához. @PHa kiválasztasz egy fedvényt, csak az adott jelentéshez kapcsolódó épületek és járókelők jelennek meg. A többi épületet rendszerint oszlopok helyettesítik. Ezek többnyire azt mutatják, hogy az adott épület mennyire fér hozzá egy szolgáltatáshoz vagy városi funkcióhoz. Minél magasabb az oszlop, annál jobb az ellátottság. @PKivételt képeznek a Kockázat fedvények, a Problémák fedvény, a Vonzóság fedvény és a Sziklák elrejtése fedvény. A Kockázat fedvényeken az épületeket ugyanúgy oszlopok helyettesítik, de minél magasabb és vörösebb egy oszlop, annál nagyobb a veszély. @PA Problémák fedvény megmutatja azokat az épületeket, amelyek nem működnek megfelelően, vagy hamarosan súlyos problémával szembesülnek. A hibát jelző ikon az épület fölött jelenik meg. Ez a fedvény azokat a taligásokat is mutatja, akik azért akadtak el, mert nincs hová szállítaniuk az árut vagy az élelmet. @PA Vonzóság fedvénynél a terepet különböző színű mezők jelzik. Az aranyszínű mezők a legvonzóbb területeket mutatják, míg a barnább árnyalatok kevésbé kívánatos helyeket jelölnek. A vonzóságról további információt @56itt& találsz. @PHa a sziklák eltakarják a kilátást, a Sziklák elrejtése fedvénnyel ideiglenesen eltüntetheted őket. Ha királyi sziklasírokat építettél a sziklákba, ezzel a fedvénnyel azok belsejébe is beláthatsz. @PA Víz fedvény némileg eltér a többitől. A vízhordók elérhetőségét kék oszlopok jelzik, amelyek a jobb ellátottsággal egyre magasabbak. Ez a fedvény azt is megmutatja, mely területek alkalmasak vízzel kapcsolatos építmények számára, illetve hol érhető el ivóvíz kútból. A sötétkék négyzetek a kúttal ellátott házakat jelölik, a világoskékek pedig azokat a területeket, ahol elegendő talajvíz van egy @62Kút, @61Vízhálózat& vagy más, talajvizet igénylő épület számára. @PA különböző fedvények megismerésének legjobb módja, ha kipróbálod őket. Ha megérted, milyen információkat nyújtanak, sokkal hatékonyabban tudod majd megtervezni a városodat."
        }
    }

    message_control_panel_toggle {
        id: 19,

        size [30, 28]
        title {
            text: "Vezérlőpanel kapcsoló",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "Ezzel a gombbal elrejtheted vagy megjelenítheted a vezérlőpanelt. Ha elrejted, többet látsz a városból, viszont néhány játékvezérlő használata kevésbé lesz kényelmes. Hogy melyik megoldást választod, kizárólag a saját igényeidtől függ."
        }
    }

    message_overseer_workers {
        id: 20,

        size [30, 28]
        title {
            text: "Munkaügyi felügyelő",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A Munkaügyi felügyelő nyilvántartja a @43munkaerővel& kapcsolatos adatokat: az üres álláshelyeket ágazatonként, a munkanélküliek számát és az éves bérszintet tíz munkásra vetítve. Segítségével hatékonyan kezelheted a munkaerővel kapcsolatos kérdéseket. @PA Munkaügyi felügyelőnél állíthatod be a városi béreket. A felügyelő paneljén láthatod az általad fizetett bért, valamint az Egyiptomban szokásos bérszintet. A nyilakkal módosíthatod a munkások fizetését. Ha többet fizetsz, mint a többi egyiptomi város, javulhat a @39városi hangulat&, és nőhet a @39bevándorlás. Az alacsonyabb bérek pénzt takarítanak meg, de rontják a lakosság hangulatát, és kivándorláshoz vezethetnek. @PA Munkaügyi felügyelőnél a munkaerő prioritásait is beállíthatod. Ha nem adsz meg prioritást, a felügyelő saját belátása szerint osztja be a dolgozókat. Általában először az élelmiszer-termelést, majd az ipart tölti fel. Ha például a hadsereget szeretnéd első helyre tenni, kattints a katonai sorra. Megjelenik egy számozott panel. A katonai ágazat első helyre állításához kattints az 1-es számra. A katonai sor előtt lakat jelenik meg, jelezve, hogy a prioritás rögzítve van. Minden ágazathoz beállíthatsz prioritást. @PFigyelj arra, hogy amikor prioritást adsz egy ágazatnak, a Munkaügyi felügyelő először oda irányít minden rendelkezésre álló munkást. Emiatt más ágazatok munkaerő nélkül maradhatnak. Egyetlen város sem maradhat fenn sokáig, ha valamelyik ágazata teljesen dolgozók nélkül marad. Munkaerőhiány idején gyakran kell módosítanod a prioritásokat, hogy egyik ágazat se maradjon túl sokáig ellátatlanul. @L@LAz ókori egyiptomi munkaerőről rövid történeti áttekintést @155itt& olvashatsz."
        }
    }

    message_overseer_military {
        id: 21,

        size [30, 28]
        title {
            text: "A hadsereg felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A hadsereg felügyelője nyomon követi a város összes @37csapatának, @365hadihajójának és @367szállítóhajójának állapotát. @PA hadsereg felügyelője hadijelentést és flottajelentést is készít. A hadijelentésben röviden tájékoztat az egyes csapatok létszámáról és állapotáról. Figyeli a moráljukat és tapasztalati szintjüket, kijelölhet egy csapatot a Királyság szolgálatára, és ha csak egy másik város kér segítséget, elküldheti azt. Egy csapat megtekintéséhez kattints a „Csapat megtekintése” gombra. A hadsereg állapotjelentéséből egy csapatot vissza is rendelhetsz az erődjébe. @PA jobb alsó sarokban lévő gombra kattintva megtekintheted a flotta állapotjelentését, amely minden szükséges információt tartalmaz a hadihajókról és szállítóhajókról. A felügyelő jelentést ad minden hadihajó legénységének fáradtsági szintjéről és a hajótest állapotáról. Szükség esetén hadihajókat is küldhet a fáraó vagy egy másik város megsegítésére. Kattints a „Hadihajó megtekintése” gombra egy adott legénység felkereséséhez, vagy a „Vissza a kikötőbe” gombra, hogy a hajót visszaküldd kikötni. @PA hadsereg felügyelője a városban és környékén zajló általános katonai tevékenységről is tájékoztat. Megmondja, ha ellenség közeledik, vagy ha valakinek szüksége van csapataid vagy hadihajóid segítségére. @PTovábbi információkért a fáraói háborúkról kattints @52ide. @L@LAz ókori egyiptomiak hatalmas hadseregeket és flottákat hoztak létre. Kattints @184ide, ha többet szeretnél megtudni az ókori hadviselésről."
        }
    }

    message_overseer_political {
        id: 22,

        size [30, 28]
        title {
            text: "Politikai felügyelő",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A politikai felügyelő kezeli kapcsolataidat Egyiptom többi részével. @PA politikai felügyelő nyomon követi az összes nyersanyagkérést, akár más városoktól, akár a fáraótól érkeznek. Tudja, mennyi van a kért áruból a város @4Raktáraiban&udvaraiban, és értesít, amikor teljesíteni tudod a kérést. Ezután utasíthatod, hogy küldje el az árut. Általában érdemes a fáraó vagy más városok kéréseit a lehető leggyorsabban teljesíteni. Egy kérés teljes figyelmen kívül hagyása csökkentheti a @47kereskedelmet, vagy akár támadást is kiválthat a városod ellen. A késve elküldött áru is jobb, mint ha egyáltalán nem küldenél semmit. @PA politikai felügyelő a családi megtakarításaid kezelésében is segít. Tudja, mennyit takarítottál meg, és mi a jelenlegi fizetési szinted. A családi megtakarítások küldetésről küldetésre megmaradnak, kivéve ha Egyiptom központi kormányzata összeomlik (az egyes korszakok között). A politikai felügyelő parancsodra megváltoztatja a fizetésedet. Egyszerűen kattints az aktuális fizetésedet jelző gombra, majd amikor megjelenik a rangokhoz tartozó fizetések listája, válassz új fizetési szintet ezen a képernyőn. Ne feledd, hogy az egyiptomiak rosszallják, ha valaki rangjához képest túl magas fizetést állapít meg magának. @PHa családi megtakarításaid egy részét el szeretnéd költeni, a politikai felügyelő intézi a tranzakciót. Választhatsz, hogy Egyiptomnak küldesz ajándékot (más politikai vezetőknek vagy más városok lakóinak), vagy a városod kincstárának adományozol. @PEgyiptomnak küldött ajándék növelheti a @35Királysági&Megítélésedet. Ha családodnak elegendő megtakarítása van, háromféle ajándék közül választhatsz. Ne légy azonban túl nagylelkű. Ha túl gyakran küldesz ajándékokat, a címzettek elvárják őket, és haragudhatnak, ha azok elmaradnak. Emellett hajlamosak minden új ajándékot értékesebbnek várni az előzőnél. Amikor ajándékot küldesz, a politikai felügyelő gondoskodik róla, hogy sértetlenül megérkezzen. @PA családi megtakarításaidat a város kincstárának is adományozhatod. Ez jó döntés lehet, különösen ha a megtakarításaid megakadályozhatják, hogy a város adósságba kerüljön. Az adósság igen költséges lehetőség. A Királyság kölcsönt ad a városodnak, de ennek ára van. A város pénzügyeiről további információért kattints @48ide. @PVégül a politikai felügyelő ismeri a Királysági megítélésedet és Egyiptom általános hozzáállását hozzád. A megítélésekkel kapcsolatos részletesebb információkért a @23Megítélés&felügyelődhöz fordulj."
        }
    }

    message_overseer_ratings {
        id: 23,

        size [30, 28]
        title {
            text: "Megítélési felügyelő",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A Megítélési felügyelő megjeleníti a város jelenlegi Kultúra-, Jólét-, Emlékmű- és Királysági megítélését, valamint a lakossági célt. Ha egy megítélésre kattintasz, a felügyelő elmondja, hogyan javíthatod azt a legjobban, vagy mi akadályozza a növekedését. A megítélések feletti oszlopok segítségével láthatod, milyen közel jár a város a célok eléréséhez. Amikor eléred a megbízatásod kezdetén kitűzött városi célt, az oszlop megtelik. Még ha el is érted az emlékmű-megítélést, az oszlop nem telik meg (és a cél nincs teljesítve), amíg az Emlékművek felügyelője el nem küldte az összes szükséges temetkezési kelléket. @PHa a városnak van @77Palotája, gyorsan ellenőrizheted a megítéléseket, ha az egeret a palota fölé viszed. Egy kis ablak jelenik meg, amely felsorolja a megítéléseket és a város munkanélküliségi arányát. @PA megítélésekről és a játékban betöltött szerepükről további részletes információért kattints @35ide."
        }
    }

    message_overseer_commerce {
        id: 24,

        size [30, 28]
        title {
            text: "A kereskedelem felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A kereskedelem felügyelője figyeli a város @46iparágait és @4Raktárait&udvarait, valamint nyomon követi a világban elérhető áruk kínálatát, keresletét és árait. Tudja, mennyi van az egyes árucikkekből a városban, és megmondja, hogy egy adott áru importálható vagy exportálható-e. @PA kereskedelem felügyelője az egyes iparágak aktuális állapotáról is tájékoztat. Látogasd meg, ha be vagy ki szeretnéd kapcsolni a város iparágait, vagy ha egy bizonyos árut fel szeretnél halmozni a város Raktáraiban. A felhalmozott áru gyorsan gyűlik a Raktárakban, mivel senki sem használhatja fel. Nem lehet kereskedni vele, és a bazárvásárlók sem szerezhetik be vevőik számára. Ha egy nyersanyagot halmozol fel, a hozzá tartozó gyártóüzemekhez nem érkezik szállítmány az adott áruból. Érdemes lehet egy árut felhalmozni egy várható jövőbeli kérésre készülve, vagy egy nyersanyagot még azelőtt összegyűjteni, hogy megépítenéd az azt igénylő iparágakat. @PEgy iparág leállításához vagy egy áru felhalmozásához kattints a kereskedelem felügyelőjének listájában egy elemre. A megjelenő panelen gombok jelennek meg a különböző lehetőségekkel. @PA kereskedelem felügyelője a kereskedelmi folyamatok kialakításában is segít. Megmutatja, mely áruk importálhatók vagy exportálhatók a megnyitott kereskedelmi útvonalak alapján. Ha kereskedni szeretnél egy áruval, keresd fel, majd kattintással jelöld ki a kívánt árucikkeket. Megadhatod, mennyi maradjon belőlük a város Raktáraiban, vagy rábízhatod a döntést, és hagyhatod, hogy belátása szerint importáljon és exportáljon élelmiszert és árukat. A felügyelő régóta végzi a munkáját, és okos döntéseket hoz arról, mennyit kell tartania a városnak az egyes árucikkekből. @PImportáláskor a felügyelő addig vásárol egy árut, amíg a városban nincs meg a kiválasztott mennyiség (vagy saját belátása szerint csak annyit próbál vásárolni, hogy kis többlet maradjon a városi raktárban). Exportáláskor akkor ad el árut, amikor a város készlete meghaladja a beállított szintet. Ha saját belátására hagyod, felméri, hogy a városnak szüksége van-e az adott árura, és nem ad el többet annál a mennyiségnél, amely szerinte szükséges a zavartalan működéshez. A felügyelő figyelemmel kíséri a lakosság változó méretét, és a város létszámának ingadozásával módosítja döntéseit. @A @46ipar, @45élelem és @47kereskedelem bejegyzések segítenek megérteni a sikeres kereskedelem finomságait."
        }
    }

    message_overseer_granaries {
        id: 25,

        size [30, 28]
        title {
            text: "A magtárak felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "Az élelem és a lakosság szorosan összefügg. A magtárak felügyelője nyomon követi a város lakosságát és az általuk elfogyasztott élelmet. @PA magtárak felügyelője három különböző grafikonnal mutatja be a város lakosságára vonatkozó adatokat. Alapértelmezés szerint először a Lakosságtörténet grafikont látod. Ez azt mutatja, hogyan nőtt vagy csökkent a lakosságod az idő múlásával. Ha a város jól működik, a jelentés többé-kevésbé folyamatos növekedést mutat. @PA Lakosságtörténet grafikontól jobbra két kisebb grafikon található: a Népszámlálás és a Társadalom grafikon. Kattints az egyikre a nagyításhoz és a képernyő közepére helyezéshez. @PA Népszámlálás grafikon a lakosság kor szerinti megoszlását mutatja – hasznos a @43munka&erő növekedésének vagy csökkenésének előrejelzéséhez. A gyermekek és az idősek nem dolgoznak, de továbbra is fogyasztanak élelmet, sört és törnek edényeket! @AA Társadalom grafikon a polgárok jövedelem szerinti megoszlását mutatja, amelyet a lakóhelyük minősége alapján mér. A nagyon gazdag lakosok @41(írástudók) szintén nem végeznek fizikai munkát, ezért ahogy a város gazdagodik, a munkaerő általában csökken. Bár nem járulnak hozzá a munkaerőhöz, az írástudók sok adót fizetnek a Palota kincstárába. @AA grafikonok alatt több hasznos információsor található. Az első sor megmutatja, hogy a jelenlegi élelmiszer-termelési szint hány embert képes ellátni, valamint a jelenlegi bevándorlási és elvándorlási arányok alapján várható lakossági változásokat. A felügyelő azt is tudja, hogy a város üres lakóhelyei hány embert tudnak befogadni, mennyi élelmet tárolnak a város magtárai, és hány bevándorló érkezett az előző hónapban. @A @39Lakosság és @45Élelem bejegyzések tanulmányozása segíthet megérteni a magtárak felügyelőjének fontosságát."
        }
    }

    message_overseer_public_health {
        id: 26,

        size [30, 28]
        title {
            text: "A közegészségügy felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A közegészségügy felügyelője jelentést készít a város általános egészségi állapotáról. Nyomon követi a városban működő @64orvosi&rendelők, @63fogorvosi&rendelők, @65patikák és @66halottasházak számát. A város egyes részeinek egészségügyi ellátásáról részletesebb információkat a @18egészségügyi&fedvény segítségével kaphatsz. @AA közegészségügy felügyelője tudja, ha egy adott egészségügyi veszély, például malária vagy járvány fenyegeti a várost. Figyeli azt is, hogy a lakosság általánosságban hogyan vélekedik az egészségügyi szolgáltatásokról. @A @53Egészség bejegyzés segít megérteni az egészségügy városodra gyakorolt hatásait."
        }
    }

    message_overseer_learning {
        id: 27,

        size [30, 28]
        title {
            text: "A tanulás felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A tanulás felügyelője tájékoztat a város oktatásának állapotáról. Jelenti az aktív @68írnoki&iskolák és @70könyvtárak számát, valamint azt, hogy hány ember részesülhet a meglévő oktatási intézmények szolgáltatásaiból. Felméri az oktatáshoz való hozzáférés megfelelőségét, és jelzi azt is, ha a polgárok új oktatási épületeket igényelnek. @AA város egyes területeinek ellátottságát a @18oktatási&fedvény segítségével tekintheted meg. További információkért lásd az @50oktatás bejegyzést. @L@LTöbbet tudhatsz meg az ókori Egyiptom oktatásáról, ha @163ide kattintasz."
        }
    }

    message_overseer_diversions {
        id: 28,

        size [30, 28]
        title { text: "A szórakoztatás felügyelője" }
        subtitle { text: "Játékvezérlés"  }
        content {
            text: "A szórakoztatás felügyelője tudja, hány zsonglőrszínpad, zenészszínpad és táncos színpad működik a városban. A színpadok száma sokkal fontosabb, mint az, hogy hány @71bódé, @72zenepavilon és @73csarnok található, ezért ezeket nem tartja számon külön. Jelenti azt is, hány @74Szenet&ház és @479állatkert szórakoztatja a közönséget. Megbecsüli, hány ember élvezheti a város színpadainak, állatkertjeinek és Szenet-házainak szolgáltatásait, valamint felméri a polgárok elégedettségét a szórakozási lehetőségeikkel kapcsolatban. @A @49szórakoztatás bejegyzés tanulmányozása segíthet jobban megérteni ennek szerepét a városodban. @L@LTöbbet tudhatsz meg az ókori Egyiptom szórakoztatásáról, ha @165ide kattintasz."
        }
    }

    message_overseer_temples {
        id: 29,

        size [30, 28]
        title {
            text: "A templomok felügyelője",
        }
        subtitle {
            text: "Játékvezérlés",
        }
        content {
            text: "A templomok felügyelője tudja, mely isteneket tisztelik a városban, és hogy van-e a városnak védőistene. Talán a legfontosabb, hogy az egyes istenek hozzáállását is nyomon követi. Jelenti, hány Szentély, Templom és Templomegyüttes működik a városban, valamint hogy az emberek igényelnek-e jobb hozzáférést a vallási létesítményekhez. A fesztiválok megtervezésében is segíthet. @PHa fesztivált szeretnél rendezni a városban, kattints az „Új fesztivál rendezése” gombra. Válaszd ki, melyik istent tiszteled meg, és a fesztivál méretét. A sikeres fesztivál megtervezéséhez szükséges költségek és idő miatt egy város legfeljebb két fesztivált rendezhet bármely 12 hónapos időszakban. Ne feledd, hogy a fesztivál megtartásához a városnak rendelkeznie kell egy @366Fesztivál&térrel is. Nagyszabású fesztivál rendezéséhez elegendő sörrel is rendelkezned kell mindenki számára. @PA templomok felügyelője a polgárok vallással kapcsolatos konkrét problémáiról is tájékoztat. @AO istenek kiengesztelésének fontosságáról többet tudhatsz meg a @51vallás bejegyzésből. @L@LA vallás az ókori egyiptomi élet alapja volt. További információért kattints @399ide."
        }
    }

    message_overseer_treasury {
        id: 30,

        size [30, 28]
        title { text: "A kincstár felügyelője" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A kincstár felügyelője nyomon követ minden deben-t, amely a város kincstárába beérkezik vagy onnan távozik. A kimutatását áttekintve felmérheted, hol csökkentheted a költségeket vagy növelheted a bevételeket. @PA kincstár felügyelőjének képernyőjének tetején összesített adózási információkat találsz. Az adókulcs melletti görgetőgombokkal módosíthatod az értékét. Az alapértelmezett 9 százalékos beállítást a polgárok elfogadhatónak tartják. Ha az adókulcsot jóval 9 százalék fölé emeled, az feldühítheti a lakosságot és visszavetheti a bevándorlást, sőt akár távozásra is késztetheti az embereket. Minél tovább tartod magas szinten az adókat, annál elégedetlenebbé válnak a polgárok. A városi hangulatról további információért kattints @39ide. @PAz összesítés azt is mutatja, mennyi adót szedtél be, hány polgár van adónyilvántartásba véve, és mennyi pénz maradt beszedetlenül az elégtelen számú adószedő miatt. Annak felméréséhez, hogy a város mely részei maradnak ki az adófizetésből, használd az @18adó&fedvényt. Arra is ügyelj, hogy a polgárok nagyon felháborodnak, ha nekik adót kell fizetniük, miközben a város más részei nem teszik ezt. @PAz összesítő információk után egy kimutatás következik. A lista felső sorai a város bevételeit részletezik: adókból, ajándékokból és áruexportból származó bevételeket. @AA csekély számú bevételi forrás alatt a város kiadásainak hosszabb listája található. Általában a bérek és az építési költségek jelentik a legnagyobb tételeket, bár az import is igen költségessé válhat. @AA lista bal oldala az előző év eredményeit mutatja összehasonlítás céljából. Láthatod, ha egy adott kiadás az előző évhez képest ellenőrizhetetlenül megugrik. @A @48pénz bejegyzés további tanácsokat ad a költségvetésről. Az @80Adószedők bejegyzés szintén hasznos lehet. @L@Az ókori Egyiptom pénzügyeiről további információért kattints @173ide."
        }
    }

    message_chief_overseer {
        id: 31,

        size [30, 28]
        title { text: "Főfelügyelő" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A főfelügyelő egyeztet az összes többi felügyelővel, hogy rövid áttekintést adjon a város állapotáról. Jó hozzá fordulni, ha nem vagy biztos benne, mire van leginkább szüksége a városodnak. A sürgős, azonnali figyelmet igénylő ügyek sárgával jelennek meg. A komoly problémák fehérrel láthatók. Kattints bármelyik problémára tanácsért, hogyan lehet megoldani, valamint olyan további tanácsadók hivatkozásaiért, akik segíthetnek. @AA főfelügyelő a legújabb nilométer-értéket is megadja. A nilométer a következő évszak áradásának mértékét jelzi előre. @AA többi felügyelő a főfelügyelőnek jelent, és érdemes alaposan megfontolnod, amit mond. A városod általános állapotát rajtad kívül senki sem ismeri jobban nála. Ha időben figyelembe veszed a figyelmeztetéseit, megóvhatod a várost a pusztulástól."
        }
    }

    message_world_map {
        id: 32,

        size [30, 28]
        title { text: "A világtérkép" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "A világtérkép megmutatja a világ többi fontos városát. Talán legfontosabb szerepe a @47kereskedelmi partnerek azonosítása. @PA zászlót viselő városok kereskednek veled. Kattints egy zászlós városra, hogy lásd, mely árukat szeretné kereskedni, valamint a kereskedelmi útvonal megnyitásának költségét. Minden áru mellett, amelyet a város vásárol vagy elad, egy-három kék pont jelzi a város kínálati vagy keresleti szintjét – egy pont azt jelenti, hogy az adott áruval alig foglalkoznak, míg három pont erős kereskedelmi igényt jelez. @AKattints a „Kereskedelmi útvonal megnyitása” gombra a kapcsolatok megkezdéséhez. A városod kincstára azonnal kifizeti az útvonal megnyitásának költségét, és a kereskedelem rögtön megkezdődhet. @AHa csapatokat vagy hadihajókat küldtél a Királyság szolgálatára, útjukat nyomon követheted a világtérképen. Az ellenséges seregek vagy flották mozgását is figyelemmel kísérheted, ahogy a városod felé közelednek. @A @47kereskedelem, @52háború és a @24Kereskedelem&felügyelője bejegyzések további információkat nyújtanak a világtérkép használatáról."
        }
    }

    message_building_buttons {
        id: 33,

        size [30, 28]
        title { text: "Építési gombok" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "Ezekkel a gombokkal helyezheted el az épületeket a tájon. Az épület ára a gombján látható. Amikor kiválasztasz egy építendő épületet, annak halványzöld képe az egérkurzorhoz tapad. Ha a kurzort építésre alkalmas terület fölé viszed, a kép zöld marad; nem megfelelő terepen a zöld kép vörös rombusszá változik. @PEgyes épületekhez kapcsolódó segítséget a meglévő épületekre jobb egérgombbal kattintva érhetsz el, vagy válaszd ki őket a @10Tartalomjegyzék „Épületek” részéből."
        }
    }

    message_game_control_messages {
        id: 34,

        size [30, 28]
        title { text: "Üzenetek" }
        subtitle { text: "Játékvezérlés" }
        content {
            text: "Amikor figyelemre méltó esemény történik a városban vagy a Királyság más részén, üzenetet kapsz, amely leírja az eseményt. Néhány üzenet sürgős, és gyors reagálást igényel. Ezek lehetnek a fáraó vagy más városok kérései, illetve felhívhatják a figyelmedet a városod egy problémás területére. @PAmikor új üzenet érkezik, a Vezérlőpult „Üzenet” gombja világítani kezd, és egy hangjelzés hallható. Kattints a gombra az üzenet elolvasásához. Ha az ügy rendkívül sürgős, az üzenetet közvetlenül megkapod, és automatikusan megjelenik a képernyőn. Ha az üzenet a városod valamely problémájára figyelmeztet, az üzeneten belüli riasztás gombra kattintva közvetlenül a problémás helyre ugorhatsz. @PEgyéb üzenetek olyan utasításokat tartalmaznak, amelyek segítenek sikeresebben irányítani a várost. Ezek az üzenetek hasznos útmutatók, amelyek fontos játékelemeket tanítanak meg, és rövid távú célokat állítanak. A különleges üzenetekben meghatározott rövid távú célok teljesítése lehetővé teszi a küldetés megnyerését és a következő lépés megtételét. Ezeket az üzeneteket a listában kék tekercs jelöli. @PEgyes üzeneteket törölhetsz úgy, hogy jobb egérgombbal kattintasz a címükre az üzenetlistában. A panel alján található gombbal egyszerre törölheted az összes korábban megnyitott üzenetet, de az olvasatlan vagy kék tekercses (oktató) üzeneteket nem törli. Ha egy üzenetet törölsz a listából, az végleg elveszik. Természetesen dönthetsz úgy is, hogy megtartod az üzenetet későbbi használatra. @ATapasztalt játékosok az @12Beállítások&menüben kikapcsolhatnak bizonyos felugró üzeneteket. Ha engedélyezed ezt a lehetőséget, az üzenetek a képernyő tetején jelennek meg, és bekerülnek az Üzenetek ablakba is."
        }
    }

    message_ratings {
        id: 35,
        
        size [30, 28]
        title { text: "Értékelések" }
        subtitle { text: "Játékmenet" }
        content {
            text: "Az értékelések azt mutatják, milyen jó a város, illetve milyen jól vezeted azt. A várost négy különböző értékelés alapján mérik: Kultúra, Jólét, Királyság és Műemlék. @L@LKultúra @LA Kultúra értékelés azt méri, hogy polgáraid mennyire férnek hozzá a @49szórakozáshoz, @50oktatáshoz, @53egészségügyi ellátáshoz és @51valláshoz. Nemcsak a rendelkezésre álló létesítmények számát veszi figyelembe, hanem a választék sokszínűségét is. Magas Kultúra értékeléshez gondoskodj arról, hogy a polgárok minél több lehetőség közül választhassanak. Ez azt jelenti, hogy könnyen elérhető legyen többféle szórakozási lehetőség, egészségügyi szolgáltatás (a Patikák kivételével – ezek nem befolyásolják a Kultúra értékelést) és vallási létesítmény. @PA gazdagabb polgárok számára a Könyvtárak és az Írnokképző Iskolák egyaránt nélkülözhetetlenek a Kultúra értékelés növeléséhez, de az elérhetőség önmagában nem elég. Az emberek jobban tanulnak csendes, nem zsúfolt intézményekben, ezért a Kultúra értékelés az oktatás minőségét is figyelembe veszi azzal, hogy méri, hányan használják az egyes iskolákat és könyvtárakat. Előfordulhat, hogy elegendő oktatási épületed van ahhoz, hogy a város minden háza hozzáférjen az oktatáshoz, mégis túlzsúfoltság alakul ki. @PA legmagasabb Kultúra értékeléshez próbálj meg építeni egy @479Állatkertet. Erre szükséged lesz, ha 75 fölötti Kultúra értékelést kell elérned. Kattints a Szórakozás gombra, hogy megnézd, az Állatkert elérhető-e a szórakozási lehetőségek között. @L@LJólét @LA Jólét értékelés a város gazdagságát és pénzügyi biztonságát méri. Nem csupán a város kincstárát veszi figyelembe, hanem a polgárok vagyonát is, beleszámítva ingatlanaik értékét és a munkanélküliség mértékét. @PHa a város minden évben nyereséget termel, a Jólét értékelésnek folyamatosan emelkednie kell, feltéve hogy más tényező nem akadályozza ezt. A magas munkanélküliség, az alacsony szintű lakóházak és az alacsony bérek visszafogják a Jólét értékelés növekedését. A Királyságnak fizetendő adó elmulasztása szintén csökkenti ezt az értékelést. Ha működik a városban Templomkomplexum vagy Senetház, a Jólét értékelés nő, mert az emberek gazdagnak tartják azt a várost, amely ilyen pompás épületekkel rendelkezik. Egy műemlék befejezése szintén növeli a Jólét értékelést. Ha a város az évet adóssággal zárja vagy veszteséget termel, a Jólét értékelés romlik. Ha azonban a veszteséget az építkezések költségei okozták, az nem befolyásolja a Jólét értékelést, mert az építkezések a város fejlődését szolgálják. @L@LKirályság @LA Királyság értékelés a hírnevedet jelképezi, különösen Egyiptom többi része szemében. Ha gyorsan reagálsz egy szövetséges segítségkérésére, az növelheti ezt az értékelést. A kérések figyelmen kívül hagyása vagy az @48éves&adó befizetésének elmulasztása a város adóssága miatt rontja a Királyság értékelést. Ha ez túl alacsonyra csökken, rossz hírneved miatt a fáraó vagy egy szomszédos város is támadást indíthat ellened. @PA legtöbb küldetést 50-es értékeléssel kezded, ami semleges megítélést jelent. A városon kívül alig ismernek, és akik hallottak rólad, azoknak sincs még határozott véleményük. Idővel azonban, ha semmit sem teszel hírneved javításáért, a Királyság értékelés fokozatosan csökken, mert elterjed, hogy a városodon kívül nincs jelentőséged. Sokkal gyorsabban romlik, ha elveszíted vagy figyelmen kívül hagyod a távoli csatákat, nem teljesíted a Királyság áru- vagy egyéb kéréseit, hosszabb ideig @48adósságban maradsz, vagy a rangodhoz tartozó fizetésnél magasabb személyes fizetést veszel fel. @PA Királyság értékelés akkor is csökken, ha @477sírrablók kifosztják egy sír @374temetkezési&kellékeit, amíg te vagy a vezető. Egyiptom népe úgy fogja gondolni, hogy nem tiszteled kellőképpen a halottakat. @PA Királyság értékelésed növeléséhez teljesítsd gyorsan a fáraó vagy más egyiptomi városok kéréseit, különösen amikor katonai segítséget kérnek. A csatákban aratott győzelmek nagyban javítják hírnevedet. Néha még egy elvesztett csata is javíthat rajta valamelyest, hiszen legalább megpróbáltad megmenteni honfitársaidat a bajban. @PHa gyorsan szeretnél javítani hírneveden, családi megtakarításaidból vásárolj ajándékot Egyiptom számára. Politikai Felügyelőd eljuttatja az ajándékot a fáraónak, más egyiptomi vezetőknek vagy Egyiptom népének – oda, ahol szerinte a legtöbbet használ. A Királyság értékelésed azonnal néhány ponttal emelkedik. Ne költsd azonban minden megtakarításodat ajándékokra. Ha túl gyakran küldesz ilyeneket, elvesztik hatásukat, és a címzettek el is várják majd őket. Ha később abbahagyod az ajándékozást, vagy olcsóbb ajándékot küldesz annál, amihez hozzászoktak, az értékelésed akár romolhat is. Évente egynél több ajándék küldése általában már kevéssé hatékony, sőt akár vissza is üthet. @PA sírrablók elfogását Egyiptom népe szintén nagyra értékeli, ezért minden elfogott sírrabló kis mértékben növeli a Királyság értékelést. @PA Királyság értékelésed természetes csökkenése valamelyest lassul, ha a rangodhoz meghatározottnál alacsonyabb személyes fizetést veszel fel. Ha egyáltalán nem veszel fel fizetést, az még tovább javítja önzetlen közszolgaként szerzett hírnevedet – bár családod vagyonának gyarapítására ez nem éppen a legjobb módszer! @L@LMűemlék @LA Műemlék értékelés a város műemlékeinek méretétől, jelentőségétől és építésük előrehaladásától függ. Ha minden előírt műemléket befejezel, és gondoskodsz a szükséges temetkezési kellékek sírba juttatásáról a túlvilági ellátáshoz, könnyedén teljesítheted a Műemlék értékelés célját. @L@LA @23Értékelési&Felügyelő megmutatja aktuális értékeléseidet. Ha valamelyik értékelésre kattintasz, tanácsot ad, hogyan javíthatod azt."
        }
    }

    message_city_crime {
        id: 36

        size [30, 28]
        title { text: "Bűnözés" }
        subtitle { text: "Játékmenet" }
        content {
            text: "A bűnözés oka a rossz @39városi&hangulat. Az emberek sokféle okból lehetnek elégedetlenek – kevés élelem, alacsony bérek, magas adók vagy nagy munkanélküliség –, de csak akkor tör ki bűnözés, ha a hangulat különösen rossz. @PA bűnözés megelőzésének legjobb módja tehát a lakosság elégedettségének fenntartása. Ha bőségesen biztosítasz árukat és szolgáltatásokat, az sokat segít. Emellett @76Bíróságok és @86Rendőrőrsök építésével is visszaszoríthatod a bűnözést. Mindkét épület jelenléte elriasztja a lehetséges bűnözőket. @PMinden erőfeszítésed ellenére a város egyes részein így is megjelenhetnek bűnözők, különösen az erősen iparosodott negyedekben. Ha mégis kitör a bűnözés, egy Rendőrőrs rendőre elfogja az általa utolért bűnözőket. @PHa egy bűnöző elkerüli a rendőr figyelmét, egyenesen a város pénzt tároló épületei felé veszi az irányt. Nem tesz különbséget a város kincstára és családod megtakarításai között: bármelyikből lop. Miután aranyat szerzett, egy időre meghúzza magát, és... egy darabig nem lop újra. @PA bűnözésből @477sírrablók is születhetnek, de csak akkor, ha városod egy nagy egyiptomi személyiség végső nyughelye, és van benne síremlék (piramis, masztaba, mauzóleum vagy királyi sír). A sírrablók különösen ügyesen törnek be a királyi sírokba, hogy kifosszák azok kincseit. @PNéha a kapzsiság még a legelégedettebb polgárokat is megrontja. Ezek a kapzsi emberek összegyűlnek barátaikkal, és a nemes halottak mellé temetett gazdag temetkezési kellékekről ábrándoznak. Amikor a meggazdagodás vágya úrrá lesz rajtuk, bűnhullám tör ki, és ezek a polgárok sírrablókká válnak! Mivel nem láthatsz polgáraid szívébe, nem tudhatod előre, mikor kezdődik ilyen bűnhullám. A rendőrök azonban készséggel lecsapnak mindenkire, aki a sírok temetkezési kellékeinek ellopásával próbálja meggyalázni a halottakat."
        }
    }

    message_fort_and_company {
        id: 37,

        size [30, 28]
        title {
            text: "Erőd és század",
        }
        content {
            text: "Városod haderejét egy „zászlóalj” alkotja. A zászlóalj minden katonája egy századhoz tartozik, és minden századnak saját Erődje van. Egy város legfeljebb hat Erődöt építhet. A századok és Erődök típusai a következők: @L@LGyalogság @LA gyalogosok alkotják a legtöbb hadsereg gerincét. Közelharcra specializálódtak, ezért a csaták első vonalában harcolnak. Átlagos sebességgel mozognak. A @88Toborzótól lándzsával felfegyverkezve indulnak útnak. Gyalogsági Erődöt csak akkor építhetsz, ha városodban működik Fegyverkovács, vagy tudsz fegyvereket importálni. @L@LÍjászok @LAz íjászok nyilaikkal nagyobb távolságból támadhatják az ellenséget, mint a gyalogosok, de közelharcban gyengék, és nem maradnak sokáig életben, ha az ellenség közvetlenül rájuk támad. Kissé lassabban vonulnak, mint a gyalogosok. Saját maguk készítik íjaikat és nyilaikat, ezért Íjász Erődöt akkor is építhetsz, ha nincs Fegyverkovács a városban. @L@LHarci kocsisok @LA katonák számára kevés rémisztőbb látvány van, mint egy feléjük vágtató harci kocsisor. A harci kocsik kulcsszerepet játszanak az ellenség védelmi alakzatainak áttörésében, és ha a soraik felbomlanak, sokkal könnyebb legyőzni őket. Minden harci kocsis kap egy harci kocsit, amikor elhagyja a Toborzót, feltéve hogy városodban működik Harci Kocsikészítő és rendelkezésre áll elegendő fa. @LMinden katonatípus szívesebben tartózkodik saját Erődjében, amikor nem harcol, és ott is marad, amíg parancsot nem kap a kivonulásra. A túl hosszú ideig tartó tábori szolgálat rontja a század morálját. @PAz Erődöknek nincs szükségük útkapcsolatra vagy munkaerőre. Rendkívül kedvezőtlenül hatnak a vonzerőre, ezért célszerű a város szélére építeni őket. Az Erődök helyének kijelölésekor ne feledd, hogy az ártér és a szárazföld közötti partfal csak ott járható, ahol út köti össze a két területet. @PA katonák lehetőségeiről a @87Század&parancsai bejegyzésben olvashatsz. A @52háború bejegyzés is hasznos lehet. @L@LAz ókori egyiptomi hadviselésről bővebben kattints @184ide."
        }
    }

    message_true_pyramid {
        id: 38,

        size [30, 28]
        title {
            text: "Valódi piramis",
        }
        content {
            text: "A valódi piramis @95közönséges&kő maggal és simára csiszolt @95mészkő burkolattal készül. A @363Kőműves&Céh kőművesei rakják le a köveket és csiszolják a burkolatot, míg a @363Ács&Céh ácsai elkészítik az építéshez szükséges rámpákat, ahogy a piramis egyre magasabbra emelkedik. Amikor egy @4Raktárudvarban összegyűlik négy kőtömb, a parasztok szánon a piramis építési területére húzzák azokat, ahol a kőművesek már várják a szállítmányt. @PA valódi piramisok méretei: kicsi, közepes, nagy, Piramiskomplexum és Nagy Piramiskomplexum. @PTovábbi információért lásd a @370Műemlék&építése, a @373Műemlékek&Felügyelője és a @369Építésvezető bejegyzéseket. @L@LA piramisok az ókori Egyiptom jelképei, és ezek tették az országot világszerte ismertté. Kattints @392ide, ha többet szeretnél megtudni a piramisokról és építésükről."
        }
    }

    message_population_groth_and_sentiment {
        id: 39,

            size [30, 28]
        title {
            text: "Népességnövekedés és városi hangulat",
            pos [15, 5]
        }
        subtitle {
            text: "Játékmenet",
        }
        content {
            text: "Amikor városod még új, a bevándorlók kevés holmijukkal lelkesen érkeznek, új lehetőségekben reménykedve. Ahogy a város fejlődik, egyre több szolgáltatást kell biztosítania ahhoz, hogy új bevándorlókat vonzzon és megtartsa jelenlegi lakóit. A kivándorlás megelőzésének legjobb módja, ha a lakosság elégedett, vagyis magas a Városi hangulat. @PA jó hangulat kulcsa az alapvető szükségletek biztosítása: tiszta ivóvíz, elegendő élelem és munkahely. Ha ezek adottak, gondoskodj az életminőséget javító szolgáltatásokról is. A versenyképes bérek és az ésszerű adókulcs szintén sokat segítenek. A város addig fog növekedni, amíg polgárainak alapvető igényeit megfelelően kielégíted. @PHa nem sikerül megfelelni a lakosság igényeinek, kivándorlási hullám indulhat. Ez könnyen ördögi körhöz vezethet: az emberek a szolgáltatások hiánya miatt elköltöznek, távozásukkal azonban munkaerőhiányt okoznak. A munkaerőhiány miatt még több szolgáltatás romlik. Mindenképpen kerüld el, hogy a körülmények annyira rosszra forduljanak, hogy az emberek tömegesen elhagyják a várost. @PA népesség a születések és a halálozások következtében is nőhet vagy csökkenhet. Rendszeresen keresd fel a @25Magtárak&Felügyelőjét, hogy nyomon követhesd a lakosság átlagéletkorát. A dolgozók egy bizonyos kor után nyugdíjba vonulnak, ezért hirtelen munkaerőhiány alakulhat ki, ha a népesség nagy része egyszerre éri el ezt a kort. Ha azt látod, hogy a lakosság elöregszik, próbálj új, általában fiatalabb bevándorlókat vonzani. @PA rossz Városi hangulat nemcsak a kivándorlást ösztönzi, hanem a @36bűnözést is. @PHa gyorsan szeretnéd javítani a Városi hangulatot, rendezz fényűző vagy nagyszabású @51ünnepséget. Az ünnepség egy időre eltereli az emberek figyelmét a gondjaikról, a vidámság pedig jobb kedvre deríti őket. Ez azonban csak átmeneti megoldás. Ha nem szünteted meg a rossz Városi hangulat kiváltó okait, a lakosság kedve hamarosan ismét romlani fog. @L@LHa többet szeretnél megtudni az ókori Egyiptom népességnövekedéséről, kattints @167ide. Az ókori Egyiptomba érkező különféle bevándorlókról pedig @388itt olvashatsz többet."
        }
    }

    message_game_concept_workers {
        id: 40,

        size [30, 28]
        title { text: "Munkaerő" }
        subtitle { text: "Játékmenet" }
        content {
            text: "A munkások jelentik a város éltető erejét. Az ő munkájuk biztosítja mindazokat az árukat és szolgáltatásokat, amelyeket a polgárok élveznek. E szerény emberekről való gondoskodás legyen egyik legfontosabb feladatod. Nélkülük a város nem maradhat fenn. @PA legtöbb új épület megépítése után egy alkalmazottat küld ki munkaerőt toborozni. Ha a toborzási körzetében lakott házakat talál, és a városban összességében elegendő munkanélküli dolgozó van, akkor az épület munkaerőhöz jut. @PBár a munkások nem sokat panaszkodnak a sorsukra (na jó, azért panaszkodnak eleget), nekik is vannak céljaik és álmaik. Arról álmodoznak, hogy egy nap az @41írnokok közé emelkedhetnek. @L@LHa szeretnéd megtudni, milyen volt dolgozni az ókori Egyiptomban, kattints @155ide."
        }
    }

    message_game_concept_scribes {
        id: 41,

        size [30, 28]
        title { text: "Írnokok" }
        subtitle { text: "Játékmenet" }
        content {
            text: "Azok a @40munkások, akik keményen dolgoznak és szorgalmasan gyűjtögetik debeneiket, idővel írnokokká válnak. @PAz írnokok rendkívül gazdagok, és nem végeznek fizikai munkát. Tágas otthonokban élnek, luxussal körülvéve, napjaikat pedig pihenéssel és tanulással töltik. Több szolgáltatást igényelnek, mint a munkások, viszont jóval több adót is fizetnek. @PMivel adójuk igen magas, megfelelő számú írnok jelentős bevételt hozhat a város kincstárának. Ha azonban túl sok írnok él a városban, a munkaerőhiány miatt a város működése akadozni kezdhet. @PHa nem tudod fenntartani a magas szintű szolgáltatásokat, az írnokok idővel visszasüllyednek a munkásosztályba. Ennél rosszabbat egy írnok el sem tud képzelni. A város ugyan több munkáshoz jut, de adóbevétele csökken, és a Jólét értékelése is romlik. @L@LAz @387írnokok az ókori egyiptomi @168társadalom egyik legtehetősebb rétegét alkották. A hivatkozásokra kattintva többet is megtudhatsz róluk."
        }
    }

    message_game_concept_walkers {
        id: 42,

        size [30, 28]
        title {
            text: "Járókelők",
        }
        content {
            text: "A város utcáin közlekedő embereknek szinte mindig valamilyen céljuk van. Egyesek árukat szállítanak egyik helyről a másikra. Mások szolgáltatásokat nyújtanak azoknak a házaknak vagy épületeknek, amelyek mellett elhaladnak. Megint mások éppen a városba érkeznek vagy onnan távoznak. Csak néhány kiváltságos engedheti meg magának, hogy minden különösebb cél nélkül sétálgasson. @PA járókelők két fő csoportra oszthatók: célirányos és kóborló járókelőkre. A két típus egészen eltérően viselkedik. @L@LCélirányos járókelők @LA célirányos járókelők munkahelyükről egy meghatározott cél felé indulnak. A város úthálózatának térképét használva mindig a legrövidebb útvonalat választják. Ilyenek például a Bazár beszerzői, a kivándorlók, a bevándorlók és a szállítók. @L@LKóborló járókelők @LA kóborló járókelők akkor nyújtanak szolgáltatást a lakóknak, ha a házak két mezős körzetében haladnak el. Néhányuk a város más épületeinek is fontos szolgáltatásokat biztosít. @PEzek a járókelők meghatározott úti cél nélkül indulnak el épületükből. Minden alkalommal más irányba próbálnak elindulni, ezután pedig mozgásuk teljesen kiszámíthatatlanná válhat. @PMinden útkereszteződésnél el kell dönteniük, merre forduljanak. Nem mindig ugyanúgy döntenek, ezért előfordulhat, hogy egy korábban már érintett házhoz hosszú ideig nem térnek vissza. @PA legjobb módja a kóborló járókelők irányításának a jó várostervezés. Mivel a kereszteződések nagy szabadságot adnak nekik, érdemes ezek számát minimálisra csökkenteni, hogy könnyebben arra haladjanak, amerre szeretnéd. @PA @358Útzárak szintén hatékony eszközök a kóborlók irányítására. Ha egy kóborló Útzárhoz ér, megfordul. A célirányos járókelők figyelmen kívül hagyják az Útzárakat. @PKóborló járókelő például a Bazár árusa, a vízhordó, a pap és az orvos. @PEgyes kóborló járókelők bizonyos helyzetekben célirányosként viselkednek. A tűzőrök például tűzoltás közben, a rendőrök pedig veszély elhárításakor célirányosan mozognak. Minden más esetben kóborlóként viselkednek. @L@LJárókelők élete @LA kóborló járókelők munkaideje korlátozott. Meghatározott ideig járőröznek, majd egy időre visszatérnek épületükbe. Ha munkahelyük teljes létszámmal működik, szinte azonnal újabb járókelőt küld ki. Ha munkaerőhiány van, az új járókelő kiküldése általában késik. @PA célirányos járókelők addig dolgoznak, amíg feladatukat be nem fejezik, még akkor is, ha ezért át kell sétálniuk az egész városon, majd vissza. @PAzok a járókelők, akik mindkét típus jellemzőivel rendelkeznek, szintén korlátozott munkaidővel dolgoznak. A céljukhoz való eljutás ideje csökkenti azt az időt, amelyet kóborlással tölthetnek. Ez különösen a fellépőknél feltűnő, akiknek előadásai lerövidülnek, ha iskolájuktól messze található a fellépési helyük. @PVégül ne feledd, hogy az ártér és a szárazföld közötti partfal meredek, sáros és nehezen járható. Senki sem tud átkelni rajta, hacsak egy @57út nem teszi járhatóvá ezt a határt. @L@LRagadozók @LNem minden, a városban kóborló élőlény barátságos. Veszélyes vadállatok is ólálkodnak a városban és környékén, könyörtelenül megölve bárkit, aki az útjukba kerül. A rendőrök megpróbálják elejteni ezeket a vadakat, de ellenük általában a hadsereg bevetése a leghatékonyabb. Figyelj a hiénákra, vízilovakra, krokodilokra, áspiskígyókra, skorpiókra és oroszlánokra."
        }
    }

    message_employment_unemployment {
        id: 43,

        size [30, 28]
        title { text: "Foglalkoztatottság és munkanélküliség" }
        subtitle { text: "Játékelem" }
        content {
            text: "A város szinte minden épületéhez dolgozók kellenek. Munkaerő nélkül a város nem tudja ellátni polgárait. @PHa felépítesz egy munkaerőt igénylő épületet, egy toborzó járja az utcákat dolgozókat keresve. Ha elhalad a közeli lakóházak mellett, és a városban van szabad munkaerő, sikerrel jár, és az őt küldő épület alkalmazottakat kap. @PA toborzók dolga nem mindig könnyű. A város vezetőjeként az egyik legnagyobb kihívás az egyensúly megteremtése a munkaerő és az állások száma között. Ideális esetben pontosan annyi állás lenne, ahány ember dolgozni akar. Ez azonban ritkán valósul meg. A városban vagy túl sok a munkás és kevés az állás, vagy túl sok az állás és kevés a munkás. @PA munkanélküliség nem tesz jót a városnak. A munka nélkül maradt emberek elégedetlenné válhatnak, ami rontja a város @39hangulatát. Akár @36bűnözéshez is fordulhatnak. A munkanélküliség legjobb ellenszere új munkahelyek létrehozása. Általában nem árt, ha a város több árut és szolgáltatást termel a szükségesnél. Néhány plusz tanya, több szórakozási lehetőség, új iskolák, könyvtárak vagy templomok mind hasznára válnak a városnak. Miközben csökkented a munkanélküliséget, javíthatod a város Jóléti és Kulturális értékelését is. @PA munkanélküliség csökkentésének másik - bár kegyetlen - módja a város népességének csökkentése. Ezt a lakóházak lerombolásával érheted el, ami kivándorlásra kényszeríti az embereket. Ennek is lehet kedvező hatása. Ha az alacsonyabb szintű házakat bontod le, a város lakásállományának átlagos értéke nő. Ez magasabb Jóléti értékelést eredményezhet. @PA másik foglalkoztatási gond a munkaerőhiány, vagyis amikor több az állás, mint a rendelkezésre álló dolgozó. A legjobb megoldás új bevándorlók odavonzása. Építs új lakónegyedeket, vagy segítsd a meglévőket nagyobb házakká fejlődni. Ügyelj arra is, hogy a @39Város&Hangulata magas legyen. Az egyiptomi átlagnál magasabb bérek vagy az alacsonyabb adó szintén új bevándorlókat vonzanak. @PMíg az új lakók megérkeznek, egyeztess a @24Kereskedelmi&felügyelővel és a @20Munkaügyi&felügyelővel a hiány enyhítéséről. A Kereskedelmi felügyelőnél átmenetileg leállíthatsz olyan iparágakat, amelyek nélkül rövid ideig megvagy. Így felszabadul néhány dolgozó más munkákra. Ha nem akarsz egy egész iparágat leállítani, lehet, hogy le kell bontanod néhány hozzá tartozó épületet. @PBeszélj a Munkaügyi felügyelővel a munkaerő-prioritások beállításáról. Ha a létfontosságú munkákat teszed első helyre, a lakosok továbbra is megkapják a megélhetésükhöz szükséges javakat és szolgáltatásokat. @PA munkaerőhiány szokatlan, és nem igazán jó ellenszere, ha hagyod, hogy az @41írnokok házai visszafejlődjenek @40munkások házaivá. Ez rontja a város Jóléti értékelését és csökkenti az adóbevételeket, de növeli a munkaerőt - a leggazdagabb polgárok reményeinek és álmainak árán! @PBár a munkanélküliség megterhelő az állástalanok számára, egy kis munkanélküliség valójában hasznos egy fejlődő városnak, mert mindig lesz szabad munkaerő az új épületekhez. Az 5 százalékot meghaladó munkanélküliség azonban már problémákat okoz."
        }
    }

    message_drinking_water {
        id: 44,

        size [30, 28]
        title { text: "Ivóvíz" }
        subtitle { text: "Játékelem" }
        content {
            text: "Az emberek egyik legelső igénye a tiszta ivóvízhez való hozzáférés. Enélkül a lakóházak egyáltalán nem fejlődnek. @PA @62kutak és a @61vízellátók biztosítanak ivóvizet a lakosoknak. A kutak egyszerű vízforrások. Egy újonnan alapított, még fejlődő városban egy ideig megfelelnek, de az emberek hamarosan már nem elégednek meg a kútvízzel. Rövid időn belül a vízellátókból származó vizet fogják igényelni. @PA vízellátók vízhordókat alkalmaznak, akik vizet visznek az otthonokba. Amikor egy vízhordó elhalad egy ház mellett, az a ház tiszta ivóvízhez jut. Figyeld őket alaposan: @42kóborló&járókelők, ezért nem mindig ugyanazon az útvonalon közlekednek. Azok a házak is elveszíthetik a tiszta ivóvízhez való hozzáférést, amelyek korábban elegendő vizet kaptak, különösen ha megváltoztatod a környék úthálózatát. @PHa a környék @56vonzereje elég magas, a vízellátó dolgozói javítanak az épület megjelenésén és hatékonyságán. Az így továbbfejlődött vízellátók vízhordói gyakrabban járják be a környéket. @PMind a kutak, mind a vízellátók csak talajvizet rejtő területre építhetők, amit a rajta növő fű jelez. @PA tiszta ivóvíz előnyeiről további információt a @53Város&egészsége fejezetben találsz."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,

            size [30, 28]
        title { text: "Élelmiszer-termelés" }
        subtitle { text: "Játékelem" }
        content {
            text: "A polgárok szívéhez a gyomrukon át vezet az út. A bőséges és változatos élelmiszer javítja a @39Város&Hangulatát és a @53Város&egészségét is. @PA játékban többféle élelmiszernövény termeszthető: @89gabona, @90gránátalma, @90csicseriborsó, @90saláta és @90füge. Kétféle gazdálkodás létezik: ártéri és réti. Mindkettőhöz útkapcsolat és munkaerő kell, de a hasonlóságok itt véget is érnek. Az élelem ráadásul nem csak földművelésből származhat. A @359vadászat, a @84halászat és a @360szarvasmarha-tenyésztés is ellátja a város magtárait. @L@LÁrtéri gazdálkodás @LAz ártéri földek működéséhez először a Nílus éves ciklusát kell megérteni. Minden évben, általában június és szeptember között a Nílus kilép medréből. Az árteret teljesen elönti a víz, így oda semmit sem lehet építeni. Néhány hónappal később a folyó visszahúzódik, termékeny iszapot hagyva maga után. Az ártér ismét használhatóvá válik, és újra megkezdődhet a művelés. @G56 @PA Nílus áradása nem minden évben egyforma. Vannak jobb és gyengébb áradások. A papok nílusi vízmérőkkel megállapítják, milyen lesz a következő áradás, majd jelentést tesznek a @31Főfelügyelőnek. Ha különös figyelmet fordítasz Oziriszre, a földművelés és a nílusi áradás istenére @51(lásd:&Vallás), nagyobb eséllyel lesz sikeres az éves áradás. @PAz ártereken a földeket, utakat és öntözőárkokat bármikor építheted, kivéve az áradás idején. Az ártéri földek építésekor csak maga a föld jelenik meg, épület nem, mert az áradás minden építményt elsodor. Mivel a parasztok nem lakhatnak az ártereken, szükségük van egy helyre, ahol munkára oszthatók be. Ezt a szerepet a @8munkatáborok töltik be. Innen indulnak a földekre vetni és aratni; munkatábor nélkül az ártéri földek parlagon maradnak. A parasztok csak bizonyos távolságot hajlandók megtenni, ezért ne építs munkatábort túl messze a földektől. @PA földeket a legjobb közvetlenül az áradás levonulása után megépíteni. Így a teljes tenyészidőszakot kihasználhatják a következő áradásig, és a lehető legnagyobb termést hozzák. Más időpontban épített földek kevesebbet teremnek. @PA másik fontos szempont a talaj termékenysége. Minél sötétebb a föld és dúsabb a növényzet, annál termékenyebb. A legjobb földek általában közvetlenül a folyó mellett találhatók, távolodva azonban egyre gyengébbé válnak. A legtermékenyebb helyre épített földek adják a legnagyobb termést. Az ártéren öntözőárkok építésével javíthatod a folyótól távolabbi földek termékenységét, így a gyengébb áradások idején sem maradnak teljesen kiszáradva. @PA Nílus éves ritmusa miatt az ártéri földek évente csak egy termést adnak. A város túlélése múlhat azon, hogy elegendő munkás legyen a betakarításhoz, és legyen elég raktárkapacitás a termény befogadására. @L@LRéti gazdálkodás @LAz ártér nem az egyetlen termékeny terület, bár ez adja a megművelhető földek nagy részét. Földeket réteken is építhetsz, amelyeket sárga fűcsomók jeleznek. Minél sűrűbbek ezek, annál termékenyebb a talaj, és annál nagyobb a termés. Ezekhez a földekhez tartozik egy munkaépület is, ezért nincs szükség munkatáborból érkező parasztokra. Mivel ezeket nem önti el a víz, egész évben működnek. Területarányosan azonban a réti föld kevésbé termékeny, mint az ártér, ezért a terméshozam is kisebb. A réti földek szinte mindig hasznot húznak az öntözőárkokból. @L@LVadászat és halászat @LA vadászok és halászok Egyiptom természetes bőségét használják ki. Mindketten a saját bázisukról indulnak, elejtik vagy kifogják zsákmányukat, majd visszatérnek feldolgozni azt. @PA vadászok vadászházakból indulnak. Struccokra, vízimadarakra vagy antilopcsordákra vadásznak. Ha ilyen állatokat látsz a város környékén, építs a közelben vadászházat. @PA halászok a halászkikötőkben gyülekeznek, ahol elmesélhetik egymásnak a nagy fogás történetét. A kikötők természetesen vízpartra épülnek, a halászoknak pedig hajóácsra van szükségük csónak készítéséhez. Csak ezután indulhatnak halászni. Nem minden város alkalmas halászatra vagy vadászatra. Ha halakat látsz kiugrani a vízből, ott lehet halászatot kialakítani. @PA csordák, madárrajok és halrajok mérete korlátozott. Vadászatból és halászatból egy kisebb város még ellátható élelemmel, de egy nagy népesség nem élhet kizárólag halon és vadhúson. @L@LSzarvasmarha-tenyésztés @LA marhatelepek kiváló kiegészítő élelmiszerforrást jelentenek. Bármilyen talajra építhetők, nem csak termékeny földre, így a jó földeket más célra használhatod. A szarvasmarhák a @89gabonatermesztés melléktermékeként keletkező szalmát fogyasztják. A marhatelepek számát csak az korlátozza, hogy mennyi szalmát tud a város takarmányozásra fordítani. @L@LÉlelmiszer-elosztás @LA @3magtárak és a @2piacok jelentik a kapcsolatot az élelmiszer-termelők és a lakosság között. A magtárak tárolják az emberek fogyasztására szánt élelmet, a piacok pedig eljuttatják azt az otthonokba. @PHa egy termelő elkészül az áruval, egy hordár a magtárba szállítja. A piaci beszerzők innen szerzik be a vásárlók által igényelt élelmiszereket. Egyszerre többféle élelmet is vihetnek. Miután visszatérnek a piacra, a piaci árusok végigjárják a környéket, és kiosztják az élelmet a lakóknak. @PNagyon fontos, hogy elegendő magtár és piac legyen. Ha minden magtár megtelik, a hordár a @4raktárba viszi az élelmet, feltéve hogy az fogad élelmiszert. A piaci beszerzők azonban a helyben termelt élelmet nem a raktárakból szerzik be (bár más árukat és importált élelmiszereket igen). Az élelmiszer legfőbb forrásai a magtárak. @PA magtárak és piacok elhelyezése nem egyszerű. A magtárak legyenek közel a termelőkhöz, hogy a hordároknak ne kelljen messzire menniük. A piacok legyenek közel a magtárakhoz, hogy könnyen feltölthessék készleteiket, ugyanakkor a kiszolgált lakóházakhoz is közel kell lenniük. Ráadásul egyik épület sem kellemes szomszéd, ezért mindig kompromisszumot kell kötni. @PAhogy nő a város, előfordulhat, hogy a magtárakat távolabb kell építened a termelőktől, hogy a külső városrészek piacai is hozzájussanak az élelemhez. Ilyenkor használd a magtár Különleges utasításait, hogy biztosan megkapja a szükséges készleteket. @L@LÉlelmiszer importálása @LNéhány város nem képes elegendő vagy kellően változatos élelmet előállítani, ezért más városokból kell importálnia. Az importált élelmiszer a raktárakba érkezik, ahonnan a piaci beszerzők elviszik a piacokra. @L@LA fejezetben számos kapcsolódó téma hivatkozásként szerepel (ezek más színnel jelennek meg). Ezek elolvasása segít jobban megérteni az élelmiszer-termelést és -elosztást. @L@LAz ókori Egyiptom élelmezésének történetéről kattints @150ide. A Nílus hatásairól pedig @157itt olvashatsz."
        }
    }

    message_game_concept_industry {
        id: 46

        size [30, 28]
        title { text: "Ipar" }
        subtitle { text: "Játékelem" }
        content {
            text: "Az ipar valószínűleg a város legnagyobb foglalkoztatási ágazata. Az itt készült termékek egy részét a lakosok életminőségük javítására használják, másokat pedig jelentős haszonnal lehet @47kereskedni. @PBár egy városban sokféle iparág működhet, mindegyiknek vannak közös jellemzői. Mindegyik munkaerőt igényel, és a termelés hatékonysága csökken, ha egy nyersanyagtermelő vagy feldolgozó üzem munkaerőhiánnyal küzd. Minden ipari épületnek útkapcsolatra is szüksége van, hogy a dolgozók eljuthassanak oda. @PEgyes iparágak nyersanyagokat állítanak elő, amelyeket más üzemek késztermékké dolgoznak fel. Ilyenek a @92agyagbányák, @361drágakőbányák, @93rézbányák, @94favágók és @94nádvágók. A @91árpaföldek, @91hennaföldek és @91lenföldek szintén ipari nyersanyagokat termelnek. A @89gabonaföldek az élelmiszer mellett szalmát is előállítanak, amely nem élelmiszeripari alapanyag. Egy nyersanyagtermelő általában két feldolgozóüzemet képes ellátni. A nyersanyagokkal is lehet kereskedni, de kevesebbet érnek, mint a késztermékek. @PA nyersanyagokat feldolgozó üzemek (más néven műhelyek): @96sörfőzdék, @99ékszerészek, @60szövödék, @97papiruszkészítők, @1fazekasműhelyek, @364téglagyárak, @473lámpakészítők, @470festékkészítők, @98fegyverkovácsok és @98harcikocsi-készítők. Termékeiket a város felhasználhatja vagy eladhatja a piacon. @PA @95kőfejtők és a @93aranybányák eltérnek a többi iparágtól, mert náluk a nyersanyag egyben a késztermék is. A @82hajóácsok fából hajókat készítenek, de a hajók nem értékesíthetők a piacon. @PA szállítómunkások juttatják el az árukat rendeltetési helyükre. A nyersanyagtermelők először mindig a nyersanyagot igénylő műhelyeket próbálják ellátni, előnyben részesítve a legközelebbit. Ha nincs rá igény, a legközelebbi, szabad hellyel rendelkező @4raktárba viszik az árut. Ha nincs ilyen, várakoznak, amíg fel nem szabadul hely. Ez alól csak az aranybánya taligása és a kőfejtő szánhúzója kivétel. Az aranybánya taligása mindig a Palotába viszi az aranyat, raktárba soha. A kőfejtők pedig mindig raktárba szállítják a követ, mivel abból nem készül más termék. @G74 @PNéhány városi épület működéséhez ipari termékekre is szükség van. Ilyen a @70könyvtár, a @68írnokiskola, a @74szenetház, a @88toborzó, a @66balzsamozó, a @363kézművescéh és a @363ácscéh. A műhelyek szállítómunkásai először ezekbe az épületekbe próbálják eljuttatni a szükséges árut. Ha egyik sem igényli, a készterméket raktárba viszik, vagy várakoznak, amíg felszabadul hely. A taligások nem bánják ezeket a kényszerszabadságokat, hiszen így is kapnak bért és élelmet. @PHa ellenőrizni szeretnéd, hogy minden rendben működik-e az iparban, használd a @18Problémák&nézetet. Ez megmutatja, mely ipari épületek nem működnek megfelelően, és miért. @PEgy épületre jobb gombbal kattintva megjelenik annak aktuális termelési állapota. Láthatod, teljes létszámmal működik-e, mennyire haladt a termelési ciklusban, és ha gond van, azt is, mi okozza. @PKattints a fenti hivatkozások bármelyikére (a hivatkozások kék színűek), ha többet szeretnél megtudni az egyes iparágakról. @L@LKattints @151ide az ókori Egyiptom iparának történetéért."
        }
    }

    message_game_concept_trade {
        id: 47,

        size [30, 28]
        title {
            text: "Kereskedelem",
        }
        subtitle {
            text: "Játékelem",
        }
        content {
            text: "Egyetlen város sem teljesen önellátó. A kereskedelem olyan árukat hoz a városodba, amelyeket nem tud előállítani. Az export jelentős bevételt termel, gyakran még többet is, mint az adók. Mivel a kereskedelem ennyire fontos, érdemes elkezdeni, amint a város már képes ellátni lakói alapvető szükségleteit. @PA @32Világtérképen láthatod, mely városok hajlandók kereskedni veled. A kereskedő városokat zászló jelöli. Kattints egy városra, hogy megtudd, milyen árukat vásárol és ad el. Az áru ikonjának sarkában látható kék pontok jelzik, évente mekkora mennyiséget hajlandó importálni vagy exportálni. Egy pont alacsony, három pont nagy kereskedelmi igényt jelent. Ezek az értékek a kereslet-kínálat vagy Egyiptom politikai helyzetének hatására változhatnak. @PKattints a „Kereskedelmi útvonal megnyitása” gombra, és fizesd ki az új kapcsolat létrehozásának költségét. Egy útvonal megnyitása drága lehet, de hosszú távon bőségesen megtérül. @PMiután megnyitottál egy kereskedelmi útvonalat, keresd fel a @24Kereskedelmi&felügyelőt a kereskedelem beállításához. A „Árak megjelenítése” gombbal láthatod az egyes áruk vételi és eladási árát. Észre fogod venni, hogy az eladási ár mindig alacsonyabb, mint a vételi. A különbség a kereskedők utazási és működési költségeit fedezi. @L@LImport @LEgy áru importálásához kattints a kívánt termékre. Ezután két lehetőséged van. Meghatározhatod, mennyit szeretnél készleten tartani, és ennek megfelelő utasítást adhatsz a Kereskedelmi felügyelőnek, vagy rábízhatod a döntést. A felügyelő addig importálja az árut, amíg a készlet a megadott szint alatt van, illetve amíg a kereskedelmi partner éves kvótája ki nem merül. @PEgyes javak kizárólag importból szerezhetők be. Ilyen például a fehér márvány a monumentumok építéséhez vagy az olaj a @473lámpákhoz. A @56lakóházak legmagasabb szintre fejlesztéséhez luxuscikkeket is importálnod kell. @PAz import költséges lehet, ezért rendszeresen ellenőrizd a város @4raktárait. Ha azt látod, hogy egy importált áruból túl nagy készlet halmozódott fel, ideiglenesen állítsd le az importját, amíg a készlet nem csökken. A nyersanyagok importja ráadásul olcsóbb, mint a késztermékeké. Hosszú távon olcsóbb, ha a város maga dolgozza fel az importált nyersanyagokat. @L@LExport @LEgy áru exportálásához kattints a kívánt termékre. Ezután eldöntheted, mennyi maradjon készleten, vagy ezt is rábízhatod a Kereskedelmi felügyelőre. A felesleg exportálásra kerül a partner éves kvótájának erejéig. Ne feledd, hogy sok exportált áru a lakosság számára is fontos, ezért mindig hagyj elegendő készletet a város szükségleteire. Rendszeresen ellenőrizd a piacokat és a lakóházakat, hogy hozzájutnak-e az exportált termékhez. Arról is gondoskodj, hogy az ipari épületek megkapják a működésükhöz szükséges késztermékeket. Ha a házak vagy más épületek hiányt szenvednek, valószínűleg túl sokat exportálsz. @LElőfordulhat, hogy ugyanazt az árut egy városból importálhatod és exportálhatod is. Ez nagyobb rugalmasságot ad az ipar megtervezéséhez. Ha növelni akarod a bevételeket, termeld meg az árut, és exportáld. Ha inkább más feladatra használnád a munkaerőt, importáld azt. Ugyanazt az árut azonban nem lehet egyszerre importálni és exportálni, és nem éri meg egyik városból megvenni csak azért, hogy egy másiknak továbbadd. A vételi ár magasabb az eladásinál, így közvetítőként csak veszteséget termelnél. Ezzel szemben a nyersanyag importálása és a belőle készült késztermék exportja gyakran igen jövedelmező. @PA kereskedők karavánnal vagy kereskedelmi hajóval érkeznek. Mindkét esetben működő @4raktárra van szükség. A hajókkal folytatott kereskedelemhez ezen felül @83dokkoló is kell. A kereskedelmi hajók minden ügyletet a dokkolóknál bonyolítanak le, érkezésükkor pedig a dokkoló taligásai hozzák el a szükséges árukat a raktárakból."
        }
    }

    message_game_concept_money {
        id: 48,

        size [30, 28]
        title {
            text: "Pénzügyek",
        }
        subtitle {
            text: "Játékelemek",
        }
        content {
            text: "Pénz nélkül nem lehet várost építeni, és a kincstár állapota jól mutatja a város sikerességét. A város adókból, exportból, ajándékokból, valamint – ahol erre lehetőség van – aranybányászatból jut bevételhez. Ezekről később részletesebben is szó lesz, de előbb érdemes megismerni a pénzügyek alapjait. @L@LAdósság @LAmikor a kincstár először kiürül, más egyiptomi vezetők esetenként kisegíthetnek némi debennel. Ez semmilyen hátránnyal nem jár, és nem várják el a visszafizetését. Tekintsd azonban figyelmeztetésnek, hogy ideje visszafogni a költekezést. @PHa ezt a segítséget is elköltöd, vagy nem kapsz ilyet, a város legfeljebb 5000 deben adósságot halmozhat fel. Az adósságot sárga számok jelzik. @PA rövid, átmeneti eladósodás gyakran elkerülhetetlen, és nem okoz gondot, ha hamar ismét pozitív lesz az egyenleged. A tartós adósság viszont akár a játék végét is jelentheti. @L@LAz adósság következményei @LMinden hónapban, amikor a kincstár hiányt mutat, kamatot kell fizetned, amely automatikusan hozzáadódik az adóssághoz. Minél nagyobb a tartozás, annál több kamatot fizetsz, így az adósság egyre gyorsabban nő. @PHa az évet adóssággal zárod, nem tudod befizetni az éves adót a Királyságnak (lásd lent). Ez ugyan nem kerül pénzbe, de rontja a @35Királyság&értékelést. Több egymást követő elmulasztott befizetés egyre súlyosabb következményekkel jár. @PHa az első eladósodást követő 12 hónapon belül egyszer sem sikerül pozitív egyenleget elérned, a Királyság értékelése tovább romlik, mert a többi vezető elveszíti a bizalmát. Az első ilyen büntetés még átvészelhető, de ha a második évfordulóra sem sikerül kilábalnod az adósságból, a Királyság értékelése jelentősen visszaesik, és minden további év még súlyosabb lesz. @L@LKilábalás az adósságból @LAz adósság komoly probléma, ezért amilyen gyorsan csak lehet, meg kell szabadulni tőle. A bevételszerzés módjairól később olvashatsz, de addig is kerüld azokat a kiadásokat, amelyek nem termelnek bevételt. Az adószedő hivatalok, exportképes iparágak és új kereskedelmi útvonalak általában jó befektetésnek számítanak. @L@LÉves adó @LMinden év végén a városnak adót kell fizetnie a Királyságnak. Az összeg a város teherbíró képességétől függ: kezdetben alacsony, majd a népesség és a gazdagság növekedésével emelkedik. A fizetendő összeget a @30Kincstári&felügyelőnél tekintheted meg. @PHa az év végén van pénz a kincstárban, az adó automatikusan levonásra kerül. Nem kell külön intézkedned. Ha azonban adósságban zárod az évet, az adót nem tudod befizetni, és romlik a @35Királyság&értékelésed. Egy kihagyott év még nem súlyos, de a többször egymás után elmulasztott befizetések egyre nagyobb büntetéssel járnak. @L@LAdók @LAz adók fedezik a város által nyújtott szolgáltatásokat. A lakosok nem panaszkodnak, amíg az adókulcs ésszerű. A kezdeti 9% jó kiindulási pont, de ezt bármikor módosíthatod a Kincstári felügyelőnél vagy a Palotára jobb gombbal kattintva. Az alacsonyabb adókulcs növeli az elégedettséget, a magasabb viszont panaszokat okoz, sőt tömeges kivándorláshoz is vezethet. @PAz adóemelés néha elkerülhetetlen. Ha azt látod, hogy a város hamarosan eladósodik, átmenetileg emelheted az adókat. Hosszabb távon azonban jobb más megoldást keresni, mert a magas adó gyorsan lerontja a @39Város&Hangulatát. @PA lakosok ugyan hajlandók adót fizetni, de csak akkor, ha van, aki beszedje. Ehhez szükség van egy @77Palotára és @80adószedő hivatalokra. @PA Kincstári felügyelő megmutatja, a lakosság mekkora része szerepel az adónyilvántartásban, illetve mennyi adóbevétel veszett el a kevés adószedő miatt. A @18Adó&nézet segítségével ellenőrizheted, hogy minden városrészből egyformán szedik-e be az adót. Ha egyes lakosok fizetnek, mások pedig egyáltalán nem, a @39Város&Hangulata romlik, és akár @36bűnözés is kialakulhat. @L@LKereskedelem @LAz exportból származó bevétel valószínűleg a város legfontosabb pénzforrása lesz. Nyiss meg minél hamarabb kereskedelmi útvonalakat. Fontos, hogy jól ismerd az export működését, ezért ha bizonytalan vagy, olvasd el a @47Kereskedelem fejezetet. @L@LAranybányászat @LNéhány város saját pénzt is előállíthat. Az aranyat debenné, Egyiptom pénznemévé alakítják. Ha sziklafalban csillogó érceket látsz, lehetőséged nyílhat @93aranybánya építésére. Ne örülj azonban túl korán: lehet, hogy csak @93rézércet találtál, ami szintén értékes, de nem ér fel az arannyal. Az Ipar menü nyersanyagok részében ellenőrizheted, milyen fémet bányászhatsz a városodban. @PAz aranybányák ugyanúgy működnek, mint a többi @46iparág, de az aranyat kizárólag a Palotába szállítják, ahol debenné alakítják. Raktárba soha nem kerül. @L@LCsaládi vagyon és fizetés @LNemcsak a város, hanem te is kereshetsz pénzt. Amint felépíted a @78kúriádat, fizetést kapsz a város vezetéséért. A bért a városi kincstár fizeti, összege pedig a tapasztalatodtól függ. A fizetésedet módosíthatod, de ha indokolatlanul magas összeget állítasz be magadnak, a @35Királyság&értékelés romolhat. Alacsonyabb fizetést is kérhetsz, vagy akár teljesen le is mondhatsz róla, ami javíthatja a megítélésedet. Ha a város pénzügyi gondokkal küzd, ez jó módja a kiadások csökkentésének. @PA családi megtakarításaidból bármikor átutalhatsz pénzt a városi kincstárba, így megszüntetheted vagy megelőzheted az adósságot. A városi pénzt azonban soha nem viheted át a saját számládra. Az már sikkasztás lenne! @PA családi vagyonból „ajándékot Egyiptomnak” is adhatsz. Az ilyen adományok – akár a népnek, akár a felügyelőd döntése alapján más vezetőknek – azonnal kis mértékben javítják a Királyság értékelését. Légy azonban óvatos: ha rendszeresen ajándékozol, idővel elvárják ezt tőled, és ha abbahagyod, az már ronthatja a megítélésedet. @PA @22Politikai&tanácsadó fejezetében további információkat találsz a személyes megtakarításaidról."
        }
    }

    message_game_concept_entertainment {
        id: 49,

            size [30, 28]
        title {
            text: "Szórakoztatás",
        }
        subtitle {
            text: "Játékelem",
        }
        content {
            text: "A sok munka és semmi szórakozás még Imhotepet is unalmassá teszi. Gondoskodj róla, hogy a város lakói megfelelő szórakozási lehetőségekhez jussanak, így kellemesebb lesz számukra az élet. @PA @71mutatványos bódék, @72zenepavilonok, @73előadóterek, @74szenetházak és @479állatkertek biztosítják a lakosok által igényelt szórakozást. Egy új városban a legkisebb szórakozóhely, a mutatványos bódé is elegendő. Ahogy azonban a város fejlődik, úgy nő a szórakozás iránti igény is, és a lakosok egyre többféle előadót várnak el. A @28Szórakoztatási&felügyelő segít felmérni ezeket az igényeket. @PA legtöbb előadót @75képzőközpontokban kell kiképezni. A zsonglőrök a zsonglőriskolában tanulnak, a zenészek a konzervatóriumban gyakorolnak, a táncosok pedig a tánciskolában sajátítják el a legújabb lépéseket. Kiképzés után az előadók a képzőközpontból a szórakoztató épülethez sétálnak. A szenetmesterek nem igényelnek ilyen képzést. @PA lakosok akkor érzékelik, hogy szórakozási lehetőség áll rendelkezésükre, amikor előadók haladnak el a házaik mellett (a járókelőkről bővebben @42itt olvashatsz). Az előadók a teljes kapacitással működő szórakoztató épületekből érkeznek. A zenészek, zsonglőrök és táncosok a képzőközpont és a fellépési hely között is végigjárják az utcákat. Ezt érdemes figyelembe venni a várostervezésnél. Ha a képzőközpont és a szórakozóhely a lakónegyed két átellenes oldalán áll, az előadók útközben is szórakoztatják a lakókat. Arra azonban ügyelj, hogy a képzőközpontok ne legyenek túl messze a fellépési helyektől. Minél tovább tart az út, annál rövidebb lesz az előadás, és annál nagyobb az esélye, hogy a szórakozóhely üresen áll, így senki sem részesül az előnyeiből. @PA szenetház és az állatkert működéséhez árukra is szükség van. A szenetház @96sört igényel a vendégek szomjának oltására, az állatkertnek pedig @89szalmára és @359vadhúsra van szüksége az állatok ellátásához. @L@LAz ókori Egyiptom szórakozásáról további információt @165itt találsz."
        }
    }

    message_game_concept_education {
        id: 50,

        size [30, 28]
        title {
            text: "Oktatás",
        }
        subtitle {
            text: "Játékelem",
        }
        content {
            text: "Az oktatás a tehetősek kiváltsága. Tudják, hogy a @68írnokiskolában szerzett tudás jobb jövőt biztosít gyermekeiknek, maguk számára pedig fontos a @70könyvtárhoz való hozzáférés. @PAz írnokiskolák és a könyvtárak @97papirusz nélkül nem működnek. Könyvtárat csak akkor építhetsz, ha elegendő papirusz van a @4raktárakban a polcok feltöltéséhez. Mindkét épület @42járókelői papiruszt visznek magukkal, miközben terjesztik a műveltséget a lakosság körében. Az oktatási épületek folyamatos működéséhez a városnak papiruszt kell előállítania vagy @47importálnia. @PKeresd fel a @27Oktatási&felügyelőt, hogy ellenőrizd, kielégíti-e a város a lakosság oktatási igényeit. @PA megfelelő számú könyvtár és írnokiskola hozzájárul a város @35Kulturális&értékeléséhez. @L@LTovábbi információt az ókori Egyiptom szórakozásáról @165itt találsz."
        }
    }

    message_game_concept_relition {
        id: 51,

        size [30, 28]
        title {
            text: "Vallás",
        }
        subtitle {
            text: "Játékelem",
        }
        content {
            text: "Egyiptom öt fő istene: Ozirisz, a földművelés és a nílusi áradás istene; Ptah, a kézművesek istene; Ré, a Királyság istene; Széth, a pusztítás istene; valamint Basztet, az otthon istennője. Ha elnyered kegyüket, a város sok előnyhöz jut, ha azonban elhanyagolod őket, súlyos bajokat zúdíthatnak rá. A @29Templomi&felügyelő ismeri az istenek hangulatát, ezért érdemes gyakran felkeresni. @PSok városnak van védőistene. Ő többet vár el a várostól, mint a többi helyi istenség. A helyi istenek kevesebbel is beérik, de ugyanúgy képesek segíteni vagy ártani. Egyes istenek egyáltalán nem ismertek a városban, őket nyugodtan figyelmen kívül hagyhatod. @PAz istenek kiengesztelésének legjobb módja, ha elegendő @67templomot&és&szentélyt emelsz tiszteletükre. A védőisten elvárja, hogy több szentélyt szentelj neki, mint bármely más istennek. A helyi istenek kevesebb templommal és szentéllyel is megelégszenek, de egymással azonos számút várnak el. @PAz istenek fesztiválokkal is kiengesztelhetők; minél nagyobb az ünnepség, annál hatásosabb. A fényűző és nagyszabású fesztivál jó átmeneti megoldás, ha egy isten kezd megharagudni a városra. Rendezz ünnepet a tiszteletére, így időt nyersz további templomok és szentélyek felépítésére, mielőtt lesújtana haragja. A fesztiválokat a @29Templomi&felügyelőnél szervezheted meg. Ne feledd, hogy fesztivált csak akkor tarthatsz, ha építettél Fesztiválteret. A nagyszabású fesztiválokhoz elegendő @96sörre is szükség van a @4raktárakban. Mivel a szervezés sok munkát igényel, 12 hónapon belül legfeljebb két fesztivál rendezhető. @PA templomokon és szentélyeken kívül templomkomplexumot is építhetsz, rendszerint a város védőistene tiszteletére. Egy városban egyszerre csak egy templomkomplexum lehet. Előfordulhat azonban, hogy egy különösen jelentőssé vált helyi istenség számára is építhetsz ilyet. Légy óvatos: a védőisten féltékennyé válhat, ha egy másik isten kap templomkomplexumot. @PA templomkomplexumok drágák, de megérik az árukat. Egy működő komplexum számos előnyt biztosít, és növeli a város @35Jóléti&értékelését. További díj ellenében jósdát és oltárt is építhetsz hozzá. A komplexumok és bővítményeik: @L@L@350Ozirisz&templomkomplexuma: @P\tSzobek oltára @P\tMin jósdája @L@351Ré&templomkomplexuma @P\tMaat oltára @P\tHórusz jósdája @L@352Ptah&templomkomplexuma @P\tÁmon oltára @P\tThot jósdája @L@353Széth&templomkomplexuma @P\tAnubisz oltára @P\tSzekhmet jósdája @L@354Basztet&templomkomplexuma @P\tÍzisz oltára @P\tHathor jósdája @L@LHa több isten számára is biztosítasz megfelelő számú imahelyet, az javítja a város @35Kulturális&értékelését. @L@LTovábbi információt az ókori Egyiptom vallásáról @399itt találsz."
        }
    }

    message_game_concept_war {
        id: 52

        size [30, 28]
        title {
            text: "Háború"
        }
        subtitle {
            text: "Játékelemek",
        }
        content {
            text: "A háború szinte állandó fenyegetés Egyiptomban. Néha idegen hódítók törnek be az országba dicsőséget keresve. Máskor Egyiptomon belüli zavargások vezetnek városok közötti összecsapásokhoz vagy akár teljes polgárháborúhoz. Időnként maga a fáraó indít hadjáratot esküdt ellenségei vagy fellázadt szövetségesei ellen. @PSokat tehetsz azért, hogy felkészülj a háborúra és megvédd a várost. Építs @85védelmi&építményeket a város határainak biztosítására. Emellett létesíts @37erődöket, @356hadihajókat és @357szállítóhajókat, hogy elbánj az ellenséggel, ha mégis betör a város területére. @PA @21Hadügyi&felügyelő figyelmeztet a közelgő támadásokra, és @34üzeneteket is kapsz az ellenséges csapatok mozgásáról. Az ellenség közeledését a @32Világtérképen követheted nyomon. @PÜgyelj arra is, hogy ne te magad provokálj ki támadást. Ha rosszul irányítod a várost vagy magadra haragítod Egyiptom vezetőit, a @35Királyság&értékelés romlik. Ha túl alacsonyra esik, városodat megtámadhatják. @PA háború nem csak a város környékén zajlik. Egyiptom időről időre saját területén és távoli vidékeken is hadakozik. Előfordulhat, hogy más városoknak vagy magának a fáraónak szüksége lesz katonáidra vagy hadihajóidra egy ellenség legyőzéséhez. A @21Hadügyi&felügyelőnél kijelölheted a külföldi szolgálatra szánt egységeket vagy hajókat, majd útnak indíthatod őket. Ha egyszerre több város kér segítséget, a @22Politikai&tanácsadónál kell eldöntened, melyiknek nyújtasz támogatást. @L@LTovábbi információt az ókori Egyiptom ellenségeiről @181itt találsz."
        }
    }

    message_tutorial_health {
        id: 53

        size [30, 28]
        title { text: "Egészség" }
        subtitle { text: "Játékelem" }
        content {
            text: "A rossz közegészségügy elriaszthatja a bevándorlókat, sőt a város lakóinak halálát is okozhatja. Gondoskodj róla, hogy polgáraid egészségesek maradjanak. Ha nem teszed meg a szükséges óvintézkedéseket, többféle egészségügyi csapás is sújthatja a várost. @PA lakosság egészségének megőrzéséhez biztosíts elegendő élelmet és @64orvosi&rendelőt. Minél változatosabban étkeznek a lakosok, annál egészségesebbek lesznek. A @66balzsamozókhoz való hozzáférés szintén javítja a város általános egészségi állapotát. A @61vízellátóból származó tiszta ivóvíz és a @65füvesasszony segít csökkenteni a malária kockázatát. A város egészségi állapota a lakók egészségének összességéből adódik, ezért mindenki számára biztosíts megfelelő egészségügyi ellátást. @PA malária mellett betegségek és a rettegett pestis is fenyegeti a várost. Gondos tervezéssel és a lakosság egészségének folyamatos figyelésével ezek a veszélyek többnyire megelőzhetők. @L@LBetegség @LBetegség azokban a házakban alakul ki, amelyeket ritkán keres fel orvos, és amelyek nem jutnak folyamatos élelmiszer-ellátáshoz. A betegség egy-egy házat érint, és nem terjed tovább. Ha azonban egy egész városrész rosszul van ellátva orvosokkal és élelemmel, több ház is megbetegedhet. @PA @18Kockázatok&nézet segítségével láthatod, mely házakat fenyegeti leginkább a betegség. Építs több orvosi rendelőt ezekre a területekre, és ügyelj arra, hogy a @2piacok megfelelően ellássák őket élelemmel. A @18Orvos&nézet megmutatja, mely házakat látogatják rendszeresen az orvosok, a @18Piaci&ellátás&nézet pedig azt, melyeket keresnek fel a piaci árusok. @L@LMalária @LA malária a vízparti élet egyik veszélye. A folyóhoz és a nádas mocsarakhoz közeli házak vannak a legnagyobb kockázatnak kitéve. A betegség kezdetben egy házat érint, de a malária átterjed a szomszédos otthonokra is. A veszély csökkentéséhez építs elegendő füvesasszonyt a veszélyeztetett területeken, és gondoskodj róla, hogy ezek a házak vízellátóból kapjanak ivóvizet. A @18Malária&nézet megmutatja a legveszélyeztetettebb házakat. @L@LPestis @LPestisjárvány akkor tör ki, amikor a város általános egészségi állapota alacsony, függetlenül az egyes házak állapotától. Csak úgy előzheted meg, ha az egész város egészségét jó szinten tartod. Ne keverd össze a pestist a @494Nagy&járványokkal. Azokat a város egészségi állapotától független események okozzák. @PHa pestis tör ki, először egyetlen házban jelenik meg. Az egyik lázálmoktól szenvedő fertőzött az utcára bolyong, és megfertőzi azokat a házakat, amelyek mellett elhalad. Körülbelül egy hónap múlva belehal a betegségbe. A füvesasszonyok gyorsan eltávolítják az útjukba kerülő pestises betegeket. @PSemmilyen nézet nem tudja előre megmutatni, melyik házban jelenik meg az első pestises eset, mert a járvány nem függ egyetlen ház vagy városrész állapotától sem. @L@PHa egy házat bármelyik fenti betegség sújtja, minden lakója meghal. A ház két hónapig fertőzött marad, ezalatt sem bevándorlók, sem csavargók nem költöznek be. Két hónap elteltével a ház újra lakhatóvá válik. Az előző lakók minden vagyontárgya megmarad benne. @PBár a fogorvosi rendelő egészségügyi épületnek számít, csak a környék vonzerejét növeli, a város általános egészségére nincs hatással. @PA @26Közegészségügyi&felügyelő segít megőrizni polgáraid egészségét."
        }
    }

    message_bent_pyramid {
        id: 54,

       size [30, 28]
        title {
            text: "Tört piramis",
        }
        content {
            text: "A Nap ihlette építészek a tört piramist egy meghajlított oldalú óriási obeliszknek képzelték el, amely a Nap egyik melegítő sugarát jelképezi. Hogy úgy ragyoghasson, mint maga a Nap, a piramis oldalait simára csiszolták. @PA tört piramis megépítéséhez @95közönséges&kőre, @95mészkőre és egy @8munkatábor parasztjaira lesz szükséged. Amikor a @4raktárakban négy tömb közönséges kő vagy mészkő összegyűlik, a parasztok szánra rakják a köveket, és a munkaterületre vontatják őket. A kövek pontos elhelyezéséhez elengedhetetlen a @363kőművescéh segítsége. A @363ácscéh a hozzá szállított fából építi meg a felhajtókat. @PA tört piramis kétféle méretben építhető. További információt a @370Monumentumok&építése, a @373Monumentumügyi&felügyelő és a @369Építésvezető fejezetekben találsz. @L@LA tört piramis történetéről @392itt olvashatsz többet."
        }
    }

    message_brick_core_pyramid {
        id: 55,

        size [30, 28]
        title {
            text: "Téglamagos piramis",
        }
        content {
            text: "A téglamagos piramisok a legösszetettebb piramisok, amelyeket építhetsz. Háromféle nyersanyagra és háromféle építőcéhre van szükség hozzájuk. Kell @364tégla, @95mészkő és @94fa, valamint a @363tégláscéh, a @363kőművescéh és az @363ácscéh szolgálata. Emellett @8munkatáborok parasztjai szállítják a nehéz téglákat és köveket az építkezésre, amikor elegendő mennyiség gyűlt össze a @4raktárakban. @PA téglamagos piramis készülhet kis, közepes vagy nagy méretben, valamint Piramiskomplexum és Nagy Piramiskomplexum változatban is. @PTovábbi információt a @370Monumentumok&építése, a @373Monumentumügyi&felügyelő és az @369Építésvezető fejezetekben találsz. @L@LA tört piramis történetéről @392itt olvashatsz többet."
        }
    }

    message_housing_and_desirability {
        id: 56

        size [35, 32]
        title { text: "Lakóházak és vonzerő" }
        content {
            text: "A lakónegyed kialakításának első lépése egy lakóterület kijelölése. Ne feledd, minden lakóháznak legfeljebb két mezőre kell lennie egy úttól. Amint kijelölöd a területet, bevándorlók érkeznek, és egyszerű kunyhókat építenek. Kezdetben a környéken gyűjtögetve szerzik meg a túléléshez szükséges javakat. Idővel azonban elvárják, hogy a város gondoskodjon róluk. Ahogy teljesíted igényeiket, saját maguk fejlesztik tovább otthonaikat. A lakóházak minősége hatással van a város @35értékeléseire, csökkenti az elvándorlást és új lakókat vonz. @PA lakosok legalapvetőbb igénye a tiszta @44ivóvíz és a @2piacokról származó @45élelmiszer. Ha ezt a két feltételt biztosítod, a kunyhók viskókká, majd házakká fejlődnek. @PA víz és az élelem után egyre több árut és szolgáltatást igényelnek. Szükségük lesz @1agyagedényekre, @96sörre és @60lenvászonra. A leggazdagabbak különféle @99luxuscikkeket, például ékszereket is elvárnak. Később egy második, importált luxuscikket is követelnek. Emellett hozzá kell férniük kedvenc szolgáltatásaikhoz: a @51valláshoz, @49szórakozáshoz, @50oktatáshoz és az @53egészségügyi&ellátáshoz. Ha mindezt biztosítod, a lakók egyre nagyobb és díszesebb otthonokat építenek. @PA lakók szép környezetben szeretnek élni. Építs @79kerteket, helyezz el @79szobrokat, vagy burkold az utakat @79díszburkolattal. A lakók értékelik a környezet szépítésére tett erőfeszítéseidet, és ennek megfelelően fejlesztik otthonaikat. @PA szép környezet iránti igény másik oldala, hogy nem szeretnek csúnya környéken lakni. Nem örülnek, ha otthonuk túl közel van az ipari épületekhez vagy a földekhez. Inkább távol maradnának a zajtól, a kellemetlen szagoktól, és a legtöbben az ipari épületeket is csúnyának tartják. Ha mégis a közelükbe kell építened lakóházakat – mert az iparnak dolgozókra van szüksége –, próbáld ezt sok kerttel, szoborral, díszburkolattal, valamint a szolgáltatásokhoz és árukhoz való könnyű hozzáféréssel ellensúlyozni. Ennek ellenére valószínűleg el kell fogadnod, hogy néhány ipari nyomornegyed mindig lesz a városban. @PA magas színvonalú lakóházak számos előnnyel járnak. Javítják a város @35Jóléti&értékelését, több lakót tudnak befogadni, így új lakóterületek kijelölése nélkül is növelhető a népesség és a munkaerő. Amikor a házak elérik a legmagasabb szintet, lakóik @41írnokokká válnak, akik ugyan adót fizetnek, de már nem tartoznak a munkaerőhöz. @PHa szeretnéd megtudni, mire van szüksége egy adott háznak a fejlődéshez, kattints rá jobb gombbal. Lakói készséggel elárulják, mire vágynak. @L@LAz ókori egyiptomiak különböző méretű és minőségű házakban éltek. További információért kattints @152ide."
        }
    }

    message_game_concept_roads {
        id: 57,

        size [30, 28]
        title {
            text: "Utak",
        }
        content {
            text: "Az utak kezdetben földutak. Ahogy fejlődik a város, lakói saját kezdeményezésre kikövezik őket. A kikövezett utakra @79díszburkolat is helyezhető. @PA jól megtervezett úthálózat nagyban hozzájárul a város hatékony működéséhez. A város szolgáltatásait biztosító @42járókelők könnyebben közlekednek hosszú, egyenes utakon, mint rövid, sok kanyarral és kereszteződéssel tarkított utcákon. @PA város szinte minden épületének útkapcsolatra van szüksége. Kivételt csak a kertek, a szobrok és az erődök jelentenek. A szentélyeknek, falaknak és lakóházaknak nem kell közvetlenül út mellett állniuk, de legfeljebb két mezőre lehetnek tőle, hogy részesüljenek az arra járók szolgáltatásaiból. @PA járókelők csak ott tudnak átkelni az árterület és a szárazföld határán, ahol út vezet át. A part meredek, sáros és veszélyes, de az út biztonságos átkelést biztosít. @PMinden út azonos forgalmat bír el, és a járókelők ugyanazzal a sebességgel haladnak rajtuk, függetlenül attól, hogy ki vannak-e kövezve. @L@LA Királyi út @LA küldetés kezdetén a térképen áthaladó út a Királyi út, amely különleges szerepet tölt be. A kereskedőkaravánok és a bevándorlók ezen érkeznek, a kivándorlók pedig ezen távoznak. A város minden részéből elérhetőnek kell lennie. Ha a város egy részét elszigeteled tőle, az a terület megreked. Az oda tartó szállítók megállnak, amíg a kapcsolat helyre nem áll. Előfordulhat, hogy a királyi építészek eltávolítják azt az építményt, amely elzárja az utat. @PEz nem jelenti azt, hogy minden utcának közvetlenül a Királyi útra kell csatlakoznia. Elég, ha minden épületből gyalogosan elérhető, akár úton, akár szabad terepen keresztül. @PEnnyi rendszerint elegendő a Királyi útról. Az épületek elérésének részletei ritkán fontosak, de néhány kivételes esetben látható akadály nélkül is megszűnhet a kapcsolat. @PAmikor új épületet emelsz, az a város úthálózatán vagy nyílt terepen keresztül megkeresi a Királyi úthoz vezető útvonalat. Többnyire meglévő út mellé építesz, ezért annak kapcsolata számít. Ha azonban az épület nem út mellett áll, először a nyílt terepen át keres kapcsolatot. Később, ha úttal kapcsolod a városhoz, az új út lesz a hozzáférési pontja. Ha ez az út már nem talál gyalogosan járható útvonalat a Királyi úthoz – például mert maga az újonnan csatlakoztatott épület zárja el –, akkor az épület is elveszíti ezt a kapcsolatot. @PA „hozzáférési pontokról” a következő fejezetben olvashatsz. @PVégül fontos tudni, hogy maga a Királyi út fizikai nyomvonala nem különleges; csak a térképre be- és kilépési pontjai számítanak. Az út nyomvonalát szabadon módosíthatod, amíg ezeket a pontokat nem zárod el. @L@LÉpület két út között @LElőfordulhat, hogy egy épület két olyan út mellé kerül, amelyek nincsenek összekötve, vagy csak távol kapcsolódnak egymáshoz. Ez nem jelenti azt, hogy a járókelők mindkét útról használhatják. Minden épületnek csak egy „hozzáférési pontja” lehet, vagyis egyszerre csak egy út aktív. @PPéldául építesz egy raktárat, amelynek déli oldalán út fut. A délről érkező műhelyek, karavánok és piaci beszerzők rendben használják. Ezután utat építesz az északi oldalára is, hogy az északi ipartelep is elérhesse. Hiába van ott az út, az épületnek csak egy hozzáférési pontja lehet, ezért az északi épületek csak akkor használhatják, ha összekötöd az északi és déli utat. @PHa egy épület több út mellett áll, a hozzáférési pontot a nagyobb úthálózat alapján választja ki. Az előző példában, ha a déli út a város fő úthálózatához tartozik, az északi pedig csak egy kisebb ipartelephez vezet, a raktár a déli utat használja. Ha viszont az északi út kapcsolódik a fővárosi hálózathoz, a déli pedig csak egy kisebb telephez, akkor az északi lesz az elsődleges hozzáférési út. @PA kiszámíthatatlan működés elkerülése érdekében ne építs olyan épületet, amely két össze nem kötött utat érint. Inkább kösd össze őket, vagy számolj azzal, hogy csak az egyik út lesz ténylegesen használatban. Figyeld a környéken közlekedő járókelőket, így kiderül, melyik út az épület hozzáférési pontja. @L@LAz ókori Egyiptom útjainak történetéről @153itt olvashatsz."
        }
    }

    message_game_concept_water_crossings {
        id: 58,

        size [30, 28]
        title {
            text: "Vízi átkelők",
        }
        content {
            text: "Kétféle vízi átkelő létezik: a hidak és a kompállomások. A hidak csak keskeny vízfelületeket ívelhetnek át. Hajók nem tudnak áthaladni alattuk, ezért csak olyan helyre építsd őket, ahol nincs hajóforgalom. @PHidat csak egyenes partszakaszra lehet építeni, és a túlpart megfelelő szakaszának is egyenesnek kell lennie. Ha megfelelő helyet választasz, megjelenik a híd zöld körvonala és az építés költsége (a hidak mezőnként kerülnek elszámolásra). Ha a hely nem megfelelő, piros négyzetek láthatók. A hidak nem igényelnek munkaerőt, de útkapcsolatra szükségük van. @PA kompok a kompállomások között közlekednek, és hasonló szerepet töltenek be, mint a hidak, de sokkal rugalmasabbak. Nem akadályozzák más hajók közlekedését, így mindenféle vízi jármű szabadon használhatja a folyót. @PA kompállomásokat a hidakhoz hasonlóan egyenes partszakaszra kell építeni. Ha megfelelő helyet választasz, zöld négyzet jelenik meg. A második kompállomást nem kell pontosan az elsővel szemben elhelyezni; a túlpart bármely egyenes szakaszára kerülhet. A megfelelő helyeket zöld jelölések mutatják. @PMivel a bevándorlók és kivándorlók saját csónakot használnak, a kompállomásokat azonnal igénybe vehetik. A többi lakos szállításához azonban a kompállomásoknak dolgozókra van szükségük. Csak azok a @42járókelők használják a kompot, akiknek konkrét céljuk van, például a szállítók, a piaci beszerzők vagy a fellépési helyükre tartó szórakoztatók. Más járókelők nem utazhatnak vele. @PA bevándorlók szállításához a kompállomásoknak nincs szükségük útkapcsolatra, mert a bevándorlók a mezőkön keresztül is odatalálnak. A többi lakos szállításához viszont már útkapcsolat szükséges. @L@LAz ókori egyiptomiak a @157Nílusnak köszönhetően sokféle hajót használtak emberek és áruk szállítására. Az ókori egyiptomi hajóépítésről @179itt olvashatsz többet."
        }
    }

    message_game_concept_irrigation {
        id: 59,

        size [30, 28]
        title {
            text: "Öntözés",
        }
        content {
            text: "A vízemelők és az öntözőcsatornák a Nílus vizét nagyobb területre juttatják el. Az öntözés növeli a termőföld termékenységét. @PAhhoz, hogy egy földet öntözz, vezess öntözőcsatornát legfeljebb két mező távolságra tőle. Az öntözés hatása nem halmozódik: ha egy csatorna két mezőn belül van, a föld teljes mértékben öntözöttnek számít. @PAz ártéri földek a víz szintjén fekszenek, ezért az öntözőcsatornák közvetlenül a Nílushoz kapcsolhatók. A réti földek azonban magasabban helyezkednek el, ezért öntözésükhöz vízemelő építése szükséges. @PA vízemelők egy szinttel magasabbra emelik a vizet. Építhetők közvetlenül vízpart mellé vagy az ártér szélére. Ha ártér mellé épülnek, a Nílustól a vízemelő elejéig öntözőcsatornát kell vezetni, hogy vízhez jussanak. @PA vízemelő hátuljához csatlakoztatott öntözőcsatorna látja el vízzel a réti földeket. Az öntözőcsatornák minden akadályt kikerülnek, kivéve az utakat. Az utak alatt automatikusan átvezetnek, ahol szükséges. @PA termékenyebb föld nagyobb terméshozamot eredményez. A termékenység azonban nem befolyásolja a termesztési időszak hosszát. @PMég az öntözött földeket is csak művelhető területre lehet építeni. Az öntözés növeli a termékenységet, de nem teszi termővé a terméketlen talajt. @PA @45gazdálkodás fejezet további részleteket tartalmaz. @L@LAz ókori Egyiptomban az öntözési technikák felfedezése jelentősen megnövelte a megművelhető földterületet. Az öntözés történetéről @154itt olvashatsz többet."
        }
    }

    message_building_weaver {
        id: 60,

        size [30, 28]
        title {
            text: "Szövöde",
        }
        content {
            text: "A szövödék lenből lenvásznat készítenek. A len @91lenfarmokon termeszthető, vagy @47kereskedelmi&partnerektől importálható. A szövödéknek útkapcsolatra és munkaerőre van szükségük. Kis mennyiségű lent helyben is tárolnak, így rövidebb ellátási zavarok esetén is folytathatják a termelést. @PA lenvászon fontos termék a városban. Nélkülözhetetlen a balzsamozáshoz, ezért a @66balzsamozóknak folyamatos lenvászonellátásra van szükségük. A lakosok is szeretnek lenvásznat tartani otthonukban ruházkodási célra. @L@LA lenvászon jelentőségéről és a szövők mesterségéről az ókori Egyiptomban @398itt olvashatsz többet."
        }
    }

    message_building_water_supply {
        id: 61,

            size [30, 28]
        title {
            text: "Vízellátó",
        }
        content {
            text: "A vízellátók és vízhordóik biztosítják a városnegyedek számára a tiszta @44ivóvizet. A vízellátóból származó víz az egyik első dolog, amelyet a lakók elvárnak, ha fejleszteni szeretnék @56otthonaikat. @PA vízellátóknak útkapcsolatra és munkaerőre van szükségük, valamint csak füves területre építhetők, ami talajvíz jelenlétét jelzi. Sivatagba nem építhetők. @PHa a vízellátó működéséhez minden feltétel adott, vízhordót küld ki. A vízhordó bejárja a városrészt, és tiszta vizet biztosít azoknak a házaknak, amelyek mellett elhalad. Érdemes időnként ellenőrizni a vízhordókat, hogy minden környék megfelelő ellátást kap-e. A @18víz&nézet megmutatja, mely házak mellett járnak el rendszeresen. A vízhordók @42szabadon&járó járókelők. @PA vízhordók hatékonyabban dolgoznak, ha a vízellátó fejlődött. Ha a környék @56vonzereje elég magas, a dolgozók fejlesztik az épületet, és a vízhordók gyakrabban járják be a környéket. @PCsak a lakóházaknak van szükségük a vízellátó ivóvizére, és az emberek szívesen laknak a közelében (a környék vonzerejéről lásd a @56vonzereje fejezetet). @L@LAz ókori Egyiptom ivóvízellátásának kihívásairól @156itt olvashatsz többet."
        }
    }

    message_building_well {
        id: 62,

        size [30, 28]
        title {
            text: "Kút",
        }
        content {
            text: "A kutak kezdetleges forrásai az @44ivóvíznek. Csak a legszegényebb városrészek lakói elégednek meg a kútvízzel. Ahhoz, hogy a lakóházak fejlettebb épületekké alakuljanak, @61vízellátóból származó vízre van szükségük. @PA kutaknak nincs szükségük útkapcsolatra vagy dolgozókra. Csak füves területre építhetők, ami talajvíz jelenlétét jelzi. Kissé növelik a környék @56vonzerejét. @PA @18Víz&nézet segítségével láthatod, mely területek férnek hozzá kútvízhez. @L@LAz ókori egyiptomi kutakról @156itt olvashatsz többet."
        }
    }

    message_building_dentist {
        id: 63,

        size [30, 28]
        title {
            text: "Fogorvos",
        }
        content {
            text: "A tehetősebb lakosok nagyra értékelik, ha szilárd ételeket fogyaszthatnak, ezért elvárják, hogy a közelben legyen fogorvosi rendelő, amely megőrzi vagy pótolja természetes fogaikat. Egy olyan vidéken, ahol a homok elkerülhetetlenül az élelmiszerbe kerül, a fogorvosoknak mindig akad munkájuk. A fogorvosok növelik a közeli lakóházak @56vonzerejét, de nincs hatásuk a város @53Egészségére. @PA @18Egészség&nézet segítségével láthatod a városodban dolgozó fogorvosokat. @L@LAz ókori Egyiptom fogorvosainak szerepéről @158itt olvashatsz többet."
        }
    }

    message_building_physician {
        id: 64,

        size [30, 28]
        title {
            text: "Orvos",
        }
        content {
            text: "Az orvosok segítenek megőrizni a város jó @53Egészségét. Látogatásaik csökkentik a betegségek kialakulásának kockázatát. @PA lakosok örülnek, ha a közelben van orvosi rendelő, és a @56lakóházak&fejlődése korlátozott nélkülük. @PAz orvosi rendelőknek munkaerőre és útkapcsolatra van szükségük. @PA @26Közegészségügyi&felügyelő felkeresése segít felmérni a város orvosi ellátottságát. @L@LAz egyiptomi gyógyászati gyakorlatokról @160itt olvashatsz többet."
        }
    }

    message_building_apothecary {
        id: 65,

        size [30, 28]
        title {
            text: "Patika",
        }
        content {
            text: "A patikák olyan városi gyógyszertárak, amelyek füvesasszonyokat alkalmaznak. A füvesasszonyok eltávolítják a forgalomból az útjuk során talált @53pestises&lakosokat. A patikák legfontosabb szerepe a @53malária kockázatának csökkentése. @AMűködésükhöz a patikáknak útkapcsolatra és munkaerőre van szükségük. A füvesasszonyok útvonalainak követéséhez használd a @18Egészség&nézetet. Láthatod a város összes füvesasszonyát és patikáját, valamint azt is, hogy az egyes házak mennyire férnek hozzá szolgáltatásaikhoz. @PA további információkért keresd fel a @26Közegészségügyi&felügyelőt. @L@LAz ókori egyiptomi gyógyszerészeti gyakorlatokról @159itt olvashatsz többet."
        }
    }

    message_building_mortuary {
        id: 66,

        size [30, 28]
        title {
            text: "Halottasház",
        }
        content {
            text: "A halottasházak balzsamozói előkészítik az elhunytakat a túlvilági utazásra. @PA halottasházak növelik a város @53Egészségét azáltal, hogy megfelelően gondoskodnak a holtakról. A legtöbb épülethez hasonlóan a halottasházaknak is szükségük van útkapcsolatra és munkaerőre. Emellett megfelelő mennyiségű @60lenvászonra is szükségük van, amelyet a városban gyártanak vagy @47kereskedelmi&partnertől importálnak. A balzsamozók a holttestek becsomagolásához használják a vásznat a balzsamozási folyamat után. @PA lakosok igénylik a halottasházak szolgáltatásait, de nem szeretnek ezek közelében élni. A halottasházak hírhedtek kellemetlen szagukról. @PA halottasházak helyét az @18Egészség&nézet segítségével láthatod. Megfigyelheted a holtakkal foglalkozó balzsamozókat, amint bejárják a városnegyedeket. A @26Közegészségügyi&felügyelő értékes információkkal szolgál a város halottasházi szolgáltatásairól. @L@LA balzsamozás alapvető része volt az ókori egyiptomi túlvilághitnek. Erről az ősi gyakorlatról @161itt olvashatsz többet."
        }
    }

    message_building_shrine_and_temple {
        id: 67,

        size [30, 28]
        title {
            text: "Szentély és templom",
        }
        content {
            text: "Az isteneket nem lehet kiengesztelni szentélyek és templomok nélkül. A helyi istenségek és a város védőistene egyaránt figyelmet követelnek, a lakosok pedig vallási szolgáltatásokat várnak. Az istenek városra gyakorolt hatásáról bővebben lásd a @51vallás fejezetet. Az egyes istenek templomkomplexumainak hatásairól itt olvashatsz: @L@P@350Ozirisz&templomkomplexuma @P@351Ré&templomkomplexuma @P@352Ptah&templomkomplexuma @P@353Széth&templomkomplexuma @P@354Básztet&templomkomplexuma @L@PA szentélyek kis emlékművek, amelyeket egy adott istennek szentelnek. Nincs szükségük közvetlen útkapcsolatra, de két mezőn belül kell lenniük egy úttól, hogy a tűzoltók és építészek szolgáltatásai elérjék őket. Nem igényelnek munkaerőt, és nem indítanak járókelőket, ezért nem biztosítanak vallási hozzáférést. Fő céljuk az istenek kiengesztelése. @PAz emberek számára biztosított istentiszteleti helyek és az istenek további kiengesztelése érdekében építs templomokat. A templomoknak útkapcsolatra van szükségük, és papokat alkalmaznak. Ha egy templom működik, papokat láthatsz, amint vallási szolgáltatásokat visznek a lakosokhoz. A szentélyekhez hasonlóan a templomokat is egy adott istennek szentelik. @G73 @PMind a templomok, mind a szentélyek növelik a környező városrészek @56ingatlan&értékét. A szentélyek és templomok hozzájárulnak a város @35Kultúra&értékéhez is. @L@LA vallás az ókori egyiptomi élet középpontjában állt. Erről az ókori kultúra fontos részéről @399itt olvashatsz többet."
        }
    }

    message_building_scribal_school {
        id: 68,

            size [30, 28]
        title {
            text: "Írnokképző iskola",
        }
        content {
            text: "Az írnokképző iskolák a város tehetősebb fiataljait oktatják. @PAz iskoláknak útkapcsolatra és munkaerőre van szükségük a megfelelő működéshez. Emellett @97papiruszellátásra is szükségük van. Ha egy iskola megfelelően működik, tanárok járják az utcákat, és a diákok otthonában oktatnak. Amikor egy tanár elhagyja az iskolát, hogy felkeresse tanítványait, papirusztekercseket visz magával, hogy a diákok gyakorolhassák a hieroglifák írását. Minden írnokképző iskola kis mennyiségű papiruszt tárolhat helyben. Az órák folytatásához gondoskodj róla, hogy a város papiruszipara megfelelően működjön, vagy importálj elegendő mennyiséget egy @47kereskedelmi&partnertől. @A @27Tanulási&felügyelő tudja, hány írnokképző iskola működik a városban. Az @18Oktatás&nézet megmutatja az összes írnokképző iskolát, valamint azokat a házakat, amelyek hozzáférnek a tanárokhoz. Az írnokképző iskolák a város @35Kultúra&értékéhez is hozzájárulnak. @L@LAz ókori egyiptomiak közül sokan úgy tekintettek az oktatásra, mint a sikeres jövő útjára. Erről az ősi intézményről @163itt olvashatsz többet."
        }
    }

    message_building_sun_temple {
        id: 69,

        size [30, 28]
        title {
            text: "Naptemplom",
        }
        content {
            text: "A naptemplomok különleges tiszteletet adnak a Napkultusznak, amelyet a legtöbb fáraó nagy becsben tart. @PNaptemplom építéséhez @95homokkőre és @94fára, valamint a @363Ácsok&céhe, a @363Kőfaragók&céhe és egy @8Munkatábor szolgálataira van szükség. @AA naptemplom egy homokkő obeliszkkel kezdődik. Az obeliszk építéséhez elegendő homokkövet kell tárolni a város @4Raktáraiban. Ha elegendő kő áll rendelkezésre, elhelyezheted a naptemplomot. Válaszd ki a Vallási épületek: Emlékművek listából a Naptemplomot, majd jelöld ki a helyét. Ha megfelelő helyet választottál, az emlékmű zöld körvonala jelenik meg. Ha a körvonal bármely része piros rombusszal látható, valamilyen tereptárgy megakadályozza az építést. Kattints az obeliszk építésének megkezdéséhez. @PA kő elhelyezése után az ácsok állványzatot építenek az obeliszk köré. Ezután a kőfaragók feldíszítik a homokkő obeliszk oldalait. Amikor az obeliszk elkészül, megkezdik a naptemplom többi részének építését. Először egy előcsarnokot, majd egy kőfalat építenek. A fal elkészülte után a kőfaragók megépítik az elülső templomot. Ezekhez az elemekhez a kőfaragóknak több szekérnyi homokkőre van szükségük, amelyet a parasztok szállítanak. Miközben az elülső templomon, a falon és az előcsarnokon dolgoznak, a kőfaragók díszcsempéket helyeznek el a falak között. @PAmikor az elülső templom elkészül és minden csempe a helyére került, a naptemplom elkészült. @PAz építés állásáról a @369építésvezetőnél érdeklődhetsz. A @373Emlékművek&felügyelőjének meglátogatása szintén hasznos lehet. @L@LA naptemplomok és más emlékművek történetéről @396itt olvashatsz többet."
        }
    }

    message_building_library {
        id: 70,

        size [30, 28]
        title {
            text: "Könyvtár",
        }
        content {
            text: "A művelt polgárok igénylik a könyvtárakhoz való hozzáférést. A könyvtárak növelik az ingatlanok értékét és hozzájárulnak a város @35Kultúra&értékéhez. @Papirusz nélkül a könyvtárak üres polcokkal rendelkező haszontalan épületek lennének. Könyvtár építése előtt elegendő @97papiruszt kell tárolni a @4Raktárakban. A könyvtár felépítése után is szüksége van helyben tárolt papiruszra a megfelelő működéshez. @PA könyvtáraknak útkapcsolatra és munkaerőre is szükségük van. Amikor a könyvtár minden szükséges készlettel rendelkezik, könyvtárost küld a környező közösségbe. Minden alkalommal, amikor egy könyvtáros elhagyja az épületet, papiruszt visz magával, hogy irodalmat terjesszen a lakosság körében. @PA város könyvtárainak számát a @27Tanulási&felügyelőnél követheted nyomon. A könyvtárak pontos helyét az @18Oktatás&nézet segítségével láthatod. A nézet megmutatja a könyvtárakat, és követheted a könyvtárosokat napi feladataik végzése közben. @L@LAz ókori Egyiptom irodalmi hagyományairól és könyvtárairól @164itt olvashatsz többet."
        }
    }

    message_building_booth {
        id: 71,

        size [30, 28]
        title {
            text: "Mutatványos bódé",
        }
        content {
            text: "A mutatványos bódék a legkisebb és legolcsóbb @49szórakozóhelyek, amelyeket építhetsz. Egy bódé egy színpadnak ad helyet, ahol zsonglőrök szórakoztatják a tömeget akrobatikus és hihetetlen mutatványaikkal. @PA bódék különleges útkapcsolatot igényelnek: egy útkereszteződésre, vagy egy „T” alakú elágazásra kell építeni őket. A bódéknak teljes személyzettel és képzett zsonglőrökkel kell rendelkezniük. A személyzet segít a tömeg irányításában és gondoskodik a zsonglőr szükségleteiről előadás közben. A zsonglőrök a @75Zsonglőriskolákban kapnak képzést, és a @72Zenepavilonokban és @73Pavilonokban is felléphetnek. @AA lakóházaknak szórakozási lehetőségre van szükségük a @56fejlődéshez, és a zsonglőrök minden ház számára előnyt biztosítanak, amely mellett elhaladnak. Egy mutatványos bódé jelenléte a környék vonzerejét is növeli. A működő bódék a város @35Kultúra&értékéhez is hozzájárulnak. @AA @28Szórakoztatási&felügyelő felkeresése megmutatja, hány zsonglőr dolgozik a városban. Az @18Szórakozás&nézet megmutatja, hol lépnek fel a zsonglőrök, és követheted őket, ahogy az utcákon járnak. @L@LAz ókori egyiptomiak a zsonglőrködés úttörői közé tartoztak. Erről @169itt olvashatsz többet."
        }
    }

    message_building_bandstand {
        id: 72,

        size [30, 28]
        title {
            text: "Zenepavilon",
        }
        content {
            text: "A zenepavilonok közepes méretű szórakozóhelyek, amelyek két színpaddal rendelkeznek: az egyik a zsonglőröknek, a másik a zenészek előadásainak ad helyet. A zsonglőrök színpada a pavilon egyik sarkában található, a zenekar pedig egy másik sarokban lévő színpadon játszik. @PA zenepavilonokat útkereszteződésre, vagy egy „T” alakú elágazásra kell építeni. Saját személyzetre van szükségük az előadók igényeinek ellátásához, valamint képzett zsonglőrökre és zenészekre. Az előadók a @75Képzőközpontokban kapnak oktatást. @AA lakóházaknak szórakozási lehetőségre van szükségük a @56fejlődéshez, és a zsonglőrök, valamint a zenészek minden háznak előnyt biztosítanak, amely mellett elhaladnak. Egy zenepavilon jelenléte a környék vonzerejét is növeli. A működő zenepavilonok a város @35Kultúra&értékéhez is hozzájárulnak. @AA @28Szórakoztatási&felügyelő felkeresése megmutatja, hány zsonglőr és zenész dolgozik a városban. Az @18Szórakozás&nézet megmutatja, hol dolgoznak ezek az előadók, és követheted őket, ahogy az utcákon járnak. @L@LAz ókori egyiptomiak kiváló zenészek voltak. Többet @170itt olvashatsz róluk. Az ókori egyiptomi zsonglőrködésről @169itt tudhatsz meg többet."
        }
    }

    message_building_pavilion {
        id: 73,

        size [30, 28]
        title {
            text: "Pavilon",
        }
        content {
            text: "A legnagyobb szórakozóhelyek közé tartozó pavilonok három színpaddal rendelkeznek: egy a zsonglőrműsoroknak, egy a zenei előadásoknak és egy a táncbemutatóknak. Egyetlen lakos sem fog panaszkodni, ha pavilon mellett kell élnie. @PA pavilonokat útkereszteződésre, vagy egy „T” alakú elágazásra kell építeni. Saját személyzetre van szükségük az előadók igényeinek ellátásához, valamint képzett zsonglőrökre, zenészekre és táncosokra. Az előadók a @75Képzőközpontokban kapnak oktatást. @AA lakóházaknak szórakozási lehetőségre van szükségük a @56fejlődéshez, és a szórakoztatók minden háznak előnyt biztosítanak, amely mellett elhaladnak. Egy pavilon jelenléte a környék vonzerejét is növeli. A működő pavilonok a város @35Kultúra&értékéhez is hozzájárulnak. @AA @28Szórakoztatási&felügyelő felkeresése megmutatja, hány zsonglőr, zenész és táncos dolgozik a városban. Az @18Szórakozás&nézet megmutatja, hol dolgoznak ezek az előadók, és követheted őket, ahogy az utcákon járnak. @L@LAz ókori egyiptomi tánc legújabb divatjáról @171itt olvashatsz. Zenéjükről @170itt, zsonglőrködési szokásaikról pedig @169itt tudhatsz meg többet."
        }
    }

    message_building_senet_house {
        id: 74,

        size [30, 28]
        title {
            text: "Szenet-ház",
        }
        content {
            text: "A Szenet-ház lehetőséget ad az embereknek, hogy egy kellemes játékot játsszanak a szenettel, amely a túlvilági utazást ábrázoló játék. Habzó korsó sörrel az oldalukon a lakosok egymás társaságában töltik az időt, és barátságos versengésben vesznek részt. @PA dolgozókon és útkapcsolaton kívül a Szenet-háznak @96sörkészletre is szüksége van, hogy kiszolgálhassa vendégeit. @AA @28Szórakoztatási&felügyelőnél megtudhatod, hány Szenet-ház található a városban. Az @18Szórakozás&nézet segítségével láthatod, mely házak férnek hozzá egy Szenet-házhoz. @AAz emberek nem szeretnek túl közel lakni a Szenet-házakhoz (a vonzerőről bővebben kattints @56ide). A vendégek általában hangosak és vidámak – különösen a nagy téttel játszott szenetjátékok vesztesei. @L@LA szenet több volt egyszerű játéknál. Erről @172itt olvashatsz többet."
        }
    }

    message_building_trading_centers {
        id: 75,

        size [30, 28]
        title {
            text: "Képzőközpontok",
        }
        content {
            text: "A zsonglőröknek, táncosoknak és zenészeknek képzőközpontban kell tanulniuk mesterségüket. Minden szakmának saját oktatási helye van: a zsonglőrök a Zsonglőriskolákban tanulják trükkjeiket, a zenészek a Konzervatóriumokban képezik magukat, a táncosok pedig Tánciskolákban gyakorolnak. @PMindegyik épületnek útkapcsolatra és saját személyzetre van szüksége. Miután a szórakoztatók befejezték képzésüket, a hozzájuk legközelebbi, szolgáltatásaikat igénylő szórakozóhelyre indulnak. Útjuk során azok a házak, amelyek mellett elhaladnak, hozzáférést kapnak az általuk nyújtott szórakozáshoz. @PAmikor az előadók megérkeznek a helyszínre, meghatározott számú napig műsort adnak. Bármely szórakozóhelyre jobb egérgombbal kattintva láthatod, mely előadók szórakoztatják a tömeget, és még hány napig élvezhetik szolgáltatásaikat. Minél közelebb van egy képzőközpont a szórakozóhelyhez, annál tovább tart az előadás. Amikor egy műsor véget ér, az előadók hazatérnek. Ha nem képeztek ki új előadókat a helyükre, a szórakozóhely üresen marad, és nem biztosít szórakozást a lakosoknak. @AA lakosok nem bánják, ha Zsonglőriskola közelében élnek. A vidám gyakorlásuk majdnem olyan szórakoztató, mint az előadásaik. Senki sem szeret azonban Tánciskolák vagy Konzervatóriumok közelében lakni. Az előadók minden órában jönnek-mennek, a gyakorló zenészek hangja pedig nem mindig kellemes. @AAz előadók iskoláiktól a fellépési helyszínekig tartó útját az @18Szórakozás&nézet segítségével követheted. @L@LAz egyiptomiak sokféle módot találtak a szórakozásra. Erről @165itt olvashatsz többet."
        }
    }

    message_building_courthouse {
        id: 76,

        size [30, 28]
        title {
            text: "Bíróság",
        }
        content {
            text: "A bíróságok sokoldalú városi épületek. Amellett, hogy csökkentik a városnegyedekben a @36bűnözést, a város vagyonának egy részét is tárolják. A lakosok értékelik a bíróságok nyújtotta biztonságot, és szívesen élnek ezek mellett a tekintélyes épületek mellett. @AA bíróságoknak útkapcsolatra és munkaerőre van szükségük, mielőtt bírákat küldhetnének az utcák járőrözésére. A bíró jelenléte egy környéken csökkenti a bűnözés kialakulásának esélyét. A bírák csak megelőző intézkedésként működnek; ha bűncselekmény történik, nem tudják megakadályozni az elkövetőt ámokfutásában. @AA város @48pénzének egy része a bíróságokon kerül tárolásra. Nem határozhatod meg, hogy mennyi pénzt tároljanak az egyes bíróságokban. A @30Kincstári&felügyelő sokkal alkalmasabb erre a feladatra, és kiszámítja a megfelelő összeget. @L@LA bíróságok mozgalmas helyek voltak az ókori Egyiptomban. Az ókori egyiptomi jogról @183itt olvashatsz többet."
        }
    }

    message_building_palace {
        id: 77,

        size [30, 28]
        title {
            text: "Palota",
        }
        content {
            text: "A város Palotája a hatalom székhelye.  @PA palota értékes erőforrás a városod számára, ezért igyekezz minél hamarabb felépíteni. Városonként csak egy palotát építhetsz. Rangod és a város nagysága alapján Falusi palotát, Városi palotát vagy Nagyvárosi palotát építhetsz. @PEgy városnak szüksége van Palotára az adók beszedéséhez. Polgáraid kételkedni fognak hatalmadban, amíg nem hozol létre erős, központosított jelenlétet. A Palotában az adókulcsot is beállíthatod. Kattints jobb gombbal a Palotára, majd a képernyő tetején lévő görgetőgombokkal módosítsd az adókulcsot. Az adókról további információért kattints @48ide. @PA Palota páncéltermei a város pénzének egy részét tárolják. A jobb gombos kattintáskor megjelenő ablak pontosan megmutatja, mennyit tárol az épület. A pénz városon belüli tárolásáról további információért lásd a @48pénz részt. @PA Palota rövid áttekintést is ad városod állapotáról. Tartsd a kurzort az épület fölött, és megjelenik egy jelentés a város adókulcsáról, értékeléseiről és munkanélküliségi arányáról. @PHa városod szerencsés módon @93aranybányászati területen fekszik, a Palota egy másik fontos feladatot is ellát. Az aranyércet közvetlenül a bányákból a palotába szállítják, ahol pénzzé finomítják és dolgozzák fel. Az így kapott debenek közvetlenül a városi kincstárba kerülnek. Aranyat soha nem szállítanak vagy kereskednek máshol, csak a Palotán keresztül. @PHa a fáraó királyi látogatással tiszteli meg városodat, a Palotában fog megszállni. @PA kormányzat központja városod egyik legszebb és legnagyobb tiszteletnek örvendő épülete. Az emberek szeretnek a közelében élni - egyesek úgy vélik, ez növeli a közösségen belüli tekintélyüket. @PA Palotának útkapcsolatra és munkásokra van szüksége feladatai ellátásához. Emellett hozzáférés kell a talajvízhez is egy uralkodói látogatás esetére. Ezért az épület legalább egy részének füves területre kell épülnie. @L@LTudj meg többet az ókori egyiptomi kormányzatról és bürokráciáról, ha @174ide kattintasz."
        }
    }

    message_building_mansion {
        id: 78,

        size [30, 28]
        title {
            text: "Kúria",
        }
        content {
            text: "Építs egy pompás otthont a városban, hogy megszilárdítsd hatalmadat és tekintélyedet. Kúriád tárolja családod vagyonát, és nem kaphatsz @48fizetést, amíg nem építettél magadnak otthont. A város lakói biztosak akarnak lenni abban, hogy állandó része vagy a közösségnek, mielőtt engednék, hogy fizetést vegyél fel. @P Fizetésedet tapasztalatod alapján állapítják meg. Ha úgy érzed, többet vagy kevesebbet érdemelsz, saját magad is beállíthatod a fizetésed szintjét. Kattints jobb gombbal a Kúriára, és megjelenik egy ablak, amely egy gombon mutatja jelenlegi fizetésedet. Kattints erre a gombra, és megjelenik a Királyság összes rangjának listája a hozzájuk tartozó fizetési szintekkel. Válassz új fizetést a listából, és ennek megfelelően kapod majd a béredet. Légy azonban óvatos: ha többet fizetsz magadnak, mint amennyit érsz, az negatívan hat a @35Királyság&értékelésedre. Személyes fizetésedet a @30Kincstár&felügyelőjénél is beállíthatod. @P Lakóhelyednek útkapcsolatra és talajvízforrásra van szüksége. Ezért a Kúria legalább egy részének füves területre kell épülnie. Mindenki a szomszédod szeretne lenni, így otthonod jelentősen növeli a környék vonzerejét. @P Rangodtól és városod lehetőségeitől függően Személyes kúriát, Családi kúriát vagy a fényűző Dinasztikus kúriát építheted meg. @L@L A fáraók hatalmas otthonokban éltek, amelyek eltörpítették a dolgozó emberek házait. Ha többet szeretnél megtudni ezekről a lenyűgöző lakóhelyekről, kattints @175ide."
        }
    }

    message_building_garden_plaze_statue {
        id: 79,

        size [30, 28]
        title {
            text: "Kert, tér és szobor",
        }
        content {
            text: "A sok élelem és szolgáltatás mind szép és jó, de a polgárok nem fogják igazán szeretni otthonaikat, amíg környezetüket széppé nem teszed. A terek, kertek és szobrok javítják egy környék hangulatát és növelik az ingatlanok értékét. Egyik szépítő építmény sem igényel munkásokat, és mindegyik megépíthető a városi építmények listájának szépítés részénél található megfelelő gombbal. @PA kertek kellemes helyek, ahol az emberek kipihenhetik magukat egy nehéz munkanap után. Minél több területet szánsz kertekre, annál díszesebbé válnak. A kerteknek nincs szükségük útkapcsolatra. @PA szobrok az ókori Egyiptom dicsőségére emlékeztetik polgáraidat. Három különböző méretben készülnek: kicsi, közepes és nagy. Építésükhöz egyszerűen válassz egy méretet, és keress egy megfelelő helyet. Miközben a kurzort egy hely fölött tartod, nyomd meg a billentyűzeten az „R” gombot. A gomb lenyomva tartása közben négyféle szobor közül választhatsz, amelyek forognak. Amikor a kívánt szobor a megfelelő irányba néz, kattints. A szobroknak nincs szükségük útkapcsolatra. @G72 @PA terek díszes @57utak. Csak olyan utakon építhetők, amelyeket a polgárok már kiköveztek. A polgárok akkor kövezik ki az utakat, ha környékük kellően @56vonzóvá válik, a terek pedig ezt a vonzerőt tovább növelik. A terek építése hasonló az utak építéséhez. Kattints a Tér gombra, majd arra a kövezett útra, amelyet burkolólapokkal szeretnél befedni. A terek semmilyen módon nem változtatják meg az út működését vagy kapacitását. Nagyobb szakaszokat is lefedhetsz egyszerre az egér húzásával, de figyelj a költségekre. @L@LA kertek szinte nélkülözhetetlenek voltak az ókori egyiptomiak számára. Kattints @176ide, hogy olvass ezekről a buja környezetekről, és megismerd az egyiptomi közművészetet."
        }
    }

    message_building_tax_collector {
        id: 80,

        size [30, 28]
        title {
            text: "Adószedő",
        }
        content {
            text: "Az adószedők a város utcáit járják, hogy biztosítsák, a lakosok befizetik a rájuk eső részt. @PAz adószedők egy adószedői hivatalból dolgoznak, amelynek útkapcsolatra és munkásokra van szüksége. Emellett a városnak működő @77Palotával kell rendelkeznie, hogy az adószedő elláthassa feladatát. @PA város pénzének egy része minden adószedői hivatalban tárolódik. @PAz adókulcs beállítása kényes feladat lehet. Egyensúlyt kell találnod a városi kincstár szükségletei és a polgárok türelme között. Az emberek nem tűrik sokáig a magas adókat, és nem haboznak elhagyni városodat egy megfizethetőbb hely kedvéért. Ha a lakosság egy része magas adót fizet, míg mások semmit sem fizetnek, a @39Városi&hangulat jelentősen romlik, ami akár @36bűnözéshez is vezethet. Látogasd meg a @30Kincstár&felügyelőjét, és olvasd el a @48pénz részt az adókulcs beállításával kapcsolatos tanácsokért. @L@LAz ókori egyiptomiak adót fizettek a fáraónak, hogy segítsék az állam működésének finanszírozását. Kattints @173ide további információkért az ókori egyiptomi adókról."
        }
    }

    message_building_architect_post {
        id: 81,

            size [30, 28]
        title {
            text: "Építészeti őrhely",
        }
        content {
            text: "A nagy építmények, például a raktárudvarok, bányák, magtárak, templomok és templomkomplexumok hajlamosak az összeomlásra. Az építészek a város utcáit járva kijavítják a szerkezeti hibákat, mielőtt bekövetkezne a katasztrófa. Az építészek az Építészeti őrhelyeken dolgoznak. @G68 @PAz Építészeti őrhelyek működéséhez útkapcsolatra és munkásokra van szükség. @PEgy adott épület összeomlási kockázatát a @18Kockázatok:&Károk&áttekintővel ellenőrizheted. Ha azt látod, hogy egy bizonyos épület vagy épületcsoport nagy összeomlási veszélyben van, érdemes a közelben Építészeti őrhelyet elhelyezni, hogy egy építész biztosíthassa a szolgáltatását. @PAz összeomlás katasztrofális következményekkel járhat. Ha egy @3Magtár vagy @4Raktár&udvar összeomlik, az ott tárolt élelem és áruk elvesznek."
        }
    }

    message_building_whipwright {
        id: 82,

        size [30, 28]
        title {
            text: "Hajóépítő",
        }
        content {
            text: "A hajóépítők kereskedelmi és katonai célokra egyaránt hajókat készítenek. Halászhajókat építenek a @84Halász&kikötőknek, hadihajókat a @356Hadihajó&kikötőknek, valamint szállítóhajókat a @357Szállító&kikötőknek. A hajóépítőket egyenes partszakaszra kell építeni. Akkor tudod, hogy megfelelő helyet választottál, amikor a hajóépítő zöld „szellemképét” látod. @PA hajóépítőt hajózható vízpartra, például a Nílusra vagy tengerpartra építsd. A keskeny öblökben vagy szárazföldi vizek mellett elhelyezett hajóépítők nem tudják eljuttatni hajóikat a rájuk váró kikötőkhöz. Ez teljesen tönkreteheti tengeri törekvéseidet, mivel a hajóépítő újra és újra hajókat készít, amelyeket azonnal elsüllyesztenek, amint kiderül, hogy nem érhetik el célkikötőjüket. @PA hajóépítő működéséhez munkásokra és útkapcsolatra van szükség. Emellett faanyag kell neki szállító- és hadihajók építéséhez. Halászhajók készítéséhez nincs szüksége fára. A hajóépítők közvetlenül a kikötőktől kapják a hajóépítési megrendeléseket. Amint a hajó elkészül, a hajóépítőtől a megfelelő kikötőbe hajózik. Ha nem kell gyorsan sok hajót építened, egy hajóépítő általában elegendő lesz az igényeidhez. @PHa egy hadihajó vagy szállítóhajó megsérül a harcban, küldd a hajóépítőhöz javításra. A súlyosan sérült hajók kapitányaik kezdeményezésére vánszorognak vissza a hajóépítőhöz. A hajóépítő kijavítja a sérüléseket, ha rendelkezik faanyaggal. @PA hajóépítők nem készítik a @58Komp&átkelőhelyekhez használt csónakokat. A révészek biztosítják az utasok szállításához szükséges csónakokat, a bevándorlóknak és kivándorlóknak pedig saját hajóik vannak. @PA hajóépítők nagy zajjal dolgoznak, ezért senki sem szeretne a közelükben élni. @L@LAz ókori egyiptomiak különböző alakú és méretű hajókat építettek. Ha többet szeretnél megtudni erről az ősi iparágról, kattints @179ide."
        }
    }

    message_building_dock {
        id: 83,

            size [30, 28]
        title {
            text: "Kikötő",
        }
        content {
            text: "A város egyes @47kereskedelmi&partnerei vízi úton érkeznek. Nagy kereskedőhajók úsznak le a Níluson, de nem sok hasznát veszed nekik, ha nincs helyük kikötni. Építs kikötőt a partvonalra, ahol ezek a bárkák horgonyozhatnak. Ügyelj rá, hogy a kikötő a Níluson vagy tengerparton legyen, ahol kereskedőhajók közlekednek. A keskeny öbölre vagy szárazföldi vízre épített kikötő nem lesz képes fogadni a kereskedőhajókat. @PA megfelelő működéshez a kikötőnek útkapcsolatra és munkásokra is szüksége van. Miután egy kereskedőhajó kikötött, a kikötő kocsihajtói serényen lerakodják az árukat, és a város @4Raktár&udvaraiba szállítják őket, majd felrakják a város által ennek a partnernek exportált árukat, és visszaviszik a kikötőbe. Érdemes raktárudvart építeni a kikötő közelében, hogy lerövidítsd a kocsihajtók útját. @PA kikötők negatívan hatnak a környék @56vonzerejére. @L@LAz ókori egyiptomi kereskedelemről további információért kattints @177ide."
        }
    }

    message_building_fishing_wharf {
        id: 84,

            size [30, 28]
        title {
            text: "Halászkikötő",
        }
        content {
            text: "Ha időnként halakat látsz kiugrani egy vízfelületből, a halászok kifoghatják őket élelemként. A halászathoz a városnak egy vagy több halászhajóra van szüksége. @PA halászhajók a halászkikötőkben horgonyoznak. A halászkikötőket egyenes partszakaszra kell építeni, és az építmény felének a víz fölé kell nyúlnia, hogy a hajók hozzáférhessenek. Győződj meg róla, hogy a halászhajó hajózni tud a halászkikötő körüli vizeken. Ha a halászkikötőt keskeny öbölbe helyezed, a halászhajók nem tudják elérni. Ez teljesen tönkreteheti tengeri törekvéseidet, mivel a hajóépítők újra és újra halászhajókat építenek, amelyeket azonnal elsüllyesztenek, amikor nem érik el célkikötőjüket. @PHa a városban működő @82Hajóépítő található, egy halászkikötő megépítése jelzi a hajóépítőknek, hogy kezdjék meg egy halászhajó építését. A hajóépítőnek nincs szüksége nyersanyagra halászhajó készítéséhez. @PA halállomány korlátozott, de teljesen nem meríthető ki. Egy nagy lakosság bajba kerül, ha kizárólag halból próbál megélni. @PA halászkikötők büdös helyek, és @56nemkívánatos szomszédságot jelentenek. @L@LKattints @186ide, hogy többet tudj meg az ókori egyiptomi halászatról."
        }
    }

    message_building_defensive_structures {
        id: 85,

        size [30, 28]
        title {
            text: "Védelmi építmények",
        }
        content {
            text: "A @37hadsereg és a @356haditengerészet védi a várost, miután az ellenség áttörte a határait. Védelmi építmények építésével megakadályozhatod, hogy az ellenség egyáltalán eljusson a város belsejébe. @L@LFalak @LA legalapvetőbb védelmi építmény a fal. Falak építéséhez válaszd ki őket a Katonai építmények: Védelmi építmények listából. Az egérrel kattintva és húzva egyszerre nagy falszakaszokat építhetsz, ugyanúgy, ahogy az utakat. @PAz egyrétegű falak csak rövid időre lassítják az ellenséget. A város legjobb védelme érdekében építs több réteg vastagságú falakat. A vastag falakon az ellenséges katonáknak sokkal tovább tart áttörniük. @PA falak a rendelkezésre álló természetes anyagokból épülnek, ezért nem kell követ bányászni vagy importálni hozzájuk. Ennek ellenére drága az építésük, ezért gondold át alaposan, mekkora területet szeretnél körülkeríteni. @PA falaknak nincs szükségük útkapcsolatra, és nemkívánatos szomszédságot jelentenek. @L@LTornyok @LÉpíts tornyokat, hogy némi támadóerőt adj védelmi falaidhoz. A tornyokat a város @88Toborzója által kiképzett őrök működtetik, akik lándzsákat hajítanak minden olyan ellenségre, amely elég bátor vagy vakmerő ahhoz, hogy hatótávolságukba kerüljön. @PHa a fal elég széles ahhoz, hogy járni lehessen rajta, a tornyok őrszemeket is küldenek a fal hosszának járőrözésére, akik nyilakkal árasztják el a közeledő ellenséget. @PTornyokat csak legalább kétrétegű falakba lehet építeni. Emellett útkapcsolatra, alkalmazottakra és egy toborzóiroda őrszemeire is szükségük van. Ne építsd olyan vastagra a falakat, hogy a toronyőrök ne tudjanak átlőni rajtuk! @L@LKapuépületek @PA bármennyire is megnyugtató lenne, városodat nem kerítheted teljesen körbe falakkal. Ahhoz, hogy bevándorlók és kereskedőkaravánok bejuthassanak, kapuépületekre van szükséged. @PA kapuépületeket a főbb bekötőutak és a városfalak találkozásánál építsd. Miközben a kurzort a kívánt hely fölött tartod, nyomd meg az „R” gombot a kapuépület irányának megváltoztatásához. Elhelyezés után a kapuépületek automatikusan csatlakoznak a szomszédos falakhoz. Ha támadás fenyeget, az őrök bezárják a kapukat, hogy távol tartsák az ellenséget. @PAz úttorlaszokhoz hasonlóan a kapuépületek szabad átjárást biztosítanak a célállomás felé tartó járókelőknek, de visszafordítják a céltalanul kóborlókat (a járókelőkről további információért kattints @42ide). @PA háborúról további információért lásd a @52háború részt. @L@LAz ókori Egyiptom városai jól védettek voltak. Kattints @182ide, hogy többet tudj meg."
        }
    }

    message_building_police_station {
        id: 86,

        size [30, 28]
        title {
            text: "Rendőrőrs",
        }
        content {
            text: "A rendőrök járőröznek a környékeken, és kordában tartják a bűnözést. @PA rendőrök rendőrőrsökön dolgoznak, amelyekhez útkapcsolatra és munkásokra is szükség van. A rendőrőrs tetején zászló lobog, amikor működésben van. @AEgy rendőr jelenléte csökkenti annak esélyét, hogy bűnözés alakuljon ki az adott környéken. Ha megelőző szerepe nem jár sikerrel, a rendőr aktívan fellép a bűnözés ellen. Ha tolvajt talál az utcán, a rendőr lefogja a hálátlant, és megakadályozza aljas tettének végrehajtásában. A rendőrök az egyik legjobb fegyvered a @477sírrablók ellen is. @PA rendőrök más veszélyekkel, például idegen támadásokkal és vadállatok támadásaival szemben is megteszik, amit tudnak. Egyetlen rendőr azonban hatástalan egy állatfalkával vagy idegen sereggel szemben. A rendőr életét adja a harcban, de valószínűleg nem tudja legyőzni az ellenfelet. Az egyetlen esélyük ezekkel a hatalmas ellenfelekkel szemben az, ha együtt tudnak működni. Ennek ellenére az ellenséges hadsereg legyőzése a katonaság feladata, és a vadállatfalkák ellen is a hadsereg bizonyul a leghatékonyabbnak. @G55 @PHa meg szeretnéd látni, mely környékekből kerülnek ki legnagyobb eséllyel bűnözők, használd a @18Kockázatok&áttekintőt. A Kockázatok áttekintő segíthet megtervezni a rendőrőrsök elhelyezését. @PBár egyetlen polgár sem szeretne olyan környéken élni, ahol nincs rendőri járőrözés, senki sem akar közvetlenül a rendőrőrs mellett lakni sem. A rendőrök a nap minden szakában jönnek-mennek, és gyakran kétes alakokat kísérnek. @L@LJogod van többet megtudni az ókori egyiptomi jogról, ha @183ide kattintasz."
        }
    }

    message_company_orders {
        id: 87,

        size [30, 28]
        title {
            text: "Egységparancsok",
        }
        content {
            text: "Egy @37egység kihelyezéséhez a harcmezőre, vagy egyszerűen új helyre vezényléséhez kattints rá, majd kattints egy új helyszínre. Az egység zászlaja megjelenik az új helyen, és az egység odavonul, feltéve, hogy a katonák el tudnak jutni oda. Ne feledd, hogy az ártér és a szárazföld közötti meredek, sáros partfal járhatatlan, kivéve ott, ahol út köti össze a két területet. @PEgy egységnek a következő parancsokat adhatod: @L@LTartsd a helyet szoros alakzatban @LSzoros alakzatban a katonák a lehető legközelebb állnak egymáshoz. Mivel parancsuk a hely megtartása, nem hagyják el pozíciójukat az ellenség megtámadására. Azonban minden közelükbe kerülő ellenséget megtámadnak. A szoros alakzat csökkenti az általuk védhető területet, és könnyebb célponttá teszi őket az ellenséges íjászok számára. Váll a váll mellett állva nagyobb védelmi erőt biztosít közelharcban. @L@LTartsd a helyet laza alakzatban @LEzt a parancsot csak gyalogosoknak és íjászoknak adhatod ki, harci szekereknek nem. Laza alakzatban a katonák szétszóródnak, hogy nagyobb területet fedjenek le, miközben megtartják helyüket. Támadnak, ha egy ellenség hatótávolságba kerül. Ez az alakzat kevésbé sebezhetővé teszi a gyalogosokat és íjászokat az ellenséges nyilakkal szemben, de kevés védelmet nyújt az ellenséges gyalogsági támadások ellen, mivel a sorban álló katonák lényegében csak saját magukat tudják védeni. @L@LKözeli ellenségek megtámadása @LEzzel a paranccsal az egység megtámadja a közvetlen közelében lévő ellenségeket. A támadás addig folytatódik, amíg az ellenséget le nem győzik vagy vissza nem vonul, illetve amíg más parancsot nem adsz... vagy amíg saját legyőzött egységed morálja össze nem omlik, és embereid vissza nem térnek erődödbe. @L@LTakarítás @LHa ezt a parancsot kapják, a katonák nagy területen keresnek ellenségeket, és megtámadják őket. A takarítási parancs alatt álló egységek a legagresszívebbek, és teljesen felbontják alakzatukat, hogy félelem nélkül harcoljanak az ellenféllel. Ez a vakmerőség azonban csökkenti védekezőképességüket, ezért ezt a parancsot leginkább akkor érdemes használni, amikor a város serege túlerőben van. @L@LRoham @LA rohamparancsot csak harci szekereknek adhatod ki. Az ellenséges sorok megrohamozása felbomlasztja alakzatukat, így sebezhetőbbé teszi őket a támadással szemben. Roham esetén a harci szekerek lovai teljes erővel vágtatnak, és nagy távolságon át maximális sebességgel húzzák a szekereket. Végül a lovak elfáradnak, a szekerek lelassulnak és pihenniük kell, ezért ezt a parancsot csak megfontoltan használd. @L@LVisszatérés az erődbe @LKattints a Visszatérés az erődbe parancsra, amikor katonáid elvégezték feladatukat és legyőzték az ellenséget. Az erődben kipihenhetik magukat a következő csatáig. Ha alacsony a moráljuk, maguktól is visszatérnek az erődbe. @L@LA fenti parancsokon kívül közvetlenül is támadásra utasíthatod az egységeket: válaszd ki őket, majd kattints egy ellenségre. Az egység haláláig üldözni fogja a kijelölt ellenséget, hacsak nem adsz másik parancsot. @L@LAz ókori egyiptomi hadviselésről további információért kattints @184ide."
        }
    }

    message_building_recruiter_academy {
        id: 88,

        size [30, 28]
        title {
            text: "Toborzó és akadémia",
        }
        content {
            text: "A városukért harcolni kész férfiak a toborzóirodába mennek, hogy besorozzák őket. További kiképzésért az akadémiára kerülhetnek. Mind a toborzóirodának, mind az akadémiának útkapcsolatra és munkásokra van szüksége. @PA toborzó feladata egyszerű: besorozza a férfiakat a város @37hadseregébe, és ellátja őket a szükséges különleges fegyverekkel. A leendő gyalogosok felszereléséhez a toborzónak fegyverkészletre van szüksége, amelyet egy @47kereskedelmi&partnertől importálhat, vagy egy @98Fegyverkovács készíthet el. Harci szekerekhez a toborzónak egy @98Harci&szekérkészítőtől vagy kereskedelmi partnertől származó szekerekre van szüksége. Az íjászoknak készülő férfiak saját maguk biztosítják íjaikat és nyilaikat. A toborzó szükség esetén a város falain és @85tornyaiban őrszolgálatra is beosztja a besorozottakat. @PAz új katonák dicsőségről álmodva és szükséges fegyverzettel hagyják el a toborzót, de kevés mással rendelkeznek. Az akadémia a tapasztalatlan gyalogosokat, íjászokat és harci szekereket a hadviselés kifinomultabb művészetére tanítja. Az őrszemek munka közben sajátítják el tudásukat, és nem járnak akadémiára. Tanulmányaik befejezése után a katonák egységük erődjébe vonulnak. @PHa nincs akadémia a városban, a katonák közvetlenül a toborzóirodából az egység erődjébe mennek. @G57 @PA katonasághoz kapcsolódó durva alakok miatt a toborzó és az akadémia negatívan hat a @56vonzóerőre. @L@LAz ókori egyiptomi háborúkról többet tudhatsz meg, ha @184ide kattintasz."
        }
    }

    message_building_grain_farm {
        id: 89,

        size [30, 28]
        title {
            text: "Gabonaföld",
        }
        content {
            text: "A gabona nem különbözik a városban fogyasztott többi élelemtől, de a gabonaföldek melléktermékként nyersanyagot is termelnek: szalmát. A szalma takarmányként szolgál a @360Marhatenyésztő&telepek állatai számára, és az egyik nyersanyag, amely a @364téglagyártáshoz szükséges. A szalmát (a vadhússal együtt) az állatok etetésére is használják az @479Állatkertben. @PA szalmát a gabonával egy időben takarítják be. Egy szállító közvetlenül a marhatelepekre, téglakészítőkhöz, állatkertekbe vagy @4Raktár&udvarokba viszi, miközben munkatársa a gabonatermést a célként kijelölt magtárba vagy raktárudvarba szállítja. @PA gabonaföldek nemkívánatos szomszédságot jelentenek, és csökkentik a közeli lakóházak értékét. @PEgyéb hasznos témák: @45Élelem&és&mezőgazdaság, @2Bazárok és @3Magtárak. @L@LKattints @185ide, hogy olvass az ókori egyiptomi gabonatermesztésről."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,

        size [30, 28]
        title {
            text: "Gyümölcs- és zöldségfarmok",
        }
        content {
            text: "A gyümölcsök és zöldségek éppúgy képesek egészséges életet biztosítani, mint bármely más élelmiszer, és kellemes változatosságot nyújtanak minden étrendben. Egyiptom különböző területei különböző növények termesztésére alkalmasak. A polgáraid számára elérhető termények között lehet gránátalma, füge, csicseriborsó és saláta. @PA gyümölcs- és zöldségfarmok ugyanúgy működnek, mint minden más élelmiszerfarm. Nem termelnek más nyersanyagot, csak élelmet. A farmok megtervezésével és a legjobb eredmény elérésével kapcsolatban lásd a @45mezőgazdaság részt. @PMindkét farmtípusnak munkásokra és útkapcsolatra van szüksége a termeléshez. Az ártérre épült farmok esetében a munkát a @8Munkatáborok biztosítják, ezért ügyelj rá, hogy egy vagy több munkatábort létesíts a farmok közelében. @L@LAz egyiptomiak sokféle ételt fogyasztottak, és ízletes konyhát élveztek. Az egyiptomi étrendről további információért kattints @187ide."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,

        size [30, 28]
        title {
            text: "Árpa-, len- és hennanövény-farmok",
        }
        content {
            text: "Az árpa-, len- és hennanövény-farmok kissé eltérnek a @89gabonaföldektől, @90gyümölcs- és @90zöldség&farmoktól. Ezek a farmok nem élelmet termelnek, hanem értékes termékekké feldolgozott nyersanyagokat. Az árpát betakarítják, majd @96sört készítenek belőle, a lent @60vászonná szövik, a hennát pedig összezúzzák és folyadékkal keverve @470festéket készítenek belőle. @PAz árpa-, len- és hennanövény-farmokat azonban ugyanúgy építik és működtetik, mint a többi farmot. Az ártéren bárhol elhelyezhetők. Az ártéren kívül termékeny réteken kell elhelyezni őket, amelyeket sárga növénycsomókról ismerhetsz fel. Tudni fogod, hogy megfelelő helyet választottál, amikor az építés előtt a farm zöld „szellemképét” látod. A farmoknak út mellett kell lenniük, és munkásokra van szükségük. Az ártéri farmok nem biztosítanak maguknak közvetlenül munkásokat, hanem a @8Munkatáborok parasztjaira támaszkodnak. Farmjaid megtervezése előtt olvasd el a @45mezőgazdaság részt. @PAmikor az árpát, lent és hennát betakarítják, a terményeket a legközelebbi feldolgozóüzembe szállítják (árpa esetén a sörfőzdébe, len esetén a szövőműhelybe, henna esetén a festékkészítőhöz). A feldolgozókban az árpából, lenből vagy hennából késztermék lesz, amelyet a polgáraid kapnak meg, a @363Kézművesek&céhe használ fel, vagy @47kereskedelemben értékesíthetsz haszonnal. Ha a feldolgozóknál nincs hely, vagy a városban egyáltalán nincsenek ilyenek, az árpát, lent és hennát egy @4Raktár&udvarba szállítják. @PMindhárom farmtípus negatívan hat a közeli területek @56vonzerejére. @L@LAz árpatermesztés történetéről további információért kattints @185ide. Az ókori egyiptomi lenbetakarításról a @189ide kattintva olvashatsz. A hennanövényekről további információért kattints @469ide."
        }
    }

    message_building_clay_pit {
        id: 92,

        size [30, 28]
        title {
            text: "Agyagbánya",
        }
        content {
            text: "Az agyagbányák agyagot termelnek, amelyből @1kerámiát lehet készíteni, @89szalmával együtt @364téglát lehet gyártani belőle, vagy egy @363Kézművesek&céhe számára szállítható, ahol vakolattá alakítják. @PAz agyagbányáknak útkapcsolatra és munkásokra van szükségük. Csak víz közelében helyezhetők el. @PMiután az agyagbánya dolgozói elegendő agyagot ástak ki egy kocsi megtöltéséhez, a bánya szállítót küld, hogy eljuttassa az árut a szükséges helyre. A szállító mindig olyan téglagyárnak, fazekasnak vagy kézművescéhnél próbálja leadni az agyagot, amelynek szüksége van rá, és a legközelebbi épületet részesíti előnyben. Ha egyik ilyen iparágnak sincs szüksége a nyersanyagra, a szállító a legközelebbi, azt befogadni képes @4Raktár&udvarba viszi az agyagot. Ha senki sem tudja átvenni az agyagot, a szállítás várakozik, amíg hely nem szabadul fel. @PAz agyagbányák nyirkos, csúnya földbe vájt gödrök, ezért igényes polgáraid nem akarnak ilyen látványos létesítmény közelében élni. @L@LAz ókori egyiptomiak kiválóan hasznosították a Nílus éves áradásai után visszamaradó gazdag agyag- és iszaplelőhelyeket. Kattints @190ide, hogy többet tudj meg erről az értékes nyersanyagról."
        }
    }

    message_building_gold_copper_mine {
        id: 93,

        size [30, 28]
        title {
            text: "Arany- és rézbányák",
        }
        content {
            text: "Az arany és a réz értékes fémek. Egy város, amelynek területén fémérc található, igazán szerencsés. Ha fényes, fémes foltokkal tarkított sziklákat látsz, kattints a vezérlőpult Ipari építmények gombjára, majd válaszd a Nyersanyagok lehetőséget, hogy megtudd, felderítőid találtak-e arany- vagy rézércet – esetleg mindkettőt. @PAz arany ritka és értékes nyersanyag, ezért mindig ki kell bányászni, amikor lehetőséged van rá. Az arany @48pénz, és az aranybányák lehetőséget adnak a városnak, hogy saját maga állítsa elő. Más árukkal ellentétben az aranyat soha nem szállítják a @4Raktár&udvarokba. Az arany csak közvetlenül a @77Palotába kerülhet, ahol debenekké alakítják, majd a város kincstárához adják. @G54 @L@LRéz @LA réz majdnem olyan értékes, mint az arany, bár hagyományosabb módon használják fel. A réz egyike azon kevés nyersanyagoknak, amelyeket jelentős haszonnal exportálhatsz. @PNyugtalan időkben a réz rendkívül értékes alapanyag a @98fegyverek készítéséhez, amelyek igen magas árat érhetnek el. Gyakran saját városodnak is szüksége lesz fegyverekre a gyalogság felszereléséhez. A háborúról a @52ide kattintva olvashatsz. @L@LA fémbányákat olyan sziklás felszínek mellé kell építeni, ahol fémes rögök találhatók. Mindkét bányatípusnak útkapcsolatra és munkásokra van szüksége, és a város számára a legkevésbé kívánatos szomszédok közé tartoznak. @L@LAz ókori egyiptomiak nagyra értékelték az aranyat, és nehéz eljárásokkal nyerték ki a földből. Kattints @191ide, hogy többet tudj meg az aranyról és ókori egyiptomi felhasználásáról."
        }
    }

    message_building_woodcutter_and_reed_gatherer {
        id: 94,

        size [30, 28]
        title { text: "Favágó és nádvágó" }
        content {
            text: "A favágók és nádvágók rendelkezésre álló nyersanyagokat gyűjtenek be, amelyeket más iparágak használnak fel. A fának sokféle felhasználása van. Az ácsmesterek fát igényelnek rámpák vagy állványzatok építéséhez az emlékművekhez, a harci szekérkészítők fából készítik halálos járműveiket, a hajóépítők pedig hadihajókat és szállítóhajókat készítenek belőle. A nádat @97papirusz gyártására használják. @PA favágókat bárhol elhelyezheted, de ideális esetben erdők közelében legyenek, hogy csökkentsd az ingázással töltött időt. A favágóknak útkapcsolatra és helyi munkaerőre is szükségük van. Amint az épület teljesen működőképes, a favágók az erdőbe indulnak, és megkezdik a fák kivágását. @G58 @PA nádvágók nagyon hasonlóan működnek a favágókhoz. A nádvágókat érdemes nádas közelében elhelyezni, bár bárhol felépíthetők. A nádasokat sötétzöld színük, valamint világosabb zöld és sárga növénycsomóik alapján ismerheted fel. A favágókhoz hasonlóan a nádvágóknak is útkapcsolatra és munkásokra van szükségük a működéshez. Amint mindenük megvan, a nádvágók a mocsarakba indulnak. @PLégy óvatos a favágók és nádvágók megtervezésekor. A fák és a nád fokozatosan újranőnek, de mindkettőt túl lehet termelni. Ha túl sok favágót vagy nádvágót építesz, fennáll a veszélye, hogy kimeríted a készletet. Betakarító iparágaid leállnak, amíg a fák és a nád újra nem nőnek. @PA fa Egyiptom egyik legértékesebb nyersanyaga. Próbáld meg nem erdőirtással felszabadítani a területet – a város jelentős bevételi forrást veszíthet, ha így teszel. A mocsarakat nem lehet eltüntetni, és egyes gyógyítók kapcsolatba hozzák őket a maláriával. @L@LKattints @192ide, hogy többet tudj meg a fa jelentőségéről az ókori Egyiptomban. Kattints @188ide, hogy megismerd a nád sokféle felhasználását."
        }
    }

    message_building_stone_quarries {
        id: 95,

        size [30, 28]
        title {
            text: "Kőbányák",
        }
        content {
            text: "A kőfejtők nagy kőtömböket vágnak ki négy különböző bányatípusból: @L@PSima kőbánya @PMészkőbánya @PGránitbánya @PHomokkőbánya @L@LHa a város területén kiterjedt sziklás felszínek találhatók, valószínűleg kőbányákat építhetsz a kő kitermelésére. Egyes területeken azonban a kő nem építési minőségű, vagy túl kevés van belőle ahhoz, hogy ipart lehessen rá alapozni. Ilyen helyeken a kő csak akadály, mert nem lehet eltávolítani, bejárni vagy építeni rá. Kattints az Ipari építmények gombra, és ellenőrizd az elérhető nyersanyagok listáját. Ez a lista megmutatja, hogy milyen típusú követ lehet kitermelni a területen, ha egyáltalán van ilyen. @PA kőbányákat sziklás felszínek mellé kell építeni. Ha megfelelő helyet választasz, megjelenik a lerakni kívánt kőbánya zöld szellemképe. Ellenkező esetben piros blokkot látsz. @PA követ nem lehet más termékké feldolgozni. A kő azonban az emlékművek alapanyaga, és még a kisebb emlékművek elkészítéséhez is jelentős mennyiségű kőre van szükség. @PA sziklás felszínek oldalába vájt kőbányák hajlamosak az összeomlásra. Ügyelj rá, hogy építs egy @81Építészeti&őrhelyet a kőbányák közelében a katasztrófák megelőzésére. @PA kőbányák működéséhez munkásokra és útkapcsolatra van szükség. A folyamatos kőfejtés zajai miatt a kőbányák nemkívánatos szomszédságot jelentenek. @L@LAz ókori Egyiptomban a kőfejtés rendkívül időigényes feladat volt. További információért kattints @193ide."
        }
    }

    message_building_brewery {
        id: 96,

        size [30, 28]
        title {
            text: "Sörfőzde",
        }
        content {
            text: "A sörfőzés megkezdéséhez a sörfőzdének útkapcsolatra, munkásokra és árpaellátásra van szüksége. A szükséges árpát a @91Árpa&farmok termelik, vagy importálható egy @47kereskedelmi&partnertől. Egy árpafarm általában két sörfőzde ellátásához elegendő árpát tud biztosítani. A sörfőzdék bizonyos mennyiségű árpát a helyszínen is tárolhatnak, hogy a betakarítások között is működhessenek. @PAmint a sörfőzők minden szükséges készlettel rendelkeznek, sört készítenek. Láthatod, hogy egy sörfőző keményen dolgozik, ha őt és segédeit a sörfőzdében látod. A sör elkészülte után a szállítók először egy @74Szenet&házba próbálják vinni. Ha egyik Szenetház sem igényli a sört, a szállítók egy @4Raktár&udvarba viszik, ahol a @2Bazár&vásárlói felvehetik, hogy szétosszák a polgárok között, vagy @47kereskedelemben értékesítsék jó haszonért. A sör egyike azoknak a termékeknek, amelyekre a polgároknak szükségük van, mielőtt otthonaikat @56vonzóbb&lakóhelyekké fejleszthetik. @PA sört a @51nagy&ünnepségeken is felszolgálják. @L@LAz ókori egyiptomi sörről további információért kattints @194ide."
        }
    }

    message_building_papyrus_maker {
        id: 97,

        size [30, 28]
        title {
            text: "Papiruszkészítő",
        }
        content {
            text: "A papiruszkészítőnek munkásokra, útkapcsolatra és @94nádból származó készletre van szüksége, amelyet egy nádvágó vagy egy @47kereskedelmi&partner biztosít. A papiruszkészítők bizonyos mennyiségű nádat a helyszínen is tárolhatnak, hogy a szállítások között is dolgozhassanak. @PAmikor egy kocsirakomány papirusz elkészül, egy szállító elviszi egy olyan @68Írnok&iskolába vagy @70Könyvtárba, amelynek szüksége van rá. Ha egyik oktatási épületnek sincs szüksége papiruszra, a szállító a készletet a @4Raktár&udvarba viszi, ahol @47kereskedelemben értékesíthető haszonnal. @G69 @PA polgárok nem szeretnek papiruszkészítő közelében élni. A folyamatos ütögetés fejfájást okoz nekik. @L@LAz ókori egyiptomi papiruszkészítésről további információért kattints @195ide."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,

        size [30, 28]
        title {
            text: "Fegyverkovács és harci szekérkészítő",
        }
        content {
            text: "A fegyverkovácsok és harci szekérkészítők olyan hadi felszereléseket gyártanak, amelyekre bizonyos katonai egységeknek szükségük van. @PA fegyverkovács egy @93Rézbányából származó vagy egy @47kereskedelmi&partnertől importált rézből készít fegyvereket. Az elkészült fegyvereket egy @88Toborzóhoz szállítják, aki a @37gyalogos&egységek felszerelésére használja őket, vagy egy @45Raktár&udvarba kerülnek, ha a toborzónak már elegendő készlete van, illetve ha a városban nincs működő toborzó. @PA harci szekérkészítő egy @94Favágótól vagy @47kereskedelmi&partnertől származó fából készít pompás harci szekereket. Az elkészült szekereket a toborzónak küldi, hogy felszerelje velük a @37harci&szekérvezetőket. Ha a toborzónak már van néhány szekere a készletében, vagy ha a városban nincs működő toborzó, a szekereket egy Raktárudvarba szállítják. @PMind a fegyverkovácsoknak, mind a harci szekérkészítőknek útkapcsolatra és munkásokra van szükségük. Mindketten @56nemkívánatos szomszédságot jelentenek. @L@LAz ókori egyiptomi fegyverekről többet tudhatsz meg, ha @196ide kattintasz."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,

        size [30, 28]
        title {
            text: "Ötvös és luxuscikkek",
        }
        content {
            text: "Megfelelő @361drágakő-készlettel az ötvösök finom ékszereket, egy luxuscikket készítenek. Drágaköveket bányászhatsz, vagy importálhatsz egy @47kereskedelmi&partnertől. @PAz ötvösök működéséhez útkapcsolatra és munkásokra van szükség. Negatívan hatnak a @56vonzóerőre. @PAz ékszer nem túl jövedelmező exportcikk. Az importált luxuscikkek árának nagy részét nem az alapanyag, hanem a szállítás költsége adja. Ezért bár a luxuscikkek más városokból történő behozatala jelentős kiadást jelenthet a kincstáradnak, az ékszerexportért nem kapsz hasonlóan magas árat. @PAz ékszer csak egyike azoknak a luxuscikkeknek, amelyekre a polgárok vágynak. A leggazdagabb polgárok egy második, importált luxuscikket is igényelnek. @L@LAz ókori Egyiptom híres volt pompás @382ékszereiről. Az ókori egyiptomi további luxuscikkekről a @197ide kattintva olvashatsz."
        }
    }

    message_population_milestone_100 {
        id: 100,

        size [30, 20]
        title { text: "Népességi mérföldkő" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "100 ember költözött a faludba." }
    }

    message_population_milestone_500 {
        id: 101,

        size [30, 20]
        title { text: "Népességi mérföldkő" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "Virágzó településed már ötszáz lakosnak ad otthont." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,

        size [30, 20]
        title { text: "Népességi mérföldkő" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "Városod immár ezer ember otthona." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@17" }
        content { text: "Kétezer lakosával városod egyre jelentősebbé válik." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@17" }
        content { text: "Városod népessége története során először érte el a háromezret." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@18" }
        content { text: "Városod már tekintélyes méretű: ötezer ember él benne." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@18" }
        content { text: "Tízezres népességével városod Egyiptom legjelentősebbjei közé emelkedett." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@18" }
        content { text: "Kevés város vetekedhet a tiéddel, amely már tizenötezer lakost számlál." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@19" }
        content { text: "Más kormányzók és nomarkhoszok ámulnak, hogy városod húszezer lakosnak ad otthont!"
        }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,

        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Népességi mérföldkő" }
        video { text: "@19" }
        content { text: "Az egykori maroknyi telepes sem hitte volna, hogy városod egy nap huszonötezer lakosú lesz!" }
    }

    message_the_control_panel {
        id: 110,

        size [30, 20]
        title { text: "Vezérlőpult" }
        content {
            text: "Ez a panel biztosít hozzáférést minden eszközhöz, amelyre városod építéséhez és irányításához szükséged van. A legjobb módja a megismerésének, ha rákattintasz a különféle gombokra – csak bátran, nem tehetsz kárt semmiben! Ha az Egérsúgó be van kapcsolva (a menüsor „Súgó” menüjében), vidd a kurzort bármely elem fölé egy rövid leírásért. A játék minden funkciójának részletes ismertetését a menüsor „Súgó” menüpontjában találod."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,

        size [30, 20]
        urgent: 1,
            title { text: "Tűz a városban" }
        content {
            text: "Lángok pusztítanak a város egyes részein. Kattints a „Fedvények: Kockázatok” nézetre, hogy lásd, hol csaphat fel legközelebb a tűz, és építs tűzoltóságokat a veszélyeztetett épületek közelébe."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1

        size [30, 20]
        urgent: 1
        title { text: "Összeomlott épület" }
        content {
            text: "Ha az építészek nem végzik el a szükséges karbantartást, városod egyes nagyobb épületei összeomlanak. Kattints a „Fedvények: Kockázatok” nézetre, hogy lásd, mely épületek vannak veszélyben, és építs a közelükbe építészeti hivatalt."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,

        size [30, 20]
        title { text: "Hajó zátonyra futott" }
        content { text: "Néhány tapasztalatlan kapitány csak akkor ismeri meg az ártéri síkságokat, amikor hajója zátonyra fut." }
    }

    message_out_of_money {
        id: 115,

        size [30, 20]
        title { text: "Elfogyott a pénz!" }
        content { text: "Kincstáradból kifogytak a debenek. Most még kapsz rendkívüli támogatást, de többé senki sem fog kisegíteni. Használd ezt az adományt jövedelmező vállalkozások létrehozására." }
    }

    message_debt_again {
        id: 116,

        size [30, 20]
        title { text: "Adósság!" }
        content { text: "Kincstárad gyorsan kiürül. Legfeljebb 5000 deben hitelt vehetsz fel, de a @48adósság családod bukásához vezethet, ha nem törleszted mielőbb." }
    }

    message_out_of_money_again {
        id: 117,

        size [30, 20]
        title { text: "Elfogyott a pénz!" }
        content { text: "Kiürültek a város kincstárai, ó, fáraó. Hű nomarkhoszaid minden nélkülözhető debenjüket felajánlották, de erre többé nem lesz lehetőségük." }
    }

    message_wrath_of_the_emperor {
        id: 118,
        type: 2,

        size [30, 20]
        urgent: 1,
            title { text: "A fáraó haragja" }
        video { text: "@12" }
    }

    message_attack_called_off {
        id: 120,
        type: 2,

        size [30, 20]
        title { text: "Lefújt támadás" }
        content {
            text: "Új parancs érkezett. Eszerint ismét kivívtál némi megbecsülést Egyiptomban, így pusztulásod már nem szükséges. Búcsúzom... egyelőre."
        }
    }
    message_debt_anniversary {
        id: 121,

        size [30, 20]
        urgent: 1,
            title { text: "Az adósság évfordulója" }
        content {
            text: "Kincstáradban továbbra sincs egyetlen deben sem. Minden újabb adósságban töltött év rontja hírnevedet, és ezzel @35Birodalmi értékelésedet is. Talán érdemes áttekintened a @48pénzügyekről szóló tudnivalókat."
        }
    }

    message_barbarians_attack {
        id: 122
        type: 2
        message_type: 7

        size [30, 20]
        urgent: 1,
        title { text: "Barbár támadás!" }
        video { text: "smk\\Spy_Barbarian.smk" }
    }

    message_legion_attacks {
        id: 123
        type: 2
        message_type: 7

        size [30, 20]
        urgent: 1,
        title { text: "A légió támadása" }
    }

    message_distant_battle {
        id: 124
        type: MESSAGE_ARCH_MESSAGE
        message_type: MESSAGE_TYPE_DISTANT_BATTLE

        title { text: "Távoli csata" }
        video { text: "@10" }
        content { text: "xxxx lásd eventmsg.txt" }
    }

    message_enemies_closing {
        id: 125
        type: 2

        size [30, 20]
        title { text: "Közeledő ellenség" }
        video { text: "@10" }
        content { text: "xxxx lásd eventmsg.txt" }
    }

    message_enemies_at_the_door {
        id: 126
        type: 2

        size [30, 20]
        urgent: 1
        title { text: "Ellenség a kapuknál" }
        video { text: "@10" }
        content { text: "xxxx lásd eventmsg.txt" }
    }

    message_template_request {
        id: 130,
        type: 2
        message_type: 2
        size [30, 20]
        title { text: "A fáraó árukat kér" }
        content { text: "" }
    }

    message_wrath_of_bast_3 {
        id: 134,
        type: 2,

        size [30, 20]
        title { text: "Bastet haragja" }
        video { text: "@20" }
        content { text: "Jaj neked! Bastet megdöbbent közönyödön. Hogy bebizonyítsa, városod egészségét nem őrzöd meg az ő tisztelete nélkül, vérrel árasztotta el a folyót, megmérgezve a vízellátást. Csak remélheted, hogy polgáraid kitartanak, amíg a víz újra megtisztul." }
    }

    message_city_unemployment {
        id: 135,
        type: 2,

        size [30, 20]
        title { text: "Városi munkanélküliség" }
        content { text: "Túl kevés a munkahely ahhoz, hogy mindenki dolgozhasson. Ha nem hozol létre új állásokat, a munkanélküliek kétségbeesésükben bűnözéshez fordulhatnak, vagy a Királyság más részein próbálhatnak szerencsét." }
    }

    message_employees_needed {
        id: 136,

        size [30, 20]
        title { text: "Munkaerő szükséges" }
        content { text: "Túl kevés a munkaképes korú lakos a város állásainak betöltésére. Ha nem találsz gyorsan új dolgozókat, a városi szolgáltatások romlani fognak, és az ipari termelés is visszaesik." }
    }

    message_common_festival {
        id: 137,

        size [30, 20]
        title { text: "Egyszerű ünnepség" }
        content { text: "Mindenki örül, hogy korábban abbahagyhatja a munkát, és egy kis pihenőt tölthet az Ünnepi téren. Választott istened is észreveszi kedves gesztusodat." }
    }

    message_lavish_festival {
        id: 138,

        size [30, 20]
        title { text: "Pompás ünnepség" }
        content { text: "Kezdetét veszi az egész napos ünnepség. A város minden részéből az Ünnepi térre sietnek az emberek, és láthatóan jókedvűek. Választott istened nagyra értékeli odaadásodat." }
    }

    message_grand_festival {
        id: 139,

        size [30, 20]
        title { text: "Nagyszabású ünnepség" }
        content { text: "Végre elkezdődött a régóta várt kétnapos ünnepség! Mindenki az Ünnepi térre özönlik az ingyen sör és a féktelen mulatság kedvéért. Az esemény által tisztelt isten bizonyára mosolyog rád." }
    }

    message_wrath_of_osiris {
        id: 140
        type: 2

        size [30, 20]
        title { text: "Ozirisz haragja" }
        video { text: "@24" }
        content { text: "Oziriszt sérti városod megdöbbentő hitetlensége. Ha nem engeszteled ki gyorsan, a következő áradás sokkal rosszabb lesz a vártnál... talán el sem érkezik!" }
    }

    message_wrath_of_ptah {
        id: 141
        type: 2

        size [30, 20]
        title { text: "Ptah haragja" }
        video { text: "@22" }
        content { text: "Kivívtad Ptah haragját! Városodban jelenleg nincs olyan iparág, amelyet megbüntethetne, de ügyelj erre az istenre, amikor bányászatba, gyártásba vagy kőfejtésbe kezdesz." }
    }

    message_wrath_of_ptah_2 {
        id: 142
        type: 2

        size [30, 20]
        title { text: "Ptah haragja" }
        video { text: "@22" }
        content { text: "Ptah neheztel büszkeségedre, amiért azt hiszed, városod az ő tisztelete nélkül is virágozhat. Emlékeztetőül elpusztított néhány ipari épületet." }
    }

    message_wrath_of_seth_noeffect {
        id: 143
        type: 2

        size [30, 20]
        title { text: "Seth haragja" }
        video { text: "@21" }
        content { text: "Városod elkerülte Seth haragját, mivel nem rendelkezett olyan katonai létesítményekkel, amelyeket az isten elpusztíthatott volna. Ennek ellenére óvakodj a Pusztítás Istenének felbőszítésétől, mert haragja sokféle formát ölthet, és sokáig emlékszik." }
    }

    message_wrath_of_bast {
        id: 144,
            type: 2,

            size [30, 20]
        title { text: "Bastet haragja" }
        video { text: "@20" }
        content { text: "Szörnyű hírek! Mivel városod nem adja meg neki a megérdemelt tiszteletet, Bastet, az Otthon Istennője, lerombolta néhány legjobb házadat!" }
    }
    message_blessing_from_ptah {
        id: 145,
            type: 2,

            size [30, 20]
        title { text: "Ptah áldása" }
        video { text: "@22" }
        content { text: "Ptah olyan raktárudvart keresett, ahol több drágakő, agyag, kerámia, len, vászon vagy ékszer fér el. Ha talált volna ilyet, növelte volna városod készleteit." }
    }
    message_wrath_of_osiris_2 {
        id: 147
        type: 2

        size [30, 20]
        title { text: "Ozirisz haragja" }
        video { text: "@24" }
        content { text: "Szomorú nap! Mivel megtagadtad tőle a megfelelő tiszteletet, Ozirisz sáskák seregét küldi, hogy felfalja terményeidet." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
            type: 2,

            size [30, 20]
        title { text: "Ptah haragja" }
        video { text: "@22" }
        content {
            text: "Ptah felháborodott, amiért megtagadod tőle a tiszteletet. Békák seregét küldi a városra. Ezek a nyálkás bőrű, bűzlő teremtmények sokakat arra kényszerítenek, hogy elhagyják otthonukat."
        }
    }

    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2

        size [30, 20]
        title { text: "Seth haragja" }
        video { text: "@21" }
        content { text: "Mivel megtagadod tőle a hódolatot, Seth dühében jégesőt zúdít a városra, amely mindenkit lesújt és megöl, aki az útjába kerül!" }
    }

    message_farming {
        id: 150,

            size [30, 20]
        image { id: 81, pos [15, 15] }
        title { text: "Mezőgazdaság" }
        subtitle { text: "Történelem" }
        content {
            text: "A földművelés és a mezőgazdaság az egyiptomi gazdaság alapját jelentette. A bőséges termés lehetővé tette Egyiptom számára, hogy @177kereskedjen szomszédaival, új javakat hozva az országba. @L@LA sikeres földművelés kulcsa az áradás, azaz az akhet volt. Minden évben a Nílus kilépett medréből, és újra termékennyé tette a talajt. Amíg az áradás bekövetkezett, az egyiptomiak biztosak lehettek abban, hogy elegendő élelmük lesz. Az alacsony vagy elmaradó áradások éveiben éhínség sújtotta Egyiptomot, ami néha kormányzatok bukásához is vezetett. @L@LA megújuló áradás kihasználására gátakat építettek a földek köré, hogy felfogják a vizet emelkedésekor. Amikor a Nílus visszahúzódott (ezt peretnek nevezték), a víz tápanyagaival együtt lassan beszivárgott a talajba. Körülbelül hat hét múlva a földművesek megnyitották a gátakat, és a maradék vizet leengedték. Természetesen a víz alá került föld igen puhává vált. Mielőtt elvethette volna a magokat, a gazdának meg kellett várnia, hogy a talaj kissé megszáradjon és megszilárduljon. @L@LVégül a shemu idején betakarították a termést. Az egyiptomi fogyasztásra szánt növényeket a @5gabonaraktárakban tárolták. A kivitelre szánt élelmet a @6Raktárudvarokban tartották, amíg bárkákra nem rakták. @L@LA birtokosok vagy a kormány tulajdonolták a földeket, és munkásokat alkalmaztak a legnehezebb munkák elvégzésére. A földművelés nem volt könnyű munka, és a legtöbb feladatot kézzel végezték. A gazdák eszközei közé tartozott a kapa, a kézi eke és a sarló. A háziasított ökrök megkönnyítették a szántás egy részét. @L@LA mezőgazdaság nyersanyagokat és élelmiszereket egyaránt termelt. A @185gabona&és&árpa fontos élelmiszernövények voltak, míg a @189len, amelyből @398vásznat készítettek, a legfontosabb ipari növénynek számított. @L@LA földművelés és mezőgazdaság az egyiptomi túlvilághitben is fontos szerepet játszott. Miután az elhunyt bebocsátást nyert a túlvilágra, a Nádlak mezőin találta magát, ahol tovább művelte a földet."
        }
    }

    message_industry {
        id: 151,

            size [30, 20]
        image { id: 82, pos [15, 15] }
        title { text: "Ipar" }
        subtitle { text: "Történelem" }
        content {
            text: "Az Óbirodalom idejére a termékek előállítása kikerült a háztartásokból, és központi műhelyekbe költözött, amelyek az élethez szükséges szinte minden eszközt előállítottak. Minden műhely egy adott termékre szakosodott, és nagyjából úgy működött, mint egy modern gyártósor. Minden munkás a késztermék egy bizonyos részéért felelt, nem pedig az elejétől a végéig dolgozott egy tárgyon. A kézművesek által használt eszközök, valamint a műhelyek által előállított anyagok az állam tulajdonát képezték. A mesterek fizetséget kaptak, amelyet általában élelmiszerben és szükséges javakban adtak. @L@LAz egyiptomi ipar virágzott, és számos terméket állított elő. Az egyiptomiak dolgozhattak @198fazekasként, @398szövőként, ékszerészként, tímárként, @389ácsként és kohászként, valamint pékek és @194sörfőzők is lehettek."
        }
    }
    message_housing {
        id: 152,

            size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Lakóházak" }
        subtitle { text: "Történelem" }
        content {
            text: "Az egyiptomiak téglából, fából, vályogból vagy ritkábban kőből építették otthonaikat. A házak stílusa és mérete a lakó vagyonától és lakhelyétől függött. A földművelésből élő vidéki lakosok egyszerű, két-négy helyiségből álló tégla- vagy préseltvályog-házakban éltek. A városi munkásosztály otthonai hasonlóan kicsik voltak, és a zsúfoltabb városokban helytakarékosság miatt kétszintes, kétcsaládos házakat is építettek. A városi munkások 3-7 szobás téglaházakban laktak. @L@LA gazdagabb polgárok nagyobb házakkal rendelkeztek, amelyek közül néhány igen tágas volt. A magas rangú hivatalnokoknak néha 60-70 szobás otthonaik voltak, magas, fából készült oszlopokkal tartott mennyezettel, vendégfogadó termekkel, bőséges tárolóhellyel és szolgák számára kialakított helyiségekkel. A legfényűzőbb otthonok mind közül a @175fáraó&palotái voltak. @L@LAz egyiptomi városok többnyire természetes módon növekedtek abba az irányba, amerre lehetőségük nyílt. Néhány várost azonban terv szerint építettek, közülük a leghíresebb a Deir el-Medinában a munkások számára létesített település. @L@LA legtöbb egyiptomi várost falak vették körül. A védelmi építményekről bővebben kattints @182ide."
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
            text: "Utak",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A @157Nílus volt Egyiptom fő közlekedési útvonala. Különböző alakú és méretű hajók szállították az embereket, árukat és nyersanyagokat egyik helyről a másikra. Az ókori egyiptomiaknak természetesen szárazföldi útjaik is voltak. Ezeket az utakat általában nem burkolták, hanem egyszerűen jól kitaposott ösvények voltak. A legtöbb városban az utak szükség szerint kanyarogtak. A tervezett városokban, például a Deir el-Medinai munkástelepen, az utak szabályos rácsos elrendezésben épültek. @L@LNéhány kereskedelmi útvonal is jól kiépült, de ezeket sem burkolták, és igencsak veszélyes lehetett rajtuk utazni. A sikeres kereskedelem veszélyeiről bővebben kattints @177ide."
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
            text: "Öntözés",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomiak öntözéssel növelték a művelhető földek mennyiségét. Már a IX. dinasztia idején, körülbelül Kr. e. 2000-ben elkezdték öntözőcsatornák és árkok hálózatának kiépítését. Néhány csatorna valószínűleg már korábban is létezett, de azokat közlekedésre használták. Az öntözőcsatornák kiterjesztették a folyó áldásait, és tápláló iszapot juttattak a folyótól távolabb eső területekre. @L@L Egyiptom korai történetében a földjüket öntözni kívánó földművesek nehéz helyzetben voltak. A gazdák kézzel öntözték földjeiket: egy vállukon hordott rúddal két agyag- vagy bőrvödröt vittek a Nílushoz vagy más vízforráshoz. A földműves ezután vízzel teli vödrökkel tért vissza a kis gátakkal felosztott földjére. A gátak felfogták a vizet, így a lassú és fáradságos öntözési módszer hatékonyabbá vált. @L@LA XVIII. dinasztia végén (körülbelül Kr. e. 1300-ban) bevezették a vízemelőt, vagyis a sadufot. A saduf valószínűleg Mezopotámiából került Egyiptomba, ahol már Kr. e. 2370 körül használták. A Nílus vagy más vízforrás partján felállított saduf egy hosszú fagerendából állt, amely egy tengelyen előre-hátra billent. A gerenda egyik végén lévő vödröt egy tégla vagy más súly ellensúlyozta. Egy ember lenyomta a vödrös végét, hogy a vízbe merítse, majd a súly segített a munkásnak a vizet a sadufhoz csatlakozó vájatba emelni. @L@LA saduf bevezetése körülbelül 15 százalékkal növelte Egyiptom művelhető földterületét. Mivel az így öntözött földeket soha nem borította el teljesen a víz, évente két termést is hozhattak az egy helyett."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2

        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Munka" }
        subtitle { text: "Történelem" }
        content { text: "Az ókori Egyiptomban a parasztok végezték a legtöbb nehéz fizikai munkát. A földművesek művelték a földet és takarították be a termést a növekedési időszakban. Az áradás idején ugyanezeket a munkásokat az állam szolgálatára sorozták be. Többnyire piramisok és más építmények építésén dolgoztak, de feladatuk lehetett az egyiptomi infrastruktúra, például az @153utak és az @154öntözőcsatornák karbantartása is. @L@LBár a parasztok munkája nem volt könnyű, nem bántak velük teljesen kegyetlenül. Egy átlagos munkanap nyolc órán át tartott, ebédszünettel. A munkahét nyolc napos volt, amelyet két pihenőnap követett. Ezeken a „hétvégéken” kívül az ünnepek idején is szünetelt a munka. A dolgozók betegségek vagy családi halálesetek esetén is szabadságot kaphattak. @L@L A jelenlétet és a hiányzások okait gondosan feljegyezték. Néhány hiányzási indok ma valószínűleg nem lenne elfogadható. Egy munkás például azért maradt távol, hogy egy barátjával italozzon. @L@L A közhiedelemmel ellentétben az állami építkezéseken ritkán alkalmaztak rabszolgamunkát. Néha rabszolgákat dolgoztattak kőfejtőkben, de többnyire háztartásokban szolgáltak. @L@L Ha a munkásokat nem megfelelően kezelték, sztrájkba léphettek. III. Ramszesz uralkodása alatt, körülbelül Kr. e. 1152-ben, a Deir el-Medinai munkások hivatalosan beszüntették a munkát, hogy tiltakozzanak járandóságuk késedelmes kifizetése miatt. Sztrájkjuk sikerrel járt, és a késedelmes fizetések problémáját rendezték." }
    }
    message_clean_water {
        id: 156

        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Kút és vízellátás", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az ivóvíz eljuttatása a lakossághoz némi kihívást jelentett az ókori Egyiptomban. A fő vízforrás a Nílus és a folyó talajvízkészlete volt. A Nílussal nem érintkező területeken néhány oázis létezett, de a föld nagy része száraz volt. @L@LA víz eljuttatására a városrészekbe ciszternákat építettek a tehetősebb házakban. Vízhordók vödrökben szállították a vizet ezekhez a házakhoz, majd a ciszternákba öntötték. @L@LAz egyiptomiak kiválóan értettek a kútfúráshoz. A gízai munkástelep közelében egy kút elkészítéséhez a munkásoknak 300 lábnyi sziklán kellett átfúrniuk magukat. A legtöbb kutat kútház fedte. A kútházból lépcsők vezettek le a víz szintjéhez. Innen az emberek megtölthették korsóikat vízzel."
        }
    }
    message_nile {
        id: 157

        size [30, 20]
        image {
            id: 87,
                pos [15, 15]
        }
        title {
            text: "Nílus",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomi civilizáció egyszerűen nem létezhetett volna a Nílus nélkül. Egy olyan vidéken, ahol kevés az eső, a Nílus megbízható vízforrást biztosít az emberek és a föld számára egyaránt. A folyó kiszámítható időközönként kilépett medréből, és újra termékennyé tette a termőföldeket. @L@LAz ókori egyiptomiak tisztában voltak a Nílus fontosságával. A folyó állandó újjáélesztő erejének megfigyelése nagyban hozzájárult az egyiptomi vallási szokásokhoz, különösen a túlvilágról alkotott hitükhöz. @L@LAz egyiptomi naptár évszakokra oszlott, amelyeket a Nílus különböző szakaszairól neveztek el. Az áradás időszakát, amikor a Nílus elöntötte partjait, akhetnek nevezték. Az áradást az etióp fennsíkon eredő Kék-Nílus forrásvidékén jelentkező éves monszunok okozták. A visszahúzódás, vagyis a peret jelezte azt az időszakot, amikor a Nílus apadni kezdett, és a föld ismét előbukkant. A betakarítás idejét shemunak nevezték, amit néha szárazságként fordítanak."
        }
    }
    message_dentistry {
        id: 158,

            size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Fogászat" }
        subtitle { text: "Történelem" }
        content {
            text: "A fogászat egyike volt annak a sok területnek, amelyen egy ókori egyiptomi orvos dolgozhatott. Az ókori egyiptomi maradványok azt mutatják, hogy a fogorvosok nehéz küzdelmet vívtak. A mindenütt jelen lévő homok elősegítette a fogszuvasodást. A homok mindenbe bekerült, még az ételbe is, és az állandó homokropogtatás gyorsan lekoptatta az egyiptomiak fogait. A fogkopás gyakran tályogokhoz vezetett, amelyek miatt a fog kieshetett, sőt akár halált is okozhattak. @L@LOrvosi papiruszok részletesen leírják, hogyan kezelték a fogorvosok az egyes problémákat. Ha például egy fog kiesett, a fogorvos arany- vagy ezüstdróttal a szomszédos fogakhoz rögzítette. Létezett egy tömési recept is, amely gyanta és malachit keverékét használta, de a régészek nem találtak olyan fogmaradványokat, amelyekben a tömés épségben fennmaradt volna. @L@L A régészek olyan eszközöket is felfedeztek, amelyekről úgy vélik, fogkefeként használták őket. Eddig nem került elő ókori egyiptomi fogselyem."
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
            text: "Patika",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori egyiptomi gyógyászati és gyógyszerészeti gyakorlat jól dokumentált. A vallás fontos szerepet játszott a betegségek gyógyításában, és a legtöbb előírt gyógymódot imák vagy varázsigék kísérték. Az orvosi papiruszok konkrét gyógymódokat ismertettek, amelyek közül néhány mai szemmel meglehetősen különösnek tűnik. Emésztési zavar kezelésére például egy disznófogat törtek össze, majd négy cukorsüteménybe keverték. A betegnek naponta egy süteményt kellett elfogyasztania, ezután az emésztési problémának meg kellett szűnnie. A kopaszság elleni gyógymód varjúcsigolya, égetett szamárpata és fekete kígyó zsírjának keverékét írta elő."
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
            text: "Orvoslás",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomi társadalom más részeihez hasonlóan az orvosi hivatás is erősen tagolt és bürokratikus volt. A szakma hierarchikus rendszerben működött, az orvosok olyan címeket viseltek, mint vezető orvos, felügyelő, elöljáró és az orvosok mestere. A legmagasabb rangú orvos a 'Dél és Észak orvosainak főnöke' címet viselte. @L@LAz orvosok tudásukat az állatok belső szerveinek és írásos szövegek tanulmányozásával szerezték, nem a balzsamozási folyamat megfigyelésével. Az orvoslás teljesen elkülönült a temetési szertartásoktól. @L@LA jó egészség alapja a metu fogalma volt. A szív volt a test központja, és a test minden része a metu, vagyis csatornák révén kapcsolódott hozzá. A keringési rendszer leírásánál többet jelentett: a test minden rendszerét metu-nak tekintették. Betegség akkor alakult ki, ha a metu valamely része elzáródott. @L@LA betegségek gyógyítására az orvosok imával kísért gyógyszereket írtak elő. Az egyiptomi gyógyszerészeti gyakorlatokról bővebben lásd: @159apothecaries. @L@LAz egyiptomiakat többek között gyermekbénulás, himlő, gerinctuberkulózis és malária is sújtotta. Emellett gyakran szenvedtek parazita férgek okozta betegségektől."
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
            text: "Balzsamozók",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A balzsamozás az ókori egyiptomi temetkezési szokások alapköve volt. Az elhunyt ká-jának, vagyis szellemének szüksége volt egy helyre, ahol a túlvilágon élhetett, ezért szüksége volt a testére is. A balzsamozás során a testet először a Nílus vizében mosták meg, az újjászületést jelképezve. Ezután eltávolították a holttest belső szerveit, és úgynevezett kanópuszedényekben tárolták őket. Az egyetlen eldobott szerv az agy volt (amelyet az orron keresztül távolítottak el), mert az ókori egyiptomiak úgy hitték, hogy nincs semmilyen szerepe. A kanópuszedényeket a testtel együtt temették el. @L@LA belső szervek eltávolítása után a balzsamozó illatszerekkel, olajokkal és vászonnal töltötte ki a testüreget, majd lezárta a testet. Ezután a testet nátronnal, egyfajta sóval borították be. 70 nap elteltével lemosták, vászonba tekerték és kátránnyal kenték be. A kátrány segített elpusztítani azokat a baktériumokat és gombákat, amelyek egyébként lebontották volna a testet. @L@LA balzsamozási eljárás költségei miatt csak a leggazdagabb polgárok engedhették meg maguknak."
        }
    }
    message_shrine_and_temple {
        id: 162,

            size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Szentély és templom", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "A templomokat az istenek lakhelyének tekintették, és mindegyik templomhoz számos szolgáló @384pap tartozott, akik az isten gondját viselték. A polgárok áldozatokkal vettek részt az istenek tiszteletében, de ritkán láthatták a templom mélyén elrejtett istenszobrot. Csak ünnepnapokon pillanthatták meg az istent, amikor szertartási bárkán vitték végig a városon. @L@LAz egyiptomiak az istenekhez fordultak tanácsért. A templom előudvarába bárki beléphetett, és itt az emberek az őket foglalkoztató kérdésekről kérdezhették az isteneket, vagy bocsánatot kérhettek korábbi vétkeikért. A papok, akik rejtve maradtak a szemük elől, válaszoltak a könyörgőknek. A polgárok ünnepnapokon is kérdezhették az istent, amikor az körbejárta a várost. @L@LA templomokban végzett hódolat mellett a legtöbb egyiptominak otthonában is volt szentélye. Gyakran Bes, a ház védelmező istenének szentélye volt ez. Úgy tűnik, az egyéneknek saját védőisteneik is voltak. A Deir el-Medinában feltárt jelenléti ívek szerint a munkások néha azért hiányoztak, hogy 'istenük ünnepét' megünnepeljék. @L@LA védőisten fogalma városokra, településekre és régiókra is kiterjedt. Ez az elképzelés változásokat okozott az egyiptomi történelem különböző korszakaiban tisztelt istenek körében. A vallás fejlődéséről bővebben kattints @399here."
        }
    }
    message_school_and_eduction {
        id: 163,

            size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "Iskola és oktatás", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az ókori Egyiptomban az oktatás rendkívül gyakorlatias volt. Mindenkit egy meghatározott pályára készítettek fel. Sokak számára az oktatás tanoncképzést jelentett, és a fiúkat általában apjuk tanította egy mesterség elsajátítására. Néhány lány is tanoncnak állt, hogy táncosként, énekesként vagy szövőként dolgozhasson, de a legtöbben a háztartás vezetésének művészetét tanulták meg. @L@LAz írnokok részesültek a legformálisabb oktatásban. Az írnokiskolák, amelyeket Per-Ankh-nak, vagyis 'az élet házának' neveztek, főként templomokhoz kapcsolódtak. Itt a leendő írnokok az írott nyelveket tanulták, elsősorban a hieratikus, később pedig a démotikus írást, amelyeket a mindennapi ügyintézésben használtak. Az írnokok mesterségüket kéziratok ostrakonokra, vagyis régi kődarabokra történő másolásával sajátították el. Csak miután teljesen elsajátították tudásukat, bízták rájuk a papiruszt. Szigorú fegyelemre volt szükség, és gyakoriak voltak a testi fenyítések. Az írnokképzés általában 10 és 20 éves kor között zajlott."
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
            text: "Könyvtár és irodalom",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az írott nyelv birtokában az egyiptomiak számos történetet, verset és himnuszt jegyeztek fel. Ezeket a szövegeket a Per-Ankh-hoz (az élet házához), vagyis a templom mellett található @163Írnok&iskolához kapcsolódó könyvtárakban őrizték. @L@LAz egyiptomi irodalom szóbeli hagyományból ered, és többnyire azért jegyezték le, hogy emlékeztetőül szolgáljon a mesélő számára. A legtöbb egyiptomi írástudatlan volt, és sok @387írnok egyben történetmesélő is volt, akik az írott szövegeket a történetek, himnuszok és versek felidézéséhez használták. Azok, akik tudtak olvasni, különösen a fáraó udvarához tartozók, hozzáférhettek a könyvtárakhoz és maguk is olvashatták a papiruszokat. Néhány gazdag polgár saját könyvtárral is rendelkezett. @L@LAz ókori egyiptomi irodalom több műfajra osztható, többek között önéletrajzokra, kalandtörténetekre, népmesékre, mitológiára, siralmakra, költészetre és himnuszokra. Ezek közül az önéletrajz volt a legrégebbi, és abból a hagyományból ered, hogy az emberek eredményeiket sírjuk falára vésték. A szatíra szintén népszerű volt."
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
            text: "Szórakozás",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori egyiptomiak számos szabadidős tevékenység közül választhattak. A sportok gyakoriak voltak, különösen a vízi sportok, például az evezés és az úszás (a leggazdagabbak saját medencéik magányában élvezhették ezt). Az egyiptomiak voltak az első ismert kultúra, amely a halászatot szabadidős tevékenységként űzte. @L@PAz ökölvívás népszerű látványsport volt, a mérkőzéseket kifejezetten a fáraó szórakoztatására rendezték. Más sportok közé tartozott a kézilabda, a gyeplabdához hasonló játék, a torna, az íjászat és a súlyemelés. @L@PA műveltek számára az olvasás kedvelt időtöltés volt, és az első ismert rövid történetet is az ókori Egyiptomban írták. A költészet népszerű volt, de nincs bizonyíték arra, hogy az egyiptomiak színdarabokat írtak volna. Az olvasásról, írásról és irodalomról bővebben lásd: @164libraries. @L@L@393Az ünnepek szintén fontos részét képezték az egyiptomi életnek."
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
            text: "Gyermekek",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori Egyiptomban nagyra becsülték a gyermekeket, és az élet folytatásának tekintették őket. A korai házasság gyakori volt, hogy sok gyermek születhessen. Az alsóbb osztályok gyermekei szüleiket követték a földekre, és segítettek a betakarításban. A közép- és felsőbb osztályok gyermekei napjaikat otthon töltötték édesanyjukkal. Amikor elég idősek lettek, a felsőbb osztályú fiúkat iskolába küldték, majd apjuk mellett tanoncként dolgoztak. @L@LAz egyiptomi gyermekeknek sok játék állt rendelkezésükre, például labdák, babák, pörgettyűk és faállatok. Játékokat játszottak, például kötélhúzást, és sok olyan szabadidős tevékenységet élveztek, mint szüleik, például az úszást és a halászatot. @L@LA gyermekek és szüleik különféle háziállatokat is tartottak. A kutyák és macskák népszerű kedvencek voltak, akárcsak a betanított majmok, madarak, gazellák, valamint a rendkívül gazdagok és bátrak számára az oroszlánok."
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
            text: "Népesség",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori Egyiptom sok szempontból hasonlított a modern társadalomra. Sok ember élt városi központokban, ahol a gyártás számos munkahelyet biztosított. A földművesek általában kisebb, vidéki falvakban laktak. A lakosság nagy része természetesen a folyó közelében élt. @L@LAz egyiptomi népesség idővel növekedett, és növekedése közvetlenül kapcsolódik a @154öntözéshez. A dinasztiák előtti korban a népesség becslések szerint nem haladta meg a 350 000 főt. Az i. e. 2. évezred végére azonban, amikor az öntözési módszerek megnövelték a művelhető földterületet, a lakosság feltehetően elérte a 3 millió főt."
        }
    }
    message_history_society {
        id: 168,

            size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Társadalom", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az egyiptomi társadalom erősen rétegzett volt, jól elkülönülő osztályokkal. Az emberek többnyire abban az osztályban maradtak, amelybe születtek, bár néhányan házasság révén magasabb osztályba kerültek. @L@LA legalacsonyabb osztály tagjai a parasztok voltak. A parasztok élettartama volt a legrövidebb az összes osztály közül, és kemény munkával töltötték életüket, akár földeken, akár állami építkezéseken dolgoztak. Maradványaik azt mutatják, hogy a legtöbb parasztnak súlyos hátproblémái voltak, és a kemény munka következtében csigolyáik néha összeforrtak. Egyszerű, néhány helyiségből álló épületekben éltek, egyszerű sírokba temették őket, és nem engedhették meg maguknak a balzsamozást. @L@LA középosztályt kézművesek, kereskedők és más iparban dolgozók alkották. Tágasabb otthonokban éltek, és néhányuk megengedhette magának a balzsamozást és szerény síremlékeket. @L@LA leggazdagabb osztályt a magas rangú állami tisztviselők alkották. Megengedhették maguknak a legnagyobb luxust, beleértve a balzsamozást is, és gyakran díszes sírokat építtettek. Étrendjük gazdagabb és változatosabb volt, mint más egyiptomiaké. A felsőbb osztályú egyiptomiak néhány mumifikált maradványának vizsgálata során 10–20%-uknál érelmeszesedést, vagyis az artériák megkeményedését találták, ami sok állati zsír fogyasztására és talán stresszes életmódra utal. A gazdag férfiakat gyakran pocakosnak ábrázolták, ami jólétük jele volt."
        }
    }
    message_history_juggling {
        id: 169,

            size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Zsonglőrködés", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az ókori egyiptomiak voltak a legkorábbi ismert zsonglőrök. A Menat Hufu-i (Beni Haszán) Középbirodalmi sír festményei fiatal nőket ábrázolnak, akik különféle zsonglőrmutatványokat végeznek, többek között egymás hátán ülve labdákat dobálnak egymásnak. @L@LA zsonglőrködés jelentősége az ókori Egyiptomban nem teljesen világos. Lehetett vallási jelentősége, de akár puszta szórakozás is."
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
            text: "Zene",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomiak sokféle hangszert használtak, köztük fuvolákat (amelyek sokféle méretben készültek), hárfákat, lírákat, lantokat, tamburinokat és más ütőhangszereket. Az énekesek az egyiptomi zene szerves részét képezték, és a papiruszokra feljegyzett himnuszok és versek többségét zenére éneklésre szánták. @L@LAz ütőhangszereket különösen a @171tánc kíséretére használták. Sok táncos kasztanyettával kísérte előadását. @L@LAz egyiptomiak trombitákat is használtak. A trombiták a hadsereghez kapcsolódtak (talán az egyiptomiaknak is volt saját ébresztőjük), és gyakran kerültek királyok és katonai vezetők sírjaiba. Tutanhamon sírjában két trombitát találtak. Hogy meghallgassák hangjukat, 1939-ben az egyiket megszólaltatták. Néhány hang után a trombita azonnal szétesett. Rögtön helyreállították. A trombita kapcsolatban állt @376Ozirisszel, a mezőgazdaság és a Nílus áradásának istenével is. @L@LMás hangszereknek szintén volt vallási jelentőségük. A szisztrum, egy nagy csörgőszerű hangszer, @380Hathorhoz, az öröm, szerelem és ünnepek istennőjéhez kapcsolódott. A fuvolák @378Amonhoz, a nap istenéhez kötődtek."
        }
    }
    message_history_dance {
        id: 171,

            size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Tánc", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az ókori egyiptomi tánc a vadászok által a vadászat előkészítésére használt rítusokból fejlődött ki. Egy vezető táncos, az úgynevezett pap-táncos, felelt azért, hogy a táncokat megfelelően hajtsák végre. @L@LKésőbb a tánc az ünnepek és más vallási szertartások szerves részévé vált, de önálló szórakozási formaként is megjelent. Hivatásos tánccsoportok léptek fel a városi tereken, és magánrendezvényekre is fel lehetett őket bérelni. A táncosokat általában @170zene kísérte. A legtöbb hivatásos táncos nő volt, és sokuk combján Besnek, a zene és tánc istenének tetoválása volt. @L@LNéhány polgár szórakozásként is táncolt, bár ez elsősorban az alsóbb osztályok kedvelt időtöltése volt. Minél magasabb rangú volt egy egyiptomi, annál kevésbé valószínű, hogy táncolt. Emellett férfiak és nők soha nem táncoltak együtt. A nők más nőkkel, a férfiak más férfiakkal táncoltak. @L@LÚgy tűnik, az egyiptomi táncmozdulatokat arról nevezték el, amit ábrázoltak, például 'egy állat vezetése', 'egy hajó sikeres elfogása' és 'a mókás csirke'."
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
            text: "Szenet",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A szenet volt az ókori Egyiptom legnépszerűbb táblajátéka. A tábla téglalap alakú volt, és három, egyenként 10 mezőből álló sorra osztották. Két játékos játszotta, és mindkettőnek legalább öt bábuja volt. A lépéseket négy dobópálca határozta meg. A szenet szabályait sehol sem jegyezték fel, ezért senki sem tudja pontosan, hogyan játszották. A legtöbb történész azonban egyetért abban, hogy a játék a túlvilágra vezető utazást jelképezte. A backgammon és az ugróiskola is a szenet leszármazottjának tekinthető. @L@LA szenet, más játékokkal együtt, valószínűleg egyike volt azoknak a szórakozásoknak, amelyeket az egyiptomiak kocsmákban vagy fogadókban űztek. Egy kemény munkanap után sok egyiptomi helyi kocsmákba tért be, ahol @194sört szolgáltak fel, és élénk beszélgetés töltötte be a levegőt. Férfiak és nők egyaránt – különösen a még hajadonok – látogatták a sörházakat."
        }
    }
    message_history_taxation_and_money {
        id: 173,

            size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Adózás és pénz", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "Az ókori egyiptomiak adót fizettek a fáraónak, amelyet árucikkek formájában teljesítettek. Így például egy földművesnek meghatározott mennyiségű gabonát kellett adóként adnia a fáraónak. Írnokokat küldtek ki minden gazdaságba, hogy megállapítsák, mennyivel tartozik az egyes földműves. @L@LAz értéket néha debenben fejezték ki. A deben fémkorong volt, amelyet valószínűleg eredetileg súlymértékként használtak."
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
            text: "Kormányzat és bürokrácia",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori Egyiptom kormányzata rendkívül bürokratikus volt. Minden elképzelhető feladathoz tartozott egy állami tisztviselő, gyakran tekintélyes hangzású címmel. Mindennek az élén természetesen a fáraó állt. A fáraó jobbkeze a vezír volt, aki felelt azért, hogy minden fáraói parancsot végrehajtsanak. A vezír alatt nomarkhoszok (tartományi kormányzók), kancellárok, alkirályok, felügyelők, polgármesterek és még sokan mások szolgáltak. Mivel az ókori Egyiptom teokrácia volt, a @384papok fontos szerepet töltöttek be. @L@LSok ember egynél több címet is viselt. Például Imhotep, aki Dzsószer I. uralkodása alatt szolgált és a lépcsős piramis építését felügyelte, többek között a vezír, Ptah főpapja és az építkezések felügyelője címet is birtokolta."
        }
    }
    message_history_pharaohs_home {
        id: 175,

            size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "A fáraó otthona", pos [125, 15] }
        subtitle { text: "Történelem" }
        content {
            text: "A fáraó otthona volt a város legpompásabb épülete. Míg a legtöbb ház csak egy-két szobából állt, néhány fáraói palota több tucat helyiséggel rendelkezett, és az ókori Egyiptom által kínált legjobb kényelmi felszerelésekkel volt ellátva. @L@LAhogy a @174kormányzatban, úgy a fáraó szolgálatában álló egyiptomiak is címeket viseltek, és pontosan meghatározott feladatokért feleltek. A fáraó alkalmazottai között volt a háztartási ügyek felügyelője, a királyi főmanikűrös és a királyi pohárnok. @L@LAz egyik királyi pohárnokot, Nefer-Peretet, rendkívül pontos feladatokkal bízták meg. Nefer-Peret feladata négy palesztin tehén, két egyiptomi tehén, egy bika és egy bronzvödör gondozása volt. Se több, se kevesebb."
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
            text: "Kertek és köztéri művészet",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A kertek rendkívül népszerűek voltak az ókori Egyiptomban, és a legtöbb házhoz tartozott egy közeli kert is. Amellett, hogy ezekben a kertekben @187gyümölcsöt&és&zöldséget termesztettek étrendjük kiegészítésére, a kertek menedéket nyújtottak a forró nap elől. Sok kertben gondosan ápolt fákat ültettek az árnyék biztosítására. @L@LA művészet elsősorban a város emlékművein és templomain jelent meg. Annyi időt és pénzt fordítottak a templomokra és emlékművekre, hogy a város többi része ezekhez képest meglehetősen sivárnak tűnt."
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
            text: "Kereskedelem",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Bár az ókori Egyiptom bővelkedett természeti erőforrásokban, bizonyos javak hiányoztak az országból. Az egyiptomiak kereskedelmi útvonalakat nyitottak számos közeli országgal és térséggel, többek között Núbiával, Libanonnal, Szíriával, Punttal (amelyet a történészek feltételezése szerint Szomália partvidékével azonosítanak) és az Égei-térséggel. Egyes források szerint az egyiptomi kereskedelem egészen a mai Törökország északi részéig elért. @L@LA Nílus ismét fontos szerepet játszott az egyiptomi kereskedelemben. A folyó az első kataraktáig, vagyis a sziklás vízesések első soráig hajózható volt. Útként szolgált, és viszonylag egyszerűvé tette a Núbiába és onnan történő utazást. @L@LA Nílus Egyiptom egyik fő exportcikkének, a gabonának az előállítását is segítette. Az áradás sokkal megbízhatóbb volt, mint a libanoni és szíriai esőzések. Amíg az áradás rendszeresen bekövetkezett, Egyiptom gabonafelesleggel rendelkezett, ami Libanonban és Szíriában gyakran nem állt rendelkezésre. Egyiptom további exportcikkei közé tartozott a lenvászon, a papirusz, a lencse, a szárított hal, az arany- és ezüstedények, az ökörbőr és a kötél. @L@LCserébe Egyiptom különféle árukat importált. A legfontosabbak közé tartozott a núbiai arany, a libanoni faanyag és a szíriai olívaolaj. Az egyiptomiak más luxuscikkeket is behoztak, például mirhát, bort és állatokat. Alkalmanként fegyvereket is importáltak. @L@LAz árukkal megrakott karavánok különösen ki voltak téve a támadásoknak. Védelmük érdekében fegyveres egységek kísérték a karavánokat kereskedelmi útjaikon. E fegyveres kíséret miatt néhány történész úgy véli, hogy Egyiptom nem szabad kereskedelmet folytatott szomszédaival, hanem inkább kényszerítette őket az áruk átadására. Bár a kényszer valószínűleg szerepet játszott az egyiptomi kereskedelemben, egyes papiruszok Egyiptom és kereskedelmi partnerei közötti tárgyalásokról is beszámolnak. @L@LNéhány sikeres kereskedelmi expedíciót feliratokkal és műalkotásokkal örökítettek meg. Hatsepszut, a női fáraó, hajóflottát küldött Puntba mirha, tömjén, elefántcsont és más értékes áruk beszerzésére. Az út olyan sikeresnek bizonyult, hogy Hatsepszut deir el-bahari templomának falain is megörökítették."
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
            text: "Hajók és hajóépítés",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A Nílus ősidők óta ihlette a hajókészítőket. A dinasztiák előtti korban az ókori egyiptomiak papirusznád kötegeit kötözték össze, hogy tutajokat készítsenek, amelyeket rudakkal hajtottak. A piramisépítés kezdetével megjelent a hajóépítő mesterség. A hajók fontos szerepet játszottak a piramisok építéséhez szükséges nehéz anyagok szállításában. @L@LAz egyiptomi iparágakhoz hasonlóan a hajóépítő műhelyek is állami tulajdonban voltak. Fafeldolgozó eszközökkel felszerelve a hajóépítők először a hajótestet készítették el: a deszkákat egymás mellé fektették, majd facsapokkal, ragasztóval és nedvesség hatására zsugorodó kötelekkel rögzítették őket. Amikor a kötelek összehúzódtak, a hajótest szilárdan összetartott. A nagyobb hajók testét bordákkal erősítették meg. Miután a hajótest elkészült, a hajóépítők felszerelték a hajó többi részét, többek között az árbocot a vitorlához és az evezőnyílásokat. Néhány nagyobb hajón kabinok is voltak. @L@LA hajók széles testűek voltak, és úgy tervezték őket, hogy magasra emelkedjenek a víz felszínén, ami segített nekik fennmaradni. A Nílus ugyan viszonylag könnyen hajózható volt, de akadtak rajta zátonyok és sekély részek, ahol a hajók könnyen megfeneklettek. @L@LA hajóépítők jelentős méretű hajókat készítettek. Egy hajó, amely Hatsepszut templomához szállított obeliszkeket, 89 yard (82 méter) hosszú volt. Az egyik leghíresebb régészeti lelet Hufu bárkája. A Hufu-piramis déli oldalán mintegy 1224 darabban megtalált bárkát az 1960-as évek elején állították helyre. A hajó több mint 46 yard (42 méter) hosszú és 6,5 yard (6 méter) széles, tíz evezős és további két kormányos számára kialakított hellyel. A történészek nem biztosak a hajó jelentőségében. Egyesek szerint Hórusz napbárkáját jelképezte. Mások úgy vélik, hogy ez lehetett a bárka, amely Hufu maradványait a piramisához szállította, vagy amelyet életében használt. Bárhogy is legyen, a hajó fontos betekintést nyújt az egyiptomi hajóépítésbe."
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
            text: "Ellenségek",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Egyiptom gyakran érintkezett szomszédaival, és ezek a kapcsolatok nem mindig voltak barátságosak. Hosszú történelme során Egyiptomot többször is megszállták, és idegenek uralkodtak felette. Ezek az idegen uralkodók azonban felvették a fáraó címet, és a perzsa hódításig az egyiptomiaknak sikerült visszaszerezniük földjüket. Egyiptom azonban nem mindig volt a támadások elszenvedője. Különösen az Újbirodalom idején Egyiptom terjeszkedni kezdett, és számos szomszédos területet meghódított. @L@LEgyiptom háborúzott többek között a núbiaiakkal és a kusitákkal. Egyiptom történelmének korai szakaszában (már i. e. 2900 körül) megtámadta Núbiát, főként annak gazdag arany- és rézlelőhelyei miatt. A késői korban azonban Núbia került fölénybe, és több núbiai fáraó is uralta Egyiptomot. @L@LA Sínai-félszigeten túl több nép is élt, amelyekkel Egyiptom háborúkat vívott. Közéjük tartoztak a kánaániak, a filiszteusok, a beduinok (a mai Szíria területéről) és a hettiták. Ezen ázsiai népek közül azonban a legjelentősebbek a hükszoszok voltak. A második átmeneti korban a hükszoszok uralták Egyiptomot. Sok egyiptomi kulturális szokást megtartottak, és számos újítást vezettek be, például a lovas harci szekeret. Körülbelül 100 évig uralkodtak, míg I. Ahmosze le nem győzte őket és át nem vette a hatalmat. @L@LNyugaton Egyiptom líbiai törzsekkel, különösen a tehenu és temehu népekkel került háborúba. Ezek a törzsek megpróbáltak betelepülni az egyiptomi Deltába, de I. Szetosz keményen visszaszorította őket. @182Erődöket építettek nyugaton, hogy távol tartsák a törzseket. @L@LVégül a hatalmas Római Birodalom a Ptolemaioszok uralma alatt érte el Egyiptom partjait. Egyiptom hanyatló katonai ereje, ám hatalmas kincstára és gabonaraktárai (nem is beszélve a lenyűgöző VII. Kleopátráról) természetesen felkeltették Julius Caesar és utódai kapzsi figyelmét. Caesar római légióinak megérkezése Egyiptom földjére egy hosszú korszak végét jelentette, amelyben Egyiptom meghatározó hatalom volt a Földközi-tenger térségében, és végül a büszke ország vazallusállammá vált. @L@LEgyiptom haderejéről bővebben kattints @184here."
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
            text: "Védelmi építmények",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Egyiptom falakkal és tornyokkal védte városait és településeit. A falak általában téglából készültek, és négyszögletes vagy kör alakban vették körül a várost. Az Egyiptom déli részén, a núbiai határ közelében fekvő Abu (Elephantiné) ásatásai egy vastag, ívelt falat tártak fel, amelyet félkör alakú tornyok szakítottak meg. @L@LEgyiptom határait erődsorozattal védte. Ezek közül az egyik legismertebb a 'Herceg fala', amely a Nílus keleti partján épült 13 erődből álló rendszer volt."
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
            text: "Törvény",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Azok az egyiptomiak, akik sérelmet szenvedtek másoktól, panaszukkal egy bíróhoz fordulhattak. A vétség súlyosságától függően az ügyet egy helyi bíró vagy maga a vezír dönthette el. A helyi bírák néha alacsonyabb rangú tisztviselők voltak a városban, például főmunkások. Az írnokok részt vettek a tárgyalásokon, és feljegyezték a résztvevőket, tanúkat, vallomásokat és büntetéseket. @L@LA törvény mindenkire vonatkozott, a felső és alsó osztályokra egyaránt. Egy óbirodalmi vezír masztabakápolnáján látható jeleneten helyi kormányzókat büntetnek meg az adóbevételek visszatartásáért. A nők is aktív résztvevői voltak a bírósági ügyeknek. Egy esetben egy nő megkapott egy olyan tulajdont, amelyet törvénytelenül követeltek maguknak a rokonai. Egy másik esetben egy nőt bűnösnek találtak abban, hogy szerszámot és edényt lopott Ámon egyik szentélyéből. @L@LA bűncselekmények büntetése igen szigorú lehetett, és gyakran verést vagy kényszermunkát jelentett. Az Újbirodalom XVIII. dinasztiája idején a bőrök ellopásának büntetése 100 ütés és öt nyílt seb okozása volt. Néhány különösen súlyos bűntettet azzal büntettek, hogy levágták a bűnöző orrát, és Egyiptom peremére száműzték. @L@LAz egyiptomi jog nem volt szigorúan kodifikálva, és a legtöbb büntetést egyedi esetek alapján szabták ki. Néhány bűn- és büntetéslista fennmaradt, különösen az Újbirodalomból, de ezek gyakran ellentmondanak egymásnak. @L@LAz igazságosság a túlvilágon is fontos fogalom volt. Mielőtt valaki beléphetett volna a túlvilágra, 'negatív vallomást' kellett tennie, amelyben felsorolta mindazt, amit életében nem követett el. A negatív vallomás után az illető szívét megmérték Maat fejdíszének egy tollával szemben. Ha a szív súlya megegyezett a tolléval, bebocsátást nyert a túlvilágra. Ha nehezebb volt a tollnál, a szívet Ammit, a szörnyű szörnyeteg falta fel, és az illető nem juthatott be a túlvilágra."
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
            text: "Hadsereg",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomi hadsereg a fáraók uralma alatt eltelt több ezer év során fejlődött ki. Az Óbirodalomban a seregeket szükség esetén állították fel, és általában nemesekből, követőikből vagy idegenekből álltak. Az Óbirodalomnak nem volt hivatásos hadserege. A katonák az élet különböző területeiről kerültek ki, és valószínűleg a harcok végeztével visszatértek korábbi foglalkozásukhoz. @L@LAz Újbirodalom idejére azonban a hadsereg felépítése megváltozott. A hadsereg egyértelműen gyalogsági és harci szekér egységekre oszlott. A gyalogság két részre tagolódott: közelharcra szakosodott katonákra és hosszabb hatótávolságú harcban jártas egységekre. A harci szekereket mozgékony távolsági támadásokra használták. Az íjjal és nyíllal felszerelt katonák a szekereken állva lőtték az ellenséget. A tengeri harcok gyakoriak voltak, bár a haditengerészetet nem tekintették a fegyveres erők különálló ágának. A haditengerészet a szárazföldi erők része volt, és a hajókon szolgáló katonákat ugyanazokkal a kifejezésekkel illették, mint a szárazföldi katonákat. Az idegenek ismét jelentős részét alkották a hadseregnek. Núbiaiak, líbiaiak, ázsiaiak és káriaiak mind harcoltak az egyiptomiak oldalán. @L@LAz egyiptomi hadsereg az Óbirodalomban zászlóaljakba szerveződött. Az Újbirodalomban a zászlóaljakat tovább osztották hadosztályokra, amelyeket istenekről neveztek el. Írnokok és hivatalnokok is elkísérték a katonákat a csatába, feltehetően azért, hogy nyilvántartsák az eseményeket. @L@LAz egyiptomi hadsereg fegyvereiről bővebben kattints @196here."
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
            text: "Gabonafélék és árpa",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A gabonatermesztés (búza és árpa egyaránt) biztosította az ókori Egyiptom legalapvetőbb élelmiszerének, a kenyérnek az alapanyagát. A búzából és az árpából is lisztet készítettek, majd kenyeret sütöttek belőlük. Az árpából készült kenyér felhasználásáról további információért lásd: @194Beer. @L@LAz egyiptomiak háromféle búzát használtak: alakor búzát, tönkölyt és kétszemű búzát. A búzát csépléssel dolgozták fel lisztté. A búzaszárakat a földre terítették, majd állatokat vagy más nagytestű jószágokat hajtottak rájuk, hogy megtapossák a búzát. Ez a zúzás kiszabadította a szemeket a kalászokból. Ezután a szemeket rostálással vagy a levegőbe szórással választották el a pelyvától és más szennyeződésektől. A szél elfújta a könnyebb pelyvát, míg a nehezebb búzaszemek a földre hullottak. A feldolgozás után a gabonát a @5gabonatárolókba vitték. Ott a búzát lisztté őrölték és későbbi felhasználásra tárolták. @L@LKenyeret úgy készítettek, hogy lisztből tésztát gyúrtak, majd különböző formájú kerámiaformákba öntötték. A legnépszerűbb forma a kúpos volt. A tésztát forró parázs és hamu által körülvett tűzhelyen sütötték meg. Kenyeret otthonokban és hivatásos pékségekben is sütöttek. A régészek szerint a levegőben lévő nagy mennyiségű hamu miatt a hivatásos pékek talán nem tartoztak a legegészségesebb emberek közé."
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
            text: "Állattenyésztés és halászat",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomiak különféle állatokat tenyésztettek gazdaságokban és állattartó telepeken élelem céljára. Ezek közül a legelterjedtebbek a hosszú szarvú szarvasmarhák voltak. Ezeket pásztorok gondozták, akiket a sírjeleneteken általában sovány, borotválatlan arcú férfiakként ábrázoltak. A marhákat legelőkre hajtották táplálkozni. Néha frissen betakarított földekre küldték őket, hogy a szalmát és a pelyvát megegyék. @L@LAz egyiptomiak juhokat, kecskéket és sertéseket is tenyésztettek, valamint libákat és más szárnyasokat. A lovakat nem élelem céljára tartották, hanem azért, hogy a legelőkelőbb egyiptomiak harci szekereit húzzák. A lovat a hükszószok, Egyiptom egyik @181hódító népe hozta be az országba. @L@LA hal másfajta élelemforrást jelentett, bár úgy tűnik, főként az alsóbb osztályok fogyasztották. Az egyiptomiak többféle módon fogtak halat. Néhányan kenukban ülve horgászbotokat használtak zsinórral és horoggal, így egyenként fogták ki a halakat. Csapdákat is építettek, hogy nagyobb mennyiségű halat ejtsenek el. A leghatékonyabb módszer azonban a kerítőháló használata volt. Mivel a zsákmány igen nagy lehetett, a háló felszínre húzásához két hajónyi emberre volt szükség. @L@LA halászat veszélyes foglalkozás volt. Egyes harcsafajok hátúszóján mérgező tüske található, és mindig fennállt a krokodilok veszélye is. A halászok hajóikban többnyire biztonságban voltak, de ha a hajó felborult, a krokodil ritkán maradt távol."
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
            text: "Gyümölcsök és zöldségek",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A @185gabonafélék és az árpa voltak az ókori egyiptomiak legfontosabb élelmiszerei, de sokféle gyümölcsöt és zöldséget is termesztettek. A bab, a csicseriborsó, a lencse és a zöldborsó nagyon népszerű volt, akárcsak a fokhagyma, a hagyma, a póréhagyma, a saláta és az uborka. Gyümölcsként fügét, datolyát, szőlőt és gránátalmát fogyasztottak. A datolya különösen az alsóbb osztályok körében volt kedvelt, és a sör ízesítésére is használták. Az egyiptomiak ételeiket fahéjjal, korianderrel, köménnyel, kaporral és mustárral is fűszerezték."
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
            text: "Nád",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A papirusznád akár 25 láb magasra is megnőhetett, és Egyiptomban nem csak papírkészítésre használták. A papirusznádból különféle háztartási tárgyakat készítettek, többek között szőnyegeket, szandálokat és köteleket. A növény belsejét élelemként fogyasztották. Néha a szárát fa helyettesítésére használták, a növény szálait pedig összekötötték, és tutajként alkalmazták. A papirusznád majdnem kihalt, de az utóbbi időben újra elterjedt. A papiruszt ismét betakarítják és papírt készítenek belőle – ezúttal turisták számára értékesítik."
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
            text: "Len",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A lent az ókori Egyiptom legfontosabb textilanyagának, a @398vászonnak az előállításához termesztették. Mivel a növény szára volt a legfontosabb része, minden növényt ki kellett húzni a földből, nem pedig levágni, így a len betakarítása lassú folyamat volt. A betakarítás után eltávolították a gyökereket és a magfejeket, majd a szárakat száradni hagyták. Ezután a szárakat két hétre vízbe merítették, majd köveken ütögették és rostokra választották szét őket. A rostokat ezután a takácsokhoz vitték, akik szövetet készítettek belőlük."
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
            text: "Agyag",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az agyag könnyen hozzáférhető volt az ókori Egyiptomban, és minősége területenként változott. A Nílus mentén az évek során bekövetkező áradások gazdag iszaplerakódásokat hoztak létre, amelyeket kiáshattak és edényekké formálhattak. A sivatagi területeken mészkőben található puha márga- és palarétegeket lehetett felfedezni. A sivatagi agyag keményebb kerámiát eredményezett, mint a nílusi agyag, és rózsaszín vagy zöldes árnyalatú tárgyakat készítettek belőle. A nílusi agyagból készült edények általában vörösek vagy feketék voltak. Mindkét agyagtípust ugyanúgy dolgozták fel, hogy @198kerámiát készítsenek belőlük."
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
            text: "Arany és aranybányászat",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Aranyat elsősorban Egyiptom keleti sivatagában és Núbiában találtak. Az arany bányászata nehéz feladat lehetett. A keleti sivatagban például az aranyércek gránitba ágyazódva fordultak elő. A gránitot porrá zúzták, majd vízbe merítették, hogy elválasszák az aranyat a kőzettől. Ez a folyamat rendkívül időigényes lehetett. Ennek ellenére az arany viszonylag bőségesen állt rendelkezésre, és valójában könnyebb volt hozzájutni, mint az ezüsthöz. @L@LAz arany felhasználásra való előkészítéséhez először az aranybányákban megolvasztották. Az olvadt aranyat ezután vízbe öntötték. Ahogy lehűlt, rögökké alakult, amelyeket később az ötvösökhöz vittek felhasználásra. @L@LMint szinte minden más árucikket, az aranykészleteket is szigorúan nyilvántartották az írnokok. Minden reggel gondosan kimérték az aranyat az ötvösök számára, és munkájukat szigorúan felügyelték, hogy biztosan ne lopjanak belőle. @L@LBár az arany bőségesebb volt az ezüstnél, korántsem állt rendelkezésre korlátlan mennyiségben. Emiatt a legtöbb tárgyat aranyozták, ahelyett hogy tömör aranyból készítették volna."
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
            text: "A fa és felhasználása",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az őshonos fák nem voltak bőségesen megtalálhatók Egyiptomban. Bár az árterek talaja elég termékeny volt a fák növekedéséhez, az áradások gyakran még azelőtt kidöntötték őket, hogy megnőhettek volna. Az Egyiptomban mégis megélő fák közé tartozott a szikomorfa, a perzsafa, a datolyapálma és a tormafa. Mindegyikük vallási jelentőséggel bírt, és az istenek lakhelyének tekintették őket. @L@LFontosságuk miatt a favágóknak külön engedélyt kellett szerezniük a fák kivágása előtt. A kivágott fák törékeny fát adtak, amelynek korlátozott volt a felhasználása. Egyiptom faanyagának nagy részét a mai Libanon, Szíria és Izrael területéről importálta. Amikor Egyiptom az Újbirodalom idején végül meghódította ezeket a vidékeket, nagy mértékben kitermelték a fákat, jelentősen csökkentve az erdőállományt. @L@LA fát bútorokhoz, koporsókhoz és épületekhez használták. A famunkások igen ügyesen készítettek bonyolult díszítésű tárgyakat berakásokkal és faragásokkal."
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
            text: "Kőfejtők",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az egyiptomiak többféle követ bányásztak piramisaikhoz, templomaikhoz és emlékműveikhez, többek között mészkövet, gránitot, homokkőt, bazaltot, palát, alabástromot és porfírt. A kőfejtők csákányokkal és vésőkkel termelték ki a kemény köveket, a puhább kövekhez pedig rézfűrészeket használtak. @L@LA legtöbb kőfejtő csak az áradás idején működött, amikor az állami építkezések a csúcspontjukon voltak. Néhány kőfejtő egész évben üzemelt, különösen ha nagy építkezés, például egy piramis építése folyt. @L@LA tömbök szállításához a végső helyükre a köveket szánokra helyezték, majd munkások csapata húzta őket. Gyakran farönköket fektettek le görgőként, megkönnyítve ezzel a folyamatot. Néha vizet öntöttek a szán elé a súrlódás csökkentésére. @L@LA kőfejtők munkaerejének egy részét rabszolgák alkották, bár a dolgozók többsége továbbra is egyiptomi volt."
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
            text: "Sör",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A sör volt az ókori egyiptomiak kedvelt itala. Az egyiptomi sörkészítés részleteiről heves viták folynak. Hogyan készítették a sört? Gyümölccsel ízesítették? Árpasört vagy gabonasört főztek? És mi a helyzet a malátázással? A kutatások jelenleg is folynak, hogy ezekre a kérdésekre választ adjanak. @L@L A sírfalak képei alapján az egyik sörkészítési módszer során az egyiptomiak különleges kenyérlepényt sütöttek. Ezt a kenyeret összetörték és szitába helyezték. Ezután vizet préseltek át rajta, a keletkező folyadékot palackozták és erjesztették. A sörfőzés elsősorban a nők feladata volt, és a papiruszokon körülbelül 17 sörfajtát azonosítottak. @L@LAz egyiptomiak külön erre a célra készített korsókból itták a sört. A korsókat ferde csővel látták el, amely kissé egy szívószálra hasonlított. A cső végén szűrő volt, amely kiszűrte a sörben található szilárd anyagokat. Az otthoni fogyasztás mellett az egyiptomiak kocsmákban és fogadókban is ittak sört. Arról, mi történt ezekben a környékbeli ivóhelyeken, kattints @172ide."
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
            text: "Papírkészítés papiruszból",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A papiruszkészítés meglehetősen összetett folyamat volt. Először eltávolították a papirusznád külső rétegét, hogy szabaddá váljon a belseje. Több növény belsejét egymás mellé fektették egy vászondarabra, kissé átfedve egymást. Amikor elérték a kívánt szélességet, az első rétegre merőlegesen újabb csíkokat helyeztek. Ezután egy másik vászondarabot tettek a tetejére, majd a papiruszt nehéz fadarabbal vagy bunkóval ütötték. Az ütögetés összedolgozta a rostokat. A papiruszt ezután a napra akasztották száradni, és gyakran egy kővel fényesítették a felületét."
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
            text: "Fegyverek",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az ókori egyiptomiak sokféle fegyvert használtak a csatákban. Közelharcban a katonák számos fegyver közül választhattak, például buzogányt, tőrt, széles kardot és harci bárdot használtak. A hosszabb távú harcok elsődleges fegyvere az íj és a nyíl volt, bár nyilvánvalóan parittyákat is alkalmaztak. Az egyiptomi fegyverzet az idők során fejlődött, és nagy előrelépést tett a hükszószok inváziója után. A hükszószok vezették be a lovakat és a harci szekereket az egyiptomi hadviselésbe."
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
            text: "Luxuscikkek",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Az élelem, az ital és a ruházat elegendő volt a parasztok számára, de az ókori Egyiptom felsőbb osztályainak számos termékre volt szükségük életmódjuk fenntartásához. Ezek közül a legfontosabb luxuscikk a smink volt. Férfiak és nők egyaránt használtak szemfestéket, például kohl-t vagy malachitot. A megjelenés javítása mellett az egyiptomiak úgy hitték, hogy a szemfesték védi a látásukat. A nők hennát is használtak körömlakként, és néha hajfestékként. @L@LA tisztaság fontos volt az ókori egyiptomiak számára, és a rendszeres fürdés mellett különféle olajokkal és kivonatokkal illatosították magukat. Erre a célra mirhát és tömjént is használtak. @L@LA tisztasághoz kapcsolódott a parókák használata is. A legtöbb egyiptomi rövidre vágta a haját, valószínűleg a tetvek elkerülése érdekében, és parókával díszítette a fejét. A parókák különböző stílusokban készültek, és a legtöbb nőnek több is volt belőlük. A parókák általában emberi hajból készültek, amelyet zsinórral erősítettek az alapjukhoz. @L@L@382Az ékszerek szintén népszerű luxuscikknek számítottak a gazdagok körében."
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
            text: "Kerámia",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "Nagyon kevés otthon nélkülözte a kerámiaedényeket. A kerámiakészítés, az ókori Egyiptom egyik legrégebbi iparága, eredetileg az otthonokban kezdődött, ahol a nők elkészítették a főzéshez szükséges edényeket. Egyiptom más iparágaihoz hasonlóan a kerámiakészítés is az otthoni környezetből műhelyekbe került. @L@LA kerámia készítésének első lépése az @190agyag előkészítése volt. Az agyagot át kellett gyúrni, és gyakran szalmát vagy pelyvát kevertek hozzá kötőanyagként. A férfiak kézzel vagy lábbal gyúrták az agyagot, rálépve, hogy megmunkálhatóvá váljon. Ezután az agyagot korongra helyezték, hogy formát adjanak neki. @L@LA fazekaskorong az idők során fejlődött. A legkorábbi változatnál a fazekas egyik kezével forgatta a korongot, miközben a másikkal formázta az agyagot. Mivel a korongot nem tudta túl gyorsan forgatni, az edényeket később kézzel kellett elsimítani. Az Újbirodalom idején egy második személy két kézzel forgatta a korongot, miközben a fazekas megformázta az edényt. Ez sokkal simább készterméket eredményezett. Az Újbirodalom végére a fazekas ismét maga forgatta a korongot, ezúttal a lábával, ami minden korábbinál simább kerámiát eredményezett. @L@LAz edények megformázása után hagyták őket megszáradni. A darabokat a száradás alatt díszítették. Száradás után kemencében kiégették őket. A kemence nagy építmény volt, amelynek alján tűztér helyezkedett el. A tűzteret egy agyagrács választotta el a felső kamrától. A kerámiát erre a rácsra helyezték. A felső kamrát lezárták, kivéve egy nyílást, amelyen a füst távozhatott. Az égetés befejezése után a készterméket tárolták, amíg szükség nem volt rá."
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
            text: "Bazár",
                pos [125, 15]
        }
        subtitle {
            text: "Történelem",
        }
        content {
            text: "A bazárok zajos és zsúfolt helyek voltak. A kereskedők, férfiak és nők egyaránt, kipakolták áruikat, a vásárlók pedig olyan termékekkel érkeztek, amelyeket ezekre az árukra cseréltek. A bazárok általában a Nílus közelében helyezkedtek el, hogy kihasználják a hajókkal érkező új árukat. @L@LA bazárjeleneteket gyakran ábrázolták a sírfalakon. Az ötödik dinasztia idején élt Hnumhotep és Niankhkhnum, a fáraó manikűröseinek sírja élénk piaci jelenetet mutat be, amelyen egy idomított majom is látható, amint megharapja egy tolvajlással próbálkozó ember bokáját."
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
            text: "Egy falu születése",

        }
        content {
            text: "@PÜdvözlünk az ókori Egyiptomban, a fáraók földjén! Itt részese lehetsz a világ egyik legnagyobb civilizációja történelmének egy epikus történetben, amely több mint tizenöt évszázadon és két tucat nemzedéken átível. Egyetlen családot kell vezetned nemzedékről nemzedékre, az egyiptomi történelem előtti idők kezdeti éveitől a civilizáció hajnalán át... egy egyedülálló és hatalmas birodalom megszületéséig... és azon túl.     @PTörténetünk több mint ötezer évvel ezelőtt kezdődik a Nílus folyó partján, egy Nubt néven ismert területen. Itt klánok kis szövetsége küzd azért, hogy megéljen a zord környezetben. Családod vezetésével ez a kis település fejlődésnek indul."
        }
    }
    message_history_thinis_2 {
        id: 201,
            type: 3,
            size [40, 30]
        title {
            text: "Thinisz",

        }
        subtitle {
            text: "A civilizáció hajnala",

        }
        content {
            text: "@PÉvek múltán, egy nemzedék elteltével családod újra letelepedett Thinisz vidékén, Felső-Egyiptomban. Itt helyi uralkodók egy kisebb csoportja megpróbálja kiterjeszteni hatalmát Alsó-Egyiptom és a Nílus teljes vidéke fölé, valamint saját dinasztiája vezetése alatt egyesíteni ezt a birodalmat egyetlen legfőbb uralkodóval. @PThinisz virágzó várossá fejlesztése, amelyhez hasonlót még soha nem látott a világ, bizonyítja majd a thiniszi szövetség rátermettségét, és segít nekik megszerezni a fennhatóságot Alsó-Egyiptom és a hatalomért versengő többi csoport felett. Idővel ez azt is jelenti majd, hogy szórakozást kell biztosítani a lakosságnak, valamint pompás templomokat kell építeni a vidék védőistenségének tiszteletére. @PEgy ilyen nagyszabású város felépítéséhez jelentős mennyiségű pénzre lesz szükség. Thiniszben gazdag aranyérc-lelőhelyeket találsz, ezért kitermelésük legyen az elsődleges feladatod."
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
            text: "A bizonytalan Nílus",

        }
        content {
            text: "A thiniszi nemesek továbbra is küzdenek azért, hogy a Nílus vidékét egyetlen legfőbb uralkodó alatt egyesítsék. Ügyük támogatására remélik, hogy virágzó közösséget hozol létre Perwadjytban, Alsó-Egyiptom nedves deltavidékén, így kiterjesztve befolyásukat a szent folyó teljes hosszában. Egy falunál nagyobb népesség eltartásához meg kell tanulnod a mezőgazdaság használatát. @PAz egyiptomi földművesek már elkezdték kihasználni a Nílus évenkénti áradása által lerakott gazdag, termékeny talajt a növénytermesztéshez. A Nílus azonban veszélyes is lehet. Partjai és vizei számos veszélyt rejtenek, például halálos krokodilokat, vízilovakat és maláriát terjesztő szúnyogokat."
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
            text: "Az első fáraó",

        }
        content {
            text: "Miközben a Nílus mentén élő emberek továbbra is küzdenek a túlélésért ebben a zord környezetben, egy Narmer nevű helyi király hatalomra jutott. Bár Narmer uralma alatt áll e föld nagy része, a két királyság teljes egyesítése még nem valósult meg. Trónra lépésének emlékére Narmer azt kívánja, hogy családod alapítson és vezessen egy új várost Nekhenben. A városban Egyiptom számos istenének templomai és sokféle szórakozóhely lesz."
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
            text: "Egy főváros alapítása",

        }
        content {
            text: "Hosszú küzdelem után Hor-Aha királynak sikerült egyesítenie Felső- és Alsó-Egyiptom kettős királyságát, és egész Egyiptom fáraójának kiáltotta ki magát! Teljes hatalmának és Egyiptom első dinasztiájának megalapítása jeleként Hor-Aha elrendelte egy hatalmas főváros alapítását Men-neferben, ahonnan kormányozhatja ezt a fiatal nemzetet. Családod sok nemzedéken át tartó hűséges szolgálatáért a fáraó téged választott ki e nagyszerű város megtervezésére. Mivel a főváros királyságunk valódi jelképe, lakóinak olyan életminőséget kell élvezniük, amely eddig ismeretlen volt ezen a földön. Ennek érdekében idővel kereskedned kell majd a birodalom más városaival, és magasabb szintű oktatást kell biztosítanod legalább néhány polgár számára. Emellett szent masztabasírt is kell építened a város nemeseinek."
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
            text: "Expedíció a Sínai-félszigetre",

        }
        content {
            text: "Új fáraó, Den lépett Egyiptom trónjára. A fáraó mély aggodalommal tekint a helyzetre, mivel ellenségek kezdték fenyegetni határainkat, és nemzetünk nem rendelkezik elegendő értékes rézzel ahhoz, hogy fegyvereket készítsünk katonáink felszerelésére. Den fáraó bányászati expedíciót rendelt el a könyörtelen Sínai-félszigetre, határainkon túlra, mélyen a beduinok területére. A Timna néven ismert vidék gazdag arany- és rézércben, valamint értékes türkiz drágakövekben, de egyébként kopár terület. A körülmények zordak lesznek, és számos szükséges árut, talán még élelmet és finom vásznat is Egyiptomból kell majd behoznod. A fáraó gyakori szállítmányokat fog követelni a Sínai-félszigetről, és pénzt, rezet, drágaköveket, valamint fegyvereket kér majd tőled. Ezen áruk feleslegét felhasználhatod az expedíció támogatására. Mindig légy óvatos, mert a Sínai-sivatag beduinjai félelmetes ellenfelek, és nem fogják önként megengedni, hogy idegenek elfoglalják földjüket, még kevésbé azt, hogy kifosszák ásványkincseiket. @P A város lakóinak terheit enyhítendő, amelyeket ezek az életkörülmények rónak rájuk, építs pavilont egy forgalmas útkereszteződésnél. A polgárok a pavilon zsonglőr- és zenei színpadain pihenhetnek, és ha tánciskolát is építesz, ez az új előadási forma nagyszerű szórakozást biztosít."
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
            text: "A fáraó haditengerészete",

        }
        content {
            text: "Egyiptom katonai ereje immár páratlan az ismert világban, de az új fáraó, a második dinasztiából származó Khasekhemwy most erős haditengerészetet is követel Behdet központtal. Csak egy teljes hadihajóflotta biztosíthatja számunkra a tengerek feletti uralmat, azonban a faanyag ritka, mivel éghajlatunk csak néhány gyér erdős terület fennmaradását teszi lehetővé. Cédrust nagy költséggel importálhatunk Bübloszból, a tőlünk északkeletre fekvő libanoni területekről. Szerencsére a hazai papirusz exportja lehetőséget biztosít majd ennek a kiadásnak az ellensúlyozására."
        }
    }
    message_history_abedju {
        id: 207,
            type: 3,
            size [40, 30]
        title {
            text: "Abedju",

        }
        subtitle {
            text: "A tenger kihívása",

        }
        content {
            text: "Abedju, őseink temetkezési helye, az évek során hatalmas, szent sírokból álló nekropolisszá fejlődött. Most a legtöbb nemes férfi és nő ezt kívánja örök nyughelyéül választani. Tiszteletükre a második dinasztia új fáraója, Khasekhemwy elrendelte három szent masztabasír építését (az egyik nagyobb méretű a másik kettőnél) a helyi nemesség számára. @PA fáraó emellett erős haditengerészet létrehozását is elrendelte Behdet központtal. Abedjunak szintén támogatnia kell egy kisebb harci hajóflottát, ha partjaink teljes biztonságát meg akarjuk őrizni. Ez nem lesz könnyű, mivel a faanyag ritka, és éghajlatunk csak néhány gyér erdős területet tart fenn. Cédrust nagy költséggel importálhatunk Bübloszból, a tőlünk északkeletre fekvő libanoni területekről. Szerencsére a hazai papirusz exportja lehetőséget biztosít majd ennek a kiadásnak az ellensúlyozására."
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
            text: "Az út Afrikába",

        }
        content {
            text: "@PÚj fáraót, Nebkát kiáltották ki, ezzel kezdetét vette az egyiptomi uralkodók harmadik dinasztiája. Nebka nagy szervezettséget és rendet hozott Egyiptomba, elrendelve, hogy egész birodalmunkat körzetekre, vagyis nomoszokra osszák, amelyek élén egy helyi uralkodó, a „nomarkha” áll. Bár ez a rendszer merevnek tűnhet, vezetése alatt Egyiptom fejlődött és gyarapodott, valamint nagy eredményeket ért el a művészet és az építészet terén. @L@PA kereskedőkaravánok, amelyek oázisról oázisra haladva érkeznek Afrika belsejének mélyéről, számos ritka és különleges luxuscikkel látják el Egyiptomot, amelyek népünk körében nagy becsben állnak. Sajnos ezeket a karavánokat rendszeresen megtámadják líbiai harcosok, sőt a keleti sivatag beduinjai is. E kereskedelmi útvonalak biztosítása érdekében Nebka fáraó, a Nád és a Méh Ura, azt kívánja, hogy katonai állomást hozz létre a Selima-oázisban, a karavánkereskedelem központjában, messze birodalmunk határain túl. @L@POtt néhány faanyagnak alkalmas fát találsz, amelyek eladásából pénzt szerezhetsz az őrhely létrehozásának finanszírozására. Fegyverek készítéséhez rezet szerezhetsz a Sínai-félszigeten, Timna újonnan létesített bányáiból. @L@PA Selima-oázisból ébenfát importálhatsz az afrikai Kermából. Ha sikeresen létrehozod ezt az állomást, megbízható ébenfa-forrást biztosít majd birodalmunk minden városa számára."
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
            text: "A núbiai határ",

        }
        content {
            text: "@PÚj fáraót, Nebkát kiáltották ki, ezzel kezdetét vette az egyiptomi uralkodók harmadik dinasztiája. Nebka nagy szervezettséget és rendet hozott Egyiptomba, elrendelve, hogy egész birodalmunkat körzetekre, vagyis nomoszokra osszák, amelyek élén egy helyi uralkodó, a „nomarkha” áll. Bár ez a rendszer merevnek tűnhet, vezetése alatt Egyiptom fejlődött és gyarapodott, valamint nagy eredményeket ért el a művészet és az építészet terén. @P A fáraó azt kívánja, hogy birodalmunk határait délebbre, Núbia felé terjesszük ki. Elrendeli, hogy várost alapítsunk a Nílus első kataraktájánál, Abu szigetén, hogy kihasználhassuk az ott található bőséges drágakő-, gránit- és homokkőlelőhelyeket. @PAbedju növekvő nekropoliszának szüksége van ezekre az anyagokra, hogy egyre díszesebb sírokat készíthessenek a nemesség számára. Men-nefer fővárosának is szüksége lehet téglára a sírok építéséhez, és Nebka fáraó engedélyezheti ezek és más építőanyagok igénylését. @PNebka fáraó azt is elrendelte, hogy egyik társad katonai állomást hozzon létre a Selima-oázisban, biztosítva az Afrika belsejébe vezető karavánútvonalakat. Miután az állomás elkészült, a Selima-őrséget az importált ébenfa forrásaként használhatod, amely nagyra értékelt luxuscikk."
        }
    }
    message_history_saqqara {
        id: 210,
            type: 3,
            size [40, 30]
        title {
            text: "Szakkara",

        }
        subtitle {
            text: "Az első piramis",

        }
        content {
            text: "Dzsószer fáraó trónra lépése új korszakot hozott Egyiptom számára a bölcsesség, a tudás és a művészi teljesítmény terén. Szakkarában királyi temetőt kell létrehozni, amely örök nyughelyül szolgál majd olyan nemesek számára, mint Hezyre és Khabausokar, a fáraó megbízható udvarnokai. @PDe ez a hely egy olyan emlékműnek is otthont ad majd, amelyhez hasonlót a világ még soha nem látott. Én, Imhotep, a fáraó királyi vezírje, a fáraó számára egy újfajta szent sírhelyet terveztem. A korábbi fáraók alacsony vályogtégla masztabáival ellentétben ez a sír az ég felé fog emelkedni, mintha több egymásra helyezett masztabából állna. Ráadásul ez a „lépcsős piramis” teljes egészében kőből épül, hogy ellenálljon az idők végtelen múlásának. Mélyen belül egy tömör gránitból készült szarkofág őrzi majd a fáraó testét örök nyughelyén. @PAbedju nekropoliszának papjai tökélyre fejlesztették a halottak lenvászonnal történő bebalzsamozásának művészetét, így megnyitva az örök élet kapuját minden egyiptomi előtt. @PA Selima-oázisnál lévő kereskedelmi állomásunk továbbra is virágzik, és onnan ébenfát importálhatsz Afrikából. @PA fáraó bőséges pénzösszeget biztosított számodra a projekt megkezdéséhez. Ne okozz neki csalódást."
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
            text: "A keleti beduinok",

        }
        content {
            text: "Den fáraóhoz hasonlóan Huni fáraó is expedíciót rendelt el a zord Sínai-félszigetre türkiz drágakövek és réz megszerzésére. Azt kívánja, hogy vezesd ezt az expedíciót egy Serabit Khadim nevű helyre, ahol egy korábbi egyiptomi őrhely épületmaradványai még megtalálhatók lehetnek. Jelenlegi állapotuk ismeretlen, de talán még mindig nyújthatnak némi védelmet az expedíció számára. @PTudnod kell, hogy az utolsó, erre a vidékre küldött expedíció soha nem tért vissza. Egy később utánuk küldött mentőexpedíció sem tért vissza. Ennek ellenére, ha megfelelően fel akarjuk fegyverezni katonáinkat, királyságunknak rézre van szüksége fegyverek készítéséhez, és ez a fém ritka földjeinken. @PKészülj fel, mert állandó támadás fenyeget majd a Sínai-sivatag beduinjai és ellenségeink, a kánaániták részéről. Ilyen körülmények között bányássz ki annyi rezet és drágakövet, amennyit csak tudsz, és időben teljesítsd a fáraó kéréseit. Ékszerészeket alkalmazhatsz, hogy a felesleges drágakövekből ékszereket készítsenek a település lakói számára."
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
            text: "Királyi nekropolisz",

        }
        content {
            text: "Huni fáraó örök nyugalmat kíván tölteni egy Dzsószeréhez hasonló lépcsős piramisban. Azt szeretné, hogy nemeseinek sírjai vegyék körül, ezért Meidumot választotta ki Alsó-Egyiptomban ennek a királyi nekropolisznak a helyszínéül. @P Házad sok nemzedéken át tartó hűséges szolgálatának elismeréseként Huni azt is engedélyezte, hogy saját sírodban temessenek el Meidumban. Ezzel nagy megtiszteltetésben részesítette családodat. @PEgyiptom bölcsességének és tudásának megőrzése érdekében Huni fáraó királyi könyvtárak építését is szorgalmazza. A papirusztekercsekkel megtöltött könyvtárak magasabb szintű oktatást biztosítanak majd a felsőbb osztályok számára. @PA fáraó egyik hűséges udvaroncát újabb expedícióra küldte Serabit Khadimba, a zord Sínai-félszigetre, hogy türkiz drágaköveket szerezzen. Ha az expedíció sikerrel jár, drágaköveket importálhatsz onnan. Az ékszerészek ezekből ékszereket készíthetnek, amelyek értékes luxuscikként szolgálnak majd városod lakói számára. @PAz egykor virágzó Behdet városa hanyatlásnak indult, és már nem exportálja nagy mennyiségben azokat az árukat, amelyekről korábban ismert volt."
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
            text: "Terjeszkedés Núbiába",

        }
        content {
            text: "Új fáraónk, Sznofru, eltökélte, hogy ez a negyedik dinasztia lesz Egyiptom valaha uralkodott legnagyobb dinasztiája. A fáraó azt kívánja, hogy határainkat még délebbre terjesszük ki. Ezért elrendelte Núbia meghódítását, valamint egy megerősített város alapítását Buhenben, a Nílus második kataraktája mellett. Ott egy gránitobelszket is fel kell állítanod, amely örök jelképként hirdeti, hogy ez a vidék Egyiptomhoz és a fáraóhoz tartozik. Ilyen messze délen azonban nem található gránit, ezért Abuból kell importálnod. @PBuhenben vad és tapasztalt núbiai harcosokkal találkozol majd, akik életük árán is megpróbálják megakadályozni, hogy ilyen messze délen megvessük a lábunkat. Ne csüggedj, mert a Katonai Akadémián végzett szigorú kiképzés után harcosaid maguk is tapasztalt veteránokká válhatnak. Ráadásul hadmérnökeink tökéletesítették több védelmi építmény, például az erődített tornyok, falak és kapuházak tervezését. Ezek felbecsülhetetlen segítséget nyújtanak majd a núbiai sereg támadásainak kivédésében. Szállítóhajókat is alkalmazhatsz, hogy szükség esetén vízen mozgathasd seregedet. @PÉszakon kapcsolatokat létesítettünk Enkomival, Ciprus szigetén. Ez a föld gazdag rézérckészleteiről kapta nevét, és most már vásárolhatunk tőlük rezet. A Sínai-félszigeten, Serabit Khadimnál nemrég létrehozott egyiptomi bányaközösségnek köszönhetően azonban kormányzóinkat sokkal kedvezőbb áron tudjuk rézzel ellátni. A Serabit Khadimból érkező szállítmányok gyakran bizonytalanok a települést érő állandó beduin és kánaánita támadások miatt, és nem tudjuk, meddig képesek még kitartani az ott állomásozó egyiptomi erők. @PA fáraó temetkezési helye, egyedülálló és lenyűgöző emlékmű, jelenleg építés alatt áll Dahsúrban. A fáraó időről időre kérheti, hogy mészkővel járulj hozzá a projekt befejezéséhez."
        }
    }
    message_history_south_dahshur {
        id: 214,
            type: 3,
            size [40, 30]
        title {
            text: "Déli Dahsúr",

        }
        subtitle {
            text: "Sznofru tört piramisa",

        }
        content {
            text: "@PÚj fáraónk, Sznofru, eltökélte, hogy ez a negyedik dinasztia lesz Egyiptom valaha uralkodott legnagyobb dinasztiája. Építészei egy Huni lépcsős piramisánál is lenyűgözőbb síremléket terveztek, és a fáraó azt kívánja, hogy felügyeld az építését. Megfelelő méretű települést kell alapítanod Dahsúrtól délre, a fáraó tört piramisának helyszínén. Ha elkészül, ez a város biztosítja majd a munkaerőt ehhez a nagyszabású projekthez. @PA tört piramis egyszerű kőmagból épül, amelyet finom fehér mészkővel burkolnak, hogy örökké ragyogjon a sivatagi nap alatt. Dahsúrban elegendő mészkövet találsz, de a szükséges mennyiségű egyszerű követ importálnod kell ehhez az építkezéshez. @PA fáraó azt kívánja, hogy határainkat még délebbre terjesszük, ezért katonai erőket küldött Núbia meghódítására, valamint egy megerősített város létrehozására Buhenben, a Nílus második kataraktája mellett. @PÉszakon Egyiptom kapcsolatokat létesített Enkomival, Ciprus szigetén. Ez a föld gazdag rézérckészleteiről ismert, amelyek most fontos importcikknek számítanak. @PÉrtékes drágaköveket szerezhetsz a Sínai-félszigeten, Serabit Khadimnál létrehozott egyiptomi őrhelyről. Az ellátás azonban az utóbbi időben bizonytalanná vált a települést érő állandó beduin és kánaánita támadások miatt, és nem tudjuk, meddig képesek még kitartani az ott állomásozó egyiptomi erők."
        }
    }
    message_history_north_dahshur {
        id: 215,
            type: 3,
            size [40, 30]
        title {
            text: "Északi Dahsúr",

        }
        subtitle {
            text: "Az igazi piramis",

        }
        content {
            text: "@PSznofru fáraó rendet teremtett Egyiptomban, és a királyság most bölcs és jóindulatú uralma alatt virágzik. Sznofru újabb építkezési projektet kíván megvalósítani Dahsúrban, amely még a már elkészült tört piramisnál is nagyszabásúbb. A királyi építészek, földmérők és mérnökök biztosak benne, hogy olyan építményt tudnak létrehozni, amelynek oldalai egyetlen folyamatos szögben emelkednek, és tökéletes csúcsban találkoznak. Ha sikerrel járnak, ez lesz az első valódi piramis, és méltó otthona lesz Sznofru fáraónak az örökkévalóságon át! @PA fáraó felesége, Hetepheresz királyné nemrég fiút szült, akit „Kheopsznak” neveztek el. Népünk aggodalommal tekint jövőbeli uralkodásának napja elé, mert Hórusz, a fáraók istenének látnokai azt jósolták, hogy nem fogja apja jóindulatát tanúsítani népünk iránt. Bár sok nagy dolgot fog véghezvinni, attól tartanak, hogy könyörtelen zsarnokként fogja uralni Egyiptomot. @PBübloszból fát szerezhetsz, mivel az ácsoknak számos rámpát kell építeniük, hogy a munkások feljuthassanak e hatalmas piramis csúcsára."
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
            text: "Egyiptom védelme",

        }
        content {
            text: "@PKheopsz fáraó elfoglalta a trónt, és ahogy Hórusz és Ré látnokai megjósolták, népünk máris szenvedni kezdett elnyomása alatt. @PKheopsz elrendelte, hogy egy királyi kormányzót azonnal küldjenek Iunetbe, hogy megvédje földünket a kusita betörőktől. Iunet egy kisebb halászati iparágat képes fenntartani, amely egy ideig elláthatja ezt a települést. Ha azonban a kusiták vízen támadnak, a folyó veszélyessé válhat a halászhajók számára, és a part menti területeket inkább hadihajóflotta fenntartására lehet használni. Ha az élelem szűkössé válik, marhákat is tenyészthetsz hús biztosítására, de a csordáknak sok szalmára van szükségük takarmányként, és ezen a vidéken nehéz szalmát termeszteni. Más városokkal kell kereskedned szalmáért, mert erre lesz szükséged a masztabád tégláinak elkészítéséhez is. @PLibanon cédrusföldjén fekvő Büblosz városa kereskedni kezdett kelet hatalmas birodalmaival. Ezek Asszíria és Ur a „Mezopotámia” nevű földön, a két nagy folyó között, és rajtuk keresztül Bübloszon át a legfinomabb elefántcsont is megszerezhető. Az ilyen ritka és különleges luxuscikkek érkezésével Iunet biztosan virágzásnak indul. @PA fővárosban az egyiptomi nép megkedvelte a szenet nevű társasjátékot. Ezt a játékot általában egy korsó sör mellett élvezik egy „Szenetház” nevű nyilvános találkozóhelyen. Az ilyen helyek kellemes kikapcsolódást nyújthatnak Iunet lakóinak Kheopsz uralmának zsarnoksága elől. @PKheopsz fáraó elrendelte, hogy Onnál, a delta vidékén számtalan kőfejtőt nyissanak, hogy hatalmas mennyiségű finom fehér mészkövet termeljenek ki. Csak az istenek tudják, milyen célra tervezi a fáraó felhasználni ezt a követ. A szóbeszéd szerint hatalmas építkezést tervez a Rosztja melletti fennsíkon, hogy túlszárnyalja apja, a bölcs és jóindulatú Sznofru hírnevét, aki két nemes piramisának befejezésével szerzett dicsőséget."
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
            text: "Elefántcsont keletről",

        }
        content {
            text: "@PKheopsz fáraó elfoglalta a trónt, és ahogy Hórusz és Ré látnokai megjósolták, népünk máris szenvedni kezdett elnyomása alatt. A szóbeszéd szerint hatalmas építkezést tervez a Rosztja melletti fennsíkon, hogy túlszárnyalja apja, a bölcs és jóindulatú Sznofru hírnevét, aki két nemes piramisának befejezésével szerzett dicsőséget. @PKheopsz fáraó elrendelte, hogy Túránál, a delta vidékén kőfejtők egész csoportját nyissák meg, ahol nemrég gazdag finom fehér mészkőlelőhelyeket fedeztek fel. Három masztabasírt is kell építened e vidék nemeseinek, hogy a fáraó tiszteletét fejezhesse ki odaadásukért. Az általad alapított kőfejtőtelep neve „On” lesz, és hosszú éveken át bőséges forrása marad a finom fehér mészkőnek... bár csak az istenek tudják, milyen célra tervezi a fáraó felhasználni. @PLibanon cédrusföldjén fekvő Büblosz városa kereskedni kezdett kelet hatalmas birodalmaival. Ezek Asszíria és Ur a „Mezopotámia” nevű földön, a két nagy folyó között, és rajtuk keresztül Bübloszon át a legfinomabb elefántcsont is megszerezhető. Az ilyen ritka és különleges luxuscikkek érkezésével On biztosan virágzásnak indul. @PKheopsz egy királyi kormányzót is küldött Iunetbe, hogy megvédje földünket a kusita betörőktől. A királyi vezírek együttérzéssel tekintenek a kormányzóra, akire ez a nehéz és veszélyes feladat hárult. @PA fővárosban az egyiptomi nép megkedvelte a szenet nevű társasjátékot. Ezt a játékot általában egy korsó sör mellett élvezik egy „Szenetház” nevű nyilvános találkozóhelyen. Az ilyen helyek kellemes kikapcsolódást nyújthatnak On lakóinak Kheopsz uralmának zsarnoksága elől."
        }
    }
    message_history_rostja {
        id: 218,
            type: 3,
            size [40, 30]
        title {
            text: "Rosztja",

        }
        subtitle {
            text: "A nagy piramis és a szfinx",

        }
        content {
            text: "Kheopsz fáraó végre nyilvánosságra hozta terveit, és határtalan becsvágya bizonyosan súlyos terhet ró majd népünkre. A fáraó egyszerre átkoz és áld benneteket, mert bár megkaptad a nomarkha rangját, rád bízták a valaha földünkön vállalt legnagyobb építkezési projekt megvalósítását is. @PA fáraó örök nyughelye egy hatalmas piramisegyüttes lesz, amelyet minden várostól távol, a Rosztja melletti fennsíkon építenek fel. Szarkofágja tömör gránitból készül, temetési bárkája pedig a drága libanoni cédrusból. A fáraó piramisegyüttese mellett egy kisebb piramist is építenek fiának, Hafré hercegnek, akinek zsarnoksága vetekszik apjáéval, bár tettei nem. Hafré azt is elrendelte, hogy képmását az élő sziklába véssék Rosztjánál egy hatalmas „szfinx” nevű alakzatként, amelynek teste oroszláné, feje pedig emberé. @PAz emlékmű elkészítéséhez szükséges hatalmas építkezési munkálatok támogatására nagy települést kell alapítanod Rosztjánál. Emiatt a körülmények nem lesznek különösebben kifinomultak, hiszen egyetlen célod e három nagyszerű építmény befejezése és a fáraó tiszteletének kivívása. @PA piramisok külső burkolatához szükséges finom fehér mészkő egy részét biztosítják számodra, de a szükséges anyagok nagy részét a város saját pénzéből kell megvásárolnod. @PA fáraó rád, egyik királyi nomarkhájára bízza ezt a három szent feladatot. Bizonyítanod kell iránta való rendíthetetlen odaadásodat, és teljesítened kell kívánságait... bármi legyen is az ára."
        }
    }
    message_history_bahariya_oasis {
        id: 219,
            type: 3,
            size [40, 30]
        title {
            text: "Bahariya-oázis",

        }
        subtitle {
            text: "A nyugati sivatag",

        }
        content {
            text: "@PKheopsz és Hafré uralma véget ért, és velük együtt lezárult az egyiptomi uralkodóházak negyedik dinasztiája is. Ám Khentkausz úrnő, e család távoli rokona, életet adott egy új fáraónak, akit „Uszerkafnak” neveztek el, így a királyi vérvonal megszakítás nélkül folytatódik. Uszerkaf trónra lépésével kezdődik az ötödik dinasztia, egy korszak, amely nagy változásokat ígér. @PUszerkaf valamelyest decentralizálta országunk irányítását, és nagyobb hatalmat adott a helyi vezetőknek. Most a hozzád hasonló nomarkhák szabadabban intézhetik saját ügyeiket. A fáraó nem hatalmas sír építését tervezi örök nyughelyéül, hanem más feladatot szán neked. @PA fáraó Ré napistent, a királyság istenét az istenek királyává nyilvánította, és fennhatóságát az egész országban ki akarja hirdetni. Sok naptemplom tarkítja már Egyiptom földjét, de a fáraó Ré hatását királyságunk legtávolabbi vidékeire is ki akarja terjeszteni. @PEhhez megerősített települést kell építened a Bahariya-oázisnál, messze a nyugati sivatag mélyén. Bölcsen használd fel az ott található vizet, mert ilyen távol a drága Ní­lustól még a kevés fellelhető vizet is gyakran a sivatag vadállatai áhítják. Óvakodnod kell a líbiai harcosok és a sivatagi beduinok támadásaitól is, akik az utóbbi időben gyakran zaklatták a sivatagi karavánokat. Gondosan tervezd meg védelmedet, és használd fel az oázisban található minden erőforrást, például a fát és a vadállományt."
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
            text: "A Naptemplom",

        }
        content {
            text: "@PKheopsz és Hafré uralma véget ért, és velük együtt lezárult az egyiptomi uralkodóházak negyedik dinasztiája is. Ám Khentkausz úrnő, e család távoli tagja, életet adott egy új fáraónak, akit „Uszerkafnak” neveztek el, így a királyi vérvonal megszakítás nélkül folytatódik. Uszerkaf trónra lépésével kezdődik az ötödik dinasztia, egy korszak, amely nagy változásokat ígér. @PUszerkaf valamelyest decentralizálta országunk irányítását, és nagyobb hatalmat adott a helyi vezetőknek. Most a hozzád hasonló nomarkhák szabadon intézhetik saját ügyeiket. A fáraó nem hatalmas sír építését tervezi örök nyughelyéül, hanem más feladatot szán neked. @PA fáraó Ré napistent, a Nap és a királyság istenét az istenek királyává nyilvánította, és fennhatóságát az egész országban ki akarja hirdetni. Sok naptemplom található már Egyiptomban, de a fáraó azt kívánja, hogy a legnagyobb Djeduban, Alsó-Egyiptom nedves delta vidékén álljon. @PA delta legtöbb részéhez hasonlóan Djedu is gazdag vadban, halban és más élővilágban, valamint növényzetben, de kevés ásványkinccsel rendelkezik. Ezért a Naptemplom építéséhez szükséges homokkövet a Dunqul-oázis kőfejtőiből kell importálni. Marhákat is tenyészthetsz itt hús biztosítására, de a csordáknak sok szalmára van szükségük takarmányként. @PTerületet kell megtisztítanod, hogy megfelelő helyet alakíts ki a Naptemplom számára. Először mindenképpen adj el elegendő mennyiséget az értékes fából, amelyet kitermelhetsz, mert ha elfogy, később talán nem tudsz többet szerezni. Behdetnek és Abedjunak mindig szüksége van fára és vadra, ezért a velük folytatott kereskedelem segíthet ellensúlyozni e szent emlékmű építésének költségeit."
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
            text: "A kusita fenyegetés",

        }
        content {
            text: "@PPepi elfoglalta a trónt, és családodat kancellári rangra emelte, de ennek ára volt. @PA központosított hatalom tovább gyengül, miközben a helyi és tartományi vezetők egyre erősebbé válnak. Egyes vidékeken a termés jóval elmarad a megszokottól, és az éhínség réme kezd megjelenni Egyiptomban. Men-nefer, az egykor pompás és gyönyörű város, hanyatlásnak indult. A látnokok nehéz időket jósolnak. @PErős szomszédaink Egyiptom növekvő gyengeségét kihasználva terjeszkedni készülnek. A buheni őrhelyet ostrom alatt tartják a Kermából érkezett rettenthetetlen kusita katonák, amely Afrika legnagyobb nem egyiptomi városa. Kus követelése adó fizetése, és a legkisebb provokáció is nyílt támadáshoz vezethet. Núbia szintén háborúra szólított fel, és elvesztett területeinek visszaszerzésére törekszik. @PHa Egyiptom túl akarja élni ezt a válságot, mindent meg kell tenned a kereskedelmi útvonalak megőrzéséért, hogy az áruk továbbra is áramolhassanak az országba és onnan kifelé. Tartsd nyitva a nehezen megszerzett kereskedelmi állomást a Selima-oázisnál. Pepi, aki a túlvilágra készül, gyakran fog követelni követ piramisának építéséhez, más városok pedig, amelyek élelmiszerhiánnyal küzdenek, tőled kérnek majd segítséget. @PBölcsen használd fel erőforrásaidat. Az oázisban bőségesen található értékes fa, de az erdő egy részét el kell pusztítanod, hogy hozzáférj a korlátozott vízkészlethez."
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
            text: "A karavánút",

        }
        content {
            text: "@P@PPepy elfoglalta a trónt, és családodat kancellári rangra emelte, de ennek ára volt. @PA központosított hatalom tovább gyengül, miközben a helyi és tartományi vezetők egyre nagyobb befolyásra tesznek szert. Egyes területeken a termés messze elmarad a megszokottól, és Egyiptomban megjelent az éhínség fenyegetése. Men-nefer, az egykor pompás és gyönyörű város hanyatlásnak indult. A jósok nehéz időket jövendölnek. @PErős szomszédaink ki akarják használni növekvő gyengeségünket. Buheni helyőrségünket ostromolják a Kermából érkezett félelmet nem ismerő kusita katonák, Afrika legnagyobb nem egyiptomi városának seregei. A kusiták adót követelnek, és a legkisebb provokáció is nyílt támadáshoz vezethet. Núbia szintén háborúra szólított fel, és vissza akarja szerezni elvesztett területeit. @PTartsd fenn Egyiptom stabilitását egy közigazgatási központ létrehozásával a Dakhla-oázisban. Az oázisban nagy értékű fák találhatók, ám ezek sajnos elzárják a hozzáférést a korlátozott vízkészlethez. Erről a fontos helyről importálj ébenfát Afrika belsejéből. Pepy, aki a túlvilági útjára készül, téglákat fog kérni emlékműve építéséhez. Más, élelmiszerhiánnyal küzdő városok is ellátmányt kérnek majd tőled."
        }
    }
    message_history_thinis {
        id: 223,
            type: 3,
            size [40, 30]
        title {
            text: "Thinis ",

        }
        subtitle {
            text: "Polgárháború",

        }
        content {
            text: "A régi életmód eltűnt, és a legtöbben attól tartanak, hogy Egyiptom soha nem nyeri vissza korábbi dicsőségét. Ozirisz hátat fordított népének, és az alacsony áradások sorozata széles körű éhínséget okozott. A fáraók hatalma, amely egykor megkérdőjelezhetetlen volt, szertefoszlott, helyét civakodó tartományi vezetők vették át. @PEnnek a káosznak a közepette két nemesi család emelkedett fel, és megpróbálja megszerezni az ország feletti uralmat. Henen-neszu uralkodói jogos örökösként követelik maguknak a trónt. Különösen kegyetlenek, és alig tesznek valamit az emberek éhezésének enyhítésére. Délen egy új család, az Inyotef-ház került hatalomra Waszetben. Ez a család sokat tett a dél egyesítéséért, és most Henen-neszu halálos polgárháborút indított Waszet ellen egész Egyiptom irányításáért. @PAz Inyotefek jóindulatukat bizonyítva rád bízták Thinisz, Egyiptom egyik legrégebbi városának újjáépítését. A hódítás zűrzavarát két nagyszerű és ősi épület élte túl: Ozirisz templomkomplexuma és a palota. Az Inyotefek elrendelték, hogy ha bármelyik épület elpusztul, nem pazarolnak pénzt a helyreállítására. Waszet uralkodói Thinisz helyreállítását elsődleges fontosságúnak tartják, és jelentős összegeket gyűjtöttek erre a célra – még ezekben a nehéz időkben is. Állítsd vissza Thiniszt régi pompájába, szervezz hadiflottát és hozz létre erős hadsereget, hogy megvédd a Henen-neszuhoz hű erők gyakori támadásaitól, köztük Sauty, Nekhen és Khmun városaitól. Légy óvatos Henen-neszu uralkodóival: adót követelhetnek, hogy próbára tegyék hűségedet – és megpróbálják kifacsarni belőled a debenjeidet. Figyelj a lehetőségre leső núbiaiakra is, akik Egyiptom belső viszályait akarják kihasználni."
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
            text: "Polgárháború",

        }
        content {
            text: "A régi életmód eltűnt, és a legtöbben attól tartanak, hogy Egyiptom soha nem nyeri vissza korábbi dicsőségét. Ozirisz hátat fordított népének, és az alacsony áradások sorozata széles körű éhínséget okozott. A fáraók hatalma, amely egykor megkérdőjelezhetetlen volt, szertefoszlott, helyét civakodó tartományi vezetők vették át. @PEnnek a káosznak a közepette két nemesi család emelkedett fel, és megpróbálja megszerezni az ország feletti uralmat. Henen-neszu uralkodói jogos örökösként követelik maguknak a trónt. Különösen kegyetlenek, és alig tesznek valamit az emberek éhezésének enyhítésére. Délen egy új család, az Inyotef-ház került hatalomra Waszetben. Ez a család sokat tett a dél egyesítéséért, és most Henen-neszu uralkodói halálos polgárháborút vívnak Waszet vezetőivel egész Egyiptom irányításáért. @PA Henen-neszu uralkodóival harcoló Inyotefek rád bízták szülővárosuk, Waszet felvirágoztatását. Ha az Inyotefek győzni akarnak Henen-neszu uralkodói ellen, és megszilárdítani akarják hírnevüket Egyiptomban, Waszetnek olyan várossá kell válnia, amelyre a többi település támaszkodhat, és segítséget vagy katonákat biztosíthat a rászorulóknak. Waszetnek, amely győzelmük esetén akár az Inyotefek fővárosa is lehet, nagyszerű várossá kell válnia. A rendelkezésre álló szűkös erőforrások felhasználásával építs Naptemplomot és piramist, hogy megmutasd az egyiptomiaknak az Inyotefek dicsőségét. @PWaszet maga sincs biztonságban a támadásoktól. Henen-neszu uralkodói és híveik időről időre fenyegethetik városodat, és megpróbálhatnak debent kicsikarni a város kincstárából. E jelentős veszélyek elhárítására építs erős hadsereget és flottát, hogy megvédd városodat, és segítséget nyújts más veszélyeztetett településeknek."
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
            text: "Újraegyesítés",

        }
        content {
            text: "Családod teljesítménye a polgárháború során nem maradt jutalom nélkül. Én, Mentuhotep fáraó, vezíri rangra emeltem családodat. Egész Egyiptomban nincs senki, akiben jobban megbíznék nálad. Most, hogy Felső- és Alsó-Egyiptom ikerkirályságai újra egyesültek, és a waszeti főváros virágzik, szükségem van rád, hogy segíts megszilárdítani hatalmamat az egész birodalomban. @PNoha Egyiptom újra egyesült, továbbra is hajlamos a belső összecsapásokra, különösen azokon a területeken, amelyek egykor Henen-neszu uralkodóit támogatták. Új egységünk megszilárdításához azt akarom, hogy építsd újjá és védd meg Kebetet. Kebetnek dicsőséges várossá kell válnia, amely megmutatja Egyiptom népének, mire képes uralmam alatt. A várost gyakran támadják a megmaradt hűséges városok, például Khmun, ezért gondoskodnod kell határainak védelméről. @PAz éhínség továbbra is sújtja az országot, és a birodalom más városai gyakran kérnek majd tőled élelmet. A lehető leggyorsabban válaszolj szívszorító kéréseikre, hogy egész Egyiptom megismerje jóindulatomat és leghűségesebb vezírem odaadását. @PTudom, hogy sokat kérek tőled, de Egyiptomban nincs más, aki képes lenne végrehajtani ezt a nehéz feladatot."
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
            text: "Újraegyesítés",

        }
        content {
            text: "Családod teljesítménye a polgárháború során nem maradt jutalom nélkül. Én, Mentuhotep fáraó, vezíri rangra emeltem családodat. Egész Egyiptomban nincs senki, akiben jobban megbíznék nálad. Most, hogy Felső- és Alsó-Egyiptom ikerkirályságai újra egyesültek, és a waszeti főváros virágzik, szükségem van rád, hogy segíts megszilárdítani hatalmamat az egész birodalomban. @PNoha Egyiptom újra egyesült, továbbra is hajlamos a belső összecsapásokra, különösen azokon a területeken, amelyek egykor Henen-neszu uralkodóit támogatták. Az újraegyesült ország megszilárdításához azt akarom, hogy építsd újjá és védd meg Menat Khufut, amely a polgárháború során majdnem teljesen elpusztult. Menat Khufunak dicsőséges várossá kell válnia, amely megmutatja Egyiptom népének, mire képes uralmam alatt. @PAz éhínség továbbra is sújtja az országot, és a birodalom más városai gyakran kérnek majd tőled élelmet. A lehető leggyorsabban válaszolj szívszorító kéréseikre, hogy egész Egyiptom megismerje jóindulatomat és leghűségesebb vezírem odaadását. @PVan még egy nemes kérésem: építs gránit obeliszkeket, hogy még inkább hirdessék mindazt, amit életem során ezért a földért tettem. @PTudom, hogy sokat kérek tőled, de azt is tudom, hogy Egyiptomban csak te vagy képes teljesíteni, amit kértem."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itjtawy", pos [50, 80] }
        subtitle { text: "Új főváros alapítása", pos [10, 30] }
        content {
            text: "Ó, hatalmas fáraó, Ré kedveltje, milyen szerencsésnek érezheted magad! Példátlan felemelkedésed Egyiptom trónjára maga is álomnak tűnik. Ennél gazdagabb jutalmat sem istenek, sem emberek nem adhatnának. Családod hatalomra kerülésével Egyiptom újrakezdhet, és talán mindannyian elfelejthetjük a polgárháború borzalmait. @PEnnek az új kezdetnek a megünneplésére építs egy nagyszerű új fővárost. Itjtawy bőséges természeti erőforrásaival tökéletes helyszín. A föld adományait felhasználva pompás várost építhetsz, amely méltó dinasztiád bátorságához és elhivatottságához. @PNagy dinasztiád tetteinek örök emlékéül építs két fenséges tégla piramist magadnak és családodnak, valamint egy félelmetes szfinxet sírod őrzésére. Egy ilyen eredményekkel rendelkező család nem érdemelhet kevesebbet. @PNe feledd azonban, hogy az országban vannak, akik megkérdőjelezik uralmad jogosságát. Sokan még mindig az éhínség következményeitől szenvednek, és azt mondják, hogy bitoroltad a trónt. Ha enyhíted ezeknek az embereknek a nyomorúságát és segítesz újjáépíteni otthonaikat, bizonyára elnyered halhatatlan hűségüket. Igyekezz a lehető legjobban gondoskodni új alattvalóidról, hogy ezek a szerencsétlen emberek ne ragadjanak fegyvert ellened."
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
            text: "Núbiába vezető út",

        }
        content {
            text: "Most, hogy Egyiptom szilárdan egyesült uralmad alatt, egész udvarod és én, hűséges vezíred, azt javasoljuk, hogy terjesszük ki országunk határait dél felé, Núbiába. Az Allaqi kiszáradt folyómedre gazdag aranyerekben, és egy hatalmas város Ikenben, ahol te is jelen vagy, bizonyára távol tartja a núbiaiakat a támadási kísérletektől. Légy azonban óvatos a kusitákkal. Ők sokkal veszélyesebb ellenfelek a núbiaiaknál, és kardjaikkal fognak arra ösztönözni téged, ó fáraó, hogy hagyd békén királyságukat. @P Hogy maradandó nyomot hagyj Núbiában, építs egy hatalmas obeliszket, amely Egyiptom számos eredményét hirdeti. Az obeliszk meggyőző bizonyítékul szolgál majd a núbiaiak számára az egyiptomi uralom előnyeiről, és állandó emlékeztető lesz jelenlétünkre. @PMiközben közvetlen figyelmed Ikenre összpontosul, ne feledkezz meg arról a célunkról sem, hogy virágzó kikötővárost hozzunk létre a Vörös-tengeren Sawunál. Sawunak szüksége lesz segítségedre, és nem fog habozni, hogy kérje azt. Ha Sawu felvirágzik, a szükséges rezet biztosíthatja Iken számára, amelyből fegyvereket kovácsolhatunk."
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
            text: "A Vörös-tenger partján",

        }
        content {
            text: "Most, hogy Egyiptom szilárdan egyesült uralmad alatt, kereskedelmi kapcsolatokat kell kialakítanunk a világ városaival, hogy növeljük Egyiptom gazdagságát, ó Két Föld Királya. @PAhogy néped gyarapodik, egyre különlegesebb árukat követel. Megunva az ékszereket, ezt a könnyen beszerezhető luxuscikket, ritka és drága javakra, például tömjénre vágynak. Udvarod és én, hűséges vezíred, azt javasoljuk, hogy alapíts Vörös-tengeri kikötőt Sawunál. Sawu kereskedelmi útvonalat kínál a távoli Pwenet felé, ahonnan a világ legkiválóbb tömjénét lehet importálni, igaz, nagy költséggel. @PA néhány szerény arany- és rézlelőhelyen kívül Sawu kevés nyersanyagot termel saját maga, de készáruk gyártójaként virágozhat. Ha kereskedelmi partnereinktől nyersanyagokat importálunk, és késztermékeket exportálunk, Sawu jelentős hasznot termelhet. @PMiközben Sawun dolgozol, egyik legbátrabb nomarchád új kereskedelmi központot alapít Núbiában. Városa, Iken, valószínűleg támadások célpontjává válik, ezért szeretett fáraómnak készen kell állnia arra, hogy minden szükséges erőforrást elküldjön neki. @PUralkodásod alatt Sawu minden bizonnyal a birodalom egyik legszebb városa lesz, amely méltó végső nyughelyedhez és családodéhoz. Miközben létrehozod a virágzó kikötőt, ne hanyagold el a túlvilágra való felkészülést. Egy mauzóleum és egy kis tégla piramis pompás lakhelyet biztosít majd neked és családodnak, miután átkeltetek a Nádas-mezőkre."
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
            text: "A próbatétel",

        }
        content {
            text: "Nagyra becsült fáraó, mindaz, amiért családod oly keményen küzdött, veszélybe került! A núbiai flotta a Nílust járőrözi, mélyen behatolva Egyiptom területére, falvakat és városokat egyaránt kifosztva. A núbiaiak kereskedelmi hajóinkat is megtámadják, és zsákmányként viszik el áruinkat. Hogy északi városaink visszaverhessék az ellenséget, készülj fel arra, hogy hadihajókat és katonákat küldj azoknak a településeknek, amelyeknek szükségük van rájuk. @PA núbiaiak újbóli hajózásának megakadályozására katonai tanácsadóid azt javasolják, hogy építs erődrendszert Hehnél, a Nílus második és harmadik kataraktája között. Az erődök dugóként zárják el az utat, és délen tartják a núbiaiakat. @PA núbiaiak sikeres kiűzéséhez Baki meghódítása vezet. Baki gazdag erőforrásokban, és elfoglalása megbénítja Núbia gazdaságát. Miután elvetted Bakit a núbiaiaktól, megkezdheted a homokkő importját a városból nagy mauzóleumodhoz. Hehi mauzóleumod emlékeztetni fog mindenkit a nyughatatlan núbiaiak felett aratott uralmadra. @PEgyiptom núbiaiaktól való megvédése számos kihívás elé állít. Figyelj, ó Élő Hórusz, a keleten gyülekező viharra. Lópaták dübörgése hallatszik egész Kánaánban, és villámgyors szekerek pusztítanak el mindent az útjukban. Ezeket a félelmetes harci szekereket, amelyekhez foghatót még sehol sem láttak, a hükszosz harcosok hajtják. Már viharfelhők gyülekeznek Egyiptom horizontján, ezért készülj fel a közelgő veszélyre."
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
            text: "Baszt városa",

        }
        content {
            text: "Legfenségesebb fáraó, most, hogy erős kereskedelmi útvonalaink szilárdan kiépültek, meg kell mutatnunk Egyiptomnak, milyen sikert és gazdagságot hozhat mindez. Bubasztisz tökéletes helyszínt biztosít egy ilyen város számára: megvédhetjük keleti értékes kereskedelmi útvonalainkat, miközben tiszteletünket fejezzük ki Baszt iránt, aki őrködött Egyiptom felett. @PBaszt városának olyannak kell lennie, amilyenhez nincs fogható Egyiptomban. Olyan szépnek kell lennie, mint a lótuszvirág, amely szórakozóhelyekkel, iskolákkal, könyvtárakkal és szentélyekkel bontja ki szirmait. Lakóinak bőségben kell élniük, és hozzá kell jutniuk a finomabb javakhoz, köztük az importált tömjénhez. Amikor elkészül, Bubasztisz lesz a kettős korona ékköve. @P Miközben ezt a dicsőséges várost építed, figyelj a keleten gyülekező viharra. Lópaták dübörgése hallatszik egész Kánaánban, és villámgyors szekerek pusztítanak el mindent az útjukban. Ezeket a félelmetes harci szekereket, amelyekhez foghatót még sehol sem láttak, a hükszosz harcosok hajtják. Már viharfelhők gyülekeznek Egyiptom horizontján, ezért készülj fel a közelgő veszélyre."
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
            text: "Egyiptom visszaszerzése",

        }
        content {
            text: "Leghatalmasabb fáraó, Egyiptom segítségért kiált. A fenyegető hükszoszok megszállták földünket, és saját fővárost alapítottak Rowartyban. Rowartyból megzavarták számos kereskedelmi útvonalunkat, elvágva a szükséges utánpótlást. Meg kell állítanunk hódításukat, mielőtt túl késő lenne. @PHa kedvedre való, nagy fáraó, vissza kell szereznünk Khmun városát, amelyet ezek az aljas betolakodók meggyaláztak. Erős hadsereget és flottát is építenünk kell, mert szükség lehet rá, hogy katonákat és fegyvereket küldjünk északi szövetségeseinknek, különösen Rowartyba, hogy segítsünk visszaverni a hükszosz támadást. Rád tekintenek majd, Ré gyermeke, támogatásért. De most nekünk is van új fegyverünk. Bölcs hadvezéreink elsajátították a rettegett harci szekér használatát, és ellenségeink ellen fordítjuk, hogy magunk előtt hajtva őket visszaszorítsuk. Miután kiűztük a bajkeverő hükszoszokat, katonai tanácsadóid azt javasolják, hogy építs erődöt a Sínai-félszigeten, Sharuhennél, hogy megakadályozzuk a keletről érkező újabb inváziókat. @P Bárcsak csak északon lennének gondjaink! Déli határainkról érkező jelentések szerint a núbiaiak ismét kihasználják Egyiptom figyelmetlenségét. Visszafoglalták Iken és Heh déli városait. Bár ezeknek az elvesztett városoknak a sorsa aggodalomra ad okot, először a hükszoszokat kell kiűznünk, mielőtt dél felé fordíthatnánk figyelmünket. @PEzek a hükszoszok szentségtelen betolakodók. Most fedeztük fel, hogy meggyalázták a khmuni piramist. Ellopták belőle mindazokat a temetési kellékeket, amelyekre az itt eltemetett hatalmas fáraónak szüksége van a Nádas-mezőkön. Új sírmellékletekkel kell ellátnunk a sírt, hogy az ott nyugvó fáraó örökké élvezhesse a túlvilági életet."
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
            text: "Egyiptom visszaszerzése",

        }
        content {
            text: "Ó, Két Föld Királya, Egyiptom segítségért kiált. A fenyegető hükszoszok megszállták földünket, és saját fővárost alapítottak Rowartyban. Rowartyból megzavarták számos kereskedelmi útvonalunkat. Meg kell állítanunk hódításukat, mielőtt túl késő lenne. @PItt, Sautyban biztonságban vagyunk a közvetlen támadástól, bár a hükszoszoknak van merszük adót követelni. Lehet, hogy katonákat és fegyvereket kell küldenünk északi szövetségeseinknek, hogy segítsünk visszaverni a hükszosz támadást. Rád tekintenek majd, ó hatalmas fáraó, támogatásért. De most nekünk is van új fegyverünk. Bölcs hadvezéreink elsajátították a rettegett harci szekér használatát, és ellenségeink ellen fordítjuk, hogy magunk előtt hajtva őket visszaszorítsuk. @PBárcsak csak északon lennének gondjaink! Déli határainkról érkező jelentések szerint a núbiaiak ismét kihasználják Egyiptom figyelmetlenségét. Visszafoglalták Iken és Heh déli városait. @PHa Egyiptom épségben akar kikerülni ezekből a viharos időkből, sok múlik hadvezéreid teljesítményén a szárazföldön és a folyón. Két legjobb tábornokod ösztönzésére megígérted, hogy mindkettőjüknek olyan lenyűgöző piramist építesz, mint a sajátod. Ígéreted tudatában szívükben elszántan küzdenek az ellenséggel, minden erejüket és kitartásukat bevetve. @PHa kedvedre való, hatalmas fáraó, építs három nagyszerű piramist Sautyban: egyet magadnak és egyet-egyet mindkét tábornokodnak. Ez a három piramis jelentős helyet foglal majd el, ezért értékes erőforrásokról kell lemondanod, hogy helyet biztosíts számukra. Talán a Níluson túlra is ki kell terjesztened városodat, hogy minden szükséges erőforrás rendelkezésre álljon a virágzáshoz."
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
            text: "Terjeszkedés és hódítás",

        }
        content {
            text: "Egyiptom új erőre kapva került ki a közelmúlt nehézségeiből. Büblosz, minden dús erdejével és gazdag rézlelőhelyével együtt a miénk! Jelenléteddel a város biztosan felvirágzik, és létrejön az Újbirodalom. @PÁm milyen riasztó felfedezést tettünk Büblosz meghódítása után! Egy új, félelmetes nép, a hettiták söpörtek végig Ázsia nagy részén, és egyesek szerint birodalmuk méretben vetekszik a miénkkel. Most Büblosz felé fordították tekintetüket, megirigyelve gazdagságát. Ha nem készülünk fel megfelelően támadásukra, könnyen elveszíthetjük Bübloszt ellenségünkkel szemben. @PMiközben a hettiták elleni összecsapásra készülünk, örökre egyiptomivá kell tennünk Bübloszt. Áldásoddal, ó fáraó, három obeliszket emelünk: két kisebbet és egy nagyot, amelyek birodalmad távoli vidékein is hirdetik felsőbbségedet és hírnevedet. Ezek a magasba törő emlékművek emlékeztetik majd Büblosz lakóit arra, hogy kinek tartoznak hűséggel. @PMiközben Büblosz ügyeivel foglalkozunk, Egyiptom más vidékei továbbra is támadásoknak vannak kitéve. A núbiaiak északra nyomultak egészen az első kataraktáig, és segítenünk kell szövetségeseinknek visszaszorítani őket. Rowartyból egy újabb rejtélyes ellenségről, a tengeri népekről érkeztek jelentések. Mindkét ellenséget határozottan le kell győzni, ha Egyiptom dicsőségre akar jutni. Hatalmad bizonyítására gondoskodj róla, hogy csapatokat és hadihajókat küldj, amikor segítséget kérnek."
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
            text: "Egyiptom dicsősége",

        }
        content {
            text: "Miután a hükszoszokat sikeresen kiűztük országunkból, földünk készen áll az újjászületésre: egy olyan Újbirodalomra, amely felülmúlja a múlt dicsőségét. Nemes fáraó, Baki ideális helyszín ennek az Újbirodalomnak a kezdetéhez. Az ott található hatalmas mennyiségű aranyat felhasználhatjuk új egyiptomi elképzeléseid megvalósításának finanszírozására. @PEgyiptom a nagyság küszöbén áll, de néhány makacs probléma még megmaradt. Egyiptom számos városa még mindig a hükszoszok által okozott pusztításból lábadozik, és szükségük lehet a fáraó segítségére. Más vidékeken régi ellenségeink továbbra is támadnak minket, miközben egy új ellenség, a tengeri népek, északi partvidékünket fosztogatja. Fel kell készülnöd arra, hogy megvédd Egyiptom városait régi és új ellenségeinktől egyaránt. @PAhogy Egyiptom egyre nagyobb tekintélyre tesz szert, sok város hajlandó kereskedni velünk. Néhányan annyira megismerték szokásainkat és annyira csodálják hatalmadat, hogy egyiptominak tekintik magukat, míg mások idegenek számunkra, és most kereskednek velünk először. Egyiptom dicsőségére használd ki ezeket a kapcsolatokat, hogy néped minden kívánt áruhoz hozzájusson. @PAz új korszak beköszöntésére királyi építészeid alig várják, hogy két piramist és egy méltóságteljes mauzóleumot építhessenek neked, ó fáraó. Ezek méltóképpen tükrözik majd azt a gazdagságot és nagyságot, amelyet Egyiptomnak hoztál."
        }
    }
    message_history_rowarty {
        id: 236,
            type: 3,
            size [40, 30]
        title {
            text: "Rowarty ",

        }
        subtitle {
            text: "A tengeri népek",

        }
        content {
            text: "Ó Arany Hórusz, ázsiai uralmunk szilárd és megkérdőjelezhetetlen, határaink pedig ismét messze benyúlnak Núbiába. Ám északi partvidékünk gondjai egyre súlyosbodnak. A tengeri népek egyre agresszívebbé váltak, és gátlástalanul fosztogatják városainkat. Csak a fáraó személyes jelenléte lehet elegendő e kegyetlen és ravasz ellenfél legyőzéséhez. Ha erős hadsereggel támogatott flottát állítasz fel, bizonyára legyőzzük a tengeri népeket. @PMiközben a tengeri népek ellen harcolsz, bátor nomarcháid támadásokat vezetnek szerte a világban. Ha sikerrel járnak, Egyiptom uralma a nagy ázsiai Eufrátesz folyótól egészen délen a hatalmas kusita Kerma városáig terjed majd. Amikor te és nomarcháid elnyeritek az édes győzelmet, dinasztiádat Egyiptom történetének legnagyobbjaként jegyzik majd fel. @PTávoli befolyásunkat egy új kereskedelmi partner is jelzi: Mükéné. Mükéné királya értesült Egyiptom pompájáról és bőségéről, és kereskedni kíván velünk. Ha beleegyezel ennek a kereskedelmi útvonalnak a megnyitásába, ó fáraó, polgáraid minden bizonnyal olyan különleges árukhoz jutnak majd, amilyeneket még sosem láttak. @PKirályi családod túlvilági nyughelyéhez lenyűgöző mauzóleumot és egy impozáns iker tégla piramispárt kell építeni. Ezek az emlékművek minden utánad következő nemzedéket emlékeztetnek majd tetteidre, a csatatéren és azon kívül egyaránt."
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
            text: "A fáraó dicsősége",

        }
        content {
            text: "Jóságos fáraó, békét és jólétet hoztál nemzetünknek. Bölcs és rátermett uralmad alatt Egyiptom ismét erős és dicsőséges országgá vált. Minden nomarch hűséges hozzád, és nagy nemzetünket már nem fenyegeti veszély. @PMiután mindazt megvalósítottad, amiért családod oly sok évvel ezelőtt küzdött, eljött az idő, hogy megörökítsd nagy dinasztiád eredményeit. Ennek egyetlen módja, ha megépíted Egyiptom valaha ismert legnagyobb piramisát Rostján, még Khufu piramisánál is hatalmasabbat. Nemes családod más tagjai sok áldozatot hoztak az Egyiptom feletti uralmadhoz vezető hosszú úton. Róluk sem szabad megfeledkezni: homokkőből készült mauzóleummal kell tisztelegni előttük rendíthetetlen támogatásukért. @PEzeknek az emlékműveknek az ideális helyszíne Hetepsensusret a gazdag Fayuum régióban. Innen intézheted az állam minden ügyét, és válaszolhatsz városaid ellátmánykéréseire is, miközben felépíted hatalmas piramisodat."
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
            text: "A Nílus partjai",

        }
        content {
            text: "@P Családod segítségével a thiniszi Hor-Aha király sikeresen egyesítette Felső- és Alsó-Egyiptom kettős királyságát, egész Egyiptom fáraójának kiáltotta ki magát, és lenyűgöző fővárost alapított Men-neferben. @PCsaládod ismét új helyre költözött, ezúttal Alsó-Egyiptom párás deltavidékére, a Perwadjyt néven ismert területre. Kánaáni hadihajók fenyegetik ezt a vidéket, és amikor eljön az idő, valószínűleg neked is ki kell küldened néhány hadihajót. @PCsaládod elnyerte a nemesi rangot. Ezért elvárható, hogy mielőtt e világból a túlvilágra távozol, elkészíts egy gyönyörű tégla síremléket – egy masztabát –, amely tested otthonául szolgál majd túlvilági utazásod során. @PMielőtt azonban ezt megtehetnéd, először farmokat kell létesítened a Nílus partján, hogy kihasználd a folyó évenkénti áradása által lerakott gazdag, termékeny talajt. Ez lehetővé teszi népességed növekedését és gyarapodását, míg végül elég nagy lesz ahhoz, hogy elkészíthesse ezt a szent emlékművet. De vigyázz, mert a Nílus életet adó vizei között számos veszély leselkedik rád, például halálos krokodilok, vízilovak és maláriát terjesztő szúnyogok. @L@L Gazdálkodás a Nílus mentén @P A termékeny ártér előnyeinek kihasználásához közvetlenül a folyó árterületére kell építened a farmokat. A legtöbb termelőépülettel ellentétben az ártéri farmoknak nincs szükségük közvetlen hozzáférésre az alkalmazottakhoz, de állandó paraszti munkaerőt igényelnek a földek műveléséhez, amelyet munkatáborok biztosítanak. A munkatáborokat viszonylag közel építsd az ártéri farmokhoz, hogy a parasztoknak ne kelljen túl messzire gyalogolniuk. @G56 @L@L Az éves aratás @L@P Minden évben a Nílus kilép medréből, és gazdag, termékeny iszappal tölti fel újra a kimerült árterület talaját. A parasztok közvetlenül az áradás előtt takarítják be az éves termést, majd a magtáraidba szállítják. Mivel évente csak egy betakarítás van, ügyelj rá, hogy elegendő magtárral rendelkezz a növekvő népességed számára szükséges élelmiszer tárolásához."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Étel vagy éhínség?", pos [0, 15] }
        content {
            text: "@P A növekvő népességnek megbízható élelemforrásra, valamint annak tárolására és elosztására szolgáló rendszerre van szüksége. Egyes állatok, például az ezen a vidéken élő struccok, vadászhatók élelemként. A magtárak tárolják a vadászott húst és más élelmiszereket, míg a bazárok szétosztják az ételt a falu lakói között. A legtöbb termelőépülethez hasonlóan ezeknek is lakóházak közelében kell lenniük, és a városnak elegendő munkással kell rendelkeznie működtetésükhöz. @L@L Élelemvadászat @L@P Építs vadászházat a strucccsordák közelében, és a vadászok elindulnak zsákmány után kutatni. Ha sikerrel járnak, a tetemeket visszaviszik a vadászházba feldolgozásra, majd egy kocsitoló elszállítja őket a legközelebbi magtárba tárolásra. @P A bazárok különböző dolgozói felmérik az általuk ellátott környékek igényeit, élelmet szereznek a közeli magtárakból, majd a közvetlen közelükben lévő házakhoz szállítják azt. @G60 @P Építs magtárakat és bazárokat az „Tároló- és elosztóépületek” gombra kattintva. @G77 @L@P A küldetés végső célja, hogy néhány „durva kunyhót” „szegényes viskóvá” fejlessz. Ehhez vizet és a bazárból származó élelmet kell biztosítanod számukra. Ügyelj arra is, hogy ne legyenek túl közel csúnyán kinéző ipari épületekhez vagy gyenge minőségű lakóhelyekhez, mert ezek csökkentik a környék vonzerejét, és akadályozzák a házak fejlődését. @P Idővel több módszert is megtanulsz egy terület vonzerejének növelésére. Egyelőre azonban egyszerűen kerüld, hogy lakóházakat ipari épületek közelébe helyezz. @L@L Felügyelők @L@L Mostantól elérhető a Magtárak felügyelője, aki információkkal és tanácsokkal szolgál. Idővel számos tanácsadód lesz, akik segítenek városod irányításában. @G76 @L@P Elérésükhöz kattints a „Felügyelők” ikonra, vagy kattints jobb gombbal a megfelelő épületre."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Szórakoztatás", pos [0, 15] }
        content {
            text: "Ahogy városod egyre fejlettebbé válik, egyes polgárok élvezhetik a szabadidős tevékenységeket, például a szórakoztató előadásokat. A szórakozás sokfélesége egy valóban művelt város egyik ismertetőjele, jelenleg azonban csak zsonglőrök segítségével tudsz szórakoztatást biztosítani. @L@L Szórakozóhelyek és zsonglőrök @L@P A zsonglőrnek előadási helyszínre van szüksége, amelynek legegyszerűbb formája a „bódé”. Építs egy bódét egy kereszteződéshez, hogy zsonglőrelőadásokat tarthass, valamint egy közeli zsonglőriskolát az előadók képzésére. Mindkettőnek hozzáférésre van szüksége a dolgozók lakóhelyeihez és elegendő munkásra a működéshez. @P Az iskolában képzett zsonglőrök a közeli bódékhoz mennek, ahol előadásokat tartanak, és mérsékelt mennyiségű szórakozást biztosítanak a környék számára. @G61 @L@L Keresd fel a Szórakoztatás felügyelőjét, hogy többet tudj meg városod kikapcsolódási igényeiről. Kattints a „Rétegek: Szórakoztatás” gombra, hogy lásd, mely házak rendelkeznek szórakozási lehetőséggel."
        }
    }
    message_gold_and_crime {
        id: 241
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Arany és bűnözés" }
        content {
            text: "@L@L Aranybányászat @L@P Keresd a sziklás területeken a fémérc jelenlétét, amelyet a kövek között látható fényes fémes foltok jeleznek. Az érc kitermeléséhez aranybányákat kell építened közvetlenül ezek mellé az erek mellé. @G53 @L@L Palota @L@P A palotára van szükség a nyers aranyérc feldolgozásához, valamint az elkészült aranyrögök tárolásához. A palota a város kormányzatának székhelye, ezért olyan helyre kell építeni, ahol megfelelő hozzáférés van a talajvízhez (füves területeken). @P Amint palotád működésbe lép, a bányászok minden aranybányából elszállítják az aranyércet, amelyet pénzzé alakítanak, és „debenben” számolnak. @G54 @L@L Bűnözés @L@P A pénzkészlet azonban magával hozza a lopás veszélyét is. A rendőrök segíthetnek csökkenteni a veszteségeket: járőröznek az utcákon a bűnözés megelőzése érdekében, és elfogják a bűnözőket, akikkel találkoznak. @G55 @L@P A bűnözés megelőzésének legjobb módja azonban az, ha lakosságodat megfelelő élelemmel, egészségügyi ellátással és munkalehetőségekkel elégedetten tartod."
        }
    }
    message_farming_along_the_nile {
        id: 242
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Gazdálkodás a Nílus mentén",

        }
        content {
            text: "Gazdálkodás a Nílus mentén @L@P A termékeny ártér előnyeinek kihasználásához közvetlenül a folyó árterületére kell építened a farmokat. A legtöbb termelőépülettel ellentétben az ártéri farmoknak nincs szükségük közvetlen hozzáférésre az alkalmazottakhoz, de állandó paraszti munkaerőt igényelnek a földek műveléséhez, amelyet munkatáborok biztosítanak. A munkatáborokat viszonylag közel építsd az ártéri farmokhoz, hogy a parasztoknak ne kelljen túl messzire gyalogolniuk. @G56 @L@P Minden évben a Nílus kilép medréből, és gazdag, termékeny iszappal tölti fel újra a kimerült árterület talaját. A parasztok közvetlenül az áradás előtt takarítják be az éves termést, majd a magtárakba szállítják. Mivel évente csak egy betakarítás van, ügyelj rá, hogy városod elegendő magtárral rendelkezzen a növekvő népesség számára szükséges élelmiszer tárolásához."
        }
    }
    message_developing_culture {
        id: 243,
            type: 2,
            message_type: 4,
            size [40, 30]
        title {
            text: "A kultúra fejlődése",

        }
        content {
            text: "Sör @L Egyiptomi társaid tökéletesítették a sörfőzés művészetét, amely Egyiptom-szerte igen népszerű itallá vált! A helyi farmokról származó árpa felhasználásával a sörfőzők sört készítenek, majd a tárolóudvarokba szállítják, ahonnan a bazár dolgozói később kiosztják (az élelemhez és a fazekasárukhoz hasonlóan). @L@L Több isten @L A vidék védőistene Ré, de Oziriszt és Basztot is helyi istenségként tisztelik itt. Ügyelj rá, hogy városodban több Rének szentelt templom és szentély legyen, de a helyi istenségekről se feledkezz meg! Legértékesebb polgáraid számára biztosíts hozzáférést a különböző isteneknek szentelt templomokhoz. @L@L Több szórakozás @L A kifinomult egyiptomiak szívesen hallgatnak zenét szabadidejükben, és időnként zsonglőrelőadásokat is megtekintenek. Míg a kis bódéban csak zsonglőrök léphetnek fel, a zenepavilonban zsonglőrök és zenészek együtt is előadhatnak. Építs zenepavilont egy kereszteződéshez, valamint egy közeli konzervatóriumot a zenészek képzésére. A többféle szórakozási lehetőség jelentősen javítja bármely város életminőségét. @L@L Törvény és rend @L A bíróságáról járőröző elöljáró segít csökkenteni a bűnözés veszélyét azáltal, hogy meghallgatja a panaszokat és gondoskodik arról, hogy a viták békésen rendeződjenek."
        }
    }
    message_getting_started {
        id: 244,
            type: 2,
            message_type: 4,
            size [40, 30]
        title {
            text: "Kezdeti lépések",

        }
        content {
            text: "Kezdd a lakó- és ipari területek megtervezésével. Mostanra már tudod, mire van szüksége a népnek az alapvető élelem- és vízellátáson kívül. Mielőtt felsőoktatásra és kereskedelemre gondolhatnál, néhány házat el kell látnod fazekasáruval, sörrel, szórakozási lehetőségekkel és vallási szolgáltatásokkal."
        }
    }
    message_soldiers_and_forts {
        id: 245
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Katonák és erődök",
        }
        content {
            text: "Katonák toborzásához építs erődöt és toborzóépületet. A toborzóépület új újoncokat küld egyenként az erődbe, amíg az teljesen meg nem telik. Kétféle erőd létezik: gyalogos- és íjászerőd, és mindegyik tizenhat katonát fogad be, amely egy „századnak” felel meg. Ha katonák halnak meg a harcban, a toborzó gondoskodik az utánpótlás besorozásáról. @G57 @L@L Fegyverek @L@P Az íjászok saját íjaikat és nyilaikat használják, de a gyalogosokat rézhegyű lándzsákkal kell felszerelni. Megfelelő mennyiségű réz birtokában a fegyverkovács ilyen fegyvereket készít. Ezeket aztán a toborzóhoz szállítják, hogy az új gyalogosok megfelelő felszereléssel indulhassanak harcba. @L@L Célok és eligazítások @P Ettől kezdve az aktuális céljaid többé nem jelennek meg a képernyő tetején. A küldetés céljainak áttekintéséhez kattints a vezérlőpulton található „ankh” jelre, majd keresd fel a felügyelőidet, hogy felmérd városod általános fejlődését."
        }
    }
    message_trade_on_the_water {
        id: 246,
            type: 2,
            message_type: 4,
            size [40, 30]
        title {
            text: "A víz partján",

        }
        content {
            text: "Kereskedelem vízen @L A kereskedelem folyón és tengeren is folyhat, ha ilyen vízi útvonalak vezetnek a városhoz. Vízi kereskedelmi útvonal megnyitásához keresd fel a világtérképet. Vízi kereskedelemhez városodnak működő kikötőre is szüksége lesz. @L@L Halászat a Níluson @L A Nílus bőséges halforrás, amely népszerű élelem Egyiptomban. Ráadásul a többféle élelmiszerből álló étrend jobb egészséget és nagyobb elégedettséget biztosít néped számára. E gazdag kincs kiaknázásához halászhajókra lesz szükséged. @L@L Hajók és csónakok építése @L A hajóács hadihajókat és halászhajókat épít. Minden hajót saját hajóállásnak kell kiszolgálnia. Amikor egy hajóállásnak szüksége van egy hajóra, a hajóács megkezdi annak elkészítését. Várakozó hajóállás nélkül a hajóács nem épít hajókat. @L Bár egyetlen hajóács is képes ellátni a város összes hajóigényét, több hajóács segítségével az elveszett hajókat sokkal gyorsabban pótolhatod. A halászhajók elkészítéséhez a hajóácsnak nincs szüksége nyersanyagra, de katonai hajók, például hadihajók és szállítóhajók építéséhez faanyagra lesz szüksége. @L A katonai hajók, kereskedelmi hajók és halászhajók széles testűek és mély merülésűek, hogy a Níluson és a part menti vizeken közlekedhessenek. Nem keskeny csatornákra készültek, ezért nem tudnak felhajózni kis patakokon vagy keskeny öblökön. Semmi sem akadályoz meg abban, hogy ilyen helyeken hajóácsot, kikötőt vagy hajóállást építs, de ha így teszel, a hajók nem tudnak eljutni ezekhez az építményekhez vagy onnan távozni, így azok nem működnek. @L Amikor megfelelő tengerparti helyszíneket keresel, ne feledd, hogy minden hajónak szabad útvonalra van szüksége kikötője és célállomása között. Például nem építhetsz halászhajó-állást egy belső tóra abban a reményben, hogy hajói elérik a nílusi halászterületeket, még akkor sem, ha a tavat egy kis patak összeköti a Nílussal."
        }
    }
    message_at_the_waters_edge {
        id: 247,
            type: 2,
            message_type: 4,
            size [40, 30]
        title {
            text: "A víz partján",

        }
        content {
            text: "Kereskedelem vízen @L A kereskedelem folyón és tengeren is folyhat, ha ilyen vízi útvonalak vezetnek a városhoz. Vízi kereskedelmi útvonal megnyitásához keresd fel a világtérképet. Vízi kereskedelemhez városodnak működő kikötőre is szüksége lesz. @L@L Halászat a Níluson @L A Nílus bőséges halforrás, amely népszerű élelem Egyiptomban. Ráadásul a többféle élelmiszerből álló étrend jobb egészséget és nagyobb elégedettséget biztosít néped számára. E gazdag kincs kiaknázásához halászhajókra lesz szükséged. @L@L Hajók és csónakok építése @L A hajóács hadihajókat és halászhajókat épít. Minden hajót saját hajóállásnak kell kiszolgálnia. Amikor egy hajóállásnak szüksége van egy hajóra, a hajóács megkezdi annak elkészítését. Várakozó hajóállás nélkül a hajóács nem épít hajókat. @L Bár egyetlen hajóács is képes ellátni a város összes hajóigényét, több hajóács segítségével az elveszett hajókat sokkal gyorsabban pótolhatod. A halászhajók elkészítéséhez a hajóácsnak nincs szüksége nyersanyagra, de katonai hajók, például hadihajók és szállítóhajók építéséhez faanyagra lesz szüksége. @L A katonai hajók, kereskedelmi hajók és halászhajók széles testűek és mély merülésűek, hogy a Níluson és a part menti vizeken közlekedhessenek. Nem keskeny csatornákra készültek, ezért nem tudnak felhajózni kis patakokon vagy keskeny öblökön. Semmi sem akadályoz meg abban, hogy ilyen helyeken hajóácsot, kikötőt vagy hajóállást építs, de ha így teszel, a hajók nem tudnak eljutni ezekhez az építményekhez vagy onnan távozni, így azok nem működnek. @L Amikor megfelelő tengerparti helyszíneket keresel, ne feledd, hogy minden hajónak szabad útvonalra van szüksége kikötője és célállomása között. Például nem építhetsz halászhajó-állást egy belső tóra abban a reményben, hogy hajói elérik a nílusi halászterületeket, még akkor sem, ha a tavat egy kis patak összeköti a Nílussal. @L@L Téglagyártás @L A tégla valamivel olcsóbb építőanyag, amelyet bizonyos síremlékek elkészítéséhez használnak. Téglák készítéséhez téglagyárra, valamint agyagra és szalmára lesz szükséged."
        }
    }
    message_the_finer_things_tutorial {
        id: 248,
            type: 2,
            message_type: 4,
            size [40, 30]
        title {
            text: "A kifinomult dolgok",

        }
        content {
            text: "Templomkomplexumok @L Ahogy az egyiptomiak védőisteneik iránti odaadása egyre növekszik, egyre nagyobb és nagyobb istentiszteleti helyeket követelnek. A legtöbb város templomkomplexumot szeretne emelni választott istenének, hogy teljes mértékben részesülhessen annak áldásaiból. Felépítése után a templomkomplexum tovább bővíthető egy jósda és egy oltár hozzáadásával, amelyek más, kisebb isteneknek vannak szentelve. Ezek az istenek szintén különféle előnyöket biztosítanak a város számára. @L@L Luxusjavak @L A helyben készített ékszereken kívül az egyiptomiak nagyra becsülnek bizonyos más luxuscikkeket is, amelyek csak behozatal útján érhetők el. Egy városnak többféle luxuscikkhez kell hozzáférnie ahhoz, hogy valóban civilizálttá váljon. @L@L Faanyag kitermelése @G58 @L A faanyag ritka és értékes nyersanyag Egyiptom száraz vidékén. Az erdőkkel rendelkező területek igazán szerencsések. A fellelhető hasznosítható fák kitermeléséhez építs fakitermelő helyet, és embereket küldenek ki a fa kivágására. A faanyagot hadihajók és szállítóhajók készítéséhez, valamint egyes emlékművek kiegészítő szerkezeteihez használják."
        }
    }
    message_housing_and_roads {
        id: 249,
            type: 2,
            message_type: 4,
            size [40, 30]
        title { text: "Lakóhelyek és utak" }
        content { text: "@P A falu elsődleges szükségletei a lakóhelyek, amelyek megfelelő otthont biztosítanak a telepeseknek, valamint az úthálózat, amely lehetővé teszi leendő lakói számára a könnyű és hatékony közlekedést. @P Építs lakóterületeket, és hamarosan emberek költöznek a faluba. @G50 @L@L Utak @L@P Kattints és húzd az egeret hosszabb útszakaszok egyidejű építéséhez. @G51 @P Minden kereszteződésnél a járókelőknek választaniuk kell az útirányok között, így minden kereszteződés csökkenti a tényleges útvonaluk feletti irányításodat. @G52 @P Gondosan tervezd meg az utakat, és használj minél kevesebb kereszteződést, hogy biztosan arra járjanak az emberek, amerre szeretnéd. @P Az útvonalat, amelyen keresztül ezek a bevándorlók elérik városodat, királyi útnak nevezik. A bevándorlóknak mindig szabad átjárásra van szükségük a királyi út és a város lakóterületei között. Ha egy városrészt elszigetelsz ettől a külvilággal való fontos kapcsolattól, az ottani házak egyszerűen eltűnnek. @L@L Egy üzenetpanelből (mint ez is) a jobb egérgombbal léphetsz ki." }
    }
    message_basic_healthcare {
        id: 250,
            type: 2,
            message_type: 4,
            size [40, 30]
        title { text: "Alapvető egészségügy" }
        content { text: "Városod egészségügyi problémákkal küzd, ami várható a növekvő népesség mellett. A malária és a betegségek a leggyakoribb egészségügyi válságok, amelyek a város háztartásait sújtják, bár széles körű járvány is kitörhet, ha az egészségügyi ellátás rendkívül hiányos. @P Ha egy házat malária vagy betegség fertőz meg, minden lakója meghal, és az épület egy bizonyos ideig nem lakható újra. @G64 @L Malária @L@P A malária leginkább víz és mocsaras területek közelében fordul elő. A „Kockázatok: Malária” réteg megmutatja, mely házak vannak nagyobb veszélyben. @P A Vízellátóból származó tiszta vízhez való hozzáférés, valamint a helyi patikus által biztosított rovarriasztó jelentősen csökkenti a malária kockázatát minden háztartásban. A legtöbb épülethez hasonlóan a patikus is csak akkor működik, ha útkapcsolattal és munkaerővel rendelkezik. @G63 @L Betegség @L@P Az orvosok gyógyszerek beadásával segítenek csökkenteni a betegségek kockázatát az általuk ellátott házakban. A folyamatos élelmiszerellátás szintén elengedhetetlen a betegségek megelőzéséhez. A „Kockázatok: Betegség” réteg megmutatja, mely házak vannak veszélyben."
    }
        message_requests_from_other_cities {
            id: 251
            type: 2
            message_type: 4
            size [40, 30]
            title {
                text: "Más városok kérései"
                pos [0, 20]
            }
            content {
                text: "Egyik testvérvárosod segítségre szorul, és kéréssel fordult hozzád. Ha jó kapcsolatot szeretnél fenntartani a növekvő Királyság többi városával, általában érdemes az ilyen kérésekre készségesen és gyorsan válaszolni. @G65 @P Ha a tárolóudvaraidban elegendő mennyiség van a kívánt áruból, keresd fel a Politikai felügyelőt, hogy elküldhesd a szállítmányt az adott városba."
            }
        }
        message_fire_in_the_village {
            id: 252
            type: 2
            message_type: 4
            size [40, 30]
            title { text: "Tűz ütött ki a faluban!" }
            content { text: "Tűz ütött ki a faluban! @L@P A jövőbeli tüzek megelőzésére mostantól tűzőrségeket építhetsz. @P A falu legtöbb nem lakóépületéhez hasonlóan a tűzőrségnek is munkásokra van szüksége a működéshez. Alkalmazottak keresésére az épületből valakit kiküldenek, hogy lakott házakat keressen. Amint talál lakóépületet, az épület hozzáfér a dolgozókhoz, bár ez nem feltétlenül jelenti azt, hogy a faluban elegendő munkás van minden üres állás betöltésére. A megfelelő létszámmal működő tűzőrség tűzfelügyelőket küldhet járőrözni a faluba. @P A tűzfelügyelők útvonalukon ellenőrzik az épületeket tűzveszély szempontjából, és csökkentik a kigyulladás kockázatát, miközben elhaladnak mellettük. A tűzfelügyelők minden olyan épületet elláthatnak, amely legfeljebb két mezőre található egy úttól. @G67 @P Ha tüzet fedeznek fel, a felügyelő odamegy, vödrökkel eloltja a lángokat, majd visszatér szokásos járőrútjára. @G66 @P Kattints a „Rétegek: Kockázatok” gombra, hogy lásd, mely épületek vannak tűzveszélyben. Ha egy épület leég, jobb gombbal kattinthatsz a hátramaradt romhalmazra, hogy megtudd, mi állt ott a tűz előtt. @L@L Üzenetek @L@P Amikor meghallod azt a csengőhangot, amely akkor szólt, amikor ez a panel megjelent, az azt jelenti, hogy üzeneted érkezett. Üzenet elolvasásához kattints az üzenet gombra. @L@P Néhány sürgős üzenetet (például ezt is) még azelőtt megkapsz, hogy a többi üzeneted közé kerülne. A kevésbé sürgős értesítések közvetlenül az üzenetdobozba kerülnek külön megjelenítés nélkül, ezért mindig figyelj a csengőhangra. A különleges oktatóüzeneteket (mint ez is) kék tekercs jelöli, így később könnyen visszatérhetsz hozzájuk, amikor szükséged van rájuk."
            }
        }
        message_tutorial_collapsed_building {
            id: 253,
                type: 2
            message_type: 4
            size [40, 30]
            title { text: "Összeomlott épület" }
            content { text: "Bizonyos nagy épületek megfelelő karbantartás nélkül összeomlanak. Ennek megelőzésére építs építészirodát. A tűzőrséghez hasonlóan ez az épület is dolgozókat küld ki, jelen esetben építészeket, akik az utcákat járva kijavítják az útjukba kerülő sérült épületeket. @G68 @L@P Kattints a „Rétegek: Kockázatok” gombra, hogy lásd, mely épületeket fenyegeti tűz vagy összeomlás veszélye."
            }
            message_tutorial_education {
                id: 254
                type: 2
                message_type: 4
                size [40, 30]
                title { text: "Oktatás", pos [0, 15] }
                content {
                    text: "Most, hogy valamennyire felépítetted ezt a várost, ideje oktatást biztosítani néhány polgár számára. @L@P Az iskolák és könyvtárak nem tudják tanítani az embereket papirusz nélkül, amelyre írhatnak. @G69 @P A nádgyűjtők biztosítják a papiruszkészítők számára a szükséges nyersanyagokat, a papiruszt pedig közvetlenül a város oktatási intézményeihez szállítják."
                }
            }
            message_tutorial_clean_water {
                id: 255
                type: 2
                message_type: 4
                size [40, 30]
                title {
                    text: "Tiszta víz",

                }
                content {
                    text: "Nagyszerű! Sikerült élelemmel ellátnod a falu magtárát. Most a falusiaknak tiszta vízhez kell jutniuk egy vízellátóból, amely sokkal jobb a kútnál. @L@L Vízellátó @L@P A kutakhoz hasonlóan ezeket is olyan földre kell építeni, ahol a talajvíz elérhető, amit a zöld fű jelenléte jelez. A vízellátóknak a közeli lakóházakból származó dolgozókhoz is hozzáférésre van szükségük. @G70 @L@P Működésbe lépése után a vízellátó vízhordót küld ki, aki tiszta ivóvizet tartalmazó vödröket szállít a közvetlen közelében lévő házakhoz. Kattints a „Rétegek: Víz” gombra, hogy lásd, mely házak rendelkeznek vízellátóból származó tiszta vízzel, egyszerű kúttal, vagy egyáltalán nincs vízforrásuk. @L@L Küldetés eligazítása és céljai @P A küldetés teljesítéséhez hat „erős kunyhót” kell ellátnod élelemmel egy bazárból, hogy „szegényes viskókká” fejlődjenek. Kattints a tekercs ikonra, hogy áttekintsd ennek és más küldetéseknek a céljait."
                }
            }

            message_tutorial_municipal_structures {
                id: 256,
                    type: 2,
                    message_type: 4,
                    size [40, 30]
                title { text: "Középületek" }
                content {
                    text: "Nagyszerű munka! Sikerült némi ipart beindítanod, és most már elgondolkodhatsz városod fejlesztésén. A szépítés vonzóbbá tehet bizonyos városrészeket, míg más középületek hatékonyabbá tehetik a működést. @L@L Kertek, szobrok és terek @G72 @P A környezetük vonzóbbá tételével a kertek, szobrok és terek segíthetik a házak fejlődését. Több kertterület egymás mellé helyezve nagyobb parkokat alkothat. A tereket kövezett utakra helyezd, hogy javítsd megjelenésüket és a környező terület vonzerejét. @L@L Útzárak @G62 @P Az útzárak segítségével irányíthatod városod járókelőit. Egyes járókelőknek meghatározott céljuk van, míg másoknak nincs. Ők egyszerűen az utcákat járják, és előnyöket biztosítanak minden épületnek, amely mellett elhaladnak. Az útzárak megakadályozzák ezen járókelők áthaladását, de azokat, akiknek meghatározott céljuk van, átengedik, hogy elvégezhessék feladataikat. @L@L Vízi átkelők @G71 @P A kompok segíthetik városod gördülékenyebb működését. A gondosan elhelyezett vízi átkelők lehetővé teszik, hogy lakóid elérjék a táj egyébként hozzáférhetetlen részeit, ahol zsákmányt vagy más értékes nyersanyagokat találhatnak. Bizonyos esetekben lerövidíthetik egyes szállítók útját, így gyorsabbá tehetik a munkájukat."
                }
            }
            message_tutorial_monuments_and_more {
                id: 257
                type: 2
                message_type: 4
                size [40, 30]
                title {
                    text: "Emlékművek és még több!"
                }
                content {
                    text: "Mivel már idáig eljutottál a bemutatóban, ideje megismerned még többet abból, amit a Pharaoh kínál. Ne felejtsd el felkeresni az újonnan elérhető tanácsadóidat, akik további információkkal és segítséggel szolgálnak növekvő városod irányításához. @L@L Emlékművek @L@P Most már elkezdheted masztaba sírod építését! A masztaba elhelyezéséhez kattints a „Vallási épületek: Emlékművek” gombra. Szükséged lesz téglakészletre, valamint téglavetőkre és paraszti munkásokra (munkatáborokból), hogy teljesítsd ezt az „emlékezetes” feladatot... és mindössze tizenegy éved van rá! @G75 @L@L Egyéb háztartási szükségletek @L@P A fazekasáru mellett az egyiptomi háztartásoknak sörre és vászonra (valamint néhány más, ebben a bemutatóban nem elérhető dologra) is szükségük van. A sör a helyi farmokon termesztett árpából készül a sörfőzdében. A vásznat a takács készíti lenből, amely szintén helyi termény. Az élelemhez és fazekasáruhoz hasonlóan a sört és a vásznat is a bazár osztja szét a házak között. @L@L Törvény és rend @L@P A bíróságáról járőröző elöljáró segít csökkenteni a bűnözés kockázatát azáltal, hogy meghallgatja a panaszokat és gondoskodik arról, hogy a viták békésen rendeződjenek. @L@L Egészség és higiénia @L@P Minden városnak szüksége van néhány balzsamozóra a tisztaság fenntartásához, valamint azért, hogy fejlettebb lakói megfelelő temetési szertartásban részesüljenek. A halottasház vásznat (amelyet a takács készít) használ, és balzsamozási szolgáltatásokat biztosít a környező házak számára. A fogorvosok a hozzájuk tartozó házak lakóinak kívánt fogászati ellátást nyújtanak. @L@L Oktatás @L@P Az iskolák és könyvtárak nem tudják tanítani az embereket papirusz nélkül, amelyre írhatnak. A nádgyűjtők biztosítják a papiruszkészítők számára a szükséges nyersanyagokat, a papiruszt pedig közvetlenül a város oktatási intézményeihez szállítják. @G69 @L@L Hadihajók @L@P Lehet, hogy erős hadihajókkal kell megvédened városod partjait. Fakitermelőre lesz szükséged, hogy faanyagot biztosítson a hajóácsnak, aki ezekből a harci hajókat készíti a hadihajó-állások számára. @L@L Adózás @L@P Bár ebben a bemutatóban kereskedelemből és exportból nem szerezhetsz bevételt, adóztatással néhány debent kinyerhetsz a lakosságból. Építs elegendő adószedőt az egész város lefedésére, különösen a legdrágább lakónegyedekben."
                }
            }
            message_tutorial_the_gods_of_egypt {
                id: 258
                type: 2
                message_type: 4
                size [40, 30]
                title { text: "Egyiptom istenei" }
                content {
                    text: "Egy egyiptomi város nem virágozhat igazán megfelelő vallási helyek, templomok és szentélyek nélkül. Ezeket az általuk szolgált házak közelében kell elhelyezni, és az öt isten egyikének kell szentelni: @L@P Ozirisz – A Nílus istene @P Ré – A Királyság istene @P Ptah – A kézművesek istene @P Széth – A pusztítás istene @P Baszt – Az otthon istennője @L@P Minden városnak eltérő vallási szokásai vannak. Egy adott városban általában egy istent különösen nagy tisztelet övez – őt nevezik a város „védőistenének” –, míg a többi istent csupán „helyi istenségként” tisztelik (más istenek pedig teljesen ismeretlenek lehetnek). Thinis védőistene Baszt. @P Mind a védőistenek, mind a helyi istenségek ellenségessé válhatnak, ha nem kapják meg a nekik járó tiszteletet. Az istenek kiengeszteléséhez építs elegendő számú, nekik szentelt templomot és szentélyt, hogy kiszolgáld jelenlegi lakosságodat. @P Egy működő templom papot küld a közeli városrészekbe, aki hozzáférést biztosít lakóiknak istene tiszteletéhez. @G73 @L Ünnepségek @P Az ünnepségek szintén az istenek kiengesztelésének egyik módját jelentik. Építs fesztiválpavilont a városban, majd utasítsd a Templomok felügyelőjét, hogy rendezzen ünnepséget valamelyik isten tiszteletére. @L@L Templomok felügyelője @L@P A Templomok felügyelőjénél tájékozódhatsz az egyes istenek állapotáról bármely városban, és arról, hogy megfelelően kiengesztelték-e őket. A villámok azt jelzik, hogy az isten ellenséges a várossal szemben, míg a kék misztikus jel azt mutatja, hogy jóindulattal viseltetik iránta. Minél többet látsz valamelyik jelből, annál valószínűbb, hogy városod erősebben érzi az adott isten jelenlétét (jó vagy rossz értelemben). @P Kattints a „Rétegek: Vallás” gombra, hogy lásd, mely házakat szolgálják ki városod templomai."
                }
            }
            message_tutorial_industry {
                id: 259
                type: 2
                message_type: 4
                size [40, 30]
                title { text: "Ipar" }
                content { text: "Most, hogy biztosítottad néped számára az alapvető élelmet és vizet, más árukkal, például fazekasáruval is javíthatod életmódjukat. @L@L Ipar és fazekasság @L@P Építs agyagbányát víz közelében, és egy fazekasműhelyt a közelben. Ügyelj rá, hogy ezek az épületek is hozzáférjenek a munkaerőhöz, és hamarosan egy kocsi agyagot szállít a fazekasműhelyhez, ahol fazekasárut készítenek városod számára. @P Építs tárolóudvart a késztermék, valamint a fazekas által fel nem használt felesleges agyag tárolására (egy agyagbánya általában két fazekasműhelyt is el tud látni elegendő agyaggal). @P A bazár dolgozói összegyűjtik a fazekasárut a tárolóudvarból, és ugyanúgy osztják szét, ahogy az élelmet. @G74 @L Az olyan iparágak, mint a fazekasság, a város lakóinak fontos munkalehetőségeket is biztosítanak. Mostantól a Munkások felügyelőjét is segítségül hívhatod a munkaerő elosztásában." }
            }
            message_tutorial_trade_with_other_cities {
                id: 260
                type: 2
                message_type: 4
                size [40, 30]
                title { text: "Kereskedelem más városokkal" }
                content { text: "Most, hogy sikerült néhány emberedet oktatásban részesíteni, további bevételt szerezhetsz a felesleges papirusz eladásával a szomszédos városoknak. A szent masztaba sír felépítéséhez téglát is be kell importálnod Perwadjytból. Amikor készen állsz, kattints a világtérkép ikonra [grafika helye], hogy megtekintsd az ismert világ többi városát, és megkezdhesd a kereskedelem kialakítását." }
            }

            message_tutorial_flooded_clay_pit {
                id: 271
                type: 2
                message_type: 1

                size [30, 20]
                title { text: "Elárasztott agyagbánya" }
                content { text: "Egyik agyagbányánkat szörnyű árvíz pusztította el. Le kellett rombolnunk az agyagbányát, hogy megakadályozzuk, hogy mások is beleessenek." }
            }

            message_kingdom_road_blocked {
                id: 279
                type: 2
                message_type: 1

                size [30, 20]
                title { text: "A királyi út elzáródott" }
                content { text: "A közelmúlt építkezései elzárták az ezen a vidéken áthaladó @57királyi&utat. A királyi építészek újra megnyitották ezt a fontos útvonalat... de ehhez egy-két épületet el kellett távolítaniuk!" }
            }

            message_wrath_of_ra {
                id: 280
                type: 2
                message_type: 1

                size [30, 20]
                title { text: "Ré haragja" }
                video { text: "@23" }
                content { text: "Ré megbünteti gőgödet azzal, hogy jelentősen csökkenti hírnevedet az egész Királyságban. Ahogy te elutasítottad az istent, úgy más egyiptomiak is lenéznek majd téged." }
            }

            message_wrath_of_seth {
                id: 281
                type: 2
                message_type: 1

                size [30, 20]
                title { text: "Seth haragja" }
                video { text: "@21" }
                content { text: "Seth iránti közönyöd arra készteti az istent, hogy elpusztítsa minden hajódat!" }
            }

            message_wrath_of_seth_2 {
                id: 281
                type: 2
                message_type: 1

                size [30, 20]
                title { text: "Seth haragja 2" }
                video { text: "@21" }
                content { text: "Seth iránti közönyöd arra készteti az istent, hogy elpusztítsa minden hajódat!" }
            }

            message_the_world_map {
                id: 282
                type: 2
                message_type: 4
                size [40, 30]
                title {
                    text: "A világtérkép",

                }
                content {
                    text: "A világtérkép megmutatja saját városod, valamint a világ többi városának helyét. Itt fizethetsz azért, hogy kereskedelmi útvonalakat nyiss meg a kereskedni hajlandó városokkal. @L@L Más városok @L A kereskedni kívánó városok színesen jelennek meg a térképen, és zászlót viselnek. Azok a városok, amelyek nem kereskednek veled, fakó színnel láthatók. Kereskedelmi útvonal létrehozásához kattints arra a városra, amellyel üzletelni szeretnél. @L@L Import és export @L Miután létrehoztál egy kereskedelmi útvonalat, a Kereskedelmi felügyelőnél még meg kell adnod, milyen nyersanyagokat és árukat kívánsz importálni vagy exportálni. Ugyanazt az árut soha nem importálhatod és exportálhatod egyszerre."
                }
            }

            message_tutorial_monuments {
                id: 283
                type: 2
                message_type: 4
                size [40, 30]
                title { text: "Emlékművek" }
                content {
                    text: "A téglakészlet biztosításával készen állsz a szent masztaba sír építésének megkezdésére. A legtöbb emlékműhöz képzett és képzetlen munkásokra is szükség van. @L@L Építőcéhek @L Az építőcéhek biztosítják az emlékművek felállításához szükséges képzett munkaerőt. A masztaba teljes egészében téglából készül, ezért csak téglakészítő céhekre van szükség az építéséhez. Annyi téglakészítő céhet alkalmazhatsz, amennyit gazdaságod elbír, de ügyelj rá, hogy elegendő tégla érkezzen az építkezéshez, hogy folyamatosan dolgozhassanak. @P Miután a téglakészítő céh elegendő munkaerővel rendelkezik, téglakészítőket küld az építkezéshez, ahol megvárják, amíg a képzetlen paraszti munkások téglát szállítanak nekik. @L@L Paraszti munkaerő @L Amint néhány téglakészítő utánpótlásra vár az emlékmű helyszínén, parasztmunkások csoportjai kezdik el hozzájuk hordani a téglát. Mivel ugyanezeknek a munkásoknak az ártéri földeken is dolgozniuk kell, az emlékmű építése lelassulhat, amikor az árvíz visszahúzódik, és a parasztok visszatérnek a földekre. További munkatáborokat építhetsz, így a földeken nem szükséges fölös munkaerő egész évben az emlékművön dolgozhat. @G75 @L@L Kezdd a Vallási épületek ikonra kattintva, majd keress megfelelő helyet ennek a nagy épületnek."
                }
            }

            message_the_finer_things {
                id: 284
                type: 2
                message_type: 4
                size [40, 30]
                title {
                    text: "A kifinomultabb dolgok"
                }
                content {
                    text: "Templomkomplexumok @LAhogy az egyiptomiak egyre nagyobb odaadással tisztelik védőisteneiket, egyre nagyobb szentélyeket követelnek maguknak. A legtöbb város templomkomplexumot szeretne emelni választott istenének, hogy teljes mértékben élvezhesse annak kegyeit. Elkészülte után a templomkomplexum egy jósda és egy oltár hozzáadásával bővíthető, melyeket más, kisebb isteneknek szentelnek. Ezek az istenek szintén bizonyos előnyöket biztosítanak a városnak. @L@LÉkszerek @L Megfelelő drágakőkészlet birtokában városod ékszerészei ékszereket készíthetnek. Az ékszer értékes luxuscikk, amelyet a város magasabb társadalmi rétegei igényelnek. @L@LLuxuscikkek @L A helyben készített ékszereken kívül az egyiptomiak más luxuscikkeket is nagyra becsülnek, amelyekhez csak importálással lehet hozzájutni. Egy városnak többféle luxuscikkhez is hozzá kell férnie, hogy valóban civilizálttá váljon. @L@LKőfejtés @L A kő, amely igen keresett építőanyag, kitermeléséhez építs kőfejtőt egy sziklakiemelkedés mellé. A kőfejtők egyenként szállítják a kőtömböket a tárolóudvarba. Alkalmazz építészeket, hogy megakadályozd a kőfejtők beomlását!"
                }
            }

            message_innovations {
                id: 285
                type: 2
                message_type: 4
                size [40, 30]
                title {
                    text: "Újítások"
                }
                content {
                    text: "Rétgazdálkodás @L Egyes földek elég termékenyek a földműveléshez akkor is, ha nem helyezkednek el az ártéren. Ezeket a réteket a magas, sárga növényzet alapján ismerheted fel. A réteken létesített egyes gazdaságok évente egynél több termést is hozhatnak, bár a hozamuk általában valamivel kisebb, mint az ártéri földeké. @G59 @L@LÖntözés @L Öntözéssel növelheted bármely termőföld termékenységét. Az ártéri öntözőcsatornák közvetlenül a Nílushoz kapcsolhatók, de szárazföldön vízemelőre lesz szükséged a víz felemeléséhez. @L@LVízemelők @L Vízemelőket az ártér szélén vagy a parton lehet építeni, ahol közvetlenül a folyóból emelhetik a vizet a szárazföldre. Kapcsolj egy öntözőcsatornát a vízemelő hátuljához, hogy az öntözővizet a belső területeken lévő földekhez vezesd. @L@LKőfaragók és ácsok @L A lépcsős piramis felépítéséhez két új építőcéhre lesz szükség: a kőfaragók céhére és az ácsok céhére. A kőfaragó céh munkásai az építkezésnél várják a kőtömböket, amelyeket paraszti munkások szállítanak oda. Ezeknek a tömbszállítóknak rámpákra van szükségük, hogy elérjék az építmény magasabb szintjeit. Amikor eljön az ideje, hogy a lépcsős piramis újabb szinttel emelkedjen, egy ács fát visz a céhtől az építkezéshez, és rámpát épít a tömbszállítóknak. @L@L A holtak megőrzése @L Minden városnak szüksége van néhány balzsamozóra a higiénia fenntartásához, valamint azért, hogy fejlettebb lakói megfelelő temetési szertartásokban részesüljenek. A halottasház a szövő által készített vásznat használja, és a környező házak számára balzsamozási szolgáltatásokat biztosít."
                }
            }

            message_troops_return_failed {
                id: 287
                type: 2

                size [30, 20]
                title { text: "A század visszatér" }
                content { text: "Az éj leple alatt a megszégyenült század túlélői visszasomfordálnak a város erődjeinek biztonságába, elhatározva, hogy többé nem szenvednek megaláztatást a csatatéren." }
            }
            message_troops_return_victorious {
                id: 288
                type: 2

                size [30, 20]
                title {
                    text: "A hősök hazatérnek!"
                }
                content {
                    text: "Győztes katonáid hazatértek a háborúból. Létszámuk talán csökkent valamelyest távozásuk óta, de bajtársaik áldozata Egyiptom javát szolgálta!"
                }
            }
            message_city_retaken {
                id: 289,
                    type: 2,

                    size [30, 20]
                title { text: "A várost visszafoglalták" }
            }
            message_osiris_is_upset {
                id: 290
                type: 2

                size [30, 20]
                title { text: "Ozirisz haragszik" }
                content { text: "A nílusi áradás ura megbünteti ezt a várost odaadásának hiánya miatt, és a következő évi áradás minden útjába kerülő földet elpusztít!" }
            }
            message_ra_is_upset_2 {
                id: 291
                type: 2

                size [30, 20]
                title { text: "Ré haragszik" }
                video { text: "@23" }
                content { text: "Ré megharagudott iránti tiszteletlenséged miatt, és csökkenti hírnevedet a Királyság szemében." }
            }
            message_ptah_is_upset {
                id: 292
                type: 2

                size [30, 20]
                title { text: "Ptah haragszik" }
                video { text: "@22" }
                content { text: "Ptah csalódott iránta tanúsított közönyöd miatt, ezért elpusztítja egyik tárolóudvarodat a benne tárolt javakkal együtt." }
            }
            message_seth_is_upset {
                id: 293
                type: 2

                size [30, 20]
                title { text: "Seth haragszik" }
                video { text: "@21" }
                content { text: "Seth emlékeztet rá, hogy az isten csak azokat védi, akik kellő tisztelettel viseltetnek iránta: elpusztítja legjobb katonai századodat, és lerombolja erődjüket." }
            }
            message_bast_is_upset {
                id: 294
                type: 2

                size [30, 20]
                title { text: "Bast haragszik" }
                video { text: "@20" }
                content { text: "Bast istennőt megbántotta közönyöd, ezért járványt küld városodra. Ne feledd, az egészség és a boldogság tőle ered." }
            }
            message_blessing_from_osiris {
                id: 295
                type: 2

                size [30, 20]
                title { text: "Ozirisz áldása" }
                video { text: "@24" }
                content { text: "Ozirisz, a nílusi áradás istene megáldja ezt a várost őszinte odaadásáért. Az ártéri földek minden gazdasága kétszer annyi termést takarít be ebben az évszakban, mint várta!" }
            }
            message_blessing_trade_from_ra {
                id: 296
                type: 2

                size [30, 20]
                title { text: "Ré áldása" }
                video { text: "@23" }
                content { text: "Ré megjutalmazza hűséges követőit! A következő 12 hónapban városod exportárui másfélszeres értéken adhatók el." }
            }
            message_blessing_trade_from_ptah {
                id: 297
                type: 2

                size [30, 20]
                title { text: "Ptah áldása" }
                video { text: "@22" }
                content { text: "Ptah kiválaszt egy szabad kapacitással rendelkező tárolóudvart, és megnöveli az ott található drágakő-, agyag-, fazekasáru-, len-, vászon- vagy ékszerkészletet." }
            }
            message_blessing_trade_from_seth {
                id: 298
                type: 2

                size [30, 20]
                title { text: "Seth áldása" }
                video { text: "@21" }
                content { text: "Seth helyesli félelmedet és engedelmességedet, ezért lesújt a következő ellenségekre, akik megpróbálják megsérteni városodat." }
            }
            message_blessing_from_bast {
                id: 299,
                    type: 2,

                    size [30, 20]
                title { text: "Bast áldása" }
                video { text: "@20" }
                content { text: "Mivel ez a város oly hűséges és odaadó, Bast bőséggel áldja meg házait és bazárjait élelemmel és javakkal!" }
            }
            message_the_gods_are_wrathful {
                id: 300
                type: 2

                size [30, 20]
                title { text: "Az istenek haragszanak" }
                content { text: "Legalább egy isten haragszik a városra. Néped arra kér, hogy építs több templomot... és egy ünnepségnek is mindig örülnek." }
            }
            message_illness {
                id: 301,
                    type: 2,

                    size [30, 20]
                title { text: "Rosszullét" }
                video { text: "smk\\sick.smk" }
            }
            message_disease {
                id: 302,
                    type: 2,

                    size [30, 20]
                title { text: "Betegség" }
                video { text: "smk\\sick.smk" }
            }
            message_pestilence {
                id: 303,
                    type: 2,

                    size [30, 20]
                title { text: "Járvány" }
                video { text: "smk\\sick.smk" }
            }
            message_the_spirit_of_seth {
                id: 304,
                    type: 2,

                    size [30, 20]
                title {
                    text: "Seth szelleme",
                }
                video {
                    text: "@21"
                }
                content {
                    text: "Seth emlékszik ígéretére, hogy megvéd téged, és örömmel pusztítja el azokat, akik elég ostobák voltak ahhoz, hogy városodat fenyegessék."
                }
            }
            message_the_emperors_respect {
                id: 305,
                    type: 2,

                    size [30, 20]
                title {
                    text: "A császár tisztelete",
                }
            }
            message_the_emperors_respect_1 {
                id: 306,
                    type: 2,

                    size [30, 20]
                title { text: "A császár tisztelete" }
            }
            message_the_emperors_respect_2 {
                id: 307,
                    type: 2,

                    size [30, 20]
                title { text: "A császár tisztelete" }
            }
            message_working_hippodrome {
                id: 308,
                    type: 2,

                    size [30, 20]
                title { text: "Működő hippodrom" }
                video { text: "smk\\\\1st_chariot.smk" }
            }
            message_compliance_now_possible {
                id: 309,
                    type: 2,
                    message_type: 2,

                    size [30, 20]
                title { text: "A teljesítés most lehetséges" }
                content { text: "Politikai felügyelőd jelenti, hogy a városban most már elegendő deben áll rendelkezésre a legutóbbi kérés teljesítéséhez." }
            }
            message_tutorial_finances {
                id: 310,
                    type: 2,
                    message_type: 4
                size [40, 30]
                title { text: "Pénzügyek" }
                content {
                    text: "Adózás @L Egy nagy városnak kezdeti támogatásán túl további bevételre van szüksége. Ennek egyik módja az adóztatás. Adók beszedéséhez városodnak palotára és adószedőkre lesz szüksége. Ügyelj rá, hogy elegendő adószedőt építs az egész város lefedésére, különösen a tehetősebb negyedekben. Ne feledd: minél jobb életminőséget élvez egy ház, annál több adót fizetnek a lakói. @L@L Személyes fizetésed @L Ha magadnak kúriát építesz, személyes fizetést vehetsz fel a város kincstárából. A személyes vagyonodat a családod megtartja, és bármikor felhasználhatod, még későbbi küldetések során is. Vigyázz azonban: ha a rangodhoz méltónál magasabb fizetést állapítasz meg magadnak, az károsan hathat a királyságban elfoglalt helyzetedre."
                }
            }
            message_mission_defeat {
                id: 311,
                    type: 2,

                    size [30, 20]
                title { text: "Vereség!" }
                content { text: "Keserű nap! Méltatlan bukásod elképzelhetetlen kellett volna, hogy legyen. Cserbenhagytad népedet, őseidet és utódaidat. Egyiptom most új bajnokra vár, aki átveszi helyed..." }
            }
            message_mission_victory {
                id: 312,
                    type: 2,

                    size [30, 20]
                title { text: "A győztes" }
                video { text: "smk\\win_game.smk" }
                content { text: "Nem használt bejegyzés 312" }
            }
            message_enemy_rome_army_attacks {
                id: 313
                type: 2
                message_type: 7

                size [30, 20]
                title { text: "Ellenséges sereg támad" }
                video { text: "smk\\spy_army.smk" }
                content { text: " Róma ellenségei városod határában vannak. Számíts rá, hogy beugranak egy-két korsó borért - és bármi másért, ami megtetszik nekik!" }
            }
            message_storage_yards_ready_to_fulfill_request {
                id: 314,
                    type: 2,
                    message_type: 2,

                    size [30, 20]
                title {
                    text: "A kérés teljesíthető",
                }
                content {
                    text: "Politikai felügyelőd jelenti, hogy a városi raktárakban már elegendő áru van a legutóbbi kérés teljesítéséhez."
                }
            }
            message_kingdom_road_obstructed {
                id: 315,
                    type: 2,

                    size [30, 20]
                title {
                    text: "A királysági út elzárva",
                }
                content {
                    text: "Az építészeknek le kellett bontaniuk néhány új építményt, hogy helyreállítsák a szabad átjárást a @57Királysági&úton."
                }
            }
            message_no_working_dock {
                id: 316,
                    type: 2,

                    size [30, 20]
                title { text: "Nincs működő kikötő" }
                content { text: "Bár utasítottad a kereskedelmi felügyelőt, hogy kezdjen kereskedni egy tengeri kereskedővel, az nem tud kikötni városodban! Kikötőt kell építened, és munkásokat kell biztosítanod hozzá. Amint a kikötő működik, a hajók megérkeznek és megkezdik a kereskedést." }
            }
            message_fishing_boats_cant_navigate {
                id: 317,
                    type: 2,

                    size [30, 20]
                title { text: "A halászhajók nem tudnak közlekedni" }
                content { text: "Halászaink jelentik, hogy egy híd elzárja az útjukat! A hajók nem tudnak áthajózni a hidak alatt. Távolítsd el a hidat, hogy a halászhajók friss hallal láthassák el városodat." }
            }
            message_health {
                id: 318,
                    type: 3,

                    size [30, 20]
                title {
                    text: "Egészség",
                }
                content {
                    text: "Az emberek szeretnek egészségesek lenni. Ha jól táplálkoznak, és rendszeresen meglátogatja őket egy orvos a rendelőből, egészségesek maradnak. Ha egészségük romlik, nagyobb eséllyel betegszenek meg. @PKórházakra akkor van szükség, amikor a polgárok megbetegszenek. A betegek gyógyításához kórház kell. Ha nincs hely a kórházban, meghalnak. @PTehát: a rendelők a betegségek megelőzését, a kórházak pedig a gyógyítást szolgálják. @L@LNéha járvány törhet ki, és Bast köztudottan betegséget küld azokba a városokba, amelyek haragját kivívták. Ilyenkor a megfelelő kórházi ellátás az egyetlen védelem. A közegészségügyi felügyelőd megmondhatja, hogy megfelelő-e a kórházi ellátásod."
                }
            }
            message_messages_await_you {
                id: 319,
                    type: 3,

                    size [30, 20]
                title {
                    text: "Üzenetek várnak rád",
                }
                content {
                    text: "Amikor fanfárt hallasz, az azt jelenti, hogy írnokod új üzenetet kapott számodra, és elmentette feljegyzései közé. @L@L Néhány üzenet, mint ez is, automatikusan megnyílik előtted. Ezek sürgős ügyek, amelyekről írnokod szerint azonnal tudnod kell. Később is átnézheted őket, ha az üzenetek gombjára kattintasz. @PFontos, de nem sürgős üzeneteket különleges fanfár jelez, ám nem jelennek meg automatikusan. A legtöbb üzenet hétköznapi üzenet, amelyet normál fanfár kísér, és akkor tekintheted meg, amikor szeretnéd. @L@LÍrnokod minden üzenetet megőriz, így később bármikor visszatérhetsz hozzájuk. Ha akarod, törölheted is őket. További információért válaszd a Súgót a menüsorból, majd kattints az „Írnokaid üzenetei” lehetőségre (a tartalomjegyzék vége felé)."
                }
            }
            message_local_uprising {
                id: 320,
                    message_type: 7

                size [30, 20]
                urgent: 1
                title { text: "Helyi felkelés" }
                content { text: "Seth ösztönzésére néhány helybéli úgy döntött, hogy hangot ad régóta dédelgetett sérelmeinek ellened!!" }
            }
            message_small_blessing_from_osiris {
                id: 321
                type: 2

                size [30, 20]
                title { text: "Ozirisz kisebb áldása" }
                video { text: "@24" }
                content { text: "Ozirisz észrevette városod hűséges odaadását. A Nílus következő áradása a vártnál kedvezőbb lesz." }
            }
            message_minor_blessing_from_ra {
                id: 322
                type: 2

                size [30, 20]
                title { text: "Ré kisebb áldása" }
                video { text: "@23"}
                content { text: "Helyes tiszteleted által bátorítva Ré valamelyest növeli hírnevedet az egész Királyságban." }
            }
            message_minor_blessing_from_ptah {
                id: 323
                type: 2

                size [30, 20]
                title { text: "Ptah kisebb áldása" }
                video { text: "@22" }
                content { text: "Ptah elégedett a figyelmeddel, ezért gondoskodik róla, hogy városod hajóácsai, takácsai vagy ékszerészei elegendő nyersanyaggal rendelkezzenek." }
            }
            message_minor_blessing_from_seth {
                id: 324
                type: 2

                title { text: "Seth kisebb áldása" }
                video { text: "@21" }
                content { text: "Engedelmességed jutalmául Seth megfogadja, hogy megvédi a távoli földeken csatába küldött katonáidat." }
            }
            message_small_blessing_from_bast {
                id: 325
                type: 2

                size [30, 20]
                title { text: "Bast kisebb áldása" }
                video { text: "@20" }
                content { text: "Bast örül, hogy városod tiszteli őt. Ünnepséget rendezett, hogy minden isten felfigyeljen jámborságodra." }
            }
            message_disease_strikes {
                id: 326,
                    type: 2,
                    message_type: 1,

                    size [30, 20]
                title {
                    text: "Betegség pusztít",
                }
                content {
                    text: "Betegség sújtott egy háztartást, ahol nem volt megfelelő az egészségügyi ellátás. Emberek halnak meg, és nem tudsz segíteni rajtuk. Javítsd az egészségtelen területeket, hogy megelőzd az újabb járványt."
                }
            }
            message_a_plague {
                id: 327,
                    type: 2,
                    message_type: 1,

                    size [30, 20]
                title {
                    text: "Járvány",
                }
                content {
                    text: "Járvány sújtja a várost! Attól tartottunk, hogy ez bekövetkezik, mivel az egész város @53egészségi&állapota igen rossz. Imádkozzunk, hogy patikusaink megbirkózzanak vele."
                }
            }
            message_malaria {
                id: 328,
                    type: 2,
                    message_type: 1,

                    size [30, 20]
                title {
                    text: "Malária",
                }
                content {
                    text: "Néhány háztartásban malária ütötte fel a fejét. Jobb egészségügyi intézkedésekkel megelőzhető lenne ez az értelmetlen emberveszteség!"
                }
            }
            message_blessing_reputation_from_ra {
                id: 329,
                    type: 2,

                    size [30, 20]
                title { text: "Ré áldása" }
                video { text: "@23" }
                content {
                    text: "Megtisztelted Rét, ezért hírneved a Királyságban jelentősen jobb lett, mint korábban volt!"
                }
            }
            message_minor_blessing_trading_from_ra {
                id: 331,
                    type: 2,

                    size [30, 20]
                title { text: "Ré kisebb áldása" }
                video { text: "@23" }
                content { text: "Tiszteletteljes hozzáállásod elismeréseként Ré arra ösztönzi kereskedelmi partnereidet, hogy többet kereskedjenek, mint korábban." }
            }
            message_wrath_of_ra_2 {
                id: 332,
                    type: 2,

                    size [30, 20]
                title { text: "Ré haragja" }
                video { text: "@23" }
                content { text: "Kivívtad Ré haragját! Az isten rontotta városod áruinak megítélését, így kereskedelmi partnereid most jóval kevesebbet fognak kereskedni, mint korábban." }
            }
            message_wrath_of_ra_3 {
                id: 333,
                    type: 2,

                    size [30, 20]
                title { text: "Ré haragja" }
                video { text: "@23" }
                content { text: "Ahogy elhagytad Rét, úgy hagynak el téged kereskedelmi partnereid is. Egy teljes éven át egyetlen kereskedőhajó vagy karaván sem látogatja meg városodat." }
            }
            message_ra_is_upset {
                id: 334,
                    type: 2,

                    size [30, 20]
                image { id: 224, pos [15, 15] }
                title { text: "Ré elégedetlen!" }
                video { text: "@23" }
                content { text: "Ahogy semmibe vetted Rét, úgy fogják kereskedelmi partnereid is semmibe venni városod áruit. Úgy döntöttek, csökkentik a veled folytatott kereskedelem mennyiségét." }
            }
            message_wrath_of_bast_2 {
                id: 335,
                    type: 2,

                    size [30, 20]
                title { text: "Bast haragja", }
                content { text: "Városod elkerülte Bast haragját -- az istennő a legszebb házaidat akarta lerombolni, de ma nem talált olyan otthonokat, amelyek méltók lettek volna dühéhez. Ennek ellenére óvakodj az Otthon Istennőjének felingerlésétől, mert türelmes, és emlékezete hosszú. Mutasd meg Bastnak a neki járó tiszteletet, mielőtt visszatér." }
            }
            message_wrath_of_ra_4 {
                id: 336,
                    type: 2,

                    size [30, 20]
                title {
                    text: "Ré haragja",
                }
                content {
                    text: "Ré gondoskodni fog róla, hogy megbűnhődj tiszteletlenségedért!"
                }
            }
            message_wrath_of_osiris_3 {
                id: 337,
                    type: 2,

                    size [30, 20]
                title {
                    text: "Ozirisz haragja",
                }
                video {
                    text: "@24"
                }
                content {
                    text: "Ozirisz feldühödött, bár nincs hatalma megbüntetni városodat. Élvezd ezt, amíg lehet, mert legközelebb városod talán nem lesz ilyen szerencsés."
                }
            }
            message_blessing_inundation_from_osiris {
                id: 340,
                    type: 2,

                    size [30, 28]
                title { text: "Ozirisz megáld téged" }
                video { text: "@24" }
                content { text: "Ozirisz megjutalmazza azokat, akik hódolnak előtte. A következő áradás jelentősen jobb lesz a vártnál." }
            }
            message_wrath_of_osiris_4 {
                id: 341,
                    type: 2,

                    size [30, 20]
                title { text: "Ozirisz haragja" }
                video { text: "@24" }
                content { text: "Ozirisz emlékeztet rá, hogy tisztelet jár neki. A következő áradás gyengébb lesz a vártnál." }
            }
            message_mediocre_inundation_seers {
                id: 342,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "Látnokaink figyelmeztetnek, hogy a következő év áradása legfeljebb közepes lehet." }
            }
            message_poor_inundation_seers {
                id: 343,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "A papok gyenge áradást várnak a következő évben." }
            }
            message_no_inundation {
                id: 344,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "Szörnyű hír! Minden jel arra utal, hogy idén egyáltalán nem lesz áradás!" }
            }
            message_poor_inundation {
                id: 345,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "A papok gyenge áradást jósolnak a következő évre. Néped arra kér, hogy gondoskodj Ozirisz kiengeszteléséről, és jobb áradásokért imádkozik az elkövetkező évekre." }
            }
            message_mediocre_inundation {
                id: 346,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "A következő áradás várhatóan legfeljebb közepes lesz. Talán Ozirisz kegyességét élvezhetjük, ha gondoskodunk kiengeszteléséről." }
            }
            message_good_inundation {
                id: 347,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "Minden jel arra mutat, hogy a következő évben jó áradás lesz." }
            }
            message_excellent_inundation {
                id: 348,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "A gazdák örömmel fogadják a következő év kiváló áradásáról szóló jóslatokat!" }
            }
            message_perfect_inundation {
                id: 349,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title { text: "Nilométer jóslata" }
                content { text: "A papok azt jósolják, hogy a várost tökéletes áradás áldja meg a következő évben!" }
            }
            message_temple_complex_to_osiris {
                id: 350,

                    size [30, 20]
                title {
                    text: "Ozirisz templomkomplexuma",
                }
                subtitle {
                    text: "Vallás",
                }
                content {
                    text: "Amikor templomkomplexumot építesz Ozirisznek, az isten hajlamos jobb áradásokat küldeni évről évre. A következő építményeket helyezheted el Ozirisz templomkomplexumában: @L@LSzebek oltára, a termékenység istene @LSzebek képessé teszi Ozirisz papjait arra, hogy városod élelmiszer- és áruellátása tovább kitartson. Ahogy Ozirisz papjai bejárják városodat, az általuk érintett házak lakói hirtelen kevesebbel is beérik. @L@LMín jóshelye, az újjászületés istene @LHa városod jóshellyel tiszteli Mínt, felgyorsítja a fák és nádasok újranövését, növeli a vadállatok szaporodási ütemét, és javítja a halászatból és vadászatból származó hozamot. @L@LAz emberek szeretnek templomkomplexum mellett élni. A vallásról további információért kattints @51ide. @L@LTudj meg többet Oziriszről, Szebekről és Mínről az ókori Egyiptomban, ha @376ide kattintasz."
                }
            }
            message_temple_complex_to_ra {
                id: 351,

                    size [30, 20]
                title {
                    text: "Ré templomkomplexuma",
                }
                content {
                    text: "Ré mosolyog a városra, amikor templomkomplexumot szentelnek neki, és gondoskodik róla, hogy a Királyság más lakói is mosolyogjanak városodra. A Rének épített templomkomplexum növeli Királyság-megítélésedet, és ha a város eladósodik, alacsonyabb kamatlábat biztosít. Ré templomkomplexumához oltár és jóshely építésével könnyebben irányíthatod a város ügyeit: @L@LMa'at oltára, az igazságosság istennője @LRé papjain keresztül Ma'at nyugalmat áraszt városodban. Ahogy elhaladnak a házak mellett, Ré papjai eltántorítják a lakókat a tolvajlástól. Az oltár puszta jelenléte is csökkenti a bűnözés kialakulásának kockázatát. @L@LHórusz jóshelye, a fáraók istene @LEz a jóshely növeli a polgárok városod és a Királyság iránti elkötelezettségét, így alacsonyabb bért is elfogadnak anélkül, hogy kedvük romlana. @L@LAz emberek szeretnek templomkomplexum mellett élni. A vallásról további információért kattints @51ide. @L@LTudj meg többet Réről, Ma'atról és Hóruszról az ókori Egyiptomban, ha @377ide kattintasz."
                }
            }
            message_temple_complex_to_ptah {
                id: 352,

                    size [30, 20]
                title {
                    text: "Ptah templomkomplexuma",
                }
                content {
                    text: "Amikor templomkomplexumot építesz neki, Ptah felgyorsítja városod számos iparágának termelését, köztük az aranybányák, rézbányák, drágakőbányák, agyaglelőhelyek, hajóácsok, ékszerészek és takácsok munkáját. Ptah templomkomplexumának oltára és jóshelye felgyorsítja más iparágak termelését, és javítja az oktatók képességeit: @L@LAmon oltára, a napisten @LFigyelmeddel megtisztelve Amon gyorsabb munkára ösztönzi a kőfejtőket, favágókat és téglagyárakat. @L@LThot jóshelye, a bölcsesség és tanulás istene @LThot célja, hogy a tanulás fényét minél több emberhez eljuttassa. Amikor Thot jóshelyét megépíted, a könyvtárosok és tanítók kevesebb papiruszt használnak a város lakóinak oktatására. @L@LAz emberek szeretnek templomkomplexum mellett élni. A vallásról további információért kattints @51ide. @L@LTudj meg többet Ptahról, Amonról és Thotról az ókori Egyiptomban, ha @378ide kattintasz."
                }
            }
            message_temple_complex_to_seth {
                id: 353,

                    size [30, 20]
                title { text: "Seth templomkomplexuma" }
                content { text: "Amikor egy város templomkomplexumot szentel neki, Seth vad elszántságot önt a város katonáiba, több tapasztalatot adva nekik és védelmezve őket a csatában. Seth templomkomplexumának kiegészítői: @L@LAnubisz oltára, a halál istene @LAnubisz könnyebbé teszi a polgárok számára az örök élet elérését. Áldásával a halottasházaknak kevesebb vászonra van szükségük a testek örökkévalóságra való előkészítéséhez. @L@LSzakhmet jóshelye, a háború istennője @LSzakhmet képessé teszi Seth papjait arra, hogy csökkentsék a bűnözés kockázatát az általuk érintett házakban, és elfogják a bűnözőket a városban. @L@LAz emberek szeretnek templomkomplexum mellett élni. A vallásról további információért kattints @51ide. @L@LTudj meg többet Sethről, Anubiszról és Szakhmetről az ókori Egyiptomban, ha @379ide kattintasz." }
            }
            message_temple_complex_to_bast {
                id: 354,

                    size [30, 20]
                title { text: "Bast templomkomplexuma" }
                content { text: "A Bastnak épített templomkomplexum szerencsét hoz minden városnak. Bast segít boldoggá tenni a polgárokat azzal, hogy kevesebbel is elégedettek lesznek. Jóindulatának köszönhetően csökken a polgárok élelmiszer- és áru-fogyasztása, valamint a szórakoztatók, oktatók és egészségügyi dolgozók hatása tovább tart. Nővéristennői is javítják polgáraid életét: @L@LÍzisz oltára, a gyógyítás istennője @LBast papnőin keresztül Ízisz gyógyító kezét a város lakóira helyezi, eltávolítva a járvány sújtotta embereket az utcákról, és megtisztítva azokat a fertőzött házakat, amelyek mellett a papnők elhaladnak. Ízisz emellett gondoskodik városod általános egészségének javításáról is. @L@LHathor jóshelye, az öröm, szerelem és ünnepségek istennője @LHathor, akit lenyűgöz a neki épített jóshely, javítja a polgárok hangulatát, ami jobb @39Városi&hangulatot eredményez. @L@LAz emberek szeretnek templomkomplexum mellett élni. A vallásról további információért kattints @51ide. @L@LTudj meg többet Bastról, Íziszről és Hathorról az ókori Egyiptomban, ha @380ide kattintasz." }
            }
            message_building_firehouse {
                id: 355,

                    size [30, 20]
                title {
                    text: "Tűzoltóság",
                }
                content {
                    text: "A város néhány épülete kigyulladhat. Valószínű célpontok a rossz állapotú lakóházak és ipari épületek, például a fazekasműhelyek. Ha nem teszel semmit a megfékezésére, a tűz végigterjedhet a városon, és egész városrészeket pusztíthat el egyszerre. Ennek megelőzésére építs tűzoltóságokat a könnyen kigyulladó épületek közelébe. A tűzoltóságok tűzoltói bejárják a várost (a járókelőkről további információért kattints @42ide), és csökkentik az épületek tűzveszélyét, amikor elhaladnak mellettük. @PHa tűz üt ki, a közeli tűzoltók a helyszínre sietnek, hogy eloltsák a lángokat. Ha egy tűzoltónak messzire kell utaznia, a lángok továbbterjedhetnek, és a pusztítás súlyos lehet a városodban. @G67 @PA @18tűz&fedőréteg hasznos útmutató a tűzmegelőzéshez. A fedőréteg megmutatja a tűzoltók munkáját, de ami még fontosabb, jelzi, mely épületek különösen hajlamosak a kigyulladásra. Használd ezt az információt következő tűzoltóságod helyének megtervezéséhez. @PTűzoltóságok működéséhez úthálózat és munkaerő szükséges. A lakók nem szívesen élnek tűzoltóságok közelében."
                }
            }
            message_building_warship_wharf {
                id: 356,

                    size [30, 20]
                title {
                    text: "Hadihajó-kikötő",
                }
                content {
                    text: "A hadihajó-kikötők hadihajókat fogadnak. Egy új hadihajó-kikötő első dolga, hogy hadihajót rendeljen a @82hajóácstól. @EA hadihajó-kikötőhöz úthálózat és munkaerő is szükséges. Egyenes partszakaszon kell elhelyezni, és a hajóknak könnyen el kell tudniuk jutniuk a kikötőhöz. A polgárok nem akarnak túl közel élni egy hadihajó-kikötőhöz. Egyes tengerészeknek ugyanis nem a legjobb a híre. @PAmikor egy hadihajó éppen nem csatázik, legénysége inkább a kikötő biztonságába tér vissza. Itt kipihenhetik magukat a következő ütközet előtt. @POlvasd el a @365hadihajók bejegyzést, hogy megtudd, hogyan irányíthatsz hajót csatában. @L@LAz ókori Egyiptom katonai hagyományai hosszú és dicsőséges múltra tekintenek vissza. További információért kattints @184ide."
                }
            }
            message_building_transport_wharf {
                id: 357,

                    size [30, 20]
                title {
                    text: "Szállítóhajó-kikötő",
                }
                content {
                    text: "A szállítóhajó-kikötők szállítóhajókat fogadnak. Egy új szállítóhajó-kikötő első dolga, hogy szállítóhajót rendeljen egy @82hajóácstól. @EA szállítóhajó-kikötőhöz úthálózat és munkaerő is szükséges. Egyenes partszakaszon kell elhelyezni, és a hajóknak könnyen el kell tudniuk jutniuk a kikötőhöz. Polgáraid nem akarnak túl közel élni egy szállítóhajó-kikötőhöz. @POlvasd el a @367szállítóhajók bejegyzést, hogy megtudd, hogyan irányíthatsz hajót csatában. @L@LAz ókori Egyiptom katonai hagyományai hosszú és dicsőséges múltra tekintenek vissza. További információért kattints @181ide."
                }
            }
            message_building_roadblock {
                id: 358,

                    size [30, 20]
                title {
                    text: "Útzár",
                }
                content {
                    text: "Az útzárak segítenek irányítani a @42vándorló&járókelők útvonalait. Amikor a várost bejáró járókelők útzárba ütköznek, visszafordulnak. Az útzárak nem befolyásolják a célállomás felé tartó járókelőket. @PÉpíts útzárat olyan helyekre, ahová a várost járó embereknek nem kell eljutniuk - például az ipari területekre vezető útra. Vigyázz azonban, hogy ne zárj el teljesen területeket a városban járó emberektől. Ugyanaz az útzár, amely megakadályozza, hogy egy bazári kereskedő az ipari negyedbe tévedjen, az építészeket, tűzoltókat és rendfenntartókat is visszafordítja. Emellett megakadályozza, hogy a munkaerő-toborzók az ipari területről a lakónegyedbe jussanak, ahol dolgozókat találnának. @G62 @PAmikor új útzárat építesz egy meglévő épület közelében, érdemes egy ideig figyelni az épületet, hogy megbizonyosodj róla: a járókelő a megfelelő oldalon lép ki az útzárhoz képest. Néha az épület dolgozói nem értik a szándékaidat, és rossz irányba küldik járókelőjüket. Ez különösen bosszantó lehet a munkaerőt kereső épületeknél, mert az őket alkalmazó épület úgy hiszi, hogy hozzáfér a munkaerőhöz, de az útzár megakadályozza, hogy a járókelő valaha elérje a munkaerőpiacot. Az egyetlen megoldás, ha az útzárat egy hellyel távolabb építed újjá. @PAz útzáraknak nincs szükségük dolgozókra, és egyetlen korlátozásuk, hogy úton kell elhelyezni őket. Nincs hatásuk a vonzerőre."
                }
            }
            message_building_hunting_lodge {
                id: 359,

                    size [30, 20]
                title {
                    text: "Vadászház",
                }
                content {
                    text: "Építs vadászházat, hogy vadászokat küldhess a zsákmány után. Struccokra, szárnyasokra és antilopokra is lehet vadászni. @PVadászházat bárhol építhetsz, bár érdemes a zsákmány közelébe helyezni őket, amely általában szaporodóhelyei közelében marad. A vadászházak működéséhez munkaerő és úthálózat is szükséges. Amikor működésbe lépnek, egy vadászt láthatsz az udvaron, amint célba lő. @PA vadászok a házból a mezőkre indulnak, ahol zsákmányuk vár rájuk. Miután elejtették az állatot, visszaviszik a vadászházba, ahol fogyasztásra alkalmassá teszik. Amikor egy kocsi rakomány vadhús elkészül, elszállítják a @3raktárakba vagy a @4tároló&udvarokba (ha azok engedélyezték a vadhús fogadását). @G60 @PA vadhús fontos része lehet a polgárok étrendjének. Változatosságot biztosít, amelyre az emberek vágynak. A város azonban valószínűleg nem tud kizárólag vadhúsból megélni. A csordák és nyájak mérete korlátozott, ezért a vadászat önmagában nem képes egy nagy város teljes élelmiszerigényét kielégíteni. A nép ellátásáról további információért olvasd el a @45mezőgazdaság&és&élelmiszer-termelés részt. @PA vadhúst (a @89szalmával együtt) állatok etetésére is használják az @479állatkertben. @PA vadászházak negatívan befolyásolják a @56vonzóerőt. @L@LAz ókori egyiptomi étrendet vadhússal egészítették ki. A vadászatot pedig a nemesek sportként is kedvelték. További információért kattints @383ide."
                }
            }
            message_building_cattle_ranch {
                id: 360,

                    size [30, 20]
                title {
                    text: "Marhafarm",
                }
                content {
                    text: "Tenyéssz marhákat egy marhafarmon, hogy hússal lásd el a város lakóit. @PA marhafarmokat út mellé kell építeni, és munkaerőre van szükségük. Szalmát is igényelnek, amelyet egy @89gabonafarmról vagy egy @47kereskedelmi&partnertől lehet beszerezni. A marhafarmokat nem kell termékeny földre építeniük, és vízellátásra sincs szükségük. @POlvasd el a @45mezőgazdaság&és&élelmiszer-termelés részt, hogy többet tudj meg a hús szerepéről polgáraid étrendjében. @PA marhafarmok bűzt árasztanak, és a lakók nem szeretnek a közelükben élni. @L@LAz ókori egyiptomiak sokféle állatot tenyésztettek élelem céljából. További információért kattints @186ide."
                }
            }
            message_building_gemstone_mine {
                id: 361,

                    size [30, 20]
                title {
                    text: "Drágakőbánya",
                }
                content {
                    text: "A drágaköveket sziklás kiemelkedésekből bányásszák. Ránézésre nem lehet megállapítani, hogy egy szikla rejt-e drágaköveket. Ha a területen bányászható drágakő található, a drágakőbányák megjelennek az Ipari épületek: Nyersanyagok listájában. A @95kőfejtőkhöz hasonlóan a drágakőbányákat is sziklás kiemelkedések mellé kell építeni, és munkaerőre, valamint úthálózatra van szükségük. Összeomlásra is hajlamosak, ezért mindenképpen építs a közelbe egy @81építész&állomást. @PA drágakőbányák poros helyek, és a polgárok nem szeretnek a közelükben élni. @L@LAz ókori Egyiptom drágaköveiről további információért kattints @382ide."
                }
            }
            message_building_sphinx {
                id: 362,

                    size [30, 20]
                title {
                    text: "Szfinx",
                }
                content {
                    text: "A Szfinx a piramisok díszesen faragott és festett őrzője. @PA Szfinx építéséhez először megfelelő helyet kell találnod. Válaszd a „Szfinx” lehetőséget a Vallási épületek: Emlékművek listájából. Megjelenik a szfinx alaprajza. Ahogy mozgatod az alaprajzot a tájon, vagy teljesen zöld lesz, vagy zöld, egy vagy több vörös gyémánttal. Ha az alaprajz teljesen zöld, megtaláltad a megfelelő rejtett kőtartalékot. Kattints az egérgombbal, és a kő feltárul. Ha vörös gyémánt jelenik meg az alaprajzban, a táj valamely hibája miatt nem építheted ide a Szfinxet. @PMost a @363kőfaragók és @363ácsok munkához láthatnak, feltéve, hogy rendelkezel a szükséges fával. Az ácsok állványzatot építenek, amelyre a kőfaragók felmásznak a Szfinx kifaragásához. @PA Szfinxre jobb gombbal kattintva meglátogathatod az @369építési&felügyelőt a munkálatok állapotjelentéséért. @L@LA leghíresebb Szfinxről szóló leírást @391ide kattintva olvashatod."
                }
            }
            message_construction_guilds {
                id: 363,

                    size [30, 20]
                title {
                    text: "Építőcéhek",
                }
                content {
                    text: "Építőcéhek nélkül nem tudod felépíteni a fáraót és Egyiptomot dicsőítő nagyszerű építményeket. @PNégy különleges építőcéh létezik: az ácsok, téglavetők, kőfaragók és kézművesek céhe. Bár a @8Munka&táborokból érkező egyszerű munkások biztosítják a legtöbb fizikai erőt egy emlékmű építéséhez, a szakértő céhek a nyersanyaghalmokat a legnagyobb és legösszetettebb épületekké alakítják, amelyeket építeni fogsz, például piramisokká, @362Szfinxekké, @371masztabákká, @69Nap&templomokká, @368mauzóleumokká és @392obeliszkekké. Minden emlékműhöz sajátos céhes munkások szükségesek. @PAz építőcéheknek úthálózatra és helyi munkaerőforrásra van szükségük. Az ácscéheknek faellátással kell rendelkezniük. A kézművescéheknek @470festékre és @92agyagra (vakolathoz) van szükségük a síremlékek utolsó díszítéseihez. A téglavetők és kőfaragók az emlékmű helyszínén várják a szükséges anyagokat. @PA zaj miatt a polgárok nem szeretnek építőcéhek közelében élni. @L@LAz ókori Egyiptom ezen különleges szakmáiról további információért olvasd el a @386téglavetők, @385kőfaragók, @389ácsok és @472kézművesek bejegyzéseit."
                }
            }
            message_building_brickworks {
                id: 364,

                    size [30, 20]
                title {
                    text: "Téglagyár",
                }
                content {
                    text: "A téglagyárak @92agyagból és @89szalmából téglákat készítenek. A téglákat többféle emlékmű építéséhez használják, és haszonnal @47exportálhatók is. @PHa egy téglagyár rendelkezik munkaerővel és úthálózattal, nyersanyagokra van szüksége a működéshez. A téglagyáraknak szalmára és agyagra is szükségük van. Szalmát a @89gabonafarmok termelnek, agyagot pedig a földből ásnak ki az @92agyaggödrökben. Mindkét nyersanyag importálható egy @47kereskedelmi&partnertől is. @PAmikor egy téglagyár téglát készít, láthatod a téglakészítőket az udvarán dolgozni. Ha elkészül egy rakomány tégla, azt egy @4tároló&udvarba szállítják. @PA téglagyárak nem kívánatos szomszédok. @L@LAz ókori Egyiptom tégláiról további információért kattints @390ide."
                }
            }
            message_building_warship {
                id: 365,

                    size [30, 20]
                title {
                    text: "Hadihajó",
                }
                content {
                    text: "A hadihajók a vízi utakat járőrözik, és döngöléssel vagy nyílzáporral támadják azokat a hajókat, amelyek ártani akarnak a városnak. A hadihajók a part közelében tartózkodó szárazföldi katonákat is támadhatják lövedékekkel. Egy hadihajó egy @356hadihajó&kikötőben állomásozik. A hátsó kabin hiánya és díszes kialakítása alapján megkülönböztethető a szállítóhajóktól. @L@LTámadási prioritások @LMindegy, milyen parancsot adsz egy hadihajónak, kapitánya támadáskor mindig ugyanazt a sorrendet követi. Fontossági sorrendben a kapitány célpontjai: @L@LEllenséges katonákat szállító szállítóhajók @LA kapitány tudja, hogy küldetése nagyrészt kudarcot vall, ha az ellenséges katonák elérik a partot. Ha a város vizein ellenséges katonákat szállító hajók vannak, először ezeket támadja meg, még mielőtt partra tehetnék támadóikat. @L@LPartra szállt ellenségek a part közelében @LHa a kapitány nem tudja megakadályozni az ellenséges katonák partra jutását, a parthoz hajózik, és nyilakkal árasztja el a hatótávolságon belüli partraszállókat. @L@LHadihajók @LAz ellenséges hadihajók a harmadik prioritást jelentik. Ha nincs csapatokat szállító hajó vagy partra szállt ellenség, a kapitány megpróbálja ledöngölni az ellenséges hadihajókat. @L@LÜres ellenséges szállítóhajók @LAz üres ellenséges szállítóhajók a kapitány utolsó célpontjai. Megtámadja őket, ha nincs más ellenség a közelben. @L@LA kapitány gyorsan reagál a változó helyzetekre. Abbahagyja a csatát, ha fontosabb célpont jelenik meg. Például ha egy hadihajót támad, de közben egy ellenséges katonákat szállító hajó érkezik a védett területre, elengedi a hadihajót, és a megrakott szállítóhajót támadja. @L@LHadihajó-parancsok @LA hadihajónak jobb gombbal kattintva adhatsz parancsot. A hadihajók a következő parancsokat hajthatják végre: @L@LÁllj a helyeden @LHa ezt a parancsot kapja, a hadihajó nem mozdul el a kijelölt helyről. Önvédelemből az ellenséges hadihajók felé fordul, hogy csökkentse a döngölés okozta sebzést, és nyilakkal támadja a hatótávolságon belüli ellenségeket. Ha több hadihajó sorakozik fel, és mindegyik az állj a helyeden parancsot kapta, blokádot alkotnak a betolakodók távoltartására. @L@L Közeli ellenségek megtámadása @LEnnek a parancsnak a hatására a hadihajó megtámadja a helye közelében lévő ellenségeket. @L@LMinden ellenség felkutatása és megsemmisítése @LEzzel a paranccsal a hadihajó járőrözni kezd a vízen, hogy ellenségeket keressen és legyőzzön. @L@LJavítás @LHa a hadihajó megsérül egy csatában, erre a gombra kattintva a hajó az ácshoz indul javításra. Amikor a hajóács befejezi a javítást, a hajó visszatér saját kikötőjébe. Súlyos sérülés esetén a kapitány magától a hajóácshoz rendeli javításra. A hajóácsoknak fára van szükségük a javításokhoz. @L@LVisszatérés a kikötőbe @LEzzel a lehetőséggel a hajó visszatér saját kikötőjébe. @L@LEgy hadihajó egyszerű mozgatásához kattints rá, majd az új helyre. Amikor odaér, követi az utoljára kiadott parancsot. Ha egy ellenségre kattintasz, a hadihajó üldözni fogja a célpontot annak legyőzéséig, vagy szárazföldi cél esetén addig, amíg az hatótávolságon belül van. @L@LAz ókori Egyiptom hadviseléséről további információért kattints @184ide."
                }
            }
            message_building_festival_square {
                id: 366,

                    size [30, 20]
                title {
                    text: "Ünnepi tér",
                }
                content {
                    text: "Mielőtt fesztivált tarthatsz (a fesztiválokról további információért lásd a @51vallás részt), városodban kell lennie egy ünnepi térnek. Az ünnepi teret egy útkereszteződésre kell építeni, de nincs szüksége munkaerőre. Minden városban csak egy ünnepi tér lehet, és nagyon @56vonzó szomszédnak számít. @PAmikor nincs fesztivál, a tér többnyire üres, de nem akadályozza a rajta áthaladó utak forgalmát. Amint a fesztivál elkezdődik, az emberek a város minden részéből ide gyűlnek ünnepelni. @PAz ókori egyiptomiak számos különböző esemény megünneplésére rendeztek fesztiválokat. További információért kattints @393ide."
                }
            }
            message_figure_transport_ship {
                id: 367,

                    size [30, 20]
                title {
                    text: "Szállítóhajó",
                }
                subtitle {
                    text: "Szállítóhajó",
                }
                content {
                    text: "A szállítóhajók a hadseregedet szállítják át a folyón vagy tengeren távoli vidékekre. Bármelyik alakulat felszállhat egy szállítóhajóra, de egy hajó egyszerre csak egy alakulatot szállíthat. Egy szállítóhajó egy @357szállítóhajó&kikötőben állomásozik. A hátsó kabinja és kialakítása alapján megkülönböztethető a hadihajótól. @L@LSzállítóhajó-parancsok A szállítóhajóknak különböző parancsokat adhatsz. Egy szállítóhajó mozgatásához kattints rá, majd az új helyre. Jobb gombbal kattintva a következő parancsokat adhatod ki: @L@LÁllj a helyeden @LArra utasítja a szállítóhajót, hogy maradjon a helyén. Ha támadás éri, a kapitány elfordítja a hajót a sebzés csökkentése érdekében. Azonban nem indul el menekülni a támadás elől. Ezt a lehetőséget óvatosan használd, mert a szállítóhajók gyengén védettek. @L@LEllenség elkerülése @LA szállítóhajók, különösen a katonákkal megrakottak, értékesek és sebezhetők. Az Ellenség elkerülése paranccsal a kapitány minden képességét felhasználja a támadások elkerülésére. A kapitány mindig megpróbálja elkerülni az ellenséget, hacsak másképp nem utasítod. @L@LFelszállás/Leszállás @LKatonák hajóra rakásához először kattints a Felszállás gombra, majd a vízen átküldeni kívánt alakulatokra. A katonák felszállnak, a hajón pedig megjelenik az alakulat zászlaja. Ha jobb gombbal kattintasz a szállítóhajóra, megjelennek a fedélzeten lévő alakulat adatai. @PA katonák partra juttatásához kattints a Leszállás gombra, majd arra a helyre, ahol állomásoztatni szeretnéd az alakulatot. @PA Felszállás/Leszállás lehetőség váltakozik attól függően, hogy tartózkodnak-e katonák a hajón. @L@LJavítás @LHa a szállítóhajó megsérül, kattints a javításra, hogy visszaküldd a @82hajóácshoz. Ha a hajótest súlyosan sérült, a kapitány magától a hajóácshoz viszi a hajót. A hajóácsoknak fára van szükségük a javításokhoz. @L@LVisszatérés a kikötőbe @LEzzel a gombbal visszaküldheted a szállítóhajót a saját @357kikötőjébe."
                }
            }
            message_building_mausoleum {
                id: 368,

                    size [30, 20]
                title {
                    text: "Mauzóleum",
                }
                content {
                    text: "A mauzóleumok nagy síremlékek, amelyekbe fáraókat és nemeseket temetnek. @PMauzóleum építéséhez homokkőre és fára van szükség, valamint legalább egy működő @363ácscéhre, @363kőfaragócéhre és @8munkatáborra. @PMauzóleum elhelyezéséhez először nagy mennyiségű homokkőnek kell lennie a város @4tároló&udvaraiban. Ha elegendő kő áll rendelkezésre, válaszd a Mauzóleumot a Vallási épületek: Emlékművek listájából. Helyezd el a mauzóleumot az alaprajz színét figyelve (a teljesen zöld azt jelenti, hogy építhető, a vörös gyémántok pedig azt jelzik, hogy valamilyen tereptárgy akadályozza az építést). Miután kijelölted a helyet, a munkatábor parasztjai megtisztítják a területet és lefektetik az alapokat. @PAmint az alap elkészül, a kőfaragók munkához látnak. Amikor egy tárolóudvar négy tömb homokkövet gyűjt össze, a parasztok szánra rakják a követ, és az építkezéshez húzzák. A kőfaragók addig helyezik el a köveket, amíg az első szint el nem készül. Ezután az ácsok fa rámpákat építenek, hogy a kőfaragók a mauzóleum második szintjén dolgozhassanak. A második szint elkészülte után a mauzóleum befejeződik. @L@LAz ilyen síremlékek történetéről @396ide kattintva olvashatsz."
                }
            }
            message_figure_construction_foreman {
                id: 369,

                    size [30, 20]
                title {
                    text: "Építési felügyelő",
                }
                content {
                    text: "Amint megkezdődik egy emlékmű építése, az építési felügyelő részletes információt nyújt az emlékmű állapotáról. Folyamatosan nyilvántartja, hogy az egyes építőanyagokból mennyire van még szükség a befejezéshez. Ha az építkezés nem halad megfelelően, meg tudja mondani az okát. Az építési felügyelő meglátogatásához kattints jobb gombbal az emlékmű helyszínére."
                }
            }
            message_building_monument_construction {
                id: 370,

                    size [30, 20]
                title {
                    text: "Emlékműépítés",
                }
                content {
                    text: "A legtöbb küldetés sikeres teljesítéséhez legalább egy emlékművet kell építened. Egyes küldetések több emlékmű építését is megkövetelik. A szükséges emlékműveket tetszőleges sorrendben építheted fel. @PA legtöbb emlékműnél a @363építőcéh&dolgozói az építési helyszínen várják a @8munkatábor parasztjait, akik a szükséges anyagokat egy @4tároló&udvarból szállítják. A parasztok olyan messzire gyalogolnak, amennyire szükséges, hogy elérjék az építkezést. A @362Szfinx és a @372Obeliszk építése kissé eltérően zajlik. @G75 @PVárosod munkásai egyszerre több emlékművön is dolgozhatnak, és kísértésbe eshetsz, hogy ezt rendeld el. Vigyázz azonban, mert ez a terv nem biztos, hogy olyan bölcs, mint elsőre tűnik. Hatékonyságcsökkenés léphet fel, amikor a @363kőfaragók és a kőtömb-szállítók nem hangolják össze munkájukat. A parasztok az egyik emlékműhöz szállíthatják az építőanyagokat, miközben a kőfaragók tétlenül várnak egy másik helyszínen, ahol inkább dolgoznának. @PEz a helyzet mélyen bosszantja az @373emlékművek&felügyelőjét, de nehéz összeegyeztetni a kőszállítók merev utasításait a kőfaragók önálló hozzáállásával. A legjobb elkerülni az ilyen konfliktusokat azzal, hogy az emlékműveket egymás után, nem pedig egyszerre építteted. @PNéhány emlékmű hatalmas mérete miatt különösen nehezen helyezhető el a városban. A legnagyobb építményeknél nem láthatod egyszerre a teljes alaprajzot. @PEgy kiválasztott hely felméréséhez nyomd meg az „M” billentyűt. Az emlékmű alaprajza rögzül a kiválasztott helyen, és a városban szokásosan mozgathatod a nézetet. Ha a hely megfelelő, az egérgombbal elhelyezheted az emlékművet. Ha tovább keresnél megfelelő helyet, nyomd meg ismét az „M” billentyűt. Az alaprajz újra követni fogja a kurzorodat a városban. @PEzen kívül néhány emlékművet sziklafalba kell építeni. Ezek az emlékművek az @492Abu&Simbel és a @478Királyi&sírhelyek. @PAz emlékművekről további információért olvasd el az egyes típusok leírását. Ezeket a Súgó menüben találod. @L@LAz emlékművek történetéről további információért kattints ezek egyikére: @391szfinx, @392piramisok, @394masztabák, @493Abu&Simbel, @481Alexandriai&Könyvtár, @482Caesareum, @475Királyok&Völgye és @396egyéb&emlékművek."
                }
            }
            message_building_mastaba {
                id: 371,

                    size [30, 20]
                title {
                    text: "Masztaba",
                }
                content {
                    text: "A masztabák nemesek számára épített díszes síremlékek. Néha te magad is választhatsz egy masztabát végső nyughelyedül. @PMasztaba építéséhez nagy mennyiségű @364téglára és egy @363téglavető&céhre lesz szükséged. Emellett a @8munkatáborok parasztjaira is szükség van. @PA masztaba építésének első lépése a helyszín kiválasztása. Tudni fogod, hogy megfelelő helyet választottál, ha a masztaba alaprajzának zöld „szellemképét” látod. Ha a zöld alaprajzban vörös gyémántok vannak, a táj valamely adottsága akadályozza az építést. Ha az alaprajz teljesen zöld, kattints az egérgombbal, és a masztaba helye rögzül. A helyszín sarkait cölöpök jelölik. @PMiután a hely kijelölésre került, a téglavetők és a parasztok munkához látnak. A parasztok szánrakományokban hordják a téglákat, a téglavetők pedig elhelyezik őket. @PAz elhunytnak sok mindenre van szüksége a Nádasok Mezején, ezért valószínűleg @374temetkezési&ellátmánnyal kell felszerelned a masztabát. Az @373emlékművek&felügyelője megmondja, mely áruk szükségesek. Az építés állapotáról az @369építési&felügyelőnél érdeklődhetsz. Az emlékműépítésről további információért kattints @370ide. @L@LAz ókori Egyiptom masztabáiról további információért kattints @394ide."
                }
            }
            message_building_obelisk {
                id: 372,

                    size [30, 20]
                title {
                    text: "Obeliszk",
                }
                content {
                    text: "Az obeliszkek a nap sugarait jelképezik, oldalain pedig a nagy tetteket és eredményeket örökítik meg. @PAz obeliszkek nagy mennyiségű @95gránitból készülnek, és az obeliszkhez szükséges teljes gránitmennyiségnek a város @4tároló&udvaraiban kell lennie, mielőtt elhelyezheted az emlékművet. @PMozgasd a kurzort a föld felett az obeliszk helyének kiválasztásához. Ha az emlékmű teljesen zöld alaprajzát látod, elhelyezheted az obeliszket. Ha az alaprajzban vörös gyémántok vannak, a táj valamely adottsága megakadályozza az építést. @PMiután kiválasztottad a helyet, a gránitot elhelyezik. Ezután az @363ácscéh ácsai állványzatot építenek az emlékmű köré, és @363kőfaragók érkeznek, hogy bonyolult mintákat véssenek bele. Obeliszk építéséhez nincs szükség parasztok segítségére. @PAz emlékműre jobb gombbal kattintva meglátogathatod az @369építési&felügyelőt. Ő tájékoztat az emlékmű állapotáról. @L@LAz obeliszkek évezredek óta törnek az ég felé. További információért kattints @397ide."
                }
            }
            message_overseer_monuments {
                id: 373,

                    size [30, 20]
                title {
                    text: "Emlékművek felügyelője",
                }
                content {
                    text: "Az emlékművek felügyelője meg tudja mondani, mi akadályozza egy emlékmű építésének megkezdését. Emellett ő irányítja a szükséges @374temetkezési&ellátmányok elküldését azokhoz a sírokhoz, amelyek igénylik ezeket. A tényleges építkezés állapotáról szóló jelentésért kattints jobb gombbal a projektre, és látogasd meg az építési felügyelőt."
                }
            }
            message_burial_provisions {
                id: 374,

                    size [30, 20]
                title {
                    text: "Temetkezési ellátmányok",
                }
                content {
                    text: "Annak biztosítására, hogy az elhunytnak mindene meglegyen a túlvilágon, a legtöbb sírt fel kell töltened temetkezési ellátmányokkal. A temetkezési ellátmányok olyan anyagok, amelyeket az elhunyt életében használt. Szükség lehet a túlvilághoz szükséges különleges tárgyak elkészítéséhez való anyagokra is, például halotti bárkához vagy szarkofághoz. Az emlékművek csak akkor készülnek el teljesen, ha minden szükséges temetkezési ellátmányt biztosítottál. Az @373emlékművek&felügyelője rendelkezik a szükséges tárgyak és mennyiségek listájával. Amikor készen állsz az elküldésükre, utasítsd az emlékművek felügyelőjét, hogy küldje el az árukat a sírhoz. @PNem kell a szükséges anyag teljes mennyiségének a @4tároló&udvarokban lennie ahhoz, hogy árut küldhess az emlékműhöz. Kisebb adagokban is küldhetsz a szükséges áruból, amíg teljesíted a követelményt. @PA városodnak esetleg @47importálnia kell néhány temetkezési ellátmányt. @L@LAz ókori egyiptomiak sokféle tárgyat temettek az elhunyt mellé. Kattints @395ide, hogy megtudd, milyen ellátmányokat vittek magukkal a túlvilágra."
                }
            }
            message_building_stepped_pyramid {
                id: 375,

                    size [30, 20]
                title {
                    text: "Lépcsős piramis",
                }
                content {
                    text: "A lépcsős piramisok, az első Egyiptomban épített piramisok, hatalmas lépcsők a nap felé. Teljes egészében @95faragatlan&kőből készülnek, bár fa szükséges a rámpák építéséhez, amelyekkel a követ a piramis magasabb szintjeire juttatják. A rámpák építéséhez és a kövek elhelyezéséhez szükséged lesz egy @363ácscéhre és egy @363kőfaragócéhre. A hatalmas kőtömböket a helyszínre húzó parasztokra is szükség van. Miután négy tömb faragatlan kő a @4tároló&udvarokban van, és a kőfaragók készen állnak, a parasztok megkezdik nehéz útjukat az emlékműhöz. @PA lépcsős piramisok öt különböző méretben készülhetnek: kicsi, közepes, nagy, piramiskomplexum és nagy piramiskomplexum. További információért keresd fel az @369építési&felügyelőt és az @373emlékművek&felügyelőjét. Az @370emlékmű&építés bejegyzése is hasznos lehet. @L@LA lépcsős piramisról, Imhotep vezír újításáról további információért kattints @392ide."
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
                    text: "Ozirisz, Szobek és Min",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Ozirisz szerepe az egyiptomi vallásban az évezredek során változott. Feleségével és nővérével, Ízisszel, valamint testvérével, Szettel együtt a legősibb istenek egyike volt, és az Enneád tagja (az Enneádról további információért lásd a @399vallás részt). @L@LAz Oziriszt meghatározó mítosz a mezőgazdasághoz, a Nílushoz és a temetkezési szokásokhoz kapcsolja. Ré-Atum Ozirisznek adta az ókori Egyiptom uralmát. Ozirisz feleségül vette nővérét, Íziszt, és uralkodóként sok mindenre megtanította népét, legfőképpen a földművelés művészetére. Miután tanításait átadta az egyiptomiaknak, Ozirisz elhagyta Egyiptomot, hogy a világ többi részét civilizálja, és Íziszt hagyta hátra uralkodni. Ízisz jól vezette az országot távollétében, de amikor Ozirisz visszatért, testvére, Szeth összeesküvést kezdett szőni ellene. Szeth fényűző lakomára hívta Oziriszt, ahol egy gyönyörű koporsót mutatott be. Felajánlotta annak, akinek pontosan megfelel a mérete. Amikor Ozirisz belefeküdt a koporsóba, Szeth lezárta a tetejét, és a Nílusba dobta. Ízisznek sikerült kihalásznia a koporsót a folyóból, de Szeth elfogta őt, és darabokra vágta Oziriszt. Ízisz kétségbeesésében sírt, és könnyeiről úgy hitték, hogy azok okozzák az áradást. Végül Ízisz összegyűjtötte Ozirisz szétszóródott testrészeit, kivéve nemi szervét, amelyet egy oxirhünkhoszi hal fogyasztott el. Ízisz vászonnal kötözte össze Oziriszt, ahogy a múmiákat is bekötözték. Az egyiptomiak érthető módon nem ehettek oxirhünkhoszi halat. Később Ozirisz az alvilág istene lett, és legfőbb bíróként döntött arról, ki léphet be a túlvilágra. @L@LSzobek, a krokodilisten, termékenységi isten volt, akit elsősorban a Fajjúm vidékén tiszteltek, bár egész Egyiptomban ismerték. Neve jelentése: „aki vigyáz rád”. Min, az újjászületés istene, szintén kapcsolatban állt a férfi termékenységgel, és egész Egyiptomban tisztelték."
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
                    text: "Ré, Ma'at és Hórusz",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Ré-t Egyiptom történelmének nagy részében a legfőbb istenként tisztelték. Az Enneád összes istenének ősatyjaként ő volt a végső teremtőisten, és a Naphoz kapcsolták. @L@LMa'at az igazságosság istennője volt, akit az igazsággal és a renddel is kapcsolatba hoztak. A fején viselt strucctollat a szív megmérésénél használták, amely az utolsó próba volt, amelyen az egyénnek át kellett esnie, mielőtt beléphetett a túlvilágra. @L@LHórusz legszorosabban a fáraókhoz kapcsolódott. Ozirisz és Ízisz fia volt, és apja halálát azzal bosszulta meg, hogy felfedte Szeth szerepét Ozirisz meggyilkolásában. Hóruszt sólyom alakjában ábrázolták."
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
                    text: "Ptah, Amon és Thot",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Ptah a kézművesek istene volt, és kapcsolatban állt a Men-neferi (Memphiszi) fáraókkal, akik először egyesítették Egyiptomot (a Men-neferi fáraók egyiptomi hitvilágra gyakorolt hatásáról további információért lásd a @399vallás részt). Különösen tisztelték Deir el-Medinában élő kézművesek, akik a Királyok Völgyének és a Királynék Völgyének sírjait építették. @L@LAmon napisten volt, különösen a reggeli naphoz kapcsolták. A XII. dinasztia idején vált jelentőssé, amikor Waset (Théba) királyai átvették Egyiptom irányítását. @L@LThot a bölcsesség és a tanulás istene volt, és a többi isten írnokának tartották. Legszorosabban Khmunhoz (Hermopoliszhoz) kapcsolódott."
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
                    text: "Szeth, Anubisz és Szekhmet",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Szeth, @376Ozirisz testvére, a pusztítás istene volt. Eredetileg Szeth Alsó-Egyiptom védelmezője volt. Ahogy Felső-Egyiptom egyre fontosabbá vált, Felső-Egyiptom patrónusistene, @377Hórusz is nagyobb szerepet kapott, Szeth pedig negatív megítélés alá került. @L@LAnubisz, a halál istene, a balzsamozás istene volt. Sakálként ábrázolták, és a holtak védelmezője volt. @L@LSzekhmet oroszlánfejű háborúistennő volt. Ptah feleségeként elpusztította azt, amit férje teremtett. Az egyiptomiak azért tisztelték, hogy megbékítsék őt, és ne szabadítsa rájuk haragját."
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
                    text: "Bastet, Ízisz és Hathor",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Bastet, a macskafejű nő vagy oroszlánnő, az otthon, valamint a macskák, a tűz és a terhes asszonyok istennője volt. Békés és haragos módon egyaránt védelmezte az otthont. Emellett Bubasztisz patrónusistennője volt. @L@LÍzisz, @376Ozirisz felesége és @377Hórusz anyja, összeillesztette Ozirisz összetört testét. Emiatt a gyógyítás istennőjeként tisztelték. Nő alakjában ábrázolták, és gyakran fiával együtt jelenik meg. @L@LHathor az öröm, a szerelem és az ünnepségek istennője volt. Tehénként ábrázolták, és Iunet (Dendera), Men-nefer (Memphisz), Qis (Kusze) és Perhathor (Gebelein) patrónusistennője volt."
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
                    text: "Malária",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A malária a mocsarak közelében való élet egyik veszélye volt. Az emberekben a maláriát négyféle, az elsősorban éjszaka aktív anopheles szúnyog által terjesztett parazita egyike okozza. A malária kezdetét láz jelzi, amelyet izomfájdalom, izzadás és fáradtság követ. Az egyik kórokozó súlyos megbetegedést okozhat, amely halálhoz vezethet. @L@L A halálos, vagy legalábbis kellemetlenül viszkető szúnyogcsípések elkerülésére az ókori egyiptomiak szúnyoghálót használtak ágyaik fölött. Hérodotosz görög történetíró azt is feljegyezte, hogy az egyiptomiak tornyokra emelték ágyaikat alváshoz, mert úgy hitték, a szúnyogok nem tudnak olyan magasra repülni."
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
                    text: "Ékszerek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az ékszerészek drágakövekből és féldrágakövekből nyakláncokat, gyöngygallérokat, öveket és más dísztárgyakat készítettek. A gyöngyök felfűzéséhez először kézi fúróval, kovakő heggyel lyukat fúrtak a kövekbe. A lyukak elkészülte után zsinórt fűztek át rajtuk, majd rögzítették. Az ékszerészek a drágakövek berakásában is jártasak voltak. @L@L A sírfalakon látható ábrázolások alapján a törpéket gyakran alkalmazták az ékszerkészítő iparban."
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
                    text: "Vadászat",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A földeken termesztett és a tanyákon nevelt élelmiszerekhez képest a vadászat kevéssé járult hozzá az egyiptomi élelemellátáshoz. Ennek ellenére a felsőbb osztályok kedvelték a vadászatot, és sok fáraó dicsekedett vadászképességeivel. A vadászok fő célpontjai a gazellák, antilopok, kőszáli kecskék, ökrök, juhok és struccok voltak, bár egyesek sportból vadásztak hiénákra, oroszlánokra és leopárdokra is (utóbbiak esetében a bőrükért is). A vadászok íjakat és nyilakat, lándzsákat vagy dárdákat használtak zsákmányuk elejtésére. @L@L Az egyiptomiak ugyanilyen kedvelték a vízi állatok vadászatát is, beleértve a madarakat és a vízilovakat. Férficsoportok együtt vadásztak vízilóra egy kötélhez erősített különleges dárdával. Többen próbálták eltalálni az állatot a dárdákkal. Miután elegendő sebet ejtettek rajta, a kötél segítségével a partra húzták a vízilovat. @L@L A madarakat hajítóbottal ölték meg, amely kissé hasonlított az ausztrál bumerángokra. A vadász segítői, legyenek azok családtagok vagy szolgák, összegyűjtötték a leterített madarakat. A madarakat mezőre kihelyezett hálókkal is csapdába ejtették. A hálót madáreleséggel szórták meg. Amikor a madarak odagyűltek, a háló sarkait összefogták, és a madarak csapdába estek."
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
                    text: "Papok",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az ókori egyiptomi lakosság jelentős része pap volt. Szerepük messze túlmutatott a vallási feladatokon. Mivel az ókori Egyiptom teokrácia volt, a papok gyakran közösségeik közigazgatási szerepeit is betöltötték, és néha igazságot is szolgáltattak. @L@L A pap ismertetőjele a tisztaság volt. A papok megtisztulási szertartásokon estek át, mielőtt beléphettek a templomba, és leborotválták hajukat, hogy ne rejthessenek el tetveket vagy más tisztátalanságot. Attól függően, melyik istent szolgálták, bizonyos ételek fogyasztása tiltott volt számukra. A papok különleges ruházatot viseltek, és fehér szandált is kellett hordaniuk. A legmagasabb rangú papok néha leopárdbőrrel díszítették magukat. @L@L A papság legfontosabb vallási feladata a helyi isten gondozása és táplálása volt. Minden templomban megtalálható volt a védőisten szobra. A templom minden papjának megvolt a saját feladata annak biztosítására, hogy az isten elégedett legyen. Egyes papok az isten megfelelő táplálásáért feleltek. A helyiek által felajánlott vagy a templom birtokán termelt élelmiszerekből a papok ételt készítettek az isten számára. Az isten elfogyasztotta az étel 'lényegét', a maradékot pedig a papok ették meg. A papok felöltöztették és megfürdették az istent, valamint szórakozást is biztosítottak számára. Időnként az istent kirándulásra vitték, és körbehordozták a faluban (lásd még: @393festivals). @L@L A papság különböző osztályokra tagolódott. A legmagasabb rangú pap a főpap volt, akit Első Prófétának is neveztek, és a fáraó nevezte ki. A főpap volt a templom legfőbb hatósága, és gyakran a fáraó tanácsadójaként is szolgált. Alatta álltak a helyettes főpapok, vagyis a Második Próféták, akik a templom vagy birtoka bizonyos területeit felügyelték, például a műhelyeket vagy a földeket. Alattuk voltak az egyes feladatokért felelős papok, például akik az istent fürdették vagy szórakoztatták. A legtöbb pap váltásokban dolgozott, és minden három hónapból egy hónapot szolgált."
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
                    text: "Kőfaragók",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A kőfaragók felügyelték a @193kőbányákat, valamint a @392piramisok és más emlékművek építését. Bár ismerték a kő minden tulajdonságát és a leghatékonyabb kitermelési módokat, a nehéz fizikai munkát többnyire nem ők végezték. A legalacsonyabb osztályba tartozó parasztok, és néha rabszolgák végezték a legkeményebb munkát. A kőfaragók az egész folyamatot irányították. A nagy építkezések mellett a kőfaragók szakértelmére kisebb munkákhoz is szükség volt, például egy ház alapjának lerakásához."
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
                    text: "Kőművesek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A téglafalazás technikája az évezredek során alig változott. Az alapanyagok lényegében ugyanazok: @390tégla és kötőanyagként használt habarcs. Az ókori Egyiptomban a habarcs agyag, homok, szalma és pelyva keverékéből készült. A kőművesek fa simítóval terítették el a habarcsot, majd a helyére illesztették a téglát. Függőónnal ellenőrizték, hogy az általuk épített falak egyenesek legyenek."
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
                    text: "Írnokok",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az írnokok, vagyis a sesek, áthatották az egyiptomi társadalom és kormányzat minden részét, és szinte minden állami tevékenységhez kapcsolódtak. Az ókori egyiptomiak szinte mindenről nyilvántartást vezettek, és ezt a feladatot csak az írnokok végezhették. Az írnokok feljegyezték, hogy ki mennyi adóval tartozik az államnak, nyomon követték az exportot és importot, sőt a katonákkal együtt a csatába is elmentek, hogy rögzítsék az eseményeket. A magánszemélyek számára jogi iratokat, például végrendeleteket készítettek, valamint leveleket olvastak és írtak. @L@L Az írnokok munkaeszközei közé tartozott a papirusz, egy két tintatartós paletta (általában fekete és vörös tintával), egy víztartó edény és nádecsetek. Az írnok az ecsetet vízbe mártotta, majd a tintakorongon dörzsölte át. Ezután a papiruszra írt. @L@L Nagyon kevés írnok ismerte a hieroglifák írását. A hieroglifákat emlékműveken és templomokban használták. A mindennapi használatra a hieroglifák egyszerűbb változata, a hieratikus írás szolgált. @L@L Az írott nyelv körülbelül 700 jelből állt, és hangokat jelölő szimbólumokat eszméket jelölő jelekkel kombinált. Az írás nem jelölte a magánhangzókat, ezért a történészek csak találgathatják, hogyan hangzott az ókori egyiptomi nyelv."
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
                    text: "Bevándorlás",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Egyiptom viszonylag stabil gazdasággal és általában egyenletes élelmiszer-termeléssel rendelkezett az áradásnak köszönhetően. Egyiptom szomszédai tudtak erről, és a környező területek sok lakója bevándorolt Egyiptomba. @L@L Egyiptom néhány bevándorlója kereskedelmi céllal érkezett. A nagy kikötővárosokban, például Memphiszben talált régészeti bizonyítékok nem egyiptomi települések létezését mutatják. Ezeket a külföldi kereskedőket a Középbirodalom és az Újbirodalom sírjain is ábrázolták. Egyes szomszédos népek, például a líbiaiak, nagy számban telepedtek le az ókori Egyiptomban. A tizenkettedik dinasztia idejére a líbiaiak a nyugati Delta jelentős részét elfoglalták, majd hamarosan a keleti Deltába is elterjedtek. @L@L Néhányan kevésbé nemes szándékkal érkeztek Egyiptomba. @181Az ország megszállói gyakran akkor is ott maradtak, miután elvesztették hatalmukat. Úgy tűnik, sok itt maradt idegen ugyanolyan jogokat élvezett, mint az egyiptomiak, és néhányan magas tisztségeket is betöltöttek az egyiptomi kormányzatban."
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
                    text: "Ácsok",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az ácsok számos szükséges tárgyat készítettek az egyiptomiak számára. A helyi @192fa ritka volt, ezért az ácsok nagyon takarékosan bántak a rendelkezésükre álló fával. Importált fát is használtak, de az drága volt, ezért csak a leggazdagabb polgárok engedhették meg maguknak. @L@L Az ácsok fejszékkel, fűrészekkel és vésőbárdokkal dolgozták fel a rönköket használható faanyaggá. A fejszékkel eltávolították az ágakat a rönkökről, és szétválasztották a fát, ha tetőgerendákat készítettek. A fűrészekkel deszkákra vágták a rönköket, a vésőbárdokkal pedig elsimították a deszkák egyenetlenségeit. @L@L A késztermékek között ládák, ágyak, ajtók és ajtókeretek, székek, valamint talán a legfontosabbak: koporsók is szerepeltek. Szögek helyett facsapokat használtak az elkészült darabok összeillesztésére. Néhány elkészült tárgy lenyűgöző volt, felületüket finom berakások és faragások díszítették. @L@L Az ácsokra nagyobb épületek építésénél is szükség volt. A gazdagabb házak mennyezetét gyakran díszes faoszlopok tartották. @L@L Az alapvető ácsmesterség alig változott az ókori egyiptomi történelem során, és ugyanazokat az alapvető eszközöket részesítették előnyben. A legnagyobb újítás a fúró kifejlesztése volt. Az Újbirodalom idején íjfúrót használtak a facsapok számára szükséges lyukak elkészítésére."
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
                    text: "Téglák",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A tégla ideális építőanyag volt az ókori egyiptomiak számára. Mivel rosszul vezette a hőt, a téglaházak belseje viszonylag hűvös maradt a forró nyár folyamán. A téglákat agyag és szalma keverékéből készítették. Az agyagot megnedvesítették, összekeverték szalmával, majd vízbe merítették. A víz alatt a szalma bomlásnak indult, és eközben olyan nyálkás anyagot bocsátott ki, amely összetartotta a téglát. A téglát ezután napon szárították. Amikor a téglák elkészültek, a @386kőművesek megkezdhették munkájukat."
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
                    text: "Szfinx",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A Szfinx, amely az ókori Egyiptomban Ámunhoz kapcsolódott, oroszlántesttel és királyi fejjel rendelkezik. Egyiptomban sok Szfinx létezett, de messze a leghíresebb a gízai Nagy Szfinx (Rosztja). @L@L A körülbelül Kr. e. 2500-ban épült Nagy Szfinx látszólag Hafré piramisát őrzi, és egy régi kőfejtő fölött helyezkedik el. Arcát vélhetően magáról Hafréról mintázták. A Szfinx körülbelül 60 méter hosszú és 20 méter magas. Puha homokkőből faragták ki. @L@L A Szfinx létezésének nagy részében homokba temetve állt. A legenda szerint IV. Thotmesz, még mielőtt fáraó lett volna, a Szfinx környékén vadászott, majd elaludt ott, ahol az áll. Álmában a Szfinx azt mondta neki, hogy ha kiássa, fáraóvá válik. Thotmesz teljesítette a Szfinx kérését, és Kr. e. 1425-ben fáraó lett. A történetet sztélékre vésette, és azokat a Szfinx mancsai közé helyezte. @L@L A Nagy Szfinxet később ismét betemette a homok, és végül az 1930-as években tárták fel véglegesen. A Szfinx megőrzésére tett kísérletek vegyes eredménnyel jártak."
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
                    text: "Piramisok",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az emberek évszázadok óta találgatják, hogyan épülhettek a piramisok. Felfoghatatlannak tűnik, hogy az ókori egyiptomiak targoncák, daruk, kotrógépek és számos más modern eszköz nélkül ilyen nagyszerű építményeket tudtak létrehozni. @L@L Minden piramis építése gondosan kidolgozott tervvel kezdődött. A vezír, aki rangban csak a fáraó mögött állt, valószínűleg az egész folyamatot felügyelte, miközben a királyi építész (ókori egyiptomi nevén medzseh neszu) elkészítette a terveket. A királyi építész felelt az anyagok kiválasztásáért és azért, hogy miként juttassák el azokat az építkezés helyszínére. @L@L Miután a helyszínt gondosan kiválasztották, a csillagászok meghatározták a piramis észak–déli tengelyét. Ezután a földmérők egy különleges zsinór segítségével kijelölték a piramis minden oldalát, amely olyan vastag volt, hogy nem nyúlhatott meg és nem torzíthatta el a méreteket. Ezután a talajt kiegyenlítették, talán úgy, hogy árkokat töltöttek fel vízzel egy egységes sík meghatározásához. @L@L Miután ezek a feladatok elkészültek, megkezdődhetett az építkezés. A munkálatok kezdetén szertartást tartottak, amely során a fáraó karókkal kijelölte a piramis sarkait, zsinórt feszített közéjük, majd egy ünnepélyes vályogtéglát helyezett el az emlékmű első köveként. @L@L Ekkor a @385kőfaragók és a @155munkások vették át a feladatot. A kőfaragók kialakították a föld alatti helyiségeket, köztük a sírkamrát. Miután ezek elkészültek, megkezdődött a nehéz munka: a kőtömbök odaszállítása, amelyek közül néhány akár 2,5 tonnát is nyomott. A köveket szánokon vontatták, és valószínűleg rámpákat használtak a piramis magasabb részeinek eléréséhez. A piramis belsejét alkotó durván megmunkált kövek mellett finomabb kőburkolat fedte az építményt. @L@L Néhány piramis önmagában állt, de gyakrabban nagyobb piramiskomplexumok részei voltak. A piramiskomplexumhoz tartozott egy völgytemplom, amely a vízparton vagy a művelt terület szélén helyezkedett el. A völgytemplomtól hosszú felvonulási út vezetett a halotti templomhoz, amely a piramistól keletre állt. @L@L A piramisok formája fejlődött, ahogy az építési technológia tökéletesedett. Az első piramis, Dzsószer lépcsős piramisa, nem rendelkezik sima oldalakkal. A Kr. e. 2620 körül épült lépcsős piramis egymásra helyezett négyzetek sorozata. Az első valódi piramis Sznofrué volt, amely Kr. e. 2550 körül épült. Külső burkolat simította el a piramis 'lépcsőit', és ezt a módszert hamarosan más piramisoknál is alkalmazták. A legnagyobb piramis Hufué, amely 230 × 230 méteres alapterületű és 146 méter magas. Egyedülálló piramis Sznofru tört piramisa. Ennek oldalainak dőlésszöge a csúcs felé vezető út körülbelül kétharmadánál megváltozik. A feltételezések szerint az építészek rájöttek, hogy a piramis túl nehéz lenne és összeomolhatna, ha az eredeti szögben folytatnák az építést. Mivel Sznofru első piramisa összeomlott, valószínűleg úgy gondolta, jobb az óvatosság."
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
                    text: "Ünnepek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az ókori egyiptomi ünnepek vidám események voltak, amelyeken bőségesen volt étel, és szabadon folyt a sör. Sokféle okból ünnepeltek: egy isten tiszteletére, az aratás megünneplésére vagy a fáraó hosszú életének elismerésére. Az egyiptomi év utolsó öt napját ünnepléssel töltötték, és az év során számos más ünnepet is tartottak. @L@L Az istenségek tiszteletére rendezett ünnepeken minden ember közvetlen kapcsolatba kerülhetett isteneivel. A vallási ünnepek középpontjában az isten körmenete állt. Az ünnep során a templomban, a nyilvánosság elől elzárva őrzött istenszobrot legszebb ruháiba öltöztették, majd a papok által hordozott szertartási bárkán körbehordozták a városban. A papok időnként megpihentek, eközben szertartásokat végeztek. Az Újbirodalom idején a polgárok kérdéseket tehettek fel az istennek, miközben a papok pihentek. A papok meghajoltak, ha az isten pozitív választ adott, és hátraléptek, ha a válasz negatív volt. Az ünnep végén az isten visszatért templombeli otthonába. @L@L Néha az istenek messzire utaztak, és hajóval szállították őket. Például az opét ünnepen Ámun Karnakból luxori déli kápolnájába utazott. Az út megtételéhez a Níluson hajózott. Az opét az egyik legvidámabb ünnep volt, és 11–27 napig is tarthatott. @L@L Ha egy fáraó elég egészséges volt ahhoz, hogy 30 évig uralkodjon, megrendezték a heb-szed ünnepet. A fáraó uralkodásának 30. évében, majd ezt követően háromévente megtartott ünnepen a fáraó rituális futást végzett, hogy bizonyítsa: továbbra is alkalmas az uralkodásra. Néhány fáraó nem várta meg a 30 évet a heb-szed megtartásával, hanem már uralkodása elején megrendezte. @L@L Kétségtelen, hogy az egyiptomiak minden társadalmi rétegből örömmel várták az ünnepeket, mint a bőséges evés és ivás időszakát. Az ünnepek egyben pihenést is nyújtottak a mindennapi munka terhei alól."
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
                    text: "Masztaba",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A korai óbirodalmi fáraókat és nemeseket masztabák alá temették. A masztabák fedték a sírkamrához vezető aknát. Kezdetben egyszerű, alacsony építmények voltak, amelyekre feliratokat véstek, később azonban nagyobb építményekké fejlődtek, kápolnákkal kiegészülve. A masztabákat a piramisok elődeinek tekintik, és Dzsószer lépcsős piramisa is valószínűleg masztabaként kezdődhetett."
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
                    text: "Sírmellékletek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A sírokat mindennel felszerelték, amire az elhunytnak a túlvilágon szüksége lehetett. Ezeket sírmellékleteknek nevezték, és közéjük tartoztak az elhunyt mesterségéhez szükséges eszközök, ételek, tisztálkodási tárgyak, ékszerek, hangszerek, sminkek – gyakorlatilag bármi, amit életében használt. A sírokat usébtikkel, vagyis 'válaszadókkal' is ellátták. Ezeket a szobrocskákat azért helyezték a sírba, hogy ha az elhunytnak munkát kellett volna végeznie a túlvilágon, az usébti végezze el helyette."
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
                    text: "Más emlékművek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az @397obeliszken, @394masztabákon, @392piramisokon és @391szfinxeken kívül az ókori Egyiptomban számos más emlékmű is létezett. Ezek közé tartoztak a mauzóleumok és a Naptemplomok is. @L@L A Napot az élet adójának tekintették az ókori Egyiptomban, és sok Naptemplomot építettek szerte Egyiptomban, különösen az ötödik dinasztia idején. A legismertebb Naptemplomok Abu Ghurábban találhatók. Két Naptemplom állt itt, és ezekben állatáldozatokat mutattak be. @L@L A sírok fölé gyakran mauzóleumokat és kápolnákat emeltek, amelyek helyet biztosítottak, ahol az elhunyt családja áldozatokat mutathatott be. Ezek az áldozatok biztosították, hogy az elhunyt továbbra is élvezhesse a túlvilági létet. Bárki, akinek volt rá lehetősége, ilyen kápolnákat építtetett családtagjai számára, és Egyiptom táját számos magánmauzóleum tarkította."
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
                    text: "Obeliszk",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az obeliszkek a Naphoz kapcsolódtak, és vagy a napsugarakat, vagy azt az ősdombot jelképezték, amelyen a Nap először ragyogott fel. Gránitból készültek, hieroglifákkal vésték őket, és általában párokban álltak a templomok előtt. @L@L Az obeliszk formáját a kőbányákban faragták ki, és egy asszuáni befejezetlen példány sokat elárul arról, hogyan termeltek ki egy ilyen hatalmas kőtömböt. A munkások doleritből készült ütőkövekkel lassan alakították ki a kívánt formát. Az asszuáni obeliszket azért hagyták félbe, mert a kő közepén repedés keletkezett. @L@L Miután az obeliszket kifaragták a sziklából, senki sem tudja pontosan, hogyan állították fel őket. A feltételezett ókori módszerekkel végzett modern kísérletek nem jártak sikerrel."
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
                    text: "Len és szövés",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A @189lenből készült vászon volt az ókori Egyiptom legelterjedtebb textíliája. Bár néhány szövetet gyapjúból vagy kenderből készítettek, ezeket sokkal gyengébb minőségűnek tartották a vászonnál. @L@L A szövet készítéséhez először a lenrostokat fonallá kellett sodorni. A fonók lenkupacok előtt ülve összecsavarták a rostokat, majd gombolyagokba tekerték őket. Ezután a fonalat orsókra erősítették, és megkezdődhetett a szövés. @L@L Az egyiptomiak vízszintes szövőszéket használtak, amelyet a földre helyeztek. A szövők a szövőszéket két párhuzamos fonalsorral (láncfonallal) fűzték fel. Két munkás ült a szövőszék két oldalán, és az átfűzött vetélőt oda-vissza küldték, hogy elkészüljön a szövet. @L@L Az Újbirodalom idején a függőleges szövőszék váltotta fel a vízszinteset. A függőleges szövőszék lehetővé tette, hogy a szövők kényelmesebben, ülőkén ülve dolgozzanak. @L@L A legtöbb szövő nő volt, akik gyakran a fáraó háremének tagjai közé tartoztak."
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
                    text: "Vallás",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az egyiptomi vallás nagy létszámú fő- és kisebb istenekből álló panteonnal rendelkezett. A legtöbb város, sőt az egyének is egy bizonyos istent tekintettek védőistenüknek, és ez befolyásolta, mely istenek váltak a legfontosabbá. @L@L Az egyik legkorábbi hitrendszer az Enneád, vagyis kilenc isten csoportja volt. Az On (Héliopolisz) városában kialakult rendszer első istene Atum volt, aki Rével egyesülve Ré-Atummá vált. Ré-Atum, bár férfi volt, egyedül adott életet az ikreknek, Suh-nak és Tefnutnak. Suh a levegő istene volt, Tefnut pedig a világ rendjének istennője. Suhnak és Tefnutnak négy gyermeke született: Ízisz, Ozirisz, Nephtüsz és Széth. A kilenc isten sorát Hórusz egészíti ki, Ízisz és Ozirisz fia. Ré később különvált Atumtól, és az Enneád legfőbb istenévé vált. Ez az istenrendszer uralta a dinasztiák előtti Egyiptomot, és Ré továbbra is fontos isten maradt az ókori egyiptomiak számára. @L@L Amikor Hór-Aha egyesítette Felső- és Alsó-Egyiptomot, a teremtő isten, Ptah iránti személyes hite megváltoztatta a vallási rendszert. Hór-Aha szerint az Enneád istenei mind Ptah megnyilvánulásai voltak. Ennek ellenére Ré maradt a meghatározó isten. @L@L Egy másik elmélet a felső-egyiptomi Khmun (Hermopolisz) városából származott. A hermopolisziak az Ogdoádban, vagyis nyolc isten csoportjában hittek. Az Ogdoádban férfi és női istenpárok a világ különböző részeit képviselték. Nun és Naunet a vizet, Huh és Hauhet a végtelenséget, Kuk és Kauket a sötétséget, Ámon és Amaunet pedig a levegőt jelképezték. @L@L Az Újbirodalomban Ámon váltotta fel Rét mint legfőbb istent. Ámon uralma egészen Ehnaton fáraó uralkodásáig tartott. Ehnaton megpróbálta bevezetni az egyistenhitet Egyiptomban, és azt vallotta, hogy Aton, akit a Napkorong testesített meg, az egyetlen isten. Uralkodása alatt, amelyet amarnai korszaknak neveznek, Ehnaton bezáratta a többi isten templomait. Halála után azonban gyorsan visszaállították a többistenhitet, és újra megnyitották a többi isten templomait."
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
                    text: "Egy falu születése",

                }
                content {
                    text: "@PÜdvözlünk az ókori Egyiptomban, a fáraók földjén! Itt részt vehetsz a világ egyik legnagyobb civilizációjának történetében, egy több mint tizenöt évszázadot és két tucat nemzedéket átívelő epikus történetben. Egyetlen családot kell vezetned, nemzedékről nemzedékre, az egyiptomi történelem előtti kor legkorábbi kezdeteitől a civilizáció hajnalán át... egy egyedülálló és hatalmas birodalom létrejöttéig... és azon túl.     @PTörténetünk több mint ötezer évvel ezelőtt kezdődik, a Nílus folyó partján, egy Naqada nevű vidéken. Itt klánok kis szövetsége küzd a fennmaradásért a zord környezetben. A családod élén állva neked kell vezetned ezt a kis települést."
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
                    text: "A civilizáció hajnala",

                }
                content {
                    text: "@PÉvek múltán, egy nemzedék elteltével családod Felső-Egyiptomban, Thinisz vidékén telepedett le újra. Itt helyi uralkodók kis csoportja próbálja kiterjeszteni hatalmát Alsó-Egyiptom és a Nílus menti összes föld felett, hogy ezt a birodalmat saját háza alatt, egyetlen legfőbb vezetővel egyesítse.   @PThinisz virágzó várossá fejlesztése, amelyhez hasonlót még nem látott a világ, bizonyítja majd a thiniszi szövetség rátermettségét, és segít nekik megszerezni az uralmat Alsó-Egyiptom és a hatalomért versengő többi csoport felett. Idővel ez azt is jelenti, hogy szórakozást kell biztosítani a lakosságnak, és nagyszerű templomokat kell építeni a vidék védőistene tiszteletére. @PEgy ilyen hatalmas város felépítéséhez jelentős mennyiségű pénzre lesz szükség. Thiniszben gazdag aranyérclelőhelyeket találsz, és ezek kitermelése legyen az elsődleges feladatod."
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
                    text: "A thiniszi nemesek továbbra is küzdenek azért, hogy a Nílus földjeit egyetlen legfőbb uralkodó alatt egyesítsék. Ügyük támogatására azt remélik, hogy virágzó közösséget hozol létre Butóban, Alsó-Egyiptom nedves deltavidékén, ezzel kiterjesztve befolyásukat a szent folyó teljes hosszában. Egy falunál nagyobb lakosság eltartásához meg kell tanulnod a mezőgazdaság használatát. @PAz egyiptomi földművesek elkezdték kihasználni a Nílus évenkénti áradása által lerakott gazdag, termékeny talajt a növénytermesztéshez. A Nílus azonban veszélyes is lehet. Sok veszély leselkedik partjai mentén és vizeiben, például halálos krokodilok, vízilovak és maláriát terjesztő szúnyogok."
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
                    text: "Az első fáraó",

                }
                content {
                    text: "Miközben a Nílus mentén élő emberek továbbra is küzdenek a túlélésért ebben a zord környezetben, egy Narmer nevű helyi király hatalomra emelkedett. Bár Narmer e földek nagy része felett uralkodik, a két királyság teljes egyesítése még nem történt meg. Trónra lépésének emlékére Narmer azt kívánja, hogy családod alapítson és vezessen egy új várost Hierakonpoliszban. A városban Egyiptom számos istenének templomai és sok szórakozóhely lesz."
                }
            }
            message_mission_memphis {
                id: 404,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Memphisz",

                }
                subtitle {
                    text: "Egy főváros alapítása",

                }
                content {
                    text: "Hosszú küzdelem után Hór-Aha király egyesítette Felső- és Alsó-Egyiptom két királyságát, és egész Egyiptom fáraójának kiáltotta ki magát! Teljhatalmának és Egyiptom első dinasztiája megalapításának jeleként Hór-Aha elrendelte egy lenyűgöző főváros felépítését Memphiszben, ahonnan kormányozhatja ezt a fiatal országot. Családod sok nemzedéken át tartó hűséges szolgálata miatt a fáraó téged választott e nagyszerű város megtervezésére. Mivel a főváros királyságunk valódi jelképe, lakóinak olyan életminőséget kell élvezniük, amely korábban ismeretlen volt ezen a földön. Ennek érdekében idővel kereskedned kell a birodalom más városaival, és magasabb szintű oktatást kell biztosítanod legalább néhány polgár számára. Emellett szent masztabasírt kell építened a város nemeseinek."
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
                    text: "Expedíció a Sínai-félszigetre"
                }
                content {
                    text: "Új fáraó, Den foglalta el Egyiptom trónját. A fáraó mélyen aggódik, mivel ellenségek kezdték fenyegetni határainkat, és országunk nem rendelkezik elegendő értékes rézzel, amely a hadsereg felszereléséhez szükséges fegyverek elkészítéséhez kell. Den fáraó bányászati expedíciót rendelt el a kegyetlen Sínai-félszigetre, határainkon túlra, mélyen a beduinok területére. A Timna néven ismert vidék gazdag arany- és rézércben, valamint értékes türkiz drágakövekben, de egyébként kopár. A körülmények kemények lesznek, és számos kényelmi cikket, talán még további élelmet és finom vásznat is Egyiptomból kell importálnod. A fáraó gyakori szállítmányokat követel majd a Sínai-félszigetről, és pénzt, rezet, drágaköveket és fegyvereket kér tőled. Ezen áruk feleslegét felhasználhatod az expedíció támogatására. Mindig légy óvatos, mert a Sínai-sivatag beduinjai félelmetes ellenfelek, és nem engedik szívesen, hogy idegenek elfoglalják földjüket, még kevésbé, hogy kifosszák ásványkincseiket. @P A város lakóira nehezedő nehéz életkörülmények enyhítésére építs Pavilont egy forgalmas útkereszteződéshez. A polgárok a Pavilon zsonglőr- és zeneszínpadain pihenhetnek, és ha Tánciskolát is építesz, ez az újfajta előadás nagyszerű szórakozást biztosít."
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
                    text: "A fáraó haditengerészete",
                }
                content {
                    text: "Egyiptom hadserege most páratlan az ismert világban, de az új fáraó, a második dinasztiabeli Kaszekhemui, most egy erős, Apollinopoliszban állomásozó haditengerészetet is követel. Semmi más, csak egy hadihajókból álló flotta biztosíthatja számunkra a tengerek feletti uralmat, de a fa ritka, mivel éghajlatunk csak kevés ritkás erdőterületet tart fenn. Cédrust nagy költséggel importálhatunk Bübloszból, a tőlünk északkeletre fekvő libanoni földről. Szerencsére őshonos papiruszunk exportja lehetőséget biztosít e kiadás ellensúlyozására."
                }
            }
            message_mission_abydos {
                id: 407,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Abydosz",
                }
                subtitle {
                    text: "A tenger kihívása",

                }
                content {
                    text: "Abydosz, őseink nyughelye, az évek során a szent sírok kiterjedt nekropoliszává fejlődött. Most a legtöbb nemes férfi és nő ezt kívánja örök nyughelyéül választani. Tiszteletükre Kaszekhemui, a második dinasztia új fáraója elrendelte három szent masztabasír építését (az egyik nagyobb legyen a másik kettőnél) a helyi nemesség számára. @P A fáraó egy erős haditengerészet létrehozását is elrendelte, amelynek bázisa Apollinopolisz lesz. Abydosznak is támogatnia kell egy kisebb harci hajóflottát, ha partjaink teljes biztonságát fenn akarjuk tartani. Ez nem lesz könnyű, mivel a fa ritka, és éghajlatunk csak kevés erdőterületet tesz lehetővé. Cédrust nagy költséggel importálhatunk Bübloszból, a tőlünk északkeletre fekvő libanoni földről. Szerencsére őshonos papiruszunk exportja lehetőséget biztosít e kiadás ellensúlyozására."
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
                    text: "Az út Afrikába",

                }
                content {
                    text: "@PÚj fáraót, Nebkát kiáltották ki, ezzel kezdetét vette az egyiptomi uralkodók harmadik dinasztiája. Nebka nagyobb rendet és szervezettséget hozott Egyiptomba, elrendelve, hogy birodalmunkat körzetekre, vagyis nomoszokra osszák, amelyek élén helyi uralkodók, úgynevezett 'nomarchák' állnak. Bár ez a rendszer merevnek tűnhet, vezetése alatt Egyiptom fejlődött és gyarapodott, valamint számos nagyszerű eredményt ért el a művészet és építészet terén. @L@L @P A mélyen Afrika belsejéből, oázisról oázisra haladó kereskedelmi karavánok számos ritka és egzotikus luxuscikkel kezdték ellátni Egyiptomot, amelyeket népünk nagyra becsül. Sajnos ezeket a karavánokat rendszeresen megtámadják líbiai harcosok, sőt a keleti sivatag beduinjai is. A kereskedelmi útvonalak biztosítása érdekében Nebka fáraó, a Nád és Méh ura, azt kívánja, hogy katonai állomást hozz létre a Selima-oázisban, a karavánkereskedelem központjában, messze birodalmunk határain túl. @L@L @P Itt találsz néhány faanyagnak alkalmas fát, amelyek eladásával pénzt gyűjthetsz az őrhely létrehozásának finanszírozására. Fegyverek készítéséhez rezet szerezhetsz a Sínai-félszigeten, Timnában újonnan megnyitott bányáinkból. @L@L @P A Selima-oázisból ébenfát importálhatsz az afrikai Kermából. Miután sikeresen létrehoztad ezt az őrhelyet, megbízható ébenfa-forrást biztosít majd birodalmunk minden városa számára."
                }
            }
            message_mission_elephantine {
                id: 409,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Elephantiné",

                }
                subtitle {
                    text: "A núbiai határ",

                }
                content {
                    text: "@PÚj fáraót, Nebkát kiáltották ki, ezzel kezdetét vette az egyiptomi uralkodók harmadik dinasztiája. Nebka nagyobb rendet és szervezettséget hozott Egyiptomba, elrendelve, hogy birodalmunkat körzetekre, vagyis nomoszokra osszák, amelyek élén helyi uralkodók, úgynevezett 'nomarchák' állnak. Bár ez a rendszer merevnek tűnhet, vezetése alatt Egyiptom fejlődött és gyarapodott, valamint számos nagyszerű eredményt ért el a művészet és építészet terén. @P A fáraó azt kívánja, hogy birodalmunk határait délebbre, Núbia felé terjesszük ki. Elrendeli egy város alapítását a Nílus első kataraktájánál, Elephantiné szigetén, hogy kihasználhassuk az ott található bőséges drágakő-, gránit- és homokkőkészleteket. @P Abydosz növekvő nekropolisza ezekből az anyagokból igényel utánpótlást, hogy egyre díszesebb sírokat készíthessenek a nemesség számára. Memphisz fővárosának is szüksége lehet téglára a sírok építéséhez, és Nebka fáraó jóváhagyhatja ezek és más építőanyagok igénylését. @P Nebka fáraó azt is elrendelte, hogy egyik társad katonai állomást hozzon létre a Selima-oázisban az Afrika belsejébe vezető karavánutak biztosítására. Miután létrejött, a Selima-őrséghelyről importált ébenfához juthatsz, amely nagyra becsült luxuscikk."
                }
            }
            message_mission_saqqara {
                id: 410,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Szakkara",

                }
                subtitle {
                    text: "Az első piramis",

                }
                content {
                    text: "Dzsószer fáraó trónra lépése új korszakot hozott Egyiptom számára a bölcsesség, tanulás és művészi eredmények terén. Szakkarában királyi temetőt kell létrehozni, amely örök nyughelyül szolgál olyan nemeseknek, mint Hezüré és Khabauszokar, a fáraó megbízható udvaroncai. @P De ez a hely egy olyan emlékművet is magában fog foglalni, amelyhez hasonlót a világ még soha nem látott. Én, a fáraó királyi vezírje, Imhotep, egy újfajta szent sírt terveztem a fáraó számára. A korábbi fáraók alacsony vályogtégla-masztabáival ellentétben ez a sír az ég felé fog emelkedni, mintha több, egymásra helyezett masztabából állna. Ráadásul ez a 'lépcsős piramis' teljes egészében kőből épül, hogy ellenálljon az idők múlásának. Mélyen belül egy tömör gránitból készült szarkofág őrzi majd a fáraó testét örök nyughelyén. @P Az abydoszi nekropolisz papjai tökéletesítették a len felhasználásának művészetét a halottak bebalzsamozásához, így minden egyiptomi számára megnyitották az örök élet kapuját. @P A Selima-oázisban lévő kereskedelmi állomásunk továbbra is virágzik, és onnan ébenfát importálhatsz Afrikából. @P A fáraó bőséges pénzösszeget biztosított e projekt megkezdéséhez. Ne okozz neki csalódást."
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
                    text: "A kelet beduinjai",

                }
                content {
                    text: "Akárcsak elődje, Den, Huni fáraó is expedíciót rendelt el a zord Sínai-félszigetre türkiz drágakövek és réz megszerzésére. Azt kívánja, hogy vezesd ezt az expedíciót Serabit Khadimba, ahol egy korábbi egyiptomi őrhely épületmaradványai még megtalálhatók lehetnek. Jelenlegi állapotuk ismeretlen, de talán még mindig nyújthatnak némi védelmet az expedíció számára. @P Tudnod kell, hogy az utolsó, erre a területre küldött expedíció soha nem tért vissza. Egy később küldött mentőexpedíció sem tért vissza. Ennek ellenére, ha megfelelően fel akarjuk fegyverezni katonáinkat, királyságunknak rézre van szüksége fegyverek készítéséhez, és ez a fém ritka földünkön. @P Készülj fel, mert állandó támadás fenyeget majd a Sínai-sivatag beduinjai és ellenségeink, a kánaániak részéről. A körülmények között bányássz ki minden lehetséges rezet és drágakövet, és haladéktalanul teljesítsd a fáraó kéréseit. Ékszerészeket alkalmazhatsz, hogy a felesleges drágakövekből ékszereket készítsenek a település lakói számára."
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
                    text: "Királyi nekropolisz",

                }
                content {
                    text: "Huni fáraó örök nyugalmat kíván találni egy lépcsős piramisban, akárcsak elődje, Dzsószer. Azt szeretné, hogy nemeseinek sírjai vegyék körül, ezért Alsó-Egyiptomban Meidumot választotta e királyi nekropolisz helyszínéül. @P Házad sok nemzedéken át tartó hűséges szolgálatának elismeréseként Huni azt is engedélyezte, hogy saját sírodban Meidumban temessenek el. Ezzel nagy megtiszteltetésben részesítette családodat. @P Annak biztosítására, hogy Egyiptom bölcsessége és tudása fennmaradjon az idők során, Huni fáraó királyi könyvtárak építését is sürgeti. A papirusztekercsekkel megtöltött könyvtárak magasabb szintű oktatást biztosítanak majd a felsőbb osztályok számára. @P A fáraó egy másik hűséges udvaroncát expedícióra küldte Serabit Khadimba, a zord Sínai-félszigetre türkiz drágakövek megszerzésére. Ha az expedíció sikerrel jár, onnan drágaköveket importálhatsz. Az ékszerészek ezekből értékes luxuscikket, ékszereket készíthetnek városod lakói számára. @P Az egykor virágzó Apollinopolisz hanyatlásnak indult, és már nem exportálja sok olyan árucikkét, amelyekről korábban ismert volt."
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
                    text: "Terjeszkedés Núbiába",

                }
                content {
                    text: "Új fáraónk, Sznofru, eltökélte, hogy ez a negyedik dinasztia lesz Egyiptom valaha uralkodó legnagyobb dinasztiája. A fáraó azt kívánja, hogy határainkat még délebbre terjesszük. Ezért elrendelte Núbia megszállását és egy megerősített város alapítását Buhenben, a Nílus második kataraktája mellett. Itt egy gránitobeliszket is fel kell állítanod, amely jelképezi, hogy ez a terület örökre Egyiptomhoz és a fáraóhoz tartozik. Ilyen messze délen azonban nincs gránit, ezért Elephantinéből kell importálnod. @P Buhenben kemény és tapasztalt núbiai harcosokkal találkozol majd, akik életük árán is megpróbálják megakadályozni, hogy ilyen messze délen megvessük a lábunkat. Ne ess kétségbe, mert a Katonai Akadémián végzett alapos kiképzés után harcosaid maguk is tapasztalt veteránokká válhatnak. Ráadásul katonai mérnökeink tökéletesítették számos védelmi építmény, például erődített tornyok, falak és kapuházak terveit. Ezek felbecsülhetetlen értékűek lesznek a núbiai sereg támadásainak kivédésében. Szállítóhajókat is használhatsz, hogy szükség esetén vízen mozgasd hadseregedet. @P Északon kapcsolatokat építettünk ki Enkomival, Ciprus szigetén. Ez a föld gazdag rézérckészleteiről kapta nevét, amelyet most megvásárolhatunk tőlük. A Sínai-félszigeten, Serabit Khadimban nemrég létrehozott egyiptomi bányaközösségnek köszönhetően azonban kormányzóinkat sokkal olcsóbban tudjuk rézzel ellátni. A Serabit Khadimból érkező készletek gyakran bizonytalanok a beduinok és kánaániak állandó támadásai miatt, és nem tudjuk, meddig képesek még kitartani az ott állomásozó egyiptomi erők. @P A fáraó temetkezési helye, egyedülálló és lenyűgöző emlékmű, jelenleg építés alatt áll Dahsúrban. A fáraó időről időre kérheti, hogy mészkővel járulj hozzá a projekt befejezéséhez."
                }
            }
            message_mission_south_dahshur {
                id: 414,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Dahsúr déli része",

                }
                subtitle {
                    text: "Sznofru tört piramisa",

                }
                content {
                    text: "@PÚj fáraónk, Sznofru, eltökélte, hogy ez a negyedik dinasztia lesz Egyiptom valaha uralkodó legnagyobb dinasztiája. Építészei egy Huni lépcsős piramisánál is lenyűgözőbb sírt terveztek, és a fáraó azt kívánja, hogy felügyeld az építését. Egy megfelelő méretű települést kell létrehoznod Dahsúrtól délre, a fáraó tört piramisának helyszínén. Ha elkészül, ez a város biztosítja majd a munkaerőt e nagyszabású projekt befejezéséhez. @P A tört piramis egyszerű kőmagból épül, amelyet finom fehér mészkővel borítanak be, hogy örökké ragyogjon a sivatagi nap alatt. Dahsúrban elegendő mészkövet találsz, de a szükséges mennyiségű egyszerű követ importálnod kell az építkezéshez. @P A fáraó azt kívánja, hogy határainkat még délebbre terjesszük, ezért katonai erőket küldött Núbia megszállására és egy megerősített város létrehozására Buhenben, a Nílus második kataraktája mellett. @P Északon Egyiptom kapcsolatokat épített ki Enkomival, Ciprus szigetén. Ez a föld gazdag rézérckészleteiről ismert, amelyek most fontos importcikké váltak. @P Értékes drágaköveket szerezhetsz a Sínai-félszigeten, Serabit Khadimban nemrég létrehozott egyiptomi őrhelyről. Az utóbbi időben azonban az ellátás bizonytalanná vált a beduinok és kánaániak állandó támadásai miatt, és nem tudjuk, meddig képesek még ellenállni az ott állomásozó egyiptomi erők."
                }
            }
            message_mission_north_dahshur {
                id: 415,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Dahsúr északi része",

                }
                subtitle {
                    text: "Az igazi piramis",

                }
                content {
                    text: "@P Sznofru fáraó rendet teremtett Egyiptomban, és a királyság most bölcs és jóindulatú uralma alatt virágzik. Sznofru újabb építkezési projektet kíván megvalósítani Dahsúrban, amely még a már elkészült tört piramisnál is nagyszabásúbb. A királyi építészek, földmérők és mérnökök biztosak benne, hogy olyan épületet tudnak emelni, amelynek oldalai egyetlen folyamatos szögben emelkednek, tökéletes csúcsban végződve. Ha sikerrel járnak, ez lesz az első valódi piramis, és méltó örök otthona lesz Sznofru fáraónak! @P A fáraó felesége, Hetepheresz királyné nemrég fiút szült, akit 'Kheopsznak' neveztek el. Népeink nagy aggodalommal tekintenek uralkodásának napja elé, mert Hórusz, a fáraó istenének látnokai megjövendölték, hogy nem mutat majd olyan jóindulatot népünk iránt, mint apja. Bár sok nagyszerű dolgot fog véghezvinni, attól tartanak, hogy hajlíthatatlan zsarnoksággal fogja kormányozni Egyiptomot. @P Fát szerezhetsz Bübloszból, mivel az ácsoknak számos rámpát kell építeniük, hogy a munkások elérhessék e hatalmas piramis csúcsát."
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
                    text: "Egyiptom védelme",

                }
                content {
                    text: "@P Kheopsz fáraó elfoglalta a trónt, és ahogy Hórusz és Ré látnokai megjövendölték, népünk máris szenvedni kezdett elnyomása alatt. @P Kheopsz azonnal elrendelte, hogy királyi kormányzót küldjenek Denderába, hogy megvédje földünket a kusita betolakodóktól. Dendera kisebb halászati ipart tarthat fenn, amely egy ideig elláthatja a települést. Ha azonban a kusiták vízen támadnak, a folyó veszélyessé válhat a halászhajók számára, és a partvidék jobban használható hadihajóflotta fenntartására. Ha kevés lesz az élelem, szarvasmarhát is tenyészthetsz hús biztosítására, de a csordáknak sok szalmára van szükségük takarmányként, a szalmát pedig nehéz termeszteni ezen a vidéken. Keress más városokat, amelyekkel szalmát cserélhetsz, mert erre lesz szükséged masztabád tégláinak elkészítéséhez is. @P A libanoni Büblosz, a cédrusok földje, kereskedni kezdett kelet hatalmas birodalmaival. Ezek Asszíria és Ur, a 'Mezopotámia' nevű földön, a két nagy folyó között, és rajtuk keresztül Bübloszon át a legfinomabb elefántcsontot is megszerezheted. Ritka és egzotikus luxuscikkek érkezésével, mint ez, Dendera biztosan virágozni fog. @P A fővárosban az egyiptomi nép kezd megismerkedni egy szenet nevű társasjátékkal. Ezt a játékot általában egy korsó sör mellett, egy 'Szenetház' nevű nyilvános helyen játsszák. Az ilyen helyek kellemes kikapcsolódást nyújthatnak Dendera lakóinak Kheopsz uralmának zsarnoksága elől. @P A fáraó elrendelte, hogy Héliopoliszban, a Delta vidékén számtalan kőfejtőt nyissanak a kiváló minőségű fehér mészkő hatalmas készletének kitermelésére. Csak az istenek tudják, milyen célra tervezi a fáraó felhasználni ezt a követ. A szóbeszéd szerint hatalmas építkezést tervez a gízai fennsíkon, hogy felülmúlja apja, a bölcs és jóindulatú Sznofru hírnevét, aki két nagyszerű piramisának elkészítésével szerzett dicsőséget."
                }
            }
            message_mission_heliopolis {
                id: 417,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Héliopolisz",

                }
                subtitle {
                    text: "Elefántcsont keletről",

                }
                content {
                    text: "@P Kheopsz fáraó elfoglalta a trónt, és ahogy Hórusz és Ré látnokai megjövendölték, népünk máris szenvedni kezdett elnyomása alatt. A szóbeszéd szerint hatalmas építkezést tervez a gízai fennsíkon, hogy felülmúlja apja, a bölcs és jóindulatú Sznofru hírnevét, aki két nagyszerű piramisának elkészítésével szerzett dicsőséget. @P Kheopsz fáraó elrendelte egy kőfejtőtelep létrehozását Túrán, a Delta vidékén, ahol nemrég gazdag kiváló minőségű fehér mészkőkészleteket fedeztek fel. Három masztabasírt is építened kell e vidék nemeseinek, hogy a fáraó tisztelegjen hűségük előtt. A kőfejtőtelep, amelyet alapítottál, a 'Héliopolisz' nevet kapja, és hosszú éveken át bőséges forrása lesz a finom fehér mészkőnek... bár csak az istenek tudják, milyen célra tervezi felhasználni a fáraó. @P A libanoni Büblosz, a cédrusok földje, kereskedni kezdett kelet hatalmas birodalmaival. Ezek Asszíria és Ur, a 'Mezopotámia' nevű földön, a két nagy folyó között, és tőlük Bübloszon keresztül a legfinomabb elefántcsont is megszerezhető. Ritka és egzotikus luxuscikkek érkezésével Héliopolisz biztosan virágozni fog. @P Kheopsz egy királyi kormányzót is küldött Denderába, hogy megvédje földünket a kusita betolakodóktól. A királyi vezírek együttérzéssel tekintenek a nehéz és veszélyes feladattal megbízott kormányzóra. @P A fővárosban az egyiptomi nép kezd megismerkedni a szenet nevű társasjátékkal. Ezt a játékot általában egy korsó sör mellett, egy 'Szenetház' nevű nyilvános helyen játsszák. Az ilyen helyek kellemes kikapcsolódást nyújthatnak Héliopolisz lakóinak Kheopsz uralmának zsarnoksága elől."
                }
            }
            message_mission_giza {
                id: 418,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Gíza",

                }
                subtitle {
                    text: "A nagy piramis és a szfinx",

                }
                content {
                    text: "Kheopsz fáraó végre nyilvánosságra hozta terveit, és határtalan becsvágya súlyos terhet ró majd népünkre. A fáraó egyszerre átkoz és áld téged, mert bár elnyerted a nomarcha rangját, rád bízta hazánk valaha vállalt legnagyobb építési projektjének végrehajtását. @P A fáraó örök nyughelye egy hatalmas piramiskomplexum lesz, amely minden várostól távol, a gízai fennsíkon épül fel. Szarkofágja tömör gránitból készül, temetési bárkája pedig értékes libanoni cédrusból. A fáraó piramiskomplexuma mellett egy kisebb piramis is épül fiának, Khefrének hercegnek, akinek zsarnoksága vetekszik apjáéval, bár eredményei nem. Khefré azt is elrendeli, hogy képmását Gíza élő sziklájába véssék egy hatalmas szobor formájában, amelyet 'szfinxnek' neveznek, oroszlántesttel és emberfejjel. @P A hatalmas építkezési munkálatok támogatásához, amelyek e műemlék elkészítéséhez szükségesek, nagy települést kell létrehoznod Gízában. Emiatt a körülmények nem lehetnek különösebben kifinomultak, hiszen egyetlen célod e három nagyszerű projekt befejezése és a fáraó tisztelete. @P Biztosítunk számodra némi kiváló fehér mészkövet, amely szükséges a piramisok külső burkolatához, de a szükséges anyagok nagy részét a város saját pénzéből kell megvásárolnod. @P A fáraó rád, egyik királyi nomarchájára bízza ezt a három szent feladatot. Bizonyítanod kell rendíthetetlen odaadásodat a fáraó iránt, és teljesítened kell kívánságait... bármi legyen is az ára."
                }
            }
            message_mission_bahariya_oasis {
                id: 419,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Bahariya-oázis",

                }
                subtitle {
                    text: "A nyugati sivatag",

                }
                content {
                    text: "@P Kheopsz és Khefré uralkodása véget ért, és velük együtt lezárult az egyiptomi uralkodócsaládok negyedik dinasztiája is. Ám Hentkausz úrnő, e család távoli tagja, életet adott egy új fáraónak, 'Uszerkafnak', így a királyi vérvonal töretlenül folytatódik. Uszerkaf trónra lépésével kezdődik az ötödik dinasztia, egy sok változást ígérő korszak. @P Uszerkaf valamelyest decentralizálta országunk irányítását, és nagyobb hatalmat adott a helyi hatóságoknak. Most az olyan nomarchák, mint te, szabadabban intézhetik saját ügyeiket. A fáraó nem hatalmas örök sír építését tervezi magának, hanem más feladatot szán neked. @P A fáraó Ré istent, a Nap és a királyság istenét az istenek királyává nyilvánította, és hatalmát az egész földön ki akarja terjeszteni. Számos Naptemplom található már Egyiptom-szerte, de a fáraó Ré befolyását királyságunk legtávolabbi szegletéig kívánja eljuttatni. @P Ennek megvalósításához megerősített települést kell építened a Bahariya-oázisban, messze a nyugati sivatagban. Bölcsen használd fel az ott található vizet, mert ilyen távol a drága Nílustól még a kevés vízforrásra is gyakran pályáznak a sivatag vadállatai. Óvakodnod kell a líbiai harcosok és a sivatagi beduinok támadásaitól is, akik az utóbbi időben gyakran zaklatták a sivatagi karavánokat. Gondosan tervezd meg védelmedet, és használd fel az oázisban található minden erőforrást, például a fát és a vadakat."
                }
            }
            message_mission_abusir {
                id: 420,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Abuszír",

                }
                subtitle {
                    text: "A Naptemplom",

                }
                content {
                    text: "@P Kheopsz és Khefré uralkodása véget ért, és velük együtt lezárult az egyiptomi uralkodócsaládok negyedik dinasztiája is. Ám Hentkausz úrnő, e család távoli tagja, életet adott egy új fáraónak, 'Uszerkafnak', így a királyi vérvonal töretlenül folytatódik. Uszerkaf trónra lépésével kezdődik az ötödik dinasztia, egy sok változást ígérő korszak. @P Uszerkaf valamelyest decentralizálta országunk irányítását, és nagyobb hatalmat adott a helyi hatóságoknak. Most az olyan nomarchák, mint te, szabadabban intézhetik saját ügyeiket. A fáraó nem hatalmas örök sír építését tervezi magának, hanem más feladatot szán neked. @P A fáraó Ré istent, a Nap és a királyság istenét az istenek királyává nyilvánította, és hatalmát az egész földön ki akarja terjeszteni. Számos Naptemplom található már Egyiptom-szerte, de a fáraó azt kívánja, hogy a legnagyobb Abuszírban, Alsó-Egyiptom nedves Delta vidékén épüljön fel. @P Mint a Delta nagy része, Abuszír is gazdag vadakban, halakban és más élőlényekben, valamint növényzetben, de kevés ásványkinccsel rendelkezik. Emiatt a Naptemplom építéséhez szükséges homokkövet a Dúnkul-oázis kőfejtőiből kell importálni. Szarvasmarhát is tenyészthetsz itt hús biztosítására, de a csordáknak sok szalmára van szükségük takarmányként. @P Meg kell tisztítanod a földet, hogy megfelelő helyet alakíts ki a Naptemplom számára. Ügyelj rá, hogy előbb elegendő mennyiségű értékes kitermelt fát adj el, mert ha elfogy, többé nem biztos, hogy hozzá tudsz jutni. Apollinopolisz és Abydosz mindig fahiánnyal küzd, és vadakra is szükségük van, ezért a velük folytatott kereskedelem segíthet ellensúlyozni e szent emlékmű építésének költségeit."
                }
            }
            message_mission_dunqul {
                id: 421,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Dúnkul",

                }
                subtitle {
                    text: "A kusita fenyegetés",

                }
                content {
                    text: "@P Pepi elfoglalta a trónt, és családodat kancellári rangra emelte, de ennek ára volt. @P A központi hatalom tovább gyengül, miközben a helyi és regionális vezetők egyre nagyobb befolyásra tesznek szert. Egyes vidékeken a termések messze elmaradnak a megszokottól, és az éhínség veszélye kezd megjelenni Egyiptomban. Memphisz, az egykor pompás és gyönyörű város, hanyatlásnak indult. A látnokok nehéz időket jósolnak. @P Erős szomszédaink kihasználják Egyiptom növekvő gyengeségét. Buhen őrhelyét ostromolják a Kermából érkezett rettenthetetlen kusita katonák, Afrika legnagyobb nem egyiptomi városának harcosai. A kusiták adót követelnek, és a legkisebb provokáció is nyílt támadáshoz vezethet. Núbia szintén háborúra szólított fel, és elvesztett földjeinek visszaszerzésére készül. @P Ha Egyiptom fenn akar maradni, mindent meg kell tenned a kereskedelmi útvonalak megőrzéséért, hogy az áruk továbbra is áramolhassanak az országba és onnan kifelé. Tartsd nyitva a nehezen megszerzett kereskedelmi állomást a Selima-oázisban. Pepi, aki az utolsó útjára készül a túlvilágra, gyakran kér majd követ piramisa építéséhez, míg más, élelemhiánnyal küzdő városok tőled kérnek segítséget. @P Gondosan használd fel erőforrásaidat. Az oázisban bőségesen található értékes fa, de az erdő egy részét el kell pusztítanod, hogy hozzáférj a korlátozott vízkészlethez."
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
                    text: "A karavánút",

                }
                content {
                    text: "@P Pepi elfoglalta a trónt, és családodat kancellári rangra emelte, de ennek ára volt. @P A központi hatalom tovább gyengül, miközben a helyi és regionális vezetők egyre nagyobb befolyásra tesznek szert. Egyes vidékeken a termések messze elmaradnak a megszokottól, és az éhínség veszélye kezd megjelenni Egyiptomban. Memphisz, az egykor pompás és gyönyörű város, hanyatlásnak indult. A látnokok nehéz időket jósolnak. @P Erős szomszédaink kihasználják növekvő gyengeségünket. Buhen őrhelyét ostromolják a Kermából érkezett rettenthetetlen kusita katonák, Afrika legnagyobb nem egyiptomi városának harcosai. A kusiták adót követelnek, és a legkisebb provokáció is nyílt támadáshoz vezethet. Núbia szintén háborúra szólított fel, és elvesztett földjeinek visszaszerzésére készül. @P Próbáld meg stabilan tartani Egyiptomot egy közigazgatási állomás létrehozásával a Dakhla-oázisban. Az oázisban nagy mennyiségű értékes fa található, de ezek a fák sajnos akadályozzák a korlátozott vízkészlet elérését. E fontos helyről ébenfát importálhatsz Afrika belsejéből. Pepi, aki a túlvilágra készül, téglát fog kérni emlékműve építéséhez. Más, élelemhiánnyal küzdő városok pedig élelmiszert kérnek majd tőled."
                }
            }
            message_mission_thinis {
                id: 423,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Thinisz ",

                }
                subtitle {
                    text: "Polgárháború",

                }
                content {
                    text: "A régi életforma eltűnt, és a legtöbben attól tartanak, hogy Egyiptom soha nem nyeri vissza korábbi dicsőségét. Ozirisz hátat fordított népének, és a sorozatos alacsony áradások széles körű éhínséget okoztak. A fáraók egykor megkérdőjelezhetetlen hatalma szertefoszlott, helyét viszálykodó tartományi vezetők vették át. @P E káoszból két nemesi család emelkedett ki, amelyek megpróbálják megszerezni az ország feletti uralmat. Hérakleopolisz uralkodói jogos örökösökként tartanak igényt a trónra. Különösen kegyetlenek, és alig tesznek valamit a nép éhezésének enyhítésére. Délen egy új család, az Inyotef-ház került hatalomra Thébában. Ez a család sokat tett a déli területek újraegyesítéséért, és most Hérakleopolisz halálos polgárháborút kezdett Théba ellen egész Egyiptom uralmáért. @P Hogy bizonyítsák jóindulatukat Egyiptom népe iránt, az Inyotefek rád bízták a frissen meghódított Thinisz, Egyiptom egyik legrégebbi városának újjáépítését. Thinisz két legszebb és legősibb épülete túlélte a hódítás zűrzavarát: Ozirisz templomkomplexuma és a palota. Az Inyotefek elrendelték, hogy ha bármelyik épület elpusztul, nem pazarolnak pénzt a helyreállítására. Théba uralkodói Thinisz újjáépítését elsődleges feladatnak tekintik, és még e nehéz időkben is jelentős összegeket gyűjtöttek erre a célra. Állítsd vissza Thinisz egykori pompáját, építs haditengerészetet és hozz létre erős hadsereget, hogy megvédd a Hérakleopoliszhoz hű erők, köztük Lükopolisz, Hierakonpolisz és Hermopolisz gyakori támadásaitól. Légy óvatos Hérakleopolisz uralkodóival: adót követelhetnek, hogy próbára tegyék hűségedet, és kicsikarják debeneidet. Figyelj az alkalomra váró núbiaiakra is, akik Egyiptom belső viszályait akarják kihasználni."
                }
            }
            message_mission_thebes {
                id: 424,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Théba",

                }
                subtitle {
                    text: "Polgárháború",

                }
                content {
                    text: "A régi életforma eltűnt, és a legtöbben attól tartanak, hogy Egyiptom soha nem nyeri vissza korábbi dicsőségét. Ozirisz hátat fordított népének, és a sorozatos alacsony áradások széles körű éhínséget okoztak. A fáraók egykor megkérdőjelezhetetlen hatalma szertefoszlott, helyét viszálykodó tartományi vezetők vették át. @P E káoszból két nemesi család emelkedett ki, amelyek megpróbálják megszerezni az ország feletti uralmat. Hérakleopolisz uralkodói jogos örökösökként tartanak igényt a trónra. Különösen kegyetlenek, és alig tesznek valamit a nép éhezésének enyhítésére. Délen egy új család, az Inyotef-ház került hatalomra Thébában. Ez a család sokat tett a déli területek újraegyesítéséért, és most Hérakleopolisz uralkodói halálos polgárháborút kezdtek Théba vezetői ellen egész Egyiptom uralmáért. @P Az Inyotefek, akik elfoglaltak a Hérakleopolisz elleni harccal, rád bízták szülővárosuk, Théba fejlesztését. Ha az Inyotefek győzni akarnak ellenfeleik felett és meg akarják szilárdítani hírnevüket Egyiptomban, Thébának olyan várossá kell válnia, amelyre a többi település támaszkodhat, segítséget vagy katonákat biztosítva a rászorulóknak. Théba, amely győzelem esetén akár fővárossá is válhat, nagyszerű város kell legyen. A rendelkezésre álló szűkös erőforrásokból építs Naptemplomot és piramist, hogy megmutasd az egyiptomiaknak az Inyotefek dicsőségét. @P Théba maga sem mentes a támadásoktól. Hérakleopolisz uralkodói és híveik időről időre fenyegethetik városodat, és Hérakleopolisz megpróbálhat debeneket kicsikarni a város kincstárából. E komoly veszélyek kivédésére építs erős hadsereget és haditengerészetet, hogy megvédd városodat és segítséget nyújts a veszélybe került településeknek."
                }
            }
            message_mission_coptos {
                id: 425,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Koptosz",

                }
                subtitle {
                    text: "Újraegyesítés",

                }
                content {
                    text: "Családod a polgárháború alatt tanúsított helytállása nem maradt jutalom nélkül. Én, Mentuhotep fáraó, vezíri rangra emeltem családodat. Egész Egyiptomban nincs senki, akiben jobban bíznék nálad. Most, hogy Felső- és Alsó-Egyiptom kettős királysága újra egyesült, és a thébai főváros virágzik, szükségem van a segítségedre, hogy megszilárdítsam hatalmamat az egész országban. @P Bár Egyiptom újra egyesült, továbbra is belső összecsapások fenyegetik, különösen azokon a területeken, amelyek egykor Hérakleopolisz uralkodóit támogatták. Az új egység megszilárdításához azt akarom, hogy építsd újjá és védd meg Koptoszt. Koptosznak dicsőséges várossá kell válnia, amely megmutatja Egyiptom népének, mire képes az én uralmam alatt. A várost gyakran támadják a megmaradt hűséges városok, például Hermopolisz, ezért gondoskodnod kell határaid védelméről. @P Az éhínség még mindig sújtja az országot, és a királyság más városai gyakran kérnek majd tőled élelmet. Válaszolj olyan gyorsan, amilyen gyorsan csak tudsz szívszorító kéréseikre, hogy egész Egyiptom megismerje jóindulatomat és leghűségesebb vezírem elkötelezettségét. @P Tudom, sokat kérek tőled, de nincs más Egyiptomban, aki képes lenne végrehajtani ezt a nehéz feladatot."
                }
            }
            message_mission_beni_hasan {
                id: 426,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Beni Haszan",

                }
                subtitle {
                    text: "Újraegyesítés",

                }
                content {
                    text: "Családod a polgárháború alatt tanúsított helytállása nem maradt jutalom nélkül. Én, Mentuhotep fáraó, vezíri rangra emeltem családodat. Egyiptomban nincs senki más, akiben jobban bíznék nálad. Most, hogy Felső- és Alsó-Egyiptom kettős királysága újra egyesült, és a thébai főváros virágzik, szükségem van a segítségedre, hogy megszilárdítsam hatalmamat az egész országban. @P Bár Egyiptom újra egyesült, továbbra is belső összecsapások fenyegetik, különösen azokon a területeken, amelyek egykor Hérakleopolisz uralkodóit támogatták. Az újraegyesült ország megszilárdításához azt akarom, hogy építsd újjá és védd meg Beni Haszant, amely szinte teljesen elpusztult a polgárháború alatt. Beni Haszannak dicsőséges várossá kell válnia, amely megmutatja Egyiptom népének, mire képes az én uralmam alatt. @P Az éhínség még mindig sújtja az országot, és a királyság más városai gyakran kérnek majd tőled élelmet. Válaszolj olyan gyorsan, amilyen gyorsan csak tudsz szívszorító kéréseikre, hogy egész Egyiptom megismerje jóindulatomat és leghűségesebb vezírem elkötelezettségét. @P Van még egy nemes kérésem: szeretném, ha gránit obeliszkeket építenél, hogy még életünkben hirdessék mindazt, amit ezért a földért tettem. @P Tudom, sokat kérek tőled, de azt is tudom, hogy Egyiptomban csak te vagy képes megtenni, amit kértem."
                }
            }
            message_mission_itjtawy {
                id: 427,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Itjtavi",

                }
                subtitle {
                    text: "Új főváros alapítása",

                }
                content {
                    text: "Ó, hatalmas Ré által szeretett fáraó, milyen szerencsésnek érezheted magad! Példátlan felemelkedésed Egyiptom trónjára maga a megtestesült álom. Ennél nagyobb jutalmat sem istenek, sem emberek nem adhatnának. Családod trónra lépésével Egyiptom új kezdetet kaphat, és talán mindannyian elfelejthetjük a polgárháború borzalmait. @P Ezen új kezdet jeleként építs egy nagyszerű új fővárost. Itjtavi, gazdag természeti erőforrásaival, tökéletes helyszín erre. A föld adományait felhasználva pompás várost építhetsz, amely méltó dinasztiád bátorságához és elkötelezettségéhez. @P Hogy nagy dinasztiád tetteire örökké emlékezzenek, építs két fenséges téglapiramist magadnak és családodnak, valamint egy félelmetes szfinxet sírod őrzésére. Egy ilyen eredményekkel rendelkező család nem érdemel kevesebbet. @P Ne feledd azonban, hogy az országban vannak, akik megkérdőjelezik uralmad jogosságát. Sokan még mindig szenvednek az éhínség következményeitől, és azt suttogják, hogy bitoroltad a trónt. Ha enyhíted e nép nyomorúságát és segítesz újjáépíteni otthonaikat, bizonyára örök hűségüket nyered el. Gondoskodj új alattvalóidról a lehető legjobban, hogy ezek a szerencsétlen emberek ne ragadjanak fegyvert ellened."
                }
            }
            message_mission_mirgissa {
                id: 428,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Mirgissza",

                }
                subtitle {
                    text: "Núbia felé",

                }
                content {
                    text: "Most, hogy Egyiptom szilárdan egyesült uralmad alatt, egész udvarod és én, hűséges vezíred, azt javasoljuk, hogy terjesszük ki országunk határait dél felé, Núbiába. Az Allaqi kiszáradt folyómedre gazdag aranylelőhelyekben, és egy hatalmas város Mirgisszában, ahol te is jelen vagy, bizonyára visszatartja majd a núbiaiakat a támadási kísérletektől. Légy azonban óvatos a kusitákkal. Sokkal veszélyesebb ellenfelek, mint a núbiaiak, és kardjaikkal fognak arra ösztönözni téged, ó fáraó, hogy hagyd békén királyságukat. @P Hogy maradandó nyomot hagyj Núbiában, építs egy hatalmas obeliszket, amely Egyiptom számos vívmányáról tanúskodik. Az obeliszk meggyőző bizonyítékot szolgáltat majd a núbiaiaknak az egyiptomi uralom előnyeiről, és állandó emlékeztető lesz jelenlétünkre. @P Miközben közvetlen figyelmedet Mirgisszára fordítod, ne feledd, hogy célunk egy virágzó vörös-tengeri kikötőváros létrehozása Merszában. Merszának szüksége lesz segítségedre, és nem fog habozni kérni azt. Ha Mersza virágozni tud, a szükséges rezet biztosítja majd Mirgisszának, amelyből fegyvereket kovácsolhatnak."
                }
            }
            message_mission_mersa_gawasis {
                id: 429,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Mersza Gavaszisz",

                }
                subtitle {
                    text: "A Vörös-tenger partján",

                }
                content {
                    text: "Most, hogy Egyiptom szilárdan egyesült uralmad alatt, kereskedelmi kapcsolatokat kell kialakítanunk a világ városaival, hogy növeljük Egyiptom gazdagságát, ó Két Föld királya. @P Ahogy néped gyarapodik, egyre különlegesebb árukat követel. Belefáradva az ékszerekbe, a könnyen beszerezhető luxuscikkekbe, néped ritka és drága árukra, például tömjénre vágyik. Udvarod és én, hűséges vezíred, azt javasoljuk, hogy alapíts vörös-tengeri kikötőt Merszában. Mersza kereskedelmi útvonalat kínál a távoli Punt földjére, ahonnan a világ legfinomabb tömjénét lehet importálni, igaz, nagy költséggel. @P A szerény arany- és rézlelőhelyeken kívül Mersza kevés nyersanyagot termel, de késztermékek előállítójaként virágozhat. Nyersanyagok importálásával kereskedelmi partnereinktől és késztermékek exportálásával Mersza jelentős haszonra tehet szert. @P Miközben te Mersza megalapításával foglalkozol, egyik legbátrabb nomarchád új kereskedelmi központot hoz létre Núbiában. Városát, Mirgisszát, valószínűleg támadások fogják érni, ezért szeretett fáraómnak készen kell állnia, hogy minden szükséges erőforrást elküldjön neki. @P Uralmad alatt Mersza bizonyára a királyság egyik legszebb városa lesz, amely méltó végső nyughelyet biztosíthat neked és családodnak. Miközben virágzó kikötődet építed, ne hanyagold el a túlvilágra való felkészülést. Egy mauzóleum és egy kis téglapiramis fényűző nyughelyet biztosít majd neked és családodnak a Nádasmezőkre való átkelés után."
                }
            }
            message_mission_semna {
                id: 430,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Szemna",

                }
                subtitle {
                    text: "Az akadály",

                }
                content {
                    text: "Nagyra becsült fáraó, mindaz, amiért családod olyan keményen küzdött, veszélybe került! A núbiai hadiflotta a Nílust járőrözi, mélyen behatolva Egyiptom területére, és falvakat, valamint városokat egyaránt kifoszt. A núbiaiak kereskedelmi hajóinkat is megtámadják, és elrabolják rakományukat. Hogy északi városaid visszaverhessék az ellenséget, készen kell állnod hadihajók és katonák küldésére azoknak a településeknek, amelyeknek szükségük van rájuk. @P Hogy megakadályozzuk, hogy a núbiaiak ismét hajózhassanak vizeinken, katonai tanácsadóid erődsor építését javasolják Szemnánál, a Nílus második és harmadik zuhataga között. Az erődök dugóként zárják el az utat, délen tartva a núbiaiakat. @P A núbiaiak sikeres kiűzéséhez Kuban városának meghódítása szükséges. Kuban gazdag erőforrásokban, és elfoglalása megbénítja a núbiai gazdaságot. Miután elvetted Kuban irányítását a núbiaiaktól, homokkövet importálhatsz a városból nagy mauzóleumodhoz. Szemnai mauzóleumod emlékeztetőül szolgál majd a nyugtalan núbiaiak feletti uralmadra. @P Sok kihívás áll előtted, miközben Egyiptomot véded a núbiaiaktól. Figyelj, ó Élő Hórusz, a keleten gyülekező viharra. Lódobogás mennydörgése hallatszik egész Kánaánban, és villámgyors harci szekerek pusztítanak mindent útjukban. Ezeket a félelmetes szekereket, amelyekhez hasonlót még sehol sem láttak, a hükszosz harcosok hajtják. Máris viharfelhők gyülekeznek Egyiptom látóhatárán, ezért készülj fel a közelgő veszélyre."
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
                    text: "Bast városa",

                }
                content {
                    text: "Felséges fáraó, a jól kiépített kereskedelmi útvonalakkal most meg kell mutatnunk Egyiptomnak, mit hozhat a siker és a gazdagság. Bubastis tökéletes helyszín egy ilyen város számára: megvédhetjük keleti kereskedelmi útjainkat, miközben hódolunk Bastnak, aki mindig őrizte Egyiptomot. @PBast városa semmihez sem fogható legyen Egyiptomban. Legyen olyan gyönyörű, mint a lótuszvirág, amely szórakozással, iskolákkal, könyvtárakkal és szent helyekkel bontja ki szirmait. Lakói bőségben éljenek, és élvezhessék a finomabb dolgokat, köztük a behozott tömjént is. Mire elkészül, Bubastis lesz a kettős korona ékköve. @PMiközben ezt a dicső várost építed, figyelj a keleten gyülekező viharra. Lópaták dübörgése hallatszik egész Kánaánban, és villámgyors harci szekerek pusztítanak el mindent útjukban. Ezeket a páratlan szekereket, amelyekhez hasonlót még sehol sem láttak, a hükszosz harcosok hajtják. Már viharfelhők jelentek meg Egyiptom horizontján, ezért készülj fel a közelgő veszélyre."
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
                    text: "Egyiptom visszaszerzése",

                }
                content {
                    text: "Hatalmas fáraó, Egyiptom segítségedért kiált. A fenyegető hükszoszok megszállták földünket, és saját fővárost alapítottak Avariszban. Innen számos kereskedelmi útvonalunkat megzavarták, elvágva a szükséges ellátmányt. Meg kell állítanunk hódításukat, mielőtt túl késő lesz. @PNagy fáraó, ha úgy kívánod, vissza kell szereznünk Hermopolis városát, amelyet ezek a tisztátalan betolakodók meggyaláztak. Erős hadsereget és flottát is építenünk kell, mert csapatokat és fegyvereket küldhetünk északi szövetségeseinknek, különösen Avariszba, hogy segítsünk visszaverni a hükszosz támadást. Rád tekintenek, Ré gyermeke, támogatásért. De most nekünk is új fegyverünk van. Bölcs hadvezéreink elsajátították a rettegett harci szekér használatát, és ellenségeink ellen fordítjuk, hogy magunk előtt hajtsuk őket. Miután kiűztük a bajkeverő hükszoszokat, katonai tanácsadóink azt javasolják, hogy építsünk erődöt a Sínai-félszigeten, Sharuhennél, hogy megakadályozzuk a további keleti betöréseket. @PHa csak északi gondjaink lennének! Déli határainkról érkező hírek szerint a núbiaiak ismét kihasználják a meggyengült Egyiptom helyzetét. Visszafoglalták Mirgissa és Semna déli városait. Bár az elvesztett városok aggodalomra adnak okot, előbb a hükszoszokat kell kiűznünk, csak utána fordíthatjuk figyelmünket dél felé. @PEzek a hükszoszok istentelen betolakodók. Most fedeztük fel, hogy meggyalázták a hermopolisi piramist. Ellopták belőle mindazokat a temetési kellékeket, amelyekre az itt eltemetett hatalmas fáraónak szüksége van a Nádas mezején. Új sírmellékletekkel kell ellátnunk a sírt, hogy az itt nyugvó fáraó örök életet élhessen."
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
                    text: "Egyiptom visszaszerzése",

                }
                content {
                    text: "Ó, Két Föld ura, Egyiptom segítségedért kiált. A fenyegető hükszoszok megszállták földünket, és saját fővárost alapítottak Avariszban. Innen számos kereskedelmi útvonalunkat megzavarták. Meg kell állítanunk hódításukat, mielőtt túl késő lesz. @PLykopolisban biztonságban vagyunk a közvetlen támadástól, bár a hükszoszok vakmerően adót követelnek tőlünk. Talán csapatokat és fegyvereket kell küldenünk északi szövetségeseinknek, hogy segítsünk visszaverni a hükszosz támadást. Rád tekintenek, hatalmas fáraó, támogatásért. De most nekünk is új fegyverünk van: bölcs hadvezéreink elsajátították a rettegett harci szekér használatát, és ellenségeink ellen fordítjuk, hogy magunk előtt hajtsuk őket. @PHa csak északi gondjaink lennének! Déli határainkról érkező hírek szerint a núbiaiak ismét kihasználják a meggyengült Egyiptom helyzetét. Visszafoglalták Mirgissa és Semna déli városait. @PHa Egyiptom sértetlenül akar kijutni ezekből a zavaros időkből, sok múlik hadvezéreiden a csatatéren és a folyón. Két legjobb tábornokod bátorítására megígérted, hogy mindkettőjüknek olyan lenyűgöző piramist építesz, mint a sajátod. Ígéreted tudatában elszántan harcolnak az ellenséggel, minden erejüket és kitartásukat latba vetve. @PHatalmas fáraó, ha úgy kívánod, építs három csodálatos piramist Lykopolisban: egyet magadnak és egyet-egyet mindkét tábornokodnak. Ez a három piramis hatalmas területet foglal majd el, ezért értékes erőforrásokról kell lemondanod a hely biztosításához. Talán városodat is ki kell terjesztened a Nílus túlpartjára, hogy minden szükséges erőforráshoz hozzájuss a város felvirágoztatásához."
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
                    text: "Terjeszkedés és hódítás",

                }
                content {
                    text: "Egyiptom új erőre kapva emelkedett ki a közelmúlt nehézségeiből. Byblos minden buja erdejével és gazdag rézlelőhelyével a miénk! Jelenléteddel a város biztosan felvirágzik, és létrejön az Újbirodalom. @PÁm milyen riasztó felfedezést tettünk Byblos meghódítása után! Egy új, vad nép, a hettiták söpörtek végig Ázsia nagy részén, és egyesek szerint birodalmuk méretben vetekszik a miénkkel. Most Byblos felé fordították tekintetüket, megirigyelve gazdagságát. Ha nem készülünk fel megfelelően támadásukra, könnyen elveszíthetjük Byblost ellenségeinkkel szemben. @PMiközben a hettiták elleni harcra készülünk, Byblost örökre egyiptomivá kell tennünk. Áldásoddal, fáraó, három obeliszket emelünk: két kisebbet és egy nagyot, hirdetve hatalmadat és hírnevedet birodalmad távoli vidékein is. Ezek a magasba törő emlékművek emlékeztetik Byblos lakóit, hogy kinek tartoznak hűséggel. @PMiközben Byblos ügyeivel foglalkozunk, Egyiptom más vidékei továbbra is támadásoknak vannak kitéve. A núbiaiak egészen az első zuhatagig északra nyomultak, és segítenünk kell honfitársainknak visszaszorítani őket. Avariszból újabb rejtélyes ellenségről érkeztek hírek: a tengeri népekről. Mindkét ellenséget határozottan le kell győznünk, ha Egyiptom dicsőségre akar jutni. Hatalmad bizonyítására küldj csapatokat és hadihajókat, ha szükség lesz rájuk."
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
                    text: "Egyiptom dicsősége",

                }
                content {
                    text: "A hükszoszok sikeres kiűzésével országunk készen áll az újjászületésre, egy olyan Újbirodalomra, amely felülmúlja a múlt dicsőségét. Nemes fáraó, Kuban ideális hely az Újbirodalom kezdetéhez. Az ott talált hatalmas mennyiségű arany segítségével megvalósíthatjuk Egyiptomról alkotott új elképzeléseidet. @PEgyiptom a nagyság küszöbén áll, de néhány gond még megmaradt. Sok városunk még mindig a hükszoszok okozta zavarokból lábadozik, és szükségük lehet a fáraó segítségére. Más vidékeken régi ellenségeink támadnak minket, míg egy új ellenség, a tengeri népek, északi partvidékünket fosztogatják. Készülj fel, hogy megvédd Egyiptom városait régi és új ellenfeleinktől egyaránt. @PEgyiptom tekintélyének növekedésével sok város hajlandó kereskedni velünk. Néhányan annyira ismerik szokásainkat, és annyira csodálják hatalmadat, hogy egyiptominak tekintik magukat, míg mások idegenek számunkra, és most kereskednek velünk először. Egyiptom dicsőségére használd ki mindezen kapcsolatokat, hogy népedet ellásd minden kívánt áruval. @PAz új korszak kezdetére királyi építészeid alig várják, hogy két piramist és egy fenséges mauzóleumot építhessenek neked, fáraó. Ezek méltón tükrözik majd azt a gazdagságot és nagyságot, amelyet Egyiptomnak hoztál."
                }
            }
            message_mission_avarist {
                id: 436,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Avarisz",

                }
                subtitle {
                    text: "A tengeri népek",

                }
                content {
                    text: "Ó, Arany Hórusz, Ázsiában szilárd és megkérdőjelezhetetlen a hatalmunk, határaink pedig ismét messze benyúlnak Núbiába. Ám északi partvidékünk gondjai egyre súlyosbodnak. A tengeri népek mind vakmerőbben támadják és fosztogatják városainkat. Csak a fáraó jelenléte lehet elegendő e kegyetlen és ravasz ellenség legyőzéséhez. Ha erős hadsereggel támogatott flottát építesz, bizonyosan felülkerekedünk a tengeri népeken. @PMiközben a tengeri népek ellen harcolsz, bátor nomarkhoszaid szerte a világban vezetik hadjárataikat. Ha sikerrel járnak, Egyiptom az ázsiai nagy Eufrátesz folyótól egészen délre, a hatalmas kusita Kerma városáig uralni fogja a világot. Amikor te és nomarkhoszaid elértek az édes győzelemhez, dinasztiád lesz a legnagyobb, amely valaha is őrizte Egyiptomot. @PTávoli befolyásodat jelzi egy új, messzi kereskedelmi partner, Mükéné. Mükéné királya megismerte Egyiptom pompáját és bőségét, és kereskedni kíván velünk. Ha megnyitod ezt a kereskedelmi útvonalat, fáraó, polgáraid olyan különleges árukhoz jutnak majd, amilyeneket még sosem láttak. @PKirályi családod túlvilági nyugalmának biztosítására két lenyűgöző mauzóleumot és egy hatalmas téglapiramist kell építeni. Ezek az emlékművek minden utánad következőt emlékeztetnek majd tetteidre, akár a csatatéren, akár azon kívül hajtottad végre őket."
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
                    text: "A fáraó dicsősége",

                }
                content {
                    text: "Jóságos fáraó, békét és jólétet hoztál nemzetünknek. Bölcs és rátermett uralmad alatt Egyiptom ismét erős és dicsőséges ország. Minden nomarkhosz hűséges hozzád, és nagy nemzetünket már nem fenyegeti veszély. @PMiután beteljesítetted mindazt, amit családod oly sok évvel ezelőtt kitűzött célul, eljött az idő, hogy megörökítsd nagy dinasztiád eredményeit. Ennek egyetlen módja, ha felépíted Egyiptom valaha volt legnagyobb piramisát, amely még a gízai Kheopsz-piramisnál is hatalmasabb. Nemes családod más tagjai is sok áldozatot hoztak hosszú utadon Egyiptom uralmáig. Őket is meg kell őrizni az emlékezetben és tiszteletben részesíteni egy homokkő mauzóleummal, amely hűséges támogatásukat hirdeti. @PAz emlékművek ideális helyszíne Kahun a gazdag Fajjúm vidékén. Innen intézheted az állam minden ügyét, és válaszolhatsz városaid ellátmányigényeire, miközben felépíted hatalmas piramisodat."
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
                    text: "@PCsaládod segítségével a thíniszi Hór-Aha király sikeresen egyesítette Felső- és Alsó-Egyiptom kettős királyságát, fáraónak kiáltotta ki magát egész Egyiptom felett, és hatalmas fővárost alapított Memphiszben. @PNemzetséged ismét átköltözött, ezúttal Alsó-Egyiptom párás Delta-vidékére, a Buto néven ismert területre. Kánaáni hadihajók fenyegetik ezt a vidéket, ezért amikor eljön az idő, néhány saját hadihajót is útnak kell indítanod. @PCsaládod elérte a nemesi rangot. Ezért elvárható, hogy mielőtt e világból a következőbe távozol, elkészíts egy gyönyörű téglából épült sírt, egy masztabát, amely tested örök nyugalmát szolgálja. @PElőbb azonban farmokat kell létesítened a Nílus partján, hogy kihasználd a folyó éves áradásai által lerakott gazdag, termékeny talajt. Ez lehetővé teszi népességed növekedését és gyarapodását, míg végül elegendően nagy lesz a szent emlékmű elkészítéséhez. De vigyázz, mert a Nílus életet adó vizei között számos veszély leselkedik, például halálos krokodilok, vízilovak és maláriát terjesztő szúnyogok. @L@L Gazdálkodás a Nílus mentén @P A termékenység előnyeinek kihasználásához közvetlenül az ártérre kell építened a farmokat. A legtöbb működő épülettel ellentétben az ártéri farmoknak nincs szükségük közvetlen dolgozói hozzáférésre, de állandó paraszti munkaerőt igényelnek, amelyet munkatáborok biztosítanak a földek műveléséhez. A munkatáborokat az ártéri farmokhoz közel építsd, hogy a parasztoknak ne kelljen messzire járniuk. @G56 @L@PA Nílus minden évben kilép medréből, és gazdag, termékeny iszappal tölti fel az ártér kimerült földjét. A parasztok az éves termést közvetlenül az áradás előtt takarítják be, majd a magtárakba szállítják. Mivel évente csak egy aratás van, gondoskodj elegendő magtárról, hogy megfelelő mennyiségű élelmet tárolhass növekvő népességed számára."
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
                    text: "A tengeri népek földje",

                }
                content {
                    text: "@PNyugatról érkező nyugtalanság és elégedetlenség morajlása az utóbbi időben egyre fenyegetőbbé vált. Felderítőink jelentik, hogy több barbár törzs, amelyek ismeretlen nyelveket beszélnek, érkezett nyugati földjeink, Kürenaika partjaihoz. A helyzetet tovább súlyosbítja, hogy ezek a népek most Marayéval, Did fiával, a líbiaiak királyával és a fáraó ellenségével szövetkeztek. @PMerneptah fáraóhoz eljutott a hír, hogy ezek a hitvány népek, mögöttük asszonyaikkal, gyermekeikkel és minden vagyonukkal, hamarosan kelet felé indulnak, a termékeny Nílus-delta, szülőföldünk felé, hogy új lakóhelyet keressenek. Már kisebb összecsapások is történtek az északi Szíva- és Farafra-oázisoknál. Delta-vidéki városod, Pi-yer most útjukban áll. Rövid időn belül ez a lassan vonuló vad sereg a kapuid előtt állhat. A fáraó elrendelte, hogy ha megérkeznek, nem engedhetjük őket tovább nyomulni! @PErős hadihajók építéséhez fát, fegyverek készítéséhez pedig rezet kell importálnod. Szerencsédre a korábban veszélyes hettiták most békések, köszönhetően II. Ramszesz nagy kádesi győzelmének, Merneptah szeretett fáraó atyja révén. Tedd városodat erőssé, és készítsd fel hűséges katonáidat a halálos küzdelemre."
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
                    text: "Az asszírok visszaverése",

                }
                content {
                    text: "@PA nagy Sábaka, Felső- és Alsó-Egyiptom egyesítője és Taharka fáraó atyja óta az agresszív asszírokkal való konfliktus mindennapossá vált. Amíg élt, Sábaka fáraó helyesnek tartotta segíteni palesztinai testvéreinket, akik Asszíria kegyetlen uralma alatt szenvedtek. Vigyázz! Az istentelen Aszarhaddón király szolgái ismét hadba vonulnak, és mint mindig, szemük Egyiptom termékeny földjeire vetül. Most rajtad a sor, hogy dicsőséget szerezz! Migdol királyi polgármestereként elvárják tőled, hogy megvédd a várost az átkozott ellenség támadássorozatától. A Nílus-delta keleti peremén fekvő határerődöd Egyiptom külső védelmének első vonalában áll. @PFontos lesz katonáid megfelelő kiképzése és kereskedelmi kapcsolatok kiépítése, hogy fegyvereket szerezz, vagy nyersanyagokat vásárolj saját fegyvereid elkészítéséhez. @PNe inogj meg! Az erős katonai ellenállás elengedhetetlen Egyiptom függetlenségének megőrzéséhez. Ha csupán hét évig kitartasz, a győzelem biztos lesz. Taharka, a nagy fáraó, Sábaka második fia, figyelni fog!"
                }
            }
            message_mission_tanis {
                id: 441,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Tanisz",

                }
                subtitle {
                    text: "A hadiflotta újjászületése",

                }
                content {
                    text: "@PEgyiptom népe sok nemzedéken át szenvedett Perzsia kegyetlen uralma alatt. Babilon szorítása azonban szent földünkön már nem olyan erős, mint egykor volt. Miközben átkozott elnyomóink Görögország politikájába avatkoztak, egyiptomi felkelések sora végül meggyengítette a gyűlölt perzsa igát. Most azonban Achorisz fáraóhoz eljutott a hír, hogy Artaxerxész II. egy flottát küldött partjaink felé, amelyet Kónón admirális (egy perzsa arannyal fizetett görög kiszolgáló) vezet. A bölcs Achorisz fáraó felismerte, hogy a Níluson erős haditengerészeti jelenlétre van szükség a támadás visszaveréséhez. Tanisz következő tíz évre kinevezett királyi kormányzójaként erős hajókat kell építened és edzett katonákat kiképezned, hogy őrizd a vízi és szárazföldi megközelítési útvonalakat. @PKereskedelmi útvonalat kell létesítened Enkomival, hogy erős hajók építéséhez szükséges fát importálj. Enkomiból, Ciprus szigetéről rezet is behozhatsz. Ez a kereskedelmi útvonal azonban rendkívül veszélyes, mivel az ellenségünk ellenőrzése alatt álló levantei partok közelében halad. A fáraó szükséges ellátmányokkal való segítése kiegészítheti bevételeidet. @PTartsd szem előtt, hogy ezekben a nehéz időkben kevés a pénz. A sikerhez éppúgy jártasnak kell lenned az üzletben és kereskedelemben, mint ügyes hadvezérnek."
                }
            }
            message_mission_alexandria_2 {
                id: 442,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Alexandria",

                }
                subtitle {
                    text: "Nagy Sándor",

                }
                content {
                    text: "@PNagy Sándor, II. Philipposz makedón király fia és a babiloni birodalom ostora, jelenlétével megáldotta Egyiptom földjét. Érkezésével az utolsó romlott perzsa szatrapa sietve elmenekült. Miután Memphiszben áldozatot mutatott be az Ápisz bikának, Sándort fáraóként fogadták el. Minden nép örvendezik! Mielőtt azonban útnak indulna Ámun jóslatának keresésére a Szíva-oázisba, vezetőnk úgy döntött, hogy új várost alapít, amelyet egy napon hatalmas és terjeszkedő birodalma fővárosának kíván. Bölcsességében téged nevezett ki e leendő város első polgármesterévé! @PNagy Sándor bőséges pénzalapot biztosított számodra az építkezés megkezdéséhez, és a neves görög építész, Deinokratész segítségét is rendelkezésedre bocsátotta. Alig tizenkét év alatt várja, hogy városa kereskedelmi, kulturális és katonai ereje magas szintre fejlődjön, ugyanis megígérte, hogy visszatér. @PVezetőnk még arra is időt szakított, hogy kijelölje városa két főútvonalának helyét. A Kanóposz utca kelet-nyugati irányban húzódik; a másik főút merőleges rá, és a Lochias-foktól dél felé, a Mariut-tó irányába vezet. @PMint a projekt megbízható felügyelője, gyorsan építs kikötői létesítményeket és alakíts ki jövedelmező kereskedelmi útvonalakat. Sok vásárló lesz termékeinkre, különösen búzára, árpára, papiruszra és lenvászonra. Ne hanyagold el azonban a város kulturális és katonai oldalát sem, mert még mindig kóbor fosztogatók járják a vidéket, akik Egyiptom gazdagságát akarják megszerezni."
                }
            }
            message_mission_ptolemy_alexandria {
                id: 443,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Ptolemaiosz Alexandriája",

                }
                subtitle {
                    text: "A fény jelzőtüze",

                }
                content {
                    text: "@PNagy Sándor öröksége tovább él büszke városunkban. Bár földi maradványai Alexandria mauzóleumában nyugszanak, nagyszerű városa tovább virágzik. Rád, I. Ptolemaiosz Szótér, vár a feladat, hogy folytasd azt a munkát, amelyet a nemes Sándor kezdett el. Alig harminc évvel ezelőtti alapítása óta a város hatalmas kereskedelmi központtá vált, amely a környező vidékek nagy részét látja el nélkülözhetetlen élelmiszerekkel és fényűző árukkal. Gazdasági fejlődésének további biztosítására és a nagy kikötőbe érkező hajók biztonságos bejutásának elősegítésére hatalmas világítótornyot kell építened Pharosz szigetén, a kikötő bejárata közelében. Ennek az építménynek a fénye biztonságosan vezeti majd be a távoli hajósokat a kikötőbe, megóvva őket a veszélyes zátonyoktól. @PBár a kereskedelem fontos, nem hanyagolhatod el társadalmunk kulturális és tudományos fejlődését sem. Vezetésed alatt Alexandria a világ ismert részének szellemi fővárosává is válhat. Gyűjts tudásanyagokat közelről és távolról, és építs egy hatalmas könyvtárat, amelyben megőrizheted őket. Ahogy a méheket vonzza a méz, úgy fognak a tudósok a világ minden tájáról erre a páratlan tudás- és tanulási központra érkezni. @PE nagyszerű emlékművek felépítéséhez olyan építőanyagot kell importálnod, például fehér márványt, amely méltó ezekhez a hatalmas építményekhez. Enkomi, Ciprus szigetén, kiváló forrása ennek az anyagnak. @PVégül ne hanyagold el hadseregedet sem. Mindig akad egy hely, ahol zavargások törnek ki. Lehet, hogy távoli határvidékekre kell csapatokat küldened, hogy megvédd Egyiptom érdekeit és becsületét."
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
                    text: "Caesar és Kleopátra",

                }
                content {
                    text: "@PA Római Birodalom könyörtelen szorítása napról napra erősödik, és egyre messzebbre ér. Még Róma halálos politikai küzdelmei is elérték földünket. Pompeiusz közelmúltbeli egyiptomi partokon történt meggyilkolása után Julius Caesar teljes ellenőrzést szerzett Róma hatalmas légiói felett, és tekintetét Egyiptom gazdagságára, valamint elbűvölő fáraónőnkre, VII. Kleopátrára, XII. Ptolemaiosz Auletész lányára vetette. Bölcs vezetőnk azonban az ész harcmezején sem könnyen múlható felül. Ha Caesar őt akarja felhasználni Róma egyiptomi befolyásának növelésére, úgy ő is eszközként kívánja alkalmazni Caesart nagy országunk dinasztikus hatalmának fenntartására. @PCaesar érkezése Alexandriába népszerűtlen római katonáival felkelést szított a város függetlenségre törekvő polgárai között. Kleopátra öccse, XIII. Ptolemaiosz által feltüzelt lázadó tömeg körbezárta Caesart és embereit a város királyi negyedében. Keserves utcai harcok törtek ki, amelyek sok áldozatot követeltek. Hogy nyitva tartsa tengeri menekülési útvonalát, Caesar felgyújtatta az alexandriai kikötőben horgonyzó egyiptomi flottát. Sajnos a tűz átterjedt néhány parti raktárra is, és hatalmas mennyiségű papirusztekercset pusztított el a Nagy Könyvtár gyűjteményéből. @P Hogy kiszabaduljon a csapdából, amelyben találta magát, Caesar segítségül hívta a hűséges Mithridatészt és szíriai csapatait. Miután sikeresen elfoglalták Migdol határerődjét, Mithridatész erőltetett menetben vezette embereit a Nílus-delta csúcsán körbe, hogy délkeletről közelítsék meg Alexandriát. E sereg előőrsei jelenleg a Mariut-tó keleti partján fekvő kis falu, Maritis mellett táboroznak, és útjuk utolsó szakaszára készülnek. @PXIII. Ptolemaiosz ártalmas uralkodója értesült az erősítés közeledéséről. Válaszul nagyobb létszámú hadseregének zömét délkelet felé vezette Alexandriából. A Mariut-tó keleti partján hamarosan döntő csata veszi kezdetét. Képes leszel Mithridatész római légióit vezetve legyőzni Ptolemaiosz lázadó egyiptomi seregét, és áttörni Caesarhoz és Kleopátrához Alexandriába? Sorsuk a te kezedben van."
                }
            }
            message_mission_cleopatra_alexandria {
                id: 445,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Kleopátra Alexandriája",

                }
                subtitle {
                    text: "Egy királynő öröksége",

                }
                content {
                    text: "@PCaesar véres halála a gyilkosok tőreinek csapásai alatt zűrzavarba döntötte a római világot, és gyászba taszított téged, fáraónőnk, VII. Kleopátra. Elvesztetted szerelmedet, mentorodat, bizalmasodat és hatalmas szövetségesedet. Octavianust, Caesar tizenéves fogadott dédöccsét nevezték ki örökösnek, ám a tapasztaltabb Marcus Antonius, aki korábban Caesar konzula volt, lett az állam névleges vezetője, a fiatal Octavianus nem kis bosszúságára. Nem meglepő módon Caesar végrendelete egy szót sem ejtett róla, hogy fiad, Ptolemaiosz Caesar, akit közismerten Caesarionnak neveznek, részesedne az örökségből. Biztonságot keresve magadnak és gyermekednek, valamint Egyiptom hatalmának megőrzésére törekedve elhagytad Rómát, és Alexandriába távoztál. @PBármekkora távolság is választ el Rómától, annak belső viszályait nem hagyhatod teljesen magad mögött. Hatalmas férfiak küzdenek továbbra is a hatalomért, és támogatásod, valamint Egyiptom gazdagságához való hozzáférésed nagy előnyt jelentene bármelyik fél számára. Döntő fontosságú, hogy a hatalmi harc győztesét támogasd; a vesztes oldalára állni könnyen Egyiptom végéhez vezethet. A rivális római csoportok drámai összecsapása nemrég Philippinél történt, ahol Marcus Antonius caesariánusai döntő győzelmet arattak Brutus és Cassius erői felett. Antonius, Octavianus és Lepidus most felosztották egymás között a birodalmat, és közös uralmat gyakorolnak, Antonius pedig a keleti részt kapta, amelyhez Egyiptom is tartozik. @PNem sokkal a csata után Marcus Antonius Tarsusba hívatott Kis-Ázsiába, hogy megmagyarázhasd, miért késlekedtél a caesariánusok mellé állni. Nem vagy az, akit pórázon vezetve lehet hívni, ezért bölcsen elutasítottad a megjelenést. Hiszen mindenkinél jobban tudod, hogy egy rómaival sokkal jobb a saját feltételeid szerint találkozni, nem az övéi szerint! @PÍgy hát te, Kleopátra fáraónő, hazatértél Alexandriába, Egyiptomba. Eljött az idő, hogy tovább növeld e csodálatos város dicsőségét, amelyet a Nagy Sándor alapított, és amelynek sírját még mindig látogatják. Alexandria híres Nagy Könyvtára továbbra is a világ minden tájáról vonzza a tudósokat; a csodálatos Pharosz világítótornyának fényes jelzőtüze tovább ég, hogy a hajósok biztonságosan áthaladhassanak a kikötő veszélyes vizein. Most tovább gazdagíthatod a város szépségét azzal, hogy felépíted a hatalmas Caesareumot egykori szerelmed és fiad tiszteletére. Emellett biztosítsd saját sikeres túlvilági utadat is egy újabb mauzóleum építésével, hogy méltó módon tisztelhessenek, miután a Nádas mezejére távozol. @PAmikor Marcus Antonius legközelebb hív téged, talán kissé több tapintattal teszi majd?"
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
                    text: "Antonius és Kleopátra",

                }
                content {
                    text: "@PNemes VII. Kleopátra fáraónő, Caesar egykori hitvese és most Antonius társa, Egyiptom sorsa a te kezedben van, de kezeid most egy római, Marcus Antonius kezében nyugszanak, aki mélyen belekeveredett Róma és légiói feletti uralomért vívott küzdelembe. @PEgyiptom felbecsülhetetlen erőforrásaira szüksége volt, de szerelmedre és ragaszkodásodra is vágyott, ezért Antonius beleegyezett házassági követelésedbe. Sajnos ennek az új kapcsolatnak a híre botrányt keltett Rómában! Tudtad, hogy Antonius még mindig Octaviával, Octavianus nővérével volt házas, aki Caesar törvényes örököse, és Antoniusszal együtt Róma hatalmának birtokosa. Ám Antonius többnejűségéről szóló hírek súlyosan megterhelték kapcsolatukat. Octavianus úgy érezte, hogy Antonius nemcsak nővére és családja becsületét, hanem Róma tekintélyét is megsértette. E becsületbeli ügy rendezésére és a Róma végső uralmáért folyó küzdelem lezárására Octavianus párbajra hívta ki szerelmedet, Antoniust. Ennek tudatában Antonius, veled és egyiptomi flottáddal együtt, tábort választott a görög szárazföldön, Actium közelében. A helyszín jó kikötőt kínál számos hajó számára alkalmas horgonyhellyel. @PGyorsan fel kell építened hadseregedet, különösen haditengerészetedet. Octavianus megfogadta, hogy Kr. e. 31 szeptemberében visszatér. @PMost ismét katonai erőd teljesítményétől függ a te és Marcus Antonius sorsa, valamint Egyiptom és Róma jövője."
                }
            }
            message_mission_thutmose_valley {
                id: 447,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Thutmosz a völgyben",

                }
                subtitle {
                    text: "Az első sír",

                }
                content {
                    text: "@PMiután számos ragyogó győzelmet aratott távoli csatamezőkön Egyiptom földjeinek és népének védelmében, Thutmosz fáraó, ahogy mindenki végül, gondolatait túlvilági útjának előkészületeire fordította. Hogy utazása sikeres legyen, a fáraó azt kívánja, hogy a lehető leghamarabb kezdd meg sírjának építését. Alapíts falut a Nílus nyugati partján, hogy elegendő hozzáértő munkás álljon rendelkezésre. Keress megfelelő helyet sírjának a falu nyugati részén emelkedő sziklák között. Képzett kőfaragókra lesz szükséged, hogy a sír számos kamráját kivájják a sziklából, és tehetséges kézművesekre, hogy bevakolják és fessék a helyiségeket. @PA sír mélyebb részein dolgozó munkások megvilágításához lámpakészítő műhelyeket kell létesítened. A lámpakészítőket látnod kell cserépedénnyel és a tüzeléshez szükséges importált olajjal. Ültess hennamezőket, hogy festékanyagot biztosíts a festők számára szükséges ragyogó színekhez."
                }
            }
            message_mission_tutankhamun_valley {
                id: 448,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Tut a völgyben",

                }
                subtitle {
                    text: "Tutanhamon halála",

                }
                content {
                    text: "@PSzörnyű tragédia sújtotta szeretett ifjú fáraónkat, Tutanhamont! Uralkodása, amely egykor nagy dicsőséget ígért, a sors kegyetlen keze által idő előtt véget ért. Eljött az idő, hogy Deir el-Medina munkásai ismét örök nyughelyet készítsenek a fáraónak. Váratlanul korai halála miatt létfontosságú, hogy munkásaidat a legnagyobb erőfeszítésre ösztönözd. Tutanhamon sírját néhány rövid év alatt teljesen fel kell tölteni a túlvilági utazáshoz szükséges ellátmánnyal, és készen kell állnia megszentelt maradványainak befogadására. A gyorsaság mindennél fontosabb!"
                }
            }
            message_mission_seti_valley {
                id: 449,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Széthi a völgyben",

                }
                subtitle {
                    text: "Sír egy fáraónak",

                }
                content {
                    text: "@PLeghatalmasabb fáraónk, Széthi, I. Ramszesz fia kijelentette, hogy elérkezett az idő túlvilági útjának előkészítésére. Ennek érdekében meg kell kezdened királyi sírjának kivájását a Királyok Völgyében. Munkásaid semmilyen erőfeszítést nem kímélhetnek az előkészületek során. Megfelelő intézkedéseket kell tenni, hogy elkészültekor mestersége sok évig páratlan maradjon. @PÁm miközben ez a királyi építkezés folyik, tegyél óvintézkedéseket a sírrablók ellen! Már érkeztek jelentések kapzsi bűnözőbandákról, amelyek gazdagságot akarnak szerezni a sírok meggyalázásával és Egyiptom örökké nyugvó fáraóinak megzavarásával. Ne engedd, hogy ez az istentelen tett megszégyenítse a Királyok Völgyének királyi sírjait, mert különben, ahogy a nap keleten felkel, hírneved foltot kap a Királyságban."
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
                    text: "A Levante földjei",

                }
                content {
                    text: "@PÜdvözlégy, királyi kormányzó, a Levante helytartója és Ré fiának, fáraónknak hűséges alattvalója. Nagy szerencse ilyen korban élni, amikor Egyiptom jóindulatú keze Núbia távoli vidékeitől egészen a Levante partjaiig ér. Végtelen a bölcsessége új fáraónknak, a nagyra becsült II. Ramszesznek, és hatalmas az elképzelése, hiszen ő küldött téged, hogy uralkodj ezen a nagyszerű földön, amely most Egyiptom egyre növekvő birodalmának része. @PEz a vidék, bár továbbra is veszélyekkel teli, számos kincset rejt, amelyet ki kell aknáznunk. A zöldellő dombok magas fákkal vannak tele, amelyek kiváló fát adnak, ideálisak harci szekerek készítéséhez és sokféle építkezéshez. Rézlelőhelyek is találhatók itt, bár nem nagy mennyiségben, és nagyon hasznosak erős fegyverek készítéséhez. A fa és a réz, amelyek hazánkban oly ritkák, bizonyára örömmel fogadott kincsek lesznek, ha nagy mennyiségben visszaszállítják őket. Ezért rád bízzuk egy hatalmas kereskedelmi kikötő létrehozásának felügyeletét, ahonnan ezek az értékes áruk exportálhatók. A fáraó és Egyiptom népe hálás lesz érte! @PDe légy óvatos! Gondoskodj róla, hogy megbízható katonáid gyors harci szekerekkel és erős fegyverekkel legyenek felszerelve, mert a hettiták, bár a fáraó atyja, Széthi által vereséget szenvedtek, még mindig veszélyesek, és megkérdőjelezhetik jogos uralmunkat ezen a gazdag földön. Erős katonai jelenlétre lehet szükség ezen az új területen a lázadások leveréséhez, és a jövőben is nagy hasznodra válhat. @PVégül, hogy e vidék népe emlékezzen, kinek kell most hódolnia, II. Ramszesz fáraó megfelelőnek tartja, hogy egy dicsőségét hirdető obeliszket emelj."
                }
            }
            message_mission_qadesh {
                id: 451,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Qádés",

                }
                subtitle {
                    text: "A kádesi csata",

                }
                content {
                    text: "@PAz amurrú föld, a levantei partok közelében, hatalmas légióid patái és léptei alatt remeg, áldott fáraó. Ez a vidék ritka drágakövekkel lehet megáldva, de viszályban is bővelkedik. Fegyveres hettiták, a nyomorult Mutwatalli király vezetésével, ismét megpróbálják megszerezni az uralmat e föld felett, amely jogosan a miénk. Az elfogott kémek arról számolnak be, hogy ellenséges csapataik még messze északon járnak, így nem jelentenek veszélyt. De hihetünk-e ennek? Bölcs harcos az, aki nem ejti le pajzsát a csata közepén. @PHogy elfojtsd a lázadásról szóló híreszteléseket, te, legnagyobb tiszteletnek örvendő fáraónk, II. Ramszesz, Ré fia, megérkeztél Qádés erődvárosába. Már két rettegett harci szekérhadtest tábora is felépült a város szélén. De ez még nem minden. Közvetlen rendelkezésedre állnak más veterán csapatok is, köztük a nemrég Sumur közelében harcoló tapasztalt katonák. De vigyázz! Bölcs döntés lehet késleltetni ezen értékes erők bevetését addig, amíg valóban szükségessé nem válnak, mert bölcs az a harcos is, akinek a csata tetőpontján még megbízható tartalékai vannak. @PMiután a nyomorult ellenséget legyőzted, újjá kell éleszteni Qádés pangó gazdaságát, hogy ez a város is hozzájáruljon Egyiptom dicsőségéhez. Gyűjts értékes drágaköveket, és alkalmazz ügyes ékszerészeket, hogy pompás tárgyakat készítsenek a fáraó hűséges alattvalóinak. Ilyen ritka szépségű luxuscikkek iránt bizonyára nagy lesz a kereslet!"
                }
            }
            message_mission_abu_simbel {
                id: 452,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Abu Szimbel",

                }
                subtitle {
                    text: "Abu Szimbel kolosszusai",

                }
                content {
                    text: "@PFáraónk, II. Ramszesz dicsősége áthatja a földet. Hogy uralkodásának öröksége örökké éljen, elrendeltetett, hogy egy hatalmas emlékmű és templom épüljön uralma tiszteletére mélyen Núbiában, és maga a fáraó választotta ki a tökéletes helyszínt ehhez. Az Abu Szimbelnél, a Nílus nyugati partjára néző rózsaszín homokkő sziklákból négy hatalmas ülő alak kifaragását fogod felügyelni, amelyek Őfelségét ábrázolják. Az élő sziklából kivágott emlékmű felszínei a fáraó hősi tetteit hirdetik majd kádesi nagy győzelme során. Ez a hatalmas építmény, miközben vezetőnk hősiességét magasztalja, Núbia népe számára is emlékeztetőül szolgál Egyiptom nagyságára és hatalmára, hiszen bár Núbia gazdag aranyban és más ritka drágakövekben, lakói mindig nehezen fogadták el az egyiptomi uralmat. Ezért mindig készen kell állnod a védelemre, és csapatokat kell küldened, ha a fáraónak szüksége van rájuk. @PA homokkő exportálható a királyság más részein folyó építkezésekhez, ahogy más áruk is, amelyeket a vidék bőséges erőforrásaiból előállíthatsz. Fából azonban igen kevés található. Bizonyára kereskedelmi útvonalat kell létesítened ennek importálására, mert szükség lesz rá a hatalmas szobrok állványzatának elkészítéséhez."
                }
            }
            message_mission_ramses_valley {
                id: 453,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Ramszesz a völgyben",

                }
                subtitle {
                    text: "Páratlan nyughely",

                }
                content {
                    text: "@PSok hosszú és dicsőséges év telt el azóta, hogy legnagyobb tiszteletnek örvendő fáraónk, II. Ramszesz átvette atyja, I. Széthi jogarát és korbácsát. Ré áldásával még sokáig fog uralkodni. Mindazonáltal eljött az idő, hogy megkezdjük a föld mélyének kivájását, és előkészítsük nagy vezetőnk örök nyughelyét. A fáraó sírjának építésze számára tervet adott a valaha épített legnagyobb sírhoz, amely még atyjáét is felülmúlja. Most rajtad múlik, hogy ez a királyi kívánság sikeresen teljesüljön. @PDe légy elővigyázatos! Néhány független gondolkodású munkás és rabszolga között nyugtalanító mértékű elégedetlenség terjed, helyben és Alsó-Egyiptomban egyaránt. Egy olyan férfit követnek, akit egykor fáraónk udvarában neveltek fel, és azzal fenyegetőznek, hogy istenük segítségét kérik beavatkozás céljából. Remélik, hogy ilyen isteni támogatással elérhetik céljaikat. A papok és szent emberek még most is vitatják fenyegetéseik valódiságát. Amíg türelmesen várjuk véleményüket, bölcs dolog lehet felkészülni a váratlan eseményekre."
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
                    text: "A tengeri népek földje",

                }
                content {
                    text: "@PA nyugatról érkező nyugtalanság és elégedetlenség morajlása az utóbbi időben egyre fenyegetőbbé vált. Felderítőink jelentik, hogy több barbár törzs, amelyek ismeretlen nyelveket beszélnek, érkezett nyugati földjeink, Kürenaika partjaihoz. A helyzetet tovább súlyosbítja, hogy ezek a népek most Marayéval, Did fiával, a líbiaiak királyával és a fáraó ellenségével szövetkeztek. @PMerneptah fáraóhoz eljutott a hír, hogy ezek a hitvány népek, mögöttük asszonyaikkal, gyermekeikkel és minden vagyonukkal, hamarosan kelet felé indulnak, a termékeny Nílus-delta, szülőföldünk felé, hogy új lakóhelyet keressenek. Már kisebb összecsapások is történtek az északi Szíva- és Farafra-oázisoknál. Delta-vidéki városod, Pi-Yer most útjukban áll. Rövid időn belül ez a lassan vonuló vad sereg a kapuid előtt állhat. A fáraó elrendelte, hogy ha megérkeznek, nem engedhetjük őket tovább nyomulni! @PErős hadihajók építéséhez fát, fegyverek készítéséhez pedig rezet kell importálnod. Szerencsédre a korábban veszélyes hettiták most békések, köszönhetően II. Ramszesz nagy kádesi győzelmének, Merneptah szeretett fáraó atyja révén. Tedd városodat erőssé, és készítsd fel hűséges katonáidat a halálos küzdelemre."
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
                    text: "Az asszírok visszaverése",

                }
                content {
                    text: "@PA nagy Sábaka, Felső- és Alsó-Egyiptom egyesítője és Taharka fáraó atyja óta az agresszív asszírokkal való konfliktus mindennapossá vált. Amíg élt, Sábaka fáraó helyesnek tartotta segíteni palesztinai testvéreinket, akik Asszíria kegyetlen uralma alatt szenvedtek. Vigyázz! Az istentelen Aszarhaddón király szolgái ismét hadba vonulnak, és mint mindig, szemük Egyiptom termékeny földjeire vetül. Most rajtad a sor, hogy dicsőséget szerezz! Pelusium királyi polgármestereként elvárják tőled, hogy megvédd a várost az átkozott ellenség támadássorozatától. A Nílus-delta keleti peremén fekvő határerődöd Egyiptom külső védelmének első vonalában áll. @PFontos lesz katonáid megfelelő kiképzése és kereskedelmi kapcsolatok kiépítése, hogy fegyvereket szerezz, vagy nyersanyagokat vásárolj saját fegyvereid elkészítéséhez. @PNe inogj meg! Az erős katonai ellenállás elengedhetetlen Egyiptom függetlenségének megőrzéséhez. Ha csupán hét évig kitartasz, a győzelem biztos lesz. Taharka, a nagy fáraó, Sábaka második fia, figyelni fog!"
                }
            }
            message_mission_tanis_2 {
                id: 456,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Tanisz",

                }
                subtitle {
                    text: "A hadiflotta újjászületése",

                }
                content {
                    text: "@PEgyiptom népe sok nemzedéken át szenvedett Perzsia kegyetlen uralma alatt. Babilon szorítása azonban szent földünkön már nem olyan erős, mint egykor volt. Miközben átkozott elnyomóink Görögország politikájába avatkoztak, egyiptomi felkelések sora végül meggyengítette a gyűlölt perzsa igát. Most azonban Achorisz fáraóhoz eljutott a hír, hogy Artaxerxész II. egy flottát küldött partjaink felé, amelyet Kónón admirális (egy perzsa arannyal fizetett görög kiszolgáló) vezet. A bölcs Achorisz fáraó felismerte, hogy a Níluson erős haditengerészeti jelenlétre van szükség a támadás visszaveréséhez. Tanisz következő tíz évre kinevezett királyi kormányzójaként erős hajókat kell építened és edzett katonákat kiképezned, hogy őrizd a vízi és szárazföldi megközelítési útvonalakat. @PKereskedelmi útvonalat kell létesítened Enkomival, hogy erős hajók építéséhez szükséges fát importálj. Enkomiból, Ciprus szigetéről rezet is behozhatsz. Ez a kereskedelmi útvonal azonban rendkívül veszélyes, mivel az ellenségünk ellenőrzése alatt álló levantei partok közelében halad. A fáraó szükséges ellátmányokkal való segítése kiegészítheti bevételeidet. @PTartsd szem előtt, hogy ezekben a nehéz időkben kevés a pénz. A sikerhez éppúgy jártasnak kell lenned az üzletben és kereskedelemben, mint ügyes hadvezérnek."
                }
            }
            message_mission_alexandria {
                id: 457,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Alexandria",

                }
                subtitle {
                    text: "Nagy Sándor",

                }
                content {
                    text: "@PA nagy Sándor, II. Philipposz makedón király fia és a babiloni birodalom ostora, jelenlétével megáldotta Egyiptom földjét. Érkezésével az utolsó romlott perzsa szatrapa sietve elmenekült. Miután Memphiszben áldozatot mutatott be Ápisz bikának, Alexandert elfogadták fáraóként. Az egész nép ujjong! Mielőtt azonban elindult volna útjára Ámon jósdájához a Szíva-oázisba, vezetőnk úgy döntött, hogy új várost alapít, amelyet egy napon hatalmas és növekvő birodalma fővárosának kíván. Végtelen bölcsességében téged nevezett ki e jövőbeli város első polgármesterévé! @PA nagy Sándor bőkezű pénzadománnyal látott el, hogy megkezdhesd az építkezést, és rendelkezésedre bocsátotta a kiváló görög építész, Deinokratész szolgálatait. Alig tizenkét év alatt a város kereskedelmi, kulturális és katonai erejét magas szintre kell fejlesztened, mivel megígérte, hogy visszatér. @PVezetőnk még arra is időt szánt, hogy kijelölje városa két fő útvonalának helyét. A Kanópusz utca kelet-nyugati tengelyen halad; a másik főút merőleges rá, és Lochiasz-foktól dél felé, a Mariut-tó irányába vezet a szárazföld belseje felé. @PMegbízható felügyelőjeként ennek a vállalkozásnak gyorsan kikötőket kell építened és jövedelmező kereskedelmi útvonalakat kell kialakítanod. Sok vevőre számíthatunk termékeink számára, különösen búzára, árpára, papiruszra és lenre. Ne hanyagold el azonban a város kulturális fejlődését és haderejét sem, mert még mindig kóbor fosztogatók járják a vidéket, akik Egyiptom gazdagságára áhítoznak."
                }
            }
            message_mission_ptolemy_alexandria_2 {
                id: 458,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Ptolemaiosz Alexandriája",

                }
                subtitle {
                    text: "A fény jelzője",

                }
                content {
                    text: "@PNagy Sándor öröksége tovább él büszke városunkban. Bár földi maradványai Alexandria mauzóleumában nyugszanak, nagyszerű városa tovább virágzik. Rajtad, I. Ptolemaiosz Szótér, a nemes Alexander által megkezdett munka folytatása a sor. Alig harminc évvel Alexander alapítása után a város hatalmas kereskedelmi központtá vált, amely a környező vidék nagy részét látja el szükséges élelmiszerekkel és luxuscikkekkel. Gazdasági fejlődésének további elősegítésére és a nagy kikötőbe érkező számos hajó biztonságos bejutásának biztosítására hatalmas világítótornyot kell építened Pharosz szigetén, a kikötő bejárata közelében. Ennek az építménynek a fénye biztonságosan vezeti majd be a távoli hajósokat a kikötőbe, megakadályozva, hogy a veszélyes zátonyokon hajótörést szenvedjenek. @PA kereskedelem ugyan fontos, de nem hanyagolhatod el társadalmunk kulturális és szellemi fejlődését sem. Vezetésed alatt Alexandria az ismert világ szellemi fővárosává is válhat. Gyűjts tudományos műveket közelről és távolról, és építs hatalmas könyvtárat megőrzésükre. Ahogy a hangyákat a méz vonzza, úgy fognak a tudósok a világ minden tájáról erre a páratlan tudás- és tanulási központra seregleni. @PE nagyszerű emlékművek megépítéséhez olyan építőanyagot kell importálnod, például fehér márványt, amely alkalmas ilyen hatalmas építményekhez. Enkomi, Ciprus szigetén, jó forrása ennek az anyagnak. @PVégül ne hanyagold el a hadseregedet sem. Mindig akad valahol nyugtalanság. Szükség lehet csapatok küldésére távoli határokra, hogy megvédd Egyiptom érdekeit és becsületét."
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
                    text: "Caesar és Kleopátra",

                }
                content {
                    text: "@PA Római Birodalom tapintatlan szorítása napról napra erősebbé válik, és egyre messzebbre terjed. Még Róma halálos politikai hatalmi harcai is elérték földünket. Pompeius nemrégiben történt meggyilkolásával Egyiptom partjain Julius Caesar teljes ellenőrzést szerzett Róma hatalmas légiói felett, és tekintetét Egyiptom gazdagságára, valamint elbűvölő fáraónk, VII. Kleopátra, XII. Ptolemaiosz Auletész lányának szépségére vetette. Eszes vezetőnk azonban nem könnyen múlható felül az elmék csatájában. Ha Caesar őt Egyiptomban Róma befolyásának növelésére akarja felhasználni, ő ugyanúgy eszközként kívánja alkalmazni Caesart nagy országunk dinasztikus hatalmának megőrzésére. @PCaesar érkezése Alexandriába népszerűtlen római katonáival felkelést szított a függetlenségre törekvő polgárok között. Egy féktelen tömeg, amelyet Kleopátra öccse, XIII. Ptolemaiosz buzdít, körülzárta Caesart és embereit a város királyi negyedében. Keserves utcai harcok törtek ki, amelyek sok áldozatot követeltek. Hogy tengeri menekülési útvonalát nyitva tartsa, Caesar felgyújtotta az alexandriai kikötőben horgonyzó egyiptomi flottát. A tűz sajnos átterjedt néhány parti raktárra is, és hatalmas mennyiségű, a Nagy Könyvtárhoz tartozó papirusztekercs égett el. @PHogy kiszabaduljon a csapdából, amelybe került, Caesar segítségül hívta a hűséges Mithridatészt és szíriai csapatait. Miután sikeresen elfoglalták a pelusiumi határerődöt, Mithridatész erőltetett menetben vezette embereit a Nílus-delta csúcsán körbe, hogy délkeletről közelítsék meg Alexandriát. E sereg előőrsei jelenleg Maritis kis falujának szélén táboroznak, a Mariut-tó keleti partján, útjuk utolsó szakaszára készülve. @PA baljós XIII. Ptolemaiosz tudomást szerzett az erősítés közeledéséről. Válaszul nagyobb létszámú hadseregének zömét délkelet felé vezette Alexandriából. Döntő csata készülődik a Mariut-tó keleti partján. Képes vagy-e Mithridatész római légióit irányítva legyőzni Ptolemaiosz lázadó egyiptomi seregét, és áttörni Caesarhoz és Kleopátrához Alexandriába? Sorsuk a te kezedben van."
                }
            }
            message_mission_cleopatra_alexandria_2 {
                id: 460,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Kleopátra Alexandriája",

                }
                subtitle {
                    text: "Egy királynő öröksége",

                }
                content {
                    text: "@PCaesar véres halála a gyilkosok tőrei által káoszba taszította a római világot, és gyászba, valamint fájdalomba döntött téged, fáraónkat, VII. Kleopátrát. Elveszett szeretőd, mentorod, bizalmasod és hatalmas szövetségesed. Octavianust, tizenéves örökbe fogadott dédöccsét jelölték örökösnek, de a tapasztaltabb Marcus Antonius, aki korábban Caesar konzula volt, vált az állam névleges vezetőjévé, a fiatal Octavianus nem kis bosszúságára. Nem meglepő módon Caesar végrendelete egy szót sem ejtett közös fiatokról, Ptolemaiosz Caesarról, akit közismerten Caesarionnak neveznek. Saját és gyermeked biztonsága, valamint Egyiptom hatalmának megőrzése érdekében, ahogy mindig, elhagytad Rómát és Alexandriába tértél vissza. @PMindazonáltal Róma és közted húzódó nagy távolság ellenére sem hagyhatod hátra belső viszályait. Hatalmas férfiak továbbra is a hatalomért küzdenek – támogatásod és Egyiptom gazdagságának hozzáférése bármely párt számára óriási előnyt jelentene. E hatalmi harcban létfontosságú, hogy a győztes mellé állj; a vesztes támogatása könnyen Egyiptom végét jelentheti. A rivális római frakciók drámai összecsapása nemrég Philippinél történt, ahol Marcus Antonius caesariánusai döntő győzelmet arattak Brutus és Cassius erői felett. Antonius, Octavianus és Lepidus most felosztották egymás között a birodalmat, és Antonius a keleti részt kapta, amelyhez Egyiptom is tartozik. @PNem sokkal a csata után Marcus Antonius magához hívatott Tarsusba, Kis-Ázsiába, hogy magyarázatot adj arra, miért késlekedtél a caesariánusok mellé állni. Nem vagy olyan, akit pórázon vezetve lehet hívogatni, ezért bölcsen elutasítottad a meghívást. Hiszen mindenkinél jobban tudod, hogy egy rómaival sokkal jobb a saját feltételeid szerint találkozni, nem az övéi szerint! @PÍgy te, Kleopátra fáraó, hazatértél Alexandriába, Egyiptomba. Elérkezett az idő, hogy tovább növeld e csodálatos város dicsőségét, amelyet Nagy Sándor alapított, és amelynek sírját még mindig látogatják az emberek. Alexandria híres Nagy Könyvtára továbbra is a világ minden tájáról vonzza a tudósokat; a csodálatos pharoszi világítótorony ragyogó fénye tovább ég, hogy a hajósok biztonságosan áthaladhassanak a kikötő veszélyes vizein. Most tovább gazdagíthatod a város szépségét a kiterjedt Caesareum felépítésével egykori szeretőd és fiad tiszteletére. Emellett biztosítsd saját sikeres túlvilági utazásodat is egy újabb mauzóleum építésével, hogy méltó módon tisztelhessenek, miután eljutottál a Nádas Mezejére. @PTalán amikor Marcus Antonius legközelebb hív téged, kissé több tapintatot fog tanúsítani?"
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
                    text: "Antonius és Kleopátra",

                }
                content {
                    text: "@PÓ, nemes VII. Kleopátra fáraó, Caesar és most Antonius hitvese, Egyiptom sorsa a te kezedben van, de kezed most egy római, Marcus Antonius kezében nyugszik – ő pedig mélyen belekeveredett a Róma és légiói feletti uralomért folyó küzdelembe. @PMivel szüksége volt Egyiptom felbecsülhetetlen erőforrásaira, de egyben vágyott szerelmedre és szeretetedre is, Antonius beleegyezett házassági követelésedbe. Sajnos ennek az új frigynek a híre botrányt kavart Rómában! Ahogy tudtad, Antonius még mindig Octaviával, Octavianus nővérével, Caesar törvényes örökösének húgával volt házas, és Antoniusszal együtt Róma hatalmának egyik birtokosa volt. Antonius többnejű életmódjának híre azonban súlyosan megterhelte kapcsolatukat. Octavianus úgy érzi, hogy Antonius nemcsak nővére és családja becsületét sértette meg, hanem Róma tekintélyét is. Hogy ezt a becsületbeli ügyet rendezze, és véget vessen a Róma végső uralmáért folyó küzdelemnek, Octavianus párbajra hívta szeretődet, Antoniust. Ennek tudatában Antonius, veled és egyiptomi flottáddal együtt, tábort keresett a görög szárazföldön, Actium közelében. A helyszín jó kikötőt kínál, számos lehetséges hajóhellyel. @PGyorsan meg kell erősítened hadseregedet, különösen a haditengerészetet. Octavianus megfogadta, hogy Kr. e. 31 szeptemberében visszatér. @PMost a te sorsod és Marcus Antoniusé, valamint Egyiptom és Róma sorsa ismét a katonai erő teljesítményétől függ."
                }
            }
            message_mission_deir_el_medina {
                id: 462,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Deir el-Medina",

                }
                subtitle {
                    text: "Az első sír",

                }
                content {
                    text: "@PMiután számos ragyogó győzelmet aratott távoli csatamezőkön Egyiptom földjeinek és népének védelmében, Thutmosz fáraó, ahogy mindenki végül, gondolatait túlvilági útjának előkészületeire fordította. Hogy utazása sikeres legyen, a fáraó azt kívánja, hogy a lehető leghamarabb kezdd meg sírjának építését. Alapíts falut a Nílus nyugati partján, hogy elegendő hozzáértő munkás álljon rendelkezésre. Keress megfelelő helyet sírjának a falu nyugati részén emelkedő sziklák között. Képzett kőfaragókra lesz szükséged, hogy a sír számos kamráját kivájják a sziklából, és tehetséges kézművesekre, hogy bevakolják és fessék a helyiségeket. @PA sír mélyebb részein dolgozó munkások megvilágításához lámpakészítő műhelyeket kell létesítened. A lámpakészítőket látnod kell cserépedénnyel és a tüzeléshez szükséges importált olajjal. Ültess hennamezőket, hogy festékanyagot biztosíts a festők számára szükséges ragyogó színekhez."
                }
            }
            message_mission_tutankhamun_valley_2 {
                id: 463,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Tut a völgyben",

                }
                subtitle {
                    text: "Tutanhamon halála",

                }
                content {
                    text: "@PSzörnyű tragédia sújtotta szeretett ifjú fáraónkat, Tutanhamont! Uralkodása, amely egykor nagy dicsőséget ígért, a sors kegyetlen keze által idő előtt véget ért. Eljött az idő, hogy Deir el-Medina munkásai ismét örök nyughelyet készítsenek a fáraónak. Váratlanul korai halála miatt létfontosságú, hogy munkásaidat a legnagyobb erőfeszítésre ösztönözd. Tutanhamon sírját néhány rövid év alatt teljesen fel kell tölteni a túlvilági utazáshoz szükséges ellátmánnyal, és készen kell állnia megszentelt maradványainak befogadására. A gyorsaság mindennél fontosabb!"
                }
            }
            message_mission_seti_valley_2 {
                id: 464,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Széthi a völgyben",

                }
                subtitle {
                    text: "Sír egy fáraónak",

                }
                content {
                    text: "@PLegkiválóbb fáraónk, Széthi, I. Ramszesz fia kijelentette, hogy elérkezett az idő túlvilági útjának előkészítésére. Ennek érdekében meg kell kezdened királyi sírjának kivájását a Királyok Völgyében. Munkásaid semmilyen erőfeszítést nem kímélhetnek az előkészületek során. Megfelelő intézkedéseket kell tenni, hogy elkészültekor mestersége sok évig páratlan maradjon. @PÁm miközben ez a királyi építkezés folyik, tegyél óvintézkedéseket a sírrablók ellen! Már érkeztek jelentések kapzsi bűnözőbandákról, amelyek gazdagságot akarnak szerezni a sírok meggyalázásával és Egyiptom örökké nyugvó fáraóinak megzavarásával. Ne engedd, hogy ez az istentelen tett megszégyenítse a Völgy királyi sírjait, mert különben, ahogy a nap keleten felkel, hírneved foltot kap a Királyságban."
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
                    text: "A Levante földjei",

                }
                content {
                    text: "@PÜdvözlégy, királyi kormányzó, a Levante helytartója és Ré fiának, fáraónknak hűséges alattvalója. Nagy szerencse ilyen korban élni, amikor Egyiptom jóindulatú keze Núbia távoli vidékeitől egészen a Levante partjaiig ér. Végtelen a bölcsessége új fáraónknak, a nagyra becsült II. Ramszesznek, és hatalmas az elképzelése, hiszen ő küldött téged, hogy uralkodj ezen a nagyszerű földön, amely most Egyiptom egyre növekvő birodalmának része. @PEz a vidék, bár továbbra is veszélyekkel teli, számos kincset rejt, amelyeket ki kell aknáznunk. A zöldellő dombok magas fákkal vannak tele, amelyek kiváló fát adnak, ideálisak harci szekerek készítéséhez és sokféle építkezéshez. Rézlelőhelyek is találhatók itt, bár nem nagy mennyiségben, és nagyon hasznosak erős fegyverek készítéséhez. A fa és a réz, amelyek hazánkban oly ritkák, bizonyára örömmel fogadott kincsek lesznek, ha nagy mennyiségben visszaszállítják őket. Ezért rád bízzuk egy hatalmas kereskedelmi kikötő létrehozásának felügyeletét, ahonnan ezek az értékes áruk exportálhatók. A fáraó és Egyiptom népe hálás lesz érte! @PDe légy óvatos! Gondoskodj róla, hogy megbízható katonáid gyors harci szekerekkel és erős fegyverekkel legyenek felszerelve, mert a hettiták, bár a fáraó atyja, Széthi által vereséget szenvedtek, még mindig veszélyesek, és megkérdőjelezhetik jogos uralmunkat ezen a gazdag földön. Erős katonai jelenlétre lehet szükség ezen az új területen a lázadások leveréséhez, és a jövőben is nagy hasznodra válhat. @PVégül, hogy e vidék népe emlékezzen, kinek kell most hódolnia, II. Ramszesz fáraó megfelelőnek tartja, hogy egy dicsőségét hirdető obeliszket emelj."
                }
            }
            message_mission_qadesh_2 {
                id: 466,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Qádés",

                }
                subtitle {
                    text: "A kádesi csata",

                }
                content {
                    text: "@PAz amurrú föld, a levantei partok közelében, hatalmas légióid patái és léptei alatt remeg, áldott fáraó. Ez a vidék ritka drágakövekkel lehet megáldva, de viszályban is bővelkedik. Fegyveres hettiták, a nyomorult Mutwatalli király vezetésével, ismét megpróbálják megszerezni az uralmat e föld felett, amely jogosan a miénk. Az elfogott kémek arról számolnak be, hogy ellenséges csapataik még messze északon járnak, így nem jelentenek veszélyt. De hihetünk-e ennek? Bölcs harcos az, aki nem ejti le pajzsát a csata közepén. @PHogy elfojtsd a lázadásról szóló híreszteléseket, te, legnagyobb tiszteletnek örvendő fáraónk, II. Ramszesz, Ré fia, megérkeztél Qádés erődvárosába. Már két rettegett harci szekérhadtest tábora is felépült a város szélén. De ez még nem minden. Közvetlen rendelkezésedre állnak más veterán csapatok is, köztük a nemrég Sumur közelében harcoló tapasztalt katonák. De vigyázz! Bölcs döntés lehet késleltetni ezen értékes erők bevetését addig, amíg valóban szükségessé nem válnak, mert bölcs az a harcos is, akinek a csata tetőpontján még megbízható tartalékai vannak. @PMiután a nyomorult ellenséget legyőzted, újjá kell éleszteni Qádés pangó gazdaságát, hogy ez a város is hozzájáruljon Egyiptom dicsőségéhez. Gyűjts értékes drágaköveket, és alkalmazz ügyes ékszerészeket, hogy pompás tárgyakat készítsenek a fáraó hűséges alattvalóinak. Ilyen ritka szépségű luxuscikkek iránt bizonyára nagy lesz a kereslet!"
                }
            }
            message_mission_abu_simbel_2 {
                id: 467,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Abu Szimbel",

                }
                subtitle {
                    text: "Abu Szimbel kolosszusai",

                }
                content {
                    text: "@PFáraónk, II. Ramszesz dicsősége áthatja a földet. Hogy uralkodásának öröksége örökké éljen, elrendeltetett, hogy egy hatalmas emlékmű és templom épüljön uralma tiszteletére mélyen Núbiában, és maga a fáraó választotta ki a tökéletes helyszínt ehhez. Az Abu Szimbelnél, a Nílus nyugati partjára néző rózsaszín homokkő sziklákból négy hatalmas ülő alak kifaragását fogod felügyelni, amelyek Őfelségét ábrázolják. Az élő sziklából kivágott emlékmű felszínei a fáraó hősi tetteit hirdetik majd kádesi nagy győzelme során. Ez a hatalmas építmény, miközben vezetőnk hősiességét magasztalja, Núbia népe számára is emlékeztetőül szolgál Egyiptom nagyságára és hatalmára, hiszen bár Núbia gazdag aranyban és más ritka drágakövekben, lakói mindig nehezen fogadták el az egyiptomi uralmat. Ezért mindig készen kell állnod a védelemre, és csapatokat kell küldened, ha a fáraónak szüksége van rájuk. @PA homokkő exportálható a királyság más részein folyó építkezésekhez, ahogy más áruk is, amelyeket a vidék bőséges erőforrásaiból előállíthatsz. Fából azonban igen kevés található. Bizonyára kereskedelmi útvonalat kell létesítened ennek importálására, mert szükség lesz rá a hatalmas szobrok állványzatának elkészítéséhez."
                }
            }
            message_mission_ramses_valley_2 {
                id: 468,
                    type: 3,
                    size [40, 30]
                title {
                    text: "Ramszesz a völgyben",

                }
                subtitle {
                    text: "Páratlan nyughely",

                }
                content {
                    text: "@PÉvek hosszú, dicsőséges sora telt el azóta, hogy legnagyobb tiszteletnek örvendő fáraónk, II. Ramszesz, átvette atyjától, I. Széthitől a pásztorbotot és az ostort. Ré áldásával még sokáig fog uralkodni. Ennek ellenére elérkezett az idő, hogy megkezdjük a föld mélyének feltárását, és előkészítsük nagyra becsült uralkodónk örök nyughelyét. Fáraónk átadta sírja építészének a valaha épített legnagyobb sír tervét, amely még atyjáét is felülmúlja. Rajtad múlik, hogy e királyi kívánság sikerrel megvalósuljon. @PDe légy elővigyázatos! Nyugtalanító mértékű elégedetlenség terjed néhány önálló gondolkodású munkás és rabszolga között, helyben és Alsó-Egyiptomban egyaránt. Egy olyan férfit követnek, akit egykor fáraónk udvarában neveltek, és azzal fenyegetőznek, hogy istenük segítségét kérik beavatkozásra. Azt remélik, hogy ilyen isteni támogatással elérhetik céljaikat. Még most is papok és szent emberek vitatják e fenyegetések hitelességét. Amíg türelmesen várunk véleményükre, bölcs dolog lehet felkészülni a váratlan eseményekre."
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
                    text: "Története",
                }
                content {
                    text: "Több mint három évezreden át különböző népek használták a cserjeszerű hennanövényt festékanyag forrásaként. A henna (tudományos nevén Lawsonia inermis) a füzényfélék családjába tartozik, és eredetileg Észak-Afrikában és a Közel-Keleten őshonos. Összezúzott levelei és ágai narancsvörös festéket adnak, amely megfelelő alkalmazás esetén haj, körmök és bőr színezésére használható. A hennát még ma is gyakran alkalmazzák számos vallási szertartásban és temetkezési rítusban Ázsiában, a Közel-Keleten és Afrikában, valamint ez a népszerű „ideiglenes tetoválások” alapvető színezőanyaga. A henna emellett sokféle hajfesték elsődleges színezőanyaga."
                }
            }
            message_mission_paint_maker {
                id: 470,

                    size [30, 28]
                title {
                    text: "Festékkészítő",
                }
                content {
                    text: "A festékkészítőknek @469henna utánpótlásra van szükségük a festék előállításához. A hennanövény összezúzott leveleit és szárát különböző festékanyagok készítésére használják, amelyek szükségesek a festék gyártásához. A hennát @91Henna&Farmokon termesztik, vagy @47kereskedelmi&útvonal hozható létre importálására. @PEgy Festékkészítő akkor dolgozik hatékonyan, ha elegendő munkással, úthálózati kapcsolattal és egy szállítmány hennával rendelkezik. A gyártás befejezése után a festéket egy @4Raktár&udvarba szállítják. A festéket ezután az @363Kézművesek használják a @478Királyi&temetkezési&sírkamrák festéséhez. @PKellemetlen szaguk és zajuk miatt a Festékkészítők @56nem&kívánatos szomszédok. @L@L Kattints @472ide, hogy többet tudj meg az ókori egyiptomi festékkészítésről."
                }
            }
            message_illness_video {
                id: 471,
                    type: 2,

                    size [30, 20]
                title {
                    text: "Betegség",
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
                    text: "Kézművesek",
                        pos [125, 15]
                }
                subtitle {
                    text: "Története",
                }
                content {
                    text: "Bár az ókori Egyiptom legtöbb építményén művészek dolgoztak a végső díszítésen, ezeknek a tehetséges alkotóknak a rendkívüli képességei igazán az Újbirodalom sírjaiban, a @475Királyok&völgyében mutatkoznak meg. A föld alatti sírok belső falainak és mennyezeteinek szinte minden négyzetcentimétere az elhunyt nagyságát hirdette gondosan festett hieroglifákkal és más ábrázolásokkal. @PA díszes és részletgazdag képek ellenére az ókori művészek meglehetősen korlátozott színpalettával dolgoztak, és természetes ecseteket használtak @94nád vagy rostos faanyag, például pálmaágak felhasználásával. Pigmentjeiket gyakran kis műhelyekben előre elkészítették természetes festékanyagokból (például @469hennából) és más természetes ásványi pigmentekből (például kalcium-karbonátból, faszénből, vas-oxidból, realgárból, auripigmentből, azuritból és malachitból), amelyeket porrá őröltek. Ezeket ezután kötőanyaggal, például növényi gumival vagy állati enyvvvel keverték, majd festékként alkalmazták. @PSzámos különleges képzettségű művész dolgozott együtt, hogy pompás domborműveket hozzanak létre a sírokban. Először @190agyag, víz és fehérítőanyag keverékéből vakolatot készítettek, majd felvitték a sír falaira. Ezután vörössel durva vázlatot rajzoltak a friss vakolatra. Egy mesterrajzoló finomította ezt a körvonalat, általában feketével. Egy mesterszobrász további javításokat végzett és részleteket adott hozzá, hogy irányítsa az utána következő domborműkészítőt. Ezután nagy, egyszínű felületekkel felvitték a festéket. A végső részleteket, például a körvonalakat és belső elemeket, egy másik mesterművész készítette el."
                }
            }
            message_building_lamp_maker {
                id: 473,

                    size [30, 28]
                title {
                    text: "Lámpakészítő",
                }
                content {
                    text: "A Lámpakészítő olyan lámpákat készít, amelyek fénye segíti a munkásokat egy @478Királyi&temetkezési&sírkamra sötét folyosóin való közlekedésben. @P Lámpák készítéséhez a Lámpakészítőnek kerámiára és olajra van szüksége. Egy @1Fazekas kerámiát biztosíthat, vagy importálható egy @47kereskedelmi&partnertől. @476Olajat csak importálni lehet. @PEgy Lámpakészítőnek útkapcsolatra és közeli munkaerőforrásra van szüksége. Amint elegendő kerámia és olaj érkezik hozzá, láthatod, ahogy a lámpakészítők szorgosan megtöltik olajjal az edényeket, hogy lámpákat készítsenek. @PA Lámpakészítők negatívan befolyásolják a @56kívánatosságot, ezért ne helyezd őket túl közel a lakónegyedekhez. @L@L Kattints @474ide, hogy többet tudj meg az ókori Egyiptom lámpáiról."
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
                    text: "Lámpák",
                        pos [125, 15]
                }
                subtitle {
                    text: "Története",
                }
                content {
                    text: "Az ókori egyiptomiak kis kerámialámpákat készítettek, amelyek természetes @476olajjal vagy feldolgozott állati zsiradékkal működtek. Ezek a lámpák szükséges fényforrást biztosítottak a temetkezési sírok mélyén dolgozó kézművesek számára."
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
                    text: "Királyok völgye",
                        pos [125, 15]
                }
                subtitle {
                    text: "Története",
                }
                content {
                    text: "@PA Királyok völgye öt évszázadon át, körülbelül i. e. 1539-1075 között volt a fáraók temetkezési helye, köztük I. Thotmeszé, Tutanhamoné és Nagy Ramszeszé (II. Ramszeszé). A Nílus nyugati partján, Théba templomegyütteseivel szemben fekvő völgyet az el-Qurn nevű, szinte piramis alakú hegy uralja, amely minden nap a napnyugta előtt Ré utolsó áldását fogadja. A völgy és a nagy Nílus között találhatók a fáraóknak szentelt halotti templomok, akik a völgy sírjaiban várták túlvilági életüket. A közeli Deir el-Medina falu több száz munkásnak és családjaiknak adott otthont. @PA Királyi temetkezési sírokat szakképzett munkások készítették, és mindenkinek fontos feladata volt. @385Kőművesek lépcsőket és folyosókat vájtak a mészkősziklákba. A nagyobb termek mennyezetét kőoszlopok tartották. A kifaragott helyiségeket elsimították és bevakolták, mielőtt a @472kézművesek megérkeztek, hogy domborművekkel és festményekkel díszítsék a mennyezeteket és falakat, amelyek segítették a fáraót túlvilági útján. Az elhunyt királyt szarkofágjába helyezték, majd a sírt számos, isteni rangjához méltó kinccsel lezárták. Ezek a hatalmas kincsek miatt a sírokat gyakran kifosztották, néha éppen azok, akik őrzésükre lettek kijelölve. @PEurópai régészek az 1800-as évek elején fedezték fel újra a Királyok völgyét. 1922-ben Howard Carter feltörte Tutanhamon lezárt sírját, és számos kincset talált benne, köztük egy aranyszarkofágot. Az évszázadok során hirtelen áradások sok sírt iszappal és törmelékkel töltöttek fel, és jó esély van rá, hogy még ma is vannak felfedezetlen folyosók, sőt talán sírok is a völgyben."
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
                    text: "Olaj",
                        pos [125, 15]
                }
                subtitle {
                    text: "Története",
                }
                content {
                    text: "Az ókori egyiptomiak által használt olajok többségét Görögországból, Ciprusról és Föníciából importálták. A természetes olajokat sokféleképpen használták, például a @474lámpák üzemanyagaként és főzéshez. Az olajokat számos forrásból nyerték (amelyek nagy részét ma is használják), például szezámból, lenmagból, olajbogyóból és természetes állati zsiradékokból."
                }
            }
            message_figure_tomb_robber {
                id: 477,

                    size [30, 28]
                title {
                    text: "Sírrabló",
                }
                content {
                    text: "@PAhol sír van, ott kincs is akad! A sírrabló olyan bűnöző, aki akkor jelenik meg, ha a @39Városi&hangulat rendkívül rossz. Csak akkor támadja meg azonban a várost, ha van mit kifosztania. Ha városodban nincsenek sírok (sem piramisok, @371masztabák, @368mauzóleumok vagy @478Királyi&temetkezési&sírkamrák), nem fog odajönni. Akkor sem érdekli a város, ha nincsenek benne @374temetkezési&ellátmányok, akár azért, mert a sír nem igényelt ilyet, akár azért, mert még nem küldted el őket a sírhoz. @PNéha sírrablók akkor is lecsapnak, amikor a városban semmilyen bűnözés jele nem látható. Ha hivatásos sírrablók hírt kapnak társaiktól arról, hogy városod sírjaiban különösen értékes temetkezési kellékek találhatók, bűnhullámot indítanak. Nem lehet előre megjósolni, mikor következik be egy ilyen bűnhullám. @PA sírrablóknak egyetlen céljuk van: megfosztani az örök álomba merült fáraót azoktól a gazdagságoktól és kincsektől, amelyeket sírjában a túlvilági életre helyeztek el. Ehhez a tervhez a sírrablónak el kell jutnia a sírig anélkül, hogy elfognák. Ha út közben őrrel vagy katonákkal találkozik, általában csendben és hatékonyan „őrizetbe veszik”, bár egy rendkívül fürge tolvaj néha még így is elmenekülhet. Ha a sírrabló sikeresen eléri a temetkezési emlékművet, elvisz néhány korábban elküldött temetkezési kelléket, és ez hátrányosan befolyásolja a @35Királyság&értékelésedet, hiszen ki akarna olyan uralkodó alatt élni, aki képtelen megvédeni ősei sírjainak szentségét? @PA sírrablók nem válogatnak a sírok között. Ugyanolyan szívesen próbálnak meg kifosztani egy olyan emlékművet is, amely már uralkodásod kezdete előtt a városban állt. Szerencsére ezek a régi sírok jól le vannak zárva, így a sírrabló nem tud belőlük temetkezési kellékeket elvinni. Azonban Egyiptom-szerte mindenki megdöbben azon, hogy az egyik legrégebbi sírt fenyegetés érte, ezért királyságod megítélése jelentősen romlik. @PVigyázz! Ha a sírrabló elvisz temetkezési kellékeket, minden ellopott tárgyat pótolnod kell a küldetés teljesítéséhez. @PA városod bűnözéséről további információért kattints @36ide. @L@LAz ókori Egyiptom Királyok völgyének temetkezési sírjairól további információért kattints @475ide."
                }
            }
            message_building_royal_burial_tomb {
                id: 478,

                    size [30, 28]
                title {
                    text: "Királyi temetkezési sírkamra",
                }
                content {
                    text: "@PAz Újbirodalom korától kezdve az ókori egyiptomiak a fáraókat és más előkelőségeket egyre díszesebb, a sziklába vájt sírokban temették el egy szinte megközelíthetetlen völgyben. @PA Királyi temetkezési sírkamra építésének megkezdéséhez először megfelelő helyet kell találnod. Válaszd a „Királyi temetkezési sírkamra” lehetőséget a Vallási építmények: Emlékművek listájából. Egy nagy alaprajz jelenik meg. Az emlékmű nagy részét sziklákra kell helyezni, kivéve a kis bejáratot, amely oldalából nyúlik ki. Mozgasd az alaprajzot a sziklák között, amíg megfelelő helyet nem találsz. Tudni fogod, hogy jó helyet választottál, amikor az egész alaprajz zöldre vált. Az alaprajz bármely piros része azt jelzi, hogy a hely nem alkalmas az emlékmű számára. @PLehet, hogy könnyebb lesz elhelyezni a Királyi temetkezési sírkamrát, ha ideiglenesen elsimítod a sziklákat. Nyomd meg a „H” billentyűt a sziklák elegyengetéséhez, vagy válaszd a @18rétegek listájából a „Sziklák elrejtése” lehetőséget. A sziklák visszaállításához nyomd meg újra a „H” billentyűt, vagy válaszd a „Normál” lehetőséget a rétegek listájából. Különösen nagy sírok esetén az „M” billentyű is hasznos lehet. Az „M” megnyomása rögzíti az alaprajzot, így elmozdíthatod a nézetet, hogy ellenőrizd a kiválasztott helyet. Ha megfelelő, egyszerűen kattints az egérrel az emlékmű elhelyezéséhez. Ha a hely nem megfelelő, nyomd meg ismét az „M” billentyűt az alaprajz felszabadításához, és folytasd a keresést. @PMiután kiválasztottad a helyet, lámpaszállítmányt kell küldeni a sírhoz, mielőtt a munka megkezdődhet. A lámpákat egy @473Lámpakészítő készíti, de importálhatók egy @47kereskedelmi&partnertől is. Amint 400 lámpa van egy @4Raktár&udvarban, egy paraszt szánon lámpákat húz az építkezéshez. @PMiután a lámpák megérkeztek és fényt biztosítanak, a @363kőművesek durván kifaragják a sír számos kamráját a tömör sziklából. Miután a kőművesek befejeztek egy kamrát, képzett @363kézműveseket hívnak, hogy megkezdjék a falak vakolását és festését. Ezeknek a kézműveseknek @92agyagra van szükségük a vakolathoz, valamint egy @470Festékkészítő által készített festékre. Az árukat közvetlenül a Kézművesek Céhéhez szállítják az előállítók, vagy egy Raktárudvarból érkeznek. Ha városod nem képes előállítani egyik vagy mindkét árut, lehetőséged nyílhat @47importálni őket. @PKattints jobb gombbal egy Királyi temetkezési sírkamra emlékműre, hogy meglátogasd annak @369Építési&felügyelőjét a munkálatok állapotjelentéséért. @L@L Kattints @475ide, hogy többet tudj meg a Királyok völgyéről és királyi temetkezési sírkamráiról."
                }
            }
            message_building_zoo {
                id: 479,

                    size [30, 28]
                title {
                    text: "Állatkert",
                }
                content {
                    text: "Az állatkertek minden városban népszerű @49szórakozási&formát jelentenek. Az állatkerthez úthálózat, az állatok gondozásához munkások, valamint @89szalma és @359vad&hús szükséges takarmányként. A szalmát a gabonaföldekről lehet begyűjteni, a Vadászkunyhó vadászai pedig vadhúst szerezhetnek. Ezeket az árukat @47kereskedelmi&útvonalon is importálhatod. @PÉrdeklődj @28Szórakozási&felügyelődnél, hogy megtudd, hány állatkert van a városodban, és használd a @18Szórakozás&nézetet annak megtekintésére, mely házakból érhető el az állatkert, valamint hogy lásd az utcákon sétáló gondozókat. @PAz állatkert különleges látványosságai ellenére a lakosok nem szeretnek túl közel élni hozzájuk, mivel az állatok üvöltése és erős szaga igencsak sértő bármely művelt egyiptomi számára. Kattints @56ide a vonzerőről szóló további információkért. @L@LAz ókori egyiptomi állatkertekről további információért kattints @480ide."
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
                    text: "Állatkert",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Az ókori egyiptomiak kedvelték a mulatságos és szokatlan dolgokat, és mindkettő bőségesen megtalálható volt az állatkertekben. Ahogy Egyiptom hatalma és befolyása több kontinensre is kiterjedt, sok fáraó kapott távoli vidékek uralkodóitól különleges és egzotikus állatokat ajándékként vagy hódolat jeléül. Ezeket az állatokat a fáraónak ajándékozták, majd különleges állatkertekben tartották őket, amelyek elkerülhetetlenül az uralkodó palotájának közelében helyezkedtek el. Úgy tűnik, Egyiptom korai állatkertjei elsősorban látványosságként, másodsorban pedig tanulmányozás céljára szolgáltak. Alexandria Nagy Könyvtárának állítólag botanikus kertje és állatkerti része is volt a területén."
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
                    text: "Alexandria and its Library",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "Nagy Sándor kezdettől fogva azt remélte, hogy Alexandria, a Nílus torkolatánál általa alapított és megtervezésében segített város, a Földközi-tenger térségének kereskedelmi és kulturális központjává válik. Alapítása után kevesebb mint ötven évvel, Kr. e. 331-ben a virágzó metropolisz a kereskedelem kifinomult központjává vált, nagyrészt híres Nagy Könyvtárának köszönhetően. @PNem sokkal Nagy Sándor váratlanul korai, Kr. e. 323-ban bekövetkezett halála után hatalmas birodalma három nagy területre szakadt. Egyik legközelebbi barátja és legtehetségesebb hadvezére, Ptolemaiosz, ekkor Egyiptom tényleges kormányzója volt. Átvette az ősi föld irányítását, végül fáraóvá vált (I. Ptolemaiosz Szótér néven), és ezzel folytatta az Egyiptomban Sándor által megkezdett görög jelenlétet. Ptolemaiosz térítette el Sándor temetési menetét is, amely Makedóniába tartott, és ő hozta a hódító földi maradványait Alexandriába, hogy ott helyezzék nyugalomra. @PAzonban a személyes dicsőség és fényűző élet mellett a korai ptolemaioszi uralkodók becsületükre legyen mondva városuk és országuk kultúrájának fejlesztésében is érdekeltek voltak. Alexandria, Egyiptom új fővárosa, már a világ ismert részének kereskedelmi központja volt; azt akarták, hogy egyben a tudomány központjává is váljon. Ennek érdekében hozták létre és építették fel Alexandria Nagy Könyvtárát. A Nagy Könyvtár az emberiség első tudományos oktatási és kutatóközpontja volt. Az ókor ragyogó elméi itt fektették le a csillagászat, földrajz, irodalom, matematika, orvostudomány és fizika rendszeres tanulmányozásának alapjait. Itt határozta meg Eukleidész először a geometria alapjait, és Eratoszthenész itt mérte meg pontosan a Föld kerületét, miközben azt állította, hogy India Spanyolországból nyugat felé hajózva is elérhető. @PA ptolemaiosziak rengeteg időt és energiát, valamint vagyonuk jelentős részét fordították arra, hogy megszerezzék minden fontos, az emberiség által ismert kézirat másolatát. Ennek érdekében törvényt hoztak, amely kimondta, hogy minden Alexandriába érkező karavánt és hajót át kell kutatni – nem csempészáru, hanem tudományos művek után. Minden megtalált térképet vagy tekercset átadtak a könyvtárnak, hogy az írnokok lemásolhassák. Így Alexandria tudományos menedéke végül több mint 700 000, rendszerezetten katalogizált papirusztekercset őrzött, köztük számos mára elveszett művészeti, irodalmi és tudományos remekművet Homérosztól, Arisztotelésztől, Szophoklésztől, Aiszkhülosztól és Euripidésztől. @PNem minden szólt azonban a tudásról. A legendás könyvtár területén botanikus kert, múzeum és a kilenc múzsának (a művészetek és tudományok görög isteneinek és istennőinek) szentelt templom is helyet kapott. Egy rövid séta a kerttel szegélyezett palánk mentén egy @480állatkerthez vezetett, amely kétségkívül sok egzotikus állatnak adott otthont. Sok ókori tudós járta oszlopcsarnokait. @PNem teljesen világos, mi vezetett a Nagy Könyvtár pusztulásához. Felbecsülhetetlen értékű műveinek jelentős része minden bizonnyal elpusztult abban a tűzben, amely akkor keletkezett, amikor Julius Caesar felgyújtotta Kleopátra VII. fivérének hajóit. A Kr. u. 4. századra, ahogy a kereszténység befolyása terjedt, a könyvtár fennmaradt kéziratainak nagy részét állítólag megsemmisítették a pogányság és eretnekség minden emlékének eltörlésére irányuló törekvésben. Később, Kr. u. 640-ben az arabok, akik az akkor már szinte elhagyott városon átvonultak, valószínűleg tüzelőanyagként elégették a még megmaradt tekercseket. A Nagy Könyvtárban őrzött 123 Szophoklész-darabból mára mindössze hét maradt fenn."
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
                    text: "Történelem",
                }
                content {
                    text: "A Caesareumot VII. Kleopátra kezdte építtetni. Eredetileg egy kis templomból vagy oltárból állt egy szentély közepén, amelyet feltehetően Marcus Antonius kultuszának tiszteletére szántak. Öngyilkossága, majd nem sokkal később Kleopátra halála azonban azt jelentette, hogy az emlékművet riválisuk, Octavianus (Augustus Caesar) fejezte be, aki saját kultuszának szentelte az épületet. Két obeliszk (amelyeket gyakran Kleopátra tűinek neveznek, noha neki semmi köze nem volt hozzájuk) évszázadokon át Alexandria keleti kikötőjének partvidékén álló jellegzetes látványosság volt. Ezeket az obeliszkeket Octavianus parancsára Héliopoliszból szállították Alexandriába, és a Caesareum bejáratát jelölték még jóval azután is, hogy az épület többi része elpusztult. Mindkét obeliszket elszállították már (az egyik New York városának Central Parkjában áll, a másik a londoni Temze partján). @PA Caesareum pontos felépítéséről nem sokat tudunk. Ismereteink néhány ókori szerző rövid leírásából származnak. Építészete, Alexandria többi nagy emlékművéhez hasonlóan, görög stílusú volt. Feltehetően egy központi szentélyből állt, amelyet nyitott udvarok vettek körül, valamint sztoák (oszlopcsarnokok) öveztek, amelyek valószínűleg az emlékmű külső 'falait' alkották. A sztoák között elhelyezkedő helyiségek és oszlopcsarnokok tekercseket őriztek, valamint gyűlések vagy csendes tanulás céljára szolgálhattak."
                }
            }
            message_plague_of_locusts {
                id: 483,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title {
                    text: "Sáskák csapása",
                }
                content {
                    text: "Jelentéseket kaptunk arról, hogy éhes sáskák őrült rajai pusztítják Egyiptom terméseit. Óvakodjatok támadásuktól a következő termesztési időszakban!"
                }
            }
            message_plague_of_frogs {
                id: 484,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title {
                    text: "Békák csapása",
                }
                content {
                    text: "Rút átok szállt a földre! Békák sokasága szennyezi utcáinkat és otthonainkat, lakóinkat pedig arra kényszeríti, hogy elhagyják házaikat!"
                }
            }
            message_hailstorm {
                id: 485,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title {
                    text: "Jégeső",
                }
                content {
                    text: "Halál és pusztulás közeleg a széllel! Vad jégeső érkezett, hogy pusztító jégzáport zúdítson ránk. Az istenek irgalmazzanak azoknak, akik nem találnak menedéket e gonosz átok elől, mert kevés reményük van a túlélésre!"
                }
            }
            message_river_of_blood {
                id: 486,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title {
                    text: "Vérfolyam",
                }
                content {
                    text: "Jaj nekünk! A vizek, amelyek egykor az élet és a táplálék forrásai voltak, vérrel mérgeződtek meg. Meddig tart még, míg megszűnik ez a gyalázatos csapás?"
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
                    text: "Pharoszi világítótorony",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "@PAlexandria fekvése ideális volt kereskedelmi kikötő számára, hosszú tengerparttal és nagy természetes kikötővel, azonban a kijáratait veszélyes homokpadok övezték. Ezért született meg az elképzelés, hogy a kikötő bejáratánál fekvő Pharosz szigetén álló magas világítótorony nemcsak a hajósok segítségére szolgálna, hanem (ha elég pompás lenne) új, lenyűgöző látványosságként Alexandria hírnevét is növelné. @PA pharoszi világítótorony, ahogy később nevezték, nagyrészt prokonnészoszi fehér márványból épült, amelynek jelentős részét a mai Törökország partjainál fekvő Herceg-szigetekről hozták. Három nagy szintből állt: az alsó szint négyszögletes, a középső nyolcszögletű, a legfelső pedig henger alakú volt. Egy hatalmas csigalépcső vezetett a tetejére, amely még azt is lehetővé tette, hogy teherhordó állatok fát szállítsanak fel a fényes tűz táplálására. A lenyűgöző építményt egyes beszámolók szerint Poszeidón szobra koronázta; mások szerint Zeusz képmása volt – vagy talán mindkettőjük szobra. @PA pharoszi világítótorony építését az első Ptolemaiosz (Auletész) kezdte meg, de csak fia, II. Ptolemaiosz Philadelphosz uralkodása alatt, Kr. e. 283-ban fejezték be. Minden beszámoló szerint hihetetlen látványt nyújtott, és méltán tartották az ókori világ hetedik csodájának. @PAz emlékmű végső pusztulását nem emberi kéz, hanem a térséget megrázó földrengések sorozata okozta. Legfelső szintje egy súlyos földrengés során, Kr. u. 303-ban omlott le. Azonban csak az 1303. augusztus 8-án bekövetkezett hatalmas rengés döntötte romba a megmaradt építmény nagy részét, amelyet aztán elnyeltek a környező vizek. Ma a Pharosz szigetén egy erőd látható, amelyet Kait bég mamlúk szultán építtetett azon a helyen, ahol egykor a csodálatos világítótorony állt."
                }
            }
            message_building_alexandria_library {
                id: 488,

                    size [30, 28]
                title {
                    text: "Alexandria könyvtára",
                }
                content {
                    text: "A világ minden tájáról tudósok és művelt férfiak és nők özönlenek Alexandria Nagy Könyvtárába, az emberiség legnagyobb tudástárába. @PAz Alexandria könyvtárának megépítéséhez először megfelelő helyszínt kell választanod. Válaszd ki Alexandria könyvtárát a Vallási épületek: Emlékművek listájából. Ha a megjelenő alaprajz teljesen zöld, akkor a kiválasztott hely megfelelő. @PAz Alexandria könyvtárának felépítéséhez szükséged lesz a @8Munka&táborok parasztjainak, a @363Kőfaragók&céheinek kőműveseire és a @363Ácsok&céheinek ácsaira. Az ácsoknak @94fára lesz szükségük az állványzat elkészítéséhez, amelyet importálhatsz, ha városodban nem tudsz fát kitermelni. Emellett @47fehér&márványt is importálnod kell egy kereskedelmi partnertől. Az emlékmű befejezéséhez @93réz utánpótlásra lesz szükséged, akár saját bányáidból, akár kereskedelmi partner segítségével. @PAz építés közben jobb gombbal kattints Alexandria könyvtárára, hogy jelentést kapj az előrehaladásról az @369Építési&vezetőtől. @L@LKattints @481ide Alexandria könyvtárának történetével kapcsolatos további információkért."
                }
            }
            message_building_pharos_lighthouse {
                id: 489,

                    size [30, 28]
                title {
                    text: "Pharoszi világítótorony",
                }
                content {
                    text: "Alexandria lenyűgöző pharoszi világítótornya nappal és éjjel egyaránt segíti a hajósokat a kikötő veszélyes zátonyai között való eligazodásban. @PA pharoszi világítótorony csak Alexandria kikötőjének Pharosz szigetén, a sziklás talajra építhető. Válaszd ki a „Pharoszi világítótorony” épületet a Vallási épületek: Emlékművek listájából, majd mozgasd a kurzort a külső kikötő bejárata közelében található sziklás terület fölé. Amikor az épület alaprajza teljesen zölddé válik, megfelelő helyet találtál, amely elbírja ennek a hatalmas építménynek a súlyát. @PMiután a területet megtisztították, importált fehér márványra lesz szükséged. Ezt az árut egy másik várossal létesített @47kereskedelmi&útvonalon szerezheted be. A Kőfaragók Céhének @363kőfaragói gondosan elhelyezik a fehér márványt, amelyet a @8Munka&tábor parasztjai egy @4Raktár&udvarból szállítanak oda. A parasztok akkor viszik a márványt az építkezéshez, amikor egyetlen Raktárudvarban legalább négy tömb található belőle. Az építkezés megkezdése után az Ácsok Céhének @363ácsaira és megfelelő mennyiségű @94fára is szükség lesz az állványzat elkészítéséhez. @PKattints jobb gombbal a pharoszi világítótoronyra építés közben, hogy megtekintsd az @369Építési&vezető jelentését az előrehaladásról. @L@LKattints @487ide, hogy többet tudj meg Alexandria pharoszi világítótornyáról."
                }
            }
            message_building_caesareum {
                id: 490,

                    size [30, 28]
                title {
                    text: "Caesareum",
                }
                content {
                    text: "Alexandria egyik legkiválóbb építészeti remekműve a Caesareum, egy hatalmas tengerparti templom és látványos tájékozódási pont a város óriási kikötőjébe érkező hajósok számára. @PA Caesareum megépítéséhez először válaszd ki azt a Vezérlőpulton található Vallási épületek: Emlékművek listájából. Kiválasztása után megjelenik az épület alaprajza. Keress egy megfelelően nagy, megtisztított területet, és helyezd el az emlékművet. Tudni fogod, hogy megfelelő helyet választottál, amikor az alaprajz teljesen zölddé válik. @PAmint a megfelelő helyet kijelölted, megkezdődhet az építkezés. A @8Munka&tábor parasztjai először megtisztítják a területet, feltárva az alatta lévő alapkőzetet. Amikor a terület elkészült, a Kőfaragók Céhének @363kőfaragói megérkeznek, hogy elhelyezzék a fehér márványt, amelyet a parasztok egy @4Raktár&udvarból szállítanak. A fehér márványt @47importálni kell egy kereskedelmi partnertől. A parasztok azonnal az építkezéshez húzzák a márványt, amint egyetlen Raktárudvarban négy tömbnyi mennyiség van belőle. @PAz Ácsok Céhének @363ácsaira és @94fával való ellátásukra szintén szükség lesz az állványzat felépítéséhez. Ha városod nem rendelkezik saját faforrással, importálnod kell. A munkálatok vége felé egy Raktárudvarból származó gránitra is szükség lesz, amelyet importálhatsz, ha városod nem tud saját maga @95kőfejteni. @PKattints jobb gombbal a Caesareumra építés közben, és az @369Építési&vezető jelentést készít az előrehaladásról. @LKattints @482ide a Caesareum történetével kapcsolatos további információkért."
                }
            }
            message_crime_wave {
                id: 491,
                    type: 2,

                    size [30, 20]
                urgent: 1,
                    title {
                    text: "Bűnözési hullám",
                }
                content {
                    text: "Az istenek irgalmazzanak nekünk! Kapzsi sírrablók egy csoportja, akik jogtalanul szerzett kincsekre áhítoznak, elszabadultak gyönyörű városunkban. Állítsd meg őket, mielőtt ellopják a nemes halottainkkal együtt eltemetett pompás temetkezési javakat!"
                }
            }
            message_building_abu_simbel {
                id: 492,

                    size [30, 28]
                title {
                    text: "Abu Szimbel",
                }
                content {
                    text: "@PAz Abu Szimbel temploma hatalmas emlékmű, amelyet II. Ramszesz vésetett ki a Núbiában, a Nílus felső folyását uraló homokkősziklákból. @PAz Abu Szimbel építésének megkezdéséhez először válaszd ki a Vallási épületek: Emlékművek listájából. Megjelenik az emlékmű alaprajza. Az építmény nagy részét a sziklákba kell építeni. A bejáratnak, amely az épület oldalából nyúlik ki, szabad területen kell elhelyezkednie. Tudni fogod, hogy megfelelő helyet választottál, amikor az egész alaprajz zölddé válik. Kattints az egérgombbal az emlékmű rögzítéséhez. @PHasznos lehet ideiglenesen lesimítani a sziklás terepet, miközben megfelelő helyet keresel az emlékmű számára. Egyszerűen nyomd meg a „H” gombot, vagy válaszd a @18rétegek&listájából a „Sziklák elrejtése” lehetőséget. A sziklákat ismét visszaállíthatod eredeti magasságukra a „H” gomb újbóli megnyomásával, vagy a rétegek listájában a „Normál” kiválasztásával. @PAmikor kijelölted a megfelelő helyet, szükséged lesz egy hozzáértő munkáscsoportra: a Kőfaragók Céhének @363kőfaragói a szikla kifaragásához, valamint az Ácsok Céhének @363ácsai a szükséges állványzat elkészítéséhez. Az ácsoknak @192fára lesz szükségük az állványzathoz, amelyet @47kereskedelmi&útvonalon importálhatsz, vagy egy @94Favágó gyűjthet be a területről. @PKattints jobb gombbal Abu Szimbel emlékművére, hogy jelentést kapj az @369Építési&vezetőtől az előrehaladásról. @L@LKattints @493ide, hogy többet tudj meg II. Ramszesz leghíresebb emlékművéről."
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
                    text: "Abu Szimbel",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "@PNagy Ramszesz (II. Ramszesz) Kr. e. 1279–1212 között uralkodott Egyiptomban. Ez a hosszú életű fáraó számos uralkodása alatt épült templomról és emlékműről híres, amelyek közül a legnagyobb Abu Szimbel volt. @PA Nílus völgyére néző rózsaszín homokkősziklákba Núbia tartományában, Waszettől (Thébától) mintegy 350 mérföldre délre Ramszesz kőfaragói a fáraó négy ülő szobrát vésték ki egymás mellett. Mindegyik szobor több mint 66 láb magas – csak a gízai Nagy Szfinx magasabb náluk. Az ülő alakok egy alagút bejáratát fogják közre, amely a sziklába 160 láb mélyen vájt belső szentélyhez vezet. A templom kelet felé néz, és úgy tervezték, hogy évente kétszer a felkelő nap fénye behatoljon a szentély hátsó faláig, megvilágítva Ramszesz, Amun és Ré három kisebb szobrát. Ptah szobra szintén a szentélyben található, de mivel ő az alvilághoz kapcsolódik, szobrát úgy helyezték el, hogy a napfény ne érje. A templom belsejében található domborművek Ramszesz katonai győzelmeinek is emléket állítanak. A közelben, a sziklákba vájt testvértemplom Hathor istennőnek és Ramszesz legfőbb feleségének, Nofertari királynénak állít emléket. Az egész épületegyüttes célja a núbiai alattvalók lenyűgözése és adóik ösztönzése volt. @PAbu Szimbel építése Kr. e. 1256 körül fejeződött be. Az évezredek során homok temette maga alá. 1817-ben Giovanni Belzoni régész feltárta a hatalmas emlékművet. Az 1960-as évek közepén ismét az eltemetés veszélye fenyegette, ezúttal az újonnan épült asszuáni gát mögött emelkedő víz miatt. Abu Szimbelt kivágták a sziklából, majd nagy pontossággal magasabb területen építették újjá – olyan mérnöki teljesítményként, amely bizonyára lenyűgözte volna az ókori egyiptomiakat."
                }
            }
            message_tutorial_major_plagues {
                id: 494

                size [30, 28]
                title { text: "Nagy csapások" }
                content { text: "Sokféle katasztrófa sújthat egy várost, méretétől és gazdagságától függetlenül, és a nagy csapások a legrosszabbak közé tartoznak. Ne feledd azonban, hogy a nagy csapások nem azonosak a @53járvánnyal. A járvány akkor sújtja a várost, amikor annak egészségi állapota különösen rossz. A nagy csapások azonban minden különösebb ok nélkül is bekövetkezhetnek. @PA nagy csapások mindegyike csökkenti a @39városi&hangulatot. Egyéb súlyos következményeiket alább olvashatod: @L@LVérfolyam @LAmikor a Vérfolyam lesújt a városodra, a folyó és a város vizei hónapokra vérré változnak, és alkalmatlanná válnak @44ivó&vízként és más célokra való használatra. A házakban tárolt víz egy része is szennyezetté és ihatatlanná válik, és a folyóhoz legközelebb élők érzik leginkább a hatásait. A víz közelében élők emellett nagyobb veszélynek vannak kitéve betegségek és malária szempontjából is (a betegségekről és maláriáról további részleteket a @53városi&egészség résznél találsz). A @84Halász&mólók, @59Víz&emelők, @94Nád&gyűjtők, @62Kutak és @61Víz&készletek nem működnek a csapás idején. Egy elégedetlen @354Baszt is rászabadíthatja ezt a csapást a városodra, de akár minden felismerhető ok nélkül is bekövetkezhet. @L@LBékák @LAmikor a Békák csapása eléri városodat, békák légiói özönlik el a határaidat, és ellepik az útjukba kerülő házakat. Senki sem élhet békákkal fertőzött házban, ezért a lakók kénytelenek kiköltözni, és hónapokig senki sem költözhet vissza. Megpróbálhatod kordában tartani a békákat úgy, hogy falakat építesz köréjük, vagy épületeket helyezel el stratégiailag, hogy bezárd őket. @352Ptah hozhatja ezt az átkot a városodra, ha nem tetszését keresed, de a békák maguktól is megjelenhetnek. @L@LJégeső @LA halálos jégdarabok a jégesők következményei, és megölhetnek bárkit, aki a városban tartózkodik. A jégdarabok nem válogatnak: éppúgy végezhetnek katonákkal (beleértve az ellenséget is) és állatokkal, mint egyszerű polgárokkal. A jégesők erőteljes viharokat is keltenek a folyón, és sok hajód elsüllyedhet. Ha elhanyagolod @353Seth-et, ő hozhatja el ezt a rettegést városodra. A jégeső természetes időjárási jelenségként is bekövetkezhet. @L@LSáskák @LA sáskák ellepik a földet, és felfalják mindazt, amit a @45gazdaságaid termesztenek. Mind az ártéri, mind a réti földek termése teljesen elpusztul közvetlenül a betakarítás előtt, megfosztva városodat az adott év termésének hasznától. Amikor felkeltetted @350Ozirisz haragját, elküldheti ezt a csapást városodra. Néha azonban a sáskák minden előzmény nélkül is megjelennek. @L@LA fáraók földjét sújtó nagy csapásokról további információért kattints @495ide." }
            }
            message_history_major_plagues {
                id: 495,

                    size [30, 20]
                image {
                    id: 1010,
                        pos [15, 15]
                }
                title {
                    text: "Nagy csapások",
                        pos [125, 15]
                }
                subtitle {
                    text: "Történelem",
                }
                content {
                    text: "A Kr. e. 13. században, I. Széthi és fia, Nagy Ramszesz (II. Ramszesz) uralkodása idején az egyiptomi hébereket rabszolgasorba vetették, hogy építkezéseken dolgozzanak. A Biblia Kivonulás könyve szerint az Úr Isten megjelent Izrael egyik gyermekének, Mózes prófétának, és megígérte neki, hogy segít népének megszabadulni. Az Úr vezetésével Mózes ezért tíz alkalommal kérte a fáraótól: „Bocsásd el népemet!”, de Ramszesz minden alkalommal megtagadta a kérést. Minden egyes megtagadás újabb csapást hozott a fáraóra és az egyiptomiakra, miközben a rabszolgasorban élő hébereket megkímélte. Először a folyó változott vérré, elpusztítva a halakat és ihatatlanná téve a vizet. A fáraó második elutasítása után békák jöttek elő a tavakból és folyókból, és ellepték a falvak házait. A hetedik csapás egy mennydörgő jégeső volt, amely a mezőkön tartózkodó embereket és állatokat sújtotta, valamint elpusztította az árpa- és lenvetéseket. A Kivonulás könyve szerint Ramszesz nyolcadik megtagadása, hogy elengedje Izrael fiait Egyiptomból, sáskák raját idézte elő, amelyek sötétségbe borították a földet tömegükkel, és felfalták mindazt a zöld növényt, amit az előző csapás jégesője meghagyott. Ramszesz a tizedik csapás után engedett, amikor az elsőszülött egyiptomi gyermekek és állatok mind elpusztultak, bár később hadseregét küldte a menekülő héberek üldözésére a Nádas-tengeren át. @PBár ezek a csapások nem szerepelnek korabeli egyiptomi feljegyzésekben, a történelem és az őstörténet során számos hasonló katasztrófa történt. Még a Kr. u. 20. században is jégesők és sáskárrajok sújtották az emberiséget."
                }
            }
            message_mummy_attacks {
                id: 496,
                    type: 2,

                    size [30, 20]
                urgent: 1
                title { text: "Múmiatámadások!" }
                content { text: "Egy múmia életre kelt, és városunk utcáin jár. Állítsd meg ezt az élőhalott átkot, mielőtt az egész földön elterjed." }
            }
}
