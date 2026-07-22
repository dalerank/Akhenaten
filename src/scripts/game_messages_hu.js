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
            text: "Architect's Post",
        }
        content {
            text: "Large structures, like Storage Yards, mines, Granaries, Temples and Temple Complexes, are prone to collapse.  Architects patrolling the city's streets repair structural flaws before disaster strikes.  Architects are based in Architect's Posts. @G68 @PArchitect's Posts need road access and labor to function properly.  @PYou can check to see if a particular building has a risk of collapse by using the @18Risks:&Damage&Overlay.  If you notice that a certain building or group of buildings has a high risk of collapse, you may want to place an Architect's Post nearby to ensure that an architect provides his services. @PCollapse can have catastrophic effects.  If a @3Granary or @4Storage&Yard collapses, any food or goods stored there will be lost."
        }
    }

    message_building_whipwright {
        id: 82,
        
        size [30, 28]
        title {
            text: "Shipwright",
        }
        content {
            text: "Shipwrights supply boats for both commercial and military purposes. They build fishing boats for @84Fishing&Wharves, warships for @356Warship&Wharves and transport ships for @357Transport&Wharves. Shipwrights need to be built on a straight stretch of  coastline. You'll know when you have chosen a viable spot when you see a green 'ghost' of the Shipwright. @PBuild the Shipwright on a navigable body of water like the Nile or a seacoast.  Shipwrights located on narrow inlets or inland bodies of water will be unable to send their ships to the wharves that await them.  This can torpedo your whole maritime effort, as the Shipwright repeatedly builds vessels that are scuttled as soon as they determine that they cannot reach their target wharves. @PShipwrights need labor and road access to be operational. They also need a supply of wood to build transport ships and warships. They do not need wood to build fishing boats. Shipwrights receive orders to build a ship directly from the wharves. Once the boat is complete, it sails from the Shipwright to the appropriate wharf. Unless you need to build a lot of boats quickly, one Shipwright should be able to serve your needs. @PShould a warship or transport ship be damaged in combat, send it to the Shipwright for repairs. Heavily-damaged ships limp to the Shipwright on their captains' own initiative. The Shipwright will repair the damage if it has a supply of wood. @PShipwrights do not build the boats used by the @58Ferry&Landings.  Ferryman provide the boats to transport their passengers, and immigrants and emigrants have their own boats.  @PShipwrights make a lot of noise, so no one wants to live nearby. @L@LThe ancient Egyptians built boats of different shapes and sizes.  To find out more about this ancient industry, click @179here."
        }
    }
    
    message_building_dock {
        id: 83,
        
        size [30, 28]
        title {
            text: "Dock",
        }
        content {
            text: "Some of the city's @47trade&partners come by water.  Great trading vessels float down the Nile, but they won't do your city any good if they don't have a place to dock.  Build a Dock on the coastline for these barges to moor.  Be sure to locate the Dock on the Nile or on a seacoast, where trading vessels sail.  A Dock built on a narrow inlet or an inland body of water will be unable to receive trade ships. @PTo function properly, Docks must also have road access and labor.  Once a trade ship has docked, cart pushers from the Dock busily unload commodities and bring them to the city's @4Storage&Yards, and then load any goods the city is exporting to this partner and bring them back to the Dock.  It's a good idea to build a Storage Yard near your Dock to shorten the cart pushers' journeys. @PDocks have a negative effect on an area's @56desirability. @L@LFor more on trade in ancient Egypt, click @177here."
        }
    }

    message_building_fishing_wharf {
        id: 84,
        
        size [30, 28]
        title {
            text: "Fishing Wharf",
        }
        content {
            text: "If you see fish periodically leaping out of a body of water, fishermen can catch these fish for food. To catch the fish, the city needs one or more fishing boats. @PFishing boats are berthed at Fishing Wharves. Fishing Wharves must be built on straight section of shore, and half of the stucture must overhang the water so that vessels can have access to them. Be sure that the fishing boat can navigate the waters around the Fishing Wharf. If you place the Fishing Wharf on a narrow inlet, fishing boats will not be able to get to them. This can torpedo your whole maritime effort, as Shipwrights repeatedly build fishing boats that are instantly scuttled when they fail to reach their destination wharf.  @PIf the city has a working @82Shipwright, building a Fishing Wharf signals the ship builders to get busy building a fishing boat. The Shipwright does not need any raw materials to build a fishing boat. @PFish stocks are limited, but cannot be completely depleted.  A large population will flounder if it tries to subsist solely on fish. @PFishing Wharves are smelly places and make @56undesirable neighbors. @L@LClick @186here to find out more about fishing in ancient Egypt."
        }
    }

    message_building_defensive_structures {
        id: 85,
        
        size [30, 28]
        title {
            text: "Defensive Structures",
        }
        content {
            text: "The @37army and @356navy defend the city after enemies penetrate its borders.  Building defensive structures may prevent enemies from ever setting foot within the city proper. @L@LWalls @LThe most basic defensive structure is the Wall.  To build Walls, choose them from the Military Structures: Defensive Structures list.  Click and drag the mouse to build large sections of a Wall at one time, just as you can do with roads. @PWalls that are a single layer thick only slow down enemies briefly.  To best defend your city from attack, build Walls several layers thick.  It takes enemy soldiers much longer to break through a thick Wall. @PWalls are built from whatever natural materials are at hand, so no stone needs to be quarried or imported to build them.  They are nevertheless expensive to build, so think carefully about the perimeter that you want to enclose. @PWalls do not need road access and are undesirable neighbors. @L@LTowers @LBuild Towers to add a little offense to your defensive Walls.  Towers are manned by guards trained by the city's @88Recruiter to hurl javelins on any enemies brave or foolhardy enough to come within range. @PProvided the Wall is wide enough for them to walk on, Towers also send out sentries to patrol the length of the Wall and rain arrows on approaching enemies. @PTowers must be built into Walls that are two layers thick.  They also require road access, employees and sentries from a Recruiter's office.  Don't build the Walls so thick that Tower guards cannot fire over them! @L@LGatehouses @PAs comforting as it would be, you cannot completely encircle your city with Walls.  To let immigrants and merchant trade caravans in, you must have Gatehouses. @PBuild Gatehouses where your major access roads meet your city Walls.  While you are holding the mouse cursor over the desired location, press 'R' to change the direction the Gatehouse is facing.  Once placed, Gatehouses will automatically attach to any adjacent Walls.  If attack is threatened, guards will close the gates to keep out the enemy. @PLike Roadblocks, Gatehouses permit destination walkers free passage but turn roaming walkers back (click @42here for more on walkers). @PFor more information, consult the entry on @52war. @L@LCities were well defended in Ancient Egypt. Click @182here to find out more."
        }
    }

    message_building_police_station {
        id: 86,
        
        size [30, 28]
        title {
            text: "Police Station",
        }
        content {
            text: "Constables keep crime in check as they patrol your neighborhoods. @PConstables are based in Police Stations, which require both road access and labor. A flag waves on the top of the Police Station when it is up and running. @PA constable's presence in a neighborhood reduces the likelihood that crime will arise there. Should his preventive role fail, the constable will actively combat crime.  If he finds a thief on the street, the constable subdues the ingrate and prevents him from performing his nefarious deed.  Constables are also one of your best weapons against @477tomb&robbers.  @PConstables do their best against other threats like foreign invasions and wild animal attacks.  A single constable, though, is ineffective against a pack of animals or a foreign army.  A constable will fight to the death, but will probably not put down the foe. The only chance constables have of defeating these mighty antagonists is if they are able to work together. Still, defeating an enemy army is the business of the military, and the military also proves to be most effective against a pack of wild animals. @G55 @PTo see which neighborhoods are most likely to produce criminals, use the @18Risks&Overlay.  The Risks Overlay can help you plan the placement of your Police Stations. @PAlthough no citizen would want to live in a neighborhood that was not patrolled by a constable, no one wants to live next door to the Police Station, either. Constables come and go at all hours of the day, and they frequently have unsavory characters in tow. @L@LYou have the right to find out more about ancient Egyptian law by clicking @183here."
        }
    }

    message_company_orders {
        id: 87,
        
        size [30, 28]
        title {
            text: "Company Orders",
        }
        content {
            text: "To station a @37company in the field, or to simply instruct it to move to a new location, click on it and then click on a new location.  The company's standard will appear in the new location, and the company will march towards it, assuming that the soldiers can get there.  Note that the steep, muddy embankment between a flood plain and dry land is impassible except where a road connects the two terrains.   @PYou can issue a company the following orders:  @L@LHold Ground in Tight Formation @LIn tight formation, soldiers stand as close to each other as possible.  Because they have been told to hold ground, they will not leave their position to attack enemies.  They will attack any enemy that comes within their range, though.  The tight formation reduces the amount of ground that the soldiers can defend and makes them an easier target for enemy arrows.  Their shoulder-to-shoulder stance enhances their defensive strength in close combat.   @L@LHold Ground in Loose Formation  @LThis command can only be issued to infantry and archers; it cannot be issued to charioteers.  Soldiers in loose formation spread out to cover more ground while holding their positions.  They will attack if an enemy comes into range.  This formation makes infantry and archers less vulnerable to enemy arrows, but does not offer much protection against enemy infantry attack, as each soldier in the line can effectively only defend himself.   @L@LEngage Nearby Enemies @LWhen given this order, a company moves to attack enemies in their immediate vicinity.  The attack continues until the enemy is killed or retreats, or until you issue a different order...or until your own defeated company's morale breaks and your men head back to their Fort. @L@LMop-Up   @LWhen told to mop-up, soldiers seek out any enemies in a wide area and attack them.  Companies under mop-up orders are at their most aggressive, and they break formation entirely to fearlessly battle the foe.  Fearlessness, however, does hamper their ability to defend themselves, so this order is best used when the city's army outnumbers its enemies.   @L@LCharge  @LThe charge command can be issued only to charioteers.  Charging an enemy line breaks up its formation, making the enemy more vulnerable to attack.  When told to charge, the charioteers work the horses up into a lather, and they pull the chariots at top speed for a great distance.  Eventually, the horses tire and the chariots slow down and need to rest, so issue this order sparingly.   @L@LReturn to Fort   @LClick Return to Fort when your soldiers have done their duty and defeated the enemy.  At the Fort, they can rest up for the next battle.   If morale is low, they'll return to Fort on their own.  @L@LIn addition to issuing the specific orders outlined above, you can also tell companies to attack by selecting them and clicking on an enemy.  The company will pursue the targeted enemy to the death unless you issue a different order. @L@LFor more on ancient Egyptian warfare, click @184here."
        }
    }

    message_building_recruiter_academy {
        id: 88,
        
        size [30, 28]
        title {
            text: "Recruiter and Academy",
        }
        content {
            text: "Men willing to fight for their city go to the Recruiter's office to enlist. For additional training, they can proceed to the Academy. Both the Recruiter's office and the Academy need road access and labor.   @PThe Recruiter's function is very simple: he enrolls men into your city's @37army and provides them with any special weaponry they might need.  To equip would-be infantrymen, the Recruiter needs a store of weapons, either imported from a @47trade&partner or made by a @98Weaponsmith.  To enlist charioteers, the Recruiter needs chariots from a @98Chariot&Maker or from a trade partner.  Men who dream of being archers supply their own bows and arrows.  The Recruiter also assigns enlistees to sentry duty on the city's Walls and in the city's @85Towers, as needed. @PNew soldiers leave the Recruiter with dreams of glory and needed weaponry, but with little else.  The Academy trains  these green infantrymen, archers and charioteers in the finer arts of warfare.  Sentries learn their skills on the job and do not attend the Academy.  Once they have completed their studies, the soldiers proceed to their companies' Forts. @PIf there is no Academy in the city, then soldiers go directly from the Recruiter's office to the company Fort. @G57 @PBecause of the rough-and-tumble characters associated with the military, the Recruiter and the Academy have a negative effect on @56desirability. @L@LFind out more about war in ancient Egypt by clicking @184here."
        }
    }

    message_building_grain_farm {
        id: 89,
        
        size [30, 28]
        title {
            text: "Grain Farm",
        }
        content {
            text: "Grain is no different from any other food in the city, but Grain Farms do produce a raw material as a byproduct: straw. Straw serves as fodder for the cattle in @360Cattle&Ranches and is one of the raw materials required for @364brick manufacture. Straw (along with game meat) is also used as a fodder for animals in the @479Zoo.  @PStraw is harvested at the same time as grain.  A delivery person takes it directly to Cattle Ranches, Brick Makers, Zoos or @4Storage&Yards at the same time as his co-worker wheels the grain harvest to its destination Granary or Storage Yard. @PGrain Farms are undesirable neighbors and will lower the value of any nearby housing. @POther topics that may be useful include @45Food&and&Farming, @2Bazaars and @3Granaries. @L@LClick @185here to read about grain in ancient Egypt."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,
        
        size [30, 28]
        title {
            text: "Fruit and Vegetable Farms",
        }
        content {
            text: "Fruits and vegetables are just as capable of sustaining healthy lives as any other food type and provide welcome variety in any diet. Different parts of Egypt support different crops. Among the crops that may be available to your citizens are pomegranates, figs, chickpeas and lettuce. @PFruit and vegetable farms operate like all other food farms.  They do not grow any produce except food.  Please refer to @45farming for complete advice on planning your farms to achieve the most benefit. @PBoth types of farm require labor and road access to produce crops. For farms on the flood plain, this labor comes from @8Work&Camps, so be sure to establish one or more Work Camps near your farms. @L@LEgyptians ate a variety of foods and enjoyed a flavorful cuisine. Click @187here for more on the Egyptian menu."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,
        
        size [30, 28]
        title {
            text: "Barley, Flax and Henna Farms",
        }
        content {
            text: "Barley, Flax and Henna Farms are a little different from @89grain, @90fruit, and @90vegetable&farms. Barley, Flax and Henna Farms do not produce food, but rather raw materials that are manufactured into valuable products.  Barley is harvested and made into @96beer, flax is woven into @60linen, and henna is crushed and mixed with liquid to make @470paint. @PBarley, Flax and Henna Farms are built and operated just like other farms, though. They can be placed anywhere on the flood plain. Off the flood plain, they must be placed on arable meadows, identified by yellow tufts of vegetation.  You'll know you've chosen a good spot when you see a green 'ghost' of the farm before you place it. Farms must be adjacent to a road and need labor. Floodplain farms do not procure labor directly, but rely on peasants from the @8Work&Camps. Read the @45farming section before you plan your farms.   @POnce barley, flax and henna are harvested, the crops are taken to the nearest manufacturer (Brewery in the case of barley, Weaver in the case of flax, Paint Maker in the case of henna). At the manufacturers, the barley, flax or henna is manufactured into a final product that will be distributed to your citizens, used at the @363Artisans'&Guild or @47traded for profit. If there is no room at the manufacturers, or if none exist in the city, barley, flax and henna are taken to a @4Storage&Yard.  @PAll three farms have a negative impact on the @56desirability of nearby land. @L@LFor more on the history of barley farming, click @185here.  To find out about flax harvesting in ancient Egypt, click @189here.  To find out more about henna plants, click @469here."
        }
    }

    message_building_clay_pit {
        id: 92,
        
        size [30, 28]
        title {
            text: "Clay Pit",
        }
        content {
            text: "Clay Pits produce clay that can be molded into @1pottery, combined with @89straw to make @364bricks, or delivered to an @363Artisans'&Guild and converted into plaster. @PClay Pits must have access to the road and to a supply of labor.  They can only be located near the water. @POnce Clay Pit workers dig up enough clay to fill a cart, the Clay Pit sends a delivery man to take the goods to whomever needs it. The delivery man always tries to take clay to a Brickworks, Potter or Artisans' Guild that needs the supply, favoring the nearest building. If none of these industries need the raw material, the delivery man takes the clay to the nearest @4Storage&Yard that can accept it. If no one can accept the clay, the delivery waits until space opens up. @PClay Pits are dank, ugly holes dug into the earth, and your discriminating citizens will not want to live near such an unsightly facility. @L@LThe ancient Egyptians made very good use of the rich clay and mud deposits left behind as a result of the Nile's yearly inundation.  Click @190here to find out more about this valued commodity."
        }
    }

    message_building_gold_copper_mine {
        id: 93,
        
        size [30, 28]
        title {
            text: "Gold and Copper Mines",
        }
        content {
            text: "Gold and copper are valuable metals. A city with metal ore in its area is truly lucky.  If you see rocks with shiny metallic patches, click the Industrial Structures button on the Control Panel, then choose Raw Materials to learn whether your surveyors found gold or copper ore - or both.  @PGold is a rare and precious commodity and should be mined whenever you have the opportunity to do so. Gold is @48money, and Gold Mines afford the city the opportunity to make its own. Unlike other commodities, gold is never delivered to the @4Storage&Yards. Gold can only go directly to the @77Palace, which turns it into debens and adds them to your city's treasury. @G54 @L@LCopper @LCopper is almost as valuable as gold, although it is used more conventionally. Copper is one of the few raw materials you can export for serious profit.  @PIn unsettled times, copper is extremely valuable as a resource for @98weapons, which can command a very dear price. Often your own city will need weapons to equip its infantry. Click @52here to read about war. @L@LMetal mines must be built adjacent to rocky outcroppings that bear metallic nuggets. Both mines need road access and labor, and both are among the most undesirable neighbors a city can have. @L@LThe ancient Egyptians valued gold and underwent arduous processes to extract the metal from the earth.  Click @191here to find out more about gold and its uses in ancient Egypt."
        }
    }
    
    message_building_woodcutter_and_reed_gatherer {
        id: 94,
        
        size [30, 28]
        title { text: "Wood Cutter and Reed Gatherer" }
        content {
            text: "Wood Cutters and Reed Gatherers harvest available raw materials to be used in other industries. Wood has a variety of uses.  Carpenters need wood to build ramps or scaffolds for monuments, Chariot Makers fashion their deadly vehicles from wood, and Shipwrights turn wood into warships and transports.  Reeds are used to manufacture @97papyrus.  @PWood Cutters can be located anywhere, but should ideally be near the woods to reduce the amount of time they spend commuting. Wood Cutters must have access to both the road and to local labor. Once the building is fully operational, wood cutters make their way to the forest and begin cutting down trees. @G58 @PReed Gatherers operate very similarly to Wood Cutters. Reed Gatherers should be located near a field of reeds, although you can build them anywhere. Reed fields are a very dark green with lighter green and yellow tufts. Like Wood Cutters, Reed Gatherers need road access and labor to operate. Once they have everything they need, reed gatherers venture into the marshes. @PBe careful when you are planning your Wood Cutters and Reed Gatherers. Wood and reeds gradually grow back, but both can be over-harvested. If you build too many Wood Cutters or Reed Gatherers, you run the risk of depleting the resource. Your harvesting industries will grind to a halt until the trees and reeds have a chance to grow back. @PWood is one of the most valuable commodities in Egypt.  Try not to destroy forests by clearing land - the city will be out a large source of income if you do.  Marshes cannot be cleared, and some healers associate them with malaria.   @L@LClick @192here to find out more about the importance of wood in ancient Egypt.  Click @188here to discover the many uses for reeds."
        }
    }

    message_building_stone_quarries {
        id: 95,
        
        size [30, 28]
        title {
            text: "Stone Quarries",
        }
        content {
            text: "Quarrymen chisel large blocks of rock at four different kinds of quarry: @L@PPlain stone Quarry @PLimestone Quarry @PGranite Quarry @PSandstone Quarry @L@LIf there are extensive rocky outcroppings in the city's area, you can probably build quarries to extract the rock.  Some areas, though, have rock that's not of construction grade, or have too little rock to support industry.  In such areas, rock is just a nuisance, because it cannot be cleared, traversed or built upon.  Click on the Industrial Structures button and check the list of raw materials available.  This list shows you what types of stone, if any, can be quarried in the area. @PYou must build quarries adjacent to rocky outcroppings.  When you pick an appropriate location, you will see a green ghost of the quarry you're trying to place.  Otherwise, you will see a red block. @PStone cannot be manufactured into other products.  Stone is, however, the stuff of monuments, and significant amounts of stone are needed to complete even some of the smaller monuments. @PQuarries, which are dug into the side of rocky outcroppings, are prone to collapse.  Be sure to build an @81Architect's&post near the quarries to prevent disaster. @PQuarries need a staff of workers and road access to operate. Because of the noise from the constant banging on the rock, quarries are undesirable neighbors.  @L@LQuarrying in ancient Egypt was a very time-consuming task. To find out more, click @193here."
        }
    }

    message_building_brewery {
        id: 96,
        
        size [30, 28]
        title {
            text: "Brewery",
        }
        content {
            text: "To begin the brewing process, Breweries must have road access, labor and a supply of barley. @91Barley&Farms produce needed barley, or it can be imported from a @47trade&partner. One Barley Farm can typically supply enough barley for two Breweries. Breweries can store some barley on the premises to keep themselves working between harvests. @POnce the brewers have all the needed supplies, they brew beer. You can tell if a brewer is hard at work if you see the brewer and his staff in the Brewery. Once the brewing process is complete, delivery men first try to take the beer to a @74Senet&House. If no Senet House needs the beer, delivery men take it to a @4Storage&Yard, where it can be picked up by @2Bazaar&buyers for distribution to your citizens or @47traded for a tidy profit. Beer is one product your citizens require before they build up their homes into more @56attractive&dwellings.  @PBeer is also served at @51grand&festivals.  @L@LTo read more about beer in ancient Egypt, click @194here."
        }
    }

    message_building_papyrus_maker {
        id: 97,
        
        size [30, 28]
        title {
            text: "Papyrus Maker",
        }
        content {
            text: "Papyrus Makers need labor, access to a road, and a supply of @94reeds from a Reed Gatherer or a @47trade&partner.  Papyrus makers can store a supply of reeds on the premises to keep themselves working between deliveries. @PWhen a cartload of papyrus is ready, a delivery man brings it to a @68Scribal&School or @70Library that needs it. If no education structures need papyrus, the delivery man brings the supplies to the @4Storage&Yard where it can be @47traded for profit. @G69 @PCitizens won't like living near a Papyrus Maker. The constant pounding gives them a headache. @L@LTo learn more about the manufacture of papyrus in ancient Egypt, click @195here."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,
        
        size [30, 28]
        title {
            text: "Weaponsmith and Chariot Maker",
        }
        content {
            text: "Weaponsmiths and Chariot Makers produce implements of war needed by certain military companies.  @PUsing copper from a @93Copper&Mine or imported from a @47trade&partner, the Weaponsmith fashions weapons.  Completed weapons are taken to a @88Recruiter, who uses them to equip @37Infantry companies, or to a @45Storage&Yard if your Recruiter already has enough on hand or if your city has no working Recruiter. @PThe Chariot Maker uses wood from a @94Wood&Cutter or @47trade&partner to manufacture magnificent war chariots.  He sends the finished product to the Recruiter to outfit @37charioteers.  If the Recruiter already has some chariots in his inventory, or if your city has no working Recruiter, the chariots are taken to a Storage Yard. @PBoth Weaponsmiths and Chariot Makers need road access and a source of labor. They make @56undesirable neighbors. @L@LLearn more about weaponry in ancient Egypt by clicking @196here."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,
        
        size [30, 28]
        title {
            text: "Jeweler and Luxury Goods",
        }
        content {
            text: "With a supply of @361gemstones, Jewelers make fine pieces of jewelry, a luxury good. Gemstones may either be mined or imported from a @47trade&partner.  @PJewelers need road access and labor in order to operate. They have a negative effect on @56desirability.  @PJewelery is not a very lucrative export. Most of the cost of imported luxury goods lies in its transportation, not in its materials.  So, while it might cost your treasury quite a lot to import luxuries from other cities, you will not receive a comparable price for your jewelry exports. @PJewelry is but one of the luxury goods that citizens crave. The wealthiest citizens will demand a second, imported luxury good. @L@LAncient Egypt is renowned for its splendid @382jewelry. To read more about other luxury goods in ancient Egypt, click @197here."
        }
    }

    message_population_milestone_100 {
        id: 100,
        
        size [30, 20]
        title { text: "Population milestone" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "100 people have moved into your village." }
    }

    message_population_milestone_500 {
        id: 101,
        
        size [30, 20]
        title { text: "Population milestone" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "Your budding town now houses five hundred residents." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,
        
        size [30, 20]
        title { text: "Population milestone" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "One thousand people now call your city home." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@17" }
        content { text: "With two thousand residents, your city is growing in importance." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@17" }
        content { text: "Your city's population has reached three thousand for the first time in history." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@18" }
        content { text: "Your city is getting quite large.  Now five thousand people live here." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@18" }
        content { text: "Its population of ten thousand places your city in Egypt's top tier." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@18" }
        content { text: "Few cities can rival yours, which now houses fifteen thousand citizens." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@19" }
        content { text: "Other governors and nomarchs are awed that your city houses twenty thousand people!" }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Population milestone" }
        video { text: "@19" }
        content { text: "The few immigrants who founded your city so many years ago never imagined that it would swell to twenty five thousand people!" }
    }

    message_the_control_panel {
        id: 110,
        
        size [30, 20]
        title { text: "The Control Panel"  }
        content {
            text: "This panel accesses all of the controls that you need to build and maintain your city.  The best way to understand its functions is simply to click on its various buttons - go ahead, you can't hurt anything!  If Mouse Help is turned ON (under 'Help' on the Menu Bar), put your cursor over any element for a short description of it.  For detailed explanations of every topic in Pharaoh, use the 'Help' item on the Menu Bar."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        urgent: 1,
        title { text: "Fire in the city" }
        content {
            text: "Flames are sweeping through parts of the city.  Click on 'Overlays: Risks' to see where fire could erupt next, and build Firehouses near the structures at risk."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1
        
        size [30, 20]
        urgent: 1
        title { text: "Collapsed building" }
        content {
            text: "Without adequate maintenence provided by architects, certain large structures in your city will collapse.  Click on 'Overlays: Risks' to see which buildings are in danger of collapsing, and build Architect's Posts nearby."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,
        
        size [30, 20]
        title { text: "Ship aground" }
        content { text: "Some inexperienced captains learn about flood plains the hard way, when their ships run aground." }
    }

    message_out_of_money {
        id: 115,
        
        size [30, 20]
        title { text: "Out of money!" }
        content { text: "Your treasury ran out of debens.  You are hereby granted additional funds, but no benefactor will rescue you again.  Use this gift to create money-making enterprises." }
    }

    message_debt_again {
        id: 116,
        
        size [30, 20]
        title { text: "Debt!" }
        content { text: "Your treasury bleeds money.  You can spend up to 5,000 debens' worth of credit, but @48debt can lead to the downfall of your family unless you repay it quickly." }
    }

    message_out_of_money_again {
        id: 117,
        
        size [30, 20]
        title { text: "Out of money!" }
        content { text: "City vaults have run dry, O Pharaoh.  Your loyal nomarchs donated all the debens they could spare, but they cannot afford to do so again." }
    }

    message_wrath_of_the_emperor {
        id: 118,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Wrath of the Emperor" }
        video { text: "@12" }
    }

    message_attack_called_off {
        id: 120,
        type: 2,
        
        size [30, 20]
        title { text: "Attack called off" }
        content {
            text: "New orders just arrived.  They say that you have regained some respect throughout Egypt, and your destruction is no longer necessary.  I bid you farewell...for now. "
        }
    }
    message_debt_anniversary {
        id: 121,
        
        size [30, 20]
        urgent: 1,
        title { text: "Debt anniversary" }
        content {
            text: "Your treasury still holds nary a deben. Each consecutive year of debt damages your reputation, and thus your @35Kingdom&rating. Perhaps you should review your knowledge of @48money."
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
        title { text: "Pharaoh request goods" }
        content { text: "" }
    }

    message_wrath_of_bast_3 {
        id: 134,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Bast" }
        video { text: "@20" }
        content { text: "Woe unto you!  Bast is appalled at your indifference.  To show that you can not preserve your city's health without worshipping her, she has filled the river with blood, poisoning the water supply. Just hope your citizens can hold on until the water is pure again." }
    }

    message_city_unemployment {
        id: 135,
        type: 2,
        
        size [30, 20]
        title { text: "City unemployment" }
        content { text: "There are too few jobs to employ everyone.  Unless new jobs are created, the unemployed may turn in desperation to crime, or even seek their fortunes elsewhere in the Kingdom." }
    }

    message_employees_needed {
        id: 136,
        
        size [30, 20]
        title { text: "Employees needed" }
        content { text: "Too few people of working age are available to fill the city's jobs. Unless you find new workers quickly, city services will deteriorate and industrial production will suffer." }
    }

    message_common_festival {
        id: 137,
        
        size [30, 20]
        title { text: "Common festival" }
        content { text: "Everyone appreciates getting out of work early to relax for awhile at the Festival Square, and your chosen god notices your kind gesture." }
    }

    message_lavish_festival {
        id: 138,
        
        size [30, 20]
        title { text: "Lavish festival" }
        content { text: "The day-long festival is starting. People all over the city are heading for the Festival Square now, and seem to be in good spirits. Your chosen god appreciates your dedication." }
    }

    message_grand_festival {
        id: 139,
        
        size [30, 20]
        title { text: "Grand festival" }
        content { text: "The much-anticipated two-day festival is under way at last! Everyone's converging on the Festival Square for free beer and wild entertainment. The god honored by this event is surely smiling upon you." }
    }

    message_wrath_of_osiris {
        id: 140
        type: 2
        
        size [30, 20]
        title { text: "Wrath of Osiris" }
        video { text: "@24" }
        content { text: "Osiris resents this city's appalling lack of dedication.  Unless you appease him quickly, the next flood will be much worse than expected...it may not even come at all!" }
    }

    message_wrath_of_ptah {
        id: 141
        type: 2
        
        size [30, 20]
        title { text: "Wrath of Ptah" }
        video { text: "@22" }
        content { text: "You have incurred the anger of Ptah! Your city currently has no industries to punish, but mind this god carefully when you start mining, manufacturing or quarrying." }
    }
    
    message_wrath_of_ptah_2 {
        id: 142
        type: 2
        
        size [30, 20]
        title { text: "Wrath of Ptah" }
        video { text: "@22" }
        content { text: "Ptah takes offense at your pride in believing that your city can be industrious without paying him respect. He destroyed some industrial buildings as a reminder to you." }
    }

    message_wrath_of_seth_noeffect {
        id: 143
        type: 2
        
        size [30, 20]
        title { text: "Wrath of Seth" }
        video { text: "@21" }
        content { text: "Your city escaped the anger of Seth by having no military assets for the god to destroy. Be wary, nonetheless, of provoking the God of Destruction, for his anger takes many forms and his memory is long." }
    }

    message_wrath_of_bast {
        id: 144,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Bast" }
        video { text: "@20" }
        content { text: "Terrible news!  Because your city neglects to show her the honor she is due, Bast, Goddess of the Home, leveled some of its best houses!" }
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
        title { text: "Wrath of Osiris" }
        video { text: "@24" }
        content { text: "Unhappy day!  Angered by your refusal to pay him the proper respect, Osiris sends a plague of locusts to devour your crops." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Ptah" }
        video { text: "@22" }
        content {
            text: "Ptah is indignant that you refuse to worship him.  He calls upon a plague of frogs to descend upon the city. These frogs, with their slimy skin and putrid stench, will force many from their homes."
        }
    }

    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2
        
        size [30, 20]
        title { text: "Wrath of Seth" }
        video { text: "@21" }
        content { text: "Furious that you refuse to pay him homage, Seth invokes a hailstorm to rain down upon the city, striking and killing anyone who happens to be in the way!" }
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
        title { text: "Industry" }
        subtitle { text: "History" }
        content {
            text: "By the Old Kingdom, manufacture of products had moved out of the domestic setting and into centralized workshops which turned out nearly all the supplies needed for daily life. Each workshop specialized in a particular product and operated very much like a modern assembly line. Each worker was responsible for a particular aspect of the finished product, rather than working on an item from beginning to end. The tools the artisans used in these workshops were the property of the state, as were any materials the workshops produced. Craftsmen earned wages, usually paid in food and necessary goods. @L@LEgyptian industry thrived and produced many products. Egyptians could find employment as @198potters, @398weavers, jewelers, tanners, @389carpenters and smelters as well as bakers and @194brewers."
        }
    }
    message_housing {
        id: 152,
        
        size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Housing" }
        subtitle { text: "History" }
        content {
            text: "Egyptians made their homes from brick, wood, mud or occasionally stone. Housing style and size depended upon the wealth of the citizen and where he lived. Thus, rural citizens who farmed for a living resided in simple brick or pressed mud structures of two to four rooms. City homes of the working class were likewise small, and some two-story, two-family homes were built to save space in the most crowded cities. City-dwelling workers lived in brick homes of 3-7 rooms. @L@LWealthier citizens had larger homes, and some of these were quite spacious. Senior government officials sometimes had homes of 60-70 rooms, with high ceilings supported by wooden columns, reception rooms for entertaining guests, plenty of storage space and servants quarters. The most luxurious homes of all were the @175Pharaoh's&palaces.  @L@LFor the most part, Egyptian cities grew organically in whichever direction they could. A few cities, however, were planned, most notably the settlement built for workers at Deir el-Medina. @L@LMost Egyptian cities were surrounded by walls. For more on defensive structures, click @182here."
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
            text: "Roads",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The @157Nile was Egypt's main highway. Boats of all shapes and sizes tranported people, goods and materials from one point to another. The ancient Egyptians, of course, had land-based roads as well. These roads generally were not paved in any fashion, but were simply well-worn paths. In most cities, roads twisted and turned in any way necessary. In planned cities, such as the settlement for workers at Deir el-Medina, the roads were laid out in a neat grid. @L@LSome trade routes were also well-established, but these roads weren't paved, either - and they could be quite dangerous to traverse. For more on the perils of successful trade, click @177here."
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
            text: "Irrigation",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Egyptians increased the amount of arable land through irrigation. Egyptians began to build a network of irrigation canals and ditches as early as the ninth dynasty, or about 2000 BC. Some canals seem to have existed before then, but they were used for transportation. The irrigation canals extended the benefits of the river, bringing nourishing silt to areas away from the river. @L@LEarly in Egyptian history, farmers who wanted to irrigate their land had a tough time of it. Farmers irrigated their land by hand, carrying a yoke with two buckets made of clay or leather to the Nile or some other water source. The farmer returned with his buckets of water to his farm, which was subdivided by small dykes. The dykes captured the water, maximizing the benefit of this slow and arduous method of irrigation.  @L@LAt the end of the 18th dynasty (about 1300 BC), the water lift, or shaduf, was introduced. The shaduf probably came to Egypt from Mesopotamia, where it had been in use as early as 2370 BC. Positioned on the bank of the Nile or other water source, the shaduf was made from a long wooden beam that rocked back and forth on a pivot. A bucket at one end of the beam was counterbalanced with a brick or other weight. A person pushed down on the end with the bucket to dip it into the water, and the brick helped the worker lift the water into the gully that was attached to the shaduf. @L@LThe introduction of the shaduf increased the arable land in Egypt by about 15 percent. Also, because it was never submerged under water, land irrigated by the shaduf could produce two harvests a year instead of one."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2
        
        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Labor" }
        subtitle { text: "History" }
        content { text: "Peasants performed most of the hardest labor in ancient Egypt. Peasants tilled the soil and harvested the crops during the growing season. During the Inundation, these same workers were conscripted to do work for the state. Mostly, they worked to build pyramids and other structures, but these workers could also be tasked with maintaining the Egyptian infrastructure, like @153roads and @154Irrigation&Ditches. @L@LWhile the work the peasants performed wasn't easy, they weren't completely abused. The typical workday lasted eight hours with a break at lunch. The work week lasted eight days, with two days off at the end. In addition to these 'weekends,' work stopped for festivals. Workers could also take time off if there was sickness or death in the family. @L@LAttendance was very well documented, as were the reasons for missing work. Some reasons for missing work probably wouldn't be acceptable excuses today. One employee missed work to go drinking with a buddy. @L@LDespite what many people think, slave labor was seldom used on state construction projects. Sometimes, slaves were used in quarries, but for the most part they served in households. @L@LIf workers were not treated well, they could go on strike.  During Ramses III's reign, about 1152 BC, workers at Deir el-Medina formally stopped work to protest the delay of their compensation.  Their strike was successful, and the problem of late compensation was rectified." }
    }
    message_clean_water {
        id: 156
        
        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Well and Water Supply", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Getting drinking water to the populace was a bit of a challenge in ancient Egypt. The main water source was the Nile and the Nile's water table. Away from the Nile, there were a few oases, but most of the land was arid. @L@LTo get water to neighborhoods, cisterns were built in well-to-do houses. Water carriers brought buckets full of water to these houses, and emptied them into the cisterns. @L@LThe Egyptians were adept at digging wells. Workers had to dig through 300 feet of rock for one well near the worker's settlement at Giza. Most wells had a well house capping them. From the well house, stairs wound down to the water's level. From there, people could fill their jugs with water."
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
            text: "Nile",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egyptian civilization simply would not exist without the Nile. In a region where rain is scarce, the Nile provides a reliable source of water to both the people and the land. By flooding its banks on a relatively predictable basis, the Nile also refertilizes farmland. @L@LThe importance of the Nile was not lost on the ancient Egyptians. Watching the Nile continuously bring the land back to life contributed volumes to Egyptian religious customs, particularly their belief in an afterlife.  @L@LThe Egyptian calendar was divided into seasons named for the different stages of the Nile. The Inundation, when the Nile was flooding its banks, was called akhet. The Inundation occurred because of yearly monsoons at the source of the Blue Nile on the Ethiopian plateaus. The Emergence, or proyet, marked the time when the Nile receded and the land began to emerge. Harvest time was called shomu, sometimes translated as drought."
        }
    }
    message_dentistry {
        id: 158,
        
        size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Dentistry" }
        subtitle { text: "History" }
        content {
            text: "Dentistry was one of many fields that an ancient Egyptain doctor could practice. Remains of ancient Egyptians indicate that dentists were fighting an uphill battle. Tooth decay was promoted by omnipresent sand. Sand worked its way into everything, including food, and constantly crunching on sand quickly wore down the Egyptians' teeth. Tooth wear often lead to abscesses, which could cause the tooth to fall out and could even cause death. @L@LMedical papyri detail the actions dentists took to treat specific problems. For example, if a tooth fell out, the dentist bound the tooth to a neighboring tooth with gold or silver wire. There is even a recipe for fillings, involving mixing resin and malachite, but archaeologists have found no remains of teeth with the fillings still intact. @L@LArcheologists have uncovered tools that they believe were used as toothbrushes. Thus far, no discoveries of ancient Egyptian floss have been reported."
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
            text: "Apothecary",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ancient Egyptian medicinal and pharmaceutical practices are well-documented. Religion was instrumental in curing disease, and most prescribed cures were accompanied by prayers or spells. Medical papyri outlined specific cures, some of which seem a bit unusual by our standards. To cure indigestion, for instance, a hog's tooth was crushed and placed inside of four sugar cakes. The patient was to eat one of these cakes per day, after which time the indigestion should be cured. A cure for baldness called for a mixture of a rook's vertebra, a burnt donkey's hoof and the lard of a black snake."
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
            text: "Medicine",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Like other parts of Egyptian society, the medical profession was highly segmented and bureaucratic. The profession was organized along hierarchical lines, with doctors holding titles such as senior doctor, inspector, overseer and master of physicians. The highest ranking doctor was the 'Chief of Physicians of the South and North.' @L@LDoctors gained their medical knowledge through studying the internal organs of animals and texts, not through observing the embalming process. Medicine was distinctly separate from the funerary rites. @L@LGood health was anchored in the concept of metu. The heart was the center of the body, and all parts of the body were linked to the heart by metu, or channels. More than a description of the circulatory system, all systems of the body were considered to be metu. Illness occurred when some part of the metu was blocked. @L@LTo cure illnesses, doctors prescribed medicine combined with prayer. For more on Egyptian pharmaceutical practices, see @159apothecaries. @L@LEgyptians suffered from polio, small pox, tuberculosis of the spine and malaria, among other maladies. The Egyptians were also prone to illness caused by parasitic worms."
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
            text: "Embalmers",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Embalming is the cornerstone of ancient Egyptian funerary customs. The ka, or spirit, of the deceased needed a place to live in the afterlife and, thus, needed its body. During the embalming process, the body was first rinsed in the waters of the Nile, symbolizing rebirth. Then, internal organs were removed from the corpse and stored in containers called canopic jars. The only organ that was discarded was the brain (which was removed through the nose) because the ancient Egyptians believed that it served no purpose. The canopic jars were entombed with the body. @L@LAfter removing the internal organs, the embalmer filled the body cavity with perfumes, oils, and linen and closed the body up. Then, the body was covered in natron, a type of salt. After 70 days, the body was rinsed off, wrapped in linen and smeared with tar. The tar helped to kill bacteria and fungi that would otherwise work to decompose the body. @L@LBecause of the expense of the embalming process, only the wealthiest citizens were able to afford it."
        }
    }
    message_shrine_and_temple {
        id: 162,
        
        size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Shrine and Temple", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Temples were viewed as the residences of the gods, and each temple had scores of attending @384priests to care for the god. Citizens took part in the care of the gods through offerings, but they rarely saw the statue of the god hidden deep inside the temple. Only on feast days, when the god was carried through town on a ceremonial bark, did citizens actually catch a glimpse of the deity. @L@LEgyptians turned to the gods for advice. Everyone was welcome into the forecourt of the temple, and here people could query the gods regarding subjects that puzzled them or ask forgiveness for past wrongs. The priests, hidden from view, responded to the beseechers. Citizens could also ask questions of the god on feast days when the god was out and about. @L@LIn addition to paying homage at the temples, most Egyptians had shrines in their homes. Frequently, the shrine was of Bes, the protector god of the household. Individuals seem to have had their own patron gods as well. In an attendance record uncovered at Deir el-Medina, workers are sometimes absent to celebrate the 'festival of their god.' @L@LThe concept of a patron god extended to cities, towns and regions. That idea caused shifts in the gods worshipped at different periods during Egyptian history. For more on the evolution of religion, click @399here."
        }
    }
    message_school_and_eduction {
        id: 163,
        
        size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "School and Education", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Education in ancient Egypt was extremely practical. Each person was educated with a specific career in mind. For many, education meant apprenticeship, and sons were generally apprenticed to their fathers to learn a craft. Some girls, too, were apprenticed to pursue careers as dancers, singers or weavers, but for the most part girls learned the art of managing a household. @L@LScribes received the most formal education. Scribal schools, called Per-Ankh or 'house of life,' were connected primarily to temples. Here, would-be scribes learned the written languages, primarily hieratic and, later, demotic, which were used for everyday business. The scribes learned their craft by copying over manuscripts onto ostraca, or old shards of stone. Only when they had mastered their craft were they entrusted with papyrus. Discipline was demanded, and physical punishment frequent. Scribal education generally occurred between the ages of 10 and 20."
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
            text: "Library and Literature",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Armed with a written language, the Eygptians recorded many of their stories, poems and hymns. These texts were stored in libraries associated with the Per-Ankh (house of life), or @163Scribal&School, which was adjacent to the Temple.  @L@LEgyptian literature sprang from an oral tradition, and for the most part literature was recorded as a reminder to the storyteller. Most Egyptians were illiterate, and many @387scribes were storytellers who used the written record to help them remember the stories, hymns and poems. Those who knew how to read, particularly those associated with the pharaoh's court, could gain access to the libraries and read papyri for themselves.  Some wealthy citizens had their own libraries. @L@LAncient Egyptian literature could be divided into several different genres, including autobiography, adventure tales, folktales, mythology, lament, poetry, and hymns, among others. Of these forms, autobiography was the oldest and came from the tradition of engraving a person's accomplishments on his tomb.  Satire was also popular."
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
            text: "Entertainment",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The ancient Egyptians could choose from a variety of leisure activites. Sports were common, especially water sports like rowing and swimming (the wealthiest enjoyed this sport from the privacy of their own swimming pools). The Egyptians are also the first known culture to engage in fishing as a leisure activity. @L@PBoxing was a popular spectator sport, with bouts arranged specifically for the pharaoh's entertainment. Other sports included handball, a form of field hockey, gymnastics, archery and weightlifting. @L@PFor the educated, reading was a popular diversion, and the first known short story was written in ancient Egypt. Poetry was popular, but there is no evidence of any Egyptian plays. For more on reading, writing and literature, see @164libraries. @L@L@393Festivals were an important part of Egyptian life as well."
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
            text: "Children",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Children were prized in ancient Egypt and viewed as a continuation of life. Early marriage was common to facilitate large broods of children. Lower-class children followed their parents out to the fields and helped in the harvest. Middle- and upper-class children spent their days at home with their mother. When they were old enough, upper-class boys would be sent to school and then apprenticed to their fathers. @L@LEgyptian children had plenty of toys and games at their disposal, including balls, dolls, tops and wooden animals. They played games, like tug of war, and enjoyed many of the same leisure pursuits as their parents, such as swimming and fishing. @L@LChildren and their parents also kept a variety of pets. Dogs and cats were both popular pets, as were trained monkeys, birds, gazelles and, for the extremely wealthy and brave, lions."
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
            text: "Population",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ancient Egypt was like modern society in many ways. Many people lived in urban centers where manufacturing provided many of the jobs. Farmers tended to live in smaller, rural villages. The bulk of the population, naturally, lived near the river. @L@LThe size of Egypt's population grew over time, and its growth is directly linked to @154irrigation. During pre-Dynastic times, the population is thought to have been no larger than about 350,000. By the end of the second millenium BC, however, when irrigation practices had expanded the amount of arable land, the population is presumed to have reached about 3 million."
        }
    }
    message_history_society {
        id: 168,
        
        size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Society", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Egyptian society was highly stratified with distinct and separate classes. For the most part, people remained in the class into which they were born, although there are a few examples of individuals marrying into a higher class. @L@LMembers of the lowest class were peasants. The peasants had the shortest life expectancy of any class and endured a life of hard labor, either on farms or on state construction projects. Their remains show that most peasants had bad back problems, and their vertebrae were sometimes fused together as a result of their hard work. They lived in very basic structures of a few rooms, and they were buried in simple graves and could not afford to be embalmed. @L@LThe middle class was comprised of artisans, merchants, and others involved in industry. They lived in more spacious homes and some of them could afford embalming and modest tombs. @L@LThe wealthiest class were high-ranking government officials. They could afford the finest luxuries, including embalming, and often had fine tombs built. Their diets were richer and more varied than other Egyptians. In an examination of some mummified remains of upper class Egyptians, 10 to 20 percent had arteriosclerosis - hardening of the arteries - indicating the consumption of plenty of animal fat and, perhaps, a life of stress. Wealthy men were often depicted with pot-bellies, an indication of their prosperity."
        }
    }
    message_history_juggling {
        id: 169,
        
        size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Juggling", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "The ancient Egyptians are the earliest known jugglers. On a Middle Kingdom tomb in Menat Khufu (Beni Hasan), paintings depict young women performing a variety of juggling feats, including women on piggy-back tossing balls to each other. @L@LThe significance of juggling in ancient Egypt isn't clear. It may have had some religious significance, or it may have been pure entertainment."
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
            text: "Music",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Egyptians played a variety of instruments, including flutes (which came in many different sizes), harps, lyres, lutes, tambourines and other percussion instruments. Singers were an integral part of Egyptian music, and most of the hymns and poems recorded on papyri were meant to be sung to music. @L@LPercussion instruments were particularly used in accompanying @171dance. Many dancers played castanets as they performed. @L@LThe Egyptians also played trumpets. Trumpets were associated with the military (perhaps the Egyptians had their own form of reveille) and are frequently found in the tombs of kings and military leaders. Two trumpets were found in the tomb of Tutankhamun. To hear what the trumpets sounded like, one of them was played in 1939. After a few notes, the trumpet promptly fell apart. It was restored immediately. The trumpet was also associated with @376Osiris, God of Agriculture and the Nile Flood. @L@LOther instruments also had religious significance. The sistrum, a large rattle-like instrument, was associated with @380Hathor, Goddess of Joy, Love and Festivity. Flutes were associated with @378Amon, God of the Sun."
        }
    }
    message_history_dance {
        id: 171,
        
        size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Dance", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Ancient Egyptian dance evolved from rituals that hunters used to prepare for the hunt. A lead dancer, called the priest-dancer, was responsible for ensuring that the dances were performed correctly. @L@LLater, dance was an integral part of festivals and other religious celebrations but was also a form of entertainment in and of itself. Professional dance troupes performed in city squares and could be hired for private parties. The dancers were usually accompanied by @170music. Most professional dancers were female, and many had tattoos of Bes, God of Music an Dancing, on their thighs.  @L@LSome citizens also danced as a pastime, although this diversion was reserved primarily for the lower classes. The greater an Egyptian's stature, the less likely he or she was to dance. Also, men and women never danced together. Women danced with other women, and men danced with other men. @L@LApparently, Egyptian dance moves were named for what they represented, for example, 'the leading along of an animal,' 'the successful capture of a boat' and 'the funky chicken.'"
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
            text: "Senet",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Senet was the most popular board game in ancient Egypt. The board was rectangular and divided into three rows of 10 squares each. It was played by two players, and each player had at least five pieces. Moves were determined by a set of four throwing sticks. The rules for senet were not recorded anywhere, so no one is quite sure how the game was played. Most historians agree, however, that the game represented the journey to the afterlife. Both backgammon and hopscotch are considered to be descendants of senet. @L@LSenet, along with other games, was probably one of many amusements Egyptians undertook while at taverns or inns. After a hard day's work, many Egyptians would retire to local taverns where @194beer was served and lively conversation filled the air. Both men and women - particularly those that were still single - attended beer halls."
        }
    }
    message_history_taxation_and_money {
        id: 173,
        
        size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Taxation and Money", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "The ancient Egyptians paid tax to their pharaoh, which were paid in commodities. So, for example, a farmer had to pay pharaoh a certain amount of grain. Scribes were sent around to all the farms to determine how much each farmer owed. @L@LValue was sometimes expressed in terms of deben. Deben were metal disks that were likely first used as weights."
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
            text: "Government and Bureaucracy",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Government in ancient Egypt was very bureaucratic. Every imaginable task had an associated government employee with a lofty-sounding title. Heading everything up, of course, was the pharaoh. The pharaoh's right-hand man was his vizier, who was responsible for ensuring that all pharaonic commands were carried out. Under the vizier were nomarchs (regional governors), chancellors, viceroys, overseers, mayors - the list goes on and on. And, because ancient Egypt was a theocracy, @384priests played an integral part. @L@LMany individuals held more than one title. For example, Imhotep, who served under Djoser I and oversaw the building of the Step Pyramid, held the titles of Vizier, High Priest of Ptah and Overseer of Works, among others."
        }
    }
    message_history_pharaohs_home {
        id: 175,
        
        size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "Pharaoh's Home", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "The pharaoh's home was the most majestic dwelling in the city. While most homes had only one or two rooms, some pharaohs' mansions boasted dozens of rooms and were outfitted with the best amenities ancient Egypt could offer. @L@LLike in the @174government, Egyptians in the employ of the pharaoh held titles and were responsible for very specific tasks. Among the people the pharaoh employed were the Superintendent of Household Affairs, the Chief Manicurist and the Royal Butler. @L@LOne royal butler, named Nefer-Peret, had very specific responsibilites accorded to him. Nefer-Peret was responsible for the care of four Palestinian cows, two Egyptian cows, one bull and one bronze bucket. Nothing more, and nothing less."
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
            text: "Gardens and Public Art",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Gardens were extremely popular in ancient Egypt, and most houses had gardens adjacent to them. In addition to growing @187fruits&and&vegetables in these gardens to supplement their diets, the gardens provided a place to go for respite from the hot sun. Many gardens had carefully tended trees to provide shade. @L@LArt was primarily found on the monuments and temples in town. So much time and expense was devoted to the temples and monumnents that the rest of the town tended to be rather drab by comparison."
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
            text: "Trade",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "While ancient Egypt was replete with natural resources, the land did lack some goods. The Egyptians opened trade routes with many nearby countries and regions, including Nubia, Lebanon, Syria, Punt (which historians speculate is the coast of Somalia) and the Aegean, among others. Some sources claim that Egyptian trade extended as far north as modern-day Turkey. @L@LThe Nile again played an important role in Egyptian trade. The river was navigable through the first cataract, or set of rocky waterfalls. It acted as a road and made travel to and from Nubia relatively easy. @L@LThe Nile also helped to provide one of Egypt's main exports: grain. The Inundation proved to be much more reliable than the rain in Lebanon and Syria. As long as the Inundation occurred, Egypt had a surplus of grain, a luxury Lebanon and Syria did not frequently have. Egypt's other exports included linen, papyrus, lentils, dried fish, gold and silver vessels, ox hides and rope. @L@LIn exchange, Egypt received a variety of goods as imports. Among the most important are gold from Nubia, wood from Lebanon and olive oil from Syria. The Egyptians also imported other luxury items, such as myrrh and wine, and livestock. The Egyptians also occasionally imported weapons. @L@LLaden with goods, caravans were especially prone to attack. For protection, armed units accompanied caravans on their trade missions. Because of these armed units, some historians speculate that Egypt did not engage in free trade with its neighbors, but rather bullied neighbors into giving up goods. While coercion probably played some role in Egyptian trade, some papyri also refer to negotiations between Egypt and its trade partners. @L@LSome successful trade missions were celebrated with inscriptions and artwork. Hatshepsut, a female pharaoh, sent a fleet of ships to Punt to procure myrrh, frankincense, ivory and other fine goods. The trip was deemed so successful that it is recorded on the walls of Hatshepsut's temple at Deir el-Bahri."
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
            text: "Ships and Ship Making",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Nile has inspired boat makers for ages. In pre-Dynastic times, ancient Egyptians lashed together reeds of papyrus to make rafts that they propelled with poles. With the advent of pyramid building came the shipwright. Ships were important in transporting heavy materials needed for the construction of the pyramids. @L@LLike other industries in Egypt, shipwrights were government-owned operations. Equipped with woodworking tools, ship builders first made the hull of the boat by laying planks side by side and securing them with dowels, glue, and ropes designed to shrink when wet. When the ropes shrank, the hull was held fast. Hulls of larger boats were ribbed. Once the hull was complete, the shipwrights outfitted the rest of the boat, including a mast for the sail and holes for oars. Some of the larger ships had cabins. @L@LThe ships were broad-beamed and designed to ride very high on the surface of the water, which helped them stay afloat. The Nile, though relatively easy to navigate, did have its share of shoals and shallow points, and it was easy for ships to run aground. @L@LShipwrights built ships of significant size. One boat, used to transport obelisks to Hatshepsut's temple, measured 89 yards (82 meters) in length. One of the most famous archaeological finds is Khufu's barge. Found in about 1,224 pieces along the south side of Khufu's pyramid, the barge was reconstructed in the early 1960s. The boat is over 46 yards (42  meters long and 6.5 yards (6 meters) wide, with spots for 10 rowers plus an additional two that steered the boat. Historians are unsure of the significance of the boat. Some speculate that it is symbolic of Horus' sun ship. Others think that it may have been the barge that transported Khufu's remains to his pyramid, or that he used the boat during life. Regardless, the boat provides insight into the construction of Egyptian ships."
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
            text: "Enemies",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egypt was in frequent contact with its neighbors, and sometimes relations weren't very friendly. Egypt was invaded several times during its long history and ruled by non-Egyptians. These non-Egyptians, though, assumed the title of pharaoh, and up until the time of the Persian invasion, Egptians managed to wrestle back their land. Egypt, though, was not always the one under attack. During the New Kingdom in particular, Egypt sought to expand its empire and invaded many neighboring lands. @L@LAmong the peoples Egypt waged war against are the Nubians and the Kush. Egypt invaded Nubia fairly early in its history (as early as 2900 BC), mostly to take advantage of Nubia's rich gold and copper resources. During the late period, however, Nubia gained the upper hand, and several Nubian pharaohs ruled Egypt. @L@LAcross the Sinai peninsula were several peoples with whom Egypt waged war. Among these are the Canaanites, Philistines, Bedouins (from what is now Syria) and the Hittites. The most notable of these Asiatic peoples, though, are the Hyksos. During the Second Intermediate Period, the Hyksos ruled Egypt. They retained many of Egypt's cultural practices, and introduced many innovations, such as the horse-drawn chariot. The Hyksos ruled Egypt for about 100 years until Ahmose I defeated them and assumed power. @L@LTo the west, Egypt engaged in war with Libyan tribes, particularly the Tehenu and Temehu. The Tehenu and Temehu attempted to move into the Egyptian Delta, and they were put down strongly by Sethos I. @182Forts were built in the west to help keep the tribes at bay.  @L@LFinally, the powerful Roman Empire reached the shores of Egypt during the rule of the Ptolemies.  Egypt's waning military might yet bountiful treasury and granaries (not to mention the beguiling Cleopatra VII) quite naturally attracted the covetous eyes of Julius Caesar and his successors.  The arrival of Caesar's Roman legions on Egyptian soil marked the beginning of the end of a long history of Egyptian dominance in the Mediterranean basin, and eventually reduced the once-proud Egypt to a vassal state. @L@LClick @184here for more on Egypt's military."
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
            text: "Defensive Structures",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egypt protected its cities and towns with walls and towers. Walls were generally made of brick and were built either in the form of a quadrangle or a circle around the town. Excavations at Abu (Elephantine), located in southern Egypt near the Nubian border, have uncovered a thick, curving wall with semi-circular towers interspersed.  @L@LEgypt defended its borders with a series of fortresses. Among the most well known of these fortresses are the 'Wall of the Prince,' a series of 13 fortresses built along the Nile's east bank."
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
            text: "Law",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egyptians with grievances against others could take their complaints to a magistrate. Depending on the seriousness of the offense, the case might be decided by a local magistrate or by the vizier himself. Local magistrates were sometimes lower-ranking officials in the town, like a chief workman. Scribes attended the court cases and recorded participants, witnesses, testimony and punishments. @L@LEveryone was subject to the law, upper and lower classes alike. In one scene engraved on a mastaba chapel of an Old Kingdom vizier, local governors are being punished for withholding tax revenue. Women, too, were active participants in court cases. In one case, a woman is awarded property that had been illegally claimed by her in-laws. In another case, a woman is found guilty of stealing a tool and a vessel from a shrine of Amun. @L@LPunishments for crime could be quite severe and frequently involved beatings or forced labor. During the New Kingdom's 18th dynasty, the punishment for stealing hides was 100 blows and five open wounds. Some particularly heinous crimes were punishable by cutting off the criminal's nose and banishing him or her to the outskirts of Egypt. @L@LEgyptian law was not strictly codified, and most punishments were meted out on a case-by-case basis. There are some lists of crimes and their punishments remaining, particularly from the New Kingdom, but these lists tend to be contradictory. @L@LJustice was an important concept in the afterlife as well. Before a person could enter the afterlife, he or she had to make a 'negative confession,' listing all the things the person hadn't done during his lifetime. After the negative confession, the individual's heart is weighed against a feather from Ma'at's headdress. If the heart weighs the same as the feather, he or she gains admittance into the afterlife. If it is heavier than the feather, the heart is eaten by Ammit, a hideous monster, and the person is denied access to the afterlife."
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
            text: "Military",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Egyptian military evolved over the thousands of years of pharaonic rule. In the Old Kingdom, armies were raised when needed and were usually comprised of nobles and their followers or foreigners. The Old Kingdom had no professional army. The men who served in the army came from different walks of life and presumably returned to their former professions as soon as the fighting was over. @L@LBy the time of the New Kingdom, however, the structure of the army had changed. The army was clearly divided into units of infantry and charioteers. The infantry could be divided into two parts: soldiers who specialized in close combat and those who specialized in longer range combat. Chariots were used for mobile long-range combat. Soldiers with bows and arrows rode each chariot, firing into the enemy. Naval combat was frequent, although the navy was not seen as a separate and distinct division of the armed forces. The navy was a part of the land forces, and soldiers who served on boats were described using the same terms as those that served on land. Again, foreigners comprised a significant portion of the army. Nubians, Libyans, Asiatics and Carians all fought on behalf of the Egyptians. @L@LThe Egyptian army was organized into battalions in the Old Kingdom. During the New Kingdom, the battalions were further subdivided into divisions, which were named after gods. Scribes and administrators would go to battle with the soldiers, presumably to keep track of the action. @L@LClick @196here to find out about the weapons the Egyptian army had at its disposal."
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
            text: "Grain and Barley",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Grain farming (both wheat and barley) produced the raw material for the most basic foodstuff in ancient Egypt: bread. Wheat and barley were both turned into flour, then baked into bread. For more on the use of bread made from barley, see @194Beer. @L@LThe Egyptians used three types of wheat: emmer, einkorn and spelt. Wheat was processed into flour through threshing. Stalks of wheat were placed on the ground, and livestock or other large animals were brought in to stomp on the wheat. This pounding released the grain from the sheaves. Then, the grain was separated from the chaff and other impurities either by sifting or by throwing the wheat up in the air. The wind would carry off the lighter chaff, and the heavier wheat would fall to the ground. After the grain was processed, it was taken to the @5granaries. At the granaries, the wheat would be processed into flour and stored for future use.  @L@LTo make bread, a dough was made from flour and poured into ceramic molds of different shapes. The most popular shape was conical. The dough was baked in a hearth surrounded by hot coals and ash. Bread was baked both in the home and by professionals in bakeries. Archeologists speculate that because of the amount of ash in the air, professional bakers may not have been the healthiest people."
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
            text: "Cattle Ranching and Fishing",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egyptians raised several different animals on ranches or farms to be used for food. The most prevalent of these animals were long-horned cattle. These cattle were tended by herdsmen, who were typically portrayed in tomb scenes as being very lean with unshaven faces. The cattle were sent to pasture to feed. Sometimes, the cattle were sent to fields that had been recently harvested to eat straw and chaff. @L@LThe Egyptians also raised sheep, goats and pigs on farms, as well as geese and other fowl. Horses were also raised, not for food, but to be used to draw the chariots of the noblest Egyptians. The horse was introduced into Egypt by the Hyksos, one of Egypt's @181invaders. @L@LFish provided an alternate source of food, though it seems to have been eaten primarily by the lower classes. The Egyptians caught fish in several different ways. Some set out in canoes and used fishing rods with lines and hooks to catch fish one at a time. Traps were also built to catch larger numbers of fish. The most efficient way to catch fish, however, was the drag net. Because the catch would be so great, bringing a drag net back to the surface required two boats of men. @L@LThere were dangers involved in the fishing profession. One species of catfish had a poisonous spine on its dorsal fin, and there was always the danger of crocodiles. Fishermen were safe enough in their boats, but should the boat capsize, the crocodile was seldom far behind."
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
            text: "Fruits and Vegetables",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "@185Grain and barley were the predominant foodstuffs for the ancient Egyptians, but they also cultivated a variety of fruits and vegetables. Beans, chickpeas, lentils and green peas were very popular, as were garlic, onions, leeks, lettuce and cucumbers. For fruit, figs, dates, grapes and pomegranates were consumed. Dates in particular were popular with the lower classes and were used to flavor beer. The Egyptians also spiced their food with cinnamon, coriander, cumin, dill and mustard."
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
            text: "Reeds",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Reaching heights of up to 25 feet, papyrus reeds weren't used just for paper in Egypt. Payprus reeds were manufactured into a variety of household goods including mats, sandals and rope. The pith of the plant was enjoyed as food. Sometimes, the stem of the plant was used as a replacement for wood, and stalks of the plant would also be bound together and used as a raft. Papyrus reeds nearly became extinct, but has enjoyed a recent resurgence. Papyrus reeds are again being harvested and manufactured into paper - this time to be sold to tourists."
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
            text: "Flax",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Flax was grown to manufacture @398linen, ancient Egypt's major textile. Because the stalk was the most important part of the plant, each plant had to be pulled from the ground rather than cut, making flax harvest a slow process. Once the flax was harvested, the roots and seed heads were removed and the stalks are laid out to dry. Then, the stalks were submerged in water for two weeks, after which they were beaten against stones and separated out into fibers. The fibers were then sent to a weaver to be made into cloth."
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
            text: "Clay",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Clay was easily obtained in ancient Egypt, and the quality of clay varied by region. Along the Nile, years of Inundations resulted in rich deposits of mud waiting to be dug up and molded into pottery. In the desert regions, veins of soft marl and shale could be found in limestone. Clay from the desert yielded harder pottery than clay from the Nile and produced objects that had a pink or green hue. Pottery made from Nile clay tended to be red or black. Both types of clay were processed in the same way to make @198pottery."
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
            text: "Gold and Gold Mining",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Gold was found primarily in Egypt's eastern desert and in Nubia. Mining the gold could be an arduous task. In the eastern desert, for example, veins of gold were interspersed in granite. The granite was chiseled into powder, then submerged in water to separate the gold from the rock. This process was certainly very time consuming. Nevertheless, gold was relatively plentiful and was, in fact, easier to obtain than silver. @L@LTo prepare the gold for use, it was first melted down at the gold mines. Once melted, the gold was poured into water. As the gold cooled, it formed into nuggets, which were then taken to goldsmiths for use. @L@LLike almost every other commodity, gold inventory was strictly maintained by scribes. They carefully weighed out gold every morning to the smiths, and their work was carefully supervised to ensure that they weren't stealing any.  @L@LWhile gold was more plentiful than silver, by no means was there an excessive amount of gold available. As a result, most objects were gold plated instead of being made of solid gold."
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
            text: "Wood and its Uses",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Native trees were not plentiful in Egypt. While the soil on the floodplains would be fertile enough to support tree growth, the flood itself would uproot trees before they had a chance to grow. Trees that did manage to grow in Egypt included the sycamore, the persea tree, the date palm and the horseradish tree. Each of these trees was accorded religious significance and viewed as a dwelling place for the gods. @L@LBecause of their special significance, wood cutters had to receive special permission before cutting trees down. The trees that were cut produced brittle wood that had limited uses. Egypt imported most of its wood from what is now Lebanon, Syria, and Israel. When Egypt eventually conquered these lands during the New Kingdom, they harvested trees with abandon, significantly depleting the tree stock. @L@LWood was used for furniture, coffins and in buildings. Wood workers were quite adept at fashioning intricately designed pieces complete with inlays and engravings."
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
            text: "Quarries",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Egyptians quarried several types of rock for their pyramids, temples and monuments, including limestone, granite, sandstone, basalt, slate, alabaster and porphyry. Quarrymen were equipped with pick axes and chisels to extract hard rock, and copper saws to extract softer rock. @L@LMost quarries operated only during the Inundation when state construction projects were at their peak. Some quarries operated year-round, especially if a large construction project, like a pyramid, was underway. @L@LTo transport the blocks to their final destination, the blocks were placed on a sled and dragged by a team of workmen. Logs were frequently laid down to act as rollers, facilitating the process. Sometimes, water was poured in front of the sled to ease friction. @L@LSlaves made up some of the labor force at quarries, although Egyptians still made up the bulk of the labor force."
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
            text: "Beer",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Beer was the beverage of choice for ancient Egyptians. Debate rages over the particulars of the Egyptian beer industry. How was the beer brewed?  Was the beer flavored with fruit?  Did they make barley or grain beers?  And what about malting?  Research is underway to answer all of these questions. @L@LBased on pictures found on tomb walls, one beer-making method the Egyptians used involved baking a special loaf of bread. This bread was crushed and placed in a sieve. Then, water was forced through it and the ensuing concoction was bottled and fermented. Women were primarily responsible for brewing beer, and about 17 types of beer have been identified in papyri. @L@LThe Egyptians drank their beer out of specially designed mugs. The mugs were outfitted with an angled pipe, a little like a straw. At the end of the pipe was a filter, which sifted out any solid material that might be in the beer. In addition to drinking beer at home, Egyptians also drank beer in taverns and inns. For more on what went on in these neighborhood drinking establishments, click @172here."
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
            text: "Papyrus Making",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Making papyrus was a rather involved process. First, the rind of the papyrus reed was removed so that the pith would be exposed. The pith from several plants was laid side by side, slightly overlapping, on top of a piece of cloth. Once the desired width was achieved, more strips of pith were laid on top of the first row at a right angle. Then, a second piece of cloth was placed on top, and the pith was beaten with a heavy piece of wood or a mallet. Beating the pith welded it together. The papyrus was then hung out to dry in the sun, and often the surface of the paper was polished with a stone."
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
            text: "Weapons",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The ancient Egyptians employed a variety of weapons in battle. For close-range fighting, soldiers used any of a number of weapons, including the mace, the dagger, the broad sword and the battle ax. The primary weapon used for longer-range battle was the bow and arrow, although slingshots were evidently used as well. Egptian weaponry evolved over time and took a big step forward after the invasion of the Hyksos. The Hyksos introduced horses and chariots to Egyptian warfare."
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
            text: "Luxury Goods",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Food, drink and clothing were enough for peasants, but the upper classes in ancient Egypt required a retinue of products to maintain their lifestyles. Chief among these luxuries was makeup. Both men and women wore eye makeup, either kohl or malachite. In addition to enhancing appearance, the Egyptians believed that eye makeup protected their vision. Women also used henna for nail polish and occasionally as hair dye. @L@LCleanliness was important to the ancient Egyptians, and in addition to regular bathing they perfumed themselves with various oils and extracts. Myrrh and frankincense were both used for this purpose. @L@LRelated to cleanliness was the use of wigs. Most Egyptians kept their hair short, possibly to prevent lice, and adorned their heads with wigs. Wigs came in various styles, and most women had more than one. Wigs were generally made from human hair, which was attached to the wig's base with string. @L@L@382Jewelry was another popular luxury item for the wealthy."
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
            text: "Pottery",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Very few homes were without a supply of pottery. Pottery manufacture, one of the oldest industries in ancient Egypt, originated in the home, where women produced whatever vessels were needed for cooking. Like other industries in Egypt, pottery making moved from the milieu of the home to the workshop. @L@LThe first step to making pottery was preparing the @190clay for use. The clay had to be kneaded, and often straw or chaff was added to the clay to act as a binding agent. Men kneaded the clay by hand or by foot, stepping on it make the clay workable. The clay was then placed on a wheel to be shaped. @L@LThe potter's wheel evolved through time. In its earliest form, the potter turned the wheel with one hand while molding the clay with the other. Because the potter could not turn the wheel very fast, the pottery had to be smoothed by hand later. During the New Kingdom, a second person spun the wheel with both hands while the potter shaped the vessel. This led to a much smoother finished product. By the end of the New Kingdom, the potter was again spinning his own wheel, this time with his feet, which yielded the smoothest pottery yet. @L@LAfter the vessels were shaped, they were left to dry. The pieces were decorated during the drying process. After drying, they were fired in a kiln. The kiln was a large oven with a fire chamber at its base. The fire chamber was separated from an upper chamber by a clay grid. Pottery was placed on this grid. The top chamber was sealed except for a hole to let smoke out. Once firing was complete, the product was finished and stored until needed."
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
            text: "Bazaar",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Bazaars were noisy and crowded places. Shopkeepers, both men and women, set out their wares, and buyers came by with goods to barter for these wares. Bazaars were generally located near the Nile to take advantage of the new goods that arrived by boat. @L@LBazaar scenes were frequently depicted on tomb walls. The Fifth Dynasty tomb of Khnumhotep and Niankhkhnum, manicurists to the pharaoh, depicts a vivid market scene, complete with a trained monkey biting the ankle of a would-be shoplifter."
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
            text: "A Village is Born",

        }
        content {
            text: "@PWelcome to ancient Egypt, land of the Pharaohs! Here you'll participate in the history of one of the greatest civilizations the world has ever seen, in an epic story that spans more than fifteen centuries and two dozen generations. You must lead one family, generation by generation, from its earliest beginnings in Egyptian pre-history, through the dawn of civilization...to the establishment of a unique and powerful empire...and beyond.     @POur story begins more than five thousand years ago, along the banks of the Nile river, in an area known as Nubt.  Here a small confederacy of clans struggles to eke out an existence in the harsh environment. With you at its head, your family leads this small settlement."
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
            text: "The Dawn of Civilization",

        }
        content {
            text: "@PAfter many years, and the passing of a generation, your family has resettled in the area of Thinis, in Upper Egypt. Here, a small band of local rulers is attempting to extend its influence over Lower Egypt, and all lands along the river Nile, and to unite this realm under its own house, with one supreme leader.   @PEstablishing Thinis as a thriving city, like nothing ever seen before, will prove the worthiness of the Thinite confederacy, and help them gain supremacy over Lower Egypt and the other factions vying for power. In time, this will mean providing the population with entertainment, and building wonderful temples to worship the region's patron deity. @PTo build a city this grand will require a substantial supply of cash. You'll find rich deposits of gold ore in Thinis, and harvesting them should be your first priority. "
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
            text: "The Precarious Nile",

        }
        content {
            text: "The Thinite nobles still struggle to unite the lands of the Nile under one supreme ruler.  To aid them in their cause, it is hoped that you will endeavor to establish a thriving community at Perwadjyt, in the humid Delta region of Lower Egypt, thus spreading their influence throughout the length of the sacred river.  To support a population larger than that of a village, you must learn to use agriculture. @PEgyptian farmers have begun to exploit the rich, fertile soil deposited by the annual Inundation of the Nile river for growing crops.  The Nile can be hazardous, however.  Many dangers lurk along its banks and in its waters, such as deadly crocodiles, hippopotamuses and malaria-carrying mosquitoes."
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
            text: "The First Pharaoh",

        }
        content {
            text: "As the people who live along the Nile still struggle to survive in this harsh environment, a local king named Narmer has risen to power.  Though Narmer has dominion over much of this land, full unification of the twin kingdoms has yet to be achieved.  In commemoration of his accession, Narmer wishes your family to establish and govern a new city at Nekhen.  This city will have temples to many of the gods of Egypt and numerous places of entertainment."
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
            text: "A Capital is Founded",

        }
        content {
            text: "After a lengthy struggle, King Hor-Aha has managed to unite the twin kingdoms of Upper and Lower Egypt, and proclaimed himself Pharaoh over all Egypt!  As a sign of his absolute sovereignty, and the establishment of this, the first dynasty of Egypt, Hor-Aha has ordered the founding of an imposing capital at Men-nefer, from which he may govern this fledgling nation.  Because of your family's many generations of faithful service to this land, Pharaoh has chosen you to be the architect of this splendid city.  Because the capital is the very symbol of our Kingdom, its citizens must enjoy a quality of life heretofore unknown in this land.  To this end you will eventually need to trade with other cities in the realm, and to provide a higher standard of education for at least some of your citizens.  You must also build a sacred mastaba tomb for the city's nobles."
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
            text: "An Expedition to Sinai",

        }
        content {
            text: "A new Pharaoh, Den, has taken the throne of Egypt.  Pharaoh is deeply concerned, as enemies have begun to threaten our borders, and our nation lacks adequate supplies of valuable copper needed to create weapons with which to equip our troops.  Pharaoh Den has ordered a mining expedition into the unforgiving land of Sinai, beyond our borders and deep within Bedouin territory.  The area known as Timna is rich in gold and copper ore, as well as precious turquoise gemstones, but it is otherwise barren.  Conditions there will be harsh, and you'll need to import many amenities, perhaps even additional food and fine linen, from Egypt.  Pharaoh will demand frequent shipments from Sinai and will ask you for money, copper, gemstones and weapons.  You can use any surplus of these items to help support the expedition.  Be always on your guard, for the Bedouin of the Sinai desert are formidable adversaries, and they will not willingly allow foreigners to occupy their land, let alone plunder their mineral wealth. @PTo lighten the burden that such living conditions impose on your city's people, build a Pavilion at some busy intersection.  Citizens can relax at the Pavilion's juggling and music stages, and, if you also build a Dance School, this new type of performance will provide great entertainment."
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
            text: "Pharaoh's Navy",

        }
        content {
            text: "Egypt's military troops are now unmatched in the known world, but the new Pharaoh, Khasekhemwy of the second dynasty, now also demands a powerful navy based at Behdet.  Nothing less than a fleet of warships will suffice to allow us dominion over the high seas, but timber is scarce, as our climate supports only a few sparse areas of forest.  Cedar may be imported at great cost from Byblos, in the land of Lebanon to the northeast.  Fortunately, exports of our native papyrus will provide a means of offsetting this expense."
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
            text: "The Challenge of the Sea ",

        }
        content {
            text: "Abedju, the burial place of our forefathers, has grown over the years into a sprawling necropolis of sacred tombs.  Now, most noble men and women wish to make this their eternal resting place.  To honor them, the new Pharaoh Khasekhemwy of the second dynasty has ordered the construction of three sacred mastaba tombs (one of greater size than the other two) for the local nobility.  @PPharaoh has also ordered the creation of a powerful navy, based at Behdet.  Abedju, too must support a modest fleet of combat ships, if our shores are to remain totally secure.  This will not be easy, as timber is scarce, and our climate supports only a few sparse areas of forest.  Cedar may be imported at great cost from Byblos, in the land of Lebanon to the northeast.  Fortunately, exports of our native papyrus will provide a means of offsetting this expense."
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
            text: "The Road to Africa",

        }
        content {
            text: "@PA new Pharaoh, Nebka, has been proclaimed, heralding the beginning of the third dynasty of Egyptian rulers.  Nebka has brought great organization and structure to Egypt, ordering that all our realm be divided into districts, or nomes, each governed by a local ruler called a 'Nomarch'.  Though this system may seem rigid, under his leadership Egypt has grown and prospered, and made many great achievements in art and architecture.  @L@PMerchant caravans, travelling oasis by oasis from deep within the African interior, have begun to provide Egypt with many rare and exotic luxury goods, now prized by our people.  Unfortunately these caravans are routinely attacked by warriors from Libya, and even by Bedouin of the Eastern Desert.  To secure these trade routes, Pharaoh Nebka, He of the Sedge and Bee, wishes you to establish a military post at the Selima Oasis, the hub of the caravan trade, far beyond the borders of our realm.   @L@PThere you will find some trees suitable for timber, the sale of which will help you raise money to fund the establishment of this outpost.  To forge weapons, you may obtain copper from our newly established mines at Timna, in the land of Sinai. @L@PFrom the Selima Oasis, you may import ebony from the African nation of Kerma.  Once you have succeeded in establishing this outpost, it shall provide a reliable source of ebony for all the cities in our realm."
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
            text: "The Nubian Border",

        }
        content {
            text: "@PA new Pharaoh, Nebka, has been proclaimed, heralding the beginning of the third dynasty of Egyptian rulers.  Nebka has brought great organization and structure to Egypt, ordering that all our realm be divided into districts, or nomes, each governed by a local ruler called a 'Nomarch'.  Though this system may seem rigid, under his leadership Egypt has grown and prospered, and made many great achievements in art and architecture.   @PPharaoh wishes to extend the borders of our realm further south, into Nubia.  He orders that a city be founded at the first cataract of the Nile, on the island of Abu, that we may take advantage of the abundant deposits of gemstones, granite and sandstone to be found there.   @PThe growing necropolis of Abjedu demands these materials for the creation of more and more elaborate tombs for the nobility.  The capital at Men-nefer, too, may have need of bricks for the construction of tombs, and Pharaoh Nebka may approve requests for these and other building materials.   @PPharaoh Nebka has also ordered that one of your peers establish a military post at the Selima Oasis, to secure the caravan routes into the African interior.  Once it has been established, you may look to the Selima outpost as a source of imported ebony, a highly prized luxury good."
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
            text: "The First Pyramid",

        }
        content {
            text: "The accession of Pharaoh Djoser to the throne of Egypt has ushered in a new era of wisdom, learning and artistic achievement.  A royal cemetery is to be established at Saqqara, to serve as the eternal resting place for nobles such as Hezyre and Khabausokar, Pharaoh's trusted courtiers.   @PBut this site shall also contain a monument the like of which the world has never seen before.  I, the Pharaoh's royal vizier Imhotep, have conceived a new form of sacred tomb for Pharaoh.  Unlike the low mud brick mastabas of prior Pharaohs, this tomb shall rise toward the heavens, as if it were comprised of several mastabas, placed one on top of the other.  And what's more, this 'stepped pyramid' shall be constructed entirely of stone, that it may endure the passage of the eons.  Deep within, a sarcophagus of solid granite shall hold Pharaoh's body for his eternal rest. @PPriests at the necropolis of Abjedu have perfected the art of using linen to embalm the dead, thus opening the door to everlasting life to all Egyptians.  @POur trading post at the Selima Oasis still thrives, and from there you may import ebony from Africa.  @PPharaoh has given you a generous supply of cash to get started on this project.  Do not let him down."
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
            text: "The Bedouin of the East",

        }
        content {
            text: "Like Den before him, Pharaoh Huni has ordered an expedition into the harsh land of Sinai to acquire turquoise gemstones and copper.  He wishes you to lead this expedition, to a place called Serabit Khadim, where the building remains of an earlier Egyptian outpost may still be found.  Their current condition is unknown, but they may still provide some means of defense for the expedition.   @PYou should be aware that the last such expedition sent to this area never returned.   A later expedition sent to recover them also did not return.  Nevertheless, if we are to arm our soldiers adequately, our Kingdom needs copper for making weapons, and this metal is scarce in our land. @PPrepare yourself, for you will be under constant threat of attack from the Bedouin of the Sinai desert, and from our enemies the Canaanites.  Mine what copper and gemstones you may under these conditions, and be prompt in fulfilling Pharaoh's requests.  You may employ jewelers to use any surplus gemstones to fashion jewelry for the people occupying the settlement."
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
            text: "A Royal Necropolis",

        }
        content {
            text: "Pharaoh Huni wishes to spend everlasting eternity in a stepped pyramid, like that of Djoser before him.  He wishes to be surrounded by the tombs of his nobles, and has chosen Meidum, in Lower Egypt, as the site for this royal necropolis.   @PAs a symbol of thanks for the many generations of faithful service provided by your house, Huni has also consented to allow you to be interred at Meidum, in your own tomb.  In doing this, he has also conferred great honor upon your family. @PTo ensure that the wisdom and learning of Egypt is preserved through the ages, Pharaoh Huni also urges the construction of royal libraries.  Once filled with scrolls of papyrus, these will provide higher education to the upper classes.  @PPharaoh has sent another of his faithful courtiers on an expedition to Serabit Khadim, in the harsh land of Sinai, to acquire turquoise gemstones.  If this expedition is a success, you may look forward to importing gemstones from there. Jewelers can use these to fashion jewelry, a valuable luxury good, for the people of your city. @PThe once-thriving city of Behdet has begun to decline, and no longer exports many of the commodities they were once known for."
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
            text: "Expansion to Nubia",

        }
        content {
            text: "Our new Pharaoh, Snofru, is determined that this, the fourth dynasty, be remembered as the greatest ever to rule Egypt.  Pharaoh wishes that our borders be pushed even further south.  He has therefore decreed that we invade Nubia, and establish a fortified city at Buhen, beside the second cataract of the Nile.  There you must also erect a granite obelisk, to serve as a beacon that this area forever belongs to Egypt, and to Pharaoh.  There is no granite to be found so far south, however, so you will need to import it from Abu.   @PAt Buhen you will encounter fierce and seasoned Nubian warriors, who will fight to the death to prevent us from establishing a foothold so far south.  Do not despair, for after rigorous training at a Military Academy, your fighting men may emerge as seasoned veterans themselves.  What's more, our military engineers have perfected the design of several defensive structures, such as fortified Towers, Walls and Gatehouses.  These will prove invaluable in withstanding the onslaught of the Nubian army.  Transport ships may also be employed, to aid in moving your army around by water when necessary.  @PTo the north, we have opened relations with Enkomi, on the island of Cyprus.  This land is named for its abundant reserves of copper ore, which we are now able to purchase from them.  However, thanks to a recently established Egyptian mining community at Serabit Khadim, in the land of Sinai, we are able to supply our governors with copper at a much more affordable price.  Supplies from Serabit Khadim are often erratic, due to unrelenting Bedouin and Canaanite attacks against the settlement, and we are uncertain how much longer the Egyptian forces stationed there can hold out.  @PPharaoh's burial place, a unique and spectacular monument, is currently under construction at Dahshur.  From time to time Pharaoh may request that you contribute some limestone to aid in the completion of this project."
        }
    }
    message_history_south_dahshur {
        id: 214,
        type: 3,
        size [40, 30]
        title {
            text: "South Dahshur",

        }
        subtitle {
            text: "Snofru's Bent Pyramid",

        }
        content {
            text: "@POur new Pharaoh, Snofru, is determined that this, the fourth dynasty, be remembered as the greatest ever to rule Egypt.  His architects have contrived a tomb even more spectacular than the stepped pyramid of Huni, and Pharoah wishes you to oversee its construction.  You will need to establish a fair sized settlement South of Dahshur, the site for Pharaoh's bent pyramid.  Once in place, this city will provide the workforce necessary to complete this ambitious project. @PThe bent pyramid is to be constructed of a plain stone core, and faced with fine white limestone, that it may forever shine under the desert sun.  You will find sufficient quantities of limestone at Dahshur, but you'll need to import the necessary amount of plain stone for this undertaking. @PPharaoh wishes that our borders be pushed even further south, and to this end he has dispatched military forces to invade Nubia, and to establish a fortified city at Buhen, beside the second cataract of the Nile. @PTo the north, Egypt has opened relations with Enkomi, on the island of Cyprus.  This land is named for its abundant reserves of copper ore, which are now a major import.  @PPrecious gemstones may be obtained from a recently established Egyptian outpost at Serabit Khadim, in the land of Sinai.  Lately the supply has become erratic, however, due to unrelenting Bedouin and Canaanite attacks against the settlement, and we are uncertain how much longer the Egyptian forces stationed there can withstand them."
        }
    }
    message_history_north_dahshur {
        id: 215,
        type: 3,
        size [40, 30]
        title {
            text: "North Dahshur",

        }
        subtitle {
            text: "The True Pyramid",

        }
        content {
            text: "@PPharaoh Snofru has brought order to Egypt, and the Kingdom now flourishes under his wise and benevolent rule.  Snofru wishes to undertake another construction project at Dahshur, even more ambitious than the bent pyramid already completed.  Royal architects, surveyors and engineers are confident that they can construct an edifice whose sides rise in one continuous angle, culminating in a perfect peak.  If successful, this will be the first true pyramid, and will be a worthy home for Pharaoh Snofru through all eternity!    @PPharaoh's wife, Queen Hetehpheres, has recently given birth to a son whom they have named 'Khufu'.  Our people look toward the day of his eventual rule with much foreboding, for the seers of Horus, God of the Pharaoh, have predicted that he will show none of his father's benevolence toward our people.  Though he will achieve many great things, they fear he will rule Egypt with unyielding tyranny.  @PYou may acquire wood from Byblos, since carpenters will have to build many ramps to allow workers to reach the summit of this great pyramid."
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
            text: "The defense of Egypt",

        }
        content {
            text: "@PPharaoh Khufu has taken the throne, and, as foretold by seers of Horus and Ra, our people have already begun to suffer under his oppression.  @PKhufu has ordered that a Royal Governor be dispatched at once to Iunet, to defend our land against Kushite invaders.  Iunet can support a small fishing industry, which should feed this settlement for a time.  If the Kushites invade by water, however, the river may become unsafe for fishing boats, and shore areas may be better used to support a fleet of warships.  If food becomes scarce, cattle may also be raised to provide meat, though the herds require much straw for fodder, and straw is difficult to grow in this land.  You should seek other cities with which to trade for straw, for you will also need this to make bricks for your mastaba. @PThe city of Byblos in Lebanon, land of the cedars, has begun trading with the powerful empires of the east.  These are Assyria and Ur, in the land called 'Mesopotamia', between the two great rivers, and from them the finest ivory may be obtained via Byblos.  With the arrival of rare and exotic luxury goods such as this, Iunet is sure to thrive. @PIn the capital, the Egyptian people have begun to enjoy a board game called senet.  This game is normally enjoyed over a pitcher of beer, in a public gathering place called a 'Senet House'.  Such places may provide a welcome diversion for the people of Iunet from the tyranny of Khufu's authority. @PPharaoh has ordered that countless quarries be dug at On, in the Delta region, to harvest a vast supply of fine white limestone.  Only the gods know what endeavor Pharaoh has planned for the use of this stone.  It is rumored that he is planning a colossal building project on the plateau outside Rostja, that he may usurp the renown his father, the wise and benevolent Snofru has earned from the completion of his two noble pyramids."
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
            text: "Ivory from the East",

        }
        content {
            text: "@PPharaoh Khufu has taken the throne, and, as foretold by seers of Horus and Ra, our people have already begun to suffer under his oppression.  It is rumored that he plans to begin a colossal building project on the plateau outside Rostja, that he may usurp the renown his father, the wise and benevolent Snofru, has earned from the completion of his two noble pyramids.  @PPharaoh Khufu has ordered a cluster of quarries to be dug at Tura, in the Delta region, where rich deposits of fine white limestone have recently been discovered.  You also must build three mastaba tombs for the nobles of this region, so that Pharaoh may honor their devotion.  The quarrying settlement you found shall be named 'On', and shall serve as a plentiful source of fine white limestone for many years...though only the gods know what endeavor Pharaoh has planned for its use. @PThe city of Byblos in Lebanon, land of the cedars, has begun trading with the powerful empires of the east.  These are Assyria and Ur, in the land called 'Mesopotamia', between the two great rivers, and from them the finest ivory may be obtained via Byblos.  With the arrival of rare and exotic luxury goods such as this, On is sure to prosper. @PKhufu has also dispatched a Royal Governor to Iunet, to defend our land against Kushite invaders.  Royal viziers look with pity upon the Governor charged with this difficult and dangerous task.  @PIn the capital, the Egyptian people have begun to enjoy a board game called senet.  This game is normally enjoyed over a pitcher of beer, in a public gathering place called a 'Senet House'.  Such places may provide a welcome diversion for the people of On from the tyranny of Khufu's authority."
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
            text: "The Great Pyramid and Sphinx",

        }
        content {
            text: "Pharaoh Khufu has at last made his plans known, and his boundless aspirations are sure to weigh heavily upon our people.  Pharaoh both curses and blesses your family, for though you have been awarded the status of Nomarch, you have also been charged with carrying out the most ambitious building project ever to be undertaken in our land.   @PPharaoh's eternal resting place shall be a massive pyramid complex, situated far from any city, on the plateau outside Rostja.  His sarcophagus shall be made of solid granite, and his funeral barge of precious Lebanese cedar. Beside Pharaoh's pyramid complex, a smaller pyramid shall also be built for his son prince Khafra, whose tyranny rivals that of his father, though his achievements do not.  Khafra also declares that his image be carved into the living rock at Rostja, upon a huge figure called a 'sphinx', with the body of a lion and the head of a man. @PTo support the massive building effort needed for the completion of this monument, you'll need to establish a large settlement at Rostja.  As such, conditions there may not be overly refined, for your goal is only to complete these three great projects, and to honor Pharaoh.   @PYou will be provided with some of the fine white limestone needed for the outer casing of these pyramids, but you will also need to purchase much of what you'll need with the city's own funds. @PPharaoh is entrusting you, one of his royal Nomarchs, with these three sacred tasks.  You must demonstrate unwavering dedication to Pharaoh and fulfill his wishes...whatever the cost."
        }
    }
    message_history_bahariya_oasis {
        id: 219,
        type: 3,
        size [40, 30]
        title {
            text: "Bahariya Oasis",

        }
        subtitle {
            text: "The Western Desert",

        }
        content {
            text: "@PThe reigns of Khufu and Khafra have come to an end, and with them so too has the fourth dynasty of Egyptian ruling families.  But lady Khentkaues, a distant member of this family, has given birth to a new Pharaoh named 'Userkaf', and so the royal line continues unbroken.  With Userkaf begins the fifth dynasty, an era that promises much change.   @PUserkaf has decentralized the rule of our country somewhat, and has granted more power to local authorities.  Now Nomarchs such as you are free to handle their own affairs.  Pharaoh will not attempt the construction of a massive tomb to house him for eternity, for he has another project in mind for you. @PPharaoh has declared Ra, god of the sun and of the kingdom, to be King of the Gods, and intends to proclaim his sovereignty throughout the land.  Many Sun Temples already dot the Egyptian landscape, but Pharaoh wishes to extend Ra's influence to the very edge of our Kingdom. @PTo accomplish this, you must build a fortified settlement at the Bahariya Oasis, far into the Western Desert. Use what water you can find there wisely, for what little there is to be found so far from the precious Nile is usually coveted by the wild beasts of the desert.  You must also beware of attacks by Libyan warriors, and Bedouin of the desert, which have plagued the desert caravans of late.  Plan your defenses carefully, and make use of whatever resources, such as wood and game, you can find at the oasis."
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
            text: "The Temple of the Sun",

        }
        content {
            text: "@PThe reigns of Khufu and Khafra have come to an end, and with them so too has the fourth dynasty of Egyptian ruling families.  But lady Khentkaues, a distant member of this family, has given birth to a new Pharaoh named 'Userkaf', and so the royal line continues unbroken.  With Userkaf begins the fifth dyanasty, an era that promises much change.   @PUserkaf has decentralized the rule of our country somewhat, and has granted more power to local authorities.  Now Nomarchs such as you are free to handle their own affairs. Pharaoh will not attempt the construction of a massive tomb to house him for eternity, for he has another project in mind for you. @PPharaoh has declared Ra, god of the sun and of the kingdom, to be King of the Gods, and intends to proclaim his sovereignty throughout the land.  Many Sun Temples already dot the Egyptian landscape, but Pharaoh wishes that the greatest be located at Djedu, in the humid Delta region of Lower Egypt.  @PLike most of the Delta, Djedu is rich in game, fish and other wildlife and vegetation, but offers few mineral resources.  As such, sandstone needed for construction of the Sun Temple will need to be imported from the quarries at the Dunqul Oasis.  Cattle may be raised here to provide meat, though the herds require much straw for fodder. @PYou'll need to clear land in order to create a suitable location for the Sun Temple.  Be sure to sell enough of the precious timber you may harvest first, for once it is gone you may not be able to acquire more.  Behdet and Abjedu are always in need of wood, and also game, thus trade with them should help to offset the cost of constructing this sacred monument."
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
            text: "The Kushite Threat",

        }
        content {
            text: "@PPepy has taken the throne, and awarded your family the status of Chancellor, but it has come with a price.   @PCentralized authority continues to erode, as local and regional leaders become more powerful.  Harvests in some regions are far below normal, and the specter of famine has begun to appear in Egypt.  Men-nefer, once a splendid and beautiful city, is beginning to decline.  Seers foretell difficult times to come. @PPowerful neighbors are moving to take advantage of Egypt's increasing weakness.  The outpost at Buhen is under siege from fearless Kushite soldiers sent from Kerma, the largest non-Egyptian city in Africa.  The Kush are demanding tribute, and the slightest provocation could lead to an outright attack. Nubia, too, has issued a call to war and is seeking to reclaim lost land.  @PIf Egypt is to survive, you must do what you can to preserve trade routes to keep goods flowing into and out of Egypt.  Keep the hard-won trading post at the Selima oasis open.  Pepy, anticipating his journey to the afterlife, will make frequent requests for stone to build his pyramid, and other cities, short on food, will seek sustenance from you. @PUse your resources carefully.  Valuable wood is plentiful at the oasis, but some of the forest must be destroyed to access the limited water supply."
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
            text: "The Caravan Trail",

        }
        content {
            text: "@P@PPepy has taken the throne, and awarded your family the status of Chancellor, but it has come with a price.   @PCentralized authority continues to erode as local and regional leaders become more powerful.  Harvests in some regions are far below normal, and the specter of famine has begun to appear in Egypt.  Men-nefer, once a splendid and beautiful city, is beginning to decline.  Seers foretell difficult times to come.  @POur powerful neighbors are moving to take advantage of our increasing weakness.  Our outpost at Buhen is under siege from fearless Kushite soldiers sent from Kerma, the largest non-Egyptian city in Africa.  The Kushite are demanding tribute, and the slightest provocation could lead to an outright attack.  Nubia, too, has issued a call to war and is seeking to reclaim lost land.  @PTry to keep Egypt stable by establishing an administrative post at Dakhla Oasis.  The oasis has a large stand of valuable trees, but these trees unfortunately block access to the limited water supply at the oasis.  From this important location, import ebony from the African interior.  Pepy, anticipating his journey to the after-life, will request bricks for the construction of his monument.  Other cities, short on food, will request sustenance from you."
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
            text: "Civil War",

        }
        content {
            text: "The old way of life is gone, and most fear that Egypt will never return to its past glory.  Osiris has turned his back on his people, and a series of low Inundations has caused widespread famine.  The power of the pharaohs, once unquestionable, has evaporated, replaced by bickering provincial leaders. @POut of this chaos, two noble families have arisen and are attempting to seize control of the country.  The rulers of Henen-nesw have laid claim to the throne as the rightful heirs.  They are particularly cruel and are doing little to assuage the people's hunger.  To the south, a new family, the Inyotef house, has risen to power in Waset.  This family has done much to reunite the south, and now Henen-nesw has engaged Waset in a deadly civil war for control of all of Egypt. @PTo show their benevolence to the people of Egypt, the Inyotefs have entrusted you with rebuilding the newly conquered city of Thinis, one of the oldest cities in Egypt.  Two of Thinis' finest and most ancient buildings have survived the turmoil of its conquest: the Temple Complex of Osiris and the mansion.  The Inyotefs have decreed that should either of these buildings be destroyed, no funds will be squandered on their restoration.  The Waset rulers consider the restoration of Thinis a top priority and have gathered up considerable funds - even in this time of strife - for this purpose.  Return Thinis to its former splendor, and commission a navy and raise a strong army to defend it from the frequent attacks of those loyal to Henen-nesw, including the cities of Sauty, Nekhen and Khmun.  Be careful of the Henen-nesw rulers: they may demand tribute to see if your loyalty - and your debens - can be extorted.  Also watch out for the opportunistic Nubians who seek to take advantage of Egypt's internal struggles."
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
            text: "Civil War",

        }
        content {
            text: "The old way of life is gone, and most fear that Egypt will never return to its past glory.  Osiris has turned his back on the people, and a series of low Inundations has caused widespread famine.  The power of the pharaohs, once unquestionable, has evaporated, replaced by bickering provincial leaders. @POut of this chaos, two noble families have arisen and are attempting to seize control of the country.  The rulers of Henen-nesw have laid claim to the throne as the rightful heirs.  They are particularly cruel and are doing little to assuage the people's hunger.  To the south, a new family, the Inyotef house, has risen to power in Waset.  The family has done much to reunite the south, and now the rulers of Henen-nesw have engaged the rulers of Waset in a deadly civil war for control of all of Egypt. @PThe Inyotefs, busy fighting the Henen-nesw rulers, have entrusted you with building up their home city of Waset.  If the Inyotefs are to succeed in their fight against the Henen-nesw rulers and solidify their reputation in Egypt, Waset must be a touchstone on which other cities rely, providing succor or soldiers to those that request aid.  Waset, which could be the capital should the Inyotefs reign victorious, must be a great city.  Using the scarce resources available to you, build a Sun Temple and pyramid to show Egyptians the glory of the Inyotefs. @PWaset itself is not immune to attack.  The Henen-nesw rulers, and those loyal to them, may threaten your city from time to time, and Henen-nesw may try to extort debens from your city's treasury.  To defend against these considerable risks, build a strong army and navy to defend your city and to come to the defense of other threatened cities."
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
            text: "Reunification",

        }
        content {
            text: "Your family's performance during the civil war has not gone unrewarded.  I, Pharaoh Mentuhotep, have awarded your family the rank of Vizier.  There is no one in all of Egypt that I trust more than you.  Now that the twin kingdoms of Upper and Lower Egypt are reunited and the capital at Waset is thriving, I need you to help me solidify my position throughout the Kingdom. @PWhile reunited, Egypt is prone to internal skirmishes, particularly in areas that were once loyal to the Henen-nesw rulers.  To help solidify our new union, I want you to rebuild and defend Kebet.  Kebet should be a glorious city that shows Egypt's citizens what is possible under my rule.   The city comes under frequent attack from remaining loyalist cities, such as Khmun, and you must be sure to defend your city's borders. @PFamine still stalks the country, and frequent requests for food will come to you from other cities in the Kingdom.  Respond as quickly as you can to their heart-rending pleas, so that all Egypt will know my benevolence and the dedication of my most trusted Vizier. @PI know that I am asking much of you, but there is no one else in Egypt capable of doing this difficult task."
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
            text: "Reunification",

        }
        content {
            text: "Your family's performance during the civil war has not gone unrewarded.  I, Pharaoh Mentuhotep, have awarded your family the rank vizier.  There is no one else in Egypt that I trust more than you.  Now that the twin kingdoms of Upper and Lower Egypt are reunited and the capital at Waset is thriving, I need you to help me solidify my position throughout the Kingdom. @PWhile reunited, Egypt is prone to internal skirmishes, particularly in areas that were once loyal to the Henen-nesw rulers.  To help solidify the newly reunited country, I want you to rebuild and defend Menat Khufu, which was nearly destroyed during the civil war.  Menat Khufu should be a glorious city that shows Egypt's citizens what is possible under my rule.   @PFamine still stalks the country, and frequent requests for food will come to you from other cities in the Kingdom.  Respond as quickly as you can to their heart-rending pleas, so that all Egypt will know my benevolence and the dedication of my most trusted vizier. @PI have one more noble request: I want you to build granite obelisks to further proclaim all I have done for this land in my lifetime. @PI know that I am asking much of you, but I also know that you are the only one in Egypt capable of doing what I have asked."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itjtawy", pos [50, 80] }
        subtitle { text: "A New Capital is Founded", pos [10, 30] }
        content {
            text: "O Mighty Pharaoh, Beloved of Ra, how fortunate you must feel.  Your unprecedented rise to the throne of Egypt is the stuff of dreams!  A richer reward could not be fashioned by gods or people. With your family's accession, Egypt can make a new start, and perhaps we can all forget the horrors of the civil war. @PTo mark this new beginning, you should build a fine new capital.  Itjtawy, with its abundant natural resources, is a perfect location.  Using what the land has to offer, you can build a splendid city worthy of your dynasty's valor and dedication. @PTo ensure the feats of your great dynasty are always remembered, you should build two majestic brick pyramids for yourself and your family and a frightening sphinx to guard your tomb.  A family with your achievements deserves no less. @PKeep in mind, though, that some in the country question the legitimacy of your rule.  Many are still suffering the effects of the famine and grumble that you usurped the throne.  If you relieve these people's misery and help them rebuild their homes, you will certainly win their undying loyalty.  You should try to provide for your new subjects as well as you can to prevent these unfortunate people from taking up arms against you."
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
            text: "Into Nubia",

        }
        content {
            text: "Now that Egypt is firmly united under your rule, all of your court, and I, your trusted vizier, recommend that we push the borders of our country south into Nubia.  The dry riverbed at Allaqi is rich with veins of gold, and a mighty city at Iken, with you in residence, will certainly keep the Nubians from trying to attack.  Be careful of the Kushites, however.  They are a much more dangerous adversary than the Nubians and will use their swords to encourage you, O Pharaoh, to leave their kingdom alone. @PTo leave a lasting mark on Nubia, you should build a large obelisk to attest to Egypt's many achievements.  The obelisk will offer compelling evidence to the Nubians of the benefits of Egyptian rule, and be a constant reminder of our presence. @PWhile your direct attention is devoted to Iken, do not forget our intent to establish a thriving port city on the Red Sea at Sawu.  Sawu will need help from you, and will not hesitate to ask for it.  If Sawu can thrive, they will provide Iken with much-needed copper, from which weapons can be forged."
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
            text: "On the Shores of the Red Sea",

        }
        content {
            text: "Now that Egypt is firmly united under your rule, we must develop trade relations with cities throughout the world to increase Egypt's wealth, O King of the Two Lands.  @PAs your people prosper, they demand more exotic items.  Tired of jewelry, an easily obtained luxury good, your people want rare and expensive luxury goods, such as incense.  Your court and I, your trusted vizier, recommend that you establish a Red Sea port at Sawu.  Sawu offers a trade route to distant Pwenet, from which the finest incense in the world may be imported, though at great cost.   @PBeside some modest veins of gold and copper ore, Sawu produces few raw materials of its own, but can thrive as a manufacturer of finished goods.  By importing raw materials from trade partners, and exporting finished products, Sawu shall be able to turn a tidy profit. @PWhile you are busy at Sawu, one of your most valiant Nomarchs is establishing a new trade center in Nubia.  His city, Iken, is likely to come under attack, so my beloved Pharaoh should be prepared to send him any resources he may need. @PUnder your rule, Sawu is sure to be one of the loveliest cities in the kingdom, suitable as a final resting place for you and your family.  As you establish the thriving port, do not neglect preparations for the afterlife.  A mausoleum and small brick pyramid will provide sumptuous quarters for you and your family after your passage to the Field of Reeds."
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
            text: "The Gauntlet",

        }
        content {
            text: "Most respected Pharaoh, all that your family has fought so hard for is threatened!  The Nubian navy is patrolling the Nile, striking deep into the heart of Egyptian territory, ransacking villages and cities alike.  The Nubians are also boarding trade ships, pirating away goods.   To help your northern cities beat back the foe, you should be prepared to send warships and soldiers to the cities that need them.   @PTo prevent the Nubians from again sailing our waters, your military advisors recommend building a cluster of forts at Heh between the second and third cataracts of the Nile.  The forts will act as a cork, penning the Nubians in to the south.   @PSuccessfully driving out the Nubians rests with conquering the city of Baki.  Baki is rich in resources, and taking it over will cripple the Nubian economy.  Once you have wrested control of Baki away from the Nubians, you can begin importing sandstone from the city for your great mausoleum.  Your mausoleum at Heh will serve as a reminder of your dominance over the unruly Nubians.   @PThere are many challenges before you as you protect Egypt from the Nubians.  Pay heed, O Living Horus, to the storm rising in the east.  The thundering of horses' hooves are heard throughout Canaan, and lightning-quick chariots are laying waste to all in their path.  These formidable chariots, the likes of which have never been seen anywhere, are driven by the Hyksos warriors.  Already, storm clouds have been spotted on the Egyptian horizon, and you should steel yourself against the impending danger."
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
            text: "The City of Bast",

        }
        content {
            text: "Most royal Pharaoh, with robust trade routes firmly in place, we should now show Egypt what success and wealth can bring.  Bubastis provides a perfect location for such a city: we can protect our valuable trade routes to the east while paying homage to Bast, who has watched over Egypt. @PBast's city should be like no other in Egypt.  It should be as lovely as the lotus flower, blooming forth with entertainment, schools, libraries and places of worship.  Its citizens should be well-supplied with the finer things, including imported incense.  When complete, Bubastis will be the jewel in the twin crowns. @PWhile you are building this glorious city, pay heed to the storm rising in the east.  The thundering of horses' hooves are heard throughout Canaan, and lightning-quick chariots are laying waste to all in their path.  These formidable chariots, the likes of which have never been seen anywhere, are driven by the Hyksos warriors.  Already, storm clouds have been spotted on the Egyptian horizon, and you should steel yourself against the impending danger."
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
            text: "Egypt Reclaimed",

        }
        content {
            text: "Most powerful Pharaoh, Egypt cries out for your help.  The menacing Hyksos have invaded our land and have set up their own capital at Rowarty.  From Rowarty, they have disrupted many of our trade routes, choking off needed supplies.  We must stop their conquest before it is too late. @PIf it pleases you, Great Pharaoh, we should reclaim the city at Khmun, which has been violated by these foul invaders.  We should also build a strong army and navy, for we may need to supply troops and arms to our compatriots in the north, especially at Rowarty, to help repel the Hyksos incursion.  They will look to you, Child of Ra, for support.  But now we too have a new weapon.  Our wise military leaders have become proficient in the use of the dreaded chariot, and we shall turn it back upon our enemies and drive them before us.  Once we drive the troublesome Hyksos out, our military advisors recommend building a fort in Sinai at Sharuhen to prevent further invasions from the east. @PIf only our trouble was limited to the north!  Reports from our southern border show that the Nubians are once again taking advantage of a distracted Egypt.  They have reclaimed the southern cities of Iken and Heh.  While these lost cities are cause for concern, we must first oust the Hyksos before we can turn our attention southward. @PThese Hyksos are most unholy invaders.  We have just discovered that they have defiled the pyramid here in Khmun.  They have stolen from the pyramid all the burial provisions that the mighty Pharaoh interred here needs in the Field of Reeds.  We should provide a new supply of grave goods so that the Pharaoh buried here can enjoy life everlasting."
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
            text: "Egypt Reclaimed",

        }
        content {
            text: " O King of the Two Lands, Egypt cries out for your help.  The menacing Hyksos have invaded our land and have set up their own capital at Rowarty.  From Rowarty, they have disrupted many of our trade routes.  We must stop their conquest before it is too late. @PHere at Sauty, we are safe from immediate attack, although the Hyksos have the gall to demand tribute. We may need to supply troops and arms to our compatriots in the north to help repel the Hyksos incursion.  They will look to you, O Mighty Pharaoh, for support.  But now we too have a new weapon.  Our wise military leaders have become proficient in the use of the dreaded chariot, and we shall turn it back upon our enemies and drive them before us. @PIf only our trouble was limited to the north!  Reports from our southern border show that the Nubians are once again taking advantage of a distracted Egypt.  They have reclaimed the southern cities of Iken and Heh. @PIf Egypt is to emerge intact from these turbulent times, much will be required of your generals in the field and on the river.  To inspire your two best generals, you have promised to build each of them a pyramid as spectacular as your own.  Holding your promise in their hearts, they are fiercely combating the foe, calling upon all their strength and sinew.   @PIf it pleases you, Mighty Pharaoh, you should build three magnificent pyramids at Sauty, one for yourself and one for each of your generals.  These three pyramids will take up considerable space, so you will need to surrender some valuable resources in order to accommodate them.  You may also need to extend your city across the Nile to avail yourself of all the resources needed for this city to flourish."
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
            text: "Expansion and Conquest",

        }
        content {
            text: "Egypt has emerged from its recent troubles with a newfound strength.  Byblos, with all its verdant forests and rich sources of copper, is ours!  With your presence, the city is sure to thrive, and a New Kingdom will be established. @PAh, but what an alarming discovery we made after conquering Byblos!  A new, ferocious people, the Hittites, have washed over much of Asia, and some even say that their empire rivals our own for size.  Now, they have turned their eyes toward Byblos, covetous of its riches.  If we are not well prepared for their attack, we could easily lose Byblos to our foe.  @PWhile preparing to meet the Hittites, we must mark Byblos as forever Egyptian.  With your blessing, O Pharaoh, we shall erect a series of three obelisks, two small and one large, proclaiming your sovereignty and fame throughout the far stretches of your empire.  These towering monuments will remind the residents of Byblos with whom their loyalties should lie. @PWhile we occupy ourselves with matters at Byblos, other regions of Egypt are still prone to attack.  Nubians have moved north as far as the first cataract, and we must help our compatriots drive them back.  Reports from Rowarty tell of another mysterious new foe, the Sea People.  Both these enemies must be strongly put down if Egypt is to attain glory.  To show your might, be sure to send troops and warships should they be requested."
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
            text: "The Glory of Egypt",

        }
        content {
            text: "With the Hyksos successfully expelled from our country, our land is ripe for rebirth, a New Kingdom that outshines past glory.  Most noble Pharaoh, Baki is an ideal place to begin this New Kingdom.  We can use the large amount of gold found there to fund your new vision of Egypt.  @PWhile Egypt is on the brink of greatness, a few nagging problems remain.  Many of Egypt's cities are still recovering from the disruptions caused by the Hyksos and may need Pharaoh's help.  In other regions, Egypt's old enemies still attack us, and a new enemy, the Sea People, has been raiding our northern coast. You must be prepared to defend other Egyptian cities from our foes, both old and new. @PAs Egypt grows in stature, many cities are willing to engage in trade.  Some of these cities are so familiar with our ways, and in awe of your power, that they consider themselves Egyptian, while others are foreign to us and are trading with us for the first time.  For the glory of Egypt, take advantage of all these relationships to provide your people with all the goods they desire. @PTo usher in the new era, your royal architects crave the opportunity to build two pyramids and a stately mausoleum for you, O Pharaoh.  These will surely reflect the wealth and grandeur you have brought to Egypt."
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
            text: "The Sea People",

        }
        content {
            text: "O Horus of Gold, our hold on Asia is strong and unchallenged, and our borders again stretch far into Nubia.  But the trouble on our northern coast is escalating.  The Sea People have become increasingly aggressive, wantonly raiding our cities.  Only Pharoah's presence will be enough to defeat this fierce and wily adversary.  If you commission a navy, supported by a strong army, surely we shall overcome the Sea People.   @PWhile you work to defeat the Sea People, your brave Nomarchs are leading attacks throughout the world.  If they are successful, Egypt will rule the world from the great Euphrates river in Asia to the sprawling Kushite city of Kerma to the south.  When you and your Nomarchs have met with sweet victory, your dynasty will be recorded as the greatest dynasty ever to keep watch over Egypt. @PMarking your far-reaching influence is a new, distant trade partner, Mycenae.  The king of Mycenae has learned of the splendor and bounty of Egypt, and wishes to engage in trade with us.  If you agree to open this trade route, O Pharaoh, your citizens will surely be provided with exotic goods unlike any they have ever seen. @PTo house your royal family for the afterlife, an awe-inspiring mausoleum and an impressive pair of brick pyramids must be built.  These monuments will remind all who follow of your deeds both on and off the battlefield."
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
            text: "The Glory of Pharaoh",

        }
        content {
            text: "Benevolent Pharaoh, you have brought peace and prosperity to our nation.  Under your wise and capable rule, Egypt is a strong and glorious country once again.  All Nomarchs are loyal to you, and no threats to our great nation remain. @PHaving accomplished all your family set out to do so many years ago, it is time to memorialize the achievements of your great dynasty.  The only way to accomplish this is to build the grandest pyramid Egypt has ever known, a pyramid even larger than Khufu's, at Rostja.  Others in your noble family have sacrificed much on the long road leading to your rule of Egypt.  They too must be remembered and honored, with a sandstone mausoleum to acknowledge their unwavering support.   @PThe ideal location for these monuments is Hetepsensusret in the rich Fayuum region.  From here, you can attend to all the affairs of state, and respond to any requests for supplies that your cities may ask of you, as you build your great pyramid."
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
            text: "The Banks of the Nile",

        }
        content {
            text: "@PWith the aid of your family, the Thinite king Hor-Aha has successfully united the twin kingdoms of Upper and Lower Egypt, proclaimed himself Pharaoh over all Egypt, and founded an imposing capital at Men-nefer.    @PYour clan has relocated once more, this time to the humid Delta region of Lower Egypt, to an area known as Perwadjyt. Canaanite warships have been threatening this region, and you'll likely need to dispatch a few warships of your own, when the time comes. @PYour family has achieved the status of nobility. As such, it is expected that before you pass from this world into the next, you will undertake to complete an exquisite brick tomb - a mastaba - to house your body on its journey into the afterlife. @PHowever, first you must establish some farms along the banks of the Nile, to exploit the rich, fertile soil deposited by the annual Inundation of the river. This will allow your population to grow and prosper, and eventually become large enough to complete this sacred monument. But beware, for many dangers lurk among the life-giving waters of the Nile, such as deadly crocodiles, hippopotamus and malaria-carrying mosquitoes. @L@LFarming along the Nile @PYou must build farms directly on the flood plain, in order to gain the benefits of its increased fertility. Unlike most working structures, farms on the flood plain do not need direct access to employees, but do need a steady workforce of peasant laborers, supplied by work camps, to tend their fields. Build work camps fairly close to flood plain farms, so peasants won't have to walk too far to reach them. @G56 @L@LThe annual harvest @L@PEach year the Nile floods its banks, replenishing the depleted soil on the flood plain with rich, fertile mud.  Peasants harvest the annual crop just before the Inundation, and deliver it to your granaries. Because there is only one harvest per year, make sure to have enough granaries to store a sufficient amount of food for your growing population."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Food or Famine?", pos [0, 15] }
        content {
            text: "@PA growing population needs a reliable source of food and some means of storing and distributing it. Certain animals, like the ostriches in this region, can be hunted for game. Granaries store game and other foods, while Bazaars distribute the food to the village's inhabitants. As with most working structures, in order to function properly these buildings must be located within reach of housing, and the city must have enough workers to staff them. @L@LHunting for food  @L@PBuild a Hunting Lodge close to the ostrich flocks, and hunters will set out in search of prey. If successful, they'll bring the carcasses back to the lodge to be butchered, after which a cart pusher will deliver them to the nearest Granary for storage.   @PDifferent workers from the Bazaar assess the needs of the neighborhoods they serve, acquire food from nearby Granaries, and deliver this food to the houses in their immediate vicinity to meet these needs. @G60 @PBuild Granaries and Bazaars by clicking on the 'Storage and Distribution Structures' button. @G77 @L@PUltimately, your goal in this mission is to transform some of your 'crude huts' into 'meager shanties'.  This is accomplished by providing them with water, and food from the Bazaar.  Also, make sure they're not too close to any unsightly industrial buildings or inferior housing, which discourage home improvements by lowering the desirability of the area.  @PYou will eventually learn various ways to increase an area's desirability. For now, though, simply avoid locating homes too near to industries.  @L@LOverseers @L@LAn Overseer of the Granaries is now available to provide information and advice. In time, you will have many advisors to help run your city. @G76  @L@PTo access them, click on the 'Overseers' icon, or right click on the appropriate building."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Entertainment", pos [0, 15] }
        content {
            text: "As your city becomes more advanced, some citizens can enjoy leisure-time activities, such as taking in a little entertainment. A wide assortment of entertainment is one of the hallmarks of a truly cultured city, but currently you can only provide entertainment in the form of Jugglers. @L@LEntertainment Venues and Jugglers @PThe Juggler needs a venue on which to perform, the smallest of which is called a 'Booth'. Build a Booth at an intersection to stage juggling performances, and a Juggler School nearby to train performers. Both need access to employee housing, and enough workers to staff them. @PJugglers trained at the school will proceed to any nearby Booth to put on shows, imparting a modest amount of entertainment to the surrounding area. @G61 @L@LConsult your Overseer of Diversions to learn more about your city's recreational needs.  Click 'Overlays: Entertainment' to see which houses in your city have access to entertainment."
        }
    }
    message_gold_and_crime {
        id: 241,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Gold and Crime" }
        content {
            text: "@L@L Mining Gold @L@PSearch rocky areas for the presence of metal ore, evidenced by shiny metallic patches among the rocks. In order to extract the ore, you must build Gold Mines adjacent to these veins. @G53 @L@LPalace @L@PA Palace is needed to convert the raw gold ore, as well as to store the resulting gold bullion. The Palace is the seat of the city's government, and must be built where there is suitable access to ground water (grassy areas). @POnce your Palace is up and running, miners will deliver gold ore from any Gold Mines for conversion into cash, counted in 'debens'. @G54 @L@LCrime @L@PWith a supply of cash in reserve, however, comes the risk of theft. Constables can help reduce losses through theft, both by patrolling the streets to prevent crime and by subduing any criminals they encounter. @G55 @L@PThe best way to prevent crime, though, is to keep your population happy with adequate food, health care and jobs."
        }
    }
    message_farming_along_the_nile {
        id: 242,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Farming along the Nile",

        }
        content {
            text: "Farming along the Nile @L@PYou must build farms directly on the flood plain, in order to gain the benefits of its increased fertility.  Unlike most working structures, farms on the flood plain do not need direct access to employees, but do need a steady workforce of peasant laborers, supplied by Work Camps, to tend their fields.  Build Work Camps fairly close to flood plain farms, so peasants won't have to walk too far to reach them. @G56 @L@PEach year the Nile floods its banks, replenishing the depleted soil on the flood plain with rich, fertile mud.  Peasants harvest the annual crop just before the inundation, and deliver it to your Granaries.  Because there is only one harvest per year, make sure your city has enough Granaries to store a sufficient amount of food for your growing population."
        }
    }
    message_developing_culture {
        id: 243,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Developing Culture",

        }
        content {
            text: "Beer @LYour fellow Egyptians have perfected the art of brewing beer, which has become a very popular libation throughout Egypt!  With a supply of barley received from local farms, brewers will make beer and deliver it to Storage Yards for future distribution by Bazaar workers (as with food and pottery). @L@LMultiple Gods @LThe patron god of this region is Ra, but Osiris and Bast are also worshipped here as local deities.  Make sure this city has more Temples and Shrines dedicated to Ra, but don't neglect the local deities either!  To accommodate your most valued citizens, make sure they have access to temples dedicated to different gods. @L@LMore Entertainment @LSophisticated Egyptians like to listen to music in their leisure time, as well as take in the occasional juggling performance.  While only Jugglers can perform at the small Booth, both Jugglers and Musicians can perform together at a Bandstand. Build a Bandstand at an intersection, and a Conservatory nearby to train Musicians.  Access to multiple types of entertainment greatly enhances the quality of life in any city. @L@LLaw and Order @LA Magistrate patrolling from his Courthouse helps to reduce the risk of crime by hearing grievances and making sure that cooler heads prevail."
        }
    }
    message_getting_started {
        id: 244,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Getting Started",

        }
        content {
            text: "Begin by planning for areas of housing and industry.  By now you know what the people want, in addition to the basics of food and water.  You must provide some houses with pottery, beer, entertainment and access to religious services before you can think about higher education and trade."
        }
    }
    message_soldiers_and_forts {
        id: 245
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: " Soldiers and Forts",
        }
        content {
            text: "To conscript troops, build a Fort and a Recruiter.  The Recruiter will send new conscripts, one by one, to the fort until it is fully occupied.  There are two types of Fort, infantry and archer, and each Fort holds sixteen soldiers, referred to as one 'company'.  If soldiers die in combat, the Recruiter will see to it that replacements are conscripted. @G57 @L@LWeapons @PArchers supply their own bows and arrows, but infantry troops must be outfitted with copper-tipped spears.  With a supply of copper, a Weaponsmith will forge such weapons.  These are then delivered to the Recruiter, so that any new foot soldiers may be suitably equipped. @L@LGoals and Briefings @PFrom now on, your immediate goals will no longer appear at the top of your screen.  Click the 'ankh' symbol on the Control Panel to review your Mission Briefing for goals, then visit your overseers to assess your overall progress."
        }
    }
    message_trade_on_the_water {
        id: 246,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "At the Water's Edge",

        }
        content {
            text: "Trade on the Water @LTrade may also be conducted by river and sea, if any such water routes currently run to the city.  To open a water trade route, visit the World Map.  To trade along a water route, your city will also need a working Dock. @L@LFishing the Nile @LThe Nile is a plentiful source of fish, a popular food in Egypt.  What's more, a diet comprised of multiple types of foods leads to better health and happiness for your people.  To harvest this rich bounty, you'll need some fishing boats. @L@LBuilding Boats and Ships @LThe Shipwright builds combat ships and fishing boats.  Each boat must be supported by its own Wharf.  Whenever there is a Wharf in need of a vessel, the Shipwright will begin constructing one for it.  Without a waiting Wharf, the Shipwright will not build any ships.   @LAlthough a single Shipwright can supply all the vessels your city needs, multiple Shipwrights will allow you to replace lost vessels much more quickly.  The Shipwright doesn't need any materials to create fishing boats, but he will need a supply of wood to construct military vessels, such as warships and transport ships. @LMilitary vessels, trade ships and fishing boats are broad-beamed and deep-keeled to navigate the Nile and coastal waters. They are not made to sail very narrow channels, and indeed cannot travel up small streams or inlets.  Nothing will stop you from building Shipwrights, Docks or Wharves in such locations, but if you do so, boats cannot travel to or from these facilities, and they will not work. @LAs you scout the shore for suitable maritime sites, bear in mind that all ships need free passage between their port and their destination.  You cannot, for example, build a Fishing Wharf on an inland lake and expect its boats to reach the fishing grounds of the Nile, even if that lake is connected to the Nile by a small stream."
        }
    }
    message_at_the_waters_edge {
        id: 247,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "At the Water's Edge",

        }
        content {
            text: "Trade on the Water @LTrade may also be conducted by river and sea, if any such water routes currently run to the city.  To open a water trade route, visit the World Map.  To trade along a water route, your city will also need a working Dock. @L@LFishing the Nile @LThe Nile is a plentiful source of fish, a popular food in Egypt.  What's more, a diet comprised of multiple types of foods leads to better health and happiness for your people.  To harvest this rich bounty, you'll need some fishing boats. @L@LBuilding Boats and Ships @LThe Shipwright builds combat ships and fishing boats.  Each boat must be supported by its own Wharf.  Whenever there is a Wharf in need of a vessel, the Shipwright will begin constructing one for it.  Without a waiting Wharf, the Shipwright will not build any ships.   @LAlthough a single Shipwright can supply all the vessels your city needs, multiple Shipwrights will allow you to replace lost vessels much more quickly.  The Shipwright doesn't need any materials to create fishing boats, but he will need a supply of wood to construct military vessels, such as warships and transport ships. @LMilitary vessels, trade ships and fishing boats are broad-beamed and deep-keeled to navigate the Nile and coastal waters. They are not made to sail very narrow channels, and indeed cannot travel up small streams or inlets.  Nothing will stop you from building Shipwrights, Docks or Wharves in such locations, but if you do so, boats cannot travel to or from these facilities, and they will not work. @LAs you scout the shore for suitable maritime sites, bear in mind that all ships need free passage between their port and their destination.  You cannot, for example, build a Fishing Wharf on an inland lake and expect its boats to reach the fishing grounds of the Nile, even if that lake is connected to the Nile by a small stream. @L@LMaking Bricks @LBricks are a somewhat less expensive building material, used in the creation of certain kinds of tombs.  To make bricks, you'll need a Brickworks, and supplies of clay and straw."
        }
    }
    message_the_finer_things_tutorial {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "The Finer Things",

        }
        content {
            text: "Temple Complexes @LAs devotion to their patron gods continues to grow, the Egyptian people demand bigger and bigger places of worship.  Most cities will want to erect a Temple Complex to their chosen god, so that they may fully partake of his or her benevolence.  Once built, the Temple Complex may be expanded through the addition of an Oracle and an Altar, each dedicated to other, lesser gods.  These gods, too, will impart certain benefits to the city.   @L@LLuxury Goods @LIn addition to locally made jewelry, the Egyptian people prize certain other luxury goods, which are available only through importation.  A city needs access to more than one type of luxury good in order to become truly civilized.  @L@LHarvesting Timber @G58 @LTimber is a rare and valuable commodity in the arid country of Egypt.  Regions that have forests are truly lucky.  To harvest what usable tree growth may be found, build a Woodcutter, and men will be dispatched to hew timber.  Timber is used to create warships, transport ships, as well as support structures for some monuments."
        }
    }
    message_housing_and_roads {
        id: 249,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Housing and Roads" }
        content { text: "@PThe first things this village will need are housing, to provide settlers with a suitable place to live, and a network of roads, to allow its eventual inhabitants to find their way around easily and efficiently. @PBuild areas of housing, and you'll soon see people move into the village. @G50 @L@LRoads @L@PClick and drag the mouse to build long lengths of road at one time. @G51 @PAt every intersection, walkers must choose which way to go, so each intersection lessens your control over their actual routes. @G52 @PPlan roads carefully, with as few intersections as possible, to ensure that people walk where you want them to.  @PThe path by which these immigrants reach your city is known as the Kingdom road. Migrants always need free passage from the Kingdom road to the city's housing areas. If you isolate some neighborhood from this vital link to the outside world, its homes will simply disappear. @L@LTo exit any message panel (like this one), click your right mouse button." }
    }
    message_basic_healthcare {
        id: 250
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Basic Healthcare" }
        content { text: "Your city suffers from health problems, as is to be expected with a growing population. Malaria and disease are the most common health crises that will afflict your city's households, though widespread plague can strike if healthcare is exceptionally inadequate.  @PIf a house does become infected with malaria or disease, all its occupants will die, and the house cannot be reoccupied for a certain period of time. @G64 @LMalaria @L@PMalaria is most prevalent close to water and marshland. The 'Risks: Malaria' overlay shows which houses are more likely to succumb to this illness.   @PAccess to clean water from a Water Supply and insect repellent provided by a local Apothecary both greatly reduce the risk of malaria for any given household. Like most buildings, the Apothecary only functions when it has road access and labor. @G63 @LDisease @L@PPhysicians help to reduce the risk of disease by administering medicines to the houses they serve. A steady supply of food is also essential to disease prevention. The 'Risks: Disease' overlay shows which houses are in danger of succumbing to disease." }
    }
    message_requests_from_other_cities {
        id: 251
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Requests from other cities"
            pos [0, 20]
        }
        content {
            text: "One of your fellow cities is in need, and has made a request of you. If you want to remain on good terms with the rest of the growing Kingdom, it is usually best to respond to requests like this willingly and promptly. @G65   @POnce your Storage Yards hold enough of the desired item, consult your Political Overseer to dispatch a delivery to the city in question."
        }
    }
    message_fire_in_the_village {
        id: 252,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Fire in the village!" }
        content { text: "A fire has broken out in the village! @L@PTo protect against future fires, you can now build Firehouses.  @PLike most non-residential buildings in the village, the Firehouse needs workers in order to operate. To find employees, someone is dispatched from the building in search of occupied houses. Once some housing is located, the building has access to employees, though this does not necessarily mean there are enough workers in the village to fill all vacant jobs. Once staffed, the Firehouse can send fire marshals out to patrol the village.  @PFire marshals inspect buildings on their routes for fire hazards, reducing their risk of catching fire as they pass. Fire marshals can provide their services to any building within two spaces of a road. @G67 @PIf he discovers a fire, the marshal moves in to douse the flames with buckets of water, then returns to his normal patrol. @G66 @PClick on 'Overlays: Risks' to see which buildings are in danger of catching fire.  If a building burns down, you can right-click on the pile of rubble left behind to learn what was there before the fire. @L@LMessages @L@PWhen you hear the chime that sounded when this panel appeared, that means a message has arrived for you. To read a message, click on the message button. @L@PSome urgent messages (like this one) are presented to you before being stored with your other messages. Less urgent notices go directly to your message box without being specially displayed, so be sure to listen for the chime.  Special instructional messages (like this one) are marked with a blue scroll so you can easily refer back to them when needed." }
    }
    message_tutorial_collapsed_building {
        id: 253,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Collapsed Building" }
        content { text: "Certain large structures in your city will collapse without adequate maintenance. To ensure this does not happen, build an Architect's Post. Like the Firehouse, this structure dispatches workers, in this case architects, to patrol the streets and repair any damaged buildings encountered. @G68 @L@PClick on 'Overlays: Risks' to see which buildings are in danger of catching fire or collapsing." }
    }
    message_tutorial_education {
        id: 254
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Education", pos [0, 15] }
        content {
            text: "Now that you've built up this city somewhat, it's time to provide education for some citizens.  @L@PSchools and Libraries cannot educate the people without papyrus on which to write. @G69 @PReed Gatherers supply Papyrus Makers with the necessary raw materials, and papyrus is then distributed directly to the city's educational facilities."
        }
    }
    message_tutorial_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Clean Water",

        }
        content {
            text: "Well done! You've managed to supply this village's Granary with food. Now the villagers need access to clean water from a Water Supply, which is much preferred over well water.    @L@LWater Supply @L@PLike Wells, these must be built on land with underlying ground water, as indicated by the presence of green grass growing. Water Supplies also need access to employees in nearby housing. @G70   @L@POnce up and running, a Water Supply will dispatch a water carrier to deliver buckets of clean drinking water to all the houses in his immediate vicinity.  Click 'Overlays: Water', to see which houses have access to clean water from a Water Supply, to simple well water, or to no water source at all. @L@LMission Briefing and Objectives @PTo complete this mission, you need to provide six 'sturdy huts' with food from a Bazaar, so they'll evolve into 'meager shanties'.  Click on the scroll icon to review your mission objectives in this and any other mission."
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
            text: "Monuments and More!"
        }
        content {
            text: "Since you've made it this far in the demo, it's time for you to sample a little more of what Pharaoh has to offer. Be sure to consult your newly available advisors for more information and help in running your burgeoning city. @L@LMonuments @L@PYou can now start to build your Mastaba tomb! To place the mastaba, click on the 'Religious Structures: Monuments' button.  You'll need a supply of bricks, plus bricklayers and peasant laborers (supplied by Workcamps) to complete this 'monumental' task...and you only have eleven years in which to do it!@G75 @L@LOther Household Amenities @L@PIn addition to pottery, Egyptian households need a supply of beer and linen (plus a few other things not available in this demo!). Beer is made at a Brewery, from barley grown on local farms. Linen is made by a Weaver from flax, another local crop. Like food and pottery, both beer and linen are distributed to houses by the Bazaar. @L@LLaw and Order @L@PA magistrate patrolling from his Courthouse helps to reduce the risk of crime, by hearing grievances and making sure that cooler heads prevail. @L@LHealth and Sanitation @L@PEvery city needs a few embalmers to ensure sanitation, and to provide its more sophisticated inhabitants with proper burial rites. The Mortuary uses linen (made by a Weaver), and confers embalming services on houses in the surrounding area. Dentists provide the houses they serve with much desired dental care. @L@LEducation @L@PSchools and Libraries cannot educate the people without papyrus on which to write. Reed Gatherers supply Papyrus Makers with the necessary raw materials, and papyrus is then distributed directly to the city's educational facilities. @G69 @L@LWarships @L@PYou might need to defend your city's shores with sturdy warships. You'll need a Wood Cutter to supply timber to the Shipwright, which fashions these combat vessels for Warship Wharves. @L@LTaxation @L@PAlthough you cannot acquire revenue through trade and exports in this demo, you can squeeze a few debens out of your population through taxation. Build enough Tax Collectors to cover the whole city, and especially its most expensive housing."
        }
    }
    message_tutorial_the_gods_of_egypt {
        id: 258
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "The Gods of Egypt" }
        content {
            text: "An Egyptian city cannot truly flourish without suitable places of worship, in the form of religious Temples and Shrines. These should be located close to the homes that they serve, and must be dedicated to one of five gods:  @L@POsiris - God of the Nile @PRa - God of the Kingdom @PPtah - God of Craftsmen @PSeth - God of Destruction @PBast - Goddess of the Home @L@PEvery city has different religious tendencies. In a given city, one god is usually held in particularly high esteem - and is referred to as its 'patron' god - while the other gods are worshipped as mere 'local deities' (and others may be completely unknown). The patron god of Thinis is Bast. @PBoth patron gods and local deities can become hostile if not shown the respect due their positions.  To appease the gods, build enough Temples and Shrines dedicated to each of them to serve your current population. @PA working Temple sends a priest through nearby neighborhoods, granting residents access to the worship of his god. @G73  @LFestivals @PFestivals are another way to appease the gods.  Build a Festival Pavilion in the city, and instruct your Overseer of the Temples to hold a festival for one of the gods. @L@LOverseer of the Temples @L@PConsult the Overseer of the Temples to determine the status of each of the gods in any particular city, and whether the gods are sufficiently appeased. Lightning bolts indicate that the god is feeling hostile toward your city, while a blue mystic symbol indicates that the god is feeling benevolent toward your city. The more you see of either, the more likely your city is to feel the god's presence (for better or worse!). @PClick 'Overlays: Religion' to see which houses in your city are served by Temples."
        }
    }
    message_tutorial_industry {
        id: 259
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Industry" }
        content { text: "Now that you've given your people basic food and water, you can enhance their lifestyle with other goods, such as pottery.  \t @L@LIndustry and Pottery @L@PBuild a Clay Pit close to water, and a Potter nearby. Make sure these have access to labor as usual, and before long a cart will deliver clay to the Potter, who will create pottery for your city.  @PBuild a Storage Yard to store the final product as well as any excess clay the Potter does not need (one Clay Pit can usually supply enough clay for two Potters).   @PWorkers from the Bazaar will collect the pottery from the Storage Yard and distribute it just as they do food. @G74 @LIndustries like pottery also provide your city's inhabitants with much-needed jobs. You can now call upon your Overseer of the Workers to assist in allocating your workforce." }
    }
    message_tutorial_trade_with_other_cities {
        id: 260
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Trade with other Cities" }
        content { text: "Now that you have managed to educate some of your people, you might want to generate additional revenue by selling any surplus papyrus you have to neighboring cities.  You'll also need to import bricks from Perwadjyt in order to build the sacred mastaba tomb.  When you're ready, click on the World Map icon [graphic here] to see what other cities there are in the known world, and to begin setting up trade." }
    }

    message_tutorial_flooded_clay_pit {
        id: 271
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Flooded Clay Pit" }
        content { text: "One of our Clay Pits suffered a terrible flood. We had to destroy the Clay Pit to prevent others from falling in." }
    }
    
    message_kingdom_road_blocked {
        id: 279
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Kingdom Road blocked" }
        content { text: "Recent construction blocked the @57Kingdom&road running through these lands.  Royal architects reopened this vital route...but they had to remove a building or two in the process!" }
    }
    
    message_wrath_of_ra {
        id: 280
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Wrath of Ra" }
        video { text: "@23" }
        content { text: "Ra punishes your arrogance by severely lowering your reputation throughout the Kingdom. As you spurned the god, so shall other Egyptians belittle you." }
    }

    message_wrath_of_seth {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Wrath of Seth" }
        video { text: "@21" }
        content { text: "Your disregard for Seth prompts the god to destroy all of your ships!" }
    }

    message_wrath_of_seth_2 {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Wrath of Seth 2" }
        video { text: "@21" }
        content { text: "Your disregard for Seth prompts the god to destroy all of your ships!" }
    }

    message_the_world_map {
        id: 282
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "The World Map",

        }
        content {
            text: "The World Map shows the location of your own city, as well as other cities in the world.  Here you can pay to open up trade routes with any cities willing to trade.   @L@LOther Cities  @LCities who wish to engage in trade appear on the map in full color and fly a flag.  Cities that will not trade with your city are muted.  To set up a trade route, click on the city you wish to do business with.   @L@LImporting and Exporting @LOnce you set up a trade route, you'll still need to instruct the Overseer of Commerce as to which resources and commodities you wish to import or export.  You can never import and export the same item at the same time."
        }
    }

    message_tutorial_monuments {
        id: 283
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monuments" }
        content {
            text: "With a supply of bricks, you're now ready to begin work on the sacred mastaba tomb.  Most monuments require both skilled and unskilled workers.   @L@LConstruction Guilds @LConstruction Guilds supply the skilled labor needed to erect monuments.  The mastaba is made entirely of bricks, and requires only Bricklayers' Guilds to build it.  You can employ as many Bricklayers' Guilds as your economy can support, but make sure you also have enough bricks being delivered to the construction site to keep them busy. @POnce the Bricklayers' Guild has adequate labor, it will dispatch bricklayers to the construction site, where they will wait for a delivery of bricks by unskilled peasant laborers. @L@LPeasant Labor @LOnce there are some bricklayers awaiting supplies at the monument site, gangs of peasant laborers will begin to haul loads of bricks to them.  Because these same laborers also must tend the fields on the flood plain, you may find that work on the monument slows down somewhat when the flood has receded and the peasants return to their fields.  You can construct additional Work Camps, so that any surplus laborers not needed to tend the fields may work on the monument year-round. @G75 @L@LBegin by clicking on the Religious Structures icon, then search for a suitable location in which to place this large building."
        }
    }
    
    message_the_finer_things {
        id: 284
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "The Finer Things"
        }
        content {
            text: "Temple Complexes @LAs devotion to their patron gods continues to grow, the Egyptian people demand bigger and bigger places of worship.  Most cities will want to erect a Temple Complex to their chosen god, so that they may fully partake of his or her benevolence.  Once built, the Temple Complex may be expanded through the addition of an Oracle and an Altar, each dedicated to other, lesser gods.  These gods, too, will impart certain benefits to the city.   @L@LJewelry @LWith a supply of gemstones, Jewelers in your city can fashion jewelry.  Jewelry is one type of valuable luxury good, which the higher social classes in the city demand.  @L@LLuxury Goods @LIn addition to locally made Jewelry, the Egyptian people prize certain other luxury goods, which are available only through importation.  A city needs access to more than one type of luxury good in order to become truly civilized.  @L@LQuarrying Stone @LTo quarry stone, a highly sought after building material, build a quarry next to a rock outcropping.  Quarrymen will deliver stone blocks, one at a time, to the Storage Yard.  Make sure to employ architects to ensure that quarries don't cave in!"
        }
    }

    message_innovations {
        id: 285
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Innovations"
        }        
        content {
            text: "Meadow Farming @LSome land is fertile enough for farming, even though it's not situated on the flood plain.  You can identify such meadow areas by tall, yellow plant growth.  Some farms planted on meadows can produce more than one harvest per year, though the yield is usually somewhat less than that of a floodplain farm. @G59   @L@LIrrigation @LEmploy irrigation to increase the fertility of any farmland. Irrigation ditches on the flood plain can be connected directly to the Nile, but you'll need a Water Lift to elevate the water onto dry land.   @L@LWater Lifts @LWater Lifts can be built on the edge of the flood plain, or on the coast, where you can raise water directly from the river up to dry land. Connect an irrigation ditch to the back of the Water Lift to bring irrigation water to inland farms.  @L@LStonemasons and Carpenters @LTwo new types of Construction Guild will be needed to erect the stepped pyramid: the Stonemasons' Guild and the Carpenters' Guild.  Stonemasons from the Guild wait at the construction site for blocks of stone, hauled there by peasant laborers.  These blockhaulers need ramps to reach the higher levels of the structure.  When it's time for the stepped pyramid to rise another level, a carpenter carries wood from the Guild to the site, and constructs a ramp for the blockhaulers. @L@LPreserving the Dead @LEvery city needs a few embalmers to ensure sanitation, and to provide its more sophisticated inhabitants with proper burial rites. The Mortuary uses linen, made by a Weaver, and confers embalming services on houses in the surrounding area."
        }
    }

    message_troops_return_failed {
        id: 287
        type: 2
        
        size [30, 20]
        title { text: "Company returns" }
        content { text: "Under cover of night, surviving members of your disgraced company slink back to the comfort of the city's Forts, determined to never again suffer humiliation in battle." }
    }
    message_troops_return_victorious {
        id: 288
        type: 2
        
        size [30, 20]
        title {
            text: "Heroes return!"
        }
        content {
            text: "Your victorious soldiers are home from the war. Their numbers might be reduced somewhat since they left, but their comrades' sacrifice was for the good of Egypt! "
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
        title { text: "Osiris is upset" }
        content { text: "The lord of the Nile flood will punish this city for its lack of devotion, and next year's flood will destroy all farms in its path!" }
    }
    message_ra_is_upset_2 {
        id: 291
        type: 2
        
        size [30, 20]
        title { text: "Ra is upset" }
        video { text: "@23" }
        content { text: "Angered by your disrespect for him, Ra lowers your own reputation in the eyes of the Kingdom." }
    }
    message_ptah_is_upset {
        id: 292
        type: 2
        
        size [30, 20]
        title { text: "Ptah is upset" }
        video { text: "@22" }
        content { text: "Dismayed by your disinterest in him, Ptah destroys one of your Storage Yards and whatever goods it held." }
    }
    message_seth_is_upset {
        id: 293
        type: 2
        
        size [30, 20]
        title { text: "Seth is upset" }
        video { text: "@21" }
        content { text: "To remind you that Seth protects only those who show the proper respect, the god destroys your best company of soldiers and razes their Fort." }
    }
    message_bast_is_upset {
        id: 294
        type: 2
        
        size [30, 20]
        title { text: "Bast is upset" }
        video { text: "@20" }
        content { text: "The goddess Bast, stung by your indifference, sends a plague to stalk your city. Remember that health and happiness flow from her." }
    }
    message_blessing_from_osiris {
        id: 295
        type: 2
        
        size [30, 20]
        title { text: "A blessing from Osiris" }
        video { text: "@24" }
        content { text: "Osiris, god of the Nile flood, blesses this city for its sincere devotion. All farms on the flood plain will harvest double what they had expected this season!" }
    }
    message_blessing_trade_from_ra {
        id: 296
        type: 2
        
        size [30, 20]
        title { text: "A blessing from Ra" }
        video { text: "@23" }
        content { text: "Ra rewards his faithful! For the next 12 months, your city can sell its exports for half again their usual value." }
    }
    message_blessing_trade_from_ptah {
        id: 297
        type: 2
        
        size [30, 20]
        title { text: "A blessing from Ptah" }
        video { text: "@22" }
        content { text: "Ptah singles out a Storage Yard with excess capacity, and increases the gems, clay, pottery, flax, linen, or jewelry already present there." }
    }
    message_blessing_trade_from_seth {
        id: 298
        type: 2
        
        size [30, 20]
        title { text: "A blessing from Seth" }
        video { text: "@21" }
        content { text: "Seth approves of your fear and obedience, and so will strike down the next enemies who dare to violate your city." }
    }
    message_blessing_from_bast {
        id: 299,
        type: 2,
        
        size [30, 20]
        title { text: "A blessing from Bast" }
        video { text: "@20" }
        content { text: "Because this city is so faithful and dedicated, Bast blesses its houses and Bazaars with a bounty of food and goods!" }
    }
    message_the_gods_are_wrathful {
        id: 300
        type: 2
        
        size [30, 20]
        title { text: "The gods are wrathful" }
        content { text: "At least one god is angry with the city. Your people beg you to build more Temples...and they always welcome a festival, too." }
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
            text: "The spirit of Seth",
        }
        video {
            text: "@21"
        }
        content {
            text: "Seth remembers his promise to protect you, and is delighted to slay those who were foolish enough to threaten your city."
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
        title { text: "Compliance now possible" }
        content { text: "Your Political Overseer reports that the city now has enough debens  to fulfill the recent request." }
    }
    message_tutorial_finances {
        id: 310,
        type: 2,
        message_type: 4
        size [40, 30]
        title { text: "Finances" }
        content {
            text: "Taxation @LA large city needs to bring in additional revenue, beyond its initial funding.  One way to accomplish this is through taxation.  In order to levy taxes, your city will need a Palace and Tax Collectors.  Make sure to build enough Tax Collectors to cover the whole city, especially its more well-to-do neighborhoods.  Remember, the better the quality of life enjoyed in a given home, the more taxes its occupants will pay. @L@LYour Personal Salary @LIf you build a Mansion for yourself, you can draw a personal salary from the city's treasury.  Personal funds are retained by your family, to be used whenever the situation demands, even in subsequent missions.  Beware, though, as awarding yourself a higher salary than is due your position can have detrimental effects on your standing in the kingdom."
        }
    }
    message_mission_defeat {
        id: 311,
        type: 2,
        
        size [30, 20]
        title { text: "Defeat!" }
        content { text: "O bitter day! Your ignoble end should have been unthinkable. You have failed your people, your ancestors and your descendants. Now Egypt yearns for another champion to take your place..." }
    }
    message_mission_victory {
        id: 312,
        type: 2,
        
        size [30, 20]
        title { text: "The Winner" }
        video { text: "smk\\win_game.smk" }
        content { text: "Unused entry 312" }
    }
    message_enemy_rome_army_attacks {
        id: 313
        type: 2
        message_type: 7
        
        size [30, 20]
        title { text: "Enemy army attacks" }
        video { text: "smk\\spy_army.smk" }
        content { text: " Enemies of Rome are at the outskirts of your city. Expect them to drop in for an urn or two of wine - and whatever else strikes their fancy!" }
    }
    message_storage_yards_ready_to_fulfill_request {
        id: 314,
        type: 2,
        message_type: 2,
        
        size [30, 20]
        title {
            text: "Compliance now possible",
        }
        content {
            text: "Your Political Overseer reports that city Storage Yards  now have enough of these goods to fulfill the recent request."
        }
    }
    message_kingdom_road_obstructed {
        id: 315,
        type: 2,
        
        size [30, 20]
        title {
            text: "Kingdom road obstructed",
        }
        content {
            text: "Architects had to demolish some recent construction to restore free passage to the @57Kingdom&road."
        }
    }
    message_no_working_dock {
        id: 316,
        type: 2,
        
        size [30, 20]
        title { text: "No Working Dock" }
        content { text: "Although you told your Overseer of Commerce to commence trade with a sea merchant, the merchant cannot land at our city! You need to construct a dock and supply it with workers. Once you have a dock operating, ships will come and begin trading." }
    }
    message_fishing_boats_cant_navigate {
        id: 317,
        type: 2,
        
        size [30, 20]
        title { text: "Fishing Boats Can't Navigate" }
        content { text: "Our fishermen report that a Bridge blocks their route! Ships cannot sail under Bridges. Remove the Bridge to let the fishing boats supply your city with fresh fish." }
    }
    message_health {
        id: 318,
        type: 3,
        
        size [30, 20]
        title {
            text: "Health",
        }
        content {
            text: "People like to be healthy. If they eat well, and are visited regularly by a doctor from a clinic, they should be healthy. If their health ever drops, they have a greater chance of falling ill. @PHospitals come in handy when citizens get sick. Anyone who is sick needs a hospital to cure them. If there is no room in the hospital, they will die. @PSo: clincs help prevent illness, while hospitals cure it. @L@LOccasionally, a plague might strike, and Bast has been known to send disease to a city which has angered her. At such times good hospital coverage is the only defense. Your Overseer of Public Health can tell you whether you have good hospital coverage or not."
        }
    }
    message_messages_await_you {
        id: 319,
        type: 3,
        
        size [30, 20]
        title {
            text: "Messages Await You",
        }
        content {
            text: "When you hear a fanfare, it means that your scribe has received another message for you, and stored it in his records. @L@LSome messages, like this one, appear opened automatically for you. These are very urgent matters that your scribe feels you should see immediately. You can review them later on, if you wish, by clicking your message button. @PImportant, rather than urgent, messages are signaled by an important fanfare, but do not appear automatically. Most messages are regular messages with a regular fanfare, which you can view at your convenience. @L@LAll messages are stored by your scribe so you can refer back to them when you want to. You can also delete them if you wish to. If you want more information, choose Help from the menu bar and click on 'Messages From Your Scribes' (near the end of the Table of Contents)."
        }
    }
    message_local_uprising {
        id: 320,
        message_type: 7
        
        size [30, 20]
        urgent: 1
        title { text: "Local uprising" }
        content { text: "Inspired by Seth, some locals have decided to air various grievances they have long held against you!!" }
    }
    message_small_blessing_from_osiris {
        id: 321
        type: 2
        
        size [30, 20]
        title { text: "A small blessing from Osiris" }
        video { text: "@24" }
        content { text: "Osiris has noticed your city's faithful dedication. The next Inundation of the Nile will be better than previously expected." }
    }
    message_minor_blessing_from_ra {
        id: 322
        type: 2
        
        size [30, 20]
        title { text: "A Minor blessing from Ra" }
        video { text: "@23"}
        content { text: "Encouraged by your proper awe, Ra lifts your reputation somewhat throughout the Kingdom." }
    }
    message_minor_blessing_from_ptah {
        id: 323
        type: 2
        
        size [30, 20]
        title { text: "A Minor blessing from Ptah" }
        video { text: "@22" }
        content { text: "Ptah is pleased by your attention, and so ensures that Shipwrights, Weavers or Jewelers throughout your city are fully stocked with raw materials." }
    }
    message_minor_blessing_from_seth {
        id: 324
        type: 2
        
        title { text: "A Minor blessing from Seth" }
        video { text: "@21" }
        content { text: "To reward your obedience to him, Seth vows to protect any of your soldiers sent to battle in far-off lands." }
    }
    message_small_blessing_from_bast {
        id: 325
        type: 2
        
        size [30, 20]
        title { text: "A small blessing from Bast" }
        video { text: "@20" }
        content { text: "Bast is pleased that your city honors her. She has thrown a festival so that all the gods will notice your piety." }
    }
    message_disease_strikes {
        id: 326,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Disease Strikes",
        }
        content {
            text: "Disease struck a household with poor healthcare access.  People are dying, and you can't help them.  Improve unhealthy areas to stave off a recurrence."
        }
    }
    message_a_plague {
        id: 327,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "A Plague",
        }
        content {
            text: "Plague stalks the city!  We feared that this would happen, with overall @53city&health so poor.  Pray that our Apothecaries can handle it."
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
            text: "Some homes have come down with malaria.  Better health measures could prevent this needless waste of human life!"
        }
    }
    message_blessing_reputation_from_ra {
        id: 329,
        type: 2,
        
        size [30, 20]
        title { text: "A blessing from Ra" }
        video { text: "@23" }
        content {
            text: "You have honored Ra, and so your reputation throughout the Kingdom is substantially better than it was!"
        }
    }
    message_minor_blessing_trading_from_ra {
        id: 331,
        type: 2,
        
        size [30, 20]
        title { text: "A minor blessing from Ra" }
        video { text: "@23" }
        content { text: "To acknowledge your respectful attitude, Ra inspires your trading partners to trade more than before." }
    }
    message_wrath_of_ra_2 {
        id: 332,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Ra" }
        video { text: "@23" }
        content { text: "You incurred Ra's anger! The god lowered the opinion of your city's goods, and your trade partners will now trade far less than they did previously." }
    }
    message_wrath_of_ra_3 {
        id: 333,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Ra" }
        video { text: "@23" }
        content { text: "As you have forsaken Ra, so shall your trade partners forsake you. No trade ships or caravans will visit your city for one full year." }
    }
    message_ra_is_upset {
        id: 334,
        type: 2,
        
        size [30, 20]
        image { id: 224, pos [15, 15] }
        title { text: "Ra is Upset!" }
        video { text: "@23" }
        content { text: "As you have spurned Ra, so shall your trade partners spurn your city's goods. They have decided to reduce the amount they are willing to trade with you." }
    }
    message_wrath_of_bast_2 {
        id: 335,
        type: 2,

        size [30, 20]
        title { text: "Wrath of Bast", }
        content { text: "Your city escaped the wrath of Bast -- the goddess sought to level your finest houses, but found no homes worthy of her fury this day. Be wary, nonetheless, of provoking the Goddess of the Home, for she is patient and her memory is long. Show Bast the respect she demands before she returns." }
    }
    message_wrath_of_ra_4 {
        id: 336,
        type: 2,
        
        size [30, 20]
        title {
            text: "Wrath of Ra",
        }
        content {
            text: "Ra shall see to it that you are punished for your disrespect!"
        }
    }
    message_wrath_of_osiris_3 {
        id: 337,
        type: 2,
        
        size [30, 20]
        title {
            text: "Wrath of Osiris",
        }
        video {
            text: "@24"
        }
        content {
            text: "Osiris is outraged, though he is powerless to punish your city.  Enjoy this while you can, for your city may not be so lucky next time."
        }
    }
    message_blessing_inundation_from_osiris {
        id: 340,
        type: 2,
        
        size [30, 28]
        title { text: "Osiris Blesses you" }
        video { text: "@24" }
        content { text: "Osiris rewards those who pay him worship. The next Inundation will be significantly better than we were expecting." }
    }
    message_wrath_of_osiris_4 {
        id: 341,
        type: 2,
        
        size [30, 20]
        title { text: "Wrath of Osiris" }
        video { text: "@24" }
        content { text: "Osiris reminds you that respect is due. The next Inundation will be poorer than we had expected." }
    }
    message_mediocre_inundation_seers {
        id: 342,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Our seers warn that the coming year's Inundation is likely to be mediocre at best." }
    }
    message_poor_inundation_seers {
        id: 343,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Priests expect a poor Inundation in the coming year." }
    }
    message_no_inundation {
        id: 344,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Terrible news! All the omens suggest that there will be no Inundation at all this year!" }
    }
    message_poor_inundation {   
        id: 345,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Priests predict a poor Inundation for the coming year. Your people beseech you to make sure Osiris is appeased, and pray for better floods in coming years." }
    }
    message_mediocre_inundation {
        id: 346,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "We expect the next Inundation to be mediocre, at best. Perhaps Osiris will bestow his benevolence upon is, if we make sure to appease him." }
    }
    message_good_inundation {
        id: 347,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "All portents point to a good Inundation in the coming year." }
    }
    message_excellent_inundation {
        id: 348,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Farmers are overjoyed by predictions for an excellent Inundation in the coming year!" }
    }
    message_perfect_inundation {
        id: 349,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer prediction" }
        content { text: "Priests predict that the city will be blessed with a perfect Inundation in the coming year!" }
    }
    message_temple_complex_to_osiris {
        id: 350,
        
        size [30, 20]
        title {
            text: "Temple Complex to Osiris",
        }
        subtitle {
            text: "Religion",
        }
        content {
            text: "When you build a Temple Complex for Osiris, the god is inclined to send better floods from year to year. You can build the following additions onto Osiris' Temple Complex: @L@LAltar of Sebek, God of Fertility @LSebek grants priests of Osiris the power to stretch the city's supplies of food and goods.  As priests of Osiris walk through your city, the people in the houses they pass are suddenly satisfied with less. @L@LOracle of Min, God of Regeneration @LWhen your city honors Min with an Oracle, he speeds the regrowth of trees and reeds, increases the rate at which prey animals reproduce and improves the yield from fishing and hunting. @L@LPeople love living next to a Temple Complex. For more on religion, click @51here. @L@LFind out about Osiris, Sebek and Min in ancient Egypt by clicking @376here."
        }
    }
    message_temple_complex_to_ra {
        id: 351,
        
        size [30, 20]
        title {
            text: "Temple Complex to Ra",
        }
        content {
            text: "Ra smiles upon the city when it has dedicated a Temple Complex to him, and he makes sure that others in the Kingdom smile upon your city, too.  Building a Temple Complex for Ra increases your Kingdom rating and, should the city find itself in debt, allows you to pay a lower interest rate.  Building an Altar and Oracle onto the Temple Complex of Ra helps you manage the city's affairs: @L@LAltar of Ma'at, Goddess of Justice @LThrough priests of Ra, Ma'at bestows a calming effect on your city.  As they pass by houses, Ra's priests dissuade individual residents from thievery.  The simple presence of the Altar reduces the city's overall risk of crime breaking out. @L@LOracle of Horus, God of the Pharaohs @LThis Oracle increases citizens' dedication to your city and to the Kingdom, encouraging them to accept a lower wage without affecting their mood. @L@LPeople love living next to a Temple Complex. For more on religion, click @51here. @L@LFind out about Ra, Ma'at and Horus in ancient Egypt by clicking @377here."
        }
    }
    message_temple_complex_to_ptah {
        id: 352,
        
        size [30, 20]
        title {
            text: "Temple Complex to Ptah",
        }
        content {
            text: "When you build him a Temple Complex, Ptah speeds the production of many of your city's industries, including Gold Mines, Copper Mines Gemstone Mines, Clay Pits, Shipwrights, Jewelers and Weavers.  The Altar and Oracle in Ptah's Temple Complex hasten the output of other industries and improve educators' abilities: @L@LAltar of Amon, God of the Sun @LHonored by your attention, Amon spurs quarries, Wood Cutters, and Brickworks to work more quickly. @L@LOracle of Thoth, God of Wisdom and Learning @LThoth's goal is to bring the light of learning to as many people as possible.  When you build an Oracle of Thoth, librarians and teachers use less papyrus to educate the city's inhabitants. @L@LPeople love living next to a Temple Complex. For more on religion, click @51here. @L@LFind out about Ptah, Amon and Thoth in ancient Egypt by clicking @378here."
        }        
    }
    message_temple_complex_to_seth {
        id: 353,
        
        size [30, 20]
        title { text: "Temple Complex to Seth" }
        content { text: "When a city has a Temple Complex dedicated to him, Seth instills a fierce will in the city's soldiers, granting them more experience, protecting them in battle.  The additions to Seth's Temple Complex are:  @L@LAltar of Anubis, God of Death @LAnubis gives easier access to eternal life for citizens in the city.  With his blessing, Mortuaries need less linen to prepare bodies for eternity.   @L@LOracle of Sekhmet, Goddess of War @LSekhmet endows priests of Seth with the power to reduce the risk of crime in the houses that they pass and to apprehend criminals in the city.  @L@LPeople love living next to a Temple Complex. For more on religion, click @51here. @L@LFind out about Seth, Anubis and Sekhmet in ancient Egypt by clicking @379here." }
    }
    message_temple_complex_to_bast {
        id: 354,
        
        size [30, 20]
        title { text: "Temple Complex to Bast" }
        content { text: "Building a Temple to Bast brings good fortune to any city.  Bast helps keep citizens happy by making them satisfied with less.  As a result of her benevolence, the rate at which your citizens consume food and goods is reduced, and the effects of entertainers, educators and health providers last longer.  Her sister goddesses also improve life for your citizens: @L@LAltar of Isis, Goddess of Healing @LThrough priestesses of Bast, Isis lays her healing hands on the city's populace, removing plagued walkers from the streets and cleansing any infected houses the priestesses may pass.  Isis also takes care to improve your city's overall health. @L@LOracle of Hathor, Goddess of Joy, Love and Festivity @LHathor, flattered by the Oracle you have built for her, will improve citizens' mood, resulting in a better @39City&Sentiment. @L@LPeople love living next to a Temple Complex. For more on religion, click @51here. @L@LFind out about Bast, Isis and Hathor in ancient Egypt by clicking @380here." }
    }
    message_building_firehouse {
        id: 355,
        
        size [30, 20]
        title {
            text: "Firehouse",
        }
        content {
            text: "Some buildings in the city can catch fire. Likely candidates include run-down housing and industrial buildings, like Potters.  If you do nothing to stop it, fire can spread through the city, destroying whole sections at one time. To prevent this, build Firehouses near buildings that are likely to catch fire. Fire marshals from Firehouses roam the city (click @42here for more on walkers)and reduce a building's risk of catching fire as they pass by. @PShould a fire break out, nearby fire marshals proceed to the scene to extinguish the flames. If a fire marshal has a long way to travel, the flames could spread and the destruction in your city could be quite severe. @G67 @PThe @18fire&overlay is a helpful guide to fire prevention. The overlay shows the fire marshals at work, but more importantly points out which buildings are especially prone to fire. Use this information to plan the placement of your next Firehouse. @PFirehouses need road access and a labor supply in order to operate. Residents won't relish living near Firehouses."
        }
    }
    message_building_warship_wharf {
        id: 356,
        
        size [30, 20]
        title {
            text: "Warship Wharf",
        }
        content {
            text: "Warship Wharves berth warships. The first thing a new Warship Wharf does is order a warship from the @82Shipwright.  @PA Warship Wharf requires both road access and labor. It must also be on straight piece of coastline, and ships must be able to easily navigate to the Wharf. Citizens will not want to live too close to a Warship Wharf. Some sailors, after all, do not have the best reputations. @PWhen a warship is not out doing battle, its crew prefers to be back in the safety of the wharf. Here, the crew can rest up for the next battle. @PRead the entry on @365warships to find out how to maneuver a ship in battle. @L@LAncient Egypt's military tradition is long and storied.  Click @184here to find out more."
        }
    }
    message_building_transport_wharf {
        id: 357,
        
        size [30, 20]
        title {
            text: "Transport Wharf",
        }
        content {
            text: "Transport Wharves berth transport ships. The first thing a new Transport Wharf does is order a transport ship from a @82Shipwright.  @PA Transport Wharf requires both road access and labor. It must also be on straight piece of coastline, and ships must be able to easily navigate to the Wharf. Your citizens will not want to live too close to a Transport Wharf.  @PRead the entry on @367transport ships to find out how to maneuver a ship in battle. @L@LAncient Egypt's military tradition is long and storied.  Click @181here to find out more."
        }
    }
    message_building_roadblock {
        id: 358,
        
        size [30, 20]
        title {
            text: "Roadblock",
        }
        content {
            text: "Roadblocks help you control the paths @42roaming&walkers take.  When walkers who roam the city encounter a Roadblock, they turn around.  Roadblocks do not affect destination walkers.   @PBuild a Roadblock anywhere that your roaming walkers don't need to go - for example, on the road to your industrial areas.  Be wary, though, of isolating areas entirely from walkers who roam the city.  The same Roadblock that keeps a trader from the Bazaar from wandering into the industrial sector also turns back architects, fire marshals and constables.  It also stops labor recruiters from walking from the industrial area to your housing sector where they find employees. @G62 @PWhen you erect a new Roadblock near an existing building, you might want to watch the building for a moment to ensure that its walker pops out on the correct side of the Roadblock.  Sometimes the building's employees won't grasp your intentions, and they will send their walker off in the wrong direction.  This can be particularly vexing with labor access seekers, because the building that employs them believes that it has access to labor, but the Roadblock prevents the walker from ever reaching the labor pool.  Your only recourse is to rebuild the Roadblock a space farther away. @PRoadblocks don't need employees, and their only restriction is that they be placed on roads. They have no impact on desirability."
        }
    }
    message_building_hunting_lodge {
        id: 359,
        
        size [30, 20]
        title {
            text: "Hunting Lodge",
        }
        content {
            text: "Build a Hunting Lodge to send out hunters after their quarry. Ostriches, fowl and antelopes can all be hunted. @PYou can build Hunting Lodges anywhere, although it is wise to place them near their prey, which tends to stay near its breeding grounds.  Hunting Lodges require both labor and road access to function. When they are up and running, you will see a hunter standing in the yard taking target practice. @PHunters proceed from the lodge out into the fields where their prey awaits. After hunters kill their prey, they bring the animal back to the Hunting Lodge where it is made suitable to eat. Once a cartload of game meat is ready, it is brought to the @3Granaries or to the @4Storage&Yards (if they have been told to accept game meat). @G60 @PGame meat can be an important part of citizens' diets. It provides the variety that people crave. The city, however, will most likely not be able to subsist solely on game meat. Herd and flock sizes are limited, so hunting alone cannot provide all the food a large city will need. For more on feeding your people, read about @45farming&and&food production. @PGame meat (along with @89straw) is also used to help feed animals in a @479Zoo.  @PHunting Lodges have a negative effect on @56desirability. @L@LGame meat was used to supplement the ancient Egyptian diet.  And, hunting was enjoyed as sport by the elite.  Click @383here to find out more."
        }
    }
    message_building_cattle_ranch {
        id: 360,
        
        size [30, 20]
        title {
            text: "Cattle Ranch",
        }
        content {
            text: "Raise cattle on a Cattle Ranch to provide meat to the city's residents. @PCattle Ranches need to be placed adjacent to a road and need access to labor. They also need straw, either from a @89Grain&Farm or imported from a @47trade&partner. Cattle Ranches do not need to be placed on fertile land, nor do they need access to water. @PRead about @45farming&and&food production to learn more about the place of meat in your citizens' diets. @PCattle ranches stink, and citizens do not enjoy living nearby. @L@LThe ancient Egyptians raised many animals for food.  Click @186here to find out more."
        }
    }
    message_building_gemstone_mine {
        id: 361,
        
        size [30, 20]
        title {
            text: "Gemstone Mine",
        }
        content {
            text: "Gems are mined from rocky outcroppings. You can't tell by looking at the rock whether or not it can produce gems. If gems can be mined, Gemstone Mines will be listed in the Industrial Structures: Raw Materials list. Like @95quarries, Gemstone Mines must be placed adjacent to rocky outcroppings, and need laborers and road access.  They are also susceptible to collapse, so be sure to build an @81Architect's&Post nearby. @PGemstone Mines are dusty places, and citizens do not want to live nearby. @L@LRead more about gems in ancient Egypt by clicking @382here."
        }
    }
    message_building_sphinx {
        id: 362,
        
        size [30, 20]
        title {
            text: "Sphinx",
        }
        content {
            text: "The Sphinx is an elaborately carved and painted protector of Pyramids. @PTo build a Sphinx, you must first find a location.  Pick 'Sphinx' from the Religious Structures: Monuments list.  A footprint of the sphinx appears.  As you move this footprint around the landscape, it will either be all green, or green with one or more red diamonds.  When the footprint is all green, then you have found a suitable hidden deposit of stone.  Click the mouse button, and the stone will be revealed.  If any red diamonds appear in the footprint, some flaw in the landscape prevents you from building the Sphinx here.   @PNow, the @363stonemasons and @363carpenters can get to work, assuming that you have the necessary wood.  Carpenters build scaffolding that stonemasons climb to carve the Sphinx. @PRight-click on the Sphinx to visit the @369Construction&Foreman for a progress report. @L@LClick @391here to read about the most famous Sphinx."
        }
    }
    message_construction_guilds {
        id: 363,
        
        size [30, 20]
        title {
            text: "Construction Guilds",
        }
        content {
            text: "Without Construction Guilds, you won't be able to build the magnificent structures that honor Pharaoh and Egypt. @PThere are four specialized Construction Guilds: Carpenters', Bricklayers', Stonemasons' and Artisans'. Although common laborers from @8Work&Camps provide most of a monument project's muscle power, the expert guilds turn piles of raw materials into the largest and most complex buildings you will build, such as the Pyramids, @362Sphinx, @371Mastabas, @69Sun&Temple, @368Mausoleums and @392Obelisks. Each monument requires its own particular guild workers. @PConstruction guilds must have road access and a local source of labor. Carpenters' Guilds must have a supply wood on hand. Artisans' Guilds need a supply of @470paint and @92clay (for plaster) to add their finishing touches to the burial tombs. Bricklayers and stonemasons wait at the monument site for the materials they need. @PBecause of the noise, your citizens do not like living near construction guilds. @L@LTo learn more about these specialized fields in ancient Egypt, read the entries on @386bricklayers, @385stonemasons, @389carpenters and @472artisans."
        }
    }
    message_building_brickworks {
        id: 364,
        
        size [30, 20]
        title {
            text: "Brickworks",
        }
        content {
            text: "Brickworks fashion @92clay and @89straw into bricks.  Bricks are used in the construction of several types of monuments and can also be @47exported for profit. @POnce a Brickworks has labor and road access, it needs a supply of raw materials to function. Brickworks need both straw and clay. Straw is produced on @89Grain&Farms and clay is dug out of the ground at @92Clay&Pits. Both raw materials can also be imported from a @47trade&partner.  @PWhen a Brickworks is producing bricks, you can see brick makers toiling in its yard. Once a load of bricks is produced, the bricks are delivered to a @4Storage&Yard. @PBrickworks make @56undesirable neighbors. @L@LClick @390here to find out more about bricks in ancient Egypt."
        }
    }
    message_building_warship {
        id: 365,
        
        size [30, 20]
        title {
            text: "Warship",
        }
        content {
            text: "Warships patrol the waterways, ramming or shooting at other ships that intend to inflict harm on the city.  Warships can also attack soldiers on land with missile fire, provided they are near the coast. A warship is berthed at a @356Warship&Wharf.  You can distinguish it from a transport by its lack of a rear cabin, and its trim style. @L@LAttack Priorities @LNo matter which order you give a warship, its captain always pursues the same agenda when attacking the enemy.  In order of importance, the captain's priorities are: @L@LTransport Ships with Enemy Soldiers on Board  @LThe captain knows that his mission has largely failed if enemy soldiers reach land.  If there are any transport ships carrying enemy soldiers in the city's waters, he attacks them first, before they can unload their invaders. @L@LDisembarked Enemies near the Shore  @LIf the captain fails to prevent enemy soldiers from making landfall, he sails near the shore and rains arrows on any disembarked invaders within range.  @L@LWarships  @LEnemy warships are his third priority.  If there are no transport ships with troops aboard or disembarked enemies, the captain tries to ram any enemy warships that are present.   @L@LEmpty Enemy Transport Ships  @LEmpty enemy transports are your captain's last priority.  He'll attack them if there is nothing else for him to assail. @L@LYour captain reacts quickly to changing situations.  He'll abandon a battle if a higher priority situation develops.  For example, if he is attacking a warship when a transport ship carrying enemy soldiers sails into the area he is protecting, he'll disengage the enemy warship and target the loaded transport.  @L@LWarship Orders @LGive a warship orders by right-clicking on it.  Warships can carry out the following orders: @L@LHold Position   @LWhen told to Hold Position, the warship will not budge from the spot you designate.  It defends itself by turning to face enemy warships to minimize the damage enemies cause by ramming, and attacks enemies in range by shooting arrows.  If several warships are lined up and all have been given the Hold Position order, the warships form a blockade with the goal of keeping invaders out.   @L@LEngage Nearby Enemies   @LWhen told to Engage Nearby Enemies, the warship attacks enemies within a small radius of its location.   @L@LSeek and Destroy All Enemies   @LWhen given this command, the warship patrols the water looking for enemies to defeat.   @L@LRepair   @LShould the warship be damaged in a conflict, clicking this button sends the ship to the Shipwright for needed repairs.  When the Shipwright is finished fixing the ship, it returns to its home wharf.  If the warship is severely damaged, the ship's captain will order it to the Shipwright for repairs on his own.  Shipwrights need wood to effect repairs.   @L@LReturn to Wharf   @LClicking on this option sends the ship back to its home wharf. @L@LTo simply tell a warship to move, click on it and then click on a new location.  When it arrives at the new spot, it will follow the last order given.  If you click on an enemy, the warship will pursue the targeted enemy until it is defeated or, if it is a land target, until it is out of range. @L@LClick @184here to read about combat in ancient Egypt."
        }
    }
    message_building_festival_square {
        id: 366,
        
        size [30, 20]
        title {
            text: "Festival Square",
        }
        content {
            text: "Before you can hold a festival (see @51religion for more on festivals), you must have a Festival Square in your city.  A Festival Square must be placed over a crossroads, but it does not require labor.  Each city can have only one Festival Square, and it makes a very @56desirable neighbor.   @PWhen no festival is in progress, the square is mostly deserted, although it does not affect traffic on the roads it was constructed upon.  Once the festival begins, people gather here from all over the city to enjoy the party.   @PThe ancient Egyptians held festivals to celebrate many different events.  Clicl @393here to find out more."
        }
    }
    message_figure_transport_ship {
        id: 367,
        
        size [30, 20]
        title {
            text: "Transport Ship",
        }
        subtitle {
            text: "Transport Ship",
        }
        content {
            text: "Transport ships carry your army across the river or over the sea to far-away lands.  Any company can board a transport ship, but a transport ship can carry only one company at a time. A transport ship is berthed at a @357Transport&Wharf.  You can distinguish it from a warship by its rear cabin and its trim style. @L@LTransport Ship Orders You can give transport ships specific orders.  To move a transport ship from one location to another, click on it and then click on a new location.  Right-click on the transport to issue any of the following commands: @L@LHold Position   @LThis commands the transport ship to stay where it is.  If the transport ship comes under attack, the captain will rotate the ship in an effort to reduce damage.  He will not, however, set sail to evade the attack.  This option should be used cautiously, because transport ships are not well-equipped to defend themselves.   @L@LEvade Enemies   @LTransport ships, especially those filled with your soldiers, are both valuable and vulnerable.  Click on Evade Enemies to give the transport ship's captain the ability to use all his powers to avoid attack.  The ship's captain always tries to Evade Enemies unless you tell him otherwise.   @L@LEmbark/Disembark   @LTo load a company of soldiers onto the transport ship, first click the Embark button, then click on the company of soldiers you wish to move over the water.  The soldiers will board the transport ship, and the ship will display the company's standard.  When you right-click on the transport ship, information on the company on board is displayed. @PTo return the soldiers to shore, click Disembark, then move the cursor to the location in which you wish to station the company. @PThe Embark/Disembark option toggles back and forth depending on whether there are soldiers currently on the transport ship.   @L@LRepair   @LIf the transport ship is damaged, click on repair to send the ship back to the @82Shipwright for repairs.  The ship's captain will bring his ship to the Shipwright on his own if the hull is severely damaged.  Shipwrights need wood in order to carry out the repairs.   @L@LReturn to Wharf   @LClick on this button to send the transport ship back to its @357Wharf."
        }
    }
    message_building_mausoleum {
        id: 368,
        
        size [30, 20]
        title {
            text: "Mausoleum",
        }
        content {
            text: "Mausoleums are large tombs used to inter pharaohs and nobility.   @PTo build a Mausoleum, supplies of sandstone and wood are needed, plus at least one working @363Carpenters'&Guild, @363Stonemasons'&Guild and @8Work&Camp. @PTo place a Mausoleum, there must first be a large quantity of sandstone stored in the city's @4Storage&Yards.  Once enough stone is stored, choose Mausoleum from the Religious Structures: Monuments list.  Place the Mausoleum, using the color of the footprint as a guide (all green means you can place the structure, red diamonds mean that some landscape feature prevents building it there).  Once you've designated a place for the building, peasants from the Work Camp clear the land and lay the foundation. @POnce the foundation is in place, stonemasons begin work.  Whenever a Storage Yard accumulates four blocks of sandstone, peasants load the stone on a sledge and drag it to the construction site.  Stonemasons put the stone in place until the first story is completed.  Then, carpenters install wooden ramps so that the stonemasons can work on the second story of the Mausoleum.  When the second story is complete, the Mausoleum is finished. @L@LRead about the history of these tombs by clicking @396here."
        }
    }
    message_figure_construction_foreman {
        id: 369,
        
        size [30, 20]
        title {
            text: "Construction Foreman",
        }
        content {
            text: "Once monument construction begins, the Construction Foreman provides detailed information on the status of the monument.  He keeps a running tally of how much of each construction material is needed to complete the monument.  If construction is not running smoothly, he can tell you why.  To visit the Construction Foreman, right-click on the monument site."
        }
    }
    message_building_monument_construction {
        id: 370,
        
        size [30, 20]
        title {
            text: "Monument Construction",
        }
        content {
            text: "To successfully complete most missions, you will need to build at least one monument.  Some missions will require you to build several.  You can build the needed monuments in any order you choose. @PFor most monuments, @363Construction&Guild workers wait at the monument site for peasants from a @8Work&Camp to deliver needed supplies from a @4Storage&Yard.  Peasants will walk as far as they must to reach the monument site.  The @362Sphinx and @372Obelisk are constructed a little differently. @G75 @PYour city's laborers can work on more than one monument at once, and you might be tempted to order them to do so.  Be forewarned, however, that such a plan might not be as wise as it first appears.  Inefficiency can creep in when @363stonemasons and block haulers fail to coordinate their work.  Peasants might deliver construction materials to one monument site while the stonemasons wait, idle, at the site where they would prefer to work.   @PThis situation frustrates the @373Overseer&of&Monuments deeply, but it is harder than you would think to reconcile the block haulers' inflexible orders with the stonemasons' independent attitudes.  It is best to avoid such conflict altogether by ordering your city's monuments to be built sequentially, rather than simultaneously. @PBecause of their immense size, some monuments can be especially difficult to place in your city.  For the largest monuments, you won't be able to see the entire footprint of the structure at one time. @PTo assess a selected location for a monument, press the 'M' key.  The monument's footprint will freeze in the spot you selected, and you can move your viewpoint around the city as normally.  To place the monument in the selected location, provided it's a viable one, click the mouse button.  To continue to look for a suitable spot, press 'M' again.  The monument's footprint will again follow your cursor around your city. @PIn addition, some monuments must be built into cliffs. These monuments are @492Abu&Simbel and the @478Royal&Burial&Tombs.  @PFor more on monuments, read the individual entries on each. The are listed in the Help menu. @L@LTo find out more about the history of monuments, click on any of these: @391sphinx, @392pyramids, @394mastabas, @493Abu&Simbel, @481Alexandria's&Library, @482Caesareum, @475Valley&of&the&Kings and @396other&monuments."
        }
    }
    message_building_mastaba {
        id: 371,
        
        size [30, 20]
        title {
            text: "Mastaba",
        }
        content {
            text: "Mastabas are fine tombs built for nobility. You will sometimes choose a mastaba for your own final resting site. @PTo build a mastaba, you'll need a large supply of @364bricks and a @363Bricklayers'&Guild. You'll also need peasants from @8Work&Camps. @PThe first step to building a mastaba is choosing a site. You'll know that you've picked a viable site if you see a green 'ghost' of the footprint of the mastaba. If the green footprint contains any red diamonds, some feature of the landscape prevents construction there.  Click the mouse button when the footprint is all green, and the mastaba's location will be locked in. Stakes mark the corners of the site. @PAfter the site is established, bricklayers and peasants get to work. Peasants drag in sledge-loads of bricks, and your bricklayers put them in place. @PThe deceased need many things in the Field of Reeds, so you will likely need to furnish the mastaba with @374burial&provisions. Your @373Overseer&of&Monuments will tell you which goods are required. Check in with the @369Construction&Foreman to find out the construction status of the mastaba. Click @370here for more on monument construction. @L@LClick @394here to learn more about mastabas in ancient Egypt."
        }
    }
    message_building_obelisk {
        id: 372,
        
        size [30, 20]
        title {
            text: "Obelisk",
        }
        content {
            text: "Obelisks symbolize the rays of the sun, and great deeds and achievements are commemorated on the sides of the monument. @PObelisks are made from a large amount of @95granite, and all the granite needed for the Obelisk must be stored in the city's @4Storage&Yards before you can place the monument. @PMove the cursor over the land to pick a location for the Obelisk.  If you see an all-green footprint of the monument, you can place the obelisk.  If the footprint contains any red diamonds, some feature of the landscape prevents building the obelisk there.   @PAfter you pick a location, the granite is put into place.  Then, carpenters from the @363Carpenters'&Guild build scaffolding around the monument, and @363stonemasons come to the monument to carve intricate designs into it.  You do not need the services of peasants to build an Obelisk. @PRight-click on the monument to visit the @369Construction&Foreman.  He will update you on the status of the monument. @L@LObelisks have been reaching towards the sky for thousands of years. Click @397here to find out more about this ancient monument."
        }
    }
    message_overseer_monuments {
        id: 373,
        
        size [30, 20]
        title {
            text: "Overseer of the Monuments",
        }
        content {
            text: "Your Overseer of the Monuments can tell you what is preventing construction from starting on a monument.  He also manages the dispatch of @374burial&provisions to any tombs that may require them.  For a progress report on actual monument construction, right-click on the project to visit the Construction Foreman."
        }
    }
    message_burial_provisions {
        id: 374,
        
        size [30, 20]
        title {
            text: "Burial Provisions",
        }
        content {
            text: "To ensure that the deceased has all he or she needs in the afterlife, you must stock most tombs with burial provisions.  Burial provisions are materials that the deceased used while alive.  You may also need to provide materials for the construction of special accouterments needed for the afterlife, such as a funeral barge and sarcophagus.  Monuments are not complete until you supply any required burial provisions.  The @373Overseer&of&Monuments has a list of the necessary items and quantities.  When you are ready to send them, tell the Overseer of Monuments to dispatch goods to the tomb. @PYou do not have to have the full amount of the required material in the @4Storage&Yards before you can send goods to the monument.  You can send smaller portions of the required commodity until you fulfill the requirement. @PYour city may need to @47import some burial provisions. @L@LThe ancient Egyptians buried a lot of different objects along with the deceased's body. Click @395here to find out what supplies the ancient Egyptians took with them to the afterlife."
        }
    }
    message_building_stepped_pyramid {
        id: 375,
        
        size [30, 20]
        title {
            text: "Stepped Pyramid",
        }
        content {
            text: "Stepped Pyramids, the first Pyramids built in Egypt, are giant staircases to the sun.  They are made entirely of @95plain&stone, although wood is required for building ramps to carry stone up to the higher levels of the Pyramid.  To build ramps and lay the stone, you'll need a @363Carpenters'&Guild and a @363Stonemasons'&Guild.  Peasants are also needed to pull the huge sledge loads of stone over to the construction site.  Once four blocks of plain stone are stored in the @4Storage&Yards, and the stonemasons are ready, peasants begin their arduous journey to the monument site. @PStepped Pyramids come in five different sizes: small, medium, large, Pyramid Complex and Grand Pyramid Complex.  Visit the @369Construction&Foreman and the @373Overseer&of&the&Monuments for more information. The entry on @370monument&construction may also be helpful. @L@LClick @392here to find out more about the vizier Imhotep's innovation: the Stepped Pyramid."
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
            text: "Osiris, Sebek and Min",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Osiris' role in Egyptian religion changed over the millennia. He, along with his wife and sister Isis and brother Seth, was one of the earliest gods and a member of the Eannead (see @399religion for more on the Eannead). @L@LThe myth that defines Osiris links him with agriculture, the Nile and funerary customs. Ra-Atum gave Osiris rule of ancient Egypt. Osiris married his sister, Isis, and taught the people many things as its ruler, most importantly the art of agriculture. After he schooled the Egyptians, Osiris left Egypt to civilize the rest of the world, leaving Isis in charge. Isis ruled well in his absence, but upon Osiris' return, his brother, Seth, began to plot against him. Seth invited Osiris to a sumptuous feast where he produced a beautiful coffin. He offered the coffin to whomever it best fit. When Osiris climbed in the coffin, Seth shut the lid and threw the coffin into the Nile. Isis managed to fish the coffin out of the Nile, but Seth caught her and hacked Osiris to pieces. Isis, distraught, cried, and her tears were believed to be the cause of the Inundation. Eventually, Isis gathered up the scattered pieces of Osiris' body except his genitalia, which had been consumed by the oxyrhynchus fish. Isis bandaged Osiris together with linen, much as mummies were bandaged. Egyptians were, understandably, banned from eating the oxyrhynchus fish. Eventually, Osiris became the god of the underworld and was the supreme judge who granted or denied entry into the afterlife. @L@LSebek, the crocodile god, was a fertility god who was worshipped primarily in the Fayuum, although he was known throughout Egypt. His name translates as 'watching over you.'  Min, god of regeneration, was also associated with male fertility and worshipped throughout Egypt."
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
            text: "Ra, Ma'at and Horus",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ra was viewed as the chief god throughout much of Egypt's history. As the forefather of all the gods in the Ennead, he was the ultimate creator god and associated with the sun. @L@LMa'at was the goddess of justice, also associated with truth and order. The ostrich's feather she wears on her head is used during the weighing of the heart, the last step that individuals must undertake before they enter the afterlife. @L@LHorus was most closely associated with the pharaohs. He was the son of Osiris and Isis and avenged his father's death by exposing Seth as the killer of Osiris. Horus was represented by a falcon. "
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
            text: "Ptah, Amon and Thoth",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ptah is god of the craftsmen and associated with the Men-nefer (Memphis) pharaohs who first united Egypt (see @399 religion for more on the Men-nefer pharaohs' effect on Egyptian beliefs). He was especially revered by the craftspeople at Deir El-Medina who built the tombs in the Valley of the Kings and Valley of the Queens. @L@LAmon was a sun god, particularly associated with the sun at morning. He came to prominence during the Twelfth Dynasty when Waset (Thebes) kings assumed control of Egypt. @L@LThoth was god of wisdom and learning and considered to be scribe to the other gods. He was most closely associated with Khmun (Hermopolis)."
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
            text: "Seth, Anubis and Sekhmet",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Seth, brother of @376Osiris, was god of destruction. Originally, Seth was the protector of Lower Egypt. As Upper Egypt gained prominence, Upper Egypt's patron god, @377Horus, became more important, and Seth was cast in a negative light. @L@LAnubis, god of death, was the embalming god. Represented by the jackal, Anubis protected the dead. @L@LSekhmet was a lion-headed goddess of war. Wife of Ptah, she destroyed what he created. The Egyptians worshipped her in the hopes of appeasing her so that she would not unleash her fury."
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
            text: "Bast, Isis and Hathor",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Bast, a cat-headed woman or lioness, was goddess of the home as well as cats, fire and pregnant women. She protected the home both through docile and aggressive means. She was also the patron goddess of Bubastis. @L@LIsis, wife of @376Osiris and mother of @377Horus, bandaged Osiris' broken body back together. As a result, she was viewed as the goddess of healing. She was represented by a woman and is often depicted with her son. @L@LHathor was goddess of joy, love and festivity. Represented by a cow, she was the patron goddess of Iunet (Dendera), Men-nefer (Memphis), Qis (Cusae), and Perhathor (Gebelein)."
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
            text: "History",
        }
        content {
            text: "Malaria was one of the risks of living near marshes. Malaria in humans is caused by any of four parasites carried by the anopheles mosquito, which is primarily active at night. The onset of malaria is marked by fever, which is followed by muscle aches, sweating and fatigue. One of the malaria-causing parasites produces severe cases that can lead to death. @L@LTo prevent potentially fatal and, at the very least, annoyingly itchy mosquito bites, ancient Egyptians used mosquito netting on their beds. Herodotus, a Greek historian, also notes that the Egyptians elevated their beds onto towers to sleep, believing that mosquitoes could not fly at that height."
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
            text: "Jewelry",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Jewelers took precious and semi-precious stones and manufactured them into necklaces, beaded collars, belts, and other adornments. To string the beads, the jewellers first drilled a hole in the stone using a hand drill with a flint bit. Once the holes were drilled, string was threaded through and fastened. Jewelers were also adept at using gems in inlays. @L@LFrom depictions on tomb walls, dwarves were frequently employed in the jewelry making industry."
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
            text: "Hunting",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Compared to the food grown on farms and raised on ranches, hunting contributed little to Egyptian food stock. Still, hunting was enjoyed by the upper class, and many pharaohs bragged about their skills as hunters. Gazelles, antelopes, ibex, oxen, sheep and ostriches were the main targets of hunters, although some hunted hyenas, lions and leopards for sport (and for their hides in the case of leopards and lions). Hunters used bows and arrows, lances, or spears to kill their quarry. @L@LThe Egyptians were equally fond of hunting water-based animals, including fowl and hippopotamus. Groups of men hunted the hippopotamus together with a special spear that was attached to a rope. Several men tried to hit the hippopotamus with the spears. Once enough damage had been inflicted, the men dragged the hippopotamus to shore using the rope. @L@LFowl were killed with throwing sticks, which are a little like Australian boomerangs. The hunter's helpers, either family members or servants, collected the felled fowl. Birds were also trapped in nets that were laid down on a field. The net was sprinkled with food for the birds. Once attracted to the spot, the net's corners were pulled together with the birds trapped inside."
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
            text: "Priests",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "A significant portion of the ancient Egyptian population were priests. Their role extended far beyond religious duties. Because ancient Egypt was a theocracy, priests frequently assumed administrative roles within their communities, sometimes dispensing justice. @L@LThe mark of a priest was his cleanliness. The priests underwent purification rites before they could enter the temple and shaved off their hair to ensure they did not harbor lice or other impurities. Depending on which god a priest served, he was prohibited from eating certain types of food. Priests had special clothing and were also required to wear white sandals. The highest ranking priests sometimes adorned themselves with leopard skins. @L@LThe primary religious concern for the priesthood was the care and feeding of the resident god. Each temple had a statue of its patron god on the premises. Each priest in the temple had his own responsibility to make sure the god was happy. Some of the priests were in charge of making sure the god was well fed. Using food that had been given as an offering by locals or produced on the temple's estate, the priests prepared a meal for the god. The god would partake of the 'essence' of the food, and the priests ate the leftovers. The priests also clothed and bathed the god and provided entertainment. Occasionally, the god would be taken on an outing and paraded through the village (see @393festivals for more). @L@LThe priesthood was divided into distinct classes. The most elite priest was the High Priest, also called the First Prophet, who was appointed by the pharaoh. The High Priest was the ultimate authority within the temple and frequently served as an advisor to the pharaoh. Beneath the High Priest were the Deputy High Priests, or Second Prophets, who oversaw particular functions of the temple or its estate, such as the workshops or the farms. Beneath them were the priests responsible for particular functions like bathing the god or providing entertainment. Most priests served in shifts, working one month out of every three."
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
            text: "Stonemasons",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Stonemasons oversaw the @193quarries and construction of @392pyramids and other monuments. While they knew the ins and outs of stone and how best to extract it from the quarries, they themselves did not do most of the backbreaking labor. Peasants of the lowest class and sometimes slaves performed the hardest labor. Stonemasons supervised the process. In addition to large construction projects, the stonemason's expertise was required for smaller undertakings, such as laying the foundation of a house."
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
            text: "Bricklayers",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Brick laying technique has not changed very much over the millennia. The supplies are essentially the same: @390brick and mortar for binding. In ancient Egypt, mortar was made from a mixture of clay, sand, straw and chaff. The bricklayers spread the mortar with a wooden trowel and put the brick in place. They used plumb lines to ensure that the walls they built were straight."
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
            text: "Scribes",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Scribes, or sesh, permeated throughout Egyptian society and government and were associated with just about every action the government took. The ancient Egyptians kept records of almost everything, and scribes were the only ones who could perform this function. Scribes recorded how much tax each person owed the government, kept track of exports and imports and even went to battle with soldiers to record events. For private citizens, scribes drew up legal documents, like wills, and also read and wrote letters for individuals. @L@LThe tools of the trade for the scribe included papyrus, a palette with two cakes of ink (typically black and red), a pot of water, and reed brushes. The scribe dipped the brush into the water and then rubbed the brush over a cake of ink. He then wrote on the papyrus. @L@LVery few scribes knew how to write hieroglyphics. Hieroglyphics were reserved for monuments and temples. For daily use, a simpler version of hieroglyphics, called hieratic, was used.  @L@LThe written language consisted of about 700 signs and combined symbols that represented sounds with symbols that represented ideas. The script omitted vowels, so historians can only speculate on how ancient Egyptian sounded."
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
            text: "Immigration",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egypt enjoyed a relatively stable economy and generally steady food production due to the Inundation. Egypt's neighbors knew this, and many residents of neighboring lands immigrated to Egypt. @L@LSome of Egypt's immigrants came to engage in trade. Archaeological evidence in major port cities such as Memphis reveals the existence of non-Egyptian settlements. These non-Egyptian merchants are depicted on Middle Kingdom and New Kingdom tombs. Some residents from neighboring countries, such as Libya, sprawled into ancient Egypt. By the twelfth dynasty, Libyans occupied large portions of the western Delta, and soon spread to the eastern Delta. @L@LSome came to Egypt with less than noble intensions. @181Invaders of Egypt often remained, even after their power had been lost. Many of those that stayed behind seem to have enjoyed the same rights as Egyptians, and some held high posts within the Egyptian government."
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
            text: "Carpenters",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Carpenters fashioned many necessary objects for the Egyptians. Native @192wood was scarce, so carpenters were very efficient with the wood they had at their disposal. Imported wood was also used, but it was expensive and thus reserved for the wealthiest of citizens. @L@LCarpenters were equipped with axes, saws and adzes to turn logs into planks of usable wood. With axes, the carpenter trimmed off any branches from the logs and split the wood if he was making rafters. Saws were used to cut the logs into planks, and adzes to smooth the planks of any bumps. @L@LFinished products included chests, beds, doors and door frames, chairs and, perhaps most importantly, coffins. Instead of nails, dowels were used to hold finished pieces together. Some of the finished pieces were exquisite, with fine inlays and engravings decorating the surfaces. @L@LCarpenters were also needed for the construction of larger homes. Ceilings in wealthier houses were frequently supported with finely decorated wooden columns. @L@LBasic carpentry changed little over ancient Egyptian history, and the same basic tools were favored. The major innovation carpentry witnessed was the development of the drill. During the New Kingdom, a bow drill was used to drill holes for the dowels."
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
            text: "Bricks",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Bricks were an ideal building material for the ancient Egyptians. Because they did not conduct heat well, brick homes remained relatively cool inside during the hot summer. Bricks were manufactured by combining clay and straw. The clay was moistened, mixed with straw and then submerged in water. While submerged, the straw began to decompose, and in so doing excreted a slime that held the brick together. The brick was then dried in the sun. When the bricks were ready, the @386brick@layers could begin their work."
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
            text: "Sphinx",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "The Sphinx, associated with Amun in ancient Egypt, has the body of a lion and the head of a king. There were many Sphinxes in Egypt, but the most famous by far is the Great Sphinx at Giza (Rostja).  @L@LBuilt around 2500 BC, the Great Sphinx seemingly guards Khafre's pyramid and sits over an old quarry. Its face is thought to be that of Khafre himself. The Sphinx is about 200 feet (60 meters) long and 65 feet (20 meters) tall. It is carved from soft sandstone. @L@LThe Sphinx was buried in sand for most of its existence. Legend has it that Thutmose IV, before he became pharaoh, was hunting in the area of the Sphinx and fell asleep on the spot where it lies. As Thutmose slept, the Sphinx told him that if he unburied the Sphinx, he would become pharaoh. Thutmose did the Sphinx's bidding and became pharaoh in 1425 BC. He recorded the story on stelae and placed it between the Sphinx's paws. @L@LThe Great Sphinx was again buried and finally uncovered for good in the 1930s. Attempts to preserve the Sphinx have met with mixed results."
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
            text: "Pyramids",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "People have speculated for centuries on how the pyramids were built. It seems unfathomable that the ancient Egyptians, without the benefit of forklifts, cranes, backhoes and a slew of other modern equipment, could have constructed such magnificent structures. @L@LThe building of any pyramid started with a well laid-out plan. The vizier, second only to the pharaoh in rank, most likely oversaw the entire process with the royal architect (known as medjeh nesu in ancient Egyptian) specifying the plans. The royal architect was responsible for choosing material and figuring out how to get the material to the site. @L@LAfter the site was carefully chosen, astronomers determined the north-south axis of the pyramid. Then, surveyors laid out all sides of the pyramid using a special kind of cord that was so thick that it would not stretch and ruin the dimensions of the pyramid. Then, the ground was leveled, perhaps by filling ditches with water to determine a uniform plane. @L@LOnce these tasks were complete, construction was ready to begin. To kick off construction, a ceremony was held in which the pharaoh marked the corners of the pyramid with stakes, stretched a cord between the stakes, and placed a ceremonial mud brick as the first stone in the monument. @L@LAt this point, the @385stonemasons and @155laborers took over. Stonemasons carved out the underground rooms, including the burial chamber. Once these were ready, the arduous process of bringing stone blocks, some of which weighed as much as 2.5 tons, began. The stones were hauled on sleds, and ramps were probably used to reach the higher parts of the pyramid. In addition to the rough-hewn stones that made up the interior of the pyramid, finer stone encased the structure. @L@LSome pyramids stood alone, but more frequently they were part of larger pyramid complexes. The pyramid complex featured a valley temple that sat on the water or on the edge of the cultivated area. From the valley temple, a long causeway led to the mortuary temple, which was situated on the east side of the pyramid. @L@LThe form of pyramids evolved as the technology to build them was refined. The first pyramid, Djoser's Step Pyramid, does not have smooth sides. Built around 2620 BC, the Step Pyramid is a series of squares stacked on top of each other. The first true pyramid is Snofru's, built around 2550 BC. An outer casing smoothed the 'steps' of the pyramid, and this practice was soon adopted for other pyramids. The largest pyramid is Khufu's, which measures 252 x 252 yards (230 x 230 meters) and reaches heights of 160 yards (146 meters). One unique pyramid is Snofru's Bent Pyramid. The angle of the sides of the pyramid changes about two-thirds of the way to the top. The speculation is that architects determined that the pyramid would be too heavy and prone to collapse if it was continued at its original angle. And because Snofru's first pyramid collapsed, he probably thought he was better safe than sorry."
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
            text: "Festivals",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ancient Egyptian festivals were joyous celebrations in which food was abundant and beer flowed freely. They celebrated for many different reasons: to honor a god, to mark the harvest and to recognize the longevity of the pharaoh. The last five days of the Egyptian year were spent celebrating, and numerous other festivals occurred throughout the year. @L@LIt was during festivals in honor of a deity that all people had direct access to their gods. At the center of religious festivals was the procession of the god. During the festival, the statue of the god that resided in the temple, beyond public view, was outfitted in its finest garments and paraded through town on a ceremonial bark borne by priests. The priests rested periodically, during which time rites were performed. During the New Kingdom, citizens could ask the god questions while the priests were resting. The priests bowed if the god responded positively to the question and moved back if the response was negative. At the end of the festival, the god returned to his home in the temple. @L@LSometimes, the gods travelled quite far and were transported by boat. For example, during the opet festival, Amun travelled from Karnak to his southern chapel at Luxor. To make the journey, he sailed along the Nile. Opet was one of the most joyous festivals and lasted anywhere from 11-27 days. @L@LIf a pharaoh was healthy enough to serve for 30 years, the heb-sed festival was held. Celebrated during the pharaoh's 30th year of rule and every three years thereafter, the festival featured the pharaoh performing a ritual run to prove he (or she) was still fit to rule. Some pharaohs didn't wait for 30 years to have a heb-sed and held them much earlier in their reigns. @L@LUndoubtedly, Egyptians from all walks of life welcomed festivals as a time to eat and drink very well. Festivals also offered respite from the daily grind."
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
            text: "History",
        }
        content {
            text: "The earliest Old Kingdom pharaohs and nobility were buried underneath mastabas. Mastabas covered the shaft that led down to the tomb chamber. They started rather simply, as low structures with text inscribed on them, but developed into larger structures, complete with chapels. Mastabas are viewed as the forerunners of pyramids, and Djoser's Stepped Pyramid may have begun as a mastaba."
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
            text: "Burial Provisions",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Tombs were well appointed with everything the deceased would need in the afterlife. Known as burial provisions, these commodities included the tools of the deceased's profession, food, toiletry, jewelry, musical instruments, makeup - basically anything that the deceased had ever used in life. Tombs were also equipped with shabtis, or 'answerers.'  These statuettes were included in the tomb just in case the deceased was asked to perform labor in the afterlife. The shabti would do the work in place of the deceased."
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
            text: "Other Monuments",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "In addition to @397obelisks, @394mastabas, @392pyramids and @391sphinxes, ancient Egypt had many other monuments. Among these were mausoleums and Temples of the Sun.  @L@LThe sun was viewed as a giver of life in ancient Egypt, and many Temples of the Sun were built throughout Egypt, particularly in the Fifth Dynasty. The most notable sun temples are at Abu Ghurab. Two sun temples were located here and were the scenes of animal sacrifice. @L@LMausoleums and chapels were frequently placed over tombs to serve as a place where the family of the deceased could make offerings. These offerings ensured that the deceased would continue to enjoy the afterlife. Anyone who had the resources would build these chapels for their family members, and personal mausoleums abound in the Egyptian landscape."
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
            text: "Obelisk",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Obelisks were associated with the sun, representing either the sun's rays or the primordial mound upon which the sun first shone. Made from granite and engraved with hieroglyphs, obelisks were found outside temples, generally in pairs. @L@LThe shape of the obelisk was hewn at the quarries, and an unfinished one at Aswan reveals much about the process of quarrying such a large piece of rock. Workers used pounders of dolerite to slowly carve out the needed shape. The obelisk at Aswan was abandoned because a fissure developed in the center of the stone. @L@LOnce the obelisk was hewn from the rock, no one is quite sure how they were erected. Modern attempts at raising obelisks using what is believed to be ancient methods have failed."
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
            text: "Linen and Weaving",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Made from @189flax, linen was the predominant textile in ancient Egypt. While some cloth was made from wool or hemp, this cloth was considered to be much inferior to linen. @L@LTo make cloth, flax fibers had to first be spun into thread. Seated in front of piles of flax, spinners twisted the fibers together and wound them into balls. Then, the thread was attached to spindles, and weaving would begin. @L@LThe Egyptians used a horizontal loom placed on the floor. The weavers threaded the loom with two parallel rows of thread (the warp). Two workers sat at either side of the loom and sent the threaded shuttle (the weft) back and forth to make cloth. @L@LDuring the New Kingdom, a vertical loom replaced the horizontal loom. The vertical loom allowed weavers to sit more comfortably on stools. @L@LThe majority of weavers were women who were frequently part of the pharaoh's harem."
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
            text: "Religion",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Egyptian religion featured a well-populated pantheon of major and minor gods. Most cities, and even individuals, viewed a specific god as their patron, and this practice influenced which gods held the most importance. @L@LOne of the earliest belief structures was the Eannead, or group of nine gods. Founded in the city of On (Heliopolis), the first god in the Eannead is Atum, who linked with Ra to become Ra-Atum. Ra-Atum, though male, managed to give birth single handedly to twins, Shu and Tefnut. Shu was god of the air, and Tefnut was goddess of world order. Shu and Tefnut had four children: Isis, Osiris, Nephthys and Seth. Rounding out the nine gods is Horus, son of Isis and Osiris. Ra was eventually thought of separately from Atum and became the chief god of the Ennead. This system of gods dominated pre-Dynastic Egypt, and Ra continued to be an important god to the ancient Egyptians.  @L@LWhen Hor-Aha united Upper and Lower Egypt, his personal belief in Ptah, a creator god, changed the belief system. Hor-Aha maintained that the Eannead gods were all manifestations of Ptah. Still, Ra was the predominant god. @L@LAnother theory sprung from the Upper Egyptian city of Khmun (Hermopolis). The Hermopolitans believed in an Ogdoad, or group of eight gods. In the Ogdoad, a pair of male and female gods represent different aspects of the world. Nun and Naunent represented water, Huh and Hauhet represented unendingness, Kuk and Kauket were the darkness gods, and Amon and Amaunet were the air gods. @L@LIn the New Kingdom, Amon unseated Ra as the primary god. Amon's domination continued until the reign of Akhenaten. Akhenaten attempted to introduce monotheism into Egypt, maintaining that Aten, who was embodied by the sun's disk, was the only god. During his rule, known as the Armana period, Ahkenaten closed down the temples to other gods. Upon his death, however, polytheism was quickly reintroduced, and the temples to other gods were reopened."
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
            text: "A Village is Born",

        }
        content {
            text: "@PWelcome to ancient Egypt, land of the Pharaohs! Here you'll participate in the history of one of the greatest civilizations the world has ever seen, in an epic story that spans more than fifteen centuries and two dozen generations. You must lead one family, generation by generation, from its earliest beginnings in Egyptian pre-history, through the dawn of civilization...to the establishment of a unique and powerful empire...and beyond.     @POur story begins more than five thousand years ago, along the banks of the Nile river, in an area known as Naqada.  Here a small confederacy of clans struggles to eke out an existence in the harsh environment. With you at its head, your family leads this small settlement."
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
            text: "The Dawn of Civilization",

        }
        content {
            text: "@PAfter many years, and the passing of a generation, your family has resettled in the area of Thinis, in Upper Egypt. Here, a small band of local rulers is attempting to extend its influence over Lower Egypt, and all lands along the river Nile, and to unite this realm under its own house, with one supreme leader.   @PEstablishing Thinis as a thriving city, like nothing ever seen before, will prove the worthiness of the Thinite confederacy, and help them gain supremacy over Lower Egypt and the other factions vying for power. In time, this will mean providing the population with entertainment, and building wonderful temples to worship the region's patron deity. @PTo build a city this grand will require a substantial supply of cash. You'll find rich deposits of gold ore in Thinis, and harvesting them should be your first priority. "
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
            text: "The Thinite nobles still struggle to unite the lands of the Nile under one supreme ruler.  To aid them in their cause, it is hoped that you will endeavor to establish a thriving community at Buto, in the humid Delta region of Lower Egypt, thus spreading their influence throughout the length of the sacred river.  To support a population larger than that of a village, you must learn to use agriculture. @PEgyptian farmers have begun to exploit the rich, fertile soil deposited by the annual inundation of the Nile river for growing crops.  The Nile can be hazardous, however.  Many dangers lurk along its banks and in its waters, such as deadly crocodiles, hippopotamuses and malaria-carrying mosquitoes."
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
            text: "The First Pharaoh",

        }
        content {
            text: "As the people who live along the Nile still struggle to survive in this harsh environment, a local king named Narmer has risen to power.  Though Narmer has dominion over much of this land, full unification of the twin kingdoms has yet to be achieved.  In commemoration of his accession, Narmer wishes your family to establish and govern a new city at Hierakonpolis.  This city will have temples to many of the gods of Egypt and numerous places of entertainment."
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
            text: "A Capital is Founded",

        }
        content {
            text: "After a lengthy struggle, King Hor-Aha has managed to unite the twin kingdoms of Upper and Lower Egypt, and proclaimed himself Pharaoh over all Egypt!  As a sign of his absolute sovereignty, and the establishment of this, the first dynasty of Egypt, Hor-Aha has ordered the founding of an imposing capital at Memphis, from which he may govern this fledgling nation.  Because of your family's many generations of faithful service to this land, Pharaoh has chosen you to be the architect of this splendid city.  Because the capital is the very symbol of our Kingdom, its citizens must enjoy a quality of life heretofore unknown in this land.  To this end you will eventually need to trade with other cities in the realm, and to provide a higher standard of education for at least some of your citizens.  You must also build a sacred mastaba tomb for the city's nobles."
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
            text: "An Expedition to Sinai"
        }
        content {
            text: "A new Pharaoh, Den, has taken the throne of Egypt.  Pharaoh is deeply concerned, as enemies have begun to threaten our borders, and our nation lacks adequate supplies of valuable copper needed to create weapons with which to equip our troops.  Pharaoh Den has ordered a mining expedition into the unforgiving land of Sinai, beyond our borders and deep within Bedouin territory.  The area known as Timna is rich in gold and copper ore, as well as precious turquoise gemstones, but it is otherwise barren.  Conditions there will be harsh, and you'll need to import many amenities, perhaps even additional food and fine linen, from Egypt.  Pharaoh will demand frequent shipments from Sinai and will ask you for money, copper, gemstones and weapons.  You can use any surplus of these items to help support the expedition.  Be always on your guard, for the Bedouin of the Sinai desert are formidable adversaries, and they will not willingly allow foreigners to occupy their land, let alone plunder their mineral wealth. @PTo lighten the burden that such living conditions impose on your city's people, build a Pavilion at some busy intersection.  Citizens can relax at the Pavilion's juggling and music stages, and, if you also build a Dance School, this new type of performance will provide great entertainment. "
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
            text: "Pharaoh's Navy",
        }
        content {
            text: "Egypt's military troops are now unmatched in the known world, but the new Pharaoh, Khasekhemwy of the second dynasty, now also demands a powerful navy based at Apollinopolis.  Nothing less than a fleet of warships will suffice to allow us dominion over the high seas, but timber is scarce, as our climate supports only a few sparse areas of forest.  Cedar may be imported at great cost from Byblos, in the land of Lebanon to the northeast.  Fortunately, exports of our native papyrus will provide a means of offsetting this expense."
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
            text: "The Challenge of the Sea ",

        }
        content {
            text: "Abydos, the burial place of our forefathers, has grown over the years into a sprawling necropolis of sacred tombs.  Now, most noble men and women wish to make this their eternal resting place.  To honor them, the new Pharaoh Khasekhemwy of the second dynasty has ordered the construction of three sacred mastaba tombs (one of greater size than the other two) for the local nobility.  @PPharaoh has also ordered the creation of a powerful navy, based at Apollinopolis.  Abydos, too, must support a modest fleet of combat ships, if our shores are to remain totally secure.  This will not be easy, as timber is scarce, and our climate supports only a few sparse areas of forest.  Cedar may be imported at great cost from Byblos, in the land of Lebanon to the northeast.  Fortunately, exports of our native papyrus will provide a means of offsetting this expense."
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
            text: "The Road to Africa",

        }
        content {
            text: "@PA new Pharaoh, Nebka, has been proclaimed, heralding the beginning of the third dynasty of Egyptian rulers.  Nebka has brought great organization and structure to Egypt, ordering that all our realm be divided into districts, or nomes, each governed by a local ruler called a 'Nomarch'.  Though this system may seem rigid, under his leadership Egypt has grown and prospered, and made many great achievements in art and architecture.  @L@PMerchant caravans, travelling oasis by oasis from deep within the African interior, have begun to provide Egypt with many rare and exotic luxury goods, now prized by our people.  Unfortunately these caravans are routinely attacked by warriors from Libya, and even by Bedouin of the Eastern Desert.  To secure these trade routes, Pharaoh Nebka, He of the Sedge and Bee, wishes you to establish a military post at the Selima Oasis, the hub of the caravan trade, far beyond the borders of our realm.   @L@PThere you will find some trees suitable for timber, the sale of which will help you raise money to fund the establishment of this outpost.  To forge weapons, you may obtain copper from our newly established mines at Timna, in the land of Sinai. @L@PFrom the Selima Oasis, you may import ebony from the African nation of Kerma.  Once you have succeeded in establishing this outpost, it shall provide a reliable source of ebony for all the cities in our realm."
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
            text: "The Nubian Border",

        }
        content {
            text: "@PA new Pharaoh, Nebka, has been proclaimed, heralding the beginning of the third dynasty of Egyptian rulers.  Nebka has brought great organization and structure to Egypt, ordering that all our realm be divided into districts, or nomes, each governed by a local ruler called a 'Nomarch'.  Though this system may seem rigid, under his leadership Egypt has grown and prospered, and made many great achievements in art and architecture.   @PPharaoh wishes to extend the borders of our realm further south, into Nubia.  He orders that a city be founded at the first cataract of the Nile, on the island of Elephantine, that we may take advantage of the abundant deposits of gemstones, granite and sandstone to be found there.   @PThe growing necropolis of Abydos demands these materials for the creation of more and more elaborate tombs for the nobility.  The capital at Memphis, too, may have need of bricks for the construction of tombs, and Pharaoh Nebka may approve requests for these and other building materials.   @PPharaoh Nebka has also ordered that one of your peers establish a military post at the Selima Oasis, to secure the caravan routes into the African interior.  Once it has been established, you may look to the Selima outpost as a source of imported ebony, a highly prized luxury good."
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
            text: "The First Pyramid",

        }
        content {
            text: "The accession of Pharaoh Djoser to the throne of Egypt has ushered in a new era of wisdom, learning and artistic achievement.  A royal cemetery is to be established at Saqqara, to serve as the eternal resting place for nobles such as Hezyre and Khabausokar, Pharaoh's trusted courtiers.   @PBut this site shall also contain a monument the like of which the world has never seen before.  I, the Pharaoh's royal vizier Imhotep, have conceived a new form of sacred tomb for Pharaoh.  Unlike the low mud brick mastabas of prior Pharaohs, this tomb shall rise toward the heavens, as if it were comprised of several mastabas, placed one on top of the other.  And what's more, this 'stepped pyramid' shall be constructed entirely of stone, that it may endure the passage of the eons.  Deep within, a sarcophagus of solid granite shall hold Pharaoh's body for his eternal rest. @PPriests at the necropolis of Abydos have perfected the art of using linen to embalm the dead, thus opening the door to everlasting life to all Egyptians.  @POur trading post at the Selima Oasis still thrives, and from there you may import ebony from Africa.  @PPharaoh has given you a generous supply of cash to get started on this project.  Do not let him down."
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
            text: "The Bedouin of the East",

        }
        content {
            text: "Like Den before him, Pharaoh Huni has ordered an expedition into the harsh land of Sinai to acquire turquoise gemstones and copper.  He wishes you to lead this expedition, to a place called Serabit Khadim, where the building remains of an earlier Egyptian outpost may still be found.  Their current condition is unknown, but they may still provide some means of defense for the expedition.   @PYou should be aware that the last such expedition sent to this area never returned.   A later expedition sent to recover them also did not return.  Nevertheless, if we are to arm our soldiers adequately, our Kingdom needs copper for making weapons, and this metal is scarce in our land. @PPrepare yourself, for you will be under constant threat of attack from the Bedouin of the Sinai desert, and from our enemies the Canaanites.  Mine what copper and gemstones you may under these conditions, and be prompt in fulfilling Pharaoh's requests.  You may employ jewelers to use any surplus gemstones to fashion jewelry for the people occupying the settlement."
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
            text: "A Royal Necropolis",

        }
        content {
            text: "Pharaoh Huni wishes to spend everlasting eternity in a stepped pyramid, like that of Djoser before him.  He wishes to be surrounded by the tombs of his nobles, and has chosen Meidum, in Lower Egypt, as the site for this royal necropolis.   @PAs a symbol of thanks for the many generations of faithful service provided by your house, Huni has also consented to allow you to be interred at Meidum, in your own tomb.  In doing this, he has conferred great honor upon your family. @PTo ensure that the wisdom and learning of Egypt is preserved through the ages, Pharaoh Huni also urges the construction of royal libraries.  Once filled with scrolls of papyrus, these will provide higher education to the upper classes.  @PPharaoh has sent another of his faithful courtiers on an expedition to Serabit Khadim, in the harsh land of Sinai, to acquire turquoise gemstones.  If this expedition is a success, you may look forward to importing gemstones from there. Jewelers can use these to fashion jewelry, a valuable luxury good, for the people of your city. @PThe once-thriving city of Apollinopolis has begun to decline, and no longer exports many of the commodities they were once known for."
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
            text: "Expansion to Nubia",

        }
        content {
            text: "Our new Pharaoh, Snofru, is determined that this, the fourth dynasty, be remembered as the greatest ever to rule Egypt.  Pharaoh wishes that our borders be pushed even further south.  He has therefore decreed that we invade Nubia, and establish a fortified city at Buhen, beside the second cataract of the Nile.  There you must also erect a granite obelisk, to serve as a beacon that this area forever belongs to Egypt, and to Pharaoh.  There is no granite to be found so far south, however, so you will need to import it from Elephantine.   @PAt Buhen you will encounter fierce and seasoned Nubian warriors, who will fight to the death to prevent us from establishing a foothold so far south.  Do not despair, for after rigorous training at a Military Academy, your fighting men may emerge as seasoned veterans themselves.  What's more, our military engineers have perfected the design of several defensive structures, such as fortified Towers, Walls and Gatehouses.  These will prove invaluable in withstanding the onslaught of the Nubian army.  Transport ships may also be employed, to aid in moving your army around by water when necessary.  @PTo the north, we have opened relations with Enkomi, on the island of Cyprus.  This land is named for its abundant reserves of copper ore, which we are now able to purchase from them.  However, thanks to a recently established Egyptian mining community at Serabit Khadim, in the land of Sinai, we are able to supply our governors with copper at a much more affordable price.  Supplies from Serabit Khadim are often erratic, due to unrelenting Bedouin and Canaanite attacks against the settlement, and we are uncertain how much longer the Egyptian forces stationed there can hold out.  @PPharaoh's burial place, a unique and spectacular monument, is currently under construction at Dahshur.  From time to time Pharaoh may request that you contribute some limestone to aid in the completion of this project."
        }
    }
    message_mission_south_dahshur {
        id: 414,
        type: 3,
        size [40, 30]
        title {
            text: "South Dahshur",

        }
        subtitle {
            text: "Snofru's Bent Pyramid",

        }
        content {
            text: "@POur new Pharaoh, Snofru, is determined that this, the fourth dynasty, be remembered as the greatest ever to rule Egypt.  His architects have contrived a tomb even more spectacular than the stepped pyramid of Huni, and Pharoah wishes you to oversee its construction.  You will need to establish a fair sized settlement South of Dahshur, the site for Pharaoh's bent pyramid.  Once in place, this city will provide the workforce necessary to complete this ambitious project. @PThe bent pyramid is to be constructed of a plain stone core, and faced with fine white limestone, that it may forever shine under the desert sun.  You will find sufficient quantities of limestone at Dahshur, but you'll need to import the necessary amount of plain stone for this undertaking. @PPharaoh wishes that our borders be pushed even further south, and to this end he has dispatched military forces to invade Nubia, and to establish a fortified city at Buhen, beside the second cataract of the Nile. @PTo the north, Egypt has opened relations with Enkomi, on the island of Cyprus.  This land is named for its abundant reserves of copper ore, which are now a major import.  @PPrecious gemstones may be obtained from a recently established Egyptian outpost at Serabit Khadim, in the land of Sinai.  Lately the supply has become erratic, however, due to unrelenting Bedouin and Canaanite attacks against the settlement, and we are uncertain how much longer the Egyptian forces stationed there can withstand them."
        }
    }
    message_mission_north_dahshur {
        id: 415,
        type: 3,
        size [40, 30]
        title {
            text: "North Dahshur",

        }
        subtitle {
            text: "The True Pyramid",

        }
        content {
            text: "@PPharaoh Snofru has brought order to Egypt, and the kingdom now flourishes under his wise and benevolent rule.  Snofru wishes to undertake another construction project at Dahshur, even more ambitious than the bent pyramid already completed.  Royal architects, surveyors and engineers are confident that they can construct an edifice whose sides rise in one continuous angle, culminating in a perfect peak.  If successful, this will be the first true pyramid, and will be a worthy home for Pharaoh Snofru through all eternity!    @PPharaoh's wife, Queen Hetehpheres, has recently given birth to a son whom they have named 'Khufu'.  Our people look toward the day of his eventual rule with much foreboding, for the seers of Horus, God of the Pharaoh, have predicted that he will show none of his father's benevolence toward our people.  Though he will achieve many great things, they fear he will rule Egypt with unyielding tyranny.  @PYou may acquire wood from Byblos, since carpenters will have to build many ramps to allow workers to reach the summit of this great pyramid."
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
            text: "The defense of Egypt",

        }
        content {
            text: "@PPharaoh Khufu has taken the throne, and, as foretold by seers of Horus and Ra, our people have already begun to suffer under his oppression.  @PKhufu has ordered that a Royal Governor be dispatched at once to Dendera, to defend our land against Kushite invaders.  Dendera can support a small fishing industry, which should feed this settlement for a time.  If the Kushites invade by water, however, the river may become unsafe for fishing boats, and shore areas may be better used to support a fleet of warships.  If food becomes scarce, cattle may also be raised to provide meat, though the herds require much straw for fodder, and straw is difficult to grow in this land.  You should seek other cities with which to trade for straw, for you will also need this to make bricks for your mastaba. @PThe city of Byblos in Lebanon, land of the cedars, has begun trading with the powerful empires of the east.  These are Assyria and Ur, in the land called 'Mesopotamia', between the two great rivers, and from them the finest ivory may be obtained via Byblos.  With the arrival of rare and exotic luxury goods such as this, Dendera is sure to thrive. @PIn the capital, the Egyptian people have begun to enjoy a board game called senet.  This game is normally enjoyed over a pitcher of beer, in a public gathering place called a 'Senet House'.  Such places may provide a welcome diversion for the people of Dendera from the tyranny of Khufu's authority. @PPharaoh has ordered that countless quarries be dug at Heliopolis, in the Delta region, to harvest a vast supply of fine white limestone.  Only the gods know what endeavor Pharaoh has planned for the use of this stone.  It is rumored that he is planning a colossal building project on the plateau outside Giza, that he may usurp the renown his father, the wise and benevolent Snofru, has earned from the completion of his two noble pyramids."
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
            text: "Ivory from the East",

        }
        content {
            text: "@PPharaoh Khufu has taken the throne, and, as foretold by seers of Horus and Ra, our people have already begun to suffer under his oppression.  It is rumored that he plans to begin a colossal building project on the plateau outside Giza, that he may usurp the renown his father, the wise and benevolent Snofru, has earned from the completion of his two noble pyramids.  @PPharaoh Khufu has ordered a cluster of quarries to be dug at Tura, in the Delta region, where rich deposits of fine white limestone have recently been discovered.  You also must build three mastaba tombs for the nobles of this region, so that Pharaoh may honor their devotion.  The quarrying settlement you found shall be named 'Heliopolis', and shall serve as a plentiful source of fine white limestone for many years...though only the gods know what endeavor Pharaoh has planned for its use. @PThe city of Byblos in Lebanon, land of the cedars, has begun trading with the powerful empires of the east.  These are Assyria and Ur, in the land called 'Mesopotamia', between the two great rivers, and from them the finest ivory may be obtained via Byblos.  With the arrival of rare and exotic luxury goods such as this, Heliopolis is sure to prosper. @PKhufu has also dispatched a Royal Governor to Dendera, to defend our land against Kushite invaders.  Royal viziers look with pity upon the Governor charged with this difficult and dangerous task.  @PIn the capital, the Egyptian people have begun to enjoy a board game called senet.  This game is normally enjoyed over a pitcher of beer, in a public gathering place called a 'Senet House'.  Such places may provide a welcome diversion for the people of Heliopolis from the tyranny of Khufu's authority."
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
            text: "The Great Pyramid and Sphinx",

        }
        content {
            text: "Pharaoh Khufu has at last made his plans known, and his boundless aspirations are sure to weigh heavily upon our people.  Pharaoh both curses and blesses your family, for though you have been awarded the status of Nomarch, you have also been charged with carrying out the most ambitious building project ever to be undertaken in our land.   @PPharaoh's eternal resting place shall be a massive pyramid complex, situated far from any city, on the plateau outside Giza.  His sarcophagus shall be made of solid granite, and his funeral barge of precious Lebanese cedar. Beside Pharaoh's pyramid complex, a smaller pyramid shall also be built for his son prince Khafra, whose tyranny rivals that of his father, though his achievements do not.  Khafra also declares that his image be carved into the living rock at Giza, upon a huge figure called a 'sphinx', with the body of a lion and the head of a man. @PTo support the massive building effort needed for the completion of this monument, you'll need to establish a large settlement at Giza.  As such, conditions there may not be overly refined, for your goal is only to complete these three great projects, and to honor Pharaoh.   @PYou will be provided with some of the fine white limestone needed for the outer casing of these pyramids, but you will also need to purchase much of what you'll need with the city's own funds. @PPharaoh is entrusting you, one of his royal Nomarchs, with these three sacred tasks.  You must demonstrate unwavering dedication to Pharaoh and fulfill his wishes...whatever the cost."
        }
    }
    message_mission_bahariya_oasis {
        id: 419,
        type: 3,
        size [40, 30]
        title {
            text: "Bahariya Oasis",

        }
        subtitle {
            text: "The Western Desert",

        }
        content {
            text: "@PThe reigns of Khufu and Khafra have come to an end, and with them so too has the fourth dynasty of Egyptian ruling families.  But lady Khentkaues, a distant member of this family, has given birth to a new Pharaoh named 'Userkaf', and so the royal line continues unbroken.  With Userkaf begins the fifth dynasty, an era that promises much change.   @PUserkaf has decentralized the rule of our country somewhat, and has granted more power to local authorities.  Now Nomarchs such as you are free to handle their own affairs.  Pharaoh will not attempt the construction of a massive tomb to house him for eternity, for he has another project in mind for you. @PPharaoh has declared Ra, god of the sun and of the kingdom, to be King of the Gods, and intends to proclaim his sovereignty throughout the land.  Many Sun Temples already dot the Egyptian landscape, but Pharaoh wishes to extend Ra's influence to the very edge of our Kingdom. @PTo accomplish this, you must build a fortified settlement at the Bahariya Oasis, far into the Western Desert. Use what water you can find there wisely, for what little there is to be found so far from the precious Nile is usually coveted by the wild beasts of the desert.  You must also beware of attacks by Libyan warriors, and Bedouin of the desert, which have plagued the desert caravans of late.  Plan your defenses carefully, and make use of whatever resources, such as wood and game, you can find at the oasis."
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
            text: "The Temple of the Sun",

        }
        content {
            text: "@PThe reigns of Khufu and Khafra have come to an end, and with them so too has the fourth dynasty of Egyptian ruling families.  But lady Khentkaues, a distant member of this family, has given birth to a new Pharaoh named 'Userkaf', and so the royal line continues unbroken.  With Userkaf begins the fifth dynasty, an era that promises much change.   @PUserkaf has decentralized the rule of our country somewhat, and has granted more power to local authorities.  Now Nomarchs such as you are free to handle their own affairs. Pharaoh will not attempt the construction of a massive tomb to house him for eternity, for he has another project in mind for you. @PPharaoh has declared Ra, god of the sun and of the kingdom, to be King of the Gods, and intends to proclaim his sovereignty throughout the land.  Many Sun Temples already dot the Egyptian landscape, but Pharaoh wishes that the greatest be located at Abusir, in the humid Delta region of Lower Egypt.  @PLike most of the Delta, Abusir is rich in game, fish and other wildlife and vegetation, but offers few mineral resources.  As such, sandstone needed for construction of the Sun Temple will need to be imported from the quarries at the Dunqul Oasis.  Cattle may be raised here to provide meat, though the herds require much straw for fodder. @PYou'll need to clear land in order to create a suitable location for the Sun Temple.  Be sure to sell enough of the precious timber you may harvest first, for once it is gone you may not be able to acquire more.  Apollinopolis and Abydos are always in need of wood, and also game, thus trade with them should help to offset the cost of constructing this sacred monument."
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
            text: "The Kushite Threat",

        }
        content {
            text: "@PPepy has taken the throne, and awarded your family the status of Chancellor, but it has come with a price.    @PCentralized authority continues to erode, as local and regional leaders become more powerful.  Harvests in some regions are far below normal, and the specter of famine has begun to appear in Egypt.  Memphis, once a splendid and beautiful city, is beginning to decline.  Seers foretell difficult times to come. @PPowerful neighbors are moving to take advantage of Egypt's increasing weakness.  The outpost at Buhen is under siege from fearless Kushite soldiers sent from Kerma, the largest non-Egyptian city in Africa.  The Kush are demanding tribute, and the slightest provocation could lead to an outright attack. Nubia, too, has issued a call to war and is seeking to reclaim lost land.  @PIf Egypt is to survive, you must do what you can to preserve trade routes to keep goods flowing into and out of Egypt.  Keep the hard-won trading post at the Selima oasis open.  Pepy, anticipating his journey to the afterlife, will make frequent requests for stone to build his pyramid, and other cities, short on food, will seek sustenance from you. @PUse your resources carefully.  Valuable wood is plentiful at the oasis, but some of the forest must be destroyed to access the limited water supply."
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
            text: "The Caravan Trail",

        }
        content {
            text: "@PPepy has taken the throne, and awarded your family the status of Chancellor, but it has come with a price.   @PCentralized authority continues to erode as local and regional leaders become more powerful.  Harvests in some regions are far below normal, and the specter of famine has begun to appear in Egypt.  Memphis, once a splendid and beautiful city, is beginning to decline.  Seers foretell difficult times to come.  @POur powerful neighbors are moving to take advantage of our increasing weakness.  Our outpost at Buhen is under siege from fearless Kushite soldiers sent from Kerma, the largest non-Egyptian city in Africa.  The Kushite are demanding tribute, and the slightest provocation could lead to an outright attack.  Nubia, too, has issued a call to war and is seeking to reclaim lost land.  @PTry to keep Egypt stable by establishing an administrative post at Dakhla Oasis.  The oasis has a large stand of valuable trees, but these trees unfortunately block access to the limited water supply at the oasis.  From this important location, import ebony from the African interior.  Pepy, anticipating his journey to the after-life, will request bricks for the construction of his monument.  Other cities, short on food, will request sustenance from you."
        }
    }
    message_mission_thinis {
        id: 423,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis ",

        }
        subtitle {
            text: "Civil War",

        }
        content {
            text: "The old way of life is gone, and most fear that Egypt will never return to its past glory.  Osiris has turned his back on his people, and a series of low Inundations has caused widespread famine.  The power of the pharaohs, once unquestionable, has evaporated, replaced by bickering provincial leaders. @POut of this chaos, two noble families have arisen and are attempting to seize control of the country.  The rulers of Herakleopolis have laid claim to the throne as the rightful heirs.  They are particularly cruel and are doing little to assuage the people's hunger.  To the south, a new family, the Inyotef house, has risen to power in Thebes.  This family has done much to reunite the south, and now Herakleopolis has engaged Thebes in a deadly civil war for control of all of Egypt. @PTo show their benevolence to the people of Egypt, the Inyotefs have entrusted you with rebuilding the newly conquered city of Thinis, one of the oldest cities in Egypt.  Two of Thinis' finest and most ancient buildings have survived the turmoil of its conquest: the Temple Complex of Osiris and the mansion.  The Inyotefs have decreed that should either of these buildings be destroyed, no funds will be squandered on their restoration.  The Theban rulers consider the restoration of Thinis a top priority and have gathered up considerable funds - even in this time of strife - for this purpose.  Return Thinis to its former splendor, and commission a navy and raise a strong army to defend it from the frequent attacks of those loyal to Herakleopolis, including the cities of Lykopolis, Hierakonpolis and Hermopolis.  Be careful of the Herakleopolis rulers: they may demand tribute to see if your loyalty - and your debens -- can be extorted.  Also watch out for the opportunistic Nubians who seek to take advantage of Egypt's internal struggles."
        }
    }
    message_mission_thebes {
        id: 424,
        type: 3,
        size [40, 30]
        title {
            text: "Thebes",

        }
        subtitle {
            text: "Civil War",

        }
        content {
            text: "The old way of life is gone, and most fear that Egypt will never return to its past glory.  Osiris has turned his back on the people, and a series of low Inundations has caused widespread famine.  The power of the pharaohs, once unquestionable, has evaporated, replaced by bickering provincial leaders. @POut of this chaos, two noble families have arisen and are attempting to seize control of the country.  The rulers of Herakleopolis have laid claim to the throne as the rightful heirs.  They are particularly cruel and are doing little to assuage the people's hunger.  To the south, a new family, the Inyotef house, has risen to power in Thebes.  The family has done much to reunite the south, and now the rulers of Herakleopolis have engaged the rulers of Thebes in a deadly civil war for control of all of Egypt. @PThe Inyotefs, busy fighting the Herakleopolis rulers, have entrusted you with building up their home city of Thebes.  If the Inyotefs are to succeed in their fight against the Herakleopolitan rulers and solidify their reputation in Egypt, Thebes must be a touchstone on which other cities rely, providing succor or soldiers to those that request aid.  Thebes, which could be the capital should the Inyotefs reign victorious, must be a great city.  Using the scarce resources available to you, build a Sun Temple and pyramid to show Egyptians the glory of the Inyotefs. @PThebes itself is not immune to attack.  The Herakleopolitan rulers, and those loyal to them, may threaten your city from time to time, and Herakleopolis may try to extort debens from your city's treasury.  To defend against these considerable risks, build a strong army and navy to defend your city and to come to the defense of other threatened cities."
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
            text: "Reunification",

        }
        content {
            text: "Your family's performance during the civil war has not gone unrewarded.  I, Pharaoh Mentuhotep, have awarded your family the rank of Vizier.  There is no one in all of Egypt that I trust more than you.  Now that the twin kingdoms of Upper and Lower Egypt are reunited and the capital at Thebes is thriving, I need you to help me solidify my position throughout the Kingdom. @PWhile reunited, Egypt is prone to internal skirmishes, particularly in areas that were once loyal to the Herakleopolitan rulers.  To help solidify our new union, I want you to rebuild and defend Coptos.  Coptos should be a glorious city that shows Egypt's citizens what is possible under my rule.   The city comes under frequent attack from remaining loyalist cities, such as Hermopolis, and you must be sure to defend your city's borders. @PFamine still stalks the country, and frequent requests for food will come to you from other cities in the Kingdom.  Respond as quickly as you can to their heart-rending pleas, so that all Egypt will know my benevolence and the dedication of my most trusted Vizier. @PI know that I am asking much of you, but there is no one else in Egypt capable of doing this difficult task."
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
            text: "Reunification",

        }
        content {
            text: "Your family's performance during the civil war has not gone unrewarded.  I, Pharaoh Mentuhotep, have awarded your family the rank of vizier.  There is no one else in Egypt that I trust more than you.  Now that the twin kingdoms of Upper and Lower Egypt are reunited and the capital at Thebes is thriving, I need you to help me solidify my position throughout the Kingdom. @PWhile reunited, Egypt is prone to internal skirmishes, particularly in areas that were once loyal to the Herakleopolis rulers.  To help solidify the newly reunited country, I want you to rebuild and defend Beni Hasan, which was nearly destroyed during the civil war.  Beni Hasan should be a glorious city that shows Egypt's citizens what is possible under my rule.   @PFamine still stalks the country, and frequent requests for food will come to you from other cities in the Kingdom.  Respond as quickly as you can to their heart-rending pleas, so that all Egypt will know my benevolence and the dedication of my most trusted vizier. @PI have one more noble request: I want you to build granite obelisks to further proclaim all I have done for this land in my lifetime. @PI know that I am asking much of you, but I also know that you are the only one in Egypt capable of doing what I have asked."
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
            text: "A New Capital is Founded",

        }
        content {
            text: "O mighty Pharaoh, Beloved of Ra, how fortunate you must feel.  Your unprecedented rise to the throne of Egypt is the stuff of dreams!  A richer reward could not be fashioned by gods or people. With your family's accession, Egypt can make a new start, and perhaps we can all forget the horrors of the civil war. @PTo mark this new beginning, you should build a fine new capital.  Itjtawy, with its abundant natural resources, is a perfect location.  Using what the land has to offer, you can build a splendid city worthy of your dynasty's valor and dedication. @PTo ensure the feats of your great dynasty are always remembered, you should build two majestic brick pyramids for yourself and your family and a frightening sphinx to guard your tomb.  A family with your achievements deserves no less. @PKeep in mind, though, that some in the country question the legitimacy of your rule.  Many are still suffering the effects of the famine and grumble that you usurped the throne.  If you relieve these people's misery and help them rebuild their homes, you will certainly win their undying loyalty.  You should try to provide for your new subjects as well as you can to prevent these unfortunate people from taken up arms against you."
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
            text: "Into Nubia",

        }
        content {
            text: "Now that Egypt is firmly united under your rule, all of your court, and I, your trusted vizier, recommend that we push the borders of our country south into Nubia.  The dry riverbed at Allaqi is rich with veins of gold, and a mighty city at Mirgissa, with you in residence, will certainly keep the Nubians from trying to attack.  Be careful of the Kushites, however.  They are a much more dangerous adversary than the Nubians and will use their swords to encourage you, O Pharaoh, to leave their kingdom alone. @PTo leave a lasting mark on Nubia, you should build a large obelisk to attest to Egypt's many achievements.  The obelisk will offer compelling evidence to the Nubians of the benefits of Egyptian rule, and be a constant reminder of our presence. @PWhile your direct attention is devoted to Mirgissa, do not forget our intent to establish a thriving port city on the Red Sea at Mersa.  Mersa will need help from you, and will not hesitate to ask for it.  If Mersa can thrive, they will provide Mirgissa with much-needed copper, from which weapons can be forged."
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
            text: "On the Shores of the Red Sea",

        }
        content {
            text: "Now that Egypt is firmly united under your rule, we must develop trade relations with cities throughout the world to increase Egypt's wealth, O King of the Two Lands.  @PAs your people prosper, they demand more exotic items.  Tired of jewelry, an easily obtained luxury good, your people want rare and expensive luxury goods, such as incense.  Your court and I, your trusted vizier, recommend that you establish a Red Sea port at Mersa.  Mersa offers a trade route to distant Punt, from which the finest incense in the world may be imported, though at great cost.   @PBeside modest veins of gold and copper ore, Mersa produces few raw materials of its own, but can thrive as a manufacturer of finished goods.  By importing raw materials from trade partners, and exporting finished products, Mersa shall be able to turn a tidy profit. @PWhile you are busy establishing Mersa, one of your most valiant Nomarchs is establishing a new trade center in Nubia.  His city, Mirgissa, is likely to come under attack, so my beloved Pharaoh should be prepared to send him any resources he may need. @PUnder your rule, Mersa is sure to be one of the loveliest cities in the Kingdom, suitable as a final resting place for you and your family.  As you establish the thriving port, do not neglect preparations for the afterlife.  A mausoleum and small brick pyramid will provide sumptuous quarters for you and your family after your passage to the Field of Reeds."
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
            text: "The Gauntlet",

        }
        content {
            text: "Most respected Pharaoh, all that your family has fought so hard for is threatened!  The Nubian navy is patrolling the Nile, striking deep into the heart of Egyptian territory, ransacking villages and cities alike.  The Nubians are also boarding trade ships, pirating away goods.   To help your northern cities beat back the foe, you should be prepared to send warships and soldiers to the cities that need them.   @PTo prevent the Nubians from again sailing our waters, your military advisors recommend building a cluster of forts at Semna between the second and third cataracts of the Nile.  The forts will act as a cork, penning the Nubians in to the south.   @PSuccessfully driving out the Nubians rests with conquering the city of Kuban.  Kuban is rich in resources, and taking it over will cripple the Nubian economy.  Once you have wrested control of Kuban away from the Nubians, you can begin importing sandstone from the city for your great mausoleum.  Your mausoleum at Semna will serve as a reminder of your dominance over the unruly Nubians.   @PThere are many challenges before you as you protect Egypt from the Nubians.  Pay heed, O Living Horus, to the storm rising in the east.  The thundering of horses' hooves are heard throughout Canaan, and lightning-quick chariots are laying waste to all in their path.  These formidable chariots, the likes of which have never been seen anywhere, are driven by the Hyksos warriors.  Already, storm clouds have been spotted on the Egyptian horizon, and you should steel yourself against the impending danger."
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
            text: "The City of Bast",

        }
        content {
            text: "Most royal Pharaoh, with robust trade routes firmly in place, we should now show Egypt what success and wealth can bring.  Bubastis provides a perfect location for such a city: we can protect our valuable trade routes to the east while paying homage to Bast, who has watched over Egypt. @PBast's city should be like no other in Egypt.  It should be as lovely as the lotus flower, blooming forth with entertainment, schools, libraries and places of worship.  Its citizens should be well-supplied with the finer things, including imported incense.  When complete, Bubastis will be the jewel in the twin crowns. @PWhile you are building this glorious city, pay heed to the storm rising in the east.  The thundering of horses' hooves are heard throughout Canaan, and lightning-quick chariots are laying waste to all in their path.  These formidable chariots, the likes of which have never been seen anywhere, are driven by the Hyksos warriors.  Already, storm clouds have been spotted on the Egyptian horizon, and you should steel yourself against the impending danger."
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
            text: "Egypt Reclaimed",

        }
        content {
            text: "Most powerful Pharaoh, Egypt cries out for your help.  The menacing Hyksos have invaded our land and have set up their own capital at Avaris.  From Avaris, they have disrupted many of our trade routes, choking off needed supplies.  We must stop their conquest before it is too late. @PIf it pleases you, Great Pharaoh, we should reclaim the city at Hermopolis, which has been violated by these foul invaders.  We should also build a strong army and navy, for we may need to supply troops and arms to our compatriots in the north, especially at Avaris, to help repel the Hyksos incursion.  They will look to you, Child of Ra, for support.  But now we too have a new weapon.  Our wise military leaders have become proficient in the use of the dreaded chariot, and we shall turn it back upon our enemies and drive them before us.  Once we drive the troublesome Hyksos out, our military advisors recommend building a fort in Sinai at Sharuhen to prevent further invasions from the east. @PIf only our trouble was limited to the north!  Reports from our southern border show that the Nubians are once again taking advantage of a distracted Egypt.  They have reclaimed the southern cities of Mirgissa and Semna.  While these lost cities are cause for concern, we must first oust the Hyksos before we can turn our attention southward. @PThese Hyksos are most unholy invaders.  We have just discovered that they have defiled the pyramid here in Hermopolis.  They have stolen from the pyramid all the burial provisions that the mighty Pharaoh interred here needs in the Field of Reeds.  We should provide a new supply of grave goods so that the Pharaoh buried here can enjoy life everlasting."
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
            text: "Egypt Reclaimed",

        }
        content {
            text: " O King of the Two Lands, Egypt cries out for your help.  The menacing Hyksos have invaded our land and have set up their own capital at Avaris.  From Avaris, they have disrupted many of our trade routes.  We must stop their conquest before it is too late. @PHere at Lykopolis, we are safe from immediate attack, although the Hyksos have the gall to demand tribute. We may need to supply troops and arms to our compatriots in the north to help repel the Hyksos incursion.  They will look to you, O Mighty Pharaoh, for support.  But now we too have a new weapon, our wise military leaders have become proficient in the use of the dreaded chariot, and we shall turn it back upon our enemies and drive them before us. @PIf only our trouble was limited to the north!  Reports from our southern border show that the Nubians are once again taking advantage of a distracted Egypt.  They have reclaimed the southern cities of Mirgissa and Semna. @PIf Egypt is to emerge intact from these turbulent times, much will be required of your generals in the field and on the river.  To inspire your two best generals, you have promised to build each of them a pyramid as spectacular as your own.  Holding your promise in their hearts, they are fiercely combating the foe, calling upon all their strength and sinew.   @PIf it pleases you, Mighty Pharaoh, you should build three magnificent pyramids at Lykopolis, one for yourself and one for each of your generals.  These three pyramids will take up considerable space, so you will need to surrender some valuable resources in order to accommodate them.  You may also need to extend your city across the Nile to avail yourself of all the resources needed for this city to flourish."
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
            text: "Expansion and Conquest",

        }
        content {
            text: "Egypt has emerged from its recent troubles with a newfound strength.  Byblos, with all its verdant forests and rich sources of copper, is ours!  With your presence, the city is sure to thrive, and a New Kingdom will be established. @PAh, but what an alarming discovery we made after conquering Byblos!  A new, ferocious people, the Hittites, have washed over much of Asia, and some even say that their empire rivals our own for size.  Now, they have turned their eyes toward Byblos, covetous of its riches.  If we are not well prepared for their attack, we could easily lose Byblos to our foe.  @PWhile preparing to meet the Hittites, we must mark Byblos as forever Egyptian.  With your blessing, O Pharaoh, we shall erect a series of three obelisks, two small and one large, proclaiming your sovereignty and fame throughout the far stretches of your empire.  These towering monuments will remind the residents of Byblos with whom their loyalties should lie. @PWhile we occupy ourselves with matters at Byblos, other regions of Egypt are still prone to attack.  Nubians have moved north as far as the first cataract, and we must help our compatriots drive them back.  Reports from Avaris tell of another mysterious new foe, the Sea People.  Both these enemies must be strongly put down if Egypt is to attain glory.  To show your might, be sure to send troops and warships should they be requested."
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
            text: "The Glory of Egypt",

        }
        content {
            text: "With the Hyksos successfully expelled from our country, our land is ripe for rebirth, a New Kingdom that outshines past glory.  Most noble Pharaoh, Kuban is an ideal place to begin this New Kingdom.  We can use the large amount of gold found there to fund your new vision of Egypt.  @PWhile Egypt is on the brink of greatness, a few nagging problems remain.  Many of Egypt's cities are still recovering from the disruptions caused by the Hyksos and may need Pharaoh's help.  In other regions, Egypt's old enemies still attack us, and a new enemy, the Sea People, has been raiding our northern coast. You must be prepared to defend other Egyptian cities from our foes, both old and new. @PAs Egypt grows in stature, many cities are willing to engage in trade.  Some of these cities are so familiar with our ways, and in awe of your power, that they consider themselves Egyptian, while others are foreign to us and are trading with us for the first time.  For the glory of Egypt, take advantage of all these relationships to provide your people with all the goods they desire. @PTo usher in the new era, your royal architects crave the opportunity to build two pyramids and a stately mausoleum for you, O Pharaoh. These will surely reflect the wealth and grandeur you have brought to Egypt."
        }
    }
    message_mission_avarist {
        id: 436,
        type: 3,
        size [40, 30]
        title {
            text: "Avaris",

        }
        subtitle {
            text: "The Sea People",

        }
        content {
            text: "O Horus of Gold, our hold on Asia is strong and unchallenged, and our borders again stretch far into Nubia.  But the trouble on our northern coast is escalating.  The Sea People have become increasingly aggressive, wantonly raiding our cities.  Only Pharoah's presence will be enough to defeat this fierce and wily adversary.  If you commission a navy, supported by a strong army, surely we shall overcome the Sea People.   @PWhile you work to defeat the Sea People, your brave Nomarchs are leading attacks throughout the world.  If they are successful, Egypt will rule the world from the great Euphrates river in Asia to the sprawling Kushite city of Kerma to the south.  When you and your Nomarchs have met with sweet victory, your dynasty will be recorded as the greatest dynasty ever to keep watch over Egypt. @PMarking your far-reaching influence is a new, distant trade partner, Mycenae.  The king of Mycenae has learned of the splendor and bounty of Egypt, and wishes to engage in trade with us.  If you agree to open this trade route, O Pharaoh, your citizens will surely be provided with exotic goods unlike any they have ever seen. @PTo house your royal family for the afterlife, a pair of awe-inspiring mausoleums and an impressive brick pyramid must be built.  These monuments will remind all who follow of your deeds both on and off the battlefield."
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
            text: "The Glory of Pharaoh",

        }
        content {
            text: "Benevolent Pharaoh, you have brought peace and prosperity to our nation.  Under your wise and capable rule, Egypt is a strong and glorious country once again.  All Nomarchs are loyal to you, and no threats to our great nation remain. @PHaving accomplished all your family set out to do so many years ago, it is time to memorialize the achievements of your great dynasty.  The only way to accomplish this is to build the grandest pyramid Egypt has ever known, a pyramid even larger than Khufu's, at Giza.  Others in your noble family have sacrificed much on the long road leading to your rule of Egypt.  They too must be remembered and honored, with a sandstone mausoleum to acknowledge their unwavering support.   @PThe ideal location for these monuments is Kahun in the rich Fayuum region.  From here, you can attend to all the affairs of state, and respond to any requests for supplies that your cities may ask of you, as you build your great pyramid."
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
            text: "@PWith the aid of your family, the Thinite king Hor-Aha has successfully united the twin kingdoms of Upper and Lower Egypt, proclaimed himself Pharaoh over all Egypt, and founded an imposing capital at Memphis.    @PYour clan has relocated once more, this time to the humid Delta region of Lower Egypt, to an area known as Buto. Canaanite warships have been threatening this region, and you'll likely need to dispatch a few warships of your own, when the time comes. @PYour family has achieved the status of nobility. As such, it is expected that before you pass from this world into the next, you will undertake to complete an exquisite brick tomb - a mastaba - to house your body on its journey into the afterlife. @PHowever, first you must establish some farms along the banks of the Nile, to exploit the rich, fertile soil deposited by the annual Inundation of the river. This will allow your population to grow and prosper, and eventually become large enough to complete this sacred monument. But beware, for many dangers lurk among the life-giving waters of the Nile, such as deadly crocodiles, hippopotamus and malaria-carrying mosquitoes. @L@L Farming along the Nile @PYou must build farms directly on the flood plain, in order to gain the benefits of its increased fertility. Unlike most working structures, farms on the flood plain do not need direct access to employees, but do need a steady workforce of peasant laborers, supplied by work camps, to tend their fields. Build work camps fairly close to flood plain farms, so peasants won't have to walk too far to reach them. @G56 @L@PEach year the Nile floods its banks, replenishing the depleted soil on the flood plain with rich, fertile mud.  Peasants harvest the annual crop just before the Inundation, and deliver it to your granaries. Because there is only one harvest per year, make sure to have enough granaries to store a sufficient amount of food for your growing population."
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
            text: "The Sea People Land",

        }
        content {
            text: "@PThe rumblings of distress and discontent to the west have become more ominous recently.  Scouts report that several barbarian tribes speaking strange tongues have arrived on the shores of Kyrenaica to our west.  To make matters worse, these peoples now walk hand-in-hand with Maraye, the son of Did, king of the Libyans and Pharaoh's enemy.   @PWord has now reached Pharaoh Merneptah that these vile people, with all of their women, children and worldly possessions close behind, will soon be headed eastward, toward the fertile Nile delta - our homeland! - in search of a place to settle.  Already there have been minor clashes at the northern oases of Siwi and Farafra.  Your delta town of Pi-yer now stands in their way.  In a short while this slow-moving band of savages could be on your doorsteps.  Pharaoh has decreed that, should they arrive, they must not be allowed to penetrate further! @PYou will need to import wood from which to construct sturdy warships, and copper for weapons.  It is your fortune that the previously troublesome Hittites are now peaceful, thanks to the great victory at Qadesh by Ramses II, sire of the beloved Merneptah. Make your town strong, and brace your loyal troops for mortal combat."
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
            text: "Repel the Assyrians",

        }
        content {
            text: "@PSince the days of the great Shabaka, unifier of Upper and Lower Egypt and sire of Pharaoh Taharqa, conflict with the aggressive Assyrians has been the norm.  While he still lived, Pharaoh Shabaka saw that it was proper to aid our brothers in Palestine who were chaffing under the harsh rule of Assyria.  Beware!  The minions of the heathen king Asarhaddon are again on the march and, as always, their eyes are on the fertile lands of Egypt.  It is now your turn for glory!  As Royal Mayor of Migdol, you will be expected to defend against the series of attacks by these accursed foes.  Located on the eastern rim of the Nile delta, your border fortress is on the front line of Egypt's outer defenses. @PProperly training your soldiers and establishing trading links to secure weapons - or raw materials from which to make your own - will be important. @PDo not falter!  A strong military stand is vital to insure the continued independence of Egypt.  If you can hold out for a mere seven years, victory will be assured.  Taharqa, the great Pharaoh, second son of Shabaka, will be watching!"
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
            text: "Rebirth of a Navy",

        }
        content {
            text: "@PFor many generations Egyptians have been suffering under the cruel fist of Persia.  Babylon's grip upon our sacred lands is, however, not as strong as it once was.  While our accursed oppressors have been busy meddling in the politics of Greece, a series of revolts in Egypt has finally managed to loosen the hated Persian yoke.  Now, however, word has reached Pharaoh Achoris that a force commanded by Fleet Admiral Conon (a Greek lackey receiving Persian gold) has been dispatched by Artaxerxes II and is headed for our shores.  Pharaoh Achoris has wisely determined that a strong naval presence in the Nile is needed to thwart this incursion.  As Royal Governor of Tanis for the next ten years, you must build strong ships and train stalwart troops to guard the approaches by water and land. @PYou will need to establish a trade route with Enkomi to import sturdy wood with which to construct a fleet.  Copper can also be imported from Enkomi, on the island of Cyprus.  This trade route is precarious at best, as it runs close to the Levant coast, under control of our foe.  Supplying the Pharaoh with needed supplies should help to supplement your income.   @PBe aware that funds are tight in these troubled times.  To succeed, you must be savvy in business and trade as well as a skillful commander."
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
            text: "Alexander the Great",

        }
        content {
            text: "@PThe great Alexander, son of Phillip II of Macedon and scourge of the Babylonian Empire, blessed the lands of Egypt with his presence.  With his coming, the final corrupt Persian satrap has hastily fled.  After sacrificing to the Apis bull at Memphis, Alexander has been accepted as Pharaoh.  All the people rejoice!  Before setting off on his journey to the Oracle of Amun in the Siwi Oasis, however, our leader decided to found a new city, one that he wishes to someday be the capital of his vast and expanding empire.  In his infinite wisdom, he has appointed you to be this future city's first mayor! @PThe great Alexander has bestowed upon you a generous endowment of funds from which to begin construction, and has given you the services of the esteemed Greek architect Dinocrates.  In a mere dozen years he expects you to have the commercial, cultural and military might of his city developed to high standards, as he has vowed to return.  @POur leader has even taken the time to trace the positions of the two main thoroughfares of his city.  The Canopic Street runs along an east-west axis; the other main avenue is perpendicular to it and heads inland from Cape Lochias southward toward Lake Mariut. @PAs trusted overseer of this project, you should quickly build port facilities and establish lucrative trade routes.  There should be many customers for our products, especially wheat, barley, papyrus and linen.  Do not neglect the cultural aspects of this city, nor its military, however, as there are still roaming vandals that wish to rob Egypt of her wealth."
        }
    }
    message_mission_ptolemy_alexandria {
        id: 443,
        type: 3,
        size [40, 30]
        title {
            text: "Ptolemy's Alexandria",

        }
        subtitle {
            text: "A Beacon of Light",

        }
        content {
            text: "@PThe legacy of Alexander the Great lives on in our proud city. Even though his mortal remains rest in Alexandria's Mausoleum, his great city continues to thrive.  It is up to you, Ptolemy I Soter, to carry on with the job the noble Alexander began.  Since its founding by Alexander barely 30 years ago, the city has become a powerful commercial hub, supplying much-needed foodstuffs and items of luxury to much of the surrounding area.  To further its economic progress and to ensure safe passage of the many ships entering the great harbor, you should construct a massive Lighthouse on Pharos Island, near the mouth of the harbor.  This structure's beacon of light will guide distant seafarers safely into the harbor, ensuring that they do not founder on its tricky shoals. @PImportant as commerce is, however, you cannot ignore the cultural and intellectual advancement of our society.  Under your leadership Alexandria can now become the intellectual capital of the known world as well.  Gather works of knowledge from near and far, and build a great Library in which to keep them.  As sure as ants are attracted to honey, learned scholars from all over will journey to this unrivaled center of knowledge and learning.   @PTo build these great monuments you will need to import a building material, such as white marble, that will be suitable for such great structures.  Enkomi, on the island of Cyprus, is a good source for this material.   @PLastly, do not ignore your military.  There always seems to be unrest in one place or another.  It might be necessary to dispatch troops to distant frontiers to protect Egypt's interests and defend her honor."
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
            text: "Caesar and Cleopatra",

        }
        content {
            text: "@PThe indelicate grasp of the Roman Empire grows stronger and reaches farther with each passing day.  Even the deadly political power struggles of Rome have reached our land.  With the recent assassination of Pompey on the shores of Egypt, Julius Caesar now has complete control of Rome's mighty legions and has cast his eyes upon the riches of Egypt - and upon the beauty of our beguiling pharaoh, Cleopatra VII, daughter of Ptolemy XII Auletes.  Our clever leader is not easily outdone on the battlefield of wits, however.  If Caesar desires to use her as a means to further Rome's influence in Egypt, so too does she plan to employ him as an instrument of maintaining the dynastic power of our great land. @PCaesar's arrival in Alexandria with his unpopular Romans has sparked an uprising among its independent minded citizens.  An unruly mob, egged on by Cleopatra's younger brother Ptolemy XIII, has cornered Caesar and his men in the royal quarter of the city.  Bitter street fighting has erupted, claiming many casualties.  In a bid to keep his seaward escape route open, Caesar burned the Egyptian fleet as it lay at anchor in Alexandria's harbor.  Unfortunately the conflagration spread to some shoreline warehouses, burning great quantities of papyrus scrolls belonging to the Great Library.   @PTo break the trap in which he now finds himself, Caesar has summoned the loyal Mithradates and his troops from Syria to effect his rescue.  After successfully storming the border fortress of Migdol, Mithradates has force-marched his men around the apex of the Nile delta so to approach Alexandria from the southeast.  The lead elements of this force are currently encamped on the outskirts of the small village of Maritis, on the eastern shore of Lake Mariut, preparing for the final leg of their journey.  @PThe baleful Ptolemy XIII has learned of the approach of these reinforcements.  In response he has marched the bulk of his more numerous army southeastward out of Alexandria.  A decisive battle on the eastern shore of Lake Mariut is about to ensue.  Can you, commanding Mithradates' Roman legions, defeat Ptolemy's rebellious Egyptian army and break through to Caesar and Cleopatra in Alexandria?  Their fate rests in your hands."
        }
    }
    message_mission_cleopatra_alexandria {
        id: 445,
        type: 3,
        size [40, 30]
        title {
            text: "Cleopatra's Alexandria",

        }
        subtitle {
            text: "The Legacy of a Queen",

        }
        content {
            text: "@PCaesar's bloody death at the points of assassins' daggers cast the Roman world into turmoil and has driven you, our Pharaoh, Cleopatra VII, into grief and mourning.  Gone is your lover, mentor, confidant and powerful ally.  Octavian, his teen-aged adopted great-nephew, has been named as heir but the more experienced Mark Antony, previously a consul to Caesar, has become the nominal head of state, somewhat to the ire of the young Octavian.  Not surprisingly, Caesar's will made no mention of your son by him, Ptolemy Caesar, popularly known as Caesarion. Desiring safety for yourself and your child and, as always, seeking to preserve the power of Egypt, you have departed Rome for Alexandria.  @PDespite all the leagues between Rome and yourself, you cannot leave behind all of its internecine squabbles.  Powerful men still vie for power - your support and the access to the riches of Egypt would be a great asset to any faction.  For you to back a winner in this power struggle is critical; siding with the loser could easily result in the end of Egypt.  The dramatic showdown between the rival Roman factions recently occurred at Philippi where Mark Antony's Caesarians decisively beat the forces of Brutus and Cassius.  Antony, Octavian and Lipidus have now carved up the empire for joint rule, with Antony claiming the eastern portion, which includes Egypt. @PNot long after the battle, Mark Antony summoned you to join him at Tarsus in Asia Minor, so that you might better explain why you had been slow to cast your lot with the Caesarians.  Not one to be summoned like a lapdog, you wisely declined to respond.  After all, you know better than most that it is much better to see a Roman under your own terms and conditions, not his! @PThus you, Pharaoh Cleopatra, have returned home to Alexandria, to Egypt.  It is now time to expand the glory of this magnificent city, founded by the Great Alexander whose tomb is still frequented by visitors.  Alexandria's renowned Great Library continues to attract scholars from all over the world; the bright beacon of the wondrous Pharos Lighthouse still burns so that seafarers can safely make their way through the treacherous waters of the harbor.  Now you can further enrich the beauty of the city by constructing the expansive Caesareum in honor of your former lover and your young son. Additionally, ensure your own successful passage into the afterlife by building another mausoleum so that you can be duly worshipped after your journey into the Field of Reeds.   @PThe next time Mark Antony calls for you, perhaps he will employ a bit more tact?"
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
            text: "Antony and Cleopatra",

        }
        content {
            text: "@POh noble Pharaoh Cleopatra VII, consort of Caesar and now Antony, the destiny of Egypt is in your hands, but your hands now nest in those of a Roman, Mark Antony - and he is deeply embroiled in the struggle for control of Rome and its legions.   @PNeeding Egypt's inestimable resources, but also desiring your love and affection, Antony agreed to your demand of marriage.  Unfortunately, word of this new union has scandalized Rome!  As you were aware, Antony was still wed to Octavia, sister of Octavian, legal heir of Caesar and, with Antony, joint wielder of Rome's might.  But with news of the polygamous ways of Antony, this relationship has become severely strained.  Octavian feels that Antony has slurred not only the honor of his sister and his family, but the prestige of Rome as well.  To settle this matter of honor, and to bring to an end the struggle for ultimate control of Rome, Octavian has duly challenged your lover, Antony to do battle.  With this in mind Antony, accompanied by you and your Egyptian fleet, has found a location on the Greek mainland near Actium for a camp.  The site offers a good harbor with many potential berths for your ships.   @PYou must quickly build up your military, especially the naval arm. Octavian has vowed to return in September of the year 31. @PNow your fate and Mark Antony's, as well as the fate of Egypt and Rome, depend once again upon the performance of military might."
        }
    }
    message_mission_thutmose_valley {
        id: 447,
        type: 3,
        size [40, 30]
        title {
            text: "Thutmose in the Valley",

        }
        subtitle {
            text: "The First Tomb",

        }
        content {
            text: "@PAfter many brilliant victories on distant battlefields defending the lands and people of Egypt, Pharaoh Thutmose, as all must eventually, has turned his thoughts to preparations for his travel into the afterlife.  To ensure that this journey is successful, Pharaoh wishes you to begin construction of his tomb at your earliest convenience.  Establish a village on the west bank of the Nile to provide a pool of capable workers.  Locate a suitable site for his tomb in the cliffs to the west of the village.  You will need skilled stonemasons to cut the tomb's many chambers from the rock, and talented artisans to plaster and paint the rooms.   @PTo provide light for the workers laboring in the far recesses of the tomb you will need to establish lamp maker shops.   Supply the lampmaker with pottery and imported oil for the fuel.  Plant fields of henna to provide a source of dye for brilliant colors the paint makers will need."
        }
    }
    message_mission_tutankhamun_valley {
        id: 448,
        type: 3,
        size [40, 30]
        title {
            text: "Tut in the Valley",

        }
        subtitle {
            text: "Death of Tutankhamun",

        }
        content {
            text: "@PA terrible tragedy has befallen our beloved young Pharaoh, Tutankhamun!  His reign, which once held much promise of glory, has been unmercifully cut short by the hand of fate.  It is time for the workers of Deir el-Medina to again prepare an eternal resting chamber for the Pharaoh.  With his unexpectedly early death, it is imperative that you compel your workers to exert maximum effort.  Tutankhamun's tomb must be fully stocked with provisions for his journey into the afterlife and ready to receive his hallowed remains within a few very short years.  Speed is of the utmost importance!"
        }
    }
    message_mission_seti_valley {
        id: 449,
        type: 3,
        size [40, 30]
        title {
            text: "Seti in the Valley",

        }
        subtitle {
            text: "Tomb for a Pharaoh",

        }
        content {
            text: "@POur most powerful Pharaoh, Seti, son of Ramses I, has declared that the present is the proper time to begin to prepare for his journey into the afterlife.  To this end you will begin the excavation of his royal tomb in the Valley of the Kings.  No effort is to be spared by your workers in its preparation.  Proper measures must be taken to ensure that, when completed, its craftsmanship will be unrivaled for many years to come. @PBut, as construction on this royal project proceeds, take due precautions against vandals!  Already there have been reports of bands of greedy criminals intent on enriching themselves by defiling the tombs and disturbing the peace of Egypt's eternally resting pharaohs.  Do not let this unholy act disgrace the royal tombs in The Valley or as sure as the sun rises in the east your standing in the Kingdom will be smirched."
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
            text: "Lands of the Levant",

        }
        content {
            text: "@PHail royal governor, regent of the Levant and loyal subject of our Pharaoh, the son of Ra.  It is indeed fortunate to live in this time when Egypt's benevolent hand stretches from the far reaches of Nubia to the shores of the Levant.  Infinite is the wisdom of our new Pharaoh, the most revered Ramses II, and great is his vision, for it is he that has dispatched you to rule in this fine land, now part of the ever-expanding domain of Egypt.  @PThis region, while still fraught with dangers, has many riches that must be exploited.  The verdant hills are ripe with tall trees yielding fine wood, ideal for fashioning chariots and useful in many forms of construction.  Seams of copper, while not abundant, can also be found, and will be most useful in fashioning strong weapons.  Wood and copper, so rare in our homeland, will surely be welcomed when shipped back in quantity.  It is therefore entrusted that you will oversee the establishment of a mighty port of commerce from which these valuable commodities can be exported.  Pharaoh and the people of Egypt will be most grateful! @PBut take care!  Ensure that your own trusted soldiers are equipped with fast chariots and strong weapons, for the Hittites, though smitten by Seti, father of Pharaoh, are still dangerous and may challenge our rightful authority in this bountiful land.  A strong military presence in this new territory may be necessary to quell insurrection, and will undoubtedly be most useful in the future. @PFinally, to remind the people of this region to whom they must now pay homage, Pharaoh Ramses II deems it appropriate that you erect an obelisk proclaiming his glories."
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
            text: "The Battle of Qadesh",

        }
        content {
            text: "@PThe land of Amurra, close by the Levantine coast, trembles beneath the hoof and foot of your mighty legions, blessed Pharaoh.  This region may be blessed with rare gems but it is also rich with discord.  Armed Hittites, led by the wretched King Mutwatalli, once again seek to contest control of this land, rightfully ours.  Captured spies speak of how his hostile bands are still far off to the north and thus pose no threat.  But is this to be believed?  Wise is the warrior who does not drop his shield in battle.   @PTo quell such rumors of insurrection you, our most revered Pharaoh, Ramses II, son of Ra, have arrived at the fortress town of Qadesh.  Already camps of two of your feared charioteer companies have been established on its outskirts.  But these are not all.  At your immediate disposal are other veteran troops - namely the experienced troops so recently engaged near Sumur.  But take heed!  It might be advisable to delay deployment of these valuable assets until the need for them is most obvious, for wise also is the warrior who has a bevy of trusted troops to summon at the height of battle. @POnce the miserable foe has been vanquished it will be necessary to revive the stagnant economy of Qadesh so that it too will contribute to the glory of Egypt.  Collect valuable gems and hire skilled jewelers to fabricate exquisite goods for Pharaoh's loyal subjects.  Luxury items of such rare beauty will surely be in much demand!"
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
            text: "Colossi of Abu Simbel",

        }
        content {
            text: "@PThe glory of our pharaoh, Ramses II, pervades the land.  So that the legacy of his reign will live forever it has been decreed that a great monument and temple dedicated to his rule be constructed deep in Nubia - and Pharaoh himself has selected the perfect spot for this creation.  From the rose-colored sandstone cliffs overlooking the Nile's west bank at Abu Simbel you will oversee the sculpting of four massive seated figures of His Majesty.  Surfaces of the monument, cut from the living rock, will proclaim the heroic deeds of Pharaoh during his great triumph at the battle of Qadesh.  This massive monument, while heralding the heroics of our leader, will also serve as a reminder to the peoples of Nubia of the greatness and power of Egypt, for, while Nubia is rich in deposits of gold and other rare gems, its people have always sat uneasily under Egyptian dominion.  To this end you should be ever prepared for defense, and be able to dispatch troops should Pharaoh need them. @PSandstone can be exported for construction elsewhere in the kingdom, as can other items that you should be able to produce from the bountiful resources of the region.  Precious little wood can be found, however.  You will no doubt have to establish a trade route to import this commodity, for it will be needed for the immense sculpture's scaffolding."
        }
    }
    message_mission_ramses_valley {
        id: 453,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses in the Valley",

        }
        subtitle {
            text: "An Unsurpassed Resting Place",

        }
        content {
            text: "@PIt has been many long and glorious years since our Pharaoh, the most revered Ramses II, accepted the crook and flail from his father, Seti I.  With the blessings of Ra, he will continue to reign for many more still.  Nevertheless, it is time to begin to cut into the bowels of the earth and prepare the eternal resting place for our vaunted leader.  He has supplied your tomb architect with a plan for the largest tomb yet constructed, surpassing even that of his sire.  It is now up to you to ensure that this royal request is brought to successful completion. @PBut be forewarned!  There is an alarming degree of unrest amongst some independent minded workers and slaves, both locally and in Lower Egypt.  They follow a man that was once raised in the court of our Pharaoh, and have threatened to call their God for divine interference.  They hope that, with such deific help, they can have their way.  Even now priests and holy men are debating the validity of these threats.  While we patiently await their opinions it might be prudent to be prepared for the unexpected."
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
            text: "The Sea People Land",

        }
        content {
            text: "@PThe rumblings of distress and discontent to the west have become more ominous recently.  Scouts report that several barbarian tribes speaking strange tongues have arrived on the shores of Kyrenaica to our west.  To make matters worse, these peoples now walk hand-in-hand with Maraye, the son of Did, king of the Libyans and Pharaoh's enemy.   @PWord has now reached Pharaoh Merneptah that these vile people, with all of their women, children and worldly possessions close behind, will soon be headed eastward, toward the fertile Nile delta - our homeland! - in search of a place to settle.  Already there have been minor clashes at the northern oases of Siwi and Farafra.  Your delta town of Pi-yer now stands in their way.  In a short while this slow-moving band of savages could be on your doorsteps.  Pharaoh has decreed that, should they arrive, they must not be allowed to penetrate further! @PYou will need to import wood from which to construct sturdy warships, and copper for weapons.  It is your fortune that the previously troublesome Hittites are now peaceful, thanks to the great victory at Qadesh by Ramses II, sire of the beloved Merneptah. Make your town strong, and brace your loyal troops for mortal combat."
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
            text: "Repel the Assyrians",

        }
        content {
            text: "@PSince the days of the great Shabaka, unifier of Upper and Lower Egypt and sire of Pharaoh Taharqa, conflict with the aggressive Assyrians has been the norm.  While he still lived, Pharaoh Shabaka saw that it was proper to aid our brothers in Palestine who were chaffing under the harsh rule of Assyria.  Beware!  The minions of the heathen king Asarhaddon are again on the march and, as always, their eyes are on the fertile lands of Egypt.  It is now your turn for glory!  As Royal Mayor of Pelusium, you will be expected to defend against the series of attacks by these accursed foes. Located on the eastern rim of the Nile delta, your border fortress is on the front line of Egypt's outer defenses. @PProperly training your soldiers and establishing trading links to secure weapons - or raw materials from which to make your own - will be important. @PDo not falter!  A strong military stand is vital to insure the continued independence of Egypt.  If you can hold out for a mere seven years, victory will be assured.  Taharqa, the great Pharaoh, second son of Shabaka, will be watching!"
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
            text: "Rebirth of a Navy",

        }
        content {
            text: "@PFor many generations Egyptians have been suffering under the cruel fist of Persia.  Babylon's grip upon our sacred lands is, however, not as strong as it once was.  While our accursed oppressors have been busy meddling in the politics of Greece, a series of revolts in Egypt has finally managed to loosen the hated Persian yoke.  Now, however, word has reached Pharaoh Achoris that a force commanded by Fleet Admiral Conon (a Greek lackey receiving Persian gold) has been dispatched by Artaxerxes II and is headed for our shores.  Pharaoh Achoris has wisely determined that a strong naval presence in the Nile is needed to thwart this incursion.  As Royal Governor of Tanis for the next ten years, you must build strong ships and train stalwart troops to guard the approaches by water and land. @PYou will need to establish a trade route with Enkomi to import sturdy wood with which to construct a fleet.  Copper can also be imported from Enkomi, on the island of Cyprus.  This trade route is precarious at best, as it runs close to the Levant coast, under control of our foe.  Supplying the Pharaoh with needed supplies should help to supplement your income.   @PBe aware that funds are tight in these troubled times.  To succeed, you must be savvy in business and trade as well as a skillful commander."
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
            text: "Alexander the Great",

        }
        content {
            text: "@PThe great Alexander, son of Phillip II of Macedon and scourge of the Babylonian empire, blessed the lands of Egypt with his presence.  With his coming, the final corrupt Persian satrap has hastily fled.  After sacrificing to the Apis bull at Memphis, Alexander has been accepted as Pharaoh.  All the people rejoice!  Before setting off on his journey to the Oracle of Amun in the Siwi Oasis, however, our leader decided to found a new city, one that he wishes to someday be the capital of his vast and expanding empire.  In his infinite wisdom, he has appointed you to be this future city's first mayor! @PThe great Alexander has bestowed upon you a generous endowment of funds from which to begin construction, and has given you the services of the esteemed Greek architect Dinocrates.  In a mere dozen years he expects you to have the commercial, cultural and military might of his city developed to high standards, as he has vowed to return.  @POur leader has even taken the time to trace the positions of the two main thoroughfares of his city.  The Canopic Street runs along an east-west axis; the other main avenue is perpendicular to it and heads inland from Cape Lochias southward toward Lake Mariut. @PAs trusted overseer of this project, you should quickly build port facilities and establish lucrative trade routes.  There should be many customers for our products, especially wheat, barley, papyrus and linen.  Do not neglect the cultural aspects of this city, nor its military, however, as there are still roaming vandals that wish to rob Egypt of her wealth."
        }
    }
    message_mission_ptolemy_alexandria_2 {
        id: 458,
        type: 3,
        size [40, 30]
        title {
            text: "Ptolemy's Alexandria",

        }
        subtitle {
            text: "A Beacon of Light",

        }
        content {
            text: "@PThe legacy of Alexander the Great lives on in our proud city. Even though his mortal remains rest in Alexandria's Mausoleum, his great city continues to thrive.  It is up to you, Ptolemy I Soter, to carry on with the job the noble Alexander began.  Since its founding by Alexander barely 30 years ago, the city has become a powerful commercial hub, supplying much-needed foodstuffs and items of luxury to much of the surrounding area.  To further its economic progress and to ensure safe passage of the many ships entering the great harbor, you should construct a massive Lighthouse on Pharos Island, near the mouth of the harbor.  This structure's beacon of light will guide distant seafarers safely into the harbor, ensuring that they do not founder on its tricky shoals. @PImportant as commerce is, however, you cannot ignore the cultural and intellectual advancement of our society.  Under your leadership Alexandria can now become the intellectual capital of the known world as well.  Gather works of knowledge from near and far, and build a great Library in which to keep them.  As sure as ants are attracted to honey, learned scholars from all over will journey to this unrivaled center of knowledge and learning.   @PTo build these great monuments you will need to import a building material, such as white marble, that will be suitable for such great structures.  Enkomi, on the island of Cyprus, is a good source for this material.   @PLastly, do not ignore your military.  There always seems to be unrest in one place or another.  It might be necessary to dispatch troops to distant frontiers to protect Egypt's interests and defend her honor."
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
            text: "Caesar and Cleopatra",

        }
        content {
            text: "@PThe indelicate grasp of the Roman Empire grows stronger and reaches farther with each passing day.  Even the deadly political power struggles of Rome have reached our land.  With the recent assassination of Pompey on the shores of Egypt, Julius Caesar now has complete control of Rome's mighty legions and has cast his eyes upon the riches of Egypt - and upon the beauty of our beguiling pharaoh, Cleopatra VII, daughter of Ptolemy XII Auletes.  Our clever leader is not easily outdone on the battlefield of wits, however.  If Caesar desires to use her as a means to further Rome's influence in Egypt, so too does she plan to employ him as an instrument of maintaining the dynastic power of our great land. @PCaesar's arrival in Alexandria with his unpopular Romans has sparked an uprising among its independent minded citizens.  An unruly mob, egged on by Cleopatra's younger brother Ptolemy XIII, has cornered Caesar and his men in the royal quarter of the city.  Bitter street fighting has erupted, claiming many casualties.  In a bid to keep his seaward escape route open, Caesar burned the Egyptian fleet as it lay at anchor in Alexandria's harbor.  Unfortunately the conflagration spread to some shoreline warehouses, burning great quantities of papyrus scrolls belonging to the Great Library.   @PTo break the trap in which he now finds himself, Caesar has summoned the loyal Mithradates and his troops from Syria to effect his rescue. After successfully storming the border fortress of Pelusium, Mithradates has force-marched his men around the apex of the Nile delta so to approach Alexandria from the southeast. The lead elements of this force are currently encamped on the outskirts of the small village of Maritis, on the eastern shore of Lake Mariut, preparing for the final leg of their journey.  @PThe baleful Ptolemy XIII has learned of the approach of these reinforcements.  In response he has marched the bulk of his more numerous army southeastward out of Alexandria.  A decisive battle on the eastern shore of Lake Mariut is about to ensue.  Can you, commanding Mithradates' Roman legions, defeat Ptolemy's rebellious Egyptian army and break through to Caesar and Cleopatra in Alexandria?  Their fate rests in your hands."
        }
    }
    message_mission_cleopatra_alexandria_2 {
        id: 460,
        type: 3,
        size [40, 30]
        title {
            text: "Cleopatra's Alexandria",

        }
        subtitle {
            text: "The Legacy of a Queen",

        }
        content {
            text: "@PCaesar's bloody death at the point of assassins' daggers cast the Roman world into turmoil and has driven you, our Pharaoh, Cleopatra VII, into grief and mourning.  Gone is your lover, mentor, confidant and powerful ally.  Octavian, his teen-aged adopted great-nephew, has been named as heir but the more experienced Mark Antony, previously a consul to Caesar, has become the nominal head of state, somewhat to the ire of the young Octavian.  Not surprisingly, Caesar's will made no mention of your son by him, Ptolemy Caesar, popularly known as Caesarion. Desiring safety for yourself and your child and, as always, seeking to preserve the power of Egypt, you have departed Rome for Alexandria.  @PDespite all the leagues between Rome and yourself, you cannot leave behind all of its internecine squabbles.  Powerful men still vie for power - your support and the access to the riches of Egypt would be a great asset to any faction.  For you to back a winner in this power struggle is critical; siding with the loser could easily result in the end of Egypt.  The dramatic showdown between the rival Roman factions recently occurred at Philippi where Mark Antony's Caesarians decisively beat the forces of Brutus and Cassius.  Antony, Octavian and Lipidus have now carved up the empire for joint rule, with Antony claiming the eastern portion, which includes Egypt. @PNot long after the battle, Mark Antony summoned you to join him at Tarsus in Asia Minor, so that you might better explain why you had been slow to cast your lot with the Caesarians.  Not one to be summoned like a lapdog, you wisely declined to respond.  After all, you know better than most that it is much better to see a Roman under your own terms and conditions, not his! @PThus you, Pharaoh Cleopatra, have returned home to Alexandria, to Egypt.  It is now time to expand the glory of this magnificent city, founded by the Great Alexander whose tomb is still frequented by visitors.  Alexandria's renowned Great Library continues to attract scholars from all over the world; the bright beacon of the wondrous Pharos Lighthouse still burns so that seafarers can safely make their way through the treacherous waters of the harbor.  Now you can further enrich the beauty of the city by constructing the expansive Caesareum in honor of your former lover and your young son. Additionally, ensure your own successful passage into the afterlife by building another mausoleum so that you can be duly worshipped after your journey into the Field of Reeds.   @PThe next time Mark Antony calls for you, perhaps he will employ a bit more tact?"
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
            text: "Antony and Cleopatra",

        }
        content {
            text: "@POh noble Pharaoh Cleopatra VII, consort of Caesar and now Antony, the destiny of Egypt is in your hands, but your hands now nest in those of a Roman, Mark Antony - and he is deeply embroiled in the struggle for control of Rome and its legions.   @PNeeding Egypt's inestimable resources, but also desiring your love and affection, Antony agreed to your demand of marriage.  Unfortunately, word of this new union has scandalized Rome!  As you were aware, Antony was still wed to Octavia, sister of Octavian, legal heir of Caesar and, with Antony, joint wielder of Rome's might.  But with news of the polygamous ways of Antony, this relationship has become severely strained.  Octavian feels that Antony has slurred not only the honor of his sister and his family, but the prestige of Rome as well.  To settle this matter of honor, and to bring to an end the struggle for ultimate control of Rome, Octavian has duly challenged your lover, Antony to do battle.  With this in mind Antony, accompanied by you and your Egyptian fleet, has found a location on the Greek mainland near Actium for a camp.  The site offers a good harbor with many potential berths for your ships.   @PYou must quickly build up your military, especially the naval arm. Octavian has vowed to return in September of the year 31. @PNow your fate and Mark Antony's, as well as the fate of Egypt and Rome, depend once again upon the performance of military might."
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
            text: "The First Tomb",

        }
        content {
            text: "@PAfter many brilliant victories on distant battlefields defending the lands and people of Egypt, Pharaoh Thutmose, as all must eventually, has turned his thoughts to preparations for his travel into the afterlife.  To ensure that this journey is successful, Pharaoh wishes you to begin construction of his tomb at your earliest convenience.  Establish a village on the west bank of the Nile to provide a pool of capable workers.  Locate a suitable site for his tomb in the cliffs to the west of the village.  You will need skilled stonemasons to cut the tomb's many chambers from the rock, and talented artisans to plaster and paint the rooms.   @PTo provide light for the workers laboring in the far recesses of the tomb you will need to establish lamp maker shops.   Supply the lampmaker with pottery and imported oil for the fuel.  Plant fields of henna to provide a source of dye for brilliant colors the paint makers will need."
        }
    }
    message_mission_tutankhamun_valley_2 {
        id: 463,
        type: 3,
        size [40, 30]
        title {
            text: "Tut in the Valley",

        }
        subtitle {
            text: "Death of Tutankhamun",

        }
        content {
            text: "@PA terrible tragedy has befallen our beloved young Pharaoh, Tutankhamun!  His reign, which once held much promise of glory, has been unmercifully cut short by the hand of fate.  It is time for the workers of Deir el-Medina to again prepare an eternal resting chamber for the Pharaoh.  With his unexpectedly early death, it is imperative that you compel your workers to exert maximum effort.  Tutankhamun's tomb must be fully stocked with provisions for his journey into the afterlife and ready to receive his hallowed remains within a few very short years.  Speed is of the utmost importance!"
        }
    }
    message_mission_seti_valley_2 {
        id: 464,
        type: 3,
        size [40, 30]
        title {
            text: "Seti in the Valley",

        }
        subtitle {
            text: "Tomb for a Pharaoh",

        }
        content {
            text: "@POur most powerful Pharaoh, Seti, son of Ramses I, has declared that the present is the proper time to begin to prepare for his journey into the afterlife.  To this end you will begin the excavation of his royal tomb in the Valley of the Kings.  No effort is to be spared by your workers in its preparation.  Proper measures must be taken to ensure that, when completed, its craftsmanship will be unrivaled for many years to come. @PBut, as construction on this royal project proceeds, take due precautions against vandals!  Already there have been reports of bands of greedy criminals intent on enriching themselves by defiling the tombs and disturbing the peace of Egypt's eternally resting pharaohs.  Do not let this unholy act disgrace the royal tombs in The Valley or as sure as the sun rises in the east your standing in the Kingdom will be smirched."
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
            text: "Lands of the Levant",

        }
        content {
            text: "@PHail royal governor, regent of the Levant and loyal subject of our Pharaoh, the son of Ra.  It is indeed fortunate to live in this time when Egypt's benevolent hand stretches from the far reaches of Nubia to the shores of the Levant.  Infinite is the wisdom of our new Pharaoh, the most revered Ramses II, and great is his vision, for it is he that has dispatched you to rule in this fine land, now part of the ever-expanding domain of Egypt.  @PThis region, while still fraught with dangers, has many riches that must be exploited.  The verdant hills are ripe with tall trees yielding fine wood, ideal for fashioning chariots and useful in many forms of construction.  Seams of copper, while not abundant, can also be found, and will be most useful in fashioning strong weapons.  Wood and copper, so rare in our homeland, will surely be welcomed when shipped back in quantity.  It is therefore entrusted that you will oversee the establishment of a mighty port of commerce from which these valuable commodities can be exported.  Pharaoh and the people of Egypt will be most grateful! @PBut take care!  Ensure that your own trusted soldiers are equipped with fast chariots and strong weapons, for the Hittites, though smitten by Seti, father of Pharaoh, are still dangerous and may challenge our rightful authority in this bountiful land.  A strong military presence in this new territory may be necessary to quell insurrection, and will undoubtedly be most useful in the future. @PFinally, to remind the people of this region to whom they must now pay homage, Pharaoh Ramses II deems it appropriate that you erect an obelisk proclaiming his glories."
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
            text: "The Battle of Qadesh",

        }
        content {
            text: "@PThe land of Amurra, close by the Levantine coast, trembles beneath the hoof and foot of your mighty legions, blessed Pharaoh.  This region may be blessed with rare gems but it is also rich with discord.  Armed Hittites, led by the wretched King Mutwatalli, once again seek to contest control of this land, rightfully ours.  Captured spies speak of how his hostile bands are still far off to the north and thus pose no threat.  But is this to be believed?  Wise is the warrior who does not drop his shield in battle.   @PTo quell such rumors of insurrection you, our most revered Pharaoh, Ramses II, son of Ra, have arrived at the fortress town of Qadesh.  Already camps of two of your feared charioteer companies have been established on its outskirts.  But these are not all.  At your immediate disposal are other veteran troops - namely the experienced troops so recently engaged near Sumur.  But take heed!  It might be advisable to delay deployment of these valuable assets until the need for them is most obvious, for wise also is the warrior who has a bevy of trusted troops to summon at the height of battle. @POnce the miserable foe has been vanquished it will be necessary to revive the stagnant economy of Qadesh so that it too will contribute to the glory of Egypt.  Collect valuable gems and hire skilled jewelers to fabricate exquisite goods for Pharaoh's loyal subjects.  Luxury items of such rare beauty will surely be in much demand!"
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
            text: "Colossi of Abu Simbel",

        }
        content {
            text: "@PThe glory of our pharaoh, Ramses II, pervades the land.  So that the legacy of his reign will live forever it has been decreed that a great monument and temple dedicated to his rule be constructed deep in Nubia - and Pharaoh himself has selected the perfect spot for this creation.  From the rose-colored sandstone cliffs overlooking the Nile's west bank at Abu Simbel you will oversee the sculpting of four massive seated figures of His Majesty.  Surfaces of the monument, cut from the living rock, will proclaim the heroic deeds of Pharaoh during his great triumph at the battle of Qadesh.  This massive monument, while heralding the heroics of our leader, will also serve as a reminder to the peoples of Nubia of the greatness and power of Egypt, for, while Nubia is rich in deposits of gold and other rare gems, its people have always sat uneasily under Egyptian dominion.  To this end you should be ever prepared for defense, and be able to dispatch troops should Pharaoh need them. @PSandstone can be exported for construction elsewhere in the kingdom, as can other items that you should be able to produce from the bountiful resources of the region.  Precious little wood can be found, however.  You will no doubt have to establish a trade route to import this commodity, for it will be needed for the immense sculpture's scaffolding."
        }
    }
    message_mission_ramses_valley_2 {
        id: 468,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses in the Valley",

        }
        subtitle {
            text: "An Unsurpassed Resting Place",

        }
        content {
            text: "@PIt has been many long and glorious years since our Pharaoh, the most revered Ramses II, accepted the crook and flail from his father, Seti I.  With the blessings of Ra, he will continue to reign for many more still.  Nevertheless, it is time to begin to cut into the bowels of the earth and prepare the eternal resting place for our vaunted leader.  He has supplied your tomb architect with a plan for the largest tomb yet constructed, surpassing even that of his sire.  It is now up to you to ensure that this royal request is brought to successful completion. @PBut be forewarned!  There is an alarming degree of unrest amongst some independent minded workers and slaves, both locally and in Lower Egypt.  They follow a man that was once raised in the court of our Pharaoh, and have threatened to call their God for divine interference.  They hope that, with such deific help, they can have their way.  Even now priests and holy men are debating the validity of these threats.  While we patiently await their opinions it might be prudent to be prepared for the unexpected."
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
            text: "History",
        }
        content {
            text: "For well over three millennia various peoples have used the shrub-like henna plant as a source for dye.  Henna (with the scientific name of Lawsonia inermis) is from the Lythraceae family and is originally native to northern Africa and the Middle East.  When crushed, its leaves and branches yield an orange-red dye that, when properly applied, can be used for coloring hair, fingernails, and skin.  Even today henna is commonly used in many religious rituals and burial rites in Asia, the Middle East and Africa, and is the basic coloring agent of many of the popular 'temporary tattoos'.  Henna is also the primary coloring agent for wide variety of hair dyes."
        }
    }
    message_mission_paint_maker {
        id: 470,
        
        size [30, 28]
        title {
            text: "Paint Maker",
        }
        content {
            text: "Paint makers need a supply of @469henna to produce paint. The crushed leaves and stalks of the henna plant are used to produce various dyes, which are necessary for the manufacture of paints. Henna is grown on @91Henna&Farms, or a @47trade&route can be set up to import it.  @POnce a Paint Maker has a steady supply of labor, road access and has had a load of henna delivered to it, you will see the paint makers hard at work producing paint. When production is complete the paint will be delivered to a @4Storage&Yard. The paint is then used by @363Artisans when painting the @478Royal&Burial&Tombs. @PDue to their unpleasant odors and noise, Paint Makers are @56not&desirable neighbors. @L@LClick @472here to find out more about paint making in ancient Egypt."
        }
    }
    message_illness_video {
        id: 471,
        type: 2,
        
        size [30, 20]
        title {
            text: "Illness",
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
            text: "Artisans",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "While most of the structures of ancient Egypt employed artists to apply finishing touches, it is in the New Kingdom's tombs in the @475Valley&of&the&Kings that these talented artists' extraordinary skills really shine. Practically every square inch of the interior walls and ceilings of these underground tombs proclaimed the greatness of the deceased through skillfully painted hieroglyphics and other illustrations. @PDespite the extravagance and detail of their illustrations, the ancient artists had a fairly limited palette of colors to work with and used natural brushes made from @94reeds or fibrous wood, such as palm ribs. Their pigments were frequently pre-mixed in small shops that manufactured them from natural dyes (such as @469henna ) and other natural pigments (such as calcium carbonate, charcoal, iron oxide, realgar, orpiment, azurite and malachite) ground into powder. These might then be mixed with a binding agent, such as plant gum or animal glue, and applied as paint. @PMany specialized artists worked together to create splendid bas-relief images in the tombs. First, plaster was prepared from a mixture of @190clay, water and a whitening agent and applied to the tomb's walls. Then, a rough design was traced in red onto the freshly plastered walls. A master draughtsman then refined this outline, usually in black. A master painter then made further corrections and added details to guide the bas-relief sculptor that followed him. Paint was then applied in large, flat colors. Final detailing, such as outlines and interior details, was then applied by another master artist."
        }
    }
    message_building_lamp_maker {
        id: 473,
        
        size [30, 28]
        title {
            text: "Lamp Maker",
        }
        content {
            text: "The Lamp Maker prepares lamps whose light helps guide workers through the dark passageways of a @478Royal&Burial&Tomb.  @PTo make lamps, the Lamp Maker needs a supply of pottery and oil. A @1Potter can supply pottery or it can be imported from a @47trade&partner. @476Oil can only be imported. @PA lamp maker must have road access and a nearby source of labor. Once the Lamp Maker has received enough pottery and oil, you'll see the lamp makers hard at work, filling the pottery with oil to make lamps. @PLamp Makers have a negative effect on @56desirability, so don't place them too close to your housing developments. @L@LClick @474here to learn more about the lamps of ancient Egypt."
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
            text: "Lamps",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Ancient Egyptians manufactured small ceramic lamps that burned natural @476oils or rendered animal fat as fuel. Such lamps provided a needed light source for craftsmen working deep inside a burial tomb."
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
            text: "Valley of the Kings",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "@PThe Valley of the Kings was the necropolis for five centuries of pharaohs, ca. 1539-1075 BC, including Thutmose I, Tutankhamun and Ramses the Great (Ramses II).  Located on the western bank of the Nile across from the temple complex at Thebes, the Valley is overlooked by el-Qurn, an almost pyramid-shaped mountain that receives the last blessings of Ra each day before the sun sets.  Between the Valley and the great Nile are the royal mortuary temples inscribed to the pharaohs who expected to enjoy their afterlives in the Valley's tombs.  A nearby village, Deir el-Medina, housed hundreds of workers and their families. @PSpecialized workers prepared the Royal Burial Tombs, and each had an important task to carry out.  @385Masons chiseled steps and passageways into the limestone cliffs.  Stone pillars were left to hold up the roofs of large chambers.  The hewn rooms were smoothed and plastered before the @472artisans arrived to decorate the ceilings and walls with carved bas-reliefs and paintings that would help guide the pharaoh through his afterlife.  The deceased king was placed in his sarcophagus and sealed into the tomb with many treasures worthy of the deified status granted him by the ancient Egyptians.  Because of these great treasures, the tombs were frequently robbed, sometimes by the very people who were placed to guard them. @PEuropean archaeologists rediscovered the Valley of the Kings in the early 1800s.  In 1922 Howard Carter broke through the sealed tomb of Tutankhamun to find many treasures, including a golden sarcophagus.  Over the centuries, flash floods have filled many of the tombs with silt and debris, and it is a good bet that there are passageways - and maybe even some tombs - as yet undiscovered in the Valley."
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
            text: "Oil",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "Most oils used by ancient Egyptians were imported from Greece, Cyprus and Phoenicia. Natural oils had many uses, such as fuel for @474lamps and for use in cooking. Oils were extracted from a variety of sources (most of which are still used today), such as sesame, linseeds, olives and natural animal fats."
        }
    }
    message_figure_tomb_robber {
        id: 477,
        
        size [30, 28]
        title {
            text: "Tomb Robber",
        }
        content {
            text: "@PWhere there's a tomb, there's treasure! A tomb robber is a type of criminal that appears if @39City&Sentiment is extremely poor. He'll only strike the city, however, if there's treasure to plunder. So, if your city doesn't have any tombs (either Pyramids, @371Mastabas, @368Mausoleums or @478Royal&Burial&Tombs), he won't bother to come to your city. He also won't bother if there aren't any @374burial&provisions to be had, either because the tomb didn't require that any be dispatched or because you haven't sent them to the tomb yet. @PSometimes, tomb robbers strike even when there is no sign of crime in the city. If professional tomb robbers receive word from their cronies that there are particularly valuable burial provisions in your city's tombs, they will unleash a crime wave. You have no way of predicting when a crime wave might occur.  @PAll tomb robbers have one goal in mind: to deprive an eternally sleeping Pharaoh of the riches and treasures that have been stored away in his tomb for use in the afterlife. To affect this scheme, the tomb robber must make his way to the tomb without being apprehended.  If he meets a constable or some soldiers on his way to the tomb, he is usually quietly and effectively 'detained,' although an extremely agile thief can sometimes still escape. If the tomb robber successfully reaches a burial monument, he will secret away with some previously dispatched burial provisions and your @35Kingdom&Rating will be adversely affected, as who would want to be governed by someone that is incapable of protecting the sanctity of his ancestors' graves? @PTomb robbers aren't picky about which tombs they strike. They are perfectly willing to try to steal from a monument that was already in the city before you began your rule. Luckily, these pre-existing tombs are well sealed, and a tomb robber won't be able to steal any burial provisions from them. However, people throughout Egypt will be so astounded that one of the oldest tombs was threatened that your Kingdom rating will take quite a tumble. @PBeware! If the tomb robber makes off with burial provisions you will need to replace each stolen item before the mission can be completed. @PFor more on crime in your city, click @36here. @L@LTo learn more about the burial tombs in ancient Egypt's Valley of the Kings, click @475here."
        }
    }
    message_building_royal_burial_tomb {
        id: 478,
        
        size [30, 28]
        title {
            text: "Royal Burial Tomb",
        }
        content {
            text: "@PBeginning in the New Kingdom period, ancient Egyptians began interring their pharaohs and other nobility in progressively elaborate tombs carved into the living rock in an almost inaccessible valley. @PFor work to commence on a Royal Burial Tomb you will first have to find a proper site.  Select 'Royal Burial Tomb' from the Religious Structures: Monuments list.  A large footprint appears.  The bulk of the monument must be placed on cliffs, except for the small entryway that juts out from its side. Move the footprint around the cliffs until you find a suitable spot. You'll know you've found a good place when the entire footprint turns green. Any red in the footprint indicates that you have not found a viable location for the monument. @PYou might find it easier to place the Royal Burial Tomb by temporarily flattening the cliffs. Simply press 'H' to flatten the cliffs, or choose 'Hide Cliffs' from the list of @18overlays. To raise the cliffs back to their lofty heights, press 'H' again or select 'Normal' from the overlay list. For particularly large tombs, you might also find pressing the 'M' key helpful. Pressing the 'M' key freezes the footprint in place, and you can then move your viewpoint to see if the site you've chosen is suitable. If it is, simply click the mouse button to set the monument in place. If the site is not appropriate, press 'M' again to free the footprint and continue looking for a site. @PAfter a site is selected, a shipment of lamps must be delivered to the tomb before any work can begin. Lamps are made by a @473Lamp&Maker and can also be imported from a @47trade&partner. Once 400 lamps are stored in one @4Storage&Yard, a peasant will drag a sled full of lamps to the construction site. @PAfter the lamps arrive to light their way, @363stonemasons roughly hew the tomb's many chambers from the solid rock. Once the stonemasons have completed their work in a chamber, skilled @363artisans will be summoned to begin plastering and painting the walls. These artisans will need a supply of @92clay for the plaster and paint from a @470Paint&Maker. The commodities will be delivered directily to the Artisans' Guild either by the manufacturers themselves or from a Storage Yard. If your city cannot produce one or both of these commodities, you may be able to @47import them. @PRight-click on a Royal Burial Tomb monument to visit its @369Construction&Foreman for a progress report. @L@LClick @475here to learn more about the Valley of the Kings and its Royal Burial Tombs."
        }
    }
    message_building_zoo {
        id: 479,
        
        size [30, 28]
        title {
            text: "Zoo",
        }
        content {
            text: "Zoos are a popular form of @49entertainment in any city. The zoo requires road access and laborers to tend the animals, as well as a supply of @89straw and @359game&meat for feed. Straw can be harvested from Grain Farms, and hunters from the Hunters' Lodge can procure game meat. You can also set up a @47trade&route to import these items. @PCheck with your @28Overseer&of&Diversions to see how many zoos your city has, and use the @18Entertainment&Overlay to view which houses have access to the zoo and to watch the zookeepers walking around the city. @PDespite the unique distractions resident in a zoo, citizens do not like living too near them, as the bellowing noises and strong odors emanating from the animals are quite offensive to any well-cultured Egyptian. Click @56here to learn more about desirability. @L@LTo learn more about zoos in ancient Egypt, click @480here."
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
            text: "History",
        }
        content {
            text: "Ancient Egyptians were fond of the fun and the unusual, and both could be found in quantity at a zoo. As Egypt's power and influence spread across several continents, many pharaohs received strange and exotic creatures from rulers of distant lands as gifts or tribute. These animals were presented to the pharaoh, and were then kept in special zoological gardens, which would inevitably be found a short distance from the ruler's palace. Evidently, the early zoos of Egypt were primarily for public spectacle and secondarily for study. Alexandria's Great Library purportedly had both a botanical garden and a zoological yard on its grounds."
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
            text: "History",
        }
        content {
            text: "From its inception, Alexander the Great hoped that Alexandria, the city at the mouth of the Nile that he founded and helped plan, would become a center of trade and culture for the Mediterranean basin. Less than fifty years after its founding in 331 BC, the booming metropolis had become a sophisticated hub of commerce, due in large part to its famed Great Library.  @PSoon after Alexander's unexpectedly early death in 323 BC, his expansive empire dissolved into three major regions. One of his closest friends and ablest generals, Ptolemy, was at the time de facto governor of Egypt. He took control of the reins of that ancient land, eventually becoming pharaoh (as Ptolemy I Soter) and thus continuing the Greek presence in Egypt begun by Alexander. It was Ptolemy that intercepted Alexander's funerary procession, bound for Macedonia, and brought his mortal remains to Alexandria for internment.  @PBesides personal glory and luxurious living, however, the early Ptolemaic rulers were, to their credit, also interested in bettering the culture of their city and its land. Alexandria, Egypt's new capital, was already the center of commerce for the known world; they wanted it to become the intellectual capital as well. To this end Alexandria's Great Library was conceived and built. The Great Library was mankind's first center of scholastic learning and research. The brilliant minds of antiquity here laid the foundations for the systematic study of astronomy, geography, literature, mathematics, medicine, and physics. It was here that Euclid first defined geometry and Eratosthenes accurately measured the circumference of the earth, arguing that India could be reached by sailing westward from Spain. @PThe Ptolemy's devoted much time and energy, and not a small portion of their wealth, to obtaining copies of every important manuscript known to man. To this end a law was passed proclaiming that every caravan and ship entering Alexandria was to be searched - not for contraband, but for articles of learning. Any map or scroll found was turned in to the library so that scribes could copy it. Thus Alexandria's scholarly haven eventually contained over 700,000 systematically cataloged papyri scrolls, including many now-lost masterpieces of art, literature and science, such as classics by Homer, Aristotle, Sophocles, Aeschylus and Euripedes.  @PBut all was not letters of learning. The legendary library's grounds also boasted a botanical gardens and a museum, as well as a temple to the nine muses (Greek gods and goddesses of the arts and sciences). A short stroll along a garden-lined palisade would take one to a @480zoo no doubt containing many exotic animals. Many were the ancient scholars that walked its colonnaded passages.  @PWhat led to the Great Library's demise is not completely clear. A good portion of its priceless works was evidently destroyed in a fire that occurred when Julius Caesar torched the ships of Cleopatra VII's brother. By the fourth century AD, as Christianity's influence was spreading, most of the remaining manuscripts of the Library were apparently destroyed in an effort to stamp out all relics of paganism and heresy. Later, in 640 AD, Arabs that swept through the almost abandoned city probably burned for fuel whatever scrolls had survived. Of the 123 plays of Sophocles that were known to be in the Great Library, only seven remain today."
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
            text: "History",
        }
        content {
            text: "Cleopatra VII began the Caesareum. It originally consisted of a small temple or altar in the middle of a sanctuary, apparently intended for the worship of Mark Antony's cult. His suicide, followed shortly thereafter by Cleopatra's death, however, meant that this monument was completed by their rival, Octavian (Augustus Caesar), who completed the structure and dedicated it to his own cult. Two obelisks (commonly referred to as Cleopatra's Needles, even though she had nothing to do with them), for centuries were prominent landmarks along Alexandria's Eastern Harbor shoreline. These obelisks, transported to Alexandria from Heliopolis by order of Octavian, marked the entrance to Caesareum long after the rest of it was destroyed. Both of the obelisks have now been removed (one stands in New York City's Central Park, the other along the banks of the Thames in London). @PPrecise details about the actual structures of the Caesareum are not known. Our knowledge of it comes from brief descriptions by some ancient authors. Its architecture, like the other great monuments of Alexandria, was in the Greek style. It evidently contained a central sanctuary set amidst open-air courts and surrounded by stoas (columned walkways) that probably served as outer 'walls' for the monument. Rooms and porticos set amidst the stoas contained scrolls and could be used for assemblies or quiet study."
        }
    }
    message_plague_of_locusts {
        id: 483,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Plague of Locusts",
        }
        content {
            text: "We have received reports of mad swarms of ravenous locusts devouring the crops throughout Egypt.  Beware their onslaught during the next growing season!"
        }
    }
    message_plague_of_frogs {
        id: 484,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Plague of Frogs",
        }
        content {
            text: "An ugly curse has descended over the land!  Multitudes of frogs pollute our streets and dwellings, forcing residents from their homes!"
        }
    }
    message_hailstorm {
        id: 485,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Hailstorm",
        }
        content {
            text: "Death and destruction is on the wind!  A savage hailstorm has come to deliver a deadly rain of ice.  May the gods have mercy on anyone not sheltered from this evil curse, for they have little hope of surviving!"
        }
    }
    message_river_of_blood {
        id: 486,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "River of Blood",
        }
        content {
            text: "Woe unto us!  The waters, once the source of life and nourishment, are poisoned with blood.  How long will it be until this vulgar blight is lifted?"
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
            text: "Pharos Lighthouse",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "@PEven though Alexandria's location was ideal for a commercial port, with lots of coastline and a large natural harbor, its points of egress were rife with dangerous sandbars.  It was therefore conceived that a tall lighthouse on Pharos island, near the mouth of the harbor, would not only be of benefit to mariners, but (at least if magnificent enough) would also be a wondrous new attraction to boost Alexandria's renown.  @PThe Pharos lighthouse, as it came to be known, was partially constructed largely of Proconnesian white marble, much of it imported from Princes' Islands off the coast of present-day Turkey.  It was built in three large tiers:  the base, or lowest tier, was quadrangular; the middle tier was octagonal; the topmost tier was cylindrical.  A mammoth spiral stairway leading to the top even allowed pack animals to haul wood to the top to feed the bright fire that burned there.  Topping the spectacular structure was (by some accounts) a statue of Poseidon; another account contends it was an image of Zeus - or perhaps a statue of both of them. @PThe construction of Alexandria's Pharos lighthouse was begun by the first Ptolemy (Auletes), but wasn't finished until 283 BC during the reign of his son, Ptolemy Philadelphus.  By all accounts it was an incredible sight, more than worthy of being the Seventh Wonder of the ancient world. @PThis monument's ultimate demise was brought about not by the hand of man but by a series of earthquakes that rocked the region.  Its topmost tier tumbled down during a severe quake in 303 AD.  However it was not until a massive trembler on August 8th, 1303, that most of the remaining structure came down, to be swallowed up by the surrounding waters.  Today a fort, built by the Mamluk sultan Qait Bey, can be seen on Pharos Island where the wondrous lighthouse once stood."
        }
    }
    message_building_alexandria_library {
        id: 488,
        
        size [30, 28]
        title {
            text: "Alexandria's Library",
        }
        content {
            text: "Scholars and other learned men and women from the entire known world flock to Alexandria's Great Library, mankind's greatest repository of knowledge. @PTo build Alexandria's Library you must first select a suitable site. Choose Alexandria's Library from the Religious structures: Monuments list. If the footprint you see is completely green, the location you have selected is acceptable.  @PTo build Alexandria's Library, you will need the services of peasants from @8Work&Camps, stonemasons from @363Stonemasons'&Guilds, and carpenters from @363Carpenters'&Guilds. The carpenters will need @94wood to construct scaffolding, which can be imported if you cannot harvest it in your city. You will also need to @47import white marble from a trade partner. To finish the monument, you will need a supply of @93copper, either from your city's own mines or from a trade partner.  @PRight-click on Alexandria's Library during its construction to get a progress report from the @369Construction&Foreman. @L@LClick @481here to find out more about the history of Alexandria's Library."
        }
    }
    message_building_pharos_lighthouse {
        id: 489,
        
        size [30, 28]
        title {
            text: "Pharos Lighthouse",
        }
        content {
            text: "Alexandria's spectacular Pharos lighthouse by day or night helps to guide mariners around the dangerous shoals of its harbor. @PThe Pharos Lighthouse can only be built on the rocky ground of Pharos Island in Alexandria's harbor. Select 'Pharos Lighthouse' from the Religious Structures: Monuments list, and then move the cursor over the rock-strewn ground near the outer harbor's entrance.  Once the monument's footprint is entirely green, you have found a suitable site that will support this structure's ponderous weight. @POnce the ground is clear you will need a supply of imported white marble.  This commodity can be obtained via a @47trade&route with another city.  @363Stonemasons from a Stonemasons' Guild will carefully place the white marble that peasants from a @8Work&Camp haul over from a @4Storage&Yard. The peasants will bring the white marble over once there are at least four blocks stored in a single Storage Yard. @363Carpenters from a Carpenters' Guild and a quantity of @94wood will also be required for building scaffolding once construction is underway. @PRight-click on the Pharos Lighthouse while it is being built to view a progress report from its @369Construction&Foreman. @L@LClick @487here to learn more about the Alexandria's Pharos Lighthouse."
        }
    }
    message_building_caesareum {
        id: 490,
        
        size [30, 28]
        title {
            text: "Caesareum",
        }
        content {
            text: "One of Alexandria's finest architectural masterpieces is the Caesareum, a sprawling seaside temple and visual landmark for sailors entering Alexandria's massive harbor. @PTo build the Caesareum, first select it from the Religious Structures: Monuments list on the Control Panel. After you select it, you will see a footprint of the building. Scout around for a suitably large section of clear land and place the monument. You'll know when you've picked an appropriate spot when the footprint is entirely green.  @POnce a suitable site has been determined, construction can commence.  Peasants from a @8Work&Camp will begin by clearing the land, exposing the bedrock below.  Once the land is ready, @363stonemasons from a Stonemasons' Guild will arrive to place the white marble that peasants will deliver from a @4Storage&Yard. White marble must be @47imported from a trade partner. Peasants will drag the white marble over to the construction site as soon as four blocks of it is stored in a single Storage Yard. @P@363Carpenters from a Carpenters' Guild supplied with @94wood will also be needed to build scaffolding. If your city does not have its own source of wood, you will need to import some. Near the end of the project, a supply of granite from a Storage Yard will also be needed, which can be imported if your city cannot @95quarry its own. @PRight-click on the Caesareum during its construction and its @369Construction&Foreman will present you with a progress report. @LClick @482here for more historical information about the Caesareum."
        }
    }
    message_crime_wave {
        id: 491,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Crime Wave",
        }
        content {
            text: "May the gods have mercy on us!  A band of greedy tomb robbers that thirst for ill-gotten riches has set themselves loose upon our fair city.  Stop them before they steal the magnificent burial provisions interred with our noble dead!"
        }
    }
    message_building_abu_simbel {
        id: 492,
        
        size [30, 28]
        title {
            text: "Abu Simbel",
        }
        content {
            text: "@PThe temple of Abu Simbel is a massive monument that Ramses II had hewn from the sandstone cliffs overlooking the upper Nile in Nubia. @PTo begin construction on Abu Simbel, first select it from the Religious Structures: Monuments list. A footpring of the monument will appear The bulk of the monument must be built into cliffs. The entranceway, which juts from the side of the monument, must be on clear land. You'll know you've selected a good spot when the entire footprint turns green. Click the mouse button to lock the monument into place. @PYou might find it helpful to temporarily flatten the cliff terrain while you are searching for a suitable spot to place the monument. Simply press 'H' or select 'Hide Cliffs' from the @18overlays list. You can restore the cliffs to their lofty heights by pressing 'H' again or selecting 'Normal' from the overlays list.  @POnce an appropriate site is designated, you will need an able workforce, headed by @363stonemasons from a Stonemasons' Guild to carve the rock and @363carpenters from a Carpenters' Guild to build the necessary scaffolding.  The carpenters will need @192wood for the scaffolding, which can be imported via a @47trade&route or harvested from the land by a @94Wood&Cutter. @PRight-click on the Abu Simbel monument for a progress report from its @369Construction&Foreman. @L@LClick @493here to learn more about Ramses II's most famous monument."
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
            text: "History",
        }
        content {
            text: "@PRamses the Great (Ramses II) ruled Egypt ca. 1279-1212 BC.  This long-lived pharaoh is renowned for the many temples and monuments built during his reign, the grandest of which was Abu Simbel.   @PAbout 350 miles south of Waset (Thebes), in the province of Nubia, Ramses' stonemasons carved a row of four seated statues of the pharaoh in the pink sandstone cliffs overlooking the Nile valley.  Each statue is over 66 feet tall - only the Great Sphinx at Giza is taller.  The seated figures flank a tunnel entrance that leads to an inner sanctum dug 160 feet into the cliff.  The temple faces east and was designed so that twice a year light from the rising sun penetrates to the rear wall of the sanctum, illuminating three smaller statues of Ramses, Amun and Ra.  A statue of Ptah is also located in the sanctum, but because he is associated with the underworld, his statue is positioned so that sunlight does not fall upon it.  Reliefs inside the temple also commemorate Ramses' military victories.  Nearby, a sister temple carved into the cliffs honors the goddess Hathor and Ramses' foremost wife, Queen Nefertari.  The whole complex was intended to awe the Nubian subjects and encourage tributes from them.   @PAbu Simbel was completed ca. 1256 BC.  Over the millenia sands buried it.  In 1817 archaeologist Giovanni Belzoni uncovered the massive monument.  Threatened to be covered again in the mid 1960s, this time by waters rising behind the newly constructed Aswan High Dam, Abu Simbel was cut out of the cliff and reconstructed with great precision on higher ground - an engineering feat that would surely have impressed the ancient Egyptians."
        }
    }
    message_tutorial_major_plagues {
        id: 494
        
        size [30, 28]
        title { text: "Major Plagues" }
        content { text: "There are many calamities that may befall a city, regardless of its size or wealth, and Major Plagues are some of the worst. Please note, though, that Major Plagues are not the same thing as @53plague. Plague strikes the city when city health is particularly bad. Major Plagues may strike for no reason at all.  @PAll of the Major Plagues result in lower @39city&sentiment. Their other dire consequences are described below: @L@LRiver of Blood @LWhen the River of Blood strikes the city, the river and waters of your city will turn to blood for several months and be unfit for @44drinking&water and other uses. Some of the water that houses store on site will also be contaminated and undrinkable, with those living closest to the river feeling the effects the most. People living near the water will also be at an even greater risk for disease and malaria (for more details on disease and malaria, see @53city&health). @84Fishing&Wharves, @59Water&Lifts, @94Reed&Gatherers, @62Wells and @61Water&Supplies will stop working during the plague. An unhappy @354Bast might unleash this plague upon your city, or the plague may occur for no discernable reason at all. @L@LFrogs @LWhen the Plague of Frogs is visited upon your city, legions of frogs invade your borders and infest any houses they pass. No one can live in a frog-infested house, so the residents are forced out, and no one can move back in for several months. You can try to contain the frogs by building walls around them or strategically positioning buildings to pen them in. @352Ptah can bring this curse down on your city if you displease him, or the frogs may strike of their own volition. @L@LHailstorm @LDeadly hailstones are the progeny of Hailstorms, which can kill anyone walking in your city. Hailstones are non-discriminatory and can kill soldiers (including enemies) and animals just as easily as they can kill ordinary citizens. Hailstorms also bring violent turbulence to the river, and many of your ships may sink. If you neglect @353Seth, he may bring this terror to your city. Hailstorms can also be natural weather phenomenon. @L@LLocusts @LLocusts descend upon the land and devour any crops your @45farms are growing. The crops on both the flood plain and meadowland will be completely destroyed just before the harvest, robbing your city of the harvest's benefit for the year. When you have piqued @350Osiris' anger, he may send this plague to your city. Sometimes, though, locusts will appear without provocation.   @L@LTo learn more about major plagues that afflicted the land of the pharaohs, click @495here." }
    }
    message_history_major_plagues {
        id: 495,
        
        size [30, 20]
        image {
            id: 1010,
            pos [15, 15]
        }
        title {
            text: "Major Plagues",
            pos [125, 15]
        }
        subtitle {
            text: "History",
        }
        content {
            text: "In the 13th century BC, during the reigns of Seti I and his son Ramses the Great (Ramses II), the Hebrews in Egypt were enslaved to work on construction projects.  According to the Book of Exodus in the Bible, the Lord God appeared to one of these children of Israel, the prophet Moses, and promised to help them escape to freedom.  Thus guided by the Lord, Moses appealed to the pharaoh to 'Let my people go,' on ten separate occasions, and Ramses denied the request each time. Each denial brought forth a different plague to afflict the pharaoh and the Egyptians while sparing the enslaved Hebrews.  First, the river turned to blood, killing the fish and making the water unfit to drink.  After Pharaoh's second denial, frogs came up from the ponds and rivers to infest the houses of the villages. The seventh plague was a thunderous hailstorm that smote men and beasts in the field and destroyed crops of barley and flax.  According to the Book of Exodus, Ramses' eighth denial to let the children of Israel leave Egypt brought forth a swarm of locusts, which darkened the land with their numbers and devoured all the green things that the hail of the previous plague had left. Ramses relented after the tenth plague killed all the first-born Egyptian children and beasts, though Ramses sent his army in pursuit of the fleeing Hebrews through the Sea of Reeds. @PThough these plagues are not recorded in contemporary Egyptian records, there are many instances of similar catastrophes occurring throughout history and prehistory.  Even as recently as the 20th century AD, hailstorms and locust swarms have plagued mankind."
        }
    }
    message_mummy_attacks {
        id: 496,
        type: 2,
        
        size [30, 20]
        urgent: 1
        title { text: "Mummy Attacks!" }
        content { text: "A mummy has risen and walks the streets of our city.  Stop this undead curse before it spreads throughout the land." }
    }
}
