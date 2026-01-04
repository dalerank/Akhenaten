log_info("akhenaten: messages config started")

game_messages_en {
    message_potter_history {
        id: 1,
        
        size [30, 28]
        title { text: "Potter" }
        advisor: ADVISOR_TRADE
        content {
            text: "Potters need a supply of clay to function. Some cities can produce their own clay by constructing @92Clay&Pits. Other cities may need to import clay from a trade partner (click @47here for more on trade). @PCartpushers bring supplies of clay to Potters from Clay Pits, if the city has them, or from @4Storage&Yards. The Potter stores some extra clay in its yard to keep him working for awhile if clay deliveries are interrupted for some reason. @PPotters also need road access and a nearby source of labor. Potters are at their most productive if they are fully staffed, but will still operate (although at reduced efficiency) when understaffed. If the Potter is turning out pottery, you will see him hard at work. Cartpushers employed by the Potter take finished pottery to a Storage Yard or to a @473Lamp&Maker (who needs a supply of pottery and oil to produce lamps). @PPottery is an important commodity in the city. @56Houses need a supply of pottery to evolve to higher levels, and pottery must be constantly replenished to prevent houses from devolving to lower levels. Demand for pottery never ceases: households are always replacing broken or worn-out pieces. See @2Bazaars for more on how to get finished goods to the citizens. @PPottery is also integral to the construction of @478Royal&Burial&Tombs. When a Lamp Maker fills pottery with oil, it becomes a powerful lamp that lights the way for tomb workers.  @PPottery can also be imported or exported. See @47trade for information on how to open trade routes. If your city is trading pottery, be sure to keep citizens' needs in mind. Let your @24Overseer&of&Commerce know how much pottery should be stored in Storage Yards for citizens' use, or let your Overseer determine an amount.  @PPeople don't want to live too near a noisy, dusty Potter, so it has a negative effect on the desirability of neighboring land. @L@LTo learn more about pottery making in ancient Egypt, click @198here."
        }
    }

    message_bazaar_history {
        id: 2,
        
        size [30, 28]
        title { text: "Bazaar" }
        content {
            text: "Without Bazaars, people will never have access to the food and goods stored in the @3Granaries and @4Storage&Yards. Only Bazaars distribute needed supplies to the populace. @PTo function properly, Bazaars need road access and a full staff. The Bazaar will still function if it is understaffed, but at a much reduced efficiency. @PEach Bazaar employs two buyers, one to purchase food from Granaries, the other to purchase items from Storage Yards.  Each buyer is specialized: the Granary buyer cannot procure items from a Storage Yard, and vice versa.  Each of these buyers, however, can buy more than one item at a time.  So, for example, a Bazaar buyer that goes to the Granary can buy grain and pomegranates. She cannot, however, buy grain and pottery, because pottery is never stored in a Granary.  @POnce a Bazaar buyer finds the items she needs, a string of helpers carries the load back to the Bazaar. @PThe Bazaar buyer is a @42'destination&walker.' She spends her life shuttling between her Bazaar and the city's Granaries and Storage Yards.  Her job description exempts her from walking clear across the city to reach supplies, and she won't do business with more than three supply sources within her range.  If you catch her standing around when there's work to be done, you're probably expecting her to walk too far or deal with too many suppliers.  @PThe other Bazaar employee, the Bazaar trader, takes the items that buyers bring back and distributes them to nearby neighborhoods. As the trader passes within two spaces of housing, she supplies each house with whatever it needs if she has the items in stock. She also finds out what goods her customers want in order to improve their housing, and reports these needs to the buyer so she can get the necessary items. The first priority is to replenish the items a house needs to keep from devolving (see the @56housing&desirability entry). When those needs are satisfied, they try to get the next item the house needs to improve. @PThe Bazaar trader, then, is a 'roaming walker.' Her purpose is to wander through nearby blocks and serve her customers, rather than to proceed to some specific destination. If a particular housing section is not receiving goods, watch where the trader walks. She does not follow a set route. Every time she encounters an intersection, she chooses which way to go, and she won't always take the same path. Plan the city's roads carefully, and use @358Roadblocks to corral Bazaar traders. A Bazaar that has evolved to its more advanced state (shown by one of its tents being replaced by a small building) sends out two 'roaming walkers' instead of one.  @PPeople's needs for basic commodities, like food and pottery, must be met before more advanced wants, like beer or linen, are addressed. Bazaar buyers will ignore a Storage Yard brimming with linen if the houses they serve are crying out for pottery. It's very important, then, to maintain steady supplies of a commodity once houses start demanding it. Remember that as houses evolve, they usually hold more people and, so, consume more goods. Sometimes you'll have to add more Bazaars to keep a neighborhood properly stocked. Right-click on a house to see what its occupants need at any given moment.   @PTo help make sure that residents are getting the food and goods they need, build Granaries and Storage Yards near Bazaars.  Use the Granary's and Storage Yard's special orders to make sure they have the goods and foods that the Bazaars need. @PIf you want more control over a Bazaar, click on its 'Special Orders' button to see a list of all the commodities that it can stock. Click on an item to tell the Bazaar whether or not to buy it. @PWhile citizens need to live near Bazaars to have access to all the goods they desire, no one wants to live too close to them. They are noisy places, sometimes filled with unsavory characters, and can be smelly too.  @L@LTo get a feel for the sights, sounds and smells of an ancient Egyptian Bazaar, click @199here."
        }
    }

    message_building_granary {
        id: 3,
        
        size [30, 28]
        title { text: "Granary" }
        content {
            text: "Granaries store the food that citizens eat. @2Bazaar&buyers collect food from the Granary to distribute to the populace. @PGranaries need road access and labor in order to operate. You can see what the Granary is storing by looking in its fill holes.  Right-click on a Granary to see precisely how much of each food it holds. @P@45Food&farms, @84Fishing&Wharves, @360Cattle&Ranches and @359Hunting&Lodges employ delivery men to bring their produce to Granaries. It's generally a good idea to have Granaries close to food producers. If a delivery man has to walk so far that his employer finishes producing another load of food before he returns with his empty cart, the production facility will sit idle until he comes to take away the food that has piled up there.   @PIf all Granaries are full, delivery men will wait around until some space in a Granary opens up, unless you have instructed a @4Storage&Yard to accept the particular food.   @PTo manage the flow of foods in the city, give Granaries Special Orders.  Right click on a Granary, then click the Special Orders button to get started.  All items the Granary can store are listed for you.  Click on an item to change the way that the specific Granary handles the food.  The choices are: @L@LAccept All/Fill Granary @LTo limit how much of a single food a Granary accepts, use the Fill command.  You can tell the Granary to Fill 1/4, 1/2 or 3/4 of the Granary.  If you do not want to limit the Granary's intake of a particular food, tell the Granary to Accept All of the item. This choice is useful when you want a Granary to store equal amounts of multiple food types.   @L@LDon't Accept  @LUse this command to tell a Granary to stop accepting a food altogether.  The Granary will not accept any new shipments of the particular food, but Bazaar buyers and cart pushers from other Granaries will continue to collect the item from the Granary until the stock is completely depleted. Use this option to make delivery men bypass a nearby Granary in favor of one farther away, or to prevent a food that you want to export from being consumed.   @L@LGet Up To @LIf a Granary is running low on a particular food that you want it to have on hand, use the Get Up To command.  The Granary's cart pusher will search for the item in other Granaries or in the city's Storage Yards until he has met the request.  You can tell a Granary to get up to 1/4, 1/2, 3/4 or the full capacity of the Granary. This option can enable Granaries far away from the city's food producers to remain stocked. @L@LEmpty Food   @LIf you issue this command, the Granary's cart pushers will try to empty the Granary's stock of food, looking for other Granaries or Storage Yards that have been told to accept the item. A Granary told to empty itself will not accept new shipments of the food that it is trying to send elsewhere. Use this order if you have decided to demolish a Granary, or if you want to remove one type of food that it carries. @L@LGranaries are dusty, often verminous, and not at all welcome neighbors. Citizens don't relish living near them. @L@LClick @5here to read about Granaries in ancient Egypt."
        }
    }

    message_building_storage_yard {
        id: 4,
        
        size [30, 28]
        title { text: "Storage Yard" }
        content {
            text: "Storage Yards are the repository for all finished goods and excess raw materials.  They also store food if you specifically tell them to do so (see Special Orders, below) and help to trade imported and exported items (see the @47trade entry).   @PTo operate, Storage Yards need road access and a nearby supply of labor. Storage Yards are most efficient when they are fully staffed. They can operate if understaffed, but they might stop accepting particular commodities. @PEach Storage Yard is divided into eight sections and can store up to eight different items. Each section can accept only one type of item, but more than one section can store the same item.  The quantity of each item that can be stored depends upon the item's size.  The larger the item, the less of it a Storage Yard can store.  For example, one section of a Storage Yard can hold many more pieces of pottery than blocks of stone.   @PMany other buildings need easy access to the Storage Yards. @46Industry delivers products to the closest Storage Yard, and Bazaar buyers proceed to the nearest Storage Yard for goods their customers need. Storage Yards, in turn, will deliver raw materials and other needed supplies to the closest buildings first. Cart pushers from Storage Yards will grudgingly travel long distances if necessary, but industries could be idle while they are waiting for needed supplies. It's wise to locate Storage Yards near all the facilities that need them. @PRight-click on a Storage Yard to find out exactly how much of each item the particular Storage Yard has on hand and whether or not it can accept more goods.  If a Storage Yard can’t hold anymore of a particular item, the item is displayed in yellow. @PYou can control the influx and outflow of goods with Special Orders. When you click on the Special Orders button, a panel listing all the goods currently available to your city is displayed. Sometimes, you will have access to dozens of goods. Use the scroll buttons at the top of the screen to see more of the goods available. @PClick on an item to tell the Storage Yard how to handle it.  The orders are: @L@LAccept All/Fill   @LTo limit how much of a single item a Storage Yard accepts, use the Fill command.  You can tell the Storage Yard to Fill 1/4, 1/2 or 3/4 of the Storage Yard.  If you do not want to limit the Storage Yard's intake of a particular item, tell the Storage Yard to Accept All of the item.  This choice is useful when you want a Storage Yard to store equal amounts of multiple commodities, or if you want a yard to store food for export.   @L@LDon't Accept   @LUse this command to tell a Storage Yard to stop accepting an item altogether.  The Storage Yard will not accept any new shipments of the particular item, but Bazaar buyers, trade partners and industries in the city can use the supplies the Storage Yard still has on hand until the stock of the item is completely depleted.  Use this option to make delivery men bypass a nearby Storage Yard in favor of one farther away.  Unless you tell them otherwise, Storage Yards do not accept food, thus ensuring that food is delivered to Granaries instead.  @L@LGet Up To   @LIf a Storage Yard is running low on a particular item you would like it to have on hand, use the Get Up To command.  The Storage Yard's cart pusher will search for the item in other Storage Yards until he has met the request.  You can tell a Storage Yard to get up to 1/4, 1/2, 3/4 or the full capacity of the Storage Yard.  This option can enable outlying Storage Yards to remain stocked. @L@LEmpty   @LIf you issue this command, the Storage Yard's cart pusher will try to empty the Storage Yard's stock of the particular item, looking for industries or other Storage Yards that can accept the item.  Use this order if you have decided to demolish a yard, or if you want to remove one type of goods that it carries. @L@LStorage Yards are key to getting goods to the city's residents.  @2Bazaars get the goods citizens' need directly from Storage Yards. Storage Yards are also vital for trade. All imported goods are stored in the Storage Yards, and all goods earmarked for export are kept there until traders from other cities come to collect them. @L@LFind out about ancient Egyptian Storage Yards by clicking @6here."
        }
    }

    message_granary_history_2 {
        id: 5
        
        size [30, 20]
        title { text: "Granary" }
        content {
            text: "Because farming was largely impossible during the Inundation, granaries were vitally important to ensure that the ancient Egyptians were fed year-round. Granaries not only stored grain and other foods, but also manufactured flour.  @L@LThe granary evolved over time. In the Archaic period, the Egyptian granary was shaped like a cone with a domed top. They were made from wood or brick, and the largest ones had ladders or steps leading to the filling hole. In the Middle Kingdom, the granary was shaped like a quadrangle and had a flat roof with several filling holes, like those depicted in our game. A third type of granary was used only for seed to be sown during the next growing season. These granaries were shaped like a trapezoid, a distinctly different shape than granaries used for food storage, so that the seed grain would not be eaten by mistake. @L@LMost granaries were strictly maintained by the government. Soldiers, construction workers and other non-agricultural workers all ate from these granaries. Some wealthy private citizens had their own granaries, and some peasants had their own small granaries to store whatever part of the harvest they were allowed to keep."
        }
    }

    message_storage_yard_history {
        id: 6
        
        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Storage Yard", pos [125, 15] }
        subtitle { text: "History" }
        content {
            text: "Located near the Nile and close to major trade routes, Storage Yards held surplus supplies and items intended for trade. Because little rain fell, many Storage Yards in ancient Egypt were open-air. They were well supervised by scribes who kept strict track of the inventory."
        }
    }

    message_keyboard_commands {
        id: 7
        
        size [30, 28]
        title { text: "Keyboard Commands" }
        subtitle { text: "Game Controls" }
        content {
            text: "Several commands in Pharaoh can be issued using the keyboard.  The commands are: @L@LKey    Effect @LA      Orders a selected warship to attack  @Pall enemies. @L@LC      Shows the Risks: Crime Overlay,  @Por orders a selected charioteer company to  @Pcharge. @L@LD      Shows the Risks: Damage Overlay. @L@LE      Orders a selected transport ship  @Pto evade enemies. @L@LF      Shows the Risks: Fire Overlay, or @Porders a selected company to return to its  @PFort. @L@LH      Hides cliff terrain. @L@P       Orders a selected ship to hold  @Pits current position. @L@LL      Centers your view on a different @Pmilitary company each time it's pressed.   @L@PIf a company is selected, 'L' issues  @Pthe 'hold ground in loose formation' order. @L@LM     When you select a monument from  @Pthe building list, its image attaches to your  @Pcursor and shows you how much land the  @Pmonument will occupy.  Holding down the 'M'  @Pkey freezes the monument's 'footprint' into  @Pplace so that you can move your viewpoint  @Paround the city without moving the  @Pmonument's tentative location.  Release  @Pthe 'M' key to resume normal mouse  @Pbehavior, or click to place the monument @Pin the footprint's current location.   @L@P       Pressing 'M' when a military  @Pcompany is selected issues the mop-up @Porder. @L@LN      Orders a selected company or  @Pwarship to attack nearby enemies. @L@LP      Pauses the flow of time in the  @Pgame. You cannot build while time is paused. @L@LR      When placing a Statue, Gatehouse  @Por Temple Complex, 'R' rotates the  @Pstructure's orientation one-quarter turn  @Pclockwise.  Statues will display multiple  @Pstyles.   @L@P       With a military company selected,  @P'R' orders the soldiers to change their  @Porientation (rotate). 'R' also orders a  @Pselected transport or warship to return to  @Pthe Shipwright for repairs. @L@LT      Shows the Risks: Problems  @POverlay.   @L@PWith a military company selected,  @P'T' issues the 'hold ground in tight  @Pformation' order. @L@LW     Shows the Water Overlay. @L@PIf a warship or transport ship is  @Pselected, 'W' orders the ship to return to  @Pits home Wharf. @L@LX      Shows Tax Overlay @L@LY      Shows the Risks: Malaria Overlay @L@LZ      Shows the Risks: Disease Overlay @L@LSpace   Press the spacebar to toggle  @Pbetween your last selected Overlay and the  @Pnormal city view. @L@LEsc    exits the game. @L@LOpen bracket @Preduces game speed by 10 percent. @L@LClose bracket @Pincreases game speed by 10 percent. @L@LAccent @POverseer of the Workers @L@L1       Overseer of the Military @L@L2      Political Overseer @L@L3      Ratings Overseer @L@L4     Overseer of Commerce @L@L5     Overseer of the Granaries @L@L6     Overseer of Public Health @L@L7     Overseer of Learning @L@L8     Overseer of Diversions @L@L9      Overseer of the Temples @L@L0     Overseer of the Treasury @L@L-      (minus sign) Chief Overseer @L@L=      (equals sign) Overseer of Monuments @L@LCTRL+F1 @PCreates F1 bookmark at current location @L@LCTRL+F2 @PCreates F2 bookmark at current location @L@LCTRL+F3 @PCreates F3 bookmark at current location @L@LF1     Goes to F1 bookmark @L@LF2    Goes to F2 bookmark @L@LF3    Goes to F3 bookmark @L@LF6    Switches to windowed view @L@LF7    Set 640x480 screen resolution @L@LF8    Set 800x600 screen resolution @L@LF9    Set 1024x768 screen resolution"
        }
    }

    message_work_camp_history {
        id: 8
        
        size [30, 28]
        title { text: "Work Camp" }
        content {
            text: "Peasants gather at Work Camps to be assigned to work on nearby @45floodplain&farms or on @370monuments. During the growing season, most peasants draw farming duty. During the Inundation, everyone works on the city's monument project.  If there's no monument being built, peasant workers have nothing to do but play a lot of senet during the Inundation.  If your city has few Work Camps relative to its number of floodplain farms, you will notice a distinct rhythm that's set by the Inundation. @PWork Camps need road access and their own staff. It is best to place Work Camps near farms and monuments so that the peasants don't have far to walk.  Indeed, there is a limit to how far they'll trek to reach their back-breaking chore.  The more Work Camps the city has, the quicker monuments can be built, because more laborers will be available during the growing season. @PThe number of farms one Work Camp can support depends mostly on proximity.  A fully-staffed Work Camp supplies one peasant worker every week (four per month).  This worker walks to the nearest floodplain farm that's awaiting a peasant, where he will toil for six months.   @PWhen a farm is halfway through its peasant's work period, Work Camp employees notice that the farm will need another peasant if farming is to continue without interruption - remember that the growing season lasts nine months in most regions.  If you're using one Work Camp to supply a very large number of farms, some might never receive peasants, and those that do will have trouble keeping peasant workers continuously. @PYou could run a huge number of floodplain farms with only one or two Work Camps, but many farms wouldn't reach their potential, and peasants would only be available to work on the monument during the Inundation.   @PPractically speaking, one Work Camp can support four to six nearby floodplain farms without interruption and still contribute some peasants to the city's monument project.  Adding more Work Camps spreads the burden around and frees up more peasants to work on the monument during the growing season. @L@LFor more on the working life in ancient Egypt, click @155here."
        }
    }

    message_frequently_asked_questions {
        id: 9
        
        size [30, 28]
        title { text: "Frequently Asked Questions" }
        content {
            text: "Money @PQ: I want my city to have money - and loads of it. What's the best way to build up the city's coffers? @PA: The simple answer to this question is to ensure the city earns more than it spends.  @PMake sure that nearly all of the city's residents are paying taxes. Raising the tax rate will add to the city's coffers, but the money may not be enough to offset the poor @39City&Sentiment that raising taxes can cause. Also, open @47trade relations as soon as possible, and export as much as you can (consult the @32World&Map to see how close the city is to its yearly trade limits).  @PReducing the amount that a city spends also helps profits. Build the city slowly and carefully. Buildings themselves cost money, of course, but you must also consider the money needed to pay employees and the cost involved in providing employees with housing and services. Building a city up too fast could easily result in debt due to the cost of wages and ancillary services. @L@PQ: Why can't my city collect taxes? @PA: Be sure that you have built a Palace. Cities cannot collect taxes until a Palace has been built. @L@PQ: I'm working as hard as I can, but I haven't been paid. What gives? @PA: A common lament, to be sure. In Pharaoh, you cannot draw a personal salary until you have built a Mansion. @L@PQ: How do I pay tribute?  What happens if I don't? @PA: Your treasury automatically pays tribute at the end of the year, assuming that you have money.  Just be sure that there's money in the vaults at the end of the year.  If your coffers are empty, you can't pay tribute, and your @35Kingdom&rating will drop.  If you're unable to pay tribute for a second consecutive year, your Kingdom rating falls a little more, and if your indebtedness continues beyond that, the penalty becomes more severe.  Read up on @48debt. @L@LWalkers @L@PQ: How come a building that says it has access to labor never finds any workers? @PA: You probably built a @358Roadblock too close to the building.  Watch the building for a moment to ensure that its walker pops out on the correct side of the Roadblock.  Sometimes the building's employees send their walker off in the wrong direction.  This can be particularly vexing with labor access seekers, because the building that employs them believes that it has access to labor, but the Roadblock prevents the walker from ever reaching the labor pool.  Rebuild the Roadblock a space farther away. @L@LReligion @PQ: I'd like to throw a festival, but I'm not allowed to. How come? @PA: There are a number of reasons you might not be able to throw a festival. Does your city have a Festival Square?  No square, no festivals.  Have you already held two festivals in the last 12 months? A city can only have two festivals in any 12-month period. If you are throwing a grand festival, be sure you have enough beer stored to hold the event. Finally, check the city's coffers. If the city can't pay for a festival, you can't throw one. @L@PQ: My city's patron god keeps getting mad at me. What do I have to do to appease this god? @PA: A city's patron god requires more attention than the local deities. Make sure you have more Temples and Shrines dedicated to him or her than you do to other gods in the city, and consider spending the money to build a Large Temple Complex in the patron god's honor. @L@LEntertainment @PQ: I can't find a viable location for my entertainment venue. What could the problem be? @PA: With the exception of Senet Houses, entertainment venues must be placed over an intersection, either a 'T' or a crossroads. Also, there must be clear space around the intersection to accomodate the venues' stages. @L@PQ: I have plenty of entertainment venues in the city, but no entertainers. Why aren't they putting on shows? @PA: Make sure you have Training Centers built in the city. Performers must first learn their crafts before they entertain the masses. @L@PQ: Why isn't my Senet House working? @PA: The answer is beer. Make sure the Senet House has beer on hand to serve to its patrons. @L@LFarming @PQ: Why aren't the floodplain farms producing crops? @PA: Check to see if there is a Work Camp near the farms. Peasants from a Work Camp till floodplain farm soil. @L@PQ:  How many floodplain farms can a Work Camp support? @PA:  It depends.  Read the Help entry on @8Work&Camps for a full explanation. @L@PQ: I've built a Fishing Wharf, but it doesn't have a boat. Why not? @PA: Fishing boats are built by a Shipwright. Make sure there is an active one in the city. @L@LStorage and Distribution @PQ: Bazaars keep running out of food and items. What can I do to keep their shelves stocked? @PA: Make sure you build a Granary and a Storage Yard near the Bazaar. If a Bazaar buyer has a long way to travel, her Bazaar is bound to run out of something while she's gone. Use the Granary and Storage Yard Special Orders to make sure these buildings are well stocked with supplies. @L@PQ: How can I use Storage Yards most effectively? @PA: To get the most out of @4Storage&Yards, carefully consider their placement in the city and make good use of their special orders. Storage Yards should be placed nearby buildings, such as Bazaars, Docks, monument construction sites and industries, that need their stored supplies. Use the Storage Yard special orders to make sure the goods stored are the ones that the nearby buildings need. Storage Yards should also be near industrial structures to reduce the time industry cart pushers spend in transit. If the cart pusher has a long way to travel to deliver his goods, his industry could idle in his absence.  @L@LMonuments @PQ:  What can I do to speed up the monument building process? @PA: Build plenty of Work Camps, the needed Construction Guilds and Storage Yards that accept only construction materials near the work site. If your city can produce its own construction materials, make sure you have lots of quarries and Brickworks to keep the Storage Yards full. Also be sure that the city has access to plenty of wood so that the Carpenters' Guild can build ramps and scaffolding. Import as much as you can from trade partners if your city cannot produce the necessary raw materials. If monument construction slows for any reason, consult the construction foreman by right-clicking on the construction site. He can tell you what is holding up construction. Also, if you have multiple construction sites in the city, peasants and construction workers may not agree on where to start, and so might not be working on any of them.  @L@PQ:  I need a particular resource to build my monument, but my city can't produce it and no one will sell it to me. Did the mission creators goof? @PA:  In some missions, the trade route that you need becomes available only when you satisfy other cities' requests (especially requests for military aid). If you fail the first request, you'll usually have opportunities to recover, and thereby to open the vital trade route. If you continue to fail these requests, you could lose the mission. Every mission does have all necessary commodities...but you sometimes have to work for them, and success is not always guaranteed.  @L@LTrade @PQ: I've opened a trade route, but my city isn't importing or exporting anything. How do I start the flow of trade? @PA: Visit your Overseer of Commerce and tell him which products to buy or sell. Also, make sure you have a Storage Yard in the city, and a Dock if your trade partner is coming by water. @L@PQ: I'm trying to import some food. I have a trade route open and have told the Overseer of Commerce to import it, but still no food comes.  People are getting hungry - what can I do? @L@PA: Make sure your Storage Yards have been told to accept the food you are trying to import. Remember, Storage Yards are told by default not to accept any food. L@PQ: I've let my @24Overseer&of&Commerce decide the level of traded goods to keep in the Storage Yards. How can I be sure that he is making good decisions? @PA: When you tell your Overseer of Commerce to manage trade, he looks at the size of the city's population, which industries the city has, and which monuments are currently under construction. Analyzing these factors only, he develops an assessment of your city's needs. To see what he recommends, click on his commodity control buttons. When the button that allows you to set the level appears, the amount shown as default is the amount the Overseer of Commerce recommends the city keep in its Storage Yards.  @L@LHousing @PQ: The housing areas I designate keep disappearing. What's happening? @PA: All housing must be within two spaces of a road. If it isn't it will disappear. Furthermore, migrants must be able to reach housing blocks. Make sure that you have a clear path between the points where migrants enter and leave the city (the @57Kingdom&Road) and your housing."
        }
    }

    message_table_of_contents {
        id: 10
        
        size [30, 28]
        image { id: 47, pos [15, 15] }
        title { text: "Table of Contents" }
        subtitle { text: "Click on a topic to view help" }
        content {
            text: " @9Frequently&Asked&Questions @L@LHelp Topics @L@L@492Abu&Simbel @L@88Academy @L@488Alexandria's&Library @L@65Apothecary @L@81Architect's&Post @L@L@72Bandstand @L@91Barley&Farm @L@2Bazaar @L@2Bazaar&Special&Orders @L@54Bent&Pyramid @L@71Booth @L@96Brewery @L@55Brick&Pyramid @L@363Bricklayers'&Guild @L@364Brickworks @L@58Bridge @L@33Building&Buttons @L@374Burial&Provisions @L@L@490Caesareum @L@363Carpenters'&Guild @L@360Cattle&Ranch @L@98Chariot&Maker @L@90Chickpea&Farm @L@31Chief&Overseer @L@53City&Health @L@39City&Sentiment @L@92Clay&Pit @L@37Companies @L@87Company&Orders @L@369Construction&Foreman @L@363Construction&Guilds @L@19Control&Panel&Toggle @L@93Copper&Mine @L@76Courthouse @L@36Crime @L@35Culture&rating @L@L@17Date&Display @L@48Debt @L@85Defensive&Structures @L@63Dentist @L@56Desirability @L@83Dock @L@44Drinking&Water @L@L@50Education @L@43Employment @L@49Entertainment @L@L@45Farming (see also specific farms) @L@11File&Menu @L@355Firehouse @L@58Ferry @L@366Festival&Plaza @L@29Festivals @L@84Fishing&Wharf @L@91Flax&Farm @L@45Food @L@37Fort @L@L@79Garden @L@85Gatehouse @L@361Gemstone&Mine @L@93Gold&Mine @L@89Grain&Farm @L@3Granary @L@3Granary&Special&Orders @L@95Granite&Quarry @L@L@13Help&Menu @L@91Henna&Farm @L@56Housing @L@359Hunting&Lodge @L@L@46Industry @L@59Irrigation @L@L@99Jeweler @L@L@7Keyboard&Controls @L@35Kingdom&rating @L@57Kingdom&Road @L@L@473Lamp&Maker @L@90Lettuce&Farm @L@70Library @L@95Limestone&Quarry @L@L@494Major&Plagues @L@78Mansion @L@371Mastaba @L@368Mausoleum @L@34Messages @L@48Money @L@15Money&Display @L@370Monument&Construction @L@35Monument&rating @L@66Mortuary @L@L@372Obelisk @L@12Options&Menu @L@18Overlays @L@24Overseer&of&Commerce @L@28Overseer&of&Diversions @L@25Overseer&of&the&Granaries @L@27Overseer&of&Learning @L@21Overseer&of&the&Military @L@373Overseer&of&the&Monuments @L@26Overseer&of&Public&Health @L@29Overseer&of&the&Temples @L@30Overseer&of&the&Treasury @L@20Overseer&of&the&Workers @L@14Overseers&Menu @L@L@470Paint&Maker @L@77Palace @L@97Papyrus&Maker @L@73Pavilion @L@489Pharos&Lighthouse @L@64Physician @L@95Plain&stone&Quarry @L@79Plaza @L@86Police&Station @L@22Political&Overseer @L@90Pomegranate&Farm @L@16Population&Display @L@39Population&Growth @L@1Potter @L@35Prosperity&rating @L@L@95Quarry @L@L@35Ratings @L@23Ratings&Overseer @L@88Recruiter @L@94Reed&Gatherer @L@51Religion @L@358Roadblock @L@57Roads @L@478Royal&Burial&Tombs @L@L@95Sandstone&Quarry @L@68Scribal&School @L@41Scribes @L@74Senet&House @L@82Shipwright @L@67Shrine @L@362Sphinx @L@79Statue @L@375Stepped&Pyramid @L@363Stonemasons'&Guild @L@4Storage&Yard @L@4Storage&Yard&Special&Orders @L@69Sun&Temple @L@L@80Tax&Collectors'&office @L@67Temple @L@350Temple&Complex&to&Osiris @L@351Temple&Complex&to&Ra @L@352Temple&Complex&to&Ptah @L@353Temple&Complex&to&Seth @L@354Temple&Complex&to&Bast @L@477Tomb&Robber @L@85Tower @L@47Trade @L@75Training&Center @L@367Transport&Ship @L@357Transport&Wharf @L@75Training&Centers (entertainers) @L@48Tribute @L@38True&Pyramid @L@L@42Walkers @L@85Wall @L@52War @L@365Warship @L@356Warship&Wharf @L@61Water&Supply @L@98Weaponsmith @L@60Weaver @L@62Well @L@94Wood&Cutter @L@8Work&Camp @L@40Workers @L@32World&Map @L@L@479Zoo @L@LHistory @L@L@493Abu&Simbel @L@481Alexandria's&Library @L@159Apothecary @L@472Artisans @L@L@380Bast,&Isis&and&Hathor @L@199Bazaar @L@194Beer @L@386Bricklayers @L@390Bricks @L@395Burial&Provisions @L@L@482Caesareum @L@389Carpenters @L@186Cattle&Ranching&and&Fishing @L@166Children @L@190Clay @L@L@171Dance @L@182Defensive&Structures @L@158Dentistry @L@L@161Embalming @L@L@181Enemies @L@165Entertainment @L@L@150Farming @L@393Festivals @L@189Flax @L@187Fruits&and&Vegetables @L@L@176Gardens&and&Public&Art @L@191Gold&and&Gold&Mining @L@174Government&and&Bureaucracy @L@185Grain&and&Barley @L@5Granary @L@L@469Henna @L@152Housing @L@383Hunting @L@L@388Immigration @L@151Industry @L@154Irrigation @L@L@382Jewelry @L@169Juggling @L@L@155Labor @L@474Lamps @L@183Law @L@164Library&and&Literature @L@398Linen&and&Weaving @L@197Luxury&Goods @L@L@495Major&Plagues @L@381Malaria @L@394Mastaba @L@160Medicine @L@184Military @L@170Music @L@L@157Nile @L@L@397Obelisk @L@476Oil @L@376Osiris,&Sebek&and&Min @L@396Other&Monuments @L@L@195Papyrus&Making @L@175Pharaoh's&Home @L@487Pharos&Lighthouse @L@167Population @L@198Pottery @L@384Priests @L@378Ptah,&Amon&and&Thoth @L@176Public&Art @L@392Pyramids @L@L@193Quarries @L@L@377Ra,&Ma'at&and&Horus @L@188Reeds @L@399Religion @L@153Roads @L@L@163School&and&Education @L@387Scribes @L@379Seth,&Anubis&and&Sekhmet @L@172Senet @L@179Ships&and&Ship&Making @L@162Shrine&and&Temple @L@168Society @L@391Sphinx @L@385Stonemasons @L@6Storage&Yard @L@L@173Taxation&and&Money @L@177Trade @L@L@475Valley&of&the&Kings @L@L@196Weapons @L@156Well&and&Water&Supply @L@192Wood&and&its&Uses @L@L@480Zoo"
        }
    }
    
    message_file_menu {
        id: 11
        
        size [30, 28]
        title { text: "File Menu" }
        subtitle { text: "Game Controls" }
        content {
            text: "From the File Menu, you can start a new game, replay the current mission, load a previously saved game, save your current game, delete a previously saved game, and exit Pharaoh."
        }
    }
    
    message_optons_menu {
        id: 12
        
        size [30, 28]
        title { text: "Options Menu" }
        subtitle { text: "Game Controls" }
        content {
            text: "Use the Options menu to change the way Pharaoh looks and sounds. Use the Display option to adjust your view and the Sound option to adjust the volume of the sounds, speech and music. The Speed setting changes the rate at which time passes in Pharaoh. Choose which version of the city names you would like to use (either Classical or Egyptian) by selecting the Cities option.  You probably have a passing familiarity with the classical names, but the Egyptian option lends a bit more authenticity to Pharaoh. @PTo control the way you receive messages while playing, adjust the Popup Messages settings. Most of the messages you receive appear in a popup screen. When the screen pops up, the game stops until you close to screen. The Popup Messages settings allow you to turn this feature off for some of the messages you receive. From the category list provided, simply select which types of messages you do not want to receive as a popup message by clicking on the category name. The category name will appear in yellow, and messages in that category will be displayed in a banner across the top of the screen. They will also appear in your @34message&list. You will not have to stop governing the city to deal with the message. If you select 'Compliance Now Possible' from the list, requested goods will automatically be sent from the city's Storage Yards when the shipment is ready. See the entry on the @22Political&Overseer for more information on requests.  @PYou can turn the game's automatic save function on or off from this menu.  Autosave saves your game every six months, which gives you a reliable fallback if you forget to save manually or if you have computer problems.  It always overwrites the same filename, so there's no danger of filling up your hard drive with autosaves.  You might turn off this feature to eliminate the brief pauses while the game saves itself.   @PTo change the difficulty level at any time during the game, use the Difficulty option.  Note, however, that your mission score is tied to the difficulty level that you choose. If you change the difficulty part way through a mission, your score will be computed using the easiest level that you play. @PFinally, the Monument Speedup option allows you to use the gods' help in building some @370monuments. Turn the option on, and a god may choose to bless you by helping you build your monument. The gods enjoy working on certain monuments only, specifically the pyramids and mastabas."
        }
    }

    message_help_menu {
        id: 13
        
        size [30, 28]
        title { text: "Help menu" }
        subtitle { text: "Game Controls" }
        content {
            text: "The Help menu lists the topics for all the things you need to know to play Pharaoh. You can also select many historical entries from the bottom part of the Table of Contents. @P'Mouse help' means the little word balloons that appear when you put your cursor over something.  'Full' displays mouse help for almost everything in the game.  'Some' turns mouse help off, with a few exceptions like @18Overlay&views and your city's Palace reports.  'None' disables mouse help completely. @P'Warnings' are the short banner messages that appear at the top of your screen.  You might wish to turn them off after you get the hang of playing Pharaoh."
        }
    }
    
    message_overseers {
        id: 14,
        
        size [30, 28]
        title { text: "Overseers" }
        subtitle {
            text: "Game Controls"
        }
        content {
            text: "Use the Overseer menu or click the Overseers button to visit a specific Overseer.  The menu is useful when you've chosen to hide the Control Panel.  Overseers present crucial information about the condition of your city at any given time."
        }
    }
    
    message_game_control_money_display_window {
        id: 15,
        
        size [30, 28]
        title {
            text: "Money Display Window",
        }
        subtitle {
            text: "Game Controls",
        }
        content {
            text: "This shows the debens in the city's treasury. A number shown in yellow indicates debt. For more on generating income, see @48money."
        }
    }
    
    message_game_control_population_display {
        id: 16,
        
        size [30, 28]
        title {
            text: "Population Display",
        }
        subtitle {
            text: "Game Controls",
        }
        content {
            text: "This window shows how many people live in the city. Remember that not everyone living in your city is a worker. Follow this link to read about how @39population works in the game."
        }
    }
   
    message_game_control_date_display {
        id: 17,
        
        size [30, 28]
        title {
            text: "Date Display Window",
        }
        subtitle {
            text: "Game Controls",
        }
        content {
            text: "This window shows the current month and year.  For convenience, the modern calendar is used.  If time is passing too quickly - or too slowly - for you, use the Speed Settings @12Options&Menu item."
        }
    }
    
    message_overlay_selector {
        id: 18,
        
        size [30, 28]
        title {
            text: "Overlay Selector",
        }
        subtitle {
            text: "Game Controls",
        }
        content {
            text: "The Overlay Selector lets you look at the city through different filters. The overlays are key to city planning and managing the city's services. @PWhen you choose an overlay, you will see only the buildings and walkers that relate directly to the report you've chosen. Other buildings are usually replaced by columns.  In most cases, the columns indicate access to a particular service or city function.  The higher the column, the better the building's access to the service. @PThe exceptions to the rule are the Risks Overlays, the Problems Overlay, the Desirability Overlay and the Hide Cliffs Overlay.  With the Risks Overlays, housing and other buildings are still replaced by columns, but the taller and redder the column the greater the risk.  @PThe Problems Overlay shows the buildings that are not operating properly or that are about to develop a serious problem.  Icons indicating the problem appear on top of the building.  This overlay also shows cart pushers who have stalled because they have no place to bring their goods or food. @PWith the Desirability Overlay selected, the city's land is replaced by different colored blocks.  Gold blocks indicate the areas that people find the most desirable.  The browner the block, the less desirable the area. For more on desirability, click @56here. @PIf cliffs are blocking your view, use the Hide Cliffs Overlay to temporarily flatten them. If you have any Royal Burial Tombs built into the cliffs, you'll be able to see into them when you've selected the Hide Cliffs Overlay.  @PFinally, the Water Overlay is a little different from the other overlays as well. Access to water carriers is shown with blue columns that grow taller with better access.  This overlay also shows which land can support water-related structures and which land has access to drinking water from a well.  Dark blue squares mark the housing that has well water, and light blue squares show which land has the necessary groundwater to support a @62Well, @61Water&Supply or other building that needs groundwater access. @PThe best way to familiarize yourself with the different overlays is to experiment with them. Once you understand the information they provide, you will be able to plan your city more efficiently."
        }
    }

    message_control_panel_toggle {
        id: 19,
        
        size [30, 28]
        title {
            text: "Control Panel Toggle",
        }
        subtitle {
            text: "Game Controls",
        }
        content {
            text: "This button simply allows you to hide or show the Control Panel. Hiding the panel enables you to see more of the city, but can make some game controls less convenient. Your personal preference is the only consideration in choosing whether or not to hide the panel."
        }
    }

    message_overseer_workers {
        id: 20,
        
        size [30, 28]
        title {
            text: "Overseer of the Workers",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of the Workers keeps track of everything involving your @43labor&force: number of job openings by employment sector, number of unemployed workers and the current annual wage scale per ten workers. He'll help you manage issues related to your workers. @PWork with the Overseer of Workers to set wages in your city. On the overseer's panel, you'll notice the wage that you pay and the wage that prevails throughout Egypt. Use the scroll buttons to adjust the salary you pay your workers. Paying your people more than other cities in Egypt can contribute to an increased @39City&Sentiment and encourage @39immigration. Paying less will save the city money, but will sour your citizens' moods and could result in emigration.   @PYou can also turn to the Overseer of the Workers to set labor priorities. If you don't set a specific priority, the Overseer assigns workers as he sees fit. He usually tries to fill the food production jobs first, followed by industry. If you want to set a new top priority, for example military, click on the military line item. A panel with numbers pops up. To set military as the top priority, click the number one. A padlock symbol appears in front of military, showing that you've locked down its priority. You can assign a priority to every job sector.  @PA word of warning: when you set a priority, the Overseer of the Workers shifts all workers to fill that particular job sector first. This can leave some sectors without any employees. Your city will not long survive if any of its job sectors goes completely unfilled. In times of labor shortage, you might have to juggle priorities frequently to ensure that no sector is neglected for too long. @L@LFor a brief history of the ancient Egyptian labor force, click @155here."
        }
    }

    message_overseer_military {
        id: 21,
        
        size [30, 28]
        title {
            text: "Overseer of the Military",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of the Military keeps tabs on all of the city's @37companies, @365warships and @367transport&ships. @PYour Overseer of the Military issues both an army report and a navy report.  In the army report, your Overseer briefly updates you on the number and condition of each of the city's companies. He keeps tabs on their morale and experience level and can also earmark a company for Kingdom service, and, if only one other city is requesting aid, send the company. Visit any one of the companies by clicking the 'Go to Company' button.  You can also order a company back to its Fort from the army status report. @PClick the button in the lower right corner to view the navy status report, which tells you everything you need to know about the navy's warships and transport ships.  Your Overseer reports each warship crew's fatigue level and the hull's strength.  He can also send warships to aid Pharaoh or another city, if needed.  Click 'Go to Warship' to visit a specific crew, and click 'Return to Wharf' to send a warship back to moor. @PYour Overseer of the Military also updates you on general military activity in and around the city. He'll tell you if there are enemies approaching or if anyone requires the services of your troops or warships. @PFor more on war in Pharaoh, click @52here. @L@LThe ancient Egyptians raised mighty armies and navies. Click @184here to find out more about ancient warfare."
        }
    }

    message_overseer_political {
        id: 22,
        
        size [30, 28]
        title {
            text: "Political Overseer",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Political Overseer manages your relations with the rest of Egypt.   @PThe Political Overseer keeps track of all requests for supplies, whether from other cities or from Pharaoh. He knows how much of the requested good the city has available in its @4Storage&Yards and will notify you when you are able to comply with the request. You can then tell your Political Overseer to send the goods. It's generally a good idea to comply with requests from Pharaoh or other cities as quickly as possible. Ignoring a request entirely can reduce @47trade, or even prompt an attack on your city. Sending goods late is better than not sending them at all. @PThe Political Overseer also helps you manage your family savings. He knows how much you have saved and your current salary level. Family savings carry over from mission to mission unless Egypt's centralized government breaks down (between each Period). Your Political Overseer will change your salary if you so command. Simply click on the button that lists your current salary, and, when the list of titles with their associated salaries appears, choose a new salary level from this screen. Keep in mind that your fellow Egyptians frown on those who pay themselves more than their rank merits. @PIf you want to spend some of your family's savings, the Political Overseer will manage the transaction. You can choose to send a gift for Egypt (other political leaders or the people of other cities), or you can give to your city's treasury.  @PSending a gift for Egypt can boost your @35Kingdom&Rating.  If your family has enough saved, you can choose among three gifts to send. Don't be overly generous, though. If you send gifts too frequently, the recipients begin to expect them, and might grow angry if they stop arriving. They also tend to expect each gift to be more precious than the previous one. When you decide to send a gift, the Political Overseer will make sure the gift arrives intact. @PYou can also donate your family savings to the city's treasury.  This can be a good idea, especially if your family savings can prevent the city from going into debt. Debt can be a very expensive proposition. The Kingdom will loan your city money, but loans do come at a cost. For more on your city's money, click @48here. @PFinally, your Political Overseer knows your Kingdom rating and Egypt's general attitude towards you. A better resource for information on ratings is your @23Ratings&Overseer."
        }
    }
    
    message_overseer_ratings {
        id: 23,
        
        size [30, 28]
        title {
            text: "Ratings Overseer",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Ratings Overseer displays the city's current Culture, Prosperity, Monument and Kingdom ratings along with your population goal. When you click on a rating, the Ratings Overseer tells you the best way to improve that rating, or what holds the rating back. You can see how far along your city is in reaching its ratings goals by looking at the columns above each rating. When you achieve the goal set for the city at the beginning of your assignment, the column is capped. Even though you may have achieved your monument rating, the column is not capped (and the goal has not been met) until all necessary burial provisions have been dispatched by the Overseer of Monuments. @PIf the city has a @77Palace, you can quickly check the city's ratings by holding the mouse over the Palace. A small window appears that lists the ratings along with the city's unemployment rate. @PFor more detailed information on ratings and their role in the game, click @35here."
        }
    }

    message_overseer_commerce {
        id: 24,
        
        size [30, 28]
        title {
            text: "Overseer of Commerce",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of Commerce monitors the city's @46industries and @4Storage&Yards and keeps track of supply, demand and prices for goods throughout the world.  He knows how much of each commodity is stored in the city and tells you whether an item can be imported or exported.   @PYour Overseer of Commerce also updates you on the current status of each industry.  Visit him to turn city industries on or off, or to stockpile a particular good in the city's Storage Yards.  When a good is being stockpiled, it accumulates quickly in the Storage Yards because no one can use it.  It cannot be traded, and Bazaar buyers cannot procure the good for their customers.  If a raw material is being stockpiled, no shipments of the commodity will be delivered to its corresponding manufacturer.  You might want to stockpile some item against an anticipated future request for it, or you might stockpile a raw material before you actually build the industries that need it.   @PTo shut down an industry or stockpile a commodity, click on an item in the Overseer of Commerce's list.  Buttons with your different options appear in the panel that pops up. @PYour Overseer of Commerce also helps you establish the flow of trade.  He identifies which commodities can be imported or exported, based on the trade routes that you have opened.  Once you decide to trade an item, visit him and specify which items to trade by clicking on them.  You can tell him how much should be kept in the city's Storage Yards, or you can rely on his judgement and allow him to import and export food and goods as he sees fit.  The Overseer has been doing his job for a long time, and makes intelligent decisions about how much of each commodity your city should have on hand.  @PWhen importing, your Overseer continues to buy a good as long as the city has less than your chosen level (or, if using his own judgement, tries to buy just enough to maintain a small surplus in city storage).  When exporting, your Overseer sells goods any time the city has more than your chosen level.  Left to his own judgement, he evaluates whether your city needs each commodity for its own purposes, and refuses to sell more than the amount that he thinks you need to keep things running smoothly.  The Overseer is keenly attuned to the population's changing size, and he revises his decisions as the city's numbers fluctuate. @PThe entries on @46industry, @45food, and @47trade will help you understand the nuances of successful trade."
        }
    }
    
    message_overseer_granaries {
        id: 25,
        
        size [30, 28]
        title {
            text: "Overseer of the Granaries",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Food and population go hand in hand. The Overseer of the Granaries keeps track of the city's population and the food they consume. @PThe Overseer of the Granaries presents information on your city's population through three different graphs. By default, the first graph you see is the Population History graph. This graph shows how your population has grown or shrunk over time. If your city is doing well, this report will show more or less continuous growth.  @PTo the right of the Population History graph are two smaller graphs, the Census graph and the Society graph. Click one of these graphs to enlarge it and place it in the center of the screen.   @PThe Census graph shows you the demographic breakdown of your population by age - useful for predicting the growth or contraction of the @43work&force. Children and the elderly don't work, but do continue to eat food, drink beer and break pottery!  @PThe Society graph shows you the breakdown of your citizens by income, as measured by the quality of their housing. Very wealthy residents @41(scribes) do not engage in manual labor, either, so as your city grows richer, its workforce tends to diminish. Although they don't contribute to the labor pool, scribes do pay a lot of tax money into your Palace vaults. @PBelow the graphs are several lines of very useful information. The first line tells you how many people your current level of food production can support and anticipated population trends based on current levels of immigration and emigration. This Overseer also knows how many people the city's vacant housing can hold, how much food the Granaries in the city have stored, and how many immigrants arrived during the previous month. @PConsulting the entries on @39Population and @45Food may be helpful to understanding the Overseer of the Granaries' importance."
        }
    }
    
    message_overseer_public_health {
        id: 26,
        
        size [30, 28]
        title {
            text: "Overseer of Public Health",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of Public Health reports on the city's overall health. He tracks the number of @64Physician's&offices, @63Dentist's&offices, @65Apothecaries and @66Mortuaries working in the city. For more specific information on health coverage in particular sections of your city, use the @18health&overlay. @PYour Overseer of Public Health knows if a particular health risk like malaria or disease threatens the city. He also keeps track of your populace's general attitude towards their health services.  @PThe @53Health entry will help you understand the effects of health throughout your city."
        }
    }
    
    message_overseer_learning {
        id: 27,
        
        size [30, 28]
        title {
            text: "Overseer of Learning",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of Learning apprises you of the status of education in the city.  He reports the number of active @68Scribal&Schools and @70Libraries and how many people can benefit from existing education structures.  He assesses the adequacy of access to education and also reports any demands citizens are making for new education structures.  @PTo look at coverage in specific areas of your city, use the @18education&overlay. Also, see the entry on @50education for more information. @L@LTo learn more about education in ancient Egypt, click @163here."
        }
    }

    message_overseer_diversions {
        id: 28,
        
        size [30, 28]
        title { text: "Overseer of Diversions" }
        subtitle { text: "Game Control"  }
        content {
            text: "Your Overseer of Diversions knows how many juggler's stages, musicians' stages and dancers' stages are working in the city.  The number of stages matters much more than how many @71Booths, @72Bandstands and @73Pavilions exist, so he does not bother enumerating those.  He also reports the number of @74Senet&Houses and @479Zoos that are entertaining the public.  He estimates how many people can benefit from your city's stages, Zoos and Senet Houses and gauges citizens' satisfaction with their entertainment options.  @PYou may want to consult the entry on @49entertainment to learn more about its role in your city. @L@LTo learn more about entertainment in ancient Egypt, click @165here."
        }
    }

    message_overseer_temples {
        id: 29,
        
        size [30, 28]
        title {
            text: "Overseer of the Temples",
        }
        subtitle {
            text: "Game Control",
        }
        content {
            text: "Your Overseer of the Temples knows which gods are worshiped in the city and whether or not the city has a patron god.  Perhaps most important, he also keeps track of each god's attitude.  He reports how many Shrines, Temples and Temple Complexes are working in the city and if people are demanding more access to religious facilities.  He can also help plan a festival.  @PWhen you want to hold a festival in your city, click on the 'Hold New Festival' button. Choose which god to honor and the size of the festival. Because of the expense and time involved in successfully planning a festival, a city can only have two festivals in any 12-month period. Keep in mind that you must also have a @366Festival&Square in the city before you can hold a festival. To throw a Grand festival, the city must also have enough beer for everyone. @PThe Overseer of the Temples will also tell you the citizens' specific concerns regarding religion in the city. @PRead about @51religion to learn more about the value of appeasing the gods. @L@LReligion was the basis for ancient Egyptian life. Click @399here for more."
        }
    }

    message_overseer_treasury {
        id: 30,
        
        size [30, 28]
        title { text: "Overseer of the Treasury" }
        subtitle { text: "Game Control" }
        content {
            text: "Your Overseer of the Treasury tracks every single deben that comes into or leaves the city's coffers. Examining his tally sheet helps you assess where you can cut costs or increase income. @PSummary tax information is located at the top of the Overseer of the Treasury screen. Use the scroll buttons by the tax rate to adjust it.  The default setting of 9 percent is considered reasonable by your citizens. Raising the rate much higher than 9 percent could anger your citizens and deter immigration, or even prompt people to leave. The longer you hold taxes at high levels, the angrier people grow. For more on City Sentiment, click @39here. @PThe summary also shows how much tax has been collected, how many of your citizens are registered for the tax and how much money was not collected due to an insufficient number of tax collectors. To assess which areas of your city are skipping out on their tax payments, use the @18tax&overlay.  Also, be aware that citizens become very agitated if they have to pay tax while other neighborhoods in the city do not.   @PFollowing the summary information is a tally sheet. The line items at the top of the sheet detail the city's income from taxes, gifts and exporting commodities.   @PBelow the meager list of sources of income is a lengthier list of the city's expenditures. Generally, wages and construction costs will be the largest line items, although imports can become quite costly, too. @PThe left side of the list shows the previous year's performance for purpose of comparison. You can see if a particular expenditure is skyrocketing out of control compared to the previous year. @PThe entry on @48money provides more advice on budgets. The entry on @80Tax&Collectors is also helpful. @L@LClick @173here for more on money in ancient Egypt."
        }
    }

    message_chief_overseer {
        id: 31,
        
        size [30, 28]
        title { text: "Chief Overseer" }
        subtitle { text: "Game Control" }
        content {
            text: "The Chief Overseer consults with all your other Overseers to provide a thumbnail sketch of the city's status. He's a good person to visit when you're not sure what your city needs most. Urgent items requiring immediate attention appear in yellow. Serious problems appear in white. Click on any problem for advice on how it might be addressed, and links to other advisors who might be able to help you further. @PYour Chief Overseer also provides you with the latest Nilometer reading. The Nilometer predicts the next season's flood. @PYour other overseers report to the Chief Overseer, and you should carefully consider what he has to say. He has a better idea of your city's overall condition than does anyone else, save yourself.  Heeding his warnings early could save your city from disaster."
        }
    }

    message_world_map {
        id: 32,
        
        size [30, 28]
        title { text: "The World Map" }
        subtitle { text: "Game Controls" }
        content {
            text: "The World Map shows you other important cities in the world. Perhaps its most important function is in the identification of @47trade partners. @PCities flying a flag will trade with you. Click on a flag-flying city to see which items it wants to trade, as well as the cost of opening a trade route.  Each commodity that the city buys or sells has from one to three blue dots indicating that city's level of supply or demand - one dot means they don't deal in that good very much at all, while three dots signal a strong desire to trade that item.   @PClick the 'Open Trade Route' button to initiate relations.  Your city's treasury immediately pays to open the route, and trading can begin immediately.   @PIf you have sent any companies or warships to serve the Kingdom, you can trace their journeys on the World Map.  You can also chart the progress of any enemy armies or navies as they move towards your city. @PRead the entries on @47trade, @52war and the @24Overseer&of&Commerce for more on the use of the World Map."
        }
    }

    message_building_buttons {
        id: 33,
        
        size [30, 28]
        title { text: "Building Buttons" }
        subtitle { text: "Game Controls" }
        content {
            text: "These buttons let you actually place structures on the landscape. The building's price is shown on its button. When you select a structure to build, a ghostly green image of it attaches to your cursor. When you sweep the cursor over buildable land, that image is green; on unsuitable terrain, the green image becomes a red diamond. @PAccess help for individual buildings by clicking on existing structures with your right mouse button, or choose them from the 'Buildings' section of the @10Table&of&Contents."
        }
    }
    
    message_game_control_messages {
        id: 34,
        
        size [30, 28]
        title { text: "Messages" }
        subtitle { text: "Game Controls" }
        content {
            text: "When a notable event occurs in the city or elsewhere in the Kingdom, you receive a message describing the event.  Some of these messages are urgent and require quick response on your part.  They could be requests from Pharaoh or other cities, or could be directing your attention to a particular trouble spot in your city. @PWhen a new message arrives, the 'Message' button on the Control Panel lights up and a chime sounds.  Click on the button to read the message.  If the matter is extremely urgent, the message is delivered to you directly and appears on the screen automatically.  If the message is alerting you to some trouble in your city, you can click on the alarm button within the message to proceed directly to the trouble spot.   @POther messages contain instructions that help you manage the city more successfully.  These messages are useful guides that teach important game concepts and set up short-term goals.  Meeting the short-term goals outlined in these special messages enables you to win a mission and move on to the next step.  These messages are marked with a blue scroll in the message list. @PYou can erase individual messages by right-clicking on their titles in your message list.  A button at the bottom of the panel lets you delete all previously-opened messages at once, although it won't delete unread or blue-scroll (tutorial) messages.  Once you delete a message from the list, it is gone forever. You can, of course, choose to keep the message for future reference. @PExpert players might want to disable certain popup messages from the @12Options&menu.  When you enable this option, messages appear across the top of the screen and are also added to your Message box."
        }
    }

    message_ratings {
        id: 35,
        
        size [30, 28]
        title { text: "Ratings" }
        subtitle { text: "Game Concept" }
        content {
            text: "Ratings are a mark of how good the city is or how well you are doing as a leader. Four different ratings are used to measure the city: Culture, Prosperity, Kingdom and Monument. @L@LCulture @LThe Culture Rating assesses how much access your citizens have to @49entertainment, @50education, @53health and @51religion. The Culture rating measures not only the number of facilities you have, but also the variety of options. To achieve a high Culture rating, be sure to provide citizens with plenty of options. This means easy access to multiple forms of entertainment, health services (except Apothecaries - they have no effect on the Culture rating) and religion.   @PFor wealthier citizens, access to both Libraries and Scribal Schools is a must to keep the Culture rating on the rise, but access is not the entire story.  People learn better in quiet, uncrowded facilities, and your Culture rating reflects the quality of education by measuring how many people use each school and Library.  It's possible to have enough educational buildings to provide access for every house in the city, and yet still suffer from overcrowding. @PTo earn the highest Culture rating, see if you can build a @479Zoo. You'll need to build a Zoo if you need to attain a Culture rating higher than 75. Click on the Entertainment button to see if a Zoo is among your entertainment options.  @L@LProsperity @LThe Prosperity rating measures a city's wealth and its financial security.  The rating goes far beyond an assessment of the city's treasury: it also looks at the wealth of its citizens, taking into account the value of their property and the unemployment level.   @PIf the city earns a profit every year, its Prosperity rating should continue to rise if nothing else in the city is holding the rating back. High unemployment, low-level housing and low wages will stunt the rating's growth. Failure to pay tribute to the Kingdom will also decrease this rating. If a Temple Complex or Senet House is functioning in the city, its Prosperity rating rises, because people feel like the city is well-off if it has such glorious structures in it. Finishing a monument also gives the Prosperity rating a boost.  When the city ends the year in debt or loses money, the Prosperity rating suffers. However, if the city lost money because of construction costs, its Prosperity rating isn't affected, because expenditures on construction improve the city.    @L@LKingdom @LThe Kingdom rating represents your reputation, especially with the rest of Egypt. Quick response to an ally's request for help can increase the rating.  Failure to comply with requests, or missing an @48annual&tribute payment because of city debt, will hurt the Kingdom rating. If the Kingdom rating falls too low, your shoddy reputation might provoke an attack by Pharaoh or by a neighboring city. @PYou'll usually begin each mission with a rating of 50, which indicates neutrality.  People outside your city have barely even heard of you, and those who do know your name and history have few opinions about you.  Over time, if you do nothing to improve it, your Kingdom rating gradually falls as word goes out that you are of little importance beyond your city's borders.  The rating falls more dramatically if you lose or ignore distant battles, fail to comply with requests for goods or other demands from the rest of the Kingdom, and remain in @48debt for any length of time.  Drawing a salary beyond the standard for your rank doesn't help matters, either. @PYour Kingdom rating will also fall if @477tomb&robbers plunder @374burial&provisions from a tomb on your watch. Others in Egypt will think that you don't have proper respect for the dead.  @PTo raise your Kingdom rating, fulfill requests from Pharaoh or other Egyptian cities promptly, especially when they ask for military aid.  Victory in battle can do wonders for your reputation.  Sometimes even losing a battle might help a little bit, since you at least tried to rescue your countrymen in their hour of need. @PFor a quick pick-me-up in your reputation, use your family savings to buy a gift for Egypt.  Your Political Overseer sends the gift of your choice to Pharaoh, or to other Egyptian leaders, or to the people of Egypt - wherever he feels that it will do the most good.  Your Kingdom rating will rise by a few points immediately.  Resist the temptation to spend all of your savings on gifts, though.  They lose their effectiveness if they become too frequent, and the recipients will come to expect them.  Eventually, your rating might even decline if you stop sending gifts or send cheaper gifts than the recipients have grown to expect.  Exceeding one gift per year is of questionable effectiveness, and could even be counterproductive. @PApprehending a tomb robber is also appreciated by your fellow Egyptians, and your Kingdom rating will increase slightly for every tomb robber your constables catch. @PYour Kingdom rating's natural tendency to decline lessens a bit if you draw a personal salary below that defined for your rank.  Drawing no salary at all is even better for your reputation as a selfless public servant - although it isn't the best strategy for building up your family's wealth!     @L@LMonument @LThe Monument rating comes from both the size and scope of any monuments in the city, as well as how far along they are in construction.  If you complete all the monuments required and remember to dispatch any necessary burial provisions to provide for the deceased's afterlife, you will have no problem meeting the Monument Rating goal. @L@LA visit to your @23Ratings&Overseer will show you your current standing. When you click on a rating, your Ratings Overseer will advise you on how to improve it."
        }
    }

    message_city_crime {
        id: 36
        
        size [30, 28]
        title { text: "Crime" }
        subtitle { text: "Game Concept" }
        content {
            text: "Crime is bred from poor @39City&Sentiment. People could be unhappy for any of a number of reasons - not enough food, low wages, high taxes, high unemployment - but their mood must be particularly bad for crime to break out. @PThe best way to prevent crime, then, is to keep people happy.  Providing plenty of goods and services goes a long way to accomplishing that task. You can also prevent crime by placing @76Courthouses and @86Police&Stations throughout the city. The presence of both these structures discourages potential criminals. @PIn spite of your best efforts, some portions of the city may produce criminals, especially residents of heavily industrialized areas. If crime does break out, a constable from a Police Station will subdue any criminal he apprehends. @PIf the criminal escapes a constable's notice, he'll head straight for one of the city's money-holding buildings. He will make little distinction between the city's treasury and your family's savings. He'll steal from either source. Once he has stolen gold, he'll lay low and won't steal again. . .for now. @PCrime can also produce @477tomb&robbers, but only if your city is the final resting place for one of Egypt's greatest and hosts a tomb (Pyramid, Mastaba, Mausoleum or Royal Burial Tomb). Tomb robbers are especially adept at breaking into and plundering the treasures of Royal Burial Tombs. @PSometimes, greed can corrupt even the happiest of citizens. These greedy citizens get together with their friends and speculate about the lavish burial provisions interred with the noble dead. When this lust for riches gets the best of them, a crime wave breaks out, and these citizens become tomb robbers! Since you cannot look deep into the hearts of your citizens, you have no way of knowing when a crime wave will occur. However, constables will eagerly strike down anyone who tries to defile a tomb by pilfering its burial provisions."
        }
    }

    message_fort_and_company {
        id: 37,
        
        size [30, 28]
        title {
            text: "Fort and Company",
        }
        content {
            text: "Your city's army is called a 'battalion'.  Each soldier in the battalion is assigned to a company, and each company has its own Fort.  A city may have no more than six Forts.  The types of companies and Forts are: @L@LInfantry @LInfantrymen are the mainstay of most armies.  Specialists in close combat, they fight on the front line of the battle.  They move at an average rate of speed.  They leave the @88Recruiter armed with spears as weapons.  You cannot build an Infantry Fort unless your city has a Weaponsmith, or can import weapons. @L@LArchers @LWith arrows, archers can attack an enemy from longer range than infantry, but they are terrible at close-range battle and won't last long if an enemy engages them directly.  They march a little more slowly than infantry.  Archers craft their own bows and arrows, so you can build Archer Forts even if your city lacks a Weaponsmith. @L@LCharioteers @LThere is nothing more frightening to soldiers than seeing a line of chariots barreling towards them.  Chariots are key to breaking the protective formations of your enemies, and once their lines are broken, it will be easier to defeat them.  Each charioteer receives a chariot upon leaving the Recruiter, assuming that your city has a Chariot Maker and a supply of wood. @L@LSoldiers of all types prefer to stay in their Forts when they are not fighting and remain there unless you order them into the field. Prolonged assignment in the field lowers a company's morale.  @PForts do not need road access or laborers.  They have an extremely negative effect on desirability, so it's best to place Forts on the outskirts of the city.  When planning the location of your Forts, remember that the embankment between a flood plain and dry land is impassible except where a road connects the two terrains. @PConsult the entry on @87Company&Orders to find out what soldiers can do. the entry on @52war may also be helpful. @L@LFor more on ancient Egyptian warfare, click @184here."
        }
    }
    
    message_true_pyramid {
        id: 38,
        
        size [30, 28]
        title {
            text: "True Pyramid",
        }
        content {
            text: "The True Pyramid has a @95plain&stone core with a @95limestone casing that is smoothed and polished.  Stonemasons from the @363Stonemasons'&Guild lay the stone and polish the surface, while carpenters from the @363Carpenters'&Guild prepare the ramps necessary for construction as the Pyramid rises higher and higher.  When a @4Storage&Yard accumulates four blocks of stone, peasants drag a sledge loaded with the stone to the monument site to the waiting stonemasons. @PThe True Pyramid sizes are small, medium, large, Pyramid Complex and Grand Pyramid Complex. @PConsult the entries on @370Monument&Construction, the @373Overseer&of&the&Monuments and the @369Construction&Foreman for additional information. @L@LThe pyramids are ancient Egypt's calling card and the landmarks for which the country is best known.  Click @392here to find out more about the pyramids and their construction."
        }
    }

    message_population_groth_and_sentiment {
        id: 39,
        
        size [30, 28]
        title {
            text: "Population Growth and City Sentiment",
            pos [15, 5]
        }
        subtitle {
            text: "Game Concept",
        }
        content {
            text: "When your city is new, immigrants eagerly approach the city with their meager belongings, hopeful for new opportunities. As the city becomes more established, it needs to provide more amenities to attract new immigrants and keep the inhabitants it has. The best way to keep residents from emigrating is to keep them in a good mood, resulting in high City Sentiment. @PThe key to keeping citizens in good humor is providing them with plenty of the basics: clean water, good food and jobs. Once these basics are covered, provide the services that enrich their lives.  Paying competitive wages and charging a reasonable tax rate also helps.  The city should continue to grow as long as you continue to provide plenty for citizens basic needs. @PFailure to meet citizens' needs can cause a wave of emigration.  Emigration can sometimes be the start of a vicious circle: emigrants leave because of lack of services, but in leaving they cause a worker shortage. This worker shortage causes even more services to suffer. You should avoid at all costs making conditions so bad in the city that people leave en masse. @PYour population can also grow and shrink as a result of births and deaths. Check in with your @25Overseer&of&the&Granaries often to monitor the average age of the city's population. Once workers reach a certain age, they retire, and a worker shortage could happen quite suddenly if a large portion of your population reaches retirement age. If you notice your populace aging, take steps to attract new immigrants, who are usually younger. @PIn addition to encouraging emigration, poor City Sentiment also encourages @36crime. @PIf you need a quick fix to poor City Sentiment, throw a lavish or grand @51festival. The festival distracts people from their troubles, and the merriment induces a pleasant feeling in citizens. Festivals are just a temporary solution, though. If you don't fix the underlying problems that created the poor City Sentiment in the first place, citizens' mood will again worsen. @L@LFor more on population growth in ancient Egypt, click @167here. Learn more about the various immigrants to ancient Egypt by clicking @388here."
        }
    }
    
    message_game_concept_workers {
        id: 40,
        
        size [30, 28]
        title { text: "Workers" }
        subtitle { text: "Game Concept" }
        content {
            text: "Workers are the city's life blood. Their efforts yield all the goods and services that each citizen enjoys.  Providing for these humble folk should be one of your chief concerns. Without them, the city cannot survive. @PWhen you construct most new buildings, they send an agent out to find workers. If they find occupied housing within their recruitment range, and if the city has enough unemployed workers overall, then the building has access to labor. @PWhile workers don't complain much about their lot in life (okay, they complain plenty), they do have goals and aspirations. They dream of one day becoming part of the @41scribe class. @L@LLearn what it was like to work in ancient Egypt by clicking @155here."
        }
    }

    message_game_concept_scribes {
        id: 41,
        
        size [30, 28]
        title { text: "Scribes" }
        subtitle { text: "Game Concept" }
        content {
            text: "@40Workers who toil hard and scrimp and save their debens eventually become scribes.   @PScribes are extremely wealthy and do not perform manual labor. They live in large dwellings, surrounded by luxury, and devote their days to the pursuit of leisure and education. They demand a higher level of services than do your workers, but also pay more in tax.  @PBecause their taxes are so high, having a good number of scribes in the city can be a boon to its treasury. If you have too many scribes, though, the city may no longer function efficiently due to lack of workers. @PIf you fail to maintain a high level of services, scribes eventually return to the working class. This is the worst thing a scribe can imagine. While the city will gain workers, it will lose tax income, and its Prosperity rating will decrease as well. @L@L@387Scribes were one of the more well-to-do classes in ancient Egyptian @168society. Follow the links to find out more."
        }
    }

    message_game_concept_walkers {
        id: 42,
        
        size [30, 28]
        title {
            text: "Walkers",
        }
        content {
            text: "Virtually all of the people walking your city's streets have some purpose to their travels. Some move commodities from one place to another. Others provide services to homes or other buildings that they pass. Still others are just arriving at or departing from your city. Only a very few elite people have the luxury of free time to walk about with no errand in mind. @PThese walkers can be divided into two basic types: destination walkers and roaming walkers.  Each behaves quite differently. @L@LDestination Walkers @LDestination walkers leave their places of employment with a specific goal in mind.  Using a map of your city's roads, they determine the shortest route to their destination. Examples of destination walkers include Bazaar buyers, emigrants, immigrants and delivery men. @L@LRoaming Walkers @LWalkers who roam the city bring benefits to your citizens when they pass within two spaces of housing.  Some also provide valuable services to the buildings in the city.   @PRoamers leave their buildings with no specific destination in mind.  They try to set off in a different direction every time.  From there, they can be completely unpredictable. @PEvery time walkers who roam the city encounter an intersection, they must decide which way to turn.  They don't make the same decision every time, so houses that they have passed before may not be visited again for some time.   @PThe best way to corral these walkers is through good city planning.  Since intersections give these walkers so much freedom, keeping intersections to a minimum helps to guide them to where you want them to go. @P@358Roadblocks are another effective tool in controlling roamers.  When a roamer encounters a Roadblock, he or she turns around.  Destination walkers ignore Roadblocks. @PExamples of roaming walkers include Bazaar sellers, water carriers, priests and physicians. @PSome roaming walkers behave like destination walkers under certain circumstances.  For example, fire marshals on their way to douse a fire or constables on their way to defend the city from some threat behave as destination walkers.  At all other times, though, they are roaming walkers. @L@LWalker Life @LRoaming walkers have a limited workday.  Their patrols last for a certain amount of time, after which they leave the streets for awhile.  If their employer has its full complement of workers, it sends another roamer out almost immediately.  If the building is short of employees, there is usually a delay in supplying a new roamer.   @PDestination walkers have to work until their errand is complete, even if that means walking all the way across town and back.   @PThose walkers who share both destination and roaming characteristics do have a limited workday.  Whatever time they must spend commuting to their destination reduces the amount of time that they can roam.  This is most noticable with performers, whose shows are cut short if they have long commutes from their schools to their stages. @PFinally, note that the embankment separating a flood plain from dry land is steep, muddy and treacherous.  No one can move to or from the flood plain unless a @57road makes this boundary passable. @L@LPredators @LNot everything that walks around the city is friendly. Dangerous animals also prowl the city and its environs, heartlessly killing anyone who might cross their paths. Constables will try their best to kill these beasts, but using your military is probably your best bet to defeat predators. Animals you should watch out for are hyenas, hippos, crocodiles, asps, scorpions and lions."
        }
    }

    message_employment_unemployment {
        id: 43,
        
        size [30, 28]
        title { text: "Employment and Unemployment" }
        subtitle { text: "Game Concept" }
        content {
            text: "Nearly every building in the city needs workers. The city cannot provide for its citizens without a labor force. @PWhen you first construct a building that needs labor, a recruitment agent patrols the streets looking for willing workers. If he passes some housing nearby, and if the city overall has available workers, then his quest is successful and the building that sent him will have employees. @PThe labor seeker's job is not always easy. One of the greatest challenges as leader of a city is balancing the work force with the number of jobs available. In a perfect world, a city would have exactly the same number of jobs as people who want them. This hardly ever happens. A city will either have too many workers and not enough jobs, or too many jobs and not enough workers. @PUnemployment is not good for the city. While the unemployed workers are idle, they may become disenchanted and bring the @39sentiment of the city down. They could even turn to @36crime. The best way to deal with unemployment is to create new jobs. Generally, it doesn't hurt a city to have extra goods and services. A few extra farms, more entertainment facilities, and new Schools, Libraries or Temples can benefit the city. While reducing unemployment, you could increase the city's Prosperity and Culture ratings. @PAnother - albeit heartless - way to reduce unemployment is to reduce the city's population. You can do this by destroying people's homes, forcing emigration. This, too, can have a positive effect on the city. If you destroy lower level housing, the overall value of the city's housing stock will increase. This increase could result in a higher Prosperity rating. @PThe other employment problem you will face is the labor shortage, or having too many jobs for the available workforce. The ideal solution to a labor shortage is to attract new immigrants. Build new housing areas or encourage existing areas to evolve into larger structures. Make sure that @39City&Sentiment is high, too. Paying more than the prevailing wage in Egypt or lowering the city's tax rate can also attract new immigrants. @PWhile you are waiting for the influx of immigrants to take the available jobs, work with your @24Overseer&of&Commerce and @20Overseer&of&the&Workers to alleviate the shortage. Visit your Overseer of Commerce and shut down industries you can do without for a short time. This frees up some of your workforce to take other jobs. If you don't want to shut down an entire industry, you may need to demolish some of an industry's buildings.   @PTalk to your Overseer of the Workers about setting labor priorities. Making crucial jobs a top priority ensures that the citizens continue to receive what they need to live. @PAn unorthodox and not entirely good cure to a labor shortage is to encourage your @41scribes' homes to devolve back into @40workers' homes.  You'll damage the city's Prosperity rating and decrease its tax revenues, but the labor force will increase - at the cost of your wealthiest citizens' hopes and dreams! @PAlthough being out of work is quite stressful for the jobless, a small amount of unemployment is actually a good thing for an expanding city, because it gives you a willing labor pool for new buildings.  Unemployment in excess of 5 percent causes problems."
        }
    }
    
    message_drinking_water {
        id: 44,
        
        size [30, 28]
        title { text: "Drinking Water" }
        subtitle { text: "Game Concept" }
        content {
            text: "One of the first things people demand is access to clean drinking water. Their housing will not improve at all without at least some water. @P@62Wells and @61Water&Supplies provide drinking water to citizens.  Wells are a rudimentary source of water. They may be acceptable to citizens when the city is new and struggling to succeed, but people won't be satisfied with well water for very long. They'll soon demand water from Water Supplies. @PWater Supplies employ water carriers to bring water to people's homes. When a water carrier passes a home, that home has access to clean water. Keep a close watch on the water carriers: they are @42roaming&walkers and may not always follow the same path twice. Homes that once had plenty of access to clean water can lose it, especially if you change the neighborhood's road network.  @PIf the @56desirability of the surrounding area is high enough, the workers at the Water Supply will take steps to improve its appearance and its efficiency. Water carriers from one of these evolved Water Supplies will circulate through the neighborhood more frequently. @PBoth Wells and Water Supplies can only be built on land that has groundwater, denoted by grass growing there. @PRead the entry on @53City&Health for more on the benefits of clean drinking water."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,
        
        size [30, 28]
        title { text: "Food and Farming" }
        subtitle { text: "Game Concept" }
        content {
            text: "The way to citizens' hearts is through their stomachs.  Providing plenty of food - and a good variety - bolsters both @39City&Sentiment and @53City&Health.  @PThere are many types of food farms in Pharaoh, including @89grain, @90pomegranate, @90chickpea, @90lettuce and @90figs. There are also two types of farming in Pharaoh: floodplain farming and meadow farming. Both types of farms require road access and labor, but most similarities end there. Farming isn't the only source of food, either.  @359Hunting, @84fishing and @360cattle&ranching all contribute to the city's Granaries. @L@LFloodplain Farming @LTo understand how floodplain farms work, you must first understand the Nile's stages. Every year, usually between June and September, the Nile floods its banks. The flood plains are completely submerged, and nothing can be placed on the land. In a few months, the Nile begins to recede, leaving nutritious silt behind that fertilizes the soil. The flood plain reemerges, and you can again operate farms on the flood plain. @G56 @PThe Nile does not flood at exactly the same time or in exactly the same way every year. Some floods are better than others. Priests use Nilometers to determine how good the next flood will be and report their findings to your @31Chief&Overseer. Paying special attention to Osiris, God of Agriculture and the Nile Flood @51(see&Religion), can help ensure successful floods every year. @PYou can build farms (and roads, and Irrigation Ditches) on the flood plain at any time except during the flood. When you build a floodplain farm, only the field appears, with no buildings, because the flood destroys any buildings on the floodplain. Since they can't build homes on the floodplain farms, peasants need a place to meet to be assigned to work. @8Work&Camps serve this function.  Work Camps dispatch workers to the farms to plant and reap the crops, and farms lie idle unless there is a Work Camp.  There's a limit to how far peasants will walk to reach their back-breaking assignments, so don't put Work Camps too far from the fields. @PThe best time to build farms is soon after the flood recedes. You'll be able to take full advantage of the growing season until the next flood, and the farm will have maximum yield. Farms placed at any other time will produce less. @PThe other factor to consider when placing farms is fertility. The darker the land and lusher the grass, the more fertile the land is. The most fertile land is usually found directly adjacent to the river. As you move away from the river, the land becomes less fertile. Farms placed on the most fertile land produce the highest yields. You can build Irrigation Ditches on flood plains to irrigate the land farthest from the river, thereby improving the fertility of land which might be left high and dry during a poor Inundation. @PDue to the annual rhythm of the Nile, floodplain farms can produce only one crop each year. A city's survival can depend on having enough workers to harvest the crop, and enough storage space to accept the harvest. @L@LMeadow Farming @LFloodplain land is not the only fertile land, although it forms the bulk of available arable land. Farms can also be placed on meadows, denoted by yellow tufts. The denser these tufts are, the more fertile the land is, resulting in larger yields. These farms do have a work building on site, so they do not need peasants from a Work Camp. Because the land is not flooded, these farms continue to work throughout the year. However, acre for acre, meadow land is less fertile than floodplain land, and farms on the meadow tend to yield fewer crops per harvest.  Meadow farms almost always benefit from Irrigation Ditches. @L@LHunting and Fishing @LHunters and fishermen take advantage of Egypt's natural abundance. Both set out from their bases, capture their prey, and return back to their bases to prepare the food. @PHunters work out of Hunting Lodges. From the Lodge, they set out for the hunt. Hunters will look for flocks of ostriches, waterfowl, or a herd of antelope. If you notice any of these animals around the city, place a Hunting Lodge nearby. @PFishermen gather at Fishing Wharves where they swap stories about the one that got away. Wharves, of course, are located on the water, and fishermen need a Shipwright to build them a boat. Once they have a boat, they'll set out. Not every city can support hunting or fishing. If you notice fish jumping out of the water, the city can have a fishing industry.   @PHerd, flock and school sizes are limited.  Hunting and fishing can provide a small population with enough food, but a large population will not be able to subsist solely on fish or game meat. @L@LCattle Ranching @LCattle Ranches can be an excellent source of additional food. They can be placed on any type of land - not just fertile land - which saves arable land for another purpose.  Cattle consume straw, the by-product of @89grain&farming. The number of cattle ranches a city can have is limited only by the amount of straw the city can devote to cattle feed. @L@LFood Distribution @L@3Granaries and @2Bazaars are the intermediaries between food producers and the city's inhabitants. Granaries store the food intended for consumption by people, and Bazaars distribute it to individual homes.   @POnce a food producer has an item ready, a cartpusher brings the food to a Granary. Bazaar buyers go to the Granaries to procure the food their customers are asking for. They can carry more than one type of food at a time. After the buyers return to the Bazaar with their items, Bazaar traders walk through the neighborhood, delivering food to the populace. @PIt's important to have enough Granaries and Bazaars. If all Granaries are full, the cartpusher takes the food to a @4Storage&Yard, if it has been instructed to accept food. Bazaar buyers won't procure locally-produced food from Storage Yards (although they will take non-food items and imported foods there). Bazaar buyers get most food from Granaries. @PPlacing Bazaars and Granaries can be tricky. Granaries should be close to the food producers so that cartpushers don't have far to travel.  Bazaars should be close to Granaries so the Bazaar buyers can keep their Bazaars well-stocked.  Bazaars also need proximity to the houses they will serve.  All of these structures make for undesirable neighbors, so siting them always involves tradeoffs.   @PAs your city grows, you might have to build Granaries further away from the food producers to ensure that Bazaars in outlying neighborhoods can procure the food they need. If you find that you need to do this, use the Granary's Special Orders to make sure it receives food. @L@LImporting Food @LSome cities cannot produce enough food to sustain themselves, or can produce only limited varieties of food, and so need to import food from other cities. Imported food is delivered to Storage Yards, where Bazaar buyers can pick up the foodstuffs and bring it back to the Bazaar. @L@LRelated topics are hyperlinked throughout this section (hyperlinked words appear in a different color than the rest of the text). Reading these entries will help understand food production and distribution. @L@LFor a history of food in ancient Egypt, click @150here. Learn about the affects of the Nile by clicking @157here."
        }
    }

    message_game_concept_industry {
        id: 46
        
        size [30, 28]
        title { text: "Industry" }
        subtitle { text: "Game Concept" }
        content {
            text: "Industry is likely one of the biggest employment sectors in the city. Citizens use some of the products industries produce to enhance their lives. Other products can be @47traded for a tidy profit.   @PWhile a city likely has a myriad of industries, all share certain characteristics. They all need a labor force, and efficiency is compromised if a particular manufacturer or raw material producer is understaffed. All industries need road access, too, so that workers can get to them. @PSome industries produce a raw material that can be processed into a finished good at a manufacturer. These industries are @92Clay&Pits, @361Gemstone&Mines, @93Copper&Mines, @94Wood&Cutters and @94Reed&Gatherers.  @91Barley&Farms, @91Henna&Farms and @91Flax&Farms also produce a raw material for industry. @89Grain&Farms, in addition to producing food, also produce a non-food item, straw. One raw material producer usually generates enough to support two finished goods industries. Raw materials can be traded, but they do not fetch as high a price as a finished product. @PIndustries that transform raw materials into another product (sometimes referred to as 'workshops') are @96Breweries, @99Jewelers, @60Weavers, @97Papyrus&Makers, @1Potters, @364Brickworks, @473Lamp&Makers, @470Paint&Makers, @98Weaponsmiths and @98Chariot&Makers. Their finished products can be used by the city or traded on the open market. @P@95Quarries and @93Gold&Mines are different from other industries, because their raw material is also their finished product. @82Shipwrights produce a finished product (ships) from a raw material (wood), but ships cannot be traded on the open market. @PDelivery men bring goods where they need to go. Delivery men employed by raw material producers always try first to bring their loads to workshops that needs the material, favoring the nearest location. If no industries require the raw material, the delivery man proceeds to the closest @4Storage&Yard that has room for his goods. If no Storage Yards are available, the delivery man takes a break until space opens up. The only raw material delivery men who do not behave in this fashion are the Gold Mine cart pusher and the quarry sled puller.  The Gold Mine cart pusher brings his gold only to the Palace, never to a Storage Yard.  Because stone cannot be manufactured into any other good, quarry sled pullers always bring their materials to a Storage Yard. @G74 @PSome city buildings need industrial goods to fully function. These include the @70Library, @68Scribal&School, @74Senet&House, @88Recruiter, @66Mortuary, @363Artisans'&Guild and @363Carpenters'&Guild. A delivery man from a manufacturer tries to bring his finished goods to one of these buildings that needs it. If none are available, he, too, brings his finished product to a Storage Yard, or stands idly by until space opens up. Cartpushers like these impromptu holidays, because they still draw wages and rations while standing about doing nothing.  @PTo see if your industries have any problems, use the @18Problems&Overlay. This overlay shows you which industry buildings are not working properly, and why.   @PRight-clicking on a building shows the building's current production status. It tells you if the building has full employment, and how far along in the production cycle they are. If there are any problems, the panel tells you what they are.   @PClick on any of the above hyperlinks (hyperlinked text is blue) to read about specific industries. @L@LClick @151here for a history of industry in ancient Egypt."
        }
    }

    message_game_concept_trade {
        id: 47,
        
        size [30, 28]
        title {
            text: "Trade",
        }
        subtitle {
            text: "Game Concept",
        }
        content {
            text: "No city is completely self-sufficient. Trade brings products to your city that it cannot produce itself. Exporting goods brings in a lot of money - often more than the city can earn from taxes. Because of its importance, your city should begin trading as soon as it can meet the basic needs of its inhabitants. @PThe @32World&Map shows which cities will trade with you. Cities willing to trade fly a flag.  Click on one of these cities to find out which products the municipality buys and sells.  Blue dots displayed in the corner of the commodity symbol show how much a city is willing to import or export each year.  One dot means they don't deal in that good very much at all, while three dots signal a strong desire to trade that item.  These levels can change with supply and demand or political pressures in Egypt.  @PClick on the 'Open Trade Route' button to spend the funds to establish the new partnership.  Opening a trade route can be costly, but it pays off in the long run. @POnce you open a trade route, visit your @24Overseer&of&Commerce to set up the interactions. Click the 'Show Prices' button to see how much products can be bought or sold for. You'll notice that products sell for less money than they cost you to buy. The difference in the prices covers the merchant's expenses in coming to your city. @L@LImporting @LTo import a good, click on the commodity you want. After you select an item, you have two choices.  You can decide for yourself how much of the item you would like the city to have on hand and instruct your Overseer of Commerce to behave accordingly.  Or, you can let your Overseer of Commerce decide how much the city should have on hand.  Your Overseer of Commerce will continue to import the item as long as the city's stocks are under the prescribed level, or until the trade partner's annual trade limit has been reached. @PSome goods your city needs can only be imported. These include white marble for monument construction and oil for @473lamps. To evolve the city's @56housing to its highest level, you will also have to import luxury goods. @PImports can become quite expensive, so monitor the city's @4Storage&Yards carefully. If you notice that the Storage Yards are full of a particular good the city is importing, save money by not importing the good until stocks are depleted. Also, importing raw materials is cheaper than importing finished products. In the long run, the city will save money if it has its own manufacturers to turn an imported raw material into a finished product. @L@LExporting @LTo export a good, click on the item you wish to export.  Then, decide for yourself how much the city should have on hand or let the Overseer of Commerce make the decision. Surpluses will be exported up to the customer's annual quota. Keep in mind that some commodities the city exports are also desired by its citizens, so make sure you keep enough in storage for citizens' needs. Check in with your Bazaars and your citizens' housing frequently to see if they have a supply of the good you are trading. Also, make sure that the buildings that need a finished good have a supply on hand. If housing and other buildings are having difficulty getting an item, the city is probably exporting too much. @L@LSometimes a city can either export or import the same commodity. This gives you more flexibility as you plan the city's industries. If you want to bolster a city's income, dedicate labor to produce the commodity and export it to a trade partner. If you want to use the city's labor force for another purpose, then import the product instead. The city can never simultaneously import and export an item, and it won't benefit from importing the product from one city just to sell it to another. Buyers pay more than sellers receive, so the city will only lose money if it acts as a middleman. On the other hand, importing a raw material and exporting its finished good is often a very profitable proposition. @PMerchants approach your city either by caravan or trade ship. Before you can trade with either type of merchant, you must have a working Storage Yard. In addition to a Storage Yard, you also need a @83Dock if you are to engage in trade with merchant barges. Trade ships conduct all their business at Docks, and when they arrive cartpushers from the Docks will retrieve needed items from the Storage Yards."
        }
    }
    
    message_game_concept_money {
        id: 48,
        
        size [30, 28]
        title {
            text: "Money",
        }
        subtitle {
            text: "Game Concepts",
        }
        content {
            text: "You can't build a city without money, and the amount of money in its coffers is a good indicator of the city's success.  The city earns money by imposing taxes, exporting commodities, receiving gifts and, if available to the city, by mining gold.  These comparatively obvious topics are explained toward the end of this entry.  First, though, you should know the finer points of money management.  @L@LDebt @LThe first time your treasury runs dry, other Egyptian leaders might deliver a bail-out gift of additional debens.  This doesn't penalize you in any way, and they don't expect repayment.  Consider it a warning, though, that your city needs to change its free-spending ways. @PIf you spend all of your rescue funds, or if you don't receive such a gift, your treasury can accrue up to 5,000 debens in debt.  Yellow numbers show that your city has a debt. @PVery brief, sporadic forays into debt are often unavoidable, and these will not harm you if you quickly restore a positive balance to your accounts.  Long-term indebtedness can cost you the game. @L@LConsequences of Debt @LEvery month that your treasury has a deficit costs you an interest payment, which is automatically added to your debt total.  The greater your indebtedness, the more interest you have to pay, and the larger your debt grows.   @PWhenever your city ends a calendar year in debt, you cannot meet your annual tribute payment (see below).  Missing a tribute doesn't cost you any money, but it does depress your @35Kingdom&rating somewhat.  The effect worsens if you miss consecutive yearly tributes. @PIf you don't achieve a positive treasury balance (however briefly) for 12 months after first incurring debt, your Kingdom rating suffers as other Egyptian leaders lose confidence in your ability to govern.  Your first 'debt anniversary' penalty, while painful, probably won't cause irreparable harm.  If you have still not seen positive numbers on your second debt anniversary, your Kingdom rating drops substantially, and subsequent years will be even worse.   @L@LGetting Out of Debt @LDebt is clearly a serious problem, and when you can't avoid it, you need to retire your debt as quickly as possible.  Ways to raise money are discussed below, but you should also refrain from spending any of your limited credit on anything that will not ultimately earn you money.  Tax Collector's offices, industries that make exportable commodities and new trade routes with cities that will buy your products could all be wise expenditures.  @L@LAnnual Tribute @LAt the end of the year, your city has to pay a 'tax' to the Kingdom, known as 'tribute'.  The amount of tribute varies with your city's ability to pay, so that it starts out quite small and increases as the city grows in population and wealth.  Visit your @30Overseer&of&the&Treasury to see how much tribute you're paying.  @PAs long as you end a year with debens in your vaults, tribute payment is automatic.  You never actively make this payment.  Whenever you end the year in debt, though, your city can't pay its tribute, and your @35Kingdom&rating falls.  The penalty is not excessive for missing one year's tribute, but it grows larger the second consecutive year, and even larger after that.  This reflects your worsening reputation with your own people for being a poor financial manager.  @L@LTaxes @LTaxes charge citizens for all the services the city provides them. Citizens won't grumble about paying taxes as long as the tax rate is reasonable. The initial tax rate of 9 percent is a good benchmark, but you can raise or lower the rate at any time. Visit your Overseer of the Treasury or right-click on the Palace to adjust the rate. Lowering the tax rate buys you joy and appreciation. Raising the tax rate prompts complaints, and could lead to a mass exodus of citizens from the city. @PRaising the tax rate may be necessary sometimes. If you notice that your city is about to go into debt, you can raise the tax rate to alleviate the problem. You should probably find an alternate long-term solution to your city's money problems, though. A high tax rate can quickly worsen @39City&Sentiment. @PWhile citizens don't mind paying taxes, they won't volunteer a portion of their income without being asked. To collect taxes, the city must have a @77Palace. Then, build @80Tax&Collectors'&offices to actually collect the tax. @PThe Overseer of the Treasury knows what percentage of your population is registered for the tax, and how much tax income was not collected because of a lack of tax collectors. Use the @18Tax&Overlay to see if a particular area of your city is getting off easy. Also, make sure that you levy taxes in the city fairly.  If a portion of the city's inhabitants is paying a high tax rate and the other portion is not paying any at all, @39City&Sentiment will plunge, and @36crime could break out. @L@LTrade @LMoney from exports will likely be the city's main source of income. Open up trade routes as soon as possible. It's crucial that you understand how to export commodities, so be sure to read up on @47trade if this gives you problems. @L@LMining Gold @LSome cities can manufacture their own money. Gold is converted into debens, the basic currency in Egypt. If you see metal nuggets embedded in an outcropping of rock, then you might be able to build a @93Gold&Mine. Don't get too excited; the ore might turn out to be @93copper, which is quite valuable in its own right but usually not as welcome as gold. Click the industry button on the Control Panel, then click raw materials, to find out which precious metal your city can mine.  @PGold Mines function like other @46industries, but their output is delivered only to the Palace, where it is turned into debens, and never to a Storage Yard. @L@LFamily Savings and Salary @LLike the city, you, too, can earn money. You are paid for your efforts as city leader and can draw a wage as soon as you build yourself a @78Mansion. Your salary is paid to you from the city's treasury, and your wage is commensurate with your experience. You can choose to alter your wage, but if you pay yourself too much more than you are worth, your @35Kingdom&rating could tumble. You can also pay yourself less money, or not pay yourself at all, which can impress people and help your Kingdom rating. If your city is having financial difficulties, not paying yourself a salary is a good way to cut costs. @PYou can transfer family savings to the city treasury at any time - a good way to erase or prevent debt.  You can never transfer treasury money to your family account, though.  That would be embezzling! @PYour family savings can also purchase a 'gift for Egypt.'  Such donations to the people of Egypt, or, at your Overseer's discretion, to other Egyptian leaders will immediately improve your Kingdom rating by a small amount.  Be careful with this strategem, though.  Once the gifts begin, their recipients come to expect them, especially if you have been handing them out on a regular basis.  Cutting them off can actually harm your rating. @PReading the entry on the @22Political&Advisor will provide you with more information on your personal savings."
        }
    }

    message_game_concept_entertainment {
        id: 49,
        
        size [30, 28]
        title {
            text: "Entertainment",
        }
        subtitle {
            text: "Game Concept",
        }
        content {
            text: "All work and no play make Imhotep a dull boy. Provide the city's inhabitants with entertainment to make the city an enjoyable place to live. @P@71Booths, @72Bandstands, @73Pavilions, @74Senet&Houses and @479Zoos provide citizens with the entertainment they crave. When your city is new, citizens are content with the smallest of the venues, the Booth. As your city grows, so too will the demand for entertainment, and citizens will expect to be entertained by a range of different performers. Your @28Overseer&of&Diversions will help you assess your citizens' needs. @PMost entertainers need to be trained in their crafts at @75Training&Centers. Jugglers hone their craft at Juggler's Schools, musicians practice at Conservatories, and dancers learn the latest steps at the Dance School. Once trained, the performers will walk from the Training Center to the entertainment venue. Senet masters are not trained at a Training Center. @PYour citizens realize they have access to entertainment when they see entertainers pass by their houses (click @42here for more on walkers). Entertainers come from fully functioning entertainment venues. Musicians, Jugglers and Dancers also walk the streets when they are going from the Training Center to the venue.  Keep this in mind when you plan your facilities. If you put your entertainment venue and Training Centers on opposite sides of a neighborhood, a performer will have to pass by housing to get to his or her venue, bringing entertainment benefits along the way. But be careful not to place Training Centers too far away from your entertainment venues. The further a performer has to travel, the shorter the amount of time a show will run for and the more likely an entertainment venue will be dormant, bringing no benefit to anyone.   @PThe Senet House and the Zoo both require a supply of goods to function. The Senet House needs @96beer to quench the thirsts of its parched patrons, and the Zoo needs @89straw and @359game&meat to properly care for the animals. @L@LClick @165here for more on entertainment in ancient Egypt."
        }
    }

    message_game_concept_education {
        id: 50,
        
        size [30, 28]
        title {
            text: "Education",
        }
        subtitle {
            text: "Game Concept",
        }
        content {
            text: "Education is the privilege of the wealthy.  The wealthy know that education at a @68Scribal&School is the pathway to a better life for their children, and they like access to a @70Library for themselves. @PNeither Scribal Schools nor Libraries will function without @97papyrus. Before you can build a Library, you must have enough papyrus stored in the @4Storage&Yards to fill the Library's shelves with scrolls. @42Walkers from both structures take papyrus with them as they spread education to the populace. The city needs to manufacture or @47import papyrus to keep education structures working. @PVisit your @27Overseer of Learning to make sure that the city is meeting citizens' demands for education.  @PHaving enough Libraries and Schools for your citizens contributes to your @35Culture&rating. @L@LFind out more about how the ancient Egyptians entertained themselves by clicking @165here."
        }
    }

    message_game_concept_relition {
        id: 51,
        
        size [30, 28]
        title {
            text: "Religion",
        }
        subtitle {
            text: "Game Concept",
        }
        content {
            text: "There are five major gods in Egypt: Osiris, God of Agriculture and the Nile Flood, Ptah, God of Craftsman, Ra, God of the Kingdom, Seth, God of Destruction, and Bast, Goddess of the Home. Appeasing these gods pays dividends, and ignoring them causes the grief. Your @29Overseer&of @29the&Temples knows the mood of the gods, so check in with him often. @PMany cities have a patron god.  The patron god expects more from a city than the other, local deities.  Local deities demand less than a patron god, but can impact the city, for good or for ill, just the same.  Some gods may be unknown to the city, and may be safely ignored. @PThe best way to appease the gods is to dedicate plenty of @67Temples&and&Shrines to them. The patron god expects to have more Shrines dedicated to him or her than any other god. Each local god expects fewer Temples and Shrines than the patron god, but expects to have the same number of Shrines and Temples as the other local gods.  @PGods can also be appeased with festivals, the bigger the better. Lavish and grand festivals are valuable stop-gap measures if a particular god is growing angry with the city. Hold a festival in the angry god's honor, and the god will feel better, buying you time to erect more Temples or Shrines before incurring the god's wrath. Visit your @29Overseer&of&the&Temples to plan a festival. Note that until you have built a Festival Square, the city cannot hold a festival.  Grand festivals also require the city to have enough @96beer in its @4Storage&Yards. Because of the effort it takes to plan a festival, a city can only have two festivals in any 12-month period.    @PIn addition to Temples and Shrines, you can also build a Temple Complex, generally in honor of the city's patron god. Each city can only have one Temple Complex at a time.  Sometimes, you can build a Temple Complex for a local deity if he or she has grown to become particularly important.  Be careful, though. The city's patron god may become very jealous if another god has a Temple Complex dedicated to him or her. @PTemple Complexes are costly, but worth the expense.  Having a functioning Temple Complex brings the city many benefits and increases its @35Prosperity&rating.  You can also pay to add an Oracle and an Altar to a Temple Complex.  The Complexes and their additions are: @L@L@350Temple&Complex&to&Osiris: @P\tAltar of Sebek @P\tOracle of Min @L@351Temple&Complex&to&Ra @P\tAltar of Ma'at @P\tOracle of Horus @L@352Temple&Complex&to&Ptah @P\tAltar of Amon @P\tOracle of Thoth @L@353Temple&Complex&to&Seth @P\tAltar of Anubis @P\tOracle of Sekhmet @L@354Temple&Complex&to&Bast @P\tAltar of Isis @P\tOracle of Hathor @L@LProviding citizens with multiple places of worship to multiple gods contributes to the city's @35Culture&Rating. @L@LFor more on religion in ancient Egypt, click @399here."
        }
    }

    message_game_concept_war {
        id: 52
        
        size [30, 28]
        title {
            text: "War"
        }
        subtitle {
            text: "Game Concepts",
        }
        content {
            text: "War is nearly a constant threat in Egypt.  Sometimes, invaders from other lands foray into Egypt with visions of greater glory.  At other times, unrest within Egypt's boundaries causes infighting between cities, or even full scale civil war.  Occasionally, Pharaoh himself decides to wage war against sworn enemies or rebellious allies. @PYou can do many things to prepare and protect the city from the horror of war.  Build @85Defensive&Structures to seal the city's boundaries against invading forces. Also build @37Forts, @356warships and @357transport&ships to attack any foes that penetrate the city's borders. @PYour @21Overseer&of&the&Military will warn you of impending attack, and you will get @34messages telling of enemy military movement.  You can trace the path of approaching enemies on the @32World&Map. @PBe careful not to provoke attack yourself. If you mismanage the city or anger others in Egypt, the @35Kingdom&rating will sink.  If the Kingdom rating drops low enough, your city could be attacked. @PWar is not limited to your city's environs. At various times, Egypt is engaged in battles within its own borders and throughout the world. Sometimes, another city or Pharaoh may need some of your troops or warships to defeat a foe.  Dispatch the troops for this Kingdom service by visiting your Overseer of the Military and earmarking particular companies or ships for service abroad and sending them on their way. If more than one city wants aid, you will have to visit your @22Political&Overseer to choose a city to which to send help. @L@LFor more on enemies of ancient Egypt, click @181here."
        }
    }

    message_tutorial_health {
        id: 53
        
        size [30, 28]
        title { text: "Health" }
        subtitle { text: "Game Concept" }
        content {
            text: "Poor city health can discourage immigrants from coming to your city, and could even cause some of the city's residents to die. Take steps to ensure that your citizens feel fit. A number of health disasters could befall your citizens if you do not take precautions. @PTo keep your citizens healthy, make sure they have access to plenty of food and to a @64Physician's&office. The more types of food your citizens eat, the healthier they feel. Access to @66Mortuaries also improves overall city health.  Clean drinking water from a @61Water&Supply and access to an @65Apothecary helps to reduce the risk of malaria. Overall city health is determined by the health of each of its citizens, so be sure to provide adequate access to healthcare to all inhabitants of the city. @PAlong with malaria, disease and the dreaded plague stalk the city. With careful planning and an ever watchful eye on citizens' health, these health problems can be avoided. @L@LDisease @LDisease occurs in homes that are not visited by a physician frequently and do not have a steady supply of food. Disease strikes homes individually and does not spread.  However, if an entire neighborhood has particularly poor access to physicians and to food, then more than one house could become diseased. @PUse the @18Risks&Overlay to see which homes are likely to develop disease.  Build more Physician's offices in these areas, and make sure @2Bazaars are supplying the houses with food. You can also use the @18Physician&Overlay to see which homes have good access to physicians, and the @18Bazaar&Access&Overlay to see which homes are visited by Bazaar traders. @L@LMalaria @LMalaria is one of the risks of living near the water. Homes close to the river and to reed-filled marshes are most at risk. Like disease, malaria strikes individual homes. The illness, however, will spread to neighboring homes. To combat the risk of malaria, build plenty of Apothecaries in at-risk areas, and make sure that houses in these areas receive water from a Water Supply. Use the @18Malaria&Overlay to see which homes are particularly prone to the illness. @L@LPlague @LOutbreaks of plague occur when overall city health is low, regardless of the health of particular homes. The only thing you can do to avoid plagues is to make sure you keep the city healthy overall. By the way, don't confuse plague with @494Major&Plagues. Major Plagues are caused by factors beyond your control, not by city health. @PWhen plague does break out, it begins in one house. One of the delirious, plague-stricken individuals in the house wanders the streets, infecting each house he passes. In a month's time, he'll succumb to the illness. An herbalist from an Apothecary will promptly remove any plagued citizen he encounters. @PNo overlays can show you which house will host the first plague victim, because plague is unrelated to conditions in any particular home or neighborhood. @L@PIf a house becomes infected with any of the above ailments, all the people in the house die. The house remains infected for two months, during which time no immigrants or vagrants will move in. After two months, the housing is cleansed and livable again.  All of the goods its previous inhabitants owned are still there. @PWhile classified as a health building, the Dentists' office contribute to an area's property value and have no effect on city-wide health. @PYour @26Overseer&of&Public&Health will help you keep your citizens well."
        }
    }

    message_bent_pyramid {
        id: 54,
        
        size [30, 28]
        title {
            text: "Bent Pyramid",
        }
        content {
            text: "Inspired by the sun, the architects who contrived the Bent Pyramid envisioned a giant obelisk with bent sides, representing one of the sun's warming rays.  So that it would shine as brightly as the sun, the sides of the Pyramid were smoothed. @PTo build a Bent Pyramid, you will need supplies of @95plain&stone and @95limestone, and peasants from a @8Work&Camp.  When four blocks of either plain stone or limestone are stored in the @4Storage&Yards, peasants load the stone onto a sledge and drag it over to the construction site.  To properly place the stones, the services of the @363Stonemasons&Guild are essential.  The @363Carpenters&Guild provides ramps from wood that is delivered to the Carpenters' Guild. @PBent Pyramids come in two sizes. Read the entries on @370Monument&Construction, the @373Overseer&of&the&Monuments and the @369Construction&Foreman for more information. @L@LTo find out more about the history of the Bent Pyramid, click @392here."
        }
    }

    message_brick_core_pyramid {
        id: 55,
        
        size [30, 28]
        title {
            text: "Brick-core Pyramid",
        }
        content {
            text: "Brick-core Pyramids are the most complex Pyramids you will build. They require three types of raw materials and three types of construction guilds. You need @364brick, @95limestone and @94wood to build them, as well as the services of the @363Bricklayers'&Guild, the @363Stonemasons'&Guild and the @363Carpenters'&Guild. You also need peasants from @8Work&Camps to haul the heavy bricks and stones to the work site once enough is stored in the @4Storage&Yards. @PBrick-Core Pyramids can be small, medium, large, Pyramid Complex and Grand Pyramid Complex. @PRead the entries on @370Monument&Construction, the @373Overseer&of&the&Monuments and the @369Construction&Foreman for more information. @L@LTo find out more about the history of the Bent Pyramid, click @392here."
        }
    }

    message_housing_and_desirability {
        id: 56
        
        size [35, 32]
        title { text: "Housing and Desirability" }
        content {
            text: "The first step to building a neighborhood is to designate a housing area. Remember that all housing needs to be within two spaces of the road. Once you lay out an area, immigrants move in and set up simple huts. They forage the local countryside to find what they need to survive. As time passes, however, citizens begin to expect the city to provide for their needs. As you meet these expectations, citizens take it upon themselves to improve their housing conditions.  The quality of housing affects the city's @35ratings, keeps citizens from emigrating and attracts new citizens to your city. @PCitizens' most basic needs are access to clean @44water and @45food from @2Bazaars. Once you provide these two necessities, you will notice huts turning into more stable shanties and cottages. @PAfter food and water, citizens begin demanding a variety of goods and services. Citizens want supplies of @1pottery, @96beer and @60linen in their homes.  The wealthiest citizens will also demand a supply of different @99luxury&goods, such as jewelery.  As their tastes become more refined, they demand a second, imported luxury good. In addition to these commodities, residents expect access to all their favorite services, like @51religion, @49entertainment, @50education and @53health&care.  Providing all these goods and services inspires residents to improve their homes into large and stately structures. @PResidents also want to live in attractive neighborhoods. You can establish fine @79Gardens and build @79Statues, or cover paved roads with @79Plaza tiles. Citizens will appreciate the effort you put into beautifying their surroundings and will likely improve their housing to match. @PThe corollary to wanting to live in attractive surroundings is not wanting to live in unattractive surroundings. Citizens balk if their housing is too close to industry or to farms. They much prefer to live away from the loud noise and strong stench frequently emitted from these structures. Furthermore, most residents think that industrial structures are eyesores. If you must place housing near industries (and sometimes you must, to make sure that industries are staffed), try to compensate for the inconvenience with plenty of Gardens, Statues and Plazas and the easiest of access to desired goods and services. Ultimately, though, you probably must resign yourself to having some industrial slums blighting the city. @PThe advantages of high-quality housing are many. Highly evolved housing has a positive effect on the @35Prosperity&Rating. Evolved housing also holds more residents, which allows you to increase the city's population - and potentially the workforce - without designating new housing areas. Once your housing reaches the highest levels, residents become @41scribes, who pay taxes but leave the city's workforce. @PTo find out what a specific dwelling needs to evolve, right click on it. Its residents won't be shy about telling you what they want. @L@LThe ancient Egyptians lived in homes of varying sizes and quality.  Click @152 here to find out more."
        }
    }
    
    message_game_concept_roads {
        id: 57,
        
        size [30, 28]
        title {
            text: "Roads",
        }
        content {
            text: "Roads begin as dirt paths. As conditions in the city improve, its residents take it upon themselves to pave roads. Once a road is paved, you can place @79Plazas over it.  @PEfficiently planned roads can go a long way to ensure that your city runs smoothly. @42Walkers who provide services to your city move easier over long, straight roads rather than short roads with lots of twists, turns and intersections. @PNearly all structures in your city need access to roads. The only exceptions are Gardens, Statues, and Forts. Shrines, Walls and housing do not need direct road access, but must be within two spaces of the road to receive benefits from passing walkers. @PWalkers can only cross the boundary between the flood plain and dry land where there's a road.  This embankment is steep, muddy and treacherous, but a road permits safe passage. @PAll roads have the same traffic capacity, and walkers move at the same speed, regardless of whether or not they are paved. @L@LThe Kingdom Road @LThe road running through your lands when you begin a new mission is the Kingdom road, and it has a special status.  Trade caravans and immigrants arrive on the Kingdom road, and emigrants leave by it.  Every part of your city needs a clear path to the Kingdom road.  If you isolate some part of the city from this important thoroughfare, that area will stagnate.  Any delivery people who were en route to the now-isolated enclave will stop in their tracks until access is restored.  Sometimes royal architects might remove whatever structure you built that blocks access.   @PThis doesn't mean that every one of your city's streets has to physically connect to the Kingdom road, merely that all buildings must have a clear, walkable path, whether via road or empty land. @PChances are that this is all you need to know about the Kingdom road.  The finer points of building access will never concern most players, but there are some rare circumstances in which you might lose Kingdom road access without creating any visible obstruction. @PWhen you first build something new, the structure seeks a path to the Kingdom road, whether by your city's road network or by open, walkable land.  Most of the time, you place the building on an existing road, so that road's access to the Kingdom road is what matters.  Sometimes, though, you might build something that isn't on a road.  In these cases, the new structure checks for Kingdom road access across the intervening open land.  If you subsequently connect this building to a city street, the building redefines its access point to be on the new street.  So, if the new street itself cannot find a walkable path to the Kingdom road (perhaps it is blocked by the very building that you just connected it to), the building that adjoins this road will also lose access to the Kingdom road. @PFor more about 'access points,' read the following section. @POne final point about the Kingdom road:  There is nothing special about the actual, physical road itself - only the points at which it enters and leaves your lands are crucial.  You can relocate parts of the Kingdom road just like any other road in your city, as long as you do not block access to these vital entry and exit points. @L@LBuilding on Two Roads @LSometimes, you might place a building adjacent to two roads that are either unconnected to each other, or connected far from the building.  This does not let walkers leave or enter the building from both roads.  Every building can have only one 'access point,' and so only one active road. @PFor example, suppose that you build a Storage Yard with a road on its southern side.  Manufacturers, caravans and Bazaar buyers south of the Storage Yard will interact with it just as you would expect.  Now say that you want industries north of the yard to use it, too.  If you build a road on the northern side of the Storage Yard, you might expect that industries to the north will interact with the yard using the northern road, while industries to the south will continue to use the road to the south.  But the building can have only one access point, so those industries to the north are out of luck unless you build a connector between the northern and southern roads. @PWhen a building does have two or more roads adjacent to it, it chooses its access point based on the larger road network.  Using the example above, if the southern road is part of your city's main street network while the new northern road goes to a small industrial outpost, then the Storage Yard's 'access point' is on the southern road.  If, on the other hand, the original southern road leads to a smaller colony and the new northern road connects to the main city, then the northern road is the building's preferred access route. @PTo avoid unpredictable behavior, don't construct buildings that touch two unconnected roads.  Either connect the roads, or know that only one of them will actually carry traffic that can interact with the building.  Watch how walkers in the vicinity behave to determine which of the roads is the building's access point. @L@LClick @153here to travel the history of roads in ancient Egypt."
        }
    }

    message_game_concept_water_crossings {
        id: 58,
        
        size [30, 28]
        title {
            text: "Water Crossings",
        }
        content {
            text: "There are two types of water crossings: Bridges and Ferry Landings. Bridges can only span short lengths of water.  Ships cannot sail underneath Bridges, so be sure to use them only when the body of water the bridge is spanning is not host to any ship traffic. @PBridges can only be placed where the shoreline is straight. The corresponding shore on the opposite side must also be straight.  When you pick an appropriate spot for a Bridge, you will see a green 'ghost' of the Bridge along with its cost (Bridges are priced per tile). If you have not picked an appropriate place, you will see red squares. Bridges do not require any labor, but do require road access. @PFerries dock at Ferry Landings and work much like Bridges, but are more versatile. Ferries do not impede the path of any other boats, so all sorts of ships can come and go as they please. @PLike Bridges, Ferry Landings must be placed on a straight piece of coastline. When you select an appropriate place, you will see a green square. You do not have to place the second Ferry Landing directly opposite the first. You can choose from a range of places on the other shore, provided the coastline is straight. Green blocks will highlight the appropriate places. @PBecause immigrants and emigrants use their own boats, they can use Ferry Landings as soon as they are placed. Ferry Landings must have workers, though, to transport other citizens. @42Walkers with a specific destination in mind, such as delivery men, Bazaar buyers, and entertainers walking to their venues, use the ferries. No other walkers are allowed on the ferries. @PTo transport immigrants, Ferry Landings do not need road access. Immigrants will cut across fields to get to the Ferry Landing. To transport other citizens, however, Ferry Landings do need road access. @L@LWith the @157Nile carving a path through the middle of their land, the ancient Egyptians employed all manners of boats to transport themselves and goods. To find out more about ancient Egyptian ship building, click @179here."
        }
    }
    
    message_game_concept_irrigation {
        id: 59,
        
        size [30, 28]
        title {
            text: "Irrigation",
        }
        content {
            text: "Water lifts and Irrigation Ditches bring the benefits of the Nile to a wider range of land. Irrigating farmland increases its fertility. @PTo bring the benefits of irrigation to a farm, run an Irrigation Ditch to within two spaces of it.  The effects of irrigation are not cumulative; as long as there is one Irrigation Ditch within two spaces of a farm, the farm is fully irrigated. @PFloodplain farms are at the water's level where Irrigation Ditches can be connected directly to the Nile.  Meadow farms, however, are not at the water's level.  To irrigate meadow farms, you must build a Water Lift. @PWater Lifts bring water up one level.  They can be built on land adjacent to a body of water or to the flood plain. For Water Lifts built adjacent to the flood plain, you must build an Irrigation Ditch running from the Nile to the front of the Water Lift to supply it with water. @PAttach an Irrigation Ditch to the back of the Water Lift to irrigate meadow farms.  Irrigation Ditches twist and turn around all objects that impede their path except for roads.  Irrigation Ditches automatically run under roads as needed. @PIncreasing the fertility of its land will increase the amount of food a farm yields.  Fertility has no effect on the length of the growing season. @PEven irrigated farms must still be built on arable land.  Irrigation can increase the fertility of land, but it cannot make infertile land fertile. @PThe entry on @45farming provides additional information. @L@LIn ancient Egypt, discovering irrigation techniques significantly increased the amount of arable land.  To find out more about irrigation, click @154here."
        }
    }
    
    message_building_weaver {
        id: 60,
        
        size [30, 28]
        title {
            text: "Weaver",
        }
        content {
            text: "Weavers turn flax into linen. Flax can be grown on @91Flax&Farms or imported from a @47trade&partner. Weavers require both road access and labor. They can store a small supply of flax on site to keep them working continuously in spite of minor supply disruptions. @PLinen is an important product in the city. It is essential to the embalming process, and @66Mortuaries need a supply of linen to function properly. Citizens also like to have a stock of linen in their homes for clothing.  @L@LTo learn more about linen's importance in ancient Egypt and the weaver's craft, click @398here."
        }
    }
    
    message_building_water_supply {
        id: 61,
        
        size [30, 28]
        title {
            text: "Water Supply",
        }
        content {
            text: "Water Supplies and water carriers provide clean @44drinking&water to the city's neighborhoods. Water from a Water Supply is one of the first demands citizens make of you as they seek to improve their @56housing. @PWater Supplies require both road access and labor, and must be placed on grassland, which indicates the presence of groundwater. You cannot place them in the desert. @POnce a Water Supply has what it needs to operate, it sends out a water carrier. The water carrier walks through your neighborhoods, distributing clean water to the housing he passes. It's a good idea to check in with your water carriers occasionally to make sure that your neighborhoods are well supplied with clean water. Use the @18water&overlay to see which of your houses are frequently passed by a water carrier. Water carriers are @42roaming&walkers.  @PWater carriers will work harder if their Water Supply has been improved. When the desirability of the surrounding area is high enough, the workers at the Water Supply will improve the building, and water carriers will circulate through the neighborhood more frequently.  @POnly housing needs water from Water Supplies, and people like to live nearby (see the entry on @56desirability for more on making a neighborhood attractive).  @L@LClick @156here to find out more about the challenges of providing clean drinking water to the ancient Egyptian populace."
        }
    }

    message_building_well {
        id: 62,
        
        size [30, 28]
        title {
            text: "Well",
        }
        content {
            text: "Wells are rudimentary sources of @44drinking&water. Only the poorest neighborhoods will be satisfied with Well access. For housing to develop into more stately structures, access to @61Water&Supplies is required. @PWells do not need road access, nor do they need employees. Wells must be placed on grassland, which indicates the presence of groundwater. They  have a slight positive effect on @56desirability. @PConsult the @18Water&Overlay to see which areas have access to Well water. @L@LFor more on ancient Egyptian wells, click @156here."
        }
    }

    message_building_dentist {
        id: 63,
        
        size [30, 28]
        title {
            text: "Dentist",
        }
        content {
            text: "Your wealthier citizens value the ability to eat solid foods, and they expect access to a nearby Dentist's office to preserve or replace their natural teeth. In a land where sand inevitably gets into the food supply, dentists never lack for work. Dentists increase the @56desirability of nearby housing, but have no effect on @53City&Health. @PUse the @18Health&Overlay to see the dentists working in your city. @L@LClick @158here to read about the role of dentists in ancient Egypt."
        }
    }

    message_building_physician {
        id: 64,
        
        size [30, 28]
        title {
            text: "Physician",
        }
        content {
            text: "Physicians help preserve good @53City&Health.  Their visits help to reduce the risk of disease. @PCitizens like having a Physician's office nearby, and @56housing&evolution is limited without them. @PPhysician's offices require labor and road access. @PA visit to the @26Overseer&of&Public&Health will help you assess physician coverage in the city. @L@LClick @160here to read more about Egyptian medical practices."
        }
    }

    message_building_apothecary {
        id: 65,
        
        size [30, 28]
        title {
            text: "Apothecary",
        }
        content {
            text: "Apothecaries are neighborhood pharmacies that employ herbalists. Herbalists remove from circulation any @53plagued&citizens they may meet in their journeys. Apothecaries are most important to reducing the risk of @53malaria. @PApothecaries require road access and labor to function properly. To track the paths of your herbalists, use the @18Health&Overlay.  You will see all the herbalists and Apothcaries in the city, plus see how much access each house has to an herbalist's services. @PCheck in with the @26Overseer&of&Public&Health for more information. @L@LTo find out more about ancient Egyptian pharmaceutical practices, click @159here."
        }
    }

    message_building_mortuary {
        id: 66,
        
        size [30, 28]
        title {
            text: "Mortuary",
        }
        content {
            text: "Embalmers at Mortuaries prepare the deceased for their journey to the afterlife. @PMortuaries increase @53City&Health by properly caring for the dead. Like most buildings, Mortuaries need both road access and labor. In addition, they need a supply of @60linen that is either manufactured in the city or imported from a @47trade&partner. Embalmers use linen to wrap the deceased bodies after the embalming process. @PAlthough citizens demand access to Mortuaries, they won't enjoy living near the structures. Mortuaries are renowned for their unpleasant odors. @PTo see where the Mortuaries are, use the @18Health&Overlay. You'll see embalmers caring for the dead and walking through your neighborhoods. Your @26Overseer&of&Public&Health provides valuable information regarding Mortuary services in your city. @L@LEmbalming was integral to ancient Egyptian belief in the afterlife.  Click @161here to find out more about this ancient practice."
        }
    }

    message_building_shrine_and_temple {
        id: 67,
        
        size [30, 28]
        title {
            text: "Shrine and Temple",
        }
        content {
            text: "You cannot appease the gods without Shrines and Temples. Both local deities and patron gods demand attention, and citizens expect access to religion. For more on the gods' effects on your city, see @51religion.  For information on the specific effects of each god's Temple Complex, choose: @L@P@350Temple&Complex&to&Osiris @P@351Temple&Complex&to&Ra @P@352Temple&Complex&to&Ptah @P@353Temple&Complex&to&Seth @P@354Temple&Complex&to&Bast @L@PShrines are small monuments dedicated to a specific god. They do not need direct road access, but do need to be within two spaces of a road to receive services from fire marshals and architects. They do not require labor and produce no walkers, hence they do not confer access to religion. Their main purpose is to appease the gods. @PTo provide places for people to worship, and to further appease the gods, build Temples. Temples require road access and employ a staff of priests. When a Temple is functioning, you will see priests bringing religion to your people. Like Shrines, Temples are dedicated to a specific god. @G73 @PBoth Temples and Shrines improve the @56property&values of the neighborhoods in which they are located. Shrines and Temples also contribute to the city's @35Culture&Rating.  @L@LReligion was at the center of ancient Egyptian life. To learn more about this important aspect of ancient Egyptian culture, click @399here."
        }
    }

    message_building_scribal_school {
        id: 68,
        
        size [30, 28]
        title {
            text: "Scribal School",
        }
        content {
            text: "Scribal Schools educate the city's well-to-do youth. @PSchools require road access and labor to function properly. They also require a supply of @97papyrus. When a school is functioning properly, teachers walk the streets tutoring students in their homes. Every time a teacher leaves a school to find his pupils, he brings some scrolls of papyrus with him so students can practice their hieroglyphs. Each Scribal School can store a small supply of papyrus on site. To keep classes in session, make sure the papyrus industry in your city is thriving or that you import enough from a @47trade&partner. @PYour @27Overseer&of&Learning knows how many Scribal Schools are operating in the city. The @18Education&Overlay shows you where all the Scribal Schools are and which houses have access to teachers. Scribal Schools also contribute to a city's @35Culture&rating. @L@LMany ancient Egyptians regarded schooling as the pathway to a sucessful future.  Click @163here to find out more about this ancient Egyptian institution."
        }
    }

    message_building_sun_temple {
        id: 69,
        
        size [30, 28]
        title {
            text: "Sun Temple",
        }
        content {
            text: "Sun Temples pay special honor to the Sun Cult that most pharaohs hold very dear. @PTo build a Sun Temple, you will need @95sandstone and @94wood, plus the services of the @363Carpenters'&Guild, @363Stonemasons'&Guild and @8Work&Camp. @PSun Temples start with a sandstone obelisk.  Before the obelisk can be built, adequate supplies of sandstone must be stored in the city's @4Storage&Yards.  Once there is enough sandstone, the Sun Temple can be placed.  Choose Sun Temple from the Religious Structures: Monuments list, and choose a location.  If you choose well, you will see a green footprint of the monument.  If any portion of this footprint shows a red diamond, some terrain feature prevents you from building the monument there.  Click to begin constructing the sandstone obelisk within the Sun Temple.   @PAfter the stone is placed, carpenters build scaffolding around the obelisk.  Then, stonemasons decorate the sides of the sandstone obelisk.  When they finish the obelisk, they begin work on the remainder of the Sun Temple.  First they build a Vestibule, and then a stone Wall.  After the Wall is complete, the stonemasons build the Fore Temple.  To complete these elements, stonemasons need several sledge loads of sandstone delivered by peasants.  While they are working on the Fore Temple, Wall and Vestibule, stonemasons install decorative tiles between the Walls. @POnce the Fore Temple is complete and all the tiles have been laid, the Sun Temple is finished. @PCheck in with the @369construction&foreman for construction updates. A visit to the @373Overseer&of&the&Monuments may also be helpful. @L@LRead about the history of Sun Temples and other monuments by clicking @396here."
        }
    }

    message_building_library {
        id: 70,
        
        size [30, 28]
        title {
            text: "Library",
        }
        content {
            text: "Sophisticated citizens require access to Libraries.  Libraries increase property value and contribute to the city's @35Culture&rating. @PLibraries would be useless buildings with empty racks without papyrus. Before you can build a Library, a supply of @97papyrus must be stored in the @4Storage&Yards. After the Library is built, it needs a store of papyrus on site to function properly. @PLibraries also need road access and labor to function. When the Library has all the supplies it needs, it sends a librarian through the local community. Each time a librarian leaves the Library, he takes papyrus with him to distribute literature to the populace. @PTo keep track of the number of Libraries in the city, visit your @27Overseer&of&Learning.  To see the specific locations of the Libraries, use the @18Education&Overlay. The overlay shows the Libraries, and you can follow the librarians as they go about their daily tasks. @L@LRead all about Ancient Egypt's literary tradition and its libraries by clicking @164here."
        }
    }

    message_building_booth {
        id: 71,
        
        size [30, 28]
        title {
            text: "Booth",
        }
        content {
            text: "Booths are the smallest, least expensive @49entertainment venues you can build. A Booth holds one stage that hosts jugglers, who amuse the crowd with acrobatics and gravity-defying tricks. @PBooths need a special kind of road access: they must be placed over an intersection, either a crossroads or a 'T'. Booths must also be fully staffed and have trained jugglers on hand. The staff helps control the crowds and attends to the needs of the juggler while the juggler entertains. Jugglers receive training at @75Juggler's&Schools, and can also take the stage at @72Bandstands and @73Pavilions. @PHouses need access to entertainment to @56evolve, and jugglers bring benefits to all the houses they pass. Having a Booth in the neighborhood also increases that neighborhood's desirability. Active Booths also contribute to the city's @35Culture&rating.  @PA visit to your @28Overseer&of&Diversions will tell you how many jugglers are working in the city.  The @18Entertainment&Overlay shows where jugglers are performing, and you can see the jugglers strolling though your streets. @L@LThe ancient Egyptians were juggling pioneers.  Click @169here to find out more."
        }
    }

    message_building_bandstand {
        id: 72,
        
        size [30, 28]
        title {
            text: "Bandstand",
        }
        content {
            text: "Bandstands are medium-sized venues that have two stages: one to host jugglers and the other to to feature performances by musicians.  The juggler's stage is in one corner of the venue, and the band plays on a second stage in another corner.   @PBandstands must be placed on an intersection, either a crossroads or a 'T'.  They need their own staff to attend to the performers' needs, plus need trained jugglers and musicians. Performers receive training at @75Training&Centers. @PHouses need access to entertainment to @56evolve, and jugglers and musicians bring benefits to all the houses they pass. Having a Bandstand in the neighborhood also increases that neighborhood's desirability. Active Bandstands also contribute to the city's @35Culture&Rating.  @PA visit to your @28Overseer&of&Diversions will tell you how many jugglers and musicians are working in the city.  The @18Entertainment&Overlay shows where these performers are working, and you can see them strolling though your streets. @L@LThe ancient Egyptians were accomplished musicians. Learn more by clicking @170here. Learn about ancient Egyptian juggling by clicking @169here."
        }
    }

    message_building_pavilion {
        id: 73,
        
        size [30, 28]
        title {
            text: "Pavilion",
        }
        content {
            text: "The largest of the entertainment venues, Pavilions have three stages: one for juggling shows, one for musical concerts and one for dance performances.  No citizen will complain about living next to a Pavilion. @PPavilions must be placed on an intersection, either a crossroads or a 'T'.  They need their own staff to attend to the performers' needs, plus need trained jugglers, musicians and dancers. Performers recieve training at @75Training&Centers. @PHouses need access to @49entertainment to @56evolve, and entertainers bring benefits to all the houses they pass. Having a Pavilion in the neighborhood also increases that neighborhood's desirability. Active Pavilions also contribute to the city's @35Culture&Rating.  @PA visit to your @28Overseer&of&Diversions will tell you how many jugglers, musicians and dancers are working in the city.  The @18Entertainment&Overlay shows where these performers are working, and you can see them strolling though your streets. @L@LCatch the latest ancient Egyptian dance craze by clicking @171here. Learn about their music by clicking @170here and their juggling practices by clicking @169here."
        }
    }

    message_building_senet_house {
        id: 74,
        
        size [30, 28]
        title {
            text: "Senet House",
        }
        content {
            text: "A Senet House offers a place for people to enjoy a relaxing game of senet, a contest that depicts the journey to the afterlife.  With frothy mugs of beer at their elbows, citizens while away the hours in each other's company and engage in a little friendly competition.   @PIn addition to workers and road access, a Senet House needs a supply of @96beer to serve to its patrons. @PCheck in with your @28Overseer&of&Diversions to find out how many Senet Houses are in the city. Use the @18Entertainment&Overlay to see which houses have access to a Senet House. @PPeople do not like living too near Senet Houses (click @56here for more on desirability).  The clientele tends to be loud and boisterous - especially the losers of high-stakes senet games. @L@LSenet was more than just a game. To find out more, click @172here."
        }
    }

    message_building_trading_centers {
        id: 75,
        
        size [30, 28]
        title {
            text: "Training Centers",
        }
        content {
            text: "To learn their craft, jugglers, dancers and musicians must train at a center. Each discipline has its own place of instruction: jugglers learn tricks at Jugglers' Schools, musicians study at Conservatories and dancers train at Dance Schools. @PEach of these buildings requires road access and its own staff. Once the entertainers complete their instruction, they proceed to the nearest venue needing their services. As the performers make their way to the venues, houses they pass receive access to their form of entertainment. @POnce the performers arrive at their venues, they put on a show for a certain number of days. Right-clicking on any entertainment venue will tell you which performers are entertaining crowds and how many more days their services will be enjoyed. The closer a Training Center is to a venue, the longer the show will run. Once a show's run is over, the performers return home. Unless new performers have been trained to take their places, the entertainment venue will be vacant and not provide diversion for your residents. @PYour residents won't mind living near a Jugglers' School. Their amusing antics are almost as much fun when they are practicing as they are when they are performing. No one likes living near Dance Schools or Conservatories, though. The performers come and go at all hours, and rehearsing musicians don't make the most pleasant sounds. @PTo watch entertainers moving from their schools to their venues, use the @18Entertainment&Overlay. @L@LThe Egyptians found many ways to entertain themselves.  Click @165here to find out more."
        }
    }

    message_building_courthouse {
        id: 76,
        
        size [30, 28]
        title {
            text: "Courthouse",
        }
        content {
            text: "Courthouses are versatile municipal structures. In addition to reducing @36crime in the city's neighborhoods, they also store a portion of the city's wealth. Citizens like the security that Courthouses bring and enjoy living near the stately structures. @PCourthouses need road access and labor before they can send out magistrates to patrol the city's streets. A magistrate's presence in a neighborhood reduces the chance that crime will break out there.  Magistrates are preventive measures only; if crime breaks out, the magistrate can do nothing to prevent the criminal from his rampage. @PA portion of the city's @48money is stored in the Courthouses. You won't be able to designate how much money is stored in each Courthouse.  Your @30Overseer&of&the&Treasury is much better equipped to handle this task and will calculate an appropriate amount.  @L@LCourthouses were busy places in ancient Egypt.  To find out more about ancient Egyptian law, click @183here."
        }
    }
    
    message_building_palace {
        id: 77,
        
        size [30, 28]
        title {
            text: "Palace",
        }
        content {
            text: "The city's Palace is the seat of power.  @PThe palace is a valuable resource in your city, and you should try to build one as soon as possible. You are only allowed one palace per city. Depending upon your rank and the city's stature, you can build a Village Palace, a Town Palace or a City Palace. @PA city must have a Palace in order to collect taxes. Your citizens will doubt your power until you establish a strong, centralized presence. You can also adjust the tax rate from the Palace. Right-click on the Palace, and use the scroll buttons at the top of the screen to adjust your tax rate. For more on taxes, click @48here. @PPalace vaults hold a portion of the city's funds. The screen that pops up when you right-click tells you exactly how much the building stores. See @48money for more on how funds are stored throughout your city. @PThe Palace also provides a thumbnail sketch of the status of your city. Hold the cursor over the building, and an update will appear detailing the city's tax rate, ratings and unemployment rate. @PIf your city is fortunate enough to be located in a @93gold-mining area, the Palace serves another vital function.  Gold ore is taken directly from the mines to the palace, where it is refined and processed into money.  The resulting debens are added directly to the city treasury.  Gold is never traded or taken anywhere except to a Palace. @PShould Pharaoh honor your city with a royal visit, he will lodge in the Palace. @PThe seat of government is one of the most beautiful and well-respected buildings in your city. People love to live nearby - some think it bolsters their own standing within the community.   @PThe Palace needs road access and a staff of workers to carry out its work. The Palace also needs access to groundwater in case of a visit from a royal personnage. Therefore, at least one part of the building must be placed over grassland.  @L@LLearn about ancient Egyptian government and bureaucracy by clicking @174here."
        }
    }

    message_building_mansion {
        id: 78,
        
        size [30, 28]
        title {
            text: "Mansion",
        }
        content {
            text: "Build a magnificent home in the city to cement your power and prestige. Your Mansion stores your family's wealth, and you will not be allowed to collect a @48salary until you have built a home for yourself. The city's residents want to make sure that you are a permanent fixture in the community before they allow you to draw a wage.  @PYour wage is set commensurate with your experience. If you feel you deserve more or less money, you can set your own salary level.  Right-click on the Mansion, and a screen appears that lists your current salary on a button. Click this button, and you will see a list of all the ranks in the Kingdom with their salary levels. Choose a new salary from this list, and you will be paid accordingly. Be forewarned, though: paying yourself more than you are worth will have a negative effect on your @35Kingdom&Rating. You can also set your personal salary by visiting your @30Overseer&of&the&Treasury. @PYour residence requires road access and a source of groundwater. Therefore, at least one part of the Mansion must be on grassland. Everyone wants to be your neighbor, so your home provides a considerable boost to nearby desirability. @PDepending on your rank and on your city's capabilities, you can build a Personal Mansion, a Family Mansion, or the ultra-luxurious Dynasty Mansion. @L@LPharaohs lived in colossal homes that dwarfed the homes of the working class.  To find out more about these impressive domiciles, click @175here."
        }
    }
    
    message_building_garden_plaze_statue {
        id: 79,
        
        size [30, 28]
        title {
            text: "Garden, Plaza and Statue",
        }
        content {
            text: "Plenty of food and services are all well and good, but  citizens will not truly love their homes unless you make their surroundings beautiful. Plazas, Gardens and Statues enhance a neighborhood's ambience and increase property values. None of the beautification structures require labor, and all may be built by selecting the appropriate button under beautification in the municipal structures list.  @PGardens are lovely spots for people to unwind after a hard day's work. The more land you allot to Gardens, the more lavish they become. Gardens do not need road access.   @PStatues remind your citizens of the glory of ancient Egypt. They come in three different sizes: small, medium and large. To build them, simply choose a size and find a nice spot. As you hold your cursor over a spot, press the 'R' button on your keyboard. While you hold down the button, a choice of four Statues will be presented, and they will rotate. When the statue you want faces the direction you desire, click. Statues do not need road access. @G72 @PPlazas are fancy @57roads. They can only be built on roads that citizens have paved. Citizens pave roads when their neighborhoods are sufficiently @56desirable, and Plazas increase this desirability even more. Building Plazas is much like building roads. Click the Plaza button, then click the paved road you want to cover with a tile. Plazas don't change the road's function or capacity in any way. You can cover large sections at a time by dragging the mouse cursor, but watch the cost. @L@LGardens were almost a necessity for ancient Egyptians. Click @176here to read about these lush environs and to learn about public art in Egypt."
        }
    }
    
    message_building_tax_collector {
        id: 80,
        
        size [30, 28]
        title {
            text: "Tax Collector",
        }
        content {
            text: "Tax collectors patrol the city's streets to make sure residents are paying their fair share. @PTax collectors work out of a Tax Collector's office, which needs road access and labor. In addition, the city must have a functioning @77Palace before the tax collector can perform his duty. @PA portion of the city's funds is stored within each Tax Collector's office.  @PSetting a tax rate can be a tricky business. You must balance the needs of the city's treasury with citizens' level of patience. People won't brook paying a high tax rate for too long and will not hesitate to leave your city in search of a more affordable situation. If a portion of the city's population is paying a high tax rate while another portion isn't paying any, @39City&Sentiment will plummet, which could result in @36crime. Visit your @30Overseer&of&the&Treasury and consult the entry on @48money for advice on setting a tax rate. @L@LThe ancient Egyptians paid tax to pharaoh to help fund the government.  Click @173here for more information on taxes in ancient Egypt."
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
    message_tutorial_clean_water {
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
            pos [0, 15]
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
            pos [0, 15]
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
            pos [0, 15]
        }
        content {
            text: "Begin by planning for areas of housing and industry.  By now you know what the people want, in addition to the basics of food and water.  You must provide some houses with pottery, beer, entertainment and access to religious services before you can think about higher education and trade."
        }
    }
    message_soldiers_and_forts {
        id: 245,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: " Soldiers and Forts",
            pos [0, 15]
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
            pos [0, 15]
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
            pos [0, 15]
        }
        content {
            text: "Trade on the Water @LTrade may also be conducted by river and sea, if any such water routes currently run to the city.  To open a water trade route, visit the World Map.  To trade along a water route, your city will also need a working Dock. @L@LFishing the Nile @LThe Nile is a plentiful source of fish, a popular food in Egypt.  What's more, a diet comprised of multiple types of foods leads to better health and happiness for your people.  To harvest this rich bounty, you'll need some fishing boats. @L@LBuilding Boats and Ships @LThe Shipwright builds combat ships and fishing boats.  Each boat must be supported by its own Wharf.  Whenever there is a Wharf in need of a vessel, the Shipwright will begin constructing one for it.  Without a waiting Wharf, the Shipwright will not build any ships.   @LAlthough a single Shipwright can supply all the vessels your city needs, multiple Shipwrights will allow you to replace lost vessels much more quickly.  The Shipwright doesn't need any materials to create fishing boats, but he will need a supply of wood to construct military vessels, such as warships and transport ships. @LMilitary vessels, trade ships and fishing boats are broad-beamed and deep-keeled to navigate the Nile and coastal waters. They are not made to sail very narrow channels, and indeed cannot travel up small streams or inlets.  Nothing will stop you from building Shipwrights, Docks or Wharves in such locations, but if you do so, boats cannot travel to or from these facilities, and they will not work. @LAs you scout the shore for suitable maritime sites, bear in mind that all ships need free passage between their port and their destination.  You cannot, for example, build a Fishing Wharf on an inland lake and expect its boats to reach the fishing grounds of the Nile, even if that lake is connected to the Nile by a small stream. @L@LMaking Bricks @LBricks are a somewhat less expensive building material, used in the creation of certain kinds of tombs.  To make bricks, you'll need a Brickworks, and supplies of clay and straw."
        }
    }
    message_the_finer_things_2 {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "The Finer Things",
            pos [0, 15]
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
    message_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Clean Water",
            pos [0, 15]
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
        id: 257,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Monuments and More!",
            pos [0, 15]
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
    message_tutorial_industry_2 {
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
        id: 279,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title { text: "Kingdom Road blocked" }
        content { text: "Recent construction blocked the @57Kingdom&road running through these lands.  Royal architects reopened this vital route...but they had to remove a building or two in the process!" }
    }
    
    message_wrath_of_ra {
        id: 280,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title { text: "Wrath of Ra" }
        video { text: "@23" }
        content { text: "Ra punishes your arrogance by severely lowering your reputation throughout the Kingdom. As you spurned the god, so shall other Egyptians belittle you." }
    }

    message_wrath_of_seth {
        id: 281,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title { text: "Wrath of Seth" }
        video { text: "@21" }
        content { text: "Your disregard for Seth prompts the god to destroy all of your ships!" }
    }

    message_wrath_of_seth_2 {
        id: 281,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title { text: "Wrath of Seth 2" }
        video { text: "@21" }
        content { text: "Your disregard for Seth prompts the god to destroy all of your ships!" }
    }

    message_the_world_map {
        id: 282,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "The World Map",
            pos [0, 15]
        }
        content {
            text: "The World Map shows the location of your own city, as well as other cities in the world.  Here you can pay to open up trade routes with any cities willing to trade.   @L@LOther Cities  @LCities who wish to engage in trade appear on the map in full color and fly a flag.  Cities that will not trade with your city are muted.  To set up a trade route, click on the city you wish to do business with.   @L@LImporting and Exporting @LOnce you set up a trade route, you'll still need to instruct the Overseer of Commerce as to which resources and commodities you wish to import or export.  You can never import and export the same item at the same time."
        }
    }
    message_tutorial_monuments {
        id: 283,
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monuments" }
        content {
            text: "With a supply of bricks, you're now ready to begin work on the sacred mastaba tomb.  Most monuments require both skilled and unskilled workers.   @L@LConstruction Guilds @LConstruction Guilds supply the skilled labor needed to erect monuments.  The mastaba is made entirely of bricks, and requires only Bricklayers' Guilds to build it.  You can employ as many Bricklayers' Guilds as your economy can support, but make sure you also have enough bricks being delivered to the construction site to keep them busy. @POnce the Bricklayers' Guild has adequate labor, it will dispatch bricklayers to the construction site, where they will wait for a delivery of bricks by unskilled peasant laborers. @L@LPeasant Labor @LOnce there are some bricklayers awaiting supplies at the monument site, gangs of peasant laborers will begin to haul loads of bricks to them.  Because these same laborers also must tend the fields on the flood plain, you may find that work on the monument slows down somewhat when the flood has receded and the peasants return to their fields.  You can construct additional Work Camps, so that any surplus laborers not needed to tend the fields may work on the monument year-round. @G75 @L@LBegin by clicking on the Religious Structures icon, then search for a suitable location in which to place this large building."
        }
    }
    message_the_finer_things {
        id: 284,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "The Finer Things",
            pos [0, 15]
        }
        content {
            text: "Temple Complexes @LAs devotion to their patron gods continues to grow, the Egyptian people demand bigger and bigger places of worship.  Most cities will want to erect a Temple Complex to their chosen god, so that they may fully partake of his or her benevolence.  Once built, the Temple Complex may be expanded through the addition of an Oracle and an Altar, each dedicated to other, lesser gods.  These gods, too, will impart certain benefits to the city.   @L@LJewelry @LWith a supply of gemstones, Jewelers in your city can fashion jewelry.  Jewelry is one type of valuable luxury good, which the higher social classes in the city demand.  @L@LLuxury Goods @LIn addition to locally made Jewelry, the Egyptian people prize certain other luxury goods, which are available only through importation.  A city needs access to more than one type of luxury good in order to become truly civilized.  @L@LQuarrying Stone @LTo quarry stone, a highly sought after building material, build a quarry next to a rock outcropping.  Quarrymen will deliver stone blocks, one at a time, to the Storage Yard.  Make sure to employ architects to ensure that quarries don't cave in!"
        }
    }
    message_innovations {
        id: 285,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Innovations",
            pos [0, 15]
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
        content { text: "placeholder - report this to Ken if it appears" }
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
