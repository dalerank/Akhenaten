log_info("akhenaten: messages config started")

game_messages_fr {
    message_potter_history {
        id: 1,

        size [30, 28]
        title { text: "Poterie" }
        advisor: ADVISOR_TRADE
        content {
            text: "Les poteries doivent être approvisionnées en argile pour fonctionner. Certaines cités peuvent fournir leur propre argile en construisant des @92puits&d'argile. D'autres doivent importer cet argile par l'intermédiaire d'un partenaire commercial (cliquez @47ici pour plus de détails concernant le commerce). @PLes charretiers transportent l'argile aux poteries depuis les puits d'argile, si la cité en possède, ou depuis un @4entrepôt. Le potier garde une réserve d'argile pour continuer à travailler si les livraisons sont interrompues. @PLes Poteries ont également besoin d'un accès à la route et à la main-d'oeuvre. Si les potiers manquent de main-d'oeuvre, ils peuvent continuer à travailler mais leur rendement est moindre. Lorsque le potier travaille, vous pouvez le voir façonner les blocs d'argile. Les charretiers amènent les poteries finies jusqu'à l'entrepôt ou la @473fabrique&de&lampes (les poteries et l'huile sont utilisées pour produire des lampes). @PCes poteries sont d'une importante valeur marchande pour une cité. Les poteries améliorent les @56logements. Veillez par conséquent à fournir régulièrement les habitants en poteries pour éviter que leur logement ne régresse. La demande ne diminue pas car les habitants remplacent continuellement leurs poteries abîmées ou trop anciennes. Reportez-vous à la rubrique @2Bazars pour savoir comment proposer des biens finis à vos concitoyens. @PLes poteries sont également intégrées à la construction des @478tombes&royales. Lorsqu'un fabricant de lampes remplit une poterie d'huile, elle devient une lampe puissante qui éclaire la voie pour les travailleurs funéraires. @PVous pouvez également importer ou exporter des poteries. Reportez-vous à la rubrique @47Commerce pour savoir comment ouvrir des routes commerciales. Si votre cité vend des poteries, veillez à satisfaire les besoins des habitants. Indiquez à votre @24chef&du&commerce la quantité de poteries qui doit être stockée dans l'entrepôt, ou demandez-lui de proposer une estimation.  @PLe bruit et la poussière qui émanent des ateliers de poterie nuisent au calme du quartier, ce qui fait fuir les habitants. @L@LCliquez @198ici pour en savoir plus sur l'art de la poterie dans l'Egypte ancienne."
        }
    }

    message_bazaar_history {
        id: 2,

        size [30, 28]
        title { text: "Bazar" }
        content {
            text: "Sans les bazars, les habitants ne peuvent pas avoir accès aux denrées alimentaires et aux produits stockés dans les @3greniers et les @4entrepôts. Seuls les bazars distribuent ces marchandises à la population. @PPour fonctionner correctement, les bazars ont besoin d'un accès à la route et de main-d'oeuvre. Si un bazar manque de main-d'oeuvre, il peut continuer à fonctionner, mais à un rendement inférieur. @PChaque bazar dispose de deux types d'acheteurs : l'un qui se charge d'acheter des biens à l'entrepôt, l'autre qui se charge d'acheter des denrées alimentaires auprès des greniers. Chaque acheteur a sa propre spécialité : l'acheteur du grenier ne peut pas acquérir les marchandises d'un entrepôt et vice versa. Chaque acheteur de bazar peut acheter plus d'un bien à la fois. Par exemple, un acheteur de bazar peut se rendre dans un grenier pour acheter des céréales et des grenades. En revanche, il ne peut acheter des céréales et des poteries car les poteries ne sont pas stockées dans un grenier.  @PUne fois les achats effectués, l'acheteur demande à ses assistants de ramener les marchandises au bazar. @PL'acheteur de bazar est un @42passant. Il passe ses journées entre le bazar, les greniers et les entrepôts de la cité. Il n'a pas besoin de traverser la cité pour aller chercher les biens et ne s'occupe que de trois marchandises à la fois. Si vous constatez qu'il reste immobile, il est probable que les marchandises à récupérer sont trop éloignées ou que les fournisseurs sont trop nombreux.  @PL'autre employé du bazar, le marchand du bazar, amène les articles rapportés par les acheteurs et les distribue dans les quartiers avoisinants. Lorsqu'un marchand passe à proximité d'une maison, il distribue aux occupants les marchandises dont ils ont besoin (s'il possède ces articles en stock). Il demande également aux habitants ce dont ils ont besoin pour améliorer leur logement et en informe les acheteurs. L'objectif principal est de remplacer l'équipement d'une maison pour éviter qu'elle ne régresse (voir la rubrique concernant l'@56attrait&du&logement). Lorsqu'une maison dispose d'un article, le marchand tente de fournir à ses occupants d'autres objets pour améliorer le logement. @PLe marchand du bazar est, quant à lui, un promeneur qui parcourt les rues de la cité pour subvenir aux besoins des habitants. Il ne suit aucun trajet déterminé. Si vous constatez qu'un quartier manque de marchandises, observez le trajet emprunté par le marchand. Il ne suit pas un chemin précis. Chaque fois qu'il rencontre une intersection, il doit décider du chemin qu'il va suivre, et il ne choisit pas toujours le même. Organisez soigneusement les routes de votre cité et installez des @358barrages&routiers pour contrôler les déplacements des marchands du bazar. Un bazar qui a atteint son stade le plus avancé (ses tentes sont remplacées par de petits bâtiments) envoie deux promeneurs dans les rues au lieu d'un.   @PVeillez à satisfaire les besoins élémentaires des habitants tels que la nourriture et la poterie, avant de leur proposer d'autres marchandises telles que la bière et la toile. Les acheteurs ne s'attarderont pas dans un entrepôt plein de toile si les habitants ont grand besoin de poteries. Lorsqu'un logement demande une certaine marchandise, veillez à l'approvisionner le plus régulièrement possible. N'oubliez pas qu'en évoluant, les habitations accueillent davantage de personnes et nécessitent par conséquent toujours plus de marchandises. Pour garantir un bon approvisionnement des différents quartiers, construisez plusieurs bazars. Faites un clic-info sur une maison pour connaître à tout moment les besoins de ses occupants.  @PConstruisez des greniers et des entrepôts près des bazars pour fournir aux habitants toutes les denrées nécessaires. Donnez à un grenier ou entrepôt des ordres spéciaux afin qu'il stocke uniquement les marchandises dont le bazar a besoin. @PSi vous souhaitez organiser davantage un bazar, cliquez sur le bouton 'Ordres spéciaux' pour afficher la liste des marchandises pouvant être stockées. Cliquez sur un article pour demander au bazar de l'acheter ou non. @PLes habitants apprécient la commodité offerte par les bazars, mais ils n'aiment pas habiter à proximité. Les bazars sont en effet des endroits bruyants et parfois nauséabonds, souvent fréquentés par des personnes peu recommandables.  @L@LCliquez @199ici pour retrouver l'ambiance des bazars égyptiens."
        }
    }

    message_building_granary {
        id: 3,

        size [30, 28]
        title { text: "Grenier" }
        content {
            text: "Les greniers stockent les denrées alimentaires de la cité. Les @2acheteurs&de&bazar prennent les marchandises du grenier pour les distribuer aux habitants. @PPour fonctionner, les greniers doivent disposer d'un accès à une route et à la main-d'oeuvre. Pour connaître le niveau d'un grenier, jetez un coup d'oeil à travers les panneaux de bois. Faites un clic-info sur un grenier pour connaître sa capacité de stockage. @PLes @45fermes&de&denrées&alimentaires, les @84quais, les @360fermes&d'élevage et les @359pavillons de chasse emploient des livreurs qui transportent les marchandises aux greniers. Nous vous conseillons de construire les greniers à proximité des producteurs de denrées alimentaires. Si un livreur doit parcourir un long trajet, il ne pourra pas revenir chercher les denrées alimentaires prêtes à être livrées, ce qui risque d'immobiliser le site de production.  @PLorsque tous les greniers sont pleins, les livreurs attendent qu'ils se vident un peu ou transportent les marchandises vers un @4entrepôt (si vous avez spécifié que l'entrepôt peut accueillir cette marchandise).  @PDonnez des ordres spéciaux aux greniers pour gérer la distribution des denrées alimentaires de votre cité. Faites un clic-info sur un bazar, puis cliquez sur le bouton Ordres spéciaux. Toutes les marchandises pouvant être stockées dans le grenier s'affichent. Cliquez sur une marchandise pour indiquer au grenier comment la traiter. Les instructions sont les suivantes : @L@LAccepter tout/Remplir. @LUtilisez l'instruction Remplir pour limiter la quantité d'un produit dans le grenier. Vous pouvez remplir le grenier au 1/4, à moitié ou au 3/4. Si vous ne souhaitez pas limiter la quantité stockée d'une denrée, choisissez l'option Accepter tout. Le grenier peut ainsi accueillir une même quantité de plusieurs denrées.  @L@LRefuser @LCliquez sur ce bouton afin que le grenier refuse certaines denrées. Le grenier n'acceptera plus aucune livraison de cette denrée particulière, mais les acheteurs de bazar et les autres greniers continueront à collecter la marchandise jusqu'à ce que leur approvisionnement soit épuisé. Si vous souhaitez exporter une denrée stockée dans un grenier, utilisez cette option afin que les livreurs se rendent dans un autre grenier en évitant le vôtre.  @L@LRemplir au maximum @LLorsqu'une marchandise est épuisée, vous devez demander aux livreurs de vous réapprovisionner. Les charretiers du grenier se rendront dans les autres greniers ou entrepôts et poursuivront leur recherche jusqu'à ce qu'ils remplissent les quotas. Vous pouvez réapprovisionner le grenier au 1/4, à moitié, au 3/4 ou totalement. Grâce à cette option, les greniers situés loin des producteurs de denrées alimentaires de la cité resteront approvisionnés. @L@LVider nourriture @LChoisissez cette option afin que les charretiers du grenier essaient de trouver un autre emplacement pour stocker la nourriture en attendant que le grenier soit épuisé. Le grenier interrompt tout approvisionnement d'une denrée qu'il essaie d'écouler. Utilisez cette option si vous avez projeté de détruire un grenier ou si vous souhaitez vider le grenier d'une denrée précise. @L@LBeaucoup d'habitants n'apprécient guère les greniers, poussiéreux et infestés de rongeurs. Ils préfèrent par conséquent éviter d'habiter à proximité. @L@LCliquez @5ici pour découvrir les greniers de l'Egypte ancienne."
        }
    }

    message_building_storage_yard {
        id: 4,

        size [30, 28]
        title { text: "Entrepôt" }
        content {
            text: "Les entrepôts sont les emplacements les mieux appropriés pour stocker des biens finis et les surplus de matières premières. Ils peuvent également stocker des denrées alimentaires si vous leur en avez donné l'ordre (voir la rubrique Ordres spéciaux ci-dessous) et servir de plate-forme pour les produits importés et exportés (voir la rubrique @47Commerce).  @PPour fonctionner correctement, les entrepôts ont besoin d'un accès à la route et de main-d'oeuvre. Pour être productif, l'entrepôt doit avoir un nombre suffisant d'employés. Si un entrepôt manque de main-d'oeuvre, il peut continuer à fonctionner, mais il risque de refuser certaines marchandises. @PChaque entrepôt est divisé en huit sections et peut contenir huit produits différents. Si chaque section ne peut contenir qu'un seul type de produit, un même produit peut être stocké dans plusieurs sections. La quantité de produit pouvant être stockée dépend de la taille de celui-ci. Si sa taille est importante, l'entrepôt ne pourra en abriter que quelques-uns. Par exemple, un entrepôt peut contenir plus de poteries que de blocs de pierre.  @PDe nombreux bâtiments doivent avoir accès aux entrepôts. Les @46structures&industrielles apportent leurs produits à l'entrepôt le plus proche et les acheteurs de bazar y choisissent les marchandises dont les habitants ont besoin. En contrepartie, les entrepôts fournissent aux industries voisines les matières premières et marchandises nécessaires. Bien que les livreurs des entrepôts puissent parcourir de grandes distances, évitez de les envoyer trop loin car les industries risquent de se retrouver au chômage technique en attendant leur cargaison. Veillez par conséquent à construire les entrepôts près des industries qui les utilisent. @PFaites un clic-info sur un entrepôt pour afficher la quantité de chaque bien pour l'entrepôt désigné et savoir si celui-ci peut encore en accepter. Si un entrepôt arrive à saturation pour un bien particulier, celui-ci apparaît en jaune. @PUtilisez les ordres spéciaux pour gérer le flux des marchandises qui arrivent dans l'entrepôt ou qui en partent. Cliquez sur le bouton Ordres spéciaux pour afficher la liste des marchandises distribuées aux habitants de votre cité. Cette liste peut atteindre plus d'une douzaine de produits. Utilisez les boutons de défilement situés en haut de l'écran pour afficher les autres produits disponibles. @PCliquez sur un article pour donner des instructions à l'entrepôt. Les instructions sont les suivantes : @L@LAccepter tout/Remplir.  @LUtilisez l'instruction Remplir pour limiter la quantité d'un produit dans l'entrepôt. Vous pouvez remplir l'entrepôt au 1/4, à moitié ou au 3/4. Si vous ne souhaitez pas limiter la quantité stockée d'une denrée, choisissez l'option Accepter tout. Utilisez cette option afin que l'entrepôt accueille une quantité égale de plusieurs denrées, ou si vous souhaitez stocker des denrées pour l'exportation.  @L@LRefuser @LCliquez sur ce bouton afin que l'entrepôt grenier refuse certaines denrées. L'entrepôt n'acceptera plus aucune livraison de cette denrée particulière, mais les acheteurs de bazar, les partenaires commerciaux et les industries de la cité continueront à collecter la marchandise jusqu'à ce qu'elle soit épuisée. Utilisez cette option afin que les livreurs se rendent dans un autre entrepôt en évitant le vôtre. A moins que vous ne l'ayez spécifié, les entrepôts n'acceptent pas de denrée alimentaire (la nourriture est stockée dans les greniers).  @L@LRemplir au maximum @LLorsqu'une marchandise est épuisée, vous devez demander aux livreurs de vous réapprovisionner. Les charretiers de l'entrepôt se rendront dans les autres entrepôts et poursuivront leur recherche jusqu'à ce qu'ils remplissent les quotas. Vous pouvez réapprovisionner l'entrepôt au 1/4, à moitié, au 3/4 ou totalement. Grâce à cette option, les entrepôts situés loin de la cité resteront approvisionnés. @L@LVider @LChoisissez cette option afin que les charretiers de l'entrepôt essaient de trouver un autre emplacement pour stocker la nourriture en attendant que l'entrepôt soit épuisé. Utilisez cette option si vous avez projeté de détruire un entrepôt ou si vous souhaitez vider l'entrepôt d'une denrée précise. @L@LLes entrepôts sont essentiels à la distribution des denrées aux habitants de votre cité. Les @2bazars s'approvisionnent directement auprès des entrepôts. Les entrepôts sont la clé du commerce. Les marchandises importées sont stockées dans l'entrepôt et les produits destinés à l'exportation attendent que les marchands étrangers viennent les récupérer. @L@LCliquez @6ici pour découvrir les entrepôts de l'Egypte ancienne."
        }
    }

    message_granary_history_2 {
        id: 5

        size [30, 20]
        title { text: "Grenier" }
        content {
            text: "Les travaux agricoles étant impossibles pendant la période des crues, les Egyptiens stockaient les denrées alimentaires dans des greniers afin de pouvoir se nourrir toute l'année. Outre les céréales et autres denrées alimentaires, les greniers renfermaient également de la farine.  @L@LL'architecture des greniers a évolué au fil des siècles. Pendant la période archaïque, les greniers avaient la forme d'un cône surmonté d'un toit. Ils étaient construits en bois et en briques, et les plus grands comportaient des escaliers pour atteindre l'entrée du grenier. Pendant le Moyen Empire, les greniers avaient la forme d'un rectangle surmonté d'un toit comportant plusieurs ouvertures. Les Egyptiens construisaient également un grenier spécialement destiné aux graines qui devaient être semées à la prochaine saison de croissance. Ces greniers ressemblaient à des trapèzes afin de les différencier des autres greniers et d'éviter ainsi que les graines ne soient consommées par mégarde. @L@LLa plupart des greniers étaient sous le contrôle du gouvernement. Ces greniers permettaient de nourrir les soldats, les ouvriers des chantiers de construction et les ouvriers non agricoles. Les riches familles égyptiennes possédaient parfois un grenier, tout comme les paysans plus modestes qui utilisaient un petit grenier pour stocker une part de la récolte."
        }
    }

    message_storage_yard_history {
        id: 6

        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Entrepôt", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "Situés à proximité du Nil et près des principales voies de communication, les entrepôts servaient à stocker les marchandises destinées au commerce. Les précipitations étant relativement rares en Egypte, ces entrepôts étaient bien souvent dépourvus de toit. Ils étaient gérés par des scribes qui répertoriaient avec précision toutes les marchandises stockées."
        }
    }

    message_keyboard_commands {
        id: 7

        size [30, 28]
        title { text: "Commandes du clavier" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "Plusieurs commandes du clavier sont disponibles pour jouer à Pharaon. Les commandes sont les suivantes : @L@LTouche    Fonction @LA      Ordonne au navire de guerre sélectionné @Pd'attaquer tous les ennemis. @L@LC      Affiche l'option Criminalité de la carte des @Prisques ou ordonne à la compagnie de @Pconducteurs de char sélectionnée de @Pcharger. @L@LD      Affiche l'option Dégâts de la carte des @Prisques. @L@LE      Ordonne au transporteur sélectionné @Pd'échapper à l'ennemi. @L@PAffiche la carte des ressources en eau. @L@LF      Affiche l'option Incendies de la carte des @Prisques ou ordonne à la compagnie @Psélectionnée de rejoindre son fort. @L@LH      Masque un terrain de falaise. @L@P       Ordonne au bateau sélectionné de @Pmaintenir sa position. @L@LI       Affiche la Carte des impôts @L@LL      Centre la vue sur une nouvelle compagnie @Pmilitaire chaque fois que vous appuyez sur @Pcette touche.  @L@P      Lorsqu'une compagnie est sélectionnée @Pet que vous appuyez sur la touche 'L', la @Pcompagnie reçoit l'ordre de se déplacer @Pen formation espacée.  @L@LM      Lorsque vous sélectionnez un monument @Pparmi la liste des bâtiments, son @P'empreinte', apparaît au bout de votre @Pcurseur afin de vous aider à définir @Pl'espace nécessaire à la construction de ce @Pmonument. Maintenez la touche 'M' @Penfoncée pour fixer 'l'empreinte' du @Pmonument à l'endroit voulu. Vous pourrez @Painsi faire pivoter la vue de votre cité @Psans déplacer le monument. Relâchez la @Ptouche 'M' pour retrouver 'l'empreinte' au @Pbout de votre curseur ou cliquez sur @Pl'emplacement prévu pour fixer le @Pmonument.  @L@P      Lorsqu'une compagnie est sélectionnée @Pet que vous appuyez sur la touche 'M', la @Pcompagnie reçoit l'ordre d'effectuer un @Pbalayage. @L@LN      Ordonne à la compagnie ou au navire de @Pguerre sélectionné d'attaquer l'ennemi le @Pplus proche. @L@LP      Interrompt momentanément le déroulement @Pde la partie. Lorsque la partie est en mode @Ppause, il vous est impossible de construire @Pquoi que ce soit. @L@LR      Lorsque vous placez une statue, un corps @Pde garde ou un ensemble de temples, la @Ptouche 'R' vous permet de faire pivoter @Pl'orientation de la structure de 45 degrés @Pdans le sens des aiguilles d'une montre, @Pce qui vous permet entre autres de voir @Pune statue sous différents angles.  @L@P      Lorsqu'une compagnie militaire est @Psélectionnée et que vous appuyez sur la @Ptouche 'R', la compagnie reçoit l'ordre @Pde modifier sa direction (de pivoter). @PCette touche transmet également l'ordre @Pau transporteur ou au navire de guerre @Psélectionné de rejoindre la fabrique de @Pbateaux pour réparation. @L@LT      Affiche l'option Problèmes de la @Pcarte des risques.  @L@PLorsqu'une compagnie militaire est @Psélectionnée et que vous appuyez sur la @Ptouche 'T', la compagnie reçoit l'ordre @Pde se placer en formation serrée. @L@LW      Diminue la vitesse du jeu par incrément de @P10 pour cent. @L@P     Lorsqu'un navire de guerre ou un @Ptransporteur est sélectionné et que vous @Pappuyez sur la touche 'W', celui-ci reçoit @Pl'ordre de rejoindre son quai d'origine. @L@LX      Augmente la vitesse du jeu par incrément de @P10 pour cent. @L@LY      Affiche les risques : carte de la malaria @L@LZ      Affiche les risques : carte des maladies @L@LBarre d'espace      Appuyez sur la barre d'espace @Ppour basculer entre la dernière carte @Psélectionnée et la vue normale de la cité. @L@LEchap      Quitte le jeu. @L@LTAB    Chef de la main-d'oeuvre @L@L1      Chef militaire @L@L2      Chef politique @L@L3      Chef des niveaux @L@L4      Chef du commerce @L@L5      Chef de la nourriture @L@L6      Chef de l'hygiène @L@L7      Chef de l'éducation @L@L8      Chef des loisirs @L@L9      Chef des temples @L@L0      Chef des finances @L@L)      Responsable @L@L=      (signe égal) Chef des monuments @L@LCTRL+F1 @PCrée un signet F1 à l'emplacement actuel @L@LCTRL+F2 @PCrée un signet F2 à l'emplacement actuel @L@LCTRL+F3 @PCrée un signet F3 à l'emplacement actuel @L@LF1     Passe au signet F1 @L@LF2     Passe au signet F2 @L@LF3     Passe au signet F3 @L@LF6     Passe en mode fenêtre @L@LF7     Sélectionne une résolution de 640x480 @L@LF8     Sélectionne une résolution de 800x600 @L@LF9     Sélectionne une résolution de 1024x768"
        }
    }

    message_work_camp_history {
        id: 8
        
        size [30, 28]
        title { text: "Chantier" }
        content {
            text: "Les paysans attendent sur des chantiers d'être envoyés sur une @45ferme&des&plaines&inondables ou un @370monument. Pendant la saison de croissance, ces paysans s'occupent des travaux agricoles. Lorsque l'inondation survient, tout le monde part travailler à la construction du monument. Si aucun monument n'est en cours de construction pendant la période des crues, les ouvriers passent leur temps en jouant au senet dans la taverne de jeux. Si votre cité manque de chantiers par rapport au nombre de fermes sur les plaines inondables, l'inondation entraîne un rythme de travail différent. @PLes chantiers ont besoin d'un accès à la route et de main-d'oeuvre. Pour éviter aux paysans de longs trajets, construisez les chantiers près des fermes et des monuments. Leur périmètre d'action est en effet limité en raison des lourdes charges qu'ils doivent transporter. Plus vous construisez de chantiers, plus les monuments seront érigés rapidement car la main-d'oeuvre disponible sera plus importante pendant la saison de croissance. @PLa proximité du chantier détermine le nombre de fermes dont il peut s'occuper. Un chantier opérationnel fournit un ouvrier par semaine (soit quatre par mois). Cet ouvrier se rend à la ferme la plus proche où il y travaillera pendant six mois.  @PAu bout de trois mois, les employés du chantier préparent un autre ouvrier pour continuer les travaux dans la ferme (n'oubliez pas que dans la plupart des régions la période de croissance dure neuf mois). Si un chantier s'occupe d'un grand nombre de fermes, certaines de ces fermes risquent de manquer de main-d'oeuvre, ce qui ralentira la production. @PVous pouvez gérer plusieurs fermes avec un ou deux chantiers, mais ces fermes n'atteindront pas leur rendement optimal, et les ouvriers ne seront pas disponibles pour participer à la construction du monument pendant la saison des crues.  @PPour travailler sans interruption, les ouvriers d'un chantier ne doivent s'occuper que de cinq à six fermes en même temps, ce qui leur permet néanmoins d'envoyer des paysans sur le site de construction du monument. Vous pouvez rajouter d'autres chantiers pour faciliter la tâche des ouvriers et envoyer davantage de personnes sur le site de construction du monument pendant la saison de croissance. @L@LCliquez @155ici pour savoir comment travaillaient les Egyptiens à l'époque des pharaons."
        }
    }

    message_frequently_asked_questions {
        id: 9
        
        size [30, 28]
        title { text: "  Questions les plus fréquemment posées" }
        content {
            text: "Argent @PQ: Je veux que ma cité s'enrichisse. Que dois-je faire pour remplir les coffres ? @PR: La solution la plus simple est de veiller à ce que la cité gagne plus d'argent qu'elle n'en dépense.  @PVérifiez que la plupart des résidents de la cité payent leurs impôts, puis définissez un taux d'imposition supérieur pour faire augmenter le niveau d'argent dans vos coffres. Ce niveau, cependant, risque de ne pas suffire à compenser l'@39opinion défavorable qu'entraîne généralement une augmentation des impôts. Par conséquent, commencez le @47commerce le plus rapidement possible et exportez le plus de biens possible (consultez la @32mappemonde pour voir où en sont les échanges commerciaux de la cité).  @PLa réduction des dépenses d'une cité permet de faire des économies. Par conséquent, soyez pondéré lors de la construction de la cité, car si les structures coûtent elles-mêmes cher, vous devez également prendre en compte l'argent nécessaire à la rémunération des employés, ainsi que le coût des services et des logements. Une cité trop rapidement construite pourrait avoir pour résultat un coût des salaires et des services auxiliaires élevé.  @L@PQ: Pourquoi ma cité ne peut-elle pas percevoir d'impôts ? @PR: Assurez-vous que vous avez bien construit un palais, car les cités ne peuvent percevoir des impôts que si elles en possèdent un.  @L@PQ: Je travaille du mieux que je peux, mais je n'ai encore perçu aucune rémunération. Que dois-je faire d'autre ? @PR: Cette plainte est courante. Dans Pharaon, vous ne pouvez percevoir un salaire tant que vous n'avez pas construit de demeure luxueuse.  @L@PQ: Comment puis-je payer mon tribut ? Que se passera-t-il si je ne le paye pas ? @PR: Si vos coffres sont pleins, votre tribut sera automatiquement prélevé à la fin de l'année. Par conséquent, vous devez vérifier à chaque fin d'année que vos coffres sont pleins. Si ceux-ci sont vides, vous ne pourrez payer votre tribut et le @35niveau&du&royaume chutera. Si, l'année suivante, vous n'êtes toujours pas en situation de le payer, le niveau du royaume chutera un peu plus. Si cette situation se poursuit, des pénalités plus sévères vous seront infligées. Analysez vos @48dettes. @L@LPiétons @PQ: L'un de mes entrepôts, greniers ou fabriques crée des piétons qui disparaissent dès qu'ils ont quitté le bâtiment. Qu'est-ce qui ne va pas ?  @PR: Ces piétons ne peuvent pas atteindre leur destination. Votre réseau routier doit être incomplet ou bien deux routes sont adjacentes au bâtiment, l'une menant à une destination appropriée, l'autre non. Les piétons ne pouvant atteindre leur destination se sentent si frustrés qu'ils se volatilisent. Le bâtiment qui les abrite continue, quant à lui, de créer des piétons dans l'espoir que ceux-ci réussiront là où les autres ont échoué. Reportez-vous à l'entrée d'aide relative aux @57routes, puis consultez la section sur les bâtiments sur deux routes. @L@PQ: Comme se fait-il qu'un bâtiment nécessitant de la main-d'oeuvre ne puisse en trouver ? @PR: Vous avez dû construire un @358barrage&routier trop près du bâtiment. Observez le bâtiment pendant un instant, puis vérifiez que ses employés se dirigent dans la bonne direction, car, en raison du barrage routier, il arrive parfois que ceux-ci empruntent une direction contraire à leur destination. En outre, ceci est particulièrement vexant pour les employés qui essaient d'accéder à ces mêmes bâtiments. En effet, les bâtiments qui les emploient supposent qu'ils peuvent y avoir accès, alors que le barrage routier empêche tout piéton d'atteindre le pôle d'activités. Replacez le barrage routier un espace plus loin.  @L@LReligion @PQ: J'aimerais organiser une fête, mais je n'y suis pas autorisé. Pourquoi ? @PR: Il peut y avoir plusieurs raisons à cela. Votre cité possède-t-elle une place des fêtes ? Si vous n'avez pas de place des fêtes, vous ne pourrez pas organiser de fête. Avez-vous déjà réalisé deux fêtes au cours des 12 derniers mois? Une cité ne peut organiser que deux fêtes dans l'année. Si vous prévoyez une grande fête, assurez-vous que vous avez suffisamment de bière en stock pour faire face à l'événement. En dernier lieu, vérifiez les coffres de la cité. Si la cité ne peut faire face aux dépenses engendrées par une fête, aucune fête ne pourra être organisée. @L@PQ: Le dieu protecteur de ma cité ne cesse de me faire des histoires. Que dois-je faire pour l'apaiser ? @PR: Le dieu protecteur d'une cité exige plus d'attention qu'une divinité locale. Vérifiez que vous avez construit plus de temples et de sanctuaires pour le dieu protecteur que pour les autres dieux de la cité et prévoyez de construire un ensemble de temples en l'honneur de ce dieu protecteur.  @L@LLoisirs @PQ: Je ne trouve pas d'emplacement approprié pour placer ce lieu de loisirs. Quel est le problème ? @PR: A l'exception des tavernes de jeux, les lieux de loisirs doivent être placés à une intersection en ' T ' ou à un carrefour. De plus, un espace doit être dégagé autour de l'intersection pour accueillir les lieux de loisirs.  @L@PQ: Je dispose de plusieurs lieux de loisirs dans la cité, mais je ne vois aucun joueur. Pourquoi ? @PR: Vérifiez que votre cité possède bien des centres d'entraînement. Les élèves doivent d'abord s'exercer avant de pouvoir divertir les masses.  @L@PQ: Pourquoi ma taverne de jeux ne fonctionne-t-elle pas ?  @PR: La réponse, c'est la bière. Vérifiez que la taverne de jeux a suffisamment de bière. @L@LAgriculture @PQ: Pourquoi les fermes des plaines inondables n'ont-elles aucune récolte ?  @PR: Assurez-vous qu'un chantier se trouve à proximité des fermes, car ce sont les ouvriers de ce chantier qui ont la charge de labourer le sol de ces fermes.  @L@PQ: Combien de fermes situées sur les plaines inondables un chantier peut-il prendre en charge ? @PR: Cela dépend. Consultez l'entrée de l'aide sur les @8chantiers pour de plus amples informations. @L@PQ: J'ai construit un quai, mais aucun bateau n'y est accosté. Pourquoi ? @PR: Les bateaux de pêche étant construits par une fabrique de bateaux, vérifiez qu'une telle fabrique est en activité dans la cité.  @L@LStockage et distribution @PQ: Les bazars sont à court de biens et de denrées alimentaires. Que puis-je faire pour avoir des étagères bien fournies? @PR: Vérifiez que vous avez construit un grenier et un entrepôt près du bazar. Si un acheteur de bazar doit faire un long trajet pour s'approvisionner, il y a de fortes chances pour que le bazar se retrouve à court de produits pendant cet intervalle. Utilisez les ordres spécifiques au grenier et à l'entrepôt pour que leurs stocks soient toujours pleins.  @L@PQ: Comment puis-je utiliser mes entrepôts plus efficacement ?  @PR: Pour une utilisation optimale des @4entrepôts, placez-les de manière réfléchie dans la cité et utilisez les ordres spéciaux à bon escient. Les entrepôts doivent être placés près de bâtiments, tels des bazars, des docks, des sites de construction de monuments et des industries, qui ont besoin de stocker des produits. Utilisez les ordres spécifiques à l'entrepôt pour vérifier que les marchandises stockées sont celles dont les bâtiments situés à proximité ont besoin. Les entrepôts doivent également être situés près des structures industrielles pour réduire le temps que les charretiers passent en transit. Si le charretier doit effectuer un long trajet pour livrer son chargement, son industrie risque d'être à court de matières premières en son absence. @L@LMonuments @PQ: Que puis-je faire pour accélérer la procédure de construction d'un monument ?  @PR: Construisez des chantiers, puis placez près du site les guildes de construction nécessaires ainsi que les entrepôts acceptant uniquement les matériaux de construction. Si votre cité peut produire ses propres matériaux de construction, vérifiez que vous disposez de plusieurs carrières et briqueteries pour garder les entrepôts pleins. Vérifiez également que la cité dispose d'un accès au bois afin que la guilde de menuisiers puisse construire des rampes et des échafaudages. Importez autant d'articles que vous le pouvez de vos partenaires commerciaux si votre cité ne peut produire les matières premières nécessaires. Si la construction d'un monument est ralentie pour une raison quelconque, consultez le contremaître en cliquant avec le bouton droit de la souris sur le site de construction pour connaître les raisons de ce retard. Par conséquent, si vous possédez plusieurs sites de construction dans la cité, les paysans et les ouvriers risquent de ne rien faire du tout, ne sachant sur quel site travailler.  @L@PQ: J'ai besoin d'une ressource particulière pour construire un monument, mais ma cité ne peut la produire et aucun partenaire commercial ne m'en propose. Les créateurs des missions ont-ils oublié quelque chose ? @PR: Dans certaines missions, la route commerciale dont vous avez besoin devient disponible uniquement lorsque les autres requêtes des cités (particulièrement les requêtes relatives à une aide militaire) sont satisfaites. Si vous ignorez la première requête, une seconde vous sera normalement proposée un peu plus tard et son acceptation vous permettra alors d'ouvrir la route commerciale dont vous avez besoin. Si vous continuez à ignorer ces requêtes, vous pouvez perdre la mission. Chaque mission dispose de tous les produits de base nécessaires... mais vous devez parfois travailler pour les obtenir et le succès, de plus, n'est pas toujours garanti. @L@LCommerce @PQ: J'ai ouvert une route commerciale, mais ma cité ne réalise aucune importation ou exportation. Comment puis-je lancer le commerce ?  @PR: Consultez votre chef du commerce et dites-lui quels sont les produits à vendre ou à acheter. En outre, assurez-vous que votre cité dispose d'un entrepôt et d'un dock si votre partenaire commercial doit venir par voie maritime. @L@PQ: J'essaie d'importer de la nourriture. Pour ce faire, j'ai ouvert une route commerciale et demandé au chef du commerce d'en importer, mais aucune nourriture n'arrive. Le peuple est en colère. Que puis-je faire ? @L@PR: Vérifiez que vos entrepôts sont prêts à accepter la nourriture que vous essayez d'importer. En effet, les entrepôts sont configurés par défaut pour ne pas accepter de nourriture.  L@PQ: J'ai laissé mon @24chef&du&commerce décider de la quantité des biens commercialisables à garder dans les entrepôts. Comment puis-je savoir s'il a pris la bonne décision ? @PR: Lorsque vous demandez à votre chef du commerce de prendre en charge le commerce, il prend en considération la taille de la population de la cité, les industries que celle-ci possède et les monuments qui sont en cours de construction. Après avoir analysé ces différents facteurs, il effectue une évaluation des besoins de votre cité. Pour connaître ses recommandations, cliquez sur les boutons des denrées. Lorsque le bouton qui vous permet de définir les niveaux apparaît, la quantité affichée par défaut correspond à la quantité recommandée par le chef du commerce pour les entrepôts.  @L@LLogement @PQ: Les terrains constructibles que je délimite disparaissent au fur et à mesure. Que se passe-t-il ? @PR: Les terrains constructibles doivent être délimités à moins de deux espaces de la route. Dans le cas contraire, ces terrains disparaîtront. De plus, les émigrants doivent pouvoir atteindre leurs logements. Vérifiez que vous avez réalisé un accès pour que les émigrants entrant et quittant la cité (la @57route&du&royaume) puissent atteindre vos terrains constructibles."
        }
    }

    message_table_of_contents {
        id: 10
        
        size [30, 28]
        image { id: 47, pos [15, 15] }
        title { text: "Table des matières" }
        subtitle { text: "Cliquez sur une rubrique pour afficher l'aide correspondante" }
        content {
            text: " @9Questions&les&plus&fréquemment&posées @L@LRubriques d'aide @L@L@492Abou&Simbel @L@88Académie @L@39Accroissement&démographique @L@17Affichage&de&la&date @L@16Affichage&de&la&population @L@15Affichage&de&l'argent @L@45Agriculture (voir également la rubrique consacrée aux exploitations) @L@81Architecte @L@48Argent @L@60Atelier&de&tissage @L@56Attrait @L@L@358Barrage&routier @L@2Bazar @L@70Bibliothèque @L@488Bibliothèque&d'Alexandrie @L@94Bois @L@33Boutons&de&construction @L@96Brasserie @L@364Briqueterie @L@L@490Caesareum @L@95Carrière @L@95Carrière&de&calcaire @L@95Carrière&de&granit @L@95Carrière&de&grès @L@95Carrière&de&pierre @L@18Cartes @L@355Caserne&de&pompiers @L@88Centre&de&recrutement @L@75Centre&d'entraînement @L@75Centres&d'entraînement (loisirs) @L@8Chantier @L@20Chef&de&la&main-d'oeuvre @L@25Chef&de&la&nourriture @L@27Chef&de&l'éducation @L@26Chef&de&l'hygiène @L@30Chef&des&finances @L@28Chef&des&loisirs @L@373Chef&des&monuments @L@23Chef&des&niveaux @L@29Chef&des&temples @L@24Chef&du&commerce @L@21Chef&militaire @L@22Chef&politique @L@7Commandes&du&clavier @L@47Commerce @L@37Compagnies @L@370Construction&de&monuments @L@369Contremaître @L@85Corps&de&garde @L@36Criminalité @L@L@78Demeure @L@63Dentiste @L@48Dettes @L@83Dock @L@L@44Eau&potable @L@68Ecole&de&scribes @L@50Education @L@43Emploi @L@354Ensemble&de&temples&dédié&à&Bastet @L@350Ensemble&de&temples&dédié&à&Osiris @L@352Ensemble&de&temples&dédié&à&Ptah @L@353Ensemble&de&temples&dédié&à&Seth @L@4Entrepôt @L@71Etal @L@89Exploitation&de&céréales @L@90Exploitation&de&grenades @L@91Exploitation&de&henné @L@90Exploitation&de&laitues @L@91Exploitation&de&lin @L@90Exploitation&de&pois&chiches @L@91Exploitation&d'orge @L@L@98Fabrique&d'armes @L@82Fabrique&de&bateaux @L@98Fabrique&de&chars @L@473Fabrique&de&lampes @L@97Fabrique&de&papyrus @L@470Fabrique&de&peinture @L@360Ferme&d'élevage @L@393Fêtes @L@494Fléaux @L@37Fort @L@L@3Grenier @L@52Guerre @L@58Gués @L@363Guilde&des&artisans @L@363Guildes&de&constructeurs @L@363Guilde&des&maçons @L@363Guilde&des&menuisiers @L@363Guilde&des&tailleurs&de&pierre @L@L@53Hygiène @L@L@46Industrie @L@59Irrigation @L@L@79Jardin @L@L@72Kiosque @L@L@56Logement @L@49Loisirs @L@L@32Mappemonde @L@371Mastaba @L@368Mausolée @L@64Médecin @L@13Menu&Aide @L@14Menu&Chefs @L@11Menu&Fichier @L@12Menu&Options @L@34Messages @L@93Mine&de&cuivre @L@361Mine&de&pierres&précieuses @L@93Mine&d'or @L@85Mur @L@L@58Navette @L@365Navire&de&guerre @L@35Niveau&architectural @L@35Niveau&de&culture @L@35Niveau&de&prospérité @L@35Niveau&du&royaume @L@35Niveaux @L@45Nourriture @L@L@372Obélisque @L@374Offrandes&funéraires @L@39Opinion @L@19Option&Basculer&de&l'interface @L@87Ordres&à&la&compagnie @L@4Ordres&spéciaux&à&l'entrepôt @L@2Ordres&spéciaux&du&bazar @L@3Ordres&spéciaux&du&grenier @L@99Orfèvrerie @L@40Ouvriers @L@L@77Palais @L@76Palais&de&justice @L@73Pavillon @L@359Pavillon&de&chasse @L@80Percepteur @L@489Phare&de&Pharos @L@65Pharmacie @L@42Piétons @L@477Pilleurs&de&tombes @L@366Place&des&fêtes @L@79Plaza @L@61Point&d'eau @L@86Poste&de&police @L@1Poterie @L@62Puits @L@92Puits&d'argile @L@375Pyramide&à&degrés @L@55Pyramide&en&briques @L@54Pyramide&penchée @L@L@84Quai @L@356Quai&de&navires&de&guerre @L@357Quai&de&transporteurs @L@L@51Religion @L@31Responsable @L@94Roseaux @L@57Route&du&royaume @L@57Routes @L@L@66Salle&des&embaumeurs @L@67Sanctuaire @L@41Scribes @L@362Sphinx @L@79Statue @L@85Structures&défensives @L@L@74Taverne&de&jeux @L@67Temple @L@69Temple&solaire @L@478Tombes&royales @L@85Tour @L@367Transporteur @L@48Tribut @L@L@38Vraie&pyramide @L@L@479Zoo @L@LHistoire @L@L@493Abou&Simbel @L@150Agriculture @L@190Argile @L@184Armée @L@196Armes @L@197Articles&de&luxe @L@472Artisans @L@396Autres&monuments @L@L@380Bastet,&Isis&et&Hathor @L@179Bateaux&et&fabrication&de&bateaux @L@199Bazar @L@481Bibliothèque&d'Alexandrie @L@164Bibliothèque&et&littérature @L@194Bière @L@390Briques @L@L@482Caesareum @L@193Carrières @L@185Céréales&et&orge @L@383Chasse @L@177Commerce @L@L@171Danse @L@175Demeure&du&pharaon @L@158Dentisterie @L@L@163Ecole&et&éducation @L@161Embaumement @L@176Embellissements @L@166Enfants @L@181Ennemis @L@6Entrepôt @L@L@195Fabrication&de&papyrus @L@186Ferme&d'élevage&et&de&pêche @L@393Fêtes @L@495Fléaux @L@187Fruits&et&légumes @L@L@5Grenier @L@L@469Henné @L@476Huile @L@L@388Immigration @L@173Impôts&et&argent @L@151Industrie @L@154Irrigation @L@L@176Jardins&et&embellissements @L@169Jonglerie @L@L@474Lampes @L@189Lin @L@152Logement @L@183Loi @L@165Loisirs @L@L@386Maçons @L@155Main-d'oeuvre @L@381Malaria @L@394Mastaba @L@160Médecine @L@389Menuisiers @L@191Mines&d'or&et&de&cuivre @L@170Musique @L@L@157Nil @L@L@397Obélisque @L@395Offrandes&funéraires @L@382Orfèvrerie @L@376Osiris,&Sebek&et&Min @L@L@487Phare&de&Pharos @L@159Pharmacie @L@174Politique&et&bureaucratie @L@167Population @L@198Poterie @L@384Prêtres @L@378Ptah,&Amon&et&Thot @L@156Puits&et&point&d'eau @L@392Pyramides @L@L@377Rê,&Maât&et&Horus @L@399Religion @L@188Roseaux @L@153Routes @L@L@162Sanctuaire&et&temple @L@387Scribes @L@172Senet @L@379Seth,&Anubis&et&Sekhmet @L@168Société @L@391Sphinx @L@182Structures&défensives @L@L@385Tailleurs&de&pierre @L@398Toile&et&tissage @L@L@192Utilisation&du&bois @L@L@475Vallée&des&rois @L@L@480Zoo"
        }
    }
    
    message_file_menu {
        id: 11
        
        size [30, 28]
        title { text: "Menu Fichier" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "A partir du menu Fichier, vous pouvez commencer une nouvelle partie, rejouer la mission, charger une partie précédente, enregistrer la partie, supprimer une partie enregistrée et quitter Pharaon."
        }
    }
    
    message_optons_menu {
        id: 12
        
        size [30, 28]
        title { text: "Menu Options" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "Utilisez le menu Options pour modifier la configuration audio et vidéo de Pharaon. Utilisez l'option Affichage pour régler la taille de votre écran et l'option Son pour régler le volume sonore de la voix et de la musique. Le paramètre Vitesse vous permet de spécifier la vitesse à laquelle le temps s'écoule dans Pharaon. Utilisez l'option Cités pour choisir le type de noms des cités (classique ou égyptien). Vous êtes sans doute déjà familiarisé avec les noms classiques, mais les noms égyptiens ajoutent une certaine authenticité au jeu. @PPour configurer le mode de réception des messages pendant le jeu, ajustez les paramètres des info-bulles. Les messages reçus s'affichent automatiquement dans une fenêtre. Lorsque la fenêtre s'ouvre, elle interrompt le jeu qui reprend dès que vous la refermez. Les paramètres des info-bulles vous permettent de désactiver cette fonction pour certains des messages reçus. Il vous suffit de cliquer dans la liste des catégories sur le nom correspondant au type de messages que vous ne voulez pas recevoir sous formes d'info-bulles. Le nom de catégorie s'affiche en jaune, et les messages appartenant à cette catégorie apparaissent dans une bannière en haut de l'écran ainsi que dans votre @34liste&de&messages. Vous n'aurez pas besoin de cesser de gouverner la cité pour vous occuper du message. Si vous sélectionnez 'Volonté satisfaite' dans la liste, les biens requis sont automatiquement envoyés depuis les entrepôts de la cité lorsque la livraison est prête. Reportez-vous à la rubrique @22chef&politique pour de plus amples informations sur les requêtes. @PCe menu vous permet d'activer ou de désactiver la fonction d'enregistrement automatique. Activez cette fonction afin que la partie soit enregistrée tous les six mois, ce qui peut s'avérer utile en cas de problème d'ordinateur. L'enregistrement écrase toujours le fichier précédent, ce qui réduit le nombre des fichiers de sauvegarde sur le disque dur. Vous pouvez désactiver cette fonction pour éliminer les pauses lors de l'enregistrement du jeu.  @PVous pouvez modifier le niveau de difficulté à tout moment à l'aide de l'option Difficulté. Notez, cependant, que votre score de mission dépend du niveau de difficulté choisi. Si vous modifiez le niveau de difficulté en cours de mission, votre score sera calculé en fonction du niveau le plus faible utilisé. @PEnfin, l'option Monument accéléré vous permet d'utiliser l'aide des dieux pour édifier certains @370monuments. Lorsque vous activez cette option, un dieu peut choisir de vous favoriser en vous aidant à édifier votre monument. Les dieux se consacrent uniquement à des monuments précis, à savoir les pyramides et les mastabas."
        }
    }

    message_help_menu {
        id: 13
        
        size [30, 28]
        title { text: "Menu Aide" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "Le menu Aide contient la liste de toutes les rubriques utilisées dans Pharaon. Vous pouvez également sélectionner plusieurs rubriques historiques dans la partie inférieure de la table des matières. @PLes 'bulles d'aide' sont les petits mots en forme de ballons qui apparaissent lorsque vous placez votre curseur sur un élément. L'option 'Toutes les bulles d'aide' affiche les bulles d'aide correspondant à presque toutes les options du jeu. L'option 'Quelques bulles d'aide' désactive les bulles d'aide pour toutes les options, sauf les @18cartes et les rapports du palais de votre cité. L'option 'Pas de bulles d'aide' désactive entièrement les bulles d'aide. @PLes 'avertissements' sont les petites bannières de message qui s'affichent en haut de l'écran. Vous pouvez les désactiver une fois que vous vous êtes familiarisé avec Pharaon."
        }
    }
    
    message_overseers {
        id: 14,
        
        size [30, 28]
        title { text: "Chefs" }
        subtitle {
            text: "Commandes du jeu"
        }
        content {
            text: "Utilisez l'option Consulter vos chefs du menu Chefs pour consulter un chef en particulier. Ce menu est particulièrement utile si vous avez choisi de masquer l'interface. Les chefs peuvent vous fournir de précieuses informations sur la situation de votre cité à un moment donné."
        }
    }
    
    message_game_control_money_display_window {
        id: 15,
        
        size [30, 28]
        title {
            text: "Ecran Argent",
        }
        subtitle {
            text: "Commandes du jeu",
        }
        content {
            text: "Cette fenêtre affiche le nombre de debens restants dans les coffres du trésor de votre ville. Pour plus de détails sur la génération d'un revenu, voir @48argent."
        }
    }
    
    message_game_control_population_display {
        id: 16,
        
        size [30, 28]
        title {
            text: "Ecran Population",
        }
        subtitle {
            text: "Commandes du jeu",
        }
        content {
            text: "Cette fenêtre affiche le nombre de citoyens dans votre cité.  Cliquez sur ce lien pour en savoir plus sur le rôle de la @39population dans ce jeu."
        }
    }
   
    message_game_control_date_display {
        id: 17,
        
        size [30, 28]
        title {
            text: "Ecran Date",
        }
        subtitle {
            text: "Commandes du jeu",
        }
        content {
            text: "Cette fenêtre affiche le mois et l'année en cours. Pour plus de clarté, le calendrier moderne est utilisé. Si le temps passe trop vite (ou trop lentement), utilisez le menu Vitesse."
        }
    }
    
    message_overlay_selector {
        id: 18,
        
        size [30, 28]
        title {
            text: "Sélecteur de carte",
        }
        subtitle {
            text: "Commandes du jeu",
        }
        content {
            text: "Le sélecteur de carte permet de voir votre cité sous plusieurs angles. Les cartes sont essentielles pour planifier et gérer les services de la cité. @PLorsque vous sélectionnez une carte, vous ne voyez que les bâtiments et les passants se rapportant directement à la section choisie. Par exemple, si vous choisissez la carte 'jongleurs' dans la liste des divertissements, vous ne verrez que vos étals, vos écoles de jongleurs et vos jongleurs. Tous les autres bâtiments sont aplatis. Les bâtiments affectés par le service affiché sont représentés par des blocs en marron clair avec des rayures. @PEchappent à cette règle la carte des risques, la carte des problèmes, la carte des attraits et la carte des falaises. En général, la hauteur de la colonne est proportionnelle au niveau d'accès. Ceci ne s'applique pas à la carte des risques. Dans ce cas, plus une colonne est élevée, plus le risque de dégâts, d'incendie, de malaria, de maladie ou de crime est élevé.  @PLa carte des attraits est organisée de façon différente. Lorsque cette carte est activée, votre cité se transforme en un tableau de blocs de couleur. Plus un bloc est élevé et bleu, plus son emplacement est attrayant et recherché par vos citoyens. Les zones à éviter sont signalées par des blocs rouges qui semblent s'enfoncer dans le sol. @PLa carte des puits fonctionne également de façon différente. Lorsque cette carte est active, les puits sont affichés dans un grand bloc bleu. Les maisons construites dans ce bloc ont accès à l'eau du puits. Une grille bleue avec des bordures en pointillés blancs couvre la plupart de votre propriété. Ceci indique que la nappe phréatique permet la construction de structures de pompage. Cette grille est également affichée si vous avez activé la carte des ressources en eau. @PSi les falaises vous bouchent la vue, utilisez votre carte Masquer falaises pour les aplanir provisoirement. Si vous avez construit des tombes royales dans les falaises, vous pourrez en visualiser l'intérieur après avoir sélectionné la carte Masquer falaises. @PLa carte des problèmes est également très différente tout en étant l'une des plus utiles. Cette carte affiche les bâtiments de votre cité qui ne fonctionnent pas à leur maximum. Placez le curseur de la souris au-dessus d'un bâtiment pour obtenir une explication du problème. Des icônes représentant des problèmes spécifiques marquent les différents bâtiments concernés. La carte des problèmes affiche aussi les charrettes bloquées. @PLa meilleure façon de se familiariser avec les différentes cartes est de les essayer. Une fois leur fonctionnement maîtrisé, la planification de la cité devient plus efficace."
        }
    }

    message_control_panel_toggle {
        id: 19,
        
        size [30, 28]
        title {
            text: "  Commande de l'affichage de l'interface",
        }
        subtitle {
            text: "Commandes du jeu",
        }
        content {
            text: "Ce bouton permet simplement d'afficher ou de masquer le panneau de commande. Masquer le panneau permet d'afficher une plus grande partie de la carte, mais rend l'accès aux commandes plus difficile. Utilisez ce bouton en fonction de vos préférences."
        }
    }

    message_overseer_workers {
        id: 20,
        
        size [30, 28]
        title {
            text: "Chef de la main-d'oeuvre",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Le Chef de la main-d'oeuvre prend note de tout ce qui concerne votre main d'oeuvre : le nombre d'offres d'emplois par secteur, le nombre de chômeurs et l'échelle des salaires. Il vous aidera à gérer les problèmes relatifs à votre main d'oeuvre. @PConsultez le Chef de la main-d'oeuvre pour décider du niveau des salaires dans votre cité. Dans le panneau Chef de la main-d'oeuvre, le salaire offert par votre cité est comparé au salaire moyen en Egypte. Utilisez les boutons de défilement pour sélectionner le montant des salaires à verser. Si les salaires que vous offrez sont supérieurs à la moyenne égyptienne, vos citoyens ont meilleur @39caractère et vous encouragez l'@39immigration. Par contre, si vous offrez des salaires inférieurs à la moyenne nationale, vos citoyens auront mauvais caractère et vont émigrer.  @PConsultez également le Chef de la main-d'oeuvre pour votre politique de l'emploi. Si vous n'avez pas de priorités spécifiques, le Chef de la main-d'oeuvre prend en charge l'affectation de la main d'oeuvre. Il commence généralement par le secteur alimentaire, puis l'industrie. Pour spécifier une nouvelle priorité (militaire par exemple), cliquez sur la ligne correspondante. Un panneau avec des chiffres est alors affiché. Pour donner la priorité à la défense, cliquez sur le numéro 1. Un cadenas est affiché en face de cette entrée, indiquant que vous avez verrouillé sa priorité. La catégorie sélectionnée suivante devient automatiquement la priorité numéro 2. Vous pouvez affecter différents niveaux de priorité à l'ensemble des secteurs.  @PAvertissement : lorsque vous définissez une priorité, le Chef de la main-d'oeuvre rassemble la main d'oeuvre nécessaire. Ceci peut avoir pour conséquence de priver d'autres secteurs de la main d'oeuvre nécessaire. Votre cité ne pourra pas survivre si l'un des secteurs d'activité reste sans main d'oeuvre. @PPour plus de détails sur l'organisation du travail, cliquez @43ici. @L@LPour un historique de l'organisation du travail dans l'Egypte ancienne, cliquez @155ici."
        }
    }

    message_overseer_military {
        id: 21,
        
        size [30, 28]
        title {
            text: "Chef militaire",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Votre Chef militaire prend note de toutes vos unités, pour l'armée et la marine. @PConsultez votre Chef militaire pour connaître le nombre et l'état de vos compagnies. Pour afficher les forces terrestres ou navales, cliquez sur le bouton situé dans la partie inférieure droite de l'écran. @PVérifiez vos unités en cliquant sur le bouton 'Atteindre'. Renvoyez vos unités au fort ou à quai en cliquant sur le bouton 'Retour'. @PParfois, le pharaon, ou une autre cité nécessite les services de vos troupes pour guerroyer. Cliquez sur le bouton 'Service royaume' pour leur envoyer des troupes. Votre aide n'est bien sûr pas désintéressée. Soit votre niveau du royaume augmentera, soit vous décrocherez des contrats plus lucratifs avec une autre cité. Par contre, un refus d'assistance risque de vous créer des ennemis. @PVotre Chef militaire vous informe également des activités militaires aux alentours de votre cité. Il vous prévient en cas de menace ou de demande d'assistance. @L@LLes Egyptiens mettaient sur pied des armées et des flottes considérables. Cliquez @181ici pour en savoir plus sur la guerre dans l'antiquité."
        }
    }

    message_overseer_political {
        id: 22,
        
        size [30, 28]
        title {
            text: "Chef politique",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Votre Chef politique se charge des relations avec le pharaon et les gouverneurs des autres cités.  @PLe Chef politique prend note de toutes les demandes de marchandises, qu'elles émanent du pharaon ou des autres cités. Il dispose d'un inventaire des marchandises disponibles dans vos @4entrepôts et vous prévient dès que vous êtes en mesure de répondre à la requête. Vous pouvez alors demander au chef d'expédier les marchandises. Il est généralement préférable de satisfaire les requêtes du pharaon ou des autres cités au plus vite. Les requêtes ignorées risquent de réduire le commerce ou de motiver une agression. Mieux vaut envoyer les marchandises tard que jamais. @PLe Chef politique est également compétent pour vos économies personnelles. Il connaît le montant de vos économies et de votre salaire. Adressez-vous à ce chef pour changer le niveau de votre rémunération. Pour ce faire, cliquez sur le bouton d'affichage de votre salaire. Un écran affiche une table. Sélectionnez une entrée dans cette table. Sachez que vos compatriotes sont à cheval sur les principes et n'apprécient pas qu'une personne s'accorde des revenus sans rapports avec son rang. @PPour utiliser une partie de vos économies, servez vous du Chef politique comme intermédiaire. Vous pouvez envoyer un cadeau au pharaon (ou, si vous êtes le pharaon, au royaume en général) ou faire un don au trésor de votre cité.  @PLe pharaon et les autres dirigeants ne dédaignent pas la flatterie et les cadeaux personnels. Vous pouvez ainsi faire progresser votre situation (et augmenter votre niveau du royaume) en envoyant des cadeaux de temps à autre. Si vous disposez d'économies suffisantes, vous pouvez choisir les cadeaux à envoyer. Ne soyez pas trop généreux pour autant. En effet, si vous envoyez trop de cadeaux, les bénéficiaires risquent d'en prendre l'habitude et de vous blâmer en cas de retard. Ils ont également tendance à vouloir des cadeaux de plus en plus précieux. Lorsque vous décidez d'envoyer un cadeau, le Chef politique s'assure qu'ils arrivent intacts. @PVous pouvez également faire don de vos économies personnelles au trésor de votre cité. Cette solution est particulièrement utile si vous parvenez à empêcher votre cité de contracter des dettes, car les intérêts sur les dettes sont particulièrement ruineux. En effet, le pharaon et les autres dirigeants ne prêtent pas d'argent sans contrepartie. Pour plus de détails sur l'argent de votre cité, cliquez @48ici. @PEnfin, votre Chef politique connaît votre niveau du royaume et a vent de l'attitude du pharaon à votre égard. Pour plus de détails sur les niveaux, consultez le @23Chef&des&niveaux."
        }
    }
    
    message_overseer_ratings {
        id: 23,
        
        size [30, 28]
        title {
            text: "Chef des niveaux",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Le Chef des niveaux vous renseigne sur les niveaux de culture et de prospérité, le niveau architectural et du royaume et précise les objectifs démographiques. Lorsque vous cliquez sur un niveau, le chef indique le meilleur moyen de l'améliorer ou ce qui l'empêche de progresser. Vous pouvez ainsi savoir où vous en êtes en regardant les colonnes placées au-dessus des différents niveaux. Si vous avez atteint le but fixé au début de la mission, les colonnes reçoivent un chapiteau. @PSi votre cité dispose d'un @77palais&gouvernemental, vous pouvez connaître rapidement vos niveaux en déplaçant la souris au-dessus de ce palais. Un petit écran énumère les niveaux et le taux de chômage. @PPour plus de détails sur les niveaux et leur rôle, cliquez @35ici."
        }
    }

    message_overseer_commerce {
        id: 24,
        
        size [30, 28]
        title {
            text: "Chef du commerce",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Votre Chef du commerce est toujours très occupé. Non seulement il s'efforce d'identifier les cités ouvertes au @47commerce, mais encore il connaît exactement le contenu de vos @4entrepôts et l'état de vos @46industries. @PLorsque vous consultez votre Chef du commerce, vous obtenez une liste des marchandises pouvant être produites ou importées par votre cité. Cliquez sur l'une de ces marchandises pour obtenir un récapitulatif de l'état de l'industrie correspondante. Vous verrez ainsi le nombre de bâtiments spécialisés dans la production d'une marchandise donnée et le nombre de ces bâtiments en fonction.  @PCe panneau comporte des instructions spécifiques sur la marchandise. Si une route commerciale est ouverte pour ce type de marchandise (voir plus bas), vous pouvez demander à votre Chef du commerce de procéder à l'importation ou à l'exportation. Si vous exportez cet article, vous devez indiquer à votre Chef du commerce la quantité que vous souhaitez conserver en réserve dans vos entrepôts. Ceci est particulièrement utile si vous exportez des articles tels que les poteries. En effet, la demande interne en poteries tend à être élevée et par conséquent, vous devez en conserver suffisamment dans vos entrepôts. @PVous pouvez également interrompre une industrie. Si vous souhaitez arrêter la production d'un bien, vous pouvez mettre l'industrie correspondante en réserve. Les bâtiments qui produisent le produit fini sont alors fermés sans être détruits. Les bâtiments produisant des matières premières pour transformation ne sont pas affectés. Les bâtiments mis en réserve congédient leur main d'oeuvre. Cette méthode permet de libérer des travailleurs en cas de pénurie de main d'oeuvre. L'activité de cette industrie peut être rétablie à tout moment. @PLe dernier bouton du panneau permet de créer des réserves dans vos entrepôts. Lorsque vous créez une réserve de marchandises, vous ne pouvez pas l'échanger et vos citoyens n'y ont pas accès. Les réserves sont particulièrement utiles si vous devez répondre rapidement à une requête en provenance d'un dieu. Cliquez de nouveau sur le bouton pour utiliser la marchandise ou en faire le commerce. Avant de reprendre le commerce d'un article en réserve, informez votre Chef du commerce. @PVous pouvez également accéder au panneau @32Carte&du&royaume à partir du panneau du Chef du commerce. La carte du royaume affiche les cités environnantes. Cliquez sur une cité pour savoir si elle est prête à faire du commerce avec vous. Dans l'affirmative, les marchandises qu'elle souhaite acheter ou vendre sont énumérées en bas de l'écran. Les boules en bronze figurant dans le coin du symbole de la marchandise indiquent la quantité de charrettes que la cité est prête à acheter ou vendre par an : une boule pour 15 charrettes, deux pour 25 et trois pour un maximum de 40. @PLe coût de l'ouverture d'une route commerciale est également affiché. Cliquez sur ce bouton pour demander à votre trésor de financer l'ouverture de la route commerciale. Une fois cette route ouverte, demandez à votre Chef du commerce d'importer ou d'exporter les marchandises voulues. @PLe Chef du commerce sait exactement combien de marchandises peuvent être achetées ou vendues. Cliquez sur le bouton 'Afficher les prix' et un panneau affiche toutes les marchandises disponibles dans le royaume. Les vendeurs ne touchent pas l'intégralité de ce qui est payé par les acheteurs. Cette différence permet de payer les caravanes et les navires effectuant des voyages longs et périlleux, le tout dans l'intérêt du libre échange. @PLes entrées des sections @46industrie, @45nourriture et @47commerce vous aident à développer votre sens des affaires."
        }
    }
    
    message_overseer_granaries {
        id: 25,
        
        size [30, 28]
        title {
            text: "Chef de la nourriture",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Nourriture et population sont indissociables. Le Chef de la nourriture prend note de l'évolution démographique de votre cité et de sa consommation. @PCe chef présente les informations relatives à votre cité par l'intermédiaire de 3 graphiques. Par défaut, le premier graphique analyse l'évolution de la population. Il indique les périodes de croissance et de réduction. A droite de ce graphique figurent deux plus petits graphiques : recensement et société. Cliquez sur l'un de ces graphiques pour l'agrandir et le placer au centre de l'écran.  @PLe graphique Recensement représente les classes d'âge. Ceci est particulièrement utile pour prédire la croissance ou la réduction de la main d'oeuvre, car même si les enfants et les vieillards ne travaillent pas, ils n'en continuent pas moins de manger, boire de la bière et casser des poteries !  @PLe graphique Société divise les citoyens par revenu, exprimé en fonction de leur logement. Les citoyens très riches (scribes) ne font pas de travaux manuels et par conséquent, plus une cité s'enrichit plus sa main d'oeuvre tend à diminuer. Bien qu'ils ne fassent pas partie de la force de travail, les scribes versent une quantité non négligeable d'impôts dans les coffres du palais. @PDes informations très utiles sont affichées en dessous des graphiques. La première ligne indique le nombre de personnes pouvant être nourries en fonction de la production alimentaire et l'impact prévisible de cette production sur la population globale. Le Chef de la nourriture indique également le nombre de greniers présents dans la cité et le nombre de mois de provisions. Il indique également les différents types de nourriture consommés par vos citoyens. Il tient le compte des personnes entrant ou quittant la cité, ainsi que du nombre d'immigrants arrivés au cours du mois précédent. @PConsultez les entrées relatives à la @39Population et l'@45Alimentation pour mieux comprendre l'importance de ce chef."
        }
    }
    
    message_overseer_public_health {
        id: 26,
        
        size [30, 28]
        title {
            text: "Chef de l'hygiène",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Le Chef de l'hygiène indique le nombre de médecins, de dentistes et de salles d'embaumeurs présents dans votre cité. Pour tous ces services d'hygiène, le chef indique le nombre de personnes desservies et un taux approximatif de couverture. Il affiche également le nombre de pharmacies. Pour plus de détails sur une section spécifique de votre cité, utilisez la carte @18hygiène. @PLe Chef de l'hygiène recense tous les risques menaçant la cité, tels que la malaria ou la peste. Dans la mesure où une alimentation équilibrée est importante pour la santé, il suit le régime de vos citoyens. Il rend également compte de l'opinion générale de la population concernant le service de santé.  @PL'entrée @53Hygiène permet de comprendre l'importance de l'hygiène dans votre cité."
        }
    }
    
    message_overseer_learning {
        id: 27,
        
        size [30, 28]
        title {
            text: "Chef de l'éducation",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Le Chef de l'éducation recense le nombre d'écoles de scribes et de bibliothèques de votre cité. Il indique le nombre de personnes desservies et si le taux de couverture est adéquat pour la cité. Pour plus de détails sur le taux de couverture de l'une des parties de votre cité, utilisez la carte @18éducation. @PLe Chef de l'éducation vous informe également des attentes de vos citoyens en termes d'éducation. Consultez l'entrée @50éducation pour plus de détails."
        }
    }

    message_overseer_diversions {
        id: 28,
        
        size [30, 28]
        title { text: "Chef des loisirs" }
        subtitle { text: "Commande du jeu"  }
        content {
            text: "Votre chef des loisirs sait combien de théâtres, de jongleurs, de musiciens et de danseurs se livrent à leurs activités dans la cité. Le nombre de théâtres est bien plus important que le nombre d'@71étals, de @72kiosques et de @73pavillons. Sa tâche ne consiste donc pas à énumérer ces lieux. En outre, il répertorie le nombre de @74tavernes&de&jeux et de @479zoos. Il évalue le nombre de personnes qui peuvent profiter des théâtres de votre cité, des zoos et des tavernes de jeux et juge ainsi de la satisfaction des habitants vis-à-vis des infrastructures de loisirs auxquelles ils ont accès.  @PReportez-vous à la section sur les @49loisirs pour en savoir plus sur leur rôle dans votre cité. @L@LPour en savoir plus sur les loisirs dans l'Egypte ancienne, cliquez @165ici."
        }
    }

    message_overseer_temples {
        id: 29,
        
        size [30, 28]
        title {
            text: "Chef des temples",
        }
        subtitle {
            text: "Commande du jeu",
        }
        content {
            text: "Apaiser les dieux n'est pas une tâche facile. Le Chef des temples permet de satisfaire les divinités. @PLe Chef des temples vous indique toutes les divinités ayant une influence sur votre cité. Vous saurez ainsi quelle divinité protège votre cité et pourrez lui accorder toute l'attention possible. Près du nom de ces divinités, vous trouverez le nombre de petits et de grands temples qui leur sont dédiés dans votre cité. Vous y trouverez également le nombre de sanctuaires et le nombre de mois écoulés depuis la dernière fête en leur honneur. Enfin, vous prendrez connaissance de l'humeur des différentes divinités. @PLorsque vous préparez une fête dans votre cité, consultez le Chef des temples. Cliquez sur le bouton 'Organiser une fête'. Désignez la divinité à honorer et spécifiez l'importance de la fête. Vous devez disposer d'un pavillon de fête dans votre cité avant d'organiser une grande fête ou une fête grandiose. Les fêtes grandioses nécessitent également de bonnes réserves de bière. @PLe Chef des temples vous informe sur les préoccupations religieuses de vos citoyens. @PConsultez les sections @51religion et @35niveaux pour mieux comprendre pourquoi il est important d'apaiser les divinités."
        }
    }

    message_overseer_treasury {
        id: 30,
        
        size [30, 28]
        title { text: "Chef des finances" }
        subtitle { text: "Commande du jeu" }
        content {
            text: "Le Chef des finances enregistre le nombre de debens entrant ou sortant des coffres de votre cité. Consultez ce chef pour déterminer les zones nécessitant des économies ou permettant d'accroître vos revenus. @PUn récapitulatif des impôts figure en haut de l'écran. Utilisez les boutons de défilement pour changer le taux d'imposition. La valeur par défaut de 9 % est considérée comme raisonnable par vos citoyens. Si vous sélectionnez une valeur supérieure à 9 %, vous attiserez leur colère et ralentirez l'immigration. Plus vous maintiendrez un taux d'imposition élevé, plus la colère de vos citoyens montera. Pour plus de détails sur le caractère de vos citoyens, cliquez @39ici. @PLe chef indique également le montant des impôts collectés, le nombre de citoyens imposés et le montant des impôts n'ayant pas pu être collectés par les percepteurs. Pour déterminer les zones de votre cité ne payant pas leur dû, utilisez la @18carte&impôts. @PVous trouverez une feuille d'analyse à la suite du récapitulatif. Les lignes de cette feuille donnent le détail des revenus provenant de l'imposition, des cadeaux et de l'exportation de marchandises.  @PSous la maigre liste de revenus, vous trouverez la liste plus considérable de vos dépenses. En général, les salaires et les frais de construction sont les plus coûteux, suivis de près par les importations. @PLa partie gauche de la liste affiche les performances de l'année précédente pour comparaison. Vous pouvez ainsi voir si l'une de vos dépenses a augmenté de façon spectaculaire au cours de l'année écoulée. @PL'entrée @48Argent comporte davantage de conseils sur le budget. L'entrée relative aux @80percepteurs est également utile."
        }
    }

    message_chief_overseer {
        id: 31,
        
        size [30, 28]
        title { text: "Responsable" }
        subtitle { text: "Commande du jeu" }
        content {
            text: "Votre Responsable consulte tous les autres chefs et affiche des vignettes représentant l'état de votre ville. N'hésitez pas à le consulter si vous n'êtes pas sûr de ce dont votre cité a le plus besoin. Les articles urgents, nécessitant votre attention immédiate apparaissent en jaune. Les problèmes sérieux apparaissent en blanc. Cliquez sur l'un des problèmes pour bénéficier de suggestions et consulter les chefs susceptibles de vous aider. @PVotre Responsable vous communique également les tout derniers résultats du nilomètre. Le nilomètre sert à prévoir le niveau de l'inondation de la saison suivante. @PPrêtez attention à votre Responsable. Ses avertissements peuvent sauver votre cité du désastre."
        }
    }

    message_world_map {
        id: 32,
        
        size [30, 28]
        title { text: "Carte du royaume" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "La carte du royaume affiche les cités environnantes. Sa fonction la plus importante consiste probablement à identifier des partenaires pour le @47commerce. @PCliquez sur un nom de cité pour prendre connaissance du type de commerce proposé. Vous trouverez en dessous du nom de la cité les produits qu'elle achète et revend, ainsi que le coût d'ouverture d'une route commerciale. Cliquez sur le bouton 'Ouvrir une route de commerce' pour activer les relations. @PVous recevrez fréquemment des demandes d'approvisionnement en provenance d'autres cités ou vous apprendrez que des combats ont lieu ailleurs. La carte du royaume est un outil de référence pratique permettant de situer les autres cités. Si un envahisseur attaque une cité près de la vôtre, mieux vaut préparer votre défense. @PLisez les entrées @47commerce, @52guerre&et&paix et @24Chef&du&commerce pour plus de détails sur l'utilisation de la carte du royaume."
        }
    }

    message_building_buttons {
        id: 33,
        
        size [30, 28]
        title { text: "Boutons de construction" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "Ces boutons permettent de placer des structures sur la carte. Le prix du bâtiment est affiché sur le bouton. Lorsque vous sélectionnez une structure à construire, une image verte en transparence remplace le curseur de la souris. Déplacez cette image sur la carte. Si le terrain est constructible l'image reste verte, sinon elle est remplacée par un losange rouge. @L@LConsultez l'aide relative aux différents bâtiments en cliquant sur les structures existantes avec le bouton droit de la souris ou sélectionnez-les dans la section 'Bâtiments' de la @10Table&des&matières."
        }
    }
    
    message_game_control_messages {
        id: 34,
        
        size [30, 28]
        title { text: "Messages des scribes" }
        subtitle { text: "Commandes du jeu" }
        content {
            text: "Lorsqu'une situation importante l'exige, l'un de vos nombreux scribes vous envoie un message détaillé. Ces messages nécessitent toute votre attention et il serait imprudent de les ignorer. @PLes nouveaux messages sont signalés par une sonnerie. Si le message est particulièrement important, il apparaît automatiquement. Cependant, vos scribes sont polis et évitent ce genre de procédé dans la mesure du possible. Si le message n'est pas très important, il est simplement ajouté à votre liste de messages. Consultez vos messages en cliquant sur le bouton près du scribe, dans la partie inférieure du panneau de commande. Ce bouton affiche un chiffre indiquant le nombre de messages reçus. Lorsque vous cliquez sur ce bouton, la liste des messages est affichée. Le premier message de cette liste est le dernier reçu. @PPour effacer ces messages après les avoir lus, cliquez avec le bouton droit sur le titre du message dans votre liste. Cette opération n'a cependant rien d'obligatoire. @PCertains messages comportent un bouton 'sonnerie d'urgence', notamment pour les messages signalant un incendie ou des dégâts structurels. Cliquez sur la cloche pour atteindre directement la zone à problème. @PLes joueurs expérimentés peuvent, s'ils le veulent, désactiver certaines info-bulles à partir du @12menu&Options. Lorsque vous activez cette option, les messages s'affichent en haut de l'écran et sont également ajoutés à votre boîte de messages."
        }
    }

    message_ratings {
        id: 35,
        
        size [30, 28]
        title { text: "Niveaux" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "Les différents niveaux permettent d'évaluer vos qualités de gouverneur. Lorsque vous commencez une mission, vous recevez une liste de niveaux à atteindre. Vous devez atteindre ces niveaux avant d'obtenir une promotion. Votre succès sera mesuré en fonction de 4 niveaux : Culture, Prospérité, Monument et Royaume. @L@LCULTURE @PLe niveau Culture dépend du nombre de citoyens ayant accès à des centres de @49loisirs, d'@50éducation, d'@53hygiène et de @51religion. Le niveau de culture mesure non seulement le nombre de centres, mais encore les différentes options. Pour atteindre un niveau de culture élevé, offrez autant d'options que possible à vos citoyens. En clair, facilitez l'accès aux multiples formes de divertissement, de services d'hygiène (à l'exception des pharmacies, car elles n'ont aucun effet sur votre niveau de culture), multipliez les bibliothèques et les temples dédiés aux différentes divinités. Le secret d'un haut niveau de culture consiste à offrir plus de centres que n'en demandent les citoyens. @PPour atteindre le niveau de culture le plus élevé, essayez de construire un @479zoo. Vous devrez construire un zoo si vous arrivez à un niveau de culture supérieur à 75. Cliquez sur le bouton Loisirs pour vérifier si le zoo figure parmi vos options de loisirs. @L@LPROSPERITE @PVotre niveau de prospérité reflète la richesse globale de la cité. Ce niveau prend en compte la rentabilité de la cité, les fortunes personnelles de vos citoyens et le tissu social de la cité. Si votre cité dégage des bénéfices tous les ans, le niveau de prospérité devrait progresser. Un chômage élevé, des logements de mauvaise qualité et l'absence de nourriture variée risquent d'entraver sa progression. Le fait de ne pas payer de tribut au pharaon (si vous n'êtes pas le pharaon) réduit également ce niveau. Si un grand temple ou une taverne de jeu sont disponibles, le niveau de prospérité progresse, car votre cité présente des signes d'opulence. L'achèvement d'un monument contribue également au niveau de prospérité. Naturellement, si votre cité perd de l'argent ou est endettée en fin d'année, le niveau de prospérité s'en ressent. Cependant, si vous avez perdu de l'argent en raison des coûts de construction, votre niveau de prospérité n'est pas affecté, car ce genre de dépense contribue à l'amélioration de la cité.   @PVotre niveau chute rapidement si vous perdez ou ignorez les batailles lointaines, si vous ne parvenez pas à assurer la distribution des marchandises provenant d'autres régions du royaume, et si vous contractez des @48dettes pendant une trop longue durée. @L@LMONUMENT @PLe niveau Monument indique le temps qu'il reste avant qu'un monument soit achevé. Le fait de déposer des @374offrandes&funéraires une fois les monuments achevés représente une étape de construction prise en compte pour mesurer le niveau Monument. @PLe niveau de votre royaume va également chuter si des @477pilleurs&de&tombes dérobent les @374offrandes&funéraires déposées dans une tombe dont vous avez la garde. En effet, les autres citoyens d'Egypte penseront que vous n'avez aucun respect pour les morts. @L@LConsultez le @23Chef&des&niveaux pour connaître votre réputation. Lorsque vous cliquez sur un niveau, votre chef suggère différentes possibilités d'amélioration des niveaux. @L@LROYAUME @PLe niveau du royaume permet de savoir quelle opinion le pharaon et les autres cités du royaume ont de vous. Une réponse rapide à leurs requêtes, ce qui inclut les tributs dus au pharaon, permet d'améliorer ce niveau. Sinon, vous ne pouvez que perdre des points. Il est également conseillé de maintenir l'ordre, et la défaite des envahisseurs potentiels contribue à l'amélioration du niveau. Si le niveau du royaume tombe trop bas, votre réputation entachée risque de motiver une attaque par le pharaon ou par une cité voisine. @PLe niveau de votre royaume va également chuter si des @477pilleurs&de&tombes dérobent les @374offrandes&funéraires déposées dans une tombe dont vous avez la garde. En effet, les autres citoyens d'Egypte penseront que vous n'avez aucun respect pour les morts. @PVos compatriotes égyptiens sont également très satisfaits de l'arrestation d'un pilleur de tombes et le niveau de votre royaume augmentera légèrement à chaque arrestation par vos agents."
        }
    }

    message_city_crime {
        id: 36
        
        size [30, 28]
        title { text: "Criminalité" }
        subtitle { text: "Game Concept" }
        content {
            text: "Lorsque les citoyens sont vraiment en colère, ils commettent des crimes. Leur objectif est de voler de l'argent, que ce soit dans le coffre de la cité ou dans vos propres économies. @PPour identifier les habitations susceptibles d'abriter de futurs voleurs, utilisez l'option Criminalité de la carte des risques. Sur cette carte, les logements sont représentés par des colonnes. Plus la colonne est haute, plus les chances sont grandes que cette habitation abrite un criminel. @PLorsqu'un criminel erre dans les rues, les @76magistrats ne peuvent rien faire pour l'arrêter. @86Les&agents, par contre, peuvent appréhender et arrêter les criminels avant qu'ils ne sévissent. @PIl est ainsi possible d'éviter un crime si un agent rencontre un criminel dans les rues de la cité. Le meilleur remède contre la criminalité reste cependant la prévention. Pour cela, veillez au bonheur des citoyens. @PLa criminalité peut également provoquer l'apparition de @477pilleurs&de&tombes, mais uniquement si votre cité abrite le tombeau d'un membre de l'une des plus prestigieuses familles d'Egypte (pyramide, mastaba, mausolée ou tombe royale). Les pilleurs de tombes ont une aptitude particulière pour pénétrer dans les tombes royales et voler les trésors qu'elles contiennent. @PIl arrive que la cupidité corrompe même les plus heureux des citoyens. Ces citoyens cupides se rassemblent entre amis et évoquent les somptueuses offrandes funéraires placées dans les tombes des nobles. Lorsqu'ils succombent à leur cupidité, ces citoyens provoquent une vague de criminalité et deviennent des pilleurs de tombes ! Puisque vous ne pouvez pas sonder le coeur de tous vos citoyens, vous ne pouvez pas prévoir l'éventualité d'une vague de criminalité. Cependant, les agents n'hésiteront pas à frapper quiconque se hasarderait à profaner une tombe pour en piller les offrandes funéraires."
        }
    }

    message_fort_and_company {
        id: 37,
        
        size [30, 28]
        title {
            text: "Compagnies et forts",
        }
        content {
            text: "Chaque soldat fait partie d'une compagnie, stationnée dans son propre fort. Il existe plusieurs types de compagnies et de forts : @L@LInfanterie @LL'infanterie constitue la base de l'armée. Entraînés pour le combat rapproché, les fantassins se battent sur la ligne de front et se déplacent à une vitesse moyenne. Ils quittent le centre de recrutement armés de lances. @L@LArchers @LGrâce à leurs flèches, les archers peuvent attaquer des ennemis à longue distance, mais ils sont très vulnérables en combat rapproché. Ils se déplacent légèrement moins vite que les fantassins et peuvent fabriquer eux-mêmes leurs arcs et leurs flèches. @L@LConducteurs de char @LRien n'est plus effrayant pour les fantassins que la vue d'une grande rangée de chars fonçant droit sur eux. Les chars sont très efficaces contre les lignes de défense ennemies qui, une fois percées, fragilisent beaucoup l'adversaire. Chaque conducteur reçoit un char lorsqu'il quitte le centre de recrutement. @L@LLes soldats restent dans leur fort en temps de paix et attendent un ordre de combat pour se rendre sur le champ de bataille. Les soldats apprécient l'esprit de camaraderie qui règne au sein du fort. Les longues campagnes militaires nuisent au moral des troupes. @PLes forts n'ont pas besoin d'un accès à la route ou à la main-d'oeuvre. Ces bâtiments exercent une très mauvaise influence sur la cité. Il est donc conseillé de les construire à l'écart de toute habitation. @L@LPour en savoir plus sur la militaires dans l'Egypte ancienne, cliquez @184ici."
        }
    }
    
    message_true_pyramid {
        id: 38,
        
        size [30, 28]
        title {
            text: "Vraie pyramide",
        }
        content {
            text: "La vraie pyramide est constituée principalement de @95blocs&de&pierre recouverts d'une couche de @95calcaire&poli.  Les @363tailleurs&de&pierre posent ces pierres et les polissent, tandis que les @363menuisiers construisent les rampes pour accéder au sommet de la pyramide au fur et à mesure que celle-ci s'élève. Lorsqu'un @4entrepôt contient quatre blocs de pierre, les paysans amènent leur cargaison aux tailleurs de pierre sur le chantier. @PIl existe cinq types de vraies pyramides : petite, moyenne, grande, ensemble de pyramides et grand ensemble de pyramides.  @LReportez-vous aux sections @370construction&de&monuments, @373chef&des&monuments et @369contremaître pour obtenir des renseignements supplémentaires.  @LLes pyramides ont fait la célébrité de l'Egypte. Plus que toute autre image, elles symbolisent l'Egypte aux yeux du monde. @L@LPour en savoir plus sur la vraie pyramide dans l'Egypte ancienne, cliquez @392ici."
        }
    }

    message_population_groth_and_sentiment {
        id: 39,
        
        size [30, 28]
        title {
            text: "Population et emploi",
            pos [15, 5]
        }
        subtitle {
            text: "Concept du jeu",
        }
        content {
            text: "Lorsque vous fondez une cité, les immigrants à la recherche d'aventure sont prêts à commencer une nouvelle vie sur cette terre étrangère. Au fur et à mesure du développement de la cité, les nouveaux immigrants qui se présentent sont principalement attirés par la réputation de la cité. Si la vie dans la cité est agréable (opinion favorable), ses habitants feront passer le mot dans tout le royaume et de nouveaux immigrants arriveront dans la cité si vous leur aménagez des zones d'habitation. @PL'opinion est un indicateur de la qualité de vie dans la cité. Les facteurs contribuant à une opinion favorable sont des salaires élevés, des impôts faibles, de la nourriture et du travail en abondance. En effet, tous les citoyens espèrent être nourris correctement, se voir attribuer un emploi, mais encore obtenir une juste compensation par rapport au travail fourni et ne pas avoir à payer des impôts déraisonnables. @PSi vos citoyens ne sont pas satisfaits, ceux-ci passeront le mot aux immigrants qui renonceront à s'installer dans votre cité. Les immigrants potentiels décideront de rester où ils sont ou d'aller ailleurs si la réputation de votre cité est mauvaise (opinion défavorable). Si la réputation de votre cité empire, certains de ses habitants se décideront à quitter la ville. @PVotre responsable connaît ses citoyens. Consultez son rapport d'opinion pour vous aider à améliorer les conditions de vie dans votre cité. @POutre le fait qu'elle décourage les immigrants, la morosité peut favoriser la @36criminalité. @PLe manque de logement peut également décourager les immigrants. Consultez le chef de la nourriture pour savoir si la cité possède suffisamment de réserves pour accueillir de nouveaux habitants. Si tous les logements sont occupés, créez de nouveaux terrains constructibles pour attirer de nouveaux immigrants ou prenez les mesures appropriées pour encourager les habitants à améliorer leur habitation. Des logements évolués abritent un plus grand nombre de personnes."
        }
    }
    
    message_game_concept_workers {
        id: 40,
        
        size [30, 28]
        title { text: "Ouvriers" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "Le fonctionnement de la plupart des bâtiments nécessite des ouvriers. Lorsqu'un nouveau bâtiment est construit, un représentant est envoyé pour recruter des travailleurs dans les environs. Si votre cité dispose de personnes sans emploi, le recrutement sera aisé. Dans le cas contraire, le représentant poursuivra sa recherche jusqu'à trouver le personnel nécessaire. @PLa cité emploie des dizaines d'ouvriers différents qui effectuent des tâches variées. Certains des travailleurs de la cité empruntent les rues de la cité en vaquant à leurs tâches quotidiennes. @L@LCliquez @155ici pour savoir comment travaillaient les Egyptiens à l'époque des pharaons."
        }
    }

    message_game_concept_scribes {
        id: 41,
        
        size [30, 28]
        title { text: "Scribes" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "Une fois que votre cité est devenue une belle métropole disposant de biens et de services de qualité, vous devez vous préoccuper d'éduquer vos @40citoyens pour en faire des scribes.   @PLes scribes ne travaillent pas, mais payent beaucoup d'impôts. Vous pouvez les observer se promenant dans la cité à la recherche de loisirs. @PLorsqu'une partie de la population est composée de scribes, la demande en biens augmente, tandis que la masse des travailleurs décroît. Si aucun immigrant ne se présente dans votre cité pour occuper les emplois vacants, prenez les mesures nécessaires pour attirer des immigrants. @PL'éducation est le privilège des gens aisés. Les citoyens les plus riches de votre cité n'effectuent pas de tâches manuelles et souhaitent que leurs enfants ne connaissent pas les longues journées de labeur harassantes sous le soleil brûlant. Les scribes envoient donc leurs enfants dans l'école de scribes de leur quartier. Ils fréquentent également les bibliothèques pour entretenir leur culture."
        }
    }

    message_game_concept_walkers {
        id: 42,
        
        size [30, 28]
        title {
            text: "Piétons",
        }
        content {
            text: "La cité emploie des dizaines d'ouvriers différents qui effectuent des tâches variées. Certains des travailleurs de la cité empruntent les rues de la cité en vaquant à leurs tâches quotidiennes. Ces piétons peuvent être répartis en deux groupes : les passants qui vont vers une destination spécifique et les promeneurs qui flânent au hasard des rues. @L@LPassants @L@LLes passants quittent leur lieu de travail avec en tête une destination spécifique. A l'aide de la carte des routes de votre cité, ils définissent l'itinéraire le plus court pour atteindre leur destination. A quelques exceptions près (indiquées ci-dessous), ils empruntent toujours les routes. @L@LPromeneurs @L@LLes piétons qui flânent dans la cité sont également utiles, car lorsqu'ils passent devant les habitations des citoyens, ils n'hésitent pas à leur rendre service. Certains promeneurs apportent également de précieux services aux bâtiments de la cité. @PLes promeneurs se déplacent sans destination spécifique et prennent à chaque départ une direction différente. En fait, ils sont complètement imprévisibles. @PChaque fois qu'un promeneur arrive à un carrefour, il doit décider du chemin à prendre. Cette décision changeant à chaque fois, les maisons visitées par le promeneur ont de fortes chances de ne pas être visitées une seconde fois avant un certain temps. @PLe moyen le plus simple de gérer ces promeneurs est de maîtriser l'infrastructure routière de la cité. Les carrefours donnant à ces piétons une trop grande liberté, limitez les croisements si vous voulez pouvoir les contrôler. @P@358Les&barrages&routiers sont un autre moyen pour contrôler les promeneurs, car face à un barrage routier, leur premier réflexe est de faire demi-tour. Cependant, les piétons avec une destination spécifique peuvent traverser ces barrages sans difficultés. @L@LPrédateurs @LIl n'y a pas que des amis dans notre cité. Des animaux dangereux rôdent également dans les alentours et tuent sans pitié ceux qui ont le malheur de croiser leur chemin. Les agents s'efforcent de tuer ces monstres, mais vous obtiendrez probablement de meilleurs résultats si vous utilisez vos forces militaires. Vous devez surveiller les animaux suivants : hyènes, hippopotames, crocodiles, aspics, scorpions et lions."
        }
    }

    message_employment_unemployment {
        id: 43,
        
        size [30, 28]
        title { text: "Travail et manque de travail" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "Presque tous les bâtiments de la cité requièrent de la main-d'oeuvre, sans laquelle la cité ne peut subvenir aux besoins de ses habitants. @PLorsque vous construisez pour la première fois un bâtiment qui nécessite de la main-d'oeuvre, un agent de recrutement patrouille les rues à la recherche de travailleurs. S'il en rencontre, le bâtiment qui l'envoie aura la main-d'oeuvre requise. @PLe travail d'un recruteur n'est pas toujours simple. L'une des principales difficultés est de trouver l'équilibre entre la main-d'oeuvre disponible et le nombre d'emplois proposés. Dans un monde idéal, une cité doit avoir exactement le même nombre d'emplois que de personnes pour s'en charger, ce qui n'est malheureusement que très rarement le cas. Une cité a soit trop de main-d'oeuvre pour le nombre d'emplois disponibles, soit le contraire. @PLe manque de travail n'est pas une bonne chose pour une cité. Les personnes sans travail, à force de ne rien faire, risquent de désespérer et de faire par conséquent chuter l'@39opinion. Elles risquent même de sombrer dans la @36criminalité. La meilleure manière de traiter le manque de travail est de créer de nouveaux emplois. En général, il n'est pas mauvais pour une cité d'avoir un surplus de biens et de services. Quelques fermes supplémentaires, davantage de structures de loisirs, ainsi que de nouvelles écoles, bibliothèques et temples peuvent constituer un avantage pour votre cité. Tout en augmentant les emplois, vous pouvez améliorer la prospérité de votre cité et son niveau de culture. @PUn autre moyen, quoique frustrant, d'augmenter le nombre d'emplois est de réduire la population. Vous pouvez pour cela détruire les habitations, forçant ainsi l'émigration. Cela peut également avoir un effet positif sur la cité. En effet, si vous détruisez les habitations des quartiers les plus défavorisés, la valeur générale des habitations de votre cité s'améliorera. Cette amélioration peut augmenter votre niveau de prospérité. @PUn autre problème que vous pouvez rencontrer est le manque de main-d'oeuvre par rapport au nombre d'emplois disponibles. La meilleure solution est d'attirer de nouveaux immigrants. Pour cela, vous devez construire de nouvelles zones d'habitation ou encourager les zones existantes à se développer en accueillant de plus grandes structures. Vérifiez que l'@39opinion est élevée. Vous pouvez également attirer de nouveaux immigrants en augmentant les salaires ou en diminuant les impôts. @PSi vous attendez un afflux d'immigrants pour se charger des emplois disponibles, vous devez consulter votre @24chef&du&commerce et votre @20chef&de&la&main-d'oeuvre. Consultez votre chef du commerce et fermez les industries non indispensables pour une courte période. Vous pourrez ainsi libérer de la main-d'oeuvre pour d'autres emplois. Si vous ne voulez pas fermer toute une industrie, vous pouvez détruire une partie des bâtiments industriels.   @PConsultez votre chef de la main-d'oeuvre afin d'établir les priorités en matière de main-d'oeuvre. Le fait de faire passer les emplois cruciaux au premier plan assure aux citoyens de quoi subvenir à leurs besoins. @PIl existe également un moyen peu orthodoxe et pas forcément avantageux de remédier à une pénurie de main-d'oeuvre. Il s'agit d'encourager les structures de @41scribes à devenir des structures d'@40ouvriers. Vous ferez ainsi chuter le niveau de prospérité de votre cité tout en diminuant le revenu lié aux  impôts ; en revanche, la main-d'oeuvre augmentera, aux dépens des espoirs et des rêves des plus riches habitants ! @PBien que le fait de n'avoir pas de travail soit relativement stressant, il n'est pas mauvais pour une cité en pleine expansion de connaître un léger manque de travail. En effet, cela confère une source de main-d'oeuvre idéale pour de nouveaux bâtiments. Toutefois, il est préférable que le chômage ne dépasse pas 5 pour cent."
        }
    }
    
    message_drinking_water {
        id: 44,
        
        size [30, 28]
        title { text: "Eau potable" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "L'accès à l'eau potable est l'une des premières choses que les habitants demandent. Leur habitation ne peut s'améliorer sans un peu d'eau. @PLes @62puits et les @61points&d'eau fournissent de l'eau potable aux habitants. Les puits sont une source d'eau rudimentaire. Ils peuvent satisfaire les habitants lorsque la cité en est à ses balbutiements, mais cette situation ne peut pas durer longtemps. Les habitants exigeront bientôt de l'eau provenant de points d'eau. @PLes points d'eau nécessitent des porteurs d'eau pour acheminer l'eau jusqu'aux habitations. Une fois qu'un porteur est venu dans un foyer, ce dernier dispose d'un accès à l'eau potable. Vous devez observer scrupuleusement l'activité des porteurs d'eau : ce sont des @42promeneurs qui ne suivent pas toujours le même chemin. Les habitations qui avaient autrefois accès à de l'eau potable en abondance risquent de perdre cet accès, en particulier si vous modifiez le réseau routier. Si un point d'eau atteint un stade plus avancé (une pierre ronde apparaît au sommet), vous constatez qu'il envoie davantage de promeneurs dans les rues. @PSi l'@56attrait des environs ne suffit pas, les travailleurs affectés aux points d'eau peuvent prendre les mesures nécessaires pour en améliorer l'aspect et l'efficacité. Les porteurs d'eau affectés à l'un de ces points d'eau évolués vont circuler plus souvent dans le voisinage. @PLes puits et les points d'eau ne peuvent être construits que sur les terres bénéficiant de nappes phréatiques, ce qui est indiqué par la présence d'herbe. @PConsultez la rubrique @53Hygiène pour en savoir plus sur les bienfaits de l'eau potable."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,
        
        size [30, 28]
        title { text: "Nourriture et agriculture" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "Le meilleur moyen de toucher le coeur des citoyens est de satisfaire leur estomac. Le fait d'assurer une nourriture abondante et variée améliore l'@39opinion et l'@53hygiène&de&la&cité.  @PIl existe plusieurs types d'exploitations agricoles dans Pharaon : on cultive notamment les @89céréales, les @90grenades, les @90pois&chiches, la @90laitue et les @90figues. Il existe également deux types d'agricultures dans Pharaon : l'agriculture des plaines inondables et l'agriculture des prairies. Ces deux types d'agricultures nécessitent un accès routier et de la main-d'oeuvre, mais les similitudes s'arrêtent là. L'agriculture n'est pas l'unique source de nourriture. En effet, la @359chasse, la @84pêche et l'@360élevage contribuent également à remplir les greniers de votre cité. @L@LAgriculture des plaines inondables @LPour comprendre comment les fermes des plaines inondables fonctionnent, vous devez d'abord comprendre le fonctionnement du Nil. Chaque année, généralement entre juin et septembre, le Nil entre en crue. Les plaines inondables sont alors entièrement submergées et rien ne peut être placé sur la terre. Au bout de quelques mois, le Nil commence à descendre, laissant un limon de nutriments fertilisant la terre. La plaine inondable émerge de nouveau, permettant de cultiver le sol. @G56 @PLe Nil n'entre pas toujours en crue à la même période ou de la même manière chaque année. En outre certaines inondations sont meilleures que d'autres. Les prêtres utilisent des nilomètres pour déterminer la valeur de la prochaine inondation et rapporter les résultats au @31responsable. Le fait de porter une attention particulière à Osiris, dieu de l'agriculture et de l'inondation par le Nil @51(voir&Religion), permet d'assurer une bonne inondation chaque année. @PVous pouvez construire des fermes (ainsi que des routes et des rigoles d'irrigation) sur la plaine inondable à tout moment, sauf durant l'inondation. Lorsque vous construisez une ferme sur une plaine inondable, seul le champ apparaît, sans bâtiments, car l'inondation les détruit tous. Comme aucune habitation ne peut être construite sur les plaines inondables, les paysans ont besoin d'un endroit où se réunir pour pouvoir travailler. Les @8chantiers remplissent cette fonction. Ils envoient les ouvriers sur les exploitations pour semer et moissonner. Sans chantiers, aucune activité ne peut avoir lieu sur les exploitations. Vous devez veiller à ne pas trop éloigner les chantiers des exploitations, afin que les ouvriers aient le moins possible à marcher pour se rendre sur leur lieu de travail. @PLe meilleur moment pour construire une ferme est juste après la décrue. Vous pouvez en effet profiter pleinement de la période de croissance jusqu'à l'inondation suivante et la récolte sera alors à son maximum. Les fermes construites à tout autre moment ont une production moins importante. @PL'autre facteur à prendre en considération lors de la construction d'une ferme est la fertilité. Plus la terre est sombre et plus l'herbe est abondante, plus le terrain est fertile. La terre la plus fertile se trouve généralement à proximité du fleuve. Plus on s'en éloigne, moins la terre est fertile. Les exploitations placées sur les terres les plus fertiles produisent les meilleures récoltes. Vous pouvez construire des rigoles d'irrigation sur des plaines inondables pour irriguer les terres les plus éloignées du fleuve, ce qui permet d'améliorer la fertilité des terres laissées sèches lors des faibles inondations. @PEn raison du rythme annuel du Nil, les fermes des plaines inondables ne peuvent produire qu'une récolte par an. La survie d'une cité peut dépendre de la main-d'oeuvre employée pour la récolte et de la place disponible pour stocker cette récolte. @L@LAgriculture des praires @LLa terre des plaines inondables n'est pas la seule terre fertile, même si elle constitue le gros des terres cultivables. Les exploitations peuvent également être placées dans les prairies, indiquées par des touffes jaunes. Plus ces touffes sont denses, plus la terre est fertile, et plus la récolte a des chances d'être abondante. Ces fermes possèdent toutes un bâtiment de travail, si bien qu'elles ne nécessitent pas la présence de paysans venant d'un chantier. Comme cette terre n'est pas inondée, ces exploitations continuent à fonctionner toute l'année. Toutefois, hectare par hectare, la terre des prairies est de moins en moins fertile par rapport à celle des plaines inondables. Les exploitations des prairies ont généralement des récoltes moins importantes. Ces exploitations ont presque toujours besoin de rigoles d'irrigation. @L@LChasse et pêche @LLes chasseurs bénéficient de la richesse naturelle de l'Egypte. Ils partent à la recherche de proies, les capturent puis retournent à leurs bases pour la préparer. @PLes chasseurs travaillent dans des pavillons de chasse. C'est de là qu'ils partent à la recherche de troupeaux d'autruches, de gibier d'eau ou d'antilopes. Si vous remarquez l'un de ces animaux aux alentours de la cité, placez un pavillon de chasse à proximité. @PLes pêcheurs se réunissent sur les quais où ils échangent des récits sur leur activité. Ces quais sont, bien entendu, situés au bord de l'eau, et les pêcheurs ont besoin d'une fabrique de bateaux pour construire leurs embarcations. Une fois qu'ils ont un bateau, ils peuvent partir travailler. Toutes les cités ne peuvent pas prendre en charge une activité de chasse ou de pêche. Si vous remarquez des poissons dans les eaux avoisinantes, votre cité pourra développer une industrie de pêche.   @PLa taille des troupeaux et des écoles est limitée. La chasse et la pêche assurent à une population peu nombreuse de quoi se nourrir, mais une population abondante ne peut survivre uniquement grâce au poisson et au gibier. @L@LElevage @LLes fermes d'élevage peuvent être une excellente source supplémentaire de nourriture. Elles peuvent être placées sur n'importe quel type de terrain, et non uniquement sur des terres fertiles, ce qui permet d'économiser des terres cultivables pour d'autres activités. Les bêtes d'élevage se nourrissent de paille, produit dérivé de la @89culture&des&céréales. Le nombre de fermes d'élevage qu'une cité peut avoir est uniquement limité par la quantité de paille que cette cité peut allouer à la nourriture des bêtes d'élevage. @L@LDistribution de la nourriture @LLes @3greniers et les @2bazars sont les intermédiaires entre les producteurs alimentaires et les habitants de la cité. Les greniers permettent de stocker la nourriture destinée à être consommée par les habitants, tandis que les bazars permettent sa distribution aux habitations individuelles.   @PDès qu'un producteur alimentaire peut distribuer un produit, un charretier achemine ce produit à un grenier. Les acheteurs de bazar se rendent dans les greniers pour récupérer la nourriture que leurs clients leur demandent. Ils peuvent transporter plusieurs types de produits alimentaires en même temps. Lorsque l'acheteur revient au bazar avec son chargement, les marchands de bazar parcourent le voisinage et distribuent la nourriture à la population. @PIl est important d'avoir suffisamment de greniers et de bazars. Si tous les greniers sont pleins, le charretier achemine la nourriture jusqu'à un @4entrepôt, si ce dernier doit recevoir de la nourriture. Les acheteurs de bazar ne peuvent pas se procurer de produits locaux dans les entrepôts (bien qu'ils y acheminent des produits non alimentaires et de la nourriture importée). Ils récupèrent la majeure partie de leur chargement de nourriture dans les greniers. @PL'installation de bazars et de greniers peut s'avérer difficile. Les greniers doivent être situés à proximité de la structure de production alimentaire afin que les charretiers n'aient pas un long trajet à effectuer. Les bazars doivent être situés à proximité des greniers afin que les acheteurs de bazar puissent alimenter leur stock. Les bazars doivent également être situés à proximité des habitations qu'ils desservent. Toutes ces structures attirent les citoyens indésirables. Vous devez donc vous attendre à quelques dérives.   @PA mesure que votre cité se développe, il se peut que vous ayez à construire des greniers plus éloignés des structures de production alimentaire afin d'assurer que les bazars des quartiers éloignés puissent se procurer la nourriture dont vous avez besoin. Vous devez donc utiliser les ordres spéciaux des greniers afin de vous assurer que ces structures reçoivent la nourriture dont elles ont besoin. @L@LImportation de nourriture @LCertaines cités ne peuvent pas produire suffisamment de nourriture pour subvenir à leurs propres besoins, ou ne peuvent produire qu'une variété limitée de produits alimentaires. Elles doivent donc importer de la nourriture livrée aux entrepôts. La nourriture importée est livrée aux entrepôts, où les acheteurs de bazar peuvent la récupérer et les acheminer de nouveau vers les bazars. @L@LDans cette section, les rubriques associées sont des liens hypertexte (les mots correspondant à ces liens apparaissent dans une couleur différente du reste du texte). Ces rubriques vous aideront à comprendre les mécanismes de production et de distribution de la nourriture. @L@LPour obtenir un récit historique sur la nourriture dans l'Egypte ancienne, cliquez @150ici. Pour plus d'informations sur l'action du Nil, cliquez @157ici."
        }
    }

    message_game_concept_industry {
        id: 46
        
        size [30, 28]
        title { text: "Industrie" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "L'industrie est l'une des principales sources d'emplois de la cité. Les citoyens utilisent certains produits industriels dans leur vie quotidienne. D'autres produits sont @47commercialisés pour réaliser des bénéfices.   @PSi les industries d'une cité peuvent être très diverses, elles ont toutes des caractéristiques communes. Elles ont toutes besoin de main-d'oeuvre ; si celle-ci est insuffisante, l'efficacité d'une fabrique ou d'un fournisseur de matières premières risque alors de diminuer. Toutes les industries ont en outre besoin d'un accès routier pour les ouvriers. @PCertaines industries produisent des matières premières pouvant servir à la réalisation de produits finis dans une fabrique. Il s'agit de @92puits&d'argile, de @361mines&de&pierres&précieuses, de @93mines&de&cuivre, de @94chantiers&de&bois et de @94structures&de&cueilleur&de&roseaux. Les @91exploitations&d'orge, les @91exploitations&de&henné et les @91exploitations&de&lin produisent également des matières premières nécessaires à l'industrie. Les @89exploitations&de&céréales, qui sont une source de nourriture, permettent également de produire une denrée non alimentaire : la paille. Un seul producteur fournit généralement suffisamment de matières premières pour deux industries de produits finis. Les matières premières peuvent être commercialisées, mais leur prix est moins élevé que celui des produits finis. @PLes industries de transformation des matières premières en un autre produit (que l'on appelle souvent 'ateliers') sont les @96brasseries, les @99orfèvreries, les @60ateliers&de&tissage, les @97fabriques&de&papyrus, les @1poteries, les @364briqueteries, les @473fabriques&de&lampes, les @470fabriques&de&peintures, les @98fabriques&d'armes et les @98fabriques&de&chars. Les produits finis sont utilisés par la cité ou commercialisés sur les marchés. @PLes @95carrières et les @93mines&d'or se distinguent des autres industries car leur matière première est également leur produit fini. Les @82fabriques&de&bateaux produisent un produit fini (bateaux) à partir d'une matière première (bois), mais les bateaux ne peuvent pas être commercialisés sur le marché. @PLes livreurs acheminent les marchandises à l'endroit adéquat. Les livreurs employés par les producteurs de matières premières essaient toujours dans un premier temps d'acheminer leurs chargements vers les ateliers où ils sont attendus, en commençant par l'endroit le plus proche. Si aucune industrie ne requiert la matière première correspondante, le livreur se rend à l'@4entrepôt le plus proche qui peut accueillir ses marchandises. Si aucun entrepôt n'est disponible, le livreur se repose jusqu'à ce que l'un d'entre eux se libère. Les seuls livreurs qui ne travaillent pas de cette façon sont les charretiers des mines d'or et les tireurs de traineaux des carrières. Le charretier des mines d'or n'achemine son or que dans le palais, jamais vers un entrepôt. La pierre ne pouvant pas être transformée en un autre produit, les tireurs de traineaux des carrières acheminent toujours leurs matériaux jusqu'à un entrepôt. @G74 @PCertains bâtiments citadins ont besoin de produits industriels pour fonctionner correctement. Il s'agit de la @70bibliothèque, de l'@68école&de&scribes, de la @74taverne&de&jeux, du @88centre&de&recrutement, de la @66salle&des&embaumeurs, de la @363guilde&des&artisans et de la @363guilde&de&menuisiers. Un livreur travaillant dans une fabrique doit acheminer ses produits finis jusqu'au bâtiment qui en a besoin. Si aucun n'est disponible, il doit se rendre à un entrepôt ou attendre jusqu'à ce que l'un d'entre eux se libère. Les charretiers apprécient ces vacances impromptues, car elles leur permettent de continuer à percevoir un salaire sans rien faire.  @PPour savoir si vos industries rencontrent des problèmes, utilisez la @18carte&des&problèmes. Elle indique les bâtiments industriels qui ne fonctionnent pas correctement et la raison de ce dysfonctionnement.   @PCliquez avec le bouton droit de la souris sur un bâtiment pour afficher le bilan actuel de sa production. Ce document vous renseigne sur le stade du cycle de production de ce bâtiment et vous indique si la main-d'oeuvre est suffisante. Le panneau vous indique les problèmes éventuels.   @PCliquez sur l'un des liens hypertexte ci-dessus (en bleu) pour en savoir plus sur chaque type d'industrie. @L@LCliquez @151ici pour obtenir un récit historique de l'industrie dans l'Egypte ancienne."
        }
    }

    message_game_concept_trade {
        id: 47,
        
        size [30, 28]
        title {
            text: "Commerce",
        }
        subtitle {
            text: "Concept du jeu",
        }
        content {
            text: "Aucune cité n'est entièrement autosuffisante. Grâce au commerce, votre cité a accès à des marchandises qu'elle ne peut pas produire. L'exportation est une source de revenus considérable, souvent plus que les impôts. En raison de son importance, votre cité devrait commencer une activité commerciale dès qu'elle pourra subvenir aux besoins de ses habitants. @PLa @32mappemonde indique les cités avec lesquelles vous pouvez entretenir des relations commerciales. Les cités désireuses de lier des relations commerciales affichent un drapeau. Cliquez sur l'une de ces cités pour connaître les produits achetés et vendus par cette municipalité. Les points bleus qui apparaissent dans le coin du symbole de la marchandise indiquent la quantité que la cité souhaite importer ou exporter chaque année. Un seul point signifie que la marchandise concernée n'est pas commercialisée en grandes quantités, tandis que la présence de trois points indique une forte volonté de commercialiser la marchandise. Ces niveaux peuvent varier en fonction de l'offre et de la demande ou de la situation politique égyptienne.  @PCliquez sur le bouton 'Ouvrir une route de commerce' pour dépenser les fonds nécessaires à l'établissement de nouvelles relations commerciales. L'ouverture d'une route de commerce peut être une opération très coûteuse, mais elle s'avère toujours payante à long terme. @PAprès avoir ouvert une route de commerce, consultez votre @24chef&du&commerce pour définir les relations à établir. Cliquez sur le bouton 'Afficher les prix' pour connaître la valeur des produits susceptibles d'être achetés ou vendus. Vous remarquerez que le prix des produits à la vente est moins élevé que leur prix à l'achat. La différence correspond aux dépenses faites par le marchand pour se rendre dans votre cité. @L@LImportation @LPour importer une marchandise, cliquez dessus. Après avoir sélectionné un élément, deux choix s'offrent à vous. Vous pouvez décider vous-même de la marchandise à acquérir et indiquer à votre chef du commerce d'agir en conséquence. Vous pouvez également laisser votre chef du commerce décider de la quantité de marchandises à acquérir. Votre chef du commerce continue à importer le bien en question tant que les stocks de la cité sont insuffisants ou jusqu'à ce que la limite de commercialisation annuelle de votre partenaire soit atteinte.  @PVous devez importer certains des biens dont votre cité a besoin, notamment le marbre blanc pour la construction de monuments et l'huile pour les @473lampes. Pour amener le niveau d'@56habitation de la cité à son niveau le plus élevé, vous devrez également importer des articles de luxe. @PL'importation peut être très coûteuse ; il vous est donc recommandé de contrôler scrupuleusement les @4entrepôts de la cité. Si vous remarquez qu'ils regorgent de l'une des marchandises importées, vous devez économiser de l'argent en évitant d'importer cette marchandise jusqu'à épuisement des stocks. En outre, l'importation de matières premières est moins coûteuse que celle de produits finis. A long terme, la cité économisera de l'argent si elle possède ses propres fabricants pour transformer les matières premières importées en produits finis. @L@LExportation @LPour exporter une marchandise, cliquez dessus. Ensuite, décidez vous-même de la quantité de marchandises à acquérir ou laissez le chef du commerce prendre cette décision. Les surplus sont exportés jusqu'à ce que le quota annuel du client soit atteint. N'oubliez pas que certaines marchandises exportées par la cité sont également convoitées par ses habitants ; veillez donc à conserver un stock suffisant pour satisfaire les besoins des habitants. Vérifiez fréquemment l'état de vos bazars et des habitations pour savoir s'ils possèdent les biens commercialisés. En outre, vérifiez que les bâtiments nécessitant un produit fini disposent d'un stock suffisant. Si certains bâtiments éprouvent des difficultés à s'approvisionner en une marchandise donnée, c'est que la cité exporte cette marchandise en trop grandes quantités. @L@LIl arrive qu'une cité importe ou exporte la même marchandise. Cela vous donne plus de flexibilité dans la planification des activités industrielles de la cité. Si vous voulez accroître les revenus d'une cité, affectez de la main-d'oeuvre à la production d'une marchandise et exportez-la auprès d'un partenaire commercial. Si vous voulez utiliser la main-d'oeuvre de la cité pour une autre activité, il est préférable d'importer ce bien. Une cité ne peut pas simultanément importer et exporter une marchandise. Elle ne peut tirer aucun bénéfice de l'importation d'un produit d'une cité dans le seul but de le vendre à une autre cité. Les acheteurs payant plus que ce que les vendeurs reçoivent, la cité ne peut que perdre de l'argent en faisant office d'intermédiaire. En revanche, l'importation d'une matière première et l'exportation du produit fini qui lui est associé s'avère souvent une opération fort bénéfique. @PLes marchands approchent votre cité par caravane ou par navire commercial. Avant de pouvoir établir des relations commerciales avec les marchands, vous devez posséder un entrepôt opérationnel. Outre un entrepôt, vous avez également besoin d'un @83dock pour lier des relations commerciales avec des marchands utilisant des barges. Les navires commerciaux poursuivent leurs activités aux docks exclusivement et, lorsqu'ils arrivent, des charretiers travaillant aux docks sont chargés de récupérer les marchandises dans les entrepôts."
        }
    }
    
    message_game_concept_money {
        id: 48,
        
        size [30, 28]
        title {
            text: "Argent",
        }
        subtitle {
            text: "Concepts du jeu",
        }
        content {
            text: "Vous ne pouvez pas construire de cité sans argent. L'argent qu'une cité a dans ses caisses est un bon indicateur de sa réussite. Une cité gagne de l'argent en collectant des impôts, en exportant des marchandises, en recevant des offrandes et, si ses ressources le permettent, en extrayant de l'or. Ces différents sujets sont évoqués à la fin de cette section. Mais avant tout, il vous faut connaître les subtilités de la gestion pécuniaire.  @L@LEndettement @LLa première fois que votre trésorerie est à sec, sachez que les autres chefs égyptiens peuvent vous apporter une aide financière supplémentaire. Cela ne vous pénalise en aucune façon et aucun remboursement n'est attendu. Vous devez cependant prendre cette situation comme un avertissement qui doit vous inciter à modifier les habitudes de dépense de votre cité. @PSi vous dépensez tous vos fonds de secours, ou si vous n'en recevez pas, votre cité a droit à une dette d'un maximum de 5 000 debens. Les chiffres jaunes indiquent que votre cité est endettée. @PLes petites dettes sporadiques sont souvent inévitables et ne portent pas à conséquences si vous rééquilibrez rapidement votre budget. L'endettement à long terme, en revanche, peut vous coûter une partie. @L@LConséquences d'un endettement @LChaque mois que votre trésorerie est en déficit, des intérêts sont automatiquement ajoutés à votre dette totale. Plus votre endettement est important, plus vous avez à payer d'intérêts, et plus votre dette s'accroît.   @PLorsque votre cité termine une année en déficit, vous n'êtes pas en mesure d'honorer votre tribut annuel (voir plus loin). Le fait de ne pas honorer un tribut ne vous coûtera pas d'argent, mais il réduira quelque peu votre @35niveau&du&royaume. Les conséquences empirent si cette situation se répète plusieurs années consécutives. @PSi vous ne parvenez pas à rééquilibrer votre budget (même provisoirement) 12 mois après votre première dette, votre niveau du royaume est affecté car les autres chefs perdent confiance dans votre aptitude à gouverner. Votre première pénalité d''endettements à répétition', bien que douloureuse, ne devrait pas causer de dommages irréparables. Si vous n'avez pas encore de chiffres positifs lors de votre second endettement, votre niveau du royaume baisse considérablement et les années qui suivent risquent d'être encore pires.   @L@LFin de l'endettement @LL'endettement est un problème grave et, lorsque vous ne pouvez pas l'éviter, vous devez rembourser votre dette aussi vite que possible. Nous évoquons plus loin les différents moyens de gagner de l'argent, mais vous devez également éviter d'investir le crédit limité dont vous disposez dans une entreprise qui ne sera pas source de revenus a posteriori. Les bureaux de perception, les industries fabriquant des produits d'exportation et les nouvelles routes de commerce reliant les cités susceptibles d'acheter vos produits constituent des dépenses valables.  @L@LTribut annuel @LA la fin de l'année, votre cité doit payer un 'impôt' au royaume, appelé 'tribut'. Le montant de cet impôt varie en fonction de la richesse de votre cité. Il est donc dans un premier temps très bas et s'accroît à mesure que la population et la richesse de la cité augmentent. Consultez votre @30chef&des&finances pour connaître le tribut que vous avez à payer.  @PSi vous terminez l'année avec de l'argent dans vos caisses, le tribut est automatique. Le paiement de cet impôt n'est jamais actif. Toutefois, si vous terminez l'année avec un endettement, votre cité ne peut pas payer son tribut et votre @35niveau&du&royaume diminue. La pénalité pour une année sans payer le tribut n'est pas excessive, mais elle augmente la deuxième année consécutive et ainsi de suite. Cela reflète l'état de votre réputation auprès de votre peuple en tant que mauvais gestionnaire financier.  @L@LImpôts @LLes impôts sont demandés aux citoyens pour tous les services qui leur sont offerts par la cité. Ils n'ont aucune raison de protester à ce sujet tant que le montant des impôts reste raisonnable. Le taux initial de 9 pour cent est un bon taux de base, mais vous pouvez l'augmenter ou le diminuer à tout moment. Consultez votre chef des finances ou cliquez avec le bouton droit de la souris sur le palais pour régler ce taux. Si vous le diminuez, vous provoquerez joie et gratitude. Si vous l'augmentez, vous engendrerez des plaintes et risquez de provoquer un exode massif hors de la cité. @PL'augmentation des impôts est parfois nécessaire. Si vous remarquez que votre cité est sur le point de s'endetter, vous pouvez augmenter l'impôt afin d'alléger cette dette. Vous devez cependant chercher une solution à long terme aux problèmes d'agent de votre cité. Un taux d'impôt élevé risque d'aggraver rapidement l'@39opinion. @PSi les citoyens acceptent de payer des impôts, ils ne sont pas enclins à sacrifier une partie de leur revenu sans qu'on le leur demande. Pour collecter des impôts, la cité doit disposer d'un @77palais. Ensuite, vous devez construire des @80bureaux&de&perception pour la collecte des impôts. @PLe chef des finances sait quel pourcentage de votre population est assujetti à l'impôt et connaît la quantité d'impôts non collectée en raison d'un nombre insuffisant de percepteurs. Utilisez la @18carte&des&impôts pour savoir si une zone de votre cité est particulièrement riche. Assurez-vous également que les impôts sont justement répartis dans la cité. Si une partie des habitants paie beaucoup d'impôts et qu'une autre partie n'en paie pas, l'@39opinion se dégradera fortement et la @36criminalité risque de se développer. @L@LCommerce @LLe revenu à l'exportation est généralement la principale source de richesse de la cité. Ouvrez des routes de commerce dès que possible. Il est impératif que vous sachiez comment exporter des marchandises. Tâchez de vous documenter sur le @47commerce en cas de problème. @L@LExtraction d'or @LCertaines cités peuvent fabriquer leur propre monnaie. L'or est converti en debens, la monnaie égyptienne de base. Si vous apercevez des pépites de métal incrustées dans un affleurement de roche, vous pourrez peut-être construire une @93mine&d'or. Mais ne vous réjouissez pas trop vite ; il se peut que le minerai ne soit que du @93cuivre, qui a une certaine valeur en soi mais qui n'est généralement pas aussi prisé que l'or. Cliquez sur le bouton Structures industrielles de l'interface, puis cliquez sur le bouton Matières premières afin de savoir de quel métal précieux dispose votre cité.  @PLes mines d'or fonctionnent comme les autres @46industries, mais leur production n'est livrée qu'au palais, où elle est transformée en debens. Elles ne sont jamais livrées à un entrepôt. @L@LEconomies familiales et salaires @LTout comme la cité, vous pouvez, vous aussi, gagner de l'argent. On vous paie pour vos efforts en tant que chef de la cité et vous pouvez vous constituer un salaire dès que vous vous êtes construit une @78demeure&luxueuse. Votre salaire vous est payé à partir des fonds de la cité et est proportionnel à votre expérience. Vous pouvez choisir de modifier votre salaire, mais, si ce dernier est plus important que votre expérience ne le suggère, votre @35niveau&du&royaume risque de chuter. Vous pouvez également vous payer moins que votre expérience ne le suggère, ou ne pas vous payer du tout, ce qui peut impressionner et accroître votre niveau du royaume. Si votre cité rencontre des difficultés financières, le fait de ne pas vous payer est un bon moyen de réduire les dépenses. @PVous pouvez transférer les économies familiales sur les fonds de la cité à tout moment, ce qui constitue un bon moyen d'éviter l'endettement. En revanche, il est impossible de transférer les fonds de la cité sur votre compte familial. Ce serait du détournement de fonds ! @PVos économies familiales peuvent également servir à acheter une 'offrande pour l'Egypte'. Une telle donation au peuple d'Egypte ou, à la discrétion de votre chef, à d'autres chefs égyptiens, augmente immédiatement votre niveau du royaume de quelques points. Vous devez cependant utiliser ce stratagème avec prudence. Dès que les offrandes commencent, leurs bénéficiaires les attendent, surtout si vous avez pris l'habitude de les distribuer régulièrement. Le fait de les supprimer risque d'affecter votre niveau. @PConsultez l'entrée du @22chef&politique pour obtenir davantage d'informations sur vos économies personnelles."
        }
    }

    message_game_concept_entertainment {
        id: 49,
        
        size [30, 28]
        title {
            text: "Divertissements",
        }
        subtitle {
            text: "Concept du jeu",
        }
        content {
            text: "Le travail sans loisirs fait d'Imhotep un être fade. Vous devez offrir des loisirs aux habitants pour que votre cité soit agréable à vivre. @PLes @71étals, les @72kiosques, les @73pavillons, les @74tavernes&de&jeux et les @479zoos offrent aux habitants les divertissements qu'ils demandent. Si votre cité est naissante, ses habitants se contentent du moindre établissement, à savoir l'étal. A mesure que votre cité se développe, la demande de loisirs grandit et les habitants exigent différents types de divertissements. Votre @28chef&des&loisirs vous aide à répondre aux besoins de vos habitants. @PLa plupart des artistes doivent pratiquer leur art dans des @75centres&d'entraînement. Les jongleurs pratiquent leur art dans les écoles de jonglerie, les musiciens dans les conservatoires et les danseurs dans les écoles de danse. Une fois prêts, les artistes passent du centre d'entraînement au lieu de représentation. Les maîtres de senet ne sont pas formés dans des centres d'entraînement. @PVos citoyens savent qu'ils ont accès aux loisirs lorsqu'ils voient des artistes passer devant leurs maisons (cliquez @42ici pour plus d'informations sur les passants). Les artistes sont issus de structures d'entraînement entièrement fonctionnelles. Musiciens, jongleurs et danseurs parcourent les rues pour se rendre du centre d'entraînement au lieu de représentation. Souvenez-vous-en lors de la conception des structures de votre cité. Si vous placez le lieu de représentation et le centre d'entraînement dans des zones opposées, les artistes devront traverser des habitations pour se rendre au bâtiment voulu, dépensant ainsi une partie de leur énergie. Mais prenez garde à ne pas placer le centre d'entraînement trop loin du lieu de représentation. Plus un artiste doit se déplacer, plus courte sera sa représentation et plus la salle a de risques de s'endormir, ce qui n'apporterait rien à personne.   @PLa taverne de jeux et le zoo exigent tous les deux diverses marchandises. La taverne de jeux a besoin de @96bière pour soulager le gosier de ses clients assoiffés, et le zoo de @89paille et de @359gibier pour subvenir aux besoins des animaux. @L@LCliquez @165ici pour en savoir plus sur les loisirs dans l'Egypte ancienne."
        }
    }

    message_game_concept_education {
        id: 50,
        
        size [30, 28]
        title {
            text: "Education",
        }
        subtitle {
            text: "Concept du jeu",
        }
        content {
            text: "L'éducation est le privilège de la haute société. Les gens riches savent que l'éducation dans une @68école&de&scribes mène à une existence meilleure pour leurs enfants et ils apprécient l'accès à une @70bibliothèque. @PNi les écoles de scribes, ni les bibliothèques ne peuvent fonctionner sans @97papyrus. Avant de construire une bibliothèque, vous devez avoir un stock suffisant de papyrus dans vos @4entrepôts pour remplir les rayonnages de la bibliothèque de rouleaux. Les @42passants des deux structures emportent avec eux des papyrus lorsqu'ils vont éduquer la population. La cité doit produire ou @47importer du papyrus pour que les structures éducatives puissent continuer à fonctionner. @PConsultez votre @27chef&de&l'éducation pour vous assurer que votre cité répond aux demandes de la population dans ce domaine.  @PLe fait de compter un nombre suffisant de bibliothèques et d'écoles pour vos habitants vous assure un bon @35niveau&de&culture. @L@LPour obtenir davantage d'informations sur les loisirs des Egyptiens anciens, cliquez @165ici."
        }
    }

    message_game_concept_relition {
        id: 51,
        
        size [30, 28]
        title {
            text: "Religion",
        }
        subtitle {
            text: "Concept du jeu",
        }
        content {
            text: "L'Egypte compte cinq divinités principales : Osiris, dieu de l'agriculture et de l'inondation par le Nil, Ptah, dieu des artisans, Rê, dieu du royaume, Seth, dieu de la destruction et Bastet, déesse du foyer. Si vous apaisez ces divinités, vous améliorez votre situation, mais, si vous les ignorez, cela peut s'avérer néfaste. Votre @29chef&des&temples connaît l'humeur des dieux ; veillez à le consulter fréquemment. @PDe nombreuses cités ont une divinité protectrice. Cette dernière attend plus d'une cité que les autres divinités locales. Ces dernières exigent moins qu'une divinité protectrice, mais elles peuvent affecter une cité, en bien ou en mal, de la même manière. Certaines divinités peuvent être inconnues de la cité, qui peut choisir de les ignorer par précaution. @PLa meilleure façon d'apaiser les dieux est de leur dédier de nombreux @67temples&et&sanctuaires. La divinité protectrice s'attend à posséder plus de sanctuaires que tout autre divinité. De même, chaque divinité locale s'attend à posséder moins de temples et de sanctuaires qu'une divinité protectrice, tout en ayant le même nombre de temples et de sanctuaires que les autres divinités locales.  @PLes dieux peuvent en outre être apaisés par une fête, la plus belle possible. Les fêtes somptueuses et les fêtes grandioses sont des mesures provisoires efficaces lorsqu'une divinité se met en colère contre une cité. Organisez une fête en l'honneur du dieu mécontent et ce dernier sera soulagé, ce qui vous fera gagner du temps pour construire d'autres temples ou d'autres sanctuaires avant d'essuyer la colère de cette divinité. Consultez votre @29chef&des&temples pour organiser une fête. Notez que, tant que vous n'avez pas construit de place des fêtes, aucune fête ne peut avoir lieu dans votre cité. Les fêtes grandioses nécessitent également une quantité de @96bière suffisante dans les @4entrepôts de la cité. Etant donné les efforts qu'une fête nécessite, une cité ne peut en organiser que deux par an.    @POutre les temples et les sanctuaires, vous pouvez également construire un ensemble de temples, généralement en l'honneur de la divinité protectrice de la cité. Chaque cité ne peut avoir qu'un ensemble de temples à la fois. Vous pouvez construire un ensemble de temples en l'honneur d'une divinité locale si celle-ci a acquis une importance particulière. Mais attention. La divinité protectrice de la cité peut devenir très jalouse si une autre divinité possède un ensemble de temples. @PLes ensembles de temples sont coûteux, mais valent la dépense. Le fait de posséder des ensembles de temples fonctionnels apporte de nombreux avantages à la cité et augmente son @35niveau&de&prospérité. Vous pouvez également payer pour ajouter un oracle ou un autel à votre ensemble de temples. Voici une liste de ces édifices : @L@L@350Ensemble&de&temples&d'Osiris : @P	Autel de Sebek @P	Oracle de Min @L@351Ensemble&de&temples&de&Rê @P	Autel de Maât @P	Oracle d'Horus @L@352Ensemble&de&temples&de&Ptah @P	Autel d'Amon @P	Oracle de Thot @L@353Ensemble&de&temples&de&Seth @P	Autel d'Anubis @P	Oracle de Sekhmet @L@354Ensemble&de&temples&de&Bastet @P	Autel d'Isis @P	Oracle d'Hathor @L@LLe fait de fournir aux habitants plusieurs lieux de culte pour honorer plusieurs dieux assure à votre cité un bon @35niveau&de&culture. @L@LPour en savoir plus sur la religion dans l'Egypte ancienne, cliquez @399ici."
        }
    }

    message_game_concept_war {
        id: 52
        
        size [30, 28]
        title {
            text: "Guerre"
        }
        subtitle {
            text: "Concepts du jeu",
        }
        content {
            text: "La guerre est presque une menace permanente en Egypte. Parfois, des envahisseurs venus d'autres pays s'introduisent en Egypte dans l'intention d'accroître leur puissance. Il arrive également que les troubles au sein de l'Egypte engendrent des guerres intestines entre les cités, voire une guerre civile proprement dite. Parfois encore, le pharaon en personne décide de mener une guerre contre un ennemi juré ou un allié rebelle. @PDe nombreuses possibilités s'offrent à vous pour préparer votre cité et la protéger contre les horreurs de la guerre. Construisez des @85structures&défensives afin de protéger les frontières de la cité de toute force d'invasion. Construisez également des @37forts, des @356navires&de&guerre et des @357transporteurs pour attaquer tout ennemi qui pénètre à l'intérieur de la cité. @PVotre @21chef&militaire vous avertit si une attaque se prépare et vous recevez des @34messages vous indiquant les mouvements militaires ennemis. Vous pouvez ainsi tracer la trajectoire des troupes ennemies en approche sur la @32mappemonde. @PVeillez à ne pas provoquer d'attaque. Si vous ne gérez pas votre cité correctement ou provoquez l'animosité d'autres cités d'Egypte, votre @35niveau&du&royaume chutera. S'il descend trop bas, votre cité risque d'être attaquée. @PLa guerre ne se limite pas aux environs de votre cité. L'Egypte peut être engagée dans des conflits internes et internationaux. Il arrive parfois qu'une autre cité ou qu'un pharaon ait besoin d'une partie de vos troupes ou de vos navires de guerre pour vaincre un ennemi. Vous devez alors envoyer ces troupes au service de ce royaume en consultant votre chef militaire. Vous devez affecter certaines compagnies ou navires au service à l'étranger. Si plusieurs cités ont besoin d'aide, vous devez consulter votre @22chef&politique pour choisir la cité à assister. @L@LPour en savoir plus sur les ennemis de l'Egypte ancienne, cliquez @181ici."
        }
    }

    message_tutorial_health {
        id: 53
        
        size [30, 28]
        title { text: "Hygiène" }
        subtitle { text: "Concept du jeu" }
        content {
            text: "La mauvaise hygiène de votre cité risque de décourager l'immigration, voire d'entraîner le décès d'une partie des habitants. Vous devez prendre des mesures afin d'assurer la bonne santé de vos citoyens. Sinon, certaines catastrophes risquent de survenir. @PPour assurer la bonne santé de vos citoyens, faites en sorte qu'ils aient accès à une quantité suffisante de nourriture ainsi qu'à un @64dispensaire. Plus la variété de nourriture consommée par vos citoyens est grande, plus ils ont de chances de rester en bonne santé. L'accès aux @66salles&d'embaumeurs améliore également l'hygiène générale de la cité. L'accès à de l'eau potable provenant d'un @61point&d'eau ainsi que l'accès à une @65pharmacie contribuent en outre à réduire le risque de malaria. Les conditions générales d'hygiène de votre cité sont déterminées par la santé de chaque citoyen. Vous devez donc veiller à assurer un accès adéquat aux soins médicaux à tous les habitants. @POutre la malaria, la peste touche la cité. Une gestion rigoureuse et une surveillance constante de l'hygiène des habitants permettent d'éviter ces problèmes de santé. @L@LMaladies @LLa maladie touche les foyers qui ne sont pas souvent visités par un médecin et ne bénéficient pas d'un approvisionnement régulier en nourriture. La maladie frappe les foyers individuellement, sans se propager. En revanche, si tout un quartier bénéficie d'un très mauvais accès aux médecins et à la nourriture, plusieurs foyers risquent d'être touchés par la maladie. @PUtilisez la @18carte&des&risques pour connaître les foyers les plus exposés à la maladie. Construisez d'autres dispensaires dans ces zones et faites en sorte que les @2bazars approvisionnent les habitations en nourriture. Vous pouvez également utiliser la @18carte&des&médecins pour connaître les foyers qui bénéficient d'un accès adéquat aux médecins et la @18carte&de&l'accès&aux&bazars pour connaître ceux visités par les marchands de bazar. @L@LMalaria @LLa malaria est l'un des risques de la vie à proximité d'un cours d'eau. Les habitations situées à proximité du fleuve ou des marécages regorgeant de roseaux sont les plus touchées. La malaria touche les foyers individuellement. Cette maladie, toutefois, est susceptible de se propager. Pour combattre le risque de malaria, vous devez construire de nombreuses pharmacies dans les zones exposées et faire en sorte que les habitations de ces zones reçoivent de l'eau provenant d'un point d'eau. Utilisez la @18carte&de&la&malaria pour connaître les habitations les plus exposées à cette maladie. @L@LPeste @LLes épidémies de peste ont lieu lorsque les conditions générales d'hygiène d'une cité sont mauvaises, quelle que soit l'hygiène de chaque habitation. La seule façon d'éviter la peste est d'assurer de bonnes conditions d'hygiène dans votre cité. Ne confondez pas la peste avec les @494grands&fléaux. Les grands fléaux sont imputables à des facteurs qui échappent totalement à votre contrôle, et non à l'hygiène dans la cité. @PLorsqu'une épidémie de peste se déclare, elle commence dans un foyer. L'un des membres de ce foyer, atteint par cette maladie parcourt les rues, contaminant toutes les habitations sur son passage. En un mois, il succombe. Un herboriste travaillant dans une pharmacie supprime rapidement tous les pestiférés qu'il rencontre. @PAucune carte n'indique l'habitation qui abritera la première victime de la peste, car cette maladie n'est pas liée aux conditions d'hygiène d'une habitation ou d'un quartier en particulier. @L@PSi une habitation est touchée par l'une des affections ci-dessus, tous les habitants de cette maison mourront. Ce foyer reste infecté pendant deux mois, durant lesquels aucun immigrant ou vagabond ne s'introduit dans cette maison. Au bout de deux mois, le foyer est assaini et de nouveau vivable. Tous les biens appartenant aux précédents habitants y demeurent. @PLe cabinet dentaire, que l'on considère comme une structure de soins médicaux, contribue à assurer la valeur immobilière d'un quartier et n'a aucun effet sur l'hygiène de la cité. @PVotre @26chef&de&l'hygiène vous aide à assurer la bonne santé de vos citoyens."
        }
    }

    message_bent_pyramid {
        id: 54,
        
        size [30, 28]
        title {
            text: "Pyramide penchée",
        }
        content {
            text: "Les architectes à l'origine de la pyramide penchée souhaitaient créer un obélisque géant dont les côtés obliques polis rappelleraient les rayons du soleil en réfléchissant la lumière de l'astre sacré. @PLa construction d'une pyramide penchée nécessite un approvisionnement en @95pierre et en @95calcaire ainsi que des ouvriers d'un @8chantier. Lorsque l'@4entrepôt contient quatre blocs de pierre ou de calcaire, les paysans transportent sur des traîneaux la marchandise jusqu'au site de construction. Seule la @363guilde&de&tailleurs&de&pierre est qualifiée pour poser les blocs de pierre. Les @363menuisiers construisent des rampes avec les réserves de bois de la &guilde. @PIl existe deux types de pyramides penchées. Pour en savoir plus, consultez les rubriques @370Construction&de&monuments, @373Chef&des&monuments et @369Contremaître. @L@LPour en savoir plus sur l'histoire de la pyramide penchée, cliquez @392ici."
        }
    }

    message_brick_core_pyramid {
        id: 55,
        
        size [30, 28]
        title {
            text: "Pyramide en briques",
        }
        content {
            text: "Les pyramides sont les monuments les plus grands et les plus complexes que vous puissiez bâtir. Les pyramides en briques sont des monuments très complexes car elles nécessitent l'emploi de trois types de matières premières (@364brique, @95calcaire et @94bois) et la mobilisation de trois guildes de constructeurs (@363tailleurs&de&pierre, @363maçons et @363menuisiers). Vous devrez également faire appel aux paysans d'un @8chantier pour amener les lourds chargements de briques de l'@4entrepôt au site de construction. @PIl existe cinq types de pyramides en briques : petite, moyenne, grande, ensemble de pyramides et grand ensemble de pyramides. @PPour en savoir plus, consultez les rubriques @370Construction&de&monuments, @373Chef&des&monuments et @369Contremaître. @L@LPour en savoir plus sur l'histoire de la pyramide en briques, cliquez @392ici."
        }
    }

    message_housing_and_desirability {
        id: 56
        
        size [35, 32]
        title { text: "Logements et attrait" }
        content {
            text: "La première étape de la construction d'un quartier consiste à désigner une zone d'habitation. Souvenez-vous que toutes les habitations doivent se trouver à proximité d'une route. Après avoir défini une zone, les immigrants peuvent s'y installer dans de simples huttes. Ces habitants parcourent alors les environs à la recherche de ce dont ils ont besoin pour survivre. Au fil du temps, cependant, les habitants s'attendent à ce que la cité satisfasse leurs besoins. Si vous répondez à ces besoins, les habitants font de leur mieux pour améliorer leur habitat. La qualité de l'habitat affecte les @35niveaux de la cité, empêche les habitants d'émigrer et attire de nouveaux habitants. @PLes besoins de base des citoyens sont l'accès à l'@44eau&potable et à la @45nourriture en provenance des @2bazars. Une fois que ces deux types de besoins sont satisfaits, vous remarquerez que les huttes deviennent des cabanes et des chaumières. @PAprès la nourriture et l'eau, les habitants exigent d'autres biens et services. Les citoyens veulent des @1poteries, de la @96bière et de la @60toile pour leurs maisons. Les citoyens les plus riches exigent également certains @99articles&de&luxe, tels que des bijoux. A mesure que leurs goûts s'affinent, les habitants demandent des articles de luxe importés. Outre ces biens, les habitants veulent avoir accès à leurs services préférés, tels que la @51religion, les @49loisirs, l'@50éducation et les @53soins&médicaux. Le fait de pouvoir accéder à ces biens et services incite les habitants à améliorer leurs maisons en les transformant en des structures spacieuses et confortables. @PLes habitants apprécient en outre de vivre dans des quartiers agréables. Vous pouvez établir de beaux @79jardins et construire des @79statues, ou recouvrir les routes pavées de @79mosaïques. Les citoyens apprécient les efforts entrepris pour embellir leur environnement et se feront un plaisir d'améliorer leur habitat en conséquence. @PLes personnes qui souhaitent habiter dans des quartiers agréables ne tiennent pas a le connaître dans une condition différente. Les habitants se plaignent si leurs maisons se trouvent à proximité d'industries ou de fermes. Ils préfèrent grandement habiter loin des sources de bruit et de mauvaises odeurs que constituent généralement ces structures. Egalement, la plupart des habitants trouvent les structures industrielles horribles. Si vous devez placer des habitations à proximité d'industries (et c'est parfois le cas pour assurer la présence de main-d'oeuvre dans les industries), vous devez essayer de compenser cet inconvénient en prévoyant des jardins, des statues et des plazas et en assurant le meilleur accès possible aux biens et services. En outre, vous devrez sans doute vous résigner à installer certains quartiers résidentiels dans votre cité. @PUn habitat de grande qualité comporte de nombreux avantages. Cela a en effet un impact positif sur votre @35niveau&de&prospérité. Les habitations évoluées peuvent, en outre, accueillir davantage de résidents, ce qui vous permet d'accroître la population de votre cité et ainsi sa main-d'oeuvre potentielle, sans avoir besoin de construire de nouvelles zones d'habitation. Une fois que vos habitations ont atteint le niveau le plus élevé, les résidents deviennent des @41scribes, qui payent des impôts mais ne font pas partie de la main-d'oeuvre de la cité. @PPour savoir ce dont une habitation spécifique a besoin pour se développer, cliquez sur cette habitation avec le bouton droit de la souris. Les habitants n'hésiteront pas à vous faire part de leurs besoins. @L@LLes Egyptiens anciens vivaient dans des maisons de tailles et de qualités variables. Cliquez @152ici pour en savoir plus."
        }
    }
    
    message_game_concept_roads {
        id: 57,
        
        size [30, 28]
        title {
            text: "Routes",
        }
        content {
            text: "Les routes sont toujours de vulgaires chemins au départ. Au fur et à mesure que les conditions de vie s'amélioreront dans votre cité, vos citoyens décideront de paver les routes. Ce n'est qu'une fois la route pavée, que vous pourrez y placer des @79plazas.  @PLes routes correctement conçues sont fort utiles au fonctionnement de votre cité. Les @42piétons qui offrent des services à votre cité circulent plus facilement sur de longues routes droites que sur de petites routes pleines de tournants et de carrefours. @PPresque toutes les structures de votre cité doivent avoir un accès routier. Les seules exceptions sont les jardins, les statues et les forts. Ces structures ne nécessitent aucun accès à la route mais doivent être installées à au moins deux espaces d'une voie pour être accessibles aux passants. @PLes piétons ne peuvent que traverser la frontière entre la plaine inondable et la terre sèche où se trouve une route. Cette digue est abrupte et boueuse, mais une route permet d'y accéder en toute sécurité. @PToutes les routes ont la même capacité de circulation et les piétons y circulent à la même vitesse, qu'elles soient ou non pavées. @L@LRoute du royaume @LLa route qui traverse vos terres lorsque vous commencez une nouvelle mission est la route du royaume. Elle a un statut particulier. Des caravanes de marchands et d'immigrants arrivent sur la route du royaume et des émigrants l'empruntent pour quitter la cité. Chaque partie de votre cité doit avoir un accès dégagé à la route du royaume. Si vous isolez une partie de la cité de cet axe, cette zone risque de stagner. Tous les livreurs en route pour l'enclave désormais isolée vont s'arrêter jusqu'à ce que l'accès soit rétabli. Parfois, les architectes royaux suppriment toute structure bloquant l'accès.  @PCela ne signifie pas que chaque rue de votre cité doit être physiquement reliée à la route du royaume. Tous les bâtiments doivent avoir un accès dégagé et piétonnier, via une route ou un terrain vierge. @PVous n'avez pas besoin d'en savoir plus sur la route du royaume. Les points les plus complexes de l'accès aux bâtiments ne concerneront jamais la plupart des joueurs, mais il existe de rares circonstances dans lesquelles vous risquez de perdre l'accès à la route du royaume sans créer d'obstruction visible. @PLorsque vous construisez une nouvelle structure, celle-ci a besoin d'un accès à la route du royaume, via le réseau routier de votre cité ou via un chemin piétonnier ouvert. Dans la plupart des cas, vous placez la structure sur une route existante. L'accès à la route du royaume est donc primordial. Parfois, cependant, vous pouvez construire une structure qui ne se trouve pas sur une route. Dans ce cas, la nouvelle structure recherche un accès à la route du royaume sur la route ouverte. Si vous connectez ensuite ce bâtiment à une rue de la cité, celui-ci redéfinit son point d'accès pour se trouver sur la nouvelle rue. Si la nouvelle rue ne trouve pas d'accès piétonnier à la route du royaume (il se peut que cet accès soit bloqué par le bâtiment que vous venez de connecter), le bâtiment relié à cette route perd également l'accès à la route du royaume. @PPour en savoir plus sur les 'points d'accès', lisez la section suivante. @PUn dernier point sur la route du royaume : il n'y a rien de particulier sur la route en elle-même, si ce n'est que les points qui la connectent à votre territoire sont cruciaux. Vous pouvez déplacer les parties de la route du royaume tout comme n'importe quelle autre route de votre cité, tant que vous ne bloquez pas l'accès à ces points vitaux d'entrée et de sortie. @L@LConstruction sur deux routes @LIl arrive que vous placiez un bâtiment à proximité de deux routes qui soit ne sont pas reliées entre elles, soit bénéficient d'une connexion éloignée de ce bâtiment. Cela ne permet pas aux piétons de quitter le bâtiment ou d'y entrer depuis ces deux routes. Tout bâtiment peut n'avoir qu'un seul 'point d'accès', donc une seule route active. @PSupposons, par exemple, que vous construisiez un entrepôt avec une route sur son côté sud. Les fabricants, les marchands et les acheteurs de bazar au sud de l'entrepôt interagissent avec cette route. Supposons maintenant que vous ayez besoin d'industries au nord de l'entrepôt. Si vous établissez une route au nord de l'entrepôt, il se peut que les industries situées au nord de cette structure interagissent avec cet entrepôt via la route située au nord, tandis que les industries situées au sud de cet entrepôt continuent à utiliser la route située au sud. Le bâtiment ne peut toutefois avoir qu'un point d'accès. Vous devez dans ce cas établir une connexion entre les routes du nord et du sud. @PSi un bâtiment n'est pas situé à proximité de plusieurs routes, il doit désigner son point d'accès en fonction du réseau routier le plus étendu. Dans le même cas, si la route du nord fait partie du principal réseau de rues de votre cité, tandis que la nouvelle route du nord mène à un petit avant-poste industriel, le 'point d'accès' de l'entrepôt se trouve sur la route du sud. Si, en revanche, la route du sud d'origine mène à une plus petite colonie et que la nouvelle route du nord est reliée à la cité principale, la route du nord constitue le meilleur accès à ce bâtiment. @PAfin d'éviter toute réaction imprévue, vous devez veiller à ne pas construire de bâtiment reliant deux routes non connectées entre elles. Vous devez les connecter entre elles ou vous assurer que seule l'une d'entre elles est susceptible d'accueillir un trafic lié au bâtiment. Vous devez observer le comportement des piétons afin de déterminer quelle route constitue le point d'accès de ce bâtiment. @L@LCliquez @153ici pour parcourir l'histoire des routes dans l'Egypte ancienne."
        }
    }

    message_game_concept_water_crossings {
        id: 58,
        
        size [30, 28]
        title {
            text: "Gués",
        }
        content {
            text: "Il existe deux types de traverses d'eau : les ponts et les embarcadères. Les ponts ne peuvent traverser que de petites étendues d'eau. Les navires ne peuvent pas passer sous les ponts. Vous devez donc veiller à ne pas les utiliser si l'étendue d'eau qu'ils traversent est fréquentée par des navires. @PLes ponts ne peuvent être placés qu'aux endroits où le rivage est droit. Il faut en outre que la rive opposée soit droite. Dès que vous avez repéré un endroit approprié pour installer un pont, une 'empreinte' verte de ce pont apparaît (le coût du pont dépend du nombre d'espaces utilisés). Si vous n'avez pas repéré d'endroit approprié, vous voyez apparaître des carrés rouges. Les ponts ne requièrent aucune main-d'oeuvre, mais doivent avoir accès à une route. @PLes navettes sont amarrées à des embarcadères et fonctionnent comme des ponts, tout en ayant d'autres usages. Les navettes ne barrent pas le passage des autres bateaux. Toutes sortes de navires peuvent donc naviguer à leur guise. @PComme les ponts, les embarcadères doivent être placés sur une rive droite de la côte. Lorsque vous sélectionnez un endroit approprié, vous voyez apparaître un carré vert. Vous n'avez pas besoin de placer le second embarcadère juste en face du premier. Vous avez le choix entre plusieurs endroits sur la rive opposée, du moment que le rivage est droit. Des blocs verts signalent les endroits choisis. @PComme les immigrants ont leurs propres bateaux, ils peuvent utiliser les embarcadères dès leur construction. Les embarcadères ont besoin de main-d'oeuvre pour transporter d'autres citoyens. Les @42piétons qui ont une destination spécifique, tels que les livreurs, les acheteurs de bazar et les artistes, utilisent les navettes. Aucun autre type de piéton n'est autorisé à utiliser les navettes. @PLes embarcadères n'ont pas besoin d'un accès routier pour transporter les immigrants. Les immigrants traversent les champs pour se rendre à l'embarcadère. Les embarcadères ont néanmoins besoin d'un accès routier pour transporter d'autres citoyens. @L@LComme le @157Nil traversait leur territoire, les Egyptiens anciens utilisaient différents types d'embarcations pour le transport des hommes et des marchandises. Pour en savoir plus sur la fabrication des bateaux dans l'Egypte ancienne, cliquez @179ici."
        }
    }
    
    message_game_concept_irrigation {
        id: 59,
        
        size [30, 28]
        title {
            text: "Irrigation",
        }
        content {
            text: "Les chadoufs et les rigoles d'irrigation permettent d'étendre les bienfaits du Nil. Les terres irriguées sont plus fertiles. @PPour irriguer une ferme, installez une rigole d'irrigation à deux espaces de la ferme. Les effets de l'irrigation ne peuvent être cumulés ; tant qu'une rigole d'irrigation est installée à deux espaces de la ferme, celle-ci sera parfaitement irriguée. @PLes fermes des plaines inondables étant au niveau de l'eau, les rigoles d'irrigation peuvent être directement connectées au Nil. Pour les fermes situées sur les prairies, donc en hauteur, la mise en place d'un chadouf est obligatoire. @PLe chadouf est un système qui permet de faire monter l'eau d'un niveau. Il peut être construit sur une terre adjacente à un point d'eau ou à une plaine inondable. Pour construire un chadouf adjacent à une plaine inondable, vous devez faire courir une rigole d'irrigation du Nil au chadouf pour l'approvisionner en eau. @PPour irriguer une ferme de prairie, vous devez raccorder une rigole d'irrigation à un chadouf. Les rigoles d'irrigation contournent tous les obstacles se trouvant sur leur chemin, excepté les routes. Les rigoles d'irrigation passent automatiquement sous les routes, si nécessaire. @PUne fertilité accrue de la terre augmentera la quantité de nourriture produite par la ferme. La fertilité n'a aucun effet sur la longueur de la saison des récoltes. @PCependant, même les fermes irriguées doivent être établies sur des terres arables. L'irrigation peut augmenter la fertilité de la terre, mais ne peut pas rendre fertile une terre infertile. @PPour plus d'informations, consultez la rubrique @45Agriculture. @L@LDans l'Egypte ancienne, la découverte des techniques d'irrigation a permis d'accroître considérablement la surface de terres cultivables. Pour en savoir plus sur l'irrigation, cliquez @154ici."
        }
    }
    
    message_building_weaver {
        id: 60,
        
        size [30, 28]
        title {
            text: "Atelier de tissage",
        }
        content {
            text: "Les ateliers de tissage servent à transformer les fibres de lin en toile. Le lin peut être cultivé sur des @91exploitations&de&lin ou importé par le biais d'un @47partenaire&commercial. Les ateliers de tissage ont besoin de main-d'oeuvre et d'un accès à la route. De petites quantités de lin peuvent être stockées sur site pour occuper la main-d'oeuvre continuellement malgré quelques problèmes d'approvisionnement. @PLa toile est d'une importante valeur marchande pour une cité. Cet élément est essentiel pour l'embaumement et les @66salles&des&embaumeurs ont besoin de toile pour fonctionner correctement. En outre, les citoyens apprécient d'avoir un stock de toile chez eux pour leur habillement.  @L@LPour en savoir plus sur l'importance de la toile dans l'Egypte ancienne et le tissage, cliquez @398ici."
        }
    }
    
    message_building_water_supply {
        id: 61,
        
        size [30, 28]
        title {
            text: "Point d'eau",
        }
        content {
            text: "Les points d'eau et les porteurs d'eau fournissent de l'@44eau&potable à la cité. L'accès à l'eau provenant d'un point d'eau est l'une des premières choses que les habitants demandent pour améliorer leur @56logement. @PLes points d'eau nécessitent un accès routier et de la main-d'oeuvre et doivent être placés sur des herbages, qui indiquent la présence de nappes phréatiques. Ils ne peuvent pas être placés dans le désert. @PDès qu'un point d'eau dispose des conditions nécessaires à son fonctionnement, il envoie un porteur d'eau. Ce dernier parcourt votre cité et distribue de l'eau potable aux habitations. Il est important de consulter régulièrement vos porteurs d'eau afin de vous assurer que votre cité est correctement approvisionnée en eau potable. Utilisez la @18carte&des&ressources&en&eau pour connaître les maisons fréquemment visitées par un porteur d'eau. Les porteurs d'eau sont des @42promeneurs. @PLes porteurs d'eau vont augmenter leur cadence de travail si leur point d'eau est amélioré. Lorsque l'attrait des environs est suffisant, les travailleurs affectés au point d'eau vont améliorer le bâtiment et les porteurs d'eau vont circuler plus souvent dans le voisinage. @PSeuls les logements ont besoin de recevoir de l'eau provenant d'un point d'eau. Les habitants apprécient que leur maison se trouve à proximité d'un point d'eau (pour plus d'informations, consultez la rubrique @56Attrait).  @L@LCliquez @156ici pour en savoir plus sur l'approvisionnement en eau potable dans l'Egypte ancienne."
        }
    }

    message_building_well {
        id: 62,
        
        size [30, 28]
        title {
            text: "Puits",
        }
        content {
            text: "Les puits sont une source d'@44eau&potable rudimentaire. Seuls les quartiers les plus pauvres se satisfont d'un accès à des puits. L'accès à un @61point&d'eau est nécessaire au développement de l'habitat. @PLes puits n'ont besoin ni d'un accès routier, ni de main-d'oeuvre. Les puits doivent être placés sur des herbages, qui indiquent la présence de nappes phréatiques. Les puits ont un effet légèrement positif sur l'@56attrait des quartiers environnants. @PConsultez la @18carte&des&ressources&en&eau pour connaître les zones qui ont accès à l'eau provenant de puits. @L@LPour en savoir plus sur les puits dans l'Egypte ancienne, cliquez @156ici."
        }
    }

    message_building_dentist {
        id: 63,
        
        size [30, 28]
        title {
            text: "Dentiste",
        }
        content {
            text: "Les habitants les plus riches apprécient de pouvoir consommer des aliments solides et l'accès à un cabinet dentaire pour préserver ou remplacer leurs dents naturelles. Dans un pays où le sable s'introduit inévitablement dans les aliments, les dentistes ne manquent jamais de travail. Les dentistes améliorent l'@56attrait des logements, mais ils n'ont aucun effet sur l'@53hygiène&de&la&cité. @PUtilisez la @18carte&de&l'hygiène pour voir les dentistes à l'oeuvre dans votre cité. @L@LCliquez @158ici pour en savoir plus sur le rôle des dentistes dans l'Egypte ancienne."
        }
    }

    message_building_physician {
        id: 64,
        
        size [30, 28]
        title {
            text: "Médecin",
        }
        content {
            text: "Les médecins permettent de maintenir l'@53hygiène&de&la&cité à un bon niveau. Leurs visites permettent de réduire les risques de maladie. @PLes citoyens apprécient la présence d'un dispensaire à proximité et leur absence freine l'@56évolution&de&l'habitat. @PLes dispensaires nécessitent de la main-d'oeuvre et un accès routier. @PUne visite au @26chef&de&l'hygiène vous permet de faire le bilan de la couverture médicale dans votre cité. @L@LCliquez @160ici pour en savoir plus sur les pratiques médicales dans l'Egypte ancienne."
        }
    }

    message_building_apothecary {
        id: 65,
        
        size [30, 28]
        title {
            text: "Pharmacie",
        }
        content {
            text: "Les pharmacies sont des structures qui emploient des herboristes. Ces derniers suppriment tous les @53pestiférés qu'ils rencontrent sur leur chemin. Les pharmacies permettent de réduire le risque de @53malaria. @PPour fonctionner, les pharmacies nécessitent un accès à la route et de la main-d'oeuvre. Pour suivre la trace de vos herboristes, utilisez la @18carte&de&l'hygiène. Vous y verrez tous les herboristes et les pharmacies de la cité, ainsi que l'accès de chaque maison aux services des herboristes. @PConsultez votre @26chef&de&l'hygiène pour en savoir plus. @L@LPour en savoir plus sur les pratiques pharmaceutiques des Egyptiens anciens, cliquez @159ici."
        }
    }

    message_building_mortuary {
        id: 66,
        
        size [30, 28]
        title {
            text: "Salle des embaumeurs",
        }
        content {
            text: "Dans ces salles, les embaumeurs préparent le corps des défunts pour leur dernier voyage vers l'au-delà. @PLes salles des embaumeurs améliorent l'@53hygiène&de&la&cité en s'occupant correctement des morts. Comme la plupart des bâtiments, les salles d'embaumeurs ont besoin d'un accès à la route et à la main-d'oeuvre. Il leur faut également de la @60toile fabriquée dans la cité ou importée par le biais d'un @47partenaire&commercial. Les embaumeurs utilisent la toile pour envelopper le corps des défunts après l'embaumement. @PBien que les citoyens exigent d'avoir accès aux salles d'embaumeurs, ils n'apprécient guère d'habiter à proximité de ces structures. Les salles d'embaumeurs sont connues pour l'odeur pestilentielle qui s'en dégage. @PPour savoir où se trouvent les salles d'embaumeurs, utilisez la @18carte&de&l'hygiène. Vous y verrez les embaumeurs s'occuper des morts et parcourir votre cité. Votre @26chef&de&l'hygiène peut vous informer sur les services d'embaumement de votre cité. @L@LL'embaumement était lié à la croyance des Egyptiens anciens dans l'au-delà. Cliquez @161ici pour en savoir plus sur cette pratique ancienne."
        }
    }

    message_building_shrine_and_temple {
        id: 67,
        
        size [30, 28]
        title {
            text: "Sanctuaire et temple",
        }
        content {
            text: "Vous ne pouvez pas apaiser les dieux sans la présence de sanctuaires et de temples. Les divinités locales, tout comme les divinités protectrices requièrent de l'attention. Les citoyens ont donc besoin d'un accès à la religion. Pour plus de détails concernant l'influence des dieux sur votre cité, voir la rubrique @51religion. Pour en savoir plus sur l'effet particulier de chaque ensemble de temples, choisissez : @L@P@350Ensemble&de&temples&d'Osiris @P@351Ensemble&de&temples&de&Rê @P@352Ensemble&de&temples&de&Ptah @P@353Ensemble&de&temples&de&Seth @P@354Ensemble&de&temples&de&Bastet @L@PLes sanctuaires sont de petits monuments dédiés à une divinité particulière. Ils ne nécessitent aucun accès à la route mais doivent être installés à au moins deux espaces d'une voie afin que les pompiers et architectes puissent intervenir. Ils n'ont pas besoin de main-d'oeuvre et ne produisent pas de piétons. Ils ne donnent donc pas accès à la religion. Leur principal rôle est d'apaiser les dieux. @PPour installer des lieux de culte et apaiser davantage les dieux, construisez des temples. Les temples nécessitent un accès à la route et la présence d'un groupe de prêtres. Lorsqu'un temple est fonctionnel, les prêtres offrent des services religieux à vos habitants. Comme les sanctuaires, les temples sont dédiés à une divinité particulière. @G73 @PLes temples et les sanctuaires améliorent la @56valeur&immobilière des quartiers où ils sont situés. Les sanctuaires et les temples contribuent également à améliorer le @35niveau&de&culture de la cité.  @L@LLa religion était au centre de la vie des Egyptiens anciens. Pour en savoir plus sur cet aspect important de la culture dans l'Egypte ancienne, cliquez @399ici."
        }
    }

    message_building_scribal_school {
        id: 68,
        
        size [30, 28]
        title {
            text: "Ecole de scribes",
        }
        content {
            text: "Les écoles de scribes forment la jeunesse aisée de la cité. @PPour fonctionner, les écoles nécessitent un accès à la route et de la main-d'oeuvre. Elles ont également besoin de @97papyrus. Lorsqu'une école fonctionne correctement, les enseignants parcourent les rues pour former les étudiants chez eux. Chaque fois qu'un professeur quitte l'école de scribes, il emporte quelques papyrus afin que ses élèves puissent étudier les hiéroglyphes. Chaque école de scribes peut contenir une petite quantité de papyrus. Pour que les écoles puissent continuer à fonctionner, veillez à ce que l'industrie du papyrus soit florissante dans votre cité ou que vous en importez suffisamment d'un @47partenaire&commercial. @PVotre @27chef&de&l'éducation sait combien votre cité compte d'écoles de scribes. La @18carte&de&l'éducation vous indique où toutes les écoles de scribes sont situées et les maisons qui ont accès à des enseignants. Les écoles de scribes contribuent également à améliorer le @35niveau&de&culture d'une cité. @L@LDe nombreux Egyptiens anciens considéraient l'école comme un passeport vers un avenir réussi. Cliquez @163ici pour en savoir plus sur cette institution de l'Egypte ancienne."
        }
    }

    message_building_sun_temple {
        id: 69,
        
        size [30, 28]
        title {
            text: "Temples solaires",
        }
        content {
            text: "Les temples solaires honorent le culte du soleil, très respecté par la plupart des pharaons. @PPour construire un temple solaire, plusieurs éléments sont nécessaires : du @94sable, du @95grès, la mobilisation d'une &guilde de @363menuisiers, de @363&tailleurs de pierre ainsi qu'un @8&chantier. @PLa construction des temples solaires commence par la mise en place d'un obélisque en grès. Vous devez auparavant avoir stocké la quantité de grès nécessaire dans l'@4entrepôt de votre cité. Vous pouvez ensuite commencer à bâtir le temple solaire. Cliquez sur le bouton Structures religieuses, sélectionnez l'option Temple solaire dans le sous-menu Monuments, puis choisissez un endroit sur la carte. Si l'endroit convient, une empreinte de couleur verte apparaît. Si une partie de cette empreinte affiche un losange rouge, cela signifie que ce terrain ne permet pas la construction de monuments. Cliquez pour commencer la construction de l'obélisque de grès dans le temple solaire.  @PUne fois les blocs de pierre en place, les menuisiers installent des échafaudages tout autour de l'obélisque. Les tailleurs de pierre peuvent ainsi commencer à décorer les côtés du monument. Lorsque l'obélisque est terminé, les ouvriers poursuivent la construction du temple solaire. Ils bâtissent un vestibule puis un mur de pierre. Les tailleurs de pierre construisent ensuite l'avant-temple. Pour cela, les paysans doivent apporter aux tailleurs de pierre plusieurs cargaisons de grès. En construisant l'avant-temple, le mur et le vestibule, les tailleurs de pierre posent des motifs de décoration entre les murs. @PUne fois l'avant-temple construit et les motifs de décoration posés, le temple solaire est terminé. @PConsultez votre @369contremaître pour obtenir un bilan des constructions. Une visite au @373chef&des&monuments peut s'avérer utile. @L@LPour en savoir plus sur les temples solaires et les autres monuments, cliquez @396ici."
        }
    }

    message_building_library {
        id: 70,
        
        size [30, 28]
        title {
            text: "Bibliothèque",
        }
        content {
            text: "Les citoyens érudits doivent avoir accès aux bibliothèques. Les bibliothèques améliorent la valeur immobilière ainsi que le @35niveau&de&culture de la cité. @PLes bibliothèques seraient inutiles sans rayons de papyrus. Avant de pouvoir construire une bibliothèque, il faut stocker du @97papyrus dans les @4entrepôts. Une fois la bibliothèque construite, elle a besoin d'un stock de papyrus pour fonctionner correctement. @PPour fonctionner, les bibliothèques nécessitent un accès à la route et de la main-d'oeuvre. Une fois que la bibliothèque a tout ce dont elle a besoin, elle envoie un bibliothécaire dans la communauté locale. Chaque fois qu'un bibliothécaire quitte la bibliothèque, il emporte avec lui du papyrus pour que la population découvre la littérature. @PPour connaître le nombre de bibliothèques que compte votre cité, consultez votre @27chef&de&l'éducation. Pour connaître l'emplacement de chaque bibliothèque, utilisez la @18carte&de&l'éducation. Cette carte indique les bibliothèques et vous permet de suivre les bibliothécaires dans leurs tâches quotidiennes. @L@LPour en savoir plus sur la tradition littéraire et les bibliothèques dans l'Egypte ancienne, cliquez @164ici."
        }
    }

    message_building_booth {
        id: 71,
        
        size [30, 28]
        title {
            text: "Etal",
        }
        content {
            text: "Les étals sont les structures de @49loisirs les plus petites et les moins chères. Un étal comporte un théâtre abritant des jongleurs qui amusent la foule par des numéros acrobatiques défiant les lois gravitationnelles. @PLes étals ont besoin d'un accès routier spécifique : ils doivent être placés à un carrefour ou à un croisement en 'T'. Les étals doivent également avoir une main-d'oeuvre suffisante et des jongleurs entraînés. La main-d'oeuvre assure le contrôle de la foule et subvient aux besoins des jongleurs lorsqu'ils s'entraînent. Les jongleurs s'entraînent dans les @75écoles&de&jonglerie et peuvent également se produire dans les @72kiosques et les @73pavillons. @PLes maisons doivent avoir accès aux loisirs pour @56évoluer. Les jongleurs font donc évoluer toutes les maisons où ils se rendent. Le fait d'avoir un étal dans une cité améliore l'attrait de cette cité. Les étals actifs contribuent également à améliorer le @35niveau&de&culture de la cité.  @PConsultez votre @28chef&des&loisirs pour connaître le nombre de jongleurs qui travaillent dans votre cité. La @18carte&des&loisirs indique les lieux où les jongleurs se produisent et vous permet de suivre le trajet de ces artistes à travers les rues de votre cité. @L@LLes Egyptiens anciens furent parmi les premiers jongleurs. Cliquez @169ici pour en savoir plus."
        }
    }

    message_building_bandstand {
        id: 72,
        
        size [30, 28]
        title {
            text: "Kiosque",
        }
        content {
            text: "Les kiosques sont des lieux de loisirs de taille moyenne comportant deux scènes : une pour les jongleurs et l'autre pour les concerts. La scène des jongleurs est située à un angle du bâtiment et la scène des musiciens à l'autre.  @PLes kiosques doivent être placés à un carrefour ou à un croisement en 'T'. Ils ont besoin de leur propre main-d'oeuvre pour s'occuper des artistes, de jongleurs entraînés et de musiciens. Les artistes sont formés dans les @75centres&d'entraînement. @PLes maisons doivent avoir accès aux loisirs pour @56évoluer. Les jongleurs et les musiciens font donc évoluer toutes les maisons où ils se rendent. Le fait d'avoir un kiosque dans une cité améliore l'attrait de cette cité. Les kiosques actifs contribuent également à améliorer le @35niveau&de&culture de la cité.  @PConsultez votre @28chef&des&loisirs pour connaître le nombre de jongleurs et de musiciens qui travaillent dans votre cité. La @18carte&des&loisirs indique les lieux où les artistes se produisent et vous permet de suivre leur trajet à travers les rues de votre cité. @L@LLes Egyptiens anciens étaient d'excellents musiciens. Pour en savoir plus, cliquez @170ici. Pour en savoir plus sur la jonglerie dans l'Egypte ancienne, cliquez @169ici."
        }
    }

    message_building_pavilion {
        id: 73,
        
        size [30, 28]
        title {
            text: "Pavillon",
        }
        content {
            text: "Le pavillon, le plus important lieu de loisirs, comporte trois scènes : une pour les jongleurs, une pour les musiciens et une pour les danseurs. Beaucoup de personnes souhaitent vivre à proximité d'un pavillon. @PLes pavillons doivent être placés à un carrefour ou à un croisement en 'T'. Ils ont besoin de leur propre main-d'oeuvre pour s'occuper des artistes, de jongleurs entraînés, de musiciens et de danseurs. Les artistes sont formés dans les @75centres&d'entraînement. @PLes maisons doivent avoir accès aux loisirs pour @56évoluer. Les artistes font donc évoluer toutes les maisons où ils se rendent. Le fait d'avoir un pavillon dans une cité améliore l'attrait de cette cité. Les pavillons actifs contribuent également à améliorer le @35niveau&de&culture de la cité.  @PConsultez votre @28chef&des&loisirs pour connaître le nombre de jongleurs, de musiciens et de danseurs qui travaillent dans votre cité. La @18carte&des&loisirs indique les lieux où les artistes se produisent et vous permet de suivre leur trajet à travers les rues de votre cité. @L@LPour en savoir plus sur la danse dans l'Egypte ancienne, cliquez @171ici. Pour en savoir plus sur la musique, cliquez @170ici et, pour en savoir plus sur la jonglerie, cliquez @169ici."
        }
    }

    message_building_senet_house {
        id: 74,
        
        size [30, 28]
        title {
            text: "Taverne de jeux",
        }
        content {
            text: "Une taverne de jeux permet aux habitants de se relaxer devant une partie de senet, un jeu qui évoque le voyage vers l'au-delà. Les gens passent ainsi de longues heures à siroter quelques bières tout en s'affrontant dans des parties amicales.  @POutre un accès à la main-d'oeuvre et à la route, la taverne de jeux doit être régulièrement approvisionnée en @96bière destinée aux clients. @PConsultez votre @28chef&des&loisirs pour connaître le nombre de tavernes de jeux que compte votre cité. Utilisez la @18carte&des&loisirs pour savoir quelles maisons font accès à une taverne de jeux. @PLes citoyens n'apprécient guère d'habiter à proximité d'une taverne de jeux (cliquez @56ici pour en savoir plus sur l'attrait), car les clients font beaucoup de bruit, en particulier les joueurs qui viennent de perdre un gros pari. @L@LLe senet était plus qu'un simple jeu. Pour en savoir plus, cliquez @172ici."
        }
    }

    message_building_trading_centers {
        id: 75,
        
        size [30, 28]
        title {
            text: "Centres d'entraînement",
        }
        content {
            text: "Pour apprendre leur art, jongleurs, danseurs et musiciens doivent fréquenter un centre d'entraînement. Chaque discipline a son propre lieu de formation : les jongleurs apprennent leurs numéros dans les écoles de jonglerie, les musiciens étudient dans les conservatoires et les danseurs s'entraînent dans les écoles de danse. @PChacune de ces structures nécessite un accès routier et sa propre main-d'oeuvre. Dès que les artistes ont terminé leur formation, ils se rendent dans le lieu le plus proche qui requiert leurs services. Lorsque les artistes se rendent dans ces lieux, les maisons qu'ils traversent ont accès à leur art. @PDès que les artistes arrivent sur les lieux, ils s'y produisent pendant quelques jours. Cliquez avec le bouton droit de la souris pour savoir quels artistes divertissent les foules et le nombre de jours qu'il leur reste à se produire. Plus le centre d'entraînement est proche du lieu de représentation, plus le spectacle restera à l'affiche. Une fois le nombre de jours de représentation atteint, l'artiste rentre chez lui. Sauf si d'autres artistes ont été formés pour les remplacer, le centre d'entraînement reste vacant et ne fournit aucun divertissement à la population. @PVos résidents ne voient pas d'inconvénient à habiter à proximité d'une école de jonglerie. Leur entraînement est presque aussi divertissant que leur représentation. Toutefois, personne n'apprécie de vivre à proximité d'écoles de danse ou de conservatoires. Les artistes vont et viennent à toute heure et les musiciens ne produisent pas les plus beaux sons en répétant. @PPour voir les artistes se rendre des écoles aux lieux de représentation, utilisez la @18carte&des&loisirs. @L@LLes Egyptiens avaient de nombreux loisirs. Cliquez @165ici pour en savoir plus."
        }
    }

    message_building_courthouse {
        id: 76,
        
        size [30, 28]
        title {
            text: "Palais de justice",
        }
        content {
            text: "Les palais de justice sont des structures municipales polyvalentes. Elles permettent de réduire la @36criminalité dans la cité et recèlent une partie de ses richesses. Les citoyens apprécient la sécurité des palais de justice et sont heureux de vivre à proximité de structures imposantes. @PLes palais de justice ont besoin d'un accès routier et de main-d'oeuvre avant de pouvoir envoyer des magistrats patrouiller dans les rues de la cité. La présence d'un magistrat réduit le risque de criminalité. Toutefois, leur présence n'est qu'une mesure préventive. Si la criminalité se développe, les magistrats ne peuvent rien faire pour empêcher sa propagation. @PUne partie de l'@48argent de la cité est stockée dans les palais de justice. Vous ne pouvez pas savoir quelle quantité d'argent est stockée dans chaque palais de justice. Votre @30chef&des&finances est bien mieux équipé pour s'acquitter de cette tâche et peut calculer la somme adéquate.  @L@LLes palais de justice étaient des lieux animés dans l'Egypte ancienne. Pour en savoir plus sur la loi dans l'Egypte ancienne, cliquez @183ici."
        }
    }
    
    message_building_palace {
        id: 77,
        
        size [30, 28]
        title {
            text: "Palais",
        }
        content {
            text: "Le palais de la cité est le centre du pouvoir.  @PUn palais est un bâtiment précieux pour une cité et il est donc conseillé d'en construire un dès que possible. Vous ne pouvez en construire qu'un dans la cité. En fonction de votre rang et de la richesse de votre cité, vous avez le choix entre un palais de village, un palais en ville et un palais citadin. @PUn palais vous permet de prélever des impôts. Tant que vous n'aurez pas affirmé votre autorité par un contrôle centralisé, vos citoyens douteront de vos capacités à gouverner. Vous pouvez également définir le taux d'imposition de votre cité à partir du palais. Cliquez avec le bouton droit sur le palais, puis utilisez les boutons en haut de l'écran pour modifier la valeur de l'impôt. Pour plus de détails concernant les impôts, cliquez @48ici. @PLe palais stocke une partie des fonds de la cité. L'écran qui apparaît lorsque vous cliquez avec le bouton droit sur le palais vous indique précisément les fonds stockés dans le bâtiment. Consultez la rubrique @48Argent pour en savoir plus sur le stockage des fonds dans la cité. @PLe palais vous donne également un aperçu de l'état général de la cité. Maintenez le curseur sur le bâtiment pour faire apparaître des informations à jour sur la cité : taux d'imposition, niveaux et taux de chômage. @PSi votre cité a la chance d'être bâtie à proximité d'un @93gisement&d'or, le palais peut remplir une autre fonction vitale. L'or est extrait des mines et transporté directement jusqu'au palais où il est transformé en pièces sonnantes et trébuchantes. Les debens ainsi obtenus s'ajoutent automatiquement au trésor de la cité. L'or n'est jamais échangé ou transporté ailleurs qu'au palais. @PSi le Pharaon vous fait l'honneur d'une visite, il séjournera au palais. @PLe siège du gouvernement est l'un des bâtiments les plus somptueux et les plus prestigieux de la cité. Les logements situés à proximité du palais sont particulièrement prisés ; ceux qui vivent dans les quartiers environnants pensent que le prestige du palais rehausse leur propre rang au sein de la communauté.  @PLe palais a besoin d'un accès à la route et de main-d'oeuvre pour fonctionner. Il doit également avoir accès à une nappe phréatique pour subvenir aux besoins du pharaon en cas de visite. Par conséquent, une partie du bâtiment doit être placée sur un herbage.  @L@LPour en savoir plus sur le gouvernement et la bureaucratie de l'Egypte ancienne cliquez @174ici."
        }
    }

    message_building_mansion {
        id: 78,
        
        size [30, 28]
        title {
            text: "Demeure",
        }
        content {
            text: "Faites-vous construire une superbe demeure pour asseoir votre prestige et votre autorité. Votre demeure vous servira à stocker vos richesses personnelles, mais vous ne pourrez toucher aucun @48salaire tant que vous ne posséderez pas votre propre logement. Les habitants de la cité veulent d'abord être certains que vous assurerez vos fonctions de manière durable avant de vous autoriser à prélever un salaire.  @PVotre salaire dépend de votre expérience. Si vous estimez que votre salaire doit être supérieur ou inférieur, vous pouvez définir vous-même la somme. Cliquez avec le bouton droit de la souris sur votre demeure pour faire apparaître un écran indiquant votre salaire actuel sous forme de bouton. Cliquez sur ce bouton pour afficher la liste de tous les rangs du royaume et les niveaux de salaires correspondants. Choisissez un salaire dans cette liste pour toucher la somme sélectionnée. Sachez, cependant, que si vous vous octroyez un salaire exorbitant, le @35niveau&du&royaume s'en ressentira. Pour fixer votre salaire, vous pouvez également faire appel au @30chef&des&finances. @PVotre demeure a besoin d'un accès à la route et à une nappe phréatique. Par conséquent, une partie du bâtiment doit être placée sur un herbage. Votre voisinage étant très recherché, votre demeure augmente considérablement l'attrait des quartiers environnants. @PEn fonction de votre rang et de la richesse de votre cité, vous avez le choix entre une demeure luxueuse personnelle, une demeure luxueuse familiale et une demeure luxueuse de dynastie. @L@LLes pharaons vivaient dans des demeures colossales dont le prestige éclipsait totalement la valeur des logements plus pauvres. Pour en savoir plus sur ces demeures grandioses, cliquez @175ici."
        }
    }
    
    message_building_garden_plaze_statue {
        id: 79,
        
        size [30, 28]
        title {
            text: "Jardin, plaza et statue",
        }
        content {
            text: "De la nourriture et des services à profusion ne suffiront pas à combler les attentes de vos citoyens. Pour les rendre heureux, vous devez embellir leur voisinage. Les plazas, les jardins et les statues apportent un attrait supplémentaire au voisinage et augmentent la valeur des logements. Les structures d'embellissement n'ont pas besoin de main-d'oeuvre. Vous pouvez construire ces structures en cliquant sur le bouton Structures municipales, puis en sélectionnant le bouton approprié dans le sous-menu Embellissement.  @PLes jardins sont des endroits merveilleux où le peuple aime se promener après une longue journée de dur labeur. Plus vous construisez de jardins, plus le peuple se montrera prodigue. Les jardins n'ont pas besoin d'accès à la route.  @PLes statues rappellent à vos citoyens la grandeur de l'Egypte ancienne. Trois tailles de statues sont disponibles : petite, moyenne et grande. Pour les construire, sélectionnez simplement une taille, puis définissez un emplacement. Tout en maintenant votre curseur sur l'emplacement souhaité, appuyez sur la touche 'R' de votre clavier. Pendant que vous maintenez le bouton enfoncé, quatre statues apparaissent, puis pivotent. Vous devez alors faire votre choix parmi l'une d'elles. Lorsque la statue sélectionnée se tourne dans la direction voulue, cliquez sur celle-ci. Les statues n'ont pas besoin d'accès à la route. @G72 @PLes plazas sont des @57routes embellies par des mosaïques. Elles ne peuvent être réalisées que sur des routes déjà pavées. Les citoyens commencent à paver les routes lorsqu'ils considèrent que leur voisinage est suffisamment @56désirable. Les plazas, évidemment, augmentent l'attrait du voisinage. La construction de plazas est identique à celle des routes. Cliquez sur le bouton Plaza, puis sur la route pavée que vous souhaitez recouvrir de mosaïques. Les plazas ne modifient nullement la fonction de la route. Vous pouvez recouvrir d'importants tronçons de route en faisant simplement glisser le curseur de la souris. Mais alors, attention à la dépense. @L@LLes jardins étaient pratiquement considérés comme une nécessité dans l'Egypte ancienne. Cliquez @176ici pour en savoir plus sur ces environnements luxuriants et sur l'embellissement en Egypte."
        }
    }
    
    message_building_tax_collector {
        id: 80,
        
        size [30, 28]
        title {
            text: "Percepteur",
        }
        content {
            text: "Les percepteurs patrouillent dans les rues de la cité afin de s'assurer que les résidents payent une part d'impôts équitable. @PLes percepteurs travaillent dans un bureau de perception qui nécessité un accès à la route et de la main-d'oeuvre. En outre, la cité doit posséder un @77palais en activité avant que le percepteur entre en fonction. @PUne partie des fonds de la cité est stockée dans chaque bureau de perception.  @PLa définition d'un taux d'imposition n'est pas chose facile. Vous devez ajuster les besoins de la trésorerie de la cité avec la capacité d'acceptation de vos citoyens. Le peuple n'acceptera de payer un taux d'imposition élevé que pendant une durée limitée, ensuite il n'hésitera pas à quitter votre cité à la recherche d'une cité plus intéressante. Si la moitié de la population de la cité doit faire face à un taux d'imposition élevé tandis que l'autre moitié ne paye rien, l'@39opinion se détériora, entraînant avec elle une augmentation de la @36criminalité. Consultez votre @30chef&des&finances, puis l'entrée relative à l'@48argent pour obtenir des conseils sur la définition du taux d'imposition. @L@LLe peuple de l'Egypte ancienne payait des impôts au pharaon pour l'aider à fonder le gouvernement. Cliquez @173ici pour en savoir plus sur les impôts dans l'Egypte ancienne."
        }
    }

    message_building_architect_post {
        id: 81,
        
        size [30, 28]
        title {
            text: "Architecte",
        }
        content {
            text: "Les constructions importantes, tels les entrepôts, les mines, les greniers, les temples et les ensembles de temples menacent parfois de s'effondrer. Les architectes qui parcourent vos rues repèrent les vices de construction avant qu'un désastre ne survienne. Les architectes travaillent dans des bureaux d'études. @G68 @PPour fonctionner, ces bâtiments doivent disposer d'un accès à une route et à la main-d'oeuvre.  @PPour vérifier si un bâtiment risque de s'effondrer, utilisez l'option @18Dégâts&de&la&carte&des&risques. Si vous constatez qu'un bâtiment ou un ensemble de bâtiments courent un réel danger d'effondrement, vous pouvez placer une étude d'architecte à proximité et vous assurer les services d'un architecte. @PUn effondrement peut avoir des conséquences dramatiques. En effet, si un @3grenier ou un @4entrepôt s'effondre, la nourriture ou les marchandises qui y sont stockées sont irrémédiablement perdues."
        }
    }

    message_building_whipwright {
        id: 82,
        
        size [30, 28]
        title {
            text: "Fabrique de bateaux",
        }
        content {
            text: "Les fabriques de bateaux réalisent des embarcations aussi bien commerciales que militaires. Elles construisent des bateaux de pêche pour les @84quais&de&bateaux&de&pêche, des navires de guerre pour les @356quais&de&navires&de&guerre et des transporteurs pour les @357quais&de&transporteurs. Les fabriques de bateaux doivent être placées sur un tronçon rectiligne de la côte. L'emplacement sélectionné est approprié lorsque 'l'empreinte' de la structure est verte. @PConstruisez la fabrique de bateaux sur une voie navigable, telle que le Nil ou une côte. Les fabriques de bateaux situées sur un bras de rivière ou sur un plan d'eau fermé ne pourront pas envoyer leurs navires jusqu'aux quais qui les attendent. Cela risque de torpiller votre effort maritime, les bateaux sortant régulièrement de la fabrique de bateaux se sabordant dès qu'ils constatent qu'ils ne pourront pas atteindre leur quai. @PLes fabriques de bateaux ont besoin de main-d'oeuvre et d'un accès à la route pour fonctionner. Elles nécessitent également un approvisionnement en bois pour construire les transporteurs et les navires de guerre. La construction des bateaux de pêche n'exige aucun approvisionnement. Ce sont les quais qui transmettent l'ordre aux fabriques de bateaux de construire une embarcation. Une fois que le bateau est terminé, celui-ci navigue jusqu'à son quai. A moins que vous ayez besoin de construire une quantité importante de bateaux en peu de temps, une seule fabrique de bateaux devrait suffire à répondre à vos besoins. @PSi un navire de guerre ou un transporteur devait être détruit au cours d'un combat, envoyez-le à la fabrique de bateaux pour y effectuer les réparations nécessaires. Les navires les plus touchés regagnent la fabrique de bateaux tant bien que mal à l'initiative de leur capitaine. La fabrique de bateaux réparera toutes les avaries si elle dispose d'un stock de bois suffisant. @PLes fabriques de bateaux ne construisent pas les bateaux se rendant aux @58embarcadères. Le passeur met à la disposition du peuple des bateaux pour transporter des passagers. Les immigrants et les émigrants disposent de leur propre embarcation.  @PLes fabriques de bateaux sont très bruyantes, aussi personne ne souhaite s'installer à proximité. @L@LLe peuple de l'Egypte ancienne construisait des bateaux fort différents en forme et en taille. Cliquez @179ici pour en savoir plus sur cette ancienne industrie."
        }
    }
    
    message_building_dock {
        id: 83,
        
        size [30, 28]
        title {
            text: "Dock",
        }
        content {
            text: "Certains @47partenaires&commerciaux voyagent par voies navigables. De grands bateaux de commerce se déplacent sur le Nil, mais vous n'en profiterez pas si vous ne disposez pas d'un quai d'accostage. Construisez un dock sur la côte pour permettre aux bateaux de s'amarrer. Veillez à construire le dock sur le Nil ou sur le littoral, là où naviguent les navires de commerce. Un dock placé sur un bras de rivière ou sur un plan d'eau fermé ne pourra accueillir de navires de commerce. @PPour être efficaces, les docks doivent également disposer d'accès routiers et de main-d'oeuvre. Une fois un bateau de commerce amarré, les charretiers du dock déchargent les biens et les transportent vers les @4entrepôts de la cité. Ils chargent ensuite les biens que la cité exporte à ce partenaire et les ramènent sur le dock. La construction d'un entrepôt à proximité du dock permet de réduire les trajets des charretiers. @PLes docks ont un effet négatif sur l'@56attrait des quartiers environnants. @L@LCliquez @177ici pour en savoir plus sur le commerce dans l'Egypte ancienne."
        }
    }

    message_building_fishing_wharf {
        id: 84,
        
        size [30, 28]
        title {
            text: "Quai",
        }
        content {
            text: "Si vous voyez des poissons sauter régulièrement hors de l'eau, des pêcheurs pourront attraper des poissons. @PPour pouvoir pêcher, la cité doit posséder des bateaux de pêche. @PLes quais permettent aux bateaux de pêche de s'amarrer. Les quais doivent être construits sur des sections de côte rectilignes et la moitié de leur structure doit reposer sur l'eau pour que les bateaux y aient accès. Veillez à ce que le bateau de pêche puisse naviguer dans les eaux environnant le quai. Si vous construisez le quai sur un bras de rivière, les bateaux de pêche ne pourront pas l'atteindre. Cela risque de torpiller votre effort maritime, les bateaux sortant régulièrement de la fabrique de bateaux se sabordant dès qu'ils constatent qu'ils ne pourront atteindre leur quai.  @PSi la cité possède une @82fabrique&de&bateaux en état de fonctionnement, l'installation d'un quai indique aux armateurs qu'ils doivent commencer à construire un bateau de pêche. La fabrique de bateaux n'a pas besoin de matières premières pour construire un bateau de pêche. @PLes bancs de poisson sont limités, mais ne peuvent être, toutefois, complètement épuisés. Une population importante ne pourra subsister en se nourrissant exclusivement de poissons. @PLes quais des bateaux de pêche sont des lieux malodorants et constituent de ce fait un voisinage @56indésirable. @L@LCliquez @186ici pour en savoir plus sur la pêche dans l'Egypte ancienne."
        }
    }

    message_building_defensive_structures {
        id: 85,
        
        size [30, 28]
        title {
            text: "Structures défensives",
        }
        content {
            text: "L'@37armée et la @356flotte&navale protègent le royaume contre les attaques ennemies. Construisez des structures défensives pour empêcher les assaillants d'envahir votre cité. @L@LMurs @LLe mur constitue la structure défensive la plus élémentaire. Pour construire un mur, cliquez sur le bouton Structures militaires, puis choisissez l'option correspondante dans la liste qui s'affiche. Cliquez sur le bouton gauche de la souris et faites glisser le curseur pour bâtir de larges enceintes. @PLes murs constitués d'une rangée de briques ne font que ralentir temporairement la progression de l'ennemi. Pour protéger votre cité contre toute agression, construisez plutôt des murs de plusieurs briques d'épaisseur. Il sera ainsi beaucoup plus difficile pour les assaillants de percer vos remparts. @PLes murs sont fabriqués avec toutes sortes de matériaux. Leur construction ne nécessite par conséquent aucune carrière, ni importation de blocs de pierre. Leur construction, cependant, étant relativement coûteuse, délimitez avec attention le périmètre que vous voulez fermer. @PLes murs n'ont pas besoin d'un accès à la route et sont indésirables pour le voisinage. @L@LTours @PConstruisez des tours pour donner un caractère offensif à vos murs. Les tours abritent en effet des sentinelles entraînées par le @88centre&de&recrutement pour lancer des javelots sur les ennemis qui osent s'approcher des enceintes. @PA condition que les murs soient assez larges pour que l'on puisse marcher dessus, des groupes de sentinelles peuvent également effectuer des rondes tout autour de la cité et lancer des flèches sur les assaillants. @PLes tours doivent être construites dans des murs d'une épaisseur de deux briques. Elles ont également besoin d'un accès à la route, de main-d'oeuvre et de sentinelles formées par un centre de recrutement. Ne construisez pas les murs trop épais de manière à ce que les soldats de la tour puissent tirer par dessus ! @L@LCorps de garde @PMalheureusement, il n'est pas possible d'encercler complètement une cité. Vous devez en effet construire des corps de garde pour laisser entrer les immigrants et les caravanes de marchands. @PConstruisez les corps de garde aux endroits où les principales voies d'accès traversent les enceintes de votre cité. Pour ce faire, placez le curseur de la souris là où vous souhaitez construire le bâtiment, puis appuyez sur 'R' pour modifier l'orientation du corps de garde. Une fois placés, les corps de garde se soudent automatiquement aux murs adjacents. En cas de menace d'attaque, les gardes fermeront les portes pour empêcher l'ennemi d'entrer. @PDe même que les barrages routiers, les corps de garde laissent passer librement les personnes ayant une destination définie, mais repoussent les promeneurs (cliquez @42ici pour en savoir plus sur les promeneurs). @PPour plus d'informations, consultez l'entrée relative à la @52guerre. @L@LLes cités étaient très bien défendues dans l'Egypte ancienne. Cliquez @182ici pour en savoir plus."
        }
    }

    message_building_police_station {
        id: 86,
        
        size [30, 28]
        title {
            text: "Poste de police",
        }
        content {
            text: "Les agents contrôlent la criminalité en patrouillant dans les voisinages. @PLes agents sont basés dans des postes de police qui ont besoin d'un accès à la route et de main-d'oeuvre. Un drapeau flottant sur le toit d'un poste de police signifie que celui-ci est prêt à fonctionner. @PLa présence d'un agent dans le voisinage en réduit considérablement la criminalité. Si son rôle préventif échoue, l'agent mènera alors une guerre active contre les criminels. S'il rencontre un voleur dans la rue, l'agent arrêtera le prévenu l'empêchant de poursuivre ses méfaits. Les agents constituent également l'un de vos meilleurs atouts contre les @477pilleurs&de&tombes.  @PLes agents font également de leur mieux pour combattre les autres menaces, telles les invasions ennemies et les attaques d'animaux sauvages. Un seul agent, cependant, est incapable de faire face à tout un troupeau d'animaux ou à une armée ennemie. Un agent n'hésitera pas un seul instant à combattre jusqu'à la mort, mais ce n'est pas pour autant qu'il parviendra à arrêter l'ennemi. La seule chance pour les agents de remporter un combat est de travailler en équipe. En outre, combattre une armée reste du ressort des militaires. Ceux-ci sont également plus efficaces pour faire face à un troupeau d'animaux sauvages. @G55 @PPour connaître les voisinages qui abritent le plus de criminels, consultez la @18carte&des&risques. La carte des risques peut vous aider à planifier les emplacements de vos postes de police. @PBien que les citoyens ne souhaitent pas s'installer dans un quartier qui ne soit pas couvert par la patrouille d'un agent, aucun d'eux ne souhaite non plus habiter à proximité d'un poste de police. Les agents vont et viennent à toute heure du jour. La plupart du temps, ils traînent derrière eux des personnages peu recommandables. @L@LCliquez @183ici pour en savoir plus sur les lois dans l'Egypte ancienne."
        }
    }

    message_company_orders {
        id: 87,
        
        size [30, 28]
        title {
            text: "Ordres à la compagnie",
        }
        content {
            text: "Pour faire stationner ou avancer une @37compagnie vers un autre lieu, cliquez sur la compagnie puis sur un nouvel emplacement. Le drapeau de la compagnie apparaît sur le nouvel emplacement et les soldats se mettent en marche en direction de ce drapeau (s'il peut être atteint). Notez que la bande de terre boueuse escarpée située entre la plaine inondable et la terre dure est impraticable sauf lorsqu'une route connecte ces deux terrains. @PVous pouvez transmettre les ordres suivants à une compagnie : @L@LMettez-vous en formation serrée. @LLes soldats se tiennent les uns contre les autres. Comme ils ont reçu l'ordre de tenir leur position, les soldats ne la quitteront pas pour attaquer leurs ennemis, ils attaqueront uniquement ceux passant à proximité. La formation serrée réduit l'espace @L@LMettez-vous en formation espacée. @LCet ordre s'adresse à l'infanterie et aux archers et non aux conducteurs de char. En formation espacée, les soldats se dispersent pour occuper plus de terrain puis gardent leur position. Ils attaqueront tout ennemi qui s'approche. Cette tactique permet @L@LEngagez le combat contre les ennemis immédiats. @LDonnez cet ordre aux soldats afin qu'ils attaquent tout ennemi situé à proximité. L'attaque se poursuit jusqu'à l'élimination ou la fuite de l'ennemi, jusqu'à ce qu'un nouvel ordre leur soit transmis ou jusqu'à ce que le moral de la compagnie vaincue cè @L@LBalayez. @LDonnez cet ordre aux soldats afin qu'ils attaquent tout ennemi présent dans un large périmètre. Les compagnies deviennent très agressives et pourchassent sans pitié le moindre adversaire. Emportés par leur fougue, les soldats oublient parfois de se défe@L@LChargez. @LCet ordre s'adresse uniquement aux conducteurs de char. Chargez les lignes ennemies pour désorganiser leur système de défense et pouvoir les attaquer plus facilement. Au cours d'une charge, les conducteurs de char excitent leurs chevaux avant de lancer @L@LRetournez au fort. @LChoisissez cette option lorsque la bataille est terminée et que l'ennemi a été  vaincu. En rentrant au fort, vos soldats peuvent se reposer en attendant le prochain combat. Si leur moral est bas, ils rentrent automatiquement au fort. @L@LOutre les ordres mentionnés ci-dessus, vous pouvez également demander à vos compagnies d'attaquer directement l'adversaire en sélectionnant ces compagnies puis en cliquant sur les ennemis. La compagnie poursuivra cet ennemi jusqu'à ce qu'il soit tué t@L@LCliquez @184ici pour en savoir plus sur la guerre dans l'Egypte ancienne."
        }
    }

    message_building_recruiter_academy {
        id: 88,
        
        size [30, 28]
        title {
            text: "Academie et Centre de recrutement",
        }
        content {
            text: "Les personnes qui souhaitent s'engager dans l'armée se rendent dans ces centres de recrutement. Pour un entraînement plus intensif, elles peuvent également passer par l'académie. Le centre de recrutement et l'académie ont besoin d'un accès à la route et de main-d'oeuvre.  @PLa fonction du centre de recrutement est très simple : il enrôle les candidats à l'@37armée et leur fournit les armes nécessaires pour combattre. Pour cela, vous devez approvisionner le centre en armes, soit en les important par l'intermédiaire d'un @47partenaire&commercial, soit en les confectionnant dans une @98fabrique&d'armes. Pour engager des conducteurs de char, vous devez acheter des chars auprès d'une @98fabrique&de&chars ou d'un commerçant étranger. Les hommes qui veulent devenir archers apportent leurs propres arcs et flèches. Le centre désigne également les sentinelles qui surveillent les murs et les @85tours de la cité. @PLes jeunes soldats quittent le centre de recrutement en rêvant de gloire et d'armes rutilantes, sans avoir conscience des risques et des exigences que leur impose leur métier. L'académie enseigne à l'infanterie, aux archers et aux conducteurs de char des tactiques avancées de combat. Les sentinelles ne fréquentent pas l'académie et apprennent leur métier au cours de leurs rondes. A la fin de leurs études, les soldats regagnent le fort de leur compagnie. @PSi la cité ne dispose pas d'une académie, les soldats rejoignent leur compagnie dès qu'ils quittent le centre de recrutement. @G57 @PEn raison du caractère tumultueux des militaires, le centre de recrutement et l'académie ont un effet négatif sur l'@56attrait. @L@LCliquez @184ici pour en savoir plus sur la guerre dans l'Egypte ancienne."
        }
    }

    message_building_grain_farm {
        id: 89,
        
        size [30, 28]
        title {
            text: "Exploitation de céréales",
        }
        content {
            text: "Les céréales ne sont pas si différentes des autres sources de nourriture dans la cité, mais les exploitations de céréales ont un atout supplémentaire car elles peuvent produire une matière première sous forme de produit intermédiaire : la paille. La paille sert de fourrage au bétail des @360fermes&d'élevage et constitue l'une des matières premières utilisées par les @364briqueteries. Outre le gibier, la paille sert de fourrage pour les animaux du @479zoo.  @PLa paille est récoltée en même temps que les céréales. Un livreur l'amène directement aux fermes d'élevage, aux briqueteries, aux zoos ou aux @4entrepôts tandis que son camarade transporte la récolte de céréales vers le grenier ou l'entrepôt de destination. @PLes abords des fermes d'élevage ne sont pas des lieux très convoités et ils ont pour conséquence de faire chuter la valeur des logements. @PVous pourrez trouver d'autres informations intéressantes dans les rubriques suivantes : @45Agriculture&et&nourriture, @2Bazar et @3Grenier. @L@LCliquez @185ici pour en savoir plus sur les céréales dans l'Egypte ancienne."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,
        
        size [30, 28]
        title {
            text: "Exploitations de fruits et légumes",
        }
        content {
            text: "Les fruits et les légumes sont tout aussi capables que n'importe quel autre type de nourriture pour répondre aux besoins du peuple. Les fruits et les légumes permettent de varier le régime alimentaire. Les différentes régions de l'Egypte abritent diverses cultures. Les cultures à la disposition de vos citoyens sont les grenades, les figues, les pois chiches et les laitues. @PLes exploitations de fruits et légumes fonctionnent comme toutes autres exploitations. Elles ne produisent que des produits destinés à l'alimentation de la population. Reportez-vous à la rubrique @45Agriculture pour de plus amples informations sur la planification de vos exploitations afin d'en tirer le meilleur profit. @PLes deux types d'exploitation ont besoin de main-d'oeuvre et d'un accès à la route pour produire des cultures. La main-d'oeuvre des fermes situées sur les plaines inondables provenant des @8chantiers, n'oubliez pas de construire au moins un chantier à proximité de vos fermes. @L@LLes Egyptiens avaient une alimentation diversifiée et adoraient la cuisine variée. Cliquez @187ici pour en savoir plus sur le régime alimentaire des Egyptiens."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,
        
        size [30, 28]
        title {
            text: "Exploitations d'orge, de lin et de henné",
        }
        content {
            text: "Les exploitations d'orge, de lin et de henné sont un peu différentes des @90exploitations&de&fruits&et&légumes et de celles de @89céréales. Les exploitations d'orge, de lin et de henné ne produisent pas de nourriture, mais uniquement des matières premières qui sont transformées en des produits à valeur marchande. L'orge est récoltée et transformée en @96bière et le lin, quant à lui, est tissé pour faire de la @60toile, tandis que le henné est réduit en poudre et mélangé à un liquide pour produire de la @470peinture. @PLes exploitations d'orge, de lin et de henné sont construites et fonctionnent comme les autres exploitations. Elles peuvent être construites n'importe où sur la plaine inondable. Les terres arables des plaines inondables sont identifiables par des touffes d'herbe jaune. L'emplacement sélectionné est approprié lorsque 'l'empreinte' de la structure est verte. Les exploitations doivent être adjacentes à une route et ont besoin de main-d'oeuvre. Les fermes des plaines inondables ne produisent pas de main-d'oeuvre directement, mais se reposent sur les paysans provenant des @8chantiers. Consultez la rubrique @45Agriculture avant de placer vos exploitations.  @PUne fois l'orge, le lin et le henné collectés, ceux-ci sont transportés jusqu'à la fabrique la plus proche (la brasserie pour l'orge et l'atelier de tissage pour le lin, les fabriques de peinture pour le henné). A la fabrique, l'orge, le lin et le henné sont transformés en des produits finaux qui sont ensuite distribués à vos citoyens ou qui sont utilisés par la @363guilde&des&artisans à des fins commerciales (@47commerce) dans le but de générer du profit. S'il n'y a plus de place dans la fabrique ou si aucun grenier n'existe dans la cité, l'orge, le lin et le henné sont transportés jusqu'à l'@4entrepôt.  @PCes trois exploitations ont un effet négatif sur l'@56attrait du voisinage. @L@LCliquez @185ici pour en savoir plus sur les cultures d'orge. Cliquez @189ici pour en savoir plus sur la collecte du lin dans l'Egypte ancienne. Pour en savoir plus sur les plantations de henné, cliquez @469ici."
        }
    }

    message_building_clay_pit {
        id: 92,
        
        size [30, 28]
        title {
            text: "Puits d'argile",
        }
        content {
            text: "Les puits d'argile produisent de l'argile qui est ensuite transformée en @1poterie, en @364briques lorsqu'elle est mélangée avec de la @89paille, ou distribuée à la @363guilde&des&artisans pour obtenir du plâtre. @PLes puits d'argile doivent avoir un accès à la route et à la main-d'oeuvre. Ils doivent être placés près de l'eau. @PUne fois que les ouvriers travaillant aux puits d'argile ont puisé suffisamment d'argile pour remplir une charrette, le puits d'argile envoie un de ses livreurs distribuer cette matière première aux personnes intéressées. Le livreur essaie toujours d'acheminer l'argile vers une @364briqueterie ou un @1potier qui en a besoin, en choisissant de préférence l'artisan le plus proche. Si aucun artisan n'a besoin de la matière première, le livreur achemine l'argile vers l'@4entrepôt le plus proche susceptible d'accepter le chargement. Si aucune fabrique n'a besoin de matières premières, le livreur transportera l'argile à l'@4entrepôt le plus proche encore disponible. Si aucun entrepôt ne peut accepter cette argile, le livreur attend que de la place soit de nouveau disponible. @PLes puits d'argile sont des trous froids et humides creusés à même la terre. Les citoyens les plus avertis ne seront pas enclins à s'installer près d'équipements aussi rudimentaires. @L@LLes égyptiens anciens savaient utiliser à bon escient les dépôts d'argile laissés par la crue annuelle du Nil. Cliquez @190ici pour en savoir plus sur cette marchandise."
        }
    }

    message_building_gold_copper_mine {
        id: 93,
        
        size [30, 28]
        title {
            text: "Mines d'or et de cuivre",
        }
        content {
            text: "L'or et le cuivre sont des métaux précieux. Une cité possédant du minerai dans son voisinage a beaucoup de chance. Si vous voyez des roches aux reflets métalliques et brillants, cliquez sur le bouton Structures industrielles de l'interface, puis sélectionnez Matières premières pour savoir s'il s'agit d'or ou de cuivre ou encore des deux.  @PL'or est une matière rare et précieuse qui doit être exploitée dès que vous en avez la possibilité. L'or est synonyme d'@48argent et les mines d'or sont les structures qui permettent à la cité de produire sa propre monnaie. Contrairement aux autres produits, l'or n'est jamais transporté jusqu'aux @4entrepôts. L'or est automatiquement dirigé vers le @77palais où il sera ensuite transformé en debens, qui viendront alors grossir la trésorerie de votre cité. @G54 @L@LCuivre @LLe cuivre est pratiquement aussi précieux que l'or, bien que son utilisation soit plus conventionnelle. Le cuivre est l'une des quelques matières premières que vous pouvez exporter en générant un profit intéressant.  @PDans ces temps incertains, le cuivre était une ressource extrêmement précieuse dans la mesure où les @98armes étaient à base de cuivre. Parfois, votre cité aura besoin d'armes pour équiper son infanterie. Cliquez @52ici pour en savoir plus sur la guerre. @L@LLes mines doivent être construites à proximité d'un affleurement rocheux marqué de pépites métalliques. Les deux types de mine ont besoin d'un accès à la route et de main-d'oeuvre et toutes deux sont considérées comme très indésirables à proximité des logements. @L@LLes Egyptiens anciens appréciaient l'or et ils avaient mis au point un processus d'extraction des plus ardus. Cliquez @191ici pour en savoir plus sur l'or et son utilisation dans l'Egypte ancienne."
        }
    }
    
    message_building_woodcutter_and_reed_gatherer {
        id: 94,
        
        size [30, 28]
        title { text: "Bûcheron et cueilleur de roseaux" }
        content {
            text: "Les bûcherons et les cueilleurs de roseaux collectent des matières premières qui sont ensuite utilisées par diverses industries. Les utilisations du bois sont multiples. Les menuisiers ont besoin de bois pour la construction des rampes et des échafaudages destinés aux monuments, les fabriques de chars pour la réalisation des chars et les fabriques de bateaux l'utilisent pour la construction des transporteurs et des navires de guerre. Les roseaux, eux, sont utilisés pour la fabrication du @97papyrus.  @PLes chantiers de bois peuvent être placés n'importe où, mais le meilleur endroit est évidemment près des forêts, car cela permet de réduire la durée du transport. Les chantiers de bois doivent avoir un accès à la route et à la main-d'oeuvre. Une fois le bâtiment opérationnel, les bûcherons se dirigent vers la forêt pour y débiter du bois. @G58 @PLes structures de cueilleur de roseaux et les chantiers de bois fonctionnent de manière similaire. Ces structures de cueilleur de roseaux doivent être situées de préférence, près d'un champ de roseaux. Vous pouvez cependant les placer n'importe où. Les champs de roseaux sont représentés par des espaces composés d'herbe vert foncé et d'herbe plus claire, le tout parsemé de touffes jaunes. Pour fonctionner, les chantiers de bois et les structures de cueilleur de roseaux doivent disposer d'un accès à une route et de main-d'oeuvre. Une fois ces conditions remplies, les cueilleurs de roseaux peuvent partir pour les marécages. @PFaites attention en plaçant vos chantiers de bois et vos structures de cueilleur de roseaux. Le bois et les roseaux ont une repousse régulière, mais cela n'élimine pas pour autant les risques de surexploitation. Si vous construisez trop de chantiers de bois ou de structures de cueilleur de roseaux, vous risquez de surexploiter ces ressources. Vos industries devront alors arrêter leur exploitation jusqu'à ce que les arbres et les roseaux aient repoussé. @PLe bois est l'une des marchandises les plus précieuses en Egypte. Essayez de ne pas détruire les forêts lorsque vous déblayez de la terre, car celles-ci pourront apporter plus tard à la cité d'importantes sources de revenus. Les zones marécageuses ne peuvent être dégagées et ce, bien que certains guérisseurs considèrent qu'elles apportent la malaria.  @L@LCliquez @192ici pour en savoir plus sur l'importance du bois dans l'Egypte ancienne. Cliquez @188ici pour découvrir les diverses utilisations des roseaux."
        }
    }

    message_building_stone_quarries {
        id: 95,
        
        size [30, 28]
        title {
            text: "Carrières de pierre",
        }
        content {
            text: "Les hommes travaillant dans les carrières de pierre taillent de larges blocs de roche dans quatre types de carrières différents : @L@PCarrière de pierre @PCarrière de calcaire @PCarrière de granit @PCarrière de grès @L@LSi une quantité importante de roches est visible aux alentours de votre cité, vous pouvez construire des carrières et en extraire la roche. Certaines régions, cependant, possèdent des roches inadaptées à la construction ou en quantité insuffisante pour supporter une industrie. Dans de telles régions, les roches sont alors inutiles car vous ne pouvez les déblayer, les traverser ou encore réaliser des constructions autour. Cliquez sur le bouton Structures industrielles et vérifiez la liste des matières premières disponibles. Cette liste vous indique le type de pierre pouvant être exploité dans la région. @PLes carrières doivent être placées à proximité des roches. Si l'emplacement indiqué est approprié, une 'empreinte' verte représentant la carrière s'affiche. Dans le cas contraire, 'l'empreinte' apparaît en rouge. @PLa pierre ne peut être transformée en d'autres produits. Mais, elle reste cependant la matière première des monuments et une quantité importante de pierre est toujours nécessaire même pour les petits monuments. @PLes carrières qui sont creusées dans l'un des flancs de la roche, ont tendance à s'effondrer. Construisez une @81étude&d'architecte près des carrières pour prévenir de tels désastres. @PLes carrières ont besoin de main-d'oeuvre et d'un accès à la route pour fonctionner. En raison du bruit assourdissant provoqué par l'extraction de la pierre, les carrières ne sont pas considérées comme un voisinage plaisant.  @L@LLa construction de carrières dans l'Egypte ancienne était un travail qui prenait beaucoup de temps. Cliquez @193ici pour en savoir plus."
        }
    }

    message_building_brewery {
        id: 96,
        
        size [30, 28]
        title {
            text: "Brasserie",
        }
        content {
            text: "Pour fabriquer de la bière, les brasseries doivent avoir accès à la route, à la main-d'oeuvre et à un stock d'orge. L'orge nécessaire est produite par les @91exploitations&d'orge ou est importée par l'intermédiaire d'un @47partenaire&commercial. Une exploitation d'orge produit normalement suffisamment d'orge pour deux brasseries. Les brasseries stockent de l'orge dans leurs locaux afin de disposer d'une quantité suffisante de matière première entre deux récoltes. @PUne fois que les brasseries disposent des produits nécessaires à la fabrication de la bière, le processus se met en route. Une brasserie est en activité lorsque les employés de la brasserie sont à l'intérieur de la structure. Une fois la bière fabriquée, les livreurs approvisionnent en premier lieu les @74tavernes&de&jeux. Si la taverne de jeux a besoin de bière, les livreurs transportent la bière jusqu'à l'@4entrepôt où elle sera collectée par des @2acheteurs&de&bazar pour être distribuée ensuite aux citoyens ou @47commercialisée dans le but de générer un profit substantiel. La bière est l'une des marchandises dont souhaitent disposer vos citoyens avant de construire des @56logements&plus&attractifs.  @PDe la bière est également distribuée lors des @51grandes&fêtes.  @L@LCliquez @194ici pour en savoir plus sur la bière dans l'Egypte ancienne."
        }
    }

    message_building_papyrus_maker {
        id: 97,
        
        size [30, 28]
        title {
            text: "Fabrique de papyrus",
        }
        content {
            text: "Les fabriques de papyrus ont besoin d'un accès à la route, à la main-d'oeuvre et à un stock de @94roseaux provenant des structures de cueilleur de roseaux ou d'un @47partenaire&commercial. Les fabriques de papyrus stockent des roseaux dans leurs locaux afin de disposer d'une quantité suffisante de matière première entre deux récoltes. @PLorsqu'une charrette de papyrus est prête, un livreur l'emmène jusqu'à une @68école&de&scribes ou une @70bibliothèque qui en a besoin. Si aucune structure éducative n'a besoin de papyrus, le livreur transportera la marchandise jusqu'à l'@4entrepôt où il sera ensuite @47commercialisé. @G69 @PLes citoyens n'apprécient pas beaucoup de vivre à proximité d'une fabrique de papyrus. En effet, les nuisances sonores émises par ce type de fabrique sont sources de mal de tête pour les riverains. @L@LCliquez @195ici pour en savoir plus sur la fabrication du papyrus dans l'Egypte ancienne."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,
        
        size [30, 28]
        title {
            text: "  Fabrique d'armes et fabrique de chars",
        }
        content {
            text: "Les fabriques d'armes et les fabriques de chars construisent le matériel de guerre nécessaire à certaines compagnies militaires.  @PLe cuivre provenant d'une @93mine&de&cuivre ou de l'importation d'un @47partenaire&commercial est utilisé par la fabrique d'armes pour être transformé en armes redoutables. Ces armes, une fois finies, sont envoyées au @88centre&de&recrutement pour équiper les compagnies d'@37infanterie. Si le centre de recrutement dispose de suffisamment d'armes ou si votre cité n'a pas encore de centre de recrutement, celles-ci seront alors envoyées dans un @45entrepôt. @PLa fabrique de chars utilise le bois provenant d'un @94chantier&de&bois ou d'un @47partenaire&commercial pour fabriquer de magnifiques chars de guerre. Le produit fini est ensuite envoyé au centre de recrutement pour équiper les @37conducteurs&de&char. Si le centre de recrutement dispose de suffisamment de chars dans son inventaire ou si votre cité n'a pas encore de centre de recrutement, les chars sont envoyés dans un entrepôt. @PCes deux bâtiments doivent disposer d'un accès routier et d'employés. Ils constituent des voisins @56indésirables. @L@LCliquez @196ici pour en savoir plus sur les armes dans l'Egypte ancienne."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,
        
        size [30, 28]
        title {
            text: "Bijouterie et articles de luxe",
        }
        content {
            text: "Grâce aux @361pierres&précieuses, les orfèvreries peuvent créer des articles de luxe comme par exemple des bijoux. Les pierres précieuses sont soit extraites, soit importées par l'intermédiaire d'un @47partenaire&commercial.  @PPour fonctionner, les bijouteries doivent disposer d'un accès à une route et à la main-d'oeuvre. Elles ont un effet négatif sur l'@56attrait des quartiers environnants.  @PL'orfèvrerie n'est pas une source d'exportation très lucrative. Le coût le plus important lors de l'importation d'articles de luxe correspond aux frais de transport et non à la nature des matières transportées. Ainsi, si le coût à l'achat des bijoux importés est très important, ce même coût pour des bijoux exportés ne sera pas comparable. Par conséquent, l'importation de bijoux vous coûtera plus cher que leur exportation. @PLes bijoux sont des articles de luxe appréciés par les citoyens. Les citoyens les plus aisés exigeront, cependant, l'importation d'un second article de luxe. @L@LL'Egypte ancienne est particulièrement renommée pour son @382orfèvrerie raffinée. Cliquez @197ici pour en savoir plus sur les articles de luxe dans l'Egypte ancienne."
        }
    }

    message_population_milestone_100 {
        id: 100,
        
        size [30, 20]
        title { text: "Evolution démographique" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "100 personnes se sont installées dans votre village." }
    }

    message_population_milestone_500 {
        id: 101,
        
        size [30, 20]
        title { text: "Evolution démographique" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "Votre nouvelle ville compte désormais cinq cents habitants." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,
        
        size [30, 20]
        title { text: "Evolution démographique" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "Votre cité compte désormais mille personnes." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@17" }
        content { text: "Avec ses deux mille habitants, votre cité prend de l'importance." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@17" }
        content { text: "La population de votre cité compte trois mille habitants, pour la première fois de son histoire." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@18" }
        content { text: "Votre cité a atteint une taille considérable. Elle compte désormais cinq mille habitants." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@18" }
        content { text: "Avec ses dix mille habitants, votre cité est l'un des bastions de l'Egypte." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@18" }
        content { text: "Peu de cités peuvent rivaliser avec la vôtre, qui compte désormais quinze mille habitants." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@19" }
        content { text: "Gouverneurs et nomarques saluent l'importance de votre cité, qui compte désormais vingt mille habitants !" }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Evolution démographique" }
        video { text: "@19" }
        content { text: "Le groupe d'immigrants qui fondèrent votre cité n'aurait jamais imaginé que sa population atteindrait un jour vingt-cinq mille habitants !" }
    }

    message_the_control_panel {
        id: 110,
        
        size [30, 20]
        title { text: "L'interface"  }
        content {
            text: "L'interface permet d'accéder à toutes les commandes nécessaires pour construire et entretenir votre cité. Pour vous familiariser avec ses différentes fonctions, il vous suffit de cliquer sur les boutons qui la composent. N'hésitez pas, vous ne risquez rien ! Si l'option Bulles d'aide pleines est activée (sous 'Aide' dans la barre de menus), placez votre curseur sur un élément pour obtenir une courte description de ce dernier. Pour obtenir des explications détaillées sur une rubrique de Pharaon, utilisez le menu 'Aide' de la barre de menus."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        urgent: 1,
        title { text: "Incendie dans la cité" }
        content {
            text: "Les flammes balaient la ville. Cliquez sur Carte des risques pour afficher les zones où l'incendie risque de se développer et construire une caserne de pompiers à proximité des structures exposées."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1
        
        size [30, 20]
        urgent: 1
        title { text: "Bâtiment détruit" }
        content {
            text: "Certaines structures imposantes de votre ville risquent de s'effondrer si elles ne sont pas correctement entretenues. Cliquez sur Carte des risques pour voir les bâtiments susceptibles de s'effondrer et construire des études d'architecte à proximité."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,
        
        size [30, 20]
        title { text: "Navire échoué" }
        content { text: " Certains capitaines inexpérimentés rencontrent parfois des difficultés dans les plaines inondables, notamment lorsque leur navire s'échoue." }
    }

    message_out_of_money {
        id: 115,
        
        size [30, 20]
        title { text: "Manque d'argent" }
        content { text: " Il n'y a plus d'argent dans les caisses de votre cité. Vous recevez donc des fonds supplémentaires, mais cette aide n'est que provisoire. Utilisez cet argent pour des placements." }
    }

    message_debt_again {
        id: 116,
        
        size [30, 20]
        title { text: "Endettement" }
        content { text: "Votre trésorerie est à sec. Vous pouvez dépenser jusqu'à 5 000 debens, mais l'@48endettement peut mener votre famille à la ruine si vous ne remboursez pas l'argent dans les plus brefs délais." }
    }

    message_out_of_money_again {
        id: 117,
        
        size [30, 20]
        title { text: "Manque d'argent" }
        content { text: "Les caisses de la cité sont vides, ô pharaon. Vos nomarques loyaux ont donné tous les debens qu'ils pouvaient, mais ils ne peuvent se permettre de recommencer." }
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
        title { text: "Message de l'ennemi" }
        content {
            text: "Nous venons de recevoir de nouveaux ordres. Il semble qu'on recommence à vous respecter en Egypte et votre destruction n'est apparemment plus nécessaire. Nous vous disons adieu... pour le le moment."
        }
    }
    message_debt_anniversary {
        id: 121,
        
        size [30, 20]
        urgent: 1,
        title { text: "Endettements à répétition" }
        content {
            text: "Votre trésorerie est toujours à sec. Chaque année consécutive d'endettement nuit à votre réputation et à votre @35niveau&du royaume. Vous devriez peut-être réviser vos notions de l'@48argent."
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
        title { text: "Colère de Bastet" }
        video { text: "@20" }
        content { text: "Malheur à vous ! Bastet est atterrée par votre indifférence. Pour montrer que la salubrité de votre cité ne peut être sans son culte, elle a rempli le fleuve de sang. Il reste à espérer que vos citoyens puissent tenir jusqu'à ce que l'eau retrouve sa pureté." }
    }

    message_city_unemployment {
        id: 135,
        type: 2,
        
        size [30, 20]
        title { text: "Manque de travail" }
        content { text: "Il n'y a pas assez de travail pour tous les habitants. Si la situation ne s'améliore pas, la criminalité risque de se développer, ou les gens iront tenter leur chance ailleurs dans le royaume." }
    }

    message_employees_needed {
        id: 136,
        
        size [30, 20]
        title { text: "Besoin de main-d'oeuvre" }
        content { text: "Les gens en âge de travailler ne sont pas assez nombreux. Si vous ne trouvez pas de main-d'oeuvre supplémentaire rapidement, les services de la cité risquent de se détériorer et la production industrielle en souffrira." }
    }

    message_common_festival {
        id: 137,
        
        size [30, 20]
        title { text: "Fête commune" }
        content { text: "Chacun apprécie de quitter le travail tôt pour se détendre un moment sur la place des fêtes. Cela est également apprécié par votre dieu." }
    }

    message_lavish_festival {
        id: 138,
        
        size [30, 20]
        title { text: "Fête somptueuse" }
        content { text: "La journée de fête commence. Tous les habitants de la cité se rendent sur la place des fêtes et semblent de bonne humeur. Votre dieu apprécie votre dévotion." }
    }

    message_grand_festival {
        id: 139,
        
        size [30, 20]
        title { text: "Fête grandiose" }
        content { text: "Les deux jours de fête que tout le monde attendait ont enfin commencé ! Tout le monde se rend sur la place des fêtes pour boire de la bière et s'amuser. Le dieu honoré par cet événement vous est infiniment reconnaissant." }
    }

    message_wrath_of_osiris {
        id: 140
        type: 2
        
        size [30, 20]
        title { text: "Colère d'Osiris" }
        video { text: "@24" }
        content { text: "Osiris est très déçu par le manque de respect de cette cité. Si vous ne l'apaisez pas rapidement, la prochaine inondation sera bien plus faible que prévue, voire inexistante !" }
    }

    message_wrath_of_ptah {
        id: 141
        type: 2
        
        size [30, 20]
        title { text: "Colère de Ptah" }
        video { text: "@22" }
        content { text: "Vous avez provoqué la colère de Ptah ! Votre cité ne possède actuellement pas d'industrie à toucher, mais attention à la colère de ce dieu lorsque votre cité aura des mines, des usines ou des carrières." }
    }
    
    message_wrath_of_ptah_2 {
        id: 142
        type: 2
        
        size [30, 20]
        title { text: "Colère de Ptah" }
        video { text: "@22" }
        content { text: "Ptah ne supporte pas l'idée que votre cité puisse développer une activité industrielle sans lui vouer le respect qui lui est dû. En guise de menace, il a déjà détruit quelques bâtiments industriels." }
    }

    message_wrath_of_seth_noeffect {
        id: 143
        type: 2
        
        size [30, 20]
        title { text: "Colère de Seth" }
        video { text: "@21" }
        content { text: "Votre cité a échappé à la colère de Seth en raison de son manque de structures militaires à détruire. Evitez néanmoins de provoquer le dieu de la destruction, car sa colère peut prendre diverses formes et sa mémoire est grande." }
    }

    message_wrath_of_bast {
        id: 144,
        type: 2,
        
        size [30, 20]
        title { text: "Colère de Bastet" }
        video { text: "@20" }
        content { text: " De terribles nouvelles ! Votre cité ayant négligé de lui porter les honneurs qui lui étaient dus, Bastet, déesse du foyer, a détruit une partie des demeures principales de votre cité !" }
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
        title { text: "Colère d'Osiris" }
        video { text: "@24" }
        content { text: "Ô, jour maudit ! Exaspéré par par votre refus de lui vouer le culte qui lui est dû, Osiris a envoyé un essaim de criquets dévorer vos récoltes." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
        type: 2,
        
        size [30, 20]
        title { text: "Colère de Ptah" }
        video { text: "@22" }
        content {
            text: " Ptah est indigné que vous refusiez de le vénérer. Il a donc fait abattre un orage de grenouilles sur votre cité. Avec leur peau visqueuse et leur odeur fétide, ces grenouilles vont chasser plus d'un habitant de sa maison."
        }
    }

    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2
        
        size [30, 20]
        title { text: "Colère de Seth" }
        video { text: "@21" }
        content { text: "Furieux que vous refusiez de lui rendre hommage, Seth a lancé un orage de grêle sur votre cité, frappant et tuant tous ceux qui se trouvent sur son passage !" }
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
        title { text: "Industrie" }
        subtitle { text: "Histoire" }
        content {
            text: "A l'époque de l'Ancien Empire, la fabrication de produits n'était plus domestique ; elle était organisée en ateliers centralisés, au sein desquels étaient produites toutes les denrées nécessaires à la vie quotidienne des Egyptiens. Chaque atelier était spécialisé dans un produit spécifique et fonctionnait comme une chaîne de montage moderne. Chaque ouvrier était responsable d'un aspect particulier du produit final, et non pas de la fabrication d'un produit de A à Z. Les outils employés par les artisans dans ces ateliers appartenaient à l'Etat, tout comme tous les matériaux produits. Les artisans percevaient un salaire, souvent sous forme de nourriture et autres biens. @L@LL'industrie égyptienne était florissante. Parmi les secteurs d'activité, on trouvait la @198poterie, le @398tissage, la joaillerie, la tannerie, la @389menuiserie et la fonderie, mais aussi la boulangerie et la @194brasserie."
        }
    }
    message_housing {
        id: 152,
        
        size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Logement" }
        subtitle { text: "Histoire" }
        content {
            text: "Les habitations des Egyptiens étaient construites en briques, en bois, en terre ou en pierre. Le style et la taille de ces habitations dépendaient de la fortune du citoyen et de l'endroit où il habitait. Ainsi, les paysans vivaient dans des constructions simples en briques ou en terre de deux à quatre pièces. Les habitations urbaines des classes moyennes étaient également de taille modeste. Les villes les plus peuplées comptaient des maisons à deux étages pouvant abriter deux familles afin d'économiser l'espace. Les travailleurs qui habitaient en ville vivaient dans des maisons en briques de 3 à 7 pièces. @L@LLes citoyens les plus aisés possédaient de plus vastes demeures, dont certaines étaient particulièrement spacieuses. Des hauts fonctionnaires possédaient des habitations de 60 à 70 pièces avec de hauts plafonds supportés par des colonnes de bois, des salles de réception, d'importants espaces de rangement et des quartiers pour les domestiques. Les habitations les plus luxueuses étaient les @175palais des pharaons.  @L@LDans leur majorité, les villes égyptiennes se développaient de façon naturelle et dans toutes les directions. Certaines d'entre elles, cependant, étaient planifiées ; le principal exemple en est le village d'ouvriers de Deir el-Médineh. @L@LLa plupart des villes égyptiennes étaient entourées d'enceintes. Pour en savoir plus sur les structures défensives, cliquez @182ici."
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
            text: "Routes",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le @157Nil constituait l'axe principal de l'Egypte. Des bateaux de toutes sortes y transportaient des hommes et des biens. L'Egypte ancienne disposait également de routes non pavées qui n'étaient généralement que des chemins améliorés. Dans la plupart des villes, le dédale des routes épousait le contour des constructions. Dans les ensembles planifiés, tels que les logements de Deir el-Médineh, les routes étaient construites selon un tracé précis. @L@LCertaines routes commerciales étaient également bien établies, mais elles n'étaient pas pavées, et pouvaient s'avérer dangereuses. Pour en savoir plus sur les dangers du commerce, cliquez @177ici."
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
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens accroissaient la surface cultivable grâce à l'irrigation. Les premiers réseaux de canaux d'irrigation et de rigoles remontent à la IXème dynastie, vers 2000 av. J.-C et il est probable que certains canaux aient été utilisés auparavant pour le transport. Les canaux d'irrigation étendaient les possibilités offertes par le fleuve en transportant le limon fertile vers des zones éloignées du Nil. @L@LA une époque reculée de l'histoire égyptienne, les paysans désireux d'irriguer leur terre n'avaient pas la tâche facile. Ils effectuaient ce travail manuellement, transportant deux seaux de terre cuite ou de cuir sur un joug jusqu'au Nil ou jusqu'à une autre source. La terre cultivée était parcourue de petites digues retenant l'eau, optimisant ainsi cette méthode d'irrigation lente et fastidieuse.  @L@LA la fin de la XVIIIème dynastie (vers 1300 av. J.-C) fut introduit le chadouf. Celui-ci fut probablement importé de Mésopotamie, où il était utilisé dès 2370 av. J.-C. Placé au bord du Nil ou d'une source, le chadouf se composait d'une longue barre en bois qui basculait sur un pivot. Le seau placé à l'une des extrémités de la barre, était contrebalancé par un contrepoids (généralement une brique). Quelqu'un plongeait le seau dans l'eau, puis le contrepoids hissait le seau. L'eau était ensuite versée dans une rigole reliée au chadouf. @L@LL'introduction du chadouf permit d'accroître la surface cultivée d'environ 15 %. En outre, ces terres, situées en dehors de la zone de crue, pouvaient supporter deux récoltes par an au lieu d'une."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2
        
        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Travail" }
        subtitle { text: "Histoire" }
        content { text: "La majeure partie des tâches les plus pénibles étaient effectuées par les paysans dans l'Egypte ancienne. Ils labouraient la terre et moissonnaient pendant la saison de croissance. Durant les périodes d'inondation, ces mêmes paysans étaient réquisitionnés par l'Etat. Pour la plupart, ils étaient employés à construire des pyramides et d'autres structures, certains étant chargés de l'entretien des infrastructures, telles que les @153routes et les @154canaux d'irrigation. @L@LLes paysans menaient une vie dure, mais n'étaient pas malmenés. La journée de travail durait huit heures et comprenait une pause déjeuner. La semaine de travail durait huit jours suivie de deux jours de repos. En outre, le travail cessait lors des fêtes. Les paysans étaient exempts de travail en cas de maladie ou de décès dans leur famille. @L@LLa présence faisait l'objet d'un contrôle précis, tout comme les raisons d'absence. D'ailleurs, certaines justifications d'absence ne seraient sans doute pas acceptées aujourd'hui. Par exemple, il arrivait qu'un employé s'absente pour aller boire avec l'un de ses amis. @L@LEn dépit de ce que l'on croit généralement, on avait rarement recours à l'esclavage pour les projets de construction publics. On employait parfois des esclaves dans les carrières, mais plus souvent en tant que serviteurs. @L@LSi les travailleurs étaient mal traités, ils pouvaient se mettre en grève. Sous le règne de Ramsès IV, vers 1150 av. J.-C, les ouvriers de Deir el-Médineh cessèrent officiellement le travail pour protester contre le retard dans le versement de leur compensation. Leur grève fut une réussite et les arriérés furent versés." }
    }
    message_clean_water {
        id: 156
        
        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Puits et citernes", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "La distribution d'eau potable à la population constituait un véritable défi dans l'Egypte ancienne. La principale source d'eau était le Nil et sa nappe phréatique. Il y avait certes quelques oasis, mais la majeure partie de la terre était aride. @L@LDes citernes furent construites pour acheminer l'eau dans les villages. Les porteurs d'eau amenaient des seaux remplis d'eau depuis le Nil jusqu'aux citernes. @L@LLes Egyptiens étaient experts en creusement de puits. Les ouvriers durent par exemple creuser un puits dans près de 10 kilomètres de roche aux environs des logements populaires de Gizeh. La plupart des puits étaient surmontés d'une coupole, depuis laquelle un escalier descendait jusqu'au niveau de l'eau pour permettre aux habitants de remplir leurs cruches."
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
            text: "Le Nil",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La civilisation égyptienne n'aurait pas existé sans le Nil. Dans les régions où les précipitations sont faibles, le Nil constitue une source d'eau fiable pour la population et la terre. Le Nil, dont les crues se produisent régulièrement, fertilise à nouveau les terres arables. @L@LL'importance du Nil n'a pas disparu avec l'Egypte ancienne. Le Nil nourricier inspira les coutumes religieuses égyptiennes et en particulier les croyances en l'existence d'une vie après la mort.  @L@LLe calendrier égyptien se divisait en saisons dont le nom provenait des différentes étapes d'évolution du Nil. L'inondation, suivant la crue du fleuve, s'appelait akhet. Ce phénomène était dû aux moussons annuelles à la source du Nil Bleu, sur les plateaux d'Ethiopie. La germination, ou pert, marquait la période de décrue du Nil et de germination des cultures. La période des moissons s'appelait shemou, terme parfois traduit par 'sécheresse'."
        }
    }
    message_dentistry {
        id: 158,
        
        size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Dentistes" }
        subtitle { text: "Histoire" }
        content {
            text: "La dentisterie était l'une des nombreuses disciplines exercées par les médecins dans l'Egypte ancienne. L'analyse des dents  de la période antique indiquent que les dentistes menaient une lutte inégale. L'omniprésence du sable favorisait la formation de caries. Le sable s'infiltrait partout, y compris dans la nourriture, et attaquait les dents . Ces problèmes dentaires provoquaient souvent des abcès, provoquant la perte de dents, voire la mort. @L@LLes papyrus médicaux détaillent les modes de traitement employés par les dentistes. Si une dent tombait, par exemple, le dentiste la rattachait à une autre avec un fil d'or ou d'argent. Il existait même une recette de plombage consistant à mélanger de la résine et de la malachite, mais les archéologues n'ont retrouvé aucune dent dont le plombage soit intact. @L@LLes archéologues ont retrouvé des outils qui servaient probablement de brosse à dents. Aucune espèce de fil dentaire datant de cette époque n'a été retrouvé à ce jour."
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
            text: "Pharmacies",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "On possède de nombreux documents sur les pratiques médicales et pharmaceutiques de l'Egypte ancienne. La religion était l'un des instruments du traitement des maladies, et la plupart des remèdes étaient accompagnés de prières ou d'incantations. Les papyrus médicaux servaient à la prescription de traitement spécifiques, dont certains peuvent nous sembler étranges. Pour guérir une indigestion, par exemple, on broyait la dent d'un cochon et on répartissait les débris dans quatre gâteaux sucrés. Le patient devait manger un de ces gâteaux par jour, après quoi l'indigestion devait être guérie. Pour guérir une calvitie, on mélangeait les vertèbres d'un corbeau, le sabot brûlé d'un âne et la chair d'un serpent noir."
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
            text: "Médecine",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Comme souvent au sein de la société égyptienne, la profession médicale était extrêmement segmentée et bureaucratique. Elle était organisée de façon hiérarchique et les médecins portaient des titres, le plus haut dans la hiérarchie étant 'directeur général des médecins de la Haute et de la Basse-Egypte'. @L@LLes médecins acquéraient leurs compétences en étudiant les organes internes des animaux et les textes, et non à travers l'observation des pratiques d'embaumement. La médecine était bien distincte des rites funéraires. @L@LLa bonne santé était incarnée par le concept de metu. Le coeur était le centre du corps et toutes les parties du corps étaient liées au coeur par des canaux, ou metu. Le metu désigne l'ensemble des systèmes corporels et non pas seulement la circulation. Par conséquent, les maladies étaient associées à un blocage du système. @L@LPour guérir les maladies, les médecins prescrivaient des médicaments et des prières. Pour en savoir plus sur les pratiques pharmaceutiques égyptiennes, reportez-vous à la section @159Pharmacies. @L@LParmi les maladies les plus courantes, on comptait la polio, la variole, la tuberculose de la moelle épinière et la malaria. Les vers parasites étaient également à la source de nombreux maux."
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
            text: "Embaumeurs",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'embaumement est la pierre angulaire des coutumes funéraires de l'Egypte ancienne. Le ka, ou esprit du défunt, devait avoir une place dans l'au-delà et il avait besoin pour cela de son corps. Durant la procédure d'embaumement, le corps était dans un premier temps rincé dans les eaux du Nil, symbole de la renaissance. Ensuite, les organes internes étaient retirés et stockés dans des conteneurs appelés canopes. Le seul organe que l'on supprimait était le cerveau (que l'on évacuait par les narines), car les Egyptiens anciens étaient persuadés qu'il n'avait aucune utilité. Les vases canopes étaient ensevelis avec le corps. @L@LUne fois les organes internes retirés, l'embaumeur remplissait la cavité de parfums, d'huiles et de toile et la recousait. Ensuite, le corps était recouvert de natron, une espèce de sel. Au bout de 70 jours, le corps était rincé de nouveau, enveloppé dans de la toile et enduit de goudron. Cette substance permettait d'éliminer les bactéries et les champignons qui provoquaient la décomposition. @L@LEn raison du coût de l'embaumement, seuls les citoyens les clus riches pouvaient se l'offrir."
        }
    }
    message_shrine_and_temple {
        id: 162,
        
        size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Sanctuaires et temples", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "Les temples étaient considérés comme la résidence des dieux, et un groupe de @384prêtres était affecté à chaque temple pour s'occuper du dieu. Les citoyens participaient à cette tâche par des offrandes, mais il était rare qu'ils aperçoivent la statue du dieu cachée au fond du temple. Il n'y avait que les jours de fête, lorsque le dieu était transporté à travers la ville sur une barque sacrée, que les citoyens avaient l'occasion d'apercevoir la divinité. @L@LLes Egyptiens s'adressaient aux dieux pour demander conseil. L'avant-cour du temple était accessible à tout le monde, et c'est là que l'on interrogeait les dieux ou on leur demandait pardon. Les prêtres, que l'on ne voyait pas, répondaient aux requêtes. Les citoyens pouvaient également interroger le dieu qui circulait dans la ville les jours de fête. @L@LEn outre, La plupart des Egyptiens possédaient chez eux des sanctuaires. Il s'agissait le plus souvent d'honorer Bès, le dieu protecteur de la maison. Il semble que les individus vénéraient également leur dieu protecteur. Dans un document retrouvé à Deir el-Médineh, il apparaît que les ouvriers s'absentaient parfois pour célébrer la 'fête de leur dieu'. @L@LLe concept de dieu protecteur s'étendit aux cités, aux villes et aux provinces. Le panthéon égyptien variait  en fonction des périodes historiques. Pour en savoir plus sur l'évolution de la religion, cliquez @399ici."
        }
    }
    message_school_and_eduction {
        id: 163,
        
        size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "Ecoles et éducation", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "Dans l'Egypte ancienne, l'éducation était extrêmement pratique. Les individus étaient éduqués en fonction d'une carrière spécifique. L'éducation était souvent synonyme d'apprentissage et les garçons suivaient généralement cet apprentissage chez leur père pour apprendre un métier. Certaines filles apprenaient la  danse, le chant ou le tissage . Cependant, la plupart étaient destinées à s'occuper du foyer. @L@LLes scribes recevaient une éducation extrêmement formelle. Les écoles de scribes, appelées Per-Ankh, ou 'maisons de vie', étaient à l'origine associées aux temples. C'est là que les futurs scribes apprenaient les langues écrites, d'abord le hiératique et, plus tard, le démotique, utilisé dans la vie de tous les jours. Les scribes se formaient en copiant des manuscrits sur des ostracas, ou anciens tessons de poterie. Ce n'est qu'une fois qu'ils maîtrisaient leur art qu'on leur confiait des papyrus. Ils étaient soumis à une discipline stricte, et les châtiments corporels n'étaient pas rares. L'éducation des scribes se déroulait généralement entre 10 et 20 ans."
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
            text: "Bibliothèques",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens immortalisèrent par écrit de nombreuses histoires, poèmes et hymnes. Ces textes étaient placés dans des bibliothèques associées aux Per-Ankh (maisons de vie), les @163écoles de scribes adjacentes aux temples.  @L@LLa littérature égyptienne prenait sa source dans la tradition orale et constituait surtout un aide-mémoire pour les narrateurs. La plupart des Egyptiens étaient analphabètes et les @387scribes faisaient office de conteurs et utilisaient les textes écrits comme aides-mémoire pour les histoires, les hymnes et les poèmes. Les personnes qui savaient lire, en particulier au sein de la cour du pharaon, avaient accès aux bibliothèques et pouvaient y consulter des papyrus. Certains citoyens aisés possédaient leur propre bibliothèque. @L@LOn peut diviser la littérature de l'Egypte en plusieurs genres, dont l'autobiographie, les récits d'aventures, les contes populaires, les récits mythologiques, les lamentations, la poésie et les hymnes. De tous ces genres, l'autobiographie est le plus ancien et provenait de la tradition consistant à graver les actes d'un défunt sur sa tombe. La satire était également un genre populaire."
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
            text: "Divertissements",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens anciens avaient le choix entre diverses activités de loisirs. Les sports étaient particulièrement appréciés, notamment les sports aquatiques tels que l'aviron et la natation (que les citoyens les plus riches pratiquaient dans leur piscine privée). Les Egyptiens sont également les premiers à avoir pratiqué la pêche comme activité de loisirs. @L@LLe pugilat était particulièrement populaire et des combats étaient organisés pour divertir les pharaons. Parmi les autres sports pratiqués, on trouve la pelote, une forme de hockey, la gymnastique, le tir à l'arc et l'haltérophilie. @L@LPour les personnes instruites, la lecture était un divertissement populaire, et la première nouvelle connue fut écrite par un Egyptien. La poésie était un genre populaire, mais aucune pièce de théâtre égyptienne n'a été recensée. Pour en savoir plus sur la lecture, l'écriture et la littérature, reportez-vous à la section @164Bibliothèques. @L@L@393Les&fêtes étaient également un élément important de la vie des Egyptiens."
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
            text: "Enfants",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Dans l'Egypte ancienne, les enfants étaient particulièrement importants et on les considérait comme le prolongement de la vie. On se mariait souvent de bonne heure pour avoir une famille nombreuse. Les enfants des plus pauvres suivaient leurs parents dans les champs et aidaient lors des moissons. Les enfants appartenant aux classes moyennes et riches restaient à la maison auprès de leur mère. Lorsqu'ils en avaient l'âge, les garçons des familles aisées étaient envoyés à l'école, avant de suivre un apprentissage auprès de leur père. @L@LLes petits Egyptiens avaient de nombreux jouets à leur disposition, tels que des ballons, des poupées, des toupies et des animaux en bois. Ils jouaient, entre autres, au tir à la corde et avaient les mêmes divertissements que leurs parents, parmi lesquels la natation et la pêche. @L@LLes familles égyptiennes étaient souvent entourées d'animaux domestiques, tels que des chiens et des chats, mais aussi des singes dressés, des oiseaux, des gazelles et, chez les plus riches et les plus courageux, des lions."
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
            text: "Population égyptienne",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'Egypte ancienne est comparable en de nombreux points à la société moderne. Une grande partie de la population vivait dans des centres urbains où l'industrie fournissait de nombreux emplois. Les paysans vivaient, quant à eux, dans des villages. La majorité de la population vivait, naturellement, en bordure du fleuve. @L@LLa population égyptienne s'est accrue au fil du temps, une croissance liée directement à l'@154irrigation. Durant la période prédynastique, la population ne dépassa pas 350000 personnes. A la fin du deuxième millénaire av. J.-C, les pratiques d'irrigation ayant augmenté la quantité de terres cultivables, les Egyptiens étaient environ 3 millions."
        }
    }
    message_history_society {
        id: 168,
        
        size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Société égyptienne", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "La société égyptienne était divisée en classes distinctes. Ces classes étaient hermétiques et, à l'exception de quelques mariages, l'appartenance à l'une des classes était déterminée par la naissance. @L@LLes membres des classes inférieures étaient des paysans. Ces derniers avaient l'espérance de vie la plus courte et menaient une vie de dur labeur, travaillant dans des exploitations agricoles ou participant à des projets de construction publics. Leurs restes font état de sérieux problèmes de dos et l'on a retrouvé des squelettes dont les vertèbres étaient littéralement soudées . Ils habitaient dans des demeures rudimentaires et étaient enterrés dans des tombes simples, car ils n'avaient pas les moyens d'être embaumés. @L@LLa classe moyenne était constituée de personnes impliquées dans l'industrie, tels que des artisans et des marchands. Leurs demeures étaient plus spacieuses et certains d'entre eux avaient les moyens d'être embaumés et inhumés dans de modestes tombeaux. @L@LLes hauts fonctionnaires vivaient dans le plus grand luxe, se faisaient embaumer et construire de somptueux tombeaux. Leur alimentation était riche et variée par rapport au reste de la population. L'étude de restes momifiés d'Egyptiens fortunés montre que 10 à 20 % d'entre eux souffraient d'artériosclérose - un durcissement des artères - car ils consommaient une grande quantité de graisse animale et menaient une vie stressante. Les hommes appartenant aux classes aisées étaient souvent représentés avec un gros ventre, signe de leur prospérité."
        }
    }
    message_history_juggling {
        id: 169,
        
        size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Jongleurs", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "L'art de jongler a vu le jour en Egypte. Des peintures retrouvées sur une tombe du Moyen Empire, à Beni Hassan, représentent de jeunes femmes exécutant plusieurs numéros, certaines couchées sur le dos et se lançant des balles. @L@LLe rôle des jongleurs dans l'Egypte ancienne n'est pas claire. Il pouvait s'agir d'une activité mystique ou d'un pur divertissement."
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
            text: "Musique",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens jouaient de plusieurs instruments, dont la flûte (que l'on trouvait en diverses tailles), la harpe, la lyre, le luth, le tambourin et autres instruments à percussion. Les chanteurs faisaient partie intégrante de la culture musicale égyptienne, et la plupart des hymnes et poèmes inscrits sur papyrus étaient composés pour être chantés. @L@LLes instruments à percussion servaient en particulier à accompagner les @171danses. De nombreux danseurs jouaient des castagnettes tout en dansant. @L@LLes Egyptiens jouaient également de la trompette. Cet instrument était associé à l'armée (les Egyptiens avaient sans doute leur propre forme de clairon) et l'on en retrouve fréquemment dans les tombes des rois et des chefs militaires. Deux trompettes ont été retrouvées dans la tombe de Toutankhamon. L'une de ces trompettes a retenti en 1939. Après quelques notes, l'instrument s'est subitement disloqué. Il fut immédiatement restauré. La trompette était également associée à @376Osiris, dieu de l'agriculture et de l'inondation par le Nil. @L@LD'autres instruments avaient également une signification religieuse. Le sistre, un grand instrument ressemblant à la crécelle, était associé à Hathor, déesse de la joie et des plaisirs. La flûte était associée à Amon, dieu du soleil."
        }
    }
    message_history_dance {
        id: 171,
        
        size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Danse", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "Dans l'Egypte ancienne, la danse était à l'origine composée de rites qui servaient aux chasseurs à se préparer pour la chasse. Un chorégraphe, ou prêtre-danseur, devait s'assurer que les danses étaient exécutées correctement. @L@LPlus tard, la danse fit partie intégrante des fêtes et d'autres célébrations religieuses, tout en restant une forme de divertissement. Des troupes de danseurs professionnels se produisaient dans les jardins des cités et étaient engagés pour des fêtes privées. Les danseurs étaient généralement accompagnés de @170musique. La plupart des danseurs professionnels étaient des femmes portant sur leurs cuisses des tatouages à l'effigie de Bès, dieu de la musique et de la danse.  @L@LPour certains citoyens, la danse était également un passe-temps, même si cette distraction était réservée en priorité aux classes inférieures. Plus un Egyptien était fortuné, moins il était susceptible de danser. En outre, les troupes de danseurs n'étaient jamais mixtes. @L@LLes noms des pas de danse égyptiens étaient figuratifs et portaient des noms tels que 'la démarche d'un lion' ou 'la capture d'un navire', par exemple."
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
            text: "Tavernes de jeux",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le senet était le jeu de société le plus populaire dans l'Egypte ancienne. Le support était rectangulaire et divisé en trois rangées de 10 cases. Il se jouait à deux, chaque joueur disposant d'au moins cinq pièces. Les tours étaient déterminés par un jeu de quatre bâtons. Les règles n'étaient inscrites nulle part, si bien que personne ne les connaît avec certitude. La plupart des historiens, cependant, pensent que ce jeu représentait le voyage dans l'au-delà. Le backgammon et la marelle sont considérés comme des descendants du senet. @L@LLe senet, tout comme d'autres jeux, était probablement l'un des divertissements des Egyptiens dans les tavernes ou les auberges. Après une dure journée de travail, de nombreux Egyptiens se rendaient dans les tavernes locales où on leur servait de la @194bière et où les conversations allaient bon train. Ces établissements étaient fréquentés par des hommes et des femmes, en particulier des célibataires."
        }
    }
    message_history_taxation_and_money {
        id: 173,
        
        size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Impôt", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "Les Egyptiens anciens payaient un impôt à leur pharaon. Comme ils n'avaient aucune monnaie, les taxes était versées en nature. Ainsi, par exemple, un paysan devait payer au pharaon une certaine quantité de blé. Les scribes étaient envoyés dans toutes les exploitations agricoles pour déterminer l'impôt à payer par chaque paysan."
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
            text: "Politique et bureaucratie",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Dans l'Egypte ancienne, le gouvernement était très bureaucratique. Chaque tâche était associée à un fonctionnaire du gouvernement au titre ronflant. Le pharaon, naturellement, dirigeait tout. Le bras droit du pharaon était son vizir, qui avait pour charge de s'assurer que tous les ordres du pharaon étaient exécutés. Le vizir avait sous ses ordres des nomarques (gouverneurs régionaux), des chanceliers, des vice-rois, des maîtres, des maires, etc. En outre, l'Egypte ancienne étant une théocratie, les prêtres avaient également un rôle important à jouer. @L@LDe nombreuses personnes portaient plusieurs titres. Imhotep, par exemple, qui officia sous Djeser I et s'occupa de la construction de la pyramide à degrés, portait le titre de vizir, grand prêtre de Ptah et maître des travaux, entre autres."
        }
    }
    message_history_pharaohs_home {
        id: 175,
        
        size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "Demeure du pharaon", pos [125, 15] }
        subtitle { text: "Histoire" }
        content {
            text: "La demeure du pharaon était la plus majestueuse de la cité. Si la plupart des habitations ne comportaient qu'une pièce ou deux, certaines demeures luxueuses pharaoniques en comportaient plusieurs dizaines et disposaient du meilleur confort qu'il était possible d'avoir dans l'Egypte ancienne. @L@LComme les fonctionnaires du @174gouvernement, les Egyptiens au service du pharaon portaient des titres et étaient responsables de tâches très spécifiques. Parmi ces personnes, on trouvait le 'Surintendant des affaires domestiques', le 'Chef de la manucure' et le 'Majordome royal'. @L@LUn majordome royal, Nefer-Peret, avait des attributions particulières. Il était responsable de quatre vaches palestiniennes, deux vaches égyptiennes, un taureau et un seau en bronze. Ni plus, ni moins."
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
            text: "Jardins et art public",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les jardins étaient extrêmement populaires dans l'Egypte ancienne et la plupart des maisons possédaient un jardin adjacent. Outre la culture des @187fruits&et&légumes pour subvenir aux besoins, les jardins servaient de  refuge contre le soleil torride. De nombreux jardins comportaient des arbres pour faire de l'ombre. @L@LLes ornements étaient réservés aux monuments et aux temples. Ces deux types de constructions demandaient tant de temps et coûtaient si cher que le reste des villes semblait plutôt morne en comparaison."
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
            text: "Commerce",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les ressources naturelles abondaient dans l'Egypte ancienne, contrairement aux produits manufacturés. Les Egyptiens ouvrirent des routes commerciales avec de nombreux pays et régions des environs, y compris la Nubie, le Liban, la Syrie, le Pount (que les historiens assimilent à la côte de Somalie) et la région de la mer Egée, entre autres. Certaines sources attestent que le commerce Egyptien s'étendait au nord jusqu'à la Turquie actuelle. @L@LLe Nil eut également un rôle important dans le commerce égyptien. La première cataracte, ou ensemble de cascades rocheuses, était navigable, ce qui offrait une voie de circulation pratique vers et depuis la Nubie. @L@LLe Nil fournissait également à l'Egypte l'un de ses principaux produits d'exportation : le blé. La crue était bien plus fiable que la pluie au Liban et en Syrie. Tant qu'elle avait lieu, l'Egypte était assurée de produire un surplus de blé, un luxe dont le Liban et la Syrie profitaient rarement. Les autres produits d'exportation égyptiens étaient le lin, le papyrus, les lentilles, le poisson séché, les vaisseaux en or et en argent, la peau de boeuf et le cordage. @L@LEn échange, l'Egypte recevait une variété de biens importés. Parmi les plus importants, on trouve l'or de Nubie, le bois du Liban et l'huile d'olive de Syrie. Les Egyptiens importaient également des articles de luxe, tels que de la myrrhe et du vin, ainsi que du bétail, voire des armes. @L@LChargées de marchandises, les caravanes étaient particulièrement vulnérables. Pour leur protection, elles étaient escortées par des unités armées. C'est pourquoi certains historiens supposent que l'Egypte ne s'est pas lancée dans le libre-échange avec ses voisins, mais les forçait à lui fournir des marchandises. Si la coercition a probablement eu son rôle à jouer dans le commerce égyptien, certains papyrus font également référence à des négociations entre l'Egypte et ses partenaires commerciaux. @L@LDes inscriptions et des oeuvres d'art ont été exécutées en l'honneur de missions commerciales couronnées de succès. La reine Hatshepsout envoya une flotte au Pount pour rapporter de la myrrhe, de l'encens, de l'ivoire et autres produits de luxe. Le voyage s'avéra tellement fructueux qu'il est relaté sur les murs du temple d'Hatshepsout à Deir el-Bahari."
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
            text: "Bateaux et leur construction",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le Nil a toujours inspiré les constructeurs de bateaux. A l'époque prédynastique, les Egyptiens liaient des bottes de papyrus pour faire des radeaux mus à l'aide de perches. Le début des constructions de pyramides vit les premières constructions de bateaux pour transporter les matériaux lourds nécessaires à la construction des pyramides. @L@LComme d'autres industries en Egypte, la construction de bateaux était une activité dirigée par l'Etat. Equipés d'outils utilisés pour le travail du bois, les constructeurs commençaient par la coque en alignant des planches côte à côte, puis en les assemblant à l'aide de chevilles, de colle et de cordes conçues pour rétrécir au contact de l'eau. En rétrécissant, les cordes fixaient la coque. Les coques des plus grands bateaux comportaient des membrures. Une fois la coque terminée, les constructeurs achevaient le travail en édifiant un mât pour la navigation et en creusant des trous pour les rames. Certains bateaux comportaient des cabines. @L@LCes bateaux étaient ventrus et conçus avec un faible tirant d'eau. La navigation sur le Nil était relativement facile, mais comportait son lot de bancs de sable et de bas-fonds. Dans ces conditions, ils n'était pas rare que des bateaux échouent. @L@LLes bateaux construits étaient relativement grands. L'un d'entre eux, qui servit à transporter des obélisques jusqu'au temple d'Hatshepsout, mesurait 82 mètres de long. La découverte du chaland de Koufou est une découverte archéologique d'importance considérable. Retrouvée en plus de 1 200 morceaux au sud de la pyramide de Koufou, ce chaland fut reconstruit au début des années 1960. Il mesure 43 mètres de long et 6 mètres de large, avec des emplacements pour 10 rameurs et deux timoniers. Les historiens ne connaissent pas l'utilité exacte de ce bateau. Certains supposent qu'il est le symbole du navire solaire d'Horus. D'autres pensent qu'il s'agissait du chaland ayant servi au transport des restes de Koufou jusqu'à sa pyramide, ou qu'il l'utilisa de son vivant. Quelle que soit les faits, cette découverte nous donne un aperçu de la construction des bateaux en Egypte."
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
            text: "Ennemis",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'Egypte était fréquemment en contact avec ses voisins et les relations n'étaient pas toujours amicales. Elle fut envahie à plusieurs reprises durant sa longue histoire et fut parfois gouvernée par des étrangers. Ces personnages usurpaient le titre de pharaon et, jusqu'à l'invasion perse, les Egyptiens réussirent toujours à reconquérir leur terre. L'Egypte, toutefois, n'était pas toujours la victime. Durant le Nouvel Empire notamment, les pharaons s'efforcèrent d'étendre leur empire et envahirent de nombreux pays voisins. @L@LParmi les peuples contre lesquels les Egyptiens entrèrent en conflit, on trouve les Nubiens et les Ethiopiens. L'Egypte envahit la Nubie assez tôt dans son histoire (vers 2900 av. J.-C), dans le but de s'emparer des abondantes ressources d'or et de cuivre du pays. La Nubie prit finalement le dessus, et une succession de pharaons nubiens régnèrent sur l'Egypte. @L@LLes Egyptiens entrèrent également en conflit avec plusieurs peuples de la péninsule du Sinaï. Parmi eux, on trouve les Canaéens, les Philistins, les Bédouins (habitants de la Syrie actuelle) et les Hittites. Les plus connus de ces peuples asiatiques sont, cependant, les Hyksos. Durant la deuxième période intermédiaire, ces derniers gouvernèrent l'Egypte. Ils conservèrent une grande partie des coutumes égyptiennes et introduisirent de nombreuses innovations, telles que le char tiré par des chevaux. Ils restèrent à la tête de l'Egypte pendant environ un siècle, jusqu'à leur défaite aux mains d'Ahmôsis, qui s'empara alors du trône. @L@LA l'ouest, l'Egypte entra en conflit contre les tribus libyennes, notamment les Tehenu et les Temehu. Ces deux peuples tentèrent de pénétrer à l'intérieur du Delta égyptien, et ils furent battus à plates coutures par Séthi I. Des @182forts furent construits à l'ouest afin de maintenir les tribus ennemies à distance. @L@LEnfin, le puissant Empire romain a rejoint les rivages de l'Egypte au cours du règne de Ptolémée. Une fois l'armée egyptienne sur le déclin, ses ennemis, et en particulier Jules César ainsi que ses successeurs, furent naturellement attirés par les greniers et autres trésors (sans parler de la captivante Cléopâtre VII). L'arrivée des légions romaines de César sur le sol égyptien marqua le début de la fin d'une longue histoire de domination égyptienne dans le bassin méditerranéen. L'Egypte, autrefois nation fière, devint un Etat vassal. @L@LCliquez @184ici pour en savoir plus sur l'armée égyptienne."
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
            text: "Structures défensives",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'Egypte protégeait ses cités et ses villes avec des murs et des tours. Les murs étaient généralement en briques et avaient la forme d'un quadrilatère ou d'un cercle entourant la ville. Des fouilles menées à Eléphantine, ville située au sud de l'Egypte, à proximité de la frontière nubienne, ont permis de retrouver un mur épais et arrondi parsemé de tours semi-circulaires.  @L@LL'Egypte défendait ses frontières grâce à des forteresses. Parmi les plus connues, on trouve les 'Murs du Prince', un ensemble de 13 forteresses construites le long de la rive orientale du Nil."
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
            text: "Loi égyptienne",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens pouvait faire enregistrer leurs griefs par un magistrat. En fonction de l'importance du délit, le cas pouvait être traité par un magistrat local ou par le vizir en personne. Le magistrat local pouvait être un petit fonctionnaire de la ville, tel qu'un contremaître. Les scribes assistaient aux procès et recensaient les participants, les témoins, les témoignages et les sentences. @L@LTout citoyen était soumis à la loi, indépendamment de son niveau social. Une scène gravée sur un mastaba de l'Ancien Empire montre des administrateurs locaux punis pour avoir refusé de payer leurs impôts. Les femmes participaient activement aux jugements. On peut citer, par exemple, le cas d'une femme qui avait récupéré la jouissance d'un bien illégalement réclamé par sa belle-famille. Dans une autre affaire, une femme est jugée coupable du vol d'un outil et d'un vaisseau de l'un des tombeaux d'Amon. @L@LLes châtiments pouvaient être très sévères et impliquaient souvent des châtiments corporels ou du travail forcé. Sous la XVIIIème dynastie du Nouvel Empire, la punition infligée pour le vol de peaux était de 100 coups et cinq blessures ouvertes. Pour certains crimes particulièrement odieux, on coupait le nez du coupable et on le bannissait hors d'Egypte. @L@LLa loi égyptienne n'était pas strictement codifiée et reposait surtout sur la jurisprudence. On a conservé des listes de délits et des châtiments correspondant, en particulier du Nouvel Empire, mais ces listes sont souvent contradictoires. @L@LLa justice était également importante dans l'au-delà. Avant de pouvoir accéder au royaume des morts, un individu devait faire une 'confession négative', au cours de laquelle il dressait la liste de tous les actes qu'il n'avait pas commis durant sa vie charnelle. Après cette confession, son coeur était pesé sur une balance dont l'un des plateaux comportait la plume de Maât. Si le  coeur était plus lourd, il était dévoré par Ammit, un horrible monstre, et l'individu n'était pas admis dans l'au-delà."
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
            text: "Armée",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'armée égyptienne s'est développée au fil des millénaires sous le règne des pharaons. Sous l'Ancien Empire, les armées étaient mobilisées en fonction des besoins et étaient généralement composées de nobles et de leurs descendants, ou d'étrangers. Il n'y avait pas encore d'armée professionnelle à cette époque. Les hommes qui servaient dans l'armée étaient d'origines diverses et reprenaient leur activité à la fin des conflits. @L@LSous le Nouvel Empire, cependant, la structure de l'armée était différente. Elle était clairement divisée en unités de fantassins et de conducteurs de char. L'infanterie était divisée en deux parties : les soldats spécialisés dans le combat rapproché et les spécialistes de la lutte à plus longue distance. Les chars étaient utilisés pour le combat mobile et à distance, principalement avec des arcs. Les affrontements entre bateaux étaient fréquents, même si la flottille faisait partie intégrante des forces terrestres. Les soldats embarqués étaient décrits dans les mêmes termes que les fantassins. Là aussi, les étrangers constituaient une partie importante de l'armée, qu'ils soient Nubiens, Libyens ou Asiatiques. @L@LSous l'Ancien Empire, l'armée égyptienne était organisée en plusieurs bataillons. Durant le Nouvel Empire, ces bataillons furent eux-mêmes subdivisés en divisions qui portaient le nom de dieux. Les scribes et les administrateurs allaient au combat avec les soldats afin de pouvoir suivre l'action. @L@LCliquez @196ici pour en savoir plus sur les armes dont disposait l'armée égyptienne."
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
            text: "Blé et orge",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'agriculture céréalière (blé et orge) produisait la matière première de l'aliment de base dans l'Egypte ancienne : le pain. Le blé et l'orge étaient transformés en farine, que l'on faisait cuire pour faire du pain. Pour en savoir plus sur l'utilisation du pain confectionné à partir de l'orge, reportez-vous à la section @194Bière. @L@LLes Egyptiens utilisaient trois types de blé : emmer, einkorn et spelt. Le blé était transformé en farine par battage. Les gerbes de blé étaient placées sur le sol et l'on amenait du bétail ou d'autres animaux corpulents pour écraser le blé. Cette opération permettait de séparer les grains des gerbes. Ensuite, les grains étaient séparés de la balle et d'autres impuretés à l'aide d'un tamis ou en jetant le blé en l'air. Le vent emportait la paille plus légère alors que les grains, plus lourds, retombaient sur le sol. Une fois ce traitement terminé, on engrangeait le blé dans les @5greniers. C'est là qu'il était transformé en farine, conservée pour un usage ultérieur.  @L@LPour faire le pain, on confectionnait une pâte à l'aide de farine, puis on la versait dans des moules en céramique de formes différentes, la plus répandue étant la forme conique. La pâte était cuite dans un foyer entouré de morceaux de charbon chauds et de cendre. On confectionnait le pain chez soi ou dans des boulangeries. Les archéologues pensent que les boulangers avaient souvent des problèmes de santé en raison de la quantité importante de cendre dans l'air."
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
            text: "Elevage et pêche",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens pratiquaient l'élevage de différents animaux dans des fermes pour leur alimentation. Les animaux les plus répandus étaient les bovins à longues cornes. Leurs gardiens étaient représentés  sur les tombes sous la forme d'individus très sveltes et mal rasés. Les animaux étaient envoyés dans les pâturages pour se nourrir. Parfois, on les envoyait dans les champs récemment moissonnés pour qu'ils se nourrissent de paille. @L@LLes Egyptiens pratiquaient également l'élevage des moutons, des chèvres et des porcs dans des fermes, ainsi que des oies et autres animaux de basse-cour. Ils élevaient aussi des chevaux, non pour la nourriture, mais pour tirer les chars des nobles. Cet animal fut introduit en Egypte par les Hyksos, l'un des @181envahisseurs d'Egypte. @L@LLe poisson constituait une autre source de nourriture, mais leur consommation se limitait surtout aux classes inférieures. Les Egyptiens avaient plusieurs manières de pêcher. Certains s'installaient dans des barques avec des cannes à pêche munies de lignes et d'hameçons pour attraper les poissons un par un. Ils construisaient également des nasses pour les attraper en plus grande quantité. La pêche au filet était la technique la plus difficile. Comme elle permettait des pêches considérables, deux bateaux remplis d'hommes étaient nécessaires pour ramener le filet à la surface. @L@LLa pêche n'allait pas sans certains dangers. En effet, le Nil abrite une espèce de poisson-chat dont la nageoire dorsale est venimeuse et la rencontre d'un crocodile n'est pas exclue. Ces derniers restaient à l'affût, surveillant les pêcheurs qui étaient relativement en sécurité dans leur embarcation."
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
            text: "Fruits et légumes",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Si le @185blé et l'orge constituaient la base de l'alimentation des Egyptiens, ils cultivaient également plusieurs variétés de fruits et légumes. Haricots, pois chiches, lentilles et petits pois étaient très répandus, tout comme l'ail, les oignons, les  poireaux, la laitue et les concombres. Du côté des fruits, on consommait figues, dattes, raisins et grenades. Les dattes étaient particulièrement consommées dans les classes inférieures de la population et servaient à parfumer la bière. En outre, les Egyptiens assaisonnaient leur nourriture à l'aide de cannelle, de coriandre, de cumin, de fenouil et de moutarde."
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
            text: "Papyrus, plante merveilleuse",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le papyrus, qui pouvait atteindre 7 à huit mètres de haut, n'était pas uniquement utilisé pour produire du papier. Il était également transformé en une variété de produits, tels que des mâts, des sandales et des cordes. Le coeur de cette plante était appréciée en tant qu'aliment. Parfois, sa tige était utilisée comme bois de construction, ou servait à confectionner des radeaux. Le papyrus avait quasiment disparu, jusqu'à ce qu'il resurgisse récemment. Il est de nouveau cultivé et sert à la production de papier, mais cette fois-ci dans un but touristique."
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
            text: "Lin",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le lin était cultivé pour confectionner de la @398toile, principal textile dans l'Egypte ancienne. Comme la partie la plus importante de la plante était sa tige, il fallait arracher les plantes du sol et non les couper, ce qui ralentissait considérablement la récolte. Une fois cette dernière terminée, on retirait les racines et les germes, et l'on étendait les tiges pour qu'elles sèchent. Ensuite, on plongeait les tiges dans l'eau pendant deux semaines, après quoi on les frappait contre des pierres et on séparait les fibres. Enfin, l'atelier de tissage les transformait en tissu."
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
            text: "Puits d'argile",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'argile était facile à extraire dans l'Egypte ancienne et sa qualité variait d'une région à l'autre. Le long du Nil, plusieurs années d'inondation avaient entraîné la formation de riches dépôts de boue ne demandant qu'à être creusés et transformés en poteries. Dans les régions désertiques, le calcaire contenait des nervures de marne souple et de schiste. L'argile du désert produisait des poteries plus dures que l'argile du Nil et servait à produire des objets de teinte rose ou verte. Les poteries exécutées en argile du Nil étaient plutôt rouges ou noires. Les deux types d'argile étaient traités de la même manière pour confectionner des @198poteries."
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
            text: "Or et mines d'or",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "On trouva à l'origine de l'or dans le désert oriental de l'Egypte et en Nubie. L'extraction de l'or pouvait s'avérer une tâche fort ardue. Dans le désert oriental, par exemple, le granit était parsemé de nervures d'or. On le transformait alors en poudre, avant de la plonger dans l'eau pour séparer l'or de la roche. Cette procédure était extrêmement longue. L'or était cependant abondant et, finalement, plus facile à obtenir que l'argent. @L@LPour que l'or soit exploitable, il était dans un premier temps fondu à la mine. Une fois fondu, on le versait dans de l'eau. Tout en refroidissant, il formait des pépites, que l'on confiait ensuite à un orfèvre. @L@LComme pour presque tous les autres biens, l'inventaire de l'or était scrupuleusement tenu par des scribes. Ils pesaient consciencieusement l'or chaque matin chez un orfèvre et leur travail était soumis à une surveillance stricte afin de s'assurer qu'ils ne volaient pas.  @L@LSi l'or était plus abondant que l'agent, la quantité disponible n'était pas excessive. C'est pourquoi de nombreux objets étaient plaqués or et non constitués d'or pur."
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
            text: "Utilisations du bois",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'Egypte compte très peu d'arbres. En effet le sol est soit trop humide en raison de l'inondation, soit trop sec. Parmi les quelques arbres qui réussissaient à se développer, on trouvait le sycomore, le dattier et le moringa. Ces arbres avaient une signification religieuse et étaient considérés comme une demeure des dieux. @L@LEn raison de ces croyances, les chantiers de bois devaient recevoir une autorisation spécifique pour abattre les arbres. Les arbres abattus fournissaient du bois fragile dont l'usage était limité. L'Egypte importait la plupart de son bois du Liban actuel, de la Syrie et d'Israël. Lorsque l'Egypte conquit ces territoires, sous le Nouvel Empire, les Egyptiens contribuèrent fortement à la déforestation de ces régions. @L@LOn utilisait le bois pour la fabrication de meubles, de cercueils et dans le bâtiment. Les menuisiers étaient maîtres dans l'art de la confection de pièces complexes comportant des incrustations et des gravures."
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
            text: "Carrières",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens exploitaient plusieurs sortes de roches pour la construction de leurs pyramides, de leurs temples et de leurs monuments, telles que le calcaire, le granit, le grès, le basalte, l'ardoise, l'albâtre et le porphyre. Les ouvriers qui travaillaient dans les carrières étaient équipés de pics et de burins pour extraire les roches dures, et de scies en cuivre pour extraire les roches plus tendres. @L@LLa plupart des carrières ne fonctionnaient que pendant l'inondation, lorsque les projets de construction publics battaient leur plein. Certaines carrières fonctionnaient toute l'année, surtout lorsqu'un grand projet, tel que l'édification d'une pyramide, était en cours. @L@LAfin de transporter les blocs de roches jusqu'à leur destination finale, on les plaçait sur un traîneau tiré par une équipe d'ouvriers. Des bûches faisaient souvent office de rouleaux, ce qui facilitait la progression du véhicule. On versait parfois de l'eau devant le traîneau pour lubrifier. @L@LUne partie de la main-d'oeuvre employée dans les carrières était constituée d'esclaves. Cependant, les Egyptiens constituaient le gros des ouvriers dans les carrières."
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
            text: "Bière",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La bière était la boisson préférée des Egyptiens. Les spécificités de la brasserie en Egypte suscitent de vifs débats. Comment brassait-on la bière ? Etait-elle parfumée à l'aide de fruits ? Faisait-on de la bière au blé ou à l'orge ? Et le maltage ? Des recherches sont en cours pour tenter de répondre à ces questions. @L@LEn se fondant sur des illustrations retrouvées sur les murs d'un tombeau, on a pu identifier l'une des méthodes employées par les Egyptiens pour fabriquer de la bière. Elle consistait à confectionner une miche de pain spéciale que l'on écrasait avant de la placer dans un van. On faisait ensuite pénétrer de l'eau dans le pain et l'on embouteillait la préparation ainsi obtenue pour la faire fermenter. Les femmes étaient les principales responsables du brassage de la bière et l'on a pu identifier 17 types de bière sur les papyrus. @L@LLes Egyptiens buvaient la bière dans des tasses spécialement conçues à cet effet. Elles étaient munies d'un tuyau incurvé ressemblant à une paille. Au bout de ce tuyau se trouvait un filtre qui permettait d'éliminer toute matière solide contenue dans la bière. Les Egyptiens buvaient de la bière chez eux, mais aussi dans les tavernes et les auberges. Pour en savoir plus sur ces établissements, cliquez @172ici."
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
            text: "Confection des papyrus",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La confection des papyrus était un processus relativement complexe. Il fallait, dans un premier temps, retirer l'écorce, afin d'exposer le coeur. Plusieurs coeurs étaient alors alignés, légèrement superposés, sur un morceau de tissu. Une fois la largeur voulue obtenue, on alignait d'autres bandes sur la première couche, à angle droit. Ensuite, on plaçait un second morceau de tissu au-dessus, et l'on battait l'ensemble à l'aide d'un gros morceau de bois ou d'un maillet. Les coeurs de papyrus étaient ainsi compactés. On étendait alors le papyrus au soleil pour qu'il sèche, puis sa surface était généralement polie à l'aide d'une pierre."
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
            text: "Armes",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "L'arsenal des Egyptiens comptait plusieurs armes. Pour le combat rapproché, les soldats utilisaient des armes telles que la massue, le poignard, le glaive ou la hache. Les principales armes utilisées pour le combat à distance étaient l'arc et les flèches, et plus rarement le lance-pierres. L'armement égyptien a évolué au fil du temps, et a fait un bon considérable en avant après l'invasion des Hyksos. Ces derniers introduisirent les chevaux et les chars."
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
            text: "Articles de luxe",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La nourriture, la boisson et l'habillement suffisaient aux paysans, mais les classes supérieures avaient besoin, pour maintenir leur style de vie, de certains produits particuliers. Le principal produit de luxe était le maquillage. Les hommes comme les femmes se maquillaient les yeux, à l'aide de kôhl ou de malachite. Outre le fait que l'utilisation de tels produits améliorait l'apparence physique, les Egyptiens pensaient que le maquillage des yeux était bon pour la vue. Les femmes utilisaient également le henné comme vernis à ongles et parfois pour se teindre les cheveux. @L@LLa propreté était importante pour les Egyptiens et ils prenaient régulièrement des bains et se parfumaient à l'aide d'huiles et d'extraits de diverses sortes. La myrrhe et l'encens étaient utilisés à cet effet. @L@LLe port de la perruque était également une question de propreté. La plupart des Egyptiens gardaient les cheveux courts, probablement pour éviter les poux, et portaient la perruque. Il y en avait de toutes sortes et la plupart des femmes en possédaient plusieurs. Elles étaient généralement fabriquées en vrais cheveux, que l'on attachait à la base de la perruque avec du fil. @L@LLa @382joaillerie était un autre luxe populaire pour les personnes les plus riches."
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
            text: "Poterie",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Très peu de maisons n'avaient pas de poteries. La fabrication de poteries, l'une des plus anciennes industries de l'Egypte antique, avait son origine dans le foyer, où les femmes produisaient tous types de récipients nécessaires à la cuisine. Comme d'autres industries en Egypte, la poterie fut peu à peu prise en charge par des ateliers. @L@LLa première étape de la confection de poteries était la préparation de l'@190argile. Il devait être travaillé et l'on ajoutait souvent de la paille pour le rendre plus compact. On malaxait l'argile à la main ou au pied, et on la piétinait pour qu'elle soit exploitable. On la plaçait ensuite sur un tour pour lui faire prendre la forme voulue. @L@LLe tour de potier a évolué au fil du temps. Dans sa forme originale, le potier le faisait tourner d'une main tout en modelant l'argile de l'autre. Comme le potier ne pouvait pas faire pivoter le tour très rapidement, la poterie devait être polie à la main ultérieurement. Sous le Nouvel Empire, une deuxième personne était chargée de faire pivoter le tour des deux mains tandis que le potier donnait leur forme aux objets. Le produit final était par conséquent plus harmonieux. A la fin du Nouvel Empire, le potier faisait de nouveau pivoter son propre tour, au pied cette fois-ci, ce qui permit de fabriquer la poterie la plus élégante jamais produite. @L@LUne fois les objets formés, on les faisait sécher. Ils étaient décorés pendant qu'ils séchaient. Une fois secs, on les faisait cuire dans un grand four avec un foyer à la base. Ce foyer était séparé dans la partie supérieure par une grille d'argile. La poterie était placée sur cette grille. La partie supérieure était scellée, à l'exception d'un trou pour l'évacuation de la fumée. Une fois la cuisson terminée, le produit était terminé et stocké jusqu'à son utilisation."
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
            text: "Bazars",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les bazars étaient des endroits bruyants et grouillants de monde. Les marchands, hommes et femmes, dressaient des étalages et les acheteurs apportaient des marchandises. Les bazars se trouvaient généralement en bordure du Nil, afin de pouvoir bénéficier des nouvelles marchandises arrivant par bateau. @L@LLes scènes se déroulant dans les bazars étaient fréquemment décrites sur les murs des tombeaux. La tombe de Khnumhotep et Niankhkhnum, manucures de la Vème dynastie auprès du pharaon, illustre une scène de marché animée mettant en scène un singe savant mordant la cheville d'un voleur à l'étalage."
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
            text: "Un village est né",

        }
        content {
            text: "@PBienvenue dans l'Egypte ancienne, terre des pharaons ! Vous allez prendre part à l'histoire de l'une des plus grandes civilisations que le monde ait jamais connues, une histoire qui couvre plus de quinze siècles. Vous dirigerez une famille, génération après génération, depuis sa naissance dans la préhistoire égyptienne, en passant par les balbutiements de la civilisation... jusqu'à l'établissement d'un empire unique et puissant... et même au-delà.     @PVotre histoire commence sur les berges du Nil, dans une région appelée Nubt, alors qu'une petite confédération de clans tente tant bien que mal de survivre dans un environnement hostile. Votre famille est à la tête de cette petite communauté. @PCe village a en priorité besoin d'habitations pour que les Egyptiens puissent s'y installer ; il lui faut également des chemins permettant aux habitants de circuler facilement."
        }
    }
    message_history_thinis_2 {
        id: 201,
        type: 3,
        size [40, 30]
        title {
            text: "This",

        }
        subtitle {
            text: "L'aube de la civilisation",

        }
        content {
            text: "@PAprès de nombreuses années, la nouvelle génération de votre famille s'est réinstallée dans la région de This, en Haute-Egypte. Un petit groupe de dirigeants locaux tente d'étendre son influence à la Basse-Egypte, ainsi qu'à toutes les terres bordant le Nil ; il veut unifier ce royaume sous le règne d'un chef suprême.   @PL'établissement de This comme cité florissante, prouvera la puissance de sa confédération et l'aidera à obtenir la suprématie sur la Basse-Egypte ainsi que sur les autres factions en quête de pouvoir. Mais il faudra pour cela offrir à la population des divertissements et construire de majestueux temples voués au culte de la divinité protectrice de la région. @PLa construction d'une telle cité nécessite certaines richesses. Vous trouverez de riches dépôts de minerai d'or à This, votre priorité étant de les exploiter."
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
            text: "Le Nil et ses dangers",

        }
        content {
            text: "La noblesse thinite poursuit ses efforts pour unir les terres du Nil sous un même administrateur suprême. Pour l'aider dans sa mission, vous devez développer une communauté prospère à Perwadjyt, dans la région humide du delta du Nil en Basse-Egypte. Vous étendrez ainsi l'influence de ces nobles sur l'ensemble du fleuve sacré. Pour administrer une population supérieure à celle d'un village, il vous faudra maîtriser les techniques de l'agriculture. @LLes fermiers égyptiens ont commencé à exploiter les grandes terres fertilisées par l'inondation annuelle du Nil en cultivant diverses plantes céréalières. Mais le Nil cache également bien des dangers. La menace rôde le long des rives ou au fond de ses eaux : des crocodiles féroces aux imposants hippopotames en passant par les moustiques porteurs de malaria."
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
            text: "Le premier pharaon",

        }
        content {
            text: "Tandis que les habitants des rives du Nil tentent tant bien que mal de survivre dans cet environnement hostile, un roi du nom de Narmer a pris le pouvoir. Bien que Narmer règne sur une grande partie du territoire, l'unification totale des deux royaumes reste à accomplir. En commémoration de son accession au trône, Narmer a désigné votre famille pour gouverner la nouvelle cité de Nekhen. Vous devrez construire des temples en l'honneur des différents dieux égyptiens ainsi que divers lieux de divertissement."
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
            text: "Une capitale est née",

        }
        content {
            text: "Après des luttes acharnées, le roi Hor-Aha est parvenu à unir les deux royaumes de Haute et Basse-Egypte. Il devient ainsi le pharaon qui règne en maître absolu sur toute l'Egypte ! Pour démontrer et asseoir sa souveraineté, la première dynastie d'Egypte, Hor-Aha a ordonné la construction d'une grande capitale à Men-nefer, d'où il pourra gouverner son jeune pays. En raison des loyaux services rendus par votre famille depuis des générations au pays, le pharaon vous a désigné comme architecte de cette grande cité. Cette capitale sera le symbole de notre royaume et les habitants devront donc jouir d'un cadre de vie agréable, jusque-là inconnu dans la région. Pour cela, votre rôle sera d'établir des échanges commerciaux avec les autres cités du royaume et de proposer une éducation de qualité à une certaine catégorie de la population. Vous veillerez également à la construction d'un mastaba sacré dédié à la noblesse de la cité."
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
            text: "Expédition au Sinaï",

        }
        content {
            text: "Un nouveau pharaon, Den, vient d'accéder au trône d'Egypte. Il affiche de vives inquiétudes au sujet des frontières du pays, sous la menace croissante des ennemis. Notre pays connaît une pénurie de cuivre, métal nécessaire à la fabrication d'armes pour nos troupes. Le pharaon Den a ordonné une expédition minière dans le Sinaï, une terre hostile et lointaine en plein territoire bédouin. La région de Timna, d'aspect aride, regorge pourtant d'or et de minerai de cuivre, ainsi que de pierres précieuses comme la turquoise. Les conditions de vie y sont difficiles et vous devrez importer de nombreuses marchandises voire de la nourriture ou de la toile directement d'Egypte. Le pharaon s'attend à des livraisons régulières de devises, cuivre, pierres précieuses et armes du Sinaï. Vous pouvez utiliser ces marchandises pour garantir le bon déroulement de l'expédition. Soyez vigilant car les Bédouins du Sinaï sont de redoutables adversaires et ils ne laisseront pas des étrangers occuper impunément leur territoire pour y piller leurs richesses minières. @PPour améliorer les conditions de vie dans cette région aride, construisez un pavillon aux endroits très fréquentés. Les habitants pourront ainsi s'y détendre en assistant à des numéros de jonglerie ou des concerts. Vous pouvez également fonder une école de danse pour procurer encore davantage de plaisir à vos concitoyens."
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
            text: "L'armée navale du pharaon",

        }
        content {
            text: "Les troupes militaires égyptiennes dominent le monde civilisé, mais le nouveau pharaon, Khasekhemwy de la seconde dynastie, exige l'installation d'une armée navale puissante à Behdet. Seule une flotte de navires de guerre serait en mesure de prendre le contrôle des océans. Mais le bois manque car les forêts sont peu abondantes sous notre climat. Le bois de cèdre peut être importé à grands frais de Byblos, une cité du Liban. Nos livraisons de papyrus permettent heureusement de compenser ces dépenses."
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
            text: "Le défi de la mer",

        }
        content {
            text: "Abjedu, le sanctuaire de nos ancêtres, est devenu avec le temps une immense nécropole de tombes sacrées. De nombreux nobles souhaitent faire de ce lieu leur demeure pour le repos éternel. Le nouveau pharaon Khasekhemwy de la seconde dynastie a ordonné la construction de trois mastabas sacrés (dont un de taille supérieure aux deux autres) en l'honneur de la noblesse locale.  @L@LLe pharaon a ordonné la création d'une puissante armée navale dans la cité de Behdet. Abjedu doit également accueillir quelques navires de guerre afin d'assurer la sécurité des cités côtières. La tâche risque d'être ardue. Nous vivons sous un climat aride, peu propice à l'exploitation des forêts et du bois. Le bois de cèdre peut être importé à grands frais de Byblos, une cité du Liban. Nos livraisons de papyrus permettent heureusement de compenser ces dépenses."
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
            text: "La route de l'Afrique",

        }
        content {
            text: "@PNebka a été proclamé premier pharaon de la troisième dynastie. Il a entrepris de profondes réformes structurelles en Egypte en ordonnant le partage du royaume en districts, appelés nomes, administrés par un nomarque. Bien que ce système puisse paraître rigide, l'Egypte est devenue sous son règne un pays prospère, notamment sur le plan architectural et artistique. @L@Ples caravanes de marchands qui voyagent d'oasis en oasis au coeur du continent africain, amènent en Egypte de nombreux produits rares et exotiques, très prisés par les populations locales. Ces convois sont malheureusement constamment attaqués par des guerriers libyens ou des Bédouins venant de l'est. Pour garantir la sécurité de ces voies commerciales, le pharaon Nebka, souverain du domaine du roseau et de l'abeille, vous demande d'établir un poste militaire dans l'oasis de Selima, un important lieu de passage des caravanes, situé bien au-delà des frontières du royaume.   @L@PLes quelques arbres qui s'y trouvent vous fourniront du bois dont la vente permettra d'entretenir cet avant-poste. Vous pourrez, grâce à la nouvelle mine de Timna au Sinaï, acheter du cuivre pour forger des armes. @L@PDans l'oasis de Selima, vous pourrez acheter de l'ébène aux marchands africains de Kerma. Une fois cet avant-poste établi, toutes les cités du royaume seront approvisionnées en ébène."
        }
    }
    message_history_abu {
        id: 209,
        type: 3,
        size [40, 30]
        title {
            text: "Abou",

        }
        subtitle {
            text: "La frontière nubienne",

        }
        content {
            text: "@PNebka a été proclamé premier pharaon de la troisième dynastie. Il a entrepris de profondes réformes structurelles en Egypte en ordonnant le partage du royaume en districts, appelés nomes, administrés par un Nomarque. Bien que ce système puisse paraître rigide, l'Egypte est devenue sous son règne un pays prospère, notamment sur le plan architectural et artistique.   @PLe pharaon souhaite étendre la frontière sud du royaume vers la Nubie. Il a ordonné la construction d'une cité à la première cataracte du Nil, sur l'île d'Abou. Il s'agit d'un emplacement idéal car le sous-sol regorge de pierres précieuses, de granit et de grès.   @PCes matériaux font l'objet d'une grande demande de la part de la noblesse d'Abjedu qui souhaite construire des monuments funéraires toujours plus élaborés dans la nécropole. Men-nefer, la capitale, a également besoin de briques pour la construction de tombes. Le pharaon Nebka commandera sûrement ces matériaux de construction.   @PLe pharaon Nebka a également ordonné à votre famille d'établir un poste militaire dans l'oasis de Selima afin de garantir la sécurité des caravanes de marchands en provenance des autres pays d'Afrique. Une fois établi, cet avant-poste constituera une source d'approvisionnement en ébène, un produit de luxe très recherché en Egypte."
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
            text: "La première pyramide",

        }
        content {
            text: "L'accession du pharaon Djoser au trône d'Egypte s'est accompagnée d'une période prospère faite de sagesse et d'importantes avancées sur le plan éducatif et artistique. La construction d'un cimetière royal est prévue sur le site de Saqqara pour servir de dernières demeures aux nobles comme Hezyre et Khabausokar, les plus fidèles courtisans du pharaon.   @PMais ce site devra également accueillir l'un des monuments les plus fabuleux que le monde ait jamais vu. Moi, Imhotep, vizir royal de Djoser, j'ai imaginé une nouvelle forme de tombe sacrée destinée au pharaon. Contrairement aux mastabas en terre des anciens pharaons, cette tombe s'élèvera vers le ciel comme plusieurs mastabas placés les uns sur les autres. Cette pyramide à degrés entièrement construite en pierre assurera la splendeur éternelle de notre souverain. L'édifice abritera un sarcophage de granit où le corps du pharaon reposera à jamais. @PLes prêtres de la nécropole d'Abjedu ont amélioré les techniques de momification grâce à l'utilisation de toile pour embaumer les morts, ouvrant ainsi les portes de la vie éternelle à tous les Egyptiens.  @PNotre poste commercial dans l'oasis de Selima est en pleine croissance. Grâce à lui, nous pouvons importer de l'ébène d'Afrique.  @PLe pharaon vous a octroyé une importante somme d'argent pour mener à bien ce projet. Ne le décevez pas."
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
            text: "Le Bédouin de l'est",

        }
        content {
            text: "Comme Den, son prédécesseur, le pharaon Huni a ordonné une expédition dans le désert du Sinaï pour collecter des pierres précieuses et du cuivre. Il souhaite que vous preniez le commandement de l'expédition en direction de Serabit Khadim, un lieu où subsistent quelques vestiges d'un avant-poste égyptien. Nous ne connaissons pas l'état de ces ruines, mais elles pourront servir de refuge en cas d'attaque.   @PN'oubliez pas que la dernière expédition envoyée dans la région n'est jamais revenue. Nous n'avons également aucune nouvelle des hommes partis à sa recherche. Mais nos soldats ont besoin d'armes efficaces en cuivre, un métal rare dans notre royaume. @PSoyez vigilant car vous risquez à tout moment de tomber dans une embuscade préparée par les Bédouins du Sinaï ou nos ennemis cananéens. Récupérez autant de cuivre et de pierres précieuses que possible afin de satisfaire les exigences du pharaon. S'il vous reste des pierres précieuses, vous pouvez faire appel à des orfèvres afin qu'ils créent des bijoux pour les habitants de l'avant-poste."
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
            text: "Une nécropole royale",

        }
        content {
            text: "Le pharaon Huni désire reposer pour l'éternité dans une pyramide à degrés comme son prédécesseur Djoser. Il souhaite être entouré par les tombes de ses courtisans et a choisi la cité de Meidum, en Basse-Egypte, comme site de construction de la nécropole royale.   @PEn récompense des loyaux services offerts depuis des générations par votre famille, Huni vous donne le droit d'être enterré à Meidum, dans votre propre tombe. Ce geste honore ainsi toute votre famille. @PPour garantir la pérennité de la sagesse et des enseignements égyptiens, le pharaon Huni souhaite la construction de plusieurs bibliothèques royales. Les grandes familles de la noblesse pourront ainsi s'éduquer en consultant les nombreux papyrus que ces bâtiments abriteront.  @PLe pharaon a envoyé un autre de ses fidèles courtisans à Serabit Khadim, dans le désert du Sinaï, afin qu'il rapporte des pierres précieuses. Si cette expédition se déroule sans encombre, vous pourrez commencer l'importation de pierres précieuses en provenance de cette région. Les orfèvres peuvent également confectionner des bijoux de luxe destinés aux habitants de votre cité. @PLa cité de Behdet, jadis florissante, connaît un important déclin et n'exporte plus les marchandises qui faisaient sa renommée."
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
            text: "Invasion de la Nubie",

        }
        content {
            text: "Notre nouveau pharaon, Snofru, souhaite que la quatrième dynastie connaisse le plus grand règne de l'histoire égyptienne. Dans sa politique d'expansion au sud du royaume, il a décidé d'envahir la Nubie afin d'y construire une citadelle à Buhen, près de la deuxième cataracte du Nil. Vous devrez alors ériger un obélisque de granit pour montrer au reste du monde que cette région appartient désormais à l'Egypte et à son pharaon. Le granit étant absent de cette partie méridionale de l'Egypte, il vous faudra importer la roche depuis la cité d'Abou.   @PA Buhen, vous devrez affronter de féroces guerriers nubiens, qui se battront jusqu'à la mort pour empêcher la construction de cet avant-poste sur leur territoire. N'ayez crainte, après un entraînement rigoureux dispensé à l'académie militaire, vos soldats seront prêts au combat. Nos ingénieurs militaires ont par ailleurs mis au point différentes armes défensives telles que des tours fortifiées, des murs et des corps de garde. Ces dispositifs serviront à repousser les attaques de l'armée nubienne. Vous pouvez, le cas échéant, utiliser des navires de transport de troupes pour amener rapidement vos soldats sur le lieu des combats.  @PAu nord, nous avons établi des relations commerciales avec la cité d'Enkomi, sur l'île de Chypre. Cette région est réputée pour ses réserves en minerai de cuivre, un métal dont nous faisons une grande consommation. Grâce à l'installation d'une exploitation minière à Serabit Khadim, dans le désert du Sinaï, nous sommes cependant en mesure d'importer du cuivre à un prix bien inférieur. Mais l'exploitation de Serabit Khadim est régulièrement prise pour cible par les Bédouins et les Cananéens, et nous craignons que les forces égyptiennes sur place ne puissent contenir ces attaques répétées.  @PUn somptueux monument funéraire dédié au pharaon est actuellement en cours de construction sur le site de Dahshur. Pour mener ce projet à terme, le pharaon vous demandera de veiller à l'approvisionnement du site en blocs de calcaire."
        }
    }
    message_history_south_dahshur {
        id: 214,
        type: 3,
        size [40, 30]
        title {
            text: "Sud de Dahshur",

        }
        subtitle {
            text: "La pyramide penchée de Snofru",

        }
        content {
            text: "@PNotre nouveau pharaon, Snofru, souhaite que la quatrième dynastie connaisse le plus grand règne de l'histoire égyptienne. Ses architectes ont imaginé une tombe encore plus spectaculaire que la pyramide de Huni et le pharaon souhaite que vous supervisiez les travaux. Il vous faudra définir l'emplacement idéal pour la construction du monument, dans la partie sud de Dahshur, la cité où sera érigée la pyramide penchée du pharaon. La ville fournira la main-d'oeuvre nécessaire à la réalisation de cet ambitieux projet. @PLa pyramide penchée sera construite en pierre et recouvertes de blocs de calcaire blanc afin qu'elle puisse briller pour l'éternité sous le soleil du désert. Vous disposez de réserves suffisantes en calcaire à Dahshur, mais les blocs de pierre devront être importés. @PLe pharaon souhaite étendre nos frontières au sud du pays. Pour cela, il a ordonné à ses troupes d'envahir la Nubie afin d'y construire une citadelle à Buhen, près de la deuxième cataracte du Nil. @PAu nord, l'Egypte a établi des relations commerciales avec la cité d'Enkomi, sur l'île de Chypre. Cette région est réputée pour ses réserves en minerai de cuivre, l'une de nos principales importations.  @PLe nouvel avant-poste de Serabit Khadim, dans le désert du Sinaï fournit une importante quantité de pierres précieuses. Nous avons connu récemment des problèmes d'approvisionnement en raison d'incessantes attaques de la part des Bédouins et des Cananéens, et nous craignons que les forces égyptiennes sur place soient bientôt débordées."
        }
    }
    message_history_north_dahshur {
        id: 215,
        type: 3,
        size [40, 30]
        title {
            text: "Nord de Dahshur",

        }
        subtitle {
            text: "La vraie pyramide",

        }
        content {
            text: "@PLe pharaon Snofru a ramené l'ordre et la paix en Egypte, et le royaume prospère désormais sous ses sages conseils. Snofru souhaite construire un autre monument sur le site de Dahshur, encore plus ambitieux que la pyramide penchée qui vient d'être achevée. Les architectes, conseillers et ingénieurs royaux pensent être en mesure de concevoir un édifice dont les faces s'élèveraient harmonieusement pour former un sommet parfait. S'ils y parviennent, l'Egypte assistera à la naissance de la première vraie pyramide, le tombeau éternel du grand pharaon Snofru !    @PL'épouse du pharaon, la reine Hetehpheres, vient de mettre au monde un fils du nom de Koufou. Notre peuple redoute l'arrivée au pouvoir de cet enfant car, d'après les prédictions d'Horus, Dieu du pharaon, il n'héritera pas de la bienveillance dont à témoigné son père envers le peuple d'Egypte. Le futur pharaon réalisera sans doute de grands projets, mais les habitants craignent que l'Egypte ne se retrouve étouffée sous le joug d'un tyran.  @PIl vous faudra importer du bois de la cité de Byblos, car les charpentiers devront construire des rampes pour permettre aux ouvriers d'acheminer les blocs de pierre au sommet de la grande pyramide."
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
            text: "La défense de l'Egypte",

        }
        content {
            text: "@PLe pharaon Koufou vient d'accéder au trône d'Egypte et, comme le prédisaient les oracles d'Horus et de Rê, notre peuple ressent déjà l'oppression de sa politique.  @PKoufou a ordonné l'envoi d'un gouverneur du royaume à Iunet, afin de défendre notre pays contre les envahisseurs éthiopiens. La cité d'Iunet possède une petite industrie de pêche, qui devrait permettre de nourrir les habitants pendant quelques temps. En cas d'invasion par la mer, les bateaux de pêche risquent d'être attaqués. Il est donc préférable de réserver les rivages aux navires de guerre. Si la nourriture vient à manquer, le bétail fournira de la viande, bien que les troupeaux consomment une importante quantité de paille et que cette ressource soit rare dans la région. Cette paille étant également nécessaire à la confection de briques pour les mastabas, vous devez établir des relations commerciales avec d'autres cités productrices de ce matériau. @PLa cité de Byblos au Liban, le pays des cèdres, a entamé des échanges commerciaux avec les puissants empires d'Orient. Ces pays, l'Assyrie et l'Ur, forment une région appelée Mésopotamie, située entre deux grands fleuves, qui fournit à Byblos un ivoire d'une qualité exceptionnelle. Avec des marchandises d'une telle valeur, la cité Iunet est assurée de connaître une longue prospérité. @PLes habitants de la capitale se divertissent avec un nouveau jeu appelé senet. Les joueurs de senet aiment se réunir autour d'une cruche de bière dans une taverne de jeux. Ces établissements permettent aux habitants d'Iunet d'oublier pendant quelques temps la tyrannie du pharaon Koufou. @PLe pharaon a ordonné la mise en place de nombreuses carrières sur le site d'On, dans le delta du Nil, afin d'extraire assez de calcaire pour ses futurs projets. Seuls les dieux connaissent les desseins du pharaon. On raconte qu'il envisage la construction d'un monument colossal sur le plateau situé à l'extérieur de la cité de Rostja. Il souhaiterait, grâce à cet édifice, connaître une plus grande gloire que son père, le sage et bienveillant pharaon Snofru, dont les deux nobles pyramides avaient fait la renommée."
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
            text: "L'ivoire de l'est",

        }
        content {
            text: "@PLe pharaon Koufou vient d'accéder au trône d'Egypte et, comme le prédisaient les oracles d'Horus et de Rê, notre peuple ressent déjà l'oppression de sa politique. On raconte qu'il envisage la construction d'un monument colossal sur le plateau situé à l'extérieur de la cité de Rostja. Il souhaiterait, grâce à cet édifice, connaître une plus grande gloire que son père, le sage et bienveillant pharaon Snofru, dont les deux nobles pyramides avaient fait la renommée.  @PLe pharaon Koufou a ordonné l'excavation de plusieurs carrières à Tura, dans le delta du Nil, où a récemment été découvert un important gisement de calcaire. Vous devez également construire trois mastabas pour la noblesse de la région, afin que le pharaon puisse honorer leur dévotion. Le gisement portera le nom de On et devra fournir un excellent calcaire pendant de longues années... seuls les dieux ont connaissance de l'usage que le pharaon fera de ce calcaire. @PLa cité de Byblos au Liban, le pays des cèdres, a entamé des échanges commerciaux avec les puissants empires d'Orient. Ces pays, l'Assyrie et l'Ur, forment une région appelée Mésopotamie, située entre deux grands fleuves, qui fournit à Byblos un ivoire d'une qualité exceptionnelle. Avec des marchandises d'une telle valeur, la cité d'On est assurée de connaître une longue prospérité. @PKoufou a également envoyé un gouverneur du royaume dans la cité d'Iunet afin de défendre notre pays contre les envahisseurs éthiopiens. Les vizirs n'envient guère la position du gouverneur car cette mission s'annonce très périlleuse.  @PLes habitants de la capitale se divertissent avec un nouveau jeu appelé senet. Les joueurs de senet aiment se réunir autour d'une cruche de bière dans une taverne de jeux. Ces établissements permettant aux habitants d'Iunet d'oublier pendant quelques temps la tyrannie du pharaon Koufou."
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
            text: "La Grande Pyramide et le Sphinx",

        }
        content {
            text: "Le pharaon Koufou a enfin fait connaître ses desseins et ses sujets risquent de payer cher sa soif de conquête. Malgré sa tyrannie, le pharaon respecte votre famille puisqu'il vous a donné le titre de nomarque. Il vous a également désigné comme responsable du plus grand projet de construction jamais entrepris dans le royaume.   @PLa demeure éternelle du pharaon aura la forme d'une imposante pyramide et sera située à l'écart de la cité, sur le plateau de Rostja. Son sarcophage sera taillé dans du granit, posé sur une barque funéraire en cèdre du Liban. A côté de cette pyramide, une autre pyramide plus petite sera construite en l'honneur du prince Khafra, un nomarque aussi tyrannique que son père, mais encore loin de l'égaler sur le plan des oeuvres accomplies. Khafra a également exigé que son effigie soit gravée dans la roche de Rostja, sous la forme d'un sphinx, un animal fantastique avec un corps de lion et un visage humain. @PPour permettre la construction de cet immense édifice, il vous faudra mettre en place un site de construction à Rostja. Vous devrez vous concentrer sur la réalisation de ces trois projets tout en honorant le pharaon.   @PLe pharaon vous enverra les blocs de calcaire servant à recouvrir les pyramides, mais il vous faudra acheter le reste des matériaux de construction à l'aide des recettes de la cité. @PLe pharaon vous a choisi parmi tous ses nomarques royaux pour réaliser ces trois travaux sacrés. Vous devrez montrer votre dévouement envers le pharaon et satisfaire ses exigences... quel qu'en soit le prix."
        }
    }
    message_history_bahariya_oasis {
        id: 219,
        type: 3,
        size [40, 30]
        title {
            text: "L'oasis de Baharièh",

        }
        subtitle {
            text: "Le désert occidental",

        }
        content {
            text: "@PLes règnes de Koufou et Khafra se sont éteints, entraînant la fin de la quatrième dynastie des pharaons d'Egypte. Mais une parente éloignée de la famille, Khentkaues, a donné naissance à un nouveau pharaon prénommé Ouserkaf. La grande lignée des pharaons peut ainsi perdurer. Ouserkaf est le premier souverain d'une cinquième dynastie qui annonce une ère d'importants bouleversements.   @POuserkaf s'est lancé dans la voie de la décentralisation en accordant plus de pouvoir aux autorités locales. En tant que nomarque, vous pouvez diriger votre cité comme vous l'entendez. Le pharaon ne souhaite entreprendre aucune construction de tombeau funéraire car il a actuellement un autre projet à vous soumettre. @PLe pharaon a désigné Rê, le dieu du soleil et du royaume, roi des dieux et il entend proclamer sa souveraineté dans tout le pays. L'Egypte possède de nombreux temples du soleil, mais le pharaon souhaite étendre l'influence de Rê aux confins du royaume. @PPour cette tâche, vous devez construire une citadelle sur l'oasis de Baharièh, au coeur du désert occidental. Utilisez l'eau avec parcimonie car cette ressource, très rare dans une région aussi éloignée du Nil, est convoitée par les animaux sauvages qui rôdent dans le désert. Méfiez-vous également des guerriers libyens et des Bédouins qui attaquent sans relâche les caravanes de nomades. Organisez votre défense et utilisez les ressources disponibles (bois et gibier) de l'oasis."
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
            text: "Le temple du soleil",

        }
        content {
            text: "@PLes règnes de Koufou et Khafra se sont éteints, entraînant la fin de la quatrième dynastie des pharaons d'Egypte. Mais une parente éloignée de la famille, Khentkaues, a donné naissance à un nouveau pharaon prénommé Ouserkaf. La grande lignée des pharaons peut ainsi perdurer. Ouserkaf est le premier souverain d'une cinquième dynastie qui annonce une ère d'importants bouleversements.   @POuserkaf s'est lancé dans la voie de la décentralisation en accordant plus de pouvoir aux autorités locales. En tant que nomarque, vous pouvez diriger votre cité comme vous l'entendez. Le pharaon ne souhaite entreprendre aucune construction de tombeau funéraire car il a actuellement un autre projet à vous soumettre. @PLe pharaon a désigné Rê, le dieu du soleil et du royaume, roi des dieux et il entend proclamer sa souveraineté dans tout le pays. L'Egypte possède de nombreux temples du soleil, mais le pharaon souhaite construire un immense temple à Djedu, dans la région humide du delta du Nil, en Basse-Egypte.  @PLa région de Djedu, comme la majeure partie du delta, regorge de gibier, poissons et autres animaux sauvages. La végétation y est également luxuriante mais les ressources minérales restent faibles. Pour cette raison, le grès nécessaire à la construction du temple du soleil doit être amené depuis les carrières d'On. Vous pouvez élever du bétail et obtenir ainsi de la viande, mais les troupeaux consomment une grande quantité de fourrage. @PIl vous faudra défricher l'emplacement choisi pour la construction du temple du soleil. Pensez à vendre autant de bois que possible. Les cités de Behdet et d'Abjedu manquent continuellement d'eau et de gibier. Vous pouvez par conséquent leur vendre ces marchandises afin de réduire les coûts de construction du monument sacré."
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
            text: "La menace éthiopienne",

        }
        content {
            text: "@PLe pharaon Pépi vient d'accéder au trône d'Egypte. En raison des bons et loyaux services rendus par votre famille, vous voilà devenu chancelier. Ce règne exceptionnel de 94 ans, le plus long de toute l'histoire, a pourtant laissé des traces douloureuses dans la vie des Egyptiens. Le pouvoir central perd peu à peu de son autorité au profit des administrations locales. Certaines régions ont eu de mauvaises récoltes et le spectre de la famine commence à planer sur toute l'Egypte. Men-nefer, une cité jadis resplendissante, connaît un lent et inexorable déclin et les oracles sont très pessimistes pour l'avenir... @PNos puissants voisins cherchent à profiter de la situation de faiblesse dans laquelle est plongé le royaume. L'avant-poste de Buhen a été assiégé par les soldats éthiopiens de Kerma, la plus grande ville non égyptienne d'Afrique. Ils exigent un tribut et se montreront impitoyables à la moindre provocation. La Nubie a également déclaré la guerre à notre pays et cherche à récupérer les terres annexées par l'Egypte.  @PPour éviter que le royaume ne s'asphyxie, vous devez tout faire pour préserver les routes commerciales permettant aux marchandises d'entrer et de sortir d'Egypte. Veillez en particulier au bon fonctionnement de l'avant-poste situé dans l'oasis de Selima. Le pharaon Pépi, en prévision de son voyage vers l'au-delà, vous demandera une grande quantité de pierres pour la construction de sa pyramide. D'autres cités, en pénurie de nourriture, chercheront également à obtenir votre aide. @PSachez utiliser les différentes ressources disponibles. L'oasis peut fournir une grande quantité de bois, mais vous devrez défricher la forêt pour avoir accès aux rares points d'eau."
        }
    }
    message_history_dakhla {
        id: 222,
        type: 3,
        size [40, 30]
        title {
            text: "Dakhlèh",

        }
        subtitle {
            text: "La caravane",

        }
        content {
            text: "@PLe pharaon Pépi vient d'accéder au trône d'Egypte. En raison des bons et loyaux services rendus par votre famille, vous voilà devenu chancelier. Ce règne exceptionnel de 94 ans, le plus long de toute l'histoire, a pourtant laissé des traces douloureuses dans la vie des Egyptiens. Le pouvoir central perd peu à peu de son autorité au profit des administrations locales. Certaines régions ont eu de mauvaises récoltes et le spectre de la famine commence à planer sur toute l'Egypte. Memphis, une cité jadis resplendissante, connaît un lent et inexorable déclin et les oracles sont très pessimistes pour l'avenir...  @PNos puissants voisins cherchent à profiter de la situation de faiblesse dans laquelle est plongé le royaume. L'avant-poste de Buhen a été assiégé par les soldats éthiopiens de Kerma, la plus grande ville non égyptienne d'Afrique. Ils exigent un tribut et se montreront impitoyables à la moindre provocation. La Nubie a également déclaré la guerre à notre pays et cherche à récupérer les terres annexées par l'Egypte.  @PEssayez de conserver la stabilité de l'Egypte en établissant un poste administratif dans l'oasis de Dakhlèh. Cette oasis possède un large éventail d'arbres précieux, mais ceux-ci bloquent malheureusement l'accès à l'étendue d'eau. A partir de cette oasis, vous devez importer de l'ébène en provenance du centre de l'Afrique. Le pharaon Pépi, en prévision de son voyage vers l'au-delà, vous demandera une grande quantité de pierres pour la construction de sa pyramide. D'autres cités, en pénurie de nourriture, chercheront également à obtenir votre aide."
        }
    }
    message_history_thinis {
        id: 223,
        type: 3,
        size [40, 30]
        title {
            text: "This",

        }
        subtitle {
            text: "Guerre civile",

        }
        content {
            text: "Le bon vieux temps désormais n'est plus et nombreuses sont les personnes qui craignent que l'Egypte ne retrouve jamais sa gloire passée. Osiris a abandonné le peuple et de faibles crues ont engendré une famine terrible. Les pharaons, autrefois tout puissants, ont cédé la place à des administrateurs provinciaux qui ne cessent de se chamailler. @PDe ce chaos ont émergé deux familles issues de la noblesse qui se battent pour prendre le contrôle du pays. Particulièrement cruelle et peu soucieuse de la famine touchant le peuple, la famille des Henen-nesw se présente comme l'héritière directe du trône. Au sud du pays, se trouve la nouvelle famille des Inyotef. Cette famille qui a beaucoup fait pour réunifier le sud, possède un certain pouvoir à Ouaset. Mais aujourd'hui, Ouaset est ravagé par une violente guerre civile fomentée par les Henen-nesw et visant le contrôle de toute l'Egypte. @PPour prouver leur générosité au peuple égyptien, les Inyotef vous ont confié la reconstruction de la cité nouvellement conquise de This, l'une des plus anciennes cités d'Egypte. Deux des bâtiments les plus anciens et les plus raffinés de This ont survécu à la prise de la ville : le temple d'Osiris et la demeure royale. Les Inyotef ont assuré que si l'un de ces bâtiments devait être détruit, aucun fonds ne serait accordé pour leur reconstruction. Les administrateurs de Ouaset, quant à eux, considèrent la restauration de This comme une priorité et des fonds considérables sont rassemblés dans ce but, même en cette période de diète. Ramenez This à sa splendeur passée, puis affrétez un navire et faites lever une puissante armée pour défendre la cité contre les fréquentes attaques des soldats vouant allégeance à la famille Henen-nesw ou contre celles Sauty, de Nekhen et de Khnoum. Prenez garde, car ils pourraient exiger un tribut dans le but de tester votre loyauté et par la même occasion vous extorquer quelques debens. Soyez également vigilant envers les Ethiopiens qui sont prêts à tirer profit des luttes intestines égyptiennes pour fondre sur le pays."
        }
    }
    message_history_waset {
        id: 224,
        type: 3,
        size [40, 30]
        title {
            text: "Ouaset",

        }
        subtitle {
            text: "Guerre civile",

        }
        content {
            text: "Le bon vieux temps désormais n'est plus et nombreuses sont les personnes qui craignent que l'Egypte ne retrouve jamais sa gloire passée. Osiris a abandonné le peuple et de faibles crues ont engendré une famine terrible. Les pharaons, autrefois tout puissants, ont cédé la place à des administrateurs provinciaux qui ne cessent de se chamailler. @PDe ce chaos ont émergé deux familles issues de la noblesse qui se battent pour prendre le contrôle du pays. Particulièrement cruelle et peu soucieuse de la famine touchant le peuple, la famille des Henen-nesw se présente comme l'héritière directe du trône. Au sud du pays, se trouve la nouvelle famille des Inyotef. Cette famille qui a beaucoup fait pour réunifier le sud, possède un certain pouvoir à Ouaset. Mais aujourd'hui, Ouaset est ravagé par une violente guerre civile fomentée par les Henen-nesw et visant le contrôle de toute l'Egypte. @PLes Inyotef qui combattent actuellement les Henen-nesw, vous ont confié la reconstruction de leur cité mère, Ouaset. Si les Inyotef remportent le combat contre les Henen-nesw, assoyant ainsi leur réputation dans toute l'Egypte, Ouaset deviendra alors la pierre angulaire vers laquelle les autres cités se tourneront, accordant aide à tous ceux qui feront appel à elle. Ouaset, qui en cas de victoire des Inyotef deviendra leur capitale, se doit d'être une grande cité. A l'aide des quelques ressources encore disponibles, construisez un temple solaire et une pyramide pour montrer aux Egyptiens la gloire des Inyotef. @POuaset n'est pas non plus à l'abri des attaques. Les Henen-nesw et leurs loyaux serviteurs menacent votre cité de temps à autre, essayant d'extorquer quelques debens de son trésor. Pour soustraire Ouaset à ces risques, levez une puissante armée de terre et affrétez une flotte qui défendra votre cité, ainsi que les autres cités menacées."
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
            text: "Réunification",

        }
        content {
            text: "La fidélité de votre famille durant la guerre civile n'aura pas été vaine. En tant que pharaon Mentuhotep, je confère à votre famille le titre de vizir. Nul autre que vous ne peut se vanter d'avoir mon entière confiance. Maintenant que les royaumes de la Basse et Haute-Egypte sont réunifiés et que la capitale de Ouaset est florissante, vous devez m'aider à asseoir ma position dans le royaume. @PBien que réunifiée, l'Egypte est aux prises à des querelles intestines, notamment dans les territoires autrefois régis par les Henen-nesw. Pour aider à la pérennité de notre nouvelle union, vous devez reconstruire, puis défendre Kebet. Cette cité devra être glorieuse, car elle sera le reflet des bienfaits réalisés sous mon règne. La cité étant soumise à de fréquentes attaques de la part des cités loyalistes, comme Khnoum, apprêtez-vous à la défendre. @PLa famine touchant l'ensemble du pays, de nombreuses requêtes provenant des autres cités du royaume vous parviennent. Répondez le plus rapidement possible à ces demandes afin que ma générosité et la dévotion de mon très dévoué vizir soient connues dans toute l'Egypte. @PJe sais que je vous en demande beaucoup, mais vous êtes le seul à pouvoir accomplir une telle tâche."
        }
    }
    message_history_menat_khufu {
        id: 226,
        type: 3,
        size [40, 30]
        title {
            text: "Menat Koufou",

        }
        subtitle {
            text: "Réunification",

        }
        content {
            text: "La fidélité de votre famille durant la guerre civile n'aura pas été vaine. En tant que pharaon Mentuhotep, je confère à votre famille le titre de vizir. Nul autre que vous ne peut se vanter d'avoir mon entière confiance. Maintenant que les royaumes de la Basse et Haute-Egypte sont réunifiés et que la capitale de Ouaset est florissante, vous devez m'aider à asseoir ma position dans le royaume. @PBien que réunifiée, l'Egypte est aux prises à des querelles intestines, notamment dans les territoires autrefois régis par les Henen-nesw. Pour aider à la pérennité de notre nouvelle union, vous devez reconstruire, puis défendre Menat Koufou. Cette cité devra être glorieuse, car elle sera le reflet des bienfaits réalisés sous mon règne. @PLa famine touchant l'ensemble du pays, de nombreuses requêtes provenant des autres cités du royaume vous parviennent. Répondez le plus rapidement possible à ces demandes afin que ma générosité et la dévotion de mon très dévoué vizir soient connues dans toute l'Egypte. @PJ'ai une seconde noble tâche à vous confier. Je désire que vous fassiez ériger des obélisques en granit comme symbole de mon entière dévotion pour ce pays au cours de mon passage terrestre. @PJe sais que je vous en demande beaucoup, mais vous êtes le seul à pouvoir accomplir une telle tâche."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itjtawy", pos [50, 80] }
        subtitle { text: "Une nouvelle capitale est née", pos [10, 30] }
        content {
            text: "O puissant pharaon, fils de Rê, comme vous devez être heureux. Votre ascension fulgurante au trône d'Egypte est un miracle ! Plus belle récompense ne pourrait être envisagée par les dieux ou le peuple. Grâce à l'accession au trône de votre famille, l'Egypte va prendre désormais un nouveau départ, et peut-être arriverons-nous à oublier les horreurs de la guerre civile. @PPour marquer cette nouvelle ère, vous devez construire une capitale d'un grand raffinement. Avec des ressources naturelles en abondance, Itjtawy est un endroit parfait. En tirant profit des richesses de la région, vous pouvez construire une cité merveilleuse à la hauteur de la valeur et du dévouement de votre dynastie. @PAfin que les bienfaits sous votre grande dynastie restent à jamais dans les mémoires, vous devez construire deux majestueuses pyramides en briques pour vous-même et votre famille, ainsi qu'un sphinx redoutable qui gardera votre tombe. Une famille telle que la vôtre ne mérite pas moins. @PGardez à l'esprit, cependant, que certaines personnes dans le pays remettent en cause votre légitimité. Un grand nombre d'entre eux souffrent encore des effets de la famine et murmurent que vous avez usurpé le trône. Si vous soulagez le peuple de ses misères et que vous l'aidez à reconstruire ses maisons, vous gagnerez certainement son allégeance éternelle. Vous devez prévenir et résoudre les problèmes de vos sujets si vous ne voulez pas que ceux-ci prennent les armes contre vous."
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
            text: "Dans la Nubie",

        }
        content {
            text: "Maintenant que l'Egypte est enfin unifiée sous votre règne, l'ensemble de votre cour et moi-même, vote fidèle vizir, vous recommandons d'agrandir les frontières de notre pays vers le sud de la Nubie. Les rives asséchées du fleuve de Allaqi riches en or et l'imposante cité d'Iken, qui abrite votre résidence, décourageront certainement les Nubiens de toute attaque. Prenez garde aux Ethiopiens cependant. Ce sont des adversaires bien plus dangereux que les Nubiens et ils n'hésiteront pas à utiliser l'épée, O pharaon, pour vous faire quitter vos terres. @PPour laisser une empreinte durable dans la Nubie, vous devez construire un imposant obélisque, signe de la toute puissance de l'Egypte. L'obélisque sera la preuve évidente pour les Nubiens de la grandeur du règne égyptien. En outre, il restera un rappel constant de notre présence. @PAlors que vous vous concentrez sur Iken, gardez à l'esprit notre intention de créer une cité côtière ouvrant sur la mer Rouge à Sawu. Cette cité aura besoin de l'aide du pharaon et n'hésitera pas à faire appel à lui. Si Sawu prospère, elle pourra fournir Iken en cuivre pour forger des armes."
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
            text: "Sur les côtes de la mer Rouge",

        }
        content {
            text: "Maintenant que l'Egypte est enfin unifiée sous votre règne, nous devons développer le commerce avec d'autres cités dans le monde entier afin d'asseoir la croissance de l'Egypte, O roi des Deux Pays. @PAu fur et à mesure que votre peuple prospère, il demande de plus en plus de biens exotiques. Lassé par les bijoux, articles de luxe certes mais acquis trop facilement, votre peuple veut désormais des articles de luxe chers et rares, tel l'encens. Votre cour et moi-même, votre fidèle vizir, nous vous recommandons de créer un port à Sawu au bord de la mer Rouge et d'ouvrir une route commerciale avec la contrée lointaine de Pwenet, d'où l'encens le plus fin au monde peut être importé à des prix très élevés. @PEn plus de modestes veines de minerai d'or et de cuivre, Sawu exploite également quelques matières premières et pourrait évoluer vers la fabrication de produits finis. Grâce à l'exportation des produits finis et à l'importation de matières premières en provenance des partenaires commerciaux, Sawu devrait pouvoir générer un certain profit. @PTandis que vous vous afférez à Sawu, l'un des nomarques les plus vaillants met en place un nouveau carrefour commercial en Nubie. Sa cité, Iken, a de fortes chances d'être attaquée, par conséquent, préparez-vous à lui envoyer des renforts. @PSous votre règne, Sawu est assurée de devenir l'une des cités les plus belles du royaume et elle semble toute désignée pour vous abriter vous et votre famille. Lorsque vous créerez le port, ne négligez pas les préparatifs pour votre passage vers l'au-delà. Un mausolée et une petite pyramide en briques offriront à votre famille et à vous-même des quartiers somptueux après votre passage dans l'au-delà."
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
            text: "Le gantelet",

        }
        content {
            text: "Tout puissant pharaon, les biens et territoires protégés par votre famille sont aujourd'hui menacés ! La flotte nubienne est partout sur le Nil, s'autorisant même des incursions au coeur du territoire égyptien, pillant villages et cités. En outre, les Nubiens n'hésitent pas à accoster vos navires marchants... Pour aider les cités se trouvant au nord du pays à repousser l'ennemi, vous devez envoyer des navires de guerre et des soldats aux cités en détresse.  @PPour empêcher les Nubiens de patrouiller dans vos eaux, vos conseillers militaires vous recommandent de construire un ensemble de forts à Heh entre la deuxième et la troisième cataractes du Nil. Les forts serviront à empêcher les Nubiens de descendre vers le sud du pays. @PAprès avoir repoussé les Nubiens, vous devrez conquérir la cité riche en ressources de Baki. La prise de cette cité pénalisera énormément l'économie nubienne. Une fois Baki reprise aux Nubiens, vous commencerez à importer du grès à partir de cette cité pour votre immense mausolée. Celui-ci rappellera aux Nubiens votre toute puissance.  @PDe nombreux défis vous attendent si vous souhaitez protéger l'Egypte des Nubiens. Prenez garde, O Grand Horus, à l'orage qui gronde à l'est. Le bruit assourdissant des sabots des chevaux se répercute dans tout Canaan et des chars rapides comme l'éclair dévastent tout sur leur passage. Ces effroyables chars, de ceux que vous n'avez encore jamais vus, sont conduits par les guerriers Hyksos. Déjà, des nuages noirs s'accumulent dans l'horizon égyptien et vous devrez vous armer de courage pour faire face à cet effroyable danger."
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
            text: "La cité de Bastet",

        }
        content {
            text: "Tout puissant pharaon, grâce aux routes commerciales en place, nous devrions désormais pouvoir montrer à l'Egypte les bienfaits du succès et de la richesse. Bubastis est l'endroit idéal pour une telle cité : nous pouvons protéger nos routes commerciales à l'est tout en rendant hommage à Bastet, le protecteur de l'Egypte. @PLa cité de Bastet devra être comme aucune autre en Egypte. Elle devra être aussi resplendissante qu'une fleur de lotus et fleurira de lieux de loisirs, d'écoles, de bibliothèques et de lieux de culte. Ses citoyens bénéficieront de l'importation des articles les plus raffinés, tel l'encens. Une fois terminé, Bubastis sera le joyaux des deux couronnes. @PTout en construisant cette glorieuse cité, prenez garde à l'orage qui gronde à l'est. Le bruit assourdissant des sabots des chevaux se répercute dans tout Canaan et des chars rapides comme l'éclair dévastent tout sur leur passage. Ces effroyables chars, de ceux que vous n'avez encore jamais vus, sont conduits par les guerriers Hyksos. Déjà, des nuages noirs s'accumulent dans l'horizon égyptien et vous devrez vous armer de courage pour faire face à cet effroyable danger."
        }
    }
    message_history_khmun {
        id: 232,
        type: 3,
        size [40, 30]
        title {
            text: "Khnoum",

        }
        subtitle {
            text: "Appel à l'aide",

        }
        content {
            text: "Très puissant pharaon, l'Egypte réclame votre aide. Les terribles guerriers Hyksos ont envahi nos terres et ont établi leur propre capitale à Rowarty. A partir de cette cité, ils ont réussi à détourner plusieurs de nos voies commerciales, nous privant de denrées nécessaires. Nous devons mettre un terme à leur conquête avant qu'il ne soit trop tard. @PSi vous l'ordonnez, O Grand pharaon, nous irons leur reprendre la cité de Khnoum. Nous devons également préparer une flotte ainsi qu'une puissante armée, car nos compatriotes qui se trouvent au nord, et tout particulièrement à Rowarty, auront certainement besoin de renfort pour repousser l'incursion des guerriers Hyksos. Ils demanderont votre protection, O fils de Rê. En outre, nous possédons désormais une nouvelle arme. Nos chefs militaires ayant appris à se servir du terrible char, nous devrions pouvoir l'utiliser contre nos ennemis. Une fois les guerriers Hyksos repoussés hors du pays, nos conseillers militaires recommandent la construction d'un fort dans le Sinaï à Sharuhen pour prévenir de futures invasions par l'est. @PSi seulement nos problèmes pouvaient se limiter au nord ! Des rapports provenant de la frontière sud montrent que les Nubiens ont une fois de plus profité des tiraillements de l'Egypte. Ils se sont emparés des cités d'Iken et de Heh au sud du pays. Bien que ces cités soient sources de problèmes, nous devons d'abord repousser les guerriers Hyksos avant de nous concentrer sur le sud du pays. @PCes guerriers Hyksos sont des envahisseurs impies, car ils n'ont pas hésité à profaner la pyramide de Khnoum, volant au tout puissant pharaon les biens nécessaires au passage vers l'au-delà. Nous devons approvisionner une nouvelle fois notre pharaon pour satisfaire ses besoins dans l'au-delà."
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
            text: "Appel à l'aide",

        }
        content {
            text: "O roi des Deux Pays, l'Egypte réclame votre aide. Les terribles guerriers Hyksos ont envahi nos terres et ont établi leur propre capitale à Rowarty. A partir de cette cité, ils ont réussi à détourner plusieurs de nos voies commerciales, nous privant de denrées nécessaires. Nous devons mettre un terme à leur conquête avant qu'il ne soit trop tard. @PA Sauty, nous sommes à l'abri d'une attaque immédiate, bien que les guerriers Hyksos osent nous demander un tribut. Nous avons besoin de fournir des troupes et des armes à nos compatriotes qui se trouvent au nord, pour les aider à repousser l'incursion de ces guerriers. Ils comptent sur votre assistance, O Grand pharaon. En outre, nous possédons désormais une nouvelle arme. Nos chefs militaires ayant appris à se servir du terrible char, nous devrions pouvoir l'utiliser contre nos ennemis. @PSi seulement nos problèmes pouvaient se limiter au nord ! Des rapports provenant de la frontière sud montrent que les Nubiens ont une fois de plus profité des tiraillements de l'Egypte. Ils se sont emparés des cités d'Iken et de Heh au sud du pays. @PPour que l'Egypte réussisse à sortir intacte de cette période tumultueuse, vos généraux vont devoir mettre les bouchées doubles sur terre comme sur le fleuve. Pour encourager vos deux meilleurs généraux, vous avez promis de construire pour chacun d'eux une pyramide aussi spectaculaire que la vôtre. Fort de cette promesse, ceux-ci combattent vaillamment l'ennemi, puisant au fond d'eux la force et la vigueur nécessaires à la victoire. @PSi vous l'ordonnez, Grand pharaon, nous construirons trois pyramides magnifiques à Sauty, l'une pour vous-même et les deux autres pour vos généraux. Ces trois pyramides nécessitant une place considérable, vous devrez renoncer à de précieuses ressources. Vous aurez également  besoin d'étendre votre cité de l'autre côté du Nil pour profiter des ressources nécessaires à son épanouissement."
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
            text: "Expansion et conquête",

        }
        content {
            text: "L'Egypte est sortie plus forte de cette période tumultueuse. Byblos, avec ses forêts verdoyantes et ses riches sources de cuivre, est désormais nôtre ! Grâce à votre présence, la cité prospèrera et un nouveau royaume verra le jour. @PCependant, suite à la conquête de Byblos, nous avons fait une terrible découverte ! Un nouveau peuple, particulièrement féroce, les Hittites, ont conquis la plus grande partie de l'Asie et certains disent que leur empire rivaliserait en taille avec le nôtre. Ce peuple montre désormais un intérêt vivace pour Byblos et notamment pour ses richesses. Si nous ne nous préparons pas à leur attaque, nous aurons quelques difficultés à les repousser. @PTout en nous préparant à affronter les Hittites, nous devons marquer Byblos à jamais de notre empreinte. Avec votre accord, O pharaon, nous érigerons trois obélisques, un grand et deux petits, pour proclamer votre souveraineté et votre gloire à travers tout votre royaume. Ces monuments rappelleront aux habitants de Byblos qu'ils doivent vous être dévoués. @PTandis que nous nous occupons de Byblos, d'autres régions d'Egypte se préparent à attaquer. Les Nubiens se sont déplacés vers le nord et ont atteint la première cataracte. Nous devons aider nos compatriotes à les repousser. Les rapports provenant de Rowarty font état d'un mystérieux ennemi, le peuple de la Mer. Ces deux ennemis doivent être retenus si l'Egypte veut atteindre la gloire. Pour montrer votre puissance, envoyez des troupes et des navires de guerre à ceux qui le demandent."
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
            text: "La gloire de l'Egypte",

        }
        content {
            text: "Les guerriers Hyksos enfin hors de notre pays, un nouveau royaume est désormais prêt à voir le jour. Très noble pharaon, Baki est un endroit idéal pour commencer ce nouveau royaume. Nous pouvons utiliser l'importante quantité d'or trouvée ici pour réaliser votre nouvelle vision de l'Egypte. @PAlors que l'Egypte approche de son apogée, quelques problèmes persistent. De nombreuses cités égyptiennes pas encore tout à fait remises de l'invasion des guerriers Hyksos requièrent votre aide. Dans d'autres régions, les anciens ennemis de l'Egypte poursuivent leurs attaques, tandis qu'un nouvel adversaire, le peuple de la Mer, effectue des raids sur nos côtes nord. Préparez-vous à défendre les autres cités égyptiennes contre ces adversaires, récents ou anciens. @PAlors que l'Egypte poursuit sa croissance, de nombreuses cités envisagent de faire du commerce. Certaines de ces cités sont familières avec nos coutumes, et remplies du respect que vous inspirez, se considèrent elles-mêmes égyptiennes. D'autres, par contre, nous sont étrangères et commercent avec nous pour la première fois. Pour la gloire de l'Egypte, utilisez au mieux ces relations commerciales pour fournir à votre peuple tous les biens qu'il désire. @PPour entrer dans cette nouvelle ère, vos architectes royaux proposent de construire en votre honneur, O pharaon, deux pyramides et un mausolée majestueux. Ces monuments reflèteront la richesse et la grandeur que vous avez apportées à l'Egypte."
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
            text: "Le peuple de la Mer",

        }
        content {
            text: "O Grand Horus, notre emprise sur l'Asie est puissante et indiscutée, et nos frontières une nouvelle fois s'étendent profondément en Nubie. Cependant, les problèmes s'intensifient sur la côte nord. Le peuple de la Mer est de plus en plus agressif, organisant des raids sur nos cités de manière injustifiée. Seule la présence du pharaon pourra repousser cet adversaire féroce et rusé. Si vous préparez un navire, soutenu par une puissante armée, nous devrions pouvoir triompher du peuple de la Mer. @PTandis que vous travaillez à la défaite du peuple de la Mer, vos braves nomarques lancent des attaques dans le monde entier. Si celles-ci s'avèrent un succès, l'Egypte contrôlera le monde de l'Euphrate en Asie jusqu'à la tentaculaire cité éthiopienne de Kerma au sud. Une fois la victoire remportée par vos nomarques, votre dynastie restera dans les esprits comme celle qui aura le plus compté en Egypte. @PMarqué par votre influence incommensurable, Mycènes, un lointain partenaire commercial s'est présenté à nous. Le roi de Mycènes ayant pris connaissance de la splendeur et de la générosité de l'Egypte désire commercer avec nous. Si vous consentez à ouvrir cette nouvelle route commerciale, O pharaon, vos citoyens seront certainement approvisionnés en des biens exotiques encore inconnus. @PPour abriter votre famille royale dans l'au-delà, un imposant mausolée et deux impressionnantes pyramides de briques seront construits. Ces monuments rappelleront vos actes à tous ceux qui vous ont suivi en temps de guerre comme en temps de paix."
        }
    }
    message_history_hetepsensusret {
        id: 237,
        type: 3,
        size [40, 30]
        title {
            text: "Hetep Sénousret",

        }
        subtitle {
            text: "La gloire du pharaon",

        }
        content {
            text: "Bienveillant pharaon, vous avez apporté la paix et la prospérité à notre nation. Sous votre règne avisé, l'Egypte est redevenue un pays fort et glorieux. Tous les nomarques vous sont loyaux et plus aucune menace ne plane désormais sur notre grande nation. @PMaintenant que tous les objectifs établis par votre famille depuis de si nombreuses années ont été atteints, l'heure est aujourd'hui venue d'immortaliser les exploits de votre grande dynastie, en l'honorant par la construction de la plus imposante pyramide d'Egypte jamais réalisée, plus grande que celle de Koufou à Rostja elle-même. D'autres membres de votre noble famille se sont également sacrifiés pour vous permettre de régner sur toute l'Egypte. Ces membres ne doivent pas être oubliés, par conséquent, un mausolée en grès sera construit en leur honneur. @LHetep Sénousret, situé dans la riche région de Fayoum, serait l'emplacement idéal pour de tels monuments. Vous pourrez, depuis cette cité, prendre part à toutes les affaires de l'état et répondre aux nombreuses requêtes d'approvisionnement provenant des autres cités, tout en faisant construire votre immense pyramide."
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
            text: "Les berges du Nil",

        }
        content {
            text: "@PAvec l'aide de votre famille, le roi thinite Horus Aha est parvenu à unir les royaumes de Haute et de Basse-Egypte, se proclamant pharaon de toute l'Egypte et fondant une capitale imposante à Men-néfer.    @PVotre clan a de nouveau migré, cette fois-ci dans une région humide du Delta de Basse-Egypte, appelée Perwadjyt. Les navires de guerre cananéens ont menacé cette région et vous voudriez bien y envoyer quelques-uns de vos propres navires de guerre, le moment venu. @PVotre famille est entrée dans la noblesse. De ce fait, avant que vous ne passiez de vie à trépas, vous devez entreprendre la construction d'une superbe tombe en briques - un mastaba - qui abritera votre corps durant son voyage dans l'au-delà. @PAuparavant, vous devez installer des fermes sur les berges du Nil, afin d'exploiter le sol riche et fertile engendré par l'inondation annuelle du fleuve. Votre population pourra ainsi croître et prospérer, jusqu'à devenir suffisamment nombreuse pour achever la construction de ce monument sacré. Mais attention : les eaux du Nil cachent de nombreux dangers, tels que des crocodiles assoiffés de sang, des hippopotames et des moustiques porteurs de malaria. @L@LAgriculture en bordure du Nil @PVous devez construire des fermes directement sur la plaine inondable, afin de bénéficier de sa fertilité croissante. Contrairement à la plupart des structures de travail, ces fermes n'ont pas besoin d'un accès direct aux employés, mais d'une main-d'oeuvre paysanne régulière, fournie par les chantiers. Vous devez construire des chantiers à proximité des fermes de la plaine inondable, afin que les paysans n'aient pas un trop long trajet à effectuer. @G56 @L@LLa moisson annuelle @L@PLa crue annuelle du Nil fertilise la terre dévastée de la plaine inondable. Les paysans moissonnent la récolte annuelle juste avant l'inondation, puis la stockent dans vos greniers. Comme il n'y a qu'une moisson par an, vérifiez que vous disposez d'un nombre suffisant de greniers pour stocker la quantité de nourriture nécessaire à votre population en plein essor."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Nourriture ou famine ?", pos [0, 15] }
        content {
            text: "@PUne population croissante a besoin d'une source de nourriture fiable, ainsi que de moyens pour stocker et distribuer cette nourriture. Vous pouvez dans cette région chasser le gibier (comme les autruches). Les greniers permettent de stocker la viande et d'autres aliments, tandis que les bazars distribuent la nourriture aux habitants du village. Comme toutes les structures de travail, ces bâtiments doivent se trouver à proximité des habitations, et la cité doit disposer d'une main-d'oeuvre suffisante pour y travailler. @L@LChasse  @L@PConstruisez un pavillon de chasse à proximité des troupeaux d'autruches, pour que les chasseurs s'y installent. S'ils trouvent du gibier, ils le ramèneront au pavillon de chasse pour qu'il y soit préparé, après quoi un charretier le livrera au grenier le plus proche.   @PLes employés du bazar satisfont aux besoins des habitations dont ils ont la charge, se procurent de la nourriture auprès des greniers voisins et livrent cette nourriture aux habitations des environs immédiats. @G60 @PConstruisez des greniers et des bazars en cliquant sur le bouton 'Structures de stockage et de distribution'. @G77 @L@PEnfin, votre but dans cette mission est de transformer certaines de vos 'huttes' en 'petites cabanes'. Pour cela, vous devez les alimenter en nourriture en provenance du bazar. Vous devez en outre vous assurer que ces structures ne sont pas trop proches de bâtiments industriels disgracieux, ce qui risquerait de gêner l'évolution de l'habitat en limitant l'attrait de la région.   @L@LRapports @L@PUn rapport sur la nourriture et la population est maintenant disponible pour vous fournir des informations et vous conseiller. Vous aurez bientôt de nombreux rapports à votre disposition pour vous aider à diriger votre cité. @G76  @L@PPour y accéder, cliquez sur l'icône 'Rapports' ou cliquez avec le bouton droit de la souris sur le bâtiment en question."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Divertissements", pos [0, 15] }
        content {
            text: "A mesure que votre cité se développe, certains citoyens pratiquent des activités de loisirs. Une vaste gamme de divertissements prouve le riche patrimoine culturel d'une cité. Pour le moment toutefois, le seul divertissement que vous puissiez fournir aux habitants de votre cité est la jonglerie. @L@LLieux de divertissement et jongleurs  @PUn jongleur a besoin d'un lieu où pratiquer son art, le plus petit étant appelé 'étal'. Construisez un étal à un emplacement central pour les représentations des jongleurs, ainsi qu'une école de jonglerie à proximité. Ces deux bâtiments doivent avoir accès aux habitations des employés et doivent disposer d'une main-d'oeuvre suffisante. @PLes jongleurs formés à l'école de jonglerie se rendent à l'étal le plus proche pour effectuer des représentations, divertissant ainsi les habitants de la région. @G61 @L@LConsultez le rapport sur les divertissements pour en savoir plus sur les besoins en divertissements de votre cité. Cliquez sur 'Cartes : Loisirs' pour voir quelles habitations de votre cité ont accès aux activités de divertissement."
        }
    }
    message_gold_and_crime {
        id: 241,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Extraction de l'or" }
        content {
            text: "@L@LExtraction de l'or @L@PRecherchez des zones rocheuses contenant du minerai ; vous les reconnaîtrez grâce à leurs taches métalliques brillantes. Pour extraire le minerai, vous devez construire des mines d'or à proximité. @G53 @L@LPalais @L@PUn palais est nécessaire pour la transformation du minerai d'or, ainsi que pour le stockage des lingots. Le palais est le siège du gouvernement de la cité. Il doit donc être construit à proximité d'une nappe phréatique (zones herbeuses). @PUne fois votre palais construit, les mineurs livrent le minerai d'or depuis les mines d'or pour qu'il soit converti en espèces, que l'on subdivise en 'debens'. @G54 @L@LCriminalité @L@PUne réserve d'or engendre un risque de vol. Les officiers de police vous aident à limiter les pertes dues au vol en patrouillant les rues pour empêcher la criminalité et en soumettant tous les criminels qu'ils rencontrent. @G55 @L@PLa meilleure façon d'empêcher la criminalité est, toutefois, de satisfaire votre population, en lui offrant nourriture, soins et travail."
        }
    }
    message_farming_along_the_nile {
        id: 242,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Cultures le long du Nil",

        }
        content {
            text: "Cultures le long du Nil @L@PConstruisez les fermes sur des plaines inondables où la terre y est très fertile. Contrairement à d'autres structures, ces fermes n'ont pas besoin d'un accès direct à la main-d'oeuvre, mais vous devez construire des chantiers afin que les paysans puissent venir cultiver la terre. Placez les chantiers à proximité des fermes pour éviter que les paysans n'aient à parcourir de longues distances. @G56 @L@PChaque année, l'inondation du Nil apporte sur les rives du fleuve de riches limons qui permettent de fertiliser les terres appauvries par les cultures. Auparavant, les paysans procèdent à la récolte et stockent leurs produits dans des greniers. Avec une seule récolte par an, veillez à construire suffisamment de greniers pour emmagasiner toute la nourriture nécessaire à la population."
        }
    }
    message_developing_culture {
        id: 243,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Cultures",

        }
        content {
            text: "Bière @LLes Egyptiens sont passés maîtres dans l'art de brasser la bière, une boisson particulièrement appréciée dans tout le royaume ! Apportez l'orge cultivée dans les fermes locales aux brasseurs afin qu'ils produisent de la bière. Cette bière sera ensuite stockée dans l'entrepôt puis distribuée par les employés du bazar (comme pour la nourriture et la poterie). @L@LDivinités @LLe dieu protecteur de votre région est Rê, Osiris et Bastet étant des divinités locales. Construisez plusieurs temples et sanctuaires en l'honneur de Rê mais n'oubliez pas les autres divinités ! Pour le bien-être de vos citoyens, offrez leurs des temples en l'honneur de ces différents dieux. @L@LLoisirs @LLes Egyptiens aiment se détendre en écoutant de la musique ou en assistant à des spectacles de jongleurs. L'étal est réservé aux jongleurs, tandis que le kiosque peut accueillir des jongleurs et des musiciens. Construisez un kiosque à une intersection de routes et installez un conservatoire à proximité afin de former des musiciens. La variété des loisirs proposés dans une cité accroît considérablement la qualité de vie de ses habitants. @L@LLois et ordre @LVous pouvez réduire la criminalité en construisant des palais de justice afin que les magistrats sillonnent les rues de la cité à l'écoute des plaintes des citoyens."
        }
    }
    message_getting_started {
        id: 244,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Début de la partie",

        }
        content {
            text: "Commencez à prévoir des zones constructibles et des zones industrielles. En plus des éléments vitaux tels que la nourriture et l'eau, vous devez satisfaire les différents besoins de vos concitoyens (poterie, bière, loisirs et accès aux cultes religieux) avant d'envisager la construction de bâtiments éducatifs et de songer au commerce."
        }
    }
    message_soldiers_and_forts {
        id: 245
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Soldats et forts",
        }
        content {
            text: "Construisez un fort et un centre de recrutement pour lever une armée. Le centre de recrutement envoie les jeunes soldats, un par un, au fort jusqu'à ce que celui-ci soit complet. Il existe deux types de forts : les forts d'infanterie et les forts d'archers, chacun abritant une compagnie de seize soldats. Lorsque les soldats meurent au combat, le centre de recrutement convoque d'autres appelés. @G57 @L@LArmes @PLes archers fabriquent leurs propres arcs et flèches, tandis que les fantassins doivent être équipés de lances cuivrées. Pour confectionner ces lances, approvisionnez la fabrique d'armes en minerai de cuivre. Les nouvelles armes sont envoyées au centre de recrutement, qui les distribue ensuite aux jeunes soldats. @L@LObjectifs des missions @PDésormais, vos objectifs n'apparaissent plus en haut de l'écran. Cliquez sur le symbole 'ankh' de l'interface pour afficher les objectifs de votre mission, puis consultez vos chefs pour connaître votre progression."
        }
    }
    message_trade_on_the_water {
        id: 246,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Sur les rives du fleuve",

        }
        content {
            text: "Commerce maritime @LVous pouvez établir des voies commerciales maritimes à condition que la cité soit construite sur une rive. Pour cela, consultez la mappemonde. Pour utiliser une route maritime, votre cité doit disposer d'un dock. @L@LPêche sur le Nil @LLe Nil regorge de poissons, un mets très prisé par les Egyptiens. Pour être heureux et en bonne santé, les habitants doivent avoir une alimentation variée. Construisez des bateaux pour partir pêcher du poisson sur le Nil. @L@LConstruction de bateaux et de navires @LLa fabrique de bateaux assemble des navires de guerre et des bateaux de pêche. Construisez un quai pour chaque embarcation. Chaque fois que vous bâtissez un quai, la fabrique entame la construction d'un bateau. Les quais sont indispensables à la fabrication des bateaux.   @LUne fabrique de bateaux suffit à construire tous les navires dont votre cité a besoin. Vous pouvez néanmoins bâtir plusieurs fabriques pour remplacer rapidement les navires détruits. Pour assembler des bateaux de pêche, la fabrique n'utilise aucune matière première. Pour les navires de guerre et les transporteurs, vous devez régulièrement l'approvisionner en bois. @LLes navires de guerre, les bateaux de commerce ou de pêche sont larges et profonds pour naviguer sur les eaux du Nil et le long des côtes d'Egypte. Ils ne peuvent pas emprunter des voies d'eau resserrées telles que des canaux ou des rivières. Rien ne vous empêche de construire des fabriques de bateaux, des docks ou des quais à ces endroits, mais vous ne pourrez pas utiliser les bateaux. @LLorsque vous choisissez un emplacement pour construire un port, veillez à ce que les bateaux puissent facilement entrer dans le port et en sortir. Il est par exemple inutile de construire un quai sur un lac si les bateaux de pêche ne peuvent pas accéder aux rives du Nil, même si ce lac est relié au fleuve par un étroit canal."
        }
    }
    message_at_the_waters_edge {
        id: 247,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Sur les rives du fleuve",

        }
        content {
            text: "Commerce maritime  @LVous pouvez établir des voies commerciales maritimes à condition que la cité soit construite sur une rive. Pour cela, consultez la mappemonde. Pour utiliser une route maritime, votre cité doit disposer d'un dock. @L@LPêche sur le Nil @LLe Nil regorge de poissons, un met très prisé par les Egyptiens. Pour être heureux et en bonne santé, les habitants doivent avoir une alimentation variée. Construisez des bateaux pour partir pêcher du poisson sur le Nil. @L@LConstruction de bateaux et de navires @LLa fabrique de bateaux assemble des navires de guerre et des bateaux de pêche. Construisez un quai pour chaque embarcation. Chaque fois que vous bâtissez un quai, la fabrique entame la construction d'un bateau. Les quais sont indispensables à la fabrication des bateaux.   @LUne fabrique de bateaux suffit à construire tous les navires dont votre cité a besoin. Vous pouvez néanmoins bâtir plusieurs fabriques pour remplacer rapidement les navires détruits. Pour assembler des bateaux de pêche, la fabrique n'utilise aucune matière première. Pour les navires de guerre et les transporteurs, vous devez régulièrement l'approvisionner en bois. @LLes navires de guerre, les bateaux de commerce ou de pêche sont larges et profonds pour naviguer sur les eaux du Nil et le long des côtes d'Egypte. Ils ne peuvent pas emprunter des voies d'eau resserrées telles que des canaux ou des rivières. Rien ne vous empêche de construire des fabriques de bateaux, des docks ou des quais à ces endroits, mais vous ne pourrez pas utiliser les bateaux. @LLorsque vous choisissez un emplacement pour construire un port, veillez à ce que les bateaux puissent facilement entrer dans le port et en sortir. Il est par exemple inutile de construire un quai sur un lac si les bateaux de pêche ne peuvent pas accéder aux rives du Nil, même si ce lac est relié au fleuve par un étroit canal. @L@LFabrication de briques @LLa brique, utilisée dans certaines tombes, est le matériau de construction le moins coûteux. Pour fabriquer des briques, vous devez construire une briqueterie et l'approvisionner en argile et en paille."
        }
    }
    message_the_finer_things_tutorial {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Beautés égyptiennes",

        }
        content {
            text: "Ensembles de temples @LLe nombre de fidèles ne cesse de croître et les Egyptiens souhaitent la construction de monuments toujours plus imposants en l'honneur des dieux protecteurs. Les cités érigent parfois un ensemble de temples dédié à leur dieu protecteur afin que ce dernier veille sur les habitants. Vous pouvez également construire un oracle ou un autel en l'honneur d'autres divinités locales. Elles se montreront, elles aussi, clémentes à l'égard de votre cité.   @L@LArticles de luxe @LOutre les bijoux confectionnés par les artisans locaux, les Egyptiens apprécient également d'autres articles de luxe, uniquement disponibles à l'importation. Pour satisfaire les habitants de votre cité, veillez à ce qu'ils puissent acheter différents types d'articles de luxe.  @L@LCollecte de bois @G58 @LDans un pays aussi aride que l'Egypte, les ressources en bois sont rares et donc très précieuses. Les régions où poussent des forêts disposent d'une grande richesse. Pour collecter le bois, créez un chantier de bois afin que les ouvriers puissent aller couper le bois qui servira à la construction des navires de guerre, des transporteurs et des monuments."
        }
    }
    message_housing_and_roads {
        id: 249,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Logements et routes" }
        content { text: "@PLorsque vous construisez une cité, vous devez penser d'abord à bâtir des logements pour abriter les immigrants, et des routes pour leur permettre de circuler rapidement. @PLes immigrants affluent vers les zones constructibles que vous construisez. @G50 @L@LRoutes @L@PAppuyez sur le bouton gauche de la souris et faites glisser le curseur pour bâtir de longues portions de route. @G51 @PA chaque croisement, les passants doivent choisir une direction, ce qui peut allonger leur trajet et donc les ralentir. @G52 @PEvitez autant que possible les intersections lorsque vous construisez des routes afin que les promeneurs puissent circuler rapidement.  @PPour venir dans votre cité, les immigrants suivent la route du royaume. Les habitants des différentes zones constructibles doivent toujours avoir accès à cette route. Sinon, vous risquez de les isoler et de faire disparaître leurs logements. @L@LPour quitter un panneau de message (comme celui-ci), cliquez sur le bouton droit de la souris." }
    }
    message_basic_healthcare {
        id: 250
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Médecine de base" }
        content { text: "Des problèmes de santé sévissent dans votre ville en raison de la croissance de la population. Les habitants sont particulièrement touchés par la malaria. En outre, la peste risque de se développer si les soins médicaux ne sont pas adaptés.  @PSi la malaria frappe un foyer, ses occupants mourront tous, et la demeure ne sera pas occupée pendant un certain temps. @G64 @L@LMalaria @L@PLa malaria sévit particulièrement dans les zones marécageuses. Risques : la carte de la malaria indique les foyers susceptibles d'être affectés par cette maladie.   @PL'accès à une source d'eau potable ainsi que l'utilisation d'un insecticide fourni par une pharmacie locale permettent de réduire considérablement le risque de malaria au sein d'un foyer. Comme la plupart des établissements, les pharmacies fonctionnent si elles bénéficient d'un accès routier et de main-d'oeuvre. @G63 @L@LMaladies @L@PLes médecins prescrivent des médicaments aux foyers qu'ils soignent afin de réduire le risque de maladie. Une alimentation régulière est également essentielle pour empêcher toute maladie. Risques : la carte des maladies indique les foyers susceptibles d'être touchés par une maladie." }
    }
    message_requests_from_other_cities {
        id: 251
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Requêtes d'autres villes"
            pos [0, 20]
        }
        content {
            text: "L'une des villes voisines a besoin d'aide, et vous a demandé assistance. Pour rester en bons termes avec le reste du royaume, il vous est conseillé de répondre rapidement et favorablement à une telle demande. @G65  @PUne fois que l'article requis est en votre possession dans la quantité voulue, consultez le Chef politique pour effectuer une livraison dans la ville concernée. "
        }
    }
    message_fire_in_the_village {
        id: 252,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Incendie dans le village !" }
        content { text: "Un incendie s'est déclaré dans le village ! @L@LMessages @L@PLorsque vous entendez le carillon indiquant l'apparition de ce panneau, c'est que vous avez reçu un message. Pour lire un message, cliquez sur le bouton correspondant. Certains messages urgents (comme celui-ci) vous sont présentés avant d'être stockés avec les autres messages. Les messages moins importants, qui signalent généralement des événements ne requérant pas une attention immédiate, sont directement stockés dans votre messagerie sans être affichés. Alors, restez attentif au carillon. @G66  @L@LPour vous protéger d'éventuels incendies, vous pouvez maintenant construire une caserne de pompiers.  @PComme la plupart des bâtiments non résidentiels du village, la caserne de pompiers a besoin de main-d'oeuvre pour fonctionner. Une personne est alors envoyée par la caserne pour trouver des maisons habitées. Lorsqu'un foyer est détecté, la main-d'oeuvre est alors disponible. La caserne peut envoyer les capitaines des pompiers patrouiller dans le village.  @PLes capitaines des pompiers inspectent les bâtiments en quête d'éventuels incendies, réduisant ainsi les risques d'incendie. Les capitaines des pompiers peuvent exercer leurs fonctions dans tout bâtiment situé à proximité d'une route. @PS'il découvre un incendie, le capitaine l'éteint à l'aide de seaux d'eau, puis reprend sa patrouille normale. @G67 @L@PSi un bâtiment est détruit par les flammes, cliquez avec le bouton droit de la souris sur le tas de gravats pour savoir ce qui se trouvait à cet endroit avant l'incendie.  " }
    }
    message_tutorial_collapsed_building {
        id: 253,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Bâtiment détruit" }
        content { text: "Certaines structures imposantes de votre ville risquent de s'effondrer si elles ne sont pas correctement entretenues. Pour empêcher cela, construisez une étude d'ingénieurs. Comme la caserne de pompiers, cette structure envoie des hommes - dans ce cas des ingénieurs - pour parcourir les rues et réparer tout bâtiment endommagé. @G68 @L@P  Les cartes des 'risques' vous indiquent les bâtiments susceptibles de prendre feu ou de s'effondrer." }
    }
    message_tutorial_education {
        id: 254
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Dieux mécontents", pos [0, 15] }
        content {
            text: "Vos citoyens sont inquiets, car certaines divinités risquent d'être mécontentes. Certains ont eu des visions de calamités à venir. Vous devez satisfaire les dieux en leur construisant des temples ou en organisant des fêtes en leur honneur, sous peine de subir leur colère."
        }
    }
    message_tutorial_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Acheminement de l'eau",

        }
        content {
            text: "Bravo ! Vous avez réussi à fournir aux habitants de votre ville une source de nourriture fiable. Vous devez maintenant leur fournir une source d'eau potable, de préférence sans utiliser de puits.    @L@LPoints d'eau @LTout comme les puits, ces structures doivent être construites sur une terre contenant de l'eau en sous-sol, ce que vous indique la présence d'herbe verte. Ces points d'eau doivent également bénéficier d'une main-d'oeuvre résidant dans les environs. @G70   @LUne fois prêt à fonctionner, le point d'eau envoie des porteurs d'eau livrer des seaux d'eau potable à toutes les maisons situées dans les environs. "
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
            text: "Monuments"
        }
        content {
            text: "Maintenant que vous avez atteint ce stade de la démo, vous pouvez explorer d'autres aspects de Pharaon. N'oubliez pas de consulter vos nouveaux chefs pour obtenir davantage d'informations ; ils peuvent vous aider dans la gestion de votre ville en pleine croissance. @L@LMonuments @L@PVous pouvez maintenant commencer la création de votre mastaba ! Vous aurez besoin de briques, ainsi que de maçons et de paysans (fournis par les chantiers) pour accomplir cette tâche... 'monumentale'. @G75 @L@LAutres biens domestiques @L@PLes foyers égyptiens doivent être approvisionnés non seulement en poteries, mais aussi en bière et en toile. La bière est produite dans une brasserie à partir d'orge cultivé sur des exploitations locales. La toile est confectionnée dans un atelier de tissage à partir de lin, autre culture locale. Comme les aliments et les poteries, la bière et la toile sont distribuées aux foyers par les employés du bazar. @L@LForces de l'ordre @L@PUn magistrat envoyé par son palais de justice vous aide à réduire la criminalité dans votre ville. Il enregistre les plaintes et s'assure que tout le monde garde son sang-froid. @L@LSanté et hygiène @L@PToute ville nécessite la présence de quelques embaumeurs pour assurer une certaine hygiène, ainsi que pour fournir aux plus riches habitants des rites funéraires convenables. Dans la salle des embaumeurs, on utilise la toile confectionnée par un atelier de tissage et l'on propose des services d'embaumement à domicile dans les environs. En outre, les dentistes fournissent un service de qualité aux foyers dont ils ont la charge. @L@LEducation @L@PLes écoles et les bibliothèques ne peuvent pas fonctionner sans papyrus. Les cueilleurs de roseaux fournissent aux fabriques de papyrus les matières premières nécessaires. Les papyrus sont ensuite distribués directement aux établissements scolaires de la ville. @G69 @L@LNavires de guerre @L@PVous pouvez être amené à défendre les abords de votre ville à l'aide de navires de guerre robustes. Vous aurez dans un premier temps besoin d'un chantier de bois pour fournir du bois à la fabrique de bateaux. @G58 @L@LImpôts @L@PBien qu'il vous soit pour l'instant impossible d'acquérir un revenu supplémentaire grâce au commerce ou à l'exportation, vous pouvez néanmoins obtenir quelques deben des habitants de votre ville en collectant des impôts. Prévoyez un nombre suffisant de percepteurs pour couvrir la ville, notamment les riches habitations."
        }
    }
    message_tutorial_the_gods_of_egypt {
        id: 258
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Culte des dieux" }
        content {
            text: "Une ville égyptienne ne peut réellement s'épanouir sans lieux de culte convenables, qu'il s'agisse de temples ou de sanctuaires. Ces lieux doivent se trouver à proximité des habitations, et doivent être dédiés à l'une des cinq divinités suivantes :  @L@POsiris - dieu du Nil @PRê - dieu du royaume @PPtah - dieu des artisans @PSeth - dieu de la destruction @PBastet - déesse du foyer @L@PChaque ville a ses propres tendances religieuses. Dans chaque ville, un culte particulier est généralement voué à l'une de ces divinités - son 'dieu protecteur' - les autres dieux étant considérés comme de simples 'divinités locales' (ou totalement ignorés). La déesse protectrice de This est Bastet. @PUne divinité protectrice peut facilement se mettre en colère si elle considère qu'elle n'est pas suffisamment respectée. Même une divinité locale peut devenir hostile, si le nombre de temples et de sanctuaires qui lui sont dédiés est insuffisant pour la population de votre ville. @PLorsqu'un temple est accessible par route et bénéficie d'une main-d'oeuvre à proximité, il envoie un prêtre dans les environs, invitant les habitants à se rendre dans la demeure de son dieu. @G73  @L@LChef des temples @L@PConsultez votre Chef des temples pour déterminer le statut de chaque divinité dans une ville en particulier, et pour savoir si les dieux sont suffisamment apaisés. Des éclairs vous indiquent que la divinité est d'un tempérament hostile envers votre ville, tandis que des étoiles indiquent qu'elle est d'un tempérament favorable. Plus vous voyez d'éclairs ou d'étoiles, plus votre ville est susceptible de sentir la présence de la divinité (pour le meilleur ou pour le pire !)."
        }
    }
    message_tutorial_industry {
        id: 259
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Industrie" }
        content { text: "Maintenant que les habitants de votre ville sont alimentés en nourriture et en eau, vous pouvez améliorer leurs conditions de vie grâce à des biens plus modernes, tels que des poteries.  	 @L@LIndustrie et poterie @L@PConstruisez un puits d'argile à proximité d'une source d'eau, et installez une poterie dans les environs. Vérifiez qu'elle peut bénéficier de main-d'oeuvre, et vous verrez bientôt une charrette arriver pour livrer de l'argile à la poterie, qui pourra ainsi confectionner des poteries pour votre ville.  @PConstruisez un entrepôt pour stocker les produits finis ainsi que l'argile dont la poterie n'a pas besoin (un puits d'argile fournit généralement une quantité d'argile suffisante pour deux poteries).   @PLes employés du bazar récupèrent les poteries dans l'entrepôt et les distribuent de la même façon que la nourriture. @G74 @LLes industries telles que la poterie sont également une source d'emploi pour les habitants de votre ville. Le Chef de la main-d'oeuvre (désormais disponible) vous assiste dans l'attribution des tâches aux< ouvriers." }
    }
    message_tutorial_trade_with_other_cities {
        id: 260
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Commerce intercités" }
        content { text: "Maintenant que vous avez réussi à éduquer une partie de la population, vous pouvez générer un revenu supplémentaire en vendant le surplus de papyrus aux cités avoisinantes. Vous pourrez également importer des briques de Perwadjyt pour la construction du mastaba. Lorsque vous serez prêt, cliquez sur l'icône de mappemonde [graphic here] pour savoir quelles autres cités sont disponibles et commencer une activité commerciale." }
    }

    message_tutorial_flooded_clay_pit {
        id: 271
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Puits d'argile inondé" }
        content { text: "L'un de nos puits d'argile a subi une terrible inondation. Il a fallu le détruire pour éviter une autre catastrophe." }
    }
    
    message_kingdom_road_blocked {
        id: 279
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Urgent: Route Blockée !" }
        content { text: "Les gravats bloquent la route. Vous devez retirer les gravats !" }
    }
    
    message_wrath_of_ra {
        id: 280
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Colère de Rê" }
        video { text: "@23" }
        content { text: "Pour vous punir de votre arrogance, Rê a considérablement assombri votre réputation au sein du royaume. Comme vous avez négligé cette divinité, d'autres Egyptiens vont vous déprécier." }
    }

    message_wrath_of_seth {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Colère de Seth" }
        video { text: "@21" }
        content { text: "Votre manque de respect envers Seth l'incite à détruire tous vos navires !" }
    }

    message_wrath_of_seth_2 {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Wrath of Seth 2" }
        video { text: "@21" }
        content { text: "Votre manque de respect envers Seth l'incite à détruire tous vos navires !" }
    }

    message_the_world_map {
        id: 282
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Carte du royaume",

        }
        content {
            text: "La carte du royaume affiche les cités environnantes. Sa fonction la plus importante consiste probablement à identifier des partenaires pour le @47commerce. @PCliquez sur un nom de cité pour prendre connaissance du type de commerce proposé. Vous trouverez en dessous du nom de la cité les produits qu'elle achète et revend, ainsi que le coût d'ouverture d'une route commerciale. Cliquez sur le bouton 'Ouvrir une route de commerce' pour activer les relations. @PVous recevrez fréquemment des demandes d'approvisionnement en provenance d'autres cités ou vous apprendrez que des combats ont lieu ailleurs. La carte du royaume est un outil de référence pratique permettant de situer les autres cités. Si un envahisseur attaque une cité près de la vôtre, mieux vaut préparer votre défense. @PLisez les entrées @47commerce, @52guerre&et&paix et @24Chef&du&commerce pour plus de détails sur l'utilisation de la carte du royaume."
        }
    }

    message_tutorial_monuments {
        id: 283
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monuments" }
        content {
            text: "Avec un chargement de briques, vous pouvez à présent travailler à la construction du mastaba sacré.  La plupart des monuments réclament des ouvriers qualifiés et non-qualifiés.   @L@LGuildes de construction.  @LLes Guildes de construction fournissent la main-d'oeuvre qualifiée nécessaire à la construction des monuments. Le mastaba est entièrement constitué de briques, et seule la Guilde des maçons est indispensable à sa construction. Vous pouvez utiliser autant de Guildes de maçons qu'il vous plaira, à condition que votre économie puisse subvenir à leurs besoins. Assurez-vous toutefois que suffisamment de briques sont livrées sur le chantier afin de maintenir occupés tous vos maçons.  @PLa Guilde des maçons répartira la main d'oeuvre sur le chantier de construction. Chaque poseur attendra alors de recevoir un chargement livré par des paysans non qualifiés.  @L@LLes paysans @LUne fois vos maçons sur le chantier, des groupes de paysans commenceront à leur livrer des briques. Ces même paysans retourneront à leur champ dès que possible. Vous remarquerez donc que le travail sur le chantier ralentit lorsque le Nil décroît.  Vous pouvez construire des chantiers supplémentaires. Ainsi tous les paysans non nécessaires à l'entretien des champs pourront travailler sur les monuments tout au long de l'année. @G75 @L@LCommencez par cliquer sur l'icône Structures Religieuses, puis cherchez un lieu qui puisse accueillir ce grand bâtiment."
        }
    }
    
    message_the_finer_things {
        id: 284
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Beautés égyptiennes"
        }
        content {
            text: "Ensembles de temples @LLe nombre de fidèles ne cesse de croître et les Egyptiens souhaitent la construction de monuments toujours plus imposants en l'honneur des dieux protecteurs. Les cités érigent parfois un ensemble de temples dédié à leur dieu protecteur afin que ce dernier veille sur les habitants. Vous pouvez également construire un oracle ou un autel en l'honneur d'autres divinités locales. Elles se montreront, elles aussi, clémentes à l'égard de votre cité.   @L@LBijoux @LGrâce aux pierres précieuses collectées, les orfèvres confectionnent de beaux bijoux destinés aux riches habitants de votre cité.  @L@LArticles de luxe @LOutre les bijoux confectionnés par les artisans locaux, les Egyptiens apprécient également d'autres articles de luxe, uniquement disponibles à l'importation. Pour satisfaire les habitants de votre cité, veillez à ce qu'ils puissent acheter différents types d'articles de luxe.  @L@LCarrières de pierre @LPour obtenir des blocs de pierre, un matériau de construction très recherché, creusez une carrière près d'une zone rocheuse. Les ouvriers de cette carrière transportent, un à un, les blocs de pierre jusqu'à l'entrepôt. Pensez à installer une étude d'architecte près de la carrière pour éviter tout risque d'effondrement !"
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
            text: "Fermes des prairies @LCertaines terres éloignées de la plaine inondable du Nil sont assez fertiles pour permettre l'installation de fermes agricoles. Vous pouvez identifier ces terres grâce aux longues plantes jaunes qui y poussent. Certaines de ces fermes peuvent ainsi produire deux récoltes par an, bien que leur rendement soit légèrement inférieur à celui des fermes situées sur la plaine inondable. @G59   @L@LIrrigation @LLes systèmes d'irrigation permettent d'augmenter la fertilité des terres. Les rigoles d'irrigation peuvent être reliées directement au Nil, mais vous devrez construire un chadouf pour amener l'eau sur les terres arides.   @L@LChadoufs @LVous pouvez construire des chadoufs au bord de la plaine inondable ou le long d'une côte pour puiser l'eau de la rivière et la verser sur les terres arides. Reliez une rigole d'irrigation à la partie arrière du chadouf pour amener l'eau vers les fermes.  @L@LTailleurs de pierre et menuisiers @LDeux guildes sont nécessaires à la construction d'une pyramide à degrés : la guilde des tailleurs de pierre et celle des menuisiers. Les tailleurs de pierre attendent que les paysans apportent les blocs de pierre sur le site de construction. Pour accéder au sommet du monument, ces paysans empruntent des rampes en bois. Lorsqu'un niveau de la pyramide et terminé, les menuisiers apportent le bois sur le site et installent une rampe pour les paysans. @L@LEmbaumement des morts @LLes embaumeurs veillent à la bonne hygiène de la cité en offrant aux habitants les plus riches de grandes cérémonies funéraires. Avec la toile fabriquée par les ateliers de tissage, la salle des embaumeurs offre ses services d'embaumement aux habitants des quartiers environnants."
        }
    }

    message_troops_return_failed {
        id: 287
        type: 2
        
        size [30, 20]
        title { text: "Retour de la compagnie" }
        content { text: "Protégés par la nuit, les membres rescapés de votre malheureuse compagnie regagnent les forts confortables de la cité, bien décidés à ne plus jamais subir d'humiliation au combat." }
    }
    message_troops_return_victorious {
        id: 288
        type: 2
        
        size [30, 20]
        title {
            text: "Retour des héros !"
        }
        content {
            text: "Vos victorieux soldats sont de retour de la guerre. Ils sont un peu moins nombreux qu'au départ, mais leurs camarades se sont sacrifiés pour le bien de l'Egypte ! "
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
        title { text: "Osiris est mécontent" }
        content { text: "A moins que vous ne réussissiez à l'apaiser, le dieu de l'inondation du Nil punira cette cité pour son manque de dévotion et, l'année prochaine, l'inondation détruira toutes les exploitations de la région !" }
    }
    message_ra_is_upset_2 {
        id: 291
        type: 2
        
        size [30, 20]
        title { text: "Rê est mécontent" }
        video { text: "@23" }
        content { text: "Irrité par votre manque de respect envers sa personne, Rê ternit votre propre réputation au sein du royaume." }
    }
    message_ptah_is_upset {
        id: 292
        type: 2
        
        size [30, 20]
        title { text: "Ptah est mécontent" }
        video { text: "@22" }
        content { text: "Consterné par votre manque d'intérêt envers sa personne, Ptah a détruit l'un de vos entrepôts." }
    }
    message_seth_is_upset {
        id: 293
        type: 2
        
        size [30, 20]
        title { text: "Seth est mécontent" }
        video { text: "@21" }
        content { text: "Seth a anéanti votre meilleure compagnie et son fort." }
    }
    message_bast_is_upset {
        id: 294
        type: 2
        
        size [30, 20]
        title { text: "Bastet est mécontente" }
        video { text: "@20" }
        content { text: "La déesse Bastet est fort mécontente du manque de respect de cette cité envers elle. Elle a donc projeté un sombre nuage de calamités sur ses habitants." }
    }
    message_blessing_from_osiris {
        id: 295
        type: 2
        
        size [30, 20]
        title { text: "Bénédiction d'Osiris" }
        video { text: "@24" }
        content { text: "Osiris, dieu de l'inondation du Nil, désire bénir cette cité pour la remercier de sa sincère dévotion. La prochaine récolte sera deux fois supérieure à la normale pour toutes les exploitations de la plaine inondable !" }
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
        title { text: "Bénédiction de Rê" }
        video { text: "@23" }
        content { text: "Rê récompense ceux qui lui sont fidèles ! Pendant les 12 mois à venir, votre cité pourra vendre ses produits d'exportation pour 50 % de plus que leur valeur normale." }
    }
    message_blessing_trade_from_ptah {
        id: 297
        type: 2
        
        size [30, 20]
        title { text: "Bénédiction de Ptah" }
        video { text: "@22" }
        content { text: "Ptah choisit un entrepôt particulièrement performant et augmente la quantité de pierres précieuses, argile, poteries, lin et bijoux qu'il contient déjà." }
    }
    message_blessing_trade_from_seth {
        id: 298
        type: 2
        
        size [30, 20]
        title { text: "Bénédiction de Seth" }
        video { text: "@21" }
        content { text: "Seth apprécie votre humilité et votre obéissance. En guise de récompense, il terrassera les prochains ennemis qui oseront attaquer votre cité." }
    }
    message_blessing_from_bast {
        id: 299,
        type: 2,
        
        size [30, 20]
        title { text: "Bénédiction de Bastet" }
        video { text: "@20" }
        content { text: " En raison de la fidélité et de la dévotion de cette cité envers sa personne, Bastet a comblé ses habitations et ses bazars d'une abondance de nourriture et d'autres marchandises !" }
    }
    message_the_gods_are_wrathful {
        id: 300
        type: 2
        
        size [30, 20]
        title { text: "Les dieux sont mécontents" }
        content { text: "Au moins une divinité est en colère contre cette cité. Votre peuple exige la construction d'autres temples... et l'organisation d'une fête." }
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
            text: "Esprit de Seth",
        }
        video {
            text: "@21"
        }
        content {
            text: "Seth se souvient qu'il a promis de vous protéger et il se fera un plaisir de terrasser tous ceux qui auront l'inconscience de s'attaquer à votre cité."
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
        title { text: "Volonté satisfaite" }
        content { text: "Votre chef politique annonce que cette cité dispose désormais d'une quantité suffisante de debens pour répondre aux récentes exigences." }
    }
    message_tutorial_finances {
        id: 310,
        type: 2,
        message_type: 4
        size [40, 30]
        title { text: "Finances" }
        content {
            text: "Impôts @LUne grande cité a besoin de générer un revenu supplémentaire par rapport à son investissement initial. Les impôts sont un moyen d'y parvenir. La collecte des impôts nécessite un palais et des percepteurs. Assurez-vous de prévoir un nombre suffisant de percepteurs pour toute la ville, en particulier pour les quartiers riches. Plus la qualité de vie est grande dans un foyer, plus ses occupants paient d'impôts. @L@LVotre salaire personnel @LSi vous construisez une demeure luxueuse pour votre propre usage, vous pouvez générer un salaire personnel à partir des caisses de la cité. Les fonds personnels sont conservés par votre famille, en cas de besoin, comme lors des missions à venir. Attention, toutefois, car, si vous percevez un salaire correspondant à une position plus élevée que la vôtre, celà risque d'avoir des effets négatifs sur votre réputation au sein du royaume."
        }
    }
    message_mission_defeat {
        id: 311,
        type: 2,
        
        size [30, 20]
        title { text: "Défaite !" }
        content { text: "Ô, jour funeste ! Votre fin n'aurait pu être pire. Vous avez failli à votre peuple, à vos ancêtres et à vos descendants. Maintenant, l'Egypte attend qu'un autre champion prenne votre place..." }
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
            text: "Volonté satisfaite",
        }
        content {
            text: " Votre chef politique annonce que les entrepôts de votre cité disposent désormais d'une quantité suffisante de biens pour répondre aux récentes exigences."
        }
    }
    message_kingdom_road_obstructed {
        id: 315,
        type: 2,
        
        size [30, 20]
        title {
            text: "Urgent : route bloquée",
        }
        content {
            text: "Les architectes ont dû détruire des constructions récentes pour rétablir l'accès à la @57route&du&royaume. Vous devez immédiatement enlever les gravats."
        }
    }
    message_no_working_dock {
        id: 316,
        type: 2,
        
        size [30, 20]
        title { text: "Aucun dock opérationnel" }
        content { text: "Bien que vous ayez demandé à votre chef du commerce d'établir des relations commerciales avec un marchand de mer, ce dernier ne peut pas accoster sur les rives de notre cité ! Vous devez construire un dock et prévoir une main-d'oeuvre pour y travailler. Une fois que votre cité disposera d'un dock opérationnel, les navires pourront accoster et les échanges commerciaux pourront commencer." }
    }
    message_fishing_boats_cant_navigate {
        id: 317,
        type: 2,
        
        size [30, 20]
        title { text: "Les navires de pêche ne peuvent pas circuler" }
        content { text: "Nos pêcheurs rapportent qu'un pont bloque le passage ! Les navires ne peuvent pas passer sous les ponts. Supprimez ce pont afin que les navires de pêche puissent approvisionner votre cité en poisson frais." }
    }
    message_health {
        id: 318,
        type: 3,
        
        size [30, 20]
        title {
            text: "Hygiène",
        }
        content {
            text: "Les gens aiment être en bonne santé. S'ils se nourrissent correctement et qu'un médecin leur rend régulièrement visite, ils ne doivent rencontrer aucun problème de santé. Sinon, les risques de maladie s'accentuent. @PLes hôpitaux sont bien utiles pour guérir les habitants qui tombent malades. S'ils ne trouvent pas de place dans les hôpitaux, ils meurent. @PEn conséquence : les cliniques servent à la prévention des malades et les hôpitaux à leur guérison. @L@LParfois, une épidémie de peste se déclare. Il arrive que Bastet frappe par cette maladie une cité qui a provoqué son courroux. Les hôpitaux sont la seule solution en de tels cas. Votre chef de l'hygiène peut vous indiquer si vous bénéficiez ou non d'une couverture hospitalière suffisante."
        }
    }
    message_messages_await_you {
        id: 319,
        type: 3,
        
        size [30, 20]
        title {
            text: "Des messages vous attendent",
        }
        content {
            text: "Lorsque vous entendez une fanfare, cela signifie que votre scribe a reçu un nouveau message pour vous et qu'il l'a enregistré. @L@LCertains messages, tels que celui-ci, sont automatiquement ouverts pour vous. Ce sont des messages que votre scribe juge très urgents. Vous pourrez les consulter plus tard, si vous le souhaitez, en cliquant sur votre bouton de message. @PLes messages importants mais pas urgents sont signalés par une grosse fanfare, mais n'apparaissent pas automatiquement. La plupart des messages sont des messages normaux, signalés par une fanfare normale, et que vous pouvez consulter lorsque cela vous convient. @L@LTous les messages sont enregistrés par votre scribe afin que vous puissiez les consulter à tout moment. Vous pouvez également les supprimer si vous le souhaitez. Pour plus d'informations, ouvrez le menu Aide dans la barre de menus et cliquez sur Messages de vos scribes à la fin de la table des matières."
        }
    }
    message_local_uprising {
        id: 320,
        message_type: 7
        
        size [30, 20]
        urgent: 1
        title { text: "Rébellion locale" }
        content { text: "Inspirés par Seth, certains citoyens ont décidé de manifester leur ressentiment à votre encontre !!" }
    }
    message_small_blessing_from_osiris {
        id: 321
        type: 2
        
        size [30, 20]
        title { text: "Une petite faveur d'Osiris" }
        video { text: "@24" }
        content { text: "La ferveur du culte d'Osiris, dieu du Nil, dans votre cité a été remarquée. Continuez à honorer Osiris de cette façon et l'inondation de l'an prochain sera parfaite, déposant du limon fertile en abondance dans la plaine." }
    }
    message_minor_blessing_from_ra {
        id: 322
        type: 2
        
        size [30, 20]
        title { text: "Une petite faveur de Rê" }
        video { text: "@23"}
        content { text: "Encouragé par le respect que vous lui témoigné, Rê a quelque peu amélioré votre réputation au sein du royaume." }
    }
    message_minor_blessing_from_ptah {
        id: 323
        type: 2
        
        size [30, 20]
        title { text: "Une petite faveur de Ptah" }
        video { text: "@22" }
        content { text: "Ptah est touché par votre sollicitude et assure que les fabriques de bateaux, les ateliers de tissage et les orfèvreries de votre ville disposent de toutes les matières premières voulues." }
    }
    message_minor_blessing_from_seth {
        id: 324
        type: 2
        
        title { text: "Une petite faveur de Seth" }
        video { text: "@21" }
        content { text: "Pour vous remercier de votre obéissance, Seth protégera tous vos soldats lors d'une bataille lointaine." }
    }
    message_small_blessing_from_bast {
        id: 325
        type: 2
        
        size [30, 20]
        title { text: "Une petite faveur de Bastet" }
        video { text: "@20" }
        content { text: "Bastet est satisfaite du culte de votre cité. Elle a organisé une fête pour que toutes les divinités puissent se rendre compte de votre piété." }
    }
    message_disease_strikes {
        id: 326,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Epidémie",
        }
        content {
            text: "Une épidémie s'est répandue dans un foyer qui ne bénéficie pas d'un bon accès aux soins médicaux. Les gens meurent sans que vous ne puissiez rien y faire. Vous devez améliorer les conditions d'hygiène dans les quartiers insalubres afin d'éviter une nouvelle épidémie."
        }
    }
    message_a_plague {
        id: 327,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Epidémie de peste",
        }
        content {
            text: "La peste envahit la cité ! C'est ce que nous craignions, compte tenu des conditions générales d'@53hygiène dans la cité. Il reste à espérer que nos pharmacies soient à la hauteur."
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
            text: "Certains foyers sont touchés par la malaria. De meilleures conditions d'hygiène éviteraient de gaspiller tant de vies humaines !"
        }
    }
    message_blessing_reputation_from_ra {
        id: 329,
        type: 2,
        
        size [30, 20]
        title { text: "Bénédiction de Rê" }
        video { text: "@23" }
        content {
            text: "Vous avez honoré Rê, et votre réputation s'est considérablement améliorée au sein du royaume !"
        }
    }
    message_minor_blessing_trading_from_ra {
        id: 331,
        type: 2,
        
        size [30, 20]
        title { text: "Une petite faveur de Rê" }
        video { text: "@23" }
        content { text: "Pour vous récompenser de votre dévotion, Rê incite vos partenaires commerciaux à acheter vos produits en plus grandes quantités." }
    }
    message_wrath_of_ra_2 {
        id: 332,
        type: 2,
        
        size [30, 20]
        title { text: "Colère de Rê" }
        video { text: "@23" }
        content { text: "Vous avez provoqué la colère de Rê ! En conséquence, ce dieu a fait baisser la réputation des produits de votre cité et vos partenaires commerciaux en achèteront de moins en moins." }
    }
    message_wrath_of_ra_3 {
        id: 333,
        type: 2,
        
        size [30, 20]
        title { text: "Colère de Rê" }
        video { text: "@23" }
        content { text: "Comme vous avez négligé Rê, vos partenaires commerciaux vont vous négliger à leur tour." }
    }
    message_ra_is_upset {
        id: 334,
        type: 2,
        
        size [30, 20]
        image { id: 224, pos [15, 15] }
        title { text: "Rê est mécontent" }
        video { text: "@23" }
        content { text: "Comme vous avez négligé Rê, vos partenaires commerciaux vont à leur tour négliger vos marchandises. Ils ont décidé de réduire leur activité commerciale avec vous." }
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
            text: "Wrath of RA",
        }
        content {
            text: "placeholder - report this to Ken if it appears"
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
        title { text: "Osiris vous bénit" }
        video { text: "@24" }
        content { text: "Osiris récompense ceux qui le vénèrent. La prochaine inondation sera bien meilleure que prévue." }
    }
    message_wrath_of_osiris_4 {
        id: 341,
        type: 2,
        
        size [30, 20]
        title { text: "Colère d'Osiris" }
        video { text: "@24" }
        content { text: " Osiris vous rappelle que vous lui devez du respect. La prochaine inondation sera plus faible que prévue." }
    }
    message_mediocre_inundation_seers {
        id: 342,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Les prêtres prédisent une faible inondation cette année." }
    }
    message_poor_inundation_seers {
        id: 343,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Les prêtres prédisent une faible inondation cette année." }
    }
    message_no_inundation {
        id: 344,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "De terribles nouvelles ! Les prêtres craignent qu'il n'y ait pas d'inondation cette année !" }
    }
    message_poor_inundation {   
        id: 345,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Les prêtres prédisent une faible inondation cette année. Il faut qu'Osiris soit satisfait pour que cela ne se reproduise pas l'année prochaine." }
    }
    message_mediocre_inundation {
        id: 346,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Malheureusement, il semble que l'inondation s'annonce médiocre cette année. Si la cité porte quelque attention à Osiris, on peut espérer que cela ne se reproduise pas l'année prochaine." }
    }
    message_good_inundation {
        id: 347,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Les prêtres d'Osiris prédisent une bonne inondation cette année." }
    }
    message_excellent_inundation {
        id: 348,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Les prêtres débordent de joie, car l'inondation s'annonce excellente cette année !" }
    }
    message_perfect_inundation {
        id: 349,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Prédiction par nilomètre" }
        content { text: "Cette cité est bénie. Nos prêtres prédisent une parfaite inondation cette année ! En honorant Osiris, cette cité devrait connaître la même bénédiction l'année prochaine !" }
    }
    message_temple_complex_to_osiris {
        id: 350,
        
        size [30, 20]
        title {
            text: "Ensemble de temples dédié à Osiris",
        }
        subtitle {
            text: "Religion",
        }
        content {
            text: "Lorsque vous construisez un ensemble de temples dédié à Osiris, le dieu est enclin à favoriser des crues plus propices chaque année. A côté de l'ensemble de temples d'Osiris, vous pouvez construire les édifices suivants : @L@LAutel de Sebek, dieu de la fertilité. @LSebek donne aux prêtres d'Osiris le pouvoir de faire durer les réserves de nourriture de la cité. Lorsque ces prêtres arpentent les rues de la cité, les habitants se contentent de peu de nourriture. @L@LOracle de Min, dieu du renouveau. @LMin récompense votre cité en accélérant la repousse des arbres et des plantes, en augmentant le gibier de chasse et en offrant aux habitants des rivières poissonneuses. @L@LLe peuple adore vivre à proximité d'un ensemble de temples. Pour plus de détails concernant la religion, cliquez @51ici.  @L@LCliquez @376ici pour en savoir plus sur Osiris, Sebek et Min dans l'Egypte ancienne."
        }
    }
    message_temple_complex_to_ra {
        id: 351,
        
        size [30, 20]
        title {
            text: "Ensemble de temples dédié à Rê",
        }
        content {
            text: "Si vous honorez le dieu Rê en construisant un ensemble de temples, il vous récompensera en affirmant votre position dans le royaume d'Egypte. Vous aurez ainsi un meilleur niveau du royaume et, si votre cité est endettée, il vous aidera à rembourser en vous accordant un taux d'intérêt inférieur. Construisez un autel et un oracle près de l'ensemble de temples afin que Rê veille sur les finances de votre cité : @L@LAutel de Maât, déesse de la justice. @LLa déesse Maât donne aux prêtres de Rê le pouvoir d'apporter la sécurité à la cité. Lorsqu'ils passent devant les logements, les prêtres de Rê dissuadent chacun des résidents de commettre des vols. La présence de cet autel permet de réduire la criminalité de la cité. @L@LOracle d'Horus, dieu des pharaons. @LCet oracle permet d'augmenter la dévotion des habitants envers leur pharaon et le royaume. Ils consentiront alors à travailler en échange d'un salaire inférieur. @L@LLe peuple adore vivre à proximité d'un ensemble de temples. Pour plus de détails concernant la religion, cliquez @51ici.  @L@LCliquez @377ici pour en savoir plus sur Rê, Maât et Horus dans l'Egypte ancienne."
        }
    }
    message_temple_complex_to_ptah {
        id: 352,
        
        size [30, 20]
        title {
            text: "Ensemble de temples dédié à Ptah",
        }
        content {
            text: "Si vous dédiez un ensemble de temples à Ptah, celui-ci augmentera la productivité des différentes industries de la cité : mines d'or, de cuivre, de pierres précieuses, puits d'argile, fabriques de bateaux, orfèvreries et ateliers de tissage. Ajoutez un autel et un oracle afin que Ptah augmente la productivité des autres industries et les aptitudes pédagogiques des éducateurs : @L@LAutel d'Amon, dieu du soleil. @LHonorez-le afin qu'il augmente la productivité des carrières, des chantiers de bois et des briqueteries. @L@LOracle de Thot, dieu de la sagesse et du savoir. @LThot permettra à une majorité de personnes d'accéder au savoir. Construisez un oracle de Thot afin que les bibliothécaires et les professeurs utilisent moins de papyrus au cours de leur travail. @L@LLe peuple adore vivre à proximité d'un ensemble de temples. Pour plus de détails concernant la religion, cliquez @51ici.  @L@LCliquez @378ici pour en savoir plus sur Ptah, Amon et Thoth dans l'Egypte ancienne."
        }        
    }
    message_temple_complex_to_seth {
        id: 353,
        
        size [30, 20]
        title { text: "Ensemble de temples dédié à Seth" }
        content { text: "Si votre cité entreprend la construction d'un ensemble de temples en l'honneur de Seth, ce dernier donnera à vos soldats du courage au combat, de l'expérience et les protégera pendant la bataille. Vous pouvez également ajouter les édifices suivants :  @L@LAutel d'Anubis, dieu de la mort. @LAnubis ouvre les portes de la vie éternelle à vos concitoyens. Grâce à sa bénédiction, les embaumeurs utilisent moins de toile lors de la momification des défunts.  @L@LOracle de Sekhmet, déesse de la guerre. @LSekhmet donne aux prêtres de Seth le pouvoir de réduire la criminalité dans les maisons qu'ils visitent et d'appréhender les criminels qui rôdent dans la cité.  @L@LLe peuple adore vivre à proximité d'un ensemble de temples. Pour plus de détails concernant la religion, cliquez @51ici.  @L@LCliquez @379ici pour en savoir plus sur Seth, Anubis et Sekhmet dans l'Egypte ancienne." }
    }
    message_temple_complex_to_bast {
        id: 354,
        
        size [30, 20]
        title { text: "Ensemble de temples dédié à Bastet" }
        content { text: "Construisez un temple en l'honneur de Bastet afin qu'elle apporte le bonheur à la cité. Bastet permet aux habitants de vivre heureux en se contentant de peu. Grâce à sa bénédiction, vos concitoyens consommeront moins de nourriture et les amuseurs, éducateurs et médecins pourront exercer leur profession plus longtemps. Les déesses associées à Bastet apportent également un plus grand bien-être aux habitants de la cité : @L@LAutel d'Isis, déesse de la guérison. @LIsis transmet aux prêtresses de Bastet ses pouvoirs de guérison afin de vider les rues de la cité des lépreux et de purifier les maisons contaminées. Isis veille également sur la santé des habitants de votre cité. @L@LOracle d'Hathor, déesse de la joie, de l'amour et des fêtes. @LHathor, flattée par l'oracle que vous avez bâti en son honneur, rendra vos concitoyens heureux et favorisera l'@39opinion des citoyens sur la cité. @L@LLe peuple adore vivre à proximité d'un ensemble de temples. Pour plus de détails concernant la religion, cliquez @51ici.  @L@LCliquez @380ici pour en savoir plus sur Bastet, Isis et Hathor dans l'Egypte ancienne." }
    }
    message_building_firehouse {
        id: 355,
        
        size [30, 20]
        title {
            text: "Caserne de pompiers",
        }
        content {
            text: "Certains bâtiments de votre cité sont particulièrement exposés aux incendies. C'est le cas des immeubles bon marché et des bâtiments industriels tels que les ateliers de poterie. Si vous n'intervenez pas, le feu risque de se propager à travers toute la cité et de détruire des quartiers entiers. Par mesure de précaution, construisez des casernes de pompiers près des bâtiments que les flammes pourraient réduire en fumée. Les capitaines des pompiers qui sortent des casernes de pompiers patrouillent dans la cité (cliquez @42ici pour en savoir plus sur les piétons) limitant les risques d'incendie pour les bâtiments qu'ils visitent. @PLorsqu'un incendie éclate, les capitaines des pompiers se précipitent pour l'éteindre. Si les pompiers doivent parcourir une longue distance pour arriver sur les lieux du sinistre, vous augmentez les risques de voir les flammes se propager aux autres habitations. @G67 @PLa @18carte&des&incendies peut vous être d'une grande aide pour la prévention de tels risques. La carte permet de voir l'action des pompiers, mais surtout elle permet de définir les bâtiments pouvant être touchés par un incendie. Utilisez ces informations pour planifier l'emplacement de votre caserne de pompiers. @PPour fonctionner, les casernes de pompiers doivent disposer d'un accès à une route et à la main-d'oeuvre. Les résidents sont peu enclins à vivre à proximité d'une caserne."
        }
    }
    message_building_warship_wharf {
        id: 356,
        
        size [30, 20]
        title {
            text: "Quai de navires de guerre",
        }
        content {
            text: "Les quais des navires de guerre abritent uniquement des navires de guerre. La première chose que fait un quai de navires de guerre lorsqu'il est en activité est de commander un navire de guerre à la @82fabrique&de&bateaux.  @PLes quais de navires de guerre ont besoin d'un accès à la route et à la main-d'oeuvre. Ils doivent être placés sur un tronçon rectiligne de la côte et les navires doivent pouvoir l'atteindre facilement. Les citoyens ne sont pas vraiment désireux de vivre près d'un quai de navires de guerre. En effet, certains marins ont une bien mauvaise réputation. @PLorsqu'un navire de guerre n'est pas engagé dans un combat, son équipage préfère rester à quai. En rentrant au fort, vos soldats peuvent se reposer en attendant le prochain combat. @PConsultez la rubrique @365Navire&de&guerre pour en savoir plus sur les manoeuvres des navires lors d'un combat. @L@LL'Egypte ancienne a toujours été marquée par une forte tradition militaire. Cliquez @184ici pour en savoir plus."
        }
    }
    message_building_transport_wharf {
        id: 357,
        
        size [30, 20]
        title {
            text: "Quai de transporteurs",
        }
        content {
            text: "Les quais de transporteurs permettent aux transporteurs de s'amarrer. Lorsque vous construisez un nouveau quai de transporteurs, celui-ci commande un transporteur à une @82fabrique&de&bateaux.  @PLes quais de transporteurs ont besoin d'un accès à la route et à la main-d'oeuvre. Ils doivent être construits sur une rive droite de la côte et être facilement accessibles aux navires. Il est préférable de ne pas placer de terrains constructibles à proximité immédiate des quais de transporteurs.  @PConsultez la rubrique @367Transporteur pour en savoir plus sur les manoeuvres des navires lors d'un combat. @L@LL'Egypte ancienne a toujours été marquée par une forte tradition militaire. Cliquez @181ici pour en savoir plus."
        }
    }
    message_building_roadblock {
        id: 358,
        
        size [30, 20]
        title {
            text: "Barrage routier",
        }
        content {
            text: "Ces barrages vous permettent de contrôler les déplacements des @42promeneurs dans la cité. Lorsque ces individus arrivent à la hauteur d'un barrage, ils rebroussent chemin. Les barrages routiers ne concernent pas les passants. @PPlacez un barrage routier aux endroits auxquels les promeneurs ne doivent pas accéder, par exemple, une route menant à des zones industrielles. Evitez cependant d'isoler complètement des endroits de la cité. Le barrage routier qui empêche un marchand du bazar d'accéder à une zone industrielle, interdit aussi l'accès aux architectes, pompiers et agents de police. Ce barrage empêche également les recruteurs des zones industrielles d'accéder aux quartiers résidentiels pour y embaucher de la main-d'oeuvre. @G62 @PLorsque vous construisez un barrage routier à proximité d'un bâtiment, attendez quelques instants pour vous assurer que les citoyens qui y travaillent quittent le bâtiment du bon côté du barrage. En effet, il se peut que les employés ne comprennent pas vos intentions et qu'ils prennent la mauvaise direction. Ceci peut s'avérer particulièrement gênant pour les bâtiments qui recherchent de la main-d'oeuvre car ses employés ne savent pas que le barrage routier empêche les piétons d'y accéder. Dans ce cas, la seule solution est de reconstruire le barrage un espace plus loin. @PLes barrages routiers n'ont pas besoin de main-d'oeuvre pour fonctionner ; ils doivent obligatoirement être placés sur une route. Ils n'ont aucun impact sur l'attrait des quartiers environnants."
        }
    }
    message_building_hunting_lodge {
        id: 359,
        
        size [30, 20]
        title {
            text: "Pavillon de chasse",
        }
        content {
            text: "Construisez un pavillon de chasse à partir duquel les chasseurs pourront pister le gibier. Les autruches, le gibier à plumes et les antilopes sont des proies rêvées pour les chasseurs. @PLes pavillons de chasse peuvent être construits n'importe où, mais il est préférable de les placer à proximité des terrains riches en gibier, c'est-à-dire près des zones de reproduction. Pour fonctionner, les pavillons de chasse nécessitent un accès à la route et de la main-d'oeuvre. Lorsque le pavillon de chasse sera opérationnel, vous verrez les chasseurs s'y entraîner. @PUne fois entraînés, les chasseurs quittent le pavillon à la recherche de gibier. Les chasseurs ramènent leurs proies au pavillon de chasse qui les prépare pour être consommées. Dès qu'une charrette de gibier est prête, les employés la transportent jusqu'à un @3grenier ou un @4entrepôt (s'il est autorisé à stocker de la viande). @G60 @PLe gibier joue un rôle important dans l'alimentation des citoyens de la cité. Il leur apporte la diversité qu'ils recherchent. Toutefois, le gibier ne peut suffire à lui seul à satisfaire les besoins alimentaires de la cité. La faune étant peu abondante, la chasse ne permet pas de nourrir une cité tout entière.  Pour plus de détails concernant les ressources alimentaires de la cité, voir la rubrique @45Agriculture&et&nourriture. @POutre la @89paille, le gibier sert de nourriture aux animaux du @479zoo. @PLes pavillons de chasse ont un effet négatif sur l'@56attrait des quartiers environnants. @L@LLe gibier permettait aux Egyptiens anciens de diversifier leur alimentation. La chasse était un sport très apprécié par l'élite. Cliquez @383ici pour en savoir plus."
        }
    }
    message_building_cattle_ranch {
        id: 360,
        
        size [30, 20]
        title {
            text: "Ferme d'élevage",
        }
        content {
            text: "Construisez des fermes d'élevage pour fournir de la viande aux habitants de la cité. @PLes fermes d'élevage doivent être adjacentes à une route et nécessitent de la main-d'oeuvre. Elles ont également besoin de paille, qui peut être fournie par une @89exploitation&de&céréales ou importée par l'intermédiaire d'un @47partenaire&commercial. Les fermes d'élevage n'ont pas besoin d'être placées sur des terres fertiles ou d'avoir accès à une source d'eau. @PConsultez la rubrique @45Agriculture&et&nourriture pour en savoir plus sur l'importance de la viande dans l'alimentation de vos citoyens. @PLes fermes d'élevage dégagent des odeurs désagréables et, en général, les citoyens n'apprécient pas de vivre à proximité de ces constructions. @L@LLes Egyptiens anciens élevaient toutes sortes d'animaux pour leur viande. Cliquez @186ici pour en savoir plus."
        }
    }
    message_building_gemstone_mine {
        id: 361,
        
        size [30, 20]
        title {
            text: "Mine de pierres précieuses",
        }
        content {
            text: "Les pierres précieuses sont extraites dans la région des roches. La présence de roches ne suffit pas à déterminer si celles-ci contiennent des pierres précieuses. Si des pierres précieuses peuvent être extraites, l'option Mine de pierres précieuses apparaît dans la liste lorsque vous sélectionnez Structures industrielles, puis Matières premières. A l'instar des @95carrières, les mines de pierres précieuses doivent être adjacentes aux roches et disposer d'un accès à la route et à la main-d'oeuvre. Ces mines étant également susceptibles de s'effondrer, n'oubliez pas de construire une @81étude&d'architecte à proximité. @PLes mines de pierres précieuses dégagent de la poussière et, en général, les citoyens n'apprécient pas de vivre à proximité de ces industries. @L@LPour en savoir plus sur l'exploitation des pierres précieuses dans l'Egypte ancienne, cliquez @382ici."
        }
    }
    message_building_sphinx {
        id: 362,
        
        size [30, 20]
        title {
            text: "Sphinx",
        }
        content {
            text: "Le sphinx, monument sculpté et peint, est le protecteur des pyramides. @PPour construire un sphinx, vous devez d'abord choisir un emplacement. Cliquez sur le bouton Structures religieuses, puis choisissez l'option Sphinx dans le sous-menu Monuments. Une empreinte du sphinx apparaît. Lorsque vous déplacez cette empreinte sur la carte, elle change de couleur et est devient entièrement verte ou verte avec un ou plusieurs losanges rouges. Une empreinte entièrement verte indique que vous avez découvert une réserve cachée de pierre. Cliquez à cet endroit pour faire apparaître la pierre. Si l'empreinte qui apparaît au bout du curseur est rouge, le terrain sur lequel vous souhaitez placer le sphinx n'est pas adapté.  @PVous pouvez à présent laisser la place aux @363tailleurs de pierre et aux @363menuisiers tout en veillant à leur fournir le bois nécessaire. Les menuisiers installent des échafaudages permettant aux tailleurs de pierre de sculpter la pierre au fur et à mesure que le monument s'élève. @PFaites un clic-info sur le sphinx pour consulter le @369contremaître et connaître ainsi l'état d'avancement des travaux. @L@LCliquez @391ici pour en savoir plus sur les sphinx les plus célèbres."
        }
    }
    message_construction_guilds {
        id: 363,
        
        size [30, 20]
        title {
            text: "Guildes de constructeurs",
        }
        content {
            text: "Sans guildes de constructeurs, vous ne pourrez pas construire de superbes édifices à la gloire du pharaon et de l'Egypte. @PIl existe quatre types de guildes de constructeurs : menuisiers, maçons, tailleurs de pierre et artisans. Bien que la main-d'oeuvre fournie par les @8chantiers soit indispensable pour construire un monument, elle n'est pas suffisante. Seul le savoir-faire des guildes permet de transformer des montagnes de matières premières en une construction complexe aux dimensions colossales, telle qu'une pyramide, un @362sphinx, un @371mastaba, un @69temple&solaire, un @368mausolée ou un @392obélisque. Chaque monument requiert un savoir-faire différent. @PLes guildes de constructeurs ont besoin d'un accès à la route et à la main-d'oeuvre. Les guildes de menuisiers doivent disposer de grandes quantités de bois. Les guildes d'artisans ont besoin de @470peinture et @92d'argile (pour le plâtre) afin d'apporter la touche finale aux tombes. Les maçons et les tailleurs de pierre attendent sur le site de construction la livraison des matériaux dont ils ont besoin. @PEn raison du bruit, les citoyens n'apprécient pas de vivre à proximité des guildes de constructeurs. @L@LPour en savoir plus sur ces guildes d'experts de l'Egypte ancienne, consultez les rubriques @386Maçons, @385Tailleurs&de&pierre, @389Menuisiers et @472Artisans."
        }
    }
    message_building_brickworks {
        id: 364,
        
        size [30, 20]
        title {
            text: "Briqueterie",
        }
        content {
            text: "Les briqueteries confectionnent des briques à l'aide d'@92argile et de @89paille. Les briques servent à la construction de plusieurs types de monuments et permettent de réaliser des profits si vous les @47exportez. @PDès qu'une briqueterie dispose d'un accès à la route et de la main-d'oeuvre dont elle a besoin, elle doit être approvisionnée en matières premières pour fonctionner. Les briqueteries ont besoin d'argile et de paille. La paille est produite par les @89exploitations&de&céréales et l'argile est extraite des @92puits&d'argile. Ces deux matières premières peuvent également être importées par l'intermédiaire d'un @47partenaire&commercial.  @PLorsque la briqueterie sera opérationnelle, vous verrez ses employés s'affairer. Dès qu'une cargaison de briques est prête, elle est livrée à un @4entrepôt. @PLes briqueteries sont des voisins @56indésirables. @L@LCliquez @390ici pour en savoir plus sur les briques dans l'Egypte ancienne."
        }
    }
    message_building_warship {
        id: 365,
        
        size [30, 20]
        title {
            text: "Navire de guerre",
        }
        content {
            text: "Ces navires parcourent les voies d'eau et attaquent tout navire hostile. Ils peuvent également lancer des projectiles incendiaires sur des troupes au sol, à condition d'être suffisamment près du rivage. Les navires de guerre sont amarrés à un @356quai&de&navires&de&guerre. Ce type de navire se différencie des transporteurs par l'absence de cabine arrière et sa forme allongée. @L@LPriorité des attaques @LLors d'une attaque, le capitaine d'un navire de guerre suit toujours le même ordre de priorités, quelles que soient les instructions que vous lui avez transmises. Par ordre d'importance, ces priorités sont les suivantes : @L@LTransporteurs ennemis  @LVotre mission risque d'être très compromise si les assaillants parviennent à accoster. Le capitaine de votre navire de guerre attaque en priorité les transporteurs ennemis qui pénètrent dans les eaux territoriales égyptiennes pour les empêcher de débarquer. @L@LDébarquement ennemi  @LSi le capitaine ne parvient pas à empêcher les soldats ennemis de débarquer, il se rapproche de la côte et lance une pluie de flèches sur les envahisseurs à portée de tir qui se trouvent sur la rive.  @L@LNavires de guerre  @LLe capitaine s'occupe ensuite des navires de guerre ennemis. S'il n'y a pas de transporteurs de troupes ou de débarquements dans les parages, le capitaine partira à l'abordage de tout navire de guerre ennemi.  @L@LNavires de guerre ennemis vides  @LEn dernier lieu, votre capitaine surveillera les navires de guerre vides et les attaquera s'il n'y a pas d'autres menaces en vue. @L@LVotre capitaine prend les décisions qui s'imposent à chaque changement de situation. Il quitte la bataille si une menace plus importante survient. Par exemple, s'il combat un navire de guerre au moment où un transporteur ennemi pénètre dans la zone qu'il protège, il quittera la bataille pour aller attaquer le transporteur.  @L@LOrdres donnés aux navires de guerre @LPour donner des ordres à vos navires de guerre, cliquez sur le bateau avec le bouton droit. Les ordres sont les suivants : @L@LMaintenir la position @LLorsque le capitaine reçoit cet ordre, il ne doit pas quitter sa position. Cependant, il se défendra contre toute attaque en faisant face à la menace afin de diminuer les dégâts provoqués par l'abordage et en lançant des flèches sur les ennemis qui passent à proximité. Ordonnez à un groupe de navires alignés de maintenir la position afin de former un barrage empêchant toute intrusion ennemie.  @L@LEngager le combat contre les ennemis immédiats  @LLorsqu'il reçoit cet ordre, le capitaine du navire n'attaque que les ennemis situés à proximité de son bateau.  @L@LChercher et détruire tout ennemi  @LLe capitaine parcourt les voies navigables à la recherche d'éventuels ennemis.  @L@LRéparer @LSi un navire de guerre est endommagé, cliquez sur le bouton Réparer pour ramener le bateau à la fabrique afin qu'il subisse les réparations nécessaires. Lorsque ces réparations sont terminées, le navire retourne automatiquement au quai. Si les dégâts sont importants, le capitaine envoie lui-même son bateau en réparation à la fabrique. Les fabriques de bateaux ont besoin de bois pour réparer les navires.  @L@LRetour au quai  @LCliquez sur ce bouton pour ramener le bateau au quai. @L@LPour déplacer rapidement un navire, sélectionnez-le et cliquez sur un autre endroit de la carte. Lorsqu'il arrive à destination, le capitaine obéit au dernier ordre transmis. Si vous cliquez sur un ennemi, le navire de guerre poursuit sa cible jusqu'à ce quelle soit détruite ou, dans le cas d'une cible terrestre, jusqu'à ce qu'elle soit hors de portée. @L@LCliquez @184ici pour en savoir plus sur les combats dans l'Egypte ancienne."
        }
    }
    message_building_festival_square {
        id: 366,
        
        size [30, 20]
        title {
            text: "Place des fêtes",
        }
        content {
            text: "Pour organiser une fête (voir la rubrique @51Religion pour plus d'informations), votre cité doit disposer d'une place des fêtes. Cette structure doit être construite au niveau d'un carrefour de routes et elle ne nécessite aucune main-d'oeuvre. Chaque cité ne peut disposer que d'une seule place des fêtes, un lieu qui augmente considérablement l'@56attrait d'un quartier.  @PEn l'absence de fête, la place est quasiment déserte, bien que les piétons continuent à circuler sur les routes environnantes. Lorsque la fête commence, la foule afflue de tous côtés pour jouir du spectacle.  @PLes Egyptiens anciens organisaient des fêtes pour célébrer un grand nombre d'événements. Cliquez @393ici pour en savoir plus."
        }
    }
    message_figure_transport_ship {
        id: 367,
        
        size [30, 20]
        title {
            text: "Transporteurs",
        }
        subtitle {
            text: "Transporteurs",
        }
        content {
            text: "Ces navires permettent de transporter vos troupes sur les fleuves et de naviguer sur les océans vers de lointaines contrées. Le transporteur peut accueillir tous les types de compagnies, mais une seule peut embarquer sur chaque bateau. Les transporteurs sont amarrés à un @357quai&de&transporteurs. Ce type de bateau se différencie des navires de guerre par sa cabine arrière et sa forme allongée. @L@LOrdres donnés aux transporteurs @LVous pouvez donner aux transporteurs des ordres spécifiques. Pour effectuer un déplacement, cliquez sur le bateau et choisissez un autre lieu sur la carte. Cliquez avec le bouton droit sur le transporteur pour lui transmettre l'un des ordres suivants : @L@LMaintenir la position @LOrdonne au transporteur de rester où il est. En cas d'abordage ennemi, le capitaine fera pivoter le bateau pour faire face aux agresseurs et diminuer ainsi les dégâts. En revanche, il ne quittera pas le champ de bataille. Utilisez cette option avec précaution car le système de défense des transporteurs est assez limité.  @L@LEviter les ennemis @LLes transporteurs sont des cibles privilégiées, surtout lorsqu'ils transportent une compagnie de soldats. Cliquez sur le bouton Eviter les ennemis afin que le capitaine fasse tout son possible pour éviter les affrontements. Le capitaine du navire s'efforce toujours d'éviter les ennemis, à moins que vous ne lui donniez un ordre contraire.  @L@LEmbarquer/débarquer @LPour embarquer une compagnie de soldats sur un transporteur, cliquez sur le bouton Embarquer, puis sur la compagnie. Les soldats montent à bord du bateau où apparaît automatiquement le drapeau de la compagnie. Faites un clic-info sur le transporteur pour afficher des informations sur la compagnie qui se trouve à bord. @PPour ramener les soldats à terre, cliquez sur le bouton Débarquer, puis positionnez le curseur sur un endroit de la côte pour y faire débarquer la compagnie. @PL'option affichée (Embarquer ou Débarquer) varie selon que le bateau transporte des troupes ou pas.  @L@LRéparer @LSi un transporteur est endommagé, cliquez sur le bouton Réparer pour ramener le bateau à la @82fabrique afin qu'il subisse les réparations nécessaires. Si les dégâts sont importants, le capitaine envoie lui-même son bateau en réparation à la fabrique. Les fabriques de bateaux ont besoin de bois pour réparer les navires.  @L@LRetour au quai  @LCliquez sur ce bouton pour ramener le transporteur au @357quai."
        }
    }
    message_building_mausoleum {
        id: 368,
        
        size [30, 20]
        title {
            text: "Mausolée",
        }
        content {
            text: "Les mausolées représentent de grands tombeaux funéraires destinés aux pharaons et à la noblesse.  @PPour construire un mausolée, plusieurs éléments sont nécessaires : du sable, du grès, la mobilisation d'une guilde de @363&menuisiers, de @363&tailleurs de pierre ainsi qu'un @8chantier. @PVous devez également disposer d'une quantité suffisante de grès dans l'@4entrepôt de la cité. Vous pouvez ensuite commencer à bâtir le mausolée. Cliquez sur le bouton Structures religieuses, puis choisissez l'option Mausolée dans le sous-menu Monuments. Placez ensuite le mausolée sur la carte à l'aide de l'empreinte du monument (la couleur verte indique que l'endroit permet la construction de l'édifice, les losanges rouges signifient que certains éléments du relief empêchent la construction). Une fois le lieu de construction défini, les paysans du chantier dégagent le terrain et creusent les fondations. @PLes fondations terminées, les tailleurs de pierre prennent le relais. Lorsque l'entrepôt contient quatre blocs de grès, les paysans chargent cette cargaison sur un traîneau et la transportent jusqu'au site de construction. Les tailleurs de pierre posent les blocs de grès pour former le premier niveau du monument. Les menuisiers installent ensuite des rampes en bois afin que les tailleurs de pierre puissent accéder au second niveau du mausolée. Le monument est terminé lorsque les ouvriers ont fini de sculpter le second niveau. @L@LPour en savoir plus sur ces sépultures cliquez @396ici."
        }
    }
    message_figure_construction_foreman {
        id: 369,
        
        size [30, 20]
        title {
            text: "Contremaître",
        }
        content {
            text: "Une fois la construction du monument entamée, le contremaître vous tient informé du déroulement des opérations. Il répertorie la quantité de matière première nécessaire à l'achèvement de l'édifice. Il peut également vous indiquer la cause des éventuels retards dans les travaux. Pour consulter le contremaître, faites un clic-info sur le site de construction."
        }
    }
    message_building_monument_construction {
        id: 370,
        
        size [30, 20]
        title {
            text: "Construction d'un monument",
        }
        content {
            text: "Pour réussir vos missions, il vous faudra construire au moins un monument (ou plus dans certaines missions). Vous pouvez construire ces monuments dans l'ordre que vous souhaitez. @PDans la plupart des cas, les ouvriers des @363guildes&de&constructeurs attendent sur le site que les paysans d'un @8chantier leur livrent les matériaux fournis par un @4entrepôt. La main-d'oeuvre du chantier s'efforce de rejoindre le site de construction le plus rapidement possible. La construction des @362sphinx et des @372obélisques se déroule de manière légèrement différente. @G75 @PLes ouvriers peuvent travailler sur plusieurs chantiers à la fois, ce qui vous facilitera grandement la tâche. Soyez prudent car ce type d'organisation présente parfois quelques inconvénients. Il arrive en effet que les @363tailleurs de pierre ne s'entendent pas très bien avec les porteurs de pierre. Parfois, des paysans acheminent les matériaux de construction vers un chantier tandis que les tailleurs de pierre attendent, immobiles, sur le chantier auquel ils voudraient prendre part.  @PCette situation risque de profondément décevoir le @373chef&des&monuments, mais vous constaterez très vite qu'il est particulièrement difficile de concilier les porteurs de pierre habitués à recevoir des ordres stricts et les tailleurs de pierre d'esprit plus indépendant. Pour éviter ce type de désagréments, nous vous conseillons de construire un à un vos monuments plutôt que de gérer plusieurs chantiers simultanément. @PLes monuments sont parfois si imposants qu'il est difficile de les placer dans votre cité. Pour certains édifices de grande taille, vous ne verrez pas la totalité de l'empreinte lorsque vous essayerez de positionner le bâtiment sur la carte. @PPour évaluer l'emplacement d'un monument, appuyez sur la touche 'M'. L'empreinte se fige, vous permettant de voir la position du bâtiment sous différents angles. Cliquez pour placer le monument à cet endroit (si cet emplacement convient). Pour choisir un autre endroit, relâchez la touche 'M' et déplacez l'empreinte du monument. @PDe plus, certains monuments doivent être construits dans les falaises : @492Abou&Simbel et les @478tombes&royales. @PPour en savoir plus sur les monuments, consultez les rubriques consacrées à chaque édifice. Ces rubriques sont répertoriées dans le menu Aide. @L@LPour en savoir plus sur l'histoire des monuments, cliquez sur @391sphinx, @392pyramides, @394mastabas, @493Abou&Simbel, @481bibliothèque&d'Alexandrie, @482Caesareum, @475Vallée&des&Rois et @396autres&monuments."
        }
    }
    message_building_mastaba {
        id: 371,
        
        size [30, 20]
        title {
            text: "Mastaba",
        }
        content {
            text: "Les mastabas sont de riches sépultures construites pour les notables. Vous pourrez vous-même choisir un mastaba comme dernière demeure. @PPour construire un mastaba, vous aurez besoin d'un grand nombre de @364briques et des services d'une @363guilde&de&maçons. Les paysans d'un ou plusieurs @8chantiers vous seront également nécessaires. @PLa première étape de la construction d'un mastaba consiste à choisir un site. L'emplacement sélectionné est approprié lorsque 'l'empreinte' du mastaba est verte. Si l'empreinte verte contient des losanges rouges, le terrain sélectionné n'est pas adapté. Lorsque l'empreinte est entièrement verte, cliquez sur le bouton de la souris pour sélectionner définitivement le site de construction du mastaba. Des piquets délimitent la zone où sera construit le monument. @PUne fois le site de construction sélectionné, les maçons et les paysans se mettent au travail. Les paysans apportent des traîneaux chargés de briques et les maçons les placent sur l'édifice. @PLes défunts ont besoin de toutes sortes d'objets pour leur voyage vers l'au-delà ; par conséquent, vous devrez déposer dans le mastaba diverses @374offrandes&funéraires. Consultez le @373chef&des&monuments pour connaître les offrandes appropriées. Adressez-vous au @369contremaître pour connaître l'état d'avancement des travaux. Cliquez @370ici pour en savoir plus sur la construction des monuments. @L@LCliquez @394ici pour en savoir plus sur les mastabas dans l'Egypte ancienne."
        }
    }
    message_building_obelisk {
        id: 372,
        
        size [30, 20]
        title {
            text: "Obélisque",
        }
        content {
            text: "Les obélisques symbolisent les rayons du soleil. De chaque côté du monument sont gravés les événements marquants de l'histoire égyptienne. @PLes obélisques nécessitent une importante quantité de @95granit. Avant d'entamer la construction d'un tel monument, veillez à stocker assez de granit dans l'@4entrepôt. @PDéplacez le curseur de la souris sur la carte pour choisir le lieu où sera érigé l'obélisque. Une empreinte entièrement verte indique que l'endroit sélectionné convient à la construction du monument. Si l'empreinte contient des losanges rouges, le terrain sélectionné n'est pas adapté pour construire l'obélisque.  @PUne fois le site de construction choisi, les blocs de granit sont amenés sur le chantier. Les @363&menuisiers de la guilde construisent alors des échafaudages tout autour du monument afin que les @363tailleurs de pierre puissent commencer à sculpter la roche. Les paysans n'interviennent pas dans la construction d'un obélisque. @PFaites un clic-info sur l'obélisque pour consulter le @369contremaître et connaître ainsi l'état d'avancement des travaux. @L@LLes obélisques se dressent fièrement vers le ciel depuis des milliers d'années. Cliquez @397ici pour en savoir plus sur ce type de monument."
        }
    }
    message_overseer_monuments {
        id: 373,
        
        size [30, 20]
        title {
            text: "Chef des monuments",
        }
        content {
            text: "Votre chef des monuments peut vous expliquer ce qui empêche les travaux de commencer. Il s'occupe également de répartir les @374&offrandes funéraires entre les différentes tombes. Pour connaître l'état d'avancement des travaux de construction, consultez le contremaître en cliquant avec le bouton droit de la souris sur le monument."
        }
    }
    message_burial_provisions {
        id: 374,
        
        size [30, 20]
        title {
            text: "Offrandes funéraires",
        }
        content {
            text: "Les offrandes funéraires déposées dans les tombes sont destinées au défunt pour son grand voyage vers la vie éternelle. Ces offrandes représentent des objets utilisés, de son vivant, par le défunt. Vous pouvez également déposer divers matériaux servant à la construction d'une barque funéraire ou d'un sarcophage. Un monument n'est pas achevé tant qu'il ne contient pas les offrandes funéraires nécessaires. Le @373chef&des&monuments vous fournit la liste de ces offrandes funéraires et les quantités recommandées. Lorsque vous avez réuni ces différents objets, contactez le chef des monuments afin qu'il les dépose dans le tombeau. @PVous pouvez déposer les offrandes funéraires même si l'@4entrepôt ne dispose pas de la quantité requise. Ces offrandes peuvent en effet être apportées petit à petit jusqu'à atteindre la quantité nécessaire. @PVotre cité devra parfois @47importer des offrandes funéraires. @L@LLes Egyptiens anciens plaçaient un grand nombre d'objets dans les tombeaux pour accompagner les défunts vers l'au-delà. Cliquez @395ici pour en savoir plus sur les offrandes funéraires placées dans les sépultures des Egyptiens anciens."
        }
    }
    message_building_stepped_pyramid {
        id: 375,
        
        size [30, 20]
        title {
            text: "Pyramide à degrés",
        }
        content {
            text: "Ces pyramides, les premières à apparaître sur le sol égyptien, représentent de gigantesques escaliers qui s'élèvent vers le soleil. Ils sont construits entièrement en @95pierre et nécessitent l'installation de rampes en bois pour permettre aux ouvriers d'atteindre le sommet de la pyramide. Pour construire ces rampes et poser les blocs de pierre, vous devez faire appel aux guildes de @363menuisiers et de @363tailleurs&de&pierre. Les paysans se chargeront quant à eux d'amener, à l'aide de grands traîneaux, les blocs de pierre sur le site de construction. Lorsque les tailleurs de pierre sont prêts à travailler et que l'@4entrepôt contient quatre blocs de pierre, les paysans prennent livraison de la pierre pour la transporter jusqu'au chantier. @PIl existe cinq types de pyramides à degrés : petite, moyenne, grande, ensemble de pyramides et grand ensemble de pyramides. Consultez le @369contremaître et le @373chef&des&monuments pour de plus amples informations. Vous trouverez également des renseignements intéressants dans la rubrique @370Construction&de&monuments. @L@LCliquez @392ici pour en savoir plus sur l'innovation architecturale du vizir Imhotep : la pyramide à degrés."
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
            text: "Osiris, Sebek et Min",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Le rôle d'Osiris dans la religion égyptienne a évolué au cours des millénaires. Avec son épouse et soeur Isis, et son frère Seth, il fut l'un des premiers dieux et membres de l'Ennéade (voir la section @399Religion pour en savoir plus). @L@LLe mythe d'Osiris l'associait à l'agriculture, au Nil et aux rites funéraires. Rê-Atoum mit Osiris à la tête de l'Egypte ancienne. Osiris épousa sa soeur, Isis, et son règne fut riche en enseignements pour son peuple, en particulier l'art de l'agriculture. Osiris quitta ensuite l'Egypte pour aller civiliser le reste du monde, laissant Isis à la tête du royaume. Elle régna de manière efficace en son absence, mais au retour d'Osiris, son frère, Seth, organisa un complot contre lui. Seth convia Osiris à une fête somptueuse où il lui présenta un magnifique cercueil. Il offrit ce cercueil à la personne à qui il conviendrait le mieux. Lorsqu'Osiris y pénétra, Seth le referma et le jeta dans le Nil. Isis réussit à le repêcher, mais Seth s'en empara et découpa Osiris en morceaux. Isis se mit à pleurer de désespoir, et ses larmes provoquèrent l'inondation. Isis rassembla les morceaux éparpillés du corps d'Osiris, à l'exception de ses parties génitales, qui avaient été dévorées par un poisson, l'oxyrhynque. Isis enveloppa Osiris dans des bandelettes de toile, d'une manière qui rappelle celle employée pour les momifications. Il était interdit aux Egyptiens de consommer la chair de l'oxyrhynque. Osiris devint le dieu du monde sous-marin et le juge suprême qui octroyait ou refusait l'entrée dans l'au-delà. @L@LSebek, le dieu-crocodile de la fertilité, était vénéré à l'origine dans le Fayoum, même s'il était connu à travers toute l'Egypte. Son nom signifie 'celui qui te regarde'. Min, divinité génératrice, était également associé à la fécondité masculine et était vénéré à travers toute l'Egypte."
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
            text: "Rê, Maât et Horus",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Rê fut longtemps placé au sommet du panthéon égyptien. En tant qu'ancêtre de tous les dieux de l'Ennéade, c'était le créateur par excellence et il était associé au soleil. @L@LMaât était la déesse de la justice, également associée à la vérité et à l'ordre. La plume qui orne sa tête sert à peser le coeur des prétendants à la vie éternelle. @L@LHorus était principalement associé aux pharaons. Fils d'Isis et d'Osiris, il  vengea la mort de son père en dénonçant Seth comme son assassin. Horus était symbolisé par un faucon. "
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
            text: "Ptah, Amon et Thot",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Ptah, dieu des artisans, est associé aux pharaons de Memphis, qui unifièrent l'Egypte (voir la section @399Religion pour en savoir plus sur l'influence de ces pharaons sur les croyances des Egyptiens). Il était particulièrement vénéré par les artisans de Deir el-Médineh, qui construisirent les tombes de la Vallée des Rois et de la Vallée des Reines. @L@LAmon, dieu du soleil, était associé au soleil levant. Il marqua la XIIème dynastie des rois de Thèbes. @L@LThot, dieu de la sagesse et du savoir, était considéré comme le scribe des autres dieux. Il était particulièrement associé à la ville d'Hermopolis."
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
            text: "Seth, Anubis et Sekhmet",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Seth, frère d'@376Osiris, était le dieu de la destruction. A l'origine, Seth était le protecteur de la Basse-Egypte. Lorsque la Haute-Egypte devint prédominante, le dieu protecteur de l'Egypte, @377Horus, remplaça progressivement Seth et ce dernier vit son image se ternir. @L@LAnubis, dieu de la mort, était le dieu embaumeur. Symbolisé par un chacal, Anubis protégeait les morts. @L@LSekhmet, divinité guerrière, était représentée comme une femme à tête de lionne. Epouse de Ptah, elle détruisit ce qu'il avait créé. Les Egyptiens la vénéraient dans l'espoir de l'apaiser."
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
            text: "Bastet, Isis et Hathor",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Bastet, femme à tête de chatte ou lionne, était la déesse du foyer, des chats, du feu et des femmes enceintes. Elle protégeait la maison d'une manière douce et agressive à la fois. Elle était également la déesse protectrice de Bubastis. @L@LIsis, épouse d'@376Osiris et mère d'@377Horus, enveloppa le corps brisé d'Osiris dans des bandelettes. C'est pourquoi elle fut considérée comme la déesse de la guérison. Elle était représentée sous les traits d'une femme, souvent en compagnie de son fils. @L@LHathor était la déesse de la joie et des plaisirs. Représentée comme une vache, elle était la déesse protectrice de Dendérah, de Memphis, de Cusae et de Gebelein."
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
            text: "Histoire",
        }
        content {
            text: "La malaria était l'un des dangers de la vie à proximité des marécages. Cette maladie est en effet provoquée par l'un les quatre parasites véhiculés par les moustiques anophèles, particulièrement actifs la nuit. Le principal symptôme de la malaria est la fièvre, suivie de douleurs musculaires, de transpiration et de fatigue. L'un des parasites responsables de la malaria provoque une forme mortelle de cette maladie. @L@LAfin de se prémunir contre les piqûres des moustiques anophèles, potentiellement mortelles et tout au moins extrêmement gênantes, les Egyptiens anciens accrochaient des filets à moustiques à leurs lits. L'historien grec Hérodote rapporte également que les Egyptiens élevaient leur lit dans des tours pour dormir, car ils pensaient que les moustiques ne volaient pas aussi haut."
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
            text: "Bijoux",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Dans les orfèvreries, on transformait des pierres précieuses et semi-précieuses en colliers, ceintures et autres parures. Pour assembler les perles, les orfèvres commençaient par percer un trou dans la pierre à l'aide d'une perceuse à main et à pointe de silex. Une fois les trous percés, ils faisaient passer un fil et l'attachaient. Les pierres précieuses leur servaient également à effectuer des incrustations. @L@LLes illustrations retrouvées sur les tombes indiquent que les nains étaient souvent employés dans l'orfèvrerie."
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
            text: "Chasse",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "En comparaison des exploitations agricoles, la chasse n'était pas une source de nourriture importante dans l'Egypte ancienne. Mais cette activité état néanmoins appréciée par les riches et de nombreux pharaons se vantaient de leurs talents de chasseurs. Leur principal gibier était les gazelles, les antilopes, les bouquetins, les boeufs, les moutons et les autruches, même si certains chassaient également les hyènes, les lions et les léopards comme divertissement (et, dans le cas des léopards et des lions, pour leur peau). Les chasseurs utilisaient des arcs et des flèches ou des lances pour tuer leur gibier. @L@LLes Egyptiens aimaient également la chasse au gibier d'eau, qu'il s'agisse de volatiles ou d'hippopotames. Les hommes se réunissaient pour chasser l'hippopotame avec un harpon  muni d'une corde. Les chasseurs frappaient l'hippopotame à l'aide de ces harpons. Une fois l'animal à bout de force, ils le ramenaient sur le rivage à l'aide des cordes. @L@LPour tuer les volatiles, les chasseurs utilisaient des armes que l'on peut rapprocher des boomerangs australiens. Les assistants des chasseurs, qu'il s'agisse de membres de leur famille ou de serviteurs, rassemblaient les volatiles abattus. Les oiseaux étaient également piégés dans des filets que l'on étendait sur le sol. Ce filet était parsemé de nourriture pour oiseaux. Une fois attirés jusqu'à l'endroit où se trouvait le filet, les coins de ce dernier se refermaient et les oiseaux étaient pris au piège."
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
            text: "Prêtres",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Une grande partie de la population égyptienne ancienne était constituée de prêtres. Leur rôle allait bien au-delà des devoirs religieux. Comme l'Egypte ancienne était une théocratie, les prêtres s'acquittaient souvent de tâches administratives au sein de leurs communautés, leur rôle s'étendant parfois à celui de juges. @L@LLes prêtres étaient reconnaissables à leur propreté. Ils suivaient des rites de purification avant de pénétrer à l'intérieur des temples et se rasaient les cheveux pour se protéger contre les poux et autres impuretés. Le régime alimentaire du prêtre dépendait du dieu qu'il servait. Les prêtres avaient un habillement particulier et devaient porter des sandales blanches. Les prêtres de haut rang arboraient parfois des peaux de léopards. @L@LLa principale préoccupation religieuse d'un prêtre consistait à prendre soin du dieu résident et à le nourrir. Chaque temple abritait la statue de son dieu protecteur. Chaque prêtre du temple avait une responsabilité particulière dans la satisfaction du dieu. Certains devaient s'assurer que le dieu était correctement nourri et préparaient ses repas avec les offrandes des habitants ou les produits du temple. Le dieu profitait de 'l'essence' de cette nourriture, tandis que les prêtres se contentaient des restes. Les prêtres se chargeaient également de l'habillement et de la toilette des dieux, ainsi que de leur divertissement. Le dieu effectuait parfois une sortie dans le village (voir la section @393Fêtes pour en savoir plus). @L@LLe clergé était divisé en classes distinctes. Le grand prêtre, ou premier prophète, était nommé par le pharaon. Il constituait l'autorité suprême au sein du temple et faisait souvent office de conseiller du pharaon. En dessous, se trouvait le second prophète, qui pouvait avoir diverses fonctions au sein du temple ou du domaine, comme au sein des ateliers ou des fermes. Encore en dessous se trouvaient les prêtres responsables de fonctions spécifiques, telles que la toilette du dieu ou son divertissement. La plupart des prêtres se relayaient, travaillant un mois sur trois."
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
            text: "Tailleurs de pierre",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les tailleurs de pierre surveillaient les @193carrières et la construction des @392pyramides et d'autres monuments. Ils savaient tout de la pierre utilisée et de ses méthodes d'extraction. Ils participaient peu au travail de force, laissé aux paysans des classes inférieures et parfois aux esclaves. Les tailleurs de pierre supervisaient l'ensemble du travail. Outre les grands projets de construction, leur compétence était requise pour des entreprises de moindre importance, telles que l'édification des fondations d'une maison."
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
            text: "Maçons",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La technique de la maçonnerie n'a pas tellement évolué au cours des siècles. Les matériaux sont essentiellement les mêmes : @390brique et mortier. Dans l'Egypte ancienne, le mortier était constitué d'un mélange d'argile, de sable, de paille et de balle. Les maçons étalaient le mortier à l'aide d'une truelle en bois avant de poser les briques. Ils assuraient la droiture des murs grâce à des fils à plomb."
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
            text: "Histoire",
        }
        content {
            text: "Les scribes, qui officiaient au sein de la société et du gouvernement, étaient associés à toute entreprise publique. Les Egyptiens voulaient noter toutes les actions et les scribes étaient les seuls à pouvoir assumer cette fonction. Ils inscrivaient les impôts que chaque individu devait au gouvernement, notaient les exportations et importations et poussaient leur sens du devoir jusqu'à accompagner les soldats au combat pour rendre compte des événements. Les scribes établissaient des documents légaux répertoriant, par exemple, les doléances des citoyens et prenaient en charge la correspondance des personnes privées. @L@LPour les scribes, les outils du commerce étaient le papyrus, une palette contenant deux cartouches d'encre (noir et rouge), un pot d'eau, et des pinceaux en roseaux. Le scribe trempait le pinceau dans l'eau, puis le frottait sur une cartouche d'encre. Il pouvait ensuite écrire sur le papyrus. @L@LTrès peu de scribes savaient écrire les hiéroglyphes, ces derniers étant réservés aux monuments et aux temples. Dans la vie quotidienne, on utilisait une écriture différente, le hiératique.  @L@LLa langue écrite comprenait environ 700 signes et associait des symboles représentant des sons à d'autres symboles représentant des idées. Cette graphie ignorait les voyelles, si bien que la langue orale des Egyptiens anciens conserve encore de son mystère."
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
            text: "Histoire",
        }
        content {
            text: "L'économie égyptienne était relativement stable et la production alimentaire régulière, grâce aux crues périodiques. Les pays voisins le savaient, si bien que l'Egypte connut une immigration importante. @L@LCertains immigrants vinrent en Egypte pour faire du commerce. Des fouilles archéologiques effectuées dans des villes portuaires telles que Memphis ont révélé l'existence de communautés non égyptiennes. Ces marchands d'origine étrangère sont illustrés sur des tombes du Moyen Empire et du Nouvel Empire. Certains habitants des pays voisins, comme la Libye, affluèrent dans l'Egypte ancienne. Sous la XIIème dynastie, les Libyens occupaient de grandes parties du Delta occidental, avant de s'installer dans le Delta oriental. @L@LCertains peuples arrivaient en Egypte avec des intentions plus barbares. Les @181envahisseurs de l'Egypte s'implantèrent généralement de façon durable malgré les revers de fortune. La plupart de ceux qui restaient jouissaient des mêmes droits que les Egyptiens, certains occupant même des postes importants au sein du gouvernement."
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
            text: "Menuiserie",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les menuisiers confectionnaient de nombreux objets utiles au sein de la société égyptienne. Le @192bois produit localement étant rare, les menuisiers devaient faire bon usage de ce matériau. Ils utilisaient également du bois importé, mais ce dernier était relativement onéreux et donc réservé aux citoyens les plus aisés. @L@LLes menuisiers étaient équipés de haches, de scies et d'herminettes pour transformer les bûches en planches. A l'aide de leurs haches, ils arrachaient toutes les branches des bûches et découpaient le bois si nécessaire. Ils utilisaient la scie pour transformer les bûches en planches, et l'herminette pour les lisser. @L@LParmi les produits finis, on trouvait coffres, lits, portes et chambranles, chaises et, surtout, cercueils. Au lieu de clous, les artisans se servaient de chevilles pour assembler les pièces. Certaines de ces pièces étaient superbes, ornées de fines incrustations et de gravures. @L@LLes menuisiers participaient également à la construction de grands édifices. Les plafonds des demeures les plus riches étaient souvent supportés par des colonnes en bois finement décorées. @L@LLa menuiserie de base a peu évolué au cours de l'histoire de l'Egypte ancienne, et les mêmes outils ont toujours été utilisés. La principale innovation dans ce domaine fut l'introduction du foret. Sous le Nouvel Empire, les ouvriers se servaient d'un foret à archet pour percer des trous pour les chevilles."
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
            text: "Briques",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les briques constituaient un matériau de construction idéal. Les maisons en brique, qui ne diffusaient pas facilement la chaleur, restaient relativement fraîches l'été. La fabrication des briques s'effectuait à l'aide d'une combinaison d'argile et de paille. L'argile était humectée, mélangée à la paille puis immergée. La paille commençait alors à se décomposer, sécrétant une boue qui compactait la brique. Celle-ci était ensuite séchée au soleil. Lorsque les briques étaient prêtes, le @386maçon pouvait commencer son travail."
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
            text: "Histoire",
        }
        content {
            text: "Le sphinx, associé à Amon dans l'Egypte ancienne, a le corps d'un lion et la tête d'un roi. Il y avait de nombreux sphinx en Egypte, le plus célèbre étant celui de Gizeh.  @L@LConstruit vers 2500 av. J.-C, ce sphinx gigantesque semble garder la pyramide de Chéphren et domine une ancienne carrière. Son visage est censé être celui de Chéphren lui-même. Il mesure environ 60 mètres de long et 20 mètres de haut. Il est sculpté dans du grès tendre. @L@LCe sphinx resta enterré dans le sable durant la majeure partie de son existence. La légende raconte qu'avant de devenir pharaon, Thoutmôsis IV chassait près de l'endroit où était enseveli le sphinx et s'endormit dessus. Le sphinx révéla à Thoutmôsis dans un rêve que, s'il le mettait à jour, il deviendrait pharaon. Thoutmôsis accéda à la prière du sphinx et devint pharaon en 1425 av. J.-C. Il raconta cette histoire sur des stèles qu'il plaça entre les pattes du sphinx. @L@LLe sphinx de Gizeh fut une nouvelle fois enseveli, puis définitivement désensablé dans les années 1930. Les tentatives de restauration ont eu des résultats mitigés."
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
            text: "Pyramides",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Durant des siècles, on a émis des hypothèses sur la construction des pyramides. Il semble en effet incroyable que les Egyptiens, qui ignoraient tout des outils modernes tels que le chariot élévateur ou la grue, aient pu construire de telles structures. @L@LL'édification d'une pyramide commençait par un plan précis. Le vizir, deuxième personnage en importance après le pharaon, supervisait généralement l'ensemble du projet, assisté de l'architecte royal (medjeh nesu en Egyptien ancien), qui élaborait les plans. L'architecte royal était responsable du choix du matériau à utiliser et de son acheminement sur le site de construction. @L@LUne fois le site choisi avec soin, des astronomes déterminaient l'axe nord-sud de la pyramide. Ensuite, des contremaîtres délimitaient les côtés de la pyramide à l'aide d'une corde spéciale suffisamment épaisse pour ne pas risquer de se détendre et de fausser ainsi les dimensions de l'édifice. Le sol était ensuite nivelé. Il est probable que des fossés étaient emplis d'eau pour vérifier le niveau du terrain. @L@LUne fois ces tâches effectuées, la construction proprement dite pouvait commencer. Une cérémonie avait lieu pour célébrer l'événement. Durant cette célébration, le pharaon marquait les angles de la pyramide de piquets, étendait une corde entre ces derniers, et plaçait une motte de terre en guise de première pierre. @L@LA ce stade, les @385tailleurs de pierre et les @155ouvriers prenaient le relais. Les premiers creusaient les pièces souterraines, dont la chambre funéraire. Une fois ce travail achevé, commençait le processus ardu d'acheminement des blocs de pierre, certains pesant jusqu'à 2,5 tonnes. On hissait les blocs sur des traîneaux et, pour atteindre les parties les plus élevées de la pyramide, on utilisait des rampes. Outre les pierres grossièrement taillées qui constituaient l'intérieur de la pyramide, on utilisait des pierres plus fines pour la façade. @L@LCertaines pyramides étaient indépendantes, mais la plupart faisaient partie d'un ensemble. Celui-ci comprenait généralement un temple construit près d'un plan d'eau ou d'une zone cultivée. Partant de ce temple, une longue chaussée menait au temple funéraire, situé à l'est de la pyramide. @L@LLa forme des pyramides a évolué avec les techniques de construction. La première pyramide, la pyramide à degrés de Djeser, n'a pas une forme régulière. Construite vers 2620 av. J.-C, elle se compose d'une série de carrés empilés. La première vraie pyramide est celle de Snéfrou, construite vers 2550 av. J.-C. Les 'degrés' de cette pyramide étaient homogénéisés à l'aide d'un revêtement extérieur, pratique qui fut vite adoptée pour la construction d'autres pyramides. La plus grande pyramide est celle de Koufou, qui mesure 230 x 230 m et atteint 146 mètres de haut. La pyramide penchée de Snéfrou est une construction unique en son genre. Les angles se déplacent des deux tiers vers le haut environ. On suppose que les architectes ont jugé que cette pyramide serait trop lourde et risquerait de s'effondrer si sa construction suivait l'inclinaison initialement prévue. En outre, la première pyramide de Snéfrou s'étant effondrée, ils ont sans doute pensé que mieux valait prévenir que guérir."
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
            text: "Fêtes",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Dans l'Egypte ancienne, les fêtes étaient de joyeuses célébrations durant lesquelles la nourriture abondait et la bière coulait à flots. Ces fêtes avaient lieu à diverses occasions : pour honorer un dieu, marquer la moisson ou célébrer la longévité du pharaon. Les cinq derniers jours de l'année se passaient en festivités, de nombreuses autres fêtes ayant lieu le reste de l'année. @L@LC'est durant les fêtes en l'honneur d'une divinité que le peuple pouvait accéder directement à ses dieux. La procession du dieu était le point central des fêtes religieuses. Durant la fête, la statue du dieu qui résidait ordinairement dans le temple, sous l'oeil du public et parée de ses plus beaux habits, paradait à travers la ville sur une barque tirée par des prêtres. Ces derniers prenaient parfois du repos, et c'est durant ces haltes que les rites avaient lieu. Sous le Nouvel Empire, les citoyens pouvaient interroger la divinité pendant que les prêtres se reposaient. Les prêtres s'inclinaient si la réponse était positive et reculaient si elle était négative. A la fin de la cérémonie, la divinité rentrait dans sa demeure, le temple. @L@LParfois, les dieux voyageaient très loin et on les transportait par bateau. Par exemple, durant la fête d'Opet, Amon alla de Karnak jusqu'à Louqsor. Il effectua ce voyage sur le Nil. Opet, qui durait entre 11 et 27 jours, était l'une des fêtes les plus joyeuses de l'Egypte ancienne. @L@LSi un pharaon supportait un règne de 30 années, la fête Sed avait lieu. Durant cette fête, célébrée au cours de la 30ème année du règne du pharaon et tous les trois ans par la suite, le pharaon exécutait un rite destiné à prouver qu'il (ou elle) était encore apte à régner. Certains pharaons n'attendaient pas 30 ans pour avoir un Hebsed, qui pouvait avoir lieu bien plus tôt au cours de leur règne. @L@LIl ne fait aucun doute que les Egyptiens, quelle que soit leur niveau social, appréciaient les fêtes, qui étaient l'occasion de bien manger et de bien boire. Il s'agissait en outre d'un répit face aux corvées quotidiennes."
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
            text: "Mastabas",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Sous l'Ancien Empire, on enterrait les pharaons et les nobles sous des mastabas. Ces derniers coiffaient le puits menant à la chambre funéraire. Leur construction était d'abord simple, structures basses comportant des inscriptions, puis ils s'agrandirent et furent complétés par une chapelle. Les mastabas sont considérés comme les ancêtres des pyramides ; il se peut d'ailleurs que la pyramide à degrés de Djeser ait été à l'origine un mastaba."
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
            text: "Offrandes funéraires",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les tombes comportaient tout ce dont le défunt avait besoin dans l'au-delà. Les tables funéraires comportaient les outils associés à la profession du défunt, de la nourriture, des articles de toilette, des bijoux, des instruments de musique, du maquillage, bref, tout ce dont le défunt s'était servi au cours de sa vie. Elles étaient également équipées d'oushebtis, ou 'répondants'. Ces statuettes étaient introduites dans la tombe au cas où le défunt ait à exécuter des tâches dans l'au-delà. Elles effectuaient alors le travail à sa place."
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
            text: "Autres monuments",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Outre les @397obélisques, les @394mastabas, les @392pyramides et les @391sphinx, l'Egypte ancienne comportait de nombreux autres monuments. On peut citer, par exemple, les mausolées et les temples solaires.  @L@LLe soleil était considéré comme un donneur de vie. Ceci explique les nombreux temples solaires construits en Egypte, sous la Vème dynastie notamment. Les plus célèbres se trouvent à Abou Gorâb, site se trouvant à un peu plus d'un kilomètre au nord-est de la pyramide de Sahure. On édifia sur ce site deux temples solaires, qui furent le lieu de sacrifices d'animaux. @L@LLes mausolées et les chapelles coiffaient souvent les tombes et constituaient un lieu où la famille du défunt pouvaient faire des offrandes. Ces offrandes étaient destinées à assurer au défunt une vie agréable dans l'au-delà. Les citoyens qui en avaient les moyens faisaient construire de telles chapelles pour les membres de leur famille. Les mausolées privés étaient très nombreux en Egypte."
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
            text: "Obélisques",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les obélisques étaient associés au soleil, symbolisant ses rayons ou le monticule sur lequel il brillait en premier. Construits en granit et incrustés de hiéroglyphes, les obélisques se trouvaient à l'extérieur des temples, généralement par paires. @L@LLa forme des obélisques était taillée dans les carrières, et un édifice inachevé à Assouan en dit long sur l'extraction d'une roche aussi volumineuse. Les ouvriers sculptaient lentement la forme voulue à l'aide d'un outil particulier. La construction de l'obélisque d'Assouan fut interrompue, car une fissure s'était développée au coeur de la pierre. @L@LUne fois l'obélisque taillé dans la pierre, on ne sait pas comment il en était dégagé. Des tentatives récentes d'extraction d'obélisques à l'aide de méthodes anciennes ont échoué."
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
            text: "Toiles et ateliers de tissage",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Constituée de @189lin, la toile était le principal textile dans l'Egypte ancienne. Si certains tissus étaient constitués de laine ou de chanvre, ils étaient considérés comme étant de qualité bien inférieure à la toile. @L@LPour confectionner du tissu, la fibre de lin était dans un premier temps filetée. Assis devant des piles de lin, les fileurs enroulaient les fibres pour en faire des pelotes. Ensuite, les fils étaient attachés à des fuseaux, et le tissage pouvait commencer. @L@LLes Egyptiens utilisaient un métier à tisser horizontal placé sur le sol. Les tisserands le chargeaient de deux rangées de fils parallèles (la chaîne). Deux ouvriers étaient assis à chaque extrémité du métier à tisser et faisaient circuler la navette tissée (la trame) d'avant en arrière pour confectionner le tissu. @L@LSous le Nouvel Empire, un métier à tisser vertical remplaça le métier à tisser horizontal. Il permettait aux tisserands d'être assis plus confortablement sur des tabourets. @L@LLa plupart des tisserands étaient des femmes faisant généralement partie du harem du pharaon."
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
            text: "Histoire",
        }
        content {
            text: "Le panthéon égyptien était peuplé de dieux majeurs et mineurs. La plupart des villes, voire des individus, étaient associés à une divinité protectrice, pratique reflétant l'importance que l'on accordait à telle ou telle divinité. @L@LL'un des cultes les plus anciens est l'Ennéade, un groupe de neuf divinités. Ce culte fut fondé dans la cité d'Héliopolis. Le premier dieu de l'Ennéade est Atoum, qui s'associa avec Rê et devint Rê-Atoum. Ce dernier, bien que de sexe masculin, donna naissance à des jumeaux, Shou et Tefnout. Shou était le dieu de l'air, et Tefnout la déesse de l'ordre du monde. Shou et Tefnout eurent quatre enfants : Isis, Osiris, Néphthys et Seth. Horus, fils d'Isis et d'Osiris, est à classer à part. Rê finit par se séparer d'Atoum et devint le principal dieu de l'Ennéade. Cette théogonie prédomina dans l'Egypte prédynastique, et Rê eut encore son importance dans l'Egypte ancienne.  @L@LLorsque Horus-Aha, également connu sous le nom de Ménès, unifia la Haute et la Basse-Egypte, sa croyance personnelle en Ptah, dieu créateur, bouleversa le système de croyance égyptien. Ménès pensait que les dieux de l'Ennéade étaient tous des incarnations de Ptah. Cependant, Rê restait le principal dieu. @L@LUn autre culte surgit de la cité d'Hermopolis, en Haute-Egypte. Les habitants de cette ville croyaient en une ogdoade, ou collège de huit dieux. Au sein de l'ogdoade, des couples constitués d'un dieu et d'une déesse représentent différents aspects du monde. Noun et Naunet représentaient l'eau, Heh et Hehet l'infinité de l'espace, Kek et Keket étant les divinités de l'obscurité, Amon et Amaunet étant celles de l'air. @L@LSous le Nouvel Empire, le culte Amon détrôna celui de Rê. Sa domination continua jusqu'au règne d'Akhnaton. Ce dernier tenta d'instituer le monothéisme en Egypte, persuadé qu'Aton, symbolisé par le disque solaire, était le seul dieu. Durant son règne, Akhnaton exclut les autres dieux des temples. A sa mort, toutefois, le polythéisme fut rapidement réintroduit et les dieux purent regagner leurs temples."
        }
    }
    message_mission_naqada {
        id: 400,
        type: 3,
        size [40, 30]
        title {
            text: "Nubt",

        }
        subtitle {
            text: "Un village est né",

        }
        content {
            text: "@PBienvenue dans l'Egypte ancienne, terre des pharaons ! Vous allez prendre part à l'histoire de l'une des plus grandes civilisations que le monde ait jamais connues, une histoire qui couvre plus de quinze siècles. Vous dirigerez une famille, génération après génération, depuis sa naissance dans la préhistoire égyptienne, en passant par les balbutiements de la civilisation... jusqu'à l'établissement d'un empire unique et puissant... et même au-delà.     @PVotre histoire commence sur les berges du Nil, dans une région appelée Nubt, alors qu'une petite confédération de clans tente tant bien que mal de survivre dans un environnement hostile. Votre famille est à la tête de cette petite communauté. @PCe village a en priorité besoin d'habitations pour que les Egyptiens puissent s'y installer ; il lui faut également des chemins permettant aux habitants de circuler facilement."
        }
    }
    message_mission_thinis_2 {
        id: 401,
        type: 3,
        size [40, 30]
        title {
            text: "This",

        }
        subtitle {
            text: "L'aube de la civilisation",

        }
        content {
            text: "@PAprès de nombreuses années, la nouvelle génération de votre famille s'est réinstallée dans la région de This, en Haute-Egypte. Un petit groupe de dirigeants locaux tente d'étendre son influence à la Basse-Egypte, ainsi qu'à toutes les terres bordant le Nil ; il veut unifier ce royaume sous le règne d'un chef suprême.   @PL'établissement de This comme cité florissante, prouvera la puissance de sa confédération et l'aidera à obtenir la suprématie sur la Basse-Egypte ainsi que sur les autres factions en quête de pouvoir. Mais il faudra pour cela offrir à la population des divertissements et construire de majestueux temples voués au culte de la divinité protectrice de la région. @PLa construction d'une telle cité nécessite certaines richesses. Vous trouverez de riches dépôts de minerai d'or à This, votre priorité étant de les exploiter."
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
            text: "La noblesse thinite poursuit ses efforts pour unir les terres du Nil sous un même administrateur suprême. Pour l'aider dans sa mission, vous devez développer une communauté prospère à Buto, dans la région humide du delta du Nil en Basse-Egypte. Vous étendrez ainsi l'influence de ces nobles sur l'ensemble du fleuve sacré. Pour administrer une population supérieure à celle d'un village, il vous faudra maîtriser les techniques de l'agriculture. @LLes fermiers égyptiens ont commencé à exploiter les grandes terres fertilisées par l'inondation annuelle du Nil en cultivant diverses plantes céréalières. Mais le Nil cache également bien des dangers. La menace rôde le long des rives ou au fond de ses eaux : des crocodiles féroces aux imposants hippopotames en passant par les moustiques porteurs de malaria."
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
            text: "Le premier pharaon",

        }
        content {
            text: "Tandis que les habitants des rives du Nil tentent tant bien que mal de survivre dans cet environnement hostile, un roi du nom de Narmer a pris le pouvoir. Bien que Narmer règne sur une grande partie du territoire, l'unification totale des deux royaumes reste à accomplir. En commémoration de son accession au trône, Narmer a désigné votre famille pour gouverner la nouvelle cité de Hierakonpolis. Vous devrez construire des temples en l'honneur des différents dieux égyptiens ainsi que divers lieux de divertissement."
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
            text: "Une capitale est née",

        }
        content {
            text: "Après des luttes acharnées, le roi Hor-Aha est parvenu à unir les deux royaumes de Haute et Basse-Egypte. Il devient ainsi le pharaon qui règne en maître absolu sur toute l'Egypte ! Pour démontrer et asseoir sa souveraineté, la première dynastie d'Egypte, Hor-Aha a ordonné la construction d'une grande capitale à Memphis, d'où il pourra gouverner son jeune pays. En raison des loyaux services rendus par votre famille depuis des générations au pays, le pharaon vous a désigné comme architecte de cette grande cité. Cette capitale sera le symbole de notre royaume et les habitants devront donc jouir d'un cadre de vie agréable, jusque-là inconnu dans la région. Pour cela, votre rôle sera d'établir des échanges commerciaux avec les autres cités du royaume et de proposer une éducation de qualité à une certaine catégorie de la population. Vous veillerez également à la construction d'un mastaba sacré dédié à la noblesse de la cité."
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
            text: "Expédition au Sinaï"
        }
        content {
            text: "Un nouveau pharaon, Den, vient d'accéder au trône d'Egypte. Il affiche de vives inquiétudes au sujet des frontières du pays, sous la menace croissante des ennemis. Notre pays connaît une pénurie de cuivre, métal nécessaire à la fabrication d'armes pour nos troupes. Le pharaon Den a ordonné une expédition minière dans le Sinaï, une terre hostile et lointaine en plein territoire bédouin. La région de Timna, d'aspect aride, regorge pourtant d'or et de minerai de cuivre, ainsi que de pierres précieuses comme la turquoise. Les conditions de vie y sont difficiles et vous devrez importer de nombreuses marchandises voire de la nourriture ou de la toile directement d'Egypte. Le pharaon s'attend à des livraisons régulières de devises, cuivre, pierres précieuses et armes du Sinaï. Vous pouvez utiliser ces marchandises pour garantir le bon déroulement de l'expédition. Soyez vigilant car les Bédouins du Sinaï sont de redoutables adversaires et ils ne laisseront pas des étrangers occuper impunément leur territoire pour y piller leurs richesses minières. @PPour améliorer les conditions de vie dans cette région aride, construisez un pavillon aux endroits très fréquentés. Les habitants pourront ainsi s'y détendre en assistant à des numéros de jonglerie ou des concerts. Vous pouvez également fonder une école de danse pour procurer encore davantage de plaisir à vos concitoyens."
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
            text: "L'armée navale du pharaon",
        }
        content {
            text: "Les troupes militaires égyptiennes dominent le monde civilisé, mais le nouveau pharaon, Khasekhemwy de la seconde dynastie, exige l'installation d'une armée navale puissante à Apollinopolis. Seule une flotte de navires de guerre serait en mesure de prendre le contrôle des océans. Mais le bois manque car les forêts sont peu abondantes sous notre climat. Le bois de cèdre peut être importé à grands frais de Byblos, une cité du Liban. Nos livraisons de papyrus permettent heureusement de compenser ces dépenses."
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
            text: "Le défi de la mer",

        }
        content {
            text: "Abydos, le sanctuaire de nos ancêtres, est devenu avec le temps une immense nécropole de tombes sacrées. De nombreux nobles souhaitent faire de ce lieu leur demeure pour le repos éternel. Le nouveau pharaon Khasekhemwy de la seconde dynastie a ordonné la construction de trois mastabas sacrés (dont un de taille supérieure aux deux autres) en l'honneur de la noblesse locale.  @L@LLe pharaon a ordonné la création d'une puissante armée navale dans la cité d'Apollinopolis. Abydos doit également accueillir quelques navires de guerre afin d'assurer la sécurité des cités côtières. La tâche risque d'être ardue. Nous vivons sous un climat aride, peu propice à l'exploitation des forêts et du bois. Le bois de cèdre peut être importé à grands frais de Byblos, une cité du Liban. Nos livraisons de papyrus permettent heureusement de compenser ces dépenses."
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
            text: "La route de l'Afrique",

        }
        content {
            text: "@PNebka a été proclamé premier pharaon de la troisième dynastie. Il a entrepris de profondes réformes structurelles en Egypte en ordonnant le partage du royaume en districts, appelés nomes, administrés par un nomarque. Bien que ce système puisse paraître rigide, l'Egypte est devenue sous son règne un pays prospère, notamment sur le plan architectural et artistique. @L@Ples caravanes de marchands qui voyagent d'oasis en oasis au coeur du continent africain, amènent en Egypte de nombreux produits rares et exotiques, très prisés par les populations locales. Ces convois sont malheureusement constamment attaqués par des guerriers libyens ou des Bédouins venant de l'est. Pour garantir la sécurité de ces voies commerciales, le pharaon Nebka, souverain du domaine du roseau et de l'abeille, vous demande d'établir un poste militaire dans l'oasis de Selima, un important lieu de passage des caravanes, situé bien au-delà des frontières du royaume.   @L@PLes quelques arbres qui s'y trouvent vous fourniront du bois dont la vente permettra d'entretenir cet avant-poste. Vous pourrez, grâce à la nouvelle mine de Timna au Sinaï, acheter du cuivre pour forger des armes. @L@PDans l'oasis de Selima, vous pourrez acheter de l'ébène aux marchands africains de Kerma. Une fois cet avant-poste établi, toutes les cités du royaume seront approvisionnées en ébène."
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
            text: "La frontière nubienne",

        }
        content {
            text: "@PNebka a été proclamé premier pharaon de la troisième dynastie. Il a entrepris de profondes réformes structurelles en Egypte en ordonnant le partage du royaume en districts, appelés nomes, administrés par un Nomarque. Bien que ce système puisse paraître rigide, l'Egypte est devenue sous son règne un pays prospère, notamment sur le plan architectural et artistique.   @PLe pharaon souhaite étendre la frontière sud du royaume vers la Nubie. Il a ordonné la construction d'une cité à la première cataracte du Nil, sur l'île d'Elephantine. Il s'agit d'un emplacement idéal car le sous-sol regorge de pierres précieuses, de granit et de grès.   @PCes matériaux font l'objet d'une grande demande de la part de la noblesse d'Abydos qui souhaite construire des monuments funéraires toujours plus élaborés dans la nécropole. Memphis, la capitale, a également besoin de briques pour la construction de tombes. Le pharaon Nebka commandera sûrement ces matériaux de construction.   @PLe pharaon Nebka a également ordonné à votre famille d'établir un poste militaire dans l'oasis de Selima afin de garantir la sécurité des caravanes de marchands en provenance des autres pays d'Afrique. Une fois établi, cet avant-poste constituera une source d'approvisionnement en ébène, un produit de luxe très recherché en Egypte."
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
            text: "La première pyramide",

        }
        content {
            text: "L'accession du pharaon Djoser au trône d'Egypte s'est accompagnée d'une période prospère faite de sagesse et d'importantes avancées sur le plan éducatif et artistique. La construction d'un cimetière royal est prévue sur le site de Saqqara pour servir de dernières demeures aux nobles comme Hezyre et Khabausokar, les plus fidèles courtisans du pharaon.   @PMais ce site devra également accueillir l'un des monuments les plus fabuleux que le monde ait jamais vu. Moi, Imhotep, vizir royal de Djoser, j'ai imaginé une nouvelle forme de tombe sacrée destinée au pharaon. Contrairement aux mastabas en terre des anciens pharaons, cette tombe s'élèvera vers le ciel comme plusieurs mastabas placés les uns sur les autres. Cette pyramide à degrés entièrement construite en pierre assurera la splendeur éternelle de notre souverain. L'édifice abritera un sarcophage de granit où le corps du pharaon reposera à jamais. @PLes prêtres de la nécropole d'Abydos ont amélioré les techniques de momification grâce à l'utilisation de toile pour embaumer les morts, ouvrant ainsi les portes de la vie éternelle à tous les Egyptiens.  @PNotre poste commercial dans l'oasis de Selima est en pleine croissance. Grâce à lui, nous pouvons importer de l'ébène d'Afrique.  @PLe pharaon vous a octroyé une importante somme d'argent pour mener à bien ce projet. Ne le décevez pas."
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
            text: "Le Bédouin de l'est",

        }
        content {
            text: "Comme Den, son prédécesseur, le pharaon Huni a ordonné une expédition dans le désert du Sinaï pour collecter des pierres précieuses et du cuivre. Il souhaite que vous preniez le commandement de l'expédition en direction de Serabit Khadim, un lieu où subsistent quelques vestiges d'un avant-poste égyptien. Nous ne connaissons pas l'état de ces ruines, mais elles pourront servir de refuge en cas d'attaque.   @PN'oubliez pas que la dernière expédition envoyée dans la région n'est jamais revenue. Nous n'avons également aucune nouvelle des hommes partis à sa recherche. Mais nos soldats ont besoin d'armes efficaces en cuivre, un métal rare dans notre royaume. @PSoyez vigilant car vous risquez à tout moment de tomber dans une embuscade préparée par les Bédouins du Sinaï ou nos ennemis cananéens. Récupérez autant de cuivre et de pierres précieuses que possible afin de satisfaire les exigences du pharaon. S'il vous reste des pierres précieuses, vous pouvez faire appel à des orfèvres afin qu'ils créent des bijoux pour les habitants de l'avant-poste."
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
            text: "Une nécropole royale",

        }
        content {
            text: "Le pharaon Huni désire reposer pour l'éternité dans une pyramide à degrés comme son prédécesseur Djoser. Il souhaite être entouré par les tombes de ses courtisans et a choisi la cité de Meidum, en Basse-Egypte, comme site de construction de la nécropole royale.   @PEn récompense des loyaux services offerts depuis des générations par votre famille, Huni vous donne le droit d'être enterré à Meidum, dans votre propre tombe. Ce geste honore ainsi toute votre famille. @PPour garantir la pérennité de la sagesse et des enseignements égyptiens, le pharaon Huni souhaite la construction de plusieurs bibliothèques royales. Les grandes familles de la noblesse pourront ainsi s'éduquer en consultant les nombreux papyrus que ces bâtiments abriteront.  @PLe pharaon a envoyé un autre de ses fidèles courtisans à Serabit Khadim, dans le désert du Sinaï, afin qu'il rapporte des pierres précieuses. Si cette expédition se déroule sans encombre, vous pourrez commencer l'importation de pierres précieuses en provenance de cette région. Les orfèvres peuvent également confectionner des bijoux de luxe destinés aux habitants de votre cité. @PLa cité d'Apollinopolis, jadis florissante, connaît un important déclin et n'exporte plus les marchandises qui faisaient sa renommée."
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
            text: "Invasion de la Nubie",

        }
        content {
            text: "Notre nouveau pharaon, Snofru, souhaite que la quatrième dynastie connaisse le plus grand règne de l'histoire égyptienne. Dans sa politique d'expansion au sud du royaume, il a décidé d'envahir la Nubie afin d'y construire une citadelle à Buhen, près de la deuxième cataracte du Nil. Vous devrez alors ériger un obélisque de granit pour montrer au reste du monde que cette région appartient désormais à l'Egypte et à son pharaon. Le granit étant absent de cette partie méridionale de l'Egypte, il vous faudra importer la roche depuis la cité d'Elephantine.   @PA Buhen, vous devrez affronter de féroces guerriers nubiens, qui se battront jusqu'à la mort pour empêcher la construction de cet avant-poste sur leur territoire. N'ayez crainte, après un entraînement rigoureux dispensé à l'académie militaire, vos soldats seront prêts au combat. Nos ingénieurs militaires ont par ailleurs mis au point différentes armes défensives telles que des tours fortifiées, des murs et des corps de garde. Ces dispositifs serviront à repousser les attaques de l'armée nubienne. Vous pouvez, le cas échéant, utiliser des navires de transport de troupes pour amener rapidement vos soldats sur le lieu des combats.  @PAu nord, nous avons établi des relations commerciales avec la cité d'Enkomi, sur l'île de Chypre. Cette région est réputée pour ses réserves en minerai de cuivre, un métal dont nous faisons une grande consommation. Grâce à l'installation d'une exploitation minière à Serabit Khadim, dans le désert du Sinaï, nous sommes cependant en mesure d'importer du cuivre à un prix bien inférieur. Mais l'exploitation de Serabit Khadim est régulièrement prise pour cible par les Bédouins et les Cananéens, et nous craignons que les forces égyptiennes sur place ne puissent contenir ces attaques répétées.  @PUn somptueux monument funéraire dédié au pharaon est actuellement en cours de construction sur le site de Dahshur. Pour mener ce projet à terme, le pharaon vous demandera de veiller à l'approvisionnement du site en blocs de calcaire."
        }
    }
    message_mission_south_dahshur {
        id: 414,
        type: 3,
        size [40, 30]
        title {
            text: "Sud de Dahshur",

        }
        subtitle {
            text: "La pyramide penchée de Snofru",

        }
        content {
            text: "@PNotre nouveau pharaon, Snofru, souhaite que la quatrième dynastie connaisse le plus grand règne de l'histoire égyptienne. Ses architectes ont imaginé une tombe encore plus spectaculaire que la pyramide de Huni et le pharaon souhaite que vous supervisiez les travaux. Il vous faudra définir l'emplacement idéal pour la construction du monument, dans la partie sud de Dahshur, la cité où sera érigée la pyramide penchée du pharaon. La ville fournira la main-d'oeuvre nécessaire à la réalisation de cet ambitieux projet. @PLa pyramide penchée sera construite en pierre et recouvertes de blocs de calcaire blanc afin qu'elle puisse briller pour l'éternité sous le soleil du désert. Vous disposez de réserves suffisantes en calcaire à Dahshur, mais les blocs de pierre devront être importés. @PLe pharaon souhaite étendre nos frontières au sud du pays. Pour cela, il a ordonné à ses troupes d'envahir la Nubie afin d'y construire une citadelle à Buhen, près de la deuxième cataracte du Nil. @PAu nord, l'Egypte a établi des relations commerciales avec la cité d'Enkomi, sur l'île de Chypre. Cette région est réputée pour ses réserves en minerai de cuivre, l'une de nos principales importations.  @PLe nouvel avant-poste de Serabit Khadim, dans le désert du Sinaï fournit une importante quantité de pierres précieuses. Nous avons connu récemment des problèmes d'approvisionnement en raison d'incessantes attaques de la part des Bédouins et des Cananéens, et nous craignons que les forces égyptiennes sur place soient bientôt débordées."
        }
    }
    message_mission_north_dahshur {
        id: 415,
        type: 3,
        size [40, 30]
        title {
            text: "Nord de Dahshur",

        }
        subtitle {
            text: "La vraie pyramide",

        }
        content {
            text: "@PLe pharaon Snofru a ramené l'ordre et la paix en Egypte, et le royaume prospère désormais sous ses sages conseils. Snofru souhaite construire un autre monument sur le site de Dahshur, encore plus ambitieux que la pyramide penchée qui vient d'être achevée. Les architectes, conseillers et ingénieurs royaux pensent être en mesure de concevoir un édifice dont les faces s'élèveraient harmonieusement pour former un sommet parfait. S'ils y parviennent, l'Egypte assistera à la naissance de la première vraie pyramide, le tombeau éternel du grand pharaon Snofru !    @PL'épouse du pharaon, la reine Hetehpheres, vient de mettre au monde un fils du nom de Koufou. Notre peuple redoute l'arrivée au pouvoir de cet enfant car, d'après les prédictions d'Horus, Dieu du pharaon, il n'héritera pas de la bienveillance dont à témoigné son père envers le peuple d'Egypte. Le futur pharaon réalisera sans doute de grands projets, mais les habitants craignent que l'Egypte ne se retrouve étouffée sous le joug d'un tyran.  @PIl vous faudra importer du bois de la cité de Byblos, car les charpentiers devront construire des rampes pour permettre aux ouvriers d'acheminer les blocs de pierre au sommet de la grande pyramide."
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
            text: "La défense de l'Egypte",

        }
        content {
            text: "@PLe pharaon Koufou vient d'accéder au trône d'Egypte et, comme le prédisaient les oracles d'Horus et de Rê, notre peuple ressent déjà l'oppression de sa politique.  @PKoufou a ordonné l'envoi d'un gouverneur du royaume à Dendera, afin de défendre notre pays contre les envahisseurs éthiopiens. La cité de Dendera possède une petite industrie de pêche, qui devrait permettre de nourrir les habitants pendant quelques temps. En cas d'invasion par la mer, les bateaux de pêche risquent d'être attaqués. Il est donc préférable de réserver les rivages aux navires de guerre. Si la nourriture vient à manquer, le bétail fournira de la viande, bien que les troupeaux consomment une importante quantité de paille et que cette ressource soit rare dans la région. Cette paille étant également nécessaire à la confection de briques pour les mastabas, vous devez établir des relations commerciales avec d'autres cités productrices de ce matériau. @PLa cité de Byblos au Liban, le pays des cèdres, a entamé des échanges commerciaux avec les puissants empires d'Orient. Ces pays, l'Assyrie et l'Ur, forment une région appelée Mésopotamie, située entre deux grands fleuves, qui fournit à Byblos un ivoire d'une qualité exceptionnelle. Avec des marchandises d'une telle valeur, la cité de Dendera est assurée de connaître une longue prospérité. @PLes habitants de la capitale se divertissent avec un nouveau jeu appelé senet. Les joueurs de senet aiment se réunir autour d'une cruche de bière dans une taverne de jeux. Ces établissements permettent aux habitants de Dendera d'oublier pendant quelques temps la tyrannie du pharaon Koufou. @PLe pharaon a ordonné la mise en place de nombreuses carrières sur le site d'Heliopolis, dans le delta du Nil, afin d'extraire assez de calcaire pour ses futurs projets. Seuls les dieux connaissent les desseins du pharaon. On raconte qu'il envisage la construction d'un monument colossal sur le plateau situé à l'extérieur de la cité de Giza."
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
            text: "L'ivoire de l'est",

        }
        content {
            text: "@PLe pharaon Koufou vient d'accéder au trône d'Egypte et, comme le prédisaient les oracles d'Horus et de Rê, notre peuple ressent déjà l'oppression de sa politique. On raconte qu'il envisage la construction d'un monument colossal sur le plateau situé à l'extérieur de la cité de Giza. Il souhaiterait, grâce à cet édifice, connaître une plus grande gloire que son père, le sage et bienveillant pharaon Snofru, dont les deux nobles pyramides avaient fait la renommée.  @PLe pharaon Koufou a ordonné l'excavation de plusieurs carrières à Tura, dans le delta du Nil, où a récemment été découvert un important gisement de calcaire. Vous devez également construire trois mastabas pour la noblesse de la région, afin que le pharaon puisse honorer leur dévotion. Le gisement portera le nom de 'Heliopolis' et devra fournir un excellent calcaire pendant de longues années... seuls les dieux ont connaissance de l'usage que le pharaon fera de ce calcaire. @PLa cité de Byblos au Liban, le pays des cèdres, a entamé des échanges commerciaux avec les puissants empires d'Orient. Ces pays, l'Assyrie et l'Ur, forment une région appelée Mésopotamie, située entre deux grands fleuves, qui fournit à Byblos un ivoire d'une qualité exceptionnelle. Avec des marchandises d'une telle valeur, la cité d'Heliopolis est assurée de connaître une longue prospérité. @PKoufou a également envoyé un gouverneur du royaume dans la cité de Dendera afin de défendre notre pays contre les envahisseurs éthiopiens. Les vizirs n'envient guère la position du gouverneur car cette mission s'annonce très périlleuse.  @PLes habitants de la capitale se divertissent avec un nouveau jeu appelé senet. Les joueurs de senet aiment se réunir autour d'une cruche de bière dans une taverne de jeux. Ces établissements permettant aux habitants de Dendera d'oublier pendant quelques temps la tyrannie du pharaon Koufou."
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
            text: "La Grande Pyramide et le Sphinx",

        }
        content {
            text: "Le pharaon Koufou a enfin fait connaître ses desseins et ses sujets risquent de payer cher sa soif de conquête. Malgré sa tyrannie, le pharaon respecte votre famille puisqu'il vous a donné le titre de nomarque. Il vous a également désigné comme responsable du plus grand projet de construction jamais entrepris dans le royaume.   @PLa demeure éternelle du pharaon aura la forme d'une imposante pyramide et sera située à l'écart de la cité, sur le plateau de Giza. Son sarcophage sera taillé dans du granit, posé sur une barque funéraire en cèdre du Liban. A côté de cette pyramide, une autre pyramide plus petite sera construite en l'honneur du prince Khafra, un nomarque aussi tyrannique que son père, mais encore loin de l'égaler sur le plan des oeuvres accomplies. Khafra a également exigé que son effigie soit gravée dans la roche de Giza, sous la forme d'un sphinx, un animal fantastique avec un corps de lion et un visage humain. @PPour permettre la construction de cet immense édifice, il vous faudra mettre en place un site de construction à Giza. Vous devrez vous concentrer sur la réalisation de ces trois projets tout en honorant le pharaon.   @PLe pharaon vous enverra les blocs de calcaire servant à recouvrir les pyramides, mais il vous faudra acheter le reste des matériaux de construction à l'aide des recettes de la cité. @PLe pharaon vous a choisi parmi tous ses nomarques royaux pour réaliser ces trois travaux sacrés. Vous devrez montrer votre dévouement envers le pharaon et satisfaire ses exigences... quel qu'en soit le prix."
        }
    }
    message_mission_bahariya_oasis {
        id: 419,
        type: 3,
        size [40, 30]
        title {
            text: "L'oasis de Baharièh",

        }
        subtitle {
            text: "Le désert occidental",

        }
        content {
            text: "@PLes règnes de Koufou et Khafra se sont éteints, entraînant la fin de la quatrième dynastie des pharaons d'Egypte. Mais une parente éloignée de la famille, Khentkaues, a donné naissance à un nouveau pharaon prénommé Ouserkaf. La grande lignée des pharaons peut ainsi perdurer. Ouserkaf est le premier souverain d'une cinquième dynastie qui annonce une ère d'importants bouleversements.   @POuserkaf s'est lancé dans la voie de la décentralisation en accordant plus de pouvoir aux autorités locales. En tant que nomarque, vous pouvez diriger votre cité comme vous l'entendez. Le pharaon ne souhaite entreprendre aucune construction de tombeau funéraire car il a actuellement un autre projet à vous soumettre. @PLe pharaon a désigné Rê, le dieu du soleil et du royaume, roi des dieux et il entend proclamer sa souveraineté dans tout le pays. L'Egypte possède de nombreux temples du soleil, mais le pharaon souhaite étendre l'influence de Rê aux confins du royaume. @PPour cette tâche, vous devez construire une citadelle sur l'oasis de Baharièh, au coeur du désert occidental. Utilisez l'eau avec parcimonie car cette ressource, très rare dans une région aussi éloignée du Nil, est convoitée par les animaux sauvages qui rôdent dans le désert. Méfiez-vous également des guerriers libyens et des Bédouins qui attaquent sans relâche les caravanes de nomades. Organisez votre défense et utilisez les ressources disponibles (bois et gibier) de l'oasis."
        }
    }
    message_mission_abusir {
        id: 420,
        type: 3,
        size [40, 30]
        title {
            text: "Abousir",

        }
        subtitle {
            text: "Le temple du soleil",

        }
        content {
            text: "@PLes règnes de Koufou et Khafra se sont éteints, entraînant la fin de la quatrième dynastie des pharaons d'Egypte. Mais une parente éloignée de la famille, Khentkaues, a donné naissance à un nouveau pharaon prénommé Ouserkaf. La grande lignée des pharaons peut ainsi perdurer. Ouserkaf est le premier souverain d'une cinquième dynastie qui annonce une ère d'importants bouleversements.   @POuserkaf s'est lancé dans la voie de la décentralisation en accordant plus de pouvoir aux autorités locales. En tant que nomarque, vous pouvez diriger votre cité comme vous l'entendez. Le pharaon ne souhaite entreprendre aucune construction de tombeau funéraire car il a actuellement un autre projet à vous soumettre. @PLe pharaon a désigné Rê, le dieu du soleil et du royaume, roi des dieux et il entend proclamer sa souveraineté dans tout le pays. L'Egypte possède de nombreux temples du soleil, mais le pharaon souhaite construire un immense temple à Abousir, dans la région humide du delta du Nil, en Basse-Egypte. @PLa région d'Abousir, comme la majeure partie du delta, regorge de gibier, poissons et autres animaux sauvages. La végétation y est également luxuriante mais les ressources minérales restent faibles. Pour cette raison, le grès nécessaire à la construction du temple du soleil doit être amené depuis les carrières d'Heliopolis. Vous pouvez élever du bétail et obtenir ainsi de la viande, mais les troupeaux consomment une grande quantité de fourrage. @PIl vous faudra défricher l'emplacement choisi pour la construction du temple du soleil. Pensez à vendre autant de bois que possible. Les cités d'Apollinopolis et d'Abydos manquent continuellement d'eau et de gibier. Vous pouvez par conséquent leur vendre ces marchandises afin de réduire les coûts de construction du monument sacré."
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
            text: "La menace éthiopienne",

        }
        content {
            text: "@PLe pharaon Pépi vient d'accéder au trône d'Egypte. En raison des bons et loyaux services rendus par votre famille, vous voilà devenu chancelier. Ce règne exceptionnel de 94 ans, le plus long de toute l'histoire, a pourtant laissé des traces douloureuses dans la vie des Egyptiens. Le pouvoir central perd peu à peu de son autorité au profit des administrations locales. Certaines régions ont eu de mauvaises récoltes et le spectre de la famine commence à planer sur toute l'Egypte. Memphis, une cité jadis resplendissante, connaît un lent et inexorable déclin et les oracles sont très pessimistes pour l'avenir... @PNos puissants voisins cherchent à profiter de la situation de faiblesse dans laquelle est plongé le royaume. L'avant-poste de Buhen a été assiégé par les soldats éthiopiens de Kerma, la plus grande ville non égyptienne d'Afrique. Ils exigent un tribut et se montreront impitoyables à la moindre provocation. La Nubie a également déclaré la guerre à notre pays et cherche à récupérer les terres annexées par l'Egypte.  @PPour éviter que le royaume ne s'asphyxie, vous devez tout faire pour préserver les routes commerciales permettant aux marchandises d'entrer et de sortir d'Egypte. Veillez en particulier au bon fonctionnement de l'avant-poste situé dans l'oasis de Selima. Le pharaon Pépi, en prévision de son voyage vers l'au-delà, vous demandera une grande quantité de pierres pour la construction de sa pyramide. D'autres cités, en pénurie de nourriture, chercheront également à obtenir votre aide. @PSachez utiliser les différentes ressources disponibles. L'oasis peut fournir une grande quantité de bois, mais vous devrez défricher la forêt pour avoir accès aux rares points d'eau."
        }
    }
    message_mission_dakhla {
        id: 422,
        type: 3,
        size [40, 30]
        title {
            text: "Dakhlèh",

        }
        subtitle {
            text: "La caravane",

        }
        content {
            text: "@PLe pharaon Pépi vient d'accéder au trône d'Egypte. En raison des bons et loyaux services rendus par votre famille, vous voilà devenu chancelier. Ce règne exceptionnel de 94 ans, le plus long de toute l'histoire, a pourtant laissé des traces douloureuses dans la vie des Egyptiens. Le pouvoir central perd peu à peu de son autorité au profit des administrations locales. Certaines régions ont eu de mauvaises récoltes et le spectre de la famine commence à planer sur toute l'Egypte. Memphis, une cité jadis resplendissante, connaît un lent et inexorable déclin et les oracles sont très pessimistes pour l'avenir...  @PNos puissants voisins cherchent à profiter de la situation de faiblesse dans laquelle est plongé le royaume. L'avant-poste de Buhen a été assiégé par les soldats éthiopiens de Kerma, la plus grande ville non égyptienne d'Afrique. Ils exigent un tribut et se montreront impitoyables à la moindre provocation. La Nubie a également déclaré la guerre à notre pays et cherche à récupérer les terres annexées par l'Egypte.  @PEssayez de conserver la stabilité de l'Egypte en établissant un poste administratif dans l'oasis de Dakhlèh. Cette oasis possède un large éventail d'arbres précieux, mais ceux-ci bloquent malheureusement l'accès à l'étendue d'eau. A partir de cette oasis, vous devez importer de l'ébène en provenance du centre de l'Afrique. Le pharaon Pépi, en prévision de son voyage vers l'au-delà, vous demandera une grande quantité de pierres pour la construction de sa pyramide. D'autres cités, en pénurie de nourriture, chercheront également à obtenir votre aide."
        }
    }
    message_mission_thinis {
        id: 423,
        type: 3,
        size [40, 30]
        title {
            text: "This",

        }
        subtitle {
            text: "Guerre civile",

        }
        content {
            text: "Le bon vieux temps désormais n'est plus et nombreuses sont les personnes qui craignent que l'Egypte ne retrouve jamais sa gloire passée. Osiris a abandonné le peuple et de faibles crues ont engendré une famine terrible. Les pharaons, autrefois tout puissants, ont cédé la place à des administrateurs provinciaux qui ne cessent de se chamailler. @PDe ce chaos ont émergé deux familles issues de la noblesse qui se battent pour prendre le contrôle du pays. Particulièrement cruelle et peu soucieuse de la famine touchant le peuple, la famille des Herakleopolis se présente comme l'héritière directe du trône. Au sud du pays, se trouve la nouvelle famille des Inyotef. Cette famille qui a beaucoup fait pour réunifier le sud, possède un certain pouvoir à Thèbes. Mais aujourd'hui, Thèbes est ravagé par une violente guerre civile fomentée par les Herakleopolis et visant le contrôle de toute l'Egypte. @PPour prouver leur générosité au peuple égyptien, les Inyotef vous ont confié la reconstruction de la cité nouvellement conquise de This, l'une des plus anciennes cités d'Egypte. Deux des bâtiments les plus anciens et les plus raffinés de This ont survécu à la prise de la ville : le temple d'Osiris et la demeure royale. Les Inyotef ont assuré que si l'un de ces bâtiments devait être détruit, aucun fonds ne serait accordé pour leur reconstruction. Les administrateurs de Thèbes, quant à eux, considèrent la restauration de This comme une priorité et des fonds considérables sont rassemblés dans ce but, même en cette période de diète. Ramenez This à sa splendeur passée, puis affrétez un navire et faites lever une puissante armée pour défendre la cité contre les fréquentes attaques des soldats vouant allégeance à la famille Herakleopolis ou contre celles de Lykopolis, de Hierakonpolis et de Hermopolis. Prenez garde, car ils pourraient exiger un tribut dans le but de tester votre loyauté et par la même occasion vous extorquer quelques debens. Soyez également vigilant envers les Ethiopiens qui sont prêts à tirer profit des luttes intestines égyptiennes pour fondre sur le pays."
        }
    }
    message_mission_thebes {
        id: 424,
        type: 3,
        size [40, 30]
        title {
            text: "Ouaset",

        }
        subtitle {
            text: "Guerre civile",

        }
        content {
            text: "Le bon vieux temps désormais n'est plus et nombreuses sont les personnes qui craignent que l'Egypte ne retrouve jamais sa gloire passée. Osiris a abandonné le peuple et de faibles crues ont engendré une famine terrible. Les pharaons, autrefois tout puissants, ont cédé la place à des administrateurs provinciaux qui ne cessent de se chamailler. @PDe ce chaos ont émergé deux familles issues de la noblesse qui se battent pour prendre le contrôle du pays. Particulièrement cruelle et peu soucieuse de la famine touchant le peuple, la famille des Herakleopolis se présente comme l'héritière directe du trône. Au sud du pays, se trouve la nouvelle famille des Inyotef. Cette famille qui a beaucoup fait pour réunifier le sud, possède un certain pouvoir à Thèbes. Mais aujourd'hui, Thèbes est ravagé par une violente guerre civile fomentée par les Herakleopolis et visant le contrôle de toute l'Egypte. @PLes Inyotef qui combattent actuellement les Herakleopolis, vous ont confié la reconstruction de leur cité mère, Thèbes. Si les Inyotef remportent le combat contre les Herakleopolis, assoyant ainsi leur réputation dans toute l'Egypte, Thèbes deviendra alors la pierre angulaire vers laquelle les autres cités se tourneront, accordant aide à tous ceux qui feront appel à elle. Thèbes, qui en cas de victoire des Inyotef deviendra leur capitale, se doit d'être une grande cité. A l'aide des quelques ressources encore disponibles, construisez un temple solaire et une pyramide pour montrer aux Egyptiens la gloire des Inyotef. @PThèbes n'est pas non plus à l'abri des attaques. Les Herakleopolis et leurs loyaux serviteurs menacent votre cité de temps à autre, essayant d'extorquer quelques debens de son trésor. Pour soustraire Ouaset à ces risques, levez une puissante armée de terre et affrétez une flotte qui défendra votre cité, ainsi que les autres cités menacées."
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
            text: "Réunification",

        }
        content {
            text: "La fidélité de votre famille durant la guerre civile n'aura pas été vaine. En tant que pharaon Mentuhotep, je confère à votre famille le titre de vizir. Nul autre que vous ne peut se vanter d'avoir mon entière confiance. Maintenant que les royaumes de la Basse- et Haute-Egypte sont réunifiés et que la capitale de Thèbes est florissante, vous devez m'aider à asseoir ma position dans le royaume. @PBien que réunifiée, l'Egypte est aux prises à des querelles intestines, notamment dans les territoires autrefois régis par les Herakleopolis. Pour aider à la pérennité de notre nouvelle union, vous devez reconstruire, puis défendre Coptos. Cette cité devra être glorieuse, car elle sera le reflet des bienfaits réalisés sous mon règne. La cité étant soumise à de fréquentes attaques de la part des cités loyalistes, comme Hermopolis, apprêtez-vous à la défendre. @PLa famine touchant l'ensemble du pays, de nombreuses requêtes provenant des autres cités du royaume vous parviennent. Répondez le plus rapidement possible à ces demandes afin que ma générosité et la dévotion de mon très dévoué vizir soient connues dans toute l'Egypte. @PJe sais que je vous en demande beaucoup, mais vous êtes le seul à pouvoir accomplir une telle tâche."
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
            text: "Réunification",

        }
        content {
            text: "La fidélité de votre famille durant la guerre civile n'aura pas été vaine. En tant que pharaon Mentuhotep, je confère à votre famille le titre de vizir. Nul autre que vous ne peut se vanter d'avoir mon entière confiance. Maintenant que les royaumes de la Basse- et Haute-Egypte sont réunifiés et que la capitale de Thèbes est florissante, vous devez m'aider à asseoir ma position dans le royaume. @PBien que réunifiée, l'Egypte est aux prises à des querelles intestines, notamment dans les territoires autrefois régis par les Herakleopolis. Pour aider à la pérennité de notre nouvelle union, vous devez reconstruire, puis défendre Beni Hasan. Cette cité devra être glorieuse, car elle sera le reflet des bienfaits réalisés sous mon règne. La cité étant soumise à de fréquentes attaques de la part des cités loyalistes, comme Khnoum, apprêtez-vous à la défendre. @PLa famine touchant l'ensemble du pays, de nombreuses requêtes provenant des autres cités du royaume vous parviennent. Répondez le plus rapidement possible à ces demandes afin que ma générosité et la dévotion de mon très dévoué vizir soient connues dans toute l'Egypte. @PJ'ai une seconde noble tâche à vous confier. Je désire que vous fassiez ériger des obélisques en granit comme symbole de mon entière dévotion pour ce pays au cours de mon passage terrestre. @PJe sais que je vous en demande beaucoup, mais vous êtes le seul à pouvoir accomplir une telle tâche."
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
            text: "Une nouvelle capitale est née",

        }
        content {
            text: "O puissant pharaon, fils de Rê, comme vous devez être heureux. Votre ascension fulgurante au trône d'Egypte est un miracle ! Plus belle récompense ne pourrait être envisagée par les dieux ou le peuple. Grâce à l'accession au trône de votre famille, l'Egypte va prendre désormais un nouveau départ, et peut-être arriverons-nous à oublier les horreurs de la guerre civile. @PPour marquer cette nouvelle ère, vous devez construire une capitale d'un grand raffinement. Avec des ressources naturelles en abondance, Itjtawy est un endroit parfait. En tirant profit des richesses de la région, vous pouvez construire une cité merveilleuse à la hauteur de la valeur et du dévouement de votre dynastie. @PAfin que les bienfaits sous votre grande dynastie restent à jamais dans les mémoires, vous devez construire deux majestueuses pyramides en briques pour vous-même et votre famille, ainsi qu'un sphinx redoutable qui gardera votre tombe. Une famille telle que la vôtre ne mérite pas moins. @PGardez à l'esprit, cependant, que certaines personnes dans le pays remettent en cause votre légitimité. Un grand nombre d'entre eux souffrent encore des effets de la famine et murmurent que vous avez usurpé le trône. Si vous soulagez le peuple de ses misères et que vous l'aidez à reconstruire ses maisons, vous gagnerez certainement son allégeance éternelle. Vous devez prévenir et résoudre les problèmes de vos sujets si vous ne voulez pas que ceux-ci prennent les armes contre vous."
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
            text: "Dans la Nubie",

        }
        content {
            text: "Maintenant que l'Egypte est enfin unifiée sous votre règne, l'ensemble de votre cour et moi-même, vote fidèle vizir, vous recommandons d'agrandir les frontières de notre pays vers le sud de la Nubie. Les rives asséchées du fleuve de Allaqi riches en or et l'imposante cité de Mirgissa, qui abrite votre résidence, décourageront certainement les Nubiens de toute attaque. Prenez garde aux Ethiopiens cependant. Ce sont des adversaires bien plus dangereux que les Nubiens et ils n'hésiteront pas à utiliser l'épée, O pharaon, pour vous faire quitter vos terres. @PPour laisser une empreinte durable dans la Nubie, vous devez construire un imposant obélisque, signe de la toute puissance de l'Egypte. L'obélisque sera la preuve évidente pour les Nubiens de la grandeur du règne égyptien. En outre, il restera un rappel constant de notre présence. @PAlors que vous vous concentrez sur Mirgissa, gardez à l'esprit notre intention de créer une cité côtière ouvrant sur la mer Rouge à Mersa Gawasis. Cette cité aura besoin de l'aide du pharaon et n'hésitera pas à faire appel à lui. Si Mersa Gawasis prospère, elle pourra fournir Mirgissa en cuivre pour forger des armes."
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
            text: "Sur les côtes de la mer Rouge",

        }
        content {
            text: "Maintenant que l'Egypte est enfin unifiée sous votre règne, nous devons développer le commerce avec d'autres cités dans le monde entier afin d'asseoir la croissance de l'Egypte, O roi des Deux Pays. @PAu fur et à mesure que votre peuple prospère, il demande de plus en plus de biens exotiques. Lassé par les bijoux, articles de luxe certes mais acquis trop facilement, votre peuple veut désormais des articles de luxe chers et rares, tel l'encens. Votre cour et moi-même, votre fidèle vizir, nous vous recommandons de créer un port à Mersa Gawasis au bord de la mer Rouge et d'ouvrir une route commerciale avec la contrée lointaine de Punt, d'où l'encens le plus fin au monde peut être importé à des prix très élevés. @PEn plus de modestes veines de minerai d'or et de cuivre, Mersa Gawasis exploite également quelques matières premières et pourrait évoluer vers la fabrication de produits finis. Grâce à l'exportation des produits finis et à l'importation de matières premières en provenance des partenaires commerciaux, Mersa Gawasis devrait pouvoir générer un certain profit. @PTandis que vous vous afférez à Mersa Gawasis, l'un des nomarques les plus vaillants met en place un nouveau carrefour commercial en Nubie. Sa cité, Mirgissa, a de fortes chances d'être attaquée, par conséquent, préparez-vous à lui envoyer des renforts. @PSous votre règne, Mersa Gawasis est assuré de devenir l'une des cités les plus belles du royaume et elle semble toute désignée pour vous abriter vous et votre famille. Lorsque vous créerez le port, ne négligez pas les préparatifs pour votre passage vers l'au-delà. Un mausolée et une petite pyramide en briques offriront à votre famille et à vous-même des quartiers somptueux après votre passage dans l'au-delà."
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
            text: "Le gantelet",

        }
        content {
            text: "Tout puissant pharaon, les biens et territoires protégés par votre famille sont aujourd'hui menacés ! La flotte nubienne est partout sur le Nil, s'autorisant même des incursions au coeur du territoire égyptien, pillant villages et cités. En outre, les Nubiens n'hésitent pas à accoster vos navires marchants... Pour aider les cités se trouvant au nord du pays à repousser l'ennemi, vous devez envoyer des navires de guerre et des soldats aux cités en détresse.  @PPour empêcher les Nubiens de patrouiller dans vos eaux, vos conseillers militaires vous recommandent de construire un ensemble de forts à Semna entre la deuxième et la troisième cataractes du Nil. Les forts serviront à empêcher les Nubiens de descendre vers le sud du pays. @PAprès avoir repoussé les Nubiens, vous devrez conquérir la cité riche en ressources de Kuban. La prise de cette cité pénalisera énormément l'économie nubienne. Une fois Kuban repris aux Nubiens, vous commencerez à importer du grès à partir de cette cité pour votre immense mausolée. Celui-ci rappellera aux Nubiens votre toute puissance.  @PDe nombreux défis vous attendent si vous souhaitez protéger l'Egypte des Nubiens. Prenez garde, O Grand Horus, à l'orage qui gronde à l'est. Le bruit assourdissant des sabots des chevaux se répercute dans tout Canaan et des chars rapides comme l'éclair dévastent tout sur leur passage. Ces effroyables chars, de ceux que vous n'avez encore jamais vus, sont conduits par les guerriers Hyksos. Déjà, des nuages noirs s'accumulent dans l'horizon égyptien et vous devrez vous armer de courage pour faire face à cet effroyable danger."
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
            text: "La cité de Bastet",

        }
        content {
            text: "Tout puissant pharaon, grâce aux routes commerciales en place, nous devrions désormais pouvoir montrer à l'Egypte les bienfaits du succès et de la richesse. Bubastis est l'endroit idéal pour une telle cité : nous pouvons protéger nos routes commerciales à l'est tout en rendant hommage à Bastet, le protecteur de l'Egypte. @PLa cité de Bastet devra être comme aucune autre en Egypte. Elle devra être aussi resplendissante qu'une fleur de lotus et fleurira de lieux de loisirs, d'écoles, de bibliothèques et de lieux de culte. Ses citoyens bénéficieront de l'importation des articles les plus raffinés, tel l'encens. Une fois terminé, Bubastis sera le joyaux des deux couronnes. @PTout en construisant cette glorieuse cité, prenez garde à l'orage qui gronde à l'est. Le bruit assourdissant des sabots des chevaux se répercute dans tout Canaan et des chars rapides comme l'éclair dévastent tout sur leur passage. Ces effroyables chars, de ceux que vous n'avez encore jamais vus, sont conduits par les guerriers Hyksos. Déjà, des nuages noirs s'accumulent dans l'horizon égyptien et vous devrez vous armer de courage pour faire face à cet effroyable danger."
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
            text: "Appel à l'aide",

        }
        content {
            text: "Très puissant pharaon, l'Egypte réclame votre aide. Les terribles guerriers Hyksos ont envahi nos terres et ont établi leur propre capitale à Havaris. A partir de cette cité, ils ont réussi à détourner plusieurs de nos voies commerciales, nous privant de denrées nécessaires. Nous devons mettre un terme à leur conquête avant qu'il ne soit trop tard. @PSi vous l'ordonnez, O Grand pharaon, nous irons leur reprendre la cité de Hermopolis. Nous devons également préparer une flotte ainsi qu'une puissante armée, car nos compatriotes qui se trouvent au nord, et tout particulièrement à Havaris, auront certainement besoin de renfort pour repousser l'incursion des guerriers Hyksos. Ils demanderont votre protection, O fils de Rê. En outre, nous possédons désormais une nouvelle arme. Nos chefs militaires ayant appris à se servir du terrible char, nous devrions pouvoir l'utiliser contre nos ennemis. Une fois les guerriers Hyksos repoussés hors du pays, nos conseillers militaires recommandent la construction d'un fort dans le Sinaï à Sharuhen pour prévenir de futures invasions par l'est. @PSi seulement nos problèmes pouvaient se limiter au nord ! Des rapports provenant de la frontière sud montrent que les Nubiens ont une fois de plus profité des tiraillements de l'Egypte. Ils se sont emparés des cités de Mirgissa et de Semna au sud du pays. Bien que ces cités soient sources de problèmes, nous devons d'abord repousser les guerriers Hyksos avant de nous concentrer sur le sud du pays. @PCes guerriers Hyksos sont des envahisseurs impies, car ils n'ont pas hésité à profaner la pyramide de Hermopolis, volant au tout puissant pharaon les biens nécessaires au passage vers l'au-delà."
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
            text: "Appel à l'aide",

        }
        content {
            text: "O roi des Deux Pays, l'Egypte réclame votre aide. Les terribles guerriers Hyksos ont envahi nos terres et ont établi leur propre capitale à Havaris. A partir de cette cité, ils ont réussi à détourner plusieurs de nos voies commerciales, nous privant de denrées nécessaires. Nous devons mettre un terme à leur conquête avant qu'il ne soit trop tard. @PA Lykopolis, nous sommes à l'abri d'une attaque immédiate, bien que les guerriers Hyksos osent nous demander un tribut. Nous avons besoin de fournir des troupes et des armes à nos compatriotes qui se trouvent au nord, pour les aider à repousser l'incursion de ces guerriers. Ils comptent sur votre assistance, O Grand pharaon. En outre, nous possédons désormais une nouvelle arme. Nos chefs militaires ayant appris à se servir du terrible char, nous devrions pouvoir l'utiliser contre nos ennemis. @PSi seulement nos problèmes pouvaient se limiter au nord ! Des rapports provenant de la frontière sud montrent que les Nubiens ont une fois de plus profité des tiraillements de l'Egypte. Ils se sont emparés des cités de Mirgissa et de Semna au sud du pays. @PPour que l'Egypte réussisse à sortir intacte de cette période tumultueuse, vos généraux vont devoir mettre les bouchées doubles sur terre comme sur le fleuve. Pour encourager vos deux meilleurs généraux, vous avez promis de construire pour chacun d'eux une pyramide aussi spectaculaire que la vôtre. Fort de cette promesse, ceux-ci combattent vaillamment l'ennemi, puisant au fond d'eux la force et la vigueur nécessaires à la victoire. @PSi vous l'ordonnez, Grand pharaon, nous construirons trois pyramides magnifiques à Lykopolis, l'une pour vous-même et les deux autres pour vos généraux. Ces trois pyramides nécessitant une place considérable, vous devrez renoncer à de précieuses ressources. Vous aurez également  besoin d'étendre votre cité de l'autre côté du Nil pour profiter des ressources nécessaires à son épanouissement."
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
            text: "Expansion et conquête",

        }
        content {
            text: "L'Egypte est sortie plus forte de cette période tumultueuse. Byblos, avec ses forêts verdoyantes et ses riches sources de cuivre, est désormais nôtre ! Grâce à votre présence, la cité prospèrera et un nouveau royaume verra le jour. @PCependant, suite à la conquête de Byblos, nous avons fait une terrible découverte ! Un nouveau peuple, particulièrement féroce, les Hittites, ont conquis la plus grande partie de l'Asie et certains disent que leur empire rivaliserait en taille avec le nôtre. Ce peuple montre désormais un intérêt vivace pour Byblos et notamment pour ses richesses. Si nous ne nous préparons pas à leur attaque, nous aurons quelques difficultés à les repousser. @PTout en nous préparant à affronter les Hittites, nous devons marquer Byblos à jamais de notre empreinte. Avec votre accord, O pharaon, nous érigerons trois obélisques, un grand et deux petits, pour proclamer votre souveraineté et votre gloire à travers tout votre royaume. Ces monuments rappelleront aux habitants de Byblos qu'ils doivent vous être dévoués. @PTandis que nous nous occupons de Byblos, d'autres régions d'Egypte se préparent à attaquer. Les Nubiens se sont déplacés vers le nord et ont atteint la première cataracte. Nous devons aider nos compatriotes à les repousser. Les rapports provenant de Havaris font état d'un mystérieux ennemi, le peuple de la Mer. Ces deux ennemis doivent être retenus si l'Egypte veut atteindre la gloire. Pour montrer votre puissance, envoyez des troupes et des navires de guerre à ceux qui le demandent."
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
            text: "La gloire de l'Egypte",

        }
        content {
            text: "Les guerriers Hyksos enfin hors de notre pays, un nouveau royaume est désormais prêt à voir le jour. Très noble pharaon, Kuban est un endroit idéal pour commencer ce nouveau royaume. Nous pouvons utiliser l'importante quantité d'or trouvée ici pour réaliser votre nouvelle vision de l'Egypte. @PAlors que l'Egypte approche de son apogée, quelques problèmes persistent. De nombreuses cités égyptiennes pas encore tout à fait remises de l'invasion des guerriers Hyksos requièrent votre aide. Dans d'autres régions, les anciens ennemis de l'Egypte poursuivent leurs attaques, tandis qu'un nouvel adversaire, le peuple de la Mer, effectue des raids sur nos côtes nord. Préparez-vous à défendre les autres cités égyptiennes contre ces adversaires, récents ou anciens. @PAlors que l'Egypte poursuit sa croissance, de nombreuses cités envisagent de faire du commerce. Certaines de ces cités sont familières avec nos coutumes, et remplies du respect que vous inspirez, se considèrent elles-mêmes égyptiennes. D'autres, par contre, nous sont étrangères et commercent avec nous pour la première fois. Pour la gloire de l'Egypte, utilisez au mieux ces relations commerciales pour fournir à votre peuple tous les biens qu'il désire. @PPour entrer dans cette nouvelle ère, vos architectes royaux proposent de construire en votre honneur, O pharaon, deux pyramides et un mausolée majestueux. Ces monuments reflèteront la richesse et la grandeur que vous avez apportées à l'Egypte."
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
            text: "Le peuple de la Mer",

        }
        content {
            text: "O Grand Horus, notre emprise sur l'Asie est puissante et indiscutée, et nos frontières une nouvelle fois s'étendent profondément en Nubie. Cependant, les problèmes s'intensifient sur la côte nord. Le peuple de la Mer est de plus en plus agressif, organisant des raids sur nos cités de manière injustifiée. Seule la présence du pharaon pourra repousser cet adversaire féroce et rusé. Si vous préparez un navire, soutenu par une puissante armée, nous devrions pouvoir triompher du peuple de la Mer. @PTandis que vous travaillez à la défaite du peuple de la Mer, vos braves nomarques lancent des attaques dans le monde entier. Si celles-ci s'avèrent un succès, l'Egypte contrôlera le monde de l'Euphrate en Asie jusqu'à la tentaculaire cité éthiopienne de Kerma au sud. Une fois la victoire remportée par vos nomarques, votre dynastie restera dans les esprits comme celle qui aura le plus compté en Egypte. @PMarqué par votre influence incommensurable, Mycènes, un lointain partenaire commercial s'est présenté à nous. Le roi de Mycènes ayant pris connaissance de la splendeur et de la générosité de l'Egypte désire commercer avec nous. Si vous consentez à ouvrir cette nouvelle route commerciale, O pharaon, vos citoyens seront certainement approvisionnés en des biens exotiques encore inconnus. @PPour abriter votre famille royale dans l'au-delà, un imposant mausolée et deux impressionnantes pyramides de briques seront construits. Ces monuments rappelleront vos actes à tous ceux qui vous ont suivi en temps de guerre comme en temps de paix."
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
            text: "La gloire du pharaon",

        }
        content {
            text: "Bienveillant pharaon, vous avez apporté la paix et la prospérité à notre nation. Sous votre règne avisé, l'Egypte est redevenue un pays fort et glorieux. Tous les nomarques vous sont loyaux et plus aucune menace ne plane désormais sur notre grande nation. @PMaintenant que tous les objectifs établis par votre famille depuis de si nombreuses années ont été atteints, l'heure est aujourd'hui venue d'immortaliser les exploits de votre grande dynastie, en l'honorant par la construction de la plus imposante pyramide d'Egypte jamais réalisée, plus grande que celle de Koufou à Giza elle-même. D'autres membres de votre noble famille se sont également sacrifiés pour vous permettre de régner sur toute l'Egypte. Ces membres ne doivent pas être oubliés, par conséquent, un mausolée en grès sera construit en leur honneur. @LKahun, situé dans la riche région de Fayoum, serait l'emplacement idéal pour de tels monuments. Vous pourrez, depuis cette cité, prendre part à toutes les affaires de l'état et répondre aux nombreuses requêtes d'approvisionnement provenant des autres cités, tout en faisant construire votre immense pyramide."
        }
    }
    message_mission_buto {
        id: 438,
        type: 3,
        size [40, 30]
        title {
            text: "Bouto",

        }
        content {
            text: "@PAvec l'aide de votre famille, le roi thinite Horus Aha est parvenu à unir les royaumes de Haute et de Basse-Egypte, se proclamant pharaon de toute l'Egypte et fondant une capitale imposante à Memphis.    @PVotre clan a de nouveau migré, cette fois-ci dans une région humide du Delta de Basse-Egypte, appelée Bouto. Les navires de guerre cananéens ont menacé cette région et vous voudriez bien y envoyer quelques-uns de vos propres navires de guerre, le moment venu. @PVotre famille est entrée dans la noblesse. De ce fait, avant que vous ne passiez de vie à trépas, vous devez entreprendre la construction d'une superbe tombe en briques - un mastaba - qui abritera votre corps durant son voyage dans l'au-delà. @PAuparavant, vous devez installer des fermes sur les berges du Nil, afin d'exploiter le sol riche et fertile engendré par l'inondation annuelle du fleuve. Votre population pourra ainsi croître et prospérer, jusqu'à devenir suffisamment nombreuse pour achever la construction de ce monument sacré. Mais attention : les eaux du Nil cachent de nombreux dangers, tels que des crocodiles assoiffés de sang, des hippopotames et des moustiques porteurs de malaria. @L@LAgriculture en bordure du Nil @PVous devez construire des fermes directement sur la plaine inondable, afin de bénéficier de sa fertilité croissante. Contrairement à la plupart des structures de travail, ces fermes n'ont pas besoin d'un accès direct aux employés, mais d'une main-d'oeuvre paysanne régulière, fournie par les chantiers. Vous devez construire des chantiers à proximité des fermes de la plaine inondable, afin que les paysans n'aient pas un trop long trajet à effectuer. @G56 @L@PLa crue annuelle du Nil fertilise la terre dévastée de la plaine inondable. Les paysans moissonnent la récolte annuelle juste avant l'inondation, puis la stockent dans vos greniers. Comme il n'y a qu'une moisson par an, vérifiez que vous disposez d'un nombre suffisant de greniers pour stocker la quantité de nourriture nécessaire à votre population en plein essor."
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
            text: "La terre des peuples de la Mer",

        }
        content {
            text: "@PLes troubles et les mécontentements envers les zones occidentales se sont récemment intensifiés. Les éclaireurs rapportent que plusieurs tribus barbares parlant d'étranges langues sont arrivées sur les rivages de Kyrenaica à l'ouest. En outre, ces peuples cheminent désormais aux côtés de Maraye, le fils de Did, roi de Libye et ennemi du pharaon.   @PLe pharaon Merneptah a entendu dire que ces vils hommes, suivis de près par leurs épouses, leurs enfants et leurs possessions, se dirigeraient bientôt à l'est, en direction du delta fertile du Nil, notre patrie, en quête d'un endroit où s'installer. De petites échauffourées ont déjà eu lieu dans les oasis au nord de Siwi et de Farafra. La ville de Pi-yer se trouve désormais sur leur chemin. Dans peu de temps, cette bande de sauvages sera à nos portes. Le pharaon a décrété que, s'ils arrivaient, ils ne devraient pas être autorisés à pénétrer dans l'enceinte de la cité! @PVous devez importer du bois pour construire des navires de guerre robustes et du cuivre pour construire des armes. Vous avez de la chance, car les Hittites qui semaient jusqu'à maintenant le trouble se sont désormais calmés, grâce à la splendide victoire remportée à Qadesh par Ramsès II, seigneur du bien-aimé Merneptah. Renforcez votre cité, et rassemblez vos troupes en vue d'un combat mortel."
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
            text: "Victoire sur les Assyriens",

        }
        content {
            text: "@PDepuis l'époque du grand Shabaka, unificateur de la Haute et de la Basse Egypte et seigneur du pharaon Taharqa, les conflits avec les Assyriens belliqueux ont été nombreux. De son vivant, le pharaon Shabaka a jugé bon de venir en aide à nos amis en Palestine, qui subissaient la domination de l'Assyrie. Mais attention ! Les serviteurs du roi Asarhaddon sont de nouveau en marche, comme toujours, les yeux tournés vers les terres fertiles d'Egypte. C'est désormais à votre tour de vous couvrir de gloire ! A l'instar du maire du royaume de Migdol, vous devez vous défendre contre une série d'attaques perpétrées par ces brutes assoiffées de sang. Située sur la rive est du delta du Nil, votre forteresse se trouve sur la ligne de front des défenses extérieures égyptiennes. @PVous devez convenablement entraîner vos soldats et établir des liaisons commerciales pour assurer un approvisionnement constant en armes et en matières premières. @PMais n'échouez pas ! Une forte résistance militaire est vitale pour assurer la pérennité de l'indépendance égyptienne. Si vous résistez pendant sept années, la victoire est assurée. Taharqa, le grand pharaon, second fils de Shabaka, vous regarde!"
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
            text: "Renaissance d'une flotte",

        }
        content {
            text: "@PDurant plusieurs générations, les Egyptiens ont souffert de la mainmise de la Perse. Toutefois, la domination babylonienne sur nos terres sacrées n'est pas aussi forte qu'autrefois. Tandis que nos oppresseurs s'occupaient des affaires politiques de Grèce, une série de révoltes en Egypte a finalement affaibli le joug perse. Le pharaon Achoris a cependant entendu dire qu'une force commandée par l'Amiral Conon (serviteur grec recevant de l'or de Perse) a été envoyée par Artaxerxes II et se dirige vers nos rivages. Le pharaon Achoris a jugé qu'une forte présence navale sur le Nil était nécessaire pour repousser cette invasion. En tant que gouvernement du royaume de Tanis pour les dix années à venir, vous devez construire de robustes navires et entraîner des troupes vigoureuses pour prévenir l'approche par voie maritime ou terrestre. @PVous devez établir une route de commerce avec Enkomi pour importer du bois robuste en vue de constituer une flotte. Vous pouvez également importer du cuivre d'Enkomi, sur l'île de Chypre. Cette route de commerce est pour le moins incertaine, car elle est proche de la côte du Levant, sous le contrôle de nos ennemis. En fournissant au pharaon les matériaux dont il a besoin, vous pourrez accroître vos revenus.   @PN'oubliez pas qu'en ces temps troublés, les fonds sont limités. Pour réussir, vous devez faire preuve de ruse en affaires et d'habileté dans le commandement."
        }
    }
    message_mission_alexandria_2 {
        id: 442,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandrie",

        }
        subtitle {
            text: "Alexandre le Grand",

        }
        content {
            text: "@PLe grand Alexandre, fils de Philippe II de Macédoine originaire de l'Empire babylonien, a béni les terres d'Egypte de sa présence. Grâce à lui, le dernier satrape perse corrompu a pris ses jambes à son cou. Après s'être sacrifié pour le taureau Apis à Memphis, Alexandre a été accepté comme pharaon. Le peuple entier se réjouit ! Avant de partir pour l'oracle d'Amon dans l'oasis de Siwi toutefois, notre héros a décidé de fonder une nouvelle cité, qu'il souhaite voir devenir un jour la capitale de son vaste empire en pleine expansion. Dans sa très grande sagesse, il vous a choisi pour occuper le premier poste de maire de la ville ! @PLe grand Alexandre vous a légué des fonds considérables afin de commencer la construction. Il vous a également offert les services du célèbre architecte grec Dinocrate. En l'espace d'une dizaine d'années, il compte sur vous pour dominer les affaires commerciales, culturelles et militaires de sa cité rayonnante.  @PNotre commandant suprême a même trouvé le temps de définir l'emplacement des deux principales voies publiques de sa cité. La rue Canope suit un axe est-ouest ; l'autre avenue principale est perpendiculaire à la première et se dirige en direction du sud vers le lac Mariout. @PEn tant que responsable agréé de ce projet, vous devez rapidement assurer la construction d'infrastructures portuaires et établir des routes de commerce lucratives. En effet, nos produits devraient attirer de nombreux consommateurs, en particulier le blé, l'orge, le papyrus et le lin. Ne négligez pas les aspects culturels de cette cité, ni ses aspects militaires, car il y a toujours des bandits pour dépouiller l'Egypte de ses richesses."
        }
    }
    message_mission_ptolemy_alexandria {
        id: 443,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alexandrie de Ptolémée",

        }
        subtitle {
            text: "Un phare lumineux",

        }
        content {
            text: "@PL'héritage d'Alexandre le Grand perdure dans la cité majestueuse. Même si sa dépouille mortelle repose dans le mausolée d'Alexandrie, sa cité reste flamboyante. Il vous incombe à vous, Ptolémée I Sôter, de poursuivre la tâche que le noble Alexandre a commencée. Depuis son fondement par Alexandre il y a à peine 30 ans, la cité est devenue un pôle commercial majeur, fournissant les denrées alimentaires indispensables ainsi que des articles de luxe aux alentours. Afin de poursuivre sa progression économique et d'assurer un passage sûr aux nombreux navires qui pénètrent le grand port de la cité, vous devez construire un très grand phare sur l'île du pharaon, au sud du port. Cette structure guidera les navigateurs en toute sécurité dans le port, en leur faisant éviter ses dangereux bancs de sable. @PLe commerce est toutefois tellement important que vous ne pouvez pas ignorer l'avancée culturelle et intellectuelle de la société. Sous votre conduite, Alexandrie peut désormais devenir la capitale intellectuelle du monde connu. Rassemblez des connaissances venues de près ou de loin et construisiez une grande bibliothèque pour les conserver. Nul doute que les érudits afflueront du monde entier pour visiter ce temple du savoir sans précédent.   @PPour construire ces grands monuments, vous devez importer des matériaux de construction, tels que du marbre blanc, particulièrement adapté à de tels édifices. Enkomi, sur l'île de Chypre, regorge de ce matériau.   @PEnfin, ne négligez pas vos forces militaires. Il y a toujours des troubles quelque part. Il peut s'avérer nécessaire d'envoyer des troupes jusqu'aux confins du territoire pour protéger les intérêts de l'Egypte et défendre son honneur."
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
            text: "César et Cléopâtre",

        }
        content {
            text: "@PLa mainmise indélicate de l'Empire romain s'accentue chaque jour. Même les luttes politiques féroces de Rome ont atteint nos terres. Suite au récent assassinat de Pompée sur les rives d'Egypte, César jouit du contrôle total des puissantes légions romaines et ses ambitions se portent maintenant sur les richesses de l'Egypte, sans oublier la beauté de la resplendissante Cléopâtre VII, fille de Ptolémée XII Aulète. Mais notre rusée Cléopâtre ne se laisse pas prendre si facilement. Si César désire l'utiliser pour étendre l'influence de Rome en Egypte, elle utilise à son tour César comme instrument pour maintenir la puissance dynastique en Egypte. @PL'arrivée de César à Alexandrie avec les impopulaires romains a soulevé une révolte chez les citoyens indépendants de cette ville. Une foule incontrôlée, conduite par le jeune frère de Cléopâtre, Ptolémée XIII, retient César et ses hommes dans les quartiers royaux de la cité. D'âpres combats de rue se sont déclenchés, et l'on déplore de nombreux blessés. Dans une tentative pour laisser sa route maritime ouverte pour pouvoir prendre la fuite, César a incendié la flotte égyptienne en rade du port d'Alexandrie. Malheureusement, l'incendie s'est étendu à certains entrepôts côtiers, brûlant de grandes quantités de papyrus appartenant à la grande bibliothèque.   @PAfin de se sortir du piège dans lequel il se trouve, César a fait appel aux troupes du loyal Mithridate de Syrie. Après avoir assiégé la forteresse de Migdol, Mithridate a ordonné à ses troupes de contourner la pointe du delta du Nil afin d'approcher Alexandrie par le sud-est. Les principaux éléments de cette force se trouvaient alors dans les faubourgs du petit village de Maritis, sur la rive est du lac Mariout, préparant la phase finale de leur voyage.  @PPtolémée XIII le maléfique a été informé de l'approche de ces renforts. En réponse, il conduit son armée, plus nombreuse, au sud-est d'Alexandrie. Une bataille décisive sur la rive est du lac Mariout est sur le point d'avoir lieu. Pouvez-vous, vous qui commandez les légions romaines de Mithridate, mettre en échec l'armée égyptienne rebelle de Ptolémée et rejoindre César et Cléopâtre en Alexandrie ? Leur sort est entre vos mains."
        }
    }
    message_mission_cleopatra_alexandria {
        id: 445,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alexandrie de Cléopâtre",

        }
        subtitle {
            text: "L'héritage d'une reine",

        }
        content {
            text: "@PLa mort sanglante de César sous les coups de poignards de ses assassins jeta le monde romain dans le trouble et vous plongea, Cléopâtre VII, dans une colère et une tristesse immenses. Votre amant et allié puissant n'est plus. Octave, son neveu adoptif, encore adolescent, a été nommé comme héritier, mais Marc-Antoine, plus expérimenté, auparavant consul de César, est devenu le chef de l'Etat, non sans causer du ressentiment au jeune Octave. Sans grande surprise, le testament de César éludait le nom de votre fils, Ptolémée César, plus connu sous le nom de Césarion. Désirant la sécurité pour vous-même et votre enfant et, comme toujours, cherchant à préserver la puissance de l'Egypte, vous avez quitté Rome pour Alexandrie.  @PMalgré tout ce qui vous lie à Rome, vous ne pouvez pas laisser derrière vous tous les troubles internes à cette cité. Des hommes puissants sont toujours avides de pouvoir, de votre soutien et de l'accès aux richesses de l'Egypte. Vous devez absolument être du côté du vainqueur de cette lutte pour le pouvoir ; si vous vous retrouvez du côté du perdant, ce sera la fin de l'Egypte. La lutte féroce entre les factions romaines rivales s'est récemment illustrée à Philippi, où les partisans de Marc-Antoine ont écrasé les forces de Brutus et de Cassius. Antoine, Octave et Lipidus ont désormais préparé l'Empire à un règne commun, Antoine revendiquant le territoire est, qui inclut l'Egypte. @PPeu de temps après la bataille, Marc-Antoine vous a demandé de le rejoindre à Tarsus, en Asie Mineure, afin que vous puissiez expliquer plus clairement pourquoi vous aviez attendu si longtemps pour combattre les partisans de Marc-Antoine. Vous avez sagement décliné l'offre qui vous était faite. Après tout, vous savez mieux que quiconque qu'il vaut bien mieux pour un romain être dans votre position que dans la sienne ! @PAinsi vous, Cléopâtre, êtes retournée chez vous à Alexandrie, en Egypte. Il est maintenant temps d'étendre la gloire de cette grande cité, fondée par le grand Alexandre, dont la tombe est toujours visitée. La fameuse grande bibliothèque d'Alexandrie continue à attirer des érudits du monde entier ; le magnifique phare de Pharos indique toujours aux navigateurs leur chemin à travers les traîtres eaux du port d'Alexandrie. Vous pouvez maintenant continuer d'enrichir la beauté de cette cité en construisant un Caesareum en l'honneur de votre ancien amant et de votre jeune fils. En outre, vous devez assurer votre passage dans l'au-delà en construisant un autre mausolée, afin que vous puissiez être convenablement vénérée après votre voyage dans les champs de roseaux.   @PLa prochaine fois que Marc-Antoine fera appel à vous, peut-être le fera-t-il avec un peu plus de tact ?"
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
            text: "Antoine et Cléopâtre",

        }
        content {
            text: "@PÔ, noble Cléopâtre VII, épouse de César et maintenant d'Antoine, la destinée de l'Egypte est entre vos mains, mais vos mains sont désormais dans celles d'un romain, Marc-Antoine, profondément engagé dans la lutte pour le contrôle des légions romaines.   @PAntoine, qui a besoin des ressources d'Egypte, mais qui désire également votre amour et votre affection, a répondu par la positive à votre demande en mariage. Malheureusement, l'annonce de cette union a scandalisé Rome ! Comme vous vous en doutiez, Antoine était toujours marié à Octavie, soeur d'Octave, héritier légitime de César et, avec Antoine, exerçait le pouvoir romain. Or, lorsque les moeurs polygames d'Antoine ont été dévoilées, cette relation s'est considérablement tendue. Octave suppose qu'Antoine a non seulement souillé l'honneur de sa soeur et de sa famille, mais également le prestige de Rome. Afin de régler cette affaire d'honneur et de mettre fin à la lutte pour le contrôle suprême de Rome, Octave a lancé un véritable défi à votre amant, Antoine. Aussi, Antoine, accompagné par vous et votre flotte égyptienne, a trouvé un poste sur la terre grecque près d'Actium où établir un campement. Ce site comporte un port important et de nombreux emplacements pour vos navires.   @PVous devez rapidement constituer une armée, en particulier un corps naval. Octave a fait le voeu de revenir en septembre de l'an 31. @PDésormais, votre sort, celui de Marc-Antoine ainsi que de l'Egypte et de Rome, dépendent de nouveau de l'efficacité militaire."
        }
    }
    message_mission_thutmose_valley {
        id: 447,
        type: 3,
        size [40, 30]
        title {
            text: "Thoutmôsis dans la Vallée",

        }
        subtitle {
            text: "La première tombe",

        }
        content {
            text: "@PAprès une série de brillantes victoires sur de lointains champs de bataille pour la défense des terres et du peuple d'Egypte, le pharaon Thoutmôsis s'est lancé dans les préparatifs de son voyage dans l'au-delà. Afin de garantir la réussite de ce voyage, le pharaon désire que vous commenciez la construction de sa tombe dès que possible. Vous devez donc établir un village sur la rive ouest du Nil pour assurer une main-d'oeuvre qualifiée suffisante. Vous devrez ensuite identifier un site adéquat pour l'édification de sa tombe dans les falaises à l'ouest de ce village. Vous aurez besoin de tailleurs de pierre expérimentés pour sculpter dans la roche les nombreuses chambres de la tombe, ainsi que d'artisans talentueux pour plâtrer et peindre ces pièces.   @PAfin de fournir de la lumière aux ouvriers travaillant dans les profondeurs de la tombe, vous devez établir des fabriques de lampes. Il vous faut pour cela fournir des poteries et de l'huile importée pour les alimenter. Vous devez en outre planter des champs de henné afin de procurer aux fabricants de peintures des bases de couleurs éclatantes."
        }
    }
    message_mission_tutankhamun_valley {
        id: 448,
        type: 3,
        size [40, 30]
        title {
            text: "Tut dans la Vallée",

        }
        subtitle {
            text: "Mort de Toutankhamon",

        }
        content {
            text: "@PUne terrible tragédie a frappé notre jeune pharaon bien-aimé, Toutankhamon ! Son règne, autrefois si prometteur, a été ignoblement interrompu par le destin. Il est temps pour les ouvriers de Deir el-Medineh de préparer à nouveau la chambre de repos éternel du pharaon. Cette disparition subite donne un caractère urgent aux travaux et vous devez encourager les artisans à oeuvrer sans relâche. La tombe de Toutankhamon doit contenir toutes les provisions nécessaires à son voyage dans l'au-delà et être prête à recevoir sa dépouille sacrée dans un délai très court. La rapidité est d'une importance extrême !"
        }
    }
    message_mission_seti_valley {
        id: 449,
        type: 3,
        size [40, 30]
        title {
            text: "Séthi dans la Vallée",

        }
        subtitle {
            text: "La tombe d'un pharaon",

        }
        content {
            text: "@PNotre plus puissant pharaon, Séthi, fils de Ramsès I, a déclaré qu'il était temps de commencer les préparatifs pour son voyage dans l'au-delà. C'est pourquoi vous devez commencer à creuser sa tombe royale dans la Vallée des Rois. Aucun effort ne doit être épargné par vos ouvriers dans ces préparatifs. Des mesures adéquates doivent être prises afin d'assurer qu'une fois l'ouvrage terminé, il sera inégalé pendant des générations. @PToutefois, à mesure que ce projet royal progresse, vous devez prendre toutes les précautions nécessaires contre les bandits ! On a déjà fait écho de bandes de criminels cherchant à s'enrichir en dépouillant les tombes, perturbant ainsi le repos éternel des pharaons d'Egypte. Vous ne devez en aucun cas laisser de tels actes déshonorer les tombes royales de la Vallée ; sinon, vous perdrez votre place au sein du royaume."
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
            text: "Terres du Levant",

        }
        content {
            text: "@PRendons grâce au gouverneur du royaume, régent du Levant et loyal sujet de notre pharaon, fils de Rê. Qu'il est heureux de vivre en ces temps où l'Egypte s'étend des confins de la Nubie jusqu'aux rivages du Levant. La sagesse de notre nouveau pharaon est infinie, Ramsès II, et sa vision est grande, car c'est lui qui vous a envoyé régner sur cette terre, qui fait aujourd'hui partie du domaine de l'Egypte.  @PCette région, toujours parsemée de dangers, recèle de nombreuses richesses à exploiter. Les collines verdoyantes regorgent de grands arbres qui produisent du bon bois, idéal pour la confection de chars et utilisable sous de multiples formes en construction. Le cuivre, que l'on trouve en abondance, est toujours fort utile pour la confection d'armes robustes. Le bois et le cuivre seront assurément les bienvenus lorsqu'ils seront rapportés en grandes quantités. Vous devrez superviser l'établissement d'un grand port de commerce à partir duquel ces biens précieux pourront être exportés. Le pharaon et le peuple d'Egypte vous en seront extrêmement reconnaissants ! @PMais attention ! Assurez-vous que vos soldats sont équipés de chars rapides et d'armes robustes, car les Hittites, bien que vaincus par Séthi, père du pharaon, sont toujours dangereux et risquent de menacer notre autorité sur ces terres. Une forte présence militaire sur ce nouveau territoire peut s'avérer nécessaire pour repousser une éventuelle insurrection, et sera sans nul doute de la plus grande utilité dans l'avenir. @PEnfin, pour rappeler aux habitants de cette région à qui ils doivent désormais rendre hommage, le pharaon Ramsès II juge approprié d'ériger un obélisque à sa gloire."
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
            text: "La bataille de Qadesh",

        }
        content {
            text: "@PLa terre d'Amurra, terminée par la côte du Levant, tremble sous les pas de vos puissantes légions, ô pharaon. Cette région comporte de rares pierres précieuses, mais elle est également riche en conflits. Les Hittites armés, conduits par le féroce roi Muwatalli, contestent de nouveau le contrôle de ces terres, qui nous appartiennent. Les espions capturés disent qu'ils se trouvent toujours bien loin au nord et qu'ils ne présentent par conséquent aucune menace. Mais doit-on les croire ? La sagesse dicte au soldat de ne jamais abaisser son bouclier au combat.   @PSuite à de telles rumeurs d'insurrection, vous, notre vénéré pharaon, Ramsès II, fils de Rê, êtes venu dans la ville fortifiée de Qadesh. Déjà, deux de vos redoutées compagnies de conducteurs de char se sont établies dans ses faubourgs. Mais ce n'est pas tout. Vous avez à votre disposition d'autres troupes d'élite, particulièrement expérimentées, récemment engagées près de Sumur. Mais attention ! Il pourrait s'avérer sage de retarder le déploiement de ces troupes jusqu'au dernier moment, car la sagesse dicte également au soldat de conserver une réserve de troupes bien entraînées pour se lancer dans le front de la bataille. @PUne fois le misérable ennemi vaincu, il sera nécessaire de raviver l'économie stagnante de Qadesh afin que cette cité puisse contribuer à la gloire de l'Egypte. Il vous faut donc recueillir des pierres précieuses en engager des orfèvres expérimentés pour fabriquer des articles de luxe pour les loyaux sujets du pharaon. Ces articles d'une rare beauté seront sans nul doute très demandés !"
        }
    }
    message_mission_abu_simbel {
        id: 452,
        type: 3,
        size [40, 30]
        title {
            text: "Abou Simbel",

        }
        subtitle {
            text: "Les colosses d'Abou Simbel",

        }
        content {
            text: "@PLa gloire de notre pharaon, Ramsès II, envahit notre territoire. Ainsi, pour que l'héritage de son règne dure à jamais, un grand monument et un temple dédiés à sa gloire doivent être construits en Nubie. Le pharaon lui-même a sélectionné l'emplacement idéal pour cette création. Depuis les falaises roses qui dominent la rive ouest du Nil à Abou Simbel, vous pourrez superviser la sculpture de quatre statues assises majestueuses représentant le pharaon. Les surfaces de ce monument, sculptées dans la roche vive, illustreront les actes héroïques du pharaon durant la bataille de Qadesh. Ce monument gigantesque, tout en célébrant la bravoure de notre chef, rappellera également aux peuples de Nubie la grandeur et la puissance de l'Egypte. En effet, si la Nubie est riche en dépôts d'or et d'autres pierres précieuses rares, ses habitants ont toujours mal supporté la domination égyptienne. Vous devez donc vous préparer à vous défendre, et vous apprêter à envoyer des troupes pour venir en aide au pharaon. @PLe grès peut être exporté pour la construction dans d'autres régions du royaume, tout comme d'autres articles que vous pouvez obtenir grâce aux abondantes ressources de la région. Le bois précieux est rare, toutefois. Vous devrez sans nul doute établir une route de commerce pour importer cette denrée, qui sera nécessaire pour construire l'immense échafaudage de la sculpture."
        }
    }
    message_mission_ramses_valley {
        id: 453,
        type: 3,
        size [40, 30]
        title {
            text: "Ramsès dans la Vallée",

        }
        subtitle {
            text: "Une tombe sans égale",

        }
        content {
            text: "@PDe longues et glorieuses années se sont écoulées depuis que notre pharaon, le vénéré Ramsès II, a accepté de succéder à son père, Séthi I. Avec la bénédiction de Rê, il continuera à régner pendant longtemps encore. Il est temps cependant de commencer les préparatifs du lieu de repos éternel de notre chef vénéré. Il a fourni à votre architecte un plan pour construire une grande tombe telle qu'il n'en a jamais édifiée, surpassant même celle de son seigneur. Il vous incombe désormais de veiller que cette requête royale soit menée à bien. @PMais attention ! Il règne un fort climat de trouble chez certains ouvriers et esclaves épris d'indépendance, dans la région tout comme en Basse Egypte. Ils suivent l'exemple d'un homme autrefois membre de la cour de notre pharaon, et ils ont menacé de faire appel à leur dieu pour une intervention divine. Ils espèrent qu'avec cette aide sacrée, ils arriveront à leurs fins. Aujourd'hui, prêtres et hommes de foi étudient cette menace. Tandis que nous attendons patiemment leur verdict, il convient de nous préparer à l'inattendu."
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
            text: "La terre des peuples de la Mer",

        }
        content {
            text: "@PLes troubles et les mécontentements envers les zones occidentales se sont récemment intensifiés. Les éclaireurs rapportent que plusieurs tribus barbares parlant d'étranges langues sont arrivées sur les rivages de Kyrenaica à l'ouest. En outre, ces peuples cheminent désormais aux côtés de Maraye, le fils de Did, roi de Libye et ennemi du pharaon.   @PLe pharaon Merneptah a entendu dire que ces vils hommes, suivis de près par leurs épouses, leurs enfants et leurs possessions, se dirigeraient bientôt à l'est, en direction du deltta fertile du Nil, notre patrie, en quête d'un endroit où s'installer. De petites échauffourées ont déjà eu lieu dans les oasis au nord de Siwi et de Farafra. La ville de Pi-yer se trouve désormais sur leur chemin. Dans peu de temps, cette bande de sauvages sera à nos portes. Le pharaon a décrété que, s'ils arrivaient, ils ne devraient pas être autorisés à pénétrer dans l'enceinte de la cité! @PVous devez importer du bois pour construire des navires de guerre robustes et du cuivre pour fabriquer des armes. Vous avez de la chance, car les Hittites qui semaient jusqu'à maintenant le trouble se sont désormais calmés, grâce à la splendide victoire remportée à Qadesh par Ramsès II, seigneur du bien-aimé Merneptah. Renforcez votre cité, et rassemblez vos troupes en vue d'un combat mortel."
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
            text: "Victoire sur les Assyriens",

        }
        content {
            text: "@PDepuis l'époque du grand Shabaka, unificateur de la Haute et de la Basse Egypte et seigneur du pharaon Taharqa, les conflits avec les Assyriens belliqueux ont été nombreux. De son vivant, le pharaon Shabaka a jugé bon de venir en aide à nos amis en Palestine, qui subissaient la domination de l'Assyrie. Mais attention ! Les serviteurs du roi Asarhaddon sont de nouveau en marche, comme toujours, les yeux tournés vers les terres fertiles d'Egypte. C'est désormais à votre tour de vous couvrir de gloire ! A l'instar du maire du royaume de Pelusium, vous devez vous défendre contre une série d'attaques perpétrées par ces brutes assoiffées de sang. Située sur la rive est du delta du Nil, votre forteresse se trouve sur la ligne de front des défenses extérieures égyptiennes. @PVous devez convenablement entraîner vos soldats et établir des liaisons commerciales pour assurer un approvisionnement constant en armes et en matières premières. @PMais n'échouez pas ! Une forte résistance militaire est vitale pour assurer la pérennité de l'indépendance égyptienne. Si vous résistez pendant sept années, la victoire est assurée. Taharqa, le grand pharaon, second fils de Shabaka, vous regarde !"
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
            text: "Renaissance d'une flotte",

        }
        content {
            text: "@PDurant plusieurs générations, les Egyptiens ont souffert de la mainmise de la Perse. Toutefois, la domination babylonienne sur nos terres sacrées n'est pas aussi forte qu'autrefois. Tandis que nos oppresseurs s'occupaient des affaires politiques de Grèce, une série de révoltes en Egypte a finalement affaibli le joug perse. Le pharaon Achoris a cependant entendu dire qu'une force commandée par l'Amiral Conon (serviteur grec recevant de l'or de Perse) a été envoyée par Artaxerxes II et se dirige vers nos rivages. Le pharaon Achoris a jugé qu'une forte présence navale sur le Nil était nécessaire pour repousser cette invasion. En tant que gouvernement du royaume de Tanis pour les dix années à venir, vous devez construire de robustes navires et entraîner des troupes vigoureuses pour prévenir l'approche par voie maritime ou terrestre. @PVous devez établir une route de commerce avec Enkomi pour importer du bois robuste en vue de constituer une flotte. Vous pouvez également importer du cuivre d'Enkomi, sur l'île de Chypre. Cette route de commerce est pour le moins incertaine, car elle est proche de la côte du Levant, sous le contrôle de nos ennemis. En fournissant au pharaon les matériaux dont il a besoin, vous pourrez accroître vos revenus.   @PN'oubliez pas qu'en ces temps troublés, les fonds sont limités. Pour réussir, vous devez faire preuve de ruse en affaires et d'habileté dans le commandement."
        }
    }
    message_mission_alexandria {
        id: 457,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandrie",

        }
        subtitle {
            text: "Alexandre le Grand",

        }
        content {
            text: "@PLe grand Alexandre, fils de Philippe II de Macédoine originaire de l'Empire babylonien, a béni les terres d'Egypte de sa présence. Grâce à lui, le dernier satrape perse corrompu a pris ses jambes à son cou. Après avoir s'être sacrifié pour le taureau Apis à Memphis, Alexandre a été accepté comme pharaon. Le peuple entier se réjouit ! Avant de partir pour l'oracle d'Amon dans l'oasis de Siwi toutefois, notre héros a décidé de fonder une nouvelle cité, qu'il souhaite voir devenir un jour la capitale de son vaste empire en pleine expansion. Dans sa très grande sagesse, il vous a nommé pour être le futur premier maire de cette ville ! @PLe grand Alexandre vous a légué des fonds considérables afin de commencer la construction. Il vous a également offert les services du célèbre architecte grec Dinocrate. En l'espace d'une dizaine d'années, il compte sur vous pour dominer les affaires commerciales, culturelles et militaires de sa cité rayonnante.  @PNotre commandant suprême a même trouvé le temps de définir l'emplacement des deux principales voies publiques de sa cité. La rue Canope suit un axe est-ouest ; l'autre avenue principale est perpendiculaire à la première et se dirige en direction du sud vers le lac Mariout. @PEn tant que responsable agréé de ce projet, vous devez rapidement assurer la construction d'infrastructures portuaires et établir des routes de commerce lucratives. En effet, nos produits devraient attirer de nombreux consommateurs, en particulier le blé, l'orge, le papyrus et le lin. Ne négligez pas les aspects culturels de cette cité, ni ses aspects militaires, car il y a toujours des bandits pour dépouiller l'Egypte de ses richesses."
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
            text: "Un phare lumineux",

        }
        content {
            text: "@PL'héritage d'Alexandre le Grand perdure dans la cité majestueuse. Même si sa dépouille mortelle repose dans le mausolée d'Alexandrie, sa cité reste flamboyante. Il vous incombe à vous, Ptolémée I Sôter, de poursuivre la tâche que le noble Alexandre a commencée. Depuis son fondement par Alexandre il y a à peine 30 ans, la cité est devenue un pôle commercial majeur, fournissant les denrées alimentaires indispensables ainsi que des articles de luxe aux alentours. Afin de poursuivre sa progression économique et d'assurer un passage sûr aux nombreux navires qui pénètrent le grand port de la cité, vous devez construire un très grand phare sur l'île du pharaon, au sud du port. Cette structure guidera les navigateurs en toute sécurité dans le port, en leur faisant éviter ses dangereux bancs de sable. @PLe commerce est toutefois tellement important que vous ne pouvez pas ignorer l'avancée culturelle et intellectuelle de la société. Sous votre conduite, Alexandrie peut désormais devenir la capitale intellectuelle du monde connu. Rassemblez des connaissances venues de près ou de loin et construisiez une grande bibliothèque pour les conserver. Nul doute que les érudits afflueront du monde entier pour visiter ce temple du savoir sans précédent.   @PPour construire ces grands monuments, vous devez importer des matériaux de construction, tels que du marbre blanc, particulièrement adapté à de tels édifices. Enkomi, sur l'île de Chypre, regorge de ce matériau.   @PEnfin, ne négligez pas vos forces militaires. Il y a toujours des troubles quelque part. Il peut s'avérer nécessaire d'envoyer des troupes jusqu'aux confins du territoire pour protéger les intérêts de l'Egypte et défendre son honneur."
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
            text: "César et Cléopâtre",

        }
        content {
            text: "@PLa mainmise indélicate de l'Empire romain s'accentue chaque jour. Même les luttes politiques féroces de Rome ont atteint nos terres. Suite au récent assassinat de Pompée sur les rives d'Egypte, César jouit du contrôle total des puissantes légions romaines et ses ambitions se portent maintenant sur les richesses de l'Egypte, sans oublier la beauté de la resplendissante Cléopâtre VII, fille de Ptolémée XII Aulète. Mais notre rusée Cléopâtre ne se laisse pas prendre si facilement. Si César désire l'utiliser pour étendre l'influence de Rome en Egypte, elle utilise à son tour César comme instrument pour maintenir la puissance dynastique en Egypte. @PL'arrivée de César à Alexandrie avec les impopulaires romains a soulevé une révolte chez les citoyens indépendants de cette ville. Une foule incontrôlée, conduite par le jeune frère de Cléopâtre, Ptolémée XIII, retient César et ses hommes dans les quartiers royaux de la cité. D'âpres combats de rue se sont déclenchés, et l'on déplore de nombreux blessés. Dans une tentative pour laisser sa route maritime ouverte pour pouvoir prendre la fuite, César a incendié la flotte égyptienne en rade du port d'Alexandrie. Malheureusement, l'incendie s'est étendu à certains entrepôts côtiers, brûlant de grandes quantités de papyrus appartenant à la grande bibliothèque.   @PAfin de se sortir du piège dans lequel il se trouve, César a fait appel aux troupes du loyal Mithridate de Syrie. Après avoir assiégé la forteresse de Pelusium, Mithridate a ordonné à ses troupes de contourner la pointe du delta du Nil afin d'approcher Alexandrie par le sud-est. Les principaux éléments de cette force se trouvaient alors dans les faubourgs du petit village de Maritis, sur la rive est du lac Mariout, préparant la phase finale de leur voyage.  @PPtolémée XIII le maléfique a été informé de l'approche de ces renforts. En réponse, il conduit son armée, plus nombreuse, au sud-est d'Alexandrie. Une bataille décisive sur la rive est du lac Mariout est sur le point d'avoir lieu. Pouvez vous, vous qui commandez les légions romaines de Mithridate, mettre en échec l'armée égyptienne rebelle de Ptolémée et rejoindre César et Cléopâtre en Alexandrie ? Leur sort est entre vos mains."
        }
    }
    message_mission_cleopatra_alexandria_2 {
        id: 460,
        type: 3,
        size [40, 30]
        title {
            text: "L'Alexandrie de Cléopâtre",

        }
        subtitle {
            text: "L'héritage d'une reine",

        }
        content {
            text: "@PLa mort sanglante de César sous les coups de poignards de ses assassins jeta le monde romain dans le trouble et vous plongea, Cléopâtre VII, dans une colère et une tristesse immenses. Votre amant et allié puissant n'est plus. Octave, son neveu adoptif, encore adolescent, a été nommé comme héritier, mais Marc-Antoine, plus expérimenté, auparavant consul de César, est devenu le chef de l'Etat, non sans causer du ressentiment au jeune Octave. Sans grande surprise, le testament de César éludait le nom de votre fils, Ptolémée César, plus connu sous le nom de Césarion. Désirant la sécurité pour vous-même et votre enfant et, comme toujours, cherchant à préserver la puissance de l'Egypte, vous avez quitté Rome pour Alexandrie.  @PMalgré tout ce qui vous lie à Rome, vous ne pouvez pas laisser derrière vous tous les troubles internes à cette cité. Des hommes puissants sont toujours avides de pouvoir, de votre soutien et de l'accès aux richesses de l'Egypte. Vous devez absolument être du côté du vainqueur de cette lutte pour le pouvoir ; si vous vous retrouvez du côté du perdant, ce sera la fin de l'Egypte. La lutte féroce entre les factions romaines rivales s'est récemment illustrée à Philippi, où les partisans de Marc-Antoine ont écrasé les forces de Brutus et de Cassius. Antoine, Octave et Lipidus ont désormais préparé l'Empire à un règne commun, Antoine revendiquant le territoire est, qui inclut l'Egypte. @PPeu de temps après la bataille, Marc-Antoine vous a demandé de le rejoindre à Tarsus, en Asie Mineure, afin que vous puissiez expliquer plus clairement pourquoi vous aviez attendu si longtemps pour combattre les partisans de Marc-Antoine. Vous avez sagement décliné l'offre qui vous était faite. Après tout, vous savez mieux que quiconque qu'il vaut bien mieux pour un romain être dans votre position que dans la sienne ! @PAinsi vous, Cléopâtre, êtes retournée chez vous à Alexandrie, en Egypte. Il est maintenant temps d'étendre la gloire de cette grande cité, fondée par le grand Alexandre, dont la tombe est toujours visitée. La fameuse grande bibliothèque d'Alexandrie continue à attirer des érudits du monde entier ; le magnifique phare de Pharos indique toujours aux navigateurs leur chemin à travers les traîtres eaux du port d'Alexandrie. Vous pouvez maintenant continuer d'enrichir la beauté de cette cité en construisant un Caesareum en l'honneur de votre ancien amant et de votre jeune fils. En outre, vous devez assurer votre passage dans l'au-delà en construisant un autre mausolée, afin que vous puissiez être convenablement vénérée après votre voyage dans les champs de roseaux.   @PLa prochaine fois que Marc-Antoine fera appel à vous, peut-être le fera-t-il avec un peu plus de tact ?"
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
            text: "Antoine et Cléopâtre",

        }
        content {
            text: "@PÔ, noble Cléopâtre VII, épouse de César et maintenant d'Antoine, la destinée de l'Egypte est entre vos mains, mais vos mains sont désormais dans celles d'un romain, Marc-Antoine, profondément engagé dans la lutte pour le contrôle des légions romaines.   @PAntoine, qui a besoin des ressources inestimables d'Egypte, mais qui désire également votre amour et votre affection, a répondu par la positive à votre demande en mariage. Malheureusement, l'annonce de cette union a scandalisé Rome ! Comme vous vous en doutiez, Antoine était toujours marié à Octavie, soeur d'Octave, héritier légitime de César et, avec Antoine, exerçait le pouvoir romain. Or, lorsque les moeurs polygames d'Antoine ont été dévoilées, cette relation s'est considérablement tendue. Octave suppose qu'Antoine a non seulement souillé l'honneur de sa soeur et de sa famille, mais également le prestige de Rome. Afin de régler cette affaire d'honneur et de mettre fin à la lutte pour le contrôle suprême de Rome, Octave a lancé un véritable défi à votre amant, Antoine. Aussi, Antoine, accompagné par vous et votre flotte égyptienne, a trouvé un poste sur la terre grecque près d'Actium où établir un campement. Ce site comporte un port important et de nombreux emplacements pour vos navires.   @PVous devez rapidement constituer une armée, en particulier un corps naval. Octave a fait le voeu de revenir en septembre de l'an 31. @PDésormais, votre sort, celui de Marc-Antoine ainsi que de l'Egypte et de Rome, dépendent de nouveau de l'efficacité militaire."
        }
    }
    message_mission_deir_el_medina {
        id: 462,
        type: 3,
        size [40, 30]
        title {
            text: "Deir el-Medineh",

        }
        subtitle {
            text: "La première tombe",

        }
        content {
            text: "@PAprès une série de brillantes victoires sur de lointains champs de bataille pour la défense des terres et du peuple d'Egypte, le pharaon Thoutmôsis s'est lancé dans les préparatifs de son voyage dans l'au-delà. Afin de garantir la réussite de ce voyage, le pharaon désire que vous commenciez la construction de sa tombe dès que possible. Vous devez donc établir un village sur la rive ouest du Nil pour assurer une main-d'oeuvre qualifiée suffisante. Vous devrez ensuite identifier un site adéquat pour l'édification de sa tombe dans les falaises à l'ouest de ce village. Vous aurez besoin de tailleurs de pierre expérimentés pour sculpter dans la roche les nombreuses chambres de la tombe, ainsi que d'artisans talentueux pour plâtrer et peindre ces pièces.   @PAfin de fournir de la lumière aux ouvriers travaillant dans les profondeurs de la tombe, vous devez établir des fabriques de lampes. Il vous faut pour cela fournir des poteries et de l'huile importée pour les alimenter. Vous devez en outre planter des champs de henné afin de procurer aux fabricants de peintures des bases de couleurs éclatantes."
        }
    }
    message_mission_tutankhamun_valley_2 {
        id: 463,
        type: 3,
        size [40, 30]
        title {
            text: "Tut dans la Vallée",

        }
        subtitle {
            text: "Mort de Toutankhamon",

        }
        content {
            text: "@PUne terrible tragédie a frappé notre jeune pharaon bien-aimé, Toutankhamon ! Son règne, autrefois si prometteur, a été ignoblement interrompu par le destin. Il est temps pour les ouvriers de Deir el-Medineh de préparer à nouveau la chambre de repos éternel du pharaon. Cette disparition subite donne un caractère urgent aux travaux et vous devez encourager les artisans à oeuvrer sans relâche. La tombe de Toutankhamon doit contenir toutes les provisions nécessaires à son voyage dans l'au-delà et être prête à recevoir sa dépouille sacrée dans un délai très court. La rapidité est d'une importance extrême !"
        }
    }
    message_mission_seti_valley_2 {
        id: 464,
        type: 3,
        size [40, 30]
        title {
            text: "Séthi dans la Vallée",

        }
        subtitle {
            text: "La tombe d'un pharaon",

        }
        content {
            text: "@PNotre plus puissant pharaon, Séthi, fils de Ramsès I, a déclaré qu'il était temps de commencer les préparatifs pour son voyage dans l'au-delà. C'est pourquoi vous devez commencer à creuser sa tombe royale dans la Vallée des Rois. Aucun effort ne doit être épargné par vos ouvriers dans ces préparatifs. Des mesures adéquates doivent être prises afin d'assurer qu'une fois l'ouvrage terminé, il sera inégalé pendant des générations. @PToutefois, à mesure que ce projet royal progresse, vous devez prendre toutes les précautions nécessaires contre les bandits ! On a déjà fait écho de bandes de criminels cherchant à s'enrichir en dépouillant les tombes, perturbant ainsi le repos éternel des pharaons d'Egypte. Vous ne devez en aucun cas laisser de tels actes déshonorer les tombes royales de la Vallée ; sinon, vous perdrez votre place au sein du royaume."
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
            text: "Terres du Levant",

        }
        content {
            text: "@PRendons grâce au gouverneur du royaume, régent du Levant et loyal sujet de notre pharaon, fils de Rê. Qu'il est heureux de vivre en ces temps où l'Egypte s'étend des confins de la Nubie jusqu'aux rivages du Levant. La sagesse de notre nouveau pharaon est infinie, Ramsès II, et sa vision est grande, car c'est lui qui vous a envoyé régner sur cette terre, qui fait aujourd'hui partie du domaine de l'Egypte.  @PCette région, toujours parsemée de dangers, recèle de nombreuses richesses à exploiter. Les collines verdoyantes regorgent de grands arbres qui produisent du bon bois, idéal pour la confection de chars et utilisable sous de multiples formes en construction. Le cuivre, que l'on trouve en abondance, est toujours fort utile pour la confection d'armes robustes. Le bois et le cuivre seront assurément les bienvenus lorsqu'ils seront rapportés en grandes quantités. Vous devrez superviser l'établissement d'un grand port de commerce à partir duquel ces biens précieux pourront être exportés. Le pharaon et le peuple d'Egypte vous en seront extrêmement reconnaissants ! @PMais attention ! Assurez-vous que vos soldats sont équipés de chars rapides et d'armes robustes, car les Hittites, bien que vaincus par Séthi, père du pharaon, sont toujours dangereux et risquent de menacer notre autorité sur ces terres. Une forte présence militaire sur ce nouveau territoire peut s'avérer nécessaire pour repousser une éventuelle insurrection, et sera sans nul doute de la plus grande utilité dans l'avenir. @PEnfin, pour rappeler aux habitants de cette région à qui ils doivent désormais rendre hommage, le pharaon Ramsès II juge approprié d'ériger un obélisque à sa gloire."
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
            text: "La bataille de Qadesh",

        }
        content {
            text: "@PLa terre d'Amurra, terminée par la côte du Levant, tremble sous les pas de vos puissantes légions, ô pharaon. Cette région comporte de rares pierres précieuses, mais elle est également riche en conflits. Les Hittites armés, conduits par le féroce roi Muwatalli, contestent de nouveau le contrôle de ces terres, qui nous appartiennent. Les espions capturés disent qu'ils se trouvent toujours bien loin au nord et qu'ils ne présentent par conséquent aucune menace. Mais doit-on les croire ? La sagesse dicte au soldat de ne jamais abaisser son bouclier au combat.   @PSuite à de telles rumeurs d'insurrection, vous, notre vénéré pharaon, Ramsès II, fils de Rê, êtes venu dans la ville fortifiée de Qadesh. Déjà, deux de vos redoutées compagnies de conducteurs de char se sont établies dans ses faubourgs. Mais ce n'est pas tout. Vous avez à votre disposition d'autres troupes d'élite, particulièrement expérimentées, récemment engagées près de Sumur. Mais attention ! Il pourrait s'avérer sage de retarder le déploiement de ces troupes jusqu'au dernier moment, car la sagesse dicte également au soldat de conserver une réserve de troupes bien entraînées pour se lancer dans le front de la bataille. @PUne fois le misérable ennemi vaincu, il sera nécessaire de raviver l'économie stagnante de Qadesh afin que cette cité puisse contribuer à la gloire de l'Egypte. Il vous faut donc recueillir des pierres précieuses en engager des orfèvres expérimentés pour fabriquer des articles de luxe pour les loyaux sujets du pharaon. Ces articles d'une rare beauté seront sans nul doute très demandés !"
        }
    }
    message_mission_abu_simbel_2 {
        id: 467,
        type: 3,
        size [40, 30]
        title {
            text: "Abou Simbel",

        }
        subtitle {
            text: "Les colosses d'Abou Simbel",

        }
        content {
            text: "@PLa gloire de notre pharaon, Ramsès II, envahit notre territoire. Ainsi, pour que l'héritage de son règne dure à jamais, un grand monument et un temple dédiés à sa gloire doivent être construits en Nubie. Le pharaon lui-même a sélectionné l'emplacement idéal pour cette création. Depuis les falaises roses qui dominent la rive ouest du Nil à Abou Simbel, vous pourrez superviser la sculpture de quatre statues assises majestueuses représentant le pharaon. Les surfaces de ce monument, sculptées dans la roche vive, illustreront les actes héroïques du pharaon durant la bataille de Qadesh. Ce monument gigantesque, tout en célébrant la bravoure de notre chef, rappellera également aux peuples de Nubie la grandeur et la puissance de l'Egypte. En effet, si la Nubie est riche en dépôts d'or et d'autres pierres précieuses rares, ses habitants ont toujours mal supporté la domination égyptienne. Vous devez donc vous préparer à vous défendre, et vous apprêter à envoyer des troupes pour venir en aide au pharaon. @PLe grès peut être exporté pour la construction dans d'autres régions du royaume, tout comme d'autres articles que vous pouvez obtenir grâce aux abondantes ressources de la région. Le bois précieux est rare, toutefois. Vous devrez sans nul doute établir une route de commerce pour importer cette denrée, qui sera nécessaire pour construire l'immense échafaudage de la sculpture."
        }
    }
    message_mission_ramses_valley_2 {
        id: 468,
        type: 3,
        size [40, 30]
        title {
            text: "Ramsès dans la Vallée",

        }
        subtitle {
            text: "Une tombe sans égale",

        }
        content {
            text: "@PDe longues et glorieuses années se sont écoulées depuis que notre pharaon, le vénéré Ramsès II, a accepté de succéder à son père, Séthi I. Avec la bénédiction de Rê, il continuera à régner pendant longtemps encore. Il est temps cependant de commencer les préparatifs du lieu de repos éternel de notre chef vénéré. Il a fourni à votre architecte un plan pour construire une grande tombe telle qu'il n'en a jamais édifiée, surpassant même celle de son seigneur. Il vous incombe désormais de veiller que cette requête royale soit menée à bien. @PMais attention ! Il règne un fort climat de trouble chez certains ouvriers et esclaves épris d'indépendance, dans la région tout comme en Basse Egypte. Ils suivent l'exemple d'un homme autrefois membre de la cour de notre pharaon, et ils ont menacé de faire appel à leur dieu pour une intervention divine. Ils espèrent qu'avec cette aide sacrée, ils arriveront à leurs fins. Aujourd'hui, prêtres et hommes de foi étudient cette menace. Tandis que nous attendons patiemment leur verdict, il convient de nous préparer à l'inattendu."
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
            text: "Henné",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Pendant plus de trois millénaires, différents peuples ont utilisé le henné pour fabriquer de la teinture. Le henné (dont le nom scientifique est Lawsonia inermis) est de la famille des lythracées et est originaire d'Afrique du Nord et du Moyen-Orient. Ses feuilles et ses branches, une fois écrasées, produisent une teinture rouge-orangée qui, lorsqu'on l'applique correctement, peut être utilisée pour la coloration des cheveux, des ongles et de la peau. Le henné est encore aujourd'hui fréquemment employé dans de nombreux rites religieux et funéraires en Asie, Moyen-Orient et Afrique. Il constitue l'élément de base de la coloration d'une grande partie des 'tatouages' populaires, ainsi que de la coloration des cheveux."
        }
    }
    message_mission_paint_maker {
        id: 470,
        
        size [30, 28]
        title {
            text: "Fabrique de peinture",
        }
        content {
            text: "Pour assurer leur production, les fabriques de peinture ont besoin de @469henné. Les feuilles et les tiges écrasées du henné servent à produire différentes teintures, nécessaires à la fabrication de peintures. Le henné pousse dans des @91exploitations&de&henné. On peut également établir une @47route&de&commerce pour son importation.  @PDès qu'une fabrique de peinture reçoit suffisamment de commandes, bénéficie d'un accès routier et dispose d'une quantité suffisante de henné, les fabricants de peinture se mettent à l'ouvrage. Une fois la production terminée, la peinture est livrée à un @4entrepôt&. Elle est ensuite utilisée par des @363artisans pour peindre les @478Tombes&Royales. @PEn raison de l'odeur et du bruit désagréables qu'elles dégagent, les fabriques de peinture sont des structures de proximité @56indésirables. @L@LCliquez @472ici pour en savoir plus sur la fabrication de la peinture dans l'Egypte ancienne."
        }
    }
    message_illness_video {
        id: 471,
        type: 2,
        
        size [30, 20]
        title {
            text: "Maladie",
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
            text: "Histoire",
        }
        content {
            text: "Si la construction de la plupart des monuments dans l'Egypte ancienne exigeait l'intervention d'artistes, c'est dans les tombes du Nouvel Empire de la @475Vallée&des&rois que le talent de ces artistes est le plus éclatant. Pratiquement chaque mètre carré des murs intérieurs et des plafonds de ces tombes souterraines illustre la grandeur des défunts, notamment à travers des hiéroglyphes peints avec la plus grande habileté. @PMalgré l'extravagance et le sens du détail que l'on peut lire dans leurs illustrations, les artistes de l'Egypte ancienne possédaient une palette de couleurs extrêmement limitée et utilisaient des pinceaux naturels en @94roseaux ou en bois fibreux, comme celui des palmiers. Leurs pigments étaient souvent mélangés dans de petites boutiques où on les fabriquaient à partir de teintures naturelles (telles que le @469henné) et d'autres pigments naturels (tels que le carbonate de calcium, le charbon de bois, l'oxyde de fer, et la malachite) en poudre. Ces composants peuvent alors être mélangés à l'aide d'un agent (tel que le caoutchouc ou la colle), avant d'être appliqués comme peinture. @PDe nombreux artistes spécialisés oeuvraient de concert pour créer de magnifiques bas-reliefs dans les tombes. Le plâtre était d'abord préparé à partir d'un mélange d'@190argile, d'eau et d'un agent blanchissant, puis appliqué sur les murs de la tombe. Une esquisse était ensuite tracée en rouge sur les murs fraîchement plâtrés. Ensuite, un dessinateur expérimenté affine cette esquisse, généralement en noir. Un peintre expérimenté apporte ensuite quelques corrections et ajoute des détails pour guider le sculpteur qui va lui succéder. La peinture est ensuite appliquée en couches de couleurs mattes. La finition des contours et des détails intérieurs est alors réalisée par un autre expert."
        }
    }
    message_building_lamp_maker {
        id: 473,
        
        size [30, 28]
        title {
            text: "Fabrique de lampes",
        }
        content {
            text: "Le fabricant de lampes prépare les lampes qui aideront les travailleurs à trouver leur chemin dans les sombres couloirs d'une @478tombe&royale.  @PDans le cadre de ses activités, le fabricant a besoin d'une réserve de poteries et d'huile. Un @1potier peut fournir la poterie ou celle-ci peut être importée par l'intermédiaire d'un @47partenaire&commercial. @476L'huile doit être importée. @PUne fabrique de lampes doit disposer d'un accès routier et d'une source de main d'oeuvre proche. Lorsqu'elle dispose d'une quantité suffisante de poteries et d'huile, ses ouvriers se mettent activement à l'oeuvre et versent l'huile dans les poteries pour confectionner les lampes. @PLa présence des fabricants de lampes a un effet négatif sur l'@56attrait d'une cité. Il est par conséquent déconseillé de les implanter trop près des habitations. @L@LCliquez @474ici pour en savoir plus sur les lampes dans l'Egypte ancienne."
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
            text: "Lampes",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens anciens fabriquaient de petites lampes en céramique qui consommaient des @476huiles naturelles ou de la graisse animale. Ces lampes fournissaient l'éclairage nécessaire pour les artisans qui travaillaient dans les tombes."
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
            text: "La Vallée des rois",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "@PLa Vallée des rois fut durant cinq siècles la nécropole des pharaons, entre 1539 et 1075 av. J.-C., dont Thoutmôsis I, Toutankhamon et Ramsès le Grand (Ramsès II). Située sur la rive ouest du Nil, le long de l'ensemble de temples de Thèbes, la Vallée des rois est surplombée par el-Qurn, une montagne ayant presque la forme d'une pyramide qui reçoit les dernières bénédictions de Rê chaque jour avant le coucher du soleil. Entre la Vallée et le Nil se trouvent les temples funéraires royaux érigés en l'honneur des pharaons destinés à passer leur vie de l'au-delà dans les tombes de la Vallée. Deir el-Medineh, un village proche, regroupait des centaines d'ouvriers et leurs familles. @PCes ouvriers, dont les spécialités étaient consacrées aux tâches importantes, préparaient les tombes du royaume et étaient des spécialistes en tâches importantes. Les @385tailleurs&de&pierre creusaient des marches et des galeries dans les falaises de grès. Ils édifiaient des piliers en pierre pour maintenir le plafond des grandes chambres. Les salles taillées étaient lissées et plâtrées avant que les @472artisans ne viennent décorer les plafonds et les murs de bas-reliefs et de peintures qui guideraient le pharaon dans l'au-delà. On plaçait le roi défunt dans son sarcophage, scellé dans la tombe en compagnie de nombreux trésors en l'honneur du statut de divinité que lui attribuaient les Egyptiens anciens. A cause de ces grands trésors, les tombes étaient fréquemment pillées, parfois même par les personnes chargées de les garder. @PLes archéologues européens ont redécouvert la Vallée des rois au début du XIXème siècle. En 1922, Howard Carter a pénétré dans la tombe scellée de Toutankhamon et y a trouvé de nombreux trésors, dont un sarcophage en or. Au cours des siècles, des inondations ont rempli une grande partie des tombes de vase et de débris. On peut supposer qu'il reste des galeries, voire même des tombes, à découvrir dans la Vallée."
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
            text: "Huile",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "La plupart des huiles utilisées par les Egyptiens anciens étaient importées de Grèce, Chypre ou de Phénicie. Les huiles naturelles avaient de nombreux usages, notamment l'alimentation des @474lampes et la cuisine. Ces huiles étaient extraites de diverses sources, telles que le sésame, les graines de lin, les olives et les graisses animales naturelles (dont la plupart sont encore utilisées aujourd'hui)."
        }
    }
    message_figure_tomb_robber {
        id: 477,
        
        size [30, 28]
        title {
            text: "Les pilleurs de tombes",
        }
        content {
            text: "@PS'il y a une tombe, il y a un trésor ! Un pilleur de tombes est un criminel qui fait son apparition lorsque l'@39attrait&de&la&cité est extrêmement faible. Cependant, il frappe la cité uniquement si elle contient des trésors à piller. Ainsi, si votre cité n'abrite aucune tombe (pyramide, @371mastaba, @368mausolée ou @478tombe&royale), le pilleur restera inactif. Il en sera de même s'il ne peut voler aucune @374offrande&funéraire, soit parce que la tombe ne devait pas en contenir, soit parce qu'elles n'ont pas encore été acheminées vers la tombe. @PIl arrive que les pilleurs de tombes sévissent alors que la cité ne connaît aucune criminalité. Si des pilleurs de tombes professionnels apprennent de leurs acolytes que les tombes de votre cité renferment de somptueuses offrandes funéraires, ils déclencheront une nouvelle vague de criminalité. Vous ne pouvez pas prévoir ces vagues de criminalité.  @PLes pilleurs de tombes n'ont qu'une idée en tête : dérober les richesses et les trésors qui avaient été déposés dans la tombe du pharaon défunt pour son voyage dans l'au-delà. Pour mettre son plan en application, le pilleur de tombes doit arriver à la tombe sans se faire appréhender. S'il rencontre un agent ou des soldats en chemin, il est normalement interpellé sans problème, mais un voleur extrêmement agile saura toujours s'échapper. Si le pilleur parvient à une tombe, il pourra emporter une partie des offrandes funéraires et votre @35niveau&de&royaume en sera affecté ; en effet qui souhaiterait être gouverné par une personne incapable de protéger les tombes sacrées de ses ancêtres ? @PLes pilleurs de tombes ne sont pas difficiles quant à leur choix. Ils peuvent très bien essayer de piller un monument déjà construit dans la cité avant votre arrivée au pouvoir. Heureusement, ces tombes sont bien scellées et le pilleur de tombes risque fort de rentrer bredouille. Cependant, les citoyens d'Egypte verront d'un mauvais oeil cette menace qui a plané sur l'une de leurs plus anciennes tombes et votre niveau de royaume en pâtira. @PAttention ! Si un pilleur de tombes s'enfuit avec des offrandes funéraires, vous devez remplacer chacun des éléments volés afin de pouvoir poursuivre votre mission. @PPour plus d'informations sur la criminalité dans votre cité, cliquez @36ici. @L@LPour en savoir plus sur les tombes de la Vallée des rois dans l'Egypte ancienne, cliquez @475ici."
        }
    }
    message_building_royal_burial_tomb {
        id: 478,
        
        size [30, 28]
        title {
            text: "Les tombes royales",
        }
        content {
            text: "@PAu Nouvel Empire, les Egyptiens anciens commencèrent à enterrer leurs pharaons et les autres membres de la noblesse dans des tombes de plus en plus élaborées sculptées dans la roche vive d'une vallée presque inaccessible. @PPour que le travail puisse commencer sur une Tombe Royale, vous devez dans un premier temps trouver un site approprié. Cliquez sur le bouton Structures religieuses et sélectionnez 'Tombe royale' dans le sous-menu Monuments. Une grande empreinte apparaît. La plus grande partie du monument doit être placée sur les falaises, sauf la petite entrée qui pointe sur le côté. Déplacez l'icône sur les falaises jusqu'à ce que vous trouviez l'emplacement approprié. Si l'icône devient verte, l'emplacement choisi convient. Si elle reste rouge, l'emplacement ne permet pas la construction du monument. @PIl vous sera peut-être plus facile de placer la Tombe Royale en aplanissant provisoirement les falaises. Appuyez sur 'H' pour aplanir les falaises ou choisissez 'Masquer falaises' dans la liste des @18cartes. Pour rétablir le relief des falaises, appuyez de nouveau 'H' ou sélectionnez 'Normal' dans la liste des cartes. Si la tombe est particulièrement volumineuse, la touche 'M' pourra se révéler fort utile. En effet, une pression sur la touche 'M' fige l'icône à sa place et vous pouvez alors déplacer votre point de vue pour vérifier si vous avez choisi un site approprié. Si tel est le cas, cliquez pour placer le monument. Dans le cas contraire, appuyez de nouveau sur 'M' pour libérer l'icône et poursuivre la recherche du site approprié. @PUne fois le site sélectionné, il faut acheminer la livraison de lampes vers la tombe avant le début des travaux. Les lampes sont fabriquées par un @473fabricant&de&lampes et peuvent également être importées auprès d'une @47partenaire&commercial. Lorsqu'un @4entrepôt contient 400 lampes, un paysan amène un traîneau rempli de lampes sur le site de construction. @PLorsqu'ils disposent des lampes pour s'éclairer, les @363menuisiers taillent les diverses chambres de la tombe dans la pierre. Une fois ce travail terminé, c'est au tour des @363artisans qualifiés de venir plâtrer et peindre les murs. Ces artisans auront besoin d'@92argile pour fabriquer le plâtre et de peinture fournie par une @470fabrique&de&peintures. Les marchandises seront directement livrées à la guilde des artisans soit par les fabricants, soit depuis un entrepôt. Si votre cité ne peut pas produire l'une de ces marchandises, voire les deux, vous pourrez peut-être les @47importer. @PCliquez avec le bouton droit de la souris sur une Tombe Royale pour rencontrer le @369contremaître afin qu'il vous informe sur la progression des travaux. @L@LCliquez @475ici pour en apprendre plus sur la Vallée des Rois et ses Tombes Royales."
        }
    }
    message_building_zoo {
        id: 479,
        
        size [30, 28]
        title {
            text: "Zoos",
        }
        content {
            text: "Les zoos constituent une forme populaire de @49loisirs dans n'importe quelle cité. Le zoo doit disposer d'une route d'accès, de la main d'oeuvre nécessaire pour s'occuper des animaux, ainsi que d'une réserve suffisante de @89paille et de @359gibier. La paille peut être récoltée par les exploitations de céréales, et les chasseurs des pavillons de chasse peuvent se charger de l'approvisionnement en gibier. Vous pouvez également ouvrir une @47route&de&commerce pour importer ces marchandises. @PVous devez consulter votre @28chef&des&loisirs pour savoir combien de zoos votre cité compte et utiliser la @18carte&des&loisirs pour savoir quelles habitations ont accès au zoo et observer les déplacement des gardiens du zoo dans la cité. @PMalgré les distractions uniques que recèle un zoo, les habitants n'apprécient guère de vivre à proximité de tels lieux, car le bruit assourdissant et les fortes odeurs qui émanent des animaux sont particulièrement gênants pour les Egytpiens cultivés. Cliquez @56ici pour en savoir plus sur l'attrait. @L@LPour en savoir plus sur les zoos dans l'Egypte ancienne, cliquez @480ici."
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
            text: "Histoire",
        }
        content {
            text: "Les Egyptiens anciens raffolaient de tout ce qui était divertissant et inhabituel, deux qualités que l'on trouvait en abondance dans un zoo. A mesure que la puissance et l'influence de l'Egypte s'étendaient sur plusieurs continents, de nombreux pharaons recevaient des créatures étranges et exotiques en cadeau ou tribut de la part de dirigeants de pays lointains. Ces animaux étaient présentés au pharaon, puis enfermés dans des jardins zoologiques particuliers, à proximité du palais du pharaon. Manifestement, les premiers zoos égyptiens étaient destinés en priorité aux manifestations publiques et en second lieu à l'étude. La grande bibliothèque d'Alexandrie possédait un jardin botanique et un jardin zoologique."
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
            text: "Alexandrie et sa bibliothèque",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Dès le début, Alexandre le Grand espérait qu'Alexandrie, la cité qu'il avait fondée à l'estuaire du Nil et qu'il avait en partie dessinée, deviendrait un centre du commerce et de la culture pour le bassin méditerranéen. Moins de cinquante ans après sa fondation en 331 av. J.-C., cette métropole florissante était devenu un important pôle commercial, grâce notamment à la renommée de sa grande bibliothèque.  @PPeu après la mort prématurée d'Alexandre en 323 av. J.-C., son empire étendu se sépara en trois régions principales. L'un de ses meilleurs amis et de ses généraux les plus habiles, Ptolémée, devint alors de facto gouverneur d'Egypte. Il prit le contrôle de cette terre ancienne, avant de devenir pharaon (sous le nom de Ptolémée I Sôter). Il perpétua ainsi la présence grecque en Egypte instaurée par Alexandre. Ce fut Ptolémée qui intercepta la procession funèbre d'Alexandre, qui partait en direction de la Macédoine, et ramena sa dépouille à Alexandrie pour lui rendre les derniers honneurs.  @POutre la gloire personnelle et la vie luxueuse, cependant, les premiers chefs ptolémaïques portaient également un intérêt à l'amélioration de la vie culturelle de leur cité. Alexandrie, nouvelle capitale de l'Egypte, était déjà le centre du commerce mondiale ; les souverains souhaitaient qu'elle devienne également la capitale intellectuelle du pays. La grande bibliothèque d'Alexandrie fut construite dans ce but. Ce bâtiment fut le premier centre mondial universitaire dédié à l'apprentissage et à la recherche. C'est là que les brillants esprits de l'antiquité bâtirent les fondations de l'étude systématique de l'astronomie, de la géographie, de la littérature, des mathématiques, de la médicine et des sciences physiques. C'ést là qu'Euclide définit pour la première fois la géométrie et qu'Eratosthène mesura avec exactitude la circonférence de la terre, arrivant à la conclusion que l'on pouvait rejoindre l'Inde par voie maritime en naviguant à l'ouest de l'Espagne. @PLes dirigeants ptolémaïques utilisèrent beaucoup de temps et d'énergie, ainsi qu'une part non négligeable de leur fortune, pour obtenir des copies de chaque manuscrit important. C'est pourquoi une loi fut adoptée, proclamant que chaque caravane et chaque navire qui pénétrait à Alexandrie devait être fouillé, non pas pour découvrir une éventuelle contrebande, mais pour trouver des éléments de savoir. Toute carte ou parchemin trouvé était envoyé à la bibliothèque afin que les scribes puissent les copier. Ainsi, le temple du savoir rassemblait plus de 700 000 rouleaux de papyrus, soigneusement classés, dont une grande partie de chefs-d'oeuvre, aujourd'hui perdus, d'art, de littérature et de sciences, tels que les oeuvres classiques d'Homères, Aristote, Sophocle, Achylle et Euripide.  @PMais le savoir n'était pas tout. Le site de la légendaire bibliothèque abritait également un jardin botanique et un musée, ainsi qu'un temple en l'honneur des neuf muses (dieux et déesses grecs des arts et des sciences). Une promenade cheminait le long d'une palissade verdoyante et emmenait les visiteurs jusqu'au @480zoo qui renfermait une multitude d'espèces animales exotiques. Nombreux étaient les anciens érudits qui traversaient ces lieux.  @PLes cicronstances de la fermeture de la grande bibliothèque ne sont pas complètement élucidées. Il est certain qu'une bonne partie de ses oeuvres inestimables fut détruite dans un incendie qui eut lieu lorsque Jules César mit le feu aux navires du frère de Cléopâtre VII. Aux alentours du quatrième siècle ap. J.-C., alors que l'influence de la chrétienté était en pleine expansion, la plupart des manuscrits épargnés furent détruits manifestement dans une tentative pour anéantir tous les vestiges du paganisme et de l'hérésie. Plus tard, en 640 ap. J.-C., les Arabes qui parcoururent la cité presque abandonnée brûlèrent tous les parchemins qui avaient survécu, probablement poussés par une pénurie de bois de chauffage. Sur les 123 pièces de Sophocle qui se trouvaient dans la grande bibliothèque, seules sept subsistent aujourd'hui."
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
            text: "Histoire",
        }
        content {
            text: "Cléopâtre VII commença le Caesareum. Il était à l'origine composé d'un petit temple ou autel au milieu d'un sanctuaire, apparemment dédié au culte de Marc-Antoine. Suite à son suicide, suivi peu après par la mort de Cléopâtre, cependant, ce monument fut achevé par leur rival, Octave (Auguste César), qui dédia cet édifice à son propre culte. Deux obélisques (communément appelées aiguilles de Cléopâtre, bien que le rapport entre les deux soit obscur), se dressèrent pendant plusieurs siècles comme deux points de repère le long de la côte est du port d'Alexandrie. Ces obélisques, transportés jusqu'à Alexandrie depuis Héliopolis sous les ordres d'Octave, marquaient l'entrée dans le Caesareum bien après que le reste de ce monument avait été détruit. Les deux obélisques ont aujourd'hui été déplacés (l'un se trouve à Central Park à New-York, l'autre sur les rives de la Tamise à Londres). @POn ne possède aucun détail précis sur la structure actuelle du Caesareum. Notre connaissance de ce monument nous vient de descriptions sommaires de la part d'auteurs antiques. Son architecture, comme celle des autres grands monuments d'Alexandrie, était de style grec. Il contenait un sanctuaire central érigé au milieu de cours extérieures et entouré de passages piétonniers à colonnes qui servaient vraisemblablement de 'murs' extérieurs. Les salles et les portiques construits au milieu de ces passages contenaient des manuscrits et pouvaient servir de lieux de réunion ou de salles d'étude."
        }
    }
    message_plague_of_locusts {
        id: 483,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Attaque de criquets",
        }
        content {
            text: "Des nuées de criquets déciment les cultures à travers toute l'Egypte. Veillez à ce qu'ils n'anéantissent pas la prochaine récolte !"
        }
    }
    message_plague_of_frogs {
        id: 484,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Attaque de grenouilles",
        }
        content {
            text: "Un mauvais sort s'est abattu sur nos terres ! Une multitude de grenouilles polluent nos rues et nos habitations, forçant les résidents à chercher refuge ailleurs."
        }
    }
    message_hailstorm {
        id: 485,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Orage de grêle",
        }
        content {
            text: "La mort et la destruction sont dans l'air ! Un violent orage de grêle s'est abattu sur nous, avec son cortège d'eau glacée. Puissent les dieux avoir pitié de ceux qui n'ont pas d'abri, car leurs chances de survie sont très minces !"
        }
    }
    message_river_of_blood {
        id: 486,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Fleuve de sang",
        }
        content {
            text: "Malheur à nous ! Les eaux, autrefois source de vie et de nutriments, sont empoisonnées de sang. Combien de temps faudra-t-il pour mettre fin à ce fléau ?"
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
            text: "Phare de Pharos",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "@PSi l'emplacement d'Alexandrie était idéal pour l'établissement d'un port de commerce, grâce à une côte importante et un vaste port naturel, l'endroit regorgeait de redoutables bancs de sable. On conçut donc un grand phare sur l'île de Pharos, près de l'embouchure du port, non seulement pour la sécurité des marins, mais également pour constituer un nouveau pôle d'attraction destiné à étendre la renommée d'Alexandrie.  @PLe phare de Pharos, c'est son nom, fut en partie construit en marbre blanc, provenant principalement des îles du prince, au large de la côte turque. Il fut construit en trois grands niveaux : la base, ou étage inférieur, était quadrangulaire ; l'étage du milieu était octogonal ; l'étage supérieur était cylindrique. Un escalier monumental en spirale menant au sommet permettait aux animaux d'acheminer du bois en haut du bâtiment pour alimenter le feu qui brûlait dans cette structure. On dit qu'une statue de Poséidon surplombait l'ensemble du monument ; pour d'autres, il s'agissait d'une représentation de Zeus, ou peut-être encore d'une statue représentant ces deux personnages. @PLa construction du phare de Pharos à Alexandrie commença sous le règne du premier souverain ptolémaïque (Auletes), mais ne fut achevée qu'en 283 av. J.-C., durant le règne de son fils, Ptolémée Philadelphus. On rapporte que ce bâtiment était spectaculaire, et qu'il mérite bien plus que le statut de septième merveille du monde antique. @PLa fermeture définitive de ce monument fut le fait non pas de l'homme, mais d'une série de séismes qui ravagèrent la région. Ces tremblements de terre culminèrent en 303 ap. J.-C. Ce ne fut toutefois que le 8 août 1303 que la plus grande partie des structures rescapées furent détruites, submergées par les eaux alentour. Aujourd'hui, un fort, construit par le sultan Bey, se dresse sur l'île de Pharos, à l'endroit où le phare se trouvait autrefois."
        }
    }
    message_building_alexandria_library {
        id: 488,
        
        size [30, 28]
        title {
            text: "La Bibliothèque d'Alexandrie",
        }
        content {
            text: "Les érudits et autres savants du monde entier affluent à Alexandrie pour visiter sa grande bibliothèque, le plus grand dépôt de savoir de l'humanité. @PPour construire la Bibliothèque d'Alexandrie, vous devez dans un premier temps sélectionner un site approprié. Choisissez la Bibliothèque d'Alexandrie dans la liste des monuments des structures religieuses. Si l'icône est entièrement verte, l'emplacement choisi est correct.  @PPour construire la Bibliothèque d'Alexandrie, vous aurez besoin du concours des paysans travaillant dans les @8chantiers, des tailleurs de pierre appartenant aux @363guildes&de&tailleurs&de&pierre et des menuisiers appartenant aux @363guildes&de&menuisiers. Pour construire les échafaudages, les menuisiers auront besoin de @94bois que vous pouvez importer si votre cité n'en produit pas. Vous devrez également @47importer du marbre blanc auprès de l'un de vos partenaires commerciaux. Pour la finition du monument, vous aurez besoin de @93cuivre, que vous pourrez vous procurer soit dans les mines de votre cité, soit auprès d'un partenaire commercial. @PCliquez avec le bouton droit de la souris sur la Bibliothèque d'Alexandrie en construction pour voir le rapport d'avancement du @369contremaître. @L@PCliquez @481ici pour en savoir plus sur l'histoire de la grande Bibliothèque d'Alexandrie."
        }
    }
    message_building_pharos_lighthouse {
        id: 489,
        
        size [30, 28]
        title {
            text: "Le phare de Pharos",
        }
        content {
            text: "Le phare spectaculaire de Pharos à Alexandrie guide, de jour comme de nuit, les marins lors de la traversée des dangereux bancs de sable de son port. @PLe phare de Pharos ne peut être construit que sur le sol rocheux de l'île de Pharos dans le port d'Alexandrie. Cliquez sur Structures religieuses et sélectionnez 'Phare de Pharos' dans le sous-menu Monuments, puis placez le curseur sur le sol rocheux (sur l'île de Pharos) à proximité de l'entrée du port. Une fois que l'empreinte du monument apparaît entièrement en vert, cela signifie que vous avez trouvé un site approprié pour supporter le lourd poids de cette structure. @PUne fois que le sol est libre, vous avez besoin de marbre importé. Vous pouvez obtenir cette denrée via une @47route&de&commerce reliant Alexandrie à une autre cité. Les @363tailleurs&de&pierre appartenant à une guilde de tailleurs de pierre vont soigneusement mettre en place le marbre blanc que les paysans d'un @8chantier amènent d'un @4entrepôt. Les paysans acheminent le marbre blanc lorsque qu'un même entrepôt contient au moins quatre blocs. Ils auront également besoin de @363menuisiers appartenant à une guilde de menuisiers et de @94bois pour installer les échafaudages nécessaires à la construction. @PCliquez avec le bouton droit de la souris sur le phare de Pharos en construction pour voir le rapport d'avancement du @369contremaître. @L@LCliquez @487ici pour en savoir plus sur le phare de Pharos à Alexandrie."
        }
    }
    message_building_caesareum {
        id: 490,
        
        size [30, 28]
        title {
            text: "Le Caesareum",
        }
        content {
            text: "L'un des plus grands chefs d'oeuvre de l'architecture d'Alexandrie est le Caesareum, un gigantesque temple en bord de mer qui accueille les navires s'engageant dans le grand port d'Alexandrie. @PPour construire le Caesareum, commencez par le sélectionner dans la liste des monuments des structures religieuses du Panneau de configuration. Vous voyez alors une icône du bâtiment. Cherchez un terrain d'une taille suffisante et implantez-y le monument. Vous savez que l'emplacement est bon lorsque l'icône vire totalement au vert.  @PUne fois le site adéquat trouvé, la construction peut commencer. Les paysans du @8chantier commencent par défricher le terrain pour exposer la roche sous-jacente. Lorsque le terrain est défriché, les @363tailleurs&de&pierre représentant une guilde de tailleurs de pierre viennent mettre en place le marbre blanc que les paysans amènent d'un @4entrepôt. Vous devez @47importer le marbre blanc auprès d'un partenaire commercial. Les paysans amènent le marbre blanc sur le site de construction dès qu'un entrepôt en contient quatre blocs. @PIl faudra également s'assurer le concours des @363menuisiers représentant une guilde de menuisiers approvisionnée en @94bois pour construire les échafaudages. Si votre cité ne dispose pas de sa propre réserve de bois, vous devrez en importer. A la fin du projet, il vous faudra également prévoir une réserve de granit que vous pourrez prélever dans un entrepôt ou importer, si votre cité ne peut pas en @95produire. @PSi vous cliquez avec le bouton droit de la souris sur le Caesareum pendant la construction, son @369contremaître vous informera de la progression des travaux."
        }
    }
    message_crime_wave {
        id: 491,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Vague de criminalité",
        }
        content {
            text: "Puissent les dieux avoir pitié de nous ! Une bande de féroces criminels assoiffés de richesses a pris notre cité comme cible. Arrêtez-les avant que les trésors de notre cité ne soient à jamais perdus."
        }
    }
    message_building_abu_simbel {
        id: 492,
        
        size [30, 28]
        title {
            text: "Abou Simbel",
        }
        content {
            text: "@PLe temple d'Abou Simbel est un monument imposant que Ramsès II fit creuser dans les falaises de grès surplombant le Nil en Nubie. @PPour commencer la construction du temple d'Abou Simbel, sélectionnez-le dans la liste des monuments des structures religieuses. Une icône du monument apparaît. La majeure partie du monument doit être construite dans la falaise. L'entrée qui dépasse du côté du monument doit être construite sur un terrain dégagé. Lorsque l'icône devient entièrement verte, l'emplacement choisi convient à la construction. Cliquez pour mettre le monument en place. @PLorsque vous recherchez un emplacement convenable pour le monument, vous pouvez masquer les falaises. Appuyez sur 'H' pour aplanir les falaises ou choisissez 'Masquer falaises' dans la liste des @18cartes. Pour rétablir le relief des falaises, appuyez de nouveau 'H' ou sélectionnez 'Normal' dans la liste des cartes. @PUne fois le site approprié choisi, vous aurez besoin d'une main-d'oeuvre compétente qui, sous les ordres de @363tailleurs&de&pierre appartenant à une guilde de tailleurs de pierre et de @363menuisiers représentant une guilde de menuisiers, devra tailler la pierre et installer les échafaudages. Pour ces échafaudages, les menuisiers auront besoin de @192bois que vous pouvez importer par le biais d'une @47route&de&commerce ou faire ramasser dans un @94chantier de bois. @PCliquez avec le bouton droit de la souris sur le monument d'Abou Simbel pour que le @369contremaître vous informe de la progression des travaux. @L@LCliquez @493ici pour en savoir plus à propos du monument le plus connu de Ramsès II."
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
            text: "Abou Simbel",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "@PRamsès le Grand (Ramsès II) régna sur l'Egypte de 1279 à 1212 av. J.-C. Ce pharaon, qui a vécu vieux, est célèbre pour les nombreux temples et autres monuments qui furent construits sous son règne, le plus connu étant le temple d'Abou Simbel.   @PA environ 350 kilomètres au sud de Waset (Thèbes), dans la province de Nubie, les tailleurs de pierre de Ramsès ont sculpté une série de quatre statues assises du pharaon dans les falaises de grès rose surplombant la vallée du Nil. Chacune de ces statues mesure plus de 20 mètres de haut ; seul le Grand Sphinx de Giza les dépasse. Ces statues assises se trouvent à côté de l'entrée d'un tunnel qui mène à un sanctuaire souterrain construit 50 mètres sous la falaise. Le temple fait face à l'est et fut conçu pour que la lumière du soleil levant éclaire la façade arrière à l'intérieur du sanctuaire, illuminant trois statues de taille inférieure représentant Ramsès, Amon et Rê. Ce sanctuaire renferme également une statue de Ptah, qui, étant associée au monde souterrain, est positionnée de telle façon que la lumière du soleil ne l'inonde pas. Les reliefs qui se trouvent à l'intérieur du temple rappellent les victoires de Ramsès. A proximité, un temple similaire creusé dans les falaises honore la déesse Hathor et la première femme de Ramsès, la reine Néfertari. Cet ensemble architectural devait revenir aux sujets de Nubie afin d'encourager leur culte.   @PLe temple d'Abou Simbel fut achevé en 1256 av. J.-C. Au cours des millénaires, les sables l'ont recouvert. En 1817, l'archéologue Giovanni Belzoni découvrit cet imposant monument. Menacé d'être à nouveau recouvert au milieu des années 1960, cette fois-ci par les eaux s'élevant derrière le tout récent barrage d'Assouan, le temple d'Abou Simbel fut détaché de la falaise et reconstruit avec une grande précision sur un terrain plus élevé, une prouesse qui n'aurait pas impressionné les Egyptiens anciens."
        }
    }
    message_tutorial_major_plagues {
        id: 494
        
        size [30, 28]
        title { text: "Grands fléaux" }
        content { text: "La taille et la richesse d'une cité ne la protègent pas contre les nombreuses calamités qui peuvent s'abattre sur elle, en particulier les grands fléaux. Notez que la @53peste n'est pas considérée comme un grand fléau. Elle frappe une cité dont l'hygiène est particulièrement mauvaise. Les grands fléaux peuvent se déclencher sans raison particulière.  @PTous les grands fléaux font chuter l'@39opinon des habitants à votre égard. Les autres conséquences de ces événements sont décrites ci-dessous : @L@LFleuve de sang @LLorsque le fleuve de sang frappe la cité, l'eau du fleuve et des autres points d'eau se transforme en sang. Elle n'est donc plus @44potable ni utilisable pour d'autres usages. L'eau stockée dans les maisons peut également être contaminée et souillée. Les riverains du fleuve sont ceux qui en pâtiront le plus. Les personnes habitant près de l'eau sont davantage exposées aux maladies et au paludisme (pour plus de détails sur les maladies et le paludisme, voir @53hygiène&de&ville).Les @84quais&de&pêche, les @59porteurs&d'eau, les @94cueilleurs&de&roseaux, les @62puits et les @61points&d'eau cesseront de fonctionner tant que le fléau sévit. Si @354Bastet est en colère, il peut faire abattre ce fléau sur votre cité. Le fléau peut aussi apparaître sans raison apparente. @L@LGrenouilles @LLorsque les grenouilles attaquent votre cité, elles passent vos frontières par légions et infestent chaque maison qu'elles visitent. Personne ne peut vivre dans une maison infestée par les grenouilles et les habitants sont forcés à l'exil, sans pouvoir revenir pendant quelques mois. Vous pouvez essayer de contenir les grenouilles en construisant des murs ou en positionnant des bâtiments de façon stratégique pour les enfermer. @352Ptah utilise parfois ce fléau pour vous punir si vous le mécontentez. Les grenouilles peuvent également attaquer sans raison particulière. @L@L Orage de grêle @LLes grêlons mortels sont le fruit des averses de grêle, qui peuvent tuer quiconque se promène dans votre cité. Les grêlons ne font aucune différence : ils peuvent toucher les soldats (même les ennemis) et les animaux autant que les citoyens ordinaires. Les averses de grêle provoquent également de violentes turbulences sur le Nil et peuvent faire chavirer de nombreuses embarcations. Si vous négligez @353Seth, il peut répandre la terreur dans votre cité de cette manière-là. Les averses de grêle sont également un phénomène météorologique naturel.  @L@LCriquets @LLes criquets envahissent le pays et dévorent toutes les cultures de vos @45fermes. Les cultures de la plaine inondable et de la prairie seront complètement détruites avant la récolte, privant ainsi votre cité de précieuses ressources. Si vous avez contrarié @350Osiris, ce dernier peut vous punir à l'aide de ce fléau. Les criquets apparaissent parfois sans raison apparente. @L@LPour en savoir plus sur les fléaux qui frappaient la terre des pharaons, cliquez @495ici." }
    }
    message_history_major_plagues {
        id: 495,
        
        size [30, 20]
        image {
            id: 1010,
            pos [15, 15]
        }
        title {
            text: "Fléaux",
            pos [125, 15]
        }
        subtitle {
            text: "Histoire",
        }
        content {
            text: "Au 13ème siècle av. J.-C., sous les règnes de Séthi I et de son fils Ramsès le Grand (Ramsès II), les Hébreux d'Egypte travaillaient en esclavage sur des projets de construction. Selon le Livre de l'Exode de la Bible, Dieu apparut à l'un de ses enfants d'Israël, le prophète Moïse, et promit de libérer ce peuple. Ainsi guidé par Dieu, Moïse fit appel au pharaon pour libérer son peuple à dix occasions, et Ramsès refusa à chaque fois. Chacun de ces refus entraîna un fléau différent pour affliger le pharaon et les Egyptiens, tout en épargnant les esclaves hébreux. Dans un premier temps, le fleuve se remplit de sang, massacrant les poissons et rendant les eaux impropres à la consommation. Après le deuxième refus du pharaon, des grenouilles surgirent des étangs et des rivières et infectèrent les habitations des villages alentours. Le septième fléau fut un terrible orage de grêle qui massacra hommes et animaux dans les champs et détruisit les récoltes d'orge et de lin. Selon le Livre de l'Exode, le huitième refus de Ramsès provoqua une attaque de criquets, qui assombrirent la terre et dévorèrent toutes les choses vertes que le fléau précédent avait épargnées. Ramsès s'adoucit après que le dixième fléau ait anéanti tous les nouveaux nés égyptiens et tous les animaux. Il envoya toutefois son armée à la poursuite des Hébreux en fuite à travers la mer de roseaux. @PBien que ces fléaux ne soient pas rapportés dans les récits égyptiens contemporains, de nombreuses catastrophes similaires égrénèrent le cours de l'histoire. Même au XXème siècle, des orages de grêle et des essaims de criquets ont sévi et tourmenté l'humanité."
        }
    }
    message_mummy_attacks {
        id: 496,
        type: 2,
        
        size [30, 20]
        urgent: 1
        title { text: "Au secours ! Des momies !" }
        content { text: "Une momie déambule dans les rues de votre ville. Arrêtez ce fléau avant qu'il ne se propage à travers le pays !" }
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
    sphinx_congratulations {
        id: 532,
        size [30, 18]
        title { text: "Sphinx finished!" }
        content {
            text: "At long last the masons have finished carving the mighty Sphinx.  This monument will watch over Egypt for all the ages."
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
