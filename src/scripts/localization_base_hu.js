log_info("akhenaten: localization_hu config started")

localization_base_hu = [
    { group:1, id:1, text: "Új játék" }
    { group:1, id:3, text: "Játék betöltése" }
    { group:1, id:4, text: "Játék mentése" }
    { group:1, id:5, text: "Kilépés" }
    { group:1, id:6, text: "Mentés törlése" }
    { group:2, id:0, text: "Beállítások" }
    { group:2, id:1, text: "Képernyőbeállítások" }
    { group:2, id:2, text: "Hangbeállítások" }
    { group:2, id:3, text: "Játéksebesség" }
    { group:2, id:4, text: "Piramisépítés gyorsítása – Kikapcsolva" }
    { group:2, id:5, text: "Piramisépítés gyorsítása – Bekapcsolva" }
    { group:2, id:6, text: "Nehézségi szint" }
    { group:2, id:7, text: "Városnevek – egyiptomi" }
    { group:2, id:8, text: "Városnevek – klasszikus" }
    { group:2, id:9, text: "Automatikus mentés – Bekapcsolva" }
    { group:2, id:10, text: "Automatikus mentés – Kikapcsolva" }
    { group:2, id:11, text: "Felugró üzenetek" }
    { group:3, id:0, text: "Súgó" }
    { group:3, id:1, text: "Súgó" }
    { group:3, id:2, text: "Egérsúgó – Kikapcsolva" }
    { group:3, id:3, text: "Egérsúgó – Részleges" }
    { group:3, id:4, text: "Egérsúgó – Teljes" }
    { group:3, id:5, text: "Figyelmeztetések – Kikapcsolva" }
    { group:3, id:6, text: "Figyelmeztetések – Bekapcsolva" }
    { group:3, id:7, text: "Névjegy" }
    { group:3, id:8, text: "Küldetésszerkesztő útmutató" }
    { group:4, id:0, text: "Felügyelők" }
    { group:4, id:1, text: "Munkaügyi felügyelő" }
    { group:4, id:2, text: "Katonai felügyelő" }
    { group:4, id:3, text: "Politikai felügyelő" }
    { group:4, id:4, text: "Értékelési felügyelő" }
    { group:4, id:5, text: "Kereskedelmi felügyelő" }
    { group:4, id:6, text: "Magtárak felügyelője" }
    { group:4, id:7, text: "Közegészségügyi felügyelő" }
    { group:4, id:8, text: "Oktatási felügyelő" }
    { group:4, id:9, text: "Szórakoztatási felügyelő" }
    { group:4, id:10, text: "Templomok felügyelője" }
    { group:4, id:11, text: "Kincstári felügyelő" }
    { group:4, id:12, text: "Főfelügyelő" }
    { group:4, id:13, text: "Emlékművek felügyelője" }
    { group:5, id:1, text: "Elhagyod a Királyságot?" }
    { group:5, id:3, text: "Fizetsz ennek a szárazföldi kereskedelmi útvonalnak a megnyitásáért?" }
    { group:5, id:4, text: "Kereskedelmi útvonal megnyitása" }
    { group:5, id:5, text: "Fizetsz ennek a vízi kereskedelmi útvonalnak a megnyitásáért?" }
    { group:5, id:6, text: "Fáraói kérés" }
    { group:5, id:9, text: "Nincs elegendőd a kérés teljesítéséhez." }
    { group:5, id:11, text: "Nincs egyetlen kiküldhető egységed sem." }
    { group:5, id:13, text: "Mondd meg a katonai felügyelődnek, hogy rendeljen ki néhány hadműveleti egységet a Királyság szolgálatába." }
    { group:5, id:15, text: "Kiküldöd a segélycsapatot?" }
    { group:5, id:17, text: "Biztosan le akarod szerelni ezt az erődöt?" }
    { group:5, id:18, text: "Hiányzó CD" }
    { group:5, id:19, text: "Kérlek, helyezd vissza a Cleopatra CD-t a CD-ROM meghajtóba." }
    { group:5, id:21, text: "Óvatosan húzd fel a hidakat. Az elszigetelt közösségek hamarosan elpusztulnak, ha elvágod őket a Királyság útjaitól." }
    { group:5, id:24, text: "Régi verzió" }
    { group:5, id:25, text: "Ez a fájl egy régebbi verzió, ezért nem tölthető be." }
    { group:5, id:26, text: "Túl sok temetkezési kellék!" }
    { group:5, id:27, text: "Ebben a forgatókönyvben legfeljebb 5 temetkezési kelléked lehet!" }
    { group:5, id:28, text: "Figyelmeztetés!" }
    { group:5, id:29, text: "Ez a temetkezési kellék nem érhető el ebben a forgatókönyvben!" }
    { group:5, id:30, text: "Nincs elég áru!" }
    { group:5, id:31, text: "Nincs elegendő mennyiségben raktáron ebből az árutípusból!" }
    { group:5, id:32, text: "Elkészült!" }
    { group:5, id:33, text: "Ehhez az árucikkhez már nincs szükséged több temetkezési kellékre!" }
    { group:5, id:34, text: "Városok maximális száma" }
    { group:5, id:35, text: "Elérted a városok maximális számát." }
    { group:5, id:36, text: "Szállítóeszköz szükséges" }
    { group:5, id:37, text: "Ezeknek a csapatoknak szállítóhajóra kell szállniuk, hogy a jelenlegi konfliktusban a Királyság szolgálatára lehessenek." }
    { group:5, id:38, text: "Szárazföldi csapatok szükségesek" }
    { group:5, id:39, text: "A Királyság jelenlegi konfliktusában csak a szárazföldön utazó csapatokra van szükség." }
    { group:5, id:40, text: "Nincs szükség csapatokra" }
    { group:5, id:41, text: "Nincs szárazföldi vagy tengeri csapatokra vonatkozó kérés." }
    { group:5, id:42, text: "A Királyságban lévő csapatok" }
    { group:5, id:43, text: "Ezek a csapatok nincsenek a városban." }
    { group:5, id:44, text: "A Királyságban lévő hadihajó" }
    { group:5, id:45, text: "Ez a hadihajó nincs a városban." }
    { group:5, id:46, text: "Az ár nem módosítható!" }
    { group:5, id:47, text: "Ez az áru nem érhető el ebben a forgatókönyvben!" }
    { group:5, id:48, text: "Ez az épület nem működhet." }
    { group:5, id:49, text: "A város nem tud vásznat termelni vagy importálni." }
    { group:5, id:50, text: "Ez az épület nem működhet." }
    { group:5, id:51, text: "A város nem tud sört termelni vagy importálni." }
    { group:5, id:52, text: "Ez az épület nem működhet." }
    { group:5, id:53, text: "A város nem tud papiruszt termelni vagy importálni." }
    { group:5, id:54, text: "A halottasházak nem működhetnek." }
    { group:5, id:55, text: "A város nem tud vásznat termelni vagy importálni. A halottasházak eltávolításra kerültek." }
    { group:5, id:56, text: "A szenet-házak nem működhetnek." }
    { group:5, id:57, text: "A város nem tud sört termelni vagy importálni. A szenet-házak eltávolításra kerültek." }
    { group:5, id:58, text: "Az írnokiskolák nem működhetnek." }
    { group:5, id:59, text: "A város nem tud papiruszt termelni vagy importálni. Az írnokiskolák eltávolításra kerültek." }
    { group:5, id:60, text: "A könyvtárak nem működhetnek." }
    { group:5, id:61, text: "A város nem tud papiruszt termelni vagy importálni. A könyvtárak eltávolításra kerültek." }
    { group:5, id:62, text: "Ez az épület nem működhet." }
    { group:5, id:63, text: "A város nem tud rezet termelni vagy importálni." }
    { group:5, id:64, text: "A fegyverkovácsok nem működhetnek." }
    { group:5, id:65, text: "A város nem tud rezet termelni vagy importálni. A fegyverkovácsok eltávolításra kerültek." }
    { group:5, id:66, text: "Ez az épület nem működhet." }
    { group:5, id:67, text: "A város nem tud fát termelni vagy importálni." }
    { group:5, id:68, text: "A harci kocsikészítők nem működhetnek." }
    { group:5, id:69, text: "A város nem tud fát termelni vagy importálni. A harci kocsikészítők eltávolításra kerültek." }
    { group:5, id:70, text: "Ez az épület nem működhet." }
    { group:5, id:71, text: "Ebben a városban nincs toborzó." }
    { group:5, id:72, text: "Erőd: Gyalogság nem működhet." }
    { group:5, id:73, text: "Ebben a városban nincs toborzó. Az erőd gyalogsági egysége eltávolításra került." }
    { group:5, id:74, text: "Erőd: Íjászok nem működhetnek." }
    { group:5, id:75, text: "Ebben a városban nincs toborzó. Az erőd íjász egysége eltávolításra került." }
    { group:5, id:76, text: "Erőd: Harci kocsisok nem működhetnek." }
    { group:5, id:77, text: "Ebben a városban nincs toborzó. Az erőd harci kocsis egysége eltávolításra került." }
    { group:5, id:78, text: "Az akadémiák nem működhetnek." }
    { group:5, id:79, text: "Ebben a városban nincs toborzó. Az akadémiák eltávolításra kerültek." }
    { group:5, id:80, text: "Ez az épület nem működhet." }
    { group:5, id:81, text: "A város nem tud fegyvert termelni vagy importálni." }
    { group:5, id:82, text: "Ez az épület nem működhet." }
    { group:5, id:83, text: "A város nem tud harci kocsikat termelni vagy importálni." }
    { group:5, id:84, text: "Erőd: Gyalogság nem működhet." }
    { group:5, id:85, text: "Ebben a városban nincs fegyverkovács. Az erőd gyalogsági egysége eltávolításra került." }
    { group:5, id:86, text: "Erőd: Harci kocsisok nem működhetnek." }
    { group:5, id:87, text: "Ebben a városban nincs harci kocsikészítő. Az erőd harci kocsis egysége eltávolításra került." }
    { group:5, id:89, text: "Fesztiváltérre van szükséged fesztivál rendezéséhez." }
    { group:5, id:91, text: "Ez törli a kiválasztott dinasztiát és az összes hozzá tartozó mentett játékot. Biztosan ezt akarod tenni?" }
    { group:5, id:92, text: "A dinasztia már létezik" }
    { group:5, id:93, text: "Ezt a nevet már használják. Válassz másik nevet." }
    { group:5, id:95, text: "Ki kell választanod egy dinasztiát." }
    { group:5, id:96, text: "Figyelmeztetés" }
    { group:5, id:97, text: "Nincs elég debened egy fesztivál megrendezéséhez." }
    { group:5, id:98, text: "Fáraói kérés" }
    { group:5, id:99, text: "Nincs kiküldhető vízi egységed." }
    { group:5, id:100, text: "Fáraói kérés" }
    { group:5, id:101, text: "Mondd meg a katonai felügyelődnek, hogy rendeljen ki néhány hadműveleti vízi egységet a Királyság szolgálatába." }
    { group:5, id:102, text: "Erők kiküldése" }
    { group:5, id:103, text: "A kiválasztott erőid számára több lehetséges célállomás is van. Mondd meg a politikai felügyelődnek, hová küldje ezeket a csapatokat." }
    { group:5, id:104, text: "Emlékmű lerombolása" }
    { group:5, id:105, text: "Biztosan le akarod rombolni ezt az emlékművet?" }
    { group:5, id:106, text: "Templomkomplexum lerombolása" }
    { group:5, id:107, text: "Valóban le akarjuk rombolni ezt a templomkomplexumot?" }
    { group:5, id:108, text: "Nem menthető" }
    { group:5, id:109, text: "A vad- és ragadozóhelyek érvénytelen helyeken vannak." }
    { group:5, id:110, text: "A fájl létezik" }
    { group:5, id:111, text: "Felülírod a meglévő fájlt?" }
    { group:5, id:112, text: "Nincs eladó" }
    { group:5, id:113, text: "Jelenleg nincs olyan város, amely el szeretné adni ezt az árucikket." }
    { group:5, id:114, text: "Nincs vevő" }
    { group:5, id:115, text: "Jelenleg nincs olyan város, amely meg szeretné venni ezt az árucikket." }
    { group:5, id:116, text: "Nincs nyitott kereskedelmi útvonal" }
    { group:5, id:117, text: "Látogasd meg a világtérképet, hogy kereskedelmi útvonalat nyiss ennek az árucikknek az exportálásához." }
    { group:5, id:118, text: "Látogasd meg a világtérképet, hogy kereskedelmi útvonalat nyiss ennek az árucikknek az importálásához." }
    { group:5, id:119, text: "Figyelmeztetés" }
    { group:5, id:120, text: "Nincs elég debened egy kereskedelmi útvonal megnyitásához." }
    { group:5, id:121, text: "Nem menthető" }
    { group:5, id:122, text: "Túl sok élelmiszertípus (legfeljebb 4)." }
    { group:5, id:123, text: "A világtérkép nem szerkeszthető" }
    { group:5, id:124, text: "A világtérkép szerkesztéséhez legalább 800x600-as képernyőfelbontás szükséges." }
    { group:5, id:125, text: "Nem lehet elhagyni a világtérképet" }
    { group:5, id:126, text: "Túl sok élelmiszertípus (legfeljebb 4)." }
    { group:5, id:127, text: "Nem menthető" }
    { group:5, id:128, text: "Néhány halászhely érvénytelen helyen van." }
    { group:5, id:129, text: "Nem menthető" }
    { group:5, id:130, text: "A bejárati/kijárati pontok érvénytelen helyen vannak." }
    { group:5, id:131, text: "Nem menthető" }
    { group:5, id:132, text: "A folyó be- és kifolyási pontjai érvénytelen helyen vannak." }
    { group:5, id:133, text: "Nem menthető" }
    { group:5, id:134, text: "Néhány szárazföldi inváziós pont érvénytelen helyen van." }
    { group:5, id:135, text: "Nem menthető" }
    { group:5, id:136, text: "Néhány vízi inváziós pont érvénytelen helyen van." }
    { group:5, id:137, text: "Fáraó" }
    { group:5, id:138, text: "Kérlek, helyezd be a Cleopatra CD-t." }
    { group:5, id:139, text: "Az állatkert nem működhet." }
    { group:5, id:140, text: "A város nem tud sem vadhúst, sem szalmát termelni vagy importálni. Az állatkert eltávolításra került." }
    { group:5, id:141, text: "A család még nem nyert küldetést" }
    { group:5, id:142, text: "Ha új vagy a Fáraóban, válaszd a „Családtörténet kezdése” lehetőséget. Folytatod a küldetés kiválasztását?" }
    { group:6, id:0, text: "Db" }
    { group:6, id:1, text: "Lakosság" }
    { group:6, id:2, text: "A küldetésből hátralévő hónapok" }
    { group:6, id:3, text: "Hónapok a győzelemig" }
    { group:6, id:4, text: "Nézetek" }
    { group:6, id:5, text: "Ezt a küldetést már teljesítetted, de a város irányítását tovább folytattad." }
    { group:6, id:6, text: "A síremlékeket sziklák mellé építsd úgy, hogy a bejáratuk a sík terepre nyíljon." }
    { group:7, id:0, text: "Fájl" }
    { group:7, id:1, text: "Új térkép" }
    { group:7, id:2, text: "Térkép betöltése" }
    { group:7, id:3, text: "Térkép mentése" }
    { group:7, id:4, text: "Kilépés a szerkesztőből" }
    { group:8, id:0, text: "Deben" }
    { group:8, id:1, text: "Deben" }
    { group:8, id:2, text: "Személy" }
    { group:8, id:3, text: "Személyek" }
    { group:8, id:4, text: "Hónap" }
    { group:8, id:5, text: "Hónapok" }
    { group:8, id:6, text: "Magtár" }
    { group:8, id:7, text: "Magtárak" }
    { group:8, id:8, text: "Év" }
    { group:8, id:9, text: "Évek" }
    { group:8, id:10, text: "Egység" }
    { group:8, id:11, text: "Egységek" }
    { group:8, id:12, text: "Alkalmazott" }
    { group:8, id:13, text: "Alkalmazottak" }
    { group:8, id:14, text: "további személy" }
    { group:8, id:15, text: "további személy" }
    { group:8, id:16, text: "egység." }
    { group:8, id:18, text: "Írnokiskola" }
    { group:8, id:19, text: "Írnokiskolák" }
    { group:8, id:20, text: "Akadémia" }
    { group:8, id:21, text: "Akadémiák" }
    { group:8, id:22, text: "Könyvtár" }
    { group:8, id:23, text: "Könyvtárak" }
    { group:8, id:24, text: "Orvos" }
    { group:8, id:25, text: "Orvosok" }
    { group:8, id:26, text: "Fogorvos" }
    { group:8, id:27, text: "Fogorvosok" }
    { group:8, id:28, text: "Patika" }
    { group:8, id:29, text: "Patikák" }
    { group:8, id:30, text: "Balzsamozóműhely" }
    { group:8, id:31, text: "Balzsamozóműhelyek" }
    { group:8, id:32, text: "Jósda" }
    { group:8, id:33, text: "Jósdák" }
    { group:8, id:34, text: "Pavilon" }
    { group:8, id:35, text: "Pavilonok" }
    { group:8, id:36, text: "Zenepavilon" }
    { group:8, id:37, text: "Zenepavilonok" }
    { group:8, id:38, text: "Színpad" }
    { group:8, id:39, text: "Színpadok" }
    { group:8, id:40, text: "Szenet-játék" }
    { group:8, id:41, text: "Szenet-játékok" }
    { group:8, id:42, text: "Üzenet" }
    { group:8, id:43, text: "Üzenetek" }
    { group:8, id:44, text: "Nap" }
    { group:8, id:45, text: "Napok" }
    { group:8, id:46, text: "Katona" }
    { group:8, id:47, text: "Katonák" }
    { group:8, id:48, text: "Század" }
    { group:8, id:49, text: "Századok" }
    { group:8, id:50, text: "Hadihajó" }
    { group:8, id:51, text: "Hadihajók" }
    { group:8, id:52, text: "Balzsamozóműhely" }
    { group:8, id:53, text: "Balzsamozóműhelyek" }
    { group:8, id:54, text: "rakomány" }
    { group:8, id:55, text: "rakományok" }
    { group:8, id:56, text: "Kőtömb" }
    { group:8, id:57, text: "Kőtömbök" }
    { group:8, id:58, text: "szállítmány" }
    { group:8, id:59, text: "szállítmányok" }
    { group:9, id:0, text: "Pharaoh (Kleopátra kiegészítő)" }
    { group:9, id:1, text: "2.1-es verzió" }
    { group:9, id:2, text: "Copyright © 1999–2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Béta kiadás: BreakAway Games tesztelő" }
    { group:9, id:4, text: "teszt1 szöveg" }
    { group:9, id:5, text: "Ide írja a nevét" }
    { group:9, id:6, text: "Egyiptomi városom" }
    { group:9, id:7, text: "1. küldetés" }
    { group:9, id:8, text: "Pharaoh küldetésszerkesztő" }
    { group:9, id:9, text: "Pharaoh demó" }
    { group:10, id:0, text: "Visszaállítások" }
    { group:10, id:1, text: "Gyilkospontok törlése" }
    { group:10, id:2, text: "Halak törlése" }
    { group:10, id:3, text: "Inváziók törlése" }
    { group:10, id:4, text: "Partraszállási pontok törlése" }
    { group:10, id:5, text: "Vadászpontok törlése" }
    { group:10, id:6, text: "Betöltés BMP-ből" }
    { group:10, id:7, text: "Mentés BMP-be" }
    { group:10, id:8, text: "Királyság szerkesztése" }
    { group:10, id:9, text: "Királyság mentése" }
    { group:10, id:10, text: "Térkép frissítése" }
    { group:11, id:0, text: "Előkészítés..." }
    { group:11, id:1, text: "teszt_szöveg €,Њ,њ,Ў,°,ї,A,А,Б,В,Д,E,И,Й,К,I,М,Н,О,П,N,С,O,Т,У,Ф,Ц,U,Щ,Ъ,Ы,Ь,Я,a,а,б,в,д,c,з,e,и,й,к,i,м,н,о,п,n,с,o,т,у,ф,ц,u,щ,ъ,ы,ь,..." }
    { group:11, id:2, text: "Betöltés..." }
    { group:11, id:3, text: "Adatok előkészítése..." }
    { group:11, id:4, text: "Hangok betöltése..." }
    { group:11, id:5, text: "Gyorsított idő" }
    { group:11, id:6, text: "Kattintson a jobb egérgombbal a folytatáshoz" }
    { group:11, id:7, text: "Hátterek betöltése..." }
    { group:11, id:8, text: "Animációk betöltése..." }
    { group:11, id:9, text: "Emlékművek betöltése..." }
    { group:11, id:10, text: "Ellenségek betöltése..." }
    { group:11, id:11, text: "Beállítások betöltése..." }
    { group:12, id:0, text: "Vissza" }
    { group:12, id:2, text: "engedelmeskedni" }
    { group:12, id:3, text: "Kevés az élelmiszerkészlet" }
    { group:12, id:4, text: "Magas a munkanélküliség" }
    { group:12, id:5, text: "Túl magasak az adók" }
    { group:12, id:6, text: "Alacsonyak a bérek" }
    { group:12, id:7, text: "Az alacsony szintű lakóházak jobb életkörülményeket igényelnek" }
    { group:13, id:0, text: "Kattintson a folytatáshoz" }
    { group:13, id:1, text: "Kattintson a jobb egérgombbal a folytatáshoz" }
    { group:13, id:2, text: "A játék szünetel ('P' a folytatáshoz)" }
    { group:13, id:3, text: "Kattintson a jobb egérgombbal a folytatáshoz" }
    { group:13, id:4, text: "Mégse" }
    { group:13, id:5, text: "Folytatás" }
    { group:13, id:6, text: "A demóban nem érhető el!" }
    { group:13, id:7, text: "Kattintson a kezdéshez" }
    { group:13, id:8, text: "Válasszon egy egyiptomi nevet:" }
    { group:14, id:8, text: "Tűz" }
    { group:14, id:9, text: "Károk" }
    { group:14, id:10, text: "Bűnözés" }
    { group:14, id:11, text: "Összesen" }
    { group:14, id:12, text: "Zsonglőr" }
    { group:14, id:13, text: "Zenész" }
    { group:14, id:14, text: "Táncos" }
    { group:14, id:15, text: "Szenet-játékosok" }
    { group:14, id:16, text: "Állatgondozók" }
    { group:14, id:17, text: "Összesen" }
    { group:14, id:18, text: "Írnokiskolák" }
    { group:14, id:19, text: "Könyvtár" }
    { group:14, id:20, text: "Vízátkelők" }
    { group:14, id:21, text: "Fogorvos" }
    { group:14, id:22, text: "Orvos" }
    { group:14, id:23, text: "Patika" }
    { group:14, id:24, text: "Balzsamozóműhely" }
    { group:14, id:25, text: "Adóbevétel" }
    { group:14, id:26, text: "Bazár elérhetősége" }
    { group:14, id:27, text: "Vonzóság" }
    { group:14, id:28, text: "Termékenység" }
    { group:14, id:29, text: "Munkaerő" }
    { group:14, id:30, text: "Őshonos" }
    { group:14, id:31, text: "Problémák" }
    { group:14, id:32, text: "Problémák" }
    { group:14, id:33, text: "Gabona" }
    { group:14, id:34, text: "Csicseriborsó" }
    { group:14, id:35, text: "Gránátalma" }
    { group:14, id:36, text: "Füge" }
    { group:14, id:37, text: "Hús" }
    { group:14, id:38, text: "Vad" }
    { group:14, id:39, text: "Agyagedény" }
    { group:14, id:40, text: "Ékszer" }
    { group:14, id:41, text: "Vászon" }
    { group:14, id:42, text: "Sör" }
    { group:14, id:43, text: "Járvány" }
    { group:14, id:44, text: "Fertőzött házak" }
    { group:14, id:45, text: "Víz" }
    { group:14, id:46, text: "Üres házak" }
    { group:14, id:47, text: "Öntözés" }
    { group:14, id:48, text: "Malária" }
    { group:14, id:49, text: "Városvédelem" }
    { group:14, id:50, text: "Magisztrátus" }
    { group:14, id:51, text: "Sziklafalak elrejtése" }
    { group:15, id:0, text: "Áruk fogadása" }
    { group:15, id:1, text: "Áruk elutasítása" }
    { group:15, id:2, text: "Áru beszerzése" }
    { group:16, id:0, text: "Épület" }
    { group:16, id:1, text: "Szövet" }
    { group:16, id:2, text: "Vezérlés" }
    { group:16, id:3, text: "Grafika" }
    { group:16, id:4, text: "Szerkezet" }
    { group:16, id:5, text: "Hálózat" }
    { group:16, id:6, text: "Véletlen" }
    { group:16, id:7, text: "Alak" }
    { group:16, id:8, text: "Animáció" }
    { group:16, id:9, text: "Ragadós" }
    { group:16, id:10, text: "RM_build" }
    { group:16, id:11, text: "Épület - vízellátás" }
    { group:16, id:12, text: "Épület - elérés" }
    { group:16, id:13, text: "Épület - fővárostól" }
    { group:16, id:14, text: "Épület - sérülés" }
    { group:16, id:15, text: "Épület - lakosság" }
    { group:16, id:16, text: "Vonzóság" }
    { group:16, id:17, text: "Magasság" }
    { group:16, id:18, text: "Folyó ragadás" }
    { group:16, id:19, text: "Barbár ragadás" }
    { group:16, id:20, text: "Sérülés" }
    { group:16, id:21, text: "Fügék száma" }
    { group:16, id:22, text: "Régi típus" }
    { group:16, id:23, text: "Befolyás" }
    { group:16, id:24, text: "Fal ragadás" }
    { group:16, id:25, text: "Úthálózat" }
    { group:16, id:26, text: "Kerület" }
    { group:17, id:0, text: "Észak" }
    { group:17, id:1, text: "Északkelet" }
    { group:17, id:2, text: "Kelet" }
    { group:17, id:3, text: "Délkelet" }
    { group:17, id:4, text: "Dél" }
    { group:17, id:5, text: "Délnyugat" }
    { group:17, id:6, text: "Nyugat" }
    { group:17, id:7, text: "Északnyugat" }
    { group:18, id:0, text: "Nem" }
    { group:18, id:1, text: "Igen" }
    { group:18, id:2, text: "Mégse" }
    { group:18, id:3, text: "OK" }
    { group:18, id:4, text: "BE" }
    { group:18, id:5, text: "KI" }
    { group:18, id:6, text: "N/A" }
    { group:18, id:7, text: "Mondjon többet" }
    { group:18, id:8, text: "és" }
    { group:18, id:9, text: "Újra" }
    { group:18, id:10, text: "Megszakítás" }
    { group:18, id:11, text: "Kihagyás" }
    { group:19, id:0, text: "Csak megtisztított területre építhető." }
    { group:19, id:1, text: "Elfogyott a pénz!" }
    { group:19, id:2, text: "Ebből az épületből csak egy lehet." }
    { group:19, id:3, text: "Házfejlődés: KI" }
    { group:19, id:4, text: "Házfejlődés: BE" }
    { group:19, id:5, text: "Útfejlődés: KI" }
    { group:19, id:6, text: "Útfejlődés: BE" }
    { group:19, id:7, text: "Lakosok megjelenítése: KI" }
    { group:19, id:8, text: "Lakosok megjelenítése: BE" }
    { group:19, id:9, text: "Ennek az épületnek útkapcsolatra van szüksége." }
    { group:19, id:10, text: "Ez az épület nem víz mellett áll!" }
    { group:19, id:11, text: "Ebben a küldetésben nem érhető el!" }
    { group:19, id:12, text: "Még nem érhető el!" }
    { group:19, id:13, text: "nincs használatban - alabástrom1" }
    { group:19, id:14, text: "nincs használatban - alabástrom2" }
    { group:19, id:15, text: "A városnak több munkásra van szüksége." }
    { group:19, id:16, text: "A lakosság több élelmet fogyaszt, mint amennyit megtermel." }
    { group:19, id:17, text: "Építs bazárokat az itt tárolt élelem kiosztásához." }
    { group:19, id:18, text: "Gazdaságokat a rétekre építs (keresd a sárgás füvet)." }
    { group:19, id:19, text: "Az agyagbányát víz közelébe építsd." }
    { group:19, id:20, text: "Köves terület mellé építsd." }
    { group:19, id:21, text: "A favágótelepet fák mellé építsd." }
    { group:19, id:22, text: "Köves terület mellé építsd." }
    { group:19, id:23, text: "Kutass a folyó mentén megfelelő hely után." }
    { group:19, id:24, text: "Ennek az épületnek rézércre van szüksége." }
    { group:19, id:25, text: "Ennek az épületnek árpára van szüksége." }
    { group:19, id:26, text: "Ennek az épületnek lenre van szüksége." }
    { group:19, id:27, text: "Ennek az épületnek agyagra van szüksége." }
    { group:19, id:28, text: "Ennek az épületnek drágakövekre van szüksége." }
    { group:19, id:29, text: "Nyiss kereskedelmi útvonalat az importálásához." }
    { group:19, id:30, text: "Utasítsd a kereskedelmi felügyelőt az importálására." }
    { group:19, id:31, text: "Építs rézbányát." }
    { group:19, id:32, text: "Építs árpagazdaságot." }
    { group:19, id:33, text: "Építs lenfarmot." }
    { group:19, id:34, text: "Építs agyagbányát." }
    { group:19, id:35, text: "Építs drágakőbányát." }
    { group:19, id:36, text: "Működéséhez feltöltött vízemelő szükséges." }
    { group:19, id:37, text: "Feltöltéséhez víz mellé kell építeni." }
    { group:19, id:38, text: "Öntözőárkokkal kösd össze egy vízemelővel." }
    { group:19, id:39, text: "Járőr küldéséhez városfal mellé kell építeni." }
    { group:19, id:40, text: "Működő toborzó szükséges katonák besorozásához." }
    { group:19, id:41, text: "Néhány katonának fegyverellátásra is szüksége lesz." }
    { group:19, id:42, text: "Építs zsonglőriskolát az előadók kiküldéséhez." }
    { group:19, id:43, text: "Építs konzervatóriumot, hogy zenészek érkezzenek ide." }
    { group:19, id:44, text: "Építs tánciskolát." }
    { group:19, id:45, text: "Építs Szenet-házat játékok rendezéséhez." }
    { group:19, id:46, text: "nincs használatban - demo1" }
    { group:19, id:47, text: "Tornyot csak vastag városfalra építhetsz." }
    { group:19, id:48, text: "Túl közel vannak az ellenséges csapatok!" }
    { group:19, id:49, text: "Az egység morálja túl alacsony az engedelmeskedéshez!" }
    { group:19, id:50, text: "A hadsereg már elérte az erődök maximális számát." }
    { group:19, id:51, text: "Havi automatikus mentés: BE" }
    { group:19, id:52, text: "Havi automatikus mentés: KI" }
    { group:19, id:53, text: "Nem bontható le a híd, amíg emberek vannak rajta." }
    { group:19, id:54, text: "Ez a belső tó nem kapcsolódik a tengerhez." }
    { group:19, id:55, text: "Nem lehet ablakos módra váltani." }
    { group:19, id:56, text: "Építs nádgyűjtőt mocsaras terület mellé." }
    { group:19, id:57, text: "A hajóácsoknak fára van szükségük hadihajók építéséhez." }
    { group:19, id:58, text: "A palota szükséges az arany debenné váltásához." }
    { group:19, id:59, text: "Nem építhetsz állatok szaporodási területére." }
    { group:19, id:60, text: "Néhány telek túl messze van az úttól." }
    { group:19, id:61, text: "A város egy része elszakadt a Királyi Úttól." }
    { group:19, id:62, text: "Amíg nem állítod helyre a kapcsolatot, ez a városrész nem fejlődik." }
    { group:19, id:63, text: "Adatkorlát elérve - lásd a README fájlt." }
    { group:19, id:64, text: "Útzárat csak útra lehet építeni." }
    { group:19, id:65, text: "Helyezd el a másik kompkikötőt is." }
    { group:19, id:66, text: "Nincs megfelelő hely ennek a kompkikötőnek." }
    { group:19, id:67, text: "A Királyság már elérte a négyféle élelmiszer maximumát." }
    { group:19, id:68, text: "Húst csak akkor adhatsz hozzá, ha szalmát tudsz termelni vagy importálni." }
    { group:19, id:69, text: "A város nem képes húst előállítani. Eltávolítva." }
    { group:19, id:70, text: "A Királyságban egyszerre csak egy különleges kőzetfajta lehet." }
    { group:19, id:71, text: "Először templomkomplexumot kell építened." }
    { group:19, id:72, text: "Egy templomkomplexumnak csak egy jósdája és egy oltára lehet." }
    { group:19, id:73, text: "A jósdát és az oltárt templomkomplexumra kell építeni." }
    { group:19, id:74, text: "Ennek az épületnek talajvízre van szüksége. Füves területre építsd." }
    { group:19, id:75, text: "Ezt a szórakoztató épületet útkereszteződésre kell építeni." }
    { group:19, id:76, text: "Először fel kell építened egy templomot!" }
    { group:19, id:77, text: "Könyvtár építéséhez 500 papirusz szükséges." }
    { group:19, id:78, text: "Ennek az épületnek nád szükséges." }
    { group:19, id:79, text: "Építs nádgyűjtőt." }
    { group:19, id:80, text: "Ennek az épületnek szalma szükséges." }
    { group:19, id:81, text: "Építs gabonafarmot." }
    { group:19, id:82, text: "A város már elérte a hadikikötők maximális számát." }
    { group:19, id:83, text: "Kis obeliszk építéséhez 100 gránittömb szükséges." }
    { group:19, id:84, text: "Nagy obeliszk építéséhez 200 gránittömb szükséges." }
    { group:19, id:85, text: "Néhány kiválasztott emlékmű már nem építhető. Eltávolítva." }
    { group:19, id:86, text: "Egyszerre csak egy obeliszk épülhet." }
    { group:19, id:87, text: "A város palota nélkül nem tud adót beszedni." }
    { group:19, id:88, text: "Naptemplom építéséhez 220 homokkőtömb szükséges." }
    { group:19, id:89, text: "Egyszerre csak egy naptemplom épülhet." }
    { group:19, id:90, text: "Már most is túl kevés munka jut a lakosságnak." }
    { group:19, id:91, text: "Alacsony az élelmiszerkészletünk." }
    { group:19, id:92, text: "A lakosság már most is több élelmet fogyaszt, mint amennyit termel." }
    { group:19, id:93, text: "A város egészségügyi helyzete katasztrofális. A járvány kitörése küszöbön áll." }
    { group:19, id:94, text: "A város egészségügyi helyzete borzalmas, a járvány nagyon valószínű." }
    { group:19, id:95, text: "Romlik a közegészségügy, komoly a járványveszély." }
    { group:19, id:96, text: "Romlik a közegészségügy, bármikor kitörhet a járvány." }
    { group:19, id:97, text: "A járványveszély még fennáll, de javul az egészségügyi helyzet." }
    { group:19, id:98, text: "Még mindig van némi járványveszély, de javul az egészségügyi helyzet." }
    { group:19, id:99, text: "Javul az egészségügyi helyzet, de még kitörhet a járvány." }
    { group:19, id:100, text: "Kirabolták a palotát!" }
    { group:19, id:101, text: "Egy tolvaj ellopta családi megtakarításának egy részét a Villájából!" }
    { group:19, id:102, text: "Nincsenek csapataink a közelgő támadás kivédésére." }
    { group:19, id:103, text: "Az egész város gyűlöli önt." }
    { group:19, id:104, text: "Az emberek nagyon haragszanak önre." }
    { group:19, id:105, text: "Az emberek haragszanak önre." }
    { group:19, id:106, text: "Az emberek nagyon elégedetlenek önnel." }
    { group:19, id:107, text: "Az emberek elégedetlenek önnel." }
    { group:19, id:108, text: "Az emberek bosszúsak önre." }
    { group:19, id:109, text: "Az emberek közömbösek önnel szemben." }
    { group:19, id:110, text: "Az emberek elégedettek önnel." }
    { group:19, id:111, text: "Az emberek nagyon elégedettek önnel." }
    { group:19, id:112, text: "Az emberek rendkívül elégedettek önnel." }
    { group:19, id:113, text: "Az emberek szeretik önt." }
    { group:19, id:114, text: "Az emberek istenként tisztelik önt." }
    { group:19, id:115, text: "mert nincs elegendő élelem." }
    { group:19, id:116, text: "mert nincs elegendő munkahely." }
    { group:19, id:117, text: "mert túl magasak az adók." }
    { group:19, id:118, text: "mert alacsonyak a bérek." }
    { group:19, id:119, text: "mert túl sok a nyomornegyed." }
    { group:19, id:120, text: "Új lakosok érkeznek a városba." }
    { group:19, id:121, text: "A lakáshiány megakadályozza a bevándorlást." }
    { group:19, id:122, text: "Az alacsony bérek elriasztják a bevándorlókat." }
    { group:19, id:123, text: "A munkahelyek hiánya elriasztja a bevándorlókat." }
    { group:19, id:124, text: "Az élelmiszerhiány elriasztja a bevándorlókat." }
    { group:19, id:125, text: "A magas adók visszatartják a bevándorlást." }
    { group:19, id:126, text: "A nyomornegyedek miatt nem érkeznek új lakosok." }
    { group:19, id:127, text: "A város közhangulata túl rossz a bevándorláshoz." }
    { group:19, id:128, text: "A lakáshiány miatt az emberek elhagyják a várost." }
    { group:19, id:129, text: "Az alacsony bérek miatt az emberek elköltöznek." }
    { group:19, id:130, text: "A magas munkanélküliség elűzi az embereket." }
    { group:19, id:131, text: "Az élelmiszerhiány miatt az éhezők elhagyják a várost." }
    { group:19, id:132, text: "Az emberek inkább elköltöznek, mint hogy magas adót fizessenek." }
    { group:19, id:133, text: "A város nyomornegyedei elűzik az embereket." }
    { group:19, id:134, text: "A város közhangulata annyira rossz, hogy az emberek elköltöznek." }
    { group:19, id:135, text: "Ennek az épületnek sörre van szüksége a működéshez." }
    { group:19, id:136, text: "Építsen Sörfőzdét." }
    { group:19, id:137, text: "Ennek az épületnek papiruszra van szüksége a működéshez." }
    { group:19, id:138, text: "Építsen Papiruszkészítőt." }
    { group:19, id:139, text: "Ennek az épületnek lenvászonra van szüksége a működéshez." }
    { group:19, id:140, text: "Építsen Szövőműhelyt." }
    { group:19, id:141, text: "Ennek az épületnek fára van szüksége a működéshez." }
    { group:19, id:142, text: "Építsen Favágótelepet." }
    { group:19, id:143, text: "Ennek az épületnek agyagra és szalmára van szüksége." }
    { group:19, id:144, text: "Nyisson kereskedelmi útvonalat agyag importálására." }
    { group:19, id:145, text: "Utasítsa a Kereskedelmi Felügyelőt agyag importálására." }
    { group:19, id:146, text: "Nyisson kereskedelmi útvonalat szalma importálására." }
    { group:19, id:147, text: "Utasítsa a Kereskedelmi Felügyelőt szalma importálására." }
    { group:19, id:148, text: "Ehhez az emlékműhöz közönséges kő és mészkő szükséges." }
    { group:19, id:149, text: "Építsen Kőbányát." }
    { group:19, id:150, text: "Nyisson kereskedelmi útvonalat közönséges kő importálására." }
    { group:19, id:151, text: "Utasítsa a Kereskedelmi Felügyelőt közönséges kő importálására." }
    { group:19, id:152, text: "Építsen Mészkőbányát." }
    { group:19, id:153, text: "Nyisson kereskedelmi útvonalat mészkő importálására." }
    { group:19, id:154, text: "Utasítsa a Kereskedelmi Felügyelőt mészkő importálására." }
    { group:19, id:155, text: "Ehhez az emlékműhöz közönséges kő szükséges." }
    { group:19, id:156, text: "Ehhez az emlékműhöz mészkő szükséges." }
    { group:19, id:157, text: "Ehhez az emlékműhöz tégla és mészkő szükséges." }
    { group:19, id:158, text: "Építsen Téglagyárat." }
    { group:19, id:159, text: "Nyisson kereskedelmi útvonalat tégla importálására." }
    { group:19, id:160, text: "Utasítsa a Kereskedelmi Felügyelőt tégla importálására." }
    { group:19, id:161, text: "Ehhez az emlékműhöz tégla szükséges." }
    { group:19, id:162, text: "Ehhez az emlékműhöz homokkő szükséges." }
    { group:19, id:163, text: "Építsen Homokkőbányát." }
    { group:19, id:164, text: "Utasítsa a Kereskedelmi Felügyelőt sör importálására." }
    { group:19, id:165, text: "Nyisson kereskedelmi útvonalat sör importálására." }
    { group:19, id:166, text: "Utasítsa a Kereskedelmi Felügyelőt árpa importálására." }
    { group:19, id:167, text: "Nyisson kereskedelmi útvonalat árpa importálására." }
    { group:19, id:168, text: "Utasítsa a Kereskedelmi Felügyelőt nád importálására." }
    { group:19, id:169, text: "Nyisson kereskedelmi útvonalat nád importálására." }
    { group:19, id:170, text: "Utasítsa a Kereskedelmi Felügyelőt papirusz importálására." }
    { group:19, id:171, text: "Nyisson kereskedelmi útvonalat papirusz importálására." }
    { group:19, id:172, text: "Utasítsa a Kereskedelmi Felügyelőt len importálására." }
    { group:19, id:173, text: "Nyisson kereskedelmi útvonalat len importálására." }
    { group:19, id:174, text: "Utasítsa a Kereskedelmi Felügyelőt lenvászon importálására." }
    { group:19, id:175, text: "Nyisson kereskedelmi útvonalat lenvászon importálására." }
    { group:19, id:176, text: "A Balzsamozók nem működhetnek, ezért el lettek távolítva. A város nem tud lenvásznat előállítani vagy importálni." }
    { group:19, id:177, text: "A Szenetház nem működhet, ezért el lett távolítva. A város nem tud sört előállítani vagy importálni." }
    { group:19, id:178, text: "Az Írnokképzők nem működhetnek, ezért el lettek távolítva. A város nem tud papiruszt előállítani vagy importálni." }
    { group:19, id:179, text: "A Könyvtárak nem működhetnek, ezért el lettek távolítva. A város nem tud papiruszt előállítani vagy importálni." }
    { group:19, id:180, text: "A Fegyverkovácsok nem működhetnek, ezért el lettek távolítva. A város nem tud rezet előállítani vagy importálni." }
    { group:19, id:181, text: "A Harcikocsikészítő nem működhet, ezért el lett távolítva. A város nem tud fát előállítani vagy importálni." }
    { group:19, id:182, text: "A Gyalogsági Erőd nem működhet, ezért el lett távolítva. A városban nincs Toborzó." }
    { group:19, id:183, text: "Az Íjász Erőd nem működhet, ezért el lett távolítva. A városban nincs Toborzó." }
    { group:19, id:184, text: "A Harcikocsis Erőd nem működhet, ezért el lett távolítva. A városban nincs Toborzó." }
    { group:19, id:185, text: "Az Akadémiák nem működhetnek, ezért el lettek távolítva. A város nem tud fát előállítani vagy importálni." }
    { group:19, id:186, text: "A Gyalogsági Erőd nem működhet, ezért el lett távolítva. A város nem tud fegyvereket előállítani vagy importálni." }
    { group:19, id:187, text: "A Harcikocsis Erőd nem működhet, ezért el lett távolítva. A város nem tud harci kocsikat előállítani vagy importálni." }
    { group:19, id:188, text: "Egy mauzóleum építéséhez 240 homokkőtömb szükséges." }
    { group:19, id:189, text: "Építsen Sörfőzdét, vagy rendelje el a sör importálását." }
    { group:19, id:190, text: "Építsen Sörfőzdét, vagy nyisson kereskedelmi útvonalat sör importálására." }
    { group:19, id:191, text: "Építsen Papiruszkészítőt, vagy rendelje el az importját." }
    { group:19, id:192, text: "Építsen Papiruszkészítőt, vagy nyisson kereskedelmi útvonalat papirusz importálására." }
    { group:19, id:193, text: "Építsen Szövőműhelyt, vagy rendelje el a lenvászon importálását." }
    { group:19, id:194, text: "Építsen Szövőműhelyt, vagy nyisson kereskedelmi útvonalat lenvászon importálására." }
    { group:19, id:195, text: "Tolvajok kifosztották egy Adószedő hivatalát!" }
    { group:19, id:196, text: "Tolvajok kifosztották a Bíróságot!" }
    { group:19, id:197, text: "Villája megsemmisült és kifosztották!" }
    { group:19, id:198, text: "A Palota megsemmisült és kifosztották!" }
    { group:19, id:199, text: "Egy Adószedő hivatala megsemmisült és kifosztották!" }
    { group:19, id:200, text: "A Bíróság megsemmisült és kifosztották!" }
    { group:19, id:201, text: "Egy aranybányászt megtámadtak és kiraboltak!" }
    { group:19, id:202, text: "Építs Magtárat a közelgő aratás tárolására." }
    { group:19, id:203, text: "Építs Magtárakat a közelgő aratás tárolására." }
    { group:19, id:204, text: "Egyszerre legfeljebb 10 Kikötő működhet." }
    { group:19, id:205, text: "A Szentélynek legfeljebb két mezőre kell lennie az úttól, hogy kifejthesse hatását." }
    { group:19, id:206, text: "Építs Zsonglőriskolát, hogy legyenek fellépők ehhez a szórakozóhelyhez." }
    { group:19, id:207, text: "Építs Konzervatóriumot, hogy legyenek zenészek ehhez a szórakozóhelyhez." }
    { group:19, id:208, text: "Építs Tánciskolát, hogy legyenek táncosok ehhez a szórakozóhelyhez." }
    { group:19, id:209, text: "Ez az alakulat nem tudja elérni a célját." }
    { group:19, id:210, text: "Játék elmentve." }
    { group:19, id:211, text: "Csak akadálymentes területre építhető." }
    { group:19, id:212, text: "Az emlékmű feljárójának vízhez kell vezetnie." }
    { group:19, id:213, text: "A Fesztiválteret útkereszteződés fölé kell építeni." }
    { group:19, id:214, text: "Amíg ellenség szennyezi földünket, senki sem költözik a városba." }
    { group:19, id:215, text: "Csalások engedélyezve." }
    { group:19, id:216, text: "Csalások letiltva." }
    { group:19, id:217, text: "Tökéletes lesz az áradás." }
    { group:19, id:218, text: "Kiváló lesz az áradás." }
    { group:19, id:219, text: "Jó lesz az áradás." }
    { group:19, id:220, text: "Közepes lesz az áradás." }
    { group:19, id:221, text: "Gyenge lesz az áradás." }
    { group:19, id:222, text: "Elmarad az áradás." }
    { group:19, id:223, text: "Áremelkedés." }
    { group:19, id:224, text: "Árcsökkenés." }
    { group:19, id:225, text: "Csökkentek a bérek a Királyságban." }
    { group:19, id:226, text: "Emelkedtek a bérek a Királyságban." }
    { group:19, id:227, text: "Csökkent a kereskedelem ezzel a várossal." }
    { group:19, id:228, text: "Nőtt a kereskedelem ezzel a várossal." }
    { group:19, id:229, text: "Javult a Királyság megítélése." }
    { group:19, id:230, text: "Új népességi mérföldkövet értél el." }
    { group:19, id:231, text: "Egy kisebb isten megáldotta a várost." }
    { group:19, id:232, text: "Megkezdődik az ünnepség." }
    { group:19, id:233, text: "A kérés most már teljesíthető: az áruk automatikusan útnak indulnak." }
    { group:19, id:234, text: "Az Állatkert nem működhet, ezért el lett távolítva. A város nem tud szalmát vagy vadhúst előállítani, illetve importálni." }
    { group:19, id:235, text: "Ennek az épületnek vadhúsra van szüksége a működéshez." }
    { group:19, id:236, text: "Építs Vadászkunyhót." }
    { group:19, id:237, text: "Építs Vadászkunyhót, vagy rendeld el a vadhús importját." }
    { group:19, id:238, text: "Építs Vadászkunyhót, vagy importálj vadhúst." }
    { group:19, id:239, text: "Ehhez az emlékműhöz réz szükséges." }
    { group:19, id:240, text: "Ehhez az emlékműhöz márvány szükséges." }
    { group:19, id:241, text: "Alexandriai Könyvtárból csak egy épülhet!" }
    { group:19, id:242, text: "A Pharosz világítótoronyból csak egy épülhet!" }
    { group:19, id:243, text: "Caesareumból csak egy épülhet!" }
    { group:19, id:244, text: "Járvány tört ki." }
    { group:19, id:245, text: "Malária ütötte fel a fejét." }
    { group:19, id:246, text: "Ehhez az emlékműhöz gránit szükséges." }
    { group:19, id:247, text: "Teljes egészében sziklás területre kell építeni." }
    { group:19, id:248, text: "A Pharosz világítótorony nem bontható le." }
    { group:19, id:249, text: "Sírrablók kifosztottak egy ősi sírt!" }
    { group:19, id:250, text: "Nagy Sándor mauzóleumát kifosztották!" }
    { group:19, id:251, text: "Sírrablók ellopták a sírmellékleteket!" }
    { group:19, id:252, text: "Elfogtak egy sírrablót." }
    { group:19, id:253, text: "Ennek az épületnek olajra és fazekasárura van szüksége a működéshez." }
    { group:19, id:254, text: "Építs Fazekasműhelyt." }
    { group:19, id:255, text: "Nyiss kereskedelmi útvonalat fazekasáru importálására." }
    { group:19, id:256, text: "Utasítsd a Kereskedelmi Felügyelőt fazekasáru importálására." }
    { group:19, id:257, text: "Nyiss kereskedelmi útvonalat olaj importálására." }
    { group:19, id:258, text: "Utasítsd a Kereskedelmi Felügyelőt olaj importálására." }
    { group:19, id:259, text: "Ennek az épületnek hennára van szüksége a működéshez." }
    { group:19, id:260, text: "Építs Hennaföldet." }
    { group:19, id:261, text: "Utasítsd a Kereskedelmi Felügyelőt henna importálására." }
    { group:19, id:262, text: "Nyiss kereskedelmi útvonalat henna importálására." }
    { group:19, id:263, text: "Ennek az épületnek olajra van szüksége a működéshez." }
    { group:19, id:264, text: "Ennek az épületnek fazekasárura van szüksége a működéshez." }
    { group:19, id:265, text: "Építs Festékkészítőt, vagy nyiss kereskedelmi útvonalat festék importálására." }
    { group:19, id:266, text: "Építs Festékkészítőt, vagy utasítsd a Kereskedelmi Felügyelőt a festék importálására." }
    { group:19, id:267, text: "Építs Festékkészítőt." }
    { group:19, id:268, text: "Ennek az épületnek agyagra és festékre van szüksége a működéshez." }
    { group:19, id:269, text: "Munkaerő szükséges." }
    { group:19, id:270, text: "Teljes egészében sziklafalra kell építeni." }
    { group:19, id:271, text: "... úgy, hogy a bejárata szabad területre nyíljon." }
    { group:20, id:0, text: "Kr. e." }
    { group:20, id:1, text: "Kr. u." }

    { group:21, id:0, text: "Elephantine" }
    { group:21, id:1, text: "Abüdosz" }
    { group:21, id:2, text: "Bahariya-oázis" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apollinopolisz" }
    { group:21, id:5, text: "Bubasztisz" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Büblosz" }
    { group:21, id:8, text: "Dahsur" }
    { group:21, id:9, text: "Dakhla-oázis" }
    { group:21, id:10, text: "Abuszír" }
    { group:21, id:11, text: "Dunqul-oázis" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "Farafra-oázis" }
    { group:21, id:14, text: "Gáza" }
    { group:21, id:15, text: "Semna" }
    { group:21, id:16, text: "Herakleopolisz" }
    { group:21, id:17, text: "Kahun" }
    { group:21, id:18, text: "Mirgissza" }
    { group:21, id:19, text: "Itjtawy" }
    { group:21, id:20, text: "Dendera" }
    { group:21, id:21, text: "Jerikó" }
    { group:21, id:22, text: "Koptosz" }
    { group:21, id:23, text: "Kerma" }
    { group:21, id:24, text: "Kharga-oázis" }
    { group:21, id:25, text: "Hermopolisz" }
    { group:21, id:26, text: "Knósszosz" }
    { group:21, id:27, text: "Küréné" }
    { group:21, id:28, text: "Meidum" }
    { group:21, id:29, text: "Memphisz" }
    { group:21, id:30, text: "Beni Haszan" }
    { group:21, id:31, text: "Mükéné" }
    { group:21, id:32, text: "Hierakónpolisz" }
    { group:21, id:33, text: "Naqada" }
    { group:21, id:34, text: "Héliopolisz" }
    { group:21, id:35, text: "Buto" }
    { group:21, id:36, text: "Punt" }
    { group:21, id:37, text: "Qanta" }
    { group:21, id:38, text: "Gíza" }
    { group:21, id:39, text: "Avarisz" }
    { group:21, id:40, text: "Szakkara" }
    { group:21, id:41, text: "Lükopolisz" }
    { group:21, id:42, text: "Mersa Gawasisz" }
    { group:21, id:43, text: "Szelima-oázis" }
    { group:21, id:44, text: "Serabit el-Khadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Sharuhen" }
    { group:21, id:47, text: "Thinisz" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toska" }
    { group:21, id:50, text: "Türosz" }
    { group:21, id:51, text: "Théba" }
    { group:21, id:52, text: "Peluszion" }
    { group:21, id:53, text: "Alexandria" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medina" }
    { group:21, id:56, text: "Abu Szimbel" }
    { group:21, id:57, text: "Actium" }
    { group:21, id:58, text: "Róma" }
    { group:21, id:59, text: "Tanisz" }
    { group:21, id:60, text: "Pi-Jer" }
    { group:21, id:61, text: "Siwa-oázis" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Piramesse" }
    { group:21, id:64, text: "Athén" }
    { group:21, id:65, text: "Cleoantonopolisz" }
    { group:22, id:0, text: "'Üres csapat'" }
    { group:22, id:1, text: "'Az Oroszlánok'" }
    { group:22, id:2, text: "'A Krokodilok'" }
    { group:22, id:3, text: "'A Kobrák'" }
    { group:22, id:4, text: "'A Skorpiók'" }
    { group:22, id:5, text: "'A Sólymok'" }
    { group:22, id:6, text: "'A Kosok'" }
    { group:22, id:7, text: "'A Leopárdok'" }
    { group:22, id:8, text: "'A Pókok'" }
    { group:22, id:9, text: "'A Macskák'" }
    { group:22, id:10, text: "'A Hiénák'" }

    { group:23, id:0, text: "Semmi" }
    { group:23, id:1, text: "Gabonafélék" }
    { group:23, id:2, text: "Hús" }
    { group:23, id:3, text: "Saláta" }
    { group:23, id:4, text: "Csicseriborsó" }
    { group:23, id:5, text: "Gránátalma" }
    { group:23, id:6, text: "Füge" }
    { group:23, id:7, text: "Hal" }
    { group:23, id:8, text: "Vadhús" }
    { group:23, id:9, text: "Szalma" }
    { group:23, id:10, text: "Fegyverek" }
    { group:23, id:11, text: "Agyag" }
    { group:23, id:12, text: "Téglák" }
    { group:23, id:13, text: "Kerámia" }
    { group:23, id:14, text: "Árpa" }
    { group:23, id:15, text: "Sör" }
    { group:23, id:16, text: "Len" }
    { group:23, id:17, text: "Vászon" }
    { group:23, id:18, text: "Drágakövek" }
    { group:23, id:19, text: "Luxuscikkek" }
    { group:23, id:20, text: "Fa" }
    { group:23, id:21, text: "Arany" }
    { group:23, id:22, text: "Nád" }
    { group:23, id:23, text: "Papirusz" }
    { group:23, id:24, text: "Egyszerű kő" }
    { group:23, id:25, text: "Mészkő" }
    { group:23, id:26, text: "Gránit" }
    { group:23, id:27, text: "Unused12" }
    { group:23, id:28, text: "Harci szekér" }
    { group:23, id:29, text: "Réz" }
    { group:23, id:30, text: "Homokkő" }
    { group:23, id:31, text: "Olaj" }
    { group:23, id:32, text: "Henna" }
    { group:23, id:33, text: "Festék" }
    { group:23, id:34, text: "Lámpák" }
    { group:23, id:35, text: "Márvány" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Csapatok" }
    { group:23, id:38, text: "Ékszerek (luxuscikkek)" }
    { group:23, id:39, text: "Ékszerek" }
    { group:23, id:40, text: "Bor (luxuscikkek)" }
    { group:23, id:41, text: "Bor" }
    { group:23, id:42, text: "Elefántcsont (luxuscikkek)" }
    { group:23, id:43, text: "Elefántcsont" }
    { group:23, id:44, text: "Ébenfa (luxuscikkek)" }
    { group:23, id:45, text: "Ébenfa" }
    { group:23, id:46, text: "Tömjén (luxuscikkek)" }
    { group:23, id:47, text: "Tömjén" }
    { group:23, id:48, text: "Olívaolaj (luxuscikkek)" }
    { group:23, id:49, text: "Olívaolaj" }
    { group:23, id:50, text: "Leopárdbőrök (luxuscikkek)" }
    { group:23, id:51, text: "Leopárdbőrök" }
    { group:23, id:52, text: "Parfüm (luxuscikkek)" }
    { group:23, id:53, text: "Parfüm" }
    { group:23, id:54, text: "Ez a hely szándékosan üresen maradt" }

    { group:23, id:55, text: "zsák gabona" }
    { group:23, id:56, text: "húsdarabok" }
    { group:23, id:57, text: "fej saláta" }
    { group:23, id:58, text: "korsó csicseriborsó" }
    { group:23, id:59, text: "gránátalmák" }
    { group:23, id:60, text: "korsó füge" }
    { group:23, id:61, text: "vödör hal" }
    { group:23, id:62, text: "adag vadhús" }
    { group:23, id:63, text: "szalmabálák" }
    { group:23, id:64, text: "fegyverek" }
    { group:23, id:65, text: "agyagos zsákok" }
    { group:23, id:66, text: "téglák" }
    { group:23, id:67, text: "kerámiadarabok" }
    { group:23, id:68, text: "árpacsomagok" }
    { group:23, id:69, text: "sörös korsók" }
    { group:23, id:70, text: "lenbálák" }
    { group:23, id:71, text: "vászontekercsek" }
    { group:23, id:72, text: "drágakövek" }
    { group:23, id:73, text: "luxuscikkes erszények" }
    { group:23, id:74, text: "faoszlopok" }
    { group:23, id:75, text: "arany" }
    { group:23, id:76, text: "nád" }
    { group:23, id:77, text: "papiruszlapok" }
    { group:23, id:78, text: "egyszerű kőtömbök" }
    { group:23, id:79, text: "mészkőtömbök" }
    { group:23, id:80, text: "gránittömbök" }
    { group:23, id:81, text: "unused line812" }
    { group:23, id:82, text: "Harci szekerek" }
    { group:23, id:83, text: "rézrúdak" }
    { group:23, id:84, text: "homokkőtömbök" }
    { group:23, id:85, text: "olajos korsók" }
    { group:23, id:86, text: "hennabálák" }
    { group:23, id:87, text: "festékes korsók" }
    { group:23, id:88, text: "lámpák" }
    { group:23, id:89, text: "márványtömbök" }
    { group:23, id:90, text: "debenek" }
    { group:23, id:91, text: "csapatok" }
    { group:24, id:0, text: "1. hét" }
    { group:24, id:1, text: "2. hét" }
    { group:24, id:2, text: "3. hét" }
    { group:24, id:3, text: "4. hét" }
    { group:24, id:4, text: "5. hét" }
    { group:24, id:5, text: "6. hét" }
    { group:24, id:6, text: "7. hét" }
    { group:24, id:7, text: "8. hét" }
    { group:24, id:8, text: "9. hét" }
    { group:24, id:9, text: "10. hét" }
    { group:24, id:10, text: "11. hét" }
    { group:24, id:11, text: "12. hét" }
    { group:24, id:12, text: "13. hét" }
    { group:24, id:13, text: "14. hét" }
    { group:24, id:14, text: "15. hét" }
    { group:24, id:15, text: "16. hét" }

    { group:25, id:0, text: "jan." }
    { group:25, id:1, text: "febr." }
    { group:25, id:2, text: "márc." }
    { group:25, id:3, text: "ápr." }
    { group:25, id:4, text: "máj." }
    { group:25, id:5, text: "jún." }
    { group:25, id:6, text: "júl." }
    { group:25, id:7, text: "aug." }
    { group:25, id:8, text: "szept." }
    { group:25, id:9, text: "okt." }
    { group:25, id:10, text: "nov." }
    { group:25, id:11, text: "dec." }

    { group:26, id:0, text: "Üres" }
    { group:26, id:1, text: "Piros" }
    { group:26, id:2, text: "Kék" }
    { group:26, id:3, text: "Zöld" }
    { group:26, id:4, text: "Narancssárga" }
    { group:26, id:5, text: "Ezüst" }
    { group:26, id:6, text: "Lila" }
    { group:26, id:7, text: "Sárga" }
    { group:26, id:8, text: "Fekete" }

    { group:27, id:0, text: "Predinasztikus kor" }
    { group:27, id:1, text: "Korai dinasztikus kor" }
    { group:27, id:2, text: "Óbirodalom" }
    { group:27, id:3, text: "Középbirodalom" }
    { group:27, id:4, text: "Újbirodalom" }
    { group:27, id:5, text: "A Királyok völgye" }
    { group:27, id:6, text: "II. Ramszesz" }
    { group:27, id:7, text: "Ókori hódítók" }
    { group:27, id:8, text: "Kleopátra fővárosa" }

    { group:28, id:0, text: "Sehol" }
    { group:28, id:1, text: "Visszavonás" }
    { group:28, id:2, text: "Gazdaság" }
    { group:28, id:3, text: "Nyersanyagok" }
    { group:28, id:4, text: "Építőcéhek" }
    { group:28, id:5, text: "Út" }
    { group:28, id:6, text: "Vályogfal" }
    { group:28, id:7, text: "Vízkiemelő" }
    { group:28, id:8, text: "Öntözőcsatorna" }
    { group:28, id:9, text: "Ásás" }
    { group:28, id:10, text: "1. ház" }
    { group:28, id:11, text: "2. ház" }
    { group:28, id:12, text: "3. ház" }
    { group:28, id:13, text: "4. ház" }
    { group:28, id:14, text: "5. ház" }
    { group:28, id:15, text: "6. ház" }
    { group:28, id:16, text: "7. ház" }
    { group:28, id:17, text: "8. ház" }
    { group:28, id:18, text: "9. ház" }
    { group:28, id:19, text: "10. ház" }
    { group:28, id:20, text: "11. ház" }
    { group:28, id:21, text: "12. ház" }
    { group:28, id:22, text: "13. ház" }
    { group:28, id:23, text: "14. ház" }
    { group:28, id:24, text: "15. ház" }
    { group:28, id:25, text: "16. ház" }
    { group:28, id:26, text: "17. ház" }
    { group:28, id:27, text: "18. ház" }
    { group:28, id:28, text: "19. ház" }
    { group:28, id:29, text: "20. ház" }
    { group:28, id:30, text: "Zenepavilon" }
    { group:28, id:31, text: "Bódé" }
    { group:28, id:32, text: "Szenet-ház" }
    { group:28, id:33, text: "Pavilon" }
    { group:28, id:34, text: "Téli kert" }
    { group:28, id:35, text: "Tánciskola" }
    { group:28, id:36, text: "Zsonglőriskola" }
    { group:28, id:37, text: "Szenet-mester" }
    { group:28, id:38, text: "Tér" }
    { group:28, id:39, text: "Kertek" }
    { group:28, id:40, text: "Harci szekérhajtók" }
    { group:28, id:41, text: "Kis szobor" }
    { group:28, id:42, text: "Közepes szobor" }
    { group:28, id:43, text: "Nagy szobor" }
    { group:28, id:44, text: "Íjászok" }
    { group:28, id:45, text: "Gyalogság" }
    { group:28, id:46, text: "Patika" }
    { group:28, id:47, text: "Halottasház" }
    { group:28, id:48, text: "Emlékművek" }
    { group:28, id:49, text: "Fogorvos" }
    { group:28, id:50, text: "Raktárudvar" }
    { group:28, id:51, text: "Írnokiskola" }
    { group:28, id:52, text: "Vízi átkelőhelyek" }
    { group:28, id:53, text: "Könyvtár" }
    { group:28, id:54, text: "Erőd" }
    { group:28, id:55, text: "Rendőrőrs" }
    { group:28, id:56, text: "unused 921" }
    { group:28, id:57, text: "Erőd" }
    { group:28, id:58, text: "Vályog kapuépület" }
    { group:28, id:59, text: "Vályogtorony" }
    { group:28, id:60, text: "Ozirisz temploma" }
    { group:28, id:61, text: "Ré temploma" }
    { group:28, id:62, text: "Ptah temploma" }
    { group:28, id:63, text: "Seth temploma" }
    { group:28, id:64, text: "Basztet temploma" }
    { group:28, id:65, text: "Ozirisz templomkomplexuma" }
    { group:28, id:66, text: "Ré templomkomplexuma" }
    { group:28, id:67, text: "Ptah templomkomplexuma" }
    { group:28, id:68, text: "Seth templomkomplexuma" }
    { group:28, id:69, text: "Basztet templomkomplexuma" }
    { group:28, id:70, text: "Bazár" }
    { group:28, id:71, text: "Magtár" }
    { group:28, id:72, text: "Raktárudvar" }
    { group:28, id:73, text: "Raktárudvarok" }
    { group:28, id:74, text: "Hajóács" }
    { group:28, id:75, text: "Kikötő" }
    { group:28, id:76, text: "Halászkikötő" }
    { group:28, id:77, text: "Személyes palota" }
    { group:28, id:78, text: "Családi palota" }
    { group:28, id:79, text: "Dinasztikus palota" }
    { group:28, id:80, text: "unused 945" }
    { group:28, id:81, text: "Építészeti hivatal" }
    { group:28, id:82, text: "Híd" }
    { group:28, id:83, text: "unused 948" }
    { group:28, id:84, text: "Falusi palota" }
    { group:28, id:85, text: "Városi palota" }
    { group:28, id:86, text: "Adószedő" }
    { group:28, id:87, text: "Adószedő" }
    { group:28, id:88, text: "Semmi" }
    { group:28, id:89, text: "Semmi" }
    { group:28, id:90, text: "Vízkiemelő" }
    { group:28, id:91, text: "Szépítés" }
    { group:28, id:92, text: "Kút" }
    { group:28, id:93, text: "Semmi" }
    { group:28, id:94, text: "Akadémia" }
    { group:28, id:95, text: "Toborzó" }
    { group:28, id:96, text: "Templomok" }
    { group:28, id:97, text: "Templomkomplexum" }
    { group:28, id:98, text: "Jósda" }
    { group:28, id:99, text: "Leégett rom" }
    { group:28, id:100, text: "Árpa" }
    { group:28, id:101, text: "Len" }
    { group:28, id:102, text: "Gabonafélék" }
    { group:28, id:103, text: "Saláta" }
    { group:28, id:104, text: "Gránátalma" }
    { group:28, id:105, text: "Csicseriborsó" }
    { group:28, id:106, text: "Egyszerűkő-bánya" }
    { group:28, id:107, text: "Mészkőbánya" }
    { group:28, id:108, text: "Favágó" }
    { group:28, id:109, text: "Agyagbánya" }
    { group:28, id:110, text: "Sörfőzde" }
    { group:28, id:111, text: "Takács" }
    { group:28, id:112, text: "Fegyverkovács" }
    { group:28, id:113, text: "Ötvös" }
    { group:28, id:114, text: "Fazekas" }
    { group:28, id:115, text: "Vadászház" }
    { group:28, id:116, text: "Semmi" }
    { group:28, id:117, text: "Semmi" }
    { group:28, id:118, text: "Semmi" }
    { group:28, id:119, text: "Semmi" }
    { group:28, id:120, text: "unused 985" }
    { group:28, id:121, text: "Repedés (nem használt?)" }
    { group:28, id:122, text: "unused 987" }
    { group:28, id:123, text: "Semmi" }
    { group:28, id:124, text: "Semmi" }
    { group:28, id:125, text: "Semmi" }
    { group:28, id:126, text: "Semmi" }
    { group:28, id:127, text: "Semmi" }
    { group:28, id:128, text: "Semmi" }
    { group:28, id:129, text: "Semmi" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Komphely-állomás" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Úttorlasz" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Ozirisz szentélye" }
    { group:28, id:141, text: "Ré szentélye" }
    { group:28, id:142, text: "Ptah szentélye" }
    { group:28, id:143, text: "Seth szentélye" }
    { group:28, id:144, text: "Basztet szentélye" }
    { group:28, id:145, text: "Szentély: " }
    { group:28, id:146, text: "Szentély:" }
    { group:28, id:147, text: "Szentély: " }
    { group:28, id:148, text: "Szentély: " }
    { group:28, id:149, text: "Szentély:" }
    { group:28, id:150, text: "Szentélyek" }
    { group:28, id:151, text: "Ozirisz temploma" }
    { group:28, id:152, text: "Ré temploma" }
    { group:28, id:153, text: "Ptah temploma" }
    { group:28, id:154, text: "Seth temploma" }
    { group:28, id:155, text: "Basztet temploma" }
    { group:28, id:156, text: "5. isten" }
    { group:28, id:157, text: "6. isten" }
    { group:28, id:158, text: "7. isten" }
    { group:28, id:159, text: "8. isten" }
    { group:28, id:160, text: "9. isten" }
    { group:28, id:161, text: "Aranybánya" }
    { group:28, id:162, text: "Drágakőbánya" }
    { group:28, id:163, text: "Közönséges kőzet" }
    { group:28, id:164, text: "Érclelőhely" }
    { group:28, id:165, text: "Unused 1030" }
    { group:28, id:166, text: "Unused 1031" }
    { group:28, id:167, text: "Tűzoltóság" }
    { group:28, id:168, text: "Téglafal" }
    { group:28, id:169, text: "Fal" }
    { group:28, id:170, text: "Tégla kapuépület" }
    { group:28, id:171, text: "Kapuépület" }
    { group:28, id:172, text: "Téglatorony" }
    { group:28, id:173, text: "Torony" }
    { group:28, id:174, text: "Vályogépítmények" }
    { group:28, id:175, text: "Téglaépítmények" }
    { group:28, id:176, text: "Védelmi építmények" }
    { group:28, id:177, text: "Ácsok céhe" }
    { group:28, id:178, text: "Kőművesek céhe" }
    { group:28, id:179, text: "Kőfaragók céhe" }
    { group:28, id:180, text: "Vízellátás" }
    { group:28, id:181, text: "Szállítókikötő" }
    { group:28, id:182, text: "Hadihajó-kikötő" }
    { group:28, id:183, text: "Piramis" }
    { group:28, id:184, text: "Bíróság" }
    { group:28, id:185, text: "Katonai akadémia 2" }
    { group:28, id:186, text: "Katonai akadémia 3" }
    { group:28, id:187, text: "Falusi palota" }
    { group:28, id:188, text: "Városi palota" }
    { group:28, id:189, text: "Városközponti palota" }
    { group:28, id:190, text: "Bazár 2" }
    { group:28, id:191, text: "Magtár 2" }
    { group:28, id:192, text: "Kikötő 2" }
    { group:28, id:193, text: "Raktárudvar 2" }
    { group:28, id:194, text: "Marhatenyészet" }
    { group:28, id:195, text: "Nádgyűjtő" }
    { group:28, id:196, text: "Fügefarm" }
    { group:28, id:197, text: "Mocsárvidék" }
    { group:28, id:198, text: "Homokdűnék" }
    { group:28, id:199, text: "Munkatábor" }
    { group:28, id:200, text: "Vályog kapuépület" }
    { group:28, id:201, text: "Tégla kapuépület" }
    { group:28, id:202, text: "Kapuépület" }
    { group:28, id:203, text: "Papiruszkészítő" }
    { group:28, id:204, text: "Téglagyár" }
    { group:28, id:205, text: "Harci szekérkészítő" }
    { group:28, id:206, text: "Orvos" }
    { group:28, id:207, text: "unused 1072" }
    { group:28, id:208, text: "unused 1073" }
    { group:28, id:209, text: "Ünnepi tér" }
    { group:28, id:210, text: "Szfinx" }
    { group:28, id:211, text: "Templomkomplexum-fejlesztés" }
    { group:28, id:212, text: "Templomkomplexum-fejlesztés" }
    { group:28, id:213, text: "unused 1078" }
    { group:28, id:214, text: "Kiszállási pont" }
    { group:28, id:215, text: "unused 1080" }
    { group:28, id:216, text: "Gránitbánya" }
    { group:28, id:217, text: "Rézbánya" }
    { group:28, id:218, text: "temp1" }
    { group:28, id:219, text: "temp2" }
    { group:28, id:220, text: "temp3" }
    { group:28, id:221, text: "Homokkőbánya" }
    { group:28, id:222, text: "Mauzóleum" }
    { group:28, id:223, text: "Sziklafal" }
    { group:28, id:224, text: "Henna" }
    { group:28, id:225, text: "Alexandria könyvtára" }
    { group:28, id:226, text: "Állatkert" }
    { group:28, id:227, text: "Caesareum" }
    { group:28, id:228, text: "Pharosz világítótornya" }
    { group:28, id:229, text: "Kis királysír" }
    { group:28, id:230, text: "Abu Szimbel" }
    { group:28, id:231, text: "Kézművesek céhe" }
    { group:28, id:232, text: "Lámpakészítő" }
    { group:28, id:233, text: "Festékkészítő" }
    { group:28, id:234, text: "Közepes királysír" }
    { group:28, id:235, text: "Nagy királysír" }
    { group:28, id:236, text: "Hatalmas királysír" }
    { group:29, id:0, text: "Durva kunyhó" }
    { group:29, id:1, text: "Masszív kunyhó" }
    { group:29, id:2, text: "Szegényes viskó" }
    { group:29, id:3, text: "Egyszerű viskó" }
    { group:29, id:4, text: "Egyszerű vályogház" }
    { group:29, id:5, text: "Átlagos vályogház" }
    { group:29, id:6, text: "Szerény tanya" }
    { group:29, id:7, text: "Tágas tanya" }
    { group:29, id:8, text: "Szerény lakás" }
    { group:29, id:9, text: "Tágas lakás" }
    { group:29, id:10, text: "Átlagos lakóház" }
    { group:29, id:11, text: "Tágas lakóház" }
    { group:29, id:12, text: "Elegáns lakóház" }
    { group:29, id:13, text: "Fényűző lakóház" }
    { group:29, id:14, text: "Átlagos kúria" }
    { group:29, id:15, text: "Tágas kúria" }
    { group:29, id:16, text: "Elegáns kúria" }
    { group:29, id:17, text: "Tekintélyes kúria" }
    { group:29, id:18, text: "Szerény birtok" }
    { group:29, id:19, text: "Palotai birtok" }

    { group:29, id:20, text: "Durva kunyhók" }
    { group:29, id:21, text: "Masszív kunyhók" }
    { group:29, id:22, text: "Szegényes viskók" }
    { group:29, id:23, text: "Egyszerű viskók" }
    { group:29, id:24, text: "Egyszerű vályogházak" }
    { group:29, id:25, text: "Átlagos vályogházak" }
    { group:29, id:26, text: "Szerény tanyák" }
    { group:29, id:27, text: "Tágas tanyák" }
    { group:29, id:28, text: "Szerény lakások" }
    { group:29, id:29, text: "Tágas lakások" }
    { group:29, id:30, text: "Átlagos lakóházak" }
    { group:29, id:31, text: "Tágas lakóházak" }
    { group:29, id:32, text: "Elegáns lakóházak" }
    { group:29, id:33, text: "Fényűző lakóházak" }
    { group:29, id:34, text: "Átlagos kúriák" }
    { group:29, id:35, text: "Tágas kúriák" }
    { group:29, id:36, text: "Elegáns kúriák" }
    { group:29, id:37, text: "Tekintélyes kúriák" }
    { group:29, id:38, text: "Szerény birtokok" }
    { group:29, id:39, text: "Palotai birtokok" }

    { group:29, id:40, text: "Durva kunyhók:" }
    { group:29, id:41, text: "Masszív kunyhók:" }
    { group:29, id:42, text: "Szegényes viskók:" }
    { group:29, id:43, text: "Egyszerű viskók:" }
    { group:29, id:44, text: "Egyszerű vályogházak:" }
    { group:29, id:45, text: "Átlagos vályogházak:" }
    { group:29, id:46, text: "Szerény tanyák:" }
    { group:29, id:47, text: "Tágas tanyák:" }
    { group:29, id:48, text: "Szerény lakások:" }
    { group:29, id:49, text: "Tágas lakások:" }
    { group:29, id:50, text: "Átlagos lakóházak:" }
    { group:29, id:51, text: "Tágas lakóházak:" }
    { group:29, id:52, text: "Elegáns lakóházak:" }
    { group:29, id:53, text: "Fényűző lakóházak:" }
    { group:29, id:54, text: "Átlagos kúriák:" }
    { group:29, id:55, text: "Tágas kúriák:" }
    { group:29, id:56, text: "Elegáns kúriák:" }
    { group:29, id:57, text: "Tekintélyes kúriák:" }
    { group:29, id:58, text: "Szerény birtokok:" }
    { group:29, id:59, text: "Palotai birtokok:" }

    { group:30, id:0, text: "Pharaoh/Cleopatra indítása" }
    { group:30, id:1, text: "Pharaoh demó indítása" }
    { group:30, id:2, text: "  Activision weboldala " }
    { group:30, id:3, text: "Küldetésszerkesztő" }
    { group:30, id:4, text: "Kilépés " }
    { group:30, id:5, text: "Legnagyobb családok" }
    { group:31, id:0, text: "Adj meg egy családnevet" }
    { group:31, id:1, text: "Jobb kattintással folytathatod" }

    { group:32, id:0, text: "Falusi vén" }
    { group:32, id:1, text: "Falusi nemes" }
    { group:32, id:2, text: "Királyi tudós" }
    { group:32, id:3, text: "Királyi írnok" }
    { group:32, id:4, text: "Királyi bíró" }
    { group:32, id:5, text: "Királyi polgármester" }
    { group:32, id:6, text: "Királyi kormányzó" }
    { group:32, id:7, text: "Nomarkhosz" }
    { group:32, id:8, text: "Kancellár" }
    { group:32, id:9, text: "Vezír" }
    { group:32, id:10, text: "Fáraó" }
    { group:32, id:11, text: "Ó, falusi vén" }
    { group:32, id:12, text: "Ó, falusi nemes" }
    { group:32, id:13, text: "Ó, királyi tudós" }
    { group:32, id:14, text: "Ó, királyi írnok" }
    { group:32, id:15, text: "Ó, királyi bíró" }
    { group:32, id:16, text: "Ó, királyi polgármester" }
    { group:32, id:17, text: "Ó, királyi kormányzó" }
    { group:32, id:18, text: "Ó, nomarkhosz" }
    { group:32, id:19, text: "Ó, kancellár" }
    { group:32, id:20, text: "Ó, vezír" }
    { group:32, id:21, text: "Ó, nagy fáraó" }
    { group:32, id:22, text: "Jelentéktelen küldetés" }
    { group:32, id:23, text: "Nagyon egyszerű küldetés" }
    { group:32, id:24, text: "Könnyű küldetés" }
    { group:32, id:25, text: "Kissé könnyű küldetés" }
    { group:32, id:26, text: "Átlagos küldetés" }
    { group:32, id:27, text: "Kissé nehéz küldetés" }
    { group:32, id:28, text: "Nehéz küldetés" }
    { group:32, id:29, text: "Nagyon nehéz küldetés" }
    { group:32, id:30, text: "Rendkívül nehéz küldetés" }
    { group:32, id:31, text: "Gyakorlatilag lehetetlen küldetés" }

    { group:33, id:0, text: "Apró térkép" }
    { group:33, id:1, text: "Kis térkép" }
    { group:33, id:2, text: "Közepes térkép" }
    { group:33, id:3, text: "Nagy térkép" }
    { group:33, id:4, text: "Hatalmas térkép" }
    { group:33, id:5, text: "Óriási térkép" }
    { group:33, id:6, text: "Mégsem" }

    { group:34, id:0, text: "Nincs támadó" }
    { group:34, id:1, text: "Ellenséges hadsereg" }
    { group:34, id:2, text: "Egyiptomi hadsereg" }
    { group:34, id:3, text: "A fáraó hadserege" }
    { group:34, id:4, text: "Beduin hadsereg" }

    { group:35, id:0, text: "Egyiptomi város elesik" }
    { group:35, id:1, text: "idegen város meghódítva" }
    { group:35, id:2, text: "kereskedelmi útvonal elérhetővé vált" }
    { group:35, id:3, text: "kereskedelmi útvonal lezárult" }
    { group:35, id:4, text: "kereskedelmi város ostrom alatt" }

    { group:36, id:0, text: "Élelmiszer-ellátás megtámadása" }
    { group:36, id:1, text: "Aranykészletek megtámadása" }
    { group:36, id:2, text: "Legjobb épületek megtámadása" }
    { group:36, id:3, text: "Csapatok megtámadása" }
    { group:36, id:4, text: "Véletlenszerű támadás" }

    { group:37, id:0, text: "Hükszoszok" }
    { group:37, id:1, text: "Tengeri népek" }
    { group:37, id:2, text: "Hettiták" }
    { group:37, id:3, text: "Mitanniak" }
    { group:37, id:4, text: "Kúsiták" }
    { group:37, id:5, text: "Líbiaiak" }
    { group:37, id:6, text: "Núbiaiak" }
    { group:37, id:7, text: "Kánaániak" }
    { group:37, id:8, text: "Asszírok" }
    { group:37, id:9, text: "Rómaiak" }
    { group:37, id:10, text: "Föníciaiak" }
    { group:37, id:11, text: "Perzsák" }
    { group:37, id:12, text: "Egyiptomiak" }
    { group:37, id:13, text: "Beduinok" }

    { group:37, id:14, text: "Egy hükszosz katona" }
    { group:37, id:15, text: "A Tengeri népek egy katonája" }
    { group:37, id:16, text: "Egy hettita katona" }
    { group:37, id:17, text: "Egy mitanni katona" }
    { group:37, id:18, text: "Egy kúsita katona" }
    { group:37, id:19, text: "Egy líbiai katona" }
    { group:37, id:20, text: "Egy núbiai katona" }
    { group:37, id:21, text: "Egy kánaáni katona" }
    { group:37, id:22, text: "Egy asszír katona" }
    { group:37, id:23, text: "Egy római katona" }
    { group:37, id:24, text: "Egy föníciai katona" }
    { group:37, id:25, text: "Egy perzsa katona" }
    { group:37, id:26, text: "Egy egyiptomi katona" }
    { group:37, id:27, text: "Egy beduin katona" }

    { group:37, id:28, text: "egy hükszosz hadsereg" }
    { group:37, id:29, text: "a Tengeri népek hadserege" }
    { group:37, id:30, text: "egy hettita hadsereg" }
    { group:37, id:31, text: "egy mitanni hadsereg" }
    { group:37, id:32, text: "egy kúsita hadsereg" }
    { group:37, id:33, text: "egy líbiai hadsereg" }
    { group:37, id:34, text: "egy núbiai hadsereg" }
    { group:37, id:35, text: "egy kánaáni hadsereg" }
    { group:37, id:36, text: "egy asszír hadsereg" }
    { group:37, id:37, text: "egy római hadsereg" }
    { group:37, id:38, text: "egy föníciai hadsereg" }
    { group:37, id:39, text: "egy perzsa hadsereg" }
    { group:37, id:40, text: "egy egyiptomi hadsereg" }
    { group:37, id:41, text: "egy beduin hadsereg" }
    { group:38, id:0, text: "Különleges események" }
    { group:38, id:1, text: "Földrengés" }
    { group:38, id:2, text: "Gladiátor-lázadás" }
    { group:38, id:3, text: "Fáraóváltás" }
    { group:38, id:4, text: "Tengeri kereskedelmi probléma" }
    { group:38, id:5, text: "Szárazföldi kereskedelmi probléma" }
    { group:38, id:6, text: "A fáraó megemeli a béreket" }
    { group:38, id:7, text: "A fáraó csökkenti a béreket" }
    { group:38, id:8, text: "Szennyezett víz" }
    { group:38, id:9, text: "Aranybánya-beomlás" }
    { group:38, id:10, text: "Agyagbányák elárasztva" }
    { group:38, id:11, text: "Használatban" }
    { group:38, id:12, text: "Időzítés" }
    { group:38, id:13, text: "Véletlenszerű" }

    { group:39, id:0, text: "Saját városunk" }
    { group:39, id:1, text: "Fáraó kereskedővárosa" }
    { group:39, id:2, text: "Fáraó városa" }
    { group:39, id:3, text: "Egyiptomi kereskedőváros" }
    { group:39, id:4, text: "Egyiptomi város" }
    { group:39, id:5, text: "Idegen kereskedőváros" }
    { group:39, id:6, text: "Idegen város" }

    { group:40, id:0, text: "Nincs" }
    { group:40, id:1, text: "Kisebb" }
    { group:40, id:2, text: "Átlagos" }
    { group:40, id:3, text: "Nagyobb" }
    { group:41, id:0, text: "Sehol" }
    { group:41, id:1, text: "Semmi" }
    { group:41, id:2, text: "Semmi" }
    { group:41, id:3, text: "Semmi" }
    { group:41, id:4, text: "Semmi" }
    { group:41, id:5, text: "Út" }
    { group:41, id:6, text: "Agyagfal" }
    { group:41, id:7, text: "Öntözőcsatorna" }
    { group:41, id:8, text: "Vízkiemelő" }
    { group:41, id:9, text: "Semmi" }

    { group:41, id:10, text: "Durva kunyhó" }
    { group:41, id:11, text: "Masszív kunyhó" }
    { group:41, id:12, text: "Szegényes viskó" }
    { group:41, id:13, text: "Egyszerű viskó" }
    { group:41, id:14, text: "Egyszerű vályogház" }
    { group:41, id:15, text: "Átlagos vályogház" }
    { group:41, id:16, text: "Szerény tanya" }
    { group:41, id:17, text: "Tágas tanya" }
    { group:41, id:18, text: "Szerény lakás" }
    { group:41, id:19, text: "Tágas lakás" }
    { group:41, id:20, text: "Átlagos lakóház" }
    { group:41, id:21, text: "Tágas lakóház" }
    { group:41, id:22, text: "Elegáns lakóház" }
    { group:41, id:23, text: "Fényűző lakóház" }
    { group:41, id:24, text: "Átlagos kúria" }
    { group:41, id:25, text: "Tágas kúria" }
    { group:41, id:26, text: "Elegáns kúria" }
    { group:41, id:27, text: "Tekintélyes kúria" }
    { group:41, id:28, text: "Szerény birtok" }
    { group:41, id:29, text: "Palotai birtok" }

    { group:41, id:30, text: "Zenepavilon" }
    { group:41, id:31, text: "Bódé" }
    { group:41, id:32, text: "Szenet-ház" }
    { group:41, id:33, text: "Pavilon" }
    { group:41, id:34, text: "Téli kert" }
    { group:41, id:35, text: "Tánciskola" }
    { group:41, id:36, text: "Zsonglőriskola" }
    { group:41, id:37, text: "Harci szekér-kiképzés" }
    { group:41, id:38, text: "Tér" }
    { group:41, id:39, text: "Kertek" }
    { group:41, id:40, text: "Gyalogsági erőd" }
    { group:41, id:41, text: "Kis szobor" }
    { group:41, id:42, text: "Közepes szobor" }
    { group:41, id:43, text: "Nagy szobor" }
    { group:41, id:44, text: "Íjászok" }
    { group:41, id:45, text: "Gyalogság" }
    { group:41, id:46, text: "Patika" }
    { group:41, id:47, text: "Halottasház" }
    { group:41, id:48, text: "Emlékművek" }
    { group:41, id:49, text: "Fogorvos" }
    { group:41, id:50, text: "Elosztóközpont" }
    { group:41, id:51, text: "Írnokképző iskola" }
    { group:41, id:52, text: "Vízi átkelők" }
    { group:41, id:53, text: "Könyvtár" }
    { group:41, id:54, text: "Semmi" }
    { group:41, id:55, text: "Rendőrőrs" }
    { group:41, id:56, text: "unused 1315" }
    { group:41, id:57, text: "Erődök" }
    { group:41, id:58, text: "Agyag kapuház" }
    { group:41, id:59, text: "Agyagtorony" }

    { group:41, id:60, text: "Ozirisz temploma" }
    { group:41, id:61, text: "Ré temploma" }
    { group:41, id:62, text: "Ptah temploma" }
    { group:41, id:63, text: "Seth temploma" }
    { group:41, id:64, text: "Bast temploma" }
    { group:41, id:65, text: "Ozirisz templomegyüttese" }
    { group:41, id:66, text: "Ré templomegyüttese" }
    { group:41, id:67, text: "Ptah templomegyüttese" }
    { group:41, id:68, text: "Seth templomegyüttese" }
    { group:41, id:69, text: "Bast templomegyüttese" }

    { group:41, id:70, text: "Bazár" }
    { group:41, id:71, text: "Magtár" }
    { group:41, id:72, text: "Raktárudvar" }
    { group:41, id:73, text: "Raktárudvarok" }
    { group:41, id:74, text: "Hajóács" }
    { group:41, id:75, text: "Kikötő" }
    { group:41, id:76, text: "Halászati kikötő" }
    { group:41, id:77, text: "Személyes palota" }
    { group:41, id:78, text: "Családi palota" }
    { group:41, id:79, text: "Dinasztikus palota" }
    { group:41, id:80, text: "unused 1339" }
    { group:41, id:81, text: "Építészeti állomás" }
    { group:41, id:82, text: "Kis híd" }
    { group:41, id:83, text: "Nagy híd" }
    { group:41, id:84, text: "Falusi palota" }
    { group:41, id:85, text: "Városi palota" }
    { group:41, id:86, text: "Adószedő" }
    { group:41, id:87, text: "Adószedő" }
    { group:41, id:88, text: "unused 1347" }
    { group:41, id:89, text: "unused 1348" }
    { group:41, id:90, text: "Vízkiemelő" }
    { group:41, id:91, text: "Szépítés" }
    { group:41, id:92, text: "Kút" }
    { group:41, id:93, text: "Semmi" }
    { group:41, id:94, text: "Akadémia" }
    { group:41, id:95, text: "Toborzó" }
    { group:41, id:96, text: "Semmi" }
    { group:41, id:97, text: "Semmi" }
    { group:41, id:98, text: "Jósda" }
    { group:41, id:99, text: "Égő rom" }
    { group:41, id:100, text: "Árpafarm" }
    { group:41, id:101, text: "Lenfarm" }
    { group:41, id:102, text: "Gabonafarm" }
    { group:41, id:103, text: "Salátafarm" }
    { group:41, id:104, text: "Gránátalmafarm" }
    { group:41, id:105, text: "Csicseriborsó-farm" }
    { group:41, id:106, text: "Egyszerű kőfejtő" }
    { group:41, id:107, text: "Mészkőbánya" }
    { group:41, id:108, text: "Favágó" }
    { group:41, id:109, text: "Agyagbánya" }
    { group:41, id:110, text: "Sörfőzde" }
    { group:41, id:111, text: "Takács" }
    { group:41, id:112, text: "Fegyverkovács" }
    { group:41, id:113, text: "Ékszerész" }
    { group:41, id:114, text: "Fazekas" }
    { group:41, id:115, text: "Vadászház" }
    { group:41, id:116, text: "Fű" }
    { group:41, id:117, text: "Fák" }
    { group:41, id:118, text: "Víz" }
    { group:41, id:119, text: "Földrengés" }
    { group:41, id:120, text: "Bozót" }
    { group:41, id:121, text: "Sziklák" }
    { group:41, id:122, text: "Rét" }
    { group:41, id:123, text: "unused 1382" }
    { group:41, id:124, text: "unused 1383" }
    { group:41, id:125, text: "Út" }
    { group:41, id:126, text: "Inváziós pont" }
    { group:41, id:127, text: "Belépési pont" }
    { group:41, id:128, text: "Kilépési pont" }
    { group:41, id:129, text: "unused 1388" }
    { group:41, id:130, text: "Folyó be" }
    { group:41, id:131, text: "Folyó ki" }
    { group:41, id:132, text: "Halászati pont" }
    { group:41, id:133, text: "Gyilkos pont" }
    { group:41, id:134, text: "Ártér" }
    { group:41, id:135, text: "Öntözés" }
    { group:41, id:136, text: "Kompállomás" }
    { group:41, id:137, text: "Úthálózat" }
    { group:41, id:138, text: "Útzár" }
    { group:41, id:139, text: "Zsákmánypont" }

    { group:41, id:140, text: "Ozirisz szentélye" }
    { group:41, id:141, text: "Ré szentélye" }
    { group:41, id:142, text: "Ptah szentélye" }
    { group:41, id:143, text: "Seth szentélye" }
    { group:41, id:144, text: "Bast szentélye" }
    { group:41, id:145, text: "5. isten szentélye" }
    { group:41, id:146, text: "6. isten szentélye" }
    { group:41, id:147, text: "7. isten szentélye" }
    { group:41, id:148, text: "8. isten szentélye" }
    { group:41, id:149, text: "9. isten szentélye" }
    { group:41, id:150, text: "Szentély" }
    { group:41, id:151, text: "Ideiglenes kis 5" }
    { group:41, id:152, text: "Ideiglenes kis 6" }
    { group:41, id:153, text: "Ideiglenes kis 7" }
    { group:41, id:154, text: "Ideiglenes kis 8" }
    { group:41, id:155, text: "Ideiglenes kis 9" }
    { group:41, id:156, text: "Ideiglenes nagy 5" }
    { group:41, id:157, text: "Ideiglenes nagy 6" }
    { group:41, id:158, text: "Ideiglenes nagy 7" }
    { group:41, id:159, text: "Ideiglenes nagy 8" }
    { group:41, id:160, text: "Ideiglenes nagy 9" }
    { group:41, id:161, text: "Aranybánya" }
    { group:41, id:162, text: "Drágakőbánya" }
    { group:41, id:163, text: "Közönséges szikla" }
    { group:41, id:164, text: "Aranytartalmú szikla" }
    { group:41, id:165, text: "Drágakőtartalmú szikla" }
    { group:41, id:166, text: "Kidolgozott szikla" }
    { group:41, id:167, text: "Tűzoltóság" }
    { group:41, id:168, text: "Téglafal" }
    { group:41, id:169, text: "Fal" }
    { group:41, id:170, text: "Tégla kapuház" }
    { group:41, id:171, text: "Kapuház" }
    { group:41, id:172, text: "Téglatorony" }
    { group:41, id:173, text: "Torony" }
    { group:41, id:174, text: "Agyagépítmények" }
    { group:41, id:175, text: "Téglaépítmények" }
    { group:41, id:176, text: "Védelmi építmények" }
    { group:41, id:177, text: "Ácsok céhe" }
    { group:41, id:178, text: "Kőművesek céhe" }
    { group:41, id:179, text: "Kőfaragók céhe" }
    { group:41, id:180, text: "Vízellátás" }
    { group:41, id:181, text: "Szállítókikötő" }
    { group:41, id:182, text: "Hadihajó-kikötő" }
    { group:41, id:183, text: "Piramis" }
    { group:41, id:184, text: "Bíróság" }
    { group:41, id:185, text: "Katonai akadémia 2" }
    { group:41, id:186, text: "Katonai akadémia 3" }
    { group:41, id:187, text: "Falusi palota" }
    { group:41, id:188, text: "Városi palota" }
    { group:41, id:189, text: "Nagyvárosi palota" }
    { group:41, id:190, text: "Bazár 2" }
    { group:41, id:191, text: "Magtár 2" }
    { group:41, id:192, text: "Kikötő 2" }
    { group:41, id:193, text: "Raktárudvar 2" }
    { group:41, id:194, text: "Marhafarm" }
    { group:41, id:195, text: "Nádgyűjtő" }
    { group:41, id:196, text: "Fügefarm" }
    { group:41, id:197, text: "Mocsárvidék" }
    { group:41, id:198, text: "Homokdűne" }
    { group:41, id:199, text: "Munkatábor" }
    { group:41, id:200, text: "Agyag kapuház" }
    { group:41, id:201, text: "Tégla kapuház" }
    { group:41, id:202, text: "Kapuház" }
    { group:41, id:203, text: "Papiruszkészítő" }
    { group:41, id:204, text: "Téglagyártó" }
    { group:41, id:205, text: "Harci szekér készítő" }
    { group:41, id:206, text: "Orvos" }
    { group:41, id:207, text: "unused 1466" }
    { group:41, id:208, text: "unused 1467" }
    { group:41, id:209, text: "Ünnepi tér" }
    { group:41, id:210, text: "Szfinx" }
    { group:41, id:211, text: "Templomkomplexum fejlesztése" }
    { group:41, id:212, text: "Templomkomplexum fejlesztése" }
    { group:41, id:213, text: "unused 1472" }
    { group:41, id:214, text: "Partraszállási pont" }
    { group:41, id:215, text: "unused 1474" }
    { group:41, id:216, text: "Gránitbánya" }
    { group:41, id:217, text: "Rézbánya" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Homokkőbánya" }
    { group:41, id:222, text: "Mauzóleum" }
    { group:41, id:223, text: "Sziklafal" }
    { group:41, id:224, text: "Hennaültetvény" }
    { group:41, id:225, text: "Alexandria könyvtára" }
    { group:41, id:226, text: "Állatkert" }
    { group:41, id:227, text: "Caesareum" }
    { group:41, id:228, text: "Pharosz világítótorony" }
    { group:41, id:229, text: "Kis királyi sír" }
    { group:41, id:230, text: "Abu Simbel" }
    { group:41, id:231, text: "Kézművesek céhe" }
    { group:41, id:232, text: "Lámpakészítő" }
    { group:41, id:233, text: "Festékkészítő" }
    { group:41, id:234, text: "Közepes királyi sír" }
    { group:41, id:235, text: "Nagy királyi sír" }
    { group:41, id:236, text: "Hatalmas királyi sír" }
    { group:42, id:1, text: "Teljes képernyő" }
    { group:42, id:2, text: "Ablakos képernyő" }
    { group:42, id:3, text: "640 x 480 felbontás" }
    { group:42, id:4, text: "800 x 600 felbontás" }
    { group:42, id:5, text: "1024 x 768 felbontás" }
    { group:42, id:6, text: "Mégse" }
    { group:43, id:0, text: "Város mentése" }
    { group:43, id:1, text: "Mentett játék betöltése" }
    { group:43, id:2, text: "A fájl nem létezik" }
    { group:43, id:3, text: "Küldetés mentése" }
    { group:43, id:4, text: "Küldetés betöltése" }
    { group:43, id:5, text: "Folytatod?" }
    { group:43, id:6, text: "Fájl törlése" }
    { group:43, id:7, text: "A fájl betöltése nem sikerült" }
    { group:44, id:0, text: "Objektum hozzáadása" }
    { group:44, id:1, text: "Objektumok szerkesztése" }
    { group:44, id:2, text: "Objektum törlése" }
    { group:44, id:3, text: "Általános" }
    { group:44, id:4, text: "Térkép importálása" }
    { group:44, id:5, text: "Vásárol" }
    { group:44, id:6, text: "nem ingyenes" }
    { group:44, id:7, text: "OK" }
    { group:44, id:8, text: "Egyszerű grafika" }
    { group:44, id:9, text: "Város" }
    { group:44, id:10, text: "Régió" }
    { group:44, id:11, text: "Csatajelző" }
    { group:44, id:12, text: "ingyenes" }
    { group:44, id:13, text: "Kezdő dátum" }
    { group:44, id:14, text: "A fáraó kérései" }
    { group:44, id:15, text: "Inváziók" }
    { group:44, id:16, text: "Elfogadás" }
    { group:44, id:17, text: "Mégse" }
    { group:44, id:18, text: "A királyság jelenlegi állapota" }
    { group:44, id:19, text: "Nincsenek kérések" }
    { group:44, id:20, text: "Nincsenek inváziók" }
    { group:44, id:21, text: "A küldetés még nincs teljesítve" }
    { group:44, id:22, text: "Invázió ütemezése" }
    { group:44, id:23, text: "Szabad hely" }
    { group:44, id:24, text: "itt:" }
    { group:44, id:25, text: "Kérés ütemezésének törlése" }
    { group:44, id:26, text: "Invázió ütemezésének törlése" }
    { group:44, id:27, text: "innen:" }
    { group:44, id:28, text: "Szárazföldi útvonal" }
    { group:44, id:29, text: "Tengeri útvonal" }
    { group:44, id:30, text: "Hadseregjelző" }
    { group:44, id:31, text: "Ellenségjelző" }
    { group:44, id:32, text: "Útvonal" }
    { group:44, id:33, text: "Követelmény" }
    { group:44, id:34, text: "Költség" }
    { group:44, id:35, text: "Nyersanyagok" }
    { group:44, id:36, text: "Elad" }
    { group:44, id:37, text: "Rövid leírás" }
    { group:44, id:38, text: "A küldetés rövid leírása a játékosok számára. Történet, célok, tippek stb." }
    { group:44, id:39, text: "Kezdő pénzkészlet" }
    { group:44, id:40, text: "Kérések" }
    { group:44, id:41, text: "Az ellenség:" }
    { group:44, id:42, text: "Inváziók" }
    { group:44, id:43, text: "A főváros biztosít gabonát?" }
    { group:44, id:44, text: "Engedélyezett épületek" }
    { group:44, id:45, text: "Győzelmi feltételek" }
    { group:44, id:46, text: "Módosítás" }
    { group:44, id:47, text: "Engedélyezett építmények" }
    { group:44, id:48, text: "Győzelmi feltételek" }
    { group:44, id:49, text: "Különleges események" }
    { group:44, id:50, text: "Szükséges kultúra" }
    { group:44, id:51, text: "Szükséges jólét" }
    { group:44, id:52, text: "Emlékművek száma" }
    { group:44, id:53, text: "Szükséges királyság" }
    { group:44, id:54, text: "Időkorlát (vesztési idő)" }
    { group:44, id:55, text: "Túlélés (győzelmi idő)" }
    { group:44, id:56, text: "Győzelmi lakosság" }
    { group:44, id:57, text: "Szükséges földrengéspont" }
    { group:44, id:58, text: "Földrengéspont beállítva" }
    { group:44, id:59, text: "Nincs belépési pont" }
    { group:44, id:60, text: "Nincs népességpont" }
    { group:44, id:61, text: "Nincs kilépési pont" }
    { group:44, id:62, text: "Népességpont beállítva" }
    { group:44, id:63, text: "Nincsenek inváziós pontok" }
    { group:44, id:64, text: "1 inváziós pont" }
    { group:44, id:65, text: "inváziós pontok" }
    { group:44, id:66, text: "Nincsenek folyópontok" }
    { group:44, id:67, text: "Folyópontok beállítva" }
    { group:44, id:68, text: "Fáraói ajándék" }
    { group:44, id:69, text: "Csatajelző" }
    { group:44, id:70, text: "Útvonal" }
    { group:44, id:71, text: "Parancs" }
    { group:44, id:72, text: "Kér" }
    { group:44, id:73, text: "Királyság" }
    { group:44, id:74, text: "Mérföldkő:" }
    { group:44, id:75, text: "Mentés" }
    { group:44, id:76, text: "Tereptípus" }
    { group:44, id:77, text: "Nedves éghajlat" }
    { group:44, id:78, text: "Normál éghajlat" }
    { group:44, id:79, text: "Száraz éghajlat" }
    { group:44, id:80, text: "Sodródó tárgyak bekapcsolva?" }
    { group:44, id:81, text: "Terjeszkedés itt:" }
    { group:44, id:82, text: "Kiterjesztett pozíciók" }
    { group:44, id:83, text: "Kínálati/keresleti szintek beállítása" }
    { group:44, id:84, text: "Nincs" }
    { group:44, id:85, text: "Alacsony" }
    { group:44, id:86, text: "Közepes" }
    { group:44, id:87, text: "Magas" }
    { group:44, id:88, text: "Kezdőfeltételek" }
    { group:44, id:89, text: "Kezdő dátum módosítása" }
    { group:44, id:90, text: "Belépés 90 - csak jelzőként használva" }
    { group:44, id:91, text: "Mérföldkő - 25%" }
    { group:44, id:92, text: "Mérföldkő - 50%" }
    { group:44, id:93, text: "Mérföldkő - 75%" }
    { group:44, id:94, text: "Keresletváltozások" }
    { group:44, id:95, text: "Események" }
    { group:44, id:96, text: "Esemény hozzáadása" }
    { group:44, id:97, text: "Esemény törlése" }
    { group:44, id:98, text: "útvonalon" }
    { group:44, id:99, text: "csökken" }
    { group:44, id:100, text: "nő" }
    { group:44, id:101, text: "az áru iránti kereslet" }
    { group:44, id:102, text: "unused 1601" }
    { group:44, id:103, text: "csökken ennyivel:" }
    { group:44, id:104, text: "nő ennyivel:" }
    { group:44, id:105, text: "érvénytelen eseményindító" }
    { group:44, id:106, text: "TIPP: A vessző és pont billentyűkkel gyorsan lépkedhetsz ezek és más objektumok között." }
    { group:44, id:107, text: "Szabad játék (nincs győzelem/vereség)" }
    { group:44, id:108, text: "Kezdő rang" }
    { group:44, id:109, text: "Terep" }
    { group:44, id:110, text: "Ellenségek" }
    { group:44, id:111, text: "Inváziók" }
    { group:44, id:112, text: "Nincs katonai tevékenység" }
    { group:44, id:113, text: "Kisebb összecsapások" }
    { group:44, id:114, text: "Némi katonai tevékenység" }
    { group:44, id:115, text: "Jelentős katonai tevékenység" }
    { group:44, id:116, text: "A város támadás alatt áll" }
    { group:44, id:117, text: "Rang" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "A főváros ellát élelemmel?" }
    { group:44, id:120, text: "Térkép mérete" }
    { group:44, id:121, text: "Apró táj" }
    { group:44, id:122, text: "Kis táj" }
    { group:44, id:123, text: "Átlagos táj" }
    { group:44, id:124, text: "Nagy táj" }
    { group:44, id:125, text: "Nagyon nagy táj" }
    { group:44, id:126, text: "Hatalmas táj" }
    { group:44, id:127, text: "Győzelmi feltételek" }
    { group:44, id:128, text: "Nincs" }
    { group:44, id:129, text: "Kultúra" }
    { group:44, id:130, text: "Jólét" }
    { group:44, id:131, text: "Emlékmű" }
    { group:44, id:132, text: "Királyság" }
    { group:44, id:133, text: "Népesség" }
    { group:44, id:134, text: "Maximális évek száma" }
    { group:44, id:135, text: "Túlélési évek" }
    { group:44, id:136, text: "Ugrás a városba" }
    { group:44, id:137, text: "Szükséges befolyó folyó" }
    { group:44, id:138, text: "Szükséges kifolyó folyó" }
    { group:44, id:139, text: "Esemény" }
    { group:44, id:140, text: "hónap" }
    { group:44, id:141, text: "között" }
    { group:44, id:142, text: "és" }
    { group:44, id:143, text: "városok" }
    { group:44, id:144, text: "jelzőkből" }
    { group:44, id:145, text: "ide:" }
    { group:44, id:146, text: "mennyiség" }
    { group:44, id:147, text: "arány" }
    { group:44, id:148, text: "ebből:" }
    { group:44, id:149, text: "ezen belül:" }
    { group:44, id:150, text: "hónapok" }
    { group:44, id:151, text: "teljesített esemény" }
    { group:44, id:152, text: "elutasított esemény" }
    { group:44, id:153, text: "túl késői esemény" }
    { group:44, id:154, text: "lemondott esemény" }
    { group:44, id:155, text: "elvesztett csata esemény" }
    { group:44, id:156, text: "következő esemény" }
    { group:44, id:157, text: "egyszeri esemény" }
    { group:44, id:158, text: "ismétlődő esemény" }
    { group:44, id:159, text: "csak indításra" }
    { group:44, id:160, text: "jóindulat által indítva" }
    { group:44, id:161, text: "Fáraó" }
    { group:44, id:162, text: "Város" }
    { group:44, id:163, text: "Hadihajók" }
    { group:44, id:164, text: "Istenbeállítások" }
    { group:44, id:165, text: "Nincs védőisten" }
    { group:44, id:166, text: "Útvonal hozzáadása" }
    { group:44, id:167, text: "Útvonal szerkesztése" }
    { group:44, id:168, text: "Útvonal törlése" }
    { group:44, id:169, text: "Általános útvonal" }
    { group:44, id:170, text: "Tengeri kereskedelmi útvonal" }
    { group:44, id:171, text: "Szárazföldi kereskedelmi útvonal" }
    { group:44, id:172, text: "Távolság" }
    { group:44, id:173, text: "Útvonal hossza" }
    { group:44, id:174, text: "Név" }
    { group:44, id:175, text: "Rang" }
    { group:44, id:176, text: "Templomkomplexum" }
    { group:44, id:177, text: "Adósság kamatlába" }
    { group:44, id:178, text: "Ártér beállításai" }
    { group:44, id:179, text: "Az áradás kezdete:" }
    { group:44, id:180, text: "Június eleje" }
    { group:44, id:181, text: "Június vége" }
    { group:44, id:182, text: "Július eleje" }
    { group:44, id:183, text: "Július vége" }
    { group:44, id:184, text: "Augusztus eleje" }
    { group:44, id:185, text: "Augusztus vége" }
    { group:44, id:186, text: "Szeptember eleje" }
    { group:44, id:187, text: "Szeptember vége" }
    { group:44, id:188, text: "Az áradás időtartama:" }
    { group:44, id:189, text: "Két hónap" }
    { group:44, id:190, text: "Három hónap" }
    { group:44, id:191, text: "Négy hónap" }
    { group:44, id:192, text: "Az áradás minősége:" }
    { group:44, id:193, text: "Nincs" }
    { group:44, id:194, text: "Gyenge" }
    { group:44, id:195, text: "Közepes" }
    { group:44, id:196, text: "Jó" }
    { group:44, id:197, text: "Kiváló" }
    { group:44, id:198, text: "Tökéletes" }
    { group:44, id:199, text: "Sikertelen áradás" }
    { group:44, id:200, text: "Tökéletes áradás" }
    { group:44, id:201, text: "Műemlékek kiválasztása" }
    { group:44, id:202, text: "Jelenlegi fáraó:" }
    { group:44, id:203, text: "Játékos megtestesülése:" }
    { group:44, id:204, text: "Királysági árak beállítása" }
    { group:44, id:205, text: "Vásárol" }
    { group:44, id:206, text: "Elad" }
    { group:44, id:207, text: "Elfogad" }
    { group:44, id:208, text: "Elutasít" }
    { group:44, id:209, text: "Elhalaszt" }
    { group:44, id:210, text: "Lakhatási szint" }
    { group:44, id:211, text: "Árak visszaállítása" }
    { group:44, id:212, text: "Isten" }
    { group:44, id:213, text: "1 szekérnyi vagy kőtömb = 100 egység" }
    { group:44, id:214, text: "Térkép szerkesztése" }
    { group:44, id:215, text: "Küldetés indítása" }
    { group:44, id:216, text: "Nehézségi szint" }
    { group:44, id:217, text: "Kilépés" }
    { group:44, id:218, text: "Küldetés kezdése" }
    { group:44, id:219, text: "Mégse" }
    { group:44, id:220, text: "Korábbi eredmények megjelenítése" }
    { group:44, id:221, text: "Küldetés céljainak megjelenítése" }
    { group:44, id:222, text: "Királyságépítő" }
    { group:44, id:223, text: "Visszaállítás" }
    { group:44, id:224, text: "Belépési pont beállítva" }
    { group:44, id:225, text: "Kilépési pont beállítva" }
    { group:44, id:226, text: "1 folyópont beállítva" }
    { group:44, id:227, text: "A játékos Egyiptom ellen harcol mint" }
    { group:45, id:0, text: "Sebességbeállítások" }
    { group:45, id:1, text: "Mégse" }
    { group:45, id:2, text: "Játék sebessége" }
    { group:45, id:3, text: "Görgetési sebesség" }
    { group:45, id:4, text: "OK" }
    { group:45, id:5, text: "Felhők sebessége" }
    { group:45, id:6, text: "Kamera mozgatása középső egérgombbal" }
    { group:45, id:7, text: "Kamera mozgatási sebessége középső egérgombbal" }

    { group:46, id:0, text: "Hangbeállítások" }
    { group:46, id:1, text: "A zene ki van kapcsolva" }
    { group:46, id:2, text: "A zene be van kapcsolva" }
    { group:46, id:3, text: "A beszéd ki van kapcsolva" }
    { group:46, id:4, text: "A beszéd be van kapcsolva" }
    { group:46, id:5, text: "A hangeffektek ki vannak kapcsolva" }
    { group:46, id:6, text: "A hangeffektek be vannak kapcsolva" }
    { group:46, id:7, text: "A városi hangok ki vannak kapcsolva" }
    { group:46, id:8, text: "A városi hangok be vannak kapcsolva" }
    { group:46, id:9, text: "Mégse" }
    { group:46, id:10, text: "Aktuális hangállapot" }
    { group:46, id:11, text: "Hangerő" }
    { group:46, id:12, text: "OK" }

    { group:47, id:0, text: "Egy távoli város" }
    { group:47, id:1, text: "A mi városunk!" }
    { group:47, id:2, text: "Ez a kereskedelmi útvonal még nincs létrehozva" }
    { group:47, id:3, text: "Megnyitás költsége" }
    { group:47, id:4, text: "Vásárol" }
    { group:47, id:5, text: "Elad" }
    { group:47, id:6, text: " szárazföldi kereskedelmi útvonal megnyitásához" }
    { group:47, id:7, text: " vízi kereskedelmi útvonal megnyitásához" }
    { group:47, id:8, text: "A kereskedelem felügyelőjének" }
    { group:47, id:9, text: "Kattints egy városra, hogy információkat kapj róla" }
    { group:47, id:10, text: "Vásárolt" }
    { group:47, id:11, text: "Eladott" }
    { group:47, id:12, text: "ebből:" }
    { group:47, id:13, text: "Egyiptomi város" }
    { group:47, id:14, text: "Elfoglalt város" }
    { group:47, id:15, text: "Ellenséges sereg, amely a Királyság egyik városát fenyegeti" }
    { group:47, id:16, text: "A sereged, amely a Királyság egyik városának felmentésére vonul" }
    { group:47, id:17, text: "A sereged, amely visszatér a városodba" }
    { group:47, id:18, text: "A betörő barbárok legutóbbi összecsapásának helyszíne" }
    { group:47, id:19, text: "A fáraó városa" }

    { group:48, id:0, text: "Apró ecset" }
    { group:48, id:1, text: "Kis ecset" }
    { group:48, id:2, text: "Közepes ecset" }
    { group:48, id:3, text: "Nagy ecset" }
    { group:48, id:4, text: "Legnagyobb ecset" }
    { group:48, id:5, text: "Belépési pont" }
    { group:48, id:6, text: "Kilépési pont" }
    { group:48, id:7, text: "Föld emelése" }
    { group:48, id:8, text: "Föld süllyesztése" }
    { group:48, id:9, text: "Feljáró" }
    { group:48, id:10, text: "1. inváziós pont (szárazföld)" }
    { group:48, id:11, text: "2. inváziós pont (szárazföld)" }
    { group:48, id:12, text: "3. inváziós pont (szárazföld)" }
    { group:48, id:13, text: "4. inváziós pont (szárazföld)" }
    { group:48, id:14, text: "5. inváziós pont (szárazföld)" }
    { group:48, id:15, text: "6. inváziós pont (szárazföld)" }
    { group:48, id:16, text: "7. inváziós pont (szárazföld)" }
    { group:48, id:17, text: "8. inváziós pont (szárazföld)" }
    { group:48, id:18, text: "Folyó belépési pont" }
    { group:48, id:19, text: "Folyó kilépési pont" }
    { group:48, id:20, text: "Bennszülött kunyhó" }
    { group:48, id:21, text: "Bennszülött központ" }
    { group:48, id:22, text: "Bennszülött föld" }
    { group:48, id:23, text: "1. halászhely" }
    { group:48, id:24, text: "2. halászhely" }
    { group:48, id:25, text: "3. halászhely" }
    { group:48, id:26, text: "4. halászhely" }
    { group:48, id:27, text: "5. halászhely" }
    { group:48, id:28, text: "6. halászhely" }
    { group:48, id:29, text: "7. halászhely" }
    { group:48, id:30, text: "8. halászhely" }
    { group:48, id:31, text: "Gyilkos megjelenési pont 1" }
    { group:48, id:32, text: "Gyilkos megjelenési pont 2" }
    { group:48, id:33, text: "Gyilkos megjelenési pont 3" }
    { group:48, id:34, text: "Gyilkos megjelenési pont 4" }
    { group:48, id:35, text: "Víz" }
    { group:48, id:36, text: "Ártér" }
    { group:48, id:37, text: "Öntözőárok" }
    { group:48, id:38, text: "Mocsárvidék" }
    { group:48, id:39, text: "Zsákmány megjelenési pont 1" }
    { group:48, id:40, text: "Zsákmány megjelenési pont 2" }
    { group:48, id:41, text: "Zsákmány megjelenési pont 3" }
    { group:48, id:42, text: "Zsákmány megjelenési pont 4" }
    { group:48, id:43, text: "Közönséges kőzet" }
    { group:48, id:44, text: "Érctartalmú kőzet" }
    { group:48, id:45, text: "Közönséges kőzet" }
    { group:48, id:46, text: "Különleges kőzet" }
    { group:48, id:47, text: "Homokdűnék" }
    { group:48, id:48, text: "9. inváziós pont (tenger)" }
    { group:48, id:49, text: "10. inváziós pont (tenger)" }
    { group:48, id:50, text: "11. inváziós pont (tenger)" }
    { group:48, id:51, text: "12. inváziós pont (tenger)" }
    { group:48, id:52, text: "13. inváziós pont (tenger)" }
    { group:48, id:53, text: "14. inváziós pont (tenger)" }
    { group:48, id:54, text: "15. inváziós pont (tenger)" }
    { group:48, id:55, text: "16. inváziós pont (tenger)" }
    { group:48, id:56, text: "Partraszállási pont 1" }
    { group:48, id:57, text: "Partraszállási pont 2" }
    { group:48, id:58, text: "Partraszállási pont 3" }
    { group:48, id:59, text: "Gyilkos típus 1" }
    { group:48, id:60, text: "Gyilkos típus 2" }
    { group:49, id:0, text: "Fű" }
    { group:49, id:1, text: "Fák" }
    { group:49, id:2, text: "Víz" }
    { group:49, id:3, text: "Földrengés" }
    { group:49, id:4, text: "Bozót" }
    { group:49, id:5, text: "Sziklák" }
    { group:49, id:6, text: "Rét" }
    { group:49, id:7, text: "Fennsík" }
    { group:49, id:8, text: "Ecsetméret" }
    { group:49, id:9, text: "Feljáró" }
    { group:49, id:10, text: "Út" }
    { group:49, id:11, text: "Föld emelése" }
    { group:49, id:12, text: "Föld süllyesztése" }
    { group:49, id:13, text: "Inváziós pont" }
    { group:49, id:14, text: "Vándorlási pont" }
    { group:49, id:15, text: "Belépési pont" }
    { group:49, id:16, text: "Kilépési pont" }
    { group:49, id:17, text: "Folyópont" }
    { group:49, id:18, text: "Folyó be" }
    { group:49, id:19, text: "Folyó ki" }
    { group:49, id:20, text: "Bennszülöttek" }
    { group:49, id:21, text: "Bennszülött kunyhó" }
    { group:49, id:22, text: "Bennszülött központ" }
    { group:49, id:23, text: "Bennszülött föld" }
    { group:49, id:24, text: "Halászvizek" }
    { group:49, id:25, text: "Gyilkos pont" }
    { group:49, id:26, text: "Ártér" }
    { group:49, id:27, text: "Öntözés" }
    { group:49, id:28, text: "Zsákmány" }
    { group:49, id:29, text: "Mocsárvidék" }
    { group:49, id:30, text: "Homokdűnék" }
    { group:49, id:31, text: "Partraszállási pont" }
    { group:49, id:32, text: "Gyilkos típus" }
    { group:49, id:33, text: "Sziklafal" }

    { group:50, id:0, text: "A munkások felügyelője" }
    { group:50, id:1, text: "Élelmiszer-termelés és elosztás" }
    { group:50, id:2, text: "Ipar és kereskedelem" }
    { group:50, id:3, text: "Szórakoztatás" }
    { group:50, id:4, text: "Vallás" }
    { group:50, id:5, text: "Oktatás" }
    { group:50, id:6, text: "Egészség és higiénia" }
    { group:50, id:7, text: "Infrastruktúra" }
    { group:50, id:8, text: "Kormányzat" }
    { group:50, id:9, text: "Katonaság" }
    { group:50, id:10, text: "Szükséglet" }
    { group:50, id:11, text: "Rendelkezésre áll" }
    { group:50, id:12, text: "Foglalkoztatott munkaerő" }
    { group:50, id:13, text: "Munkanélküli munkaerő (" }
    { group:50, id:14, text: "Bér/10" }
    { group:50, id:15, text: "Deben" }
    { group:50, id:16, text: "kevesebb, mint a királysági arány:" }
    { group:50, id:17, text: "több, mint a királysági arány:" }
    { group:50, id:18, text: "(A királyság fizet:" }
    { group:50, id:19, text: "Az idei várható bérköltség:" }
    { group:50, id:20, text: "Zárolva" }
    { group:50, id:21, text: "Prioritás" }
    { group:50, id:22, text: "Ágazat" }
    { group:50, id:23, text: "Szükséglet" }
    { group:50, id:24, text: "Rendelkezésre áll" }
    { group:50, id:25, text: "Prioritási szint" }
    { group:50, id:26, text: "Nincs prioritás" }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Sereg állapota" }
    { group:51, id:1, text: "Menj ide:" }
    { group:51, id:2, text: "csapat" }
    { group:51, id:3, text: "Visszatérés" }
    { group:51, id:4, text: "az erődhöz" }
    { group:51, id:5, text: "Királyság" }
    { group:51, id:6, text: "szolgálat" }
    { group:51, id:7, text: "itt:" }
    { group:51, id:8, text: "Nem érkezett jelentés a várost fenyegető veszélyről." }
    { group:51, id:9, text: "Jelentéseket kapunk arról, hogy ellenségek közelednek a város felé." }
    { group:51, id:10, text: "Ellenségeink már a város látótávolságában vannak." }
    { group:51, id:11, text: "A fáraó csapatainak egy zászlóalja áll kapuink előtt!" }
    { group:51, id:12, text: "Nincs kérés katonai segítségre külföldről." }
    { group:51, id:13, text: "Néhány csapatunkra külföldön van szükség." }
    { group:51, id:14, text: "Zászlóaljunk a Királyságért harcolni vonul." }
    { group:51, id:15, text: "Zászlóaljunk visszafelé menetel a városunkba." }
    { group:51, id:16, text: "Nincs irányítható csapatod. Először építened kell egy erődöt egy új csapat elhelyezéséhez." }
    { group:51, id:17, text: "Csapat" }
    { group:51, id:18, text: "Tapasztalat" }
    { group:51, id:19, text: "Haditengerészet állapota" }
    { group:51, id:20, text: "hadihajó" }
    { group:51, id:21, text: "a kikötőhöz" }
    { group:51, id:22, text: "Hajótest" }
    { group:51, id:23, text: "Erő" }
    { group:51, id:24, text: "Legénység állapota" }
    { group:51, id:25, text: "Nincs irányítható hadihajód. Először építened kell egy kikötőt egy új hadihajóhoz." }
    { group:51, id:26, text: "Haditengerészetünk egy részére máshol van szükség." }
    { group:51, id:27, text: "Csapatunk hajózik egy egyiptomi város megmentésére." }
    { group:51, id:28, text: "Csapatunk visszahajózik a városunkba." }
    { group:51, id:29, text: "külföldön" }
    { group:51, id:30, text: "Kivezénylés" }
    { group:51, id:31, text: "most" }
    { group:51, id:32, text: " és " }

    { group:52, id:0, text: "Királysági megítélés" }
    { group:52, id:1, text: "Megtakarítás:" }
    { group:52, id:2, text: "Adás a városnak" }
    { group:52, id:3, text: "Deben havonta" }
    { group:52, id:4, text: "A falusi elöljáró fizetése:" }
    { group:52, id:5, text: "A falusi nemes fizetése:" }
    { group:52, id:6, text: "A királyi tudós fizetése:" }
    { group:52, id:7, text: "A királyi írnok fizetése:" }
    { group:52, id:8, text: "A királyi bíró fizetése:" }
    { group:52, id:9, text: "A királyi polgármester fizetése:" }
    { group:52, id:10, text: "A királyi kormányzó fizetése:" }
    { group:52, id:11, text: "A nomarkhosz fizetése:" }
    { group:52, id:12, text: "A kancellár fizetése:" }
    { group:52, id:13, text: "A vezír fizetése:" }
    { group:52, id:14, text: "A fáraó fizetése:" }
    { group:52, id:15, text: "Fizetési szint beállítása" }
    { group:52, id:16, text: "Pénz adása a városnak" }
    { group:52, id:17, text: "Az adomány:" }
    { group:52, id:18, text: "Pénz adása" }
    { group:52, id:19, text: "Mind" }
    { group:52, id:20, text: "Aktuális kérések" }
    { group:52, id:22, text: "A közvélemény szerint a sakáloknak kellene átadniuk a maradványaidat." }
    { group:52, id:23, text: "Népszerű vagy a zsonglőrök között, akik komédiáikban használnak fel téged." }
    { group:52, id:24, text: "Széles körben úgy tartják, hogy már puszta jelenléted is maláriát okoz." }
    { group:52, id:25, text: "A patikusok egyetértenek abban, hogy neved keserűbb minden ismert gyógynövénynél." }
    { group:52, id:26, text: "Az anyák a neveddel ijesztgetik kisgyermekeiket." }
    { group:52, id:27, text: "Nevedet soha nem említik udvarias társaságban." }
    { group:52, id:28, text: "Hírneved hitvány, és még saját családod is elkerül." }
    { group:52, id:29, text: "Nevedet ismerik, de kigúnyolják a Két Földön mindenütt." }
    { group:52, id:30, text: "A fontos emberek ismerik nevedet és történetedet, bár hajlamosak lekicsinyelni téged." }
    { group:52, id:31, text: "A Királyságban kevesen ismerik tetteidet, és akik igen, azok nem nyűgöződtek le." }
    { group:52, id:32, text: "Az a kevés ember, aki felismeri nevedet, nem alkot rólad véleményt." }
    { group:52, id:33, text: "Szerény eredményeid nem híresek, de akik ismernek, általában kedvelnek." }
    { group:52, id:34, text: "A fontos emberek ismerik múltadat, és általában helyeslik, amit tettél." }
    { group:52, id:35, text: "Nevedet széles körben ismerik és ünneplik a Két Földön." }
    { group:52, id:36, text: "Hírneved jó, és gyakran keresnek fel rég nem látott rokonaid." }
    { group:52, id:37, text: "Neved említése megmelengeti azok szívét, akik hallják." }
    { group:52, id:38, text: "A Királyság anyái gyermekeiket rólad nevezik el." }
    { group:52, id:39, text: "Sok egyiptomi város fontolgatja, hogy ünnepségeket rendez a tiszteletedre." }
    { group:52, id:40, text: "Az Egyiptomot meghódító legnépszerűbb tánc életed történetét meséli el." }
    { group:52, id:41, text: "Zenészek dalokat szereznek rólad, és neved minden közterületen bevésik." }
    { group:52, id:42, text: "Egyiptom minden lakója örökké szolgálni kíván téged a Nádasok Mezején." }
    { group:52, id:43, text: "a raktárudvarokban" }
    { group:52, id:44, text: "a városi kincstárakban" }
    { group:52, id:45, text: "ember" }
    { group:52, id:46, text: "Fegyverek" }
    { group:52, id:47, text: "Kattints ide a kérés elküldéséhez" }
    { group:52, id:49, text: "Ajándék küldése" }
    { group:52, id:51, text: "Egy babiloni agyagtábla" }
    { group:52, id:52, text: "Perzsa szőnyegek" }
    { group:52, id:53, text: "Ősi faragványok" }
    { group:52, id:54, text: "Afrikai elefántcsont" }
    { group:52, id:55, text: "Egy fellépő rabszolgacsoport" }
    { group:52, id:56, text: "Arabiai csődörök" }
    { group:52, id:57, text: "Művelt rabszolga" }
    { group:52, id:58, text: "Líbiai testőrök" }
    { group:52, id:59, text: "Gepárdok és zsiráfok" }
    { group:52, id:60, text: "Egy láda zafír" }
    { group:52, id:61, text: "Aranyszekér" }
    { group:52, id:62, text: "Libanoni cédrushajó" }
    { group:52, id:71, text: "Figyelmeztetés: A jelenlegi rangodnál magasabb fizetés adása magadnak nem fog senkit lenyűgözni." }
    { group:52, id:72, text: "Csapatok küldése a védelemre:" }
    { group:52, id:73, text: "Egy kis sereg támadása ennyi idő múlva várható:" }
    { group:52, id:74, text: "Egy átlagos sereg támadása ennyi idő múlva várható:" }
    { group:52, id:75, text: "Egy nagy sereg támadása ennyi idő múlva várható:" }
    { group:52, id:76, text: "Jelenleg szabadon beállíthatod saját fizetésed szintjét." }
    { group:52, id:77, text: "A palota most megtiltja, hogy fizetést vegyél fel, mivel saját döntésedből folytatod a kormányzást." }
    { group:52, id:78, text: "Személyes fizetés felvételéhez kastélyt kell építened." }
    { group:52, id:79, text: "idén lopás miatt elvesztett deben." }
    { group:52, id:80, text: "Vízi csapatok küldése ide:" }
    { group:52, id:81, text: "Politikai felügyelő számára: " }
    { group:53, id:0, text: "Megítélés felügyelője" }
    { group:53, id:1, text: "Kultúra" }
    { group:53, id:2, text: "Jólét" }
    { group:53, id:3, text: "Műemlék" }
    { group:53, id:4, text: "Királyság" }
    { group:53, id:5, text: "Szükséges" }
    { group:53, id:6, text: "Népesség:" }
    { group:53, id:7, text: "Nincs célzott népesség" }
    { group:53, id:8, text: "Kattints egy megítélési számra az információk megtekintéséhez" }
    { group:53, id:9, text: "Túl kevés zsonglőr van a városban. Ha lehetséges, építs több zsonglőrszínpadot a megítélés javításához." }
    { group:53, id:10, text: "Túl kevés zenész van a városban. Ha lehetséges, építs több zenészszínpadot a megítélés javításához." }
    { group:53, id:11, text: "Túl kevés táncos van a városban. Ha lehetséges, építs több táncsszínpadot a megítélés javításához." }
    { group:53, id:12, text: "Túl kevés Szenet-ház van a városban. Ha lehetséges, építs Szenet-házakat a megítélés javításához." }
    { group:53, id:13, text: "Túl kevés állatkert van a városban. Ha lehetséges, építs állatkerteket a megítélés javításához." }
    { group:53, id:14, text: "Túl kevés imahely van a városban. Több építése javítaná ezt a megítélést." }
    { group:53, id:15, text: "Túl kevés írnokképző iskola működik a városban. Több építése javítaná ezt a megítélést." }
    { group:53, id:16, text: "Túl kevés könyvtár működik a városban. Ha lehetséges, építs többet a megítélés javításához." }
    { group:53, id:17, text: "Nincs elég ház, amely hozzáfér fogorvoshoz. A jobb hozzáférés javítaná ezt a megítélést." }
    { group:53, id:18, text: "Nincs elég ház, amely hozzáfér orvoshoz. A jobb hozzáférés javítaná ezt a megítélést." }
    { group:53, id:19, text: "Nincs elég ház, amely hozzáfér ravatalozóhoz. A jobb hozzáférés javítaná ezt a megítélést." }
    { group:53, id:20, text: "A megítélés javul." }
    { group:53, id:21, text: "A megítélés romlik." }
    { group:53, id:22, text: "A megítélés változatlan." }
    { group:53, id:23, text: "A városi lakóépületek általános minősége visszatartja ezt a megítélést. Javítsd a város lakhatását, hogy növeld." }
    { group:53, id:24, text: "Tavaly a városod pénzt veszített – ez csökkentette a város jólétét." }
    { group:53, id:25, text: "A magas munkanélküliség a városodban rontja a jóléti megítélést." }
    { group:53, id:26, text: "A királysági bérnél kevesebb fizetés rontja a városod virágzó hírnevét." }
    { group:53, id:27, text: "A nyomornegyedek lakóinak magas aránya szegény város benyomását kelti." }
    { group:53, id:28, text: "Az éves adó befizetésének képtelensége kudarcként tünteti fel a városodat." }
    { group:53, id:29, text: "nem használt - az élelmiszerváltozatosság hiánya hat a jólétre." }
    { group:53, id:30, text: "A munkaerőhiány csökkenti a jólétet." }
    { group:53, id:31, text: "A város jóléte nő, ha az exportból származó bevétel meghaladja az import költségét." }
    { group:53, id:32, text: "A királysági megítélésed alacsonyabb, mint tavaly volt. Fizesd be az éves adót, vegyél fel mérsékelt fizetést, és teljesítsd a fáraó vagy a Királyság más városainak kéréseit." }
    { group:53, id:33, text: "A nevetségesen magas fizetésed azt mutatja, hogy teljesen nem törődsz a Királysággal, és csökkenti ezt a megítélést." }
    { group:53, id:34, text: "Az éves adó folyamatos elmulasztása rontja a hírnevedet az egész Királyságban, és csökkenti ezt a megítélést." }
    { group:53, id:35, text: "Bizonyos eseményekre adott válaszaid súlyosan rontották a hírnevedet a Királyságban, és csökkentették ezt a megítélést." }
    { group:53, id:36, text: "A rangodat messze meghaladó fizetés, amit magadnak adsz, csökkenti a hírnevedet a Királyságban." }
    { group:53, id:37, text: "Második éve egymás után nem fizettél adót, és ez rontja a királysági megítélésedet." }
    { group:53, id:38, text: "Bizonyos eseményekre adott válaszaid kissé rontották a helyzetedet a Királyságban." }
    { group:53, id:39, text: "A fizetésed túl magas a jelenlegi rangodhoz képest. A királysági megítélésed javulna, ha valamelyest csökkentenéd." }
    { group:53, id:40, text: "Idén nem tudtad befizetni az adót, ami csökkentette a királysági megítélésedet. Tarts pénzt a kincstárban év végén, hogy teljesíthesd az éves befizetést." }
    { group:53, id:41, text: "A fizetésed túl magas a jelenlegi rangodhoz képest. Jól tennéd, ha csökkentenéd." }
    { group:53, id:42, text: "A céljaid időben történő elérésében mutatott lassú haladásod csökkentette a királysági megítélésedet." }
    { group:53, id:43, text: "A rangod által megengedettnél magasabb fizetés vakmerő megállapítása rosszallást vált ki." }
    { group:53, id:44, text: "A királysági megítélésed magasabb, mint tavaly volt. Utasíthatod a politikai felügyelőt, hogy ajándékot küldjön Egyiptomnak, és ez a megítélés még tovább nő." }
    { group:53, id:45, text: "A királysági megítélésed nem változott tavaly óta. Utasíthatod a politikai felügyelőt, hogy ajándékot küldjön Egyiptomnak, és ez javítani fog rajta." }
	{ group:53, id:46, text: "nem használt - korábban békeértékelési jelentés1" }
	{ group:53, id:47, text: "nem használt - korábban békeértékelési jelentés2" }
	{ group:53, id:48, text: "nem használt - korábban békeértékelési jelentés3" }
	{ group:53, id:49, text: "nem használt - korábban békeértékelési jelentés4" }
	{ group:53, id:50, text: "nem használt - korábban békeértékelési jelentés5" }
	{ group:53, id:51, text: "nem használt - korábban békeértékelési jelentés6" }
	{ group:53, id:52, text: "nem használt - korábban békeértékelési jelentés7" }
	{ group:53, id:53, text: "nem használt - korábban békeértékelési jelentés8" }
	{ group:53, id:54, text: "nem használt - korábban békeértékelési jelentés9" }
	{ group:53, id:55, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:56, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:57, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:58, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:59, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:60, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:61, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:62, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:63, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:64, text: "Ne felejtsd el utasítani a műemlékek felügyelőjét a szükséges temetési felszerelések elküldésére. Látogasd meg a műemlék építési helyszínét is a részletes állapotjelentésért." }
    { group:53, id:65, text: "Ez a város műveltebb, mint bármelyik másik Egyiptomban!" }
    { group:53, id:66, text: "Ennek a városnak a lenyűgöző jóléte egész Egyiptomban beszédtéma!" }
    { group:53, id:67, text: "Ennek a városnak vannak a legnagyszerűbb műemlékei egész Egyiptomban!" }
    { group:53, id:68, text: "A te Királyságod rendelkezik a legjobb megítéléssel egész Egyiptomban!" }
    { group:53, id:69, text: "Ebben a városban még nincsenek műemlékek." }
    { group:54, id:1, text: "Kattints egy árura a kereskedelem, készletezés vagy az iparág állapotának módosításához" }
    { group:54, id:2, text: "Árak mutatása" }
    { group:54, id:3, text: "Készletezés" }
    { group:54, id:4, text: "Nem kereskedik" }
    { group:54, id:5, text: "Import a fenntartáshoz" }
    { group:54, id:6, text: "Export a többlet felett" }
    { group:54, id:7, text: "Nincs iparág a városban" }
    { group:54, id:8, text: "működő iparág a városban" }
    { group:54, id:9, text: "működő iparágak a városban" }
    { group:54, id:10, text: "iparág a városban, jelenleg leállítva" }
    { group:54, id:11, text: "iparágak a városban, jelenleg leállítva" }
    { group:54, id:12, text: "működik" }
    { group:54, id:13, text: "tétlen iparágak a városban" }
    { group:54, id:14, text: "tétlen iparág a városban" }
    { group:54, id:15, text: "a város raktárudvaraiban tárolva" }
    { group:54, id:16, text: "Ipar BE" }
    { group:54, id:17, text: "Ipar KI" }
    { group:54, id:18, text: "Nem kereskedik" }
    { group:54, id:19, text: "Import a fenntartáshoz" }
    { group:54, id:20, text: "Export a többlet esetén" }
    { group:54, id:21, text: "Árak egész Egyiptomban" }
    { group:54, id:22, text: "A vásárlók fizetnek" }
    { group:54, id:23, text: "Az eladók kapnak" }
    { group:54, id:24, text: "Nincs nyitott kereskedelmi útvonal ezekhez az árukhoz" }
    { group:54, id:25, text: "Ezek az áruk csak importból szerezhetők be" }
    { group:54, id:26, text: "Erőforrás készletezése" }
    { group:54, id:27, text: "Kattints ide a készletezés kikapcsolásához" }
    { group:54, id:28, text: "Ezt az erőforrást használod és kereskedsz vele" }
    { group:54, id:29, text: "Kattints ide a készletezéshez" }
    { group:54, id:30, text: "Világtérkép megnyitása" }
    { group:54, id:31, text: "Importálható" }
    { group:54, id:32, text: "Exportálható" }
    { group:54, id:33, text: "Importálható vagy exportálható" }
    { group:54, id:34, text: "Nyiss kereskedelmi útvonalat importhoz" }
    { group:54, id:35, text: "Nyiss kereskedelmi útvonalat exporthoz" }
    { group:54, id:36, text: "Nyiss kereskedelmi útvonalakat importhoz/exporthoz" }
    { group:54, id:37, text: "Importálás szükség szerint" }
    { group:54, id:38, text: "Többlet exportálása" }
    { group:54, id:39, text: "Kattints az importáláshoz" }
    { group:54, id:40, text: "Kattints az exportáláshoz" }
    { group:54, id:41, text: "Nincs eladó ehhez az erőforráshoz" }
    { group:54, id:42, text: "Nincs vásárló ehhez az erőforráshoz" }
    { group:54, id:43, text: "A felügyelő állítsa be az importsávot" }
    { group:54, id:44, text: "A felügyelő állítsa be az exportsávot" }
    { group:54, id:45, text: "több" }
    { group:54, id:46, text: "Vissza a kereskedelmi állapothoz" }
    { group:54, id:47, text: "fegyverenként" }
    { group:54, id:48, text: "szekerenként" }
    { group:54, id:49, text: "tömbönként" }
    { group:54, id:50, text: "100 darabonként" }

    { group:55, id:0, text: "Népesség - Történet" }
    { group:55, id:1, text: "Népesség - Népszámlálás" }
    { group:55, id:2, text: "Népesség - Társadalom" }
    { group:55, id:3, text: "Történet" }
    { group:55, id:4, text: "Népszámlálás" }
    { group:55, id:5, text: "Társadalom" }
    { group:55, id:6, text: "A város népessége idővel" }
    { group:55, id:7, text: "Népesség kor szerinti összetétele (években)" }
    { group:55, id:8, text: "Népesség jövedelem szerinti összetétele" }
    { group:55, id:9, text: "Kunyhólakók" }
    { group:55, id:10, text: "Birtoklakók" }
    { group:55, id:11, text: "A főváros biztosítja az összes élelmet ennek a városnak" }
    { group:55, id:12, text: " élelem " }
    { group:55, id:13, text: " némi élelem a következő hónapra" }
    { group:55, id:14, text: " nincs élelem a következő hónapra" }
    { group:55, id:15, text: " nagyon kevés élelem a következő hónapra" }
    { group:55, id:16, text: "A jelenlegi lakóhelyek befogadóképessége:" }
    { group:55, id:17, text: "több ember" }
    { group:55, id:18, text: "új lakos érkezett ebben a hónapban" }
    { group:55, id:19, text: "új lakos érkezett ebben a hónapban" }
    { group:55, id:20, text: "A lakóhelyek hiánya korlátozza a bevándorlást." }
    { group:55, id:21, text: "Az alacsony bérek csökkentik a városunkba érkező bevándorlást." }
    { group:55, id:22, text: "A munkanélküliség csökkenti a bevándorlók számát." }
    { group:55, id:23, text: "A magtárakban lévő élelem hiánya csökkenti a bevándorlást." }
    { group:55, id:24, text: "A magas adók távol tartanak néhány embert a városunktól." }
    { group:55, id:25, text: "Összességében emberek érkeznek, vagy szeretnének érkezni a városunkba." }
    { group:55, id:26, text: "Összességében emberek hagyják el a városunkat." }
    { group:55, id:27, text: "A munkahelyek hiánya elűzi az embereket." }
    { group:55, id:28, text: "Az emberek máshová mennek magasabb bérek után." }
    { group:55, id:29, text: "Az emberek a magas adókulcsod miatt hagyják el a várost." }
    { group:55, id:30, text: "Összességében a város népessége változatlan." }
    { group:55, id:31, text: "Egyensúly van a városba érkezők és távozók között." }
    { group:55, id:32, text: "A város gazdagsága ellenére a rossz lakhatás elriasztja a bevándorlókat." }
    { group:55, id:33, text: "Senki sem akar a városunkban élni." }
    { group:55, id:34, text: "Előállítunk vagy importálunk elegendő élelmet körülbelül " }
    { group:55, id:35, text: "ember számára." }
    { group:55, id:36, text: "Sokkal többet eszünk, mint amennyit termelünk!" }
    { group:55, id:37, text: "Sokkal többet eszünk, mint amennyit termelünk, ezért városunk zsugorodására számíthatunk." }
    { group:55, id:38, text: "Túl kevés élelmet termelünk. Növekvő városunknak még többre lesz szüksége." }
    { group:55, id:39, text: "Többet eszünk, mint amennyit termelünk." }
    { group:55, id:40, text: "Többet eszünk, mint amennyit termelünk, de zsugorodó városunk kevesebbet fog enni." }
    { group:55, id:41, text: "Túl kevés élelmet termelünk. Növekvő városunknak még többre lesz szüksége." }
    { group:55, id:42, text: "Jelenleg kissé többet eszünk, mint amennyit termelünk. " }
    { group:55, id:43, text: "Kicsivel többet eszünk, mint amennyit termelünk, ezért városunk zsugorodására számíthatunk." }
    { group:55, id:44, text: "Kicsivel többet eszünk, mint amennyit termelünk. Növekvő városunknak többre lesz szüksége." }
    { group:55, id:45, text: "Jelenleg éppen elegendő élelmet termelünk mindenki ellátásához." }
    { group:55, id:46, text: "Nem termelünk felesleges élelmet, és zsugorodó városunk még kevesebbet fog enni." }
    { group:55, id:47, text: "Most éppen elegendő élelmet termelünk, de növekvő városunknak többre lesz szüksége." }
    { group:55, id:48, text: "Jelenleg kissé többet termelünk, mint amennyit eszünk." }
    { group:55, id:49, text: "Kis mennyiségű többlet élelmet termelünk. Zsugorodó városunk még kevesebbet fog enni." }
    { group:55, id:50, text: "Kis élelmiszer-felesleget termelünk, és növekvő városunknak szüksége lesz rá." }
    { group:55, id:51, text: "Jelenleg sokkal többet termelünk, mint amennyit eszünk." }
    { group:55, id:52, text: "Sok felesleges élelmet termelünk. Zsugorodó városunknak még kevesebbre lesz szüksége." }
    { group:55, id:53, text: "Sok felesleges élelmet termelünk, de növekvő városunknak még többre lesz szüksége." }
    { group:56, id:0, text: "Közegészségügyi felügyelő" }
    { group:56, id:1, text: "Szabad" }
    { group:56, id:2, text: "Nincs" }
    { group:56, id:3, text: "Dolgozik" }
    { group:56, id:4, text: "Ellát" }
    { group:56, id:5, text: "Városi lefedettség" }
    { group:56, id:6, text: "beteget" }
    { group:56, id:7, text: "A város bizonyos részein már szükség van orvosi ellátásra." }
    { group:56, id:8, text: "A város egyes részei több orvost szeretnének." }
    { group:56, id:9, text: "A város bizonyos tehetősebb részei fogorvost szeretnének. Egy helyi fogorvos növelné a környék rangját." }
    { group:56, id:10, text: "A város egyre több részén van szükség fogorvosokra. Ahogy a város gazdagodik, egyre több lakos engedheti meg magának az új elefántcsont fogakat." }
    { group:56, id:11, text: "A város egyes részein szükség van patikushoz való hozzáférésre." }
    { group:56, id:12, text: "Egyre többen szeretnének kényelmesen elérhető egészségügyi létesítményeket (patikákat)." }
    { group:56, id:13, text: "Egyes negyedek fejlődését akadályozza a város halottasházi lefedettségének hiánya." }
    { group:56, id:14, text: "A lakosoknak több halottasházra van szükségük, hogy halottaikat megfelelően előkészíthessék a túlvilágra." }
    { group:56, id:15, text: "Senki sem kér egészségügyi vagy higiéniai létesítményeket. Ahogy azonban a város fejlődik, az emberek előbb egészségügyi ellátást, majd fogorvosokat, később pedig még több egészségügyi létesítményt fognak igényelni!" }
    { group:56, id:16, text: "Kis településeden még nem jelentettek egészségügyi problémákat." }
    { group:56, id:17, text: "A város egészségügyi helyzete borzalmas! Ilyen szörnyű körülmények között biztos a járvány." }
    { group:56, id:18, text: "A város egészségügyi helyzete rettenetes! A betegség szinte elkerülhetetlen." }
    { group:56, id:19, text: "A város egészségügyi helyzete rossz. Több egészségügyi dolgozó javíthatna a helyzeten." }
    { group:56, id:20, text: "A város egészségügyi helyzete gyenge. Sok élelem és egészségügyi létesítmény javítana rajta." }
    { group:56, id:21, text: "A város egészségügyi helyzete átlag alatti. Gondoskodj róla, hogy a lakosoknak legyen élelmük és hozzáférésük egészségügyi ellátókhoz." }
    { group:56, id:22, text: "A város egészségügyi helyzete átlagos. A káros hatások ellenőrzés alatt vannak, és az emberek eleget esznek." }
    { group:56, id:23, text: "A város egészségügyi helyzete jó. A lakosokat csak kisebb betegségek sújtják." }
    { group:56, id:24, text: "A város egészségügyi helyzete nagyon jó. A helyi gyógyítók jól végzik a munkájukat." }
    { group:56, id:25, text: "A város egészségügyi helyzete kiváló, a helyi egészségügyi létesítményeknél egyáltalán nincs várakozási idő." }
    { group:56, id:26, text: "A város egészségügyi helyzete szinte tökéletes, az egészségügyi létesítmények gyakorlatilag üresek." }
    { group:56, id:27, text: "A város egészségügyi helyzete tökéletes. Egészségügyi dolgozóid napjaik nagy részét szenetezéssel töltik." }
    { group:56, id:28, text: "A város egészségügyi helyzete borzalmas." }
    { group:56, id:29, text: "A város egészségügyi helyzete rettenetes." }
    { group:56, id:30, text: "A város egészségügyi helyzete rossz." }
    { group:56, id:31, text: "A város egészségügyi helyzete gyenge." }
    { group:56, id:32, text: "A város egészségügyi helyzete átlag alatti." }
    { group:56, id:33, text: "A város egészségügyi helyzete átlagos." }
    { group:56, id:34, text: "A város egészségügyi helyzete jó." }
    { group:56, id:35, text: "A város egészségügyi helyzete nagyon jó." }
    { group:56, id:36, text: "A város egészségügyi helyzete kiváló." }
    { group:56, id:37, text: "A város egészségügyi helyzete szinte tökéletes." }
    { group:56, id:38, text: "A város egészségügyi helyzete tökéletes." }
    { group:56, id:39, text: "Orvosok" }
    { group:56, id:40, text: "Fogorvosok" }
    { group:56, id:41, text: "Patikusok" }
    { group:56, id:42, text: "Halottasházak" }
    { group:56, id:43, text: "Ritka" }
    { group:56, id:44, text: "Nagyon gyenge" }
    { group:56, id:45, text: "Gyenge" }
    { group:56, id:46, text: "Átlag alatti" }
    { group:56, id:47, text: "Átlagos" }
    { group:56, id:48, text: "Átlagos" }
    { group:56, id:49, text: "Átlag feletti" }
    { group:56, id:50, text: "Jó" }
    { group:56, id:51, text: "Nagyon jó" }
    { group:56, id:52, text: "Kiváló" }
    { group:56, id:53, text: "Tökéletes" }
    { group:56, id:54, text: "Nincs" }
    { group:56, id:55, text: "Néhány" }
    { group:56, id:56, text: "Néhány" }
    { group:56, id:57, text: "Több" }
    { group:56, id:58, text: "Sok" }
    { group:56, id:59, text: "A patikusok jelenleg a város védelmén dolgoznak a malária ellen." }
    { group:56, id:60, text: "kitörést jelentettek ebben a hónapban." }
    { group:56, id:61, text: "féle élelem található a városodban." }

    { group:57, id:0, text: "Tanulmányi felügyelő" }
    { group:57, id:1, text: "Dolgozik" }
    { group:57, id:2, text: "Oktathat" }
    { group:57, id:3, text: "Városi lefedettség" }
    { group:57, id:4, text: "gyermeket" }
    { group:57, id:5, text: "Fiatalokat" }
    { group:57, id:6, text: "embert" }
    { group:57, id:7, text: "Nincs" }
    { group:57, id:8, text: "Ritka" }
    { group:57, id:9, text: "Nagyon gyenge" }
    { group:57, id:10, text: "Gyenge" }
    { group:57, id:11, text: "Átlag alatti" }
    { group:57, id:12, text: "Átlagos" }
    { group:57, id:13, text: "Átlagos" }
    { group:57, id:14, text: "Átlag feletti" }
    { group:57, id:15, text: "Jó" }
    { group:57, id:16, text: "Nagyon jó" }
    { group:57, id:17, text: "Kiváló" }
    { group:57, id:18, text: "Tökéletes" }
    { group:57, id:19, text: "A város bizonyos részein már szükség van írnokképző iskolákra. A gyenge oktatás megakadályozza, hogy egyes lakosok fejlesszék otthonaikat." }
    { group:57, id:20, text: "Néhány városrész jobb hozzáférést követel az írnokképző iskolákhoz. Egyes házak elérik a városi iskolákat, mások viszont nem, és ez akadályozza fejlődésüket." }
    { group:57, id:21, text: "A város bizonyos részein már szükség van könyvtárakra. Az embereknek irodalomhoz kell jutniuk, ha írnokként akarnak dolgozni." }
    { group:57, id:22, text: "A város egyes részei jobb könyvtári hozzáférést szeretnének. A felsőbb osztálybeli írnokok nem örülnek annak, hogy ilyen messzire kell gyalogolniuk a könyvtárig." }
    { group:57, id:23, text: "A jobb írnokképző- és könyvtári hozzáférés javítaná a város egyes részeit. Az embereknek nem kellene ilyen messzire gyalogolniuk a tanulásért!" }
    { group:57, id:24, text: "Senki sem igényel még oktatási létesítményeket. Ahogy azonban a város tekintélye nő, az emberek előbb írnokképző iskolákat, később pedig könyvtárakat fognak követelni." }
    { group:57, id:25, text: "Minden otthon, amely igényli, rendelkezik oktatási létesítményekkel. Az írnokképző iskolák és könyvtárak számosak, és senki sem panaszkodik túlzsúfoltságra." }
    { group:57, id:26, text: "Minden otthon, amely igényli, rendelkezik oktatási létesítményekkel, de több írnokképző iskola építése csökkentené az osztálylétszámot és növelné a város kultúráját." }
    { group:57, id:27, text: "Minden otthon, amely igényli, rendelkezik oktatási létesítményekkel, de több könyvtár építése csökkentené a zsúfoltságot és növelné a város kultúráját." }
    { group:57, id:28, text: "Írnokképző iskolák " }
    { group:57, id:29, text: "Könyvtár" }
    { group:58, id:0, text: "Szórakoztatási felügyelő" }
    { group:58, id:1, text: "Dolgozik" }
    { group:58, id:2, text: "Előadások" }
    { group:58, id:3, text: "Szórakoztathat" }
    { group:58, id:4, text: "Városi lefedettség" }
    { group:58, id:5, text: "embert" }
    { group:58, id:6, text: "N/A" }
    { group:58, id:7, text: "Senki sem keres még szórakozási lehetőségeket. Ahogy azonban a városod növekszik, az emberek olyan mulatságokra vágynak majd, mint a zsonglőrködés, a zene és a tánc." }
    { group:58, id:8, text: "Jelenleg elegendő szórakozás áll mindenki rendelkezésére. Ahogy azonban a város növekszik, az emberek több és jobb szórakozási formát fognak kérni." }
    { group:58, id:9, text: "Néhány lakos több kikapcsolódási lehetőséget szeretne. Több szórakozási lehetőség arra ösztönözné őket, hogy fejlesszék otthonaikat." }
    { group:58, id:10, text: "A város egyes részei panaszkodnak, hogy nincs hozzáférésük szórakozási lehetőségekhez. Több szórakozóhely építése segítene ezeknek a szegényebb területeknek a fejlődésében." }
    { group:58, id:11, text: "Néhányan panaszkodnak a környékük elégtelen szórakozási lehetőségei miatt. Lehet, hogy többféle szórakozást kell biztosítanod, vagy több előadóművész-iskolát kell építened, hogy előadókat biztosíts az előadóhelyek számára." }
    { group:58, id:12, text: "Néhány bódé vagy zenepavilon üres színpaddal rendelkezik. Több zsonglőr vagy zenész kielégítené a gyenge szórakozásra panaszkodó városrészek igényeit." }
    { group:58, id:13, text: "Pavilonjaidnak több táncosra van szükségük. Egy új konzervatórium javíthatná a város egyes részeinek szórakoztatási színvonalát." }
    { group:58, id:14, text: "Amíg a szenetházban van alkalmazott és sör is, a szenetmester körbejárja a környéket, hogy emlékeztesse az embereket: a játékok folynak." }
    { group:58, id:15, text: "az utolsó fesztivál óta" }
    { group:58, id:16, text: "Új fesztivál rendezése" }
    { group:58, id:17, text: "Fesztiválok" }
    { group:58, id:18, text: "A legkitartóbb mulatozók még mindig nem aludták ki az utolsó fesztivált." }
    { group:58, id:19, text: "Az emberek még mindig mosolyognak, amikor az utolsó fesztiválodra emlékeznek." }
    { group:58, id:20, text: "A korábbi fesztivál emléke halványul az emberek fejében." }
    { group:58, id:21, text: "Az emberek már nem emlékeznek a városban rendezett utolsó fesztiválra." }
    { group:58, id:22, text: "A lakosok panaszkodnak a városodban rendezett fesztiválok hiánya miatt." }
    { group:58, id:23, text: "Néped nem bírja elviselni még egy fesztivál nélküli év gondolatát." }
    { group:58, id:24, text: "A levert lakosok kételkednek benne, hogy megérnek még egy fesztivált." }
    { group:58, id:30, text: "költsége" }
    { group:58, id:31, text: "Egyszerű fesztivál" }
    { group:58, id:32, text: "Fényűző fesztivál" }
    { group:58, id:33, text: "Nagy fesztivál" }
    { group:58, id:34, text: "Fesztivál előkészítése: " }
    { group:58, id:35, text: "Nincs" }
    { group:58, id:36, text: "Ritka" }
    { group:58, id:37, text: "Nagyon gyenge" }
    { group:58, id:38, text: "Gyenge" }
    { group:58, id:39, text: "Átlag alatti" }
    { group:58, id:40, text: "Átlagos" }
    { group:58, id:41, text: "Átlagos" }
    { group:58, id:42, text: "Átlag feletti" }
    { group:58, id:43, text: "Jó" }
    { group:58, id:44, text: "Nagyon jó" }
    { group:58, id:45, text: "Kiváló" }
    { group:58, id:46, text: "Tökéletes" }
    { group:58, id:47, text: "Zsonglőrök színpadai" }
    { group:58, id:48, text: "Zenészek színpadai" }
    { group:58, id:49, text: "Táncosok színpadai" }
    { group:58, id:50, text: "Szenetházak " }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Fesztivál elrendelése" }
    { group:58, id:53, text: "Fesztiválrendelés: " }
    { group:58, id:54, text: "következő hónap" }
    { group:58, id:55, text: "Színpadok" }
    { group:58, id:56, text: "Állatkertek" }

    { group:59, id:0, text: "Templomok felügyelője" }
    { group:59, id:1, text: "Templomok" }
    { group:59, id:2, text: "Templomkomplexumok" }
    { group:59, id:3, text: "Megbékítés" }
    { group:59, id:4, text: "N/A" }
    { group:59, id:5, text: "Templom" }
    { group:59, id:6, text: "Hónapok" }
    { group:59, id:7, text: "Fesztivál" }
    { group:59, id:8, text: "óta" }
    { group:59, id:9, text: "A lakosok kezdenek spirituális igényeket támasztani. A közeli imahelyek hiánya visszafogja a város fejlődését." }
    { group:59, id:10, text: "Egyre többen tartanak attól, hogy ha legalább egy imahely nincs a környékükön, az istenek megsértve érzik magukat." }
    { group:59, id:11, text: "A kifinomultabb lakosok egy másik vallás közeli elérhetőségét szeretnék. A vallási sokszínűség hiánya korlátozza a város fejlődését bizonyos területeken." }
    { group:59, id:12, text: "Az igényes polgárok szerint környékük jobb osztályú írnokokat vonzana, ha könnyen hozzáférnének egy harmadik valláshoz." }
    { group:59, id:13, text: "Eddig az embereket túlságosan lefoglalták a fizikai szükségletek ahhoz, hogy a vallással foglalkozzanak. Ahogy azonban a város növekszik, könnyen elérhető különféle templomokat fognak igényelni." }
    { group:59, id:14, text: "Mindenki vallási igényeit kielégítik, és a papok szerint az istenek elégedettek a város vallásosságával." }
    { group:59, id:15, text: "Ozirisz elégedetlensége veszélyes. Elpusztíthatja terményeidet és kiürítheti magtáraidat, vagy akár visszatarthatja az áradást is." }
    { group:59, id:16, text: "Amikor a hatalmas Ré, a fáraó atyja elégedetlenné válik, városod szomszédait is arra készteti, hogy osztozzanak érzéseiben. Ré haragja veszélyezteti a birodalommal való harmóniát." }
    { group:59, id:17, text: "Ptah, a kézművesek pártfogó istene, akinek jóindulatára gyártóidnak szüksége van, elégedetlenné válik. Nyerj vissza a kegyét, vagy készülj fel egész iparágak és termékek elvesztésére." }
    { group:59, id:18, text: "A legbátrabb katonák is remegnek Széth haragja előtt. Állítsd helyre az isten véleményét városodról gyorsan, különben zászlóaljadat elsöpri!" }
    { group:59, id:19, text: "Amikor a jóságos Bászt megsértődik, az emberek saját otthonaikban sincsenek biztonságban. Engeszteld ki gyorsan az istennőt, különben pusztulás és járvány következik!" }
    { group:59, id:20, text: "Dühöngő" }
    { group:59, id:21, text: "Őrjöngő" }
    { group:59, id:22, text: "Mérges" }
    { group:59, id:23, text: "Neheztelő" }
    { group:59, id:24, text: "Elégedetlen" }
    { group:59, id:25, text: "Közömbös" }
    { group:59, id:26, text: "Barátságos" }
    { group:59, id:27, text: "Kedvező" }
    { group:59, id:28, text: "Együttérző" }
    { group:59, id:29, text: "Helyeslő" }
    { group:59, id:30, text: "Jóindulatú" }
    { group:59, id:31, text: "nem használt - isten kapcsoló volt" }
    { group:59, id:32, text: "Ozirisz a Nílus áradásának és az alvilágból fakadó minden életnek az istene. Jóindulatával városod részesülhet a bőséges évi áradás áldásában, amely éltető termékeny talajt hoz a földjeidre. Más módokon is javíthatja a betakarítás hozamát. Szebek oltára – a termékenység istene – lehetővé teszi, hogy Ozirisz papjai segítsenek polgáraidnak egy kicsit tovább beosztani élelmüket és egyéb készleteiket, míg Min jóslata – az újjászületés istenéé – nagyobb életerővel tölti fel a városod körüli élővilágot. Jóslata ellenállóbbá teszi az állatcsordákat és haltelepeket, sőt egyes növények újranövését is felgyorsítja." }
    { group:59, id:33, text: "Ré, a Királyság istene megkönnyíti a kereskedelmet és az utazást az ismert világban, sőt még egyiptomi hírnevedet is erősítheti. Ma'at oltára – az igazság istennőjéé – segít megelőzni a bűnözést városodban, míg Hórusz jóslata – a fáraó istenéé – készségesebbé teszi dolgozóidat mindennapi munkájuk elvégzésében. A fáraó nevében arra ösztönzi őket, hogy Egyiptom nagyobb javáért dolgozzanak." }
    { group:59, id:34, text: "Ptah a kézművesek védőistene, és sokuknak segít gyorsabban befejezni feladataikat. Amon oltára – a Nap istenéé – javítja városod emlékműépítési képességét, míg Thot jóslata – a bölcsesség és tanulás istenéé – elősegítheti néped oktatását." }
    { group:59, id:35, text: "Ha Szet kegyében részesül, ellenségeid az ő ellenségeivé válnak. Segíthet a legtapasztalatlanabb katonáidnak is úgy harcolni, mint a veteránok, és akár saját kezével is lesújthat ellenségeidre. Olyan hatalmas az ereje, hogy befolyása még a távoli vidékeken vívott csatákra is kiterjed. Természetesen, ha Szet nincs kiengesztelve, városod első kézből tapasztalhatja meg pusztító erejének teljes hatalmát." }
    { group:59, id:36, text: "Básztet az otthon istennőjeként javíthatja városod életminőségét, és lehetővé teszi polgáraid számára, hogy sokkal magasabb életszínvonalat élvezzenek, mint ami egyébként lehetséges lenne. Ereje olyan nagy, hogy még a többi istent is segíthet boldogan tartani. Természetesen, ha nincs kiengesztelve, városod valódi nyomort és szenvedést fog megismerni. Ízisz oltára – a gyógyítás istennőjéé – segít biztosítani, hogy polgáraid jó egészségnek örvendjenek, és még akkor is támogatja őket, ha megbetegszenek, míg Hathor jóslata – az öröm, szeretet és ünneplés istennőjéé – segít népednek valamivel boldogabbnak maradni a nehézségek ellenére is." }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Papnő" }
    { group:60, id:0, text: "A kincstár felügyelője" }
    { group:60, id:1, text: "Adókulcs:" }
    { group:60, id:2, text: "A városi kincstár vagyona:" }
    { group:60, id:3, text: "A város adóssága:" }
    { group:60, id:4, text: "várható hozama:" }
    { group:60, id:5, text: "az adónyilvántartásban szereplő lakosság" }
    { group:60, id:6, text: "Tavaly" }
    { group:60, id:7, text: "Idén eddig" }
    { group:60, id:8, text: "Adók innen:" }
    { group:60, id:9, text: "Az export bevétele:" }
    { group:60, id:10, text: "Bevétel" }
    { group:60, id:11, text: "Az import költsége:" }
    { group:60, id:12, text: "Bérek" }
    { group:60, id:13, text: "Építkezés" }
    { group:60, id:14, text: "Kamat:" }
    { group:60, id:15, text: "Személyes fizetés" }
    { group:60, id:16, text: "Lopás" }
    { group:60, id:17, text: "Kiadások" }
    { group:60, id:18, text: "Nettó be-/kiáramlás" }
    { group:60, id:19, text: "Egyenleg" }
    { group:60, id:20, text: "Ajándékok" }
    { group:60, id:21, text: "Adó" }
    { group:60, id:22, text: "Kérések és ünnepségek" }
    { group:60, id:23, text: "idén be nem szedve" }
    { group:60, id:24, text: "Bányászott arany" }
    { group:61, id:13, text: "Sokkal többet termelünk, mint amennyit elfogyasztunk" }
    { group:61, id:14, text: "Kicsivel többet termelünk, mint amennyit elfogyasztunk" }
    { group:61, id:15, text: "Pontosan elég élelmet termelünk mindenki ellátásához" }
    { group:61, id:16, text: "FONTOS: Kicsivel többet fogyasztunk, mint amennyit termelünk" }
    { group:61, id:17, text: "SÚLYOS: Többet fogyasztunk, mint amennyit termelünk" }
    { group:61, id:18, text: "SÜRGŐS: Sokkal többet fogyasztunk, mint amennyit termelünk" }
    { group:61, id:19, text: "NEM HASZNÁLT 2426" }
    { group:61, id:20, text: "Mindenki gyűlöl téged" }
    { group:61, id:21, text: "Az emberek nagyon haragszanak rád" }
    { group:61, id:22, text: "Az emberek haragszanak rád" }
    { group:61, id:23, text: "Az emberek nagyon elégedetlenek veled" }
    { group:61, id:24, text: "Az emberek elégedetlenek veled" }
    { group:61, id:25, text: "Az embereket bosszantod" }
    { group:61, id:26, text: "Az emberek közömbösek irántad" }
    { group:61, id:27, text: "Az emberek elégedettek veled." }
    { group:61, id:28, text: "Az emberek nagyon elégedettek veled." }
    { group:61, id:29, text: "Az emberek rendkívül elégedettek veled." }
    { group:61, id:30, text: "Az emberek szeretnek téged." }
    { group:61, id:31, text: "Az emberek istenként tisztelnek téged." }
    { group:61, id:32, text: "az élelmiszerhiány miatt." }
    { group:61, id:33, text: "a munkahelyhiány miatt." }
    { group:61, id:34, text: "a magas adók miatt." }
    { group:61, id:35, text: "az alacsony bérek miatt." }
    { group:61, id:36, text: "a sok nyomornegyed miatt." }
    { group:61, id:37, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. A város élelmiszerhiánya az elégedetlenség legfőbb oka, de a magas adók, az alacsony bérek, a társadalmi egyenlőtlenség és a munkahelyek hiánya szintén ronthatják a városi közhangulatot." }
    { group:61, id:38, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. A munkahelyek hiánya minden másnál jobban bosszantja az embereket, de a magas adók, az alacsony bérek, a társadalmi egyenlőtlenség és az élelmiszerhiány szintén ronthatják a városi közhangulatot." }
    { group:61, id:39, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. A polgáraidat leginkább a magas adók aggasztják, de az alacsony bérek, a társadalmi egyenlőtlenség, valamint az élelmiszer- és munkahelyhiány is ronthatja a városi közhangulatot." }
    { group:61, id:40, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. Legnagyobb panaszuk a csekély fizetésük (más egyiptomi munkások béreihez képest), de a magas adók, a társadalmi egyenlőtlenség, valamint az élelmiszer- és munkahelyhiány is ronthatják a városi közhangulatot." }
    { group:61, id:41, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. Az embereket leginkább a széles körű társadalmi egyenlőtlenség dühíti, de a magas adók, az alacsony bérek, valamint az élelmiszer- és munkahelyhiány is ronthatja a városi közhangulatot." }
    { group:61, id:42, text: "Az alacsony városi közhangulat növeli a bűnözést, megakadályozza, hogy telepesek érkezzenek a városodba, és akár arra is késztetheti jelenlegi polgáraidat, hogy elköltözzenek. Az alacsony bérek, a magas adók, a társadalmi egyenlőtlenség, valamint az élelmiszer- és munkahelyhiány mind hozzájárulnak az alacsony városi közhangulathoz." }
    { group:61, id:43, text: "A háború elriasztja a bevándorlókat!" }
    { group:61, id:44, text: "Emberek települnek be a városba" }
    { group:61, id:45, text: "A lakáshiány akadályozza a bevándorlást" }
    { group:61, id:46, text: "Az alacsony bérek akadályozzák a bevándorlást" }
    { group:61, id:47, text: "A munkahelyhiány akadályozza a bevándorlást" }
    { group:61, id:48, text: "Az élelmiszerhiány akadályozza a bevándorlást" }
    { group:61, id:49, text: "A magas adók akadályozzák a bevándorlást" }
    { group:61, id:50, text: "A város nyomornegyedei elriasztják a bevándorlókat" }
    { group:61, id:51, text: "A rossz városi közhangulat akadályozza a bevándorlást" }
    { group:61, id:52, text: "Az üres lakóhelyek hiánya elűzi az embereket" }
    { group:61, id:53, text: "Az alacsony bérek miatt emberek hagyják el a várost" }
    { group:61, id:54, text: "A munkanélküliség miatt emberek hagyják el a várost" }
    { group:61, id:55, text: "A távozók az éhezést nevezik meg okként" }
    { group:61, id:56, text: "A tisztességtelen vagy túl magas adózás elűzi az embereket" }
    { group:61, id:57, text: "A nyomornegyedek megléte távozásra ösztönöz embereket" }
    { group:61, id:58, text: "Az emberek a rossz városi közhangulat miatt távoznak" }
    { group:61, id:59, text: "Kevés változás várható" }
    { group:61, id:60, text: "Amíg van szabad lakóhely, és a városod lakói elégedettek veled, újabb emberek fognak a városodba költözni. Építs több lakónegyedet, hogy a városod növekedhessen és virágozhasson." }
    { group:61, id:61, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni. Emeld a béreket, ha több embert szeretnél a városba csábítani." }
    { group:61, id:62, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni. Hozz létre új munkahelyeket további iparágak építésével, ha több embert szeretnél a városba vonzani." }
    { group:61, id:63, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni. Termelj több élelmiszert a jelenleginél, ha több embert szeretnél a városba vonzani." }
    { group:61, id:64, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni. Az alacsonyabb adók több embert vonzanának a városba." }
    { group:61, id:65, text: "Általában érdemes növelned a lakosságot, hogy a városod növekedhessen és virágozhasson. Az új telepeseket a szabad lakóhelyek és a magasabb városi elégedettség vonzza." }
    { group:61, id:66, text: "Általában érdemes növelned a lakosságot, hogy a városod növekedhessen és virágozhasson. Mivel van szabad lakóhely, és az embereid elégedettek az itteni életükkel, az új telepesek tömegesen érkeznek a városba." }
    { group:61, id:67, text: "Ha túl nagy a különbség a tehetősek és a nélkülözők között, senki sem akar majd a városodba költözni. Biztosíts jobb szolgáltatásokat a szegényebb városrészekben, hogy nagyobb egyensúlyt teremts a gazdagok és a szerényebb körülmények között élők között." }
    { group:61, id:68, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni. Növeld a városi elégedettséget, hogy több embert vonzz a városba." }
    { group:61, id:69, text: "Amíg elegendő lakóhely áll rendelkezésre, és a városod lakói elégedettek, újabb emberek fognak a városodba költözni (és a saját polgáraid sem távoznak majd jobb lehetőségeket keresve!). Építs több lakóhelyet, hogy a városod növekedhessen és virágozhasson." }
    { group:61, id:70, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, a városodban maradnak. Emeld a béreket, ha arra szeretnéd ösztönözni az embereket, hogy maradjanak." }
    { group:61, id:71, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, a városodban maradnak. Hozz létre több munkahelyet újabb iparágak építésével, ha arra szeretnéd ösztönözni az embereket, hogy maradjanak." }
    { group:61, id:72, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, a városodban maradnak. A jelenlegi népességed mérete alapján több élelmiszert kell termelned a jelenleginél, ha arra szeretnéd ösztönözni az embereket, hogy maradjanak." }
    { group:61, id:73, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, a városodban maradnak. Az alacsonyabb adók arra ösztönzik az embereket, hogy maradjanak." }
    { group:61, id:74, text: "Ha túl nagy a különbség a tehetősek és a nélkülözők között, az emberek hajlamosak máshol keresni lehetőségeket. Biztosíts jobb szolgáltatásokat a szegényebb városrészekben, hogy nagyobb egyensúlyt teremts a gazdagok és a szerényebb körülmények között élők között." }
    { group:61, id:75, text: "Amíg a városod lakói elégedettek veled, és elegendő lakóhely áll rendelkezésre, újabb emberek fognak a városodba költözni (és a saját polgáraid sem távoznak majd jobb lehetőségeket keresve!). Növelned kell a városi elégedettséget, ha azt szeretnéd, hogy az emberek itt maradjanak." }
    { group:61, id:76, text: "SÜRGŐS:   A város munkanélkülisége" }
    { group:61, id:77, text: "SÚLYOS:  A város munkanélkülisége" }
    { group:61, id:78, text: "FONTOS: A város munkanélkülisége" }
    { group:61, id:79, text: "A város munkanélkülisége" }
    { group:61, id:80, text: "SÜRGŐS:   A város hiánya" }
    { group:61, id:81, text: "SÚLYOS:  A város hiánya" }
    { group:61, id:82, text: "FONTOS: A város hiánya" }
    { group:61, id:83, text: "A város hiánya" }
    { group:61, id:84, text: "A városnak nincs foglalkoztatási problémája" }
    { group:61, id:85, text: "A magas munkanélküliség miatt az embereid máshol kereshetnek munkát. Építs több ipart új munkahelyek létrehozásához." }
    { group:61, id:86, text: "A magas munkanélküliség miatt az embereid máshol kereshetnek munkát. További iparágak építésével új munkahelyeket teremthetsz." }
    { group:61, id:87, text: "A magas munkanélküliség miatt az embereid máshol kereshetnek munkát. További iparágak építésével új munkahelyeket teremthetsz." }
    { group:61, id:88, text: "Ez a munkanélküliségi szint még elfogadható, de ha túl magasra emelkedik, az embereid máshol kereshetnek munkát. További iparágak építésével új munkahelyeket teremthetsz." }
    { group:61, id:89, text: "Az ilyen súlyos munkaerőhiány teljesen megbénítja a városodat. Állíts le minden felesleges iparágat, vagy vonzz több dolgozót szabad lakóhelyekkel és elégedett lakossággal." }
    { group:61, id:90, text: "A súlyos munkaerőhiány megakadályozza, hogy polgáraid ellássák mindennapi feladataikat. Állíts le minden felesleges iparágat, vagy vonzz több dolgozót szabad lakóhelyekkel és elégedett lakossággal." }
    { group:61, id:91, text: "Elegendő dolgozó nélkül polgáraid nehezen tudják elvégezni mindennapi feladataikat." }
    { group:61, id:92, text: "A munkaerőhiány az áruk és szolgáltatások csökkenéséhez vezethet az egész városban. Tedd hatékonyabbá a városodat a felesleges iparágak leállításával, vagy több dolgozó vonzásával szabad lakóhelyekkel és elégedett lakossággal." }
    { group:61, id:93, text: "A magas munkanélküliség miatt az egyébként elégedett polgáraid is elhagyhatják a várost munkát keresve, míg a munkaerőhiány az áruk és szolgáltatások csökkenéséhez vezethet az egész városban." }
    { group:61, id:94, text: "A főváros minden szükségletünket biztosítja" }
    { group:61, id:95, text: "SÜRGŐS:    Élelmiszerkészleteink alacsonyak" }
    { group:61, id:96, text: "SÚLYOS:   Élelmiszerkészleteink alacsonyak" }
    { group:61, id:97, text: "FONTOS: Élelmiszerkészleteink alacsonyak" }
    { group:61, id:98, text: "Készletek ehhez:" }
    { group:61, id:99, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Ügyelj arra, hogy az embereid ne fogyasszanak többet annál, mint amennyit termelsz, és hogy elegendő magtárad legyen a betakarított termények tárolására." }
    { group:61, id:100, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Ügyelj arra, hogy az embereid ne fogyasszanak többet annál, mint amennyit termelsz, és hogy elegendő magtárad legyen a betakarított termények tárolására." }
    { group:61, id:101, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Ügyelj arra, hogy az embereid ne fogyasszanak többet annál, mint amennyit termelsz, és hogy elegendő magtárad legyen a betakarított termények tárolására." }
    { group:61, id:102, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Ügyelj arra, hogy az embereid ne fogyasszanak többet annál, mint amennyit termelsz, és hogy elegendő magtárad legyen a betakarított termények tárolására." }
    { group:61, id:103, text: "SÜRGŐS: A város egészségi állapota borzalmas – járvány kitörése várható." }
    { group:61, id:104, text: "SÜRGŐS: A város egészségi állapota rettenetes – járvány valószínű." }
    { group:61, id:105, text: "SÚLYOS: A város egészségi állapota rossz – fennáll a járvány veszélye." }
    { group:61, id:106, text: "FONTOS: A város egészségi állapota gyenge – némi járványveszély áll fenn." }
    { group:61, id:107, text: "A város egészségi állapota átlag alatti." }
    { group:61, id:108, text: "A város egészségi állapota átlagos." }
    { group:61, id:109, text: "A város egészségi állapota jó." }
    { group:61, id:110, text: "A város egészségi állapota nagyon jó." }
    { group:61, id:111, text: "A város egészségi állapota kiváló." }
    { group:61, id:112, text: "A város egészségi állapota majdnem tökéletes." }
    { group:61, id:113, text: "A város egészségi állapota tökéletes." }
    { group:61, id:114, text: "Ennyi rossz egészségi állapotú ember mellett szinte biztos, hogy egy széles körű járvány pusztítja majd a várost. Építs orvosi rendelőket és halottasházakat azok számára, akik jelenleg nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:115, text: "Ennyi beteg ember mellett hamarosan valószínűleg széles körű járvány tör ki, amely elpusztíthatja a város lakosságának nagy részét. Építs orvosi rendelőket és halottasházakat azok számára, akik jelenleg nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:116, text: "Ennyi beteg ember mellett a városban a patikusoknak és orvosoknak nehéz lépést tartaniuk. A várost egy pusztító járvány veszélye fenyegeti, amely megtizedelheti a lakosságot. Építs orvosi rendelőket és halottasházakat azok számára, akik jelenleg nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:117, text: "Ennyi beteg ember mellett a városban a patikusoknak és orvosoknak nehéz lépést tartaniuk. A várost járvány sújthatja, amely elpusztíthatja a lakosság nagy részét. Építs orvosi rendelőket és halottasházakat azok számára, akik jelenleg nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:118, text: "Ha a lakosság egészségi állapota tovább romlik, a várost pusztító járvány sújthatja. Építs orvosi rendelőket és halottasházakat azoknak a szerencsétleneknek, akik jelenleg nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:119, text: "Ha a lakosság egészségi állapota tovább romlik, a várost járvány sújthatja, amely megtizedelheti a lakosságot. Építs orvosi rendelőket és halottasházakat azoknak a szerencsétleneknek, akik nem férnek hozzá az orvosok és balzsamozók által nyújtott szolgáltatásokhoz, valamint gondoskodj róla, hogy polgáraidnak elegendő élelmiszer álljon rendelkezésére." }
    { group:61, id:120, text: "A jó egészség fontos a malária és a betegségek visszaszorításához, különösen pedig a várost sújtó járványok megelőzéséhez. Ha a lakosság egészségi állapota romlik, a várost pusztító járvány sújthatja. Az orvosi rendelők és halottasházak által biztosított orvosok és balzsamozók segítenek egészségesen tartani a várost, ahogy a többféle élelmiszerből álló megfelelő készlet is." }
    { group:61, id:121, text: "A jó egészség fontos a malária és a betegségek visszaszorításához, különösen pedig a várost sújtó járványok megelőzéséhez. Ha a lakosság egészségi állapota romlik, a várost pusztító járvány sújthatja. Az orvosi rendelők és halottasházak által biztosított orvosok és balzsamozók segítenek egészségesen tartani a várost, ahogy a többféle élelmiszerből álló megfelelő készlet is." }
    { group:61, id:122, text: "A jó egészség fontos a malária és a betegségek visszaszorításához, különösen pedig a várost sújtó járványok megelőzéséhez. Ha a lakosság egészségi állapota romlik, a várost pusztító járvány sújthatja. Az orvosi rendelők és halottasházak által biztosított orvosok és balzsamozók segítenek egészségesen tartani a várost, ahogy a többféle élelmiszerből álló megfelelő készlet is." }
    { group:61, id:123, text: "A jó egészség fontos a malária és a betegségek visszaszorításához, különösen pedig a várost sújtó járványok megelőzéséhez. Ha a lakosság egészségi állapota romlik, a várost pusztító járvány sújthatja. Az orvosi rendelők és halottasházak által biztosított orvosok és balzsamozók segítenek egészségesen tartani a várost, ahogy a többféle élelmiszerből álló megfelelő készlet is." }
    { group:61, id:124, text: "A jó egészség fontos a malária és a betegségek visszaszorításához, különösen pedig a várost sújtó járványok megelőzéséhez. Ha a lakosság egészségi állapota romlik, a várost pusztító járvány sújthatja. Az orvosi rendelők és halottasházak által biztosított orvosok és balzsamozók segítenek egészségesen tartani a várost, ahogy a többféle élelmiszerből álló megfelelő készlet is." }
    { group:61, id:125, text: "FONTOS: Több istenség nincs kiengesztelve" }
    { group:61, id:126, text: "SÚLYOS: Több istenség is lesújthat ránk" }
    { group:61, id:127, text: "FONTOS: Három istenség nincs kiengesztelve" }
    { group:61, id:128, text: "SÚLYOS: Három istenség nincs kiengesztelve" }
    { group:61, id:129, text: "FONTOS: Két istenség nincs kiengesztelve" }
    { group:61, id:130, text: "SÚLYOS: Két istenség nincs kiengesztelve" }
    { group:61, id:131, text: "FONTOS: Egy istenség nincs kiengesztelve" }
    { group:61, id:132, text: "SÚLYOS: Egy istenség nincs kiengesztelve" }
    { group:61, id:133, text: "Minden istenség kellően ki van engesztelve" }
    { group:61, id:134, text: "Minden istenség ki van engesztelve. Egyikük különösen elégedett" }
    { group:61, id:135, text: "Minden istenség ki van engesztelve. Kettőjük különösen elégedett" }
    { group:61, id:136, text: "Minden istenség ki van engesztelve. Hármuk különösen elégedett" }
    { group:61, id:137, text: "Minden istenség ki van engesztelve. Többük különösen elégedett" }
    { group:61, id:138, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:139, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:140, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:141, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:142, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:143, text: "Az ellenséges istenségek erejükkel elpusztíthatják a városodat. Engeszteld ki őket templomok építésével és tiszteletükre rendezett ünnepségekkel." }
    { group:61, id:144, text: "Egy haragos istenség erejével elpusztíthatja a városodat. Engeszteld ki őt templomok építésével és tiszteletére rendezett ünnepségekkel." }
    { group:61, id:145, text: "Egy haragos istenség erejével elpusztíthatja a városodat. Engeszteld ki őt templomok építésével és tiszteletére rendezett ünnepségekkel." }
    { group:61, id:146, text: "Ha bármelyik istenség ellenségessé válik, erejével elpusztíthatja a városodat." }
    { group:61, id:147, text: "A jóindulatú istenségek többféleképpen is megáldhatják a városodat erejükkel. Ahogy a városod növekszik, tartsd kiengesztelve az istenségeket a nekik szentelt templomokkal, és továbbra is rendezz a tiszteletükre ünnepségeket." }
    { group:61, id:148, text: "A jóindulatú istenségek többféleképpen is megáldhatják a városodat erejükkel. Ahogy a városod növekszik, tartsd kiengesztelve az istenségeket a nekik szentelt templomokkal, és továbbra is rendezz a tiszteletükre ünnepségeket." }
    { group:61, id:149, text: "A jóindulatú istenségek többféleképpen is megáldhatják a városodat erejükkel. Ahogy a városod növekszik, tartsd kiengesztelve az istenségeket a nekik szentelt templomokkal, és továbbra is rendezz a tiszteletükre ünnepségeket." }
    { group:61, id:150, text: "A jóindulatú istenségek többféleképpen is megáldhatják a városodat erejükkel. Ahogy a városod növekszik, tartsd kiengesztelve az istenségeket a nekik szentelt templomokkal, és továbbra is rendezz a tiszteletükre ünnepségeket." }
    { group:61, id:151, text: "SÚLYOS: Nem hajtjuk be az esedékes adók nagy részét!" }
    { group:61, id:152, text: "Ebben az évben a vagyonunk ennyivel nőtt: " }
    { group:61, id:153, text: "Nagyjából ugyanolyan jól teljesítünk, mint tavaly." }
    { group:61, id:154, text: "Ebben az évben a vagyonunk ennyivel csökkent: " }
    { group:61, id:155, text: "Jelentős mennyiségű pénzről mondasz le, mert a városodban nincs elegendő adószedő, aki járná az utcákat. Építs több adószedő-állomást, különösen a magasabb szintű lakónegyedekben, és használd az adózási nézetet annak ellenőrzésére, hogy mindenkit felkeressen egy adószedő." }
    { group:61, id:156, text: "Ha elfogy a pénzed, a kincstárad legfeljebb 5000 deben kölcsönt vehet fel. A hosszú ideig fennálló adósságnak azonban nagyon súlyos következményei vannak. Az adók, az export és az aranybányászat a város bevételeinek legjobb forrásai. További információért kattints a menüsávon a „Segítség” gombra, majd válaszd az „Adósság” lehetőséget." }
    { group:61, id:157, text: "Ha elfogy a pénzed, a kincstárad legfeljebb 5000 deben kölcsönt vehet fel. A hosszú ideig fennálló adósságnak azonban nagyon súlyos következményei vannak. Az adók, az export és az aranybányászat a város bevételeinek legjobb forrásai. További információért kattints a menüsávon a „Segítség” gombra, majd válaszd az „Adósság” lehetőséget." }
    { group:61, id:158, text: "Ha továbbra is veszteségesen működsz, igénybe kell venned a hitelkeretedet. A város kincstára legfeljebb 5000 deben kölcsönt vehet fel, de a túl hosszú ideig fennálló adósságnak súlyos következményei vannak. Az adók, az export és az aranybányászat a város bevételeinek legjobb forrásai. További információért kattints a menüsávon a „Segítség” gombra, majd válaszd az „Adósság” lehetőséget." }
    { group:61, id:159, text: "SÜRGŐS: Sok közelmúltbeli lopás," }
    { group:61, id:160, text: "SÚLYOS: Több közelmúltbeli lopás," }
    { group:61, id:161, text: "FONTOS: Néhány közelmúltbeli lopás," }
    { group:61, id:162, text: "Nagyon kevés lopás." }
    { group:61, id:163, text: "Nem jelentettek lopást" }
    { group:61, id:164, text: "deben ellopva." }
    { group:61, id:165, text: "Ennyi lopás komolyan megcsapolhatja a városod kincstárát, sőt akár a saját családi megtakarításaidat is! Megfelelő számú bíróság és rendőrőrs segít megelőzni a bűnözést, a rendfenntartók pedig elfogják a tolvajokat, akikkel találkoznak. Az embereid elégedettségének fenntartása a legjobb módja annak, hogy eleve elkerüld a bűnözést." }
    { group:61, id:166, text: "A gyakori lopások kimeríthetik a városod kincstárát, sőt akár a saját családi megtakarításaidat is! A megfelelő számú bíróság és rendőrőrs segít megelőzni a bűnözést, a rendfenntartók pedig elfogják a tolvajokat, akikkel találkoznak. Természetesen az embereid elégedettségének fenntartása a legjobb módja annak, hogy eleve elkerüld a bűnözést." }
    { group:61, id:167, text: "A gyakori lopások gyengíthetik a városod pénzügyeit, sőt akár a saját családod megtakarításait is! A megfelelő számú bíróság és rendőrőrs segít megelőzni a bűnözést, a rendfenntartók pedig elfogják a tolvajokat, akikkel találkoznak. Természetesen az embereid elégedettségének fenntartása a legjobb módja annak, hogy eleve elkerüld a bűnözést." }
    { group:61, id:168, text: "A gyakori lopások gyengíthetik a városod pénzügyeit, sőt akár a saját családod megtakarításait is! A megfelelő számú bíróság és rendőrőrs segít megelőzni a bűnözést, a rendfenntartók pedig elfogják a tolvajokat, akikkel találkoznak. Természetesen az embereid elégedettségének fenntartása a legjobb módja annak, hogy eleve elkerüld a bűnözést." }
    { group:61, id:169, text: "A lopások károsíthatják a városod pénzügyeit, sőt akár a családod megtakarításait is! Megfelelő számú bíróság és rendőrőrs segít megelőzni a bűnözést, a rendfenntartók pedig elfogják a tolvajokat, akikkel találkoznak. Természetesen az embereid elégedettségének fenntartása a legjobb módja annak, hogy eleve ne forduljanak a bűnözéshez." }
    { group:61, id:170, text: "Nincs irányítható egységünk" }
    { group:61, id:171, text: "Nincs jelentett fenyegetés" }
    { group:61, id:172, text: "Ellenség közeledik a városhoz" }
    { group:61, id:173, text: "Az ellenség támadja a várost" }
    { group:61, id:174, text: "Ellenséges csapatok állnak a kapuinknál" }
    { group:61, id:175, text: "Csapatainkra máshol van szükség" }
    { group:61, id:176, text: "Csapataink máshol szolgálnak" }
    { group:61, id:177, text: "Nem rendelkezünk katonai erőkkel. Jelenleg nincs rájuk szükség, mivel minden biztonságos." }
    { group:61, id:178, text: "Ha ellenség közeledne a városunkhoz, biztosan üzenetet kapnál róla. Az ellenséges seregek a világtérképen is megjelennek, így figyelheted az előrenyomulásukat, és remélhetőleg felkészítheted a várost az érkezésükre." }
    { group:61, id:179, text: "Egy ellenséges sereg közeledik, hogy megtámadja a várost! Támadás alatt nehéz vagy akár lehetetlen is lehet épületeket építeni, ezért készítsd elő a védelmet most, amíg még lehet: építs falakat, tornyokat, kapuházakat és erődöket." }
    { group:61, id:180, text: "Mindig jobb felkészülni a támadásokra, mint az utolsó pillanatban megpróbálni katonákat toborozni. Remélhetőleg megfelelő védelemmel rendelkezünk a város megóvásához." }
    { group:61, id:181, text: "Mindig jobb felkészülni a támadásokra, mint az utolsó pillanatban megpróbálni katonákat toborozni. Remélhetőleg megfelelő védelemmel rendelkezünk a város megóvásához." }
    { group:61, id:182, text: "Egyiptomi parancsnoktársunktól csapatokat kérő üzenetet kaptunk. Általában érdemes eleget tenni az ilyen kéréseknek, ha jó kapcsolatban szeretnél maradni a Királyság többi részével. A csapatok elküldéséhez keresd fel a Politikai felügyelőt és a Katonai felügyelőt." }
    { group:61, id:183, text: "Néhány csapatunk távoli hadjáratokban szolgálja Egyiptomot. Általában jó dolog támogatni a Királyságot azzal, hogy szükség esetén csapatokat küldesz, ha meg akarod őrizni jó hírnevedet egész Egyiptomban." }
    { group:61, id:184, text: "Városunkkal szemben sok teljesítetlen kérés van." }
    { group:61, id:185, text: "Városunkkal szemben több teljesítetlen kérés van." }
    { group:61, id:186, text: "Városunkkal szemben néhány teljesítetlen kérés van." }
    { group:61, id:187, text: "Városunkkal szemben nincs teljesítetlen kérés." }
    { group:61, id:188, text: "A fáraó vagy szomszédaid kéréseinek elmulasztása különféle hátrányos következményekkel járhat. Ha nem segítesz egyiptomi várostársaidnak szükség idején, szegénységbe süllyedhetnek, vagy ellenségeink kezére kerülhetnek. Ha jó kapcsolatban szeretnél maradni honfitársaiddal, az ilyen kérésekre készségesen és gyorsan válaszolj." }
    { group:61, id:189, text: "A fáraó vagy szomszédaid kéréseinek elmulasztása különféle hátrányos következményekkel járhat. Ha nem segítesz egyiptomi várostársaidnak szükség idején, szegénységbe süllyedhetnek, vagy ellenségeink kezére kerülhetnek. Ha jó kapcsolatban szeretnél maradni honfitársaiddal, az ilyen kérésekre készségesen és gyorsan válaszolj." }
    { group:61, id:190, text: "Ha nem segítesz egyiptomi várostársaidnak szükség idején, szegénységbe süllyedhetnek, ellenségeik kezére kerülhetnek, vagy más kellemetlen sorsra juthatnak. Ez kedvezőtlenül befolyásolhatja a kereskedelmet, az árakat, sőt még a Királyságban elfoglalt helyzetedet is. Ha jó kapcsolatban szeretnél maradni honfitársaiddal, a legjobb, ha készségesen és gyorsan teljesíted a kéréseket." }
    { group:61, id:191, text: "Ha jó kapcsolatban szeretnél maradni honfitársaiddal, készségesen és gyorsan válaszolj minden szükség idején érkező kérésükre. Ha nem segítesz, szegénységbe süllyedhetnek, ellenségeik kezére kerülhetnek, vagy más kellemetlen sorsra juthatnak. Ez káros hatással lehet a kereskedelemre, az árakra, sőt még a Királyságban elfoglalt helyzetedre is." }
    { group:61, id:192, text: "A következő áradás valószínűleg teljes kudarc lesz" }
    { group:61, id:193, text: "A következő áradás valószínűleg gyenge lesz" }
    { group:61, id:194, text: "A következő áradás valószínűleg közepes lesz" }
    { group:61, id:195, text: "A következő áradás várhatóan jó lesz" }
    { group:61, id:196, text: "A következő áradás várhatóan kiváló lesz" }
    { group:61, id:197, text: "A következő áradás várhatóan tökéletes lesz" }
    { group:61, id:198, text: "A Nílusmérőt értelmező papok arra figyelmeztetnek, hogy az idei áradás teljes kudarcba fulladhat, és a Nílus gazdag, termékeny iszapja nem fogja megújítani a földjeidet. Ha városod az ártéri földműveléstől függ az élelmiszerellátásban, ez polgáraid túlélését is veszélybe sodorhatja. Ozirisz, a nílusi áradás istenének tisztelete segíthet elkerülni ezt jövőre." }
    { group:61, id:199, text: "A jósok gyenge áradást jósolnak erre az évre. Attól tartanak, hogy a Nílus gazdag, termékeny iszapjából csak kevés újítja meg a földjeidet. Ha városod az ártéri földműveléstől függ az élelmiszerellátásban, ez polgáraid túlélését is veszélybe sodorhatja. Ozirisz, a nílusi áradás istenének kiengesztelése segíthet elkerülni ezt jövőre." }
    { group:61, id:200, text: "A jelek közepes áradást jósolnak erre az évre. Ha igazuk lesz, a Nílus csak némi gazdag, termékeny iszapot fog lerakni a földjeidre. Ha városod az ártéri földműveléstől függ az élelmiszerellátásban, ez polgáraid túlélését is veszélybe sodorja. Ozirisz, a nílusi áradás istenének fokozott tisztelete segít biztosítani, hogy ez jövőre ne történjen meg." }
    { group:61, id:201, text: "Ha a jósok helyesen értelmezik a Nílusmérők jeleit, az idei várható jó áradás a Nílus gazdag és termékeny iszapját fogja lerakni városod földjeire. Gondoskodj róla, hogy Ozirisz, a nílusi áradás istene, kiengesztelt maradjon, különben jövőre megtagadhatja ezt az áldását." }
    { group:61, id:202, text: "Ha városod az ártéri földműveléstől függ az élelmiszerellátásban, az a gazdag és termékeny iszapmennyiség, amelyet a jelek szerint egy kiváló áradás rakhat le a földjeidre, olyan bőség, amelyet nem szabad magától értetődőnek venni. Gondoskodj róla, hogy Ozirisz, a nílusi áradás istene, elégedett maradjon, hogy újra megadhassa ezt az áldást." }
    { group:61, id:203, text: "Ha városod az ártéri földműveléstől függ az élelmiszerellátásban, az a hatalmas mennyiségű gazdag és termékeny iszap, amelyet a papok reményei szerint az idei tökéletes áradás lerak majd a földjeidre, felbecsülhetetlen kincs, amelyet nem szabad magától értetődőnek venni. Imádkozz Oziriszhez, a nílusi áradás istenéhez, hogy ez a jövőben is megtörténhessen." }
    { group:61, id:204, text: "Az áradás várhatóan június elején érkezik" }
    { group:61, id:205, text: "Az áradás várhatóan június végén érkezik" }
    { group:61, id:206, text: "Az áradás várhatóan július elején érkezik" }
    { group:61, id:207, text: "Az áradás várhatóan július végén érkezik" }
    { group:61, id:208, text: "Az áradás várhatóan augusztus elején érkezik" }
    { group:61, id:209, text: "Az áradás várhatóan augusztus végén érkezik" }
    { group:61, id:210, text: "Az áradás várhatóan szeptember elején érkezik" }
    { group:61, id:211, text: "Az áradás várhatóan szeptember végén érkezik" }
    { group:61, id:212, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Egy ekkora népesség ellátásához termelj több élelmiszert több földművesbirtok, vadászház, halászrakpart vagy marhatenyészet építésével, illetve importálj több élelmiszert. Öntözéssel is növelheted a jelenleg művelt földek terméshozamát." }
    { group:61, id:213, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Egy ekkora népesség ellátásához építs több földművesbirtokot, vadászházat vagy marhatenyészetet, illetve importálj több élelmiszert." }
    { group:61, id:214, text: "Ha polgáraid túl sokszor maradnak étel nélkül, megbetegszenek (vagy elhagyják a várost, hogy jobb életkörülményeket keressenek). Egy ekkora népesség ellátásához építs több földművesbirtokot, vadászházat vagy marhatenyészetet, illetve importálj több élelmiszert." }
    { group:61, id:215, text: "Ha polgáraid továbbra is megfelelően táplálkoznak, valószínűleg egészségesek maradnak (és nem hagyják el a várost jobb étrendet keresve). Nagyjából megfelelő arányban rendelkezel földművesbirtokokkal, marhatenyészetekkel, vadászházakkal és importált élelmiszerrel egy ekkora népesség ellátásához." }
    { group:61, id:216, text: "Ha polgáraid továbbra is jól táplálkoznak, valószínűleg egészségesek maradnak (és nem hagyják el a várost jobb étrendet keresve). Néhány földművesbirtokkal, marhatenyészettel és vadászházzal többel rendelkezel, mint amennyi egy ekkora népesség ellátásához szükséges." }
    { group:61, id:217, text: "Ha polgáraid továbbra is jól táplálkoznak, valószínűleg egészségesek maradnak (és nem hagyják el a várost jobb étrendet keresve). Sokkal több földművesbirtokkal, marhatenyészettel és vadászházzal rendelkezel, mint amennyi egy ekkora népesség ellátásához szükséges." }
    { group:61, id:218, text: "Kattints bármelyik elemre további információkért és tanácsokért" }
    { group:62, id:0, text: "Győzelem" }
    { group:62, id:1, text: "Vereség!" }
    { group:62, id:2, text: "Kattints a folytatáshoz" }
    { group:62, id:3, text: "Folytatás" }
    { group:62, id:4, text: "Kormányozz tovább még 2 évig" }
    { group:62, id:5, text: "Folytatás még 5 évig" }
    { group:62, id:6, text: "Új játék" }
    { group:62, id:7, text: "A városba" }
    { group:62, id:8, text: "Gratulálunk!" }
    { group:62, id:9, text: "nem használt 2636 (demóüzenet)" }
    { group:62, id:10, text: "Célkitűzések" }
    { group:62, id:11, text: "Népesség:" }
    { group:62, id:12, text: "Kultúra értékelése:" }
    { group:62, id:13, text: "Jólét értékelése:" }
    { group:62, id:14, text: "Emlékmű értékelése:" }
    { group:62, id:15, text: "Királyság értékelése:" }
    { group:62, id:16, text: "Milyen sötét véget ért egy ilyen fényes kezdet! Kudarccal gyalázatot hoztál Egyiptomra és őseidre, és beszennyezted még meg nem született utódaid nevét is. Csatlakozhattál volna azokhoz a kiválasztottakhoz, akik halhatatlanságot nyernek a Nádföldeken. Ehelyett siratatlanul a homályba távozol. Mások lépnek majd elő, hogy elfogadják a fáraó kihívását..." }
    { group:62, id:17, text: "Építs tűzoltóállomásokat" }
    { group:62, id:18, text: "Építs építészirodákat" }
    { group:62, id:19, text: "Építs magtárat, amelyet a vadászok megtölthetnek vadhússal" }
    { group:62, id:20, text: "Biztosíts élelmiszert a házak számára egy bazárból" }
    { group:62, id:21, text: "Hozz létre lakónegyedet, és figyeld, ahogy bevándorlók érkeznek" }
    { group:62, id:22, text: "Építs bódékat és zsonglőriskolákat a város kultúrájának növeléséhez" }
    { group:62, id:23, text: "Építs Bastetnek szentelt templomokat és szentélyeket" }
    { group:62, id:24, text: "Bányássz aranyat a palota kincstára számára" }
    { group:62, id:25, text: "Építs patikákat és orvosi rendelőket az egészség javításához" }

    { group:62, id:32, text: "Építs egy masztabát, majd tekintsd át a küldetés ismertetőjének céljait" }
    { group:62, id:34, text: "Kattints az ankh szimbólumra a küldetés céljainak áttekintéséhez" }
    { group:62, id:35, text: "Helyed a történelemben biztosított. Egyiptom népe istenné nyilvánít téged." }
    { group:62, id:36, text: "Fogadd el az isteni rangot!" }
    { group:62, id:37, text: "Küldetés újrajátszása" }
    { group:62, id:38, text: "Lejárt az idő!" }
    { group:62, id:39, text: "Elvesztetted ezt a küldetést. Csökkentheted a nehézségi szintet, hogy több időt kapj, vagy újra megpróbálhatod a küldetést." }
    { group:62, id:40, text: "Nehézség csökkentése" }
    { group:63, id:0, text: "Üzenetek" }
    { group:63, id:1, text: "Jelenleg nincs olvasatlan üzeneted. Ahogy a városod növekszik, vagy ha más városok árukat kérnek tőled, az üzenetek itt jelennek meg." }
    { group:63, id:2, text: "Dátum" }
    { group:63, id:3, text: "Tárgy" }
    { group:63, id:4, text: "Bal egérgombbal kattints egy üzenetre az elolvasásához. Jobb egérgombbal kattints egy üzenetre a törléséhez." }
    { group:63, id:5, text: "Címzett" }
    { group:63, id:6, text: "Megnyitott üzenetek törlése" }

    { group:64, id:0, text: "Senki" }
    { group:64, id:1, text: "Bevándorló" }
    { group:64, id:2, text: "Kivándorló" }
    { group:64, id:3, text: "Hajléktalan" }
    { group:64, id:4, text: "Szállító" }
    { group:64, id:5, text: "Polgár" }
    { group:64, id:6, text: "Robbanás" }
    { group:64, id:7, text: "Adószedő" }
    { group:64, id:8, text: "Építész" }
    { group:64, id:9, text: "Raktáros" }
    { group:64, id:10, text: "Tűzoltó" }
    { group:64, id:11, text: "Íjász" }
    { group:64, id:12, text: "Kocsihajtó" }
    { group:64, id:13, text: "Gyalogság" }
    { group:64, id:14, text: "Zászlóvivő" }
    { group:64, id:15, text: "Zsonglőr" }
    { group:64, id:16, text: "Zenész" }
    { group:64, id:17, text: "Táncos" }
    { group:64, id:18, text: "Szenet-játékos" }
    { group:64, id:19, text: "Kereskedőkaraván innen:" }
    { group:64, id:20, text: "Kereskedelmi hajó innen:" }
    { group:64, id:21, text: "Kereskedőkaraván innen:" }
    { group:64, id:22, text: "Tüntető" }
    { group:64, id:23, text: "Bűnöző" }
    { group:64, id:24, text: "Sírrabló" }
    { group:64, id:25, text: "Halászhajó" }
    { group:64, id:26, text: "Bazári kereskedő" }
    { group:64, id:27, text: "Pap" }
    { group:64, id:28, text: "Iskolás gyermek" }
    { group:64, id:29, text: "Tanító" }
    { group:64, id:30, text: "Könyvtáros" }
    { group:64, id:31, text: "Fogorvos" }
    { group:64, id:32, text: "Orvos" }
    { group:64, id:33, text: "Gyógyfüves" }
    { group:64, id:34, text: "Balzsamozó" }
    { group:64, id:35, text: "Munkás" }
    { group:64, id:36, text: "Térképes zászló" }
    { group:64, id:37, text: "Sodródó tárgy" }
    { group:64, id:38, text: "Rakodómunkás" }
    { group:64, id:39, text: "Bazári vásárló" }
    { group:64, id:40, text: "Írnok" }
    { group:64, id:41, text: "Őslakos (nem használt?)" }
    { group:64, id:42, text: "Őrszem" }
    { group:64, id:43, text: "Ellenség" }
    { group:64, id:44, text: "Ellenség" }
    { group:64, id:45, text: "Ellenség" }
    { group:64, id:46, text: "Ellenség" }
    { group:64, id:47, text: "Ellenség" }
    { group:64, id:48, text: "Ellenség" }
    { group:64, id:49, text: "nem használt 2722" }
    { group:64, id:50, text: "nem használt 2723" }
    { group:64, id:51, text: "nem használt 2724" }
    { group:64, id:52, text: "nem használt 2725" }
    { group:64, id:53, text: "Ellenség" }
    { group:64, id:54, text: "Ellenség" }
    { group:64, id:55, text: "Ellenség" }
    { group:64, id:56, text: "Ellenség" }
    { group:64, id:57, text: "Ellenség" }
    { group:64, id:58, text: "nem használt 2731" }
    { group:64, id:59, text: "Nyílvessző" }
    { group:64, id:60, text: "Lándzsa" }
    { group:64, id:61, text: "Nyílvessző" }
    { group:64, id:62, text: "Hajítógép" }
    { group:64, id:63, text: "Lény" }
    { group:64, id:64, text: "Misszionárius" }
    { group:64, id:65, text: "Sirályok" }
    { group:64, id:66, text: "Kézbesítő fiú" }
    { group:64, id:67, text: "Hajóroncs" }
    { group:64, id:68, text: "Madarak" }
    { group:64, id:69, text: "Strucc" }
    { group:64, id:70, text: "Antilop" }
    { group:64, id:71, text: "Dárda" }
    { group:64, id:72, text: "Kocsiversenyző" }
    { group:64, id:73, text: "Vadász" }
    { group:64, id:74, text: "Vadászlándzsa" }
    { group:64, id:75, text: "Favágó" }
    { group:64, id:76, text: "Révcsónak" }
    { group:64, id:77, text: "Szállítóeszköz" }
    { group:64, id:78, text: "Hadihajó" }
    { group:64, id:79, text: "Ács" }
    { group:64, id:80, text: "Téglavető" }
    { group:64, id:81, text: "Kőfaragó" }
    { group:64, id:82, text: "Krokodil" }
    { group:64, id:83, text: "Hiéna" }
    { group:64, id:84, text: "Víziló" }
    { group:64, id:85, text: "Segédmunkás" }
    { group:64, id:86, text: "Szán" }
    { group:64, id:87, text: "Vízszállító" }
    { group:64, id:88, text: "Rendfenntartó" }
    { group:64, id:89, text: "Bíró" }
    { group:64, id:90, text: "Nádszedő" }
    { group:64, id:91, text: "Ünnepi pap" }
    { group:64, id:92, text: "Ellenséges szállítóeszköz" }
    { group:64, id:93, text: "Ellenséges hadihajó" }
    { group:64, id:94, text: "Temetési menet résztvevője" }
    { group:64, id:95, text: "Hal" }
    { group:64, id:96, text: "Szánhúzó" }
    { group:64, id:97, text: "Előadóművész" }
    { group:64, id:98, text: "Járvány sújtotta polgár" }
    { group:64, id:99, text: "Beduin gyalogság" }
    { group:64, id:100, text: "Egyiptomi hadihajó" }
    { group:64, id:101, text: "Egyiptomi szállítóhajó" }
    { group:64, id:102, text: "Áspiskígyó" }
    { group:64, id:103, text: "Oroszlán" }
    { group:64, id:104, text: "Skorpió" }
    { group:64, id:105, text: "Állatgondozó" }
    { group:64, id:106, text: "Béka" }
    { group:64, id:107, text: "Sáska" }
    { group:64, id:108, text: "Sírműves" }
    { group:64, id:109, text: "Múmia" }
    { group:65, id:0, text: "nem használt szakasz 65 - a C3 járókelők nevei voltak" }

    { group:66, id:0, text: "Réteg intelligens súgó." }
    { group:66, id:1, text: "Ezen a területen a kutak és vízellátók számára elérhető felszín alatti vízkészlet található" }
    { group:66, id:2, text: "Ennek a lakóháznak nincs hozzáférése ivóvízhez" }
    { group:66, id:3, text: "Ennek a lakóháznak csak alapvető hozzáférése van ivóvízhez" }
    { group:66, id:4, text: "Ennek a háznak nincs élelmiszerkészlete" }
    { group:66, id:5, text: "Ennek a háznak hamarosan elfogy a korlátozott élelmiszerkészlete" }
    { group:66, id:6, text: "Ennek a háznak legalább a következő hónapra elegendő élelmiszerkészlete van" }
    { group:66, id:7, text: "Ennek a háznak nincs gondja a túléléshez szükséges élelem beszerzésével" }
    { group:66, id:8, text: "Ennek a háznak nem szállítanak tiszta ivóvizet" }
    { group:66, id:9, text: "Ezt a házat nemrég meglátogatta egy vízszállító. Hosszú ideig lesz tiszta ivóvize" }
    { group:66, id:10, text: "Ennek a háznak van tisztaivóvíz-készlete" }
    { group:66, id:11, text: "Ha hamarosan nem jár erre vízszállító, ennek a háznak elfogy a tisztaivóvíz-készlete" }
    { group:66, id:12, text: "Ennek a háznak nincs hozzáférése templomokhoz vagy szentélyekhez" }
    { group:66, id:13, text: "Ennek a háznak csak egyetlen isten templomához van hozzáférése" }
    { group:66, id:14, text: "Ennek a háznak két különböző isten templomához van hozzáférése" }
    { group:66, id:15, text: "Ennek a háznak három különböző isten templomához van hozzáférése" }
    { group:66, id:16, text: "Ennek a háznak négy különböző isten templomához van hozzáférése" }
    { group:66, id:17, text: "Ennek a háznak minden isten templomához van hozzáférése" }
    { group:66, id:18, text: "Ennek a háznak van hozzáférése egy szentélyhez és minden isten templomához" }

    { group:66, id:46, text: "Ennek az épületnek nincs tűzveszélye" }
    { group:66, id:47, text: "Ennek az épületnek elhanyagolható a tűzveszélye" }
    { group:66, id:48, text: "Ennek az épületnek van némi tűzveszélye" }
    { group:66, id:49, text: "Ennek az épületnek tűzveszélye van" }
    { group:66, id:50, text: "Ez az épület valóságos tűzfészek" }
    { group:66, id:51, text: "Ez az épület bármelyik pillanatban kigyulladhat!" }

    { group:66, id:58, text: "Ez egy igen törvénytisztelő környék, egyáltalán nem jelentettek bűncselekményt" }
    { group:66, id:59, text: "Ezen a területen csak időnként fordul elő bűncselekmény" }
    { group:66, id:60, text: "Ez egy alacsony bűnözésű terület, de néhány lakó panaszkodott" }
    { group:66, id:61, text: "Nemrég több bűncselekményt is jelentettek itt, de összességében ez a környék meglehetősen biztonságos" }
    { group:66, id:62, text: "Ez egy magas bűnözésű terület. A lakók elégedetlenek, és az utcák éjszaka nem biztonságosak" }
    { group:66, id:63, text: "Az egész környék a nyugtalanság puskaporos hordója! A bűnözés mindennapos, és bármi megtörténhet" }

    { group:66, id:83, text: "Ennek a háznak nincs hozzáférése táncszínpadhoz" }
    { group:66, id:84, text: "Ezt a házat nemrég meglátogatta egy táncos. Hosszú ideig lesz hozzáférése táncszínpadhoz" }
    { group:66, id:85, text: "Ennek a háznak van hozzáférése táncszínpadhoz" }
    { group:66, id:86, text: "Ezt a házat egy ideje nem látogatta meg táncos. Hamarosan elveszíti a tánchoz való hozzáférést" }

    { group:66, id:91, text: "RÉGI: Egyetlen polgár sem akar itt élni" }
    { group:66, id:92, text: "RÉGI: Polgáraid nem látnak sem pozitív, sem negatív tényezőt ezen a területen" }
    { group:66, id:93, text: "RÉGI: Ez a terület kívánatos lakóhely" }

    { group:66, id:94, text: "Ennek az épületnek jelenleg nincs hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:95, text: "Ennek az épületnek jelenleg nagyon korlátozott a hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:96, text: "Ennek az épületnek jelenleg rossz a hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:97, text: "Ennek az épületnek jelenleg van némi hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:98, text: "Ennek az épületnek jelenleg jó a hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:99, text: "Ennek az épületnek jelenleg kiváló a hozzáférése munkaerőt biztosító emberekhez" }
    { group:66, id:104, text: "Ez a kunyhó maga gyűjti össze a saját élelmét..." }
    { group:66, id:105, text: "Ez a föld rendkívül termékeny. Az itt termesztett növények nagyok és erősek lesznek." }
    { group:66, id:106, text: "Ez a föld meglehetősen termékeny. Az itt termesztett növények általában egészségesek lesznek." }
    { group:66, id:107, text: "Ez a föld közepesen termékeny. Az itt termesztett növények nem érik el teljes lehetőségüket." }
    { group:66, id:108, text: "Ez a föld nem túl termékeny. Itt a növények alig fognak megteremni." }
    { group:66, id:109, text: "Ez a föld terméketlen. Itt semmilyen növény nem képes megteremni." }

    { group:66, id:110, text: " kosár gabonát tárolnak ebben az épületben." }
    { group:66, id:111, text: " kosár gabonát tárolnak ebben az épületben." }
    { group:66, id:112, text: " korsó gyümölcsöt tárolnak ebben az épületben." }
    { group:66, id:113, text: " korsó gyümölcsöt tárolnak ebben az épületben." }
    { group:66, id:114, text: " korsó zöldséget tárolnak ebben az épületben." }
    { group:66, id:115, text: " korsó zöldséget tárolnak ebben az épületben." }
    { group:66, id:116, text: " húsdarabot tárolnak ebben az épületben." }
    { group:66, id:117, text: " húsdarabot tárolnak ebben az épületben." }
    { group:66, id:118, text: " kerámiadarabot tárolnak ebben az épületben." }
    { group:66, id:119, text: " kerámiadarabot tárolnak ebben az épületben." }
    { group:66, id:120, text: " ékszerzacskót (luxuscikket) tárolnak ebben az épületben." }
    { group:66, id:121, text: " ékszerzacskót (luxuscikket) tárolnak ebben az épületben." }
    { group:66, id:122, text: " vászontekercset tárolnak ebben az épületben." }
    { group:66, id:123, text: " vászontekercset tárolnak ebben az épületben." }
    { group:66, id:124, text: " korsó sört tárolnak ebben az épületben." }
    { group:66, id:125, text: " korsó sört tárolnak ebben az épületben." }
    { group:66, id:126, text: "Ez az épület nem tárol árukat." }

    { group:66, id:136, text: "Ennek az épületnek nincs maláriaveszélye." }
    { group:66, id:137, text: "Ennek az épületnek elhanyagolható a maláriaveszélye." }
    { group:66, id:138, text: "Ennek az épületnek van némi maláriaveszélye." }
    { group:66, id:139, text: "Ennek az épületnek maláriaveszélye van." }
    { group:66, id:140, text: "Ebben az épületben hamarosan megjelenik a malária." }

    { group:66, id:141, text: "Ennek a háznak a következő problémái vannak:" }
    { group:66, id:142, text: "Ennek az iparnak a következő problémái vannak:" }
    { group:66, id:143, text: "Összeomlás veszélye" }
    { group:66, id:144, text: "Tűzveszély" }
    { group:66, id:145, text: "Betegségveszély" }
    { group:66, id:146, text: "Üres" }
    { group:66, id:147, text: "Maláriaveszély" }
    { group:66, id:148, text: "Beteg" }
    { group:66, id:149, text: "Lehetséges bűnözési veszély" }
    { group:66, id:150, text: "Hamarosan visszafejlődik" }
    { group:66, id:151, text: "Nincs nyersanyag" }
    { group:66, id:152, text: "Nincs munkaerő" }
    { group:66, id:153, text: "Részleges munkaerő" }
    { group:66, id:154, text: "Ipar leállítva" }
    { group:66, id:155, text: "Munkásokat keres" }
    { group:66, id:156, text: "Békákkal fertőzött" }
    { group:66, id:157, text: "Senki sem lakik ebben a lakóházban" }

    { group:66, id:158, text: "Ennek a háznak nincs hozzáférése bírósághoz" }
    { group:66, id:159, text: "Ezt a házat nemrég meglátogatta egy bíró. Hosszú ideig lesz hozzáférése bírósághoz" }
    { group:66, id:160, text: "Ennek a háznak van hozzáférése bírósághoz" }
    { group:66, id:161, text: "Ezt a házat egy ideje nem látogatta meg bíró. Hamarosan elveszíti a bírósági hozzáférést" }

    { group:66, id:162, text: "Ez a város egyik legkevésbé kívánatos helye" }
    { group:66, id:163, text: "Senki sem szeretne itt lakni, de vannak ennél rosszabb helyek is" }
    { group:66, id:164, text: "Az embereknek nincs különösebb véleményük ennek a területnek a kívánatosságáról" }
    { group:66, id:165, text: "Ez a terület jobb néhány másiknál, bár nem különösebben vonzó" }
    { group:66, id:166, text: "A legtöbb ember kellemes lakóhelynek találná ezt a helyet" }
    { group:66, id:167, text: "Ez a város egyik legelőkelőbb címe" }

    { group:66, id:168, text: "Ennek a háznak nincs hozzáférése állatkerthez" }
    { group:66, id:169, text: "Ezt a házat nemrég meglátogatta egy állatgondozó. Hosszú ideig lesz hozzáférése állatkerthez" }
    { group:66, id:170, text: "Ennek a háznak van hozzáférése állatkerthez" }
    { group:66, id:171, text: "Ezt a házat egy ideje nem látogatta meg állatgondozó. Hamarosan elveszíti az állatkerti hozzáférést" }
    { group:66, id:172, text: "Ez a ház békákkal fertőzött" }
    { group:67, id:0, text: "Engedélyezett épületek" }
    { group:67, id:1, text: "Nyersanyagok" }
    { group:67, id:2, text: "Aranybánya" }
    { group:67, id:3, text: "Vízemelő" }
    { group:67, id:4, text: "Öntözőcsatorna" }
    { group:67, id:5, text: "Halászati kikötő" }
    { group:67, id:6, text: "Munkatábor" }
    { group:67, id:7, text: "Magtár" }
    { group:67, id:8, text: "Bazár" }
    { group:67, id:9, text: "Raktárudvar" }
    { group:67, id:10, text: "Kikötő" }
    { group:67, id:11, text: "Zsonglőrködés" }
    { group:67, id:12, text: "Zene" }
    { group:67, id:13, text: "Tánc" }
    { group:67, id:14, text: "Szenet-játékok" }
    { group:67, id:15, text: "Ünnepi tér" }
    { group:67, id:16, text: "Írnokiskola" }
    { group:67, id:17, text: "Könyvtár" }
    { group:67, id:18, text: "Vízellátó" }
    { group:67, id:19, text: "Fogorvos" }
    { group:67, id:20, text: "Patika" }
    { group:67, id:21, text: "Orvosi rendelő" }
    { group:67, id:22, text: "Halottasház" }
    { group:67, id:23, text: "Adószedő" }
    { group:67, id:24, text: "Bíróság" }
    { group:67, id:25, text: "Palota" }
    { group:67, id:26, text: "Kúria" }
    { group:67, id:27, text: "Úttorlasz" }
    { group:67, id:28, text: "Híd" }
    { group:67, id:29, text: "Révátkelő" }
    { group:67, id:30, text: "Kertek" }
    { group:67, id:31, text: "Tér" }
    { group:67, id:32, text: "Szobrok" }
    { group:67, id:33, text: "Fal" }
    { group:67, id:34, text: "Torony" }
    { group:67, id:35, text: "Kapuház" }
    { group:67, id:36, text: "Toborzó" }
    { group:67, id:37, text: "Erőd: Gyalogság" }
    { group:67, id:38, text: "Erőd: Íjászok" }
    { group:67, id:39, text: "Erőd: Kocsihajtók" }
    { group:67, id:40, text: "Katonai akadémia" }
    { group:67, id:41, text: "Fegyverkovács" }
    { group:67, id:42, text: "Kocsikészítő" }
    { group:67, id:43, text: "Hadihajó-kikötő" }
    { group:67, id:44, text: "Szállítóhajó-kikötő" }
    { group:67, id:45, text: "Állatkert" }
    { group:68, id:0, text: "Ez az egérsúgó szövege" }
    { group:68, id:1, text: "A panelhez tartozó súgóoldal megjelenítése" }
    { group:68, id:2, text: "Panel bezárása" }
    { group:68, id:3, text: "E mentett játék betöltése" }
    { group:68, id:4, text: "Az aktuális játék mentése ebbe a fájlba" }
    { group:68, id:5, text: "Művelet megszakítása" }
    { group:68, id:6, text: "Mentett játékok görgetése" }
    { group:68, id:7, text: "Kattints egy fájlnévre a kiválasztásához" }
    { group:68, id:8, text: "szabad egérsúgó" }
    { group:68, id:9, text: "szabad egérsúgó" }
    { group:68, id:10, text: "A vezérlőpult elrejtése a nagyobb játéktér megjelenítéséhez" }
    { group:68, id:11, text: "Városi rétegjelentés kiválasztása" }
    { group:68, id:12, text: "A teljes vezérlőpult megjelenítése" }
    { group:68, id:13, text: "E játék betöltése" }
    { group:68, id:14, text: "Az aktuális játék mentése ebbe a fájlba" }
    { group:68, id:15, text: "Művelet megszakítása" }
    { group:68, id:16, text: "Küldetések görgetése" }
    { group:68, id:17, text: "Kattints egy fájlnévre a kiválasztásához" }
    { group:68, id:18, text: "szabad egérsúgó" }
    { group:68, id:19, text: "szabad egérsúgó" }
    { group:68, id:20, text: "Lakóépületek építése" }
    { group:68, id:21, text: "Utak építése" }
    { group:68, id:22, text: "Terület megtisztítása" }
    { group:68, id:23, text: "Mezőgazdasági és élelmiszeripari épületek" }
    { group:68, id:24, text: "Ipari épületek" }
    { group:68, id:25, text: "Raktározási és elosztási épületek" }
    { group:68, id:26, text: "Szórakoztató épületek" }
    { group:68, id:27, text: "Vallási épületek" }
    { group:68, id:28, text: "Oktatási épületek" }
    { group:68, id:29, text: "Egészségügyi és higiéniai épületek" }
    { group:68, id:30, text: "Városi épületek" }
    { group:68, id:31, text: "Katonai épületek" }
    { group:68, id:32, text: "UTOLSÓ művelet visszavonása (csak akkor érhető el, ha az ikon világít)" }
    { group:68, id:33, text: "Üzenetek megtekintése" }
    { group:68, id:34, text: "A város legutóbbi problémás területeinek végigjárása" }
    { group:68, id:35, text: "Küldetés áttekintése" }
    { group:68, id:36, text: "Kattints erre az áttekintő térképre, hogy a város távoli részeire ugorj" }
    { group:68, id:37, text: "szabad egérsúgó" }
    { group:68, id:38, text: "szabad egérsúgó" }
    { group:68, id:39, text: "szabad egérsúgó" }
    { group:68, id:40, text: "szabad egérsúgó" }
    { group:68, id:41, text: "Felügyelők felkeresése" }
    { group:68, id:42, text: "Világtérkép megnyitása" }
    { group:68, id:43, text: "Küldetés áttekintése" }
    { group:68, id:44, text: "Nézet visszaállítása pontosan észak felé" }
    { group:68, id:45, text: "Nézet forgatása az óramutató járásával megegyező irányba" }
    { group:68, id:46, text: "Nézet forgatása az óramutató járásával ellentétes irányba" }
    { group:68, id:47, text: "szabad egérsúgó" }
    { group:68, id:48, text: "szabad egérsúgó" }
    { group:68, id:49, text: "szabad egérsúgó" }
    { group:68, id:50, text: "szabad egérsúgó" }
    { group:68, id:52, text: "Hang- és sebességbeállítások" }
    { group:68, id:53, text: "Játéksúgó megnyitása" }
    { group:68, id:54, text: "Közvetlen ugrás a kiválasztott felügyelő jelentéseihez" }
    { group:68, id:55, text: "szabad egérsúgó" }
    { group:68, id:56, text: "szabad egérsúgó" }
    { group:68, id:57, text: "szabad egérsúgó" }
    { group:68, id:58, text: "szabad egérsúgó" }
    { group:68, id:59, text: "szabad egérsúgó" }
    { group:68, id:60, text: "szabad egérsúgó" }
    { group:68, id:61, text: "A város jelenlegi pénzkészlete" }
    { group:68, id:62, text: "A város jelenlegi lakossága" }
    { group:68, id:63, text: "Az aktuális dátum!" }
    { group:68, id:64, text: "szabad egérsúgó" }
    { group:68, id:65, text: "szabad egérsúgó" }
    { group:68, id:66, text: "szabad egérsúgó" }
    { group:68, id:67, text: "szabad egérsúgó" }
    { group:68, id:68, text: "szabad egérsúgó" }
    { group:68, id:69, text: "szabad egérsúgó" }
    { group:68, id:70, text: "Kereskedelmi felügyelő felkeresése" }
    { group:68, id:71, text: "A munkások felügyelőjének felkeresése" }
    { group:68, id:72, text: "A hadügyi felügyelő felkeresése" }
    { group:68, id:73, text: "Politikai felügyelő felkeresése" }
    { group:68, id:74, text: "Értékelési felügyelő felkeresése" }
    { group:68, id:75, text: "Kereskedelmi felügyelő felkeresése" }
    { group:68, id:76, text: "A magtárak felügyelőjének felkeresése" }
    { group:68, id:77, text: "A közegészségügyi felügyelő felkeresése" }
    { group:68, id:78, text: "A tanulás felügyelőjének felkeresése" }
    { group:68, id:79, text: "A szórakoztatás felügyelőjének felkeresése" }
    { group:68, id:80, text: "A templomok felügyelőjének felkeresése" }
    { group:68, id:81, text: "A kincstár felügyelőjének felkeresése" }
    { group:68, id:82, text: "Főfelügyelő felkeresése" }
    { group:68, id:83, text: "Az emlékművek felügyelőjének felkeresése" }
    { group:68, id:84, text: "Visszatérés a fő városnézethez" }
    { group:68, id:85, text: "szabad egérsúgó" }
    { group:68, id:86, text: "szabad egérsúgó" }
    { group:68, id:87, text: "szabad egérsúgó" }
    { group:68, id:88, text: "szabad egérsúgó" }
    { group:68, id:89, text: "szabad egérsúgó" }
    { group:68, id:90, text: "szabad egérsúgó" }
    { group:68, id:91, text: "szabad egérsúgó" }
    { group:68, id:92, text: "Kattints ide, hogy fontossági sorrendet állíts be ehhez a munkakategóriához" }
    { group:68, id:93, text: "Az éves bér meghatározása minden 10 munkásra" }
    { group:68, id:94, text: "Kattints ide, hogy eltávolítsd az ehhez a feladathoz beállított prioritást" }
    { group:68, id:95, text: "Kattints egy számra a prioritási szint beállításához. Minden más feladat prioritása ennek megfelelően módosul" }
    { group:68, id:96, text: "Kattints ide, hogy pénzt adományozz a városnak" }
    { group:68, id:97, text: "Kattints ide, hogy beállítsd a személyes fizetésedet" }
    { group:68, id:98, text: "Fizetési képernyő bezárása" }
    { group:68, id:99, text: "Ennek a fizetési szintnek a kiválasztása" }
    { group:68, id:100, text: "Adományozási képernyő bezárása" }
    { group:68, id:101, text: "Ezt a pénzt a családi megtakarításaidból adományozod a városnak" }
    { group:68, id:102, text: "Az adományozandó összeg beállítása" }
    { group:68, id:103, text: "A pontosan adományozni kívánt összeg módosítása" }
    { group:68, id:104, text: "Kattints ide, hogy tanácsot kapj a Kultúra értékelésedről" }
    { group:68, id:105, text: "Kattints ide, hogy tanácsot kapj a Jólét értékelésedről" }
    { group:68, id:106, text: "Kattints ide, hogy tanácsot kapj az Emlékmű értékelésedről" }
    { group:68, id:107, text: "Kattints ide, hogy tanácsot kapj a Királyság értékelésedről" }
    { group:68, id:108, text: "Minden áru import- és exportárának megjelenítése" }
    { group:68, id:109, text: "Kattints ide az iparág állapotának megtekintéséhez" }
    { group:68, id:110, text: "A kívánt készletmennyiség beállítása, amelynek meg kell maradnia, mielőtt bármit exportálnál" }
    { group:68, id:111, text: "A tevékenység termelésének be- vagy kikapcsolása az egész városban" }
    { group:68, id:112, text: "Az adott áru kereskedelmi állapotának módosítása" }
    { group:68, id:113, text: "Grafikon kiválasztása" }
    { group:68, id:114, text: "Ünnepség információi" }
    { group:68, id:115, text: "Ünnepség rendezése ennek az istennek a tiszteletére" }
    { group:68, id:116, text: "Ne rendezz ünnepséget" }
    { group:68, id:117, text: "Ünnepség rendezése Ozirisz tiszteletére" }
    { group:68, id:118, text: "Ünnepség rendezése Ré tiszteletére" }
    { group:68, id:119, text: "Ünnepség rendezése Ptah tiszteletére" }
    { group:68, id:120, text: "Ünnepség rendezése Széth tiszteletére" }
    { group:68, id:121, text: "Ünnepség rendezése Básztet tiszteletére" }
    { group:68, id:122, text: "Városi adókulcs módosítása" }
    { group:68, id:123, text: "Kattints ide, hogy beszélj ezzel a személlyel" }
    { group:68, id:124, text: "Részletes információk erről a házról" }
    { group:68, id:125, text: "Tárolt üzenetek görgetése" }
    { group:68, id:126, text: "Korábban olvasott üzenet. @L Bal kattintással elolvashatod ezt az üzenetet. @L Jobb kattintással törölheted." }
    { group:68, id:127, text: "Olvasatlan üzenet. @L Bal kattintással elolvashatod ezt az üzenetet. @L Jobb kattintással törölheted." }
    { group:68, id:128, text: "Visszatérés az előző súgóképernyőre" }
    { group:68, id:129, text: "Kilépés a fáraó súgójából" }
    { group:68, id:130, text: "Súgó görgetése erről a témáról" }
    { group:68, id:131, text: "Üzenet törlése" }
    { group:68, id:132, text: "Kattints ide, hogy a problémás helyre ugorj" }
    { group:68, id:133, text: "Ajándék küldése Egyiptomnak" }
    { group:68, id:134, text: "Kattints ide a vállalat alapításának módosításához" }
    { group:68, id:140, text: "Kattints ide a szállítóhajó parancsainak kiadásához" }
    { group:68, id:141, text: "Kattints ide a hadihajó parancsainak kiadásához" }
    { group:68, id:142, text: "Adókulcs" }
    { group:68, id:143, text: "Hadsereg állapotának megtekintése" }
    { group:68, id:144, text: "Flotta állapotának megtekintése" }
    { group:68, id:145, text: "Ugrás a Királyság térképére" }
    { group:68, id:146, text: "Küldetésfeltételek beállítása" }
    { group:68, id:147, text: "Sík terület" }
    { group:68, id:148, text: "Fák" }
    { group:68, id:149, text: "Víz és mocsaras területek" }
    { group:68, id:150, text: "Rét" }
    { group:68, id:151, text: "Út" }
    { group:68, id:152, text: "Sziklák és dűnék" }
    { group:68, id:153, text: "Folyópontok" }
    { group:68, id:154, text: "Inváziós pontok" }
    { group:68, id:155, text: "Emberpontok" }
    { group:68, id:156, text: "Állatpontok" }
    { group:68, id:157, text: "Ecsetek" }
    { group:68, id:158, text: "Város, régió vagy grafika hozzáadása" }
    { group:68, id:159, text: "Város, régió vagy grafika szerkesztése" }
    { group:68, id:160, text: "Város, régió vagy grafika törlése" }
    { group:68, id:161, text: "Főmenü megjelenítése" }
    { group:68, id:162, text: "Kereskedelmi vagy inváziós útvonal hozzáadása" }
    { group:68, id:163, text: "Kereskedelmi vagy inváziós útvonal szerkesztése" }
    { group:68, id:164, text: "Visszaállítás az alapértelmezett térképre" }
    { group:68, id:165, text: "Visszatérés a régiónézethez" }
    { group:68, id:166, text: "Import- és exportárak módosítása" }
    { group:68, id:167, text: "Rang, finanszírozás, kezdődátum és jelenlegi fáraó módosítása" }
    { group:68, id:168, text: "Éghajlati lehetőségek végigjárása" }
    { group:68, id:169, text: "Események megtervezése" }
    { group:68, id:170, text: "Ellenség kiválasztása" }
    { group:68, id:171, text: "Istenek meghatározása" }
    { group:68, id:172, text: "Elérhető épületek beállítása" }
    { group:68, id:173, text: "Értékelési követelmények beállítása és emlékművek kiválasztása" }
    { group:68, id:174, text: "Az áradás hosszának és minőségének meghatározása" }
    { group:68, id:175, text: "Nézet forgatása" }
    { group:68, id:176, text: "Grafika módosítása" }
    { group:68, id:177, text: "Gyilkos típusok" }
    { group:68, id:178, text: "Emlékmű korszaka" }
    { group:69, id:0, text: "szükséges)" }
    { group:69, id:1, text: "Hatékonyság" }
    { group:69, id:2, text: "Nincs omlásveszély" }
    { group:69, id:3, text: "Nagyon alacsony omlásveszély" }
    { group:69, id:4, text: "Alacsony omlásveszély" }
    { group:69, id:5, text: "Némi omlásveszély" }
    { group:69, id:6, text: "Magas omlásveszély" }
    { group:69, id:7, text: "Nagyon magas omlásveszély" }
    { group:69, id:8, text: "Az omlás közvetlen veszélye fennáll" }
    { group:69, id:9, text: "Nincs tűzveszély" }
    { group:69, id:10, text: "Nagyon alacsony tűzveszély" }
    { group:69, id:11, text: "Alacsony tűzveszély" }
    { group:69, id:12, text: "Némi tűzveszély" }
    { group:69, id:13, text: "Magas tűzveszély" }
    { group:69, id:14, text: "Nagyon magas tűzveszély" }
    { group:69, id:15, text: "Rendkívüli tűzveszély" }
    { group:69, id:16, text: "Nincsenek emberek a városban!" }
    { group:69, id:17, text: "Nem élnek munkások a közelben" }
    { group:69, id:18, text: "A munkások felügyelője átcsoportosíthatna némi munkaerőt" }
    { group:69, id:19, text: "A munkások felügyelője átcsoportosíthatna némi munkaerőt" }
    { group:69, id:20, text: "FIGYELEM: Rossz hozzáférés a munkásokhoz" }
    { group:69, id:21, text: "Alig működik. Az ágazatunknak kétségbeejtően több munkásra van szüksége" }
    { group:69, id:22, text: "Gyengén működik. Az ágazatunknak sokkal több munkásra van szüksége" }
    { group:69, id:23, text: "Jól működik, de az ágazatunknak nagy szüksége lenne még több munkásra" }
    { group:69, id:24, text: "Csökkentett kapacitással működik. Alig érkezett munkás mostanában" }
    { group:69, id:25, text: "FIGYELEM: Ez az épület nem kapcsolódik úthoz" }
    { group:69, id:26, text: "Létszámhiányos. Csak árut tud kiküldeni, de árut nem fogad" }
    { group:69, id:27, text: "Csak minimális személyzettel működik. Nem küld ki és nem fogad árut" }
    { group:70, id:0, text: "Nincs ember ezen a területen." }
    { group:70, id:1, text: "szabad" }
    { group:70, id:2, text: "szabad" }
    { group:70, id:3, text: "szabad" }
    { group:70, id:4, text: "szabad" }
    { group:70, id:5, text: "szabad" }
    { group:70, id:6, text: "szabad" }
    { group:70, id:7, text: "szabad" }
    { group:70, id:8, text: "szabad" }
    { group:70, id:9, text: "szabad" }
    { group:70, id:10, text: "Semmi" }
    { group:70, id:11, text: "Fák és erdőség" }
    { group:70, id:12, text: "Sziklák" }
    { group:70, id:13, text: "Víz" }
    { group:70, id:14, text: "Fák" }
    { group:70, id:15, text: "Repedések a földön" }
    { group:70, id:16, text: "Út" }
    { group:70, id:17, text: "Öntözőcsatorna" }
    { group:70, id:18, text: "Elpusztult épületek törmeléke" }
    { group:70, id:19, text: "Fal" }
    { group:70, id:20, text: "Üres terület" }
    { group:70, id:21, text: "Híd" }
    { group:70, id:22, text: "Kertek" }
    { group:70, id:23, text: "Tér" }
    { group:70, id:24, text: "A fővárosba" }
    { group:70, id:25, text: "A királyságba" }
    { group:70, id:26, text: "Érctartalmú szikla" }
    { group:70, id:27, text: "Normál szikla" }
    { group:70, id:28, text: "Különleges szikla" }
    { group:70, id:29, text: "Ártér" }
    { group:70, id:30, text: "Elárasztott ártér" }
    { group:70, id:31, text: "Mocsárvidék" }
    { group:70, id:32, text: "Homokdűnék" }
    { group:70, id:33, text: "Téglafal" }
    { group:70, id:34, text: "Fal" }
    { group:70, id:35, text: "Rét" }
    { group:70, id:36, text: "Sziklafalak" }
    { group:70, id:37, text: "A fákon nem lehet áthaladni, de ki lehet irtani őket. A favágóknak érdemes megfelelően közel lenniük a fákhoz. Az erdőség idővel újranő. (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:38, text: "A sziklákon nem lehet áthaladni, és nem távolíthatók el. Talán szerencséd van, és mészkövet, homokkövet vagy gránitot találsz itt fejtésre, de az is lehet, hogy értéktelen közönséges kő. Nézd meg a nyersanyagaidat, hogy kiderüljön." }
    { group:70, id:39, text: "A vízen csak hajók és csónakok közlekednek, de kompok és hidak bizonyos pontokon lehetővé teszik az átkelést. A kikötők létfontosságú kereskedelmet tesznek lehetővé a királyság többi részével. Az agyagbányáknak víz mellett kell lenniük." }
    { group:70, id:40, text: "Járhatatlan terület, amely megtisztítható a város terjeszkedéséhez. A favágóknak a fák közelében kell lenniük, hogy kitermelhessék a fát. (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:41, text: "Ezeket a szakadékokat földrengések okozták. Nem lehet rajtuk átkelni, és nem lehet őket feltölteni. Az emberek pedig nem szeretnek mellettük élni." }
    { group:70, id:42, text: "Az emberek csak az utakon hagyják el épületeiket, és csak ott kelhetnek át az ártér és a szárazföld között, ahol az utak átjárást biztosítanak. (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:43, text: "Az öntözőcsatornák javítják a két mezőnyi körzetükben található földek termékenységét." }
    { group:70, id:44, text: "Ezek a régi épületek omladozó maradványai csökkentik a környék vonzerejét." }
    { group:70, id:45, text: "A falak megvédik a védtelen polgárokat a fosztogatóktól és betolakodóktól. Csak bizonyos mennyiségű ostromot képesek elviselni, és a vastagabb falak tovább tartanak." }
    { group:70, id:46, text: "A nyílt terület kiváló építési hely. A bevándorlók, katonák és bizonyos nyersanyaggyűjtők áthaladhatnak rajta. (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:47, text: "Ez a híd új területeket nyit meg városunk számára, de lehetővé teszi a ragadozók vagy betolakodók számára is, hogy átkeljenek a vízen!" }
    { group:70, id:48, text: "A kertek javítják a helyi környezetet." }
    { group:70, id:49, text: "Az emberek kedvelik a tereket!" }
    { group:70, id:50, text: "Ez az út köti össze városunkat Egyiptom többi részével, és nyitva kell tartani, hogy bevándorlók és kereskedők érkezhessenek városunkba." }
    { group:70, id:51, text: "Ez az út vezet a királyság távolabbi vidékei felé. Királyi országút, ezért a szabad áthaladást fenn kell tartani rajta." }
    { group:70, id:52, text: "Ez érctartalmú szikla. Itt aranyat vagy rezet bányászhatsz, attól függően, hogy melyik fém található benne." }
    { group:70, id:53, text: "Ez normál szikla. Városod nyersanyagaitól függően építési követ vagy akár drágaköveket is bányászhatsz innen." }
    { group:70, id:54, text: "Ez különleges szikla. (Ez a szöveg sehol sem jelenhet meg)" }
    { group:70, id:55, text: "Ez a terület most rendkívül termékeny földet kínál, miután a folyó visszahúzódott." }
    { group:70, id:56, text: "Ez a terület rendkívül termékeny földet fog kínálni, miután a folyó visszahúzódik." }
    { group:70, id:57, text: "A mocsaras területek túl vizenyősek ahhoz, hogy építményeket tartsanak meg, de óvatos polgárok átkelhetnek rajtuk. Itt nád terem, de vigyázz a krokodilokkal! (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:58, text: "Az itt mozgó homok nem alkalmas építkezésre, de bevándorlók, katonák és mások áthaladhatnak rajta. (Egy épület kijelöléséhez kattints jobb gombbal az alapjára.)" }
    { group:70, id:59, text: "Ez téglafal. Tovább lassítja a támadókat, mint egy vályogfal, de nem helyettesíti a kiképzett katonákból álló sereget!" }
    { group:70, id:60, text: "Ez egyszerű vályogfal. Rövid ideig lassítja a támadókat, de nem szabad erős védelemnek tekintened." }
    { group:70, id:61, text: "Ezen a földön mindenféle növény termeszthető. Minél dúsabbak az itt növő virágok, annál termékenyebb a talaj." }
    { group:70, id:62, text: "Ezek a hatalmas sziklafalak ideális helyek bizonyos műemlékek építésére. Az emberek nem tudnak átkelni ezen a meredek terepen, és bányászni sem lehet belőlük." }
    { group:71, id:0, text: "Zenepavilon" }
    { group:71, id:1, text: "Az emberek ide jönnek, hogy megnézzék a legújabb zsonglőrmutatványokat és zenét hallgassanak." }
    { group:71, id:2, text: "Ezen a téren soha nincsenek előadások. Zsonglőrökre és zenészekre van szüksége, hogy életre keljen." }
    { group:71, id:3, text: "Ez a tér izgalmas zsonglőrmutatványokkal és helyi zenészek zenéjével szórakoztatja a közösséget." }
    { group:71, id:4, text: "Ez a tér a helyi közösség szórakoztatására zenei előadásokat kínál. Zsonglőröket keres, hogy néhány műsort bemutathassanak." }
    { group:71, id:5, text: "Ez a tér zsonglőrmutatványoknak ad helyet. Még jobban tetszene a közönségnek, ha zenészek is játszanának." }
    { group:71, id:6, text: "Ez a tér halott. Alkalmazottak nélkül nem nyújt szórakozási lehetőséget a helyi közösségnek." }
    { group:71, id:7, text: "Nincs jelenlegi zenei előadás" }
    { group:71, id:8, text: "A zenészek még ennyi ideig játszanak:" }
    { group:71, id:9, text: "Nincs jelenlegi zsonglőrmutatvány" }
    { group:71, id:10, text: "A jelenlegi zsonglőrök még ennyi ideig kápráztatják el a közönséget:" }
    { group:72, id:0, text: "Bódé" }
    { group:72, id:1, text: "A polgárok ügyes zsonglőrmutatványokat és mindenféle bolondozást élvezhetnek itt." }
    { group:72, id:2, text: "Ezen a téren soha nincsenek előadások. Igazi zsonglőrökre van szüksége, hogy szórakoztatást nyújtson." }
    { group:72, id:3, text: "Ezen a téren jelenleg helyi zsonglőrök előadásai láthatók, akik általában nagy közönséget vonzanak." }
    { group:72, id:4, text: "Ezen a téren csak a szellő mozgat meg valamit. Dolgozók nélkül nem kínál előadásokat a helyieknek." }
    { group:72, id:5, text: "Nincs jelenlegi zsonglőrelőadás" }
    { group:72, id:6, text: "A jelenlegi előadás még ennyi ideig tart:" }
    { group:72, id:7, text: "Műsoron: „A nagy Mephisto zsonglőrmutatványa” – Mephisto előadásában" }
    { group:72, id:8, text: "Műsoron: „Az idő homokja” – Vasrúdhotep előadásában" }
    { group:72, id:9, text: "Műsoron: „Sírasd meg a folyót” – Waseth előadásában" }
    { group:72, id:10, text: "Műsoron: „A 10 000 debenes piramis” – Desenseth előadásában" }
    { group:72, id:11, text: "Műsoron: El-Tonjon „Krokodilsziklái”" }
    { group:73, id:0, text: "Szenet-ház" }
    { group:73, id:1, text: "Az ügyességi és szerencsejátékok a játékosok vagyonát gyarapíthatják vagy teljesen tönkretehetik." }
    { group:73, id:2, text: "Ebben a Szenet-házban vannak játékosok, de a megbízható sörutánpótlás még élvezetesebbé tenné a játékokat." }
    { group:73, id:3, text: "Ebben a Szenet-házban folyamatosan zajlanak a játékok, a helyi lakosság nagy örömére." }
    { group:73, id:4, text: "Senki sem látogatja ezt a Szenet-házat. Dolgozók nélkül a helyi közösség nem kap belőle semmilyen szórakozást." }
    { group:73, id:5, text: "Nincs folyamatban lévő játék" }
    { group:73, id:6, text: "A jelenlegi játékok még ennyi ideig tartanak:" }
    { group:73, id:7, text: "Tárolt sör:" }
    { group:74, id:0, text: "Pavilon" }
    { group:74, id:1, text: "Tánc, zene és zsonglőrködés... mi másra vágyhatna egy polgár?" }
    { group:74, id:2, text: "Ezen a téren nincsenek előadások. Táncosokra, zenészekre és zsonglőrökre van szüksége, hogy tömegeket vonzzon." }
    { group:74, id:3, text: "Ezen a téren folyamatos a pezsgés: a tánc, a zene és a zsonglőrmutatványok nagy örömet okoznak a helyi közösségnek." }
    { group:74, id:4, text: "Ezen a téren táncosok és zenészek szórakoztatják a helyieket, de néhány zsonglőrt is szívesen látnának." }
    { group:74, id:5, text: "Ezen a téren táncosok és zsonglőrök vannak. Zenészekre van szüksége, hogy teljes legyen a szórakoztatás." }
    { group:74, id:6, text: "Ezen a téren zenészek és zsonglőrök vannak, de a zene táncosokért kiált, hogy teljes legyen az előadás." }
    { group:74, id:7, text: "Ezen a téren zsonglőrelőadások vannak, de zenészekre és táncosokra van szüksége, hogy megtöltsék az egyébként üres színpadokat." }
    { group:74, id:8, text: "Ezen a téren zenészek vannak, de nincsenek zsonglőrök vagy táncosok." }
    { group:74, id:9, text: "Ezen a téren táncosok vannak, akik nagyon örülnének egy kis zenének. A zsonglőrök is jól jönnének." }
    { group:74, id:10, text: "Ez a tér zárva van. Alkalmazottak nélkül, akik működtetnék, haszontalan szórakoztató létesítmény." }
    { group:74, id:11, text: "Nincs jelenlegi zsonglőrelőadás" }
    { group:74, id:12, text: "A zsonglőrmutatványok még ennyi ideig folytatódnak:" }
    { group:74, id:13, text: "Nincs jelenlegi zenei előadás" }
    { group:74, id:14, text: "A zenei előadások még ennyi ideig tartanak:" }
    { group:74, id:15, text: "Nincs jelenlegi táncelőadás" }
    { group:74, id:16, text: "A táncelőadások még ennyi ideig tartanak:" }
    { group:75, id:0, text: "Konzervatórium" }
    { group:75, id:1, text: "Az egyiptomiak mindig lelkesen hallgatják az új zenészek legújabb előadásait." }
    { group:75, id:2, text: "Örömmel jelentjük, hogy teljes létszámmal működve havonta akár négy új zenészt is kiképezünk." }
    { group:75, id:3, text: "Kissé létszámhiányosak vagyunk, ezért legfeljebb két új zenészt tudunk kiképezni havonta." }
    { group:75, id:4, text: "Fél létszámmal működünk, ezért a következő hónapban csak egy zenészt tudunk kiképezni." }
    { group:75, id:5, text: "Olyan kevés alkalmazottunk van, hogy nehezen fogunk egyetlen új zenészt is kiképezni a következő két hónap során." }
    { group:75, id:6, text: "Rajtam kívül nincs egyetlen alkalmazottam sem. Ilyen körülmények között nem várható el tőlem a munka! Legjobb esetben is három hónap alatt tudok kiképezni egy zenészt." }
    { group:75, id:7, text: "Képzőszemélyzet nélkül ez az iskola nem tud új zenészeket kiképezni." }
    { group:76, id:0, text: "Tánciskola" }
    { group:76, id:1, text: "A táncosok kecses és csábító új mozdulatokkal gyönyörködtetik a közönséget." }
    { group:76, id:2, text: "Örömmel jelentjük, hogy teljes létszámmal működve havonta akár négy új táncost is képezhetünk." }
    { group:76, id:3, text: "Kissé létszámhiányosak vagyunk, ezért legfeljebb két új táncost tudunk kiképezni havonta." }
    { group:76, id:4, text: "Fél létszámmal működünk, ezért a következő hónapban csak egy táncost tudunk kiképezni." }
    { group:76, id:5, text: "Nagy szükségünk van oktatókra, ezért alig tudunk egyetlen új táncossal is végezni a következő két hónap során." }
    { group:76, id:6, text: "Rajtam kívül nincs egyetlen alkalmazottam sem. Ilyen körülmények között nem várható el tőlem a munka! Legjobb esetben is három hónap alatt tudok megtanítani egy táncost." }
    { group:76, id:7, text: "Oktatók nélkül ez a tánciskola nem tud új táncosokat képezni." }
    { group:77, id:0, text: "Zsonglőriskola" }
    { group:77, id:1, text: "Az új, ötletes mutatványokkal rendelkező zsonglőrökre mindig nagy a kereslet." }
    { group:77, id:2, text: "Örömmel jelentjük, hogy teljes létszámmal működve havonta akár négy új zsonglőrt is kiképezünk." }
    { group:77, id:3, text: "Kissé létszámhiányosak vagyunk, ezért legfeljebb két új zsonglőrt tudunk kiképezni havonta." }
    { group:77, id:4, text: "Fél létszámmal működünk, ezért a következő hónapban csak egy zsonglőrt tudunk kiképezni." }
    { group:77, id:5, text: "Nagy szükségünk van alkalmazottakra. Nehéz lesz egyetlen új zsonglőrt is kiképeznünk a következő két hónap során." }
    { group:77, id:6, text: "Rajtam kívül nincs egyetlen alkalmazottam sem. Ilyen körülmények között nem várható el tőlem a munka! Legjobb esetben is három hónap alatt tudok kiképezni egy zsonglőrt." }
    { group:77, id:7, text: "Ez az iskola elhagyatott. Alkalmazott mentorok nélkül nem képeznek ki új zsonglőröket." }
    { group:78, id:0, text: "Szenet-oktatók? Korábban bikaviadal-oktató volt" }
    { group:78, id:1, text: "Az itt dolgozó mesterséges stratégák szakértő Szenet-mestereket képeznek ki, hogy működtessék a város mindig népszerű Szenet-házait." }
    { group:78, id:2, text: "Örömmel jelentjük, hogy teljes létszámmal működve havonta akár négy Szenet-mestert is biztosíthatunk." }
    { group:78, id:3, text: "Kissé létszámhiányosak vagyunk, ezért legfeljebb két új Szenet-mestert tudunk biztosítani havonta." }
    { group:78, id:4, text: "Fél létszámmal működünk, ezért a következő hónapban csak egy Szenet-mestert tudunk kiképezni." }
    { group:78, id:5, text: "Nagy szükségünk van alkalmazottakra, ezért nehéz lesz egyetlen új Szenet-mestert is kiképeznünk a következő két hónap során." }
    { group:78, id:6, text: "Rajtam kívül nincs egyetlen alkalmazottam sem. Ilyen körülmények között nem várható el tőlem a munka! Legjobb esetben is három hónap alatt tudok tökéletesíteni egy Szenet-mestert." }
    { group:78, id:7, text: "Tanítók nélkül nem képeznek ki új Szenet-mestereket. Emiatt a város Szenet-házai mind megsínylhetik a helyzetet." }
    { group:79, id:0, text: "Kertek" }
    { group:80, id:0, text: "Szobor" }
    { group:80, id:1, text: "Az isteneknek és letűnt fáraóknak állított emlékművek növelik egy városrész tekintélyét. Az emberek büszkék, ha szobrok vannak a közelükben... és minél nagyobb, annál jobb." }
    { group:80, id:2, text: "Diadalív" }
    { group:80, id:3, text: "Ez a lenyűgöző építmény Egyiptom ellenségei felett aratott történelmi győzelmeknek állít emléket. Ennél tekintélyesebb dolog aligha létezhet." }
    { group:81, id:0, text: "Patika" }
    { group:81, id:1, text: "A patikusok javítják a polgárok egészségét, miközben útvonaluk mentén házhoz járnak a városrészekben. A gazdagabb területek szeretnének patikát a közelükben." }
    { group:81, id:2, text: "Ez a patika nem működik, és semmit sem tesz a helyi közösség egészségéért." }
    { group:81, id:3, text: "Ez a patika működik, és gyógyitalokat valamint kenőcsöket biztosít a helyi közösség számára." }
    { group:82, id:0, text: "Halottasház" }
    { group:82, id:1, text: "Bár senki sem szeretne egy ilyen épület közelében élni, a halottasházak életeket mentenek, amikor járvány tör ki. A városnak elegendő kapacitással kell rendelkeznie minden elhunyt bebalzsamozásához." }
    { group:82, id:2, text: "Ez a halottasház nem működik, és nem tudja az elhunyt lakosok testeit előkészíteni a túlvilági útra." }
    { group:82, id:3, text: "Ez a halottasház működik, és gyorsan, szakszerűen mumifikálja az elhunyt szomszédokat." }
    { group:82, id:4, text: "Vászon nélkül nem tudjuk előkészíteni a halottakat az örökkévalóságon át vezető útjukra." }
    { group:83, id:0, text: "Orvos" }
    { group:83, id:1, text: "Napi egy gránátalma távol tartja az orvost, tartja a mondás. Az orvosok javítják az egészséget, miközben körútjaikat végzik." }
    { group:83, id:2, text: "Ez az orvosi rendelő nem működik, és semmit sem tesz a közösség egészségéért." }
    { group:83, id:3, text: "Ez az orvosi rendelő működik, és a helyi közösség egészséges és életerős." }
    { group:84, id:0, text: "Fogorvos" }
    { group:84, id:1, text: "A homok mindenbe bekerül, még az ételbe is. Az állandó koptatás rengeteg munkát ad az egyiptomi fogorvosoknak." }
    { group:84, id:2, text: "Ez a fogorvosi rendelő nem működik, és a szomszédok fogain látszik az elhanyagoltság." }
    { group:84, id:3, text: "Ez a fogorvosi rendelő működik, és a helyi közösség fogai büszkén ragyognak." }
    { group:85, id:0, text: "Írnokiskola" }
    { group:85, id:1, text: "A gazdagok gyermekeinek a környékbeli iskolákba kell járniuk, hogy megtanuljanak írni és olvasni, ha el akarják érni szüleik társadalmi helyzetét." }
    { group:85, id:2, text: "Ez az iskola jelenleg senkit sem tud oktatni. Hiányoznak az alkalmazottak, a papirusz, vagy mindkettő." }
    { group:85, id:3, text: "Ez az iskola lehetővé teszi a gyermekek számára, hogy elkerüljék a fizikai munkával teli életet, amíg rendelkezik alkalmazottakkal és papirusszal is." }
    { group:86, id:0, text: "Balra" }
    { group:86, id:1, text: "Felül" }
    { group:86, id:2, text: "Jobbra" }
    { group:86, id:3, text: "Alul" }
    { group:87, id:0, text: "Könyvtár" }
    { group:87, id:1, text: "Itt készülnek és itt tárolják a különféle irodalmi műveket. Az írnokok szerint a könyvtárak nélkülözhetetlenek egy fontos város számára." }
    { group:87, id:2, text: "Ez a könyvtár nélkülözi az alkalmazottakat, a papiruszt, vagy mindkettőt. Nem tudja szolgálni a közösséget." }
    { group:87, id:3, text: "Amíg ez a könyvtár rendelkezik alkalmazottakkal és papirusszal, képes szolgálni a közösséget." }
    { group:88, id:0, text: "Rendőrőrs" }
    { group:88, id:1, text: "A rendőrőrsök járőröket küldenek a városba, hogy fenntartsák a rendet. A közbiztonság akkor garantált, ha a járőrök egyenletesen ellenőrzik a várost." }
    { group:88, id:2, text: "A járőrünk szolgálatban van." }
    { group:88, id:3, text: "A járőrünk készül a szolgálatra." }
    { group:88, id:4, text: "Jelenleg teljes a szolgálati beosztásunk. Járőreink mindig figyelnek a bűnözés jeleire." }
    { group:88, id:5, text: "Kissé hiány van járőrökből. Lefedettségünkben talán egy-két napos hiányosságok vannak." }
    { group:88, id:6, text: "Létszámhiánnyal működünk. A bűnözőket akár egyhetes szolgálati hiányok is bátoríthatják." }
    { group:88, id:7, text: "Túl kevés emberünk van. A bűnözők akár két héten keresztül is zavartalanul működhetnek." }
    { group:88, id:8, text: "Csak irodai személyzettel működünk. Gyakran előfordul, hogy egy teljes hónapig nem küldünk járőrt az utcákra." }
    { group:88, id:9, text: "Személyzet nélkül ez az őrs alig több egy rongálók számára kitűzött céltáblánál." }
    { group:88, id:10, text: " lopás idén." }
    { group:88, id:11, text: " aranyat loptak idén." }
    { group:89, id:0, text: "Erőd" }
    { group:89, id:1, text: "Ezt az erődöt Seth átka sújtja, és még időbe telik, mire katonák ismét mernek ide visszatérni." }
    { group:89, id:2, text: "Az erődök a város toborzójától kapnak katonákat. Egy Katonai Akadémia jobban képzett csapatokat biztosítana." }
    { group:90, id:0, text: "Kapuház" }
    { group:90, id:1, text: "A falaknak kapuházra van szükségük, hogy a bevándorlók és kereskedők szabadon közlekedhessenek." }
    { group:91, id:0, text: "Torony" }
    { group:91, id:1, text: "Építs tornyokat a falakba rendszeres időközönként, vagy legalább a sebezhető helyekre. Ha utakhoz kapcsolódnak, a tornyok a város toborzójától kapnak őrséget. A toronyőrök dárdazáport zúdítanak a közeli támadókra, és járőröznek a megfelelő vastagságú falakon." }
    { group:91, id:2, text: "Dolgozók nélkül nem tudunk toronyőröket állomásoztatni, és senkit sem tudunk felfogadni a falak őrzésére." }
    { group:91, id:3, text: "Embereink teljes létszámban szolgálnak, éberek és készen állnak minden fenyegetés visszaverésére." }
    { group:91, id:4, text: "Van karbantartó személyzetünk, de a város védelméhez őrökre van szükségünk a toborzótól." }
    { group:92, id:0, text: "Ozirisz temploma (Mezőgazdaság)" }
    { group:92, id:1, text: "Ozirisz termékenységet hoz a földre, és növekedésre bírja a termést. Engeszteld ki őt, vagy készülj az éhezésre." }
    { group:93, id:0, text: "Ré temploma (A királyság)" }
    { group:93, id:1, text: "A kereskedők jól ismerik Ré kegyének értékét. A kereskedelem biztonságosabb és jövedelmezőbb Ré áldásával, és városod tekintélye is nagyobb lesz." }
    { group:94, id:0, text: "Ptah temploma (Kézművesek)" }
    { group:94, id:1, text: "A munkások és kézművesek Ptahhoz imádkoznak, hogy könnyebb legyen a munkájuk. Amikor Ptah haragszik, egyetlen iparág sincs biztonságban a katasztrófától." }
    { group:95, id:0, text: "Seth temploma (Pusztítás)" }
    { group:95, id:1, text: "Seth vigyáz a katonákra, és bátorságra ösztönzi őket a harcban. Seth áldása nélkül senki sem mer csatába szállni." }
    { group:96, id:0, text: "Bast temploma (Otthon)" }
    { group:96, id:1, text: "Amikor Bast elégedetlen, senki otthona sincs biztonságban. Egyesek még a betegségekért is Bastot hibáztatják." }
    { group:97, id:1, text: "A bazárjaink a királyság bőségét minden közeli polgár számára elérhetővé teszik. Minden otthonnak szüksége van bazárkapcsolatra, bár senki sem akar közvetlenül egy mellett lakni." }
    { group:97, id:2, text: "Ez a bazár nem működik, és semmivel sem látja el a helyi közösséget." }
    { group:97, id:3, text: "Ez a bazár működik, és ellátja a környékbeli otthonok szükségleteit." }
    { group:97, id:4, text: "Ebben a bazárban vannak kereskedők, de jelenleg élelmet vagy eladható árut keresnek." }
    { group:97, id:5, text: "Élelmiszerkészlet:" }
    { group:97, id:6, text: "Különleges rendelések" }
    { group:97, id:7, text: "Bazárutasítások" }
    { group:97, id:8, text: "Vásárlás" }
    { group:97, id:9, text: "Ne vásárolj" }
    { group:97, id:10, text: "A bazár kereskedője itt van, élelemre vár." }
    { group:97, id:11, text: "A bazár kereskedője éppen árukat oszt szét." }
    { group:97, id:12, text: "A bazár kereskedője visszatér feltölteni a készleteket." }
    { group:98, id:1, text: "A teli magtárak létfontosságúak ahhoz, hogy az emberek hasa tele legyen, és segítenek új polgárokat vonzani. Egy magtár bármilyen élelmiszert képes tárolni." }
    { group:98, id:5, text: "Különleges rendelések" }
    { group:98, id:6, text: "Magtárutasítások" }
    { group:98, id:7, text: "Magtár kiürítése" }
    { group:98, id:8, text: "Magtár kiürítésének leállítása" }
    { group:98, id:9, text: "Élelmiszer küldése máshová" }
    { group:99, id:0, text: "Raktárudvar" }
    { group:99, id:1, text: "Mindenféle árunak tárolásra van szüksége. A karavánok a raktárudvarokon kereskednek, a kikötők a közeli raktárudvarokon cserélik el az exportárukat importárukra, és a bazárok is innen töltik fel készleteiket." }
    { group:99, id:2, text: "Különleges rendelések" }
    { group:99, id:3, text: "Raktárudvar-utasítások" }
    { group:99, id:4, text: "Raktárudvar kiürítésének ELINDÍTÁSA" }
    { group:99, id:5, text: "Raktárudvar kiürítésének LEÁLLÍTÁSA" }
    { group:99, id:6, text: "Áruk küldése máshová" }
    { group:99, id:7, text: "Semmit ne fogadjon el" }
    { group:99, id:8, text: "Ne fogadja el" }
    { group:99, id:9, text: "Áru beszerzése" }
    { group:99, id:10, text: "Élelmiszer beszerzése" }
    { group:99, id:11, text: "Kereskedelmi központ" }
    { group:99, id:12, text: "Legyen kereskedelmi központ" }
    { group:99, id:13, text: "FIGYELMEZTETÉS: Ez a raktárudvar teljesen megtelt. Nem tud több árut fogadni." }
    { group:99, id:14, text: "FIGYELMEZTETÉS: Ez a raktárudvar kezd megtelni. Csak a már meglévő árufajtákat tudja fogadni. Új árufajtákat egyáltalán nem vesz át." }
    { group:99, id:15, text: "A szállítónk készen áll új megbízásokra." }
    { group:99, id:16, text: "A szállítónk árut visz máshová." }
    { group:99, id:17, text: "A szállítónk úton van visszafelé." }
    { group:99, id:18, text: "Elfogad" }
    { group:99, id:19, text: "Szerezd be" }
    { group:99, id:20, text: "Élelmiszer kiürítése" }
    { group:99, id:21, text: "Kiürítés " }
    { group:99, id:22, text: "Ez a raktárudvar üres." }
    { group:99, id:23, text: "egység" }
    { group:99, id:24, text: "egység " }
    { group:99, id:25, text: "legfeljebb 1/4-e" }
    { group:99, id:26, text: "legfeljebb 1/2-e" }
    { group:99, id:27, text: "legfeljebb 3/4-e" }
    { group:99, id:28, text: "az összes" }
    { group:99, id:29, text: "Raktárudvar" }
    { group:99, id:30, text: "Magtár" }
    { group:99, id:31, text: "maximum " }
    { group:99, id:32, text: "Feltöltés" }
    { group:99, id:33, text: "A szállítónk éppen árut szerez be" }
    { group:100, id:0, text: "Hajóács" }
    { group:100, id:1, text: "Elegendő munkással a hajóács hadihajókat és halászhajókat épít a város kikötői számára. A hadihajók és szállítóhajók építéséhez fára van szükség; a halászhajók építéséhez nincs szükség nyersanyagra." }
    { group:100, id:2, text: "A gyártás" }
    { group:100, id:3, text: "befejeződött." }
    { group:100, id:4, text: "Jelenleg egyetlen kikötő sem igényli egyik hajónkat sem." }
    { group:100, id:5, text: "A város egyik kikötőjének megrendelésére hadihajót vagy halászhajót építünk." }
    { group:100, id:6, text: "Egy hadihajót javítunk." }
    { group:100, id:7, text: "Tárolt fa:" }
    { group:100, id:8, text: "Fára van szükségünk a hadihajók javításához és építéséhez." }
    { group:100, id:9, text: "Egy hadihajó- vagy szállítóhajó-kikötő hajóépítést rendelt tőlünk, de nincs meg a szükséges faanyagunk." }
    { group:100, id:10, text: "Javításra váró hajóink vannak, de nincs faanyagunk a javításukhoz." }
    { group:101, id:0, text: "Kikötő" }
    { group:101, id:1, text: "A világ minden tájáról érkező kereskedőhajók itt kötnek ki, hogy importárut szállítsanak le és exportárut vegyenek fel. Kikötők nélkül nem lehet vízi kereskedelmet folytatni." }
    { group:101, id:2, text: "Mivel nincs kikötői személyzetünk, nem tudjuk kiszolgálni a kikötött hajót." }
    { group:101, id:3, text: "A kikötött hajót szolgáljuk ki. Mivel azonban kevés a kikötői munkásunk, ez sokáig tarthat." }
    { group:101, id:4, text: "A kikötött hajót szolgáljuk ki, bár ez kissé tovább tart, mint teljes létszám esetén." }
    { group:101, id:5, text: "Teljes létszámmal gyorsan és hatékonyan tudjuk kiszolgálni a kikötött hajót." }
    { group:101, id:6, text: "Bármely hajó, amely itt köt ki, nem talál munkásokat a rakomány be- vagy kirakodásához." }
    { group:101, id:7, text: "Az itt dolgozó kevés kikötői munkásnak sok időbe telne a kikötőbe érkező hajók rakományának be- és kirakodása." }
    { group:101, id:8, text: "Létszámhiánnyal működünk, ezért a kikötőbe érkező hajók rakományának be- és kirakodása a szokásosnál kissé tovább tart." }
    { group:101, id:9, text: "Teljes létszámmal működünk, kikötői munkásaink csak arra várnak, hogy befusson a hajójuk." }
    { group:102, id:0, text: "Halászkikötő" }
    { group:102, id:1, text: "A hajók innen indulnak a hajóácstól, hogy legénységet vegyenek fel és megkezdjék a helyi vizek halászatát. Minden kikötő egy halászhajót képes kiszolgálni." }
    { group:102, id:2, text: "Jelenleg egy hajóácsra várunk, hogy megépítse számunkra a halászhajót." }
    { group:102, id:3, text: "Halászhajónk kifelé tart a halászterületek felé." }
    { group:102, id:4, text: "Hajónk jelenleg a halászterületeken van, és halat zsákmányol." }
    { group:102, id:5, text: "Hajónk most tart vissza a kikötő felé." }
    { group:102, id:6, text: "Feltöltjük halászhajónk készleteit a következő indulás előtt." }
    { group:102, id:7, text: "Halászhajónk a fogással tér vissza a halászterületekről." }
    { group:102, id:8, text: "Halászaink remélik, hogy egyszer valaki felfedez egy halászterületet ezen a vidéken. A kimerült vizekből már nem tudnak tisztességes megélhetést biztosítani." }
    { group:102, id:9, text: "A kereskedelmi felügyelőd elrendelte a halászat leállítását." }
    { group:102, id:10, text: "Halászhajónk nem megy ki abba a szennyezett vízbe!" }
    { group:103, id:0, text: "Palota" }
    { group:103, id:1, text: "Otthonod a város egyik legkívánatosabb lakhelye. Palotád feljogosít arra, hogy fizetést kapj." }
    { group:103, id:2, text: "Deben havonta" }
    { group:103, id:3, text: "A falusi elöljáró fizetése:" }
    { group:103, id:4, text: "A falusi nemes fizetése:" }
    { group:103, id:5, text: "A királyi tudós fizetése:" }
    { group:103, id:6, text: "A királyi írnok fizetése:" }
    { group:103, id:7, text: "A királyi bíró fizetése:" }
    { group:103, id:8, text: "A királyi polgármester fizetése:" }
    { group:103, id:9, text: "A királyi kormányzó fizetése:" }
    { group:103, id:10, text: "A nomarkhosz fizetése:" }
    { group:103, id:11, text: "A kancellár fizetése:" }
    { group:103, id:12, text: "A vezír fizetése:" }
    { group:103, id:13, text: "A fáraó fizetése:" }
    { group:104, id:0, text: "Építészállomás" }
    { group:104, id:1, text: "Az egyiptomi építészek a világ által valaha ismert legfejlettebbek. Éberségük megakadályozza az épületek összeomlását." }
    { group:104, id:2, text: "Építészünk keményen dolgozik." }
    { group:104, id:3, text: "Építészünk indulásra készül." }
    { group:104, id:4, text: "Jelenleg nincs üresjáratunk. Építészeink folyamatosan úton vannak, a város nagyobb épületeit ellenőrzik és javítják." }
    { group:104, id:5, text: "Egy-két napunk van még, mielőtt túlterhelt építészeink ismét az utcákra indulnak." }
    { group:104, id:6, text: "Létszámhiánnyal működünk, ezért egy hetet kell várnunk, mire visszatérő építészeink újra szolgálatba állnak." }
    { group:104, id:7, text: "Súlyos létszámhiánnyal küzdünk, ezért két hét telik el az egyes építészi körutak között." }
    { group:104, id:8, text: "Minimális személyzettel működünk. Alig tudunk havonta egy építészt is kiküldeni." }
    { group:104, id:9, text: "Nincsenek építészeink az alkalmazottak között, ezért a környék ki van szolgáltatva a változó homoknak." }
    { group:105, id:0, text: "Palota" }
    { group:105, id:1, text: "A palota városod egyik legkívánatosabb épülete és a város gazdaságának alapköve. Aranyrögöket vált át debenekre, és a város pénzkészletének egy részét tárolja." }
    { group:105, id:2, text: "A trezorokban ennyi található:" }
    { group:106, id:0, text: "Adószedő irodája" }
    { group:106, id:1, text: "Bár nem ők a város legnépszerűbb dolgozói, az adószedők teszik lehetővé nagyszerű királyságunkat és mindazokat az előnyöket, amelyekben részesülünk." }
    { group:106, id:2, text: "A trezorokban ennyi található:" }
    { group:106, id:3, text: "Adószedőnk a helyiek számláit ellenőrzi." }
    { group:106, id:4, text: "Adószedőnk indulásra készül." }
    { group:106, id:5, text: "Jelenleg teljes hatékonysággal dolgozunk, adószedőink biztosítják, hogy az útvonalukon minden esedékes adót befizessenek." }
    { group:106, id:6, text: "Egy-két napnyi üresjáratunk van, mielőtt visszatérő adószedőink ismét az utcákra indulnak." }
    { group:106, id:7, text: "Létszámhiánnyal működünk, és egy hetet kell várnunk, mielőtt bármelyik adószedő visszatér szolgálatba." }
    { group:106, id:8, text: "Súlyos létszámhiánnyal küzdünk, ezért két hét telik el az adószedői körutak között." }
    { group:106, id:9, text: "Ilyen kevés dolgozóval ebben az irodában a helyi polgárok elkerülhetik adóik jelentős részének befizetését." }
    { group:106, id:10, text: "Adószedő személyzet nélkül ez az iroda semmivel sem járul hozzá a város kincstárához." }
    { group:106, id:11, text: "A városodnak palotára van szüksége, mielőtt adókat szedhetnél." }
    { group:106, id:12, text: "A városodnak működő palotára van szüksége ahhoz, hogy adókat szedhess." }
    { group:107, id:0, text: "Vízemelő" }
    { group:107, id:1, text: "Ez a vízemelő nagy mennyiségű vizet képes szivattyúzni, ha öntözőcsatornák kapcsolódnak az elülső vagy hátsó zsilipjeihez." }
    { group:107, id:2, text: "Ez a vízemelő nem működik. Kérd meg a munkafelügyelődet, hogy osszon több munkást a vízellátási szolgálatokhoz." }
    { group:107, id:3, text: "Ennek a vízemelőnek víz mellett kell lennie, vagy egy működő vízemelőhöz kell öntözőcsatornával kapcsolódnia, mielőtt működni kezd." }
    { group:108, id:0, text: "Vízellátás" }
    { group:108, id:1, text: "A vízhordók ebből a kedvező forrásból tiszta vizet szereznek, és javítják az egészséget és a közérzetet, miközben útvonalaikon a házakhoz szállítják." }
    { group:108, id:2, text: "Személyzetünk folyamatosan tiszta vizet szállít a helyi lakosságnak." }
    { group:108, id:3, text: "Kissé hiány van vízhordókból. Lefedettségünkben talán egy-két napos hiányosságok vannak." }
    { group:108, id:4, text: "Létszámhiánnyal működünk, és akár egyhetes veszélyes hiányok is előfordulnak vízszállítási ciklusunkban." }
    { group:108, id:5, text: "Túl kevés munkásunk van. Néha akár két héten keresztül sem érkezik vízszállítás." }
    { group:108, id:6, text: "Csak minimális személyzettel működünk. Gyakran előfordul, hogy egy teljes hónapig nem szállítunk vizet." }
    { group:108, id:7, text: "Szállító személyzet nélkül ez a létesítmény akár egy száraz gödör is lehetne a földben." }
    { group:110, id:0, text: "Jósda? Ide kerülne a szentély?" }
    { group:110, id:1, text: "Ez a szentély kívánatosabbá teszi a közeli otthonokat, és minden istent megelégedéssel tölt el. Nem alkalmaz papokat, és nem biztosít hozzáférést egyetlen konkrét istenhez sem." }
    { group:111, id:0, text: "Égő rom" }
    { group:111, id:1, text: "A tűzoltók nem értek ide időben, hogy megmentsék az épületet. Amikor a tüzek maguktól kialszanak, ezen a helyen már csak törmelék marad." }
    { group:112, id:0, text: "Gabonafarm" }
    { group:112, id:1, text: "A gabonát magtárakban kell tárolni, hogy a népedet elláthasd vele, vagy raktárudvarokban, ha exportra szánod." }
    { group:112, id:2, text: "A termelés" }
    { group:112, id:3, text: "befejeződött." }
    { group:112, id:4, text: "A kereskedelmi felügyelőd elrendelte a gabonatermesztés leállítását." }
    { group:112, id:5, text: "Ezen a földön nincsenek munkások. Még a gyomok is nehezen nőnek itt." }
    { group:112, id:6, text: "Ezen a földön minden szükséges munkás rendelkezésre áll. A jelenlegi termékenység mellett maximális termést ér el." }
    { group:112, id:7, text: "Ez a föld termelékenyebb lehetne, ha több munkása lenne." }
    { group:112, id:8, text: "Ez a föld létszámhiánnyal működik. Munkásai nem termelnek annyi élelmet, amennyit tudnának." }
    { group:112, id:9, text: "Nagyon kevés földműves dolgozik itt. Ennek következtében kevés gabona terem." }
    { group:112, id:10, text: "Alig van munkás ezen a földön, ezért ebben az évszakban nagyon kevés gabonát fog termelni." }
    { group:112, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása, és időbe telik, mire helyreáll." }
    { group:112, id:12, text: "A föld" }
    { group:112, id:13, text: "termékeny." }
    { group:112, id:14, text: "A következő gabonatermés még ennyi idő múlva lesz:" }
    { group:113, id:0, text: "Salátafarm" }
    { group:113, id:1, text: "A saláta hozzájárul a néped egészségéhez és boldogságához szükséges kiegyensúlyozott étrendhez. A magtárak a helyi fogyasztásra szánt salátát tárolják, a raktárudvarok pedig az exportfelesleget veszik át." }
    { group:113, id:2, text: "A termelés" }
    { group:113, id:3, text: "befejeződött." }
    { group:113, id:4, text: "A kereskedelmi felügyelő elrendelte a salátatermesztés beszüntetését." }
    { group:113, id:5, text: "Ezen a földön nincsenek munkások. Semmit sem ültettek." }
    { group:113, id:6, text: "Ezen a földön minden szükséges munkás rendelkezésre áll. Annyi salátát termeszt, amennyit a termékenysége lehetővé tesz." }
    { group:113, id:7, text: "Ez a föld nem teljes kapacitással működik, ezért a termés kisebb, mint amekkora lehetne." }
    { group:113, id:8, text: "Ez a föld létszámhiánnyal működik. A salátafejek kisebbek és kevesebbek, mint amennyit termelhetne." }
    { group:113, id:9, text: "Nagyon kevés földműves dolgozik itt. A salátatermés ennek nagyon meg fogja látni a kárát." }
    { group:113, id:10, text: "Szinte nincs földműves, aki gondozza a termést, ezért ez nem lesz kiemelkedő salátaév." }
    { group:113, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása, és időbe telik, mire helyreáll." }
    { group:113, id:12, text: "A föld" }
    { group:113, id:13, text: "termékeny." }
    { group:113, id:14, text: "A következő salátatermés még ennyi idő múlva lesz:" }
    { group:114, id:0, text: "Gránátalmafarm" }
    { group:114, id:1, text: "A gránátalma javítja a nép egészségéhez és boldogságához szükséges kiegyensúlyozott étrendet. A magtárak a helyi fogyasztásra szánt gránátalmát tárolják, a raktárudvarok pedig exportálhatják a felesleget." }
    { group:114, id:2, text: "A termelés" }
    { group:114, id:3, text: "befejeződött." }
    { group:114, id:4, text: "A kereskedelmi felügyelő parancsára a gránátalmatermesztés megszűnt." }
    { group:114, id:5, text: "Ezen a gyümölcsösön nincsenek munkások, a fák terméketlenek és göcsörtösek." }
    { group:114, id:6, text: "Ezen a gyümölcsösön minden szükséges munkás rendelkezésre áll. A fák annyi gyümölcsöt teremnek, amennyit a föld termékenysége lehetővé tesz." }
    { group:114, id:7, text: "Ez a gyümölcsös nem teljes kapacitással működik, ezért az idei termés kissé gyengébb, mint amilyen lehetne." }
    { group:114, id:8, text: "Ez a gyümölcsös létszámhiánnyal működik. Kevesebb gránátalmát termel, mint amennyit tudna." }
    { group:114, id:9, text: "Nagyon kevesen dolgoznak ezen a gyümölcsösön. A gránátalmatermés csekély lesz." }
    { group:114, id:10, text: "Alig van munkás ezen a gyümölcsösön, ezért a gránátalmatermés meglehetősen kiábrándító lesz." }
    { group:114, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása, és időbe telik, mire helyreáll." }
    { group:114, id:12, text: "A föld" }
    { group:114, id:13, text: "termékeny." }
    { group:114, id:14, text: "A következő gránátalmatermés még ennyi idő múlva lesz:" }
    { group:115, id:0, text: "Lenfarm" }
    { group:115, id:1, text: "A lent a takácshoz kerül, aki feldolgozza a rostokat és vásznat sző belőlük a holttestek balzsamozásához a halottemberek számára, vagy exportra." }
    { group:115, id:2, text: "A termelés" }
    { group:115, id:3, text: "befejeződött." }
    { group:115, id:4, text: "A kereskedelmi felügyelőd elrendelte a lentermesztés leállítását." }
    { group:115, id:5, text: "Ezen a földön nincsenek munkások. Itt nem nőhet len." }
    { group:115, id:6, text: "Ezen a földön minden szükséges munkás rendelkezésre áll. A mezőket kék lenvirágok szőnyege borítja." }
    { group:115, id:7, text: "Ez a föld nem teljes kapacitással működik. Több munkással jobb lehetne a lentermelés." }
    { group:115, id:8, text: "Ez a föld létszámhiánnyal működik. A len növényei nem olyan sűrűek és erősek, mint amilyenek lehetnének." }
    { group:115, id:9, text: "Nagyon kevesen dolgoznak itt. A lentermés ennek következtében gyengébb lesz." }
    { group:115, id:10, text: "Alig van munkás ezen a földön, ezért a talaj nagyrészt terméketlen." }
    { group:115, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása, és időbe telik, mire helyreáll." }
    { group:115, id:12, text: "A föld" }
    { group:115, id:13, text: "termékeny." }
    { group:115, id:14, text: "A következő lenbetakarítás még ennyi idő múlva lesz:" }
    { group:116, id:0, text: "Nádgyűjtő" }
    { group:116, id:1, text: "A nádgyűjtők innen indulnak a mocsarakba, hogy papiruszhoz szükséges nádat gyűjtsenek, amely nélkül az oktatás lehetetlen lenne." }
    { group:116, id:2, text: "Tárolt nád:" }
    { group:116, id:3, text: "befejeződött." }
    { group:116, id:4, text: "A nádgyűjtést a kereskedelmi felügyelő parancsára leállították." }
    { group:116, id:5, text: "Ezen a helyen nincsenek munkások a nád begyűjtésére." }
    { group:116, id:6, text: "Ezen a helyen minden szükséges munkás rendelkezésre áll. Egyetlen nád sincs biztonságban." }
    { group:116, id:7, text: "Ez a hely nincs teljesen kihasználva munkaerő szempontjából, ezért a nádgyűjtés kissé lelassult." }
    { group:116, id:8, text: "Ez a hely létszámhiánnyal működik, ezért a nád vágása lassan halad." }
    { group:116, id:9, text: "Nagyon kevesen dolgoznak itt, és kevés nádat vágnak le." }
    { group:116, id:10, text: "Ilyen kevés gyűjtő alkalmazásával szinte semennyi nád nem kerül betakarításra." }
    { group:116, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása, és időbe telik, mire helyreáll." }
    { group:116, id:12, text: "A föld" }
    { group:116, id:13, text: "termékeny." }
    { group:116, id:14, text: "A következő nádaratás még ennyi idő múlva lesz:" }
    { group:117, id:0, text: "Marhatenyésztő telep" }
    { group:117, id:1, text: "A jól táplált polgárok húst szeretnének az étrendjükben. A húst a helyi fogyasztásra magtárakban lehet tárolni, vagy export céljára raktárudvarokba lehet szállítani." }
    { group:117, id:2, text: "A termelés" }
    { group:117, id:3, text: "befejeződött." }
    { group:117, id:4, text: "A kereskedelmi felügyelő rendelete alapján a marhatenyésztés megszűnt." }
    { group:117, id:5, text: "Ezen a telepen nincsenek munkások. Minden állat elszökött vagy elpusztult." }
    { group:117, id:6, text: "Ezen a telepen minden szükséges munkás rendelkezésre áll. Szalmával elegendő mennyiségű húst tud termelni." }
    { group:117, id:7, text: "Ennek a telepnek több munkást kell alkalmaznia, hogy hatékonyan termelhessen húst." }
    { group:117, id:8, text: "Ez a telep létszámhiánnyal működik. Nem képes elérni a maximális termelési szintjét." }
    { group:117, id:9, text: "Nagyon kevesen dolgoznak ezen a telepen. A lehetséges hústermelése alacsony." }
    { group:117, id:10, text: "Ilyen kevés munkással ez a telep csak nagyon kevés marhát tud nevelni." }
    { group:117, id:11, text: "Ezt a földet megkárosította a közelmúlt sáskajárása. A marhák nem tudnak itt megfelelően fejlődni, amíg helyre nem áll." }
    { group:117, id:12, text: "A föld" }
    { group:117, id:13, text: "termékeny." }
    { group:118, id:0, text: "Egyszerű kőbánya" }
    { group:118, id:1, text: "Itt egyszerű követ bányászhatsz a földből. Mivel egész Egyiptomban folyamatosan emelkednek a monumentális építmények, jó építőkőre általában mindig találni vevőt, még akkor is, ha neked nincs rá szükséged." }
    { group:118, id:2, text: "A termelés" }
    { group:118, id:3, text: "befejeződött." }
    { group:118, id:4, text: "A kereskedelmi felügyelő elrendelte a kőfejtés leállítását." }
    { group:118, id:5, text: "Ebben a kőbányában nincsenek munkások, akik követ fejtenének a földből." }
    { group:118, id:6, text: "Ebben a kőbányában minden szükséges munkás rendelkezésre áll, és sok tonna egyszerű követ termel." }
    { group:118, id:7, text: "Ez a kőbánya a kisebb munkaerőhiány miatt nem teljes kapacitással működik." }
    { group:118, id:8, text: "Ez a kőbánya létszámhiánnyal működik, ezért a kőtömbök előállítása tovább tart a kelleténél." }
    { group:118, id:9, text: "Nagyon kevesen dolgoznak ebben a kőbányában. Ennek következtében a termelés nagyon lassú." }
    { group:118, id:10, text: "Alig van munkás ebben a kőbányában, ezért a termelés gyakorlatilag leállt. A következő évben csak kevés követ fog kitermelni." }
    { group:119, id:0, text: "Mészkőbánya" }
    { group:119, id:1, text: "Finom mészkövet bányászhatsz itt műemlékek építéséhez vagy exportra." }
    { group:119, id:2, text: "A termelés" }
    { group:119, id:3, text: "befejeződött." }
    { group:119, id:4, text: "A kereskedelmi felügyelőd elrendelte a mészkőfejtés leállítását." }
    { group:119, id:5, text: "Ebben a kőbányában nincsenek munkások, ezért nem termel mészkövet." }
    { group:119, id:6, text: "Ebben a kőbányában minden szükséges munkás rendelkezésre áll, és annyi mészkövet termel, amennyit csak lehet." }
    { group:119, id:7, text: "Ez a kőbánya nem teljes kapacitással működik. Több munkással nagyobb lehetne a termelés." }
    { group:119, id:8, text: "Ez az épület létszámhiánnyal működik. A mészkőtömbök kivágása tovább tart a kelleténél." }
    { group:119, id:9, text: "Nagyon kevesen dolgoznak ebben az épületben. Ennek következtében a termelés túl lassú." }
    { group:119, id:10, text: "Alig van itt munkás, ezért a mészkőtermelés szinte nem is létezik." }
    { group:120, id:0, text: "Favágó" }
    { group:120, id:1, text: "A fának számos felhasználása van, a műemléképítéstől a hajóépítésig, és a királyság minden részén nagy a kereslet iránta." }
    { group:120, id:2, text: "Tárolt:" }
    { group:120, id:3, text: "Nyers fa." }
    { group:120, id:4, text: "A fakitermelést a kereskedelmi felügyelő parancsára leállították." }
    { group:120, id:5, text: "Ezen a létesítményen nincsenek munkások, és semmivel sem járul hozzá a város gazdaságához." }
    { group:120, id:6, text: "Ebben az épületben minden szükséges munkás rendelkezésre áll. Maximális hatékonysággal termeli ki a fát." }
    { group:120, id:7, text: "Ez a favágó nincs teljesen feltöltve munkásokkal, ezért a fa kitermelése kisebb, mint amekkora lehetne." }
    { group:120, id:8, text: "Ez az iparág létszámhiánnyal működik, ezért a fakitermelés tovább tart a kelleténél." }
    { group:120, id:9, text: "Nagyon kevesen dolgoznak ezen a telepen. Ennek következtében a fatermelés nagyon lassú." }
    { group:120, id:10, text: "Alig van favágó ezen a helyen, ezért a fakitermelés gyakorlatilag leállt." }
    { group:121, id:0, text: "Agyagbánya" }
    { group:121, id:1, text: "Bányássz agyagot kereskedelemhez vagy a fazekasok ellátására. Az emberek számtalan módon használják a fazekasárut, és gyakran nyereségesen kereskedhetsz vele más városokkal." }
    { group:121, id:2, text: "A termelés" }
    { group:121, id:3, text: "befejeződött." }
    { group:121, id:4, text: "A kereskedelmi felügyelőd leállította az agyagásást." }
    { group:121, id:5, text: "Ebben a bányagödörben nincsenek munkások, akik agyagot ásnának." }
    { group:121, id:6, text: "Ebben a bányagödörben minden szükséges munkás rendelkezésre áll, és nagy mennyiségű agyagot termel." }
    { group:121, id:7, text: "Ez a bányagödör nem teljes kapacitással működik. Emiatt az agyagtermelés kissé lassabb." }
    { group:121, id:8, text: "Ez a bányagödör létszámhiánnyal működik, ezért az agyag előállítása tovább tart a kelleténél." }
    { group:121, id:9, text: "Olyan kevesen dolgoznak ebben a bányagödörben, hogy az agyagtermelés rendkívül lassú." }
    { group:121, id:10, text: "Alig van ásómunkás ebben a bányagödörben, ezért a következő évben nagyon kevés agyagot fog termelni." }
    { group:122, id:0, text: "Sörfőzde" }
    { group:122, id:1, text: "A sörfőzők árpából sört készítenek, amely nélkül a szenetházak üresek lennének, és a város ünnepségei unalmasak volnának. A sör igen keresett kereskedelmi áru." }
    { group:122, id:2, text: "A termelés" }
    { group:122, id:3, text: "befejeződött." }
    { group:122, id:4, text: "A kereskedelmi felügyelő rendelete leállította a sörfőzést." }
    { group:122, id:5, text: "Ebben a sörfőzdében nincsenek alkalmazottak. Innen nem kerül ki sör." }
    { group:122, id:6, text: "Teljes létszámmal ez a sörfőzde teljes sebességgel dolgozik, hogy oltsa Egyiptom szomját." }
    { group:122, id:7, text: "Ez a sörfőzde nem teljes kapacitással működik. A sörtermelés kissé lassabb a lehetségesnél." }
    { group:122, id:8, text: "Ez a sörfőzde létszámhiánnyal működik, ezért a sör előállítása jóval tovább tart a kelleténél." }
    { group:122, id:9, text: "Nagyon kevesen dolgoznak ebben a sörfőzdében. Emiatt a sörtermelés nagyon lassú." }
    { group:122, id:10, text: "Alig van sörfőzőnk, ezért ez a sörfőzde a következő évben szinte egyáltalán nem fog sört termelni." }
    { group:122, id:11, text: "Ez a sörfőzde nem tud sört készíteni, amíg nem kap árpaszállítmányt egy raktárudvarból vagy egy farmról." }
    { group:122, id:12, text: "Tárolt árpa:" }

    { group:123, id:0, text: "Takácsműhely" }
    { group:123, id:1, text: "Itt dolgozzák fel a lent vászonná, amelyre a halottembereknek a balzsamozáshoz van szükségük. A vászonnal nyereségesen is lehet kereskedni." }
    { group:123, id:2, text: "A termelés" }
    { group:123, id:3, text: "befejeződött." }
    { group:123, id:4, text: "A kereskedelmi felügyelőd elrendelte a vászontermelés befejezését." }
    { group:123, id:5, text: "Ebben a takácsműhelyben nincsenek munkások, ezért egyáltalán nem tud vásznat előállítani." }
    { group:123, id:6, text: "Ez a takácsműhely teljes létszámmal működik, és bőségesen termel kiváló minőségű vásznat." }
    { group:123, id:7, text: "Ennek a takácsműhelynek több munkásra lenne szüksége, hogy elérje teljes vászontermelési kapacitását." }
    { group:123, id:8, text: "Ez a takácsműhely létszámhiánnyal működik, ezért a vászon előállítása lassabb a kelleténél." }
    { group:123, id:9, text: "Nagyon kevesen dolgoznak ebben a takácsműhelyben. Emiatt a vászontermelés lassú." }
    { group:123, id:10, text: "Alig van alkalmazott, ezért ez a takácsműhely a következő évben szinte egyáltalán nem fog vásznat termelni." }
    { group:123, id:11, text: "Ez a műhely nem tud vásznat készíteni, amíg nem kap lenszállítmányt egy raktárudvarból vagy egy farmról." }
    { group:123, id:12, text: "Tárolt len:" }
    { group:124, id:0, text: "Fegyverkovács" }
    { group:124, id:1, text: "A fegyverkovácsok a rezet lándzsákká alakítják, amelyeket szép haszonnal eladhatsz, vagy saját katonai egységeid felszerelésére használhatsz." }
    { group:124, id:2, text: "A termelés" }
    { group:124, id:3, text: "befejeződött." }
    { group:124, id:4, text: "A kereskedelmi felügyelőd elrendelte a fegyvergyártás leállítását." }
    { group:124, id:5, text: "Ebben a fegyverkovács műhelyben nincsenek alkalmazottak, ezért nem készülnek fegyverek." }
    { group:124, id:6, text: "Ebben a műhelyben minden szükséges dolgozó rendelkezésre áll, így a lehető legtöbb fegyvert állítja elő." }
    { group:124, id:7, text: "Ez a fegyverkovács műhely nem teljes létszámmal működik, ezért a fegyvergyártás kissé lassabb a lehetségesnél." }
    { group:124, id:8, text: "Ez a műhely létszámhiánnyal működik. A fegyverek elkészítése tovább tart a kelleténél." }
    { group:124, id:9, text: "Nagyon kevesen dolgoznak ebben a fegyverkovács műhelyben. A fegyvergyártás nagyon lassú." }
    { group:124, id:10, text: "Alig van alkalmazott, ezért ez a fegyverkovács műhely csak nagyon kevés fegyverrel járul hozzá a város védelméhez." }
    { group:124, id:11, text: "Ennek a fegyverkovács műhelynek rézre van szüksége egy raktárudvarból vagy egy rézbányából a fegyvergyártáshoz." }
    { group:124, id:12, text: "Tárolt réz:" }

    { group:125, id:0, text: "Ékszerész" }
    { group:125, id:1, text: "Az itt dolgozó mesterek a drágakövekből ékszereket (luxuscikket) készítenek. Egyes polgárok vágynak ékszerekre, a felesleget pedig gyakran exportálhatod, bár ritkán ér sokat." }
    { group:125, id:2, text: "A termelés" }
    { group:125, id:3, text: "befejeződött." }
    { group:125, id:4, text: "A kereskedelmi felügyelő elrendelte az ékszergyártás leállítását." }
    { group:125, id:5, text: "Ebben az ékszerészműhelyben nincsenek alkalmazottak, ezért semmit sem termel." }
    { group:125, id:6, text: "Ez a műhely teljes létszámmal működik, és a lehető legtöbb ékszert készíti." }
    { group:125, id:7, text: "Ebben a műhelyben még vannak betöltetlen állások. Az ékszertermelés javulni fog, ha ezeket betöltik." }
    { group:125, id:8, text: "Ez a műhely létszámhiánnyal működik, ezért az ékszerek elkészítése tovább tart a kelleténél." }
    { group:125, id:9, text: "Nagyon kevés mester dolgozik itt. Emiatt az ékszertermelés nagyon lassú." }
    { group:125, id:10, text: "Alig van mesterember, ezért ez az ékszerész a következő évben csak kevés luxuscikket fog előállítani." }
    { group:125, id:11, text: "Ennek a műhelynek drágakőszállítmányra van szüksége egy raktárudvarból vagy egy drágakőbányából az ékszerkészítéshez." }
    { group:125, id:12, text: "Tárolt drágakövek:" }
    { group:126, id:0, text: "Fazekasműhely" }
    { group:126, id:1, text: "Itt a fazekasok agyagból edényeket készítenek, amelyeket a polgárok áruk tárolására használnak. Kereskedj cserépedényekkel, vagy hagyd, hogy a bazárok szétosszák őket, hogy az emberek jobb házakat építhessenek." }
    { group:126, id:2, text: "A termelés" }
    { group:126, id:3, text: "befejeződött." }
    { group:126, id:4, text: "A kereskedelmi felügyelő rendeletére a cserépedények gyártása leállt." }
    { group:126, id:5, text: "Ebben a fazekasműhelyben nincsenek alkalmazottak. Egyetlen edény sem készül." }
    { group:126, id:6, text: "Ebben a fazekasműhelyben minden szükséges dolgozó rendelkezésre áll, és a lehető legtöbb cserépedényt készíti." }
    { group:126, id:7, text: "Ebben a fazekasműhelyben még vannak betöltetlen állások. Emiatt a cserépedények gyártása kissé lassabb." }
    { group:126, id:8, text: "Ez a műhely létszámhiánnyal működik, ezért a cserépedények előállítása tovább tart a kelleténél." }
    { group:126, id:9, text: "Nagyon kevesen dolgoznak itt, ezért a cserépedények gyártása nagyon lassú." }
    { group:126, id:10, text: "Alig van alkalmazott, ezért ez a fazekasműhely a következő évben szinte egyáltalán nem fog cserépedényt előállítani." }
    { group:126, id:11, text: "Ennek a műhelynek agyagszállítmányra van szüksége egy raktárudvarból vagy egy agyagbányából a cserépedények készítéséhez." }
    { group:126, id:12, text: "Tárolt agyag:" }

    { group:127, id:0, text: "Lakóház" }
    { group:127, id:1, text: "Tesztmód KI" }
    { group:127, id:2, text: "Tesztmód BE" }
    { group:127, id:3, text: "Vonzó környezet" }
    { group:127, id:4, text: "Szórakozás" }
    { group:127, id:5, text: "Víz" }
    { group:127, id:6, text: "Vallás" }
    { group:127, id:7, text: "Oktatás" }
    { group:127, id:8, text: "Bazár elérhetősége" }
    { group:127, id:9, text: "Fogorvos elérhetősége" }
    { group:127, id:10, text: "Orvos elérhetősége" }
    { group:127, id:11, text: "Egészség" }
    { group:127, id:12, text: "Élelmiszertípusok" }
    { group:127, id:13, text: "Cserépedény szükséges" }
    { group:127, id:14, text: "Vászon szükséges" }
    { group:127, id:15, text: "Luxuscikk szükséges" }
    { group:127, id:16, text: "Sör szükséges" }
    { group:127, id:17, text: "Jelenleg" }
    { group:127, id:18, text: "erre fejlődik:" }
    { group:127, id:19, text: "igényel:" }
    { group:127, id:20, text: "lakó" }
    { group:127, id:21, text: " fővel több a kelleténél." }
    { group:127, id:22, text: "Szabad hely még" }
    { group:127, id:23, text: "Adószedő még nem járt itt. Nem fizet adót." }
    { group:127, id:24, text: "Eddig termelt" }
    { group:127, id:25, text: "adóként." }
    { group:127, id:26, text: "A lakók szerint egyáltalán nincs bűnözés." }
    { group:127, id:27, text: "Ez egy békés környék." }
    { group:127, id:28, text: "Van némi bűnözés, de semmi komoly." }
    { group:127, id:29, text: "A bűnözés kezd problémává válni." }
    { group:127, id:30, text: "A magas bűnözési ráta elriasztja a helyieket." }
    { group:127, id:31, text: "Törvénytelen környék. Az emberek féltik a biztonságukat." }
    { group:127, id:32, text: "Ez a tolvajok melegágya." }
    { group:127, id:33, text: "A kunyhóknak a bazárból származó élelemre és vonzó környezetre van szükségük a fejlődéshez." }
    { group:127, id:34, text: "Lakóház FREE" }
    { group:127, id:35, text: "Lakóház FREE" }
    { group:127, id:36, text: "Lakóház FREE" }
    { group:127, id:37, text: "Lakóház FREE" }
    { group:127, id:38, text: "Lakóház FREE" }
    { group:127, id:39, text: "Lakóház FREE" }
    { group:127, id:40, text: "Ez a ház hamarosan visszafejlődik. A környék csökkenő vonzereje visszaveti." }
    { group:127, id:42, text: "Ez a ház hamarosan visszafejlődik, mert nem jár hozzá vízhordó." }
    { group:127, id:43, text: "Ez a ház hamarosan visszafejlődik, mert a környéken egyáltalán nincs szórakozási lehetőség." }
    { group:127, id:44, text: "Ez a ház hamarosan visszafejlődik, mert alig van szórakozási lehetőség a környéken." }
    { group:127, id:45, text: "Ez a ház hamarosan visszafejlődik, mert túl kevés a szórakozási lehetőség a környéken." }
    { group:127, id:46, text: "Ez a ház hamarosan visszafejlődik. Van ugyan némi szórakozási lehetőség a környéken, de nem elegendő." }
    { group:127, id:47, text: "Ez a ház hamarosan visszafejlődik. Jó a szórakozási kínálat a környéken, de nem elég változatos." }
    { group:127, id:48, text: "Ez a ház hamarosan visszafejlődik. Bár kiváló a szórakozási kínálat, a helyszínek túlzsúfoltak vagy nem elég változatosak az igényesebb írnokréteg számára." }
    { group:127, id:49, text: "Ez a ház hamarosan visszafejlődik, mert mostanában nem kapott élelmiszert a helyi bazárból." }
    { group:127, id:50, text: "Ez a ház hamarosan visszafejlődik, mert jelenleg csak egyféle élelmiszerhez jut hozzá a helyi bazárból. Ez elriasztja a tehetősebb lakókat." }
    { group:127, id:51, text: "Ez a ház hamarosan visszafejlődik, mert jelenleg csak kétféle élelmiszert kap a helyi bazárból. Ez nem elég az írnokréteg számára." }
    { group:127, id:52, text: "Ez a ház hamarosan visszafejlődik. Elvesztette a bazárhoz való hozzáférését." }
    { group:127, id:53, text: "Ez a ház hamarosan visszafejlődik. Bár eléri a bazárt, a bazár nehezen jut élelmiszer-utánpótláshoz." }
    { group:127, id:54, text: "Ez a ház hamarosan visszafejlődik, mert elvesztette az írnokiskola és a könyvtár által biztosított alapfokú oktatást." }
    { group:127, id:55, text: "Ez a ház hamarosan visszafejlődik. Az oktatási ellátása romlott, mert elvesztette a könyvtárhoz való hozzáférését." }
    { group:127, id:56, text: "Ez a ház hamarosan visszafejlődik. Az oktatási ellátása romlott, mert elvesztette az írnokiskolához való hozzáférését." }
    { group:127, id:57, text: "Ez a ház hamarosan visszafejlődik. Korábban kiváló oktatási ellátása romlott, mert elvesztette a felsőfokú oktatáshoz való hozzáférését." }
    { group:127, id:58, text: "Ez a ház hamarosan visszafejlődik, mert nincs hozzáférése a bíróság bíráihoz." }
    { group:127, id:59, text: "Ez a ház hamarosan visszafejlődik. Elfogyott a cserépedénye, a helyi bazár ellátása pedig legfeljebb rendszertelen." }
    { group:127, id:60, text: "Ez a ház hamarosan visszafejlődik, mert elvesztette a helyi vallási létesítményekhez való hozzáférését." }
    { group:127, id:61, text: "Ez a ház hamarosan visszafejlődik. Vallási ellátása egyetlen isten templomára csökkent." }
    { group:127, id:62, text: "Ez a ház hamarosan visszafejlődik. Korábban kiváló vallási ellátása már csak két isten templomára terjed ki." }
    { group:127, id:63, text: "Ez a ház hamarosan visszafejlődik, mert elvesztette a fogorvosi ellátást." }
    { group:127, id:64, text: "Ez a ház hamarosan visszafejlődik, mert egészségügyi ellátása siralmas. Nemcsak balzsamozóház nincs a közelben, de az orvosi ellátás sem megfelelő." }
    { group:127, id:65, text: "Ez a ház hamarosan visszafejlődik, mert romlott az egészségügyi ellátása. Az orvosi ellátás megfelelő, de nincs a közelben balzsamozóház." }
    { group:127, id:66, text: "Ez a ház hamarosan visszafejlődik, mert romlott az egészségügyi ellátása. Van a közelben balzsamozóház, de nehéz orvost találni." }
    { group:127, id:67, text: "Ez a ház hamarosan visszafejlődik. Elfogyott a vászna, a helyi bazár ellátása pedig legfeljebb rendszertelen." }
    { group:127, id:68, text: "unused8" }
    { group:127, id:69, text: "Ez a ház hamarosan visszafejlődik. Elfogyott a söre, a helyi bazár ellátása pedig legfeljebb rendszertelen." }
    { group:127, id:70, text: "Ez a ház addig nem fejlődhet tovább, amíg a környék vonzereje nem javul." }
    { group:127, id:71, text: "Ez a ház nem fejlődhet tovább, mert még a legegyszerűbb vízforráshoz sem fér hozzá." }
    { group:127, id:72, text: "Ez a ház nem fejlődhet tovább, mert nem részesül vízhordó szolgáltatásában." }
    { group:127, id:73, text: "Ez a ház nem fejlődhet tovább, mert a környéken egyáltalán nincs szórakozási lehetőség." }
    { group:127, id:74, text: "Ez a ház nem fejlődhet tovább, mert alig van szórakozási lehetőség a környéken." }
    { group:127, id:75, text: "Ez a ház nem fejlődhet tovább, mert túl kevés a szórakozási lehetőség a környéken." }
    { group:127, id:76, text: "Ez a ház nem fejlődhet tovább. Van ugyan némi szórakozási lehetőség a környéken, de nem elegendő." }
    { group:127, id:77, text: "Ez a ház nem fejlődhet tovább. Jó a szórakozási kínálat a környéken, de nem elég változatos." }
    { group:127, id:78, text: "Ez a ház nem fejlődhet tovább. Bár kiváló a szórakozási kínálat, a helyszínek túlzsúfoltak vagy nem elég változatosak az igényesebb írnokréteg számára." }
    { group:127, id:79, text: "Ez a ház nem fejlődhet tovább, mert élelmiszerre van szüksége a helyi bazárból." }
    { group:127, id:80, text: "Ez a ház nem fejlődhet tovább, mert szüksége van egy második élelmiszerfajtára a helyi bazárból, hogy tehetősebb egyiptomiak költözzenek ide." }
    { group:127, id:81, text: "Ez a ház nem fejlődhet tovább, mert szüksége van egy harmadik élelmiszerfajtára a helyi bazárból, hogy magasabb társadalmi osztályba tartozó egyiptomiak költözzenek ide." }
    { group:127, id:82, text: "Ez a ház nem fejlődhet tovább, mert nem éri el a helyi bazárt." }
    { group:127, id:83, text: "Ez a ház nem fejlődhet tovább. Bár eléri a helyi bazárt, a bazár nehezen jut élelmiszer-utánpótláshoz." }
    { group:127, id:84, text: "Ez a ház nem fejlődhet tovább, mert nem rendelkezik az írnokiskola vagy a könyvtár által biztosított alapfokú oktatással." }
    { group:127, id:85, text: "Ez a ház nem fejlődhet tovább, mert oktatási ellátását könyvtár hozzáféréssel kell javítani." }
    { group:127, id:86, text: "Ez a ház nem fejlődhet tovább, mert oktatási ellátását írnokiskola hozzáféréssel kell javítani." }
    { group:127, id:87, text: "Fel nem használt sor: a fejlődést az akadémia hiánya akadályozza." }
    { group:127, id:88, text: "Ez a ház nem fejlődhet tovább, mert nincs hozzáférése a bíróság bíráihoz." }
    { group:127, id:89, text: "Ez a ház nem fejlődhet tovább. Cserépedényre van szüksége, amelyet a helyi bazárnak kell biztosítania, mielőtt tehetősebb lakók költöznének ide." }
    { group:127, id:90, text: "Ez a ház nem fejlődhet tovább, mert nem fér hozzá semmilyen helyi vallási létesítményhez." }
    { group:127, id:91, text: "Ez a ház csak egyetlen isten templomaihoz fér hozzá. Nem fejlődhet tovább, amíg lakói nem tiszteleghetnek a többi isten előtt is." }
    { group:127, id:92, text: "Ez a ház csak két isten templomaihoz fér hozzá. Nem fejlődhet tovább, amíg lakói nem tiszteleghetnek a többi isten előtt is." }
    { group:127, id:93, text: "Ez a ház nem fejlődhet tovább, mert nincs a közelben Fogorvos." }
    { group:127, id:94, text: "Ez a ház nem fejlődhet tovább, mert gyakorlatilag nincs egészségügyi ellátása. Nem fér hozzá Sem Orvoshoz, sem Halottasházhoz." }
    { group:127, id:95, text: "Ez a ház nem fejlődhet tovább, mert jobb egészségügyi ellátást igényel. Az Orvos ellátottsága megfelelő, de nincs a közelben Halottasház." }
    { group:127, id:96, text: "Ez a ház nem fejlődhet tovább, mert jobb egészségügyi ellátást igényel. Van a közelben Halottasház, de Orvosra is szüksége van." }
    { group:127, id:97, text: "Ez a ház nem fejlődhet tovább. Mielőtt tehetősebb lakók költöznének be, a helyi Bazárnak lennel kell ellátnia." }
    { group:127, id:98, text: "unused9" }
    { group:127, id:99, text: "Ez a ház nem fejlődhet tovább. Mielőtt tehetősebb lakók költöznének be, a helyi Bazárnak sörrel kell ellátnia." }
    { group:127, id:100, text: "E palota lakói az egyiptomi társadalom csúcsán állnak. Semmiben sem szenvednek hiányt. Már pusztán az igényeik kielégítése is figyelemre méltó teljesítmény!" }
    { group:127, id:101, text: "A környék állapota javul, és a ház tulajdonosai már most is bővítik otthonukat." }
    { group:127, id:102, text: "Egy közeli épület (" }
    { group:127, id:103, text: "kedvezőtlenül befolyásolja a környék vonzerejét." }
    { group:127, id:104, text: "Ez a ház hamarosan magasabb szintre fejlődne, ha lenne elegendő helye a terjeszkedéshez." }
    { group:127, id:105, text: "unused10" }
    { group:127, id:106, text: "unused11" }
    { group:127, id:107, text: "A ház még ennyi ideig fertőzött:" }
    { group:127, id:108, text: "Ez a ház nem fejlődhet tovább. Mielőtt tehetősebb lakók költöznének be, a helyi Bazárnak luxuscikkekkel kell ellátnia, például:" }
    { group:127, id:109, text: "A házat még ennyi ideig békák lepik el:" }
    { group:127, id:110, text: "Ez a ház hamarosan visszafejlődik, mert kifinomult ízlésű lakói egy második fajta luxuscikket is igényelnek, például:" }
    { group:127, id:111, text: "(unused)" }
    { group:127, id:112, text: "Ez a ház hamarosan visszafejlődik. Az itt élő tétlen írnokoknak szükségük van arra, hogy a Bazár luxuscikkekkel lássa el őket, például:" }
    { group:127, id:113, text: "(unused)" }
    { group:127, id:114, text: "A fejlődéshez a Bazárnak egy második fajta luxuscikkel is el kell látnia ezt a házat, például:" }
    { group:127, id:115, text: "(unused)" }
    { group:127, id:116, text: "(unused)" }
    { group:128, id:0, text: "Lakatlan" }
    { group:128, id:1, text: "Ez a telek jelenleg üres. Vagy még nem épült rá ház, vagy az előző lakók megbetegedtek és meghaltak." }
    { group:128, id:2, text: "Ez a telek túl messze van a legközelebbi úttól. Ha nem épül hamarosan út a közelébe, ismét beépítetlen terület lesz." }

    { group:129, id:0, text: "-ból/-ből" }
    { group:129, id:1, text: "Kapacitás" }
    { group:129, id:2, text: "Vásárol" }
    { group:129, id:3, text: "Elad" }
    { group:129, id:4, text: "Vásárolt" }
    { group:129, id:5, text: "Eladott" }
    { group:129, id:6, text: "Horgonyon áll, szabad Kikötőhelyre vár" }
    { group:129, id:7, text: "Kikötött, árut vásárol és ad el" }
    { group:129, id:8, text: "Hazatér" }
    { group:129, id:9, text: "A város Kikötői felé tart" }
    { group:129, id:10, text: "Árukkal kereskedik" }
    { group:129, id:11, text: "Hazatér" }
    { group:129, id:12, text: "A város Tárolóudvarai felé tart" }
    { group:129, id:13, text: "Nincs itt kereskednivaló, csak áthalad" }
    { group:129, id:14, text: "-ból/-ből" }
    { group:129, id:15, text: "Úticél:" }
    { group:129, id:16, text: "Visszatér ide:" }
    { group:129, id:17, text: "Felvesz" }
    { group:129, id:18, text: "Visszatér ezzel:" }
    { group:129, id:19, text: "egység" }
    { group:129, id:20, text: "egység" }
    { group:129, id:21, text: "Rakomány:" }
    { group:130, id:0, text: "(nincs használatban)" }

    { group:131, id:0, text: "Bennszülöttek kunyhója" }
    { group:131, id:1, text: "Megjelenik ez a szöveg valahol?" }

    { group:132, id:0, text: "Bennszülöttek gyűlésháza" }
    { group:132, id:1, text: "Használatban van ez a bejegyzés?" }

    { group:133, id:0, text: "Egyszerű haszonnövények" }
    { group:133, id:1, text: "Ez a bejegyzés valószínűleg nincs használatban." }

    { group:134, id:0, text: "Missziós állomás" }
    { group:134, id:1, text: "Hol jelent meg ez a szöveg?" }

    { group:135, id:0, text: "Katonai Akadémia" }
    { group:135, id:1, text: "Miután az újoncok elvégzik az alapkiképzést a Toborzóban, ebben az akadémiában fejlesztik tovább képességeiket. Erre azonban csak akkor kerülhet sor, ha az akadémia teljes létszámú személyzettel működik." }
    { group:135, id:2, text: "Személyzet nélkül nem tudjuk tovább fejleszteni a város újoncainak képességeit. Kénytelenek egyenesen az Erődökbe menni, és a legjobbakban reménykedni." }
    { group:135, id:3, text: "A Toborzóból érkező újoncoknak megadjuk azt a pluszt, amellyel kiemelkedhetnek a mai egyiptomi hadseregben." }

    { group:136, id:0, text: "Toborzó" }
    { group:136, id:1, text: "Senki sem csatlakozhat az egyiptomi hadsereghez anélkül, hogy előbb ne fordulna meg itt. Ez a város újonckiképzője." }
    { group:136, id:2, text: "Tárolt fegyverek" }
    { group:136, id:3, text: "Személyzet nélkül egyetlen újoncot sem tudunk kiképezni. Segíts minket, Seth, a háború idején!" }
    { group:136, id:4, text: "Jelenleg nem képzünk újoncokat, mert sem az Erődök, sem az Őrtornyok nem kértek új katonákat." }
    { group:136, id:5, text: "Az íjászokat gyorsan ki tudjuk képezni, de fegyverekre van szükségünk, hogy gyalogosokat vagy harci kocsizókat is a város seregeibe sorozhassunk." }
    { group:136, id:6, text: "Kevés a személyzetünk, ezért lassabban képezzük a katonákat. Tárolt fegyverek nélkül sem gyalogosokat, sem harci kocsizókat nem tudunk kiképezni." }
    { group:136, id:7, text: "Kevés a személyzetünk, és fegyvereink sincsenek! Íjászokat még tudunk képezni, de csak lassan." }
    { group:136, id:8, text: "Minimális személyzettel és fegyverek nélkül épphogy ki tudunk képezni egy-egy íjászt." }
    { group:136, id:9, text: "Maximális hatékonysággal képezzük az új katonákat, és minden katonatípus kiképzéséhez elegendő fegyverrel rendelkezünk." }
    { group:136, id:10, text: "A személyzet hiánya miatt lassabban képezzük az új katonákat, de minden katonatípus kiképzéséhez elegendő fegyverrel rendelkezünk." }
    { group:136, id:11, text: "Kevés a személyzetünk, ezért lassan képezzük az új katonákat, de minden katonatípus kiképzéséhez elegendő fegyverrel rendelkezünk." }
    { group:136, id:12, text: "Minimális személyzettel rendkívül lassan képezzük az új katonákat, pedig minden katonatípus kiképzéséhez elegendő fegyverrel rendelkezünk." }
    { group:136, id:13, text: "Tárolt harci kocsik" }
    { group:136, id:14, text: "Tárolt harci kocsi" }
    { group:136, id:15, text: "Tárolt fegyver" }

    { group:137, id:0, text: "Sétány" }
    { group:137, id:1, text: "A sétányok növelik a kövezett utak menti területek vonzerejét, anélkül hogy befolyásolnák a forgalmat." }
    { group:138, id:0, text: "'Az Oroszlánok'" }
    { group:138, id:1, text: "'A Krokodilok'" }
    { group:138, id:2, text: "'A Kobrák'" }
    { group:138, id:3, text: "'A Skorpiók'" }
    { group:138, id:4, text: "'A Sólymok'" }
    { group:138, id:5, text: "'A Kosok'" }
    { group:138, id:6, text: "'A Hiénák'" }
    { group:138, id:7, text: "'A Szkarabeuszok'" }
    { group:138, id:8, text: "'A Sakálok'" }
    { group:138, id:9, text: "'A Viperák'" }

    { group:138, id:10, text: "Jelenleg nincs katona ehhez az erődhöz beosztva. Vagy külföldön teljesítenek szolgálatot, vagy még nem érkeztek meg a Toborzóból." }
    { group:138, id:11, text: "Ennek az alakulatnak nincsenek katonái, ezért semmit sem tesz hozzá hadereünkhöz. Működő Toborzó nélkül nem kap utánpótlást, így csak üres alakulat marad." }

    { group:138, id:12, text: "Állás tartása szoros alakzatban" }
    { group:138, id:13, text: "Az alakulat tartja az állásait, és csak támadás esetén veszi fel a harcot. Katonái hatékonyabban küzdenek közelharcban, de sebezhetőbbek a lövedékekkel szemben." }

    { group:138, id:14, text: "Állás tartása laza alakzatban" }
    { group:138, id:15, text: "Az alakulat csak támadás esetén harcol. Katonái nagyobb területet fednek le és kevésbé sebezhetők a lövedékekkel szemben, viszont gyengébben teljesítenek közelharcban." }

    { group:138, id:16, text: "Közeli ellenség támadása" }
    { group:138, id:17, text: "E parancs hatására az alakulat alakzatban maradva megtámad minden ellenséget, amely elég közel merészkedik." }

    { group:138, id:18, text: "Felderítés és tisztogatás" }
    { group:138, id:19, text: "E parancsra az alakulat felbontja az alakzatot, felkutatja és megtámadja az összes fellelhető ellenséget." }

    { group:138, id:20, text: "Roham" }
    { group:138, id:21, text: "E parancs hatására az alakulat félredob minden óvatosságot, és teljes erejével az ellenséges sorok áttörésére törekszik." }

    { group:138, id:22, text: "E parancsra az alakulat elhagyja a csatateret, és visszatér az Erődbe, hogy pótolja veszteségeit, kipihenje magát és visszanyerje harci kedvét." }

    { group:138, id:23, text: "Katonák száma" }
    { group:138, id:24, text: "Katonák egészsége" }
    { group:138, id:25, text: "Tapasztalat" }

    { group:138, id:26, text: "Tökéletes" }
    { group:138, id:27, text: "Nagyon jó" }
    { group:138, id:28, text: "Jó" }
    { group:138, id:29, text: "Átlagos" }
    { group:138, id:30, text: "Gyenge" }
    { group:138, id:31, text: "Nagyon gyenge" }
    { group:138, id:32, text: "Siralmas" }

    { group:138, id:33, text: "Harci kocsizók" }
    { group:138, id:34, text: "Gyalogság" }
    { group:138, id:35, text: "Íjászok" }

    { group:138, id:36, text: "Morál" }
    { group:138, id:37, text: "Pánikban!" }
    { group:138, id:38, text: "Retteg" }
    { group:138, id:39, text: "Rémülten fél" }
    { group:138, id:40, text: "Nagyon ijedt" }
    { group:138, id:41, text: "Ijedt" }
    { group:138, id:42, text: "Erősen megrendült" }
    { group:138, id:43, text: "Megrendült" }
    { group:138, id:44, text: "Gyenge" }
    { group:138, id:45, text: "Elég gyenge" }
    { group:138, id:46, text: "Átlag alatti" }
    { group:138, id:47, text: "Átlagos" }
    { group:138, id:48, text: "Átlag feletti" }
    { group:138, id:49, text: "Bizakodó" }
    { group:138, id:50, text: "Elég bátor" }
    { group:138, id:51, text: "Bátor" }
    { group:138, id:52, text: "Merész" }
    { group:138, id:53, text: "Nagyon merész" }
    { group:138, id:54, text: "Erős" }
    { group:138, id:55, text: "Rendkívül erős" }
    { group:138, id:56, text: "Kiváló" }
    { group:138, id:57, text: "Tökéletes" }

    { group:138, id:58, text: "Visszatérés az Erődbe" }
    { group:138, id:59, text: "Seth átka sújtja!" }

    { group:138, id:60, text: "Újonc" }
    { group:138, id:61, text: "Képzett" }
    { group:138, id:62, text: "Veterán" }
    { group:138, id:63, text: "Mester" }
    { group:138, id:64, text: "Elit" }
    { group:138, id:65, text: "A legjobbak" }

    { group:138, id:66, text: "Életerő" }
    { group:138, id:67, text: "Közelharci támadás" }
    { group:138, id:68, text: "Közelharci páncél" }
    { group:138, id:69, text: "Páncél lövedékek ellen" }
    { group:138, id:70, text: "Távolsági támadás" }
    { group:138, id:71, text: "Lőtávolság" }
    { group:138, id:72, text: "Tűzgyorsaság" }

    { group:138, id:73, text: "Alakulat" }
    { group:138, id:74, text: "Gyalogos alakulat" }
    { group:138, id:75, text: "Íjász alakulat" }
    { group:138, id:76, text: "Harci kocsis alakulat" }

    { group:138, id:77, text: "Kattints ide az alakulat vonalának elforgatásához" }
    { group:138, id:78, text: "Az alakulat parancsai és tájolása" }
    { group:139, id:0, text: "Sárfal" }
    { group:139, id:1, text: "A falak megakadályozzák, hogy a betolakodók előrenyomuljanak a városba. A támadók lerombolhatják a falakat. A vastagabb falak erősebbek, és lehetővé teszik, hogy a kapcsolódó Őrtornyok őrei járőrözzenek rajtuk." }

    { group:140, id:0, text: "Romok" }
    { group:140, id:1, text: "Ezek a fent megnevezett épület romjai. Az ilyen elhagyatott romok alig növelik a környék vonzerejét." }

    { group:141, id:0, text: "Öntözőárok" }
    { group:141, id:1, text: "Ez az öntözőárok vizet szállít, hogy termékenyebbé tegye a mezőgazdasági területeket." }
    { group:141, id:2, text: "Ez az öntözőárok nem szállít vizet a kevésbé termékeny területekre, mert nincs vízforrása." }

    { group:142, id:0, text: "Új kereskedelmi útvonal nyílt meg." }
    { group:142, id:1, text: "Az újonnan elérhető árukkal való kereskedéshez állítsd a Kereskedelmi Felügyelőnél az áruk állapotát Importunak vagy Exportnak." }
    { group:142, id:2, text: "Megnyitod a felügyelőt?" }
    { group:142, id:3, text: "NE FELEDD! A városnak Kikötőre van szüksége, mielőtt a kereskedelmi hajók használhatnák ezt az új tengeri útvonalat." }

    { group:143, id:0, text: "Áruk fogadása" }
    { group:143, id:1, text: "Áruk elutasítása" }
    { group:143, id:2, text: "Élelmiszer kérése" }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Blank" }
    { group:144, id:3, text: "Blank" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Blank" }
    { group:144, id:6, text: "Blank" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "Blank" }
    { group:144, id:9, text: "Blank" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "Blank" }
    { group:144, id:12, text: "Blank" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "Blank" }
    { group:144, id:15, text: "Blank" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "Blank" }
    { group:144, id:18, text: "Blank" }

    { group:144, id:19, text: "Az Archaikus Kor vége" }
    { group:144, id:20, text: "Behdet (Apollinopolisz): Veszélyes vizek" }
    { group:144, id:21, text: "Abedju (Abüdosz): A nekropolisz" }
    { group:144, id:22, text: "Az Óbirodalom születése" }
    { group:144, id:23, text: "Szelima-oázis: Biztosítsd a karavánutakat" }
    { group:144, id:24, text: "Abu (Elephantiné): Szerezz új gazdagságot" }

    { group:144, id:25, text: "IX (Az Óbirodalom)" }
    { group:144, id:26, text: "Blank" }
    { group:144, id:27, text: "Blank" }

    { group:144, id:28, text: "Az Óbirodalom" }
    { group:144, id:29, text: "Szerábít el-Hádim: A zord Sínai" }
    { group:144, id:30, text: "Meidum: Saját síremléket" }

    { group:144, id:31, text: "A Piramisok Kora" }
    { group:144, id:32, text: "Buhen: A núbiaiak megszelídítése" }
    { group:144, id:33, text: "Dél-Dahsúr: A piramisok új fajtája" }

    { group:144, id:34, text: "XII (Az Óbirodalom)" }
    { group:144, id:35, text: "Blank" }
    { group:144, id:36, text: "Blank" }

    { group:144, id:37, text: "A Piramisok Kora" }
    { group:144, id:38, text: "Iunet (Dendera): Kus veszélye" }
    { group:144, id:39, text: "On (Héliopolisz): Tura kőbányái" }

    { group:144, id:40, text: "XIV (Az Óbirodalom)" }
    { group:144, id:41, text: "Blank" }
    { group:144, id:42, text: "Blank" }

    { group:144, id:43, text: "Az Óbirodalom fénykora" }
    { group:144, id:44, text: "Baharija-oázis: Ré katonái" }
    { group:144, id:45, text: "Dzsedu (Abúszír): Ré imádata" }

    { group:144, id:46, text: "Az Óbirodalom hanyatlása" }
    { group:144, id:47, text: "Dunkul-oázis: Űzd ki a sakálokat" }
    { group:144, id:48, text: "Dahla-oázis: Rend a káoszban" }

    { group:144, id:49, text: "Az Első Átmeneti Kor" }
    { group:144, id:50, text: "Thinisz: Harc a trónért" }
    { group:144, id:51, text: "Waszet (Théba): Veszélyben a dicsőség" }

    { group:144, id:52, text: "A Középbirodalom születése" }
    { group:144, id:53, text: "Kebet (Koptosz): Harc a békéért" }
    { group:144, id:54, text: "Menat Khufu (Beni Haszan): Éhínség" }

    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "Blank" }
    { group:144, id:57, text: "Blank" }

    { group:144, id:58, text: "A Középbirodalom" }
    { group:144, id:59, text: "Iken (Mirgissza): A határ kitolása" }
    { group:144, id:60, text: "Szawu (Mersza Gawasis): Új kereskedők" }

    { group:144, id:61, text: "A Középbirodalom" }
    { group:144, id:62, text: "Heh (Szemna): Régi ellenségek... és újak" }
    { group:144, id:63, text: "Bubasztisz: Egyiptom koronájának ékköve" }

    { group:144, id:64, text: "A Második Átmeneti Kor" }
    { group:144, id:65, text: "Khmun (Hermopolisz): Bosszú" }
    { group:144, id:66, text: "Szauti (Lükopolisz): Ihlet" }

    { group:144, id:67, text: "Újbirodalom: Hódítás vagy béke?" }
    { group:144, id:68, text: "Byblosz: Palesztina meghódítása" }
    { group:144, id:69, text: "Baki (Kuban): Aranykor" }

    { group:144, id:70, text: "Utolsó küldetés" }
    { group:144, id:71, text: "Rowarty (Avarisz): A világ a miénk lesz" }
    { group:144, id:72, text: "Hetepsenuszret (Kahun): A nagy piramis" }
    { group:145, id:0, text: "Ehhez a küldetéshez nem tartoznak győzelmi vagy vereségi feltételek. Ez kizárólag a városépítésről szól." }

    { group:146, id:0, text: "Ellenőrizd, hogy az új felbontás megfelelően lett-e beállítva (ha ezt látod, akkor igen!). Ez az üzenet 10 másodperc múlva eltűnik." }
    { group:146, id:1, text: "Nincs kiválasztva helyszín a Birodalom térképén." }
    { group:146, id:2, text: "Az alapértelmezett helyszínt használom." }
    { group:146, id:3, text: "Ugrás a Birodalom térképére!" }
    { group:147, id:0, text: "Szép munka! Tápláló élelemmel töltötted meg néped hasát, és megvédted otthonaikat a tűztől és az összeomlástól, így segítettél ennek a zsenge civilizációnak megtenni első lépését a történelem hosszú útján." }

    { group:147, id:1, text: "Kiváló. Felépítetted az első valódi várost ezen a zord vidéken, gondoskodtál polgáraid testi és lelki szükségleteiről, és segítettél a thiniszi szövetségnek egyesíteni a megosztott országot." }

    { group:147, id:2, text: "Nagyszerű! Saját polgáraid már gondviselőjükként tekintenek rád, és a szomszédos városok is téged dicsőítenek, mint aki a szükség idején segítséget nyújt." }

    { group:147, id:3, text: "Szép munka! Rátermett vezetésednek köszönhetően az egyiptomi civilizáció jelentős fejlődésen ment keresztül, és az elkövetkező évtizedekben is tovább fog gyarapodni." }

    { group:147, id:4, text: "Gratulálunk. Olyan fővárost építettél, amely méltó az élőkhöz és a holtakhoz egyaránt. A többi várossal kiépített kereskedelmi kapcsolatok révén pedig városod kilépett a világ színpadára." }

    { group:147, id:5, text: "A fáraó elismeréssel adózik neked. Kiváló irányításoddal sikeresen megvédted városodat a beduinok támadásától, és megteremtetted Egyiptom önvédelmének alapjait." }

    { group:147, id:6, text: "A fáraó elégedett. Meghódítottad a tengert és a folyót, és bölcsen használtad ki erőforrásaikat. Az általad felépített hatalmas hadiflotta járőrözik a vízi utakon, biztosítva határainkat." }

    { group:147, id:7, text: "A fáraó mosollyal tekint eredményeidre. A legtöbbet hoztad ki a folyó és a tenger nyújtotta lehetőségekből, és kis létszámú, de ütőképes flottával véded határainkat. A nemességet is megtisztelted azzal, hogy sírokat emeltél földi maradványaik számára." }

    { group:147, id:8, text: "Szép munka! Két nagy kihívással is megbirkóztál: biztosítottál egy fontos kereskedelmi útvonalat, és virágzó várost építettél, amely még a legigényesebb polgárok szükségleteit is kielégíti. Teljesítményed valóban figyelemre méltó." }

    { group:147, id:9, text: "Szép munka! Virágzó várost alapítottál, amelyet Egyiptom többi városa példaképnek tekint, Núbia pedig irigykedve szemlél." }

    { group:147, id:10, text: "Páratlan tettet vittél véghez. Bölcsességednek köszönhetően egy hatalmas piramis emelkedik az ég felé, amelyhez foghatót még senki sem látott, és biztosítja szeretett fáraónk halhatatlanságát." }

    { group:147, id:11, text: "Sikeresen legyőzted a Sínai veszélyeit, és bőséges mennyiségű értékes rezet és türkizt biztosítottál Egyiptom számára. Tetteidre nemzedékeken át emlékezni fognak." }

    { group:147, id:12, text: "Kiváló. Az általad épített királyi nekropolisz valóban pompás. Te és családod hosszú éveken át végzett odaadó szolgálatotok jutalmául saját szent sírhelyet kaptatok." }

    { group:147, id:13, text: "Ügyességednek köszönhetően Egyiptom immár Núbia egy részét is birtokolja. Az általad alapított város révén megmutattad a meghódított núbiaiaknak Egyiptom erejét, gazdagságát és nagyságát." }

    { group:147, id:14, text: "A fáraó dicséretben részesít. A tiszteletére emelt tört piramis csodálatos, és felülmúl minden korábban épített emlékművet." }

    { group:147, id:15, text: "Kiemelkedő teljesítmény. Meghatározó szerepet játszottál egy történelmi mérföldkő elérésében: az első valódi piramis felépítésében. Sznofru piramisának elkészültével olyan mércét állítottál a piramisépítésben, amelyet minden későbbi építmény követni fog." }

    { group:147, id:16, text: "Rendkívüli. A mostoha körülmények és a kegyetlen kusiták folyamatos támadásai ellenére virágzó várost építettél, és megerősítetted Egyiptom déli határát." }

    { group:147, id:17, text: "Pompás. A Turában létesített bányák eddig minden mészkövet biztosítottak, amelyre Hufu számára szükség volt... egyelőre. A termékeny turai bányákra épülő erős gazdaságnak köszönhetően városod új kulturális és társadalmi magaslatokra emelkedett." }

    { group:147, id:18, text: "Egész Egyiptom hódol eredményeid előtt. Felépítetted Hufu hatalmas piramisát, a leggazdagabb temetkezési mellékletekkel láttad el, és nagy tiszteletet adtál Hafrának is azzal, hogy felépítetted végső nyughelyét és hatalmas szfinxét." }

    { group:147, id:19, text: "Szép munka. A szűkös erőforrásokból is a legtöbbet hoztad ki, és Ré hatalmát erre az elszigetelt vidékre is elhoztad." }

    { group:147, id:20, text: "Nagyszerű. Az általad emelt dicsőséges Naptemplom méltó tiszteletet ad Rének és a fáraónak egyaránt." }

    { group:147, id:21, text: "Sikerült gondoskodnod népedről, miközben Egyiptom körülötted összeomlik. Családod rátermettsége nagy szolgálatot tesz majd Egyiptomnak az előttünk álló nehéz időkben." }

    { group:147, id:22, text: "Miközben Egyiptom körülötted darabjaira hullik, sikerült egyben tartanod városodat. Ezek a képességek nagy szolgálatot tesznek majd Egyiptomnak az előttünk álló nehéz időkben." }

    { group:147, id:23, text: "Még a súlyos zűrzavar idején is családod kivételes vezetői képességei visszaadták Thinis korábbi dicsőségét. Bátor hadsereged segített az Inyotefeknek legyőzni vetélytársaikat – ezt a tettet még sokáig emlegetni fogják." }

    { group:147, id:24, text: "Kitartó munkáddal jóllakattad az éhező népet a háború idején, és biztosítottad a szükséges erősítéseket, hogy egyszer s mindenkorra legyőzzék ezt az ellenséget. Tetteidre még sokáig emlékezni fognak." }

    { group:147, id:25, text: "Fáradhatatlan erőfeszítéseidnek köszönhetően a Királyság egy gyönyörű és méltóságteljes új várossal gazdagodott. Emellett egész Egyiptomért is sokat tettél, amikor a szükség idején tápláltad az éhezőket. Kimagasló szolgálataid nem maradnak jutalom nélkül." }
    { group:147, id:26, text: "Az általam emeltetett pompás piramisaid és obeliszkjeid uralkodásom örök tanúbizonyságai, ezért mélységes hálával tartozom neked. Hűséged nem marad jutalom nélkül." }

    { group:147, id:27, text: "Néped iránti önzetlen gondoskodásodnak köszönhetően Egyiptom immár jogos fáraójaként ismer el, és azt várja dinasztiádtól, hogy ugyanilyen jóságos és leleményes örökösöket adjon." }

    { group:147, id:28, text: "Hódoljatok a dicsőséges, hatalmas fáraónak! Sikeresen meghódítottad Észak-Núbiát, miközben a Vörös-tengeri kikötőnket is elláttad a virágzásához szükséges erőforrásokkal, biztosítva hadseregünk számára a réz megbízható utánpótlását." }

    { group:147, id:29, text: "Éljen a bölcs és leleményes fáraó! Az új vörös-tengeri kereskedelmi kikötő virágzik, támogatásodnak köszönhetően pedig Núbiában is sikerült egy hasonlóan erős kereskedelmi állomást létrehozni." }

    { group:147, id:30, text: "Szet bizonyára rád mosolyog, legvitézebb fáraó. Sikeresen kiűzted a núbiaiakat, és ezzel biztosítottad déli határunkat." }

    { group:147, id:31, text: "Bubasztisz ragyogó városa méltó dicsőséget szerez neked, legrátermettebb fáraó, és egész Egyiptomnak." }

    { group:147, id:32, text: "Örvend Egyiptom! A hükszoszokat kiűztük földünkről, és vezetéseddel Egyiptom ismét a miénk." }

    { group:147, id:33, text: "Az örök élet ígéretével nagyszerű győzelmekre lelkesítetted hadvezéreidet a csatatéren. A hükszoszokat és rettegett harci szekereiket kiűztétek Egyiptomból." }

    { group:147, id:34, text: "Mindenható fáraó, a hettiták visszaverésével Egyiptom hatalmas birodalommá vált! Kardod elhozta az egyiptomi civilizáció ajándékát a világnak." }

    { group:147, id:35, text: "Legbékésebb fáraó, megnyugtató bölcsességed Egyiptomot egy új korszak küszöbére vezette!" }

    { group:147, id:36, text: "Éljen a hatalmas fáraó! Dinasztiádnak nincs párja, és az egyiptomiak mostantól az idők végezetéig a legmélyebb tisztelettel ejtik ki nevedet." }

    { group:147, id:37, text: "Éljen a hatalmas fáraó! Dinasztiád páratlan, és az egyiptomiak mostantól az idők végezetéig a legmélyebb tisztelettel ejtik ki nevedet." }

    { group:147, id:38, text: "Szép munka. I. Thotmesz sírja elkészült – rendkívüli teljesítmény! A fáraó biztos benne, hogy ez a gyönyörűen díszített sír elnyeri az istenek tetszését, és felgyorsítja útját a túlvilágra." }

    { group:147, id:39, text: "Lenyűgöző teljesítmény! Ritkán fordul elő, hogy ekkora nyomás alatt dolgozó munkások ilyen kiváló mestermunkát alkossanak. Tutanhamon sírját immár örökre biztonságosan lezárták. Reméljük, az eretnek sírrablók soha nem fedezik fel nyughelyét!" }

    { group:147, id:40, text: "Kiváló munka! Sikeresen megvédted a Királyok Völgyének királyi sírjait, és az új sírt is az utasításoknak megfelelően elkészítetted. Széthi fáraót rendkívül elégedetté tette munkásaid kifinomult mesterségbeli tudása." }

    { group:147, id:41, text: "Kiváló munka! Nagy fáraónk, II. Ramszesz nem tévedett, amikor téged választott e vidék kereskedelmi és katonai fejlesztésének felügyeletére. Ám veszély közeleg! A hettiták seregei ismét fegyvert ragadtak, hogy megkérdőjelezzék jogos uralmunkat e felbecsülhetetlen értékű terület felett." }

    { group:147, id:42, text: "A fáraó keze ismét lesújtott a gyűlöletes hettitákra. Nagy az öröm legbölcsebb és legbátrabb uralkodónk, II. Ramszesz dicsőségére! Fenséges győzelmedet ebben a kemény csatában bizonyosan örökre feljegyzik a történelem évkönyvei." }

    { group:147, id:43, text: "Kiváló munka! II. Ramszesz rendkívül elégedett a tiszteletére Abu Szimbelnél emelt monumentális emlékművel." }

    { group:147, id:44, text: "Szép munka! A látszólag véget nem érő csapások és szerencsétlenségek ellenére idősödő fáraónk nagyszerű sírja teljesen elkészült. Pompája méltóképpen tükrözi tiszteletünket II. Ramszesz iránt, aki kétségkívül Egyiptom egyik legnagyobb uralkodója." }

    { group:147, id:45, text: "A napfény elűzte az Egyiptom fölött tornyosuló viharfelhőket. Nagy az öröm! A gyalázatos libu törzsfő és tengeri szövetségesei az éj leple alatt elmenekültek. Balul sikerült tervük, hogy partjainkon telepedjenek le, végleg összeomlott. Szerencsénkre asszonyaik és gyermekeik közül sokan immár szégyenteljes foglyaink." }

    { group:147, id:46, text: "Szép munka! Személyes bátorságod és rendíthetetlenséged a csatában arra ösztönözte katonáidat, hogy minden erejüket beleadják. Az átkozott asszírokat végleg kiűztétek Egyiptom földjéről. Tetted híre eljutott a fáraóhoz, aki igen elégedett." }

    { group:147, id:47, text: "Dicsőség Tanisz hősének, Egyiptom oltalmazójának! Fényes győzelmeid szárazföldön és vízen egyaránt biztosították Egyiptom függetlenségének fennmaradását. Az egykor hatalmas perzsák ma már reszketnek, amikor Achorisz fáraó nevét kimondják." }

    { group:147, id:48, text: "Jól végezted a feladatod. Bölcs vezetésednek és gondos tervezésednek köszönhetően Alexandria a földközi-tengeri kereskedelem központjává vált. Nagy kár, hogy Nagy Sándor sohasem láthatta birodalma fővárosát. Legalább azzal vigasztalódhatunk, hogy immár biztonságban nyugszik annak falai között." }

    { group:147, id:49, text: "Alexandria világvárosa immár jelzőfényként ragyog a világ számára! Nagy Könyvtára felülmúlhatatlan tudományos központ, a magasba törő pharoszi világítótorony pedig már most a világ egyik valódi csodája." }

    { group:147, id:50, text: "Hatalmas légióid szétzúzták XIII. Ptolemaiosz csőcselékét. A Nílusból kiemelt holtteste kétséget kizáróan bizonyítja halálát. Az ostrom véget ért, Kleopátra pedig ismét biztonságban ül trónján. A győzelem megünneplésére és kapcsolatuk további megszilárdítására Caesar és Kleopátra most fényűző királyi bárkájukon hajóznak felfelé a Níluson." }
    { group:147, id:51, text: "Alexandria pompája és Egyiptom sorsa biztos kezekben van vezetésed alatt. Ahogy várható volt, amikor végre kegyeskedtél megjelenni Marcus Antonius előtt, illő tisztelettel adózott neked, miközben anyagi támogatásodat kérte céljai megvalósításához. Sőt, olyannyira beléd szeretett, hogy Alexandriába költözött, hogy társad és szeretőd legyen." }

    { group:147, id:52, text: "Kleopátra kincstárának gazdagságával és Antonius hadvezéri zsenialitásával Octavianus flottája és veterán légiói teljes vereséget szenvedtek. Róma népe türelmetlenül várja Antonius és Kleopátra diadalmas hazatérését. Róma és Alexandria kéz a kézben uralja majd a Földközi-tengert még sok nemzedéken át." }

    { group:147, id:53, text: "Egyéni küldetés teljesítve" }

    { group:147, id:54, text: "Jól helytálltál, de még számtalan kihívás vár rád az úton, míg végül... fáraóvá válsz!" }
    { group:148, id:5, text: "Végső városi vagyon" }

    { group:148, id:6, text: "Felépített emlékművek" }

    { group:148, id:7, text: "A küldetés teljesítési ideje:" }

    { group:148, id:8, text: "Legalacsonyabb nehézségi szint:" }

    { group:148, id:9, text: "Pontszám:" }

    { group:148, id:10, text: "Gratulálunk! A „Küldetés kiválasztása” gombra kattintva visszatérhetsz, és megpróbálhatod megdönteni a pontszámodat." }

    { group:148, id:11, text: "Legutóbb jobb eredményt értél el ezen a küldetésen." }

    { group:148, id:12, text: "Nagyszerű! Megdöntötted a korábbi pontszámodat ezen a küldetésen!" }

    { group:148, id:13, text: "Sikeresen teljesítetted ezt a küldetést, de ebben a városban továbbra is [player_name] tartja a legjobb eredményt." }

    { group:148, id:14, text: "Mostantól tied a küldetés legjobb eredménye! Túlszárnyaltad [player_name] teljesítményét." }

    { group:148, id:15, text: "hónap" }

    { group:148, id:16, text: "Csaltál! Az eredményed nem méltó arra, hogy bekerüljön a Legjobb családok közé." }
    { group:149, id:0, text: "Általános kérés" }
    { group:149, id:1, text: "Egyiptomi város támadás alatt" }
    { group:149, id:2, text: "Távoli csata" }
    { group:149, id:3, text: "Ünnepség" }
    { group:149, id:4, text: "Építkezés" }
    { group:149, id:5, text: "Éhínség" }
    { group:149, id:6, text: "Fenyegetés" }

    { group:150, id:0, text: "Egyiptomi város megmenekült" }
    { group:150, id:1, text: "Távoli csata megnyerve" }
    { group:150, id:2, text: "Távoli csata elveszítve" }
    { group:150, id:3, text: "Köszönetnyilvánítás" }

    { group:151, id:0, text: "I. Amenemhat" }
    { group:151, id:1, text: "II. Amenemhat" }
    { group:151, id:2, text: "III. Amenemhat" }
    { group:151, id:3, text: "IV. Amenemhat" }
    { group:151, id:4, text: "Anedzsib" }
    { group:151, id:5, text: "Den" }
    { group:151, id:6, text: "Dzsedefré" }
    { group:151, id:7, text: "Dzsedkaré Iszeszi" }
    { group:151, id:8, text: "Dzser" }
    { group:151, id:9, text: "Dzset" }
    { group:151, id:10, text: "Dzsószer" }
    { group:151, id:11, text: "Hetepszehemui" }
    { group:151, id:12, text: "Hor" }
    { group:151, id:13, text: "Hor-Aha" }
    { group:151, id:14, text: "Huni" }
    { group:151, id:15, text: "I. Inyotef" }
    { group:151, id:16, text: "II. Inyotef" }
    { group:151, id:17, text: "III. Inyotef" }
    { group:151, id:18, text: "Haba" }
    { group:151, id:19, text: "Haszehemui" }
    { group:151, id:20, text: "Hendzser" }
    { group:151, id:21, text: "Hafré" }
    { group:151, id:22, text: "Heti" }
    { group:151, id:23, text: "Hufu" }
    { group:151, id:24, text: "Ménész" }
    { group:151, id:25, text: "Menkauhor" }
    { group:151, id:26, text: "Menkauré" }
    { group:151, id:27, text: "I. Mentuhotep" }
    { group:151, id:28, text: "II. Mentuhotep" }
    { group:151, id:29, text: "III. Mentuhotep" }
    { group:151, id:30, text: "IV. Mentuhotep" }
    { group:151, id:31, text: "Merenré" }
    { group:151, id:32, text: "Merneith királynő" }
    { group:151, id:33, text: "Narmer" }
    { group:151, id:34, text: "Nebka" }
    { group:151, id:35, text: "I. Neferhotep" }
    { group:151, id:36, text: "Neferirkaré" }
    { group:151, id:37, text: "Neuszerré" }
    { group:151, id:38, text: "Ninetjer" }
    { group:151, id:39, text: "Nitikret" }
    { group:151, id:40, text: "I. Pepi" }
    { group:151, id:41, text: "II. Pepi" }
    { group:151, id:42, text: "Peribszen" }
    { group:151, id:43, text: "Qa'a" }
    { group:151, id:44, text: "Raneferef" }
    { group:151, id:45, text: "Reneb" }
    { group:151, id:46, text: "Szahuré" }
    { group:151, id:47, text: "Szehemhet" }
    { group:151, id:48, text: "Szemerhet" }
    { group:151, id:49, text: "Szened" }
    { group:151, id:50, text: "I. Szenuszert" }
    { group:151, id:51, text: "II. Szenuszert" }
    { group:151, id:52, text: "III. Szenuszert" }
    { group:151, id:53, text: "Sepszeszkaf" }
    { group:151, id:54, text: "Sepszeszkaré" }
    { group:151, id:55, text: "Sznofru" }
    { group:151, id:56, text: "III. Szobekhotep" }
    { group:151, id:57, text: "Szobekneferu királynő" }
    { group:151, id:58, text: "Teti" }
    { group:151, id:59, text: "Unasz" }
    { group:151, id:60, text: "Uszerkaf" }
    { group:151, id:61, text: "Uszerkaré" }
    { group:151, id:62, text: "Weneg" }
    { group:151, id:63, text: "I. Jahmesz" }
    { group:151, id:64, text: "I. Amenhotep" }
    { group:151, id:65, text: "I. Thotmesz" }
    { group:151, id:66, text: "II. Thotmesz" }
    { group:151, id:67, text: "Hatsepszut" }
    { group:151, id:68, text: "III. Thotmesz" }
    { group:151, id:69, text: "II. Amenhotep" }
    { group:151, id:70, text: "IV. Thotmesz" }
    { group:151, id:71, text: "III. Amenhotep" }
    { group:151, id:72, text: "Ehnaton" }
    { group:151, id:73, text: "Neferneferuaton" }
    { group:151, id:74, text: "Szemenhkaré" }
    { group:151, id:75, text: "Tutanhamon" }
    { group:151, id:76, text: "Aj" }
    { group:151, id:77, text: "Horemheb" }
    { group:151, id:78, text: "I. Ramszesz" }
    { group:151, id:79, text: "I. Széthi" }
    { group:151, id:80, text: "II. Ramszesz" }
    { group:151, id:81, text: "Merenptah" }
    { group:151, id:82, text: "Amenmesze" }
    { group:151, id:83, text: "II. Széthi" }
    { group:151, id:84, text: "Sziptah" }
    { group:151, id:85, text: "Tauszert királynő" }
    { group:151, id:86, text: "Szetnaht" }
    { group:151, id:87, text: "III. Ramszesz" }
    { group:151, id:88, text: "IV. Ramszesz" }
    { group:151, id:89, text: "V. Ramszesz" }
    { group:151, id:90, text: "VI. Ramszesz" }
    { group:151, id:91, text: "VII. Ramszesz" }
    { group:151, id:92, text: "VIII. Ramszesz" }
    { group:151, id:93, text: "IX. Ramszesz" }
    { group:151, id:94, text: "X. Ramszesz" }
    { group:151, id:95, text: "XI. Ramszesz" }
    { group:151, id:96, text: "Pije" }
    { group:151, id:97, text: "Sabaka" }
    { group:151, id:98, text: "Sebitku" }
    { group:151, id:99, text: "Taharka" }
    { group:151, id:100, text: "Tanutamon" }
    { group:151, id:101, text: "I. Nepheritész" }
    { group:151, id:102, text: "Pszammuthisz" }
    { group:151, id:103, text: "I. Nefaarud" }
    { group:151, id:104, text: "Hakor" }
    { group:151, id:105, text: "Nakhtnebef" }
    { group:151, id:106, text: "Nagy Sándor" }
    { group:151, id:107, text: "Philipposz Arrhidaiosz" }
    { group:151, id:108, text: "IV. Alexandrosz" }
    { group:151, id:109, text: "I. Ptolemaiosz" }
    { group:151, id:110, text: "II. Ptolemaiosz" }
    { group:151, id:111, text: "III. Ptolemaiosz" }
    { group:151, id:112, text: "IV. Ptolemaiosz" }
    { group:151, id:113, text: "V. Ptolemaiosz" }
    { group:151, id:114, text: "VI. Ptolemaiosz" }
    { group:151, id:115, text: "VII. Ptolemaiosz" }
    { group:151, id:116, text: "VIII. Ptolemaiosz" }
    { group:151, id:117, text: "IX. Ptolemaiosz" }
    { group:151, id:118, text: "X. Ptolemaiosz" }
    { group:151, id:119, text: "XI. Ptolemaiosz" }
    { group:151, id:120, text: "XII. Ptolemaiosz" }
    { group:151, id:121, text: "IV. Bereniké királynő" }
    { group:151, id:122, text: "XIII. Ptolemaiosz" }
    { group:151, id:123, text: "VII. Kleopátra" }
    { group:151, id:124, text: "XV. Ptolemaiosz" }

    { group:152, id:0, text: "" }
    { group:152, id:1, text: "I." }
    { group:152, id:2, text: "II." }
    { group:152, id:3, text: "III." }
    { group:152, id:4, text: "IV." }
    { group:152, id:5, text: "V." }
    { group:152, id:6, text: "VI." }
    { group:152, id:7, text: "VII." }
    { group:152, id:8, text: "VIII." }
    { group:152, id:9, text: "IX." }
    { group:152, id:10, text: "X." }
    { group:152, id:11, text: "XI." }
    { group:152, id:12, text: "XII." }
    { group:152, id:13, text: "XIII." }
    { group:152, id:14, text: "XIV." }
    { group:152, id:15, text: "XV." }
    { group:152, id:16, text: "XVI." }
    { group:152, id:17, text: "XVII." }
    { group:152, id:18, text: "XVIII." }
    { group:152, id:19, text: "XIX." }
    { group:152, id:20, text: "XX." }
    { group:152, id:21, text: "XXI." }
    { group:152, id:22, text: "XXII." }
    { group:152, id:23, text: "XXIII." }
    { group:152, id:24, text: "XXIV." }
    { group:152, id:25, text: "XXV." }
    { group:152, id:26, text: "XXVI." }
    { group:152, id:27, text: "XXVII." }
    { group:152, id:28, text: "XXVIII." }
    { group:152, id:29, text: "XXIX." }
    { group:152, id:30, text: "XXX." }
    { group:154, id:0, text: "Vadászház" }
    { group:154, id:1, text: "Az itt élő vadászok követik és elejtik a környék vadállatait. A Vadászház ezután a vadhúst a helyi raktárakba vagy magtárakba szállítja." }
    { group:154, id:2, text: "A termelés" }
    { group:154, id:3, text: "befejeződött." }
    { group:154, id:4, text: "A Kereskedelmi felügyelő elrendelte a vadászat beszüntetését." }
    { group:154, id:5, text: "Ennek a vadászháznak nincsenek dolgozói. A vadászatot törölték." }
    { group:154, id:6, text: "Ennek a vadászháznak minden szükséges dolgozója megvan. A vadászok minden fellelhető csordát nyomon követnek." }
    { group:154, id:7, text: "Ez a vadászház nem teljes kapacitással működik. Emiatt az élelem begyűjtése lassabb lesz." }
    { group:154, id:8, text: "Ennek a vadászháznak kevés a dolgozója, ezért a hús begyűjtése tovább tart a kelleténél." }
    { group:154, id:9, text: "Nagyon kevesen dolgoznak itt. A hús begyűjtése valóban lassú." }
    { group:154, id:10, text: "Alig dolgozik itt néhány vadász, ezért a zsákmányállatok zavartalanul járják a vidéket. Könnyen lehet, hogy nagyon éhes száraz évszak elé nézünk..." }
    { group:154, id:11, text: "Ennek a vadászháznak a vadászai zsákmány után kutatnak." }
    { group:154, id:12, text: "Túl sokáig tart, amíg a hús visszajut a vadászházba. Próbáld közelebb építeni a vadon élő állatokhoz." }
    { group:154, id:13, text: "Tárolt hús," }

    { group:155, id:0, text: "Úttorlasz" }
    { group:155, id:1, text: "Helyezz el úttorlaszokat a gyalogosok útvonalainak korlátozására. Azok, akiknek meghatározott céljuk van (például szállítók vagy a bazár vásárlói), szabadon áthaladhatnak." }

    { group:156, id:0, text: "Szabad esemény" }
    { group:156, id:1, text: "Kérés" }
    { group:156, id:2, text: "Invázió" }
    { group:156, id:3, text: "Földrengés" }
    { group:156, id:4, text: "Lázadás" }
    { group:156, id:5, text: "Fáraóváltás" }
    { group:156, id:6, text: "Tengeri kereskedelmi probléma" }
    { group:156, id:7, text: "Szárazföldi kereskedelmi probléma" }
    { group:156, id:8, text: "Béremelés" }
    { group:156, id:9, text: "Bércsökkentés" }
    { group:156, id:10, text: "Szennyezett víz" }
    { group:156, id:11, text: "Aranybánya beomlása" }
    { group:156, id:12, text: "Agyagbánya elárasztása" }
    { group:156, id:13, text: "Kereslet növekedése" }
    { group:156, id:14, text: "Kereslet csökkenése" }
    { group:156, id:15, text: "Áremelkedés" }
    { group:156, id:16, text: "Árcsökkenés" }
    { group:156, id:17, text: "Királyság növekedése" }
    { group:156, id:18, text: "Királyság csökkenése" }
    { group:156, id:19, text: "Városi rang változása" }
    { group:156, id:20, text: "Üzenetes esemény" }
    { group:156, id:21, text: "Sikertelen áradás" }
    { group:156, id:22, text: "Tökéletes áradás" }
    { group:156, id:23, text: "Ajándék" }
    { group:156, id:24, text: "Sáskák csapása" }
    { group:156, id:25, text: "Békák csapása" }
    { group:156, id:26, text: "Jégeső" }
    { group:156, id:27, text: "Vérfolyó" }
    { group:156, id:28, text: "Bűnözési hullám" }
    { group:156, id:29, text: "Múmia" }

    { group:157, id:0, text: "Ozirisz" }
    { group:157, id:1, text: "Ré" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Szet" }
    { group:157, id:4, text: "Bastet" }
    { group:157, id:5, text: "Hermie" }
    { group:157, id:6, text: "Janus" }

    { group:158, id:0, text: "A mezőgazdaság és a nílusi áradás istene" }
    { group:158, id:1, text: "A Királyság istene" }
    { group:158, id:2, text: "A kézművesek istene" }
    { group:158, id:3, text: "A pusztítás istene" }
    { group:158, id:4, text: "Az otthon istennője" }
    { group:158, id:5, text: "(Fogászat)" }
    { group:158, id:6, text: "(Minden)" }

    { group:159, id:0, text: "Kompállomás" }
    { group:159, id:1, text: "FIGYELEM! Ehhez a kompállomáshoz nem tartozik összekapcsolt átkelőhely a folyó túlpartján. Senki sem tud átkelni." }
    { group:159, id:2, text: "FIGYELEM! A komp kapcsolódó átkelőhelyéhez nem vezet út. Csak a bevándorlók tudnak átkelni." }
    { group:159, id:3, text: "FIGYELEM! A komp kapcsolódó átkelőhelyén munkaerő-problémák vannak. Csak a bevándorlók tudnak átkelni." }

    { group:160, id:0, text: "Január" }
    { group:160, id:1, text: "Február" }
    { group:160, id:2, text: "Március" }
    { group:160, id:3, text: "Április" }
    { group:160, id:4, text: "Május" }
    { group:160, id:5, text: "Június" }
    { group:160, id:6, text: "Július" }
    { group:160, id:7, text: "Augusztus" }
    { group:160, id:8, text: "Szeptember" }
    { group:160, id:9, text: "Október" }
    { group:160, id:10, text: "November" }
    { group:160, id:11, text: "December" }

    { group:161, id:0, text: "Ozirisz szentélye (mezőgazdaság)" }
    { group:161, id:1, text: "Ozirisz termékennyé teszi a földet, és növekedésre bírja a termést. Engeszteld ki, vagy készülj fel az éhezésre." }
    { group:161, id:2, text: "Ré szentélye (Királyság)" }
    { group:161, id:3, text: "A kereskedők jól tudják, milyen értékkel bír Ré kegyének elnyerése. Ré áldásával a kereskedelem biztonságosabb és jövedelmezőbb, városod tekintélye pedig nagyobb lesz." }
    { group:161, id:4, text: "Ptah szentélye (kézművesek)" }
    { group:161, id:5, text: "A munkások és kézművesek Ptahhoz fohászkodnak, hogy megkönnyítse munkájukat. Amikor Ptah haragra gerjed, egyetlen iparág sincs biztonságban a katasztrófáktól." }
    { group:161, id:6, text: "Szet szentélye (pusztítás)" }
    { group:161, id:7, text: "Szet őrködik a katonák felett, és bátorságra ösztönöz a harcban. Senki sem mer csatába indulni Szet áldása nélkül." }
    { group:161, id:8, text: "Bastet szentélye (otthon)" }
    { group:161, id:9, text: "Ha Bastet elégedetlen, senki otthona sincs biztonságban. Egyesek még a betegségekért is Bastetet hibáztatják." }

    { group:162, id:0, text: "Aranybánya" }
    { group:162, id:1, text: "Az arany bányászata a legközvetlenebb módja városod kincstárának feltöltésére. Szerencsés az a város, amely ilyen értékes kinccsel rendelkezik, mert gazdagsága biztosított." }
    { group:162, id:2, text: "A termelés" }
    { group:162, id:3, text: "befejeződött." }
    { group:162, id:4, text: "A Kereskedelmi felügyelő elrendelte az aranybányászat beszüntetését." }
    { group:162, id:5, text: "Ennek a bányának nincsenek dolgozói. Egyáltalán nem lehet ércet kitermelni." }
    { group:162, id:6, text: "Ennek a bányának minden szükséges dolgozója megvan, és kisebb vagyont termel aranyban." }
    { group:162, id:7, text: "Ez a bánya nem teljes kapacitással működik. Több aranyat hozna, ha több bányász dolgozna benne." }
    { group:162, id:8, text: "Ennek a bányának kevés a dolgozója. Kevesebb aranyat termel, mint amire képes lenne." }
    { group:162, id:9, text: "Nagyon kevesen dolgoznak itt. Az aranykitermelés meglehetősen csekély." }
    { group:162, id:10, text: "Alig dolgozik itt néhány munkás, ezért a bányászat szinte leállt. Alig várható ebből arany." }

    { group:163, id:0, text: "Drágakőbánya" }
    { group:163, id:1, text: "Bányássz drágaköveket exportra vagy ékszerek készítéséhez, városod alapvető luxuscikkéhez." }
    { group:163, id:2, text: "A termelés" }
    { group:163, id:3, text: "befejeződött." }
    { group:163, id:4, text: "A Kereskedelmi felügyelő úgy döntött, hogy a városnak elegendő drágaköve van, ezért leállította a bányászatot." }
    { group:163, id:5, text: "Ennek a bányának nincsenek dolgozói. A drágakövek örökre a kőzet fogságában maradnak." }
    { group:163, id:6, text: "Ennek a bányának minden szükséges dolgozója megvan, és csillogó drágakőhalmokat termel." }
    { group:163, id:7, text: "Ebben a bányában vannak betöltetlen állások, ezért a drágakőtermelés kevésbé hatékony a lehetségesnél." }
    { group:163, id:8, text: "Ennek a bányának kevés a dolgozója. Jelentősen kevesebb drágakövet termel, mint amire képes lenne." }
    { group:163, id:9, text: "Nagyon kevés bányász dolgozik itt. A drágakövek kiszabadítása a kőzetből valóban nagyon lassan halad." }
    { group:163, id:10, text: "Alig dolgozik itt néhány munkás, ezért szinte egyáltalán nem bányásznak drágaköveket." }

    { group:164, id:0, text: "Tűzőrség" }
    { group:164, id:1, text: "A tűzőrségek őröket küldenek a városba, hogy megelőzzék a tüzeket, és megfékezzék azokat, amelyek mégis kitörnek." }
    { group:164, id:2, text: "Őrünk az utcákat járőrözi." }
    { group:164, id:3, text: "Őrünk szolgálatra készül." }
    { group:164, id:4, text: "Jelenleg teljes a szolgálati beosztásunk. Őreink mindig kint vannak, és a tűz jeleit keresik." }
    { group:164, id:5, text: "Kissé híján vagyunk őröknek. Az ellenőrzésben talán egy-két napos kiesések fordulnak elő." }
    { group:164, id:6, text: "Kevés a személyzetünk. A tűzmegelőző járőrözésben akár egyhetes késések is előfordulnak." }
    { group:164, id:7, text: "Sokkal kevesebb emberünk van a szükségesnél. Gyakran előfordul, hogy akár két hétig egyetlen őr sem hagyja el a tűzőrséget." }
    { group:164, id:8, text: "Csak irodai személyzettel működünk. Gyakran egy teljes hónap is eltelik anélkül, hogy őrt küldenénk az utcákra." }
    { group:164, id:9, text: "Nincs személyzetünk, így ez a tűzőrség alig több, mint egy készülő tűzvész." }

    { group:165, id:0, text: "Téglafal" }
    { group:165, id:1, text: "A falak megakadályozzák a támadók előrenyomulását a városban. A támadók lerombolhatják a falakat. A vastagabb falak erősebbek, és lehetővé teszik a kapcsolódó tornyok őreinek járőrözését rajtuk." }

    { group:166, id:0, text: "Fal" }
    { group:166, id:1, text: "A falak megakadályozzák a támadók előrenyomulását a városban. A támadók lerombolhatják a falakat. A vastagabb falak erősebbek, és lehetővé teszik a kapcsolódó tornyok őreinek járőrözését rajtuk." }

    { group:167, id:0, text: "Téglakapuőrház" }
    { group:167, id:1, text: "A falaknak kapuőrházra van szükségük, hogy a bevándorlók és kereskedők szabadon be- és kijárhassanak." }

    { group:168, id:0, text: "Kapuőrház" }
    { group:168, id:1, text: "A falaknak kapuőrházra van szükségük, hogy a bevándorlók és kereskedők szabadon be- és kijárhassanak." }

    { group:169, id:0, text: "Téglatorony" }
    { group:169, id:1, text: "Építs tornyokat a falaidba rendszeres időközönként, vagy legalább a sebezhető területekre. Ha utakhoz kapcsolódnak, a tornyok őröket kapnak a város Toborzójától. A toronyőrség dárdazáport zúdít a közeli támadókra, és járőrözik a megfelelő vastagságú falakon." }
    { group:169, id:2, text: "Dolgozók nélkül nem tudjuk ellátni a tornyokat személyzettel, és nem tudunk őröket fogadni a falak járőrözésére." }
    { group:169, id:3, text: "Embereink éberek és készen állnak minden támadás visszaverésére." }
    { group:169, id:4, text: "Van karbantartó személyzetünk, de a város védelméhez a Toborzótól érkező őrökre van szükségünk." }

    { group:170, id:0, text: "Torony" }
    { group:170, id:1, text: "Építs tornyokat a falaidba rendszeres időközönként, vagy legalább a sebezhető területekre. Ha utakhoz kapcsolódnak, a tornyok őröket kapnak a város Toborzójától. A toronyőrség dárdazáport zúdít a közeli támadókra, és járőrözik a megfelelő vastagságú falakon." }
    { group:170, id:2, text: "Dolgozók nélkül nem tudjuk ellátni a tornyainkat személyzettel, és nem tudunk őröket fogadni a falak járőrözésére." }
    { group:170, id:3, text: "Embereink éberek és készen állnak minden támadás visszaverésére." }
    { group:170, id:4, text: "Van karbantartó személyzetünk, de a város védelméhez a Toborzótól érkező őrökre van szükségünk." }

    { group:171, id:0, text: "Ácsok céhe" }
    { group:171, id:1, text: "Az ácsok itt gyűlnek össze, hogy szakmájukról történeteket és tanácsokat cseréljenek, munkákat kapjanak, és megoldják felmerülő problémáikat." }
    { group:171, id:2, text: "A termelés" }
    { group:171, id:3, text: "befejeződött." }
    { group:171, id:4, text: "Ezt a céhet a Kereskedelmi felügyelő bezáratta." }
    { group:171, id:5, text: "Ennek a céhnek nincsenek alkalmazottai. Ácsmunkák nem érhetők el." }
    { group:171, id:6, text: "Ennek a céhnek minden szükséges alkalmazottja megvan. Az ácsok maximális hatékonysággal dolgozhatnak." }
    { group:171, id:7, text: "Ez a céh nem teljes kapacitással működik. Emiatt a munkavégzés kissé lassabb lesz." }
    { group:171, id:8, text: "Ennek a céhnek kevés a dolgozója, ezért kevesebb ácsot biztosít, mint amennyire képes lenne." }
    { group:171, id:9, text: "Nagyon kevesen dolgoznak itt. Jelentős várakozási idő van egy ács szolgáltatásaira." }
    { group:171, id:10, text: "Alig dolgozik néhány alkalmazott ebben a céhben, ezért úgy tűnik, örökké tart, mire egy ács megérkezik." }
    { group:171, id:11, text: "Ebbe a műhelybe fát kell szállítani." }
    { group:171, id:12, text: "Tárolt fa," }

    { group:172, id:0, text: "Kőművesek céhe" }
    { group:172, id:1, text: "A kőművesek itt gyűlnek össze, hogy szakmájukról történeteket és tanácsokat cseréljenek, munkákat kapjanak, és megtervezzék a jövőt." }
    { group:172, id:2, text: "A termelés" }
    { group:172, id:3, text: "befejeződött." }
    { group:172, id:4, text: "Ezt a céhet a Kereskedelmi felügyelő bezáratta." }
    { group:172, id:5, text: "Ennek a céhnek nincsenek alkalmazottai. Nem lehet téglát rakni." }
    { group:172, id:6, text: "Ennek a céhnek minden szükséges alkalmazottja megvan. A kőművesek maximális hatékonysággal dolgozhatnak." }
    { group:172, id:7, text: "Ez a céh nem teljes kapacitással működik. Emiatt a munkavégzés kissé lassabb lesz." }
    { group:172, id:8, text: "Ennek a céhnek kevés a dolgozója, ezért kevesebb kőművest biztosít, mint amennyire képes lenne." }
    { group:172, id:9, text: "Nagyon kevesen dolgoznak itt. Jelentős várakozási idő van a kőművesmunkákra." }
    { group:172, id:10, text: "Alig dolgozik néhány alkalmazott ebben a céhben, ezért úgy tűnik, örökké tart, mire egy kőműves megérkezik." }
    { group:172, id:11, text: "Ez a céh szakképzett munkásokat biztosít az emlékművek építéséhez. Nincs szüksége saját téglakészletre." }
    { group:172, id:12, text: "Tárolt tégla," }

    { group:173, id:0, text: "Kőfaragók céhe" }
    { group:173, id:1, text: "A kőfaragók itt gyűlnek össze, hogy szakmájukról történeteket és tanácsokat cseréljenek, munkákat kapjanak, és megtervezzék a jövőt." }
    { group:173, id:2, text: "A termelés" }
    { group:173, id:3, text: "befejeződött." }
    { group:173, id:4, text: "Ezt a céhet a Kereskedelmi felügyelő bezáratta." }
    { group:173, id:5, text: "Ennek a céhnek nincsenek alkalmazottai. Kőfaragás nem lehetséges." }
    { group:173, id:6, text: "Ennek a céhnek minden szükséges alkalmazottja megvan. A kőfaragók maximális hatékonysággal dolgozhatnak." }
    { group:173, id:7, text: "Ez a céh nem teljes kapacitással működik. Emiatt a munkavégzés kissé lassabb lesz." }
    { group:173, id:8, text: "Ennek a céhnek kevés a dolgozója, ezért kevesebb kőfaragót biztosít, mint amennyire képes lenne." }
    { group:173, id:9, text: "Nagyon kevesen dolgoznak itt. Hosszú várakozási idő van a kőfaragó munkákra." }
    { group:173, id:10, text: "Alig dolgozik néhány alkalmazott ebben a céhben, ezért úgy tűnik, örökké tart, mire egy kőfaragó szolgálatba áll." }
    { group:173, id:11, text: "Ez a céh szakképzett munkásokat biztosít az emlékművek építéséhez. Nincs szüksége saját kőkészletre." }
    { group:173, id:12, text: "Tárolt kő," }

    { group:174, id:0, text: "Szállítóhajó-kikötő" }
    { group:174, id:1, text: "A hajóácsok által épített szállítóhajók itt horgonyoznak a megbízások között. A zászlóaljadnak szállítóhajókra van szüksége a Níluson való közlekedéshez." }
    { group:174, id:2, text: "Szállítóhajónk a kikötőben van." }
    { group:174, id:3, text: "Szállítóhajónk éppen szállítást végez." }

    { group:175, id:0, text: "Hadihajó-kikötő" }
    { group:175, id:1, text: "Egy hadihajó itt köt ki a csaták között. Minden nílusi városnak legalább néhány védelmi hajót készenlétben kell tartania." }
    { group:175, id:2, text: "Hadihajónk a kikötőben van." }
    { group:175, id:3, text: "Hadihajónk a várost védi a támadásokkal szemben." }

    { group:176, id:0, text: "Bíróság" }
    { group:176, id:1, text: "A bíróságok bírákat küldenek ki, akik a bűnözés csökkentésében segítenek azzal, hogy minden panasz tisztességes elbírálást kap. A bíróság páncéltermei őrzik városod kincstárának egy részét." }
    { group:176, id:2, text: "Ennek a bíróságnak egyáltalán nincsenek dolgozói, ezért a helyi lakosok úgy rendezik saját vitáikat, ahogy csak tudják." }
    { group:176, id:3, text: "Olyan kevés bíró áll rendelkezésre, hogy a peres felek számára a jogi döntések szinte véletlenszerűnek tűnnek." }
    { group:176, id:4, text: "Mivel csak a szükséges dolgozók felével rendelkezik, ez a bíróság néha elhamarkodott ítéleteket hoz." }
    { group:176, id:5, text: "Mivel kissé létszámhiánnyal működik, ennek a bíróságnak kisebb elmaradása van a tárgyalandó ügyekben." }
    { group:176, id:6, text: "A bíróságnak minden szükséges alkalmazottja megvan ahhoz, hogy gyorsan meghallgassa a polgárok panaszait, és körültekintő döntéseket hozzon." }
    { group:176, id:7, text: "A bíró éppen vitákat rendez." }
    { group:176, id:8, text: "A bíró a kamrájában tartózkodik." }
    { group:176, id:9, text: "A páncélterem tartalma" }

    { group:177, id:0, text: "Ezt a termőföldet öntözik." }
    { group:177, id:1, text: "Ezt a termőföldet nem öntözik." }
    { group:177, id:2, text: "A következő áradás ennyi idő múlva érkezik:" }
    { group:177, id:3, text: "Ez a terület rendkívül termékeny földet kínál, most, hogy a folyó visszahúzódott." }
    { group:177, id:4, text: "Ez a terület rendkívül termékeny földet fog kínálni, amint a folyó visszahúzódik." }
    { group:177, id:5, text: "Ennek a gazdaságnak munkásokra van szüksége, akiket egy Munkatáborban lehet kiképezni." }
    { group:177, id:6, text: "Ennek a gazdaságnak teljes létszámú munkáscsapata dolgozik a földeken." }

    { group:178, id:0, text: "befejeződött." }
    { group:178, id:1, text: "A munkások most a piramis külső burkolatán dolgoznak." }
    { group:178, id:2, text: "Ez a feladat" }
    { group:178, id:3, text: "Először a munkásoknak az alapkőzetig meg kell tisztítaniuk a piramis helyét. Több paraszt a Munkatáborokból felgyorsíthatná a tereprendezést." }
    { group:178, id:4, text: "Először a munkásoknak az alapkőzetig meg kell tisztítaniuk a masztaba helyét. Több paraszt a Munkatáborokból felgyorsíthatná a tereprendezést." }
    { group:178, id:5, text: "A munkások most hornyokat vágnak az alapkőzetbe, hogy azok megtartsák a vizet.  Több munkatáborból érkező paraszt felgyorsítaná ezt a munkát." }
    { group:178, id:6, text: "Most a vizet töltjük az alapkőzetbe vájt hornyokba.  Több munkatáborból érkező paraszt gyorsabban végezhetné el ezt a feladatot." }
    { group:178, id:7, text: "A munkások megjelölik a vízszintet, majd leengedik a vizet a hornyokból." }
    { group:178, id:8, text: "Nagyon gondosan az alapkőzetet a vízszint jelöléseiig faragjuk.  Ezt a munkát soha senki nem fogja látni, de ez biztosítja, hogy az emlékmű örökké fennmaradjon." }
    { group:178, id:9, text: "A vízszinthez vájt hornyokat törmelékkel töltjük fel.  Szorosan össze kell tömöríteni, hogy az emlékmű idővel ne süllyedjen meg." }
    { group:178, id:10, text: "A terület előkészítése befejeződött!  Elsimítottuk a földet, és most készen állunk a sír építésére." }
    { group:178, id:11, text: "Az alapot elsimítottuk, és tetőt helyezünk a sírra.  Most már van egy az örökkévalósághoz méltó nyughely." }
    { group:178, id:12, text: "Építésvezető" }
    { group:178, id:13, text: "Azt hiszed, hogy az ég istenei fogják felépíteni ezt az emlékművet?  Építs néhány Munkatábort, hogy paraszti munkaerőhöz juthassak, méghozzá gyorsan!" }
    { group:178, id:14, text: "Nincsenek elérhető kőfaragók, akik ezen az emlékművön dolgozhatnának.  Ha haladást akarsz, azonnal építs egy Kőfaragó céhet!" }
    { group:178, id:15, text: "Gondolom, a projekthez szükséges téglák majd varázslatos módon maguktól összeállnak.  Biztosan ez a terved, hiszen nem építettél Téglaégető céhet." }
    { group:178, id:16, text: "Mivel nincs a városban Ácscéh, amely rámpákat vagy állványokat építene, remélem, nagyon rövid emlékművet tervezel!" }
    { group:178, id:17, text: "Egyetlen paraszt sem jelentkezett munkára.  A helyedben kideríteném, miért.  Lehet, hogy a Munkatáboraid inkább alvótáborokra hasonlítanak." }
    { group:178, id:18, text: "Lenyűgöző kőhalom, nem igaz?  És ennyi is marad belőle mindaddig, amíg néhány kőfaragó meg nem jelenik.  A város Kőfaragó céhe nem fog díjakat nyerni a termelékenységéért..." }
    { group:178, id:19, text: "Köztünk szólva, a város Téglaégető céhe bizonyára valamilyen szórakozóhelynek képzeli magát.  Az biztos, hogy nem küld nekem egyetlen téglavetőt sem." }
    { group:178, id:20, text: "Szükségem van itt egy ácsra, méghozzá azonnal!  Miért nem veted be vezetői képességeidet annál a semmirekellő Ácscéhnél?" }
    { group:178, id:21, text: "Rengeteg ember várakozik itt arra, hogy megjelenjen egy ács.  Bizonyára nagyon ráérősen érkezik meg." }
    { group:178, id:22, text: "Szomorú látvány egy kőfaragó kő nélkül.  Bányássz vagy importálj több egyszerű követ, különben ez az emlékmű soha nem ölthet formát." }
    { group:178, id:23, text: "Jobb lesz, ha több mészkövet bányászol vagy importálsz, ha azt akarod, hogy a kőfaragók még életünkben felépítsék az emlékművet." }
    { group:178, id:24, text: "Ha a város nem importál vagy nem bányászik több homokkövet, a kőfaragónk hamar nyugdíjba vonulhat." }
    { group:178, id:25, text: "Nem lesz valami nagy emlékmű abból a csekély mennyiségű gránitból, amit látok.  Bányássz vagy importálj belőle többet." }
    { group:178, id:26, text: "Ha nem importálsz több márványt, a kőfaragóink soha nem lesznek képesek befejezni ezt az emlékművet." }
    { group:178, id:27, text: "A téglavetőinknek sokkal több téglára van szükségük, mint amennyit kapnak.  Ha nem tudjuk előállítani őket, talán importálhatnál valamennyit." }
    { group:178, id:28, text: "Az ácsaim panaszkodnak a fa hiánya miatt.  Vágj ki több fát, vagy növeld az importot." }
    { group:178, id:29, text: "Kőműveseink készen állnak, hogy rezet helyezzenek a tetőre, ha végre megérkezne.  Bányássz vagy importálj belőle többet." }
    { group:178, id:30, text: "A munkások most csak megtisztítják és elegyengetik az építési területet.  Ez jó alkalom lenne némi egyszerű kő és mészkő felhalmozására.  Sokra lesz szükségünk." }
    { group:178, id:31, text: "Minden jól halad, és a piramis egyre magasabbra és magasabbra emelkedik." }
    { group:178, id:32, text: "A kőművesek most a finom kőmunkát végzik.  Nem lesz több mészkőre szükségünk a munka befejezéséhez." }
    { group:178, id:33, text: "A munkások most csak megtisztítják és elegyengetik az építési területet.  Ezután rengeteg téglára és mészkőre lesz szükségünk ennek az emlékműnek a befejezéséhez." }
    { group:178, id:34, text: "Minden jól halad, és a piramis egyre magasabbra és magasabbra emelkedik." }
    { group:178, id:35, text: "A kőművesek most a finom kőmunkát végzik.  Nem lesz több téglára vagy mészkőre szükségünk a munka befejezéséhez." }
    { group:178, id:36, text: "A munkások most csak megtisztítják és elegyengetik az építési területet.  Ezután rengeteg egyszerű kőre lesz szükségünk ennek az emlékműnek a felépítéséhez." }
    { group:178, id:37, text: "Minden jól halad, és a piramis lépésről lépésre emelkedik." }
    { group:178, id:38, text: "Végre elkészült a piramis!" }
    { group:178, id:39, text: "A munkások most csak megtisztítják az építési területet.  Ezután rengeteg téglára lesz szükségünk a masztabához." }
    { group:178, id:40, text: "Minden jól halad.  Ez a masztaba hamarosan elkészül." }
    { group:178, id:41, text: "A masztaba elkészült." }
    { group:178, id:42, text: "Végre megvan az összes gránit, amire szükségünk van.  Amint az ácsaim befejezik az állványzat építését, a kőfaragók elkezdhetik az obeliszk kifaragását." }
    { group:178, id:43, text: "A kőfaragóim keményen dolgoznak a hatalmas obeliszk kifaragásán." }
    { group:178, id:44, text: "Az obeliszk elkészült!" }
    { group:178, id:45, text: "A kőművesek a szfinx durva formáját alakítják ki." }
    { group:178, id:46, text: "A kőművesek finom faragómunkát végeznek a szfinxen." }
    { group:178, id:47, text: "A munkások befejezik a szfinx kidolgozását és festését." }
    { group:178, id:48, text: "A szfinx elkészült!" }
    { group:178, id:49, text: "Ácsmunkák: " }
    { group:178, id:50, text: "Kőművesmunka: " }
    { group:178, id:51, text: "A város összes parasztjára szükség van az ártéri földeken végzett mezőgazdasági munkákhoz, így évente csak három hónapjuk marad arra, hogy ezen a projekten dolgozzanak.  Építs több Munkatábort az emlékmű helyszínének közelében, hogy felgyorsítsd a munkát." }
    { group:178, id:52, text: "A munkások nem tudnak eljutni az emlékmű előkészített területére.  Nézd meg, mi akadályozza a területet jelölő deszkákat." }
    { group:178, id:53, text: "Most, hogy elegendő homokkövünk van, elkezdhetjük a naptemplom építését.  A munkásaim most éppen megtisztítják a területet." }
    { group:178, id:54, text: "Amint az ácsaim befejezik az állványzat építését, a kőművesek elkezdhetik a naptemplom központi obeliszkjének kifaragását." }
    { group:178, id:55, text: "A kőműveseim most a központi obeliszket faragják.  Amikor végeznek, több homokkőre lesz szükségünk a naptemplom többi részének befejezéséhez." }
    { group:178, id:56, text: "Amint befejezzük az előcsarnokot, a falat és az előtemplomot, ez az emlékmű elkészül." }
    { group:178, id:57, text: "A naptemplom elkészült!" }
    { group:178, id:58, text: "Most, hogy elegendő homokkövünk van, elkezdhetjük ennek az emlékműnek az építését.  A munkásaim most tisztítják a területet." }
    { group:178, id:59, text: "A kőművesek keményen dolgoznak ezen a mauzóleumon.  Minden a tervek szerint halad, és nem számítok semmilyen problémára." }
    { group:178, id:60, text: "A mauzóleum elkészült." }
    { group:178, id:61, text: "A(z) [monument_name] [percent_complete]%-ban elkészült." }
    { group:178, id:62, text: "Még egyetlen kősor sem került teljesen a helyére." }
    { group:178, id:63, text: "Egy kősor már teljesen a helyére került." }
    { group:178, id:64, text: "[number_courses_complete] kősor került teljesen a helyére." }
    { group:178, id:65, text: "A jelenlegi kősor elkészítéséhez [quantity_needed_current_course_main] ([number_loads_current_course_main]) szükséges." }
    { group:178, id:66, text: "A jelenlegi kősor elkészítéséhez [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) szükséges." }
    { group:178, id:67, text: "A jelenlegi kősor elkészítéséhez [quantity_needed_current_course_main] ([number_loads_current_course_main]) és [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) szükséges." }
    { group:178, id:68, text: "A(z) [monument_name] hátralévő részéhez további [quantity_needed_remainder_main] ([number_loads_remainder_main]) szükséges." }
    { group:178, id:69, text: "A(z) [monument_name] hátralévő részéhez további [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary]) szükséges." }
    { group:178, id:70, text: "A(z) [monument_name] hátralévő részéhez további [quantity_needed_remainder_main] ([number_loads_remainder_main]) és [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary]) szükséges." }
    { group:178, id:71, text: "A(z) [monument_name] elkészült, és összesen [quantity_total_main] található benne." }
    { group:178, id:72, text: "A(z) [monument_name] elkészült, és összesen [quantity_total_main] és [quantity_total_secondary] található benne." }
    { group:178, id:73, text: "masztaba" }
    { group:178, id:74, text: "piramis" }
    { group:178, id:75, text: "lépcsős piramis" }
    { group:178, id:76, text: "tört piramis" }
    { group:178, id:77, text: "téglapiramis" }
    { group:178, id:78, text: "obeliszk" }
    { group:178, id:79, text: "szfinx" }
    { group:178, id:80, text: "naptemplom" }
    { group:178, id:81, text: "alexandriai könyvtár" }
    { group:178, id:82, text: "Abu Szimbel" }
    { group:178, id:83, text: "Kis királyi sír" }
    { group:178, id:84, text: "Közepes királyi sír" }
    { group:178, id:85, text: "Nagy királyi sír" }
    { group:178, id:86, text: "Hatalmas királyi sír" }
    { group:178, id:87, text: "Caesareum" }
    { group:178, id:88, text: "világítótorony" }
    { group:178, id:89, text: "mauzóleum" }
    { group:178, id:90, text: "egyszerű kőtömbök" }
    { group:178, id:91, text: "mészkőtömbök" }
    { group:178, id:92, text: "gránittömbök" }
    { group:178, id:93, text: "homokkőtömbök" }
    { group:178, id:94, text: "téglák" }
    { group:178, id:95, text: "márványtömbök" }
    { group:178, id:96, text: "rézrudak" }
    { group:178, id:97, text: "Ennek a mauzóleumnak szüksége van egy ács munkájára." }
    { group:178, id:98, text: "A Kereskedelmi felügyelő nem hajlandó egyszerű követ kiadni a munkásaimnak.  Azt állítja, hogy elrendelted a készletezését.  Nem hiszek neki, de talán helyre kellene tenned." }
    { group:178, id:99, text: "A Kereskedelmi felügyelőd azt mondja, hogy megparancsoltad neki a mészkő készletezését.  Amíg nem beszélsz vele, a munkásaim soha nem kapnak szállítmányt." }
    { group:178, id:100, text: "Tényleg azt mondtad a Kereskedelmi felügyelőnek, hogy készletezze a homokkövet?  Nem engedélyezi a szállítmányok kiadását a Raktárudvarokból." }
    { group:178, id:101, text: "Megkérhetnéd a Kereskedelmi felügyelődet, hogy hagyjon fel a fehér márvány készletezésével?  Nagy szükségünk lenne rá az emlékműnél." }
    { group:178, id:102, text: "A Kereskedelmi felügyelőd azt mondja, hogy megparancsoltad neki a gránit készletezését.  Amíg nem beszélsz vele, a munkásaim soha nem kapnak szállítmányt." }
    { group:178, id:103, text: "A Kereskedelmi felügyelőd még téged mer hibáztatni a munka leállásáért!  Azt állítja, hogy elrendelted a téglák készletezését." }
    { group:178, id:104, text: "A Kereskedelmi felügyelő azt mondta nekem, hogy elrendelted számára a réz készletezését.  Biztos vagyok benne, hogy jó okod van erre, de az embereim nem folytathatják az emlékmű munkálatait ezen nyersanyag nélkül." }
    { group:178, id:105, text: "A fáraó egyáltalán nem fog örülni, ha élettörténete nem a lehető legelegánsabb módon kerül megörökítésre.  Művészcéh nélkül kitől várod, hogy díszítse a sírt?" }
    { group:178, id:106, text: "Elég sivár kinézetű sír, nem igaz?  Ilyen is marad, hacsak néhány művész hamarosan meg nem jelenik!  Mindig is úgy gondoltam, hogy meglehetősen lusta népség.  Jobb lesz, ha utánanézel, mi okozza a késést." }
    { group:178, id:107, text: "Márvány nélkül tehetséges kőfaragóinknak nincs mit tenniük.  Ez igazán nagy kár, mert szívesen látnám őket sokkal elfoglaltabban.  Gondoskodj róla, hogy gyorsan importáljunk némi márványt." }
    { group:178, id:108, text: "Ennek a tetőnek mindenütt be fog ázni, ha nem szerzünk rezet.  Ha nem tudod kibányászni, akkor jobb, ha importálsz belőle.  Minél hamarabb megkapom, annál hamarabb készül el ez az emlékmű!" }
    { group:178, id:109, text: "A munkások megtisztítják és elegyengetik a területet.  Most kiváló alkalom lenne jelentős mennyiségű márvány felhalmozásának megkezdésére." }
    { group:178, id:110, text: "A munka szépen halad.  A munkások minden szükséges nyersanyaggal rendelkeznek." }
    { group:178, id:111, text: "Nehéz elhinni, de a Kereskedelmi felügyelő tájékoztatott, hogy márványt halmoznak fel a raktárudvarainkban.  Márvány nélkül hogyan várhatod el, hogy a munka folytatódjon?" }
    { group:178, id:112, text: "Megbízható forrásból tudom, hogy gránitot készleteznek.  Azt várod, hogy a Nílus homokjából varázsoljam elő, amire szükségem van?  Gondoskodj róla, hogy a kőfaragóim számára azonnal elérhetővé váljon némi gránit." }
    { group:178, id:113, text: "Rézkészlet nélkül hogyan várhatod el, hogy ennek a nagyszerű építménynek a teteje elkészüljön?  Bármilyen hihetetlennek tűnik is, a Kereskedelmi felügyelőd azt mondta nekem, hogy készletezi." }
    { group:178, id:114, text: "Arra várunk, hogy a parasztok megtisztítsák a területet." }
    { group:178, id:115, text: "Most, hogy a terület megtisztult, a kőfaragók lerakják az alapokat." }
    { group:178, id:116, text: "Az alapozás elkészült, így most a padlón dolgozhatunk." }
    { group:178, id:117, text: "Most oszlopokat emelünk, hogy a padló elkészült." }
    { group:178, id:118, text: "A következő lépés a tető megépítése.  Az oszlopok elkészültek." }
    { group:178, id:119, text: "Most rézre van szükségünk a tető befejezéséhez, hogy úgy ragyogjon, mint a nap." }
    { group:178, id:120, text: "Most éppen a Könyvtár utolsó simításait végezzük." }
    { group:178, id:121, text: "Alexandria könyvtára elkészült, és az ismert világ tudásának központja." }
    { group:178, id:122, text: "A parasztok keményen dolgoznak, hogy megtisztítsák a Caesareum számára a területet." }
    { group:178, id:123, text: "Most, hogy a terület készen áll, a kőfaragók serényen rakják le a szilárd alapokat." }
    { group:178, id:124, text: "Fáradt kőfaragóink befejezték az alapozást.  De a fáradtaknak sincs pihenés: a templom építése már folyamatban van." }
    { group:178, id:125, text: "A központi templom elkészültével megkezdődött az udvar építése!" }
    { group:178, id:126, text: "Az udvaroktól a csarnokokig!  Ügyes kőfaragóink befejezték az udvart, és megkezdték a csarnok építését." }
    { group:178, id:127, text: "A kőfaragók elkezdték elhelyezni a tetőt a csarnok oszlopain." }
    { group:178, id:128, text: "A csarnokok minden tetőeleme a helyére került." }
    { group:178, id:129, text: "A Caesareum fenséges bejárata elkészült." }
    { group:178, id:130, text: "A kőfaragók befejezték a Caesareum belső munkálatait, és most az épület külsejét díszítő gránitobeliszkekre fordítják figyelmüket." }
    { group:178, id:131, text: "A Caesareum elkészült, és Egyiptom és Róma egyesülését ünnepli." }
    { group:178, id:132, text: "A parasztok megkezdték a nehéz feladatot, a terület megtisztítását." }
    { group:178, id:133, text: "A kőfaragók szorgosan rakják le a világítótorony alapjait." }
    { group:178, id:134, text: "Az alapozás majdnem elkészült, és a parkettapadló lerakása folyamatban van." }
    { group:178, id:135, text: "A parkettapadló elkészültével a kőfaragók figyelmüket a világítótorony első szintjére fordították." }
    { group:178, id:136, text: "A kőfaragóknak nincs sok idejük csodálni az első szinten végzett munkájukat, mert hamarosan megkezdődik a második, nyolcszögletű szint építése." }
    { group:178, id:137, text: "A világítótorony valóban kezd formát ölteni.  A nyolcszögletű szint elkészült, és a kőfaragók hamarosan megkezdik a kupola építését." }
    { group:178, id:138, text: "A világítótorony utolsó köve is a helyére került, de az emlékmű nem lesz teljes, amíg az állványzatot el nem távolítják.  Ez a munka most kezdődik." }
    { group:178, id:139, text: "Az állványzat nagy részét eltávolították, és a világítótorony már majdnem elkészült." }
    { group:178, id:140, text: "A Pharoszi világítótorony elkészült, és jelzőfényként ragyog a Földközi-tenger keleti része felett." }
    { group:178, id:141, text: "A munkások szorgosan dolgoznak Abu Szimbelen.  Gondoskodj róla, hogy az ácsoknak elegendő fájuk legyen, hogy időben felépíthessék az állványzatot." }
    { group:178, id:142, text: "Nagy Ramszesz II. lenyűgöző szobrai üdvözölnek mindenkit, aki délről érkezik Egyiptomba." }
    { group:178, id:143, text: "A művészek és kőművesek nem hajlandók belépni a Királyi sírba lámpások nélkül.  Odabent rettenetesen sötét van!" }
    { group:178, id:144, text: "A művészek és kőművesek szorgalmasan végzik mesterségüket, és a Királyi sír építése szépen halad.  Ne felejtsd el, hogy a Művészcéhnek folyamatosan biztosíts agyagot és festéket, hogy minden zökkenőmentesen menjen." }
    { group:178, id:145, text: "A Királyi sír elkészült.  Már csak az elhunyt számára szükséges temetési kellékek hiányoznak, amelyeket a Nádasok mezején fog használni." }
    { group:178, id:146, text: "A rejtett Királyi sír készen áll a fáraó fogadására.  Hórusz őrizze a sírt, és sújtson le mindenkire, aki merészelné megsérteni azt!" }
    { group:178, id:147, text: "Lámpások:" }
    { group:178, id:148, text: "A munkások nem tudnak eljutni a sír bejáratához.  Nézd meg, mi akadályozza az utat." }
    { group:178, id:149, text: "A munkások nem tudnak eljutni az emlékmű előkészített területére.  Nézd meg, mi akadályozza a hozzáférésüket." }
    { group:179, id:0, text: "Munkatábor" }
    { group:179, id:1, text: "Ez a Munkatábor olyan munkásokat szállásol el, akik az ártéri földeken vagy az emlékműveken dolgozhatnak." }
    { group:179, id:2, text: "Ennek a Munkatábornak munkásokra van szüksége az itt állomásozó fizikai dolgozók támogatásához." }
    { group:179, id:3, text: "Amennyi szakképzetlen munkaerőt csak emberileg lehetséges, biztosítunk." }
    { group:179, id:4, text: "Munkásaink munkát keresnek." }
    { group:179, id:5, text: "Munkásaink az ártéri földeken dolgoznak." }
    { group:179, id:6, text: "Munkásaink emlékműveken dolgoznak." }
    { group:179, id:7, text: "Munkásaink az ártéri földeken és az emlékműveken is dolgoznak." }
    { group:180, id:0, text: "Téglagyár" }
    { group:180, id:1, text: "Itt agyagot és szalmát kevernek össze, hogy erős, tartós téglákat készítsenek." }
    { group:180, id:2, text: "A termelés" }
    { group:180, id:3, text: "kész." }
    { group:180, id:4, text: "A Kereskedelmi felügyelőd leállíttatta a téglagyártást." }
    { group:180, id:5, text: "Ennek a Téglagyárnak nincsenek dolgozói.  Egyetlen tégla sem készülhet." }
    { group:180, id:6, text: "Ennek a műhelynek minden szükséges dolgozója megvan.  Rengeteg téglát állít elő." }
    { group:180, id:7, text: "Ennek a Téglagyárnak vannak betöltetlen munkahelyei, ami némileg lassítja a téglagyártást." }
    { group:180, id:8, text: "Ennek a műhelynek kevés a dolgozója, ezért a téglák előállítása tovább tart a kelleténél." }
    { group:180, id:9, text: "Nagyon kevesen dolgoznak itt.  A téglagyártás sokkal lassabb, mint amilyen lehetne." }
    { group:180, id:10, text: "Alig néhány munkással ez a Téglagyár nagyon kevés téglát fog előállítani a következő évben." }
    { group:180, id:11, text: "Ennek a műhelynek agyagot kell szállítani egy Raktárudvarból vagy Agyagbányából, hogy téglát gyárthasson." }
    { group:180, id:12, text: "Ennek a műhelynek szalmát kell szállítani egy Raktárudvarból vagy Gabonafarmról, hogy téglát gyárthasson." }
    { group:180, id:13, text: "Agyag: " }
    { group:180, id:14, text: "Szalmа: " }
    { group:181, id:0, text: "Árpafarm" }
    { group:181, id:1, text: "Az árpa a sör egyik alapvető összetevője, amely nélkül civilizációnk bizonyára nem is létezne." }
    { group:181, id:2, text: "A termelés" }
    { group:181, id:3, text: "kész." }
    { group:181, id:4, text: "A Kereskedelmi felügyelőd elrendelte, hogy az árpatermesztést be kell szüntetni." }
    { group:181, id:5, text: "Ennek a farmnak nincsenek dolgozói.  A föld parlagon hever." }
    { group:181, id:6, text: "Ennek a farmnak minden szükséges dolgozója megvan.  A terméshozam a lehető legmagasabb a föld termékenységéhez képest." }
    { group:181, id:7, text: "Ennek a farmnak van néhány betöltetlen munkahelye.  Több dolgozóval több árpát termeszthetne." }
    { group:181, id:8, text: "Ennek a farmnak kevés a dolgozója.  Az árpatermés sokkal jobb lehetne." }
    { group:181, id:9, text: "Olyan kevés földműves dolgozik itt, hogy éppen csak elegendő árpánk van a „könnyű” sörhöz." }
    { group:181, id:10, text: "Ha ezen a farmon alig dolgoznak, az egyiptomiak hamarosan kénytelenek lesznek vízen élni." }
    { group:181, id:11, text: "Ennek a farmnak a földjét a közelmúltbeli sáskajárás tönkretette, és időbe telik, mire helyreáll." }
    { group:181, id:12, text: "A föld" }
    { group:181, id:13, text: "termékeny." }
    { group:181, id:14, text: "A következő árpaaratás" }
    { group:182, id:0, text: "Csicseriborsó-farm" }
    { group:182, id:1, text: "A csicseriborsó sokoldalú fehérjeforrás, és néped étrendjében igen népszerű." }
    { group:182, id:2, text: "A termelés" }
    { group:182, id:3, text: "kész." }
    { group:182, id:4, text: "A Kereskedelmi felügyelőd leállíttatta a csicseriborsó-termesztést." }
    { group:182, id:5, text: "Ennek a farmnak nincsenek dolgozói.  A föld parlagon hever." }
    { group:182, id:6, text: "Ennek a farmnak minden szükséges dolgozója megvan.  A terméshozam a lehető legmagasabb a föld termékenységéhez képest." }
    { group:182, id:7, text: "Ez a farm több dolgozót szeretne alkalmazni.  Több csicseriborsót termelhetne, mint amennyit jelenleg termel." }
    { group:182, id:8, text: "Ennek a farmnak kevés a dolgozója.  Munkásai kevesebb csicseriborsót termelnek, mint amennyit a föld hozhatna." }
    { group:182, id:9, text: "Nagyon kevés földműves dolgozik itt.  A csicseriborsó-termelés messze elmarad a maximumtól." }
    { group:182, id:10, text: "Ha ezen a farmon alig dolgoznak, a csicseriborsó-termés jelentéktelen lesz." }
    { group:182, id:11, text: "Ennek a farmnak a földjét a közelmúltbeli sáskajárás tönkretette, és időbe telik, mire helyreáll." }
    { group:182, id:12, text: "A föld" }
    { group:182, id:13, text: "termékeny." }
    { group:182, id:14, text: "A következő csicseriborsó-betakarítás" }
    { group:183, id:0, text: "Fügefarm" }
    { group:183, id:1, text: "A füge fontos szerepet játszik az egészséghez és boldogsághoz szükséges kiegyensúlyozott étrendben." }
    { group:183, id:2, text: "A termelés" }
    { group:183, id:3, text: "kész." }
    { group:183, id:4, text: "A Kereskedelmi felügyelőd leállíttatta a fügetermesztést." }
    { group:183, id:5, text: "Ennek a ligetnek nincsenek dolgozói.  A fák vadon nőnek és terméketlenek." }
    { group:183, id:6, text: "Ennek a ligetnek minden szükséges dolgozója megvan.  A termékenységéhez képest maximális termést hoz." }
    { group:183, id:7, text: "Ennek a ligetnek több dolgozóra lenne szüksége.  Több fügét termelhetne." }
    { group:183, id:8, text: "Ennek a ligetnek kevés a dolgozója.  Munkásai kevesebb fügét szüretelnek, mint amennyit egyébként tudnának." }
    { group:183, id:9, text: "Nagyon kevés földműves dolgozik itt.  A fügetermelés messze elmarad a maximumtól." }
    { group:183, id:10, text: "Ha ezen a farmon alig dolgoznak, alig fog teremni valami." }
    { group:183, id:11, text: "Ennek a farmnak a földjét a közelmúltbeli sáskajárás tönkretette, és időbe telik, mire helyreáll." }
    { group:183, id:12, text: "A föld" }
    { group:183, id:13, text: "termékeny." }
    { group:183, id:14, text: "A következő fügeszüret" }
    { group:184, id:0, text: "Szállítás" }
    { group:184, id:1, text: "Hadihajó" }
    { group:184, id:2, text: "Hajótest állapota" }
    { group:184, id:3, text: "Nagyon erős" }
    { group:184, id:4, text: "Erős" }
    { group:184, id:5, text: "Jó" }
    { group:184, id:6, text: "Átlagos" }
    { group:184, id:7, text: "Megfelelő" }
    { group:184, id:8, text: "Gyenge" }
    { group:184, id:9, text: "Helyben maradás" }
    { group:184, id:10, text: "Ha ezt a parancsot kapja, a hajó a helyén marad, és feltartóztat minden ellenséges hajót, amíg a vízen marad." }
    { group:184, id:11, text: "Közeli ellenségek megtámadása" }
    { group:184, id:12, text: "Ezzel a paranccsal a hadihajó egy kisebb területet őriz.  Megtámad minden hatótávolságába kerülő ellenséges katonát vagy hajót." }
    { group:184, id:13, text: "Minden ellenség felkutatása és megsemmisítése" }
    { group:184, id:14, text: "Ezzel a paranccsal a hadihajó messze földön ellenséges hajókat és katonákat keres, és megtámad mindenkit, akit elér." }
    { group:184, id:15, text: "Javítás" }
    { group:184, id:16, text: "A hajó visszatér egy Hajóácshoz javításra.  A súlyosan sérült hajók kapitányai saját kezdeményezésükre is javításra indulnak." }
    { group:184, id:17, text: "Visszatérés a kikötőbe" }
    { group:184, id:18, text: "Ez a parancs arra utasítja a hajót, hogy térjen vissza a hozzá tartozó Kikötőbe, ahol legénysége pihenhet és új erőre kaphat." }
    { group:184, id:19, text: "Helyben maradás" }
    { group:184, id:20, text: "Ha ezt a parancsot kapja, a hajó mindenáron a helyén marad.  Ha megtámadják, lehet, hogy nem marad sokáig a vízen." }
    { group:184, id:21, text: "Ellenségek elkerülése" }
    { group:184, id:22, text: "Ennek a hajónak a kapitánya állandó parancsot kapott az elkerülésre.  Amíg más utasítást nem kap, mindenáron kerüli az ellenséggel való találkozást." }
    { group:184, id:23, text: "Felszállás" }
    { group:184, id:24, text: "Ez a parancs arra utasítja a hajó kapitányát, hogy vegyen fel egy katonai egységet szállításra." }
    { group:184, id:25, text: "Kiszállás" }
    { group:184, id:26, text: "Ez a parancs arra utasítja a kapitányt, hogy tegye partra a katonai egységet." }
    { group:184, id:27, text: "Legénység fáradtsága" }
    { group:184, id:28, text: "Pihent" }
    { group:184, id:29, text: "Fáradt" }
    { group:184, id:30, text: "Kimerült" }
    { group:184, id:31, text: "Íjász század," }
    { group:184, id:32, text: "Harci szekér század," }
    { group:184, id:33, text: "Gyalogsági század," }
    { group:184, id:34, text: "a fedélzeten" }
    { group:185, id:0, text: "Harci szekér műhely" }
    { group:185, id:1, text: "Itt képzett kézművesek készítik a „háborús kerekeket”, Egyiptom egyik leghalálosabb fegyverét." }
    { group:185, id:2, text: "A termelés" }
    { group:185, id:3, text: "kész." }
    { group:185, id:4, text: "A Kereskedelmi felügyelőd elrendelte a harci szekér gyártásának leállítását." }
    { group:185, id:5, text: "Ennek a Harci szekér készítő műhelynek nincsenek dolgozói, ezért egyetlen háborús kereket sem fog előállítani." }
    { group:185, id:6, text: "Ennek a Harci szekér készítő műhelynek minden szükséges dolgozója megvan, és sok kiváló minőségű harci szekeret állít elő." }
    { group:185, id:7, text: "Ennek a Harci szekér készítő műhelynek több dolgozóra lenne szüksége, hogy elérje a harci szekérgyártásban rejlő teljes lehetőségeit." }
    { group:185, id:8, text: "Ennek a Harci szekér készítő műhelynek kevés a dolgozója, ezért a kelleténél lassabban készíti a harci szekereket." }
    { group:185, id:9, text: "Nagyon kevesen dolgoznak ebben a Harci szekér készítő műhelyben.  Ennek következtében lassú a harci szekér gyártása." }
    { group:185, id:10, text: "Alig néhány dolgozóval ez a Harci szekér készítő műhely nagyon kevés harci szekeret fog előállítani a következő évben." }
    { group:185, id:11, text: "Ez a műhely egyetlen harci szekeret sem tud készíteni fa szállítása nélkül, akár egy Raktárudvarból, akár egy Fakitermelőből érkezik." }
    { group:185, id:12, text: "Tárolt fa," }
    { group:187, id:0, text: "Ismeretlen" }
    { group:187, id:1, text: "Helyi istenség" }
    { group:187, id:2, text: "Védőisten" }
    { group:188, id:0, text: "Ünnepi tér" }
    { group:188, id:1, text: "Amikor utasítod a Templomok felügyelőjét, hogy rendezzen ünnepséget valamelyik isten tiszteletére, a polgárok itt gyűlnek össze, hogy részt vegyenek rajta." }
    { group:188, id:2, text: "Rendezz ünnepséget, hogy boldoggá tedd a népet és kiengeszteld az isteneket." }
    { group:188, id:3, text: "Jelenleg ünnepség zajlik." }
    { group:189, id:0, text: "Sebeck oltára" }
    { group:189, id:1, text: "Min jóslata" }
    { group:189, id:2, text: "Ma'at oltára" }
    { group:189, id:3, text: "Hórusz jóslata" }
    { group:189, id:4, text: "Amon oltára" }
    { group:189, id:5, text: "Thot jóslata" }
    { group:189, id:6, text: "Anubisz oltára" }
    { group:189, id:7, text: "Szehmet jóslata" }
    { group:189, id:8, text: "Ízisz oltára" }
    { group:189, id:9, text: "Hathor jóslata" }
    { group:190, id:0, text: "Papiruszkészítő" }
    { group:190, id:1, text: "Itt a nádkötegeket összekötik, hogy papiruszt készítsenek belőlük, amelyre az oktatási intézményeknek szükségük van az információk lejegyzéséhez és a tudás megosztásához.  A papirusz jövedelmezően kereskedhető is." }
    { group:190, id:2, text: "A termelés" }
    { group:190, id:3, text: "kész." }
    { group:190, id:4, text: "A Kereskedelmi felügyelőd elrendelte a papiruszgyártás leállítását." }
    { group:190, id:5, text: "Ennek a Papiruszkészítőnek nincsenek dolgozói, ezért semmilyen terméket nem fog előállítani." }
    { group:190, id:6, text: "Ennek a Papiruszkészítőnek minden szükséges dolgozója megvan, és elegendő mennyiségű kiváló minőségű papiruszt állít elő." }
    { group:190, id:7, text: "Ennek a Papiruszkészítőnek több dolgozóra lenne szüksége, hogy elérje a papiruszgyártásban rejlő teljes lehetőségeit." }
    { group:190, id:8, text: "Ennek a Papiruszkészítőnek kevés a dolgozója, ezért a kelleténél lassabban készít papiruszt." }
    { group:190, id:9, text: "Nagyon kevesen dolgoznak ebben a műhelyben.  Ennek következtében lassú a papiruszgyártás." }
    { group:190, id:10, text: "Alig néhány dolgozóval ez a Papiruszkészítő kevés papiruszt fog előállítani a következő évben." }
    { group:190, id:11, text: "Ez a műhely nem tud papiruszt készíteni nád szállítása nélkül, akár egy Raktárudvarból, akár egy Nádgyűjtőtől érkezik." }
    { group:190, id:12, text: "Tárolt nád," }
    { group:191, id:0, text: "Csalás párbeszéd" }
    { group:191, id:1, text: "Csalások kikapcsolása" }
    { group:192, id:0, text: "Gránitbánya" }
    { group:192, id:1, text: "Az obeliszkekhez szükséges súlyos, erős gránittömböket itt faragod ki a föld mélyének sziklás alapjából." }
    { group:192, id:2, text: "A termelés" }
    { group:192, id:3, text: "kész." }
    { group:192, id:4, text: "A Kereskedelmi felügyelőd elrendelte, hogy több gránitot ne bányásszanak." }
    { group:192, id:5, text: "Ennek a bányának nincsenek dolgozói.  A termelés leállt." }
    { group:192, id:6, text: "Ennek a bányának minden szükséges dolgozója megvan, és teljes kapacitással dolgozik a gránit kitermelésén." }
    { group:192, id:7, text: "Ez a bánya nem teljes kapacitással működik.  Több dolgozóval a termelés kissé hatékonyabb lehetne." }
    { group:192, id:8, text: "Ennek a bányának kevés a dolgozója.  A gránit kitermelése tovább tart a kelleténél." }
    { group:192, id:9, text: "Nagyon kevesen dolgoznak itt.  A bánya nagyon kevés gránitot termel." }
    { group:192, id:10, text: "Alig néhány dolgozóval a termelés szinte leállt.  A következő évben csak keveset fog előállítani." }
    { group:193, id:0, text: "Rézbánya" }
    { group:193, id:1, text: "A könnyen megmunkálható és tartós rézből kiváló fegyverek és értékes exportáru készül." }
    { group:193, id:2, text: "A termelés" }
    { group:193, id:3, text: "kész." }
    { group:193, id:4, text: "A Kereskedelmi felügyelőd leállíttatta a rézbányászatot." }
    { group:193, id:5, text: "Ennek a bányának nincsenek dolgozói.  A termelés leállt." }
    { group:193, id:6, text: "Ennek a bányának minden szükséges dolgozója megvan, és rengeteg rezet termel." }
    { group:193, id:7, text: "Ez a bánya nem teljes kapacitással működik.  Több dolgozóval a termelés kissé hatékonyabb lehetne." }
    { group:193, id:8, text: "Ennek a bányának kevés a dolgozója.  A réz kitermelése tovább tart a kelleténél." }
    { group:193, id:9, text: "Nagyon kevesen dolgoznak ebben az épületben.  Ennek következtében lassú a termelés." }
    { group:193, id:10, text: "Alig néhány dolgozóval a termelés szinte leállt.  A következő évben csak keveset fog előállítani." }
    { group:194, id:0, text: "Homokkőbánya" }
    { group:194, id:1, text: "Csak a homokkő rendelkezik a megfelelő tulajdonságokkal a mauzóleumok és naptemplomok építéséhez." }
    { group:194, id:2, text: "A termelés" }
    { group:194, id:3, text: "kész." }
    { group:194, id:4, text: "A Kereskedelmi felügyelőd elrendelte, hogy több homokkövet ne bányásszanak." }
    { group:194, id:5, text: "Ennek a bányának nincsenek dolgozói.  A termelés leállt." }
    { group:194, id:6, text: "Ennek a bányának minden szükséges dolgozója megvan, és teljes kapacitással dolgozik a homokkő kitermelésén." }
    { group:194, id:7, text: "Ez a bánya nem teljes kapacitással működik.  Több dolgozóval a termelés kissé hatékonyabb lehetne." }
    { group:194, id:8, text: "Ennek a bányának kevés a dolgozója.  A homokkő kitermelése tovább tart a kelleténél." }
    { group:194, id:9, text: "Nagyon kevesen dolgoznak ebben az épületben.  Ennek következtében rendkívül lassú a termelés." }
    { group:194, id:10, text: "Alig néhány dolgozóval a termelés szinte leállt.  A következő évben csak keveset fog előállítani." }
    { group:195, id:0, text: "Abu" }
    { group:195, id:1, text: "Abedzsu" }
    { group:195, id:2, text: "Baharía-oázis" }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubasztisz" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Büblosz" }
    { group:195, id:8, text: "Dahsúr" }
    { group:195, id:9, text: "Dakhla-oázis" }
    { group:195, id:10, text: "Dzsedu" }
    { group:195, id:11, text: "Dunkul-oázis" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "Farafra-oázis" }
    { group:195, id:14, text: "Gáza" }
    { group:195, id:15, text: "Heh" }
    { group:195, id:16, text: "Henen-neszu" }
    { group:195, id:17, text: "Hetepszeneuszret" }
    { group:195, id:18, text: "Iken" }
    { group:195, id:19, text: "Itjtavi" }
    { group:195, id:20, text: "Iunet" }
    { group:195, id:21, text: "Jerikó" }
    { group:195, id:22, text: "Kebet" }
    { group:195, id:23, text: "Kerma" }
    { group:195, id:24, text: "Kharga-oázis" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knósszosz" }
    { group:195, id:27, text: "Küréné" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mükéné" }
    { group:195, id:32, text: "Nekhen" }
    { group:195, id:33, text: "Nubt" }
    { group:195, id:34, text: "On" }
    { group:195, id:35, text: "Peruadzsit" }
    { group:195, id:36, text: "Puenet" }
    { group:195, id:37, text: "Kádes" }
    { group:195, id:38, text: "Rosztja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Szakkara" }
    { group:195, id:41, text: "Szauti" }
    { group:195, id:42, text: "Szavu" }
    { group:195, id:43, text: "Szelima-oázis" }
    { group:195, id:44, text: "Szerabit el-Khadim" }
    { group:195, id:45, text: "Shaat" }
    { group:195, id:46, text: "Sharuhen" }
    { group:195, id:47, text: "Thinisz" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toska" }
    { group:195, id:50, text: "Türosz" }
    { group:195, id:51, text: "Waszet" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alexandria" }
    { group:195, id:54, text: "Szümur" }
    { group:195, id:55, text: "Deir el-Medina" }
    { group:195, id:56, text: "Abu Szimbel" }
    { group:195, id:57, text: "Actium" }
    { group:195, id:58, text: "Róma" }
    { group:195, id:59, text: "Tanisz" }
    { group:195, id:60, text: "Pi-Jer" }
    { group:195, id:61, text: "Sziwi-oázis" }
    { group:195, id:62, text: "Maritisz" }
    { group:195, id:63, text: "Piramesz" }
    { group:195, id:64, text: "Athén" }
    { group:195, id:65, text: "Kleoantonopolisz" }
    { group:196, id:0, text: "KRÉTA" }
    { group:196, id:1, text: "CIPRUS" }
    { group:196, id:2, text: "KELET-AFRIKA" }
    { group:196, id:3, text: "KELETI-SIVATAG" }
    { group:196, id:4, text: "GÖRÖGORSZÁG" }
    { group:196, id:5, text: "LÍBIA" }
    { group:196, id:6, text: "ALSÓ-EGYIPTOM" }
    { group:196, id:7, text: "DELTA" }
    { group:196, id:8, text: "FÁJÚM" }
    { group:196, id:9, text: "NÚBIA" }
    { group:196, id:10, text: "PALESZTINA" }
    { group:196, id:11, text: "SÍNAI-félsziget" }
    { group:196, id:12, text: "SZÍRIA" }
    { group:196, id:13, text: "FELSŐ-EGYIPTOM" }
    { group:196, id:14, text: "NYUGATI-SIVATAG" }
    { group:196, id:15, text: "LIBANON" }
    { group:196, id:16, text: "KÁNAÁN" }
    { group:198, id:0, text: "Nincs" }
    { group:198, id:1, text: "Kis tört piramis" }
    { group:198, id:2, text: "Közepes tört piramis" }
    { group:198, id:3, text: "Kis vályogtégla-piramis" }
    { group:198, id:4, text: "Közepes vályogtégla-piramis" }
    { group:198, id:5, text: "Nagy vályogtégla-piramis" }
    { group:198, id:6, text: "Vályogtégla-piramis komplexum" }
    { group:198, id:7, text: "Nagyszabású vályogtégla-piramis komplexum" }
    { group:198, id:8, text: "Kis lépcsős piramis" }
    { group:198, id:9, text: "Közepes lépcsős piramis" }
    { group:198, id:10, text: "Nagy lépcsős piramis" }
    { group:198, id:11, text: "Lépcsős piramis komplexum" }
    { group:198, id:12, text: "Nagyszabású lépcsős piramis komplexum" }
    { group:198, id:13, text: "Kis piramis" }
    { group:198, id:14, text: "Közepes piramis" }
    { group:198, id:15, text: "Nagy piramis" }
    { group:198, id:16, text: "Piramis komplexum" }
    { group:198, id:17, text: "Nagyszabású piramis komplexum" }
    { group:198, id:18, text: "Kis masztaba" }
    { group:198, id:19, text: "Közepes masztaba" }
    { group:198, id:20, text: "Nagy masztaba" }
    { group:198, id:21, text: "Szfinx" }
    { group:198, id:22, text: "Kis obeliszk" }
    { group:198, id:23, text: "Nagy obeliszk" }
    { group:198, id:24, text: "Naptemplom" }
    { group:198, id:25, text: "Mauzóleum" }
    { group:198, id:26, text: "Mauzóleum" }
    { group:198, id:27, text: "Mauzóleum" }
    { group:198, id:28, text: "Pharoszi világítótorony" }
    { group:198, id:29, text: "Alexandriai könyvtár" }
    { group:198, id:30, text: "Caesareum" }
    { group:198, id:31, text: "Kolosszusok" }
    { group:198, id:32, text: "Luxori templom" }
    { group:198, id:33, text: "Kis királyi sír" }
    { group:198, id:34, text: "Közepes királyi sír" }
    { group:198, id:35, text: "Nagy királyi sír" }
    { group:198, id:36, text: "Nagyszabású királyi sír" }
    { group:198, id:37, text: "Abu Szimbel" }
    { group:199, id:0, text: "Emlékművek felügyelője" }
    { group:199, id:1, text: "Raktáron" }
    { group:199, id:2, text: "Elkészült" }
    { group:199, id:3, text: "Kattints a temetkezési kellékekre a szállításhoz." }
    { group:199, id:4, text: "Kiszállítandó mennyiség" }
    { group:199, id:5, text: "Mind" }
    { group:199, id:6, text: "Kattints a kiszállításhoz" }
    { group:199, id:7, text: "Mégsem" }
    { group:199, id:8, text: "Mennyiség növelése" }
    { group:199, id:9, text: "Mennyiség csökkentése" }
    { group:199, id:10, text: "Temetkezési kellékek kiszállítása" }
    { group:199, id:11, text: "Emlékmű értékelése" }
    { group:199, id:12, text: "Nincs kiszállítandó temetkezési kellék." }
    { group:199, id:13, text: "További részletekért látogasd meg az építési területet." }
    { group:199, id:14, text: "Ennek a piramisnak az építése még nem kezdődött el.  Paraszti munkaerőre van szükséged a projekt megkezdéséhez," }
    { group:199, id:15, text: "valamint rengeteg sima kőtömbre és mészkőre a befejezéséhez." }
    { group:199, id:16, text: "Ez a piramis " }
    { group:199, id:17, text: "Ez a piramis most már elkészült!" }
    { group:199, id:18, text: "Ez a piramis elkészült.  Örökké őrizni fogja a szent maradványokat." }
    { group:199, id:19, text: "Ennek a téglapiramisnak az építése még nem kezdődött el.  Paraszti munkaerőre van szükséged a projekt megkezdéséhez," }
    { group:199, id:20, text: "valamint rengeteg téglára és mészkőre a befejezéséhez." }
    { group:199, id:21, text: "Ez a téglapiramis   " }
    { group:199, id:22, text: "Ez a téglapiramis most már elkészült!" }
    { group:199, id:23, text: "Ez a piramis elkészült.  Örökké őrizni fogja a szent maradványokat." }
    { group:199, id:24, text: "Ennek a lépcsős piramisnak az építése még nem kezdődött el.  Paraszti munkaerőre van szükséged" }
    { group:199, id:25, text: "a projekt megkezdéséhez, valamint rengeteg sima kőtömbre a befejezéséhez." }
    { group:199, id:26, text: "Ez a lépcsős piramis " }
    { group:199, id:27, text: "Ez a lépcsős piramis most már elkészült!" }
    { group:199, id:28, text: "Ez a lépcsős piramis elkészült.  Örökké őrizni fogja a szent maradványokat." }
    { group:199, id:29, text: "Ennek a tört piramisnak az építése még nem kezdődött el.  Paraszti munkaerőre van szükséged a projekt megkezdéséhez," }
    { group:199, id:30, text: "valamint rengeteg sima kőtömbre és mészkőre a befejezéséhez." }
    { group:199, id:31, text: "Ez a tört piramis" }
    { group:199, id:32, text: "Ez a tört piramis most már elkészült!" }
    { group:199, id:33, text: "Ez a tört piramis elkészült.  Örökké őrizni fogja a szent maradványokat." }
    { group:199, id:34, text: "Ennek a masztabának az építése még nem kezdődött el.  Paraszti munkaerőre van szükséged a projekt megkezdéséhez," }
    { group:199, id:35, text: "valamint megfelelő mennyiségű téglára a befejezéséhez." }
    { group:199, id:36, text: "Ez a masztaba " }
    { group:199, id:37, text: "Ez a masztaba most már elkészült!" }
    { group:199, id:38, text: "Ez a masztaba elkészült, és örökké őrizni fogja a szent maradványokat." }
    { group:199, id:39, text: "Ennek a szfinxnek az építése még nem kezdődött el.  Szükséged van ácsokra, kőfaragókra," }
    { group:199, id:40, text: "fára és sima kőtömbökre a projekt megkezdéséhez." }
    { group:199, id:41, text: "Ez a szfinx " }
    { group:199, id:42, text: "Ez a szfinx most már elkészült!" }
    { group:199, id:43, text: "Ennek az obeliszknek az építése még nem kezdődött el.  Szükséged lesz" }
    { group:199, id:44, text: "gránittömbökre a projekt megkezdéséhez.  Neked van " }
    { group:199, id:45, text: "Ez az obeliszk" }
    { group:199, id:46, text: "Ez az obeliszk most már elkészült!" }
    { group:199, id:47, text: "Ennek a naptemplomnak az építése még nem kezdődött el.  Szükséged lesz" }
    { group:199, id:48, text: "homokkőtömbökre a projekt megkezdéséhez.  Neked van " }
    { group:199, id:49, text: "Ez a naptemplom" }
    { group:199, id:50, text: "Ez a naptemplom most már elkészült!" }
    { group:199, id:51, text: "Ennek a mauzóleumnak az építése még nem kezdődött el. Szükséged lesz " }
    { group:199, id:52, text: "homokkőtömbökre a projekt megkezdéséhez. Rendelkezel " }
    { group:199, id:53, text: "Ez a mauzóleum " }
    { group:199, id:54, text: "Ez a mauzóleum mostanra elkészült!" }
    { group:199, id:55, text: "Ez a mauzóleum elkészült, és örökre itt fogja őrizni a szent maradványokat. " }
    { group:199, id:56, text: "Kattints az építési terület megtekintéséhez." }
    { group:199, id:57, text: "tömb tárolva" }
    { group:199, id:58, text: "tömb tárolva" }
    { group:199, id:59, text: "Alexandria könyvtárának építése még nem kezdődött el. Szükséged lesz paraszti munkaerőre" }
    { group:199, id:60, text: "a projekt megkezdéséhez, valamint márvány- és rézkészletre a befejezéséhez." }
    { group:199, id:61, text: "Az alexandriai könyvtár " }
    { group:199, id:62, text: "Az alexandriai könyvtár mostanra elkészült!" }
    { group:199, id:63, text: "A Caesareum építése még nem kezdődött el. Szükséged lesz paraszti munkaerőre " }
    { group:199, id:64, text: "a projekt megkezdéséhez, valamint márvány- és gránitkészletre a befejezéséhez." }
    { group:199, id:65, text: "A Caesareum " }
    { group:199, id:66, text: "A Caesareum mostanra elkészült!" }
    { group:199, id:67, text: "A Pharosz világítótorony építése még nem kezdődött el. Szükséged lesz paraszti" }
    { group:199, id:68, text: "munkaerőre a projekt megkezdéséhez, valamint márványkészletre a befejezéséhez." }
    { group:199, id:69, text: "A Pharosz világítótorony " }
    { group:199, id:70, text: "A Pharosz világítótorony mostanra elkészült!" }
    { group:199, id:71, text: "Abu Szimbel építése még nem kezdődött el. Szükséged lesz ácsokra, kőfaragókra " }
    { group:199, id:72, text: "és fakészletre a projekt megkezdéséhez." }
    { group:199, id:73, text: "Abu Szimbel " }
    { group:199, id:74, text: "Abu Szimbel mostanra elkészült!" }
    { group:199, id:75, text: "A Kis Sírkamra építése még nem kezdődött el. Szükséged lesz kőfaragókra," }
    { group:199, id:76, text: "kézművesekre, agyagra, festékre és lámpásokra a projekt megkezdéséhez." }
    { group:199, id:77, text: "A Kis Királyi Sírkamra " }
    { group:199, id:78, text: "A Kis Királyi Sírkamra mostanra elkészült!" }
    { group:199, id:79, text: "A Közepes Sírkamra építése még nem kezdődött el. Szükséged lesz " }
    { group:199, id:80, text: "kőfaragókra, kézművesekre, agyagra, festékre és lámpásokra a projekt megkezdéséhez." }
    { group:199, id:81, text: "A Közepes Királyi Sírkamra " }
    { group:199, id:82, text: "A Közepes Királyi Sírkamra mostanra elkészült!" }
    { group:199, id:83, text: "A Nagy Sírkamra építése még nem kezdődött el. Szükséged lesz kőfaragókra," }
    { group:199, id:84, text: "kézművesekre, agyagra, festékre és lámpásokra a projekt megkezdéséhez." }
    { group:199, id:85, text: "A Nagy Királyi Sírkamra " }
    { group:199, id:86, text: "A Nagy Királyi Sírkamra mostanra elkészült!" }
    { group:199, id:87, text: "A Hatalmas Sírkamra építése még nem kezdődött el. Szükséged lesz kőfaragókra," }
    { group:199, id:88, text: "kézművesekre, agyagra, festékre és lámpásokra a projekt megkezdéséhez." }
    { group:199, id:89, text: "A Hatalmas Királyi Sírkamra " }
    { group:199, id:90, text: "A Hatalmas Királyi Sírkamra mostanra elkészült!" }
    { group:200, id:0, text: "Első fázis: Szerezz gránitot a nyers szerkezet elkészítéséhez" }
    { group:200, id:1, text: "Második fázis: Az ácsok fát használnak az állványzat felépítéséhez" }
    { group:200, id:2, text: "Harmadik fázis: A kőfaragók kialakítják a végső formát, felülről lefelé haladva" }
    { group:200, id:3, text: "Állapot:" }
    { group:200, id:4, text: "Nem kezdődött el" }
    { group:200, id:5, text: "Befejezetlen" }
    { group:200, id:6, text: "Elkészült" }
    { group:200, id:7, text: "Teljes előrehaladás:" }
    { group:201, id:0, text: "Általános1" }
    { group:201, id:1, text: "Általános2" }
    { group:201, id:2, text: "Általános3" }
    { group:201, id:3, text: "Általános4" }
    { group:201, id:4, text: "Általános5" }
    { group:201, id:5, text: "Általános6" }
    { group:201, id:6, text: "Általános7" }
    { group:201, id:7, text: "Általános8" }
    { group:201, id:8, text: "Általános9" }
    { group:201, id:9, text: "Általános10" }
    { group:205, id:0, text: "Talán ha meglopnám a kincstárát, az felkeltené annak a hamis szakállasnak a figyelmét! // kocsitoló" }
    { group:205, id:1, text: "Elveszem, amit akarok! Ne próbálj megállítani!" }
    { group:205, id:2, text: "A tolvajlás sokkal jövedelmezőbb, mint a többi munka ebben a városban!" }
    { group:205, id:3, text: "Elvenni, elvenni, elvenni. Egész életemben csak ezt csinálom." }
    { group:206, id:0, text: "Óóó, a gyomrom! Ó, a fejem! // munkakereső" }
    { group:207, id:0, text: "Bármikor kitörhet a pestis! Remélem, a város szegényebb részein marad!" }
    { group:207, id:1, text: "Botrányos, hogy egy hozzám hasonló ember éhezhet!" }
    { group:207, id:2, text: "Nem hiszem, hogy ez a város elbírna egy támadást, és nekem olyan sok vesztenivalóm van." }
    { group:207, id:3, text: "Hogyan tud ilyen kevés munkás megfelelően gondoskodni az igényeimről?" }
    { group:207, id:4, text: "Sokkal jobban bánnak velem, mint az istenekkel! Remélem, nem sújtanak le ránk." }
    { group:207, id:5, text: "Szégyellem, hogy itt élek. Remélem, ellenségeink nem használják ki a hírnevünket!" }
    { group:207, id:6, text: "Nézzétek ezeket a semmittevőket! Miért nem keresnek munkát?" }
    { group:207, id:7, text: "Hogyan élhetnék fényűző életet, ha nem szórakoztatnak megfelelően?" }
    { group:207, id:8, text: "Ez a város, azt hiszem, megfelel az elvárásoknak." }
    { group:207, id:9, text: "Ez a város nem is lehetne jobb!" }
    { group:207, id:10, text: "Ezek a fesztiválok sokkal jobbak lennének, ha csak meghívottak vehetnének részt rajtuk." }
    { group:210, id:0, text: "A madarak ravaszak. Elrepülnek, ha nem közelíted meg őket megfelelően." }
    { group:210, id:1, text: "Nézd azokat a gyönyörű madarakat, készen állnak a megsütésre!" }
    { group:211, id:0, text: "Újabb tökéletes nap a halászathoz. Remélem, a fogás ugyanolyan bőséges lesz, mint mindig." }
    { group:211, id:1, text: "Tele van a rakterünk, de látnod kellett volna azt, amelyik elúszott!" }
    { group:211, id:2, text: "Gyorsabban! Nem térhetünk vissza dolgozni, amíg ki nem rakod a rakományunkat." }
    { group:215, id:0, text: "A mocsárba megyek a szükséges nádakért." }
    { group:215, id:1, text: "Ezekből a nádakból kiváló papirusz készül majd." }
    { group:216, id:0, text: "Szükség van a szolgálataimra az emlékműnél!" }
    { group:216, id:1, text: "Ez az emlékmű nagyon alacsony lenne a rámpáim és állványaim nélkül." }
    { group:217, id:0, text: "Eljött a téglarakás ideje az emlékműnél!" }
    { group:217, id:1, text: "A tégláimmal ez az emlékmű erős lesz." }
    { group:218, id:0, text: "Az emlékműhöz megyek, hogy megformáljam a köveket." }
    { group:218, id:1, text: "Kőmunkám kiállja majd az idők próbáját." }
    { group:219, id:0, text: "Olyan sokan megbetegedtek. Remélem, hamar felépülnek, különben kitörhet a pestis." }
    { group:219, id:1, text: "Éhezem. A legtöbb vásárlóm ételt követel, én pedig alig tudom magamat ellátni." }
    { group:219, id:2, text: "A védelmünk gyenge. Könnyen megszállhatnának minket." }
    { group:219, id:3, text: "Jobb, ha különösen kedves vagyok a segítőimmel. Ennyi szabad munkahely mellett a városban könnyen elveszíthetem őket." }
    { group:219, id:4, text: "Ha hamarosan nem mutatunk nagyobb tiszteletet az isteneknek, nyomorúságos büntetést fognak kiszabni ránk." }
    { group:219, id:5, text: "Eszembe sem jutna hagyni, hogy a hírnevem olyan mélyre süllyedjen, mint ennek a városnak. Hamarosan megfizethetünk érte." }
    { group:219, id:6, text: "Szerencsés vagyok, hogy van munkám. Sok embert ismerek, aki munka nélkül van." }
    { group:219, id:7, text: "Itt egyáltalán nem történik semmi. Bárcsak több előadást lehetne látni." }
    { group:219, id:8, text: "Nem fogok panaszkodni erre a városra... de megtehetném." }
    { group:219, id:9, text: "Ez a város nagyszerű!" }
    { group:219, id:10, text: "A bazárnak szüksége van néhány árucikkre, és én be fogom szerezni őket." }
    { group:219, id:11, text: "Ezek az áruk remek kiegészítői lesznek a bazárnak." }
    { group:222, id:0, text: "Nem viszem tovább ezeket a készleteket, amíg nincs valaki, aki lerakodja őket." }
    { group:222, id:1, text: "Senki sem tudja átvenni ezeket az árukat! Semmi baj, a maradékot felhasználhatom." }
    { group:222, id:2, text: "Ezekkel az árukkal át kell kelnem az egész városon. Egész nap eltart majd!" }
    { group:223, id:0, text: "Többet dolgozunk a ránk eső résznél. Több segítségre van szükségünk." }
    { group:223, id:1, text: "Itt várok, amíg lesz hely ezeknek a holmiknak." }
    { group:223, id:2, text: "Már ott vagyok? Nem tudom sokkal tovább cipelni ezeket az árukat." }
    { group:226, id:0, text: "Még soha nem láttam ennyi beteget. Remélem, nem tör ki a pestis." }
    { group:226, id:1, text: "Nehéz elkapni ezeket a bunkókat, amikor az éhségtől a hasadat fogod." }
    { group:226, id:2, text: "Talán ezekkel a bunkókkal megdobálhatom az ellenséget, ha támadnak. Alig védi valami ezt a várost." }
    { group:226, id:3, text: "Mindenütt üres állásokat látok! Vajon el tudnék vállalni egyszerre több munkát is?" }
    { group:226, id:4, text: "A legrosszabbra számítok. Az istenek bizonyára azt gondolják, hogy megfeledkeztünk róluk." }
    { group:226, id:5, text: "Ennek a városnak rosszabb a híre, mint nekem. Remélem, senki sem támad meg minket." }
    { group:226, id:6, text: "Bárcsak több munka lenne ebben a városban. Senki azok közül, akiket szórakoztatok, nem tud megfizetni." }
    { group:226, id:7, text: "Csak ennyi mindent tudok egyszerre kézben tartani. Bárcsak lennének más szórakoztatók is a városban." }
    { group:226, id:8, text: "Ez a város nem is olyan rossz." }
    { group:226, id:9, text: "Nincs hely, ahol szívesebben zsonglőrködnék." }
    { group:226, id:10, text: "Imádom ezeket a fesztiváli tömegeket szórakoztatni. Mindenki olyan boldog!" }
    { group:227, id:10, text: "Ezek a fesztiválok nagyszerűek! Mindenki együtt énekel." }
    { group:229, id:0, text: "Az emberek egészsége veszélyben van. Nagy a pestis kockázata." }
    { group:229, id:1, text: "Olyan éhes vagyok, mint egy víziló, de alig találni élelmet." }
    { group:229, id:2, text: "Meg kellene tanulnom a hadviselés művészetét. Ilyen gyenge védelem mellett veszélyben vagyunk." }
    { group:229, id:3, text: "A munkáshiány komoly problémákat okozhat a városban." }
    { group:229, id:4, text: "Az igazat megvallva, én nem merném ilyen rosszul kezelni az isteneket." }
    { group:229, id:5, text: "Ennek a városnak legfeljebb foltos a hírneve. Megtámadhatnak minket." }
    { group:229, id:6, text: "A legtöbb ember számára a munkakeresés ebben a városban hiábavaló próbálkozás, amely kudarccal végződik." }
    { group:229, id:7, text: "Ennek a városnak fel kellene ismernie, hogy milyen kevés a szórakozási lehetőség!" }
    { group:229, id:8, text: "Nem bánom, hogy itt élek." }
    { group:229, id:9, text: "Ez a város teljesen rabul ejtette a szívemet. Imádok itt élni!" }
    { group:229, id:10, text: "Itt a sör! Meleg, állott, frissítő sör! Kevés üledékkel!" }
    { group:235, id:0, text: "A város hamarosan megtanulhatja, hogy a rossz egészség borzalmas pestishez vezethet." }
    { group:235, id:1, text: "Az elmém tanulással táplálkozik, de a testem élelem után éhezik." }
    { group:235, id:2, text: "A betolakodóknak nem okozna gondot áttörni gyenge védelmünkön!" }
    { group:235, id:3, text: "A munkások hiánya az egész városban érezteti hatását, korlátozva a szolgáltatásokat." }
    { group:235, id:4, text: "A város istenkáromló viselkedése miatt az istenek lesújthatnak ránk!" }
    { group:235, id:5, text: "Ó, hírnév, hírnév. Botrányos hírnevünk támadásra csábít." }
    { group:235, id:6, text: "Még az oktatás sem oldja meg ennek a városnak a munkanélküliségi problémáját." }
    { group:235, id:7, text: "Unalmas, érdektelen, vontatott, egyhangú, semmitmondó. Ez a város mind az öt." }
    { group:235, id:8, text: "Ez a város teljesen átlagos." }
    { group:235, id:9, text: "Ez a város kitűnő értékelést érdemel!" }
    { group:235, id:10, text: "Egy fesztiválon sokat lehet tanulni az emberi természetről." }


    { group:240, id:0, text: "A városban lévő betegek száma alapján hamarosan rengeteg dolgom akadhat!" }
    { group:240, id:1, text: "Éhezem. Hamarosan soványabb leszek, mint egy múmia!" }
    { group:240, id:2, text: "A várost nem védi megfelelően erős védelem. Egy ellenség könnyen legyőzhetne minket." }
    { group:240, id:3, text: "Ha valaha is abba akarnám hagyni a balzsamozást, most itt a lehetőségem. Rengeteg az üres állás!" }
    { group:240, id:4, text: "Az istenek hamarosan szétszakíthatják városunkat, ha nem mutatunk nekik nagyobb tiszteletet." }
    { group:240, id:5, text: "A város rossz hírneve mindannyiunk vesztét okozhatja. Bármelyik pillanatban megtámadhatnak minket." }
    { group:240, id:6, text: "Amikor ennyi munkanélküli embert látok, örülök, hogy nekem van munkám." }
    { group:240, id:7, text: "Ez a város olyan halott, mint azok a testek, amelyekkel egész nap dolgozom. Bárcsak élettel telne meg a város szórakozással." }
    { group:240, id:8, text: "Akár itt is élhetek. Körülbelül olyan jó, mint bárhol máshol." }
    { group:240, id:9, text: "Őszintén sajnálom az ügyfeleimet. Nincsenek itt, hogy élvezzék ezt a hihetetlen várost!" }
    { group:240, id:10, text: "Úgy tűnik, a város egészségi állapota folyamatosan romlik." }

    { group:247, id:0, text: "Festési és vakolási tudásomra szükség van az emlékműnél!" }
    { group:247, id:1, text: "Egyiptom történeteit örökítem meg a királyi sírok falain." }
    { group:248, id:0, text: "Az arany az élőké, nem a holtaké!" }
    { group:248, id:1, text: "Csak gondolj bele, mekkora vagyonra teszek majd szert, ha eladom azokat a kincseket!" }
    { group:249, id:0, text: "Halálig harcolunk, hogy megvédjük gyönyörű városunkat!" }
    { group:249, id:1, text: "Az ellenség túl erős nekünk! Ha elmenekülünk előlük, készen állunk majd arra, hogy egy másik napon harcoljunk." }
    { group:249, id:2, text: "Ellenségek közelednek erre!" }
    { group:249, id:3, text: "Olyan veszélyesek vagyunk, mint egy krokodil, készen állunk rá, hogy megtámadjuk a betolakodókat, amikor megérkeznek." }
    { group:249, id:4, text: "Ha ellenségeink eljönnek, készen állunk majd rájuk." }
    { group:250, id:0, text: "Evezzetek erősebben! Mindenáron meg kell védenünk a hajónkat!" }
    { group:250, id:1, text: "Az ellenség itt van! Mindenki készüljön a manőverekre." }
    { group:250, id:2, text: "Jöhet a támadás! Felkészültünk." }
    { group:250, id:3, text: "Készen állunk szolgálni, ha szükség lesz ránk." }
    { group:251, id:0, text: "Pontos szekér 1" }
    { group:252, id:0, text: "Nem észleltünk ellenséget, de ennek ellenére készen állunk." }
    { group:252, id:1, text: "Olyan feltekeredve várunk, mint egy áspiskígyó, készen arra, hogy lecsapjunk a közeledő ellenségre." }
    { group:252, id:2, text: "Ezt nevezitek hadseregnek?! Nem lesz gondunk ezzel a tarka csapattal." }
    { group:252, id:3, text: "Ez az ellenség kemény ellenfél! Mindent megteszek, hogy legyőzzük őket." }
    { group:253, id:0, text: "Naptemplom" }
    { group:253, id:1, text: "1. fázis" }
    { group:253, id:2, text: "A nyers obeliszket elhelyezték " }
    { group:253, id:3, text: "és a munkások megtisztítják a területet" }
    { group:253, id:4, text: "2. fázis" }
    { group:253, id:5, text: "Az ácsok állványokat helyeznek el az " }
    { group:253, id:6, text: "obeliszket körül" }
    { group:253, id:7, text: "3. fázis" }
    { group:253, id:8, text: "A kőfaragók kialakítják az obeliszk " }
    { group:253, id:9, text: "végső formáját" }
    { group:253, id:10, text: "4. fázis" }
    { group:253, id:11, text: "Az előcsarnok, a fal, a tér és " }
    { group:253, id:12, text: "a templom előtti rész építése folyamatban van" }
    { group:253, id:13, text: "Egyetlen kőfaragó vár kőre." }
    { group:253, id:14, text: "A kőfaragók kőre várnak." }
    { group:253, id:15, text: "A Naptemplom " }
    { group:253, id:16, text: "százalékban kész" }
    { group:253, id:17, text: "kőtömbökre van szükség a " }
    { group:253, id:18, text: "Naptemplom építésének befejezéséhez." }

    { group:291, id:0, text: "Mauzóleum" }
    { group:291, id:1, text: "1. fázis" }
    { group:291, id:2, text: "Az alapzatot elhelyezték" }
    { group:291, id:3, text: "és a munkások megtisztítják a területet" }
    { group:291, id:4, text: "2. fázis" }
    { group:291, id:5, text: "A kőművesek építik a mauzóleum alsó " }
    { group:291, id:6, text: "részét" }
    { group:291, id:7, text: "3. fázis" }
    { group:291, id:8, text: "A kőfaragók építik a mauzóleum felső " }
    { group:291, id:9, text: "részét" }
    { group:291, id:10, text: "Egyetlen kőfaragó vár kőre" }
    { group:291, id:11, text: "A kőfaragók kőre várnak" }
    { group:291, id:12, text: "A mauzóleum " }
    { group:291, id:13, text: "százalékban kész" }
    { group:291, id:14, text: "kőtömbökre van szükség a" }
    { group:291, id:15, text: "mauzóleum építésének befejezéséhez" }
    { group:292, id:0, text: "Család létrehozása" }
    { group:292, id:1, text: "Család törlése" }
    { group:292, id:2, text: "Folytatás" }
    { group:292, id:3, text: "Családi nyilvántartás" }
    { group:292, id:4, text: "Vissza a főmenübe" }
    { group:293, id:0, text: "Családtörténet folytatása" }
    { group:293, id:1, text: "Küldetés kiválasztása" }
    { group:293, id:2, text: "Mentett játék betöltése" }
    { group:293, id:3, text: "Egyéni küldetések" }
    { group:293, id:4, text: "Vissza a családi nyilvántartáshoz" }
    { group:293, id:5, text: "[player_name] családja" }
    { group:293, id:6, text: "Történelem felfedezése" }
    { group:293, id:7, text: "Családtörténet kezdése" }
    { group:294, id:0, text: "Predinasztikus kor" }
    { group:294, id:1, text: "A predinasztikus korban azok a törzsek, amelyek végül Egyiptomot fogják uralni, megteszik első bizonytalan lépéseiket a civilizáció felé vezető úton." }
    { group:294, id:2, text: "Családod a predinasztikus kor kezdetén egy kis nomádcsoport vezetésével indul útnak, és felfedezi a civilizáció művészetét. Vezetésed segít Egyiptomot a későbbi nagyság felé vezető útra állítani, bár ez a nagyság ekkor még csak halványan sejlik fel." }
    { group:294, id:3, text: "A predinasztikus kor az egyiptomi történelem, valamint családod történetének hajnala." }
    { group:294, id:4, text: "Óbirodalom előtti kor" }
    { group:294, id:5, text: "Fokozatosan a predinasztikus korban létrejött falvak egyesült királysággá olvadnak össze, amely lenyűgöző fővárossal és első monumentális síremlékeivel rendelkezik." }
    { group:294, id:6, text: "Az óbirodalom előtti korban a predinasztikus időszakban kialakult falvak fokozatosan egyesülnek, és létrehozzák Egyiptom nagy királyságát. A fiatal civilizáció megalapítja fővárosát, biztosítja határait, uralma alá hajtja a vizeket, és megépíti első monumentális síremlékeit." }
    { group:294, id:7, text: "Családtörténetedet sorrendben kell végigélned! Sajnos nem uralkodhatsz az óbirodalom előtti korban, amíg előbb meg nem tanulod a predinasztikus korban felfedezett művészeteket." }
    { group:294, id:8, text: "Óbirodalom" }
    { group:294, id:9, text: "Egyiptom a gazdagság, hatalom és dicsőség aranykorába lép, és lenyűgöző új emlékműveket emel szerte a világon. Ám e szédítő magasságok elérése után Egyiptom háborúba süllyedt." }
    { group:294, id:10, text: "Egyiptom az Óbirodalom idején példátlan hatalomra, gazdagságra és dicsőségre emelkedik. Ám miközben hihetetlen új emlékművek emelkednek a Nílus völgyében, a jósok nyugtalanító jóslatokat tesznek a Két Ország sorsáról." }
    { group:294, id:11, text: "Családtörténeted alakítása közben nem ugorhatsz előre. Mielőtt beléphetnél az Óbirodalomba, előbb be kell fejezned az óbirodalom előtti kort." }
    { group:294, id:12, text: "Középbirodalom" }
    { group:294, id:13, text: "Fájdalmas megszületését követően a Középbirodalom nagy lehetőségek korszakának bizonyul családod felemelkedése számára a világban." }
    { group:294, id:14, text: "A viszályból született Középbirodalom családod számára a nagy lehetőségek korszakának bizonyul. Vezetéseddel Egyiptom visszanyeri egykori ragyogását... és még többet is." }
    { group:294, id:15, text: "A családtörténetnek sorrendben kell kibontakoznia. A Középbirodalom nem kezdődhet el, amíg az Óbirodalom véget nem ér!" }
    { group:294, id:16, text: "Újbirodalom" }
    { group:294, id:17, text: "Egy ádáz új ellenség egy leleményes és megállíthatatlan új fegyver segítségével elsöpri a Középbirodalmat. E pusztításból Egyiptom ismét újjászületik." }
    { group:294, id:18, text: "Különös új ellenségek egy félelmetes szuperfegyverrel véget vetnek a Középbirodalomnak, és előkészítik az utat az ezt követő dicsőséges Újbirodalom számára." }
    { group:294, id:19, text: "Nem térhetsz le családtörténeted útjáról! Családod nem élheti át az Újbirodalom korát, amíg be nem fejezed az előző korszakokat." }
    { group:294, id:20, text: "Királyok Völgye" }
    { group:294, id:21, text: "A Királyok Völgyében létrehozott új nekropolisz kialakítása új lehetőséget biztosított a fáraók felkészítésére a túlvilági utazásukhoz." }
    { group:294, id:22, text: "Bármilyen nagyszerűek is, őseid piramisai az évszázadok során leromlottak, a bennük lévő sírokat megszentségtelenítették, és a rejtett kincseket tolvajok fosztották ki, akiket az istenek bizonyára az örökkévalóságon át büntetni fognak! Lemondasz a piramisokról, és új nekropoliszt hozol létre egy nehezen megközelíthető vádiban, Théba túloldalán, ahol a sziklafalakba vájt sírokkal létrehozod a Királyok Völgyét, biztonságban a sírrablóktól. Vagy mégsem?" }
    { group:294, id:23, text: "Családtörténetedben mindennek megvan a maga ideje. Nem építheted meg a Királyok Völgyének fenséges sírjait, amíg be nem fejezed az Újbirodalom dicsőségét." }
    { group:294, id:24, text: "II. Ramszesz" }
    { group:294, id:25, text: "II. Ramszesz kivívja Egyiptom legnagyobb győzelmét, és lenyűgöző emlékművekkel állít emléket nagyságának." }
    { group:294, id:26, text: "II. Ramszesz egy dinasztiai sorozat harmadik uralkodója, amelyet nagyapja, I. Ramszesz indított el. Ő nem királyi származású vezír volt, aki akkor ragadta magához a trónt, amikor Horemheb utód nélkül halt meg. Katonai győzelmeket kell aratnod, és hatalmas emlékműveket kell építened, amelyek alattvalóidat istenhez hasonló rangodról győzik meg, ellenségeidet kétségbe ejtik, és az eljövendő nemzedékek számára hirdetik II. Ramszesz, a Nagy nevét és Egyiptom dicsőségét." }
    { group:294, id:27, text: "A családtörténetet sorrendben kell befejezni. Nem uralkodhatsz II. Ramszeszként, amíg meg nem építetted a Királyok Völgyének dicsőséges sírjait." }
    { group:294, id:28, text: "Ősi hódítók" }
    { group:294, id:29, text: "Távoli földek hatalmas harcosai özönlenek be, hogy megpróbálják megszerezni Egyiptom gazdagsága feletti uralmat. Miután elhárítod ezeket a fenyegetéseket, és üdvözlöd Alexandrosz dicsőségét, a „Küldetés kiválasztása” részben újrajátszhatod a teljes hadjáratot vagy annak bármely egyes küldetését." }
    { group:294, id:30, text: "Egyiptomnak sok irigy szomszédja van, akik gazdag birodalmunkra úgy tekintenek, ahogy egy hiénacsapat veszi körül az oroszlán zsákmányát. Képes vagy felépíteni és irányítani azokat a hadseregeket és flottákat, amelyek szükségesek e komoly fenyegetések legyőzéséhez, valamint a Nílus-delta megvédéséhez a tengeri népek, az asszírok és a perzsák egymást követő invázióival szemben? Egyiptom a védelmedre számít!" }
    { group:294, id:31, text: "Ha ezt most játszanád, megszakadna családtörténeted folytonossága. Nem győzheted le az Ősi hódítókat, amíg nem éltél II. Ramszesz korában." }
    { group:294, id:32, text: "Kleopátra fővárosa" }
    { group:294, id:33, text: "A görög származású Ptolemaioszok visszaállítják a fáraók földjének dicsőségét, és elhárítják a Róma felől érkező fenyegetést." }
    { group:294, id:34, text: "Nagy Sándor maga jelölte ki Alexandria jövőbeli helyét – azt a Földközi-tenger partján fekvő kikötővárost, amelyet most neked kell felépítened. A Ptolemaioszok 300 éves uralma alatt, amely VII. Kleopátrával ér véget, Alexandria a világ legnagyobb városává válik, lakosságban és gazdagságban is felülmúlva Rómát. Nagy Sándor mauzóleuma, a Nagy Könyvtár, a Pharosz világítótorony és a Caesareum a városod építési projektjei. De mi lesz Róma hatalmas légióival? Kleopátra Egyiptoma mellett vagy ellene fognak harcolni?" }
    { group:294, id:35, text: "Családtörténeted nem veheti fel Kleopátra életét a krónikáiba, amíg le nem győzted az Ősi hódítókat." }
    { group:294, id:36, text: "Kezdés" }
    { group:294, id:37, text: "Játék" }
    { group:294, id:38, text: "Egyéni küldetések" }
    { group:294, id:39, text: "Hadjáratok" }
    { group:294, id:40, text: "Csak a sikeresen teljesített küldetéseket játszhatod újra." }
    { group:294, id:41, text: "Fáraó" }
    { group:294, id:42, text: "Kleopátra" }
    { group:295, id:0, text: "Ez a fesztivál olyan jó hangulatba hozott mindenkit, hogy a városnak hamarosan újabbat kellene rendeznie." }
    { group:295, id:1, text: "Már néhány hónap eltelt az utolsó fesztivál óta. Jó alkalom lenne egy újabb megrendezésére." }
    { group:295, id:2, text: "Már jó ideje nem volt fesztivál, és az emberek kezdenek panaszkodni." }
    { group:295, id:3, text: "Több mint egy éve volt az utolsó fesztivál. Az emberek unatkoznak és túlterheltnek érzik magukat." }
    { group:295, id:4, text: "Már majdnem két éve volt az utolsó fesztivál. Az embereknek kétségbeesetten szükségük van egy kis pihenésre." }
    { group:295, id:5, text: "Több mint két év telt el fesztivál nélkül! Az emberek kezdenek reménytelenné válni." }
    { group:295, id:6, text: "Az emberek nosztalgiával beszélnek a „régi szép időkről”, amikor a fesztiválok megtörték az egyhangúságot." }
    { group:295, id:7, text: "Ez egy olyan csodálatos fesztivál volt! Egy ilyen ünnepség előkészítése sok időt vesz igénybe." }
    { group:295, id:8, text: "A fesztiválok előkészítése olyan sok időt és erőfeszítést igényel, hogy bölcs döntés lehet, ha most rendelünk egyet." }
    { group:295, id:9, text: "Az utolsó fesztivál már elég régen volt ahhoz, hogy ideje legyen újat rendelni." }
    { group:295, id:10, text: "A közönséges fesztivál hamarosan elkészül. Mindenki a jövő havi ünnepről beszél." }
    { group:295, id:11, text: "A közönséges fesztivál előkészítése folyamatban van. Már csak két hónap, és mindenki ünnepelhet!" }
    { group:295, id:12, text: "A három hónap múlva megrendezésre kerülő közönséges fesztivál előkészületei jövő hónapban kezdődnek." }
    { group:295, id:13, text: "A fesztiválszervezők véglegesítik a négy hónap múlva esedékes közönséges fesztivál terveit." }
    { group:295, id:14, text: "A közönséges fesztivál öt hónap múlva kerül megrendezésre. A szervezők átnézik a javaslatokat." }
    { group:295, id:15, text: "A tervezők biztosak benne, hogy hat hónap múlva készen állnak majd a közönséges fesztiválra." }
    { group:295, id:16, text: "A megterhelt szervezők ígérik, hogy a közönséges fesztivált hét hónap múlva rendezik meg." }
    { group:295, id:17, text: "A közönséges fesztiválra még nyolc hónapig nem kerül sor. A tervezés alig kezdődött el." }
    { group:295, id:18, text: "A fesztiválszervezők annyira elfoglaltak, hogy az általad kért közönséges fesztivál csak kilenc hónap múlva lesz." }
    { group:295, id:19, text: "Máris egy újabb? Tíz hónapba telik, mire a szervezők megrendezhetnek egy közönséges fesztivált." }
    { group:295, id:20, text: "A fényűző fesztivál hamarosan elkészül. Az emberek izgatottan várják a jövő havi ünnepséget!" }
    { group:295, id:21, text: "A fényűző fesztivál előkészítése folyamatban van, és már csak két hónapunk van a felkészülésre." }
    { group:295, id:22, text: "A fényűző fesztivált előkészítik. Három hónap múlva emlékezetes ünnepséget rendezünk." }
    { group:295, id:23, text: "A tervezők lendületbe jöttek, és a fényűző fesztivált biztosan négy hónap múlva rendezik meg." }
    { group:295, id:24, text: "A szórakoztatók csiszolják műsoraikat az öt hónap múlva megrendezendő fényűző fesztiválra." }
    { group:295, id:25, text: "A tervezők megerősítik, hogy az új fényűző fesztivált az ígéret szerint hat hónap múlva rendezik meg." }
    { group:295, id:26, text: "A szervezők mérlegelik a lakosság javaslatait a hét hónap múlva esedékes fényűző fesztiválhoz." }
    { group:295, id:27, text: "Néhány szórakoztató új műsorszámokat gyakorol a nyolc hónap múlva megrendezendő fényűző fesztiválra." }
    { group:295, id:28, text: "Mivel még rengeteg a tennivaló az előkészületekben, a fényűző fesztiválra csak kilenc hónap múlva kerül sor." }
    { group:295, id:29, text: "Mivel jelenleg senkinek sincs ideje foglalkozni vele, a fényűző fesztivált tíz hónap múlva rendezik meg." }
    { group:295, id:30, text: "A tervezők annyira elfoglaltak, hogy az új fényűző fesztivált csak tizenegy hónap múlva tudják megrendezni." }
    { group:295, id:31, text: "A nagyszabású fesztivál hamarosan elkészül. Még egy hónap, és mindenki friss sört ihat." }
    { group:295, id:32, text: "A nagyszabású fesztivál előkészületeiből már csak két hónap van hátra. Az izgalom elviselhetetlen!" }
    { group:295, id:33, text: "A nagyszabású fesztivált előkészítik. Az embereknek már csak három hónapjuk van a tervezésre." }
    { group:295, id:34, text: "A nagyszabású fesztivál előkészítése folyamatban van. Senki sem akarja kivárni azt a négy hónapot, amire a tervezőknek szükségük van!" }
    { group:295, id:35, text: "A szervezők jövő hónapban kezdhetik meg az előkészületeket, így öt hónap múlva megrendezhető lesz a nagyszabású fesztivál." }
    { group:295, id:36, text: "A zsonglőrök valódi meglepetéseket mutatnak majd be a nagyszabású fesztiválon, amely már csak hat hónap múlva lesz." }
    { group:295, id:37, text: "A zenészek mind új dalokat írnak a nagyszabású fesztiválra, amely már csak hét hónap múlva lesz." }
    { group:295, id:38, text: "A táncosokat merész új mozdulatokat gyakorolva lehet látni a nyolc hónap múlva esedékes nagyszabású fesztiválra." }
    { group:295, id:39, text: "A tervezők elegendő ötletet és energiát gyűjtöttek össze ahhoz, hogy kilenc hónap múlva nagyszabású fesztivált rendezzenek." }
    { group:295, id:40, text: "A fesztiválszervezők túlórában dolgoznak, hogy tíz hónap múlva készen álljanak az új nagyszabású fesztivállal." }
    { group:295, id:41, text: "A tervezők biztosak benne, hogy tizenegy hónap múlva megfelelően meg tudnak rendezni egy nagyszabású fesztivált." }
    { group:295, id:42, text: "A szervezők annyira túlterheltek, hogy az általad rendelt nagyszabású fesztiválra csak egy év múlva kerül sor." }
    { group:296, id:0, text: "Egyiptom örök házai" }
    { group:296, id:1, text: "Küldetés" }
    { group:296, id:2, text: "Legjobb család" }
    { group:296, id:3, text: "Nehézségi szint" }
    { group:296, id:4, text: "Pontszám" }
    { group:296, id:5, text: "A(z) háza" }
    { group:296, id:6, text: "Nincsenek rekordpontszámok." }
    { group:297, id:0, text: "Családod legkorábbi feljegyzett őse felemelkedett, és megtanulta a vezetés alapjait." }
    { group:297, id:1, text: "Miután a család Thiniszbe költözött, ősöd segített a thiniszi szövetségnek Felső- és Alsó-Egyiptom egyesítésében." }
    { group:297, id:2, text: "A családi legendák szerint klánod fontos új technológiákat fedezett fel, és megtanulta kihasználni az áradást." }
    { group:297, id:3, text: "Családod akkor került először a hivatalos egyiptomi történetírásba, amikor Narmer egyik ősödet a királyi építész tisztségére nevezte ki." }
    { group:297, id:4, text: "Családod jelentős szerepet játszott Egyiptom első fővárosának megalapításában és az ottani masztaba felépítésében." }
    { group:297, id:5, text: "A legenda szerint családod nyitotta meg a timnai rézbányákat, amelyek kulcsfontosságúak voltak Den fáraó sikerében a beduinok távoltartásában." }
    { group:297, id:6, text: "Először fordult elő, hogy egyik ősöd a szárazföld helyett a vizet választotta, és elsajátította a hajózás minden tudományát – beleértve a hadviselést is." }
    { group:297, id:7, text: "Először fordult elő, hogy egyik ősöd a szárazföld helyett a vizet választotta, és elsajátította a békés hajózás tudományát." }
    { group:297, id:8, text: "Néped egy fontos katonai őrhelyet hozott létre a civilizációtól távol, megnyitva az Afrikába vezető kereskedelmi útvonalakat, amelyek mind a mai napig fennmaradtak." }
    { group:297, id:9, text: "Nebka fáraó jóvoltából családod megszerezte az Első-katarakta ásványkincseit, amelyek nélkül számos sír nem épülhetett volna meg, és sok nemes számára elérhetetlenné vált volna a Nádasmező." }
    { group:297, id:10, text: "Ősöd büszkén valósította meg Imhotep vezír elképzelését, és megépítette Egyiptom első kőpiramisát Dzsószer múmiájának elhelyezésére." }
    { group:297, id:11, text: "Hősies elődöd értékes drágaköveket és rezet szerzett a barátságtalan Sínai-félszigetről és annak vad lakóitól, akik minden erejükkel próbálták megakadályozni a vállalkozást." }
    { group:297, id:12, text: "Klánod javuló sorsáról tanúskodik a meidumi családi sír, amely mind a mai napig bizonyítéka a vérvonal Egyiptomban betöltött fontosságának." }
    { group:297, id:13, text: "A Buhenben emelt erőd, valamint az ellenség ottani teljes megsemmisítése rokonaid által Egyiptom hatalmát egészen a Második-kataraktáig kiterjesztette, az ellenséges Núbia által igényelt területekre." }
    { group:297, id:14, text: "Miközben mások a Királyság határainak kiterjesztésével foglalkoztak, ősöd megépítette az addig elképzelt legnagyszerűbb síremléket – Sznofru tört piramisát." }
    { group:297, id:15, text: "Miközben Sznofru olyan örököst üdvözölt, akit a királyi jósok zsarnoknak bélyegeztek, saját elődeid befejezték a világ első tökéletes piramisát a fáraó maradványainak elhelyezésére." }
    { group:297, id:16, text: "Hufu kibontakozó zsarnoksága ellenére ősöd hűségesen szolgált királyi helytartójaként, és megvédte Egyiptom határait a kusita betolakodóktól." }
    { group:297, id:17, text: "A kusita fenyegetéstől védve ősöd jövedelmező kőfejtőket nyitott Turában, hogy kielégítse Hufu megmagyarázhatatlan igényét a látszólag végtelen mennyiségű mészkő iránt." }
    { group:297, id:18, text: "Ősöd Hufu és Hafré nomarkhoszává emelkedett, és a fáraóéval vetekedő akaraterővel felépítette az örökkévaló Nagy Piramist és annak őrzőjét, a Szfinxet." }
    { group:297, id:19, text: "A fáraó Rét nyilvánította az istenek között a legfőbbnek, és megbízta elődödet, hogy terjessze ki a Napkultusz uralmát a Királyság legszélén fekvő, ellenséges nyugati sivatag pusztaságaira." }
    { group:297, id:20, text: "Uszerkaf fáraó Rét az istenek legfőbb urává nyilvánította, és megbízta ősödet, hogy építse fel a legnagyszerűbb Naptemplomot a buja deltavidéken, ahol nem állt rendelkezésre építőkő." }
    { group:297, id:21, text: "Miközben Egyiptom ellenségei úgy özönlöttek, mint bogarak egy rothadó testre, családod elérte a kancellári rangot, és megakadályozta, hogy a Királyság ellenségei elvágják éltető útvonalait." }
    { group:297, id:22, text: "Miközben Egyiptom ellenségei úgy özönlöttek, mint bogarak egy rothadó testre, családod elérte a kancellári rangot, és bebizonyította, hogy képes hozzáértően kormányozni akkor is, amikor minden más összeomlott." }
    { group:297, id:23, text: "Őseid hűséget fogadtak a törvényes Inyotefeknek, és visszaállították Thinisz dicsőségét, a lázadó seregek összehangolt erőfeszítései ellenére is." }
    { group:297, id:24, text: "Két frakció harcolt Egyiptom szívéért, miközben annak népe éhezett. Ősöd sokakat megmentett az éhhaláltól, miközben döntő támogatást nyújtott a törvényes dinasztiának." }
    { group:297, id:25, text: "Mentuhotep a vezíri rangot adományozta családodnak, és nagyban támaszkodott támogatásukra a megmaradt lázadók és trónbitorlók leverésében, akik az újraegyesítés megakadályozására törekedtek." }
    { group:297, id:26, text: "Mentuhotep a vezíri rangot adományozta családodnak, és újraegyesítési törekvései nagy hasznát látták annak a tekintélynek és dicsőségnek, amelyet a porból felemelt fenséges városod sugárzott." }
    { group:297, id:27, text: "Végre családod egyik tagja beteljesítette sorsát, és fáraóvá vált. Klánod királyi dinasztiává lett, új fővárost épített, és együttérzéssel, valamint jó cselekedetekkel elhallgattatta az ellenállást." }
    { group:297, id:28, text: "Isteni származású ősöd meghódította északi Núbia ősi ellenségeink földjeit, tiszteletet ébresztett a kusitákban dinasztiád iránt, és fontos vörös-tengeri kikötőt alapított." }
    { group:297, id:29, text: "Isteni elődöd vörös-tengeri kereskedelmi kikötője felmérhetetlen új gazdagságot és fényűző javakat hozott népednek, családod sírja pedig az idők végezetéig fennmarad." }
    { group:297, id:30, text: "Nagy hírű ősöd, aki ma egy pompás mauzóleumban nyugszik, szétzúzta a núbiai flottát, és meghódította egyik legszebb városukat." }
    { group:297, id:31, text: "Bubasztisz városa mind a mai napig a Kettős Korona ékköve maradt. Elődöd olyan várost épített, amelyre egész Egyiptom büszkén tekint." }
    { group:297, id:32, text: "A hikszoszok félelmetes harci szekereit egyiptomi fegyverré változtatni, majd azokat a háború sújtotta Királyságunk ellenségei ellen használni ragyogó teljesítmény volt, amelyet a történelem soha nem felejt el." }
    { group:297, id:33, text: "Valóban, családodat régóta bölcsesség áldása kíséri. Ősöd stratégiája, amellyel Egyiptom legnagyobb hadvezéreit emberfeletti erőfeszítésekre ösztönözte, bőségesen meghozta gyümölcsét." }
    { group:297, id:34, text: "Új Királyságot alapítottál, örökre biztosítottad Büblosz erdőinek használatát, és megtanítottad a félelmetes hettitákat és a rejtélyes tengeri népeket egyaránt Egyiptom határainak tiszteletére." }
    { group:297, id:35, text: "Elképzelhetetlen gazdagságot teremtettél új Királyságod számára, miközben megvédted az egyiptomi városokat régi és új ellenségeiktől." }
    { group:297, id:36, text: "Uralkodásod volt Egyiptom valaha ismert legnagyobb korszaka. Határaink az ismert világig terjedtek, népünk pedig elképzelhetetlen fényűzésben részesült." }
    { group:297, id:37, text: "Miután minden ellenségedet legyőzted, és felbecsülhetetlen jólétet hoztál a Királyságba, végül olyan piramist építettél, amely még a legendás Hufu piramisát is felülmúlta." }
    { group:297, id:38, text: "Deir el-Medina megalapításával a fáraók örök nyugalomra lelhetnek, és alig kell tartaniuk attól, hogy rettegett sírrablók megzavarják őket." }
    { group:297, id:39, text: "Alig maradt idő, de Tutanhamon sírja mégis elkészült, és gazdag temetési felszereléssel látták el." }
    { group:297, id:40, text: "I. Széthi sírja valóságos csoda, amelyet még különlegesebbé tesznek azok a sírrablók elleni harcok, amelyeket az építése érdekében kellett megvívni. Szégyen, hogy a világ szemei nem gyönyörködhetnek majd örök szépségében." }
    { group:297, id:41, text: "Sumur kikötője ma virágzó kereskedelmi központként pezseg, miközben azon dolgozik, hogy kielégítse hazánk fa és más értékes árucikkek iránti igényét." }
    { group:297, id:42, text: "Egyiptom kádesi csatában aratta legnagyobb győzelmét, és újra megszilárdította uralmát Amurru földje felett. A hettita fenyegetést egyszer s mindenkorra megsemmisítettük." }
    { group:297, id:43, text: "Az Abu Szimbel-i kolosszusok örökké Egyiptom hatalmáról és dicsőségéről fognak tanúskodni." }
    { group:297, id:44, text: "II. Ramszesz földi maradványai nyugodjanak békében pompás sírjában. Örök életében minden bizonnyal továbbra is segíteni fogja Egyiptom vezetését." }
    { group:297, id:45, text: "A tenger felől érkező veszélyes fosztogatók, akik ostobán Egyiptom földjein akartak letelepedni, erővel visszavonulásra kényszerültek. Egyiptom határai ismét biztonságban vannak." }
    { group:297, id:46, text: "Az Egyiptom távoli vidékein emelt megerősített őrhely hullámról hullámra állta ki az asszír támadásokat, biztosítva, hogy az aljas ellenség ne hatolhasson mélyebbre a Két Föld területére." }
    { group:297, id:47, text: "Akhórisz népe még hosszú ideig mesélni fog a perzsa flotta megsemmisítéséről és gyalogságuk elpusztításáról. Súlyos csapást mértünk a perzsák hódító álmaira." }
    { group:297, id:48, text: "Mindössze tizenkét év alatt Alexandria kiemelkedett a földből, és virágzó nagyvárossá fejlődött ott, ahol néhány évvel korábban még csak egy szegény halászfalu állt." }
    { group:297, id:49, text: "Alexandriát a Nagy Könyvtár és a Pharosz világítótorony ékesítette, és a város tekintélye az egész világon tovább növekedett." }
    { group:297, id:50, text: "Mithradatész római légiói nagy csatában, a Mariut-tó partján verték le Kleopátra lázadó testvérét, XIII. Ptolemaioszt." }
    { group:297, id:51, text: "Alexandria dicsőséges fejlődése tovább folytatódott, amikor a csodálatos építmények sorát a Caesareummal és egy újabb halotti templommal bővítették." }
    { group:297, id:52, text: "Egyiptom flottájának és Antonius erőinek egyesített hatalma megsemmisítő vereséget mért Octavianusra, és Egyiptom valamint Róma egyenrangú félként egyesült az ismert világ uralmára." }
    { group:298, id:0, text: "Végső kulturális érték:" }
    { group:298, id:1, text: "Végső jóléti érték:" }
    { group:298, id:2, text: "Végső műemlékérték:" }
    { group:298, id:3, text: "Végső királyságérték:" }
    { group:298, id:4, text: "A befejezéskori népesség:" }
    { group:298, id:5, text: "Végső városi pénzkészlet:" }
    { group:298, id:6, text: "A küldetés teljesítési ideje:" }
    { group:298, id:7, text: "Legalacsonyabb használt nehézségi szint:" }
    { group:298, id:8, text: "Végső pontszám:" }
    { group:298, id:9, text: "év" }
    { group:299, id:0, text: "Közvetlen eredmény" }
    { group:299, id:1, text: "Járulékos" }
    { group:299, id:2, text: "Ennek ellenére" }
    { group:299, id:3, text: "Nincs ok" }
    { group:299, id:4, text: "Folyamatos/Ciklikus" }
    { group:299, id:5, text: "Szükség szerint meghatározott" }
    { group:299, id:6, text: "Automatikus" }
    { group:299, id:7, text: "Közvetlen" }
    { group:299, id:8, text: "Egyébként" }
    { group:299, id:9, text: "Ennek ellenére" }
    { group:299, id:10, text: "Nincs" }
    { group:299, id:11, text: "Ciklus" }
    { group:299, id:12, text: "Speciális" }
    { group:299, id:13, text: "Automatikus" }

    { group:304, id:0, text: "Következő oldal" }
    { group:304, id:1, text: "Előző oldal" }

    { group:305, id:0, text: "Családod még soha nem nézett szembe ezzel a kihívással. A küldetés céljainak megtekintéséhez kattints az alábbi gombra." }

    { group:306, id:0, text: "Hennafarm" }
    { group:306, id:1, text: "Itt termesztik a legkiválóbb hennát, amelyet a festékkészítőhöz szállítanak, aki elkészíti belőle a sírok falait díszítő élénk festékeket." }
    { group:306, id:2, text: "A termelés" }
    { group:306, id:3, text: "befejeződött." }
    { group:306, id:4, text: "A kereskedelmi felügyelőd elrendelte a hennatermelés leállítását." }
    { group:306, id:5, text: "Munkások nélkül ez a farm képtelen bármilyen hennát termeszteni." }
    { group:306, id:6, text: "Ennek a farmnak minden szükséges munkása megvan. A földeken dolgoznak, és gondozzák a növényeket." }
    { group:306, id:7, text: "Ez a farm több hennát tudna betakarítani, ha több munkása lenne." }
    { group:306, id:8, text: "Ennek a farmnak nincs elég munkása ahhoz, hogy egy teljes hennamezőt gondozzon." }
    { group:306, id:9, text: "Nagyon kevesen dolgoznak itt. Emiatt a hennatermés csökkenni fog." }
    { group:306, id:10, text: "A farm nagy része terméketlen. Több munkásra van szüksége, mielőtt több hennát termeszthetne." }
    { group:306, id:11, text: "A sáskák mindent felfaltak, ami itt termett, és a földnek időre van szüksége a regenerálódáshoz." }
    { group:306, id:12, text: "A föld" }
    { group:306, id:13, text: "termékeny." }
    { group:306, id:14, text: "A következő hennaszüret időpontja:" }

    { group:307, id:0, text: "0,0,0,0   // 0. küldetés" }
    { group:307, id:1, text: "0,0,0,0" }
    { group:307, id:2, text: "0,0,0,0" }
    { group:307, id:3, text: "0,0,0,0   // Nekhen: első küldetés személyes fizetéssel" }
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
    { group:307, id:37, text: "1,0,0,0   // Az eredeti játék utolsó küldetése" }
    { group:307, id:38, text: "0,0,0,1   // Thutmose" }
    { group:307, id:39, text: "0,0,V,1   // Tutanhamon" }
    { group:307, id:40, text: "0,0,V,1   // Szeti" }
    { group:307, id:41, text: "0,0,0,0   // Szumúr" }
    { group:307, id:42, text: "1,1,0,0   // Qádés" }
    { group:307, id:43, text: "1,1,0,0   // Abu Szimbel" }
    { group:307, id:44, text: "1,1,V,0   // II. Ramszesz a Királyok Völgyében" }
    { group:307, id:45, text: "0,0,0,0   // Pi-Jer" }
    { group:307, id:46, text: "0,0,0,0   // Migdol" }
    { group:307, id:47, text: "0,0,0,0   // Tanisz" }
    { group:307, id:48, text: "0,0,0,1   // Alexandria (Alexandroszé)" }
    { group:307, id:49, text: "1,1,A,1   // Alexandria (Ptolemaioszé)" }
    { group:307, id:50, text: "0,0,0,0   // Caesar és Kleopátra" }
    { group:307, id:51, text: "1,1,A,0   // Kleopátra öröksége" }
    { group:307, id:52, text: "1,1,0,0   // Actium" }

    { group:308, id:0, text: "Állatkert" }
    { group:308, id:1, text: "A közeli és távoli vidékek egzotikus állatai elbűvölik a város lakóinak tömegeit az állatkertben." }
    { group:308, id:2, text: "Ennek az állatkertnek vannak gondozói, de vadállathúsra van szüksége, mielőtt bármely állat otthonra találhatna benne." }
    { group:308, id:3, text: "Ennek az állatkertnek vannak alkalmazottai, de szalma nélkül nem fogadhat be egyetlen állatot sem." }
    { group:308, id:4, text: "Az emberek félnek olyan állatkertet látogatni, ahol nincsenek állatgondozók. Amíg az állatkert nem talál alkalmazottakat, nem jelent semmilyen előnyt a környék számára." }
    { group:308, id:5, text: "Állatok nélkül ez az állatkert nem több üres ketrecek sorozatánál." }
    { group:308, id:6, text: "Vadállathús:" }
    { group:308, id:7, text: "Szalma:" }

    { group:309, id:0, text: "A betegségek veszélye olyan nagy, hogy még a nevető hiénák is szomorúak." }
    { group:309, id:1, text: "Hogyan etethetjük az állatokat, amikor magunkat sem tudjuk ellátni?" }
    { group:309, id:2, text: "A védelmünk rettenetesen gyenge. Talán ki kellene képeznem a vízilovat harcra?" }
    { group:309, id:3, text: "Még egy elefánt sem emlékszik rá, mikor volt ennél rosszabb a munkáshiány." }
    { group:309, id:4, text: "Amikor egy isten haragszik, nem szeretnéd, ha a nyakad úgy kilógna, mint egy zsiráfé!" }
    { group:309, id:5, text: "A fáraó nagyon elégedetlen. Remélem, az állatkerti állatokra nincs szükség különleges ajándékokhoz!" }
    { group:309, id:6, text: "Ebben a városban munkát találni nehezebb, mint egy vad oroszlánt csapdába ejteni." }
    { group:309, id:7, text: "A város szórakozási lehetőségei rosszabbul festenek, mint a majomketrecek." }
    { group:309, id:8, text: "Itt élni jobb, mint az oroszlánok kifutójában aludni." }
    { group:309, id:9, text: "Boldogabb vagyok, mint egy sárban fetrengő víziló, hogy ebben a városban élhetek." }

    { group:310, id:0, text: "Felugró üzenetek" }
    { group:310, id:1, text: "Csak a kiválasztott üzenetek jelennek meg a képernyő tetején" }
    { group:310, id:2, text: "Áradási üzenetek" }
    { group:310, id:3, text: "Népességi üzenetek" }
    { group:310, id:4, text: "Mostantól teljesíthető a követelmény" }
    { group:310, id:5, text: "Nő a királyság megítélése" }
    { group:310, id:6, text: "Ünnepségek" }
    { group:310, id:7, text: "Kisebb áldások" }
    { group:310, id:8, text: "Árváltozások" }
    { group:310, id:9, text: "Kereskedelmi szint változásai" }
    { group:310, id:10, text: "Bérváltozások" }
    { group:310, id:11, text: "Betegség sújt le" }
    { group:310, id:12, text: "Malária" }
    { group:310, id:13, text: "Alkalmazottak szükségesek" }
    { group:310, id:14, text: "Rendben" }
    { group:310, id:15, text: "Mégsem" }

    { group:311, id:0, text: "Műemlék korszakának kiválasztása" }
    { group:311, id:1, text: "Piramisok" }
    { group:311, id:2, text: "Királyok Völgye" }
    { group:311, id:3, text: "Alexandria" }
    { group:311, id:4, text: "Abu Szimbel" }

    { group:312, id:0, text: "Kézművesek céhe" }
    { group:312, id:1, text: "A kézművesek itt találkoznak, hogy agyagból vakolatot készítsenek és kikeverjék festékeiket, mielőtt elindulnak egy sír díszítésére." }
    { group:312, id:2, text: "Ennek a céhnek nincsenek alkalmazottai, ezért nem tud kézműveseket küldeni." }
    { group:312, id:3, text: "Ennek a céhnek teljes létszámú kézművescsapata van, akik késedelem nélkül díszítik a sírok belsejét." }
    { group:312, id:4, text: "Ennek a céhnek hiányzik egy-két kézművese. A sírok festése kissé lelassult." }
    { group:312, id:5, text: "Ez a céh igyekszik kézműveseket biztosítani a sírhoz, de kevesebb sírfestőt tud küldeni, mint amennyire képes lenne." }
    { group:312, id:6, text: "Ennek a céhnek sokkal több munkásra van szüksége. Az itt dolgozó néhány magányos kézműves mindent megtesz a sír díszítéséért, de több segítségre van szükségük." }
    { group:312, id:7, text: "A sírokban lévő festéknek bőven van ideje megszáradni. Ha ez a céh nem talál több munkást, a sír díszítése örökké tarthat." }
    { group:312, id:8, text: "A kézművesek nehezen tudnak sírt díszíteni a Festékkészítőből vagy raktárból származó szükséges festék nélkül." }
    { group:312, id:9, text: "A céh nem küld kézműveseket a sírhoz, amíg nem kap agyagszállítmányt." }
    { group:312, id:10, text: "Festék:" }
    { group:312, id:11, text: "Agyag:" }

    { group:313, id:0, text: "Festékkészítő" }
    { group:313, id:1, text: "Itt zúzzák és dolgozzák fel a hennát festékké, amelyet a kézművesek a Királyi Sírok falainak gazdag díszítésére használnak." }
    { group:313, id:2, text: "A termelés" }
    { group:313, id:3, text: "befejeződött." }
    { group:313, id:4, text: "A kereskedelmi felügyelőd leállította a festéktermelést." }
    { group:313, id:5, text: "Ennek a Festékkészítőnek teljesen elfogyott a személyzete. Munkások nélkül nem készülhet festék." }
    { group:313, id:6, text: "Teljes létszámú személyzettel ez a Festékkészítő olyan gyorsan és hatékonyan termel festéket, amennyire csak képes." }
    { group:313, id:7, text: "Ennek a Festékkészítőnek kissé kevés a dolgozója, ezért a festéktermelés akadozik." }
    { group:313, id:8, text: "Ennek a Festékkészítőnek nincs elég munkása, ezért lassabban termel festéket a kelleténél." }
    { group:313, id:9, text: "Ennek a Festékkészítőnek sokkal több munkásra van szüksége. A festéktermelés itt szinte teljesen lelassult." }
    { group:313, id:10, text: "Ezt a Festékkészítőt csak néhány munkás szolgálja ki. A kis létszámú személyzet alig tud egyáltalán festéket előállítani." }
    { group:313, id:11, text: "Ennek a műhelynek hennára van szüksége egy Hennafarmról vagy raktárból, mielőtt bármilyen festéket készíthetne." }
    { group:313, id:12, text: "Henna:" }
]
