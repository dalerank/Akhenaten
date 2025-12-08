log_info("akhenaten: messages config started")

game_messages_de {
    message_potter_history {
        id: 1,
        pos [0, 24]
        size [30, 28]
        title { text: "Töpferei" }
        advisor: ADVISOR_TRADE
        content {
            text: "Potters need a supply of clay to function. Some cities can produce their own clay by constructing @92Clay&Pits. Other cities may need to import clay from a trade partner (click @47here for more on trade). @PCartpushers bring supplies of clay to Potters from Clay Pits, if the city has them, or from @4Storage&Yards. The Potter stores some extra clay in its yard to keep him working for awhile if clay deliveries are interrupted for some reason. @PPotters also need road access and a nearby source of labor. Potters are at their most productive if they are fully staffed, but will still operate (although at reduced efficiency) when understaffed. If the Potter is turning out pottery, you will see him hard at work. Cartpushers employed by the Potter take finished pottery to a Storage Yard or to a @473Lamp&Maker (who needs a supply of pottery and oil to produce lamps). @PPottery is an important commodity in the city. @56Houses need a supply of pottery to evolve to higher levels, and pottery must be constantly replenished to prevent houses from devolving to lower levels. Demand for pottery never ceases: households are always replacing broken or worn-out pieces. See @2Bazaars for more on how to get finished goods to the citizens. @PPottery is also integral to the construction of @478Royal&Burial&Tombs. When a Lamp Maker fills pottery with oil, it becomes a powerful lamp that lights the way for tomb workers.  @PPottery can also be imported or exported. See @47trade for information on how to open trade routes. If your city is trading pottery, be sure to keep citizens' needs in mind. Let your @24Overseer&of&Commerce know how much pottery should be stored in Storage Yards for citizens' use, or let your Overseer determine an amount.  @PPeople don't want to live too near a noisy, dusty Potter, so it has a negative effect on the desirability of neighboring land. @L@LTo learn more about pottery making in ancient Egypt, click @198here."
        }
    }

    message_bazaar_history {
        id: 2,
        pos [0, 24]
        size [30, 28]
        title { text: "Basar" }
        content {
            text: "Basare sind das letzte Glied in der Versorgungskette der Bevölkerung mit Nahrungsmitteln und Waren. Sie sind der Dreh- und Angelpunkt des städtischen Vertriebssystems. Ohne sie sind die Aktivitäten von Produktionsstätten und Nahrungsmittelproduzenten umsonst. Basare liefern den Bürgern die benötigten Waren nach Hause. @PMit Warenlagern und Silos haben Stadtbewohner nie direkt zu tun. Es sind die Basarangestellten, die die Waren für die Bürger aus den Warenlagern und Silos beschaffen. Jeder Basar beschäftigt zwei Einkäuferinnen: eine für den Einkauf von Waren in Warenlagern, die andere für den Einkauf in Silos. @PNahrungsmittelkäuferinnen erhalten ihre Waren nur in Silos, Warenkäuferinnen nur in Warenlagern. Jede Basarkäuferin kann jedoch mehr als ein Objekt auf einmal tragen. Benötigt ihr Basar beispielsweise sowohl Getreide als auch Granatäpfel, kann die Nahrungsmitteleinkäuferin beide Nahrungsmittel mitnehmen. Die Händlerin hat die Aufgabe, Waren vom Basar in die Wohngebiete zu bringen. Händlerinnen haben kein festes Ziel und folgen keinem bestimmten Weg. Wann immer eine Händlerin auf eine Kreuzung stößt, muss sie sich für eine Richtung entscheiden. Diese Entscheidung wird nicht jedes Mal gleich ausfallen. Je mehr Kreuzungen es gibt, auf die sie stößt, desto weniger vorhersehbar wird der eingeschlagene Weg. Und während sie so ziellos durch die Stadt streift, gibt es Häuser, denen es an Nahrungsmitteln und Waren mangelt und deren Wohnqualität sich verschlechtert. Wenn Bürger nicht die Nahrungsmittel und Waren erhalten, die sie benötigen, bauen Sie weitere Basare. Mit der Weiterentwicklung der Wohnungen werden diese größer und bieten mehr Bewohnern ein Dach über dem Kopf. Ein auf eine höhere Stufe aufgestiegener Basar (erkenntlich daran, dass eines seiner Zelte durch ein kleines Gebäude ersetzt wird) schickt zwei Fußgänger statt eines einzigen aus. Versäumen Sie nicht, beim Zuzug neuer Bewohner in ein Wohnviertel neue Basare zu bauen.  @PHat die Einkäuferin alle Vorräte beisammen, wandert sie mit ihren Helfern zurück zum Basar. Die Helfer tragen die Waren zum Basar. Je mehr Helfer sichtbar sind, desto mehr Ware hat sie gekauft. Infoklicken Sie auf die Basarkäuferin, um festzustellen, was genau sie zum Basar mitnimmt. Basare beschäftigen darüber hinaus Händlerinnen, die Nahrungsmittel und Waren an den Mann bzw. die Frau bringen. Sie verkaufen alles, was der Basar vorrätig hat - Nahrungsmittel ebenso wie Waren. Häuser werden mit Produkten vom Basar beliefert, indem die Händlerin an ihnen vorübergeht. Beim Vorbeigehen an den einzelnen Häusern bringt die Händlerin auch in Erfahrung, was die Bewohner zukünftig wünschen und teilt dies den Einkäuferinnen mit, damit diese die entsprechenden Waren besorgen. Wenn die Bürger nicht nach Nahrungsmitteln oder bestimmten Waren verlangen, werden diese von den Basarkäuferinnen auch nicht eingekauft. @PUm einen Basar zu bauen, klicken Sie in der Steuerleiste auf den Button 'Gebäude für Lagerung und Vertrieb'. Basare benötigen Arbeitskräfte und eine Straßenanbindung.  @PBesondere Befehle für Basare @L@LStandardmäßig versuchen Einkäuferinnen, die Waren zu beschaffen, nach denen die Bürger verlangen. Um mehr Kontrolle über die Basare der Stadt auszuüben, können Sie 'Besondere Befehle' erteilen.  @PInfoklicken Sie hierzu auf einen Basar, und klicken Sie dann auf den Button 'Besondere Befehle'. Es wird eine Liste aller Waren angezeigt, mit denen der Basar handelt. Indem Sie auf die einzelnen Waren klicken, können Sie den Basar anweisen, diese Ware einzukaufen oder auch nicht. @PPlanung eines effizienten Vertriebssystems @L@LWarenlager, Silo und Basar sind die grundlegenden Bestandteile des Vertriebssystems in Ihrer Stadt. Wenn Sie die Beziehung zwischen diesen drei Einrichtungen verstehen, können Sie die Versorgung Ihrer Bürger mit den gewünschten Nahrungsmitteln und Waren besser gewährleisten. Die Befriedigung der materiellen Bedürfnisse Ihrer Bürger führt zu einer besseren Wohnungsqualität, wodurch sich die Wohlstand-Wertung erhöht und Sie mehr Steuern einnehmen. Beherzigen Sie die folgenden Tipps beim Planen der Stadt, um sicherzustellen, dass die Wohngebiete regelmäßig mit allen Nahrungsmitteln und Waren versorgt werden, die sie benötigen. Errichten Sie Basare in der Nähe von Warenlagern und Silos. Wenn Sie die Basare der Stadt gut mit Waren versorgen, wird es Ihren Bürgern materiell kaum an etwas fehlen. Die beste Methode, die Basare der Stadt ausreichend mit Waren zu versorgen, ist, sie in der Nähe eines Silos und eines Warenlagers einzurichten, so dass Einkäuferinnen nur kurze Wege zurücklegen müssen. Errichten Sie Basare in der Nähe von Warenlagern und Silos.  @PDer Bedarf der Menschen an Produkten zur Deckung der Grundbedürfnisse wie z.B. Nahrungsmittel und Töpferwaren muss gedeckt werden, bevor Sie sich weitergehenden Wünschen der Bürger wie etwa denen nach Bier oder Leinen zuwenden können. Basarkäuferinnen ignorieren Warenlager, auch wenn diese randvoll mit Leinen sind, wenn die von ihnen bedienten Häuser z.B. dringend Geschirr benötigen. Daher ist es sehr wichtig, die regelmäßige Versorgung mit einer Ware zu gewährleisten, sobald die Bürger einen Bedarf danach anmelden. Denken Sie daran, dass mit dem Ausbau von Häusern diese meist mehr Bewohner beherbergen können und somit mehr Waren verbrauchen. Manchmal werden Sie weitere Basare errichten müssen, um die Versorgung eines Wohngebiets zu gewährleisten. Klicken Sie auf ein Haus, um festzustellen, was dessen Bewohner gerade benötigen.  @PUm zu gewährleisten, dass die Bewohner der Stadt die Nahrungsmittel und Waren bekommen, die sie brauchen, errichten Sie in der Nähe von Basaren Silos und Warenlager. Verwenden Sie die 'Besonderen Befehle' für Silos und Warenlager, um dafür zu sorgen, dass dort die vom Basar benötigten Waren auf Lager gehalten werden. @PUm mehr Kontrolle über einen Basar zu erhalten, klicken Sie auf den Button 'Besondere Befehle', um eine Liste aller Waren angezeigt zu bekommen, die der Basar anbieten kann. Klicken Sie auf eine Ware, um dem Basar die Anweisung zum Kaufen oder zum Nicht-Kaufen zu erteilen. @PZwar müssen Bürger in der Nähe von Basaren leben, um Zugang zu allen gewünschten Waren zu haben, dennoch will niemand allzu nah bei einem Basar wohnen. Dort ist es laut, manchmal stinkt es, und Leute, auf deren engere Bekanntschaft man eigentlich lieber verzichtet, treiben sich dort gern herum.  @L@LUm ein Gefühl für die Optik, die Geräuschkulisse und die Gerüche eines altägyptischen Basars zu bekommen, klicken Sie @199hier."
        }
    }

    message_building_granary {
        id: 3,
        pos [0, 24]
        size [30, 28]
        title { text: "Silo" }
        content {
            text: "Wenn die Ernte eingefahren, das Wild zerlegt, die Fische ausgenommen und die Rinder verarbeitet sind, müssen die Nahrungsmittel irgendwo gelagert werden. Dieser Ort ist das Silo.  @PJede Farm, auf der Nahrungsmittel angebaut werden, und jedes Gebäude, in dem Nahrungsmittel produziert werden, beschäftigt einen Karrenschieber. Diese kräftigen Männer sind für den sicheren Transport der Nahrungsmittel in die Silos verantwortlich. Sie werden zwar stets zuerst das nächstgelegene Silo aufsuchen, legen aber auch lange Strecken zurück, wenn die nahe gelegenen Silos keinen Platz für ihre Waren haben. Falls kein Silo in der Stadt mehr Platz hat, oder falls die Silos nicht mit voller Belegschaft arbeiten, sieht man Karrenschieber verwirrt auf der Straße herumstehen, bis ein Silo wieder Platz für die Nahrungsmittel hat. Um herauszufinden, warum ein untätiger Karrenschieber sich nicht bewegt, infoklicken Sie auf ihn.  @PKarrenschieber bringen ihre Ware in ein Warenlager, wenn Sie das Warenlager ausdrücklich beauftragt haben, ein bestimmtes Nahrungsmittel anzunehmen. Auch hierbei wird das nächstgelegene zuerst angesteuert. Der Karrenschieber geht sogar am Silo vorbei und bringt die Ware direkt in ein Warenlager, wenn Sie in den 'Besonderen Befehlen' des Warenlagers ein bestimmtes Nahrungsmittel auf 'Annehmen' einstellen. Von den Warenlagern aus können die Nahrungsmittel an Handelspartner exportiert werden.   @PSie können sofort sehen, wie voll ein Silo ist, wenn Sie einen Blick durch die Einfüllöffnungen werfen. Infoklicken Sie auf das Silo, um herauszufinden, welche Menge von welcher Art Nahrungsmittel dort auf Lager ist.  @PUm ein Silo zu bauen, klicken Sie in der Steuerleiste auf den Button 'Gebäude für Lagerung und Vertrieb'. Silos benötigen sowohl eine Straßenanbindung als auch Arbeitskräfte.  @PBesondere Befehle für Silos @L@LWenn Ihre Stadt größer wird, kann es sinnvoll sein, manchen Silos bestimmte Anweisungen zur Nahrungsmittelverwaltung zu erteilen. Anweisungen für Silos erteilen Sie, indem Sie in dem Fenster, das sich nach einem Infoklick auf ein Silo öffnet, die Option 'Besondere Befehle' anwählen.  @PIm Fenster 'Besondere Befehle' sind alle Arten von Nahrungsmitteln aufgelistet, die Ihrer Stadt zur Verfügung stehen. Die Standardeinstellung für Silos ist 'Alle annehmen', und zwar für alle Nahrungsmittel, bis zur Kapazitätsgrenze des Silos. Indem Sie auf den Button neben einem Nahrungsmittel klicken, können Sie einen der folgenden Befehle für die einzelnen Nahrungsmittel anwählen:  @PAlle annehmen/Silo füllen @L@LMöglicherweise möchten Sie auch die Menge eines bestimmten Nahrungsmittels, die ein Silo zur Lagerung aufnimmt, beschränken (z.B. um zu gewährleisten, dass das Silo verschiedene Nahrungsmittel vorrätig hält). Zu diesem Zweck können Sie einen Wert zwischen 1/4 bis 3/4 der Silogröße einstellen. Sie können die Menge aber auch unbegrenzt lassen und alle Nahrungsmittel annehmen. Benutzen Sie die Scroll-Buttons außen rechts neben jedem Eintrag, um eine Beschränkung einzustellen.  @PNicht annehmen @L@LWenn ein Silo ein bestimmtes Nahrungsmittel gar nicht mehr annehmen soll, klicken Sie auf den Button, bis der Eintrag 'Nicht annehmen' angezeigt wird. Im Silo werden dann zwar keine weiteren Lieferungen dieses Nahrungsmittels angenommen, Basareinkäuferinnen und andere Silos können aber weiterhin die Ware daraus entnehmen, bis der Vorrat erschöpft ist.   @PFordern bis zu @L@L Wenn in einem Silo ein bestimmtes Nahrungsmittel, das Sie gerne vorrätig hätten, auszugehen droht, können Sie dieses Nahrungsmittel von anderen Silos anfordern. Welche Menge davon Sie gerne hätten, können Sie mit den Scroll-Buttons auf der rechten Seite des Nahrungsmittels einstellen. Die Karrenschieber des Silos begeben sich dann zu den anderen Silos oder zu Warenlagern, um das Nahrungsmittel zu besorgen, bis die angegebene Menge im Silo eingelagert ist. Karrenschieber werden jedoch keine Nahrungsmittel aus Silos entnehmen, denen der gleiche Befehl erteilt wurde, denn dann würden sie einen Großteil ihrer Zeit damit verbringen, die gleiche Ware einfach nur hin und her zu verfrachten.  @PNahrungsmittel wegschicken @L@LWenn ein Silo ein bestimmtes Nahrungsmittel nicht mehr auf Lager halten soll, klicken Sie auf den Button, bis der Eintrag 'Nahrungsmittel wegschicken' angezeigt wird. Die Karrenschieber des Silos suchen dann einen anderen Lagerort für dieses Nahrungsmittel, bis der Bestand des Silos an dieser Ware erschöpft ist.  @L@LSilos sind staubig, häufig voller Ungeziefer und deshalb alles andere als beliebte Nachbarn. Ihre Bürger leben nicht gerne in der Nähe von Silos. @L@LKlicken Sie @5hier, um weitere Informationen über Silos im alten Ägypten zu erhalten."
        }
    }

    message_building_storage_yard {
        id: 4,
        pos [0, 24]
        size [30, 28]
        title { text: "Warenlager" }
        content {
            text: "Warenlager sind Aufbewahrungsorte für alle fertigen Produkte sowie für überschüssige Rohstoffe. Hier können auch Nahrungsmittel aufbewahrt werden, wenn Sie den Befehl dazu erteilen (siehe 'Besondere Befehle'). Außerdem können sie bei Import und Export nützlich sein (siehe Eintrag @47Handel).  @PWarenlager benötigen eine Straßenanbindung und Arbeitskräfte, die in der Nähe wohnen. Warenlager arbeiten dann am effizientesten, wenn sie voll besetzt sind. Sie können auch mit weniger Personal arbeiten, aber dann werden möglicherweise bestimmte Waren nicht mehr angenommen. @PJedes Warenlager ist in acht Abschnitte unterteilt und kann bis zu acht verschiedene Waren lagern. Ein Abschnitt kann immer nur Waren einer Sorte annehmen. Dieselbe Ware kann aber in mehreren Abschnitten gelagert werden. Die Menge der einzelnen lagerbaren Waren hängt von deren Größe ab. Je größer die Waren, desto weniger können gelagert werden. So kann ein Abschnitt eines Warenlagers zahlenmäßig z.B. wesentlich mehr Geschirr als Stein lagern.  @PViele der anderen Gebäude benötigen einen einfachen Zugang zu den Warenlagern. @46Gewerbestätten liefern ihre Waren dem nächstgelegenen Warenlager. Basarkäuferinnen wiederum kaufen ihre Waren im nächstgelegenen Warenlager ein. Und auch Warenlager beliefern immer zuerst die nächstgelegenen Gebäude mit Rohstoffen und anderen benötigten Waren. Karrenschieber aus Warenlagern legen, falls erforderlich, längere Strecken zurück - wenngleich nicht besonders gerne -, aber wenn die Gewerbestätten aus diesem Grund auf Nachschub warten, kann es sein, dass ihr Betrieb unterbrochen werden muss. Daher ist es sinnvoll, Warenlager in der Nähe aller Einrichtungen zu errichten, die solche Lager benötigen. @PMit einem Infoklick auf ein Warenlager erhalten Sie eine Liste, der Sie entnehmen können, welche Menge jeder Ware in diesem speziellen Warenlager vorrätig ist und ob weitere Waren angenommen werden können. Kann ein Warenlager nichts mehr von einer Ware aufnehmen, wird diese Ware gelb angezeigt. @PMit den 'Besonderen Befehlen' können Sie den Warenein- und -ausgang steuern. Wenn Sie auf den Button 'Besondere Befehle' klicken, wird eine Liste sämtlicher Waren angezeigt, die der Stadt derzeit verfügbar sind. Manchmal haben Sie Zugang zu Dutzenden verschiedener Waren. Verwenden Sie die Scroll-Buttons oben im Bildschirm, um mehr verfügbare Waren anzuzeigen. @PKlicken Sie auf eine Ware, um dem Warenlager Anweisungen dazu zu erteilen. Diese Befehle stehen zur Verfügung: @L@LAlle annehmen/Füllen @LSetzen Sie diesen Befehl ein, um die Menge einer bestimmten Ware zu begrenzen, die ein Warenlager annimmt. Sie können dem Warenlager Anweisung erteilen, seine Kapazität zu 1/4, 1/2 oder 3/4 auszunutzen. Wenn Sie die Annahme einer bestimmten Ware nicht begrenzen wollen, erteilen Sie dem Warenlager für diese Ware die Anweisung 'Alle annehmen'. Diese Option ist nützlich, wenn ein Warenlager gleiche Mengen verschiedener Waren lagern soll, oder wenn ein Warenlager Nahrungsmittel für den Export lagern soll.  @L@LNicht annehmen @LVerwenden Sie diesen Befehl, um einem Warenlager die Anweisung zu geben, eine Ware gar nicht mehr anzunehmen. Das Warenlager nimmt dann keine Lieferung dieser Ware mehr an. Basarkäuferinnen, Handelspartner und die Gewerbestätten der Stadt können die gelagerten Waren jedoch aufbrauchen. Mit dieser Option können Sie dafür sorgen, dass Lieferanten an einem nahe gelegenen Warenlager vorbeigehen und stattdessen ein weiter entfernt gelegenes Warenlager beliefern. Wenn Sie keine anders lautenden Befehle erteilen, nehmen Warenlager keine Nahrungsmittellieferungen an, so dass diese an die Silos gehen.  @L@LFordern bis zu @LGeht einem Warenlager eine bestimmte Ware langsam aus, die Sie gerne auf Lager halten würden, können Sie den Befehl 'Fordern bis zu' einsetzen. Der Karrenschieber des Warenlagers sucht dann in anderen Warenlagern nach der Ware, bis die Forderung erfüllt ist. Sie können dem Warenlager Anweisungen erteilen, 1/4, 1/2, 3/4 oder die gesamte Kapazität des Lagers mit der Ware zu füllen. Mit dieser Option können Sie gewährleisten, dass auch entlegenere Warenlager mit Waren versorgt werden. @L@LLeeren @LWenn Sie diesen Befehl ausgeben, versucht der Karrenschieber des Warenlagers, den Bestand an dieser Ware abzubauen. Er sucht dann nach Gewerbestätten oder anderen Warenlagern, die noch Kapazitäten für die Ware frei haben. Setzen Sie diesen Befehl ein, wenn Sie beschlossen haben, ein Warenlager abzureißen, oder wenn Sie eine bestimmte Ware daraus entfernen wollen. @L@LWarenlager sind wichtig, damit Sie die Bürger der Stadt mit Waren versorgen können. @2Basare holen die Waren, die die Bürger benötigen, direkt aus Warenlagern. Warenlager sind außerdem von entscheidender Bedeutung für den Handel. Sämtliche importierten Waren werden in Warenlagern aufbewahrt, und alle für den Export vorgesehenen Waren werden dort gelagert, bis Händler aus anderen Städten herkommen, um die Waren abzuholen. @L@LWeitere Informationen über altägyptische Warenlager erhalten Sie, indem Sie @6hier klicken."
        }
    }

    message_granary_history_2 {
        id: 5
        pos [0, 24]
        size [30, 20]
        title { text: "Silo" }
        content {
            text: "Da während der Überschwemmung praktisch keine Landwirtschaft möglich war, kam den Silos eine zentrale Bedeutung zu - mit ihnen konnte man dafür sorgen, dass die Bürger auch zu dieser Zeit genug zu essen hatten. In Silos wurden nicht nur Getreide und andere Nahrungsmittel aufbewahrt, sondern hier wurde auch Mehl hergestellt.  @L@LSilos entwickelten sich im Laufe der Zeit immer weiter. In der prädynastischen Zeit waren die Silos wie ein Kegel mit einer runden Kuppel geformt. Sie bestanden aus Holz oder Ziegeln, und die größten dieser Silos waren mit Leitern oder Treppen ausgestattet, die zu den Einfüllöffnungen führten. Im Mittleren Reich war das Silo quadratisch und hatte ein flaches Dach mit mehreren Einfüllöffnungen. Den Silos dieser Epoche sind die Silos in 'Pharao' nachempfunden. Ein dritter Silotyp wurde nur für Saatgut verwendet, das in der nächsten Saison ausgesät werden sollte. Diese Silos waren trapezförmig, sahen also ganz anders aus als der für Nahrungsmittel verwendete Typ, damit man dieses Getreide nicht versehentlich verzehrte. @L@LDie meisten Silos wurden streng von der Regierung verwaltet. Soldaten, Bauarbeiter und andere nichtlandwirtschaftliche Arbeiter wurden aus diesen Beständen ernährt. Einige wohlhabende Bürger besaßen eigene Silos, und manche Bauern besaßen eigene kleine Silos, um den Teil der Ernte aufzubewahren, den sie behalten durften."
        }
    }

    message_storage_yard_history {
        id: 6
        pos [0, 24]
        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Warenlager", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Warenlager befanden sich in der Nähe des Nils und größerer Handelsrouten. Hier wurden überschüssige Waren für den Handel gelagert. Da kaum Regen zu befürchten war, hatten viele Warenlager im alten Ägypten kein Dach. Ihr Inventar wurde von Schreibern genau überwacht."
        }
    }

    message_keyboard_commands {
        id: 7
        pos [0, 24]
        size [30, 28]
        title { text: "Tastaturbefehle" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Einige Befehle in 'Pharao' können über die Tastatur ausgegeben werden. Es handelt es sich dabei um diese Befehle: @L@LTaste      Effekt @LA      Erteilt einem angewählten Kriegsschiff den  @PBefehl, alle Feinde anzugreifen. @L@LK      Ruft die Spezialkarte 'Risiken:  @PKriminalität' auf oder erteilt einer angewählten @PWagenlenker-Kompanie den Befehl zum Angriff. @L@LD      Ruft die Spezialkarte 'Risiken: Schäden' @Pauf. @L@LE      Erteilt einem angewählten Transportschiff  @Pden Befehl, allen Feinden aus dem Weg zu @Pgehen.  @L@LF      Ruft die Spezialkarte 'Risiken: Feuer' auf  @Poder erteilt einer angewählten Kompanie den Befehl,  @Pzum Fort zurückzukehren. @L@LH      Verbirgt Felswände @L@LP      Erteilt einem angewählten Schiff den Befehl,  @Pdie aktuelle Position zu halten. @L@LL      Zentriert Ihre Ansicht bei jedem Druck  @Pauf eine andere Kompanie.  @L@PWenn eine Kompanie angewählt ist, erteilt  @Pdiese Taste den Befehl 'Stellung in loser  @PFormation halten'. @L@LM     Wenn Sie ein Monument in der  @PGebäudeliste anwählen, wird dessen  @PAbbildung an den Mauszeiger angehängt, @PDamit erkennen Sie, welche Fläche dieses @PMonument belegt. Wenn Sie die M-Taste  @Pgedrückt halten, wird der 'Abdruck' des @PMonuments an dieser Stelle fixiert, und @PSie können Ihre Ansicht innerhalb der @PStadt wechseln, ohne die vorläufige @PPosition des Monuments ändern zu müssen. @P Lassen Sie die M-Taste los, um das @Pnormale Mausverhalten wiederherzustellen, @Poder klicken Sie, um das Monument an der @PAbdruck-Position zu platzieren. @L@P       Wenn Sie M drücken, während eine  @PMilitärkompanie angewählt ist, wird der  @P'Aufräum'-Befehl erteilt. @L@LN      Erteilt einer angewählten Kompanie  @Poder einem angewählten Kriegsschiff den  @PBefehl, alle Feinde in der Nähe @Panzugreifen. @L@LP      Unterbricht den Zeitablauf im Spiel.  @PSolange das Spiel auf 'Pause' steht, können  @PSie keine Gebäude errichten. @L@LR      Beim Platzieren einer Statue, eines  @PStadttors oder eines Tempelkomplexes können  @PSie durch Drücken der R-Taste die Ausrichtung  @Pdes Gebäudes um eine Vierteldrehung im  @PUhrzeigersinn drehen. Statuen werden in  @Punterschiedlichen Ausführungen angezeigt.  @L@P       Ist eine Militärkompanie angewählt,  @Perteilen Sie den Soldaten mit der R-Taste den  @PBefehl, ihre Ausrichtung zu ändern (drehen).  @PWeiterhin wird mit der R-Taste einem angewählten  @PTransport- oder Kriegsschiff der Befehl erteilt, zu  @PReparaturzwecken zur Werft zurückzukehren. @L@PS      Ruft die 'Spezialkarte: Steuer' auf. @L@LT      Ruft die Spezialkarte 'Risiken: Probleme' auf.  @L@PWenn eine Kompanie angewählt ist, wird mit  @Pder T-Taste der Befehl 'Stellung in enger Formation  @Phalten' ausgegeben. @L@PV      Ruft die Spezialkarte 'Risiken: Malaria' auf. @L@LW     Ruft die Spezialkarte 'Wasser' auf. @L@PIst ein Kriegs- oder Transportschiff angewählt,  @Perteilen Sie diesem mit der W-Taste den Befehl,  @Pwieder in den Heimathafen zurückzukehren. @L@LLeertaste   Drücken Sie die Leertaste, um  @Pzwischen der zuletzt angewählten Karte und  @Pder normalen Stadtansicht zu wechseln. @L@LESC    Hiermit verlassen Sie das Spiel. @L@LX      Erhöht die Spielgeschwindigkeit um 10%. @L@LY      Verringert die Spielgeschwindigkeit um 10%. @L@LZ      Ruft die Spezialkarte 'Risiken: Krankheit' auf. @L@LTAB      Aufseher der Arbeitskraft @L@L1        Aufseher des Militärs @L@L2       Aufseher der Politik @L@L3      Aufseher der Wertungen @L@L4     Aufseher des Handels @L@L5     Aufseher der Silos @L@L6     Aufseher der Gesundheit @L@L7     Aufseher des Wissens @L@L8     Aufseher der Unterhaltung @L@L9     Aufseher der Tempel @L@L0     Aufseher der Finanzen @L@Lß      Hauptaufseher @L@L+      Aufseher der Monumente @L@LCTRL+F1 @PMarkiert die aktuelle Position, die Sie dann mit F1 anspringen können. @L@LCTRL+F2 @PMarkiert die aktuelle Position, die Sie dann mit F2 anspringen können. @L@LCTRL+F3 @PMarkiert die aktuelle Position, die Sie dann mit F3 anspringen können. @L@LF1     Springt zur F1-Markierung. @L@LF2     Springt zur F2-Markierung. @L@LF3     Springt zur F3-Markierung. @L@LF6    Schaltet zur Fenster-Ansicht um. @L@LF7    Bildschirmauflösung 640x480 einstellen @L@LF8    Bildschirmauflösung 800x600 einstellen @L@LF9     Bildschirmauflösung 1024x768 einstellen"
        }
    }

    message_work_camp_history {
        id: 8
        pos [0, 24]
        size [30, 28]
        title { text: "Arbeiterlager" }
        content {
            text: "Gruppen von Bauern sammeln sich in den Arbeiterlagern für die Zuteilung zur Arbeit. Während der Anbauzeit schickt das Arbeiterlager höchstwahrscheinlich die meisten seiner Arbeiter auf die Farmen. Wenn alle Farmen voll besetzt sind oder gerade Überschwemmungszeit ist, werden die Arbeiter dagegen zu aktiven Monumentprojekten in der Stadt geschickt. @PArbeiterlager beherbergen nicht nur die Bauern, die das Land im Überschwemmungsgebiet bearbeiten, sondern auch die Arbeitskräfte, die für den Bau eines Monuments benötigt werden. Wenn Maurer oder Steinmetze an der Baustelle bereitstehen und in den Warenlagern die notwendigen Vorräte vorhanden sind, zieht eine Gruppe Bauern einen riesigen Schlitten mit den benötigten Rohstoffen (Steine oder Ziegel) zur Baustelle. Die oberste Priorität eines Arbeiterlagers besteht darin, während der Pflanz- und Erntezeit Bauern für die Arbeit auf den Farmen im Überschwemmungsgebiet bereitzustellen. Baustellen kommt eine untergeordnete Bedeutung zu. Wenn Sie jedoch genügend Arbeiterlager errichten, kann die Arbeit an den Monumenten das ganze Jahr hindurch, auch während der Pflanz- und Ernteperiode, fortgesetzt werden. Obwohl ein Arbeiterlager durchaus Arbeiter für alle Monumente und Farmen bereitstellen kann, gilt: Je mehr Arbeiterlager Sie haben, desto schneller erhalten Farmen und Bauprojekte die benötigten Arbeitskräfte. Gibt es mehr Arbeiterlager, gibt es auch mehr Arbeiter, was den Bau von Monumenten beschleunigt. @PGenau wie andere Fußgänger haben auch Arbeiter ein begrenztes Arbeitsleben. Die Zeit, die sie für den Weg zur Arbeit brauchen, wird nicht mit Arbeiten verbracht. Bauen Sie also die Arbeiterlager lieber nicht allzu weit von den Farmen im Überschwemmungsgebiet entfernt. @PSowohl Arbeiterlager als auch Farmen im Überschwemmungsgebiet brauchen Zugang zu Straßen. Arbeiterlager benötigen außerdem Arbeitskräfte. @L@LWeitere Informationen zum Thema Arbeitsleben im alten Ägypten finden Sie @155hier."
        }
    }

    message_frequently_asked_questions {
        id: 9
        pos [0, 24]
        size [30, 28]
        title { text: "Häufig gestellte Fragen" }
        content {
            text: "Geld @PF: Ich will, dass meine Stadt Geld hat - VIEL Geld. Wie stelle ich es am besten an, dass die Stadtkasse sich rasch füllt? @PA: Achten Sie darauf, dass die Einnahmen höher sind als die Ausgaben. Sorgen Sie ebenfalls dafür, dass möglichst alle Bürger Steuern bezahlen. @P Wenn Sie den Steuersatz anheben, bringt das zwar mehr Geld in die Stadtkasse, aber verursacht schlechte @39Stimmung&in&der&Stadt. Sie sollten außerdem so schnell wie möglich @47Handelsbeziehungen aufbauen und so viele Waren wie möglich exportieren. (Schauen Sie auf der @32Weltkarte nach, wie nahe die Stadt an die jährliche Höchstgrenze für den Handel herangekommen ist.)  @PWenn Sie die städtischen Ausgaben verringern, verbessert auch das die Einnahmensituation. Bauen Sie die Stadt langsam und planvoll aus. Schon die Gebäude an sich verursachen natürlich Kosten, aber Sie müssen daran denken, dass auch Angestellte bezahlt werden müssen. Wenn Sie die Stadt zu schnell vergrößern, dann können die Lohn- und Nebenkosten Sie rasch ins Minus bringen. @L@PF: Warum kann meine Stadt keine Steuern eintreiben? @PA: Ohne einen Palast können Städte keine Steuern eintreiben. @L@PF: Ich stürze mich mit voller Energie auf meine Aufgabe, bekomme aber kein Gehalt. Was ist da los? @PA: Ja, ja, die Bezahlung. Um in 'Pharao' ein persönliches Gehalt beziehen zu können, müssen Sie zunächst einen Wohnsitz errichten. @L@PF: Wie entrichte ich meinen Tribut? Und was passiert, wenn ich es nicht tue? @PA: Ihre Stadtkasse entrichtet den Tribut automatisch am Jahresende, vorausgesetzt, es ist genug Geld da. Sie sollten bewusst darauf achten, dass am Jahresende wirklich genug Geld in den Tresoren liegt. Sollte die Stadtkasse leer sein, können Sie Ihren Tribut nicht entrichten, und das verschlechtert Ihre @35Königreich-Wertung. Wenn Sie in zwei aufeinander folgenden Jahren keinen Tribut entrichten können, fällt die Königreich-Wertung noch ein bisschen mehr, und wenn Sie auch danach zahlungsunfähig bleiben, warten harte Strafen auf Sie. Siehe auch @48Schulden. @L@LFußgänger @PF: Eines meiner Warenlager (oder auch Silos bzw. Produktionsstätten) produziert Fußgänger, die sich sofort in Luft auflösen, nachdem sie das Gebäude verlassen haben. Was habe ich falsch gemacht? @PA: Diese Fußgänger können ihr gewünschtes Ziel nicht erreichen. Möglicherweise ist Ihr Straßennetz irgendwo unterbrochen, oder es gibt zwei an das Gebäude angrenzende Straßen, von denen nur eine zu einem für die Fußgänger vorgesehenen Ziel führt. Fußgänger, die kein vorgesehenes Ziel erreichen können, sind so frustriert, dass sie sich einfach auflösen. Das Gebäude, für das sie arbeiten, schickt laufend neue Fußgänger auf den Weg - in der Hoffnung, dass sie nicht wie ihre Vorgänger an der Aufgabe scheitern. Springen Sie zum Hilfeeintrag @57Straßen, und lesen Sie sich dort den Abschnitt 'Gebäude mit zwei angrenzenden Straßen' durch. @L@PF: Wie kann es passieren, dass ein Gebäude, das angeblich Zugang zu Arbeitskräften hat, keine Arbeiter findet? @PA: Vermutlich haben Sie eine @358Straßensperre zu nahe am Gebäude errichtet. Beobachten Sie das Gebäude ein paar Augenblicke lang, um festzustellen, ob der Fußgänger auf der richtigen Seite der Straßensperre aus dem Gebäude heraustritt. Manchmal sind Gebäude überzeugt, Zugang zu Arbeitskräften zu haben, aber die Straßensperre verhindert, dass der Fußgänger jemals auf Arbeitskräfte stößt.  @L@LReligion @PF: Ich würde gern ein Fest ausrichten, aber ich darf nicht. Wieso? @PA: Es gibt eine ganze Reihe von möglichen Ursachen, wenn Sie kein Fest ausrichten können. Verfügt Ihre Stadt über einen Festplatz? Innerhalb von zwölf Monaten kann eine Stadt maximal zwei Feste ausrichten. Wenn Sie ein gewaltiges Fest ausrichten, sollten Sie darauf achten, dass genug Biervorräte vorhanden sind, um das Fest abzuhalten. Wenn die Stadt ein Fest nicht bezahlen kann, dann können Sie auch keines ausrichten. @L@PF: Der Schutzgott meiner Stadt ist böse auf mich. Was kann ich tun, um ihn zu besänftigen? @PA: Der Schutzgott einer Stadt verlangt mehr Aufmerksamkeit als die anderen lokalen Gottheiten. Achten Sie darauf, dass ihm (oder ihr) in Ihrer Stadt mehr Tempel und Schreine als den anderen Gottheiten geweiht sind, und ziehen Sie in Erwägung, einen 'Großen Tempelkomplex' zu Ehren der Schutzgottheit zu errichten. @L@LUnterhaltung @PF: Ich kann keinen geeigneten Bauplatz für die von mir geplante Unterhaltungseinrichtung finden. Woran könnte es liegen? @PA: Mit Ausnahme von Senet-Häusern müssen alle Unterhaltungseinrichtungen auf einer Straßengabelung oder auf einer Straßenkreuzung errichtet werden. Außerdem muss rund um die Kreuzung jeweils ein Feld frei bleiben, damit genug Platz für die Bühnen der Unterhaltungseinrichtung bleibt. @L@PF: Meine Stadt hat jede Menge Unterhaltungseinrichtungen, aber keine Künstler. Was ist da los? @PA: Vergewissern Sie sich, dass es in der Stadt entsprechende Ausbildungsstätten gibt. @L@LLandwirtschaft @PF: Warum produzieren die Farmen im Überschwemmungsgebiet keine Erträge? @PA: Prüfen Sie, ob es in der Nähe der Farmen ein Arbeiterlager gibt.  @L@PF: Wie viele Farmen im Überschwemmungsgebiet können durch ein Arbeiterlager mit Arbeitskräften versorgt werden? @PA: Das ist verschieden. Lesen Sie in der Hilfe den Themenpunkt @8Arbeiterlager durch. @L@LLagerung und Vertrieb @PF: In den Basaren gibt es nicht genug Nahrungsmittel und Gebrauchswaren. Was kann ich tun, damit sich die Stände füllen? @PA: Sorgen Sie dafür, dass es in der Nähe des Basars ein Silo und ein Warenlager gibt. Wenn der Weg für eine Basarkäuferin zu lang ist, dann gehen ihrem Basar zwangsläufig die Vorräte aus, während sie unterwegs ist. Machen Sie Gebrauch von den 'Besonderen Befehlen', um sicherzustellen, dass Silos und Warenlager über ausreichende Vorräte verfügen. @L@PF: Wie kann ich erreichen, dass Warenlager möglichst effektiv arbeiten? @PA: Um das Beste aus @4Warenlagern herauszuholen, sollten Sie ihren Standort sorgfältig planen und Gebrauch von den 'Besonderen Befehlen' machen. Warenlager sollten in der Nähe von Einrichtungen gebaut werden, die auf ihre Dienstleistungen angewiesen sind, zum Beispiel Basare, Docks usw. Machen Sie Gebrauch von den 'Besonderen Befehlen', damit die gelagerten Waren diejenigen sind, die von diesen nahen Einrichtungen benötigt werden. Warenlager sollten außerdem in der Nähe von Gewerbebetrieben errichtet werden, damit die Karrenschieber dieser Betriebe möglichst kurze Lieferwege haben. @L@LMonumente @L@PF: Ich brauche einen bestimmten Rohstoff für den Bau eines Monuments, aber meine Stadt kann ihn nicht selbst produzieren, und niemand will ihn mir verkaufen. @PA: In einigen Missionen werden die benötigten Handelsrouten erst zugänglich, wenn Sie die Forderungen anderer Städte zufrieden gestellt haben. Wenn Sie der ersten Forderung nicht nachkommen, erhalten Sie in der Regel später nochmals Gelegenheit, sie zu erfüllen. Wenn Sie den Forderungen wiederholt nicht nachkommen, verlieren Sie möglicherweise die Mission. In jeder Mission stehen alle notwendigen Rohstoffe und Waren zur Verfügung ... aber manchmal muss man sich anstrengen. @L@LHandel @PF: Ich habe eine Handelsroute eröffnet, aber meine Stadt importiert und exportiert überhaupt nichts. Wie bringe ich den Handel in Schwung? @PA: Schauen Sie bei Ihrem Aufseher des Handels vorbei, und geben Sie ihm Anweisungen, welche Produkte er kaufen und verkaufen soll. Achten Sie darauf, dass es in der Stadt ein Warenlager und gegebenenfalls ein Dock gibt. @L@PF: Ich möchte gerne einige Nahrungsmittel importieren. Ich habe eine Handelsroute eröffnet und den Aufseher des Handels angewiesen, aber es kommen keine Nahrungsmittel in der Stadt an.  @L@PA: Achten Sie darauf, dass Ihre Warenlager angewiesen sind, die Nahrungsmittel anzunehmen, die Sie importieren wollen. Denken Sie daran: Laut Vorgabe sind Warenlager angewiesen, keine Nahrungsmittel anzunehmen. @L@PF: Ich habe es meinem @24Aufseher&des&Handels überlassen, über die Menge der in den Warenlagern gespeicherten Güter zu entscheiden. Wie kann ich sichergehen, dass er die richtigen Entscheidungen trifft? @PA: Wenn Sie Ihren Aufseher des Handels anweisen, den Handel zu organisieren, dann analysiert der Aufseher die Bevölkerungsdichte der Stadt, die Zahl und Art der Gewerbestätten, und er prüft, welche Monumente gerade errichtet werden. Aufgrund dieser Analyse kommt er zu einer Einschätzung, welche Waren Ihre Stadt benötigt. Wenn Sie seine Vorschläge sehen möchten, klicken Sie seine Buttons für die Warensteuerung an. Wenn der Button für die Einstellung des Sollwerts erscheint, entspricht der als Vorgabe angezeigte Wert der Empfehlung des Aufsehers des Handels. @L@LWohnungen @PF: Die Wohngebiete, die ich ausweise, verschwinden immer wieder. Was ist da los? @PA: Alle Wohngebiete dürfen höchstens zwei Felder von einer Straße entfernt ausgewiesen werden. Außerdem müssen Einwanderer in der Lage sein, die Wohngebiete zu erreichen. Vergewissern Sie sich, dass es einen ungehinderten Weg zwischen den Punkten, wo Ein- und Auswanderer die Stadt betreten oder verlassen (die @57Königreichstraße), und Ihren Wohnvierteln gibt."
        }
    }

    message_table_of_contents {
        id: 10
        pos [0, 24]
        size [30, 28]
        image { id: 47, pos [15, 15] }
        title { text: "Inhalt" }
        subtitle { text: "Klicken Sie auf ein Thema, um einen Hilfetext dazu aufzurufen." }
        content {
            text: " @9Häufig&gestellte&Fragen @L@LHilfethemen @L@L@492Abu&Simbel @L@88Akademie @L@65Apotheke @L@40Arbeiter @L@8Arbeiterlager @L@43Arbeitslosigkeit @L@64Arztpraxis @L@81Architektenbüro @L@56Attraktivität @L@14Aufsehermenü @L@20Aufseher&der&Arbeitskraft @L@30Aufseher&der&Finanzen @L@26Aufseher&der&Gesundheit @L@24Aufseher&des&Handels @L@21Aufseher&des&Militärs @L@373Aufseher&der&Monumente @L@22Aufseher&der&Politik @L@25Aufseher&der&Silos @L@29Aufseher&der&Tempel @L@28Aufseher&der&Unterhaltung @L@23Aufseher&der&Wertungen @L@27Aufseher&des&Wissens @L@75Ausbildungsstätte @L@75Ausbildungsstätten&(Künstler) @L@L@2Basar @L@363Baugilden @L@2Besondere&Befehle&für&den&Basar @L@3Besondere&Befehle&für&das&Silo @L@4Besondere&Befehle&für&das&Warenlager @L@16Bevölkerungsanzeige @L@39Bevölkerungswachstum @L@59Bewässerung @L@70Bibliothek @L@488Bibliothek&von&Alexandria @L@50Bildung @L@96Brauerei @L@58Brücke @L@71Bühne @L@L@490Caesareum @L@L@11Dateimenü @L@17Datumsanzeige @L@83Dock @L@88Drillplatz @L@L@38Echte&Pyramide @L@361Edelsteinmine @L@66Einbalsamierungshaus @L@95Einfacher&Steinbruch @L@L@58Fähre @L@29Feste @L@366Festplatz @L@355Feuerwache @L@84Fischerhafen @L@91Flachsfarm @L@470Farbmühle @L@37Fort @L@42Fußgänger @L@L@79Gärten @L@33Gebäude-Buttons @L@48Geld @L@15Geldanzeige @L@76Gericht @L@91Gerstenfarm @L@53Gesundheit&in&der&Stadt @L@89Getreidefarm @L@46Gewerbe @L@93Goldmine @L@477Grabräuber @L@90Granatapfelfarm @L@95Granitsteinbruch @L@374Grabbeigaben @L@494Große&Plagen @L@L@47Handel @L@31Hauptaufseher @L@13Hilfemenü @L@91Hennafarm @L@94Holzfällerlager @L@L@359Jagdhof @L@99Juwelier @L@L@95Kalksteinbruch @L@90Kirchererbsenfarm @L@54Knickpyramide @L@37Kompanien @L@87Kompanie-Befehle @L@35Königreich-Wertung @L@57Königreichstraße @L@478Königliche&Grabstätten @L@52Krieg @L@356Kriegshafen @L@365Kriegsschiff @L@36Kriminalität @L@35Kultur-Wertung @L@93Kupfermine @L@L@473Lampenwerkstatt @L@45Landwirtschaft @L@489Leuchtturm&von&Pharos @L@L@85Mauer @L@371Mastaba @L@363Maurergilde @L@368Mausoleum @L@370Monumentbau @L@35Monument-Wertung @L@72Musikpavillon @L@L@34Nachrichten @L@45Nahrung @L@L@372Obelisk @L@12Optionenmenü @L@L@77Palast @L@97Papyruswerkstatt @L@73Pavillon @L@494Plagen&und&Seuchen @L@79Platz @L@86Polizeiposten @L@L@51Religion @L@360Rinderfarm @L@360Rinderfarm @L@L@90Salatfarm @L@95Sandsteinbruch @L@94Schilfsammelstelle @L@41Schreiber @L@68Schreiberschule @L@67Schrein @L@48Schulden @L@74Senet-Haus @L@3Silo @L@69Sonnentempel @L@18Spezialkarten @L@362Sphinx @L@85Stadttor @L@79Statue @L@363Steinmetzgilde @L@95Steinbruch @L@80Steuereintreiberbüro @L@19Steuerleisten-Umschaltung @L@39Stimmung&in&der&Stadt @L@57Straßen @L@358Straßensperre @L@375Stufenpyramide @L@L@7Tastatursteuerung @L@67Tempel @L@350Tempelkomplex&des&Osiris @L@351Tempelkomplex&des&Re @L@352Tempelkomplex&des&Ptah @L@353Tempelkomplex&des&Seth @L@354Tempelkomplex&der&Bastet @L@92Tongrube @L@1Töpferei @L@367Transportschiff @L@357Transporthafen @L@48Tribut @L@44Trinkwasser @L@85Turm @L@L@49Unterhaltung @L@L@369Vorarbeiter&des&Baus @L@85Verteidigungsanlagen @L@L@98Waffenschmiede @L@98Wagenbaubetrieb @L@4Warenlager @L@60Weberei @L@32Weltkarte @L@82Werft @L@35Wertungen @L@35Wohlstand-Wertung @L@56Wohnungen @L@78Wohnsitz @L@L@63Zahnarztpraxis @L@364Ziegelei @L@55Ziegelpyramide @L@62Ziehbrunnen @L@363Zimmermannsgilde @L@61Zisterne @L@L@479Zoo @L@LGeschichte @L@L@396Andere&Monumente @L@493Abu&Simbel @L@159Apotheke @L@155Arbeit @L@L@199Basar @L@380Bastet,&Isis&und&Hathor @L@167Bevölkerung @L@154Bewässerung @L@481Bibliothek&von&Alexandria @L@164Bibliothek&und&Literatur @L@194Bier @L@L@482Caesareum @L@L@161Einbalsamierung @L@388Einwanderung @L@L@181Feinde @L@393Feste @L@189Flachs @L@L@176Gärten&und&Kunstwerke @L@198Geschirr @L@168Gesellschaft @L@183Gesetz @L@185Getreide&und&Gerste @L@151Gewerbe @L@191Gold&und&Goldabbau @L@395Grabbeigaben @L@495Große&Plagen @L@L@177Handel @L@175Heim&des&Pharao @L@469Henna @L@192Holz&und&seine&Verwendungsmöglichkeiten @L@L@383Jagd @L@169Jonglierkunst @L@L@166Kinder @L@176Kunstwerke @L@472Kunsthandwerker @L@L@474Lampen @L@150Landwi&tschaft @L@398Leinen&und&Weberei @L@487Leuchtturm&von&Pharos @L@197Luxuswaren @L@L@381Malaria @L@394Mastaba @L@386Maurer @L@160Medizin @L@184Militär @L@170Musik @L@L@157Nil @L@L@397Obelisk @L@476Öl @L@187Obst&und&Gemüse @L@376Osiris,&Sobek&und&Min @L@L@195Papyrusherstellung @L@378Ptah,&Amun&und&Thot @L@384Priester @L@392Pyramiden @L@L@174Regierung&und&Bürokratie @L@399Religion @L@377Re,&Maat&und&Horus @L@186Rinderzucht&und&Fischerei @L@L@172Senet @L@379Seth,&Anubis&und&Sachmet @L@179Schiffe&und&Schiffbau @L@188Schilf @L@382Schmuck @L@387Schreiber @L@162Schreine&und&Tempel @L@163Schule&und&Bildung @L@5Silo @L@391Sphinx @L@193Steinbrüche @L@385Steinmetze @L@173Steuern&und&Geld @L@153Straßen @L@L@475Tal&der&Könige @L@171Tanz @L@190Ton @L@L@165Unterhaltung @L@L@182Verteidigungsanlagen @L@L@6Warenlager @L@196Waffen @L@152Wohnungen @L@L@158Zahnärzte @L@390Ziegel @L@156Ziehbrunnen&Zisternen @L@389Zimmerleute @L@480Zoo"
        }
    }
    
    message_file_menu {
        id: 11
        pos [0, 24]
        size [30, 28]
        title { text: "Dateimenü" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Im Menü 'Datei' können Sie ein neues Spiel starten, die aktuelle Mission erneut spielen, ein zuvor gespeichertes Spiel laden, das aktuelle Spiel speichern, ein zuvor gespeichertes Spiel löschen und 'Pharao' beenden."
        }
    }
    
    message_optons_menu {
        id: 12
        pos [0, 24]
        size [30, 28]
        title { text: "Optionenmenü" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Im Menü 'Optionen' können Sie Optik und Sound von 'Pharao' ändern. Mit der Option 'Anzeige' können Sie die Ansicht, mit der Option 'Sound' die Lautstärke von Soundeffekten, Sprachausgabe und Musik verändern. Mit der Option 'Geschwindigkeit' können Sie einstellen, wie schnell die Zeit in 'Pharao' verstreichen soll. In der Option 'Städte' können Sie wählen, welche Version der Stadtnamen Sie verwenden wollen (klassisch oder ägyptisch). Den klassischen Namen sind Sie vermutlich schon einmal irgendwo begegnet, aber die altägyptischen Namen verleihen 'Pharao' etwas mehr Authentizität. @PMit der Einstellung 'Popup-Nachrichten' können Sie festlegen, auf welche Weise Sie während des Spiels Nachrichten erhalten. Die meisten Nachrichten, die Sie erhalten, erscheinen in einem Popup-Fenster. Sobald sich ein Popup-Fenster öffnet, stoppt das Spiel, bis Sie das Fenster wieder schließen. Mit den Optionen der 'Popup-Nachrichten' können Sie dieses Feature für einige der Nachrichten ausschalten. Wählen Sie in der angezeigten Kategorienliste die Nachrichtenarten aus, die Sie nicht als Popup-Nachricht erhalten möchten, indem Sie die entsprechende Kategorie einfach anklicken. Der Name der Kategorie erscheint in Gelb, und sämtliche Nachrichten dieser Kategorie werden als Kurzmitteilung am oberen Bildschirmrand angezeigt. Sie erscheinen außerdem in Ihrer @34Nachrichtenliste. Sie müssen dann die Regierungsgeschäfte Ihrer Stadt nicht unterbrechen, um die Nachricht wegzuklicken. Wenn Sie in der Liste die Option 'Erfüllung jetzt möglich' anwählen, werden die angeforderten Waren automatisch von den Lagerhäusern der Stadt weggeschickt, sobald die Lieferung bereit ist. Weitere Informationen zum Thema 'Forderungen' erhalten Sie unter @22Aufseher&der&Politik. @PIn diesem Menü können Sie die automatische Speicherfunktion des Spiels ein- und ausschalten. Die automatische Speicherung speichert das Spiel alle sechs Monate ab, damit Sie stets auf einen Spielstand zurückgreifen können, falls Computerprobleme auftreten oder Sie vergessen, manuell zu speichern. Dabei wird stets derselbe Dateiname benutzt und die bereits bestehende Datei dieses Namens überschrieben, sodass keine Gefahr besteht, dass Ihre Festplatte von automatischen Speicherdateien überquillt. Sie können diese Funktion auch ausschalten, um die kleinen Pausen zu verhindern, die bei der automatischen Speicherung entstehen.  @PSchließlich können Sie jederzeit während des Spiels noch mit der Option 'Schwierigkeitsgrad' den Schwierigkeitsgrad ändern. Dabei sollten Sie aber daran denken, dass Ihre Missionspunktzahl mit dem gewählten Schwierigkeitsgrad zusammenhängt. Wenn Sie den Schwierigkeitsgrad mitten in einer Mission ändern, wird zur Berechnung der Punktzahl der leichteste eingestellte Level zugrunde gelegt. @PSchließlich können Sie sich noch über die Option 'Monumentbau beschleunigen' von den Göttern beim Bau einiger @370Monumente helfen lassen. Wenn Sie diese Option einschalten, wird einer der Götter Sie vielleicht segnen und beim Bau Ihres Monumentes unterstützen. Die Götter arbeiten aber nur bei bestimmten Monumenten gerne mit: bei Pyramiden und Mastabas."
        }
    }

    message_help_menu {
        id: 13
        pos [0, 24]
        size [30, 28]
        title { text: "Hilfemenü" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Im Menü 'Hilfe' finden Sie eine Liste aller Themen, über die Sie zum Spielen von 'Pharao' Bescheid wissen sollten. Im unteren Teil des Inhaltsverzeichnisses können Sie auch viele geschichtliche Einträge anwählen. @PMit 'Maushilfe' sind die kleinen Fenster gemeint, die angezeigt werden, wenn Sie Ihren Cursor auf etwas schieben. 'Voll' zeigt Maushilfetexte für fast jede Spielsituation an. 'Klein' schaltet die Maushilfe bis auf einige Ausnahmen wie z.B. die @18Spezialkarten und die Palastberichte der Stadt aus. 'Aus' schaltet die Maushilfe vollständig aus. @P'Warnungen' sind die kurzen Mitteilungen, die oben im Bildschirm angezeigt werden. Wenn Sie erst einmal wissen, wie 'Pharao' funktioniert, können Sie diese Meldungen auch ausschalten."
        }
    }
    
    message_overseers {
        id: 14,
        pos [0, 24]
        size [30, 28]
        title { text: "Aufseher" }
        subtitle {
            text: "Spielsteuerung"
        }
        content {
            text: "Benutzen Sie das Aufsehermenü, um einem bestimmten Aufseher einen Besuch abzustatten. Dieses Menü ist nützlich, wenn Sie die Steuerleiste weggeschaltet haben. Aufseher versorgen Sie jederzeit mit wichtigen Informationen über den Zustand der Stadt."
        }
    }
    
    message_game_control_money_display_window {
        id: 15,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Geldanzeige",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Hier finden Sie den aktuellen Stand Ihres Stadtvermögens. Mehr zum Thema Geldverdienen finden Sie unter @48Geld."
        }
    }
    
    message_game_control_population_display {
        id: 16,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Bevölkerungsanzeige",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Dieses Fenster zeigt Ihnen, wie viele Bürger derzeit in Ihrer Stadt leben. Folgen Sie diesem Querverweis und Sie erfahren, wie der Punkt @39Bevölkerung im Spiel funktioniert."
        }
    }
   
    message_game_control_date_display {
        id: 17,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Fenster: Datumsanzeige",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Dieses Fenster zeigt Ihnen den aktuellen Monat und das aktuelle Jahr an. Aus praktischen Gründen wird der moderne Kalender benutzt. Falls die Zeit für Ihren Geschmack zu schnell - oder zu langsam - abläuft, können Sie dies im Geschwindigkeit-Menü ändern."
        }
    }
    
    message_overlay_selector {
        id: 18,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Spezialkartenauswahl",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Mit Hilfe der Spezialkarten können Sie Ihre Stadt durch unterschiedliche Filter betrachten. Die Spezialkarten sind der Schlüssel für die Planung der Stadt und für die Verwaltung ihrer verschiedenen Dienstleistungen. @PWenn Sie eine Spezialkarte auswählen, sehen Sie nur die Gebäude und die Fußgänger, die für die gewählte Karte relevant sind. Ein Beispiel: Wenn Sie in der Unterhaltung-Liste die Option 'Jongleure' gewählt haben, sehen Sie nur die Bühnen, Jongleurschulen und Jongleure. Alle anderen Gebäude sind flach dargestellt. Gebäude, die von der gewählten Dienstleistung betroffen sind, werden durch hellbraune, gestreifte Blöcke dargestellt. @PWenn Sie eine Spezialkarte angewählt haben, zeigen Säulen den Zugang des Gebäudes zu einer bestimmten Dienstleistung an. Allgemein gilt: je höher die Säule, desto besser der Zugang. Dies gilt jedoch nicht für die Spezialkarte 'Risiken'. Je höher hier die Säule ist, desto höher ist das Risiko in puncto Schäden, Feuer, Malaria, Krankheit oder Kriminalität.  @PVon dieser Regel ausgenommen sind die Spezialkarten 'Risiken', 'Probleme', 'Attraktivität' und 'Felsen verbergen'. @PDie Spezialkarte 'Attraktivität' funktioniert anders als die übrigen Karten. Wenn die Attraktivität-Karte aktiviert wurde, verwandelt sich Ihre Stadt in ein Meer aus bunten Blöcken. Je höher und blauer diese Blöcke sind, desto attraktiver ist ein Gebiet und desto größer ist die Wahrscheinlichkeit, dass Ihre Bürger hier wohnen möchten. Unattraktive Gebiete werden durch rote Blöcke dargestellt, die im Boden zu versinken scheinen. @PAuch die Spezialkarte für Brunnen funktioniert etwas anders. In der Brunnen-Karte sehen Sie Ihre Brunnen innerhalb eines größeren blauen Blocks. Häuser, die sich in diesen blauen Blöcken befinden, haben Zugang zu Brunnenwasser. Des Weiteren sehen Sie ein blaues Raster mit weißen Linien, das weite Teile des Landes überzieht. Dieses Land liegt über Grundwasser und kann Einrichtungen, die mit Wasser zu tun haben, unterstützen. Auch wenn die Spezialkarte 'Wasser' aktiviert wurde, ist dieses Raster zu sehen. @PWenn Felswände Ihnen den Blick versperren, können Sie sie mit der Spezialkarte 'Felsen verbergen' vorübergehend ausblenden. Ist die Spezialkarte 'Felsen verbergen' angewählt, können Sie Ihre königlichen Grabstätten sehen, die Sie in den Felsen hineingebaut haben. @PDie Spezialkarte 'Probleme' unterscheidet sich ebenfalls erheblich von den anderen Spezialkarten und ist so ziemlich die nützlichste von allen. Die Problem-Karte zeigt all die Gebäude der Stadt, die nicht mit voller Effizienz funktionieren. Wenn Sie die Maus über ein solches Gebäude schieben und festhalten, erklärt Ihnen die Maushilfe, was mit dem Gebäude nicht stimmt. Außerdem sehen Sie bei jedem Gebäude Symbole, die spezielle Problematiken darstellen. Auf der Spezialkarte 'Probleme' sehen Sie des Weiteren alle Karrenschieber, die nur herumstehen und nicht arbeiten. @PDie beste Art, sich mit den verschiedenen Spezialkarten vertraut zu machen, besteht darin, mit ihnen zu experimentieren. Sobald Sie wissen, welche Informationen Sie durch die Karten erhalten, können Sie Ihre Stadt viel effektiver planen."
        }
    }

    message_control_panel_toggle {
        id: 19,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Steuerleiste ein-/ausblenden",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Mit diesem Button können Sie die Steuerleiste ein- oder ausblenden. Wenn die Steuerleiste verborgen ist, können Sie mehr von der Karte sehen, jedoch sind einige der Spielsteuerungen dann etwas umständlicher zu benutzen. Es liegt daher völlig in Ihrem eigenen Ermessen, ob Sie die Steuerleiste einblenden oder lieber verbergen möchten."
        }
    }

    message_overseer_workers {
        id: 20,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Arbeitskraft",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher der Arbeitskraft hält Sie über alles auf dem Laufenden, was mit Arbeit und Arbeitskräften zu tun hat: die Anzahl der offenen Stellen nach Arbeitsgebiet, die Anzahl der Arbeitslosen und das aktuelle Lohnniveau. Er hilft Ihnen bei Problemen, die mit Arbeitskräften zu tun haben. @PArbeiten Sie mit dem Aufseher der Arbeitskraft zusammen, um die Löhne in der Stadt festzulegen. Im Fenster des Aufsehers der Arbeitskraft sehen Sie die von Ihnen gezahlten und die in Ägypten üblichen Löhne. Sie können den Lohn, den Sie Ihren Arbeitern zahlen, mit Hilfe der Scroll-Buttons verändern. Wenn Sie Ihren Bürgern mehr zahlen als in Ägypten üblich ist, verbessert sich ihre @39Stimmung und die @39Einwanderung wird gefördert. Zahlen Sie weniger, schont das zwar die Finanzen der Stadt, drückt aber auf die Stimmung der Bevölkerung und könnte die Einwanderung bremsen.  @PSie können sich auch an den Aufseher der Arbeitskraft wenden, um die Priorität bei der Arbeitszuweisung zu ändern. Falls Sie keine spezifischen Prioritäten vorgeben, verteilt der Aufseher der Arbeitskraft die Arbeitskräfte so, wie er es für richtig hält. Normalerweise wird er erst alle Arbeitsplätze bei der Nahrungsmittelerzeugung und dann im Gewerbe besetzen. Wenn Sie eine neue Priorität an erste Stelle setzen möchten, z.B. das Militär, klicken Sie auf die Militär-Zeile. Ein Fenster mit verschiedenen Zahlen öffnet sich. Um das Militär auf die Prioritätsstufe 1 zu setzen, klicken Sie auf die Zahl 1. Vor 'Militär' erscheint ein Vorhängeschloss. Damit wird angezeigt, dass Sie diese Priorität bestimmt haben. Die nächste von Ihnen gewählte Kategorie erhält automatisch die Stufe 2. Sie können für jedes Arbeitsplatzsegment eine Priorität festlegen.  @PEine kleine Warnung: Wenn Sie eine Priorität festlegen, zieht der Aufseher der Arbeitskraft von überall her Arbeitskräfte zusammen, um dieses spezielle Arbeitsplatzsegment als Erstes zu belegen. Dadurch kann es passieren, dass einige Sektoren überhaupt keine Arbeitskräfte mehr haben. Ihre Stadt wird nicht lange überleben, wenn auch nur ein Sektor völlig ignoriert wird. @PWenn Sie mehr zum Thema Arbeit wissen möchten, klicken Sie @43hier. @L@LKlicken Sie @155hier, wenn Sie eine kurze Geschichte der Arbeitskräfte im alten Ägypten lesen möchten."
        }
    }

    message_overseer_military {
        id: 21,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher des Militärs",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher des Militärs überwacht all Ihre militärischen Einheiten, sowohl an Land als auch zur See. @PWenn Sie Ihrem Aufseher des Militärs einen Besuch abstatten, gibt Ihnen dieser einen Überblick über Anzahl und Zustand Ihrer Kompanien. Klicken Sie auf den Button unten rechts im Bildschirm, um zwischen Ihren Einheiten an Land und zur See zu wechseln. @PSie können auch den Zustand einer bestimmten Einheit überprüfen, indem Sie auf den Button 'Zur' klicken, oder eine Einheit ins Fort oder in den Hafen zurückbeordern, indem Sie auf den Button 'Zurück ...' klicken. @PGelegentlich benötigt der Pharao oder eine andere Stadt die Dienste Ihrer Truppen in einem Kampf außerhalb der Stadt. Klicken Sie in diesem Fall auf den Button 'Königreichdienst', um Truppen für den Kampf zu entsenden. Wenn Sie anderen Städten und dem Pharao helfen, kann dies Vorteile für Sie haben. Ihre Königreich-Wertung kann sich verbessern oder vielleicht wird Ihnen eine lukrativere Handelsbeziehung zu einer anderen Stadt gewährt. Wenn Sie die Dienste Ihrer Truppen jenen versagen, die darum bitten, könnte dies zu Verärgerung und Unzufriedenheit führen. @PIhr Aufseher des Militärs hält Sie darüber hinaus über allgemeine militärische Aktivitäten in und um die Stadt auf dem Laufenden. Er teilt Ihnen mit, wenn Feinde in die Nähe der Stadt kommen oder wenn jemand die Hilfe Ihrer Truppen benötigt. @L@LDie alten Ägypter bauten mächtige Land- und Seestreitkräfte auf. Klicken Sie @181hier, um mehr über die Kriegskunst zur damaligen Zeit zu erfahren."
        }
    }

    message_overseer_political {
        id: 22,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Politik",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher der Politik kümmert sich um Ihre Beziehungen zum Pharao und den Gouverneuren anderer Städte.  @PEr weiß über sämtliche Forderungen nach Waren Bescheid, sei es von anderen Städten oder vom Pharao. Er weiß stets, welche Menge einer geforderten Ware in den @4Warenlagern vorhanden ist, und informiert Sie, wenn Sie in der Lage sind, der Forderung Folge zu leisten. Sie können dann Ihren Aufseher der Politik anweisen, die Ware abzuschicken. In der Regel ist es sinnvoll, Forderungen seitens des Pharao oder anderer Städte so schnell wie möglich zu erfüllen. Wenn Sie eine Forderung völlig ignorieren, kann dies den Handel verschlechtern oder sogar einen Angriff auf Ihre Stadt bewirken. Das Geforderte spät zu schicken, ist dabei immer noch besser, als es gar nicht zu schicken. @PDer Aufseher der Politik hilft Ihnen auch, Ihre persönlichen Ersparnisse zu verwalten. Er weiß, wie viel Sie gespart haben und wie viel Sie derzeit verdienen. Wenn Sie möchten, können Sie mit Ihrem Aufseher der Politik zusammenarbeiten, um Ihr Einkommen zu verändern. Klicken Sie hierzu einfach auf den Button mit Ihrem derzeitigen Gehalt. Ein Bildschirm mit Titeln und den zugehörigen Gehaltsstufen wird eingeblendet. Wählen Sie in diesem Bildschirm eine neue Gehaltsstufe aus. Bedenken Sie dabei jedoch, dass es Ihren Landsleuten missfallen wird, wenn Sie sich mehr ausbezahlen, als Ihr Rang rechtfertigt. @PWenn Sie etwas von Ihrem Ersparten ausgeben wollen, nimmt der Aufseher der Politik die Transaktion vor. Sie können dem Pharao ein Geschenk schicken (oder dem Königreich, wenn Sie selbst Pharao sind), oder Sie können etwas in die Stadtkasse einbezahlen.  @PDem Pharao und anderen Regenten gefällt es, persönliche Geschenke zu erhalten. So können Sie möglicherweise Ihren Status erhöhen - und eine verbesserte Königreich-Wertung erhalten - indem Sie regelmäßig Geschenke schicken. Sind Ihre Ersparnisse hoch genug, haben Sie die Auswahl zwischen drei Geschenken. Seien Sie aber nicht allzu freigiebig. Wenn Sie zu häufig Geschenke schicken, erwarten die Empfänger solche Gaben mit der Zeit in regelmäßigen Abständen und können verärgert reagieren, wenn sie ausbleiben. Außerdem neigen sie dazu zu erwarten, dass jedes Geschenk wertvoller ist als das vorherige. Wenn Sie beschließen, ein Geschenk zu schicken, sorgt der Aufseher der Politik dafür, dass es gut beim Empfänger ankommt. @PSie können Ihr Erspartes auch der Stadtkasse spenden. Das kann insbesondere dann sinnvoll sein, wenn so verhindert wird, dass die Stadt sich verschuldet. Schulden können einen sehr teuer zu stehen kommen. Der Pharao oder andere Regenten sind zwar bereit, Ihrer Stadt ein Darlehen zu gewähren, aber Darlehen sind nicht umsonst. Wenn Sie mehr zum Thema Geld wissen möchten, klicken Sie @48hier. @PSchließlich ist der Aufseher der Politik auch über die Königreich-Wertung und die allgemeine Einstellung des Pharao Ihnen gegenüber informiert. Eine bessere Informationsquelle zum Thema Wertungen ist jedoch Ihr @23Aufseher der Wertungen."
        }
    }
    
    message_overseer_ratings {
        id: 23,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Wertungen",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher der Wertungen zeigt die derzeitigen Wertungen (Kultur, Wohlstand, Monument und Königreich) sowie das Bevölkerungsziel an. Wenn Sie auf eine Wertung klicken, informiert Sie der Aufseher der Wertungen über die beste Methode, diese Wertung zu verbessern bzw. über die Gründe für schlechte Wertungen. Ihren Fortschritt, was das Erreichen der Wertungsziele betrifft, zeigen Ihnen die Säulen über jeder Kategorie. Wenn Sie das Ziel erreichen, das zu Beginn einer Aufgabe gestellt wurde, wird die Säule mit einem Kapitell gekrönt. @PWenn sich in Ihrer Stadt ein @77Regierungspalast befindet, können Sie sich schnell über die Wertungen informieren, indem Sie den Mauszeiger auf den Palast setzen. Ein kleiner Bildschirm mit Ihren Wertungen sowie der Arbeitslosenquote wird angezeigt. @PWenn Sie mehr zum Thema Wertungen und deren Rolle im Spiel wissen möchten, klicken Sie @35hier."
        }
    }

    message_overseer_commerce {
        id: 24,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher des Handels",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher des Handels ist ein äußerst beschäftigter Mensch. Er informiert Sie nicht nur darüber, mit welchen Städten Sie @47Handel treiben können, sondern weiß auch über den Gesamtinhalt Ihrer @4Warenlager und den Status all Ihrer Gewerbezweige Bescheid. @PWenn Sie Ihrem Aufseher des Handels einen Besuch abstatten, wird eine Liste sämtlicher Güter angezeigt, die Ihre Stadt herstellen oder importieren kann. Indem Sie auf eine dieser Waren klicken, erhalten Sie eine Zusammenfassung über den Status des betreffenden Gewerbezweiges. Hier sehen Sie, wie viele Gebäude für die Herstellung dieser Ware existieren und in wie vielen dieser Gebäude tatsächlich gearbeitet wird.  @PIn diesem Fenster können Sie auch spezielle Anweisungen für diese Ware ausgeben. Wenn Sie für die Ware eine offene Handelsroute haben (mehr dazu später) können Sie Ihren Aufseher des Handels anweisen, mit dem Import bzw. Export der Ware zu beginnen. Wenn Sie die Ware exportieren, müssen Sie dem Aufseher des Handels darüber hinaus mitteilen, welche Menge dieser Ware er in den Warenlagern vorrätig halten soll. Das ist besonders wichtig, wenn Sie Dinge wie z.B. Töpferwaren exportieren. Die Nachfrage Ihrer Bürger nach Geschirr ist i.d.R. recht hoch, daher sollten Sie darauf achten, genügend davon auf Lager zu halten. @PSie können einen Gewerbezweig auch komplett ausschalten. Wenn Sie aufhören wollen, eine Ware zu produzieren, legen Sie das Gewerbe einfach still. Dabei werden allerdings nur die Aktivitäten eingestellt, die Gebäude, in denen das Endprodukt hergestellt wird, bleiben erhalten. Gebäude, die Rohstoffe für das Endprodukt erzeugen, sind davon nicht betroffen. In stillgelegten Gebäuden werden keine Arbeitskräfte mehr beschäftigt. Auf diese Art können Sie auch zusätzliche Arbeiter freisetzen, wenn ein Mangel an Arbeitskräften auftritt. Den stillgelegten Wirtschaftszweig können Sie im Übrigen jederzeit wieder aktivieren. @PMit dem letzten Button in diesem Fenster können Sie die Ressource hamstern. Während Sie eine Ressource hamstern, können Sie damit weder handeln noch erhalten Ihre Bürger Zugang zu dieser Ware. Hamstern kann besonders nützlich sein, wenn Sie schnell einer Forderung nach Waren nachkommen wollen. Indem Sie erneut auf den Button klicken, können Sie die Ressource wieder auf normale Weise verwenden und damit handeln. Falls Sie mit dieser Ressource gehandelt hatten, bevor Sie die Hamsteraktion starteten, müssen Sie Ihrem Aufseher des Handels jetzt mitteilen, dass er den Handel mit dieser Ressource wieder aufnehmen soll. @PAuf die @32Königreichkarte können Sie auch vom Aufseher des Handels-Fenster aus zugreifen. Auf der Karte des Königreichs sehen Sie die weiteren Städte in Ihrer Gegend. Indem Sie auf eine Stadt klicken, erfahren Sie, ob diese bereit ist, mit Ihnen Handel zu treiben oder nicht. Wenn die Stadt bereit ist, mit Ihnen zu handeln, werden unten im Bildschirm die Waren aufgelistet, die sie kaufen oder verkaufen will. Bronzekugeln in der Ecke des Warensymbols zeigen an, welche Menge einer bestimmten Ware die Stadt im kommenden Jahr verkaufen bzw. kaufen wird - ein Punkt steht für bis zu 15 Wagenladungen, zwei für bis zu 25, drei für bis zu 40. @PDie Kosten für die Eröffnung der Handelsroute werden ebenfalls aufgelistet. Klicken Sie auf diesen Button, dann gibt die Stadtkasse die für das Öffnen der Handelsroute erforderlichen Mittel frei. Ist die Route erst einmal geöffnet, kehren Sie zum Aufseher des Handels zurück, um ihm mitzuteilen, welche Waren importiert bzw. exportiert werden sollen. @PDer Aufseher des Handels ist auch über die gängigen Marktpreise informiert. Wenn Sie auf den Button 'Preise anzeigen' klicken, werden sämtliche Waren im Königreich angezeigt. Sie werden feststellen, dass die Verkäufer weniger erhalten als die Käufer zahlen. Die Differenz wird zur Deckung der Unkosten für die Karawanen und Handelsschiffe benötigt, die lange, schwierige Reisen im Interesse des freien Handels auf sich nehmen. @PÜber die Einträge @46Gewerbe, @45Nahrungsmittel und @47Handel lernen Sie, die Nuancen des erfolgreichen Handels besser zu verstehen."
        }
    }
    
    message_overseer_granaries {
        id: 25,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Silos",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Das Nahrungsmittelangebot und die Bevölkerungsentwicklung sind eng miteinander verknüpft. Der Aufseher der Silos verfolgt die Bevölkerungsentwicklung und deren Ernährung. @PDieser Aufseher unterbreitet Ihnen in drei verschiedenen Diagrammen Informationen über die Bevölkerung Ihrer Stadt. Standardmäßig wird zunächst das Diagramm zur bisherigen Bevölkerungsgeschichte angezeigt. In diesem Diagramm ist zu sehen, wie sich die Bevölkerungszahlen im Laufe der Zeit entwickelt haben. Auf der rechten Seite des Diagramms zur Bevölkerungsgeschichte befinden sich zwei kleinere Diagramme: Zensus und Gesellschaft. Klicken Sie auf eines dieser Diagramme, um es zu vergrößern und auf dem Bildschirm zu zentrieren.  @PDas Zensus-Diagramm zeigt die demographische Struktur Ihrer Bevölkerung nach Alter - sehr nützlich, wenn man das Wachstum oder das Schrumpfen der arbeitenden Bevölkerung berechnen will, denn Kinder und ältere Leute arbeiten zwar nicht, verbrauchen aber weiterhin Nahrungsmittel und zerbrechen Geschirr!  @PDas Gesellschaftsdiagramm zeigt die genaue Struktur der Bevölkerung nach Einkommen, und zwar aufgeteilt nach Behausung. Extrem reiche Einwohner (Schreiber) verrichten ebenfalls keine körperliche Arbeit, so dass die Anzahl der Arbeitskräfte häufig sinkt, je reicher die Stadt wird. Aber obwohl sie keine körperliche Arbeit verrichten, bezahlen Schreiber eine Menge Steuern. @PUnter den Diagrammen finden Sie mehrere Zeilen mit sehr nützlichen Informationen. In der ersten Zeile erfahren Sie, wie viele Personen Sie mit der derzeitigen Nahrungsmittelproduktion ernähren können und welche Auswirkungen dies voraussichtlich auf die Bevölkerungszahlen haben wird. Der Aufseher der Silos informiert Sie auch über die Anzahl der Silos in der Stadt und für wie viele Monate dort Nahrungsmittel lagern. Darüber hinaus teilt er Ihnen mit, wie viele verschiedene Arten an Nahrungsmitteln Ihre Bürger konsumieren. Er weiß, ob Ihre Stadt Zu- oder Abwanderung erlebt und wie viele Neubürger im vergangenen Monat angekommen sind. @PDie Einträge zum Thema @39Bevölkerung und @45Nahrung können helfen, die Bedeutung des Aufseher der Siloss zu verstehen."
        }
    }
    
    message_overseer_public_health {
        id: 26,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Gesundheit",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Ihr Aufseher der Gesundheit informiert Sie über die Anzahl an Arztpraxen, Zahnarztpraxen und Einbalsamierungshäusern, die in der Stadt aktiv sind. Von jedem dieser Dienstleistungsbetriebe weiß der Aufseher der Gesundheit, wie vielen Personen er dient, und gibt eine allgemeine Bewertung der Versorgung ab. Er informiert Sie darüber hinaus auch über die Anzahl an Apotheken in Ihrer Stadt. Weitere Informationen über den Stand der Versorgung in bestimmten Stadtgebieten erhalten Sie, indem Sie die @18Spezialkarte&Gesundheit benutzen. @PIhr Aufseher der Gesundheit weiß, ob ein bestimmtes Gesundheitsrisiko in der Stadt herrscht (z.B. Malaria oder Seuchen). Da eine ausgewogene Ernährung von so überragender Bedeutung für die Gesundheit ist, informiert er Sie auch über die Anzahl unterschiedlicher Nahrungsmittel, die Ihre Bürger verzehren. Darüber hinaus verfolgt er die allgemeine Einstellung der Bevölkerung gegenüber der medizinischen Versorgung.  @PDer Eintrag zur @53Gesundheit kann Ihnen helfen, die Auswirkungen des Gesundheitszustandes in der Stadt zu verstehen."
        }
    }
    
    message_overseer_learning {
        id: 27,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher des Wissens",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Der Aufseher des Wissens informiert Sie darüber, wie viele Schreiberschulen und Bibliotheken der Bevölkerung Ihrer Stadt zur Verfügung stehen. Er teilt Ihnen mit, wie viele Menschen Zugang zu den Einrichtungen haben und ob sämtliche Stadtteile hinreichend damit versorgt sind. Um die Anzahl der Einrichtungen in bestimmten Stadtgebieten zu betrachten, verwenden Sie die @18Spezialkarte&Bildung. @PDer Aufseher des Wissens informiert Sie darüber hinaus, welche Anforderungen Ihre Bürger in puncto Bildung stellen. Mehr zu diesem Thema erfahren Sie unter @50Bildung."
        }
    }

    message_overseer_diversions {
        id: 28,
        pos [0, 24]
        size [30, 28]
        title { text: "Aufseher der Unterhaltung" }
        subtitle { text: "Spielsteuerung"  }
        content {
            text: "Der Aufseher der Unterhaltung weiß, wie viele Jongleur-, Musik- und Tanzbühnen in der Stadt aktiv sind. Die Anzahl der vorhandenen Unterhaltungsplätze ist dabei viel wichtiger als die Zahl der einzelnen @71Bühnen, @72Musikpavillons und @73Pavillons, daher führt er diese auch nicht einzeln auf. Außerdem informiert er Sie über die Anzahl der @74Senet-Häuser und @479Zoos, die der Bevölkerung Unterhaltung bieten. Er kann einschätzen, wie viele Menschen von den Unterhaltungsplätzen, Zoos und Senet-Häusern der Stadt profitieren, und beurteilt die Zufriedenheit der Bürger mit den Unterhaltungsmöglichkeiten, die ihnen zur Verfügung stehen.  @PMehr über die Rolle der Unterhaltung für die Stadt erfahren Sie unter @49Unterhaltung. @L@LKlicken Sie @165hier, um mehr über Unterhaltung im alten Ägypten zu erfahren."
        }
    }

    message_overseer_temples {
        id: 29,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Aufseher der Tempel",
        }
        subtitle {
            text: "Spielsteuerung",
        }
        content {
            text: "Das Zufriedenstellen sämtlicher Götter kann sich als große Herausforderung erweisen. Ihr Aufseher der Tempel hilft Ihnen, die Götter bei Laune zu halten. @PEin Besuch beim Aufseher der Tempel zeigt Ihnen alle Götter, die Einfluss auf Ihre Stadt haben. Der Aufseher teilt Ihnen mit, welcher Gott die Schutzgottheit Ihrer Stadt ist und daher besondere Aufmerksamkeit verdient. Neben dem Namen eines jeden Gottes finden Sie eine Liste der kleinen und großen Tempel, die dieser Gottheit in der Stadt geweiht sind. Darüber hinaus informiert er Sie über die Anzahl an Schreinen für diesen Gott und darüber, vor wie vielen Monaten Sie zuletzt ein Fest zu Ehren dieser Gottheit veranstaltet haben. Schließlich informiert er Sie noch über die Stimmung der einzelnen Gottheiten. @PWenn Sie ein Fest in der Stadt veranstalten wollen, hilft Ihnen der Aufseher der Tempel bei der Planung. Klicken Sie hierzu auf den Button 'Neues Fest abhalten'. Bestimmen Sie, zu Ehren welcher Gottheit ein Fest welcher Größe veranstaltet werden soll. Denken Sie daran, dass Sie einen Festpavillon in der Stadt haben müssen, bevor Sie ein großes oder ein gewaltiges Fest veranstalten können. Für gewaltige Feste benötigen Sie darüber hinaus einen Vorrat an Bier. @PDer Aufseher der Tempel informiert Sie des Weiteren über die genauen Bedürfnisse Ihrer Bürger hinsichtlich der Religionsausübung in Ihrer Stadt. @PUnter @51Religion und @35Wertungen erhalten Sie weitere Informationen darüber, wie die Götter besänftigt werden."
        }
    }

    message_overseer_treasury {
        id: 30,
        pos [0, 24]
        size [30, 28]
        title { text: "Aufseher der Finanzen" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Ihr Aufseher der Finanzen verfügt über genaueste Aufzeichnungen über jeden Deben, der in die oder aus der Stadtkasse fließt. Anhand seiner Berechnungen können Sie herausfinden, wo Sie Kosten senken oder Einkünfte erhöhen können. @PEine Zusammenfassung von Informationen zum Thema Steuer finden Sie oben im Aufseher der Finanzen-Bildschirm. Den Steuersatz können Sie mit den Scroll-Buttons ändern. Die Standardeinstellung, die Ihre Bürger für vertretbar halten, liegt bei 7 Prozent. Wenn Sie den Steuersatz deutlich über 7 Prozent anheben, wird dies Ihre Bürger verärgern und Einwanderer abschrecken. Je länger die Steuern hoch bleiben, desto erboster wird die Bevölkerung. Wenn Sie mehr über die Stimmung in der Bevölkerung wissen möchten, klicken Sie @39hier. @PIm Überblick erfahren Sie auch, wie viele Steuern eingetrieben wurden, wie viele Ihrer Bürger steuerlich registriert sind und wie viel Geld auf Grund einer unzureichenden Anzahl an Steuereintreibern nicht eingetrieben wurde. Um festzustellen, welche Stadtgebiete ihre Steuern nicht entrichten, benutzen Sie die @18Spezialkarte&Steuern. @PDer Zusammenfassung folgend finden Sie ein Abrechnungsblatt. Die oberen Zeilen enthalten Informationen über Ihre Einkünfte aus Steuern, Geschenken und dem Export von Waren.  @PUnter der mageren Liste der Einnahmequellen befindet sich die weitaus längere Liste Ihrer Ausgaben. In der Regel stellen Löhne und Baukosten die größten Posten dar, allerdings kann auch der Import recht teuer werden. @PAuf der linken Seite der Liste sehen Sie zum Vergleich die Ergebnisse des vergangenen Jahres. So erkennen Sie schnell, ob ein bestimmtes Ausgabengebiet im Vergleich zum vergangenen Jahr völlig außer Kontrolle zu geraten droht. @PMehr zum Thema Budgetplanung erfahren Sie unter @48Geld. Der Eintrag über @80Steuereintreiber ist ebenfalls hilfreich."
        }
    }

    message_chief_overseer {
        id: 31,
        pos [0, 24]
        size [30, 28]
        title { text: "Hauptaufseher" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Der Hauptaufseher berät sich mit allen anderen Aufsehern und gibt Ihnen eine allgemeine Übersicht über die aktuelle Lage in der Stadt. Es ist sinnvoll, ihm einen Besuch abzustatten, wenn Sie sich nicht ganz sicher sind, was Ihre Stadt am dringendsten benötigt. Wichtiges, auf das Sie sich sofort konzentrieren sollten, ist gelb dargestellt. Ernsthafte Probleme werden weiß angezeigt. Klicken Sie auf ein Problem, um Ratschläge und Hinweise auf andere Aufseher zu bekommen, die Ihnen vielleicht weiterhelfen können. @PIhr Hauptaufseher liefert Ihnen außerdem die aktuellsten Nilometer-Werte. Der Nilometer bietet eine Vorhersage zur Überschwemmung in der kommenden Saison. @PDenken Sie immer genau über die Dinge nach, die Ihr Hauptaufseher zu sagen hat. Wenn Sie rechtzeitig auf seine Warnungen hören, kann dies Ihre Stadt vor Katastrophen bewahren."
        }
    }

    message_world_map {
        id: 32,
        pos [0, 24]
        size [30, 28]
        title { text: "Die Königreichkarte" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Die Karte des Königreichs zeigt Ihnen, wo andere wichtige Städte in der Region liegen. Eine ihrer wichtigsten Funktionen ist wohl das Aufzeigen möglicher @47Handelspartner. @PKlicken Sie auf den Namen einer Stadt, um festzustellen, ob diese bereit wäre, mit Ihnen Handel zu treiben. Wenn die Stadt Handel treiben will, finden Sie unter dem Stadtnamen eine Liste der Produkte, die die Stadt kauft und verkauft, sowie die Kosten für die Eröffnung einer Handelsroute. Klicken Sie auf den Button 'Handelsroute öffnen', um Handelsbeziehungen aufzunehmen. @PHäufig erhalten Sie von anderen Städten Forderungen nach Waren oder Nachrichten über Kämpfe an anderen Orten. Die Königreichkarte hilft Ihnen, festzustellen, wo sich diese Städte befinden. Wird zum Beispiel eine Stadt in der Nähe angegriffen, sollten Sie auf der Hut sein. Schließlich könnte Ihre Stadt ebenfalls angegriffen werden. @PMehr über die Verwendung der Königreichkarte finden Sie unter den Themen @47Handel, @52Krieg&und&Frieden und @24Aufseher des Handels."
        }
    }

    message_building_buttons {
        id: 33,
        pos [0, 24]
        size [30, 28]
        title { text: "Gebäude-Buttons" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Mit diesen Buttons können Sie Gebäude auf der Karte platzieren. Außerdem sehen Sie auf den Buttons die Baukosten des jeweiligen Gebäudes. Wenn Sie ein Gebäude ausgewählt haben, das erstellt werden soll, erscheint der Mauszeiger als grüne, schemenhafte Darstellung dieses Gebäudes. Solange Sie den Zeiger über bebaubares Land führen, ist die Abbildung grün; auf nicht bebaubarem Land verwandelt sich der Mauszeiger in eine rote Raute. @L@LDie Hilfe zu den einzelnen Gebäuden können Sie aufrufen, indem Sie mit der rechten Maustaste auf bereits bestehende Gebäude dieser Art klicken oder sie im @10Inhaltsverzeichnis unter der Rubrik 'Gebäude' anwählen."
        }
    }
    
    message_game_control_messages {
        id: 34,
        pos [0, 24]
        size [30, 28]
        title { text: "Nachrichten von Ihren Schreibern" }
        subtitle { text: "Spielsteuerung" }
        content {
            text: "Ereignet sich etwas Wichtiges, schickt Ihnen einer Ihrer vielen Schreiber eine Nachricht mit Einzelheiten darüber. Diese Nachrichten erfordern meist besondere Aufmerksamkeit von Ihrer Seite - sie zu ignorieren, könnte sich als sehr gefährlich erweisen. @PWenn Sie eine neue Nachricht erhalten, ist ein Klingelton zu hören. Ist die Nachricht besonders wichtig, wird sie automatisch angezeigt, allerdings versuchen Ihre Schreiber, Sie möglichst selten auf diese Weise zu belästigen. Ist das Ereignis von nicht ganz so großer Dringlichkeit, wird die Nachricht dann einfach in Ihre Nachrichtenliste gestellt. Ihre Nachrichten können Sie lesen, indem Sie unten in der Steuerleiste auf den Button mit dem Schreiber klicken. Die Zahl auf dem Button zeigt an, wie viele Nachrichten Sie haben. Wenn Sie auf diesen Button klicken, wird eine Liste mit all Ihren Nachrichten angezeigt. Die erste Nachricht in der Liste ist stets die zuletzt erhaltene. @PNachrichten können Sie löschen, sobald Sie sie gelesen haben, indem Sie in der Nachrichtenliste auf den Nachrichtentitel klicken. Natürlich können Sie sich auch dafür entscheiden, die Nachricht zu Informationszwecken aufzubewahren. @PFortgeschrittene Spieler werden vielleicht einige der Popup-Nachrichten mit Hilfe des @12Optionenmenüs lieber ausschalten. Wenn Sie diese Option aktivieren, erscheinen die Nachrichten am oberen Bildschirmrand und werden auch in Ihrem 'Posteingang' abgelegt."
        }
    }

    message_ratings {
        id: 35,
        pos [0, 24]
        size [30, 28]
        title { text: "Wertungen" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Wertungen zeigen an, wie gut Sie Ihre Arbeit als Herrscher verrichten. Zu Beginn jeder Aufgabe wird ein Wertungsziel vorgegeben. Befördert werden Sie erst, wenn Sie diese Ziele erreicht haben. Ihr Erfolg misst sich an vier verschiedenen Wertungen: Kultur, Wohlstand, Königreich und Monument. @L@LKULTUR @PDie Kultur-Wertung zeigt an, wie gut der Zugang Ihrer Bürger zu @49Unterhaltung, @50Bildung, @53Gesundheit und @51Religion ist. In diese Wertung fließt nicht nur die Anzahl der vorhandenen Einrichtungen, sondern auch die Vielfalt der angebotenen Möglichkeiten ein. Um hohe Kultur-Wertungen zu erzielen, müssen Sie für Ihre Bürger ein breites Angebot bereithalten: Die Bürger müssen jederzeit Zugang zu mehreren Unterhaltungsarten, medizinischen Einrichtungen (außer Apotheken - diese haben keine Auswirkungen auf die Kultur-Wertung), Bibliotheken und Schreiberschulen sowie zu Tempeln verschiedener Gottheiten haben. Der Schlüssel zum Erzielen einer guten Kultur-Wertung besteht darin, mehr von diesen Einrichtungen zu bieten, als Ihre Bürger fordern. @PFür eine optimale Kultur-Wertung sollten Sie vielleicht einen @479Zoo bauen. Sie benötigen einen Zoo, wenn Sie eine Kultur-Wertung von mehr als 75 erreichen möchten. Klicken Sie auf den Button für Unterhaltungseinrichtungen, um zu sehen, ob ein Zoo zur Verfügung steht. @L@LWOHLSTAND @PIhre Wohlstand-Wertung zeigt den Gesamtwohlstand der Stadt an. In der Wohlstand-Wertung werden die Rentabilität der Stadt, der Wohlstand der Bürger sowie die soziale Struktur der Stadt berücksichtigt. Macht Ihre Stadt jedes Jahr Gewinn, müsste die Wohlstand-Wertung stetig steigen, wenn keine anderen Faktoren dem im Wege stehen. Solche negativen Faktoren sind hohe Arbeitslosigkeit, schlechte Wohnungen, niedrige Löhne und mangelnde Vielfalt an Nahrungsmitteln. Wenn Sie dem Pharao keinen Tribut zahlen (außer wenn Sie selbst bereits Pharao sind), verschlechtert dies ebenfalls die Wohlstand-Wertung. Ist in Ihrer Stadt ein großer Tempel oder ein großes Senet-Haus in Betrieb, steigert dies die Wohlstand-Wertung, weil die Bürger den Eindruck haben, in einer wohlhabenden Stadt zu leben. Auch die Fertigstellung eines Monumentes fördert diese Wertung. Ist eine Stadt am Jahresende im Minus oder verliert sie Geld, leidet die Wohlstand-Wertung natürlich. Wenn Sie jedoch wegen Bautätigkeiten Geld verloren haben, beeinflusst dies die Wohlstand-Wertung nicht, da solche Investitionen das Stadtbild verbessern.  @L@LKÖNIGREICH @PDie Königreich-Wertung zeigt an, welchen Status Sie in den Augen des Pharao und anderer Städte im Königreich haben. Schnelles Reagieren auf Forderungen und das Zahlen von Tribut an den Pharao verbessern diese Wertung. Wenn Sie Forderungen dagegen nicht nachkommen oder eine Tributzahlung verpassen, schadet dies Ihrer Königreich-Wertung. Positiv wirken sich auch Friedenszeiten in der Stadt und erfolgreiche Verteidigung gegen Angreifer aus. Sinkt diese Wertung zu stark ab, könnte Ihr schlechter Ruf einen Angriff durch den Pharao oder eine benachbarte Stadt bewirken. Die Wertung fällt dramatisch, wenn Sie ein entferntes Gefecht verlieren oder ignorieren, Forderungen nach Waren oder anderen Dingen aus dem restlichen Reich nicht erfüllen und über längere Zeit Ihre @48Schulden nicht begleichen. @PIhre Königreich-Wertung fällt auch, wenn @477Grabräuber @Grabbeigaben aus einem unter Ihrer Aufsicht stehenden Grab stehlen. Die Bewohner Ägyptens könnten dann auf die Idee kommen, dass Sie den Toten nicht den nötigen Respekt zollen. @PDie Verhaftung eines Grabräubers wird von Ihren Mitbürgern begrüßt, daher steigt Ihre Königreich-Wertung mit jedem Grabräuber, den Ihre Polizisten festnehmen, etwas an. @L@LMONUMENT @PDie Monument-Wertung zeigt, wie groß Ihre Fortschritte bei der Fertigstellung Ihrer Monumente sind. Das Beliefern der Monumente mit @374Grabbeigaben ist Bestandteil der Fertigstellung und spiegelt sich ebenfalls in der Monument-Wertung wider. @L@LEin Besuch bei Ihrem @23Aufseher der Wertungen informiert Sie über Ihren derzeitigen Rang. Wenn Sie auf einen Wertungstyp klicken, gibt Ihnen der zuständige Aufseher der Wertungen Ratschläge, wie Sie diese Wertung verbessern können."
        }
    }

    message_city_crime {
        id: 36
        pos [0, 24]
        size [30, 28]
        title { text: "Kriminalität" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "In der Stadt entsteht eine schlechte Stimmung, wenn die grundlegenden Bedürfnisse der Bürger nicht erfüllt werden. Zu schlechter Stimmung tragen niedrige Löhne, hohe Steuern sowie ein Mangel an Nahrungsmitteln und Arbeitsplätzen bei. Soziale Ungleichheiten verschlechtern ebenfalls die Stimmung. Die Einwohner werden unzufrieden, wenn sie Steuern zahlen und andere nicht, oder wenn ihnen Dienstleistungen verwehrt werden, zu denen andere Stadtbewohner Zugang haben. @PWenn die Wut der Bürger ein bestimmtes Maß erreicht, rutschen sie in die Kriminalität ab. Ihr Ziel ist es, Geld zu stehlen - aus der Stadtkasse oder aus den Ersparnissen Ihrer Familie. Um festzustellen, aus welchen Häusern am ehesten Diebe kommen werden, verwenden Sie die Spezialkarte 'Risiken: Kriminalität'. In dieser Karte sind statt Häusern Säulen zu sehen - je höher die Säule, desto wahrscheinlicher ist es, dass aus diesem Haus ein Verbrecher kommt. @PIst ein Verbrecher erst einmal auf der Straße, können auch Magistrate ihn nicht mehr aufhalten. Polizisten können Verbrecher dagegen abfangen, bevor sie zuschlagen. Trifft ein Polizist auf der Straße einen Verbrecher, wird das Verbrechen verhindert. Allerdings ist die beste Methode der Verbrechensbekämpfung immer noch, die Stimmung in der Stadt zu fördern. @PKriminalität kann auch @477Grabräuber hervorbringen. Diese Räuber treten allerdings nur dann in Erscheinung, wenn sich in Ihrer Stadt die letzte Ruhestätte eines großen Pharaos befindet und ein Grab (Pyramide, Mastaba, Mausoleum oder königliche Grabstätte) vorhanden ist. Grabräuber sind wahre Meister darin, in königliche Grabstätten einzudringen und die darin verborgenen Schätze zu plündern. @PManchmal kann Habgier sogar die zufriedensten Bürger verführen. Diese Bürger und ihre Freunde spekulieren begehrlich auf die üppigen Grabbeigaben, die mit dem edlen Verblichenen begraben wurden. Wenn diese Gier nach Reichtum unbezähmbar wird, bricht eine Welle des Verbrechens über die Stadt herein, und die Bürger werden zu Grabräubern! Da Sie nicht in die Herzen Ihrer Bürger blicken können, können Sie auch nicht wissen, wann eine solche Welle sich Bahn brechen wird. Ihre Polizisten werden jedoch eifrig danach trachten, jeden zu ergreifen, der versucht, eine Grabstätte ihres wertvollen Inhaltes zu berauben."
        }
    }

    message_fort_and_company {
        id: 37,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Kompanien und Forts",
        }
        content {
            text: "Jeder Soldat wird einer Kompanie zugeteilt, und jede Kompanie besitzt ein eigenes Fort. Es gibt verschiedene Kompanien und Forts: @L@LInfanterie @LInfanteristen sind die Stütze der meisten Armeen. Sie sind Nahkampfspezialisten und kämpfen an vorderster Front. Infanteristen bewegen sich mit mittlerer Geschwindigkeit fort. Auf dem Drillplatz werden sie mit Speeren ausgestattet. @L@LBogenschützen @LMit Pfeilen haben Bogenschützen eine größere Reichweite als Infanteristen, sie sind aber im Nahkampf ziemlich schlecht und halten nicht lange durch, wenn sie direkt angegriffen werden. Sie marschieren etwas langsamer als Infanteristen. Bogenschützen stellen ihre eigenen Bogen und Pfeile her. @L@LWagenlenker @LEs gibt nichts Furcht erregenderes für Soldaten, als eine geschlossene Formation Streitwagen, die auf sie zurollt. Streitwagen haben eine Schlüsselfunktion beim Durchbrechen der Schutzformationen Ihrer Feinde. Sobald die Linien durchbrochen sind, haben Sie die Oberhand. Auf dem Drillplatz werden Wagenlenker mit Wagen ausgestattet. @L@LSoldaten ziehen es vor, in ihren Forts zu bleiben, wenn sie gerade nicht kämpfen. Dort bleiben sie auch, solange Sie ihnen nicht den Befehl erteilen, ins Feld zu ziehen. In den Forts genießen die Soldaten die Gesellschaft ihrer Kameraden. Eine längere Zeit auf dem Schlachtfeld senkt die Moral der Truppe. Weitere Informationen zum Thema 'Truppenmoral' finden Sie im entsprechenden Kapitel. @PForts benötigen weder Straßenanbindung noch Arbeitskräfte. Sie haben äußerst negative Auswirkungen auf die Attraktivität, daher ist es besser, Forts möglichst weit vom Stadtzentrum entfernt zu platzieren. @P@87Kompanie-Befehle @P@52Krieg @L@L@184Militär"
        }
    }
    
    message_true_pyramid {
        id: 38,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Echte Pyramide",
        }
        content {
            text: "Eine echte Pyramide hat einen Kern aus @95einfachem&Stein mit einer geglätteten, polierten @95Kalksteinverkleidung. Steinmetze aus der @363Steinmetzgilde bearbeiten den Stein und polieren die Oberfläche. Unterdessen bereiten Zimmerleute aus der @363Zimmermannsgilde die Rampen vor, die für den Bau benötigt werden, während die Pyramide immer höher und höher hinaufragt. Hat ein Warenlager vier Steinblöcke angesammelt, ziehen Bauern einen Schlitten mit Stein zur Baustelle, wo die Steinmetze bereits warten. @PEchte Pyramiden gibt es als kleine, mittlere und große Pyramiden, Pyramidenkomplexe und große Pyramidenkomplexe. @P@370Monumentbau @P@373Aufseher&der&Monumente @P@369Vorarbeiter&des&Baus @L@LWenn Sie mehr über die Geschichte der echten Pyramide wissen wollen, klicken Sie @392hier."
        }
    }

    message_population_groth_and_sentiment {
        id: 39,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Stimmung in der Stadt",
            pos [15, 5]
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Wenn die Stadt neu erbaut wird, strömen abenteuerlustige Einwanderer herbei, um sich hier eine neue Existenz aufzubauen. Wenn mit der Zeit neue Zuwanderer angelockt werden, dann geschieht das vor allem durch Mundpropaganda. Die angenehmen Lebensbedingungen und die gute Stimmung in der Stadt werden von ihren Bewohnern im ganzen Königreich gepriesen. Dann braucht man auf neue Zuwanderer nicht lange zu warten - vorausgesetzt, man bietet ihnen Platz. @PDie in der Stadt herrschende Stimmung ist ein Indikator der dort zu erwartenden Lebensqualität. Zur guten Stimmung tragen hohe Löhne, geringe Steuern und die Verfügbarkeit von Nahrungsmitteln und Arbeitsplätzen bei. Alle Bürger erwarten, eine Arbeit zu finden und genug Nahrung zu bekommen. Außerdem wollen sie fair für ihre Arbeit entlohnt werden und keine absurd hohen Steuern zahlen. @PDie Bürger sind immer gut darüber informiert, was für Gehälter in anderen ägyptischen Städten üblich sind. Verändert sich der Durchschnittslohn im Königreich, wird Ihnen eine Nachricht mit dem neuen Lohnniveau zugeschickt. @PWenn die Stadt ansonsten hervorragende Lebensqualität bietet, können Sie mit den Steuern ruhig etwas hochgehen. Ihren Bürgern wird es nichts ausmachen, wenn sie ein kleines bisschen mehr Steuern entrichten, um in einer Stadt mit genügend Nahrungsmitteln, Arbeit und guter Entlohnung zu leben. Wenn sie jedoch das Gefühl bekommen, dass die Bedingungen unfair sind, werden sie verärgert reagieren. Zahlt also die eine Hälfte der Bürger hohe Steuern und die andere Hälfte gar keine, verschlechtert sich die Stimmung rapide. @PWenn es Ihnen nicht gelingt, die Erwartungen Ihrer Bürger zu erfüllen, erfahren davon schnell auch potentielle Einwanderer. Diese werden dann beschließen, entweder gar nicht erst zuzuwandern, oder sich eine andere neue Heimat suchen. Sackt der Ruf der Stadt drastisch ab, wandern möglicherweise sogar einige Bewohner auf der Suche nach einem besseren Leben ab. @PSchlechte Stimmung in der Stadt kann neben der Abnahme der Einwanderung auch zu einer Zunahme der Kriminalität führen. @L@L@167Bevölkerung @L@L@388Einwanderung"
        }
    }
    
    message_game_concept_workers {
        id: 40,
        pos [0, 24]
        size [30, 28]
        title { text: "Arbeiter" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Für die meisten Gebäude sind Arbeitskräfte erforderlich. Wenn ein neues Gebäude errichtet wird, für das Arbeitskräfte erforderlich sind, entsendet es einen Repräsentanten, um verfügbare Arbeitskräfte in nahe gelegenen Wohngebieten ausfindig zu machen. Findet er bewohnte Gebiete in der Gegend, und herrscht in der Stadt kein Mangel an Arbeitskräften, wird das Gebäude, aus dem er entsandt wurde, mit Mitarbeitern besetzt. Findet er keine Mitarbeiter, setzt er seine Suche fort."
        }
    }

    message_game_concept_scribes {
        id: 41,
        pos [0, 24]
        size [30, 28]
        title { text: "Schreiber" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Wenn Ihre Stadt zu einer herrlichen Metropole heranreift und das Angebot an Waren, Dienstleistungen und vor allem Bildung nicht mehr zu überbieten ist, werden einige Bürger zu Schreibern. Schreiber arbeiten nicht, bezahlen aber hohe Steuern. Sie können zusehen, wie sie müßig in der Stadt umherwandern.  @PWenn einige Ihrer Arbeiter zu Schreibern werden, kann sich zwar die Nachfrage nach Waren erhöhen, die Anzahl der verfügbaren Arbeitskräfte sinkt jedoch. Falls dann keine Einwanderer in die Stadt strömen, um die neuen, frei gewordenen Stellen zu besetzen, sollten Sie Schritte einleiten, um neue Einwanderer anzulocken. @L@L@387Schreiber @L@L@168Gesellschaft"
        }
    }

    message_game_concept_walkers {
        id: 42,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Fußgänger",
        }
        content {
            text: "'Fußgänger' können in zwei Gruppen unterteilt werden: solche mit einem Ziel und solche ohne. @L@LFußgänger mit Ziel @LDiese Fußgänger verlassen ihre Arbeitsstätten mit einem bestimmten Ziel. Anhand einer Stadtkarte bestimmen sie den kürzesten Weg zu ihrem Ziel. @L@LFußgänger ohne Ziel @LFußgänger, die in der Stadt umherlaufen, bringen Vorteile, wenn sie an Gebäuden vorbeikommen. Einige von ihnen versorgen die Gebäude in der Stadt darüber hinaus mit wertvollen Dienstleistungen. @PUmherwandernde Fußgänger verlassen ihre Gebäude ohne bestimmtes Ziel. @PImmer, wenn solche Fußgänger auf eine Kreuzung stoßen, müssen sie entscheiden, in welche Richtung sie weitergehen wollen. Sie treffen dabei nicht jedes Mal die gleiche Entscheidung, sodass Häuser, an denen sie zuvor vorbeigegangen sind, möglicherweise längere Zeit nicht mehr besucht werden. @PAm einfachsten sind diese Fußgänger durch gute Stadtplanung zu steuern. Da Kreuzungen den Fußgängern so viel Freiheit lassen, sollte man die Anzahl der Kreuzungen beschränken. @P@358Sperren sind ein weiteres Hilfsmittel zur Steuerung. Schauen Sie im Handbuch nach, dort finden Sie weitere Informationen zu diesem Thema. @L@LRaubtiere @LNicht jeder, der in der Stadt unterwegs ist, hat gute Absichten. Auch gefährliche Tiere streifen durch die Stadt und ihre Umgebung, wobei sie rücksichtslos alles töten, was ihnen über den Weg läuft. Die Polizisten versuchen ihr Bestes, diese Tiere zu erlegen, aber der Einsatz des Militärs dürfte die beste Möglichkeit sein, mit Raubtieren fertig zu werden. Zu den Tieren, vor denen Sie sich in Acht nehmen sollten, gehören Hyänen, Nilpferde, Krokodile, Giftschlangen, Skorpione und Löwen."
        }
    }

    message_employment_unemployment {
        id: 43,
        pos [0, 24]
        size [30, 28]
        title { text: "Arbeit und Arbeitslosigkeit" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Fast jedes Gebäude der Stadt benötigt Arbeitskräfte. Ohne Arbeitskräfte kann die Stadt die Versorgung ihrer Bürger nicht gewährleisten. @PWenn Sie zum ersten Mal ein Gebäude errichten, das Arbeitskräfte benötigt, dann macht sich ein Anwerber auf den Weg auf die Suche nach arbeitswilligen Bürgern. Passiert er bewohnte Gebiete in der Gegend, und gibt es arbeitswillige Bürger in der Stadt, dann hat der Anwerber Erfolg, und das Gebäude, aus dem er entsandt wurde, wird mit Mitarbeitern besetzt. @PDie Aufgabe des Anwerbers ist nicht immer leicht zu erfüllen. Eine der größten Herausforderungen für den Herrscher einer Stadt ist, auf dem Arbeitsmarkt ein Gleichgewicht zwischen Angebot und Nachfrage herzustellen. In einer perfekt funktionierenden Welt gibt es in einer Stadt genauso viele Jobs wie Arbeitskräfte. Aber das kommt so gut wie nie vor. Entweder hat eine Stadt zu viele Arbeiter und nicht genug Jobangebote oder zu viele offene Stellen und nicht genug Arbeiter. @PArbeitslosigkeit ist nicht gut für die Stadt. Wenn Arbeitslose nichts zu tun haben, dann reagieren sie enttäuscht, und das drückt den Wert für die @39Stimmung in der Stadt. Möglicherweise rutschen Arbeitslose sogar in die @36Kriminalität ab. Arbeitslosigkeit lässt sich am einfachsten mit der Schaffung neuer Arbeitsplätze beseitigen. Im Allgemeinen schadet es einer Stadt nicht, wenn zusätzliche Waren und Dienstleistungen entstehen. Ein paar neue Farmen, zusätzliche Unterhaltungseinrichtungen, neue Schulen, Bibliotheken oder Tempel können der Stadt zugute kommen. Und wird die Arbeitslosenquote verringert, kann sich das auch positiv auf die Wohlstand- und die Kultur-Wertung auswirken. @PEine weitere Möglichkeit zur Verringerung der Arbeitslosenquote - allerdings eine herzlose - ist, die Bevölkerungsdichte der Stadt zu verringern. Das erreicht man am besten, indem man Wohnhäuser zerstört und damit Bürger zur Auswanderung zwingt. Und das kann sogar einen positiven Effekt auf die Entwicklung der Stadt haben: Wenn Sie minderwertige Unterkünfte abreißen, dann steigt die allgemeine Wohnqualität ihrer sonstigen Wohnhäuser. Diese Qualitätsverbesserung kann sich in einer höheren Wohlstand-Wertung niederschlagen. @PMit dem umgekehrten Problem müssen Sie sich herumplagen, wenn nicht genug Arbeitskräfte zur Verfügung stehen - wenn Sie also zu viele offene Stellen und nicht genug Arbeiter haben. Die beste Lösung für eine solche Situation ist, zusätzliche Einwanderer anzulocken. Richten Sie neue Wohngebiete ein, oder ergreifen Sie Maßnahmen, die dazu führen, dass die vorhandenen Unterkünfte vergrößert werden. Achten Sie außerdem darauf, dass der Wert für die @39Stimmung&in&der&Stadt hoch ist. Wenn Sie mehr als den ägyptischen Durchschnittslohn zahlen oder die Steuern der Stadt senken, können Sie damit neue Einwanderer anlocken. @PWährend Sie darauf warten, dass neue Einwanderer in die Stadt strömen, sollten Sie gemeinsam mit Ihrem @24Aufseher&des&Handels und Ihrem @20Aufseher&der&Arbeitskraft planen, wie der Arbeitskräftemangel beseitigt werden soll. Schauen Sie beim Aufseher des Handels vorbei, und schließen Sie Gewerbestätten, auf die Sie zeitweilig verzichten können. Damit werden einige Ihrer Arbeitskräfte freigesetzt und können andere Jobs übernehmen. Wenn Sie einen Gewerbezweig nicht vollständig stilllegen möchten, dann sind Sie möglicherweise gezwungen, einige Gewerbestätten der entsprechenden Gruppe abzureißen.  @PPlanen Sie gemeinsam mit dem Aufseher der Arbeitskraft, welchen Aufgaben Sie die höchste Priorität zuweisen wollen. Wenn Sie den wichtigen Arbeiten die höchste Priorität zuweisen, stellen Sie damit sicher, dass die Bürger die lebenswichtigen Güter erhalten. @PEine unorthodoxe und nicht hundertprozentig wirksame Maßnahme gegen Arbeitermangel besteht darin, die Unterkünfte Ihrer @41Schreiber in Unterkünfte für @40Arbeiter zurückzuverwandeln. Damit senken Sie die Wohlstand-Wertung für die Stadt und mindern die Steuereinnahmen, aber es entstehen zusätzliche Arbeitskräfte - zu Lasten der Hoffnungen und Träume Ihrer reichsten Bürger! @PObwohl Arbeitslosigkeit eine Menge Stress für die Betroffenen bedeutet, ist eine geringe Arbeitslosenquote sogar gut für eine sich ausdehnende Stadt, denn so gibt es ein Reservoir von Arbeitskräften für neu errichtete Gebäude. Eine Arbeitslosenquote von mehr als 5 Prozent bereitet allerdings Probleme."
        }
    }
    
    message_drinking_water {
        id: 44,
        pos [0, 24]
        size [30, 28]
        title { text: "Trinkwasser" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "So ziemlich die erste Forderung, die Ihre Bürger stellen, ist der Zugang zu sauberem Trinkwasser. Solange sie keinen Zugang zu mindestens einer Wasserversorgungsmöglicheit haben, weigern sie sich standhaft, ihre Unterkünfte auszubauen. @P@62Ziehbrunnen und @61Zisternen versorgen die Bürger mit Trinkwasser. Bei Ziehbrunnen handelt es sich um provisorische Einrichtungen zur Wasserversorgung. Sie sind vielleicht in der wilden Gründungsphase einer Stadt gut genug für die Bürger, aber lange werden die sich nicht mit Wasser aus Ziehbrunnen zufrieden geben. Bald schon werden sie nach Wasser aus Zisternen verlangen. @PZisternen beschäftigen Wasserträger, die den Bürgern das frische Nass direkt ins Haus bringen. Wenn ein Wasserträger an einem Wohngebäude vorbeigeht, hat dieses Gebäude Zugang zu frischem Wasser. Behalten Sie die Wasserträger gut im Auge: Sie sind @42Fußgänger&ohne&Ziel und gehen nicht immer regelmäßige Routen. Wohngebiete, die einmal bestens mit Wasser versorgt waren, können durchaus ihren Zugang zu Wasser verlieren, und zwar vor allem dann, wenn Sie das Straßennetz eines solchen Viertels umbauen. @PWenn die @56Attraktivität der Umgebung hoch genug ist, machen sich die Arbeitskräfte der Zisterne an die Verbesserung ihrer Effizienz und ihres Erscheinungsbildes. Die Wasserträger dieser verbesserten Zisternen machen ihre Rundgänge durch die Nachbarschaft dann sehr viel häufiger. @PSowohl Ziehbrunnen als auch Zisternen können nur dort gebaut werden, wo Grundwasser vorhanden ist, was man am Graswuchs erkennen kann. @PLesen Sie den Eintrag @53Gesundheit&der&Stadt durch, wo mehr über die Vorteile sauberen Trinkwassers verraten wird."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,
        pos [0, 24]
        size [30, 28]
        title { text: "Nahrungsmittel und Landwirtschaft" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Der Weg in die Herzen Ihrer Bürger führt durch ihre Mägen. Wenn Sie für reichlich Nahrungsmittel sorgen - und auch für abwechslungsreiche Kost -, dann steigert das nicht nur die @39Stimmung&in&der&Stadt, sondern auch die @53Gesundheit&der&Stadt.  @PIn 'Pharao' gibt es zahlreiche Arten von Farmen. Sie produzieren die unterschiedlichsten Produkte: @89Getreide, @90Granatäpfel, @90Kichererbsen, @90Salat und @90Feigen. Außerdem gibt es in 'Pharao' zwei unterschiedliche Arten des Ackerbaus: Landwirtschaft im Überschwemmungsgebiet und Wiesenbewirtschaftung. Beide Arten von Farmen benötigen Zugang zu Straßen und Arbeitskräften, aber damit hören die Gemeinsamkeiten eigentlich auch schon auf. Ackerbau ist allerdings auch nicht die einzige Form der Versorgung mit Nahrungsmitteln. Die @359Jagd, die @84Fischerei und die @360Rinderzucht tragen ebenfalls zum Lagerbestand der Silos in der Stadt bei. @L@LLandwirtschaft im Überschwemmungsgebiet @LUm zu verstehen, wie Farmen im Überschwemmungsgebiet funktionieren, müssen Sie zuerst die verschiedenen Stadien des Nils verstehen. Jedes Jahr, in der Regel zwischen Juni und September, tritt der Nil über die Ufer. Die Überschwemmungsgebiete sind komplett vom Wasser bedeckt, und dort kann nichts gebaut werden. Nach ein paar Monaten zieht sich der Nil zurück und hinterlässt fruchtbaren Schlamm, der die Muttererde düngt. Das Überschwemmungsgebiet wird wieder zur Landfläche, und Sie können dort wieder Farmen in Betrieb nehmen. @G56 Der Nil tritt nicht in jedem Jahr genau zum gleichen Zeitpunkt über die Ufer. Einige Überschwemmungen wirken sich positiver aus als andere. Priester machen Gebrauch von 'Nilometern', um vorherzusagen, wie gut die jeweils nächste Flut ausfallen wird, und sie teilen Ihrem @31Hauptaufseher mit, was sie herausgefunden haben. Wenn Sie Osiris, dem Gott der Landwirtschaft und der Nilflut, @51(siehe&Religion), besondere Aufmerksamkeit schenken, dann trägt das möglicherweise dazu bei, dass die Flut in jedem Jahr zufriedenstellend ausfällt. @PSie können im Überschwemmungsgebiet außer während der Flut jederzeit Farmen, Straßen und Bewässerungsgräben bauen. Wenn Sie eine Farm im Überschwemmungsgebiet errichten, dann erscheint nur das Feld ohne Gebäude, denn die Flut zerstört regelmäßig sämtliche Gebäude im Überschwemmungsgebiet. Weil Landarbeiter auf den Farmen im Überschwemmungsgebiet keine Unterkünfte bauen können, brauchen sie einen Platz, wo sie sich treffen und zur Arbeit eingeteilt werden können. Diese Funktion übernehmen @8Arbeiterlager. Arbeiterlager teilen Arbeitskräfte für Aussaat und Ernte auf den Farmen ein, und die Farmen werden nicht bewirtschaftet, wenn kein Arbeiterlager existiert. Landarbeiter sind nicht bereit, über eine bestimmte Entfernung hinaus zu laufen, um ihre Knochenarbeit zu verrichten, und deshalb sollten Sie Arbeiterlager nicht zu weit von den Feldern entfernt errichten. @PDer beste Zeitpunkt zum Bau von Farmen ist kurz nach Rückgang der Flut. Bis zur nächsten Flut können Sie die Erntesaison voll ausnutzen, und die Farm erbringt den maximalen Ertrag. Farmen, die später errichtet werden, produzieren geringere Erträge. @PDer zweite Faktor, den Sie beim Bau von Farmen in Erwägung ziehen müssen, ist die Fruchtbarkeit. Je dunkler das Land und je üppiger das Gras, desto fruchtbarer ist der Ackerboden. Der fruchtbarste Boden findet sich in der Regel unmittelbar in der Nähe des Flussbetts. Je weiter Sie sich vom Fluss entfernen, desto weniger fruchtbar ist das Land. Farmen, die auf dem fruchtbarsten Boden errichtet werden, erbringen die höchsten Erträge. Sie können Bewässerungsgräben im Überschwemmungsgebiet bauen, um die am weitesten vom Fluss entfernten Äcker zu bewässern; dadurch verbessern Sie auch die Fruchtbarkeit von Landflächen, die während einer schwachen Überschwemmung möglicherweise nicht vom Wasser erreicht wurden. @PWegen des jährlichen Wechsels von Flut- und Trockenzeit des Nils produzieren Farmen im Überschwemmungsgebiet in jedem Jahr nur eine Ernte. Das Überleben einer Stadt kann davon abhängen, dass genug Landarbeiter für diese Ernte zur Verfügung stehen und dass es genug Speicherplatz für die Unterbringung der Erträge gibt. @L@LWiesenbewirtschaftung @LDie Äcker im Überschwemmungsgebiet sind nicht die einzigen fruchtbaren Böden, obwohl sie den Großteil des bebaubaren Landes ausmachen. Farmen können auch auf Wiesen errichtet werden, die man am gelben Grasbewuchs erkennt. Je dichter dieser Bewuchs, desto fruchtbarer ist das Land und desto höhere Erträge bringt es ein. Wiesenfarmen verfügen über ein Arbeitsgebäude auf ihrem Grund und Boden und sind deshalb nicht auf die Versorgung durch Arbeiterlager angewiesen. Weil ihr Land nicht überflutet wird, arbeiten diese Farmen während des gesamten Jahres. Sämtliche Wiesenäcker sind allerdings weniger fruchtbar als Land im Überschwemmungsgebiet, und Wiesenfarmen erbringen in der Regel geringere Erträge pro Ernte. Wiesenfarmen profitieren beinahe immer von Bewässerungsgräben. @L@LJagd und Fischerei @LJäger und Fischer profitieren vom natürlichen Wildreichtum Ägyptens. Beide starten von ihren Stützpunkten aus, fangen ihre Beute und kehren zu den Stützpunkten zurück, um die Nahrungsmittel fertig zu stellen. @PJäger haben Jagdhöfe als Stützpunkte. Vom Jagdhof aus begeben sie sich auf die Jagd. Jäger suchen nach Herden von Straußen- und Wasservögeln oder Antilopen. Wenn Sie derartige Tiere in der Nähe der Stadt entdecken, errichten Sie einen Jagdhof in der Nähe. @PFischer versammeln sich in Häfen, wo sie sich gegenseitig Seemannsgeschichten erzählen. Häfen werden (natürlich) am Wasser gebaut, und Fischer sind auf eine Werft angewiesen, die ihnen Boote baut. Sobald sie ein Boot besitzen, laufen die Fischer zum Fischfang aus. Nicht jede Stadt kann Jäger oder Fischer beschäftigen. Wenn Sie feststellen, dass Fische aus dem Wasser springen, kann Ihre Stadt das Fischereigewerbe aufnehmen.  @PDie Größe der Herden und Schwärme ist begrenzt. Jagd und Fischerei können eine kleine Bevölkerung mit ausreichenden Nahrungsmitteln versorgen, aber eine größere Bevölkerung kann sich nicht ausschließlich von Fisch und Wild ernähren. @L@LViehzucht @LRinderfarmen sind oft ausgezeichnete Quellen für zusätzliche Nahrungsmittel. Sie können auf jeder Art von Boden errichtet werden - nicht nur auf fruchtbarem Land. Der kostbare Ackerboden ist daher für andere Zwecke nutzbar. Rinder fressen Stroh, ein Nebenprodukt der @89Getreidefarmen. Die Zahl der Rinderfarmen, die eine Stadt unterhalten kann, ist nur durch die Menge von Stroh begrenzt, die als Viehfutter erübrigt werden kann. @L@LNahrungsmittelverteilung @L@3Silos und @2Basare sind Zwischenstationen auf dem Weg von den Erzeugern der Nahrungsmittel zu den Bürgern der Stadt. In Silos werden die Nahrungsmittel gespeichert, die für die Versorgung der Bürger bestimmt sind, und Basare liefern sie an die einzelnen Häuser aus.  @PWenn ein Nahrungsmittelproduzent eine Lieferung fertig gestellt hat, schafft ein Karrenschieber sie in ein Silo. Basarkäuferinnen suchen die Silos auf, um die von ihren Kunden gewünschten Waren zu beschaffen. Sie können verschiedene Nahrungsmittel gleichzeitig transportieren. Nachdem die Einkäuferinnen mit den Waren zum Basar zurückgekehrt sind, machen sich die Basarhändlerinnen auf den Weg durch die Stadtviertel, um die Nahrungsmittel an die Bevölkerung auszuliefern. @PEs ist sehr wichtig, dass es genügend Silos und Basare gibt. Wenn sämtliche Silos gefüllt sind, bringt der Karrenschieber die Nahrungsmittel in ein @4Warenlager, falls dort Nahrungsmittel angenommen werden. Basarkäuferinnen holen sich einheimische Nahrungsmittel nicht aus Warenlagern (beschaffen sich dort allerdings andere Waren und importierte Nahrungsmittel). Sie beschaffen sich die meisten Nahrungsmittel aus Silos. @PDie Platzierung von Basaren und Silos kann ziemlich schwierig sein. Silos sollten in der Nähe von Nahrungsmittelproduzenten untergebracht werden, damit die Karrenschieber möglichst kurze Wege zurückzulegen haben. Basare sollten in der Nähe von Silos eingerichtet werden, damit die Basarkäuferinnen für ausreichende Vorräte sorgen können. Außerdem sollten Basare in der Nachbarschaft der Wohnungen liegen, die von ihnen versorgt werden sollen. Alle diese Einrichtungen haben allerdings einen negativen Einfluss auf die Attraktivität ihrer Nachbarschaft, sodass ihr Bau neben Vorteilen stets auch Nachteile mit sich bringt.  @PWenn Ihre Stadt wächst, müssen Silos unter Umständen auch weiter entfernt von den Nahrungsmittelproduzenten errichtet werden, um sicherzustellen, dass die Basare in weiter entfernten Stadtvierteln die benötigten Nahrungsmittel beschaffen können. Wenn Sie das Gefühl haben, es sei vielleicht notwendig, dann machen Sie Gebrauch von den 'Besonderen Befehlen' des Silos, damit es auf jeden Fall Nahrungsmittel erhält. @L@LNahrungsmittel importieren @LEinige Städte können nicht genug Nahrungsmittel zur Selbstversorgung produzieren oder produzieren nur wenige Sorten von Nahrungsmitteln und müssen deshalb Nahrungsmittel aus anderen Städten importieren. Importierte Nahrungsmittel werden an Warenlager ausgeliefert, wo Basarkäuferinnen die Lebensmittel aufnehmen und zum Basar transportieren können. @L@LAuf ähnliche Themen wird in diesem Abschnitt durch Querverweise hingewiesen (mit Hyperlinks verknüpfte Begriffe werden in einer anderen Farbe vom restlichen Text hervorgehoben). Wenn Sie diese Einträge durchlesen, werden Sie die Zusammenhänge zwischen Nahrungsmittelproduktion und -verteilung besser verstehen lernen. @L@LKlicken Sie @150hier, wenn Sie mehr über Geschichte der Nahrungsmittel im alten Ägypten wissen möchten. Wenn Sie @157hier klicken, erfahren Sie mehr über den Einfluss des Nils auf die Nahrungsmittelproduktion."
        }
    }

    message_game_concept_industry {
        id: 46
        pos [0, 24]
        size [30, 28]
        title { text: "Gewerbe" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Die Gewerbebetriebe sind höchstwahrscheinlich die größten Arbeitgeber der Stadt. Die Bürger verwenden einige der von ihnen hergestellten Produkte, um ihre Lebensqualität zu verbessern. Andere Produkte können gegen gutes Geld @47gehandelt werden.  @PObwohl eine Stadt mit Sicherheit unzählige Gewerbestätten beherbergt, sind doch allen einige Eigenschaften gemeinsam. Sie alle benötigen Arbeitskräfte, und die Effizienz ist beeinträchtigt, wenn ein bestimmter Produktionsbetrieb oder Rohstoffproduzent zu wenige Arbeitskräfte hat. Alle Gewerbestätten brauchen außerdem Zugang zu einer Straße, damit sie von Arbeitern erreicht werden können. @PEinige Gewerbestätten produzieren Rohmaterialien, die von Produktionsbetrieben zu Fertigwaren weiterverarbeitet werden. Zu derartigen Gewerbestätten gehören @92Tongruben, @361Edelsteinminen, @93Kupferminen, @94Holzfällerlager und @94Schilfsammelstellen. @91Gerstefarmen, @91Hennafarmen und @91Flachsfarmen produzieren ebenfalls Rohstoffe für das Gewerbe. @89Getreidefarmen produzieren nicht nur Nahrungsmittel, sondern mit Stroh außerdem einen Rohstoff zur Weiterverarbeitung. Ein einzelner Rohstoffabbauer kann in der Regel zwei Warenhersteller mit seinem Rohstoff beliefern. Rohstoffe können gehandelt werden, aber sie erzielen nicht so hohe Erlöse wie Fertigwaren. @PBetriebe, die Rohstoffe in Fertigwaren umwandeln (manchmal 'Werkstätten' genannt), sind @96Brauereien, @99Juweliere, @60Webereien, @97Papyruswerkstätten, @1Töpfereien, @364Ziegeleien, @473Lampenwerkstätten, @470Farbmühlen, @98Waffenschmieden und @98Wagenbaubetriebe. Ihre Fertigwaren können in der Stadt verbraucht oder auf dem freien Markt gehandelt werden. @P@95Steinbrüche und @93Goldminen unterscheiden sich von allen anderen Gewerbestätten, weil die von ihnen produzierten Rohstoffe gleichzeitig Endprodukte sind. @82Werften bauen ein Fertigprodukt (Schiffe) aus einem Rohmaterial (Holz), Schiffe können jedoch nicht auf dem freien Markt gehandelt werden. @PLieferanten (Karrenschieber, Schlittenzieher) transportieren Waren dorthin, wo sie gebraucht werden. Die bei Rohstoffproduzenten angestellten Auslieferer versuchen zunächst, die Rohstoffe an die weiterverarbeitenden Betriebe auszuliefern, in denen sie gebraucht werden; dabei bevorzugen sie die nächstgelegenen Einrichtungen. Wenn keine Gewerbestätten die Rohstoffe benötigen, dann transportieren die Auslieferer sie zum nächstgelegenen @4Warenlager, in dem Platz zur Lagerung vorhanden ist. Gibt es keine solchen Warenlager, legen Auslieferer eine Pause ein, bis ein Speicherplatz frei wird. Die einzigen Rohstofflieferanten, die sich anders verhalten, sind der Karrenschieber der Goldmine und der Schlittenzieher des Steinbruchs. Der Auslieferer der Goldmine bringt sein Gold nur zum Palast und unter keinen Umständen in ein Warenlager. Da Stein nicht zu anderen Waren weiterverarbeitet werden kann, bringen Schlittenzieher des Steinbruchs ihre Rohstoffe stets in ein Warenlager. @G74 @PEin paar Gebäude der Stadt benötigen Fertigwaren, um ihren Zweck vollständig zu erfüllen. Dazu gehören die @70Bibliothek, die @68Schreiberschule, das @74Senet-Haus, der @88Drillplatz, das @66Einbalsamierungshaus, die @363Kunsthandwerkergilde und die @363Zimmermannsgilde. Ein Lieferant, der für einen Produktionsbetrieb arbeitet, versucht, seine Güter in einem dieser Gebäude abzuliefern, wenn es die Waren benötigt. Gibt es keinen derartigen Bedarf, dann bringt auch er seine Waren zum Warenlager, oder er steht untätig herum, bis es einen freien Lagerplatz gibt. Karrenschieber lieben diese Art von Sonderurlaub, weil sie bezahlt und versorgt werden, während sie müßig herumstehen.  @PUm festzustellen, ob Ihre Gewerbestätten irgendwelche Schwierigkeiten haben, konsultieren Sie die @18Spezialkarte&Probleme. Diese Spezialkarte zeigt Ihnen, welche Gewerbestätten nicht ordnungsgemäß funktionieren und woran es liegt.  @PDurch einen Rechtsklick auf ein Gebäude wird der aktuelle Produktionsstatus des Gebäudes eingeblendet. Sie können dort ablesen, ob das Gebäude über genug Arbeitskräfte verfügt und wie weit der aktuelle Produktionszyklus gediehen ist. Gibt es irgendwelche Probleme, dann verrät Ihnen das eingeblendete Fenster auch das.  @PKlicken Sie auf einen der oben ausgewiesenen Querverweise (Hyperlinks sind blau hervorgehoben), um weitere Informationen über bestimmte Gewerbestätten zu bekommen. @L@LKlicken Sie @151hier, wenn Sie mehr über die Geschichte des Gewerbes im alten Ägypten erfahren möchten."
        }
    }

    message_game_concept_trade {
        id: 47,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Handel",
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Kaum eine ägyptische Stadt ist völlig autark. Handel verschafft Ihrer Stadt Produkte, die sie selbst nicht produzieren kann. Der Warenexport bringt eine Menge Geld ein - oft mehr, als die Stadt durch Steuereinnahmen verdient. Wegen der großen Bedeutung des Handels sollte Ihre Stadt Handelsbeziehungen aufnehmen, sobald die Grundbedürfnisse der Bewohner zufrieden gestellt sind. @PDie @32Weltkarte zeigt, welche Städte bereit sind, mit Ihnen zu handeln. Handelswillige Städte sind mit einer Flagge markiert. Klicken Sie auf eine dieser Städte, um herauszufinden, welche Waren dort gekauft und verkauft werden. Blaue Punkte in der Ecke des Warensymbols zeigen, wie viele der entsprechenden Waren die Stadt jährlich zu kaufen oder zu verkaufen bereit ist. Ein Punkt bedeutet, dass mit der entsprechenden Ware nur sehr selten gehandelt wird, während drei Punkte darauf hinweisen, dass starke Nachfrage nach dem Handel mit dieser Ware besteht. Diese Werte können sich aufgrund von Angebot und Nachfrage oder politischer Zwänge innerhalb Ägyptens ändern.  @PKlicken Sie auf die Schaltfläche 'Handelsroute eröffnen', um den Preis zu zahlen, den die Aufnahme einer neuen Handelsbeziehung kostet. Die Eröffnung einer Handelsroute kann teuer werden, aber auf lange Sicht lohnt sich die Investition. @PWenn Sie erst einmal eine Handelsroute eröffnet haben, sollten Sie beim @24Aufseher&des&Handels vorbeischauen, um das genaue Vorgehen festzulegen. Klicken Sie auf die Schaltfläche 'Preise anzeigen', um zu prüfen, wie viel Waren beim Kauf oder Verkauf kosten oder einbringen. Sie werden feststellen, dass die Preise für verkaufte Waren niedriger sind als für gekaufte. Die Differenz zwischen Ein- und Verkaufspreis deckt die Unkosten des Händlers ab, die ihm durch die Reise und den Transport in Ihre Stadt entstehen. @L@LImport @LUm eine Ware zu importieren, klicken Sie auf das gewünschte Angebot. Nachdem Sie ein Warenangebot markiert haben, gibt es zwei Möglichkeiten. Entweder Sie entscheiden selbst, wie viel von der Ware Sie gerne in Ihrer Stadt zur Verfügung haben möchten und geben dem Aufseher des Handels entsprechende Anweisungen. Oder Sie lassen den Aufseher des Handels selbst entscheiden, wie viel von der Ware in Ihrer Stadt zur Verfügung stehen sollte. Der Aufseher des Handels wird den Import der Ware fortsetzen, bis die festgelegte Einfuhrgrenze oder die jährliche Höchstgrenze für den Handel mit diesem Handelspartner erreicht ist.  @PEinige Waren, die Ihre Stadt benötigt, können nur importiert werden. Dazu gehören unter anderem weißer Marmor für den Bau von Monumenten und Öl für @473Lampen. Damit sich die @56Wohnungen der Stadt auf ihre höchste Stufe entwickeln können, müssen Sie auch Luxusgüter importieren. @PImporte können ziemlich kostspielig werden, und deshalb sollten Sie die @4Warenlager der Stadt genau beobachten. Sollten Sie feststellen, dass sich die Warenlager mit einer bestimmten Importware füllen, dann sparen Sie Geld, wenn Sie die Einfuhr aussetzen, bis die vorhandenen Güter verbraucht sind. Außerdem ist der Import von Rohstoffen billiger als der von Fertigwaren. Auf lange Sicht spart die Stadt also Geld, wenn sie über eigene Produktionsbetriebe verfügt, die Rohstoffe zu den entsprechenden Fertigwaren verarbeiten. @L@LExport @LUm eine Ware zu exportieren, klicken Sie auf den entsprechenden Artikel. Danach bestimmen Sie, wie viel von der Ware in der Stadt zur Verfügung stehen sollte, oder lassen den Aufseher des Handels diese Entscheidung treffen. Überschüsse werden exportiert, bis die jährliche Importquote Ihres Kunden erreicht ist. Denken Sie daran, dass einige der Exportartikel Ihrer Stadt auch von Ihren eigenen Bürgern gewünscht werden, und Sie sollten dafür sorgen, dass genug Vorräte übrig bleiben, um ihre Bürger zufrieden zu stellen. Überprüfen Sie regelmäßig Ihre Basare und die Wohnungen Ihrer Bürger, um festzustellen, ob dort ausreichende Vorräte Ihrer Handelswaren vorhanden sind. Achten Sie auch darauf, dass Gebäude, die Fertigwaren benötigen, einen entsprechenden Vorrat auf Lager haben. Wenn Wohn- und andere Gebäude Schwierigkeiten haben, eine bestimmte Ware zu bekommen, dann exportiert die Stadt unter Umständen zu viel von dieser Ware. @L@LGelegentlich kann eine Stadt eine bestimmte Ware sowohl importieren als auch exportieren. Das verschafft Ihnen zusätzliche Flexibilität bei der Planung Ihrer Gewerbestätten. Wenn Sie das Einkommen einer Stadt aufstocken wollen, sollten Sie Arbeitskräfte für die Produktion der Ware abstellen und sie zu einem Handelspartner exportieren. Wenn Sie die Arbeitskräfte für andere Aufgaben einsetzen wollen, importieren Sie die Ware. Die Stadt kann eine bestimmte Ware allerdings niemals gleichzeitig importieren und exportieren, und es würde auch keinerlei Vorteile bringen, das Produkt aus einer Stadt zu importieren und es gleich wieder an eine andere zu verkaufen. Käufer zahlen mehr als Verkäufer erhalten, und deshalb würde die Stadt draufzahlen, wenn sie sich als Zwischenhändler betätigen würde. Andererseits ist es oftmals eine lohnende Sache, Rohmaterialien zu importieren und die daraus hergestellten Fertigwaren zu exportieren. @PHändler kommen entweder mit Karawanen oder mit Handelsschiffen in Ihre Stadt. Bevor Sie mit diesen Leuten jedoch überhaupt Handel treiben können, müssen Sie über ein Warenlager verfügen. Neben dem Warenlager brauchen Sie überdies ein @83Dock, wenn Sie mit Handelsschiffen Geschäfte machen möchten. Handelsschiffe erledigen all ihre Geschäfte an den Docks, und wenn sie anlegen, holen die Karrenschieber die notwendigen Waren aus den Warenlagern."
        }
    }
    
    message_game_concept_money {
        id: 48,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Geld",
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Ohne Geld können Sie keine Stadt aufbauen, und die Menge des Geldes in der Kasse einer Stadt ist ein guter Indikator für ihren Erfolg. Die Stadt nimmt Geld ein, indem sie Steuern erhebt, Waren exportiert, Geschenke erhält und Gold schürft - falls ihr entsprechende Minen zur Verfügung stehen. Diese ziemlich einfachen Themen werden am Ende dieses Abschnitts erklärt. Zunächst jedoch sollten Sie ein paar wichtige Details über das Finanzmanagement erfahren.  @L@LSchulden @PWenn Sie zum ersten Mal kein Geld mehr haben, helfen Ihnen unter Umständen andere ägyptische Herrscher mit einem zusätzlichen Deben-Geschenk aus der Patsche. Dadurch entstehen Ihnen keine Nachteile, und die netten Leutchen erwarten auch keine Rückzahlung. Betrachten Sie es aber trotzdem als Warnung, dass Ihre Stadt nicht mehr so einfach mit dem Geld um sich werfen kann. @PWenn Sie sämtliche Barmittel ausgeben oder keine solche Finanzspritze bekommen, kann Ihre Stadtkasse ein Darlehen über bis zu 5000 Deben aufnehmen. Gelbe Zahlen zeigen an, dass Ihre Stadt verschuldet ist. @PHin und wieder ist es leider unvermeidlich, für kurze Zeit ins Minus zu rutschen, und derartige Defizite richten keinen Schaden an, wenn Sie sie rasch kompensieren und wieder schwarze Zahlen schreiben. Langfristige Verschuldung dagegen kann Sie das Spiel kosten. @L@LKonsequenzen der Verschuldung @LFür jeden Monat, in dem Ihre Stadtkasse ein Defizit aufweist, müssen Sie Zinsen zahlen, die automatisch auf Ihre Schuldensumme aufgeschlagen werden. Je höher Ihre Verschuldung, desto mehr Zinsen müssen Sie zahlen und desto schneller wachsen Ihre Schulden.  @PImmer wenn Ihre Stadt am Ende eines Kalenderjahres verschuldet ist, können Sie Ihren jährlichen Tribut nicht entrichten (siehe unten). Wenn Sie eine Tributzahlung auslassen, kostet Sie das kein Geld, aber es drückt Ihre @35Königreich-Wertung ein wenig. Dieser Effekt verschlimmert sich, wenn Sie in darauf folgenden Jahren weitere Tributzahlungen ebenfalls nicht leisten können. @PFalls Sie innerhalb von zwölf Monaten nach Ihrer erstmaligen Verschuldung nicht wenigstens einmal (wie kurz auch immer) eine positive Zwischenbilanz erzielen konnten, sinkt Ihre Königreich-Wertung, weil andere ägyptische Herrscher das Vertrauen in Ihre Führungsqualitäten verlieren. Die Strafe für den ersten 'Jahrestag' Ihrer Verschuldung ist schmerzhaft, richtet aber möglicherweise keinen irreparablen Schaden an. Wenn Sie am Ende Ihres zweiten Jahres im Minus immer noch keine schwarzen Zahlen gesehen haben, dann sinkt Ihre Königreich-Wertung erheblich, und in den folgenden Jahren ist es noch schlimmer.  @L@LSchulden abzahlen @LSchulden sind offensichtlich ein ernstes Problem, und wenn Sie sie schon nicht vermeiden können, dann müssen Sie ihre Schulden wenigstens so schnell wie möglich zurückzahlen. Weiter unten werden Möglichkeiten vorgestellt, wie man an Geld kommt, aber darüber hinaus sollten Sie kein Geld mehr ausgeben, das Ihnen am Ende nicht neue Einnahmen verschafft. Steuereintreiberbüros, Gewerbestätten, die Exportgüter produzieren, und neue Handelsrouten zu Städten, die Ihre Waren kaufen, können samt und sonders sinnvolle Ausgaben bedeuten.  @L@LJährlicher Tribut @LAm Ende eines Jahres muss Ihre Stadt eine 'Steuer' an das Königreich entrichten, die man 'Tribut' nennt. Die Höhe des Tributs hängt von der Zahlungsfähigkeit Ihrer Stadt ab, und deshalb ist er anfangs ziemlich niedrig und steigert sich, wenn Bevölkerungszahl und Wohlstand zunehmen. Schauen Sie beim @30Aufseher&der&Finanzen vorbei, um herauszufinden, wie viel Tribut Sie zahlen.  @PWenn am Ende eines Jahres genügend Deben in Ihren Tresoren lagern, wird die Tributzahlung automatisch abgezogen. Sie leisten diese Zahlung niemals aktiv selbst. Wenn Sie ein Jahr allerdings im Minus abschließen, kann Ihre Stadt den Tribut nicht entrichten, und dadurch sinkt Ihre @35Königreich-Wertung. Die Strafe ist nicht sehr hoch, wenn der Tribut einmal nicht entrichtet wird, fällt aber höher aus, wenn auch im Folgejahr kein Tribut gezahlt wird, und danach fällt sie immer schlimmer aus. In dieser Strafe spiegelt sich Ihr ständig schlechter werdender Ruf innerhalb der eigenen Bevölkerung, die Sie für einen schlechten Finanzverwalter hält.  @L@LSteuern @LSteuern werden für alle Dienstleistungen erhoben, die eine Stadt ihren Bürgern bietet. Bürger werden sich nicht über Steuerzahlungen beschweren, solange die Rate im vernünftigen Rahmen bleibt. Der ursprüngliche Steuersatz von 9 Prozent bietet einen guten Richtwert, aber Sie können den Satz jederzeit anheben oder senken. Besuchen Sie den Aufseher der Finanzen, oder rechtsklicken Sie auf den Palast, um den Steuersatz zu verändern. Steuersenkungen verschaffen Ihnen Freude und Anerkennung. Steuererhöhungen führen zu Beschwerden und können zu einem Massenauszug von Bürgern aus Ihrer Stadt führen. @PManchmal kann eine Steuererhöhung jedoch dringend notwendig werden. Wenn Sie feststellen, dass Ihre Stadt Schulden anhäuft, können Sie den Steuersatz anheben, um das Problem zu mildern. Allerdings sollten Sie vielleicht besser eine alternative Langzeitlösung für die Zahlungsschwierigkeiten Ihrer Stadt finden. Ein hoher Steuersatz kann nämlich schnell die @39Stimmung&in&der&Stadt verschlechtern. @PObgleich Bürger gegen das Zahlen von Steuern an sich nichts haben (oder zumindest nicht allzu viel), werden sie nicht freiwillig einen Anteil ihres Einkommens abgeben. Um Steuern einzunehmen, muss eine Stadt über einen @77Palast verfügen. Anschließend müssen @80Steuereintreiberbüros errichtet werden, damit tatsächlich Steuern eingesammelt werden. @PDer Aufseher der Finanzen weiß, wie viele Ihrer Bürger als Steuerzahler erfasst sind und wie viele Steuereinnahmen Ihnen entgangen sind, weil es nicht genug Steuereintreiber gibt. Schauen Sie sich die @18Spezialkarte&Steuern an, wenn Sie prüfen wollen, ob ein bestimmtes Viertel Ihrer Stadt beim Eintreiben der Steuern unbesucht bleibt. Achten Sie auch darauf, dass Sie die Steuerlast gleichmäßig verteilen. Wenn ein Teil der Bürger hohe Steuern entrichtet und ein anderer Teil gar keine Zahlungen leistet, wird die @39Stimmung&in&der&Stadt in den Keller gehen und die @36Kriminalität steigen. @L@LHandel @LExporteinnahmen werden wahrscheinlich die Hauptquelle für die Einkünfte der Stadt sein. Eröffnen Sie daher so schnell wie möglich Handelsrouten. Es ist entscheidend, dass Sie wissen, wie Waren exportiert werden, und deshalb sollten Sie auf jeden Fall das Thema @47Handel nachlesen, wenn Sie in diesem Punkt nicht ganz sicher sind. @L@LGoldbergbau @LEinige Städte können ihre eigenen Münzen prägen. Gold wird zu Deben verarbeitet, der allgemeinen Währungseinheit in Ägypten. Wenn Sie in einem felsigen Gebiet Goldklumpen entdecken, dann können Sie dort möglicherweise eine @93Goldmine einrichten. Freuen Sie sich nicht zu früh; unter Umständen stellt sich das Erz als @93Kupfer heraus, das zwar auch ziemlich wertvoll, aber nicht so begehrt ist wie Gold. Klicken Sie in der Steuerleiste auf den Button 'Gewerbe', und klicken Sie dort auf 'Rohmaterial', um nachzusehen, welche Erze Ihre Stadt schürfen kann.  @PGoldminen funktionieren genau wie andere @46Gewerbestätten, allerdings werden ihre Erzeugnisse direkt an den Palast geliefert, wo das Gold zu Deben verarbeitet wird, und niemals an Warenlager. @L@LPersönliche Ersparnisse und Gehalt @LGenau wie die Stadt können auch Sie selbst Geld verdienen. Sie werden für Ihre Mühen als Herrscher über die Stadt bezahlt, und Sie können ein Gehalt beziehen, sobald Sie sich einen @78Wohnsitz gebaut haben. Ihr Gehalt wird Ihnen aus der Stadtkasse gezahlt, und die Höhe des Gehalts entspricht Ihrer Erfahrungsstufe. Sie entscheiden selbst über die Höhe Ihres Gehalts, aber wenn Sie sich ein zu üppiges Salär gönnen, könnte sich das negativ auf Ihre @35Königreich-Wertung auswirken. Sie können sich aber natürlich auch ein geringeres Gehalt zahlen oder ganz umsonst arbeiten, was bei Ihren Bürgern Eindruck schindet und die Königreich-Wertung verbessert. Wenn Ihre Stadt in finanzielle Schwierigkeiten gerät, ist der Verzicht auf Ihr eigenes Gehalt eine gute Sparmaßnahme. @PAußerdem können Sie jederzeit persönliche Ersparnisse an die Stadtkasse zurückgeben - ein geeigneter Weg, um Schulden auszugleichen oder zu vermeiden. Dagegen können Sie niemals Geld aus der Stadtkasse in Ihre persönlichen Ersparnisse übernehmen. Das wäre Unterschlagung! @PMit Ihren persönlichen Ersparnissen können Sie außerdem ein 'Geschenk für Ägypten' finanzieren. Solche Spenden an die ägyptischen Bürger bzw. - auf Empfehlung Ihres Aufsehers - an andere ägyptische Führer verbessert Ihre Königreich-Wertung sofort um einen kleinen Schritt. Wenden Sie diese Methode aber mit Bedacht an. Wenn Sie erst einmal einige dieser Geschenke gemacht haben, fangen die jeweiligen Empfänger allmählich an, sie als selbstverständlich zu betrachten, vor allem, wenn Sie regelmäßig Geld spenden. Schränken Sie Ihre milden Gaben dann irgendwann ein, kann das umgekehrt einen negativen Einfluss auf Ihre Königreich-Wertung haben. @PLesen Sie sich den Eintrag über den @22Aufseher&der&Politik durch; dort erfahren Sie mehr über die Bedeutung Ihrer persönlichen Ersparnisse."
        }
    }

    message_game_concept_entertainment {
        id: 49,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Unterhaltung",
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Nur Arbeit und kein Spiel - das freut Imhotep nicht viel. Stellen Sie den Bürgern Ihrer Stadt Unterhaltungseinrichtungen zur Verfügung, um die Lebensqualität zu verbessern. @P@71Bühnen, @72Musikpavillons, @73Pavillons, @74Senet-Häuser und @479Zoos bieten den Bürgern die Unterhaltung, nach der sie verlangen. Wenn Ihre Stadt noch jung ist, sind die Bürger mit der allerkleinsten Einrichtung, der Bühne, zufrieden. In dem Maße, in dem Ihre Stadt dann wächst, wächst auch die Nachfrage nach Unterhaltung, und die Bürger erwarten, von verschiedenen Künstlern unterhalten zu werden. Der @28Aufseher&der&Unterhaltung wird Ihnen helfen herauszufinden, welche Wünsche Ihre Bürger hegen. @PDie meisten Künstler müssen ihre Fertigkeiten zunächst in @75Ausbildungsstätten erlernen. Jongleure feilen in Jonglierschulen an ihrer Geschicklichkeit, Musikerinnen üben in Konservatorien, und Tänzerinnen erlernen die allermodernsten Tanzschritte in der Tanzschule. Einmal ausgebildet, wandern die Künstler von der Ausbildungsstätte zur Unterhaltungseinrichtung. Nur Senet-Meister werden nicht in speziellen Ausbildungsstätten ausgebildet. @PIhre Bürger erkennen, dass ihnen ein Unterhaltungsprogramm zur Verfügung steht, wenn die Künstler an ihren Häusern vorbeiwandern (klicken Sie @42hier, wenn Sie mehr über Fußgänger erfahren möchten). Herumlaufende Künstler kommen aus voll funktionsfähigen Unterhaltungseinrichtungen. Künstler wandern auch durch die Straßen, wenn sie sich auf den Weg von der Ausbildungsstätte zu einer Unterhaltungseinrichtung machen. Denken Sie daran, wenn Sie den Bau entsprechender Einrichtungen planen. Wenn Sie Ihre Unterhaltungseinrichtung und die Ausbildungsstätten auf gegenüberliegenden Seiten eines Stadtviertels unterbringen, müssen Künstler dieses Viertel durchqueren, wenn sie ihre Unterhaltungseinrichtung ansteuern, und auf dem Weg unterhalten sie bereits viele Bürger. Sie sollten aber auch darauf achten, dass Ausbildungsstätten und Unterhaltungseinrichtungen nicht allzu weit voneinander entfernt sind. Je weiter ein Künstler wandern muss, desto weniger Zeit steht für die Vorführungen zur Verfügung, und desto eher wird die Unterhaltungseinrichtung leer stehen und niemandem etwas nützen.  @PDas Senet-Haus und der Zoo benötigen bestimmte Güter, um zu funktionieren. Das Senet-Haus braucht @96Bier, um den Durst seiner Gäste zu stillen, und der Zoo @89Stroh und @359Wildfleisch zur Fütterung und Pflege der Tiere. @L@LNäheres über Unterhaltung im alten Ägypten erfahren Sie @165hier."
        }
    }

    message_game_concept_education {
        id: 50,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Bildung",
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Bildung ist ein Privileg der Reichen. Die reicheren Bürger wissen, dass die Ausbildung in einer @68Schreiberschule ihren Kindern die Tore zu einem angenehmeren Leben öffnet, und für sich selbst wünschen sie sich Zugang zu einer Bibliothek. @PWeder Schreiberschulen noch Bibliotheken können ohne @97Papyrus funktionieren. Bevor Sie eine Bibliothek bauen können, müssen Sie über ausreichende Papyrus-Vorräte in den @4Warenlagern verfügen, um die Regale der Bibliothek mit Schriftrollen zu füllen. @42Fußgänger aus beiden Gebäudetypen tragen Papyrus mit sich herum, während sie die Bevölkerung unterrichten. Die Stadt muss Papyrus herstellen oder importieren, damit das Bildungssystem funktionsfähig bleibt. @PSuchen Sie den @27Aufseher&des&Wissens auf, um herauszufinden, ob der Bildungshunger in der Bevölkerung befriedigt wird.  @PWenn Ihren Bürgern genug Bibliotheken und Schulen zur Verfügung stehen, verbessert das Ihre @35Kultur-Wertung. @L@LKlicken Sie @165hier, um mehr zum Thema Unterhaltung im alten Ägypten zu erfahren."
        }
    }

    message_game_concept_relition {
        id: 51,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Religion",
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Fünf Hauptgottheiten werden in Ägypten verehrt: Osiris ist der Gott der Landwirtschaft und der Nilflut. Ptah ist der Gott der Handwerker. Ra ist der Gott des Königreichs. Seth ist der Gott der Zerstörung. Und Bastet ist die Göttin des Heims. Es lohnt sich, die Götter zu besänftigen, denn wenn man es nicht tut, kann das schlimme Folgen haben. Der @29Aufseher&der&Tempel weiß, wie die Götter gelaunt sind, und deshalb sollten Sie regelmäßig bei ihm vorbeischauen. @PViele Städte haben eine Schutzgottheit. Der Schutzgott einer Stadt verlangt mehr Aufmerksamkeit als die anderen lokalen Gottheiten. Nun verlangen lokale Gottheiten zwar weniger Aufmerksamkeit als ein Schutzgott, aber sie können die Geschicke der Stadt doch genauso zum Guten oder zum Schlechten beeinflussen. Einige Götter sind in der Stadt jedoch möglicherweise unbekannt und können daher ohne Konsequenzen ignoriert werden. @PDer beste Weg, um die Götter zu besänftigen, ist, ihnen möglichst viele @67Tempel&und&Schreine zu weihen. Der Schutzgott erwartet dabei, dass ihm mehr Schreine als sonst einer Gottheit in der Stadt geweiht sind. Die lokalen Gottheiten geben sich zwar mit weniger Tempeln und Schreinen zufrieden als der Schutzgott, aber nichtsdestotrotz erwarten sie die gleiche Zahl von Tempeln und Schreinen wie alle anderen lokalen Gottheiten.  @PGötter können auch durch die Veranstaltung von Festen besänftigt werden - je größer, desto besser. Üppige und gewaltige Feste sind wertvolle Sofortmaßnahmen, um Unheil abzuwenden, wenn eine bestimmte Gottheit unzufrieden mit der Stadt ist. Veranstalten Sie ein Fest zu Ehren der zornigen Gottheit, und diese Gottheit wird sich ein wenig beruhigen, was Ihnen Zeit verschafft, um zusätzliche Tempel und Schreine zu errichten, bevor diese Gottheit die Stadt mit einem Strafgericht überzieht. Suchen Sie den @29Aufseher&der&Tempel auf, um ein Fest zu planen. Beachten Sie, dass Feste erst dann abgehalten werden können, wenn die Stadt über einen Festplatz verfügt. 'Gewaltige Feste' setzen außerdem voraus, dass die Stadt über genug @96Bier in den @4Warenlagern verfügt. Aufgrund der großen Anstrengungen, die die Vorbereitung eines Fests verlangt, kann eine Stadt innerhalb von zwölf Monaten maximal zwei Feste ausrichten.  @PNeben Tempeln und Schreinen können Sie auch einen Tempelkomplex errichten, normalerweise zu Ehren der Schutzgottheit der Stadt. Jede Stadt kann immer nur einen Tempelkomplex unterhalten. Hin und wieder ist es jedoch auch möglich, einer lokalen Gottheit, die besonders wichtig geworden ist, einen Tempelkomplex zu bauen. Seien Sie aber vorsichtig! Der Schutzgott der Stadt könnte sehr eifersüchtig werden, wenn eine andere Gottheit einen Tempelkomplex geweiht bekommt. @PTempelkomplexe kosten eine Menge, sind ihr Geld aber wert. Wenn die Stadt über einen funktionsfähigen Tempelkomplex verfügt, bringt das viele Vorteile, und die @35Wohlstand-Wertung steigt. Sie können außerdem für den Ausbau des Tempelkomplexes mit einem Orakel oder einem Altar zahlen. Folgende Tempelkomplexe und Erweiterungen stehen zur Verfügung: @L@L@350Tempelkomplex&des&Osiris: @P	Altar des Sobek @P	Orakel des Min @L@351Tempelkomplex&des&Re @P	Altar der Maat @P	Orakel des Horus @L@352Tempelkomplex&des&Ptah @P	Altar des Amun @P	Orakel des Thot @L@353Tempelkomplex&des&Seth @P	Altar des Anubis @P	Orakel der Sachmet @L@354Tempelkomplex&der&Bastet @P	Altar der Isis @P	Orakel der Hathor @L@LWenn den Bürgern verschiedene Einrichtungen zur Verehrung der Götter zur Verfügung stehen, dann steigt die @35Kultur-Wertung der Stadt. @L@LNäheres zum Thema Religion im alten Ägypten erfahren Sie @399hier."
        }
    }

    message_game_concept_war {
        id: 52
        pos [0, 24]
        size [30, 28]
        title {
            text: "Krieg"
        }
        subtitle {
            text: "Spielkonzept",
        }
        content {
            text: "Ägypten wird fast ständig von Kriegen bedroht. Von Zeit zu Zeit dringen Soldaten aus anderen Ländern in Ägypten ein, um das Land zu unterwerfen. Manchmal kommt es auch innerhalb von Ägyptens Grenzen zu Unruhen, wenn Städte sich bekriegen oder gar ein ausgewachsener Bürgerkrieg ausbricht. Hin und wieder beschließt auch der Pharao, einen Krieg gegen Erzfeinde oder aufrührerische Verbündete zu führen. @PSie können zahlreiche Vorsichtsmaßnahmen treffen, um Ihre Stadt vor den Schrecken des Krieges zu beschützen. Bauen Sie @85Verteidigungsanlagen, um die Grenzen Ihrer Stadt gegen eindringende Streitkräfte abzuschirmen. Außerdem können Sie @37Forts, @356Kriegs- und @357Transportschiffe bauen, um Feinde anzugreifen, die in die Stadt eindringen. @PDer @21Aufseher&des&Militärs wird Sie vor einem bevorstehenden Angriff warnen, und Sie erhalten @34Nachrichten über feindliche Truppenbewegungen. Auf der @32Weltkarte können Sie die Marschroute sich nähernder Feinde verfolgen. @PSeien Sie vorsichtig, damit Sie nicht selbst einen Angriff provozieren. Wenn Sie bei der Verwaltung der Stadt versagen oder andere Herrscher in Ägypten verärgern, dann sinkt die @35Königreich-Wertung. Wenn die Königreich-Wertung unter einen bestimmten Wert sinkt, wird Ihre Stadt möglicherweise angegriffen. @PKrieg beschränkt sich nicht auf die unmittelbare Umgebung Ihrer Stadt. Hin und wieder ist Ägypten auch an Kriegen innerhalb der eigenen Grenzen oder sonstwo in der Welt beteiligt. Manchmal benötigen eine andere Stadt oder der Pharao Ihre Truppen oder Kriegsschiffe, um einen Feind zu besiegen. Sie ordnen Truppen für derartige Staatsdienste gemeinsam mit dem Aufseher des Militärs ab, indem Sie in seinem Fenster bestimmte Kompanien oder Schiffe für den Auslandseinsatz auswählen und auf die Reise schicken. Wenn mehr als eine Stadt Ihre Hilfe wünscht, müssen Sie den @22Aufseher&der&Politik aufsuchen und entscheiden, welcher Stadt Sie Unterstützung gewähren wollen. @L@LNäheres zum Thema Feinde im alten Ägypten erfahren Sie @181hier."
        }
    }

    message_tutorial_health {
        id: 53
        pos [0, 24]
        size [30, 28]
        title { text: "Gesundheit" }
        subtitle { text: "Spielkonzept" }
        content {
            text: "Ist der Gesundheitszustand der Stadt schlecht, kann dies einwanderungswillige Bürger abschrecken oder im schlimmsten Fall dazu führen, dass einige Ihrer Untertanen sterben. Ergreifen Sie Maßnahmen, um sicherzustellen, dass Ihre Bürger gesund bleiben. Eine Reihe von Seuchen könnte Ihre Bürger heimsuchen, wenn Sie keine Vorsichtsmaßnahmen treffen. @PUm zu gewährleisten, dass Ihre Bürger gesund bleiben, sollten Sie für eine ausreichende Versorgung mit Nahrungsmitteln sorgen und eine @64Arztpraxis erbauen. Je abwechslungsreicher die Ernährung, desto besser ist die Gesundheit Ihrer Bürger. Der Zugang zu @66Einbalsamierungshäusern verbessert ebenfalls den allgemeinen Gesundheitszustand in der Stadt. Sauberes Trinkwasser aus einer @61Zisterne und Zugang zu einer @65Apotheke verringern das Risiko einer Malaria-Epidemie. Der allgemeine Gesundheitszustand der Stadt wird anhand der Gesundheit jedes einzelnen Bürgers ermittelt, und deshalb sollten Sie geeignete Gesundheitsvorsorgeeinrichtungen für alle Ihre Bürger bereitstellen. @PNeben der Malaria suchen auch andere Krankheiten und gefürchtete Seuchen wie die Pest die Stadt heim. Wenn Sie sorgfältig planen und ein wachsames Auge auf die Gesundheit der Bürger haben, können derartige Gesundheitsprobleme vermieden werden. @L@LKrankheiten @LKrankheiten kommen in Häusern vor, die nicht regelmäßig von einem Arzt besucht werden und keine regelmäßige Nahrungsmittelversorgung haben. Normale Plagen, wie z.B. Seuchen, sollten Sie übrigens nicht mit @494großen&Plagen verwechseln. Große Plagen werden durch Faktoren ausgelöst, die von Ihnen nicht beeinflusst werden können, und haben nichts mit der Gesundheit der Stadt zu tun.  Einfache Krankheiten betreffen einzelne Häuser und verbreiten sich nicht. Hat allerdings ein ganzes Stadtviertel einen besonders schlechten Zugang zu ärztlicher Versorgung und Nahrungsmitteln, dann können Krankheiten auch in mehreren Häusern gleichzeitig ausbrechen. @PSehen Sie auf der @18Spezialkarte&Risiken nach, welche Häuser für Krankheiten besonders anfällig sind. Bauen Sie zusätzliche Arztpraxen in solchen Gebieten, und stellen Sie sicher, dass die Häuser durch @2Basare mit Nahrungsmitteln versorgt werden. Sie können auch die @18Spezialkarte&Gesundheit:&Arzt benutzen, um herauszufinden, welche Wohnungen guten Zugang zu Ärzten haben, oder die @18Spezialkarte&Basarzugang, um zu prüfen, welche Häuser von Basarhändlerinnen besucht werden. @L@LMalaria @LMalaria ist eine der Gefahren, denen man in der Nähe des Wassers ausgesetzt ist. Häuser in der Nähe des Flusses oder entlang schilfbewachsener Sumpfgebiete sind am stärksten gefährdet. Wie andere Krankheiten befällt die Malaria einzelne Häuser. Allerdings kann sie auf benachbarte Häuser überspringen. Um das Risiko eines Malaria-Ausbruchs zu minimieren, sollten Sie in Risikogebieten viele Apotheken bauen und sicherstellen, dass die dortigen Wohnungen ihr Wasser aus einer Zisterne beziehen. Sehen Sie auf der @18Spezialkarte&Malaria nach, welche Häuser ein besonderes Malaria-Risiko darstellen. @L@LSeuchen @LAusbrüche von Seuchen wie der Pest treffen die Stadt häufig dann, wenn der allgemeine Gesundheitszustand der Stadt besonders schlecht ist, und dabei spielt der Gesundheitszustand einzelner Häuser kaum eine Rolle. Das Einzige, womit Sie einen Seuchenausbruch wirksam verhindern können, ist, dafür zu sorgen, dass der allgemeine Gesundheitszustand gut bleibt. @PWenn eine Seuche ausbricht, befällt sie zunächst ein einzelnes Haus. Einer der fantasierenden, von der Seuche gezeichneten Bewohner des Hauses läuft durch die Straßen und infiziert die Bewohner jener Häuser, an denen er vorbeikommt. Innerhalb eines Monats wird er der Seuche erliegen. Zum Glück gibt es jedoch die Kräuterkundigen aus den Apotheken. Sie holen jeden infizierten Bürger von der Straße, dem sie begegnen. @PKeine Spezialkarte kann Ihnen zeigen, in welchem Haus der erste Seuchenpatient Symptome der Krankheit entwickeln wird, weil Seuchen nicht aufgrund der besonderen Verhältnisse in einem bestimmten Haus oder Viertel ausbrechen. @L@PWenn in einem Haus irgendeine der oben beschriebenen Krankheiten ausbricht, sterben alle Bewohner dieses Hauses. Das Haus bleibt zwei Monate lang ein Krankheitsherd, und in dieser Zeit ziehen weder Einwanderer noch Vagabunden dort ein. Nach zwei Monaten ist das Haus wieder ansteckungsfrei und bewohnbar. Sämtliche Güter aus dem Besitz der Vorbewohner sind nach wie vor vorhanden. @PZahnarztpraxen nehmen eine Sonderstellung ein. Auch wenn sie als Gebäude im Rahmen der Gesundheitsvorsorge klassifiziert werden, steigern sie lediglich den Landwert eines Gebiets und haben keinerlei Auswirkungen auf den allgemeinen Gesundheitszustand der Stadt. @PDer @26Aufseher&der&Gesundheit wird Ihnen dabei helfen, die Gesundheit Ihrer Bürger zu erhalten."
        }
    }

    message_bent_pyramid {
        id: 54,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Knickpyramide",
        }
        content {
            text: "Von der Sonne inspiriert, stellten sich die Architekten der Knickpyramide einen riesigen Obelisken mit geknickten Seiten vor, der einen wärmenden Sonnenstrahl darstellen sollte. Und damit die Pyramide so hell leuchten würde wie die Sonne, wurden ihre Seiten geglättet. @PFür den Bau einer Knickpyramide benötigen Sie @95einfachen&Stein und @95Kalkstein sowie Bauern aus dem @8Arbeiterlager als Arbeitskräfte. Sobald im @4Warenlager vier Blöcke einfacher Stein oder Kalkstein gelagert sind, laden Arbeiter den Stein auf einen Schlitten und ziehen ihn zur Baustelle. Um die Steine richtig zu platzieren, sind die Dienste der @363Steinmetzgilde unabdingbar. Die @363Zimmermannsgilde erbaut Rampen aus Holz, das direkt an die Zimmermannsgilde geliefert wird. @PKnickpyramiden gibt es in zwei Größen. Weitere Informationen finden Sie in den Einträgen @370Monumentbau, @373Aufseher&der&Monumente und @369Vorarbeiter&des&Baus. @L@LWenn Sie mehr über die Geschichte der Knickpyramide wissen wollen, klicken Sie @392hier."
        }
    }

    message_brick_core_pyramid {
        id: 55,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Ziegelkernpyramide",
        }
        content {
            text: "Ziegelkernpyramiden sind die komplexesten Pyramiden, die Sie errichten können, da man hierfür drei verschiedene Rohstoffe und drei verschiedene Baugilden benötigt. Für den Bau benötigen Sie @364Ziegel, @95Kalkstein und @94Holz sowie die Dienste der @363Maurergilde, der @363Steinmetzgilde und der @363Zimmermannsgilde. Außerdem benötigen Sie Bauern aus den @8Arbeiterlagern als Arbeitskräfte, um die schweren Ziegel und Steine zum Bauplatz zu schleifen, sobald genug davon in den @4Warenlagern vorhanden sind. @PZiegelkernpyramiden gibt es als kleine, mittlere und große Pyramiden, als Pyramidenkomplexe und große Pyramidenkomplexe. @PWeitere Informationen finden Sie in den Einträgen @370Monumentbau, @373Aufseher&der&Monumente und @369Vorarbeiter&des&Baus. @L@LWenn Sie mehr über die Geschichte der Knickpyramide wissen wollen, klicken Sie @392hier."
        }
    }

    message_housing_and_desirability {
        id: 56
        pos [0, 24]
        size [35, 32]
        title { text: "Wohnungen und Attraktivität" }
        content {
            text: "Um Menschen in die Stadt zu locken, müssen Sie zunächst einmal Wohngebiete ausweisen. Wenn die ersten Einwanderer in die Stadt kommen, genügt ihnen eine provisorische Unterkunft. Wenn die Stadt dann wächst (und mit ihr die Ansprüche ihrer Bewohner), wollen diese ihre Behausungen zu schöneren, beeindruckenderen Gebäuden ausbauen.   @PAußerdem können die Bürger ohne Ihre Hilfe nicht finden, was sie doch zuallererst zum Leben brauchen: Wasser. Ohne Trinkwasser können Ihre Bürger nicht lange überleben.  @PDiese Einrichtungen - Wohnungen, Straßen und Wasserversorgungseinrichtungen - sind die grundlegenden Voraussetzungen jeder Stadt. Wenn Sie die Kunst meistern, diese Gebäude zu errichten, bekommen Sie auch das Grundlagenwissen, das Sie brauchen, um eine großartige Stadt zu bauen.  @PAttraktivität @L@LWenn Sie die Gegend verschönern, vergrößert sich der Anreiz, bessere Wohnungen zu bauen. Gegenden mit Gärten und repräsentativen Statuen werden von Ihren Bürgern sehr geschätzt. Genauso wichtig ist es, unattraktive Elemente auf ein Minimum zu reduzieren. Es wird Ihren Bürgern wenig Freude bereiten, wenn sie in der Nähe lauter, stinkender Gewerbestätten leben oder neben Gebäuden, die zwielichtige Gestalten anziehen.  @PHeruntergekommene Gebäude verringern die Attraktivität der umliegenden Gegend. Klapprige Gebäude fangen darüber hinaus leicht Feuer - durch den Ausbau verringert sich auch die Feuergefahr. Schöne Wohngebäude verbessern außerdem die Attraktivität der Umgebung und tragen möglicherweise auch dazu bei, dass andere nahe gelegene Gebäude ebenfalls ausgebaut werden.  @PEntwicklung der Wohnungen @L@LMit der Verbesserung der Lebensbedingungen in der Stadt erhöhen sich auch die Ansprüche der Bürger an ihre Wohnungen. Die Leute bauen ihre Wohnungen dann selbständig aus. Hoch entwickelte Wohngegenden haben viele Vorteile, unter anderem ein höheres Steueraufkommen und mehr Wohlstand. Um die Entstehung besserer Wohngebiete zu fördern, müssen Sie lediglich darauf achten, dass Ihre Bürger in angenehmen Gegenden wohnen und Zugang zu allen Waren und Dienstleistungen haben, die sie benötigen.  @L@LDie Wohnungen der alten Ägypter unterschieden sich recht stark in Größe und Qualität. Klicken Sie @152hier, um mehr darüber zu erfahren."
        }
    }
    
    message_game_concept_roads {
        id: 57,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Straßen",
        }
        content {
            text: "Die meisten Gebäude in Pharao benötigen Zugang zu einer Straße. Wenn Ihre Bürger ein Gebäude nicht über eine Straße erreichen können, können sie weder eine Arbeit finden noch die Waren oder Dienstleistungen in Anspruch nehmen, die dort angeboten werden. Voraussetzung für den Bau einer Straße ist, dass das Land planiert ist. Klicken Sie, wenn diese Voraussetzung erfüllt ist, erst auf den 'Straße'-Button und anschließend auf das Gebiet, auf dem Sie die Straße platzieren wollen. Wie beim Planieren von Land können Sie große Straßenabschnitte auf einmal bauen, indem Sie auf einen Punkt klicken und den Mauszeiger mit gedrückter Maustaste über die Fläche bewegen. Während Sie die Maus bewegen, sehen Sie, wie die Straße aussehen wird, wenn sie gebaut ist, und wie viel dies kosten wird. Treten Hindernisse auf, wie z.B. nicht planiertes Land oder ein Gebäude, führt die Straße um das Hindernis herum. Wenn Sie die Maustaste loslassen, ist die Straße gebaut.  @PSobald die Menschen in Wohngegenden wohlhabender werden, beginnen sie, in Eigeninitiative nichtbefestigte Wege zu pflastern. Wenn eine Straße erst einmal gepflastert ist, können Sie sie durch Plätze verschönern. @PBeinahe alle Gebäude in Ihrer Stadt benötigen eine Straßenanbindung. Die einzigen Ausnahmen davon bilden Gärten, Statuen und Forts. Schreine, Mauern und Wohngebiete benötigen zwar keine direkte Straßenanbindung, können jedoch nur dann die Dienstleistungen vorbeigehender Fußgänger nutzen, wenn sie sich im Umkreis von zwei Feldern von der Straße befinden. @PFußgänger können nur an solchen Stellen die Grenzen zwischen Überschwemmungsgebiet und trockenem Land überqueren, an denen Straßen vorhanden sind. Die Küste ist steil, schlammig und rutschig, daher sind Straßen nötig, um sicher passieren zu können. @PAlle Straßen haben, was den Verkehr anbelangt, die gleiche Kapazität, und alle Fußgänger bewegen sich mit derselben Geschwindigkeit auf den Straßen, unabhängig davon, ob diese gepflastert sind.   @PDie Königreichstraße @L@LDiese Straße führt durch die Stadt und verbindet sie mit anderen Städten in Ägypten und in anderen Ländern. Einwanderer nutzen die Königreichstraße, um in Ihre Stadt zu gelangen. Achten Sie darauf, die Stadt nicht vom Königreich zu isolieren. Um zu überleben, braucht sie Zugang zum Rest des Königreichs.  @PDas bedeutet nun nicht, dass sämtliche Straßen der Stadt direkt mit der Königreichstraße verbunden sein müssen, sondern lediglich, dass alle Gebäude einen freien, begehbaren Pfad benötigen, egal, ob es sich dabei um eine Straße oder um freies Land handelt. @PMehr ist zum Thema Königreichstraße eigentlich nicht zu sagen. Mit den Feinheiten des Zugangs zu Gebäuden müssen sich die meisten Spieler wahrscheinlich niemals herumschlagen, aber es gibt einige selten Fälle, in denen man den Zugang zur Königreichstraße verlieren kann, ohne dass ein sichtbares Hindernis errichtet wurde. @PWenn Sie zu Beginn ein neues Gebäude errichten, wird ein Weg gesucht, der zur Königreichstraße führt - ganz gleich, ob er zum Straßennetz der Stadt gehört oder ob es sich um offenes, begehbares Land handelt. Meist wird das Gebäude an einer vorhandenen Straße platziert, so dass der Zugang der Straße zur Königreichstraße entscheidend ist. Manchmal werden Sie jedoch auch ein Gebäude bauen, das nicht an einer Straße liegt. In diesem Fall sucht das neue Gebäude nach einem Zugang über das dazwischenliegende freie Land. Wenn Sie das Gebäude dann an eine städtische Straße anbinden, wird der Zugangspunkt auf die neue Straße verlegt. Gelingt es der neuen Straße allerdings nicht, einen begehbaren Weg zur Königreichstraße zu finden (vielleicht wird dieser durch genau das Gebäude blockiert, zu dem Sie gerade eine Verbindung hergestellt haben), verliert das an die Straße angrenzende Gebäude ebenfalls die Anbindung an die Königreichstraße. @PMehr über 'Zugangspunkte' erfahren Sie im folgenden Abschnitt. @PNoch eine letzte Bemerkung zur Königreichstraße: Die Straße selbst ist nichts Besonderes - entscheidend sind nur die Stellen, an denen sie Ihr Gebiet erreicht oder verlässt. Teile der Königreichstraße können Sie wie andere Straßen in der Stadt auch verlegen, solange Sie nicht den Zugang zu diesen wichtigen Eingangs- und Ausgangspunkten blockieren. @L@LGebäude mit zwei angrenzenden Straßen @LManchmal kann es vorkommen, dass Sie ein Gebäude so platzieren, dass es an zwei Straßen grenzt, die entweder nicht miteinander verbunden sind, oder die in großer Entfernung von diesem Gebäude verbunden sind. Das bedeutet nicht, dass Fußgänger von beiden Straßen aus in das Gebäude gelangen können bzw. dass man vom Gebäude aus in beide Straßen gelangen kann. Jedes Gebäude kann maximal einen 'Zugangspunkt', also eine aktive Straßenanbindung haben. @PNehmen wir beispielsweise an, dass Sie ein Warenlager errichten. Auf der Südseite befindet sich eine Straße. Betriebe, Karawanen und Basarkäuferinnen auf der Südseite des Warenlagers verhalten sich in diesem Fall genauso, wie man das erwarten würde. Nehmen wir nun an, dass auch Betriebe im Norden des Warenlagers Zugang dazu haben sollen. Wenn Sie nun eine Straße auf der Nordseite des Warenlagers errichten, könnte man erwarten, dass Gewerbestätten im Norden den Zugang auf der Nordseite wählen, und solche im Süden weiterhin die Straße im Süden nutzen. Da das Gebäude jedoch nur einen Zugangspunkt haben kann, haben die Gewerbestätten im Norden Pech gehabt, wenn Sie keine Verbindungsstraße zwischen den beiden Straßen bauen. @PGrenzen an ein Gebäude tatsächlich zwei oder mehr Straßen an, wird der Zugangspunkt auf Grundlage des größeren Straßennetzes gewählt. Um bei obigem Beispiel zu bleiben: Wenn die südlich gelegene Straße Teil des Hauptstraßennetzes der Stadt ist, während die neue Straße im Norden nur in ein kleines Gewerbegebiet führt, wird der Zugangspunkt an der südlich gelegenen Straße platziert. Führt dagegen die ursprüngliche Straße auf der Südseite in eine kleine Siedlung und die neue Straße auf der Nordseite stellt eine Anbindung an die Innenstadt dar, wird die nördlich gelegene Straße gewählt. @PUm unvorhergesehene Komplikationen zu vermeiden, sollten Sie keine Gebäude bauen, die zwei nicht miteinander verbundene Straßen berühren. Verbinden Sie in einem solchen Fall die Straßen. Falls Sie das nicht tun, müssen Sie sich darüber im Klaren sein, dass das Gebäude nur über eine der Straßen erreichbar sein wird. Um festzustellen, von welcher Straße aus Zugang besteht, sehen Sie einfach den Fußgängern zu. @L@LKlicken Sie @153hier, wenn Sie mehr über die Geschichte der Straßen im alten Ägypten erfahren möchten."
        }
    }

    message_game_concept_water_crossings {
        id: 58,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Fähren und Brücken",
        }
        content {
            text: "Ohne den Nil könnte Ägypten nicht überleben, aber ohne ihn hätten die Stadtplaner manche Sorgenfalte weniger. Gut, dass es Fähren und Brücken gibt, um beide Seiten des fruchtbaren Nilufers erreichen zu können.  @PBrücken @L@LEine Brücke ist eine relativ billige Methode, kleine Gewässer zu überqueren. Allerdings können damit nur kurze Strecken überspannt werden. Außerdem kommen Schiffe, sowohl Fischerboote als auch Kriegsschiffe, nicht unter Brücken hindurch. Bauen Sie nur dann Brücken, wenn der zu überwindende Abstand gering ist und es keinen Schiffsverkehr in diesem Gewässer gibt.  @PBrücken müssen an geraden Küstenabschnitten errichtet werden - das gilt auch für die gegenüberliegende Seite. Wenn eine Brücke an der gewählten Stelle errichtet werden kann, wird ein grünes 'Geisterbild' der Brücke angezeigt. Kann die Brücke nicht gebaut werden, wird ein rotes Quadrat angezeigt. Gewässer lassen sich auch mit Fähren überqueren. Fähren sind weitaus vielseitiger als Brücken und behindern den Schiffsverkehr nicht.   @PFür eine Fähre müssen zwei Anlegeplätze gebaut werden. Genau wie andere Ufergebäude müssen auch diese Fährhäfen an geraden Küstenabschnitten gebaut werden. Und wie Sie es von anderen Bauten her schon kennen, haben Sie eine geeignete Stelle für den Fährhafen gewählt, wenn ein grünes 'Geisterbild' des Gebäudes angezeigt wird. Nach dem Platzieren des ersten Anlegeplatzes werden grüne Quadrate auf dem gegenüberliegenden Ufer sichtbar. Den zweiten Fährhafen können Sie überall bauen, wo ein grünes Quadrat zu sehen ist. Beide Anlegeplätze benötigen Arbeitskräfte und eine Straßenanbindung, bevor sie benutzt werden können. Sie müssen also wahrscheinlich einige Wohngebiete auf der anderen Seite des Flusses ausweisen, sobald die Fährhäfen gebaut sind. Fährschiffer bringen eigene Fähren mit, die Dienste einer Werft werden also nicht benötigt.  @PSobald die Anlegeplätze für die Fähren fertig sind, können Ein- und Auswanderer das Wasser überqueren. Da sie eigene Boote verwenden, können sie die Fährhäfen benutzen, auch wenn diese keine Arbeitskräfte oder Straßenzugänge haben. Sollen jedoch andere Personen mit der Fähre transportiert werden, sind sowohl Arbeitskräfte als auch Straßenzugänge erforderlich.   @PJeder Fährhafen verfügt über ein Fährschiff. Beide Boote warten, bis eines davon mit mindestens vier Passagieren besetzt ist, bevor sie den Fluss überqueren. Bei den vier Passagieren kann es sich um eine beliebige Kombination aus Fußgängern mit Ziel handeln. Ist einer der Passagiere ein Lieferant mit Waren, werden seine Waren ebenfalls mitgenommen. Wenn die Wartezeit zu lang wird, setzt eine Fähre auch dann über, wenn nicht genügend Passagiere an Bord sind.  @PHat eine Fähre keinen Platz mehr, warten die Menschen geduldig, bis ein Platz frei wird. Falls die Schlangen an den Fährhäfen zu lang werden, sollten Sie den Bau zusätzlicher Anlegeplätze in Erwägung ziehen.  @L@LDa der @157Nil ihr Land quasi in der Mitte durchschnitt, lag es nahe, dass die alten Ägypter Boote und Schiffe in großer Zahl einsetzten, um Personen und Waren zu befördern. Um mehr über den Schiffbau im alten Ägypten zu erfahren, klicken Sie @179hier."
        }
    }
    
    message_game_concept_irrigation {
        id: 59,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Bewässerung",
        }
        content {
            text: "Wasserheber und Bewässerungsgräben verteilen die Segnungen des Nils über eine größere Fläche. Durch die Bewässerung von landwirtschaftlichen Nutzflächen wird deren Fruchtbarkeit erhöht. @PUm einer Farm die Vorteile der Bewässerung zugute kommen zu lassen, müssen Sie in einem Umkreis von zwei Feldern einen Bewässerungsgraben anlegen. Die Wirkung der Bewässerung ist begrenzt - ein Bewässerungsgraben im Umkreis von zwei Feldern genügt für die vollständige Bewässerung. @PFarmen im Überschwemmungsgebiet befinden sich auf Höhe des Wasserspiegels und können über Bewässerungsgräben direkt mit dem Nil verbunden werden. Wiesenfarmen befinden sich jedoch nicht auf Höhe des Wasserspiegels, daher ist für ihre Bewässerung ein Wasserheber erforderlich. @PWasserheber transportieren das Wasser jeweils um eine Stufe höher. Sie können auf einem Feld errichtet werden, das entweder ans Überschwemmungsgebiet oder an ein Gewässer angrenzt. Für Wasserheber neben dem Überschwemmungsgebiet müssen Sie einen Bewässerungsgraben vom Nil bis zum Wasserheber anlegen, damit dieser genügend Wasser bekommt. @PUm Wiesenfarmen zu bewässern, schließen Sie einen Bewässerungsgraben hinten an den Wasserheber an. Bewässerungsgräben führen um alle Hindernisse (mit Ausnahme von Straßen) herum. Unter Straßen führen sie automatisch hindurch. @PMit der erhöhten Fruchtbarkeit des Bodens steigt der darauf erzielte Ertrag. Allerdings hat die Fruchtbarkeit keine Auswirkung auf die Dauer der Anbauzeit. @PAuch bewässerte Farmen müssen auf urbarem Land errichtet werden, denn durch Bewässerung kann die Fruchtbarkeit des Landes zwar erhöht, unfruchtbares Land damit jedoch nicht zu fruchtbarem gemacht werden. @PDer Eintrag zum Thema @45Landwirtschaft enthält zusätzliche Informationen. @L@LDurch die Entwicklung der Bewässerungstechnologie konnten die alten Ägypter die Menge des landwirtschaftlich nutzbaren Landes vergrößern. Klicken Sie @154hier, um mehr über die Bewässerungstechnik zu erfahren."
        }
    }
    
    message_building_weaver {
        id: 60,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Weberei",
        }
        content {
            text: "Weber verarbeiten Flachs zu Leinen. Flachs kann auf @91Flachsfarmen angebaut oder über @47Handelspartner importiert werden. Webereien benötigen sowohl eine Straßenanbindung als auch Arbeitskräfte. In Webereien kann eine kleine Menge an Flachs aufbewahrt werden, so dass diese Betriebe weiterarbeiten können, auch wenn kleinere Engpässe in der Versorgung entstehen. @PLeinen ist in jeder Stadt eine wichtige Ware. Ohne Leinen können keine Einbalsamierungen ausgeführt werden, und @66Einbalsamierungshäuser benötigen einen Leinenvorrat, um zu funktionieren. Außerdem bewahren die Bürger gerne eine gewisse Menge an Leinen in ihren Wohnungen auf, um daraus Kleidung herstellen zu können.  @L@LWenn Sie @398hier klicken, erfahren Sie mehr über die Bedeutung von Leinen im alten Ägypten."
        }
    }
    
    message_building_water_supply {
        id: 61,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Zisternen",
        }
        content {
            text: "Zisternen und Wasserträger versorgen die Viertel der Stadt mit sauberem @44Trinkwasser. So ziemlich die erste Forderung, die Ihre Bürger stellen, wenn sie ihre @56Wohnungen verbessern wollen, ist eine Wasserversorgung durch eine Zisterne. @PZisternen benötigen sowohl eine Straßenanbindung als auch Arbeitskräfte und müssen auf Grasland gebaut werden, das ein sicheres Indiz für das Vorhandensein von Grundwasser ist. In der Wüste können keine Zisternen errichtet werden. @PSobald eine Zisterne ihre Funktion aufnehmen kann, wird ein Wasserträger entsandt. Dieser marschiert durch die Wohngebiete und bringt den Bewohnern der Häuser, an denen er vorbeigeht, sauberes Wasser. Es ist sinnvoll, von Zeit zu Zeit zu überprüfen, was die Wasserträger tun, um dafür zu sorgen, dass die Wohngebiete ausreichend mit sauberem Trinkwasser versorgt sind. In der @18Spezialkarte&Wasser sehen Sie, welche Häuser häufig von einem Wasserträger besucht werden. Wasserträger sind @42Fußgänger&ohne&Ziel. @PWasserträger arbeiten mehr, wenn ihre Zisterne verbessert wurde. Wenn die Attraktivität der Umgebung hoch genug ist, verbessern die Arbeitskräfte der Zisterne das Gebäude, und die Wasserträger sind häufiger in den umliegenden Vierteln unterwegs. @PNur Wohngebiete benötigen Wasser aus Zisternen, und Ihre Bürger wohnen gerne in der Nähe von Zisternen. (Weitere Informationen darüber, was ein Wohngebiet attraktiv macht, finden Sie im Eintrag über @56Attraktivität.)  @L@LKlicken Sie @156hier, um mehr über die Herausforderungen zu erfahren, die mit der Versorgung der Bevölkerung mit sauberem Trinkwasser einhergehen."
        }
    }

    message_building_well {
        id: 62,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Ziehbrunnen",
        }
        content {
            text: "Ein Ziehbrunnen ist die einfachste wasserbezogene Einrichtung. Er schafft für eine begrenzte Anzahl von Gebäuden Zugang zu relativ sauberem Trinkwasser. Zwar ist Brunnenwasser besser als kein Wasser, aber Zisternen sind eine sehr viel bessere Lösung. @PZisternen brauchen Straßenzugang und Arbeitskräfte, damit das Wasser in nahe gelegene Gebäude gebracht werden kann. Zisternen und Wasserträger können einen größeren Bereich der Stadt mit Wasser versorgen, als dies mit Ziehbrunnen möglich ist, und das Wasser ist deutlich sauberer als Brunnenwasser. Zisternen verringern außerdem das Risiko einer Malariaepidemie. @PSehen Sie auf der @18Spezialkarte&Wasser nach, welche Gebiete Zugang zu Wasser aus Ziehbrunnen haben. @L@LNäheres zum Thema Ziehbrunnen im alten Ägypten erfahren Sie @156hier."
        }
    }

    message_building_dentist {
        id: 63,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Zahnarztpraxis",
        }
        content {
            text: "Zahnärzte. @PSand ist in Ägypten fast überall, auch im Essen. Das ständige Kauen auf Sand schleift die Zähne schnell ab. Wohlhabendere Bürger möchten ihre Zähne in Ordnung halten und wenden sich an Zahnärzte, damit sie sich auch morgen noch strahlend zulächeln können. @PIn der @18Spezialkarte&Gesundheit sehen Sie, wie die Zahnärzte in der Stadt ihrer Arbeit nachgehen. @L@LKlicken Sie @158hier, wenn Sie mehr über die Rolle der Zahnärzte im alten Ägypten erfahren möchten."
        }
    }

    message_building_physician {
        id: 64,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Arztpraxis",
        }
        content {
            text: "Ärzte gehen von Arztpraxen aus durch die Wohngebiete und kümmern sich um die Gesundheit der Bevölkerung. @PArztpraxen benötigen sowohl eine Straßenanbindung als auch Arbeitskräfte. @PEin Besuch beim @26Aufseher&der&Gesundheit hilft Ihnen, den Umfang der ärztlichen Versorgung in der Stadt abzuschätzen. @L@LKlicken Sie @160hier, um mehr über die Medizin im alten Ägypten zu erfahren."
        }
    }

    message_building_apothecary {
        id: 65,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Apotheke",
        }
        content {
            text: "Kräuterkundige aus Apotheken verteilen in den Wohngebieten aus Tierfett hergestellte Insektenabwehrmittel. Dies hilft, das Malariarisiko einzudämmen.   @PApotheken benötigen sowohl eine Straßenanbindung als auch Arbeitskräfte. Auf der @18Spezialkarte&Gesundheit sehen Sie, was die Kräuterkundigen gerade tun. Sie sehen hier sämtliche Kräuterkundigen und Apotheken der Stadt und auch, wie gut der Zugang der Häuser zu den Diensten der Kräuterkundigen ist. @PWeitere Informationen hierzu bekommen Sie vom @26Aufseher&der&Gesundheit. @L@LKlicken Sie @159hier, um mehr über die Pharmazie im alten Ägypten zu erfahren."
        }
    }

    message_building_mortuary {
        id: 66,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Einbalsamierungshaus",
        }
        content {
            text: "In Einbalsamierungshäusern bereiten Einbalsamierer die Toten für ihre letzte Reise ins Jenseits vor. Die richtige Präparierung der Toten verbessert die allgemeine Gesundheitslage in der Stadt und verhindert Seuchen. Zum Einwickeln der Leiche verwenden Einbalsamierer Leinen, das entweder von Webern vor Ort hergestellt oder über einen Handelspartner importiert wird. @PZwar verlangen die Bürger Zugang zu Einbalsamierungshäusern, doch niemand wohnt gern in der Nähe eines solchen Gebäudes. Schließlich sind Einbalsamierungshäuser für ihre unangenehmen Gerüche berühmt-berüchtigt. @PAuf der @18Spezialkarte&Gesundheit sehen Sie, wo Einbalsamierungshäuser stehen, wie die Einbalsamierer sich um die Verblichenen kümmern und wie sie durch die Wohngebiete gehen. Der @26Aufseher&der&Gesundheit bietet wertvolle Informationen über Einbalsamierungsdienste in der Stadt. @L@LDie Einbalsamierung war ein wichtiger Bestandteil der altägyptischen Riten zur Vorbereitung auf das Leben nach dem Tod. Klicken Sie @161hier, um mehr über dieses alte Gewerbe zu erfahren."
        }
    }

    message_building_shrine_and_temple {
        id: 67,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Schreine und Tempel",
        }
        content {
            text: "Schreine. @PSchreine sind die einfachsten religiösen Gebäude, die Sie bauen können. Für sie ist keine Straßenanbindung erforderlich, allerdings dürfen sie maximal zwei Felder von einer Straße entfernt errichtet werden, um noch von Feuerwehrleuten und Architekten betreut werden zu können. Der einzige Zweck eines Schreins liegt in der Beschwichtigung der Gottheit, der er geweiht ist. Schreine haben zwar eine positive Wirkung auf die Attraktivität einer Wohngegend, bieten den Bürgern jedoch keinen Zugang zu Religion. Schreine beschäftigen keine Mitarbeiter.   @PTempel. @L@LTempel sind erheblich größer als Schreine, und in ihnen wird den Göttern mit Inbrunst gehuldigt. Wenn ein Tempel errichtet wird, müssen Sie ihn einem bestimmten Gott weihen. Sobald der Tempel ganz fertig gestellt und gottgefällig ist, tauchen Priester auf den Straßen auf und bieten den Bewohnern religiöse Dienstleistungen an.  @PTempelkomplexe. @L@LIn der Regel kann nur für den Schutzgott einer Stadt ein Tempelkomplex errichtet werden. Hin und wieder ist es jedoch auch möglich, einer lokalen Gottheit, die besonders wichtig ist, einen Tempelkomplex zu bauen. Eine Stadt kann nur einen Tempelkomplex beherbergen, daher sollten Sie es sich genau überlegen, bevor Sie einer lokalen Gottheit einen Komplex weihen. Der Schutzgott könnte ziemlich böse werden, und das bekäme die Stadt sofort zu spüren.  @L@LIm alten Ägypten drehte sich alles um die Religion. Wenn Sie @399hier klicken, erfahren Sie mehr über diesen wichtigen Aspekt der alten ägyptischen Kultur."
        }
    }

    message_building_scribal_school {
        id: 68,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Schreiberschule",
        }
        content {
            text: "Bildung ist ein Privileg der Reichen. Sie verrichten keine körperliche Arbeit mehr und wollen ihre Kinder niemals den Schrecken der harten, schweißtreibenden Arbeit in der brütenden Hitze aussetzen. Um dieses Ziel zu erreichen, wünschen sich wohlhabende Schreiber in der Nähe ihrer Wohnungen gelegene Schreiberschulen für ihre Kinder.  @PSobald eine Schreiberschule mit voller Belegschaft arbeitet und einen Papyrusvorrat hat, gehen Lehrer durch die Wohngebiete der Stadt und bilden die Jugendlichen der wohlhabenden Haushalte aus. Wann immer ein Lehrer die Schreiberschule verlässt, nimmt er etwas Papyrus mit, damit die Schüler ihre Hieroglyphen üben können. Achten Sie daher darauf, den Papyrusvorrat der Schreiberschule regelmäßig aufzufüllen, damit die Kinder das Schreiben erlernen können.  @L@LViele alte Ägypter betrachteten Bildung als Weg zu einer erfolgreichen Zukunft. Klicken Sie @163hier, um mehr über diese ägyptische Institution zu erfahren."
        }
    }

    message_building_sun_temple {
        id: 69,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Sonnentempel",
        }
        content {
            text: "Sonnentempel ehren besonders den Sonnenkult, der den meisten Pharaonen sehr ans Herz gewachsen ist. @PFür den Bau eines Sonnentempels benötigen Sie @95Sandstein und @94Holz sowie die Dienste der @363Zimmermannsgilde, der @363Steinmetzgilde und der Arbeiter aus dem @8Arbeiterlager. @PDer erste Teil eines Sonnentempels, der errichtet wird, ist ein Obelisk aus Sandstein. Bevor der Obelisk gebaut werden kann, müssen ausreichende Mengen Sandstein in den @4Warenlagern der Stadt vorrätig sein. Sobald Sie genug Sandstein beisammen haben, können Sie den Sonnentempel platzieren. Wählen Sie in der Liste 'Religiöse Einrichtungen: Monumente' die Option 'Sonnentempel' an, und wählen Sie dann einen Standort. Wenn Sie einen geeigneten Standort gewählt haben, erscheint ein grüner Grundriss des Monuments. Falls jedoch auch nur ein Teil dieses Grundrisses als rote Raute erscheint, befindet sich auf dem gewählten Terrain etwas, das den Bau des Monuments an dieser Stelle verhindert. Klicken Sie, um mit dem Bau des Sandsteinobelisken im Sonnentempel zu beginnen.  @PNach dem Aufstellen des Obelisken bauen Zimmerleute ein Gerüst um den Obelisken herum. Dann dekorieren Steinmetze die Seiten des Sandsteinobelisken. Wenn sie mit dem Obelisken fertig sind, fangen sie mit der Arbeit an den übrigen Teilen des Sonnentempels an. Zunächst werden ein Vorplatz und eine Mauer errichtet. Wenn die Mauer fertig ist, wird der Vortempel errichtet. Hierzu benötigen die Steinmetze mehrere Schlittenladungen voll Sandstein, die von Bauern herbeigeschafft werden müssen. Während der Arbeit an Vortempel, Mauer und Vorplatz verblenden die Steinmetze die Freiräume zwischen den Mauern mit dekorativen Fliesen. @PSobald der Vortempel fertig ist und alle Fliesen gelegt sind, ist der Sonnentempel fertig. @PStatten Sie dem @369Vorarbeiter&des&Baus einen Besuch ab, um einen Statusbericht betreffs der Bauarbeiten abzurufen. Auch ein Besuch beim @373Aufseher&der&Monumente kann recht hilfreich sein. @L@LKlicken Sie @396hier, wenn Sie an Informationen über die Geschichte der Sonnentempel und anderer Monumente interessiert sind."
        }
    }

    message_building_library {
        id: 70,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Bibliothek",
        }
        content {
            text: "Bibliotheken entsenden Bibliothekare in die wohlhabenderen Wohngebiete der Stadt. Der benötigte Papyrus für den Aufbau der Bibliothek bildet den dauerhaften Grundstock. Allerdings brauchen Bibliothekare zusätzliche Papyrusrollen, um literarische Werke für die Bürger zu kopieren, die diese zu Hause lesen möchten. Außerdem wird weiterer Papyrus benötigt, um die Sammlung zu erhalten. Daher muss auch der Vorrat einer Bibliothek an Papyrus ständig aufgefüllt werden, um sie funktionsfähig zu halten.  @PUm sich über die Anzahl der Bibliotheken in der Stadt auf dem Laufenden zu halten, statten Sie dem @27Aufseher&des&Wissens einen Besuch ab. Die Standorte der Bibliotheken finden Sie in der @18Spezialkarte&Bildung. In dieser Spezialkarte sehen Sie die Bibliotheken und können den Bibliothekaren bei ihrer täglichen Arbeit zusehen. @L@LWeitere Informationen zum Thema Literatur im alten Ägypten erhalten Sie, wenn Sie @164hier klicken."
        }
    }

    message_building_booth {
        id: 71,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Bühne",
        }
        content {
            text: "Die Bühne ist die kleinste Unterhaltungseinrichtung. Sie bietet nur wenig Platz, sodass auf ihr ausschließlich Jongleure auftreten können. Bühnen haben positive Auswirkungen auf die umliegenden Wohngebiete. Jongleure werden in @75Jonglierschulen ausgebildet, und sie können auch in @72Musikpavillons und @73Pavillons auftreten. @PHäuser brauchen Zugang zu Unterhaltung, um sich zu @56entwickeln, und von vorbeigehenden Jongleuren profitieren alle Häuser. Eine Bühne erhöht darüber hinaus die Attraktivität eines Viertels. Aktive Bühnen tragen außerdem zur @35Kultur-Wertung der Stadt bei.  @PBei einem Besuch beim @28Aufseher&der&Unterhaltung erfahren Sie, wie viele Jongleure in der Stadt arbeiten. In der @18Spezialkarte&Unterhaltung sehen Sie, wo die Jongleure auftreten, und Sie können sie bei ihren Wanderungen durch die Stadt beobachten. @L@LDie alten Ägypter waren die Pioniere auf dem Gebiet der Jonglierkunst. Klicken Sie @169hier, um mehr darüber zu erfahren."
        }
    }

    message_building_bandstand {
        id: 72,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Musikpavillon",
        }
        content {
            text: "Musikpavillons sind mittelgroße Einrichtungen mit zwei Bühnen: einer Bühne für Jongleure und einer für Musikerinnen. Die Jongleurbühne befindet sich in einer Ecke, die Musikbühne in einer anderen.  @PMusikpavillons müssen auf einer Straßengabelung oder auf einer Straßenkreuzung errichtet werden. Sie brauchen eigene Arbeitskräfte, die sich um die Künstler kümmern, sowie ausgebildete Jongleure und Musikerinnen. Künstler werden in speziellen @75Ausbildungsstätten ausgebildet. @PHäuser brauchen Zugang zu Unterhaltung, um sich zu @56entwickeln, und von Jongleuren und Musikerinnen profitieren alle Häuser, an denen diese Künstler vorüberkommen. Ein Musikpavillon erhöht darüber hinaus die Attraktivität eines Viertels. Aktive Musikpavillons tragen außerdem zur @35Kultur-Wertung der Stadt bei.  @PBei einem Besuch beim @28Aufseher&der&Unterhaltung erfahren Sie, wie viele Jongleure und Musikerinnen in der Stadt arbeiten. In der @18Spezialkarte&Unterhaltung sehen Sie, wo die Künstler auftreten, und können sie bei ihren Wanderungen durch die Stadt beobachten. @L@LDie alten Ägypter waren ausgezeichnete Musiker. Klicken Sie @170hier, um mehr darüber zu erfahren. Klicken Sie hier, um mehr über die @169Jonglierkunst im alten Ägypten zu erfahren."
        }
    }

    message_building_pavilion {
        id: 73,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Pavillon",
        }
        content {
            text: "Ein Pavillon, die größte Unterhaltungseinrichtung, umfasst drei Bühnen: Eine Bühne für Jongleuraufführungen, eine für Konzerte und eine für Tanzdarbietungen. Kein Bürger wird sich darüber beschweren, wenn er neben einem Pavillon lebt! @PPavillons müssen auf einer Straßengabelung oder auf einer Straßenkreuzung errichtet werden. Sie brauchen eigene Arbeitskräfte, die sich um die Künstler kümmern, sowie ausgebildete Jongleure, Musikerinnen und Tänzerinnen. Künstler werden in speziellen @75Ausbildungsstätten ausgebildet. @PHäuser brauchen Zugang zu @49Unterhaltung, um sich zu @56entwickeln, und von vorbeikommenden Künstlern profitieren alle Häuser. Ein Pavillon erhöht darüber hinaus die Attraktivität eines Viertels. Aktive Pavillons tragen außerdem zur @35Kultur-Wertung der Stadt bei.  @PBei einem Besuch beim @28Aufseher&der&Unterhaltung erfahren Sie, wie viele Jongleure, Musikerinnen und Jongleure in der Stadt arbeiten. In der @18Spezialkarte&Unterhaltung sehen Sie, wo die Künstler auftreten, und können sie bei ihren Wanderungen durch die Stadt beobachten. @L@LKlicken Sie @171hier, und lassen Sie sich von den modernsten Tänzen des alten Ägypten mitreißen. Klicken Sie @170hier, um mehr über die damalige Musik, und @169hier, um etwas über die Jonglierkunst zu erfahren."
        }
    }

    message_building_senet_house {
        id: 74,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Senet-Haus",
        }
        content {
            text: "In Senet-Häusern kann man sich entspannt dem Senet-Spiel widmen. Das Senet-Spiel symbolisiert die Reise ins Jenseits. Mit schäumenden Bierkrügen vor sich und in gemütlicher Runde halten es die Bürger hier stundenlang aus und vertreiben sich die Zeit mit ein paar freundschaftlichen Partien Senet.  @PEin Senet-Haus braucht außer Arbeitern und Straßenanbindung einen Vorrat an @96Bier für seine Gäste. @PBei einem Besuch beim @28Aufseher&der&Unterhaltung erfahren Sie, wie viele Senet-Häuser in der Stadt aktiv sind. Sehen Sie auf der @18Spezialkarte&Unterhaltung nach, welche Gebiete Zugang zu einem Senet-Haus haben. @PIn allzu großer Nähe von Senet-Häusern leben die Bürger allerdings doch nicht sehr gern. Klicken Sie @56hier, um mehr zum Thema 'Attraktivität' zu erfahren. Die Gäste solcher Einrichtungen sind oft laut und machen Rabatz - vor allem jene, die gerade bei einem Senet-Spiel einen hohen Einsatz verloren haben. @L@LSenet war mehr als nur ein Spiel. Klicken Sie @172hier, um mehr darüber zu erfahren."
        }
    }

    message_building_trading_centers {
        id: 75,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Ausbildungsstätten",
        }
        content {
            text: "Ausbildungsstätten @L@LIhre Bürger erwarten qualitativ hochwertige Unterhaltung. Ausbildungsstätten sorgen dafür, dass die Darbietungen von Profis und nicht von Amateuren geboten werden. Für jede Kunstgattung gibt es eine spezielle Ausbildungsstätte: Angehende Jongleure üben in einer Jonglierschule, Musikerinnen besuchen das Konservatorium, und Tänzerinnen feilen in Tanzschulen an ihren Fähigkeiten.   @L@LSowohl Konservatorien als auch Tanzschulen haben negative Auswirkungen auf die Attraktivität eines Wohngebiets. Der Lärm, der aus einem Konservatorium dringt, erfreut die Ohren der Anwohner ganz und gar nicht, und Tänzer haben die Angewohnheit, zu den seltsamsten Zeiten ein- und auszugehen. In der Nähe von Jonglierschulen lebt man dagegen gerne, denn Jongleuren, die noch in der Ausbildung sind, unterlaufen in der Regel äußerst amüsante Fehler.   @L@LWurden keine neuen Künstler ausgebildet, bleibt die Unterhaltungseinrichtung ungenutzt und bietet den Bürgern Ihrer Stadt keine Ablenkung. @PIn der Nähe einer Jonglierschule leben die Leute recht gern. Ihre lustigen Verrenkungen beim Üben sind fast genauso amüsant wie ihre öffentlichen Darbietungen. In der Nähe von Tanzschulen oder Konservatorien wohnen 'anständige' Bürger jedoch nicht so gern. Die Schüler und Schülerinnen gehen dort zu allen möglichen Zeiten ein und aus, und übende Musiker sind alles andere als ein Ohrenschmaus. @PUm zu sehen, wie die Künstler von den Schulen in die Unterhaltungseinrichtungen gehen, benutzen Sie die @18Spezialkarte&Unterhaltung. @L@LDie alten Ägypter kannten viele Arten der Unterhaltung. Klicken Sie @165hier, um mehr darüber zu erfahren."
        }
    }

    message_building_courthouse {
        id: 76,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Gericht",
        }
        content {
            text: "Gerichte sind recht vielseitige städtische Einrichtungen. Sie verringern nicht nur die @36Kriminalität in den Wohngegenden, sondern hier wird auch ein Teil der Stadtkasse aufbewahrt. Bürger freuen sich über die Sicherheit, die ihnen Gerichte bescheren, und leben gerne in der Nähe solcher imposanter Gebäude. @PGerichte benötigen eine Straßenanbindung und Mitarbeiter, bevor sie Magistrate auf die Straßen der Stadt entsenden können. Die Gegenwart eines Magistrats verringert in einem Wohngebiet die Wahrscheinlichkeit von Kriminalität. Magistrate haben lediglich präventive Funktion - ist ein Verbrecher erst einmal auf Raubzug, kann der Magistrat nichts dagegen unternehmen. @PIn den Gerichtsgebäuden wird din Teil der städtischen @48Finanzen aufbewahrt. Wie viel Geld in jedem Gerichtsgebäude aufbewahrt wird, kann von Ihnen jedoch nicht festgelegt werden. Hierfür haben Sie den @30Aufseher&der&Finanzen - er berechnet die geeignete Summe.  @L@LDie Gerichte im alten Ägypten hatten stets viel zu tun. Klicken Sie @183hier, um mehr über die Gerichtsbarkeit im alten Ägypten zu erfahren."
        }
    }
    
    message_building_palace {
        id: 77,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Palast",
        }
        content {
            text: "Paläste @L@LEin besonders majestätisches Gebäude der Stadt ist der Palast. Dieses Gebäude bringt die Macht Ägyptens eindrucksvoll zum Ausdruck.   @L@LEine Stadt kann nur einen Palast haben, und er ist der Regierungssitz. Ohne diesen kann die Stadt keine Steuern eintreiben. Der Palast entsendet jedoch keine eigenen Steuereintreiber. Um Steuern einzutreiben, müssen Sie ein Büro für den Steuereintreiber bauen.  @L@LDer Palast braucht einen Zugang zu Straßen und Arbeitskräften; außerdem muss sich mindestens ein Teil des Palasts auf grasbewachsenem Gelände befinden, damit er Grundwasserversorgung hat. Hochrangige Beamte aus Ägypten und dem Ausland übernachten im Palast, wenn sie auf Besuch in der Stadt weilen.  @L@LDer Palast bietet Ihnen auch einen schnellen Überblick über Ihre Wertungen. Wenn Sie den Cursor auf das Gebäude schieben, erscheint ein Fenster, in dem Ihre Wertungen, der Steuersatz und die Arbeitslosenquote angezeigt werden.   @L@LSie können auch den Steuersatz der Stadt durch Infoklicks auf den Palast festlegen. Im Popup-Fenster ist der Steuersatz zu sehen. Klicken Sie auf die Buttons rechts neben dem Steuersatz, um ihn zu erhöhen oder zu senken.  @L@LWenn die Stadt das Glück hat, Goldminen in der Nähe zu haben, nimmt der Palast Golderz an, um es in Deben umzuwandeln. Paläste gibt es in drei Größen: Dorfpalast, Kleinstadtpalast und Großstadtpalast. In jeder Stadt ist nur eine Palastgröße verfügbar. Diese richtet sich nach dem von Ihnen erreichten Rang. @L@LKlicken Sie hier, um mehr über die @174Regierung und die Bürokratie im alten Ägypten zu erfahren."
        }
    }

    message_building_mansion {
        id: 78,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Wohnsitz",
        }
        content {
            text: "Der Wohnsitz muss eine Straßenanbindung besitzen. Arbeitskräfte werden nicht benötigt, aber da Sie hier wohnen, muss das Gebäude auf Grasland gebaut werden, damit die Versorgung mit Grundwasser gewährleistet ist. Es reicht, wenn zumindest ein Teil des Wohnsitzes auf grünem Gras steht.  @L@LAufgrund der Bedeutung Ihrer Familie dürfen Sie sich einen Wohnsitz mit Geldern der Stadtkasse bauen. Ihre Residenz ist ein großartiges Gebäude, und die Nachbarn gehen mit stolzgeschwellter Brust an Ihrem Haus vorbei. Ihre Anstrengungen beim Aufbau einer großen ägyptischen Stadt bleiben nicht unbelohnt. Die Höhe des Gehalts, das man Ihnen zugesteht, wird anhand Ihres Rangs berechnet. Die Residenz ist nicht nur ein Ort zum Ausruhen, hier werden auch die Ersparnisse der Familie aufbewahrt. Um ein Gehalt beziehen zu können, müssen Sie zunächst einen Wohnsitz errichten. Solange Sie einen Wohnsitz haben, können Sie ein Einkommen beziehen. Wenn Sie der Meinung sind, dass Ihre Dienste mehr (oder weniger) wert sind, als Sie erhalten, können Sie Ihr Gehalt entsprechend anpassen. Denken Sie aber daran, dass es nicht alle Leute im Königreich gerne sehen, wenn Sie sich ein zu üppiges Salär gönnen. Sie werden Ihre Ergebenheit dem Königreich gegenüber in Frage stellen, und Ihre Königreich-Wertung leidet möglicherweise darunter.   @L@LNichts ist besser für den guten Ruf im Königreich, als eine blühende Stadt zu schaffen, die gewinnbringend wirtschaftet. Natürlich stehen jene, die Ägypten mit Geschenken verwöhnen, in hohem Ansehen. Seien Sie jedoch gewarnt, dass sich bei den Empfängern schnell ein Gewöhnungseffekt einstellen kann, und die Geschenke dann jedes Mal üppiger und wertvoller ausfallen müssen. Und wenn das nicht der Fall ist, könnte man denken, Sie wären geizig, was sich wiederum negativ auf Ihr Ansehen auswirken könnte. @L@LJe bedeutsamer Ihre Familie wird, desto größer ist der Wohnsitz, den Sie bauen können. Es gibt Persönliche Wohnsitze, Familienwohnsitze und Dynastiewohnsitze.  @L@LPharaonen leben in riesigen Palästen, neben denen sich die Häuser der arbeitenden Bevölkerung wie Ameisenhügel ausmachen. Klicken Sie @175hier, um mehr über diese beeindruckenden Residenzen zu erfahren."
        }
    }
    
    message_building_garden_plaze_statue {
        id: 79,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Garten, Platz und Statue",
        }
        content {
            text: "Verschönerung @L@LGanz gleich, wie viele Waren und Dienstleistungen eine Stadt bietet - die Bürger werden nicht das Gefühl haben, in einer tollen Stadt zu wohnen, wenn ihre Umgebung nicht attraktiv genug ist. Verschönernde Einrichtungen verleihen einer Stadt Charakter und geben den Bürgern das Gefühl, dass sie für etwas Sinnvolles arbeiten. Außerdem hat dies positive Auswirkungen auf die Attraktivität der Wohnviertel. Gärten Gärten bieten Ihren Bürgern einen Ort zum Entspannen, und im Schatten üppiger Pflanzen finden sie Schutz vor der heißen ägyptischen Sonne. Alle Bürger haben gerne Gärten in der Nähe - manche verlangen sogar danach. @L@LUm einen Garten zu planen, wählen Sie erst den Button 'Öffentliche Einrichtungen' und dann unter dem Menüpunkt 'Verschönerung' die Option 'Gärten' an. Gärten sind umso beeindruckender, je mehr Platz Sie dafür zur Verfügung stellen. Bürger mögen zwar auch kleine Gärten, große sind ihnen aber noch lieber. Gärten benötigen keine Straßenanbindung und können weder einstürzen noch in Brand geraten. Fußgänger, die nicht auf Straßen bleiben müssen, wie z.B. Feuerwehrleute auf dem Weg zu einem Brand, können durch Gärten gehen.  @L@LPlätze @L@LPlätze sind bunt gepflasterte Straßen und können nur auf Straßen eingerichtet werden, die bereits von Ihren Bürgern befestigt wurden.  @L@LUm sie zu bauen, klicken Sie in der Liste 'Öffentliche Einrichtungen: Verschönerung' auf den Button 'Plätze'. Verschönerungsliste. Klicken Sie dann auf die gepflasterte Straße. Plätze können Sie Stückchen für Stückchen einrichten, oder indem Sie die Maus mit gedrückter Maustaste auf einer größeren Straße entlang ziehen. @L@LPlätze beeinflussen die Kapazität der Straße und die Geschwindigkeit von Fußgängern nicht, und sie benötigen auch keine Arbeitskräfte.  @L@LStatuen @L@LStatuen erinnern an all das, was einen Ägypter mit Stolz erfüllt.  @L@LStatuen gibt es in drei Größen: Klein, mittel und groß. Für jede Größe gibt es zwei Optionen. Nach Auswahl der gewünschten Größe platzieren Sie den Mauszeiger auf der gewählten Position und drücken die R-Taste. Es erscheinen vier sich drehende Statuen. Halten Sie die Taste gedrückt, bis die gewünschte Art von Statue in der gewünschten Ausrichtung erscheint. Klicken Sie dann mit der Maustaste, um die Statue zu platzieren.  @L@LJe größer die Statue, desto größer ihre Wirkung auf die Attraktivität. Statuen benötigen keine Straßenanbindung und können weder einstürzen noch in Brand geraten."
        }
    }
    
    message_building_tax_collector {
        id: 80,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Steuereintreiberbüro",
        }
        content {
            text: "Steuern und Geld @L@LIst der Palast errichtet, kann die Stadt anfangen, Steuern einzutreiben. @L@LWenn Ihre Stadt noch jung ist und die Gewerbestätten noch in den Kinderschuhen stecken, sind es die Steuern, die die Stadt vor dem Bankrott bewahren. Aber auch wenn die Einnahmen aus dem Handel zunehmen, kann auf das Erheben von Steuern als wichtigem Zusatzeinkommen nur schlecht verzichtet werden. @L@LDer Steuersatz @L@LStandardmäßig ist der Steuersatz auf 9 Prozent eingestellt. Um dies zu ändern, infoklicken Sie auf den Palast oder statten dem Aufseher der Finanzen einen Besuch ab. Der Aufseher der Finanzen versorgt Sie mit vielen Informationen, die Ihnen bei der Festlegung des Steuersatzes helfen können. Außer über den Steuersatz selbst informiert er Sie über die Steuereinnahmen und über den Prozentsatz der Bevölkerung, der derzeit steuerlich erfasst ist (d.h. von Steuereintreibern besucht wird). Er weiß auch, wie viel mehr die Stadt einnehmen würde, wenn jeder Bürger steuerlich erfasst wäre. @L@LDamit haben Sie genügend Informationen an der Hand, um zu entscheiden, was Sie hinsichtlich des Steuersatzes der Stadt unternehmen wollen. Nimmt die Stadt nicht genug Steuern ein, sollten Sie vielleicht mehr Steuereintreiberbüros errichten.  @L@LEs kann sinnvoll sein, die Steuern zu erhöhen, wenn die Stadt verschuldet ist und schnell Geld braucht. Allerdings ist dies keine dauerhafte Lösung. Ein hoher Steuersatz hat äußerst negative Auswirkungen auf die Stimmung in der Stadt, und die Bürger akzeptieren hohe Steuern höchstens für kurze Zeit. Viele verlassen lieber die Stadt, wodurch ein Mangel an Arbeitskräften entsteht. Seien Sie also vorsichtig, wenn Sie den Steuersatz erhöhen, und haben Sie stets ein Auge auf die Reaktionen Ihrer Bürger. @L@LDas Senken von Steuern dagegen erfreut Ihre Bürger. Dann werden sie Sie als weisen, gütigen Herrscher loben.  Steuereintreiber Ihre Bürger wissen zwar, dass sie Steuern bezahlen müssen, allerdings muss man dem in der Praxis meist etwas nachhelfen. Aus diesem Grund gehen Steuereintreiber von Tür zu Tür, beurteilen, wie viele Steuern jeder Haushalt zahlen muss, und sorgen dafür, dass diese auch entrichtet werden. @L@LSteuereintreiber arbeiten von Steuereintreiberbüros aus. Um funktionieren zu können, benötigen diese Gebäude eine Straßenanbindung und Arbeitskräfte. Bevor Sie Steuereintreiberbüros bauen können, braucht die Stadt einen Palast. Wird der Palast zerstört, bleibt das Büro des Steuereintreibers bestehen, allerdings werden keine Steuereintreiber mehr ausgeschickt. @L@LErrichten Sie Steuereintreiberbüros überall, wo Häuser sind, um zu gewährleisten, dass möglichst alle Bürger steuerlich erfasst werden. @PDas Festlegen eines Steuersatzes ist nicht ganz einfach. Hier gilt es, den Bedarf der Stadtkasse mit der Geduld der Bürger in Einklang zu bringen. Lange sind die Bürger nämlich nicht bereit, hohe Steuern zu zahlen, sonst verlassen sie lieber kurzerhand die Stadt und suchen nach einer besseren bzw. billigeren Heimat. Entrichtet ein Teil der Bevölkerung hohe Steuern und ein anderer Teil gar keine, sinkt die @39Stimmung&in&der&Stadt rapide ab. Das könnte zu @36Verbrechen führen. Statten Sie dem @30Aufseher&der&Finanzen einen Besuch ab, und lesen Sie unter @48Finanzen nach, um Ratschläge zur Festlegung des Steuersatzes zu erhalten. @L@LIm alten Ägypten zahlte man dem Pharao Steuern, um die Regierung zu finanzieren. Näheres zu den Steuern im alten Ägypten erfahren Sie @173hier."
        }
    }

    message_building_architect_post {
        id: 81,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Architektenbüro",
        }
        content {
            text: "Große Gebäude, wie z.B. Warenlager, Minen, Silos, Tempel und Tempelkomplexe, sind einsturzgefährdet. Architekten, die durch die Straßen patrouillieren, beheben strukturelle Schwächen, bevor es zu einer Katastrophe kommt. Architekten haben ihr Quartier in Architektenbüros. Wenn Sie auf ein solches Gebäude infoklicken, erfahren Sie, wie viele Mitarbeiter es hat. Sobald das Gebäude funktionsfähig ist, fangen Architekten an, Gebäude auf Schäden zu überprüfen.  @POb ein bestimmtes Gebäude Gefahr läuft, einzustürzen, können Sie in der @18Spezialkarte&Risiken:&Schäden sehen. Wenn Sie feststellen, dass ein bestimmtes Gebäude oder eine bestimmte Ansammlung von Gebäuden stark einsturzgefährdet ist, ist es möglicherweise sinnvoll, ein Architektenbüro in der Nähe zu errichten, um zu gewährleisten, dass ein Architekt darüber wacht. @PEin Zusammenbruch kann katastrophale Folgen haben. Bricht ein @3Silo oder ein @4Warenlager zusammen, gehen sämtliche dort gelagerten Lebensmittel und Waren verloren."
        }
    }

    message_building_whipwright {
        id: 82,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Werft",
        }
        content {
            text: "Kriegs- und Transportschiffe werden von Schiffbauern in Werften hergestellt. Um mit dem Bau eines mächtigen Kriegsschiffs zu beginnen, sollten Sie zunächst dafür sorgen, dass in der Stadt eine Werft betriebsbereit ist. Eine Werft können Sie bauen, indem Sie auf den Button 'Gewerbliche Gebäude' klicken und dort 'Werft' anwählen. Ist die Werft erst einmal betriebsbereit und hat sie einen Vorrat an Holz, müssen die Häfen gebaut werden, in denen die Schiffe vor Anker liegen. Der Bau von Häfen und deren Versorgung mit Arbeitskräften ist das Signal für die Werft, mit dem Schiffbau anzufangen.   @L@LUm einen Hafen zu bauen, klicken Sie auf den Button 'Militäreinrichtungen' und wählen in der angezeigten Liste einen Kriegshafen oder einen Transporthafen aus. So wie alle am Ufer liegenden Gebäude müssen auch Häfen an einem geraden Küstenabschnitt gebaut werden. Schiffe können nicht durch schmale Kanäle fahren, achten Sie also darauf, dass das fertige Schiff unbehindert zum Hafen segeln kann. Außerdem benötigt ein Hafen eine Straßenanbindung und Arbeitskräfte. Diese Mitarbeiter sind nicht identisch mit der Besatzung des Schiffs, die aus einer anderen Quelle rekrutiert wird und die weder die Bevölkerung noch die Zahl der Arbeitskräfte in der Stadt verringert.  @PWerften produzieren viel Lärm, daher möchte niemand in ihrer Nähe leben. @L@LIm alten Ägypten wurden Schiffe in vielerlei Größen und Formen gebaut. Klicken Sie @179hier, um mehr über dieses alte Gewerbe zu erfahren."
        }
    }
    
    message_building_dock {
        id: 83,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Dock",
        }
        content {
            text: "Einige @47Handelspartner der Stadt müssen Wasserwege in Anspruch nehmen. Große Handelsschiffe fahren den Nil hinab. Doch sie können Ihrer Stadt erst dann etwas nützen, wenn sie die Möglichkeit zum Anlegen haben. Bauen Sie ein Dock an der Küste, damit diese Schiffe anlegen können. Bauen Sie das Dock unbedingt am Nil oder an einem Meeresufer, an dem Handelsschiffe unterwegs sind. An einem Dock, das an einem schmalen Seitenkanal oder einem Gewässer ohne Außenverbindung liegt, können keine Handelsschiffe anlegen. @PUm funktionsfähig zu sein, benötigen Docks eine Straßenanbindung und Arbeitskräfte. Hat ein Handelsschiff einmal angelegt, wird seine Ladung von den Karrenschiebern des Docks gelöscht und in die @4Warenlager der Stadt gebracht. Dort werden die Exportwaren der Stadt für diesen Handelspartner aufgeladen und zum Dock gebracht. Es ist zweckmäßig, ein Warenlager in der Nähe des Docks zu errichten, damit die Karrenschieber keinen so langen Weg zurücklegen müssen. @PDocks haben einen negativen Einfluss auf die @56Attraktivität eines Gebiets. @L@LNäheres zum Thema 'Handel' im alten Ägypten erfahren Sie @177hier."
        }
    }

    message_building_fishing_wharf {
        id: 84,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Fischerhafen",
        }
        content {
            text: "Enthält ein Gewässer Fische, sieht man sie von Zeit zu Zeit aus dem Wasser springen. Ihre Fischer können diese Fische fangen und das Nahrungsmittelangebot auf diese Weise erweitern. Um Fische zu fangen, benötigt die Stadt ein oder mehrere Fischerboote. @PFischerboote liegen in Fischerhäfen vor Anker. Fischerhäfen müssen an geraden Küstenabschnitten errichtet werden und zur Hälfte ins Wasser hineinragen, damit die Schiffe Zugang zu ihnen haben. Achten Sie darauf, dass die Fischerboote das Gewässer um den Fischerhafen befahren können. Wenn Sie den Fischerhafen in einem schmalen Kanal bauen, ist er für Fischerboote nicht erreichbar. Es kann alle Ihre Bemühungen beim Aufbau einer Fischwirtschaft sabotieren, wenn auf Werften immer wieder Fischerboote gebaut werden, die den Zielhafen nicht erreichen und dann sofort versenkt werden.  @PWenn in der Stadt eine funktionierende @82Werft vorhanden ist, signalisiert der Bau eines Fischerhafens den dortigen Schiffbauern, dass sie ein Fischerboot bauen sollen. Werften brauchen kein Rohmaterial, um ein Fischerboot zu bauen. @PDie Fischbestände sind zwar begrenzt, sie können jedoch nicht völlig abgefischt werden. Würde aber eine große Bevölkerung versuchen, sich nur von Fisch zu ernähren, gäbe es doch Probleme. @PFischerhäfen sind recht anrüchige Einrichtungen und somit keine sehr @56attraktiven Nachbarn. @L@LKlicken Sie @186hier, um mehr über die Fischerei im alten Ägypten zu erfahren."
        }
    }

    message_building_defensive_structures {
        id: 85,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Verteidigungsanlagen",
        }
        content {
            text: "Das Land wirkt mit seinen fruchtbaren Farmen, herrlichen Tempeln und luxuriösen Gärten recht idyllisch, aber all dies kann sich schnell ändern, wenn es zum Krieg kommt. Häufig liegt die Gefahr einer Invasion in der Luft. Aber auch Schlachten, die weit weg von den Grenzen der Stadt geführt werden, haben direkte Auswirkungen auf die Bevölkerung. Angriffe können von allen Seiten kommen, über den Landweg oder über das Wasser.  @L@LEs gibt viele Methoden, die Stadt gegen Angriffe zu verteidigen. Sie können starke Mauern um die Stadt herum errichten und so jene abwehren, die in böser Absicht kommen. Entschlossene Invasoren werden mit der Zeit aber auch die dickste Stadtmauer durchbrechen, daher sollten Sie in der Stadt eine vielseitige, starke Armee unterhalten, um solche Katastrophen zu verhindern.  @37Armee und @356Seestreitkräfte verteidigen die Stadt, wenn Feinde ihre Grenzen überschritten haben. Verteidigungsanlagen können verhindern, dass Feinde überhaupt ihren Fuß in die Stadt setzen. @L@LMauern @LDie wichtigste Verteidigungsanlage ist die Mauer. Mauern bauen Sie, indem Sie sie in der Liste 'Militärgebäude: Verteidigungsanlagen' anwählen. Klicken Sie mit der Maustaste, und ziehen Sie den Mauszeiger mit gedrückter Taste an den gewünschten Ort, um große Mauerabschnitte auf einmal zu errichten. @PEinfache Mauern können Feinde nur kurz aufhalten. Um die Stadt besser zu schützen, sollten die Mauern mehrere Schichten dick sein. Solche Mauern stellen feindliche Soldaten vor sehr viel größere Probleme. @PMauern werden aus jeder gewöhnlichen Steinart gebaut, über die die Gegend verfügt, daher muss für sie kein Stein in Steinbrüchen abgebaut oder importiert werden. Trotzdem sind Mauern für den Bauherrn eine teure Angelegenheit, daher sollten Sie sich sorgfältig überlegen, welches Gebiet sie damit umgeben wollen. @PMauern benötigen keine Straßenanbindung und sind unattraktive Nachbarn. @L@LTürme @LDurch Türme werden die Verteidigungsmauern etwas offensiver. Sie werden mit Wächtern bemannt, die am @88Drillplatz dazu ausgebildet werden, Wurfspeere auf jeden Feind zu schleudern, der mutig oder tollkühn genug ist, in Wurfweite zu kommen. @PVorausgesetzt, die Mauer bietet genug Platz, um darauf gehen zu können, werden darüber hinaus von Türmen Wächter entsandt, die überall auf der Mauer patrouillieren und herannahende Feinde mit einem Pfeilregen begrüßen. @PTürme können nur auf Mauern mit doppelter Stärke gebaut werden. Außerdem benötigen sie eine Straßenanbindung, Mitarbeiter und Wachen. Diese kommen vom Drillplatz. Bauen Sie die Mauern aber nicht so dick, dass die Turmwächter nicht mehr darüberschießen können! @L@LStadttore @PSo beruhigend Mauern auch sein mögen - Sie können Ihre Stadt nicht vollständig damit umgeben. Um Einwanderer und Handelskarawanen hereinzulassen, benötigen Sie auch Stadttore. @PBauen Sie Stadttore dort ein, wo die großen Durchgangsstraßen auf die Stadtmauern stoßen. Schieben Sie den Mauszeiger auf die gewünschte Stelle, und drücken Sie die R-Taste, um die Richtung zu ändern, in die das Stadttor zeigt. Nach ihrer Platzierung werden Stadttore automatisch mit den angrenzenden Mauern verbunden. Sobald ein Angriff droht, schließen die Wächter die Tore, um den Feind auszusperren. @PGenau wie Sperren lassen Stadttore Fußgänger mit bestimmtem Ziel hindurch, Fußgänger ohne bestimmtes Ziel machen hier dagegen kehrt. Klicken Sie @42hier, um mehr über Fußgänger zu erfahren. @PFalls Sie weitere Informationen zum Thema 'Verteidigungsanlagen' wünschen, klicken Sie den Eintrag über @52Krieg an. @L@LDie Städte des alten Ägypten wurden gut verteidigt. Klicken Sie @182hier, um mehr darüber zu erfahren."
        }
    }

    message_building_police_station {
        id: 86,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Polizeiposten",
        }
        content {
            text: "Polizisten und Magistrate @L@LDie meisten Bürger genießen ein friedliches Leben. Wenn sie etwas an einer Stadt auszusetzen haben, halten sie damit nicht hinter dem Berg, oder sie suchen sich anderswo eine neue Heimat. Es gibt jedoch auch Elemente, die ihre Unzufriedenheit durch kriminelle Handlungen zum Ausdruck bringen. Ein beachtliches Aufgebot an Polizisten und Magistraten hilft, diese Unzufriedenen in Schach zu halten. Polizisten stellen außerdem eine Ihrer besten Waffen gegen @477Grabräuber dar.  @L@LPolizisten arbeiten von Polizeiposten und Magistrate von Gerichten aus. Beide Gebäude benötigen Arbeitskräfte und eine Straßenanbindung. Sobald sie in Betrieb sind, sehen Sie Polizisten ihre Runde drehen und Magistrate durch die Wohngebiete der Stadt gehen. Infoklicken Sie auf diese Gebäude, um festzustellen, ob sie mit Vollbesetzung arbeiten und was die Mitarbeiter gerade tun.  @L@LWenn Polizisten und Magistrate an einem Haus vorbeigehen, verringern sie die Wahrscheinlichkeit, dass aus diesem Haus ein Verbrecher kommt. Denken Sie jedoch daran, dass Polizisten und Magistrate keine festen Routen haben. Genau wie andere Fußgänger ohne festes Ziel streifen sie durch die Straßen der Stadt und müssen sich an jeder Kreuzung entscheiden, in welche Richtung sie weitergehen wollen.  Über der Polizeistation weht eine Flagge, wenn sie besetzt und aktiv ist. @PDie Gegenwart eines Polizisten in einem Wohngebiet verringert die Wahrscheinlichkeit von Kriminalität. @PUm festzustellen, in welchen Wohngebieten sich am ehesten Verbrecher entwickeln, verwenden Sie die @18Spezialkarte&Risiken. Diese Karte ist bei der Platzierung der Polizeiposten recht hilfreich. @PZwar würde kein Bürger auch nur im Traum daran denken, in einer Wohngegend zu leben, in der kein Polizist patrouilliert, aber direkt neben dem Polizeiposten möchte auch niemand wohnen. Polizisten kommen und gehen zu jeder Tages- und Nachtzeit, und häufig haben sie ziemlich zwielichtige Typen im Schlepptau. @L@LSie haben das Recht, @183hier zu klicken, um mehr über das Gesetz im alten Ägypten zu erfahren."
        }
    }

    message_company_orders {
        id: 87,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Kompanie-Befehle",
        }
        content {
            text: "Um eine @37Kompanie im Feld zu stationieren oder um einfach den Befehl zu erteilen, die Position zu wechseln, klicken Sie erst die Kompanie und dann die neue Position an. Die Flagge der Kompanie wird am neuen Standort gehisst, und die Kompanie marschiert dorthin - vorausgesetzt, die Stelle ist für die Soldaten erreichbar. Der steile, schlammige Abhang zwischen dem Überschwemmungsgebiet und trockenem Land ist nicht passierbar, außer, eine Straße verbindet die beiden Arten von Gelände.  @PEiner Kompanie können Sie folgende Befehle erteilen:  @L@LStellung halten in enger Formation @LIn dieser Formation stehen die Soldaten so eng wie möglich beisammen. Da sie Anweisung haben, die Stellung zu halten, verlassen sie ihre Position nicht, um Feinde anzugreifen. Allerdings werden alle Feinde angegriffen, die sich in Reichweite begeben. Die enge Formation verringert die Fläche, die die Soldaten verteidigen können. Sie sind so auch ein leichteres Ziel für feindliche Pfeile. Das Stehen Schulter an Schulter verbessert im Nahkampf jedoch die Verteidigungskraft.  @L@LStellung halten in loser Formation @LDieser Befehl kann nur Infanteristen und Bogenschützen erteilt werden (also nicht den Wagenlenkern). In loser Formation verteilen sich die Soldaten, um ein größeres Areal abzudecken, und versuchen dabei, die Stellung zu halten. Sie greifen an, wenn sich ein Feind in Reichweite begibt. Diese Formation verleiht Infanteristen und Bogenschützen mehr Schutz gegen feindliche Pfeile, sie bietet jedoch nicht viel Schutz vor Infanterieangriffen, da jeder Soldat nur sich selbst effektiv verteidigen kann.  @L@LFeinde in der Nähe angreifen @LWenn dieser Befehl erteilt wird, greift eine Kompanie Feinde in der direkten Umgebung an. Der Angriff wird fortgesetzt, bis der Feind getötet ist oder den Rückzug antritt bzw. bis Sie einen anderen Befehl erteilen ... oder bis die Moral der eigenen, geschlagenen Kompanie zu bröckeln beginnt und Ihre Männer ins Fort fliehen. @L@LAufräumen @LWenn Soldaten der Befehl zum Aufräumen erteilt wird, schwärmen sie aus, um die Feinde großflächig anzugreifen. Bei diesem Befehl agieren die Soldaten besonders aggressiv, verlassen die Formation und kämpfen furchtlos gegen den Feind. Furchtlosigkeit beeinträchtigt jedoch die Fähigkeit, sich zu verteidigen, daher wird dieser Befehl am besten nur dann angewandt, wenn Ihre Armee in der Überzahl ist.  @L@LStürmen @LDer Befehl zum Stürmen kann nur Wagenlenkern erteilt werden. Der Sturm gegen feindliche Linien bricht deren Formation auf, so dass sie Angriffen weniger entgegensetzen können. Bei einem Sturm peitschen die Wagenlenker ihre Pferde im Galopp über eine große Strecke und holen das Letzte aus den Tieren heraus. Mit der Zeit werden sie müde und müssen sich ausruhen. Diesen Befehl sollten Sie daher sparsam verwenden.  @L@LZurück zum Fort @LKlicken Sie auf 'Zurück zum Fort', wenn Ihre Soldaten ihre Aufgabe erfüllt und den Feind besiegt haben. Im Fort können sie sich für die nächste Schlacht ausruhen. Ist die Moral schlecht, kehren sie von allein zum Fort zurück.  @L@LZusätzlich zu den erwähnten besonderen Befehlen können Sie Kompanien auch einen Angriffsbefehl erteilen, indem Sie die Kompanie anwählen und dann auf einen Feind klicken. Die Kompanie verfolgt den angewählten Feind bis zum Tode, wenn Sie keinen anderen Befehl erteilen. @L@LNäheres zum Thema 'Kriegführung' im alten Ägypten erfahren Sie @184hier."
        }
    }

    message_building_recruiter_academy {
        id: 88,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Drillplatz und Akademie",
        }
        content {
            text: "Männer, die bereit sind, für ihre Stadt zu kämpfen, lassen sich auf dem Drillplatz registrieren. Weiteres Training können sie später in der Akademie erhalten. Sowohl der Drillplatz als auch die Akademie benötigt eine Straßenanbindung und Arbeitskräfte.  @PDie Funktion des Drillplatzes ist einfach: Hier werden neue Soldaten für die @37Armee der Stadt rekrutiert und gegebenenfalls mit speziellen Waffen ausgestattet. Um potentielle Infanteristen auszustatten, benötigt der Drillplatz einen Vorrat an Waffen. Waffen können über einen @47Handelspartner importiert oder von der @98Waffenschmiede hergestellt werden. Um Wagenlenker zu rekrutieren, werden Wagen benötigt. Diese können von einem Handelspartner importiert oder von einem @98Wagenbaubetrieb hergestellt werden. Wer davon träumt, als Bogenschütze in die Armee einzutreten, bringt Pfeil und Bogen selbst mit. Außerdem werden auf dem Drillplatz Rekruten je nach Bedarf für den Wachdienst auf den Stadtmauern und den @85Wachtürmen der Stadt eingeteilt. @PNeue Rekruten verlassen den Drillplatz mit den benötigten Waffen und großen Träumen von Heldentum, aber sonst mit herzlich wenig. In der Akademie werden Infanteristen, Bogenschützen und Wagenlenker in den Feinheiten der Kriegführung ausgebildet. Wächter erlernen ihren Beruf während der Arbeit und besuchen die Akademie nicht. Sobald die Soldaten diese Ausbildung absolviert haben, schließen sie sich ihren Kompanien in deren Fort an. @PBefindet sich in der Stadt keine Akademie, gehen Soldaten direkt vom Drillplatz aus zum Fort der Kompanie. @G57 @PAufgrund des eher lauten und rüden Umgangstons, den man mit dem Militär in Verbindung bringt, haben Drillplatz und Akademie negative Auswirkungen auf die @56Attraktivität. @L@LKlicken Sie @184hier, um mehr über den Krieg im alten Ägypten zu erfahren."
        }
    }

    message_building_grain_farm {
        id: 89,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Getreidefarm",
        }
        content {
            text: "Getreide unterscheidet sich nur insofern von anderen Nahrungsmitteln in der Stadt, als in Getreidefarmen ein Rohstoff als Nebenprodukt anfällt: Stroh. Stroh dient den Rindern auf @360Rinderfarmen als Futter und ist einer der für die @364Ziegelherstellung benötigten Rohstoffe. Stroh wird (genau wie Wildfleisch) als Futter für die Tiere im @479Zoo benutzt.  @PStroh wird zusammen mit dem Getreide geerntet. Ein Lieferant bringt das Stroh direkt zu Rinderfarmen, Ziegeleien, Zoos oder in @4Warenlager, während sein Kollege das Getreide in Silos oder Warenlager karrt. @PGetreidefarmen sind unbeliebte Nachbarn und senken den Wert der nahe gelegenen Grundstücke. @PWeitere hilfreiche Themen könnten sein: @45Nahrungsmittel&und&Landwirtschaft, @2Basare und @3Silos. @L@LKlicken Sie @185hier, um mehr über Getreide im alten Ägypten zu erfahren."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Obst- und Gemüsefarmen",
        }
        content {
            text: "Von Obst und Gemüse kann man sich genauso gesund ernähren wie von anderen Nahrungsmitteln. Außerdem bietet beides eine willkommene Abwechslung. In unterschiedlichen Gegenden Ägyptens wächst unterschiedliches Obst und Gemüse. Unter anderem können für Ihre Bürger Granatäpfel, Feigen, Kichererbsen und Salat angebaut werden. @PObst- und Gemüsefarmen werden auf dieselbe Weise bewirtschaftet wie andere Farmen, auf denen Nahrungsmittel angebaut werden. Hier werden jedoch ausschließlich Nahrungsmittel angebaut. Ausführlichere Informationen über die vorteilhafteste Planung der Farmen finden Sie im Eintrag zum Thema @45Landwirtschaft. @PBeide Arten von Farmen benötigen Arbeitskräfte und Zugang zu Straßen, um funktionsfähig zu sein. Bei Farmen im Überschwemmungsgebiet kommen die Arbeitskräfte aus @8Arbeiterlagern. Errichten Sie daher unbedingt mindestens ein Arbeiterlager in der Nähe der Farmen. @L@LDie Ägypter verzehrten eine Vielfalt an Nahrungsmitteln und genossen eine sehr geschmacksintensive Küche. Mehr über die Gaumenfreuden im alten Ägypten erfahren Sie @187hier."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Gerste-, Flachs- und Hennafarmen",
        }
        content {
            text: "Gerste-, Flachs- und Hennafarmen unterscheiden sich ein wenig von @89Getreide- und @90Obst-&und&Gemüsefarmen. Gerste-, Flachs- und Hennafarmen produzieren keine Nahrungsmittel, sondern Rohstoffe, die zu wertvollen Produkten verarbeitet werden. Gerste wird nach der Ernte zu @96Bier verarbeitet, Flachs zu @60Leinen versponnen und Henna wird zerstampft und mit Flüssigkeit gemischt, um @470Farbe herzustellen. @PGerste-, Flachs- und Hennafarmen werden jedoch genau wie andere Farmen errichtet und betrieben. Sie können an jedem beliebigen Ort im Überschwemmungsgebiet platziert werden, außerhalb jedoch nur auf landwirtschaftlich nutzbaren Wiesen, die man an den gelben Grasbüscheln erkennt. Wenn ein grünes Geisterbild der Farm angezeigt wird, haben Sie eine geeignete Stelle für den Bau gewählt. Farmen benötigen eine Straßenanbindung und Arbeitskräfte. Die Farmen im Überschwemmungsgebiet besorgen sich jedoch nicht direkt Arbeitskräfte, sondern verlassen sich dabei auf Bauern aus den @8Arbeiterlagern. Lesen Sie den Eintrag zum Thema @45Landwirtschaft durch, bevor Sie Ihre Farmen planen.  @PSobald Gerste, Flachs und Henna geerntet sind, wird die Ernte zum nächsten verarbeitenden Betrieb gebracht (Gerste in eine Brauerei, Flachs zur Weberei und Henna zu einer Farbmühle). Dort wird das Endprodukt aus Gerste, Flachs oder Henna hergestellt, das an Ihre Bürger verteilt, von der @363Kunsthandwerkergilde verarbeitet oder Gewinn bringend @47gehandelt wird. Haben die Hersteller keinen Platz oder gibt es keine Brauerei bzw. keine Weberei oder Farbmühle in der Stadt, werden die Produkte in ein @4Warenlager gebracht.  @PAlle drei Farmen haben negative Auswirkungen auf die @56Attraktivität der Umgebung. @L@LNäheres über die Geschichte des Gersteanbaus finden Sie @185hier. Klicken Sie @189hier, um mehr über den Flachsanbau im alten Ägypten zu erfahren. Wenn Sie mehr über den Anbau von Henna wissen möchten, klicken Sie @469hier."
        }
    }

    message_building_clay_pit {
        id: 92,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Tongrube",
        }
        content {
            text: "In Tongruben wird Ton abgebaut, der zu @1Geschirr oder in Verbindung mit @89Stroh zu @364Ziegeln verarbeitet werden kann. Die @363Kunsthandwerkergilde benötigt Ton für Verputzarbeiten. @PTongruben müssen Straßenanbindung und Zugang zu Arbeitskräften haben. Sie können nur neben Gewässern eingerichtet werden. @PSobald die Tongrubenarbeiter genug Ton abgebaut haben, um einen Karren zu füllen, wird ein Karrenschieber entsandt. Zuerst versucht er, den Ton bei der nächstgelegenen Ziegelei, Töpferei oder der Kunsthandwerkergilde loszuwerden, wobei er in der Nähe liegende Einrichtungen bevorzugt beliefert. Wenn keiner dieser Betriebe den Rohstoff braucht, bringt er den Ton in das nächste @4Warenlager mit freier Kapazität. Falls niemand den Ton annehmen kann, legt der Auslieferer eine Pause ein, bis ein Speicherplatz frei wird. @PTongruben sind feuchtkalte, hässliche Löcher im Boden, und Ihre anspruchsvollen Bürger möchten lieber nicht in der Nähe eines so unansehnlichen Ortes leben. @L@LDie alten Ägypter nutzten die reichhaltigen Ton- und Schlammablagerungen, die der Nil jedes Jahr hinterließ, optimal. Klicken Sie @190hier, um mehr über dieses wertvolle Produkt zu erfahren."
        }
    }

    message_building_gold_copper_mine {
        id: 93,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Gold- und Kupferminen",
        }
        content {
            text: "Gold und Kupfer. @L@LMetallbrocken, die in den Felsgebieten liegen, können ein Hinweis darauf sein, dass es hier Gold- oder Kupferadern oder beides gibt. Klicken Sie auf den Button 'Gewerbliche Gebäude', und lesen Sie sich die Liste der Rohstoffe durch, um festzustellen, was hier abgebaut werden kann. Wenn Sie das Glück haben, Gold abbauen zu können, sollten Sie sich diese Gelegenheit nicht entgehen lassen. Gold ist bares Geld wert, und der Goldabbau ermöglicht Ihrer Stadt, eigenes Geld zu produzieren.  @L@LBevor Sie mit dem Goldabbau anfangen, sollten Sie einen Palast errichten. Der Palast wandelt Golderz in Geld, also in Deben, um. Wenn Gold abgebaut wird, bevor ein Palast errichtet wurde, kann es der Karrenschieber der Goldmine nirgendwo abliefern. Golderz wird nie in Warenlagern aufbewahrt.  @L@LAuch Kupfer ist ein wertvolles Metall. Nach dem Abbau kann Kupfer an Handelspartner verkauft oder von einem Waffenschmied zu Waffen verarbeitet werden.  @L@LMinen müssen an felsiges Gebiet angrenzen, in dem Metallbrocken sichtbar sind. Beide Minentypen benötigen Straßenzugang und Arbeitskräfte, und beide gehören zu den unattraktivsten Nachbarn, die man in einer Stadt nur haben kann. @L@LDie alten Ägypter schätzten Gold sehr und nahmen Schwerstarbeit auf sich, um das Metall zu fördern. Klicken Sie @191hier, um mehr über Gold und seine Verwendung im alten Ägypten zu erfahren."
        }
    }
    
    message_building_woodcutter_and_reed_gatherer {
        id: 94,
        pos [0, 24]
        size [30, 28]
        title { text: "Holzfällerlager und Schilfsammelstellen" }
        content {
            text: "Holzfällerlager und Schilfsammelstellen bringen verfügbare Rohstoffe für andere Gewerbe ein. Holz kann vielseitig eingesetzt werden. Zimmerleute brauchen Holz, um Rampen und Gerüste für Monumente zu bauen, Wagenbauer bauen ihre tödlichen Streitwagen aus Holz, und auf Werften wird Holz zu Kriegs- und Transportschiffen verarbeitet.  @L@LSchilf wird für die Herstellung von Papyrus benötigt. Von Schilfsammelstellen werden Schilfsammler entsandt. Das gesammelte Schilf kann in Papyruswerkstätten zu Papyrus verarbeitet werden. Schilfsammelstellen müssen sich nicht direkt neben einem Schilffeld befinden. Schilfsammler sind gerne bereit, zu Fuß von ihrem Gebäude zu einem Schilffeld zu gehen.  @L@LÄhnlich funktioniert ein Holzfällerlager. So wie Schilfsammelstellen müssen auch Holzfällerlager nicht direkt an einen Wald grenzen. @PHolz ist eine der wertvollsten Waren in ganz Ägypten. Versuchen Sie, nicht durch Planieren von Land Wälder zu zerstören - sonst berauben Sie Ihre Stadt einer wichtigen Einkommensquelle. Sümpfe lassen sich nicht planieren. Es gibt übrigens Heiler, die glauben, dass Malaria durch die Sümpfe ausgelöst wird. @L@LKlicken Sie @192hier, um mehr darüber zu erfahren, wie wichtig Holz im alten Ägypten war. Klicken Sie @188hier, um einen Überblick über die vielen Verwendungsmöglichkeiten von Schilf zu bekommen."
        }
    }

    message_building_stone_quarries {
        id: 95,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Steinbrüche",
        }
        content {
            text: "In vier verschiedenen Steinbruchtypen können Arbeiter Stein brechen: @L@PEinfacher Steinbruch @PKalksteinbruch @PGranitsteinbruch @PSandsteinbruch @L@LWenn es im Stadtgebiet größere felsige Gebiete gibt, können Sie wahrscheinlich Steinbrüche einrichten, in denen der Stein abgebaut werden kann. In manchen Gebieten hat der Stein jedoch keine Bauqualität, oder es gibt zu wenig Stein, um eine lohnende Gewerbestätte einzurichten. In solchen Gebieten sind Felsen einfach nur lästig, da man sie weder entfernen noch überqueren noch bebauen kann. Klicken Sie auf den Button 'Gewerbliche Gebäude', und werfen Sie einen Blick in die Liste des verfügbaren Rohmaterials. Hier erfahren Sie, welche Arten von Stein in der Gegend gegebenenfalls abgebaut werden können. @PSteinbrüche müssen an felsige Gebiete angrenzen. Wenn Sie eine geeignete Position ausgesucht haben, wird ein grünes 'Geisterbild' des Steinbruchs angezeigt, den Sie platzieren wollen. Ansonsten sehen Sie ein rotes Zeichen. @PStein kann nicht zu anderen Produkten weiterverarbeitet werden. Allerdings werden Monumente aus Stein gebaut, und auch für den Bau kleinerer Monumente werden größere Mengen an Stein benötigt. @PSteinbrüche, die seitlich in felsige Gebiete gegraben werden, neigen dazu, zusammenzubrechen. Errichten Sie daher unbedingt ein @81Architektenbüro in der Nähe von Steinbrüchen, um Katastrophen zu verhindern. @PSteinbrüche benötigen eine Straßenanbindung und Arbeitskräfte, um zu funktionieren. Aufgrund des ständigen Hämmerns und Lärmens sind Steinbrüche sehr unattraktive Nachbarn.  @L@LUm im alten Ägypten Steine zu brechen, brauchte man viel Zeit. Klicken Sie @193hier, um mehr darüber zu erfahren."
        }
    }

    message_building_brewery {
        id: 96,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Brauerei",
        }
        content {
            text: "Um mit dem Brauen anfangen zu können, benötigen Brauereien einen Straßenzugang, Arbeitskräfte und eine gewisse Menge an Gerste. Die benötigte Gerste wird auf @91Gerstefarmen produziert bzw. kann über @47Handelspartner importiert werden. Eine Gerstefarm produziert in der Regel genug Gerste für zwei Brauereien. Brauereien können eine gewisse Menge an Gerste vor Ort auf Lager halten, um zwischen den Ernten weiterhin Bier brauen zu können. @PSobald eine Brauerei alles Nötige hat, wird mit dem Bierbrauen begonnen. Ob in einer Brauerei fleißig gebraut wird, erkennen Sie daran, ob der Braumeister und seine Mitarbeiter in der Brauerei zu sehen sind. Ist das Bier gebraut, versuchen Lieferanten das Bier zunächst an ein @74Senet-Haus zu liefern. Benötigt kein Senet-Haus das Bier, wird es in ein @4Warenlager gebracht, wo @2Basarkäuferinnen es für ihre Kunden erstehen können. Von hier aus können Sie mit Bier auch ziemlich lukrativ @47Handel treiben. Bier ist eines der Produkte, die Ihre Bürger benötigen, bevor sie ihre Häuser zu @56attraktiveren&Wohngebäuden ausbauen.  @PBier wird auch bei @51gewaltigen&Festen serviert.  @L@LWenn Sie @194hier klicken, erfahren Sie mehr über Bier im alten Ägypten."
        }
    }

    message_building_papyrus_maker {
        id: 97,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Papyruswerkstatt",
        }
        content {
            text: "Papyrus. @L@LPapyrushersteller verarbeiten Schilf zu Papyrus. Papyrus ist von grundlegender Bedeutung für die Bildung in der Stadt. Um eine Bibliothek errichten zu können, muss bereits ein Papyrusvorrat in Ihrem Warenlager vorhanden sein, und sowohl Bibliotheken als auch Schreiberschulen benötigen Papyrus, um den wohlhabenden Bürgern Bildung bieten zu können.  @PBürger leben nicht gern neben einer Papyruswerkstatt. Das ständige Hämmern verursacht ihnen Kopfschmerzen. @L@LWenn Sie @195hier klicken, erfahren Sie mehr über die Papyrusherstellung im alten Ägypten."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Waffenschmiede und Wagenbaubetrieb",
        }
        content {
            text: "Waffenschmieden und Wagenbaubetriebe stellen Kriegswerkzeuge her, die von bestimmten Militärkompanien benötigt werden.  @PDie Waffenschmiede verwendet Kupfer aus @93Kupferminen oder solches, das über @47Handelspartner importiert wurde, um daraus Waffen zu schmieden. Fertige Waffen werden zum @88Drillplatz gebracht, wo @37Infanterie-Kompanien damit ausgestattet werden, bzw. in ein @45Warenlager, wenn der Drillplatz bereits genügend Waffen auf Lager hat oder kein Drillplatz in der Stadt aktiv ist. @PWagenbaubetriebe verwenden Holz von @94Holzfällerlagern oder solches, das über @47Handelspartner importiert wurde, um herrliche Streitwagen aus Holz herzustellen. Das fertige Produkt wird zum Drillplatz geschickt, wo @37Wagenlenker damit ausgestattet werden. Hat der Drillplatz bereits einige Streitwagen im Inventar oder besitzt Ihre Stadt keinen funktionierenden Drillplatz, werden die Wagen in ein Warenlager gebracht. @PSowohl Waffenschmieden als auch Wagenbaubetriebe benötigen Arbeitskräfte und eine Straßenanbindung. Beides sind wenig @56attraktive Nachbarn. @L@LKlicken Sie @196hier, um mehr über Waffen im alten Ägypten zu erfahren."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Juwelier und Luxuswaren",
        }
        content {
            text: "Die wirklich reichen Bürger verlangen nach Luxuswaren - und sie lassen sich auch nicht mit nur einer Art davon abspeisen. Selbst herstellen können Sie allerdings nur Schmuck aus Edelsteinen.   @L@LJuweliere fertigen diese herrlichen Schmuckstücke in ihren Werkstätten an. Um den Wünschen der wohlhabenden Bürger nachzukommen, müssen Sie ein zweites Luxusgut zu einem hohen Preis von einem Handelspartner importieren. @L@LDer Import von Schmuck ist dabei sehr kostspielig, während der Export von Schmuck nur wenig abwirft. Luxuswaren sind mehr wegen der Transportkosten und weniger wegen der Materialkosten so teuer.  @L@LDas alte Ägypten ist für seinen wunderschönen @382Schmuck berühmt. Wenn Sie @197hier klicken, erfahren Sie mehr über weitere Luxusgüter im alten Ägypten."
        }
    }

    message_population_milestone_100 {
        id: 100,
        pos [0, 88]
        size [30, 20]
        title { text: "Wichtige Bevölkerungszahl" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "100 Leute sind in Ihr Dorf gezogen." }
    }

    message_population_milestone_500 {
        id: 101,
        pos [0, 88]
        size [30, 20]
        title { text: "Wichtige Bevölkerungszahl" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "In der aufblühenden Stadt wohnen jetzt 500 Menschen." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Wichtige Bevölkerungszahl" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "1000 Menschen nennen diese Stadt ihr Zuhause." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@17" }
        content { text: "Ihre Stadt hat jetzt 2000 Einwohner und gewinnt an Einfluss." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@17" }
        content { text: "Die Bevölkerung Ihrer Stadt hat zum ersten Mal in der Geschichte die 3000er-Marke erreicht." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@18" }
        content { text: "Ihre Stadt wird jetzt schon recht groß. Es leben bereits 5000 Menschen hier." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@18" }
        content { text: "Mit einer Bevölkerungszahl von 10000 gehört Ihre Stadt in Ägypten zu den größten." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@18" }
        content { text: "Wenige Städte können es mit Ihrer Stadt aufnehmen, in der jetzt 15000 Menschen leben." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@19" }
        content { text: "Andere Statthalter und Nomarchen blicken voller Bewunderung auf Ihre Stadt, in der jetzt 20000 Menschen leben!" }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Wichtige Bevölkerungszahl" }
        video { text: "@19" }
        content { text: "Selbst in ihren kühnsten Träumen hätten die wenigen Einwanderer, die Ihre Stadt vor so vielen Jahren gründeten, nicht zu denken gewagt, dass die Stadt einmal auf 25000 Köpfe anschwellen würde!" }
    }

    message_the_control_panel {
        id: 110,
        pos [0, 24]
        size [30, 20]
        title { text: "Die Steuerleiste"  }
        content {
            text: "In dieser Leiste finden Sie alle Steuerelemente, die Sie für Aufbau und Verwaltung der Stadt benötigen. Die einfachste Art, sich mit ihren Funktionen vertraut zu machen, ist, die einzelnen Buttons anzuklicken - keine Angst, es geht nichts kaputt! Wenn die Maushilfe (in der Menüleiste unter 'Hilfe') EINgeschaltet wurde, schieben Sie den Mauszeiger auf ein beliebiges Element und lassen ihn dort kurz stehen. Detaillierte Erklärungen der einzelnen Themen in Pharao finden Sie in der Menüleiste unter dem Punkt 'Hilfe'."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Feuer in der Stadt!" }
        content {
            text: "Flammen lodern in mehreren Teilen der Stadt. Klicken Sie auf die 'Spezialkarte: Risiken', um herauszufinden, wo das nächste Feuer ausbrechen könnte, und errichten Sie neben den gefährdeten Gebäuden Feuerwachen."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1
        pos [0, 88]
        size [30, 20]
        urgent: 1
        title { text: "Eingestürztes Gebäude!" }
        content {
            text: "Ohne angemessene Wartung durch die Architekten werden einige große Gebäude Ihrer Stadt einstürzen. Klicken Sie auf die 'Spezialkarte: Risiken', um herauszufinden, welche Gebäude vor dem Einsturz stehen, und errichten Sie neben den gefährdeten Gebäuden Architektenbüros."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Schiff auf Grund gelaufen!" }
        content { text: "Unerfahrene Kapitäne lernen Überschwemmungsgebiete oft auf die harte Tour kennen, wenn ihre Schiffe hier auf Grund laufen." }
    }

    message_out_of_money {
        id: 115,
        pos [0, 88]
        size [30, 20]
        title { text: "Kein Geld mehr!" }
        content { text: "Ihrer Finanzkasse sind die Deben ausgegangen. Sie erhalten hiermit zusätzliches Geld, aber niemand wird ein weiteres Mal helfen. Setzen Sie dieses Geschenk zum Aufbau lukrativer Betriebe ein." }
    }

    message_debt_again {
        id: 116,
        pos [0, 88]
        size [30, 20]
        title { text: "Schulden!" }
        content { text: "Ihre Finanzkasse verliert Geld. Sie verfügen über einen Kreditrahmen von bis zu 5000 Deben, aber @48Schulden können das Ende Ihrer Familie bedeuten, wenn Sie sie nicht schnell zurückzahlen." }
    }

    message_out_of_money_again {
        id: 117,
        pos [0, 88]
        size [30, 20]
        title { text: "Kein Geld mehr!" }
        content { text: "Die Kassen der Stadt sind leer, oh Pharao. Ihre treuen Nomarchen haben alle Deben gespendet, die sie erübrigen konnten, aber nochmals ist ihnen das nicht möglich." }
    }

    message_wrath_of_the_emperor {
        id: 118,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Der Pharao ist wütend!" }
        video { text: "@12" }
    }

    message_attack_called_off {
        id: 120,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Nachricht der Invasionstruppen" }
        content {
            text: "Gerade sind neue Befehle eingetroffen. Sie besagen, dass Sie in Ägypten wieder ein gewisses Maß an Respekt genießen und Ihre Vernichtung nicht mehr nötig ist. Ich sage Ihnen daher Lebwohl... fürs erste. "
        }
    }
    message_debt_anniversary {
        id: 121,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Immer noch Schulden!" }
        content {
            text: "Noch immer befinden sich fast keine Deben in Ihrer Kasse. Jedes aufeinander folgende Jahr, das Sie mit Schulden abschließen, schadet Ihrem Ruf und damit auch Ihrer @35Königreich-Wertung. Vielleicht sollten Sie Ihre Kenntnisse zum Thema @48Geld nochmals auffrischen."
        }
    }

    message_barbarians_attack {
        id: 122
        type: 2
        message_type: 7
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Barbarians attack!" }
        video { text: "smk\\Spy_Barbarian.smk" }
    }

    message_legion_attacks {
        id: 123
        type: 2
        message_type: 7
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Legion attacks" }
    }

    message_distant_battle {
        id: 124
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Distant battle" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_enemies_closing {
        id: 125
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Enemies closing" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_enemies_at_the_door {
        id: 126
        type: 2
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Enemies at the door" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_template_request {
        id: 130
    }

    message_wrath_of_bast_3 {
        id: 134,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Bastet zürnt" }
        video { text: "@20" }
        content { text: "Wehe! Bastet ist wütend über Ihre Gleichgültigkeit. Um Ihnen vor Augen zu führen, dass Sie den Gesundheitszustand Ihrer Stadt nur aufrechterhalten können, wenn Sie ihr genügend huldigen, hat sie das Wasser des Flusses in Blut verwandelt und die Wasservorräte vergiftet. Es bleibt nur zu hoffen, dass Ihre Bürger so lange durchhalten, bis das Wasser wieder sauber ist." }
    }
    message_city_unemployment {
        id: 135,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Arbeitslosigkeit in der Stadt!" }
        content { text: "Es gibt zu wenige Arbeitsplätze, um allen Leuten Arbeit zu geben. Falls keine neuen Arbeitsplätze geschaffen werden, wenden sich die Arbeitslosen in ihrer Verzweiflung möglicherweise der Kriminalität zu oder suchen ihr Glück woanders im Königreich." }
    }
    message_employees_needed {
        id: 136,
        pos [0, 88]
        size [30, 20]
        title { text: "Arbeitskräfte benötigt!" }
        content { text: "In der Stadt gibt es nicht genügend Leute im arbeitsfähigen Alter. Falls die Stadt nicht bald weitere Arbeitskräfte findet, werden die Dienstleistungen sich verschlechtern und die Produktion der Gewerbe zurückgehen." }
    }
    message_common_festival {
        id: 137,
        pos [0, 88]
        size [30, 20]
        title { text: "Gewöhnliches Fest" }
        content { text: "Alle Leute freuen sich darüber, früher Feierabend zu machen und ein paar entspannende Stunden auf dem Festplatz zuzubringen. Und die so geehrte Gottheit hat die Geste wohlwollend zur Kenntnis genommen." }
    }
    message_lavish_festival {
        id: 138,
        pos [0, 88]
        size [30, 20]
        title { text: "Üppiges Fest" }
        content { text: "Das den ganzen Tag über andauernde Fest beginnt. Überall in der Stadt begeben sich die Leute jetzt zum Festplatz und sind dabei ausgezeichneter Laune. Die geehrte Gottheit freut sich über Ihren Eifer." }
    }
    message_grand_festival {
        id: 139,
        pos [0, 88]
        size [30, 20]
        title { text: "Gewaltiges Fest" }
        content { text: "Das so lange und sehnsüchtig erwartete Fest hat endlich begonnen! Alle Leute versammeln sich auf dem Festplatz, um kostenloses Bier und mitreißende Unterhaltung zu genießen. Die mit diesem Ereignis geehrte Gottheit lächelt freudig auf Sie herab." }
    }
    message_wrath_of_osiris {
        id: 140
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Osiris zürnt ..." }
        video { text: "@24" }
        content { text: "Osiris ist über den eklatanten Mangel an Respekt äußerst aufgebracht. Falls Sie ihn nicht schnell besänftigen, ist die nächste Flut vielleicht nicht so gut wie erwartet ... und vielleicht fällt sie sogar völlig aus!" }
    }
    message_wrath_of_ptah {
        id: 141
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Ptah zürnt ..." }
        video { text: "@22" }
        content { text: "Sie haben den Zorn des Ptah erregt! In Ihrer Stadt gibt es zwar zurzeit keine Gewerbestätten, die er strafen könnte, aber behandeln Sie diesen Gott höflich, wenn Sie beginnen, Bergbau-, Produktions- oder Steinbruchbetriebe aufzubauen." }
    }
    message_wrath_of_ptah_2 {
        id: 142
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Ptah zürnt ..." }
        video { text: "@22" }
        content { text: "Ptah stößt sich an Ihrem Hochmut, der Sie glauben lässt, Ihre Stadt könnte produktiv sein, ohne ihm Respekt zu zollen. Als kleinen Denkanstoß hat er einige Ihrer Gewerbestätten vernichtet." }
    }
    message_wrath_of_seth_noeffect {
        id: 143
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Seth zürnt ..." }
        video { text: "@21" }
        content { text: "Ihre Stadt ist von Seths Zorn nur verschont geblieben, weil sie über keinerlei Militäreinrichtungen verfügt, die der Gott vernichten könnte. Dennoch sollte der Gott der Zerstörung nicht provoziert werden, denn sein Zorn kann vielfach Gestalt annehmen und sein Gedächtnis ist sehr gut." }
    }
    message_wrath_of_bast {
        id: 144,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Bastet zürnt ..." }
        video { text: "@20" }
        content { text: "Schlechte Nachrichten! Da die Stadt Bastet, Göttin des Heims, die ihr gebührenden Ehren vorenthält, hat die Gottheit einige der schönsten Häuser vernichtet!" }
    }
    message_blessing_from_ptah {
    id: 145,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Ptah" }
        video { text: "@22" }
        content { text: "Ptah suchte nach einem Warenlager, das noch Platz für Edelsteine, Ton, Geschirr, Flachs, Leinen oder Schmuck hat. Hätte er eines gefunden, hätte er die Vorräte Ihrer Stadt ergänzt." }
    }
    message_wrath_of_osiris_2 {
        id: 147
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Osiris zürnt ..." }
        video { text: "@24" }
        content { text: "Welch große Not! Verärgert über Ihre Weigerung, ihm den gebührenden Respekt zu zollen, schickt Osiris eine Heuschreckenplage über das Land, um Ihre Ernte zu vernichten." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Ptah zürnt ..." }
        video { text: "@22" }
        content {
            text: "Ptah ist empört, dass Sie sich weigern, ihm zu huldigen. Er lässt eine Froschplage über Ihre Stadt kommen. Die Frösche mit ihrer schleimigen Haut und ihrem ekelhaften Gestank werden viele Menschen aus ihren Häusern vertreiben."
        }
    }
    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Seth zürnt ..." }
        video { text: "@21" }
        content { text: "Erzürnt über Ihre Weigerung, ihm Ihre Hochachtung zu bezeigen, lässt Seth einen Hagelschauer über Ihrer Stadt niedergehen, der alle Leute tötet, die von den taubeneigroßen Körnern getroffen werden." }
    }
    message_farming {
    id: 150,
        pos [0, 88]
        size [30, 20]
        image { id: 81, pos [15, 15] }
        title { text: "Landwirtschaft" }
        subtitle { text: "Geschichte" }
        content {
            text: "Landwirtschaft und Ackerbau waren die Grundlage der ägyptischen Wirtschaft. Durch reiche Ernten konnte Ägypten mit seinen Nachbarn @47Handel treiben, so dass andere, neue Waren in das Land eingeführt wurden. @L@LDer Schlüssel zum erfolgreichen Ackerbau war die jährliche Überschwemmung, genannt Achet. Jedes Jahr trat der Nil über die Ufer und befruchtete den Boden von neuem. Solange die Überschwemmung stattfand, konnten die Ägypter gewiss sein, dass sie genug Nahrung haben würden. In den Jahren dagegen, in denen nur eine geringe oder gar keine Überschwemmung stattfand, darbte das Land. Häufig reichte dies, um eine Regierung zu stürzen. @L@LUm den Segen der Überschwemmung nutzen zu können, baute man um die Farmen herum Deichgräben, die das steigende Wasser auffangen sollten. Während sich der Nil wieder in seinen Lauf zurückzog (diese Jahreszeit wurde Peret genannt), sog sich der Boden mit Wasser und Nährstoffen voll. Etwa sechs Wochen später öffneten die Bauern die Kanäle und ließen das übrige Wasser abfließen. Natürlich war der Boden recht weich, nachdem er so viel Wasser aufgesogen hatte. Bevor der Bauer also sein Saatgut ausbringen konnte, musste er warten, bis das Land wieder etwas trockener und fester wurde. @L@LWährend der 'Schemu' genannten Jahreszeit wurde dann die Ernte eingebracht. Erträge für den ägyptischen Gebrauch lagerte man in @5Silos. Nahrungsmittel für den Export dagegen bewahrte man in @6Warenlagern auf, bis man sie auf Barken verladen konnte.  @L@LGroßgrundbesitzer oder die Regierung besaßen Farmen und beschäftigten Arbeiter für viele der besonders schweren Aufgaben. Ackerbau war keine leichte Arbeit, und ein Großteil der Arbeit wurde von Hand verrichtet. An Werkzeugen standen den Bauern Hacken, Sicheln und Handpflüge zur Verfügung. Zahme Ochsen erleichterten einen Teil des Pflügens. @L@LDurch den Ackerbau wurden sowohl Rohstoffe als auch Nahrungsmittel gewonnen. @185Weizen und Gerste waren wichtige Nahrungsmittel, und @189Flachs, der zu @398Leinen versponnen wurde, war der wichtigste pflanzliche Rohstoff. @L@LLandwirtschaft und Ackerbau waren auch ein wesentlicher Bestandteil des ägyptischen Jenseits. Wurde der Verstorbene für ein Leben nach dem Tode für würdig befunden, durfte er die Erde des Schilffeldes bearbeiten."
        }
    }
    message_industry {
        id: 151,
        pos [0, 88]
        size [30, 20]
        image { id: 82, pos [15, 15] }
        title { text: "Gewerbe" }
        subtitle { text: "Geschichte" }
        content {
            text: "Während des Alten Reichs fand die Produktion bereits nicht mehr zu Hause, sondern zentral in Werkstätten statt, in denen fast alles hergestellt wurde, was man im täglichen Leben so brauchte. Jede Werkstatt war auf ein bestimmtes Produkt spezialisiert und arbeitete in ähnlicher Weise wie man heute am Fließband arbeitet. Jeder Arbeiter war für einen bestimmten Aspekt des Endprodukts zuständig, anstatt ein Produkt von Anfang bis Ende herzustellen. Die Werkzeuge, die in diesen Werkstätten benutzt wurden, gehörten dem Staat, genau wie auch die Produkte, die in den Werkstätten entstanden. Handwerker wurden regelmäßig, meist in Nahrungsmitteln und anderen Gütern des täglichen Bedarfs, entlohnt. @L@LDie blühende ägyptische Wirtschaft erzeugte viele Produkte. Im alten Ägypten konnte man Arbeit als @198Töpfer, @398Weber, Juwelier, Gerber, @389Zimmermann, Schmelzer, Bäcker oder @194Braumeister finden."
        }
    }
    message_housing {
        id: 152,
        pos [0, 88]
        size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Wohnungen" }
        subtitle { text: "Geschichte" }
        content {
            text: "Im alten Ägypten baute man sein Haus aus Ziegeln, Holz, Lehm und gelegentlich aus Stein. Art und Größe der Behausung hing sowohl vom Reichtum des Besitzers als auch von der Umgebung ab. So lebten Landbewohner, die als Kleinbauern arbeiteten, in einfachen Behausungen aus Ziegeln oder gepresstem Lehm, die zwei bis vier Zimmer umfassten. In der Stadt lebten Arbeiter ebenfalls in kleinen Behausungen - aber es wurden auch einige zweistöckige Häuser für zwei Familien errichtet, um in Städten mit besonders hoher Bevölkerungsdichte Platz zu sparen. In der Regel wohnten Arbeiter in der Stadt in einem Ziegelbau, der aus 3 bis 7 Zimmern bestand. @L@LWohlhabendere Bürger besaßen größere Häuser, manche davon waren recht geräumig. Ranghohe Regierungsbeamte wohnten teilweise in Häusern mit 60 bis 70 Zimmern, die hohe, von hölzernen Säulen getragene Decken hatten. Hier gab es Empfangsräume für Gäste, jede Menge Lagerplatz und Dienstbotenquartiere. Die luxuriösesten Behausungen jedoch waren die @175Pharaonenpaläste.  @L@LGrößtenteils wuchsen ägyptische Städte nicht nach Plan, sondern dehnten sich eher willkürlich aus. Einige wenige Städte jedoch wurden tatsächlich geplant. Das wohl bekannteste Beispiel für eine solche Stadt ist die Arbeitersiedlung bei Deir el-Medina. @L@LDie meisten ägyptischen Städte waren von einer Stadtmauer umgeben. Mehr über Verteidigungsanlagen erfahren Sie @182hier."
        }
    }
    message_roads {
        id: 153,
        pos [0, 88]
        size [30, 20]
        image {
            id: 84,
            pos [15, 15]
        }
        title {
            text: "Straßen",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Der @157Nil war die Hauptverkehrsader Ägyptens. Schiffe aller Arten und Größenordnungen beförderten Menschen, Waren und Rohstoffe von einem Ort zum anderen. Natürlich gab es auch richtige Straßen auf dem Festland. Diese Straßen waren in der Regel nicht gepflastert, sondern einfach nur ausgetretene Pfade. In den meisten Städten wanden sich die Straßen überall dort hin, wo es gerade praktisch erschien. In geplanten Städten wie z.B. der Arbeitersiedlung in Deir el-Medina waren die Straßen rasterförmig angeordnet. @L@LFeste Handelsrouten gab es zwar auch, aber auch sie waren nicht gepflastert - und es konnte recht gefährlich sein, sich darauf zu bewegen. Näheres über die Gefahren des Handels erfahren Sie @177hier."
        }
    }
    message_irrigation {
        id: 154,
        pos [0, 88]
        size [30, 20]
        image {
            id: 27,
            pos [15, 15]
        }
        title {
            text: "Bewässerung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Durch Bewässerungssysteme konnten die Ägypter die Menge des landwirtschaftlich nutzbaren Landes vergrößern. Bereits zur Zeit der neunten Dynastie, also etwa um 2000 v. Chr., begannen die Ägypter, ein Netzwerk aus Bewässerungskanälen und Deichgräben zu errichten. Zwar gab es anscheinend auch schon vor dieser Zeit einige Kanäle, diese wurden jedoch für Transportaufgaben genutzt. Die Bewässerungskanäle weiteten die Vorteile, die der Fluss brachte, auf andere Gebiete aus und versorgten auch diese Gebiete mit dem nährstoffreichen Schlamm. @L@LIn der Frühzeit der ägyptischen Geschichte war es für die Bauern harte Arbeit, das Land zu bewässern. Damals bewässerte man das Land von Hand, indem man eine Schultertrage mit zwei Eimern aus Ton oder Leder zum Nil oder einer anderen Wasserquelle trug. Dann trug der Bauer die Wassereimer wieder zur Farm zurück, die von kleinen Bewässerungsgräben durchzogen war. In diesen Gräben wurde das Wasser aufgefangen, was die Vorteile dieser langsamen und mühevollen Bewässerungsmethode maximierte.  @L@LEnde der 18. Dynastie (um 1300 v. Chr.) wurde der Wasserheber, Schaduf genannt, eingeführt. Der Schaduf kam vermutlich aus Mesopotamien nach Ägypten. In Mesopotamien ist sein Einsatz bereits 2370 v. Chr. belegt. Der Schaduf, ein langer hölzerner Balken, der sich auf einem Zapfen hin- und herbewegt, wurde am Ufer des Nils oder einer anderen Wasserquelle aufgestellt. Als Gegengewicht zum Eimer am einen Ende des Balkens wurden am anderen Ende Ziegel oder andere Gewichte genutzt. Ein Arbeiter drückte das Ende mit dem Eimer hinunter ins Wasser. Mit Hilfe des Gewichts konnte er das Wasser dann in die Wasserrinne befördern, die mit dem Schaduf verbunden war. @L@LMit der Einführung des Schaduf vergrößerte sich die landwirtschaftliche Nutzfläche in Ägypten um etwa 15 Prozent. Außerdem konnte Land, das mit dem Schaduf bewässert wurde, statt einer Ernte pro Jahr zwei hervorbringen, da es nie unter Wasser stand."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2
        pos [0, 88]
        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Arbeit" }
        subtitle { text: "Geschichte" }
        content { text: "Ein Großteil der wirklich schweren Arbeit wurde im alten Ägypten von Bauern verrichtet. Während der Anbau- und Erntezeit bearbeiteten sie den Boden und brachten die Ernte ein. Während der Überschwemmung wurden dieselben Arbeiter eingezogen, um für den Staat zu arbeiten. Größtenteils arbeiteten sie am Bau von Pyramiden und anderen Gebäuden mit, wurden aber durchaus auch mit dem Unterhalt der Infrastruktur beauftragt, wie z.B. dem Bau und Erhalt von @153Straßen und @154Bewässerungskanälen. @L@LZwar war das kein leichtes Leben, doch wurden die Arbeiter nicht wirklich ausgebeutet. Üblicherweise dauerte ein Arbeitstag acht Stunden. Mittags gab es eine Pause. Die Arbeitswoche dauerte acht Tage. Am Ende dieser Woche hatten die Arbeiter zwei Tage frei. Zusätzlich zu diesen 'Wochenenden' musste auch an Festtagen nicht gearbeitet werden. Ein Arbeiter konnte sich auch frei nehmen, wenn Familienangehörige erkrankten oder es einen Todesfall in der Familie gab. @L@LÜber die Anwesenheit sowie über die Gründe bei Ausfällen gibt es ausführliche Unterlagen. Einige Gründe wären heute allerdings wohl keine akzeptierten Ausreden mehr ... Ein Arbeiter z.B. kam nicht zur Arbeit, weil er mit einem Freund einen trinken gehen wollte. @L@LIm Gegensatz zur landläufigen Meinung wurden Sklaven nur selten für die Arbeit an staatlichen Bauvorhaben eingesetzt. Manchmal setzte man Sklaven in Steinbrüchen ein, größtenteils jedoch dienten sie in Haushalten. @L@LWenn Arbeiter nicht gut behandelt wurden, konnten sie in Streik treten. Während der Herrschaft von Ramses III., etwa im Jahr 1152 v. Chr., legten Arbeiter in Deir el-Medina offiziell die Arbeit nieder, um gegen die Verzögerungen bei der Entlohnung zu protestieren. Der Streik war erfolgreich und das Problem der verspäteten Entlohnung wurde behoben." }
    }
    message_tutorial_clean_water {
        id: 156
        pos [0, 88]
        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Ziehbrunnen und Zisternen", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Die Versorgung der Bevölkerung mit Trinkwasser war im alten Ägypten keine geringe Herausforderung. Die wichtigste Wasserquelle war der Nil und dessen Grundwasserspiegel. Abseits des Nils gab es zwar einige Oasen, aber der Großteil des Landes war trocken. @L@LUm Wasser in Wohngebiete zu bringen, wurden Zisternen in den Dörfern errichtet. Wasserträger brachten eimerweise Wasser vom Nil und leerten es in die Zisternen. @L@LDie Ägypter waren Meister im Brunnenbau. Für einen Brunnen in der Nähe der Arbeitersiedlung von Giseh mussten Arbeiter sich durch 100 Meter Stein graben. Über den meisten Brunnen wurde ein Brunnenhäuschen errichtet. Von hier aus führte eine Treppe zum Wasserspiegel hinab. Dort füllten die Leute dann ihre Krüge mit Wasser."
        }
    }
    message_nile {
        id: 157,
        pos [0, 88]
        size [30, 20]
        image {
            id: 87,
            pos [15, 15]
        }
        title {
            text: "Der Nil",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ohne den Nil hätte es die ägyptische Zivilisation niemals gegeben. In einer Region, in der es nur wenig Regen gab, stellte der Nil für Menschen und Land eine zuverlässige Wasserquelle dar. Und durch die ziemlich regelmäßige Überschwemmung machte der Nil das Ackerland immer wieder fruchtbar. @L@LDie alten Ägypter waren sich der Bedeutung des Nils sehr wohl bewusst. Die Erfahrung, dass der Nil das Land immer wieder zu neuem Leben erweckte, prägte die religiösen Traditionen der Ägypter sehr nachhaltig, und hier vor allem ihren Glauben an ein Leben nach dem Tod.  @L@LDer ägyptische Kalender war in Jahreszeiten aufgeteilt, die nach den verschiedenen Stadien des Nils benannt waren. Die Überschwemmung, die Zeit also, in der der Nil über die Ufer trat, hieß Achet. Zu der Überschwemmung kam es aufgrund der jährlichen Monsunregen an der Quelle des Blauen Nils auf den Hochebenen Äthiopiens. Die Aussaat, Peret genannt, war die Zeit, in der sich der Nil in sein Bett zurückzog und das Land wieder zum Vorschein kam. Die Erntezeit schließlich nannte man Schemu, was gelegentlich auch als 'Dürre' übersetzt wird."
        }
    }
    message_dentistry {
        id: 158,
        pos [0, 88]
        size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Zahnärzte" }
        subtitle { text: "Geschichte" }
        content {
            text: "Ein Arzt im alten Ägypten konnte sich auf viele Gebiete spezialisieren - die zahnärztliche Heilkunst war nur eines davon. Die sterblichen Überreste der alten Ägypter lassen vermuten, dass Zahnärzte jedoch auf verlorenem Posten standen, denn Zahnschäden wurden durch den allgegenwärtigen Sand noch verstärkt. Sand wehte in fast alles hinein, auch in Nahrungsmittel - und durch das ständige Beißen auf Sand waren die Zähne bald abgeschliffen. Dies führte oft zu Abszessen, die im besten Fall zum Verlust des Zahns und im schlimmsten Fall zum Tod führten. @L@LAus medizinischen Dokumenten erfahren wir detailgenau, wie ein Zahnarzt bestimmte Probleme behandelte. Fiel jemandem beispielsweise einen Zahn aus, band der Zahnarzt diesen mit Gold- oder Silberdraht am benachbarten Zahn fest. Es gibt sogar ein überliefertes Rezept für Füllungen, für die Harz und Malachit vermischt wurden, aber bisher haben Archäologen keine Zähne finden können, in denen diese Füllungen noch intakt waren. @L@LIm Übrigen wurden bei Ausgrabungen Werkzeuge gefunden, von denen man glaubt, dass sie als Zahnbürsten verwendet wurden. Altägyptische Zahnseide wurde bisher allerdings noch nicht entdeckt."
        }
    }
    message_apothecary {
        id: 159,
        pos [0, 88]
        size [30, 20]
        image {
            id: 89,
            pos [15, 15]
        }
        title {
            text: "Apotheken",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die medizinischen und pharmazeutischen Verfahren im alten Ägypten sind genau dokumentiert. Religion war für das Heilen von Krankheiten entscheidend, und die meisten verschriebenen Kuren wurden durch Gebete oder Zaubersprüche begleitet. Medizinische Schriften erläuterten spezielle Heilverfahren, die uns heute zum Teil allerdings etwas merkwürdig vorkommen. Beispielsweise pulverisierte man den Zahn eines Ebers und mischte ihn in vier Zuckerküchlein, um gegen Magenverstimmung vorzugehen. Der Patient musste ein Küchlein pro Tag verzehren, danach sollte das Problem behoben sein. Auch ein Mittel gegen Haarausfall war recht kurios: Die Mischung bestand aus dem Wirbel einer Saatkrähe, dem verbrannten Huf eines Esels und dem Fett einer schwarzen Schlange."
        }
    }
    message_medicine {
        id: 160,
        pos [0, 88]
        size [30, 20]
        image {
            id: 90,
            pos [15, 15]
        }
        title {
            text: "Medizin",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Genau wie andere Bereiche der ägyptischen Gesellschaft war auch der Beruf des Mediziners sehr segmentiert und bürokratisch. Der Berufsstand war hierarchisch organisiert. Ärzte trugen Titel wie z.B. Leiter, Inspektor, Aufseher und Meister der Ärzte. Der höchste Rang unter Medizinern war 'Oberster der Ärzte im Süden und Norden'. @L@LIhr medizinisches Wissen erlangten Ärzte durch das Studium der inneren Organe von Tieren und aus Texten, und nicht etwa durch das Beobachten des Prozesses beim Einbalsamieren, denn die Medizin war ein deutlich von den Beerdigungsriten getrennter Bereich. @L@LGesundheit war im Konzept der Metu verankert. Das Herz wurde als Mittelpunkt des Körpers betrachtet, alle anderen Körperteile waren über Metu, d.h. Kanäle, mit dem Herzen verbunden. Metu war jedoch nicht nur eine Beschreibung des Herz-Kreislauf-Systems. Sämtliche Körperteile wurden als Metu betrachtet. Zu Krankheiten kam es, wenn ein Teil der Metu blockiert war. @L@LUm Krankheiten zu heilen, verschrieben Ärzte Medizin und Gebete. Näheres über die pharmazeutischen Gepflogenheiten der Ägypter finden Sie unter @159Apotheken. @L@LÄgypter litten unter anderem an Kinderlähmung, Pocken, Tuberkulose der Wirbelsäule und Malaria. Außerdem neigten sie zu Krankheiten, die durch Wurmbefall verursacht wurden."
        }
    }
    message_embalmers {
        id: 161,
        pos [0, 88]
        size [30, 20]
        image {
            id: 23,
            pos [15, 15]
        }
        title {
            text: "Einbalsamierer",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Das Einbalsamieren ist der Eckpfeiler der ägyptischen Begräbnisriten. Der Ka, also der Geist des Verstorbenen, brauchte einen Aufenthaltsort im Jenseits - seinen Körper. Während der Einbalsamierung wurde der Körper als Symbol der Wiedergeburt zunächst im Wasser des Nils gereinigt. Danach wurden der Leiche die inneren Organe entnommen und in Behältern aufbewahrt, den sogenannten Kanopen. Das einzige Organ, das weggeworfen wurde, war das Gehirn (das man durch die Nase entfernte), da die Ägypter der Auffassung waren, dass es keinen Zweck erfülle. Die Kanopen wurden zusammen mit der Leiche beerdigt. @L@LNach dem Entfernen der inneren Organe füllte der Einbalsamierer die Körperhöhlung mit Parfüm, Öl und Leinen, bevor er den Körper wieder verschloss. Dann wurde der Körper mit Natronsalz bedeckt. Nach 70 Tagen wurde der Körper abgespült, in Leinen eingewickelt und mit Teer eingerieben. Der Teer trug dazu bei, Bakterien und Pilze abzutöten, die ansonsten zur Verwesung des Körpers geführt hätten. @L@LDa die Einbalsamierung eine sehr teure Angelegenheit war, war sie nur für die reichsten Bürger erschwinglich."
        }
    }
    message_shrine_and_temple {
        id: 162,
        pos [0, 88]
        size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Schreine und Tempel", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Tempel wurden als Wohnstatt der Götter betrachtet. In jedem Tempel dienten unzählige @384Priester dem jeweiligen Gott. Der Normalbürger sorgte zwar durch Opfergaben ebenfalls für den Gott, bekam dessen Statue jedoch nur selten zu Gesicht, denn sie war tief im Tempel verborgen. Lediglich an Festtagen, wenn die Statue auf einer zeremoniellen Barke durch den Ort getragen wurde, erhaschten die Bürger einen Blick auf die Gottheit. @L@LÄgypter baten ihre Götter oft und gern um Rat. Im Vorhof des Tempels war jedermann willkommen. Hier konnte man die Götter zu Dingen befragen, die man nicht verstand, oder um Vergebung für begangene Sünden bitten. Antworten erhielten die Ratsuchenden von Priestern, die allerdings vor ihren Blicken verborgen blieben. Des Weiteren konnten Bürger dem Gott auch an Festtagen ihre Fragen stellen, wenn er unter ihnen weilte. @L@LDen Göttern wurde jedoch nicht nur im Tempel Verehrung zuteil. Auch in den Wohnungen der meisten Ägypter befanden sich kleine Schreine. Häufig handelte es sich dabei um einen Schrein von Bes, dem Schutzgott des Haushalts. Aber auch jeder Einzelne schien eigene Schutzgötter zu haben. In einem Dokument, das die Anwesenheit der Arbeiter von Deir el-Medina auflistet, ist gelegentlich verzeichnet, dass Arbeiter abwesend waren, um 'das Fest ihres Gottes zu feiern'. @L@LDas Konzept eines Schutzgottes bezog sich auch auf Städte, Orte und Regionen. Daher wurden zu verschiedenen Zeitpunkten der ägyptischen Geschichte unterschiedliche Götter verehrt. Näheres über die Entwicklung der Religion finden Sie @399hier."
        }
    }
    message_school_and_eduction {
        id: 163,
        pos [0, 88]
        size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "Schulen und Ausbildung", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Das Bildungssystem im alten Ägypten war äußerst praktisch ausgelegt. Jeder Bürger wurde im Hinblick auf einen bestimmten Beruf erzogen. Für viele bedeutete Bildung eine Lehre, und in der Regel gingen Söhne bei ihrem Vater in die Lehre, um ein Handwerk zu erlernen. Einige Mädchen durchliefen ebenfalls eine Lehre - als Tänzerin, Sängerin oder Weberin, aber meist wurden sie in der Kunst unterrichtet, einen Haushalt zu führen. @L@LSchreiber erhielten am meisten Bildung im herkömmlichen Sinne. Schreiberschulen, auch als Per Anch oder 'Lebenshäuser' bezeichnet, waren meist einem Tempel angeschlossen. Hier lernten zukünftige Schreiber die geschriebenen Sprachen, vor allem die hieratische und später die demotische Schrift, die für die täglichen Geschäfte genutzt wurden. Schreiber lernten ihr Handwerk, indem sie Manuskripte auf Ostraka oder alte Steinscherben kopierten. Erst wenn sie ihr Handwerk beherrschten, vertraute man ihnen Papyrus an. Disziplin wurde vorausgesetzt und körperliche Züchtigung kam häufig vor. Die Ausbildung zum Schreiber erfolgte in der Regel im Alter zwischen 10 und 20 Jahren."
        }
    }
    message_library_and_literature {
        id: 164,
        pos [0, 88]
        size [30, 20]
        image {
            id: 91,
            pos [15, 15]
        }
        title {
            text: "Bibliotheken",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Da die Ägypter eine geschriebene Sprache besaßen, zeichneten sie viele ihrer Geschichten, Gedichte und Hymnen auf. Diese Texte wurden in Bibliotheken aufbewahrt, die dem Per Anch (Lebenshaus), der @163Schreiberschule, angegliedert waren, die wiederum an den Tempel grenzte.  @L@LDie ägyptische Literatur entsprang der Tradition der mündlichen Überlieferung, und bei Literatur-Aufzeichnungen handelte es sich zumeist um Gedächtnisstützen für den Geschichtenerzähler. Die meisten Ägypter waren Analphabeten, und viele @387Schreiber waren Geschichtenerzähler, die die Schrift nutzten, um die Geschichten, Hymnen und Gedichte nicht zu vergessen. Wer lesen konnte, insbesondere diejenigen, die mit dem Hof des Pharao in Verbindung standen, konnte Zugang zu den Bibliotheken erhalten und die Papyri selbst lesen. Einige wohlhabende Bürger besaßen sogar eigene Bibliotheken. @L@LDie altägyptische Literatur ließ sich in mehrere verschiedene Gattungen aufteilen. Unter anderem gab es Autobiographien, Abenteuergeschichten, Märchen, mythologische Schriften, Klagelieder, Gedichte und Hymnen. Von all diesen Gattungen war die Autobiographie die älteste - sie entstand aus der Tradition, die Taten eines Menschen in sein Grabmal einzugravieren. Satiren waren ebenfalls sehr beliebt."
        }
    }
    message_history_entertainment {
        id: 165,
        pos [0, 88]
        size [30, 20]
        image {
            id: 92,
            pos [15, 15]
        }
        title {
            text: "Unterhaltung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die alten Ägypter konnten unter vielen verschiedenen Freizeitaktivitäten wählen. Häufig wurde Sport getrieben, insbesondere Wassersport wie z.B. Rudern oder Schwimmen (die Superreichen konnten diesen Sport ganz privat im eigenen Pool genießen). Außerdem sind die Ägypter die erste Kultur, von der man das Angeln als Freizeitaktivität kennt. @L@LBoxen war eine beliebte Zuschauer-Sportart. Schaukämpfe wurden unter anderem speziell für die Belustigung des Pharao arrangiert. Andere Sportarten waren zum Beispiel Handball, dann eine dem Hockey ähnliche Sportart, Gymnastik, Bogenschießen und Gewichtheben. @L@LUnter gebildeten Bürgern war das Lesen eine beliebte Freizeitbeschäftigung. Die erste uns bekannte Kurzgeschichte überhaupt wurde im alten Ägypten verfasst. Gedichte waren ebenfalls beliebt, aber es gibt keinerlei Hinweise auf ägyptische Theaterstücke. Näheres über Lesen, Schreiben und Literatur erfahren Sie unter @164Bibliotheken. @L@L@393Feste waren ein weiterer wichtiger Bestandteil des Lebens im alten Ägypten."
        }
    }
    message_children {
        id: 166,
        pos [0, 88]
        size [30, 20]
        image {
            id: 93,
            pos [15, 15]
        }
        title {
            text: "Kinder",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Kinder galten im alten Ägypten sehr viel und wurden als Fortführung des Lebens betrachtet. Meist wurde früh geheiratet, damit viele Kinder gezeugt werden konnten. Die Kinder der Unterschichten gingen mit ihren Eltern auf die Felder und halfen bei der Ernte. Kinder der Mittel- und Oberschicht verbrachten ihre Zeit zu Hause bei ihren Müttern. Wenn sie alt genug waren, wurden Jungen der Oberklasse in die Schule geschickt und gingen dann bei ihren Vätern in die Lehre. @L@LÄgyptische Kinder hatten viele Spielsachen und Spiele, darunter Bälle, Puppen, Kreisel und Holztiere. Sie spielten Spiele wie Tauziehen und genossen viele der Freizeitaktivitäten ihrer Eltern wie z.B. Schwimmen oder Angeln. @L@LKinder (und ihre Eltern) hatten darüber hinaus viele Haustiere. Sowohl Hunde als auch Katzen waren beliebte Haustiere, aber auch dressierte Affen, Vögel, Gazellen gab es - und Löwen, zumindest bei den besonders Reichen und Mutigen."
        }
    }
    message_history_population {
        id: 167,
        pos [0, 88]
        size [30, 20]
        image {
            id: 94,
            pos [15, 15]
        }
        title {
            text: "Die ägyptische Bevölkerung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "In vielerlei Hinsicht ähnelte das alte Ägypten unserer heutigen Gesellschaft. Viele Menschen lebten in städtischen Zentren, wo sie im Gewerbe einen Arbeitsplatz fanden. Bauern lebten in kleineren Dörfern auf dem Land. Der Großteil der Bevölkerung wohnte natürlich in Flussnähe. @L@LDie Größe der ägyptischen Bevölkerung wuchs im Laufe der Zeit, und dieses Bevölkerungswachstum steht in direktem Zusammenhang mit der @154Bewässerung. In der Zeit vor den Dynastien, so vermutet man, lag die Bevölkerungszahl höchstens bei 350.000. Am Ende des zweiten Jahrhunderts vor Christus lag diese Zahl allerdings vermutlich bereits bei etwa 3 Millionen, da die Menge fruchtbaren Landes durch Bewässerung deutlich vergrößert worden war."
        }
    }
    message_history_society {
        id: 168,
        pos [0, 88]
        size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Die ägyptische Gesellschaft", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Die ägyptische Gesellschaft war von einem starken Klassensystem geprägt. Größtenteils verharrte man in der Klasse, in die man hineingeboren wurde, obwohl es einige Beispiele dafür gibt, dass Einzelne in eine höhere Klasse eingeheiratet haben. @L@LDie niedrigste Klasse war die der Bauern. Sie hatten die geringste Lebenserwartung aller Bevölkerungsschichten und mussten ein Leben lang hart arbeiten - entweder in der Landwirtschaft oder an staatlichen Bauprojekten. Ihre sterblichen Überreste beweisen, dass die meisten von ihnen Rückenprobleme hatten. Manchmal waren sogar Wirbel durch die schwere Arbeit miteinander verwachsen. Bauern lebten in äußerst spartanischen Gebäuden mit wenigen Zimmern, wurden in einfachen Gräbern beerdigt und konnten es sich nicht leisten, sich einbalsamieren zu lassen. @L@LDie Mittelklasse bestand aus Handwerkern, Händlern und anderen Menschen, die am Wirtschaftsleben teilnahmen. Sie lebten in größeren Häusern und einige von ihnen konnten sich die Einbalsamierung und kleinere Grabstätten leisten. @L@LDie reichste Klasse bestand aus hochrangigen Regierungsbeamten. Sie konnten sich jeglichen Luxus leisten, auch das Einbalsamieren, und häufig ließen sie sich herrliche Grabmäler bauen. Ihre Ernährung war reichhaltiger und vielfältiger als die der anderen Ägypter. Bei der Studie einiger mumifizierter Überreste von Ägyptern der Oberklasse wurden bei 10 bis 20 Prozent Anzeichen von Arteriosklerose festgestellt - eine Verhärtung der Arterien - was zeigt, dass diese Menschen viel tierische Fette zu sich nahmen und möglicherweise ein stressreiches Leben hatten. Reiche Männer wurden oft mit Bierbäuchen dargestellt, um ihren Reichtum zu dokumentieren."
        }
    }
    message_history_juggling {
        id: 169,
        pos [0, 88]
        size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Jongleure", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Die alten Ägypter waren die ersten uns bekannten Jongleure. Auf einem Grabmal des Mittleren Reichs in Beni Hassan wurden Zeichnungen gefunden, auf denen junge Frauen verschiedene Jongleurtricks ausführen, darunter auch Frauen, die sich huckepack gegenseitig Bälle zuwerfen. @L@LDie Bedeutung, die dem Jonglieren im alten Ägypten zugebilligt wurde, ist nicht ganz klar. Möglicherweise hatte es eine religiöse Bedeutung, möglicherweise diente es aber auch nur rein der Unterhaltung."
        }
    }
    message_history_music {
        id: 170,
        pos [0, 88]
        size [30, 20]
        image {
            id: 96,
            pos [15, 15]
        }
        title {
            text: "Musik",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Ägypter spielten viele verschiedene Instrumente, darunter Flöten (die es in vielen verschiedenen Größen gab), Harfen, Leiern, Lauten, Tamburine und andere Perkussionsinstrumente. Sänger bildeten einen integralen Bestandteil der ägyptischen Musik. Die meisten auf Papyrus aufgezeichneten Hymnen und Gedichte waren zum Singen mit Musikbegleitung gedacht. @L@LPerkussionsinstrumente kamen vor allem als Untermalung bei @171Tänzen zum Einsatz. Viele Tänzer benutzten während ihrer Darbietung z.B. Kastagnetten. @L@LAuch Trompeten waren in Ägypten populär. Trompeten waren mit dem Militär verbunden (wer weiß, vielleicht gab es auch bei den Ägyptern schon eine Art von Art Wecksignal ...). Diese Instrumente wurden häufig in den Grabkammern von Königen und Militärführern gefunden. Zwei Trompeten fand man z.B. in der Grabkammer von Tutanchamun. Um festzustellen, wie sich die Instrumente anhörten, wurde eines davon im Jahr 1939 gespielt. Nach wenigen Noten zerbrach es leider schon. Natürlich wurde die Trompete sofort restauriert. Die Trompete verband man auch mit @376Osiris, dem Gott der Landwirtschaft und der Nilflut. @L@LAuch andere Instrumente hatten eine religiöse Bedeutung. Das Sistrum, ein großes Instrument, das einer Rassel ähnelt, verband man mit Hathor, der Göttin der Freude, der Liebe und der Festlichkeiten. Flöten assoziierte man mit Amun, dem Gott der Sonne."
        }
    }
    message_history_dance {
        id: 171,
        pos [0, 88]
        size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Tanz", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Der Tanz im alten Ägypten entwickelte sich aus Ritualen, die Jäger zur Vorbereitung auf die Jagd durchführten. Ein führender Tänzer, der Priester-Tänzer, war verantwortlich für die richtige Ausführung der Tänze. @L@LSpäter wurde der Tanz zu einem integralen Bestandteil von Festen und anderen religiösen Feiern, aber auch eine Art der Unterhaltung in sich selbst. Professionelle Tanzgruppen traten auf Plätzen in der Stadt auf und konnten für private Feiern angeheuert werden. Meist wurden die Tänzer von @170Musik begleitet. Die meisten professionellen Tänzer waren Frauen. Viele von ihnen trugen auf den Oberschenkeln eine Tätowierung von Bes, dem Gott der Musik und des Tanzes.  @L@LEinige Bürger tanzten auch zum Vergnügen, obwohl dieser Spaß vorrangig den unteren Klassen vorbehalten war. Je höher das Ansehen eines Ägypters, desto unwahrscheinlicher war es, dass er tanzte. Auch tanzten Männer und Frauen niemals miteinander. Frauen tanzten mit anderen Frauen, Männer mit anderen Männern. @L@LAnscheinend benannte man die Tanzbewegungen in Ägypten nach dem, was sie darstellten, zum Beispiel 'das Führen eines Tieres', 'das erfolgreiche Kapern eines Boots' und 'das lustige Huhn'."
        }
    }
    message_history_senet {
        id: 172,
        pos [0, 88]
        size [30, 20]
        image {
            id: 98,
            pos [15, 15]
        }
        title {
            text: "Senet-Häuser",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Senet war das beliebteste Brettspiel im alten Ägypten. Das Spielbrett war rechteckig und in drei Reihen à zehn Quadrate aufteilt. Senet spielte man zu zweit, und jeder Spieler besaß mindestens fünf Spielsteine. Die Züge wurden durch vier Wurfhölzer bestimmt. Da die Regeln für das Senet-Spiel jedoch nirgends verzeichnet wurden, weiß man leider nicht genau, wie das Spiel tatsächlich gespielt wurde. Die meisten Historiker sind sich allerdings einig, dass das Spiel die Reise ins Jenseits symbolisierte. Sowohl Backgammon als auch das Spiel 'Himmel und Hölle' werden als Ableitungen von Senet betrachtet. @L@LSenet dürfte, zusammen mit vielen anderen Spielen, vermutlich eine der vielen Vergnügungen gewesen sein, denen Ägypter in Tavernen und Gasthäusern frönen konnten. Nach einem langen, schweren Arbeitstag zogen sich viele Ägypter in lokale Tavernen zurück, wo es @194Bier und viel lebhafte Unterhaltung gab. Sowohl Männer als auch Frauen - insbesondere unverheiratete - frequentierten Bierhäuser."
        }
    }
    message_history_taxation_and_money {
        id: 173,
        pos [0, 88]
        size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Steuern", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Die alten Ägypter zahlten ihrem Pharao Steuern. Da es keine Währung gab, beglich man seine Steuerschuld in Form von Waren. So musste ein Bauer beispielsweise dem Pharao eine bestimmte Menge Weizen als Steuer entrichten. Schreiber wurden auf alle Bauernhöfe geschickt, um festzulegen, wie viel jeder Bauer dem Staat schuldete."
        }
    }
    message_history_government_and_bureaucracy {
        id: 174,
        pos [0, 88]
        size [30, 20]
        image {
            id: 40,
            pos [15, 15]
        }
        title {
            text: "Regierung und Bürokratie",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Regierung im alten Ägypten war extrem bürokratisch. Für jede nur vorstellbare Aufgabe gab es einen Regierungsbeamten mit einem wichtig klingenden Titel. Ganz oben in der Hierarchie stand natürlich der Pharao. Seine rechte Hand war der Wesir. Dieser war dafür verantwortlich, dass alle Befehle des Pharao ausgeführt wurden. Unter dem Wesir standen die Nomarchen (Regionalgouverneure), Kanzler, Vizekönige, Inspektoren, Bürgermeister - und die Liste geht immer weiter. Und da das alte Ägypten eine Theokratie war, spielten Priester eine wichtige Rolle. @L@LEinige Personen trugen auch mehr als einen Titel. So war beispielsweise Imhotep, der unter Djoser I. diente und den Bau der Stufenpyramide überwachte, nicht nur Wesir, sondern auch 'Hohepriester des Ptah' und 'Aufseher der Arbeiten'."
        }
    }
    message_history_pharaohs_home {
        id: 175,
        pos [0, 88]
        size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "So wohnte der Pharao", pos [125, 15] }
        subtitle { text: "Geschichte" }
        content {
            text: "Die Residenz des Pharao war das majestätischste Gebäude der ganzen Stadt. Während die meisten Häuser nur ein oder zwei Zimmer hatten, umfassten manche Villen des Pharao Dutzende von Zimmern und waren mit dem größten Komfort ausgestattet, den man zu dieser Zeit kannte. @L@LGenau wie in der @174Regierung hatten auch Ägypter im Dienste des Pharao Titel inne und waren für sehr spezifische Aufgaben verantwortlich. Unter anderem beschäftigte der Pharao einen 'Leiter des Haushaltes', einen 'Obersten Maniküristen' und einen 'Königlichen Butler'. @L@LEinem königlichen Diener mit dem Namen Nefer-Peret waren ganz besondere Aufgaben zugeteilt. Er war verantwortlich für die Pflege von vier palästinensischen und zwei ägyptischen Kühen, eines Bullen und eines Kupfereimers. Nicht mehr, nicht weniger."
        }
    }
    message_history_gardens_and_public_art {
        id: 176,
        pos [0, 88]
        size [30, 20]
        image {
            id: 38,
            pos [15, 15]
        }
        title {
            text: "Gärten und Kunstwerke",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Gärten waren im alten Ägypten äußerst beliebt, daher waren die meisten Häuser von Gärten umgeben. Abgesehen davon, dass man hier @187Obst&und&Gemüse anbaute, um die Ernährung zu ergänzen, bot der Garten Zuflucht vor der heißen Sonne. In vielen Gärten wurden mit viel Sorgfalt Bäume gehegt, die Schatten bieten sollten. @L@LKunst konzentrierte sich vorwiegend auf die Monumente und Tempel der Stadt. Für die Tempel und Monumente wurde so viel Zeit und Geld aufgewendet, dass der Rest des Ortes vergleichsweise langweilig wirkte."
        }
    }
    message_history_trade {
        id: 177,
        pos [0, 88]
        size [30, 20]
        image {
            id: 30,
            pos [15, 15]
        }
        title {
            text: "Handel",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Zwar mangelte es dem alten Ägypten nicht an natürlichen Ressourcen, bestimmte Waren jedoch waren absolute Mangelware. Die Ägypter richteten Handelswege zu vielen nahe gelegenen Ländern und Regionen ein, zu denen Nubien, der Libanon, Syrien und Punt (von dem Historiker meinen, es könnte sich um die somalische Küste handeln) sowie die Ägäis gehörten. Manche Quellen behaupten, dass sich der ägyptische Handel bis in die heutige Türkei ausgedehnt habe. @L@LDer Nil spielte beim Handel eine wichtige Rolle. Navigierbar war er bis zum ersten Katarakt, einer Serie felsiger Wasserfälle. Er diente als Straße und machte das Reisen von und nach Nubien recht einfach. @L@LAußerdem half der Nil, eines der wichtigsten Exportgüter zu transportieren: Weizen. Die Überschwemmung erwies sich als wesentlich zuverlässiger als der Regen im Libanon oder in Syrien. Solange die Überflutung stattfand, hatte Ägypten einen Überschuss an Weizen, ein Luxus, den der Libanon und Syrien selten genossen. Darüber hinaus exportierte man Leinen, Papyrus, Linsen, getrockneten Fisch, Gold- und Silberbehälter, Ochsenfelle und Seile. @L@LIm Austausch dafür importierte Ägypten eine Vielzahl an Waren. Besonders wichtig waren Gold aus Nubien, Holz aus dem Libanon und Olivenöl aus Syrien. Die Ägypter importierten aber auch andere Luxusgüter wie z.B. Myrrhe, Wein und Vieh sowie gelegentlich auch Waffen. @L@LMit Waren schwer beladene Karawanen hatten häufig unter Überfällen zu leiden. Zu ihrem Schutz wurden sie auf ihren Handelsmissionen daher von bewaffneten Einheiten begleitet. Aufgrund dieser bewaffneten Einheiten spekulieren manche Historiker, dass Ägypten keinen freien Handel mit seinen Nachbarn betrieb, sondern sie eher dazu zwang, Waren abzugeben. Gewalt dürfte im ägyptischen Handel zwar wahrscheinlich eine gewisse Rolle gespielt haben, trotzdem wird in einigen Papyri von Verhandlungen zwischen Ägypten und seinen Handelspartnern gesprochen. @L@LEinige besonders erfolgreiche Handelsmissionen feierte man mit Inschriften und Kunstwerken. Hatschepsut, eine Pharaonin, entsandte eine Flotte nach Punt, um Myrrhe, Weihrauch, Elfenbein und andere wertvolle Güter zu beschaffen. Die Reise wurde als so erfolgreich gewertet, dass dies auf den Mauern des Tempels von Hatschepsut in Deir el-Bahri verzeichnet wurde."
        }
    }
    message_history_ships_and_ship_making {
        id: 179,
        pos [0, 88]
        size [30, 20]
        image {
            id: 101,
            pos [15, 15]
        }
        title {
            text: "Schiffe und Schiffbau",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Seit jeher hat der Nil Schiffbauer inspiriert. In vordynastischer Zeit banden die Ägypter Papyrusschilf zusammen, um Flöße herzustellen, die sie mit Stäben voranbewegten. Mit dem Pyramidenbau kam dann der Beruf des Schiffbauers auf. Schiffe waren für den Transport der schweren Materialien wichtig, die für den Pyramidenbau benötigt wurden. @L@LGenau wie andere Gewerbestätten in Ägypten waren Werften Betriebe im Besitz der Regierung. Mit Holzwerkzeugen ausgestattet, bauten Schiffbauer zunächst den Rumpf des Bootes, indem sie Planken nebeneinander legten und sie mit Dübeln, Leim und Seilen, die schrumpften, wenn sie nass wurden, fixierten. Sobald die Seile schrumpften, war der Rumpf fest verbunden. Rümpfe größerer Schiffe waren mit Rippen versehen. Sobald der Rumpf komplett war, kümmerten sich die Schiffbauer um den Rest des Bootes und statteten es mit einem Mast für das Segel und Öffnungen für die Ruder aus. Einige der größeren Schiffe verfügten sogar über Kabinen. @L@LDie Schiffe besaßen einen breiten Bug und waren so konzipiert, dass sie wenig Tiefgang hatten, damit sie nicht so leicht sanken. Der Nil, obwohl relativ leicht zu navigieren, wies nämlich durchaus einige Sandbänke und flache Stellen auf, in denen Schiffe leicht auf Grund liefen. @L@LMan baute damals Schiffe von recht beachtlicher Größe. Ein Schiff, das verwendet wurde, um Obelisken in den Tempel von Hatschepsut zu transportieren, war 82 m lang. Eine der berühmtesten archäologischen Fundstücke ist die Barke des Cheops. Die Barke, die man in 1224 Stücken entlang der südlichen Seite der Cheops-Pyramide fand, wurde Anfang der 60-er Jahre rekonstruiert. Das Schiff war mehr als 43 Meter lang und 6 Meter breit mit Platz für 10 Ruderer und zwei Steuerleute. Über die Bedeutung des Schiffs streiten sich die Historiker noch. Einige spekulieren, dass es ein Symbol für das Sonnenschiff des Horus sei. Andere wiederum glauben, dass es möglicherweise die Barke war, mit der die sterblichen Überreste des Cheops zu seiner Pyramide gebracht wurden, oder dass er das Boot zu seinen Lebzeiten nutzte. Wie dem auch sei, das Boot gibt uns interessante Aufschlüsse über die Bauweise ägyptischer Schiffe."
        }
    }
    message_history_enemies {
        id: 181,
        pos [0, 88]
        size [30, 20]
        image {
            id: 102,
            pos [15, 15]
        }
        title {
            text: "Feinde",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ägypten stand in ständigem Kontakt mit seinen Nachbarn. Manchmal waren die Beziehungen jedoch nicht allzu freundschaftlich. Im Verlauf seiner langen Geschichte wurde Ägypten mehrfach überfallen und von Nichtägyptern regiert. Diese Nichtägypter nahmen dann jedoch den Titel eines Pharao an. Und bis zur persischen Invasion gelang es den Ägyptern stets, ihr Land wieder zurückzuerobern. Ägypten war jedoch nicht immer nur Opfer von Angriffen. Vor allem während der Zeit des Neuen Reichs strebte Ägypten danach, seinen Einflussbereich zu vergrößern, und fiel in viele benachbarte Länder ein. @L@LUnter anderem führte Ägypten Krieg gegen die Nubier und die Kusch. In Nubien fiel Ägypten relativ früh ein (um 2900 v. Chr.), und zwar vor allem, um die reichhaltigen Gold- und Kupferressourcen des Landes für sich zu beanspruchen. Während der Spätzeit gelang es Nubien jedoch, selbst die Oberhand zu gewinnen, und Ägypten wurde von mehreren nubischen Pharaonen regiert. @L@LAuf der Halbinsel Sinai gab es ebenfalls mehrere Völker, mit denen Ägypten Krieg führte. Zu diesen gehörten die Kanaaniter, die Philister, die Beduinen (aus dem heutigen Syrien) und die Hethiter. Die wichtigsten dieser asiatischen Völker sind jedoch die Hyksos. Während der zweiten Zwischenzeit herrschten die Hyksos über Ägypten. Sie übernahmen viele der kulturellen Traditionen Ägyptens, führten jedoch gleichzeitig viele Innovationen ein, so z.B. Pferdewagen. Die Hyksos herrschten etwa 100 Jahre lang über Ägypten, bis Ahmose I. sie besiegte und die Macht übernahm. @L@LIm Westen bekriegte Ägypten die libyschen Stämme, insbesondere die Tjehenu und die Tjemehu. Diese versuchten, in das ägyptische Delta zu gelangen, wurden aber von Sethos I. vernichtend geschlagen. Danach errichtete man im Westen @182Forts, um die Stämme in Schach zu halten. @L@LSchließlich erreichte das mächtige römische Imperium während der Herrschaft der Ptolemäer die Küsten Ägyptens. Ägyptens schwindende Militärmacht und die immer noch unermesslichen Reichtümer und prallvollen Lagerhäuser (nicht zu vergessen die betörende Kleopatra VII) zogen die gierigen Augen Julius Caesars und seiner Nachfolger geradezu magisch auf sich. Die Ankunft der römischen Legionen auf ägyptischem Boden markierte den Anfang vom Ende der langen Geschichte ägyptischer Herrschaft über den Mittelmeerraum und ließ das einst so stolze Ägypten schließlich zu einem Vasallenstaat werden. @L@LNäheres über das ägyptische Militär erfahren Sie @184hier."
        }
    }
    message_history_defensive_structures {
        id: 182,
        pos [0, 88]
        size [30, 20]
        image {
            id: 103,
            pos [15, 15]
        }
        title {
            text: "Verteidigungsanlagen",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ägypten schützte seine Städte durch Mauern und Türme. In der Regel bestanden die Mauern aus Lehmziegeln und umschlossen den Ort entweder in Form eines Vierecks oder eines Kreises. Ausgrabungen auf Elephantine im südlichen Ägypten in der Nähe der nubischen Grenze haben eine dicke, gebogene Mauer mit halbkreisförmigen Türmen zutage gefördert.  @L@LSeine Grenzen verteidigte Ägypten mit einer ganzen Reihe von Festungen. Zu den berühmtesten Verteidigungsanlagen zählen die 'Mauern des Herrschers', ein Gürtel aus 13 Festungen, der sich am Ostufer des Nils entlang zieht."
        }
    }
    message_history_law {
        id: 183,
        pos [0, 88]
        size [30, 20]
        image {
            id: 104,
            pos [15, 15]
        }
        title {
            text: "Ägyptisches Recht",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ägypter, die sich über einen anderen Bürger beschweren wollten, konnten ihr Anliegen beim Magistrat vorbringen. Je nach Schwere des Vergehens entschied entweder ein örtlicher Magistrat oder der Wesir höchstselbst über den Fall. Lokale Magistrate waren manchmal örtliche Beamte niederen Ranges, wie z.B. ein Vorarbeiter. Den Gerichtsfällen wohnten Schreiber bei, die Beteiligte, Zeugen, Aussagen und Strafen notierten. @L@LJeder - ob er nun aus der Ober- oder der Unterklasse stammte - war dem Gesetz unterworfen. In einer Szene, die auf einer Mastaba-Kapelle eines Wesirs des Alten Reichs eingraviert ist, werden Gouverneure dafür bestraft, dass sie Steuereinnahmen unterschlagen haben. Auch Frauen nahmen aktiv an Gerichtsverhandlungen teil. In einem bekannten Fall wurde einer Frau Land zugesprochen, das ihre Schwiegereltern ungerechtfertigterweise für sich beansprucht hatten. In einem anderen Fall wurde eine Frau für schuldig befunden, ein Werkzeug und ein Gefäß aus einem Schrein des Amun gestohlen zu haben. @L@LDie Strafen für ein Verbrechen konnten recht schwer sein - häufig wurden Schläge oder Zwangsarbeit verhängt. Während der 18. Dynastie im Neuen Reich belief sich die Strafe für den Diebstahl von Fellen auf 100 Schläge und fünf offene Wunden. Einige besonders schlimme Verbrechen wurden bestraft, indem man dem Schuldigen die Nase abschnitt und ihn an den Rand des Landes verbannte. @L@LDas ägyptische Recht war nicht streng schriftlich festgelegt, die meisten Strafen wurden von Fall zu Fall verhängt. Es existieren zwar, insbesondere aus der Zeit des Neuen Reichs, noch einige Listen von Verbrechen und deren Strafen, aber diese sind recht widersprüchlich. @L@LAuch im Leben nach dem Tod war Gerechtigkeit ein wichtiges Konzept. Bevor man in das Leben nach dem Tod gelangen konnte, musste man eine 'negative Beichte' ablegen, also alles aufzählen, was man während seines Lebens unterlassen hatte. Nach einer solchen Beichte wurde das Herz des Menschen auf einer Waage mit einer Feder aus dem Kopfschmuck von Maat gewogen. Wog das Herz nicht mehr als die Feder, durfte der Mensch ins Jenseits wechseln. War es schwerer, wurde es von Ammit, einem schrecklichen Monster, gefressen, und dem Menschen wurde der Zugang zum Jenseits verwehrt."
        }
    }
    message_history_military {
        id: 184,
        pos [0, 88]
        size [30, 20]
        image {
            id: 105,
            pos [15, 15]
        }
        title {
            text: "Militär",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Das ägyptische Militär entwickelte sich während der jahrtausendelangen Herrschaft der Pharaonen immer weiter. Im Alten Reich stellte man Armeen nur bei Bedarf auf. Sie bestanden meist aus Adligen und deren Gefolgsleuten oder aus Ausländern. Eine Berufsarmee gab es damals nicht. Die Männer, die in der Armee dienten, kamen aus allen Gesellschaftsschichten und kehrten vermutlich in ihren vorherigen Beruf zurück, wenn der Kampf vorüber war. @L@LZur Zeit des Neuen Reichs hatte sich die Struktur der Armee jedoch verändert. Die Armee war klar in Infanterie- und Wagenlenkereinheiten aufgeteilt. Die Infanterie wiederum bestand aus zwei Teilen: Einheiten, die auf Nahkampf, und andere, die auf den Kampf aus der Entfernung spezialisiert waren. Für den mobilen Einsatz im Kampf aus der Entfernung wurden Wagen eingesetzt. Soldaten mit Pfeil und Bogen fuhren auf den Wagen und feuerten Pfeile auf den Feind ab. Kämpfe zur See kamen häufig vor. Allerdings wurde die Marine nicht als getrennter Teil der Streitkräfte betrachtet. Vielmehr war die Marine Teil der Landstreitmacht, und Soldaten, die auf Schiffen dienten, wurden mit den gleichen Begriffen bezeichnet wie solche auf dem Land. Auch hier bestand wieder ein großer Teil der Armee aus Ausländern. Sowohl Nubier als auch Libyer und Asiaten kämpften auf der Seite der Ägypter. @L@LDie ägyptische Armee war im Alten Reich in Bataillone aufgeteilt. Während der Zeit des Neuen Reichs waren die Bataillone weiter in Divisionen unterteilt, die nach den Göttern benannt waren. Schreiber und Verwaltungsbeamte begleiteten die Soldaten im Kampf, vermutlich, um das Geschehen zu dokumentieren. @L@LNäheres über die Waffen der ägyptischen Armee erfahren Sie @196hier."
        }
    }
    message_history_grain_and_barley {
        id: 185,
        pos [0, 88]
        size [30, 20]
        image {
            id: 106,
            pos [15, 15]
        }
        title {
            text: "Weizen und Gerste",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Der Getreideanbau (Weizen und Gerste) lieferte den Grundstoff für das wichtigste Grundnahrungsmittel im alten Ägypten: Brot. Sowohl Weizen als auch Gerste wurden erst zu Mehl vermahlen und dann zu Brot gebacken. Näheres über die Verwendung von Gerstenbrot finden Sie unter @194Bier. @L@LDie Ägypter verwendeten drei Arten von Weizen: Emmer, Einkorn und Dinkel. Weizen wurde durch Dreschen zu Mehl verarbeitet. Dazu wurden Weizenhalme auf die Erde gelegt und Vieh oder andere große Tiere wurden herangeführt, um darauf herumzustampfen. Hierdurch wurden die Weizenkörner aus den Garben gelöst. Nun trennte man das Korn von der Spreu und anderen Verunreinigungen, indem man es siebte oder indem man den Weizen in die Luft warf. Der Wind nahm dann die leichtere Spreu mit, der schwerere Weizen fiel auf den Boden. Nach dieser Bearbeitung des Getreides brachte man es in @5Silos. Dort wurde der Weizen zu Mehl verarbeitet und für die zukünftige Verwendung gelagert.  @L@LUm Brot herzustellen, machte man einen Teig aus Mehl und gab ihn in unterschiedliche gestaltete Keramikformen. Am beliebtesten war die konische Form. Der Teig samt Form wurde in einer Feuerstelle mit heißen Kohlen und Asche umgeben und gebacken. Brot wurde sowohl zu Hause als auch in professionellen Bäckereien gebacken. Archäologen vermuten, dass sich Berufsbäcker aufgrund der vielen Asche in der Luft möglicherweise nicht allzu guter Gesundheit erfreuten."
        }
    }
    message_history_cattle_ranching_and_fishing {
        id: 186,
        pos [0, 88]
        size [30, 20]
        image {
            id: 13,
            pos [15, 15]
        }
        title {
            text: "Rinderzucht und Fischerei",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Ägypter züchteten auf Farmen oder Bauernhöfen verschiedene Tiere, die ihnen als Nahrung dienten. Vor allem Langhornrinder waren sehr beliebt. Um das Vieh kümmerten sich Hirten, die in Grabkammerszenen immer als sehr hager und unrasiert dargestellt wurden. Zum Füttern trieb man die Rinder auf die Weide. Gelegentlich schickte man die Rinder auch auf Felder, die vor kurzem abgeerntet worden waren, damit sie Stroh und Spreu fraßen. @L@LDes Weiteren züchteten die Ägypter Schafe, Ziegen und Schweine sowie Gänse und anderes Geflügel. Pferde wurden ebenfalls gezüchtet - allerdings nicht, um sie zu schlachten, sondern um die Wagen der Adligen zu ziehen. Das Pferd kam erst im Gefolge von @181Invasoren nach Ägypten - die Hyksos brachten es mit. @L@LFisch diente als weitere Nahrungsquelle, obwohl er anscheinend hauptsächlich von der Unterschicht verzehrt wurde. Es gab verschiedene Arten, Fische zu fangen. Manche Ägypter fuhren in Booten aus und benutzten Angeln mit Angelhaken, um einen Fisch nach dem anderen zu fangen. Aber auch Fallen wurden gebaut, um gleich größere Mengen an Fisch zu fangen. Als effizienteste Fischfangmethode erwiesen sich jedoch Schleppnetze. Da man auf diese Weise enorm viele Fische fing, waren zwei Bootsbesatzungen nötig, um ein Schleppnetz an wieder die Oberfläche zu hieven. @L@LDas Fischen war nicht ganz ungefährlich. Eine bestimmte Wels-Art besaß eine Giftspitze auf der Rückenflosse, und natürlich drohte ständig Gefahr durch Krokodile. Die Fischer waren in ihren Booten zwar recht sicher, wenn das Boot jedoch kenterte, waren die Krokodile meist nicht fern."
        }
    }
    message_history_fruits_and_vegetables {
        id: 187,
        pos [0, 88]
        size [30, 20]
        image {
            id: 107,
            pos [15, 15]
        }
        title {
            text: "Obst und Gemüse",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die wichtigsten Nahrungsmittel im alten Ägypten waren @185Weizen&und&Gerste, kultiviert wurden aber auch verschiedene Obst- und Gemüsesorten. Bohnen, Kichererbsen, Linsen und grüne Erbsen waren sehr beliebt, genauso wie Knoblauch, Zwiebeln, Lauch, Kopfsalat und Gurken. An Obst verzehrte man Feigen, Datteln, Trauben und Granatäpfel. Insbesondere Datteln erfreuten sich großer Beliebtheit bei den unteren Klassen. Man verwendete sie auch, um Bier einen bestimmten Geschmack zu verleihen. An Gewürzen wurde Zimt, Koriander, Kreuzkümmel, Dill und Senf benutzt."
        }
    }
    message_history_reeds {
        id: 188,
        pos [0, 88]
        size [30, 20]
        image {
            id: 108,
            pos [15, 15]
        }
        title {
            text: "Papyrus, die Wunderpflanze",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Papryrusschilf, das bis zu 8 Meter hoch wuchs, wurde in Ägypten nicht nur für die Papierherstellung verwendet. Verschiedene Haushaltswaren wie z.B. Matten, Sandalen und Seile wurden ebenfalls daraus hergestellt. Das Mark der Pflanze wurde mit Genuss verzehrt. Manchmal verwendete man die Stiele der Pflanzen anstelle von Holz. Die Halme konnte man außerdem auch zusammenbinden und als Floß verwenden. Der Papyrus ist seit damals beinahe ausgestorben. Heute erfreut sich die Pflanze jedoch wieder neuer Beliebtheit. Wieder wird Papyrus nun geerntet und zu Papier verarbeitet - nur diesmal wird es an Touristen verkauft."
        }
    }
    message_history_flax {
        id: 189,
        pos [0, 88]
        size [30, 20]
        image {
            id: 109,
            pos [15, 15]
        }
        title {
            text: "Flachs",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Flachs wurde angebaut, um @398Leinen, den wichtigsten Stoff im alten Ägypten, herzustellen. Da der Stiel der wichtigste Teil der Pflanze war, musste jede Pflanze einzeln aus dem Boden gezogen wurde, so dass die Flachsernte eine sehr zeitaufwendige Angelegenheit war. Sobald der Flachs geerntet war, wurden die Wurzeln und Samenkapseln entfernt und die Stiele zum Trocknen ausgebreitet. Danach wurden sie zwei Wochen lang in Wasser eingelegt, mit Steinen gedroschen und dann in einzelne Fasern zerteilt. Die Fasern wurden dann zum Weber gebracht, um zu Stoff gewoben zu werden."
        }
    }
    message_history_clay {
        id: 190,
        pos [0, 88]
        size [30, 20]
        image {
            id: 110,
            pos [15, 15]
        }
        title {
            text: "Tongrube",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ton kam im alten Ägypten in rauen Mengen vor, nur die Qualität variierte je nach Gegend. Entlang des Nils waren durch die jahrelangen regelmäßigen Überschwemmungen reiche Schlammablagerungen entstanden, die man nur ausgraben und zu Tongeschirr formen musste. In den Wüstenregionen konnte man Adern weichen Mergels und Schiefertons finden, die sich durch den Kalkstein zogen. Ton aus der Wüste konnte zu härterem Tongeschirr verarbeitet werden als solcher vom Nil. Die Töpferwaren hatten in diesem Fall einen rosa oder grünen Farbton. Töpferwaren aus Nil-Ton waren dagegen eher rot oder schwarz. Beide Arten von Ton wurden auf gleiche Weise zu @198Geschirr verarbeitet."
        }
    }
    message_history_gold_and_gold_mining {
        id: 191,
        pos [0, 88]
        size [30, 20]
        image {
            id: 22,
            pos [15, 15]
        }
        title {
            text: "Gold und Goldbergwerke",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Gold fand man vor allem in der östlichen Wüste Ägyptens und in Nubien. Der Goldbergbau war dabei eine äußerst mühsame Arbeit. In der östlichen Wüste durchzogen Goldadern beispielsweise häufig Granitgestein. Der Granit wurde hier herausgehauen, mit dem Meißel zu Pulver zerkleinert und dann in Wasser getaucht, um das Gold vom Gestein zu trennen. Dieser Vorgang war mit Sicherheit äußerst zeitaufwendig. Gold kam jedoch in relativ großen Mengen vor, es gab davon mehr als Silber. @L@LUm Gold für die Verarbeitung vorzubereiten, schmolz man es zuerst in den Goldbergwerken ein. Nachdem man es geschmolzen hatte, goss man es in Wasser. Beim Abkühlen entstanden Goldklumpen, die Goldschmiede dann weiterverarbeiteten. @L@LWie fast jede andere Ware wurde auch der Goldbestand streng von Schreibern überwacht. Sorgfältig wogen sie jeden Morgen das Gold ab, das die Schmiede zur Arbeit bekamen, und ihre Arbeit wurde genau überwacht, damit sie kein Gold stahlen.  @L@LZwar gab es mehr Gold als Silber, das heißt aber nicht, dass Gold in Unmengen verfügbar war. Aus diesem Grund wurden die meisten Gegenstände nur mit Gold überzogen und nicht aus reinem Gold gefertigt."
        }
    }
    message_history_wood_and_its_uses {
        id: 192,
        pos [0, 88]
        size [30, 20]
        image {
            id: 111,
            pos [15, 15]
        }
        title {
            text: "Holz und seine Verwendung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "In Ägypten gab es nicht allzu viele einheimische Bäume. Zwar wäre die Erde auf den Überflutungsflächen durchaus fruchtbar genug für Bäume gewesen, die Flut jedoch entwurzelte die Bäume wieder, bevor sie fest genug angewachsen waren. Zu den Bäumen, denen es in Ägypten trotzdem gelang zu wachsen, gehört die Sykomore, die Tamariske, die Dattelpalme und die Dum-Palme. Jedem dieser Bäume kam eine religiöse Bedeutung zu. Sie wurden als Wohnsitz der Götter betrachtet. @L@LAufgrund dieser besonderen Bedeutung mussten Holzfäller spezielle Genehmigungen einholen, bevor sie einen Baum fällen durften. Die gefällten Bäume besaßen jedoch nur recht brüchiges Holz, dessen Verwendungsmöglichkeiten sich in engen Grenzen hielten. Ägypten importierte einen Großteil seines Holzes aus Gebieten, die heute der Libanon, Syrien und Israel sind. Als Ägypten diese Länder während des Neuen Reichs eroberte, wurden so viele Bäume geschlagen, dass sich der Baumbestand spürbar reduzierte. @L@LHolz wurde für Möbel, Särge und Gebäude verwendet, und die Schreiner waren sehr geschickt bei der Herstellung kunstvoller Werke mit Intarsien und Gravuren."
        }
    }
    message_history_quarries {
        id: 193,
        pos [0, 88]
        size [30, 20]
        image {
            id: 112,
            pos [15, 15]
        }
        title {
            text: "Steinbrüche",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Für den Bau von Pyramiden, Tempeln und Monumenten brach man in Ägypten viele Arten von Stein: Kalkstein, Granit, Sandstein, Basalt, Schiefer, Alabaster und Porphyr. Arbeiter im Steinbruch waren mit Spitzhacken und Meißeln für harte Steinarten und Kupfersägen für weicheren Stein ausgestattet. @L@LDie meisten Steinbrüche waren nur während der Überschwemmung in Betrieb, also während der Zeit, zu der die meisten staatlichen Bauprojekte durchgeführt wurden. Einige Steinbrüche waren jedoch auch das ganze Jahr hindurch in Betrieb, und zwar vor allem dann, wenn an einem besonders großen Projekt wie z.B. einer Pyramide gearbeitet wurde. @L@LUm die Steinblöcke an ihren Bestimmungsort zu befördern, setzte man die Blöcke auf eine Art Schlitten, der von mehreren Arbeitern gezogen wurde. Häufig verwendete man Baumstämme, um das Rollen zu erleichtern. Und um die Reibung zu verringern, wurde vor den Schlitten manchmal Wasser auf den Boden gegossen. @L@LDie Arbeit in den Steinbrüchen wurde zum Teil von Sklaven verrichtet, der weitaus größere Teil der Arbeiterschaft jedoch bestand aus Ägyptern."
        }
    }
    message_history_beer {
        id: 194,
        pos [0, 88]
        size [30, 20]
        image {
            id: 113,
            pos [15, 15]
        }
        title {
            text: "Bier",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Bier war das bevorzugte Getränk der alten Ägypter. Was jedoch die genauen Einzelheiten der ägyptischen Bierherstellung angeht, so werden darüber noch immer heftige Debatten geführt. Wie wurde das Bier gebraut? Wurden ihm mit Früchten verschiedene Geschmacksrichtungen gegeben? Stellten die Ägypter Gersten- oder Weizenbiere her? Und wie war das mit dem Malz? All diese Themen werden zur Zeit noch immer eifrig erforscht. @L@LWenn man den Wandmalereien in diversen Grabkammern Glauben schenken darf, so scheint man damals, zumindest für eine Methode des Bierbrauens, eine besondere Art von Brot gebacken zu haben. Dieses Brot wurde zerstoßen und in ein Sieb gelegt. Dann wurde Wasser durch die Brotmasse gedrückt. Die so entstandene Flüssigkeit füllte man anschließend in Flaschen ab und ließ sie gären. Das Bierbrauen war vor allem Frauenarbeit. Und etwa 17 Sorten Bier wurden auf verschiedenen Papyri identifiziert. @L@LDie Ägypter tranken ihr Bier aus speziellen Krügen. Diese Krüge waren mit einem schrägen Rohr ausgestattet - das fast wie ein Strohhalm aussah. Am Ende des Röhrchens befand sich ein Filter, der alle Feststoffe herausfilterte, die möglicherweise noch im Bier verblieben waren. Ägypter tranken Bier aber nicht nur zu Hause, sondern auch in Tavernen und Gasthäusern. Näheres über diese Art von Kneipen finden Sie @172hier."
        }
    }
    message_history_papyrus_making {
        id: 195,
        pos [0, 88]
        size [30, 20]
        image {
            id: 48,
            pos [15, 15]
        }
        title {
            text: "Papyrus-Herstellung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Herstellung von Papyrus war eine ziemlich komplizierte Angelegenheit. Zunächst entfernte man die Stiele, um an das Mark zu kommen. Das Mark mehrerer Pflanzen legte man auf einem Stück Stoff so übereinander, dass es leicht überlappte. Sobald man die gewünschte Breite erreicht hatte, legte man weitere Markstreifen im rechten Winkel über die erste Schicht. Dann legte man ein zweites Stück Stoff darüber und schlug mit einem schweren Holzscheit oder mit einem Hammer auf das Mark. Auf diese Art wurden die Markschichten quasi miteinander verschweißt. Anschließend wurde der Papyrus in der Sonne zum Trocknen aufgehängt. Häufig polierte man die Papieroberfläche zum Abschluss auch noch mit einem Stein."
        }
    }
    message_history_weapons {
        id: 196,
        pos [0, 88]
        size [30, 20]
        image {
            id: 114,
            pos [15, 15]
        }
        title {
            text: "Waffen",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die alten Ägypter nutzten viele verschiedene Waffen im Kampf. Für den Nahkampf verwendeten Soldaten Waffen wie Knüppel, Dolche, Breitschwerter und Streitäxte. Die wichtigsten Waffen für den Kampf auf größere Entfernung waren Pfeil und Bogen, aber auch Schleudern scheinen benutzt worden zu sein. Das Waffenarsenal der Ägypter entwickelte sich im Lauf der Zeit immer weiter. Eine große Erweiterung erfuhr es vor allem nach der Invasion der Hyksos, denn diese ergänzten die ägyptische Kriegführung mit Pferd und Wagen."
        }
    }
    message_history_luxury_goods {
        id: 197,
        pos [0, 88]
        size [30, 20]
        image {
            id: 115,
            pos [15, 15]
        }
        title {
            text: "Luxuswaren",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Nahrung, Getränke und Kleidung waren für Bauern genug, aber die oberen Schichten des alten Ägypten benötigten eine Vielzahl von Produkten, um ihren Lebensstil halten zu können. Besonders wichtig war dabei das Make-up. Sowohl Männer als auch Frauen schminkten sich die Augen mit Antimonpulver oder Malachit. Das diente nicht nur kosmetischen Zwecken, denn man glaubte auch, dass das Augen-Make-up die Sehkraft schützte. Frauen verwendeten darüber hinaus Henna als Nagelpolitur und gelegentlich auch als Haarfarbe. @L@LSauberkeit war für die alten Ägypter äußerst wichtig. So badeten sie nicht nur regelmäßig, sondern parfümierten sich auch mit verschiedenen Ölen und Extrakten. Dabei kann sowohl Myrrhe als auch Weihrauch zur Anwendung. @L@LMit der Sauberkeit hing auch das Tragen von Perücken zusammen. Die meisten Ägypter trugen ihr Haar kurz geschoren, vielleicht, um einen Befall durch Läuse zu verhindern. Stattdessen schmückten sie ihre Häupter mit Perücken. Diese gab es in verschiedenen Ausführungen, und die meisten Frauen besaßen mehr als nur eine. Perücken wurden meist aus Menschenhaar hergestellt, das mit Fäden am Untermaterial befestigt war. @L@L@382Schmuck war ein weiterer Luxus, den sich reiche Bürger leisteten."
        }
    }
    message_history_pottery {
        id: 198,
        pos [0, 88]
        size [30, 20]
        image {
            id: 25,
            pos [15, 15]
        }
        title {
            text: "Töpferwaren",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Kaum ein Heim kam ohne einen Vorrat an Geschirr aus. Bei der Töpferei handelt es sich um eines der ältesten Gewerbe in Ägypten. Ursprünglich wurden Töpferwaren zu Hause hergestellt, wo die Frauen jene Behältnisse selbst formten, die sie zum Kochen benötigten. Genau wie andere Gewerbe in Ägypten wurde auch das Herstellen von Töpferwaren später in Werkstätten verlegt. @L@LDer erste Schritt für die Herstellung von Töpferwaren war die Vorbereitung des @190Tons. Dieser musste geknetet werden, und häufig wurde Stroh oder Spreu hinzugefügt, um ihn fester zu machen. Männer kneteten den Ton mit den Händen oder stampften ihn mit den Füßen, um ihn für die Verarbeitung vorzubereiten. Dann wurde der Ton auf eine Töpferscheibe gelegt, um ihm eine Form zu geben. @L@LDie Töpferscheibe entwickelte sich im Laufe der Zeit immer weiter. In ihrer ursprünglichen Form drehte der Töpfer die Scheibe mit einer Hand, während er den Ton mit der anderen Hand formte. Da der Töpfer die Scheibe nicht sehr schnell drehen konnte, musste das Geschirr später mit der Hand geglättet werden. Während der Zeit des Neuen Reichs drehte eine zweite Person die Scheibe mit beiden Händen, während der Töpfer den Behälter formte. Dies ergab ein deutlich glatteres Endprodukt. Gegen Ende des Neuen Reichs drehte der Töpfer seine Töpferscheibe wieder selbst, diesmal jedoch mit den Füßen. Dies ergab noch glattere Töpferwaren. @L@LNach dem Formen ließ man die Gefäße trocknen, und noch während des Trockenvorgangs wurden die Dekorationen aufgebracht. Nach dem Trocknen wurden die Gefäße in einem speziellen großen Ofen gebrannt, der eine Feuerkammer an der Basis hatte. Die Feuerkammer war durch ein Tongitter von der oberen Kammer getrennt. Auf dieses Gitter wurden die Töpferwaren gestellt. Mit Ausnahme einer Öffnung, durch die der Rauch abziehen konnte, wurde die obere Kammer dann völlig verschlossen. Nach Abschluss des Brennvorgangs war das Produkt fertig und wurde gelagert, bis es gebraucht wurde."
        }
    }
    message_history_bazaar {
        id: 199,
        pos [0, 88]
        size [30, 20]
        image {
            id: 116,
            pos [15, 15]
        }
        title {
            text: "Basare",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Basare waren laute Orte, an denen sich viele Menschen drängten. Ladeninhaber - sowohl Männer als auch Frauen - stellten ihre Waren aus. Potentielle Käufer kamen mit anderen Waren auf den Markt, um sie gegen die angebotenen Waren zu tauschen. Meist befanden sich die Basare in der Nähe des Nils, da neue Waren oft per Schiff angeliefert wurden. @L@LBasarszenen wurden häufig auf Wandmalereien in Grabkammern abgebildet. Im Grab von Chnumhotep und Nianchchnum, Maniküristen des Pharao, aus der Zeit der fünften Dynastie, ist eine lebhafte Marktszene abgebildet, komplett mit einem dressierten Affen, der einen Möchtegern-Ladendieb in den Knöchel beißt."
        }
    }
    message_history_nubt {
        id: 200,
        type: 3,
        size [40, 30]
        title {
            text: "Nubt",
            pos [50, 80]
        }
        subtitle {
            text: "Ein Dorf entsteht",
            pos [10, 30]
        }
        content {
            text: "@PWillkommen im alten Ägypten, dem Land der Pharaonen! Sie greifen in diesem Spiel in den Lauf der Geschichte ein, in die Entwicklung einer der größten Zivilisationen, die die Welt je gesehen hat, und erleben ein Epos, das sich über mehr als 15 Jahrhunderte und 50 Generationen erstreckt. Sie lenken die Geschicke einer Familie von Generation zu Generation, von den ersten Anfängen im ägyptischen Altertum an, über die aufkeimende Zivilisation ... bis zur Errichtung eines einzigartigen, mächtigen Reiches ... und darüber hinaus.  @PIhre Geschichte beginnt an den Ufern des Nils, in einem Gebiet, das als Nubt bekannt ist. Den rauhen Lebensbedingungen trotzend kämpft dort eine Gemeinschaft von Klans ums Überleben. Mit Ihnen als Oberhaupt steht Ihre Familie an der Spitze dieser kleinen Siedlung."
        }
    }
    message_history_thinis_2 {
        id: 201,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Anfänge der Zivilisation",
            pos [10, 30]
        }
        content {
            text: "@PNach vielen Jahren - und eine Generation später - hat sich Ihre Familie im Gebiet von Thinis in Oberägypten neu niedergelassen. Hier versucht eine kleine Gruppe lokaler Regenten ihren Einfluss über Unterägypten und das Land längs des Nils auszuweiten, um das gesamte Gebiet unter ihrer Herrschaft und mit einem obersten Führer zu vereinen.  @PWenn Thinis zu einer blühenden Stadt wird, wie sie noch nie gesehen wurde, wird niemand mehr den Wert der thinitischen Föderation bestreiten und die Oberherrschaft dieser Regenten über Unterägypten und die anderen Teile, die um die Macht wetteifern, ernsthaft in Frage stellen. Das bedeutet, dass der Bevölkerung Unterhaltung geboten werden muss und prächtige Tempel zu Ehren der Schutzgötter der Region errichtet werden müssen. @PUm eine Stadt dieser Größe aufzubauen, benötigen Sie beträchtliche Geldmengen. In Thinis finden Sie reiche Goldadern. Diese auszubeuten, muss Ihr oberstes Ziel sein."
        }
    }
    message_history_perwadjyt {
        id: 202,
        type: 3,
        size [40, 30]
        title {
            text: "Perwadiut",
            pos [50, 80]
        }
        subtitle {
            text: "Der Nil und seine Gefahren",
            pos [10, 30]
        }
        content {
            text: "Der thinitische Adel kämpft noch immer darum, die Länder am Nil unter einem Herrscher zu vereinen. Man hegt die Hoffnung, dass Sie ihn bei diesem Bestreben unterstützen werden und sich darum bemühen, bei Perwadiut im feuchten Deltagebiet Unterägyptens ein blühendes Gemeinwesen aufzubauen, wodurch der Einfluss des Adels entlang des gesamten heiligen Flusses gestärkt würde. Um mehr als nur ein kleines Dorf zu ernähren, müssen Sie lernen, wie man Landwirtschaft betreibt. @LÄgyptische Bauern haben begonnen, den fruchtbaren Schlamm, der jedes Jahr nach der Überschwemmung des Nils zurückbleibt, zum Anbau von Pflanzen zu nutzen. Doch zahlreich sind auch die Gefahren, die am Nil lauern. An seinem Ufer und im Wasser wimmelt es von todbringenden Krokodilen, von Nilpferden und von Stechmücken, die Malaria übertragen."
        }
    }
    message_history_nekhen {
        id: 203,
        type: 3,
        size [40, 30]
        title {
            text: "Nechen",
            pos [50, 80]
        }
        subtitle {
            text: "Der erste Pharao",
            pos [10, 30]
        }
        content {
            text: "Während die Bevölkerung entlang des Nils den äußerst rauen Bedingungen trotzt und um das nackte Überleben kämpft, ist ein lokaler König namens Narmer an die Macht gekommen. Obgleich er über einen großen Teil des Landes herrscht, ist eine vollständige Vereinigung der beiden Königreiche noch lange nicht in Sicht. Narmer wünscht, dass zum Gedenken an seine Thronbesteigung Ihre Familie sich in Nechen niederlässt und hier eine neue Stadt errichtet und regiert. Die Stadt wird Tempel zu Ehren vieler ägyptischer Gottheiten und eine große Anzahl an Unterhaltungsstätten besitzen."
        }
    }
    message_history_men_nefer {
        id: 204,
        type: 3,
        size [40, 30]
        title {
            text: "Men-nefer",
            pos [50, 80]
        }
        subtitle {
            text: "Die Gründung einer Hauptstadt",
            pos [10, 30]
        }
        content {
            text: "Nach langem Kampf hat König Aha sein Ziel erreicht und die beiden Königreiche Unter- und Oberägypten vereinigt. Nun hat er sich zum Pharao über ganz Ägypten ernannt! Als Zeichen seiner absoluten Souveränität und zur Festigung der ersten ägyptischen Dynastie hat Aha die Gründung einer imposanten Hauptstadt bei Men-nefer angeordnet. Von hier aus will er seine aufstrebende Nation regieren. Da Ihre Familie dem Land bereits seit vielen Generationen treue Dienste leistet, hat der Pharao Sie als Architekten dieser herrlichen Stadt auserkoren. Und da die Hauptstadt das Symbol des Königreichs selbst ist, sollen die Bürger hier einen nie gekannten Lebensstandard genießen. Um dieses Ziel zu erreichen, müssen Sie im Laufe der Zeit Handelsbeziehungen mit anderen Städten des Reichs aufnehmen und zumindest einem Teil der Bevölkerung bessere Bildungsmöglichkeiten eröffnen. Darüber hinaus müssen Sie eine geweihte Mastaba für die Adligen der Stadt errichten."
        }
    }
    message_history_timna {
        id: 205,
        type: 3,
        size [40, 30]
        title {
            text: "Timna",
            pos [50, 80]
        }
        subtitle {
            text: "Eine Expedition nach Sinai",
            pos [10, 30]
        }
        content {
            text: "Mit Den hat ein neuer Pharao den ägyptischen Thron bestiegen. Der Pharao ist äußerst besorgt: Feinde bedrohen zunehmend unsere Grenzen, und unserem Staat mangelt es an wertvollem Kupfer, das wir zur Herstellung der Waffen für unsere Truppen benötigen. Pharao Den hat eine Bergbau-Expedition in die erbarmungslose Wüste Sinai angeordnet, ein Land jenseits unserer Grenzen und tief im Gebiet der Beduinen. In der Gegend, die unter dem Namen Timna bekannt ist, gibt es große Gold- und Kupfererzvorkommen sowie wertvolle Türkise. Ansonsten jedoch liegt das Land völlig brach. Unter durch und durch lebensfeindlichen Bedingungen werden Sie für diesen Vorposten der Zivilisation viele Dinge, möglicherweise sogar zusätzliche Nahrungsmittel, aus Ägypten importieren müssen. Der Pharao wird häufig Lieferungen aus dem Sinai verlangen. Sie werden ihm Geld, Kupfer, Edelsteine und Waffen liefern müssen. Etwaige Überschüsse dieser Waren können Sie dazu verwenden, die Expedition zu unterstützen. Seien Sie stets auf der Hut, denn die Beduinen der Wüste Sinai sind gefährliche Gegner und werden nicht tatenlos zusehen, wenn Fremde ihr Land besetzen und nicht einmal vor ihren Bodenschätzen Halt machen. @PUm die Last zu lindern, die solche Lebensbedingungen der Bevölkerung der Stadt auferlegen, sollten Sie einen Pavillon an einer belebten Kreuzung errichten. Die Bürger können sich dann bei Musik und Jongleursdarbietungen entspannen. Wenn Sie zusätzlich auch noch eine Tanzschule einrichten, wird diese neue Art der Zerstreuung für hervorragende Unterhaltung sorgen."
        }
    }
    message_history_behdet {
        id: 206,
        type: 3,
        size [40, 30]
        title {
            text: "Per-hebit",
            pos [50, 80]
        }
        subtitle {
            text: "Seestreitkräfte des Pharao",
            pos [10, 30]
        }
        content {
            text: "Das ägyptische Heer sucht in der bekannten Welt seinesgleichen, doch der neue Pharao, Chasechemui aus der zweiten Dynastie, fordert nun auch den Aufbau einer mächtigen Seestreitmacht mit Basis in Per-hebit. Um die Herrschaft über die Meere zu erringen, benötigen wir eine komplette Flotte an Kriegsschiffen. Es mangelt uns jedoch an Holz, da in unserem Klima Wald nur spärlich wächst. Doch wir können - wenn auch zu einem hohen Preis - Zedernholz von Byblos aus dem Libanon, einem Land im Nordosten, importieren. Zum Glück können wir diese Kosten durch Papyrusexporte wieder etwas ausgleichen."
        }
    }
    message_history_abedju {
        id: 207,
        type: 3,
        size [40, 30]
        title {
            text: "Abedju",
            pos [50, 80]
        }
        subtitle {
            text: "Das Meer und die Macht",
            pos [10, 30]
        }
        content {
            text: "Abjedu, der Friedhof unserer Vorfahren, hat sich im Laufe der Jahre zu einer großen Nekropole heiliger Grabstätten entwickelt. Nun möchten die meisten Adligen hier ihre letzte Ruhe finden. Zu ihren Ehren hat der neue Pharao, Chasechemui aus der zweiten Dynastie, den Bau dreier heiliger Mastabas für die hiesigen Edelleute angeordnet. Eine Mastaba soll größer sein als die beiden anderen.  @L@LDarüber hinaus hat der Pharao den Aufbau einer mächtigen Seestreitmacht mit Basis in Per-hebit angeordnet. Abjedu muss ebenfalls eine bescheidene Flotte an Kriegsschiffen unterhalten, um die absolute Sicherheit unserer Küsten zu gewährleisten. Das wird keine leichte Aufgabe sein, denn es mangelt uns an Holz, da unser Klima nur einen geringen Waldbestand gestattet. Doch wir können - wenn auch zu einem hohen Preis - Zedernholz von Byblos aus dem Libanon, einem Land im Nordosten, importieren. Zum Glück können wir diese Kosten durch Papyrusexporte wieder etwas ausgleichen."
        }
    }
    message_history_selima {
        id: 208,
        type: 3,
        size [40, 30]
        title {
            text: "Selime",
            pos [50, 80]
        }
        subtitle {
            text: "Die Straße nach Afrika",
            pos [10, 30]
        }
        content {
            text: "@PMit Nebkare hat ein neuer Pharao den Thron bestiegen und die dritte Dynastie der ägyptischen Herrscher begonnen. Nebkare hat Ägypten neu organisiert und strukturiert, indem er die Aufteilung des gesamten Reichs in Distrikte, in so genannte Nomes, angeordnet hat. Jeder Nomes wird von einem lokalen Herrscher, dem Nomarchen, regiert. So starr dieses System auch wirkt, es trägt doch dazu bei, dass unter Nebkares Herrschaft Ägypten wächst und gedeiht und dass große Errungenschaften in den Bereichen Kunst und Architektur erzielt werden. @L@PHändlerkarawanen aus dem tiefsten Afrika, die von Oase zu Oase ziehen, bringen jetzt viele seltene und exotische Luxuswaren nach Ägypten, die unser Volk heute nicht mehr missen möchte. Leider werden diese Karawanen regelmäßig von libyschen Kriegern und sogar von Beduinen aus der Wüste im Osten angegriffen. Um diese Handelswege zu sichern, wünscht Pharao Nebkare, dass Sie einen Militärposten in der Oase Selime errichten, dem Dreh- und Angelpunkt des Karawanenhandels weit jenseits der Grenzen unseres Reichs.  @L@PDort werden Sie Bäume finden, die sich zur Abholzung eignen. Die Einkünfte aus dem Verkauf des Holzes werden Ihnen dabei helfen, diesen Vorposten einzurichten. Für das Schmieden von Waffen dürfen Sie Kupfer aus unseren neu errichteten Minen in Timna, das im Lande Sinai liegt, importieren. @L@PVon der Oase Selime aus können Sie Ebenholz aus dem Land Kerma in Afrika importieren. Wenn es Ihnen gelingt, diesen Außenposten zu befestigen, wird er eine nie versiegende Ebenholzquelle für alle Städte in unserem Reich darstellen."
        }
    }
    message_history_abu {
        id: 209,
        type: 3,
        size [40, 30]
        title {
            text: "Abu",
            pos [50, 80]
        }
        subtitle {
            text: "Die nubische Grenze",
            pos [10, 30]
        }
        content {
            text: "@PMit Nebkare hat ein neuer Pharao den Thron bestiegen und die dritte Dynastie der ägyptischen Herrscher begonnen. Nebkare hat Ägypten neu organisiert und strukturiert, indem er die Aufteilung des gesamten Reichs in Distrikte, in so genannte Nomes, angeordnet hat. Jeder Nomes wird von einem lokalen Herrscher, dem Nomarchen, regiert. So starr dieses System auch wirkt, es trägt doch dazu bei, dass unter Nebkares Herrschaft Ägypten wächst und gedeiht und dass große Errungenschaften in den Bereichen Kunst und Architektur erzielt werden.  @PDer Pharao wünscht, die Grenzen unseres Reiches weiter nach Süden, nach Nubien hinein, auszudehnen. Er hat die Gründung einer Stadt am ersten Katarakt des Nils verfügt, auf der Insel Abu, damit wir die immensen Vorräte an Edelsteinen, Granit und Sandstein abbauen können, die dort zu finden sind.  @PDiese Materialien werden für die stetig größer werdende Nekropole Abjedu benötigt, damit immer noch kunstvollere Grabmäler für den Adel errichtet werden können. Die Hauptstadt bei Men-nefer könnte auch Ziegel für den Bau von Grabmälern benötigen. Pharao Nebkare wird möglicherweise Forderungen nach solchen und anderen Baumaterialien genehmigen.  @PPharao Nebkare hat darüber hinaus angeordnet, dass ein Ihnen Gleichrangiger einen Militärposten in der Oase Selime errichten soll, um die Karawanenstraßen ins Innere Afrikas zu sichern. Sobald dieser Vorposten steht, kann von dort aus Ebenholz, ein wertvolles und sehr geschätztes Luxusgut, importiert werden."
        }
    }
    message_history_saqqara {
        id: 210,
        type: 3,
        size [40, 30]
        title {
            text: "Saqqara",
            pos [50, 80]
        }
        subtitle {
            text: "Die erste Pyramide",
            pos [10, 30]
        }
        content {
            text: "Die Thronbesteigung von Pharao Djoser hat eine neue Ära der Weisheit, Gelehrsamkeit und Kunst eingeleitet. Ein königlicher Friedhof soll in Saqqara eingerichtet werden und als letzte Ruhestätte für Adlige wie Hesire und Chabausokar, die Vertrauten und Höflinge des Pharao, dienen.  @PAn diesem Ort soll auch ein Monument entstehen, wie es die Welt noch nie gesehen hat. Ich, Imhotep, königlicher Wesir des Pharao, habe eine neue Form eines heiligen Grabmals für den Pharao entworfen. Im Gegensatz zu den niedrigen Ziegelmastabas einstiger Pharaonen soll dieses Grabmal in den Himmel ragen, als bestünde es aus mehreren Mastabas übereinander. Des Weiteren soll diese 'Stufenpyramide' vollständig aus Stein bestehen, damit ihr der Lauf der Zeiten nichts anhaben kann. Tief im Innern der Pyramide soll ein Sarkophag aus reinem Granit den Körper des Pharao in seiner ewigen Ruhe schützen. @PPriester der Nekropole von Abjedu haben die Kunst perfektioniert, die Toten mit Hilfe von Leinen einzubalsamieren, so dass allen Ägyptern nun das Tor zum ewigen Leben offen steht.  @PUnser Handelsposten in der Oase Selime blüht und gedeiht weiterhin. Von dort aus können Sie Ebenholz aus Afrika importieren.  @PDer Pharao hat Ihnen für dieses Projekt einen großzügigen finanziellen Vorschuss gegeben. Enttäuschen Sie ihn nicht."
        }
    }
    message_history_serabit_khadim {
        id: 211,
        type: 3,
        size [40, 30]
        title {
            text: "Serabit el-Chadim",
            pos [50, 80]
        }
        subtitle {
            text: "Die Beduinen des Ostens",
            pos [10, 30]
        }
        content {
            text: "Wie bereits Pharao Den vor ihm hat Pharao Huni eine Expedition in die raue Landschaft des Sinai angeordnet, um Türkise und Kupfer zu beschaffen. Er wünscht, dass diese Expedition unter Ihrer Führung zu einem Ort namens Serabit el-Chadim aufbricht. Hier gibt es noch Überreste eines früheren ägyptischen Außenpostens. Sein derzeitiger Zustand ist zwar unbekannt, doch man geht davon aus, dass er der Expedition noch ein gewisses Maß an Schutz bieten müsste.  @PSie sollten auch wissen, dass die Expedition, die sich zuletzt dorthin aufgemacht hat, nie zurückgekehrt ist. Nicht anders erging es einer späteren Expedition, die sich auf die Suche nach den Verschollenen begeben hatte. Dennoch, wenn wir unsere Soldaten ausreichend mit Waffen versorgen wollen, müssen wir uns das Kupfer dafür dort besorgen, denn in unserem Land gibt es nicht genug davon. @PBereiten Sie sich gut vor, denn Sie müssen immer mit Angriffen der Beduinen aus dem Sinai und der Kanaaniter, unseren Feinden, rechnen. Fördern Sie so viel Kupfer und Edelsteine, wie dies unter diesen Bedingungen möglich ist, und erfüllen Sie umgehend die Forderungen des Pharao. Sie können Juweliere einstellen, die aus den übrigen Edelsteinen Schmuck für die Bewohner der Siedlung fertigen."
        }
    }
    message_history_meidum {
        id: 212,
        type: 3,
        size [40, 30]
        title {
            text: "Medum",
            pos [50, 80]
        }
        subtitle {
            text: "Eine königliche Nekropole",
            pos [10, 30]
        }
        content {
            text: "Pharao Huni wünscht, die Ewigkeit in einer Stufenpyramide zu verbringen, wie bereits Djoser vor ihm. Die Pyramide soll von den Gräbern seiner Gefolgsleute umgeben sein und in Medum in Unterägypten stehen.  @PAls Zeichen der Dankbarkeit für die treuen Dienste Ihres Hauses über viele Generationen hinweg erweist Huni Ihnen die Gunst, sich in einem eigenen Grabmal in Medum beerdigen zu lassen. Damit hat er Ihrer Familie eine große Ehre erwiesen. @PUm zu gewährleisten, dass die Weisheit und die Kenntnisse Ägyptens nicht im Laufe der Zeit der Vergessenheit anheim fallen, drängt Pharao Huni auf den Bau königlicher Bibliotheken. Stapeln sich darin erst einmal die Papyrusrollen, werden die oberen Klassen der Gesellschaft auch in den Genuss einer höheren Bildung kommen.  @PDer Pharao hat einen weiteren seiner treuen Höflinge auf eine Expedition nach Serabit el-Chadim ins unwirtliche Land des Sinai entsandt, um Türkise zu holen. Sollte die Expedition von Erfolg gekrönt sein, können Sie sich darauf freuen, Edelsteine von dort zu importieren. Juweliere können daraus Schmuck, ein wertvolles Luxusgut für die Stadtbevölkerung, herstellen. @PDas einst blühende Per-hebit steht vor dem Untergang und exportiert viele Waren nicht mehr, die einst den Ruf der Stadt begründeten."
        }
    }
    message_history_buhen {
        id: 213,
        type: 3,
        size [40, 30]
        title {
            text: "Buhen",
            pos [50, 80]
        }
        subtitle {
            text: "Expansion nach Nubien",
            pos [10, 30]
        }
        content {
            text: "Unser neuer Pharao Snofru ist entschlossen, die vierte Dynastie als die größte Dynastie in die Geschichte eingehen zu lassen, die Ägypten je regiert hat. Er wünscht, dass unsere Grenzen noch weiter nach Süden ausgedehnt werden. Daher gab er den Befehl zum Angriff auf Nubien und zur Errichtung einer befestigten Stadt bei Buhen neben dem zweiten Nilkatarakt. Dort soll ein weithin sichtbarer Obelisk aus Granit errichtet werden, zum Zeichen, dass diese Gegend auf ewig Ägypten und dem Pharao gehört. So weit im Süden gibt es jedoch keinen Granit, daher müssen Sie ihn aus Abu importieren.  @PBei Buhen werden Sie auf wilde und erfahrene nubische Krieger stoßen, die bis zum Tod kämpfen werden, um zu verhindern, dass wir so weit im Süden Fuß fassen. Lassen Sie sich davon jedoch nicht entmutigen, denn nach der strengen Ausbildung an der Militärakademie brauchen Ihre Kämpfer niemanden zu fürchten. Außerdem haben unsere Festungsbaumeister alles dafür getan, unsere Verteidigungseinrichtungen wie z.B. befestigte Türme, Mauern und Stadttore unüberwindlich zu machen. Dies werden Sie spätestens dann zu schätzen wissen, wenn die ersten Wellen des nubischen Angriffs heranrollen. Transportschiffe können eingesetzt werden, um Ihre Armee, falls erforderlich, auf dem Seewege zu verlegen.  @PIm Norden haben wir Beziehungen mit Enkomi auf der Insel Zypern aufgenommen. Dieses Land ist für seine unerschöpflichen Vorkommen an Kupfererz bekannt, das wir nun von dort erwerben können. Dank der kürzlich etablierten ägyptischen Bergbaustadt bei Serabit el-Chadim im Lande Sinai können wir unseren Gouverneuren jedoch Kupfer zu einem weitaus günstigeren Preis anbieten. Diese Lieferungen sind allerdings aufgrund der nicht nachlassenden Angriffe von Beduinen und Kanaanitern auf Serabit el-Chadim starken Schwankungen unterworfen, und wir wissen nicht, wie lange die dort stationierten ägyptischen Streitkräfte noch ausharren können.  @PDas Grabmal des Pharao, ein einzigartiges und spektakuläres Monument, wird derzeit in Dahschur errichtet. Von Zeit zu Zeit wird der Pharao möglicherweise eine Lieferung Kalkstein für dieses Projekt anfordern."
        }
    }
    message_history_south_dahshur {
        id: 214,
        type: 3,
        size [40, 30]
        title {
            text: "Süd-Dahschur",
            pos [50, 80]
        }
        subtitle {
            text: "Die Knickpyramide des Snofru",
            pos [10, 30]
        }
        content {
            text: "Unser neuer Pharao Snofru ist entschlossen, die vierte Dynastie als die größte Dynastie in die Geschichte eingehen zu lassen, die Ägypten je regiert hat. Seine Architekten haben ein Grabmal entworfen, das noch spektakulärer sein wird als die Stufenpyramide des Huni. Der Pharao möchte Ihnen die Bauaufsicht übertragen. Hierzu müssen Sie zunächst eine mittelgroße Siedlung im Süden von Dahschur aufbauen, dem Ort, an dem die Knickpyramide errichtet werden soll. Ist dies geschehen, können die Arbeitskräfte für dieses ehrgeizige Projekt aus der Siedlung rekrutiert werden. @PDie Knickpyramide soll aus einem einfachen Steinkern bestehen und mit feinem weißen Kalkstein verschalt werden, so dass sie für immer gleißend hell in der Wüstensonne leuchten wird. In Dahschur finden Sie ausreichend Kalkstein, Sie müssen aber den normalen Stein importieren. @PDer Pharao wünscht, dass unsere Grenzen noch weiter gen Süden ausgedehnt werden. Daher gab er den Befehl zum Angriff auf Nubien und zur Errichtung einer befestigten Stadt bei Buhen neben dem zweiten Nilkatarakt. @PIm Norden hat Ägypten Beziehungen mit Enkomi auf der Insel Zypern aufgenommen. Dieses Land ist für seine unerschöpflichen Vorkommen an Kupfererz bekannt, dessen Import von größter Bedeutung ist.  @PWertvolle Edelsteine können von einem kürzlich eingerichteten ägyptischen Außenposten in Serabit el-Chadim im Lande Sinai bezogen werden. Diese Lieferungen sind allerdings aufgrund der unerbittlichen Angriffe von Beduinen und Kanaanitern auf die Siedlung in letzter Zeit starken Schwankungen unterworfen, und wir wissen nicht, wie lange die dort stationierten ägyptischen Streitkräfte noch standhalten können."
        }
    }
    message_history_north_dahshur {
        id: 215,
        type: 3,
        size [40, 30]
        title {
            text: "Nord-Dahschur",
            pos [50, 80]
        }
        subtitle {
            text: "Die wahre Pyramide",
            pos [10, 30]
        }
        content {
            text: "@PPharao Snofru hat in Ägypten Ordnung einkehren lassen. Heute blüht das Königreich unter seiner weisen, gütigen Herrschaft. Snofru wünscht, in Dahschur ein weiteres Bauprojekt in Angriff zu nehmen, das noch ehrgeiziger sein soll als die Knickpyramide, die Sie bereits fertig gestellt haben. Königliche Architekten, Landvermesser und Ingenieure sind zuversichtlich, ein Gebäude errichten zu können, dessen Seiten gerade nach oben steigen und in eine perfekte Spitze münden. Sollte diesem Projekt Erfolg beschieden sein, wäre dies die erste echte Pyramide und für Pharao Snofru eine würdige Heimat in der Ewigkeit!  @PDie Frau des Pharao, Königin Hetepheres, hat vor kurzem einen Sohn geboren, der den Namen Cheops erhielt. Unserem Volk graut es vor dem Tag seines Regierungsantritts, denn die Seher des Horus, des Gottes des Pharao, haben vorhergesagt, dass er unserem Volk alles andere erweisen wird als die Güte seines Vaters. Während man sich einerseits Großes von ihm verspricht, fürchtet man andererseits, dass er Ägypten mit unnachgiebiger Hand regieren wird.  @PHolz können Sie aus Byblos beziehen. Die Zimmerleute werden große Mengen davon benötigen, um die vielen Rampen zu errichten, auf denen die Arbeiter die Spitze dieser großen Pyramide erklimmen können."
        }
    }
    message_history_iunet {
        id: 216,
        type: 3,
        size [40, 30]
        title {
            text: "Iunet",
            pos [50, 80]
        }
        subtitle {
            text: "Die Verteidigung Ägyptens",
            pos [10, 30]
        }
        content {
            text: "@PPharao Cheops hat den Thron bestiegen, und wie dies die Seher von Horus und Re vorhergesagt haben, stöhnt unser Volk bereits jetzt unter seiner Tyrannei.  @PCheops hat die Entsendung eines königlichen Gouverneurs nach Iunet befohlen, um unser Land gegen eindringende Kuschiter zu verteidigen. Iunet kann eine kleine Fischereiwirtschaft unterhalten, was die Siedlung eine Zeit lang ernähren dürfte. Wenn die Kuschiter jedoch auf dem Seeweg einfallen, kann der Fluss für Fischerboote gefährlich werden. Möglicherweise sollten dann die Ufergebiete besser zur Unterstützung einer Flotte von Kriegsschiffen eingesetzt werden. Sollte die Nahrung knapp werden, können Sie auch Rinder mästen, um Fleisch zu bekommen. Allerdings benötigen die Herden viel Stroh, und das ist in diesem Land nur schwer zu bekommen. Sie sollten daher andere Städte ausfindig machen, von denen Sie Stroh erhalten können, das Sie außerdem auch zur Herstellung von Ziegeln für Ihre Mastaba benötigen. @PDie Stadt Byblos im Libanon, dem Land der Zedern, hat begonnen, mit den mächtigen Imperien des Ostens Handel zu treiben. Dabei handelt es sich um Assyrien und Ur, die zwischen den beiden großen Flüssen in dem Land liegen, das man 'Mesopotamien' nennt. Feinstes Elfenbein aus diesen Orten können Sie über Byblos erwerben. Mit dem Eintreffen solch seltener, exotischer Luxuswaren wird Iunet gewiss aufblühen. @PIn der Hauptstadt erfreut sich Senet, ein neues Brettspiel, bei den Ägyptern immer größerer Beliebtheit. Dazu trifft man sich meist in einem öffentlichen Gebäude, dem so genannten 'Senet-Haus', und lässt sich dabei einen Krug Bier munden. An solchen Orten vergessen die Menschen von Iunet vorübergehend die Tyrannei des Cheops. @PDer Pharao hat befohlen, dass unzählige Steinbrüche in On, das im Deltagebiet liegt, eingerichtet werden sollen, um einen riesigen Vorrat herrlichen weißen Kalksteins zu fördern. Nur die Götter wissen, was er damit vorhaben mag. Gerüchten zufolge plant er ein monumentales Bauprojekt auf dem Plateau vor Rostia, um anmaßenderweise den Ruhm seines Vaters zu übertreffen, den dieser weise und gütige Herrscher durch den Bau seiner beiden herrlichen Pyramiden erworben hat."
        }
    }
    message_history_on {
        id: 217,
        type: 3,
        size [40, 30]
        title {
            text: "On",
            pos [50, 80]
        }
        subtitle {
            text: "Elfenbein aus dem Osten",
            pos [10, 30]
        }
        content {
            text: "@PPharao Cheops hat den Thron bestiegen, und wie dies die Seher von Horus und Re vorhergesagt haben, stöhnt unser Volk bereits jetzt unter seiner Tyrannei. Gerüchten zufolge plant er ein monumentales Bauprojekt auf dem Plateau vor Rostia, um den Ruhm seines Vaters zu übertrumpfen, den dieser weise und gütige Herrscher durch den Bau seiner beiden herrlichen Pyramiden erworben hat. @PPharao Cheops hat befohlen, dass einige Steinbrüche bei Tura im Deltagebiet eingerichtet werden, an einer Stelle, an der vor kurzem große Mengen herrlichen weißen Kalksteins entdeckt wurden. Darüber hinaus müssen Sie drei Mastabas für die Adligen dieser Region errichten, damit der Pharao deren Ergebenheit belohnen kann. Die Steinbruchsiedlung, die Sie aufgebaut haben, soll den Namen 'On' tragen. Sie wird für viele Jahre weißen Kalkstein in großen Mengen liefern können ... auch wenn nur die Götter wissen, was der Pharao damit vorhaben mag. @PDie Stadt Byblos im Libanon, dem Land der Zedern, hat begonnen, mit den mächtigen Imperien des Ostens Handel zu treiben. Dabei handelt es sich um Assyrien und Ur, die zwischen den beiden großen Flüssen in dem Land liegen, das man 'Mesopotamien' nennt. Feinstes Elfenbein aus diesen Orten können Sie über Byblos erwerben. Mit dem Eintreffen solch seltener, exotischer Luxuswaren wird On gewiss blühen und gedeihen. @PCheops hat die Entsendung eines königlichen Gouverneurs nach Iunet befohlen, um unser Land gegen eindringende Kuschiter zu verteidigen. Die königlichen Wesire bedauern den Gouverneur, der mit dieser schweren und gefährlichen Aufgabe betraut wurde.  @PIn der Hauptstadt erfreut sich Senet, ein neues Brettspiel, bei den Ägyptern immer größerer Beliebtheit. Dazu trifft man sich meist in einem öffentlichen Gebäude, dem so genannten 'Senet-Haus', und lässt sich dabei einen Krug Bier munden. An solchen Orten vergessen die Menschen von On vorübergehend die Tyrannei des Cheops."
        }
    }
    message_history_rostja {
        id: 218,
        type: 3,
        size [40, 30]
        title {
            text: "Rostia",
            pos [50, 80]
        }
        subtitle {
            text: "Die große Pyramide und die Sphinx",
            pos [10, 30]
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
            text: "Oase Baharija",
            pos [50, 80]
        }
        subtitle {
            text: "Die westliche Wüste",
            pos [10, 30]
        }
        content {
            text: "@PDie Herrschaft von Cheops und Chephren ist zu Ende. Mit ihnen endet auch die vierte Dynastie der ägyptischen Herrscherfamilien. Chentkaues, eine Verwandte aus einer Nebenlinie dieser Dynastie, hat einen neuen Pharao namens 'Userkaf' geboren, so dass das königliche Geschlecht in gerader Linie fortbesteht. Mit Userkaf beginnt die fünfte Dynastie, ein Zeitalter, mit dem große Veränderungen einhergehen werden.  @PUserkaf hat die Herrschaft über das Land etwas dezentralisiert und den regionalen Behörden mehr Macht zugestanden. Jetzt haben Nomarchen wie Sie größere Spielräume bei der Ausübung ihrer Regierungsgeschäfte. Dieser Pharao sinniert auch nicht über den Bau einer riesigen Pyramide nach, in der er ewige Ruhe finden kann. Ihn treiben ganz andere Pläne um. @PPharao Userkaf hat Re, den Gott der Sonne und des Königreichs, zum König der Götter erklärt und plant, seine Herrschaft im ganzen Land zu verkünden. Es gibt in Ägypten bereits viele Sonnentempel, doch der Pharao wünscht, den Einfluss des Re bis an den Rand des Königreichs auszudehnen. @PHierzu müssen Sie eine befestigte Siedlung in der Oase Baharija tief in der westlichen Wüste errichten. Nutzen Sie das Wasser, das Sie dort finden, sorgfältig, denn die geringen Wassermengen, auf die man in dieser Entfernung vom Nil noch stößt, werden auch von den wilden Tieren der Wüste sehr begehrt. Sie sollten sich außerdem vor Angriffen durch libysche Krieger und Beduinen in Acht nehmen, die in letzter Zeit den Wüstenkarawanen verstärkt nachstellten. Planen Sie Ihre Verteidigungsanlagen sorgfältig, und nutzen Sie alle Ressourcen wie Holz und Wild, die Sie in der Oase vorfinden."
        }
    }
    message_history_djedu {
        id: 220,
        type: 3,
        size [40, 30]
        title {
            text: "Djedu",
            pos [50, 80]
        }
        subtitle {
            text: "Der Sonnentempel",
            pos [10, 30]
        }
        content {
            text: "@PDie Herrschaft von Cheops und Chephren ist zu Ende. Mit ihnen endet auch die vierte Dynastie der ägyptischen Herrscherfamilien. Chentkaues, eine Verwandte aus einer Nebenlinie dieser Dynastie, hat einen neuen Pharao namens 'Userkaf' geboren, so dass das königliche Geschlecht in gerader Linie fortbesteht. Mit Userkaf beginnt die fünfte Dynastie, ein Zeitalter, das große Veränderungen mit sich bringen wird.  @PUserkaf hat die Herrschaft über das Land etwas dezentralisiert und den regionalen Behörden mehr Macht zugestanden. Jetzt haben Nomarchen wie Sie größere Spielräume bei der Ausübung ihrer Regierungsgeschäfte. Dieser Pharao sinniert auch nicht über den Bau einer riesigen Pyramide nach, in der er ewige Ruhe finden kann. Ihn treiben ganz andere Pläne um. @PPharao Userkaf hat Re, den Gott der Sonne und des Königreichs, zum König der Götter erklärt und plant, seine Herrschaft im ganzen Land zu verkünden. Es gibt in Ägypten bereits viele Sonnentempel, doch der Pharao wünscht, den größten Sonnentempel von allen in Djedu in der feuchten Deltaregion Unterägyptens zu errichten.  @PWie fast im gesamten Delta gibt es auch in Djedu große Mengen an Wild, Fisch und anderen Tieren sowie eine üppige Vegetation. Bodenschätze allerdings sind Mangelware. So müssen Sie den Sandstein, den Sie für den Bau des Sonnentempels benötigen, aus den Steinbrüchen von On heranschaffen. In Djedu können Sie Rinder züchten, um Fleisch zu erzeugen - allerdings brauchen die Herden viel Stroh als Futter. @PSie werden Land planieren müssen, um einen geeigneten Standort für den Sonnentempel vorzubereiten. Achten Sie darauf, genug, aber nicht zu viel von dem wertvollen Holz zu verkaufen, das Sie schlagen werden. Wenn es erst einmal weg ist, wird es möglicherweise schwierig, weiteres zu beschaffen. In Per-hebit und Abjedu braucht man stets Holz und Wild. Wenn Sie also mit diesen Städten Handel treiben, dürfte das dazu beitragen, die Aufwendungen für das Errichten des heiligen Monuments wieder hereinzuholen."
        }
    }
    message_history_dunqul {
        id: 221,
        type: 3,
        size [40, 30]
        title {
            text: "Dunqul",
            pos [50, 80]
        }
        subtitle {
            text: "Bedrohung durch die Kuschiter",
            pos [10, 30]
        }
        content {
            text: "@PPharao Pepi ist nun an die Macht gekommen und hat Ihrer Familie den Kanzlerstatus zuerkannt. Die zentralisierte Macht wird zunehmend ausgehöhlt, und regionale Herrscher werden immer mächtiger. Die Ernten in einigen Regionen fallen deutlich geringer aus als üblich, und langsam beginnt das Schreckgespenst einer Hungersnot in Ägypten umzugehen. Men-nefer, einst eine herrliche, schöne Stadt, ist dem Verfall preisgegeben. Seher sagen schwere Zeiten voraus. @PAus der zunehmenden Schwäche Ägyptens versuchen seine mächtigen Nachbarn Nutzen zu ziehen. Der Außenposten in Buhen wird von verwegenen kuschitischen Soldaten belagert, die aus Kerma geschickt wurden, der größten nichtägyptischen Stadt in ganz Afrika. Die Kuschiter verlangen Tributzahlungen, und die geringste Provokation könnte zu einem direkten Angriff führen. Nubien hat ebenfalls seine Männer zu den Waffen gerufen und will verlorenes Land zurückerobern.  @PWenn Ägypten überleben soll, müssen Sie alles in Ihrer Macht stehende tun, um Handelsrouten aufrechtzuerhalten, damit der Warenverkehr von und nach Ägypten nicht abreißt. Sorgen Sie dafür, dass der unter schweren Verlusten erkämpfte Handelsposten in der Oase Selime offen bleibt. Pepi, der sich immer mehr Gedanken um seine Reise ins Jenseits macht, wird häufig Stein für den Bau seiner Pyramide fordern. Andere Städte, denen es an Nahrungsmitteln mangelt, werden Sie um Unterstützung bitten. @PSetzen Sie Ihre Ressourcen mit Bedacht ein. In der Oase gibt es viel wertvolles Holz, aber ein Teil des Waldes muss zerstört werden, um Zugang zu den begrenzten Wasserressourcen zu erlangen."
        }
    }
    message_history_dakhla {
        id: 222,
        type: 3,
        size [40, 30]
        title {
            text: "Dachla",
            pos [50, 80]
        }
        subtitle {
            text: "Die Karawanenstraße",
            pos [10, 30]
        }
        content {
            text: "@PPharao Pepi ist nun an die Macht gekommen und hat Ihrer Familie den Kanzlerstatus zuerkannt. Die zentralisierte Macht wird zunehmend ausgehöhlt, und regionale Herrscher werden immer mächtiger. Die Ernten in einigen Regionen fallen deutlich geringer aus als üblich, und langsam beginnt das Schreckgespenst einer Hungersnot in Ägypten umzugehen. Men-nefer, einst eine herrliche, schöne Stadt, ist dem Verfall preisgegeben. Seher sagen schwere Zeiten voraus.  @PAus unserer zunehmenden Schwäche versuchen unsere mächtigen Nachbarn Nutzen zu ziehen. Unser Außenposten in Buhen wird von verwegenen kuschitischen Soldaten belagert, die aus Kerma geschickt wurden, der größten nichtägyptischen Stadt in ganz Afrika. Die Kuschiter verlangen Tributzahlungen, und die geringste Provokation könnte zu einem direkten Angriff führen. Nubien hat ebenfalls seine Männer zu den Waffen gerufen und will verlorenes Land zurückerobern.  @PVersuchen Sie, die Stabilität in Ägypten zu wahren, indem Sie einen Verwaltungsposten in der Oase Dachla einrichten. In der Oase gibt es einen großen Bestand an wertvollen Bäumen. Nur blockieren diese leider den Zugang zu den begrenzten Wasserreserven der Oase. Von diesem wichtigen Standort aus soll Ebenholz aus dem Inneren Afrikas importiert werden. Pepi, der sich immer mehr Gedanken um seine Reise ins Jenseits macht, wird Ziegel für den Bau seines Grabmals fordern. Andere Städte, denen es an Nahrungsmitteln mangelt, werden Sie um Unterstützung bitten."
        }
    }
    message_history_thinis {
        id: 223,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis ",
            pos [50, 80]
        }
        subtitle {
            text: "Der Bürgerkrieg",
            pos [10, 30]
        }
        content {
            text: "Nichts ist geblieben vom früheren Überfluss und Stolz, und die meisten Menschen fürchten, dass Ägypten nie wieder zu seiner einstigen Herrlichkeit zurückfinden wird. Osiris hat sich von seinem Volk abgewandt, und mehrere schwache Überflutungen nacheinander haben zu großen Hungersnöten geführt. Die Macht der Pharaonen, die früher nie in Frage gestellt wurde, ist nur noch ein matter Abglanz von einst. Stattdessen wird die politische Bühne nun von Provinzgouverneuren beherrscht, die sich gegenseitig ihre Einflussbereiche streitig machen. @PUnbeschadet aus diesem Chaos gingen zwei Adelsfamilien hervor, die versuchen, die Herrschaft über das Land an sich zu reißen. Die Herrscher von Henen-nesw haben ihre Ansprüche auf den Thron als rechtmäßige Erben angemeldet. Diese Familie ist bekannt für ihre Grausamkeit und weniger dafür, sich um den Hunger der Menschen zu kümmern. In Waset im Süden ist eine bislang unbedeutende Herrscherfamilie, das Haus Inyotef, an die Macht gekommen. Dieses Haus hat viel für die Wiedervereinigung des Südens getan. In dieser Konstellation entbrennt ein mörderischer Bürgerkrieg, angefacht von Henen-nesw, um die Herrschaft über ganz Ägypten. @PDarauf bedacht, für das Wohl des ägyptischen Volkes da zu sein, hat die Familie Inyotef Ihnen den Wiederaufbau der soeben eroberten Stadt Thinis anvertraut, einer der ältesten Städte Ägyptens. Zwei der herrlichsten und ältesten Gebäude von Thinis blieben während der Eroberung von Zerstörungen verschont: der Tempelkomplex des Osiris und das Herrenhaus. Die Familie Inyotef hat angeordnet, dass, sollte eines dieser Gebäude zerstört werden, keine Gelder für deren Restaurierung verschwendet würden. Die Herrscher von Waset räumen dem Wiederaufbau von Thinis oberste Priorität ein und haben ungeachtet der schlechten Zeiten großzügig Gelder für diesen Zweck bereitgestellt. Ihre Aufgabe ist es, den alten Glanz der Stadt Thinis wiederherzustellen, und eine Seestreitmacht und eine starke Armee aufzustellen, um die Stadt gegen die häufigen Angriffe derer zu verteidigen, die Hesen-nesw treu ergeben sind. Dazu zählen auch die Städte Sauty, Nechen und Chmun. Nehmen Sie sich vor den Herrschern der Familie Henen-nesw in Acht: Möglicherweise werden sie einen Tribut verlangen, um Ihnen Loyalität - und Ihre Deben - abzupressen. Sehen Sie sich auch vor den opportunistischen Nubiern vor, die die internen Kämpfe in Ägypten zu ihrem eigenen Vorteil nutzen wollen."
        }
    }
    message_history_waset {
        id: 224,
        type: 3,
        size [40, 30]
        title {
            text: "Waset",
            pos [50, 80]
        }
        subtitle {
            text: "Der Bürgerkrieg",
            pos [10, 30]
        }
        content {
            text: "Nichts ist geblieben vom früheren Überfluss und Stolz, und die meisten Menschen fürchten, dass Ägypten nie wieder zu seiner einstigen Herrlichkeit zurückfinden wird. Osiris hat sich von seinem Volk abgewandt, und mehrere schwache Überflutungen nacheinander haben zu großen Hungersnöten geführt. Die Macht der Pharaonen, die früher nie in Frage gestellt wurde, ist nur noch ein matter Abglanz von einst. Stattdessen wird die politische Bühne nun von Provinzgouverneuren beherrscht, die sich gegenseitig ihre Einflussbereiche streitig machen. @PUnbeschadet aus diesem Chaos gingen zwei Adelsfamilien hervor, die versuchen, die Herrschaft über das Land an sich zu reißen. Die Herrscher von Henen-nesw haben ihre Ansprüche auf den Thron als rechtmäßige Erben angemeldet. Diese Familie ist bekannt für ihre Grausamkeit und weniger dafür, sich um den Hunger der Menschen zu kümmern. In Waset im Süden ist eine bislang unbedeutende Herrscherfamilie, das Haus Inyotef, an die Macht gekommen. Das Haus hat viel für die Wiedervereinigung des Südens getan. In dieser Konstellation entbrennt ein mörderischer Bürgerkrieg, angefacht von den Herrschern der Henen-nesw-Dynastie, um die Herrschaft über ganz Ägypten. @PDie Familie Inyotef, die mit dem Kampf gegen die Herrscher von Henen-nesw beschäftigt ist, hat Sie mit dem Aufbau ihrer Heimatstadt Waset beauftragt. Um im Kampf gegen die Herrscher des Hauses Henen-nesw erfolgreich zu bestehen und um ihren Ruf in Ägypten zu festigen, müssen die Inyotefs Waset zu einem Dreh- und Angelpunkt machen, auf den sich andere Städte verlassen können und an den sie sich wenden, wenn sie Unterstützung oder Soldaten benötigen. Waset - möglicherweise einmal Hauptstadt, wenn die Familie Inyotef den Krieg gewinnen sollte - muss eine großartige Stadt werden. Mit den geringen Ressourcen, die Ihnen zur Verfügung stehen, haben Sie nun die Aufgabe, einen Sonnentempel und eine Pyramide zu errichten, um den Ägyptern die Herrlichkeit der Inyotefs zu beweisen. @PWaset selbst ist keineswegs von Angriffen ausgenommen. Die Herrscher von Henen-nesw und deren Getreue werden die Stadt von Zeit zu Zeit bedrohen, möglicherweise wird man auch versuchen, Geld aus der Stadtkasse zu erpressen. Um sich gegen diese vielfältigen Gefahren zu wappnen, müssen Sie starke Land- und Seestreitkräfte aufbauen, die die Stadt und andere bedrohte Städte zu verteidigen in der Lage sind."
        }
    }
    message_history_kebet {
        id: 225,
        type: 3,
        size [40, 30]
        title {
            text: "Kebet",
            pos [50, 80]
        }
        subtitle {
            text: "Wiedervereinigung",
            pos [10, 30]
        }
        content {
            text: "Was Ihre Familie während des Bürgerkriegs geleistet hat, soll nicht unbelohnt bleiben. Ich, Pharao Mentuhotep, erhebe Ihre Familie in den Rang eines Wesirs. In ganz Ägypten gibt es niemanden, dem ich mehr vertraue als Ihnen. Jetzt, da die beiden Königreiche Ober- und Unterägypten wieder vereinigt sind und die Hauptstadt Waset blüht, brauche ich Ihre Hilfe, um meine Position im ganzen Königreich zu stärken. @PTrotz der Wiedervereinigung flackern in Ägypten immer wieder Kämpfe auf, insbesondere in Gebieten, die einst den Herrschern von Henen-nesw treu ergeben waren. Um unsere neue Union zu festigen, möchte ich, dass Sie Kebet wieder aufbauen und verteidigen. Kebet soll eine glorreiche Stadt werden, die den Bürgern Ägyptens eindrucksvoll vor Augen führt, was unter meiner Herrschaft möglich ist. Die Stadt wird häufig von den verbliebenen Städten der Loyalisten angegriffen, z.B. von Chmun. Achten Sie also darauf, die Grenzen der Stadt zu verteidigen. @PDie Hungersnot im Land ist nach wie vor groß. Häufig werden andere Städte Sie um Nahrungsmittel bitten. Verschließen Sie Ihre Ohren nicht vor ihren flehenden Bitten. Ganz Ägypten soll meine Güte und die Ergebenheit meines treuen Wesirs rühmen. @PIch weiß, ich verlange viel von Ihnen, doch ich sehe niemanden in Ägypten, der sonst in der Lage wäre, diese schwierige Aufgabe zu erfüllen."
        }
    }
    message_history_menat_khufu {
        id: 226,
        type: 3,
        size [40, 30]
        title {
            text: "Menat Chufu",
            pos [50, 80]
        }
        subtitle {
            text: "Wiedervereinigung",
            pos [10, 30]
        }
        content {
            text: "Was Ihre Familie während des Bürgerkriegs geleistet hat, soll nicht unbelohnt bleiben. Ich, Pharao Mentuhotep, erhebe Ihre Familie in den Rang eines Wesirs. In ganz Ägypten gibt es niemanden, dem ich mehr vertraue als Ihnen. Jetzt, da die beiden Königreiche Ober- und Unterägypten wieder vereinigt sind und die Hauptstadt Waset blüht, brauche ich Ihre Hilfe, um meine Position im ganzen Königreich zu stärken. @PTrotz der Wiedervereinigung flackern in Ägypten immer wieder Kämpfe auf, insbesondere in Gebieten, die einst den Herrschern von Henen-nesw treu ergeben waren. Um das wieder vereinigte Land zu festigen, möchte ich, dass Sie Menat Khufu wieder aufbauen und verteidigen. Die Stadt wurde während des Bürgerkriegs fast vollständig zerstört. Menat Chufu soll eine glorreiche Stadt werden, die den Bürgern Ägyptens eindrucksvoll vor Augen führt, was unter meiner Herrschaft möglich ist.  @PDie Hungersnot im Land ist nach wie vor groß. Häufig werden andere Städte Sie um Nahrungsmittel bitten. Verschließen Sie Ihre Ohren nicht vor ihren flehenden Bitten. Ganz Ägypten soll meine Güte und die Ergebenheit meines treuen Wesirs rühmen. Obelisken aus Granit sollen der Nachwelt von den Taten künden, die ich während meines Lebens für dieses Land vollbracht habe. @PIch weiß, ich verlange viel von Ihnen, aber ich weiß auch, dass Sie der Einzige in Ägypten sind, der in der Lage ist, meine Bitten zu erfüllen."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itijtaui", pos [50, 80] }
        subtitle { text: "Die Gründung einer neuen Hauptstadt", pos [10, 30] }
        content {
            text: "Oh mächtiger Pharao, gesegnet von Re, wie glücklich müssen Sie sich schätzen! Ihren unvergleichlichen Aufstieg auf den ägyptischen Thron umgibt eine Aura des Göttlichen! Nur einem Liebling der Götter kann solches Glück widerfahren. Mit dem Machtantritt Ihrer Familie kann Ägypten einen neuen Anfang wagen und vielleicht all das Grauen des Bürgerkriegs hinter sich lassen. @PWas könnte diesen Neuanfang besser symbolisieren als die Errichtung einer herrlichen neuen Hauptstadt. Itijtaui ist mit seinen vielen Bodenschätzen ein idealer Ort dafür. Mit dem, was das Land in sich birgt, können Sie eine herrliche Stadt errichten, wie es dem Ruhm und der Güte Ihrer Dynastie gebührt. @PDamit die Leistungen Ihrer großen Dynastie niemals der Vergessenheit anheim fallen, sollten Sie zwei majestätische Ziegelpyramiden für sich und Ihre Familie errichten sowie eine furchterregende Sphinx, die Ihr Grab bewacht. Eine Familie, die vollbracht hat, was Sie vollbracht haben, verdient nichts Geringeres. @PDenken Sie jedoch stets daran, dass es einige im Land gibt, die die Rechtmäßigkeit Ihrer Herrschaft in Frage stellen. Viele leiden noch unter den Nachwirkungen der Hungersnot und beklagen, Sie hätten den Thron usurpiert. Wenn Sie die Not der Menschen lindern und ihnen helfen, ihre Behausungen wieder aufzubauen, können Sie ihrer grenzenlosen Loyalität gewiss sein. Sie sollten versuchen, sich so gut wie möglich um Ihre neuen Untertanen zu kümmern, damit diese nicht auf die Idee kommen, sich mit Waffengewalt gegen Sie zu erheben."
        }
    }
    message_history_iken {
        id: 228,
        type: 3,
        size [40, 30]
        title {
            text: "Iken",
            pos [50, 80]
        }
        subtitle {
            text: "Nach Nubien",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da Ägypten fest unter Ihrer Herrschaft vereint ist, empfiehlt Ihnen Ihr Hofstaat ebenso wie ich, Ihr treuer Wesir, die Grenzen unseres Landes gen Süden nach Nubien zu erweitern. Das trockene Flussbett bei Allaqi enthält reiche Goldadern, und eine mächtige Stadt in Iken, in der Sie Ihre Residenz einrichten, wird die Nubier gewiss von einem Angriff abhalten. Nehmen Sie sich jedoch vor den Kuschitern in Acht. Sie sind weitaus gefährlichere Gegner als die Nubier und werden ihre Schwerter benutzen, oh Pharao, um Sie davon zu überzeugen, ihr Königreich in Frieden zu lassen. @PUm ein dauerhaftes Zeichen in Nubien zu hinterlassen, sollten Sie einen großen Obelisken errichten, der Zeugnis von den vielen Errungenschaften Ägyptens ablegt. Der Obelisk wird den Nubiern überzeugender Beweis sein, welche Vorteile die ägyptische Herrschaft hat, und sie stets an unsere Gegenwart erinnern. @PWährend Ihre direkte Aufmerksamkeit auf Iken gelenkt ist, sollten Sie unsere Absicht nicht aus den Augen verlieren, am Roten Meer bei Sawu eine blühende Hafenstadt zu errichten. Sawu wird Hilfe vom Pharao benötigen und nicht zögern, darum zu bitten. Wenn Sawu eine blühende Stadt wird, kann Iken von dort aus mit dem wertvollen Kupfer beliefert werden, aus dem wir Waffen schmieden können."
        }
    }
    message_history_sawu {
        id: 229,
        type: 3,
        size [40, 30]
        title {
            text: "Sawu",
            pos [50, 80]
        }
        subtitle {
            text: "An der Küste des Roten Meers",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da Ägypten fest unter Ihrer Herrschaft vereinigt ist, müssen wir Handelsbeziehungen mit Städten in der ganzen Welt aufbauen, um den Reichtum Ägyptens zu vergrößern, oh König der zwei Länder.  @PJe wohlhabender Ihr Volk wird, desto größer wird sein Verlangen nach exotischen Waren. Das Volk hat genug von Juwelen, einem leicht erhältlichen Luxusgut, und wünscht sich seltene, teure Luxuswaren wie z. B. Weihrauch. Der Hofstaat und ich, Ihr treuer Wesir, empfehlen Ihnen, bei Sawu am Roten Meer einen Hafen einzurichten. Von Sawu aus kann eine Handelsroute in das ferne Pwenet eingerichtet werden, von wo - wenn auch zu enormen Kosten - der herrlichste Weihrauch der Welt importiert werden kann.  @PAbgesehen von einigen bescheidenen Adern mit Gold oder Kupfererz kann Sawu nur wenig eigene Rohstoffe produzieren, allerdings hat die Stadt große Potentiale für die Herstellung von Fertigprodukten. Durch den Import von Rohstoffen von seinen Handelspartnern und den Export von Fertigprodukten müsste Sawu in der Lage sein, gewinnbringende Geschäfte zu betreiben. @PWährend Sie in Sawu beschäftigt sind, richtet einer Ihrer besten Nomarchen ein neues Handelszentrum in Nubien ein. Seine Stadt, Iken, wird ständig von Angriffen bedroht, daher sollte unser geliebter Pharao bereit sein, ihm jegliche Ressourcen zu schicken, die er möglicherweise benötigt. @PUnter Ihrer Herrschaft wird Sawu mit Sicherheit eine der schönsten Städte des Königreichs. Eine bessere letzte Ruhestatt für Sie und Ihre Familie ließe sich kaum denken. Vergessen Sie über der Errichtung des Hafens nicht die Vorbereitungen für das Leben nach dem Tode. Ein Mausoleum und eine kleine Ziegelpyramide werden eine hervorragende Wohnstatt für Sie und Ihre Familie abgeben, wenn Sie dereinst zu den Feldern voll Schilf gewandert sind."
        }
    }
    message_history_heh {
        id: 230,
        type: 3,
        size [40, 30]
        title {
            text: "Heh",
            pos [50, 80]
        }
        subtitle {
            text: "Der Fehdehandschuh",
            pos [10, 30]
        }
        content {
            text: "Hochverehrter Pharao! Alles, wofür Ihre Familie so hart gekämpft hat, ist derzeit bedroht! Die Seestreitkräfte der Nubier patrouillieren auf dem Nil, sie greifen tief im Herzen Ägyptens an und plündern Dörfer und Städte ohne Unterschied. Wie gemeine Piraten überfallen sie Handelsschiffe und rauben unsere Waren. Um den Städten im Norden zu helfen, den Feind zurückzuschlagen, sollten Sie sich bereitmachen, Kriegsschiffe und Soldaten dorthin zu entsenden.  @PUm zu verhindern, dass die Nubier erneut in unsere Gewässer eindringen, empfehlen Ihnen die Militärberater den Bau mehrerer Festungen bei Heh zwischen dem zweiten und dritten Nilkatarakt. Die Festungen werden wie eine Art Korken wirken und die Nubier im Süden einschließen.  @PDie erfolgreiche Vertreibung der Nubier steht und fällt mit der Eroberung der Stadt Baki. Baki ist reich an Ressourcen. Wenn es uns gelänge, diese Stadt zu erobern, wäre dies der Todesstoß für die nubische Wirtschaft. Sobald es Ihnen gelungen ist, den Nubiern die Herrschaft über Baki zu entreißen, können Sie anfangen, aus dieser Stadt Sandstein für Ihr großes Mausoleum zu importieren. Ihr Mausoleum in Heh wird stets an Ihren Sieg über die widerspenstigen Nubier erinnern.  @PVor Ihnen türmen sich die Herausforderungen, wenn Sie Ägypten vor den Nubiern schützen wollen. Oh lebendiger Horus, stets muss auf den Sturm geachtet werden, der sich im Osten erhebt. Das Donnern der Pferdehufe schallt durch ganz Kanaan, und die blitzschnellen Streitwagen legen alles in Schutt und Asche, das sich ihnen in den Weg stellt. Solche Wagen, die durch nichts aufzuhalten sind, hat man nie zuvor gesehen. Sie werden von Kriegern vom Volk der Hyksos gefahren. Bereits jetzt erheben sich dunkle Wolken am ägyptischen Horizont - seien Sie gewappnet, wenn die Gefahr näher kommt."
        }
    }
    message_history_bubastis {
        id: 231,
        type: 3,
        size [40, 30]
        title {
            text: "Bubastis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Stadt der Bastet",
            pos [10, 30]
        }
        content {
            text: "Oh königlicher Pharao. Jetzt, da die Handelsrouten fest verankert sind, sollten wir Ägypten zeigen, was Erfolg und Wohlstand ihm bringen können. Bubastis ist ein idealer Standort für eine solche Stadt: Von hier aus können wir unsere wichtigen Handelsrouten in den Osten schützen und gleichzeitig Bastet Ehre erweisen, die ihre schützende Hand über Ägypten gehalten hat. @PDie Stadt der Göttin Bastet soll keiner anderen Stadt in Ägypten gleichen. Sie soll lieblich sein wie eine Lotusblume und reich an Unterhaltung, Schulen, Bibliotheken und Andachtsorten. Die Bürger der Stadt sollen ausreichend mit Luxuswaren versorgt werden, wozu auch importierter Weihrauch gehören soll. Wenn die Stadt fertig ist, wird sie das Juwel in der Doppelkrone sein. @PWenn Sie diese herrliche Stadt errichten, sollten Sie jedoch auch stets ein Auge auf den Sturm haben, der sich im Osten erhebt. Das Donnern der Pferdehufe schallt durch ganz Kanaan, und die blitzschnellen Streitwagen legen alles in Schutt und Asche, das sich ihnen in den Weg stellt. Solche Wagen, die durch nichts aufzuhalten sind, hat man nie zuvor gesehen. Sie werden von Kriegern vom Volk der Hyksos gefahren. Bereits jetzt erheben sich dunkle Wolken am ägyptischen Horizont - seien Sie gewappnet, wenn die Gefahr näher kommt."
        }
    }
    message_history_khmun {
        id: 232,
        type: 3,
        size [40, 30]
        title {
            text: "Chmun",
            pos [50, 80]
        }
        subtitle {
            text: "Die Rückeroberung Ägyptens",
            pos [10, 30]
        }
        content {
            text: "Oh mächtigster aller Pharaonen - Ägypten ruft Sie um Hilfe an. Die finsteren Hyksos sind in unser Land eingefallen und haben eine eigene Hauptstadt in Rowarty errichtet. Sie nennen sie Hut-Waret. Von dort aus haben sie viele unserer Handelsrouten unterbrochen und uns so von dringend benötigten Gütern abgeschnitten. Wir müssen ihrem Siegeszug Einhalt gebieten, bevor es zu spät ist. @PWenn es Ihnen gefällt, großer Pharao, sollten wir die Stadt Chmun zurückerobern, die von den grausamen Eindringlingen eingenommen wurde. Darüber hinaus sollten wir starke Land- und Seestreitkräfte aufbauen, denn es kann sein, dass wir unseren Landsleuten im Norden Truppen und Waffen stellen müssen, um die Hyksos zurückzuschlagen - insbesondere in Hut-Waret. Oh Sohn des Re, edler Pharao, die Menschen warten auf Ihre Hilfe. Doch nun besitzen auch wir eine neue Waffe. Unseren weisen militärischen Führern ist es gelungen, den Gebrauch des gefürchteten Wagens zu studieren. Mit diesem werden wir uns gegen unsere Feinde stellen und sie wieder aus dem Land vertreiben. Nach der Vertreibung der Hyksos empfehlen unsere Militärberater den Bau eines Forts bei Scharuhen im Lande Sinai, um weitere Invasionen aus dem Osten zu verhindern. @PAch, wenn unsere Schwierigkeiten doch nur auf den Norden beschränkt wären! Berichte von unserer Südgrenze indessen zeigen, dass die Nubier die auf andere Dinge gerichtete Aufmerksamkeit Ägyptens wieder einmal zu ihrem Vorteil nutzen wollen. Sie haben die im Süden gelegenen Städte Iken und Heh zurückerobert. Zwar bereiten uns diese verlorenen Städte Kopfzerbrechen, dennoch müssen wir erst die Hyksos vertreiben, bevor wir uns wieder dem Süden zuwenden können. @PDiese Hyksos sind wahrhaft bösartige Eindringlinge. Soeben haben wir entdeckt, dass sie eine Pyramide hier in Chmun geschändet haben. Sie haben sämtliche Grabbeigaben des mächtigen Pharao gestohlen, die dieser im Schilffeld benötigt. Wir sollten dem dort bestatteten Pharao neue Grabbeigaben schenken, damit er das Leben in der Ewigkeit genießen kann."
        }
    }
    message_history_sauty {
        id: 233,
        type: 3,
        size [40, 30]
        title {
            text: "Sauty",
            pos [50, 80]
        }
        subtitle {
            text: "Die Rückeroberung Ägyptens",
            pos [10, 30]
        }
        content {
            text: "Oh König der zwei Länder - Ägypten fleht Sie um Hilfe an. Die finsteren Hyksos sind in unser Land eingefallen und haben eine eigene Hauptstadt in Rowarty errichtet. Sie nennen sie Hut-Waret. Von dort aus haben sie viele unserer Handelsrouten unterbrochen. Wir müssen ihrem Siegeszug Einhalt gebieten, bevor es zu spät ist. @PHier in Sauty sind wir vor direkten Angriffen sicher, obschon die Hyksos die Dreistigkeit besitzen, Tributzahlungen zu verlangen. Möglicherweise müssen wir unseren Landsleuten im Norden Truppen und Waffen zur Verfügung stellen, um zum Zurückschlagen der Hyksos beizutragen. Oh edler Pharao, die Menschen warten auf Ihre Hilfe. Inzwischen sind aber auch wir im Besitz der neuen Waffe. Unseren weisen militärischen Führern ist es gelungen, den Gebrauch des gefürchteten Wagens zu studieren. Mit diesem werden wir uns gegen unsere Feinde stellen und sie wieder aus dem Land vertreiben. @PAch, wenn unsere Schwierigkeiten doch nur auf den Norden beschränkt wären! Berichte von unserer Südgrenze indessen zeigen, dass die Nubier die auf andere Dinge gerichtete Aufmerksamkeit Ägyptens wieder einmal zu ihrem Vorteil nutzen wollen. Sie haben die im Süden gelegenen Städte Iken und Heh zurückerobert. @PWenn Ägypten aus dieser schweren Zeit unversehrt hervorgehen soll, wird Ihren Generälen zu Wasser und zu Lande das Äußerste abverlangt werden. Um Ihre beiden besten Generäle zu beflügeln, haben Sie das Gelübde abgelegt, jedem eine Pyramide zu bauen, die ebenso spektakulär ist wie Ihre eigene. Mit dieser Aussicht im Herzen kämpfen sie mit aller Macht gegen den Feind und mobilisieren die letzten Reserven an Kraft und Zähigkeit.  @PWenn es Ihnen denn gefällt, oh mächtiger Pharao, so sollten Sie drei herrliche Pyramiden in Sauty bauen - eine für sich selbst und eine für jeden der beiden Generäle. Diese drei Pyramiden werden verhältnismäßig viel Platz benötigen, Sie werden also einige wertvolle Ressourcen aufgeben müssen, um Raum dafür zu schaffen. Möglicherweise müssen Sie Ihre Stadt auch über den Nil hinweg ausdehnen, um sämtliche benötigten Ressourcen zu erhalten, die diese Stadt braucht, um zu gedeihen."
        }
    }
    message_history_byblos {
        id: 234,
        type: 3,
        size [40, 30]
        title {
            text: "Byblos",
            pos [50, 80]
        }
        subtitle {
            text: "Ausdehnung und Eroberung",
            pos [10, 30]
        }
        content {
            text: "Ägypten ist gestärkt aus den jüngsten Schwierigkeiten hervorgegangen. Byblos, mit all seinen grünen Wäldern und reichen Kupfervorkommen, ist unser! Mit Ihrer Anwesenheit hier wird die Stadt gewiss aufblühen, und ein neues Königreich wird errichtet. @PAber welch eine schreckliche Entdeckung mussten wir nach der Eroberung von Byblos machen! Ein neues, grausames Volk, die Hethiter, sind über einen Großteil Asiens hergefallen - manch einer sagt sogar, ihr Imperium käme von der Größe her an unseres heran! Nun haben sie ihre gierigen Augen gen Byblos gewandt. Wenn wir uns nicht gut auf ihren Angriff vorbereiten, könnte es sein, dass wir Byblos wieder an den Feind verlieren.  @PWährend wir uns gegen die hethitische Gefahr wappnen, müssen wir Byblos auf ewig als ägyptische Stadt kennzeichnen. Mit Ihrem Segen, oh Pharao, werden wir eine Reihe von drei Obelisken - zwei kleine und einen großen - errichten, die Ihre Souveränität und Ihren Ruhm bis in den letzten Winkel Ihres Königreichs verkünden. Diese alles überragenden Monumente werden die Einwohner von Byblos daran erinnern, wem sie Treue schulden. @PWährend wir uns in Byblos mit diesen Problemen beschäftigen, werden andere Gegenden Ägyptens weiterhin angegriffen. Die Nubier sind bereits am ersten Katarakt angelangt. Wir müssen unseren Mitbürgern helfen, sie zurückzuschlagen. Laut Berichten aus Rowarty gibt es einen weiteren geheimnisvollen neuen Feind: das Seevolk. Beide Feinde müssen mit äußerster Härte bekämpft werden, wenn Ägypten ruhmreich bleiben will. Um Ihre Macht zu zeigen, sollten Sie unbedingt Truppen und Kriegsschiffe entsenden, sobald diese angefordert werden."
        }
    }
    message_history_baki {
        id: 235,
        type: 3,
        size [40, 30]
        title {
            text: "Baki",
            pos [50, 80]
        }
        subtitle {
            text: "Der Glanz Ägyptens",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da die Hyksos erfolgreich aus unserem Land vertrieben wurden, ist unser Land für seine Wiederauferstehung bereit - für ein neues Königreich, dessen neuer Glanz den der Vergangenheit überstrahlen wird. Oh edler Pharao, Baki ist ein idealer Ort für den Anbeginn dieses neuen Königreichs. Die großen Goldvorkommen in Baki können wir nutzen, um Ihre neue Vision Ägyptens in Stein zu meißeln.  @PZwar steht Ägypten an der Schwelle zu wahrer Größe, dennoch bleiben einige störenden Probleme bestehen. Viele ägyptische Städte erholen sich noch von den Überfällen der Hyksos und bedürfen möglicherweise pharaonischer Hilfe. In anderen Gegenden greifen unsere alten Feinde weiterhin an, und der neue Feind, das Seevolk, geht an unserer Nordküste auf Raubzüge. Sie müssen also bereit sein, andere ägyptische Städte gegen unsere alten und neuen Feinden zu verteidigen. @PMit zunehmender Bedeutung Ägyptens sind viele Städte bereit, mit uns Handel zu treiben. Einigen dieser Städte ist unsere Kultur so vertraut und sie stehen so sehr im Banne unserer Macht, dass sie sich als ägyptische Städte verstehen, andere dagegen sind uns fremd und treiben zum ersten Mal mit uns Handel. Nutzen Sie all diese Beziehungen zum Ruhme Ägyptens und um Ihrem Volk all die Waren zu bieten, die es wünscht. @PUm das neue Zeitalter würdig zu empfangen, wäre es Ihren königlichen Architekten eine Ehre, zwei Pyramiden und ein herrliches Mausoleum für Sie, oh großer Pharao, zu errichten. Diese Bauwerke werden gewiss den Wohlstand und die Herrlichkeit widerspiegeln, die Sie Ägypten gebracht haben."
        }
    }
    message_history_rowarty {
        id: 236,
        type: 3,
        size [40, 30]
        title {
            text: "Rowarty ",
            pos [50, 80]
        }
        subtitle {
            text: "Das Seevolk",
            pos [10, 30]
        }
        content {
            text: "Oh güldener Horus, unser Griff um Asien ist stark und unbestritten, und unsere Grenzen erstrecken sich wieder bis weit nach Nubien hinein. An unserer Nordküste jedoch nehmen die Schwierigkeiten zu. Das Seevolk wird zunehmend aggressiver und plündert unsere Städte ohne Rücksicht. Nur die Gegenwart des Pharao wird in der Lage sein, diese wilden und ruchlosen Gegner zu besiegen. Wenn Sie eine Seestreitkraft aufstellen, die von einer starken Armee unterstützt wird, werden wir das Seevolk bestimmt überwältigen.  @PWährend Sie das Seevolk in die Knie zwingen, tragen Ihre tapferen Nomarchen Angriffe in der ganzen Welt vor. Sollte ihnen Erfolg beschieden sein, wird Ägypten die Welt vom großen Euphrat in Asien bis hin zur riesigen kuschitischen Stadt Kerma im Süden untertan sein. Wenn Ihnen und Ihren Nomarchen der Sieg gehört, wird Ihre Dynastie als die größte Herrscherdynastie aller Zeiten in die ägyptische Geschichte eingehen. @PIhr großer Einfluss wird auch durch einen neuen, entfernten Handelspartner unter Beweis gestellt - die Stadt Mykene. Der König von Mykene hat von der Herrlichkeit und dem Reichtum Ägyptens erfahren und will mit uns Handel treiben. Wenn Sie dieser Handelsroute zustimmen, oh Pharao, werden Ihre Bürger exotische Waren erhalten, wie sie sie noch nie gesehen haben. @PUm die königliche Familie in ihrem Leben nach dem Tod würdig zu beherbergen, müssen ein mächtiges Mausoleum und zwei beeindruckende Ziegelpyramiden errichtet werden. Diese Monumente werden Ihre Taten als Feldherr und Wohltäter rühmen und unvergesslich machen."
        }
    }
    message_history_hetepsensusret {
        id: 237,
        type: 3,
        size [40, 30]
        title {
            text: "Hetepsensusret",
            pos [50, 80]
        }
        subtitle {
            text: "Die Herrlichkeit des Pharao",
            pos [10, 30]
        }
        content {
            text: "Oh gütiger Pharao, Sie haben unserem Land Frieden und Wohlstand gebracht. Unter Ihrer weisen, klugen Herrschaft ist Ägypten wieder ein mächtiges und glorreiches Land geworden. Alle Nomarchen sind Ihnen treu ergeben, alle Bedrohungen unserer großen Nation sind abgewendet. @PNachdem Sie alles erreicht haben, was sich Ihre Familie vor so vielen Jahren zum Ziel gesetzt hat, ist es nun an der Zeit, die Leistungen Ihrer großen Dynastie für die Nachwelt zu verewigen. Dies kann nur dadurch geschehen, dass Sie die größte Pyramide errichten, die es jemals in Ägypten gab, eine Pyramide, größer noch als die des Cheops in Rostia. Auch andere Mitglieder Ihrer edlen Familie haben viel auf dem langen Weg zur Herrschaft über Ägypten geopfert. Auch ihrer muss ehrend gedacht werden, am besten mit einem Mausoleum aus Sandstein, das ihrer unerschütterlichen Loyalität würdig ist.  @LDer ideale Standort für diese Monumente ist Hetepsensusret in der reichen Region Fayum. Von hier aus können Sie alle Staatsangelegenheiten regeln und allen Forderungen nach Waren nachkommen, die möglicherweise aus Städten in Ihrem Herrschaftsbereich eingehen, während Sie an Ihrer großen Pyramide bauen."
        }
    }
    message_history_perwadjyt_3 {
        id: 238,
        type: 3,
        size [40, 30]
        title {
            text: "Perwadiut",
            pos [50, 80]
        }
        subtitle {
            text: "Die Ufer des Nils",
            pos [10, 30]
        }
        content {
            text: "@PMit Hilfe Ihrer Familie gelang es dem thinitischen König Aha, auch Hu-eje genannt, das Doppel-Königreich aus Unter- und Oberägypten zu vereinen. Er ernannte sich zum Pharao von ganz Ägypten und gründete in Men-nefer eine imposante Hauptstadt.  @PIhr Klan ist ein weiteres Mal umgezogen, diesmal in das feuchte Delta Unterägyptens, in ein Gebiet, das Perwadiut genannt wird. Kanaanitische Kriegsschiffe stellten in dieser Gegend eine ständige Bedrohung dar, und wenn die Zeit dafür gekommen ist, kommen Sie wohl nicht umhin, selbst ebenfalls ein paar Kriegsschiffe zu bauen. @PIhre Familie wurde in den Adelsstand erhoben. Nun wird von Ihnen erwartet, dass Sie, bevor Sie von dieser Welt in die nächste wechseln, ein prächtiges Ziegelsteingrab - eine Mastaba - errichten, in dem Ihr Körper seine Reise in das Leben nach dem Tod antreten kann. @PZuerst müssen Sie jedoch einige Farmen an den Ufern des Nils bauen, damit Sie den fruchtbaren Schlamm nutzbar machen können, der nach den alljährlichen Überschwemmungen des Flusses am Ufer zurückbleibt. Nur dann kann Ihre Bevölkerung wachsen und gedeihen und schließlich groß genug werden, um das heilige Bauwerk zu vollenden. Doch Vorsicht: Im Leben spendenden Wasser des Nils lauern auch viele Gefahren, wie todbringende Krokodile, Nilpferde und Malaria übertragende Mücken. @L@LAckerbau entlang des Nils @PSie müssen die Farmen direkt im Überschwemmungsland bauen, um von dessen Fruchtbarkeit profitieren zu können. Anders als die meisten Gewerbestätten müssen die Farmen im Überschwemmungsgebiet keinen direkten Zugang für Arbeiter haben. Ihre Felder benötigen aber trotzdem ständige Betreuung durch Landarbeiter, die aus Arbeiterlagern kommen. Bauen Sie die Arbeiterlager relativ nah an den landwirtschaftlichen Anwesen im Überschwemmungsgebiet, damit die Bauern nicht zu weit laufen müssen, um sie zu erreichen. @G56 @L@LDie jährliche Erntezeit @L@PJedes Jahr tritt der Nil über die Ufer und reichert die verbrauchte Erde wieder mit seinem fruchtbaren Schlamm an. Die Bauern bringen die jährliche Ernte kurz vor der Überschwemmung ein und liefern sie in Ihren Silos ab. Da es nur eine Ernte im Jahr gibt, sollten Sie dafür sorgen, dass Sie genügend Silos haben, um ausreichend Nahrung für Ihre wachsende Bevölkerung einzulagern."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Brot oder Hungersnot?", pos [0, 15] }
        content {
            text: "@PEine wachsende Bevölkerung benötigt eine zuverlässige Versorgung mit Nahrung sowie Einrichtungen zur Lagerung und Verteilung der Nahrungsmittel. Bestimmte Tiere können von Jägern erlegt werden, wie z.B. in diesem Gebiet Strauße. In Silos werden Fleisch und andere Nahrungsmittel eingelagert. Über Basare gelangt die Nahrung zu den Dorfbewohnern. Wie die meisten Gewerbestätten müssen auch diese Einrichtungen im Einzugsgebiet der Wohnungen liegen, damit sie richtig funktionieren. Außerdem muss die Stadt genügend Arbeitskräfte haben, um die Gebäude zu betreiben. @L@LDie Jagd @L@PBauen Sie in der Nähe der Straußenherde einen Jagdhof. Die Jäger brechen von dort zur Jagd auf. Wenn sie erfolgreich sind, bringen sie das erlegte Wild zum Jagdhof zurück, wo es zerlegt wird. Danach liefert ein Karrenschieber das Fleisch beim nächstgelegenen Silo zur Einlagerung ab.  @PVerschiedene Arbeitskräfte vom Basar schätzen die Bedürfnisse der Viertel ab, um die sie sich kümmern. Sie holen Nahrung aus nahe gelegenen Silos und liefern sie an die unmittelbar benachbarten Häuser aus. @G60 @PBauen Sie Silos und Basare, indem Sie auf den Button 'Gebäude für Lagerung und Vertrieb' klicken. @G77 @L@PZiel Ihrer Mission ist, am Ende einige Ihrer 'Hütten' in 'Kleine Häuschen' zu verwandeln. Sie erreichen dies, indem Sie deren Bewohner mit Nahrung aus dem Basar versorgen. Außerdem sollten Sie die Häuser nicht zu dicht bei unschönen gewerblichen Gebäuden errichten, da dies die Entwicklung der Häuser hemmen kann: Gewerbegebiete wirken sich negativ auf die Attraktivität der Umgebung aus.  @L@LAufseher @L@PJetzt steht ein Aufseher für Nahrungs- und Bevölkerungsfragen zur Verfügung, der Ihnen Informationen und Ratschläge geben kann. Im Laufe der Zeit werden Sie viele Aufseher haben, die Ihnen bei der Leitung der Stadt zur Seite stehen. @G76 @L@PUm sie zu erreichen, müssen Sie auf das 'Aufseher'-Icon linksklicken oder auf das entsprechende Gebäude rechtsklicken."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Unterhaltung", pos [0, 15] }
        content {
            text: "Nachdem sich Ihre Stadt etwas weiterentwickelt hat, können sich einige Bewohner einer gewissen Freizeit erfreuen, die sie zum Besuch von Unterhaltungseinrichtungen nutzen. Zu einer wirklich kultivierten Stadt gehört ein breit gefächertes Unterhaltungsangebot. Aber zur Zeit können Sie nur Auftritte von Jongleuren bieten. @L@LUnterhaltungseinrichtungen und Jongleure @PDer Jongleur benötigt eine Unterhaltungsstätte, in der er auftreten kann. Die kleinste dieser Art wird als 'Bühne' bezeichnet. Bauen Sie eine Bühne auf einer zentralen Wegkreuzung, um dort Jongleuraufführungen zu veranstalten, und eine Jonglierschule in der Nähe, um die Künstler auszubilden. Beide Einrichtungen benötigen Zugang zu Arbeiterwohnungen und ausreichend Arbeitskräfte, um sie zu betreiben. @PJongleure, die an der Schule ausgebildet wurden, begeben sich danach zu einer nahe gelegenen Bühne, um dort aufzutreten und dem umliegenden Gebiet ein bescheidenes Maß an Unterhaltung zu bieten. @G61 @L@LBefragen Sie Ihren Aufseher der Unterhaltung, um mehr über die Erholungsbedürfnisse Ihrer Stadt zu erfahren. Klicken Sie auf die 'Spezialkarte: Unterhaltung', um festzustellen, welche Häuser Ihrer Stadt Zugang zu Unterhaltung haben."
        }
    }
    message_gold_and_crime {
        id: 241,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Goldbergbau und Kriminalität", pos [0, 15] }
        content {
            text: "Suchen Sie in dem Felsgebiet nach Vorkommen von Metallerzen. Sie erkennen diese am metallischen Schimmer zwischen den Steinen. Um Erz abzubauen, müssen Sie neben den Erzadern Goldminen bauen. @G53 @L@LPalast @L@PEin Palast wird benötigt, um aus dem rohen Golderz Gold zu gewinnen und die dabei entstehenden Goldbarren einzulagern. Der Palast ist der Sitz der Stadtregierung und muss in einem Bereich gebaut werden, in dem es genügend Grundwasser gibt (Grasbereiche). @PSobald Ihr Palast gebaut ist und funktioniert, liefern die Minenarbeiter hier das Golderz aus allen Minen ab, damit es zu 'Deben', das Geld der hiesigen Währung, veredelt werden kann. @G54 @L@LKriminalität @L@PKaum haben Sie es zu etwas Gold gebracht, sehen Sie sich auch schon neidischen Blicken und dem Risiko des Diebstahls ausgesetzt. Polizisten können die Verluste durch Diebstahl reduzieren, indem sie in den Straßen patrouillieren, um Verbrechen vorzubeugen, oder auch, indem sie alle kriminellen Elemente festnehmen, auf die sie treffen. @G55 @L@PDie beste Art jedoch, Verbrechen zu verhindern, besteht darin, Ihre Bevölkerung zufrieden zu stellen und für ausreichend Essen, ein gutes Gesundheitssystem und genügend Jobs zu sorgen."
        }
    }
    message_farming_along_the_nile {
        id: 242,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Landwirtschaft entlang des Nils",
            pos [0, 15]
        }
        content {
            text: "Landwirtschaft entlang des Nils @L@PSie müssen die Farmen direkt im Überschwemmungsland bauen, um von dessen Fruchtbarkeit profitieren zu können. Anders als die meisten Gewerbestätten müssen die Farmen im Überschwemmungsgebiet keinen direkten Zugang für Arbeitskräfte haben. Ihre Felder benötigen aber trotzdem ständige Betreuung durch Bauern, die aus Arbeiterlagern kommen. Bauen Sie die Arbeiterlager relativ nah an den landwirtschaftlichen Anwesen im Überschwemmungsgebiet, damit die Bauern nicht zu weit laufen müssen, um sie zu erreichen. @G56 @L@PJedes Jahr tritt der Nil über die Ufer und reichert die verbrauchte Erde wieder mit seinem fruchtbaren Schlamm an. Die Bauern bringen die jährliche Ernte kurz vor der Überschwemmung ein und liefern sie in Ihren Silos ab. Da es nur eine Ernte im Jahr gibt, sollten Sie dafür sorgen, dass Ihre Stadt genügend Silos hat, um ausreichend Nahrung für die wachsende Bevölkerung einzulagern."
        }
    }
    message_developing_culture {
        id: 243,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Kulturentwicklung",
            pos [0, 15]
        }
        content {
            text: "Bier @LIhre ägyptischen Landsleute haben die Kunst des Bierbrauens perfektioniert, und Bier ist überall in Ägypten ein beliebtes Getränk geworden! Wenn die Braumeister durch die Farmen vor Ort mit Gerste beliefert werden, dann produzieren sie Bier und liefern es an Warenlager, von denen aus es später (genau wie Nahrungsmittel und Töpferwaren) durch Basarangestellte weiterverteilt werden kann. @L@LVerschiedene Götter @LDer Schutzgott in dieser Gegend ist Re, aber Osiris und Bastet werden ebenfalls als lokale Gottheiten verehrt. Achten Sie darauf, dass es in dieser Stadt mehr Tempel und Schreine gibt, die Re geweiht sind, aber vernachlässigen Sie darüber nicht die anderen lokalen Gottheiten! Um Ihre wichtigsten Bürger (Steuerzahler) zufrieden zu stellen, sollten Sie darauf achten, dass sie Zugang zu mehreren verschiedenen Gottheiten haben. @L@LZusätzliche Unterhaltung @LBetuchte Ägypter hören in ihrer Freizeit begeistert Musikern zu; ebenso gern schauen sie sich von Zeit zu Zeit eine Jongleurdarbietung an. Während auf der kleinen Bühne nur Jongleure auftreten können, bietet ein Musikpavillon Platz für Vorstellungen sowohl von Jongleuren als auch von Musikerinnen. Bauen Sie einen Musikpavillon auf einer Kreuzung, und errichten Sie ein Konservatorium in der Nähe, um Musikerinnen auszubilden. Der Zugang zu unterschiedlichen Formen der Unterhaltung verbessert die Lebensqualität jeder Stadt enorm. @L@LRecht und Ordnung @LEin Magistrat, der vom Gerichtsgebäude aus auf Patrouille geht, trägt dazu bei, das Risiko der Kriminalität zu reduzieren, indem er ein offenes Ohr für Sorgen hat und darauf achtet, dass alle einen kühlen Kopf behalten."
        }
    }
    message_getting_started {
        id: 244,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "So geht's los",
            pos [0, 15]
        }
        content {
            text: "Fangen Sie an, indem Sie Wohngebiete und Gewerbestätten planen. Mittlerweile wissen Sie darüber Bescheid, was Ihre Bürger neben den grundlegenden Bedürfnissen nach Nahrung und Wasserversorgung für Wünsche haben. Sie müssen einige Häuser mit Geschirr, Bier, Unterhaltung und dem Zugang zu Gotteshäusern versorgen, bevor Sie über höhere Bildung und Handel nachdenken können."
        }
    }
    message_soldiers_and_forts {
        id: 245,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Soldaten und Forts",
            pos [0, 15]
        }
        content {
            text: "Um Truppen aufzustellen, müssen Sie ein Fort und einen Drillplatz bauen. Vom Drillplatz aus werden, Mann für Mann, neue Rekruten zum Fort geschickt, bis es vollständig besetzt ist. Es gibt zwei Arten von Forts - Forts für Infanterie und Forts für Bogenschützen -, und jedes Fort bietet Platz für sechzehn Soldaten, die eine 'Kompanie' bilden. Wenn Soldaten im Kampf sterben, dann sorgt der Drillplatz dafür, dass Ersatzkräfte eingezogen werden. @G57 @L@LWaffen @PBogenschützen sind von sich aus mit Pfeil und Bogen ausgestattet, aber für Infanteriesoldaten müssen kupferbewehrte Speere bereitgestellt werden. Wenn eine Waffenschmiede mit Kupfer beliefert wird, dann produziert sie solche Waffen. Die fertig gestellten Waffen werden an den Drillplatz ausgeliefert, damit neue Infanteriesoldaten damit ausgerüstet werden können. @L@LMissionsziele und -beschreibungen @PVon nun an werden Ihre unmittelbaren Missionsziele nicht länger oben auf dem Bildschirm angezeigt. Klicken Sie auf das 'Ankh'-Symbol in der Steuerleiste, wenn Sie die Beschreibung Ihrer Mission noch einmal einsehen möchten, und besuchen Sie dann Ihre Aufseher, um sich über Ihren Gesamtfortschritt zu informieren."
        }
    }
    message_trade_on_the_water {
        id: 246,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Nahe am Wasser",
            pos [0, 15]
        }
        content {
            text: "Wasser-Handelswege @LHandel kann auch auf dem Fluss- oder Seeweg betrieben werden, wenn entsprechende Wasserwege an die Stadt angrenzen. Wenn Sie eine Handelsroute auf dem Wasserweg einrichten möchten, dann gehen Sie zur Weltkarte. Um auf Wasserwegen Handel zu betreiben, braucht Ihre Stadt außerdem ein funktionierendes Dock. @L@LFischfang auf dem Nil @LDer Nil bietet reiche Fischgründe, und Fisch ist in Ägypten ein beliebtes Nahrungsmittel. Überdies sorgt eine Ernährung mit unterschiedlichen Lebensmitteln für mehr Gesundheit und bessere Stimmung in Ihrer Bevölkerung. Um die reichen Fischgründe auszubeuten, benötigen Sie einige Fischerboote. @L@LBoots- und Schiffsbau @LDer Schiffbauer baut in der Werft sowohl Kriegsschiffe als auch Fischerboote. Jedes Boot braucht einen Heimathafen. Wann immer ein Hafen Platz für ein Schiff bietet, macht sich der Schiffbauer daran, eines für diesen Hafen zu bauen. Ohne einen freien Platz in einem Hafen baut der Schiffbauer keine Schiffe.  @LZwar kann eine einzige Werft durchaus sämtliche Schiffe liefern, die Ihre Stadt braucht, verfügen Sie jedoch über mehrere Werften, bietet sich Ihnen die Möglichkeit, verlorene Schiffe viel schneller zu ersetzen. Die Werft braucht keine Materiallieferungen für den Bau von Fischerbooten, wenn jedoch Kriegs- und Transportschiffe für militärische Zwecke gebaut werden sollen, dann muss sie mit Holz versorgt werden. @LMilitär- und Handelsschiffe sowie Fischerboote sind breit gebaut und haben einen tief gehenden Kiel, damit sie auf dem Nil und in Küstengewässern segeln können. Dagegen sind sie nicht für das Befahren enger Kanäle geeignet, und kleine Bäche oder Zuflüsse sind für sie unpassierbar. Niemand wird Sie daran hindern, gegebenenfalls auch an derartigen Wasserläufen Werften, Docks oder Häfen einzurichten, aber wenn Sie das tun, dann können Schiffe diese Einrichtungen weder anlaufen noch verlassen - sie funktionieren also nicht. @LWenn Sie an einem Ufer nach geeigneten Bauplätzen für maritime Einrichtungen suchen, dann sollten Sie darauf achten, dass ein durchgehend schiffbarer Wasserweg zwischen einer solchen Einrichtung und dem jeweiligen Zielort existiert. Zum Beispiel können Sie nicht einen Fischerhafen an einem Binnensee einrichten und erwarten, dass die dort beheimateten Fischerboote Fischgründe auf dem Nil erreichen - selbst dann nicht, wenn der Binnensee über einen Bach mit dem Nil verbunden ist."
        }
    }
    message_at_the_waters_edge {
        id: 247,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Nahe am Wasser",
            pos [0, 15]
        }
        content {
            text: "Wasser-Handelswege @LHandel kann auch auf dem Fluss- oder Seeweg betrieben werden, wenn entsprechende Wasserwege an die Stadt angrenzen. Wenn Sie eine Handelsroute auf dem Wasserweg einrichten möchten, dann gehen Sie zur Weltkarte. Um auf Wasserwegen Handel zu betreiben, braucht Ihre Stadt außerdem ein funktionierendes Dock. @L@LFischfang auf dem Nil @LDer Nil bietet reiche Fischgründe, und Fisch ist in Ägypten ein beliebtes Nahrungsmittel. Überdies sorgt eine Ernährung mit unterschiedlichen Lebensmitteln für mehr Gesundheit und bessere Stimmung in Ihrer Bevölkerung. Um die reichen Fischgründe auszubeuten, benötigen Sie einige Fischerboote. @L@LBoots- und Schiffsbau @LDer Schiffbauer baut in der Werft sowohl Kriegsschiffe als auch Fischerboote. Jedes Boot braucht einen Heimathafen. Wann immer ein Hafen Platz für ein Schiff bietet, macht sich der Schiffbauer daran, eines für diesen Hafen zu bauen. Ohne einen freien Platz in einem Hafen baut der Schiffbauer keine Schiffe.  @LZwar kann eine einzige Werft durchaus sämtliche Schiffe liefern, die Ihre Stadt braucht, verfügen Sie jedoch über mehrere Werften, bietet sich Ihnen die Möglichkeit, verlorene Schiffe viel schneller zu ersetzen. Die Werft braucht keine Materiallieferungen für den Bau von Fischerbooten, wenn jedoch Kriegs- und Transportschiffe für militärische Zwecke gebaut werden sollen, dann muss sie mit Holz versorgt werden. @LMilitär- und Handelsschiffe sowie Fischerboote sind breit gebaut und haben einen tief gehenden Kiel, damit sie auf dem Nil und in Küstengewässern segeln können. Dagegen sind sie nicht für das Befahren enger Kanäle geeignet, und kleine Bäche oder Zuflüsse sind für sie unpassierbar. Niemand wird Sie daran hindern, gegebenenfalls auch an derartigen Wasserläufen Werften, Docks oder Häfen einzurichten, aber wenn Sie das tun, dann können Schiffe diese Einrichtungen weder anlaufen noch verlassen - sie funktionieren also nicht. @LWenn Sie an einem Ufer nach geeigneten Bauplätzen für maritime Einrichtungen suchen, dann sollten Sie darauf achten, dass ein durchgehend schiffbarer Wasserweg zwischen einer solchen Einrichtung und dem jeweiligen Zielort existiert. Zum Beispiel können Sie nicht einen Fischerhafen an einem Binnensee einrichten und erwarten, dass die dort beheimateten Fischerboote Fischgründe auf dem Nil erreichen - selbst dann nicht, wenn der Binnensee über einen Bach mit dem Nil verbunden ist. @L@LDie Herstellung von Ziegeln @LZiegel sind ein relativ preisgünstiges Baumaterial, das bei der Errichtung bestimmter Arten von Grabmälern Verwendung findet. Um Ziegel herzustellen, benötigen Sie eine Ziegelei sowie Ton- und Strohvorräte."
        }
    }
    message_the_finer_things_2 {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Die Feinheiten",
            pos [0, 15]
        }
        content {
            text: "Tempelkomplexe @LIn dem Maße, in dem die Ergebenheit der ägyptischen Bürger gegenüber ihren Schutzgöttern wächst, verlangen sie nach immer großartigeren Kultstätten. Die meisten Städte werden danach streben, einen Tempelkomplex für die von ihnen geehrte Gottheit zu errichten, damit sie in den vollen Genuss der Gnade dieses Gottes oder dieser Göttin kommen. Einmal errichtet, kann der Tempelkomplex durch den zusätzlichen Bau eines Orakels oder Altars erweitert werden, zwei Einrichtungen, die jeweils anderen, nachgeordneten Gottheiten geweiht sind. Auch diese anderen Götter werden der Stadt daraufhin ihre Gunst zuteil werden lassen.  @L@Luxuswaren @LNeben vor Ort hergestelltem Schmuck schätzen die Ägypter auch bestimmte andere Luxuswaren, die nur über den Import angeboten werden können. Eine Stadt braucht Zugang zu mindestens zwei Sorten von Luxuswaren, damit sie sich wirklich 'zivilisiert' nennen darf.  @L@LHolzwirtschaft @G58 @LHolz ist im trockenen Ägypten ein seltener und wertvoller Rohstoff. Wer dort in einer Gegend mit Wäldern lebt, darf sich wahrhaft glücklich schätzen. Um Holzwirtschaft zu betreiben - wenn es denn überhaupt nennenswerte Baumbestände gibt - müssen Sie ein Holzfällerlager bauen, das dann Männer ausschickt, um Holz zu fällen. Holz wird sowohl für den Bau von Kriegs- und Transportschiffen als auch für Hilfskonstruktionen bei der Errichtung einiger Monumente benötigt."
        }
    }
    message_housing_and_roads {
        id: 249,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Wohnungen und Straßen" }
        content { text: "@PZuallererst benötigt dieses Dorf Behausungen, damit die Siedler einen angemessenen Unterschlupf haben, außerdem ein Straßennetz, auf dem die künftigen Einwohner sich schnell und bequem fortbewegen können. @PLegen Sie Wohngebiete an, und es wird nicht lange dauern, bis die Menschen das Dorf besiedeln. @G50 @L@LStraßen @L@PKlicken und ziehen Sie die Maus mit gedrückter Maustaste, wenn Sie rasch lange Straßen anlegen möchten. @G51 @PAn jeder Kreuzung müssen die Fußgänger wählen, welchen Weg sie nehmen. Mit jeder Kreuzung vermindert sich also Ihre Kontrolle über die Routen der Bewohner. @G52 @PPlanen Sie Wege sorgfältig und mit so wenigen Kreuzungen wie möglich, um sicherzustellen, dass die Leute sich dorthin begeben, wo Sie es möchten.  @PDer Weg, auf dem die Einwanderer Ihre Stadt erreichen, wird Königreichstraße genannt. Einwanderer brauchen eine ungehinderte Verbindung zwischen der Königreichstraße und den Wohngebieten der Stadt. Wenn Sie diese lebenswichtige Verbindung mit der Außenwelt für irgendein Stadtviertel unterbrechen, dann verschwinden die Häuser dieses Viertels einfach von der Landkarte. @L@LUm ein beliebiges Nachrichtenfenster (wie dieses) zu schließen, müssen Sie nur die rechte Maustaste drücken." }
    }
    message_basic_healthcare {
        id: 250
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Gesundheitsversorgung" }
        content { text: "Ihre Stadt leidet an gesundheitlichen Problemen, wie dies bei einer steigenden Bevölkerungszahl zu erwarten ist. Malaria und andere Krankheiten sind die häufigsten gesundheitlichen Probleme, mit denen sich Ihr Volk herumplagen muss. Ist die Gesundheitsversorgung jedoch besonders unzulänglich, kann es zu größeren Epidemien kommen. @PKommen in einem Haus Malaria oder andere Krankheiten vor, sterben sämtliche Bewohner, und das Haus ist für eine bestimmte Zeit lang nicht bewohnbar. @G64 @L@LMalaria @L@PMalaria kommt am häufigsten in der Nähe von Wasser und Morast vor. Die Spezialkarte 'Risiken - Malaria' zeigt an, in welchen Häusern die Wahrscheinlichkeit des Auftretens dieser Krankheit am höchsten ist. @PZugang zu sauberem Wasser aus einer Zisterne und Insektenschutzmittel aus der örtlichen Apotheke verringern das Malaria-Risiko für jeden Haushalt sehr deutlich. Wie die meisten Gebäude muss auch die Apotheke Zugang zur Straße und zu Arbeitskräften haben. @G63 @L@LKrankheiten @L@PÄrzte können helfen, das Erkrankungsrisiko zu verringern, indem sie die Häuser in ihrem Einzugsgebiet mit Medizin versorgen. Eine regelmäßige Versorgung mit Nahrungsmitteln ist ebenfalls von großer Bedeutung, um Krankheiten zu verhindern. Die Spezialkarte 'Risiken - Krankheit' zeigt an, in welchen Häusern die Wahrscheinlichkeit des Auftretens von Krankheiten am höchsten ist." }
    }
    message_requests_from_other_cities {
        id: 251
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Forderungen anderer Städte"
            pos [0, 20]
        }
        content {
            text: "Eine Ihrer Partnerstädte ist in Not geraten und hat eine Forderung an Sie gestellt. Wenn Sie gute Beziehungen zum Rest des wachsenden Königreichs aufrechterhalten möchten, ist es meist ratsam, auf solcherlei Forderungen schnell und bereitwillig zu reagieren. @G65  @PSobald Sie genug von der gewünschten Ware beisammenhaben, kontaktieren Sie Ihren Aufseher der Politik, um eine Lieferung in die betroffene Stadt vorzunehmen."
        }
    }
    message_fire_in_the_village {
        id: 252,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Feuer im Dorf!" }
        content { text: "Irgendwo im Dorf ist ein Feuer ausgebrochen! @L@LNachrichten @L@PWenn Sie das Geräusch hören, das ertönte, als sich dieses Fenster öffnete, ist eine Nachricht für Sie angekommen. Klicken Sie auf den Nachrichten-Button, um die Nachricht zu lesen.@G70 Besonders wichtige Mitteilungen (wie diese) werden automatisch eingeblendet, bevor sie zusammen mit den übrigen Nachrichten gespeichert werden. Weniger wichtige Nachrichten, die Sie meist über Ereignisse informieren, die keiner sofortigen Aktion bedürfen, werden direkt in das Nachrichtenfenster gestellt, ohne direkt angezeigt zu werden. Achten Sie daher unbedingt auf das Nachrichten-Geräusch. @G66 @L@LUm sich in Zukunft vor Feuer zu schützen, können Sie jetzt eine Feuerwache errichten.  @PWie die meisten Gebäude im Dorf, die keine Wohngebäude sind, braucht die Feuerwache Arbeiter für den Betrieb. Um Arbeitskräfte zu finden, wird jemand aus dem Gebäude entsandt, um bewohnte Häuser zu suchen. Sobald ein bewohntes Gebäude gefunden wird, bekommt die Feuerwache Mitarbeiter. Dann können aus der Feuerwache Feuerwehrmänner entsandt werden, um im Dorf zu patrouillieren.  @PFeuerwehrmänner überprüfen die Gebäude auf ihrer Patrouille auf Brandgefahr hin und verringern so das Risiko, dass ein Gebäude Feuer fängt. Feuerwehrmänner können all jene Gebäude bedienen, die im Abstand von höchstens zwei Feldern von einer Straße entfernt liegen. @PEntdeckt ein Feuerwehrmann ein Feuer, löscht er die Flammen mit Eimern voll Wasser und geht dann weiter seine Runden. @G67 @L@PWenn ein Gebäude abbrennt, klicken Sie mit der rechten Maustaste auf den übrig gebliebenen Schutthaufen, um zu erfahren, welches Gebäude abgebrannt ist." }
    }
    message_tutorial_collapsed_building {
        id: 253,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Eingestürztes Gebäude" }
        content { text: "Einige der großen Gebäude in Ihrer Stadt können einstürzen, wenn sie nicht entsprechend gepflegt werden. Um solchen Einstürzen vorzubeugen, können Sie einen Ingenieursposten bauen. Wie bei der Feuerwache werden auch aus diesem Gebäude Arbeitskräfte - in diesem Fall Bauingenieure - entsandt, um in den Straßen ihre Runden zu gehen und alle beschädigten Gebäude zu reparieren, auf die sie stoßen. @G68 @L@PMit Hilfe der Spezialkarte 'Risiken' können Sie einsturzgefährdete bzw. brandgefährdete Gebäude auffinden." }
    }
    message_tutorial_education {
        id: 254
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Der Unmut der Götter", pos [0, 15] }
        content {
            text: "Ihre Bürger sind in Sorge, dass dieser oder jener Gott grollen könnte. Manche hatten gar Visionen von schrecklichen Katastrophen, die bevorstehen würden. Besänftigen Sie mit Tempeln oder Festen zu Ehren der Götter deren Groll, wenn Sie vermeiden wollen, dass sich ihr Zorn in einem Strafgericht über Ihrer Stadt entlädt."
        }
    }
    message_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Wasserversorgung",
            pos [0, 15]
        }
        content {
            text: "Ausgezeichnet! Es ist Ihnen gelungen, die Bewohner Ihrer Stadt zuverlässig mit Nahrung zu versorgen. Nun sollten Sie die Einwohner mit sauberem Wasser aus einer Zisterne versorgen. Zisternenwasser steht höher in der Gunst der Bevölkerung als Wasser aus dem Ziehbrunnen.  @L@LZisterne @LGenau wie Ziehbrunnen müssen Zisternen auf Land mit Grundwasser errichtet werden. Ob irgendwo Grundwasser vorhanden ist, sieht man daran, ob grünes Gras wächst. Eine Zisterne benötigt außerdem eine Verbindung zu Arbeitskräften aus nahe gelegenen Wohngebäuden. @G70.  @LSobald die Zisterne in Betrieb ist, werden von ihr Wasserträger entsandt, die alle Häuser in der direkten Umgebung mit sauberem Trinkwasser aus Eimern versorgen. "
        }
    }

    message_tutorial_municipal_structures {
    id: 256,
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Öffentliche Einrichtungen" }
        content {
            text: "Abgesehen von Palast, Feuerwache und Polizeiposten tragen weitere öffentliche Einrichtungen zum reibungslosen Ablauf des städtischen Lebens bei.  @L@LGärten @L@PGärten werten die umliegende Gegend auf und ermutigen die Ägypter, ihre Häuser auszubauen. Mehrere Gartenanlagen nebeneinander werden zu größeren Parks zusammengeschlossen. @G72 @L@LBrücken und Fähren @PDurch den sorgfältig geplanten Bau von Fähren und Brücken können die Bewohner Ihrer Stadt Gegenden erreichen, die ansonsten nicht zugänglich wären. @G71 In einigen Fällen tragen sie dazu bei, dass der Ablauf in der Stadt besser funktioniert, indem manche Lieferanten kürzere Wege zurücklegen müssen. Aus bautechnischen Gründen können nur auf bestimmten, geraden Küstenabschnitten Brücken und Fähren eingerichtet werden. "
        }
    }
    message_tutorial_monuments_and_more {
        id: 257,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Monumente und mehr",
            pos [0, 15]
        }
        content {
            text: "Jetzt, da Sie im Demo-Programm so weit gekommen sind, können Sie ein bisschen mehr von dem sehen, was Pharao zu bieten hat. Denken Sie daran, die neu verfügbaren Aufseher zu konsultieren, um weitere Informationen und Hilfe bei der Verwaltung der aufblühenden Stadt zu erhalten. @L@LMonumente @L@PJetzt können Sie anfangen, Ihre eigene Mastaba zu errichten! Dazu benötigen Sie einen Vorrat an Ziegeln sowie Maurer und Bauern als Arbeitskräfte (aus Arbeiterlagern), um diese 'monumentale' Aufgabe zu bewältigen. @G75 @L@LWeitere Haushaltswaren @L@PAbgesehen von Töpferwaren benötigen ägyptische Haushalte einen Vorrat an Bier und Leinen. Bier wird in einer Brauerei aus Gerste hergestellt, die auf Farmen vor Ort angebaut wird. Leinen wird von Webern aus Flachs hergestellt, das ebenfalls vor Ort angebaut wird. Genau wie Nahrungsmittel und Töpferwaren werden auch Bier und Leinen durch Arbeitskräfte vom Basar an die Bewohner der Häuser verteilt. @L@LRecht und Ordnung @L@PEin Magistrat, der vom Gerichtsgebäude aus auf Patrouille geht, trägt dazu bei, das Risiko der Kriminalität zu reduzieren, indem er ein offenes Ohr für Sorgen hat und darauf achtet, dass alle einen kühlen Kopf behalten. @L@LGesundheit und Hygiene @L@PJede Stadt braucht einige Einbalsamierer, um hygienisch einwandfreie Verhältnisse zu wahren und um ihren betuchteren Bewohnern die angemessenen Begräbnisriten zu ermöglichen. Im Einbalsamierungshaus wird Leinen benötigt, das Weber herstellen. Dort werden den Bewohnern der Umgebung auch Einbalsamierungsdienste angeboten. Zahnärzte bieten den Bewohnern der Häuser, die sie besuchen, die sehr begehrten zahnärztlichen Dienste an. @L@LBildung @L@PSchulen und Bibliotheken können ohne Papyrus zum Schreiben keinen Unterricht erteilen. Schilfsammler beliefern Papyrushersteller mit dem notwendigen Rohstoff. Der Papyrus wird dann direkt an die Bildungseinrichtungen der Stadt verteilt. @G69 @L@LKriegsschiffe @L@PMöglicherweise müssen Sie die Küsten Ihrer Stadt mit stabilen Kriegsschiffen verteidigen. Zunächst einmal brauchen Sie dafür einen Holzhacker, der dem Schiffsbauer Holz liefert. Dieser stellt dann Schiffe für den Kriegshafen her. @G58 @L@LSteuern @L@PObwohl Sie noch keine zusätzlichen Einnahmen durch Handel und Export erzielen können, ist es doch möglich, der Bevölkerung in Form von Steuern einige Deben abzunehmen. Hierzu müssen Sie in der gesamten Stadt genügend Zentren für Steuereintreiber errichten, und zwar insbesondere in der Nähe der teueren Wohnhäuser der betuchteren Bewohner."
        }
    }
    message_tutorial_the_gods_of_egypt {
        id: 258
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Verehrung der Götter", pos [0, 15] }
        content {
            text: "Ohne geeignete Andachtsorte in Form von Tempeln und Schreinen kann eine ägyptische Stadt nicht wirklich aufblühen. Diese Stätten sollten sich in der Nähe der Häuser befinden, deren Bewohnern sie dienen sollen, und müssen einer von fünf Gottheiten geweiht sein:  @L@POsiris - Gott des Nils @PRe - Gott des Königreichs @PPtah - Gott der Handwerker @PSeth - Gott der Zerstörung @PBastet - Göttin des Heims @L@PJede Stadt hat verschiedene religiöse Neigungen. In irgendeiner Stadt wird einer dieser Götter meist besonders geschätzt - und ist sozusagen die Schirmgottheit - während die anderen Götter lediglich als 'lokale Gottheiten' verehrt werden (und wieder andere möglicherweise völlig unbekannt sind). Die Schirmgottheit von Thinis ist Bastet. @PEine Schirmgottheit kann leicht zornig werden, wenn sie meint, dass ihr nicht der gebührende Respekt gezollt wird. Sogar eine lokale Gottheit kann verärgert werden, wenn ihr nicht genügend Tempel und Schreine, gemessen an der derzeitigen Bevölkerungszahl, geweiht werden. @PHat ein Tempel Zugang zur Straße und zu Arbeitskräften in der Nähe, entsendet er Priester in die umliegenden Viertel, so dass die Bewohner 'Zugang' zur Gottheit des Priesters haben. @G73 @L@LAufseher der Tempel @L@PBefragen Sie Ihren Aufseher der Tempel, um den Status der einzelnen Gottheiten in einer Stadt zu bestimmen und um festzustellen, ob die Götter alle besänftigt sind. Blitze zeigen an, dass der Gott über die Stadt erzürnt ist, Sterne dagegen, dass er der Stadt freundlich gesonnen ist. Je mehr Blitze bzw. Sterne zu sehen sind, desto stärker wird die Stadt diese Laune des Gottes zu spüren bekommen (im Guten wie im Schlechten)."
        }
    }
    message_tutorial_industry_2 {
        id: 259
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Gewerbe" }
        content { text: "Jetzt, da Ihre Bevölkerung mit Nahrung und Wasser versorgt ist, können Sie den Lebensstandard mit weiteren Annehmlichkeiten wie z.B. Töpferwaren erhöhen.  @L@LGewerbestätten & Töpferwaren @L@PErrichten Sie nun eine Tongrube in der Nähe eines Gewässers und in deren Nähe eine Töpferei. Achten Sie darauf, dass beide Einrichtungen wie üblich Zugang zu Arbeitskräften haben. Dann wird es nicht lange dauern, bis dem Töpfer auf einem Wagen Ton geliefert wird und er die Stadt mit Töpferwaren versorgen kann.  @PErrichten Sie ein Warenlager, um die Endprodukte und eventuell überschüssigen Ton zu lagern (normalerweise liefert eine Tongrube genug Ton für zwei Töpfer).  @PArbeiter vom Basar holen die Töpferwaren im Lager ab und verteilen sie genau wie Nahrungsmittel. @G74 @LGewerbestätten wie Töpfereien versorgen die Stadtbewohner auch mit den nötigen Arbeitsstellen. Der Aufseher der Arbeitskraft (jetzt verfügbar) kann Ihnen bei der Zuteilung der Arbeitskräfte behilflich sein." }
    }
    message_tutorial_trade_with_other_cities {
        id: 260
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Handel mit anderen Städten" }
        content { text: "Nun, da Sie es geschafft haben, einigen Ihrer Untertanen zu Bildung zu verhelfen, könnten Sie der Stadt zusätzliche Einkünfte verschaffen, indem Sie überflüssigen Papyrus an benachbarte Städte verkaufen. Außerdem müssen Sie Ziegel aus Perwadiut importieren, um die geheiligte Mastaba zu errichten. Wenn Sie bereit sind, klicken Sie auf das Symbol der Weltkarte [graphic here], um herauszufinden, welche Städte es noch in der bekannten Welt gibt, und Handelsverbindungen aufzubauen." }
    }

    message_tutorial_flooded_clay_pit {
        id: 271
        type: 2
        message_type: 1
        pos [0, 88]
        size [30, 20]
        title { text: "Überflutete Tongrube" }
        content { text: "Es gab einen üblen Wassereinbruch in einer unserer Tongruben. Wir mussten die Grube zerstören, damit kein noch größeres Unglück geschieht." }
    }
    
    message_kingdom_road_blocked {
        id: 279,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title { text: "Dringend: Straße blockiert" }
        content { text: "Die Straße zum Königreich ist blockiert. Räumen Sie sofort das Geröll weg." }
    }
    
    message_wrath_of_ra {
        id: 280,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title { text: "Re zürnt ..." }
        video { text: "@23" }
        content { text: "Re straft Ihre Arroganz, indem er Ihren Ruf im ganzen Königreich deutlich heruntersetzt. So wie Sie den Gott mit Verachtung straften, werden die anderen Ägypter jetzt Sie wiederum strafen." }
    }
    message_wrath_of_seth {
        id: 281,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title { text: "Seth zürnt ..." }
        video { text: "@21" }
        content { text: "Ihr mangelnder Respekt gegenüber Seth hat den Gott dazu veranlasst, alle Ihre Schiffe zu zerstören!" }
    }
    message_the_world_map {
        id: 282,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Die Königreichkarte",
            pos [0, 15]
        }
        content {
            text: "Die Karte des Königreichs zeigt Ihnen, wo andere wichtige Städte in der Region liegen. Eine ihrer wichtigsten Funktionen ist wohl das Aufzeigen möglicher @47Handelspartner. @PKlicken Sie auf den Namen einer Stadt, um festzustellen, ob diese bereit wäre, mit Ihnen Handel zu treiben. Wenn die Stadt Handel treiben will, finden Sie unter dem Stadtnamen eine Liste der Produkte, die die Stadt kauft und verkauft, sowie die Kosten für die Eröffnung einer Handelsroute. Klicken Sie auf den Button 'Handelsroute öffnen', um Handelsbeziehungen aufzunehmen. @PHäufig erhalten Sie von anderen Städten Forderungen nach Waren oder Nachrichten über Kämpfe an anderen Orten. Die Königreichkarte hilft Ihnen, festzustellen, wo sich diese Städte befinden. Wird zum Beispiel eine Stadt in der Nähe angegriffen, sollten Sie auf der Hut sein. Schließlich könnte Ihre Stadt ebenfalls angegriffen werden. @PMehr über die Verwendung der Königreichkarte finden Sie unter den Themen @47Handel, @52Krieg&und&Frieden und @24Aufseher des Handels."
        }
    }
    message_tutorial_monuments {
        id: 283,
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monumente" }
        content {
            text: "Jetzt, da Sie Ziegel haben, können Sie mit der Arbeit an der heiligen Mastaba beginnen. Für die meisten Monumente benötigen Sie sowohl Facharbeiter als auch ungelernte Arbeiter. @L@LBaugilden @LBaugilden liefern die Facharbeiter, die Sie für den Bau von Monumenten brauchen. Mastabas bestehen vollständig aus Ziegeln, daher benötigen Sie nur die Dienste der Maurergilde für den Bau einer Mastaba. Sie können so viele Maurergilden einrichten, wie Ihre Wirtschaft das verkraftet. Sorgen Sie jedoch dafür, dass genügend Ziegel an der Baustelle angeliefert werden, damit die Maurer ständig beschäftigt sind. @PSobald die Maurergilde über genügend Maurer verfügt, werden diese an die Baustelle entsandt. Dort warten sie auf die Lieferung von Ziegeln durch ungelernte Arbeiter (Bauern). @L@LBauern/ungelernte Arbeiter @LSobald einige Maurer an der Baustelle sind und auf die Lieferung von Baumaterial warten, ziehen Gruppen von ungelernten Arbeitern (Bauern) Schlitten voller Ziegel zur Baustelle. Da die gleichen Bauern auch die Felder im Überschwemmungsgebiet bestellen müssen, werden Sie feststellen, dass der Bau von Monumenten etwas langsamer vor sich geht, nachdem die Nilflut zurückgewichen ist und die Bauern wieder zu ihrer Hauptarbeit auf die Felder zurückgekehrt sind. Abhilfe können Sie schaffen, indem Sie weitere Arbeiterlager errichten. So können alle Arbeitskräfte, die gerade nicht auf den Feldern benötigt werden, das ganze Jahr hindurch im Monumentbau beschäftigt werden. @G75 @L@LKlicken Sie zunächst auf das Icon 'Religiöse Einrichtungen', und suchen Sie dann nach einem geeigneten Standort für dieses große Gebäude."
        }
    }
    message_the_finer_things {
        id: 284,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Die Feinheiten",
            pos [0, 15]
        }
        content {
            text: "Tempelkomplexe @LIn dem Maße, in dem die Ergebenheit der ägyptischen Bürger gegenüber ihren Schutzgöttern wächst, verlangen sie nach immer großartigeren Kultstätten. Die meisten Städte werden danach streben, einen Tempelkomplex für die von ihnen geehrte Gottheit zu errichten, damit sie in den vollen Genuss der Gnade dieses Gottes oder dieser Göttin kommen. Einmal errichtet, kann der Tempelkomplex durch den zusätzlichen Bau eines Orakels oder Altars erweitert werden, zwei Einrichtungen, die jeweils anderen, nachgeordneten Gottheiten geweiht sind. Auch diese anderen Götter werden der Stadt daraufhin ihre Gunst zuteil werden lassen.  @L@LSchmuck @LWenn Edelsteine zur Verfügung stehen, können die Juweliere in Ihrer Stadt Schmuck herstellen. Schmuck gehört zu denjenigen Luxuswaren, nach denen die höheren Gesellschaftsschichten der Stadt verlangen.  @L@LLuxuswaren @LNeben vor Ort hergestelltem Schmuck schätzen die Ägypter auch bestimmte andere Luxuswaren, die nur über den Import angeboten werden können. Eine Stadt braucht Zugang zu mindestens zwei Sorten von Luxuswaren, damit sie sich wirklich 'zivilisiert' nennen darf.  @L@LSteinbrüche @LUm Stein - ein viel gefragtes Baumaterial - zu beschaffen, müssen Sie einen Steinbruch dort errichten, wo Felsgestein offen zu Tage tritt. Die Arbeiter im Steinbruch liefern Steinblöcke Stück für Stück an das Warenlager aus. Achten Sie darauf, dass Sie Architekten eingestellt haben, die dafür Sorge tragen, dass Steinbrüche nicht durch einen Felsrutsch zerstört werden!"
        }
    }
    message_innovations {
        id: 285,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Innovationen",
            pos [0, 15]
        }
        content {
            text: "Wiesenbewirtschaftung @LEinige Landstriche sind fruchtbar genug für die Landwirtschaft, selbst wenn sie nicht im Überschwemmungsgebiet liegen. Sie erkennen solche Wiesen am hohen, gelben Pflanzenwuchs. Einige der Farmen, die auf Wiesengrundstücke gebaut werden, können pro Jahr mehrere Ernten erzielen, obwohl die Erträge in der Regel ein wenig geringer ausfallen als bei einer Farm im Überschwemmungsgebiet. @G59  @L@LBewässerung @LSie können die Fruchtbarkeit jedes Ackerlands durch Bewässerung erhöhen. Bewässerungsgräben im Überschwemmungsgebiet können direkt mit dem Nil verbunden werden, aber für die Wasserversorgung der trockenen Gebiete brauchen Sie einen Wasserheber.  @L@LWasserheber @LWasserheber können entweder am Rand des Überschwemmungsgebiets oder am Ufer gebaut werden, von wo aus Wasser direkt aus dem Fluss auf trockenes Land geleitet werden kann. Verbinden Sie einen Bewässerungsgraben mit der rückwärtigen Seite des Wasserhebers, um so die Bewässerung von Farmen im Binnenland zu organisieren.  @L@LSteinmetze und Zimmerleute @LZwei neue Baugilden werden gebraucht, wenn eine Stufenpyramide errichtet werden soll: eine Steinmetz- und eine Zimmermannsgilde. Steinmetze der Gilde warten an der Baustelle auf Steinblöcke, die von Arbeitern dorthin transportiert werden. Diese Steinzieher benötigen Rampen, um die höheren Stufen des Bauwerks zu erreichen. Wenn es so weit ist, dass eine Stufenpyramide um eine weitere Ebene erweitert werden kann, schafft ein Zimmermann Holz aus seiner Gilde zum Bauplatz und baut dort eine Rampe für die Steinzieher. @L@LEinbalsamierung der Toten @LJede Stadt braucht einige Einbalsamierer, um hygienisch einwandfreie Verhältnisse zu wahren und um ihren betuchteren Bewohnern die angemessenen Begräbnisriten zu ermöglichen. Einbalsamierungshäuser benötigen in Webereien hergestelltes Leinen und bieten den Bewohnern der Umgebung die gewünschten Einbalsamierungsdienste an."
        }
    }
    message_company_returns {
        id: 287,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Kompanie kehrt zurück" }
        content { text: "Im Schutze der Nacht schleichen sich die überlebenden Mitglieder Ihrer gedemütigten Kompanie in den Schoß ihres Forts zurück. Niemals wieder wollen sie eine solche Niederlage im Kampf erleiden." }
    }
    message_heroes_return {
        id: 288,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Rückkehr der Helden!",
        }
        content {
            text: "Ihre siegreichen Soldaten sind aus dem Krieg zurückgekehrt. Ihre Zahl mag sich seit ihrem Auszug etwas verringert haben, doch der Opfertod ihrer Kameraden erfolgte zum Wohle Ägyptens!"
        }
    }
    message_city_retaken {
        id: 289,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "City retaken" }
    }
    message_osiris_is_upset {
        id: 290
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Osiris ist böse" }
        content { text: "Falls nicht bald etwas unternommen wird, um Osiris zu besänftigen, wird der Herr der Nilflut die Stadt für ihre Respektlosigkeit bestrafen und bei der nächsten Überschwemmung alle in ihrem Einzugsbereich liegenden Farmen vernichten!" }
    }
    message_ra_is_upset_2 {
        id: 291
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Re ist böse" }
        video { text: "@23" }
        content { text: "Über Ihre Respektlosigkeit verärgert, verschlechtert Re Ihren Ruf im ganzen Königreich." }
    }
    message_ptah_is_upset {
        id: 292
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Ptah ist böse" }
        video { text: "@22" }
        content { text: "Durch den fehlenden Respekt erbost, hat Ptah eines der Warenlager zerstört." }
    }
    message_seth_is_upset {
        id: 293
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Seth ist böse" }
        video { text: "@21" }
        content { text: "Seth hat die beste Kompanie der Stadt samt ihrem Fort vernichtet." }
    }
    message_bast_is_upset {
        id: 294
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Bastet ist böse" }
        video { text: "@20" }
        content { text: "Die Göttin Bastet ist über den mangelnden Respekt der Bürger erbost und hat eine schwarze Wolke der Verzweiflung über die Stadt geschickt." }
    }
    message_blessing_from_osiris {
        id: 295
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Osiris" }
        video { text: "@24" }
        content { text: "Osiris, Gott der Nilflut, segnet diese Stadt für ihre aufrichtige Verehrung. Die Ernte aller im Überschwemmungsgebiet gelegenen Farmen wird doppelt so reich ausfallen wie erwartet." }
    }
   message_blessing_trade_from_ra {
        id: 296
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Re" }
        video { text: "@23" }
        content { text: "Re belohnt die, die ihm treu ergeben sind! In den nächsten zwölf Monaten kann die Stadt für ihre Exportprodukte 50% mehr Gewinn erzielen." }
    }
    message_blessing_trade_from_ptah {
        id: 297
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Ptah" }
        video { text: "@22" }
        content { text: "Ptah erwählt ein Warenlager, dessen Kapazität noch nicht voll ausgeschöpft ist, und erhöht die darin vorhandene Menge an Edelsteinen, Ton, Flachs, Leinen oder Schmuck." }
    }
    message_blessing_trade_from_seth {
        id: 298
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Seth" }
        video { text: "@21" }
        content { text: "Seth sieht mit Wohlwollen, dass ihm Ehrfurcht und Gehorsam entgegengebracht werden, und wird den nächsten Feind niederstrecken, der es wagt Ihre Stadt zu überfallen." }
    }
    message_blessing_from_bast {
        id: 299,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Bastet" }
        video { text: "@20" }
        content { text: "Da diese Stadt Bastet so inniglich verehrt, segnet die Göttin ihre Häuser und Basare mit einem Überfluss an Nahrungsmitteln und Waren." }
    }
    message_the_gods_are_wrathful {
        id: 300
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Die Götter sind erzürnt" }
        content { text: "Mindestens eine Gottheit ist der Stadt zornig gestimmt. Dein Volk fleht dich an, mehr Tempel zu errichten … und ein Fest ist ebenfalls immer willkommen." }
    }
    message_illness {
        id: 301,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Krankheit" }
        video { text: "smk\\sick.smk" }
    }
    message_disease {
        id: 302,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Krankheit" }
        video { text: "smk\\sick.smk" }
    }
    message_pestilence {
        id: 303,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Seuche" }
        video { text: "smk\\sick.smk" }
    }
    message_the_spirit_of_seth {
        id: 304,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Der Schutzgeist des Seth ...",
        }
        video {
            text: "@21"
        }
        content {
            text: "Seth erinnert sich an sein Versprechen, die Stadt zu beschützen, und streckt mit Freude jene nieder, die unvorsichtig genug waren, Ihre Stadt zu bedrohen."
        }
    }
    message_the_emperors_respect {
        id: 305,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "The Emperor's respect",
        }
    }
    message_the_emperors_respect_1 {
        id: 306,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Der Respekt des Kaisers" }
    }
    message_the_emperors_respect_2 {
        id: 307,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Der Respekt des Kaisers" }
    }
    message_working_hippodrome {
        id: 308,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Funktionsfähige Rennbahn" }
        video { text: "smk\\\\1st_chariot.smk" }
    }
    message_compliance_now_possible {
        id: 309,
        type: 2,
        message_type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Forderung kann erfüllt werden" }
        content { text: "Der Aufseher der Politik berichtet, dass der Stadt jetzt genügend Deben zur Verfügung stehen, um die aktuelle Forderung zu erfüllen." }
    }
    message_tutorial_finances {
        id: 310,
        type: 2,
        message_type: 4
        size [40, 30]
        title { text: "Finanzen" }
        content {
            text: "Steuern @LEine große Stadt muss für weitere Einkünfte sorgen, denn das Startkapital ist bald aufgebraucht. Eine Möglichkeit, um Geld in die Kasse zu bringen, sind Steuern. Um Steuern einzutreiben, braucht die Stadt einen Palast und Steuereintreiber. Stellen Sie sicher, dass Sie genügend Steuereintreiberbüros erbauen, um die ganze Stadt - und vor allem die reicheren Viertel - steuerlich zu erfassen. Denken Sie daran: Je höher die Lebensqualität in einem Haus ist, desto mehr Steuern zahlen die Bewohner. @L@LIhr persönliches Gehalt @LWenn Sie sich einen Wohnsitz errichten, können Sie aus der Finanzkasse ein Gehalt beziehen. Persönliche Ersparnisse werden von Ihrer Familie aufbewahrt und können, wann immer es die Situation erfordert, genutzt werden - auch in folgenden Missionen. Doch Vorsicht: Falls Sie sich ein Gehalt bezahlen, das über dem für Ihre Position als angemessen empfundenen liegt, kann das einen negativen Einfluss auf Ihren Ruf im Königreich haben."
        }
    }
    message_mission_defeat {
        id: 311,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Niederlage!" }
        content { text: "Ein bitterer Tag! Ein solch unrühmliches Ende ist eigentlich undenkbar. Sie haben Ihr Volk, Ihre Vorfahren und Ihre Nachkommen enttäuscht. Nun sehnt sich Ägypten nach einem anderen Helden, der Ihren Platz einnehmen wird ..." }
    }
    message_mission_victory {
        id: 312,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Der Gewinner" }
        video { text: "smk\\win_game.smk" }
        content { text: "Unused entry 312" }
    }
    message_enemy_rome_army_attacks {
        id: 313
        type: 2
        message_type: 7
        pos [0, 88]
        size [30, 20]
        title { text: "Feindliche Armee greift an" }
        video { text: "smk\\spy_army.smk" }
        content { text: "Roms Feinde stehen vor den Toren deiner Stadt. Erwarte, dass sie hereinschneien, um sich ein oder zwei Krüge Wein zu holen – und alles andere, worauf sie sonst noch Lust haben!" }
    }
    message_storage_yards_ready_to_fulfill_request {
        id: 314,
        type: 2,
        message_type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Forderung kann erfüllt werden",
        }
        content {
            text: "Der Aufseher der Politik berichtet, dass die Warenlager der Stadt jetzt genügend Güter dieser Art enthalten, um die aktuelle Forderung zu erfüllen."
        }
    }
    message_kingdom_road_obstructed {
        id: 315,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Dringend: Straße blockiert",
        }
        content {
            text: "Die Architekten mussten einige erst kürzlich errichtete Gebäude einreißen, um den freien Zugang zur @57Königreichstraße wieder herzustellen. Räumen Sie sofort den Schutt weg."
        }
    }
    message_no_working_dock {
        id: 316,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Kein funktionierendes Dock..." }
        content { text: "Obwohl Sie dem Aufseher des Handels aufgetragen hatten, Handelsbeziehungen zu einem zur See fahrenden Händler aufzubauen, kann der Händler in Ihrer Stadt nicht landen! Sie müssen ein Dock errichten und es mit Arbeitskräften versorgen. Sobald das Dock funktioniert, werden Schiffe anlegen und mit dem Handel beginnen." }
    }
    message_fishing_boats_cant_navigate {
        id: 317,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Fischerboote sind blockiert" }
        content { text: "Unsere Fischer berichten, dass eine Brücke sie behindert! Schiffe können unter Brücken nicht hindurchsegeln. Entfernen Sie die Brücke, damit die Fischerboote Ihre Stadt mit frischem Fisch versorgen können." }
    }
    message_health {
        id: 318,
        type: 3,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Gesundheit",
        }
        content {
            text: "Das Volk möchte gesund bleiben. Wenn die Menschen gut ernährt und regelmäßig von einem Arzt besucht werden, sollten sie eigentlich hübsch gesund bleiben. Sollte ihre Gesundheit jedoch beeinträchtigt werden, besteht ein größeres Risiko, krank zu werden. @PKrankenhäuser kommen sehr gelegen, wenn die Bürger krank werden. Jeder Kranke benötigt ein Krankenhaus, um dort geheilt zu werden. Falls es jedoch keinen Platz im Krankenhaus gibt, müssen diese Menschen sterben. @PKurz: Arztpraxen tragen zur Verhinderung von Krankheiten bei, während Krankenhäuser sie behandeln. @L@LHin und wieder kann durchaus eine Seuche ausbrechen, und man weiß, dass Bastet einer Stadt, die sie verärgert hat, Krankheiten schickt. In solchen Zeiten ist eine gute Versorgung durch Krankenhäuser die einzige Verteidigung. Der Aufseher der Gesundheit kann Ihnen sagen, ob Ihre Stadt gut mit Krankenhäusern versorgt ist oder nicht."
        }
    }
    message_messages_await_you {
        id: 319,
        type: 3,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Nachrichten warten auf Sie",
        }
        content {
            text: "Wenn Sie eine Fanfare hören, bedeutet dies, dass Ihr Schreiber eine weitere Nachricht für Sie erhalten hat und sie für Sie aufbewahrt. @L@LEinige Nachrichten, wie diese hier, werden automatisch für Sie geöffnet. Sie enthalten sehr wichtige Mitteilungen, von denen Ihr Schreiber glaubt, dass Sie sie unbedingt sofort lesen müssten. Wenn Sie möchten, können Sie sie später noch einmal ansehen, indem Sie auf den Nachrichten-Button klicken. @PWichtige, jedoch nicht so dringende Mitteilungen werden ebenfalls durch eine Fanfare angekündigt, erscheinen allerdings nicht automatisch. Die meisten Nachrichten sind normale Mitteilungen mit einfachem Fanfarenstoß, die Sie je nach Belieben lesen können. @L@LSämtliche Nachrichten werden von Ihrem Schreiber aufbewahrt, so dass Sie, wenn Sie wollen, später noch einmal darauf zurückgreifen können. Sie können die Nachrichten auch löschen, wenn Sie wollen. Falls Sie weitere Informationen darüber möchten, wählen Sie in der Menüleiste die Option 'Hilfe' an und klicken auf 'Nachrichten Ihrer Schreiber' (gegen Ende des Inhaltsverzeichnisses)."
        }
    }
    message_local_uprising {
        id: 320,
        message_type: 7
        pos [0, 88]
        size [30, 20]
        urgent: 1
        title { text: "Lokaler Aufstand" }
        content { text: "Angestachelt durch Seth haben sich einige Bewohner dazu entschlossen, ihrem Ärger Luft zu machen, den sie so lange unterdrückt haben!" }
    }
    message_small_blessing_from_osiris {
        id: 321
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Osiris" }
        video { text: "@24" }
        content { text: "Die Verehrung, die Ihre Stadt Osiris, dem Herrn der Nilflut entgegenbringt, wurde mit Wohlwollen registriert. Falls sie Osiris weiterhin auf diese Art verehrt, wird die Überschwemmung im nächsten Jahr perfekt sein und reichlich fruchtbaren Schlamm im Überschwemmungsgebiet ablagern." }
    }
    message_minor_blessing_from_ra {
        id: 322
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Re" }
        video { text: "@23"}
        content { text: "Von der ihm entgegengebrachten Ehrfurcht angetan, verbessert Re etwas Ihren Ruf im Königreich." }
    }
    message_minor_blessing_from_ptah {
        id: 323
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Ptah" }
        video { text: "@22" }
        content { text: "Ptah ist mit Ihrer Aufmerksamkeit zufrieden und stellt sicher, dass die Werften, Webereien oder Juweliere Ihrer Stadt einen vollen Vorrat an Rohmaterial haben." }
    }
    message_minor_blessing_from_seth {
        id: 324
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Seth" }
        video { text: "@21" }
        content { text: "Um Ihren Gehorsam ihm gegenüber zu belohnen, verspricht Seth, alle Ihre Soldaten zu beschützen, die in fremden Ländern kämpfen." }
    }
    message_small_blessing_from_bast {
        id: 325
        type: 2
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Bastet" }
        video { text: "@20" }
        content { text: "Bastet ist erfreut, dass Ihre Stadt sie ehrt. Sie hat ein Fest ausgerichtet, damit alle Götter Ihre Frömmigkeit sehen." }
    }
    message_disease_strikes {
        id: 326,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Krankheit bricht aus",
        }
        content {
            text: "In einem Haus mit schlechter Gesundheitsversorgung ist eine Krankheit ausgebrochen. Die Leute sterben, und niemand kann ihnen helfen. Verbessern Sie die Gesundheitsversorgung in ungesunden Gegenden, damit das nicht wieder vorkommt."
        }
    }
    message_a_plague {
        id: 327,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Eine Seuche",
        }
        content {
            text: "In der Stadt ist eine Seuche ausgebrochen! Wir haben so etwas schon befürchtet, da der allgemeine @53Gesundheitszustand&der&Stadt so schlecht ist. Beten Sie, dass unsere Apotheker damit fertig werden."
        }
    }
    message_malaria {
        id: 328,
        type: 2,
        message_type: 1,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Malaria",
        }
        content {
            text: "In einigen Häusern hat es Fälle von Malaria gegeben. Verbessern Sie die Gesundheitsversorgung, um diesen sinnlosen Verlust menschlichen Lebens zu verhindern!"
        }
    }
    message_blessing_reputation_from_ra {
        id: 329,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Eine Segnung von Re" }
        video { text: "@23" }
        content {
            text: "Sie haben Re die gebührende Ehre erwiesen, daher ist Ihr Ruf im Königreich jetzt erheblich besser als zuvor!"
        }
    }
    message_minor_blessing_trading_from_ra {
        id: 331,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Eine kleine Segnung von Re" }
        video { text: "@23" }
        content { text: "Als Anerkennung für Ihre respektvolle Verehrung bringt Re Ihre Handelspartner dazu, mehr von Ihren Produkten zu kaufen, als sie eigentlich vorhatten." }
    }
    message_wrath_of_ra_2 {
        id: 332,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Re zürnt ..." }
        video { text: "@23" }
        content { text: "Sie haben Res Zorn auf sich gezogen! Der Gott hat das Ansehen der aus Ihrer Stadt kommenden Waren verringert, und Ihre Handelspartner werden jetzt weit weniger kaufen, als sie dies zuvor taten." }
    }
    message_wrath_of_ra_3 {
        id: 333,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Re zürnt ..." }
        video { text: "@23" }
        content { text: "So wie Sie sich von Re abgewandt haben, werden sich nun auch Ihre Handelspartner von Ihnen abwenden. Ein volles Jahr lang wird keine Karawane und kein Handelsschiff Ihre Stadt aufsuchen." }
    }
    message_ra_is_upset {
        id: 334,
        type: 2,
        pos [0, 88]
        size [30, 20]
        image { id: 224, pos [15, 15] }
        title { text: "Re ist böse!" }
        video { text: "@23" }
        content { text: "So wie Sie Re im Stich gelassen haben, werden nun Ihre Handelspartner Sie im Stich lassen. Sie haben beschlossen, weniger von Ihnen zu kaufen als zuvor." }
    }
    message_wrath_of_bast_2 {
        id: 335,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Bast zürnt ...", }
        content { text: "Der Zorn der Bast ist über dich gekommen. Lächle schnell, wenn du es wagst, denn auch wenn sie heute keine Macht über dich hat … beim nächsten Mal hast du vielleicht nicht so viel Glück!" }
    }
    message_wrath_of_ra_4 {
        id: 336,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Re zürnt ...",
        }
        content {
            text: "Der bittere Zorn Ras ist über dich gekommen. Lächle schnell, wenn du es wagst, denn auch wenn du heute keine militärischen Mittel hast, lässt Seth sich nicht so leicht beleidigen. Hüte dich!"
        }
    }
    message_wrath_of_osiris_3 {
        id: 337,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Osiris zürnt ...",
        }
        video {
            text: "@24"
        }
        content {
            text: "Osiris ist außer sich vor Zorn, kann die Stadt jedoch nicht bestrafen. Das ist erfreulich, aber das nächste Mal hat die Stadt vielleicht nicht so viel Glück."
        }
    }
    message_blessing_inundation_from_osiris {
        id: 340,
        type: 2,
        pos [0, 24]
        size [30, 28]
        title { text: "Eine Segnung von Osiris" }
        video { text: "@24" }
        content { text: "Osiris belohnt die, die ihm Verehrung entgegenbringen. Die nächste Überschwemmung wird sehr viel besser als erwartet ausfallen." }
    }
    message_wrath_of_osiris_4 {
        id: 341,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title { text: "Osiris zürnt ..." }
        video { text: "@24" }
        content { text: "Osiris erinnert Sie an den Respekt, den Sie ihm schulden. Die nächste Überschwemmung wird schlechter ausfallen, als wir erwartet haben." }
    }
    message_mediocre_inundation_seers {
        id: 342,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Die Priester sagen für das kommende Jahr eine mittelmäßige Überschwemmung voraus." }
    }
    message_poor_inundation_seers {
        id: 343,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Die Priester sagen für das kommende Jahr eine geringe Überschwemmung voraus." }
    }
    message_no_inundation {
        id: 344,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Schlechte Nachrichten! Die Priester fürchten, dass die Überschwemmung in diesem Jahr ausbleiben wird!" }
    }
    message_poor_inundation {   
        id: 345,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Die Priester sagen für das kommende Jahr eine geringe Überschwemmung voraus. Damit dies nicht auch im folgenden Jahr passiert, muss Osiris bei Laune gehalten werden." }
    }
    message_mediocre_inundation {
        id: 346,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Unglücklicherweise sieht es so aus, als würde die Überschwemmung im kommenden Jahr nur durchschnittlich ausfallen. Wenn die Stadt Osiris mehr Aufmerksamkeit schenkt, wird sich das im folgenden Jahr hoffentlich nicht wiederholen." }
    }
    message_good_inundation {
        id: 347,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Die Priester des Osiris sagen für das kommende Jahr eine gute Überschwemmung voraus." }
    }
    message_excellent_inundation {
        id: 348,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Die Priester sind überglücklich. Sie erwarten für das kommende Jahr eine hervorragende Überschwemmung." }
    }
    message_perfect_inundation {
        id: 349,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title { text: "Nilometer-Vorhersage" }
        content { text: "Diese Stadt ist wahrlich gesegnet. Unsere Priester sagen für das kommende Jahr eine perfekte Überschwemmung voraus. Wird Osiris aufrichtig verehrt, könnte die Stadt auch im folgenden Jahr wieder damit gesegnet sein!" }
    }
    message_temple_complex_to_osiris {
        id: 350,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Tempelkomplex des Osiris",
        }
        subtitle {
            text: "Religion",
        }
        content {
            text: "Wenn Sie einen Tempelkomplex zu Ehren des Osiris bauen, ist der Gott willens, von Jahr zu Jahr bessere Überschwemmungen zu schicken. An den Tempelkomplex des Osiris können Sie Folgendes anbauen: @L@LAltar des Sobek, Gott der Fruchtbarkeit. @LSobek gewährt Priestern des Osiris die Macht, die Vorräte der Stadt an Nahrungsmitteln und Waren zu verlängern. Wenn die Priester des Osiris dann durch die Stadt gehen, geben sich die Menschen in den Häusern, an denen sie vorbeikommen, plötzlich mit weniger zufrieden. @L@LOrakel des Min, Gott der Regeneration. @LWenn Ihre Stadt Min mit einem Orakel huldigt, segnet er die Stadt, indem er Bäume und Schilf schneller nachwachsen lässt, die Vermehrung der Beutetiere beschleunigt und die Erträge von Fischerei und Jagd erhöht. @L@LDie Leute leben ausgesprochen gern neben einem Tempelkomplex. Weitere Informationen zum Thema 'Religion' finden Sie @51hier. @L@LKlicken Sie @376hier, um mehr über Osiris, Sobek und Min zu erfahren."
        }
    }
    message_temple_complex_to_ra {
        id: 351,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Tempelkomplex des Re",
        }
        content {
            text: "Re schaut wohlwollend auf eine Stadt, wenn sie ihm einen Tempelkomplex geweiht hat, und er belohnt die Stadt, indem er dafür sorgt, dass andere Städte im Königreich eine besonders gute Meinung von ihr haben. Der Bau eines Tempelkomplexes für Re erhöht Ihre Königreich-Wertung, und Sie müssen einen geringeren Zinssatz bezahlen, falls die Stadt Schulden haben sollte. Der Anbau eines Altars und eines Orakels an den Tempelkomplex des Re hilft Ihnen bei der Verwaltung städtischer Angelegenheiten: @L@LAltar der Maat, Göttin der Gerechtigkeit. @LDurch die Priester des Re hat Maat beruhigende Wirkung auf Ihre Stadt. Wenn Res Priester an den Häusern vorüberwandern, können sie einzelne Bewohner dazu bringen, ihre Hände nicht nach anderer Leute Eigentum auszustrecken. Die bloße Gegenwart des Altars verringert das Risiko der Kriminalität insgesamt. @L@LOrakel des Horus, Gott der Pharaonen. @LDieses Orakel erhöht die Ergebenheit der Bürger Ihrer Stadt und dem Königreich gegenüber und trägt dazu bei, dass sie einer schlechteren Entlohnung mit Gleichmut begegnen. @L@LDie Leute leben ausgesprochen gern neben einem Tempelkomplex. Weitere Informationen zum Thema 'Religion' finden Sie @51hier. @L@LKlicken Sie @377hier, um mehr über Re, Maat und Horus zu erfahren."
        }
    }
    message_temple_complex_to_ptah {
        id: 352,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Tempelkomplex des Ptah",
        }
        content {
            text: "Wenn Sie Ptah einen Tempelkomplex bauen, beschleunigt der Gott die Produktion in vielen Gewerbestätten der Stadt. Zu diesen zählen Goldminen, Kupferminen, Edelsteinminen, Tongruben, Werften, Juweliere und Webereien. Der Altar und das Orakel im Tempelkomplex des Ptah beschleunigen die Produktionsgeschwindigkeit in anderen Gewerbestätten und verbessern das pädagogische Geschick des Lehrkörpers. @L@LAltar des Amun, Gott der Sonne. @LVon Ihrer Aufmerksamkeit geehrt lässt Amun Steinbrüche, Holzfällerlager und Ziegeleien schneller arbeiten. @L@LOrakel des Thot, Gott der Weisheit und des Lernens. @LThot hat das Ziel, in so vielen Menschen wie möglich das Licht des Wissens anzuzünden. Wenn Sie ein Orakel des Thot bauen, benötigen Bibliothekare und Lehrer weniger Papyrus, um die Bürger der Stadt auszubilden. @L@LDie Leute leben ausgesprochen gern neben einem Tempelkomplex. Weitere Informationen zum Thema 'Religion' finden Sie @51hier. @L@LKlicken Sie @378hier, um mehr über Ptah, Amun and Thot zu erfahren."
        }        
    }
    message_temple_complex_to_seth {
        id: 353,
        pos [0, 88]
        size [30, 20]
        title { text: "Tempelkomplex des Seth" }
        content { text: "Wenn eine Stadt einen Tempelkomplex zu seinen Ehren errichtet hat, verleiht Seth den Soldaten der Stadt einen eisernen Willen, schenkt ihnen mehr Erfahrung und schützt sie im Kampf. Die Anbauten am Tempelkomplex des Seth sind:  @L@LAltar des Anubis, Gott des Todes. @LAnubis gewährt den Bürgern der Stadt leichteren Zugang zum ewigen Leben. Mit seinem Segen benötigen Einbalsamierungshäuser weniger Leinen, um Leichen für die Ewigkeit vorzubereiten.  @L@LOrakel der Sachmet, Göttin des Krieges. @LSachmet gibt Priestern des Seth die Macht, das Risiko der Kriminalität in den Häusern zu verringern, an denen sie vorbeikommen, und Verbrecher in der Stadt festzunehmen.  @L@LDie Leute leben ausgesprochen gern neben einem Tempelkomplex. Weitere Informationen zum Thema 'Religion' finden Sie @51hier. @L@LKlicken Sie @379hier, um mehr über Seth, Anubis und Sachmet zu erfahren." }
    }
    message_temple_complex_to_bast {
        id: 354,
        pos [0, 88]
        size [30, 20]
        title { text: "Tempelkomplex der Bastet" }
        content { text: "Der Göttin Bastet einen Tempel zu bauen, bringt jeder Stadt Glück. Bastet trägt zur Zufriedenheit der Bürger bei, indem sie deren Ansprüche zurückschraubt. Es ist Ausdruck ihrer Güte, wenn sich die Geschwindigkeit verringert, mit der Ihre Bürger Nahrungsmittel und Waren verbrauchen, und sich der Einfluss verlängert, der von Künstlern, Lehrern und Gesundheitsdiensten ausgeht. Ihre göttlichen Schwestern tragen das Ihre dazu bei, um das Leben Ihrer Bürger zu verbessern: @L@LAltar der Isis, Göttin der Heilkunst. @LDurch die Priesterinnen der Bastet legt Isis der Bevölkerung ihre heilenden Hände auf, entfernt kranke Fußgänger von den Straßen und reinigt infizierte Häuser, an denen die Priesterinnen vorbeikommen. Isis verbessert darüber hinaus den gesamten gesundheitlichen Zustand der Stadt. @L@LOrakel der Hathor, Göttin der Freude, der Liebe und der Feste. @LHathor, durch das zu ihren Ehren errichtete Orakel geschmeichelt, verbessert die Laune der Bürger und die @39Stimmung&in&der&Stadt. @L@LDie Leute leben ausgesprochen gern neben einem Tempelkomplex. Weitere Informationen zum Thema 'Religion' finden Sie @51hier. @L@LKlicken Sie @380hier, um mehr über Bastet, Isis and Hathor zu erfahren." }
    }
    message_building_firehouse {
        id: 355,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Feuerwache",
        }
        content {
            text: "Manche Gebäude der Stadt sind besonders feuergefährdet. Gefährdet sind vor allem heruntergekommene Wohngebiete und Gewerbestätten wie z.B. Töpfereien. Wenn Sie nichts gegen ein Feuer unternehmen, breitet es sich möglicherweise über die gesamte Stadt aus und zerstört nacheinander ganze Stadtteile. Um dies zu verhindern, sollten Sie Feuerwachen in der Nähe von Gebäuden errichten, von denen eine größere Feuergefahr ausgeht. Feuerwehrleute kommen aus Feuerwachen, drehen in der Stadt ihre Runden (klicken Sie @42hier, um weitere Informationen zum Thema 'Fußgänger' abzurufen) und verringern für jedes Gebäude, an dem sie vorbeikommen, die Gefahr eines Brandes. @PSollte ein Feuer ausbrechen, begeben sich die in der Nähe befindlichen Feuerwehrleute zum Brandherd, um die Flammen zu löschen. Ist der Weg für die Feuerwehrleute zu weit, können sich die Flammen ausbreiten und der Stadt großen Schaden zufügen. @G67 @PDie @18Spezialkarte&Feuer ist sehr nützlich, um Feuersbrünsten vorzubeugen. Die Karte zeigt die Feuerwehrleute bei der Arbeit und, was noch wichtiger ist, macht deutlich, welche Gebäude besonders gefährdet sind und leicht in Flammen aufgehen könnten. Benutzen Sie diese Informationen, um Ihre nächsten Feuerwachen zu platzieren. @PUm funktionieren zu können, benötigen Feuerwachen eine Straßenanbindung und Arbeitskräfte. Bürger wohnen jedoch nicht sehr gern neben Feuerwachen."
        }
    }
    message_building_warship_wharf {
        id: 356,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Kriegshafen",
        }
        content {
            text: "In Kriegshäfen liegen Kriegsschiffe vor Anker. Das Erste, was in einem neuen Kriegshafen geschieht, ist, dass ein Kriegsschiff bei der @82Werft in Auftrag gegeben wird.  @PEin Kriegshafen benötigt sowohl eine Straßenanbindung als auch Arbeitskräfte. Außerdem muss er an einem geraden Küstenabschnitt errichtet werden, und Schiffe müssen den Hafen leicht erreichen können. Zu nah an einem Kriegshafen lebt kein Bürger gerne. Schließlich haben manche Seeleute nicht den allerbesten Ruf. @PIst ein Kriegsschiff gerade nicht im Einsatz, bevorzugt die Besatzung die Sicherheit des Hafens. Hier kann sie sich für die nächste Schlacht ausruhen. @PUm herauszufinden, wie Sie ein Schiff im Kampf steuern können, lesen Sie den Eintrag über @365Kriegsschiffe. @L@LDie militärische Tradition des alten Ägypten ist lang und ereignisreich. Klicken Sie @184hier, um mehr darüber zu erfahren."
        }
    }
    message_building_transport_wharf {
        id: 357,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Transporthafen",
        }
        content {
            text: "In Transporthäfen liegen Transportschiffe vor Anker. Das Erste, was in einem neuen Transporthafen geschieht, ist, dass ein Transportschiff bei der @82Werft in Auftrag gegeben wird.  @PEin Transporthafen benötigt sowohl eine Straßenanbindung als auch Arbeitskräfte. Außerdem muss er an einem geraden Küstenabschnitt errichtet werden, und Schiffe müssen den Hafen leicht erreichen können. Zu nah an einem Transporthafen lebt kein Bürger gerne.  @PUm herauszufinden, wie Sie ein Schiff im Kampf steuern können, lesen Sie den Eintrag über @367Transportschiffe. @L@LDie militärische Tradition des alten Ägypten ist lang und ereignisreich. Klicken Sie @181hier, um mehr darüber zu erfahren."
        }
    }
    message_building_roadblock {
        id: 358,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Straßensperre",
        }
        content {
            text: "Setzen Sie Sperren vorsichtig ein. @L@LWenn Sie beispielsweise eine Sperre setzen, um zu verhindern, dass eine Basarhändlerin durch das Gewerbegebiet einer Stadt läuft (wo ihre Dienste nicht sehr nützlich sind), schneiden Sie damit auch Architekten und Feuerwehrleuten den Weg zu den Gewerbestätten auf der anderen Seite der Sperre ab und verhindern somit, dass sie dort ihre wichtigen Dienstleistungen erbringen können. Straßensperren, die Gewerbestätten von Wohngebieten trennen, können auch verhindern, dass die benötigten Mitarbeiter gefunden werden.   @L@LDie Sperren unterscheiden nicht zwischen verschiedenen umherwandernden Fußgängern - überlegen Sie sich also genau, wen Sie da aussperren."
        }
    }
    message_building_hunting_lodge {
        id: 359,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Jagdhof",
        }
        content {
            text: "Bauen Sie einen Jagdhof, um Jäger auf die Jagd zu schicken. Sie können Straußenvögel, Wasservögel und Antilopen jagen. @PJagdhöfe können überall errichtet werden, auch wenn es sinnvoll ist, sie in der Nähe des zu jagenden Wilds zu errichten. Dieses bleibt den Heimatgefilden meist recht treu. Jagdhöfe benötigen eine Straßenanbindung und Arbeitskräfte. Wenn Jagdhöfe in Betrieb sind, sehen Sie einen Jäger im Hof, der gerade Zielschießen übt. @PJäger gehen vom Jagdhof aus in die umliegenden Felder und Wälder, wo sie das Wild jagen. Wenn Sie ein Tier erlegt haben, bringen sie es zum Jagdhof, wo es für den Verzehr vorbereitet wird. Sobald eine Karrenladung Fleisch bereit ist, wird sie in @3Silos oder @4Warenlager verfrachtet (wenn Sie letzteren die Anweisung gegeben haben, Wild anzunehmen). @G60 @PWild kann ein wichtiger Bestandteil der Ernährung Ihrer Bürger sein. Es sorgt für die Abwechslung, die Ihre Bevölkerung wünscht. Allerdings wird es der Stadt wohl kaum gelingen, sich von Wild allein zu ernähren. Die Größe von Herden und Schwärmen ist begrenzt, so dass die Versorgung einer großen Stadt nur mittels der Jagd nicht möglich ist.  Mehr darüber, wie Sie Ihre Bürger ernähren können, finden Sie unter @45Landwirtschaft&und&Nahrungsmittelproduktion. @PWildfleisch wird (genau wie @89Stroh) als Futter für die Tiere im @479Zoo benutzt. @PJagdhöfe haben einen negativen Einfluss auf die @56Attraktivität eines Gebiets. @L@LDie Ernährung der alten Ägypter wurde durch Wild ergänzt. Außerdem war die Jagd ein beliebter Sport der gesellschaftlichen Elite. Klicken Sie @383hier, um mehr darüber zu erfahren."
        }
    }
    message_building_cattle_ranch {
        id: 360,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Rinderfarm",
        }
        content {
            text: "Züchten Sie Rinder auf einer Rinderfarm, um Fleisch für die Bürger der Stadt zu produzieren. @PRinderfarmen müssen an eine Straße angrenzen und benötigen Zugang zu Arbeitskräften. Außerdem benötigen sie Stroh - entweder von einer @89Getreidefarm, wo es quasi als Nebenprodukt anfällt, oder durch Import über einen @47Handelspartner. Rinderfarmen müssen nicht auf fruchtbarem Land errichtet werden und benötigen auch keine Wasseranbindung. @PLesen Sie unter @45Landwirtschaft&und&Nahrungsmittelproduktion nach, um mehr über die Bedeutung von Fleisch für die Ernährung Ihrer Bürger zu erfahren. @PRinderfarmen stinken gewaltig, daher wohnen Ihre Bürger nicht gerne in deren Nähe. @L@LDie alten Ägypter züchteten viele zum Verzehr bestimmte Tierarten. Klicken Sie @186hier, um mehr darüber zu erfahren."
        }
    }
    message_building_gemstone_mine {
        id: 361,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Edelsteinmine",
        }
        content {
            text: "Edelsteine werden in felsigen Gebieten abgebaut. Ob es in einem Felsgebiet Edelsteine gibt, ist jedoch durch einfache Betrachtung nicht feststellbar. Falls Edelsteine abgebaut werden können, werden Edelsteinminen in der Liste 'Gewerbliche Gebäude: Rohstoffe' aufgelistet. Genau wie @95Steinbrüche müssen Edelsteinminen in felsigem Gebiet angelegt werden und benötigen sowohl Straßenanbindung als auch Arbeitskräfte. Auch sie neigen zum Zusammenbruch, richten Sie daher unbedingt in der Nähe ein @81Architektenbüro ein. @PEdelsteinminen produzieren viel Staub, daher schätzen es die Bürger gar nicht, in ihrer Nähe zu wohnen. @L@LKlicken Sie @382, um mehr über Edelsteine im alten Ägypten zu erfahren."
        }
    }
    message_building_sphinx {
        id: 362,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Sphinx",
        }
        content {
            text: "Eine Sphinx ist eine aufwendig behauene und bemalte Schutzstatue der Pyramiden. @PUm eine Sphinx bauen zu können, müssen Sie zunächst einen Standort dafür wählen. Wählen Sie hierzu in der Liste 'Religiöse Einrichtungen: Monumente' die Option 'Sphinx' an. Ein Grundriss der Pyramide erscheint. Wenn Sie diesen Grundriss verschieben, wird er entweder komplett grün oder grün mit einer oder mehreren roten Rauten dargestellt. Ist er komplett grün, haben Sie einen geeigneten verdeckten Fels gefunden. Klicken Sie mit der Maustaste, und der Stein wird freigelegt. Falls jedoch auch nur ein Teil dieses Grundrisses als rote Raute erscheint, befindet sich auf dem gewählten Terrain etwas, das den Bau des Monuments an dieser Stelle verhindert.  @PIst eine geeignete Stelle gefunden, können sich @363Steinmetze und @363Zimmerleute an die Arbeit machen, vorausgesetzt, Sie haben das dafür benötigte Holz. Zimmerleute errichten das Gerüst, das Steinmetze erklimmen, um die Sphinx zu behauen. @PInfoklicken Sie auf die Sphinx, um den @369Vorarbeiter&des&Baus zu besuchen und einen Fortschrittsbericht abzurufen. @L@LKlicken Sie @391hier, um mehr über die berühmte Sphinx zu erfahren."
        }
    }
    message_construction_guilds {
        id: 363,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Baugilden",
        }
        content {
            text: "Ohne Baugilden können Sie die herrlichen Gebäude zu Ehren Pharaos und Ägyptens nicht errichten. @PEs gibt vier spezialisierte Baugilden: Zimmerleute, Maurer, Steinmetze und Kunsthandwerker. Obwohl die einfachen Arbeiter aus den @8Arbeiterlagern den Großteil der Muskelarbeit an einem Monument leisten, verwandeln erst die Experten der Gilden die Tonnen von Rohmaterial in die größten und komplexesten Bauwerke, die man sich vorstellen kann. Hierzu gehören die Pyramiden, die @362Sphinx, die @371Mastabas, die @69Sonnentempel, die @368Mausoleen und die @392Obelisken. Jedes Monument bedarf besonderer Gildenarbeiter. @PBaugilden müssen über eine Straßenanbindung und Arbeiter, die in der Nähe wohnen, verfügen. Die Zimmermannsgilde muss mit Holz versorgt werden. Die Kunsthandwerkergilde benötigt Farbe und Ton (zum Verputzen), um die Abschlussarbeiten an den Grabkammern vornehmen zu können. Maurer und Steinmetze warten auf der Baustelle auf das Material, das sie für den Bau des Monuments benötigen. @PAufgrund des Lärms wohnen Ihre Bürger nicht sonderlich gern neben Baugilden. @L@LWenn Sie weitere Informationen über diese Bauspezialisten benötigen, klicken Sie auf folgende Einträge: @386Maurer, @385Steinmetze, @389Zimmerleute und @472Kunsthandwerker."
        }
    }
    message_building_brickworks {
        id: 364,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Ziegelei",
        }
        content {
            text: "In Ziegeleien werden @92Ton und @89Stroh zu Ziegeln verarbeitet. Ziegel werden für den Bau verschiedener Monumenttypen verwendet und können @47exportiert werden. @PSobald eine Ziegelei über genügend Arbeitskräfte und Straßenzugang verfügt, benötigt sie auch einen Vorrat an Rohstoffen, um funktionsfähig zu sein. Ziegeleien benötigen Stroh und Ton, um arbeiten zu können. Stroh wird auf @89Getreidefarmen produziert, Ton wird in @92Tongruben abgebaut. Beide Rohstoffe lassen sich auch über einen @47Handelspartner importieren.  @PWenn in einer Ziegelei Ziegel hergestellt werden, sehen Sie Arbeiter, die im Hof schuften. Sobald eine Ladung Ziegel fertig ist, werden diese zu einem @4Warenlager gebracht. @PZiegeleien sind wenig @56attraktive Nachbarn. @L@LKlicken Sie @390hier, um mehr über Ziegel im alten Ägypten zu erfahren."
        }
    }
    message_building_warship {
        id: 365,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Kriegsschiff",
        }
        content {
            text: "Kriegsschiffe patrouillieren auf den Wasserstraßen und rammen andere Schiffe bzw. nehmen sie unter Beschuss, wenn diese der Stadt schaden wollen. Von Kriegsschiffen aus können auch Soldaten an Land mit Geschossen angegriffen werden, vorausgesetzt, das Schiff ist nahe genug an der Küste. Ein Kriegsschiff liegt in einem @356Kriegshafen vor Anker. Es ist leicht von einem Transportschiff zu unterscheiden, da es keinen hinteren Kabinenaufbau hat und schlanker ist. @L@LAngriffsprioriäten @LUnabhängig von den Befehlen, die Sie einem Kriegsschiff erteilen, folgt dessen Kapitän stets den gleichen Prioritäten beim Angriff auf den Feind. Diese sind: @L@LTransportschiffe mit feindlichen Soldaten an Bord. @LDer Kapitän weiß, dass seine Mission weitgehend fehlgeschlagen ist, wenn es feindlichen Truppen gelingt, an Land zu gehen. Wenn sich in den Gewässern um die Stadt Schiffe mit feindlichen Soldaten befinden, greift er diese zuerst an, und zwar bevor sie ihre Soldaten an Land absetzen können. @L@LVon Bord gegangene Feinde in Ufernähe. @LKann der Kapitän nicht verhindern, dass feindliche Soldaten an Land gehen, segelt er in Küstennähe und lässt einen Pfeilhagel auf die Soldaten in Reichweite niedergehen.  @L@LKriegsschiffe @LFeindliche Kriegsschiffe kommen an dritter Stelle. Findet der Kapitän weder Transportschiffe mit Truppen an Bord noch an Land gegangene Feinde, versucht er, erreichbare feindliche Kriegsschiffe zu rammen.  @L@LLeere Transportschiffe des Feindes. @LLeere Transportschiffe stehen ganz unten auf der Liste. Sie werden angegriffen, wenn es sonst nichts anzugreifen gibt. @L@LDer Kapitän reagiert schnell auf Veränderungen. Entsteht eine Situation, in der sich seine Prioritäten ändern, bricht er auch schon mal Kämpfe ab. Ist er beispielsweise gerade dabei, ein Kriegsschiff anzugreifen, und ein Transportschiff mit feindlichen Truppen an Bord dringt in das von ihm geschützte Gebiet ein, lässt er von dem Kriegsschiff ab und greift das Transportschiff an.  @L@LAnordnungen für Kriegsschiffe @LMit einem Infoklick auf das Kriegsschiff erteilen Sie ihm einen Befehl. Kriegsschiffe können folgende Befehle ausführen: @L@LPosition halten @LWenn dieser Befehl erteilt wurde, entfernt sich das Kriegsschiff nicht von der festgelegten Stelle. Das Schiff verteidigt sich, indem es sich so zu feindlichen Kriegsschiffen hindreht, dass Schäden durch Ramm-Angriffe minimal gehalten werden. Feinde in Reichweite werden mit Pfeilen angegriffen. Wenn mehrere Kriegsschiffe aufgereiht sind und allen der Befehl 'Position halten' erteilt wurde, formieren sie sich zu einer Blockade mit dem Ziel, Eindringlinge abzuhalten.  @L@LFeinde in der Nähe angreifen @LWenn dieser Befehl erteilt wird, greift das Kriegsschiff Feinde in einem kleinen Umkreis um seine aktuelle Position an.  @L@LAlle Feinde suchen und vernichten @LWenn dieser Befehl erteilt wird, sucht das Kriegsschiff die Gewässer nach Feinden ab, denen es den Garaus machen kann.  @L@LReparieren @LSollte das Kriegsschiff bei einer Auseinandersetzung beschädigt werden, können Sie das Schiff mit diesem Button zur Reparatur in die Werft schicken. Wurden die Reparaturen ausgeführt, kehrt das Schiff in seinen Heimathafen zurück. Ist das Schiff schwer beschädigt, bringt der Kapitän das Schiff selbständig in die Werft. Schiffbauer brauchen Holz, um Kriegsschiffe zu reparieren.  @L@LZurück zum Hafen @LKlicken Sie auf diesen Button, um das Kriegsschiff wieder in den Hafen zu schicken. @L@LUm ein Kriegsschiff zu verlegen, klicken Sie zunächst auf das Schiff und dann auf die neue Position. Sobald das Schiff am neuen Standort ankommt, wird der zuletzt erteilte Befehl ausgeführt. Wenn Sie auf einen Feind klicken, verfolgt das Kriegsschiff den angewählten Feind, bis er besiegt ist, bzw., wenn es sich um ein Ziel an Land handelt, bis das Ziel nicht mehr in Reichweite ist. @L@LKlicken Sie @184hier, um mehr über Kampftechniken im alten Ägypten zu erfahren."
        }
    }
    message_building_festival_square {
        id: 366,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Festplatz",
        }
        content {
            text: "Bevor Sie ein Fest veranstalten können, benötigen Sie einen Festplatz in der Stadt. (Unter @51Religion finden Sie weitere Informationen zum Thema 'Feste'.) Ein Festplatz muss auf einer Kreuzung eingerichtet werden, benötigt aber keine Arbeitskräfte. In jeder Stadt kann es nur einen Festplatz geben. Festplätze sind äußerst @56beliebte Nachbarn.  @PWenn gerade kein Fest im Gange ist, ist der Festplatz meist verlassen, hat jedoch keine negativen Auswirkungen auf die Straßen, auf denen er gebaut wurde. Wenn das Fest anfängt, versammeln sich hier Menschen aus der ganzen Stadt, um die Feier zu genießen.  @PDie alten Ägypter hielten Feste zu vielen Anlässen ab. Klicken Sie @393hier, um mehr darüber zu erfahren."
        }
    }
    message_figure_transport_ship {
        id: 367,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Transportschiffe",
        }
        subtitle {
            text: "Transportschiffe",
        }
        content {
            text: "Transportschiffe befördern Ihre Armee über den Fluss und über das Meer in ferne Länder. Jede Kompanie kann an Bord eines Transportschiffs gehen, allerdings kann ein Schiff immer nur eine Kompanie befördern. Ein Transportschiff liegt in einem @357Transporthafen vor Anker. Es ist durch seinen Kabinenaufbau leicht von einem Kriegsschiff zu unterscheiden. @L@LBefehle für Transportschiffe @LSie können Transportschiffen spezielle Befehle erteilen. Um ein Transportschiff von einer Position an eine andere zu verlegen, klicken Sie erst auf das Schiff und dann auf die neue Position. Infoklicken Sie auf das Transportschiff, um ihm einen der folgenden Befehle zu erteilen: @L@LPosition halten @LHiermit wird dem Transportschiff befohlen zu bleiben, wo es ist. Wird das Transportschiff angegriffen, dreht der Kapitän das Schiff, um zu versuchen, den Schaden in Grenzen zu halten. Allerdings wird er nicht von dannen segeln, um dem Angriff zu entgehen. Mit dieser Option sollten Sie vorsichtig umgehen, da Transportschiffe nicht gut für ihre Verteidigung gerüstet sind.  @L@LGegnern ausweichen @LTransportschiffe, insbesondere die, mit denen Sie Ihre Soldaten transportieren, sind sowohl wertvoll als auch verletzlich. Klicken Sie auf 'Gegnern ausweichen', um dem Kapitän die Möglichkeit zu geben, mit allen Kräften einen Angriff zu vermeiden. Der Kapitän wird immer versuchen, Gegnern auszuweichen, solange Sie ihm nichts Gegenteiliges befehlen.  @L@LAn/Von Bord gehen @LUm eine Kompanie Soldaten auf ein Transportschiff zu beordern, klicken Sie erst auf den Button 'An Bord gehen' und dann auf die Kompanie, die über das Gewässer befördert werden soll. Die Soldaten gehen an Bord, und auf dem Schiff wird die Flagge der Kompanie gehisst. Wenn Sie auf das Transportschiff infoklicken, werden Informationen über die an Bord befindliche Kompanie angezeigt. @PUm die Soldaten wieder an Land gehen zu lassen, klicken Sie auf 'Von Bord gehen' und setzen den Mauszeiger dann auf die Position, an der die Kompanie stationiert werden soll. @PDie Option 'An Bord gehen/Von Bord gehen' schaltet hin und her, je nachdem, ob sich gerade Soldaten an Bord befinden oder nicht.  @L@LReparieren @LIst ein Transportschiff beschädigt, klicken Sie auf 'Reparieren', um das Schiff für Reparaturarbeiten in die @82Werft zu beordern. Ist der Rumpf schwer beschädigt, bringt der Kapitän das Schiff selbständig in die Werft. Schiffbauer brauchen Holz, um Kriegsschiffe zu reparieren.  @L@LZurück zum Hafen @LKlicken Sie auf diesen Button, um das Transportschiff wieder in den @357Hafen zu schicken."
        }
    }
    message_building_mausoleum {
        id: 368,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Mausoleum",
        }
        content {
            text: "Mausoleen sind große Grabmäler für Pharaonen und Adlige.  @PFür den Bau eines Mausoleums benötigen Sie @95Sandstein und @94Holz sowie mindestens eine funktionierende @363Zimmermannsgilde, @363Steinmetzgilde sowie Arbeiter aus dem @8Arbeiterlager. @PBevor ein Mausoleum platziert werden kann, müssen die @4Warenlager der Stadt genug Sandstein enthalten. Sobald genug Stein vorrätig ist, wählen Sie in der Liste 'Religiöse Einrichtungen: Monumente' die Option 'Mausoleum' an. Platzieren Sie das Mausoleum mit Hilfe der farbigen Grundrisse (grün bedeutet, Sie können das Gebäude hier platzieren, rot bedeutet, dass dies nicht möglich ist). Sobald Sie einen Bauplatz für das Gebäude bestimmt haben, planieren Bauern aus dem Arbeiterlager das Land und bauen das Fundament. @PWenn das Fundament steht, fangen die Steinmetze mit der Arbeit an. Immer wenn sich in einem Warenlager vier Sandsteinblöcke angesammelt haben, laden Arbeiter den Stein auf einen Schlitten und ziehen diesen zur Baustelle. Steinmetze bringen den Stein an seinen Platz, bis das erste Geschoss fertig ist. Dann stellen Zimmerleute hölzerne Rampen auf, damit die Steinmetze mit der Arbeit am zweiten Geschoss beginnen können. Steht das zweite Geschoss, ist das Mausoleum fertig. @L@LKlicken Sie @396hier, wenn Sie an Informationen über die Geschichte dieser Gräber interessiert sind."
        }
    }
    message_figure_construction_foreman {
        id: 369,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Vorarbeiter des Baus",
        }
        content {
            text: "Sobald mit dem Bau begonnen wurde, verfügt der Vorarbeiter über noch weitaus ausführlichere Informationen über den Status des Monuments. Er unterhält eine stets aktuelle Aufstellung, wie viel von welchem Baustoff für die Fertigstellung des Monuments benötigt wird. Wenn der Bau nicht richtig vorankommt, kann er Ihnen mitteilen, woran dies liegt. Um den Vorarbeiter des Baus zu besuchen, infoklicken Sie auf die Monumentbaustelle."
        }
    }
    message_building_monument_construction {
        id: 370,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Bau von Monumenten",
        }
        content {
            text: "Für den erfolgreichen Abschluss der meisten Missionen ist es notwendig, mindestens ein Monument zu errichten. Für manche Missionen müssen Sie sogar mehrere bauen. Die Monumente können Sie in beliebiger Reihenfolge errichten. @PBeim Bau der meisten Monumente warten die Arbeitskräfte der @363Baugilde darauf, dass Bauern aus einem @8Arbeiterlager die benötigten Materialien von einem @4Warenlager besorgen und herbeischaffen. Die Bauern laufen so weit es nötig ist, um den Bauplatz des Monuments zu erreichen. Bei @362Sphinx und @372Obelisk funktioniert das etwas anders. @G75 @PDie Arbeiter der Stadt können an mehr als einem Monument gleichzeitig arbeiten, und in der Tat ist die Versuchung groß, diese Möglichkeit zu nutzen. Seien Sie jedoch gewarnt, dass ein solcher Plan möglicherweise nicht so weise ist, wie dies zunächst den Anschein haben mag. Ein Bau kann ins Stocken geraten, wenn @363Steinmetze und Transporteure ihre Arbeit nicht mehr koordinieren können. So kann es durchaus passieren, dass an der Baustelle des einen Monuments Baustoffe angeliefert werden, die Steinmetze aber auf der anderen Baustelle sind und dort mangels Baustoffen nicht weiterarbeiten können.  @PSolche Situationen bereiten dem @373Aufseher&der&Monumente große Sorgen, denn es ist schwerer, als man denkt, die Halsstarrigkeit der Transporteure mit der Dickköpfigkeit der Steinmetze in Einklang zu bringen. Von solchen Konflikten bleibt man verschont, wenn man Monumente nacheinander statt gleichzeitig errichten lässt. @PAufgrund ihrer enormen Größe sind manche Monumente in der Stadt sehr schwierig zu platzieren. Bei den größten Monumenten ist darüber hinaus nie die gesamte Grundfläche des Baus auf einmal zu sehen. @PUm die Eignung eines bestimmten Standorts für ein Monument zu beurteilen, drücken Sie die M-Taste. Der Grundriss des Monuments wird an der gewählten Stelle fixiert, und Sie können Ihren Blick wie gewohnt in der Stadt umherschweifen lassen. Um das Monument an dem gewählten Standort zu platzieren (falls er dafür geeignet ist), genügt ein Klick mit der Maustaste. Um weiter nach einem geeigneten Standort zu suchen, drücken Sie die M-Taste erneut. Nun folgt der Grundriss des Monuments erneut dem Mauszeiger. @PAußerdem müssen einige Monumente in Felswände hineingebaut werden. Zu diesen Monumenten gehören @492Abu&Simbel und die @478königlichen&Grabstätten.  @PWeitere Informationen über Monumente erhalten Sie, wenn Sie die jeweiligen Einträge dazu durchlesen. Sie werden im Hilfemenü aufgelistet. @L@LWenn Sie mehr über die Geschichte der Monumente wissen wollen, klicken Sie auf folgende Einträge: @391Sphinx, @392Pyramiden, @394Mastabas, @493Abu&Simbel, @481Bibliothek&von&Alexandria, @482Caesareum, @475Tal&der&Könige und @396andere&Monumente."
        }
    }
    message_building_mastaba {
        id: 371,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Mastaba",
        }
        content {
            text: "Mastabas sind die ersten Grabmale, die in Ägypten gebaut wurden. Sie bestehen vollständig aus Ziegeln. Für den Bau einer Mastaba benötigen Sie die Dienste von Maurern aus der Maurergilde. Mastabas gibt es in drei verschiedenen Größen - und sie sind stets gen Osten ausgerichtet.  @L@LEine Mastaba bauen Sie, indem Sie in der Monumentliste auf den Button 'Religiöse Einrichtungen' klicken und in der Liste 'Mastaba' anwählen. Während Sie den Mauszeiger über die Gegend bewegen, sehen Sie den Grundriss des Baus. Ist er rot, kann die Mastaba an der gewählten Position nicht errichtet werden. Ist der Grundriss dagegen grün, haben Sie einen geeigneten Standort gewählt. Falls Sie Probleme beim Platzieren des Monuments haben, drücken Sie die M-Taste, um den Grundriss zu fixieren. Sobald Sie auf einen gültigen Standort klicken, werden die Ecken der Mastaba mit Pflöcken abgesteckt. Ab da übernehmen dann Arbeiter und Maurer die Arbeit.   @L@LSie können den Arbeitern Schritt für Schritt beim Bau der Mastaba zusehen. Nachdem das Land planiert ist (Sand und Erde werden entfernt, bis der feste Untergrund sichtbar wird), begibt sich ein Maurerteam an die Baustelle und wartet auf die Ziegellieferung. Sobald die Warenlager der Stadt mindestens 400 Ziegel enthalten, ziehen Arbeiter einen Schlitten mit dem Material zur Baustelle, damit die Maurer arbeiten können. Jede Ladung Ziegel reicht für eine Reihe eines Abschnitts der Mastaba aus. Die Anzahl der Reihen und die Anzahl der Abschnitte pro Reihe hängt von der Größe des Monuments ab.  @L@LInfoklicken Sie auf die Mastaba, um jederzeit einen aktuellen Fortschrittsbericht über das Projekt zu erhalten.  @PDer Verblichene braucht viele Dinge im Schilffeld, daher muss die Mastaba höchstwahrscheinlich mit @374Grabbeigaben ausgestattet werden. Der @373Aufseher&der&Monumente informiert Sie, welche Grabbeigaben erforderlich sind. Den Baustatus der Mastaba erfahren Sie vom @369Vorarbeiter&des&Baus. Klicken Sie @370hier, um mehr über den Bau von Monumenten zu erfahren. @L@LKlicken Sie @394hier, um mehr über Mastabas im alten Ägypten zu erfahren."
        }
    }
    message_building_obelisk {
        id: 372,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Obelisk",
        }
        content {
            text: "Obelisken symbolisieren die Strahlen der Sonne. An große Taten und Leistungen erinnern Reliefs an den Seiten. @PObelisken werden aus großen Granitblöcken herausgehauen. Der gesamte @95Granit für einen Obelisken muss in den @4Warenlagern der Stadt vorhanden sein, bevor Sie das Monument platzieren können. @PSchieben Sie den Mauszeiger über das Areal, um einen Standort für den Obelisken auszuwählen. Wenn der Grundriss des Monuments komplett grün angezeigt wird, können Sie den Obelisken platzieren. Falls jedoch auch nur ein Teil dieses Grundrisses als rote Raute erscheint, befindet sich auf dem gewählten Terrain etwas, das den Bau des Obelisken an dieser Stelle verhindert.  @PNach Auswahl eines Standorts für den Obelisken wird der Granit an Ort und Stelle gebracht. Dann errichten Zimmerleute von der @363Zimmermannsgilde ein Gerüst um das Monument herum, und @363Steinmetze eilen zur Baustelle, um aufwendige Reliefs in den Stein einzumeißeln. Für den Bau eines Obelisken benötigen Sie keine Bauern als Arbeiter. @PInfoklicken Sie auf das Monument, um den @369Vorarbeiter&des&Baus zu besuchen. Er gibt Ihnen aktuelle Informationen zum Status des Monuments. @L@LObelisken recken sich seit Tausenden von Jahren gen Himmel. Klicken Sie @397hier, um mehr über dieses alte Monument zu erfahren."
        }
    }
    message_overseer_monuments {
        id: 373,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Aufseher der Monumente",
        }
        content {
            text: "Der Aufseher der Monumente kann Ihnen mitteilen, was den Baubeginn eines Monuments verhindert. Außerdem verwaltet er die Versorgung von Gräbern mit @374Grabbeigaben. Infoklicken Sie auf das Projekt, um den Vorarbeiter des Baus zu besuchen und einen Fortschrittsbericht abzurufen."
        }
    }
    message_burial_provisions {
        id: 374,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Grabbeigaben",
        }
        content {
            text: "Um zu gewährleisten, dass der Verblichene alles hat, was er (oder sie) im Leben nach dem Tod benötigen könnte, müssen die meisten Grabmäler mit Grabbeigaben ausgestattet werden. Grabbeigaben sind Dinge, die der Verstorbene in seinem Leben benutzt hat. Möglicherweise müssen Sie auch Materialien für den Bau bestimmter Dinge herbeischaffen, die im Leben nach dem Tod benötigt werden, wie z.B. Begräbnisbarke und Sarkophag. Monumente sind erst fertig, wenn Sie sie mit den erforderlichen Grabbeigaben ausgestattet haben. Der @373Aufseher&der&Monumente besitzt eine Liste der erforderlichen Objekte und Mengen. Wenn Sie bereit sind, die Güter abzuschicken, müssen Sie dem Aufseher der Monumente nur noch den Befehl geben, die Grabbeigaben zum Grab zu befördern. @PHierzu muss nicht die gesamte Menge der benötigten Materialien in den @4Warenlagern vorhanden sein. Sie können auch kleinere Mengen losschicken, bis das Soll erfüllt ist. @PHin und wieder muss die Stadt benötigte Grabbeigaben möglicherweise auch @47importieren. @L@LIm alten Ägypten wurden dem Verblichenen viele verschiedene Gegenstände mit ins Grab gelegt. Klicken Sie @395hier, um zu erfahren, was die alten Ägypter im Leben nach dem Tode so alles brauchten."
        }
    }
    message_building_stepped_pyramid {
        id: 375,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Stufenpyramide",
        }
        content {
            text: "Stufenpyramiden, die ersten in Ägypten errichteten Pyramiden, sind riesige Treppen hin zur Sonne. Sie bestehen vollständig aus @95einfachem&Stein, allerdings benötigt man hölzerne Rampen, um den Stein auf die höheren Ebenen der Pyramiden zu transportieren. Um Rampen zu bauen und den Stein zu bearbeiten, benötigen Sie die Dienste einer @363Zimmermannsgilde und einer @363Steinmetzgilde. Außerdem benötigen Sie Bauern als Arbeitskräfte, um die riesigen Steinschlitten zur Baustelle zu ziehen. Sobald in den @4Warenlagern vier Blöcke einfacher Stein gelagert und die Steinmetze bereit sind, machen sich die Schlittenzieher auf ihren beschwerlichen Weg zur Baustelle. @PStufenpyramiden gibt es in fünf Größen: Es gibt kleine, mittlere und große Pyramiden, Pyramidenkomplexe und große Pyramidenkomplexe. Besuchen Sie den @373Aufseher&der&Monumente und den @369Vorarbeiter&des&Baus, wenn Sie an weiteren Informationen interessiert sind. Auch der Eintrag zum Thema @370Bau&von&Monumenten kann hilfreich sein. @L@LKlicken Sie @392hier, um mehr über die Erfindung des Wesirs Imhotep zu erfahren: die Stufenpyramide."
        }
    }
    message_osiris_sebek_min {
        id: 376,
        pos [0, 88]
        size [30, 20]
        image {
            id: 42,
            pos [15, 15]
        }
        title {
            text: "Osiris, Sobek und Min",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Rolle von Osiris in der ägyptischen Religion hat sich im Lauf der Jahrtausende verändert. Zusammen mit seiner Frau und Schwester Isis und seinem Bruder Seth war er einer der ersten Götter und Mitglied der Enneade (näheres über die Enneade - Neunheit - finden Sie unter @399Religion). @L@LDer Mythos, der Osiris definiert, verbindet ihn mit Landwirtschaft, dem Nil und Begräbnisriten. Re-Atum verlieh Osiris die Herrschaft über das alte Ägypten. Osiris heiratete seine Schwester Isis und lehrte das Volk als Herrscher viele Dinge, vor allem die Kunst der Landwirtschaft. Nachdem die Ägypter viel von ihm gelernt hatten, verließ er Ägypten, um den Rest der Welt zu zivilisieren. Während seiner Abwesenheit herrschte Isis an seiner statt. Nach Osiris' Rückkehr begann jedoch sein Bruder Seth, eine Verschwörung gegen ihn anzuzetteln. Seth lud Osiris zu einem prunkvollen Festmahl ein, bei dem er einen herrlichen Sarg zur Schau stellte. Diesen Sarg bot er demjenigen an, der am besten hineinpasste. Als Osiris sich hineingelegt hatte, schloss Seth den Deckel und warf den Sarg in den Nil. Isis gelang es, den Sarg aus dem Nil zu holen, aber Seth ertappte sie dabei und hackte Osiris in Stücke. Die verzweifelte Isis weinte, und im allgemeinen Volksglauben wurden ihre Tränen zum Ursprung der Überschwemmung. Schließlich sammelte Isis die verstreuten Teile von Osiris' Körper auf, alle außer seinen Genitalien, die ein Oxyrinchusfisch verschlungen hatte. Isis bandagierte den Leichnam mit Leinen auf ähnliche Weise, wie man es mit Mumien tat. Verständlicherweise war es Ägyptern verboten, den Oxyrinchusfisch zu essen. Mit der Zeit wurde Osiris zum Gott der Unterwelt und oberster Richter, der darüber befand, wer ins Jenseits eingehen durfte und wer nicht. @L@LSobek, der Krokodilgott, war ein Gott der Fruchtbarkeit, der vor allem in Fayum verehrt wurde, obwohl er in ganz Ägypten bekannt war. Übersetzt bedeutet sein Name 'der, der über dich wacht'. Min, der Gott der Regeneration, wurde ebenfalls mit männlicher Fruchtbarkeit in Verbindung gebracht und in ganz Ägypten verehrt."
        }
    }
    message_ra_maat_horus {
        id: 377,
        pos [0, 88]
        size [30, 20]
        image {
            id: 18,
            pos [15, 15]
        }
        title {
            text: "Ra, Ma'at und Horus",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Re wurde während des größten Teils der ägyptischen Geschichtsschreibung als Hauptgott betrachtet. Als Vorfahr aller Götter in der Enneade war er der wichtigste Schöpfergott und wurde mit der Sonne assoziiert. @L@LMa'at war die Göttin der Gerechtigkeit, die man auch mit Wahrheit und Ordnung verband. Die Straußenfeder, die sie als Kopfschmuck trägt, wird zum Wiegen des Herzens verwendet, die letzte Prüfung des Menschen vor dem Leben nach dem Tod. @L@LHorus war besonders eng mit den Pharaonen verbunden. Er war der Sohn von Osiris und Isis und rächte den Tod seines Vaters, indem er Seth als Mörder von Osiris entlarvte. Horus wurde durch einen Falken dargestellt."
        }
    }
    message_ptah_amon_thoth {
        id: 378,
        pos [0, 88]
        size [30, 20]
        image {
            id: 3,
            pos [15, 15]
        }
        title {
            text: "Ptah, Amun und Thot",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ptah war der Gott der Handwerker und wird mit den Pharaonen von Memphis verbunden, die Ägypten ursprünglich vereinigten (Näheres über den Einfluss der Memphis-Pharaonen auf den Glauben der Ägypter finden Sie unter @399Religion). Insbesondere die Handwerker in Deir el-Medina, die die Gräber im Tal der Könige und im Tal der Königinnen bauten, verehrten Ptah. @L@LAmun war ein Gott der Sonne, der besonders eng mit der Morgensonne verbunden war. Besondere Bedeutung wurde ihm während der zwölften Dynastie zuteil, als die Könige von Theben die Herrschaft über Ägypten erlangten. @L@LThot war der Gott der Weisheit und des Lernens und wurde als Schreiber der anderen Götter betrachtet. Ihn verband man besonders mit Hermopolis."
        }
    }
    message_seth_anubis_sekhmet {
        id: 379,
        pos [0, 88]
        size [30, 20]
        image {
            id: 117,
            pos [15, 15]
        }
        title {
            text: "Seth, Anubis und Sachmet",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Seth, der Bruder des @376Osiris, war der Gott der Zerstörung. Ursprünglich war er der Schutzherr von Niederägypten. Mit der zunehmenden Bedeutung von Oberägypten wurde dessen Schutzgott @377Horus wichtiger und Seth bekam ein negatives Image. @L@LAnubis, Gott des Todes, war der Gott des Einbalsamierens. Der Schakal was das Wahrzeichen von Anubis, der die Toten schützte. @L@LSachmet war eine löwenköpfige Kriegsgöttin. Sie war die Ehefrau des Ptah und zerstörte, was er geschaffen hatte. Ihr huldigte man in der Hoffnung, sie zu besänftigen, damit man ihre Wut nicht zu spüren bekam."
        }
    }
    message_bast_isis_hathor {
        id: 380,
        pos [0, 88]
        size [30, 20]
        image {
            id: 28,
            pos [15, 15]
        }
        title {
            text: "Bastet, Isis und Hathor",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Bastet, eine katzenköpfige Frau oder Löwin, war die Göttin des Heims sowie der Katzen, des Feuers und der Schwangeren. Sie schützte das Heim auf sanfte wie auf aggressive Art. Außerdem war sie die Schutzgöttin von Bubastis. @L@LIsis, Frau des @376Osiris und Mutter des @377Horus, setzte die Körperteile des Osiris wieder zusammen und bandagierte die Leiche. Daher wurde sie als Göttin der Heilkunst betrachtet. Sie wurde durch eine Frau dargestellt und wird oft mit ihrem Sohn zusammen abgebildet. @L@LHathor war die Göttin der Freude, der Liebe und der Feste. Sie wurde durch eine Kuh dargestellt und war die Schutzgöttin von Dendera, Memphis, Kusae und Pathyris (Gebelen)."
        }
    }
    message_history_malaria {
        id: 381,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Malaria war eine der Gefahren, denen man ausgesetzt war, wenn man in der Nähe von Sümpfen lebte. Malaria wird im Menschen durch einen von vier Parasiten ausgelöst, die durch die nachtaktive Anophelesmücke übertragen wird. Das erste Symptom der Malaria ist Fieber, gefolgt von Muskelschmerzen, Schweißausbrüchen und Müdigkeit. Einer dieser Parasiten löst schwere Fälle von Malaria aus, die zum Tod führen können. @L@LUm juckende und möglicherweise tödliche Mückenstiche zu verhindern, verwendeten die alten Ägypter Moskitonetze, die sie über ihre Betten hängten. Der griechische Historiker Herodot schrieb außerdem, dass die Ägypter, in dem Glauben, Mücken könnten nicht in einer großen Höhe fliegen, ihre Betten auf Türme stellten."
        }
    }
    message_history_jewelry {
        id: 382,
        pos [0, 88]
        size [30, 20]
        image {
            id: 33,
            pos [15, 15]
        }
        title {
            text: "Schmuck",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Juweliere stellten aus Edelsteinen und Halbedelsteinen Halsketten, Perlenkragen, Gürtel und andere Schmuckstücke her. Um die Perlen aufzufädeln, bohrten sie zunächst mit einem Handbohrer, der eine Flintspitze besaß, ein Loch in den Stein. Danach wurde ein Faden hindurchgezogen und befestigt. Juweliere waren auch sehr versiert in der Verwendung von Edelsteinen bei Einlegearbeiten. @L@LAuf Wandgemälden in Grabkammern ist zu sehen, dass häufig Zwerge für die Schmuckherstellung eingesetzt wurden."
        }
    }
    message_history_hunting {
        id: 383,
        pos [0, 88]
        size [30, 20]
        image {
            id: 119,
            pos [15, 15]
        }
        title {
            text: "Jagd",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Im Vergleich zu den Nahrungsmitteln, die in der Landwirtschaft produziert wurden, trug die Jagd nur wenig zur Versorgung der Ägypter mit Nahrung bei. Dennoch ging man in den oberen Gesellschaftsschichten gerne zur Jagd, und viele Pharaonen brüsteten sich mit ihren Jagderfolgen. Gazellen, Antilopen, Steinböcke, Ochsen, Schafe und Strauße wurden am meisten gejagt. Als Sport betrieb man aber auch die Jagd nach Hyänen, Löwen und Leoparden (Löwen und Leoparden wurden natürlich auch wegen ihrer Felle gejagt). Jäger verwendeten Pfeil und Bogen, Lanzen oder Speere, um ihre Beute zu erlegen. @L@LDie Ägypter jagten ebenso gerne Wassertiere, darunter Vögel und Nilpferde. Nilpferde wurden von Männergruppen gejagt. Dazu verwendeten die Männer einen speziellen Speer, der an einem Seil befestigt war. Mehrere Gruppenmitglieder versuchten, das Nilpferd mit diesen Speeren zu treffen. War das Tier geschwächt genug, zog man das Nilpferd mit Hilfe der Seile ans Ufer. @L@LWasservögel tötete man mit Wurfhölzern, die dem australischen Bumerang ähnelten. Die Helfer des Jägers - Familienmitglieder oder Diener - sammelten die Beute ein. Vögel wurden auch in Netzen gefangen, die man auf den Feldern auslegte. Erst wurde das Netz mit Vogelfutter bestreut. Wenn sich die Vögel dann zum Fressen darauf niederließen, zog man die Ecken des Netzes zusammen und die Vögel waren darin gefangen."
        }
    }
    message_history_priests {
        id: 384,
        pos [0, 88]
        size [30, 20]
        image {
            id: 120,
            pos [15, 15]
        }
        title {
            text: "Priester",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ein bedeutender Teil der Bevölkerung im alten Ägypten bestand aus Priestern. Ihre Rolle ging weit über religiöse Aufgaben hinaus. Da das alte Ägypten eine Theokratie war, übernahmen Priester häufig Verwaltungsaufgaben in ihren Gemeinden und sprachen sogar gelegentlich Recht. @L@LDas auffälligste Merkmal eines Priesters war seine Sauberkeit. Die Priester durchliefen Reinigungsriten, bevor sie den Tempel betreten konnten, und rasierten ihr Haar ab, um sicher sein zu können, dass sie keine Läuse oder sonstige Unreinheiten aufwiesen. Je nachdem, welchem Gott ein Priester diente, durfte er bestimmte Nahrungsmittel nicht verzehren. Priester trugen besondere Kleidung und mussten außerdem weiße Sandalen tragen. Die am höchsten in der Hierarchie stehenden Priester schmückten sich manchmal mit Leopardenfellen. @L@LDie wichtigste religiöse Aufgabe der Priesterschaft war die Versorgung ihres Gottes, und zwar nicht nur mit Gebeten, sondern auch mit Nahrungsmitteln. In jedem Tempel befand sich eine Statue des jeweiligen Schutzgottes. Jeder Priester des Tempels war auf seinem Gebiet dafür verantwortlich, dass der Gott zufrieden war. Einige der Priester mussten zum Beispiel dafür sorgen, dass der Gott genügend Nahrung bekam. Mit Nahrungsmitteln, die von der örtlichen Bevölkerung als Opfer dargebracht oder die auf dem Tempelanwesen erzeugt worden waren, bereiteten die Priester eine Mahlzeit für ihren Gott. Der Gott ernährte sich von der 'Essenz' der Nahrung, die Priester aßen das übrig Gebliebene. Die Priester kleideten und badeten den Gott außerdem und sorgten für seine Unterhaltung. Gelegentlich wurde der Gott auch mit hinausgenommen und in einer Parade durch das Dorf getragen oder gezogen. (Näheres dazu finden Sie unter @393Feste). @L@LDie Priesterschaft war in einzelne Klassen aufgeteilt. Den höchsten Rang hatte der Hohepriester inne, der vom Pharao ernannt wurde. Er wurde auch als 'Erster Prophet' bezeichnet. Der Hohepriester war die absolute Autorität im Tempel und diente dem Pharao häufig als Berater. Unter dem Hohepriester standen seine Stellvertreter, die 'Zweiten Propheten', die bestimmte Funktionen des Tempels oder des Anwesens leiteten, z.B. die Werkstätten oder die landwirtschaftlichen Bereiche. Unter ihnen wiederum standen die Priester, die bestimmte Aufgaben innehatten, z.B. den Gott zu baden oder ihn zu unterhalten. Die meisten Priester arbeiteten in Schichten, sie taten jeweils in einem von drei Monaten Dienst."
        }
    }
    message_history_stonemasons {
        id: 385,
        pos [0, 88]
        size [30, 20]
        image {
            id: 121,
            pos [15, 15]
        }
        title {
            text: "Steinmetzgilde",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Steinmetze leiteten den Betrieb der @193Steinbrüche und den Bau von @392Pyramiden und anderen Monumenten. Sie wussten alles über Steine und wie man sie am besten brach. Der Großteil der schweren körperlichen Arbeit wurde jedoch nicht von ihnen verrichtet. Dies blieb Bauern der niedersten Klasse und manchmal Sklaven überlassen. Steinmetze überwachten das Ganze nur. Das Fachwissen der Steinmetze wurde jedoch nicht nur bei großen, sondern auch bei kleineren Bauprojekten benötigt, so z.B. wenn das Fundament eines Hauses zu errichten war."
        }
    }
    message_history_bricklayers {
        id: 386,
        pos [0, 88]
        size [30, 20]
        image {
            id: 122,
            pos [15, 15]
        }
        title {
            text: "Maurergilde",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die Technik des Mauerns hat sich im Lauf der Jahrtausende nicht sehr verändert. Man braucht im Prinzip immer das Gleiche: @390Ziegel und Mörtel. Im alten Ägypten bestand der Mörtel aus einer Mischung aus Ton, Sand, Stroh und Spreu. Die Maurer brachten den Mörtel mit einer hölzernen Kelle auf und setzten den Ziegel darauf. Sie verwendeten Senkbleie, um zu gewährleisten, dass die Mauern gerade waren."
        }
    }
    message_history_scribes {
        id: 387,
        pos [0, 88]
        size [30, 20]
        image {
            id: 21,
            pos [15, 15]
        }
        title {
            text: "Schreiber",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Schreiber, auch Sesch oder Sech genannt, waren überall in der ägyptischen Gesellschaft und der Regierung präsent und an fast allen Regierungsaktivitäten beteiligt. Die alten Ägypter führten über fast alles Buch. Und diese Funktion konnten nur Schreiber ausfüllen. Schreiber zeichneten auf, wer der Regierung wie viel Steuern schuldete, überwachten die Exporte und Importe und zogen sogar mit Soldaten in den Krieg, um die Ereignisse zu protokollieren. Für normale Bürger erstellten Schreiber rechtliche Dokumente, wie z.B. Testamente, außerdem schrieben und verlasen sie die Briefe für ihre des Schreibens unkundigen Mitbürger. @L@LDas Handwerkszeug eines Schreibers bestand aus Papyrus, einer Palette mit zwei Tintenstücken (meist schwarz und rot), einem Töpfchen mit Wasser und Schilfpinseln. Der Schreiber tauchte den Pinsel in das Wasser und rieb ihn dann über die Tinte. Anschließend schrieb er damit auf dem Papyrus. @L@LDie wenigsten Schreiber konnten Hieroglyphen schreiben. Hieroglyphen waren Denkmälern und Tempeln vorbehalten. Für den täglichen Gebrauch wurde eine einfachere Version der Hieroglyphen, die hieratische Schrift verwendet.  @L@LDiese Schriftsprache bestand aus etwa 700 Zeichen und kombinierte Symbole, die für Laute standen, mit solchen, die für Ideen standen. In der Schriftsprache wurden die Vokale nicht mit aufgezeichnet, daher können Historiker heute nur darüber spekulieren, wie die Sprache wohl geklungen haben mag."
        }
    }
    message_history_immigration {
        id: 388,
        pos [0, 88]
        size [30, 20]
        image {
            id: 123,
            pos [15, 15]
        }
        title {
            text: "Einwanderung",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ägypten hatte eine relativ stabile Wirtschaft und meist, dank der Überschwemmung, genug zu essen. Das war in den benachbarten Ländern natürlich auch bekannt, und so wanderten viele Bewohner der Nachbarländer nach Ägypten aus. @L@LEinige der Einwanderer kamen, um Handel zu treiben. Archäologische Fundstücke aus wichtigen Hafenstädten, wie z.B. Memphis, belegen die Existenz nichtägyptischer Siedlungen. Diese ausländischen Händler werden in Gräbern aus der Zeit des Mittleren und des Neuen Reichs dargestellt. In einigen direkt angrenzenden Nachbarländern (z.B. Libyen) breitete sich die Bevölkerung über die Grenzen hinaus nach Ägypten hinein aus. Zur Zeit der zwölften Dynastie bewohnten Libyer große Teile des westlichen Delta und drangen bald bis in das östliche Delta vor. @L@LAndere kamen mit weniger ehrbaren Absichten nach Ägypten. Und solche @181Invasoren blieben häufig auch weiterhin in Ägypten, selbst wenn sie ihre Macht hier schon wieder verloren hatten. Viele dieser 'Eindringlinge' scheinen später die gleichen Rechte wie Ägypter genossen zu haben, und manche hatten sogar hohe Posten in der ägyptischen Regierung inne."
        }
    }
    message_history_carpenters {
        id: 389,
        pos [0, 88]
        size [30, 20]
        image {
            id: 124,
            pos [15, 15]
        }
        title {
            text: "Zimmerleute",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Zimmerleute stellten viele nützliche Gegenstände für die Ägypter her. Es wuchs wenig @192Holz in Ägypten, daher ging man damit sehr vorsichtig um. Es wurde zwar auch importiertes Holz verarbeitet, aber da es so teuer war, blieb es nur den reichsten Bürgern vorbehalten. @L@LZimmerleute waren mit Äxten, Sägen und Breitbeilen ausgestattet, mit denen sie Baumstämme in Bretter verwertbaren Holzes verarbeiteten. Mit der Axt entfernten sie Zweige und teilten das Holz, wenn sie Dachbalken herstellten. Mit Sägen wurden die Stämme in rohe Bretter zersägt, mit Breitbeilen glättete man die Planken. @L@LZu den Endprodukten gehörten Truhen, Betten, Türen, Türrahmen, Stühle und, was besonders wichtig war, Särge. Anstelle von Nägeln wurden Dübel verwendet, um die fertigen Produkte zusammenzuhalten. Einige der fertigen Produkte waren herrliche Kunstwerke mit wunderschönen Intarsien und dekorativen Gravuren. @L@LZimmerleute brauchte man auch für den Bau größerer Häuser. Häufig wurden die Decken der Häuser reicher Leute durch schön geschnitzte Holzsäulen gestützt. @L@LIm Prinzip änderte sich die Zimmermannskunst im Verlauf der altägyptischen Geschichte nur wenig, und man verwendete stets die gleichen Grundwerkzeuge. Die wichtigste Neuerung war die Entwicklung des Bohrers. Während der Zeit des Neuen Reichs verwendete man einen Bogenbohrer, um Löcher für die Dübel zu bohren."
        }
    }
    message_history_bricks {
        id: 390,
        pos [0, 88]
        size [30, 20]
        image {
            id: 125,
            pos [15, 15]
        }
        title {
            text: "Ziegel",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Ziegel waren ein ideales Baumaterial für das alte Ägypten. Da Ziegel Wärme nur schlecht leiten, blieb es in Häusern aus Ziegeln im Sommer relativ kühl. Ziegel wurden aus Ton und Stroh hergestellt. Hierzu feuchtete man den Ton an, vermischte ihn mit Stroh und bedeckte ihn dann mit Wasser. Mit der Zeit begann sich das Stroh zu zersetzen, wobei ein Schleim abgesondert wurde, der den Ziegel zusammenhielt. Dann ließ man den Stein in der Sonne trocknen. Wenn die Ziegel fertig waren, konnten die @386Maurer mit der Arbeit anfangen."
        }
    }
    message_history_sphinx {
        id: 391,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Die Sphinx, die man im alten Ägypten mit Amun verband, hat den Körper eines Löwen und den Kopf eines Königs. In Ägypten gab es viele Sphinx-Skulpturen, die berühmteste von allen ist jedoch die Große Sphinx von Giseh.  @L@LDiese wurde gegen 2500 v. Chr. über einem alten Steinbruch erbaut und scheint die Pyramide von Chephren zu bewachen. Man glaubt, das Gesicht der Sphinx sei das von Chephren selbst. Die Sphinx ist etwa 60 Meter lang und 20 Meter hoch. Sie ist aus weichem Sandstein gehauen. @L@LDen größten Teil ihrer Existenz verbrachte die Sphinx im Sand vergraben. Laut der Legende jagte Thutmosis IV., bevor er zum Pharao wurde, in der Gegend, in der die Sphinx verborgen lag, und schlief an genau dieser Stelle ein. Während er schlief, versprach die Sphinx Thutmosis in einem Traum, wenn er sie ausgrabe, werde er Pharao. Thutmosis tat, wie ihm geheißen, und kam im Jahr 1425 v. Chr. tatsächlich auf den Pharaonenthron. Die Geschichte schrieb er auf Bildsäulen, sogenannten Stelen, nieder und stellte sie zwischen die Pfoten der Sphinx. @L@LDanach wurde die Große Sphinx erneut von Sand bedeckt und schließlich in den 30er Jahren des 20. Jahrhunderts endgültig freigelegt. Versuche, sie zu restaurieren, führten zu gemischten Ergebnissen."
        }
    }
    message_history_pyramids {
        id: 392,
        pos [0, 88]
        size [30, 20]
        image {
            id: 39,
            pos [15, 15]
        }
        title {
            text: "Pyramiden",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Seit Jahrhunderten schon rätseln die Menschen, wie die Pyramiden wohl erbaut worden sind. Es scheint unfasslich, dass die alten Ägypter ohne Zuhilfenahme von Gabelstapler, Kran, Bagger und allen möglichen anderen Mitteln der modernen Technik solch herrliche Gebäude errichten konnten. @L@LDer Bau einer Pyramide begann stets mit einem sorgfältig entwickelten Plan. Der Wesir, der nur dem Pharao unterstand, überwachte wahrscheinlich gemeinsam mit dem königlichen Architekten (auf Altägyptisch der 'Medjeh Nesu') den gesamten Vorgang und achtete auf die Einhaltung der Pläne. Dem königlichen Architekten oblag es, das Baumaterial auszuwählen und eine Möglichkeit zu finden, das Material an die Baustelle zu transportieren. @L@LNach der sorgfältigen Auswahl der Baustelle bestimmten Astronomen die Nord-Süd-Achse der Pyramide. Dann steckten Vermesser alle Seiten der Pyramide ab. Dazu verwendeten sie eine Art Strick, der so dick war, dass er sich nicht dehnen und so die Abmessungen der Pyramide verfälschen konnte. Anschließend wurde der Boden geebnet, möglicherweise, indem man Gräben mit Wasser füllte, um eine absolut glatte Fläche zu schaffen. @L@LSobald dies geschehen war, konnte man mit dem Bau beginnen. Zunächst einmal wurde eine Zeremonie abgehalten, in welcher der Pharao die Eckpunkte der Pyramide absteckte, diese mit Seilen verband und einen zeremoniellen Schlammziegel als ersten Stein des Gebäudes legte. @L@LDann kamen die @385Steinmetze und @155Arbeiter an die Reihe. Steinmetze arbeiteten unterirdische Räume heraus, darunter auch die Grabkammer. Sobald diese Räume bereit waren, begann die mühevolle Arbeit des Herbeischaffens von Steinblöcken, von denen manche bis zu 2,5 Tonnen wogen. Die Steine wurden auf Schlitten gezogen. Um die höheren Bereiche der Pyramide zu erreichen, wurden vermutlich Rampen verwendet. Im Innenbereich der Pyramide wurden grob behauene Steine verwendet, während feiner bearbeitete Steine den Außenbereich bedeckten. @L@LEinige Pyramiden standen für sich alleine, meist waren sie jedoch Teil größerer Pyramidenkomplexe. Ein Pyramidenkomplex umfasste zunächst einmal einen Taltempel, der am Wasser oder am Rand des fruchtbaren Gebiets stand. Von diesem Tempel aus führte dann ein langer Fußweg zu dem Totentempel, der als Einbalsamierungshaus diente. Dieser befand sich auf der Ostseite der Pyramide. @L@LDie Form der Pyramiden änderte sich mit der Verbesserung der verfügbaren Werkzeuge für den Bau. Die erste Pyramide, die Stufenpyramide von Djoser, hat keine glatten Seiten. Diese Stufenpyramide, die etwa um das Jahr 2620 v. Chr. erbaut wurde, besteht aus einer Reihe von Quadraten, die übereinandergestapelt wurden. Die erste echte Pyramide ist die von König Snofru II., die um 2550 v. Chr. errichtet wurde. Eine äußere Verschalung glättete die 'Stufen' der Pyramide. Dieses Verfahren übernahm man bald auch für andere Pyramiden. Die größte Pyramide ist die des Cheops. Sie ist 230 x 230 Meter groß und 146 Meter hoch. Eine ganz außergewöhnliche Pyramide ist die Knickpyramide des Pharao Snofru. Der Winkel der Pyramidenseiten ändert sich in etwa zwei Dritteln der Höhe. Man vermutet, dass Architekten feststellten, dass die Pyramide zu schwer sein und zusammenbrechen würde, wenn man sie im Originalwinkel weiterbauen würde. Und da schon Snofrus erste Pyramide zusammengebrochen war, wollte er beim zweiten Mal wohl lieber auf Nummer Sicher gehen."
        }
    }
    message_history_festivals {
        id: 393,
        pos [0, 88]
        size [30, 20]
        image {
            id: 126,
            pos [15, 15]
        }
        title {
            text: "Feste",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Feste im alten Ägypten waren freudige Feiern, bei denen Unmengen an Essen und Bier serviert wurden. Gefeiert wurde aus den verschiedensten Gründen: zu Ehren eines Gottes, als Zeichen der Ernte und als Freudenbeweis über die Langlebigkeit des Pharao. Die letzten fünf Tage des ägyptischen Jahres verbrachte man mit Feiern, und im Laufe des Jahres fanden noch viele weitere Feste statt. @L@LBei Festen zu Ehren einer Gottheit hatten alle Menschen direkten Zugang zu ihren Göttern. Im Zentrum der religiösen Festlichkeiten stand die Prozession des Gottes. Während des Festes wurde die Statue der Gottheit, die fernab vom Blick der Öffentlichkeit im Tempel aufbewahrt wurde, herrlich geschmückt und auf einer zeremoniellen Barke von Priestern durch den Ort getragen. Von Zeit zu Zeit ruhten sich die Priester aus. Während dieser Zeit wurden bestimmte Riten ausgeführt. Zur Zeit des Neuen Reichs konnten die Bürger ihrem Gott Fragen stellen, während sich die Priester ausruhten. Wenn die Antwort des Gottes positiv war, verbeugten sich die Priester, war sie negativ, traten sie zurück. Am Ende des Festes wurde der Gott wieder in den Tempel zurückgebracht. @L@LManchmal reisten die Götter recht weit und wurden per Schiff transportiert. Beispielsweise reiste der Gott Amun während des Opet-Fests von Karnak zu seiner weiter südlich gelegenen Kapelle in Luxor. Hierzu segelte er den Nil entlang. Opet war eines der größten Freudenfeste und dauerte zwischen 11 und 27 Tage. @L@LWar ein Pharao gesund genug, um 30 Jahre lang im Amt zu bleiben, wurde das Sed-Fest abgehalten. Bei diesem Fest, das zum ersten Mal im dreißigsten Herrschaftsjahr des Pharao und danach alle drei Jahre gefeiert wurde, führte der Pharao einen rituellen Lauf durch, um zu beweisen, dass er (oder sie) noch in der Lage war zu regieren. Manche Pharaonen warteten gar nicht erst 30 Jahre lang, sondern hielten deutlich früher ein solches Fest ab. @L@LZweifellos freuten sich Ägypter aller Klassen über Feste als Gelegenheit, gut zu essen und zu trinken. Feste boten auch etwas Erholung vom alltäglichen Einerlei."
        }
    }
    message_history_mastaba {
        id: 394,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Die ersten Pharaonen und Adligen im Alten Reich wurden unter Mastabas beerdigt. Mastabas bedeckten den Schacht, der in die Grabkammer hinabführte. Zunächst handelte es sich dabei um recht einfache, niedrige Gebäude mit eingraviertem Text. Im Laufe der Zeit entwickelten sie sich jedoch zu größeren Gebäuden, komplett mit Kapellen. Mastabas werden als Vorläufer der Pyramiden angesehen, und möglicherweise war die Stufenpyramide des Djoser ursprünglich als Mastaba geplant."
        }
    }
    message_history_burial_provisions {
        id: 395,
        pos [0, 88]
        size [30, 20]
        image {
            id: 26,
            pos [15, 15]
        }
        title {
            text: "Grabbeigaben",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Grabkammern waren gut gefüllt mit allem, was der Verstorbene im Leben nach dem Tod brauchen konnte. Diese Grabbeigaben umfassten die beruflichen Werkzeuge des Verstorbenen, Nahrung, Toilettenartikel, Schmuck, Musikinstrumente, Make-up - eigentlich alles, was der Verstorbene in seinem Leben jemals besessen hatte. Gräber waren darüber hinaus mit Uschebtis, sog. 'Antwortern', ausgestattet. Diese kleinen Statuen wurden in die Grabkammern gegeben, falls der Verstorbene im Leben nach dem Tode zur Arbeit gerufen wurde. Die Uschebti würden dann auf den Ruf antworten und anstelle des Toten die Arbeit verrichten."
        }
    }
    message_history_other_monuments {
        id: 396,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1,
            pos [15, 15]
        }
        title {
            text: "Andere Monumente",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Abgesehen von @397Obelisken, @394Mastabas, @392Pyramiden und @391Sphinxen gab es im alten Ägypten noch viele weitere Monumente, darunter Mausoleen und Sonnentempel.  @L@LDie Sonne wurde im alten Ägypten als Lebensspender betrachtet, und in ganz Ägypten wurden viele Sonnentempel errichtet, insbesondere während der fünften Dynastie. Die bemerkenswertesten Sonnentempel befinden sich in Abu Gurob, etwa einen Kilometer nordöstlich der Pyramide des Sahure. Hier befanden sich zwei Sonnentempel, in denen Tieropfer stattfanden. @L@LMausoleen und Kapellen wurden häufig über Grabkammern errichtet, damit die Familie des Verstorbenen Opfer darbringen konnte. Durch diese Opfer wurde dafür gesorgt, dass der Verstorbene das Leben nach dem Tod weiterhin genießen konnte. Wer das nötige Geld hatte, errichtete diese Kapellen für seine Familienmitglieder. In ganz Ägypten gibt es unzählige dieser persönlichen Mausoleen."
        }
    }
    message_history_obelisk {
        id: 397,
        pos [0, 88]
        size [30, 20]
        image {
            id: 17,
            pos [15, 15]
        }
        title {
            text: "Obelisken",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Obelisken verbanden die alten Ägypter mit der Sonne. Sie stellten entweder die Strahlen der Sonne oder den ursprünglichen Hügel dar, auf den die Sonne bei ihrem ersten Aufgehen schien. Obelisken aus Granit wurden mit Hieroglyphen graviert und waren meist paarweise vor Tempeln stehend zu finden. @L@LDie Form des Obelisken wurde im Steinbruch herausgehauen. In Assuan ist ein unfertiger Obelisk zu sehen, anhand dessen man sehr gut erkennen kann, wie man damals vorging, um einen so großen Stein zu bearbeiten. Arbeiter verwendeten Hämmer aus Dolerit, einer Basalt-Art, um die benötigte Form langsam herauszuarbeiten. Der Obelisk in Assuan wurde aufgegeben, weil in der Mitte des Steins ein Riss erschien. @L@LNachdem der Obelisk aus dem Stein herausgehauen war, musste er noch aufgerichtet werden. Wie das funktionierte, weiß jedoch niemand so genau. Moderne Versuche, Obelisken mit dem Altertum nachempfundenen Methoden aufzustellen, schlugen allesamt fehl."
        }
    }
    message_history_linen_and_weaving {
        id: 398,
        pos [0, 88]
        size [30, 20]
        image {
            id: 24,
            pos [15, 15]
        }
        title {
            text: "Leinen und Weber",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Aus @189Flachs hergestelltes Leinen war die vorherrschende Stoffart im alten Ägypten. Es gab zwar auch Woll- oder Hanfstoffe, diese hielt man jedoch für wesentlich schlechter als Leinen. @L@LUm Stoff herzustellen, mussten die Flachsfasern zunächst zu einem Faden versponnen werden. Die Spinner hatten dazu Stapel von Flachs vor sich, drehten die Fasern zusammen und wickelten den entstandenen Faden auf ein Knäuel. Dann wurde der Faden auf Spindeln gerollt und die Weber konnten mit ihrer Arbeit anfangen. @L@LIm alten Ägypten verwendete man einen waagerecht auf dem Boden liegenden Webrahmen. Die Weber zogen zwei parallele Fadenreihen (die Kette) auf den Rahmen auf. Zwei Arbeiter saßen zu beiden Seiten des Webrahmens und schoben das Schiffchen mit dem Faden (Schuss) hin und her, um Stoff herzustellen. @L@LZur Zeit des Neuen Reichs wurde der waagerechte Webrahmen durch einen aufrechten Webstuhl ersetzt. So konnten die Weber bequemer auf Hockern sitzen. @L@LDie Mehrzahl der Weber waren Frauen. Häufig waren sie Teil des Harems des Pharao."
        }
    }
    message_history_religion {
        id: 399,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Die ägyptische Religion umfasste einen ganzen Pantheon voller Neben- und Hauptgottheiten. Die meisten Städte und sogar Einzelpersonen betrachteten einen bestimmten Gott als ihren persönlichen Schutzgott. Dies beeinflusste die Bedeutung der einzelnen Götter nicht wenig. @L@LEine der frühesten Glaubensstrukturen war die Enneade (Neunheit), eine Gruppe von neun Göttern. In der Stadt Heliopolis gegründet, war die wichtigste Gottheit der Enneade Atum, der sich mit Re zu Re-Atum verband. Re-Atum war zwar männlich, dennoch gelang es ihm, selbst Zwillinge zu gebären: Schu und Tefnet. Schu war der Gott der Luft, Tefnet die Göttin der weltlichen Ordnung. Schu und Tefnet hatten vier Kinder: Isis, Osiris, Nephtys und Seth. Der neunte Gott ist Horus, Sohn von Isis und Osiris. Re wurde im Laufe der Zeit als separat von Atum betrachtet und wurde zur Hauptgottheit der Enneade. Dieses System von Gottheiten dominierte in Ägypten vor der Zeit der Dynastien. Re blieb danach aber auch weiterhin ein wichtiger Gott für die alten Ägypter.  @L@LAls Aha, auch als Menes bekannt, Ober- und Niederägypten vereinigte, veränderte sein persönlicher Glaube an Ptah, einen Schöpfergott, das Glaubenssystem. Menes war der Auffassung, dass die Götter der Neunheit alles Manifestationen des Gottes Ptah seien. Dennoch blieb Re die vorherrschende Gottheit. @L@LEine andere Theorie kam aus der oberägyptischen Stadt Hermopolis. Dort glaubte man an eine Chemenu, eine Achtheit von Göttern. Darin stellten männliche und weibliche Gottheiten jeweils paarweise verschiedene Aspekte der Welt dar. Nun und Naunet standen für Wasser, Heh und Hehet für Unendlichkeit, Keku und Kekuit waren die Götter der Dunkelheit und Amun und Amaunet die der Luft. @L@LIm Neuen Reich ersetzte Amun schließlich Re als Hauptgottheit. Die dominante Rolle Amuns setzte sich bis zur Herrschaft von Echnaton fort. Dieser versuchte, in Ägypten den Monotheismus einzuführen. Er war der Auffassung, dass Aton, verkörpert durch die Sonnenscheibe, der einzige Gott sei. Während seiner Herrschaft, der sogenannten Amarna-Zeit, schloss er Tempel, in denen zu anderen Göttern gebetet wurde. Nach seinem Tod war jedoch der Polytheismus schnell wieder eingeführt und die Tempel anderer Götter wurden wieder geöffnet."
        }
    }
    message_mission_naqada {
        id: 400,
        type: 3,
        size [40, 30]
        title {
            text: "Naqada",
            pos [50, 80]
        }
        subtitle {
            text: "Ein Dorf entsteht",
            pos [10, 30]
        }
        content {
            text: "@PWillkommen im alten Ägypten, dem Land der Pharaonen! Sie greifen in diesem Spiel in den Lauf der Geschichte ein, in die Entwicklung einer der größten Zivilisationen, die die Welt je gesehen hat, und erleben ein Epos, das sich über mehr als 15 Jahrhunderte und 50 Generationen erstreckt. Sie lenken die Geschicke einer Familie von Generation zu Generation, von den ersten Anfängen im ägyptischen Altertum an, über die aufkeimende Zivilisation ... bis zur Errichtung eines einzigartigen, mächtigen Reiches ... und darüber hinaus.  @PUnsere Geschichte beginnt an den Ufern des Nils, in einem Gebiet, das als Naqada bekannt ist. Den rauhen Lebensbedingungen trotzend kämpft hier eine Gemeinschaft von Klans ums Überleben. Mit Ihnen als Oberhaupt steht Ihre Familie an der Spitze dieser kleinen Siedlung."
        }
    }
    message_mission_thinis_2 {
        id: 401,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Anfänge der Zivilisation",
            pos [10, 30]
        }
        content {
            text: "@PNach vielen Jahren - und eine Generation später - hat sich Ihre Familie im Gebiet von Thinis in Oberägypten neu niedergelassen. Hier versucht eine kleine Gruppe lokaler Regenten ihren Einfluss über Unterägypten und das Land längs des Nils auszuweiten, um das gesamte Gebiet unter ihrer Herrschaft und mit einem obersten Führer zu vereinen.  @PWenn Thinis zu einer blühenden Stadt wird, wie sie noch nie gesehen wurde, wird niemand mehr den Wert der thinitischen Föderation bestreiten und die Oberherrschaft dieser Regenten über Unterägypten und die anderen Teile, die um die Macht wetteifern, ernsthaft in Frage stellen. Das bedeutet, dass der Bevölkerung Unterhaltung geboten werden muss und prächtige Tempel zu Ehren der Schutzgötter der Region errichtet werden müssen. @PUm eine Stadt dieser Größe aufzubauen, benötigen Sie beträchtliche Geldmengen. In Thinis finden Sie reiche Goldadern. Diese auszubeuten, muss Ihr oberstes Ziel sein. "
        }
    }
    message_mission_buto_2 {
        id: 402,
        type: 3,
        size [40, 30]
        title {
            text: "Buto",
            pos [50, 80]
        }
        subtitle {
            text: "Der Nil und seine Gefahren",
            pos [10, 30]
        }
        content {
            text: "Der thinitische Adel kämpft noch immer darum, die Länder am Nil unter einem Herrscher zu vereinen. Man hegt die Hoffnung, dass Sie ihn bei diesem Bestreben unterstützen werden und sich darum bemühen, bei Buto im feuchten Deltagebiet Unterägyptens ein blühendes Gemeinwesen aufzubauen, wodurch der Einfluss des Adels entlang des gesamten heiligen Flusses gestärkt würde. Um mehr als nur ein kleines Dorf zu ernähren, müssen Sie lernen, wie man Landwirtschaft betreibt. @PÄgyptische Bauern haben begonnen, den fruchtbaren Schlamm, der jedes Jahr nach der Überschwemmung des Nils zurückbleibt, zum Anbau von Pflanzen zu nutzen. Doch zahlreich sind auch die Gefahren, die am Nil lauern. An seinem Ufer und im Wasser wimmelt es von todbringenden Krokodilen, von Nilpferden und von Stechmücken, die Malaria übertragen."
        }
    }
    message_mission_hierakonpolis {
        id: 403,
        type: 3,
        size [40, 30]
        title {
            text: "Hierakonpolis",
            pos [50, 80]
        }
        subtitle {
            text: "Der erste Pharao",
            pos [10, 30]
        }
        content {
            text: "Während die Bevölkerung entlang des Nils den äußerst rauen Bedingungen trotzt und um das nackte Überleben kämpft, ist ein lokaler König namens Narmer an die Macht gekommen. Obgleich er über einen großen Teil des Landes herrscht, ist eine vollständige Vereinigung der beiden Königreiche noch lange nicht in Sicht. Narmer wünscht, dass zum Gedenken an seine Thronbesteigung Ihre Familie sich in Hierakonpolis niederlässt und hier eine neue Stadt errichtet und regiert. Die Stadt wird Tempel zu Ehren vieler ägyptischer Gottheiten und eine große Anzahl an Unterhaltungsstätten besitzen."
        }
    }
    message_mission_memphis {
        id: 404,
        type: 3,
        size [40, 30]
        title {
            text: "Memphis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Gründung einer Hauptstadt",
            pos [10, 30]
        }
        content {
            text: "Nach langem Kampf hat König Aha sein Ziel erreicht und die beiden Königreiche Unter- und Oberägypten vereinigt. Nun hat er sich zum Pharao über ganz Ägypten ernannt! Als Zeichen seiner absoluten Souveränität und zur Festigung der ersten ägyptischen Dynastie hat Aha die Gründung einer imposanten Hauptstadt bei Memphis angeordnet. Von hier aus will er seine aufstrebende Nation regieren. Da Ihre Familie dem Land bereits seit vielen Generationen treue Dienste leistet, hat der Pharao Sie als Architekten dieser herrlichen Stadt auserkoren. Und da die Hauptstadt das Symbol des Königreichs selbst ist, sollen die Bürger hier einen nie gekannten Lebensstandard genießen. Um dieses Ziel zu erreichen, müssen Sie im Laufe der Zeit Handelsbeziehungen mit anderen Städten des Reichs aufnehmen und zumindest einem Teil der Bevölkerung bessere Bildungsmöglichkeiten eröffnen. Darüber hinaus müssen Sie eine geweihte Mastaba für die Adligen der Stadt errichten."
        }
    }
    message_mission_timna {
        id: 405,
        type: 3,
        size [40, 30]
        title {
            text: "Timna",
            pos [50, 80]
        }
        subtitle {
            text: "Eine Expedition nach Sinai",
            pos [10, 30]
        }
        content {
            text: "Mit Den hat ein neuer Pharao den ägyptischen Thron bestiegen. Der Pharao ist äußerst besorgt: Feinde bedrohen zunehmend unsere Grenzen, und unserem Staat mangelt es an wertvollem Kupfer, das wir zur Herstellung der Waffen für unsere Truppen benötigen. Pharao Den hat eine Bergbau-Expedition in die erbarmungslose Wüste Sinai angeordnet, ein Land jenseits unserer Grenzen und tief im Gebiet der Beduinen. In der Gegend, die unter dem Namen Timna bekannt ist, gibt es große Gold- und Kupfererzvorkommen sowie wertvolle Türkise. Ansonsten jedoch liegt das Land völlig brach. Unter durch und durch lebensfeindlichen Bedingungen werden Sie für diesen Vorposten der Zivilisation viele Dinge, möglicherweise sogar zusätzliche Nahrungsmittel, aus Ägypten importieren müssen. Der Pharao wird häufig Lieferungen aus dem Sinai verlangen. Sie werden ihm Geld, Kupfer, Edelsteine und Waffen liefern müssen. Etwaige Überschüsse dieser Waren können Sie dazu verwenden, die Expedition zu unterstützen. Seien Sie stets auf der Hut, denn die Beduinen der Wüste Sinai sind gefährliche Gegner und werden nicht tatenlos zusehen, wenn Fremde ihr Land besetzen und nicht einmal vor ihren Bodenschätzen Halt machen. @PUm die Last zu lindern, die solche Lebensbedingungen der Bevölkerung der Stadt auferlegen, sollten Sie einen Pavillon an einer belebten Kreuzung errichten. Die Bürger können sich dann bei Musik und Jongleursdarbietungen entspannen. Wenn Sie zusätzlich auch noch eine Tanzschule einrichten, wird diese neue Art der Zerstreuung für hervorragende Unterhaltung sorgen. "
        }
    }
    message_mission_apollinopolis {
        id: 406,
        type: 3,
        size [40, 30]
        title {
            text: "Apollinopolis",
            pos [50, 80]
        }
        subtitle {
            text: "Seestreitkräfte des Pharao",
            pos [10, 30]
        }
        content {
            text: "Das ägyptische Heer sucht in der bekannten Welt seinesgleichen, doch der neue Pharao, Chasechemui aus der zweiten Dynastie, fordert nun auch den Aufbau einer mächtigen Seestreitmacht mit Basis in Apollinopolis. Um die Herrschaft über die Meere zu erringen, benötigen wir eine komplette Flotte an Kriegsschiffen. Es mangelt uns jedoch an Holz, da in unserem Klima Wald nur spärlich wächst. Doch wir können - wenn auch zu einem hohen Preis - Zedernholz von Byblos aus dem Libanon, einem Land im Nordosten, importieren. Zum Glück können wir diese Kosten durch Papyrusexporte wieder etwas ausgleichen."
        }
    }
    message_mission_abydos {
        id: 407,
        type: 3,
        size [40, 30]
        title {
            text: "Abydos",
            pos [50, 80]
        }
        subtitle {
            text: "Das Meer und die Macht",
            pos [10, 30]
        }
        content {
            text: "Abydos, der Friedhof unserer Vorfahren, hat sich im Laufe der Jahre zu einer großen Nekropole heiliger Grabstätten entwickelt. Nun möchten die meisten Adligen hier ihre letzte Ruhe finden. Zu ihren Ehren hat der neue Pharao, Chasechemui aus der zweiten Dynastie, den Bau dreier heiliger Mastabas für die hiesigen Edelleute angeordnet. Eine Mastaba soll größer sein als die beiden anderen.  @L@LDarüber hinaus hat der Pharao den Aufbau einer mächtigen Seestreitmacht mit Basis in Apollinopolis angeordnet. Abydos muss ebenfalls eine bescheidene Flotte an Kriegsschiffen unterhalten, um die absolute Sicherheit unserer Küsten zu gewährleisten. Das wird keine leichte Aufgabe sein, denn es mangelt uns an Holz, da unser Klima nur einen geringen Waldbestand gestattet. Doch wir können - wenn auch zu einem hohen Preis - Zedernholz von Byblos aus dem Libanon, einem Land im Nordosten, importieren. Zum Glück können wir diese Kosten durch Papyrusexporte wieder etwas ausgleichen."
        }
    }
    message_mission_selima {
        id: 408,
        type: 3,
        size [40, 30]
        title {
            text: "Selime",
            pos [50, 80]
        }
        subtitle {
            text: "Die Straße nach Afrika",
            pos [10, 30]
        }
        content {
            text: "@PMit Nebkare hat ein neuer Pharao den Thron bestiegen und die dritte Dynastie der ägyptischen Herrscher begonnen. Nebkare hat Ägypten neu organisiert und strukturiert, indem er die Aufteilung des gesamten Reichs in Distrikte, in so genannte Nomes, angeordnet hat. Jeder Nomes wird von einem lokalen Herrscher, dem Nomarchen, regiert. So starr dieses System auch wirkt, es trägt doch dazu bei, dass unter Nebkares Herrschaft Ägypten wächst und gedeiht und dass große Errungenschaften in den Bereichen Kunst und Architektur erzielt werden. @L@PHändlerkarawanen aus dem tiefsten Afrika, die von Oase zu Oase ziehen, bringen jetzt viele seltene und exotische Luxuswaren nach Ägypten, die unser Volk heute nicht mehr missen möchte. Leider werden diese Karawanen regelmäßig von libyschen Kriegern und sogar von Beduinen aus der Wüste im Osten angegriffen. Um diese Handelswege zu sichern, wünscht Pharao Nebkare, dass Sie einen Militärposten in der Oase Selime errichten, dem Dreh- und Angelpunkt des Karawanenhandels weit jenseits der Grenzen unseres Reichs.  @L@PDort werden Sie Bäume finden, die sich zur Abholzung eignen. Die Einkünfte aus dem Verkauf des Holzes werden Ihnen dabei helfen, diesen Vorposten einzurichten. Für das Schmieden von Waffen dürfen Sie Kupfer aus unseren neu errichteten Minen in Timna, das im Lande Sinai liegt, importieren. @L@PVon der Oase Selime aus können Sie Ebenholz aus dem Land Kerma in Afrika importieren. Wenn es Ihnen gelingt, diesen Außenposten zu befestigen, wird er eine nie versiegende Ebenholzquelle für alle Städte in unserem Reich darstellen."
        }
    }
    message_mission_elephantine {
        id: 409,
        type: 3,
        size [40, 30]
        title {
            text: "Elephantine",
            pos [50, 80]
        }
        subtitle {
            text: "Die nubische Grenze",
            pos [10, 30]
        }
        content {
            text: "@PMit Nebkare hat ein neuer Pharao den Thron bestiegen und die dritte Dynastie der ägyptischen Herrscher begonnen. Nebkare hat Ägypten neu organisiert und strukturiert, indem er die Aufteilung des gesamten Reichs in Distrikte, in so genannte Nomes, angeordnet hat. Jeder Nomes wird von einem lokalen Herrscher, dem Nomarchen, regiert. So starr dieses System auch wirkt, es trägt doch dazu bei, dass unter Nebkares Herrschaft Ägypten wächst und gedeiht und dass große Errungenschaften in den Bereichen Kunst und Architektur erzielt werden.  @PDer Pharao wünscht, die Grenzen unseres Reiches weiter nach Süden, nach Nubien hinein, auszudehnen. Er hat die Gründung einer Stadt am ersten Katarakt des Nils verfügt, auf der Insel Elephantine, damit wir die immensen Vorräte an Edelsteinen, Granit und Sandstein abbauen können, die dort zu finden sind.  @PDiese Materialien werden für die stetig größer werdende Nekropole Abydos benötigt, damit immer noch kunstvollere Grabmäler für den Adel errichtet werden können. Die Hauptstadt bei Memphis könnte auch Ziegel für den Bau von Grabmälern benötigen. Pharao Nebkare wird möglicherweise Forderungen nach solchen und anderen Baumaterialien genehmigen.  @PPharao Nebkare hat darüber hinaus angeordnet, dass ein Ihnen Gleichrangiger einen Militärposten in der Oase Selime errichten soll, um die Karawanenstraßen ins Innere Afrikas zu sichern. Sobald dieser Vorposten steht, kann von dort aus Ebenholz, ein wertvolles und sehr geschätztes Luxusgut, importiert werden."
        }
    }
    message_mission_saqqara {
        id: 410,
        type: 3,
        size [40, 30]
        title {
            text: "Saqqara",
            pos [50, 80]
        }
        subtitle {
            text: "Die erste Pyramide",
            pos [10, 30]
        }
        content {
            text: "Die Thronbesteigung von Pharao Djoser hat eine neue Ära der Weisheit, Gelehrsamkeit und Kunst eingeleitet. Ein königlicher Friedhof soll in Saqqara eingerichtet werden und als letzte Ruhestätte für Adlige wie Hesire und Chabausokar, die Vertrauten und Höflinge des Pharao, dienen.  @PAn diesem Ort soll auch ein Monument entstehen, wie es die Welt noch nie gesehen hat. Ich, Imhotep, königlicher Wesir des Pharao, habe eine neue Form eines heiligen Grabmals für den Pharao entworfen. Im Gegensatz zu den niedrigen Ziegelmastabas einstiger Pharaonen soll dieses Grabmal in den Himmel ragen, als bestünde es aus mehreren Mastabas übereinander. Des Weiteren soll diese 'Stufenpyramide' vollständig aus Stein bestehen, damit ihr der Lauf der Zeiten nichts anhaben kann. Tief im Innern der Pyramide soll ein Sarkophag aus reinem Granit den Körper des Pharao in seiner ewigen Ruhe schützen. @PPriester der Nekropole von Abydos haben die Kunst perfektioniert, die Toten mit Hilfe von Leinen einzubalsamieren, so dass allen Ägyptern nun das Tor zum ewigen Leben offen steht.  @PUnser Handelsposten in der Oase Selime blüht und gedeiht weiterhin. Von dort aus können Sie Ebenholz aus Afrika importieren.  @PDer Pharao hat Ihnen für dieses Projekt einen großzügigen finanziellen Vorschuss gegeben. Enttäuschen Sie ihn nicht."
        }
    }
    message_mission_serabit_khadim {
        id: 411,
        type: 3,
        size [40, 30]
        title {
            text: "Serabit el-Chadim",
            pos [50, 80]
        }
        subtitle {
            text: "Die Beduinen des Ostens",
            pos [10, 30]
        }
        content {
            text: "Wie bereits Pharao Den vor ihm hat Pharao Huni eine Expedition in die raue Landschaft des Sinai angeordnet, um Türkise und Kupfer zu beschaffen. Er wünscht, dass diese Expedition unter Ihrer Führung zu einem Ort namens Serabit el-Chadim aufbricht. Hier gibt es noch Überreste eines früheren ägyptischen Außenpostens. Sein derzeitiger Zustand ist zwar unbekannt, doch man geht davon aus, dass er der Expedition noch ein gewisses Maß an Schutz bieten müsste.  @PSie sollten auch wissen, dass die Expedition, die sich zuletzt dorthin aufgemacht hat, nie zurückgekehrt ist. Nicht anders erging es einer späteren Expedition, die sich auf die Suche nach den Verschollenen begeben hatte. Dennoch, wenn wir unsere Soldaten ausreichend mit Waffen versorgen wollen, müssen wir uns das Kupfer dafür dort besorgen, denn in unserem Land gibt es nicht genug davon. @PBereiten Sie sich gut vor, denn Sie müssen immer mit Angriffen der Beduinen aus dem Sinai und der Kanaaniter, unseren Feinden, rechnen. Fördern Sie so viel Kupfer und Edelsteine, wie dies unter diesen Bedingungen möglich ist, und erfüllen Sie umgehend die Forderungen des Pharao. Sie können Juweliere einstellen, die aus den übrigen Edelsteinen Schmuck für die Bewohner der Siedlung fertigen."
        }
    }
    message_mission_meidum {
        id: 412,
        type: 3,
        size [40, 30]
        title {
            text: "Medum",
            pos [50, 80]
        }
        subtitle {
            text: "Eine königliche Nekropole",
            pos [10, 30]
        }
        content {
            text: "Pharao Huni wünscht, die Ewigkeit in einer Stufenpyramide zu verbringen, wie bereits Djoser vor ihm. Die Pyramide soll von den Gräbern seiner Gefolgsleute umgeben sein und in Medum in Unterägypten stehen.  @PAls Zeichen der Dankbarkeit für die treuen Dienste Ihres Hauses über viele Generationen hinweg erweist Huni Ihnen die Gunst, sich in einem eigenen Grabmal in Medum beerdigen zu lassen. Damit hat er Ihrer Familie eine große Ehre erwiesen. @PUm zu gewährleisten, dass die Weisheit und die Kenntnisse Ägyptens nicht im Laufe der Zeit der Vergessenheit anheim fallen, drängt Pharao Huni auf den Bau königlicher Bibliotheken. Stapeln sich darin erst einmal die Papyrusrollen, werden die oberen Klassen der Gesellschaft auch in den Genuss einer höheren Bildung kommen.  @PDer Pharao hat einen weiteren seiner treuen Höflinge auf eine Expedition nach Serabit el-Chadim ins unwirtliche Land des Sinai entsandt, um Türkise zu holen. Sollte die Expedition von Erfolg gekrönt sein, können Sie sich darauf freuen, Edelsteine von dort zu importieren. Juweliere können daraus Schmuck, ein wertvolles Luxusgut für die Stadtbevölkerung, herstellen. @PDas einst blühende Apollinopolis steht vor dem Untergang und exportiert viele Waren nicht mehr, die einst den Ruf der Stadt begründeten."
        }
    }
    message_mission_buhen {
        id: 413,
        type: 3,
        size [40, 30]
        title {
            text: "Buhen",
            pos [50, 80]
        }
        subtitle {
            text: "Expansion nach Nubien",
            pos [10, 30]
        }
        content {
            text: "Unser neuer Pharao Snofru ist entschlossen, die vierte Dynastie als die größte Dynastie in die Geschichte eingehen zu lassen, die Ägypten je regiert hat. Er wünscht, dass unsere Grenzen noch weiter nach Süden ausgedehnt werden. Daher gab er den Befehl zum Angriff auf Nubien und zur Errichtung einer befestigten Stadt bei Buhen neben dem zweiten Nilkatarakt. Dort soll ein weithin sichtbarer Obelisk aus Granit errichtet werden, zum Zeichen, dass diese Gegend auf ewig Ägypten und dem Pharao gehört. So weit im Süden gibt es jedoch keinen Granit, daher müssen Sie ihn aus Elephantine importieren.  @PBei Buhen werden Sie auf wilde und erfahrene nubische Krieger stoßen, die bis zum Tod kämpfen werden, um zu verhindern, dass wir so weit im Süden Fuß fassen. Lassen Sie sich davon jedoch nicht entmutigen, denn nach der strengen Ausbildung an der Militärakademie brauchen Ihre Kämpfer niemanden zu fürchten. Außerdem haben unsere Festungsbaumeister alles dafür getan, unsere Verteidigungseinrichtungen wie z.B. befestigte Türme, Mauern und Stadttore unüberwindlich zu machen. Dies werden Sie spätestens dann zu schätzen wissen, wenn die ersten Wellen des nubischen Angriffs heranrollen. Transportschiffe können eingesetzt werden, um Ihre Armee, falls erforderlich, auf dem Seewege zu verlegen.  @PIm Norden haben wir Beziehungen mit Enkomi auf der Insel Zypern aufgenommen. Dieses Land ist für seine unerschöpflichen Vorkommen an Kupfererz bekannt, das wir nun von dort erwerben können. Dank der kürzlich etablierten ägyptischen Bergbaustadt bei Serabit el-Chadim im Lande Sinai können wir unseren Gouverneuren jedoch Kupfer zu einem weitaus günstigeren Preis anbieten. Diese Lieferungen sind allerdings aufgrund der nicht nachlassenden Angriffe von Beduinen und Kanaanitern auf Serabit el-Chadim starken Schwankungen unterworfen, und wir wissen nicht, wie lange die dort stationierten ägyptischen Streitkräfte noch ausharren können.  @PDas Grabmal des Pharao, ein einzigartiges und spektakuläres Monument, wird derzeit in Dahschur errichtet. Von Zeit zu Zeit wird der Pharao möglicherweise eine Lieferung Kalkstein für dieses Projekt anfordern."
        }
    }
    message_mission_south_dahshur {
        id: 414,
        type: 3,
        size [40, 30]
        title {
            text: "Süd-Dahschur",
            pos [50, 80]
        }
        subtitle {
            text: "Die Knickpyramide des Snofru",
            pos [10, 30]
        }
        content {
            text: "@Unser neuer Pharao Snofru ist entschlossen, die vierte Dynastie als die größte Dynastie in die Geschichte eingehen zu lassen, die Ägypten je regiert hat. Seine Architekten haben ein Grabmal entworfen, das noch spektakulärer sein wird als die Stufenpyramide des Huni. Der Pharao möchte Ihnen die Bauaufsicht übertragen. Hierzu müssen Sie zunächst eine mittelgroße Siedlung im Süden von Dahschur aufbauen, dem Ort, an dem die Knickpyramide errichtet werden soll. Ist dies geschehen, können die Arbeitskräfte für dieses ehrgeizige Projekt aus der Siedlung rekrutiert werden. @PDie Knickpyramide soll aus einem einfachen Steinkern bestehen und mit feinem weißen Kalkstein verschalt werden, so dass sie für immer gleißend hell in der Wüstensonne leuchten wird. In Dahschur finden Sie ausreichend Kalkstein, Sie müssen aber den normalen Stein importieren. @PDer Pharao wünscht, dass unsere Grenzen noch weiter gen Süden ausgedehnt werden. Daher gab er den Befehl zum Angriff auf Nubien und zur Errichtung einer befestigten Stadt bei Buhen neben dem zweiten Nilkatarakt. @PIm Norden hat Ägypten Beziehungen mit Enkomi auf der Insel Zypern aufgenommen. Dieses Land ist für seine unerschöpflichen Vorkommen an Kupfererz bekannt, dessen Import von größter Bedeutung ist.  @PWertvolle Edelsteine können von einem kürzlich eingerichteten ägyptischen Außenposten in Serabit el-Chadim im Lande Sinai bezogen werden. Diese Lieferungen sind allerdings aufgrund der unerbittlichen Angriffe von Beduinen und Kanaanitern auf die Siedlung in letzter Zeit starken Schwankungen unterworfen, und wir wissen nicht, wie lange die dort stationierten ägyptischen Streitkräfte noch standhalten können."
        }
    }
    message_mission_north_dahshur {
        id: 415,
        type: 3,
        size [40, 30]
        title {
            text: "Nord-Dahschur",
            pos [50, 80]
        }
        subtitle {
            text: "Die wahre Pyramide",
            pos [10, 30]
        }
        content {
            text: "@PPharao Snofru hat in Ägypten Ordnung einkehren lassen. Heute blüht das Königreich unter seiner weisen, gütigen Herrschaft. Snofru wünscht, in Dahschur ein weiteres Bauprojekt in Angriff zu nehmen, das noch ehrgeiziger sein soll als die Knickpyramide, die Sie bereits fertig gestellt haben. Königliche Architekten, Landvermesser und Ingenieure sind zuversichtlich, ein Gebäude errichten zu können, dessen Seiten gerade nach oben steigen und in eine perfekte Spitze münden. Sollte diesem Projekt Erfolg beschieden sein, wäre dies die erste echte Pyramide und für Pharao Snofru eine würdige Heimat in der Ewigkeit!  @PDie Frau des Pharao, Königin Hetepheres, hat vor kurzem einen Sohn geboren, der den Namen Cheops erhielt. Unserem Volk graut es vor dem Tag seines Regierungsantritts, denn die Seher des Horus, des Gottes des Pharao, haben vorhergesagt, dass er unserem Volk alles andere erweisen wird als die Güte seines Vaters. Während man sich einerseits Großes von ihm verspricht, fürchtet man andererseits, dass er Ägypten mit unnachgiebiger Hand regieren wird.  @PHolz können Sie aus Byblos beziehen. Die Zimmerleute werden große Mengen davon benötigen, um die vielen Rampen zu errichten, auf denen die Arbeiter die Spitze dieser großen Pyramide erklimmen können."
        }
    }
    message_mission_dendera {
        id: 416,
        type: 3,
        size [40, 30]
        title {
            text: "Dendera",
            pos [50, 80]
        }
        subtitle {
            text: "Die Verteidigung Ägyptens",
            pos [10, 30]
        }
        content {
            text: "@PPharao Cheops hat den Thron bestiegen, und wie dies die Seher von Horus und Re vorhergesagt haben, stöhnt unser Volk bereits jetzt unter seiner Tyrannei.  @PCheops hat die Entsendung eines königlichen Gouverneurs nach Dendera befohlen, um unser Land gegen eindringende Kuschiter zu verteidigen. Dendera kann eine kleine Fischereiwirtschaft unterhalten, was die Siedlung eine Zeit lang ernähren dürfte. Wenn die Kuschiter jedoch auf dem Seeweg einfallen, kann der Fluss für Fischerboote gefährlich werden. Möglicherweise sollten dann die Ufergebiete besser zur Unterstützung einer Flotte von Kriegsschiffen eingesetzt werden. Sollte die Nahrung knapp werden, können Sie auch Rinder mästen, um Fleisch zu bekommen. Allerdings benötigen die Herden viel Stroh, und das ist in diesem Land nur schwer zu bekommen. Sie sollten daher andere Städte ausfindig machen, von denen Sie Stroh erhalten können, das Sie außerdem auch zur Herstellung von Ziegeln für Ihre Mastaba benötigen. @PDie Stadt Byblos im Libanon, dem Land der Zedern, hat begonnen, mit den mächtigen Imperien des Ostens Handel zu treiben. Dabei handelt es sich um Assyrien und Ur, die zwischen den beiden großen Flüssen in dem Land liegen, das man 'Mesopotamien' nennt. Feinstes Elfenbein aus diesen Orten können Sie über Byblos erwerben. Mit dem Eintreffen solch seltener, exotischer Luxuswaren wird Dendera gewiss aufblühen. @PIn der Hauptstadt erfreut sich Senet, ein neues Brettspiel, bei den Ägyptern immer größerer Beliebtheit. Dazu trifft man sich meist in einem öffentlichen Gebäude, dem so genannten 'Senet-Haus', und lässt sich dabei einen Krug Bier munden. An solchen Orten vergessen die Menschen von Dendera vorübergehend die Tyrannei des Cheops. @PDer Pharao hat befohlen, dass unzählige Steinbrüche in Heliopolis, das im Deltagebiet liegt, eingerichtet werden sollen, um einen riesigen Vorrat herrlichen weißen Kalksteins zu fördern. Nur die Götter wissen, was er damit vorhaben mag. Gerüchten zufolge plant er ein monumentales Bauprojekt auf dem Plateau vor Giseh, um anmaßenderweise den Ruhm seines Vaters zu übertreffen, den dieser weise und gütige Herrscher durch den Bau seiner beiden herrlichen Pyramiden erworben hat."
        }
    }
    message_mission_heliopolis {
        id: 417,
        type: 3,
        size [40, 30]
        title {
            text: "Heliopolis",
            pos [50, 80]
        }
        subtitle {
            text: "Elfenbein aus dem Osten",
            pos [10, 30]
        }
        content {
            text: "Pharao Cheops hat den Thron bestiegen, und wie dies die Seher von Horus und Re vorhergesagt haben, stöhnt unser Volk bereits jetzt unter seiner Tyrannei. Gerüchten zufolge plant er ein monumentales Bauprojekt auf dem Plateau vor Giseh, um den Ruhm seines Vaters zu übertrumpfen, den dieser weise und gütige Herrscher durch den Bau seiner beiden herrlichen Pyramiden erworben hat.  @PPharao Cheops hat befohlen, dass einige Steinbrüche bei Tura im Deltagebiet eingerichtet werden, an einer Stelle, an der vor kurzem große Mengen herrlichen weißen Kalksteins entdeckt wurden. Darüber hinaus müssen Sie drei Mastabas für die Adligen dieser Region errichten, damit der Pharao deren Ergebenheit belohnen kann. Die Steinbruchsiedlung, die Sie aufgebaut haben, soll den Namen 'Heliopolis' tragen. Sie wird für viele Jahre weißen Kalkstein in großen Mengen liefern können ... auch wenn nur die Götter wissen, was der Pharao damit vorhaben mag. @PDie Stadt Byblos im Libanon, dem Land der Zedern, hat begonnen, mit den mächtigen Imperien des Ostens Handel zu treiben. Dabei handelt es sich um Assyrien und Ur, die zwischen den beiden großen Flüssen in dem Land liegen, das man 'Mesopotamien' nennt. Feinstes Elfenbein aus diesen Orten können Sie über Byblos erwerben. Mit dem Eintreffen solch seltener, exotischer Luxuswaren wird Heliopolis gewiss blühen und gedeihen. @PCheops hat die Entsendung eines königlichen Gouverneurs nach Dendera befohlen, um unser Land gegen eindringende Kuschiter zu verteidigen. Die königlichen Wesire bedauern den Gouverneur, der mit dieser schweren und gefährlichen Aufgabe betraut wurde.  @PIn der Hauptstadt erfreut sich Senet, ein neues Brettspiel, bei den Ägyptern immer größerer Beliebtheit. Dazu trifft man sich meist in einem öffentlichen Gebäude, dem so genannten 'Senet-Haus', und lässt sich dabei einen Krug Bier munden. An solchen Orten vergessen die Menschen von Heliopolis vorübergehend die Tyrannei des Cheops."
        }
    }
    message_mission_giza {
        id: 418,
        type: 3,
        size [40, 30]
        title {
            text: "Giseh",
            pos [50, 80]
        }
        subtitle {
            text: "Die große Pyramide und die Sphinx",
            pos [10, 30]
        }
        content {
            text: "Pharao Cheops hat seine Pläne bekannt gegeben. Sein grenzenloser Ehrgeiz lastet schwer auf unserem Volk. Der Pharao verflucht und segnet Ihre Familie gleichzeitig. Hat man Ihnen einerseits den Status eines Nomarchen verliehen, wurden Sie andererseits mit der Ausführung des ehrgeizigsten Bauprojekts beauftragt, das jemals in unserem Land ersonnen wurde.  @PDie letzte Ruhestatt des Pharao soll ein massiver Pyramidenkomplex sein, weit entfernt von jeder Stadt auf dem Plateau vor Giseh gelegen. Sein Sarg wird aus solidem Granit bestehen, seine Begräbnisbarke aus wertvollem libanesischen Zedernholz. Neben dem Pyramidenkomplex des Pharao soll eine kleinere Pyramide für seinen Sohn, Prinz Chephren, entstehen, dessen Tyrannei der seines Vaters gleichkommt, dessen Erfolge jedoch hinter diesem zurückbleiben. Chephren verlangt darüber hinaus, dass sein Abbild in den Stein bei Giseh gehauen wird, als Teil einer riesigen Figur, die man 'Sphinx' nennt und die den Körper eines Löwen und den Kopf eines Menschen hat. @PZur Bereitstellung der riesigen Mengen an Material und Arbeitskräften, die für den Bau dieses Monuments nötig sind, müssen Sie bei Giseh eine große Siedlung errichten. Die Bedingungen dort werden nicht allzu gut sein. Doch darüber sollten Sie hinwegsehen und sich einzig auf Ihre Ziele konzentrieren, nämlich, diese drei großen Projekte abzuschließen und den Pharao zu ehren.  @PEinen Teil des herrlichen weißen Sandsteins für die Verschalung der Pyramiden bekommen Sie gestellt, aber den Großteil der notwendigen Aufwendungen müssen Sie aus der Stadtkasse bezahlen. @PDer Pharao vertraut Ihnen, einem seiner königlichen Nomarchen, diese drei heiligen Aufgaben an. Nun müssen Sie dem Pharao absolute Treue beweisen und seine Wünsche erfüllen ... koste es, was es wolle."
        }
    }
    message_mission_bahariya_oasis {
        id: 419,
        type: 3,
        size [40, 30]
        title {
            text: "Oase Baharija",
            pos [50, 80]
        }
        subtitle {
            text: "Die westliche Wüste",
            pos [10, 30]
        }
        content {
            text: "@PDie Herrschaft von Cheops und Chephren ist zu Ende. Mit ihnen endet auch die vierte Dynastie der ägyptischen Herrscherfamilien. Chentkaues, eine Verwandte aus einer Nebenlinie dieser Dynastie, hat einen neuen Pharao namens 'Userkaf' geboren, so dass das königliche Geschlecht in gerader Linie fortbesteht. Mit Userkaf beginnt die fünfte Dynastie, ein Zeitalter, mit dem große Veränderungen einhergehen werden.  @PUserkaf hat die Herrschaft über das Land etwas dezentralisiert und den regionalen Behörden mehr Macht zugestanden. Jetzt haben Nomarchen wie Sie größere Spielräume bei der Ausübung ihrer Regierungsgeschäfte. Dieser Pharao sinniert auch nicht über den Bau einer riesigen Pyramide nach, in der er ewige Ruhe finden kann. Ihn treiben ganz andere Pläne um. @PPharao Userkaf hat Re, den Gott der Sonne und des Königreichs, zum König der Götter erklärt und plant, seine Herrschaft im ganzen Land zu verkünden. Es gibt in Ägypten bereits viele Sonnentempel, doch der Pharao wünscht, den Einfluss des Re bis an den Rand des Königreichs auszudehnen. @PHierzu müssen Sie eine befestigte Siedlung in der Oase Baharija tief in der westlichen Wüste errichten. Nutzen Sie das Wasser, das Sie dort finden, sorgfältig, denn die geringen Wassermengen, auf die man in dieser Entfernung vom Nil noch stößt, werden auch von den wilden Tieren der Wüste sehr begehrt. Sie sollten sich außerdem vor Angriffen durch libysche Krieger und Beduinen in Acht nehmen, die in letzter Zeit den Wüstenkarawanen verstärkt nachstellten. Planen Sie Ihre Verteidigungsanlagen sorgfältig, und nutzen Sie alle Ressourcen wie Holz und Wild, die Sie in der Oase vorfinden."
        }
    }
    message_mission_abusir {
        id: 420,
        type: 3,
        size [40, 30]
        title {
            text: "Abusir",
            pos [50, 80]
        }
        subtitle {
            text: "Der Sonnentempel",
            pos [10, 30]
        }
        content {
            text: "@PDie Herrschaft von Cheops und Chephren ist zu Ende. Mit ihnen endet auch die vierte Dynastie der ägyptischen Herrscherfamilien. Chentkaues, eine Verwandte aus einer Nebenlinie dieser Dynastie, hat einen neuen Pharao namens 'Userkaf' geboren, so dass das königliche Geschlecht in gerader Linie fortbesteht. Mit Userkaf beginnt die fünfte Dynastie, ein Zeitalter, mit dem große Veränderungen einhergehen werden.  @PUserkaf hat die Herrschaft über das Land etwas dezentralisiert und den regionalen Behörden mehr Macht zugestanden. Jetzt haben Nomarchen wie Sie größere Spielräume bei der Ausübung ihrer Regierungsgeschäfte. Dieser Pharao sinniert auch nicht über den Bau einer riesigen Pyramide nach, in der er ewige Ruhe finden kann. Ihn treiben ganz andere Pläne um. @PPharao Userkaf hat Re, den Gott der Sonne und des Königreichs, zum König der Götter erklärt und plant, seine Herrschaft im ganzen Land zu verkünden. Es gibt in Ägypten bereits viele Sonnentempel, doch der Pharao wünscht, den größten Sonnentempel von allen in Abusir in der feuchten Deltaregion Unterägyptens zu errichten.  @PWie fast im gesamten Delta gibt es auch in Abusir große Mengen an Wild, Fisch und anderen Tieren sowie eine üppige Vegetation. Bodenschätze allerdings sind Mangelware. So müssen Sie den Sandstein, den Sie für den Bau des Sonnentempels benötigen, aus den Steinbrüchen von Heliopolis heranschaffen. In Djedu können Sie Rinder züchten, um Fleisch zu erzeugen - allerdings brauchen die Herden viel Stroh als Futter. @PSie werden Land planieren müssen, um einen geeigneten Standort für den Sonnentempel vorzubereiten. Achten Sie darauf, genug, aber nicht zu viel von dem wertvollen Holz zu verkaufen, das Sie schlagen werden. Wenn es erst einmal weg ist, wird es möglicherweise schwierig, weiteres zu beschaffen. In Apollinopolis und Abydos braucht man stets Holz und Wild. Wenn Sie also mit diesen Städten Handel treiben, dürfte das dazu beitragen, die Aufwendungen für das Errichten des heiligen Monuments wieder hereinzuholen."
        }
    }
    message_mission_dunqul {
        id: 421,
        type: 3,
        size [40, 30]
        title {
            text: "Dungul",
            pos [50, 80]
        }
        subtitle {
            text: "Die kuschitische Gefahr",
            pos [10, 30]
        }
        content {
            text: "@PPharao Pepi ist nun an die Macht gekommen und hat Ihrer Familie den Kanzlerstatus zuerkannt. Seine 94 Jahre währende Herrschaft ist die längste überlieferte Herrschaftsdauer in der Geschichte der Menschheit - doch sie hatte ihren Preis. Die zentralisierte Macht wird zunehmend ausgehöhlt, und regionale Herrscher werden immer mächtiger. Die Ernten in einigen Regionen fallen deutlich geringer aus als üblich, und langsam beginnt das Schreckgespenst einer Hungersnot in Ägypten umzugehen. Memphis, einst eine herrliche, schöne Stadt, ist dem Verfall preisgegeben. Seher sagen schwere Zeiten voraus. @PAus der zunehmenden Schwäche Ägyptens versuchen seine mächtigen Nachbarn Nutzen zu ziehen. Der Außenposten in Buhen wird von verwegenen kuschitischen Soldaten belagert, die aus Kerma geschickt wurden, der größten nichtägyptischen Stadt in ganz Afrika. Die Kuschiter verlangen Tributzahlungen, und die geringste Provokation könnte zu einem direkten Angriff führen. Nubien hat ebenfalls seine Männer zu den Waffen gerufen und will verlorenes Land zurückerobern.  @PWenn Ägypten überleben soll, müssen Sie alles in Ihrer Macht stehende tun, um Handelsrouten aufrechtzuerhalten, damit der Warenverkehr von und nach Ägypten nicht abreißt. Sorgen Sie dafür, dass der unter schweren Verlusten erkämpfte Handelsposten in der Oase Selime offen bleibt. Pepi, der sich immer mehr Gedanken um seine Reise ins Jenseits macht, wird häufig Stein für den Bau seiner Pyramide fordern. Andere Städte, denen es an Nahrungsmitteln mangelt, werden Sie um Unterstützung bitten. @PSetzen Sie Ihre Ressourcen mit Bedacht ein. In der Oase gibt es viel wertvolles Holz, aber ein Teil des Waldes muss zerstört werden, um Zugang zu den begrenzten Wasserressourcen zu erlangen."
        }
    }
    message_mission_dakhla {
        id: 422,
        type: 3,
        size [40, 30]
        title {
            text: "Dachla",
            pos [50, 80]
        }
        subtitle {
            text: "Die Karawanenstraße",
            pos [10, 30]
        }
        content {
            text: "@PPharao Pepi ist nun an die Macht gekommen und hat Ihrer Familie den Kanzlerstatus zuerkannt. Seine 94 Jahre währende Herrschaft ist die längste überlieferte Herrschaftsdauer in der Geschichte der Menschheit - doch sie hatte ihren Preis. Die zentralisierte Macht wird zunehmend ausgehöhlt, und regionale Herrscher werden immer mächtiger. Die Ernten in einigen Regionen fallen deutlich geringer aus als üblich, und langsam beginnt das Schreckgespenst einer Hungersnot in Ägypten umzugehen. Memphis, einst eine herrliche, schöne Stadt, ist dem Verfall preisgegeben. Seher sagen schwere Zeiten voraus.  @PAus unserer zunehmenden Schwäche versuchen unsere mächtigen Nachbarn Nutzen zu ziehen. Unser Außenposten in Buhen wird von verwegenen kuschitischen Soldaten belagert, die aus Kerma geschickt wurden, der größten nichtägyptischen Stadt in ganz Afrika. Die Kuschiter verlangen Tributzahlungen, und die geringste Provokation könnte zu einem direkten Angriff führen. Nubien hat ebenfalls seine Männer zu den Waffen gerufen und will verlorenes Land zurückerobern.  @PVersuchen Sie, die Stabilität in Ägypten zu wahren, indem Sie einen Verwaltungsposten in der Oase Dachla einrichten. In der Oase gibt es einen großen Bestand an wertvollen Bäumen. Nur blockieren diese leider den Zugang zu den begrenzten Wasserreserven der Oase. Von diesem wichtigen Standort aus soll Ebenholz aus dem Inneren Afrikas importiert werden. Pepi, der sich immer mehr Gedanken um seine Reise ins Jenseits macht, wird Ziegel für den Bau seines Grabmals fordern. Andere Städte, denen es an Nahrungsmitteln mangelt, werden Sie um Unterstützung bitten."
        }
    }
    message_mission_thinis {
        id: 423,
        type: 3,
        size [40, 30]
        title {
            text: "Thinis ",
            pos [50, 80]
        }
        subtitle {
            text: "Bürgerkrieg",
            pos [10, 30]
        }
        content {
            text: "Nichts ist geblieben vom früheren Überfluss und Stolz, und die meisten Menschen fürchten, dass Ägypten nie wieder zu seiner einstigen Herrlichkeit zurückfinden wird. Osiris hat sich von seinem Volk abgewandt, und mehrere schwache Überflutungen nacheinander haben zu großen Hungersnöten geführt. Die Macht der Pharaonen, die früher nie in Frage gestellt wurde, ist nur noch ein matter Abglanz von einst. Stattdessen wird die politische Bühne nun von Provinzgouverneuren beherrscht, die sich gegenseitig ihre Einflussbereiche streitig machen. @PUnbeschadet aus diesem Chaos gingen zwei Adelsfamilien hervor, die versuchen, die Herrschaft über das Land an sich zu reißen. Die Herrscher von Herakleopolis haben ihre Ansprüche auf den Thron als rechtmäßige Erben angemeldet. Diese Familie ist bekannt für ihre Grausamkeit und weniger dafür, sich um den Hunger der Menschen zu kümmern. In Theben im Süden ist eine bislang unbedeutende Herrscherfamilie, das Haus Intef, an die Macht gekommen. Dieses Haus hat viel für die Wiedervereinigung des Südens getan. In dieser Konstellation entbrennt ein mörderischer Bürgerkrieg, angefacht von Herakleopolis, um die Herrschaft über ganz Ägypten. @PDarauf bedacht, für das Wohl des ägyptischen Volkes da zu sein, hat die Familie Intef Ihnen den Wiederaufbau der soeben eroberten Stadt Thinis anvertraut, einer der ältesten Städte Ägyptens. Zwei der herrlichsten und ältesten Gebäude von Thinis blieben während der Eroberung von Zerstörungen verschont: der Tempelkomplex des Osiris und das Herrenhaus. Die Familie Intef hat angeordnet, dass, sollte eines dieser Gebäude zerstört werden, keine Gelder für deren Restaurierung verschwendet würden. Die Herrscher von Theben räumen dem Wiederaufbau von Thinis oberste Priorität ein und haben ungeachtet der schlechten Zeiten großzügig Gelder für diesen Zweck bereitgestellt. Ihre Aufgabe ist es, den alten Glanz der Stadt Thinis wiederherzustellen, und eine Seestreitmacht und eine starke Armee aufzustellen, um die Stadt gegen die häufigen Angriffe derer zu verteidigen, die Herakleopolis treu ergeben sind. Dazu zählen auch die Städte Lykopolis, Hierakonpolis und Hermopolis. Nehmen Sie sich vor den Herrschern der Familie Herakleopolis in Acht: Möglicherweise werden sie einen Tribut verlangen, um Ihnen Loyalität - und Ihre Deben - abzupressen. Sehen Sie sich auch vor den opportunistischen Nubiern vor, die die internen Kämpfe in Ägypten zu ihrem eigenen Vorteil nutzen wollen."
        }
    }
    message_mission_thebes {
        id: 424,
        type: 3,
        size [40, 30]
        title {
            text: "Theben",
            pos [50, 80]
        }
        subtitle {
            text: "Bürgerkrieg",
            pos [10, 30]
        }
        content {
            text: "Nichts ist geblieben vom früheren Überfluss und Stolz, und die meisten Menschen fürchten, dass Ägypten nie wieder zu seiner einstigen Herrlichkeit zurückfinden wird. Osiris hat sich von seinem Volk abgewandt, und mehrere schwache Überflutungen nacheinander haben zu großen Hungersnöten geführt. Die Macht der Pharaonen, die früher nie in Frage gestellt wurde, ist nur noch ein matter Abglanz von einst. Stattdessen wird die politische Bühne nun von Provinzgouverneuren beherrscht, die sich gegenseitig ihre Einflussbereiche streitig machen. @PUnbeschadet aus diesem Chaos gingen zwei Adelsfamilien hervor, die versuchen, die Herrschaft über das Land an sich zu reißen. Die Herrscher von Herakleopolis haben ihre Ansprüche auf den Thron als rechtmäßige Erben angemeldet. Diese Familie ist bekannt für ihre Grausamkeit und weniger dafür, sich um den Hunger der Menschen zu kümmern. In Theben im Süden ist eine bislang unbedeutende Herrscherfamilie, das Haus Intef, an die Macht gekommen. Das Haus hat viel für die Wiedervereinigung des Südens getan. In dieser Konstellation entbrennt ein mörderischer Bürgerkrieg, angefacht von den Herrschern aus Herakleopolis, um die Herrschaft über ganz Ägypten. @PDie Familie Intef, die mit dem Kampf gegen die Herrscher von Herakleopolis beschäftigt ist, hat Sie mit dem Aufbau ihrer Heimatstadt Theben beauftragt. Um im Kampf gegen die Herrscher aus Herakleopolis erfolgreich zu bestehen und um ihren Ruf in Ägypten zu festigen, muss die Familie Intef Theben zu einem Dreh- und Angelpunkt machen, auf den sich andere Städte verlassen können und an den sie sich wenden, wenn sie Unterstützung oder Soldaten benötigen. Theben - möglicherweise einmal Hauptstadt, wenn die Familie Intef den Krieg gewinnen sollte - muss eine großartige Stadt werden. Mit den geringen Ressourcen, die Ihnen zur Verfügung stehen, haben Sie nun die Aufgabe, einen Sonnentempel und eine Pyramide zu errichten, um den Ägyptern die Herrlichkeit der Intefs zu beweisen. @Theben selbst ist keineswegs von Angriffen ausgenommen. Die Herrscher von Herakleopolis und deren Getreue werden die Stadt von Zeit zu Zeit bedrohen, möglicherweise wird man auch versuchen, Geld aus der Stadtkasse zu erpressen. Um sich gegen diese vielfältigen Gefahren zu wappnen, müssen Sie starke Land- und Seestreitkräfte aufbauen, die die Stadt und andere bedrohte Städte zu verteidigen in der Lage sind."
        }
    }
    message_mission_coptos {
        id: 425,
        type: 3,
        size [40, 30]
        title {
            text: "Koptos",
            pos [50, 80]
        }
        subtitle {
            text: "Wiedervereinigung",
            pos [10, 30]
        }
        content {
            text: "Was Ihre Familie während des Bürgerkriegs geleistet hat, soll nicht unbelohnt bleiben. Ich, Pharao Mentuhotep, erhebe Ihre Familie in den Rang eines Wesirs. In ganz Ägypten gibt es niemanden, dem ich mehr vertraue als Ihnen. Jetzt, da die beiden Königreiche Ober- und Unterägypten wieder vereinigt sind und die Hauptstadt Theben blüht, brauche ich Ihre Hilfe, um meine Position im ganzen Königreich zu stärken. @PTrotz der Wiedervereinigung flackern in Ägypten immer wieder Kämpfe auf, insbesondere in Gebieten, die einst den Herrschern von Herakleopolis treu ergeben waren. Um unsere neue Union zu festigen, möchte ich, dass Sie Koptos wieder aufbauen und verteidigen. Koptos soll eine glorreiche Stadt werden, die den Bürgern Ägyptens eindrucksvoll vor Augen führt, was unter meiner Herrschaft möglich ist. Die Stadt wird häufig von den verbliebenen Städten der Loyalisten angegriffen, z.B. von Hermopolis. Achten Sie also darauf, die Grenzen der Stadt zu verteidigen. @PDie Hungersnot im Land ist nach wie vor groß. Häufig werden andere Städte Sie um Nahrungsmittel bitten. Verschließen Sie Ihre Ohren nicht vor ihren flehenden Bitten. Ganz Ägypten soll meine Güte und die Ergebenheit meines treuen Wesirs rühmen. @PIch weiß, ich verlange viel von Ihnen, doch ich sehe niemanden in Ägypten, der sonst in der Lage wäre, diese schwierige Aufgabe zu erfüllen."
        }
    }
    message_mission_beni_hasan {
        id: 426,
        type: 3,
        size [40, 30]
        title {
            text: "Beni Hassan",
            pos [50, 80]
        }
        subtitle {
            text: "Wiedervereinigung",
            pos [10, 30]
        }
        content {
            text: "Was Ihre Familie während des Bürgerkriegs geleistet hat, soll nicht unbelohnt bleiben. Ich, Pharao Mentuhotep, erhebe Ihre Familie in den Rang eines Wesirs. In ganz Ägypten gibt es niemanden, dem ich mehr vertraue als Ihnen. Jetzt, da die beiden Königreiche Ober- und Unterägypten wieder vereinigt sind und die Hauptstadt Theben blüht, brauche ich Ihre Hilfe, um meine Position im ganzen Königreich zu stärken. @PTrotz der Wiedervereinigung flackern in Ägypten immer wieder Kämpfe auf, insbesondere in Gebieten, die einst den Herrschern von Herakleopolis treu ergeben waren. Um das wieder vereinigte Land zu festigen, möchte ich, dass Sie Beni Hassan wieder aufbauen und verteidigen. Die Stadt wurde während des Bürgerkriegs fast vollständig zerstört. Beni Hassan soll eine glorreiche Stadt werden, die den Bürgern Ägyptens eindrucksvoll vor Augen führt, was unter meiner Herrschaft möglich ist.  @PDie Hungersnot im Land ist nach wie vor groß. Häufig werden andere Städte Sie um Nahrungsmittel bitten. Verschließen Sie Ihre Ohren nicht vor ihren flehenden Bitten. Ganz Ägypten soll meine Güte und die Ergebenheit meines treuen Wesirs rühmen. Obelisken aus Granit sollen der Nachwelt von den Taten künden, die ich während meines Lebens für dieses Land vollbracht habe. @PIch weiß, ich verlange viel von Ihnen, aber ich weiß auch, dass Sie der Einzige in Ägypten sind, der in der Lage ist, meine Bitten zu erfüllen."
        }
    }
    message_mission_itjtawy {
        id: 427,
        type: 3,
        size [40, 30]
        title {
            text: "Itijtaui",
            pos [50, 80]
        }
        subtitle {
            text: "Die Gründung einer neuen Hauptstadt",
            pos [10, 30]
        }
        content {
            text: "Oh mächtiger Pharao, gesegnet von Re, wie glücklich müssen Sie sich schätzen! Ihren unvergleichlichen Aufstieg auf den ägyptischen Thron umgibt eine Aura des Göttlichen! Nur einem Liebling der Götter kann solches Glück widerfahren. Mit dem Machtantritt Ihrer Familie kann Ägypten einen neuen Anfang wagen und vielleicht all das Grauen des Bürgerkriegs hinter sich lassen. @PWas könnte diesen Neuanfang besser symbolisieren als die Errichtung einer herrlichen neuen Hauptstadt. Itijtaui ist mit seinen vielen Bodenschätzen ein idealer Ort dafür. Mit dem, was das Land in sich birgt, können Sie eine herrliche Stadt errichten, wie es dem Ruhm und der Güte Ihrer Dynastie gebührt. @PDamit die Leistungen Ihrer großen Dynastie niemals der Vergessenheit anheim fallen, sollten Sie zwei majestätische Ziegelpyramiden für sich und Ihre Familie errichten sowie eine furchterregende Sphinx, die Ihr Grab bewacht. Eine Familie, die vollbracht hat, was Sie vollbracht haben, verdient nichts Geringeres. @PDenken Sie jedoch stets daran, dass es einige im Land gibt, die die Rechtmäßigkeit Ihrer Herrschaft in Frage stellen. Viele leiden noch unter den Nachwirkungen der Hungersnot und beklagen, Sie hätten den Thron usurpiert. Wenn Sie die Not der Menschen lindern und ihnen helfen, ihre Behausungen wieder aufzubauen, können Sie ihrer grenzenlosen Loyalität gewiss sein. Sie sollten versuchen, sich so gut wie möglich um Ihre neuen Untertanen zu kümmern, damit diese nicht auf die Idee kommen, sich mit Waffengewalt gegen Sie zu erheben."
        }
    }
    message_mission_mirgissa {
        id: 428,
        type: 3,
        size [40, 30]
        title {
            text: "Mirgissa",
            pos [50, 80]
        }
        subtitle {
            text: "Nach Nubien",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da Ägypten fest unter Ihrer Herrschaft vereint ist, empfiehlt Ihnen Ihr Hofstaat ebenso wie ich, Ihr treuer Wesir, die Grenzen unseres Landes gen Süden nach Nubien zu erweitern. Das trockene Flussbett bei Allaqi enthält reiche Goldadern, und eine mächtige Stadt in Mirgissa, in der Sie Ihre Residenz einrichten, wird die Nubier gewiss von einem Angriff abhalten. Nehmen Sie sich jedoch vor den Kuschitern in Acht. Sie sind weitaus gefährlichere Gegner als die Nubier und werden ihre Schwerter benutzen, oh Pharao, um Sie davon zu überzeugen, ihr Königreich in Frieden zu lassen. @PUm ein dauerhaftes Zeichen in Nubien zu hinterlassen, sollten Sie einen großen Obelisken errichten, der Zeugnis von den vielen Errungenschaften Ägyptens ablegt. Der Obelisk wird den Nubiern überzeugender Beweis sein, welche Vorteile die ägyptische Herrschaft hat, und sie stets an unsere Gegenwart erinnern. @PWährend Ihre direkte Aufmerksamkeit auf Mirgissa gelenkt ist, sollten Sie unsere Absicht nicht aus den Augen verlieren, am Roten Meer bei Mersa eine blühende Hafenstadt zu errichten. Mersa wird Hilfe vom Pharao benötigen und nicht zögern, darum zu bitten. Wenn Mersa eine blühende Stadt wird, kann Mirgissa von dort aus mit dem wertvollen Kupfer beliefert werden, aus dem wir Waffen schmieden können."
        }
    }
    message_mission_mersa_gawasis {
        id: 429,
        type: 3,
        size [40, 30]
        title {
            text: "Mersa Gawasis",
            pos [50, 80]
        }
        subtitle {
            text: "An den Ufern des Roten Meers",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da Ägypten fest unter Ihrer Herrschaft vereinigt ist, müssen wir Handelsbeziehungen mit Städten in der ganzen Welt aufbauen, um den Reichtum Ägyptens zu vergrößern, oh König der zwei Länder.  @PJe wohlhabender Ihr Volk wird, desto größer wird sein Verlangen nach exotischen Waren. Das Volk hat genug von Juwelen, einem leicht erhältlichen Luxusgut, und wünscht sich seltene, teure Luxuswaren wie z. B. Weihrauch. Der Hofstaat und ich, Ihr treuer Wesir, empfehlen Ihnen, bei Mersa am Roten Meer einen Hafen einzurichten. Von Mersa aus kann eine Handelsroute in das ferne Punt eingerichtet werden, von wo - wenn auch zu enormen Kosten - der herrlichste Weihrauch der Welt importiert werden kann.  @PAbgesehen von einigen bescheidenen Adern mit Gold oder Kupfererz kann Mersa nur wenig eigene Rohstoffe produzieren, allerdings hat die Stadt große Potentiale für die Herstellung von Fertigprodukten. Durch den Import von Rohstoffen von seinen Handelspartnern und den Export von Fertigprodukten müsste Mersa in der Lage sein, gewinnbringende Geschäfte zu betreiben. @PWährend Sie in Mersa beschäftigt sind, richtet einer Ihrer besten Nomarchen ein neues Handelszentrum in Nubien ein. Seine Stadt, Mirgissa, wird ständig von Angriffen bedroht, daher sollte unser geliebter Pharao bereit sein, ihm jegliche Ressourcen zu schicken, die er möglicherweise benötigt. @PUnter Ihrer Herrschaft wird Mersa mit Sicherheit eine der schönsten Städte des Königreichs. Eine bessere letzte Ruhestatt für Sie und Ihre Familie ließe sich kaum denken. Vergessen Sie über der Errichtung des Hafens nicht die Vorbereitungen für das Leben nach dem Tode. Ein Mausoleum und eine kleine Ziegelpyramide werden eine hervorragende Wohnstatt für Sie und Ihre Familie abgeben, wenn Sie dereinst zu den Feldern voll Schilf gewandert sind."
        }
    }
    message_mission_semna {
        id: 430,
        type: 3,
        size [40, 30]
        title {
            text: "Semna",
            pos [50, 80]
        }
        subtitle {
            text: "Spießrutenlauf",
            pos [10, 30]
        }
        content {
            text: "Hochverehrter Pharao! Alles, wofür Ihre Familie so hart gekämpft hat, ist derzeit bedroht! Die Seestreitkräfte der Nubier patrouillieren auf dem Nil, sie greifen tief im Herzen Ägyptens an und plündern Dörfer und Städte ohne Unterschied. Wie gemeine Piraten überfallen sie Handelsschiffe und rauben unsere Waren. Um den Städten im Norden zu helfen, den Feind zurückzuschlagen, sollten Sie sich bereitmachen, Kriegsschiffe und Soldaten dorthin zu entsenden.  @PUm zu verhindern, dass die Nubier erneut in unsere Gewässer eindringen, empfehlen Ihnen die Militärberater den Bau mehrerer Festungen bei Semna zwischen dem zweiten und dritten Nilkatarakt. Die Festungen werden wie eine Art Korken wirken und die Nubier im Süden einschließen.  @PDie erfolgreiche Vertreibung der Nubier steht und fällt mit der Eroberung der Stadt Kuban. Kuban ist reich an Ressourcen. Wenn es uns gelänge, diese Stadt zu erobern, wäre dies der Todesstoß für die nubische Wirtschaft. Sobald es Ihnen gelungen ist, den Nubiern die Herrschaft über Kuban zu entreißen, können Sie anfangen, aus dieser Stadt Sandstein für Ihr großes Mausoleum zu importieren. Ihr Mausoleum in Semna wird stets an Ihren Sieg über die widerspenstigen Nubier erinnern.  @PVor Ihnen türmen sich die Herausforderungen, wenn Sie Ägypten vor den Nubiern schützen wollen. Oh lebendiger Horus, stets muss auf den Sturm geachtet werden, der sich im Osten erhebt. Das Donnern der Pferdehufe schallt durch ganz Kanaan, und die blitzschnellen Streitwagen legen alles in Schutt und Asche, das sich ihnen in den Weg stellt. Solche Wagen, die durch nichts aufzuhalten sind, hat man nie zuvor gesehen. Sie werden von Kriegern vom Volk der Hyksos gefahren. Bereits jetzt erheben sich dunkle Wolken am ägyptischen Horizont - seien Sie gewappnet, wenn die Gefahr näher kommt."
        }
    }
    message_mission_bubastis {
        id: 431,
        type: 3,
        size [40, 30]
        title {
            text: "Bubastis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Stadt der Bastet",
            pos [10, 30]
        }
        content {
            text: "Oh königlicher Pharao. Jetzt, da die Handelsrouten fest verankert sind, sollten wir Ägypten zeigen, was Erfolg und Wohlstand ihm bringen können. Bubastis ist ein idealer Standort für eine solche Stadt: Von hier aus können wir unsere wichtigen Handelsrouten in den Osten schützen und gleichzeitig Bastet Ehre erweisen, die ihre schützende Hand über Ägypten gehalten hat. @PDie Stadt der Göttin Bastet soll keiner anderen Stadt in Ägypten gleichen. Sie soll lieblich sein wie eine Lotusblume und reich an Unterhaltung, Schulen, Bibliotheken und Andachtsorten. Die Bürger der Stadt sollen ausreichend mit Luxuswaren versorgt werden, wozu auch importierter Weihrauch gehören soll. Wenn die Stadt fertig ist, wird sie das Juwel in der Doppelkrone sein. @PWenn Sie diese herrliche Stadt errichten, sollten Sie jedoch auch stets ein Auge auf den Sturm haben, der sich im Osten erhebt. Das Donnern der Pferdehufe schallt durch ganz Kanaan, und die blitzschnellen Streitwagen legen alles in Schutt und Asche, das sich ihnen in den Weg stellt. Solche Wagen, die durch nichts aufzuhalten sind, hat man nie zuvor gesehen. Sie werden von Kriegern vom Volk der Hyksos gefahren. Bereits jetzt erheben sich dunkle Wolken am ägyptischen Horizont - seien Sie gewappnet, wenn die Gefahr näher kommt."
        }
    }
    message_mission_hermopolis {
        id: 432,
        type: 3,
        size [40, 30]
        title {
            text: "Hermopolis",
            pos [50, 80]
        }
        subtitle {
            text: "Invasion in Ägypten",
            pos [10, 30]
        }
        content {
            text: "Oh mächtigster aller Pharaonen - Ägypten ruft Sie um Hilfe an. Die finsteren Hyksos sind in unser Land eingefallen und haben eine eigene Hauptstadt in Avaris errichtet. Von dort aus haben sie viele unserer Handelsrouten unterbrochen und uns so von dringend benötigten Gütern abgeschnitten. Wir müssen ihrem Siegeszug Einhalt gebieten, bevor es zu spät ist. @PWenn es Ihnen gefällt, großer Pharao, sollten wir die Stadt Hermopolis zurückerobern, die von den grausamen Eindringlingen eingenommen wurde. Darüber hinaus sollten wir starke Land- und Seestreitkräfte aufbauen, denn es kann sein, dass wir unseren Landsleuten im Norden Truppen und Waffen stellen müssen, um die Hyksos zurückzuschlagen - insbesondere in Avaris. Oh Sohn des Re, edler Pharao, die Menschen warten auf Ihre Hilfe. Doch nun besitzen auch wir eine neue Waffe. Unseren weisen militärischen Führern ist es gelungen, den Gebrauch des gefürchteten Wagens zu studieren. Mit diesem werden wir uns gegen unsere Feinde stellen und sie wieder aus dem Land vertreiben. Nach der Vertreibung der Hyksos empfehlen unsere Militärberater den Bau eines Forts bei Scharuhen im Lande Sinai, um weitere Invasionen aus dem Osten zu verhindern. @PAch, wenn unsere Schwierigkeiten doch nur auf den Norden beschränkt wären! Berichte von unserer Südgrenze indessen zeigen, dass die Nubier die auf andere Dinge gerichtete Aufmerksamkeit Ägyptens wieder einmal zu ihrem Vorteil nutzen wollen. Sie haben die im Süden gelegenen Städte Mirgissa und Semna zurückerobert. Zwar bereiten uns diese verlorenen Städte Kopfzerbrechen, dennoch müssen wir erst die Hyksos vertreiben, bevor wir uns wieder dem Süden zuwenden können. @PDiese Hyksos sind wahrhaft bösartige Eindringlinge. Soeben haben wir entdeckt, dass sie eine Pyramide hier in Hermopolis geschändet haben. Sie haben sämtliche Grabbeigaben des mächtigen Pharao gestohlen, die dieser im Schilffeld benötigt. Wir sollten dem dort bestatteten Pharao neue Grabbeigaben schenken, damit er das Leben in der Ewigkeit genießen kann."
        }
    }
    message_mission_lykopolis {
        id: 433,
        type: 3,
        size [40, 30]
        title {
            text: "Lykopolis",
            pos [50, 80]
        }
        subtitle {
            text: "Invasion in Ägypten",
            pos [10, 30]
        }
        content {
            text: "Oh König der zwei Länder - Ägypten fleht Sie um Hilfe an. Die finsteren Hyksos sind in unser Land eingefallen und haben eine eigene Hauptstadt in Avaris errichtet. Von dort aus haben sie viele unserer Handelsrouten unterbrochen. Wir müssen ihrem Siegeszug Einhalt gebieten, bevor es zu spät ist. @PHier in Lykopolis sind wir vor direkten Angriffen sicher, obschon die Hyksos die Dreistigkeit besitzen, Tributzahlungen zu verlangen. Möglicherweise müssen wir unseren Landsleuten im Norden Truppen und Waffen zur Verfügung stellen, um zum Zurückschlagen der Hyksos beizutragen. Oh edler Pharao, die Menschen warten auf Ihre Hilfe. Inzwischen sind aber auch wir im Besitz der neuen Waffe. Unseren weisen militärischen Führern ist es gelungen, den Gebrauch des gefürchteten Wagens zu studieren. Mit diesem werden wir uns gegen unsere Feinde stellen und sie wieder aus dem Land vertreiben. @PAch, wenn unsere Schwierigkeiten doch nur auf den Norden beschränkt wären! Berichte von unserer Südgrenze indessen zeigen, dass die Nubier die auf andere Dinge gerichtete Aufmerksamkeit Ägyptens wieder einmal zu ihrem Vorteil nutzen wollen. Sie haben die im Süden gelegenen Städte Mirgissa und Semna zurückerobert. @PWenn Ägypten aus dieser schweren Zeit unversehrt hervorgehen soll, wird Ihren Generälen zu Wasser und zu Lande das Äußerste abverlangt werden. Um Ihre beiden besten Generäle zu beflügeln, haben Sie das Gelübde abgelegt, jedem eine Pyramide zu bauen, die ebenso spektakulär ist wie Ihre eigene. Mit dieser Aussicht im Herzen kämpfen sie mit aller Macht gegen den Feind und mobilisieren die letzten Reserven an Kraft und Zähigkeit.  @PWenn es Ihnen denn gefällt, oh mächtiger Pharao, so sollten Sie drei herrliche Pyramiden in Lykopolis bauen - eine für sich selbst und eine für jeden der beiden Generäle. Diese drei Pyramiden werden verhältnismäßig viel Platz benötigen, Sie werden also einige wertvolle Ressourcen aufgeben müssen, um Raum dafür zu schaffen. Möglicherweise müssen Sie Ihre Stadt auch über den Nil hinweg ausdehnen, um sämtliche benötigten Ressourcen zu erhalten, die diese Stadt braucht, um zu gedeihen."
        }
    }
    message_mission_byblos {
        id: 434,
        type: 3,
        size [40, 30]
        title {
            text: "Byblos",
            pos [50, 80]
        }
        subtitle {
            text: "Ausdehnung und Eroberung",
            pos [10, 30]
        }
        content {
            text: "Ägypten ist gestärkt aus den jüngsten Schwierigkeiten hervorgegangen. Byblos, mit all seinen grünen Wäldern und reichen Kupfervorkommen, ist unser! Mit Ihrer Anwesenheit hier wird die Stadt gewiss aufblühen, und ein neues Königreich wird errichtet. @PAber welch eine schreckliche Entdeckung mussten wir nach der Eroberung von Byblos machen! Ein neues, grausames Volk, die Hethiter, sind über einen Großteil Asiens hergefallen - manch einer sagt sogar, ihr Imperium käme von der Größe her an unseres heran! Nun haben sie ihre gierigen Augen gen Byblos gewandt. Wenn wir uns nicht gut auf ihren Angriff vorbereiten, könnte es sein, dass wir Byblos wieder an den Feind verlieren.  @PWährend wir uns gegen die hethitische Gefahr wappnen, müssen wir Byblos auf ewig als ägyptische Stadt kennzeichnen. Mit Ihrem Segen, oh Pharao, werden wir eine Reihe von drei Obelisken - zwei kleine und einen großen - errichten, die Ihre Souveränität und Ihren Ruhm bis in den letzten Winkel Ihres Königreichs verkünden. Diese alles überragenden Monumente werden die Einwohner von Byblos daran erinnern, wem sie Treue schulden. @PWährend wir uns in Byblos mit diesen Problemen beschäftigen, werden andere Gegenden Ägyptens weiterhin angegriffen. Die Nubier sind bereits am ersten Katarakt angelangt. Wir müssen unseren Mitbürgern helfen, sie zurückzuschlagen. Laut Berichten aus Avaris gibt es einen weiteren geheimnisvollen neuen Feind: das Seevolk. Beide Feinde müssen mit äußerster Härte bekämpft werden, wenn Ägypten ruhmreich bleiben will. Um Ihre Macht zu zeigen, sollten Sie unbedingt Truppen und Kriegsschiffe entsenden, sobald diese angefordert werden."
        }
    }
    message_mission_kuban {
        id: 435,
        type: 3,
        size [40, 30]
        title {
            text: "Kuban",
            pos [50, 80]
        }
        subtitle {
            text: "Der Glanz Ägyptens",
            pos [10, 30]
        }
        content {
            text: "Jetzt, da die Hyksos erfolgreich aus unserem Land vertrieben wurden, ist unser Land für seine Wiederauferstehung bereit - für ein neues Königreich, dessen neuer Glanz den der Vergangenheit überstrahlen wird. Oh edler Pharao, Kuban ist ein idealer Ort für den Anbeginn dieses neuen Königreichs. Die großen Goldvorkommen in Baki können wir nutzen, um Ihre neue Vision Ägyptens in Stein zu meißeln.  @PZwar steht Ägypten an der Schwelle zu wahrer Größe, dennoch bleiben einige störenden Probleme bestehen. Viele ägyptische Städte erholen sich noch von den Überfällen der Hyksos und bedürfen möglicherweise pharaonischer Hilfe. In anderen Gegenden greifen unsere alten Feinde weiterhin an, und der neue Feind, das Seevolk, geht an unserer Nordküste auf Raubzüge. Sie müssen also bereit sein, andere ägyptische Städte gegen unsere alten und neuen Feinden zu verteidigen. @PMit zunehmender Bedeutung Ägyptens sind viele Städte bereit, mit uns Handel zu treiben. Einigen dieser Städte ist unsere Kultur so vertraut und sie stehen so sehr im Banne unserer Macht, dass sie sich als ägyptische Städte verstehen, andere dagegen sind uns fremd und treiben zum ersten Mal mit uns Handel. Nutzen Sie all diese Beziehungen zum Ruhme Ägyptens und um Ihrem Volk all die Waren zu bieten, die es wünscht. @PUm das neue Zeitalter würdig zu empfangen, wäre es Ihren königlichen Architekten eine Ehre, zwei Pyramiden und ein herrliches Mausoleum für Sie, oh großer Pharao, zu errichten. Diese Bauwerke werden gewiss den Wohlstand und die Herrlichkeit widerspiegeln, die Sie Ägypten gebracht haben."
        }
    }
    message_mission_avarist {
        id: 436,
        type: 3,
        size [40, 30]
        title {
            text: "Rowarty",
            pos [50, 80]
        }
        subtitle {
            text: "Das Seevolk",
            pos [10, 30]
        }
        content {
            text: "Oh güldener Horus, unser Griff um Asien ist stark und unbestritten, und unsere Grenzen erstrecken sich wieder bis weit nach Nubien hinein. An unserer Nordküste jedoch nehmen die Schwierigkeiten zu. Das Seevolk wird zunehmend aggressiver und plündert unsere Städte ohne Rücksicht. Nur die Gegenwart des Pharao wird in der Lage sein, diese wilden und ruchlosen Gegner zu besiegen. Wenn Sie eine Seestreitkraft aufstellen, die von einer starken Armee unterstützt wird, werden wir das Seevolk bestimmt überwältigen.  @PWährend Sie das Seevolk in die Knie zwingen, tragen Ihre tapferen Nomarchen Angriffe in der ganzen Welt vor. Sollte ihnen Erfolg beschieden sein, wird Ägypten die Welt vom großen Euphrat in Asien bis hin zur riesigen kuschitischen Stadt Kerma im Süden untertan sein. Wenn Ihnen und Ihren Nomarchen der Sieg gehört, wird Ihre Dynastie als die größte Herrscherdynastie aller Zeiten in die ägyptische Geschichte eingehen. @PIhr großer Einfluss wird auch durch einen neuen, entfernten Handelspartner unter Beweis gestellt - die Stadt Mykene. Der König von Mykene hat von der Herrlichkeit und dem Reichtum Ägyptens erfahren und will mit uns Handel treiben. Wenn Sie dieser Handelsroute zustimmen, oh Pharao, werden Ihre Bürger exotische Waren erhalten, wie sie sie noch nie gesehen haben. @PUm die königliche Familie in ihrem Leben nach dem Tod würdig zu beherbergen, müssen ein mächtiges Mausoleum und zwei beeindruckende Ziegelpyramiden errichtet werden. Diese Monumente werden Ihre Taten als Feldherr und Wohltäter rühmen und unvergesslich machen."
        }
    }
    message_mission_kahun {
        id: 437,
        type: 3,
        size [40, 30]
        title {
            text: "Kahun",
            pos [50, 80]
        }
        subtitle {
            text: "Die Herrlichkeit des Pharao",
            pos [10, 30]
        }
        content {
            text: "Oh gütiger Pharao, Sie haben unserem Land Frieden und Wohlstand gebracht. Unter Ihrer weisen, klugen Herrschaft ist Ägypten wieder ein mächtiges und glorreiches Land geworden. Alle Nomarchen sind Ihnen treu ergeben, alle Bedrohungen unserer großen Nation sind abgewendet. @PNachdem Sie alles erreicht haben, was sich Ihre Familie vor so vielen Jahren zum Ziel gesetzt hat, ist es nun an der Zeit, die Leistungen Ihrer großen Dynastie für die Nachwelt zu verewigen. Dies kann nur dadurch geschehen, dass Sie die größte Pyramide errichten, die es jemals in Ägypten gab, eine Pyramide, größer noch als die des Cheops in Giseh. Auch andere Mitglieder Ihrer edlen Familie haben viel auf dem langen Weg zur Herrschaft über Ägypten geopfert. Auch ihrer muss ehrend gedacht werden, am besten mit einem Mausoleum aus Sandstein, das ihrer unerschütterlichen Loyalität würdig ist.  @LDer ideale Standort für diese Monumente ist Kahun in der reichen Region Fayum. Von hier aus können Sie alle Staatsangelegenheiten regeln und allen Forderungen nach Waren nachkommen, die möglicherweise aus Städten in Ihrem Herrschaftsbereich eingehen, während Sie an Ihrer großen Pyramide bauen."
        }
    }
    message_mission_buto {
        id: 438,
        type: 3,
        size [40, 30]
        title {
            text: "Buto",
            pos [50, 80]
        }
        content {
            text: "@PMit Hilfe Ihrer Familie gelang es dem thinitischen König Aha, auch Hu-eje genannt, das Doppel-Königreich aus Unter- und Oberägypten zu vereinen. Er ernannte sich zum Pharao von ganz Ägypten und gründete in Memphis eine imposante Hauptstadt.  @PIhr Klan ist ein weiteres Mal umgezogen, diesmal in das feuchte Delta Unterägyptens, in ein Gebiet, das Buto genannt wird. Kanaanitische Kriegsschiffe stellten in dieser Gegend eine ständige Bedrohung dar, und wenn die Zeit dafür gekommen ist, kommen Sie wohl nicht umhin, selbst ebenfalls ein paar Kriegsschiffe zu bauen. @PIhre Familie wurde in den Adelsstand erhoben. Nun wird von Ihnen erwartet, dass Sie, bevor Sie von dieser Welt in die nächste wechseln, ein prächtiges Ziegelsteingrab - eine Mastaba - errichten, in dem Ihr Körper seine Reise in das Leben nach dem Tod antreten kann. @PZuerst müssen Sie jedoch einige Farmen an den Ufern des Nils bauen, damit Sie den fruchtbaren Schlamm nutzbar machen können, der nach den alljährlichen Überschwemmungen des Flusses am Ufer zurückbleibt. Nur dann kann Ihre Bevölkerung wachsen und gedeihen und schließlich groß genug werden, um das heilige Bauwerk zu vollenden. Doch Vorsicht: Im Leben spendenden Wasser des Nils lauern auch viele Gefahren, wie todbringende Krokodile, Nilpferde und Malaria übertragende Mücken. @L@L Ackerbau entlang des Nils @PSie müssen die Farmen direkt im Überschwemmungsland bauen, um von dessen Fruchtbarkeit profitieren zu können. Anders als die meisten Gewerbestätten müssen die Farmen im Überschwemmungsgebiet keinen direkten Zugang für Arbeiter haben. Ihre Felder benötigen aber trotzdem ständige Betreuung durch Landarbeiter, die aus Arbeiterlagern kommen. Bauen Sie die Arbeiterlager relativ nah an den landwirtschaftlichen Anwesen im Überschwemmungsgebiet, damit die Bauern nicht zu weit laufen müssen, um sie zu erreichen. @G56 @L@PJedes Jahr tritt der Nil über die Ufer und reichert die verbrauchte Erde wieder mit seinem fruchtbaren Schlamm an. Die Bauern bringen die jährliche Ernte kurz vor der Überschwemmung ein und liefern sie in Ihren Silos ab. Da es nur eine Ernte im Jahr gibt, sollten Sie dafür sorgen, dass Sie genügend Silos haben, um ausreichend Nahrung für Ihre wachsende Bevölkerung einzulagern."
        }
    }
    message_mission_pi_yer {
        id: 439,
        type: 3,
        size [40, 30]
        title {
            text: "Pi-Yer",
            pos [50, 80]
        }
        subtitle {
            text: "Das Land des Seevolks",
            pos [10, 30]
        }
        content {
            text: "@PDie Nachrichten über Unzufriedenheit und Unruhe im Westen haben in letzter Zeit immer beunruhigendere Formen angenommen. Späher berichten, dass einige fremdartig sprechende Barbarenstämme an den Küsten von Kyrenaica westlich von uns gelandet sind. Als wäre dies nicht schon schlimm genug, stehen diese Menschen auch noch auf Seiten von Maraye, dem Sohn des Did, König der Libyer und Feind des Pharao.  @PPharao Merneptah ist zu Ohren gekommen, dass sich diese ungehobelten Barbaren, mit ihren Frauen, Kindern und weltlichen Besitztümern im Schlepptau, bald nach Osten wenden werden. Auf der Suche nach einem Ort, an dem sie sich ansiedeln können, ziehen sie in Richtung des fruchtbaren Nildeltas - unseres Heimatlandes! Bei den nördlichen Oasen Siwa und Farafra hat es bereits kleinere Zwischenfälle gegeben. Jetzt liegt Pi-Yer vor ihnen, Ihre Stadt im Delta. Dieser langsam vorrückende Haufen von Barbaren könnte schon bald vor unseren Türen stehen. Der Pharao hat befohlen, dass sie keinesfalls weiter vordringen dürfen, sollten sie es tatsächlich bis hierher schaffen. @PSie werden Holz für den Bau stabiler Kriegsschiffe und Kupfer für Waffen importieren müssen. Was für ein Glück, dass die früher so lästigen Hethiter dank des großen Sieges bei Kadesch durch Ramses II., dem Vater unserer geliebten Merneptah, momentan friedlich sind. Befestigen Sie Ihre Stadt, und bereiten Sie Ihre treuen Truppen auf einen Kampf auf Leben und Tod vor."
        }
    }
    message_mission_migdol {
        id: 440,
        type: 3,
        size [40, 30]
        title {
            text: "Migdol",
            pos [50, 80]
        }
        subtitle {
            text: "Abwehr der Assyrer",
            pos [10, 30]
        }
        content {
            text: "@PSeit den Tagen des großen Schabaka, dem Einiger von Ober- und Unterägypten und Vater Pharao Taharqas, waren Konflikte mit den aggressiven Assyrern an der Tagesordnung. Als er noch lebte befand Pharao Schabaka es für angemessen, unseren Brüdern in Palästina zu helfen, die sehr unter der strengen Herrschaft Assyriens zu leiden hatten. Aber Vorsicht! Die Bluthunde des barbarischen Königs Asarhaddon marschieren wieder und haben erneut ein Auge auf den fruchtbaren Boden Ägyptens geworfen. Jetzt können Sie Ruhm und Ehre erringen! Von Ihnen als Königlichem Bürgermeister von Migdol wird erwartet, dass Sie die Angriffe dieser verfluchten Feinde zurückschlagen. Ihre Grenzfestung am östlichen Rand des Nildeltas bildet die Frontlinie von Ägyptens äußerem Verteidigungsring. @PEs ist wichtig, dass Sie Ihre Soldaten ordentlich ausbilden und neue Handelsverbindungen knüpfen, um die Lieferung von Waffen oder Rohstoffen zur Herstellung von eigenen Waffen zu gewährleisten. @PZeigen Sie keine Schwäche! Ein starkes Militär ist unabdingbar, um die Unabhängigkeit Ägyptens zu sichern. Wenn Sie nur sieben Jahre lang durchhalten, ist der Sieg Ihnen sicher. Taharqa, der große Pharao, zweiter Sohn von Schabaka, wird Sie im Auge behalten!"
        }
    }
    message_mission_tanis {
        id: 441,
        type: 3,
        size [40, 30]
        title {
            text: "Tanis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Wiedergeburt einer Seestreitmacht",
            pos [10, 30]
        }
        content {
            text: "@PViele Generationen Ägypter litten unter der grausamen Faust Persiens. Babylons Einfluss auf unser gesegnetes Land ist jedoch nicht so stark wie er früher einmal war. Während unsere verfluchten Unterdrücker damit beschäftigt waren, sich in die Politik Griechenlands einzumischen, ist es Ägypten durch eine ganze Reihe von Aufständen gelungen, den Würgegriff der verhassten Perser zu lockern. Nun allerdings ist Pharao Achoris zu Ohren gekommen, dass sich eine Streitmacht, ausgesandt von Artaxerxes II. und befehligt von Flottenadmiral Conon (einem griechischen Lakaien, der mit persischem Gold bezahlt wird), auf unsere Küsten zubewegt. Pharao Achoris hat in seiner Weisheit beschlossen, dass eine starke Flottenpräsenz auf dem Nil notwendig sei, um den Einfall zu verhindern. Als Königlicher Gouverneur von Tanis müssen Sie in den nächsten zehn Jahren massive Schiffe bauen und schlagkräftige Truppen ausbilden, um den Angriff zu Wasser und zu Lande abzuwehren. @PSie werden eine Handelsroute nach Enkomi einrichten und von dort Holz für den Bau Ihrer Flotte importieren müssen. Kupfer bekommen Sie ebenfalls aus Enkomi, das auf der Insel Zypern liegt. Diese Handelsroute ist jedoch stets äußerst gefährdet, da sie in der Nähe der levantinischen Küste verläuft, die von unseren Feinden kontrolliert wird. Wenn Sie den Pharao mit allem versorgen, was er benötigt, wird auch Ihr Einkommen steigen.  @PVergessen Sie nicht, dass die Stadtkassen in diesen unruhigen Zeiten nicht gerade voll sind. Sie müssen als Händler genauso geschickt sein wie als tüchtiger Kommandeur."
        }
    }
    message_mission_alexandria_2 {
        id: 442,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria",
            pos [50, 80]
        }
        subtitle {
            text: "Alexander der Große",
            pos [10, 30]
        }
        content {
            text: "@PDer große Alexander, Sohn von Philipp II. von Mazedonien und Geißel des babylonischen Reiches, beglückt Ägypten durch die Gnade seiner Anwesenheit. Bei seiner Ankunft hat der letzte korrupte persische Satrap fluchtartig das Feld geräumt. Alexander wurde nach seinem Opfer an den Apis-Stier in Memphis zum Pharao erklärt. Alle Menschen jubeln! Bevor er sich jedoch auf die Reise zum Orakel des Amun in der Oase Siwa begab, befahl unser Anführer die Gründung einer neuen Stadt. Einer Stadt, die nach seinem Wunsch einmal zur Hauptstadt dieses riesigen und wachsenden Imperiums werden soll. In seiner unendlichen Weisheit hat er Sie zum ersten Bürgermeister dieser zukünftigen Stadt bestimmt! @PDer große Alexander hat Ihnen eine großzügige Geldspende als Grundlage für das Bauvorhaben zukommen lassen und stellt den berühmten griechischen Architekten Dinokrates in Ihre Dienste. Er erwartet von Ihnen, dass Sie die wirtschaftliche, kulturelle und militärische Stärke dieser Stadt auf einen hohen Stand gebracht haben, wenn er in zwölf Jahren wieder zurückzukehren gedenkt.  @PUnser Anführer hat sich sogar herabgelassen, die Positionen der beiden Hauptdurchgangsstraßen dieser Stadt festzulegen. Die Kanopen-Straße verläuft entlang einer Ost-West-Achse, während die andere Hauptstraße im rechten Winkel dazu verläuft und von Kap Lochias aus südlich zum Mariut-See hinein ins Landesinnere führt. @PAls treuer Aufseher dieses Projektes sollten Sie so schnell es geht Hafenanlagen bauen und lukrative Handelsrouten einrichten. Es sollten sich eigentlich viele Abnehmer für unsere Produkte, insbesondere für Weizen, Gerste, Papyrus und Leinen finden lassen. Vernachlässigen Sie weder die kulturellen noch die militärischen Aspekte dieser Stadt, denn es gibt immer noch herumstreichende Barbaren, die Ägypten seiner Reichtümer berauben wollen."
        }
    }
    message_mission_ptolemy_alexandria {
        id: 443,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria (Ptolemäus)",
            pos [50, 80]
        }
        subtitle {
            text: "Ein strahlendes Licht",
            pos [10, 30]
        }
        content {
            text: "@PDas Erbe von Alexander dem Großen lebt in unserer stolzen Stadt weiter. Seine Stadt hat nicht aufgehört zu wachsen, auch wenn seine sterblichen Überreste schon lange im Mausoleum in Alexandria ruhen. Es liegt nun an Ihnen, Ptolemäus I. Soter, das Werk weiterzuführen, das der edle Alexander begonnen hat. Seit der Gründung der Stadt durch Alexander vor gerade einmal 30 Jahren ist die Stadt zu einem mächtigen Handelsknoten geworden, der große Teile des Umlandes mit den am meisten benötigten Nahrungsmitteln und Luxusgütern versorgt. Sie sollten auf der Insel Pharos in der Nähe der Hafeneinfahrt einen massiven Leuchtturm errichten, damit die vielen Schiffe sicher passieren können und der wirtschaftliche Aufstieg weiter voranschreitet. Das Leuchtsignal dieses Gebäudes wird die sich nähernden Seefahrer sicher in den Hafen leiten und sicherstellen, dass ihre Schiffe auf den tückischen Sandbänken nicht auf Grund laufen. @PSo bedeutsam der Handel auch ist, die kulturelle und intellektuelle Weiterentwicklung unserer Gesellschaft dürfen Sie dennoch nicht aus den Augen verlieren. Unter Ihrer Herrschaft kann Alexandria jetzt zur intellektuellen Hauptstadt der gesamten bekannten Welt werden. Tragen Sie Wissen von nah und fern zusammen, und bauen Sie eine große Bibliothek, in der es bewahrt werden kann. So sicher wie Ameisen von Honig angelockt werden, so sicher reisen dann auch Gelehrte aus aller Welt zu diesem unvergleichlichen Zentrum des Wissens und Lernens.  @PFür den Bau dieser großen Monumente werden Sie Baumaterial wie zum Beispiel weißen Marmor importieren müssen, der für so großartige Gebäude gerade gut genug ist. Enkomi auf der Insel Zypern ist eine gute Quelle für dieses Material.  @PUnd noch eines: Vernachlässigen Sie nicht Ihre Streitkräfte. Irgendwo scheint es immer Unruhen zu geben. Und es könnte durchaus notwendig werden, Truppen an weit entfernte Grenzen zu entsenden, um Ägyptens Interessen zu wahren und seine Ehre zu verteidigen."
        }
    }
    message_mission_maritis {
        id: 444,
        type: 3,
        size [40, 30]
        title {
            text: "Maritis",
            pos [50, 80]
        }
        subtitle {
            text: "Caesar und Kleopatra",
            pos [10, 30]
        }
        content {
            text: "@PDie Habgier des römischen Imperiums wird mit jedem Tag größer und greift immer weiter um sich. Sogar die tödlichen politischen Machtkämpfe Roms haben unser Land erreicht. Nach der Ermordung von Pompeius auf ägyptischem Boden hält Julius Caesar nun die absolute Kontrolle über die mächtigen Legionen Roms in seinen Händen und hat ein Auge auf die Reichtümer Ägyptens geworfen - wie auch auf die betörende Schönheit unserer Pharaonin Kleopatra VII., der Tochter von Ptolemäus XII. Auletes. Unsere kluge Herrscherin ist allerdings im Kampf der Geister nicht so leicht zu besiegen. Sollte Caesar danach trachten, sie als Werkzeug für eine künftige Einflussnahme auf Ägypten zu benutzen, wird sie ihn im Gegenzug zur Wahrung der dynastischen Macht unseres großen Landes zu verwenden wissen. @PCaesars Ankunft in Alexandria in Begleitung seiner äußerst unpopulären Römer entfachte unter den freidenkenden Bürgern einen Aufstand. Ein aufsässiger Mob, angestachelt von Kleopatras jüngerem Bruder Ptolemäus XIII., hat Caesar und seine Männer im königlichen Viertel der Stadt eingekesselt. Erbitterte Straßenkämpfe sind ausgebrochen, die viele Todesopfer forderten. Um sich einen seeseitigen Fluchtweg offen zu halten, ließ Caesar die ägyptische Flotte in Brand setzen, während diese in Alexandrias Hafen vor Anker lag. Unglücklicherweise sprang das Feuer auf einige entlang des Ufers liegende Lagerhäuser über, wodurch Papyrusrollen in großer Zahl verbrannten, die eigentlich für die Große Bibliothek bestimmt waren.  @PUm der Falle zu entkommen, in der er sich jetzt befindet, hat Caesar den ihm loyal ergebenen Mithradates und dessen Truppen aus Syrien herbeigerufen. Nach der erfolgreichen Erstürmung der Grenzfestung Migdol hat Mithradates seine Männer in einem Gewaltmarsch um das Nildelta herumgeführt, um sich Alexandria von Südosten zu nähern. Die Vorhut dieser Streitmacht lagert zurzeit in der Umgebung des Dorfes Maritis am östlichen Ufer des Sees Mariut und bereitet sich auf die letzte Etappe ihrer Reise vor.  @PPtolemäus XIII. hat vom Herannahen dieser Verstärkung erfahren. Als Antwort darauf setzte er einen Großteil seiner zahlenmäßig überlegenen Armee von Alexandria aus gen Südosten in Marsch. In Kürze wird eine entscheidende Schlacht am östlichen Ufer des Mariut-Sees stattfinden. Können Sie als Kommandeur der römischen Legionen des Mithradates die aufständische ägyptische Armee unter Ptolemäus besiegen und sich zu Caesar und Kleopatra nach Alexandria durchschlagen? Das Schicksal der beiden liegt in Ihren Händen."
        }
    }
    message_mission_cleopatra_alexandria {
        id: 445,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria (Kleopatra)",
            pos [50, 80]
        }
        subtitle {
            text: "Das Erbe einer Königin",
            pos [10, 30]
        }
        content {
            text: "@PCaesars grausamer Tod durch die Klingen von Meuchelmördern stürzte die römische Welt in Aufruhr und hat Ihnen, unserer Pharaonin Kleopatra VII., Trauer und Schmerz gebracht. Ihr Geliebter, Mentor, Vertrauter und mächtiger Verbündeter ist nicht mehr. Sein gerade den Kinderschuhen entwachsener adoptierter Großneffe Octavian wurde zu seinem Erben bestimmt. Der viel erfahrenere Marcus Antonius, ehemals ein Konsul Caesars, jedoch wurde, zum Leidwesen des jungen Octavian, zum formellen Staatsoberhaupt ernannt. Dass euer gemeinsamer Sohn Ptolemäus Caesar, auch 'Caesarion' genannt, in Caesars Testament nicht erwähnt wurde, konnte nicht weiter überraschen. Um Ihr Kind und sich selbst in Sicherheit zu bringen und auch die Macht Ägyptens weiter zu erhalten, haben Sie Rom mit Ziel Alexandria verlassen.  @PDoch trotz der großen räumlichen Entfernung zwischen Ihnen und Rom können Sie die mörderischen Machtkämpfe dort nicht völlig hinter sich lassen. Noch immer gieren mächtige Männer nach Macht - Ihre Unterstützung und der Zugang zu den Reichtümern Ägyptens wären ein großes Plus für jede Partei. Dass Sie in diesem Machtkampf den Sieger unterstützen, ist ungemein wichtig, denn eine Kollaboration mit dem Verlierer könnte leicht das Ende Ägyptens nach sich ziehen. Der dramatische Entscheidungskampf zwischen den rivalisierenden römischen Parteien, in dem Marcus Antonius' Caesarianer den entscheidenden Schlag gegen die Streitkräfte von Brutus und Cassius führten, fand unlängst bei Philippi statt. Antonius, Octavian und Lepidus bilden nun ein Triumvirat, um das Imperium zu lenken, wobei Antonius Anspruch auf den östlichen Teil einschließlich Ägypten erhebt. @PKurz nach dem Kampf befahl Ihnen Marcus Antonius, zu ihm nach Tarsus in Kleinasien zu kommen, um ihm zu erklären, warum es so lange dauerte, bis Sie sich auf die Seite der Caesarianer schlugen. Da Sie sich nicht wie ein Hund herbeizitieren lassen, haben Sie es in Ihrer Weisheit abgelehnt zu antworten. Schließlich wissen Sie besser als jeder andere, dass es sehr viel vorteilhafter ist, einen Römer nach IHREN Vorgaben zu empfangen, als umgekehrt. @PDaher sind Sie, Pharaonin Kleopatra, nach Ägypten und nach Alexandria heimgekehrt. Es ist nun an der Zeit, den Ruhm dieser einzigartigen Stadt des großen Alexander, dessen Grab noch heute Scharen von Pilgern besuchen, zu neuer Größe zu führen. Alexandrias berühmte Große Bibliothek zieht immer noch Gelehrte aus aller Welt an; das helle Leuchtsignal des wunderbaren Leuchtturms von Pharos weist immer noch den Weg, damit die Seefahrer sicher durch die tückischen Wasser des Hafens gelangen können. Sie können nun die Schönheit der Stadt durch den Bau des weitläufigen Caesareums zu Ehren Ihres ehemaligen Geliebten und Ihres kleinen Sohnes noch weiter bereichern. Darüber hinaus sichern Sie Ihren eigenen Übergang zum ewigen Leben durch den Bau eines weiteren Mausoleums, sodass Ihnen auch nach Ihrer Reise zu den Feldern des Schilfs gebührend gehuldigt werden kann.  @POb Marcus Antonius das nächste Mal wohl etwas mehr Takt walten lässt, wenn er nach Ihnen ruft?"
        }
    }
    message_mission_actium {
        id: 446,
        type: 3,
        size [40, 30]
        title {
            text: "Actium",
            pos [50, 80]
        }
        subtitle {
            text: "Antonius und Kleopatra",
            pos [10, 30]
        }
        content {
            text: "@POh edle Pharaonin Kleopatra VII., Gefährtin des Caesar und nun des Antonius, Ägyptens Geschick liegt in Ihren Händen, aber diese ruhen jetzt in denen eines Römers, Marcus Antonius - und der ist tief in den Kampf um die Macht in Rom und dessen Legionen verstrickt.  @PDa Marcus Antonius Ägyptens unermessliche Rohstoffe brauchte, aber auch Ihre Liebe und Zuneigung wünschte, willigte er in eine Hochzeit mit Ihnen ein. Unglücklicherweise hat die Nachricht von dieser neuen Verbindung in Rom einen Skandal ausgelöst! Wie Sie wissen, war Marcus Antonius noch immer mit Octavia, der Schwester von Caesars gesetzmäßigem Nachfolger Octavian, vermählt, mit dem zusammen er die Herrschaft über Rom ausübt. Diese Beziehung steht nun durch die offensichtliche Bigamie des Marcus Antonius vor einer schweren Zerreißprobe. Octavian ist der Ansicht, dass Marcus Antonius nicht nur die Ehre seiner Schwester und seiner Familie in den Schmutz gezogen, sondern auch das Ansehen Roms beschädigt hat. Um die Ehre wiederherzustellen und den Streit um die absolute Macht über Rom zu beenden, forderte Octavian Ihren Geliebten Marcus Antonius zu einem Kampf heraus. Aus diesem Grund entschied sich Marcus Antonius, der von Ihnen und Ihrer ägyptischen Flotte begleitet wird, für einen Ort auf dem griechischen Festland in der Nähe von Actium, um dort sein Lager aufzuschlagen. Diese Stelle bietet einen guten Hafen mit vielen möglichen Liegeplätzen für Ihre Schiffe.  @PSie müssen nun schnellstens eine Streitmacht und vor allem eine Flotte aufbauen. Octavian hat geschworen, im September des Jahres 31 zurückzukehren. @PNun hängt Ihr Schicksal und das von Marcus Antonius, aber auch die Zukunft Ägyptens und Roms einmal mehr davon ab, wie sich die militärischen Streitkräfte bewähren."
        }
    }
    message_mission_thutmose_valley {
        id: 447,
        type: 3,
        size [40, 30]
        title {
            text: "Thutmosis im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Das erste Grab",
            pos [10, 30]
        }
        content {
            text: "@PNach vielen brillanten Siegen auf weit entfernten Schlachtfeldern, die die Sicherheit des Landes und der Bewohner Ägyptens garantieren, denkt Pharao Thutmosis nun über die Vorbereitungen für seine Reise ins Jenseits nach. Um sicherzustellen, dass seine Reise erfolgreich verläuft, wünscht der Pharao, dass Sie so bald wie möglich mit dem Bau seines Grabes beginnen. Errichten Sie ein Dorf am Westufer des Nils, um tüchtige Arbeiter in Reichweite zu haben. Suchen Sie westlich des Dorfs in den Felsen nach einer passenden Stelle für das Grab. Sie werden geschickte Steinmetze benötigen, um die vielen Kammern des Grabes aus dem Stein zu hauen, sowie talentierte Kunsthandwerker, die die Räume verputzen und bemalen.  @PDamit die Arbeiter auch an den tiefsten Stellen des Grabes genügend Licht haben, müssen Sie Lampenwerkstätten errichten. Statten Sie die Lampenwerkstätten mit Töpferwaren und importiertem Öl als Brennstoff aus. Bauen Sie Henna auf Feldern an, um den Rohstoff für die leuchtenden Farben zu erzeugen, die die Farbenmacher benötigen werden."
        }
    }
    message_mission_tutankhamun_valley {
        id: 448,
        type: 3,
        size [40, 30]
        title {
            text: "Tut im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Tut-ench-Amuns Tod",
            pos [10, 30]
        }
        content {
            text: "@PEin furchtbares Unglück ist über unseren geliebten jungen Pharao Tut-ench-Amun hereingebrochen! Seine Herrschaft, die einst so viel Ruhm versprach, wurde durch die Hand des Schicksals erbarmungslos und viel zu früh beendet. Es ist nun an der Zeit, dass die Arbeiter in Deir el-Medina wieder einen Platz der ewigen Ruhe für den Pharao vorbereiten. Sein unvorhersehbarer früher Tod zwingt Sie, Ihre Arbeiter aufs Äußerste anzutreiben. Es stehen Ihnen nur wenige Jahre zur Verfügung, um Tut-ench-Amuns Grab so weit fertigzustellen, dass es mit allen nötigen Gütern für die Reise ins Jenseits ausgestattet ist und die geheiligten Überreste aufnehmen kann. Arbeiten Sie so schnell es irgend geht!"
        }
    }
    message_mission_seti_valley {
        id: 449,
        type: 3,
        size [40, 30]
        title {
            text: "Seti im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Ein Grab für einen Pharao",
            pos [10, 30]
        }
        content {
            text: "@PUnser mächtiger Pharao Seti, Sohn von Ramses I., hat verkündet, dass der richtige Zeitpunkt für den Beginn der Vorbereitungen für seine Reise ins Jenseits gekommen sei. Daher werden Sie im Tal der Könige mit den Ausschachtarbeiten für sein königliches Grab beginnen. Bei diesem Vorhaben müssen Sie Ihren Arbeitern die größten Anstrengungen abverlangen. Es müssen geeignete Vorkehrungen getroffen werden, um sicherzustellen, dass nach der Vollendung die bauliche Meisterleistung auf lange Sicht unerreicht bleiben wird. @PPlanen Sie beim Bau dieses königlichen Projektes unbedingt strikte Schutzmaßnahmen gegen Banditen mit ein! Es hat bereits Berichte über Banden gieriger Verbrecher gegeben, die sich durch Plünderung der Grabkammern bereichern wollen und dabei den Frieden der in Ewigkeit ruhenden Pharaonen stören. Lassen Sie nicht zu, dass diese gottlosen Taten die königlichen Gräber im Tal der Könige entweihen, sonst wird, so sicher wie die Sonne im Osten aufgeht, auch Ihre Stellung im Königreich darunter leiden."
        }
    }
    message_mission_sumur {
        id: 450,
        type: 3,
        size [40, 30]
        title {
            text: "Sumur",
            pos [50, 80]
        }
        subtitle {
            text: "Land der Levante",
            pos [10, 30]
        }
        content {
            text: "@PSeien Sie gegrüßt, königlicher Gouverneur, Herrscher über die Levante und ergebener Untertan unseres Pharao, Sohn des Ra. Sie können sich wirklich glücklich schätzen, in dieser Zeit zu leben, in der sich die wohlwollende Hand Ägyptens von Nubien bis weit zu den levantinischen Küsten erstreckt. Unendlich ist die Weisheit unseres neuen Pharao, des hochverehrten Ramses II., und groß ist seine Vision, denn er hat Ihnen die Gnade erwiesen, in diesem herrlichen Land zu regieren, das nun Teil des ständig wachsenden ägyptischen Reiches ist.  @PDiese Region besitzt, auch wenn hier noch immer zahlreiche Gefahren drohen, viele Reichtümer, die ihrer Ausbeutung harren. Auf den grünen Hügeln wachsen hohe Bäume, aus denen bestes Holz für die Herstellung von Streitwagen und vielen anderen Dingen gewonnen werden kann. Kupferadern sind zwar relativ selten, aber dennoch zu finden, und werden zur Herstellung von starken Waffen benötigt. Holz und Kupfer, also Dinge, die in unserem Heimatland sehr selten sind, werden mit Sicherheit hochwillkommen sein, wenn sie in großen Mengen in die Heimat geschickt werden. Deshalb wurden Sie mit der Aufgabe betraut, die Errichtung eines großen Handelshafens zu beaufsichtigen, von dem aus diese wertvollen Güter exportiert werden können. Pharao und das ägyptische Volk werden Ihnen sehr dankbar sein! @PAber Vorsicht! Achten Sie darauf, dass Ihre eigenen vertrauenswürdigen Soldaten mit schnellen Streitwagen und starken Waffen ausgerüstet sind, denn die Hethiter sind noch immer gefährlich, auch wenn sie von Seti, dem Vater des Pharao, besiegt wurden. Sie könnten Ihre rechtmäßige Autorität in diesem reichen Land anfechten. Daher wird sich vermutlich eine starke militärische Präsenz in diesem neuen Territorium als notwendig erweisen, um Aufstände zu verhindern, und auch in der Zukunft dürfte sie sicherlich äußerst nützlich sein. @PZu guter Letzt betrachtet es Pharao Ramses II. als angemessen, wenn Sie einen Obelisken zum Zeichen seines Ruhmes errichten, damit die Bewohner dieser Region nicht vergessen, wem sie jetzt ihren Respekt zollen müssen."
        }
    }
    message_mission_qadesh {
        id: 451,
        type: 3,
        size [40, 30]
        title {
            text: "Kadesch",
            pos [50, 80]
        }
        subtitle {
            text: "Die Schlacht von Kadesch",
            pos [10, 30]
        }
        content {
            text: "@PAmurra an der levantinischen Küste erzittert unter den Hufen Ihrer Furcht erregenden Kavallerie und den Füßen Ihrer mächtigen Legionen, gesegneter Pharao. Diese Region ist nicht nur reich an Edelsteinen, noch reicher ist sie an Zwietracht. Bewaffnete Hethiter unter der Führung des erbärmlichen Königs Muwatallis trachten erneut nach der Herrschaft über dieses Land, das rechtmäßig uns gehört. Gefangen genommene Spione berichten davon, dass seine feindlichen Banden sich noch weit im Norden aufhalten und daher keine Bedrohung darstellen. Aber kann man dem Glauben schenken? Weise ist der Krieger, der seinen Schild im Kampf nicht fallen lässt.  @PUm Gerüchte über Aufstände im Keim zu ersticken, sind Sie, unser hochverehrter Pharao Ramses II., Sohn des Ra, in der Festungsstadt Kadesch eingetroffen. In der Umgebung haben bereits zwei unserer gefürchteten Streitwagenkompanien ihre Lager aufgeschlagen. Aber das ist nicht alles. Andere Veteranenkompanien, darunter die erfahrenen Truppen, die vor kurzem erst in der Nähe von Sumur gekämpft haben, stehen ebenfalls zu Ihrer Verfügung. Doch Vorsicht! Sie wären gut beraten, die wertvollen Truppen erst einzusetzen, wenn sie wirklich gebraucht werden. Denn weise ist auch der Krieger, der gute Truppen in Reserve hält, um sie auf dem Höhepunkt des Gefechtes in die Schlacht zu schicken. @PNachdem der elende Feind vernichtet ist, wird es notwendig sein, die stagnierende Wirtschaft von Kadesch wieder zu beleben, damit auch diese Stadt zum Ruhme Ägyptens beitragen kann. Tragen Sie wertvolle Edelsteine zusammen, und stellen Sie fähige Juweliere ein, die daraus exquisite Güter für die treuen Untertanen des Pharao fertigen. Luxusgüter von solch seltener Schönheit werden mit Sicherheit sehr gefragt sein!"
        }
    }
    message_mission_abu_simbel {
        id: 452,
        type: 3,
        size [40, 30]
        title {
            text: "Abu Simbel",
            pos [50, 80]
        }
        subtitle {
            text: "Die Felsentempel von Abu Simbel",
            pos [10, 30]
        }
        content {
            text: "@PDer Ruhm unseres Pharao Ramses II. erfüllt das Land. Damit seine Herrschaft auf ewig lebendig bleiben möge, wurde beschlossen, dass im Herzen von Nubien ein großes Monument und ein Tempel zu Ehren seiner Regierung errichtet werden sollen. Pharao selbst hat den perfekten Platz für diese Bauwerke ausgewählt. Von den rosafarbenen Sandsteinfelsen über dem Westufer des Nils bei Abu Simbel aus können Sie die Steinmetzarbeiten an vier massiven Statuen seiner Majestät verfolgen. Die Oberflächen des Monuments, die aus dem lebendigen Stein herausgehauen werden, verkünden die heldenhaften Taten des Pharao während seines großen Triumphs in der Schlacht bei Kadesch. Dieses massive Monument dient neben der Verkündung der Heldentaten unseres Herrschers dem nubischen Volk aber auch als stete Erinnerung an die Größe und Macht Ägyptens, denn Nubien ist zwar reich an Goldvorkommen und seltenen Edelsteinen, seine Bewohner jedoch haben sich nie damit abgefunden, unter ägyptischer Herrschaft zu stehen. Aus diesem Grund sollten Sie immer bereit sein, sich zu verteidigen und auch Truppen zu entsenden, sollte Pharao Soldaten benötigen. @PSandstein kann exportiert werden, um an anderen Orten des Königreichs als Baumaterial zu dienen. Für den Export eignen sich aber auch andere Güter, die Sie aufgrund der reichhaltigen Ressourcen der Region produzieren können. Holz ist allerdings nur sehr wenig zu finden. Sie werden wohl eine Handelsroute für den Import dieses Materials einrichten müssen, da es für die Gerüste an diesem riesigen Bauvorhaben benötigt wird."
        }
    }
    message_mission_ramses_valley {
        id: 453,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Eine unübertroffene Ruhestätte",
            pos [10, 30]
        }
        content {
            text: "@PLange und ruhmreiche Jahre liegen hinter uns, seit unser Pharao, der hochverehrte Ramses II., Stab und Wedel von seinem Vater Seti I. übernommen hat. Mit Res Segen wird er noch viele weitere Jahre regieren. Trotzdem ist es nun an der Zeit, in die Tiefen der Erde vorzudringen und die ewige Ruhestätte für unseren erlauchten Herrscher vorzubereiten. Er hat dem Architekten der Grabstätte einen Plan für das größte Grab aller Zeiten übergeben, das sogar das Grab seines Vater noch übertrifft. Es liegt nun an Ihnen, diese königliche Forderung zu einem erfolgreichen Abschluss zu bringen. @PDoch hier noch ein Wort der Warnung! Sowohl hier als auch in Unterägypten hat die Unruhe unter frei denkenden Arbeitern und Sklaven Besorgnis erregende Formen angenommen. Sie folgen einem Mann, der einst am Hofe unseres Pharao aufgewachsen ist, und haben damit gedroht, ihren Gott um göttliche Hilfe zu bitten. Sie hoffen, dass sie mit solcher Unterstützung ihren Willen bekommen. In diesem Moment debattieren Priester und heilige Männer darüber, ob diese Bedrohung ernst zu nehmen ist. Während wir nun geduldig auf ihre Entscheidung warten, wäre es vielleicht durchaus ratsam, sich auf unerwartete Dinge vorzubereiten."
        }
    }
    message_mission_pi_yer_2 {
        id: 454,
        type: 3,
        size [40, 30]
        title {
            text: "Pi-Yer",
            pos [50, 80]
        }
        subtitle {
            text: "Das Land des Seevolks",
            pos [10, 30]
        }
        content {
            text: "@PDie Nachrichten über Unzufriedenheit und Unruhe im Westen haben in letzter Zeit immer beunruhigendere Formen angenommen. Späher berichten, dass einige fremdartig sprechende Barbarenstämme an den Küsten von Kyrenaica westlich von uns gelandet sind. Als wäre dies nicht schon schlimm genug, stehen diese Menschen auch noch auf Seiten von Maraye, dem Sohn des Did, König der Libyer und Feind des Pharao.  @PPharao Merneptah ist zu Ohren gekommen, dass sich diese ungehobelten Barbaren, mit ihren Frauen, Kindern und weltlichen Besitztümern im Schlepptau, bald nach Osten wenden werden. Auf der Suche nach einem Ort, an dem sie sich ansiedeln können, ziehen sie in Richtung des fruchtbaren Nildeltas - unseres Heimatlandes!Bei den nördlichen Oasen Siwa und Farafra hat es bereits kleinere Zwischenfälle gegeben. Jetzt liegt Pi-Yer vor ihnen, Ihre Stadt im Delta. Dieser langsam vorrückende Haufen von Barbaren könnte schon bald vor unseren Türen stehen. Der Pharao hat befohlen, dass sie keinesfalls weiter vordringen dürfen, sollten sie es tatsächlich bis hierher schaffen. @PSie werden Holz für den Bau stabiler Kriegsschiffe und Kupfer für Waffen importieren müssen. Was für ein Glück, dass die früher so lästigen Hethiter dank des großen Sieges bei Kadesch durch Ramses II., dem Vater unserer geliebten Merneptah, momentan friedlich sind. Befestigen Sie Ihre Stadt, und bereiten Sie Ihre treuen Truppen auf einen Kampf auf Leben und Tod vor."
        }
    }
    message_mission_pelusium {
        id: 455,
        type: 3,
        size [40, 30]
        title {
            text: "Pelusium",
            pos [50, 80]
        }
        subtitle {
            text: "Abwehr der Assyrer",
            pos [10, 30]
        }
        content {
            text: "@PSeit den Tagen des großen Schabaka, dem Einiger von Ober- und Unterägypten und Vater Pharao Taharqas, waren Konflikte mit den aggressiven Assyrern an der Tagesordnung. Als er noch lebte befand Pharao Schabaka es für angemessen, unseren Brüdern in Palästina zu helfen, die sehr unter der strengen Herrschaft Assyriens zu leiden hatten. Aber Vorsicht! Die Bluthunde des barbarischen Königs Asarhaddon marschieren wieder und haben erneut ein Auge auf den fruchtbaren Boden Ägyptens geworfen. Jetzt können Sie Ruhm und Ehre erringen! Von Ihnen als Königlichem Bürgermeister von Pelusium wird erwartet, dass Sie die Angriffe dieser verfluchten Feinde zurückschlagen. Ihre Grenzfestung am östlichen Rand des Nildeltas bildet die Frontlinie von Ägyptens äußerem Verteidigungsring. @PEs ist wichtig, dass Sie Ihre Soldaten ordentlich ausbilden und neue Handelsverbindungen knüpfen, um die Lieferung von Waffen oder Rohstoffen zur Herstellung von eigenen Waffen zu gewährleisten. @PZeigen Sie keine Schwäche! Ein starkes Militär ist unabdingbar, um die Unabhängigkeit Ägyptens zu sichern. Wenn Sie nur sieben Jahre lang durchhalten, ist der Sieg Ihnen sicher. Taharqa, der große Pharao, zweiter Sohn von Schabaka, wird Sie im Auge behalten!"
        }
    }
    message_mission_tanis_2 {
        id: 456,
        type: 3,
        size [40, 30]
        title {
            text: "Tanis",
            pos [50, 80]
        }
        subtitle {
            text: "Die Wiedergeburt einer Seestreitmacht",
            pos [10, 30]
        }
        content {
            text: "@PViele Generationen von Ägyptern litten unter der grausamen Faust Persiens. Babylons Einfluss auf unser gesegnetes Land ist jedoch nicht so stark wie er früher einmal war. Während unsere verfluchten Unterdrücker damit beschäftigt waren, sich in die Politik Griechenlands einzumischen, ist es Ägypten durch eine ganze Reihe von Aufständen gelungen, den Würgegriff der verhassten Perser zu lockern. Nun allerdings ist Pharao Achoris zu Ohren gekommen, dass sich eine Streitmacht, ausgesandt von Artaxerxes II. und befehligt von Flottenadmiral Conon (einem griechischen Lakaien, der mit persischem Gold bezahlt wird), auf unsere Küsten zubewegt. Pharao Achoris hat in seiner Weisheit beschlossen, dass eine starke Flottenpräsenz auf dem Nil notwendig sei, um den Einfall zu verhindern. Als Königlicher Gouverneur von Tanis müssen Sie in den nächsten zehn Jahren massive Schiffe bauen und schlagkräftige Truppen ausbilden, um den Angriff zu Wasser und zu Lande abzuwehren. @PSie werden eine Handelsroute nach Enkomi einrichten und von dort Holz für den Bau Ihrer Flotte importieren müssen. Kupfer bekommen Sie ebenfalls aus Enkomi, das auf der Insel Zypern liegt. Diese Handelsroute ist jedoch stets äußerst gefährdet, da sie in der Nähe der levantinischen Küste verläuft, die von unseren Feinden kontrolliert wird. Wenn Sie den Pharao mit allem versorgen, was er benötigt, wird auch Ihr Einkommen steigen.  @PVergessen Sie nicht, dass die Stadtkassen in diesen unruhigen Zeiten nicht gerade voll sind. Sie müssen als Händler genauso geschickt sein wie als tüchtiger Kommandeur."
        }
    }
    message_mission_alexandria {
        id: 457,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria",
            pos [50, 80]
        }
        subtitle {
            text: "Alexander der Große",
            pos [10, 30]
        }
        content {
            text: "@PDer große Alexander, Sohn von Philipp II. von Mazedonien und Geißel des babylonischen Reiches, beglückt Ägypten durch die Gnade seiner Anwesenheit. Bei seiner Ankunft hat der letzte korrupte persische Satrap fluchtartig das Feld geräumt. Alexander wurde nach seinem Opfer an den Apis-Stier in Memphis zum Pharao erklärt. Alle Menschen jubeln! Bevor er sich jedoch auf die Reise zum Orakel des Amun in der Oase Siwa begab, befahl unser Anführer die Gründung einer neuen Stadt. Einer Stadt, die nach seinem Wunsch einmal zur Hauptstadt dieses riesigen und wachsenden Imperiums werden soll. In seiner unendlichen Weisheit hat er Sie zum ersten Bürgermeister dieser zukünftigen Stadt bestimmt! @PDer große Alexander hat Ihnen eine großzügige Geldspende als Grundlage für das Bauvorhaben zukommen lassen und stellt den berühmten griechischen Architekten Dinokrates in Ihre Dienste. Er erwartet von Ihnen, dass Sie die wirtschaftliche, kulturelle und militärische Stärke dieser Stadt auf einen hohen Stand gebracht haben, wenn er in zwölf Jahren wieder zurückzukehren gedenkt.  @PUnser Anführer hat sich sogar herabgelassen, die Positionen der beiden Hauptdurchgangsstraßen dieser Stadt festzulegen. Die Kanopen-Straße verläuft entlang einer Ost-West-Achse, während die andere Hauptstraße im rechten Winkel dazu verläuft und von Kap Lochias aus südlich zum Mariut-See hinein ins Landesinnere führt. @PAls treuer Aufseher dieses Projektes sollten Sie so schnell es geht Hafenanlagen bauen und lukrative Handelsrouten einrichten. Es sollten sich eigentlich viele Abnehmer für unsere Produkte, insbesondere für Weizen, Gerste, Papyrus und Leinen finden lassen. Vernachlässigen Sie weder die kulturellen noch die militärischen Aspekte dieser Stadt, denn es gibt immer noch herumstreichende Barbaren, die Ägypten seiner Reichtümer berauben wollen."
        }
    }
    message_mission_ptolemy_alexandria_2 {
        id: 458,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria (Ptolemäus)",
            pos [50, 80]
        }
        subtitle {
            text: "Ein strahlendes Licht",
            pos [10, 30]
        }
        content {
            text: "@PDas Erbe von Alexander dem Großen lebt in unserer stolzen Stadt weiter. Seine Stadt hat nicht aufgehört zu wachsen, auch wenn seine sterblichen Überreste schon lange im Mausoleum in Alexandria ruhen. Es liegt nun an Ihnen, Ptolemäus I. Soter, das Werk weiterzuführen, das der edle Alexander begonnen hat. Seit der Gründung der Stadt durch Alexander vor gerade einmal 30 Jahren ist die Stadt zu einem mächtigen Handelsknoten geworden, der große Teile des Umlandes mit den am meisten benötigten Nahrungsmitteln und Luxusgütern versorgt. Sie sollten auf der Insel Pharos in der Nähe der Hafeneinfahrt einen massiven Leuchtturm errichten, damit die vielen Schiffe sicher passieren können und der wirtschaftliche Aufstieg weiter voranschreitet. Das Leuchtsignal dieses Gebäudes wird die sich nähernden Seefahrer sicher in den Hafen leiten und sicherstellen, dass ihre Schiffe auf den tückischen Sandbänken nicht auf Grund laufen. @PSo bedeutsam der Handel auch ist, die kulturelle und intellektuelle Weiterentwicklung unserer Gesellschaft dürfen Sie dennoch nicht aus den Augen verlieren. Unter Ihrer Herrschaft kann Alexandria jetzt zur intellektuellen Hauptstadt der gesamten bekannten Welt werden. Tragen Sie Wissen von nah und fern zusammen, und bauen Sie eine große Bibliothek, in der es bewahrt werden kann. So sicher wie Ameisen von Honig angelockt werden, so sicher reisen dann auch Gelehrte aus aller Welt zu diesem unvergleichlichen Zentrum des Wissens und Lernens.  @PFür den Bau dieser großen Monumente werden Sie Baumaterial wie zum Beispiel weißen Marmor importieren müssen, der für so großartige Gebäude gerade gut genug ist. Enkomi auf der Insel Zypern ist eine gute Quelle für dieses Material.  @PUnd noch eines: Vernachlässigen Sie nicht Ihre Streitkräfte. Irgendwo scheint es immer Unruhen zu geben. Und es könnte durchaus notwendig werden, Truppen an weit entfernte Grenzen zu entsenden, um Ägyptens Interessen zu wahren und seine Ehre zu verteidigen."
        }
    }
    message_mission_maritis_2 {
        id: 459,
        type: 3,
        size [40, 30]
        title {
            text: "Maritis",
            pos [50, 80]
        }
        subtitle {
            text: "Caesar und Kleopatra",
            pos [10, 30]
        }
        content {
            text: "@PDie Habgier des römischen Imperiums wird mit jedem Tag größer und greift immer weiter um sich. Sogar die tödlichen politischen Machtkämpfe Roms haben unser Land erreicht. Nach der Ermordung von Pompeius auf ägyptischem Boden hält Julius Caesar nun die absolute Kontrolle über die mächtigen Legionen Roms in seinen Händen und hat ein Auge auf die Reichtümer Ägyptens geworfen - wie auch auf die betörende Schönheit unserer Pharaonin Kleopatra VII., der Tochter von Ptolemäus XII. Auletes. Unsere kluge Herrscherin ist allerdings im Kampf der Geister nicht so leicht zu besiegen. Sollte Caesar danach trachten, sie als Werkzeug für eine künftige Einflussnahme auf Ägypten zu benutzen, wird sie ihn im Gegenzug zur Wahrung der dynastischen Macht unseres großen Landes zu verwenden wissen. @PCaesars Ankunft in Alexandria in Begleitung seiner äußerst unpopulären Römer entfachte unter den freidenkenden Bürgern einen Aufstand. Ein aufsässiger Mob, angestachelt von Kleopatras jüngerem Bruder Ptolemäus XIII., hat Caesar und seine Männer im königlichen Viertel der Stadt eingekesselt. Erbitterte Straßenkämpfe sind ausgebrochen, die viele Todesopfer forderten. Um sich einen seeseitigen Fluchtweg offen zu halten, ließ Caesar die ägyptische Flotte in Brand setzen, während diese in Alexandrias Hafen vor Anker lag. Unglücklicherweise sprang das Feuer auf einige entlang des Ufers liegende Lagerhäuser über, wodurch Papyrusrollen in großer Zahl verbrannten, die eigentlich für die Große Bibliothek bestimmt waren.  @PUm der Falle zu entkommen, in der er sich jetzt befindet, hat Caesar den ihm loyal ergebenen Mithradates und dessen Truppen aus Syrien herbeigerufen. Nach der erfolgreichen Erstürmung der Grenzfestung Pelusium hat Mithradates seine Männer in einem Gewaltmarsch um das Nildelta herumgeführt, um sich Alexandria von Südosten zu nähern. Die Vorhut dieser Streitmacht lagert zurzeit in der Umgebung des Dorfes Maritis am östlichen Ufer des Sees Mariut und bereitet sich auf die letzte Etappe ihrer Reise vor.  @PPtolemäus XIII. hat vom Herannahen dieser Verstärkung erfahren. Als Antwort darauf setzte er einen Großteil seiner zahlenmäßig überlegenen Armee von Alexandria aus gen Südosten in Marsch. In Kürze wird eine entscheidende Schlacht am östlichen Ufer des Mariut-Sees stattfinden. Können Sie als Kommandeur der römischen Legionen des Mithradates die aufständische ägyptische Armee unter Ptolemäus besiegen und sich zu Caesar und Kleopatra nach Alexandria durchschlagen? Das Schicksal der beiden liegt in Ihren Händen."
        }
    }
    message_mission_cleopatra_alexandria_2 {
        id: 460,
        type: 3,
        size [40, 30]
        title {
            text: "Alexandria (Kleopatra)",
            pos [50, 80]
        }
        subtitle {
            text: "Das Erbe einer Königin",
            pos [10, 30]
        }
        content {
            text: "@PCaesars grausamer Tod durch die Klingen von Meuchelmördern stürzte die römische Welt in Aufruhr und hat Ihnen, unserer Pharaonin Kleopatra VII., Trauer und Schmerz gebracht. Ihr Geliebter, Mentor, Vertrauter und mächtiger Verbündeter ist nicht mehr. Sein gerade den Kinderschuhen entwachsener adoptierter Großneffe Octavian wurde zu seinem Erben bestimmt. Der viel erfahrenere Marcus Antonius, ehemals ein Konsul Caesars, jedoch wurde, zum Leidwesen des jungen Octavian, zum formellen Staatsoberhaupt ernannt. Dass euer gemeinsamer Sohn Ptolemäus Caesar, auch 'Caesarion' genannt, in Caesars Testament nicht erwähnt wurde, konnte nicht weiter überraschen. Um Ihr Kind und sich selbst in Sicherheit zu bringen und auch die Macht Ägyptens weiter zu erhalten, haben Sie Rom mit Ziel Alexandria verlassen.  @PDoch trotz der großen räumlichen Entfernung zwischen Ihnen und Rom können Sie die mörderischen Machtkämpfe dort nicht völlig hinter sich lassen. Noch immer gieren mächtige Männer nach Macht - Ihre Unterstützung und der Zugang zu den Reichtümern Ägyptens wären ein großes Plus für jede Partei. Dass Sie in diesem Machtkampf den Sieger unterstützen, ist ungemein wichtig, denn eine Kollaboration mit dem Verlierer könnte leicht das Ende Ägyptens nach sich ziehen. Der dramatische Entscheidungskampf zwischen den rivalisierenden römischen Parteien, in dem Marcus Antonius' Caesarianer den entscheidenden Schlag gegen die Streitkräfte von Brutus und Cassius führten, fand unlängst bei Philippi statt. Antonius, Octavian und Lepidus bilden nun ein Triumvirat, um das Imperium zu lenken, wobei Antonius Anspruch auf den östlichen Teil einschließlich Ägypten erhebt. @PKurz nach dem Kampf befahl Ihnen Marcus Antonius, zu ihm nach Tarsus in Kleinasien zu kommen, um ihm zu erklären, warum es so lange dauerte, bis Sie sich auf die Seite der Caesarianer schlugen. Da Sie sich nicht wie ein Hund herbeizitieren lassen, haben Sie es in Ihrer Weisheit abgelehnt zu antworten. Schließlich wissen Sie besser als jeder andere, dass es sehr viel vorteilhafter ist, einen Römer nach IHREN Vorgaben zu empfangen, als umgekehrt. @PDaher sind Sie, Pharaonin Kleopatra, nach Ägypten und nach Alexandria heimgekehrt. Es ist nun an der Zeit, den Ruhm dieser einzigartigen Stadt des großen Alexander, dessen Grab noch heute Scharen von Pilgern besuchen, zu neuer Größe zu führen. Alexandrias berühmte Große Bibliothek zieht immer noch Gelehrte aus aller Welt an; das helle Leuchtsignal des wunderbaren Leuchtturms von Pharos weist immer noch den Weg, damit die Seefahrer sicher durch die tückischen Wasser des Hafens gelangen können. Sie können nun die Schönheit der Stadt durch den Bau des weitläufigen Caesareums zu Ehren Ihres ehemaligen Geliebten und Ihres kleinen Sohnes noch weiter bereichern. Darüber hinaus sichern Sie Ihren eigenen Übergang zum ewigen Leben durch den Bau eines weiteren Mausoleums, sodass Ihnen auch nach Ihrer Reise zu den Feldern des Schilfs gebührend gehuldigt werden kann.  @POb Marcus Antonius das nächste Mal wohl etwas mehr Takt walten lässt, wenn er nach Ihnen ruft?"
        }
    }
    message_mission_actium_2 {
        id: 461,
        type: 3,
        size [40, 30]
        title {
            text: "Actium",
            pos [50, 80]
        }
        subtitle {
            text: "Antonius und Kleopatra",
            pos [10, 30]
        }
        content {
            text: "@POh edle Pharaonin Kleopatra VII., Gefährtin des Caesar und nun des Antonius, Ägyptens Geschick liegt in Ihren Händen, aber diese ruhen jetzt in denen eines Römers, Marcus Antonius - und der ist tief in den Kampf um die Macht in Rom und dessen Legionen verstrickt.  @PDa Marcus Antonius Ägyptens unermessliche Rohstoffe brauchte, aber auch Ihre Liebe und Zuneigung wünschte, willigte er in eine Hochzeit mit Ihnen ein. Unglücklicherweise hat die Nachricht von dieser neuen Verbindung in Rom einen Skandal ausgelöst! Wie Sie wissen, war Marcus Antonius noch immer mit Octavia, der Schwester von Caesars gesetzmäßigem Nachfolger Octavian, vermählt, mit dem zusammen er die Herrschaft über Rom ausübte. Diese Beziehung steht nun durch die offensichtliche Bigamie des Marcus Antonius vor einer schweren Zerreißprobe. Octavian ist der Ansicht, dass Marcus Antonius nicht nur die Ehre seiner Schwester und seiner Familie in den Schmutz gezogen, sondern auch das Ansehen Roms beschädigt hat. Um die Ehre wiederherzustellen und den Streit um die absolute Macht über Rom zu beenden, forderte Octavian Ihren Geliebten Marcus Antonius zu einem Kampf heraus. Aus diesem Grund entschied sich Marcus Antonius, der von Ihnen und Ihrer ägyptischen Flotte begleitet wird, für einen Ort auf dem griechischen Festland in der Nähe von Actium, um dort sein Lager aufzuschlagen. Diese Stelle bietet einen guten Hafen mit vielen möglichen Liegeplätzen für Ihre Schiffe.  @PSie müssen nun schnellstens eine Streitmacht und vor allem eine Flotte aufbauen. Octavian hat geschworen, im September des Jahres 31 zurückzukehren. @PNun hängt Ihr Schicksal und das von Marcus Antonius, aber auch die Zukunft Ägyptens und Roms einmal mehr davon ab, wie sich die militärischen Streitkräfte bewähren."
        }
    }
    message_mission_deir_el_medina {
        id: 462,
        type: 3,
        size [40, 30]
        title {
            text: "Deir el-Medina",
            pos [50, 80]
        }
        subtitle {
            text: "Das erste Grab",
            pos [10, 30]
        }
        content {
            text: "@PNach vielen brillanten Siegen auf weit entfernten Schlachtfeldern, die die Sicherheit des Landes und der Bewohner Ägyptens garantieren, denkt Pharao Thutmosis nun über die Vorbereitungen für seine Reise ins Jenseits nach. Um sicherzustellen, dass seine Reise erfolgreich verläuft, wünscht der Pharao, dass Sie so bald wie möglich mit dem Bau seines Grabes beginnen. Errichten Sie ein Dorf am Westufer des Nils, um tüchtige Arbeiter in Reichweite zu haben. Suchen Sie westlich des Dorfs in den Felsen nach einer passenden Stelle für das Grab. Sie werden geschickte Steinmetze benötigen, um die vielen Kammern des Grabes aus dem Stein zu hauen, sowie talentierte Kunsthandwerker, die die Räume verputzen und bemalen.  @PDamit die Arbeiter auch an den tiefsten Stellen des Grabes genügend Licht haben, müssen Sie Lampenwerkstätten errichten. Statten Sie die Lampenwerkstätten mit Töpferwaren und importiertem Öl als Brennstoff aus. Bauen Sie Henna auf Feldern an, um den Rohstoff für die leuchtenden Farben zu erzeugen, die die Farbenmacher benötigen werden."
        }
    }
    message_mission_tutankhamun_valley_2 {
        id: 463,
        type: 3,
        size [40, 30]
        title {
            text: "Tut im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Tut-ench-Amuns Tod",
            pos [10, 30]
        }
        content {
            text: "@PEin furchtbares Unglück ist über unseren geliebten jungen Pharao Tut-ench-Amun hereingebrochen! Seine Herrschaft, die einst so viel Ruhm versprach, wurde durch die Hand des Schicksals erbarmungslos und viel zu früh beendet. Es ist nun an der Zeit, dass die Arbeiter in Deir el-Medina wieder einen Platz der ewigen Ruhe für den Pharao vorbereiten. Sein unvorhersehbarer früher Tod zwingt Sie, Ihre Arbeiter aufs Äußerste anzutreiben. Es stehen Ihnen nur wenige Jahre zur Verfügung, um Tut-ench-Amuns Grab so weit fertigzustellen, dass es mit allen nötigen Gütern für die Reise ins Jenseits ausgestattet ist und die geheiligten Überreste aufnehmen kann. Arbeiten Sie so schnell es irgend geht!"
        }
    }
    message_mission_seti_valley_2 {
        id: 464,
        type: 3,
        size [40, 30]
        title {
            text: "Seti im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Ein Grab für einen Pharao",
            pos [10, 30]
        }
        content {
            text: "@PUnser mächtiger Pharao Seti, Sohn von Ramses I., hat verkündet, dass der richtige Zeitpunkt für den Beginn der Vorbereitungen für seine Reise ins Jenseits gekommen sei. Daher werden Sie im Tal der Könige mit den Ausschachtarbeiten für sein königliches Grab beginnen. Bei diesem Vorhaben müssen Sie Ihren Arbeitern die größten Anstrengungen abverlangen. Es müssen geeignete Vorkehrungen getroffen werden, um sicherzustellen, dass nach der Vollendung die bauliche Meisterleistung auf lange Sicht unerreicht bleiben wird. @PPlanen Sie beim Bau dieses königlichen Projektes unbedingt strikte Schutzmaßnahmen gegen Banditen mit ein! Es hat bereits Berichte über Banden gieriger Verbrecher gegeben, die sich durch Plünderung der Grabkammern bereichern wollen und dabei den Frieden der in Ewigkeit ruhenden Pharaonen stören. Lassen Sie nicht zu, dass diese gottlosen Taten die königlichen Gräber im Tal der Könige entweihen, sonst wird, so sicher wie die Sonne im Osten aufgeht, auch Ihre Stellung im Königreich darunter leiden."
        }
    }
    message_mission_sumur_2 {
        id: 465,
        type: 3,
        size [40, 30]
        title {
            text: "Sumur",
            pos [50, 80]
        }
        subtitle {
            text: "Land der Levante",
            pos [10, 30]
        }
        content {
            text: "@PSeien Sie gegrüßt, königlicher Gouverneur, Herrscher über die Levante und ergebener Untertan unseres Pharao, Sohn des Ra. Sie können sich wirklich glücklich schätzen, in dieser Zeit zu leben, in der sich die wohlwollende Hand Ägyptens von Nubien bis weit zu den levantinischen Küsten erstreckt. Unendlich ist die Weisheit unseres neuen Pharao, des hochverehrten Ramses II., und groß ist seine Vision, denn er hat Ihnen die Gnade erwiesen, in diesem herrlichen Land zu regieren, das nun Teil des ständig wachsenden ägyptischen Reiches ist.  @PDiese Region besitzt, auch wenn hier noch immer zahlreiche Gefahren drohen, viele Reichtümer, die ihrer Ausbeutung harren. Auf den grünen Hügeln wachsen hohe Bäume, aus denen bestes Holz für die Herstellung von Streitwagen und vielen anderen Dingen gewonnen werden kann. Kupferadern sind zwar relativ selten, aber dennoch zu finden, und werden zur Herstellung von starken Waffen benötigt. Holz und Kupfer, also Dinge, die in unserem Heimatland sehr selten sind, werden mit Sicherheit hochwillkommen sein, wenn sie in großen Mengen in die Heimat geschickt werden. Deshalb wurden Sie mit der Aufgabe betraut, die Errichtung eines großen Handelshafens zu beaufsichtigen, von dem aus diese wertvollen Güter exportiert werden können. Pharao und das ägyptische Volk werden Ihnen sehr dankbar sein! @PAber Vorsicht! Achten Sie darauf, dass Ihre eigenen vertrauenswürdigen Soldaten mit schnellen Streitwagen und starken Waffen ausgerüstet sind, denn die Hethiter sind noch immer gefährlich, auch wenn sie von Seti, dem Vater des Pharao, besiegt wurden. Sie könnten Ihre rechtmäßige Autorität in diesem reichen Land anfechten. Daher wird sich vermutlich eine starke militärische Präsenz in diesem neuen Territorium als notwendig erweisen, um Aufstände zu verhindern, und auch in der Zukunft dürfte sie sicherlich äußerst nützlich sein. @PZu guter Letzt betrachtet es Pharao Ramses II. als angemessen, wenn Sie einen Obelisken zum Zeichen seines Ruhmes errichten, damit die Bewohner dieser Region nicht vergessen, wem sie jetzt ihren Respekt zollen müssen."
        }
    }
    message_mission_qadesh_2 {
        id: 466,
        type: 3,
        size [40, 30]
        title {
            text: "Kadesch",
            pos [50, 80]
        }
        subtitle {
            text: "Die Schlacht von Kadesch",
            pos [10, 30]
        }
        content {
            text: "@PAmurra an der levantinischen Küste erzittert unter den Hufen Ihrer Furcht erregenden Kavallerie und den Füßen Ihrer mächtigen Legionen, gesegneter Pharao. Diese Region ist nicht nur reich an Edelsteinen, noch reicher ist sie an Zwietracht. Bewaffnete Hethiter unter der Führung des erbärmlichen Königs Muwatallis trachten erneut nach der Herrschaft über dieses Land, das rechtmäßig uns gehört. Gefangen genommene Spione berichten davon, dass seine feindlichen Banden sich noch weit im Norden aufhalten und daher keine Bedrohung darstellen. Aber kann man dem Glauben schenken? Weise ist der Krieger, der seinen Schild im Kampf nicht fallen lässt.  @PUm Gerüchte über Aufstände im Keim zu ersticken, sind Sie, unser hochverehrter Pharao Ramses II., Sohn des Ra, in der Festungsstadt Kadesch eingetroffen. In der Umgebung haben bereits zwei unserer gefürchteten Streitwagenkompanien ihre Lager aufgeschlagen. Aber das ist nicht alles. Andere Veteranenkompanien, darunter die erfahrenen Truppen, die vor kurzem erst in der Nähe von Sumur gekämpft haben, stehen ebenfalls zu Ihrer Verfügung. Doch Vorsicht! Sie wären gut beraten, die wertvollen Truppen erst einzusetzen, wenn sie wirklich gebraucht werden. Denn weise ist auch der Krieger, der gute Truppen in Reserve hält, um sie auf dem Höhepunkt des Gefechtes in die Schlacht zu schicken. @PNachdem der elende Feind vernichtet ist, wird es notwendig sein, die stagnierende Wirtschaft von Kadesch wieder zu beleben, damit auch diese Stadt zum Ruhme Ägyptens beitragen kann. Tragen Sie wertvolle Edelsteine zusammen, und stellen Sie fähige Juweliere ein, die daraus exquisite Güter für die treuen Untertanen des Pharao fertigen. Luxusgüter von solch seltener Schönheit werden mit Sicherheit sehr gefragt sein!"
        }
    }
    message_mission_abu_simbel_2 {
        id: 467,
        type: 3,
        size [40, 30]
        title {
            text: "Abu Simbel",
            pos [50, 80]
        }
        subtitle {
            text: "Die Felsentempel von Abu Simbel",
            pos [10, 30]
        }
        content {
            text: "@PDer Ruhm unseres Pharao Ramses II. erfüllt das Land. Damit seine Herrschaft auf ewig lebendig bleiben möge, wurde beschlossen, dass im Herzen von Nubien ein großes Monument und ein Tempel zu Ehren seiner Regierung errichtet werden sollen. Pharao selbst hat den perfekten Platz für diese Bauwerke ausgewählt. Von den rosafarbenen Sandsteinfelsen über dem Westufer des Nils bei Abu Simbel aus können Sie die Steinmetzarbeiten an vier massiven Statuen seiner Majestät verfolgen. Die Oberflächen des Monuments, die aus dem lebendigen Stein herausgehauen werden, verkünden die heldenhaften Taten des Pharao während seines großen Triumphs in der Schlacht bei Kadesch. Dieses massive Monument dient neben der Verkündung der Heldentaten unseres Herrschers dem nubischen Volk aber auch als stete Erinnerung an die Größe und Macht Ägyptens, denn Nubien ist zwar reich an Goldvorkommen und seltenen Edelsteinen, seine Bewohner jedoch haben sich nie damit abgefunden, unter ägyptischer Herrschaft zu stehen. Aus diesem Grund sollten Sie immer bereit sein, sich zu verteidigen und auch Truppen zu entsenden, sollte Pharao Soldaten benötigen. @PSandstein kann exportiert werden, um an anderen Orten des Königreichs als Baumaterial zu dienen. Für den Export eignen sich aber auch andere Güter, die Sie aufgrund der reichhaltigen Ressourcen der Region produzieren können. Holz ist allerdings nur sehr wenig zu finden. Sie werden wohl eine Handelsroute für den Import dieses Materials einrichten müssen, da es für die Gerüste an diesem riesigen Bauvorhaben benötigt wird."
        }
    }
    message_mission_ramses_valley_2 {
        id: 468,
        type: 3,
        size [40, 30]
        title {
            text: "Ramses im Tal",
            pos [50, 80]
        }
        subtitle {
            text: "Eine unübertroffene Ruhestätte",
            pos [10, 30]
        }
        content {
            text: "@PLange und ruhmreiche Jahre liegen hinter uns, seit unser Pharao, der hochverehrte Ramses II., Stab und Wedel von seinem Vater Seti I. übernommen hat. Mit Res Segen wird er noch viele weitere Jahre regieren. Trotzdem ist es nun an der Zeit, in die Tiefen der Erde vorzudringen und die ewige Ruhestätte für unseren erlauchten Herrscher vorzubereiten. Er hat dem Architekten der Grabstätte einen Plan für das größte Grab aller Zeiten übergeben, das sogar das Grab seines Vater noch übertrifft. Es liegt nun an Ihnen, diese königliche Forderung zu einem erfolgreichen Abschluss zu bringen. @PDoch hier noch ein Wort der Warnung! Sowohl hier als auch in Unterägypten hat die Unruhe unter frei denkenden Arbeitern und Sklaven Besorgnis erregende Formen angenommen. Sie folgen einem Mann, der einst am Hofe unseres Pharao aufgewachsen ist, und haben damit gedroht, ihren Gott um göttliche Hilfe zu bitten. Sie hoffen, dass sie mit solcher Unterstützung ihren Willen bekommen. In diesem Moment debattieren Priester und heilige Männer darüber, ob diese Bedrohung ernst zu nehmen ist. Während wir nun geduldig auf ihre Entscheidung warten, wäre es vielleicht durchaus ratsam, sich auf unerwartete Dinge vorzubereiten."
        }
    }
    message_mission_henna {
        id: 469,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Seit mehr als dreitausend Jahren haben Menschen Hennapflanzen als Rohstoff für die Herstellung von Farben genutzt. Henna (botanische Bezeichnung: Lawsonia inermis) gehört zur Familie der Lythraceae und stammt ursprünglich aus Nordafrika und dem Mittleren Osten. Wenn die Pflanze zerstampft wird, tritt aus den Blättern und Stängeln eine orangerote Farbe aus, die sich bei richtiger Anwendung hervorragend als Färbemittel für Haare, Fingernägel und Haut eignet. Auch heute noch wird Henna bei vielen religiösen Ritualen und Bestattungsriten in Asien, dem Mittleren Osten und Afrika verwendet und bildet die Grundlage der Farbstoffe für die populären 'temporären' Tattoos. Henna ist darüber hinaus der Grundwirkstoff bei einer großen Anzahl von Haarfärbemitteln."
        }
    }
    message_mission_paint_maker {
        id: 470,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Farbmühle",
        }
        content {
            text: "Die Farbenmacher der Farbmühlen benötigen @469Henna, um Farbe herzustellen. Die zerstampften Blätter und Stängel der Hennapflanze werden genutzt, um daraus verschiedene Farbstoffe zu gewinnen, die für die Herstellung von Farben nötig sind. Henna wird auf @91Hennafarmen angebaut oder über eine @47Handelsroute importiert.  @PSobald eine Farbmühle kontinuierlich mit Arbeitern versorgt wird und über Straßenanbindung sowie Hennavorräte verfügt, können Sie zusehen, wie die Farbenmacher im Schweiße ihres Angesichts Farbe herstellen. Wenn die Produktion abgeschlossen ist, wird die Farbe zu einem @4Warenlager gebracht. Die Farbe wird dann von den @363Kunsthandwerkern zur Ausmalung der @478Königlichen&Grabkammern verwendet. @PWegen der unangenehmen Geruchs- und Geräuschentwicklung sind Farbmühlen @56wenig&attraktive&Nachbarn. @L@LKlicken Sie @472hier, um mehr über die Farbenherstellung im alten Ägypten zu erfahren."
        }
    }
    message_illness_video {
        id: 471,
        type: 2,
        pos [0, 88]
        size [30, 20]
        title {
            text: "Krankheit",
        }
        video {
            text: "smk\\sick.smk"
        }
    }
    message_history_artisans {
        id: 472,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1004,
            pos [15, 15]
        }
        title {
            text: "Kunsthandwerk",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Künstler und Kunsthandwerker wurden zwar bei den meisten Gebäuden des alten Ägypten für die Fein- und Abschlussarbeiten herangezogen, an den Gräbern aus der Ära des Neuen Reichs im @475Tal&der&Könige aber wird deutlich, über welche außerordentlichen Fähigkeiten diese Künstler wirklich verfügt haben. Praktisch jeder Quadratzentimeter der Innenwände und Decken dieser unterirdischen Gräber erzählte durch wunderschön gemalte Hieroglyphen und andere Illustrationen von den großen Taten des Verstorbenen. @PAuch wenn die Extravaganz und die Detailgenauigkeit dieser Illustrationen dem zu widersprechen scheinen, aber die Künstler verfügten damals nur über eine ziemlich beschränkte Auswahl an Farben, mit denen sie arbeiten konnten, und sie benutzten Naturpinsel aus @94Schilf oder faserigem Holz, wie z.B. Palmstängeln.  Ihre Pigmente wurden häufig in kleinen Werkstätten vorgemischt. Sie wurden dort aus natürlichen Farbstoffen (wie z.B. @469Henna) und anderen natürlichen Pigmenten (z.B. Kalziumkarbonat, Holzkohle, Eisenoxid, Orpiment, Azurit und Malachit) gewonnen und zu Pulver zerrieben. Danach wurden die Pigmente mit einem Bindemittel vermengt (Pflanzenkleber oder tierischer Leim)und als Farbe benutzt.  @PViele speziell ausgebildete Künstler arbeiteten Hand in Hand an den herrlichen Flachreliefs der Gräber. Zuerst wurde Putz auf die Wände des Grabes aufgebracht, der aus @190Ton, Wasser und einem weißen Farbstoff zusammengemischt wurde. Dann wurde mit roter Farbe eine Rohzeichnung auf den frisch verputzten Wänden angefertigt. Der Hauptzeichner verfeinerte sodann die Umrisse, normalerweise mit schwarzer Farbe. Anschließend führte der Hauptmaler Korrekturarbeiten durch und fügte Details hinzu, an denen sich der nach ihm kommende Basrelief-Bildhauer orientieren konnte. Anschließend wurden die Grundfarben großflächig aufgetragen. Die abschließenden Details (wie Umrandungen und innere Details) wurden dann von anderen Künstlern fertiggestellt."
        }
    }
    message_building_lamp_maker {
        id: 473,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Lampenwerkstatt",
        }
        content {
            text: "Die Lampenwerkstatt produziert Lampen, deren Licht die Arbeiter durch die dunklen Gänge einer @478königlichen&Grabstätte leitet.  @PZur Herstellung von Lampen benötigt eine Lampenwerkstatt Töpferwaren und Öl. Die Töpferwaren sind entweder über eine @1Töpferei oder durch Import über einen @47Handelspartner erhältlich. @476Öl kann nur importiert werden. @PLampenwerkstätten benötigen eine Straßenanbindung und in der Nähe wohnende Arbeiter. Sobald die Lampenwerkstatt ausreichend Töpferwaren und Öl erhalten hat, können Sie die fleißigen Lampenbauer bei der Arbeit beobachten, wie sie Öl in Gefäße füllen, um Lampen herzustellen. @L@LKlicken Sie @474hier, wenn Sie mehr über die Lampen im alten Ägypten wissen möchten. Lampenwerkstätten haben einen negativen Effekt auf die Attraktivität, daher sollten Sie sie nicht in der Nähe Ihrer Wohngebiete einrichten."
        }
    }
    message_history_lamps {
        id: 474,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1003,
            pos [15, 15]
        }
        title {
            text: "Lampen",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Die alten Ägypter stellten kleine Keramiklampen her, die mit natürlichem @476Öl oder ausgelassenem tierischem Fett betrieben werden konnten. Diese Lampen waren die Lichtquellen für die tief im Inneren einer Grabkammer arbeitenden Handwerker."
        }
    }
    message_history_valley_of_the_kings {
        id: 475,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1011,
            pos [15, 15]
        }
        title {
            text: "Das Tal der Könige",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "@PDas Tal der Könige diente fünf Jahrhunderte lang als Nekropole für die Pharaonen, und zwar ca. von 1539 v.Chr. bis 1075 v.Chr. Unter anderem wurden dort Thutmosis I., Tut-ench-Amun und Ramses II. bestattet. Das Tal liegt am Westufer des Nils gegenüber dem Tempelkomplex von Theben. Überragt wird es von El-Kurna, einem fast pyramidenförmigen Berg, der jeden Tag bei Sonnenuntergang von den letzten Strahlen des Re gesegnet wird. Zwischen dem Tal und dem großen Nil befinden sich die königlichen Totentempel, die jenen Pharaonen geweiht waren, die in ihren Gräbern im Tal ihr Leben im Jenseits genießen wollten. Im angrenzenden Dorf Deir el-Medina lebten hunderte von Arbeitern mit ihren Familien. @PDie Arbeiter bereiteten die königlichen Grabkammern vor und waren allesamt Spezialisten auf ihrem besonderen Gebiet. Steinmetze schlugen Stufen und Gänge in die Kalksteinwände. Dabei ließen sie steinerne Säulen stehen, um die Decken größerer Gewölbe abzustützen. Die Wände der herausgehauenen Räume wurden geglättet und verputzt. Dann kamen die Kunsthandwerker und schmückten Decken und Wände mit Basreliefs und Malereien, die den Pharao auf seinem Weg ins Jenseits leiten sollten. Der verstorbene König wurde in seinen Sarkophag gelegt und in der Grabkammer zusammen mit vielen Reichtümern bestattet, die seinem durch das ägyptische Volk verliehenen göttlichen Status entsprachen. Die Grabkammern wurden wegen der unermesslichen Reichtümer häufig ausgeraubt, oftmals sogar durch die Wächter der Kammern selbst. @PEuropäische Archäologen entdeckten das Tal der Könige im frühen 18. Jahrhundert. 1922 öffnete Howard Carter die versiegelte Grabkammer von Tut-ench-Amun und fand dort viele Schätze sowie einen goldenen Sarkophag vor. Im Lauf der Jahrhunderte wurden viele Gräber nach Überschwemmungen durch Schlamm und Geröll verschüttet. Es ist anzunehmen, dass im Tal noch weitere Gänge und vielleicht sogar Grabkammern existieren, die bis heute unentdeckt geblieben sind."
        }
    }
    message_history_oil {
        id: 476,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1009,
            pos [15, 15]
        }
        title {
            text: "Öl",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Der größte Teil des von den alten Ägyptern verwendeten Öls stammte aus Griechenland, Zypern und Phönizien. Es gab viele Einsatzmöglichkeiten für natürliche Öle, zum Beispiel beim Kochen oder als Brennstoff für @474Lampen. Öle wurden aus verschiedenen Rohstoffen (beispielsweise Sesam, Leinsamen, Oliven und tierischen Fetten) gewonnen, von denen viele auch heute noch verwendet werden."
        }
    }
    message_figure_tomb_robber {
        id: 477,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Grabräuber",
        }
        content {
            text: "@PWo ein Grab ist, da gibt es auch Schätze! Grabräuber gehören zu einer besonderen Art von Verbrechern, die immer dann auftritt, wenn die @39Stimmung&in&der&Stadt besonders schlecht ist. Allerdings sieht man sie nur dann, wenn es Schätze zu plündern gibt. Wenn es in Ihrer Stadt keine Gräber (wie z.B. Pyramiden, @371Mastabas, @368Mausoleen oder @478königliche&Grabstätten) gibt, werden sie sich für Ihre Stadt nicht interessieren. Sie werden Ihre Stadt auch dann verschonen, wenn es keine @374Grabbeigaben gibt, weil diese entweder noch nicht ausgeliefert wurden oder für das Grab keine Beigaben erforderlich sind. @PManchmal schlagen Grabräuber auch zu, wenn in der Stadt keine Anzeichen für Kriminalität zu finden sind. Wenn professionelle Grabräuber von ihren Informanten hören, dass es in den Gräbern Ihrer Stadt besonders wertvolle Beigaben gibt, wird damit eine wahre Verbrechenswelle ausgelöst. Wann jedoch eine solche Welle des Verbrechens über Sie hereinbricht, das ist für Sie nicht vorhersehbar. @PAlle Grabräuber haben nur ein Ziel vor Augen: die Plünderung aller Reichtümer und Schätze eines in der Ewigkeit ruhenden Pharao, die ihm für das Leben nach dem Tod mitgegeben wurden. Der Grabräuber muss sich dabei Zugang zu der königlichen Grabkammer verschaffen, ohne entdeckt zu werden. Falls er auf seinem Weg in die Grabkammer auf einen Polizeibeamten oder Soldaten stößt, wird er im Allgemeinen still und wirkungsvoll 'aufgehalten'. Besonders geschickten Dieben gelingt allerdings manchmal doch die Flucht. Ist es einem Grabräuber gelungen, in ein Grab einzudringen, schleicht er sich mit den erst vor kurzem eingelagerten Grabbeigaben davon, was Ihre @35Königreich-Wertung negativ beeinflusst. Wer will schon von einer Person regiert werden, die nicht in der Lage ist, die Unantastbarkeit der Gräber ihrer Ahnen zu gewährleisten? @PGrabräuber sind bezüglich der Gräber nicht wählerisch. Sie rauben auch Monumente aus, die schon vor Ihrer Regierungszeit in der Stadt existierten. Glücklicherweise sind diese alten Gräber gut verschlossen, und Grabräuber werden es nicht schaffen, Grabbeigaben daraus zu entwenden. Dennoch werden die Ägypter so erstaunt darüber sein, dass eines der ältesten Gräber in Gefahr war, dass Ihre Königreich-Wertung ziemlich in den Keller gehen wird. @PVorsicht! Sollte es einem Grabräuber gelingen, Grabbeigaben zu stehlen, müssen Sie jeden entwendeten Gegenstand ersetzen, bevor die Mission erfolgreich abgeschlossen werden kann. @PWenn Sie mehr zum Thema Kriminalität in Ihrer Stadt wissen möchten, klicken Sie @36hier. @L@LWenn Sie mehr über die Gräber im Tal der Könige erfahren möchten, klicken Sie @475hier."
        }
    }
    message_building_royal_burial_tomb {
        id: 478,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Königliche Grabstätte",
        }
        content {
            text: "@PMit Beginn der Zeitrechnung des Neuen Reichs bestatteten die alten Ägypter ihre Pharaonen und anderen Würdenträger in immer schöner ausgearbeiteten Grabkammern, die in das Gestein eines nahezu unerreichbaren Tales geschlagen wurden. @PBevor die Arbeiten an einer königlichen Grabstätte beginnen können, muss erst einmal eine passende Stelle dafür gefunden werden. Wählen Sie dazu unter 'Religiöse Einrichtungen: Monument' die Option '[Größe] - Königliche Grabstätte' an. Ein großer Grundriss erscheint. Der größte Teil des Monuments muss, mit Ausnahme des seitlich herausragenden kleinen Eingangsbereichs, in Felswände hineingebaut werden. Verschieben Sie den Grundriss des Gebäudes auf dem Felsterrain, bis eine passende Stelle gefunden ist. Wenn der Grundriss komplett grün wird, wissen Sie, dass Sie einen passenden Bauplatz gefunden haben. Rote Bereiche innerhalb des Grundrisses zeigen an, dass die Stelle für den Bau des Monumentes nicht geeignet ist. @PMöglicherweise ist es für Sie einfacher, eine geeignete Stelle für die königliche Grabkammer zu finden, wenn Sie die Felsen vorübergehend verbergen. Drücken Sie dazu einfach die H-Taste, oder wählen Sie in der Liste der @18Spezialkarten die Option 'Felsen verbergen' an. Wenn Sie die Felswände wieder in ihrer ursprünglichen Gestalt sehen möchten, drücken Sie erneut die H-Taste oder wählen in der Spezialkartenliste die Option 'Normal' an. Bei besonders großen Gräbern kann Ihnen auch die M-Taste helfen. Durch Drücken der M-Taste wird der Grundriss an der aktuellen Stelle fixiert, und Sie können Ihren Blickwinkel wechseln, um zu überprüfen, ob der gewählte Platz geeignet ist. Ist dies der Fall, klicken Sie mit der linken Maustaste, um das Monument zu platzieren. Falls der Bauplatz nicht geeignet ist, drücken Sie erneut die M-Taste, um den Grundriss wieder bewegen und nach einer anderen Stelle suchen zu können. @PSobald ein Bauplatz ausgewählt ist, muss eine Ladung Lampen zum Grab geliefert werden, bevor mit der Arbeit begonnen werden kann. Lampen werden in einer @473Lampenwerkstatt hergestellt und können auch über einen @47Handelspartner importiert werden. Wenn in einem @4Warenlager 400 Lampen vorrätig sind, zieht ein Arbeiter einen mit Lampen beladenen Schlitten zur Baustelle. @PNachdem die Lampen zur Ausleuchtung des Weges eingetroffen sind, schlagen die @363Steinmetze die vielen Kammern des Grabes roh aus dem harten Gestein. Wenn die Steinmetze ihre Arbeit an einer Kammer abgeschlossen haben, werden die @363Kunsthandwerker mit dem Verputzen und Bemalen der Wände beauftragt. Diese Kunsthandwerker müssen mit @92Ton für den Putz und mit Farbe aus einer @470Farbmühle versorgt werden. Diese Dinge werden entweder durch den Hersteller oder aus einem Warenlager direkt zur Kunsthandwerkergilde geliefert. Wenn Ihre Stadt eine oder gar beide Waren nicht produzieren kann, können Sie sie vielleicht auch @47importieren. @PRechtsklicken Sie auf eine königliche Grabstätte, um sich den Fortschrittsbericht des @369Vorarbeiters&des&Baus anzusehen. @L@LKlicken Sie @475hier, wenn Sie mehr über das Tal der Könige und seine königlichen Gräbstätten erfahren möchten."
        }
    }
    message_building_zoo {
        id: 479,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Zoo",
        }
        content {
            text: "Zoos sind in jeder Stadt eine beliebte Form der @49Unterhaltung. Der Zoo benötigt für die Pflege der Tiere sowohl Straßenanbindung und Arbeitskräfte als auch @89Stroh und @359Wildfleisch für die Fütterung. Stroh ist ein Nebenprodukt, das bei der Ernte auf Getreidefarmen abfällt, und die Jäger des Jagdhofs können Wildfleisch beschaffen. Es ist auch möglich, eine @47Handelsroute einzurichten, um diese Dinge zu importieren. @PStatten Sie dem @280Aufseher&der&Unterhaltung einen Besuch ab, um festzustellen, wie viele Zoos es in Ihrer Stadt gibt. Benutzen Sie die 'Spezialkarte: Unterhaltung', um nachzuprüfen, wie viele Häuser Zugang zum Zoo haben, und um die Tierpfleger bei ihren Rundgängen durch die Stadt zu beobachten. @PAuch wenn in einem Zoo wunderbare Unterhaltung geboten wird, möchten die Bürger dennoch nicht direkt daneben wohnen, da das Gebrüll und der strenge Geruch einiger Tiere von jedem kultivierten Ägypter als Zumutung empfunden werden. Klicken Sie @56hier, wenn Sie mehr über die Attraktivität eines Gebäudes erfahren möchten. @L@LKlicken Sie @480hier, um mehr über Zoos im alten Ägypten zu erfahren."
        }
    }
    message_history_zoo {
        id: 480,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Die alten Ägypter liebten das Außergewöhnliche und alles, was Spaß machte. Ein Zoo bot beides im Überfluss. Als Ägyptens Macht und Einfluss sich über mehrere Kontinente erstreckte, bekamen die Pharaonen fremdartige und exotische Tiere von Herrschern weit entfernter Länder als Geschenk oder Tribut. Diese Tiere wurden dem Pharao präsentiert und sodann in besonderen zoologischen Gärten untergebracht, die sich zwangsläufig in unmittelbarer Nähe des Herrscherpalastes befanden. Die frühen ägyptischen Zoos dienten in erster Linie der öffentlichen Belustigung und in zweiter Linie dem Studium. Die Große Bibliothek in Alexandria besaß sowohl einen botanischen Garten als auch einen Zoo."
        }
    }
    message_history_alexandria_and_its_library {
        id: 481,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1001,
            pos [15, 15]
        }
        title {
            text: "Alexandria und seine Bibliothek",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Alexander der Große hoffte von Anfang an, dass Alexandria, die Stadt an der Mündung des Nils, die er gegründet und mitgeplant hatte, zu einem Zentrum für Handel und Kultur im Mittelmeerraum werden würde. Weniger als fünfzig Jahre nach ihrer Gründung im Jahr 331 v.Chr. war die ständig wachsende Metropole zu einem weltoffenen Knotenpunkt des Handels geworden, was in gewissem Maße auch der Großen Bibliothek zu verdanken war.  @PSchon bald nach Alexanders überraschendem Tod im Jahr 323 v.Chr. zerfiel sein großes Imperium in drei Hauptregionen. Zu dieser Zeit war Ptolemäus, einer seiner engsten Freunde und fähigsten Generäle, de facto Gouverneur von Ägypten. Er nahm die Zügel dieses alten Landes in die Hand, wurde schließlich Pharao (als Ptolemäus I. Soter) und festigte so die griechische Präsenz in Ägypten, die mit Alexander begonnen hatte. Ptolemäus war es auch, der Alexanders Bestattungsprozession, die auf dem Weg nach Mazedonien war, abfing, die sterblichen Überreste nach Alexandria brachte und dort zur ewigen Ruhe bettete.  @PZur Ehrenrettung der frühen ptolemäischen Herrscher muss gesagt werden, dass sie, abgesehen von ihrem Hang zu persönlichem Ruhm und luxuriösem Leben, auch sehr an der Verbesserung der Kultur ihrer Stadt und des Landes interessiert waren. Alexandria, die neue Hauptstadt Ägyptens, die bereits das Handelszentrum der bekannten Welt war, sollte nach ihrem Willen auch zur intellektuellen Hauptstadt werden. Aus diesem Grund wurde Alexandrias Große Bibliothek geplant und gebaut. Die Große Bibliothek war das erste Bildungs- und Forschungszentrum in der Geschichte der Menschheit. Die brillantesten Denker der Antike legten hier den Grundstein für ein systematisches Studium von Astronomie, Geografie, Literatur, Mathematik, Medizin und Physik. Hier definierte Euklid die Grundregeln der Geometrie und führte Eratosthenes genaue Messungen des Erdumfangs durch. Letzterer vertrat auch die Ansicht, dass Indien erreicht werden könne, indem man von Spanien aus in Richtung Westen segle. @Die Ptolemäer investierten viel Zeit und Energie, aber auch große Teile ihres Vermögens, um Exemplare jedes bekannten und wichtigen Manuskripts zusammenzutragen. Zu dieser Zeit wurde auch ein Gesetz erlassen, das anordnete, dass jede Karawane und jedes Schiff, das nach Alexandria kam, nicht etwa nach Schmuggelware, sondern nach gelehrten Schriften durchsucht werden musste. Jede Karte oder Schriftrolle, die gefunden wurde, wurde in die Bibliothek gebracht, damit die Schreiber sie kopieren konnten. So kam es, dass Alexandrias Gelehrtenparadies schließlich weit über 700.000 systematisch katalogisierte Papyrusrollen, darunter viele inzwischen verschollene Meisterstücke der Kunst, Literatur und Wissenschaft umfasste, wie z.B. Klassiker von Homer, Aristoteles, Sophokles, Aeschylos und Euripides.  @PEs gab aber nicht nur geschriebenes Lehrmaterial. Die legendäre Bibliothek beherbergte darüber hinaus einen botanischen Garten und ein Museum sowie einen Tempel zu Ehren der neun Musen (griechische Göttinnen der Kunst und Wissenschaft). Eine kurze Wanderung entlang einer gartengesäumten Palisade führte zu einem Zoo, in dem wahrscheinlich viele exotische Tiere lebten. Unzählige Gelehrte müssen durch ihre Säulengänge gewandelt sein.  @PWas genau zum Niedergang der Großen Bibliothek führte, ist nicht bekannt. Sicher ist, dass ein großer Teil dieser unschätzbaren Werke durch ein Feuer zerstört wurde, als Julius Caesar die Schiffe von Kleopatras Bruder in Brand setzen ließ. Im vierten Jahrundert nach Christus, als sich der Einfluss der Christen immer mehr ausdehnte, fielen viele der noch verbliebenen Manuskripte der Bibliothek dem Bemühen zum Opfer, sämtliche Überbleibsel von Heidentum und Ketzerei auszulöschen. Später, etwa um 640 n.Chr., zogen Araber durch die fast verlassene Stadt und verfeuerten vermutlich sämtliche Papyrusrollen, die noch verblieben waren. Von den 123 Theaterstücken des Sophokles, von denen man weiß, dass sie in der Großen Bibliothek waren, sind heute nur noch sieben übrig."
        }
    }
    message_history_caesareum {
        id: 482,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "Kleopatra VII. begann mit dem Bau des Caesareums. Es bestand ursprünglich aus einem kleinen Tempel oder Altar in der Mitte eines Sanktuariums, das offensichtlich der Verehrung des Marcus Antonius diente. Sein Selbstmord, gefolgt von Kleopatras Tod, hatte zur Folge, dass dieses Monument von seinem Rivalen Octavian (Augustus Caesar) zwar vollendet wurde, nach Fertigstellung jedoch dessen eigenem Kult geweiht wurde. Zwei Obelisken (im Volksmund 'Kleopatras Steinnadeln' genannt, obwohl sie gar nichts mit ihr zu tun hatten) waren über Jahrzehnte hinweg weithin sichtbare Marksteine am Ostufer von Alexandrias Hafen. Diese Obelisken, die auf Octavians Befehl hin eigens von Heliopolis nach Alexandria gebracht wurden, markierten noch lange den Eingang zum Caesareum, nachdem der Rest des Gebäudes längst zerstört war. Beide Obelisken stehen heute an anderen Orten (einer im Central Park in New York, der andere am Ufer der Themse in London). @PPräzise Details über die tatsächliche Gestalt des Caesareums sind nicht bekannt. Unsere Informationen darüber stammen aus kurzen Beschreibungen antiker Autoren. Seine Architektur war, wie viele große Monumente Alexandrias, dem griechischen Stil nachempfunden. Bekannt ist, dass es ein zentrales Sanktuarium inmitten offener Höfe besaß und von Stoae (säulengerahmten Wandelgängen) umgeben war, die wahrscheinlich die 'Außenwände' des Monuments bildeten. Räume und Säulengänge zwischen den Stoae enthielten Schriftrollen und konnten für Studien oder Seminare verwendet werden."
        }
    }
    message_plague_of_locusts {
        id: 483,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title {
            text: "Heuschreckenplage",
        }
        content {
            text: "Berichten aus ganz Ägypten zufolge vernichten riesige Schwärme gefräßiger Heuschrecken den Ertrag unserer Felder. In der nächsten Saison werden sie auch uns erreichen!"
        }
    }
    message_plague_of_frogs {
        id: 484,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title {
            text: "Froschplage",
        }
        content {
            text: "Ein schlimmer Fluch lastet auf unserem Land! Millionen von Fröschen machen unsere Straßen unpassierbar und unsere Wohnungen unbewohnbar."
        }
    }
    message_hailstorm {
        id: 485,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title {
            text: "Hagelschauer",
        }
        content {
            text: "Tod und Zerstörung liegen in der Luft! Ein wilder Hagelschauer bringt tödlichen Eisregen über uns. Mögen sich die Götter all denen gnädig erweisen, die sich nicht vor diesem bösen Fluch retten konnten."
        }
    }
    message_river_of_blood {
        id: 486,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title {
            text: "Blutiger Fluss",
        }
        content {
            text: "Wehe uns! Die Gewässer, unsere Lebens- und Nahrungsquellen, sind mit Blut verseucht. Wie lange werden wir unter diesem schrecklichen Fluch leiden müssen?"
        }
    }
    message_history_pharos_lighthouse {
        id: 487,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1006,
            pos [15, 15]
        }
        title {
            text: "Leuchtturm von Pharos",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "@PAlexandrias Lage mit langen Uferstrecken und einem großen, natürlichen Hafenbecken war zwar ideal für einen Handelshafen, das Fahrwasser jedoch war voller gefährlicher Sandbänke. Aus diesem Grund wurde beschlossen, dass ein hoher Leuchtturm auf der Insel Pharos in der Nähe der Hafeneinfahrt nicht nur den Seeleuten zugute kommen, sondern (zumindest wenn er prächtig genug wäre) auch eine wunderbare neue Attraktion zur Steigerung von Alexandrias Ruhm sein würde.  @PDas heute auch als 'Leuchtturm von Alexandria' bekannte Bauwerk wurde größtenteils aus weißem Marmor errichtet, der von den Prinzeninseln vor der Küste der heutigen Türkei importiert wurde. Er besteht aus drei großen Stufen: die unterste Stufe (das Fundament) war quadratisch, die mittlere achteckig und die oberste zylindrisch angelegt. Eine riesige Wendeltreppe, die so breit war, dass sogar Lasttiere mit Holz zur Unterhaltung des dort brennenden hellen Leuchtfeuers hinaufklettern konnten, führte bis zur Spitze. Auf der Spitze dieses spektakulären Bauwerks stand (einigen Informationen zufolge) eine Poseidon-Statue; andere Quellen behaupten, dass es sich um eine Zeus-Statue oder vielleicht Statuen beider Gottheiten gehandelt hatte. @PDer Bau des Leuchtturms von Alexandria wurde von Ptolemäus Auletes begonnen und erst 283 v.Chr. während der Regierungszeit seines Sohnes Ptolemäus Philadelphus abgeschlossen. Allen Berichten zufolge bot er einen unglaublichen Anblick und wurde zu Recht zu den Sieben Weltwundern der antiken Welt gezählt. @PDie letztendliche totale Zerstörung des Monuments geschah nicht durch Menschenhand, sondern durch eine Reihe von Erdbeben, die dieses Gebiet erschütterten. Die oberste Stufe stürzte 303 n.Chr. während eines schweren Bebens herunter. Der Großteil des restlichen Gebäudes dagegen brach erst durch ein gewaltiges Erdbeben zusammen, das sich am 8. August 1303 ereignete und den gesamten östlichen Mittelmeerraum erschütterte. Heute ist auf der Insel Pharos an der Stelle, an der einst der beeindruckende Leuchtturm stand, eine Festung zu sehen, die der Mamelucken-Sultan Qait Bei erbauen ließ."
        }
    }
    message_building_alexandria_library {
        id: 488,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Alexandrias Bibliothek",
        }
        content {
            text: "Gelehrte und andere gebildete Männer und Frauen aus der gesamten bekannten Welt strömen in Scharen zur Großen Bibliothek in Alexandria, der wohl größten Wissenssammlung der Menschheit. Wählen Sie die Bibliothek von Alexandria in der Liste 'Religiöse Einrichtungen: Monumente' an. Ist der Grundriss komplett grün, haben Sie einen geeigneten Standort dafür ausgewählt.  @PFür den Bau der Bibliothek von Alexandria benötigen Sie die Dienste von Arbeitern aus einem @8Arbeiterlager, von Steinmetzen der @363Steinmetzgilde und Zimmerleuten der @363Zimmermannsgilde. Die Zimmerleute brauchen für den Gerüstbau @94Holz, das Sie importieren können, wenn es in Ihrer Stadt keines gibt. Des Weiteren müssen Sie über einen Handelspartner weißen Marmor @47importieren. Um das Monument zu vollenden, ist eine Ladung @93Kupfer erforderlich, das Sie entweder aus eigenen Minen in Ihrer Stadt oder über einen Handelspartner beziehen können. @PRechtsklicken Sie während der Bauphase auf die Bibliothek, wenn Sie den Fortschrittsbericht des @369Vorarbeiters&des&Baus einsehen möchten. @L@PKlicken Sie @481hier, wenn Sie mehr über die Geschichte der Großen Bibliothek von Alexandria erfahren möchten."
        }
    }
    message_building_pharos_lighthouse {
        id: 489,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Leuchtturm von Pharos",
        }
        content {
            text: "Alexandrias spektakulärer Leuchtturm auf der Insel Pharos leitet die Seeleute tags und nachts sicher durch die gefährlichen Untiefen des Hafens. @PDer Leuchtturm kann nur auf dem felsigen Boden der Insel Pharos im Hafen von Alexandria erbaut werden. Wählen Sie hierzu in der Liste 'Religiöse Einrichtungen: Monumente' die Option 'Leuchtturm von Pharos' an, und schieben Sie den Mauszeiger in der Nähe der Hafeneinfahrt über den steinigen Boden (auf der Insel Pharos). Sobald der Grundriss des Monuments vollständig grün ist, haben Sie eine passende Stelle gefunden, die das gewaltige Gewicht dieses Bauwerks tragen kann. @PWenn der Boden planiert ist, benötigen Sie einen Vorrat an importiertem Marmor. Dieses Material kann über eine @47Handelsroute aus einer anderen Stadt bezogen werden. @363Steinmetze einer Steinmetzgilde verlegen vorsichtig den weißen Marmor, den die Arbeiter eines @8Arbeiterlagers von einem @4Warenlager herbeischaffen. Die Arbeiter holen den weißen Marmor, sobald mindestens vier Blöcke davon in einem einzelnen Warenlager vorrätig sind. Nachdem die Bauarbeiten begonnen haben, werden zur Herstellung eines Gerüsts @363Zimmerleute und eine gewisse Menge @94Holz benötigt. @PRechtsklicken Sie während des Baus auf den Leuchtturm, um sich den Fortschrittsbericht des @369Vorarbeiters&des&Baus anzusehen. @LKlicken Sie @487hier, wenn Sie mehr über den Leuchtturm von Alexandria erfahren möchten."
        }
    }
    message_building_caesareum {
        id: 490,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Caesareum",
        }
        content {
            text: "Eines von Alexandrias großartigsten architektonischen Meisterwerken ist zweifellos das Caesareum, ein ausgedehnter Tempel am Meer und weithin sichtbarer Wegweiser für die Seeleute, die Alexandrias Hafen anlaufen. @PUm das Caesareum zu bauen, müssen Sie es zunächst in der Liste 'Religiöse Einrichtungen: Monumente' der Steuerleiste anwählen. Dann sehen Sie einen Grundriss des Gebäudes. Suchen Sie ein bisschen, bis Sie ein genügend großes ebenes Areal gefunden haben, und platzieren Sie dort das Monument. Ob ein geeigneter Platz gefunden ist, erkennen Sie daran, dass der gesamte Grundriss grün erscheint.  @PSobald ein passender Bauplatz gefunden ist, kann das Bauvorhaben in Angriff genommen werden. Arbeiter aus einem @8Arbeiterlager beginnen, den Boden zu planieren und das darunter liegende Gestein freizulegen. Wenn der Untergrund vorbereitet ist, treffen die @363Steinmetze einer Steinmetzgilde ein und verlegen den weißen Marmor, den die Arbeiter aus einem @4Warenlager holen. Weißer Marmor muss über einen @47Handelspartner importiert werden. Die Arbeiter schleppen die Marmorblöcke zur Baustelle, sobald vier Stück davon in einem einzelnen Warenlager vorrätig sind. @PUm das Gerüst zu bauen, werden dann @363Zimmerleute von einer Zimmermannsgilde benötigt, die über genügend @94Holz verfügt. Falls Ihre Stadt nicht selbst Holz schlagen kann, müssen Sie welches importieren. Gegen Ende der Bauarbeiten benötigen Sie dann noch eine gewisse Menge Granit aus einem Warenlager. Wenn Ihre Stadt keine @95Granitsteinbrüche besitzt, kann auch dieser Rohstoff importiert werden. @PKlicken Sie das Caesareum während der Bauphase mit der rechten Maustaste an, und lassen Sie sich von dem @369Vorarbeiter&des&Baus den Fortschrittsbericht zeigen. @LKlicken Sie @482hier, wenn Sie detaillierte historische Informationen über das Caesareum haben möchten."
        }
    }
    message_crime_wave {
        id: 491,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1,
        title {
            text: "Verbrechenswelle",
        }
        content {
            text: "Mögen die Götter uns gnädig sein! Eine nach Reichtümern gierende Bande von Grabräubern marodiert in unserer schönen Stadt. Halten Sie sie auf, bevor sie die herrlichen Dinge stehlen, die wir unseren edlen Vorfahren mit ins Grab gegeben haben!"
        }
    }
    message_building_abu_simbel {
        id: 492,
        pos [0, 24]
        size [30, 28]
        title {
            text: "Abu Simbel",
        }
        content {
            text: "@PDer Tempel von Abu Simbel ist ein riesiges Bauwerk, das Ramses II. am Oberlauf des Nils in Nubien aus den Sandsteinfelsen schlagen ließ. Um mit dem Bau von Abu Simbel zu beginnen, wählen Sie das Monument zunächst in der Liste 'Religiöse Einrichtungen: Monumente' an. Der Grundriss des Monuments erscheint. Der größte Teil des Monuments muss in Felswände hineingebaut werden. Der Eingang dagegen, der an einer Seite des Monuments herausragt, muss sich auf ebenem Boden befinden. Wenn der Grundriss komplett grün wird, wissen Sie, dass Sie einen passenden Bauplatz gefunden haben. Klicken Sie mit der linken Maustaste, um das Monument zu platzieren. @PVielleicht hilft es Ihnen bei der Suche nach einem geeigneten Bauplatz für das Monument, wenn Sie die Felswände vorübergehend ausblenden. Drücken Sie dazu einfach die H-Taste, oder wählen Sie in der Liste der @18Spezialkarten die Option 'Felsen verbergen' an. Wenn Sie die Felswände wieder in ihre ursprüngliche Gestalt zurückverwandeln möchten, drücken Sie erneut die H-Taste oder wählen in der Spezialkartenliste die Option 'Normal' an.  @PWenn eine passende Stelle zugewiesen ist, brauchen Sie fähige Arbeitskräfte, wie z.B. @363Steinmetze einer Steinmetzgilde für das Aushöhlen des Gesteins und @363Zimmerleute einer Zimmermannsgilde, die die nötigen Gerüste bauen. Die Zimmerleute benötigen @192Holz für den Gerüstbau, das entweder über eine @47Handelsroute importiert oder durch ein @94Holzfällerlager selbst beschafft werden kann. @PRechtsklicken Sie auf das Monument, und Sie erhalten einen Fortschrittsbericht vom @Vorarbeiters&des&Baus."
        }
    }
    message_history_abu_simbel {
        id: 493,
        pos [0, 88]
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
            text: "Geschichte",
        }
        content {
            text: "@PRamses der Große (Ramses II.) regierte Ägypten etwa in der Zeit von 1279 bis 1212 v.Chr. Dieser mit einem langen Leben gesegnete Pharao ist für seine vielen Tempel und Monumente bekannt, die er während seiner Regierungszeit errichten ließ. Das großartigste davon ist Abu Simbel.  @PÜber 500 Kilometer südlich von Waset (Theben) meißelten Ramses' Steinmetze eine Reihe von vier sitzenden Statuen des Pharao in die rosafarbenen Sandsteinfelsen, die sich über dem Niltal erhoben. Jede Statue ist über 20 Meter hoch - nur die große Sphinx bei Giseh ist noch größer. Die sitzenden Figuren flankieren einen Tunneleingang, der zum inneren Heiligtum 63 Meter weit in den Felsen hineinführt. Der Tempel weist nach Osten und ist so angelegt, dass zweimal im Jahr das Licht der aufgehenden Sonne auf die hintere Wand des Heiligtums fällt und drei kleinere Statuen von Ramses, Amun und Ra beleuchtet. Auch eine Statue des Ptah befindet sich im Heiligtum; diese ist jedoch so positioniert, dass das Sonnenlicht sie nicht erreicht, da Ptah mit der Unterwelt assoziiert wird. Reliefs im Inneren des Tempels erzählen von Ramses' militärischen Glanzleistungen. Dicht daneben wurde ein kleinerer Tempel zu Ehren der Göttin Hathor und Ramses' Hauptfrau, Königin Nefertari, in den Felsen geschlagen. Der gesamte Komplex hatte den Zweck, den nubischen Untertanen Respekt einzuflößen und sie zu Tributzahlungen zu ermuntern.  @PAbu Simbel wurde etwa 1256 v.Chr. fertiggestellt. Im Verlauf der Jahrtausende jedoch häufte sich immer mehr Sand um und über ihm auf, sodass er schließlich völlig im Wüstensand verschwunden war. 1817 legte der Archäologe Giovanni Belzoni das riesige Bauwerk wieder frei. In den sechziger Jahren drohte es dann erneut zu versinken, dieses Mal jedoch im steigenden Wasser hinter dem neu gebauten Assuan-Staudamm. Abu Simbel wurde daraufhin aus dem Felsen herausgesägt und mit großer Präzision an einer höher gelegenen Stelle neu errichtet - dies war eine Meisterleistung der Ingenieure, die den alten Ägyptern mit Sicherheit sehr imponiert hätte."
        }
    }
    message_tutorial_major_plagues {
        id: 494
        pos [0, 24]
        size [30, 28]
        title { text: "Große Plagen" }
        content { text: "Es gibt viele Übel, die über eine Stadt ungeachtet ihrer Größe oder ihres Wohlstandes hereinbrechen können, aber die großen Plagen gehören zu den schlimmsten. Beachten Sie bitte, dass 'große Plagen' nicht identisch mit @53Seuchen sind. Seuchen brechen aus, wenn der Gesundheitszustand in der Stadt besonders schlecht ist. Große Plagen können auch ohne Ursache auftreten.  @PAlle großen Plagen führen zu schlechter @39Stimmung&in&der&Stadt. Ihre weiteren schrecklichen Konsequenzen werden nachfolgend beschrieben @L@LBlutiger Fluss @LBei der Plage des 'blutigen Flusses' färben sich die Flüsse und Seen Ihrer Stadt mehrere Monate lang rot, und das Wasser kann weder als @44Trinkwasser noch in sonstiger Weise genutzt werden. Ein Teil des in den Häusern aufbewahrten Wassers wird ebenfalls verseucht und ungenießbar, wobei diejenigen, die in der Nähe des Flusses leben, am schwersten betroffen sind. Bei den in unmittelbarer Nähe des Wassers lebenden Menschen steigt die Anfälligkeit für Krankheiten und Malaria (weitere Informationen über Krankheiten und Malaria finden Sie unter @53Gesundheit&der&Stadt). @84Fischerhäfen, @59Wasserheber, @94Schilfsammelstellen, @62Brunnen und @61Zisternen können während dieser Plage nicht genutzt werden. Vielleicht schickt @354Bastet aus Wut die Plage über Ihre Stadt ... oder die Plage kommt ganz ohne ersichtlichen Grund. @L@LFrösche @LWenn die Froschplage hereinbricht, fallen Unmengen von Fröschen über Ihre Stadt her und dringen in jedes Haus ein, das auf ihrem Weg liegt. Niemand kann in einem von Fröschen besetzten Haus leben, daher müssen die Bewohner flüchten und können mehrere Monate lang nicht zurückkehren. Sie können versuchen, die Frösche durch den Bau von Mauern oder strategisch günstig platzierten Gebäuden aufzuhalten. Manchmal ist @352Ptah für den Fluch verantwortlich, der Ihre Stadt heimsucht, wenn Sie sein Missfallen erregt haben. Manchmal jedoch folgen die Frösche auch nur ihrem eigenen Willen. @L@LHagelschauer @LBei einem Hagelschauer prasseln tödliche Hagelkörner herab, die jedermann erschlagen, der sich auf den Straßen der Stadt bewegt. Hagelkörner machen keine Ausnahmen und können Soldaten (einschließlich Feinde) und Tiere genauso leicht töten wie gewöhnliche Bürger. Hagelschauer wühlen außerdem das Wasser der Flüsse stark auf, und viele Ihrer Schiffe könnten dadurch sinken. Wenn Sie @353Seth vernachlässigen, könnte er diese schreckliche Plage über Ihre Stadt kommen lassen. Hagelschauer können aber auch natürliche Wettererscheinungen sein. @L@LHeuschrecken @LHeuschrecken fallen über das Land her und vernichten die gesamte Ernte, die auf Ihren @45Farmen wächst. Die Erträge sowohl im Überschwemmungsgebiet als auch im Wiesengebiet werden noch vor der Ernte vollständig vernichtet, sodass Ihre Stadt in diesem Jahr nicht davon profitieren kann. Wenn Sie @350Osiris' Ärger provoziert haben, könnte er Ihrer Stadt diese Plage schicken. Ab und zu treten Heuschrecken jedoch auch ohne jegliche Provokation auf. @L@LWenn Sie mehr über die großen Plagen wissen möchten, die das Land der Pharaonen heimgesucht haben, klicken Sie @495hier." }
    }
    message_history_major_plagues {
        id: 495,
        pos [0, 88]
        size [30, 20]
        image {
            id: 1010,
            pos [15, 15]
        }
        title {
            text: "Große Plagen",
            pos [125, 15]
        }
        subtitle {
            text: "Geschichte",
        }
        content {
            text: "Im 13. Jahrhundert v.Chr., während der Regierungszeit Setis I. und seines Sohnes Ramses II. (Ramses der Große), wurden die Israeliten durch die Ägypter versklavt, um bei ihren Bauvorhaben mitzuarbeiten. Nach dem zweiten Buch Mose, dem Exodus, erschien Gott einem der Kinder Israels, dem Propheten Moses, und versprach ihm, dessen Volk zu befreien. Auf diese Weise durch den Herrn geführt, trat Moses zehn Mal vor den Pharao hin und forderte: 'Gib mein Volk frei.' Ramses allerdings lehnte jedes Mal ab. Nach jeder Ablehnung brach eine andere Plage über den Pharao und die Ägypter herein, nur die versklavten Israeliten blieben verschont. Zuerst verwandelte sich das Wasser des Flusses in Blut, wodurch die Fische starben und das Wasser ungenießbar wurde. Nach der zweiten Weigerung des Pharao kamen die Frösche aus den Teichen und Flüssen und besetzten die Häuser der Dörfer. Die siebente Plage bestand in einem donnernden Hagelschauer, der die Menschen und Tiere auf den Feldern zerschmetterte und die gesamte Gerste- und Flachsernte vernichtete. Gemäß dem Buch Exodus kamen nach Ramses' achter Weigerung 'die Heuschrecken über ganz Ägyptenland und sie ließen nichts Grünes übrig an den Bäumen und auf dem Felde in ganz Ägyptenland'. Ramses kapitulierte, nachdem die zehnte Plage alle Erstgeborenen des ägyptischen Volkes und seiner Tiere tötete. Allerdings schickte Ramses seine Armee aus, um die fliehenden Israeliten durch das Schilfmeer zu verfolgen. @PObwohl diese Plagen in zeitgenössischen ägyptischen Aufzeichnungen nicht erwähnt werden, gibt es mehrere Hinweise darauf, dass es diese oder ähnliche Katastrophen in der Geschichte und Vorgeschichte gegeben hat. Sogar im 20. Jahrhundert n.Chr. wird die Menschheit noch von Hagelstürmen und Heuschreckenschwärmen heimgesucht."
        }
    }
    message_mummy_attacks {
        id: 496,
        type: 2,
        pos [0, 88]
        size [30, 20]
        urgent: 1
        title { text: "Mumie greift an!" }
        content { text: "Eine Mumie ist auferstanden und streift durch die Straßen der Stadt. Dieser Fluch muss gestoppt werden, bevor er das ganze Land erfasst." }
    }
}
