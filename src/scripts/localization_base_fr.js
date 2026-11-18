log_info("akhenaten: localization_fr config started")

localization_base_fr = [
    { group:2, id:0, text: "Options" }
    { group:2, id:9, text: "Enregistrement auto" }
    { group:2, id:10, text: "Pas d'enregistrement auto" }
    { group:3, id:0, text: "Aide" }
    { group:3, id:8, text: "Guide de l'éditeur" }
    { group:4, id:0, text: "Chefs" }
    { group:4, id:1, text: "Chef de la main-d'œuvre" }
    { group:4, id:2, text: "Chef militaire" }
    { group:4, id:3, text: "Chef politique" }
    { group:4, id:4, text: "Chef des niveaux" }
    { group:4, id:5, text: "Chef du commerce" }
    { group:4, id:6, text: "Chef de la nourriture" }
    { group:4, id:7, text: "Chef de l'hygiène" }
    { group:4, id:8, text: "Chef de l'éducation" }
    { group:4, id:9, text: "Chef des loisirs" }
    { group:4, id:10, text: "Chef des temples" }
    { group:4, id:11, text: "Chef des finances" }
    { group:4, id:12, text: "Responsable" }
    { group:4, id:13, text: "Chef des monuments" }
    { group:5, id:1, text: "Quitter le royaume ?" }
    { group:5, id:3, text: "Payer pour ouvrir cette route de commerce ?" }
    { group:5, id:4, text: "Ouvrir une route de commerce" }
    { group:5, id:5, text: "Payer pour ouvrir cette route maritime de commerce ?" }
    { group:5, id:6, text: "Requête du pharaon" }
    { group:5, id:9, text: "Vous n'avez pas assez de marchandises" }
    { group:5, id:11, text: "Vous n'avez aucune compagnie à envoyer" }
    { group:5, id:13, text: "Ordonnez à votre chef militaire d'affecter des compagnies opérationnelles au service du royaume." }
    { group:5, id:15, text: "Envoyer une force de soutien ?" }
    { group:5, id:17, text: "Etes-vous sûr de vouloir supprimer ce fort ?" }
    { group:5, id:18, text: "CD absent" }
    { group:5, id:19, text: "Veuillez remplacer le CD de 'La Reine du Nil - Cléopâtre' dans votre lecteur de CD-ROM." }
    { group:5, id:21, text: "Réfléchissez bien avant de détruire des ponts. Les communautés isolées dépérissent lorsqu'elles sont coupées de la route du royaume." }
    { group:5, id:24, text: "Ancienne version" }
    { group:5, id:25, text: "Ce fichier est une version ancienne qui ne peut pas être chargée" }
    { group:5, id:26, text: "Trop d'offrandes funéraires !" }
    { group:5, id:27, text: "Vous ne pouvez pas faire plus de 5 offrandes funéraires dans ce scénario !" }
    { group:5, id:28, text: "Attention !" }
    { group:5, id:29, text: "Cette offrande funéraire n'est pas disponible dans ce scénario !" }
    { group:5, id:30, text: "Pas assez de marchandises !" }
    { group:5, id:31, text: "Vous n'avez pas assez de marchandises de ce type en stock !" }
    { group:5, id:32, text: "Terminé !" }
    { group:5, id:33, text: "Vous n'avez plus besoin d'offrandes funéraires de ce type !" }
    { group:5, id:34, text: "Nb max de cités" }
    { group:5, id:35, text: "Le nombre maximal de cités est atteint" }
    { group:5, id:36, text: "Transporteur nécessaire" }
    { group:5, id:37, text: "Ces troupes doivent embarquer à bord d'un transporteur pour servir le royaume dans le conflit actuel." }
    { group:5, id:38, text: "Troupes terrestres nécessaires" }
    { group:5, id:39, text: "Seules des troupes se déplaçant par voie terrestre sont nécessaires pour servir le royaume dans le conflit actuel." }
    { group:5, id:40, text: "Pas de troupes nécessaires" }
    { group:5, id:41, text: "Aucune troupe n'est requise, ni terrestre ni maritime" }
    { group:5, id:42, text: "Troupes dans le royaume" }
    { group:5, id:43, text: "Ces troupes ne sont pas dans la cité" }
    { group:5, id:44, text: "Navire de guerre dans le royaume" }
    { group:5, id:45, text: "Ce navire de guerre n'est pas dans la cité" }
    { group:5, id:46, text: "Impossible de modifier le prix !" }
    { group:5, id:47, text: "Cette marchandise n'est pas disponible dans ce scénario !" }
    { group:5, id:48, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:49, text: "La cité ne peut pas produire ni importer de toile." }
    { group:5, id:50, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:51, text: "La cité ne peut pas produire ni importer de bière." }
    { group:5, id:52, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:53, text: "La cité ne peut pas produire ni importer de papyrus." }
    { group:5, id:54, text: "Les salles d'embaumeurs ne peuvent pas fonctionner." }
    { group:5, id:55, text: "La cité ne peut pas produire ni importer de toile. Les salles d'embaumeurs ont été supprimées." }
    { group:5, id:56, text: "La taverne de jeux ne peut pas fonctionner." }
    { group:5, id:57, text: "La cité ne peut pas produire ni importer de bière. Les tavernes de jeux ont été supprimées." }
    { group:5, id:58, text: "Les écoles de scribes ne peuvent pas fonctionner." }
    { group:5, id:59, text: "La cité ne peut pas produire ni importer de papyrus. Les écoles de scribes ont été supprimées." }
    { group:5, id:60, text: "Les bibliothèques ne peuvent pas fonctionner." }
    { group:5, id:61, text: "La cité ne peut pas produire ni importer de papyrus. Les bibliothèques ont été supprimées." }
    { group:5, id:62, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:63, text: "La cité ne peut pas produire ni importer de cuivre." }
    { group:5, id:64, text: "Les fabriques d'armes ne peuvent pas fonctionner." }
    { group:5, id:65, text: "La cité ne peut pas produire ni importer de cuivre. Les fabriques d'armes ont été supprimées." }
    { group:5, id:66, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:67, text: "La cité ne peut pas produire ni importer de bois." }
    { group:5, id:68, text: "Les fabriques de chars ne peuvent pas fonctionner." }
    { group:5, id:69, text: "La cité ne peut pas produire ni importer de bois. Les fabriques de chars ont été supprimées." }
    { group:5, id:70, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:71, text: "Cette cité n'a pas de centre de recrutement." }
    { group:5, id:72, text: "Fort : les fantassins ne peuvent pas travailler." }
    { group:5, id:73, text: "Cette cité n'a pas de centre de recrutement. Fort : les fantassins ont été supprimés." }
    { group:5, id:74, text: "Fort : les archers ne peuvent pas travailler." }
    { group:5, id:75, text: "Cette cité n'a pas de centre de recrutement. Fort : les archers ont été supprimés." }
    { group:5, id:76, text: "Fort : les conducteurs de chars ne peuvent pas travailler." }
    { group:5, id:77, text: "Cette cité n'a pas de centre de recrutement. Fort : le conducteur de char a été supprimé." }
    { group:5, id:78, text: "Les académies ne fonctionnent pas." }
    { group:5, id:79, text: "Cette cité n'a pas de centre de recrutement. Les académies ont été supprimées." }
    { group:5, id:80, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:81, text: "La cité ne peut pas produire ni importer d'armes." }
    { group:5, id:82, text: "Ce bâtiment ne peut pas fonctionner." }
    { group:5, id:83, text: "La cité ne peut pas produire ni importer de chars." }
    { group:5, id:84, text: "Fort : les fantassins ne peuvent pas travailler." }
    { group:5, id:85, text: "Cette cité n'a pas de fabrique d'armes. Fort : les fantassins ont été supprimés." }
    { group:5, id:86, text: "Fort : les conducteurs de chars ne peuvent pas travailler." }
    { group:5, id:87, text: "Cette cité n'a pas de fabrique de chars. Fort : le conducteur de char a été supprimé." }
    { group:5, id:89, text: "Il faut une place des fêtes pour organiser une fête." }
    { group:5, id:91, text: "Cette opération supprimera la dynastie sélectionnée et toutes les parties qui lui sont associées. Voulez-vous continuer ?" }
    { group:5, id:92, text: "Cette dynastie existe" }
    { group:5, id:93, text: "Ce nom est déjà utilisé. Choisissez un autre nom." }
    { group:5, id:95, text: "Vous devez sélectionner une dynastie" }
    { group:5, id:96, text: "Attention" }
    { group:5, id:97, text: "Vous n'avez pas suffisamment de debens pour organiser une fête." }
    { group:5, id:98, text: "Requête du pharaon" }
    { group:5, id:99, text: "Vous n'avez pas assez de compagnies opérationnelles à envoyer" }
    { group:5, id:100, text: "Requête du pharaon" }
    { group:5, id:101, text: "Ordonnez à votre chef militaire d'affecter des compagnies opérationnelles au service du royaume" }
    { group:5, id:102, text: "Envoyer les forces" }
    { group:5, id:103, text: "Plusieurs destinations sont possibles pour les forces sélectionnées. Vous devez indiquer au chef politique où envoyer les troupes." }
    { group:5, id:104, text: "Destruction d'un monument" }
    { group:5, id:105, text: "Etes-vous sûr de vouloir détruire ce monument ?" }
    { group:5, id:106, text: "Destruction d'un ensemble de temples" }
    { group:5, id:107, text: "Faut-il détruire cet ensemble de temples ?" }
    { group:5, id:108, text: "Enregistrement impossible" }
    { group:5, id:109, text: "Emplacement des points de prédateurs/gibier incorrect" }
    { group:5, id:110, text: "Ce fichier existe" }
    { group:5, id:111, text: "Ecraser le fichier existant ?" }
    { group:5, id:112, text: "Aucun vendeur" }
    { group:5, id:113, text: "Aucune cité ne souhaite actuellement vendre cette marchandise." }
    { group:5, id:114, text: "Aucun acheteur" }
    { group:5, id:115, text: "Aucune cité ne souhaite actuellement acheter cette marchandise." }
    { group:5, id:116, text: "Aucune route de commerce ouverte" }
    { group:5, id:117, text: "Ouvrez une route de commerce à la mappemonde pour exporter cette denrée." }
    { group:5, id:118, text: "Ouvrez une route de commerce à la mappemonde pour importer cette denrée." }
    { group:5, id:119, text: "Attention" }
    { group:5, id:120, text: "Vous n'avez pas suffisamment de debens pour ouvrir une route de commerce." }
    { group:5, id:121, text: "Enregistrement impossible" }
    { group:5, id:122, text: "Trop de types d'aliments (4 max.)." }
    { group:5, id:123, text: "Impossible d'éditer la mappemonde" }
    { group:5, id:124, text: "L'édition de la mappemonde requiert une résolution d'écran 800x600 ou supérieure." }
    { group:5, id:125, text: "Impossible de quitter la mappemonde" }
    { group:5, id:126, text: "Trop de types d'aliments (4 max.)." }
    { group:5, id:127, text: "Enregistrement impossible" }
    { group:5, id:128, text: "Certains points de pêche se trouvent dans des lieux non valides." }
    { group:5, id:129, text: "Enregistrement impossible" }
    { group:5, id:130, text: "Points d'entrée/sortie dans des lieux non valides" }
    { group:5, id:131, text: "Enregistrement impossible" }
    { group:5, id:132, text: "Points internes/externes au fleuve dans des lieux non valides." }
    { group:5, id:133, text: "Enregistrement impossible" }
    { group:5, id:134, text: "Certains points d'invasion (terrestres) se trouvent dans des lieux non valides." }
    { group:5, id:135, text: "Enregistrement impossible" }
    { group:5, id:136, text: "Certains points d'invasion (terrestres) se trouvent dans des lieux non valides." }
    { group:5, id:137, text: "Pharaon" }
    { group:5, id:138, text: "Insérez le CD de 'La Reine du Nil - Cléopâtre'." }
    { group:5, id:139, text: "Le zoo n'est pas opérationnel." }
    { group:5, id:140, text: "L'importation de gibier ou de paille est impossible dans la cité. Le zoo a été fermé." }
    { group:5, id:141, text: "Missions non terminées" }
    { group:5, id:142, text: "Cliquez sur Lancer l'histoire si vous débutez. Voulez-vous choisir une mission ?" }
    { group:6, id:2, text: "Mois pour accomplir la mission" }
    { group:6, id:3, text: "Mois jusqu'à la victoire" }
    { group:6, id:4, text: "Cartes" }
    { group:6, id:5, text: "Vous avez déjà atteint vos objectifs et choisi de continuer à gouverner." }
    { group:6, id:6, text: "Placez les tombes au-dessus des falaises. Assurez-vous que l'entrée se trouve en terrain dégagé." }
    { group:7, id:0, text: "Fichier" }
    { group:7, id:1, text: "Nouvelle carte" }
    { group:7, id:2, text: "Charger la carte" }
    { group:7, id:3, text: "Enregistrer la carte" }
    { group:7, id:4, text: "Quitter l'éditeur" }
    { group:8, id:1, text: "debens" }
    { group:8, id:2, text: "personne" }
    { group:8, id:3, text: "personnes" }
    { group:8, id:4, text: "mois" }
    { group:8, id:5, text: "mois" }
    { group:8, id:6, text: "grenier avec" }
    { group:8, id:7, text: "greniers avec" }
    { group:8, id:8, text: "année" }
    { group:8, id:9, text: "années" }
    { group:8, id:10, text: "unité" }
    { group:8, id:11, text: "unités" }
    { group:8, id:12, text: "employé" }
    { group:8, id:13, text: "employés" }
    { group:8, id:14, text: "personne de plus" }
    { group:8, id:15, text: "personnes de plus" }
    { group:8, id:16, text: "unité." }
    { group:8, id:18, text: "école de scribes" }
    { group:8, id:19, text: "écoles de scribes" }
    { group:8, id:20, text: "académie" }
    { group:8, id:21, text: "académies" }
    { group:8, id:22, text: "bibliothèque" }
    { group:8, id:23, text: "bibliothèques" }
    { group:8, id:24, text: "médecin" }
    { group:8, id:25, text: "médecins" }
    { group:8, id:26, text: "dentiste" }
    { group:8, id:27, text: "dentistes" }
    { group:8, id:28, text: "pharmacie" }
    { group:8, id:29, text: "pharmacies" }
    { group:8, id:30, text: "salle des embaumeurs" }
    { group:8, id:31, text: "salles d'embaumeurs" }
    { group:8, id:32, text: "oracle" }
    { group:8, id:33, text: "oracles" }
    { group:8, id:34, text: "étal" }
    { group:8, id:35, text: "étals" }
    { group:8, id:36, text: "kiosque" }
    { group:8, id:37, text: "kiosques" }
    { group:8, id:38, text: "théâtre" }
    { group:8, id:39, text: "théâtres" }
    { group:8, id:40, text: "jeu de senet" }
    { group:8, id:41, text: "jeux de senet" }
    { group:8, id:42, text: "message" }
    { group:8, id:43, text: "messages" }
    { group:8, id:44, text: "jour" }
    { group:8, id:45, text: "jours" }
    { group:8, id:46, text: "soldat" }
    { group:8, id:47, text: "soldats" }
    { group:8, id:48, text: "compagnie" }
    { group:8, id:49, text: "compagnies" }
    { group:8, id:50, text: "navire de guerre" }
    { group:8, id:51, text: "navires de guerre" }
    { group:8, id:52, text: "salle des embaumeurs" }
    { group:8, id:53, text: "Salles des embaumeurs" }
    { group:8, id:54, text: "chargement" }
    { group:8, id:55, text: "chargements" }
    { group:8, id:56, text: "Bloc" }
    { group:8, id:57, text: "Blocs" }
    { group:8, id:58, text: "transporteur" }
    { group:8, id:59, text: "transporteurs" }
    { group:9, id:0, text: "Pharaon (extension La Reine du Nil - Cléopâtre)" }
    { group:9, id:1, text: "Version 2.1" }
    { group:9, id:2, text: "Copyright 1999-2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Version bêta pour : BreakAway Games" }
    { group:9, id:4, text: "test1 string" }
    { group:9, id:5, text: "Votre nom" }
    { group:9, id:6, text: "Ma cité égyptienne" }
    { group:9, id:7, text: "Scénario 1" }
    { group:9, id:8, text: "Editeur d'affectation de Pharaon" }
    { group:9, id:9, text: "Démo de Pharaon" }
    { group:10, id:0, text: "Réinitialiser" }
    { group:10, id:1, text: "Effacer les points de prédateurs" }
    { group:10, id:2, text: "Effacer les points de pêche" }
    { group:10, id:3, text: "Effacer les points d'invasions" }
    { group:10, id:4, text: "Effacer les points de débarquements" }
    { group:10, id:5, text: "Effacer les points de gibier" }
    { group:10, id:6, text: "Charger depuis BMP" }
    { group:10, id:7, text: "Enregistrer vers BMP" }
    { group:10, id:8, text: "Modifier le royaume" }
    { group:10, id:9, text: "Enregistrer le royaume" }
    { group:10, id:10, text: "Rafraîchir la carte" }
    { group:11, id:0, text: "Configuration..." }
    { group:11, id:1, text: "test_string €,Њ,њ,Ў,°,ї,A,А,Б,В,Д, E,И,Й,К,I,М,Н,О,П,N,С,O,Т,У,Ф,Ц, U,Щ,Ъ,Ы,Ь,Я,a,а,б,в,д,c,з, e,и,й,к,i,м,н,о,п,n,с,o,т,у,ф,ц,u,щ,ъ,ы,ь,..." }
    { group:11, id:2, text: "Chargement..." }
    { group:11, id:3, text: "Chargement des données..." }
    { group:11, id:4, text: "Chargement des sons..." }
    { group:11, id:5, text: "Temps accéléré" }
    { group:11, id:6, text: "Clic droit pour continuer" }
    { group:11, id:7, text: "Chargement des toiles de fond ..." }
    { group:11, id:8, text: "Chargement des animations ..." }
    { group:11, id:9, text: "Chargement des monuments ..." }
    { group:11, id:10, text: "Chargement des ennemis ..." }
    { group:11, id:11, text: "Chargement des paramètres ..." }
    { group:12, id:0, text: "Retour" }
    { group:12, id:2, text: "pour répondre" }
    { group:12, id:3, text: "Les stocks de nourriture sont presque épuisés." }
    { group:12, id:4, text: "Le taux de chômage élevé pose des problèmes." }
    { group:12, id:5, text: "Le taux d'imposition élevé pose des problèmes." }
    { group:12, id:6, text: "La faiblesse des salaires pose des problèmes." }
    { group:12, id:7, text: "Les habitants des quartiers pauvres désirent de meilleures conditions de vie." }
    { group:13, id:0, text: "Cliquez pour continuer" }
    { group:13, id:1, text: "Clic droit pour continuer" }
    { group:13, id:2, text: "Jeu en pause (touche 'P' pour continuer)" }
    { group:13, id:3, text: "Clic droit pour continuer" }
    { group:13, id:4, text: "Annuler" }
    { group:13, id:5, text: "Continuer" }
    { group:13, id:6, text: "Non disponible dans la version de démonstration !" }
    { group:13, id:7, text: "Cliquez pour démarrer" }
    { group:13, id:8, text: "Choisissez un nom égyptien" }
    { group:14, id:8, text: "Incendies" }
    { group:14, id:9, text: "Dégâts" }
    { group:14, id:10, text: "Criminalité" }
    { group:14, id:11, text: "Global" }
    { group:14, id:12, text: "Jongleur" }
    { group:14, id:13, text: "Musicien" }
    { group:14, id:14, text: "Danseur" }
    { group:14, id:15, text: "Senet" }
    { group:14, id:16, text: "Gardiens du zoo" }
    { group:14, id:17, text: "Global" }
    { group:14, id:18, text: "Ecoles" }
    { group:14, id:19, text: "Bibliothèque" }
    { group:14, id:20, text: "Gués" }
    { group:14, id:21, text: "Dentiste" }
    { group:14, id:22, text: "Médecin" }
    { group:14, id:23, text: "Pharmacie" }
    { group:14, id:24, text: "Embaumeurs" }
    { group:14, id:25, text: "Impôts" }
    { group:14, id:26, text: "Accès au bazar" }
    { group:14, id:27, text: "Attrait" }
    { group:14, id:28, text: "Fertilité" }
    { group:14, id:29, text: "Main-d'œuvre" }
    { group:14, id:30, text: "Indigènes" }
    { group:14, id:31, text: "Problèmes" }
    { group:14, id:32, text: "Problèmes" }
    { group:14, id:33, text: "Céréales" }
    { group:14, id:34, text: "Pois chiches" }
    { group:14, id:35, text: "Grenades" }
    { group:14, id:36, text: "Figues" }
    { group:14, id:37, text: "Viande" }
    { group:14, id:38, text: "Gibier" }
    { group:14, id:39, text: "Poterie" }
    { group:14, id:40, text: "Bijoux" }
    { group:14, id:41, text: "Toile" }
    { group:14, id:42, text: "Bière" }
    { group:14, id:43, text: "Maladie" }
    { group:14, id:44, text: "Epidémie" }
    { group:14, id:45, text: "Eau" }
    { group:14, id:46, text: "Logement vide" }
    { group:14, id:47, text: "Irrigation" }
    { group:14, id:48, text: "Malaria" }
    { group:14, id:49, text: "Défenses" }
    { group:14, id:50, text: "Magistrat" }
    { group:14, id:51, text: "Falaises off" }
    { group:15, id:0, text: "Accepter les biens" }
    { group:15, id:1, text: "Refuser les biens" }
    { group:15, id:2, text: "Aller chercher les marchandises" }
    { group:16, id:0, text: "Bâtiment" }
    { group:16, id:1, text: "Usine" }
    { group:16, id:2, text: "Control" }
    { group:16, id:3, text: "Gfx" }
    { group:16, id:4, text: "Structure" }
    { group:16, id:5, text: "Réseau" }
    { group:16, id:6, text: "Aléatoire" }
    { group:16, id:7, text: "Données" }
    { group:16, id:8, text: "Anim" }
    { group:16, id:9, text: "Sticky" }
    { group:16, id:10, text: "RM_build" }
    { group:16, id:11, text: "Bâtiment - point d'eau" }
    { group:16, id:12, text: "Bâtiment - accès" }
    { group:16, id:13, text: "Building - from Capital" }
    { group:16, id:14, text: "Bâtiment - dégâts" }
    { group:16, id:15, text: "Bâtiment - population" }
    { group:16, id:16, text: "Attrait" }
    { group:16, id:17, text: "Hauteur" }
    { group:16, id:18, text: "River sticky" }
    { group:16, id:19, text: "Barb sticky" }
    { group:16, id:20, text: "Dégâts" }
    { group:16, id:21, text: "Nof figs" }
    { group:16, id:22, text: "Old type" }
    { group:16, id:23, text: "Influence" }
    { group:16, id:24, text: "Wall sticky" }
    { group:16, id:25, text: "Réseau routier" }
    { group:16, id:26, text: "Quartier" }
    { group:17, id:0, text: "Nord" }
    { group:17, id:1, text: "Nord-est" }
    { group:17, id:2, text: "Est" }
    { group:17, id:3, text: "Sud-est" }
    { group:17, id:4, text: "Sud" }
    { group:17, id:5, text: "Sud-ouest" }
    { group:17, id:6, text: "Ouest" }
    { group:17, id:7, text: "Nord-ouest" }
    { group:18, id:0, text: "Non" }
    { group:18, id:1, text: "Oui" }
    { group:18, id:2, text: "Annuler" }
    { group:18, id:3, text: "OK" }
    { group:18, id:4, text: "Actif" }
    { group:18, id:5, text: "Inactif" }
    { group:18, id:6, text: "N.D." }
    { group:18, id:7, text: "En savoir plus" }
    { group:18, id:8, text: "et" }
    { group:18, id:9, text: "Réessayer" }
    { group:18, id:10, text: "Abandonner" }
    { group:18, id:11, text: "Ignorer" }
    { group:19, id:0, text: "Impossible : terrain non dégagé" }
    { group:19, id:1, text: "Crédit insuffisant !" }
    { group:19, id:2, text: "Vous ne pouvez construire qu'un bâtiment de ce type" }
    { group:19, id:3, text: "Pas d'évolution des maisons" }
    { group:19, id:4, text: "Evolution des maisons" }
    { group:19, id:5, text: "Pas d'évolution des routes" }
    { group:19, id:6, text: "Evolution des routes" }
    { group:19, id:7, text: "Ne pas montrer les gens" }
    { group:19, id:8, text: "Montrer les gens" }
    { group:19, id:9, text: "Ce bâtiment a besoin d'accéder à une route" }
    { group:19, id:10, text: "Ce bâtiment est trop éloigné de l'eau !" }
    { group:19, id:11, text: "Non disponible dans cette mission !" }
    { group:19, id:12, text: "Non disponible pour l'instant !" }
    { group:19, id:13, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build a large temple" }
    { group:19, id:14, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build an oracle" }
    { group:19, id:15, text: "La cité manque de main-d'œuvre." }
    { group:19, id:16, text: "Consommation de nourriture supérieure à production" }
    { group:19, id:17, text: "Créez des bazars pour les denrées entreposées." }
    { group:19, id:18, text: "Construisez les fermes dans la prairie (herbe jaune)." }
    { group:19, id:19, text: "Construisez les puits d'argile près de l'eau." }
    { group:19, id:20, text: "Construisez ceci près des zones rocheuses." }
    { group:19, id:21, text: "Construisez les chantiers de bois près des arbres." }
    { group:19, id:22, text: "Construisez ceci près des zones rocheuses." }
    { group:19, id:23, text: "Cherchez un endroit adapté le long de la rivière." }
    { group:19, id:24, text: "Ce bâtiment a besoin de cuivre." }
    { group:19, id:25, text: "Ce bâtiment a besoin d'orge." }
    { group:19, id:26, text: "Ce bâtiment a besoin de lin." }
    { group:19, id:27, text: "Ce bâtiment a besoin d'argile." }
    { group:19, id:28, text: "Ce bâtiment a besoin de pierres précieuses." }
    { group:19, id:29, text: "Etablissez une route de commerce pour en importer." }
    { group:19, id:30, text: "Chargez le chef du commerce d'en importer." }
    { group:19, id:31, text: "Creusez une mine de cuivre." }
    { group:19, id:32, text: "Construisez une exploitation d'orge." }
    { group:19, id:33, text: "Construisez une exploitation de lin." }
    { group:19, id:34, text: "Construisez un puits d'argile." }
    { group:19, id:35, text: "Creusez une mine de pierres précieuses." }
    { group:19, id:36, text: "Doit avoir accès à un chadouf complet pour fonctionner" }
    { group:19, id:37, text: "Doit être près de l'eau pour se remplir." }
    { group:19, id:38, text: "Utilisez des rigoles pour relier ceci à un chadouf." }
    { group:19, id:39, text: "Doit être près d'un mur pour envoyer une patrouille." }
    { group:19, id:40, text: "Il faut un centre de recrutement pour enrôler des soldats." }
    { group:19, id:41, text: "Vos troupes auront besoin d'armes." }
    { group:19, id:42, text: "Créez une école de jonglerie pour former des élèves" }
    { group:19, id:43, text: "Construisez un conservatoire pour former des musiciens" }
    { group:19, id:44, text: "Construisez une école de danse" }
    { group:19, id:45, text: "Construisez une taverne pour y organiser des jeux." }
    { group:19, id:46, text: "Non disponible dans la démo" }
    { group:19, id:47, text: "Les tours doivent être installées sur des murs épais." }
    { group:19, id:48, text: "Trop près des troupes ennemies" }
    { group:19, id:49, text: "Moral des troupes trop bas pour qu'elles réagissent !" }
    { group:19, id:50, text: "Votre armée est suffisamment équipée en forts." }
    { group:19, id:53, text: "Impossible de détruire un pont tant qu'il est occupé" }
    { group:19, id:54, text: "Ce lac n'a pas d'accès à la mer" }
    { group:19, id:55, text: "Impossible de passer en mode fenêtre." }
    { group:19, id:56, text: "Créez des cueilleurs de roseaux près du marécage." }
    { group:19, id:57, text: "Du bois est nécessaire pour les navires de guerre" }
    { group:19, id:58, text: "Palais requis pour la transformation d'or en debens" }
    { group:19, id:59, text: "Construction impossible sur les champs d'élevage" }
    { group:19, id:60, text: "Certains points sont trop éloignés d'une route" }
    { group:19, id:61, text: "Une partie de la cité est isolée de la route du royaume." }
    { group:19, id:62, text: "Sans accès, ce secteur continuera à stagner." }
    { group:19, id:63, text: "Limite de données atteinte - voir le fichier Readme" }
    { group:19, id:64, text: "Les barrages ne sont possibles que sur des routes." }
    { group:19, id:65, text: "Placez l'autre station de navettes" }
    { group:19, id:66, text: "Cette navette n'a pas d'emplacement valable" }
    { group:19, id:67, text: "Le royaume dispose déjà des 4 types de nourriture." }
    { group:19, id:68, text: "Paille requise pour produire de la viande." }
    { group:19, id:69, text: "Production de viande impossible. Elle a été supprimée." }
    { group:19, id:70, text: "Un seul type de roche spéciale est autorisé." }
    { group:19, id:71, text: "Vous devez d'abord construire un ensemble de temples." }
    { group:19, id:72, text: "Un ensemble de temples peut comporte un oracle et un autel." }
    { group:19, id:73, text: "Un ensemble de temples doit contenir oracles et autels." }
    { group:19, id:74, text: "Cette structure a besoin d'eau. Zone herbeuse requise." }
    { group:19, id:75, text: "Ce lieu de divertissement doit être placé au carrefour." }
    { group:19, id:76, text: "Vous devez d'abord construire un temple !" }
    { group:19, id:77, text: "Il faut 500 papyrus pour construire une bibliothèque." }
    { group:19, id:78, text: "Ce bâtiment a besoin de roseaux." }
    { group:19, id:79, text: "Créez un cueilleur de roseaux." }
    { group:19, id:80, text: "Ce bâtiment a besoin de paille." }
    { group:19, id:81, text: "Construisez une exploitation de céréales." }
    { group:19, id:82, text: "Nombre maximal de quais de navires de guerre atteint." }
    { group:19, id:83, text: "%d blocs de granit sont requis pour un petit obélisque." }
    { group:19, id:84, text: "%d blocs de granit sont requis pour un grand obélisque." }
    { group:19, id:85, text: "Certains des monuments que vous avez choisis ne peuvent plus être construits. Ils ont été supprimés !" }
    { group:19, id:86, text: "Vous ne pouvez construire qu'un seul obélisque à la fois." }
    { group:19, id:87, text: "Votre cité doit avoir un palais pour pouvoir lever des impôts." }
    { group:19, id:88, text: "220 blocs de grès sont requis pour un temple solaire." }
    { group:19, id:89, text: "Seul un temple solaire peut être construit à la fois." }
    { group:19, id:90, text: "Il n'y a pas assez de travail pour cette population." }
    { group:19, id:91, text: "Les réserves de nourriture sont presque épuisées." }
    { group:19, id:92, text: "Consommation de nourriture supérieure à la production." }
    { group:19, id:93, text: "L'hygiène est devenue épouvantable. La peste va éclater." }
    { group:19, id:94, text: "L'hygiène est pitoyable. La peste risque d'éclater." }
    { group:19, id:95, text: "L'hygiène empire. Le risque de peste est important." }
    { group:19, id:96, text: "L'hygiène dans la cité empire. La peste pourrait éclater." }
    { group:19, id:97, text: "La peste reste possible, malgré une meilleure hygiène." }
    { group:19, id:98, text: "La peste est possible, malgré une meilleure hygiène." }
    { group:19, id:99, text: "L'hygiène s'améliore, mais la peste menace encore." }
    { group:19, id:100, text: "Le palais a été dévalisé !" }
    { group:19, id:101, text: "On vous a volé dans votre demeure luxueuse !" }
    { group:19, id:102, text: "Aucune troupe pour combattre l'attaque imminente." }
    { group:19, id:103, text: "Toute la cité vous déteste." }
    { group:19, id:104, text: "La population est très en colère." }
    { group:19, id:105, text: "La population est en colère." }
    { group:19, id:106, text: "La population vous en veut beaucoup." }
    { group:19, id:107, text: "La population vous en veut." }
    { group:19, id:108, text: "La population est contrariée." }
    { group:19, id:109, text: "La population est indifférente." }
    { group:19, id:110, text: "La population est satisfaite." }
    { group:19, id:111, text: "La population est très satisfaite." }
    { group:19, id:112, text: "La population est heureuse." }
    { group:19, id:113, text: "La population vous adore." }
    { group:19, id:114, text: "Vous êtes considéré comme un dieu." }
    { group:19, id:115, text: "parce qu'il n'y a pas assez à manger." }
    { group:19, id:116, text: "parce qu'il n'y a pas assez de travail." }
    { group:19, id:117, text: "parce que les impôts sont trop élevés." }
    { group:19, id:118, text: "parce que les salaires sont trop bas." }
    { group:19, id:119, text: "parce qu'il y a trop de quartiers pauvres." }
    { group:19, id:120, text: "Des gens immigrent vers la cité" }
    { group:19, id:121, text: "Il n'y a pas assez de logements" }
    { group:19, id:122, text: "Les revenus sont trop bas" }
    { group:19, id:123, text: "Le chômage freine l'immigration" }
    { group:19, id:124, text: "Il n'y a pas assez de nourriture" }
    { group:19, id:125, text: "Les impôts sont trop élevés" }
    { group:19, id:126, text: "Les quartiers pauvres limitent l'immigration" }
    { group:19, id:127, text: "La morosité de votre cité limite l'immigration" }
    { group:19, id:128, text: "Les gens partent à cause du manque de logements." }
    { group:19, id:129, text: "Les gens quittent la cité à cause des salaires bas." }
    { group:19, id:130, text: "Les gens quittent la cité à cause du manque de travail." }
    { group:19, id:131, text: "Les gens partent à cause du manque de nourriture." }
    { group:19, id:132, text: "Les gens quittent la cité à cause des impôts élevés." }
    { group:19, id:133, text: "La présence de quartiers pauvres incite les gens à partir." }
    { group:19, id:134, text: "Les gens partent à cause de la morosité ambiante." }
    { group:19, id:135, text: "Ce bâtiment a besoin de bière pour fonctionner." }
    { group:19, id:136, text: "Construisez une brasserie." }
    { group:19, id:137, text: "Ce bâtiment a besoin de papyrus pour fonctionner." }
    { group:19, id:138, text: "Construisez une fabrique de papyrus." }
    { group:19, id:139, text: "Ce bâtiment a besoin de toile pour fonctionner." }
    { group:19, id:140, text: "Construisez un atelier de tissage." }
    { group:19, id:141, text: "Ce bâtiment a besoin de bois pour fonctionner." }
    { group:19, id:142, text: "Créez un chantier de bois." }
    { group:19, id:143, text: "Ce bâtiment a besoin d'argile et de paille." }
    { group:19, id:144, text: "Route de commerce requise pour importer de l'argile." }
    { group:19, id:145, text: "Chargez le chef du commerce d'importer de l'argile." }
    { group:19, id:146, text: "Route de commerce requise pour importer de la paille." }
    { group:19, id:147, text: "Chargez le chef du commerce d'importer de la paille." }
    { group:19, id:148, text: "Ce monument a besoin de pierre et de calcaire." }
    { group:19, id:149, text: "Creusez une carrière de pierre" }
    { group:19, id:150, text: "Route de commerce requise pour importer de la pierre" }
    { group:19, id:151, text: "Chargez le chef du commerce d'importer de la pierre." }
    { group:19, id:152, text: "Creusez une carrière de calcaire blanc." }
    { group:19, id:153, text: "Tracez une route de commerce pour importer du calcaire." }
    { group:19, id:154, text: "Chargez le chef du commerce d'importer du calcaire." }
    { group:19, id:155, text: "Ce monument a besoin de pierre." }
    { group:19, id:156, text: "Ce monument a besoin de calcaire." }
    { group:19, id:157, text: "Ce monument a besoin de briques et de calcaire." }
    { group:19, id:158, text: "Construisez une briqueterie." }
    { group:19, id:159, text: "Route de commerce requise pour importer des briques" }
    { group:19, id:160, text: "Chargez le chef du commerce d'importer des briques." }
    { group:19, id:161, text: "Ce monument a besoin de briques." }
    { group:19, id:162, text: "Ce monument a besoin de grès." }
    { group:19, id:163, text: "Creusez une carrière de grès." }
    { group:19, id:164, text: "Chargez le chef du commerce d'importer de la bière." }
    { group:19, id:165, text: "Route de commerce requise pour importer de la bière" }
    { group:19, id:166, text: "Chargez le chef du commerce d'importer de l'orge." }
    { group:19, id:167, text: "Route de commerce requise pour importer de l'orge" }
    { group:19, id:168, text: "Chargez le chef du commerce d'importer des roseaux." }
    { group:19, id:169, text: "Route de commerce requise pour importer des roseaux" }
    { group:19, id:170, text: "Chargez le chef du commerce d'importer du papyrus." }
    { group:19, id:171, text: "Route de commerce requise pour importer du papyrus" }
    { group:19, id:172, text: "Chargez le chef du commerce d'importer du lin." }
    { group:19, id:173, text: "Etablissez une route de commerce pour importer du lin." }
    { group:19, id:174, text: "Chargez le chef du commerce d'importer de la toile." }
    { group:19, id:175, text: "Route de commerce requise pour importer de la toile" }
    { group:19, id:176, text: "Les salles d'embaumeurs ne peuvent pas fonctionner et ont été supprimées. La cité ne peut pas produire ni importer de toile." }
    { group:19, id:177, text: "La taverne de jeux ne peut pas fonctionner et a été supprimée. La cité ne peut pas produire ni importer de bière." }
    { group:19, id:178, text: "Les écoles de scribes ne peuvent pas fonctionner et ont été supprimées. La cité ne peut pas produire ni importer de papyrus." }
    { group:19, id:179, text: "Les bibliothèques ne peuvent pas fonctionner et ont été supprimées. La cité ne peut pas produire ni importer de papyrus." }
    { group:19, id:180, text: "Les fabriques d'armes ne peuvent pas fonctionner et ont été supprimées. La cité ne peut pas produire ni importer de cuivre." }
    { group:19, id:181, text: "La fabrique de chars ne peut pas fonctionner et a été supprimée. La cité ne peut pas produire ni importer de bois." }
    { group:19, id:182, text: "Fort : les fantassins ne peuvent pas travailler et ont été supprimés. La cité n'a pas de centre de recrutement." }
    { group:19, id:183, text: "Fort : les archers ne peuvent pas travailler et ont été supprimés. La cité n'a pas de centre de recrutement." }
    { group:19, id:184, text: "Fort : les conducteurs de chars ne peuvent pas travailler et ont été supprimés. La cité n'a pas de centre de recrutement." }
    { group:19, id:185, text: "Les académies ne peuvent pas fonctionner et ont été supprimées. La cité ne peut pas produire ni importer de bois." }
    { group:19, id:186, text: "Fort : les fantassins ne peuvent pas travailler et ont été supprimés. La cité ne peut pas produire ni importer d'armes." }
    { group:19, id:187, text: "Les conducteurs de chars ne peuvent pas travailler. Ils ont été supprimés. La cité ne peut ni produire ni importer de chariots." }
    { group:19, id:188, text: "240 blocs de grès requis pour un mausolée." }
    { group:19, id:189, text: "Construisez une brasserie ou importez de la bière." }
    { group:19, id:190, text: "Brasserie ou route requises pour la bière." }
    { group:19, id:191, text: "Construisez une fabrique de papyrus ou commandez-en." }
    { group:19, id:192, text: "Fabrique ou route requises pour le papyrus" }
    { group:19, id:193, text: "Construisez un atelier ou importez de la toile." }
    { group:19, id:194, text: "Construisez un atelier ou une route pour la toile." }
    { group:19, id:195, text: "Un bureau de perception a été pillé !" }
    { group:19, id:196, text: "Un palais de justice a été pillé !" }
    { group:19, id:197, text: "Votre demeure luxueuse a été détruite et pillée !" }
    { group:19, id:198, text: "Ce palais a été détruit et pillé !" }
    { group:19, id:199, text: "Un bureau de perception a été pillé !" }
    { group:19, id:200, text: "Un palais de justice a été pillé !" }
    { group:19, id:201, text: "Une mine d'or a été attaquée et pillée !" }
    { group:19, id:202, text: "Construisez un grenier pour stocker la prochaine récolte" }
    { group:19, id:203, text: "Construisez des greniers pour stocker la prochaine récolte" }
    { group:19, id:204, text: "Seuls 10 docks peuvent être activés en même temps" }
    { group:19, id:205, text: "Les sanctuaires doivent se trouver près d'une route." }
    { group:19, id:206, text: "Construisez une école de jonglerie pour l'événement" }
    { group:19, id:207, text: "Construisez un conservatoire pour les musiciens" }
    { group:19, id:208, text: "Construisez une école de danse pour cet événement" }
    { group:19, id:209, text: "Cette compagnie ne peut pas rejoindre sa destination" }
    { group:19, id:210, text: "Partie enregistrée" }
    { group:19, id:211, text: "A construire sur un terrain non obstrué" }
    { group:19, id:212, text: "La chaussée de ce monument doit mener à une étendue d'eau" }
    { group:19, id:213, text: "Construisez la place des fêtes à un carrefour" }
    { group:19, id:214, text: "La présence d'ennemis sur notre sol empêche toute immigration" }
    { group:19, id:215, text: "Astuces activées" }
    { group:19, id:216, text: "Astuces désactivées" }
    { group:19, id:217, text: "L'inondation sera parfaite." }
    { group:19, id:218, text: "L'inondation sera excellente" }
    { group:19, id:219, text: "L'inondation sera bonne." }
    { group:19, id:220, text: "L'inondation sera médiocre." }
    { group:19, id:221, text: "L'inondation sera faible." }
    { group:19, id:222, text: "Il n'y aura pas d'inondation." }
    { group:19, id:223, text: "Augmentation des prix" }
    { group:19, id:224, text: "Diminution des prix" }
    { group:19, id:225, text: "Les salaires ont baissé au sein du royaume." }
    { group:19, id:226, text: "Les salaires ont augmenté au sein du royaume." }
    { group:19, id:227, text: "Le commerce décroît" }
    { group:19, id:228, text: "Le commerce augmente." }
    { group:19, id:229, text: "Le niveau du royaume augmente." }
    { group:19, id:230, text: "Borne de population atteinte" }
    { group:19, id:231, text: "Petite bénédiction divine reçue" }
    { group:19, id:232, text: "La fête commence." }
    { group:19, id:233, text: "Volonté satisfaite : envoi automatique des biens" }
    { group:19, id:234, text: "Ce zoo a été supprimé. La production et l'importation de paille ou de gibier sont impossibles." }
    { group:19, id:235, text: "Ce bâtiment a besoin de gibier." }
    { group:19, id:236, text: "Pavillon de chasse" }
    { group:19, id:237, text: "Construisez un pavillon de chasse ou importez du gibier." }
    { group:19, id:238, text: "Construisez un pavillon de chasse ou importez le gibier." }
    { group:19, id:239, text: "Cuivre requis" }
    { group:19, id:240, text: "Marbre requis" }
    { group:19, id:241, text: "Une seule bibliothèque d'Alexandrie possible." }
    { group:19, id:242, text: "Un seul phare de Pharos possible." }
    { group:19, id:243, text: "Un seul Caesareum possible." }
    { group:19, id:244, text: "Maladie" }
    { group:19, id:245, text: "Malaria" }
    { group:19, id:246, text: "Granit requis" }
    { group:19, id:247, text: "Construire sur terrain rocheux" }
    { group:19, id:248, text: "Impossible de détruire le phare" }
    { group:19, id:249, text: "Une tombe antique a été pillée !" }
    { group:19, id:250, text: "Le mausolée d'Alexandre le Grand a été pillé !" }
    { group:19, id:251, text: "Des offrandes funéraires ont été pillées !" }
    { group:19, id:252, text: "Un pilleur de tombes a été arrêté." }
    { group:19, id:253, text: "Ce bâtiment a besoin d'huile et de poteries" }
    { group:19, id:254, text: "Créez une poterie" }
    { group:19, id:255, text: "Importez des poteries par route." }
    { group:19, id:256, text: "Le chef du commerce doit importer des poteries." }
    { group:19, id:257, text: "Importez de l'huile par route." }
    { group:19, id:258, text: "Le chef du commerce doit importer de l'huile." }
    { group:19, id:259, text: "Ce bâtiment a besoin de henné." }
    { group:19, id:260, text: "Créez une exploitation de henné" }
    { group:19, id:261, text: "Le chef du commerce doit importer du henné." }
    { group:19, id:262, text: "Importez du henné par route." }
    { group:19, id:263, text: "Ce bâtiment a besoin d'huile." }
    { group:19, id:264, text: "Ce bâtiment a besoin de poteries." }
    { group:19, id:265, text: "Construisez une fabrique de peinture ou importez-en." }
    { group:19, id:266, text: "Construisez une fabrique de peinture ou importez-en." }
    { group:19, id:267, text: "Construisez une fabrique de peinture" }
    { group:19, id:268, text: "Ce bâtiment à besoin d'argile et de peinture." }
    { group:19, id:269, text: "Manque de main-d'œuvre" }
    { group:19, id:270, text: "Ceci doit être entièrement construit sur des falaises" }
    { group:19, id:271, text: "...avec une entrée sur terrain dégagé. " }
    { group:20, id:0, text: "avJC" }
    { group:20, id:1, text: "aprJC" }
    { group:21, id:0, text: "Elephantine" }
    { group:21, id:1, text: "Abedju" }
    { group:21, id:2, text: "l'oasis de Bahariya" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apollinopolis" }
    { group:21, id:5, text: "Bubastis" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Byblos" }
    { group:21, id:8, text: "Dahshur" }
    { group:21, id:9, text: "l'oasis de Dakhlèh" }
    { group:21, id:10, text: "Abousir" }
    { group:21, id:11, text: "l'oasis de Dunqul" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "l'oasis de Farafra" }
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
    { group:21, id:24, text: "l'oasis de Kharga" }
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
    { group:21, id:43, text: "l'oasis de Selima" }
    { group:21, id:44, text: "Serabit Khadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Sharuhen" }
    { group:21, id:47, text: "Thinis" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toshka" }
    { group:21, id:50, text: "Tyre" }
    { group:21, id:51, text: "Thèbes" }
    { group:21, id:52, text: "Pelusium" }
    { group:21, id:53, text: "Alexandrie" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medineh" }
    { group:21, id:56, text: "Abou Simbel" }
    { group:21, id:57, text: "Actium" }
    { group:21, id:58, text: "Rome" }
    { group:21, id:59, text: "Tanis" }
    { group:21, id:60, text: "Pi-Yer" }
    { group:21, id:61, text: "l'oasis de Siwi" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Pi-Ramsès" }
    { group:21, id:64, text: "Athènes" }
    { group:21, id:65, text: "Clèoantonopolis" }
    { group:22, id:0, text: "'Compagnie vide'" }
    { group:22, id:1, text: "'Les lions'" }
    { group:22, id:2, text: "'Les crocodiles'" }
    { group:22, id:3, text: "'Les cobras'" }
    { group:22, id:4, text: "'Les scorpions'" }
    { group:22, id:5, text: "'Les faucons'" }
    { group:22, id:6, text: "'Les béliers'" }
    { group:22, id:7, text: "'Les léopards'" }
    { group:22, id:8, text: "'Les araignées'" }
    { group:22, id:9, text: "'Les chats'" }
    { group:22, id:10, text: "'Les hyènes'" }
    { group:23, id:0, text: "Rien" }
    { group:23, id:1, text: "Céréales" }
    { group:23, id:2, text: "Viande" }
    { group:23, id:3, text: "Laitue" }
    { group:23, id:4, text: "Pois chiches" }
    { group:23, id:5, text: "Grenades" }
    { group:23, id:6, text: "Figues" }
    { group:23, id:7, text: "Poisson" }
    { group:23, id:8, text: "Gibier" }
    { group:23, id:9, text: "Paille" }
    { group:23, id:10, text: "Armes" }
    { group:23, id:11, text: "Argile" }
    { group:23, id:12, text: "Briques" }
    { group:23, id:13, text: "Poterie" }
    { group:23, id:14, text: "Orge" }
    { group:23, id:15, text: "Bière" }
    { group:23, id:16, text: "Lin" }
    { group:23, id:17, text: "Toile" }
    { group:23, id:18, text: "Gemmes" }
    { group:23, id:19, text: "Articles de luxe" }
    { group:23, id:20, text: "Bois" }
    { group:23, id:21, text: "Or" }
    { group:23, id:22, text: "Roseaux" }
    { group:23, id:23, text: "Papyrus" }
    { group:23, id:24, text: "Pierre" }
    { group:23, id:25, text: "Calcaire" }
    { group:23, id:26, text: "Granit" }
    { group:23, id:27, text: "Albâtre" }
    { group:23, id:28, text: "Char" }
    { group:23, id:29, text: "Cuivre" }
    { group:23, id:30, text: "Grès" }
    { group:23, id:31, text: "Huile" }
    { group:23, id:32, text: "Henné" }
    { group:23, id:33, text: "Peinture" }
    { group:23, id:34, text: "Lampes" }
    { group:23, id:35, text: "Marbre" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Troupes" }
    { group:23, id:38, text: "Bijoux (articles de luxe)" }
    { group:23, id:39, text: "Bijoux" }
    { group:23, id:40, text: "Vin (articles de luxe)" }
    { group:23, id:41, text: "Vin" }
    { group:23, id:42, text: "Ivoire (articles de luxe)" }
    { group:23, id:43, text: "Ivoire" }
    { group:23, id:44, text: "Ebène (articles de luxe)" }
    { group:23, id:45, text: "Ebène" }
    { group:23, id:46, text: "Encens (articles de luxe)" }
    { group:23, id:47, text: "Encens" }
    { group:23, id:48, text: "Huile d'olive (articles de luxe)" }
    { group:23, id:49, text: "Huile d'olive" }
    { group:23, id:50, text: "Peaux de léopard (articles de luxe)" }
    { group:23, id:51, text: "Peaux de léopard" }
    { group:23, id:52, text: "Parfum (articles de luxe)" }
    { group:23, id:53, text: "Parfum" }
    { group:23, id:54, text: "." }
    { group:23, id:55, text: "paniers de céréales" }
    { group:23, id:56, text: "unités de viande" }
    { group:23, id:57, text: "têtes de laitue" }
    { group:23, id:58, text: "jarres de pois chiches" }
    { group:23, id:59, text: "grenades" }
    { group:23, id:60, text: "jarres de figues" }
    { group:23, id:61, text: "seaux de poissons" }
    { group:23, id:62, text: "portions de gibier" }
    { group:23, id:63, text: "mottes de paille" }
    { group:23, id:64, text: "armes" }
    { group:23, id:65, text: "sacs d'argile" }
    { group:23, id:66, text: "briques" }
    { group:23, id:67, text: "pièces de poterie" }
    { group:23, id:68, text: "paquets d'orge" }
    { group:23, id:69, text: "bouteilles de bière" }
    { group:23, id:70, text: "unités de lin" }
    { group:23, id:71, text: "rouleaux de toiles" }
    { group:23, id:72, text: "pierres précieuses" }
    { group:23, id:73, text: "sacs d'articles de luxe" }
    { group:23, id:74, text: "planches de bois" }
    { group:23, id:75, text: "or" }
    { group:23, id:76, text: "roseaux" }
    { group:23, id:77, text: "feuilles de papyrus" }
    { group:23, id:78, text: "blocs de pierre" }
    { group:23, id:79, text: "blocs de calcaire" }
    { group:23, id:80, text: "blocs de granit" }
    { group:23, id:81, text: "." }
    { group:23, id:82, text: "Chars" }
    { group:23, id:83, text: "lingots de cuivre" }
    { group:23, id:84, text: "blocs de grès" }
    { group:23, id:85, text: "jarres d'huile" }
    { group:23, id:86, text: "chargements de henné" }
    { group:23, id:87, text: "seaux de peinture" }
    { group:23, id:88, text: "lampes" }
    { group:23, id:89, text: "blocs de marbre" }
    { group:23, id:90, text: "debens" }
    { group:23, id:91, text: "troupes" }
    { group:24, id:0, text: "1ère semaine" }
    { group:24, id:1, text: "2e semaine" }
    { group:24, id:2, text: "3e semaine" }
    { group:24, id:3, text: "4e semaine" }
    { group:24, id:4, text: "5e semaine" }
    { group:24, id:5, text: "6e semaine" }
    { group:24, id:6, text: "7e semaine" }
    { group:24, id:7, text: "8e semaine" }
    { group:24, id:8, text: "9e semaine" }
    { group:24, id:9, text: "10e semaine" }
    { group:24, id:10, text: "11e semaine" }
    { group:24, id:11, text: "12e semaine" }
    { group:24, id:12, text: "13e semaine" }
    { group:24, id:13, text: "14e semaine" }
    { group:24, id:14, text: "15e semaine" }
    { group:24, id:15, text: "16e semaine" }
    { group:26, id:0, text: "Blanc" }
    { group:26, id:1, text: "Rouge" }
    { group:26, id:2, text: "Bleu" }
    { group:26, id:3, text: "Vert" }
    { group:26, id:4, text: "Orange" }
    { group:26, id:5, text: "Argent" }
    { group:26, id:6, text: "Pourpre" }
    { group:26, id:7, text: "Jaune" }
    { group:26, id:8, text: "Noir" }
    { group:27, id:0, text: "Période prédyn." }
    { group:27, id:1, text: "Période archaïque" }
    { group:27, id:2, text: "Ancien Empire" }
    { group:27, id:3, text: "Moyen Empire" }
    { group:27, id:4, text: "Nouvel Empire" }
    { group:27, id:5, text: "Vallée des Rois" }
    { group:27, id:6, text: "Ramsès II" }
    { group:27, id:7, text: "Anciens conquér." }
    { group:27, id:8, text: "Alexandrie" }
    { group:28, id:0, text: "Nulle part" }
    { group:28, id:1, text: "Annuler" }
    { group:28, id:2, text: "Ferme" }
    { group:28, id:3, text: "Matières premières" }
    { group:28, id:4, text: "Guildes de constructeurs" }
    { group:28, id:5, text: "Route" }
    { group:28, id:6, text: "Mur en terre" }
    { group:28, id:7, text: "Chadouf" }
    { group:28, id:8, text: "Rigole d'irrigation" }
    { group:28, id:9, text: "Creuser" }
    { group:28, id:10, text: "Maison1" }
    { group:28, id:11, text: "Maison2" }
    { group:28, id:12, text: "Maison3" }
    { group:28, id:13, text: "Maison4" }
    { group:28, id:14, text: "Maison5" }
    { group:28, id:15, text: "Maison6" }
    { group:28, id:16, text: "Maison7" }
    { group:28, id:17, text: "Maison8" }
    { group:28, id:18, text: "Maison9" }
    { group:28, id:19, text: "Maison10" }
    { group:28, id:20, text: "Maison11" }
    { group:28, id:21, text: "Maison12" }
    { group:28, id:22, text: "Maison13" }
    { group:28, id:23, text: "Maison14" }
    { group:28, id:24, text: "Maison15" }
    { group:28, id:25, text: "Maison16" }
    { group:28, id:26, text: "Maison17" }
    { group:28, id:27, text: "Maison18" }
    { group:28, id:28, text: "Maison19" }
    { group:28, id:29, text: "Maison20" }
    { group:28, id:30, text: "Kiosque" }
    { group:28, id:31, text: "Etal" }
    { group:28, id:32, text: "Taverne de jeux" }
    { group:28, id:33, text: "Pavillon" }
    { group:28, id:34, text: "Conservatoire" }
    { group:28, id:35, text: "Ecole de danse" }
    { group:28, id:36, text: "Ecole de jonglerie" }
    { group:28, id:37, text: "Maître de senet" }
    { group:28, id:38, text: "Plaza" }
    { group:28, id:39, text: "Jardins" }
    { group:28, id:40, text: "Conducteurs de chars" }
    { group:28, id:41, text: "Petite statue" }
    { group:28, id:42, text: "Statue moyenne" }
    { group:28, id:43, text: "Grande statue" }
    { group:28, id:44, text: "Archers" }
    { group:28, id:45, text: "Fantassins" }
    { group:28, id:46, text: "Pharmacie" }
    { group:28, id:47, text: "Salle des embaumeurs" }
    { group:28, id:48, text: "Monuments" }
    { group:28, id:49, text: "Dentiste" }
    { group:28, id:50, text: "Entrepôt" }
    { group:28, id:51, text: "Ecole de scribes" }
    { group:28, id:52, text: "Gués" }
    { group:28, id:53, text: "Bibliothèque" }
    { group:28, id:54, text: "Rien" }
    { group:28, id:55, text: "Poste de police" }
    { group:28, id:56, text: "Triumphal arch (not used?)" }
    { group:28, id:57, text: "Forts" }
    { group:28, id:58, text: "Corps de garde en terre" }
    { group:28, id:59, text: "Tour en terre" }
    { group:28, id:60, text: "Temple d'Osiris" }
    { group:28, id:61, text: "Temple de Rê" }
    { group:28, id:62, text: "Temple de Ptah" }
    { group:28, id:63, text: "Temple de Seth" }
    { group:28, id:64, text: "Temple de Bastet" }
    { group:28, id:65, text: "Ensemble de temples d'Osiris" }
    { group:28, id:66, text: "Ensemble de temples de Rê" }
    { group:28, id:67, text: "Ensemble de temples de Ptah" }
    { group:28, id:68, text: "Ensemble de temples de Seth" }
    { group:28, id:69, text: "Ensemble de temples de Bastet" }
    { group:28, id:70, text: "Bazar" }
    { group:28, id:71, text: "Grenier" }
    { group:28, id:72, text: "Entrepôt" }
    { group:28, id:73, text: "Entrepôts" }
    { group:28, id:74, text: "Fabrique de bateaux" }
    { group:28, id:75, text: "Dock" }
    { group:28, id:76, text: "Quai" }
    { group:28, id:77, text: "Demeure luxueuse personnelle" }
    { group:28, id:78, text: "Demeure luxueuse familiale" }
    { group:28, id:79, text: "Demeure luxueuse de dynastie" }
    { group:28, id:80, text: "Mission (not used?)" }
    { group:28, id:81, text: "Architecte" }
    { group:28, id:82, text: "Pont" }
    { group:28, id:83, text: "Pont surélevé" }
    { group:28, id:84, text: "Palais de village" }
    { group:28, id:85, text: "Palais en ville" }
    { group:28, id:86, text: "Percepteur" }
    { group:28, id:87, text: "Percepteur" }
    { group:28, id:88, text: "Rien" }
    { group:28, id:89, text: "Rien" }
    { group:28, id:90, text: "Chadouf" }
    { group:28, id:91, text: "Embellissement" }
    { group:28, id:92, text: "Puits" }
    { group:28, id:93, text: "Rien" }
    { group:28, id:94, text: "Académie" }
    { group:28, id:95, text: "Centre de recrutement" }
    { group:28, id:96, text: "Temples" }
    { group:28, id:97, text: "Ensemble de temples" }
    { group:28, id:98, text: "Oracle" }
    { group:28, id:99, text: "Ruines en flammes" }
    { group:28, id:100, text: "Orge" }
    { group:28, id:101, text: "Lin" }
    { group:28, id:102, text: "Céréales" }
    { group:28, id:103, text: "Laitue" }
    { group:28, id:104, text: "Grenades" }
    { group:28, id:105, text: "Pois chiches" }
    { group:28, id:106, text: "Carrière de pierre" }
    { group:28, id:107, text: "Carrière de calcaire" }
    { group:28, id:108, text: "Chantier de bois" }
    { group:28, id:109, text: "Puits d'argile" }
    { group:28, id:110, text: "Brasserie" }
    { group:28, id:111, text: "Atelier de tissage" }
    { group:28, id:112, text: "Fabrique d'armes" }
    { group:28, id:113, text: "Orfèvrerie" }
    { group:28, id:114, text: "Poterie" }
    { group:28, id:115, text: "Pavillon de chasse" }
    { group:28, id:116, text: "Rien" }
    { group:28, id:117, text: "Rien" }
    { group:28, id:118, text: "Rien" }
    { group:28, id:119, text: "Rien" }
    { group:28, id:120, text: "Plateau (not used?)" }
    { group:28, id:121, text: "Crack (not used?)" }
    { group:28, id:122, text: "Anti plateau (not used?)" }
    { group:28, id:123, text: "Rien" }
    { group:28, id:124, text: "Rien" }
    { group:28, id:125, text: "Rien" }
    { group:28, id:126, text: "Rien" }
    { group:28, id:127, text: "Rien" }
    { group:28, id:128, text: "Rien" }
    { group:28, id:129, text: "Rien" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Embarcadère" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Barrage routier" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Sanctuaire d'Osiris" }
    { group:28, id:141, text: "Sanctuaire de Rê" }
    { group:28, id:142, text: "Sanctuaire de Ptah" }
    { group:28, id:143, text: "Sanctuaire de Seth" }
    { group:28, id:144, text: "Sanctuaire de Bastet" }
    { group:28, id:145, text: "Sanctuaire de" }
    { group:28, id:146, text: "Sanctuaire de" }
    { group:28, id:147, text: "Sanctuaire de" }
    { group:28, id:148, text: "Sanctuaire de" }
    { group:28, id:149, text: "Sanctuaire de" }
    { group:28, id:150, text: "Sanctuaires" }
    { group:28, id:151, text: "Temple d'Osiris" }
    { group:28, id:152, text: "Temple de Rê" }
    { group:28, id:153, text: "Temple de Ptah" }
    { group:28, id:154, text: "Temple de Seth" }
    { group:28, id:155, text: "Temple de Bastet" }
    { group:28, id:156, text: "God 5" }
    { group:28, id:157, text: "God 6" }
    { group:28, id:158, text: "God 7" }
    { group:28, id:159, text: "God 8" }
    { group:28, id:160, text: "God 9" }
    { group:28, id:161, text: "Mine d'or" }
    { group:28, id:162, text: "Mine de pierres précieuses" }
    { group:28, id:163, text: "Roche ordinaire" }
    { group:28, id:164, text: "Roche contenant du minerai" }
    { group:28, id:165, text: "Sans utilisation" }
    { group:28, id:166, text: "Sans utilisation" }
    { group:28, id:167, text: "Caserne de pompiers" }
    { group:28, id:168, text: "Mur de briques" }
    { group:28, id:169, text: "Mur" }
    { group:28, id:170, text: "Corps de garde en brique" }
    { group:28, id:171, text: "Corps de garde" }
    { group:28, id:172, text: "Tour en brique" }
    { group:28, id:173, text: "Tour" }
    { group:28, id:174, text: "Structures en terre" }
    { group:28, id:175, text: "Structures en brique" }
    { group:28, id:176, text: "Structures défensives" }
    { group:28, id:177, text: "Guilde de menuisiers" }
    { group:28, id:178, text: "Guilde de maçons" }
    { group:28, id:179, text: "Guilde de tailleurs de pierre" }
    { group:28, id:180, text: "Point d'eau" }
    { group:28, id:181, text: "Quai de transporteurs" }
    { group:28, id:182, text: "Quai de navires de guerre" }
    { group:28, id:183, text: "Pyramide" }
    { group:28, id:184, text: "Palais de justice" }
    { group:28, id:185, text: "Académie 2" }
    { group:28, id:186, text: "Académie 3" }
    { group:28, id:187, text: "Palais de village" }
    { group:28, id:188, text: "Palais en ville" }
    { group:28, id:189, text: "Palais citadin" }
    { group:28, id:190, text: "Bazar 2" }
    { group:28, id:191, text: "Grenier 2" }
    { group:28, id:192, text: "Dock 2" }
    { group:28, id:193, text: "Entrepôt 2" }
    { group:28, id:194, text: "Ferme d'élevage" }
    { group:28, id:195, text: "Cueilleur de roseaux" }
    { group:28, id:196, text: "Exploitation de figues" }
    { group:28, id:197, text: "Marécage" }
    { group:28, id:198, text: "Dunes de sable" }
    { group:28, id:199, text: "Chantier" }
    { group:28, id:200, text: "Corps de garde en terre" }
    { group:28, id:201, text: "Corps de garde en brique" }
    { group:28, id:202, text: "Corps de garde" }
    { group:28, id:203, text: "Fabrique de papyrus" }
    { group:28, id:204, text: "Briqueterie" }
    { group:28, id:205, text: "Fabrique de chars" }
    { group:28, id:206, text: "Médecin" }
    { group:28, id:207, text: "Placeholder4" }
    { group:28, id:208, text: "Placeholder5" }
    { group:28, id:209, text: "Place des fêtes" }
    { group:28, id:210, text: "Sphinx" }
    { group:28, id:211, text: "Extension d'un ensemble de temples" }
    { group:28, id:212, text: "Extension d'un ensemble de temples" }
    { group:28, id:213, text: "Placeholder10" }
    { group:28, id:214, text: "Point de débarquement" }
    { group:28, id:215, text: "Carrière d'albâtre (not used?)" }
    { group:28, id:216, text: "Carrière de granit" }
    { group:28, id:217, text: "Mine de cuivre" }
    { group:28, id:218, text: "temp" }
    { group:28, id:219, text: "temp" }
    { group:28, id:220, text: "temp" }
    { group:28, id:221, text: "Carrière de grès" }
    { group:28, id:222, text: "Mausolée" }
    { group:28, id:223, text: "Falaise" }
    { group:28, id:224, text: "Henné" }
    { group:28, id:225, text: "Bibliothèque d'Alexandrie" }
    { group:28, id:226, text: "Zoo" }
    { group:28, id:227, text: "Caesareum" }
    { group:28, id:228, text: "Phare de Pharos" }
    { group:28, id:229, text: "Petite Tombe Royale" }
    { group:28, id:230, text: "Abou Simbel" }
    { group:28, id:231, text: "Guilde des artisans" }
    { group:28, id:232, text: "Fabrique de lampes" }
    { group:28, id:233, text: "Fabrique de peinture" }
    { group:28, id:234, text: "Tombe Royale Moyenne" }
    { group:28, id:235, text: "Grande Tombe Royale" }
    { group:28, id:236, text: "Très Grande Tombe Royale" }
    { group:29, id:0, text: "Hutte rudimentaire" }
    { group:29, id:1, text: "Hutte solide" }
    { group:29, id:2, text: "Cabane rudimentaire" }
    { group:29, id:3, text: "Cabane commune" }
    { group:29, id:4, text: "Chaumière rudimentaire" }
    { group:29, id:5, text: "Chaumière ordinaire" }
    { group:29, id:6, text: "Propriété modeste" }
    { group:29, id:7, text: "Propriété spacieuse" }
    { group:29, id:8, text: "Appartement modeste" }
    { group:29, id:9, text: "Appartement spacieux" }
    { group:29, id:10, text: "Résidence commune" }
    { group:29, id:11, text: "Résidence spacieuse" }
    { group:29, id:12, text: "Résidence élégante" }
    { group:29, id:13, text: "Résidence de luxe" }
    { group:29, id:14, text: "Manoir commun" }
    { group:29, id:15, text: "Manoir spacieux" }
    { group:29, id:16, text: "Manoir élégant" }
    { group:29, id:17, text: "Manoir imposant" }
    { group:29, id:18, text: "Domaine modeste" }
    { group:29, id:19, text: "Magnifique domaine" }
    { group:29, id:20, text: "Huttes rudimentaires" }
    { group:29, id:21, text: "Huttes solides" }
    { group:29, id:22, text: "Cabanes rudimentaires" }
    { group:29, id:23, text: "Cabanes communes" }
    { group:29, id:24, text: "Chaumières rudim." }
    { group:29, id:25, text: "Chaumières ordin." }
    { group:29, id:26, text: "Propriétés modestes" }
    { group:29, id:27, text: "Propriétés spacieuses" }
    { group:29, id:28, text: "Appartements modestes" }
    { group:29, id:29, text: "Appartements spacieux" }
    { group:29, id:30, text: "Résidences communes" }
    { group:29, id:31, text: "Résidences spacieuses" }
    { group:29, id:32, text: "Résidences élégantes" }
    { group:29, id:33, text: "Résidences de luxe" }
    { group:29, id:34, text: "Manoirs communs" }
    { group:29, id:35, text: "Manoirs spacieux" }
    { group:29, id:36, text: "Manoirs élégants" }
    { group:29, id:37, text: "Manoirs imposants" }
    { group:29, id:38, text: "Domaines modestes" }
    { group:29, id:39, text: "Magnifiques domaines" }
    { group:29, id:40, text: "Huttes rudimentaires:" }
    { group:29, id:41, text: "Huttes solides:" }
    { group:29, id:42, text: "Cabanes rudimentaires:" }
    { group:29, id:43, text: "Cabanes communes:" }
    { group:29, id:44, text: "Chaumières rudim.:" }
    { group:29, id:45, text: "Chaumières ordin.:" }
    { group:29, id:46, text: "Propriétés modestes:" }
    { group:29, id:47, text: "Propriétés spacieuses:" }
    { group:29, id:48, text: "Appartements modestes:" }
    { group:29, id:49, text: "Appartements spacieux:" }
    { group:29, id:50, text: "Résidences communes:" }
    { group:29, id:51, text: "Résidences spacieuses:" }
    { group:29, id:52, text: "Résidences élégantes:" }
    { group:29, id:53, text: "Résidences de luxe:" }
    { group:29, id:54, text: "Manoirs communs:" }
    { group:29, id:55, text: "Manoirs spacieux:" }
    { group:29, id:56, text: "Manoirs élégants:" }
    { group:29, id:57, text: "Manoirs imposants:" }
    { group:29, id:58, text: "Domaines modestes:" }
    { group:29, id:59, text: "Magnifiques domaines:" }
    { group:30, id:0, text: "Pharaon/La Reine du Nil" }
    { group:30, id:1, text: "Exécuter la démo de Pharaon" }
    { group:30, id:2, text: "Visiter le site Web de Pharaon" }
    { group:30, id:3, text: "Editeur de cartes" }
    { group:30, id:4, text: "Quitter" }
    { group:30, id:5, text: "Familles prestigieuses" }
    { group:31, id:0, text: "Entrez un nom de famille" }
    { group:31, id:1, text: "Clic droit pour continuer" }
    { group:32, id:0, text: "Doyen du village" }
    { group:32, id:1, text: "Noble du village" }
    { group:32, id:2, text: "Erudit du royaume" }
    { group:32, id:3, text: "Scribe du royaume" }
    { group:32, id:4, text: "Juge du royaume" }
    { group:32, id:5, text: "Maire du royaume" }
    { group:32, id:6, text: "Gouverneur du royaume" }
    { group:32, id:7, text: "Nomarque" }
    { group:32, id:8, text: "Chancelier" }
    { group:32, id:9, text: "Vizir" }
    { group:32, id:10, text: "Pharaon" }
    { group:32, id:11, text: "Ô Doyen du village" }
    { group:32, id:12, text: "Ô Noble du village" }
    { group:32, id:13, text: "Ô Erudit du royaume" }
    { group:32, id:14, text: "Ô Scribe du royaume" }
    { group:32, id:15, text: "Ô Juge du royaume" }
    { group:32, id:16, text: "Ô Maire du royaume" }
    { group:32, id:17, text: "Ô Gouverneur du royaume" }
    { group:32, id:18, text: "Ô Nomarque" }
    { group:32, id:19, text: "Ô Chancelier" }
    { group:32, id:20, text: "Ô Vizir" }
    { group:32, id:21, text: "Ô Grand pharaon" }
    { group:32, id:22, text: "Mission insignifiante" }
    { group:32, id:23, text: "Mission très facile" }
    { group:32, id:24, text: "Mission facile" }
    { group:32, id:25, text: "Mission assez facile" }
    { group:32, id:26, text: "Mission normale" }
    { group:32, id:27, text: "Mission assez difficile" }
    { group:32, id:28, text: "Mission difficile" }
    { group:32, id:29, text: "Mission très difficile" }
    { group:32, id:30, text: "Mission extrêmement difficile" }
    { group:32, id:31, text: "Mission quasiment impossible" }
    { group:33, id:0, text: "Mini carte" }
    { group:33, id:1, text: "Petite carte" }
    { group:33, id:2, text: "Carte moyenne" }
    { group:33, id:3, text: "Grande carte" }
    { group:33, id:4, text: "Carte étendue" }
    { group:33, id:5, text: "Carte immense" }
    { group:33, id:6, text: "Annuler" }
    { group:34, id:0, text: "Pas d'envahisseurs" }
    { group:34, id:1, text: "Armée ennemie" }
    { group:34, id:2, text: "Armée égyptienne" }
    { group:34, id:3, text: "Armée du pharaon" }
    { group:34, id:4, text: "Armée bédouine" }
    { group:35, id:0, text: "la cité égyptienne tombe" }
    { group:35, id:1, text: "la cité étrangère est conquise" }
    { group:35, id:2, text: "Route accessible" }
    { group:35, id:3, text: "Route interrompue" }
    { group:35, id:4, text: "cité commerçante assiégée" }
    { group:36, id:0, text: "Attaquer les productions de nourriture" }
    { group:36, id:1, text: "Attaquer les réserves d'or" }
    { group:36, id:2, text: "Attaquer les bâtiments principaux" }
    { group:36, id:3, text: "Attaquer les troupes" }
    { group:36, id:4, text: "Attaque aléatoire" }
    { group:37, id:0, text: "Hyksos" }
    { group:37, id:1, text: "Peuples de la mer" }
    { group:37, id:2, text: "Hittites" }
    { group:37, id:3, text: "Mitanni" }
    { group:37, id:4, text: "Ethiopiens" }
    { group:37, id:5, text: "Libyens" }
    { group:37, id:6, text: "Nubiens" }
    { group:37, id:7, text: "Cananéens" }
    { group:37, id:8, text: "Assyriens" }
    { group:37, id:9, text: "Romains" }
    { group:37, id:10, text: "Phéniciens" }
    { group:37, id:11, text: "Perses" }
    { group:37, id:12, text: "Egyptiens" }
    { group:37, id:13, text: "Bédouins" }
    { group:37, id:14, text: "Un soldat hyksos" }
    { group:37, id:15, text: "Un soldat des peuples de la mer" }
    { group:37, id:16, text: "Un soldat hittite" }
    { group:37, id:17, text: "Un soldat Mitanni" }
    { group:37, id:18, text: "Un soldat éthiopien" }
    { group:37, id:19, text: "Un soldat libyen" }
    { group:37, id:20, text: "Un soldat nubien" }
    { group:37, id:21, text: "Un soldat cananéen" }
    { group:37, id:22, text: "Soldat assyrien" }
    { group:37, id:23, text: "Soldat romain" }
    { group:37, id:24, text: "Soldat phénicien" }
    { group:37, id:25, text: "Soldat perse" }
    { group:37, id:26, text: "Un soldat égyptien" }
    { group:37, id:27, text: "Un soldat bédouin" }
    { group:37, id:28, text: "une armée hyksos" }
    { group:37, id:29, text: "une armée des peuples de la mer" }
    { group:37, id:30, text: "une armée hittite" }
    { group:37, id:31, text: "une armée Mitanni" }
    { group:37, id:32, text: "une armée éthiopienne" }
    { group:37, id:33, text: "une armée libyenne" }
    { group:37, id:34, text: "une armée nubienne" }
    { group:37, id:35, text: "une armée cananéenne" }
    { group:37, id:36, text: "une armée assyrienne" }
    { group:37, id:37, text: "une armée romaine" }
    { group:37, id:38, text: "une armée phénicienne" }
    { group:37, id:39, text: "une armée perse" }
    { group:37, id:40, text: "une armée égyptienne" }
    { group:37, id:41, text: "une armée bédouine" }
    { group:38, id:0, text: "Evénements spéciaux" }
    { group:38, id:1, text: "Tremblement de terre" }
    { group:38, id:2, text: "Révolte des gladiateurs" }
    { group:38, id:3, text: "Changement de pharaon" }
    { group:38, id:4, text: "Problème de route maritime" }
    { group:38, id:5, text: "Problème de route terrestre" }
    { group:38, id:6, text: "Le pharaon augmente les salaires" }
    { group:38, id:7, text: "Le pharaon baisse les salaires" }
    { group:38, id:8, text: "Eau contaminée" }
    { group:38, id:9, text: "Effondrement de la mine d'or" }
    { group:38, id:10, text: "Puits d'argile inondé" }
    { group:38, id:11, text: "En activité" }
    { group:38, id:12, text: "Synchronisation" }
    { group:38, id:13, text: "Aléatoire" }
    { group:39, id:0, text: "Notre cité" }
    { group:39, id:1, text: "Cité commerçante du pharaon" }
    { group:39, id:2, text: "Cité du pharaon" }
    { group:39, id:3, text: "Cité commerçante égyptienne" }
    { group:39, id:4, text: "Cité égyptienne" }
    { group:39, id:5, text: "Cité commerçante étrangère" }
    { group:39, id:6, text: "Cité étrangère" }
    { group:40, id:0, text: "aucun" }
    { group:40, id:1, text: "Mineur" }
    { group:40, id:2, text: "Moyen" }
    { group:40, id:3, text: "Majeur" }
    { group:41, id:0, text: "Nulle part" }
    { group:41, id:1, text: "Rien" }
    { group:41, id:2, text: "Rien" }
    { group:41, id:3, text: "Rien" }
    { group:41, id:4, text: "Rien" }
    { group:41, id:5, text: "Route" }
    { group:41, id:6, text: "Mur en terre" }
    { group:41, id:7, text: "Rigole d'irrigation" }
    { group:41, id:8, text: "Chadouf" }
    { group:41, id:9, text: "Rien" }
    { group:41, id:10, text: "Hutte rudimentaire" }
    { group:41, id:11, text: "Hutte solide" }
    { group:41, id:12, text: "Cabane rudimentaire" }
    { group:41, id:13, text: "Cabane commune" }
    { group:41, id:14, text: "Chaumière rudimentaire" }
    { group:41, id:15, text: "Chaumière ordinaire" }
    { group:41, id:16, text: "Propriété modeste" }
    { group:41, id:17, text: "Propriété spacieuse" }
    { group:41, id:18, text: "Appartement modeste" }
    { group:41, id:19, text: "Appartement spacieux" }
    { group:41, id:20, text: "Résidence commune" }
    { group:41, id:21, text: "Résidence spacieuse" }
    { group:41, id:22, text: "Résidence élégante" }
    { group:41, id:23, text: "Résidence de luxe" }
    { group:41, id:24, text: "Manoir commun" }
    { group:41, id:25, text: "Manoir spacieux" }
    { group:41, id:26, text: "Manoir élégant" }
    { group:41, id:27, text: "Manoir imposant" }
    { group:41, id:28, text: "Domaine modeste" }
    { group:41, id:29, text: "Magnifique domaine" }
    { group:41, id:30, text: "Kiosque à musique" }
    { group:41, id:31, text: "Etal" }
    { group:41, id:32, text: "Taverne de jeux" }
    { group:41, id:33, text: "Théâtre de danse" }
    { group:41, id:34, text: "Conservatoire" }
    { group:41, id:35, text: "Ecole de danse" }
    { group:41, id:36, text: "Ecole de jonglerie" }
    { group:41, id:37, text: "Centre de formation à la conduite de chars" }
    { group:41, id:38, text: "Plaza" }
    { group:41, id:39, text: "Jardins" }
    { group:41, id:40, text: "Fort d'infanterie" }
    { group:41, id:41, text: "Petite statue" }
    { group:41, id:42, text: "Statue moyenne" }
    { group:41, id:43, text: "Grande statue" }
    { group:41, id:44, text: "Archers" }
    { group:41, id:45, text: "Fantassins" }
    { group:41, id:46, text: "Pharmacie" }
    { group:41, id:47, text: "Salle des embaumeurs" }
    { group:41, id:48, text: "Monuments" }
    { group:41, id:49, text: "Dentiste" }
    { group:41, id:50, text: "Centre de distribution" }
    { group:41, id:51, text: "Ecole de scribes" }
    { group:41, id:52, text: "Gués" }
    { group:41, id:53, text: "Bibliothèque" }
    { group:41, id:54, text: "Rien" }
    { group:41, id:55, text: "Poste de police" }
    { group:41, id:56, text: "Triumphal arch (not used?)" }
    { group:41, id:57, text: "Forts" }
    { group:41, id:58, text: "Corps de garde en terre" }
    { group:41, id:59, text: "Tour en terre" }
    { group:41, id:60, text: "Temple d'Osiris" }
    { group:41, id:61, text: "Temple de Rê" }
    { group:41, id:62, text: "Temple de Ptah" }
    { group:41, id:63, text: "Temple de Seth" }
    { group:41, id:64, text: "Temple de Bastet" }
    { group:41, id:65, text: "Ensemble de temples d'Osiris" }
    { group:41, id:66, text: "Ensemble de temples de Rê" }
    { group:41, id:67, text: "Ensemble de temples de Ptah" }
    { group:41, id:68, text: "Ensemble de temples de Seth" }
    { group:41, id:69, text: "Ensemble de temples de Bastet" }
    { group:41, id:70, text: "Bazar" }
    { group:41, id:71, text: "Grenier" }
    { group:41, id:72, text: "Entrepôt" }
    { group:41, id:73, text: "Entrepôts" }
    { group:41, id:74, text: "Fabrique de bateaux" }
    { group:41, id:75, text: "Dock" }
    { group:41, id:76, text: "Quai" }
    { group:41, id:77, text: "Demeure luxueuse personnelle" }
    { group:41, id:78, text: "Demeure luxueuse familiale" }
    { group:41, id:79, text: "Demeure luxueuse de dynastie" }
    { group:41, id:80, text: "Mission" }
    { group:41, id:81, text: "Etude d'architecte" }
    { group:41, id:82, text: "Petit pont" }
    { group:41, id:83, text: "Grand pont" }
    { group:41, id:84, text: "Palais de village" }
    { group:41, id:85, text: "Palais en ville" }
    { group:41, id:86, text: "Percepteur" }
    { group:41, id:87, text: "Percepteur" }
    { group:41, id:88, text: "Hutte indigène" }
    { group:41, id:89, text: "Forum des indigènes" }
    { group:41, id:90, text: "Chadouf" }
    { group:41, id:91, text: "Embellissement" }
    { group:41, id:92, text: "Puits" }
    { group:41, id:93, text: "Rien" }
    { group:41, id:94, text: "Académie" }
    { group:41, id:95, text: "Centre de recrutement" }
    { group:41, id:96, text: "Rien" }
    { group:41, id:97, text: "Rien" }
    { group:41, id:98, text: "Oracle" }
    { group:41, id:99, text: "Ruines en flammes" }
    { group:41, id:100, text: "Exploitation d'orge" }
    { group:41, id:101, text: "Exploitation de lin" }
    { group:41, id:102, text: "Exploitation de céréales" }
    { group:41, id:103, text: "Exploitation de laitues" }
    { group:41, id:104, text: "Exploitation de grenades" }
    { group:41, id:105, text: "Exploitation de pois chiches" }
    { group:41, id:106, text: "Carrière de pierre" }
    { group:41, id:107, text: "Carière de calcaire" }
    { group:41, id:108, text: "Chantier de bois" }
    { group:41, id:109, text: "Puits d'argile" }
    { group:41, id:110, text: "Brasserie" }
    { group:41, id:111, text: "Atelier de tissage" }
    { group:41, id:112, text: "Fabrique d'armes" }
    { group:41, id:113, text: "Orfèvrerie" }
    { group:41, id:114, text: "Poterie" }
    { group:41, id:115, text: "Pavillon de chasse" }
    { group:41, id:116, text: "Herbe" }
    { group:41, id:117, text: "Arbres" }
    { group:41, id:118, text: "Eau" }
    { group:41, id:119, text: "Tremblement de terre" }
    { group:41, id:120, text: "Broussailles" }
    { group:41, id:121, text: "Rochers" }
    { group:41, id:122, text: "Prairie" }
    { group:41, id:123, text: "Plateau (not used?)" }
    { group:41, id:124, text: "Anti Plateau (not used?)" }
    { group:41, id:125, text: "Route" }
    { group:41, id:126, text: "Point d'invasion" }
    { group:41, id:127, text: "Point d'entrée" }
    { group:41, id:128, text: "Point de sortie" }
    { group:41, id:129, text: "Ramp (not used?)" }
    { group:41, id:130, text: "Entrée rivière" }
    { group:41, id:131, text: "Sortie rivière" }
    { group:41, id:132, text: "Point de pêche" }
    { group:41, id:133, text: "Point de prédateurs" }
    { group:41, id:134, text: "Plaine inondable" }
    { group:41, id:135, text: "Irrigation" }
    { group:41, id:136, text: "Embarcadère" }
    { group:41, id:137, text: "Réseau routier" }
    { group:41, id:138, text: "Aucun accès" }
    { group:41, id:139, text: "Point de gibier" }
    { group:41, id:140, text: "Sanctuaire d'Osiris" }
    { group:41, id:141, text: "Sanctuaire de Rê" }
    { group:41, id:142, text: "Sanctuaire de Ptah" }
    { group:41, id:143, text: "Sanctuaire de Seth" }
    { group:41, id:144, text: "Sanctuaire de Bastet" }
    { group:41, id:145, text: "Shrine God5" }
    { group:41, id:146, text: "Shrine God6" }
    { group:41, id:147, text: "Shrine God7" }
    { group:41, id:148, text: "Shrine God8" }
    { group:41, id:149, text: "Shrine God9" }
    { group:41, id:150, text: "Sanctuaire" }
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
    { group:41, id:161, text: "Mine d'or" }
    { group:41, id:162, text: "Mine de pierres précieuses" }
    { group:41, id:163, text: "Roche ordinaire" }
    { group:41, id:164, text: "Roche aurifère" }
    { group:41, id:165, text: "Roche gemmifère" }
    { group:41, id:166, text: "Roche polie" }
    { group:41, id:167, text: "Caserne de pompiers" }
    { group:41, id:168, text: "Mur de briques" }
    { group:41, id:169, text: "Mur" }
    { group:41, id:170, text: "Corps de garde en brique" }
    { group:41, id:171, text: "Corps de garde" }
    { group:41, id:172, text: "Tour en brique" }
    { group:41, id:173, text: "Tour" }
    { group:41, id:174, text: "Structures en terre" }
    { group:41, id:175, text: "Structures en brique" }
    { group:41, id:176, text: "Structures défensives" }
    { group:41, id:177, text: "Guilde de menuisiers" }
    { group:41, id:178, text: "Guilde de maçons" }
    { group:41, id:179, text: "Guilde de tailleurs de pierre" }
    { group:41, id:180, text: "Point d'eau" }
    { group:41, id:181, text: "Quai de transporteurs" }
    { group:41, id:182, text: "Quai de navires de guerre" }
    { group:41, id:183, text: "Pyramide" }
    { group:41, id:184, text: "Palais de justice" }
    { group:41, id:185, text: "Académie militaire 2" }
    { group:41, id:186, text: "Académie militaire 3" }
    { group:41, id:187, text: "Palais de village" }
    { group:41, id:188, text: "Palais en ville" }
    { group:41, id:189, text: "Palais citadin" }
    { group:41, id:190, text: "Bazar 2" }
    { group:41, id:191, text: "Grenier 2" }
    { group:41, id:192, text: "Dock 2" }
    { group:41, id:193, text: "Entrepôt 2" }
    { group:41, id:194, text: "Ferme d'élevage" }
    { group:41, id:195, text: "Cueilleur de roseaux" }
    { group:41, id:196, text: "Exploitation de figues" }
    { group:41, id:197, text: "Marécage" }
    { group:41, id:198, text: "Dune de sable" }
    { group:41, id:199, text: "Chantier" }
    { group:41, id:200, text: "Corps de garde en terre" }
    { group:41, id:201, text: "Corps de garde en brique" }
    { group:41, id:202, text: "Corps de garde" }
    { group:41, id:203, text: "Fabrique de papyrus" }
    { group:41, id:204, text: "Briqueterie" }
    { group:41, id:205, text: "Fabrique de chars" }
    { group:41, id:206, text: "Médecin" }
    { group:41, id:207, text: "Placeholder4" }
    { group:41, id:208, text: "Placeholder5" }
    { group:41, id:209, text: "Place des fêtes" }
    { group:41, id:210, text: "Sphinx" }
    { group:41, id:211, text: "Extension d'un ensemble de temples" }
    { group:41, id:212, text: "Extension d'un ensemble de temples" }
    { group:41, id:213, text: "Placeholder10" }
    { group:41, id:214, text: "Point de débarquement" }
    { group:41, id:215, text: "temp" }
    { group:41, id:216, text: "Carrière de granit" }
    { group:41, id:217, text: "Mine de cuivre" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Carrière de grès" }
    { group:41, id:222, text: "Mausolée" }
    { group:41, id:223, text: "Falaise" }
    { group:41, id:224, text: "Exploitation de henné" }
    { group:41, id:225, text: "Bibliothèque d'Alexandrie" }
    { group:41, id:226, text: "Zoo" }
    { group:41, id:227, text: "Caesareum" }
    { group:41, id:228, text: "Phare de Pharos" }
    { group:41, id:229, text: "Petite Tombe Royale" }
    { group:41, id:230, text: "Abou Simbel" }
    { group:41, id:231, text: "Guilde des artisans" }
    { group:41, id:232, text: "Fabrique de lampes" }
    { group:41, id:233, text: "Fabrique de peinture" }
    { group:41, id:234, text: "Tombe Royale Moyenne" }
    { group:41, id:235, text: "Grande Tombe Royale" }
    { group:41, id:236, text: "Très Grande Tombe Royale" }
    { group:42, id:1, text: "Plein écran" }
    { group:42, id:2, text: "Fenêtre" }
    { group:42, id:3, text: "Résolution 640 x 480" }
    { group:42, id:4, text: "Résolution 800 x 600" }
    { group:42, id:5, text: "Résolution 1024 x 768" }
    { group:42, id:6, text: "Annuler" }
    { group:43, id:0, text: "Enregistrement de votre cité" }
    { group:43, id:1, text: "Chargement d'une cité" }
    { group:43, id:2, text: "Le fichier n'existe pas" }
    { group:43, id:3, text: "Enregistrement d'une province" }
    { group:43, id:4, text: "  Chargement d'une province" }
    { group:43, id:5, text: "Continuer ?" }
    { group:43, id:6, text: "Supprimer un fichier" }
    { group:43, id:7, text: "Impossible de charger ce fichier" }
    { group:44, id:0, text: "Ajouter" }
    { group:44, id:1, text: "Editer" }
    { group:44, id:2, text: "Supprimer" }
    { group:44, id:3, text: "Général" }
    { group:44, id:4, text: "Importer la carte" }
    { group:44, id:5, text: "Achats" }
    { group:44, id:6, text: "pas libre" }
    { group:44, id:7, text: "OK" }
    { group:44, id:8, text: "Graphique simple" }
    { group:44, id:9, text: "Cité" }
    { group:44, id:10, text: "Région" }
    { group:44, id:11, text: "Marqueur de bataille" }
    { group:44, id:12, text: "libre" }
    { group:44, id:13, text: "Date de début" }
    { group:44, id:14, text: "Requêtes du pharaon" }
    { group:44, id:15, text: "Invasions" }
    { group:44, id:16, text: "OK" }
    { group:44, id:17, text: "Annuler" }
    { group:44, id:18, text: "Niveau actuel du royaume" }
    { group:44, id:19, text: "Pas de requêtes" }
    { group:44, id:20, text: "Pas d'invasions" }
    { group:44, id:21, text: "Mission pas encore gagnée" }
    { group:44, id:22, text: "Planification d'une invasion" }
    { group:44, id:23, text: "Emplacement libre" }
    { group:44, id:24, text: "en" }
    { group:44, id:25, text: "Annulation de la requête" }
    { group:44, id:26, text: "Annulation de l'invasion" }
    { group:44, id:27, text: "de" }
    { group:44, id:28, text: "Route terrestre" }
    { group:44, id:29, text: "Route maritime" }
    { group:44, id:30, text: "Marqueur d'armée" }
    { group:44, id:31, text: "Marqueur d'ennemi" }
    { group:44, id:32, text: "Route" }
    { group:44, id:33, text: "Demande" }
    { group:44, id:34, text: "Coût" }
    { group:44, id:35, text: "Ressources" }
    { group:44, id:36, text: "Ventes" }
    { group:44, id:37, text: "Description brève" }
    { group:44, id:38, text: "Brève description de cette carte pour les joueurs. Historique, objectifs, astuces, etc." }
    { group:44, id:39, text: "Budget de départ" }
    { group:44, id:40, text: "Requêtes" }
    { group:44, id:41, text: "Les ennemis sont les" }
    { group:44, id:42, text: "Invasions" }
    { group:44, id:43, text: "La capitale fournit-elle des céréales ?" }
    { group:44, id:44, text: "Bâtiments autorisés" }
    { group:44, id:45, text: "Critères de victoire" }
    { group:44, id:46, text: "Ajuster" }
    { group:44, id:47, text: "Structures autorisées" }
    { group:44, id:48, text: "Critères de victoire" }
    { group:44, id:49, text: "Evénements spéciaux" }
    { group:44, id:50, text: "Culture requise" }
    { group:44, id:51, text: "Prospérité requise" }
    { group:44, id:52, text: "Nombre de monuments" }
    { group:44, id:53, text: "Royaume requis" }
    { group:44, id:54, text: "Limite de temps (durée maximale)" }
    { group:44, id:55, text: "Survie (durée minimale)" }
    { group:44, id:56, text: "Nombre d'habitants" }
    { group:44, id:57, text: "Point de séisme requis" }
    { group:44, id:58, text: "Ligne de faille fixée" }
    { group:44, id:59, text: "Pas de point d'entrée" }
    { group:44, id:60, text: "Pas de points de peuple" }
    { group:44, id:61, text: "Pas de point de sortie" }
    { group:44, id:62, text: "Points de peuple fixés" }
    { group:44, id:63, text: "Pas de points d'invasion" }
    { group:44, id:64, text: "1 point d'invasion" }
    { group:44, id:65, text: "points d'invasion" }
    { group:44, id:66, text: "Pas de points de rivière" }
    { group:44, id:67, text: "Points de rivière fixés" }
    { group:44, id:68, text: "Offrande du pharaon" }
    { group:44, id:69, text: "Marqueur de bataille" }
    { group:44, id:70, text: "Chemin" }
    { group:44, id:71, text: "Ordre" }
    { group:44, id:72, text: "Veut" }
    { group:44, id:73, text: "Royaume" }
    { group:44, id:74, text: "Bornes à" }
    { group:44, id:75, text: "Sauver" }
    { group:44, id:76, text: "Type de Terrain" }
    { group:44, id:77, text: "Climat humide" }
    { group:44, id:78, text: "Climat normal" }
    { group:44, id:79, text: "Climat aride" }
    { group:44, id:80, text: "Débris actifs ?" }
    { group:44, id:81, text: "Expansion à" }
    { group:44, id:82, text: "Positions étendues" }
    { group:44, id:83, text: "Régler les niveaux d'offre et de demande" }
    { group:44, id:84, text: "Aucun" }
    { group:44, id:85, text: "faible" }
    { group:44, id:86, text: "moyen" }
    { group:44, id:87, text: "élevé" }
    { group:44, id:88, text: "Conditions de départ" }
    { group:44, id:89, text: "Modifier la date de début" }
    { group:44, id:90, text: "Entry 90 - used as a marker only" }
    { group:44, id:91, text: "Borne - 25%" }
    { group:44, id:92, text: "Borne - 50%" }
    { group:44, id:93, text: "Borne - 75%" }
    { group:44, id:94, text: "Variation de la demande" }
    { group:44, id:95, text: "Evénements" }
    { group:44, id:96, text: "Ajouter un événement" }
    { group:44, id:97, text: "Supprimer un événement" }
    { group:44, id:98, text: "en route" }
    { group:44, id:99, text: "diminue" }
    { group:44, id:100, text: "augmente" }
    { group:44, id:101, text: "demande pour ce bien" }
    { group:44, id:102, text: "sans utilisation" }
    { group:44, id:103, text: "diminue de" }
    { group:44, id:104, text: "augmente de" }
    { group:44, id:105, text: "événement incorrect" }
    { group:44, id:106, text: "CONSEIL : utilisez les touches virgule et point pour vous déplacer rapidement au sein de ces objets." }
    { group:44, id:107, text: "Partie libre (pas de victoire)" }
    { group:44, id:108, text: "Rang initial" }
    { group:44, id:109, text: "Terrain" }
    { group:44, id:110, text: "Ennemis" }
    { group:44, id:111, text: "Invasions" }
    { group:44, id:112, text: "Pas d'activité militaire" }
    { group:44, id:113, text: "Troubles mineurs" }
    { group:44, id:114, text: "Quelques combats signalés" }
    { group:44, id:115, text: "Activité militaire intense" }
    { group:44, id:116, text: "Cité assiégée" }
    { group:44, id:117, text: "Grade" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "La capitale nourrit-elle ses habitants ?" }
    { group:44, id:120, text: "Taille de la carte" }
    { group:44, id:121, text: "Province minuscule" }
    { group:44, id:122, text: "Petite province" }
    { group:44, id:123, text: "Province moyenne" }
    { group:44, id:124, text: "Grande province" }
    { group:44, id:125, text: "Très grande province" }
    { group:44, id:126, text: "Province immense" }
    { group:44, id:127, text: "Conditions de victoire" }
    { group:44, id:128, text: "aucun" }
    { group:44, id:129, text: "Culture" }
    { group:44, id:130, text: "Prospérité" }
    { group:44, id:131, text: "Monument" }
    { group:44, id:132, text: "Royaume" }
    { group:44, id:133, text: "Population" }
    { group:44, id:134, text: "Nombre max. d'années" }
    { group:44, id:135, text: "Années de survie" }
    { group:44, id:136, text: "Aller à la cité" }
    { group:44, id:137, text: "Entrée de rivière requise" }
    { group:44, id:138, text: "Sortie de rivière requise" }
    { group:44, id:139, text: "Evénement" }
    { group:44, id:140, text: "mois" }
    { group:44, id:141, text: "entre" }
    { group:44, id:142, text: "et" }
    { group:44, id:143, text: "cités" }
    { group:44, id:144, text: "du point" }
    { group:44, id:145, text: "à" }
    { group:44, id:146, text: "Nombre" }
    { group:44, id:147, text: "échelle" }
    { group:44, id:148, text: "/" }
    { group:44, id:149, text: "dans" }
    { group:44, id:150, text: "mois" }
    { group:44, id:151, text: "accepter l'événement" }
    { group:44, id:152, text: "refuser l'événement" }
    { group:44, id:153, text: "événement trop tardif" }
    { group:44, id:154, text: "annuler l'événement" }
    { group:44, id:155, text: "événement de défaite" }
    { group:44, id:156, text: "événement suivant" }
    { group:44, id:157, text: "événement unique" }
    { group:44, id:158, text: "événement récurrent" }
    { group:44, id:159, text: "déclenché" }
    { group:44, id:160, text: "déclenché par faveur" }
    { group:44, id:161, text: "Pharaon" }
    { group:44, id:162, text: "Cité" }
    { group:44, id:163, text: "Navires de guerre" }
    { group:44, id:164, text: "Paramètres des dieux" }
    { group:44, id:165, text: "Pas de dieu protecteur" }
    { group:44, id:166, text: "Ajouter route" }
    { group:44, id:167, text: "Editer route" }
    { group:44, id:168, text: "Supprimer route" }
    { group:44, id:169, text: "Route générale" }
    { group:44, id:170, text: "Route maritime" }
    { group:44, id:171, text: "Route terrestre" }
    { group:44, id:172, text: "Espace" }
    { group:44, id:173, text: "Longueur route :" }
    { group:44, id:174, text: "Nom" }
    { group:44, id:175, text: "Grade" }
    { group:44, id:176, text: "Ensemble de temples" }
    { group:44, id:177, text: "Taux d'intérêt de la dette" }
    { group:44, id:178, text: "Paramètres de la plaine inondable" }
    { group:44, id:179, text: "Début de l'inondation :" }
    { group:44, id:180, text: "Début juin" }
    { group:44, id:181, text: "Fin juin" }
    { group:44, id:182, text: "Début juillet" }
    { group:44, id:183, text: "Fin juillet" }
    { group:44, id:184, text: "Début août" }
    { group:44, id:185, text: "Fin août" }
    { group:44, id:186, text: "Début septembre" }
    { group:44, id:187, text: "Fin septembre" }
    { group:44, id:188, text: "Durée de l'inondation :" }
    { group:44, id:189, text: "Deux mois" }
    { group:44, id:190, text: "Trois mois" }
    { group:44, id:191, text: "Quatre mois" }
    { group:44, id:192, text: "Qualité de l'inondation :" }
    { group:44, id:193, text: "Nulle" }
    { group:44, id:194, text: "Faible" }
    { group:44, id:195, text: "Médiocre" }
    { group:44, id:196, text: "Bonne" }
    { group:44, id:197, text: "Excellente" }
    { group:44, id:198, text: "Parfaite" }
    { group:44, id:199, text: "Echec de l'inondation" }
    { group:44, id:200, text: "Inondation parfaite" }
    { group:44, id:201, text: "Sélectionner" }
    { group:44, id:202, text: "Pharaon actuel :" }
    { group:44, id:203, text: "Incarnation du joueur :" }
    { group:44, id:204, text: "Fixer les prix" }
    { group:44, id:205, text: "Achats" }
    { group:44, id:206, text: "Ventes" }
    { group:44, id:207, text: "Accepter" }
    { group:44, id:208, text: "Refuser" }
    { group:44, id:209, text: "Reporter" }
    { group:44, id:210, text: "Niveau d'habitation" }
    { group:44, id:211, text: "Redéfinir les prix" }
    { group:44, id:212, text: "Dieu" }
    { group:44, id:213, text: "1 charrette ou bloc de pierres = 100 unités" }
    { group:44, id:214, text: "Modifier cette carte" }
    { group:44, id:215, text: "Exécuter cette mission" }
    { group:44, id:216, text: "Difficulté" }
    { group:44, id:217, text: "Quitter" }
    { group:44, id:218, text: "Lancer la mission" }
    { group:44, id:219, text: "Annuler" }
    { group:44, id:220, text: "Afficher les résultats précédents" }
    { group:44, id:221, text: "Afficher résumé de mission" }
    { group:44, id:222, text: "Royaume" }
    { group:44, id:223, text: "Restaurer" }
    { group:44, id:224, text: "Point d'entrée fixé" }
    { group:44, id:225, text: "Point de sortie fixé" }
    { group:44, id:226, text: "1 point de rivière fixé" }
    { group:44, id:227, text: "Joueur avec les" }
    { group:45, id:0, text: "Options de vitesse" }
    { group:45, id:1, text: "Annuler" }
    { group:45, id:2, text: "Jeu" }
    { group:45, id:3, text: "Défilement" }
    { group:45, id:4, text: "OK" }
    { group:45, id:5, text: "Vitesse des nuages" }
    { group:45, id:6, text: "Déplacer la caméra avec le bouton du milieu" }
    { group:45, id:7, text: "Vitesse de déplacement (bouton du milieu)" }
    { group:46, id:0, text: "Options sonores" }
    { group:46, id:1, text: "Pas de musique" }
    { group:46, id:2, text: "Musique activée" }
    { group:46, id:3, text: "Pas de voix" }
    { group:46, id:4, text: "Avec les voix" }
    { group:46, id:5, text: "Pas de bruitages" }
    { group:46, id:6, text: "Avec les bruitages" }
    { group:46, id:7, text: "Pas d'ambiance cité" }
    { group:46, id:8, text: "Avec l'ambiance de la cité" }
    { group:46, id:9, text: "Annuler" }
    { group:46, id:10, text: "Réglages audio actuels" }
    { group:46, id:11, text: "Volume" }
    { group:46, id:12, text: "OK" }
    { group:47, id:0, text: "Une lointaine cité." }
    { group:47, id:1, text: "Notre cité !" }
    { group:47, id:2, text: "Cette route de commerce n'a pas encore été établie" }
    { group:47, id:3, text: "Coût d'ouverture" }
    { group:47, id:4, text: "Achats" }
    { group:47, id:5, text: "Ventes" }
    { group:47, id:6, text: "pour ouvrir une route de commerce." }
    { group:47, id:7, text: "pour une route maritime de commerce" }
    { group:47, id:8, text: "Auprès du chef du commerce" }
    { group:47, id:9, text: "Cliquez sur une cité pour obtenir des informations à son sujet." }
    { group:47, id:10, text: "Acheté" }
    { group:47, id:11, text: "Vendu" }
    { group:47, id:12, text: "/" }
    { group:47, id:13, text: "Une cité égyptienne" }
    { group:47, id:14, text: "Une cité capturée" }
    { group:47, id:15, text: "Une armée ennemie, menaçant une cité du royaume" }
    { group:47, id:16, text: "Votre armée, en marche pour secourir une cité du royaume" }
    { group:47, id:17, text: "Votre armée, retournant à votre cité" }
    { group:47, id:18, text: "Le site d'une récente escarmouche avec des envahisseurs barbares" }
    { group:47, id:19, text: "La cité du pharaon" }
    { group:48, id:0, text: "Pinceau fin" }
    { group:48, id:1, text: "Petit pinceau" }
    { group:48, id:2, text: "Pinceau moyen" }
    { group:48, id:3, text: "Gros pinceau" }
    { group:48, id:4, text: "Très gros pinceau" }
    { group:48, id:5, text: "Point d'entrée" }
    { group:48, id:6, text: "Point de sortie" }
    { group:48, id:7, text: "Surélever le terrain" }
    { group:48, id:8, text: "Rabaisser le terrain" }
    { group:48, id:9, text: "Rampe d'accès" }
    { group:48, id:10, text: "Pt d'invasion 1 (terrestre)" }
    { group:48, id:11, text: "Pt d'invasion 2 (terrestre)" }
    { group:48, id:12, text: "Pt d'invasion 3 (terrestre)" }
    { group:48, id:13, text: "Pt d'invasion 4 (terrestre)" }
    { group:48, id:14, text: "Pt d'invasion 5 (terrestre)" }
    { group:48, id:15, text: "Pt d'invasion 6 (terrestre)" }
    { group:48, id:16, text: "Pt d'invasion 7 (terrestre)" }
    { group:48, id:17, text: "Pt d'invasion 8 (terrestre)" }
    { group:48, id:18, text: "Entrée de rivière" }
    { group:48, id:19, text: "Sortie de rivière" }
    { group:48, id:20, text: "Hutte indigène" }
    { group:48, id:21, text: "Place indigène" }
    { group:48, id:22, text: "Champ indigène" }
    { group:48, id:23, text: "Point de pêche 1" }
    { group:48, id:24, text: "Point de pêche 2" }
    { group:48, id:25, text: "Point de pêche 3" }
    { group:48, id:26, text: "Point de pêche 4" }
    { group:48, id:27, text: "Point de pêche 5" }
    { group:48, id:28, text: "Point de pêche 6" }
    { group:48, id:29, text: "Point de pêche 7" }
    { group:48, id:30, text: "Point de pêche 8" }
    { group:48, id:31, text: "Point de prédateurs 1" }
    { group:48, id:32, text: "Point de prédateurs 2" }
    { group:48, id:33, text: "Point de prédateurs 3" }
    { group:48, id:34, text: "Point de prédateurs 4" }
    { group:48, id:35, text: "Eau" }
    { group:48, id:36, text: "Plaine inondable" }
    { group:48, id:37, text: "Rigole d'irrigation" }
    { group:48, id:38, text: "Marécage" }
    { group:48, id:39, text: "Point de gibier 1" }
    { group:48, id:40, text: "Point de gibier 2" }
    { group:48, id:41, text: "Point de gibier 3" }
    { group:48, id:42, text: "Point de gibier 4" }
    { group:48, id:43, text: "Roche ordinaire" }
    { group:48, id:44, text: "Roche contenant du minerai" }
    { group:48, id:45, text: "Roche ordinaire" }
    { group:48, id:46, text: "Roche spéciale" }
    { group:48, id:47, text: "Dunes de sable" }
    { group:48, id:48, text: "Pt d'invasion 9 (maritime)" }
    { group:48, id:49, text: "Pt d'invasion 10 (maritime)" }
    { group:48, id:50, text: "Pt d'invasion 11 (maritime)" }
    { group:48, id:51, text: "Pt d'invasion 12 (maritime)" }
    { group:48, id:52, text: "Pt d'invasion 13 (maritime)" }
    { group:48, id:53, text: "Pt d'invasion 14 (maritime)" }
    { group:48, id:54, text: "Pt d'invasion 15 (maritime)" }
    { group:48, id:55, text: "Pt d'invasion 16 (maritime)" }
    { group:48, id:56, text: "Pt de débarquement 1" }
    { group:48, id:57, text: "Pt de débarquement 2" }
    { group:48, id:58, text: "Pt de débarquement 3" }
    { group:48, id:59, text: "Prédateur Type 1" }
    { group:48, id:60, text: "Prédateur Type 2" }
    { group:49, id:0, text: "Herbe" }
    { group:49, id:1, text: "Arbres" }
    { group:49, id:2, text: "Eau" }
    { group:49, id:3, text: "Tremblement de terre" }
    { group:49, id:4, text: "Broussailles" }
    { group:49, id:5, text: "Rochers" }
    { group:49, id:6, text: "Prairie" }
    { group:49, id:7, text: "Plateau" }
    { group:49, id:8, text: "Taille du pinceau" }
    { group:49, id:9, text: "Rampe d'accès" }
    { group:49, id:10, text: "Route" }
    { group:49, id:11, text: "Surélever le terrain" }
    { group:49, id:12, text: "Rabaisser le terrain" }
    { group:49, id:13, text: "Point d'invasion" }
    { group:49, id:14, text: "Point de migration" }
    { group:49, id:15, text: "Point d'entrée" }
    { group:49, id:16, text: "Point de sortie" }
    { group:49, id:17, text: "Point de rivière" }
    { group:49, id:18, text: "Entrée rivière" }
    { group:49, id:19, text: "Sortie rivière" }
    { group:49, id:20, text: "Indigènes" }
    { group:49, id:21, text: "Hutte indigène" }
    { group:49, id:22, text: "Place indigène" }
    { group:49, id:23, text: "Champ indigène" }
    { group:49, id:24, text: "Zones de pêche" }
    { group:49, id:25, text: "Point de prédateurs" }
    { group:49, id:26, text: "Plaine inondable" }
    { group:49, id:27, text: "Irrigation" }
    { group:49, id:28, text: "Gibier" }
    { group:49, id:29, text: "Marécage" }
    { group:49, id:30, text: "Dunes de sable" }
    { group:49, id:31, text: "Point de débarquement" }
    { group:49, id:32, text: "Prédateur Type 3" }
    { group:49, id:33, text: "Falaise" }
    { group:50, id:0, text: "Chef de la main-d'œuvre" }
    { group:50, id:1, text: "Production de nourriture et distribution" }
    { group:50, id:2, text: "Industrie et commerce" }
    { group:50, id:3, text: "Loisirs" }
    { group:50, id:4, text: "Religion" }
    { group:50, id:5, text: "Education" }
    { group:50, id:6, text: "Structures sanitaires et hygiène" }
    { group:50, id:7, text: "Infrastructure" }
    { group:50, id:8, text: "Gouvernement" }
    { group:50, id:9, text: "Militaire" }
    { group:50, id:10, text: "Besoin" }
    { group:50, id:11, text: "Possession" }
    { group:50, id:12, text: "Force de travail utilisée" }
    { group:50, id:13, text: "Force de travail inutilisée (" }
    { group:50, id:14, text: "Salaire/10" }
    { group:50, id:15, text: "Debens" }
    { group:50, id:16, text: "inférieur au niveau du royaume de" }
    { group:50, id:17, text: "supérieur au niveau du royaume de" }
    { group:50, id:18, text: "(Le royaume paye" }
    { group:50, id:19, text: "Salaire prévisionnel à verser cette année" }
    { group:50, id:20, text: "Verrouillé" }
    { group:50, id:21, text: "Priorité" }
    { group:50, id:22, text: "Secteur" }
    { group:50, id:23, text: "Besoin" }
    { group:50, id:24, text: "Possession" }
    { group:50, id:25, text: "Niveau de priorité." }
    { group:50, id:26, text: "Pas de priorité." }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Etat des troupes" }
    { group:51, id:1, text: "Atteindre" }
    { group:51, id:2, text: "compagnie" }
    { group:51, id:3, text: "Retour" }
    { group:51, id:4, text: "au fort" }
    { group:51, id:5, text: "Royaume" }
    { group:51, id:6, text: "service" }
    { group:51, id:7, text: "en" }
    { group:51, id:8, text: "Il n'y a aucune menace dans la cité." }
    { group:51, id:9, text: "On signale des troupes ennemies se dirigeant vers la cité." }
    { group:51, id:10, text: "Les troupes ennemies sont en vue !" }
    { group:51, id:11, text: "Un bataillon des troupes du pharaon est aux portes de la cité." }
    { group:51, id:12, text: "Il n'y a aucune demande d'aide dans tout le royaume." }
    { group:51, id:13, text: "Nos troupes sont requises dans une autre région du royaume." }
    { group:51, id:14, text: "Le bataillon est en route pour sauver une cité du royaume." }
    { group:51, id:15, text: "Notre bataillon retourne à notre cité." }
    { group:51, id:16, text: "Vous n'avez pas de compagnie à commander. Vous devez d'abord construire un fort pour y placer une nouvelle compagnie." }
    { group:51, id:17, text: "Expérience" }
    { group:51, id:18, text: "de la compagnie" }
    { group:51, id:19, text: "Etat de la flotte" }
    { group:51, id:20, text: "navire de guerre" }
    { group:51, id:21, text: "vers le quai" }
    { group:51, id:22, text: "Coque" }
    { group:51, id:23, text: "Force" }
    { group:51, id:24, text: "Etat de l'équipage" }
    { group:51, id:25, text: "Vous n'avez pas de navires de guerre à commander. Vous devez commencer par construire un quai pour accueillir un nouveau navire de guerre." }
    { group:51, id:26, text: "Une partie de la flotte est demandée ailleurs" }
    { group:51, id:27, text: "Notre compagnie part sauver une cité égyptienne" }
    { group:51, id:28, text: "Notre compagnie retourne à notre cité" }
    { group:51, id:29, text: "à l'étranger" }
    { group:51, id:30, text: "Envoyer" }
    { group:51, id:31, text: "maintenant" }
    { group:51, id:32, text: "et" }
    { group:52, id:0, text: "Niveau du royaume" }
    { group:52, id:1, text: "Economies :" }
    { group:52, id:2, text: "Faire un don à la cité" }
    { group:52, id:3, text: "Deben par mois" }
    { group:52, id:4, text: "Doyen du village" }
    { group:52, id:5, text: "Noble du village" }
    { group:52, id:6, text: "Erudit du royaume" }
    { group:52, id:7, text: "Scribe du royaume" }
    { group:52, id:8, text: "Juge du royaume" }
    { group:52, id:9, text: "Maire du royaume" }
    { group:52, id:10, text: "Gouverneur du royaume" }
    { group:52, id:11, text: "Nomarque" }
    { group:52, id:12, text: "Chancelier" }
    { group:52, id:13, text: "Vizir" }
    { group:52, id:14, text: "Pharaon" }
    { group:52, id:15, text: "Fixer le niveau de salaire" }
    { group:52, id:16, text: "Donner de l'argent à la cité" }
    { group:52, id:17, text: "La donation est de" }
    { group:52, id:18, text: "Donner de l'argent" }
    { group:52, id:19, text: "Tout" }
    { group:52, id:20, text: "Requêtes actuelles" }
    { group:52, id:22, text: "La population veut se débarrasser de vous." }
    { group:52, id:23, text: "Les jongleurs se servent de vous dans leurs comédies et votre nom est prononcé en tant que malédiction." }
    { group:52, id:24, text: "On dit que votre seule présence provoque la malaria." }
    { group:52, id:25, text: "Les pharmaciens disent que votre nom est plus amer que n'importe quelle herbe." }
    { group:52, id:26, text: "Les mères se servent de votre nom pour faire peur à leurs enfants." }
    { group:52, id:27, text: "Votre nom n'est jamais prononcé en société." }
    { group:52, id:28, text: "Votre réputation n'est plus à faire et votre propre famille vous fuit." }
    { group:52, id:29, text: "Votre nom est connu, mais il est tourné en dérision dans les Deux Pays." }
    { group:52, id:30, text: "Les personnalités importantes connaissent votre nom et votre histoire, mais vous injurient." }
    { group:52, id:31, text: "Peu de gens au sein du royaume connaissent votre histoire et ceux qui la connaissent n'en font pas grand cas." }
    { group:52, id:32, text: "Les quelques personnes qui connaissent votre nom ne vous estiment guère." }
    { group:52, id:33, text: "Vos petites réalisations ne sont pas célèbres, mais les personnes qui vous connaissent vous apprécient généralement." }
    { group:52, id:34, text: "Les personnalités importantes connaissent votre histoire et vous apprécient généralement pour ce que vous avez fait." }
    { group:52, id:35, text: "Votre nom est universellement connu et loué dans les Deux Pays." }
    { group:52, id:36, text: "Votre réputation est bonne et des membres de votre famille que vous n'avez pas revus depuis longtemps se tournent vers vous." }
    { group:52, id:37, text: "Votre nom réjouit le cœur de ceux qui l'entendent." }
    { group:52, id:38, text: "Les mères du royaume donnent votre nom à leurs enfants." }
    { group:52, id:39, text: "De nombreuses cités égyptiennes envisagent d'organiser une fête en votre honneur." }
    { group:52, id:40, text: "La danse la plus populaire en Egypte illustre l'histoire de votre vie." }
    { group:52, id:41, text: "Les musiciens composent des chansons en votre honneur et votre nom est inscrit dans tous les lieux publics." }
    { group:52, id:42, text: "Tous les Egyptiens souhaitent vous servir éternellement dans le champ de roseaux." }
    { group:52, id:43, text: "dans les entrepôts" }
    { group:52, id:44, text: "dans les caisses de la cité" }
    { group:52, id:45, text: "personnes" }
    { group:52, id:46, text: "armes" }
    { group:52, id:47, text: "Expédier requête : cliquez ici" }
    { group:52, id:49, text: "Envoyer un cadeau" }
    { group:52, id:51, text: "Une tablette babylonienne" }
    { group:52, id:52, text: "Tapis persans" }
    { group:52, id:53, text: "Sculptures anciennes" }
    { group:52, id:54, text: "Ivoire africain" }
    { group:52, id:55, text: "Une troupe d'acteurs esclaves" }
    { group:52, id:56, text: "Etalons arabes" }
    { group:52, id:57, text: "Un esclave cultivé" }
    { group:52, id:58, text: "Gardes du corps libyens" }
    { group:52, id:59, text: "Guépards et girafes" }
    { group:52, id:60, text: "Un coffre de saphirs" }
    { group:52, id:61, text: "Un char en or" }
    { group:52, id:62, text: "Un navire en cèdre du Liban" }
    { group:52, id:71, text: "Attention : si vous vous accordez un salaire sans commune mesure avec votre rang actuel, cela ne sera pas apprécié." }
    { group:52, id:72, text: "Envoyer des troupes pour protéger" }
    { group:52, id:73, text: "Une armée modeste attaquera dans" }
    { group:52, id:74, text: "Une armée attaquera dans" }
    { group:52, id:75, text: "Une armée conséquente attaquera dans" }
    { group:52, id:76, text: "Vous êtes actuellement libre de fixer votre salaire" }
    { group:52, id:77, text: "Le palais vous interdit de toucher un salaire pour l'instant, car vous continuez à gouverner de votre plein gré." }
    { group:52, id:78, text: "Vous devez construire une demeure luxueuse pour toucher un salaire." }
    { group:52, id:79, text: "debens dérobés cette année." }
    { group:52, id:80, text: "Envoyer des troupes opérationnelles pour protéger" }
    { group:52, id:81, text: "Chef politique de" }
    { group:53, id:0, text: "Chef des niveaux" }
    { group:53, id:1, text: "Culture" }
    { group:53, id:2, text: "Prospérité" }
    { group:53, id:3, text: "Monument" }
    { group:53, id:4, text: "Royaume" }
    { group:53, id:5, text: "Requis" }
    { group:53, id:6, text: "Population" }
    { group:53, id:7, text: "Pas d'objectif de population" }
    { group:53, id:8, text: "Cliquez sur un nombre pour plus d'informations." }
    { group:53, id:9, text: "Il n'y a pas assez de jongleurs dans votre cité. Créez-en plus pour augmenter cette valeur." }
    { group:53, id:10, text: "Il n'y a pas de musiciens dans votre cité. Créez-en plus pour augmenter cette valeur." }
    { group:53, id:11, text: "Il n'y a pas assez de danseurs dans votre cité. Créez-en plus pour augmenter cette valeur." }
    { group:53, id:12, text: "Il n'y a pas assez de tavernes de jeux dans votre cité. Créez-en plus pour augmenter cette valeur." }
    { group:53, id:13, text: "La cité n'a pas assez de Zoos. Vous devez construire des Zoos pour améliorer cette situation." }
    { group:53, id:14, text: "Il n'y a pas assez de lieux de culte dans votre cité. Construisez-en plus pour augmenter cette valeur." }
    { group:53, id:15, text: "Il n'y a pas assez d'écoles de scribes dans votre cité. Construisez-en plus pour augmenter cette valeur." }
    { group:53, id:16, text: "Il n'y a pas assez de bibliothèques dans votre cité. Construisez-en plus pour augmenter cette valeur." }
    { group:53, id:17, text: "Le nombre de maisons ayant accès à un dentiste est insuffisant. Améliorez cet accès pour augmenter cette valeur." }
    { group:53, id:18, text: "Le nombre de maisons ayant accès à une pharmacie est insuffisant. Améliorez cet accès pour augmenter cette valeur" }
    { group:53, id:19, text: "Le nombre de maisons ayant accès à une salle des embaumeurs est insuffisant. Améliorez cet accès pour augmenter cette valeur" }
    { group:53, id:20, text: "en augmentation." }
    { group:53, id:21, text: "en baisse." }
    { group:53, id:22, text: "stable." }
    { group:53, id:23, text: "La qualité générale des logements de votre cité empêche cette valeur d'augmenter. Améliorez les logements pour remédier à cette situation." }
    { group:53, id:24, text: "Les fonds de votre cité sont en baisse par rapport à l'année dernière. C'est mauvais signe pour votre trésorerie." }
    { group:53, id:25, text: "Le taux de chômage élevé dans votre cité déteint sur votre prospérité." }
    { group:53, id:26, text: "Un paiement inférieur au salaire moyen du royaume nuit à l'image de prospérité de votre cité." }
    { group:53, id:27, text: "Une grande concentration de miséreux dans votre cité lui donne l'apparence d'une ville pauvre." }
    { group:53, id:28, text: "Votre incapacité à payer le tribut annuel au pharaon est un signe d'échec." }
    { group:53, id:29, text: "Le manque de variétés de nourriture nuit à votre prospérité." }
    { group:53, id:30, text: "Le manque de main-d'oeuvre nuit à la prospérité." }
    { group:53, id:31, text: "La cité est plus prospère lorsque le revenu des exportations est supérieur au coût des importations." }
    { group:53, id:32, text: "Le niveau du royaume baisse. Payez votre tribut annuel, versez-vous un salaire raisonnable et accédez aux requêtes que vous recevez." }
    { group:53, id:33, text: "Le salaire exagérément élevé que vous vous versez irrite le pharaon et fait baisser votre niveau." }
    { group:53, id:34, text: "Votre incapacité permanente à verser un tribut fait baisser le niveau du royaume." }
    { group:53, id:35, text: "Le requête que vous avez récemment annulée nuit au prestige de votre cité dans le royaume." }
    { group:53, id:36, text: "Le salaire que vous vous versez, largement supérieur à votre rang, nuit à votre réputation dans le royaume." }
    { group:53, id:37, text: "C'est la deuxième année que vous ne payez pas le tribut, ce qui fait baisser le niveau du royaume." }
    { group:53, id:38, text: "Vos récentes décisions ont légèrement diminué votre niveau du royaume." }
    { group:53, id:39, text: "Votre salaire est trop élevé pour votre rang actuel. Le niveau du royaume augmentera si vous le réduisez un peu." }
    { group:53, id:40, text: "Vous n'avez pas pu payer votre tribut cette année, ce qui a nui à votre niveau. Gardez de l'argent dans les caisses en fin d'année pour pouvoir effectuer votre versement annuel." }
    { group:53, id:41, text: "Votre salaire est trop élevé pour votre rang actuel. Vous seriez bien inspiré de le réduire un peu." }
    { group:53, id:42, text: "Votre incapacité à atteindre vos objectifs dans les délais prévus fait baisser votre niveau." }
    { group:53, id:43, text: "L'impudence dont vous faites preuve en vous accordant un salaire plus élevé que celui auquel vous avez droit vous attire la réprobation." }
    { group:53, id:44, text: "Le niveau du royaume a augmenté depuis l'année dernière." }
    { group:53, id:45, text: "Le niveau du royaume reste inchangé depuis l'année dernière." }
    { group:53, id:46, text: "Le niveau de paix augmentera chaque année si la cité n'est troublée par aucune émeute ou invasion." }
    { group:53, id:47, text: "Cette province était relativement paisible, mais vos citoyens ne se sentent plus en sécurité. Quelques années de paix supplémentaires devraient apaiser leurs craintes." }
    { group:53, id:48, text: "Les habitants de cette province se sentent globalement en sécurité. Ce sentiment s'accentuera avec le temps." }
    { group:53, id:49, text: "La loi règne dans votre cité. Avec le temps, vos citoyens se sentiront vraiment en sécurité." }
    { group:53, id:50, text: "Tout semble bien calme dans cette cité, ce qui fait le bonheur de tous vos citoyens." }
    { group:53, id:51, text: "Le calme et la sécurité de votre province sont si légendaires que les autres gouverneurs prévoient de venir passer leur retraite ici !" }
    { group:53, id:52, text: "Les récentes émeutes dans votre cité ont eu un effet négatif sur votre niveau de paix." }
    { group:53, id:53, text: "La présence de troupes ennemies non loin de la cité n'améliore pas votre niveau de paix !" }
    { group:53, id:54, text: "Les forces pharaoniques qui approchent effraient la population, ce qui risque de nuire à votre niveau de paix." }
    { group:53, id:55, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:56, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:57, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:58, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:59, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:60, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:61, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:62, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:63, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:64, text: "Le chef des monuments et le contremaître (cliquez avec le bouton droit de la souris sur un monument) peuvent vous conseiller." }
    { group:53, id:65, text: "Cette cité possède un niveau de culture inégalé en Egypte !" }
    { group:53, id:66, text: "L'incroyable prospérité de cette cité est célèbre dans toute l'Egypte !" }
    { group:53, id:67, text: "Cette cité possède les monuments les plus somptueux de toute l'Egypte !" }
    { group:53, id:68, text: "Votre royaume est le mieux noté de toute l'Egypte !" }
    { group:53, id:69, text: "Il n'y a encore aucun monument dans cette cité." }
    { group:54, id:1, text: "Cliquez sur un objet, stockez ou modifiez le bilan de cette industrie" }
    { group:54, id:2, text: "Afficher les prix" }
    { group:54, id:3, text: "Stockage" }
    { group:54, id:4, text: "Pas d'échange" }
    { group:54, id:5, text: "Importation jusqu'à" }
    { group:54, id:6, text: "Exportation au delà de" }
    { group:54, id:7, text: "Pas d'industries dans la cité" }
    { group:54, id:8, text: "industrie fonctionnelle dans la cité" }
    { group:54, id:9, text: "industries fonctionnelles dans la cité" }
    { group:54, id:10, text: "industrie inactive dans la cité" }
    { group:54, id:11, text: "industries inactives dans la cité" }
    { group:54, id:12, text: "en service" }
    { group:54, id:13, text: "industries désœuvrées dans la cité" }
    { group:54, id:14, text: "industrie désœuvrée dans la cité" }
    { group:54, id:15, text: "en stock dans les entrepôts de la cité" }
    { group:54, id:16, text: "Avec industrie" }
    { group:54, id:17, text: "Pas d'industrie" }
    { group:54, id:18, text: "Pas d'échange" }
    { group:54, id:19, text: "Importer jusqu'à" }
    { group:54, id:20, text: "Exporter au delà de" }
    { group:54, id:21, text: "Prix pratiqués en Egypte" }
    { group:54, id:22, text: "Prix d'achat" }
    { group:54, id:23, text: "Prix de vente" }
    { group:54, id:24, text: "Il n'existe pas de route de commerce pour le transport de ces biens." }
    { group:54, id:25, text: "Ces biens ne sont disponibles qu'à l'importation." }
    { group:54, id:26, text: "Cette ressource est stockée" }
    { group:54, id:27, text: "Cliquez ici pour cesser de stocker cette ressource" }
    { group:54, id:28, text: "Utilisation et commerce de cette ressource" }
    { group:54, id:29, text: "Cliquez ici pour la stocker" }
    { group:54, id:30, text: "Aller à la mappemonde" }
    { group:54, id:31, text: "Disponible pour l'importation" }
    { group:54, id:32, text: "Disponible pour l'exportation" }
    { group:54, id:33, text: "Disponible pour import ou export" }
    { group:54, id:34, text: "Ouvrez une route pour importer" }
    { group:54, id:35, text: "Ouvrez une route pour exporter" }
    { group:54, id:36, text: "Créer route pour import/export" }
    { group:54, id:37, text: "Importation des biens requis" }
    { group:54, id:38, text: "Exportation des surplus uniquement" }
    { group:54, id:39, text: "Cliquez pour en importer" }
    { group:54, id:40, text: "Cliquez pour en exporter" }
    { group:54, id:41, text: "Aucun vendeur pour ce bien" }
    { group:54, id:42, text: "Aucun acheteur pour ce bien" }
    { group:54, id:43, text: "Importer les marchandises requises" }
    { group:54, id:44, text: "Exporter les surplus" }
    { group:54, id:45, text: "multiple" }
    { group:54, id:46, text: "Afficher le statut d'échange" }
    { group:54, id:47, text: "par arme" }
    { group:54, id:48, text: "par char" }
    { group:54, id:49, text: "par bloc" }
    { group:54, id:50, text: "pour 100 pièces" }
    { group:55, id:0, text: "Population - Historique" }
    { group:55, id:1, text: "Population - Recensement" }
    { group:55, id:2, text: "Population - Société" }
    { group:55, id:3, text: "Historique" }
    { group:55, id:4, text: "Recensement" }
    { group:55, id:5, text: "Société" }
    { group:55, id:6, text: "Population de la cité à travers le temps." }
    { group:55, id:7, text: "Répartition de la population par âge (en années)." }
    { group:55, id:8, text: "Répartition de la population par revenu." }
    { group:55, id:9, text: "Habitants de huttes" }
    { group:55, id:10, text: "Habitants de domaines" }
    { group:55, id:11, text: "La capitale fournit toute la nourriture nécessaire à cette cité" }
    { group:55, id:12, text: "de la nourriture pour" }
    { group:55, id:13, text: "de la nourriture pour le mois à venir" }
    { group:55, id:14, text: "aucune nourriture pour le mois à venir" }
    { group:55, id:15, text: "très peu de nourriture pour le mois à venir" }
    { group:55, id:16, text: "Le logement actuel peut accueillir" }
    { group:55, id:17, text: "personnes de plus" }
    { group:55, id:18, text: "nouveaux venus ce mois-ci." }
    { group:55, id:19, text: "nouveau venu ce mois-ci." }
    { group:55, id:20, text: "Le manque de logements freine l'immigration." }
    { group:55, id:21, text: "Les salaires bas freinent l'immigration dans notre cité." }
    { group:55, id:22, text: "Le chômage réduit le nombre d'immigrants." }
    { group:55, id:23, text: "La pénurie de nourriture en réserve réduit l'immigration." }
    { group:55, id:24, text: "Les impôts élevés découragent certains de s'installer dans notre cité." }
    { group:55, id:25, text: "Des immigrants s'installent ou souhaitent s'installer dans notre cité." }
    { group:55, id:26, text: "Dans l'ensemble, la population quitte notre cité." }
    { group:55, id:27, text: "Le manque d'emplois fait partir votre population." }
    { group:55, id:28, text: "Les gens quittent la cité à la recherche de meilleurs salaires." }
    { group:55, id:29, text: "Les gens, révoltés par le montant des impôts, quittent la cité." }
    { group:55, id:30, text: "Dans l'ensemble, la population de votre cité est stable." }
    { group:55, id:31, text: "Les flux d'émigration et d'immigration de la cité sont équilibrés." }
    { group:55, id:32, text: "La piètre qualité des logements limite l'immigration." }
    { group:55, id:33, text: "Personne ne veut vivre dans notre cité." }
    { group:55, id:34, text: "Nourriture produite ou importée suffisante pour" }
    { group:55, id:35, text: "personnes." }
    { group:55, id:36, text: "A l'heure actuelle, nous consommons bien plus que nous ne produisons." }
    { group:55, id:37, text: "La consommation dépassant la production, la population va baisser." }
    { group:55, id:38, text: "La consommation dépasse la production et la population va augmenter." }
    { group:55, id:39, text: "A l'heure actuelle, nous consommons plus que nous ne produisons." }
    { group:55, id:40, text: "La consommation dépasse la production et la population va baisser." }
    { group:55, id:41, text: "La consommation dépasse la production, mais la population va augmenter." }
    { group:55, id:42, text: "Actuellement, nous consommons un peu plus que nous ne produisons." }
    { group:55, id:43, text: "La consommation dépassant la production, notre population va baisser." }
    { group:55, id:44, text: "La consommation dépasse la production, mais notre cité va s'agrandir." }
    { group:55, id:45, text: "Actuellement, nous produisons juste assez pour nourrir tout le monde." }
    { group:55, id:46, text: "La production est suffisante, mais notre population devrait diminuer." }
    { group:55, id:47, text: "La production couvre les besoins et notre cité devrait s'agrandir." }
    { group:55, id:48, text: "A l'heure actuelle, nous produisons un peu plus que nous ne consommons." }
    { group:55, id:49, text: "Nous produisons des surplus, mais notre population devrait diminuer." }
    { group:55, id:50, text: "Nous produisons des surplus mais notre population devrait augmenter." }
    { group:55, id:51, text: "Actuellement, nous produisons beaucoup plus que nous ne consommons." }
    { group:55, id:52, text: "Nous produisons des surplus, mais notre population devrait diminuer." }
    { group:55, id:53, text: "Nous produisons des surplus mais notre population devrait augmenter." }
    { group:56, id:0, text: "Chef de l'hygiène" }
    { group:56, id:1, text: "Free" }
    { group:56, id:2, text: "Aucune" }
    { group:56, id:3, text: "En service" }
    { group:56, id:4, text: "Prise en charge de" }
    { group:56, id:5, text: "Couverture de la cité" }
    { group:56, id:6, text: "patients" }
    { group:56, id:7, text: "Certains secteurs de la cité doivent maintenant avoir accès à des médecins." }
    { group:56, id:8, text: "Certains secteurs de la cité souhaitent avoir plus de médecins." }
    { group:56, id:9, text: "Certaines zones aisées de la cité souhaitent avoir des dentistes. La présence d'un dentiste augmentera l'attrait du quartier." }
    { group:56, id:10, text: "De nombreux quartiers de la cité souhaitent avoir des dentistes. Au fur et à mesure que votre cité s'enrichit, de plus en plus d'habitants peuvent se payer des dents en ivoire." }
    { group:56, id:11, text: "Certains secteurs de la cité exigent d'avoir accès à une pharmacie." }
    { group:56, id:12, text: "De plus en plus de gens veulent des installations médicales convenables (pharmacies)." }
    { group:56, id:13, text: "Le nombre insuffisant de salles d'embaumeurs dans la cité retarde le développement de certains quartiers." }
    { group:56, id:14, text: "Les citoyens exigent plus de salles d'embaumeurs pour mieux préparer leurs morts en voyage dans l'au-delà." }
    { group:56, id:15, text: "Il n'y a pour l'instant aucune demande de services d'hygiène ou de santé. Au fur et à mesure que la cité va se développer, la population exigera d'avoir accès à des soins de santé, puis plus tard à des dentistes et à d'autres installations médicales !" }
    { group:56, id:16, text: "Votre petite colonie n'a pas encore eu de problèmes d'hygiène." }
    { group:56, id:17, text: "L'hygiène de votre cité est épouvantable, germes et virus y prolifèrent en toute quiétude." }
    { group:56, id:18, text: "L'hygiène de votre cité est pitoyable ! Les épidémies sont presque inévitables." }
    { group:56, id:19, text: "L'hygiène de votre cité est mauvaise. La situation pourrait s'améliorer si les responsables de l'hygiène étaient plus nombreux." }
    { group:56, id:20, text: "L'hygiène de votre cité est médiocre. Il suffirait pour y remédier de disposer de plus de nourriture et d'installations sanitaires." }
    { group:56, id:21, text: "L'hygiène de votre cité est inférieure à la moyenne. Nourrissez la population et donnez-lui accès à des services de santé." }
    { group:56, id:22, text: "L'hygiène de votre cité est moyenne. Les conditions s'améliorent et les habitants ont de quoi manger." }
    { group:56, id:23, text: "L'hygiène est bonne. Les citoyens ne souffrent que de troubles mineurs." }
    { group:56, id:24, text: "L'hygiène de votre cité est très bonne. Les praticiens locaux se débrouillent bien." }
    { group:56, id:25, text: "L'hygiène de votre cité est excellente. Il n'y a aucune attente dans les installations sanitaires locales." }
    { group:56, id:26, text: "L'hygiène de votre cité est presque parfaite. Les installations sanitaires sont presque vides." }
    { group:56, id:27, text: "L'hygiène de votre cité est parfaite. Les travailleurs médicaux passent le plus clair de leur temps à jouer au senet." }
    { group:56, id:28, text: "L'hygiène dans votre cité est épouvantable." }
    { group:56, id:29, text: "L'hygiène dans votre cité est pitoyable." }
    { group:56, id:30, text: "L'hygiène dans votre cité est déplorable." }
    { group:56, id:31, text: "L'hygiène dans votre cité est très insuffisante." }
    { group:56, id:32, text: "L'hygiène dans votre cité est insuffisante." }
    { group:56, id:33, text: "L'hygiène dans votre cité est moyenne." }
    { group:56, id:34, text: "L'hygiène dans votre cité est bonne." }
    { group:56, id:35, text: "L'hygiène dans votre cité est très bonne." }
    { group:56, id:36, text: "L'hygiène dans votre cité est excellente." }
    { group:56, id:37, text: "L'hygiène dans votre cité est presque parfaite." }
    { group:56, id:38, text: "L'hygiène dans votre cité est parfaite." }
    { group:56, id:39, text: "Médecins" }
    { group:56, id:40, text: "Dentistes" }
    { group:56, id:41, text: "Pharmacies" }
    { group:56, id:42, text: "Salles d'embaumeurs" }
    { group:56, id:43, text: "Eparse" }
    { group:56, id:44, text: "Très faible" }
    { group:56, id:45, text: "Faible" }
    { group:56, id:46, text: "Un peu faible" }
    { group:56, id:47, text: "Moyenne" }
    { group:56, id:48, text: "Moyenne" }
    { group:56, id:49, text: "Assez bonne" }
    { group:56, id:50, text: "Bonne" }
    { group:56, id:51, text: "Très bonne" }
    { group:56, id:52, text: "Excellente" }
    { group:56, id:53, text: "Parfaite" }
    { group:56, id:54, text: "0" }
    { group:56, id:55, text: "Quelques" }
    { group:56, id:56, text: "Des" }
    { group:56, id:57, text: "Plusieurs" }
    { group:56, id:58, text: "Beaucoup de" }
    { group:56, id:59, text: "Pharmacies s'efforcent actuellement de protéger la cité de la malaria." }
    { group:56, id:60, text: "cas ont été signalés ce mois-ci." }
    { group:56, id:61, text: "variétés de nourriture dans votre cité." }
    { group:57, id:0, text: "Chef de l'éducation" }
    { group:57, id:1, text: "En service" }
    { group:57, id:2, text: "Peut éduquer" }
    { group:57, id:3, text: "Couverture de la cité" }
    { group:57, id:4, text: "enfants" }
    { group:57, id:5, text: "jeunes" }
    { group:57, id:6, text: "personnes" }
    { group:57, id:7, text: "Aucune" }
    { group:57, id:8, text: "Eparse" }
    { group:57, id:9, text: "Très faible" }
    { group:57, id:10, text: "Faible" }
    { group:57, id:11, text: "Un peu faible" }
    { group:57, id:12, text: "Moyenne" }
    { group:57, id:13, text: "Moyenne" }
    { group:57, id:14, text: "Assez bonne" }
    { group:57, id:15, text: "Bonne" }
    { group:57, id:16, text: "Très bonne" }
    { group:57, id:17, text: "Excellente" }
    { group:57, id:18, text: "Parfaite" }
    { group:57, id:19, text: "Certains secteurs de la cité ont besoin d'avoir accès à une école de scribes. Le manque de structures éducatives empêche le développement de logements de meilleure qualité dans certaines zones." }
    { group:57, id:20, text: "Certains quartiers exigent un meilleur accès à des écoles de scribes. Certains logements ont accès aux écoles publiques, mais pas tous, ce qui freine leur développement." }
    { group:57, id:21, text: "Une bibliothèque est requise dans certains secteurs de la cité. Les futurs scribes doivent avoir accès à la littérature." }
    { group:57, id:22, text: "Certains secteurs de la cité réclament un meilleur accès à une bibliothèque. Les riches scribes n'apprécient guère de devoir marcher autant pour arriver jusqu'à la bibliothèque." }
    { group:57, id:23, text: "Un meilleur accès à des écoles de scribes et des bibliothèques améliorerait certains secteurs de la cité. Les citoyens ne devraient pas avoir à marcher autant pour avoir accès à l'éducation !" }
    { group:57, id:24, text: "Aucun citoyen ne réclame encore d'installations éducatives. Cependant, au fur et à mesure que la cité se développe, il faut s'attendre à ce que les gens demandent des écoles de scribes, puis plus tard des bibliothèques." }
    { group:57, id:25, text: "Tous les besoins d'éducation de la cité sont satisfaits, et la couverture en installations éducatives est parfaite." }
    { group:57, id:26, text: "Bien que les besoins d'éducation de la cité soient globalement satisfaits, construire plus d'écoles de scribes réduirait le nombre d'élèves dans les salles de classe." }
    { group:57, id:27, text: "Bien que les besoins d'éducation de la cité soient globalement satisfaits, construire plus de bibliothèques réduirait la foule dans les salles de lecture." }
    { group:57, id:28, text: "Ecoles de scribes" }
    { group:57, id:29, text: "Bibliothèque" }
    { group:58, id:0, text: "Chef des loisirs" }
    { group:58, id:1, text: "Théâtres" }
    { group:58, id:2, text: "Spectacles" }
    { group:58, id:3, text: "Peut divertir" }
    { group:58, id:4, text: "Couverture de la cité" }
    { group:58, id:5, text: "personnes" }
    { group:58, id:6, text: "N.D." }
    { group:58, id:7, text: "Pour l'instant, vos citoyens ont des besoins simples et les loisirs ne sont pas une priorité. Cependant, avec l'évolution de votre cité, ils réclameront quelque chose qui leur fasse oublier la monotonie de leur train-train quotidien." }
    { group:58, id:8, text: "Les citoyens qui ont besoin de se changer les idées sont comblés. Cependant, avec l'évolution de la cité, il vous faudra rapidement fournir des formes de divertissement plus variées et plus nombreuses !" }
    { group:58, id:9, text: "Des citoyens se plaignent du manque d'installations de divertissement. Certains secteurs de la cité nécessitent des structures de loisirs plus variées afin de pouvoir se développer." }
    { group:58, id:10, text: "Des secteurs de la cité se plaignent car ils n'ont pas accès aux installations de divertissement. La construction de structures de loisirs pourrait aider au développement de ces quartiers." }
    { group:58, id:11, text: "Des citoyens se plaignent du manque de loisirs dans leur secteur. Il faudrait proposer une plus grande diversité ou peut-être construire plus d'écoles formant des artistes destinés à animer les structures qui en ont besoin." }
    { group:58, id:12, text: "Certaines structures manquent de musiciens ou de jongleurs et ne sont donc pas exploitées pleinement. Il faudrait plus d'artistes pour dynamiser certains secteurs de la cité qui manquent cruellement de divertissements." }
    { group:58, id:13, text: "Vos structures manquent de spectacles ! Il faudrait faire venir des danseurs pour augmenter l'offre de divertissements dans certains secteurs de la cité." }
    { group:58, id:14, text: "Votre taverne de jeux n'accueille aucun joueur de senet. Des jeux de senet dynamiseraient la population de la cité, qui aspire à plus de divertissements." }
    { group:58, id:15, text: "depuis la dernière fête" }
    { group:58, id:16, text: "Organiser une fête" }
    { group:58, id:17, text: "Fêtes" }
    { group:58, id:18, text: "Les plus grands fêtards ne se sont pas encore remis de la dernière fête." }
    { group:58, id:19, text: "Les gens parlent encore avec enthousiasme de la dernière fête." }
    { group:58, id:20, text: "Le souvenir de la dernière fête disparaît progressivement de la mémoire de la population." }
    { group:58, id:21, text: "Plus personne ne se souvient de la date de la dernière fête organisée dans la cité." }
    { group:58, id:22, text: "Les citoyens se plaignent du manque de fêtes organisées dans la cité." }
    { group:58, id:23, text: "La population est contrariée à l'idée de passer encore une année sans aucune fête." }
    { group:58, id:24, text: "'Nous voulons une fête !' réclament les gens dans les rues." }
    { group:58, id:30, text: "coûts" }
    { group:58, id:31, text: "Fête commune" }
    { group:58, id:32, text: "Fête somptueuse" }
    { group:58, id:33, text: "Fête grandiose" }
    { group:58, id:34, text: "Préparation de la fête pour" }
    { group:58, id:35, text: "Aucune" }
    { group:58, id:36, text: "Eparse" }
    { group:58, id:37, text: "Très faible" }
    { group:58, id:38, text: "Faible" }
    { group:58, id:39, text: "Un peu faible" }
    { group:58, id:40, text: "Moyenne" }
    { group:58, id:41, text: "Moyenne" }
    { group:58, id:42, text: "Assez bonne" }
    { group:58, id:43, text: "Bonne" }
    { group:58, id:44, text: "Très bonne" }
    { group:58, id:45, text: "Excellente" }
    { group:58, id:46, text: "Parfaite" }
    { group:58, id:47, text: "Théâtres de jongleurs" }
    { group:58, id:48, text: "Théâtres de musiciens" }
    { group:58, id:49, text: "Théâtres de danseurs" }
    { group:58, id:50, text: "Tavernes de jeux" }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Demander une fête" }
    { group:58, id:53, text: "Demande de fête pour" }
    { group:58, id:54, text: "le mois prochain" }
    { group:58, id:55, text: "en service" }
    { group:58, id:56, text: "Zoos" }
    { group:59, id:0, text: "Chef des temples" }
    { group:59, id:1, text: "Ensembles de" }
    { group:59, id:2, text: "temples" }
    { group:59, id:3, text: "Apaisement" }
    { group:59, id:4, text: "N.D." }
    { group:59, id:5, text: "Temples" }
    { group:59, id:6, text: "Mois" }
    { group:59, id:7, text: "Fête" }
    { group:59, id:8, text: "depuis" }
    { group:59, id:9, text: "Vos citoyens commencent à s'intéresser à la religion. La difficulté d'accès à un lieu de culte freine le développement de la cité." }
    { group:59, id:10, text: "De plus en plus de citoyens réclament au moins un lieu de culte dans leur quartier pour que les dieux aient une meilleure opinion d'eux." }
    { group:59, id:11, text: "Les citoyens de certains secteurs désirent accéder à d'autres cultes. Le manque de diversité religieuse limite le développement de ces quartiers." }
    { group:59, id:12, text: "Certains citoyens désirent introduire une troisième religion dans leur quartier. Ils pensent attirer ainsi des scribes de meilleure qualité." }
    { group:59, id:13, text: "Pour l'instant, vos citoyens sont surtout préoccupés par l'aspect matériel de la vie. Cependant, avec l'évolution de la cité, ils désireront avoir accès à différents types de temples." }
    { group:59, id:14, text: "La religion est florissante dans votre cité. Tous les cultes sont représentés, et les dieux sont satisfaits." }
    { group:59, id:15, text: "Il est dangereux de mécontenter Osiris. En effet, il peut détruire vos récoltes et vider vos greniers, ou même empêcher la crue du Nil." }
    { group:59, id:16, text: "Si le puissant Rê, père du pharaon, est mécontent, les cités voisines s'en ressentiront. La colère de Rê menace l'harmonie du royaume." }
    { group:59, id:17, text: "Ptah, dieu protecteur des artisans, est de plus en plus mécontent. Regagnez ses faveurs, sinon des pans entiers de l'industrie et de nombreux produits seront détruits." }
    { group:59, id:18, text: "Les soldats les plus braves tremblent devant la colère de Seth. Regagnez vite la confiance du dieu dans votre cité, ou votre armée sera balayée !" }
    { group:59, id:19, text: "Quand Bastet la douce est contrariée,  personne n'est en sécurité chez soi. Apaisez la déesse sans délai, ou préparez-vous à subir destructions et épidémies !" }
    { group:59, id:20, text: "Enragé" }
    { group:59, id:21, text: "Furieux" }
    { group:59, id:22, text: "En colère" }
    { group:59, id:23, text: "Froissé" }
    { group:59, id:24, text: "Mécontent" }
    { group:59, id:25, text: "Indifférent" }
    { group:59, id:26, text: "Aimable" }
    { group:59, id:27, text: "Agréable" }
    { group:59, id:28, text: "Sympathique" }
    { group:59, id:29, text: "Approbateur" }
    { group:59, id:30, text: "Bienveillant" }
    { group:59, id:31, text: "Vous avez désactivé l'influence des dieux. Qu'ils soient heureux ou furieux, ils ne se manifesteront pas." }
    { group:59, id:32, text: "Osiris est le dieu de la crue du Nil et de toute vie issue du monde souterrain. S'il vous est propice, votre cité bénéficiera chaque année d'une inondation recouvrant vos champs d'un limon fertile. Il peut aussi améliorer les récoltes. Avec un autel élevé à Sebek, dieu de la fertilité, les prêtres d'Osiris aideront vos citoyens à faire durer leurs réserves. Avec l'oracle de Min, dieu du renouveau, la nature dans votre cité et aux environs renaîtra. Son oracle rend les troupeaux plus forts, le poisson plus abondant et accélère même la pousse de certaines plantes." }
    { group:59, id:33, text: "En tant que dieu du royaume, Rê facilite le commerce et les voyages dans tout le monde connu ; il peut même vous aider à maintenir votre position dans toute l'Egypte. Avec un autel élevé à Maât, déesse de la justice, le crime dans votre cité sera freiné. Avec l'oracle d'Horus, dieu du pharaon, vos employés seront encouragés à vaquer de bonne grâce à leurs tâches quotidiennes. Au nom du pharaon, ils seront inspirés à travailler pour le plus grand bien de l'Egypte." }
    { group:59, id:34, text: "Ptah, dieu protecteur des artisans, aide souvent ces derniers à finir leur travail plus vite. Avec un autel élevé à Amon, dieu du soleil, votre cité pourra construire plus de monuments. Avec l'oracle de Thot, dieu de la sagesse et du savoir, l'éducation de vos citoyens sera favorisée." }
    { group:59, id:35, text: "Quand Seth est apaisé, vos ennemis deviennent les siens. Il aidera vos soldats les plus jeunes à se battre comme des vétérans expérimentés, et abattra même vos ennemis de sa propre main. Sa puissance est telle que son influence s'étend même aux batailles livrées très loin. Mais, bien sûr, si Seth n'est pas satisfait, votre cité subira la pleine mesure de ses pouvoirs destructeurs." }
    { group:59, id:36, text: "En tant que déesse du foyer, Bastet peut améliorer la qualité de vie dans votre cité et accorder à vos citoyens un niveau de vie bien plus élevé. Son pouvoir est tel qu'elle peut même vous concilier les autres dieux. Mais, bien sûr, si elle n'est pas apaisée, votre cité connaîtra une misère et des souffrances atroces. Avec un autel élevé à Isis, déesse de la guérison, vos citoyens seront assurés de rester en bonne santé et seront secourus en cas de maladie. Avec l'oracle d'Hathor, déesse de la joie, de l'amour et des fêtes,  vos citoyens seront toujours heureux, en dépit de leurs problèmes." }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Prêtresse" }
    { group:60, id:0, text: "Chef des finances" }
    { group:60, id:2, text: "La trésorerie de la cité s'élève à" }
    { group:60, id:3, text: "La dette de la cité s'élève à" }
    { group:60, id:4, text: "Somme due (environ) :" }
    { group:60, id:5, text: "des gens paient l'impôt" }
    { group:60, id:6, text: "L'an dernier" }
    { group:60, id:7, text: "Depuis le début de l'année" }
    { group:60, id:8, text: "Revenus (impôts)" }
    { group:60, id:9, text: "Revenus à l'exportation" }
    { group:60, id:10, text: "Revenus (total)" }
    { group:60, id:11, text: "Coûts à l'importation" }
    { group:60, id:12, text: "Salaire" }
    { group:60, id:13, text: "Constructions" }
    { group:60, id:14, text: "Intérêts à" }
    { group:60, id:15, text: "Salaire personnel" }
    { group:60, id:16, text: "Vols" }
    { group:60, id:17, text: "Dépenses" }
    { group:60, id:18, text: "Bénéfices / Pertes" }
    { group:60, id:19, text: "Solde" }
    { group:60, id:20, text: "Cadeaux" }
    { group:60, id:21, text: "Tribut" }
    { group:60, id:22, text: "Requêtes et fêtes" }
    { group:60, id:23, text: "en impôts manquants" }
    { group:60, id:24, text: "Or extrait" }
    { group:61, id:13, text: "Offre bien supérieure à la demande" }
    { group:61, id:14, text: "Offre un peu supérieure à la demande" }
    { group:61, id:15, text: "Juste assez de nourriture produite pour la cité" }
    { group:61, id:16, text: "IMPORTANT : consommation supérieure à production" }
    { group:61, id:17, text: "GRAVE : consommation supérieure à production" }
    { group:61, id:18, text: "URGENT : consommation supérieure à production" }
    { group:61, id:19, text: "SANS UTILISATION" }
    { group:61, id:20, text: "Tout le monde vous déteste." }
    { group:61, id:21, text: "La pop. est très en colère." }
    { group:61, id:22, text: "La pop. est en colère" }
    { group:61, id:23, text: "La pop. vous en veut beaucoup" }
    { group:61, id:24, text: "La pop. vous en veut" }
    { group:61, id:25, text: "La pop. est contrariée" }
    { group:61, id:26, text: "La pop. est indifférente" }
    { group:61, id:27, text: "La population vous aime bien." }
    { group:61, id:28, text: "La population vous aime beaucoup." }
    { group:61, id:29, text: "La population vous aime énormément." }
    { group:61, id:30, text: "La population vous adore." }
    { group:61, id:31, text: "La population vous considère comme un dieu." }
    { group:61, id:32, text: "car il y a des disettes." }
    { group:61, id:33, text: "car il y a du chômage." }
    { group:61, id:34, text: "car il y a trop d'impôts." }
    { group:61, id:35, text: "car les salaires sont bas." }
    { group:61, id:36, text: "car il y a des quartiers pauvres." }
    { group:61, id:37, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Le mécontentement des citoyens est exacerbé par le manque de nourriture. L'imposition élevée, les salaires bas, les inégalités sociales et le chômage peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:38, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Le mécontentement des citoyens est exacerbé par le manque de travail. L'imposition élevée, les salaires bas, les inégalités sociales et la disette peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:39, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Le mécontentement des citoyens est exacerbé par le taux d'imposition élevé. Les salaires bas, les inégalités sociales, le manque de nourriture et le chômage peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:40, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Le mécontentement des citoyens est exacerbé par les salaires bas que vous leur payez (comparativement à d'autres régions d'Egypte). L'imposition élevée, les inégalités sociales, le manque de nourriture et le chômage peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:41, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Le mécontentement des citoyens est exacerbé par les inégalités sociales flagrantes. L'imposition élevée, les salaires bas, le manque de nourriture et le chômage peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:42, text: "Le faible attrait de la cité contribue à augmenter le taux de criminalité, décourage l'immigration et peut même inciter la population actuelle à s'en aller. Les salaires bas, l'imposition élevée, les inégalités sociales, le manque de nourriture et le chômage peuvent aussi être des facteurs de ce manque d'attrait." }
    { group:61, id:43, text: "La guerre nuit à l'immigration !" }
    { group:61, id:44, text: "Des gens immigrent vers la cité" }
    { group:61, id:45, text: "Il n'y a pas assez de logements" }
    { group:61, id:46, text: "Les revenus sont trop bas" }
    { group:61, id:47, text: "Le chômage freine l'immigration" }
    { group:61, id:48, text: "Il n'y a pas assez de nourriture" }
    { group:61, id:49, text: "Le taux d'imposition est trop élevé" }
    { group:61, id:50, text: "Les quartiers pauvres freinent l'immigration" }
    { group:61, id:51, text: "La morosité de votre cité limite l'immigration" }
    { group:61, id:52, text: "La cité se vide à cause du manque de logements." }
    { group:61, id:53, text: "La cité se vide en raison des salaires bas." }
    { group:61, id:54, text: "La cité se vide en raison du manque de travail." }
    { group:61, id:55, text: "La cité se vide à cause du manque de nourriture." }
    { group:61, id:56, text: "La cité se vide en raison des impôts élevés." }
    { group:61, id:57, text: "Les quartiers pauvres font fuir les gens." }
    { group:61, id:58, text: "La cité se vide à cause de la morosité ambiante." }
    { group:61, id:59, text: "Peu de changements à prévoir" }
    { group:61, id:60, text: "Tant qu'il y aura des logements libres et que les habitants de votre cité seront satisfaits, les immigrants afflueront.  Vous devez construire plus de logements pour que votre cité s'agrandisse et devienne prospère." }
    { group:61, id:61, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront. Vous devez augmenter les salaires pour en attirer encore plus." }
    { group:61, id:62, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront. Vous devez créer des emplois en développant l'industrie, afin d'attirer encore plus d'immigrants." }
    { group:61, id:63, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront. Vous devez produire plus de nourriture pour attirer encore plus d'immigrants." }
    { group:61, id:64, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront. Vous devez baisser le taux d'imposition pour attirer encore plus d'immigrants." }
    { group:61, id:65, text: "En principe, vous devez augmenter votre population, pour que la cité s'agrandisse et devienne prospère.  Les nouveaux immigrants sont attirés par des logements libres et le charme de la cité." }
    { group:61, id:66, text: "En principe, vous devez augmenter votre population, pour que la cité s'agrandisse et devienne prospère. Comme des logements sont disponibles et que les habitants sont heureux, de nouveaux immigrants affluent." }
    { group:61, id:67, text: "Si le fossé entre riches et pauvres est trop important, personne ne voudra s'installer dans votre cité. Offrez de meilleurs services aux quartiers les plus pauvres, afin de rééquilibrer la balance en faveur des citoyens défavorisés." }
    { group:61, id:68, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront. Vous devez augmenter l'attrait de votre cité pour attirer encore plus d'immigrants." }
    { group:61, id:69, text: "Tant qu'il y aura assez de logements et que les habitants de votre cité seront heureux, les immigrants afflueront (et vos propres citoyens ne seront pas tentés de s'exiler !). Construisez plus de logements pour que votre cité s'agrandisse et devienne prospère." }
    { group:61, id:70, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, ils resteront. Augmentez les salaires pour les inciter à rester." }
    { group:61, id:71, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, ils resteront. Créez plus d'emplois en développant l'industrie, afin de les inciter à rester." }
    { group:61, id:72, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, ils resteront. Etant donné la taille de la population actuelle, vous devez produire plus de nourriture pour inciter les gens à rester." }
    { group:61, id:73, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, ils resteront. Ils y seront encore encouragés par une baisse de l'imposition." }
    { group:61, id:74, text: "Si le fossé entre riches et pauvres est trop important, les gens préféreront tenter leur chance ailleurs. Offrez de meilleurs services aux quartiers les plus pauvres, afin de rééquilibrer la balance en faveur des personnes défavorisées." }
    { group:61, id:75, text: "Tant que les habitants de votre cité seront satisfaits et qu'il y aura assez de logements, les immigrants afflueront (et vos propres citoyens ne seront pas tentés de s'exiler !). Vous devez augmenter l'attrait de votre cité pour que les gens y restent." }
    { group:61, id:76, text: "URGENT : le chômage touche" }
    { group:61, id:77, text: "GRAVE :  le chômage touche" }
    { group:61, id:78, text: "IMPORTANT : le chômage touche" }
    { group:61, id:79, text: "Le chômage touche" }
    { group:61, id:80, text: "URGENT : la cité a besoin de" }
    { group:61, id:81, text: "GRAVE : la cité a besoin de" }
    { group:61, id:82, text: "IMPORTANT : la cité a besoin de" }
    { group:61, id:83, text: "La cité a besoin de" }
    { group:61, id:84, text: "Pas de problèmes de chômage" }
    { group:61, id:85, text: "Le taux élevé de chômage incite la population à chercher du travail ailleurs. Développez l'industrie pour créer des emplois." }
    { group:61, id:86, text: "Le taux élevé de chômage risque d'inciter la population à chercher du travail ailleurs. Vous pouvez créer des emplois en créant plus d'industries." }
    { group:61, id:87, text: "Le taux élevé de chômage risque d'inciter la population à chercher du travail ailleurs. Vous pouvez créer des emplois en créant plus d'industries." }
    { group:61, id:88, text: "Ce niveau de chômage est supportable mais s'il augmente trop, la population risque de chercher du travail ailleurs. Vous pouvez créer des emplois en créant plus d'industries." }
    { group:61, id:89, text: "Avec une telle pénurie de main-d'œuvre, votre cité va peu à peu être paralysée. Fermez les industries inutiles ou attirez plus de travailleurs par la construction de logements vides et par l'image d'une population heureuse." }
    { group:61, id:90, text: "Avec une grave pénurie de main-d'œuvre, vos citoyens ne seront plus en mesure d'accomplir leurs tâches quotidiennes. Fermez les industries inutiles ou attirez plus de travailleurs par la construction de logements vides et par l'image d'une population heureuse." }
    { group:61, id:91, text: "S'il n'y a pas assez de travailleurs, vos citoyens auront du mal à accomplir leurs tâches quotidiennes." }
    { group:61, id:92, text: "Les pénuries de main-d'œuvre peuvent entraîner une diminution de la circulation des biens et des services dans la cité. Augmentez la rentabilité de votre cité en fermant les industries inutiles ou en attirant plus de travailleurs par la construction de logements vides et par l'image d'une population heureuse." }
    { group:61, id:93, text: "Le taux élevé de chômage peut obliger une population heureuse par ailleurs à partir à la recherche de travail, tandis que des pénuries de main-d'œuvre peuvent entraîner une diminution de la circulation des biens et des services dans la cité." }
    { group:61, id:94, text: "La capitale subvient à tous nos besoins" }
    { group:61, id:95, text: "URGENT : réserves de nourriture presque épuisées" }
    { group:61, id:96, text: "GRAVE : réserves de nourriture presque épuisées" }
    { group:61, id:97, text: "IMPORTANT : nourriture presque épuisée" }
    { group:61, id:98, text: "Réserves pour" }
    { group:61, id:99, text: "Si vos citoyens sautent trop de repas, leur santé va se dégrader (ou ils quitteront la cité à la recherche d'un meilleur niveau de vie). Assurez-vous que la population ne consomme pas plus qu'elle ne produit et que vous disposez de greniers en nombre suffisant pour engranger les récoltes." }
    { group:61, id:100, text: "Si vos citoyens sautent trop de repas, leur santé va se dégrader (ou ils quitteront la cité à la recherche d'un meilleur niveau de vie). Assurez-vous que la population ne consomme pas plus qu'elle ne produit et que vous disposez de greniers en nombre suffisant pour engranger les récoltes." }
    { group:61, id:101, text: "Si vos citoyens sautent trop de repas, leur santé va se dégrader (ou ils quitteront la cité à la recherche d'un meilleur niveau de vie). Assurez-vous que la population ne consomme pas plus qu'elle ne produit et que vous disposez de greniers en nombre suffisant pour engranger les récoltes." }
    { group:61, id:102, text: "Si vos citoyens sautent trop de repas, leur santé va se dégrader (ou ils quitteront la cité à la recherche d'un meilleur niveau de vie). Assurez-vous que la population ne consomme pas plus qu'elle ne produit et que vous disposez de greniers en nombre suffisant pour engranger les récoltes." }
    { group:61, id:103, text: "URGENT : hygiène épouvantable ; risque de peste." }
    { group:61, id:104, text: "URGENT : hygiène pitoyable ; risque de peste." }
    { group:61, id:105, text: "GRAVE : mauvaise hygiène ; risque de peste." }
    { group:61, id:106, text: "IMPORTANT : hygiène médiocre ; risque de peste." }
    { group:61, id:107, text: "L'hygiène dans votre cité est insuffisante." }
    { group:61, id:108, text: "L'hygiène dans votre cité est moyenne." }
    { group:61, id:109, text: "L'hygiène dans votre cité est bonne." }
    { group:61, id:110, text: "L'hygiène dans votre cité est très bonne." }
    { group:61, id:111, text: "L'hygiène dans votre cité est excellente." }
    { group:61, id:112, text: "L'hygiène dans votre cité est presque parfaite." }
    { group:61, id:113, text: "L'hygiène dans votre cité est parfaite." }
    { group:61, id:114, text: "Vu l'état sanitaire déplorable de ses habitants, votre cité va certainement subir une épidémie de peste, qui risque de décimer sa population. Construisez des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:115, text: "Vu le mauvais état sanitaire de ses habitants, votre cité ne devrait pas tarder à subir une épidémie de peste, qui risque de décimer sa population. Vous devez construire des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:116, text: "Vu le mauvais état sanitaire des habitants de la cité, les apothicaires et les médecins ont du mal à faire face. La cité risque de subir une épidémie de peste, qui pourrait dévaster la population. Construisez des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:117, text: "Vu le mauvais état sanitaire des habitants de la cité, les apothicaires et les médecins ont du mal à faire face. La cité pourrait être frappée par une épidémie de peste, qui risque de dévaster la population. Construisez des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:118, text: "Si l'hygiène de ses habitants empire, la cité pourrait subir une épidémie de peste, qui risquerait de dévaster la population. Construisez des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:119, text: "Si l'hygiène de ses habitants empire, la cité pourrait subir une épidémie de peste, qui risquerait de dévaster la population. Construisez des dispensaires et des salles d'embaumeurs à l'intention des citoyens qui n'ont pas encore accès aux services de médecins et d'embaumeurs. Par ailleurs, assurez-vous que la population dispose de réserves suffisantes de nourriture." }
    { group:61, id:120, text: "Il est important d'être en bonne santé pour se protéger contre la malaria et les maladies, et surtout pour empêcher la peste de se répandre dans la cité. Si la santé de la population se détériore, la peste risque de faire des ravages. Les médecins et les embaumeurs, responsables des dispensaires et des salles d'embaumeurs, contribuent au maintien de la santé publique en complément d'une alimentation riche et variée." }
    { group:61, id:121, text: "Il est important d'être en bonne santé pour se protéger contre la malaria et les maladies, et surtout pour empêcher la peste de se répandre dans la cité. Si la santé de la population se détériore, la peste risque la peste risque de faire des ravages. Les médecins et les embaumeurs, responsables des dispensaires et des salles d'embaumeurs, contribuent au maintien de la santé publique en complément d'une alimentation riche et variée." }
    { group:61, id:122, text: "Il est important d'être en bonne santé pour se protéger contre la malaria et les maladies et surtout pour empêcher la peste de se répandre dans la cité. Si la santé de la population se détériore, la peste risque de faire des ravages. Les médecins et les embaumeurs, responsables des dispensaires et des salles d'embaumeurs, contribuent au maintien de la santé publique en complément d'une alimentation riche et variée." }
    { group:61, id:123, text: "Il est important d'être en bonne santé pour se protéger contre la malaria et les maladies et surtout pour empêcher la peste de se répandre dans la cité. Si la santé de la population se détériore, la peste risque de faire des ravages. Les médecins et les embaumeurs, responsables des dispensaires et des salles d'embaumeurs, contribuent au maintien de la santé publique en complément d'une alimentation riche et variée." }
    { group:61, id:124, text: "Il est important d'être en bonne santé pour se protéger contre la malaria et les maladies et surtout pour empêcher la peste de se répandre dans la cité. Si la santé de la population se détériore, la peste risque de faire des ravages. Les médecins et les embaumeurs, responsables des dispensaires et des salles d'embaumeurs, contribuent au maintien de la santé publique en complément d'une alimentation riche et variée." }
    { group:61, id:125, text: "IMPORTANT : plusieurs dieux sont courroucés" }
    { group:61, id:126, text: "SERIEUX : plusieurs dieux risquent de frapper" }
    { group:61, id:127, text: "IMPORTANT : trois dieux sont courroucés" }
    { group:61, id:128, text: "SERIEUX : trois dieux sont courroucés" }
    { group:61, id:129, text: "IMPORTANT : deux dieux sont courroucés" }
    { group:61, id:130, text: "SERIEUX : deux dieux sont courroucés" }
    { group:61, id:131, text: "IMPORTANT : un dieu est courroucé" }
    { group:61, id:132, text: "SERIEUX : un dieu est courroucé" }
    { group:61, id:133, text: "Tous les dieux ont été apaisés" }
    { group:61, id:134, text: "L'un des dieux apaisés est spécialement content" }
    { group:61, id:135, text: "Deux dieux apaisés sont spécialement contents" }
    { group:61, id:136, text: "Trois dieux apaisés sont spécialement contents" }
    { group:61, id:137, text: "Plusieurs dieux sont particulièrement contents" }
    { group:61, id:138, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:139, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:140, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:141, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:142, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:143, text: "Des dieux hostiles risquent de dévaster votre cité. Pour les apaiser, construisez des temples et organisez des fêtes en leur honneur." }
    { group:61, id:144, text: "Un dieu hostile risque de dévaster votre cité. Pour l'apaiser, construisez un temple et organisez des fêtes en son honneur." }
    { group:61, id:145, text: "Un dieu hostile risque de dévaster votre cité. Pour l'apaiser, construisez un temple et organisez des fêtes en son honneur." }
    { group:61, id:146, text: "Si un dieu devient hostile, il risque de dévaster votre cité." }
    { group:61, id:147, text: "Les dieux bienveillants peuvent favoriser votre cité de plusieurs façons. Pendant que vous la développez, veillez à ne pas vous attirer la colère des dieux : dédiez-leur des temples et organisez des fêtes en leur honneur." }
    { group:61, id:148, text: "Les dieux bienveillants peuvent favoriser votre cité de plusieurs façons. Pendant que vous la développez, veillez à ne pas vous attirer la colère des dieux : dédiez-leur des temples et organisez des fêtes en leur honneur." }
    { group:61, id:149, text: "Les dieux bienveillants peuvent favoriser votre cité de plusieurs façons. Pendant que vous la développez, veillez à ne pas vous attirer la colère des dieux : dédiez-leur des temples et organisez des fêtes en leur honneur." }
    { group:61, id:150, text: "Les dieux bienveillants peuvent favoriser votre cité de plusieurs façons. Pendant que vous la développez, veillez à ne pas vous attirer la colère des dieux : dédiez-leur des temples et organisez des fêtes en leur honneur." }
    { group:61, id:151, text: "SERIEUX : nous ne percevons presque pas d'impôts" }
    { group:61, id:152, text: "L'avoir de cette année a augmenté de" }
    { group:61, id:153, text: "La situation est presque la même cette année." }
    { group:61, id:154, text: "L'avoir de cette année a diminué de" }
    { group:61, id:155, text: "Vous ne touchez pas tout ce qui vous est dû, car vous n'avez pas assez de percepteurs. Recrutez davantage de percepteurs, surtout dans les zones les plus riches, et assurez-vous qu'ils ont accès à tout le monde avec la carte des impôts." }
    { group:61, id:156, text: "Si votre trésor s'épuise, vous pouvez emprunter 5 000 debens. Mais attention, une dette prolongée peut avoir des conséquences sérieuses. Les impôts, les exportations et les mines d'or restent le meilleur moyen d'enrichir la cité. Ceci dit, vous pouvez toujours verser une partie de vos économies dans le trésor de la cité." }
    { group:61, id:157, text: "Si votre trésor s'épuise, vous pouvez emprunter 5 000 debens. Mais attention, une dette prolongée peut avoir des conséquences sérieuses. Les impôts, les exportations et les mines d'or restent le meilleur moyen d'enrichir la cité. Ceci dit, vous pouvez toujours verser une partie de vos économies dans le trésor de la cité." }
    { group:61, id:158, text: "Si vous continuez à perdre de l'argent, vous risquez de devoir emprunter. Un maximum de 5 000 debens est à votre disposition. Mais attention, une dette prolongée peut avoir des répercussions graves. Les impôts, les exportations et les mines d'or restent le meilleur moyen d'enrichir la cité. Ceci dit, vous pouvez toujours verser une partie de vos économies dans le trésor de la cité." }
    { group:61, id:159, text: "URGENT : de nombreux vols récents," }
    { group:61, id:160, text: "SERIEUX : plusieurs vols récents," }
    { group:61, id:161, text: "IMPORTANT : quelques vols récents," }
    { group:61, id:162, text: "Très peu de vols." }
    { group:61, id:163, text: "Aucun vol signalé" }
    { group:61, id:164, text: "db volés." }
    { group:61, id:165, text: "Ce niveau de vol risquent d'affecter sérieusement le trésor de la cité, sans parler de vos économies ! Un nombre adéquat de palais de justice et de postes de police permet de limiter la criminalité. Les agents arrêtent les voleurs qu'ils rencontrent. Naturellement, le meilleur remède est toujours la prévention. Pour cela, veillez au bonheur de vos administrés." }
    { group:61, id:166, text: "Des vols fréquents risquent d'affecter sérieusement le trésor de la cité, sans parler de vos économies ! Un nombre adéquat de palais de justice et de postes de police permet de limiter la criminalité. Les agents arrêtent les voleurs qu'ils rencontrent. Naturellement, le meilleur remède est toujours la prévention. Pour cela, veillez au bonheur de vos administrés." }
    { group:61, id:167, text: "Des vols fréquents risquent d'affecter le trésor de la cité, sans parler de vos économies ! Un nombre adéquat de palais de justice et de postes de police permet de limiter la criminalité. Les agents arrêtent les voleurs qu'ils rencontrent. Naturellement, le meilleur remède est toujours la prévention. Pour cela, veillez au bonheur de vos administrés." }
    { group:61, id:168, text: "Des vols fréquents risquent d'affecter le trésor de la cité, sans parler de vos économies ! Un nombre adéquat de palais de justice et de postes de police permet de limiter la criminalité. Les agents arrêtent les voleurs qu'ils rencontrent. Naturellement, le meilleur remède est toujours la prévention. Pour cela, veillez au bonheur de vos administrés." }
    { group:61, id:169, text: "Des vols risquent d'affecter le trésor de la cité, sans parler de vos économies ! Un nombre adéquat de palais de justice et de postes de police permet de limiter la criminalité. Les agents arrêtent les voleurs qu'ils rencontrent. Naturellement, le meilleur remède est toujours la prévention. Pour cela, veillez au bonheur de vos administrés." }
    { group:61, id:170, text: "Aucune compagnie n'est sous votre commandement" }
    { group:61, id:171, text: "La cité n'est pas menacée" }
    { group:61, id:172, text: "Les ennemis s'approchent de la cité" }
    { group:61, id:173, text: "Les ennemis attaquent la cité" }
    { group:61, id:174, text: "Les troupes ennemies sont aux portes de notre cité" }
    { group:61, id:175, text: "Nos troupes sont attendues ailleurs" }
    { group:61, id:176, text: "Nous avons des troupes ailleurs" }
    { group:61, id:177, text: "Aucune force militaire n'est à notre disposition. Cela n'a pas d'importance pour l'instant, car il n'y a pas de danger." }
    { group:61, id:178, text: "Lorsque des ennemis approchent de notre cité, votre scribe envoie un message. Des armées ennemies ont fait leur apparition sur la mappemonde. Surveillez leur progression et essayez de préparer la cité." }
    { group:61, id:179, text: "Une armée ennemie est en formation d'attaque ! Il est difficile, voire impossible de construire des bâtiments pendant une attaque. Alors, préparez vos défenses en construisant des murs, des tours, des corps de garde et des forts avant leur arrivée." }
    { group:61, id:180, text: "Il est toujours préférable de prévoir les attaques que de réunir des soldats au dernier moment. Heureusement, les défenses de notre cité sont suffisantes." }
    { group:61, id:181, text: "Il est toujours préférable de prévoir les attaques que de réunir des soldats au dernier moment. Heureusement, les défenses de notre cité sont suffisantes." }
    { group:61, id:182, text: "Un commandant égyptien nous demande des renforts. Il est préférable d'honorer ce type de requête pour rester en bons termes avec le reste du royaume. Consultez le chef politique, ainsi que le chef militaire avant d'envoyer des troupes." }
    { group:61, id:183, text: "Une partie de nos troupes sert l'Egypte en participant à des campagnes militaires lointaines. Il est recommandé de participer à la défense du royaume pour rester en bons termes avec l'ensemble de ses sujets." }
    { group:61, id:184, text: "Bien des requêtes sur notre cité restent en suspens." }
    { group:61, id:185, text: "Plusieurs requêtes sur notre cité restent en suspens." }
    { group:61, id:186, text: "Certaines requêtes sur notre cité restent en suspens." }
    { group:61, id:187, text: "Toutes les requêtes sur notre cité ont été satisfaites." }
    { group:61, id:188, text: "Ignorer les requêtes du pharaon et de vos voisins peut avoir des conséquences graves. Si vous ne secourez pas les autres cités égyptiennes, ces dernières risquent de succomber à la pauvreté ou de tomber aux mains des ennemis. Pour rester en bons termes avec vos concitoyens, il est préférable de répondre prestement et volontairement à ce type de requête." }
    { group:61, id:189, text: "Ne pas répondre aux requêtes du pharaon et de vos voisins risque d'avoir des conséquences graves. Si vous ne secourez pas les autres cités égyptiennes, ces dernières risquent de succomber à la pauvreté ou de tomber aux mains de vos ennemis. Pour rester en bons termes avec vos concitoyens, il est préférable de répondre prestement et volontairement à ce type de requête." }
    { group:61, id:190, text: "Si vous ne secourez pas les autres cités égyptiennes, ces dernières risquent de succomber à la pauvreté ou de tomber aux mains de leurs ennemis ou de subir un sort peu enviable. En outre, le commerce, les prix, voire l'état du royaume risquent d'en souffrir. Pour rester en bons termes avec vos concitoyens, il est préférable de répondre prestement et volontairement aux requêtes." }
    { group:61, id:191, text: "Pour rester en bons termes avec vos concitoyens, il est préférable de répondre prestement et volontairement aux requêtes adressées dans le besoin. Sinon, ils risquent de succomber à la pauvreté ou de tomber aux mains de leurs ennemis ou de subir un sort peu enviable. En outre, le commerce, les prix, voire l'état du royaume risquent d'en souffrir." }
    { group:61, id:192, text: "Il n'y aura pas d'inondation cette année" }
    { group:61, id:193, text: "L'inondation sera faible cette année" }
    { group:61, id:194, text: "L'inondation sera médiocre cette année" }
    { group:61, id:195, text: "L'inondation sera bonne cette année" }
    { group:61, id:196, text: "L'inondation sera excellente cette année" }
    { group:61, id:197, text: "L'inondation sera parfaite cette année" }
    { group:61, id:198, text: "La faiblesse de la crue de cette année implique que le limon fertile ne sera pas déposé dans vos champs. Si votre cité dépend de la culture des terres inondables, la survie de vos citoyens est en jeu. Le culte d'Osiris, le dieu régissant les crues du Nil, permettra d'éviter une répétition de ce phénomène l'année suivante." }
    { group:61, id:199, text: "La faible inondation prévue pour cette année implique que très peu de limon fertile viendra engraisser vos champs. Si votre cité dépend de la culture des terres inondables, la survie de vos citoyens risque d'être menacée. Apaisez Osiris, le dieu régissant les crues du Nil, pour éviter une répétition de ce phénomène l'année suivante." }
    { group:61, id:200, text: "L'inondation médiocre prévue pour cette année implique que très peu de limon fertile sera déposé dans vos champs. Si votre cité dépend de la culture des terres inondables, la survie de vos citoyens est menacée. Développez le culte d'Osiris, le dieu régissant les crues du Nil, pour éviter une répétition de ce phénomène l'année suivante." }
    { group:61, id:201, text: "Une bonne inondation a été prévue pour cette année ce qui déposera le limon fertile dans les champs de votre cité. Assurez-vous qu'Osiris, le dieu de la crue du Nil, reste satisfait, faute de quoi il risque de retirer sa protection l'année prochaine." }
    { group:61, id:202, text: "Si votre cité dépend de la culture des terres inondables, la quantité de limon fertile déposé dans vos champs par l'inondation ne doit pas être considérée comme acquise. Assurez-vous qu'Osiris, le dieu de la crue du Nil, reste satisfait, faute de quoi il risque de retirer sa protection l'année prochaine." }
    { group:61, id:203, text: "Si votre cité dépend de la culture des terres inondables, la quantité idéale de limon fertile déposé dans vos champs par l'inondation de cette année est un trésor qui ne doit pas être considéré comme acquis. Glorifiez Osiris, le dieu de la crue du Nil, pour que cela se reproduise l'année prochaine." }
    { group:61, id:204, text: "La crue devrait se produire début juin" }
    { group:61, id:205, text: "La crue devrait se produire fin juin" }
    { group:61, id:206, text: "La crue devrait se produire début juillet" }
    { group:61, id:207, text: "La crue devrait se produire fin juillet" }
    { group:61, id:208, text: "La crue devrait se produire début août" }
    { group:61, id:209, text: "La crue devrait se produire fin août" }
    { group:61, id:210, text: "La crue devrait se produire début septembre" }
    { group:61, id:211, text: "La crue devrait se produire fin septembre" }
    { group:61, id:212, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Pour nourrir ce niveau de population, construisez davantage de fermes, de pavillons de chasse, de quais ou de fermes d'élevage, ou bien importez davantage de nourriture. L'irrigation permet également d'améliorer le rendement des terres cultivées." }
    { group:61, id:213, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Pour nourrir ce niveau de population, construisez davantage de fermes, de pavillons de chasse ou de fermes d'élevage, ou bien importez davantage de nourriture." }
    { group:61, id:214, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Pour nourrir ce niveau de population, construisez davantage de fermes, de pavillons de chasse ou de fermes d'élevage, ou bien importez davantage de nourriture." }
    { group:61, id:215, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Vos fermes, fermes d'élevage, pavillons de chasse et stocks de nourriture importée constituent une infrastructure idéale pour ce niveau de population." }
    { group:61, id:216, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Le nombre de vos fermes, fermes d'élevage et pavillons de chasse est un peu trop élevé pour une population de ce niveau." }
    { group:61, id:217, text: "Si vos citoyens ne mangent pas à leur faim, ils s'exposent à des maladies (ou ils risquent d'émigrer). Le nombre de vos fermes, fermes d'élevage et pavillons de chasse est beaucoup trop élevé pour une population de ce niveau." }
    { group:61, id:218, text: "Cliquez sur l'un des éléments pour obtenir des informations et des conseils" }
    { group:62, id:0, text: "Victoire" }
    { group:62, id:1, text: "Destitué !" }
    { group:62, id:2, text: "Mission accomplie !" }
    { group:62, id:3, text: "Terminer la mission" }
    { group:62, id:4, text: "Continuer à gouverner pendant 2 ans." }
    { group:62, id:5, text: "Continuer pendant 5 ans." }
    { group:62, id:6, text: "Nouvelle partie" }
    { group:62, id:7, text: "Rejoindre la cité" }
    { group:62, id:8, text: "Félicitations !" }
    { group:62, id:9, text: "Vous avez accompli toutes les missions de la 'Période prédynastique'. Pour un vrai défi, cliquez de nouveau sur 'Exécuter la démo', puis passez à la 'Période archaïque'." }
    { group:62, id:10, text: "Objectifs" }
    { group:62, id:11, text: "Population de" }
    { group:62, id:12, text: "Niveau de culture de" }
    { group:62, id:13, text: "Niveau de prospérité de" }
    { group:62, id:14, text: "Niveau architectural de" }
    { group:62, id:15, text: "Niveau du royaume de" }
    { group:62, id:16, text: "Je suis vraiment perplexe. Malgré toute la confiance accordée par le peuple d'Egypte, il semblerait que les dieux aient abandonné votre cause. Votre cité ne fait pas honneur à l'Egypte. En outre, votre place dans l'au-delà est compromise. Quel dommage, surtout après un si bon début. Un autre doit désormais prendre votre place. - Le pharaon" }
    { group:62, id:17, text: "Construire des casernes de pompiers." }
    { group:62, id:18, text: "Construire des études d'architecte." }
    { group:62, id:19, text: "Construire un grenier et le remplir de gibier." }
    { group:62, id:20, text: "Offrir des maisons ayant accès au bazar." }
    { group:62, id:21, text: "Construire des maisons." }
    { group:62, id:22, text: "Construire des étals et des écoles de jongleurs." }
    { group:62, id:23, text: "Eriger des temples et des sanctuaires en l'honneur de Bastet." }
    { group:62, id:24, text: "Extraire de l'or." }
    { group:62, id:25, text: "Construire des pharmacies et des dispensaires." }
    { group:62, id:32, text: "Construire un mastaba" }
    { group:62, id:34, text: "Cliquez sur le symbole ankh pour afficher vos objectifs" }
    { group:62, id:35, text: "En accédant au rang de déité, vous entrez dans l'Histoire !" }
    { group:62, id:36, text: "Accepter le statut de déité !" }
    { group:62, id:37, text: "Rejouer la mission" }
    { group:62, id:38, text: "Temps épuisé" }
    { group:62, id:39, text: "Vous avez échoué dans votre mission. Choisissez un niveau de difficulté inférieur ou recommencez la mission." }
    { group:62, id:40, text: "Facile" }
    { group:63, id:0, text: "Messages" }
    { group:63, id:1, text: "Aucun message n'est en attente. Pendant le développement de la cité ou lorsque les autres villes vous demandent des biens, des messages sont affichés ici." }
    { group:63, id:2, text: "Date" }
    { group:63, id:3, text: "Sujet" }
    { group:63, id:4, text: "Cliquez sur un message pour le lire. Faites un cliquez droit sur un message pour l'effacer." }
    { group:63, id:5, text: "Pour" }
    { group:63, id:6, text: "Supprimer les messages ouverts" }
    { group:64, id:0, text: "Personne" }
    { group:64, id:1, text: "Immigrant" }
    { group:64, id:2, text: "Emigrant" }
    { group:64, id:3, text: "Sans abri" }
    { group:64, id:4, text: "- Charretier" }
    { group:64, id:5, text: "Citoyen" }
    { group:64, id:6, text: "Explosion" }
    { group:64, id:7, text: "Percepteur" }
    { group:64, id:8, text: "Architecte" }
    { group:64, id:9, text: "Magasinier" }
    { group:64, id:10, text: "Capitaine des pompiers" }
    { group:64, id:11, text: "Archer" }
    { group:64, id:12, text: "Fantassin" }
    { group:64, id:13, text: "Conducteur de char" }
    { group:64, id:14, text: "Porte-enseigne" }
    { group:64, id:15, text: "Jongleur" }
    { group:64, id:16, text: "Musicien" }
    { group:64, id:17, text: "Danseur" }
    { group:64, id:18, text: "Joueur de senet" }
    { group:64, id:19, text: "Caravane de marchands de" }
    { group:64, id:20, text: "Navire commercial de" }
    { group:64, id:21, text: "Caravane de marchands de" }
    { group:64, id:22, text: "Manifestant" }
    { group:64, id:23, text: "Criminel" }
    { group:64, id:24, text: "Pilleur de tombes" }
    { group:64, id:25, text: "Bateau de pêche" }
    { group:64, id:26, text: "Marchand de bazar" }
    { group:64, id:27, text: "Prêtre" }
    { group:64, id:28, text: "Ecolier" }
    { group:64, id:29, text: "Professeur" }
    { group:64, id:30, text: "Bibliothécaire" }
    { group:64, id:31, text: "Dentiste" }
    { group:64, id:32, text: "Médecin" }
    { group:64, id:33, text: "Herboriste" }
    { group:64, id:34, text: "Embaumeur" }
    { group:64, id:35, text: "Ouvrier" }
    { group:64, id:36, text: "Drapeau" }
    { group:64, id:37, text: "Débris" }
    { group:64, id:38, text: "Docker" }
    { group:64, id:39, text: "Acheteur de bazar" }
    { group:64, id:40, text: "Scribe" }
    { group:64, id:41, text: "Indigène (not used?)" }
    { group:64, id:42, text: "Sentinelle" }
    { group:64, id:43, text: "Ennemi" }
    { group:64, id:44, text: "Ennemi" }
    { group:64, id:45, text: "Ennemi" }
    { group:64, id:46, text: "Ennemi" }
    { group:64, id:47, text: "Ennemi" }
    { group:64, id:48, text: "Ennemi" }
    { group:64, id:49, text: "Barbarian (not used?)" }
    { group:64, id:50, text: "Barbarian (not used?)" }
    { group:64, id:51, text: "Barbarian (not used?)" }
    { group:64, id:52, text: "Barbarian (not used?)" }
    { group:64, id:53, text: "Ennemi" }
    { group:64, id:54, text: "Ennemi" }
    { group:64, id:55, text: "Ennemi" }
    { group:64, id:56, text: "Ennemi" }
    { group:64, id:57, text: "Ennemi" }
    { group:64, id:58, text: "Native Trader (not used?)" }
    { group:64, id:59, text: "Flèche" }
    { group:64, id:60, text: "Javeline" }
    { group:64, id:61, text: "Lance de baliste" }
    { group:64, id:62, text: "Baliste" }
    { group:64, id:63, text: "Créature" }
    { group:64, id:64, text: "Missionnaire" }
    { group:64, id:65, text: "Mouette" }
    { group:64, id:66, text: "Livreur" }
    { group:64, id:67, text: "Epave" }
    { group:64, id:68, text: "Oiseaux" }
    { group:64, id:69, text: "Autruche" }
    { group:64, id:70, text: "Antilope" }
    { group:64, id:71, text: "Lance" }
    { group:64, id:72, text: "Coureur de char" }
    { group:64, id:73, text: "Chasseur" }
    { group:64, id:74, text: "Lance de chasseur" }
    { group:64, id:75, text: "Bûcheron" }
    { group:64, id:76, text: "Bac" }
    { group:64, id:77, text: "Transporteur" }
    { group:64, id:78, text: "Navire de guerre" }
    { group:64, id:79, text: "Menuisier" }
    { group:64, id:80, text: "Maçon" }
    { group:64, id:81, text: "Tailleur de pierre," }
    { group:64, id:82, text: "Crocodile" }
    { group:64, id:83, text: "Hyène" }
    { group:64, id:84, text: "Hippopotame" }
    { group:64, id:85, text: "Main-d'œuvre" }
    { group:64, id:86, text: "Traî" }
    { group:64, id:87, text: "Porteur d'eau" }
    { group:64, id:88, text: "Agent" }
    { group:64, id:89, text: "Magistrat" }
    { group:64, id:90, text: "Cueilleur de roseaux" }
    { group:64, id:91, text: "Prêtre de fête" }
    { group:64, id:92, text: "Transporteur ennemi" }
    { group:64, id:93, text: "Navire de guerre ennemi" }
    { group:64, id:94, text: "Employé funéraire" }
    { group:64, id:95, text: "Poisson" }
    { group:64, id:96, text: "Cond. Traîn" }
    { group:64, id:97, text: "Artiste" }
    { group:64, id:98, text: "Pestiféré" }
    { group:64, id:99, text: "Fantassin bédouin" }
    { group:64, id:100, text: "Navire de guerre égyptien" }
    { group:64, id:101, text: "Transporteur égyptien" }
    { group:64, id:102, text: "Aspic" }
    { group:64, id:103, text: "Lion" }
    { group:64, id:104, text: "Scorpion" }
    { group:64, id:105, text: "Gardien du zoo" }
    { group:64, id:106, text: "Grenouille" }
    { group:64, id:107, text: "Criquet" }
    { group:64, id:108, text: "Artisan funéraire" }
    { group:64, id:109, text: "Momie" }
    { group:64, id:110, text: "Pharaon" }
    { group:65, id:0, text: "unused section 65 - was c3 walker names" }
    { group:66, id:0, text: "Bulles d'aide des cartes." }
    { group:66, id:1, text: "Cette terre est proche d'une nappe phréatique et permet de creuser des puits de toutes dimensions." }
    { group:66, id:2, text: "Cette demeure n'a pas accès à de l'eau potable." }
    { group:66, id:3, text: "Cette demeure n'a qu'un accès rudimentaire à de l'eau potable." }
    { group:66, id:4, text: "Cette maison n'a pas de réserve de nourriture." }
    { group:66, id:5, text: "Cette maison aura bientôt épuisé sa réserve de nourriture." }
    { group:66, id:6, text: "Cette maison dispose de réserves de nourriture pour les mois à venir." }
    { group:66, id:7, text: "Cette maison n'a pas de mal à obtenir la nourriture dont elle a besoin." }
    { group:66, id:8, text: "Cette maison n'est pas desservie en eau potable." }
    { group:66, id:9, text: "Un porteur d'eau est passé récemment près de cette maison. Celle-ci dispose d'une réserve durable en eau potable." }
    { group:66, id:10, text: "Cette maison dispose de bonnes réserves en eau potable." }
    { group:66, id:11, text: "Cette maison a un besoin urgent en eau et nécessite la visite d'un porteur d'eau." }
    { group:66, id:12, text: "Cette maison n'a accès à aucun temple." }
    { group:66, id:13, text: "Cette maison a accès au temple d'une seule divinité." }
    { group:66, id:14, text: "Cette maison a accès aux temples de deux divinités." }
    { group:66, id:15, text: "Cette maison a accès aux temples de trois divinités." }
    { group:66, id:16, text: "Cette maison a accès aux temples de quatre divinités." }
    { group:66, id:17, text: "Cette maison a accès aux temples de toutes les divinités." }
    { group:66, id:18, text: "Cette maison a accès à un sanctuaire et aux temples de toutes les divinités." }
    { group:66, id:46, text: "Ce bâtiment ne risque pas de prendre feu." }
    { group:66, id:47, text: "Ce bâtiment présente un faible risque d'incendie." }
    { group:66, id:48, text: "Ce bâtiment pourrait éventuellement prendre feu." }
    { group:66, id:49, text: "Ce bâtiment risque de prendre feu." }
    { group:66, id:50, text: "Ce bâtiment est très susceptible de prendre feu." }
    { group:66, id:51, text: "Ce bâtiment risque de prendre feu très prochainement !" }
    { group:66, id:58, text: "Ce quartier est très respectueux des lois, et aucun crime n'y a été signalé." }
    { group:66, id:59, text: "Ce secteur ne souffre que d'une criminalité occasionnelle." }
    { group:66, id:60, text: "Ce secteur n'est pas trop dangereux, mais certains habitants se sont plaints du manque de sécurité." }
    { group:66, id:61, text: "Quelques problèmes ont été signalés récemment dans ce secteur, mais globalement, le quartier est calme." }
    { group:66, id:62, text: "Ce secteur est dangereux. Les habitants sont mécontents, et les rues ne sont pas sûres la nuit." }
    { group:66, id:63, text: "Ce secteur est une véritable cour des miracles ! Le crime y est incontrôlable et la révolte gronde." }
    { group:66, id:83, text: "Cette maison n'a pas accès à un théâtre de danse." }
    { group:66, id:84, text: "Un danseur est passé récemment près de cette maison. Celle-ci dispose d'un accès durable aux théâtres de danse." }
    { group:66, id:85, text: "Cette maison a accès à un théâtre de danse." }
    { group:66, id:86, text: "Aucun danseur n'est passé près de cette maison depuis longtemps. Celle-ci perdra bientôt son accès aux théâtres de danse." }
    { group:66, id:91, text: "Aucun de vos citoyens ne désire vivre ici." }
    { group:66, id:92, text: "Vos citoyens ne sont pas particulièrement intéressés par ce secteur." }
    { group:66, id:93, text: "Ce secteur est très convoité." }
    { group:66, id:94, text: "Ce bâtiment n'a pour l'instant pas accès à de la main-d'œuvre." }
    { group:66, id:95, text: "Ce bâtiment n'a accès qu'à un minimum de main-d'œuvre." }
    { group:66, id:96, text: "Ce bâtiment a peu accès à de la main-d'œuvre." }
    { group:66, id:97, text: "Ce bâtiment a accès à de la main-d'œuvre." }
    { group:66, id:98, text: "Ce bâtiment a un bon accès à de la main-d'œuvre." }
    { group:66, id:99, text: "Ce bâtiment a un très bon accès à de la main-d'œuvre." }
    { group:66, id:104, text: "Les habitants de cette hutte en sont à fouiller dans les détritus..." }
    { group:66, id:105, text: "Cette terre est incroyablement fertile. Tout poussera en abondance." }
    { group:66, id:106, text: "Cette terre est assez fertile. Ici, les cultures seront saines." }
    { group:66, id:107, text: "Cette terre est assez peu fertile. Les cultures n'y atteindront pas tout leur potentiel." }
    { group:66, id:108, text: "Cette terre n'est pas très fertile. Les cultures seront rachitiques." }
    { group:66, id:109, text: "Cette terre est stérile. Rien ne poussera." }
    { group:66, id:110, text: "paniers de céréales sont engrangés dans ce bâtiment." }
    { group:66, id:111, text: "panier de céréales est engrangé dans ce bâtiment." }
    { group:66, id:112, text: "jarres de fruits sont engrangées dans ce bâtiment." }
    { group:66, id:113, text: "jarre de fruit est engrangée dans ce bâtiment." }
    { group:66, id:114, text: "jarres de légumes sont engrangées dans ce bâtiment." }
    { group:66, id:115, text: "jarre de légume est engrangée dans ce bâtiment." }
    { group:66, id:116, text: "unités de viande sont engrangées dans ce bâtiment." }
    { group:66, id:117, text: "unité de viande est engrangée dans ce bâtiment." }
    { group:66, id:118, text: "pièces de poterie sont engrangées dans ce bâtiment." }
    { group:66, id:119, text: "pièce de poterie est engrangée dans ce bâtiment." }
    { group:66, id:120, text: "sacs de bijoux (objets de luxe) sont engrangés dans ce bâtiment." }
    { group:66, id:121, text: "sac de bijoux (objets de luxe) est engrangé dans ce bâtiment." }
    { group:66, id:122, text: "rouleaux de toile en lin sont engrangés dans ce bâtiment." }
    { group:66, id:123, text: "rouleau de toile en lin est engrangé dans ce bâtiment." }
    { group:66, id:124, text: "bouteilles de bière sont engrangées dans ce bâtiment." }
    { group:66, id:125, text: "bouteille de bière est engrangée dans ce bâtiment." }
    { group:66, id:126, text: "Ce bâtiment n'est pas prévu pour le stockage des biens." }
    { group:66, id:136, text: "Ce bâtiment n'est pas dans une zone de malaria." }
    { group:66, id:137, text: "Ce bâtiment est à la limite d'une zone de malaria." }
    { group:66, id:138, text: "Ce bâtiment est dans une zone à risque de malaria." }
    { group:66, id:139, text: "Ce bâtiment est dans une zone de malaria." }
    { group:66, id:140, text: "Les habitants de ce bâtiment seront vite atteints par la malaria." }
    { group:66, id:141, text: "Cette maison présente les problèmes suivants:" }
    { group:66, id:142, text: "Cette industrie présente les problèmes suivants:" }
    { group:66, id:143, text: "Risque d'effondrement." }
    { group:66, id:144, text: "Risque d'incendie." }
    { group:66, id:145, text: "Insalubrité." }
    { group:66, id:146, text: "Libre." }
    { group:66, id:147, text: "Risque de malaria." }
    { group:66, id:148, text: "Maladie." }
    { group:66, id:149, text: "Criminalité." }
    { group:66, id:150, text: "Régression prochaine." }
    { group:66, id:151, text: "Manque de matières premières." }
    { group:66, id:152, text: "Pas de main-d'œuvre." }
    { group:66, id:153, text: "Main-d'œuvre peu nombreuse." }
    { group:66, id:154, text: "En réserve." }
    { group:66, id:155, text: "Pas d'accès à la main-d'œuvre." }
    { group:66, id:156, text: "Infection de grenouilles" }
    { group:66, id:157, text: "Personne n'habite ici." }
    { group:66, id:158, text: "Cette maison n'a pas accès à un palais de justice." }
    { group:66, id:159, text: "Cette maison a été récemment visitée par un magistrat. Elle aura bientôt accès à un palais de justice." }
    { group:66, id:160, text: "Cette maison a accès à un palais de justice." }
    { group:66, id:161, text: "Cette maison n'a pas été visitée par un magistrat depuis longtemps. Elle n'aura bientôt plus accès à un palais de justice." }
    { group:66, id:162, text: "Il s'agit d'un des pires endroits de la ville." }
    { group:66, id:163, text: "Personne ne choisirait d'habiter ici, mais il y a des endroits pires." }
    { group:66, id:164, text: "Les gens n'apprécient guère cet endroit." }
    { group:66, id:165, text: "Cet endroit est meilleur que d'autres, mais il n'est pas très attractif." }
    { group:66, id:166, text: "La plupart des gens apprécient cet endroit." }
    { group:66, id:167, text: "C'est l'une des adresses les plus en vogue de votre cité." }
    { group:66, id:168, text: "Cette maison n'a pas accès à un Zoo." }
    { group:66, id:169, text: "Cette maison a récemment été visitée par un gardien de Zoo. Elle bénéficiera d'un accès à un Zoo pendant longtemps." }
    { group:66, id:170, text: "Cette maison a accès à un Zoo." }
    { group:66, id:171, text: "Cette maison n'a pas été visitée par un gardien de Zoo depuis longtemps. Elle n'aura bientôt plus accès à un Zoo." }
    { group:66, id:172, text: "Cette maison est infestée de grenouilles." }
    { group:67, id:0, text: "Structures autorisées" }
    { group:67, id:1, text: "Matières premières" }
    { group:67, id:2, text: "Mine d'or" }
    { group:67, id:3, text: "Chadouf" }
    { group:67, id:4, text: "Rigole d'irrigation" }
    { group:67, id:5, text: "Quai" }
    { group:67, id:6, text: "Chantier" }
    { group:67, id:7, text: "Grenier" }
    { group:67, id:8, text: "Bazar" }
    { group:67, id:9, text: "Entrepôt" }
    { group:67, id:10, text: "Dock" }
    { group:67, id:11, text: "Jonglerie" }
    { group:67, id:12, text: "Musique" }
    { group:67, id:13, text: "Danse" }
    { group:67, id:14, text: "Jeux de senet" }
    { group:67, id:15, text: "Place des fêtes" }
    { group:67, id:16, text: "Ecole de scribes" }
    { group:67, id:17, text: "Bibliothèque" }
    { group:67, id:18, text: "Point d'eau" }
    { group:67, id:19, text: "Dentiste" }
    { group:67, id:20, text: "Pharmacie" }
    { group:67, id:21, text: "Médecin" }
    { group:67, id:22, text: "Salle des embaumeurs" }
    { group:67, id:23, text: "Percepteur" }
    { group:67, id:24, text: "Palais de justice" }
    { group:67, id:25, text: "Palais" }
    { group:67, id:26, text: "Demeure" }
    { group:67, id:27, text: "Barrage routier" }
    { group:67, id:28, text: "Pont" }
    { group:67, id:29, text: "Embarcadère" }
    { group:67, id:30, text: "Jardins" }
    { group:67, id:31, text: "Plaza" }
    { group:67, id:32, text: "Statue" }
    { group:67, id:33, text: "Mur" }
    { group:67, id:34, text: "Tour" }
    { group:67, id:35, text: "Corps de garde" }
    { group:67, id:36, text: "Centre de recrutement" }
    { group:67, id:37, text: "Fort: Fantassins" }
    { group:67, id:38, text: "Fort: Archers" }
    { group:67, id:39, text: "Fort: Chars" }
    { group:67, id:40, text: "Académie" }
    { group:67, id:41, text: "Fabrique d'armes" }
    { group:67, id:42, text: "Fabrique de chars" }
    { group:67, id:43, text: "Quai: navires de guerre" }
    { group:67, id:44, text: "Quai: transporteurs" }
    { group:67, id:45, text: "Zoo" }
    { group:68, id:0, text: "Texte des bulles d'aide" }
    { group:68, id:1, text: "Afficher l'écran d'aide correspondant à ce panneau" }
    { group:68, id:2, text: "Quitter ce panneau" }
    { group:68, id:3, text: "Charger cet enregistrement" }
    { group:68, id:4, text: "Enregistrer votre partie vers ce fichier" }
    { group:68, id:5, text: "Annuler cette opération." }
    { group:68, id:6, text: "Faire défiler la liste des enregistrements" }
    { group:68, id:7, text: "Cliquez sur un nom de fichier pour le sélectionner" }
    { group:68, id:8, text: "mouse help free" }
    { group:68, id:9, text: "mouse help free" }
    { group:68, id:10, text: "Cacher l'interface afin d'agrandir la zone de jeu" }
    { group:68, id:11, text: "Sélectionner le type de carte à visualiser" }
    { group:68, id:12, text: "Afficher l'interface" }
    { group:68, id:13, text: "Charger cette partie" }
    { group:68, id:14, text: "Enregistrer votre partie vers ce fichier" }
    { group:68, id:15, text: "Annuler cette opération." }
    { group:68, id:16, text: "Faire défiler les missions" }
    { group:68, id:17, text: "Cliquez sur un nom de fichier pour le sélectionner" }
    { group:68, id:18, text: "mouse help free" }
    { group:68, id:19, text: "mouse help free" }
    { group:68, id:20, text: "Construire des logements" }
    { group:68, id:21, text: "Construire des routes" }
    { group:68, id:22, text: "Dégager le terrain" }
    { group:68, id:23, text: "Agriculture et structures alimentaires" }
    { group:68, id:24, text: "Structures industrielles" }
    { group:68, id:25, text: "Structures de stockage et de distribution" }
    { group:68, id:26, text: "Structures de divertissement" }
    { group:68, id:27, text: "Structures religieuses" }
    { group:68, id:28, text: "Structures en rapport avec l'éducation" }
    { group:68, id:29, text: "Structures sanitaires et d'hygiène" }
    { group:68, id:30, text: "Structures municipales" }
    { group:68, id:31, text: "Structures militaires" }
    { group:68, id:32, text: "ANNULER votre dernière action (seulement si l'icône est disponible)" }
    { group:68, id:33, text: "Afficher les messages" }
    { group:68, id:34, text: "Faire défiler les zones de troubles de la cité" }
    { group:68, id:35, text: "Revoir votre mission" }
    { group:68, id:36, text: "Cliquez sur cette carte pour vous déplacer rapidement dans la cité" }
    { group:68, id:37, text: "mouse help free" }
    { group:68, id:38, text: "mouse help free" }
    { group:68, id:39, text: "mouse help free" }
    { group:68, id:40, text: "mouse help free" }
    { group:68, id:41, text: "Consulter vos chefs" }
    { group:68, id:42, text: "Afficher la mappemonde" }
    { group:68, id:43, text: "Revoir votre mission" }
    { group:68, id:44, text: "Réorienter la vue vers le Nord" }
    { group:68, id:45, text: "Tourner la vue dans le sens des aiguilles d'une montre" }
    { group:68, id:46, text: "Tourner la vue vers la gauche" }
    { group:68, id:47, text: "mouse help free" }
    { group:68, id:48, text: "mouse help free" }
    { group:68, id:49, text: "mouse help free" }
    { group:68, id:50, text: "mouse help free" }
    { group:68, id:52, text: "Options de son et de vitesse" }
    { group:68, id:53, text: "Accéder à l'aide du jeu" }
    { group:68, id:54, text: "Consulter les différents rapports de vos chefs" }
    { group:68, id:55, text: "mouse help free" }
    { group:68, id:56, text: "mouse help free" }
    { group:68, id:57, text: "mouse help free" }
    { group:68, id:58, text: "mouse help free" }
    { group:68, id:59, text: "mouse help free" }
    { group:68, id:60, text: "mouse help free" }
    { group:68, id:64, text: "mouse help free" }
    { group:68, id:65, text: "mouse help free" }
    { group:68, id:66, text: "mouse help free" }
    { group:68, id:67, text: "mouse help free" }
    { group:68, id:68, text: "mouse help free" }
    { group:68, id:69, text: "mouse help free" }
    { group:68, id:70, text: "Consulter le chef du commerce" }
    { group:68, id:71, text: "Consulter le chef de la main-d'œuvre" }
    { group:68, id:72, text: "Consulter votre chef militaire" }
    { group:68, id:73, text: "Consulter le chef politique" }
    { group:68, id:74, text: "Consulter le chef des niveaux" }
    { group:68, id:75, text: "Consulter le chef du commerce" }
    { group:68, id:76, text: "Consulter le chef de la nourriture" }
    { group:68, id:77, text: "Consulter le chef de l'hygiène" }
    { group:68, id:78, text: "Consulter le chef de l'éducation" }
    { group:68, id:79, text: "Consulter le chef des loisirs" }
    { group:68, id:80, text: "Consulter le chef des temples" }
    { group:68, id:81, text: "Consulter le chef des finances" }
    { group:68, id:82, text: "Consulter le responsable" }
    { group:68, id:83, text: "Consulter le chef des monuments" }
    { group:68, id:84, text: "Retourner à la vue principale de la cité" }
    { group:68, id:85, text: "mouse help free" }
    { group:68, id:86, text: "mouse help free" }
    { group:68, id:87, text: "mouse help free" }
    { group:68, id:88, text: "mouse help free" }
    { group:68, id:89, text: "mouse help free" }
    { group:68, id:90, text: "mouse help free" }
    { group:68, id:91, text: "mouse help free" }
    { group:68, id:92, text: "Fixer le niveau de priorité d'une catégorie de tâches" }
    { group:68, id:93, text: "Fixez le salaire annuel pour 10 ouvriers" }
    { group:68, id:94, text: "Cliquez ici pour annuler la priorité de cette tâche" }
    { group:68, id:95, text: "Cliquez sur un chiffre pour fixer le niveau  de priorité. Les priorités des autres tâches seront réajustées en fonction" }
    { group:68, id:96, text: "Cliquez ici pour faire un don d'argent à la cité" }
    { group:68, id:97, text: "Cliquez ici pour fixer votre salaire personnel" }
    { group:68, id:98, text: "Quitter l'écran de salaire" }
    { group:68, id:99, text: "Sélectionner ce niveau de salaire" }
    { group:68, id:100, text: "Quitter l'écran des donations" }
    { group:68, id:101, text: "Faire don de cette somme à la cité" }
    { group:68, id:102, text: "Fixer le montant du don." }
    { group:68, id:103, text: "Ajuster le montant de la donation" }
    { group:68, id:104, text: "Obtenir des conseils sur le niveau de culture" }
    { group:68, id:105, text: "Obtenir des conseils sur le niveau de prospérité" }
    { group:68, id:106, text: "Obtenir des conseils sur le niveau architectural" }
    { group:68, id:107, text: "Obtenir des conseils sur le niveau du royaume" }
    { group:68, id:108, text: "Affiche les prix de tous les biens" }
    { group:68, id:109, text: "Cliquez ici pour obtenir un bilan de cette industrie" }
    { group:68, id:110, text: "Fixez la quantité produite de ce bien à partir de laquelle vous désirez commencer son exportation." }
    { group:68, id:111, text: "Activer ou désactiver ce type de production pour toute la cité" }
    { group:68, id:112, text: "Ajuster le statut d'échange de cet article" }
    { group:68, id:113, text: "Sélectionner ce graphique" }
    { group:68, id:114, text: "Informations sur les fêtes" }
    { group:68, id:115, text: "Préparer une fête en l'honneur de ce dieu" }
    { group:68, id:116, text: "Ne pas organiser de fête" }
    { group:68, id:117, text: "Dédier une fête à Osiris" }
    { group:68, id:118, text: "Dédier une fête à Rê" }
    { group:68, id:119, text: "Dédier une fête à Ptah" }
    { group:68, id:120, text: "Dédier une fête à Seth" }
    { group:68, id:121, text: "Dédier une fête à Bastet" }
    { group:68, id:122, text: "Ajuster le taux d'imposition de la cité" }
    { group:68, id:123, text: "Cliquez ici pour parler à cette personne" }
    { group:68, id:124, text: "Informations détaillées sur cette maison" }
    { group:68, id:125, text: "Faire défiler les messages" }
    { group:68, id:126, text: "Message lu précédent. @L Cliquez sur ce message pour le lire. @L Cliquez droit pour l'effacer" }
    { group:68, id:127, text: "Message non lu. @L Cliquez sur ce message pour le lire. @L Cliquez droit pour l'effacer" }
    { group:68, id:128, text: "Retour à l'écran d'aide précédent" }
    { group:68, id:129, text: "Quitter l'aide de Pharaon" }
    { group:68, id:130, text: "Faire défiler l'aide sur ce sujet" }
    { group:68, id:131, text: "Supprimer ce message" }
    { group:68, id:132, text: "Cliquez ici pour aller dans cette zone de troubles" }
    { group:68, id:133, text: "Faire une offrande pour l'Egypte" }
    { group:68, id:134, text: "Cliquez ici pour changer la formation de la compagnie" }
    { group:68, id:135, text: "Chômage" }
    { group:68, id:140, text: "Cliquez ici pour donner des ordres au transporteur" }
    { group:68, id:141, text: "Cliquez ici pour donner des ordres au navire de guerre" }
    { group:68, id:142, text: "Taux d'imposition" }
    { group:68, id:143, text: "Consulter l'état des troupes" }
    { group:68, id:144, text: "Consulter l'état de la flotte" }
    { group:68, id:145, text: "Aller à la carte du royaume" }
    { group:68, id:146, text: "Définir les critères de mission" }
    { group:68, id:147, text: "Terrain vague" }
    { group:68, id:148, text: "Arbres" }
    { group:68, id:149, text: "Eau et marécages" }
    { group:68, id:150, text: "Prairie" }
    { group:68, id:151, text: "Route" }
    { group:68, id:152, text: "Rochers et dunes" }
    { group:68, id:153, text: "Points de rivière" }
    { group:68, id:154, text: "Points d'invasion" }
    { group:68, id:155, text: "Points de peuple" }
    { group:68, id:156, text: "Points d'animaux" }
    { group:68, id:157, text: "Pinceaux" }
    { group:68, id:158, text: "Ajouter une ville, une région ou un graphique" }
    { group:68, id:159, text: "Modifier la ville, la région ou le graphique" }
    { group:68, id:160, text: "Supprimer une ville, une région ou un graphique" }
    { group:68, id:161, text: "Afficher le menu principal" }
    { group:68, id:162, text: "Ajouter une route commerciale ou d'invasion" }
    { group:68, id:163, text: "Modifier la route commerciale ou d'invasion" }
    { group:68, id:164, text: "Restaurer la carte par défaut" }
    { group:68, id:165, text: "Retourner dans la vue régionale" }
    { group:68, id:166, text: "Ajuster les prix des importations et des exportations" }
    { group:68, id:167, text: "Ajuster le rang, le budget, la date de début et le pharaon actuel" }
    { group:68, id:168, text: "Parcourir les options climatiques" }
    { group:68, id:169, text: "Planifier les événements" }
    { group:68, id:170, text: "Choisir un ennemi" }
    { group:68, id:171, text: "Définir les dieux" }
    { group:68, id:172, text: "Désigner les bâtiments disponibles" }
    { group:68, id:173, text: "Définir les spécifications des niveaux et choisir les monuments" }
    { group:68, id:174, text: "Déterminer la durée et la qualité de l'inondation" }
    { group:68, id:175, text: "Pivoter la vue" }
    { group:68, id:176, text: "Modifier le graphique" }
    { group:68, id:177, text: "Types de prédateurs" }
    { group:68, id:178, text: "Ere des monuments" }
    { group:69, id:0, text: "requis)" }
    { group:69, id:1, text: "Efficacité" }
    { group:69, id:2, text: "Aucun risque d'effondrement" }
    { group:69, id:3, text: "Très léger risque d'effondrement" }
    { group:69, id:4, text: "Léger risque d'effondrement" }
    { group:69, id:5, text: "Risque d'effondrement" }
    { group:69, id:6, text: "Haut risque d'effondrement" }
    { group:69, id:7, text: "Très haut risque d'effondrement" }
    { group:69, id:8, text: "Effondrement imminent" }
    { group:69, id:9, text: "Aucun risque d'incendie" }
    { group:69, id:10, text: "Très léger risque d'incendie" }
    { group:69, id:11, text: "Léger risque d'incendie" }
    { group:69, id:12, text: "Risque d'incendie" }
    { group:69, id:13, text: "Haut risque d'incendie" }
    { group:69, id:14, text: "Très haut risque d'incendie" }
    { group:69, id:15, text: "Menace d'incendie à court terme" }
    { group:69, id:21, text: "Fonctionne à peine. Allouez plus de main-d'œuvre à ce secteur" }
    { group:69, id:22, text: "Fonctionne mal. Allouez plus de main-d'œuvre à ce secteur" }
    { group:69, id:23, text: "Fonctionne bien, mais plus de main-d'œuvre pourrait être allouée à ce secteur" }
    { group:69, id:24, text: "Fonctionne à capacité réduite. Trop peu d'employés se sont présentés dernièrement." }
    { group:69, id:26, text: "Manque de personnel. Seule la distribution de biens peut être effectuée, pas le stockage." }
    { group:69, id:27, text: "Personnel insuffisant. Impossible de distribuer ou de stocker des biens." }
    { group:70, id:0, text: "Il n'y a personne par ici." }
    { group:70, id:1, text: "Free" }
    { group:70, id:2, text: "Free" }
    { group:70, id:3, text: "Free" }
    { group:70, id:4, text: "Free" }
    { group:70, id:5, text: "Free" }
    { group:70, id:6, text: "Free" }
    { group:70, id:7, text: "Free" }
    { group:70, id:8, text: "Free" }
    { group:70, id:9, text: "Free" }
    { group:70, id:10, text: "Rien" }
    { group:70, id:11, text: "Arbres et bosquets" }
    { group:70, id:12, text: "Rochers" }
    { group:70, id:13, text: "Eau" }
    { group:70, id:14, text: "Arbres" }
    { group:70, id:15, text: "Faille" }
    { group:70, id:16, text: "Route" }
    { group:70, id:17, text: "Rigole d'irrigation" }
    { group:70, id:18, text: "Gravats d'un bâtiment détruit" }
    { group:70, id:19, text: "Mur" }
    { group:70, id:20, text: "Terre en friche" }
    { group:70, id:21, text: "Pont" }
    { group:70, id:22, text: "Jardins" }
    { group:70, id:23, text: "Plaza" }
    { group:70, id:24, text: "A la capitale" }
    { group:70, id:25, text: "Au royaume" }
    { group:70, id:26, text: "Roche contenant du minerai" }
    { group:70, id:27, text: "Roche normale" }
    { group:70, id:28, text: "Roche spéciale" }
    { group:70, id:29, text: "Plaine d'inondation" }
    { group:70, id:30, text: "Plaine inondée" }
    { group:70, id:31, text: "Marécage" }
    { group:70, id:32, text: "Dunes de sable" }
    { group:70, id:33, text: "Mur de briques" }
    { group:70, id:34, text: "Mur" }
    { group:70, id:35, text: "Prairie" }
    { group:70, id:36, text: "Falaises" }
    { group:70, id:37, text: "Il faut abattre les arbres pour passer. Ils sont indispensables pour l'industrie du bois et les chantiers de bois doivent être placés près d'arbres. Les arbres se renouvellent d'eux-mêmes au cours du temps." }
    { group:70, id:38, text: "Les rochers sont infranchissables et ne peuvent pas être déblayés. Avec un peu de chance, ce sera du calcaire, du grès ou du granit ; mais il peut aussi s'agir de cailloux sans valeur. Vérifiez vos ressources." }
    { group:70, id:39, text: "Les bateaux naviguent sur l'eau, les navettes et les ponts permettent de traverser certains points. Grâce aux docks, les voies d'eau sont de grandes routes. Les puits d'argile doivent être près de l'eau." }
    { group:70, id:40, text: "Terrain infranchissable, peut être dégagé si nécessaire. Les chantiers de bois doivent être installés à proximité d'une forêt." }
    { group:70, id:41, text: "Ces crevasses ont été causées par un tremblement de terre. Elles sont infranchissables et les gens préfèrent ne pas vivre à proximité." }
    { group:70, id:42, text: "Les routes sont vitales au bon fonctionnement de la cité, car ses habitants ne s'aventureront pas à l'extérieur s'il n'y a pas de route." }
    { group:70, id:43, text: "Les rigoles d'irrigation permettent d'améliorer la fertilité des exploitations situées à proximité." }
    { group:70, id:44, text: "Ces débris d'un ancien bâtiment réduisent l'attrait des terrains à proximité." }
    { group:70, id:45, text: "Les murs protègent les citoyens sans défenses contre les razzias et les envahisseurs. Leur résistance n'est pas éternelle. Les murs plus épais résistent mieux." }
    { group:70, id:46, text: "Ce terrain est constructible et permet le passage des soldats alliés, mais aussi des ennemis !" }
    { group:70, id:47, text: "Ce pont agrandit nos terres et permet le passage de nos ennemis !" }
    { group:70, id:48, text: "Les jardins améliorent l'attrait du quartier." }
    { group:70, id:49, text: "Les gens préfèrent les plazas !" }
    { group:70, id:50, text: "Cette route nous relie au reste de l'Egypte et doit rester ouverte pour attirer les immigrants et les marchands dans notre cité." }
    { group:70, id:51, text: "Cette route va jusqu'aux confins du royaume. Il s'agit d'une voie royale et, en tant que telle, la liberté de circulation doit être garantie." }
    { group:70, id:52, text: "Cette roche est porteuse de minerai. Outre les pierres de construction et les pierres précieuses, extrayez de l'or ou du cuivre de ces roches, en fonction des ressources de votre cité." }
    { group:70, id:53, text: "Il s'agit d'une roche normale. Selon les ressources de votre cité, extrayez des pierres de construction, voire des pierres précieuses." }
    { group:70, id:54, text: "Il s'agit d'une roche spéciale.  Blah blah blah... (this text should not appear anywhere)" }
    { group:70, id:55, text: "Cette zone offre des terres extrêmement fertiles après la décrue." }
    { group:70, id:56, text: "Cette zone offrira des terres extrêmement fertiles après la décrue." }
    { group:70, id:57, text: "Les zones marécageuses ne permettent pas de construire. Elles peuvent cependant être traversées par des citoyens prudents. Vous y trouverez des roseaux, mais attention aux crocodiles !" }
    { group:70, id:58, text: "Les sables mouvants ne permettent pas de construire. Ils peuvent cependant être traversés par des citoyens prudents." }
    { group:70, id:59, text: "Il s'agit d'un mur de briques. Ce mur retiendra les envahisseurs plus longtemps qu'un mur de terre, mais ne remplace pas une compagnie de soldats entraînés !" }
    { group:70, id:60, text: "Il s'agit d'un mur de terre simple. Ce mur ralentira les envahisseurs, mais ne constitue pas une défense efficace." }
    { group:70, id:61, text: "Cette terre est propice à toutes sortes de cultures. Plus les fleurs sont luxuriantes, plus la terre est fertile." }
    { group:70, id:62, text: "Ces falaises abruptes sont idéales pour construire certains monuments. Personne ne peut les franchir, ni en extraire quoi que ce soit." }
    { group:71, id:0, text: "Kiosque" }
    { group:71, id:1, text: "Les gens viennent ici pour regarder les jongleurs et écouter de la musique." }
    { group:71, id:2, text: "Cette place n'est jamais utilisée pour des représentations. Elle nécessite la présence de jongleurs et de musiciens." }
    { group:71, id:3, text: "Cette place offre à la communauté des spectacles de jongleurs audacieux et de musiciens locaux." }
    { group:71, id:4, text: "Les musiciens offrent un divertissement à la communauté locale sur cette place. Des jongleurs sont recherchés pour présenter divers spectacles." }
    { group:71, id:5, text: "Des jongleurs sont sur la place. L'audience serait encore plus satisfaite s'il y avait des musiciens." }
    { group:71, id:6, text: "Cette place est morte. La communauté locale ne dispose d'aucun divertissement." }
    { group:71, id:7, text: "Il n'y a pas de musique" }
    { group:71, id:8, text: "Les musiciens joueront encore pendant" }
    { group:71, id:9, text: "Les jongleurs sont inactifs" }
    { group:71, id:10, text: "Le spectacle des jongleurs durera encore" }
    { group:72, id:0, text: "Etal" }
    { group:72, id:1, text: "Les citoyens aiment regarder les jongleurs et divers autres menus spectacles." }
    { group:72, id:2, text: "Cette place n'est jamais utilisée pour des représentations. Elle nécessite la présence de vrais jongleurs." }
    { group:72, id:3, text: "Des jongleurs locaux présentent des spectacles sur cette place, ce qui attire normalement une audience nombreuse." }
    { group:72, id:4, text: "Hormis la brise, rien ne bouge sur cette place. Vous devez employer des artistes pour bénéficier de spectacles." }
    { group:72, id:5, text: "Les jongleurs sont inactifs" }
    { group:72, id:6, text: "Le spectacle actuel va encore durer" }
    { group:72, id:7, text: "Spectacle : 'Jonglerie du Grand Mephisto' par Mephisto" }
    { group:72, id:8, text: "Spectacle : 'Les sables du temps' par Ironrodhotep" }
    { group:72, id:9, text: "Spectacle : 'Rivière de larmes' par Waseth" }
    { group:72, id:10, text: "Spectacle : 'La pyramide de 10 000 Deben' par Desenseth" }
    { group:72, id:11, text: "Spectacle : 'Crocodile Roc' par El-Tone Djone" }
    { group:73, id:0, text: "Taverne de jeux" }
    { group:73, id:1, text: "Les jeux d'adresse et de hasard ajoutent un peu de piquant à la vie de tous les jours." }
    { group:73, id:2, text: "Des joueurs sont attablés dans cette taverne de jeux. Apportez de la bière pour animer le jeu." }
    { group:73, id:3, text: "Cette taverne abrite constamment des jeux, au plus grand plaisir de la population locale." }
    { group:73, id:4, text: "Personne ne fréquente cette taverne de jeux. La communauté locale ne bénéficie d'aucun divertissement en l'absence d'employés." }
    { group:73, id:5, text: "Aucun jeu en cours" }
    { group:73, id:6, text: "Les jeux vont encore durer" }
    { group:73, id:7, text: "Bière entreposée," }
    { group:74, id:0, text: "Pavillon" }
    { group:74, id:1, text: "Les danseurs, les musiciens et les jongleurs offrent des divertissements très prisés par tout le monde." }
    { group:74, id:2, text: "Aucune représentation n'a lieu sur cette place. Il faut des danseurs, des musiciens et des jongleurs pour attirer la foule." }
    { group:74, id:3, text: "Cette place abrite des danses somptueuses, des musiciens sublimes et des jongleurs espiègles qui ravissent la communauté locale." }
    { group:74, id:4, text: "Cette place abrite des danseurs et des musiciens pour vos citoyens. Des jongleurs ajouteraient une note de variété." }
    { group:74, id:5, text: "Cette place abrite des danseurs et des jongleurs. Engagez des musiciens pour compléter le spectacle." }
    { group:74, id:6, text: "Cette place abrite des musiciens et des jongleurs, mais pour accompagner la musique, il faudrait des danseurs." }
    { group:74, id:7, text: "Cette place abrite des jongleurs. Engagez des musiciens et des danseurs pour remplir les estrades." }
    { group:74, id:8, text: "Cette place abrite des musiciens, mais ni jongleurs ni danseurs." }
    { group:74, id:9, text: "Cette place abrite des danseurs, mais ni jongleurs ni musiciens." }
    { group:74, id:10, text: "Cette place est fermée. En l'absence d'employés, elle n'offre aucun divertissement." }
    { group:74, id:11, text: "Les jongleurs sont inactifs" }
    { group:74, id:12, text: "Le spectacle des jongleurs durera encore" }
    { group:74, id:13, text: "Aucun concert" }
    { group:74, id:14, text: "La musique va encore durer" }
    { group:74, id:15, text: "Aucun danseur actif" }
    { group:74, id:16, text: "Les danses vont encore durer" }
    { group:75, id:0, text: "Conservatoire" }
    { group:75, id:1, text: "Les Egyptiens aiment les concerts interprétés par de nouveaux musiciens." }
    { group:75, id:2, text: "Nous avons le plaisir d'annoncer que, grâce au plein emploi, nous formons jusqu'à quatre nouveaux musiciens par mois." }
    { group:75, id:3, text: "Nous manquons de personnel et ne pouvons former que deux nouveaux musiciens par mois." }
    { group:75, id:4, text: "La moitié de notre personnel est absent, nous ne pourrons former qu'un seul musicien au cours du mois à venir." }
    { group:75, id:5, text: "Nous avons désespérément besoin de personnel et allons nous efforcer de former un musicien au cours des deux mois à venir." }
    { group:75, id:6, text: "Je suis le seul membre du personnel. Je ne peux pas travailler dans ces conditions ! Je peux former tout au plus un musicien en trois mois." }
    { group:75, id:7, text: "En l'absence de personnel, cette école ne peut pas former de nouveaux musiciens." }
    { group:76, id:0, text: "Ecole de danse" }
    { group:76, id:1, text: "Les danseurs émerveillent leurs audiences avec leurs mouvements gracieux et sensuels." }
    { group:76, id:2, text: "Nous avons le plaisir d'annoncer que, grâce au plein emploi, nous formons jusqu'à quatre nouveaux danseurs par mois." }
    { group:76, id:3, text: "Nous manquons de personnel et ne pouvons former que deux nouveaux danseurs par mois." }
    { group:76, id:4, text: "La moitié de notre personnel est absent, nous ne pourrons former qu'un seul danseur au cours du mois à venir." }
    { group:76, id:5, text: "Nous avons désespérément besoin de personnel et allons nous efforcer de former un danseur au cours des deux mois à venir." }
    { group:76, id:6, text: "Je suis le seul membre du personnel. Je ne peux pas travailler dans ces conditions ! Je peux former tout au plus un danseur en trois mois." }
    { group:76, id:7, text: "En l'absence d'instructeurs, cette école ne pourra plus former de danseurs." }
    { group:77, id:0, text: "Ecole de jonglerie" }
    { group:77, id:1, text: "De nouveaux jongleurs avec de nouveaux numéros sont toujours très demandés." }
    { group:77, id:2, text: "Nous avons le plaisir d'annoncer que, grâce au plein emploi, nous formons jusqu'à quatre nouveaux jongleurs par mois." }
    { group:77, id:3, text: "Nous manquons de personnel et ne pouvons former que deux nouveaux jongleurs par mois." }
    { group:77, id:4, text: "La moitié de notre personnel est absent, nous ne pourrons former qu'un seul jongleur au cours du mois à venir." }
    { group:77, id:5, text: "Nous avons désespérément besoin d'employés. Il va être difficile de former un nouveau jongleur au cours des deux mois à venir." }
    { group:77, id:6, text: "Je suis le seul membre du personnel. Je ne peux pas travailler dans ces conditions ! Je peux former tout au plus un jongleur en trois mois." }
    { group:77, id:7, text: "Cette école a été désertée. En l'absence de mentors, il est impossible de former des jongleurs." }
    { group:78, id:0, text: "Maîtres de senet" }
    { group:78, id:1, text: "Les maîtres stratèges qui travaillent ici, forment des maîtres de senet pour diriger des tavernes de jeux toujours plus populaires." }
    { group:78, id:2, text: "Nous avons le plaisir d'annoncer que, grâce au plein emploi, nous formons jusqu'à quatre nouveaux maîtres de senet par mois." }
    { group:78, id:3, text: "Nous manquons de personnel et ne pouvons former que deux nouveaux maîtres de senet par mois." }
    { group:78, id:4, text: "La moitié de notre personnel est absent, nous ne pourrons former qu'un seul maître de senet au cours du mois à venir." }
    { group:78, id:5, text: "Nous avons désespérément besoin de personnel et allons nous efforcer de former un maître de senet au cours des deux mois à venir." }
    { group:78, id:6, text: "Je suis le seul membre du personnel. Je ne peux pas travailler dans ces conditions !  Je peux former tout au plus un maître de senet en trois mois." }
    { group:78, id:7, text: "En l'absence de professeurs, aucun nouveau maître de senet ne sera formé. Les tavernes de jeux risquent d'en souffrir." }
    { group:79, id:0, text: "Jardins" }
    { group:80, id:0, text: "Statue" }
    { group:80, id:1, text: "Les monuments dédiés aux divinités et aux pharaons d'autrefois participent au prestige d'un quartier. Les citoyens sont fiers d'habiter près de statues et plus elles sont imposantes, mieux c'est." }
    { group:80, id:2, text: "Arc de Triomphe" }
    { group:80, id:3, text: "Ce superbe édifice commémore les victoires de l'Egypte sur ses ennemis. On ne fait pas plus prestigieux." }
    { group:81, id:0, text: "Pharmacie" }
    { group:81, id:1, text: "Les pharmacies permettent d'améliorer la santé des citoyens en offrant un service à domicile. Les zones favorisées exigent une pharmacie." }
    { group:81, id:2, text: "Cette pharmacie n'est pas opérationnelle. Elle n'est donc d'aucune utilité pour vos citoyens." }
    { group:81, id:3, text: "Cette pharmacie est opérationnelle et fournit potions et onguents à vos citoyens." }
    { group:82, id:0, text: "Salle des embaumeurs" }
    { group:82, id:1, text: "Personne n'aime habiter près d'une salle des embaumeurs. Cependant, ces salles permettent de sauver des vies en période d'épidémie. La cité doit disposer de lieux d'embaumement pour tous ses morts." }
    { group:82, id:2, text: "Cette salle des embaumeurs n'est pas opérationnelle. Elle n'est donc d'aucune utilité pour vos citoyens." }
    { group:82, id:3, text: "Cette salle des embaumeurs est opérationnelle et momifie les défunts de manière rapide et professionnelle." }
    { group:82, id:4, text: "Sans toile, nous ne pouvons pas apprêter les morts pour leur voyage dans l'au-delà." }
    { group:83, id:0, text: "Médecin" }
    { group:83, id:1, text: "Restez en bonne santé, mangez des grenades. Les médecins améliorent le niveau de santé." }
    { group:83, id:2, text: "Ce dispensaire n'est pas opérationnel." }
    { group:83, id:3, text: "Ce dispensaire est opérationnel et vos citoyens sont en pleine forme." }
    { group:84, id:0, text: "Dentiste" }
    { group:84, id:1, text: "Le sable s'infiltre partout, y compris dans les aliments. L'érosion constante ne facilite pas la tâche des dentistes égyptiens." }
    { group:84, id:2, text: "Ce cabinet dentaire n'est pas opérationnel. Il n'est donc d'aucune utilité pour vos citoyens." }
    { group:84, id:3, text: "Ce cabinet dentaire est opérationnel, et les dents de vos citoyens brillent comme des lapis-lazuli." }
    { group:85, id:0, text: "Ecole de scribes" }
    { group:85, id:1, text: "Les enfants des familles riches doivent fréquenter les écoles du voisinage pour apprendre à lire s'ils veulent atteindre le même statut que leurs parents." }
    { group:85, id:2, text: "Cette école n'est pas opérationnelle. Elle n'est donc d'aucune utilité pour vos citoyens." }
    { group:85, id:3, text: "Cette école est opérationnelle et éduque les enfants du quartier." }
    { group:86, id:0, text: "Gauche" }
    { group:86, id:1, text: "Haut" }
    { group:86, id:2, text: "Droite" }
    { group:86, id:3, text: "Bas" }
    { group:87, id:0, text: "Bibliothèque" }
    { group:87, id:1, text: "Toutes les œuvres littéraires du royaume sont stockées à cet endroit. Les érudits insistent sur le fait que les bibliothèques sont essentielles pour une cité importante." }
    { group:87, id:2, text: "Les étagères de cette bibliothèque sont vides. Elle n'est donc d'aucune utilité pour vos citoyens." }
    { group:87, id:3, text: "Cette bibliothèque est opérationnelle, et ses étagères sont pleines de manuscrits et de parchemins." }
    { group:88, id:0, text: "Poste de police" }
    { group:88, id:1, text: "Les agents, stationnés dans des postes de police, parcourent la cité et assurent l'ordre public. Pour cela, ils doivent patrouiller la cité de façon homogène." }
    { group:88, id:2, text: "Notre agent est parti en patrouille." }
    { group:88, id:3, text: "Notre agent se prépare." }
    { group:88, id:4, text: "Tous nos agents sont en patrouille. Nos agents sont toujours en action, veillant sur vos rues." }
    { group:88, id:5, text: "Nous manquons d'agents. Il se passe parfois un jour ou deux sans que personne ne soit envoyé en patrouille." }
    { group:88, id:6, text: "Nous manquons d'effectifs, et il se passe parfois une semaine sans que personne ne soit envoyé en patrouille." }
    { group:88, id:7, text: "Nous manquons cruellement d'hommes. Souvent, aucun agent ne patrouille pendant 1 ou 2 semaines." }
    { group:88, id:8, text: "Nous manquons d'employés. Il se passe souvent un mois entier sans qu'un agent ne soit envoyé en patrouille." }
    { group:88, id:9, text: "Sans employés, cette préfecture n'est que la risée des vandales de la cité." }
    { group:88, id:10, text: " vols cette année" }
    { group:88, id:11, text: " pièces d'or volées cette année" }
    { group:89, id:0, text: "Fort" }
    { group:89, id:1, text: "Ce fort a été maudit par Seth et il faudra attendre longtemps avant d'y revoir des soldats." }
    { group:89, id:2, text: "Les soldats du forts sont fournis par le centre de recrutement de la cité. L'ajout d'une académie permettrait d'obtenir des troupes mieux formées." }
    { group:90, id:0, text: "Corps de garde" }
    { group:90, id:1, text: "Les corps de garde permettent de surveiller le passage des citoyens et des marchands." }
    { group:91, id:0, text: "Tour" }
    { group:91, id:1, text: "Espacez les tours de vos murs à intervalles réguliers. Privilégiez les zones vulnérables. Dès lors que les tours sont reliées à des routes, le centre de recrutement vous enverra des gardes pour patrouiller les murs et lancer des javelots sur les envahisseurs." }
    { group:91, id:2, text: "Sans employés, nous ne pouvons ni stationner des gardes, ni patrouiller les murs d'enceinte." }
    { group:91, id:3, text: "Nos hommes sont prêts à repousser toute menace." }
    { group:91, id:4, text: "Nous disposons d'un personnel de maintenance, mais le centre de recrutement doit nous envoyer des gardes pour défendre la cité." }
    { group:92, id:0, text: "Temple d'Osiris (agriculture)" }
    { group:92, id:1, text: "Osiris accorde la fertilité à la terre et favorise la croissance des cultures. Apaisez-le ou préparez-vous à la disette." }
    { group:93, id:0, text: "Temple de Rê (royaume)" }
    { group:93, id:1, text: "Les marchands connaissent la valeur des faveurs de Rê. Le commerce est plus sûr et plus rentable sous la bénédiction de Rê, ce qui renforce l'estime envers votre cité." }
    { group:94, id:0, text: "Temple de Ptah (artisanat)" }
    { group:94, id:1, text: "Les ouvriers et les artisans vénèrent Ptah pour soulager leur labeur. Lorsque Ptah est en colère, aucune industrie n'est à l'abri de la catastrophe." }
    { group:95, id:0, text: "Temple de Seth (destruction)" }
    { group:95, id:1, text: "Seth protège les soldats et leur donne du courage au combat. Aucun homme n'est assez brave pour se battre sans la bénédiction de Seth." }
    { group:96, id:0, text: "Temple de Bastet (foyer)" }
    { group:96, id:1, text: "Si Bastet est mécontente, aucune maison n'est à l'abri de son courroux. Certaines personnes associent les maladies à Bastet." }
    { group:97, id:1, text: "Nos bazars mettent à la disposition des citoyens les trésors du royaume, contre argent sonnant et trébuchant. Toutes les maisons doivent avoir accès à un bazar, mais personne n'aime vivre trop près." }
    { group:97, id:2, text: "Ce bazar n'est pas opérationnel. Il n'est donc d'aucune utilité pour vos citoyens." }
    { group:97, id:3, text: "Ce bazar est opérationnel." }
    { group:97, id:4, text: "Des marchands sont arrivés sur le bazar et recherchent de la nourriture ou des biens à vendre." }
    { group:97, id:5, text: "Nourriture disponible pour" }
    { group:97, id:6, text: "Ordres spéciaux" }
    { group:97, id:7, text: "Instructions du bazar" }
    { group:97, id:8, text: "Acheter" }
    { group:97, id:9, text: "Ne pas acheter" }
    { group:97, id:10, text: "Le marchand de bazar est arrivé; il attend la nourriture." }
    { group:97, id:11, text: "Le marchand de bazar fait sa tournée de distribution." }
    { group:97, id:12, text: "Le marchand de bazar vient reconstituer ses stocks" }
    { group:98, id:1, text: "Il est vital d'avoir des greniers pleins pour nourrir correctement les citoyens et attirer des immigrants. Les greniers permettent de stocker n'importe quel type de nourriture." }
    { group:98, id:5, text: "Ordres spéciaux" }
    { group:98, id:6, text: "Instructions pour le grenier" }
    { group:98, id:7, text: "Vider le grenier" }
    { group:98, id:8, text: "Arrêter de vider le grenier" }
    { group:98, id:9, text: "Réexpédition des biens vers un autre lieu de stockage" }
    { group:99, id:0, text: "Entrepôt" }
    { group:99, id:1, text: "Les biens destinés au commerce nécessitent des entrepôts. Les caravanes achètent et vendent leurs biens dans les chantiers. Les biens chargés sur les docks proviennent également des entrepôts." }
    { group:99, id:2, text: "Ordres spéciaux" }
    { group:99, id:3, text: "Instructions pour l'entrepôt" }
    { group:99, id:4, text: "COMMENCER à vider l'entrepôt" }
    { group:99, id:5, text: "ARRETER de vider l'entrepôt" }
    { group:99, id:6, text: "Réexpédition des biens vers un autre lieu de stockage" }
    { group:99, id:7, text: "Refuser" }
    { group:99, id:8, text: "Refuser" }
    { group:99, id:9, text: "Va chercher les biens" }
    { group:99, id:10, text: "Va chercher la nourriture" }
    { group:99, id:11, text: "Centre de commerce" }
    { group:99, id:12, text: "Changer le centre de commerce" }
    { group:99, id:13, text: "ATTENTION Cet entrepôt est complet. Il est impossible d'y placer d'autres biens." }
    { group:99, id:14, text: "ATTENTION Cet entrepôt est presque complet. Vous ne pouvez y placer que les stocks existants." }
    { group:99, id:15, text: "Notre charrette est là, en attente de nouvelles instructions." }
    { group:99, id:16, text: "Notre charrette porte les marchandises ailleurs." }
    { group:99, id:17, text: "Notre charrette est de retour de livraison." }
    { group:99, id:18, text: "Accepter" }
    { group:99, id:19, text: "Remplir" }
    { group:99, id:20, text: "Vider nourriture" }
    { group:99, id:21, text: "Vider" }
    { group:99, id:22, text: "Cet entrepôt est vide." }
    { group:99, id:23, text: "bloc de" }
    { group:99, id:24, text: "blocs de" }
    { group:99, id:25, text: "1/4" }
    { group:99, id:26, text: "1/2" }
    { group:99, id:27, text: "3/4" }
    { group:99, id:28, text: "tout" }
    { group:99, id:29, text: "Entrepôt" }
    { group:99, id:30, text: "Grenier" }
    { group:99, id:31, text: "au maximum" }
    { group:99, id:32, text: "Remplir" }
    { group:99, id:33, text: "Notre charretier est en quête de marchandises" }
    { group:100, id:0, text: "Fabrique de bateaux" }
    { group:100, id:1, text: "Avec suffisamment d'ouvriers, la fabrique de bateaux peut produire toutes sortes de bateaux pour les quais de la cité." }
    { group:100, id:2, text: "Production à" }
    { group:100, id:3, text: "terminée." }
    { group:100, id:4, text: "Aucun quai ne demande nos bateaux." }
    { group:100, id:5, text: "Nous construisons un bateau sur demande de l'un des quais de la cité." }
    { group:100, id:6, text: "Nous radoubons un bateau." }
    { group:100, id:7, text: "Bois stocké," }
    { group:100, id:8, text: "Nous avons besoin de bois pour radouber et construire des bateaux." }
    { group:100, id:9, text: "Nous n'avons pas assez de bois pour terminer le bateau commandé par l'un des quais de la cité." }
    { group:100, id:10, text: "Plusieurs bateaux sont en réparation, mais nous manquons de bois." }
    { group:101, id:0, text: "Dock" }
    { group:101, id:1, text: "Des navires marchands en provenance du monde entier viennent s'amarrer ici pour livrer les biens importés et charger les biens à exporter. Le commerce outre-mer est impossible sans docks." }
    { group:101, id:2, text: "Nous ne pouvons pas nous occuper du navire qui vient d'accoster car aucun docker n'est employé ici." }
    { group:101, id:3, text: "Nous nous occupons du navire à quai, mais cela risque d'être long car nous sommes peu nombreux." }
    { group:101, id:4, text: "Nous nous occupons du navire à quai, mais nous manquons de main-d'œuvre. Cela prendra plus longtemps que prévu." }
    { group:101, id:5, text: "Nous nous occupons du navire à quai. Avec tous nos hommes disponibles, nous devrions terminer rapidement." }
    { group:101, id:6, text: "Tout navire accostant ici ne trouvera personne pour s'occuper de sa cargaison." }
    { group:101, id:7, text: "Très peu de dockers travaillent ici, il nous faudra beaucoup de temps pour nous occuper des navires qui accosteront." }
    { group:101, id:8, text: "Nous manquons de main-d'œuvre, et il nous faudra du temps pour nous occuper des navires qui accosteront au port." }
    { group:101, id:9, text: "Nos hommes sont près à s'occuper efficacement des navires qui accosteront ici." }
    { group:102, id:0, text: "Quai" }
    { group:102, id:1, text: "Les bateaux quittent la fabrique à cet endroit pour recevoir un équipage et commencer à pêcher dans les environs. Vous pouvez amarrer un bateau par quai." }
    { group:102, id:2, text: "Nous attendons que la fabrique de bateaux nous construise un bateau de pêche." }
    { group:102, id:3, text: "Notre bateau se dirige vers la zone de pêche." }
    { group:102, id:4, text: "Notre bateau est dans une zone de pêche et attrape des poissons." }
    { group:102, id:5, text: "Notre bateau de pêche revient au port." }
    { group:102, id:6, text: "Nous préparons notre bateau pour un nouveau voyage hors de nos frontières." }
    { group:102, id:7, text: "Notre bateau de pêche revient d'une zone de pêche avec sa cargaison." }
    { group:102, id:8, text: "Nos pêcheurs espèrent que quelqu'un découvrira du poisson dans cette province, sinon, ils auront bien du mal à gagner leur vie." }
    { group:102, id:9, text: "Le chef du commerce a ordonné l'interruption de la pêche." }
    { group:102, id:10, text: "Notre bateau de pêche n'ira pas dans ces eaux polluées !" }
    { group:103, id:0, text: "Palais" }
    { group:103, id:1, text: "Votre résidence est l'une des adresses les plus convoitées. Votre demeure luxueuse vous donne le droit de percevoir un salaire." }
    { group:103, id:2, text: "par mois" }
    { group:103, id:3, text: "Salaire du doyen du village :" }
    { group:103, id:4, text: "Salaire du noble du village :" }
    { group:103, id:5, text: "Salaire de l'érudit du royaume :" }
    { group:103, id:6, text: "Salaire du scribe du royaume :" }
    { group:103, id:7, text: "Salaire du juge du royaume :" }
    { group:103, id:8, text: "Salaire du maire du royaume :" }
    { group:103, id:9, text: "Salaire du gouverneur du royaume :" }
    { group:103, id:10, text: "Salaire du nomarque :" }
    { group:103, id:11, text: "Salaire du chancelier :" }
    { group:103, id:12, text: "Salaire du vizir :" }
    { group:103, id:13, text: "Salaire du pharaon :" }
    { group:104, id:0, text: "Etude d'architecte" }
    { group:104, id:1, text: "Les architectes égyptiens sont des professionnels hautement respectés dont les services sont toujours très demandés. Les bâtiments entretenus régulièrement risquent moins de s'effondrer." }
    { group:104, id:2, text: "Notre architecte travaille à l'extérieur." }
    { group:104, id:3, text: "Notre architecte se prépare à sortir." }
    { group:104, id:4, text: "Nous n'avons pas une minute à nous. Nos architectes sont toujours à l'extérieur en train d'inspecter et de réparer les détériorations des bâtiments de la cité." }
    { group:104, id:5, text: "Nos architectes sont épuisés. Ils reprendront le travail dans un jour ou deux." }
    { group:104, id:6, text: "Nous manquons de personnel, et il faudra attendre une semaine avant qu'un architecte reparte au travail." }
    { group:104, id:7, text: "Nous manquons cruellement de personnel, et il faut parfois deux semaines à un architecte pour faire sa ronde." }
    { group:104, id:8, text: "Nous sommes vraiment trop peu nombreux. Il faut presque un mois à un architecte pour faire sa ronde." }
    { group:104, id:9, text: "Aucun architecte ne travaillant ici, ce bâtiment risque de s'effondrer." }
    { group:105, id:0, text: "Palais" }
    { group:105, id:1, text: "Le palais compte parmi les bâtiments les plus attrayants de votre cité. Il abrite les percepteurs et leurs revenus, tout en conservant une trace des fonds de la cité." }
    { group:106, id:0, text: "Bureau de perception" }
    { group:106, id:1, text: "Les percepteurs ne sont certes pas populaires, mais ils sont à la base de la grandeur du royaume et des bénéfices qui nous reviennent." }
    { group:106, id:2, text: "Dans les coffres" }
    { group:106, id:3, text: "Notre percepteur vérifie les comptes des habitants de la région." }
    { group:106, id:4, text: "Notre percepteur se prépare à sortir." }
    { group:106, id:5, text: "Nous travaillons à plein rendement. Les percepteurs en tournée vont s'assurer que tous les impôts dus sont payés." }
    { group:106, id:6, text: "Nous avons subi un contretemps et il faudra compter un jour ou deux avant que les percepteurs ne reprennent leurs tournées." }
    { group:106, id:7, text: "Nous manquons de personnel, et il faudra attendre une semaine avant que les percepteurs repartent au travail." }
    { group:106, id:8, text: "Nous sommes pratiquement à cours de personnel et il faudra compter deux semaines avant la collecte." }
    { group:106, id:9, text: "En raison du manque de personnel, notre travail demandera plus de temps." }
    { group:106, id:10, text: "Aucun percepteur ne travaille ici, et les comptes de la cité doivent s'en ressentir." }
    { group:106, id:11, text: "Votre cité nécessite un palais pour collecter les impôts." }
    { group:106, id:12, text: "Votre cité nécessite un palais fonctionnel pour collecter les impôts." }
    { group:107, id:0, text: "Chadouf" }
    { group:107, id:1, text: "Ce chadouf permet de pomper de grandes quantités d'eau et d'alimenter les écluses parcourant la cité." }
    { group:107, id:2, text: "Ce chadouf ne fonctionne pas. Demandez au chef de la main-d'œuvre d'affecter davantage d'ouvriers au service des eaux." }
    { group:107, id:3, text: "Ce chadouf doit être près d'un point d'eau ou relié par une rigole à un chadouf opérationnel avant de pouvoir fonctionner." }
    { group:108, id:0, text: "Point d'eau" }
    { group:108, id:1, text: "Les porteurs tirent l'eau de cette source. Ils améliorent les conditions d'hygiène et de vie en la distribuant aux habitants." }
    { group:108, id:2, text: "Notre personnel offre un service ininterrompu de distribution à vos citoyens." }
    { group:108, id:3, text: "Nous manquons de porteurs d'eau. Il se passe parfois un jour ou deux sans distribution." }
    { group:108, id:4, text: "Nous manquons d'effectifs et il se passe parfois une semaine sans distribution." }
    { group:108, id:5, text: "Nous manquons d'employés. Il arrive parfois que la distribution soit interrompue pendant deux semaines." }
    { group:108, id:6, text: "Nous avons tout juste le minimum de personnel. Il arrive souvent que la distribution soit interrompue pendant une semaine." }
    { group:108, id:7, text: "En l'absence de personnel, cette installation ne sert à rien." }
    { group:110, id:0, text: "Oracle ? Est-ce que ce sanctuaire a sa place ici ?" }
    { group:110, id:1, text: "Ce sanctuaire rend les maisons environnantes plus attrayantes et satisfait la plupart des dieux. Il n'emploie pas de prêtres et ne ménage aucun accès à un dieu particulier." }
    { group:111, id:0, text: "Ruines en flammes" }
    { group:111, id:1, text: "Les pompiers ne sont pas arrivés à temps pour sauver le bâtiment. L'incendie ne laissera que des décombres." }
    { group:112, id:0, text: "Exploitation de céréales" }
    { group:112, id:1, text: "Les céréales sont les aliments de base de vos administrés. Elles doivent être stockées dans des greniers pour nourrir vos citoyens ou dans des entrepôts si vous souhaitez les exporter." }
    { group:112, id:2, text: "Récolte :" }
    { group:112, id:3, text: "terminée." }
    { group:112, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture des céréales." }
    { group:112, id:5, text: "Cette ferme n'emploie personne. Ses champs sont en friche." }
    { group:112, id:6, text: "Cette ferme dispose de toute la main-d'œuvre nécessaire. La production est à son maximum." }
    { group:112, id:7, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production pourrait être meilleure avec plus de main-d'œuvre." }
    { group:112, id:8, text: "La ferme manque de main-d'œuvre, ce qui fait chuter son rendement." }
    { group:112, id:9, text: "Compte tenu du faible nombre de paysans, la production de céréales est ralentie." }
    { group:112, id:10, text: "Compte tenu du nombre d'employés de cette ferme, la production est pratiquement interrompue." }
    { group:112, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:112, id:12, text: "Terre :" }
    { group:112, id:13, text: "fertile." }
    { group:112, id:14, text: "La prochaine récolte de céréales se fera en" }
    { group:113, id:0, text: "Exploitation de laitues" }
    { group:113, id:1, text: "Les laitues contribuent à une alimentation équilibrée et permettent ainsi de maintenir le moral et la santé de vos citoyens. Stockez les laitues dans des greniers pour la consommation locale et les surplus dans des entrepôts pour l'exportation." }
    { group:113, id:2, text: "Récolte :" }
    { group:113, id:3, text: "terminée." }
    { group:113, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture des laitues." }
    { group:113, id:5, text: "Cette ferme n'emploie personne. Rien n'a été planté." }
    { group:113, id:6, text: "Cette ferme dispose de suffisamment d'employés. Les laitues y poussent en abondance." }
    { group:113, id:7, text: "Cette ferme ne travaille pas à plein rendement, ce qui ralentit la production de laitues." }
    { group:113, id:8, text: "Cette ferme manque de personnel. La production de laitues demandera donc plus de temps." }
    { group:113, id:9, text: "Seuls quelques employés travaillent ici. Il faudra une éternité avant que des légumes ne poussent." }
    { group:113, id:10, text: "Compte tenu du nombre d'employés de cette ferme, les légumes vont succomber aux maladies et aux insectes." }
    { group:113, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:113, id:12, text: "Terre :" }
    { group:113, id:13, text: "fertile." }
    { group:113, id:14, text: "La prochaine cueillette de laitues se fera en" }
    { group:114, id:0, text: "Exploitation de grenades" }
    { group:114, id:1, text: "Les grenades contribuent à une alimentation équilibrée. Stockez les grenades dans des greniers pour la consommation locale et les surplus dans des entrepôts pour l'exportation." }
    { group:114, id:2, text: "Récolte :" }
    { group:114, id:3, text: "terminée." }
    { group:114, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture des grenades." }
    { group:114, id:5, text: "Ce verger n'emploie personne. La production a cessé." }
    { group:114, id:6, text: "Ce verger dispose de suffisamment d'employés. Les arbres ploient sous le nombre de grenades mûres." }
    { group:114, id:7, text: "Ce verger ne travail pas à plein rendement, ce qui ralentit légèrement la production de grenades." }
    { group:114, id:8, text: "Ce verger manque de personnel. Il produit des grenades plus lentement que la normale." }
    { group:114, id:9, text: "Très peu de personnes travaillent dans ce verger. La récolte de grenades sera très en retard." }
    { group:114, id:10, text: "Il n'y a presque pas d'employés dans ce verger et la culture de grenades prendra des années." }
    { group:114, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:114, id:12, text: "Terre :" }
    { group:114, id:13, text: "fertile." }
    { group:114, id:14, text: "La prochaine cueillette de grenades se fera en" }
    { group:115, id:0, text: "Exploitation de lin" }
    { group:115, id:1, text: "Le lin est la matière première servant à fabriquer de la toile. Les ateliers traitent et tissent les fibres de lin pour fabriquer des toiles utilisées par les embaumeurs ou pour l'exportation." }
    { group:115, id:2, text: "Récolte :" }
    { group:115, id:3, text: "terminée." }
    { group:115, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture du lin." }
    { group:115, id:5, text: "Cette ferme n'emploie personne. La production de lin est interrompue." }
    { group:115, id:6, text: "Cette ferme dispose de suffisamment d'employés. Les champs sont remplis de graines de lin bleu." }
    { group:115, id:7, text: "Cette ferme ne travaille pas à plein rendement. La production de lin pourrait être développée en engagent des employés." }
    { group:115, id:8, text: "Cette ferme manque de personnel. La production de lin s'en trouve ralentie." }
    { group:115, id:9, text: "Très peu de personnes travaillent ici. Par conséquent, la production de lin est lente." }
    { group:115, id:10, text: "En l'absence de suffisamment de travailleurs dans cette ferme, le sol est devenu quasiment stérile." }
    { group:115, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:115, id:12, text: "Terre :" }
    { group:115, id:13, text: "fertile." }
    { group:115, id:14, text: "La prochaine cueillette de lin se fera en" }
    { group:116, id:0, text: "Cueilleur de roseaux" }
    { group:116, id:1, text: "Les cueilleurs vont dans les marais cueillir les roseaux servant à la fabrication des papyrus, sans lesquels l'éducation serait impossible." }
    { group:116, id:2, text: "Roseaux stockés" }
    { group:116, id:3, text: "terminée." }
    { group:116, id:4, text: "Votre chef du commerce a ordonné l'interruption de la cueillette des roseaux." }
    { group:116, id:5, text: "Aucun cueilleur de roseaux n'est employé ici." }
    { group:116, id:6, text: "Il y a suffisamment d'employés. Aucun roseau ne sera laissé." }
    { group:116, id:7, text: "Le niveau de main-d'œuvre est inférieur au niveau potentiel, ce qui ralentit la cueillette des roseaux." }
    { group:116, id:8, text: "Cet endroit manque de personnel et la cueillette des roseaux se fait lentement." }
    { group:116, id:9, text: "Très peu de gens travaillent ici, ce qui fait que très peu de roseaux sont coupés." }
    { group:116, id:10, text: "Etant donné le nombre insignifiant de cueilleurs, la cueillette des roseaux est pratiquement nulle." }
    { group:116, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:116, id:12, text: "Terre :" }
    { group:116, id:13, text: "fertile." }
    { group:116, id:14, text: "La prochaine cueillette des roseaux se fera en" }
    { group:117, id:0, text: "Ferme d'élevage" }
    { group:117, id:1, text: "Les citoyens les plus aisés veulent manger de la viande. La viande est stockée dans des greniers pour la consommation locale ou dans des entrepôts pour l'exportation." }
    { group:117, id:2, text: "Production :" }
    { group:117, id:3, text: "terminée." }
    { group:117, id:4, text: "Votre chef du commerce a ordonné l'interruption de l'élevage." }
    { group:117, id:5, text: "Cette ferme d'élevage n'emploie presque personne et tous les animaux se sont échappés ou sont morts." }
    { group:117, id:6, text: "Il y a suffisamment d'employés pour cette ferme d'élevage. La production de viande peut être augmentée grâce à la paille." }
    { group:117, id:7, text: "Cette ferme d'élevage doit embaucher de nouveaux employés pour augmenter sa production de viande." }
    { group:117, id:8, text: "Cette ferme manque de personnel. La production est donc ralentie." }
    { group:117, id:9, text: "Très peu de personnes travaillent dans cette ferme d'élevage. Par conséquent, la production de viande est lente." }
    { group:117, id:10, text: "Dans la mesure où cette ferme n'a pratiquement pas d'employés, son troupeau est très petit." }
    { group:117, id:11, text: "Les terres de cette ferme ont été ravagée récemment par des criquets. Son troupeau ne pourra pas prospérer tant qu'elles ne seront pas restaurées." }
    { group:117, id:12, text: "Terre :" }
    { group:117, id:13, text: "fertile." }
    { group:118, id:0, text: "Carrière de pierre" }
    { group:118, id:1, text: "Taillez de la pierre en fonction des ressources de votre cité. Etant donné le nombre de monuments en construction en Egypte, vous n'aurez pas de mal à trouver un acheteur pour de bonnes pierres de taille, même si vous avez des surplus." }
    { group:118, id:2, text: "Production à" }
    { group:118, id:3, text: "terminée." }
    { group:118, id:4, text: "Votre chef du commerce a ordonné l'interruption de la production." }
    { group:118, id:5, text: "Cette carrière n'emploie personne. La production est interrompue." }
    { group:118, id:6, text: "Cette carrière dispose de toute la main-d'œuvre nécessaire, et elle produit des tonnes de pierre." }
    { group:118, id:7, text: "Cette carrière ne dispose pas de suffisamment d'ouvriers, la production est donc légèrement réduite." }
    { group:118, id:8, text: "Cette carrière manque de main-d'œuvre, et la production de blocs de pierre est plus lente que prévue." }
    { group:118, id:9, text: "Très peu de personnes travaillent dans cette carrière. Par conséquent, la production est très lente." }
    { group:118, id:10, text: "Compte tenu du nombre d'employés de cette carrière, la production est pratiquement interrompue. Son rendement sera faible au cours des prochaines années." }
    { group:119, id:0, text: "Carrière de calcaire" }
    { group:119, id:1, text: "Taillez du calcaire pour la construction de monuments ou pour l'exportation." }
    { group:119, id:2, text: "Production à" }
    { group:119, id:3, text: "terminée." }
    { group:119, id:4, text: "Votre chef du commerce a ordonné l'interruption de cette industrie." }
    { group:119, id:5, text: "Ce bâtiment n'emploie personne. La production de calcaire est interrompue." }
    { group:119, id:6, text: "Ce bâtiment dispose de toute la main-d'œuvre nécessaire, et fonctionne à plein rendement." }
    { group:119, id:7, text: "Ce bâtiment ne travaille pas à plein rendement. La production pourrait être légèrement améliorée en embauchant davantage de main-d'œuvre." }
    { group:119, id:8, text: "Ce bâtiment manque de personnel. La production de blocs de calcaire est plus lente que prévue." }
    { group:119, id:9, text: "Très peu de personnes travaillent dans ce bâtiment. Par conséquent, la production est lente." }
    { group:119, id:10, text: "Il n'y a presque plus de main-d'œuvre et la production de calcaire est quasiment nulle." }
    { group:120, id:0, text: "Chantier de bois" }
    { group:120, id:1, text: "Le bois a de nombreuses utilisations : de la construction de monuments à la construction navale. C'est une matière très demandée dans tout le royaume." }
    { group:120, id:2, text: "Contient" }
    { group:120, id:3, text: "Bois brut" }
    { group:120, id:4, text: "Votre chef du commerce a ordonné l'interruption de la coupe des arbres." }
    { group:120, id:5, text: "Ce chantier n'emploie personne. La production a cessé." }
    { group:120, id:6, text: "Ce bâtiment dispose de toute la main-d'œuvre nécessaire. La production de bois est abondante." }
    { group:120, id:7, text: "Ce chantier de bois ne dispose pas de suffisamment d'ouvriers. La production sera donc légèrement réduite." }
    { group:120, id:8, text: "Cette industrie manque de main-d'œuvre et la coupe du bois prend plus longtemps qu'à l'accoutumée." }
    { group:120, id:9, text: "Seuls quelques employés travaillent ici. La production de bois est donc ralentie." }
    { group:120, id:10, text: "Compte tenu du nombre de bûcherons, la production est pratiquement nulle. Les bois redeviennent sauvages." }
    { group:121, id:0, text: "Puits d'argile" }
    { group:121, id:1, text: "Extrayez de l'argile pour en faire le commerce ou pour fournir les poteries. Les citoyens ont besoin de poteries pour vivre dans les insulae. Vous pouvez également faire le commerce des poteries avec les autres cités." }
    { group:121, id:2, text: "Production à" }
    { group:121, id:3, text: "terminée." }
    { group:121, id:4, text: "Votre chef du commerce a ordonné de mettre un frein à l'extraction d'argile." }
    { group:121, id:5, text: "Ce puits n'emploie personne. La production est inexistante." }
    { group:121, id:6, text: "Ce puits dispose de toute la main-d'œuvre nécessaire, et la production d'argile est abondante." }
    { group:121, id:7, text: "Ce puits ne dispose pas de suffisamment d'ouvriers. La production sera donc légèrement ralentie." }
    { group:121, id:8, text: "Ce puits manque de main-d'œuvre, et la production d'argile est plus longue que prévue." }
    { group:121, id:9, text: "Seuls quelques employés travaillent ici. La production est donc très ralentie." }
    { group:121, id:10, text: "Compte tenu du nombre d'employés de ce puits, la production est pratiquement nulle. Très peu d'argile sera extraite cette année." }
    { group:122, id:0, text: "Brasserie" }
    { group:122, id:1, text: "Les brasseries transforment l'orge en bière. Sans elles, les tavernes de jeux se videraient et les fêtes seraient ennuyeuses. La bière est une denrée commerciale très demandée." }
    { group:122, id:2, text: "Production à" }
    { group:122, id:3, text: "terminée." }
    { group:122, id:4, text: "Votre chef du commerce a ordonné l'interruption des brasseries." }
    { group:122, id:5, text: "Cette brasserie n'emploie personne. La production est interrompue." }
    { group:122, id:6, text: "Cette brasserie dispose de toute la main-d'œuvre nécessaire, et la production de bière est abondante." }
    { group:122, id:7, text: "Cette brasserie ne travaille pas à plein rendement. La production de bière est inférieure à la normale." }
    { group:122, id:8, text: "Cette brasserie manque de main-d'œuvre, et la production de bière est beaucoup plus longue que prévue." }
    { group:122, id:9, text: "Très peu de personnes travaillent dans cette brasserie. Par conséquent, la production de bière est très lente." }
    { group:122, id:10, text: "Compte tenu du nombre d'employés de cette brasserie, la production est pratiquement interrompue. La production de bière sera faible au cours des prochaines années." }
    { group:122, id:11, text: "Cet atelier ne peut pas produire de bière tant qu'il n'a pas reçu de livraison d'orge en provenance d'un entrepôt ou d'une ferme." }
    { group:122, id:12, text: "Orge en stock," }
    { group:123, id:0, text: "Atelier de tissage" }
    { group:123, id:1, text: "Ici, le lin est transformé en toiles, destinées aux salles d'embaumeurs. Les toiles de lin peuvent également servir à un commerce rentable." }
    { group:123, id:2, text: "Production à" }
    { group:123, id:3, text: "terminée." }
    { group:123, id:4, text: "Votre chef du commerce a ordonné l'interruption de la production de toile." }
    { group:123, id:5, text: "Cet atelier de tissage n'emploie aucun tisserand et ne produit pas de toiles." }
    { group:123, id:6, text: "La main-d'œuvre de cet atelier de tissage est au complet et produit des toiles de grande qualité." }
    { group:123, id:7, text: "Cet atelier de tissage nécessite un supplément de main-d'œuvre pour fonctionner à plein rendement." }
    { group:123, id:8, text: "Cet atelier de tissage manque de main-d'œuvre, ce qui ralentit la production de toiles." }
    { group:123, id:9, text: "Très peu de personnes travaillent dans cet atelier de tissage. Par conséquent, la production de toiles est lente." }
    { group:123, id:10, text: "Cet atelier de tissage n'a presque plus de main-d'œuvre et la production est au plus bas. La production de toiles sera faible au cours des prochaines années." }
    { group:123, id:11, text: "Cet atelier ne fabriquera pas de toiles sans une livraison de lin, que ce soit en provenance d'un entrepôt ou d'une ferme." }
    { group:123, id:12, text: "Lin stocké," }
    { group:124, id:0, text: "Fabrique d'armes" }
    { group:124, id:1, text: "Les armuriers transforment le bois et le cuivre en lances, que vous pouvez revendre au prix fort ou utiliser pour équiper vos propres compagnies." }
    { group:124, id:2, text: "Production à" }
    { group:124, id:3, text: "terminée." }
    { group:124, id:4, text: "La production d'armes a été interdite par votre chef du commerce." }
    { group:124, id:5, text: "Cette fabrique n'emploie personne. La production a cessé." }
    { group:124, id:6, text: "Cette fabrique dispose de toute la main-d'œuvre nécessaire et produit des armes de qualité." }
    { group:124, id:7, text: "Cette fabrique ne dispose pas de suffisamment d'ouvriers, la production sera donc légèrement réduite." }
    { group:124, id:8, text: "Cette fabrique manque de personnel, et la production d'armes est plus longue que d'habitude." }
    { group:124, id:9, text: "Seuls quelques employés travaillent ici. La production est donc très ralentie." }
    { group:124, id:10, text: "Compte tenu du nombre d'employés de cette fabrique d'armes, la production est pratiquement inexistante. Très peu d'armes seront fabriquées cette année." }
    { group:124, id:11, text: "Cet atelier doit recevoir une livraison de cuivre d'un entrepôt ou d'une mine pour la production d'armes." }
    { group:124, id:12, text: "Cuivre stocké," }
    { group:125, id:0, text: "Orfèvrerie" }
    { group:125, id:1, text: "Les artisans travaillant dans cet atelier fabriquent de somptueux bijoux (articles de luxe) à l'aide de pierres précieuses. Certains citoyens veulent des bijoux pour eux-mêmes, ou pour commercer." }
    { group:125, id:2, text: "Production à" }
    { group:125, id:3, text: "terminée." }
    { group:125, id:4, text: "La fabrication de bijoux a été interrompue sur ordre du chef du commerce." }
    { group:125, id:5, text: "Cet endroit n'a pas d'orfèvrerie. La production est interrompue." }
    { group:125, id:6, text: "Cet atelier est en plein emploi et fonctionne à plein rendement pour produire des bijoux (articles de luxe)." }
    { group:125, id:7, text: "Cet atelier a quelques postes à pourvoir, ce qui permettra d'augmenter la production de bijoux (articles de luxe)." }
    { group:125, id:8, text: "Cet atelier n'a pas suffisamment de main-d'œuvre, et la production de bijoux (articles de luxe) est donc plus lente que la normale." }
    { group:125, id:9, text: "Seuls quelques employés travaillent ici. La production de bijoux (articles de luxe) est donc très ralentie." }
    { group:125, id:10, text: "En raison du nombre très peu élevé d'artisans qui travaillent dans cette orfèvrerie, la production stagne. La production de bijoux (articles de luxe) sera très faible cette année." }
    { group:125, id:11, text: "Cet atelier doit recevoir une livraison de pierres précieuses d'un entrepôt ou d'une mine pour la production de bijoux." }
    { group:125, id:12, text: "Pierres précieuses stockées," }
    { group:126, id:0, text: "Poterie" }
    { group:126, id:1, text: "Ici, les potiers fabriquent des pots en argile que les citoyens utilisent pour stocker des denrées. Commercialisez des poteries, ou faites-les distribuer par les bazars afin de permettre aux habitants de construire de meilleures habitations." }
    { group:126, id:2, text: "Production à" }
    { group:126, id:3, text: "terminée." }
    { group:126, id:4, text: "La production de poteries a été interrompue sur ordre du chef du commerce." }
    { group:126, id:5, text: "Cette fabrique n'emploie personne. La production a cessé." }
    { group:126, id:6, text: "Cet atelier dispose de toute la main-d'œuvre nécessaire. Les poteries qu'il produit sont réputées pour leur qualité." }
    { group:126, id:7, text: "Cet atelier ne dispose pas de suffisamment d'ouvriers. La production de poteries sera donc légèrement réduite." }
    { group:126, id:8, text: "Cet atelier manque de main-d'œuvre, et la production de poteries prendra plus de temps que prévu." }
    { group:126, id:9, text: "Seuls quelques employés travaillent ici. La production de poteries est donc très ralentie." }
    { group:126, id:10, text: "Compte tenu du nombre d'employés de cette poterie, la production est pratiquement inexistante. Très peu de poteries seront produites cette année." }
    { group:126, id:11, text: "Cet atelier doit recevoir une livraison d'argile d'un entrepôt ou d'un puits d'argile pour la production de poteries." }
    { group:126, id:12, text: "Argile en stock," }
    { group:127, id:0, text: "Logement" }
    { group:127, id:1, text: "Mode de test désactivé" }
    { group:127, id:2, text: "Mode de test activé" }
    { group:127, id:3, text: "Attrait" }
    { group:127, id:4, text: "Div" }
    { group:127, id:5, text: "H2O" }
    { group:127, id:6, text: "Religion" }
    { group:127, id:7, text: "Education" }
    { group:127, id:8, text: "Accès au bazar" }
    { group:127, id:9, text: "Accès au dentiste" }
    { group:127, id:10, text: "Accès au médecin" }
    { group:127, id:11, text: "Hygiène" }
    { group:127, id:12, text: "Types de nourriture" }
    { group:127, id:13, text: "Poteries requises" }
    { group:127, id:14, text: "Toile requise" }
    { group:127, id:15, text: "Articles de luxe requis" }
    { group:127, id:16, text: "Bière requise" }
    { group:127, id:17, text: "Maintenant" }
    { group:127, id:18, text: "évolue vers" }
    { group:127, id:19, text: "nécessite" }
    { group:127, id:20, text: "occupants" }
    { group:127, id:21, text: "en trop." }
    { group:127, id:22, text: "Espace disponible pour" }
    { group:127, id:23, text: "Aucune visite du percepteur. Impôts non payés" }
    { group:127, id:24, text: "Généré" }
    { group:127, id:25, text: "d'impôts à ce jour." }
    { group:127, id:26, text: "Les habitants n'ont signalé aucun crime." }
    { group:127, id:27, text: "Ce quartier est tranquille." }
    { group:127, id:28, text: "Quelques crimes signalés, rien de grave." }
    { group:127, id:29, text: "La criminalité devient un problème." }
    { group:127, id:30, text: "Les habitants n'osent plus sortir de chez eux." }
    { group:127, id:31, text: "Ce secteur est dangereux. Les habitants sont terrifiés." }
    { group:127, id:32, text: "Cet endroit est propice aux voleurs." }
    { group:127, id:33, text: "Aucune amélioration des huttes prévue avant la distribution de nourriture par les bazars." }
    { group:127, id:34, text: "Housing FREE" }
    { group:127, id:35, text: "Housing FREE" }
    { group:127, id:36, text: "Housing FREE" }
    { group:127, id:37, text: "Housing FREE" }
    { group:127, id:38, text: "Housing FREE" }
    { group:127, id:39, text: "Housing FREE" }
    { group:127, id:40, text: "Cette maison va bientôt régresser. L'attrait décroissant pour ce secteur entraîne le déclin de cette demeure." }
    { group:127, id:42, text: "Cette maison va bientôt régresser, car elle n'est même pas visitée par un porteur d'eau" }
    { group:127, id:43, text: "Cette maison va bientôt régresser, car il n'y a rien pour se divertir dans ce secteur." }
    { group:127, id:44, text: "Cette maison va bientôt régresser, car il y a très peu de distractions dans ce secteur." }
    { group:127, id:45, text: "Cette maison va bientôt régresser, car il n'y a pas assez de distractions dans ce secteur." }
    { group:127, id:46, text: "Cette maison va bientôt régresser. Il est possible de se divertir dans ce secteur, mais pas suffisamment." }
    { group:127, id:47, text: "Cette maison va bientôt régresser. Il est possible de se divertir dans ce secteur, mais cela manque un peu de variété." }
    { group:127, id:48, text: "Cette maison va bientôt régresser. L'endroit offre d'excellentes possibilités de divertissement, mais il est trop fréquenté et pas assez varié pour les scribes" }
    { group:127, id:49, text: "Cette maison va bientôt régresser, car elle n'a pas récemment reçu de nourriture par les bazars" }
    { group:127, id:50, text: "Cette maison va bientôt régresser, car elle n'a actuellement accès qu'à une sorte de nourriture par son bazar local. De quoi décourager les plus riches citoyens." }
    { group:127, id:51, text: "Cette maison va bientôt régresser, car elle n'a actuellement accès qu'à deux sortes de nourriture par son bazar local. De quoi décourager les scribes." }
    { group:127, id:52, text: "Cette maison va bientôt régresser, car elle a perdu tout accès à un bazar." }
    { group:127, id:53, text: "Cette maison va bientôt régresser. Bien qu'elle ait accès à un bazar, ce dernier n'est pas suffisamment alimenté en nourriture." }
    { group:127, id:54, text: "Cette maison va bientôt régresser, car elle n'a plus ni école de scribes, ni bibliothèque." }
    { group:127, id:55, text: "Cette maison va bientôt régresser. Son accès à l'éducation a diminué car elle a perdu son accès à une bibliothèque." }
    { group:127, id:56, text: "Cette maison va bientôt régresser. Son accès à l'éducation a diminué car elle a perdu son accès à une école de scribes." }
    { group:127, id:57, text: "Cette maison va bientôt régresser. Son accès à l'éducation, auparavant excellent, a diminué car elle a perdu tout accès à l'éducation supérieure." }
    { group:127, id:58, text: "Cette maison va bientôt régresser, car elle n'a pas accès à des magistrats de palais de justice." }
    { group:127, id:59, text: "Cette maison va bientôt régresser. Elle ne dispose plus de poteries, et les livraisons de son bazar local sont irrégulières." }
    { group:127, id:60, text: "Cette maison va bientôt régresser, car elle a perdu tout accès à des lieux de culte." }
    { group:127, id:61, text: "Cette maison va bientôt régresser. Son accès à des lieux de culte a été réduit au point de ne pouvoir adorer qu'une seule divinité." }
    { group:127, id:62, text: "Cette maison va bientôt régresser. Son accès à des lieux de culte a été réduit et seuls les temples de deux divinités sont maintenant à proximité." }
    { group:127, id:63, text: "Cette maison va bientôt régresser, car elle a perdu tout accès à un dentiste." }
    { group:127, id:64, text: "Cette maison va bientôt régresser, car elle bénéficie désormais d'une hygiène déplorable. Non seulement elle n'a pas accès à un lieu d'embaumement, mais son accès à un médecin est loin d'être parfait." }
    { group:127, id:65, text: "Cette maison va bientôt régresser, car elle a perdu toute hygiène. Elle a accès à un nombre suffisant de médecins, mais à aucune salle des embaumeurs." }
    { group:127, id:66, text: "Cette maison va bientôt régresser, car elle a perdu toute hygiène. Elle a accès à une salle des embaumeurs, mais les médecins se font rare." }
    { group:127, id:67, text: "Cette maison va bientôt régresser, car elle n'a plus de toile et les livraisons de son bazar local sont irrégulières." }
    { group:127, id:68, text: "sans utilisation" }
    { group:127, id:69, text: "Cette maison va bientôt régresser, car elle n'a plus de bière et son bazar local ne reçoit que des livraisons irrégulières." }
    { group:127, id:70, text: "Cette demeure ne peut pas évoluer tant que les environs n'ont pas suffisamment d'attrait." }
    { group:127, id:71, text: "Cette maison ne peut pas évoluer tant qu'elle n'a pas accès à une source d'eau de base." }
    { group:127, id:72, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès aux services d'un porteur d'eau" }
    { group:127, id:73, text: "Cette maison ne peut pas évoluer, car il n'y a rien pour se divertir dans ce secteur." }
    { group:127, id:74, text: "Cette maison ne peut pas évoluer, car il y a très peu de distractions dans ce secteur." }
    { group:127, id:75, text: "Cette maison ne peut pas évoluer, car il n'y a pas assez de distractions dans ce secteur." }
    { group:127, id:76, text: "Cette maison ne peut pas évoluer. Il est possible de se divertir dans ce secteur, mais pas suffisamment." }
    { group:127, id:77, text: "Cette maison ne peut pas évoluer. Il est possible de se divertir dans ce secteur, mais cela manque un peu de variété." }
    { group:127, id:78, text: "Cette maison ne peut pas évoluer. L'endroit offre d'excellentes possibilités de divertissement, mais il est trop fréquenté et pas assez varié pour les scribes." }
    { group:127, id:79, text: "Cette maison ne peut pas évoluer, car elle doit recevoir de la nourriture d'un bazar local." }
    { group:127, id:80, text: "Cette maison ne peut pas évoluer, car il lui faut une deuxième sorte de nourriture, fournie par un bazar local, pour que des Egyptiens plus riches veuillent s'y installer." }
    { group:127, id:81, text: "Cette maison ne peut pas évoluer, car il lui faut une troisième sorte de nourriture, fournie par un bazar local, pour que des Egyptiens d'une classe supérieure veuillent s'y installer." }
    { group:127, id:82, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès à un bazar local." }
    { group:127, id:83, text: "Cette maison ne peut pas évoluer. Bien qu'elle ait accès à un bazar local, ce dernier n'est pas régulièrement approvisionné en nourriture." }
    { group:127, id:84, text: "Cette maison ne peut pas évoluer, car elle n'a accès ni à une école de scribes, ni à une bibliothèque." }
    { group:127, id:85, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès à une bibliothèque." }
    { group:127, id:86, text: "Cette maison ne peut pas évoluer, car elle doit avoir accès à une école de scribes." }
    { group:127, id:87, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès à une académie militaire." }
    { group:127, id:88, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès à un magistrat d'un palais de justice local." }
    { group:127, id:89, text: "Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de poteries de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
    { group:127, id:90, text: "Cette maison ne peut pas évoluer, car elle n'a accès à aucun lieu de culte." }
    { group:127, id:91, text: "Cette maison ne peut pas évoluer, car elle a uniquement accès aux temples dédiés à une seule divinité. Les habitants des classes supérieures désirent adorer plusieurs divinités." }
    { group:127, id:92, text: "Cette maison ne peut pas évoluer, car elle a uniquement accès aux temples dédiés à deux divinités. Les habitants des classes supérieures désirent adorer plus de divinités." }
    { group:127, id:93, text: "Cette maison ne peut pas évoluer, car elle n'a pas accès à un dentiste." }
    { group:127, id:94, text: "Cette maison ne peut pas évoluer, car elle n'a pas d'hygiène effective. Elle n'a en effet accès ni à un médecin, ni à une salle des embaumeurs." }
    { group:127, id:95, text: "Cette maison ne peut pas évoluer, car elle doit avoir plus d'hygiène. Elle a accès à un nombre suffisant de médecins, mais à aucune salle des embaumeurs." }
    { group:127, id:96, text: "Cette maison ne peut pas évoluer, car elle doit avoir plus d'hygiène. Elle a accès à une salle des embaumeurs, mais il faut construire une pharmacie dans les environs." }
    { group:127, id:97, text: "Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de toile de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
    { group:127, id:98, text: "sans utilisation" }
    { group:127, id:99, text: "Cette maison ne peut pas évoluer. Elle doit recevoir une livraison de bières de son bazar local pour que les citoyens des classes supérieures viennent s'y installer." }
    { group:127, id:100, text: "Les habitants de ce palais sont au sommet de la société égyptienne. Ils veulent tout pour rien. C'est tout un travail de les satisfaire !" }
    { group:127, id:101, text: "Cette demeure va bientôt évoluer, en conséquence de l'amélioration des conditions de vie dans ce secteur." }
    { group:127, id:102, text: "La proximité de cet édifice (" }
    { group:127, id:103, text: "a un effet négatif sur l'attrait de ce secteur." }
    { group:127, id:104, text: "Cette habitation est gênée dans son évolution car elle manque d'espace pour s'agrandir." }
    { group:127, id:105, text: "sans utilisation" }
    { group:127, id:106, text: "sans utilisation" }
    { group:127, id:107, text: "Maison contaminée pour encore" }
    { group:127, id:108, text: "Cette maison ne peut pas évoluer. Elle doit recevoir des articles de luxe comme" }
    { group:127, id:109, text: "Infection de grenouilles pour encore" }
    { group:127, id:110, text: "Cette maison va bientôt régresser, car elle n'a accès qu'à une sorte d'articles de luxe" }
    { group:127, id:111, text: "et ses habitants se plaignent de ce manque de choix." }
    { group:127, id:112, text: "Cette maison va bientôt régresser. Elle doit recevoir des articles de luxe, tels que des bijoux," }
    { group:127, id:113, text: "pour satisfaire les goûts raffinés des scribes." }
    { group:127, id:114, text: "Cette maison ne peut évoluer sans :" }
    { group:127, id:115, text: "mais elle doit avoir accès à une deuxième sorte d'articles de luxe, telle que l'ébène, l'ivoire ou l'encens," }
    { group:127, id:116, text: "pour satisfaire les goûts raffinés des scribes." }
    { group:128, id:0, text: "Terrain à bâtir" }
    { group:128, id:1, text: "Personne n'a encore daigné s'installer ici, mais des immigrants devraient arriver rapidement si la cité a de la nourriture et des emplois à offrir." }
    { group:128, id:2, text: "Personne ne viendra s'installer ici car il n'y a pas de route à proximité. Si vous ne remédiez pas à ce problème, ce terrain retournera bientôt à l'état sauvage." }
    { group:129, id:0, text: "de" }
    { group:129, id:1, text: "Capacité" }
    { group:129, id:2, text: "Achats" }
    { group:129, id:3, text: "Ventes" }
    { group:129, id:4, text: "Acheté" }
    { group:129, id:5, text: "Vendu" }
    { group:129, id:6, text: "A jeté l'ancre en attente d'un dock libre." }
    { group:129, id:7, text: "A quai, en train d'acheter et de revendre des biens." }
    { group:129, id:8, text: "Sur le retour" }
    { group:129, id:9, text: "En route vers les docks de la cité." }
    { group:129, id:10, text: "En train de commercer" }
    { group:129, id:11, text: "Sur le retour" }
    { group:129, id:12, text: "En direction des entrepôts de la cité" }
    { group:129, id:13, text: "Rien à échanger ici, juste de passage" }
    { group:129, id:14, text: "En provenance de :" }
    { group:129, id:15, text: "En route vers :" }
    { group:129, id:16, text: "Vers:" }
    { group:129, id:17, text: "Collecte" }
    { group:129, id:18, text: "De retour avec" }
    { group:129, id:19, text: "unité de" }
    { group:129, id:20, text: "unités de" }
    { group:129, id:21, text: "Transportant" }
    { group:130, id:0, text: "(Non utilisé)" }
    { group:131, id:0, text: "Hutte indigène" }
    { group:131, id:1, text: "Does this text appear anywhere?" }
    { group:132, id:0, text: "Hutte du chef de la tribu" }
    { group:132, id:1, text: "Is this entry used anywhere?" }
    { group:133, id:0, text: "Cultures de base" }
    { group:133, id:1, text: "This entry is probably unused." }
    { group:134, id:0, text: "Mission" }
    { group:134, id:1, text: "Where did this text appear?" }
    { group:135, id:0, text: "Académie militaire" }
    { group:135, id:1, text: "Une fois que les nouveaux soldats ont terminé leur formation au centre de recrutement, ils doivent la compléter au sein de l'académie militaire, mais il faut pour cela que le quota des membres soit atteint." }
    { group:135, id:2, text: "Par manque d'employés, nous ne pouvons assurer la formation des nouvelles troupes de la cité. Elles devront se rendre directement au fort." }
    { group:135, id:3, text: "Nous offrons aux nouvelles recrues la formation nécessaire à la réussite au sein d'une armée égyptienne moderne." }
    { group:136, id:0, text: "Centre de recrutement" }
    { group:136, id:1, text: "Nul ne peut rejoindre l'armée égyptienne avant d'avoir reçu une formation ici ; il s'agit du centre de formation des nouvelles recrues." }
    { group:136, id:2, text: "Stocks d'armes" }
    { group:136, id:3, text: "Sans personnel, il nous est impossible de former les nouvelles recrues. Que Seth nous aide en temps de guerre !" }
    { group:136, id:4, text: "Nous ne formons actuellement aucune recrue, car ni les forts, ni les tours n'ont réclamé de nouvelles troupes." }
    { group:136, id:5, text: "Nous pouvons former de nouveaux archers rapidement, mais il nous faut des armes pour rajouter des fantassins ou des chars au bataillon de la cité." }
    { group:136, id:6, text: "Comme il nous manque des employés, nous formons les nouveaux soldats moins rapidement. Sans stock d'armes, il nous est impossible de former des fantassins ou des conducteurs de char." }
    { group:136, id:7, text: "Nous manquons de personnel et notre stock d'armes est épuisé ! Nous pouvons former des archers, mais lentement." }
    { group:136, id:8, text: "Sans employés et sans stocks d'armes dans la cité, il est difficile de former des archers." }
    { group:136, id:9, text: "Tous nos instructeurs sont au travail, et nous disposons du stock d'armes nécessaire pour former tous types de troupes." }
    { group:136, id:10, text: "Nous manquons d'employés, ce qui ralentit la formation des troupes. En revanche, nous disposons des armes nécessaires pour équiper tous types de troupes." }
    { group:136, id:11, text: "Nous manquons sérieusement d'employés. Les stocks d'armes nous permettent bien de former tous types de troupes, mais à un rythme très faible." }
    { group:136, id:12, text: "Bien que des armes soient disponibles, sans employés, il nous est difficile de former même la plus sommaire des troupes." }
    { group:136, id:13, text: "Chars stockés" }
    { group:136, id:14, text: "Char stocké" }
    { group:136, id:15, text: "Arme stockée" }
    { group:137, id:0, text: "Plaza" }
    { group:137, id:1, text: "Les plazas augmentent l'attrait des routes pavées, sans gêner la circulation." }
    { group:138, id:0, text: "'Les lions'" }
    { group:138, id:1, text: "'Les crocodiles'" }
    { group:138, id:2, text: "'Les cobras'" }
    { group:138, id:3, text: "'Les scorpions'" }
    { group:138, id:4, text: "'Les faucons'" }
    { group:138, id:5, text: "'Les béliers'" }
    { group:138, id:6, text: "'Les hyènes'" }
    { group:138, id:7, text: "'Les scarabées'" }
    { group:138, id:8, text: "'Les chacals'" }
    { group:138, id:9, text: "'Les vipères'" }
    { group:138, id:10, text: "Cette compagnie n'a actuellement aucun soldat. Elle ne deviendra une unité de combat que lorsque des troupes fraîchement formées arriveront." }
    { group:138, id:11, text: "Cette compagnie n'a pas de soldats. Elle n'existe que nominalement et, sans véritable centre de recrutement, on ne peut accueillir de troupes." }
    { group:138, id:12, text: "Mettez-vous en formation serrée" }
    { group:138, id:13, text: "La compagnie ne se bat que lorsqu'elle est attaquée. Ses soldats sont forts au combat mais sont plus vulnérables aux attaques à distance." }
    { group:138, id:14, text: "Mettez-vous en formation relâchée" }
    { group:138, id:15, text: "La compagnie se bat en cas d'attaque. Ses soldats couvrent beaucoup de terrain et résistent bien à distance, mais leurs aptitudes s'en ressentent." }
    { group:138, id:16, text: "Engager le combat contre les ennemis immédiats" }
    { group:138, id:17, text: "A cet ordre, la compagnie attaque, en formation, tout ennemi suffisamment inconscient pour s'approcher." }
    { group:138, id:18, text: "Balayage" }
    { group:138, id:19, text: "Lorsqu'elle reçoit cet ordre, la compagnie rompt sa formation et se met à la recherche des ennemis." }
    { group:138, id:20, text: "Charge" }
    { group:138, id:21, text: "Une compagnie qui reçoit cet ordre entreprend de briser les rangs des forces ennemies." }
    { group:138, id:22, text: "Lorsqu'elle en reçoit l'ordre, la compagnie quitte le champ de bataille et va remplacer les camarades tombés au combat et se reposer." }
    { group:138, id:23, text: "Soldats de la compagnie" }
    { group:138, id:24, text: "Santé des soldats" }
    { group:138, id:25, text: "Expérience" }
    { group:138, id:26, text: "Parfaite" }
    { group:138, id:27, text: "Très bonne" }
    { group:138, id:28, text: "Bonne" }
    { group:138, id:29, text: "Moyen" }
    { group:138, id:30, text: "Faible" }
    { group:138, id:31, text: "Très faible" }
    { group:138, id:32, text: "Epouvantable" }
    { group:138, id:33, text: "Chars" }
    { group:138, id:34, text: "Fantassins" }
    { group:138, id:35, text: "Archers" }
    { group:138, id:36, text: "Moral" }
    { group:138, id:37, text: "Panique !" }
    { group:138, id:38, text: "Terreur en marche !" }
    { group:138, id:39, text: "Grande frayeur !" }
    { group:138, id:40, text: "Frayeur extrême !" }
    { group:138, id:41, text: "Frayeur !" }
    { group:138, id:42, text: "Grand désarroi" }
    { group:138, id:43, text: "Désarroi" }
    { group:138, id:44, text: "Pauvre" }
    { group:138, id:45, text: "Assez pauvre" }
    { group:138, id:46, text: "Inférieur à moyenne" }
    { group:138, id:47, text: "Dans la moyenne" }
    { group:138, id:48, text: "Supérieur à moyenne" }
    { group:138, id:49, text: "Remotivé" }
    { group:138, id:50, text: "Audacieux !" }
    { group:138, id:51, text: "Très audacieux !" }
    { group:138, id:52, text: "Intrépide" }
    { group:138, id:53, text: "Très intrépide" }
    { group:138, id:54, text: "Résistant" }
    { group:138, id:55, text: "Très résistant" }
    { group:138, id:56, text: "Excellente" }
    { group:138, id:57, text: "Parfaite" }
    { group:138, id:58, text: "Retour au fort" }
    { group:138, id:59, text: "Maudit par Seth !" }
    { group:138, id:60, text: "Vert" }
    { group:138, id:61, text: "Expérimenté" }
    { group:138, id:62, text: "Vétéran" }
    { group:138, id:63, text: "Maîtres" }
    { group:138, id:64, text: "Elite" }
    { group:138, id:65, text: "Les meilleurs" }
    { group:138, id:66, text: "Points principaux" }
    { group:138, id:67, text: "Attaque en mêlée" }
    { group:138, id:68, text: "Armure de mêlée" }
    { group:138, id:69, text: "Armure contre armes de jet" }
    { group:138, id:70, text: "Attaque d'armes de jet" }
    { group:138, id:71, text: "Portée des armes de jet" }
    { group:138, id:72, text: "Armes de jet ROF" }
    { group:138, id:73, text: "Compagnie" }
    { group:138, id:74, text: "Compagnie de fantassins" }
    { group:138, id:75, text: "Compagnie d'archers" }
    { group:138, id:76, text: "Compagnie de charretiers" }
    { group:138, id:77, text: "Cliquez pour pivoter la ligne de la compagnie" }
    { group:138, id:78, text: "Ordres et orientation de la compagnie" }
    { group:139, id:0, text: "Mur de terre" }
    { group:139, id:1, text: "Les murs défendent votre cité des invasions, mais ne sont pas indestructibles. Plus ils sont épais, plus ils sont solides, et des soldats peuvent les patrouiller" }
    { group:140, id:0, text: "Gravats" }
    { group:140, id:1, text: "Il ne reste que des ruines de ce bâtiment. Ces gravats ne font rien pour améliorer l'attrait de ce quartier." }
    { group:141, id:0, text: "Rigole d'irrigation" }
    { group:141, id:1, text: "Cette rigole d'irrigation fait circuler l'eau pour fertiliser les terres arables" }
    { group:141, id:2, text: "Cette rigole d'irrigation ne transporte pas l'eau dans des zones moins fertiles, car il n'y a pas de source d'eau à proximité." }
    { group:142, id:0, text: "Nouvelle route de commerce établie" }
    { group:142, id:1, text: "Pour commencer le commerce de ces marchandises, indiquez à votre chef du commerce de modifier leur statut dans le rapport sur les ressources." }
    { group:142, id:2, text: "Consulter le chef ?" }
    { group:142, id:3, text: "ATTENTION ! Votre cité doit disposer d'un dock avant qu'un navire de commerce puisse emprunter cette nouvelle voie maritime." }
    { group:143, id:0, text: "Accepter les biens" }
    { group:143, id:1, text: "Refuser les biens" }
    { group:143, id:2, text: "Demander de la nourriture" }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Vide" }
    { group:144, id:3, text: "Vide" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Vide" }
    { group:144, id:6, text: "Vide" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "Vide" }
    { group:144, id:9, text: "Vide" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "Vide" }
    { group:144, id:12, text: "Vide" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "Vide" }
    { group:144, id:15, text: "Vide" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "Vide" }
    { group:144, id:18, text: "Vide" }
    { group:144, id:19, text: "VII Fin de la période archaïque" }
    { group:144, id:20, text: "Behdet (Apollinopolis) : eaux dangereuses" }
    { group:144, id:21, text: "Abedju (Abydos) : la nécropole" }
    { group:144, id:22, text: "Naissance de l'Ancien Empire" }
    { group:144, id:23, text: "l'oasis de Selima : renforcer les colonnes de caravanes" }
    { group:144, id:24, text: "Abou (Eléphantine) : chercher de nouvelles richesses" }
    { group:144, id:25, text: "IX (Ancien Empire)" }
    { group:144, id:26, text: "Vide" }
    { group:144, id:27, text: "Vide" }
    { group:144, id:28, text: "Ancien Empire" }
    { group:144, id:29, text: "Serabit Khadim : le rude Sinaï" }
    { group:144, id:30, text: "Meidoum : votre propre tombe" }
    { group:144, id:31, text: "L'Age des Pyramides" }
    { group:144, id:32, text: "Buhen : maîtrise des Nubiens" }
    { group:144, id:33, text: "Sud de Dahshur : un nouveau type de pyramide" }
    { group:144, id:34, text: "XII (Ancien Empire)" }
    { group:144, id:35, text: "Vide" }
    { group:144, id:36, text: "Vide" }
    { group:144, id:37, text: "L'Age des Pyramides" }
    { group:144, id:38, text: "Iount Tentöre (Dendérah) : menace des Ethiopiens" }
    { group:144, id:39, text: "On (Héliopolis) : les carrières de Tura" }
    { group:144, id:40, text: "XIV (Ancien Empire)" }
    { group:144, id:41, text: "Vide" }
    { group:144, id:42, text: "Vide" }
    { group:144, id:43, text: "Grandeur de l'Ancien Empire" }
    { group:144, id:44, text: "l'oasis de Baharièh : les soldats de Rê" }
    { group:144, id:45, text: "Djédu (Abousir) : culte de Rê" }
    { group:144, id:46, text: "Déclin de l'Ancien Empire" }
    { group:144, id:47, text: "l'oasis de Dunqul : éloigner les chacals" }
    { group:144, id:48, text: "l'oasis de Dakhlèh : ordre au sein du chaos" }
    { group:144, id:49, text: "Première période intermédiaire" }
    { group:144, id:50, text: "This : la lutte pour le trône" }
    { group:144, id:51, text: "Ouaset (Thèbes) : la gloire menacée" }
    { group:144, id:52, text: "Naissance du Moyen Empire" }
    { group:144, id:53, text: "Gebtyou (Coptos) : la lutte pour la paix" }
    { group:144, id:54, text: "Menat Koufou (Beni Hasan) : famine" }
    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "Vide" }
    { group:144, id:57, text: "Vide" }
    { group:144, id:58, text: "Moyen Empire" }
    { group:144, id:59, text: "Iken (Mirgissa) : repousser la frontière" }
    { group:144, id:60, text: "Sawu (Mersa Gawasis) : nouveaux marchands" }
    { group:144, id:61, text: "Moyen Empire" }
    { group:144, id:62, text: "Heh (Semna) : anciens et nouveaux ennemis" }
    { group:144, id:63, text: "Bubastis : les joyaux de la couronne d'Egypte" }
    { group:144, id:64, text: "Deuxième période intermédiaire" }
    { group:144, id:65, text: "Khnoum (Hermopolis) : vengeance" }
    { group:144, id:66, text: "Sauty (Lycopolis) : inspiration" }
    { group:144, id:67, text: "Nouvel Empire : conquête ou paix ?" }
    { group:144, id:68, text: "Byblos : invasion de la Palestine" }
    { group:144, id:69, text: "Baki (Kuban) : l'âge d'or" }
    { group:144, id:70, text: "Mission finale" }
    { group:144, id:71, text: "Het ouaret (Avaris) : le monde est à nous" }
    { group:144, id:72, text: "Hetep Sénousret (Kahoun) : la grande pyramide" }
    { group:145, id:0, text: "Il n'est pas question de gagner ou de perdre dans cette mission. Il s'agit purement et simplement de la construction d'une cité." }
    { group:146, id:0, text: "Si vous réussissez à lire ce message, cliquez sur OK. Sinon, l'écran reviendra à la résolution d'origine dans 10 secondes." }
    { group:146, id:1, text: "Emplacement de royaume non choisi." }
    { group:146, id:2, text: "J'utilise l'emplacement par défaut." }
    { group:146, id:3, text: "Afficher l'écran du royaume" }
    { group:147, id:0, text: "Bien joué ! En alimentant ce village en nourriture, vous avez réussi à surpasser le rude environnement égyptien. Vous avez contribué à l'essor de cette civilisation naissante." }
    { group:147, id:1, text: "Excellent ! Vous venez de construire la première véritable cité dans cet environnement impitoyable. Vous avez contribué au développement d'une dynastie puissante et durable au sein de la confédération thinite." }
    { group:147, id:2, text: "Formidable ! Vos propres citoyens commencent à vous considérer comme leur bienfaiteur et les cités voisines comptent également sur vous." }
    { group:147, id:3, text: "Bien joué ! Grâce à votre gestion efficace, la civilisation égyptienne a considérablement progressé et cette progression devrait se poursuivre dans les décennies à venir." }
    { group:147, id:4, text: "Félicitations ! Vous avez construit une capitale digne des vivants et des morts. Grâce au développement des relations commerciales avec les autres villes, votre cité est désormais connue sur la scène internationale." }
    { group:147, id:5, text: "Le pharaon est fier de vous. Grâce à une gestion efficace, vous avez réussi à défendre votre cité contre l'attaque des Bédouins et avez doté l'Egypte des moyens de se défendre." }
    { group:147, id:6, text: "Le pharaon est satisfait. Vous avez maîtrisé les forces maritimes et fluviales et utilisé ces ressources à bon escient. La puissante flotte que vous avez créée patrouille les voies d'eau et assure la sécurité de nos rivages." }
    { group:147, id:7, text: "Le pharaon apprécie votre travail. Vous avez su exploiter au mieux les ressources fluviales et maritimes, en défendant nos rivages grâce à une flotte réduite mais efficace. Vous avez en outre honoré les membres de la noblesse en leur construisant des tombes." }
    { group:147, id:8, text: "Bien joué ! Vous avez réussi à sécuriser une route de commerce importante et à construire une cité prospère qui subvient aux besoins de tous les citoyens sans exception." }
    { group:147, id:9, text: "Bien joué ! Vous avez construit une cité qui sert de modèle aux autres cités égyptiennes et que la Nubie vous envie." }
    { group:147, id:10, text: "L'exploit que vous avez accompli est incroyable. Grâce à votre sagesse, une pyramide plus imposante que jamais s'élève dans le ciel et garantit l'immortalité à votre cher pharaon." }
    { group:147, id:11, text: "Vous avez surpassé les dangers du Sinaï et avez offert aux Egyptiens une grande quantité de cuivre et de pierres précieuses. Vos actes seront loués pendant plusieurs générations." }
    { group:147, id:12, text: "Excellent ! La nécropole royale que vous avez construite est absolument splendide et les années de loyaux services de votre famille sont largement récompensés par la tombe sacrée qui vous appartient." }
    { group:147, id:13, text: "Grâce à vos compétences, l'Egypte possède désormais une partie de la Nubie. La cité que vous avez construite révèle la puissance, la richesse et la grandeur de l'Egypte aux Nubiens conquis." }
    { group:147, id:14, text: "Le pharaon vous félicite. La pyramide penchée que vous avez construite en son honneur est magnifique et surpasse tous les monuments construits jusque-là." }
    { group:147, id:15, text: "Formidable ! Vous avez joué un rôle crucial à un moment important : la construction de la première vraie pyramide. Avec la construction de la pyramide de Snéfrou, vous avez défini la norme de construction des pyramides." }
    { group:147, id:16, text: "Extraordinaire ! En dépit de la pauvreté et de la menace continuelle des féroces Ethiopiens, vous avez construit une magnifique cité et avez consolidé la rive sud de l'Egypte." }
    { group:147, id:17, text: "Splendide ! Les mines que vous avez établies à Tura ont fourni tout le calcaire demandé par Koufou jusqu'ici. Grâce à l'économie ainsi générée, votre cité a progressé sur les plans culturel et social." }
    { group:147, id:18, text: "Tous les Egyptiens s'inclinent devant vos réalisations. Vous avez construit la pyramide de Koufou et l'avez ornée des plus riches offrandes funéraires possibles. Vous avez également honoré Khafra en construisant sa dernière demeure et son magnifique sphinx." }
    { group:147, id:19, text: "Bien joué ! Vous avez su exploiter au mieux les ressources limitées et avez apporté la puissance de Rê à cet endroit isolé." }
    { group:147, id:20, text: "Parfait. Le magnifique temple solaire que vous avez construit honore Rê et le pharaon." }
    { group:147, id:21, text: "Vous avez réussi à subvenir aux besoins de votre peuple tandis que l'Egypte s'effondre autour de vous. Les compétences de votre famille seront fort utiles à l'Egypte dans la période à venir." }
    { group:147, id:22, text: "Tandis que l'Egypte s'effondre autour de vous, vous avez réussi à maintenir votre cité debout. Ces compétences seront fort utiles à l'Egypte dans la période à venir." }
    { group:147, id:23, text: "Même durant les périodes de forts troubles, les grandes capacités de gestion de votre famille ont permis à This de retrouver son ancienne gloire. Le courage de votre force armée a permis aux Inyotefs de vaincre leurs rivaux ; ceci ne sera pas oublié." }
    { group:147, id:24, text: "Grâce à votre empressement, vous avez nourri un peuple affamé durant une période de guerre et leur avez offert les renforts nécessaires pour vaincre leurs énnemis une fois pour toutes. Vos exploits ne sont pas près d'être oubliés." }
    { group:147, id:25, text: "Vos efforts sans relâche ont permis d'établir une nouvelle cité magnifique. Vous avez également fait beaucoup pour l'Egypte dans son ensemble, en nourrissant un peuple affamé. Vos efforts seront récompensés." }
    { group:147, id:26, text: "Les magnifiques pyramides et obélisques que vous avez construits en mon honneur illustrent mon règne et je vous en suis infiniment reconnaissant. Vous en serez récompensé." }
    { group:147, id:27, text: "Grâce à votre dévotion envers votre peuple, l'Egypte vous accepte désormais en tant que pharaon et compte sur votre dynastie pour produire des héritiers de votre acabit." }
    { group:147, id:28, text: "Tout le monde s'incline devant vous, ô puissant pharaon. Vous avez conquis le nord de la Nubie en fournissant au port de notre mer rouge les ressources nécessaires à son essor, tout en assurant une source de cuivre fiable à nos forces militaires." }
    { group:147, id:29, text: "Tout le monde loue la sagesse et la puissance du pharaon. Le nouveau port de commerce de la mer rouge est en plein essor et, grâce à votre aide, un poste de commerce d'égale valeur a été établi en Nubie." }
    { group:147, id:30, text: "Seth est très fier de vous, ô puissant pharaon. Vous avez repoussé les Nubiens et renforcé votre rivage sud." }
    { group:147, id:31, text: "La glorieuse ville de Bubastis et toute l'Egypte avec elle vous rendent hommage, ô puissant pharaon." }
    { group:147, id:32, text: "L'Egypte se réjouit ! Les Hyksos ont été expulsés de nos terres sous votre commandement." }
    { group:147, id:33, text: "Sous votre commandement, les généraux ont remporté de grandes victoires. Les Hyksos et leurs chars ont été expulsés d'Egypte." }
    { group:147, id:34, text: "Ô pharaon tout-puissant ! en repoussant les Hittites, l'Egypte est devenu un empire considérable ! Votre épée a fait connaître la civilisation égyptienne au monde entier." }
    { group:147, id:35, text: "Ô paisible pharaon ! Votre influence a donné une nouvelle grandeur à l'Egypte !" }
    { group:147, id:36, text: "Ô puissant pharaon ! Votre dynastie est sans égal et les Egyptiens scanderont votre nom pour les siècles des siècles." }
    { group:147, id:37, text: "Ô puissant pharaon ! Votre dynastie est sans égal et les Egyptiens scanderont votre nom pour les siècles des siècles." }
    { group:147, id:38, text: "Bien joué. La tombe de Thoutmôsis I est terminée. C'est une œuvre superbe ! Nul doute qu'une tombe aussi magnifiquement décorée comblera les dieux et accélérera le voyage du pharaon dans l'au-delà." }
    { group:147, id:39, text: "C'est impressionnant ! Il est rare en effet que des ouvriers soumis à une telle pression produisent un travail d'une telle qualité. La tombe de Toutankhamon est maintenant scellée pour l'éternité. Espérons que les pillards ne découvriront jamais son lieu de repos éternel !" }
    { group:147, id:40, text: "Beau travail ! Vous avez bien protégé les tombes royales de la Vallée et achevé la construction de la nouvelle tombe en temps voulu. Le pharaon Séthi est très satisfait du travail de vos ouvriers." }
    { group:147, id:41, text: "Beau travail ! Notre grand pharaon, Ramsès II, ne s'est pas trompé en vous choisissant pour contrôler le développement commercial et militaire de cette terre. Mais le danger est toujours présent ! Les armées hittites revendiquent le contrôle de cette région." }
    { group:147, id:42, text: "La main du pharaon a de nouveau frappé les Hittites. Tout le monde loue le courage de notre chef, Ramsès II ! Votre splendide victoire restera à jamais dans les annales de l'Histoire." }
    { group:147, id:43, text: "Beau travail ! Ramsès II est très satisfait du monument colossal que vous avez construit en son honneur à Abou Simbel." }
    { group:147, id:44, text: "Bien joué ! Malgré une série ininterrompue de fléaux et autres calamités, la tombe de notre pharaon est prête. Sa splendeur est à l'image de Ramsès II, l'un des plus grands souverains que l'Egypte ait jamais connu." }
    { group:147, id:45, text: "Le soleil a dissipé l'orage qui planait sur l'Egypte. Quelle soulagement ! Le chef des Libu et ses alliés ont profité de la nuit pour s'enfuir. Leur funeste plan de débarquement sur nos côtes a lamentablement échoué. Nous avons même l'avantage d'avoir pu capturer un grand nombre de leurs épouses et enfants." }
    { group:147, id:46, text: "Bien joué ! Votre courage au combat a motivé vos troupes, qui se sont battues sans relâche. Les Assyriens ont été repoussés hors du sol égyptien. Le pharaon, qui a entendu parler de vos exploits, en est ravi." }
    { group:147, id:47, text: "Gloire au héros de Tanis, protecteur d'Egypte ! Vos victoires glorieuses sur terre comme sur mer ont permis d'assurer la pérennité de l'indépendance égyptienne. Les Perses, autrefois puissants, tremblent en entendant le récit des exploits du pharaon Achoris." }
    { group:147, id:48, text: "Bien joué. Grâce à votre commandement avisé, Alexandrie est désormais au centre du commerce sur le bassin méditerranéen. Quel dommage qu'Alexandre le Grand n'ait jamais vu la capitale de son empire. Nous avons au moins la satisfaction de savoir qu'il repose désormais en paix." }
    { group:147, id:49, text: "La métropole d'Alexandrie se dresse désormais fièrement ! Sa grande bibliothèque est un temple du savoir inégalé, et le phare de Pharos est désormais l'une des plus grandes merveilles du monde." }
    { group:147, id:50, text: "Vos légions puissantes ont repoussé Ptolémée XIII. Son corps inanimé a été sorti du Nil pour prouver sa mort. Le siège est levé et Cléopâtre est désormais sur son trône. Pour célébrer cette victoire et sceller leur relation, César et Cléopâtre sont partis en voyage à bord d'une luxueuse barge royale." }
    { group:147, id:51, text: "Les splendeurs d'Alexandrie et le sort de l'Egypte sont entre de bonnes mains grâce à votre commandement. Comme prévu, Marc-Antoine, honoré de votre présence, vous a demandé une aide financière. Il est tombé si amoureux de vous qu'il est venu à Alexandrie pour devenir votre compagnon et amant." }
    { group:147, id:52, text: "Grâce au génie tactique d'Antoine et aux joyaux de Cléopâtre, la flotte et les légions d'Octave se sont dispersées aux quatre vents. Les Romains attendent avec impatience le retour triomphal d'Antoine et Cléopâtre. Main dans la main, Rome et Alexandrie règneront sur le bassin méditerranéen pendant des générations." }
    { group:147, id:53, text: "Victoire carte personnalisée" }
    { group:147, id:54, text: "Vous avez bien joué, mais bien d'autres défis vous attendent pour devenir un pharaon !" }
    { group:148, id:5, text: "Trésorerie finale" }
    { group:148, id:6, text: "Monuments construits" }
    { group:148, id:7, text: "Mission terminée en" }
    { group:148, id:8, text: "Niveau le plus bas utilisé :" }
    { group:148, id:9, text: "Score" }
    { group:148, id:10, text: "Félicitations. Vous pouvez revenir et tenter de battre votre record en cliquant sur le bouton 'Choisir une mission'." }
    { group:148, id:11, text: "Vous avez mieux joué la dernière fois." }
    { group:148, id:12, text: "Bravo ! Vous avez battu votre record !" }
    { group:148, id:13, text: "Vous avez réussi cette mission, mais [player_name] règne toujours sur cette cité." }
    { group:148, id:14, text: "Vous menez maintenant au score ! Vous avez battu [player_name]." }
    { group:148, id:15, text: "mois" }
    { group:148, id:16, text: "Vous avez triché ! Vous ne pouvez pas faire partie des meilleures familles." }
    { group:149, id:0, text: "Requête générale" }
    { group:149, id:1, text: "Cité égyptienne attaquée" }
    { group:149, id:2, text: "Bataille lointaine" }
    { group:149, id:3, text: "Fête" }
    { group:149, id:4, text: "Constructions" }
    { group:149, id:5, text: "Famine" }
    { group:149, id:6, text: "Menace" }
    { group:150, id:0, text: "Cité égyptienne sauvée" }
    { group:150, id:1, text: "bataille lointaine gagnée" }
    { group:150, id:2, text: "bataille lointaine perdue" }
    { group:150, id:3, text: "rapport" }
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
    { group:151, id:32, text: "Reine Merneith" }
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
    { group:151, id:57, text: "Reine Sobknefru" }
    { group:151, id:58, text: "Teti" }
    { group:151, id:59, text: "Unas" }
    { group:151, id:60, text: "Userkaf" }
    { group:151, id:61, text: "Userkara" }
    { group:151, id:62, text: "Weneg" }
    { group:151, id:63, text: "Ahmosis I" }
    { group:151, id:64, text: "Amenhotep I" }
    { group:151, id:65, text: "Thoutmôsis I" }
    { group:151, id:66, text: "Thoutmôsis II" }
    { group:151, id:67, text: "Hatshepsut" }
    { group:151, id:68, text: "Thoutmôsis III" }
    { group:151, id:69, text: "Amenhotep II" }
    { group:151, id:70, text: "Thoutmôsis IV" }
    { group:151, id:71, text: "Amenhotep III" }
    { group:151, id:72, text: "Akhnaton" }
    { group:151, id:73, text: "Neferneferuaten" }
    { group:151, id:74, text: "Smenkhkare" }
    { group:151, id:75, text: "Toutankhamon" }
    { group:151, id:76, text: "Ay" }
    { group:151, id:77, text: "Horemheb" }
    { group:151, id:78, text: "Ramsès I" }
    { group:151, id:79, text: "Séthi I" }
    { group:151, id:80, text: "Ramsès II" }
    { group:151, id:81, text: "Merneptah" }
    { group:151, id:82, text: "Amménémès" }
    { group:151, id:83, text: "Séthi II" }
    { group:151, id:84, text: "Siptah" }
    { group:151, id:85, text: "Reine Twosret" }
    { group:151, id:86, text: "Setnakhte" }
    { group:151, id:87, text: "Ramsès III" }
    { group:151, id:88, text: "Ramsès IV" }
    { group:151, id:89, text: "Ramsès V" }
    { group:151, id:90, text: "Ramsès VI" }
    { group:151, id:91, text: "Ramsès VII" }
    { group:151, id:92, text: "Ramsès VIII" }
    { group:151, id:93, text: "Ramsès IX" }
    { group:151, id:94, text: "Ramsès X" }
    { group:151, id:95, text: "Ramsès XI" }
    { group:151, id:96, text: "Piye" }
    { group:151, id:97, text: "Shabaka" }
    { group:151, id:98, text: "Shebitku" }
    { group:151, id:99, text: "Taharqa" }
    { group:151, id:100, text: "Tantamani" }
    { group:151, id:101, text: "Nepherites I" }
    { group:151, id:102, text: "Psammuthis" }
    { group:151, id:103, text: "Nefaarud I" }
    { group:151, id:104, text: "Hakor" }
    { group:151, id:105, text: "Naktnebef" }
    { group:151, id:106, text: "Alexandre le Grand" }
    { group:151, id:107, text: "Philippe Arrhidaeus" }
    { group:151, id:108, text: "Alexandre IV" }
    { group:151, id:109, text: "Ptolémée I" }
    { group:151, id:110, text: "Ptolémée II" }
    { group:151, id:111, text: "Ptolémée III" }
    { group:151, id:112, text: "Ptolémée IV" }
    { group:151, id:113, text: "Ptolémée V" }
    { group:151, id:114, text: "Ptolémée VI" }
    { group:151, id:115, text: "Ptolémée VII" }
    { group:151, id:116, text: "Ptolémée VIII" }
    { group:151, id:117, text: "Ptolémée IX" }
    { group:151, id:118, text: "Ptolémée X" }
    { group:151, id:119, text: "Ptolémée XI" }
    { group:151, id:120, text: "Ptolémée XII" }
    { group:151, id:121, text: "Reine Bernice IV" }
    { group:151, id:122, text: "Ptolémée XIII" }
    { group:151, id:123, text: "Cléopâtre VII" }
    { group:151, id:124, text: "Ptolémée XV" }
    { group:152, id:0, text: "Aucune" }
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
    { group:155, id:0, text: "Barrage routier" }
    { group:155, id:1, text: "Placez des barrages routiers pour limiter les patrouilles sur les routes. Les personnes ayant une destination bien définie (tels que les charretiers ou les acheteurs de bazar) peuvent circuler librement." }
    { group:156, id:0, text: "Evénement gratuit" }
    { group:156, id:1, text: "Requête" }
    { group:156, id:2, text: "Invasion" }
    { group:156, id:3, text: "Tremblement de terre" }
    { group:156, id:4, text: "Révolte" }
    { group:156, id:5, text: "Changer de pharaon" }
    { group:156, id:6, text: "Problème de route maritime" }
    { group:156, id:7, text: "Problème de route terrestre" }
    { group:156, id:8, text: "Hausse de salaire" }
    { group:156, id:9, text: "Baisse de salaire" }
    { group:156, id:10, text: "Eau contaminée" }
    { group:156, id:11, text: "Effondrement de la mine d'or" }
    { group:156, id:12, text: "Débordement du puits d'argile" }
    { group:156, id:13, text: "Augmentation de la demande" }
    { group:156, id:14, text: "Diminution de la demande" }
    { group:156, id:15, text: "Augmentation des prix" }
    { group:156, id:16, text: "Diminution des prix" }
    { group:156, id:17, text: "Augmentation du royaume" }
    { group:156, id:18, text: "Diminution du royaume" }
    { group:156, id:19, text: "Modif. du statut de la cité" }
    { group:156, id:20, text: "Message" }
    { group:156, id:21, text: "Echec de la crue" }
    { group:156, id:22, text: "Crue parfaite" }
    { group:156, id:23, text: "Cadeau" }
    { group:156, id:24, text: "Attaque de criquets" }
    { group:156, id:25, text: "Attaque de grenouilles" }
    { group:156, id:26, text: "Orage de grêle" }
    { group:156, id:27, text: "Fleuve de sang" }
    { group:156, id:28, text: "Vague de criminalité" }
    { group:156, id:29, text: "Momie" }
    { group:157, id:0, text: "Osiris" }
    { group:157, id:1, text: "Rê" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Seth" }
    { group:157, id:4, text: "Bastet" }
    { group:157, id:5, text: "Hermie" }
    { group:157, id:6, text: "Janus" }
    { group:158, id:0, text: "Dieu de l'agriculture et de l'inondation par le Nil" }
    { group:158, id:1, text: "Dieu du royaume" }
    { group:158, id:2, text: "Dieu des artisans" }
    { group:158, id:3, text: "Dieu de la destruction" }
    { group:158, id:4, text: "Déesse du foyer" }
    { group:158, id:5, text: "(Dentisterie)" }
    { group:158, id:6, text: "(Tout)" }
    { group:159, id:0, text: "Arrivée de la navette" }
    { group:159, id:1, text: "ATTENTION ! Cet embarcadère ne dispose pas d'une zone adéquate sur le fleuve. Seuls les émigrants peuvent traverser." }
    { group:159, id:2, text: "ATTENTION ! Cette navette ne peut pas circuler correctement, la zone qui lui est associée n'est pas suffisamment accessible. Seuls les émigrants peuvent traverser." }
    { group:159, id:3, text: "ATTENTION ! Cette navette ne peut pas circuler correctement, car la zone qui lui est associée n'a pas suffisamment de main-d'œuvre. Seuls les émigrants peuvent traverser." }
    { group:160, id:0, text: "janvier" }
    { group:160, id:1, text: "février" }
    { group:160, id:2, text: "mars" }
    { group:160, id:3, text: "avril" }
    { group:160, id:4, text: "mai" }
    { group:160, id:5, text: "juin" }
    { group:160, id:6, text: "juillet" }
    { group:160, id:7, text: "août" }
    { group:160, id:8, text: "septembre" }
    { group:160, id:9, text: "octobre" }
    { group:160, id:10, text: "novembre" }
    { group:160, id:11, text: "décembre" }
    { group:161, id:0, text: "Sanctuaire d'Osiris" }
    { group:161, id:1, text: "Osiris fertilise la terre et facilite les cultures. Apaisez-le, ou préparez-vous à mourir de faim." }
    { group:161, id:2, text: "Sanctuaire de Rê (royaume)" }
    { group:161, id:3, text: "Les marchands connaissent bien l'importance de satisfaire Rê. Le commerce est plus sûr et plus profitable avec la bénédiction de Rê, qui accorde ainsi plus d'intérêt à votre cité." }
    { group:161, id:4, text: "Sanctuaire de Ptah (artisans)" }
    { group:161, id:5, text: "Ouvriers et artisans vouent un culte à Ptah pour qu'il facilite leur dur labeur. Lorsque Ptah est en colère, aucune industrie n'est sûre d'échapper à la catastrophe." }
    { group:161, id:6, text: "Sanctuaire de Seth (destruction)" }
    { group:161, id:7, text: "Seth surveille les soldats et encourage la bravoure au combat. Nul n'ose se battre sans la bénédiction de Seth." }
    { group:161, id:8, text: "Sanctuaire de Bastet (foyer)" }
    { group:161, id:9, text: "Lorsque Bastet est mécontente, aucun foyer n'est en sécurité. Cette déesse est aussi considérée comme responsable des maladies." }
    { group:162, id:0, text: "Mine d'or" }
    { group:162, id:1, text: "L'exploitation de l'or est le moyen le plus sûr de remplir les caisses de votre cité. Bien heureuse est la cité qui possède cette source de richesse." }
    { group:162, id:2, text: "Production à" }
    { group:162, id:3, text: "terminée." }
    { group:162, id:4, text: "Le chef du commerce a ordonné l'interruption de l'extraction d'or." }
    { group:162, id:5, text: "Cette mine n'emploie personne. La production est inexistante." }
    { group:162, id:6, text: "Cette mine dispose de toute la main-d'œuvre nécessaire et sa production d'or est abondante." }
    { group:162, id:7, text: "Cette mine fonctionne en dessous de sa capacité maximale. La production pourrait être légèrement améliorée si elle disposait de main-d'œuvre supplémentaire." }
    { group:162, id:8, text: "Cette mine ne dispose pas d'une main-d'œuvre suffisante. La production d'or est moins forte que prévue." }
    { group:162, id:9, text: "Seuls quelques employés travaillent ici. La production est donc ralentie." }
    { group:162, id:10, text: "Seuls quelques employés travaillent ici. Le rendement a donc considérablement diminué, et la production risque d'être très faible." }
    { group:163, id:0, text: "Mine de pierres précieuses" }
    { group:163, id:1, text: "Exploitez des pierres précieuses pour l'exportation ou pour la fabrication de bijoux, le principal article de luxe de votre cité." }
    { group:163, id:2, text: "Production à" }
    { group:163, id:3, text: "terminée." }
    { group:163, id:4, text: "Votre chef du commerce a décrété que la cité disposait d'une quantité suffisante de pierres précieuses et a donc ordonné l'arrêt de l'extraction." }
    { group:163, id:5, text: "Cette mine n'emploie personne. La production est inexistante." }
    { group:163, id:6, text: "Cette mine dispose de toute la main-d'œuvre nécessaire et sa production de pierres précieuses est abondante." }
    { group:163, id:7, text: "Cette mine fonctionne en dessous de sa capacité maximale. La production pourrait être légèrement améliorée si elle disposait de main-d'œuvre supplémentaire." }
    { group:163, id:8, text: "Cette mine ne dispose pas d'une main-d'œuvre suffisante. La production de pierres précieuses est moins forte que prévue." }
    { group:163, id:9, text: "Seuls quelques employés travaillent ici. La production est donc ralentie." }
    { group:163, id:10, text: "Seuls quelques employés travaillent ici. L'extraction de pierres précieuses est donc quasiment nulle." }
    { group:164, id:0, text: "Caserne de pompiers" }
    { group:164, id:1, text: "Les casernes envoient des capitaines des pompiers dans la cité pour empêcher tout incendie de se déclarer et éteindre les incendies en cours." }
    { group:164, id:2, text: "Notre capitaine effectue sa patrouille." }
    { group:164, id:3, text: "Notre capitaine se prépare." }
    { group:164, id:4, text: "Nous manquons d'effectifs. Nos capitaines des pompiers sont toujours en patrouille dans les rues." }
    { group:164, id:5, text: "Nous manquons de capitaines. Nous sommes en retard d'un jour ou deux sur notre programme." }
    { group:164, id:6, text: "Nous manquons d'effectifs, et il se passe des fois une semaine sans que personne ne soit envoyé en patrouille." }
    { group:164, id:7, text: "Notre effectif est bien trop insuffisant. Les capitaines quittent souvent la caserne pour tout au plus deux semaines." }
    { group:164, id:8, text: "Nous manquons d'employés. Il se passe souvent un mois entier sans qu'un capitaine soit envoyé en patrouille." }
    { group:164, id:9, text: "Sans employés, cette caserne est vouée à partir en fumée." }
    { group:165, id:0, text: "Mur de briques" }
    { group:165, id:1, text: "Les murs défendent votre cité des invasions, mais ne sont pas indestructibles. Plus ils sont épais, plus ils sont solides, et des soldats peuvent les patrouiller" }
    { group:166, id:0, text: "Mur" }
    { group:166, id:1, text: "Les murs défendent votre cité des invasions, mais ne sont pas indestructibles. Plus ils sont épais, plus ils sont solides, et des soldats peuvent les patrouiller" }
    { group:167, id:0, text: "Corps de garde en brique" }
    { group:167, id:1, text: "Les corps de garde permettent de surveiller le passage des citoyens et des marchands." }
    { group:168, id:0, text: "Corps de garde" }
    { group:168, id:1, text: "Les corps de garde permettent de surveiller le passage des citoyens et des marchands." }
    { group:169, id:0, text: "Tour en brique" }
    { group:169, id:1, text: "Espacez les tours de vos murs à intervalles réguliers, surtout dans les zones vulnérables. Des gardes sont envoyés dans les tours par le centre de recrutement de la cité, lorsque ces dernières sont reliées à des routes. Les gardes envoient une nuée de javelots sur les envahisseurs et patrouillent les murs épais." }
    { group:169, id:2, text: "Sans employés, nous ne pouvons ni peupler les tours, ni patrouiller les murs d'enceinte." }
    { group:169, id:3, text: "Nos hommes sont prêts à repousser toute attaque" }
    { group:169, id:4, text: "Nous disposons d'un personnel de maintenance, mais le centre de recrutement doit nous envoyer des gardes pour défendre notre cité." }
    { group:170, id:0, text: "Tour" }
    { group:170, id:1, text: "Espacez les tours de vos murs à intervalles réguliers, surtout dans les zones vulnérables. Des gardes sont envoyés dans les tours par le centre de recrutement de la cité, lorsque ces dernières sont reliées à des routes. Les gardes envoient une nuée de javelots sur les envahisseurs et patrouillent les murs épais." }
    { group:170, id:2, text: "Sans employés, nous ne pouvons ni manœuvrer les tours, ni patrouiller les murs d'enceinte." }
    { group:170, id:3, text: "Nos hommes sont prêts à repousser toute attaque" }
    { group:170, id:4, text: "Nous disposons d'un personnel de maintenance, mais le centre de recrutement doit nous envoyer des gardes pour défendre notre cité." }
    { group:171, id:0, text: "Guilde de menuisiers" }
    { group:171, id:1, text: "Les menuisiers se réunissent ici pour discuter, s'échanger des conseils sur leur profession, trouver du travail et confier leurs problèmes." }
    { group:171, id:2, text: "Production à" }
    { group:171, id:3, text: "terminée." }
    { group:171, id:4, text: "Votre chef du commerce a ordonné la fermeture de cette guilde" }
    { group:171, id:5, text: "Cette guilde n'emploie personne. La production est interrompue." }
    { group:171, id:6, text: "Cette guilde dispose de toute la main-d'œuvre nécessaire. Sa production est abondante." }
    { group:171, id:7, text: "Cette guilde fonctionne en dessous de sa capacité maximale. Le travail est donc légèrement ralenti." }
    { group:171, id:8, text: "Cette guilde ne dispose pas d'une main-d'œuvre suffisante. Le nombre de menuisiers est donc moins important que prévu." }
    { group:171, id:9, text: "Seuls quelques employés travaillent ici. Les services de menuiserie se font donc considérablement attendre." }
    { group:171, id:10, text: "Seuls quelques employés travaillent ici. Il devient donc quasiment impossible d'obtenir les services d'un menuisier." }
    { group:171, id:11, text: "Cet atelier doit recevoir une livraison de bois." }
    { group:171, id:12, text: "Bois en stock," }
    { group:172, id:0, text: "Guilde de maçons" }
    { group:172, id:1, text: "Les maçons se réunissent ici pour discuter, s'échanger des conseils sur leur profession, trouver du travail et tirer des plans sur la comète." }
    { group:172, id:2, text: "Production à" }
    { group:172, id:3, text: "terminée." }
    { group:172, id:4, text: "Votre chef du commerce a ordonné la fermeture de cette guilde" }
    { group:172, id:5, text: "Cette guilde n'emploie personne. La production de briques est interrompue." }
    { group:172, id:6, text: "Cette guilde dispose de toute la main-d'œuvre nécessaire. Les maçons sont donc particulièrement efficaces." }
    { group:172, id:7, text: "Cette guilde fonctionne en dessous de sa capacité maximale. Le travail est donc légèrement ralenti." }
    { group:172, id:8, text: "Cette guilde ne dispose pas d'une main-d'œuvre suffisante. Le nombre de maçons est donc moins important que prévu." }
    { group:172, id:9, text: "Seuls quelques employés travaillent ici. Les maçons se font donc considérablement attendre." }
    { group:172, id:10, text: "Seuls quelques employés travaillent ici. Il est donc quasiment impossible d'obtenir les services d'un maçon." }
    { group:172, id:11, text: "Cet atelier doit recevoir une livraison de bois." }
    { group:172, id:12, text: "Briques stockées" }
    { group:173, id:0, text: "Guilde de tailleurs de pierre" }
    { group:173, id:1, text: "Les tailleurs de pierre se réunissent ici pour discuter, s'échanger des conseils sur leur profession, trouver du travail et tirer des plans sur la comète." }
    { group:173, id:2, text: "Production à" }
    { group:173, id:3, text: "terminée." }
    { group:173, id:4, text: "Votre chef du commerce a ordonné la fermeture de cette guilde" }
    { group:173, id:5, text: "Cette guilde n'emploie personne. Il est donc impossible de tailler la pierre." }
    { group:173, id:6, text: "Cette guilde dispose de toute la main-d'œuvre nécessaire. Les maçons sont donc particulièrement efficaces." }
    { group:173, id:7, text: "Cette guilde fonctionne en dessous de sa capacité maximale. Le travail est donc légèrement ralenti." }
    { group:173, id:8, text: "Cette guilde ne dispose pas d'une main-d'œuvre suffisante. Le nombre de maçons est donc insuffisant." }
    { group:173, id:9, text: "Très peu de personnes travaillent ici. Les tailleurs de pierre sont attendus avec impatience." }
    { group:173, id:10, text: "Seuls quelques employés travaillent ici. Il est donc quasiment impossible d'obtenir les services d'un maçon." }
    { group:173, id:11, text: "Cette guilde fournit une main-d'œuvre qualifiée pour la construction de monuments. Elle n'a pas besoin de pierres." }
    { group:173, id:12, text: "Pierres stockées" }
    { group:174, id:0, text: "Quai de transporteurs" }
    { group:174, id:1, text: "C'est ici que les navires construits se détériorent sous l'effet du temps. Votre bataillon a besoin de transporteurs pour naviguer sur le Nil." }
    { group:174, id:2, text: "Notre transporteur est dans le port." }
    { group:174, id:3, text: "Notre transporteur effectue actuellement un transport." }
    { group:175, id:0, text: "Quai de navires de guerre" }
    { group:175, id:1, text: "C'est ici que l'on construit des navires de guerre entre les batailles. Chaque cité bordant le Nil doit disposer d'au moins deux navires de défense." }
    { group:175, id:2, text: "Notre navire de guerre est dans le port." }
    { group:175, id:3, text: "Notre navire de guerre défend actuellement la cité contre des envahisseurs." }
    { group:176, id:0, text: "Palais de justice" }
    { group:176, id:1, text: "Les palais de justice envoient des magistrats pour réduire la criminalité en faisant en sorte que chaque crime trouve un châtiment mérité. Les coffres des palais de justice constituent un élément important de la trésorerie de votre cité." }
    { group:176, id:2, text: "Ce palais de justice n'a pas du tout d'employés. Les citoyens résolvent donc leurs différends par leurs propres moyens." }
    { group:176, id:3, text: "Seuls quelques magistrats travaillent ici. Les sentences semblent donc presque aléatoires." }
    { group:176, id:4, text: "Ce palais de justice ne dispose que de la moitié de la main-d'œuvre nécessaire. Elle délivre donc parfois des jugements hâtifs." }
    { group:176, id:5, text: "Ce palais ne dispose pas de suffisamment de main-d'œuvre. Certaines affaires sont donc toujours en attente." }
    { group:176, id:6, text: "Ce palais de justice dispose de toute la main-d'œuvre nécessaire pour répondre rapidement aux plaintes des citoyens et émettre des jugements adéquats." }
    { group:176, id:7, text: "Le magistrat est en train de résoudre des différends." }
    { group:176, id:8, text: "Le magistrat est dans ses appartements." }
    { group:176, id:9, text: "Dans les coffres" }
    { group:177, id:0, text: "Cette terre est irriguée." }
    { group:177, id:1, text: "Cette terre n'est pas irriguée." }
    { group:177, id:2, text: "Les prochaines crues arrivent en" }
    { group:177, id:3, text: "Maintenant que le fleuve est descendu, cette  terre est extrêmement fertile." }
    { group:177, id:4, text: "Une fois le fleuvre redescendu, cette terre sera extrêmement fertile." }
    { group:177, id:5, text: "Cette ferme a besoin d'une main-d'œuvre formée sur des chantiers." }
    { group:177, id:6, text: "Cette ferme dispose d'une main-d'œuvre suffisante travaillant dans les champs." }
    { group:178, id:0, text: "terminée." }
    { group:178, id:1, text: "Les ouvriers achèvent actuellement l'extérieur de la pyramide." }
    { group:178, id:2, text: "Cette tâche est" }
    { group:178, id:3, text: "Les ouvriers nettoient le site pour la construction de la pyramide" }
    { group:178, id:4, text: "Les ouvriers nettoient le site pour la construction du mastaba" }
    { group:178, id:5, text: "Les ouvriers creusent des trous dans la roche pour l'eau" }
    { group:178, id:6, text: "Les trous à la base de la pyramide sont remplis d'eau" }
    { group:178, id:7, text: "L'eau s'écoule depuis le site et des marques indiquent le niveau" }
    { group:178, id:8, text: "La roche est taillée pour être à niveau" }
    { group:178, id:9, text: "Les trous sont remplis de gravats" }
    { group:178, id:10, text: "La base est nivelée et la construction de la tombe est désormais en cours" }
    { group:178, id:11, text: "La base est nivelée et le toit est placé sur la tombe" }
    { group:178, id:12, text: "Contremaître" }
    { group:178, id:13, text: "J'ai besoin de main-d'œuvre agricole pour cette construction. Il faut construire des chantiers." }
    { group:178, id:14, text: "Aucun tailleur de pierre n'est disponible pour construire ce monument. Si vous voulez que la construction avance, vous devez construire une guilde de tailleurs de pierre le plus vite possible !" }
    { group:178, id:15, text: "Comment embaucher des maçons si aucune guilde de maçons n'existe dans la cité ?" }
    { group:178, id:16, text: "Il faut que j'aie accès à une guilde de menuisiers pour construire ce monument." }
    { group:178, id:17, text: "J'attends des paysans pour travailler sur ce projet. Vous devriez peut-être visiter les chantiers pour voir s'il y a des problèmes." }
    { group:178, id:18, text: "J'attends des tailleurs de pierre pour la construction de ce monument. Une visite à la guilde des tailleurs de pierre serait peut-être profitable." }
    { group:178, id:19, text: "J'attends des maçons pour effectuer cette construction. En cas de problème, une visite à la guilde des maçons peut s'avérer utile." }
    { group:178, id:20, text: "Il me faut un menuisier sur ce chantier. Je me demande s'il n'y a pas un problème au sein de la guilde des menuisiers." }
    { group:178, id:21, text: "Mes ouvriers attendent qu'un menuisier construise un chantier, afin que nous puissions passer à l'étape suivante." }
    { group:178, id:22, text: "Mes maçons ont besoin de pierre pour construire ce monument." }
    { group:178, id:23, text: "Mes maçons ont besoin de calcaire pour construire ce monument" }
    { group:178, id:24, text: "Mes maçons ont besoin de grès pour construire ce monument." }
    { group:178, id:25, text: "Mes maçons ont besoin de granite pour construire ce monument." }
    { group:178, id:26, text: "Vous devez importer du marbre pour que les tailleurs de pierre puissent achever la construction de ce monument." }
    { group:178, id:27, text: "Mes maçons ont besoin de briques pour construire ce monument." }
    { group:178, id:28, text: "Mes menuisiers ont besoin de bois pour construire ce monument." }
    { group:178, id:29, text: "Nos ouvriers ajouteront du cuivre au plafond dès qu'il arrivera. Vous devez en produire ou en importer." }
    { group:178, id:30, text: "Les ouvriers nettoient et nivellent le site de construction. Il vous faudra ensuite une grande quantité de pierre et de calcaire pour achever ce travail." }
    { group:178, id:31, text: "Tout semble en ordre, et la pyramide ne cesse de s'élever." }
    { group:178, id:32, text: "Les maçons travaillent maintenant la pierre fine. Nous n'aurons plus besoin de calcaire." }
    { group:178, id:33, text: "Les ouvriers nettoient et nivellent le site de construction. Ensuite, nous aurons besoin d'une quantité importante de briques et de calcaire blanc pour la construction." }
    { group:178, id:34, text: "Tout semble en ordre, et la pyramide ne cesse de s'élever." }
    { group:178, id:35, text: "Les maçons travaillent maintenant la pierre fine. Nous n'aurons plus besoin de briques ni de calcaire." }
    { group:178, id:36, text: "Les ouvriers nettoient et nivellent le site de construction. Ensuite, nous aurons besoin d'une quantité importante de calcaire pour la construction." }
    { group:178, id:37, text: "Tout semble en ordre, et la pyramide continue de s'élever." }
    { group:178, id:38, text: "La pyramide est enfin terminée !" }
    { group:178, id:39, text: "Les ouvriers nettoient le site de construction. Ensuite, nous aurons besoin d'une quantité importante de briques jaunes pour le mastaba." }
    { group:178, id:40, text: "Tout semble dans l'ordre. Ce mastaba devrait être construit en un rien de temps." }
    { group:178, id:41, text: "Le mastaba est terminé." }
    { group:178, id:42, text: "Finalement, nous disposons de tout le granit nécessaire. Lorsque mes menuisiers auront terminé la construction de l'échafaudage, les maçons pourront commencer à sculpter l'obélisque." }
    { group:178, id:43, text: "Mes maçons sculptent actuellement l'immense obélisque." }
    { group:178, id:44, text: "L'obélisque est terminé." }
    { group:178, id:45, text: "Les maçons créent actuellement la forme du sphinx." }
    { group:178, id:46, text: "Les maçons sculptent actuellement le sphinx." }
    { group:178, id:47, text: "Les menuisiers peignent actuellement le sphinx." }
    { group:178, id:48, text: "Le sphinx est terminé." }
    { group:178, id:49, text: "La menuiserie est à" }
    { group:178, id:50, text: "La maçonnerie est à" }
    { group:178, id:51, text: "A cette époque de l'année, la majeure partie de la main-d'œuvre agricole travaille sur les exploitations des plaines inondables." }
    { group:178, id:52, text: "L'accès à ce monument est bloqué." }
    { group:178, id:53, text: "Maintenant que nous disposons de suffisamment de grès, nous pouvons commencer la construction du temple solaire. Mes ouvriers sont en train de nettoyer le site de construction." }
    { group:178, id:54, text: "Une fois que mes menuisiers auront terminé la construction de l'échafaudage, les maçons pourront commencer à sculpter l'obélisque central du temple solaire." }
    { group:178, id:55, text: "Mes maçons construisent actuellement l'obélisque central. Lorsqu'ils auront terminé, il nous faudra davantage de calcaire pour terminer la construction du temple solaire." }
    { group:178, id:56, text: "Dès que nous auront terminé la construction du vestibule, des murs et de l'avant-temple, ce monument sera terminé." }
    { group:178, id:57, text: "Le temple solaire est terminé." }
    { group:178, id:58, text: "Maintenant que nous disposons de suffisamment de grès, nous pouvons commencer la construction de ce monument. Mes ouvriers sont en train de nettoyer le site de construction." }
    { group:178, id:59, text: "Mes maçons travaillent dur pour achever la construction de ce mausolée. Si nous recevons suffisamment de calcaire, la construction ne devrait pas poser de problème." }
    { group:178, id:60, text: "Le mausolée est terminé." }
    { group:178, id:61, text: "[monument_name] : monument achevé à [percent_complete]." }
    { group:178, id:62, text: "Aucune voie n'est achevée pour le moment." }
    { group:178, id:63, text: "Une voie est achevée." }
    { group:178, id:64, text: "[number_courses_complete] voies sont entièrement achevées." }
    { group:178, id:65, text: "La construction de cette voie nécessite encore [quantity_needed_current_course_main] ([number_loads_current_course_main])." }
    { group:178, id:66, text: "La construction de la voie nécessite encore [quantity_needed_current_course_main] ([number_loads_current_course_main])." }
    { group:178, id:67, text: "La construction de la voie nécessite encore [quantity_needed_current_course_main] ([number_loads_current_course_main]) et [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary])." }
    { group:178, id:68, text: "[monument_name] : nécessite encore [quantity_needed_remainder_main] ([number_loads_remainder_main])." }
    { group:178, id:69, text: "[monument_name] : nécessite encore [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:70, text: "[monument_name] : nécessite encore [quantity_needed_remainder_main] ([number_loads_remainder_main]) et [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:71, text: "[monument_name] : maintenant terminé ; contient un total de [quantity_total_main]." }
    { group:178, id:72, text: "[monument_name] : maintenant terminé ; contient un total de [quantity_total_main] et [quantity_total_secondary]." }
    { group:178, id:73, text: "Mastaba" }
    { group:178, id:74, text: "Pyramide" }
    { group:178, id:75, text: "Pyramide à degrés" }
    { group:178, id:76, text: "Pyramide penchée" }
    { group:178, id:77, text: "Pyramide en brique" }
    { group:178, id:78, text: "Obélisque" }
    { group:178, id:79, text: "Sphinx" }
    { group:178, id:80, text: "Temple solaire" }
    { group:178, id:81, text: "Bibliothèque d'Alexandrie" }
    { group:178, id:82, text: "Abou Simbel" }
    { group:178, id:83, text: "Petite Tombe Royale" }
    { group:178, id:84, text: "Tombe Royale Moyenne" }
    { group:178, id:85, text: "Grande Tombe Royale" }
    { group:178, id:86, text: "Très Grande Tombe Royale" }
    { group:178, id:87, text: "Caesareum" }
    { group:178, id:88, text: "Phare" }
    { group:178, id:89, text: "Mausolée" }
    { group:178, id:90, text: "Blocs de pierre" }
    { group:178, id:91, text: "blocs de calcaire" }
    { group:178, id:92, text: "blocs de granite" }
    { group:178, id:93, text: "blocs de grès" }
    { group:178, id:94, text: "briques" }
    { group:178, id:95, text: "blocs de marbre" }
    { group:178, id:96, text: "lingots de cuivre" }
    { group:178, id:97, text: "Ce mausolée requiert les services d'un menuisier." }
    { group:178, id:98, text: "Le chef du commerce refuse de fournir de la pierre à mes ouvriers. Il dit que vous avez ordonné le stockage de cette denrée. Je ne le crois pas, mais vous devriez peut-être le remettre à sa place." }
    { group:178, id:99, text: "Votre chef du commerce dit que vous lui avez ordonné de stocker le calcaire. Si vous ne lui parlez pas, mes ouvriers ne recevront jamais de livraison." }
    { group:178, id:100, text: "Avez-vous vraiment ordonné au chef du commerce de stocker le grès ? Il n'autorise aucun transport de marchandises depuis les entrepôts." }
    { group:178, id:101, text: "Pouvez-vous demander au chef du commerce de ne plus stocker le marbre blanc ? Il s'avère utile pour le monument." }
    { group:178, id:102, text: "Votre chef du commerce dit que vous lui avez demandé de stocker du granit. Vous devez lui parler, sinon nous ne recevrons pas de livraison." }
    { group:178, id:103, text: "Votre chef du commerce ose vous accuser de l'interruption des travaux ! Il dit que vous avez ordonné le stockage des briques." }
    { group:178, id:104, text: "Le chef du commerce vous aurait ordonné de stocker le cuivre. Je suis sûr que vos raisons sont bonnes, mais mes hommes ne peuvent pas continuer à travailler sur le monument sans ce matériau." }
    { group:178, id:105, text: "Le pharaon sera mécontent si son histoire n'est pas retranscrite de la manière la plus élégante qui soit. Sans guilde d'artisans, comment comptez-vous décorer sa tombe ?" }
    { group:178, id:106, text: "Drôle de tombe, n'est-ce pas ? Elle risque de rester dans cet état si des artisans n'arrivent pas bientôt ! J'ai toujours pensé qu'ils étaient paresseux. Regardez plutôt le délai de construction." }
    { group:178, id:107, text: "Sans marbre, nos talentueux tailleurs de pierre ne peuvent rien faire. C'est bien dommage, car j'aimerais les voir occupés. Je vous conseille de faire importer du marbre le plus rapidement possible." }
    { group:178, id:108, text: "Il faut du cuivre pour éviter l'effondrement du plafond. Si vous ne pouvez pas en produire, vous devez en importer. La construction du monument en dépend !" }
    { group:178, id:109, text: "Les ouvriers nettoient et aplanissent la terre. Il est temps de rassembler une bonne quantité de marbre." }
    { group:178, id:110, text: "Le travail progresse bien. Les ouvriers ont tout ce qui leur faut." }
    { group:178, id:111, text: "C'est difficile à croire, mais le chef du commerce m'informe que du marbre s'empile inutilement dans nos entrepôts. Sans marbre, comment pourrez-vous continuer ?" }
    { group:178, id:112, text: "Je sais de source sûre que des stocks de granit sont constitués. Où croyez-vous que je trouverai le granit dont j'ai besoin, dans les sables du NIl, peut-être ? Veillez à ce que mes tailleurs de pierre reçoivent du granit dans les meilleurs délais." }
    { group:178, id:113, text: "Sans cuivre, comment pensez-vous pouvoir terminer la pose du plafond de cette structure gigantesque ? Aussi étrangère que cela puisse paraître, votre chef du commerce m'a dit qu'il en stockait actuellement." }
    { group:178, id:114, text: "Les paysans doivent nettoyer la terre." }
    { group:178, id:115, text: "La terre est nettoyée, les tailleurs de pierre posent les fondations." }
    { group:178, id:116, text: "Les fondations sont posées, le sol peut être mis en place." }
    { group:178, id:117, text: "Le sol est en place, nous montons quelques colonnes." }
    { group:178, id:118, text: "Les colonnes sont montées et le toit va être posé." }
    { group:178, id:119, text: "Nous avons maintenant besoin de cuivre pour que le toit brille de mille feux." }
    { group:178, id:120, text: "Nous apportons les touches finales à la bibliothèque." }
    { group:178, id:121, text: "La bibliothèque est achevée. C'est le plus grand temple du savoir au monde." }
    { group:178, id:122, text: "Les paysans travaillent dur pour nettoyer la terre du Caesareum." }
    { group:178, id:123, text: "La terre est prête, les tailleurs de pierre posent des fondations solides." }
    { group:178, id:124, text: "Nos tailleurs de pierre, fatigués par la pose des fondations, doivent à présent entamer la construction du temple." }
    { group:178, id:125, text: "Le temple central achevé, nous commençons le patio." }
    { group:178, id:126, text: "Nos talentueux tailleurs de pierre ont terminé le patio et commencé la construction du portique." }
    { group:178, id:127, text: "Les tailleurs de pierre posent le toit sur les piliers du portique." }
    { group:178, id:128, text: "Toutes les sections du plafond sont en place sur les portiques." }
    { group:178, id:129, text: "L'entrée du Caesareum est posée." }
    { group:178, id:130, text: "Les tailleurs de pierre ont achevé l'intérieur du Caesareum et érigent maintenant des obélisques à l'extérieur du bâtiment." }
    { group:178, id:131, text: "Le Caesareum est achevé et célèbre l'union entre l'Egypte et Rome." }
    { group:178, id:132, text: "Les paysans ont entamé le pénible nettoyage de la terre." }
    { group:178, id:133, text: "Les tailleurs de pierre posent les fondations du phare." }
    { group:178, id:134, text: "Les fondations sont presque achevées et la pose du parquet est en cours." }
    { group:178, id:135, text: "Le parquet posé, les tailleurs de pierre s'occupent du premier étage du phare." }
    { group:178, id:136, text: "Les tailleurs de pierre n'ont pas le temps d'admirer leur travail car ils doivent déjà commencer le deuxième étage octogonal." }
    { group:178, id:137, text: "Le phare prend réellement forme. L'étage octogonal est achevé. L'installation de la coupole va bientôt commencer." }
    { group:178, id:138, text: "La dernière partie du phare a été posée. Les ouvriers procèdent maintenant au démontage des échafaudages." }
    { group:178, id:139, text: "La plupart des échafaudages ont été démontés, le phare est presque terminé." }
    { group:178, id:140, text: "Le phare de Pharos est achevé. Il surplombe fièrement l'est de la mer Méditerranée." }
    { group:178, id:141, text: "Les ouvriers travaillent dur à Abou Simbel. Assurez-vous qu'ils disposent du bois nécessaire pour installer les échafaudages à temps." }
    { group:178, id:142, text: "Les colosses du Temple d'Abou Simbel accueillent quiconque arrive en Egypte par le sud." }
    { group:178, id:143, text: "Les artisans et tailleurs de pierre refusent de pénétrer dans le tombeau royal sans lampe. Il y fait trop noir !" }
    { group:178, id:144, text: "Les artisans et tailleurs de pierre sont à pied d'œuvre et la construction du tombeau royal progresse. Pensez à fournir à la guilde des artisans l'argile et la peinture nécessaires à leurs travaux." }
    { group:178, id:145, text: "Le tombeau royal est achevé. Il ne manque que les offrandes funéraires destinées au défunt pharaon pour son voyage vers l'au-delà." }
    { group:178, id:146, text: "Le tombeau royal secret est maintenant prêt pour le pharaon. Puisse Horus garder le tombeau et frapper quiconque osera le violer !" }
    { group:178, id:147, text: "Lampes" }
    { group:178, id:148, text: "Les ouvriers ne peuvent pas accéder à l'entrée de la tombe. Allez voir ce qui bloque le passage." }
    { group:178, id:149, text: "Les ouvriers ne peuvent accéder au monument. Vérifiez ce qui en bloque l'accès." }
    { group:179, id:0, text: "Chantier" }
    { group:179, id:1, text: "Ce bâtiment abrite une main-d'œuvre pouvant travailler sur les exploitations des plaines inondables ou construire des monuments." }
    { group:179, id:2, text: "Ce bâtiment a besoin d'ouvriers pour former la nouvelle main-d'œuvre." }
    { group:179, id:3, text: "Nous formons la main-d'œuvre le plus vite possible." }
    { group:179, id:4, text: "Notre main-d'œuvre cherche du travail." }
    { group:179, id:5, text: "Notre main-d'œuvre travaille sur les exploitations des plaines inondables." }
    { group:179, id:6, text: "Notre main-d'œuvre construit des monuments." }
    { group:179, id:7, text: "Notre main-d'œuvre travaille sur les exploitations des plaines inondables et construit des monuments." }
    { group:180, id:0, text: "Briqueterie" }
    { group:180, id:1, text: "C'est ici que l'on confectionne des briques à l'aide d'argile et de paille." }
    { group:180, id:2, text: "Production à" }
    { group:180, id:3, text: "terminée." }
    { group:180, id:4, text: "Votre chef du commerce a ordonné l'interruption de la production de briques." }
    { group:180, id:5, text: "Cette fabrique n'emploie personne. La production a cessé." }
    { group:180, id:6, text: "Cette fabrique dispose de toute la main-d'œuvre nécessaire. Sa production de briques est abondante." }
    { group:180, id:7, text: "Cette fabrique fonctionne en dessous de sa capacité maximale. La production de briques est donc légèrement ralentie." }
    { group:180, id:8, text: "Cette fabrique ne dispose pas d'une main-d'œuvre suffisante. La production de briques est donc très ralentie." }
    { group:180, id:9, text: "Seuls quelques employés travaillent ici. La production de briques est donc ralentie." }
    { group:180, id:10, text: "Seuls quelques employés travaillent ici. La production est quasiment nulle, et devrait être faible cette année." }
    { group:180, id:11, text: "Cette fabrique doit recevoir une livraison de briques d'un entrepôt ou d'un puits d'argile pour la production de briques." }
    { group:180, id:12, text: "Cette fabrique doit recevoir une livraison de paille d'un entrepôt ou d'une exploitation de céréales pour la production de briques." }
    { group:180, id:13, text: "Argile :" }
    { group:180, id:14, text: "Paille :" }
    { group:181, id:0, text: "Exploitation d'orge" }
    { group:181, id:1, text: "L'orge est un ingrédient de base pour la bière, sans laquelle la civilisation égyptienne n'existerait pas." }
    { group:181, id:2, text: "Récolte :" }
    { group:181, id:3, text: "terminée." }
    { group:181, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture de l'orge." }
    { group:181, id:5, text: "Cette ferme n'emploie personne. Ses champs sont en friche." }
    { group:181, id:6, text: "Cette ferme dispose de toute la main-d'œuvre nécessaire. La production est à son maximum." }
    { group:181, id:7, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production pourrait être meilleure avec plus de main-d'œuvre." }
    { group:181, id:8, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production d'orge pourrait être meilleure avec plus de main-d'œuvre." }
    { group:181, id:9, text: "Cette ferme ne dispose que de quelques ouvriers. La quantité d'orge est donc insuffisante pour la bière blonde." }
    { group:181, id:10, text: "Compte tenu du nombre d'employés de cette ferme, la production est pratiquement interrompue." }
    { group:181, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:181, id:12, text: "Terre à" }
    { group:181, id:13, text: "fertile." }
    { group:181, id:14, text: "La prochaine moisson d'orge se fera en" }
    { group:182, id:0, text: "Exploitation de pois chiches" }
    { group:182, id:1, text: "Les pois chiches sont une source de protéines relativement populaire." }
    { group:182, id:2, text: "Récolte :" }
    { group:182, id:3, text: "terminée." }
    { group:182, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture des pois chiches." }
    { group:182, id:5, text: "Cette ferme n'emploie personne. Ses champs sont en friche." }
    { group:182, id:6, text: "Cette ferme dispose de toute la main-d'œuvre nécessaire. La production est à son maximum." }
    { group:182, id:7, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production pourrait être meilleure avec plus de main-d'œuvre." }
    { group:182, id:8, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production de pois chiches pourrait être meilleure avec plus de main-d'œuvre." }
    { group:182, id:9, text: "Cette ferme ne dispose que de quelques ouvriers. La production de pois chiches est donc ralentie." }
    { group:182, id:10, text: "Compte tenu du nombre d'employés de cette ferme, la production est pratiquement interrompue." }
    { group:182, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:182, id:12, text: "Terre :" }
    { group:182, id:13, text: "fertile." }
    { group:182, id:14, text: "La prochaine moisson de pois chiches se fera en" }
    { group:183, id:0, text: "Exploitation de figues" }
    { group:183, id:1, text: "Les figues sont l'un des éléments de base d'un régime équilibré." }
    { group:183, id:2, text: "Récolte :" }
    { group:183, id:3, text: "terminée." }
    { group:183, id:4, text: "Votre chef du commerce a ordonné l'interruption de la culture des figues." }
    { group:183, id:5, text: "Cette ferme n'emploie personne. Ses champs sont en friche." }
    { group:183, id:6, text: "Cette ferme dispose de toute la main-d'œuvre nécessaire. La production est à son maximum." }
    { group:183, id:7, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production pourrait être meilleure avec plus de main-d'œuvre." }
    { group:183, id:8, text: "Cette ferme ne dispose pas de suffisamment d'ouvriers. La production de figues pourrait être meilleure avec plus de main-d'œuvre." }
    { group:183, id:9, text: "Cette ferme ne dispose que de quelques ouvriers. La production de figues est donc ralentie." }
    { group:183, id:10, text: "Compte tenu du nombre d'employés de cette ferme, la production est pratiquement interrompue." }
    { group:183, id:11, text: "Les champs de cette ferme ont été récemment ravagés par un essaim de criquets, et la production va s'en ressentir." }
    { group:183, id:12, text: "Terre :" }
    { group:183, id:13, text: "fertile." }
    { group:183, id:14, text: "La prochaine moisson de figues se fera en" }
    { group:184, id:0, text: "Transporteur" }
    { group:184, id:1, text: "Navire de guerre" }
    { group:184, id:2, text: "Robustesse de la coque" }
    { group:184, id:3, text: "Très robuste" }
    { group:184, id:4, text: "Résistant" }
    { group:184, id:5, text: "Bonne" }
    { group:184, id:6, text: "Moyen" }
    { group:184, id:7, text: "Correct" }
    { group:184, id:8, text: "Faible" }
    { group:184, id:9, text: "Maintenir la position" }
    { group:184, id:10, text: "Lorsqu'il reçoit cet ordre, le navire reste en position, bloquant ainsi le passage à tous les navires ennemis tant qu'il reste sur l'eau." }
    { group:184, id:11, text: "Engager le combat contre les ennemis immédiats" }
    { group:184, id:12, text: "Lorsqu'il reçoit cet ordre, le navire de guerre garde une petite zone. Il se lance à l'attaque de tout soldat ou navire qui s'approche de lui." }
    { group:184, id:13, text: "Chercher et détruire tout ennemi" }
    { group:184, id:14, text: "Lorsqu'il reçoit cet ordre, le navire de guerre recherche au loin tout navire ou soldat ennemi et se lance à son attaque." }
    { group:184, id:15, text: "Réparer" }
    { group:184, id:16, text: "Le navire retourne à la fabrique pour être réparé. Les capitaines de navires fortement endommagés font réparer leurs embarcations de leur propre initiative." }
    { group:184, id:17, text: "Retour au quai" }
    { group:184, id:18, text: "Cet ordre indique au navire de retourner à son quai, où son équipage peut se reposer et reprendre ses esprits." }
    { group:184, id:19, text: "Maintenir la position" }
    { group:184, id:20, text: "Lorsqu'il reçoit cet ordre, le navire reste en position à tout prix. S'il est attaqué, il risque de ne pas rester longtemps en mer." }
    { group:184, id:21, text: "Eviter les ennemis" }
    { group:184, id:22, text: "Sauf contrordre, le capitaine doit à tout prix éviter le contact avec l'ennemi et protéger les troupes qui se trouvent à bord de son navire." }
    { group:184, id:23, text: "Embarquer" }
    { group:184, id:24, text: "Cet ordre indique au capitaine du navire de prendre au passage une compagnie de soldats." }
    { group:184, id:25, text: "Débarquer" }
    { group:184, id:26, text: "Cet ordre indique au capitaine de déposer une compagnie de soldats sur la terre ferme." }
    { group:184, id:27, text: "Fatigue de l'équipage" }
    { group:184, id:28, text: "Reposé" }
    { group:184, id:29, text: "Fatigué" }
    { group:184, id:30, text: "Exténué" }
    { group:184, id:31, text: "Compagnie d'archers" }
    { group:184, id:32, text: "Compagnie de chars" }
    { group:184, id:33, text: "Compagnie de fantassins" }
    { group:184, id:34, text: "à bord" }
    { group:185, id:0, text: "Fabrique de chars" }
    { group:185, id:1, text: "Des artisans expérimentés construisent ici l'une des armes les plus impitoyables des Egyptiens, les roues de guerre." }
    { group:185, id:2, text: "Production à" }
    { group:185, id:3, text: "terminée." }
    { group:185, id:4, text: "Votre chef du commerce a ordonné l'interruption de la fabrication de chars." }
    { group:185, id:5, text: "Cette fabrique de chars n'emploie personne. Elle ne fabriquera pas de chars." }
    { group:185, id:6, text: "Cette fabrique de chars dispose d'une main-d'œuvre suffisante. Sa production de chars est abondante et de qualité." }
    { group:185, id:7, text: "La production de cette fabrique de chars serait meilleure si elle disposait d'une main-d'œuvre supplémentaire." }
    { group:185, id:8, text: "Cette fabrique de chars ne dispose pas d'une main-d'œuvre suffisante. Sa production est donc ralentie." }
    { group:185, id:9, text: "Seuls quelques employés travaillent ici. La production de chars est donc ralentie." }
    { group:185, id:10, text: "Seuls quelques employés travaillent ici. La production est donc légèrement ralentie et devrait être faible cette année." }
    { group:185, id:11, text: "Cette fabrique ne peut produire de chars sans bois." }
    { group:185, id:12, text: "Bois stocké," }
    { group:187, id:0, text: "Inconnu" }
    { group:187, id:1, text: "Divinité locale" }
    { group:187, id:2, text: "Dieu protecteur" }
    { group:188, id:0, text: "Place des fêtes" }
    { group:188, id:1, text: "Demandez au chef des temples d'organiser une fête en l'honneur d'une divinité, et vos citoyens y participeront." }
    { group:188, id:2, text: "Organisez une fête pour amuser les gens et apaiser les dieux" }
    { group:188, id:3, text: "Une fête est en cours" }
    { group:189, id:0, text: "Autel de Sebek" }
    { group:189, id:1, text: "Oracle de Min" }
    { group:189, id:2, text: "Autel de Maât" }
    { group:189, id:3, text: "Oracle d'Horus" }
    { group:189, id:4, text: "Autel d'Amon" }
    { group:189, id:5, text: "Oracle de Thot" }
    { group:189, id:6, text: "Autel d'Anubis" }
    { group:189, id:7, text: "Oracle de Sekhmet" }
    { group:189, id:8, text: "Autel d'Isis" }
    { group:189, id:9, text: "Oracle d'Hathor" }
    { group:190, id:0, text: "Fabrique de papyrus" }
    { group:190, id:1, text: "C'est ici que les roseaux sont assemblés pour en faire des papyrus. Les institutions éducatives utilisent ces derniers pour inscrire des informations et échanger des connaissances. Le papyrus peut également être un objet de commerce." }
    { group:190, id:2, text: "Production à" }
    { group:190, id:3, text: "terminée." }
    { group:190, id:4, text: "Votre chef du commerce a ordonné l'interruption de la production de papyrus." }
    { group:190, id:5, text: "Cette fabrique de papyrus n'emploie personne. Elle ne produira donc pas de papyrus." }
    { group:190, id:6, text: "Cette fabrique de papyrus dispose de toute la main-d'œuvre nécessaire. Sa production est abondante et de qualité." }
    { group:190, id:7, text: "La production de cette fabrique de papyrus serait meilleure si elle disposait d'une main-d'œuvre supplémentaire." }
    { group:190, id:8, text: "Cette fabrique de papyrus ne dispose pas d'une main-d'œuvre suffisante. Sa production est donc ralentie." }
    { group:190, id:9, text: "Seuls quelques employés travaillent ici. La production de papyrus est donc ralentie." }
    { group:190, id:10, text: "Seuls quelques employés travaillent ici. La production de papyrus est donc légèrement ralentie et devrait être faible cette année." }
    { group:190, id:11, text: "Cette fabrique de papyrus ne peut pas fonctionner sans roseaux." }
    { group:190, id:12, text: "Roseaux stockés," }
    { group:191, id:0, text: "Dialogue d'astuce" }
    { group:191, id:1, text: "Désactiver les astuces" }
    { group:192, id:0, text: "Carrière de granit" }
    { group:192, id:1, text: "Pour construire les obélisques, on utilise les lourds blocs de granit qui sont extraits ici." }
    { group:192, id:2, text: "Production à" }
    { group:192, id:3, text: "terminée." }
    { group:192, id:4, text: "Votre chef du commerce a ordonné l'interruption de cette industrie." }
    { group:192, id:5, text: "Ce bâtiment n'emploie personne. La production est interrompue." }
    { group:192, id:6, text: "Ce bâtiment dispose d'une main-d'œuvre suffisante. Sa production de granit est abondante." }
    { group:192, id:7, text: "Ce bâtiment fonctionne en dessous de sa capacité maximale. Sa production serait meilleure s'il disposait d'une main-d'œuvre supplémentaire." }
    { group:192, id:8, text: "Cette carrière ne dispose pas d'une main-d'œuvre suffisante. Sa production est donc ralentie." }
    { group:192, id:9, text: "Seuls quelques employés travaillent ici. La production de granite est donc ralentie." }
    { group:192, id:10, text: "Seuls quelques employés travaillent ici. La production est quasiment nulle, et devrait être faible cette année." }
    { group:193, id:0, text: "Mine de cuivre" }
    { group:193, id:1, text: "Un cuivre facile à travailler et de bonne qualité permet de fabriquer des armes de qualité et constitue un bon article d'exportation." }
    { group:193, id:2, text: "Production à" }
    { group:193, id:3, text: "terminée." }
    { group:193, id:4, text: "Votre chef du commerce a ordonné l'interruption de cette industrie." }
    { group:193, id:5, text: "Cette mine n'emploie personne. La production est inexistante." }
    { group:193, id:6, text: "Cette mine dispose d'une main-d'œuvre suffisante. Sa production de cuivre est abondante." }
    { group:193, id:7, text: "Cette mine fonctionne en dessous de sa capacité maximale. Sa production serait meilleure si elle disposait d'une main-d'œuvre supplémentaire." }
    { group:193, id:8, text: "Cette mine ne dispose pas d'une main-d'œuvre suffisante. Sa production de cuivre est donc ralentie." }
    { group:193, id:9, text: "Seuls quelques employés travaillent ici. La production est donc ralentie." }
    { group:193, id:10, text: "Seuls quelques employés travaillent ici. La production est quasiment nulle, et devrait être faible cette année." }
    { group:194, id:0, text: "Carrière de grès" }
    { group:194, id:1, text: "Seul le grès possède les propriétés nécessaires à la construction des mausolées et des temples solaires." }
    { group:194, id:2, text: "Production à" }
    { group:194, id:3, text: "terminée." }
    { group:194, id:4, text: "Votre chef du commerce a ordonné l'interruption de cette industrie." }
    { group:194, id:5, text: "Cette carrière n'emploie personne. La production est interrompue." }
    { group:194, id:6, text: "Cette carrière dispose d'une main-d'œuvre suffisante. Sa production de grès est abondante." }
    { group:194, id:7, text: "Cette carrière fonctionne en dessous de sa capacité maximale. Sa production serait meilleure si elle disposait d'une main-d'œuvre supplémentaire." }
    { group:194, id:8, text: "Cette carrière ne dispose pas d'une main-d'œuvre suffisante. Sa production est donc ralentie." }
    { group:194, id:9, text: "Seuls quelques employés travaillent ici. La production est donc ralentie." }
    { group:194, id:10, text: "Seuls quelques employés travaillent ici. La production est quasiment nulle, et devrait être faible cette année." }
    { group:195, id:0, text: "Abou" }
    { group:195, id:1, text: "Abydos" }
    { group:195, id:2, text: "l'oasis de Bahariya " }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubastis" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Byblos" }
    { group:195, id:8, text: "Dahshur" }
    { group:195, id:9, text: "l'oasis de Dakhlèh" }
    { group:195, id:10, text: "Djedu" }
    { group:195, id:11, text: "l'oasis de Dunqul" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "l'oasis de Farafra" }
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
    { group:195, id:24, text: "l'oasis de Kharga" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knossos" }
    { group:195, id:27, text: "Kyrene" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mycenae" }
    { group:195, id:32, text: "Nekhen" }
    { group:195, id:33, text: "Nubt (Ombos)" }
    { group:195, id:34, text: "Actif" }
    { group:195, id:35, text: "Perwadjyt" }
    { group:195, id:36, text: "Pwenet" }
    { group:195, id:37, text: "Qadesh" }
    { group:195, id:38, text: "Rostja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Saqqara" }
    { group:195, id:41, text: "Sauty" }
    { group:195, id:42, text: "Sawu" }
    { group:195, id:43, text: "l'oasis de Selima" }
    { group:195, id:44, text: "Serabit Khadim" }
    { group:195, id:45, text: "Shaat" }
    { group:195, id:46, text: "Sharuhen" }
    { group:195, id:47, text: "Thinis" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toshka" }
    { group:195, id:50, text: "Tyre" }
    { group:195, id:51, text: "Waset" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alexandrie" }
    { group:195, id:54, text: "Sumur" }
    { group:195, id:55, text: "Deir el-Medineh" }
    { group:195, id:56, text: "Abou Simbel" }
    { group:195, id:57, text: "Actium" }
    { group:195, id:58, text: "Rome" }
    { group:195, id:59, text: "Tanis" }
    { group:195, id:60, text: "Pi-Yer" }
    { group:195, id:61, text: "l'oasis de Siwi" }
    { group:195, id:62, text: "Maritis" }
    { group:195, id:63, text: "Pi-Ramsès" }
    { group:195, id:64, text: "Athènes" }
    { group:195, id:65, text: "Cléoantonopolis" }
    { group:198, id:0, text: "Aucun" }
    { group:198, id:1, text: "Petite pyramide penchée" }
    { group:198, id:2, text: "Pyramide penchée moyenne" }
    { group:198, id:3, text: "Petite pyramide en terre" }
    { group:198, id:4, text: "Pyramide en terre moyenne" }
    { group:198, id:5, text: "Grande pyramide en terre" }
    { group:198, id:6, text: "Ensemble de pyramides en terre" }
    { group:198, id:7, text: "Grd ensemble pyramides en terre" }
    { group:198, id:8, text: "Petite pyramide à degrés" }
    { group:198, id:9, text: "Pyramide à degrés moyenne" }
    { group:198, id:10, text: "Grande pyramide à degrés" }
    { group:198, id:11, text: "Ensemble de pyramides à degrés" }
    { group:198, id:12, text: "Grd ensemble pyramides à degrés" }
    { group:198, id:13, text: "Petite pyramide" }
    { group:198, id:14, text: "Pyramide moyenne" }
    { group:198, id:15, text: "Grande pyramide" }
    { group:198, id:16, text: "Ensemble de pyramides" }
    { group:198, id:17, text: "Grand ensemble de pyramides" }
    { group:198, id:18, text: "Petit mastaba" }
    { group:198, id:19, text: "Mastaba moyen" }
    { group:198, id:20, text: "Grand mastaba" }
    { group:198, id:21, text: "Sphinx" }
    { group:198, id:22, text: "Petit obélisque" }
    { group:198, id:23, text: "Grand obélisque" }
    { group:198, id:24, text: "Temple solaire" }
    { group:198, id:25, text: "Mausolée" }
    { group:198, id:26, text: "Mausolée" }
    { group:198, id:27, text: "Mausolée" }
    { group:198, id:28, text: "Phare de Pharos" }
    { group:198, id:29, text: "Bibliothèque d'Alexandrie" }
    { group:198, id:30, text: "Caesareum" }
    { group:198, id:31, text: "Colosse" }
    { group:198, id:32, text: "Temple de Louqsor" }
    { group:198, id:33, text: "Petite Tombe Royale" }
    { group:198, id:34, text: "Tombe Royale Moyenne" }
    { group:198, id:35, text: "Grande Tombe Royale" }
    { group:198, id:36, text: "Très Grande Tombe Royale" }
    { group:198, id:37, text: "Abou Simbel" }
    { group:199, id:0, text: "Chef des monuments" }
    { group:199, id:1, text: "en stock" }
    { group:199, id:2, text: "terminée." }
    { group:199, id:3, text: "Cliquez sur les offrandes funéraires à livrer." }
    { group:199, id:4, text: "Quantité à expédier" }
    { group:199, id:5, text: "Tout" }
    { group:199, id:6, text: "Cliquez pour expédier" }
    { group:199, id:7, text: "Annuler" }
    { group:199, id:8, text: "Augmenter quantité" }
    { group:199, id:9, text: "Diminuer quantité" }
    { group:199, id:10, text: "Expédier offrandes funéraires" }
    { group:199, id:11, text: "Niveau architectural" }
    { group:199, id:12, text: "Il n'y a pas d'offrandes à expédier." }
    { group:199, id:13, text: "Visitez la construction pour en savoir plus." }
    { group:199, id:14, text: "La construction de la pyramide n'est pas commencée. Main-d'œuvre et" }
    { group:199, id:15, text: "importantes quantités de pierre et de calcaire sont requises pour ce projet." }
    { group:199, id:16, text: "La construction de la pyramide est à" }
    { group:199, id:17, text: "La pyramide est terminée !" }
    { group:199, id:18, text: "La pyramide est terminée et attend l'arrivée des vestiges sacrés." }
    { group:199, id:19, text: "La construction de la pyramide en briques nécessite de la main-d'œuvre pour" }
    { group:199, id:20, text: "ce projet, et d'une quantité importante de briques et de calcaire blanc." }
    { group:199, id:21, text: "La construction de la pyramide en briques est à" }
    { group:199, id:22, text: "La pyramide en briques est terminée !" }
    { group:199, id:23, text: "La pyramide en briques est terminée et attend l'arrivée des vestiges sacrés." }
    { group:199, id:24, text: "La construction de la pyramide à degrés nécessite de la main-d'œuvre pour" }
    { group:199, id:25, text: "ce projet, ainsi que d'une quantité importante de pierre pour l'achever." }
    { group:199, id:26, text: "La construction de la pyramide à degrés est à" }
    { group:199, id:27, text: "La pyramide à degrés est terminée !" }
    { group:199, id:28, text: "La pyramide à degrés est terminée et attend l'arrivée des vestiges sacrés." }
    { group:199, id:29, text: "La construction de la pyramide penchée nécessite de la main-d'œuvre" }
    { group:199, id:30, text: "pour ce projet, et d'une quantité importante de pierre et de calcaire." }
    { group:199, id:31, text: "La construction de la pyramide penchée est à" }
    { group:199, id:32, text: "La pyramide penchée est terminée !" }
    { group:199, id:33, text: "La pyramide penchée est terminée et attend l'arrivée des vestiges sacrés." }
    { group:199, id:34, text: "La construction du mastaba nécessite de la main-d'œuvre pour" }
    { group:199, id:35, text: "ce projet, et d'une quantité importante de briques pour l'achever." }
    { group:199, id:36, text: "La construction du mastaba est à" }
    { group:199, id:37, text: "Le mastaba est terminé !" }
    { group:199, id:38, text: "Le mastaba est terminé et attend l'arrivée des vestiges sacrés." }
    { group:199, id:39, text: "La construction du Sphinx nécessite des menuisiers, des tailleurs" }
    { group:199, id:40, text: "de pierre, du bois et de la pierre." }
    { group:199, id:41, text: "La construction du sphinx est à" }
    { group:199, id:42, text: "Le sphinx est terminé !" }
    { group:199, id:43, text: "La construction de l'obélisque n'a pas commencé. Besoin de :" }
    { group:199, id:44, text: "blocs de granit pour ce projet. Vous avez" }
    { group:199, id:45, text: "La construction de l'obelisque est à" }
    { group:199, id:46, text: "L'obélisque est terminé !" }
    { group:199, id:47, text: "La construction du temple solaire n'a pas commencé. Besoin de :" }
    { group:199, id:48, text: "blocs de grès pour ce projet. Vous avez" }
    { group:199, id:49, text: "La construction du temple solaire est à" }
    { group:199, id:50, text: "Le temple solaire est terminé !" }
    { group:199, id:51, text: "Construction du mausolée impossible. Il vous faut" }
    { group:199, id:52, text: "blocs de grès pour ce projet. Vous avez" }
    { group:199, id:53, text: "La construction du mausolée est à" }
    { group:199, id:54, text: "Le mausolée est terminé !" }
    { group:199, id:55, text: "Le mausolée est terminé et attend l'arrivée des vestiges sacrés." }
    { group:199, id:56, text: "Cliquez pour visiter le site de construction." }
    { group:199, id:57, text: "bloc en stock" }
    { group:199, id:58, text: "blocs en stock" }
    { group:199, id:59, text: "Cherchez de la main-d'œuvre pour le chantier de la bibliothèque" }
    { group:199, id:60, text: "pour commencer ce projet, ainsi que du marbre et du cuivre pour l'achever." }
    { group:199, id:61, text: "La construction de la bibliothèque d'Alexandrie est à" }
    { group:199, id:62, text: "La bibliothèque d'Alexandrie est achevée !" }
    { group:199, id:63, text: "La construction du Caesarum n'a pas débuté. Cherchez de la main-d'œuvre" }
    { group:199, id:64, text: "pour commencer ce projet, ainsi que du marbre et du granit pour l'achever." }
    { group:199, id:65, text: "La construction du Caesareum est à" }
    { group:199, id:66, text: "Le Caesarum est maintenant achevé !" }
    { group:199, id:67, text: "Cherchez de la main-d'œuvre pour le chantier du phare de Pharos" }
    { group:199, id:68, text: "pour commencer ce projet, ainsi que du marbre pour l'achever." }
    { group:199, id:69, text: "La construction du phare de Pharos est à" }
    { group:199, id:70, text: "Le phare de Pharos est maintenant achevé !" }
    { group:199, id:71, text: "Le travail sur le temple d'Abou Simbel n'a pas commencé. Vous avez besoin " }
    { group:199, id:72, text: "de menuisiers, de tailleurs de pierre et de bois pour commencer ce projet." }
    { group:199, id:73, text: "La construction du temple d'Abou Simbel est à" }
    { group:199, id:74, text: "Le temple d'Abou Simbel est achevé !" }
    { group:199, id:75, text: "La Petite Tombe n'est pas commencée. Il faut des maçons, des artisans," }
    { group:199, id:76, text: "de l'argile, de la peinture et des lampes pour commencer ce projet." }
    { group:199, id:77, text: "La construction de la Petite Tombe est à" }
    { group:199, id:78, text: "La Petite Tombe est achevée !" }
    { group:199, id:79, text: "La Tombe Moyenne n'est pas commencée. Il faut des maçons, des artisans," }
    { group:199, id:80, text: "de l'argile, de la peinture et des lampes pour commencer ce projet." }
    { group:199, id:81, text: "La construction de la Tombe Moyenne est à" }
    { group:199, id:82, text: "La Tombe Moyenne est achevée !" }
    { group:199, id:83, text: "La Grande Tombe n'est pas commencée. Il faut des maçons, des artisans," }
    { group:199, id:84, text: "de l'argile, de la peinture et des lampes pour commencer ce projet." }
    { group:199, id:85, text: "La construction de la Grande Tombe Royale est à" }
    { group:199, id:86, text: "La Grande Tombe est terminée !" }
    { group:199, id:87, text: "La Très Grande Tombe n'est pas entamée. Il faut des maçons, des artisans," }
    { group:199, id:88, text: "de l'argile, de la peinture et des lampes pour commencer ce projet." }
    { group:199, id:89, text: "La construction de la Très Grande Tombe Royale est à" }
    { group:199, id:90, text: "La Très Grande Tombe est prête !" }
    { group:200, id:0, text: "Phase 1 : se procurer du granit pour construire les bases de la structure" }
    { group:200, id:1, text: "Phase 2 : les menuisiers se servent de bois pour construire les échafaudages" }
    { group:200, id:2, text: "Phase 3 : les tailleurs de pierre sculptent la forme de haut en bas" }
    { group:200, id:3, text: "Statut :" }
    { group:200, id:4, text: "Non commencé" }
    { group:200, id:5, text: "Inachevé" }
    { group:200, id:6, text: "Terminé" }
    { group:200, id:7, text: "Progression globale :" }
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
    { group:205, id:0, text: "Je vais lui voler son trésor ! On verra s'il s'en apercevra !" }
    { group:205, id:1, text: "Je prends ce que je veux ! N'essayez pas de m'en empêcher !" }
    { group:205, id:2, text: "Voler rapporte bien plus d'argent que certains travaux en ville !" }
    { group:205, id:3, text: "Voler, voler, voler. Voilà ma devise." }
    { group:206, id:0, text: "Hum, hum ! (toux) Ohhh, mon ventre ! Oh, ma tête !" }
    { group:207, id:0, text: "Attention à la peste ! Pourvu qu'elle se limite aux quartiers pauvres de la ville !" }
    { group:207, id:1, text: "Il est scandaleux qu'une personne de mon rang connaisse la faim !" }
    { group:207, id:2, text: "Je ne crois pas que cette ville supporterait une attaque et j'ai beaucoup à y perdre." }
    { group:207, id:3, text: "Avec une main-d'œuvre aussi peu nombreuse, mes besoins ne seront jamais satisfaits !" }
    { group:207, id:4, text: "On me traite bien mieux que les dieux ! J'espère qu'aucune attaque ne se prépare." }
    { group:207, id:5, text: "J'ai honte de vivre ici. Pourvu que nos ennemis ne profitent pas de notre réputation !" }
    { group:207, id:6, text: "Regardez ces oisifs ! Pourquoi ne trouvent-ils pas de travail ?" }
    { group:207, id:7, text: "Je ne peux pas vivre une existence snob sans divertissements adéquats !" }
    { group:207, id:8, text: "Je suppose que cette cité est convenable." }
    { group:207, id:9, text: "On ne peut rêver cité plus réussie !" }
    { group:207, id:10, text: "Ces fêtes seraient bien plus réussies si elles étaient sur invitation uniquement." }
    { group:210, id:0, text: "Les oiseaux sont rusés. Ils fuient lorsqu'on s'approche trop près." }
    { group:210, id:1, text: "Admirez ces magnifiques oiseaux, prêts à être dégustés !" }
    { group:211, id:0, text: "Encore une magnifique journée de pêche qui s'annonce. J'espère que la prise sera aussi bonne que d'habitude." }
    { group:211, id:1, text: "Cette prise est magnifique, mais pas autant que la précédente !" }
    { group:211, id:2, text: "Plus vite ! Nous ne pouvons pas nous remettre au travail avant le déchargement." }
    { group:215, id:0, text: "Des marécages. Les roseaux ne poussent que sur des marécages." }
    { group:215, id:1, text: "Ces roseaux feront un excellent papyrus." }
    { group:216, id:0, text: "On a besoin de mes services au monument !" }
    { group:216, id:1, text: "Sans mes chantiers et mes échafaudages, ce monument sera très bas." }
    { group:217, id:0, text: "Tout le monde au monument pour poser des briques !" }
    { group:217, id:1, text: "Grâce à mes briques, ce monument sera très solide." }
    { group:218, id:0, text: "Je me rends au monument pour tailler les pierres." }
    { group:218, id:1, text: "Mon travail survivra au temps." }
    { group:219, id:0, text: "Beaucoup de gens sont malades. J'espère qu'ils guériront vite avant que la peste ne s'installe." }
    { group:219, id:1, text: "Je meurs de faim. Mes clients me réclament de la nourriture et j'en ai à peine assez pour moi." }
    { group:219, id:2, text: "Nos défenses sont fragiles. Nous pourrions facilement être envahis." }
    { group:219, id:3, text: "Je dois ménager mes assistants car avec toutes ces offres d'emploi, je risque de les perdre." }
    { group:219, id:4, text: "Si nous ne respectons pas davantage les dieux, ils risquent de nous punir sévèrement." }
    { group:219, id:5, text: "Nous pourrions bientôt payer le prix de la mauvaise réputation de cette ville !" }
    { group:219, id:6, text: "J'ai de la chance de travailler. Beaucoup de personnes sont sans emploi." }
    { group:219, id:7, text: "Rien ne se passe ici. Si seulement il y avait plus d'animations." }
    { group:219, id:8, text: "Je ne voudrais pas critiquer cette ville... mais…" }
    { group:219, id:9, text: "Cette ville est fantastique !" }
    { group:219, id:10, text: "Le bazar a besoin de marchandises. Je vais les chercher." }
    { group:219, id:11, text: "Ces objets seront très utiles au bazar." }
    { group:226, id:0, text: "J'ai vu tant de gens malades. Je crains une épidémie de peste." }
    { group:226, id:1, text: "C'est difficile d'attraper les balles lorsqu'on a des crampes d'estomac." }
    { group:226, id:2, text: "Je devrais utiliser ces balles comme projectiles en cas d'attaque ennemie. Les défenses de la ville sont dérisoires." }
    { group:226, id:3, text: "On cherche de la main-d'œuvre partout ! J'arriverais peut-être à jongler avec plusieurs boulots." }
    { group:226, id:4, text: "Je m'attends au pire. Les dieux doivent se sentir un peu oubliés." }
    { group:226, id:5, text: "La réputation de cette ville est pire que la mienne. Gare à l'invasion !" }
    { group:226, id:6, text: "Si seulement les gens avaient plus de travail... Personne n'est assez riche pour me payer." }
    { group:226, id:7, text: "Mes talents se limitent à la jonglerie. Cette ville devrait accueillir d'autres artistes." }
    { group:226, id:8, text: "Cette ville n'est pas désagréable." }
    { group:226, id:9, text: "J'adore jongler ici." }
    { group:226, id:10, text: "J'adore les fêtes. Les gens y sont si heureux !" }
    { group:227, id:10, text: "Ces fêtes sont géniales ! Tout le monde chante." }
    { group:229, id:0, text: "La vie des habitants est en danger. Le risque de peste est important." }
    { group:229, id:1, text: "J'ai une faim de loup, mais je ne trouve pas grand-chose à manger." }
    { group:229, id:2, text: "Je devrais apprendre l'art de la guerre. Nos défenses sont tellement faibles que nous courons un grand danger." }
    { group:229, id:3, text: "Le manque de main-d'œuvre risque de poser de graves problèmes à la cité." }
    { group:229, id:4, text: "A vrai dire, je n'oserais pas traiter les dieux de cette façon." }
    { group:229, id:5, text: "La réputation de cette cité est extrêment inégale. Nous risquons d'être attaqués." }
    { group:229, id:6, text: "D'une manière générale, il est quasiment impossible de trouver du travail dans cette ville." }
    { group:229, id:7, text: "Cette cité devrait remédier au manque de loisirs !" }
    { group:229, id:8, text: "J'ai honte de vivre ici." }
    { group:229, id:9, text: "Cette cité tient une place importante dans mon cœur. J'adore cet endroit !" }
    { group:229, id:10, text: "Servez-vous en bière! Généreuse et rafraîchissante. Peu riche en sédiments !" }
    { group:235, id:0, text: "Les terribles conditions d'hygiène risquent bientôt de provoquer une épidémie de peste dans cette cité." }
    { group:235, id:1, text: "Mon esprit est rempli d'instruction, mais j'ai le ventre vide." }
    { group:235, id:2, text: "Les ennemis n'auront pas de mal à percer nos faibles défenses." }
    { group:235, id:3, text: "Le manque de main-d'œuvre se reflète dans toute la cité, ce qui limite les services." }
    { group:235, id:4, text: "Les mœurs sacrilèges de cette ville risquent de provoquer le châtiment des dieux !" }
    { group:235, id:5, text: "Ah, réputation, réputation. Notre réputation scandaleuse incite à l'attaque." }
    { group:235, id:6, text: "Même l'éducation ne peut résoudre le manque de travail dans cette cité." }
    { group:235, id:7, text: "Il n'y a rien de plus ennuyeux que cette cité." }
    { group:235, id:8, text: "Cette cité est d'importance moyenne." }
    { group:235, id:9, text: "Cette cité est formidable !" }
    { group:235, id:10, text: "On peut en apprendre beaucoup sur la nature humaine lors d'une fête." }
    { group:240, id:0, text: "Il y a trop de malades, je suis débordé !" }
    { group:240, id:1, text: "Je meurs de faim. Je vais bientôt ressembler à une momie !" }
    { group:240, id:2, text: "J'espère que nos ennemis n'ont pas l'intention de nous envahir, nous serions perdus." }
    { group:240, id:3, text: "On cherche de la main-d'œuvre partout ! Peut-être y-a-t'il une place de tisserand disponible !" }
    { group:240, id:4, text: "J'espère que les dieux vont se montrer cléments.  " }
    { group:240, id:5, text: "Il semblerait que la ville ait mauvaise réputation. Nous risquons d'être attaqués !" }
    { group:240, id:6, text: "J'ai la chance de pouvoir travailler, ce qui n'est pas le cas de tout le monde." }
    { group:240, id:7, text: "Je passe mon temps à travailler. Il n'y a rien d'autre à faire ici." }
    { group:240, id:8, text: "Je me sens bien ici, mais je pense pouvoir trouver mieux." }
    { group:240, id:9, text: "J'espère rester ici toute ma vie !" }
    { group:240, id:10, text: "L'hygiène semble empirer dans toute la cité." }
    { group:247, id:0, text: "On a besoin de mes services au monument !" }
    { group:247, id:1, text: "Je raconte l'histoire égyptienne en peignant les tombes royales." }
    { group:248, id:0, text: "Les morts n'ont que faire de l'or !" }
    { group:248, id:1, text: "Je serai immensément riche lorsque j'aurai vendu tous ces trésors !" }
    { group:249, id:0, text: "Nous lutterons jusqu'au bout pour défendre notre ville !" }
    { group:249, id:1, text: "L'ennemi est trop puissant ! Si nous nous en sortons, nous reprendrons le combat un autre jour." }
    { group:249, id:2, text: "Les ennemis arrivent de ce côté !" }
    { group:249, id:3, text: "Nous sommes aussi dangereux que des crocodiles et prêts à attaquer l'ennemi s'il s'approche." }
    { group:249, id:4, text: "Nous sommes prêts à repousser l'assaillant le moment venu." }
    { group:250, id:0, text: "Du nerf ! Nous devons protéger notre navire à tout prix !" }
    { group:250, id:1, text: "L'ennemi est là ! Que tout le monde se prépare à la manœuvre !" }
    { group:250, id:2, text: "A l'attaque ! Nous sommes prêts." }
    { group:250, id:3, text: "Nous sommes prêts à intervenir en cas de besoin." }
    { group:251, id:0, text: "Chariot Exact 1" }
    { group:252, id:0, text: "Aucun ennemi en vue, mais nous sommes prêts quoi qu'il arrive." }
    { group:252, id:1, text: "Nous sommes sur nos gardes, prêts à bondir sur l'ennemi." }
    { group:252, id:2, text: "Vous appelez ça une armée ?! Nous n'aurons pas de mal à battre cette bande d'incapables." }
    { group:252, id:3, text: "Ces ennemis sont féroces ! Je ferai tout pour les battre." }
    { group:253, id:0, text: "Temple solaire" }
    { group:253, id:1, text: "Phase 1" }
    { group:253, id:2, text: "Le grand obélisque est en place" }
    { group:253, id:3, text: "et les ouvriers nettoient le site de construction" }
    { group:253, id:4, text: "Phase 2" }
    { group:253, id:5, text: "Les menuisiers installent des échafaudages autour de" }
    { group:253, id:6, text: "l'obélisque" }
    { group:253, id:7, text: "Phase 3" }
    { group:253, id:8, text: "Les tailleurs de pierre sculptent les dernières formes" }
    { group:253, id:9, text: "de l'obélisque" }
    { group:253, id:10, text: "Phase 4" }
    { group:253, id:11, text: "Le vestibule, les murs, la plaza et" }
    { group:253, id:12, text: "l'avant-temple sont en cours de construction" }
    { group:253, id:13, text: "Un seul tailleur de pierre attend de la pierre" }
    { group:253, id:14, text: "les tailleurs de pierre attendent de la pierre" }
    { group:253, id:15, text: "Le temple solaire est" }
    { group:253, id:16, text: "pour cent terminé" }
    { group:253, id:17, text: "blocs de pierre requis pour" }
    { group:253, id:18, text: "terminer la construction du temple solaire" }
    { group:291, id:0, text: "Mausolée" }
    { group:291, id:1, text: "Phase 1" }
    { group:291, id:2, text: "Les fondations sont en place" }
    { group:291, id:3, text: "et les ouvriers nettoient le site de construction" }
    { group:291, id:4, text: "Phase 2" }
    { group:291, id:5, text: "Les maçons construisent la partie inférieure" }
    { group:291, id:6, text: "du mausolée" }
    { group:291, id:7, text: "Phase 3" }
    { group:291, id:8, text: "Les tailleurs de pierre construisent la partie supérieure" }
    { group:291, id:9, text: "du mausolée" }
    { group:291, id:10, text: "Un seul tailleur de pierre attend de la pierre" }
    { group:291, id:11, text: "les tailleurs de pierre attendent de la pierre" }
    { group:291, id:12, text: "Le mausolée est" }
    { group:291, id:13, text: "pour cent terminé" }
    { group:291, id:14, text: "des blocs de pierre sont requis pour" }
    { group:291, id:15, text: "terminer la construction du mausolée" }
    { group:292, id:0, text: "Créer une famille" }
    { group:292, id:1, text: "Supprimer" }
    { group:292, id:2, text: "Continuer" }
    { group:292, id:3, text: "Registre des familles" }
    { group:292, id:4, text: "Retour au menu principal" }
    { group:293, id:0, text: "Rejouer l'histoire" }
    { group:293, id:1, text: "Choisir une mission" }
    { group:293, id:2, text: "Charger une partie" }
    { group:293, id:3, text: "Missions personnalisées" }
    { group:293, id:4, text: "Retour au registre des familles" }
    { group:293, id:5, text: "famille [player_name]" }
    { group:293, id:6, text: "Lire l'histoire" }
    { group:293, id:7, text: "Lancer l'histoire" }
    { group:294, id:0, text: "Période prédynastique" }
    { group:294, id:1, text: "Durant la période prédynastique, les clans qui allaient contrôler l'Egypte se lancèrent sur la route de la civilisation." }
    { group:294, id:2, text: "Votre famille commence la période prédynastique à la tête d'une petite bande de nomades qui découvrent les arts de la civilisation. Grâce à votre règne, l'Egypte pourra devenir une très grande nation." }
    { group:294, id:3, text: "La période prédynastique constitue l'aube de l'histoire de l'Egypte et de celle de votre famille." }
    { group:294, id:4, text: "Période archaïque" }
    { group:294, id:5, text: "Petit à petit, les villages établis durant la période prédynastique se sont coalisés pour former un royaume unifié, doté d'une magnifique capitale et de tombes monumentales." }
    { group:294, id:6, text: "Durant la période archaïque, les villages fondés durant la période prédynastique s'unissent petit à petit pour former le grand royaume d'Egypte. Cette civilisation naissante érige une capitale, renforce ses frontières, maîtrise les ressources maritimes et fluviales et construit les premières tombes monumentales." }
    { group:294, id:7, text: "Respectez l'ordre de votre histoire ! Malheureusement, vous ne pouvez pas être à la tête de la période archaïque tant que vous ne vous êtes pas familiarisé avec les arts découverts durant la période prédynastique." }
    { group:294, id:8, text: "Ancien empire" }
    { group:294, id:9, text: "L'Egypte entre dans un âge d'or de richesse, de puissance et de gloire, et érige de superbes monuments dans le monde entier. Après avoir atteint son apogée, l'Egypte sombra dans la guerre." }
    { group:294, id:10, text: "L'Egypte accède à un niveau de puissance, de richesse et de gloire sans précédent sous l'Ancien empire. Toutefois, même lorsque de superbes monuments sont érigés dans la vallée du Nil, les voyants font d'étranges prévisions sur l'avenir des Deux Pays." }
    { group:294, id:11, text: "Ne brûlez pas les étapes du cours de votre histoire. Avant de pouvoir intégrer l'Ancien empire, vous devez terminer la période archaïque." }
    { group:294, id:12, text: "Moyen empire" }
    { group:294, id:13, text: "Depuis sa naissance pénible, le Moyen Empire s'est avéré être une période de gloire pour votre famille. " }
    { group:294, id:14, text: "Le Moyen empire, qui s'est développé dans le trouble, s'avère une période de grandes opportunités pour votre famille. Grâce à votre règne, l'Egypte retrouve sa splendeur d'autrefois et bien plus encore." }
    { group:294, id:15, text: "Respectez l'ordre de l'histoire ! Le Moyen empire ne peut pas commencer avant la fin de l'Ancien empire !" }
    { group:294, id:16, text: "Nouvel empire" }
    { group:294, id:17, text: "Un nouvel ennemi belliqueux, doté d'une arme ingénieuse, met fin au Moyen Empire. L'Egypte finit par renaître de ses cendres." }
    { group:294, id:18, text: "D'étranges ennemis dotés d'une arme terrifiante mettent fin au Moyen empire et préparent le superbe Nouvel empire qui suivra." }
    { group:294, id:19, text: "Vous ne pouvez pas changer le cours de votre histoire. Vous ne pouvez pas vivre le Nouvel Empire sans avoir vécu les périodes antérieures." }
    { group:294, id:20, text: "Vallée des Rois" }
    { group:294, id:21, text: "Le développement d'une nouvelle nécropole dans la Vallée des Rois a permis de préparer les pharaons à leur voyage dans l'au-delà. " }
    { group:294, id:22, text: "En dépit de leur splendeur, les pyramides se sont détériorées au fil des siècles, les tombes qu'elles abritent ont perdu leur caractère sacré, et les trésors cachés ont été pillés par des voleurs, que les dieux ne manqueront pas de punir à jamais. Construisez une nécropole dans un oued d'accès difficile depuis Thèbes. Creusez les falaises pour créer une Vallée des Rois, à l'abri des voleurs. Mais le sera-t-elle vraiment ?" }
    { group:294, id:23, text: "Il y a un temps pour tout dans votre histoire. Vous ne pouvez pas construire les superbes tombeaux de la Vallée des Rois tant que vous n'avez pas achevé les splendeurs du Nouvel Empire" }
    { group:294, id:24, text: "Ramsès II" }
    { group:294, id:25, text: "Ramsès II célèbre sa grandeur et ses victoires en faisant ériger des monuments somptueux." }
    { group:294, id:26, text: "Ramsès II est le troisième d'une dynastie commencée par son grand-père, Ramsès I, un vizir roturier qui accéda au trône lorsque Horemheb mourut sans descendance. Vous devez remporter plusieurs victoires militaires et construire de splendides monuments qui convaincront vos sujets de votre statut divin, plongeront vos ennemis dans le désespoir et couvriront de gloire le nom de Ramsès et l'Egypte pendant des générations." }
    { group:294, id:27, text: "Votre histoire doit suivre son cours. Vous devez construire les tombeaux de la Vallée des Rois, pour pouvoir régner comme Ramsès II." }
    { group:294, id:28, text: "Anciens conquérants" }
    { group:294, id:29, text: "De puissants guerriers de pays lointains tentent d'exercer leur influence sur la noblesse égyptienne. Après avoir écarté ces menaces et célébré la gloire d'Alexandre, sélectionnez 'Choisir une mission' pour rejouer la campagne entière ou l'une de ses missions particulières." }
    { group:294, id:30, text: "L'Egypte possède de nombreux voisins envieux, qui affluent vers notre riche empire tels une meute de hyènes à la poursuite d'un lion. Etes-vous en mesure de constituer et de commander l'armée et la flotte à même d'anéantir ces menaces et défendre le delta du Nil contre les invasions successives des Peuples de la Mer, des Assyriens et des Perses ? L'Egypte compte sur vous pour sa protection !" }
    { group:294, id:31, text: "Le cours de l'histoire doit être respecté. Tant que vous n'avez pas été Ramsès II, vous ne pouvez pas vaincre les Conquérants antiques." }
    { group:294, id:32, text: "Capitale de Cléopâtre" }
    { group:294, id:33, text: "Les dirigeants ptolémaïques de Grèce ont restauré la gloire de l'Egypte et écarté la menace romaine." }
    { group:294, id:34, text: "Alexandre le Grand a décidé du sort d'Alexandrie, la cité portuaire de la mer Méditerranée à construire. Sous les 300 ans de règne ptolémaïque, qui s'achèveront avec Cléopâtre, Alexandrie deviendra la plus grande cité du monde, dépassant Rome en termes de population et de richesses. Le mausolée d'Alexandre, la grande bibliothèque, le phare de Pharos et le Caesareum sont vos projets. Mais les puissantes légions romaines seront-elles utilisées en faveur de l'Egypte de Cléopâtre, ou contre elle ?" }
    { group:294, id:35, text: "Vous ne pouvez pas ajouter Cléopâtre dans vos annales tant que vous n'avez pas vaincu les Conquérants antiques." }
    { group:294, id:36, text: "Commencer" }
    { group:294, id:37, text: "Jouer" }
    { group:294, id:38, text: "Missions individuelles" }
    { group:294, id:39, text: "Campagnes" }
    { group:294, id:40, text: "Vous ne pouvez rejouer les missions qu'une fois qu'elles sont terminées." }
    { group:294, id:41, text: "Pharaon" }
    { group:294, id:42, text: "La Reine du Nil - Cléopâtre" }
    { group:295, id:0, text: "Cette fête a mis tout le monde de bonne humeur et une autre devrait bientôt avoir lieu dans cette cité." }
    { group:295, id:1, text: "Quelques mois se sont écoulés depuis la dernière fête. Il est temps d'en organiser une autre." }
    { group:295, id:2, text: "Cela fait longtemps qu'aucune fête n'a eu lieu et les gens commencent à se plaindre." }
    { group:295, id:3, text: "Cela fait plus d'un an qu'aucune fête n'a eu lieu. Les gens s'ennuient et sont exténués." }
    { group:295, id:4, text: "Presque deux ans se sont écoulés depuis la dernière fête. Les gens n'en peuvent plus." }
    { group:295, id:5, text: "Plus de trois ans se sont écoulés depuis la dernière fête ! Les gens commencent à désespérer." }
    { group:295, id:6, text: "Les gens regrettent l'époque où les fêtes contribuaient à dissiper la morosité ambiante. " }
    { group:295, id:7, text: "Quelle fête superbe ! Les préparatifs d'un tel gala sont très longs." }
    { group:295, id:8, text: "Préparer une fête nécessite temps et énergie. Vous devriez y songer dès à présent... " }
    { group:295, id:9, text: "Suffisamment de temps s'est écoulé depuis la dernière fête. Il est temps d'en prévoir une autre." }
    { group:295, id:10, text: "La fête commune est presque prête. Tout le monde attend cet événement avec impatience." }
    { group:295, id:11, text: "La fête commune se prépare. Plus que deux mois avant cet événement !" }
    { group:295, id:12, text: "Les préparatifs pour la fête commune qui doit avoir lieu dans trois mois commencent le mois prochain." }
    { group:295, id:13, text: "Les organisateurs de la fête préparent la fête commune qui doit avoir lieu dans quatre mois." }
    { group:295, id:14, text: "La fête commune aura lieu dans cinq mois. Les organisateurs étudient les suggestions." }
    { group:295, id:15, text: "Les organisateurs pensent que les préparatifs pour la fête commune seront terminés dans six mois." }
    { group:295, id:16, text: "Les organisateurs assurent que la fête commune pourra avoir lieu dans sept mois." }
    { group:295, id:17, text: "La fête commune n'aura pas lieu avant huit mois. Les préparatifs viennent seulement de commencer." }
    { group:295, id:18, text: "Les organisateurs étant débordés, la fête commune ne pourra avoir lieu avant neuf mois." }
    { group:295, id:19, text: "Encore une ? La prochaine fête commune ne pourra pas avoir lieu avant dix mois." }
    { group:295, id:20, text: "La fête somptueuse est presque prête. Tout le monde attend cet événement avec impatience !" }
    { group:295, id:21, text: "La fête somptueuse se prépare, et il ne nous reste plus que deux mois." }
    { group:295, id:22, text: "La fête somptueuse se prépare. Dans trois mois, nous connaîtrons un événement mémorable." }
    { group:295, id:23, text: "Les préparatifs avancent à grands pas, et la fête somptueuse devrait avoir lieu dans quatre mois." }
    { group:295, id:24, text: "Les artistes répètent pour que la fête somptueuse puisse avoir lieu dans cinq mois." }
    { group:295, id:25, text: "Les organisateurs confirment que la nouvelle fête somptueuse aura bien lieu dans six mois." }
    { group:295, id:26, text: "Les organisateurs étudient les suggestions pour la fête somptueuse qui aura lieu dans sept mois." }
    { group:295, id:27, text: "Certains artistes répètent de nouveaux numéros pour la fête somptueuse qui aura lieu dans huit mois." }
    { group:295, id:28, text: "Avec tous les préparatifs qu'il reste à accomplir, la fête somptueuse n'aura pas lieu avant neuf mois." }
    { group:295, id:29, text: "La fête somptueuse n'aura pas lieu avant dix mois." }
    { group:295, id:30, text: "Les organisateurs ont trop à faire pour programmer la prochaine fête somptueuse avant onze mois." }
    { group:295, id:31, text: "La fête grandiose est presque prête. Dans un mois, la bière fraîche coulera à flots." }
    { group:295, id:32, text: "Les préparatifs de la fête grandiose dureront encore deux mois. L'impatience devient insupportable !" }
    { group:295, id:33, text: "La fête grandiose est en cours de préparation. Il ne reste plus que trois mois." }
    { group:295, id:34, text: "Il faut quatre mois pour préparer la fête grandiose. Autant prendre son mal en patience." }
    { group:295, id:35, text: "Les préparatifs débutant le mois prochain, la fête grandiose aura lieu dans cinq mois." }
    { group:295, id:36, text: "Les jongleurs réservent de vraies surprises pour la fête grandiose qui aura lieu dans six mois à peine." }
    { group:295, id:37, text: "Les musiciens écrivent de nouvelles chansons pour la fête grandiose qui aura lieu dans sept mois à peine." }
    { group:295, id:38, text: "Les danseurs répètent et essaient de nouveaux pas pour la fête grandiose qui aura lieu dans huit mois." }
    { group:295, id:39, text: "Les efforts réalisés laissent présager une fête grandiose dans les neuf mois." }
    { group:295, id:40, text: "Les organisateurs se démènent pour que la fête grandiose ait lieu dans dix mois." }
    { group:295, id:41, text: "Les organisateurs pensent pouvoir mettre au point une fête grandiose d'ici onze mois." }
    { group:295, id:42, text: "Les organisateurs étant débordés, la fête grandiose ne pourra avoir lieu avant un an." }
    { group:296, id:0, text: "Demeures éternelles d'Egypte" }
    { group:296, id:1, text: "Mission" }
    { group:296, id:2, text: "Meilleure famille" }
    { group:296, id:3, text: "Difficulté :" }
    { group:296, id:4, text: "Score" }
    { group:296, id:5, text: "Maison de" }
    { group:296, id:6, text: "Pas de score élevé." }
    { group:297, id:0, text: "Le premier ancêtre de votre famille a accédé à un haut rang et a appris les rudiments de la gestion." }
    { group:297, id:1, text: "Après avoir installé la famille à This, votre ancêtre a aidé la confédération thinite à unifier les royaumes de Haute-Egypte et de Basse-Egypte." }
    { group:297, id:2, text: "Les légendes racontent que votre clan a découvert d'importantes technologies et a appris à exploiter l'inondation." }
    { group:297, id:3, text: "Votre famille est entrée dans l'histoire de l'Egypte lorsque Narmer a nommé l'un de vos ancêtres comme architecte du royaume." }
    { group:297, id:4, text: "Votre famille a joué un rôle prédominant dans la fondation de la première capitale égyptienne et la construction du mastaba dans cette cité." }
    { group:297, id:5, text: "D'après la légende, votre famille a ouvert à Timna des mines de cuivre qui ont fortement contribué à la réussite du pharaon Den lors de l'attaque bédouine." }
    { group:297, id:6, text: "Pour la première fois, l'un de vos ancêtres a choisi les eaux plutôt que la terre ferme et a appris toutes les techniques maritimes, y compris celles liées à la guerre." }
    { group:297, id:7, text: "Pour la première fois, l'un de vos ancêtres a choisi les eaux plutôt que la terre ferme et a appris toutes les techniques maritimes liées aux périodes de paix." }
    { group:297, id:8, text: "Les habitants ont établi un avant-poste militaire important loin de la civilisation, ouvrant des routes de commerce vers l'Afrique qui servent toujours." }
    { group:297, id:9, text: "En l'honneur du pharaon Nebka, votre famille a extrait les richesses minières de la première cataracte, sans lesquelles de nombreuses tombes n'auraient pas pu voir le jour et de nombreux nobles n'auraient pas pu accéder au champ de roseaux." }
    { group:297, id:10, text: "Votre ancêtre a fièrement achevé la vision du vizir Imhotep et construit la première pyramide de pierre pour y renfermer la momie de Djoser." }
    { group:297, id:11, text: "Votre héroïque ancêtre a extrait des pierres précieuses et du cuivre du Sinaï sauvage et les féroces habitants de la région ont tout fait pour contrarier cet effort." }
    { group:297, id:12, text: "La progression de votre clan est attestée par la tombe familiale qui se trouve à Meidoum, qui constitue aujourd'hui une preuve du rôle prépondérant de l'Egypte." }
    { group:297, id:13, text: "La forteresse érigée à Buhen et l'habileté avec laquelle vos ancêtres ont repoussé l'ennemi dans cette région ont projeté le pouvoir de l'Egypte dans la seconde cataracte, sur un territoire revendiqué par la Nubie." }
    { group:297, id:14, text: "Tandis que d'autres étaient occupés à repousser les frontières du royaume, votre ancêtre a construit la tombe la plus magnifique jamais construite, la pyramide penchée de Snéfrou." }
    { group:297, id:15, text: "Même lorsque Snéfrou accueillit un héritier que les voyants considéraient comme un tyran, vos propres ancêtres construisirent la pyramide la mieux réussie du monde pour abriter les restes de ce pharaon." }
    { group:297, id:16, text: "Malgré la tyrannie de Koufou, ton ancêtre l'a loyalement servi en tant que gouverneur royal et a défendu les frontières égyptiennes contre les envahisseurs éthiopiens." }
    { group:297, id:17, text: "Libéré de la menace éthiopienne, votre ancêtre a ouvert des carrières productives à Tura pour satisfaire la demande inexplicable de Koufou en calcaire." }
    { group:297, id:18, text: "Votre ancêtre a accédé à la position de nomarque auprès de Koufou et de Khafra et, mu par une volonté rivalisant avec celle du pharaon lui-même, a construit l'éternelle grande pyramide et son sphinx." }
    { group:297, id:19, text: "Le pharaon a déclaré que Rê était le dieu suprême et a chargé votre ancêtre d'étendre le culte solaire au désert occidental ennemi aux fins fonds du royaume." }
    { group:297, id:20, text: "Le pharaon Userkaf a proclamé Rê comme dieu suprême et demandé à votre ancêtre de construire le plus grand temple solaire de tout le Delta, une région vide de pierres de construction." }
    { group:297, id:21, text: "Tandis que les ennemis de l'Egypte pullulaient, votre famille a accédé au grade de chancelier et a empêché les ennemis du royaume de dépasser les limites du pays." }
    { group:297, id:22, text: "Tandis que les ennemis de l'Egypte pullulaient, votre famille a accédé au rang de chancelier et démontré une grande aptitude de gestion tandis que le reste du pays s'écroulait autour d'elle." }
    { group:297, id:23, text: "Vos ancêtres ont offert leur loyauté aux Inyotefs et restauré la gloire de This en dépit des efforts concertés des armées rebelles pour contrarier cette entreprise." }
    { group:297, id:24, text: "Deux factions ont combattu au nom de l'Egypte, même en période de famine. Votre ancêtre en a sauvé beaucoup de ce fléau tout en accordant une aide cruciale à la dynastie légitime." }
    { group:297, id:25, text: "Mentouhotep a accordé à votre famille le rang de vizir et a considérablement compté sur leur aide pour combattre les rebelles et les envahisseurs en puissance qui tentaient d'empêcher la réunification." }
    { group:297, id:26, text: "Mentouhotep a accordé à votre famille le rang de vizir et ses efforts de réunification ont fortement bénéficié de la cité que vous avez fait renaître de ses cendres." }
    { group:297, id:27, text: "Finalement, un membre de votre famille est devenu pharaon. Votre clan est alors devenu une dynastie royale, a fondé une nouvelle capitale et mis fin à l'opposition à force de compassion et d'efforts." }
    { group:297, id:28, text: "Votre divin ancêtre a conquis nos anciens ennemis au nord de la Nubie, a instauré le respect pour votre dynastie dans l'esprit des Ethiopiens et établi un important port sur la mer Rouge." }
    { group:297, id:29, text: "Le port industriel fondé par votre divin ancêtre sur la mer Rouge a apporté une source de richesse considérable à votre peuple et la tombe de votre famille survivra au temps." }
    { group:297, id:30, text: "Votre illustre ancêtre, qui repose aujourd'hui dans un superbe mausolée, a vaincu la flotte nubienne et conquis l'une de ses principales cités." }
    { group:297, id:31, text: "La ville de Bubastis reste aujourd'hui l'un des joyaux de la couronne. Votre ancêtre a édifié une cité dont toute l'Egypte est fière." }
    { group:297, id:32, text: "La transformation des chars des Hyksos en une arme égyptienne et son utilisation contre les ennemis dans tout le royaume est l'une des réalisations les plus brillantes de l'histoire." }
    { group:297, id:33, text: "Votre famille est depuis longtemps bénie par la sagesse. La stratégie de votre ancêtre, qui consistait à inspirer les principaux généraux égyptiens à effectuer des efforts surhumains fut grandement bénéfique." }
    { group:297, id:34, text: "Vous avez fondé un Nouvel empire, renforcé les forêts de Byblos et appris aux féroces Hittites et aux Peuples de la mer à respecter les frontières égyptiennes." }
    { group:297, id:35, text: "Vous avez créé une richesse inespérée pour votre Nouvel empire, tout en défendant les cités égyptiennes de leurs anciens et nouveaux ennemis." }
    { group:297, id:36, text: "Votre règne a été le plus glorieux que l'Egypte ait jamais connu. Nos frontières se sont étendues et notre peuple a connu un luxe jusqu'alors inimaginable." }
    { group:297, id:37, text: "Après avoir vaincu tous les ennemis et apporté une grande prospérité au royaume, vous avez construit une pyramide surpassant même celle du légendaire Koufou." }
    { group:297, id:38, text: "Avec la fondation de Deir el-Medineh, les pharaons pourront se reposer sans craindre d'être dérangés par des pilleurs de tombes." }
    { group:297, id:39, text: "La tombe de Toutankhamon a pu être construite à temps avant de recevoir les riches offrandes funéraires." }
    { group:297, id:40, text: "Le tombeau funéraire de Séthi I est une pure merveille, courtisée par les nombreux pilleurs de tombes assoiffés de richesse. Quelle tristesse que le monde ne puisse plus jamais contempler son éternelle beauté." }
    { group:297, id:41, text: "Le port de Sumur connaît actuellement une forte activité commerciale, en approvisionnant nos cités en bois et en autres denrées précieuses." }
    { group:297, id:42, text: "L'Egypte a connu sa plus grande victoire à la bataille de Qadesh et restauré sa domination sur la terre d'Amurra. La menace Hittite fut définitivement écrasée." }
    { group:297, id:43, text: "Le colosse d'Abou Simbel perpétuera la légende de puissance et de gloire d'Egypte." }
    { group:297, id:44, text: "La dépouille de Ramsès II repose en paix dans sa somptueuse tombe. Le pharaon continuera à guider le royaume d'Egypte pour l'éternité." }
    { group:297, id:45, text: "Les dangereux pirates des mers qui ont tenté de s'établir dans les pays d'Egypte ont été refoulés. Les frontières de l'Egypte ont retrouvé leur sécurité." }
    { group:297, id:46, text: "L'avant-poste fortifié de l'arrière-pays d'Egypte a résisté aux vagues d'attaques des Assyriens, les empêchant ainsi de pénétrer plus avant dans les Deux Pays." }
    { group:297, id:47, text: "Le peuple d'Achoris se souviendra longtemps de la victoire sur la flotte et l'infanterie perses qui a mis fin à leurs rêves de conquête." }
    { group:297, id:48, text: "En l'espace de douze ans, le petit village de pêcheurs s'est développé pour devenir Alexandrie, grande métropole florissante." }
    { group:297, id:49, text: "La grande bibliothèque et le phare de Pharos ont contribué à la renommée d'Alexandrie à travers le monde." }
    { group:297, id:50, text: "Les légions romaines Mithridates ont vaincu Ptolémée XIII, frère rebelle de Cléopâtre, lors d'une grande bataille sur les rives du lac Mariout." }
    { group:297, id:51, text: "Le Caesareum et d'autres temples mortuaires sont autant de sites prestigieux qui contribuèrent au rayonnement d'Alexandrie." }
    { group:297, id:52, text: "La flotte égyptienne et l'armée de Marc-Antoine ont vaincu Octave. L'Egypte et Rome se sont unies sur un pied d'égalité pour dominer le monde." }
    { group:298, id:0, text: "Niveau final de culture" }
    { group:298, id:1, text: "Niveau final de prospérité" }
    { group:298, id:2, text: "Niveau final de monument" }
    { group:298, id:3, text: "Niveau final de royaume" }
    { group:298, id:4, text: "Population totale" }
    { group:298, id:5, text: "Trésorerie finale" }
    { group:298, id:6, text: "Mission terminée en" }
    { group:298, id:7, text: "Niveau de difficulté :" }
    { group:298, id:8, text: "Score final :" }
    { group:298, id:9, text: "année(s)" }
    { group:299, id:0, text: "Résultat direct" }
    { group:299, id:1, text: "Accidentel" }
    { group:299, id:2, text: "Malgré" }
    { group:299, id:3, text: "Aucune cause" }
    { group:299, id:4, text: "Continu/Cyclique" }
    { group:299, id:5, text: "Besoins spécifiques" }
    { group:299, id:6, text: "Automatique" }
    { group:299, id:7, text: "Direct" }
    { group:299, id:8, text: "Accidentel" }
    { group:299, id:9, text: "Malgré" }
    { group:299, id:10, text: "Aucun" }
    { group:299, id:11, text: "Cycle" }
    { group:299, id:12, text: "Spéc." }
    { group:299, id:13, text: "Auto" }
    { group:304, id:0, text: "Page suivante" }
    { group:304, id:1, text: "Page précédente" }
    { group:305, id:0, text: "Votre famille n'a jamais relevé ce défi. Pour afficher les objectifs de la mission, cliquez sur le bouton ci-dessous." }
    { group:306, id:0, text: "Exploitation de henné" }
    { group:306, id:1, text: "Le henné le plus fin est cultivé ici, puis transformé en peinture pour la décoration des tombes funéraires." }
    { group:306, id:2, text: "Récolte :" }
    { group:306, id:3, text: "terminée." }
    { group:306, id:4, text: "Le chef du commerce a décrété l'arrêt de la production de henné." }
    { group:306, id:5, text: "Sans ouvriers, cette ferme ne peut pas produire de henné." }
    { group:306, id:6, text: "L'exploitation a assez de main-d'œuvre. Ils cultivent les plantes dans les champs." }
    { group:306, id:7, text: "La faible main-d'œuvre gêne l'extension de l'exploitation." }
    { group:306, id:8, text: "Cette exploitation manque de main-d'œuvre pour produire assez de henné." }
    { group:306, id:9, text: "Peu d'employés travaillent ici. La récolte de henné risque d'en souffrir." }
    { group:306, id:10, text: "Cette exploitation aride nécessite davantage d'ouvriers pour produire du henné." }
    { group:306, id:11, text: "Des criquets ont dévoré les récoltes et les champs doivent maintenant être mis au repos." }
    { group:306, id:12, text: "Terre :" }
    { group:306, id:13, text: "fertile." }
    { group:306, id:14, text: "Prochaine récolte de henné dans" }
    { group:307, id:0, text: "0,0,0,0   // mission 0" }
    { group:307, id:1, text: "0,0,0,0" }
    { group:307, id:2, text: "0,0,0,0" }
    { group:307, id:3, text: "0,0,0,0   // Nekhen: première mission avec salaire personnel" }
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
    { group:307, id:37, text: "1,0,0,0   // Dernière mission du jeu original" }
    { group:307, id:38, text: "0,0,0,1   // Thoutmôsis" }
    { group:307, id:39, text: "0,0,V,1   // Toutankhamon" }
    { group:307, id:40, text: "0,0,V,1   // Séthi" }
    { group:307, id:41, text: "0,0,0,0   // Sumer" }
    { group:307, id:42, text: "1,1,0,0   // Qadesh" }
    { group:307, id:43, text: "1,1,0,0   // Abou Simbel" }
    { group:307, id:44, text: "1,1,V,0   // Ramsès dans la Vallée" }
    { group:307, id:45, text: "0,0,0,0   // Pi-Yer" }
    { group:307, id:46, text: "0,0,0,0   // Migdol" }
    { group:307, id:47, text: "0,0,0,0   // Tanis" }
    { group:307, id:48, text: "0,0,0,1   // Alexandrie (Alexandre)" }
    { group:307, id:49, text: "1,1,A,1   // Alexandrie (Ptolémée)" }
    { group:307, id:50, text: "0,0,0,0   // César et Cléopâtre" }
    { group:307, id:51, text: "1,1,A,0   // L'héritage de Cléopâtre" }
    { group:307, id:52, text: "1,1,0,0   // Actium" }
    { group:308, id:0, text: "Zoo" }
    { group:308, id:1, text: "Les animaux exotiques font la joie de tous les visiteurs du zoo." }
    { group:308, id:2, text: "Ce zoo dispose d'employés mais nécessite une réserve de gibier pour que les animaux s'y sentent chez eux." }
    { group:308, id:3, text: "Ce zoo dispose d'employés mais n'a plus de paille pour le confort des animaux." }
    { group:308, id:4, text: "Les gens hésitent à visiter un zoo sans gardien. Si cette situation ne s'améliore pas, l'attrait du quartier risque d'en pâtir." }
    { group:308, id:5, text: "Sans animaux, ce zoo est un endroit vraiment triste." }
    { group:308, id:6, text: "Gibier :" }
    { group:308, id:7, text: "Paille :" }
    { group:309, id:0, text: "Le risque d'épidémie est si grand que même les animaux sauvages ont peur." }
    { group:309, id:1, text: "Comment nourrir les animaux si nous avons le ventre vide ?" }
    { group:309, id:2, text: "Nos défenses sont très faibles. Comment pouvons-nous lutter ?" }
    { group:309, id:3, text: "Nous n'avions jamais rencontré un tel manque de main-d'œuvre." }
    { group:309, id:4, text: "Il vaut mieux ne pas trop se montrer lorsque les dieux sont en colère !" }
    { group:309, id:5, text: "Le pharaon est accablé, tous les animaux du zoo sont en danger !" }
    { group:309, id:6, text: "Trouver du travail dans cette ville relève de l'exploit !" }
    { group:309, id:7, text: "Les possibilités de se divertir dans cette ville sont vraiment pitoyables !" }
    { group:309, id:8, text: "La vie ici n'est quand même pas trop désagréable ." }
    { group:309, id:9, text: "Je vis dans cette ville comme un poisson dans l'eau." }
    { group:310, id:0, text: "Info-bulles" }
    { group:310, id:1, text: "Les messages ne s'affichent qu'en haut de l'écran." }
    { group:310, id:2, text: "Infos sur les inondations" }
    { group:310, id:3, text: "Infos démographiques" }
    { group:310, id:4, text: "Volonté satisfaite" }
    { group:310, id:5, text: "Meilleur niveau du royaume" }
    { group:310, id:6, text: "Fêtes" }
    { group:310, id:7, text: "Bénédictions mineures" }
    { group:310, id:8, text: "Evolution des prix" }
    { group:310, id:9, text: "Evolution du commerce" }
    { group:310, id:10, text: "Evolution des salaires" }
    { group:310, id:11, text: "Epidémies" }
    { group:310, id:12, text: "Malaria" }
    { group:310, id:13, text: "Manque de main-d'œuvre" }
    { group:310, id:14, text: "OK" }
    { group:310, id:15, text: "Annuler" }
    { group:311, id:0, text: "Sélectionnez l'ère du monument" }
    { group:311, id:1, text: "Pyramides" }
    { group:311, id:2, text: "Vallée des Rois" }
    { group:311, id:3, text: "Alexandrie" }
    { group:311, id:4, text: "Abou Simbel" }
    { group:312, id:0, text: "Guilde des artisans" }
    { group:312, id:1, text: "Les artisans préparent ici un plâtre à base d'argile et des peintures pour décorer la tombe. " }
    { group:312, id:2, text: "Sans employé, cette guilde ne peut envoyer aucun artisan." }
    { group:312, id:3, text: "Cette guilde dispose de toute la main-d'œuvre nécessaire pour décorer l'intérieur des tombes." }
    { group:312, id:4, text: "La guilde recherche un ou deux artisans pour finir la peinture des tombes." }
    { group:312, id:5, text: "Cette guilde s'efforce de trouver des artisans pour décorer la tombe mais elle manque de main-d'œuvre." }
    { group:312, id:6, text: "Cette guilde manque de main-d'œuvre. En attendant, les quelques ouvriers disponibles font de leur mieux pour décorer la tombe." }
    { group:312, id:7, text: "La peinture des tombes est sérieusement ralentie. Cette guilde recherche des ouvriers pour pouvoir finir les travaux à temps." }
    { group:312, id:8, text: "Les artisans attendent de la peinture venant d'une fabrique ou d'un entrepôt pour pouvoir peindre la tombe." }
    { group:312, id:9, text: "La guilde attend la livraison d'argile pour envoyer des artisans sur le chantier." }
    { group:312, id:10, text: "Peinture:" }
    { group:312, id:11, text: "Argile:" }
    { group:313, id:0, text: "Fabrique de peinture" }
    { group:313, id:1, text: "Le henné est ici écrasé puis transformé en peinture dont les artisans se servent pour décorer les tombes royales." }
    { group:313, id:2, text: "Production à" }
    { group:313, id:3, text: "terminée." }
    { group:313, id:4, text: "Le chef du commerce a arrêté la production de peinture." }
    { group:313, id:5, text: "Ce fabricant de peinture n'a pas d'ouvrier.  La production est complètement asséchée." }
    { group:313, id:6, text: "Ce fabricant de peinture ne manque pas d'ouvriers et la production est importante." }
    { group:313, id:7, text: "Cette fabrique de peinture pourrait augmenter sa production en employant davantage d'ouvriers." }
    { group:313, id:8, text: "Ce fabricant de peinture emploie peu d'ouvriers ce qui ralentit la production." }
    { group:313, id:9, text: "Ce fabricant de peinture a besoin de main-d'œuvre car la production a fortement chuté." }
    { group:313, id:10, text: "La production de ce fabricant de peinture reste faible car il manque de main-d'œuvre." }
    { group:313, id:11, text: "Cette fabrique nécessite du henné provenant d'une exploitation ou d'un entrepôt." }
    { group:313, id:12, text: "Henné :" }
    { group:314, id:0, text: "Fabrique de lampes" }
    { group:314, id:1, text: "Les poteries sont remplies d'huile pour servir de lampes." }
    { group:314, id:2, text: "Production à" }
    { group:314, id:3, text: "terminée." }
    { group:314, id:4, text: "Le chef du commerce a fait cesser la production de lampes." }
    { group:314, id:5, text: "Ce fabricant ne produit aucune lampe faute d'ouvriers." }
    { group:314, id:6, text: "Ce fabricant de lampes ne manque pas de main-d'œuvre et produit un grand nombre d'articles." }
    { group:314, id:7, text: "Ce fabriquant de lampes manque de main-d'œuvre, ce qui ralentit sa production." }
    { group:314, id:8, text: "Ce fabricant manque d'ouvriers et produit peu de lampes." }
    { group:314, id:9, text: "Ce fabricant de lampes manque de main-d'œuvre. Les ouvriers font de leur mieux mais la production a sensiblement baissé." }
    { group:314, id:10, text: "Ce fabricant produit très peu de lampes car il manque sérieusement de main-d'œuvre pour accroître sa production." }
    { group:314, id:11, text: "Pour produire des lampes, cet atelier a besoin d'huile d'un entrepôt." }
    { group:314, id:12, text: "Pour produire des lampes, cet atelier a besoin de poteries d'un entrepôt ou d'un potier." }
    { group:314, id:13, text: "Huile:" }
    { group:314, id:14, text: "Poterie:" }
]
