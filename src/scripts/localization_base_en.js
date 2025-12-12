log_info("akhenaten: localization_en config started")

localization_base_en = [
    { group:1, id:0, text: "File" }
    { group:1, id:1, text: "New game" }
    { group:1, id:2, text: "Replay mission" }
    { group:1, id:3, text: "Load game" }
    { group:1, id:4, text: "Save game" }
    { group:1, id:5, text: "Exit game" }
    { group:1, id:6, text: "Delete game" }
    { group:2, id:0, text: "Options" }
    { group:2, id:1, text: "Display settings" }
    { group:2, id:2, text: "Sound settings" }
    { group:2, id:3, text: "Speed settings" }
    { group:2, id:4, text: "Pyramid Speedup - OFF" }
    { group:2, id:5, text: "Pyramid Speedup - ON" }
    { group:2, id:6, text: "Difficulty" }
    { group:2, id:7, text: "Cities - Egyptian" }
    { group:2, id:8, text: "Cities - Classical" }
    { group:2, id:9, text: "Autosave - ON" }
    { group:2, id:10, text: "Autosave - OFF" }
    { group:2, id:11, text: "Popup Messages" }
    { group:3, id:0, text: "Help" }
    { group:3, id:1, text: "Help" }
    { group:3, id:2, text: "Mouse help - OFF" }
    { group:3, id:3, text: "Mouse help - SOME" }
    { group:3, id:4, text: "Mouse help - FULL" }
    { group:3, id:5, text: "Warnings - OFF" }
    { group:3, id:6, text: "Warnings - ON" }
    { group:3, id:7, text: "About" }
    { group:3, id:8, text: "Mission Editor Guide" }
    { group:4, id:0, text: "Overseers" }
    { group:4, id:1, text: "Overseer of the Workers" }
    { group:4, id:2, text: "Overseer of the Military" }
    { group:4, id:3, text: "Political Overseer" }
    { group:4, id:4, text: "Ratings Overseer" }
    { group:4, id:5, text: "Overseer of Commerce" }
    { group:4, id:6, text: "Overseer of the Granaries" }
    { group:4, id:7, text: "Overseer of Public Health" }
    { group:4, id:8, text: "Overseer of Learning" }
    { group:4, id:9, text: "Overseer of Diversions" }
    { group:4, id:10, text: "Overseer of the Temples" }
    { group:4, id:11, text: "Overseer of the Treasury" }
    { group:4, id:12, text: "Chief Overseer" }
    { group:4, id:13, text: "Overseer of Monuments" }
    { group:5, id:0, text: "Quit" }
    { group:5, id:1, text: "Leave the Kingdom?" }
    { group:5, id:2, text: "Open trade route" }
    { group:5, id:3, text: "Pay to open this land trade route?" }
    { group:5, id:4, text: "Open trade route" }
    { group:5, id:5, text: "Pay to open this water trade route?" }
    { group:5, id:6, text: "Pharaonic request" }
    { group:5, id:7, text: "Dispatch goods?" }
    { group:5, id:8, text: "Pharaonic request" }
    { group:5, id:9, text: "You do not have enough to fulfill the request " }
    { group:5, id:10, text: "Pharaonic request" }
    { group:5, id:11, text: "You do not have any companies to send" }
    { group:5, id:12, text: "Pharaonic request" }
    { group:5, id:13, text: "Tell your Overseer of the Military to assign some operational companies to Kingdom service" }
    { group:5, id:14, text: "Pharaonic request" }
    { group:5, id:15, text: "Dispatch relief force?" }
    { group:5, id:16, text: "Demolishing a Fort" }
    { group:5, id:17, text: "Are you sure you wish to decommission this Fort?" }
    { group:5, id:18, text: "Missing CD" }
    { group:5, id:19, text: "Please replace your Cleopatra CD in your CD-ROM drive" }
    { group:5, id:20, text: "Demolishing a bridge" }
    { group:5, id:21, text: "Pull down bridges with care. Isolated communities soon perish if they are cut off from the Kingdom road." }
    { group:5, id:22, text: "Quit" }
    { group:5, id:23, text: "Exit without saving?" }
    { group:5, id:24, text: "Old Version" }
    { group:5, id:25, text: "This file is an old version and cannot be loaded" }
    { group:5, id:26, text: "Too many burial provisions!" }
    { group:5, id:27, text: "You cannot have more than 5 burial provisions for this scenario!" }
    { group:5, id:28, text: "Warning!" }
    { group:5, id:29, text: "This burial provision is not available in this scenario!" }
    { group:5, id:30, text: "Not Enough Goods!" }
    { group:5, id:31, text: "You don't have enough goods of this type in storage!" }
    { group:5, id:32, text: "Completed!" }
    { group:5, id:33, text: "You don't need any more burial provisions for this commodity!" }
    { group:5, id:34, text: "Max Cities" }
    { group:5, id:35, text: "The maximum number of cities has been reached" }
    { group:5, id:36, text: "Transport Needed" }
    { group:5, id:37, text: "These troops must board a transport ship to serve the Kingdom in its current conflict." }
    { group:5, id:38, text: "Land Troops Needed" }
    { group:5, id:39, text: "Only troops traveling by land are required to serve the Kingdom in its current conflict." }
    { group:5, id:40, text: "No Troops Needed" }
    { group:5, id:41, text: "There are no requests for troops either by land or sea" }
    { group:5, id:42, text: "Troops In Kingdom" }
    { group:5, id:43, text: "These troops are not in the city" }
    { group:5, id:44, text: "Warship In Kingdom" }
    { group:5, id:45, text: "This warship is not in the city" }
    { group:5, id:46, text: "Cannot Change Price!" }
    { group:5, id:47, text: "This good is not available in this scenario!" }
    { group:5, id:48, text: "This building cannot work." }
    { group:5, id:49, text: "The city cannot produce or import linen." }
    { group:5, id:50, text: "This building cannot work." }
    { group:5, id:51, text: "The city cannot produce or import beer." }
    { group:5, id:52, text: "This building cannot work." }
    { group:5, id:53, text: "The city cannot produce or import papyrus." }
    { group:5, id:54, text: "Mortuaries cannot work." }
    { group:5, id:55, text: "The city cannot produce or import linen. Mortuaries have been removed." }
    { group:5, id:56, text: "Senet House cannot work." }
    { group:5, id:57, text: "The city cannot produce or import beer. Senet Houses have been removed." }
    { group:5, id:58, text: "Scribal Schools cannot work." }
    { group:5, id:59, text: "The city cannot produce or import papyrus. Scribal Schools have been removed." }
    { group:5, id:60, text: "Libraries cannot work. " }
    { group:5, id:61, text: "The city cannot produce or import papyrus. Libraries have been removed." }
    { group:5, id:62, text: "This building cannot work." }
    { group:5, id:63, text: "The city cannot produce or import copper." }
    { group:5, id:64, text: "Weaponsmiths cannot work." }
    { group:5, id:65, text: "The city cannot produce or import copper. Weaponsmiths have been removed." }
    { group:5, id:66, text: "This building cannot work." }
    { group:5, id:67, text: "The city cannot produce or import wood." }
    { group:5, id:68, text: "Chariot Makers cannot work." }
    { group:5, id:69, text: "The city cannot produce or import wood. Chariot Makers have been removed." }
    { group:5, id:70, text: "This building cannot work." }
    { group:5, id:71, text: "This city does not have a Recruiter." }
    { group:5, id:72, text: "Fort: Infantry cannot work." }
    { group:5, id:73, text: "This city does not have a Recruiter. Fort: Infantry has been removed." }
    { group:5, id:74, text: "Fort: Archers cannot work." }
    { group:5, id:75, text: "This city does not have a Recruiter. Fort: Archers has been removed." }
    { group:5, id:76, text: "Fort: Charioteers cannot work." }
    { group:5, id:77, text: "This city does not have a Recruiter. Fort: Charioteer has been removed." }
    { group:5, id:78, text: "Academies cannot work." }
    { group:5, id:79, text: "This city does not have a Recruiter. Academies have been removed." }
    { group:5, id:80, text: "This building cannot work." }
    { group:5, id:81, text: "The city cannot produce or import weapons." }
    { group:5, id:82, text: "This building cannot work." }
    { group:5, id:83, text: "The city cannot produce or import chariots." }
    { group:5, id:84, text: "Fort: Infantry cannot work." }
    { group:5, id:85, text: "This city does not have a Weaponsmith. Fort: Infantry has been removed." }
    { group:5, id:86, text: "Fort: Charioteers cannot work." }
    { group:5, id:87, text: "This city does not have a Chariot Maker. Fort: Charioteer has been removed." }
    { group:5, id:88, text: "Festival: No Festival Square." }
    { group:5, id:89, text: "You need a Festival Square to hold a festival." }
    { group:5, id:90, text: "Delete Dynasty?" }
    { group:5, id:91, text: "This deletes the selected dynasty and all of its saved games. Do you really want to do that?" }
    { group:5, id:92, text: "Dynasty Exists" }
    { group:5, id:93, text: "This name is already being used.  Choose another name." }
    { group:5, id:94, text: "No Dynasty" }
    { group:5, id:95, text: "You must select a dynasty" }
    { group:5, id:96, text: "Warning" }
    { group:5, id:97, text: "You do not have enough debens to hold a festival." }
    { group:5, id:98, text: "Pharaonic request" }
    { group:5, id:99, text: "You do not have any waterborne companies to send." }
    { group:5, id:100, text: "Pharaonic request" }
    { group:5, id:101, text: "Tell your Overseer of the Military to assign some operational waterborne companies to Kingdom service" }
    { group:5, id:102, text: "Dispatch forces" }
    { group:5, id:103, text: "Multiple destinations are possible for the forces you've selected.  Tell your Political Overseer where to send these troops." }
    { group:5, id:104, text: "Demolishing a monument" }
    { group:5, id:105, text: "Are you sure you wish to demolish this monument?" }
    { group:5, id:106, text: "Demolishing a Temple Complex" }
    { group:5, id:107, text: "Shall we really demolish this Temple Complex?" }
    { group:5, id:108, text: "Can't Save" }
    { group:5, id:109, text: "Prey/Pred points in invalid locations." }
    { group:5, id:110, text: "File Exists" }
    { group:5, id:111, text: "Overwrite existing file?" }
    { group:5, id:112, text: "No Sellers" }
    { group:5, id:113, text: "There are currently no cities that wish to sell this commodity." }
    { group:5, id:114, text: "No Buyers" }
    { group:5, id:115, text: "There are currently no cities that wish to buy this commodity." }
    { group:5, id:116, text: "No open trade route" }
    { group:5, id:117, text: "Visit the World Map to open a trade route to export this commodity." }
    { group:5, id:118, text: "Visit the World Map to open a trade route to import this commodity." }
    { group:5, id:119, text: "Warning" }
    { group:5, id:120, text: "You do not have enough debens to open a trade route." }
    { group:5, id:121, text: "Can't Save" }
    { group:5, id:122, text: "Too many food types (4 max)." }
    { group:5, id:123, text: "Cannot Edit World Map" }
    { group:5, id:124, text: "Editing the world map requires a screen resolution of 800x600 or greater." }
    { group:5, id:125, text: "Can't Leave World Map" }
    { group:5, id:126, text: "Too many food types (4 max)." }
    { group:5, id:127, text: "Can't Save" }
    { group:5, id:128, text: "Some Fishing points are in invalid locations." }
    { group:5, id:129, text: "Can't Save" }
    { group:5, id:130, text: "Entry/Exit points in invalid locations." }
    { group:5, id:131, text: "Can't Save" }
    { group:5, id:132, text: "River In/River Out points in invalid locations." }
    { group:5, id:133, text: "Can't Save" }
    { group:5, id:134, text: "Some Invasion(Land) points are in invalid locations." }
    { group:5, id:135, text: "Can't Save" }
    { group:5, id:136, text: "Some Invasion(Water) points are in invalid locations." }
    { group:5, id:137, text: "Pharaoh" }
    { group:5, id:138, text: "Please insert your Cleopatra CD." }
    { group:5, id:139, text: "Zoo cannot work." }
    { group:5, id:140, text: "The city cannot produce or import either game meat or straw. Zoo has been removed." }
    { group:5, id:141, text: "No Missions Won By Family" }
    { group:5, id:142, text: "Please 'Begin Family History' if you are new to Pharaoh.  Continue to choose mission?" }
    { group:6, id:0, text: "Db" }
    { group:6, id:1, text: "Pop" }
    { group:6, id:2, text: "Months to complete mission" }
    { group:6, id:3, text: "Months until victory" }
    { group:6, id:4, text: "Overlays" }
    { group:6, id:5, text: "You have already won this mission, and have chosen to continue governing" }
    { group:6, id:6, text: "Place tombs over cliffs, making sure that the entrance juts out onto clear land" }
    { group:7, id:0, text: "File" }
    { group:7, id:1, text: "New map" }
    { group:7, id:2, text: "Load map" }
    { group:7, id:3, text: "Save map" }
    { group:7, id:4, text: "Exit builder" }
    { group:8, id:0, text: "Debens" }
    { group:8, id:1, text: "Deben" }
    { group:8, id:2, text: "Person" }
    { group:8, id:3, text: "People" }
    { group:8, id:4, text: "Month" }
    { group:8, id:5, text: "Months" }
    { group:8, id:6, text: "Granary holds" }
    { group:8, id:7, text: "Granaries hold" }
    { group:8, id:8, text: "Year" }
    { group:8, id:9, text: "Years" }
    { group:8, id:10, text: "Unit" }
    { group:8, id:11, text: "Units" }
    { group:8, id:12, text: "Employee" }
    { group:8, id:13, text: "Employees" }
    { group:8, id:14, text: "more person" }
    { group:8, id:15, text: "more people" }
    { group:8, id:16, text: "unit." }
    { group:8, id:17, text: "units." }
    { group:8, id:18, text: "Scribal School" }
    { group:8, id:19, text: "Scribal Schools" }
    { group:8, id:20, text: "Academy" }
    { group:8, id:21, text: "Academies" }
    { group:8, id:22, text: "Library" }
    { group:8, id:23, text: "Libraries" }
    { group:8, id:24, text: "Physician" }
    { group:8, id:25, text: "Physicians" }
    { group:8, id:26, text: "Dentist" }
    { group:8, id:27, text: "Dentists" }
    { group:8, id:28, text: "Apothecary" }
    { group:8, id:29, text: "Apothecaries" }
    { group:8, id:30, text: "Mortuary" }
    { group:8, id:31, text: "Mortuaries" }
    { group:8, id:32, text: "Oracle" }
    { group:8, id:33, text: "Oracles" }
    { group:8, id:34, text: "Booth" }
    { group:8, id:35, text: "Booths" }
    { group:8, id:36, text: "Bandstand" }
    { group:8, id:37, text: "Bandstands" }
    { group:8, id:38, text: "Stage" }
    { group:8, id:39, text: "Stages" }
    { group:8, id:40, text: "Senet game" }
    { group:8, id:41, text: "Senet games" }
    { group:8, id:42, text: "Message" }
    { group:8, id:43, text: "Messages" }
    { group:8, id:44, text: "Day" }
    { group:8, id:45, text: "Days" }
    { group:8, id:46, text: "Soldier" }
    { group:8, id:47, text: "Soldiers" }
    { group:8, id:48, text: "Company" }
    { group:8, id:49, text: "Companies" }
    { group:8, id:50, text: "Warship" }
    { group:8, id:51, text: "Warships" }
    { group:8, id:52, text: "Mortuary" }
    { group:8, id:53, text: "Mortuaries" }
    { group:8, id:54, text: "load" }
    { group:8, id:55, text: "loads" }
    { group:8, id:56, text: "Block" }
    { group:8, id:57, text: "Blocks" }
    { group:8, id:58, text: "transport" }
    { group:8, id:59, text: "transports" }
    { group:9, id:0, text: "Pharaoh (Cleopatra Expansion)" }
    { group:9, id:1, text: "Version 2.1" }
    { group:9, id:2, text: "Copyright 1999-2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Beta Release for: BreakAway Games Tester" }
    { group:9, id:4, text: "test1 string" }
    { group:9, id:5, text: "Your Name Here" }
    { group:9, id:6, text: "My Egyptian City" }
    { group:9, id:7, text: "Scenario1" }
    { group:9, id:8, text: "Pharaoh assignment editor" }
    { group:9, id:9, text: "Pharaoh Demo" }
    { group:10, id:0, text: "Resets" }
    { group:10, id:1, text: "Clear Killer Pts." }
    { group:10, id:2, text: "Clear fish" }
    { group:10, id:3, text: "Clear invasions" }
    { group:10, id:4, text: "Clear dsmbark pts." }
    { group:10, id:5, text: "Clear Prey Pts." }
    { group:10, id:6, text: "Load from BMP" }
    { group:10, id:7, text: "Save to BMP" }
    { group:10, id:8, text: "Edit Kingdom" }
    { group:10, id:9, text: "Save Kingdom" }
    { group:10, id:10, text: "Refresh Map" }
    { group:11, id:0, text: "Setting up ..." }
    { group:11, id:1, text: "test_string €,Њ,њ,Ў,°,ї,A,А,Б,В,Д, E,И,Й,К,I,М,Н,О,П,N,С,O,Т,У,Ф,Ц, U,Щ,Ъ,Ы,Ь,Я,a,а,б,в,д,c,з, e,и,й,к,i,м,н,о,п,n,с,o,т,у,ф,ц,u,щ,ъ,ы,ь,..." }
    { group:11, id:2, text: "Loading ..." }
    { group:11, id:3, text: "Preparing data ..." }
    { group:11, id:4, text: "Loading sounds ..." }
    { group:11, id:5, text: "Accelerated Time" }
    { group:11, id:6, text: "Right-click to continue" }
    { group:11, id:7, text: "Loading Backdrops ..." }
    { group:11, id:8, text: "Loading Animations ..." }
    { group:11, id:9, text: "Loading Monuments ..." }
    { group:11, id:10, text: "Loading Enemies ..." }
    { group:11, id:11, text: "Loading Settings ..." }
    { group:12, id:0, text: "Back" }
    { group:12, id:2, text: "to comply" }
    { group:12, id:3, text: "Low food stocks are a problem" }
    { group:12, id:4, text: "High unemployment is a problem" }
    { group:12, id:5, text: "High tax rates are a problem" }
    { group:12, id:6, text: "Low wages are a problem" }
    { group:12, id:7, text: "Inhabitants of low-grade housing want better conditions" }
    { group:13, id:0, text: "Click to continue" }
    { group:13, id:1, text: "Right-click to continue" }
    { group:13, id:2, text: "Game paused ('P' key continues)" }
    { group:13, id:3, text: "Right-click to continue" }
    { group:13, id:4, text: "Cancel" }
    { group:13, id:5, text: "Continue" }
    { group:13, id:6, text: "Not available in the demo!" }
    { group:13, id:7, text: "Click to Start" }
    { group:13, id:8, text: "Choose an Egyptian Name:" }
    { group:14, id:0, text: "Normal" }
    { group:14, id:1, text: "Risks" }
    { group:14, id:2, text: "Water" }
    { group:14, id:3, text: "Entertainment" }
    { group:14, id:4, text: "Religion" }
    { group:14, id:5, text: "Education" }
    { group:14, id:6, text: "Health" }
    { group:14, id:7, text: "Administration" }
    { group:14, id:8, text: "Fire" }
    { group:14, id:9, text: "Damage" }
    { group:14, id:10, text: "Crime" }
    { group:14, id:11, text: "Overall" }
    { group:14, id:12, text: "Juggler" }
    { group:14, id:13, text: "Musician" }
    { group:14, id:14, text: "Dancer" }
    { group:14, id:15, text: "Senet players" }
    { group:14, id:16, text: "Zookeepers" }
    { group:14, id:17, text: "Overall" }
    { group:14, id:18, text: "Scribal Schools" }
    { group:14, id:19, text: "Library" }
    { group:14, id:20, text: "Water Crossings" }
    { group:14, id:21, text: "Dentist" }
    { group:14, id:22, text: "Physician" }
    { group:14, id:23, text: "Apothecary" }
    { group:14, id:24, text: "Mortuary" }
    { group:14, id:25, text: "Tax income" }
    { group:14, id:26, text: "Bazaar access" }
    { group:14, id:27, text: "Desirability" }
    { group:14, id:28, text: "Fertility" }
    { group:14, id:29, text: "Labor" }
    { group:14, id:30, text: "Native" }
    { group:14, id:31, text: "Problems" }
    { group:14, id:32, text: "Problems" }
    { group:14, id:33, text: "Grain" }
    { group:14, id:34, text: "Chickpeas" }
    { group:14, id:35, text: "Pomegranates" }
    { group:14, id:36, text: "Figs" }
    { group:14, id:37, text: "Meat" }
    { group:14, id:38, text: "Game" }
    { group:14, id:39, text: "Pottery" }
    { group:14, id:40, text: "Jewelry" }
    { group:14, id:41, text: "Linen" }
    { group:14, id:42, text: "Beer" }
    { group:14, id:43, text: "Disease" }
    { group:14, id:44, text: "Infected housing" }
    { group:14, id:45, text: "Water" }
    { group:14, id:46, text: "Empty housing" }
    { group:14, id:47, text: "Irrigation" }
    { group:14, id:48, text: "Malaria" }
    { group:14, id:49, text: "City defenses" }
    { group:14, id:50, text: "Magistrate" }
    { group:14, id:51, text: "Hide cliffs" }
    { group:15, id:0, text: "Accept goods" }
    { group:15, id:1, text: "Refuse goods" }
    { group:15, id:2, text: "Go get goods" }
    { group:16, id:0, text: "Building" }
    { group:16, id:1, text: "Fabric" }
    { group:16, id:2, text: "Control" }
    { group:16, id:3, text: "Gfx" }
    { group:16, id:4, text: "Structure" }
    { group:16, id:5, text: "Net" }
    { group:16, id:6, text: "Random" }
    { group:16, id:7, text: "Figure" }
    { group:16, id:8, text: "Anim" }
    { group:16, id:9, text: "Sticky" }
    { group:16, id:10, text: "RM_build" }
    { group:16, id:11, text: "Building - water supply" }
    { group:16, id:12, text: "Building - access" }
    { group:16, id:13, text: "Building - from Capital" }
    { group:16, id:14, text: "Building - damage" }
    { group:16, id:15, text: "Building - Population" }
    { group:16, id:16, text: "Desirability" }
    { group:16, id:17, text: "Height" }
    { group:16, id:18, text: "River sticky" }
    { group:16, id:19, text: "Barb sticky" }
    { group:16, id:20, text: "Damage" }
    { group:16, id:21, text: "Nof figs" }
    { group:16, id:22, text: "Old type" }
    { group:16, id:23, text: "Influence" }
    { group:16, id:24, text: "Wall sticky" }
    { group:16, id:25, text: "Road net" }
    { group:16, id:26, text: "District" }
    { group:17, id:0, text: "North" }
    { group:17, id:1, text: "Northeast" }
    { group:17, id:2, text: "East" }
    { group:17, id:3, text: "Southeast" }
    { group:17, id:4, text: "South" }
    { group:17, id:5, text: "Southwest" }
    { group:17, id:6, text: "West" }
    { group:17, id:7, text: "Northwest" }
    { group:18, id:0, text: "No" }
    { group:18, id:1, text: "Yes" }
    { group:18, id:2, text: "Cancel" }
    { group:18, id:3, text: "OK" }
    { group:18, id:4, text: "ON" }
    { group:18, id:5, text: "OFF" }
    { group:18, id:6, text: "N/A" }
    { group:18, id:7, text: "Tell me more" }
    { group:18, id:8, text: "and" }
    { group:18, id:9, text: "Retry" }
    { group:18, id:10, text: "Abort" }
    { group:18, id:11, text: "Ignore" }
    { group:19, id:0, text: "Must build on cleared land" }
    { group:19, id:1, text: "Out of credit!" }
    { group:19, id:2, text: "You can only have one building of this type" }
    { group:19, id:3, text: "House evolution OFF" }
    { group:19, id:4, text: "House evolution ON" }
    { group:19, id:5, text: "Road evolution OFF" }
    { group:19, id:6, text: "Road evolution ON" }
    { group:19, id:7, text: "Show people OFF" }
    { group:19, id:8, text: "Show people ON" }
    { group:19, id:9, text: "This building needs road access" }
    { group:19, id:10, text: "This building is not next to water!" }
    { group:19, id:11, text: "Not available in this assignment!" }
    { group:19, id:12, text: "Not available... Yet!" }
    { group:19, id:13, text: "unused - alabaster1" }
    { group:19, id:14, text: "unused - alabaster2" }
    { group:19, id:15, text: "Your city needs more workers" }
    { group:19, id:16, text: "People eat more food than they produce" }
    { group:19, id:17, text: "Build Bazaars to distribute the food stored here" }
    { group:19, id:18, text: "Build farms on meadow (look for yellow grass)" }
    { group:19, id:19, text: "Build Clay Pits close to water" }
    { group:19, id:20, text: "Build this next to rocky areas" }
    { group:19, id:21, text: "Build Wood Cutters next to trees" }
    { group:19, id:22, text: "Build this next to rocky areas" }
    { group:19, id:23, text: "Scout along the river to find a suitable site" }
    { group:19, id:24, text: "This building needs copper ore" }
    { group:19, id:25, text: "This building needs barley" }
    { group:19, id:26, text: "This building needs flax" }
    { group:19, id:27, text: "This building needs clay" }
    { group:19, id:28, text: "This building needs gems" }
    { group:19, id:29, text: "Set up a trade route to import it" }
    { group:19, id:30, text: "Instruct the Overseer of Commerce to import it" }
    { group:19, id:31, text: "Build a Copper Mine" }
    { group:19, id:32, text: "Build a Barley Farm" }
    { group:19, id:33, text: "Build an Flax Farm" }
    { group:19, id:34, text: "Build a Clay Pit" }
    { group:19, id:35, text: "Build a Gem Mine" }
    { group:19, id:36, text: "Needs access to a full Water Lift to operate" }
    { group:19, id:37, text: "Needs to be next to water to fill up" }
    { group:19, id:38, text: "Use Irrigation Ditches to connect this to a Water Lift" }
    { group:19, id:39, text: "Must be next to a Wall to send out a patrol" }
    { group:19, id:40, text: "Needs a working Recruiter to conscript soldiers" }
    { group:19, id:41, text: "Some soldiers will need supplies of weapons" }
    { group:19, id:42, text: "Build a Juggling School to send performers here" }
    { group:19, id:43, text: "Build a Conservatory to have musicians here" }
    { group:19, id:44, text: "Build a Dance School" }
    { group:19, id:45, text: "Build a Senet House to host games" }
    { group:19, id:46, text: "unused - demo1" }
    { group:19, id:47, text: "You can only build Towers on thick Walls" }
    { group:19, id:48, text: "Too close to enemy troops!" }
    { group:19, id:49, text: "Company's morale is too low to respond!" }
    { group:19, id:50, text: "Your army has its full complement of Forts" }
    { group:19, id:51, text: "Monthly autosave ON" }
    { group:19, id:52, text: "Monthly autosave OFF" }
    { group:19, id:53, text: "Can't demolish Bridge with people on it" }
    { group:19, id:54, text: "This inland lake has no access to the sea." }
    { group:19, id:55, text: "Cannot set Windows mode." }
    { group:19, id:56, text: "Build Reed Gatherers near marshland." }
    { group:19, id:57, text: "Shipwrights need wood for war vessels" }
    { group:19, id:58, text: "Requires a Palace to convert the gold into deben" }
    { group:19, id:59, text: "You cannot build over animal breeding grounds." }
    { group:19, id:60, text: "Some plots are too far from a road" }
    { group:19, id:61, text: "Part of the city is isolated from the Kingdom road" }
    { group:19, id:62, text: "Until you restore access, that sector will stagnate" }
    { group:19, id:63, text: "Data limit reached - see README" }
    { group:19, id:64, text: "You can only build Roadblocks on roads" }
    { group:19, id:65, text: "Please place the other Ferry Landing" }
    { group:19, id:66, text: "There is no valid spot for this Ferry Landing" }
    { group:19, id:67, text: "The Kingdom already has its maximum four food types." }
    { group:19, id:68, text: "You may not add meat unless you can produce or import straw." }
    { group:19, id:69, text: "You cannot produce meat in the city. It has been removed." }
    { group:19, id:70, text: "You may only have one special rock type in the Kingdom." }
    { group:19, id:71, text: "You must build a Temple Complex first" }
    { group:19, id:72, text: "A Temple Complex can have only one Oracle and one Altar." }
    { group:19, id:73, text: "You must place Oracles and Altars on a Temple Complex." }
    { group:19, id:74, text: "This structure needs groundwater. Build on a grassy area." }
    { group:19, id:75, text: "You must place this entertainment venue over an intersection." }
    { group:19, id:76, text: "You must have a completed Temple first!" }
    { group:19, id:77, text: "You need 500 papyrus to build a Library." }
    { group:19, id:78, text: "This building needs reeds" }
    { group:19, id:79, text: "Build a Reed Gatherer" }
    { group:19, id:80, text: "This building needs straw" }
    { group:19, id:81, text: "Build a Grain Farm" }
    { group:19, id:82, text: "Your city has its full complement of Warship Wharves" }
    { group:19, id:83, text: "You need 100 blocks of granite to build a small obelisk" }
    { group:19, id:84, text: "You need 200 blocks of granite to build a large obelisk" }
    { group:19, id:85, text: "Some of the monuments you have chosen can no longer be built. They have been removed!" }
    { group:19, id:86, text: "You may only build one obelisk at a time" }
    { group:19, id:87, text: "Your city cannot collect taxes without a Palace." }
    { group:19, id:88, text: "You need 220 blocks of sandstone to build a sun temple" }
    { group:19, id:89, text: "You can only have one sun temple under construction at a time" }
    { group:19, id:90, text: "There are already too few jobs for the existing population." }
    { group:19, id:91, text: "Our food levels are low." }
    { group:19, id:92, text: "People already eat more food than they produce." }
    { group:19, id:93, text: "City health has become appalling. Plague is imminent." }
    { group:19, id:94, text: "City health is terrible and plague is very likely." }
    { group:19, id:95, text: "City health is worsening, there is serious risk of plague." }
    { group:19, id:96, text: "City health is getting worse, and plague could strike." }
    { group:19, id:97, text: "Plague is still likely, but health conditions are improving." }
    { group:19, id:98, text: "There is still some risk of plague, but health is improving." }
    { group:19, id:99, text: "Health is improving, but plague still could strike." }
    { group:19, id:100, text: "The Palace has been robbed!" }
    { group:19, id:101, text: "A thief stole some family savings from your Mansion!" }
    { group:19, id:102, text: "We have no troops to defend against the impending attack." }
    { group:19, id:103, text: "You are loathed throughout the city" }
    { group:19, id:104, text: "People are very angry with you" }
    { group:19, id:105, text: "People are angry with you" }
    { group:19, id:106, text: "People are very upset with you" }
    { group:19, id:107, text: "People are upset with you" }
    { group:19, id:108, text: "People are annoyed with you" }
    { group:19, id:109, text: "People are indifferent to you" }
    { group:19, id:110, text: "People are pleased with you" }
    { group:19, id:111, text: "People are very pleased with you" }
    { group:19, id:112, text: "People are extremely pleased with you" }
    { group:19, id:113, text: "People love you" }
    { group:19, id:114, text: "People idolize you as a god" }
    { group:19, id:115, text: "because there isn't enough to eat." }
    { group:19, id:116, text: "because there aren't enough jobs." }
    { group:19, id:117, text: "because taxes are so high." }
    { group:19, id:118, text: "because wages are low." }
    { group:19, id:119, text: "because there are too many slums. " }
    { group:19, id:120, text: "People are immigrating to the city" }
    { group:19, id:121, text: "Lack of housing prevents immigration" }
    { group:19, id:122, text: "Low wages deter immigrants" }
    { group:19, id:123, text: "Lack of jobs deters immigration" }
    { group:19, id:124, text: "Lack of food deters immigration" }
    { group:19, id:125, text: "High taxes discourage immigration" }
    { group:19, id:126, text: "Having some slums prevents immigration" }
    { group:19, id:127, text: "Low City Sentiment prevents immigration" }
    { group:19, id:128, text: "Lack of housing drives people from the city." }
    { group:19, id:129, text: "Low wages prompt people to leave the city." }
    { group:19, id:130, text: "High unemployment makes people leave the city." }
    { group:19, id:131, text: "Lack of food drives hungry people from the city." }
    { group:19, id:132, text: "People would rather leave than pay high taxes." }
    { group:19, id:133, text: "The city's slums encourage people to leave." }
    { group:19, id:134, text: "City Sentiment is so bad that people are leaving." }
    { group:19, id:135, text: "This building needs beer to function" }
    { group:19, id:136, text: "Build a Brewery" }
    { group:19, id:137, text: "This building needs papyrus to function" }
    { group:19, id:138, text: "Build a Papyrus Maker" }
    { group:19, id:139, text: "This building needs linen to function" }
    { group:19, id:140, text: "Build a Weaver" }
    { group:19, id:141, text: "This building needs wood to function" }
    { group:19, id:142, text: "Build a Wood Cutter" }
    { group:19, id:143, text: "This building needs clay and straw" }
    { group:19, id:144, text: "Set up a trade route to import clay" }
    { group:19, id:145, text: "Instruct the Overseer of Commerce to import clay" }
    { group:19, id:146, text: "Set up a trade route to import straw" }
    { group:19, id:147, text: "Instruct the Overseer of Commerce to import straw" }
    { group:19, id:148, text: "This monument needs plain stone and limestone" }
    { group:19, id:149, text: "Build a Plain Stone Quarry" }
    { group:19, id:150, text: "Set up a trade route to import plain stone" }
    { group:19, id:151, text: "Instruct the Overseer of Commerce to import plain stone" }
    { group:19, id:152, text: "Build a Limestone Quarry" }
    { group:19, id:153, text: "Set up a trade route to import limestone" }
    { group:19, id:154, text: "Instruct the Overseer of Commerce to import limestone" }
    { group:19, id:155, text: "This monument needs plain stone" }
    { group:19, id:156, text: "This monument needs limestone" }
    { group:19, id:157, text: "This monument needs bricks and limestone" }
    { group:19, id:158, text: "Build a Brickworks" }
    { group:19, id:159, text: "Set up a trade route to import bricks" }
    { group:19, id:160, text: "Instruct the Overseer of Commerce to import bricks" }
    { group:19, id:161, text: "This monument needs bricks" }
    { group:19, id:162, text: "This monument needs sandstone" }
    { group:19, id:163, text: "Build a Sandstone Quarry" }
    { group:19, id:164, text: "Instruct the Overseer of Commerce to import beer" }
    { group:19, id:165, text: "Set up a trade route to import beer" }
    { group:19, id:166, text: "Instruct the Overseer of Commerce to import barley" }
    { group:19, id:167, text: "Set up a trade route to import barley" }
    { group:19, id:168, text: "Instruct the Overseer of Commerce to import reeds" }
    { group:19, id:169, text: "Set up a trade route to import reeds" }
    { group:19, id:170, text: "Instruct the Overseer of Commerce to import papyrus" }
    { group:19, id:171, text: "Set up a trade route to import papyrus" }
    { group:19, id:172, text: "Instruct the Overseer of Commerce to import flax" }
    { group:19, id:173, text: "Set up a trade route to import flax" }
    { group:19, id:174, text: "Instruct the Overseer of Commerce to import linen" }
    { group:19, id:175, text: "Set up a trade route to import linen" }
    { group:19, id:176, text: "Mortuaries cannot work, and were removed. The city cannot produce or import linen." }
    { group:19, id:177, text: "Senet House cannot work, and was removed. The city cannot produce or import beer." }
    { group:19, id:178, text: "Scribal Schools can't work, and were removed. The city cannot produce or import papyrus." }
    { group:19, id:179, text: "Libraries cannot work, and were removed. The city cannot produce or import papyrus." }
    { group:19, id:180, text: "Weaponsmiths cannot work, and was removed. The city cannot produce or import copper." }
    { group:19, id:181, text: "Chariot Maker cannot work, and was removed. The city cannot produce or import wood." }
    { group:19, id:182, text: "Fort: Infantry cannot work, and was removed. The city does not have a Recruiter." }
    { group:19, id:183, text: "Fort: Archers cannot work, and was removed. The city does not have a Recruiter." }
    { group:19, id:184, text: "Fort: Charioteers cannot work, and was removed. The city does not have a Recruiter." }
    { group:19, id:185, text: "Academies cannot work, and was removed. The city cannot produce or import wood." }
    { group:19, id:186, text: "Fort: Infantry cannot work, and was removed. The city cannot produce or import weapons." }
    { group:19, id:187, text: "Fort: Charioteers cannot work, and was removed. The city cannot produce or import chariots." }
    { group:19, id:188, text: "You need 240 blocks of sandstone to build a mausoleum" }
    { group:19, id:189, text: "Build a Brewery, or order that beer be imported." }
    { group:19, id:190, text: "Build a Brewery or set up a trade route to import beer." }
    { group:19, id:191, text: "Build a Papyrus Maker, or order that it be imported." }
    { group:19, id:192, text: "Build a Papyrus Maker, or open a trade route to import papyrus." }
    { group:19, id:193, text: "Build a Weaver, or order that linen be imported." }
    { group:19, id:194, text: "Build a Weaver or set up a trade route to import linen.   " }
    { group:19, id:195, text: "Thieves just robbed a Tax Collector's office!" }
    { group:19, id:196, text: "Thieves just robbed a Courthouse!" }
    { group:19, id:197, text: "Your Mansion was destroyed and plundered!" }
    { group:19, id:198, text: "The Palace was destroyed and plundered!" }
    { group:19, id:199, text: "A Tax Collector's office was destroyed and plundered!" }
    { group:19, id:200, text: "A Courthouse was destroyed and plundered!" }
    { group:19, id:201, text: "A gold miner was attacked and robbed!" }
    { group:19, id:202, text: "Build a Granary to store the upcoming harvest" }
    { group:19, id:203, text: "Build Granaries to store the upcoming harvest" }
    { group:19, id:204, text: "You may only have 10 docks active at once" }
    { group:19, id:205, text: "Shrines must be within two spaces of a road to affect the city" }
    { group:19, id:206, text: "Build a Juggler's School to provide performers for this venue" }
    { group:19, id:207, text: "Build a Conservatory to supply musicians for this venue" }
    { group:19, id:208, text: "Build a Dance School to train dancers for this venue" }
    { group:19, id:209, text: "This company cannot reach its intended destination" }
    { group:19, id:210, text: "Game saved." }
    { group:19, id:211, text: "Must be built on land free of obstructions" }
    { group:19, id:212, text: "Monument's causeway must lead to water" }
    { group:19, id:213, text: "Build the Festival Square over a road intersection" }
    { group:19, id:214, text: "No one will immigrate while enemies pollute our soil" }
    { group:19, id:215, text: "Cheats enabled" }
    { group:19, id:216, text: "Cheats disabled" }
    { group:19, id:217, text: "Flood will be perfect" }
    { group:19, id:218, text: "Flood will be excellent" }
    { group:19, id:219, text: "Flood will be good" }
    { group:19, id:220, text: "Flood will be mediocre" }
    { group:19, id:221, text: "Flood will be poor" }
    { group:19, id:222, text: "Flood will fail" }
    { group:19, id:223, text: "Price increase" }
    { group:19, id:224, text: "Price decrease" }
    { group:19, id:225, text: "Wages lowered in kingdom" }
    { group:19, id:226, text: "Wages raised in kingdom" }
    { group:19, id:227, text: "Trade decreases with city" }
    { group:19, id:228, text: "Trade increases with city" }
    { group:19, id:229, text: "Kingdom standing climbs" }
    { group:19, id:230, text: "Population milestone reached" }
    { group:19, id:231, text: "Minor god blessing received" }
    { group:19, id:232, text: "Festival is starting" }
    { group:19, id:233, text: "Compliance now possible: goods automatically dispatched" }
    { group:19, id:234, text: "The zoo cannot work, and was removed. The city cannot produce or import either straw or game meat." }
    { group:19, id:235, text: "This building needs game meat to function" }
    { group:19, id:236, text: "Build a Hunting Lodge" }
    { group:19, id:237, text: "Build a Hunting Lodge, or order that game meat be imported." }
    { group:19, id:238, text: "Build a Hunting Lodge or import game meat." }
    { group:19, id:239, text: "This monument needs copper" }
    { group:19, id:240, text: "This monument needs marble" }
    { group:19, id:241, text: "You can only build one Library of Alexandria!" }
    { group:19, id:242, text: "You can only build one Pharos Lighthouse!" }
    { group:19, id:243, text: "You can only build one Caesareum!" }
    { group:19, id:244, text: "Disease strikes" }
    { group:19, id:245, text: "Malaria strikes" }
    { group:19, id:246, text: "This monument needs granite" }
    { group:19, id:247, text: "Must build entirely over rocks" }
    { group:19, id:248, text: "Pharos Lighthouse can not be demolished" }
    { group:19, id:249, text: "Tomb robbers have plundered an ancient tomb!" }
    { group:19, id:250, text: "Alexander the Great's mausoleum has been plundered!" }
    { group:19, id:251, text: "Tomb robbers have stolen burial provisions!" }
    { group:19, id:252, text: "A tomb robber has been apprehended" }
    { group:19, id:253, text: "This building needs oil and pottery to function" }
    { group:19, id:254, text: "Build a Potter" }
    { group:19, id:255, text: "Set up a trade route to import pottery" }
    { group:19, id:256, text: "Instruct the Overseer of Commerce to import pottery" }
    { group:19, id:257, text: "Set up a trade route to import oil" }
    { group:19, id:258, text: "Instruct the Overseer of Commerce to import oil" }
    { group:19, id:259, text: "This building needs henna to function" }
    { group:19, id:260, text: "Build a Henna Farm" }
    { group:19, id:261, text: "Instruct the Overseer of Commerce to import henna" }
    { group:19, id:262, text: "Set up a trade route to import henna" }
    { group:19, id:263, text: "This building needs oil to function" }
    { group:19, id:264, text: "This building needs pottery to function" }
    { group:19, id:265, text: "Build a Paint Maker, or set up a trade route to import paint" }
    { group:19, id:266, text: "Build a Paint Maker, or order the Overseer of Commerce to import it" }
    { group:19, id:267, text: "Build a Paint Maker" }
    { group:19, id:268, text: "This building needs clay and paint to function" }
    { group:19, id:269, text: "Employees needed" }
    { group:19, id:270, text: "Must build entirely over cliffs" }
    { group:19, id:271, text: "... with entranceway on clear land." }
    { group:20, id:0, text: "BC" }
    { group:20, id:1, text: "AD" }
    { group:21, id:0, text: "Elephantine" }
    { group:21, id:1, text: "Abydos" }
    { group:21, id:2, text: "Bahariya Oasis" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apollinopolis" }
    { group:21, id:5, text: "Bubastis" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Byblos" }
    { group:21, id:8, text: "Dahshur" }
    { group:21, id:9, text: "Dakhla Oasis" }
    { group:21, id:10, text: "Abusir" }
    { group:21, id:11, text: "Dunqul Oasis" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "Farafra Oasis" }
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
    { group:21, id:24, text: "Kharga Oasis" }
    { group:21, id:25, text: "Hermopolis" }
    { group:21, id:26, text: "Knossos" }
    { group:21, id:27, text: "Kyrene" }
    { group:21, id:28, text: "Meidum" }
    { group:21, id:29, text: "Memphis" }
    { group:21, id:30, text: "Beni Hasan" }
    { group:21, id:31, text: "Mycenae" }
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
    { group:21, id:42, text: "Mersa Gawasis" }
    { group:21, id:43, text: "Selima Oasis" }
    { group:21, id:44, text: "Serabit Khadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Sharuhen" }
    { group:21, id:47, text: "Thinis" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toshka" }
    { group:21, id:50, text: "Tyre" }
    { group:21, id:51, text: "Thebes" }
    { group:21, id:52, text: "Pelusium" }
    { group:21, id:53, text: "Alexandria" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medina" }
    { group:21, id:56, text: "Abu Simbel" }
    { group:21, id:57, text: "Actium" }
    { group:21, id:58, text: "Rome" }
    { group:21, id:59, text: "Tanis" }
    { group:21, id:60, text: "Pi-Yer" }
    { group:21, id:61, text: "Siwi Oasis" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Piramesse" }
    { group:21, id:64, text: "Athens" }
    { group:21, id:65, text: "Cleoantonopolis" }
    { group:22, id:0, text: "'Empty Company'" }
    { group:22, id:1, text: "'The Lions'" }
    { group:22, id:2, text: "'The Crocodiles'" }
    { group:22, id:3, text: "'The Cobras'" }
    { group:22, id:4, text: "'The Scorpions'" }
    { group:22, id:5, text: "'The Falcons'" }
    { group:22, id:6, text: "'The Rams'" }
    { group:22, id:7, text: "'The Leopards'" }
    { group:22, id:8, text: "'The Spiders'" }
    { group:22, id:9, text: "'The Cats'" }
    { group:22, id:10, text: "'The Hyenas'" }
    { group:23, id:0, text: "Nothing" }
    { group:23, id:1, text: "Grain" }
    { group:23, id:2, text: "Meat" }
    { group:23, id:3, text: "Lettuce" }
    { group:23, id:4, text: "Chickpeas" }
    { group:23, id:5, text: "Pomegranates" }
    { group:23, id:6, text: "Figs" }
    { group:23, id:7, text: "Fish" }
    { group:23, id:8, text: "Game meat" }
    { group:23, id:9, text: "Straw" }
    { group:23, id:10, text: "Weapons" }
    { group:23, id:11, text: "Clay" }
    { group:23, id:12, text: "Bricks" }
    { group:23, id:13, text: "Pottery" }
    { group:23, id:14, text: "Barley" }
    { group:23, id:15, text: "Beer" }
    { group:23, id:16, text: "Flax" }
    { group:23, id:17, text: "Linen" }
    { group:23, id:18, text: "Gems" }
    { group:23, id:19, text: "Luxury goods" }
    { group:23, id:20, text: "Wood" }
    { group:23, id:21, text: "Gold" }
    { group:23, id:22, text: "Reeds" }
    { group:23, id:23, text: "Papyrus" }
    { group:23, id:24, text: "Plain stone" }
    { group:23, id:25, text: "Limestone" }
    { group:23, id:26, text: "Granite" }
    { group:23, id:27, text: "Unused12" }
    { group:23, id:28, text: "Chariot" }
    { group:23, id:29, text: "Copper" }
    { group:23, id:30, text: "Sandstone" }
    { group:23, id:31, text: "Oil" }
    { group:23, id:32, text: "Henna" }
    { group:23, id:33, text: "Paint" }
    { group:23, id:34, text: "Lamps" }
    { group:23, id:35, text: "Marble" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Troops" }
    { group:23, id:38, text: "Jewelry (luxury goods)" }
    { group:23, id:39, text: "Jewelry" }
    { group:23, id:40, text: "Wine (luxury goods)" }
    { group:23, id:41, text: "Wine" }
    { group:23, id:42, text: "Ivory (luxury goods)" }
    { group:23, id:43, text: "Ivory" }
    { group:23, id:44, text: "Ebony (luxury goods)" }
    { group:23, id:45, text: "Ebony" }
    { group:23, id:46, text: "Incense (luxury goods)" }
    { group:23, id:47, text: "Incense" }
    { group:23, id:48, text: "Olive oil (luxury goods)" }
    { group:23, id:49, text: "Olive oil" }
    { group:23, id:50, text: "Leopard skins (luxury goods)" }
    { group:23, id:51, text: "Leopard skins" }
    { group:23, id:52, text: "Perfume (luxury goods)" }
    { group:23, id:53, text: "Perfume" }
    { group:23, id:54, text: "This space left blank" }
    { group:23, id:55, text: "baskets of grain" }
    { group:23, id:56, text: "slabs of meat" }
    { group:23, id:57, text: "heads of lettuce" }
    { group:23, id:58, text: "jars of chickpeas" }
    { group:23, id:59, text: "pomegranates" }
    { group:23, id:60, text: "jars of figs" }
    { group:23, id:61, text: "buckets of fish" }
    { group:23, id:62, text: "portions of game" }
    { group:23, id:63, text: "bales of straw" }
    { group:23, id:64, text: "weapons" }
    { group:23, id:65, text: "bags of clay" }
    { group:23, id:66, text: "bricks" }
    { group:23, id:67, text: "pieces of pottery" }
    { group:23, id:68, text: "parcels of barley" }
    { group:23, id:69, text: "flasks of beer" }
    { group:23, id:70, text: "bales of flax" }
    { group:23, id:71, text: "rolls of linen" }
    { group:23, id:72, text: "gems" }
    { group:23, id:73, text: "pouches of luxury goods" }
    { group:23, id:74, text: "planks of wood" }
    { group:23, id:75, text: "gold" }
    { group:23, id:76, text: "reeds" }
    { group:23, id:77, text: "sheets of papyrus" }
    { group:23, id:78, text: "blocks of plain stone" }
    { group:23, id:79, text: "blocks of limestone" }
    { group:23, id:80, text: "blocks of granite" }
    { group:23, id:81, text: "unused line812" }
    { group:23, id:82, text: "Chariots" }
    { group:23, id:83, text: "ingots of copper" }
    { group:23, id:84, text: "blocks of sandstone" }
    { group:23, id:85, text: "jars of oil" }
    { group:23, id:86, text: "bales of henna" }
    { group:23, id:87, text: "jars of paint" }
    { group:23, id:88, text: "lamps" }
    { group:23, id:89, text: "blocks of marble" }
    { group:23, id:90, text: "debens" }
    { group:23, id:91, text: "troops" }
    { group:24, id:0, text: "Week 1" }
    { group:24, id:1, text: "Week 2" }
    { group:24, id:2, text: "Week 3" }
    { group:24, id:3, text: "Week 4" }
    { group:24, id:4, text: "Week 5" }
    { group:24, id:5, text: "Week 6" }
    { group:24, id:6, text: "Week 7" }
    { group:24, id:7, text: "Week 8" }
    { group:24, id:8, text: "Week 9" }
    { group:24, id:9, text: "Week 10" }
    { group:24, id:10, text: "Week 11" }
    { group:24, id:11, text: "Week 12" }
    { group:24, id:12, text: "Week 13" }
    { group:24, id:13, text: "Week 14" }
    { group:24, id:14, text: "Week 15" }
    { group:24, id:15, text: "Week 16" }
    { group:25, id:0, text: "Jan" }
    { group:25, id:1, text: "Feb" }
    { group:25, id:2, text: "Mar" }
    { group:25, id:3, text: "Apr" }
    { group:25, id:4, text: "May" }
    { group:25, id:5, text: "Jun" }
    { group:25, id:6, text: "Jul" }
    { group:25, id:7, text: "Aug" }
    { group:25, id:8, text: "Sep" }
    { group:25, id:9, text: "Oct" }
    { group:25, id:10, text: "Nov" }
    { group:25, id:11, text: "Dec" }
    { group:26, id:0, text: "Blank" }
    { group:26, id:1, text: "Red" }
    { group:26, id:2, text: "Blue" }
    { group:26, id:3, text: "Green" }
    { group:26, id:4, text: "Orange" }
    { group:26, id:5, text: "Silver" }
    { group:26, id:6, text: "Purple" }
    { group:26, id:7, text: "Yellow" }
    { group:26, id:8, text: "Black" }
    { group:27, id:0, text: "Predynastic Period" }
    { group:27, id:1, text: "Archaic Period" }
    { group:27, id:2, text: "Old Kingdom" }
    { group:27, id:3, text: "Middle Kingdom" }
    { group:27, id:4, text: "New Kingdom" }
    { group:27, id:5, text: "Valley of the Kings" }
    { group:27, id:6, text: "Ramses II" }
    { group:27, id:7, text: "Ancient Conquerors" }
    { group:27, id:8, text: "Cleopatra's Capital" }
    { group:28, id:0, text: "Nowhere" }
    { group:28, id:1, text: "Undo" }
    { group:28, id:2, text: "Farm" }
    { group:28, id:3, text: "Raw Materials" }
    { group:28, id:4, text: "Construction Guilds" }
    { group:28, id:5, text: "Road" }
    { group:28, id:6, text: "Mud Wall" }
    { group:28, id:7, text: "Water Lift" }
    { group:28, id:8, text: "Irrigation Ditch" }
    { group:28, id:9, text: "Dig" }
    { group:28, id:10, text: "House1" }
    { group:28, id:11, text: "House2" }
    { group:28, id:12, text: "House3" }
    { group:28, id:13, text: "House4" }
    { group:28, id:14, text: "House5" }
    { group:28, id:15, text: "House6" }
    { group:28, id:16, text: "House7" }
    { group:28, id:17, text: "House8" }
    { group:28, id:18, text: "House9" }
    { group:28, id:19, text: "House10" }
    { group:28, id:20, text: "House11" }
    { group:28, id:21, text: "House12" }
    { group:28, id:22, text: "House13" }
    { group:28, id:23, text: "House14" }
    { group:28, id:24, text: "House15" }
    { group:28, id:25, text: "House16" }
    { group:28, id:26, text: "House17" }
    { group:28, id:27, text: "House18" }
    { group:28, id:28, text: "House19" }
    { group:28, id:29, text: "House20" }
    { group:28, id:30, text: "Bandstand" }
    { group:28, id:31, text: "Booth" }
    { group:28, id:32, text: "Senet House" }
    { group:28, id:33, text: "Pavilion" }
    { group:28, id:34, text: "Conservatory" }
    { group:28, id:35, text: "Dance School" }
    { group:28, id:36, text: "Juggler School" }
    { group:28, id:37, text: "Senet Master" }
    { group:28, id:38, text: "Plaza" }
    { group:28, id:39, text: "Gardens" }
    { group:28, id:40, text: "Charioteers" }
    { group:28, id:41, text: "Small Statue" }
    { group:28, id:42, text: "Medium Statue" }
    { group:28, id:43, text: "Large Statue" }
    { group:28, id:44, text: "Archers" }
    { group:28, id:45, text: "Infantry" }
    { group:28, id:46, text: "Apothecary" }
    { group:28, id:47, text: "Mortuary" }
    { group:28, id:48, text: "Monuments" }
    { group:28, id:49, text: "Dentist" }
    { group:28, id:50, text: "Storage Yard" }
    { group:28, id:51, text: "Scribal School" }
    { group:28, id:52, text: "Water Crossings" }
    { group:28, id:53, text: "Library" }
    { group:28, id:54, text: "Fort" }
    { group:28, id:55, text: "Police Station" }
    { group:28, id:56, text: "unused 921" }
    { group:28, id:57, text: "Fort" }
    { group:28, id:58, text: "Mud Gatehouse" }
    { group:28, id:59, text: "Mud Tower" }
    { group:28, id:60, text: "Temple to Osiris" }
    { group:28, id:61, text: "Temple to Ra" }
    { group:28, id:62, text: "Temple to Ptah" }
    { group:28, id:63, text: "Temple to Seth" }
    { group:28, id:64, text: "Temple to Bast" }
    { group:28, id:65, text: "Temple Complex to Osiris" }
    { group:28, id:66, text: "Temple Complex to Ra" }
    { group:28, id:67, text: "Temple Complex to Ptah" }
    { group:28, id:68, text: "Temple Complex to Seth" }
    { group:28, id:69, text: "Temple Complex to Bast" }
    { group:28, id:70, text: "Bazaar" }
    { group:28, id:71, text: "Granary" }
    { group:28, id:72, text: "Storage Yard" }
    { group:28, id:73, text: "Storage Yards" }
    { group:28, id:74, text: "Shipwright" }
    { group:28, id:75, text: "Dock" }
    { group:28, id:76, text: "Fishing Wharf" }
    { group:28, id:77, text: "Personal Mansion" }
    { group:28, id:78, text: "Family Mansion" }
    { group:28, id:79, text: "Dynasty Mansion" }
    { group:28, id:80, text: "unused 945" }
    { group:28, id:81, text: "Architect's Post" }
    { group:28, id:82, text: "Bridge" }
    { group:28, id:83, text: "unused 948" }
    { group:28, id:84, text: "Village Palace" }
    { group:28, id:85, text: "Town Palace" }
    { group:28, id:86, text: "Tax Collector" }
    { group:28, id:87, text: "Tax Collector" }
    { group:28, id:88, text: "Nothing" }
    { group:28, id:89, text: "Nothing" }
    { group:28, id:90, text: "Water Lift" }
    { group:28, id:91, text: "Beautification" }
    { group:28, id:92, text: "Well" }
    { group:28, id:93, text: "Nothing" }
    { group:28, id:94, text: "Academy" }
    { group:28, id:95, text: "Recruiter" }
    { group:28, id:96, text: "Temples" }
    { group:28, id:97, text: "Temple Complex" }
    { group:28, id:98, text: "Oracle" }
    { group:28, id:99, text: "Burning ruin" }
    { group:28, id:100, text: "Barley" }
    { group:28, id:101, text: "Flax" }
    { group:28, id:102, text: "Grain" }
    { group:28, id:103, text: "Lettuce" }
    { group:28, id:104, text: "Pomegranates" }
    { group:28, id:105, text: "Chickpeas" }
    { group:28, id:106, text: "Plain Stone Quarry" }
    { group:28, id:107, text: "Limestone Quarry" }
    { group:28, id:108, text: "Wood Cutter" }
    { group:28, id:109, text: "Clay Pit" }
    { group:28, id:110, text: "Brewery" }
    { group:28, id:111, text: "Weaver" }
    { group:28, id:112, text: "Weaponsmith" }
    { group:28, id:113, text: "Jeweler" }
    { group:28, id:114, text: "Potter" }
    { group:28, id:115, text: "Hunting Lodge" }
    { group:28, id:116, text: "Nothing" }
    { group:28, id:117, text: "Nothing" }
    { group:28, id:118, text: "Nothing" }
    { group:28, id:119, text: "Nothing" }
    { group:28, id:120, text: "unused 985" }
    { group:28, id:121, text: "Crack (not used?)" }
    { group:28, id:122, text: "unused 987" }
    { group:28, id:123, text: "Nothing" }
    { group:28, id:124, text: "Nothing" }
    { group:28, id:125, text: "Nothing" }
    { group:28, id:126, text: "Nothing" }
    { group:28, id:127, text: "Nothing" }
    { group:28, id:128, text: "Nothing" }
    { group:28, id:129, text: "Nothing" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Ferry Landing" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Roadblock" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Shrine to Osiris" }
    { group:28, id:141, text: "Shrine to Ra" }
    { group:28, id:142, text: "Shrine to Ptah" }
    { group:28, id:143, text: "Shrine to Seth" }
    { group:28, id:144, text: "Shrine to Bast" }
    { group:28, id:145, text: "Shrine to " }
    { group:28, id:146, text: "Shrine to" }
    { group:28, id:147, text: "Shrine to " }
    { group:28, id:148, text: "Shrine to " }
    { group:28, id:149, text: "Shrine to" }
    { group:28, id:150, text: "Shrines" }
    { group:28, id:151, text: "Temple to Osiris" }
    { group:28, id:152, text: "Temple to Ra" }
    { group:28, id:153, text: "Temple to Ptah" }
    { group:28, id:154, text: "Temple to Seth" }
    { group:28, id:155, text: "Temple to Bast" }
    { group:28, id:156, text: "God 5" }
    { group:28, id:157, text: "God 6" }
    { group:28, id:158, text: "God 7" }
    { group:28, id:159, text: "God 8" }
    { group:28, id:160, text: "God 9" }
    { group:28, id:161, text: "Gold Mine" }
    { group:28, id:162, text: "Gemstone Mine" }
    { group:28, id:163, text: "Ordinary rock" }
    { group:28, id:164, text: "Ore-bearing rock" }
    { group:28, id:165, text: "Unused 1030" }
    { group:28, id:166, text: "Unused 1031" }
    { group:28, id:167, text: "Firehouse" }
    { group:28, id:168, text: "Brick Wall" }
    { group:28, id:169, text: "Wall" }
    { group:28, id:170, text: "Brick Gatehouse" }
    { group:28, id:171, text: "Gatehouse" }
    { group:28, id:172, text: "Brick Tower" }
    { group:28, id:173, text: "Tower" }
    { group:28, id:174, text: "Mud structures" }
    { group:28, id:175, text: "Brick structures" }
    { group:28, id:176, text: "Defensive Structures" }
    { group:28, id:177, text: "Carpenters' Guild" }
    { group:28, id:178, text: "Bricklayers' Guild" }
    { group:28, id:179, text: "Stonemasons' Guild" }
    { group:28, id:180, text: "Water Supply" }
    { group:28, id:181, text: "Transport Wharf" }
    { group:28, id:182, text: "Warship Wharf" }
    { group:28, id:183, text: "Pyramid" }
    { group:28, id:184, text: "Courthouse" }
    { group:28, id:185, text: "Military academy 2" }
    { group:28, id:186, text: "Military academy 3" }
    { group:28, id:187, text: "Village Palace" }
    { group:28, id:188, text: "Town Palace" }
    { group:28, id:189, text: "City Palace" }
    { group:28, id:190, text: "Bazaar 2" }
    { group:28, id:191, text: "Granary 2" }
    { group:28, id:192, text: "Dock 2" }
    { group:28, id:193, text: "Storage Yard 2" }
    { group:28, id:194, text: "Cattle Ranch" }
    { group:28, id:195, text: "Reed Gatherer" }
    { group:28, id:196, text: "Fig Farm" }
    { group:28, id:197, text: "Marshland" }
    { group:28, id:198, text: "Sand dunes" }
    { group:28, id:199, text: "Work Camp" }
    { group:28, id:200, text: "Mud gatehouse" }
    { group:28, id:201, text: "Brick gatehouse" }
    { group:28, id:202, text: "Gatehouse" }
    { group:28, id:203, text: "Papyrus Maker" }
    { group:28, id:204, text: "Brickworks" }
    { group:28, id:205, text: "Chariot Maker" }
    { group:28, id:206, text: "Physician" }
    { group:28, id:207, text: "unused 1072" }
    { group:28, id:208, text: "unused 1073" }
    { group:28, id:209, text: "Festival Square" }
    { group:28, id:210, text: "Sphinx" }
    { group:28, id:211, text: "Temple Complex upgrade" }
    { group:28, id:212, text: "Temple Complex upgrade" }
    { group:28, id:213, text: "unused 1078" }
    { group:28, id:214, text: "Disembark point" }
    { group:28, id:215, text: "unused 1080" }
    { group:28, id:216, text: "Granite Quarry" }
    { group:28, id:217, text: "Copper Mine" }
    { group:28, id:218, text: "temp1" }
    { group:28, id:219, text: "temp2" }
    { group:28, id:220, text: "temp3" }
    { group:28, id:221, text: "Sandstone Quarry" }
    { group:28, id:222, text: "Mausoleum" }
    { group:28, id:223, text: "Cliff" }
    { group:28, id:224, text: "Henna" }
    { group:28, id:225, text: "Alexandria's Library" }
    { group:28, id:226, text: "Zoo" }
    { group:28, id:227, text: "Caesareum" }
    { group:28, id:228, text: "Pharos Lighthouse" }
    { group:28, id:229, text: "Small Royal Burial Tomb" }
    { group:28, id:230, text: "Abu Simbel" }
    { group:28, id:231, text: "Artisans' Guild" }
    { group:28, id:232, text: "Lamp Maker" }
    { group:28, id:233, text: "Paint Maker" }
    { group:28, id:234, text: "Medium Royal Burial Tomb" }
    { group:28, id:235, text: "Large Royal Burial Tomb" }
    { group:28, id:236, text: "Grand Royal Burial Tomb" }
    { group:29, id:0, text: "Crude Hut" }
    { group:29, id:1, text: "Sturdy Hut" }
    { group:29, id:2, text: "Meager Shanty" }
    { group:29, id:3, text: "Common Shanty" }
    { group:29, id:4, text: "Rough Cottage" }
    { group:29, id:5, text: "Ordinary Cottage" }
    { group:29, id:6, text: "Modest Homestead" }
    { group:29, id:7, text: "Spacious Homestead" }
    { group:29, id:8, text: "Modest Apartment" }
    { group:29, id:9, text: "Spacious Apartment" }
    { group:29, id:10, text: "Common Residence" }
    { group:29, id:11, text: "Spacious Residence" }
    { group:29, id:12, text: "Elegant Residence" }
    { group:29, id:13, text: "Fancy Residence" }
    { group:29, id:14, text: "Common Manor" }
    { group:29, id:15, text: "Spacious Manor" }
    { group:29, id:16, text: "Elegant Manor" }
    { group:29, id:17, text: "Stately Manor" }
    { group:29, id:18, text: "Modest Estate" }
    { group:29, id:19, text: "Palatial Estate" }
    { group:29, id:20, text: "Crude Huts" }
    { group:29, id:21, text: "Sturdy Huts" }
    { group:29, id:22, text: "Meager Shanties" }
    { group:29, id:23, text: "Common Shanties" }
    { group:29, id:24, text: "Rough Cottages" }
    { group:29, id:25, text: "Ordinary Cottages" }
    { group:29, id:26, text: "Modest Homesteads" }
    { group:29, id:27, text: "Spacious Homesteads" }
    { group:29, id:28, text: "Modest Apartments" }
    { group:29, id:29, text: "Spacious Apartments" }
    { group:29, id:30, text: "Common Residences" }
    { group:29, id:31, text: "Spacious Residences" }
    { group:29, id:32, text: "Elegant Residences" }
    { group:29, id:33, text: "Fancy Residences" }
    { group:29, id:34, text: "Common Manors" }
    { group:29, id:35, text: "Spacious Manors" }
    { group:29, id:36, text: "Elegant Manors" }
    { group:29, id:37, text: "Stately Manors" }
    { group:29, id:38, text: "Modest Estates" }
    { group:29, id:39, text: "Palatial Estates" }
    { group:29, id:40, text: "Crude Huts:" }
    { group:29, id:41, text: "Sturdy Huts:" }
    { group:29, id:42, text: "Meager Shanties:" }
    { group:29, id:43, text: "Common Shanties:" }
    { group:29, id:44, text: "Rough Cottages:" }
    { group:29, id:45, text: "Ordinary Cottages:" }
    { group:29, id:46, text: "Modest Homesteads:" }
    { group:29, id:47, text: "Spacious Homesteads:" }
    { group:29, id:48, text: "Modest Apartments:" }
    { group:29, id:49, text: "Spacious Apartments:" }
    { group:29, id:50, text: "Common Residences:" }
    { group:29, id:51, text: "Spacious Residences:" }
    { group:29, id:52, text: "Elegant Residences:" }
    { group:29, id:53, text: "Fancy Residences:" }
    { group:29, id:54, text: "Common Manors:" }
    { group:29, id:55, text: "Spacious Manors:" }
    { group:29, id:56, text: "Elegant Manors:" }
    { group:29, id:57, text: "Stately Manors:" }
    { group:29, id:58, text: "Modest Estates:" }
    { group:29, id:59, text: "Palatial Estates:" }
    { group:30, id:0, text: "Play Pharaoh/Cleopatra" }
    { group:30, id:1, text: "Play Pharaoh Demo" }
    { group:30, id:2, text: "  Activision Website " }
    { group:30, id:3, text: "Mission Editor" }
    { group:30, id:4, text: "Quit " }
    { group:30, id:5, text: "Greatest Families" }
    { group:31, id:0, text: "Enter a family name" }
    { group:31, id:1, text: "Right-click to continue" }
    { group:32, id:0, text: "Village Elder" }
    { group:32, id:1, text: "Village Noble" }
    { group:32, id:2, text: "Royal Scholar" }
    { group:32, id:3, text: "Royal Scribe" }
    { group:32, id:4, text: "Royal Judge" }
    { group:32, id:5, text: "Royal Mayor" }
    { group:32, id:6, text: "Royal Governor" }
    { group:32, id:7, text: "Nomarch" }
    { group:32, id:8, text: "Chancellor" }
    { group:32, id:9, text: "Vizier" }
    { group:32, id:10, text: "Pharaoh" }
    { group:32, id:11, text: "O Village Elder" }
    { group:32, id:12, text: "O Village Noble" }
    { group:32, id:13, text: "O Royal Scholar" }
    { group:32, id:14, text: "O Royal Scribe" }
    { group:32, id:15, text: "O Royal Judge" }
    { group:32, id:16, text: "O Royal Mayor" }
    { group:32, id:17, text: "O Royal Governor" }
    { group:32, id:18, text: "O Nomarch" }
    { group:32, id:19, text: "O Chancellor" }
    { group:32, id:20, text: "O Vizier" }
    { group:32, id:21, text: "O Great Pharaoh" }
    { group:32, id:22, text: "Trivial mission" }
    { group:32, id:23, text: "Very simple mission" }
    { group:32, id:24, text: "Easy mission" }
    { group:32, id:25, text: "Somewhat easy mission" }
    { group:32, id:26, text: "Standard mission" }
    { group:32, id:27, text: "Somewhat hard mission" }
    { group:32, id:28, text: "Hard mission" }
    { group:32, id:29, text: "Very hard mission" }
    { group:32, id:30, text: "Extremely hard mission" }
    { group:32, id:31, text: "Virtually impossible mission" }
    { group:33, id:0, text: "Tiny map" }
    { group:33, id:1, text: "Small map" }
    { group:33, id:2, text: "Medium map" }
    { group:33, id:3, text: "Large map" }
    { group:33, id:4, text: "Huge map" }
    { group:33, id:5, text: "Enormous map" }
    { group:33, id:6, text: "Cancel" }
    { group:34, id:0, text: "No invaders" }
    { group:34, id:1, text: "Enemy army" }
    { group:34, id:2, text: "Egyptian Army" }
    { group:34, id:3, text: "Pharaoh's Army" }
    { group:34, id:4, text: "Bedouin Army" }
    { group:35, id:0, text: "Egyptian city falls" }
    { group:35, id:1, text: "foreign city conquered" }
    { group:35, id:2, text: "trade route now available" }
    { group:35, id:3, text: "trade route shuts down" }
    { group:35, id:4, text: "trade city under siege" }
    { group:36, id:0, text: "Attack food chain" }
    { group:36, id:1, text: "Attack gold stores" }
    { group:36, id:2, text: "Attack best buildings" }
    { group:36, id:3, text: "Attack troops" }
    { group:36, id:4, text: "Random attack" }
    { group:37, id:0, text: "Hyksos" }
    { group:37, id:1, text: "Sea People" }
    { group:37, id:2, text: "Hittites" }
    { group:37, id:3, text: "Mitani" }
    { group:37, id:4, text: "Kushites" }
    { group:37, id:5, text: "Libyans" }
    { group:37, id:6, text: "Nubians" }
    { group:37, id:7, text: "Canaanites" }
    { group:37, id:8, text: "Assyrians" }
    { group:37, id:9, text: "Romans" }
    { group:37, id:10, text: "Phoenicians" }
    { group:37, id:11, text: "Persians" }
    { group:37, id:12, text: "Egyptians" }
    { group:37, id:13, text: "Bedouin" }
    { group:37, id:14, text: "A Hyksos soldier" }
    { group:37, id:15, text: "A soldier of the Sea People" }
    { group:37, id:16, text: "A Hittite soldier" }
    { group:37, id:17, text: "A Mitani soldier" }
    { group:37, id:18, text: "A Kushite soldier" }
    { group:37, id:19, text: "A Libyan soldier" }
    { group:37, id:20, text: "A Nubian soldier" }
    { group:37, id:21, text: "A Canaanite soldier" }
    { group:37, id:22, text: "An Assyrian soldier" }
    { group:37, id:23, text: "A Roman soldier" }
    { group:37, id:24, text: "A Phoenician soldier" }
    { group:37, id:25, text: "A Persian soldier" }
    { group:37, id:26, text: "An Egyptian soldier" }
    { group:37, id:27, text: "A Bedouin soldier" }
    { group:37, id:28, text: "a Hyksos army" }
    { group:37, id:29, text: "an army of the Sea People" }
    { group:37, id:30, text: "a Hittite army" }
    { group:37, id:31, text: "a Mitani army" }
    { group:37, id:32, text: "a Kushite army" }
    { group:37, id:33, text: "a Libyan army" }
    { group:37, id:34, text: "a Nubian army" }
    { group:37, id:35, text: "a Canaanite army" }
    { group:37, id:36, text: "an Assyrian army" }
    { group:37, id:37, text: "a Roman army" }
    { group:37, id:38, text: "a Phoenician army" }
    { group:37, id:39, text: "a Persian army" }
    { group:37, id:40, text: "an Eygptian army" }
    { group:37, id:41, text: "a Bedouin army" }
    { group:38, id:0, text: "Special events" }
    { group:38, id:1, text: "Earthquake" }
    { group:38, id:2, text: "Gladiator revolt" }
    { group:38, id:3, text: "Change of Pharaoh" }
    { group:38, id:4, text: "Sea trade problem" }
    { group:38, id:5, text: "Land trade problem" }
    { group:38, id:6, text: "Pharaoh raises wages" }
    { group:38, id:7, text: "Pharaoh lowers wages" }
    { group:38, id:8, text: "Contaminated water" }
    { group:38, id:9, text: "Gold mine collapse" }
    { group:38, id:10, text: "Clay pits flooded" }
    { group:38, id:11, text: "In use" }
    { group:38, id:12, text: "Timing" }
    { group:38, id:13, text: "Random" }
    { group:39, id:0, text: "Our city" }
    { group:39, id:1, text: "Pharaoh Trade City" }
    { group:39, id:2, text: "Pharaoh City" }
    { group:39, id:3, text: "Egyptian Trade City" }
    { group:39, id:4, text: "Egyptian City" }
    { group:39, id:5, text: "Foreign Trade City" }
    { group:39, id:6, text: "Foreign City" }
    { group:40, id:0, text: "None" }
    { group:40, id:1, text: "Minor" }
    { group:40, id:2, text: "Average" }
    { group:40, id:3, text: "Major" }
    { group:41, id:0, text: "Nowhere" }
    { group:41, id:1, text: "Nothing" }
    { group:41, id:2, text: "Nothing" }
    { group:41, id:3, text: "Nothing" }
    { group:41, id:4, text: "Nothing" }
    { group:41, id:5, text: "Road" }
    { group:41, id:6, text: "Mud wall" }
    { group:41, id:7, text: "Irrigation Ditch" }
    { group:41, id:8, text: "Water Lift" }
    { group:41, id:9, text: "Nothing" }
    { group:41, id:10, text: "Crude Hut" }
    { group:41, id:11, text: "Sturdy Hut" }
    { group:41, id:12, text: "Meager Shanty" }
    { group:41, id:13, text: "Common Shanty" }
    { group:41, id:14, text: "Rough Cottage" }
    { group:41, id:15, text: "Ordinary Cottage" }
    { group:41, id:16, text: "Modest Homestead" }
    { group:41, id:17, text: "Spacious Homestead" }
    { group:41, id:18, text: "Modest Apartment" }
    { group:41, id:19, text: "Spacious Apartment" }
    { group:41, id:20, text: "Common Residence" }
    { group:41, id:21, text: "Spacious Residence" }
    { group:41, id:22, text: "Elegant Residence" }
    { group:41, id:23, text: "Fancy Residence" }
    { group:41, id:24, text: "Common Manor" }
    { group:41, id:25, text: "Spacious Manor" }
    { group:41, id:26, text: "Elegant Manor" }
    { group:41, id:27, text: "Stately Manor" }
    { group:41, id:28, text: "Modest Estate" }
    { group:41, id:29, text: "Palatial Estate" }
    { group:41, id:30, text: "Bandstand" }
    { group:41, id:31, text: "Booth" }
    { group:41, id:32, text: "Senet House" }
    { group:41, id:33, text: "Pavilion" }
    { group:41, id:34, text: "Conservatory" }
    { group:41, id:35, text: "Dance School" }
    { group:41, id:36, text: "Juggler School" }
    { group:41, id:37, text: "Chariot training" }
    { group:41, id:38, text: "Plaza" }
    { group:41, id:39, text: "Gardens" }
    { group:41, id:40, text: "Infantry Fort" }
    { group:41, id:41, text: "Small Statue" }
    { group:41, id:42, text: "Medium Statue" }
    { group:41, id:43, text: "Large Statue" }
    { group:41, id:44, text: "Archers" }
    { group:41, id:45, text: "Infantry" }
    { group:41, id:46, text: "Apothecary" }
    { group:41, id:47, text: "Mortuary" }
    { group:41, id:48, text: "Monuments" }
    { group:41, id:49, text: "Dentist" }
    { group:41, id:50, text: "Distribution center" }
    { group:41, id:51, text: "Scribal School" }
    { group:41, id:52, text: "Water Crossings" }
    { group:41, id:53, text: "Library" }
    { group:41, id:54, text: "Nothing" }
    { group:41, id:55, text: "Police Station" }
    { group:41, id:56, text: "unused 1315" }
    { group:41, id:57, text: "Forts" }
    { group:41, id:58, text: "Mud Gatehouse" }
    { group:41, id:59, text: "Mud Tower" }
    { group:41, id:60, text: "Temple to Osiris" }
    { group:41, id:61, text: "Temple to Ra" }
    { group:41, id:62, text: "Temple to Ptah" }
    { group:41, id:63, text: "Temple to Seth" }
    { group:41, id:64, text: "Temple to Bast" }
    { group:41, id:65, text: "Temple Complex to Osiris" }
    { group:41, id:66, text: "Temple Complex to Ra" }
    { group:41, id:67, text: "Temple Complex to Ptah" }
    { group:41, id:68, text: "Temple Complex to Seth" }
    { group:41, id:69, text: "Temple Complex to Bast" }
    { group:41, id:70, text: "Bazaar" }
    { group:41, id:71, text: "Granary" }
    { group:41, id:72, text: "Storage Yard" }
    { group:41, id:73, text: "Storage Yards" }
    { group:41, id:74, text: "Shipwright" }
    { group:41, id:75, text: "Dock" }
    { group:41, id:76, text: "Fishing Wharf" }
    { group:41, id:77, text: "Personal Mansion" }
    { group:41, id:78, text: "Family Mansion" }
    { group:41, id:79, text: "Dynasty Mansion" }
    { group:41, id:80, text: "unused 1339" }
    { group:41, id:81, text: "Architect's Post" }
    { group:41, id:82, text: "Small Bridge" }
    { group:41, id:83, text: "Large Bridge" }
    { group:41, id:84, text: "Village Palace" }
    { group:41, id:85, text: "Town Palace" }
    { group:41, id:86, text: "Tax Collector" }
    { group:41, id:87, text: "Tax Collector" }
    { group:41, id:88, text: "unused 1347" }
    { group:41, id:89, text: "unused 1348" }
    { group:41, id:90, text: "Water Lift" }
    { group:41, id:91, text: "Beautification" }
    { group:41, id:92, text: "Well" }
    { group:41, id:93, text: "Nothing" }
    { group:41, id:94, text: "Academy" }
    { group:41, id:95, text: "Recruiter" }
    { group:41, id:96, text: "Nothing" }
    { group:41, id:97, text: "Nothing" }
    { group:41, id:98, text: "Oracle" }
    { group:41, id:99, text: "Burning ruin" }
    { group:41, id:100, text: "Barley Farm" }
    { group:41, id:101, text: "Flax Farm" }
    { group:41, id:102, text: "Grain Farm" }
    { group:41, id:103, text: "Lettuce Farm" }
    { group:41, id:104, text: "Pomegranate Farm" }
    { group:41, id:105, text: "Chickpea Farm" }
    { group:41, id:106, text: "Plain Stone Quarry" }
    { group:41, id:107, text: "Limestone Quarry" }
    { group:41, id:108, text: "Wood Cutter" }
    { group:41, id:109, text: "Clay Pit" }
    { group:41, id:110, text: "Brewery" }
    { group:41, id:111, text: "Weaver" }
    { group:41, id:112, text: "Weaponsmith" }
    { group:41, id:113, text: "Jeweler" }
    { group:41, id:114, text: "Potter" }
    { group:41, id:115, text: "Hunting Lodge " }
    { group:41, id:116, text: "Grass " }
    { group:41, id:117, text: "Trees " }
    { group:41, id:118, text: "Water " }
    { group:41, id:119, text: "Earthquake " }
    { group:41, id:120, text: "Scrub " }
    { group:41, id:121, text: "Rocks " }
    { group:41, id:122, text: "Meadow " }
    { group:41, id:123, text: "unused 1382" }
    { group:41, id:124, text: "unused 1383" }
    { group:41, id:125, text: "Road " }
    { group:41, id:126, text: "Invasion point " }
    { group:41, id:127, text: "Entry point " }
    { group:41, id:128, text: "Exit point " }
    { group:41, id:129, text: "unused 1388 " }
    { group:41, id:130, text: "River in " }
    { group:41, id:131, text: "River out " }
    { group:41, id:132, text: "Fishing point " }
    { group:41, id:133, text: "Killer point " }
    { group:41, id:134, text: "Flood plain " }
    { group:41, id:135, text: "Irrigation " }
    { group:41, id:136, text: "Ferry Landing " }
    { group:41, id:137, text: "Road system " }
    { group:41, id:138, text: "Road Block " }
    { group:41, id:139, text: "Map prey point " }
    { group:41, id:140, text: "Shrine to Osiris" }
    { group:41, id:141, text: "Shrine to Ra" }
    { group:41, id:142, text: "Shrine to Ptah" }
    { group:41, id:143, text: "Shrine to Seth" }
    { group:41, id:144, text: "Shrine to Bast" }
    { group:41, id:145, text: "Shrine God5" }
    { group:41, id:146, text: "Shrine God6" }
    { group:41, id:147, text: "Shrine God7" }
    { group:41, id:148, text: "Shrine God8" }
    { group:41, id:149, text: "Shrine God9" }
    { group:41, id:150, text: "Shrine" }
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
    { group:41, id:161, text: "Gold Mine" }
    { group:41, id:162, text: "Gemstone Mine" }
    { group:41, id:163, text: "Ordinary rock" }
    { group:41, id:164, text: "Gold rock" }
    { group:41, id:165, text: "Gem rock" }
    { group:41, id:166, text: "Finishing rock" }
    { group:41, id:167, text: "Firehouse" }
    { group:41, id:168, text: "Brick Wall" }
    { group:41, id:169, text: "Wall" }
    { group:41, id:170, text: "Brick Gatehouse" }
    { group:41, id:171, text: "Gatehouse" }
    { group:41, id:172, text: "Brick Tower" }
    { group:41, id:173, text: "Tower" }
    { group:41, id:174, text: "Mud structures" }
    { group:41, id:175, text: "Brick structures" }
    { group:41, id:176, text: "Defensive Structures" }
    { group:41, id:177, text: "Carpenters' Guild" }
    { group:41, id:178, text: "Bricklayers' Guild" }
    { group:41, id:179, text: "Stonemasons' Guild" }
    { group:41, id:180, text: "Water Supply" }
    { group:41, id:181, text: "Transport Wharf" }
    { group:41, id:182, text: "Warship Wharf" }
    { group:41, id:183, text: "Pyramid" }
    { group:41, id:184, text: "Courthouse" }
    { group:41, id:185, text: "Military academy 2" }
    { group:41, id:186, text: "Military academy 3" }
    { group:41, id:187, text: "Village Palace" }
    { group:41, id:188, text: "Town Palace" }
    { group:41, id:189, text: "City Palace" }
    { group:41, id:190, text: "Bazaar 2" }
    { group:41, id:191, text: "Granary 2" }
    { group:41, id:192, text: "Dock 2" }
    { group:41, id:193, text: "Storage yard 2" }
    { group:41, id:194, text: "Cattle Farm" }
    { group:41, id:195, text: "Reed Gatherer" }
    { group:41, id:196, text: "Fig Farm" }
    { group:41, id:197, text: "Marshland" }
    { group:41, id:198, text: "Sand dune" }
    { group:41, id:199, text: "Work Camp" }
    { group:41, id:200, text: "Mud Gatehouse" }
    { group:41, id:201, text: "Brick Gatehouse" }
    { group:41, id:202, text: "Gatehouse" }
    { group:41, id:203, text: "Papyrus Maker" }
    { group:41, id:204, text: "Brick Maker" }
    { group:41, id:205, text: "Chariot Maker" }
    { group:41, id:206, text: "Physician" }
    { group:41, id:207, text: "unused 1466" }
    { group:41, id:208, text: "unused 1467" }
    { group:41, id:209, text: "Festival Square" }
    { group:41, id:210, text: "Sphinx" }
    { group:41, id:211, text: "Temple Complex upgrade" }
    { group:41, id:212, text: "Temple Complex upgrade" }
    { group:41, id:213, text: "unused 1472" }
    { group:41, id:214, text: "Disembark point" }
    { group:41, id:215, text: "unused 1474" }
    { group:41, id:216, text: "Granite Quarry" }
    { group:41, id:217, text: "Copper Mine" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Sandstone quarry" }
    { group:41, id:222, text: "Mausoleum" }
    { group:41, id:223, text: "Cliff" }
    { group:41, id:224, text: "Henna Farm" }
    { group:41, id:225, text: "Alexandria's Library" }
    { group:41, id:226, text: "Zoo" }
    { group:41, id:227, text: "Caesareum" }
    { group:41, id:228, text: "Pharos Lighthouse" }
    { group:41, id:229, text: "Small Royal Burial Tomb" }
    { group:41, id:230, text: "Abu Simbel" }
    { group:41, id:231, text: "Artisans' Guild" }
    { group:41, id:232, text: "Lamp Maker" }
    { group:41, id:233, text: "Paint Maker" }
    { group:41, id:234, text: "Medium Royal Burial Tomb" }
    { group:41, id:235, text: "Large Royal Burial Tomb" }
    { group:41, id:236, text: "Grand Royal Burial Tomb" }
    { group:42, id:0, text: "Display options" }
    { group:42, id:1, text: "Full screen" }
    { group:42, id:2, text: "Windowed screen" }
    { group:42, id:3, text: "640 x 480 resolution" }
    { group:42, id:4, text: "800 x 600 resolution" }
    { group:42, id:5, text: "1024 x 768 resolution" }
    { group:42, id:6, text: "Cancel" }
    { group:43, id:0, text: "Saving your city" }
    { group:43, id:1, text: "Loading saved game" }
    { group:43, id:2, text: "File does not exist" }
    { group:43, id:3, text: "Saving a mission" }
    { group:43, id:4, text: "Loading a mission" }
    { group:43, id:5, text: "Proceed?" }
    { group:43, id:6, text: "Delete a file" }
    { group:44, id:0, text: "Add object" }
    { group:44, id:1, text: "Edit objects" }
    { group:44, id:2, text: "Delete object" }
    { group:44, id:3, text: "General" }
    { group:44, id:4, text: "Import map" }
    { group:44, id:5, text: "Buys" }
    { group:44, id:6, text: "not free" }
    { group:44, id:7, text: "Ok" }
    { group:44, id:8, text: "Simple graphic" }
    { group:44, id:9, text: "City" }
    { group:44, id:10, text: "Region" }
    { group:44, id:11, text: "Battle marker" }
    { group:44, id:12, text: "free" }
    { group:44, id:13, text: "Start date" }
    { group:44, id:14, text: "Pharaoh requests" }
    { group:44, id:15, text: "Invasions" }
    { group:44, id:16, text: "Accept" }
    { group:44, id:17, text: "Cancel" }
    { group:44, id:18, text: "Current state of Kingdom" }
    { group:44, id:19, text: "No requests" }
    { group:44, id:20, text: "No invasions" }
    { group:44, id:21, text: "Mission not yet won" }
    { group:44, id:22, text: "Scheduling an invasion" }
    { group:44, id:23, text: "Free slot" }
    { group:44, id:24, text: "in" }
    { group:44, id:25, text: "Unschedule request" }
    { group:44, id:26, text: "Unschedule invasion" }
    { group:44, id:27, text: "from" }
    { group:44, id:28, text: "Land route" }
    { group:44, id:29, text: "Sea route" }
    { group:44, id:30, text: "Army marker" }
    { group:44, id:31, text: "Enemy marker" }
    { group:44, id:32, text: "Route" }
    { group:44, id:33, text: "Demand" }
    { group:44, id:34, text: "Cost" }
    { group:44, id:35, text: "Resources" }
    { group:44, id:36, text: "Sells" }
    { group:44, id:37, text: "Brief description" }
    { group:44, id:38, text: "Brief description of this mission, for players. History, aims and tips etc." }
    { group:44, id:39, text: "Initial funds" }
    { group:44, id:40, text: "Requests" }
    { group:44, id:41, text: "Enemy is" }
    { group:44, id:42, text: "Invasions" }
    { group:44, id:43, text: "Capital supplies grain?" }
    { group:44, id:44, text: "Buildings allowed" }
    { group:44, id:45, text: "Win criteria" }
    { group:44, id:46, text: "Adjust" }
    { group:44, id:47, text: "Allowed structures" }
    { group:44, id:48, text: "Win criteria" }
    { group:44, id:49, text: "Special events" }
    { group:44, id:50, text: "Culture needed" }
    { group:44, id:51, text: "Prosperity needed" }
    { group:44, id:52, text: "Number of monuments" }
    { group:44, id:53, text: "Kingdom needed" }
    { group:44, id:54, text: "Time limit (losing time)" }
    { group:44, id:55, text: "Survival (Winning time)" }
    { group:44, id:56, text: "Winning population" }
    { group:44, id:57, text: "Need quake point" }
    { group:44, id:58, text: "Quake point set" }
    { group:44, id:59, text: "No entry point" }
    { group:44, id:60, text: "No people points" }
    { group:44, id:61, text: "No exit point" }
    { group:44, id:62, text: "People points set" }
    { group:44, id:63, text: "No invasion points" }
    { group:44, id:64, text: "1 invasion point" }
    { group:44, id:65, text: "invasion points" }
    { group:44, id:66, text: "No river points" }
    { group:44, id:67, text: "River points set" }
    { group:44, id:68, text: "Pharaoh Gift" }
    { group:44, id:69, text: "Battle marker" }
    { group:44, id:70, text: "Path" }
    { group:44, id:71, text: "Order" }
    { group:44, id:72, text: "Wants" }
    { group:44, id:73, text: "Kingdom" }
    { group:44, id:74, text: "Milestones at" }
    { group:44, id:75, text: "Save" }
    { group:44, id:76, text: "Terrain set" }
    { group:44, id:77, text: "Humid climate" }
    { group:44, id:78, text: "Normal climate" }
    { group:44, id:79, text: "Arid climate" }
    { group:44, id:80, text: "Flotsam on?" }
    { group:44, id:81, text: "Expansion at" }
    { group:44, id:82, text: "Expanded positions" }
    { group:44, id:83, text: "Set Supply/demand levels" }
    { group:44, id:84, text: "None" }
    { group:44, id:85, text: "Low" }
    { group:44, id:86, text: "Med" }
    { group:44, id:87, text: "High" }
    { group:44, id:88, text: "Starting conditions" }
    { group:44, id:89, text: "Adjust the start date" }
    { group:44, id:90, text: "Entry 90 - used as a marker only" }
    { group:44, id:91, text: "Milestone - 25%" }
    { group:44, id:92, text: "Milestone - 50%" }
    { group:44, id:93, text: "Milestone - 75%" }
    { group:44, id:94, text: "Demand changes" }
    { group:44, id:95, text: "Events" }
    { group:44, id:96, text: "Add event" }
    { group:44, id:97, text: "Delete event" }
    { group:44, id:98, text: "in route" }
    { group:44, id:99, text: "falls" }
    { group:44, id:100, text: "rises" }
    { group:44, id:101, text: "demand for this good" }
    { group:44, id:102, text: "unused 1601" }
    { group:44, id:103, text: "falls by" }
    { group:44, id:104, text: "rises by" }
    { group:44, id:105, text: "invalid trigger event" }
    { group:44, id:106, text: "TIP: Use the comma and full stop keys to quickly move through these and other objects." }
    { group:44, id:107, text: "Open play (No win/lose)" }
    { group:44, id:108, text: "Initial rank" }
    { group:44, id:109, text: "Terrain" }
    { group:44, id:110, text: "Enemies" }
    { group:44, id:111, text: "Invasions" }
    { group:44, id:112, text: "No military activity" }
    { group:44, id:113, text: "Minor skirmishes" }
    { group:44, id:114, text: "Some military activity" }
    { group:44, id:115, text: "Much military activity" }
    { group:44, id:116, text: "City is under attack" }
    { group:44, id:117, text: "Rank" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "Capital feeds?" }
    { group:44, id:120, text: "Map size" }
    { group:44, id:121, text: "Tiny landscape" }
    { group:44, id:122, text: "Small landscape" }
    { group:44, id:123, text: "Average landscape" }
    { group:44, id:124, text: "Large landscape" }
    { group:44, id:125, text: "Very large land" }
    { group:44, id:126, text: "Enormous land" }
    { group:44, id:127, text: "Win conditions" }
    { group:44, id:128, text: "None" }
    { group:44, id:129, text: "Culture" }
    { group:44, id:130, text: "Prosperity" }
    { group:44, id:131, text: "Monument" }
    { group:44, id:132, text: "Kingdom" }
    { group:44, id:133, text: "People" }
    { group:44, id:134, text: "Years maximum" }
    { group:44, id:135, text: "Survival years" }
    { group:44, id:136, text: "Go to city" }
    { group:44, id:137, text: "Need river in" }
    { group:44, id:138, text: "Need river out" }
    { group:44, id:139, text: "Event" }
    { group:44, id:140, text: "month" }
    { group:44, id:141, text: "between" }
    { group:44, id:142, text: "and" }
    { group:44, id:143, text: "cities" }
    { group:44, id:144, text: "from markers" }
    { group:44, id:145, text: "to" }
    { group:44, id:146, text: "amount" }
    { group:44, id:147, text: "scale" }
    { group:44, id:148, text: "of" }
    { group:44, id:149, text: "within" }
    { group:44, id:150, text: "months" }
    { group:44, id:151, text: "comply event" }
    { group:44, id:152, text: "refuse event" }
    { group:44, id:153, text: "too late event" }
    { group:44, id:154, text: "forfeit event" }
    { group:44, id:155, text: "lose battle event" }
    { group:44, id:156, text: "next event" }
    { group:44, id:157, text: "one time event" }
    { group:44, id:158, text: "recurring event" }
    { group:44, id:159, text: "triggered only" }
    { group:44, id:160, text: "triggered by favor" }
    { group:44, id:161, text: "Pharaoh" }
    { group:44, id:162, text: "City" }
    { group:44, id:163, text: "Warships" }
    { group:44, id:164, text: "Gods settings" }
    { group:44, id:165, text: "No patron god" }
    { group:44, id:166, text: "Add route" }
    { group:44, id:167, text: "Edit route" }
    { group:44, id:168, text: "Delete route" }
    { group:44, id:169, text: "General route" }
    { group:44, id:170, text: "Sea trade route" }
    { group:44, id:171, text: "Land trade route" }
    { group:44, id:172, text: "Spacing" }
    { group:44, id:173, text: "Route length" }
    { group:44, id:174, text: "Name" }
    { group:44, id:175, text: "Rank" }
    { group:44, id:176, text: "Temple Complex" }
    { group:44, id:177, text: "Interest rate on debt" }
    { group:44, id:178, text: "Flood plain settings" }
    { group:44, id:179, text: "Flooding starts on:" }
    { group:44, id:180, text: "Early June" }
    { group:44, id:181, text: "Late June" }
    { group:44, id:182, text: "Early July" }
    { group:44, id:183, text: "Late July" }
    { group:44, id:184, text: "Early August" }
    { group:44, id:185, text: "Late August" }
    { group:44, id:186, text: "Early September" }
    { group:44, id:187, text: "Late September" }
    { group:44, id:188, text: "Flooding lasts for:" }
    { group:44, id:189, text: "Two Months" }
    { group:44, id:190, text: "Three Months" }
    { group:44, id:191, text: "Four Months" }
    { group:44, id:192, text: "Flooding quality:" }
    { group:44, id:193, text: "None" }
    { group:44, id:194, text: "Poor" }
    { group:44, id:195, text: "Mediocre" }
    { group:44, id:196, text: "Good" }
    { group:44, id:197, text: "Excellent" }
    { group:44, id:198, text: "Perfect" }
    { group:44, id:199, text: "Fail flood" }
    { group:44, id:200, text: "Perfect flood" }
    { group:44, id:201, text: "Select monuments" }
    { group:44, id:202, text: "Current Pharaoh:" }
    { group:44, id:203, text: "Player incarnation:" }
    { group:44, id:204, text: "Set Kingdom prices" }
    { group:44, id:205, text: "Buys" }
    { group:44, id:206, text: "Sells" }
    { group:44, id:207, text: "Accept" }
    { group:44, id:208, text: "Refuse" }
    { group:44, id:209, text: "Postpone" }
    { group:44, id:210, text: "Housing level" }
    { group:44, id:211, text: "Reset prices" }
    { group:44, id:212, text: "God" }
    { group:44, id:213, text: "1 cartload or block of stone = 100 units" }
    { group:44, id:214, text: "Edit this map" }
    { group:44, id:215, text: "Play this mission" }
    { group:44, id:216, text: "Difficulty Level" }
    { group:44, id:217, text: "Exit" }
    { group:44, id:218, text: "Start Mission" }
    { group:44, id:219, text: "Cancel" }
    { group:44, id:220, text: "Show Prior Results" }
    { group:44, id:221, text: "Show Mission Objectives" }
    { group:44, id:222, text: "Kingdom builder" }
    { group:44, id:223, text: "Reset" }
    { group:44, id:224, text: "Entry point set" }
    { group:44, id:225, text: "Exit point set" }
    { group:44, id:226, text: "1 River point set" }
    { group:44, id:227, text: "Player fights Egypt as" }
    { group:45, id:0, text: "Speed options" }
    { group:45, id:1, text: "Cancel" }
    { group:45, id:2, text: "Game speed" }
    { group:45, id:3, text: "Scroll speed" }
    { group:45, id:4, text: "OK" }
    { group:46, id:0, text: "Sound options" }
    { group:46, id:1, text: "Music is off" }
    { group:46, id:2, text: "Music is on" }
    { group:46, id:3, text: "Speech is off" }
    { group:46, id:4, text: "Speech is on" }
    { group:46, id:5, text: "Sound effects are off" }
    { group:46, id:6, text: "Sound effects are on" }
    { group:46, id:7, text: "City sounds are off" }
    { group:46, id:8, text: "City sounds are on" }
    { group:46, id:9, text: "Cancel" }
    { group:46, id:10, text: "Current audio state" }
    { group:46, id:11, text: "Volume" }
    { group:46, id:12, text: "OK" }
    { group:47, id:0, text: "A distant city" }
    { group:47, id:1, text: "Our city!" }
    { group:47, id:2, text: "This trading route is not yet established" }
    { group:47, id:3, text: "Cost to open" }
    { group:47, id:4, text: "Buys" }
    { group:47, id:5, text: "Sells" }
    { group:47, id:6, text: " to open land trade route" }
    { group:47, id:7, text: " to open water trade route" }
    { group:47, id:8, text: "To Overseer of Commerce" }
    { group:47, id:9, text: "Click on a city to get information on it" }
    { group:47, id:10, text: "Bought" }
    { group:47, id:11, text: "Sold" }
    { group:47, id:12, text: "of" }
    { group:47, id:13, text: "An Egyptian city" }
    { group:47, id:14, text: "A captured city" }
    { group:47, id:15, text: "An enemy army, threatening a city of the Kingdom" }
    { group:47, id:16, text: "Your army, marching to relieve a city of the Kingdom" }
    { group:47, id:17, text: "Your army, returning to your city" }
    { group:47, id:18, text: "The site of a recent skirmish by invading barbarians " }
    { group:47, id:19, text: "The Pharaoh's city" }
    { group:48, id:0, text: "Tiny brush" }
    { group:48, id:1, text: "Small brush" }
    { group:48, id:2, text: "Medium brush" }
    { group:48, id:3, text: "Big brush" }
    { group:48, id:4, text: "Biggest brush" }
    { group:48, id:5, text: "Entry point" }
    { group:48, id:6, text: "Exit point" }
    { group:48, id:7, text: "Raise land" }
    { group:48, id:8, text: "Lower land" }
    { group:48, id:9, text: "Access ramp" }
    { group:48, id:10, text: "Invasion pt 1 (Land) " }
    { group:48, id:11, text: "Invasion pt 2 (Land) " }
    { group:48, id:12, text: "Invasion pt 3 (Land) " }
    { group:48, id:13, text: "Invasion pt 4 (Land) " }
    { group:48, id:14, text: "Invasion pt 5 (Land) " }
    { group:48, id:15, text: "Invasion pt 6 (Land) " }
    { group:48, id:16, text: "Invasion pt 7 (Land) " }
    { group:48, id:17, text: "Invasion pt 8 (Land) " }
    { group:48, id:18, text: "River entry" }
    { group:48, id:19, text: "River exit" }
    { group:48, id:20, text: "Native hut" }
    { group:48, id:21, text: "Native center" }
    { group:48, id:22, text: "Native field" }
    { group:48, id:23, text: "Fishing point 1" }
    { group:48, id:24, text: "Fishing point 2" }
    { group:48, id:25, text: "Fishing point 3" }
    { group:48, id:26, text: "Fishing point 4" }
    { group:48, id:27, text: "Fishing point 5" }
    { group:48, id:28, text: "Fishing point 6" }
    { group:48, id:29, text: "Fishing point 7" }
    { group:48, id:30, text: "Fishing point 8" }
    { group:48, id:31, text: "Killer spawn 1" }
    { group:48, id:32, text: "Killer spawn 2" }
    { group:48, id:33, text: "Killer spawn 3" }
    { group:48, id:34, text: "Killer spawn 4" }
    { group:48, id:35, text: "Water" }
    { group:48, id:36, text: "Flood plain" }
    { group:48, id:37, text: "Irrigation Ditch" }
    { group:48, id:38, text: "Marshland" }
    { group:48, id:39, text: "Prey spawn 1" }
    { group:48, id:40, text: "Prey spawn 2" }
    { group:48, id:41, text: "Prey spawn 3" }
    { group:48, id:42, text: "Prey spawn 4" }
    { group:48, id:43, text: "Ordinary rock" }
    { group:48, id:44, text: "Ore-bearing rock" }
    { group:48, id:45, text: "Ordinary rock" }
    { group:48, id:46, text: "Special rock" }
    { group:48, id:47, text: "Sand dunes" }
    { group:48, id:48, text: "Invasion pt 9 (Sea) " }
    { group:48, id:49, text: "Invasion pt 10 (Sea) " }
    { group:48, id:50, text: "Invasion pt 11 (Sea) " }
    { group:48, id:51, text: "Invasion pt 12 (Sea) " }
    { group:48, id:52, text: "Invasion pt 13 (Sea) " }
    { group:48, id:53, text: "Invasion pt 14 (Sea) " }
    { group:48, id:54, text: "Invasion pt 15 (Sea) " }
    { group:48, id:55, text: "Invasion pt 16 (Sea) " }
    { group:48, id:56, text: "Disembark pt 1" }
    { group:48, id:57, text: "Disembark pt 2" }
    { group:48, id:58, text: "Disembark pt 3" }
    { group:48, id:59, text: "Killer Type 1" }
    { group:48, id:60, text: "Killer Type 2" }
    { group:49, id:0, text: "Grass" }
    { group:49, id:1, text: "Trees" }
    { group:49, id:2, text: "Water" }
    { group:49, id:3, text: "Earthquake" }
    { group:49, id:4, text: "Scrub" }
    { group:49, id:5, text: "Rocks" }
    { group:49, id:6, text: "Meadow" }
    { group:49, id:7, text: "Plateau" }
    { group:49, id:8, text: "Brush size" }
    { group:49, id:9, text: "Access ramp" }
    { group:49, id:10, text: "Road" }
    { group:49, id:11, text: "Raise land" }
    { group:49, id:12, text: "Lower land" }
    { group:49, id:13, text: "Invasion point" }
    { group:49, id:14, text: "Migration point" }
    { group:49, id:15, text: "Entry point" }
    { group:49, id:16, text: "Exit point" }
    { group:49, id:17, text: "River point" }
    { group:49, id:18, text: "River IN" }
    { group:49, id:19, text: "River OUT" }
    { group:49, id:20, text: "Natives" }
    { group:49, id:21, text: "Native hut" }
    { group:49, id:22, text: "Native center" }
    { group:49, id:23, text: "Native field" }
    { group:49, id:24, text: "Fishing waters" }
    { group:49, id:25, text: "Killer point" }
    { group:49, id:26, text: "Floodplain" }
    { group:49, id:27, text: "Irrigation" }
    { group:49, id:28, text: "Prey" }
    { group:49, id:29, text: "Marshland" }
    { group:49, id:30, text: "Sand dunes" }
    { group:49, id:31, text: "Disembark point" }
    { group:49, id:32, text: "Killer Type" }
    { group:49, id:33, text: "Cliff" }
    { group:50, id:0, text: "Overseer of the Workers" }
    { group:50, id:1, text: "Food Production and Distribution" }
    { group:50, id:2, text: "Industry and Commerce" }
    { group:50, id:3, text: "Entertainment" }
    { group:50, id:4, text: "Religion" }
    { group:50, id:5, text: "Education" }
    { group:50, id:6, text: "Health and Sanitation" }
    { group:50, id:7, text: "Infrastructure" }
    { group:50, id:8, text: "Government" }
    { group:50, id:9, text: "Military" }
    { group:50, id:10, text: "Need" }
    { group:50, id:11, text: "Have" }
    { group:50, id:12, text: "Employed workforce" }
    { group:50, id:13, text: "Unemployed workforce (" }
    { group:50, id:14, text: "Wage/10" }
    { group:50, id:15, text: "Deben" }
    { group:50, id:16, text: "less than Kingdom rate of" }
    { group:50, id:17, text: "more than Kingdom rate of" }
    { group:50, id:18, text: "(Kingdom pays" }
    { group:50, id:19, text: "Projected payroll this year:" }
    { group:50, id:20, text: "Locked" }
    { group:50, id:21, text: "Priority" }
    { group:50, id:22, text: "Sector" }
    { group:50, id:23, text: "Need" }
    { group:50, id:24, text: "Have" }
    { group:50, id:25, text: "Priority level" }
    { group:50, id:26, text: "No priority" }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Army status" }
    { group:51, id:1, text: "Go to" }
    { group:51, id:2, text: "company" }
    { group:51, id:3, text: "Return" }
    { group:51, id:4, text: "to Fort" }
    { group:51, id:5, text: "Kingdom" }
    { group:51, id:6, text: "service" }
    { group:51, id:7, text: "in" }
    { group:51, id:8, text: "We have no reports of any threats to the city." }
    { group:51, id:9, text: "We are getting reports of enemies moving toward the city." }
    { group:51, id:10, text: "Our enemies are within sight of the city." }
    { group:51, id:11, text: "A battalion of Pharaoh's troops is at our gates!" }
    { group:51, id:12, text: "We have no requests for military assistance abroad." }
    { group:51, id:13, text: "Some of our troops are needed abroad." }
    { group:51, id:14, text: "Our battalion is marching to fight for the Kingdom." }
    { group:51, id:15, text: "Our battalion is marching back to our city." }
    { group:51, id:16, text: "You have no companies to command. You must first build a Fort to house a new company." }
    { group:51, id:17, text: "Company" }
    { group:51, id:18, text: "Experience" }
    { group:51, id:19, text: "Navy status" }
    { group:51, id:20, text: "warship" }
    { group:51, id:21, text: "to Wharf" }
    { group:51, id:22, text: "Hull" }
    { group:51, id:23, text: "Strength" }
    { group:51, id:24, text: "Crew status" }
    { group:51, id:25, text: "You have no warships to command. You must first build a Wharf for a new warship." }
    { group:51, id:26, text: "Some of our navy is needed elsewhere" }
    { group:51, id:27, text: "Our company is sailing to save an Egyptian city" }
    { group:51, id:28, text: "Our company is sailing back to our city" }
    { group:51, id:29, text: "abroad" }
    { group:51, id:30, text: "Dispatch" }
    { group:51, id:31, text: "now" }
    { group:51, id:32, text: " and " }
    { group:52, id:0, text: "Kingdom Rating" }
    { group:52, id:1, text: "Savings of" }
    { group:52, id:2, text: "Give to city" }
    { group:52, id:3, text: "Deben per month" }
    { group:52, id:4, text: "Village Elder's salary of" }
    { group:52, id:5, text: "Village Noble's salary of" }
    { group:52, id:6, text: "Royal Scholar's salary of" }
    { group:52, id:7, text: "Royal Scribe's salary of" }
    { group:52, id:8, text: "Royal Judge's salary of" }
    { group:52, id:9, text: "Royal Mayor's salary of" }
    { group:52, id:10, text: "Royal Governor's salary of" }
    { group:52, id:11, text: "Nomarch's salary of" }
    { group:52, id:12, text: "Chancellor's salary of" }
    { group:52, id:13, text: "Vizier's salary of" }
    { group:52, id:14, text: "Pharaoh's salary of" }
    { group:52, id:15, text: "Set salary level" }
    { group:52, id:16, text: "Give money to the city" }
    { group:52, id:17, text: "Donation is" }
    { group:52, id:18, text: "Give money" }
    { group:52, id:19, text: "All" }
    { group:52, id:20, text: "Current requests" }
    { group:52, id:21, text: "There are no requests outstanding at the moment." }
    { group:52, id:22, text: "Popular opinion would consign your remains to the jackals." }
    { group:52, id:23, text: "You are popular among jugglers, who use you in their comedies." }
    { group:52, id:24, text: "It is widely believed that your very presence causes malaria." }
    { group:52, id:25, text: "Apothecaries agree that your name is more bitter than any known herb." }
    { group:52, id:26, text: "Mothers use your name to frighten their small children." }
    { group:52, id:27, text: "Your name is never mentioned in polite company." }
    { group:52, id:28, text: "Your reputation is base, and your own family shuns you." }
    { group:52, id:29, text: "Your name is recognized, but ridiculed, throughout the Two Lands." }
    { group:52, id:30, text: "People who matter know your name and history, although they tend to belittle you." }
    { group:52, id:31, text: "Few people in the Kingdom know your record, and those who do are unimpressed." }
    { group:52, id:32, text: "Those few people who recognize your name have no opinion of you." }
    { group:52, id:33, text: "Your meager achievements aren't famous, but those who know you generally like you." }
    { group:52, id:34, text: "People who matter know of your history, and generally approve of what you've done." }
    { group:52, id:35, text: "Your name is widely recognized and applauded throughout the Two Lands." }
    { group:52, id:36, text: "Your reputation is good, and you are often approached by long-lost relatives." }
    { group:52, id:37, text: "The mention of your name lightens the hearts of those who hear it." }
    { group:52, id:38, text: "Mothers throughout the Kingdom name their children after you." }
    { group:52, id:39, text: "Many Egyptian cities contemplate holding festivals in your honor." }
    { group:52, id:40, text: "The most popular dance sweeping Egypt interprets the story of your life." }
    { group:52, id:41, text: "Musicians compose songs to you, and your name is carved on every public space." }
    { group:52, id:42, text: "All people of Egypt wish to serve you eternally in the Field of Reeds." }
    { group:52, id:43, text: "in Storage Yards" }
    { group:52, id:44, text: "in city treasuries" }
    { group:52, id:45, text: "people" }
    { group:52, id:46, text: "Weapons" }
    { group:52, id:47, text: "Click here to dispatch request" }
    { group:52, id:48, text: "Unable to fulfill request" }
    { group:52, id:49, text: "Send a gift" }
    { group:52, id:50, text: "Time since last gift" }
    { group:52, id:51, text: "A Babylonian tablet" }
    { group:52, id:52, text: "Persian carpets" }
    { group:52, id:53, text: "Ancient carvings" }
    { group:52, id:54, text: "African ivory" }
    { group:52, id:55, text: "A troupe of performing slaves" }
    { group:52, id:56, text: "Arabian stallions" }
    { group:52, id:57, text: "An educated slave" }
    { group:52, id:58, text: "Libyan bodyguards" }
    { group:52, id:59, text: "Cheetahs and giraffes" }
    { group:52, id:60, text: "A chest of sapphires" }
    { group:52, id:61, text: "A golden chariot" }
    { group:52, id:62, text: "A Lebanese cedar ship" }
    { group:52, id:63, text: "Modest:" }
    { group:52, id:64, text: "Generous:" }
    { group:52, id:65, text: "Lavish:" }
    { group:52, id:66, text: "Dispatch modest gift" }
    { group:52, id:67, text: "Dispatch generous gift" }
    { group:52, id:68, text: "Dispatch lavish gift" }
    { group:52, id:69, text: "Give to the people of Egypt" }
    { group:52, id:70, text: "You do not have enough personal savings to make a gift to Egypt. Try paying yourself a bigger salary!" }
    { group:52, id:71, text: "Warning: Paying yourself a salary greater than your current rank will not impress anyone." }
    { group:52, id:72, text: "Dispatch troops to protect" }
    { group:52, id:73, text: "A small force will attack in" }
    { group:52, id:74, text: "An average force will attack in" }
    { group:52, id:75, text: "A large force will attack in" }
    { group:52, id:76, text: "You are currently free to set your own salary level" }
    { group:52, id:77, text: "The Palace forbids you to draw a salary now, as you are continuing to govern of your own free choice." }
    { group:52, id:78, text: "You need to build a Mansion in order to draw a personal salary." }
    { group:52, id:79, text: "debens lost this year through theft." }
    { group:52, id:80, text: "Dispatch waterborne troops to" }
    { group:52, id:81, text: "Political Overseer for " }
    { group:53, id:0, text: "Ratings Overseer" }
    { group:53, id:1, text: "Culture" }
    { group:53, id:2, text: "Prosperity" }
    { group:53, id:3, text: "Monument" }
    { group:53, id:4, text: "Kingdom" }
    { group:53, id:5, text: "Needed" }
    { group:53, id:6, text: "Population:" }
    { group:53, id:7, text: "No target population" }
    { group:53, id:8, text: "Click on a rating number for information on it" }
    { group:53, id:9, text: "There are too few jugglers in the city. If possible, add more Juggler's stages to improve this rating." }
    { group:53, id:10, text: "There are too few musicians in the city. If possible, add more Musicians' stages to improve this rating." }
    { group:53, id:11, text: "There are too few dancers in the city. If possible, add more Dancers' stages to improve this rating." }
    { group:53, id:12, text: "There are too few Senet Houses in the city. If possible, build Senet Houses to improve this rating." }
    { group:53, id:13, text: "There are too few Zoos in the city. If possible, build Zoos to improve this rating." }
    { group:53, id:14, text: "There are too few places of worship in the city. Building more would improve this rating." }
    { group:53, id:15, text: "There are too few Scribal Schools working in the city. Building more would improve this rating." }
    { group:53, id:16, text: "There are too few Libraries working in the city. If possible, build more to improve this rating." }
    { group:53, id:17, text: "Not enough houses have access to a Dentist. Better access would improve this rating." }
    { group:53, id:18, text: "Not enough houses have access to a Physician. Better access would improve this rating." }
    { group:53, id:19, text: "Not enough houses have access to a Mortuary. Better access would improve this rating." }
    { group:53, id:20, text: "rating is rising." }
    { group:53, id:21, text: "rating is falling." }
    { group:53, id:22, text: "rating is stagnant." }
    { group:53, id:23, text: "The overall quality of your city's housing holds this rating back. Improve the housing in your city to raise it." }
    { group:53, id:24, text: "Last year your city lost money - this reduced the city's Prosperity." }
    { group:53, id:25, text: "High unemployment in your city retards your Prosperity rating." }
    { group:53, id:26, text: "Paying less than the Kingdom wage tarnishes your city's image as a prosperous one." }
    { group:53, id:27, text: "The high concentration of slum dwellers in your city lends it the appearance of a poor one." }
    { group:53, id:28, text: "Your inability to pay the annual tribute marks your city out as a failure." }
    { group:53, id:29, text: "unused 2041 - was lack of food variety affects Prosperity." }
    { group:53, id:30, text: "Labor shortages reduce Prosperity." }
    { group:53, id:31, text: "The city is more Prosperous when exports earn more than imports cost." }
    { group:53, id:32, text: "Your Kingdom rating is lower than it was last year. Pay your annual tribute, draw a modest salary, and fulfill requests from Pharaoh or other cities in the Kingdom." }
    { group:53, id:33, text: "The ridiculously high salary that you pay yourself indicates your complete lack of dedication to the Kingdom, and reduces this rating." }
    { group:53, id:34, text: "Your continued inability to provide annual tribute lowers your reputation throughout the Kingdom, and reduces this rating." }
    { group:53, id:35, text: "The way you have responded to certain events has greatly harmed your reputation throughout the Kingdom, and lowered this rating." }
    { group:53, id:36, text: "The salary that you pay yourself, far exceeding your rank, reduces your reputation in the Kingdom." }
    { group:53, id:37, text: "For the second year in a row, you have not paid tribute, and your Kingdom rating suffers for it." }
    { group:53, id:38, text: "Your response to certain events has harmed your standing in the Kingdom a little." }
    { group:53, id:39, text: "Your salary is too high for your current standing. Your Kingdom rating will rise if you reduce it somewhat." }
    { group:53, id:40, text: "You could not pay your tribute this year, which reduced your Kingdom rating. Keep some money in your treasury at year's end so you can make your annual payment." }
    { group:53, id:41, text: "Your salary is too high for your current standing. You would do well to reduce it." }
    { group:53, id:42, text: "Your slow progress toward meeting your goals in a timely fashion has reduced your Kingdom rating." }
    { group:53, id:43, text: "Your brazenness in paying yourself a salary higher than your rank entitles you to is frowned upon." }
    { group:53, id:44, text: "Your Kingdom rating is higher than it was last year. You can instruct your Political Overseer to give a gift to Egypt, and this rating will rise even more." }
    { group:53, id:45, text: "Your Kingdom rating is unchanged from last year. You can instruct your Political Overseer to give a gift to Egypt, and this rating will rise." }
    { group:53, id:46, text: "unused - was peace rating report1" }
    { group:53, id:47, text: "unused - was peace rating report2." }
    { group:53, id:48, text: "unused - was peace rating report3" }
    { group:53, id:49, text: "unused - was peace rating report4." }
    { group:53, id:50, text: "unused - was peace rating report5" }
    { group:53, id:51, text: "unused - was peace rating report6" }
    { group:53, id:52, text: "unused - was peace rating report7" }
    { group:53, id:53, text: "unused - was peace rating report8" }
    { group:53, id:54, text: "unused - was peace rating report9" }
    { group:53, id:55, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:56, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:57, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:58, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:59, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:60, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:61, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:62, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:63, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:64, text: "Remember to instruct the Overseer of Monuments to dispatch any necessary burial provisions. Also visit monument constructions site for a detailed progress report." }
    { group:53, id:65, text: "This city is more Cultured than any in Egypt!" }
    { group:53, id:66, text: "The amazing Prosperity of this city is the talk of Egypt!" }
    { group:53, id:67, text: "This city has the most magnificent Monuments in all Egypt!" }
    { group:53, id:68, text: "Your Kingdom is the best rated in all Egypt!" }
    { group:54, id:0, text: "Overseer of Commerce" }
    { group:54, id:1, text: "click on an item to trade, stockpile, or change industry status" }
    { group:54, id:2, text: "Show prices" }
    { group:54, id:3, text: "Stockpiling" }
    { group:54, id:4, text: "Not trading" }
    { group:54, id:5, text: "Importing to maintain" }
    { group:54, id:6, text: "Exporting when over" }
    { group:54, id:7, text: "No industries in the city" }
    { group:54, id:8, text: "working industry in the city" }
    { group:54, id:9, text: "working industries in the city" }
    { group:54, id:10, text: "industry in the city, currently shut down" }
    { group:54, id:11, text: "industries in the city, currently shut down" }
    { group:54, id:12, text: "working" }
    { group:54, id:13, text: "idle industries in the city" }
    { group:54, id:14, text: "idle industry in the city" }
    { group:54, id:15, text: "stored in the city's Storage Yards" }
    { group:54, id:16, text: "Industry is ON" }
    { group:54, id:17, text: "Industry is OFF" }
    { group:54, id:18, text: "Not trading" }
    { group:54, id:19, text: "Import to maintain" }
    { group:54, id:20, text: "Export when over" }
    { group:54, id:21, text: "Prices throughout Egypt" }
    { group:54, id:22, text: "Buyers pay" }
    { group:54, id:23, text: "Sellers receive" }
    { group:54, id:24, text: "There are no trade routes open for these goods" }
    { group:54, id:25, text: "These goods are available by import only" }
    { group:54, id:26, text: "Stockpiling resource" }
    { group:54, id:27, text: "Click here to turn off stockpiling" }
    { group:54, id:28, text: "Using and trading this resource" }
    { group:54, id:29, text: "Click here to stockpile it" }
    { group:54, id:30, text: "Go to the World Map" }
    { group:54, id:31, text: "Available for import" }
    { group:54, id:32, text: "Exportable" }
    { group:54, id:33, text: "Available for import or export" }
    { group:54, id:34, text: "Open trade route to import" }
    { group:54, id:35, text: "Open trade route to export" }
    { group:54, id:36, text: "Open trade routes to import/export" }
    { group:54, id:37, text: "Importing as needed" }
    { group:54, id:38, text: "Exporting surpluses" }
    { group:54, id:39, text: "Click to import" }
    { group:54, id:40, text: "Click to export" }
    { group:54, id:41, text: "No sellers for this resource" }
    { group:54, id:42, text: "No buyers for this resource" }
    { group:54, id:43, text: "Let Overseer set import level" }
    { group:54, id:44, text: "Let Overseer set export level" }
    { group:54, id:45, text: "multiple" }
    { group:54, id:46, text: "Return to trade status" }
    { group:54, id:47, text: "per weapon" }
    { group:54, id:48, text: "per chariot" }
    { group:54, id:49, text: "per block" }
    { group:54, id:50, text: "per 100 pieces" }
    { group:55, id:0, text: "Population - History" }
    { group:55, id:1, text: "Population - Census" }
    { group:55, id:2, text: "Population - Society" }
    { group:55, id:3, text: "History" }
    { group:55, id:4, text: "Census" }
    { group:55, id:5, text: "Society" }
    { group:55, id:6, text: "City population over time" }
    { group:55, id:7, text: "Population composition by age (in years)" }
    { group:55, id:8, text: "Population composition by income" }
    { group:55, id:9, text: "Hut dwellers" }
    { group:55, id:10, text: "Estate dwellers" }
    { group:55, id:11, text: "The Capital provides all the food for this city" }
    { group:55, id:12, text: " food for" }
    { group:55, id:13, text: " some food for the coming month" }
    { group:55, id:14, text: " no food for the coming month" }
    { group:55, id:15, text: " very little food for the coming month" }
    { group:55, id:16, text: "Current housing can hold" }
    { group:55, id:17, text: "more people" }
    { group:55, id:18, text: "newcomers arrived this month" }
    { group:55, id:19, text: "newcomer arrived this month" }
    { group:55, id:20, text: "Lack of housing vacancies limits immigration." }
    { group:55, id:21, text: "Low wages reduce immigration to our city." }
    { group:55, id:22, text: "Unemployment reduces your number of immigrants." }
    { group:55, id:23, text: "Lack of food in your Granaries reduces immigration." }
    { group:55, id:24, text: "High taxes keep some people away from our city." }
    { group:55, id:25, text: "Overall, people are coming, or wish to come, to our city." }
    { group:55, id:26, text: "Overall, people are leaving our city." }
    { group:55, id:27, text: "Lack of jobs drives people away." }
    { group:55, id:28, text: "People are going elsewhere in search of higher wages." }
    { group:55, id:29, text: "People are leaving the city due to your high tax rate." }
    { group:55, id:30, text: "Overall, your city population is static." }
    { group:55, id:31, text: "There is a balance between people coming to and leaving the city." }
    { group:55, id:32, text: "Poor housing, despite your city's wealth, discourages immigrants." }
    { group:55, id:33, text: "Nobody wants to live in our city." }
    { group:55, id:34, text: "We produce or import enough food for about  " }
    { group:55, id:35, text: "people." }
    { group:55, id:36, text: "We eat much more than we produce!" }
    { group:55, id:37, text: "We eat much more than we produce, so expect our city to shrink." }
    { group:55, id:38, text: "We produce far too little food.Our growing city will need even more." }
    { group:55, id:39, text: "We eat more than we produce." }
    { group:55, id:40, text: "We eat more than we produce, but our shrinking city will eat less." }
    { group:55, id:41, text: "We produce too little food.Our growing city will need even more." }
    { group:55, id:42, text: "Right now we eat a little more than we produce. " }
    { group:55, id:43, text: "We eat a bit more than we produce, so expect our city to shrink." }
    { group:55, id:44, text: "We eat a bit more than we produce.Our growing city will need more." }
    { group:55, id:45, text: "Right now we produce just enough to feed everyone." }
    { group:55, id:46, text: "We produce no extra food, and our shrinking city will eat even less. " }
    { group:55, id:47, text: "Now we produce just enough food, but our growing city will need more." }
    { group:55, id:48, text: "Right now we produce a little more than we eat." }
    { group:55, id:49, text: "We produce a little extra food.Our shrinking city will eat even less." }
    { group:55, id:50, text: "We produce a little surplus food, and our growing city will need it." }
    { group:55, id:51, text: "Right now we produce much more than we eat." }
    { group:55, id:52, text: "We produce a lot of extra food.Our shrinking city will need even less." }
    { group:55, id:53, text: "We produce a lot of extra food, but our growing city will need more." }
    { group:56, id:0, text: "Overseer of Public Health" }
    { group:56, id:1, text: "Free" }
    { group:56, id:2, text: "None" }
    { group:56, id:3, text: "Working" }
    { group:56, id:4, text: "Care for" }
    { group:56, id:5, text: "City coverage" }
    { group:56, id:6, text: "patients" }
    { group:56, id:7, text: "Certain areas of the city now need access to Physicians." }
    { group:56, id:8, text: "Some regions of the city want more Physicians." }
    { group:56, id:9, text: "Certain well-to-do areas of the city want Dentists. A local Dentist will enhance the stature of the neighborhood." }
    { group:56, id:10, text: "More areas of the city now require Dentists. As your city grows wealthier, more and more residents can afford new ivory teeth." }
    { group:56, id:11, text: "Some parts of the city demand access to an Apothecary." }
    { group:56, id:12, text: "More and more people want convenient medical facilities (Apothecaries)." }
    { group:56, id:13, text: "Development in some quarters is being held back by poor citywide Mortuary coverage." }
    { group:56, id:14, text: "Citizens require more Mortuaries to properly prepare their dead for the afterlife." }
    { group:56, id:15, text: "No one is asking for health or sanitary facilities. As the city develops, though, people will expect access to healthcare, then Dentists, and then even more medical facilities!" }
    { group:56, id:16, text: "Your small settlement has yet to report any problems with health." }
    { group:56, id:17, text: "City health is appalling! Pestilence is certain in such shocking conditions." }
    { group:56, id:18, text: "City health is terrible! Disease is almost inevitable." }
    { group:56, id:19, text: "City health is bad. More health care workers might improve the situation." }
    { group:56, id:20, text: "City health is poor. Plenty of food and health facilities would improve it." }
    { group:56, id:21, text: "City health is below average. Make sure citizens have food, and access to health care providers." }
    { group:56, id:22, text: "City health is average. Foul influences are under control, and people get enough to eat." }
    { group:56, id:23, text: "City health is good. Citizens are prone to only minor ailments." }
    { group:56, id:24, text: "City health is very good. Local caregivers are coping well." }
    { group:56, id:25, text: "City health is excellent, with no waiting times at all to visit local health facilities." }
    { group:56, id:26, text: "City health is almost perfect, with health facilities virtually empty." }
    { group:56, id:27, text: "City health is perfect. Your health care workers spend most of their days playing senet. " }
    { group:56, id:28, text: "City health is appalling." }
    { group:56, id:29, text: "City health is terrible." }
    { group:56, id:30, text: "City health is bad." }
    { group:56, id:31, text: "City health is poor." }
    { group:56, id:32, text: "City health is below average." }
    { group:56, id:33, text: "City health is average." }
    { group:56, id:34, text: "City health is good." }
    { group:56, id:35, text: "City health is very good." }
    { group:56, id:36, text: "City health is excellent." }
    { group:56, id:37, text: "City health is almost perfect." }
    { group:56, id:38, text: "City health is perfect." }
    { group:56, id:39, text: "Physicians" }
    { group:56, id:40, text: "Dentists" }
    { group:56, id:41, text: "Apothecaries" }
    { group:56, id:42, text: "Mortuaries" }
    { group:56, id:43, text: "Sparse" }
    { group:56, id:44, text: "Very poor" }
    { group:56, id:45, text: "Poor" }
    { group:56, id:46, text: "Below average" }
    { group:56, id:47, text: "Average" }
    { group:56, id:48, text: "Average" }
    { group:56, id:49, text: "Above average" }
    { group:56, id:50, text: "Good" }
    { group:56, id:51, text: "Very good" }
    { group:56, id:52, text: "Excellent" }
    { group:56, id:53, text: "Perfect" }
    { group:56, id:54, text: "No" }
    { group:56, id:55, text: "A few" }
    { group:56, id:56, text: "Some" }
    { group:56, id:57, text: "Several" }
    { group:56, id:58, text: "Many" }
    { group:56, id:59, text: "Apothecaries currently work to protect the city from malaria." }
    { group:56, id:60, text: "outbreaks have been reported this month." }
    { group:56, id:61, text: "varieties of food in your city." }
    { group:57, id:0, text: "Overseer of Learning" }
    { group:57, id:1, text: "Working" }
    { group:57, id:2, text: "Can educate" }
    { group:57, id:3, text: "City coverage" }
    { group:57, id:4, text: "children" }
    { group:57, id:5, text: "Young people" }
    { group:57, id:6, text: "people" }
    { group:57, id:7, text: "None" }
    { group:57, id:8, text: "Sparse" }
    { group:57, id:9, text: "Very poor" }
    { group:57, id:10, text: "Poor" }
    { group:57, id:11, text: "Below average" }
    { group:57, id:12, text: "Average" }
    { group:57, id:13, text: "Average" }
    { group:57, id:14, text: "Above average" }
    { group:57, id:15, text: "Good" }
    { group:57, id:16, text: "Very good" }
    { group:57, id:17, text: "Excellent" }
    { group:57, id:18, text: "Perfect" }
    { group:57, id:19, text: "Certain areas of the city now need Scribal School access. Poor education prevents some residents from improving their housing." }
    { group:57, id:20, text: "Some neighborhoods demand better Scribal School access. Some houses have access to city schools, but others do not, and this hinders their development." }
    { group:57, id:21, text: "Library access is now needed in certain areas of the city. People need access to literature if they are to work as scribes." }
    { group:57, id:22, text: "Some areas of the city want better Library access. Upper-class scribes do not appreciate having to walk so far to the Library." }
    { group:57, id:23, text: "Better Scribal School and Library access would enhance some areas of the city. People should not have to walk so far for learning!" }
    { group:57, id:24, text: "No one is asking for educational facilities yet. As the city grows in stature, though, people will expect Scribal Schools, followed later by demands for Libraries." }
    { group:57, id:25, text: "All homes that want them have educational facilities.  Scribal Schools and Libraries are numerous, and no one complains of overcrowding." }
    { group:57, id:26, text: "All homes that want them have educational facilities, but building more Scribal Schools would reduce classroom sizes and improve city Culture." }
    { group:57, id:27, text: "All homes that want them have educational facilities, but building more Libraries would reduce overcrowding and enhance city Culture." }
    { group:57, id:28, text: "Scribal schools " }
    { group:57, id:29, text: "Library" }
    { group:58, id:0, text: "Overseer of Diversions" }
    { group:58, id:1, text: "Working" }
    { group:58, id:2, text: "Shows" }
    { group:58, id:3, text: "Can entertain" }
    { group:58, id:4, text: "City coverage" }
    { group:58, id:5, text: "people" }
    { group:58, id:6, text: "N/A" }
    { group:58, id:7, text: "No one is seeking entertainment yet. As your city grows, though, people will want amusements like juggling, music and dancing." }
    { group:58, id:8, text: "There's currently enough diversion to satisfy everyone. As the city grows, though, people will ask for more and better forms of entertainment." }
    { group:58, id:9, text: "Some residents want more recreational facilities. More choices in diversions would motivate them to upgrade their homes." }
    { group:58, id:10, text: "Parts of the city grumble that they have no access to recreation. Building more entertainment venues would help these poorer areas develop." }
    { group:58, id:11, text: "Some people whine about inadequate entertainment in their neighborhoods. You may need to offer more variety, or perhaps build more performer schools to provide artists for venues that lack them." }
    { group:58, id:12, text: "Some Booths or Bandstands have empty stages.  More jugglers or musicians would satisfy neighborhoods that are complaining of poor entertainment." }
    { group:58, id:13, text: "Your Pavilions need more dancers.  A new Conservatory could boost local entertainment levels in parts of the city." }
    { group:58, id:14, text: "As long as the Senet House has both employees and beer, the senet master will circulate through the neighborhood to remind people that games are in progress." }
    { group:58, id:15, text: "since last festival" }
    { group:58, id:16, text: "Hold new festival" }
    { group:58, id:17, text: "Festivals" }
    { group:58, id:18, text: "The hardiest revellers have not slept off the last festival yet." }
    { group:58, id:19, text: "People still smile when they remember your last festival." }
    { group:58, id:20, text: "The memory of the earlier festival is fading from people's minds." }
    { group:58, id:21, text: "People cannot remember the last festival to be held in the city." }
    { group:58, id:22, text: "Citizens grumble at the lack of festivals held in your city." }
    { group:58, id:23, text: "Your people cannot bear the prospect of another year without a festival." }
    { group:58, id:24, text: "Depressed residents doubt that they will live to see another festival." }
    { group:58, id:30, text: "costs" }
    { group:58, id:31, text: "Common festival" }
    { group:58, id:32, text: "Lavish festival" }
    { group:58, id:33, text: "Grand festival" }
    { group:58, id:34, text: "Preparing festival for " }
    { group:58, id:35, text: "None" }
    { group:58, id:36, text: "Sparse" }
    { group:58, id:37, text: "Very poor" }
    { group:58, id:38, text: "Poor" }
    { group:58, id:39, text: "Below average" }
    { group:58, id:40, text: "Average" }
    { group:58, id:41, text: "Average" }
    { group:58, id:42, text: "Above average" }
    { group:58, id:43, text: "Good" }
    { group:58, id:44, text: "Very good" }
    { group:58, id:45, text: "Excellent" }
    { group:58, id:46, text: "Perfect" }
    { group:58, id:47, text: "Juggler's stages" }
    { group:58, id:48, text: "Musicians' stages" }
    { group:58, id:49, text: "Dancers' stages" }
    { group:58, id:50, text: "Senet Houses " }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Order a festival" }
    { group:58, id:53, text: "Festival order for" }
    { group:58, id:54, text: "next month" }
    { group:58, id:55, text: "Stages" }
    { group:58, id:56, text: "Zoos" }
    { group:59, id:0, text: "Overseer of the Temples" }
    { group:59, id:1, text: "Temples" }
    { group:59, id:2, text: "Complexes" }
    { group:59, id:3, text: "Appeasement" }
    { group:59, id:4, text: "N/A" }
    { group:59, id:5, text: "Temple" }
    { group:59, id:6, text: "Months" }
    { group:59, id:7, text: "Festival" }
    { group:59, id:8, text: "since" }
    { group:59, id:9, text: "Residents are beginning to feel spiritual needs.  The absence of nearby places of worship holds back city development." }
    { group:59, id:10, text: "More and more people fear that, without at least one place of worship in their neighborhoods, the gods will feel spurned." }
    { group:59, id:11, text: "More sophisticated residents want access to another religion close to home. Lack of religious diversity limits city development in certain areas." }
    { group:59, id:12, text: "Discerning citizens say that their neighborhoods would attract a better class of scribe if they had easy access to a third religion." }
    { group:59, id:13, text: "So far, people are too preoccupied with physical needs to think about religion. As your city grows, though, they will want easy access to a variety of Temples." }
    { group:59, id:14, text: "Everyone's particular religious beliefs are served, and the priests report that the gods are satisfied with the city's spirituality." }
    { group:59, id:15, text: "Osiris' displeasure is dangerous. He can destroy your crops and empty your Granaries, or even withhold the Inundation." }
    { group:59, id:16, text: "When mighty Ra, father to Pharaoh, grows displeased, he will make your city's neighbors share his feeling. Ra's anger endangers harmony with the Kingdom.  " }
    { group:59, id:17, text: "Ptah, whose beneficence your manufacturers require, grows unhappy. Regain his favor, or brace your workers for the loss of whole industries and products." }
    { group:59, id:18, text: "The bravest soldiers tremble before the wrath of Seth. Repair the god's opinion of your city quickly, or watch your battalion be swept away!" }
    { group:59, id:19, text: "When kind Bast becomes upset, people are not safe in their own homes. Placate the goddess swiftly, or destruction and pestilence will follow!" }
    { group:59, id:20, text: "Enraged" }
    { group:59, id:21, text: "Furious" }
    { group:59, id:22, text: "Angry" }
    { group:59, id:23, text: "Resentful" }
    { group:59, id:24, text: "Displeased" }
    { group:59, id:25, text: "Apathetic" }
    { group:59, id:26, text: "Amiable" }
    { group:59, id:27, text: "Congenial" }
    { group:59, id:28, text: "Sympathetic" }
    { group:59, id:29, text: "Approving" }
    { group:59, id:30, text: "Benevolent" }
    { group:59, id:31, text: "unused - was god toggle" }
    { group:59, id:32, text: "Osiris is the god of the Nile flood, and all life which springs from the underworld. With his benevolence, your city may receive the blessing of a bountiful annual Inundation, bringing life-giving fertile soil to your fields.  He can also improve the yield at harvest time in other ways. An Altar of Sebek - god of fertility - means that priests of Osiris can help your citizens stretch their food and other supplies a little farther, while an Oracle of Min - god of regeneration - infuses the wildlife in and around your city with greater vitality. His Oracle makes animal herds and fish colonies more resilient, and even accelerates the regrowth of some plants. " }
    { group:59, id:33, text: "As god of the Kingdom, Ra facilitates trade and travel throughout the known world, and can even help to bolster your reputation throughout Egypt. An Altar of Ma'at - goddess of justice - helps prevent crime in your city, while an Oracle of  Horus - god of the Pharaoh - makes your employees more willing to attend to their daily labors. In the name of Pharaoh, they'll be inspired to work for the greater good of Egypt." }
    { group:59, id:34, text: "Ptah is the patron god of craftsmen, and helps many of them finish their tasks more quickly. An Altar of Amon - god of the Sun - improves your city's ability to build monuments, while an Oracle of Thoth - god of wisdom and learning - can facilitate the education of your people." }
    { group:59, id:35, text: "When Seth is appeased, your enemies are his enemies. He can help your greenest soldiers fight like seasoned veterans, and even strike down your enemies by his own hand. So powerful is he that his influence even extends to battles fought far afield. Of course, if Seth is not appeased, your city may experience the full might of his destructive powers first hand." }
    { group:59, id:36, text: "As goddess of the home, Bast can improve the quality of life in your city, and can allow your citizens to enjoy a much higher standard of living than might otherwise be the case. So great is her power that she can even help keep the other gods happy. Of course, if she is unappeased, then your city will know true misery and suffering. An Altar of Isis - goddess of healing - can help ensure that your citizens remain in good health, and even assist them if they do get sick, while an Oracle of Hathor - goddess of joy, love and festivity - can help keep your people a little happier in spite of whatever problems they might have.    " }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Priestess" }
    { group:60, id:0, text: "Overseer of the Treasury" }
    { group:60, id:1, text: "Tax rate of" }
    { group:60, id:2, text: "City treasury has assets of" }
    { group:60, id:3, text: "City has a debt of" }
    { group:60, id:4, text: "yields an estimated" }
    { group:60, id:5, text: "of population registered for tax" }
    { group:60, id:6, text: "Last year" }
    { group:60, id:7, text: "So far this year" }
    { group:60, id:8, text: "Taxes in" }
    { group:60, id:9, text: "Exports earn" }
    { group:60, id:10, text: "Income" }
    { group:60, id:11, text: "Imports cost" }
    { group:60, id:12, text: "Wages" }
    { group:60, id:13, text: "Construction" }
    { group:60, id:14, text: "Interest at" }
    { group:60, id:15, text: "Personal salary" }
    { group:60, id:16, text: "Theft" }
    { group:60, id:17, text: "Expenses" }
    { group:60, id:18, text: "Net in/out flow" }
    { group:60, id:19, text: "Balance" }
    { group:60, id:20, text: "Gifts" }
    { group:60, id:21, text: "Tribute" }
    { group:60, id:22, text: "Requests and Festivals" }
    { group:60, id:23, text: "uncollected this year" }
    { group:60, id:24, text: "Mined Gold" }
    { group:61, id:0, text: "Chief Overseer" }
    { group:61, id:1, text: "City Sentiment" }
    { group:61, id:2, text: "Migration" }
    { group:61, id:3, text: "Employment" }
    { group:61, id:4, text: "Food Stocks" }
    { group:61, id:5, text: "Food Production" }
    { group:61, id:6, text: "Health" }
    { group:61, id:7, text: "Religion" }
    { group:61, id:8, text: "Finances" }
    { group:61, id:9, text: "Crime" }
    { group:61, id:10, text: "Military" }
    { group:61, id:11, text: "Kingdom" }
    { group:61, id:12, text: "Nilometer" }
    { group:61, id:13, text: "We produce much more than we eat" }
    { group:61, id:14, text: "We produce a little more than we eat" }
    { group:61, id:15, text: "We produce just enough to feed everyone" }
    { group:61, id:16, text: "IMPORTANT: We eat a little more than we produce" }
    { group:61, id:17, text: "SERIOUS: We eat more than we produce" }
    { group:61, id:18, text: "URGENT: We eat much more than we produce" }
    { group:61, id:19, text: "UNUSED 2426" }
    { group:61, id:20, text: "You are universally loathed" }
    { group:61, id:21, text: "People are very angry at you" }
    { group:61, id:22, text: "People are angry with you" }
    { group:61, id:23, text: "People are very upset with you" }
    { group:61, id:24, text: "People are upset with you" }
    { group:61, id:25, text: "People are annoyed with you" }
    { group:61, id:26, text: "People are indifferent to you" }
    { group:61, id:27, text: "People are pleased with you." }
    { group:61, id:28, text: "People are very pleased with you." }
    { group:61, id:29, text: "People are extremely pleased with you." }
    { group:61, id:30, text: "People love you." }
    { group:61, id:31, text: "People idolize you as a god." }
    { group:61, id:32, text: "because of food shortages." }
    { group:61, id:33, text: "because of job shortages." }
    { group:61, id:34, text: "because of high taxes." }
    { group:61, id:35, text: "because wages are low." }
    { group:61, id:36, text: "because of so many slums. " }
    { group:61, id:37, text: "Low City Sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  The city's food shortage is the leading cause of unhappiness, but high taxes, low wages, social inequality and lack of jobs may also be lowering City Sentiment." }
    { group:61, id:38, text: "Low City Sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  The lack of jobs here upsets people more than anything else, but high taxes, low wages, social inequality and lack of food may also be lowering City Sentiment." }
    { group:61, id:39, text: "Low City Sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  The high tax rate is foremost on your citizens' minds, but low wages, social inequality and lack of food and jobs may also be dragging down City Sentiment." }
    { group:61, id:40, text: "Low City Sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  Their paltry wages (compared to what workers make elsewhere in Egypt) are their main complaint, but high taxes, social inequality and lack of food and jobs may also be lowering City Sentiment." }
    { group:61, id:41, text: "Low City Sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  Widespread social inequality angers people the most, but high taxes, low wages and lack of food and jobs may also be depressing City Sentiment." }
    { group:61, id:42, text: "Low city sentiment contributes to higher crime rates, prevents settlers from coming to your city, and can even cause your current citizens to pick up and leave.  Low wages, high taxes, social inequality and lack of food and jobs all contribute to low City Sentiment." }
    { group:61, id:43, text: "War frightens immigrants away!" }
    { group:61, id:44, text: "People are immigrating to the city" }
    { group:61, id:45, text: "Lack of housing prevents immigration" }
    { group:61, id:46, text: "Low wages prevent immigration" }
    { group:61, id:47, text: "Lack of jobs prevents immigration" }
    { group:61, id:48, text: "Lack of food prevents immigration" }
    { group:61, id:49, text: "High taxes prevent immigration" }
    { group:61, id:50, text: "The city's slum areas discourage immigration" }
    { group:61, id:51, text: "Poor City Sentiment prevents immigration" }
    { group:61, id:52, text: "Lack of vacant housing drives people away" }
    { group:61, id:53, text: "Low wages are making people leave the city" }
    { group:61, id:54, text: "Unemployment makes people abandon the city" }
    { group:61, id:55, text: "People who are leaving cite hunger as the reason" }
    { group:61, id:56, text: "Unfair or excessive taxation drives people away" }
    { group:61, id:57, text: "Having some slums is encouraging people to leave" }
    { group:61, id:58, text: "People are leaving because of poor City Sentiment" }
    { group:61, id:59, text: "Little change expected" }
    { group:61, id:60, text: "As long as there is vacant housing, and the residents of your city are happy with you, more people will come to settle in your city.  Create more housing areas to let your city grow and prosper." }
    { group:61, id:61, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city. Raise wages if you want to lure more people to the city." }
    { group:61, id:62, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city. Create some jobs by building more industries if you want to attract more people to the city." }
    { group:61, id:63, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city. Produce more food than you currently are, if you want to attract more people to the city." }
    { group:61, id:64, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city. Lower taxes would attract more people to the city." }
    { group:61, id:65, text: "Normally, you'll want to increase the population so your city can grow and prosper.  New settlers are attracted by vacant housing and higher City Sentiment." }
    { group:61, id:66, text: "Normally, you'll want to increase the population so your city can grow and prosper.  Because there is vacant housing available, and your people are happy with their lives here, new settlers are flocking to the city." }
    { group:61, id:67, text: "When there is too much of a gap between the haves and the have-nots, no one will want to come to your city. Provide better services to your poorer neighborhoods to create more of a balance between the wealthy and those of more modest means." }
    { group:61, id:68, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city. Increase your City Sentiment in order to attract people to the city." }
    { group:61, id:69, text: "As long as sufficient housing is available, and the residents of your city are happy, more people will come to settle in your city (and your own citizens won't depart for greener pastures!). Build more housing in order for your city to grow and prosper." }
    { group:61, id:70, text: "As long as the residents of your city are happy with you, and sufficient housing is available, they'll remain in your city. Raise wages if you want to encourage people to stay." }
    { group:61, id:71, text: "As long as the residents of your city are happy with you, and sufficient housing is available, they'll remain in your city. Create more jobs by building some more industries if you want to encourage people to stay." }
    { group:61, id:72, text: "As long as the residents of your city are happy with you, and sufficient housing is available, they'll remain in your city. Given the size of your current population, you need to produce more food than you currently are, if you want to encourage people to stay." }
    { group:61, id:73, text: "As long as the residents of your city are happy with you, and sufficient housing is available, they'll remain in your city. Lower taxes will encourage people to stay." }
    { group:61, id:74, text: "When there is too much of a gap between the haves and the have-nots, people tend to seek opportunities elsewhere. Provide better services to your poorer neighborhoods, to create more of a balance between the wealthy and those of more modest means." }
    { group:61, id:75, text: "As long as the residents of your city are happy with you, and sufficient housing is available, more people will come to settle in your city (and your own citizens won't depart for greener pastures!). You need to increase your City Sentiment if you want people to stay here." }
    { group:61, id:76, text: "URGENT:   The city has unemployment of" }
    { group:61, id:77, text: "SERIOUS:  The city has unemployment of" }
    { group:61, id:78, text: "IMPORTANT:The city has unemployment of" }
    { group:61, id:79, text: "The city has unemployment of" }
    { group:61, id:80, text: "URGENT:   The city is short by" }
    { group:61, id:81, text: "SERIOUS:  The city is short by" }
    { group:61, id:82, text: "IMPORTANT:The city is short by" }
    { group:61, id:83, text: "The city is short by" }
    { group:61, id:84, text: "The city has no employment problems" }
    { group:61, id:85, text: "High unemployment will make your people seek jobs elsewhere. Build more industry to create some jobs." }
    { group:61, id:86, text: "High unemployment can make your people seek jobs elsewhere. You can create more jobs by building additional industries." }
    { group:61, id:87, text: "High unemployment can make your people seek jobs elsewhere. You can create more jobs by building additional industries." }
    { group:61, id:88, text: "This level of unemployment is tolerable, but if it gets too high your people may seek jobs elsewhere. You can create additional jobs by building more industries." }
    { group:61, id:89, text: "A severe labor shortage like this will bring your city to a grinding halt. Shut down any unneeded industries, or attract more workers with vacant housing and a happy population." }
    { group:61, id:90, text: "A severe labor shortage will prevent your citizens from carrying out their daily functions. Shut down any unneeded industries, or attract more workers with vacant housing and a happy population." }
    { group:61, id:91, text: "Without enough workers to go around, your citizens have a difficult time performing their daily tasks." }
    { group:61, id:92, text: "Labor shortages can result in a reduction of goods and services throughout the city. Make your city more efficient by shutting down any unneeded industries, or attracting more workers with vacant housing and a happy population." }
    { group:61, id:93, text: "High unemployment can cause your otherwise happy citizens to depart the city in search of jobs, while labor shortages can result in a reduction of goods and services throughout the city." }
    { group:61, id:94, text: "The Capital supplies all our needs" }
    { group:61, id:95, text: "URGENT:    Our food levels are low" }
    { group:61, id:96, text: "SERIOUS:   Our food levels are low" }
    { group:61, id:97, text: "IMPORTANT: Our food levels are low" }
    { group:61, id:98, text: "Supplies for" }
    { group:61, id:99, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). Make sure that your people are not eating more than they produce, and that you have adequate Granaries to store the harvested crops." }
    { group:61, id:100, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). Make sure that your people are not eating more than they produce, and that you have adequate Granaries to store the harvested crops." }
    { group:61, id:101, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). Make sure that your people are not eating more than they produce, and that you have adequate Granaries to store the harvested crops." }
    { group:61, id:102, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). Make sure that your people are not eating more than they produce, and that you have adequate Granaries to store the harvested crops." }
    { group:61, id:103, text: "URGENT: City health is appalling-plague is imminent." }
    { group:61, id:104, text: "URGENT: City health is terrible-plague is likely." }
    { group:61, id:105, text: "SERIOUS: City health is bad-there is risk of plague." }
    { group:61, id:106, text: "IMPORTANT: City health is poor - some plague risk." }
    { group:61, id:107, text: "City health is below average." }
    { group:61, id:108, text: "City health is average." }
    { group:61, id:109, text: "City health is good." }
    { group:61, id:110, text: "City health is very good." }
    { group:61, id:111, text: "City health is excellent." }
    { group:61, id:112, text: "City health is almost perfect." }
    { group:61, id:113, text: "City health is perfect." }
    { group:61, id:114, text: "With so many people in such poor health, widespread plague is almost certain to decimate the city. Build Physicians' offices and Mortuaries for the people who do not currently have access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:115, text: "With this many unhealthy people, widespread plague will probably strike soon, and could decimate the city. Build Physicians' offices and Mortuaries for the people who do not currently have access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:116, text: "With this many unhealthy people in the city, it's hard for apothecaries and physicians to keep up.  Your city runs the risk of widespread plague, which can devastate its population. Build Physicians' offices and Mortuaries for the people who do not currently have access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:117, text: "With this many unhealthy people in the city, it's hard for apothecaries and physicians to keep up.  Your city could be struck by a plague, which can devastate the population. Build Physicians' offices and Mortuaries for the people who do not currently have access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:118, text: "If the health of its population worsens, the city could find itself devastated by a plague.  Build Physicians' offices and Mortuaries for the unfortunates who currently lack access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:119, text: "If the health of its population worsens, the city could suffer a plague, which can decimate the population. Build Physicians' offices and Mortuaries for those unfortunates who lack access to the services provided by physicians and embalmers, and make sure your citizens have adequate supplies of food." }
    { group:61, id:120, text: "Good health is important for curbing malaria and disease, and especially for preventing plague throughout the city.  If the health of its population worsens, the city could find a plague devastating its population. Physicians and embalmers, provided by Physicians' offices and Mortuaries, help to keep the city healthy, as does a good supply of multiple types of food." }
    { group:61, id:121, text: "Good health is important for curbing malaria and disease, and especially for preventing plague throughout the city.  If the health of its population worsens, the city could find a plague devastating its population. Physicians and embalmers, provided by Physicians' offices and Mortuaries, help to keep the city healthy, as does a good supply of multiple types of food." }
    { group:61, id:122, text: "Good health is important for curbing malaria and disease, and especially for preventing plague throughout the city.  If the health of its population worsens, the city could find a plague devastating its population. Physicians and embalmers, provided by Physicians' offices and Mortuaries, help to keep the city healthy, as does a good supply of multiple types of food." }
    { group:61, id:123, text: "Good health is important for curbing malaria and disease, and especially for preventing plague throughout the city.  If the health of its population worsens, the city could find a plague devastating its population. Physicians and embalmers, provided by Physicians' offices and Mortuaries, help to keep the city healthy, as does a good supply of multiple types of food." }
    { group:61, id:124, text: "Good health is important for curbing malaria and disease, and especially for preventing plague throughout the city.  If the health of its population worsens, the city could find a plague devastating its population. Physicians and embalmers, provided by Physicians' offices and Mortuaries, help to keep the city healthy, as does a good supply of multiple types of food." }
    { group:61, id:125, text: "IMPORTANT: Several gods are not appeased" }
    { group:61, id:126, text: "SERIOUS: Several gods may strike us down" }
    { group:61, id:127, text: "IMPORTANT: Three gods are not appeased" }
    { group:61, id:128, text: "SERIOUS: Three gods are not appeased" }
    { group:61, id:129, text: "IMPORTANT: Two gods are not appeased" }
    { group:61, id:130, text: "SERIOUS: Two gods are not appeased" }
    { group:61, id:131, text: "IMPORTANT: One god is not appeased" }
    { group:61, id:132, text: "SERIOUS: One god is not appeased" }
    { group:61, id:133, text: "All gods are adequately appeased" }
    { group:61, id:134, text: "All gods are appeased. One is especially happy" }
    { group:61, id:135, text: "All gods are appeased. Two are especially happy" }
    { group:61, id:136, text: "All gods are appeased. Three are especially happy" }
    { group:61, id:137, text: "All gods are appeased. Several are especially happy" }
    { group:61, id:138, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:139, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:140, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:141, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:142, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:143, text: "Hostile gods can use their powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:144, text: "An angry god can use his powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:145, text: "An angry god can use his powers to devastate your city. To appease them, build Temples to them and hold festivals in their honor." }
    { group:61, id:146, text: "If any gods become hostile, they may use their powers to devastate your city.  " }
    { group:61, id:147, text: "Benevolent gods can use their powers to bless your city in various ways.  As your city grows, keep the gods appeased by dedicating Temples to them, and continue to hold festivals in their honor." }
    { group:61, id:148, text: "Benevolent gods can use their powers to bless your city in various ways.  As your city grows, keep the gods appeased by dedicating Temples to them, and continue to hold festivals in their honor." }
    { group:61, id:149, text: "Benevolent gods can use their powers to bless your city in various ways.  As your city grows, keep the gods appeased by dedicating Temples to them, and continue to hold festivals in their honor." }
    { group:61, id:150, text: "Benevolent gods can use their powers to bless your city in various ways.  As your city grows, keep the gods appeased by dedicating Temples to them, and continue to hold festivals in their honor." }
    { group:61, id:151, text: "SERIOUS: We don't collect most of the taxes owed!" }
    { group:61, id:152, text: "This year assets have risen by " }
    { group:61, id:153, text: "We are doing about as well as last year." }
    { group:61, id:154, text: "This year assets have fallen by " }
    { group:61, id:155, text: "You are passing up a substantial amount of money because your city does not have enough tax collectors working the streets. Build more Tax Collectors, especially in areas of higher-level housing, and use the tax overlay to make sure that everyone is visited by a tax collector." }
    { group:61, id:156, text: "If you run out of money, your treasury will borrow up to 5,000 debens. However, remaining in debt for long has very serious consequences. Taxes, exports and mining gold are the best ways to bring revenues to the city. Click 'Help' on the menu bar and choose 'Debt' to learn more." }
    { group:61, id:157, text: "If you run out of money, your treasury will borrow up to 5,000 debens. However, remaining in debt for long has very serious consequences. Taxes, exports and mining gold are the best ways to bring revenues to the city. Click 'Help' on the menu bar and choose 'Debt' to learn more." }
    { group:61, id:158, text: "If you keep losing money, you'll have to tap your line of credit. The city's treasury can borrow up to 5,000 debens, but remaining in debt for very long has serious consequences. Taxes, exports and mining gold are the best ways to bring revenues to the city. Click 'Help' on the menu bar and choose 'Debt' to learn more." }
    { group:61, id:159, text: "URGENT: Many recent thefts," }
    { group:61, id:160, text: "SERIOUS: Several recent thefts," }
    { group:61, id:161, text: "IMPORTANT: Some recent thefts," }
    { group:61, id:162, text: "Very few thefts." }
    { group:61, id:163, text: "No thefts reported" }
    { group:61, id:164, text: "db stolen." }
    { group:61, id:165, text: "This much theft can seriously drain your city's treasury, or even your own family savings! An adequate number of Courthouses and Police Stations helps prevent crime, and constables subdue any thieves they encounter. Keeping your people happy is the best way to deter crime in the first place." }
    { group:61, id:166, text: "Frequent thefts can drain your city's treasury, or even your own family savings! Adequate Courthouses and Police Stations help prevent crime, and constables will subdue any thieves they encounter. Of course, keeping your people happy is the best way to deter crime in the first place." }
    { group:61, id:167, text: "Frequent thefts can weaken your city's finances, and even your own family's savings!  Adequate Courthouses and Police Stations help prevent crime, and constables will subdue any thieves they encounter. Of course, keeping your people happy is the best way to deter crime in the first place." }
    { group:61, id:168, text: "Frequent thefts can weaken your city's finances, and even your own family's savings!  Adequate Courthouses and Police Stations help prevent crime, and constables will subdue any thieves they encounter. Of course, keeping your people happy is the best way to deter crime in the first place." }
    { group:61, id:169, text: "Theft can harm your city's finances, and even your family savings! An adequate number of Courthouses and Police Stations helps prevent crime, and constables will subdue any thieves they encounter. Of course, keeping your people happy is the best way to ensure that they don't turn to crime in the first place." }
    { group:61, id:170, text: "You have no companies to command" }
    { group:61, id:171, text: "We have no reported threats" }
    { group:61, id:172, text: "Enemies are closing on the city" }
    { group:61, id:173, text: "Enemies are attacking the city" }
    { group:61, id:174, text: "Enemy troops at our gates" }
    { group:61, id:175, text: "Our troops are needed elsewhere" }
    { group:61, id:176, text: "We have troops elsewhere" }
    { group:61, id:177, text: "There are no military forces at our disposal. Currently there is no need, as all is safe." }
    { group:61, id:178, text: "If enemies were advancing toward our city, you would surely receive a message.  Enemy armies also appear on the World Map, so you can watch them advance, and hopefully have the city ready when they arrive." }
    { group:61, id:179, text: "An enemy army is advancing to attack the city! It can be difficult or impossible to construct buildings while under attack, so prepare your defenses by building Walls, Towers, Gatehouses and Forts now, while you still can.  " }
    { group:61, id:180, text: "It's always best to be prepared for attacks, rather than try to conscript troops at the last minute. Hopefully we have adequate defenses to protect the city." }
    { group:61, id:181, text: "It's always best to be prepared for attacks, rather than try to conscript troops at the last minute. Hopefully we have adequate defenses to protect the city." }
    { group:61, id:182, text: "We have received a request for troops from a fellow Egyptian commander. It is usually best to honor such requests, if you want to remain on good terms with the rest of the Kingdom. Consult the Political Overseer, as well as the Overseer of the Military, to dispatch troops." }
    { group:61, id:183, text: "Some of our troops are serving Egypt in far-off military campaigns. It is generally good to support the Kingdom by sending troops to help out when needed, if you want to maintain your good name throughout Egypt." }
    { group:61, id:184, text: "There are many outstanding requests upon our city." }
    { group:61, id:185, text: "There are several outstanding requests upon our city." }
    { group:61, id:186, text: "There are some outstanding requests upon our city." }
    { group:61, id:187, text: "There are no outstanding requests upon our city." }
    { group:61, id:188, text: "Failure to fulfill requests from Pharaoh or your neighbors can have various ill effects. If you don't help out your fellow Egyptian cities in their time of need, they may succumb to poverty, or fall into the hands of our enemies. To remain on good terms with your countrymen, respond to requests like these willingly and promptly." }
    { group:61, id:189, text: "Failure to fulfill requests from Pharaoh or your neighbors can have various ill effects. If you don't help out your fellow Egyptian cities in their time of need, they may succumb to poverty, or fall into the hands of our enemies. To remain on good terms with your countrymen, respond to requests like these willingly and promptly." }
    { group:61, id:190, text: "If you don't aid your fellow Egyptian cities in their time of need, they may succumb to poverty, fall into the hands of their enemies, or suffer some other undesirable fate. This could adversely affect trade, prices, even your Kingdom status. To remain on good terms with your countrymen, it's best to respond to requests willingly and promptly." }
    { group:61, id:191, text: "To remain on good terms with your countrymen, respond willingly and promptly to any requests they may make in their time of need. If you fail they may succumb to poverty, fall into the hands of their enemies, or suffer some other undesirable fate. This could have detrimental effects on trade, prices, even your Kingdom status. " }
    { group:61, id:192, text: "The next flood will likely fail entirely" }
    { group:61, id:193, text: "The next flood is likely to be poor" }
    { group:61, id:194, text: "The next flood is likely to be mediocre" }
    { group:61, id:195, text: "The next flood should be good" }
    { group:61, id:196, text: "The next flood should be excellent" }
    { group:61, id:197, text: "The next flood should be perfect" }
    { group:61, id:198, text: "Priests interpreting the Nilometer warn that this year's flood could fail entirely, and the rich, fertile mud of the Nile won't renew your fields.  If your city depends on farming the flood plain for its food, this could put the very survival of your citizens in jeopardy. Worshipping Osiris, the god of the Nile flood, can help avoid this next year." }
    { group:61, id:199, text: "Seers foretell a poor flood this year. They fear that very little rich, fertile mud of the Nile will renew your fields. If your city depends on farming the flood plain for its food, this could put the very survival of your citizens in jeopardy. Appeasing Osiris, the god of the Nile flood, can help avoid this next year." }
    { group:61, id:200, text: "Omens portend a mediocre flood this year. If they are right, the Nile will deposit only some rich, fertile mud on your fields.  If your city depends on farming the flood plain for its food, this puts the very survival of your citizens in jeopardy. Increased worship of Osiris, the god of the Nile flood, will help ensure that this doesn't happen again next year." }
    { group:61, id:201, text: "If seers read the Nilometers right, the good flood expected this year will deposit the rich and fertile mud of the Nile onto your city's fields. Make sure that Osiris, the god of the Nile flood, is kept appeased, or he may decide to withhold this blessing next year." }
    { group:61, id:202, text: "If your city depends on farming the flood plain for its food, the amount of rich and fertile mud that omens indicate could be deposited on your fields by an excellent flood is a bounty not to be taken for granted.  Make sure that Osiris, the god of the Nile flood, is kept happy, so that he will bestow this blessing again." }
    { group:61, id:203, text: "If your city depends on farming the flood plain for its food, the abundant rich and fertile mud that priests hope will be deposited on your fields this year by the perfect flood is an immeasurable bounty not to be taken for granted. Pray to Osiris, the god of the Nile flood, that this might happen again in the future." }
    { group:61, id:204, text: "The flood is expected to come in early June" }
    { group:61, id:205, text: "The flood is expected to come in late June" }
    { group:61, id:206, text: "The flood is expected to come in early July" }
    { group:61, id:207, text: "The flood is expected to come in late July" }
    { group:61, id:208, text: "The flood is expected to come in early August" }
    { group:61, id:209, text: "The flood is expected to come in late August" }
    { group:61, id:210, text: "The flood is expected to come in early September" }
    { group:61, id:211, text: "The flood is expected to come in late September" }
    { group:61, id:212, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). To feed a population of this size, produce more food by building more farms, Hunting Lodges, Fishing Wharves or Cattle Ranches, or import some more food. You can also use irrigation to increase the output of the land you're currently farming." }
    { group:61, id:213, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). To feed a population of this size, build more farms, Hunting Lodges or Cattle Ranches, or import some more food." }
    { group:61, id:214, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). To feed a population of this size, build more farms, Hunting Lodges or Cattle Ranches, or import some more food." }
    { group:61, id:215, text: "If your citizens miss too many meals, they'll become unhealthy (or they'll leave the city in search of a better lifestyle). You have just about the right mix of farms, Cattle Ranches, Hunting Lodges and imported food to feed a population of this size." }
    { group:61, id:216, text: "If your citizens continue to eat well, they're likely to remain healthy (and won't leave the city in search of a better diet). You have a few more farms, Cattle Ranches and Hunting Lodges than you need to feed a population of this size." }
    { group:61, id:217, text: "If your citizens continue to eat well, they're likely to remain healthy (and won't leave the city in search of a better diet). You have far more farms, Cattle Ranches and Hunting Lodges than you need to feed a population this size. " }
    { group:61, id:218, text: "Click on any item for additional information and advice  " }
    { group:62, id:0, text: "Victory" }
    { group:62, id:1, text: "Defeat!" }
    { group:62, id:2, text: "Click to proceed" }
    { group:62, id:3, text: "Proceed" }
    { group:62, id:4, text: "Continue governing for 2 more years" }
    { group:62, id:5, text: "Continue for 5 more years" }
    { group:62, id:6, text: "New Game" }
    { group:62, id:7, text: "To the city" }
    { group:62, id:8, text: "Congratulations!" }
    { group:62, id:9, text: "unused 2636 (demo message) " }
    { group:62, id:10, text: "Objectives" }
    { group:62, id:11, text: "Population of" }
    { group:62, id:12, text: "Culture rating of" }
    { group:62, id:13, text: "Prosperity rating of" }
    { group:62, id:14, text: "Monument rating of" }
    { group:62, id:15, text: "Kingdom rating of" }
    { group:62, id:16, text: "What a dark end to so bright a beginning!  Your failure dishonors Egypt and your ancestors, and stains the names of descendants yet unborn.  You might have joined the elite who achieve immortality in the Field of Reeds.  Instead, you will pass unlamented into shadow.  Others will come forward to accept the challenge of Pharaoh... " }
    { group:62, id:17, text: "Build some Firehouses" }
    { group:62, id:18, text: "Build some Architect's Posts" }
    { group:62, id:19, text: "Build a Granary that hunters can fill with game" }
    { group:62, id:20, text: "Provide houses with food from a Bazaar" }
    { group:62, id:21, text: "Create an area of housing, and watch immigrants arrive" }
    { group:62, id:22, text: "Build Booths and Juggler Schools to raise city Culture" }
    { group:62, id:23, text: "Build some Temples and Shrines to Bast" }
    { group:62, id:24, text: "Mine some gold for the Palace's treasury" }
    { group:62, id:25, text: "Build Apothecaries and Physicians to improve health" }
    
    { group:62, id:32, text: "Build a mastaba, then review the Mission Briefing goals" }   
    { group:62, id:34, text: "Click the ankh symbol to review your mission goals" }
    { group:62, id:35, text: "Your place in history is assured. The Egyptian people declare you to be a god." }
    { group:62, id:36, text: "Accept deity status!" }
    { group:62, id:37, text: "Replay mission" }
    { group:62, id:38, text: "Out of Time!" }
    { group:62, id:39, text: "You have lost this mission. You may lower the difficulty level to gain additional time, or you may try the mission again." }
    { group:62, id:40, text: "Lower Difficulty" }
    { group:63, id:0, text: "Messages" }
    { group:63, id:1, text: "You currently have no messages to read. As your city grows, or if other cities ask you for goods, messages will be posted here" }
    { group:63, id:2, text: "Date" }
    { group:63, id:3, text: "Subject" }
    { group:63, id:4, text: "Left-click on a message to read it. Right-click on a message to delete it." }
    { group:63, id:5, text: "To" }
    { group:63, id:6, text: "Delete opened messages" }
    { group:64, id:0, text: "Nobody" }
    { group:64, id:1, text: "Immigrant" }
    { group:64, id:2, text: "Emigrant" }
    { group:64, id:3, text: "Homeless" }
    { group:64, id:4, text: "Delivery man" }
    { group:64, id:5, text: "Citizen" }
    { group:64, id:6, text: "Explosion" }
    { group:64, id:7, text: "Tax collector" }
    { group:64, id:8, text: "Architect" }
    { group:64, id:9, text: "Warehouseman" }
    { group:64, id:10, text: "Fire marshal" }
    { group:64, id:11, text: "Archer" }
    { group:64, id:12, text: "Charioteer" }
    { group:64, id:13, text: "Infantry" }
    { group:64, id:14, text: "Standard bearer" }
    { group:64, id:15, text: "Juggler" }
    { group:64, id:16, text: "Musican" }
    { group:64, id:17, text: "Dancer" }
    { group:64, id:18, text: "Senet player" }
    { group:64, id:19, text: "Caravan of merchants from" }
    { group:64, id:20, text: "Trade ship from" }
    { group:64, id:21, text: "Caravan of merchants from" }
    { group:64, id:22, text: "Protestor" }
    { group:64, id:23, text: "Criminal" }
    { group:64, id:24, text: "Tomb Robber" }
    { group:64, id:25, text: "Fishing boat" }
    { group:64, id:26, text: "Bazaar trader" }
    { group:64, id:27, text: "Priest" }
    { group:64, id:28, text: "Schoolchild" }
    { group:64, id:29, text: "Teacher" }
    { group:64, id:30, text: "Librarian" }
    { group:64, id:31, text: "Dentist" }
    { group:64, id:32, text: "Physician" }
    { group:64, id:33, text: "Herbalist" }
    { group:64, id:34, text: "Embalmer" }
    { group:64, id:35, text: "Worker" }
    { group:64, id:36, text: "Map flag" }
    { group:64, id:37, text: "Flotsam" }
    { group:64, id:38, text: "Docker" }
    { group:64, id:39, text: "Bazaar buyer" }
    { group:64, id:40, text: "Scribe" }
    { group:64, id:41, text: "Indigenous native (not used?)" }
    { group:64, id:42, text: "Sentry" }
    { group:64, id:43, text: "Enemy" }
    { group:64, id:44, text: "Enemy" }
    { group:64, id:45, text: "Enemy" }
    { group:64, id:46, text: "Enemy" }
    { group:64, id:47, text: "Enemy" }
    { group:64, id:48, text: "Enemy" }
    { group:64, id:49, text: "unused 2722" }
    { group:64, id:50, text: "unused 2723" }
    { group:64, id:51, text: "unused 2724" }
    { group:64, id:52, text: "unused 2725" }
    { group:64, id:53, text: "Enemy" }
    { group:64, id:54, text: "Enemy" }
    { group:64, id:55, text: "Enemy" }
    { group:64, id:56, text: "Enemy" }
    { group:64, id:57, text: "Enemy" }
    { group:64, id:58, text: "unused 2731" }
    { group:64, id:59, text: "Arrow" }
    { group:64, id:60, text: "Javelin" }
    { group:64, id:61, text: "Bolt" }
    { group:64, id:62, text: "Ballista" }
    { group:64, id:63, text: "Creature" }
    { group:64, id:64, text: "Missionary" }
    { group:64, id:65, text: "Seagulls" }
    { group:64, id:66, text: "Delivery boy" }
    { group:64, id:67, text: "Shipwreck" }
    { group:64, id:68, text: "Birds" }
    { group:64, id:69, text: "Ostrich" }
    { group:64, id:70, text: "Antelope" }
    { group:64, id:71, text: "Spear" }
    { group:64, id:72, text: "Chariot racer" }
    { group:64, id:73, text: "Hunter" }
    { group:64, id:74, text: "Hunter's spear" }
    { group:64, id:75, text: "Lumberjack" }
    { group:64, id:76, text: "Ferry boat" }
    { group:64, id:77, text: "Transport" }
    { group:64, id:78, text: "Warship" }
    { group:64, id:79, text: "Carpenter" }
    { group:64, id:80, text: "Bricklayer" }
    { group:64, id:81, text: "Stone mason" }
    { group:64, id:82, text: "Crocodile" }
    { group:64, id:83, text: "Hyena" }
    { group:64, id:84, text: "Hippo" }
    { group:64, id:85, text: "Laborer" }
    { group:64, id:86, text: "Sled" }
    { group:64, id:87, text: "Water carrier" }
    { group:64, id:88, text: "Constable" }
    { group:64, id:89, text: "Magistrate" }
    { group:64, id:90, text: "Reed gatherer" }
    { group:64, id:91, text: "Festival priest" }
    { group:64, id:92, text: "Enemy transport" }
    { group:64, id:93, text: "Enemy warship" }
    { group:64, id:94, text: "Funeral walker" }
    { group:64, id:95, text: "Fish" }
    { group:64, id:96, text: "Sled puller" }
    { group:64, id:97, text: "Showman" }
    { group:64, id:98, text: "Plagued citizen" }
    { group:64, id:99, text: "Bedouin infantry" }
    { group:64, id:100, text: "Egyptian warship" }
    { group:64, id:101, text: "Egyptian transport" }
    { group:64, id:102, text: "Asp" }
    { group:64, id:103, text: "Lion" }
    { group:64, id:104, text: "Scorpion" }
    { group:64, id:105, text: "Zookeeper" }
    { group:64, id:106, text: "Frog" }
    { group:64, id:107, text: "Locust" }
    { group:64, id:108, text: "Tomb artisan" }
    { group:64, id:109, text: "Mummy" }
    { group:65, id:0, text: "unused section 65 - was c3 walker names" }
    { group:66, id:0, text: "Overlay intelligent help." }
    { group:66, id:1, text: "This land has a groundwater supply for wells and Water Supplies" }
    { group:66, id:2, text: "This dwelling has no access to drinking water" }
    { group:66, id:3, text: "This dwelling has only basic drinking water access" }
    { group:66, id:4, text: "This house has no stocks of food" }
    { group:66, id:5, text: "This house will soon eat through its limited stocks of food" }
    { group:66, id:6, text: "This house has food stocks to last for at least the coming month" }
    { group:66, id:7, text: "This house has no problems in getting the food it requires to survive" }
    { group:66, id:8, text: "This house is receiving no deliveries of clean drinking water" }
    { group:66, id:9, text: "This house was recently passed by a water carrier. It will have clean drinking water for a long time" }
    { group:66, id:10, text: "This house has stocks of clean drinking water" }
    { group:66, id:11, text: "Unless a water carrier passes soon, this house will exhaust its stocks of clean drinking water" }
    { group:66, id:12, text: "This house has no access to any Temples or Shrines" }
    { group:66, id:13, text: "This house has access to a Temple to a single god only" }
    { group:66, id:14, text: "This house has access to Temples to 2 different gods" }
    { group:66, id:15, text: "This house has access to Temples to 3 different gods" }
    { group:66, id:16, text: "This house has access to Temples to 4 different gods" }
    { group:66, id:17, text: "This house has access to Temples to all the gods" }
    { group:66, id:18, text: "This house has access to a Shrine, and Temples to all the gods" }
    { group:66, id:19, text: "This house has no access to a Scribal School" }
    { group:66, id:20, text: "This house was recently passed by a scholar. It will have Scribal School access for a long time" }
    { group:66, id:21, text: "This house has Scribal School access" }
    { group:66, id:22, text: "Unless a scholar passes by soon, this house will lose Scribal School access" }
    { group:66, id:23, text: "This house has no access to a Library" }
    { group:66, id:24, text: "This house was recently passed by a librarian. It will have Library access for a long time" }
    { group:66, id:25, text: "This house has Library access" }
    { group:66, id:26, text: "Unless a librarian passes it soon, this house will lose Library access" }
    { group:66, id:27, text: "This house has no access to an Academy" }
    { group:66, id:28, text: "This house was recently passed by a teacher. It will have Academy access for a long time" }
    { group:66, id:29, text: "This house has Academy access" }
    { group:66, id:30, text: "Unless a teacher passes it soon, this house will lose Academy access" }
    { group:66, id:31, text: "This house has no access to a Dentist's office" }
    { group:66, id:32, text: "This house was recently passed by a dentist. It will have Dentist access for a long time" }
    { group:66, id:33, text: "This house has Dentist access" }
    { group:66, id:34, text: "Unless a dentist walks by soon, this house will lose Dentist office access" }
    { group:66, id:35, text: "This house has no access to an Apothecary" }
    { group:66, id:36, text: "This house was recently passed by an herbalist. It will have Apothecary access for a long time" }
    { group:66, id:37, text: "This house has Apothecary access" }
    { group:66, id:38, text: "Unless an herbalist passes it soon, this house will lose Apothecary access" }
    { group:66, id:39, text: "This house has no access to a Mortuary" }
    { group:66, id:40, text: "This house was recently passed by a embalmer. It will have Mortuary access for a long time" }
    { group:66, id:41, text: "This house has Mortuary access" }
    { group:66, id:42, text: "Unless a embalmer passes it soon, this house will lose Mortuary access" }
    { group:66, id:43, text: "This house is not registered for taxes, and so does not pay any tax" }
    { group:66, id:44, text: "No tax collected from this house so far this year." }
    { group:66, id:45, text: " deben collected so far this year." }
    { group:66, id:46, text: "This building has no likelihood of catching fire" }
    { group:66, id:47, text: "This building is a negligible fire risk" }
    { group:66, id:48, text: "This building has some risk of fire" }
    { group:66, id:49, text: "This building has a risk of fire" }
    { group:66, id:50, text: "This building is a fire trap" }
    { group:66, id:51, text: "This building could catch fire at any moment!" }
    { group:66, id:52, text: "This building is in perfect structural condition" }
    { group:66, id:53, text: "This building has a negligible risk of collapse" }
    { group:66, id:54, text: "This building has a low risk of collapse" }
    { group:66, id:55, text: "This building has some structural faults" }
    { group:66, id:56, text: "This building has many structural faults and cracks" }
    { group:66, id:57, text: "This building is unstable, and is likely to collapse soon" }
    { group:66, id:58, text: "This is a very law-abiding neighborhood, with no crimes reported at all" }
    { group:66, id:59, text: "There is only the occasional crime in this area" }
    { group:66, id:60, text: "This is a low-crime area, but a few residents have complained" }
    { group:66, id:61, text: "Several crimes were reported here recently, but on the whole, this neighborhood is reasonably secure" }
    { group:66, id:62, text: "This is a high-crime area. Residents are unhappy, and the streets are not safe to walk at night" }
    { group:66, id:63, text: "This whole area is a tinderbox of unrest! Crime is endemic, and anything might happen" }
    { group:66, id:64, text: "This dwelling has no access to any entertainment whatsoever" }
    { group:66, id:65, text: "This dwelling barely has access to any entertainment" }
    { group:66, id:66, text: "This dwelling has very limited access to entertainment venues" }
    { group:66, id:67, text: "This dwelling has limited access to entertainment venues" }
    { group:66, id:68, text: "This dwelling has some access to entertainment venues" }
    { group:66, id:69, text: "This dwelling has access to several entertainment venues" }
    { group:66, id:70, text: "This dwelling has reasonable access to entertainment venues" }
    { group:66, id:71, text: "This dwelling has good access to entertainment venues" }
    { group:66, id:72, text: "This dwelling has very good access to entertainment venues" }
    { group:66, id:73, text: "This dwelling has excellent access to entertainment venues" }
    { group:66, id:74, text: "This dwelling has access to all the entertainment it could ever desire" }
    { group:66, id:75, text: "This house has no access to a juggler" }
    { group:66, id:76, text: "This house was recently passed by a juggler. It will have juggler access for a long time" }
    { group:66, id:77, text: "This house has juggler access" }
    { group:66, id:78, text: "This house has not been passed by a juggler for a while. It will soon lose juggler access" }    
    { group:66, id:83, text: "This house has no access to a dance stage" }
    { group:66, id:84, text: "This house was recently passed by a dancer. It will have dance stage access for a long time" }
    { group:66, id:85, text: "This house has dance stage access" }
    { group:66, id:86, text: "This house has not been passed by a dancer for a while. It will soon lose dance access" }
    { group:66, id:87, text: "This house has no access to a Senet House" }
    { group:66, id:88, text: "This house was recently passed by a senet master. It will have Senet House access for a long time" }
    { group:66, id:89, text: "This house has Senet House access" }
    { group:66, id:90, text: "This house has not been passed by a senet master for a while. It will soon lose Senet House access" }
    { group:66, id:91, text: "OLD: No citizens want to live here" }
    { group:66, id:92, text: "OLD: Your citizens see no positive or negative factors associated with this area" }
    { group:66, id:93, text: "OLD: This land is a desirable area" }
    { group:66, id:94, text: "This building currently has no access to people to supply it with labor" }
    { group:66, id:95, text: "This building currently has very little access to people to supply it with labor" }
    { group:66, id:96, text: "This building currently has poor access to people to supply it with labor" }
    { group:66, id:97, text: "This building currently has some access to people to supply it with labor" }
    { group:66, id:98, text: "This building currently has good access to people to supply it with labor" }
    { group:66, id:99, text: "This building currently has excellent access to people to supply it with labor" }
    { group:66, id:100, text: "This house has no access to any Scribal Schools or Libraries" }
    { group:66, id:101, text: "This house has access to a Scribal School or to a Library" }
    { group:66, id:102, text: "This house has access to both a Scribal School and a Library" }
    { group:66, id:103, text: "This house has Scribal School and Library access. Its children are also in an Academy district" }
    { group:66, id:104, text: "This hut scavenges for its own food..." }
    { group:66, id:105, text: "This land is abundantly fertile. Crops grown here will be big and strong." }
    { group:66, id:106, text: "This land is fairly fertile. Crops grown here will tend to be quite healthy." }
    { group:66, id:107, text: "This land is moderately fertile. Crops grown here will not reach their full potential." }
    { group:66, id:108, text: "This land is not very fertile. Crops will barely grow here." }
    { group:66, id:109, text: "This land is infertile. No crops can grow here." }
    { group:66, id:110, text: " baskets of grain are stored in this building." }
    { group:66, id:111, text: " basket of grain is stored in this building." }
    { group:66, id:112, text: " jars of fruit are stored in this building." }
    { group:66, id:113, text: " jar of fruit is stored in this building." }
    { group:66, id:114, text: " jars of vegetables are stored in this building." }
    { group:66, id:115, text: " jar of vegetables is stored in this building." }
    { group:66, id:116, text: " slabs of meat are stored in this building." }
    { group:66, id:117, text: " slab of meat is stored in this building." }
    { group:66, id:118, text: " pieces of pottery are stored in this building." }
    { group:66, id:119, text: " piece of pottery is stored in this building." }
    { group:66, id:120, text: " pouches of jewelry(luxury goods) are stored in this building." }
    { group:66, id:121, text: " pouch of jewelry(luxury goods) is stored in this building." }
    { group:66, id:122, text: " rolls of linen are stored in this building." }
    { group:66, id:123, text: " roll of linen is stored in this building." }
    { group:66, id:124, text: " flasks of beer are stored in this building." }
    { group:66, id:125, text: " flask of beer is stored in this building." }
    { group:66, id:126, text: "This building does not store goods." }
    { group:66, id:127, text: "This building has no likelihood of disease." }
    { group:66, id:128, text: "This building is a negligible disease risk." }
    { group:66, id:129, text: "This building has some risk of disease." }
    { group:66, id:130, text: "This building has a risk of disease" }
    { group:66, id:131, text: "This building is disease ridden." }
    { group:66, id:132, text: "No Physician access." }
    { group:66, id:133, text: "This house hasn't been passed by a physician in a while." }
    { group:66, id:134, text: "This house has had a physician pass by." }
    { group:66, id:135, text: "This house has recently had a physician pass by." }
    { group:66, id:136, text: "This building has no likelihood of malaria." }
    { group:66, id:137, text: "This building is a negligible malaria risk." }
    { group:66, id:138, text: "This building has some risk of malaria." }
    { group:66, id:139, text: "This building has a risk of malaria" }
    { group:66, id:140, text: "This building will have malaria soon." }
    { group:66, id:141, text: "This house has the following problems:" }
    { group:66, id:142, text: "This industry has the following problems:" }
    { group:66, id:143, text: "Risk of collapse" }
    { group:66, id:144, text: "Risk of fire" }
    { group:66, id:145, text: "Risk of disease" }
    { group:66, id:146, text: "Vacant" }
    { group:66, id:147, text: "Risk of malaria" }
    { group:66, id:148, text: "Diseased" }
    { group:66, id:149, text: "Potential crime risk" }
    { group:66, id:150, text: "Will devolve soon" }
    { group:66, id:151, text: "Lacks raw materials" }
    { group:66, id:152, text: "No labor" }
    { group:66, id:153, text: "Partial labor" }
    { group:66, id:154, text: "Industry shut down" }
    { group:66, id:155, text: "Looking for laborers" }
    { group:66, id:156, text: "Infested with frogs" }
    { group:66, id:157, text: "No one lives in this dwelling" }
    { group:66, id:158, text: "This house has no access to a Courthouse" }
    { group:66, id:159, text: "This house was recently passed by a magistrate. It will have Courthouse access for a long time" }
    { group:66, id:160, text: "This house has Courthouse access" }
    { group:66, id:161, text: "This house has not been passed by a magistrate for a while. It will soon lose Courthouse access" }
    { group:66, id:162, text: "This is one of the least desirable places in town" }
    { group:66, id:163, text: "No one would prefer to live here, but there are worse places" }
    { group:66, id:164, text: "People have no strong feelings about this area's desirability" }
    { group:66, id:165, text: "This area is better than some, although not highly attractive" }
    { group:66, id:166, text: "Most people would find this a pleasant place to live" }
    { group:66, id:167, text: "This is among the most fashionable addresses in your city" }
    { group:66, id:168, text: "This house has no access to a Zoo" }
    { group:66, id:169, text: "This house was recently passed by a zookeeper. It will have Zoo access for a long time" }
    { group:66, id:170, text: "This house has Zoo access" }
    { group:66, id:171, text: "This house has not been passed by a zookeeper for a while. It will soon lose Zoo access" }
    { group:66, id:172, text: "This house is infested with frogs" }
    { group:67, id:0, text: "Allowed structures" }
    { group:67, id:1, text: "Raw materials" }
    { group:67, id:2, text: "Gold Mine" }
    { group:67, id:3, text: "Water Lift" }
    { group:67, id:4, text: "Irrigation Ditch" }
    { group:67, id:5, text: "Fishing Wharf" }
    { group:67, id:6, text: "Work Camp" }
    { group:67, id:7, text: "Granary" }
    { group:67, id:8, text: "Bazaar" }
    { group:67, id:9, text: "Storage Yard" }
    { group:67, id:10, text: "Dock" }
    { group:67, id:11, text: "Juggling" }
    { group:67, id:12, text: "Music" }
    { group:67, id:13, text: "Dancing" }
    { group:67, id:14, text: "Senet games" }
    { group:67, id:15, text: "Festival Square" }
    { group:67, id:16, text: "Scribal School" }
    { group:67, id:17, text: "Library" }
    { group:67, id:18, text: "Water Supply" }
    { group:67, id:19, text: "Dentist" }
    { group:67, id:20, text: "Apothecary" }
    { group:67, id:21, text: "Physician" }
    { group:67, id:22, text: "Mortuary" }
    { group:67, id:23, text: "Tax Collector" }
    { group:67, id:24, text: "Courthouse" }
    { group:67, id:25, text: "Palace" }
    { group:67, id:26, text: "Mansion" }
    { group:67, id:27, text: "Roadblock" }
    { group:67, id:28, text: "Bridge" }
    { group:67, id:29, text: "Ferry Landing" }
    { group:67, id:30, text: "Gardens" }
    { group:67, id:31, text: "Plaza" }
    { group:67, id:32, text: "Statues" }
    { group:67, id:33, text: "Wall" }
    { group:67, id:34, text: "Tower" }
    { group:67, id:35, text: "Gatehouse" }
    { group:67, id:36, text: "Recruiter" }
    { group:67, id:37, text: "Fort: Infantry" }
    { group:67, id:38, text: "Fort: Archers" }
    { group:67, id:39, text: "Fort: Charioteers" }
    { group:67, id:40, text: "Academy" }
    { group:67, id:41, text: "Weaponsmith" }
    { group:67, id:42, text: "Chariot Maker" }
    { group:67, id:43, text: "Warship Wharf" }
    { group:67, id:44, text: "Transport Wharf" }
    { group:67, id:45, text: "Zoo" }
    { group:68, id:0, text: "This is the text for mouse help" }
    { group:68, id:1, text: "Display the relevant help page for this panel" }
    { group:68, id:2, text: "Exit this panel" }
    { group:68, id:3, text: "Load this saved game" }
    { group:68, id:4, text: "Save the current game to this file" }
    { group:68, id:5, text: "Cancel this operation" }
    { group:68, id:6, text: "Scroll through saved games" }
    { group:68, id:7, text: "Click on a filename to select it" }
    { group:68, id:8, text: "mouse help free" }
    { group:68, id:9, text: "mouse help free" }
    { group:68, id:10, text: "Hide the Control Panel to see a wider playing area" }
    { group:68, id:11, text: "Select a city overlay report" }
    { group:68, id:12, text: "Display the full Control Panel" }
    { group:68, id:13, text: "Load this game" }
    { group:68, id:14, text: "Save the current game to this file" }
    { group:68, id:15, text: "Cancel this operation" }
    { group:68, id:16, text: "Scroll through missions" }
    { group:68, id:17, text: "Click on a filename to select it" }
    { group:68, id:18, text: "mouse help free" }
    { group:68, id:19, text: "mouse help free" }
    { group:68, id:20, text: "Build Housing" }
    { group:68, id:21, text: "Build Roads" }
    { group:68, id:22, text: "Clear Land" }
    { group:68, id:23, text: "Farming and Food Structures" }
    { group:68, id:24, text: "Industrial Structures" }
    { group:68, id:25, text: "Storage and Distribution Structures" }
    { group:68, id:26, text: "Entertainment Structures" }
    { group:68, id:27, text: "Religious Structures" }
    { group:68, id:28, text: "Education Structures" }
    { group:68, id:29, text: "Health and Sanitation Structures" }
    { group:68, id:30, text: "Municipal Structures" }
    { group:68, id:31, text: "Military Structures" }
    { group:68, id:32, text: "UNDO your last action (only available when icon is lit up)" }
    { group:68, id:33, text: "View messages" }
    { group:68, id:34, text: "Cycle through any recent trouble spots in the city" }
    { group:68, id:35, text: "Review your mission" }
    { group:68, id:36, text: "Click on this overview map to move to distant parts of your city" }
    { group:68, id:37, text: "mouse help free" }
    { group:68, id:38, text: "mouse help free" }
    { group:68, id:39, text: "mouse help free" }
    { group:68, id:40, text: "mouse help free" }
    { group:68, id:41, text: "Visit your overseers" }
    { group:68, id:42, text: "Go to the map of the world" }
    { group:68, id:43, text: "Review your mission" }
    { group:68, id:44, text: "Re-orient your view to Due North" }
    { group:68, id:45, text: "Rotate the view clockwise" }
    { group:68, id:46, text: "Rotate the view counter-clockwise" }
    { group:68, id:47, text: "mouse help free" }
    { group:68, id:48, text: "mouse help free" }
    { group:68, id:49, text: "mouse help free" }
    { group:68, id:50, text: "mouse help free" }
    { group:68, id:51, text: "Load, save, new game and exit" }
    { group:68, id:52, text: "Sound and speed options" }
    { group:68, id:53, text: "Access game help" }
    { group:68, id:54, text: "Go directly to specific overseer reports" }
    { group:68, id:55, text: "mouse help free" }
    { group:68, id:56, text: "mouse help free" }
    { group:68, id:57, text: "mouse help free" }
    { group:68, id:58, text: "mouse help free" }
    { group:68, id:59, text: "mouse help free" }
    { group:68, id:60, text: "mouse help free" }
    { group:68, id:61, text: "Current city funds" }
    { group:68, id:62, text: "Current city population" }
    { group:68, id:63, text: "The current date!" }
    { group:68, id:64, text: "mouse help free" }
    { group:68, id:65, text: "mouse help free" }
    { group:68, id:66, text: "mouse help free" }
    { group:68, id:67, text: "mouse help free" }
    { group:68, id:68, text: "mouse help free" }
    { group:68, id:69, text: "mouse help free" }
    { group:68, id:70, text: "Visit your Overseer of Commerce" }
    { group:68, id:71, text: "Visit your Overseer of the Workers" }
    { group:68, id:72, text: "Visit your Overseer of the Military" }
    { group:68, id:73, text: "Visit your Political Overseer" }
    { group:68, id:74, text: "Visit your Ratings Overseer" }
    { group:68, id:75, text: "Visit your Overseer of Commerce" }
    { group:68, id:76, text: "Visit your Overseer of the Granaries" }
    { group:68, id:77, text: "Visit your Overseer of Public Health" }
    { group:68, id:78, text: "Visit your Overseer of Learning" }
    { group:68, id:79, text: "Visit your Overseer of Diversions" }
    { group:68, id:80, text: "Visit your Overseer of the Temples" }
    { group:68, id:81, text: "Visit your Overseer of the Treasury" }
    { group:68, id:82, text: "Visit your Chief Overseer" }
    { group:68, id:83, text: "Visit your Overseer of Monuments" }
    { group:68, id:84, text: "Return to main city view" }
    { group:68, id:85, text: "mouse help free" }
    { group:68, id:86, text: "mouse help free" }
    { group:68, id:87, text: "mouse help free" }
    { group:68, id:88, text: "mouse help free" }
    { group:68, id:89, text: "mouse help free" }
    { group:68, id:90, text: "mouse help free" }
    { group:68, id:91, text: "mouse help free" }
    { group:68, id:92, text: "Click here to set a priority for this labor category" }
    { group:68, id:93, text: "Decree the annual wage for every 10 workers" }
    { group:68, id:94, text: "Click here to remove any priority set for this task" }
    { group:68, id:95, text: "Click on a number to set a priority level. All other task priorities will re-adjust accordingly" }
    { group:68, id:96, text: "Click here to donate money to the city" }
    { group:68, id:97, text: "Click here to set your personal salary" }
    { group:68, id:98, text: "Exit the salary screen" }
    { group:68, id:99, text: "Select this salary level" }
    { group:68, id:100, text: "Exit the donation screen" }
    { group:68, id:101, text: "Donate this money to the city from your family's savings" }
    { group:68, id:102, text: "Set the amount to donate." }
    { group:68, id:103, text: "Adjust the exact amount you wish to donate" }
    { group:68, id:104, text: "Click here for advice about your Culture rating" }
    { group:68, id:105, text: "Click here for advice about your Prosperity rating" }
    { group:68, id:106, text: "Click here for advice about your Monument rating" }
    { group:68, id:107, text: "Click here for advice about your Kingdom rating" }
    { group:68, id:108, text: "Shows the import/export prices of all goods" }
    { group:68, id:109, text: "Click here for industry status" }
    { group:68, id:110, text: "Set the quantity of this good you wish to keep before any is exported" }
    { group:68, id:111, text: "Turn production on or off for this activity throughout the city" }
    { group:68, id:112, text: "Adjust the trade status of this item" }
    { group:68, id:113, text: "Select this graph" }
    { group:68, id:114, text: "Festival information" }
    { group:68, id:115, text: "Arrange a festival in honor of this god" }
    { group:68, id:116, text: "Do not organize festival" }
    { group:68, id:117, text: "Dedicate a festival to Osiris" }
    { group:68, id:118, text: "Dedicate a festival to Ra" }
    { group:68, id:119, text: "Dedicate a festival to Ptah" }
    { group:68, id:120, text: "Dedicate a festival to Seth" }
    { group:68, id:121, text: "Dedicate a festival to Bast" }
    { group:68, id:122, text: "Adjust city tax rate" }
    { group:68, id:123, text: "Click here to talk to this person" }
    { group:68, id:124, text: "Advanced information about this house" }
    { group:68, id:125, text: "Scroll through stored messages" }
    { group:68, id:126, text: "Previously read message. @L Left click on this message to read it. @L Right click on it to delete it" }
    { group:68, id:127, text: "Unread message. @L Left click on this message to read it. @L Right click on it to delete it" }
    { group:68, id:128, text: "Takes you back to the previous help screen" }
    { group:68, id:129, text: "Exit Pharaoh help" }
    { group:68, id:130, text: "Scroll through help on this topic" }
    { group:68, id:131, text: "Delete this message" }
    { group:68, id:132, text: "Click here to go to this trouble spot" }
    { group:68, id:133, text: "Send gift for Egypt" }
    { group:68, id:134, text: "Click here to change the company's formation" }
    { group:68, id:135, text: "Unemployment" }
    { group:68, id:136, text: "Culture rating" }
    { group:68, id:137, text: "Prosperity rating" }
    { group:68, id:138, text: "Monument rating" }
    { group:68, id:139, text: "Kingdom rating" }
    { group:68, id:140, text: "Click here to give the transport orders" }
    { group:68, id:141, text: "Click here to give the warship orders" }
    { group:68, id:142, text: "Tax rate" }
    { group:68, id:143, text: "View army status" }
    { group:68, id:144, text: "View navy status" }
    { group:68, id:145, text: "Go to Kingdom map" }
    { group:68, id:146, text: "Set mission criteria" }
    { group:68, id:147, text: "Plain land" }
    { group:68, id:148, text: "Trees" }
    { group:68, id:149, text: "Water and wetlands" }
    { group:68, id:150, text: "Meadow" }
    { group:68, id:151, text: "Road" }
    { group:68, id:152, text: "Rocks and dunes" }
    { group:68, id:153, text: "River points" }
    { group:68, id:154, text: "Invasion points" }
    { group:68, id:155, text: "People points" }
    { group:68, id:156, text: "Animal points" }
    { group:68, id:157, text: "Brushes" }
    { group:68, id:158, text: "Add city, region or graphic" }
    { group:68, id:159, text: "Edit city, region or graphic" }
    { group:68, id:160, text: "Delete city, region or graphic" }
    { group:68, id:161, text: "View main menu" }
    { group:68, id:162, text: "Add trade or invasion route" }
    { group:68, id:163, text: "Edit trade or invasion route" }
    { group:68, id:164, text: "Reset to default map" }
    { group:68, id:165, text: "Return to region view" }
    { group:68, id:166, text: "Adjust prices of imports and exports" }
    { group:68, id:167, text: "Adjust rank, funding, starting date and current pharaoh" }
    { group:68, id:168, text: "Cycle through climate options" }
    { group:68, id:169, text: "Plan events" }
    { group:68, id:170, text: "Choose an enemy" }
    { group:68, id:171, text: "Define gods" }
    { group:68, id:172, text: "Set available buildings" }
    { group:68, id:173, text: "Set ratings requirements and choose monuments" }
    { group:68, id:174, text: "Determine length and quality of flood" }
    { group:68, id:175, text: "Rotate view" }
    { group:68, id:176, text: "Change graphic" }
    { group:68, id:177, text: "Killer Types" }
    { group:68, id:178, text: "Monument Era" }
    { group:69, id:0, text: "needed)" }
    { group:69, id:1, text: "Efficiency" }
    { group:69, id:2, text: "No risk of collapse" }
    { group:69, id:3, text: "Very low risk of collapse" }
    { group:69, id:4, text: "Low risk of collapse" }
    { group:69, id:5, text: "Some risk of collapse" }
    { group:69, id:6, text: "High risk of collapse" }
    { group:69, id:7, text: "Very high risk of collapse" }
    { group:69, id:8, text: "Collapse imminent" }
    { group:69, id:9, text: "No fire risk" }
    { group:69, id:10, text: "Very low fire risk" }
    { group:69, id:11, text: "Low fire risk" }
    { group:69, id:12, text: "Some fire risk" }
    { group:69, id:13, text: "High fire risk" }
    { group:69, id:14, text: "Very high fire risk" }
    { group:69, id:15, text: "Extreme fire risk" }
    { group:69, id:16, text: "No people in the city!" }
    { group:69, id:17, text: "No workers live nearby" }
    { group:69, id:18, text: "The Overseer of Workers could shift some labor" }
    { group:69, id:19, text: "The Overseer of Workers could shift some labor" }
    { group:69, id:20, text: "WARNING: Poor access to workers" }
    { group:69, id:21, text: "Barely working. Our sector desperately needs more workers" }
    { group:69, id:22, text: "Working poorly. Our sector needs a lot more workers" }
    { group:69, id:23, text: "Working well, but our sector could really use more workers" }
    { group:69, id:24, text: "Working at reduced capacity. Hardly any workers arrived recently" }
    { group:69, id:25, text: "WARNING: This building is not adjacent to a road" }
    { group:69, id:26, text: "Understaffed. Can only dispatch goods, will not receive any goods" }
    { group:69, id:27, text: "Skeleton staff only. Will not dispatch or receive goods" }
    { group:70, id:0, text: "No people in this locality." }
    { group:70, id:1, text: "free" }
    { group:70, id:2, text: "free" }
    { group:70, id:3, text: "free" }
    { group:70, id:4, text: "free" }
    { group:70, id:5, text: "free" }
    { group:70, id:6, text: "free" }
    { group:70, id:7, text: "free" }
    { group:70, id:8, text: "free" }
    { group:70, id:9, text: "free" }
    { group:70, id:10, text: "Nothing" }
    { group:70, id:11, text: "Trees and woodland" }
    { group:70, id:12, text: "Rocks" }
    { group:70, id:13, text: "Water" }
    { group:70, id:14, text: "Trees" }
    { group:70, id:15, text: "Cracks in the land" }
    { group:70, id:16, text: "Road" }
    { group:70, id:17, text: "Irrigation Ditch" }
    { group:70, id:18, text: "Rubble from destroyed buildings" }
    { group:70, id:19, text: "Wall" }
    { group:70, id:20, text: "Empty land" }
    { group:70, id:21, text: "Bridge" }
    { group:70, id:22, text: "Gardens" }
    { group:70, id:23, text: "Plaza" }
    { group:70, id:24, text: "To the Capital" }
    { group:70, id:25, text: "To the Kingdom" }
    { group:70, id:26, text: "Ore-bearing rock" }
    { group:70, id:27, text: "Normal rock" }
    { group:70, id:28, text: "Special rock" }
    { group:70, id:29, text: "Flood plain" }
    { group:70, id:30, text: "Submerged flood plain" }
    { group:70, id:31, text: "Marshland" }
    { group:70, id:32, text: "Sand dunes" }
    { group:70, id:33, text: "Brick wall" }
    { group:70, id:34, text: "Wall" }
    { group:70, id:35, text: "Meadow" }
    { group:70, id:36, text: "Cliffs" }
    { group:70, id:37, text: "Trees are impassable, but may be cleared.  Wood Cutters should be reasonably close to trees.  Woodland regrows over time.  (To select a building, right-click on its foundation)." }
    { group:70, id:38, text: "Rocks are impassable and may not be cleared. Perhaps you are lucky enough to have limestone, sandstone or granite for quarrying, although it could be ordinary rock of no value. Check your resources to find out." }
    { group:70, id:39, text: "Only ships and boats travel on water, but ferries and bridges can allow people to cross at certain points. Docks can permit vital trade with the rest of the Kingdom. Clay Pits must be adjacent to water." }
    { group:70, id:40, text: "Impassable terrain that may be cleared to allow city expansion. Wood Cutters need to be near trees in order to harvest timber.  (To select a building, right-click on its foundation)." }
    { group:70, id:41, text: "These chasms were caused by earthquakes. They may not be passed or filled in, and people prefer not to live next to them." }
    { group:70, id:42, text: "People only venture out of their buildings onto roads, and can only cross between flood plains and dry land where roads allow passage.  (To select a building, right-click on its foundation)." }
    { group:70, id:43, text: "Irrigation Ditches improve the fertility of any farms within two spaces." }
    { group:70, id:44, text: "These crumbled remains of old buildings lower the desirability of land in their vicinity." }
    { group:70, id:45, text: "Walls protect helpless citizens from raiders and invaders. They can withstand only a certain amount of battering, and thicker walls last longer." }
    { group:70, id:46, text: "Open land is prime building terrain.  Migrants, soldiers and some resource gatherers can walk upon it.  (To select a building, right-click on its foundation). " }
    { group:70, id:47, text: "This Bridge opens new land for our city, but also enables predators or invaders to cross the water!" }
    { group:70, id:48, text: "Gardens improve the local environment." }
    { group:70, id:49, text: "People prefer plazas!" }
    { group:70, id:50, text: "This road connects us to the rest of Egypt, and must be kept open so that immigrants and traders can arrive at our city. " }
    { group:70, id:51, text: "This is the road out to the further reaches of the Kingdom. It is a royal highway and, as such, freedom of passage must be maintained along it." }
    { group:70, id:52, text: "This is ore-bearing rock. You can mine either gold or copper here, depending on which metal is present.  " }
    { group:70, id:53, text: "This is normal rock. Depending on your city's resources, you might be able to mine construction-grade stone, or even gems, here. " }
    { group:70, id:54, text: "This is Special rock. (this text should not appear anywhere) " }
    { group:70, id:55, text: "This area offers highly fertile land now that the river has subsided." }
    { group:70, id:56, text: "This area will offer highly fertile land once the river subsides." }
    { group:70, id:57, text: "Marshy areas are too soggy to support structures, but can be traversed by careful citizens. Reeds grow here, but beware of crocodiles!  (To select a building, right-click on its foundation)." }
    { group:70, id:58, text: "The shifting sands here can't support structures, but migrants, soldiers and others can walk upon it.  (To select a building, right-click on its foundation). " }
    { group:70, id:59, text: "This is a brick wall. It slows invaders longer than a mud wall would do, but is no substitute for a company of trained soldiers!" }
    { group:70, id:60, text: "This is a simple mud wall. It will slow invaders for a short while, but you should not consider it a strong defense." }
    { group:70, id:61, text: "This land will allow all types of crops to grow. The lusher the flowers that grow here, the more fertile it is." }
    { group:70, id:62, text: "These massive cliffs are ideal places to build certain monuments. People cannot walk over this steep terrain, nor can anything be mined from them." }
    { group:71, id:0, text: "Bandstand" }
    { group:71, id:1, text: "People come here to watch the latest juggling tricks and listen to music." }
    { group:71, id:2, text: "This square never has any shows. It needs jugglers and musicians to liven it up." }
    { group:71, id:3, text: "This square offers its community both exciting juggling and music from local musicians." }
    { group:71, id:4, text: "This square hosts music for the amusement of the local community. It seeks jugglers to put on a few shows." }
    { group:71, id:5, text: "This square stages juggling. It could please audiences better if it had musicians to play." }
    { group:71, id:6, text: "This square is dead. With no employees, it provides no leisure services to the local community." }
    { group:71, id:7, text: "No current musical shows" }
    { group:71, id:8, text: "The musicians will play for another" }
    { group:71, id:9, text: "No current juggling acts" }
    { group:71, id:10, text: "Current jugglers will amaze for another" }
    { group:72, id:0, text: "Booth" }
    { group:72, id:1, text: "Citizens enjoy clever juggling acts and general nonsense here." }
    { group:72, id:2, text: "This square never has any shows. It needs real jugglers to provide entertainment for it." }
    { group:72, id:3, text: "This square is currently staging shows from local jugglers, who usually draw a good audience." }
    { group:72, id:4, text: "Breezes are the only thing stirring in this square. Without workers, it provides no shows for the locals." }
    { group:72, id:5, text: "No current juggling shows" }
    { group:72, id:6, text: "Current show runs for another" }
    { group:72, id:7, text: "Showing: 'Juggling by the Great Mephisto' by Mephisto" }
    { group:72, id:8, text: "Showing: 'The Sands of Time' by Ironrodhotep" }
    { group:72, id:9, text: "Showing: 'Cry Me a River' by Waseth" }
    { group:72, id:10, text: "Showing: 'The 10,000 Deben Pyramid' by Desenseth" }
    { group:72, id:11, text: "Showing: El-Tonjon's 'Crocodile Rocks" }
    { group:73, id:0, text: "Senet House" }
    { group:73, id:1, text: "Games of skill and chance can make or break the fortunes of the players." }
    { group:73, id:2, text: "This Senet House has players, but a reliable supply of beer would enliven the games." }
    { group:73, id:3, text: "This Senet House has constant games, much to the delight of the local population." }
    { group:73, id:4, text: "No one visits this Senet House. Without workers, the local community draws no entertainment from it." }
    { group:73, id:5, text: "No games in progress" }
    { group:73, id:6, text: "Current games will last" }
    { group:73, id:7, text: "Stored beer," }
    { group:74, id:0, text: "Pavilion" }
    { group:74, id:1, text: "Dancing, music and juggling...what more could a citizen desire?" }
    { group:74, id:2, text: "This square has no shows. It needs dancers, musicians and jugglers to draw crowds." }
    { group:74, id:3, text: "This square is in constant motion with dancing, music and juggling greatly delighting the local community." }
    { group:74, id:4, text: "This square has dancers and musicians for the locals, but some jugglers would be most welcome." }
    { group:74, id:5, text: "This square has dancers and jugglers. It needs musicians to provide complete entertainment." }
    { group:74, id:6, text: "This square has musicians and jugglers, but the music cries out for dancers to complete the show." }
    { group:74, id:7, text: "This square has juggling performances, but it needs musicians and dancers to fill the otherwise-empty stages." }
    { group:74, id:8, text: "This square has musicians, but no jugglers or dancers." }
    { group:74, id:9, text: "This square has dancers, who would greatly welcome some music. Juggling would be nice, too." }
    { group:74, id:10, text: "This square is closed. With no employees to run it, it is useless as a leisure amenity." }
    { group:74, id:11, text: "No current juggling shows" }
    { group:74, id:12, text: "Juggling will continue for another" }
    { group:74, id:13, text: "No current musicals" }
    { group:74, id:14, text: "Musical shows run for another" }
    { group:74, id:15, text: "No current dancing" }
    { group:74, id:16, text: "Dance shows run for another" }
    { group:75, id:0, text: "Conservatory" }
    { group:75, id:1, text: "Egyptian people are always eager to hear the latest renditions from new musicians." }
    { group:75, id:2, text: "We are pleased to announce that, with full employment, we are training up to four new musicians every month." }
    { group:75, id:3, text: "We are slightly understaffed, and so can train at most two new musicians each month." }
    { group:75, id:4, text: "We are half-staffed, and so are only able to train one musician in the coming month." }
    { group:75, id:5, text: "We have so few employees that we will struggle to turn out one new musician over the next two months." }
    { group:75, id:6, text: "I have no staff other than myself. I cannot be expected to work under these conditions! At best, I can train a musician in three months." }
    { group:75, id:7, text: "With no training staff, this school cannot train any new musicians." }
    { group:76, id:0, text: "Dance School" }
    { group:76, id:1, text: "Dancers delight audiences with graceful and tantalizing new moves." }
    { group:76, id:2, text: "We are pleased to announce that, with full employment, we can provide up to four new dancers every month." }
    { group:76, id:3, text: "We are slightly understaffed, and so can only train two new dancers each month at most." }
    { group:76, id:4, text: "We are half-staffed, so we can train only one dancer in the coming month." }
    { group:76, id:5, text: "We need instructors so badly that we can barely handle one new dancer over the next two months." }
    { group:76, id:6, text: "I have no staff other than myself. I cannot be expected to work under these conditions! At best, I can teach one dancer in three months." }
    { group:76, id:7, text: "With no instructors, this dance school cannot teach any new dancers." }
    { group:77, id:0, text: "Juggler School" }
    { group:77, id:1, text: "New jugglers with inventive new routines are always in demand." }
    { group:77, id:2, text: "We are pleased to announce that, with full employment, we train up to four new jugglers every month." }
    { group:77, id:3, text: "We are slightly understaffed, and so can produce two new jugglers each month, at most." }
    { group:77, id:4, text: "We are half-staffed, and so are only able to train one juggler in the coming month." }
    { group:77, id:5, text: "We need employees badly.  It will be a struggle to turn out one new juggler over the next two months." }
    { group:77, id:6, text: "I have no staff other than myself. I cannot be expected to work under these conditions! At best, I can train a juggler in three months." }
    { group:77, id:7, text: "This school is deserted. Without mentors in its employ, no new jugglers will be produced." }
    { group:78, id:0, text: "Senet trainers? Was Bullfighting Trainer" }
    { group:78, id:1, text: "The master strategists who work here train expert senet masters to run the city's ever-popular Senet Houses." }
    { group:78, id:2, text: "We are pleased to announce that, with full employment, we can provide up to four senet masters every month." }
    { group:78, id:3, text: "We are slightly understaffed, and so can only provide two new senet masters each month, at most." }
    { group:78, id:4, text: "We are half staffed, and so can only train one senet master in the coming month." }
    { group:78, id:5, text: "We are badly in need of employees, and will struggle to turn out one new senet master over the next two months." }
    { group:78, id:6, text: "I have no staff other than myself. I cannot be expected to work under these conditions!  At best, I can hone one senet master in three months." }
    { group:78, id:7, text: "With no teachers, no new senet masters will be trained. Senet Houses throughout the city could suffer as a result." }
    { group:79, id:0, text: "Gardens" }
    { group:79, id:1, text: "This pleasant lot gives citizens relief from the noise, heat and dirt of the city with a cool oasis of green space.  Everyone wants a garden next door." }
    { group:80, id:0, text: "Statue" }
    { group:80, id:1, text: "Monuments to gods and bygone pharaohs enhance a neighborhood's prestige. People are proud to have statues nearby...and the bigger, the better." }
    { group:80, id:2, text: "Triumphal arch" }
    { group:80, id:3, text: "This magnificent edifice commemorates historic victories over Egypt's enemies. Nothing could be more prestigious." }
    { group:81, id:0, text: "Apothecary" }
    { group:81, id:1, text: "Apothecaries improve citizens' health as they make house-calls in the neighborhoods on their route. Wealthy areas want an Apothecary nearby." }
    { group:81, id:2, text: "This Apothecary is not operational, and does nothing for the health of the local community." }
    { group:81, id:3, text: "This Apothecary is operational and provides potions and unguents to the local community." }
    { group:82, id:0, text: "Mortuary" }
    { group:82, id:1, text: "Although no one wants to live near one, Mortuaries save lives when disease strikes. The city should have the capacity to embalm all of its dead." }
    { group:82, id:2, text: "This Mortuary is not operational, and cannot prepare departed residents' bodies for the afterlife." }
    { group:82, id:3, text: "This Mortuary is operational and mummifies deceased neighbors quickly and professionally." }
    { group:82, id:4, text: "Without linen, we cannot prepare the dead for their journey through eternity." }
    { group:83, id:0, text: "Physician" }
    { group:83, id:1, text: "A pomegranate a day keeps the doctor away, or so the saying goes. Physicians improve health as they make their rounds." }
    { group:83, id:2, text: "This Physician's office is not operational, and does nothing for community health." }
    { group:83, id:3, text: "This Physician's office is operational, and the local community is healthy and fit." }
    { group:84, id:0, text: "Dentist" }
    { group:84, id:1, text: "Sand gets into everything, including food. Constant abrasion makes plenty of work for Egyptian dentists." }
    { group:84, id:2, text: "This Dentist's office is not operational, and its neighbors' teeth show the lack of care." }
    { group:84, id:3, text: "This Dentist's office is operational, and the local community's teeth gleam with pride." }
    { group:85, id:0, text: "Scribal School" }
    { group:85, id:1, text: "Children of the wealthy must attend neighborhood schools to learn reading and writing if they are to attain their parents' status." }
    { group:85, id:2, text: "This school cannot educate anyone at present. It lacks employees, papyrus, or both." }
    { group:85, id:3, text: "This school enables children to escape a life of physical toil as long as it has both employees and papyrus." }
    { group:86, id:0, text: "Left" }
    { group:86, id:1, text: "Top" }
    { group:86, id:2, text: "Right" }
    { group:86, id:3, text: "Bottom" }
    { group:87, id:0, text: "Library" }
    { group:87, id:1, text: "Literary works of all kinds are produced and stored here. Scribes insist that Libraries are crucial for an important city." }
    { group:87, id:2, text: "This Library lacks employees, papyrus, or both. It cannot serve the community." }
    { group:87, id:3, text: "As long as this Library has employees and papyrus, it can serve the community." }
    { group:88, id:0, text: "Police Station" }
    { group:88, id:1, text: "Police Stations send constables into the city to keep the peace. Civic order is assured when constables patrol the city evenly." }
    { group:88, id:2, text: "Our constable is out on patrol." }
    { group:88, id:3, text: "Our constable is preparing for duty." }
    { group:88, id:4, text: "Currently our duty roster is full. Our constables are always alert to signs of crime." }
    { group:88, id:5, text: "We are a little short of constables. We have gaps of perhaps a day or two in our coverage." }
    { group:88, id:6, text: "We are understaffed. Criminals are encouraged by gaps of up to a week in our duty roster." }
    { group:88, id:7, text: "We have far too few men. Criminals could operate unchecked for up to two weeks at a time." }
    { group:88, id:8, text: "We are operating on a desk staff only. We frequently go a full month without sending a constable out on the streets." }
    { group:88, id:9, text: "With no staff, this station is little more than a target for vandals." }
    { group:88, id:10, text: " thefts this year." }
    { group:88, id:11, text: " gold stolen this year." }
    { group:89, id:0, text: "Fort" }
    { group:89, id:1, text: "This Fort is accursed by Seth, and it will be some time yet before any soldiers dare to venture back here." }
    { group:89, id:2, text: "Forts draw soldiers from the city's Recruiter. A Military Academy would provide better-trained troops." }
    { group:90, id:0, text: "Gatehouse" }
    { group:90, id:1, text: "Walls need a Gatehouse so that migrants and traders can come and go freely." }
    { group:91, id:0, text: "Tower" }
    { group:91, id:1, text: "Build Towers into Walls at regular intervals, or at least in vulnerable areas. When connected to roads, Towers receive guards from the city's Recruiter. Tower guards rain javelins on nearby invaders, and patrol thick enough walls." }
    { group:91, id:2, text: "With no workers, we cannot station Tower guards or hire anyone to patrol the Walls." }
    { group:91, id:3, text: "Our men are at full strength, alert and ready to repel any threats." }
    { group:91, id:4, text: "We have maintenance staff, but we need guards from a Recruiter to defend the city." }
    { group:92, id:0, text: "Temple to Osiris (Agriculture)" }
    { group:92, id:1, text: "Osiris brings fertility to the land and makes the crops grow. Appease him, or prepare to go hungry." }
    { group:93, id:0, text: "Temple to Ra (The Kingdom)" }
    { group:93, id:1, text: "Merchants know well the value in pleasing Ra. Trade is safer and more profitable with Ra's blessing, and your city's esteem is greater." }
    { group:94, id:0, text: "Temple to Ptah (Craftsman)" }
    { group:94, id:1, text: "Laborers and craftsmen worship Ptah to ease their toil. When Ptah is angered, no industry is safe from catastrophe." }
    { group:95, id:0, text: "Temple to Seth (Destruction)" }
    { group:95, id:1, text: "Seth watches over soldiers and encourages valor in combat. No man dares fight without the blessing of Seth." }
    { group:96, id:0, text: "Temple to Bast (Home)" }
    { group:96, id:1, text: "When Bast is displeased, nobody's home is safe. Some blame Bast for disease, too." }
    { group:97, id:0, text: "Bazaar" }
    { group:97, id:1, text: "Our Bazaars make the Kingdom's bounty available to every nearby citizen. Every home needs Bazaar access, although no one wants to live next door to one." }
    { group:97, id:2, text: "This Bazaar is not operational, and supplies nothing to the local community." }
    { group:97, id:3, text: "This Bazaar is operational and supplies the needs of local homes." }
    { group:97, id:4, text: "This Bazaar has traders, but they are currently looking for food or goods to sell." }
    { group:97, id:5, text: "Food supplies for" }
    { group:97, id:6, text: "Special orders" }
    { group:97, id:7, text: "Bazaar instructions" }
    { group:97, id:8, text: "Buy" }
    { group:97, id:9, text: "Don't Buy" }
    { group:97, id:10, text: "The Bazaar trader is here, awaiting food." }
    { group:97, id:11, text: "The Bazaar trader is out distributing goods." }
    { group:97, id:12, text: "The Bazaar trader is returning to restock." }
    { group:98, id:0, text: "Granary" }
    { group:98, id:1, text: "Full Granaries are vital for keeping the people's bellies filled, and help attract new citizens. A Granary can store any type of food." }
    { group:98, id:2, text: "Storing" }
    { group:98, id:3, text: "Space for" }
    { group:98, id:4, text: "This Granary is not needed. Egypt provides our city with all the grain it needs. Any food we produce will go straight into any Storage Yards with empty space." }
    { group:98, id:5, text: "Special orders" }
    { group:98, id:6, text: "Granary instructions" }
    { group:98, id:7, text: "Empty Granary" }
    { group:98, id:8, text: "Stop emptying Granary" }
    { group:98, id:9, text: "Trying to send food elsewhere" }
    { group:99, id:0, text: "Storage Yard" }
    { group:99, id:1, text: "All manner of goods need storage. Caravans trade at Storage Yards, Docks swap exports for imports at nearby yards, and Bazaars stock up here, too." }
    { group:99, id:2, text: "Special orders" }
    { group:99, id:3, text: "Storage Yard instructions" }
    { group:99, id:4, text: "START emptying Storage Yard" }
    { group:99, id:5, text: "STOP emptying Storage Yard" }
    { group:99, id:6, text: "Trying to send goods elsewhere" }
    { group:99, id:7, text: "Accept None" }
    { group:99, id:8, text: "Don't Accept" }
    { group:99, id:9, text: "Getting goods" }
    { group:99, id:10, text: "Getting food" }
    { group:99, id:11, text: "Trade Center" }
    { group:99, id:12, text: "Become the Trade Center" }
    { group:99, id:13, text: "WARNING: This Storage Yard is completely full. It cannot accept any more goods." }
    { group:99, id:14, text: "WARNING: This Storage Yard is getting full. It can only accept goods of existing types. No new commodity types will be checked in at all." }
    { group:99, id:15, text: "Our delivery man is ready for new orders." }
    { group:99, id:16, text: "Our delivery man is taking goods elsewhere." }
    { group:99, id:17, text: "Our delivery man is on his way back." }
    { group:99, id:18, text: "Accept" }
    { group:99, id:19, text: "Get" }
    { group:99, id:20, text: "Empty Food" }
    { group:99, id:21, text: "Empty " }
    { group:99, id:22, text: "This Storage Yard is empty." }
    { group:99, id:23, text: "block of" }
    { group:99, id:24, text: "blocks of " }
    { group:99, id:25, text: "up to 1/4 of" }
    { group:99, id:26, text: "up to 1/2 of" }
    { group:99, id:27, text: "up to 3/4 of" }
    { group:99, id:28, text: "all" }
    { group:99, id:29, text: "Yard" }
    { group:99, id:30, text: "Granary" }
    { group:99, id:31, text: "maximum " }
    { group:99, id:32, text: "Fill" }
    { group:99, id:33, text: "Our delivery man is out getting goods" }
    { group:100, id:0, text: "Shipwright" }
    { group:100, id:1, text: "With enough workers, the Shipwright builds military vessels and fishing boats for the city's Wharves. Wood is required to build warships and transport ships; no raw materials are needed to build fishing boats." }
    { group:100, id:2, text: "Production is" }
    { group:100, id:3, text: "complete." }
    { group:100, id:4, text: "There are currently no Wharves demanding any of our vessels." }
    { group:100, id:5, text: "We are building a military vessel or fishing boat to order for a Wharf in the city." }
    { group:100, id:6, text: "We are repairing a military vessel." }
    { group:100, id:7, text: "Stored wood," }
    { group:100, id:8, text: "We need wood to repair and build military vessels." }
    { group:100, id:9, text: "A Warship or Transport Wharf has ordered us to build a ship, but we lack the necessary wood." }
    { group:100, id:10, text: "We have ships lined up to be repaired, but no wood with which to repair them." }
    { group:101, id:0, text: "Dock" }
    { group:101, id:1, text: "Trading ships from all over the world moor here to deliver imports and pick up exports. You cannot conduct waterborne trade without Docks." }
    { group:101, id:2, text: "Without any dockers on staff, we cannot service the docked ship." }
    { group:101, id:3, text: "We are servicing the docked ship. With so few dock workers, though, this could take a long time." }
    { group:101, id:4, text: "We are servicing the docked ship, although this will take a little longer than it would if we were fully staffed." }
    { group:101, id:5, text: "With full employment, we can service the docked ship quickly and efficiently." }
    { group:101, id:6, text: "Any ship that moors here will find no workers to load or unload its cargo." }
    { group:101, id:7, text: "The few dockers employed here would take a long time to load and unload any ships that arrive in port." }
    { group:101, id:8, text: "We are understaffed, so it will take a little longer than normal to load and unload any ships that arrive in port." }
    { group:101, id:9, text: "With full employment, our dockers are just waiting for their ship to come in." }
    { group:102, id:0, text: "Fishing Wharf" }
    { group:102, id:1, text: "Boats sail here from the Shipwright to take on crews and begin fishing local waters. Each Wharf can service one fishing boat." }
    { group:102, id:2, text: "We are currently waiting for a Shipwright to build us a fishing boat." }
    { group:102, id:3, text: "Our fishing boat is sailing out to the fishing grounds." }
    { group:102, id:4, text: "Our boat is at the fishing grounds now, hauling in fish." }
    { group:102, id:5, text: "Our boat is sailing to the Wharf now." }
    { group:102, id:6, text: "We are re-stocking our fishing boat for another outbound voyage." }
    { group:102, id:7, text: "Our fishing boat is sailing back from the fishing grounds with its catch." }
    { group:102, id:8, text: "Our fishermen hope that someone discovers fishing grounds in this area someday. They can't earn much of a living with the waters depleted." }
    { group:102, id:9, text: "Your Overseer of Commerce ordered a halt to fishing." }
    { group:102, id:10, text: "Our fishing boat is not going out into that polluted water!" }
    { group:103, id:0, text: "Mansion" }
    { group:103, id:1, text: "Your home is one of the city's most desirable addresses. Your Mansion gives you the authority to draw a salary. " }
    { group:103, id:2, text: "Deben per month" }
    { group:103, id:3, text: "Village Elder's salary of" }
    { group:103, id:4, text: "Village Noble's salary of" }
    { group:103, id:5, text: "Royal Scholar's salary of" }
    { group:103, id:6, text: "Royal Scribe's salary of" }
    { group:103, id:7, text: "Royal Judge's salary of" }
    { group:103, id:8, text: "Royal Mayor's salary of" }
    { group:103, id:9, text: "Royal Governor's salary of" }
    { group:103, id:10, text: "Nomarch's salary of" }
    { group:103, id:11, text: "Chancellor's salary of" }
    { group:103, id:12, text: "Vizier's salary of" }
    { group:103, id:13, text: "Pharaoh's salary of" }
    { group:104, id:0, text: "Architect's Post" }
    { group:104, id:1, text: "Egyptian architects are the most advanced the world has ever known. Their vigilance prevents buildings from collapsing." }
    { group:104, id:2, text: "Our architect is hard at work." }
    { group:104, id:3, text: "Our architect is preparing to depart." }
    { group:104, id:4, text: "Currently we have no down time. Our architects are constantly out inspecting and repairing the city's larger buildings." }
    { group:104, id:5, text: "We have a day or two before our overworked architects are back out on the streets." }
    { group:104, id:6, text: "We are understaffed, so we have a week's wait before our returning architects go back on duty." }
    { group:104, id:7, text: "We are badly understaffed and have a two-week gap between each architect's rounds." }
    { group:104, id:8, text: "We are operating on a skeleton staff. We can barely field one architect each month." }
    { group:104, id:9, text: "With no architects on staff, the neighborhood is at the mercy of shifting sands." }
    { group:105, id:0, text: "Palace" }
    { group:105, id:1, text: "The Palace is among your city's most desirable buildings and the cornerstone of the city economy. It turns gold nuggets to debens and stores some of the city's funds." }
    { group:105, id:2, text: "Vaults hold" }
    { group:105, id:3, text: "Visit your Ratings Overseer?" }
    { group:106, id:0, text: "Tax Collector's office" }
    { group:106, id:1, text: "Although not the most popular workers in the city, tax collectors make possible our great Kingdom and all the benefits that flow to us." }
    { group:106, id:2, text: "Vaults hold" }
    { group:106, id:3, text: "Our collector is out auditing the locals' accounts." }
    { group:106, id:4, text: "Our collector is preparing to depart." }
    { group:106, id:5, text: "Currently working with complete efficiency, our collectors ensure that all due taxes on their routes are paid." }
    { group:106, id:6, text: "We have a day or two of idle time before returning collectors go back out on the streets." }
    { group:106, id:7, text: "We are understaffed, and have a week's wait before any collectors return to duty." }
    { group:106, id:8, text: "We are badly understaffed and go two weeks between collection patrols." }
    { group:106, id:9, text: "With so few people in this office, local citizens can evade much of their tax bills." }
    { group:106, id:10, text: "With no collection staff, this office contributes nothing to the city treasury." }
    { group:106, id:11, text: "Your city needs a Palace before you can collect taxes." }
    { group:106, id:12, text: "Your city needs a working Palace in order to collect taxes." }
    { group:107, id:0, text: "Water Lift" }
    { group:107, id:1, text: "This Water Lift can pump large volumes of water when Irrigation Ditches are connected to its front or back sluices." }
    { group:107, id:2, text: "This Water Lift is not working. Ask your Overseer of the Workers to assign more workers to Water Services." }
    { group:107, id:3, text: "This Water Lift needs to be adjacent to water, or connected by an Irrigation Ditch to a working Water Lift, before it will function." }
    { group:108, id:0, text: "Water Supply" }
    { group:108, id:1, text: "Water carriers get clean water from this desirable source, and improve health and happiness as they deliver it to houses on their routes. " }
    { group:108, id:2, text: "Our staff continuously carries clean water to the local populace." }
    { group:108, id:3, text: "We are a little short of water carriers. We have gaps of perhaps a day or two in our coverage." }
    { group:108, id:4, text: "We are understaffed, and have dangerous gaps of up to a week in our water delivery cycle." }
    { group:108, id:5, text: "We have far too few workers. Sometimes, no water is delivered for up to two weeks at a time." }
    { group:108, id:6, text: "We are operating on a skeleton staff only. We frequently go a full month without delivering any water." }
    { group:108, id:7, text: "With no delivery staff, this facility could just as well be a dry hole in the ground." }
    { group:109, id:0, text: "Well" }
    { group:109, id:1, text: "Citizens without clean water deliveries can draw water from Wells, but Well-water neighborhoods are not the healthiest or most desirable places to live." }
    { group:109, id:2, text: "This well is unneeded. All the houses it serves get deliveries from a Water Supply." }
    { group:109, id:3, text: "This well's water is going to waste, as there are no houses within its service range." }
    { group:110, id:0, text: "Oracle? Does Shrine go here?" }
    { group:110, id:1, text: "This Shrine makes nearby homes more desirable and pleases all of the gods. It does not employ priests, though, or provide houses with access to any particular god." }
    { group:111, id:0, text: "Burning ruin" }
    { group:111, id:1, text: "Fire marshals could not get here in time to save the building. When the fires burn themselves out, only rubble will be left on this site." }
    { group:112, id:0, text: "Grain Farm" }
    { group:112, id:1, text: "Grain must be stored in Granaries to feed your people, or in Storage Yards if it is for export." }
    { group:112, id:2, text: "Production is" }
    { group:112, id:3, text: "complete." }
    { group:112, id:4, text: "Your Overseer of Commerce ordered a halt to grain farming." }
    { group:112, id:5, text: "This farm has no workers. Even weeds struggle to grow here." }
    { group:112, id:6, text: "This farm has all the workers it needs. It gets maximum yield, given its current fertility." }
    { group:112, id:7, text: "This farm could be more productive if it had more workers." }
    { group:112, id:8, text: "This farm is understaffed. Its workers don't grow as much food as they could." }
    { group:112, id:9, text: "There are very few farmers working here. Grain production is scanty as a result." }
    { group:112, id:10, text: "With hardly any workers at this farm, it will produce very little grain this season." }
    { group:112, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:112, id:12, text: "Land is" }
    { group:112, id:13, text: "fertile." }
    { group:112, id:14, text: "The next grain harvest is in" }
    { group:113, id:0, text: "Lettuce Farm" }
    { group:113, id:1, text: "Lettuce contributes to the balanced diet your people need for happiness and health. Granaries store lettuce for local consumption, and Storage Yards take surpluses for export." }
    { group:113, id:2, text: "Production is" }
    { group:113, id:3, text: "complete." }
    { group:113, id:4, text: "The Overseer of Commerce decreed that lettuce farming should cease." }
    { group:113, id:5, text: "This farm has no workers. Nothing has been planted." }
    { group:113, id:6, text: "This farm has all the workers it needs. It grows as much lettuce as its fertility allows." }
    { group:113, id:7, text: "This farm is working below maximum capacity, so its crop is smaller than it could be." }
    { group:113, id:8, text: "This farm is understaffed. Its lettuce heads are smaller and fewer than they could be." }
    { group:113, id:9, text: "There are very few farmers working here. The lettuce harvest will suffer greatly for it." }
    { group:113, id:10, text: "With almost no farmers to tend the crop, this will not be a banner year for lettuce." }
    { group:113, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:113, id:12, text: "Land is" }
    { group:113, id:13, text: "fertile." }
    { group:113, id:14, text: "The next lettuce harvest is in" }
    { group:114, id:0, text: "Pomegranate Farm" }
    { group:114, id:1, text: "Pomegranates enhance the balanced diet people need for health and happiness. Granaries store pomegranates for local consumption, and Storage Yards can export surpluses." }
    { group:114, id:2, text: "Production is" }
    { group:114, id:3, text: "complete." }
    { group:114, id:4, text: "Pomegranate farming has ceased, by order of the Overseer of Commerce." }
    { group:114, id:5, text: "This orchard has no workers, and the trees are fruitless and gnarled." }
    { group:114, id:6, text: "This orchard has all the workers it needs. The trees bear as much fruit as the land's fertility allows." }
    { group:114, id:7, text: "This orchard is working below maximum capacity, so the crop this year is a bit lighter than it should be." }
    { group:114, id:8, text: "This orchard is understaffed. It produces fewer pomegranates than it could." }
    { group:114, id:9, text: "Very few people work at this orchard. The pomegranate harvest will be small." }
    { group:114, id:10, text: "With hardly any workers at this orchard, the pomegranate crop will be quite disappointing." }
    { group:114, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:114, id:12, text: "Land is" }
    { group:114, id:13, text: "fertile." }
    { group:114, id:14, text: "The next pomegranate harvest is in" }
    { group:115, id:0, text: "Flax Farm" }
    { group:115, id:1, text: "Flax goes to a Weaver, who processes the fibers and weaves them into linen for Mortuaries to use in embalming, or for export." }
    { group:115, id:2, text: "Production is" }
    { group:115, id:3, text: "complete." }
    { group:115, id:4, text: "Your Overseer of Commerce ordered a halt to flax growing." }
    { group:115, id:5, text: "This farm has no workers. No flax can grow here." }
    { group:115, id:6, text: "This farm has all the workers it needs. The fields are carpeted with blue flax flowers." }
    { group:115, id:7, text: "This farm is working below maximum capacity. Flax production could be better with more workers." }
    { group:115, id:8, text: "This farm is understaffed. Flax plants aren't as dense or as sturdy as they could be." }
    { group:115, id:9, text: "There are very few people working here. The flax harvest will suffer as a result." }
    { group:115, id:10, text: "With hardly any workers in this farm, the ground is mostly barren." }
    { group:115, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:115, id:12, text: "Land is" }
    { group:115, id:13, text: "fertile." }
    { group:115, id:14, text: "The next flax harvest is in" }
    { group:116, id:0, text: "Reed Gatherer" }
    { group:116, id:1, text: "Reed gatherers venture from here into the marshes to collect reeds for papyrus, without which education would be impossible." }
    { group:116, id:2, text: "Stored reeds" }
    { group:116, id:3, text: "complete." }
    { group:116, id:4, text: "Reed harvesting has ceased, by command of the Overseer of Commerce." }
    { group:116, id:5, text: "This place has no workers to gather reeds. " }
    { group:116, id:6, text: "This place has all the workers it needs. No reed is safe. " }
    { group:116, id:7, text: "This place is below its labor potential, so reed gathering is slowed somewhat." }
    { group:116, id:8, text: "This place is understaffed, so reed cutting is slow going. " }
    { group:116, id:9, text: "Very few people work here, and few reeds are being cut." }
    { group:116, id:10, text: "With so few gatherers employed here, almost no reeds are harvested." }
    { group:116, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:116, id:12, text: "Land is" }
    { group:116, id:13, text: "fertile." }
    { group:116, id:14, text: "The next reed harvest is in" }
    { group:117, id:0, text: "Cattle Ranch" }
    { group:117, id:1, text: "Well-fed citizens want meat in their diet. Meat can be kept in Granaries for local consumption, or taken to Storage Yards for export." }
    { group:117, id:2, text: "Production is" }
    { group:117, id:3, text: "complete." }
    { group:117, id:4, text: "By decree of the Overseer of Commerce, cattle ranching has ceased." }
    { group:117, id:5, text: "This ranch has no workers. All of the animals have escaped or died." }
    { group:117, id:6, text: "This ranch has all the workers it needs. With straw, it can yield ample meat." }
    { group:117, id:7, text: "This ranch needs to hire more workers if it is to produce meat efficiently. " }
    { group:117, id:8, text: "This farm is understaffed. It cannot reach its potential output." }
    { group:117, id:9, text: "Very few people work at this ranch. Its potential meat production is low." }
    { group:117, id:10, text: "With hardly any workers, this ranch can raise very few cattle." }
    { group:117, id:11, text: "This farm's land was blighted by the recent swarm of locusts. Cattle cannot thrive here until it recovers." }
    { group:117, id:12, text: "Land is" }
    { group:117, id:13, text: "fertile." }
    { group:118, id:0, text: "Plain Stone Quarry" }
    { group:118, id:1, text: "Cut plain stone from the earth here. With monuments rising all across Egypt, you can usually find a buyer for good building stone, even if you have no use for it yourself. " }
    { group:118, id:2, text: "Production is" }
    { group:118, id:3, text: "complete." }
    { group:118, id:4, text: "The Overseer of Commerce commanded a halt to quarrying." }
    { group:118, id:5, text: "This quarry has no workers to cut rock from the earth." }
    { group:118, id:6, text: "This quarry has all the workers it needs, and produces many tons of plain stone." }
    { group:118, id:7, text: "This quarry is working below maximum capacity due to a small shortage of workers." }
    { group:118, id:8, text: "This quarry is understaffed, and takes longer to produce stone blocks than it should." }
    { group:118, id:9, text: "There are very few people working at this quarry. Production is very slow as a result." }
    { group:118, id:10, text: "With hardly any workers at this quarry, production is at a virtual standstill. It will produce little over the coming year." }
    { group:119, id:0, text: "Limestone Quarry" }
    { group:119, id:1, text: "Cut fine limestone for use in monument construction or for export." }
    { group:119, id:2, text: "Production is" }
    { group:119, id:3, text: "complete." }
    { group:119, id:4, text: "Your Overseer of Commerce ordered a halt to limestone quarrying." }
    { group:119, id:5, text: "This quarry has no workers, and thus produces no limestone." }
    { group:119, id:6, text: "This quarry has all the workers it needs, and produces as much limestone as possible." }
    { group:119, id:7, text: "This quarry is working below maximum capacity. Production could be greater with more workers." }
    { group:119, id:8, text: "This building is understaffed. It takes longer than it should to cut blocks of limestone." }
    { group:119, id:9, text: "Very few people work in this building. Production is much too slow as a result." }
    { group:119, id:10, text: "With hardly any workers here, limestone production is almost nonexistent. " }
    { group:120, id:0, text: "Wood Cutter" }
    { group:120, id:1, text: "Wood has many uses ranging from monument construction to shipbuilding, and is in great demand throughout the Kingdom." }
    { group:120, id:2, text: "Holds" }
    { group:120, id:3, text: "Raw wood." }
    { group:120, id:4, text: "Tree cutting has ceased, by order of the Overseer of Commerce." }
    { group:120, id:5, text: "This facility has no workers, and contributes nothing to the city's economy." }
    { group:120, id:6, text: "This building has all the workers it needs. It harvests wood with maximum efficiency." }
    { group:120, id:7, text: "This Wood Cutter is not fully staffed, and wood production is lower than it could be." }
    { group:120, id:8, text: "This industry is understaffed, and takes longer to cut wood than it should." }
    { group:120, id:9, text: "Very few people work at this yard. Wood production is very slow as a result." }
    { group:120, id:10, text: "With hardly any tree-cutters, wood output is at a virtual standstill here." }
    { group:121, id:0, text: "Clay Pit" }
    { group:121, id:1, text: "Mine clay for trade, or to supply potters. People find endless uses for pottery, and you can often trade it profitably with other cities." }
    { group:121, id:2, text: "Production is" }
    { group:121, id:3, text: "complete." }
    { group:121, id:4, text: "Your Overseer of Commerce stopped clay digging." }
    { group:121, id:5, text: "This pit has no workers to dig clay." }
    { group:121, id:6, text: "This pit has all the workers it needs, and produces large amounts of clay." }
    { group:121, id:7, text: "This pit is working below maximum capacity. Clay production will be slightly slower as a result." }
    { group:121, id:8, text: "This pit is understaffed, and is taking longer to produce clay than it should." }
    { group:121, id:9, text: "So few people work at this pit that clay production is extremely slow." }
    { group:121, id:10, text: "With hardly any diggers at this pit, it will produce very little clay over the coming year." }
    { group:122, id:0, text: "Brewery" }
    { group:122, id:1, text: "Brewers turn barley into beer, without which the Senet Houses would be empty and the city's festivals boring. Beer is a widely-demanded trade commodity." }
    { group:122, id:2, text: "Production is" }
    { group:122, id:3, text: "complete." }
    { group:122, id:4, text: "An edict from the Overseer of Commerce ordered a halt to brewing." }
    { group:122, id:5, text: "This Brewery has no employees. There will be no beer from here." }
    { group:122, id:6, text: "With a full complement of employees, this Brewery works at top speed to slake Egypt's thirst." }
    { group:122, id:7, text: "This Brewery is working below maximum capacity. Beer output is slightly slower than it could be." }
    { group:122, id:8, text: "This Brewery is understaffed, and takes much longer to produce beer than it should." }
    { group:122, id:9, text: "Very few people work at this Brewery. Beer production is very slow as a result." }
    { group:122, id:10, text: "With hardly any brewers on staff, this Brewery will produce almost no beer over the coming year." }
    { group:122, id:11, text: "This Brewery cannot make beer until it receives a delivery of barley from a Storage Yard or a farm." }
    { group:122, id:12, text: "Stored barley," }
    { group:123, id:0, text: "Weaver" }
    { group:123, id:1, text: "Here flax is processed into linen, which Mortuaries need for embalming. Linen may also be profitably traded." }
    { group:123, id:2, text: "Production is" }
    { group:123, id:3, text: "complete." }
    { group:123, id:4, text: "Your Overseer of Commerce decreed that linen production be wrapped up." }
    { group:123, id:5, text: "This Weaver has no workers, and so cannot produce any linen at all." }
    { group:123, id:6, text: "This Weaver is fully staffed, and produces ample high-quality linen." }
    { group:123, id:7, text: "This Weaver could use more workers to reach its full potential for linen production." }
    { group:123, id:8, text: "This Weaver is understaffed, and produces linen more slowly than it should." }
    { group:123, id:9, text: "Very few people work at this Weaver. Linen production is slow as a result." }
    { group:123, id:10, text: "With hardly any employees, this Weaver can produce almost no linen over the coming year." }
    { group:123, id:11, text: "This workshop will produce no linen without a shipment of flax, whether from a Storage Yard or a farm." }
    { group:123, id:12, text: "Stored flax," }
    { group:124, id:0, text: "Weaponsmith" }
    { group:124, id:1, text: "Armorers transform copper into spears, which you may trade for a handsome profit or use to equip your own companies." }
    { group:124, id:2, text: "Production is" }
    { group:124, id:3, text: "complete." }
    { group:124, id:4, text: "Your Overseer of Commerce ordered a halt to weapon production." }
    { group:124, id:5, text: "This Weaponsmith has no employees, and will therefore produce no weapons." }
    { group:124, id:6, text: "This workshop has all the employees it needs, and produces as many weapons as possible." }
    { group:124, id:7, text: "This Weaponsmith is not fully staffed, so weapon production is slightly slower than it could be." }
    { group:124, id:8, text: "This workshop is understaffed. It takes longer to produce weapons than it should." }
    { group:124, id:9, text: "There are very few people working at this Weaponsmith. Weapon production is very slow." }
    { group:124, id:10, text: "With hardly any employees, this Weaponsmith contributes very few weapons to the city's efforts." }
    { group:124, id:11, text: "This Weaponsmith needs copper, from a Storage Yard or a Copper Mine, to produce weapons." }
    { group:124, id:12, text: "Stored copper," }
    { group:125, id:0, text: "Jeweler" }
    { group:125, id:1, text: "The craftsmen here turn gemstones into jewelry (a luxury good). Some citizens want jewelry for themselves, and you can often export any surplus, although it is seldom worth much." }
    { group:125, id:2, text: "Production is" }
    { group:125, id:3, text: "complete." }
    { group:125, id:4, text: "The Overseer of Commerce commands a halt to jewelry production." }
    { group:125, id:5, text: "This Jeweler has no employees, and is not producing anything." }
    { group:125, id:6, text: "This facility is at full employment, and makes as much jewelry as possible." }
    { group:125, id:7, text: "This facility has some job openings. Jewelry production will improve when they are filled." }
    { group:125, id:8, text: "This facility is understaffed, and takes longer to produce jewelry than it should." }
    { group:125, id:9, text: "Very few craftsmen work here. Jewelry production is very slow as a result." }
    { group:125, id:10, text: "With hardly any craftsmen, this Jeweler will produce few luxury goods over the coming year." }
    { group:125, id:11, text: "This workshop needs a shipment of gems from a Storage Yard or a Gemstone Mine to produce jewelry." }
    { group:125, id:12, text: "Stored gems," }
    { group:126, id:0, text: "Potter" }
    { group:126, id:1, text: "Here, potters mould clay into pots that citizens use for storing commodities. Trade pottery, or let your Bazaars distribute it so that people can build better housing." }
    { group:126, id:2, text: "Production is" }
    { group:126, id:3, text: "complete." }
    { group:126, id:4, text: "Pottery production has ceased, by order of the Overseer of Commerce." }
    { group:126, id:5, text: "This Potter has no employees. It will not turn out a single pot." }
    { group:126, id:6, text: "This Potter has all the employees it needs, and produces as much pottery as possible." }
    { group:126, id:7, text: "This Potter has some job openings. Pottery production will suffer slightly as a result." }
    { group:126, id:8, text: "This workshop is understaffed, and it takes longer to produce pottery than it should." }
    { group:126, id:9, text: "Very few people work here, so pottery production is very slow." }
    { group:126, id:10, text: "With hardly any employees, this Potter will produce almost no pottery over the coming year." }
    { group:126, id:11, text: "This workshop needs clay delivered to it, from a Storage Yard or a Clay Pit, to produce pottery." }
    { group:126, id:12, text: "Stored clay," }
    { group:127, id:0, text: "Housing" }
    { group:127, id:1, text: "Turn test mode OFF" }
    { group:127, id:2, text: "Turn test mode ON" }
    { group:127, id:3, text: "Desirability" }
    { group:127, id:4, text: "Ent" }
    { group:127, id:5, text: "H2O" }
    { group:127, id:6, text: "Religion" }
    { group:127, id:7, text: "Education" }
    { group:127, id:8, text: "Bazaar access" }
    { group:127, id:9, text: "Dentist access" }
    { group:127, id:10, text: "Physician access" }
    { group:127, id:11, text: "Health" }
    { group:127, id:12, text: "Food types" }
    { group:127, id:13, text: "Pottery needed" }
    { group:127, id:14, text: "Linen needed" }
    { group:127, id:15, text: "Luxury goods needed" }
    { group:127, id:16, text: "Beer needed" }
    { group:127, id:17, text: "Now" }
    { group:127, id:18, text: "evolves at" }
    { group:127, id:19, text: "needs" }
    { group:127, id:20, text: "occupants" }
    { group:127, id:21, text: " too many." }
    { group:127, id:22, text: "Extra room for" }
    { group:127, id:23, text: "Not visited by a tax collector. Not paying tax" }
    { group:127, id:24, text: "Generated" }
    { group:127, id:25, text: "so far in tax." }
    { group:127, id:26, text: "Residents report no crime at all." }
    { group:127, id:27, text: "This is a peaceful neighborhood." }
    { group:127, id:28, text: "There is some crime here, nothing serious." }
    { group:127, id:29, text: "Crime is becoming a problem." }
    { group:127, id:30, text: "High crime levels are scaring the locals." }
    { group:127, id:31, text: "A lawless area. People fear for their safety." }
    { group:127, id:32, text: "This is a breeding ground for thieves." }
    { group:127, id:33, text: "Huts need food from a Bazaar, and desirable surroundings, before they will improve. " }
    { group:127, id:34, text: "Housing FREE" }
    { group:127, id:35, text: "Housing FREE" }
    { group:127, id:36, text: "Housing FREE" }
    { group:127, id:37, text: "Housing FREE" }
    { group:127, id:38, text: "Housing FREE" }
    { group:127, id:39, text: "Housing FREE" }
    { group:127, id:40, text: "This house will devolve soon. The falling desirability of living in this locality is dragging it down" }
    { group:127, id:42, text: "This house will devolve soon, as it is not visited by a water carrier" }
    { group:127, id:43, text: "This house will devolve soon, as there is no entertainment to be found in the location" }
    { group:127, id:44, text: "This house will devolve soon, as there is hardly any entertainment in the location" }
    { group:127, id:45, text: "This house will devolve soon, as there is too little entertainment in the location" }
    { group:127, id:46, text: "This house will devolve soon. There is some entertainment to be found in the location, but not enough" }
    { group:127, id:47, text: "This house will devolve soon. There is good entertainment to be found in the location, but not enough variety" }
    { group:127, id:48, text: "This house will devolve soon. There is excellent entertainment to be found in the location, but venues are too crowded, or lack enough variety for the discerning scribal classes" }
    { group:127, id:49, text: "This house will devolve soon, as it has not received any supplies of food recently from a local Bazaar" }
    { group:127, id:50, text: "This house will devolve soon, as it currently only has access to a single type of food from its local Bazaar. This discourages the wealthier citizens." }
    { group:127, id:51, text: "This house will devolve soon, as it currently gets only two types of food from its local Bazaar. This is discouraging the scribal classes." }
    { group:127, id:52, text: "This house will devolve soon. It has lost access to a Bazaar." }
    { group:127, id:53, text: "This house will devolve soon. Although it has access to a Bazaar, the Bazaar itself finds it hard to get supplies of food." }
    { group:127, id:54, text: "This house will devolve soon, as it has lost all basic educational facilities provided by either a Scribal School or a Library." }
    { group:127, id:55, text: "This house will devolve soon. Its access to education has been downgraded, as it has lost access to its Library." }
    { group:127, id:56, text: "This house will devolve soon. Its access to education has been downgraded, as it has lost access to its Scribal School." }
    { group:127, id:57, text: "This house will devolve soon. Its previously excellent access to education was downgraded when it lost access to higher education." }
    { group:127, id:58, text: "This house will devolve soon, as it has no access to magistrates from Courthouses." }
    { group:127, id:59, text: "This house will devolve soon. It has run out of pottery, and its local Bazaar has at best an erratic supply." }
    { group:127, id:60, text: "This house will devolve soon, as it has lost all access to local religious facilities." }
    { group:127, id:61, text: "This house will devolve soon. Its access to local religious facilities was reduced to the Temple of only one god." }
    { group:127, id:62, text: "This house will devolve soon. Its previously excellent religious facilities were reduced to the Temples of only two gods." }
    { group:127, id:63, text: "This house will devolve soon, as it has lost Dentist access." }
    { group:127, id:64, text: "This house will devolve soon, as it now has woeful health provision. Not only does it lack access to a Mortician, but Physician access is also less than perfect." }
    { group:127, id:65, text: "This house will devolve soon, as its health provision has been cut. Physician coverage is good, but there is no local access to a Mortuary." }
    { group:127, id:66, text: "This house will devolve soon, as its health provision has been cut. There is local access to a Mortuary, but a Physician's office is hard to find." }
    { group:127, id:67, text: "This house will devolve soon, as it has run out of linen and its local Bazaar has at best an erratic supply." }
    { group:127, id:68, text: "unused8" }
    { group:127, id:69, text: "This house will devolve soon, as it has run out of beer and its local Bazaar has at best an erratic supply." }
    { group:127, id:70, text: "This dwelling cannot evolve until the desirability of the area improves." }
    { group:127, id:71, text: "This house cannot evolve, as it does not have access to even the most primitive water source." }
    { group:127, id:72, text: "This house cannot evolve, as it does not have access to a water carrier's services " }
    { group:127, id:73, text: "This house cannot evolve, as there is no entertainment to be found in the location." }
    { group:127, id:74, text: "This house cannot evolve, as there is hardly any entertainment to be found in the location." }
    { group:127, id:75, text: "This house cannot evolve, as there is too little entertainment to be found in the location." }
    { group:127, id:76, text: "This house cannot evolve, as there is some entertainment to be found in the location, but not enough." }
    { group:127, id:77, text: "This house cannot evolve, as there is good entertainment to be found in the location, but not enough variety." }
    { group:127, id:78, text: "This house cannot evolve, as there is excellent entertainment to be found in the location, but the venues are too crowded or lack enough variety for the discerning scribal classes." }
    { group:127, id:79, text: "This house cannot evolve, as it needs a supply of food from a local Bazaar." }
    { group:127, id:80, text: "This house cannot evolve, as it needs a second type of food, supplied from a local Bazaar, to encourage wealthier Egyptians to move in." }
    { group:127, id:81, text: "This house cannot evolve, as it needs a third type of food, supplied from a local Bazaar, to encourage a higher class of Egyptians to move in." }
    { group:127, id:82, text: "This house cannot evolve, as it does not have access to a local Bazaar." }
    { group:127, id:83, text: "This house cannot evolve. Although it has access to a local Bazaar, the Bazaar itself has trouble getting supplies of food." }
    { group:127, id:84, text: "This house cannot evolve, as it has no basic educational facilities provided by either a Scribal School or a Library." }
    { group:127, id:85, text: "This house cannot evolve, as its access to education needs to be improved by access to a Library." }
    { group:127, id:86, text: "This house cannot evolve, as its access to education needs to be improved by access to a Scribal School." }
    { group:127, id:87, text: "unused line reporting evolution halted by lack of academy access." }
    { group:127, id:88, text: "This house cannot evolve, as it does not have access to a local magistrate from a Courthouse." }
    { group:127, id:89, text: "This house cannot evolve. It needs supplies of pottery provided to it by its local Bazaar before a wealthier class of citizen will move in." }
    { group:127, id:90, text: "This house cannot evolve, as it has no access to any local religious facilities." }
    { group:127, id:91, text: "This house has access to Temples of a single god only. It will not improve until residents can pay homage to other gods." }
    { group:127, id:92, text: "This house has access to Temples of only two gods. It will not improve until residents can pay homage to other gods." }
    { group:127, id:93, text: "This house cannot evolve, as it has no local access to a Dentist." }
    { group:127, id:94, text: "This house cannot evolve, as it effectively has no health provision. It does not have access to a Physician or a Mortuary." }
    { group:127, id:95, text: "This house cannot evolve, as it wants greater health provision. Physician coverage is good, but there is no local access to a Mortuary." }
    { group:127, id:96, text: "This house cannot evolve, as it wants greater health provision. There is local access to a Mortuary, but access to a Physician is needed." }
    { group:127, id:97, text: "This house cannot evolve. It needs supplies of linen provided to it by its local Bazaar before a wealthier class of citizen will move in." }
    { group:127, id:98, text: "unused9" }
    { group:127, id:99, text: "This house cannot evolve. It needs supplies of beer provided to it by its local Bazaar before a wealthier class of citizen will move in." }
    { group:127, id:100, text: "The dwellers of this palace are at the pinnacle of Egyptian society. They want for nothing. Just keeping their needs satisfied is a remarkable achievement!" }
    { group:127, id:101, text: "Local conditions are improving, and this dwelling's owners are upgrading it even now." }
    { group:127, id:102, text: "A nearby building (" }
    { group:127, id:103, text: "is having a detrimental effect on the desirability of the location." }
    { group:127, id:104, text: "This dwelling would soon evolve to one of greater stature if it had more space to expand into." }
    { group:127, id:105, text: "unused10" }
    { group:127, id:106, text: "unused11" }
    { group:127, id:107, text: "House infected for another" }
    { group:127, id:108, text: "This house cannot evolve. Before a wealthier class of citizen will move in, the local Bazaar must supply this dwelling with luxury goods, like" }
    { group:127, id:109, text: "House infested with frogs for another" }
    { group:127, id:110, text: "This house will devolve soon, as its discerning residents want a second type of luxury good, like" }
    { group:127, id:111, text: "(unused)" }
    { group:127, id:112, text: "This house will devolve soon. The idle scribes who live here need a Bazaar to provide luxury goods, like" }
    { group:127, id:113, text: "(unused)" }
    { group:127, id:114, text: "In order to evolve, a Bazaar must provide this house with a second type of luxury good, like" }
    { group:127, id:115, text: "(unused)" }
    { group:127, id:116, text: "(unused)" }
    { group:128, id:0, text: "Unoccupied" }
    { group:128, id:1, text: "This plot is vacant at the moment.  Either the land has not yet been built upon, or the existing home's previous residents fell ill and died.  " }
    { group:128, id:2, text: "This lot is too far from the nearest road. Unless a new road is soon built nearby, the site will revert to open land." }
    { group:129, id:0, text: "from" }
    { group:129, id:1, text: "Capacity" }
    { group:129, id:2, text: "Buys" }
    { group:129, id:3, text: "Sells" }
    { group:129, id:4, text: "Bought" }
    { group:129, id:5, text: "Sold" }
    { group:129, id:6, text: "Anchored, waiting for free Dock" }
    { group:129, id:7, text: "Docked, buying and selling goods" }
    { group:129, id:8, text: "Returning home" }
    { group:129, id:9, text: "Sailing to city Docks" }
    { group:129, id:10, text: "Trading goods" }
    { group:129, id:11, text: "Returning home" }
    { group:129, id:12, text: "Heading to city Storage Yards" }
    { group:129, id:13, text: "Nothing to trade here, just passing through" }
    { group:129, id:14, text: "from" }
    { group:129, id:15, text: "Going to" }
    { group:129, id:16, text: "Returning to" }
    { group:129, id:17, text: "Collecting" }
    { group:129, id:18, text: "Returning with" }
    { group:129, id:19, text: "unit of" }
    { group:129, id:20, text: "units of" }
    { group:129, id:21, text: "Carrying" }
    { group:130, id:0, text: "(not used)" }
    { group:131, id:0, text: "Native hut" }
    { group:131, id:1, text: "Does this text appear anywhere?" }
    { group:132, id:0, text: "Native meeting hut" }
    { group:132, id:1, text: "Is this entry used anywhere?" }
    { group:133, id:0, text: "Simple crops" }
    { group:133, id:1, text: "This entry is probably unused." }
    { group:134, id:0, text: "Mission post" }
    { group:134, id:1, text: "Where did this text appear?" }
    { group:135, id:0, text: "Military Academy" }
    { group:135, id:1, text: "When new soldiers finish their basic training at the Recruiter, they seek to improve in quality and capability at this academy, but cannot until it receives its full quota of staff." }
    { group:135, id:2, text: "With no staff, we cannot polish the skills of the city's new soldiers. They will have to go straight to their Forts and hope for the best." }
    { group:135, id:3, text: "We give green soldiers from the city's Recruiter the extra edge they need to excel in today's Egyptian army." }
    { group:136, id:0, text: "Recruiter" }
    { group:136, id:1, text: "No one can join the Egyptian army without first passing through here; it's the city's training school for new recruits." }
    { group:136, id:2, text: "Weapons Stored" }
    { group:136, id:3, text: "With no staff, we cannot train a single new recruit. Seth help us in times of war!" }
    { group:136, id:4, text: "We are not currently training any recruits, as we have no requests from city Forts or Towers for any new men." }
    { group:136, id:5, text: "We can train new archers quickly enough, but we need weapons to add any infantry or chariots to the city's battalion." }
    { group:136, id:6, text: "We are missing employees, so we can train soldiers at a reduced rate. Without stored weapons, we can train neither infantry nor charioteers." }
    { group:136, id:7, text: "We are understaffed and out of weapons! We can train archers, but only slowly." }
    { group:136, id:8, text: "With a skeleton staff and no supply of weapons, we can just barely train the occasional archer." }
    { group:136, id:9, text: "We train new soldiers at maximum efficiency, and we have the weapons to train any type of soldier." }
    { group:136, id:10, text: "We train new soldiers at reduced speed due to lack of staff, although we do have the weapons to train any type of soldier." }
    { group:136, id:11, text: "We are understaffed and training new soldiers slowly, but we have the weapons to train any type of soldier." }
    { group:136, id:12, text: "With a skeleton staff, we are training new soldiers extremely slowly, even though we have the weapons to train any type of soldier." }
    { group:136, id:13, text: "Chariots Stored" }
    { group:136, id:14, text: "Chariot Stored" }
    { group:136, id:15, text: "Weapon Stored" }
    { group:137, id:0, text: "Plaza" }
    { group:137, id:1, text: "Plazas make ordinary paved roads more desirable, without affecting traffic." }
    { group:138, id:0, text: "'The Lions'" }
    { group:138, id:1, text: "'The Crocodiles'" }
    { group:138, id:2, text: "'The Cobras'" }
    { group:138, id:3, text: "'The Scorpions'" }
    { group:138, id:4, text: "'The Falcons'" }
    { group:138, id:5, text: "'The Rams'" }
    { group:138, id:6, text: "'The Hyenas'" }
    { group:138, id:7, text: "'The Scarabs'" }
    { group:138, id:8, text: "'The Jackals'" }
    { group:138, id:9, text: "'The Adders'" }
    { group:138, id:10, text: "There are no soldiers currently assigned to this fort. Either they are in service abroad, or have yet to arrive from the Recruiter." }
    { group:138, id:11, text: "This company has no soldiers and contributes nothing to our might. With no functional Recruiter to raise new troops, it will remain a hollow unit." }
    { group:138, id:12, text: "Hold ground in tight formation" }
    { group:138, id:13, text: "The company stands its ground, fighting only if attacked. Its soldiers gain combat advantages, but are more vulnerable to missile fire." }
    { group:138, id:14, text: "Hold ground in loose formation" }
    { group:138, id:15, text: "The company fights only if attacked. Soldiers cover more ground and are less vulnerable to missile fire, but their combat abilities suffer." }
    { group:138, id:16, text: "Engage nearby enemies" }
    { group:138, id:17, text: "Under this order, the company attacks, in formation, any enemies foolish enough to come near it." }
    { group:138, id:18, text: "Mop up" }
    { group:138, id:19, text: "When so ordered, the company breaks formation to seek out and attack any enemies it can find." }
    { group:138, id:20, text: "Charge" }
    { group:138, id:21, text: "A company with this order abandons caution and turns all its might to breaking enemy ranks." }
    { group:138, id:22, text: "When so ordered, the company leaves the field and returns to its Fort to replace fallen comrades, rest and revitalize its spirits." }
    { group:138, id:23, text: "Soldiers in company" }
    { group:138, id:24, text: "Soldiers' health" }
    { group:138, id:25, text: "Experience" }
    { group:138, id:26, text: "Perfect" }
    { group:138, id:27, text: "Very good" }
    { group:138, id:28, text: "Good" }
    { group:138, id:29, text: "Average" }
    { group:138, id:30, text: "Poor" }
    { group:138, id:31, text: "Very poor" }
    { group:138, id:32, text: "Appalling" }
    { group:138, id:33, text: "Charioteers" }
    { group:138, id:34, text: "Infantry" }
    { group:138, id:35, text: "Archers" }
    { group:138, id:36, text: "Morale" }
    { group:138, id:37, text: "Panicked!" }
    { group:138, id:38, text: "Terrified" }
    { group:138, id:39, text: "Extremely scared" }
    { group:138, id:40, text: "Very frightened" }
    { group:138, id:41, text: "Frightened" }
    { group:138, id:42, text: "Badly shaken" }
    { group:138, id:43, text: "Shaken" }
    { group:138, id:44, text: "Poor" }
    { group:138, id:45, text: "Quite poor" }
    { group:138, id:46, text: "Below average" }
    { group:138, id:47, text: "Average" }
    { group:138, id:48, text: "Above average" }
    { group:138, id:49, text: "Encouraged" }
    { group:138, id:50, text: "Quite daring" }
    { group:138, id:51, text: "Daring" }
    { group:138, id:52, text: "Bold" }
    { group:138, id:53, text: "Very Bold" }
    { group:138, id:54, text: "Strong" }
    { group:138, id:55, text: "Extremely strong" }
    { group:138, id:56, text: "Excellent" }
    { group:138, id:57, text: "Perfect" }
    { group:138, id:58, text: "Return to Fort" }
    { group:138, id:59, text: "Cursed by Seth!" }
    { group:138, id:60, text: "Green" }
    { group:138, id:61, text: "Skilled" }
    { group:138, id:62, text: "Veteran" }
    { group:138, id:63, text: "Masters" }
    { group:138, id:64, text: "Elite" }
    { group:138, id:65, text: "The best" }
    { group:138, id:66, text: "Hit Points" }
    { group:138, id:67, text: "Melee Attack" }
    { group:138, id:68, text: "Melee Armor" }
    { group:138, id:69, text: "Armor vs Missiles" }
    { group:138, id:70, text: "Missile Attack" }
    { group:138, id:71, text: "Missile Range" }
    { group:138, id:72, text: "Missile ROF" }
    { group:138, id:73, text: "Company" }
    { group:138, id:74, text: "Infantry company" }
    { group:138, id:75, text: "Archer company" }
    { group:138, id:76, text: "Charioteer company" }
    { group:138, id:77, text: "Click here to rotate company's line" }
    { group:138, id:78, text: "Company orders and orientation" }
    { group:139, id:0, text: "Mud Wall" }
    { group:139, id:1, text: "Walls prevent invaders' advance into a city. Invaders can destroy Walls. Thicker Walls are stronger, and allow guards from connected Towers to patrol them." }
    { group:140, id:0, text: "Rubble" }
    { group:140, id:1, text: "These are the ruins of the building named above. Derelict sites like this do little to enhance the location." }
    { group:141, id:0, text: "Irrigation Ditch" }
    { group:141, id:1, text: "This Irrigation Ditch moves water to help fertilize farmland" }
    { group:141, id:2, text: "This Irrigation Ditch is not transporting water to less fertile areas, as it has no source of water from which to draw." }
    { group:142, id:0, text: "New trade route established." }
    { group:142, id:1, text: "To trade these newly available goods, tell your Overseer of Commerce to set the goods' status to Import or Export." }
    { group:142, id:2, text: "Visit overseer?" }
    { group:142, id:3, text: "REMEMBER! Your city needs a Dock before any trade ships can ply this new sea route." }
    { group:143, id:0, text: "Accept goods" }
    { group:143, id:1, text: "Refuse goods" }
    { group:143, id:2, text: "Request food" }
    { group:144, id:0, text: "Click on a city to govern " }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Blank" }
    { group:144, id:3, text: "Blank" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Blank" }
    { group:144, id:6, text: "Blank" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "blank" }
    { group:144, id:9, text: "blank" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "blank" }
    { group:144, id:12, text: "blank" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "blank" }
    { group:144, id:15, text: "blank" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "blank" }
    { group:144, id:18, text: "blank" }
    { group:144, id:19, text: "The close of the Archaic Period" }
    { group:144, id:20, text: "Behdet (Apollinopolis): Dangerous waters" }
    { group:144, id:21, text: "Abedju (Abydos): The Necropolis" }
    { group:144, id:22, text: "The Birth of the Old Kingdom" }
    { group:144, id:23, text: "Selima Oasis: Secure the caravan trails" }
    { group:144, id:24, text: "Abu (Elephantine): Procure new wealth" }
    { group:144, id:25, text: "IX (The Old Kingdom)" }
    { group:144, id:26, text: "blank" }
    { group:144, id:27, text: "blank" }
    { group:144, id:28, text: "The Old Kingdom" }
    { group:144, id:29, text: "Serabit Khadim: The harsh Sinai" }
    { group:144, id:30, text: "Meidum: A tomb of your own" }
    { group:144, id:31, text: "The Age of Pyramids" }
    { group:144, id:32, text: "Buhen: Taming the Nubians" }
    { group:144, id:33, text: "South Dahshur: A new kind of pyramid" }
    { group:144, id:34, text: "XII (The Old Kingdom)" }
    { group:144, id:35, text: "blank" }
    { group:144, id:36, text: "blank" }
    { group:144, id:37, text: "The Age of Pyramids" }
    { group:144, id:38, text: "Iunet (Dendera): A threat from Kush" }
    { group:144, id:39, text: "On (Heliopolis): The quarries of Tura" }
    { group:144, id:40, text: "XIV (The Old Kingdom)" }
    { group:144, id:41, text: "blank" }
    { group:144, id:42, text: "blank" }
    { group:144, id:43, text: "The Height of the Old Kingdom" }
    { group:144, id:44, text: "Bahariya Oasis: The soldiers of Ra" }
    { group:144, id:45, text: "Djedu (Abusir): Worshipping Ra" }
    { group:144, id:46, text: "The Decline of the Old Kingdom" }
    { group:144, id:47, text: "Dunqul Oasis: Drive out the jackals" }
    { group:144, id:48, text: "Dakhla Oasis: Order amid chaos" }
    { group:144, id:49, text: "The First Intermediate Period" }
    { group:144, id:50, text: "Thinis: The war for the Throne" }
    { group:144, id:51, text: "Waset (Thebes): Glory threatened" }
    { group:144, id:52, text: "The Birth of the Middle Kingdom" }
    { group:144, id:53, text: "Kebet (Coptos): Fighting for peace" }
    { group:144, id:54, text: "Menat Khufu (Beni Hasan): Hunger" }
    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "blank" }
    { group:144, id:57, text: "blank" }
    { group:144, id:58, text: "The Middle Kingdom" }
    { group:144, id:59, text: "Iken (Mirgissa): Pushing the border" }
    { group:144, id:60, text: "Sawu (Mersa Gawasis): New traders" }
    { group:144, id:61, text: "The Middle Kingdom" }
    { group:144, id:62, text: "Heh (Semna): Old foes...and new" }
    { group:144, id:63, text: "Bubastis: Egypt's crown jewel" }
    { group:144, id:64, text: "The Second Intermediate Period" }
    { group:144, id:65, text: "Khmun (Hermopolis): Vengeance" }
    { group:144, id:66, text: "Sauty (Lykopolis): Inspiration" }
    { group:144, id:67, text: "New Kingdom: Conquest or Peace?" }
    { group:144, id:68, text: "Byblos: Invade Palestine" }
    { group:144, id:69, text: "Baki (Kuban): A golden age" }
    { group:144, id:70, text: "Final Mission" }
    { group:144, id:71, text: "Rowarty (Avaris): The world becomes ours" }
    { group:144, id:72, text: "Hetepsenusret (Kahun): The grand pyramid" }
    { group:145, id:0, text: "This mission has no winning or losing conditions.  It is about city building, pure and simple." }
    { group:146, id:0, text: "Please confirm that your new resolution has been set correctly (if you can see this, it has!) This message will time out in 10 seconds." }
    { group:146, id:1, text: "Kingdom location not chosen." }
    { group:146, id:2, text: "I am using the default location." }
    { group:146, id:3, text: "Take me to the Kingdom screen!" }
    { group:147, id:0, text: "Well done! By filling your people's bellies with nourishing food and protecting their homes from fire and collapse, you have helped this fledgling civilization take its first step on the long road of history." }
    { group:147, id:1, text: "Excellent. You have built the first true city in this unforgiving land, providing for your citizens' corporal and spiritual needs, and have helped the Thinite confederacy unify the divided land.  " }
    { group:147, id:2, text: "Superb!  Your own citizens are beginning to look to you as their caretaker, and neighboring cities also hail you as a provider in times of need." }
    { group:147, id:3, text: "Well done!  Thanks to your capable leadership, Egyptian civilization has advanced considerably, and will continue to do so in the coming decades." }
    { group:147, id:4, text: "Congratulations.  You have built a capital worthy both of the living and the dead.  And, by developing trade relations with other cities, you have introduced your city to the world's stage." }
    { group:147, id:5, text: "Pharaoh applauds you.  Through your skilled management, you have successfully defended your city from Bedouin attack and provided Egypt with the means of defending itself." }
    { group:147, id:6, text: "Pharaoh is pleased.  You have mastered the seas and river and made good use of the resources they offer.  The mighty navy you built patrols the waterways, securing our borders." }
    { group:147, id:7, text: "Pharaoh smiles at your accomplishments.  You have made the most of what the river and sea have to offer, defending our borders with a small but capable fleet of ships.  You have also honored the nobility by providing them with tombs to house their bodies." }
    { group:147, id:8, text: "Well done!  You have met the twin challenges of securing an important trade route and building a prosperous city that provides for even the most discriminating citizens.  Your achievement is truly noteworthy." }
    { group:147, id:9, text: "Well done!  You have established a thriving city that other Egyptian cities look to as an example and that Nubia looks to with envy. " }
    { group:147, id:10, text: "The feat you have accomplished is unmatched.  With your wisdom, a massive pyramid, unlike anything that has been seen before, stretches toward the sky and guarantees immortality to our beloved Pharaoh." }
    { group:147, id:11, text: "You have managed to overcome the dangers of Sinai and supplied Egypt with copious amounts of precious copper and turquoise.  Your deeds will be remembered for generations." }
    { group:147, id:12, text: "Excellent.  The royal necropolis you have endeavored to build is truly splendid. You and your family's years of dedicated service have been richly rewarded with a sacred tomb of your own." }
    { group:147, id:13, text: "Thanks to your skill, Egypt now claims part of Nubia as its own.  Through the city you have established, you have demonstrated Egypt's strength, wealth and grandeur to the conquered Nubians." }
    { group:147, id:14, text: "Pharaoh commends you.  The bent pyramid you constructed in his honor is magnificent and outshines any monument built in the past." }
    { group:147, id:15, text: "Outstanding.  You have played an integral role in a landmark moment: the construction of the first true pyramid.  With the completion of Snofru's pyramid, you have set the standard of pyramid building that all others will follow." }
    { group:147, id:16, text: "Extraordinary.  In spite of poor conditions and continuous attack from fierce Kushites, you have built a fine city and shored up Egypt's southern border." }
    { group:147, id:17, text: "Splendid.  The mines you established at Tura have furnished all the limestone that Khufu has required . . . so far.  With the strong economy based on the productive Tura mines, your city has reached new cultural and social heights." }
    { group:147, id:18, text: "All in Egypt bow to your accomplishments.  You have built Khufu's massive pyramid and supplied it with the richest of burial provisions, and done great honor to Khafra, constructing his final resting place and his formidable sphinx." }
    { group:147, id:19, text: "Well done.  You have made the most of limited resources and brought Ra's power to this isolated spot." }
    { group:147, id:20, text: "Superb.  The glorious Sun Temple you have built honors both Ra and Pharaoh." }
    { group:147, id:21, text: "You have managed to provide for your people while Egypt crumbles around you.  Your family's skill will serve Egypt well in the difficult times to come." }
    { group:147, id:22, text: "While Egypt falls apart around you, you have managed to hold your city together.  These skills will serve Egypt well in the difficult time to come." }
    { group:147, id:23, text: "Even in times of great unrest, your family's considerable leadership skills have returned Thinis to its prior glory.  Your courageous military has helped the Inyotefs defeat their rivals, a feat that will not soon be forgotten." }
    { group:147, id:24, text: "Through your diligence, you have fed a hungry people during a time of war and supplied the necessary reinforcements to defeat this enemy once and for all.  Your accomplishments will not soon be forgotten." }
    { group:147, id:25, text: "Your tireless efforts have given the Kingdom a beautiful and stately new city.  You have also done much for all of Egypt, feeding hungry people in their time of need.  Your considerable efforts shall not go unrewarded." }
    { group:147, id:26, text: "The fine pyramids and obelisks you have built for me stand as testament to my reign, and for that I am deeply grateful.  Your dedication shall be rewarded." }
    { group:147, id:27, text: "Through your unselfish dedication to providing for your people, Egypt now accepts you as the rightful Pharaoh and looks to your dynasty to produce equally benevolent and resourceful heirs. " }
    { group:147, id:28, text: "All bow to your glory, mighty Pharaoh.  You have successfully conquered northern Nubia, while simultaneously providing our Red Sea port with the resources it needed to thrive, assuring that our military forces will have a reliable source of copper." }
    { group:147, id:29, text: "All hail the wise and resourceful Pharaoh.  The new Red Sea trade port is booming, and your support helped establish an equally strong trading post in Nubia." }
    { group:147, id:30, text: "Seth must truly smile upon you, Most Martial Pharaoh.  You have successfully driven out the Nubians, sealing your southern border." }
    { group:147, id:31, text: "The gleaming city of Bubastis does credit to you, Most Capable Pharaoh, and to all Egypt." }
    { group:147, id:32, text: "Egypt rejoices!  The Hyksos have been expelled from our land, and, under your leadership, Egypt is reclaimed. " }
    { group:147, id:33, text: "You successfully inspired your generals to great victories on the field with promises of life everlasting.  The Hyksos and their fearsome chariots have been driven out of Egypt." }
    { group:147, id:34, text: "All-powerful Pharaoh, by turning back the Hittites, Egypt has grown into a mighty empire!  Your sword has given the gift of Egyptian civilization to the world." }
    { group:147, id:35, text: "Most peaceful Pharaoh, your calming influence has brought Egypt to the brink of new greatness!" }
    { group:147, id:36, text: "All hail the mighty Pharaoh!  Your dynasty has no peer, and Egyptians from now until the end of time will speak your name with the greatest reverence." }
    { group:147, id:37, text: "All hail the mighty Pharaoh! Your dynasty is without equal, and Egyptians from now until the end of time will speak your name with the greatest reverence." }
    { group:147, id:38, text: "Well done.  The tomb for Thutmose I is complete, an extraordinary accomplishment!  Pharaoh is confident that such a beautifully decorated tomb will please the gods and speed his journey into the afterlife." }
    { group:147, id:39, text: "An impressive feat!  It is rare indeed when workers under such pressure can produce such fine handiwork.  Tutankhamun's tomb is now safely sealed for all eternity.  Let us hope heretic robbers never discover his resting place!" }
    { group:147, id:40, text: "An excellent job!  You managed to adequately guard the royal tombs in the Valley and complete the new tomb as ordered.  Pharaoh Seti is most pleased with the exquisite craftsmanship of your workers." }
    { group:147, id:41, text: "A job well done!  Our great pharaoh, Ramses II, did not err when he chose you to oversee the commercial and military development of this land.  But danger rides the wind!  Hittite armies have again arisen to contest our rightful control of this most valuable region. " }
    { group:147, id:42, text: "The hand of Pharaoh has once again beaten the loathsome Hittites.  Great is the rejoicing for our most wise and brave leader, Ramses II!  Your splendid victory in this hard-fought battle will surely be recorded forever in the annals of history." }
    { group:147, id:43, text: "A job well done!  Ramses II is quite pleased with the colossal monument that you created in his honor at Abu Simbel." }
    { group:147, id:44, text: "Well done!  Despite a seemingly unending series of vile plagues and misfortunes, the grand tomb for our aging pharaoh is fully prepared.  Its grandeur speaks well for our appreciation of Ramses II, surely one of Egypt's greatest leaders." }
    { group:147, id:45, text: "The sun has lifted the storm cloud that had been over Egypt.  Great is the joy!  The vile chief of the Libu and his allies from the sea have fled under cover of the night.  Their ill-conceived plan to settle along our shores has been smashed. It is indeed fortunate for us that so many of their women and children are now our shameful captives." }
    { group:147, id:46, text: "Well done!  Your personal courage and steadfastness in battle inspired your troops to perform to their utmost.  The accursed Assyrians have been ingraciously expelled from Egypt's soil.  Word of your deed has reached the Pharaoh and he is indeed pleased." }
    { group:147, id:47, text: "Hail to the hero of Tanis, protector of Egypt!  Your glorious victories on land and on water have secured Egypt's continued independence.  The once-powerful Persians now quake before they speak the name of Pharaoh Achoris." }
    { group:147, id:48, text: "You have done well.  Your wise leadership and careful planning have positioned Alexandria to be the hub of Mediterranean commerce.  It is most unfortunate that Alexander the Great never saw his empire's capital.  At least we have the satisfaction to know that he is now safely entombed within it." }
    { group:147, id:49, text: "The metropolis of Alexandria now shines as a beacon to the world!  Its Great Library is unsurpassed as a center for scholastic learning, and the towering Pharos Lighthouse is already one of the true wonders of the world." }
    { group:147, id:50, text: "Your mighty legions have crushed Ptolemy XIII's rabble.  His drowned body was dredged from the Nile as proof of his death.  The siege has been lifted and Cleopatra is now secure on her throne.  To celebrate the victory and further cement their relationship, Caesar and Cleopatra are now embarked on a journey up the Nile aboard the luxurious royal barge." }
    { group:147, id:51, text: "The splendors of Alexandria and the fate of Egypt are in good hands under your direction.  As expected, when you finally blessed Mark Antony with your presence, he paid you proper homage while seeking your financial aid in furthering his goals.  In fact, he became so enamored of you that he has come to Alexandria to be your companion and lover." }
    { group:147, id:52, text: "With Cleopatra's deep treasury and Antony's genius for tactics, Octavian's fleet and veteran legions have been scattered to the four winds. Romans impatiently await the triumphant return of Antony and Cleopatra. Hand in hand, Rome and Alexandria will rule the Mediterranean for many more generations." }
    { group:147, id:53, text: "Custom Mission Victory" }
    { group:147, id:54, text: "You have done well, but many more challenges await you on your quest to become...Pharaoh! " }
    { group:148, id:0, text: "Final Culture rating" }
    { group:148, id:1, text: "Final Prosperity rating" }
    { group:148, id:2, text: "Final Monument rating" }
    { group:148, id:3, text: "Final Kingdom Rating" }
    { group:148, id:4, text: "Final population" }
    { group:148, id:5, text: "Final city funds" }
    { group:148, id:6, text: "Monuments Erected" }
    { group:148, id:7, text: "Mission was completed in" }
    { group:148, id:8, text: "Least-difficult level:" }
    { group:148, id:9, text: "Score:" }
    { group:148, id:10, text: "Congratulations.  You can go back and try to beat your score by clicking the 'Choose a Mission' button." }
    { group:148, id:11, text: "You did better the last time you played this mission. " }
    { group:148, id:12, text: "Great job!  You beat your last score for this mission!" }
    { group:148, id:13, text: "You completed this mission successfully, but [player_name] still reigns supreme in this city." }
    { group:148, id:14, text: "You now hold the high score for this mission!  You have bested [player_name]'s achievement." }
    { group:148, id:15, text: "months" }
    { group:148, id:16, text: "You cheated! Your score is not worthy for inclusion with the Best Families." }
    { group:149, id:0, text: "General Request" }
    { group:149, id:1, text: "Egyptian city under attack" }
    { group:149, id:2, text: "Distant battle" }
    { group:149, id:3, text: "Festival" }
    { group:149, id:4, text: "Construction" }
    { group:149, id:5, text: "Famine" }
    { group:149, id:6, text: "Threat" }
    { group:150, id:0, text: "Egyptian city saved" }
    { group:150, id:1, text: "distant battle won" }
    { group:150, id:2, text: "distant battle lost" }
    { group:150, id:3, text: "acknowledgement" }
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
    { group:151, id:11, text: "Hetepsekhemwy " }
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
    { group:151, id:32, text: "Queen Merneith" }
    { group:151, id:33, text: "Narmer" }
    { group:151, id:34, text: "Nebka" }
    { group:151, id:35, text: "Neferhotep I " }
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
    { group:151, id:57, text: "Queen Sobknefru" }
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
    { group:151, id:79, text: "Seti I" }
    { group:151, id:80, text: "Ramses II" }
    { group:151, id:81, text: "Merneptah" }
    { group:151, id:82, text: "Amenmes" }
    { group:151, id:83, text: "Seti II" }
    { group:151, id:84, text: "Siptah" }
    { group:151, id:85, text: "Queen Twosret" }
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
    { group:151, id:106, text: "Alexander the Great" }
    { group:151, id:107, text: "Philip Arrhidaeus" }
    { group:151, id:108, text: "Alexander IV" }
    { group:151, id:109, text: "Ptolemy I" }
    { group:151, id:110, text: "Ptolemy II" }
    { group:151, id:111, text: "Ptolemy III" }
    { group:151, id:112, text: "Ptolemy IV" }
    { group:151, id:113, text: "Ptolemy V" }
    { group:151, id:114, text: "Ptolemy VI" }
    { group:151, id:115, text: "Ptolemy VII" }
    { group:151, id:116, text: "Ptolemy VIII" }
    { group:151, id:117, text: "Ptolemy IX" }
    { group:151, id:118, text: "Ptolemy X" }
    { group:151, id:119, text: "Ptolemy XI" }
    { group:151, id:120, text: "Ptolemy XII" }
    { group:151, id:121, text: "Queen Bernice IV" }
    { group:151, id:122, text: "Ptolemy XIII" }
    { group:151, id:123, text: "Cleopatra VII" }
    { group:151, id:124, text: "Ptolemy XV" }
    { group:152, id:0, text: "None" }
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
    { group:154, id:0, text: "Hunting Lodge" }
    { group:154, id:1, text: "Hunters based here track and hunt local wildlife. The Hunting Lodge then distributes game meat to local Storage Yards or Granaries." }
    { group:154, id:2, text: "Production is" }
    { group:154, id:3, text: "complete." }
    { group:154, id:4, text: "The Overseer of Commerce decreed that hunting should cease." }
    { group:154, id:5, text: "This lodge has no workers. The hunt is cancelled." }
    { group:154, id:6, text: "This lodge has all the workers it needs. The hunters are stalking every herd they can find." }
    { group:154, id:7, text: "This lodge is working below maximum capacity. Food collection will be slower as a result." }
    { group:154, id:8, text: "This lodge is understaffed, and it takes longer to collect meat than it should." }
    { group:154, id:9, text: "Very few people work here. Meat collection is slow, indeed." }
    { group:154, id:10, text: "With hardly any hunters working here, prey animals cavort unmolested. It could be a very hungry dry season..." }
    { group:154, id:11, text: "This lodge's hunters are out seeking prey." }
    { group:154, id:12, text: "It takes too long for meat to get back to the lodge. Try putting it closer to wildlife." }
    { group:154, id:13, text: "Stored meat," }
    { group:155, id:0, text: "Roadblock" }
    { group:155, id:1, text: "Place roadblocks to restrict walkers' patrol routes. People with specific destinations (like delivery men or Bazaar buyers) can pass freely." }
    { group:156, id:0, text: "Free Event" }
    { group:156, id:1, text: "Request" }
    { group:156, id:2, text: "Invasion" }
    { group:156, id:3, text: "Earthquake" }
    { group:156, id:4, text: "Revolt" }
    { group:156, id:5, text: "Change Pharaoh" }
    { group:156, id:6, text: "Sea trade problem" }
    { group:156, id:7, text: "Land trade problem" }
    { group:156, id:8, text: "Wage increase" }
    { group:156, id:9, text: "Wage decrease" }
    { group:156, id:10, text: "Contaminated water" }
    { group:156, id:11, text: "Gold Mine collapse" }
    { group:156, id:12, text: "Clay Pit flood" }
    { group:156, id:13, text: "Demand increase" }
    { group:156, id:14, text: "Demand decrease" }
    { group:156, id:15, text: "Price increase" }
    { group:156, id:16, text: "Price decrease" }
    { group:156, id:17, text: "Kingdom Increase" }
    { group:156, id:18, text: "Kingdom Decrease" }
    { group:156, id:19, text: "City Status Change" }
    { group:156, id:20, text: "Message Event" }
    { group:156, id:21, text: "Failed Flood" }
    { group:156, id:22, text: "Perfect Flood" }
    { group:156, id:23, text: "Gift" }
    { group:156, id:24, text: "Plague of locusts" }
    { group:156, id:25, text: "Plague of frogs" }
    { group:156, id:26, text: "Hailstorm" }
    { group:156, id:27, text: "River of blood" }
    { group:156, id:28, text: "Crime wave" }
    { group:156, id:29, text: "Mummy" }
    { group:157, id:0, text: "Osiris" }
    { group:157, id:1, text: "Ra" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Seth" }
    { group:157, id:4, text: "Bast" }
    { group:157, id:5, text: "Hermie" }
    { group:157, id:6, text: "Janus" }
    { group:158, id:0, text: "God of Agriculture and the Nile Flood" }
    { group:158, id:1, text: "God of the Kingdom" }
    { group:158, id:2, text: "God of Craftsmen" }
    { group:158, id:3, text: "God of Destruction" }
    { group:158, id:4, text: "Goddess of the Home" }
    { group:158, id:5, text: "(Dentistry)" }
    { group:158, id:6, text: "(Everything)" }
    { group:159, id:0, text: "Ferry Landing" }
    { group:159, id:1, text: "WARNING! This Ferry Landing lacks a linked site across the river. No one can cross." }
    { group:159, id:2, text: "WARNING! This ferry's associated landing site lacks road access. Only migrants can cross." }
    { group:159, id:3, text: "WARNING! This ferry's associated landing site has labor problems. Only migrants can cross." }
    { group:160, id:0, text: "January" }
    { group:160, id:1, text: "February" }
    { group:160, id:2, text: "March" }
    { group:160, id:3, text: "April" }
    { group:160, id:4, text: "May" }
    { group:160, id:5, text: "June" }
    { group:160, id:6, text: "July" }
    { group:160, id:7, text: "August" }
    { group:160, id:8, text: "September" }
    { group:160, id:9, text: "October" }
    { group:160, id:10, text: "November" }
    { group:160, id:11, text: "December" }
    { group:161, id:0, text: "Shrine to Osiris (Agriculture)" }
    { group:161, id:1, text: "Osiris brings fertility to the land and makes the crops grow. Appease him, or prepare to go hungry." }
    { group:161, id:2, text: "Shrine to Ra (The Kingdom)" }
    { group:161, id:3, text: "Merchants know well the value in pleasing Ra. Trade is safer and more profitable with Ra's blessing, and your city's esteem is greater." }
    { group:161, id:4, text: "Shrine to Ptah (Craftsman)" }
    { group:161, id:5, text: "Laborers and craftsmen worship Ptah to ease their toil. When Ptah is angered, no industry is safe from catastrophe." }
    { group:161, id:6, text: "Shrine to Seth (Destruction)" }
    { group:161, id:7, text: "Seth watches over soldiers and encourages valor in combat. No man dares fight without the blessing of Seth." }
    { group:161, id:8, text: "Shrine to Bast (Home)" }
    { group:161, id:9, text: "When Bast is displeased, nobody's home is safe. Some blame Bast for disease, too." }
    { group:162, id:0, text: "Gold Mine" }
    { group:162, id:1, text: "Mining gold is the most direct way to fill your city's treasury. Lucky is the city that has this precious resource, for its wealth is assured." }
    { group:162, id:2, text: "Production is" }
    { group:162, id:3, text: "complete." }
    { group:162, id:4, text: "The Overseer of Commerce commanded an end to gold mining." }
    { group:162, id:5, text: "This mine has no workers. No ore whatsoever can be extracted." }
    { group:162, id:6, text: "This mine has all the workers it needs, and produces a small fortune in gold." }
    { group:162, id:7, text: "This mine is working below maximum capacity. It would yield more gold if there were more miners." }
    { group:162, id:8, text: "This mine is understaffed. It produces less gold than it could." }
    { group:162, id:9, text: "Very few people work here. Gold output is rather anemic." }
    { group:162, id:10, text: "With hardly any workers here, mining has nearly stopped. Very little gold will come of this." }
    { group:163, id:0, text: "Gemstone Mine" }
    { group:163, id:1, text: "Mine gems for export, or to produce jewelry, your city's basic luxury good." }
    { group:163, id:2, text: "Production is" }
    { group:163, id:3, text: "complete." }
    { group:163, id:4, text: "Your Overseer of Commerce ruled that the city has enough gems, and halted mining." }
    { group:163, id:5, text: "This mine has no workers. Precious stones remain locked forever in the rock." }
    { group:163, id:6, text: "This mine has all the workers it needs, and produces glittering mounds of gems." }
    { group:163, id:7, text: "This mine has some job openings, and gem production is less efficient than it could be." }
    { group:163, id:8, text: "This mine is understaffed. It produces considerably fewer gems than it could." }
    { group:163, id:9, text: "Very few miners work here. Teasing gems from rock is very slow going indeed." }
    { group:163, id:10, text: "With hardly any workers here, almost no gems are being mined." }
    { group:164, id:0, text: "Firehouse" }
    { group:164, id:1, text: "Firehouses send marshals into the city to prevent fires, and to fight those that do break out. " }
    { group:164, id:2, text: "Our marshal is patrolling the streets." }
    { group:164, id:3, text: "Our marshal is preparing for duty." }
    { group:164, id:4, text: "Currently our duty roster is full. Our marshals are always out there, sniffing out evidence of fire." }
    { group:164, id:5, text: "We are a little short of marshals. We have gaps of perhaps a day or two in our coverage." }
    { group:164, id:6, text: "We are understaffed. There are delays of up to a week in fire prevention patrols." }
    { group:164, id:7, text: "We have far too few men. Often, no marshals leave the Firehouse for up to two weeks at a time." }
    { group:164, id:8, text: "We are operating with desk staff only. We frequently go a full month without sending a marshal out on the streets." }
    { group:164, id:9, text: "With no staff, this Firehouse is little more than a fire waiting to happen." }
    { group:165, id:0, text: "Brick Wall" }
    { group:165, id:1, text: "Walls prevent invaders' advance into a city. Invaders can destroy Walls. Thicker Walls are stronger, and allow guards from connected Towers to patrol them. " }
    { group:166, id:0, text: "Wall" }
    { group:166, id:1, text: "Walls prevent invaders' advance into a city. Invaders can destroy Walls. Thicker Walls are stronger, and allow guards from connected Towers to patrol them." }
    { group:167, id:0, text: "Brick Gatehouse" }
    { group:167, id:1, text: "Walls need a Gatehouse so that migrants and traders can come and go freely." }
    { group:168, id:0, text: "Gatehouse" }
    { group:168, id:1, text: "Walls need a Gatehouse so that migrants and traders can come and go freely." }
    { group:169, id:0, text: "Brick Tower" }
    { group:169, id:1, text: "Build Towers into your Walls at regular intervals, or at least in vulnerable areas. When connected to roads, Towers receive guards from the city's Recruiter. Tower guards rain javelins on nearby invaders and patrol thick enough Walls." }
    { group:169, id:2, text: "With no workers, we cannot staff the Towers or hire guards to patrol the Walls." }
    { group:169, id:3, text: "Our men are alert and ready to repel any attacks." }
    { group:169, id:4, text: "We have maintenance staff, but we need guards from a Recruiter to defend the city." }
    { group:170, id:0, text: "Tower" }
    { group:170, id:1, text: "Build towers into your Walls at regular intervals, or at least in vulnerable areas. When connected to roads, Towers receive guards from the city's Recruiter. Tower guards rain javelins on nearby invaders and patrol thick enough Walls." }
    { group:170, id:2, text: "With no workers, we cannot man our Towers or hire guards to patrol the Walls." }
    { group:170, id:3, text: "Our men are alert and ready to repel any attacks." }
    { group:170, id:4, text: "We have maintenance staff, but we need guards from a Recruiter to defend the city." }
    { group:171, id:0, text: "Carpenters' Guild" }
    { group:171, id:1, text: "Carpenters gather here to swap stories and tips about their profession, find work assignments and hammer out their problems." }
    { group:171, id:2, text: "Production is" }
    { group:171, id:3, text: "complete." }
    { group:171, id:4, text: "This guild has been shuttered by your Overseer of Commerce" }
    { group:171, id:5, text: "This guild has no employees. Carpentry services are not available." }
    { group:171, id:6, text: "This guild has all the employees it needs. Carpenters can work with maximal efficiency." }
    { group:171, id:7, text: "This guild is working below maximum capacity. Work will be slightly slower as a result." }
    { group:171, id:8, text: "This guild is understaffed, and supplies fewer carpenters than it could." }
    { group:171, id:9, text: "Very few people work here. There is a considerable wait for a carpenter's services." }
    { group:171, id:10, text: "With hardly any employees at this guild, it seems to take forever for a carpenter to show up." }
    { group:171, id:11, text: "This workshop needs wood delivered to it." }
    { group:171, id:12, text: "Stored wood," }
    { group:172, id:0, text: "Bricklayers' Guild" }
    { group:172, id:1, text: "Bricklayers gather here to swap stories and tips about their profession, find work assignments and lay plans for the future. " }
    { group:172, id:2, text: "Production is" }
    { group:172, id:3, text: "complete." }
    { group:172, id:4, text: "This guild has been shut down by your Overseer of Commerce" }
    { group:172, id:5, text: "This guild has no employees. No bricks can be laid." }
    { group:172, id:6, text: "This guild has all the employees it needs. Bricklayers can work with maximal efficiency." }
    { group:172, id:7, text: "This guild is working below maximum capacity. Work will be slightly slower as a result." }
    { group:172, id:8, text: "This guild is understaffed, and supplies fewer bricklayers than it could." }
    { group:172, id:9, text: "Very few people work here. There is a substantial wait for bricklaying services." }
    { group:172, id:10, text: "With hardly any employees at this guild, it seems to take forever for a bricklayer to show up." }
    { group:172, id:11, text: "This guild provides skilled workers for monument construction. It does not need its own supply of bricks." }
    { group:172, id:12, text: "Stored bricks," }
    { group:173, id:0, text: "Stonemasons' Guild" }
    { group:173, id:1, text: "Stonemasons meet here to swap stories and tips about their profession, find work assignments and hew plans for the future. " }
    { group:173, id:2, text: "Production is" }
    { group:173, id:3, text: "complete." }
    { group:173, id:4, text: "This guild has been shut down by your Overseer of Commerce" }
    { group:173, id:5, text: "This guild has no employees. Stonecarving is not possible." }
    { group:173, id:6, text: "This guild has all the employees it needs. Stonemasons can work with maximal efficiency." }
    { group:173, id:7, text: "This guild is working below maximum capacity. Work will be slightly slower as a result." }
    { group:173, id:8, text: "This guild is understaffed, and provides fewer stonemasons than it could." }
    { group:173, id:9, text: "Very few people work here. There is a lengthy wait for stonemasonry." }
    { group:173, id:10, text: "With hardly any employees at this guild, it seems to take forever for a stonemason to report for duty." }
    { group:173, id:11, text: "This guild provides skilled workers for monument construction. It does not need its own supply of stone." }
    { group:173, id:12, text: "Stored stone," }
    { group:174, id:0, text: "Transport Wharf" }
    { group:174, id:1, text: "Transport ships, built by Shipwrights, moor here between assignments. Your battalion needs transports to navigate the Nile." }
    { group:174, id:2, text: "Our transport is in port." }
    { group:174, id:3, text: "Our transport is off transporting." }
    { group:175, id:0, text: "Warship Wharf" }
    { group:175, id:1, text: "A warship berths here between battles. Any city on the Nile ought to have at least a couple of defensive ships at the ready." }
    { group:175, id:2, text: "Our warship is in port." }
    { group:175, id:3, text: "Our warship is out defending the city against invasion." }
    { group:176, id:0, text: "Courthouse" }
    { group:176, id:1, text: "Courthouses send forth magistrates, who help to reduce crime by ensuring that all grievances get a fair hearing. Courthouse vaults hold part of your city's treasury." }
    { group:176, id:2, text: "This Courthouse has no workers at all, so local citizens solve their own disputes in whatever ways they can." }
    { group:176, id:3, text: "There are so few magistrates available that legal decisions seem almost random to the plaintiffs." }
    { group:176, id:4, text: "With only half the workers it needs, this Courthouse sometimes rushes to judgment." }
    { group:176, id:5, text: "Because it is slightly understaffed, this Courthouse has a small backlog of cases to hear." }
    { group:176, id:6, text: "The Courthouse has all the staff it needs to hear citizens' complaints swiftly and dispatch careful decisions." }
    { group:176, id:7, text: "The magistrate is out resolving disputes." }
    { group:176, id:8, text: "The magistrate is in his chambers." }
    { group:176, id:9, text: "Vault holds" }
    { group:177, id:0, text: "This farmland is irrigated." }
    { group:177, id:1, text: "This farmland is not irrigated." }
    { group:177, id:2, text: "The next floods will come in" }
    { group:177, id:3, text: "This area offers highly fertile land, now that the river has subsided." }
    { group:177, id:4, text: "This area will offer highly fertile land once the river subsides." }
    { group:177, id:5, text: "This farm needs laborers, who can be trained at a Work Camp." }
    { group:177, id:6, text: "This farm has a full crew of laborers working the fields." }
    { group:178, id:0, text: "complete. " }
    { group:178, id:1, text: "Workers are now finishing the outside of the pyramid." }
    { group:178, id:2, text: "This task is" }
    { group:178, id:3, text: "First, workers need to clear the pyramid site down to bedrock.  More peasants from Work Camps could speed the leveling process." }
    { group:178, id:4, text: "First, workers need to clear the mastaba site down to bedrock.  More peasants from Work Camps could speed the leveling process." }
    { group:178, id:5, text: "Workers are now cutting grooves into the bedrock to hold water.  More peasants from Work Camps would hasten this job." }
    { group:178, id:6, text: "Now we're filling the grooves in the bedrock with water.  More peasants from Work Camps could make this go more quickly." }
    { group:178, id:7, text: "Workers are marking the water level, then draining water from the grooves.    " }
    { group:178, id:8, text: "We're very carefully cutting the bedrock down to the water-level marks.  No one will ever see this work, but it ensures that the monument will endure forever." }
    { group:178, id:9, text: "The water-level grooves are being filled with rubble.  It has to be tightly compacted so that the monument won't settle over time." }
    { group:178, id:10, text: "Site preparation is finished!  We've leveled the land, and now we're ready to build the tomb." }
    { group:178, id:11, text: "The base has been leveled and a roof is being placed on the tomb.  Now, there's a resting place fit for eternity." }
    { group:178, id:12, text: "Construction Foreman" }
    { group:178, id:13, text: "Do you think gods from the sky are going to build this monument?  Build some Work Camps so that I can get some peasant labor, and quickly!" }
    { group:178, id:14, text: "There are no stonemasons available to work on this monument.  If you want progress, build a Stonemasons' Guild at once!" }
    { group:178, id:15, text: "I suppose the bricks for this project will magically assemble themselves.  That must be your plan, since you haven't built a Bricklayers' Guild." }
    { group:178, id:16, text: "With no Carpenters' Guild in the city to build ramps or scaffolds, I hope that you're planning on a very short monument!  " }
    { group:178, id:17, text: "No peasants have reported for duty.  I'd find out why, if I were you.  Maybe your Work Camps are more like sleep camps." }
    { group:178, id:18, text: "Impressive heap of stone, isn't it?  And that's all it's ever going to be, unless some stonemasons show up.  The Stonemasons' Guild in this city won't win any awards for productivity..." }
    { group:178, id:19, text: "Between you and me, the Bricklayers' Guild in this city must be some kind of recreation club.  It's not sending me any bricklayers, that's for certain." }
    { group:178, id:20, text: "I need a carpenter here, and I need him now!  Why don't you apply your leadership skills at that good-for-nothing Carpenters' Guild?" }
    { group:178, id:21, text: "An awful lot of people are standing around waiting for a carpenter to show up.  He sure does take his sweet time getting here.  " }
    { group:178, id:22, text: "A stonemason without stone is sad to see. Quarry or import more plain stone, or this monument will never take form." }
    { group:178, id:23, text: "You had best quarry or import more limestone, if stonemasons are to build a monument during our lifetimes." }
    { group:178, id:24, text: "Unless the city imports or quarries more sandstone, our stonemason is going to enjoy an early retirement." }
    { group:178, id:25, text: "It won't be much of a monument, with the paltry supply of granite I'm seeing.  Quarry or import more of it." }
    { group:178, id:26, text: "Unless you import more marble, our stonemasons will never be able to finish this monument." }
    { group:178, id:27, text: "Our bricklayers need a lot more bricks than they're getting.  If we can't make them, maybe you can import some." }
    { group:178, id:28, text: "My carpenters lament the shortage of wood.  Cut more trees, or step up the imports." }
    { group:178, id:29, text: "Our masons are ready to add copper to the roof if only it would arrive.  Mine or import more of it." }
    { group:178, id:30, text: "Workers are just clearing and leveling the construction site now.  This would be a fine time to amass some plain stone and limestone.  We are going to need plenty." }
    { group:178, id:31, text: "Everything seems to be going just fine, and the pyramid continues to rise higher and higher." }
    { group:178, id:32, text: "The masons are now doing the fine stone work.  We won't need any more limestone to finish this job." }
    { group:178, id:33, text: "Workers are just clearing and leveling the construction site now.  After that, we'll need plenty of bricks and limestone to complete this monument." }
    { group:178, id:34, text: "Everything seems to be going just fine, and the pyramid continues to rise higher and higher." }
    { group:178, id:35, text: "The masons are now doing the fine stone work.  We won't need any more bricks or limestone to finish this job." }
    { group:178, id:36, text: "Workers are just clearing and leveling the construction site now.  After that, we'll need plenty of plain stone to build this monument." }
    { group:178, id:37, text: "Everything seems to be going just fine, and the pyramid continues to rise step by step." }
    { group:178, id:38, text: "At last, the pyramid is complete!" }
    { group:178, id:39, text: "Workers are just clearing the construction site now.  After that, we'll need plenty of bricks for the mastaba." }
    { group:178, id:40, text: "Everything seems to be going just fine.  This mastaba will be done in no time." }
    { group:178, id:41, text: "The mastaba is complete." }
    { group:178, id:42, text: "Finally we have all the granite we need.  Once my carpenters finish building the scaffolding, stonemasons can begin carving the obelisk." }
    { group:178, id:43, text: "My stonemasons are hard at work carving the mighty obelisk." }
    { group:178, id:44, text: "The obelisk is complete!" }
    { group:178, id:45, text: "Masons are creating the rough shape of the sphinx." }
    { group:178, id:46, text: "Masons are doing some fine carving on the sphinx." }
    { group:178, id:47, text: "Workers are finishing and painting the sphinx." }
    { group:178, id:48, text: "The sphinx is complete!" }
    { group:178, id:49, text: "Carpentry is " }
    { group:178, id:50, text: "Mason work is " }
    { group:178, id:51, text: "All of the city's peasants are needed on the floodplain farms, leaving them only three months out of the year to work on this project.  Build more Work Camps near the monument site to speed things up." }
    { group:178, id:52, text: "Workers can't get to the monument's staging area.  See what's blocking the planks that mark it." }
    { group:178, id:53, text: "Now that we have enough sandstone, we can begin work on the sun temple. My workers are just clearing the site now." }
    { group:178, id:54, text: "Once my carpenters finish building the scaffolding, masons can begin carving the central obelisk for the sun temple." }
    { group:178, id:55, text: "My masons are carving the central obelisk now. When they're done, we'll need more sandstone to finish the rest of the sun temple." }
    { group:178, id:56, text: "As soon as we finish the vestibule, wall and foretemple, this monument will be complete." }
    { group:178, id:57, text: "The sun temple is complete! " }
    { group:178, id:58, text: "Now that we've got enough sandstone, we can start on this monument. My workers are clearing the site now." }
    { group:178, id:59, text: "Masons are working hard to complete this mausoleum.  Everything's on schedule, and I don't expect any problems." }
    { group:178, id:60, text: "The mausoleum is complete." }
    { group:178, id:61, text: "The [monument_name] is [percent_complete] complete." }
    { group:178, id:62, text: "No courses have been completely laid in place yet. " }
    { group:178, id:63, text: "One course has been completely laid in place. " }
    { group:178, id:64, text: "[number_courses_complete] courses have been completely laid in place. " }
    { group:178, id:65, text: "The current course requires [quantity_needed_current_course_main] ([number_loads_current_course_main]) to complete." }
    { group:178, id:66, text: "The current course requires [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) to complete." }
    { group:178, id:67, text: "The current course requires [quantity_needed_current_course_main] ([number_loads_current_course_main]) and [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) to complete." }
    { group:178, id:68, text: "The remainder of the [monument_name] will require an additional [quantity_needed_remainder_main] ([number_loads_remainder_main]). " }
    { group:178, id:69, text: "The remainder of the [monument_name] will require an additional [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:70, text: "The remainder of the [monument_name] will require an additional [quantity_needed_remainder_main] ([number_loads_remainder_main]) and [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:71, text: "The [monument_name] is now complete, and contains a total of [quantity_total_main]." }
    { group:178, id:72, text: "The [monument_name] is now complete, and contains a total of [quantity_total_main] and [quantity_total_secondary]." }
    { group:178, id:73, text: "mastaba" }
    { group:178, id:74, text: "pyramid" }
    { group:178, id:75, text: "stepped pyramid" }
    { group:178, id:76, text: "bent pyramid" }
    { group:178, id:77, text: "brick pyramid" }
    { group:178, id:78, text: "obelisk" }
    { group:178, id:79, text: "sphinx" }
    { group:178, id:80, text: "sun temple" }
    { group:178, id:81, text: "Alexandria library" }
    { group:178, id:82, text: "Abu Simbel" }
    { group:178, id:83, text: "Small Royal Burial Tomb" }
    { group:178, id:84, text: "Medium Royal Burial Tomb" }
    { group:178, id:85, text: "Large Royal Burial Tomb" }
    { group:178, id:86, text: "Grand Royal Burial Tomb" }
    { group:178, id:87, text: "Caesareum" }
    { group:178, id:88, text: "lighthouse" }
    { group:178, id:89, text: "mausoleum" }
    { group:178, id:90, text: "blocks of plain stone" }
    { group:178, id:91, text: "blocks of limestone" }
    { group:178, id:92, text: "blocks of granite" }
    { group:178, id:93, text: "blocks of sandstone" }
    { group:178, id:94, text: "bricks" }
    { group:178, id:95, text: "blocks of marble" }
    { group:178, id:96, text: "ingots of copper" }
    { group:178, id:97, text: "This mausoleum requires a carpenter's services. " }
    { group:178, id:98, text: "The Overseer of Commerce refuses to release plain stone to my workers. He claims you ordered that it be stockpiled. I disbelieve him, but perhaps you should straighten him out." }
    { group:178, id:99, text: "Your Overseer of Commerce says that you commanded him to stockpile limestone. Unless you have a talk with him, my workers will never get any deliveries. " }
    { group:178, id:100, text: "Did you really direct the Overseer of Commerce to stockpile sandstone? He will not authorize shipments from the Storage Yards." }
    { group:178, id:101, text: "Could you ask your Overseer of Commerce to stop stockpiling white marble? We could really use it at the monument." }
    { group:178, id:102, text: "Your Overseer of Commerce says that you commanded him to stockpile granite. Unless you have a talk with him, my workers will never get any deliveries. " }
    { group:178, id:103, text: "Your Overseer of Commerce dares to blame you for the work stoppage! He claims that you ordered bricks to be stockpiled." }
    { group:178, id:104, text: "The Overseer of Commerce told me that you have ordered him to stockpile copper. I'm sure you have a good reason for doing so, but my men can't continue work on the monument without the commodity." }
    { group:178, id:105, text: "The Pharaoh will not be the least bit amused if his life's story is not told in the most elegant fashion.  With no Artisans' Guild, whom do you expect to illustrate the tomb?" }
    { group:178, id:106, text: "A rather drab looking tomb, isn't it?  That's how it's going to stay unless some artisans show up soon!  I always thought they were a lazy lot.  You'd better see what the delay is." }
    { group:178, id:107, text: "Without any marble our talented stonemasons have nothing to do.  That is a real shame, as I'd really like to see them much busier.  You had better see to it that some marble gets imported quickly." }
    { group:178, id:108, text: "The roof on this will leak like a sieve if we don't get some copper.  If you can't mine it than you had better import some.  The sooner I get it the sooner this monument will be done!" }
    { group:178, id:109, text: "Workers are clearing and leveling the land.  Now would be an excellent time to start amassing a goodly supply of marble." }
    { group:178, id:110, text: "Work is progressing nicely.  The laborers have all the supplies they need." }
    { group:178, id:111, text: "It is hard to believe, but the Overseer of Commerce informs me that marble is being stockpiled in our storage yards.  Without marble, how can you expect work to continue?" }
    { group:178, id:112, text: "I've learned from a reliable source that granite is being stockpiled.  Do you expect me to conjure up what I need from the sands of the Nile?  You had better see to it that some granite is made available to my stonemasons immediately." }
    { group:178, id:113, text: "Without a supply of copper how can you expect the roof of this great structure to be completed?  Incredible as it may seem, your Overseer of Commerce has told me that he's stockpiling it." }
    { group:178, id:114, text: "We're waiting for peasants to clear the land." }
    { group:178, id:115, text: "Now that the land is cleared, stonemasons are putting the foundation in place." }
    { group:178, id:116, text: "The foundation is complete, so now we can work on the floor." }
    { group:178, id:117, text: "We're erecting some columns now that the floor is laid." }
    { group:178, id:118, text: "Building a roof is the next step. The columns are complete." }
    { group:178, id:119, text: "Now we need some copper to finish the roof so that it will glisten like the sun." }
    { group:178, id:120, text: "We're just putting the finishing touches on the Library now." }
    { group:178, id:121, text: "Alexandria's Library is finished and is the center of learning in the known world." }
    { group:178, id:122, text: "Peasants are hard at work, clearing the land for the Caesareum." }
    { group:178, id:123, text: "Now that the land is ready, the stonemasons are busy laying a solid foundation." }
    { group:178, id:124, text: "Our tired stonemasons have finished laying the foundation. No rest for the weary, though: construction of the temple is underway." }
    { group:178, id:125, text: "With the central temple complete, work has begun on the patio!" }
    { group:178, id:126, text: ">From patios to porticos! Our skillful stonemasons have finished the patio and have begun work on the portico. " }
    { group:178, id:127, text: "The stonemasons have started placing the roof on the portico's pillars." }
    { group:178, id:128, text: "All of the roof sections are in place on the porticos." }
    { group:178, id:129, text: "The Caesareum's majestic entranceway is finished." }
    { group:178, id:130, text: "Stonemasons have finished the Caesareum's interior and have turned their attention to the granite obelisks that adorn the exterior of the building." }
    { group:178, id:131, text: "The Caesareum is complete and celebrates the union between Egypt and Rome." }
    { group:178, id:132, text: "Peasants have begun the arduous task of clearing the land." }
    { group:178, id:133, text: "The stonemasons are busily laying the foundation for the Lighthouse." }
    { group:178, id:134, text: "The foundation is almost complete and the parquet floor is being installed." }
    { group:178, id:135, text: "With the parquet floor complete, the stonemasons have turned their attention to the first tier of the Lighthouse." }
    { group:178, id:136, text: "The stonemasons don't have much time to admire their work on the first tier, for work on the second octagonal tier will begin soon." }
    { group:178, id:137, text: "The Lighthouse is really beginning to take shape. The octagonal tier is done, and the stonemasons will begin the cupola soon." }
    { group:178, id:138, text: "The last piece of the Lighthouse had been laid in place, but the monument won't be complete until the scaffolding is removed. That work is beginning now." }
    { group:178, id:139, text: "Most of the scaffolding has been removed, and the Lighthouse is nearly complete." }
    { group:178, id:140, text: "The Pharos Lighthouse is finished and shines as a beacon over the Eastern Mediterranean Sea." }
    { group:178, id:141, text: "Workers are busy working on Abu Simbel. Make sure that the carpenters have plenty of wood so that they can build scaffolding in a timely fashion." }
    { group:178, id:142, text: "The impressive figures of our Ramses II welcome all who approach Egypt from the south." }
    { group:178, id:143, text: "The artisans and masons refuse to step foot in the Royal Burial Tomb without lamps. It is awfully dark in there!" }
    { group:178, id:144, text: "The artisans and masons are busy at their crafts, and work on the Royal Burial Tomb is progressing nicely. Remember to keep the Artisans' Guild supplied with clay and paint to help ensure that everything goes smoothly." }
    { group:178, id:145, text: "The Royal Burial Tomb is complete. All that is lacking now are the burial provisions the deceased will need in the Field of Reeds." }
    { group:178, id:146, text: "The hidden Royal Burial Tomb is now ready for the Pharaoh. May Horus guard the tomb and strike down anyone who may dare to violate it!" }
    { group:178, id:147, text: "Lamps:" }
    { group:178, id:148, text: "Workers can't get to the tomb's entrance.  See what's blocking the way." }
    { group:178, id:149, text: "Workers can't get to the monument's staging area.  See what's blocking their access." }
    { group:179, id:0, text: "Work Camp" }
    { group:179, id:1, text: "This Work Camp houses laborers who can work either on floodplain farms or on monuments." }
    { group:179, id:2, text: "This Work Camp needs workers to support the manual laborers based here. " }
    { group:179, id:3, text: "We supply as much unskilled labor as is humanly possible." }
    { group:179, id:4, text: "Our laborers are off looking for work." }
    { group:179, id:5, text: "Our laborers are off working on floodplain farms." }
    { group:179, id:6, text: "Our laborers are off working on monuments." }
    { group:179, id:7, text: "Our laborers are off working on both floodplain farms and monuments." }
    { group:180, id:0, text: "Brickworks" }
    { group:180, id:1, text: "Clay and straw are combined here to form sturdy, durable bricks." }
    { group:180, id:2, text: "Production is" }
    { group:180, id:3, text: "complete." }
    { group:180, id:4, text: "Your Overseer of Commerce ordered a halt to brick production." }
    { group:180, id:5, text: "This Brickworks has no employees. Not a single brick can be made." }
    { group:180, id:6, text: "This workshop has all the employees it needs. It produces tons of bricks." }
    { group:180, id:7, text: "This Brickworks has some unfilled jobs, which slows down brick production somewhat." }
    { group:180, id:8, text: "This workshop is understaffed, and it takes longer to produce bricks than it should." }
    { group:180, id:9, text: "Very few people work here. Brick production is much slower than it could be." }
    { group:180, id:10, text: "With hardly any workers, this Brickworks will produce very few bricks over the coming year." }
    { group:180, id:11, text: "This workshop needs clay delivered to it, from a Storage Yard or a Clay Pit, to produce bricks." }
    { group:180, id:12, text: "This workshop needs straw delivered to it, from a Storage Yard or a Grain Farm, to produce bricks." }
    { group:180, id:13, text: "Clay: " }
    { group:180, id:14, text: "Straw: " }
    { group:181, id:0, text: "Barley Farm" }
    { group:181, id:1, text: "Barley is a key ingredient for beer, without which our civilization would surely not exist." }
    { group:181, id:2, text: "Production is" }
    { group:181, id:3, text: "complete." }
    { group:181, id:4, text: "Your Overseer of Commerce commanded that barley farming should cease." }
    { group:181, id:5, text: "This farm has no workers. The land lies fallow." }
    { group:181, id:6, text: "This farm has all the workers it needs. It gets maximum yield, given its fertility." }
    { group:181, id:7, text: "This farm has a few job openings. It could grow more barley with more workers." }
    { group:181, id:8, text: "This farm is understaffed. The barley crop could be much better than it is." }
    { group:181, id:9, text: "So few farmers work here that we have barely enough barley for 'lite' beer." }
    { group:181, id:10, text: "With hardly any workers at this farm, Egyptians might soon be reduced to drinking water." }
    { group:181, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:181, id:12, text: "Land is" }
    { group:181, id:13, text: "fertile." }
    { group:181, id:14, text: "The next barley harvest is in" }
    { group:182, id:0, text: "Chickpea Farm" }
    { group:182, id:1, text: "Chickpeas are a versatile source of protein, and quite popular in your people's diets." }
    { group:182, id:2, text: "Production is" }
    { group:182, id:3, text: "complete." }
    { group:182, id:4, text: "Your Overseer of Commerce ordered a halt to chickpea farming." }
    { group:182, id:5, text: "This farm has no workers. The land lies fallow." }
    { group:182, id:6, text: "This farm has all the workers it needs. It gets maximum yield, given its fertility." }
    { group:182, id:7, text: "This farm would like to hire more workers. It could grow more chickpeas than it does." }
    { group:182, id:8, text: "This farm is understaffed. Its workers grow fewer chickpeas than the land could yield." }
    { group:182, id:9, text: "There are very few farmers working here. Chickpea production is far from maximal." }
    { group:182, id:10, text: "With hardly any workers at this farm, the chickpea harvest will be negligible." }
    { group:182, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:182, id:12, text: "Land is" }
    { group:182, id:13, text: "fertile." }
    { group:182, id:14, text: "The next chickpea harvest is in" }
    { group:183, id:0, text: "Fig Farm" }
    { group:183, id:1, text: "Figs figure prominently in the balanced diet that people need for health and happiness." }
    { group:183, id:2, text: "Production is" }
    { group:183, id:3, text: "complete." }
    { group:183, id:4, text: "Your Overseer of Commerce ordered a halt to fig farming." }
    { group:183, id:5, text: "This grove has no workers. The trees are wild and barren." }
    { group:183, id:6, text: "This grove has all the workers it needs. It gets maximum yield for its fertility." }
    { group:183, id:7, text: "This grove could use more workers. It would produce more figs." }
    { group:183, id:8, text: "This grove is understaffed. Its workers harvest fewer figs than they otherwise could." }
    { group:183, id:9, text: "There are very few farmers working here. Fig production is far from maximal." }
    { group:183, id:10, text: "With hardly any workers at this farm, it will barely give a fig." }
    { group:183, id:11, text: "This farm's land was blighted by the recent swarm of locusts, and will take some time to recover." }
    { group:183, id:12, text: "Land is" }
    { group:183, id:13, text: "fertile." }
    { group:183, id:14, text: "The next fig harvest is in" }
    { group:184, id:0, text: "Transport" }
    { group:184, id:1, text: "Warship" }
    { group:184, id:2, text: "Hull strength" }
    { group:184, id:3, text: "Very strong" }
    { group:184, id:4, text: "Strong" }
    { group:184, id:5, text: "Good" }
    { group:184, id:6, text: "Average" }
    { group:184, id:7, text: "Fair" }
    { group:184, id:8, text: "Weak" }
    { group:184, id:9, text: "Hold position" }
    { group:184, id:10, text: "When so ordered, the ship remains in position, blocking passage of all enemy ships for as long as it remains afloat." }
    { group:184, id:11, text: "Engage nearby enemies " }
    { group:184, id:12, text: "Under this order, the warship guards a small area. It moves to attack any enemy soldiers or ships that come within range." }
    { group:184, id:13, text: "Seek and destroy all enemies" }
    { group:184, id:14, text: "With this order, the warship searches far and wide for enemy ships and soldiers, attacking any that it can reach." }
    { group:184, id:15, text: "Repair" }
    { group:184, id:16, text: "The ship returns to a Shipwright for repairs. Captains of heavily-damaged ships will head in for repairs on their own initiative." }
    { group:184, id:17, text: "Return to Wharf" }
    { group:184, id:18, text: "This instructs the ship to return to its parent Wharf, where its crew can rest and revitalize their spirits." }
    { group:184, id:19, text: "Hold position" }
    { group:184, id:20, text: "When so ordered, the ship remains in position at all costs. It might not remain afloat for long if attacked." }
    { group:184, id:21, text: "Evade enemies" }
    { group:184, id:22, text: "This ship's captain has standing orders to evade. Unless told otherwise, he avoids enemy contact at all costs." }
    { group:184, id:23, text: "Embark" }
    { group:184, id:24, text: "This order instructs the ship's captain to pick up a company of soldiers for transport." }
    { group:184, id:25, text: "Disembark" }
    { group:184, id:26, text: "This order tells the captain to drop off a company of soldiers onto dry land." }
    { group:184, id:27, text: "Crew fatigue" }
    { group:184, id:28, text: "Rested" }
    { group:184, id:29, text: "Tired" }
    { group:184, id:30, text: "Exhausted " }
    { group:184, id:31, text: "Archer Company," }
    { group:184, id:32, text: "Chariot Company," }
    { group:184, id:33, text: "Infantry Company," }
    { group:184, id:34, text: "on board" }
    { group:185, id:0, text: "Chariot Workshop" }
    { group:185, id:1, text: "Expert craftsmen produce 'war wheels,' one of Egypt's deadliest weapons, here." }
    { group:185, id:2, text: "Production is" }
    { group:185, id:3, text: "complete." }
    { group:185, id:4, text: "Your Overseer of Commerce decreed that chariot production should cease." }
    { group:185, id:5, text: "This Chariot Maker has no employees, and will produce no war wheels at all." }
    { group:185, id:6, text: "This Chariot Maker is fully staffed, and produces many high-quality chariots." }
    { group:185, id:7, text: "This Chariot Maker could use more workers to reach its full potential for chariot production." }
    { group:185, id:8, text: "This Chariot Maker is understaffed, and produces chariots more slowly than it should." }
    { group:185, id:9, text: "Very few people work at this Chariot Maker. Chariot production is slow as a result." }
    { group:185, id:10, text: "With hardly any employees, this Chariot Maker will produce very few chariots over the coming year." }
    { group:185, id:11, text: "This workshop will produce no chariots without a shipment of wood, whether from a Storage Yard or a Wood Cutter." }
    { group:185, id:12, text: "Stored wood," }
    { group:187, id:0, text: "Unknown" }
    { group:187, id:1, text: "Local Deity" }
    { group:187, id:2, text: "Patron God" }
    { group:188, id:0, text: "Festival Square" }
    { group:188, id:1, text: "When you instruct your Overseer of the Temples to throw a festival in honor of one of the gods, citizens gather here to participate. " }
    { group:188, id:2, text: "Hold a festival to make the people happy, and to appease the gods" }
    { group:188, id:3, text: "A festival is currently in progress" }
    { group:189, id:0, text: "Altar of Sebek" }
    { group:189, id:1, text: "Oracle of Min" }
    { group:189, id:2, text: "Altar of Ma'at" }
    { group:189, id:3, text: "Oracle of Horus" }
    { group:189, id:4, text: "Altar of Amon" }
    { group:189, id:5, text: "Oracle of Thoth" }
    { group:189, id:6, text: "Altar of Anubis" }
    { group:189, id:7, text: "Oracle of Sekhmet" }
    { group:189, id:8, text: "Altar of Isis" }
    { group:189, id:9, text: "Oracle of Hathor" }
    { group:190, id:0, text: "Papyrus Maker" }
    { group:190, id:1, text: "Here reeds are bound together to make papyrus, which educational institutions require for writing down information and sharing knowledge. Papyrus may also be profitably traded." }
    { group:190, id:2, text: "Production is" }
    { group:190, id:3, text: "complete." }
    { group:190, id:4, text: "Your Overseer of Commerce decreed that papyrus production should cease." }
    { group:190, id:5, text: "This Papyrus Maker has no employees, and will yield no products as a result." }
    { group:190, id:6, text: "This Papyrus Maker is fully staffed, and produces ample high-quality papyrus." }
    { group:190, id:7, text: "This Papyrus Maker could use more workers to reach its full potential for papyrus production." }
    { group:190, id:8, text: "This Papyrus Maker is understaffed, and produces papyrus more slowly than it should." }
    { group:190, id:9, text: "Very few people work at this workshop. Papyrus production is slow as a result." }
    { group:190, id:10, text: "With hardly any employees, this Papyrus Maker will produce little papyrus over the coming year." }
    { group:190, id:11, text: "This workshop will produce no papyrus without a shipment of reeds, whether from a Storage Yard or a Reed Gatherer." }
    { group:190, id:12, text: "Stored reeds," }
    { group:191, id:0, text: "Cheat dialog" }
    { group:191, id:1, text: "Disable cheats" }
    { group:192, id:0, text: "Granite Quarry" }
    { group:192, id:1, text: "Obelisks use the heavy blocks of sturdy granite that you carve from the bones of the earth here." }
    { group:192, id:2, text: "Production is" }
    { group:192, id:3, text: "complete." }
    { group:192, id:4, text: "Your Overseer of Commerce ordered that no more granite be quarried." }
    { group:192, id:5, text: "This quarry has no workers. Production has ceased." }
    { group:192, id:6, text: "This quarry has all the workers it needs, and is working flat out to produce granite." }
    { group:192, id:7, text: "This quarry is working below maximum capacity. Production could be slightly more efficient with more workers." }
    { group:192, id:8, text: "This quarry is understaffed. It takes longer to produce granite than it should." }
    { group:192, id:9, text: "Very few people work here. The quarry yields very little granite." }
    { group:192, id:10, text: "With hardly any workers here, output has nearly stopped. It will produce little over the coming year." }
    { group:193, id:0, text: "Copper Mine" }
    { group:193, id:1, text: "Easily worked and durable, copper makes fine weapons and a valuable export." }
    { group:193, id:2, text: "Production is" }
    { group:193, id:3, text: "complete." }
    { group:193, id:4, text: "Your Overseer of Commerce ordered a halt to copper mining." }
    { group:193, id:5, text: "This mine has no workers. Production has ceased." }
    { group:193, id:6, text: "This mine has all the workers it needs, and is producing plenty of copper." }
    { group:193, id:7, text: "This mine is working below maximum capacity. Production could be slightly more efficient with more workers." }
    { group:193, id:8, text: "This mine is understaffed. It takes longer to produce copper than it should." }
    { group:193, id:9, text: "Very few people work in this building. Production is slow as a result." }
    { group:193, id:10, text: "With hardly any workers here, output has nearly stopped. It will produce little over the coming year." }
    { group:194, id:0, text: "Sandstone Quarry" }
    { group:194, id:1, text: "Only sandstone has the right properties for mausoleums and sun temples." }
    { group:194, id:2, text: "Production is" }
    { group:194, id:3, text: "complete." }
    { group:194, id:4, text: "Your Overseer of Commerce ordered that no more sandstone be quarried." }
    { group:194, id:5, text: "This quarry has no workers. Production has ceased." }
    { group:194, id:6, text: "This quarry has all the workers it needs, and is working flat out to produce sandstone." }
    { group:194, id:7, text: "This quarry is working below maximum capacity. Production could be slightly more efficient with more workers." }
    { group:194, id:8, text: "This quarry is understaffed. It takes longer to produce sandstone than it should." }
    { group:194, id:9, text: "Very few people work in this building. Production is extremely slow as a result." }
    { group:194, id:10, text: "With hardly any workers here, output has nearly stopped. It will produce little over the coming year." }
    { group:195, id:0, text: "Abu" }
    { group:195, id:1, text: "Abedju" }
    { group:195, id:2, text: "Bahariya Oasis" }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubastis" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Byblos" }
    { group:195, id:8, text: "Dahshur" }
    { group:195, id:9, text: "Dakhla Oasis" }
    { group:195, id:10, text: "Djedu" }
    { group:195, id:11, text: "Dunqul Oasis" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "Farafra Oasis" }
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
    { group:195, id:24, text: "Kharga Oasis" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knossos" }
    { group:195, id:27, text: "Kyrene" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mycenae" }
    { group:195, id:32, text: "Nekhen" }
    { group:195, id:33, text: "Nubt" }
    { group:195, id:34, text: "On" }
    { group:195, id:35, text: "Perwadjyt" }
    { group:195, id:36, text: "Pwenet" }
    { group:195, id:37, text: "Qadesh" }
    { group:195, id:38, text: "Rostja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Saqqara" }
    { group:195, id:41, text: "Sauty" }
    { group:195, id:42, text: "Sawu" }
    { group:195, id:43, text: "Selima Oasis" }
    { group:195, id:44, text: "Serabit Khadim" }
    { group:195, id:45, text: "Shaat" }
    { group:195, id:46, text: "Sharuhen" }
    { group:195, id:47, text: "Thinis" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toshka" }
    { group:195, id:50, text: "Tyre" }
    { group:195, id:51, text: "Waset" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alexandria" }
    { group:195, id:54, text: "Sumur" }
    { group:195, id:55, text: "Deir el-Medina" }
    { group:195, id:56, text: "Abu Simbel" }
    { group:195, id:57, text: "Actium" }
    { group:195, id:58, text: "Rome" }
    { group:195, id:59, text: "Tanis" }
    { group:195, id:60, text: "Pi-Yer" }
    { group:195, id:61, text: "Siwi Oasis" }
    { group:195, id:62, text: "Maritis" }
    { group:195, id:63, text: "Piramesse" }
    { group:195, id:64, text: "Athens" }
    { group:195, id:65, text: "Cleoantonopolis" }
    { group:196, id:0, text: "CRETE" }
    { group:196, id:1, text: "CYPRUS" }
    { group:196, id:2, text: "EASTERN AFRICA" }
    { group:196, id:3, text: "EASTERN DESERT" }
    { group:196, id:4, text: "GREECE" }
    { group:196, id:5, text: "LIBYA" }
    { group:196, id:6, text: "LOWER EGYPT" }
    { group:196, id:7, text: "DELTA" }
    { group:196, id:8, text: "FAYUUM" }
    { group:196, id:9, text: "NUBIA" }
    { group:196, id:10, text: "PALESTINE" }
    { group:196, id:11, text: "SINAI" }
    { group:196, id:12, text: "SYRIA" }
    { group:196, id:13, text: "UPPER EGYPT" }
    { group:196, id:14, text: "WESTERN DESERT" }
    { group:196, id:15, text: "LEBANON" }
    { group:196, id:16, text: "CANAAN" }   
    { group:198, id:0, text: "None " }
    { group:198, id:1, text: "Small Bent Pyramid" }
    { group:198, id:2, text: "Medium Bent Pyramid" }
    { group:198, id:3, text: "Small Mudbrick Pyramid" }
    { group:198, id:4, text: "Medium Mudbrick Pyramid" }
    { group:198, id:5, text: "Large Mudbrick Pyramid" }
    { group:198, id:6, text: "Mudbrick Pyramid Complex" }
    { group:198, id:7, text: "Grand Mudbrick Pyramid Complex" }
    { group:198, id:8, text: "Small Stepped Pyramid" }
    { group:198, id:9, text: "Medium Stepped Pyramid" }
    { group:198, id:10, text: "Large Stepped Pyramid" }
    { group:198, id:11, text: "Stepped Pyramid Complex" }
    { group:198, id:12, text: "Grand Stepped Pyramid Complex" }
    { group:198, id:13, text: "Small Pyramid" }
    { group:198, id:14, text: "Medium Pyramid" }
    { group:198, id:15, text: "Large Pyramid" }
    { group:198, id:16, text: "Pyramid Complex" }
    { group:198, id:17, text: "Grand Pyramid Complex" }
    { group:198, id:18, text: "Small Mastaba" }
    { group:198, id:19, text: "Medium Mastaba" }
    { group:198, id:20, text: "Large Mastaba" }
    { group:198, id:21, text: "Sphinx" }
    { group:198, id:22, text: "Small Obelisk" }
    { group:198, id:23, text: "Large Obelisk" }
    { group:198, id:24, text: "Sun Temple" }
    { group:198, id:25, text: "Mausoleum" }
    { group:198, id:26, text: "Mausoleum" }
    { group:198, id:27, text: "Mausoleum" }
    { group:198, id:28, text: "Pharos Lighthouse" }
    { group:198, id:29, text: "Alexandria's Library" }
    { group:198, id:30, text: "Caesareum" }
    { group:198, id:31, text: "Colossi" }
    { group:198, id:32, text: "Temple of Luxor" }
    { group:198, id:33, text: "Small Royal Burial Tomb" }
    { group:198, id:34, text: "Medium Royal Burial Tomb" }
    { group:198, id:35, text: "Large Royal Burial Tomb" }
    { group:198, id:36, text: "Grand Royal Burial Tomb" }
    { group:198, id:37, text: "Abu Simbel" }
    { group:199, id:0, text: "Overseer of Monuments" }
    { group:199, id:1, text: "in Storage" }
    { group:199, id:2, text: "Finished" }
    { group:199, id:3, text: "Click burial provisions to deliver." }
    { group:199, id:4, text: "Amount to Dispatch" }
    { group:199, id:5, text: "All" }
    { group:199, id:6, text: "Click to Dispatch" }
    { group:199, id:7, text: "Cancel" }
    { group:199, id:8, text: "Increase Amount" }
    { group:199, id:9, text: "Decrease Amount" }
    { group:199, id:10, text: "Dispatch Burial Provisions" }
    { group:199, id:11, text: "Monument Rating" }
    { group:199, id:12, text: "No burial provisions need to be dispatched." }
    { group:199, id:13, text: "Visit the construction site for more details." }
    { group:199, id:14, text: "Work on this pyramid has not begun. You  need peasant labor to begin " }
    { group:199, id:15, text: "this project, and plenty of plain stone and limestone to complete it." }
    { group:199, id:16, text: "This pyramid is " }
    { group:199, id:17, text: "This pyramid is now complete! " }
    { group:199, id:18, text: "This pyramid is complete.  It will forever house the sacred remains." }
    { group:199, id:19, text: "Work on this brick pyramid has not begun. You need peasant labor to begin " }
    { group:199, id:20, text: "this project, and plenty of bricks and limestone to complete it." }
    { group:199, id:21, text: "This brick pyramid is   " }
    { group:199, id:22, text: "This brick pyramid is now complete!" }
    { group:199, id:23, text: "This pyramid is complete.  It will forever house the sacred remains." }
    { group:199, id:24, text: "Work on this stepped pyramid has not begun. You need peasant labor" }
    { group:199, id:25, text: "to begin this project, and plenty of plain stone to complete it." }
    { group:199, id:26, text: "This stepped pyramid is " }
    { group:199, id:27, text: "This stepped pyramid is now complete!" }
    { group:199, id:28, text: "This stepped pyramid is done. It will forever house the sacred remains." }
    { group:199, id:29, text: "Work on this bent pyramid has not begun. You need peasant labor to begin " }
    { group:199, id:30, text: "this project, and plenty of plain stone and limestone to complete it." }
    { group:199, id:31, text: "This bent pyramid is" }
    { group:199, id:32, text: "This bent pyramid is now complete!" }
    { group:199, id:33, text: "This bent pyramid is done. It will forever house the sacred remains." }
    { group:199, id:34, text: "Work on this mastaba has not yet begun. You need peasant labor to begin" }
    { group:199, id:35, text: "this project, and a good supply of bricks to complete it." }
    { group:199, id:36, text: "This mastaba is " }
    { group:199, id:37, text: "This mastaba is now complete!" }
    { group:199, id:38, text: "This mastaba is complete, and will forever house the sacred remains." }
    { group:199, id:39, text: "Work on this sphinx has not yet begun. You need carpenters, stonemasons, " }
    { group:199, id:40, text: "wood and plain stone to begin this project." }
    { group:199, id:41, text: "This sphinx is " }
    { group:199, id:42, text: "This sphinx is now complete!" }
    { group:199, id:43, text: "Work on this obelisk has not yet begun. You will need " }
    { group:199, id:44, text: "blocks of granite to begin this project.  You have " }
    { group:199, id:45, text: "This obelisk is" }
    { group:199, id:46, text: "This obelisk is now complete!" }
    { group:199, id:47, text: "Work on this sun temple has not yet begun.  You will need " }
    { group:199, id:48, text: "blocks of sandstone to begin this project.  You have " }
    { group:199, id:49, text: "This sun temple is" }
    { group:199, id:50, text: "This sun temple is now complete!" }
    { group:199, id:51, text: "Work on this mausoleum has not yet begun.  You will need " }
    { group:199, id:52, text: "blocks of sandstone to begin this project.  You have" }
    { group:199, id:53, text: "This mausoleum is" }
    { group:199, id:54, text: "This mausoleum is now complete!" }
    { group:199, id:55, text: "This mausoleum is complete, and will forever house the sacred remains. " }
    { group:199, id:56, text: "Click to visit construction site." }
    { group:199, id:57, text: "block stored" }
    { group:199, id:58, text: "blocks stored" }
    { group:199, id:59, text: "Work on Alexandria's Library has not begun. You will need peasant labor" }
    { group:199, id:60, text: "to begin this project, and a supply of marble and copper to complete it." }
    { group:199, id:61, text: "The Library of Alexandria is" }
    { group:199, id:62, text: "The Library of Alexandria is now complete!" }
    { group:199, id:63, text: "Work on the Caesareum has not begun. You will need peasant labor " }
    { group:199, id:64, text: "to begin this project, and a supply of marble and granite to complete it." }
    { group:199, id:65, text: "The Caesareum is" }
    { group:199, id:66, text: "The Caesareum is now complete!" }
    { group:199, id:67, text: "Work on the Pharos Lighthouse has not begun. You will need peasant" }
    { group:199, id:68, text: "labor to begin this project, and a supply of marble to complete it." }
    { group:199, id:69, text: "The Pharos Lighthouse is" }
    { group:199, id:70, text: "The Pharos Lighthouse is now complete!" }
    { group:199, id:71, text: "Work on Abu Simbel has not begun. You will need carpenters, stonemasons " }
    { group:199, id:72, text: "and a supply of wood to begin this project." }
    { group:199, id:73, text: "Abu Simbel is" }
    { group:199, id:74, text: "Abu Simbel is now complete!" }
    { group:199, id:75, text: "Work on the Small Burial Tomb has not begun. You will need stonemasons," }
    { group:199, id:76, text: "artisans, clay, paint and lamps to begin this project." }
    { group:199, id:77, text: "The Small Royal Burial Tomb is" }
    { group:199, id:78, text: "The Small Royal Burial Tomb is now complete!" }
    { group:199, id:79, text: "Work on the Medium Burial Tomb has not begun. You will need " }
    { group:199, id:80, text: "stonemasons, artisans, clay, paint and lamps to begin this project." }
    { group:199, id:81, text: "The Medium Royal Burial Tomb is" }
    { group:199, id:82, text: "The Medium Royal Burial Tomb is now complete!" }
    { group:199, id:83, text: "Work on the Large Burial Tomb has not begun. You will need stonemasons," }
    { group:199, id:84, text: "artisans, clay, paint and lamps to begin this project." }
    { group:199, id:85, text: "The Large Royal Burial Tomb is" }
    { group:199, id:86, text: "The Large Royal Burial Tomb is now complete!" }
    { group:199, id:87, text: "Work on the Grand Burial Tomb has not begun. You will need stonemasons," }
    { group:199, id:88, text: "artisans, clay, paint and lamps to begin this project." }
    { group:199, id:89, text: "The Grand Royal Burial Tomb is" }
    { group:199, id:90, text: "The Grand Royal Burial Tomb is now complete!" }
    { group:200, id:0, text: "Phase One: Obtain granite to place rough structure" }
    { group:200, id:1, text: "Phase Two: Carpenters use wood to build scaffolding" }
    { group:200, id:2, text: "Phase Three: Stonemasons carve final shape, working from top to bottom" }
    { group:200, id:3, text: "Status:" }
    { group:200, id:4, text: "Not started" }
    { group:200, id:5, text: "Incomplete" }
    { group:200, id:6, text: "Complete" }
    { group:200, id:7, text: "Overall Progress:" }
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
    { group:205, id:0, text: "Maybe stealing from his treasury will get that false beard's attention! // cart_pusher" }
    { group:205, id:1, text: "I take what I want! Don't try to stop me!" }
    { group:205, id:2, text: "Thievery is a lot more profitable than other jobs in this city!" }
    { group:205, id:3, text: "Take, take, take. That's all I ever do." }
    { group:206, id:0, text: "Ohhh, my stomach! Oh, my head! 											// labor seeker" }
    { group:207, id:0, text: "Plague could break out at any time! I hope it stays in the poor parts of town!" }
    { group:207, id:1, text: "That a person of my quality could know hunger is scandalous!" }
    { group:207, id:2, text: "I don't think this city could handle an attack, and I have so very much to lose." }
    { group:207, id:3, text: "How can so few workers properly cater to my needs?" }
    { group:207, id:4, text: "I'm treated far better than the gods! I hope they don't strike at us." }
    { group:207, id:5, text: "I'm ashamed to live here. I hope our enemies don't take advantage of our reputation!" }
    { group:207, id:6, text: "Look at all these idlers! Why don't they get jobs?" }
    { group:207, id:7, text: "How can I lead a posh lifestyle if I'm not properly entertained?" }
    { group:207, id:8, text: "This city passes muster, I suppose." }
    { group:207, id:9, text: "This city couldn't be better!" }
    { group:207, id:10, text: "These festivals would be so much better if they were by invitation only." }    
    { group:210, id:0, text: "Birds are wily. They'll fly away if you don't approach them just right." }
    { group:210, id:1, text: "Look at those beautiful birds, ready for roasting!" }
    { group:211, id:0, text: "Another perfect day for fishing.  I hope the catch is as plentiful as usual." }
    { group:211, id:1, text: "Our hold is overflowing, but you should have seen the one that got away!" }
    { group:211, id:2, text: "Move faster! We can't get back to work until you unload us." }    
    { group:215, id:0, text: "To the marsh I march for the reeds we need." }
    { group:215, id:1, text: "These reeds will make some fine papyrus." }
    { group:216, id:0, text: "My services are needed at the monument!" }
    { group:216, id:1, text: "This monument would be very short without my ramps and scaffolds." }
    { group:217, id:0, text: "It's bricklaying time at the monument!" }
    { group:217, id:1, text: "With my bricks, this monument will be strong." }
    { group:218, id:0, text: "I'm going to the monument to shape the stones." }
    { group:218, id:1, text: "My stonework will endure through the ages." }
    { group:219, id:0, text: "So many people have taken ill. I hope they recover soon, or else a plague might break out." }
    { group:219, id:1, text: "I'm starving. Most of my customers demand food, and I can barely feed myself." }
    { group:219, id:2, text: "Our defenses are flimsy. We could easily be invaded." }
    { group:219, id:3, text: "I better be extra nice to my helpers. With this many job openings in the city, I could easily lose them." }
    { group:219, id:4, text: "If we don't soon pay the gods more respect, they are going to dole out a miserable punishment." }
    { group:219, id:5, text: "I wouldn't dream of letting my reputation slip as far as this city's has. We could soon pay the price." }
    { group:219, id:6, text: "I'm lucky to have a job. I know a lot of people who are out of work." }
    { group:219, id:7, text: "Nothing whatsoever happens here. I wish there were more shows to see. " }
    { group:219, id:8, text: "I won't complain about this city... but I could." }
    { group:219, id:9, text: "This city is tops!" }
    { group:219, id:10, text: "The bazaar needs some items, and I'm going to get them." }
    { group:219, id:11, text: "These goods will make welcome additions to the bazaar." }
    { group:222, id:0, text: "I'm not taking these supplies any further until someone's available to unload them." }
    { group:222, id:1, text: "No one can accept these goods! That's okay, I can use the rest." }
    { group:222, id:2, text: "I have to go clear across the city with these goods. It'll take all day!" }
    { group:223, id:0, text: "We're doing more than our share of work.  We need more help." }
    { group:223, id:1, text: "I'll wait here until some space for this stuff opens up." }
    { group:223, id:2, text: "Am I there yet?  I can't haul these goods much further." }   
    { group:226, id:0, text: "I've never seen so many sick people. I hope a plague doesn't break out." }
    { group:226, id:1, text: "It's hard to catch these clubs when you're doubled over with hunger pangs." }
    { group:226, id:2, text: "Maybe I can throw these clubs at the enemy should they attack. Little else is defending this city." }
    { group:226, id:3, text: "I see job vacancies everywhere! I wonder if I could juggle more than one job." }
    { group:226, id:4, text: "I'm expecting the worst. The gods must think we've forgotten them." }
    { group:226, id:5, text: "This city has a worse reputation than I do. I hope no one attacks us." }
    { group:226, id:6, text: "I wish there were more jobs in this city. None of the people I entertain can pay me." }
    { group:226, id:7, text: "I can only juggle so much. I wish there were other entertainers in the city." }
    { group:226, id:8, text: "This city isn't too bad.  " }
    { group:226, id:9, text: "There's no place I'd rather juggle." }
    { group:226, id:10, text: "I love working these festival crowds. Everyone's so happy!" }
    { group:227, id:10, text: "These festivals are great! Everyone sings along." }    
    { group:229, id:0, text: "People's health is in jeopardy. The risk of plague is great." }
    { group:229, id:1, text: "I'm as hungry as a hippo, but there's little food to be found." }
    { group:229, id:2, text: "I ought to learn the war craft. With our defenses so weak, we're at risk." }
    { group:229, id:3, text: "The worker shortage could cause real trouble in the city." }
    { group:229, id:4, text: "To tell the truth, I would not dare to treat the gods so badly." }
    { group:229, id:5, text: "This city's reputation is checkered at best. We could be attacked." }
    { group:229, id:6, text: "For most, finding work in this city is a trivial pursuit that ends in failure." }
    { group:229, id:7, text: "This city should clue in to the lack of entertainment!" }
    { group:229, id:8, text: "I'm not sorry to live here." }
    { group:229, id:9, text: "This city has a monopoly on my heart. I love it here!" }
    { group:229, id:10, text: "Get your beer here! Warm, flat, refreshing beer! Low in sediment!" }    
    { group:235, id:0, text: "The city may soon learn that bad health can lead to a horrible plague." }
    { group:235, id:1, text: "My mind is fed with learning, but my body hungers for food." }
    { group:235, id:2, text: "Invaders would have no trouble penetrating our scanty defenses!" }
    { group:235, id:3, text: "The scarcity of workers reverberates throughout the city, limiting its services." }
    { group:235, id:4, text: "The city's sacreligious ways could cause the gods to smite us!" }
    { group:235, id:5, text: "Ah, reputation, reputation. Our scandalous reputation invites attack." }
    { group:235, id:6, text: "Even education won't cure this city's jobless problem." }
    { group:235, id:7, text: "Boring, dull, tedious, monotonous, ho-hum. This city is all five." }
    { group:235, id:8, text: "This city is thoroughly average." }
    { group:235, id:9, text: "This city earns top marks!" }
    { group:235, id:10, text: "One can learn much about human nature at a festival." }
    
    
    { group:240, id:0, text: "Judging by the number of sick people in this city, I could soon have my hands full!" }
    { group:240, id:1, text: "I'm famished. Before long, I'll be skinnier than a mummy!" }
    { group:240, id:2, text: "The city is not securely wrapped in defenses. An enemy could easily defeat us." }
    { group:240, id:3, text: "If I ever wanted to leave embalming behind, now is my chance. So many job openings!" }
    { group:240, id:4, text: "The gods could soon unravel our city if we don't pay them more respect." }
    { group:240, id:5, text: "The city's bad reputation could be the death of us all. We could be attacked at any moment." }
    { group:240, id:6, text: "When I see so many people out of work, it makes me glad that I have a job." }
    { group:240, id:7, text: "This city is as dead as the bodies I work with all day. I wish the city were alive with entertainment." }
    { group:240, id:8, text: "I might as will live here. It's about as good as anywhere else." }
    { group:240, id:9, text: "I feel truly sorry for my clients. They aren't around to enjoy this incredible city!" }
    { group:240, id:10, text: "Health seems to be worsening throughout the city." }             
    
    { group:247, id:0, text: "My painting and plastering skills are needed at the monument!" }
    { group:247, id:1, text: "I capture the stories of Egypt on the walls of the royal tombs." }
    { group:248, id:0, text: "Gold should be for the living, not the dead!" }
    { group:248, id:1, text: "Just think of the fortune I'll have when I sell off all those treasures!" }
    { group:249, id:0, text: "We'll fight to the death to defend our fair city!" }
    { group:249, id:1, text: "The enemy is too much for us! If we escape them, we'll be ready to fight another day." }
    { group:249, id:2, text: "Enemies are coming this way!" }
    { group:249, id:3, text: "We're as dangerous as a crocodile, ready to attack our invaders when they arrive." }
    { group:249, id:4, text: "If and when our foes come, we'll be ready for them." }
    { group:250, id:0, text: "Row harder! We must protect our ship at all costs!" }
    { group:250, id:1, text: "The enemy is here! All hands prepare for maneuvers." }
    { group:250, id:2, text: "Bring on the attack! We're prepared." }
    { group:250, id:3, text: "We're ready to serve if the need arises." }
    { group:251, id:0, text: "Chariot Exact 1" }
    { group:252, id:0, text: "No enemies have been sighted, but we're ready nonetheless." }
    { group:252, id:1, text: "We're coiled like an asp, eager to strike at the approaching enemy." }
    { group:252, id:2, text: "You call that an army?! We'll have no trouble defeating that motley crew." }
    { group:252, id:3, text: "This enemy is a fierce one! I'm doing all that I can to defeat them." }
    { group:253, id:0, text: "Sun Temple" }
    { group:253, id:1, text: "Phase 1" }
    { group:253, id:2, text: "The rough obelisk has been placed " }
    { group:253, id:3, text: "and workers are clearing the site" }
    { group:253, id:4, text: "Phase 2" }
    { group:253, id:5, text: "Carpenters are placing scaffolds around " }
    { group:253, id:6, text: "the obelisk" }
    { group:253, id:7, text: "Phase 3" }
    { group:253, id:8, text: "Stone masons are carving the final shape " }
    { group:253, id:9, text: "of the obelisk" }
    { group:253, id:10, text: "Phase 4" }
    { group:253, id:11, text: "The vestibule, wall, plaza, and " }
    { group:253, id:12, text: "fore temple are being constructed" }
    { group:253, id:13, text: "A lone stone mason is waiting for stone." }
    { group:253, id:14, text: "stone masons are waiting for stone." }
    { group:253, id:15, text: "The Sun temple is" }
    { group:253, id:16, text: "percent complete" }
    { group:253, id:17, text: "blocks of stone are needed to " }
    { group:253, id:18, text: "finish construction of the Sun Temple." }    
        
    { group:291, id:0, text: "Mausoleum" }
    { group:291, id:1, text: "Phase 1" }
    { group:291, id:2, text: "The foundation has been placed" }
    { group:291, id:3, text: "and workers are clearing the site" }
    { group:291, id:4, text: "Phase 2" }
    { group:291, id:5, text: "Masons are constructing the lower part" }
    { group:291, id:6, text: "of the mausoleum" }
    { group:291, id:7, text: "Phase 3" }
    { group:291, id:8, text: "Stonemasons are constructing the upper" }
    { group:291, id:9, text: "part of the mausoleum" }
    { group:291, id:10, text: "A lone stonemason is waiting for stone" }
    { group:291, id:11, text: "stonemasons are waiting for stone" }
    { group:291, id:12, text: "The mausoleum is" }
    { group:291, id:13, text: "percent complete" }
    { group:291, id:14, text: "blocks of stone are needed to" }
    { group:291, id:15, text: "finish construction of the mausoleum" }
    { group:292, id:0, text: "Create Family" }
    { group:292, id:1, text: "Delete Family" }
    { group:292, id:2, text: "Proceed" }
    { group:292, id:3, text: "Family Registry" }
    { group:292, id:4, text: "Return to main menu" }
    { group:293, id:0, text: "Resume Family History" }
    { group:293, id:1, text: "Choose a Mission" }
    { group:293, id:2, text: "Load Saved Game" }
    { group:293, id:3, text: "Custom Missions" }
    { group:293, id:4, text: "Return to Family Registry" }
    { group:293, id:5, text: "[player_name] family" }
    { group:293, id:6, text: "Explore History" }
    { group:293, id:7, text: "Begin Family History" }
    { group:294, id:0, text: "Predynastic Period" }
    { group:294, id:1, text: "During the Predynastic period, the clans who will eventually rule Egypt take their first faltering steps on the road to civilization. " }
    { group:294, id:2, text: "Your family begins the Predynastic period leading a small band of nomads through their discovery of the arts of civilization. Your leadership helps to set Egypt on its course to eventual greatness, still glimpsed only dimly.  " }
    { group:294, id:3, text: "The Predynastic period is the dawn of Egyptian history, and that of your family.  " }
    { group:294, id:4, text: "Archaic Period" }
    { group:294, id:5, text: "Gradually, the villages established during the Predynastic period coalesce into a unified kingdom, complete with a magnificent capital and its first monumental tombs. " }
    { group:294, id:6, text: "During the Archaic period, the villages that emerged in the Predynastic gradually unite to form the great Kingdom of Egypt. The young civilization founds a capital, secures its borders, masters the waters and builds its first monumental tombs.  " }
    { group:294, id:7, text: "Your Family History must be lived in order! Alas, you cannot rule the Archaic period until you first learn the arts discovered in the Predynastic." }
    { group:294, id:8, text: "Old Kingdom" }
    { group:294, id:9, text: "Egypt enters a golden age of wealth, might and glory, and erects astonishing new monuments throughout the world. Yet, after attaining these dizzying heights, Egypt fell into war. " }
    { group:294, id:10, text: "Egypt rises to unprecedented might, wealth and glory during the Old Kingdom. Yet, even as incredible new monuments rise throughout the Nile valley, seers make disturbing predictions about the fate of the Two Lands.  " }
    { group:294, id:11, text: "You cannot skip ahead while forging your Family History. Before you can enter the Old Kingdom, you must first complete the Archaic period." }
    { group:294, id:12, text: "Middle Kingdom" }
    { group:294, id:13, text: ">From its painful genesis, the Middle Kingdom proves to be a time of great opportunity for your family's advancement in the world." }
    { group:294, id:14, text: "The Middle Kingdom, born in strife, proves to be a time of great opportunity for your family. With your leadership, Egypt regains its former splendor...and more.  " }
    { group:294, id:15, text: "Family History must unfold in order. The Middle Kingdom cannot begin until the Old Kingdom ends!" }
    { group:294, id:16, text: "New Kingdom" }
    { group:294, id:17, text: "A fierce new enemy, using an ingenious and unstoppable new weapon, sweeps the Middle Kingdom away. Out of this destruction, Egypt is again reborn." }
    { group:294, id:18, text: "Strange new enemies with a terrifying super weapon bring the Middle Kingdom to its end, and prepare the way for the magnificent New Kingdom to follow. " }
    { group:294, id:19, text: "You cannot diverge from the path of your Family History! Your family cannot experience the New Kingdom until you complete the previous periods." }
    { group:294, id:20, text: "Valley of the Kings" }
    { group:294, id:21, text: "The development of a new necropolis in the Valley of the Kings provided a new way to prepare the pharaohs for their journeys to the after life." }
    { group:294, id:22, text: "Grand as they are, the pyramids of your ancestors have eroded over the centuries, the tombs within have been desecrated, and the hidden treasures pilfered by robbers, whom the gods will surely punish throughout eternity!  You will forego pyramids and start a new necropolis in a hard-to-reach wadi across from Thebes, digging tombs into the cliffs to create a Valley of the Kings, safe from robbers.  Or is it?" }
    { group:294, id:23, text: "There is a proper time for everything in your Family History. You cannot build the magnificent tombs of the Valley of the Kings until you've completed the splendors of the New Kingdom." }
    { group:294, id:24, text: "Ramses II" }
    { group:294, id:25, text: "Ramses II wins Egypt's greatest victory and commemorates his greatness with stunning monuments." }
    { group:294, id:26, text: "Ramses II is third in a dynastic line begun by his grandfather, Ramses I, a vizier of non-royal blood who claimed the throne when Horemheb left no descendent.  You need to achieve military triumphs and construct great monuments that will convince your subjects of your god-like status, fill your enemies with despair, and proclaim Ramses the Great's name and the glory of Egypt for generations to come." }
    { group:294, id:27, text: "Family History must be completed in order. You cannot rule as Ramses II until you have constructed the glorious tombs in the Valley of the Kings." }
    { group:294, id:28, text: "Ancient Conquerors" }
    { group:294, id:29, text: "Powerful warriors from distant lands sweep in to try to exert dominance over the riches of Egypt.  After you fend off these threats and welcome the glory of Alexander, you may go to the 'Choose a Mission' area to replay the entire campaign or any of its individual missions." }
    { group:294, id:30, text: "Egypt has many envious neighbors, and they look upon our rich empire the way a hyena pack crowds a lion's kill.  Can you build and command the armies and fleets necessary to defeat these serious threats and defend the Nile Delta against successive invasions by the Sea People, Assyrians and Persians?  Egypt looks to you for protection!" }
    { group:294, id:31, text: "Playing this now would create a gap in your Family History. You cannot overcome Ancient Conquerors until you have lived as Ramses II." }
    { group:294, id:32, text: "Cleopatra's Capital" }
    { group:294, id:33, text: "The Ptolemy's from Greece restore glory to the land of the pharaohs and stave off the threat from Rome." }
    { group:294, id:34, text: "Alexander the Great himself has paced off the future site of Alexandria-the port city on the Mediterranean Sea that you must now build.  Under the 300-year reign of the Ptolemy's, ending with Cleopatra VII, Alexandria will become the greatest city in the world, exceeding Rome in population and wealth.  Alexander's Mausoleum, the Great Library, the Pharos Lighthouse and the Caesareum are your city's projects.  But what of Rome's mighty legions?  Will they be used for or against Cleopatra's Egypt?" }
    { group:294, id:35, text: "Your Family History cannot add the life of Cleopatra to its annals until you have defeated the Ancient Conquerors." }
    { group:294, id:36, text: "Begin" }
    { group:294, id:37, text: "Play" }
    { group:294, id:38, text: "Individual Missions" }
    { group:294, id:39, text: "Campaigns" }
    { group:294, id:40, text: "You can only replay missions after you complete them successfully." }
    { group:294, id:41, text: "Pharaoh" }
    { group:294, id:42, text: "Cleopatra" }
    { group:295, id:0, text: "That festival put everyone into such good spirits, the city should hold another one soon." }
    { group:295, id:1, text: "It's been a few months since the last festival. This would be a good time for another." }
    { group:295, id:2, text: "There've been no festivals for quite some time, and people are starting to complain." }
    { group:295, id:3, text: "It's been more than a year since the last festival. People feel bored and overworked." }
    { group:295, id:4, text: "It's been almost two years since the last festival. The people desperately need a break." }
    { group:295, id:5, text: "More than two years have passed with no festivals! People are starting to feel hopeless." }
    { group:295, id:6, text: "People talk wistfully of 'the good old days', when festivals used to relieve the monotony." }
    { group:295, id:7, text: "That was such a wonderful festival! It takes a lot of time to prepare a gala like that." }
    { group:295, id:8, text: "Festivals take so much time and effort to prepare that it might be wise to order one now." }
    { group:295, id:9, text: "The last festival was long enough ago that it's just about time to order another." }
    { group:295, id:10, text: "The common festival is nearly ready. People are all talking about next month's holiday." }
    { group:295, id:11, text: "The common festival is being prepared. Just two more months until everyone gets a holiday!" }
    { group:295, id:12, text: "Preparations for the common festival being held in three months will begin next month." }
    { group:295, id:13, text: "Festival organizers are firming up plans for the common festival coming in four months." }
    { group:295, id:14, text: "The common festival will take place in five months. Organizers are reviewing suggestions." }
    { group:295, id:15, text: "Planners are confident that they will be ready for a common festival in six more months." }
    { group:295, id:16, text: "Harried organizers promise that your common festival will be held seven months from now." }
    { group:295, id:17, text: "The common festival won't occur for another eight months. Planning has barely even begun." }
    { group:295, id:18, text: "Festival organizers are so busy that your requested common festival is nine months away." }
    { group:295, id:19, text: "Another one already? It will be ten months before organizers can hold a common festival." }
    { group:295, id:20, text: "The lavish festival is almost ready. People are excited about next month's celebration!" }
    { group:295, id:21, text: "The lavish festival is being prepared, and we have only two more months to get ready." }
    { group:295, id:22, text: "The lavish festival is being readied. In three months, we'll have a memorable celebration." }
    { group:295, id:23, text: "Planners have hit their stride, and the lavish festival will surely occur in four months." }
    { group:295, id:24, text: "Entertainers are polishing their acts for the lavish festival to be held in five months." }
    { group:295, id:25, text: "Planners confirm that the new lavish festival will take place in six months, as promised." }
    { group:295, id:26, text: "Organizers are weighing public suggestions for the lavish festival coming in seven months." }
    { group:295, id:27, text: "Some entertainers are working out new routines for the lavish festival eight months hence." }
    { group:295, id:28, text: "With so much planning left to do, the lavish festival won't occur for another nine months." }
    { group:295, id:29, text: "Because no one has time to devote to it yet, the lavish festival will occur in ten months." }
    { group:295, id:30, text: "Planners are so busy that they have to schedule the new lavish festival eleven months out." }
    { group:295, id:31, text: "The grand festival is nearly ready. In one more month, it'll be fresh beer for everyone." }
    { group:295, id:32, text: "The grand festival's preparation has two months left. The anticipation is unbearable!" }
    { group:295, id:33, text: "The grand festival is being readied. People have only three more months to make plans." }
    { group:295, id:34, text: "The grand festival is being prepared. No one wants to wait the four months planners need!" }
    { group:295, id:35, text: "Organizers can start preparations next month, enabling a grand festival in five months." }
    { group:295, id:36, text: "Jugglers will unveil some real surprises at the grand festival, just six months from now." }
    { group:295, id:37, text: "Musicians are all writing new songs for the grand festival, now only seven months away." }
    { group:295, id:38, text: "Dancers can be seen rehearsing daring new moves for the grand festival, eight months out." }
    { group:295, id:39, text: "Planners have mustered enough ideas and energy to throw a grand festival in nine months." }
    { group:295, id:40, text: "Festival organizers are working overtime to ready the new grand festival in ten months." }
    { group:295, id:41, text: "Planners are confident that they can properly throw a grand festival in eleven months." }
    { group:295, id:42, text: "Organizers are so overworked that the grand festival you ordered will be a year from now." }
    { group:296, id:0, text: "Eternal Houses of Egypt" }
    { group:296, id:1, text: "Mission" }
    { group:296, id:2, text: "Best Family" }
    { group:296, id:3, text: "Difficulty Level" }
    { group:296, id:4, text: "Score" }
    { group:296, id:5, text: "House of" }
    { group:296, id:6, text: "There are no high scores." }
    { group:297, id:0, text: "Your family's earliest recorded ancestor rose to prominence, and learned the rudiments of leadership." }
    { group:297, id:1, text: "After relocating the family to Thinis, your ancestor helped the Thinnite Confederation unite Upper and Lower Egypt." }
    { group:297, id:2, text: "Family myths say that your clan discovered important new technologies and learned to exploit the Inundation. " }
    { group:297, id:3, text: "Your family first entered official Egyptian histories when Narmer appointed an ancestor to the position of Royal Architect." }
    { group:297, id:4, text: "Your family had a prominent role in founding Egypt's first capital city, and building the mastaba there. " }
    { group:297, id:5, text: "Legend has it that your family opened the copper mines at Timna that proved key to Pharaoh Den's success in keeping the Bedouin at bay." }
    { group:297, id:6, text: "For the first time, one of your ancestors chose the waters over dry land, and learned all of the maritime skills - including warfare." }
    { group:297, id:7, text: "For the first time, one of your ancestors chose the waters over dry land, and learned the maritime skills of peacetime." }
    { group:297, id:8, text: "Your people established an important military outpost far from civilization, opening trade routes to Africa that still endure. " }
    { group:297, id:9, text: "At the pleasure of Pharaoh Nebka, your family reaped the mineral wealth of the First Cataract, without which many tombs could not have arisen, and many nobles would have been denied the Field of Reeds." }
    { group:297, id:10, text: "Your ancestor proudly achieved the Vizier Imhotep's vision, and built Egypt's first stone pyramid to house Djoser's mummy.  " }
    { group:297, id:11, text: "Your heroic forebear wrested valuable gems and copper from the hostile Sinai and its fierce inhabitants, who did their utmost to thwart the effort. " }
    { group:297, id:12, text: "The improving fortunes of your clan are attested by the family's tomb at Meidum, which stands to this day as testimonial to the bloodline's importance to Egypt. " }
    { group:297, id:13, text: "The fortress erected at Buhen, and the finality with which your kin crushed the enemy there, projected Egyptian power to the Second Cataract, in the lands claimed by hostile Nubia.  " }
    { group:297, id:14, text: "While others concerned themselves with extending the Kingdom's boundaries, your ancestor built the most magnificent tomb ever conceived - Snofru's bent pyramid." }
    { group:297, id:15, text: "Even as Snofru welcomed an heir whom royal seers branded a tyrant, your own forebears completed the world's first perfect pyramid to house Pharaoh's remains. " }
    { group:297, id:16, text: "Despite Khufu's emerging tyranny, your ancestor loyally served as his Royal Governor and defended Egypt's borders from the Kushite invaders. " }
    { group:297, id:17, text: "Protected from the Kushite threat, your progenitor opened productive quarries at Tura to satisfy Khufu's inexplicable demand for seemingly limitless amounts of limestone.  " }
    { group:297, id:18, text: "Your ancestor rose to be Nomarch to Khufu and Khafra, and, through a force of will rivalling Pharaoh's own, erected the eternal Great Pyramid and its guardian Sphinx.  " }
    { group:297, id:19, text: "Pharaoh declared Ra to be supreme among gods, and charged your forebear with extending the Sun Cult's dominance to the hostile Western Desert wastelands at the very edge of the Kingdom." }
    { group:297, id:20, text: "Pharaoh Userkaf declared Ra supreme over the gods, and commissioned your ancestor to build the grandest Sun Temple of all in the lush Delta, a region devoid of building stone." }
    { group:297, id:21, text: "While Egypt's enemies swarmed like beetles to a decaying body, your family reached the rank of Chancellor and prevented the Kingdom's foes from severing her lifelines." }
    { group:297, id:22, text: "While Egypt's enemies swarmed like beetles to a decaying body, your family attained the rank of Chancellor and showed an ability to govern capably while all else crumbled.  " }
    { group:297, id:23, text: "Your ancestors gave their loyalty to the legitimate Inyotefs and restored Thinis to glory, despite the concerted efforts of rebellious armies to thwart this achievement." }
    { group:297, id:24, text: "Two factions fought for the heart of Egypt, even as her belly went empty. Your ancestor saved many from starvation while lending crucial support to the legitimate dynasty." }
    { group:297, id:25, text: "Mentuhotep awarded your family the rank of Vizier, and relied heavily on their support in crushing the efforts of remaining rebels and would-be usurpers to prevent reunification. " }
    { group:297, id:26, text: "Mentuhotep awarded your family the rank of Vizier, and his reunification effort benefited greatly from the reflected glory of the stately city that you raised from the dust. " }
    { group:297, id:27, text: "At last, a member of your family fulfilled fate and became Pharaoh. Your clan became a royal dynasty, built a new capital and silenced the opposition with compassion and good works." }
    { group:297, id:28, text: "Your divine ancestor conquered our ancient enemies in northern Nubia, instilled respect for your dynasty in the Kushites, and established an important Red Sea port." }
    { group:297, id:29, text: "Your divine forebear's manufacturing port on the Red Sea brought untold new wealth and luxuries to your people, and your family tomb will endure through the ages." }
    { group:297, id:30, text: "Your illustrious ancestor, who rests today in a fabulous mausoleum, smashed the Nubian navy and conquered one of their fairest cities. " }
    { group:297, id:31, text: "The city of Bubastis remains the jewel in the Twin Crowns to this day. Your forebear built a city that all of Egypt regards with pride." }
    { group:297, id:32, text: "Turning the Hyksos' dread chariots into an Egyptian weapon, and using it against enemies throughout our beleagured Kingdom, was a brilliant achievement that history will never forget." }
    { group:297, id:33, text: "Truly, your family has long been blessed with wisdom. Your ancestor's strategy of inspiring Egypt's greatest generals to superhuman efforts paid off handsomely." }
    { group:297, id:34, text: "You founded a New Kingdom, secured the forests of Byblos for all time, and taught ferocious Hittites and mysterious Sea People alike to respect Egypt's borders." }
    { group:297, id:35, text: "You created undreamed-of wealth for your New Kingdom, while defending Egyptian cities from enemies old and new.   " }
    { group:297, id:36, text: "Your reign was the greatest that Egypt has ever known. Our borders spanned the known world, and our people enjoyed luxuries unimagined." }
    { group:297, id:37, text: "Having defeated every foe and brought untold prosperity to the Kingdom, you then built a pyramid surpassing even that of the legendary Khufu.  " }
    { group:297, id:38, text: "With the founding of Deir el-Medina, the pharaohs can rest for eternity with little fear of being disturbed by dreaded tomb robbers." }
    { group:297, id:39, text: "With little time to spare, Tutankhamun's tomb was constructed and provided with lavish burial provisions." }
    { group:297, id:40, text: "Seti I's burial tomb is a marvel, made even more noteworthy by the waves of tomb robbers that had to be suppressed to build it.  It is a shame that the eyes of the world will not be able to gaze upon its eternal beauty." }
    { group:297, id:41, text: "The port of Sumur now bustles with trade as it works to satisfy our homeland's thirst for wood and other precious commodities." }
    { group:297, id:42, text: "Egypt witnessed her greatest victory at the battle of Qadesh and reasserted her dominance over the land of Amurra. The Hittite threat was crushed once and for all." }
    { group:297, id:43, text: "The Colossi at Abu Simbel will speak forever of the power and glory of Egypt." }
    { group:297, id:44, text: "The mortal remains of Ramses II rest well in his lavish tomb.  In his eternal life he will surely continue to help guide the hand of Egypt." }
    { group:297, id:45, text: "The dangerous brigands from the sea that foolishly sought to settle on the lands of Egypt were forcefully turned back. Egypt's borders were once again secure." }
    { group:297, id:46, text: "The fortified outpost in the hinterlands of Egypt withstood wave upon wave of Assyrian attacks, ensuring that the vile enemy did not penetrate further within the Two Lands." }
    { group:297, id:47, text: "The people of Achoris will long tell the tale of the decimation of the Persian fleet and annihilation of their infantry. A serious blow was dealt to the Persians' dreams of conquest." }
    { group:297, id:48, text: "In a mere dozen years, Alexandria sprung forth from the land and developed into a thriving metropolis where only a few years before a poor fishing village stood." }
    { group:297, id:49, text: "Alexandria was adorned with the Great Library and the Pharos Lighthouse and her prominence throughout the world increased." }
    { group:297, id:50, text: "Mithradates' Roman legions put down Cleopatra's rebellious sibling, Ptolemy XIII, in a great battle along the shores of Lake Mariut." }
    { group:297, id:51, text: "The glorious development of Alexandria continued when the Caesareum and another mortuary temple were added to its list of wondrous sites." }
    { group:297, id:52, text: "The combined strength of Egypt's fleet and Antony's forces smashed Octavian, and Egypt and Rome were united as equals to rule over the known world." }
    { group:298, id:0, text: "Final Culture rating was" }
    { group:298, id:1, text: "Final Prosperity rating was" }
    { group:298, id:2, text: "Final Monument rating was" }
    { group:298, id:3, text: "Final Kingdom Rating was" }
    { group:298, id:4, text: "Ending population was" }
    { group:298, id:5, text: "Final city funds were" }
    { group:298, id:6, text: "Mission was completed in" }
    { group:298, id:7, text: "Lowest Diff. Level Used:" }
    { group:298, id:8, text: "Final Score was:" }
    { group:298, id:9, text: "years" }
    { group:299, id:0, text: "Direct result" }
    { group:299, id:1, text: "Incidental" }
    { group:299, id:2, text: "In spite of" }
    { group:299, id:3, text: "No cause" }
    { group:299, id:4, text: "Continuous/Cyclical" }
    { group:299, id:5, text: "Specific as needed" }
    { group:299, id:6, text: "Automatic" }
    { group:299, id:7, text: "Direct" }
    { group:299, id:8, text: "BTW" }
    { group:299, id:9, text: "Despite" }
    { group:299, id:10, text: "None" }
    { group:299, id:11, text: "Cycle" }
    { group:299, id:12, text: "Spec" }
    { group:299, id:13, text: "Auto" }
        
    { group:304, id:0, text: "Next Page" }
    { group:304, id:1, text: "Previous Page" }
    { group:305, id:0, text: "Your family has never faced this challenge. To view mission objectives, click on the button below." }
    { group:306, id:0, text: "Henna Farm" }
    { group:306, id:1, text: "The finest henna is grown here and sent to the Paint Maker, who makes the bright paints that decorate tomb walls." }
    { group:306, id:2, text: "Production is" }
    { group:306, id:3, text: "complete." }
    { group:306, id:4, text: "Your Overseer of Commerce has decreed that henna production should stop." }
    { group:306, id:5, text: "Without any workers, this farm can't possibly grow any henna." }
    { group:306, id:6, text: "This farm has all the workers it needs. They are in the fields, tending to the plants." }
    { group:306, id:7, text: "This farm could harvest more henna if it had more workers." }
    { group:306, id:8, text: "This farm doesn't have enough workers to tend to an entire field of henna." }
    { group:306, id:9, text: "There are very few people working here. The henna harvest will suffer as a result." }
    { group:306, id:10, text: "Most of this farm is barren. It needs more workers before it can grow more henna." }
    { group:306, id:11, text: "Locusts have devoured all that was growing here, and the land needs some time to recover." }
    { group:306, id:12, text: "Land is" }
    { group:306, id:13, text: "fertile." }
    { group:306, id:14, text: "The next henna harvest is in" }
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
    { group:308, id:1, text: "Exotic animals from near and far delight crowds of citizens at the Zoo." }
    { group:308, id:2, text: "This Zoo has zookeepers, but needs a supply of game meat before any animals can call it home." }
    { group:308, id:3, text: "This Zoo has employees, but with no straw it cannot host any animals." }
    { group:308, id:4, text: "People are afraid to visit a Zoo without zookeepers. Until the Zoo finds some employees, it won't bring the neighborhood any benefit." }
    { group:308, id:5, text: "With no animals, this Zoo is nothing more than empty cages." }
    { group:308, id:6, text: "Game Meat:" }
    { group:308, id:7, text: "Straw:" }
    { group:309, id:0, text: "This danger of disease is so great that even the laughing hyenas are sad." }
    { group:309, id:1, text: "How will we feed the animals when we can't feed ourselves?" }
    { group:309, id:2, text: "Our defenses are terribly weak. Perhaps I should train the hippo to fight?" }
    { group:309, id:3, text: "Even an elephant cannot recall when the worker shortage has been worse." }
    { group:309, id:4, text: "When a god is angry you don't want your neck sticking out like a giraffe's!" }
    { group:309, id:5, text: "Pharaoh is so unhappy. I hope the zoo animals are not needed for exotic gifts!" }
    { group:309, id:6, text: "Trying to land a job in this city is more difficult than trapping a wild lion." }
    { group:309, id:7, text: "The entertainment situation in this city stinks worse than the monkey cages." }
    { group:309, id:8, text: "Living here is better than sleeping in the lions' pen." }
    { group:309, id:9, text: "I am happier than a mud-covered hippo to be living in this city." }
    { group:310, id:0, text: "Popup Messages" }
    { group:310, id:1, text: "Selected messages appear at top of screen only" }
    { group:310, id:2, text: "Flood Messages" }
    { group:310, id:3, text: "Population Messages" }
    { group:310, id:4, text: "Compliance Now Possible" }
    { group:310, id:5, text: "Kingdom Standing Climbs" }
    { group:310, id:6, text: "Festivals" }
    { group:310, id:7, text: "Minor Blessings" }
    { group:310, id:8, text: "Price Changes" }
    { group:310, id:9, text: "Trade Level Changes" }
    { group:310, id:10, text: "Wage Changes" }
    { group:310, id:11, text: "Disease Strikes" }
    { group:310, id:12, text: "Malaria" }
    { group:310, id:13, text: "Employees Needed" }
    { group:310, id:14, text: "Ok" }
    { group:310, id:15, text: "Cancel" }
    { group:311, id:0, text: "Select Monument Era" }
    { group:311, id:1, text: "Pyramids" }
    { group:311, id:2, text: "Valley of the Kings" }
    { group:311, id:3, text: "Alexandria" }
    { group:311, id:4, text: "Abu Simbel" }
    { group:312, id:0, text: "Artisans' Guild" }
    { group:312, id:1, text: "Artisans meet here to prepare plaster from clay and mix their paints before heading out to decorate a tomb. " }
    { group:312, id:2, text: "This guild has no employees and cannot send out any artisans." }
    { group:312, id:3, text: "This guild has a full palette of artisans who waste no time decorating the interiors of tombs." }
    { group:312, id:4, text: "This guild lacks an artisan or two. Tomb painting has slowed a little bit." }
    { group:312, id:5, text: "This guild is doing its best to provide artisans to the tomb and provides fewer tomb artisans than it could." }
    { group:312, id:6, text: "This guild needs many more workers. The few lone artisans that work here are doing what they can to decorate the tomb, but they need more help." }
    { group:312, id:7, text: "Paint in the tombs has plenty of time to dry. Unless this guild finds more workers, the tomb may take an eternity to decorate." }
    { group:312, id:8, text: "Artisans are hard-pressed to decorate a tomb without the paint it needs from a Paint Maker or Storage Yard." }
    { group:312, id:9, text: "The guild won't send any artisans to the tomb until it receives a supply of clay." }
    { group:312, id:10, text: "Paint:" }
    { group:312, id:11, text: "Clay:" }
    { group:313, id:0, text: "Paint Maker" }
    { group:313, id:1, text: "Here, henna is crushed and processed into paint, which artisans use to lavishly decorate the walls of Royal Burial Tombs." }
    { group:313, id:2, text: "Production is" }
    { group:313, id:3, text: "complete." }
    { group:313, id:4, text: "Your Overseer of Commerce has stopped paint production." }
    { group:313, id:5, text: "This Paint Maker's staff has completely dried up. With no workers, no paint can be made." }
    { group:313, id:6, text: "With a full staff, this Paint Maker produces paint as quickly and efficiently as it can." }
    { group:313, id:7, text: "This Paint Maker's staffing level is a little thin, so paint production is compromised." }
    { group:313, id:8, text: "This Paint Maker is understaffed, and produces paint more slowly than it should." }
    { group:313, id:9, text: "This Paint Maker needs many more workers. Paint production here has slowed to a crawl." }
    { group:313, id:10, text: "Only a few workers are employed by this Paint Maker. The small staff can hardly turn out any paint at all." }
    { group:313, id:11, text: "This workshop needs henna from a Henna Farm or Storage Yard before it can make any paint. " }
    { group:313, id:12, text: "Henna:" }
]