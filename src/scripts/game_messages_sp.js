log_info("akhenaten: messages config started")

game_messages_sp {
    message_potter_history {
        id: 1,

        size [30, 28]
        title { text: "Alfarero" }
        advisor: ADVISOR_TRADE
        content {
            text: "Los alfareros necesitan un suministro de arcilla para funcionar. Algunas ciudades pueden producir su propia arcilla construyendo @92Canteras&de&arcilla. Otras ciudades pueden necesitar importar arcilla de un socio comercial (haga clic en @47aquí para saber más sobre el comercio). @PLos carreteros llevan arcilla a los alfareros desde las canteras de arcilla, si la ciudad las tiene, o desde @4Almacenes. El alfarero guarda algo de arcilla extra en su patio para seguir trabajando durante un tiempo si las entregas de arcilla se interrumpen por algún motivo. @PLos alfareros también necesitan acceso a una carretera y una fuente cercana de mano de obra. Los alfareros son más productivos cuando tienen el personal completo, pero seguirán funcionando (aunque con menor eficiencia) si tienen personal insuficiente. Si el alfarero está produciendo cerámica, lo verá trabajando con empeño. Los carreteros empleados por el alfarero llevan la cerámica terminada a un Almacén o a un @473Fabricante&de&lámparas (que necesita un suministro de cerámica y aceite para producir lámparas). @PLa cerámica es un bien importante en la ciudad. @56Las casas necesitan un suministro de cerámica para evolucionar a niveles superiores, y la cerámica debe reponerse constantemente para evitar que las casas degeneren a niveles inferiores. La demanda de cerámica nunca cesa: los hogares siempre están reponiendo piezas rotas o gastadas. Consulte los @2Bazares para saber más sobre cómo hacer llegar los bienes terminados a los ciudadanos. @PLa cerámica también es fundamental para la construcción de las @478Tumbas&reales&de&enterramiento. Cuando un fabricante de lámparas llena la cerámica de aceite, se convierte en una lámpara potente que ilumina el camino de los trabajadores de la tumba.  @PLa cerámica también puede importarse o exportarse. Consulte @47comercio para obtener información sobre cómo abrir rutas comerciales. Si su ciudad comercia con cerámica, procure tener en cuenta las necesidades de los ciudadanos. Informe a su @24Supervisor&de&comercio de cuánta cerámica debe almacenarse en los Almacenes para uso de los ciudadanos, o deje que el supervisor determine una cantidad.  @PA la gente no le gusta vivir demasiado cerca de un alfarero ruidoso y polvoriento, por lo que tiene un efecto negativo en el atractivo de los terrenos vecinos. @L@LPara saber más sobre la fabricación de cerámica en el antiguo Egipto, haga clic @198aquí."
        }
    }

    message_bazaar_history {
        id: 2,

        size [30, 28]
        title { text: "Bazar" }
        content {
            text: "Sin bazares, la gente nunca tendría acceso a los alimentos y bienes almacenados en los @3Graneros y en los @4Almacenes. Solo los bazares distribuyen los suministros necesarios a la población. @PPara funcionar correctamente, los bazares necesitan acceso a una carretera y una plantilla completa. El bazar seguirá funcionando si tiene personal insuficiente, pero con una eficiencia muy reducida. @PCada bazar emplea a dos compradores: uno para comprar alimentos en los graneros y otro para comprar artículos en los almacenes.  Cada comprador es especialista: el comprador de graneros no puede adquirir artículos de un almacén, y viceversa.  Sin embargo, cada uno de estos compradores puede comprar más de un artículo a la vez.  Por ejemplo, un comprador del bazar que va al granero puede comprar grano y granadas. Sin embargo, no puede comprar grano y cerámica, porque la cerámica nunca se almacena en un granero.  @PUna vez que el comprador del bazar encuentra los artículos que necesita, una fila de ayudantes lleva la carga de vuelta al bazar. @PEl comprador del bazar es un @42'paseante&de&destino'. Pasa su vida yendo y viniendo entre su bazar y los graneros y almacenes de la ciudad.  Su descripción de trabajo la exime de cruzar toda la ciudad para llegar a los suministros, y no comerciará con más de tres fuentes de suministro dentro de su alcance.  Si la ve parada sin hacer nada cuando hay trabajo pendiente, probablemente esté esperando que tenga que caminar demasiado lejos o tratar con demasiados proveedores.  @PEl otro empleado del bazar, el comerciante del bazar, toma los artículos que traen los compradores y los distribuye a los barrios cercanos. Cuando el comerciante pasa a dos casillas de una vivienda, le suministra lo que necesita si tiene los artículos en existencia. También averigua qué bienes desean sus clientes para mejorar sus viviendas, y comunica estas necesidades al comprador para que pueda obtener los artículos necesarios. La primera prioridad es reponer los artículos que una casa necesita para no degenerar (consulte la entrada de @56habitabilidad de las viviendas). Una vez satisfechas esas necesidades, intentan conseguir el siguiente artículo que la casa necesita para mejorar. @PEl comerciante del bazar, por tanto, es un 'paseante errante'. Su función es recorrer los bloques cercanos y atender a sus clientes, en lugar de dirigirse a un destino concreto. Si un sector residencial no recibe bienes, observe por dónde camina el comerciante. No sigue una ruta fija. Cada vez que llega a una intersección, elige por dónde ir, y no siempre toma el mismo camino. Planifique con cuidado las carreteras de la ciudad y use @358Barreras para encauzar a los comerciantes de los bazares. Un bazar que ha evolucionado a su estado más avanzado (indicado por una de sus tiendas sustituida por un pequeño edificio) envía dos 'paseantes errantes' en lugar de uno.  @PLas necesidades de la gente en productos básicos, como la comida y la cerámica, deben satisfacerse antes de atender deseos más avanzados, como la cerveza o el lino. Los compradores del bazar ignorarán un almacén repleto de lino si las casas a las que sirven reclaman cerámica a gritos. Por eso es muy importante mantener un suministro constante de un bien una vez que las casas empiezan a demandarlo. Recuerde que, al evolucionar, las casas suelen albergar a más personas y, por tanto, consumen más bienes. A veces tendrá que añadir más bazares para mantener un barrio bien abastecido. Haga clic con el botón derecho sobre una casa para ver qué necesitan sus habitantes en cada momento.   @PPara asegurarse de que los residentes reciben los alimentos y bienes que necesitan, construya graneros y almacenes cerca de los bazares.  Use las órdenes especiales del granero y del almacén para asegurarse de que disponen de los bienes y alimentos que necesitan los bazares. @PSi quiere tener más control sobre un bazar, haga clic en su botón de 'Órdenes especiales' para ver una lista de todos los bienes que puede almacenar. Haga clic en un artículo para indicar al bazar si debe comprarlo o no. @PAunque los ciudadanos necesitan vivir cerca de los bazares para tener acceso a todos los bienes que desean, nadie quiere vivir demasiado cerca de ellos. Son lugares ruidosos, a veces frecuentados por personajes poco recomendables, y pueden oler mal.  @L@LPara hacerse una idea de la vista, los sonidos y los olores de un bazar del antiguo Egipto, haga clic @199aquí."
        }
    }

    message_building_granary {
        id: 3,

        size [30, 28]
        title { text: "Granero" }
        content {
            text: "Los graneros almacenan los alimentos que consumen los ciudadanos. Los @2compradores&de&bazar recogen alimentos del granero para distribuirlos entre la población. @PLos graneros necesitan acceso a una carretera y mano de obra para funcionar. Puede ver lo que almacena el granero mirando por sus bocas de llenado.  Haga clic con el botón derecho sobre un granero para ver exactamente cuánto de cada alimento contiene. @P@45Granjas&de&cultivo, @84Muelles&de&pesca, @360Ranchos&de&ganado y @359Cabañas&de&caza emplean repartidores que llevan su producción a los graneros. Por lo general, conviene situar los graneros cerca de los productores de alimentos. Si un repartidor tarda tanto en llegar que su empleador termina otra carga de alimentos antes de que regrese con su carro vacío, la instalación de producción permanecerá parada hasta que llegue a recoger los alimentos acumulados.   @PSi todos los graneros están llenos, los repartidores esperarán hasta que se libere espacio en algún granero, a menos que haya ordenado a un @4Almacén que acepte ese alimento concreto.   @PPara gestionar el flujo de alimentos en la ciudad, asigne órdenes especiales a los graneros.  Haga clic con el botón derecho en un granero y, a continuación, en el botón de Órdenes especiales para empezar.  Se muestran todos los artículos que el granero puede almacenar.  Haga clic en un artículo para cambiar la forma en que ese granero gestiona el alimento.  Las opciones son: @L@LAceptar todo/Llenar granero @LPara limitar la cantidad de un alimento que acepta un granero, use el comando Llenar.  Puede indicar al granero que se llene hasta 1/4, 1/2 o 3/4 de su capacidad. Si no desea limitar la entrada de un alimento concreto, ordene al granero que acepte todo el artículo. Esta opción es útil cuando quiere que un granero almacene cantidades iguales de varios tipos de alimentos.   @L@LNo aceptar  @LUse este comando para indicar a un granero que deje de aceptar un alimento por completo.  El granero no aceptará nuevos envíos de ese alimento, pero los compradores del bazar y los carreteros de otros graneros seguirán recogiendo el artículo hasta agotar las existencias. Use esta opción para que los repartidores eviten un granero cercano en favor de otro más lejano, o para impedir que se consuma un alimento que quiere exportar.   @L@LObtener hasta @LSi un granero se está quedando sin un alimento concreto que quiere tener disponible, use el comando Obtener hasta. El carretero del granero buscará el artículo en otros graneros o en los almacenes de la ciudad hasta cumplir el pedido.  Puede indicar a un granero que obtenga hasta 1/4, 1/2, 3/4 o la capacidad total del granero. Esta opción puede mantener abastecidos los graneros alejados de los productores de alimentos de la ciudad. @L@LVaciar alimentos   @LSi emite esta orden, los carreteros del granero intentarán vaciar sus existencias de alimentos, buscando otros graneros o almacenes que hayan recibido orden de aceptar el artículo. Un granero al que se ordena vaciarse no aceptará nuevos envíos del alimento que está intentando enviar a otro lugar. Use esta orden si ha decidido derribar un granero o si quiere retirar un tipo de alimento que almacena. @L@LLos graneros son polvorientos, a menudo infestados de alimañas y nada bienvenidos como vecinos. A los ciudadanos no les gusta vivir cerca de ellos. @L@LHaga clic @5aquí para leer sobre los graneros en el antiguo Egipto."
        }
    }

    message_building_storage_yard {
        id: 4,

        size [30, 28]
        title { text: "Almacén" }
        content {
            text: "Los almacenes son el depósito de todos los bienes terminados y de las materias primas sobrantes.  También almacenan alimentos si se lo indica expresamente (véanse las Órdenes especiales, más abajo) y ayudan a comerciar con los artículos importados y exportados (véase la entrada de @47comercio).   @PPara funcionar, los almacenes necesitan acceso a una carretera y un suministro cercano de mano de obra. Los almacenes son más eficientes cuando tienen la plantilla completa. Pueden funcionar con personal insuficiente, pero podrían dejar de aceptar determinados bienes. @PCada almacén se divide en ocho secciones y puede guardar hasta ocho artículos distintos. Cada sección solo puede aceptar un tipo de artículo, pero más de una sección puede almacenar el mismo artículo.  La cantidad de cada artículo que puede guardarse depende de su tamaño.  Cuanto mayor es el artículo, menos cantidad puede almacenar el almacén.  Por ejemplo, una sección de un almacén puede contener muchas más piezas de cerámica que bloques de piedra.   @PMuchos otros edificios necesitan un acceso fácil a los almacenes. La @46industria entrega sus productos al almacén más cercano, y los compradores de los bazares acuden al almacén más próximo en busca de los bienes que necesitan sus clientes. Los almacenes, a su vez, entregan primero las materias primas y otros suministros necesarios a los edificios más cercanos. Los carreteros de los almacenes recorrerán largas distancias si es necesario, pero las industrias podrían quedar paradas mientras esperan los suministros que necesitan. Es sensato situar los almacenes cerca de todas las instalaciones que los necesitan. @PHaga clic con el botón derecho en un almacén para averiguar exactamente cuánto de cada artículo tiene en existencia ese almacén y si puede aceptar más mercancías.  Si un almacén no puede admitir más cantidad de un artículo concreto, el artículo aparece en amarillo. @PPuede controlar la entrada y salida de mercancías con las Órdenes especiales. Al hacer clic en el botón de Órdenes especiales, se muestra un panel con todos los bienes disponibles en su ciudad. A veces tendrá acceso a decenas de bienes. Use los botones de desplazamiento de la parte superior de la pantalla para ver más bienes disponibles. @PHaga clic en un artículo para indicar al almacén cómo debe gestionarlo. Las órdenes son: @L@LAceptar todo/Llenar   @LPara limitar la cantidad de un artículo que acepta un almacén, use el comando Llenar.  Puede indicar al almacén que se llene hasta 1/4, 1/2 o 3/4 de su capacidad.  Si no desea limitar la entrada de un artículo concreto, ordene al almacén que acepte todo el artículo.  Esta opción es útil cuando quiere que un almacén guarde cantidades iguales de varios productos, o si quiere que un almacén guarde alimentos para exportar.   @L@LNo aceptar   @LUse este comando para indicar a un almacén que deje de aceptar un artículo por completo.  El almacén no aceptará nuevos envíos de ese artículo, pero los compradores de los bazares, los socios comerciales y las industrias de la ciudad podrán usar los suministros que el almacén aún tiene hasta agotar las existencias.  Use esta opción para que los repartidores eviten un almacén cercano en favor de otro más lejano.  Si no se les indica lo contrario, los almacenes no aceptan alimentos, de modo que los alimentos se entregan a los graneros.  @L@LObtener hasta   @LSi un almacén se está quedando sin un artículo concreto que quiere tener disponible, use el comando Obtener hasta. El carretero del almacén buscará el artículo en otros almacenes hasta cumplir el pedido.  Puede indicar a un almacén que obtenga hasta 1/4, 1/2, 3/4 o la capacidad total del almacén.  Esta opción puede mantener abastecidos los almacenes alejados del centro. @L@LVaciar   @LSi emite esta orden, el carretero del almacén intentará vaciar sus existencias del artículo concreto, buscando industrias u otros almacenes que puedan aceptarlo.  Use esta orden si ha decidido derribar un almacén o si quiere retirar un tipo de bien que almacena. @L@LLos almacenes son clave para hacer llegar los bienes a los residentes de la ciudad.  Los @2bazares obtienen los bienes que necesitan los ciudadanos directamente de los almacenes. Los almacenes también son vitales para el comercio. Todos los bienes importados se guardan en los almacenes, y todos los bienes destinados a la exportación se conservan allí hasta que los comerciantes de otras ciudades vienen a recogerlos. @L@LDescubra cómo eran los almacenes del antiguo Egipto haciendo clic @6aquí."
        }
    }

    message_granary_history_2 {
        id: 5

        size [30, 20]
        title { text: "Granero" }
        content {
            text: "Como la agricultura era en gran medida imposible durante la Inundación, los graneros eran de vital importancia para garantizar que los antiguos egipcios tuvieran alimento durante todo el año. Los graneros no solo almacenaban grano y otros alimentos, sino que también fabricaban harina.  @L@LEl granero evolucionó con el tiempo. En el período arcaico, el granero egipcio tenía forma de cono con una cúpula en la parte superior. Se construían con madera o ladrillo, y los más grandes tenían escaleras o peldaños que conducían a la boca de llenado. En el Reino Medio, el granero tenía forma de cuadrilátero y un techo plano con varias bocas de llenado, como las que aparecen representadas en nuestro juego. Un tercer tipo de granero se usaba solo para la semilla que se sembraría en la siguiente temporada de cultivo. Estos graneros tenían forma de trapecio, una forma claramente distinta de los graneros destinados al almacenamiento de alimentos, para que el grano de siembra no se comiera por error. @L@LLa mayoría de los graneros eran mantenidos estrictamente por el gobierno. Los soldados, los obreros de la construcción y otros trabajadores no agrícolas comían de estos graneros. Algunos ciudadanos ricos tenían sus propios graneros, y algunos campesinos tenían pequeños graneros propios para guardar la parte de la cosecha que se les permitía conservar."
        }
    }

    message_storage_yard_history {
        id: 6

        size [30, 20]
        image { id: 79, pos [15, 15] }
        title { text: "Almacén", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "Situados cerca del Nilo y próximos a las principales rutas comerciales, los almacenes guardaban los excedentes de suministros y los artículos destinados al comercio. Como llovía poco, muchos almacenes del antiguo Egipto eran al aire libre. Los escribas, que llevaban un control estricto del inventario, los supervisaban con esmero."
        }
    }

    message_keyboard_commands {
        id: 7

        size [30, 28]
        title { text: "Comandos de teclado" }
        subtitle { text: "Controles del juego" }
        content {
            text: "Varios comandos de Faraón pueden emitirse con el teclado.  Los comandos son: @L@LTecla    Efecto @LA      Ordena a un barco de guerra seleccionado atacar  @Pa todos los enemigos. @L@LC      Muestra los riesgos: superposición de delincuencia,  @Po ordena a una compañía de carros seleccionada  @Pcargar. @L@LD      Muestra los riesgos: superposición de daños. @L@LE      Ordena a un barco de transporte seleccionado  @Pevadir a los enemigos. @L@LF      Muestra los riesgos: superposición de incendios, u @Pordena a una compañía seleccionada regresar a su  @PFuerte. @L@LH      Oculta el terreno de acantilados. @L@LP       Ordena a un barco seleccionado mantener  @Psu posición actual. @L@LL      Centra la vista en una compañía militar distinta  @Pcada vez que se pulsa. @L@PSi hay una compañía seleccionada, 'L' emite  @Pla orden 'mantener el terreno en formación abierta'. @L@LM     Al seleccionar un monumento de  @Pla lista de edificios, su imagen se adhiere a su  @Pcursor y muestra cuánto terreno ocupará el  @Pmonumento. Mantener pulsada la tecla 'M'  @Pinmoviliza la 'huella' del monumento en su  @Pposición para que pueda desplazar la vista  @Ppor la ciudad sin mover la ubicación  @Pprovisional del monumento.  Suelte  @Pla tecla 'M' para reanudar el comportamiento  @Pnormal del ratón, o haga clic para colocar el monumento  @Pen la ubicación actual de la huella.   @L@P       Pulsar 'M' cuando hay una compañía  @Pmilitar seleccionada emite la orden de  @Prematar a los enemigos restantes. @L@LN      Ordena a una compañía o un  @Pbarco de guerra seleccionado atacar a los enemigos cercanos. @L@LP      Detiene el paso del tiempo en el  @Pjuego. No puede construir mientras el tiempo está detenido. @L@LR      Al colocar una estatua, una puerta  @Po un complejo de templos, 'R' gira la  @Porientación de la estructura un cuarto de vuelta  @Pen el sentido de las agujas del reloj.  Las estatuas mostrarán varios  @Pestilos.   @L@P       Con una compañía militar seleccionada,  @P'R' ordena a los soldados cambiar su  @Porientación (girar). 'R' también ordena a un  @Pbarco de transporte o de guerra seleccionado regresar al  @Pastillero para ser reparado. @L@LT      Muestra los riesgos: superposición  @Pde problemas.   @L@PCon una compañía militar seleccionada,  @P'T' emite la orden 'mantener el terreno en formación cerrada'. @L@LW     Muestra la superposición de agua. @L@PSi un barco de guerra o de transporte está  @Pseleccionado, 'W' ordena al barco regresar  @Pa su muelle de origen. @L@LX      Muestra la superposición de impuestos. @L@LY      Muestra los riesgos: superposición de malaria. @L@LZ      Muestra los riesgos: superposición de enfermedades. @L@LEspacio   Pulse la barra espaciadora para alternar  @Pentre la última superposición seleccionada y la  @Pvista normal de la ciudad. @L@LEsc    sale del juego. @L@LCorchete de apertura @Preduce la velocidad del juego un 10 por ciento. @L@LCorchete de cierre @Paumenta la velocidad del juego un 10 por ciento. @L@LAcento @PSupervisor de los trabajadores @L@L1       Supervisor militar @L@L2      Supervisor político @L@L3      Supervisor de valoraciones @L@L4     Supervisor de comercio @L@L5     Supervisor de los graneros @L@L6     Supervisor de salud pública @L@L7     Supervisor de la enseñanza @L@L8     Supervisor de entretenimientos @L@L9      Supervisor de los templos @L@L0     Supervisor del tesoro @L@L-      (signo menos) Supervisor jefe @L@L=      (signo igual) Supervisor de monumentos @L@LCTRL+F1 @PCrea un marcador F1 en la ubicación actual @L@LCTRL+F2 @PCrea un marcador F2 en la ubicación actual @L@LCTRL+F3 @PCrea un marcador F3 en la ubicación actual @L@LF1     Va al marcador F1 @L@LF2    Va al marcador F2 @L@LF3    Va al marcador F3 @L@LF6    Cambia a vista en ventana @L@LF7    Establece una resolución de pantalla de 640x480 @L@LF8    Establece una resolución de pantalla de 800x600 @L@LF9    Establece una resolución de pantalla de 1024x768"
        }
    }

    message_work_camp_history {
        id: 8
        
        size [30, 28]
        title { text: "Campamento de trabajo" }
        content {
            text: "Los campesinos se reúnen en los campamentos de trabajo para ser asignados a labores en las @45granjas&de&la&llanura&aluvial cercanas o en los @370monumentos. Durante la temporada de cultivo, la mayoría de los campesinos se dedica a labrar. Durante la Inundación, todos trabajan en el proyecto de monumentos de la ciudad.  Si no hay ningún monumento en construcción, los trabajadores campesinos no tienen nada que hacer salvo jugar mucho al senet durante la Inundación.  Si su ciudad tiene pocos campamentos de trabajo en relación con el número de granjas de la llanura aluvial, notará un ritmo marcado que impone la Inundación. @PLos campamentos de trabajo necesitan acceso a una carretera y su propio personal. Lo mejor es colocar los campamentos cerca de las granjas y los monumentos para que los campesinos no tengan que caminar mucho.  De hecho, hay un límite a la distancia que están dispuestos a recorrer para llegar a su agotador trabajo.  Cuantos más campamentos de trabajo tenga la ciudad, más rápido se construirán los monumentos, porque habrá más trabajadores disponibles durante la temporada de cultivo. @PEl número de granjas que puede sostener un campamento de trabajo depende sobre todo de la proximidad.  Un campamento de trabajo con la plantilla completa suministra un trabajador campesino cada semana (cuatro al mes).  Este trabajador camina hasta la granja de la llanura aluvial más cercana que esté esperando a un campesino, donde trabajará durante seis meses.   @PCuando una granja se encuentra a mitad del período de trabajo de su campesino, los empleados del campamento se dan cuenta de que la granja necesitará otro campesino si la labranza ha de continuar sin interrupciones; recuerde que la temporada de cultivo dura nueve meses en la mayoría de las regiones.  Si utiliza un solo campamento de trabajo para abastecer un número muy elevado de granjas, algunas podrían no recibir nunca campesinos, y las que los reciban tendrán problemas para mantener a sus trabajadores de forma continua. @PPodría explotar un gran número de granjas de la llanura aluvial con uno o dos campamentos de trabajo, pero muchas granjas no alcanzarían su potencial y los campesinos solo estarían disponibles para trabajar en el monumento durante la Inundación.   @PEn la práctica, un campamento de trabajo puede abastecer de cuatro a seis granjas de la llanura aluvial cercanas sin interrupciones y aun así aportar algunos campesinos al proyecto de monumentos de la ciudad.  Añadir más campamentos de trabajo reparte la carga y libera más campesinos para trabajar en el monumento durante la temporada de cultivo. @L@LPara saber más sobre la vida laboral en el antiguo Egipto, haga clic @155aquí."
        }
    }

                message_frequently_asked_questions {
                    id: 9
        
                    size [30, 28]
                    title { text: "Preguntas frecuentes" }
                    content {
                        text: "Dinero @PP: Quiero que mi ciudad tenga dinero, y mucho. ¿Cuál es la mejor forma de llenar las arcas de la ciudad? @PR: La respuesta sencilla es asegurarse de que la ciudad gane más de lo que gasta. @PAsegúrese de que casi todos los residentes de la ciudad paguen impuestos. Subir el tipo impositivo aumentará las arcas de la ciudad, pero es posible que el dinero no compense la mala @39Opinión&de&la&ciudad que pueden provocar los impuestos más altos. Además, establezca cuanto antes @47relaciones&comerciales y exporte todo lo que pueda (consulte el @32Mapa&del&mundo para ver lo cerca que está la ciudad de sus límites comerciales anuales). @PReducir lo que gasta una ciudad también ayuda a los beneficios. Construya la ciudad despacio y con cuidado. Los edificios cuestan dinero, por supuesto, pero también debe considerar el dinero necesario para pagar a los empleados y el coste de proporcionarles vivienda y servicios. Construir la ciudad demasiado deprisa podría generar deudas fácilmente debido al coste de los salarios y de los servicios auxiliares. @L@PP: ¿Por qué mi ciudad no puede recaudar impuestos? @PR: Asegúrese de haber construido un Palacio. Las ciudades no pueden recaudar impuestos hasta que se construye un Palacio. @L@PP: Trabajo lo mejor que puedo, pero no me han pagado. ¿Qué pasa? @PR: Una queja muy común, sin duda. En Faraón no puede cobrar un sueldo personal hasta que haya construido una Mansión. @L@PP: ¿Cómo pago el tributo? ¿Qué pasa si no lo pago? @PR: Su tesorería paga automáticamente el tributo al final del año, siempre que tenga dinero. Solo asegúrese de que haya dinero en las bóvedas a final de año. Si las arcas están vacías, no podrá pagar el tributo y su @35Calificación&del&reino bajará. Si no puede pagar el tributo durante dos años consecutivos, la calificación del reino baja un poco más, y si la deuda continúa después, la penalización se vuelve más grave. Lea sobre la @48deuda. @L@LPaseantes @L@PP: ¿Por qué un edificio que dice tener acceso a mano de obra nunca encuentra trabajadores? @PR: Probablemente construyó una @358Barrera demasiado cerca del edificio. Observe el edificio un momento para asegurarse de que su paseante sale por el lado correcto de la Barrera. A veces, los empleados del edificio envían a su paseante en la dirección equivocada. Esto puede ser especialmente frustrante con los buscadores de mano de obra, porque el edificio que los emplea cree que tiene acceso a mano de obra, pero la Barrera impide que el paseante llegue nunca al grupo de trabajadores. Reconstruya la Barrera una casilla más lejos. @L@LReligión @PP: Me gustaría celebrar un festival, pero no me lo permite. ¿Por qué? @PR: Hay varias razones por las que puede que no pueda celebrar un festival. ¿Su ciudad tiene una Plaza de festivales? Sin plaza, no hay festivales. ¿Ya ha celebrado dos festivales en los últimos 12 meses? Una ciudad solo puede celebrar dos festivales en cualquier período de 12 meses. Si celebra un gran festival, asegúrese de tener suficiente cerveza almacenada para el evento. Por último, compruebe las arcas de la ciudad. Si la ciudad no puede pagar un festival, no podrá celebrarlo. @L@PP: El dios patrón de mi ciudad sigue enfadado conmigo. ¿Qué tengo que hacer para apaciguarlo? @PR: El dios patrón de una ciudad requiere más atención que las deidades locales. Asegúrese de tener más templos y santuarios dedicados a él o a ella que a cualquier otro dios de la ciudad, y considere gastar dinero en construir un Gran complejo de templos en honor al dios patrón. @L@LEntretenimiento @PP: No encuentro una ubicación viable para mi local de entretenimiento. ¿Cuál puede ser el problema? @PR: Salvo las Casas de senet, los locales de entretenimiento deben colocarse sobre una intersección, ya sea en forma de 'T' o de cruce. Además, debe haber espacio libre alrededor de la intersección para acomodar los escenarios de los locales. @L@PP: Tengo muchos locales de entretenimiento en la ciudad, pero no hay artistas. ¿Por qué no ofrecen espectáculos? @PR: Asegúrese de tener Centros de formación construidos en la ciudad. Los artistas deben aprender su oficio antes de entretener a las masas. @L@PP: ¿Por qué no funciona mi Casa de senet? @PR: La respuesta es la cerveza. Asegúrese de que la Casa de senet tenga cerveza disponible para servir a sus clientes. @L@LAgricultura @PP: ¿Por qué las granjas de la llanura aluvial no producen cosechas? @PR: Compruebe si hay un Campamento de trabajo cerca de las granjas. Los campesinos de un Campamento de trabajo labran la tierra de las granjas de la llanura aluvial. @L@PP:  ¿Cuántas granjas de la llanura aluvial puede sostener un Campamento de trabajo? @PR:  Depende.  Lea la entrada de ayuda sobre @8Campamentos&de&trabajo para obtener una explicación completa. @L@PP:  He construido un Muelle de pesca, pero no tiene barco. ¿Por qué? @PR:  Los barcos de pesca los construye un Carpintero de barcos. Asegúrese de que haya uno activo en la ciudad. @L@LAlmacenamiento y distribución @PP: Los bazares se quedan sin alimentos y artículos continuamente. ¿Qué puedo hacer para mantener sus estanterías surtidas? @PR: Asegúrese de construir un Granero y un Almacén cerca del Bazar. Si el comprador del bazar tiene un largo camino que recorrer, su bazar seguro que se quedará sin algo mientras ella esté fuera. Use las órdenes especiales del Granero y del Almacén para asegurarse de que estos edificios estén bien surtidos. @L@PP: ¿Cómo puedo usar los almacenes de la forma más eficaz? @PR: Para sacar el máximo partido de los @4Almacenes, considere con cuidado su ubicación en la ciudad y aproveche sus órdenes especiales. Los almacenes deben situarse cerca de edificios como bazares, muelles, obras de monumentos e industrias que necesiten sus suministros almacenados. Use las órdenes especiales del almacén para asegurarse de que los bienes almacenados son los que necesitan los edificios cercanos. Los almacenes también deben estar cerca de las estructuras industriales para reducir el tiempo que los empujadores de carros de la industria pasan en tránsito. Si el empujador de carros tiene que recorrer un largo camino para entregar sus bienes, su industria podría quedar parada mientras él está fuera. @L@LMonumentos @PP:  ¿Qué puedo hacer para acelerar la construcción de monumentos? @PR: Construya muchos Campamentos de trabajo, los gremios de construcción necesarios y almacenes que acepten solo materiales de construcción cerca de la obra. Si tiene demasiadas obras en la ciudad, los campesinos y los obreros de la construcción pueden no ponerse de acuerdo sobre dónde empezar, y es posible que no trabajen en ninguna de ellas. @L@PP: Necesito un recurso concreto para construir mi monumento, pero mi ciudad no puede producirlo y nadie quiere vendérmelo. ¿Se han equivocado los creadores de la misión? @PR: En algunas misiones, la ruta comercial que necesita solo se habilita cuando se satisfacen las peticiones de otras ciudades (especialmente las peticiones de ayuda militar). Si falla la primera petición, normalmente tendrá oportunidades de recuperarse y, así, abrir la ruta comercial vital. Si sigue fallando estas peticiones, podría perder la misión. Todas las misiones tienen todos los bienes necesarios... pero a veces hay que trabajar para conseguirlos, y el éxito no siempre está garantizado. @L@LComercio @PP: He abierto una ruta comercial, pero mi ciudad no importa ni exporta nada. ¿Cómo inicio el flujo comercial? @PR: Visite a su Supervisor de comercio y dígale qué productos debe comprar o vender. Asegúrese también de tener un Almacén en la ciudad y un Muelle si su socio comercial llega por agua. @L@PP: Intento importar algo de comida. Tengo una ruta comercial abierta y le he dicho al Supervisor de comercio que la importe, pero todavía no llega comida. La gente tiene hambre, ¿qué puedo hacer? @L@PR: Asegúrese de que sus almacenes hayan recibido la orden de aceptar la comida que intenta importar. Recuerde que los almacenes, por defecto, no aceptan ningún alimento. L@PP: He dejado que mi @24Supervisor&de&comercio decida el nivel de bienes comerciales que debe mantener en los almacenes. ¿Cómo puedo estar seguro de que toma buenas decisiones? @PR: Cuando le dice a su Supervisor de comercio que gestione el comercio, este analiza el tamaño de la población de la ciudad, las industrias que tiene y los monumentos que se están construyendo. Solo con estos factores, elabora una valoración de las necesidades de la ciudad. Para ver lo que recomienda, haga clic en sus botones de control de bienes. Cuando aparece el botón que permite fijar el nivel, la cantidad que se muestra por defecto es la que el Supervisor de comercio recomienda que la ciudad conserve en sus almacenes. @L@LVivienda @PP: Las zonas residenciales que designo siguen desapareciendo. ¿Qué está pasando? @PR: Todas las viviendas deben estar a menos de dos casillas de una carretera. Si no lo están, desaparecerán. Además, los migrantes deben poder llegar a los bloques de viviendas. Asegúrese de que hay un camino despejado entre los puntos por los que los migrantes entran y salen de la ciudad (el @57Camino&del&reino) y sus viviendas."
                    }
                }

                message_table_of_contents {
                    id: 10
        
                    size [30, 28]
                    image { id: 47, pos [15, 15] }
                    title { text: "Índice" }
                    subtitle { text: "Haga clic en un tema para ver la ayuda" }
                    content {
                        text: " @9Preguntas&frecuentes @L@LTemas de ayuda @L@L@492Abu&Simbel @L@88Academia @L@488Biblioteca&de&Alejandría @L@65Boticario @L@81Oficina&del&arquitecto @L@L@72Quiosco&de&música @L@91Granja&de&cebada @L@2Bazar @L@2Bazar:&órdenes&especiales @L@54Pirámide&escalonada @L@71Puesto @L@96Cervecería @L@55Pirámide&de&ladrillo @L@363Gremio&de&albañiles @L@364Fábrica&de&ladrillos @L@58Puente @L@33Botones&del&edificio @L@374Provisiones&funerarias @L@L@490Cesáreo @L@363Gremio&de&carpinteros @L@360Rancho&de&ganado @L@98Fabricante&de&carros @L@90Granja&de&garbanzos @L@31Supervisor&jefe @L@53Salud&de&la&ciudad @L@39Opinión&de&la&ciudad @L@92Cantera&de&arcilla @L@37Empresas @L@87Órdenes&de&la&empresa @L@369Capataz&de&obra @L@363Gremios&de&construcción @L@19Panel&de&control @L@93Mina&de&cobre @L@76Tribunal @L@36Delincuencia @L@35Calificación&de&la&cultura @L@L@17Pantalla&de&fecha @L@48Deuda @L@85Estructuras&defensivas @L@63Dentista @L@56Deseabilidad @L@83Muelle @L@44Agua&potable @L@L@50Educación @L@43Empleo @L@49Entretenimiento @L@L@45Agricultura (ver también granjas concretas) @L@11Menú&de&archivo @L@355Parque&de&bomberos @L@58Transbordador @L@366Plaza&de&festivales @L@29Festivales @L@84Muelle&de&pesca @L@91Granja&de&lino @L@45Alimentos @L@37Fuerte @L@L@79Jardín @L@85Puerta&de&la&muralla @L@361Mina&de&piedras&preciosas @L@93Mina&de&oro @L@89Granja&de&grano @L@3Granero @L@3Granero:&órdenes&especiales @L@95Cantera&de&granito @L@L@13Menú&de&ayuda @L@91Granja&de&henna @L@56Viviendas @L@359Cabaña&de&caza @L@L@46Industria @L@59Riego @L@L@99Joyero @L@L@7Controles&del&teclado @L@35Calificación&del&reino @L@57Camino&del&reino @L@L@473Fabricante&de&lámparas @L@90Granja&de&lechugas @L@70Biblioteca @L@95Cantera&de&caliza @L@L@494Grandes&plagas @L@78Mansión @L@371Mastaba @L@368Mausoleo @L@34Mensajes @L@48Dinero @L@15Pantalla&de&dinero @L@370Construcción&de&monumentos @L@35Calificación&de&monumentos @L@66Funeraria @L@L@372Obelisco @L@12Menú&de&opciones @L@18Superposiciones @L@24Supervisor&de&comercio @L@28Supervisor&de&los&entretenimientos @L@25Supervisor&de&los&graneros @L@27Supervisor&de&la&enseñanza @L@21Supervisor&militar @L@373Supervisor&de&los&monumentos @L@26Supervisor&de&salud&pública @L@29Supervisor&de&los&templos @L@30Supervisor&del&tesoro @L@20Supervisor&de&los&trabajadores @L@14Menú&de&supervisores @L@L@470Fabricante&de&pinturas @L@77Palacio @L@97Fabricante&de&papiro @L@73Pabellón @L@489Faro&de&Faros @L@64Médico @L@95Cantera&de&piedra&común @L@79Plaza @L@86Comisaría @L@22Supervisor&político @L@90Granja&de&granadas @L@16Pantalla&de&población @L@39Crecimiento&de&la&población @L@1Alfarero @L@35Calificación&de&prosperidad @L@L@95Cantera @L@L@35Calificaciones @L@23Supervisor&de&calificaciones @L@88Reclutador @L@94Recolector&de&juncos @L@51Religión @L@358Barrera @L@57Caminos @L@478Tumbas&reales&de&enterramiento @L@L@95Cantera&de&arenisca @L@68Escuela&de&escribas @L@41Escribas @L@74Casa&de&senet @L@82Carpintero&de&barcos @L@67Santuario @L@362Esfinge @L@79Estatua @L@375Pirámide&escalonada @L@363Gremio&de&canteros @L@4Almacén @L@4Almacén:&órdenes&especiales @L@69Templo&del&Sol @L@L@80Oficina&de&recaudadores&de&impuestos @L@67Templo @L@350Complejo&de&templos&a&Osiris @L@351Complejo&de&templos&a&Ra @L@352Complejo&de&templos&a&Ptah @L@353Complejo&de&templos&a&Seth @L@354Complejo&de&templos&a&Bastet @L@477Saqueador&de&tumbas @L@85Torre @L@47Comercio @L@75Centro&de&formación @L@367Barco&de&transporte @L@357Muelle&de&transporte @L@75Centros&de&formación&(artistas) @L@48Tributo @L@38Pirámide&verdadera @L@L@42Paseantes @L@85Muralla @L@52Guerra @L@365Barco&de&guerra @L@356Muelle&de&guerra @L@61Suministro&de&agua @L@98Armero @L@60Tejedor @L@62Pozo @L@94Leñador @L@8Campamento&de&trabajo @L@40Trabajadores @L@32Mapa&del&mundo @L@L@479Zoo @L@LHistoria @L@L@493Abu&Simbel @L@481Biblioteca&de&Alejandría @L@159Boticario @L@472Artesanos @L@L@380Bast,&Isis&y&Hathor @L@199Bazar @L@194Cerveza @L@386Albañiles @L@390Ladrillos @L@395Provisiones&funerarias @L@L@482Cesáreo @L@389Carpinteros @L@186Ganadería&y&pesca @L@166Niños @L@190Arcilla @L@L@171Danza @L@182Estructuras&defensivas @L@158Odontología @L@L@161Embalsamamiento @L@L@181Enemigos @L@165Entretenimiento @L@L@150Agricultura @L@393Festivales @L@189Lino @L@187Frutas&y&verduras @L@L@176Jardines&y&arte&público @L@191Oro&y&minería&de&oro @L@174Gobierno&y&burocracia @L@185Grano&y&cebada @L@5Granero @L@L@469Henna @L@152Viviendas @L@383Caza @L@L@388Inmigración @L@151Industria @L@154Riego @L@L@382Joyería @L@169Malabarismo @L@L@155Mano&de&obra @L@474Lámparas @L@183Leyes @L@164Biblioteca&y&literatura @L@398Lino&y&tejidos @L@197Artículos&de&lujo @L@L@495Grandes&plagas @L@381Malaria @L@394Mastaba @L@160Medicina @L@184Ejército @L@170Música @L@L@157Nilo @L@L@397Obelisco @L@476Aceite @L@376Osiris,&Sebek&y&Min @L@396Otros&monumentos @L@L@195Fabricación&de&papiro @L@175La&casa&del&faraón @L@487Faro&de&Faros @L@167Población @L@198Cerámica @L@384Sacerdotes @L@378Ptah,&Amón&y&Thot @L@176Arte&público @L@392Pirámides @L@L@193Canteras @L@L@377Ra,&Maat&y&Horus @L@188Juncos @L@399Religión @L@153Caminos @L@L@163Escuela&y&educación @L@387Escribas @L@379Set,&Anubis&y&Sejmet @L@172Senet @L@179Barcos&y&construcción&naval @L@162Santuario&y&templo @L@168Sociedad @L@391Esfinge @L@385Canteros @L@6Almacén @L@L@173Impuestos&y&dinero @L@177Comercio @L@L@475Valle&de&los&Reyes @L@L@196Armas @L@156Pozo&y&suministro&de&agua @L@192Madera&y&sus&usos @L@L@480Zoo"
                    }
                }

                message_file_menu {
                    id: 11
        
                    size [30, 28]
                    title { text: "Menú de archivo" }
                    subtitle { text: "Controles del juego" }
                    content {
                        text: "Desde el Menú de archivo puede iniciar una partida nueva, repetir la misión actual, cargar una partida guardada previamente, guardar la partida actual, eliminar una partida guardada y salir de Faraón."
                    }
                }
    
                message_optons_menu {
                    id: 12
        
                    size [30, 28]
                    title { text: "Menú de opciones" }
                    subtitle { text: "Controles del juego" }
                    content {
                        text: "Use el menú de opciones para cambiar el aspecto y el sonido de Faraón. Use la opción Pantalla para ajustar la vista y la opción Sonido para ajustar el volumen de los efectos, las voces y la música. El ajuste de Velocidad cambia el ritmo al que transcurre el tiempo en Faraón. Elija la versión de los nombres de las ciudades que prefiera (clásica o egipcia) seleccionando la opción Ciudades. Probablemente conozca los nombres clásicos, pero la opción egipcia aporta un poco más de autenticidad a Faraón. @PPara controlar la forma en que recibe los mensajes durante la partida, ajuste las opciones de Mensajes emergentes. La mayoría de los mensajes aparecen en una pantalla emergente. Cuando aparece, el juego se detiene hasta que cierre la pantalla. Las opciones de Mensajes emergentes le permiten desactivar esta función para algunos de los mensajes que recibe. En la lista de categorías, seleccione simplemente los tipos de mensaje que no quiere recibir como mensaje emergente haciendo clic en el nombre de la categoría. El nombre de la categoría aparecerá en amarillo, y los mensajes de esa categoría se mostrarán en una franja en la parte superior de la pantalla. También aparecerán en su @34lista&de&mensajes. No tendrá que dejar de gobernar la ciudad para atender el mensaje. Si selecciona 'Cumplimiento ahora posible' de la lista, los bienes solicitados se enviarán automáticamente desde los almacenes de la ciudad cuando el envío esté listo. Consulte la entrada del @22Supervisor&político para obtener más información sobre las peticiones.  @PPuede activar o desactivar la función de guardado automático del juego desde este menú. El guardado automático guarda su partida cada seis meses, lo que le ofrece una copia de seguridad fiable si olvida guardar manualmente o si tiene problemas con el ordenador. Siempre sobrescribe el mismo nombre de archivo, así que no hay peligro de llenar el disco duro con guardados automáticos. Puede desactivar esta función para eliminar las breves pausas mientras el juego se guarda.   @PPara cambiar el nivel de dificultad en cualquier momento de la partida, use la opción Dificultad. Tenga en cuenta, sin embargo, que su puntuación de la misión depende del nivel de dificultad elegido. Si cambia la dificultad a mitad de una misión, su puntuación se calculará según el nivel más fácil en el que haya jugado. @PPor último, la opción Aceleración de monumentos le permite contar con la ayuda de los dioses para construir algunos @370monumentos. Actívela y un dios podrá decidir bendecirle ayudándole a construir su monumento. Los dioses solo disfrutan trabajando en ciertos monumentos, concretamente en las pirámides y las mastabas."
                    }
                }

                message_help_menu {
                    id: 13
        
                    size [30, 28]
                    title { text: "Menú de ayuda" }
                    subtitle { text: "Controles del juego" }
                    content {
                        text: "El menú de ayuda enumera los temas sobre todo lo que necesita saber para jugar a Faraón. También puede seleccionar muchas entradas históricas de la parte inferior del Índice. @P'Ayuda del ratón' se refiere a los pequeños bocadillos de texto que aparecen cuando coloca el cursor sobre algo.  'Completa' muestra la ayuda del ratón para casi todo lo del juego.  'Algunas' desactiva la ayuda del ratón, con algunas excepciones como las @18vistas&de&superposición y los informes del Palacio de su ciudad.  'Ninguna' desactiva por completo la ayuda del ratón. @P'Advertencias' son los mensajes breves en forma de franja que aparecen en la parte superior de la pantalla.  Puede que quiera desactivarlas cuando le haya cogido el truco a Faraón."
                    }
                }
    
                message_overseers {
                    id: 14,
        
                    size [30, 28]
                    title { text: "Supervisores" }
                    subtitle {
                        text: "Controles del juego"
                    }
                    content {
                        text: "Use el menú de supervisores o haga clic en el botón Supervisores para visitar a un supervisor concreto.  El menú resulta útil cuando ha decidido ocultar el Panel de control. Los supervisores presentan información crucial sobre el estado de su ciudad en cada momento."
                    }
                }
    
    message_game_control_money_display_window {
        id: 15,
        
        size [30, 28]
        title {
            text: "Ventana de dinero",
        }
        subtitle {
            text: "Controles del juego",
        }
        content {
            text: "Muestra los debens del tesoro de la ciudad. Un número en amarillo indica deuda. Para más información sobre cómo generar ingresos, consulte @48dinero."
        }
    }
    
    message_game_control_population_display {
        id: 16,
        
        size [30, 28]
        title {
            text: "Visualización de población",
        }
        subtitle {
            text: "Controles del juego",
        }
        content {
            text: "Esta ventana muestra cuántas personas viven en la ciudad. Recuerde que no todos los habitantes de su ciudad son trabajadores. Siga este enlace para leer cómo funciona la @39población en el juego."
        }
    }
    
    message_game_control_date_display {
        id: 17,
        
        size [30, 28]
        title {
            text: "Ventana de fecha",
        }
        subtitle {
            text: "Controles del juego",
        }
        content {
            text: "Esta ventana muestra el mes y el año actuales. Por comodidad se usa el calendario moderno. Si el tiempo pasa demasiado deprisa o demasiado despacio para usted, use los Ajustes de velocidad del @12Menú&de&opciones."
        }
    }
    
    message_overlay_selector {
        id: 18,
        
        size [30, 28]
        title {
            text: "Selector de superposiciones",
        }
        subtitle {
            text: "Controles del juego",
        }
        content {
            text: "El Selector de superposiciones le permite ver la ciudad a través de distintos filtros. Las superposiciones son fundamentales para planificar la ciudad y gestionar sus servicios. @PCuando elige una superposición, solo ve los edificios y los transeúntes directamente relacionados con el informe elegido. El resto de edificios suele sustituirse por columnas. En la mayoría de los casos, las columnas indican el acceso a un determinado servicio o función de la ciudad. Cuanto más alta es la columna, mejor es el acceso del edificio al servicio. @PLas excepciones a la regla son las superposiciones de riesgos, la superposición de problemas, la superposición de atractivo y la superposición de ocultar acantilados. En las superposiciones de riesgos, las viviendas y otros edificios siguen sustituidos por columnas, pero cuanto más alta y roja es la columna, mayor es el riesgo. @PLa superposición de problemas muestra los edificios que no funcionan correctamente o que están a punto de sufrir un problema grave. Sobre el edificio aparecen iconos que indican el problema. Esta superposición también muestra a los empujadores de carros que se han detenido porque no tienen dónde llevar sus mercancías o alimentos. @PCon la superposición de atractivo seleccionada, el terreno de la ciudad se sustituye por bloques de distintos colores. Los bloques dorados indican las zonas que la gente considera más atractivas. Cuanto más marrón es el bloque, menos atractiva es la zona. Para más información sobre el atractivo, haga clic @56aquí. @PSi los acantilados le bloquean la vista, use la superposición de ocultar acantilados para aplanarlos temporalmente. Si tiene tumbas reales de enterramiento construidas en los acantilados, podrá verlas por dentro cuando haya seleccionado la superposición de ocultar acantilados. @PPor último, la superposición de agua también es algo distinta de las demás. El acceso a los aguadores se muestra con columnas azules que crecen en altura cuanto mejor es el acceso. Esta superposición también muestra qué terrenos pueden sostener estructuras relacionadas con el agua y qué terrenos tienen acceso a agua potable de un pozo. Los cuadrados azul oscuro marcan las viviendas que tienen agua de pozo, y los cuadrados azul claro indican qué terrenos tienen el agua subterránea necesaria para sostener un @62Pozo, @61Suministro&de&agua u otro edificio que necesite acceso a agua subterránea. @PLa mejor manera de familiarizarse con las distintas superposiciones es experimentar con ellas. Cuando entienda la información que proporcionan, podrá planificar su ciudad con más eficacia."
        }
    }

                message_control_panel_toggle {
                    id: 19,
        
                    size [30, 28]
                    title {
                        text: "Alternar panel de control",
                    }
                    subtitle {
                        text: "Controles del juego",
                    }
                    content {
                        text: "Este botón le permite ocultar o mostrar el Panel de control. Ocultar el panel le permite ver más de la ciudad, pero puede hacer algunos controles del juego menos cómodos. Su preferencia personal es lo único que debe tener en cuenta a la hora de decidir si oculta el panel o no."
                    }
                }

                message_overseer_workers {
                    id: 20,
        
                    size [30, 28]
                    title {
                        text: "Supervisor de los trabajadores",
                    }
                    subtitle {
                        text: "Control del juego",
                    }
                    content {
                        text: "Su Supervisor de los trabajadores lleva la cuenta de todo lo relacionado con su @43fuerza&de&trabajo: número de puestos vacantes por sector de empleo, número de trabajadores desempleados y la escala salarial anual actual por cada diez trabajadores. Le ayudará a gestionar los asuntos relacionados con sus trabajadores. @PTrabaje con el Supervisor de los trabajadores para fijar los salarios de su ciudad. En el panel del supervisor verá el salario que paga y el que prevalece en todo Egipto. Use los botones de desplazamiento para ajustar el salario que paga a sus trabajadores. Pagar a su gente más que otras ciudades de Egipto puede contribuir a aumentar la @39Opinión&de&la&ciudad y atraer la @39inmigración. Pagar menos ahorrará dinero a la ciudad, pero empeorará el ánimo de sus ciudadanos y podría provocar emigración.   @PTambién puede recurrir al Supervisor de los trabajadores para establecer prioridades de mano de obra. Si no fija una prioridad concreta, el supervisor asigna a los trabajadores como considera oportuno. Normalmente intenta cubrir primero los puestos de producción de alimentos, seguidos de la industria. Si quiere fijar una nueva prioridad principal, por ejemplo la militar, haga clic en la línea del ejército. Aparece un panel con números. Para establecer el ejército como prioridad principal, haga clic en el número uno. Aparece un símbolo de candado delante de la categoría militar, que indica que ha fijado su prioridad. Puede asignar una prioridad a cada sector de empleo.  @PUna advertencia: cuando fija una prioridad, el Supervisor de los trabajadores traslada a todos los trabajadores para cubrir primero ese sector de empleo concreto. Esto puede dejar algunos sectores sin ningún empleado. Su ciudad no sobrevivirá mucho tiempo si alguno de sus sectores de empleo se queda completamente vacío. En épocas de escasez de mano de obra, quizá tenga que cambiar las prioridades con frecuencia para asegurarse de que ningún sector quede desatendido durante demasiado tiempo. @POpción mejorada: cuando está activada la división de categorías de mano de obra, los almacenes y los muelles usan su propio sector de Almacenamiento & distribución, separado de la industria, de modo que cada uno puede tener su propia prioridad. @L@LPara una breve historia de la fuerza laboral del antiguo Egipto, haga clic @155aquí."
                    }
                }

                message_overseer_military {
                    id: 21,
        
                    size [30, 28]
                    title {
                        text: "Supervisor militar",
                    }
                    subtitle {
                        text: "Control del juego",
                    }
                    content {
                        text: "Su Supervisor militar vigila todas las @37compañías, los @365barcos&de&guerra y los @367barcos&de&transporte de la ciudad. @PSu Supervisor militar presenta tanto un informe del ejército como un informe de la armada.  En el informe del ejército, el supervisor le informa brevemente del número y el estado de cada compañía de la ciudad. Controla su moral y su nivel de experiencia, y también puede reservar una compañía para el servicio del reino y, si solo otra ciudad solicita ayuda, enviarla. Visite cualquiera de las compañías haciendo clic en el botón 'Ir a la compañía'.  También puede ordenar que una compañía regrese a su Fuerte desde el informe de estado del ejército. @PHaga clic en el botón de la esquina inferior derecha para ver el informe de estado de la armada, que le informa de todo lo que necesita saber sobre los barcos de guerra y de transporte.  Su supervisor informa del nivel de fatiga de la tripulación de cada barco de guerra y de la resistencia del casco.  También puede enviar barcos de guerra a ayudar al faraón o a otra ciudad, si es necesario.  Haga clic en 'Ir al barco de guerra' para visitar a una tripulación concreta, y en 'Volver al muelle' para enviar un barco de guerra de vuelta a su amarre. @PSu Supervisor militar también le informa de la actividad militar general en la ciudad y sus alrededores. Le avisará si se acercan enemigos o si alguien necesita los servicios de sus tropas o barcos de guerra. @PPara más información sobre la guerra en Faraón, haga clic @52aquí. @L@LLos antiguos egipcios levantaron poderosos ejércitos y armadas. Haga clic @184aquí para saber más sobre la guerra en la antigüedad."
                    }
                }
    
                            message_overseer_political {
                                id: 22,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor político",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor político gestiona sus relaciones con el resto de Egipto.   @PEl Supervisor político lleva la cuenta de todas las solicitudes de suministros, ya sean de otras ciudades o del faraón. Sabe cuánto de la mercancía solicitada tiene disponible la ciudad en sus @4Almacenes y le avisará cuando pueda atender la solicitud. Entonces puede ordenar a su Supervisor político que envíe los bienes. En general, conviene atender las solicitudes del faraón o de otras ciudades lo antes posible. Ignorar por completo una solicitud puede reducir el @47comercio, e incluso provocar un ataque contra su ciudad. Enviar los bienes con retraso es mejor que no enviarlos nunca. @PEl Supervisor político también le ayuda a gestionar los ahorros de su familia. Sabe cuánto ha ahorrado y cuál es su nivel de salario actual. Los ahorros familiares se transfieren de una misión a otra, salvo que el gobierno centralizado de Egipto se desmorone (entre cada Período). Su Supervisor político cambiará su salario si usted lo ordena. Basta con hacer clic en el botón que muestra su salario actual y, cuando aparezca la lista de títulos con sus salarios asociados, elegir un nuevo nivel de salario en esta pantalla. Tenga en cuenta que sus compatriotas miran con malos ojos a quienes se pagan más de lo que merece su rango. @PSi desea gastar parte de los ahorros de su familia, el Supervisor político se encargará de la transacción. Puede enviar un regalo a Egipto (a otros líderes políticos o al pueblo de otras ciudades) o donar al tesoro de su ciudad. @PEnviar un regalo a Egipto puede aumentar su @35Calificación&del&reino. Si su familia tiene ahorros suficientes, puede elegir entre tres regalos. Aun así, no sea demasiado generoso. Si envía regalos con demasiada frecuencia, los destinatarios empiezan a esperarlos y pueden enfadarse si dejan de llegar. También tienden a esperar que cada regalo sea más valioso que el anterior. Cuando decida enviar un regalo, el Supervisor político se asegurará de que llegue intacto. @PTambién puede donar los ahorros de su familia al tesoro de la ciudad. Puede ser una buena idea, sobre todo si esos ahorros pueden evitar que la ciudad entre en deuda. Las deudas pueden salir muy caras. El reino prestará dinero a su ciudad, pero los préstamos tienen un coste. Para más información sobre el dinero de su ciudad, haga clic @48aquí. @PPor último, su Supervisor político conoce su calificación en el reino y la actitud general de Egipto hacia usted. Una fuente de información más útil sobre las calificaciones es su @23Supervisor&de&calificaciones."
                                }
                            }
    
                            message_overseer_ratings {
                                id: 23,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de calificaciones",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor de calificaciones muestra las calificaciones actuales de la ciudad en Cultura, Prosperidad, Monumentos y reino, junto con su objetivo de población. Al hacer clic en una calificación, el Supervisor de calificaciones le indica la mejor manera de mejorarla o qué la limita. Puede ver lo cerca que está la ciudad de alcanzar sus objetivos de calificación observando las columnas situadas sobre cada calificación. Cuando alcance el objetivo fijado para la ciudad al principio de su mandato, la columna se llena hasta el máximo. Aunque haya alcanzado su calificación de monumentos, la columna no se llena (y el objetivo no se cumple) hasta que el Supervisor de monumentos haya enviado todas las provisiones funerarias necesarias. @PSi la ciudad tiene un @77Palacio, puede consultar rápidamente sus calificaciones pasando el ratón sobre el Palacio. Aparece una pequeña ventana con las calificaciones y la tasa de desempleo de la ciudad. @PPara información más detallada sobre las calificaciones y su papel en el juego, haga clic @35aquí."
                                }
                            }
    
                            message_overseer_commerce {
                                id: 24,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de comercio",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor de comercio supervisa las @46industrias y los @4Almacenes de la ciudad, y lleva la cuenta de la oferta, la demanda y los precios de los bienes en todo el mundo. Sabe cuánto de cada producto se almacena en la ciudad y le indica si un artículo puede importarse o exportarse.   @PSu Supervisor de comercio también le informa del estado actual de cada industria. Visítelo para activar o desactivar las industrias de la ciudad, o para acumular un determinado bien en los Almacenes de la ciudad. Cuando un bien se acumula, crece rápidamente en los Almacenes porque nadie puede usarlo. No puede comerciarse, y los compradores del Bazar no pueden conseguirlo para sus clientes. Si se acumula una materia prima, no se entregará ningún envío de ese producto a su fabricante correspondiente. Quizá quiera acumular algún artículo para una futura solicitud prevista, o acumular una materia prima antes de construir las industrias que la necesitan.   @PPara cerrar una industria o acumular un producto, haga clic en un artículo de la lista del Supervisor de comercio. En el panel que aparece verá botones con las distintas opciones. @PSu Supervisor de comercio también le ayuda a establecer el flujo comercial. Determina qué productos pueden importarse o exportarse, según las rutas comerciales que haya abierto. Una vez que decida comerciar con un artículo, visítelo y especifique qué artículos comerciar haciendo clic en ellos. Puede indicarle cuánto debe conservarse en los Almacenes de la ciudad, o confiar en su criterio y permitirle importar y exportar alimentos y bienes como considere oportuno. El Supervisor lleva mucho tiempo haciendo su trabajo y toma decisiones acertadas sobre la cantidad de cada producto que su ciudad debe tener a mano. @PAl importar, su Supervisor sigue comprando un bien mientras la ciudad tenga menos de la cantidad que usted haya elegido (o, si usa su propio criterio, intenta comprar lo justo para mantener un pequeño excedente en los almacenes de la ciudad). Al exportar, su Supervisor vende bienes siempre que la ciudad tenga más de la cantidad elegida. Si lo deja a su criterio, evalúa si su ciudad necesita cada producto para sus propios fines y se niega a vender más de lo que cree que necesita para que todo funcione sin problemas. El Supervisor está muy atento a los cambios de tamaño de la población y revisa sus decisiones a medida que fluctúan las cifras de la ciudad. @PLas entradas sobre la @46industria, los @45alimentos y el @47comercio le ayudarán a entender los matices de un comercio exitoso."
                                }
                            }
    
                            message_overseer_granaries {
                                id: 25,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de los graneros",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Alimentos y población van de la mano. El Supervisor de los graneros lleva la cuenta de la población de la ciudad y de los alimentos que consume. @PEl Supervisor de los graneros presenta la información sobre la población de su ciudad en tres gráficos diferentes. Por defecto, el primer gráfico que ve es el de Historial de población. Este gráfico muestra cómo ha crecido o disminuido su población con el tiempo. Si su ciudad va bien, este informe mostrará un crecimiento más o menos continuo.  @PA la derecha del gráfico de Historial de población hay dos gráficos más pequeños: el gráfico de Censo y el gráfico de Sociedad. Haga clic en uno de ellos para ampliarlo y colocarlo en el centro de la pantalla.   @PEl gráfico de Censo muestra el desglose demográfico de su población por edad, útil para prever el crecimiento o la contracción de la @43fuerza&de&trabajo. Los niños y los ancianos no trabajan, pero sí siguen comiendo alimentos, bebiendo cerveza y rompiendo cerámica.  @PEl gráfico de Sociedad muestra el desglose de sus ciudadanos por ingresos, medidos según la calidad de sus viviendas. Los residentes muy ricos @41(escribas) tampoco realizan trabajos manuales, de modo que, a medida que su ciudad se enriquece, su fuerza de trabajo tiende a disminuir. Aunque no contribuyen a la reserva de mano de obra, los escribas pagan muchos impuestos a las arcas de su Palacio. @PDebajo de los gráficos hay varias líneas de información muy útil. La primera línea le indica cuántas personas puede sostener su nivel actual de producción de alimentos, así como las tendencias previstas de población según los niveles actuales de inmigración y emigración. Este Supervisor también sabe cuántas personas pueden alojar las viviendas vacías de la ciudad, cuántos alimentos tienen almacenados los graneros de la ciudad y cuántos inmigrantes llegaron durante el mes anterior. @PConsultar las entradas sobre la @39Población y los @45Alimentos puede ayudarle a entender la importancia del Supervisor de los graneros."
                                }
                            }
    
                            message_overseer_public_health {
                                id: 26,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de salud pública",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor de salud pública informa sobre el estado general de salud de la ciudad. Lleva la cuenta de los @64consultorios&de&médicos, @63consultorios&de&dentistas, @65boticas y @66funerarias que funcionan en la ciudad. Para información más específica sobre la cobertura sanitaria en determinadas zonas de la ciudad, use la @18superposición&de&salud. @PSu Supervisor de salud pública sabe si un riesgo sanitario concreto, como la malaria o una enfermedad, amenaza la ciudad. También lleva la cuenta de la actitud general de sus habitantes hacia los servicios sanitarios.  @PLa entrada sobre la @53Salud le ayudará a entender los efectos de la salud en toda la ciudad."
                                }
                            }
    
                            message_overseer_learning {
                                id: 27,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de educación",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor de educación le informa del estado de la educación en la ciudad.  Le indica el número de @68Escuelas&de&escribas y @70Bibliotecas activas, y cuántas personas pueden beneficiarse de las estructuras educativas existentes.  Evalúa si el acceso a la educación es adecuado e informa también de las peticiones de nuevas estructuras educativas que hagan los ciudadanos.  @PPara ver la cobertura en zonas concretas de la ciudad, use la @18superposición&de&educación. Además, consulte la entrada sobre la @50educación para más información. @L@LPara saber más sobre la educación en el antiguo Egipto, haga clic @163aquí."
                                }
                            }
    
                            message_overseer_diversions {
                                id: 28,
        
                                size [30, 28]
                                title { text: "Supervisor de entretenimiento" }
                                subtitle { text: "Control del juego"  }
                                content {
                                    text: "Su Supervisor de entretenimiento sabe cuántos escenarios de malabaristas, escenarios de músicos y escenarios de bailarines funcionan en la ciudad.  El número de escenarios importa mucho más que cuántos @71puestos, @72quioscos de música y @73pabellones existen, por eso no se molesta en enumerarlos.  También informa del número de @74Casas&de&senet y @479zoológicos que entretienen al público.  Calcula cuántas personas pueden beneficiarse de los escenarios, zoológicos y casas de senet de su ciudad y mide la satisfacción de los ciudadanos con sus opciones de entretenimiento.  @PPuede consultar la entrada sobre el @49entretenimiento para saber más sobre su papel en la ciudad. @L@LPara saber más sobre el entretenimiento en el antiguo Egipto, haga clic @165aquí."
                                }
                            }

                            message_overseer_temples {
                                id: 29,
        
                                size [30, 28]
                                title {
                                    text: "Supervisor de los templos",
                                }
                                subtitle {
                                    text: "Control del juego",
                                }
                                content {
                                    text: "Su Supervisor de los templos sabe qué dioses se adoran en la ciudad y si la ciudad tiene un dios patrón.  Quizá lo más importante es que también lleva la cuenta de la actitud de cada dios.  Informa de cuántos santuarios, templos y complejos de templos funcionan en la ciudad y si la gente exige más acceso a las instalaciones religiosas.  También puede ayudar a planificar un festival.  @PCuando quiera celebrar un festival en su ciudad, haga clic en el botón 'Celebrar nuevo festival'. Elija a qué dios honrar y el tamaño del festival. Debido al coste y al tiempo que supone planificar con éxito un festival, una ciudad solo puede celebrar dos festivales en cualquier periodo de 12 meses. Tenga en cuenta que también debe tener una @366Plaza&de&festivales en la ciudad antes de poder celebrar un festival. Para celebrar un Gran festival, la ciudad también debe tener cerveza suficiente para todos. @PEl Supervisor de los templos también le indicará las preocupaciones específicas de los ciudadanos en materia religiosa. @PLea sobre la @51religión para saber más sobre el valor de apaciguar a los dioses. @L@LLa religión era la base de la vida en el antiguo Egipto. Haga clic @399aquí para más información."
                                }
                            }

                            message_overseer_treasury {
                                id: 30,
        
                                size [30, 28]
                                title { text: "Supervisor del tesoro" }
                                subtitle { text: "Control del juego" }
                                content {
                                    text: "Su Supervisor del tesoro registra cada debens que entra o sale de las arcas de la ciudad. Examinar su hoja de cálculo le ayuda a evaluar dónde puede reducir costes o aumentar los ingresos. @PLa información resumida sobre impuestos se encuentra en la parte superior de la pantalla del Supervisor del tesoro. Use los botones de desplazamiento junto al tipo impositivo para ajustarlo.  Sus ciudadanos consideran razonable el ajuste predeterminado del 9 por ciento. Subir el tipo muy por encima del 9 por ciento puede enfadar a sus ciudadanos y disuadir la inmigración, o incluso provocar que la gente se marche. Cuanto más tiempo mantenga los impuestos en niveles altos, más enfadada se pondrá la gente. Para más información sobre el Sentimiento de la ciudad, haga clic @39aquí. @PEl resumen también muestra cuántos impuestos se han recaudado, cuántos ciudadanos están registrados para pagarlos y cuánto dinero no se recaudó por falta de recaudadores de impuestos suficientes. Para ver qué zonas de la ciudad evitan pagar sus impuestos, use la @18superposición&de&impuestos.  Tenga en cuenta también que los ciudadanos se irritan mucho si tienen que pagar impuestos mientras otros barrios de la ciudad no lo hacen.   @PA continuación del resumen hay una hoja de cálculo. Las partidas situadas en la parte superior de la hoja detallan los ingresos de la ciudad por impuestos, regalos y exportación de mercancías.   @PDebajo de la escasa lista de fuentes de ingresos hay una lista más extensa de los gastos de la ciudad. En general, los salarios y los costes de construcción serán las partidas más importantes, aunque las importaciones también pueden resultar muy caras. @PA la izquierda de la lista aparece el rendimiento del año anterior, para poder comparar. Así puede ver si un gasto concreto se dispara fuera de control respecto al año anterior. @PLa entrada sobre el @48dinero ofrece más consejos sobre presupuestos. La entrada sobre los @80Recaudadores&de&impuestos también es útil. @L@LHaga clic @173aquí para más información sobre el dinero en el antiguo Egipto."
                                }
                            }
    
                            message_chief_overseer {
                                id: 31,
        
                                size [30, 28]
                                title { text: "Supervisor jefe" }
                                subtitle { text: "Control del juego" }
                                content {
                                    text: "El Supervisor jefe consulta a todos sus demás supervisores para ofrecer un esbozo general del estado de la ciudad. Es buena persona a la que visitar cuando no está seguro de lo que su ciudad necesita más. Los asuntos urgentes que requieren atención inmediata aparecen en amarillo. Los problemas graves aparecen en blanco. Haga clic en cualquier problema para recibir consejos sobre cómo abordarlo y enlaces a otros consejeros que podrían ayudarle más. @PSu Supervisor jefe también le proporciona la última lectura del Nilómetro. El Nilómetro predice la inundación de la próxima temporada. @PSus demás supervisores informan al Supervisor jefe, y debe considerar con atención lo que tiene que decirle. Tiene una idea mejor del estado general de su ciudad que nadie, excepto usted mismo. Atender a sus advertencias a tiempo podría salvar a su ciudad del desastre."
                                }
                            }

                            message_world_map {
                                id: 32,
        
                                size [30, 28]
                                title { text: "El mapa del mundo" }
                                subtitle { text: "Controles del juego" }
                                content {
                                    text: "El Mapa del mundo le muestra otras ciudades importantes del mundo. Quizá su función más importante sea identificar a los @47socios&comerciales. @PLas ciudades que izan una bandera comerciarán con usted. Haga clic en una ciudad con bandera para ver qué artículos quiere comerciar, así como el coste de abrir una ruta comercial.  Cada mercancía que la ciudad compra o vende tiene de una a tres puntos azules que indican su nivel de oferta o demanda: un punto significa que apenas comercian con ese bien, mientras que tres puntos señalan un fuerte deseo de comerciar con ese artículo.   @PHaga clic en el botón 'Abrir ruta comercial' para iniciar las relaciones.  El tesoro de su ciudad paga de inmediato la apertura de la ruta, y el comercio puede empezar al instante.   @PSi ha enviado compañías o barcos de guerra para servir al reino, puede seguir sus viajes en el Mapa del mundo.  También puede seguir el avance de los ejércitos o armadas enemigos que se dirijan a su ciudad. @PLea las entradas sobre el @47comercio, la @52guerra y el @24Supervisor&de&comercio para saber más sobre el uso del Mapa del mundo."
                                }
                            }

                            message_building_buttons {
                                id: 33,
        
                                size [30, 28]
                                title { text: "Botones de edificios" }
                                subtitle { text: "Controles del juego" }
                                content {
                                    text: "Estos botones le permiten colocar estructuras en el terreno. El precio del edificio aparece en su botón. Cuando selecciona una estructura para construir, una imagen fantasmal de color verde se adhiere a su cursor. Cuando pasa el cursor sobre terreno edificable, la imagen es verde; en terreno no apto, la imagen verde se convierte en un rombo rojo. @PPuede consultar la ayuda de cada edificio haciendo clic con el botón derecho del ratón en las estructuras existentes, o elegirlo en la sección 'Edificios' del @10Índice."
                                }
                            }
    
                            message_game_control_messages {
                                id: 34,
        
                                size [30, 28]
                                title { text: "Mensajes" }
                                subtitle { text: "Controles del juego" }
                                content {
                                    text: "Cuando ocurre un suceso notable en la ciudad o en otro lugar del reino, recibe un mensaje que lo describe.  Algunos de estos mensajes son urgentes y exigen una respuesta rápida por su parte.  Pueden ser solicitudes del faraón u otras ciudades, o pueden llamar su atención sobre un punto problemático de su ciudad. @PCuando llega un mensaje nuevo, el botón 'Mensaje' del Panel de control se ilumina y suena un aviso.  Haga clic en el botón para leer el mensaje.  Si el asunto es extremadamente urgente, el mensaje se le entrega directamente y aparece en pantalla automáticamente.  Si el mensaje le avisa de algún problema en su ciudad, puede hacer clic en el botón de alarma dentro del mensaje para ir directamente al punto problemático.   @POtros mensajes contienen instrucciones que le ayudan a gestionar la ciudad con más éxito.  Son guías útiles que enseñan conceptos importantes del juego y fijan objetivos a corto plazo.  Cumplir los objetivos a corto plazo que se indican en estos mensajes especiales le permite ganar una misión y pasar a la siguiente etapa.  Estos mensajes se marcan con un pergamino azul en la lista de mensajes. @PPuede borrar mensajes individuales haciendo clic con el botón derecho en sus títulos en la lista de mensajes.  Un botón en la parte inferior del panel le permite eliminar de una vez todos los mensajes ya abiertos, aunque no borra los mensajes no leídos ni los del pergamino azul (tutorial).  Una vez que elimina un mensaje de la lista, desaparece para siempre. Por supuesto, puede optar por conservar el mensaje para futuras consultas. @PLos jugadores expertos quizá quieran desactivar ciertos mensajes emergentes desde el @12menú&de&opciones.  Cuando active esta opción, los mensajes aparecen en la parte superior de la pantalla y también se añaden a su cuadro de mensajes."
                                }
                            }

                            message_ratings {
                                id: 35,
        
                                size [30, 28]
                                title { text: "Calificaciones" }
                                subtitle { text: "Concepto del juego" }
                                content {
                                    text: "Las calificaciones indican lo bien que está la ciudad o lo bien que lo está haciendo como líder. Se usan cuatro calificaciones distintas para medir la ciudad: Cultura, Prosperidad, Reino y Monumentos. @L@LCultura @LLa calificación de Cultura evalúa el acceso de sus ciudadanos al @49entretenimiento, a la @50educación, a la @53salud y a la @51religión. La calificación de Cultura mide no solo el número de instalaciones que tiene, sino también la variedad de opciones. Para obtener una calificación de Cultura alta, asegúrese de ofrecer a los ciudadanos muchas opciones. Esto significa acceso fácil a varias formas de entretenimiento, a servicios de salud (salvo las boticas, que no afectan a la calificación de Cultura) y a la religión.   @PPara los ciudadanos más ricos, el acceso tanto a las bibliotecas como a las escuelas de escribas es imprescindible para que la calificación de Cultura siga subiendo, pero el acceso no lo es todo.  La gente aprende mejor en instalaciones tranquilas y poco concurridas, y su calificación de Cultura refleja la calidad de la educación, midiendo cuánta gente usa cada escuela y biblioteca.  Es posible tener suficientes edificios educativos para dar acceso a todas las casas de la ciudad y, aun así, sufrir hacinamiento. @PPara obtener la calificación de Cultura más alta, vea si puede construir un @479zoológico. Necesitará uno si quiere alcanzar una calificación de Cultura superior a 75. Haga clic en el botón de Entretenimiento para ver si un zoológico figura entre sus opciones de entretenimiento.  @L@LProsperidad @LLa calificación de Prosperidad mide la riqueza de una ciudad y su seguridad financiera.  Va mucho más allá de la evaluación del tesoro de la ciudad: también examina la riqueza de sus ciudadanos, teniendo en cuenta el valor de sus propiedades y el nivel de desempleo.   @PSi la ciudad obtiene beneficios cada año, su calificación de Prosperidad debería seguir subiendo si nada más en la ciudad la frena. El desempleo elevado, las viviendas de bajo nivel y los salarios bajos frenarán su crecimiento. No pagar tributo al reino también reducirá esta calificación. Si funciona en la ciudad un Complejo de templos o una Casa de senet, su calificación de Prosperidad sube, porque la gente considera que la ciudad es próspera si tiene estructuras tan gloriosas. Terminar un monumento también impulsa la calificación de Prosperidad.  Cuando la ciudad cierra el año con deudas o pierde dinero, la calificación de Prosperidad se resiente. Sin embargo, si la ciudad perdió dinero por costes de construcción, su calificación de Prosperidad no se ve afectada, porque los gastos en construcción mejoran la ciudad.    @L@LReino @LLa calificación del Reino representa su reputación, sobre todo ante el resto de Egipto. Responder con rapidez a la petición de ayuda de un aliado puede subir la calificación.  No atender las solicitudes, o no pagar un @48tributo anual por culpa de las deudas de la ciudad, perjudicará la calificación del Reino. Si la calificación del Reino cae demasiado, su mala reputación podría provocar un ataque del faraón o de una ciudad vecina. @PNormalmente empieza cada misión con una calificación de 50, que indica neutralidad.  La gente de fuera de su ciudad apenas ha oído hablar de usted, y quienes conocen su nombre y su historia tienen pocas opiniones sobre usted.  Con el tiempo, si no hace nada por mejorarla, su calificación del Reino baja poco a poco a medida que se corre la voz de que usted tiene poca importancia más allá de los límites de su ciudad. La calificación cae con más fuerza si pierde o ignora batallas lejanas, si no atiende las solicitudes de mercancías u otras exigencias del resto del reino, y si permanece en @48deuda durante cierto tiempo.  Cobrar un salario superior al estándar de su rango tampoco ayuda. @PSu calificación del Reino también bajará si @477ladrones&de&tumbas saquean @374provisiones&funerarias de una tumba bajo su vigilancia. Los demás egipcios pensarán que no respeta debidamente a los muertos.  @PPara subir su calificación del Reino, atienda con prontitud las solicitudes del faraón o de otras ciudades egipcias, sobre todo cuando piden ayuda militar.  La victoria en batalla puede hacer maravillas por su reputación.  A veces, incluso perder una batalla ayuda un poco, ya que al menos intentó rescatar a sus compatriotas en su hora de necesidad. @PPara una mejora rápida de su reputación, use los ahorros de su familia para comprar un regalo para Egipto.  Su Supervisor político envía el regalo que usted elija al faraón, a otros líderes egipcios o al pueblo de Egipto, allí donde considere que será más útil.  Su calificación del Reino subirá unos puntos de inmediato.  Resista la tentación de gastar todos sus ahorros en regalos. Pierden efecto si son demasiado frecuentes, y los destinatarios acabarán esperándolos.  Con el tiempo, su calificación incluso podría bajar si deja de enviar regalos o envía regalos más baratos de lo que los destinatarios han llegado a esperar. Más de un regalo al año tiene una eficacia dudosa, e incluso podría resultar contraproducente. @PCapturar a un ladrón de tumbas también es bien visto por sus compatriotas, y su calificación del Reino aumenta ligeramente por cada ladrón de tumbas que capturen sus guardias. @PLa tendencia natural de la calificación del Reino a bajar se atenúa un poco si cobra un salario personal inferior al definido para su rango. No cobrar ningún salario es aún mejor para su reputación como servidor público desinteresado, aunque no es la mejor estrategia para aumentar la riqueza de su familia!     @L@LMonumentos @LLa calificación de Monumentos depende tanto del tamaño y alcance de los monumentos de la ciudad como de lo avanzada que esté su construcción. Si completa todos los monumentos requeridos y recuerda enviar las provisiones funerarias necesarias para asegurar la vida después de la muerte del difunto, no tendrá problemas para cumplir el objetivo de calificación de Monumentos. @L@LUna visita a su @23Supervisor&de&calificaciones le mostrará su situación actual. Al hacer clic en una calificación, su Supervisor de calificaciones le aconsejará cómo mejorarla."
                                }
                            }

                            message_city_crime {
                                id: 36
        
                                size [30, 28]
                                title { text: "Delincuencia" }
                                subtitle { text: "Concepto del juego" }
                                content {
                                    text: "La delincuencia nace de una mala @39Opinión&de&la&ciudad. La gente puede estar descontenta por diversas razones (falta de alimentos, salarios bajos, impuestos altos, desempleo elevado), pero su ánimo debe estar especialmente mal para que estalle la delincuencia. @PLa mejor manera de prevenir la delincuencia, por tanto, es mantener contenta a la gente.  Proporcionar abundantes bienes y servicios ayuda mucho a lograrlo. También puede prevenir la delincuencia construyendo @76Tribunales y @86Comisarías&de&policía por toda la ciudad. La presencia de ambas estructuras desalienta a los posibles delincuentes. @PPese a sus mejores esfuerzos, algunas zonas de la ciudad pueden producir delincuentes, sobre todo residentes de zonas muy industrializadas. Si estalla la delincuencia, un guardia de una comisaría reducirá a cualquier delincuente que detenga. @PSi el delincuente escapa a la vista de un guardia, se dirigirá directamente a uno de los edificios de la ciudad donde se guarda dinero. No hará mucha distinción entre el tesoro de la ciudad y los ahorros de su familia. Robará de cualquiera de las dos fuentes. Una vez que haya robado oro, se ocultará y no volverá a robar... por ahora. @PLa delincuencia también puede producir @477ladrones&de&tumbas, pero solo si su ciudad es el lugar de descanso final de uno de los grandes de Egipto y alberga una tumba (pirámide, mastaba, mausoleo o tumba real de enterramiento). Los ladrones de tumbas son especialmente hábiles para entrar y saquear los tesoros de las tumbas reales de enterramiento. @PA veces, la codicia puede corromper incluso a los ciudadanos más felices. Estos ciudadanos codiciosos se reúnen con sus amigos y especulan sobre las lujosas provisiones funerarias que se entierran con los nobles difuntos. Cuando esa ansia de riquezas puede con ellos, estalla una ola de delincuencia y estos ciudadanos se convierten en ladrones de tumbas. Como no puede ver en el corazón de sus ciudadanos, no tiene forma de saber cuándo se producirá una ola de delincuencia. Sin embargo, los guardias golpearán sin dudar a cualquiera que intente profanar una tumba robando sus provisiones funerarias."
                                }
                            }
    
                            message_fort_and_company {
                                id: 37,
        
                                size [30, 28]
                                title {
                                    text: "Fuerte y compañía",
                                }
                                content {
                                    text: "El ejército de su ciudad se llama 'batallón'.  Cada soldado del batallón está asignado a una compañía, y cada compañía tiene su propio Fuerte.  Una ciudad puede tener como máximo seis Fuertes.  Los tipos de compañías y Fuertes son: @L@LInfantería @LLos infantes son el núcleo de la mayoría de los ejércitos.  Especialistas en el combate cuerpo a cuerpo, luchan en primera línea de batalla.  Avanzan a una velocidad media.  Salen del @88Reclutador armados con lanzas.  No puede construir un Fuerte de infantería a menos que su ciudad tenga un Fabricante de armas o pueda importarlas. @L@LArqueros @LCon sus flechas, los arqueros pueden atacar al enemigo desde más lejos que la infantería, pero son pésimos en el combate a corta distancia y no aguantan mucho si el enemigo los ataca directamente.  Marchan algo más despacio que la infantería.  Los arqueros fabrican sus propios arcos y flechas, así que puede construir Fuertes de arqueros aunque su ciudad no tenga Fabricante de armas. @L@LCarros de combate @LNada asusta más a los soldados que ver una línea de carros lanzada contra ellos.  Los carros son clave para romper las formaciones defensivas del enemigo, y una vez rotas sus líneas, será más fácil derrotarlo.  Cada auriga recibe un carro al salir del Reclutador, siempre que su ciudad tenga un Fabricante de carros y un suministro de madera. @L@LLos soldados de todos los tipos prefieren quedarse en sus Fuertes cuando no combaten, y permanecen allí a menos que usted les ordene salir a campaña. La asignación prolongada en campaña reduce la moral de la compañía.  @PLos Fuertes no necesitan acceso a caminos ni trabajadores.  Tienen un efecto muy negativo en la deseabilidad, así que lo mejor es situarlos en las afueras de la ciudad.  Al planificar la ubicación de sus Fuertes, recuerde que el terraplén entre la llanura aluvial y el terreno seco es intransitable, salvo donde un camino conecte ambos terrenos. @PConsulte la entrada sobre @87Órdenes&de&la&compañía para saber lo que pueden hacer los soldados. La entrada sobre la @52guerra también puede serle útil. @L@LPara saber más sobre la guerra en el antiguo Egipto, haga clic @184aquí."
                                }
                            }
    
                            message_true_pyramid {
                                id: 38,
        
                                size [30, 28]
                                title {
                                    text: "Pirámide verdadera",
                                }
                                content {
                                    text: "La Pirámide verdadera tiene un núcleo de @95piedra&sencilla y un revestimiento de @95caliza alisado y pulido.  Los canteros del @363Gremio&de&canteros colocan la piedra y pulen la superficie, mientras que los carpinteros del @363Gremio&de&carpinteros preparan las rampas necesarias para la construcción a medida que la Pirámide se eleva cada vez más.  Cuando un @4Almacén acumula cuatro bloques de piedra, los campesinos arrastran un trineo cargado de piedra hasta el lugar del monumento, donde esperan los canteros. @PLas Pirámides verdaderas pueden ser pequeñas, medianas, grandes, Complejo piramidal o Gran complejo piramidal. @PConsulte las entradas sobre @370Construcción&de&monumentos, el @373Supervisor&de&los&monumentos y el @369Capataz&de&obras para obtener más información. @L@LLas pirámides son la carta de presentación del antiguo Egipto y los monumentos por los que el país es más conocido.  Haga clic @392aquí para saber más sobre las pirámides y su construcción."
                                }
                            }

                            message_population_groth_and_sentiment {
                                id: 39,
        
                                size [30, 28]
                                title {
                                    text: "Crecimiento de la población y opinión de la ciudad",
                                    pos [15, 5]
                                }
                                subtitle {
                                    text: "Concepto del juego",
                                }
                                content {
                                    text: "Cuando su ciudad es nueva, los inmigrantes llegan con entusiasmo y con sus escasas pertenencias, llenos de esperanza ante nuevas oportunidades. A medida que la ciudad se consolida, necesita ofrecer más servicios para atraer nuevos inmigrantes y retener a los que ya tiene. La mejor manera de evitar que los residentes emigren es mantenerlos de buen ánimo, lo que se refleja en una buena Opinión de la ciudad. @PLa clave para que los ciudadanos estén contentos es proporcionarles en abundancia lo básico: agua limpia, buena comida y empleo. Una vez cubiertas estas necesidades, ofrezca los servicios que enriquecen sus vidas.  Pagar salarios competitivos y cobrar un tipo impositivo razonable también ayuda.  La ciudad debería seguir creciendo mientras siga proporcionando lo necesario a las necesidades básicas de los ciudadanos. @PSi no atiende las necesidades de los ciudadanos, puede desencadenarse una ola de emigración.  La emigración puede convertirse en un círculo vicioso: la gente se marcha por falta de servicios, pero al marcharse provoca escasez de trabajadores. Esa escasez hace que los servicios empeoren aún más. Debe evitar a toda costa que las condiciones de la ciudad empeoren tanto que la gente se vaya en masa. @PLa población también puede crecer o menguar por nacimientos y muertes. Consulte con frecuencia a su @25Supervisor&de&los&graneros para vigilar la edad media de la población de la ciudad. Cuando los trabajadores alcanzan cierta edad, se jubilan, y puede producirse una escasez de trabajadores bastante repentina si una gran parte de la población llega a la edad de jubilación. Si nota que su población envejece, tome medidas para atraer nuevos inmigrantes, que suelen ser más jóvenes. @PAdemás de fomentar la emigración, una mala Opinión de la ciudad también favorece la @36delincuencia. @PSi necesita una solución rápida a una mala Opinión de la ciudad, organice un @51festival suntuoso o grandioso. El festival distrae a la gente de sus problemas, y la alegría genera una sensación agradable en los ciudadanos. Sin embargo, los festivales son solo una solución temporal. Si no corrige los problemas de fondo que causaron la mala Opinión de la ciudad, el ánimo de los ciudadanos volverá a empeorar. @L@LPara saber más sobre el crecimiento de la población en el antiguo Egipto, haga clic @167aquí. Conozca más sobre los distintos inmigrantes del antiguo Egipto haciendo clic @388aquí."
                                }
                            }
    
                            message_game_concept_workers {
                                id: 40,
        
                                size [30, 28]
                                title { text: "Trabajadores" }
                                subtitle { text: "Concepto del juego" }
                                content {
                                    text: "Los trabajadores son la sangre de la ciudad. Sus esfuerzos producen todos los bienes y servicios que disfruta cada ciudadano.  Atender a estas humildes personas debe ser una de sus principales preocupaciones. Sin ellos, la ciudad no puede sobrevivir. @PCuando construye la mayoría de los edificios nuevos, estos envían un agente en busca de trabajadores. Si encuentran viviendas ocupadas dentro de su radio de contratación, y si la ciudad tiene suficientes trabajadores desempleados en total, el edificio tendrá acceso a mano de obra. @PAunque los trabajadores no se quejan mucho de su suerte (bueno, sí se quejan bastante), tienen metas y aspiraciones. Sueñan con formar algún día parte de la clase de los @41escribas. @L@LConozca cómo era trabajar en el antiguo Egipto haciendo clic @155aquí."
                                }
                            }

                            message_game_concept_scribes {
                                id: 41,
        
                                size [30, 28]
                                title { text: "Escribas" }
                                subtitle { text: "Concepto del juego" }
                                content {
                                    text: "Los @40trabajadores que se esfuerzan mucho, ahorran y guardan sus debens acaban convirtiéndose en escribas.   @PLos escribas son muy ricos y no realizan trabajos manuales. Viven en grandes casas, rodeados de lujos, y dedican sus días al ocio y a la educación. Exigen un nivel de servicios superior al de sus trabajadores, pero también pagan más impuestos.  @PComo sus impuestos son tan altos, tener un buen número de escribas en la ciudad puede ser una bendición para el tesoro. Sin embargo, si tiene demasiados, la ciudad puede dejar de funcionar con eficiencia por falta de trabajadores. @PSi no mantiene un nivel alto de servicios, los escribas acaban volviendo a la clase trabajadora. Es lo peor que un escriba puede imaginar. Aunque la ciudad gane trabajadores, perderá ingresos fiscales, y su calificación de Prosperidad también bajará. @L@L@387Los escribas formaban una de las clases más acomodadas de la @168sociedad del antiguo Egipto. Siga los enlaces para saber más."
                                }
                            }

    message_game_concept_walkers {
        id: 42,
        
        size [30, 28]
        title {
            text: "Transeúntes",
        }
        content {
            text: "Prácticamente todas las personas que caminan por las calles de tu ciudad tienen algún motivo para sus viajes. Algunas trasladan mercancías de un lugar a otro. Otras prestan servicios a las viviendas o a los demás edificios por los que pasan. Y otras simplemente están llegando a la ciudad o marchándose de ella. Solo unas pocas personas de la élite tienen el lujo de pasear sin ningún recado en mente. @PEstos transeúntes se dividen en dos tipos básicos: transeúntes con destino y transeúntes errantes. Cada uno se comporta de forma muy distinta. @L@LTranseúntes con destino @LLos transeúntes con destino abandonan sus lugares de trabajo con un objetivo concreto. Usando un mapa de las calles de tu ciudad, determinan la ruta más corta hasta su destino. Ejemplos de transeúntes con destino son los compradores del Bazar, los emigrantes, los inmigrantes y los repartidores. @L@LTranseúntes errantes @LLos transeúntes que deambulan por la ciudad aportan beneficios a tus ciudadanos cuando pasan a menos de dos casillas de las viviendas. Algunos también prestan servicios valiosos a los edificios de la ciudad.   @PLos errantes salen de sus edificios sin un destino concreto en mente. Intentan tomar una dirección distinta cada vez. A partir de ahí, pueden resultar completamente impredecibles. @PCada vez que un transeúnte errante llega a una intersección, debe decidir por dónde girar. No toma la misma decisión cada vez, así que es posible que las casas que ya ha visitado tarden bastante en recibir otra visita.   @PLa mejor manera de encauzar a estos transeúntes es una buena planificación urbana. Como las intersecciones les dan tanta libertad, mantenerlas al mínimo ayuda a guiarlos hacia donde quieres que vayan. @P@358Los bloqueos de calle son otra herramienta eficaz para controlar a los errantes. Cuando un errante se encuentra con un bloqueo, da media vuelta. Los transeúntes con destino ignoran los bloqueos. @PEjemplos de transeúntes errantes son los vendedores del Bazar, los aguadores, los sacerdotes y los médicos. @PAlgunos transeúntes errantes se comportan como transeúntes con destino en determinadas circunstancias. Por ejemplo, los bomberos que van a apagar un incendio o los guardias que se dirigen a defender la ciudad de alguna amenaza actúan como transeúntes con destino. En todos los demás momentos, sin embargo, son transeúntes errantes. @L@LLa vida del transeúnte @LLos transeúntes errantes tienen una jornada laboral limitada. Sus rondas duran un tiempo determinado, tras el cual abandonan las calles durante un rato. Si su empleador tiene a todo su personal completo, envía otro errante casi de inmediato. Si el edificio va escaso de empleados, normalmente hay un retraso antes de que salga un nuevo errante.   @PLos transeúntes con destino deben trabajar hasta completar su encargo, aunque eso signifique recorrer toda la ciudad de ida y vuelta. @PLos transeúntes que comparten características de destino y de errante sí tienen una jornada laboral limitada. El tiempo que deben dedicar al trayecto hasta su destino reduce el que tienen para deambular. Esto se nota sobre todo en los artistas, cuyas actuaciones se acortan si tienen trayectos largos desde sus escuelas hasta sus escenarios. @PPor último, ten en cuenta que el terraplén que separa la llanura inundable de la tierra firme es empinado, fangoso y traicionero. Nadie puede moverse hacia la llanura inundable ni desde ella a menos que una @57carretera haga pasable esa frontera. @L@LDepredadores @LNo todo lo que camina por la ciudad es amistoso. También merodean por la ciudad y sus alrededores animales peligrosos que matan sin piedad a quien se cruce en su camino. Los guardias harán todo lo posible por abatir a estas bestias, pero usar tu ejército es probablemente la mejor opción para derrotar a los depredadores. Los animales de los que debes cuidarte son hienas, hipopótamos, cocodrilos, áspides, escorpiones y leones."
        }
    }

    message_employment_unemployment {
        id: 43,
        
        size [30, 28]
        title { text: "Empleo y desempleo" }
        subtitle { text: "Concepto de juego" }
        content {
            text: "Casi todos los edificios de la ciudad necesitan trabajadores. La ciudad no puede proveer a sus ciudadanos sin una fuerza laboral. @PCuando construyes por primera vez un edificio que necesita mano de obra, un agente de contratación patrulla las calles en busca de trabajadores dispuestos. Si pasa cerca de alguna vivienda, y si la ciudad en conjunto tiene trabajadores disponibles, su búsqueda tiene éxito y el edificio que lo envió tendrá empleados. @PLa labor del buscador de empleo no siempre es fácil. Uno de los mayores desafíos como líder de una ciudad es equilibrar la fuerza de trabajo con el número de empleos disponibles. En un mundo perfecto, una ciudad tendría exactamente el mismo número de empleos que de personas que los quieren. Esto casi nunca ocurre. Una ciudad tendrá demasiados trabajadores y pocos empleos, o demasiados empleos y pocos trabajadores. @PEl desempleo no es bueno para la ciudad. Mientras los trabajadores desempleados están ociosos, pueden desencantarse y hacer que el @39ánimo de la ciudad baje. Incluso podrían recurrir a la @36delincuencia. La mejor manera de tratar el desempleo es crear nuevos empleos. En general, no perjudica a una ciudad tener bienes y servicios adicionales. Unas cuantas granjas más, más instalaciones de entretenimiento y nuevas Escuelas, Bibliotecas o Templos pueden beneficiar a la ciudad. Al reducir el desempleo, podrías aumentar los índices de prosperidad y cultura de la ciudad. @POtra forma -aunque despiadada- de reducir el desempleo es reducir la población de la ciudad. Puedes hacerlo destruyendo las casas de la gente, forzando la emigración. Esto también puede tener un efecto positivo en la ciudad. Si destruyes las viviendas de nivel inferior, el valor total del parque de viviendas de la ciudad aumentará. Este aumento podría traducirse en un índice de prosperidad más alto. @PEl otro problema de empleo al que te enfrentarás es la escasez de mano de obra, es decir, tener demasiados empleos para la fuerza de trabajo disponible. La solución ideal para la escasez de mano de obra es atraer nuevos inmigrantes. Construye nuevas zonas residenciales o anima a las zonas existentes a evolucionar hacia estructuras más grandes. Asegúrate también de que el @39ánimo de la ciudad se mantenga alto. Pagar más que el salario vigente en Egipto o bajar el tipo impositivo de la ciudad también pueden atraer a nuevos inmigrantes. @PMientras esperas la llegada de inmigrantes que ocupen los empleos disponibles, trabaja con tu @24supervisor&de&comercio y con el @20supervisor&de&los&trabajadores para aliviar la escasez. Visita a tu supervisor de comercio y cierra durante un tiempo las industrias sin las que puedas prescindir. Así se liberan algunos trabajadores para ocupar otros puestos. Si no quieres cerrar una industria entera, quizá tengas que demoler parte de sus edificios.   @PHabla con tu supervisor de los trabajadores sobre el establecimiento de prioridades laborales. Dar prioridad a los empleos esenciales garantiza que los ciudadanos sigan recibiendo lo que necesitan para vivir. @PUn remedio poco ortodoxo y no del todo bueno para la escasez de mano de obra es animar a las casas de tus @41escribas a degradarse de nuevo a @40casas de trabajadores. Dañarás el índice de prosperidad de la ciudad y reducirás sus ingresos fiscales, pero la fuerza laboral aumentará, a costa de las esperanzas y los sueños de tus ciudadanos más ricos. @PAunque estar sin trabajo resulta muy estresante para quien está desempleado, un pequeño porcentaje de desempleo es en realidad algo bueno para una ciudad en expansión, porque te proporciona un grupo de trabajadores dispuestos para los nuevos edificios. El desempleo por encima del 5 por ciento causa problemas."
        }
    }
    
    message_drinking_water {
        id: 44,
        
        size [30, 28]
        title { text: "Agua potable" }
        subtitle { text: "Concepto de juego" }
        content {
            text: "Una de las primeras cosas que exige la gente es acceso a agua potable limpia. Sus viviendas no mejorarán en absoluto sin al menos algo de agua. @P@62Los pozos y los @61suministros&de&agua proporcionan agua potable a los ciudadanos. Los pozos son una fuente rudimentaria de agua. Pueden resultar aceptables para los ciudadanos cuando la ciudad es nueva y lucha por prosperar, pero la gente no se conformará con el agua de pozo durante mucho tiempo. Pronto exigirán agua de los suministros de agua. @PLos suministros de agua emplean aguadores que llevan el agua a los hogares. Cuando un aguador pasa frente a una casa, esa casa tiene acceso a agua limpia. Vigila de cerca a los aguadores: son @42transeúntes&errantes y no siempre siguen el mismo camino dos veces. Las casas que antes tenían agua limpia en abundancia pueden perderla, sobre todo si cambias la red de carreteras del barrio.   @PSi el @56atractivo de la zona es lo bastante alto, los trabajadores del suministro de agua tomarán medidas para mejorar su aspecto y su eficiencia. Los aguadores de uno de estos suministros evolucionados recorrerán el barrio con más frecuencia. @PTanto los pozos como los suministros de agua solo pueden construirse en terrenos con agua subterránea, señalados por la hierba que crece allí. @PLee la entrada sobre la @53salud&de&la&ciudad para saber más sobre los beneficios del agua potable limpia."
        }
    }

    message_tutorial_food_and_farming {
        id: 45,
        
        size [30, 28]
        title { text: "Alimentos y agricultura" }
        subtitle { text: "Concepto de juego" }
        content {
            text: "El camino al corazón de los ciudadanos pasa por sus estómagos.  Proporcionar comida abundante, y de buena variedad, refuerza tanto el @39ánimo de la ciudad como la @53salud de la ciudad.  @PHay muchos tipos de granjas de alimentos en Faraón, entre ellas las de @89grano, @90granadas, @90garbanzos, @90lechuga y @90higos. También hay dos tipos de agricultura en Faraón: la agricultura de llanura inundable y la agricultura de prados. Ambos tipos de granja requieren acceso por carretera y mano de obra, pero la mayoría de sus similitudes terminan ahí. Además, la agricultura no es la única fuente de alimento.  @359La caza, @84la pesca y la @360ganadería contribuyen a los graneros de la ciudad. @L@LAgricultura de llanura inundable @LPara entender cómo funcionan las granjas de la llanura inundable, primero debes conocer las fases del Nilo. Cada año, normalmente entre junio y septiembre, el Nilo inunda sus orillas. Las llanuras inundables quedan completamente sumergidas, y no se puede levantar nada sobre el terreno. En pocos meses, el Nilo empieza a retirarse, dejando tras de sí un limo nutritivo que fertiliza el suelo. La llanura inundable vuelve a emerger, y puedes volver a explotar granjas en ella. @G56 @PEl Nilo no inunda exactamente al mismo tiempo ni de la misma manera cada año. Algunas crecidas son mejores que otras. Los sacerdotes usan los nilómetros para determinar lo buena que será la próxima crecida e informan de sus conclusiones a tu @31jefe&supervisor. Prestar especial atención a Osiris, dios de la agricultura y de la crecida del Nilo @51(ver&Religión), puede ayudar a garantizar crecidas favorables cada año. @PPuedes construir granjas (y carreteras y acequias de riego) en la llanura inundable en cualquier momento, excepto durante la crecida. Cuando construyes una granja en la llanura inundable, solo aparece el campo, sin edificios, porque la crecida destruye cualquier edificio de la llanura. Como no se pueden construir viviendas en las granjas de la llanura, los campesinos necesitan un lugar donde reunirse para que se les asigne trabajo. Los @8campamentos&de&trabajo cumplen esta función. Los campamentos de trabajo envían trabajadores a las granjas para sembrar y recoger los cultivos, y las granjas permanecen ociosas si no hay un campamento de trabajo. Hay un límite a la distancia que los campesinos recorrerán para llegar a sus agotadoras tareas, así que no sitúes los campamentos de trabajo demasiado lejos de los campos. @PEl mejor momento para construir granjas es poco después de que retroceda la crecida. Así podrás aprovechar al máximo la temporada de cultivo hasta la siguiente crecida, y la granja tendrá su máximo rendimiento. Las granjas que se levanten en cualquier otro momento producirán menos. @POtro factor que considerar al situar granjas es la fertilidad. Cuanto más oscura sea la tierra y más frondosa la hierba, más fértil es el terreno. Las tierras más fértiles suelen encontrarse directamente junto al río. A medida que te alejas del río, la tierra se vuelve menos fértil. Las granjas situadas en las tierras más fértiles producen las cosechas más abundantes. Puedes construir acequias de riego en las llanuras inundables para regar las tierras más alejadas del río, mejorando así la fertilidad de las tierras que podrían quedar secas durante una mala inundación. @PDebido al ritmo anual del Nilo, las granjas de la llanura inundable solo pueden producir una cosecha al año. La supervivencia de una ciudad puede depender de tener suficientes trabajadores para recoger la cosecha y suficiente espacio de almacenamiento para recibirla. @L@LAgricultura de prados @LLa llanura inundable no es la única tierra fértil, aunque constituye la mayor parte de la tierra cultivable disponible. También pueden situarse granjas en los prados, señalados con matas amarillas. Cuanto más densas son estas matas, más fértil es la tierra, lo que se traduce en cosechas mayores. Estas granjas sí tienen un edificio de trabajo en el propio terreno, así que no necesitan campesinos de un campamento de trabajo. Como la tierra no se inunda, estas granjas siguen funcionando durante todo el año. Sin embargo, hectárea a hectárea, la tierra de prado es menos fértil que la de la llanura inundable, y las granjas de prado suelen dar menos cosechas por temporada. Las granjas de prado casi siempre se benefician de las acequias de riego. @L@LCaza y pesca @LLos cazadores y los pescadores aprovechan la abundancia natural de Egipto. Ambos salen de sus bases, capturan a sus presas y regresan a ellas para preparar la comida. @PLos cazadores trabajan desde los refugios de caza. Desde el refugio salen a cazar. Buscarán bandadas de avestruces, aves acuáticas o manadas de antílopes. Si observas alguno de estos animales alrededor de la ciudad, sitúa un refugio de caza cerca. @PLos pescadores se reúnen en los embarcaderos de pesca, donde intercambian historias sobre el que se les escapó. Los embarcaderos, por supuesto, están junto al agua, y los pescadores necesitan que un constructor de barcos les fabrique una embarcación. Una vez que tienen barco, zarpan. No todas las ciudades pueden sostener la caza o la pesca. Si ves peces saltando fuera del agua, la ciudad puede tener una industria pesquera.   @PEl tamaño de los rebaños, bandadas y bancos de peces es limitado. La caza y la pesca pueden proporcionar a una población pequeña suficiente comida, pero una población grande no podrá subsistir solo con pescado o carne de caza. @L@LGanadería @LLos ranchos de ganado pueden ser una excelente fuente de alimento adicional. Pueden situarse en cualquier tipo de terreno, no solo en tierra fértil, lo que deja la tierra cultivable para otro fin. El ganado consume paja, el subproducto del @89cultivo&de&grano. El número de ranchos de ganado que puede tener una ciudad solo está limitado por la cantidad de paja que la ciudad puede destinar al forraje. @L@LDistribución de alimentos @L@3Graneros y @2Bazares son los intermediarios entre los productores de alimentos y los habitantes de la ciudad. Los graneros almacenan la comida destinada al consumo de las personas, y los bazares la reparten a cada vivienda.   @PCuando un productor de alimentos tiene un artículo listo, un empujador de carros lo lleva a un granero. Los compradores del Bazar acuden a los graneros para adquirir los alimentos que piden sus clientes. Pueden transportar más de un tipo de alimento a la vez. Cuando los compradores regresan al Bazar con sus productos, los comerciantes recorren el barrio entregando comida a la población. @PEs importante tener suficientes graneros y bazares. Si todos los graneros están llenos, el empujador de carros lleva la comida a un @4patio&de&almacenamiento, si se le ha indicado que acepte alimentos. Los compradores del Bazar no adquieren alimentos de producción local en los patios de almacenamiento (aunque sí llevan allí artículos no alimentarios y alimentos importados). Los compradores del Bazar obtienen la mayor parte de los alimentos de los graneros. @PColocar bazares y graneros puede ser complicado. Los graneros deben estar cerca de los productores de alimentos para que los empujadores de carros no tengan que recorrer grandes distancias. Los bazares deben estar cerca de los graneros para que los compradores puedan mantenerlos bien surtidos. Los bazares también necesitan estar próximos a las casas a las que sirven. Todas estas estructuras son vecinos poco deseables, así que situarlas siempre implica hacer concesiones. @PA medida que tu ciudad crezca, quizá tengas que construir graneros más alejados de los productores de alimentos para que los bazares de los barrios periféricos puedan conseguir lo que necesitan. Si ves que tienes que hacerlo, usa las órdenes especiales del granero para asegurarte de que recibe alimentos. @L@LImportación de alimentos @LAlgunas ciudades no pueden producir suficiente comida para sostenerse, o solo pueden producir variedades limitadas, y por ello necesitan importar alimentos de otras ciudades. Los alimentos importados se entregan en los patios de almacenamiento, donde los compradores del Bazar pueden recoger los productos y llevarlos de vuelta al Bazar. @L@LLos temas relacionados están enlazados a lo largo de esta sección (las palabras enlazadas aparecen en un color distinto al resto del texto). Leer estas entradas te ayudará a entender la producción y la distribución de alimentos. @L@LPara conocer la historia de la comida en el antiguo Egipto, haz clic @150aquí. Descubre los efectos del Nilo haciendo clic @157aquí."
        }
    }

    message_game_concept_industry {
        id: 46
        
        size [30, 28]
        title { text: "Industria" }
        subtitle { text: "Concepto de juego" }
        content {
            text: "La industria es probablemente uno de los sectores de empleo más grandes de la ciudad. Los ciudadanos usan algunos de los productos que fabrican las industrias para mejorar sus vidas. Otros productos pueden @47comerciarse&con&un&buen&beneficio.   @PAunque una ciudad probablemente tenga una gran variedad de industrias, todas comparten ciertas características. Todas necesitan fuerza laboral, y la eficiencia se resiente si algún fabricante o productor de materias primas está falto de personal. Todas las industrias también necesitan acceso por carretera para que sus trabajadores puedan llegar a ellas. @PAlgunas industrias producen una materia prima que puede transformarse en un bien acabado en un fabricante. Estas industrias son @92Yacimientos&de&arcilla, @361Minas&de&piedras&preciosas, @93Minas&de&cobre, @94Leñadores y @94Recolectores&de&juncos.  @91Campos&de&cebada, @91Campos&de&henna y @91Campos&de&lino también producen materias primas para la industria. @89Las granjas de grano, además de producir alimentos, también producen un artículo no alimentario: la paja. Un productor de materias primas suele generar suficiente para abastecer a dos industrias de bienes acabados. Las materias primas pueden comerciarse, pero no alcanzan un precio tan alto como un producto acabado. @PLas industrias que transforman materias primas en otro producto (a veces llamadas 'talleres') son @96cervecerías, @99joyerías, @60tejedurías, @97talleres&de&papiro, @1alfarerías, @364ladrilleras, @473fabricantes&de&lámparas, @470fabricantes&de&pintura, @98armerías y @98fabricantes&de&carros. Sus productos acabados pueden usarse en la ciudad o comerciarse en el mercado abierto. @P@95Las canteras y las @93minas&de&oro se diferencian de otras industrias porque su materia prima es también su producto acabado. @82Los astilleros producen un bien acabado (barcos) a partir de una materia prima (madera), pero los barcos no pueden comerciarse en el mercado abierto. @PLos repartidores llevan los bienes adonde deben ir. Los repartidores empleados por los productores de materias primas siempre intentan llevar primero su carga a los talleres que necesitan el material, prefiriendo el más cercano. Si ninguna industria necesita la materia prima, el repartidor se dirige al @4patio&de&almacenamiento más cercano que tenga espacio para sus mercancías. Si no hay patios de almacenamiento disponibles, el repartidor se toma un descanso hasta que se libere espacio. Los únicos repartidores de materias primas que no se comportan de esta forma son el empujador de carros de la mina de oro y el arrastrador de trineos de la cantera. El empujador de carros de la mina de oro lleva su oro solo al Palacio, nunca a un patio de almacenamiento. Como la piedra no puede transformarse en ningún otro bien, los arrastradores de trineos de la cantera siempre llevan su material a un patio de almacenamiento. @G74 @PAlgunos edificios de la ciudad necesitan bienes industriales para funcionar plenamente. Entre ellos se incluyen la @70Biblioteca, la @68Escuela&de&escribas, la @74Casa&del&senet, el @88Reclutador, el @66Tanatorio, el @363Gremio&de&artesanos y el @363Gremio&de&carpinteros. Un repartidor de un fabricante intenta llevar sus productos acabados a uno de estos edificios que los necesiten. Si no hay ninguno disponible, también lleva su producto acabado a un patio de almacenamiento, o se queda parado hasta que se libere espacio. A los empujadores de carros les gustan estas vacaciones improvisadas, porque siguen cobrando salario y raciones mientras permanecen de pie sin hacer nada.  @PPara ver si tus industrias tienen algún problema, usa el @18Mapa&de&problemas. Esta vista muestra qué edificios industriales no funcionan correctamente, y por qué.   @PHaz clic con el botón derecho en un edificio para ver su estado de producción actual. Te indica si el edificio tiene el personal completo y en qué punto del ciclo de producción se encuentra. Si hay algún problema, el panel te dirá cuáles son.   @PHaz clic en cualquiera de los enlaces anteriores (el texto enlazado aparece en azul) para leer sobre industrias concretas. @L@LHaz clic @151aquí para conocer la historia de la industria en el antiguo Egipto."
        }
    }

    message_game_concept_trade {
        id: 47,
        
        size [30, 28]
        title {
            text: "Comercio",
        }
        subtitle {
            text: "Concepto de juego",
        }
        content {
            text: "Ninguna ciudad es completamente autosuficiente. El comercio trae a tu ciudad productos que no puede fabricar por sí misma. Exportar mercancías genera mucho dinero, a menudo más de lo que la ciudad puede ganar con los impuestos. Por su importancia, tu ciudad debería empezar a comerciar en cuanto pueda satisfacer las necesidades básicas de sus habitantes. @PEl @32mapa&del&mundo muestra qué ciudades comerciarán contigo. Las ciudades dispuestas a comerciar ondean una bandera. Haz clic en una de ellas para averiguar qué productos compra y vende el municipio. Los puntos azules que aparecen en la esquina del símbolo de cada mercancía indican cuánto está dispuesta a importar o exportar la ciudad cada año. Un punto significa que apenas comercian con ese bien, mientras que tres puntos señalan un fuerte deseo de comerciar con él. Estos niveles pueden cambiar según la oferta y la demanda o las presiones políticas en Egipto. @PHaz clic en el botón 'Abrir ruta comercial' para gastar los fondos necesarios para establecer la nueva alianza. Abrir una ruta comercial puede resultar costoso, pero compensa a largo plazo. @PUna vez abierta una ruta comercial, visita a tu @24supervisor&de&comercio para configurar los intercambios. Haz clic en el botón 'Mostrar precios' para ver cuánto pueden comprarse o venderse los productos. Notarás que los productos se venden por menos dinero del que te cuesta comprarlos. La diferencia de precios cubre los gastos del mercader por venir hasta tu ciudad. @L@LImportar @LPara importar un bien, haz clic en la mercancía que quieras. Después de seleccionar un artículo, tienes dos opciones. Puedes decidir por ti mismo cuánto de ese artículo quieres que tenga la ciudad en reserva e indicar a tu supervisor de comercio que actúe en consecuencia. O bien puedes dejar que tu supervisor de comercio decida cuánto debe tener la ciudad en reserva. Tu supervisor de comercio seguirá importando el artículo mientras las existencias de la ciudad estén por debajo del nivel prescrito, o hasta que se alcance el límite comercial anual del socio. @PAlgunos bienes que necesita tu ciudad solo pueden importarse. Entre ellos se encuentran el mármol blanco para la construcción de monumentos y el aceite para las @473lámparas. Para hacer evolucionar las @56viviendas de la ciudad a su nivel más alto, también tendrás que importar artículos de lujo. @PLas importaciones pueden resultar bastante caras, así que vigila de cerca los @4patios&de&almacenamiento de la ciudad. Si observas que los patios están llenos de un bien concreto que la ciudad importa, ahorra dinero dejando de importarlo hasta que se agoten las existencias. Además, importar materias primas es más barato que importar productos acabados. A largo plazo, la ciudad ahorrará dinero si tiene sus propios fabricantes que conviertan una materia prima importada en un producto acabado. @L@LExportar @LPara exportar un bien, haz clic en el artículo que quieras vender. Después, decide tú mismo cuánto debe tener la ciudad en reserva o deja que sea el supervisor de comercio quien lo decida. Los excedentes se exportarán hasta la cuota anual del cliente. Ten presente que algunas mercancías que exporta la ciudad también las desean sus ciudadanos, así que asegúrate de mantener suficiente cantidad en almacén para sus necesidades. Revisa con frecuencia tus bazares y las viviendas de tus ciudadanos para comprobar si tienen suministro del bien que comercias. Asegúrate también de que los edificios que necesitan un bien acabado tengan existencias. Si las viviendas y otros edificios tienen dificultades para conseguir un artículo, probablemente la ciudad está exportando demasiado. @L@LA veces una ciudad puede exportar o importar la misma mercancía. Esto te da más flexibilidad a la hora de planificar las industrias de la ciudad. Si quieres reforzar los ingresos de una ciudad, dedica mano de obra a producir el bien y expórtalo a un socio comercial. Si quieres usar la fuerza laboral de la ciudad para otro fin, importa el producto. La ciudad nunca puede importar y exportar un artículo al mismo tiempo, y no se beneficiará de importar un producto de una ciudad solo para venderlo a otra. Los compradores pagan más de lo que reciben los vendedores, así que la ciudad solo perderá dinero si actúa como intermediaria. Por otro lado, importar una materia prima y exportar su producto acabado suele ser una operación muy rentable. @PLos mercaderes llegan a tu ciudad en caravana o en barco de comercio. Antes de comerciar con cualquiera de los dos tipos de mercader, debes tener un patio de almacenamiento en funcionamiento. Además de un patio de almacenamiento, también necesitas un @83muelle si quieres comerciar con mercaderes en barcazas. Los barcos de comercio realizan todas sus operaciones en los muelles, y cuando llegan, los empujadores de carros de los muelles recogen los artículos necesarios de los patios de almacenamiento."
        }
    }
    
    message_game_concept_money {
        id: 48,
        
        size [30, 28]
        title {
            text: "Dinero",
        }
        subtitle {
            text: "Conceptos del juego",
        }
        content {
            text: "No puedes construir una ciudad sin dinero, y la cantidad de dinero en sus arcas es un buen indicador del éxito de la ciudad.  La ciudad gana dinero imponiendo impuestos, exportando mercancías, recibiendo regalos y, si la ciudad dispone de minas, extrayendo oro.  Estos temas, relativamente obvios, se explican hacia el final de esta entrada.  Primero, sin embargo, debes conocer los detalles de la gestión del dinero. @L@LDeuda @LLa primera vez que tu tesorería se quede sin fondos, otros líderes egipcios podrían enviarte un regalo de rescate en forma de debens adicionales.  Esto no te penaliza de ninguna manera, y no esperan que lo devuelvas.  Considéralo, eso sí, una advertencia de que tu ciudad debe cambiar su forma de gastar. @PSi gastas todos tus fondos de rescate, o si no recibes ningún regalo de este tipo, tu tesorería puede acumular hasta 5.000 debens de deuda.  Los números amarillos indican que tu ciudad tiene deudas. @PLos endeudamientos breves y esporádicos suelen ser inevitables, y no te perjudicarán si restableces rápidamente un saldo positivo en tus cuentas.  El endeudamiento a largo plazo puede costarte la partida. @L@LConsecuencias de la deuda @LCada mes que tu tesorería tenga un déficit te costará un pago de intereses, que se añade automáticamente a tu total de deuda.  Cuanto mayor sea tu endeudamiento, más intereses tendrás que pagar y más crecerá tu deuda.   @PCada vez que tu ciudad cierre un año en deuda, no podrás pagar tu tributo anual (ver más abajo).  Faltar a un tributo no te cuesta dinero, pero sí reduce algo tu @35Índice&del&Reino.  El efecto empeora si faltas a tributos anuales consecutivos. @PSi no logras un saldo positivo en la tesorería (aunque sea brevemente) durante los 12 meses siguientes a contraer la deuda, tu índice del Reino sufrirá, pues otros líderes egipcios perderán confianza en tu capacidad de gobierno.  Tu primera penalización por 'aniversario de deuda', aunque dolorosa, probablemente no causará daños irreparables.  Si en el segundo aniversario de la deuda aún no ves cifras positivas, tu índice del Reino caerá considerablemente, y los años siguientes serán aún peores.   @L@LCómo salir de la deuda @LLa deuda es un problema serio y, cuando no puedas evitarla, debes saldarla lo antes posible.  Las formas de recaudar dinero se explican más abajo, pero también debes abstenerte de gastar tu limitado crédito en nada que no te vaya a generar dinero a la larga.  Las oficinas de recaudadores de impuestos, las industrias que producen mercancías exportables y las nuevas rutas comerciales con ciudades que compren tus productos pueden ser inversiones acertadas.  @L@LTributo anual @LAl final del año, tu ciudad debe pagar un 'impuesto' al Reino, llamado 'tributo'.  La cuantía del tributo varía según la capacidad de pago de la ciudad, por lo que empieza siendo bastante pequeña y aumenta a medida que la ciudad crece en población y riqueza.  Visita a tu @30Supervisor&del&Tesoro para ver cuánto tributo pagas. @PMientras termines el año con debens en tus arcas, el pago del tributo es automático.  Nunca tienes que realizar este pago activamente.  Sin embargo, cada vez que termines el año en deuda, tu ciudad no podrá pagar su tributo y tu @35Índice&del&Reino caerá.  La penalización no es excesiva por faltar al tributo de un año, pero crece el segundo año consecutivo y aún más después.  Esto refleja tu creciente mala reputación ante tu propio pueblo como mal administrador financiero. @L@LImpuestos @LLos impuestos cobran a los ciudadanos por todos los servicios que la ciudad les proporciona.  Los ciudadanos no protestarán por pagar impuestos mientras el tipo impositivo sea razonable.  El tipo inicial del 9 por ciento es una buena referencia, pero puedes subirlo o bajarlo en cualquier momento.  Visita a tu Supervisor del Tesoro o haz clic derecho en el Palacio para ajustar el tipo.  Bajar el tipo impositivo te granjea alegría y aprecio.  Subirlo provoca quejas y puede llevar a una emigración masiva de ciudadanos. @PSubir el tipo impositivo puede ser necesario a veces.  Si ves que tu ciudad está a punto de entrar en deuda, puedes subir el tipo para aliviar el problema.  Aun así, probablemente deberías buscar una solución alternativa a largo plazo para los problemas financieros de la ciudad.  Un tipo impositivo alto puede empeorar rápidamente el @39Ánimo&de&la&ciudad. @PAunque a los ciudadanos no les importa pagar impuestos, no entregarán parte de sus ingresos sin que se les pida.  Para recaudar impuestos, la ciudad necesita un @77Palacio.  Luego, construye oficinas de @80Recaudadores&de&impuestos para recaudarlos de verdad. @PEl Supervisor del Tesoro sabe qué porcentaje de tu población está registrado para el impuesto y cuántos ingresos no se recaudaron por falta de recaudadores.  Usa la @18Capa&de&impuestos para ver si alguna zona de tu ciudad se libra fácilmente.  Asegúrate también de cobrar los impuestos de forma justa.  Si una parte de los habitantes paga un tipo alto y la otra no paga nada, el @39Ánimo&de&la&ciudad caerá en picado y podría estallar el @36crimen. @L@LComercio @LLos ingresos por exportaciones serán probablemente la principal fuente de dinero de la ciudad.  Abre rutas comerciales cuanto antes.  Es fundamental que entiendas cómo exportar mercancías, así que lee sobre el @47comercio si te da problemas. @L@LExtracción de oro @LAlgunas ciudades pueden fabricar su propio dinero.  El oro se convierte en debens, la moneda básica de Egipto.  Si ves pepitas de metal incrustadas en un afloramiento rocoso, quizá puedas construir una @93Mina&de&oro.  No te emociones demasiado; el mineral podría resultar ser @93cobre, que es muy valioso por sí mismo pero normalmente no tan deseado como el oro.  Haz clic en el botón de industria del Panel de control y luego en materias primas para averiguar qué metal precioso puede extraer tu ciudad. @PLas minas de oro funcionan como otras @46industrias, pero su producción se entrega solo al Palacio, donde se convierte en debens, y nunca a un Patio de almacenamiento. @L@LAhorros familiares y salario @LAl igual que la ciudad, tú también puedes ganar dinero.  Se te paga por tus esfuerzos como líder de la ciudad y puedes cobrar un sueldo en cuanto construyas una @78Mansión.  Tu salario se paga desde la tesorería de la ciudad y es proporcional a tu experiencia.  Puedes elegir modificar tu sueldo, pero si te pagas mucho más de lo que vales, tu @35Índice&del&Reino podría desplomarse.  También puedes pagarte menos, o no pagarte nada, lo que puede impresionar a la gente y ayudar a tu índice del Reino.  Si tu ciudad atraviesa dificultades financieras, no cobrar un salario es una buena forma de reducir costes. @PPuedes transferir ahorros familiares a la tesorería de la ciudad en cualquier momento: una buena forma de saldar o prevenir deudas.  Nunca puedes transferir dinero de la tesorería a tu cuenta familiar, ¡eso sería malversación! @PTus ahorros familiares también pueden comprar un 'regalo para Egipto'.  Tales donaciones al pueblo de Egipto o, a discreción de tu Supervisor, a otros líderes egipcios mejorarán de inmediato tu índice del Reino en una pequeña cantidad.  Ten cuidado con esta estratagema, sin embargo.  Una vez comenzados los regalos, los receptores llegan a esperarlos, sobre todo si los has repartido con regularidad.  Dejar de hacerlos puede perjudicar tu índice. @PLa entrada sobre el @22Asesor&político te dará más información sobre tus ahorros personales."
        }
    }

    message_game_concept_entertainment {
        id: 49,
        
        size [30, 28]
        title {
            text: "Entretenimiento",
        }
        subtitle {
            text: "Concepto del juego",
        }
        content {
            text: "Todo trabajo y nada de diversión hacen de Imhotep un hombre aburrido.  Proporciona a los habitantes de la ciudad entretenimiento para que sea un lugar agradable para vivir. @P@71Casetas, @72Quioscos&de&música, @73Pabellones, @74Casas&del&senet y @479Zoológicos ofrecen a los ciudadanos el entretenimiento que anhelan.  Cuando tu ciudad es nueva, los ciudadanos se conforman con el más pequeño de los locales, la Caseta.  A medida que la ciudad crezca, también crecerá la demanda de entretenimiento, y los ciudadanos esperarán ser entretenidos por una variedad de artistas.  Tu @28Supervisor&de&Diversiones te ayudará a evaluar las necesidades de tus ciudadanos. @PLa mayoría de los artistas necesitan formarse en su oficio en los @75Centros&de&formación.  Los malabaristas perfeccionan su arte en las escuelas de malabarismo, los músicos practican en los conservatorios y los bailarines aprenden los pasos más recientes en la escuela de danza.  Una vez formados, los artistas caminan desde el centro de formación hasta el local de entretenimiento.  Los maestros del senet no se forman en un centro de formación. @PTus ciudadanos saben que tienen acceso al entretenimiento cuando ven pasar a los artistas frente a sus casas (haz clic en @42aquí para más información sobre los transeúntes).  Los artistas salen de locales de entretenimiento en pleno funcionamiento.  Los músicos, malabaristas y bailarines también recorren las calles cuando van del centro de formación al local.  Ten esto en cuenta al planificar tus instalaciones.  Si colocas tu local de entretenimiento y los centros de formación en lados opuestos de un barrio, un artista tendrá que pasar junto a las viviendas para llegar a su local, aportando entretenimiento por el camino.  Pero ten cuidado de no colocar los centros de formación demasiado lejos de los locales.  Cuanto más viaje un artista, más corta será la función y más probable será que el local esté inactivo, sin beneficiar a nadie.   @PLa Casa del senet y el Zoológico necesitan un suministro de mercancías para funcionar.  La Casa del senet necesita @96cerveza para calmar la sed de sus clientes, y el Zoológico necesita @89paja y @359carne&de&caza para cuidar adecuadamente a los animales. @L@LHaz clic en @165aquí para más información sobre el entretenimiento en el antiguo Egipto."
        }
    }

    message_game_concept_education {
        id: 50,
        
        size [30, 28]
        title {
            text: "Educación",
        }
        subtitle {
            text: "Concepto del juego",
        }
        content {
            text: "La educación es un privilegio de los ricos.  Los ricos saben que la educación en una @68Escuela&de&escribas es el camino hacia una vida mejor para sus hijos, y les gusta tener acceso a una @70Biblioteca para ellos mismos. @PNi las escuelas de escribas ni las bibliotecas funcionarán sin @97papiro.  Antes de construir una biblioteca, debes tener suficiente papiro almacenado en los @4Patios&de&almacenamiento para llenar sus estanterías de rollos.  Los @42transeúntes de ambos edificios llevan papiro consigo mientras difunden la educación entre la población.  La ciudad debe fabricar o @47importar papiro para que los edificios educativos sigan funcionando. @PVisita a tu @27Supervisor&de&Educación para asegurarte de que la ciudad satisface la demanda de educación de los ciudadanos.  @PTener suficientes bibliotecas y escuelas para tus ciudadanos contribuye a tu @35Índice&de&Cultura. @L@LEntérate de cómo los antiguos egipcios se entretenían haciendo clic @165aquí."
        }
    }

    message_game_concept_relition {
        id: 51,
        
        size [30, 28]
        title {
            text: "Religión",
        }
        subtitle {
            text: "Concepto del juego",
        }
        content {
            text: "Hay cinco grandes dioses en Egipto: Osiris, dios de la agricultura y de la crecida del Nilo; Ptah, dios de los artesanos; Ra, dios del Reino; Seth, dios de la destrucción; y Bast, diosa del hogar.  Apaciguar a estos dioses da buenos frutos, y descuidarlos causa desgracias.  Tu @29Supervisor&de&los&Templos conoce el estado de ánimo de los dioses, así que consúltale a menudo. @PMuchas ciudades tienen un dios patrón.  El dios patrón espera más de una ciudad que las otras deidades locales.  Las deidades locales exigen menos que un dios patrón, pero pueden afectar a la ciudad, para bien o para mal, igualmente.  Algunos dioses pueden ser desconocidos para la ciudad y pueden ignorarse sin peligro. @PLa mejor forma de apaciguar a los dioses es dedicarles muchos @67templos&y&santuarios.  El dios patrón espera tener más santuarios dedicados a él o a ella que cualquier otro dios.  Cada deidad local espera menos templos y santuarios que el dios patrón, pero espera tener el mismo número de santuarios y templos que las demás deidades locales.  @PLos dioses también pueden apaciguarse con festivales, cuanto más grandes, mejor.  Los festivales suntuosos y grandiosos son medidas valiosas para ganar tiempo si un dios se enfada con la ciudad.  Celebra un festival en honor del dios enfadado, y este se calmará, lo que te dará tiempo para erigir más templos o santuarios antes de incurrir en su ira.  Visita a tu @29Supervisor&de&los&Templos para planificar un festival.  Ten en cuenta que hasta que no construyas una Plaza de festivales, la ciudad no podrá celebrar ninguno.  Los festivales grandiosos también exigen que la ciudad disponga de suficiente @96cerveza en sus @4patios&de&almacenamiento.  Debido al esfuerzo que supone planificar un festival, una ciudad solo puede celebrar dos festivales en cualquier periodo de 12 meses.    @PAdemás de templos y santuarios, también puedes construir un Complejo religioso, generalmente en honor al dios patrón de la ciudad.  Cada ciudad solo puede tener un Complejo religioso a la vez.  A veces puedes construir un Complejo religioso para una deidad local si esta se ha vuelto especialmente importante.  Pero ten cuidado: el dios patrón de la ciudad puede volverse muy celoso si otro dios tiene un Complejo religioso dedicado a él o ella. @PLos complejos religiosos son costosos, pero valen la pena.  Tener un complejo religioso en funcionamiento aporta muchos beneficios a la ciudad y aumenta su @35índice&de&prosperidad.  También puedes pagar para añadir un Oráculo y un Altar a un Complejo religioso.  Los complejos y sus añadidos son: @L@L@350Complejo&religioso&a&Osiris: @P\tAltar de Sebek @P\tOráculo de Min @L@351Complejo&religioso&a&Ra @P\tAltar de Ma'at @P\tOráculo de Horus @L@352Complejo&religioso&a&Ptah @P\tAltar de Amón @P\tOráculo de Thoth @L@353Complejo&religioso&a&Seth @P\tAltar de Anubis @P\tOráculo de Sekhmet @L@354Complejo&religioso&a&Bast @P\tAltar de Isis @P\tOráculo de Hathor @L@LOfrecer a los ciudadanos varios lugares de culto a diferentes dioses contribuye al @35índice&de&cultura de la ciudad. @L@LPara saber más sobre la religión en el antiguo Egipto, haz clic @399aquí."
        }
    }

    message_game_concept_war {
        id: 52
        
        size [30, 28]
        title {
            text: "Guerra"
        }
        subtitle {
            text: "Conceptos del juego",
        }
        content {
            text: "La guerra es una amenaza casi constante en Egipto.  A veces, invasores de otras tierras se adentran en Egipto con visiones de mayor gloria.  En otras ocasiones, los disturbios dentro de las fronteras de Egipto provocan luchas intestinas entre ciudades, o incluso una guerra civil a gran escala.  Ocasionalmente, el propio Faraón decide hacer la guerra a enemigos jurados o aliados rebeldes. @PHay muchas cosas que puedes hacer para preparar y proteger la ciudad del horror de la guerra.  Construye @85estructuras&defensivas para sellar las fronteras de la ciudad frente a las fuerzas invasoras.  También puedes construir @37fortes, @356navíos&de&guerra y @357barcos&de&transporte para atacar a cualquier enemigo que penetre en las fronteras de la ciudad. @PTu @21Supervisor&militar te advertirá de los ataques inminentes, y recibirás @34mensajes que informarán de los movimientos militares enemigos.  Puedes seguir la ruta de los enemigos que se aproximan en el @32mapa&del&mundo. @PTen cuidado de no provocar un ataque tú mismo.  Si gestionas mal la ciudad o enfureces a otros en Egipto, el @35índice&del&Reino caerá.  Si el índice del Reino baja lo suficiente, tu ciudad podría ser atacada. @PLa guerra no se limita a los alrededores de la ciudad.  En distintos momentos, Egipto participa en batallas dentro de sus propias fronteras y en todo el mundo.  A veces, otra ciudad o el Faraón pueden necesitar algunas de tus tropas o navíos de guerra para derrotar a un enemigo.  Envía las tropas para este servicio al Reino visitando a tu Supervisor militar, asignando compañías o barcos concretos para el servicio en el extranjero y enviándolos a su destino.  Si más de una ciudad pide ayuda, tendrás que visitar a tu @22Supervisor&político para elegir a qué ciudad enviar la ayuda. @L@LPara saber más sobre los enemigos del antiguo Egipto, haz clic @181aquí."
        }
    }

    message_tutorial_health {
        id: 53
        
        size [30, 28]
        title { text: "Salud" }
        subtitle { text: "Concepto del juego" }
        content {
            text: "Una mala salud en la ciudad puede disuadir a los inmigrantes de venir a tu ciudad e incluso causar la muerte de algunos residentes.  Toma medidas para que tus ciudadanos se sientan sanos.  Varias catástrofes sanitarias podrían sobrevenir a tus ciudadanos si no tomas precauciones. @PPara mantener sanos a tus ciudadanos, asegúrate de que tengan acceso a abundante comida y a un @64consultorio&de&médico.  Cuantos más tipos de alimentos coman tus ciudadanos, más sanos se sentirán.  El acceso a las @66tanatorios también mejora la salud general de la ciudad.  El agua potable limpia de un @61suministro&de&agua y el acceso a una @65botica ayudan a reducir el riesgo de malaria.  La salud general de la ciudad depende de la salud de cada uno de sus ciudadanos, así que asegúrate de proporcionar un acceso adecuado a la atención sanitaria a todos los habitantes. @PAdemás de la malaria, las enfermedades y la temida peste acechan a la ciudad.  Con una planificación cuidadosa y una vigilancia constante de la salud de los ciudadanos, estos problemas pueden evitarse. @L@LEnfermedades @LLas enfermedades aparecen en las casas que no reciben visitas frecuentes de un médico y no tienen un suministro constante de comida.  Las enfermedades afectan a las casas de forma individual y no se extienden.  Sin embargo, si todo un barrio tiene un acceso especialmente malo a médicos y a comida, más de una casa podría enfermar. @PUsa la @18Capa&de&riesgos para ver qué casas son propensas a desarrollar enfermedades.  Construye más consultorios de médico en estas zonas, y asegúrate de que los @2mercados abastecen de comida a las casas.  También puedes usar la @18Capa&de&médicos para ver qué casas tienen buen acceso a los médicos, y la @18Capa&de&acceso&al&bazar para ver qué casas reciben la visita de los comerciantes del bazar. @L@LMalaria @LLa malaria es uno de los riesgos de vivir cerca del agua.  Las casas próximas al río y a los pantanos llenos de juncos son las más expuestas.  Igual que las enfermedades, la malaria afecta a casas individuales.  Sin embargo, la enfermedad se extiende a las casas vecinas.  Para combatir el riesgo de malaria, construye muchas boticas en las zonas de riesgo y asegúrate de que las casas de estas zonas reciban agua de un suministro de agua.  Usa la @18Capa&de&malaria para ver qué casas son especialmente propensas a esta enfermedad. @L@LPeste @LLos brotes de peste se producen cuando la salud general de la ciudad es baja, con independencia de la salud de las casas concretas.  Lo único que puedes hacer para evitar las pestes es mantener la ciudad sana en general.  Por cierto, no confundas la peste con las @494grandes&pestes.  Las grandes pestes son causadas por factores fuera de tu control, no por la salud de la ciudad. @PCuando la peste estalla, comienza en una sola casa.  Uno de los individuos delirantes afectados por la peste en la casa vaga por las calles, contagiando a cada casa que pasa.  En el plazo de un mes, sucumbirá a la enfermedad.  Un herborista de una botica eliminará de inmediato a cualquier ciudadano afectado por la peste que se encuentre.  @PNinguna capa puede mostrarte qué casa será la primera víctima de la peste, porque esta no está relacionada con las condiciones de ninguna casa o barrio concreto. @L@PSi una casa se infecta con cualquiera de las dolencias anteriores, todas las personas de la casa mueren.  La casa permanece infectada durante dos meses, período durante el cual ningún inmigrante ni vagabundo se mudará a ella.  Pasados dos meses, la vivienda se limpia y vuelve a ser habitable.  Todos los bienes que poseían sus antiguos habitantes siguen allí. @PAunque se clasifica como edificio de salud, el consultorio del dentista contribuye al valor de la propiedad de una zona y no tiene ningún efecto sobre la salud de la ciudad. @PTu @26Supervisor&de&Salud&Pública te ayudará a mantener sanos a tus ciudadanos."
        }
    }

    message_bent_pyramid {
        id: 54,
        
        size [30, 28]
        title {
            text: "Pirámide acodada",
        }
        content {
            text: "Inspirados por el sol, los arquitectos que idearon la Pirámide acodada imaginaron un gigantesco obelisco de lados curvados, que representa uno de los rayos cálidos del sol.  Para que brille tan intensamente como el sol, los lados de la pirámide se alisaron. @PPara construir una Pirámide acodada necesitarás suministros de @95piedra&sin&labrar y @95caliza, y campesinos de un @8campamento&de&trabajo.  Cuando haya cuatro bloques de piedra sin labrar o de caliza almacenados en los @4patios&de&almacenamiento, los campesinos cargarán la piedra en un trineo y la arrastrarán hasta el lugar de construcción.  Para colocar correctamente las piedras son esenciales los servicios del @363Gremio&de&canteros.  El @363Gremio&de&carpinteros proporciona rampas de madera que se entregan al propio gremio. @PLas Pirámides acodadas vienen en dos tamaños.  Lee las entradas sobre @370construcción&de&monumentos, el @373Supervisor&de&monumentos y el @369Capataz&de&obras para más información. @L@LPara saber más sobre la historia de la Pirámide acodada, haz clic @392aquí."
        }
    }

    message_brick_core_pyramid {
        id: 55,
        
        size [30, 28]
        title {
            text: "Pirámide de núcleo de ladrillo",
        }
        content {
            text: "Las pirámides de núcleo de ladrillo son las más complejas que construirás.  Requieren tres tipos de materias primas y tres tipos de gremios de construcción.  Necesitas @364ladrillos, @95caliza y @94madera para construirlas, así como los servicios del @363Gremio&de&albañiles, el @363Gremio&de&canteros y el @363Gremio&de&carpinteros.  También necesitas campesinos de los @8campamentos&de&trabajo para transportar los pesados ladrillos y piedras hasta la obra, una vez que haya suficiente almacenado en los @4patios&de&almacenamiento. @PLas pirámides de núcleo de ladrillo pueden ser pequeñas, medianas, grandes, Complejo piramidal y Gran complejo piramidal. @PLee las entradas sobre @370construcción&de&monumentos, el @373Supervisor&de&monumentos y el @369Capataz&de&obras para más información. @L@LPara saber más sobre la historia de la Pirámide acodada, haz clic @392aquí."
        }
    }

    message_housing_and_desirability {
        id: 56
        
        size [35, 32]
        title { text: "Vivienda y atractivo" }
        content {
            text: "El primer paso para construir un barrio es designar una zona residencial.  Recuerda que todas las viviendas deben estar a menos de dos casillas de una calzada.  Una vez trazada la zona, los inmigrantes se instalan en sencillas chozas.  Recorren el campo de los alrededores para encontrar lo que necesitan para sobrevivir.  Con el tiempo, sin embargo, los ciudadanos empiezan a esperar que la ciudad atienda sus necesidades.  Al cumplir estas expectativas, los ciudadanos se encargan de mejorar sus condiciones de vivienda.  La calidad de las viviendas afecta a los @35índices de la ciudad, impide que los ciudadanos emigren y atrae a nuevos ciudadanos. @PLas necesidades más básicas de los ciudadanos son el acceso a @44agua limpia y a @45comida de los @2bazares.  Una vez que proporciones estos dos bienes de primera necesidad, verás cómo las chozas se convierten en chabolas y casas de adobe más estables. @PDespués de la comida y el agua, los ciudadanos empiezan a exigir una variedad de bienes y servicios.  Quieren tener en sus casas @1cerámica, @96cerveza y @60lino.  Los ciudadanos más ricos también exigirán un suministro de distintos @99artículos&de&lujo, como joyas.  A medida que sus gustos se refinan, exigen un segundo artículo de lujo importado.  Además de estas mercancías, los residentes esperan acceder a todos sus servicios favoritos, como @51religión, @49entretenimiento, @50educación y @53atención&sanitaria.  Contar con todos estos bienes y servicios anima a los residentes a mejorar sus casas hasta convertirlas en estructuras grandes y señoriales. @PLos residentes también quieren vivir en barrios atractivos.  Puedes crear bellos @79jardines y levantar @79estatuas, o cubrir las calzadas pavimentadas con baldosas de @79plaza.  Los ciudadanos apreciarán el esfuerzo que dediques a embellecer sus alrededores y probablemente mejorarán sus viviendas para estar a la altura. @PLo contrario de querer vivir en un entorno atractivo es no querer vivir en uno poco atractivo.  Los ciudadanos se resisten si sus viviendas están demasiado cerca de industrias o granjas.  Prefieren vivir lejos del ruido y del fuerte hedor que suelen emitir estas estructuras.  Además, la mayoría de los residentes considera que las estructuras industriales son un espanto.  Si debes situar viviendas cerca de industrias (y a veces no hay más remedio, para que las industrias tengan personal), intenta compensar la molestia con muchos jardines, estatuas y plazas, y con el acceso más fácil a los bienes y servicios deseados.  Aun así, probablemente tendrás que resignarte a que algunos barrios industriales marginales afeen la ciudad. @PLas ventajas de las viviendas de alta calidad son muchas.  Las viviendas muy evolucionadas tienen un efecto positivo en el @35índice&de&prosperidad.  Además, las viviendas evolucionadas albergan a más residentes, lo que permite aumentar la población de la ciudad (y, potencialmente, la mano de obra) sin designar nuevas zonas residenciales.  Cuando las viviendas alcanzan los niveles más altos, los residentes se convierten en @41escribas, que pagan impuestos pero abandonan la mano de obra de la ciudad. @PPara saber qué necesita una vivienda concreta para evolucionar, haz clic derecho sobre ella.  Sus residentes no tendrán reparo en decirte lo que quieren. @L@LLos antiguos egipcios vivían en casas de tamaños y calidades variados.  Haz clic @152 aquí para saber más."
        }
    }
    
    message_game_concept_roads {
        id: 57,
        
        size [30, 28]
        title {
            text: "Calzadas",
        }
        content {
            text: "Las calzadas empiezan siendo senderos de tierra.  A medida que mejoran las condiciones de la ciudad, sus residentes se encargan de pavimentarlas.  Una vez pavimentada una calzada, puedes colocar @79plazas sobre ella. @PUna red de calzadas bien planificada puede contribuir mucho a que tu ciudad funcione sin problemas.  Los @42transeúntes que prestan servicios a la ciudad se desplazan con más facilidad por calzadas largas y rectas que por calzadas cortas con muchas curvas, giros e intersecciones. @PCasi todas las estructuras de la ciudad necesitan acceso a las calzadas.  Las únicas excepciones son los jardines, las estatuas y los fuertes.  Los santuarios, las murallas y las viviendas no necesitan acceso directo a la calzada, pero deben estar a menos de dos casillas de ella para recibir los beneficios de los transeúntes que pasen. @PLos transeúntes solo pueden cruzar el límite entre la llanura aluvial y la tierra seca cuando hay una calzada.  Este terraplén es empinado, fangoso y traicionero, pero una calzada permite un paso seguro. @PTodas las calzadas tienen la misma capacidad de tráfico, y los transeúntes se desplazan a la misma velocidad, estén o no pavimentadas. @L@LLa Calzada del Reino @LLa calzada que atraviesa tus tierras al comenzar una nueva misión es la Calzada del Reino, y tiene un estatus especial.  Por ella llegan las caravanas comerciales y los inmigrantes, y por ella salen los emigrantes.  Cada parte de la ciudad necesita un camino despejado hasta la Calzada del Reino.  Si aíslas alguna parte de la ciudad de esta importante vía, esa zona se estancará.  Los repartidores que se dirigieran al recinto ahora aislado se detendrán en seco hasta que se restablezca el acceso.  A veces, los arquitectos reales pueden eliminar cualquier estructura que hayas construido y que bloquee el acceso.   @PEsto no significa que todas las calles de la ciudad deban conectarse físicamente con la Calzada del Reino, sino solo que todos los edificios deben tener un camino despejado y transitable, ya sea por calzada o por terreno libre. @PLo más probable es que esto sea todo lo que necesitas saber sobre la Calzada del Reino.  A la mayoría de los jugadores nunca les preocuparán los detalles del acceso a los edificios, pero hay algunas circunstancias excepcionales en las que podrías perder el acceso a la Calzada del Reino sin crear ningún obstáculo visible. @PCuando construyes algo nuevo, la estructura busca un camino hasta la Calzada del Reino, ya sea por la red de calzadas de la ciudad o por terreno libre y transitable.  La mayoría de las veces, el edificio se coloca sobre una calzada existente, así que lo que importa es el acceso de esa calzada a la Calzada del Reino.  A veces, sin embargo, construyes algo que no está sobre una calzada.  En estos casos, la nueva estructura comprueba el acceso a la Calzada del Reino a través del terreno libre intermedio.  Si después conectas este edificio a una calle de la ciudad, el edificio redefine su punto de acceso para situarse en la nueva calle.  Así, si la nueva calle no encuentra un camino transitable hasta la Calzada del Reino (quizá porque la bloquea el propio edificio al que la conectaste), el edificio que da a esta calzada también perderá el acceso a la Calzada del Reino. @PPara más información sobre los 'puntos de acceso', lee la siguiente sección. @PUn último detalle sobre la Calzada del Reino: la calzada en sí, física, no tiene nada especial; solo son cruciales los puntos por los que entra y sale de tus tierras.  Puedes reubicar partes de la Calzada del Reino como cualquier otra calzada de la ciudad, siempre que no bloquees el acceso a estos puntos vitales de entrada y salida. @L@LConstruir entre dos calzadas @LA veces puedes colocar un edificio junto a dos calzadas que no están conectadas entre sí, o que se conectan lejos del edificio.  Esto no permite a los transeúntes entrar o salir del edificio desde ambas calzadas.  Cada edificio solo puede tener un 'punto de acceso' y, por tanto, una sola calzada activa. @PPor ejemplo, supongamos que construyes un Patio de almacenamiento con una calzada en su lado sur.  Los fabricantes, las caravanas y los compradores del bazar al sur del patio interactuarán con él como cabría esperar.  Ahora supongamos que quieres que las industrias situadas al norte del patio también lo usen.  Si construyes una calzada en el lado norte del Patio de almacenamiento, podrías esperar que las industrias del norte interactúen con el patio a través de la calzada norte, mientras que las del sur seguirían usando la calzada del sur.  Pero el edificio solo puede tener un punto de acceso, así que las industrias del norte no tendrán suerte a menos que construyas un conector entre las calzadas norte y sur. @PCuando un edificio tiene dos o más calzadas adyacentes, elige su punto de acceso según la red de calzadas más amplia.  Siguiendo el ejemplo anterior, si la calzada sur forma parte de la red principal de calles de tu ciudad y la nueva calzada norte lleva a un pequeño puesto industrial, el 'punto de acceso' del Patio de almacenamiento estará en la calzada sur.  Si, por el contrario, la calzada sur original lleva a una colonia más pequeña y la nueva calzada norte conecta con la ciudad principal, la calzada norte será la ruta de acceso preferida del edificio. @PPara evitar comportamientos impredecibles, no construyas edificios que toquen dos calzadas no conectadas.  Conecta las calzadas o ten en cuenta que solo una de ellas transportará tráfico que pueda interactuar con el edificio.  Observa cómo se comportan los transeúntes de los alrededores para saber cuál es el punto de acceso del edificio. @L@LHaz clic @153 aquí para recorrer la historia de las calzadas en el antiguo Egipto."
        }
    }

    message_game_concept_water_crossings {
        id: 58,
        
        size [30, 28]
        title {
            text: "Cruces de agua",
        }
        content {
            text: "Hay dos tipos de cruces de agua: puentes y embarcaderos de ferri.  Los puentes solo pueden salvar tramos cortos de agua.  Los barcos no pueden navegar bajo los puentes, así que úsalos solo cuando la masa de agua que cruzan no tenga tráfico de barcos. @PLos puentes solo pueden colocarse donde la orilla sea recta.  La orilla correspondiente del lado opuesto también debe ser recta.  Cuando elijas un lugar adecuado para un puente, verás un 'fantasma' verde del puente junto con su coste (los puentes se cobran por casilla).  Si no has elegido un lugar adecuado, verás cuadrados rojos.  Los puentes no requieren mano de obra, pero sí acceso a una calzada. @PLos ferris atracan en los embarcaderos de ferri y funcionan de forma parecida a los puentes, pero son más versátiles.  Los ferris no obstaculizan el paso de otras embarcaciones, así que todo tipo de barcos puede ir y venir como quiera. @PAl igual que los puentes, los embarcaderos de ferri deben colocarse en un tramo de costa recto.  Cuando selecciones un lugar adecuado, verás un cuadrado verde.  No tienes que colocar el segundo embarcadero justo enfrente del primero.  Puedes elegir entre varios lugares de la otra orilla, siempre que la costa sea recta.  Los bloques verdes indicarán los lugares apropiados. @PComo los inmigrantes y emigrantes usan sus propias barcas, pueden usar los embarcaderos de ferri en cuanto se construyen.  Sin embargo, los embarcaderos de ferri necesitan trabajadores para transportar a otros ciudadanos.  Los @42transeúntes con un destino concreto, como los repartidores, los compradores del bazar y los artistas que se dirigen a sus locales, utilizan los ferris.  Ningún otro transeúnte puede subir a los ferris. @PPara transportar inmigrantes, los embarcaderos de ferri no necesitan acceso a una calzada.  Los inmigrantes cruzarán los campos para llegar al embarcadero.  Para transportar a otros ciudadanos, en cambio, los embarcaderos sí necesitan acceso a una calzada. @L@LComo el @157Nilo atraviesa sus tierras, los antiguos egipcios emplearon todo tipo de barcos para transportarse a sí mismos y sus mercancías.  Para saber más sobre la construcción naval en el antiguo Egipto, haz clic @179aquí."
        }
    }
    
    message_game_concept_irrigation {
        id: 59,
        
        size [30, 28]
        title {
            text: "Riego",
        }
        content {
            text: "Las norias y los canales de riego llevan los beneficios del Nilo a una mayor extensión de tierra.  Regar las tierras de cultivo aumenta su fertilidad. @PPara llevar los beneficios del riego a una granja, tiende un canal de riego hasta una distancia de dos casillas de ella.  Los efectos del riego no son acumulativos; mientras haya un canal de riego a menos de dos casillas de una granja, esta estará totalmente regada. @PLas granjas de la llanura aluvial están al nivel del agua, por lo que los canales de riego pueden conectarse directamente con el Nilo.  Las granjas de prado, sin embargo, no están a ese nivel.  Para regar las granjas de prado, debes construir una noria. @PLas norias elevan el agua un nivel.  Pueden construirse en terrenos contiguos a una masa de agua o a la llanura aluvial.  Para las norias construidas junto a la llanura aluvial, debes construir un canal de riego desde el Nilo hasta la parte delantera de la noria para suministrarle agua. @PConecta un canal de riego a la parte trasera de la noria para regar las granjas de prado.  Los canales de riego serpentean y dan vueltas alrededor de todos los objetos que obstaculizan su camino, excepto las calzadas.  Los canales de riego pasan automáticamente por debajo de las calzadas cuando es necesario. @PAumentar la fertilidad de sus tierras incrementará la cantidad de comida que produce una granja.  La fertilidad no afecta a la duración de la temporada de cultivo. @PIncluso las granjas regadas deben construirse sobre tierras cultivables.  El riego puede aumentar la fertilidad de la tierra, pero no puede convertir en fértil una tierra infértil. @PLa entrada sobre la @45agricultura ofrece información adicional. @L@LEn el antiguo Egipto, el descubrimiento de las técnicas de riego aumentó significativamente la superficie de tierra cultivable.  Para saber más sobre el riego, haz clic @154aquí."
        }
    }
    
    message_building_weaver {
        id: 60,
        
        size [30, 28]
        title {
            text: "Tejedor",
        }
        content {
            text: "Los tejedores convierten el lino en tela.  El lino puede cultivarse en @91granjas&de&lino o importarse de un @47socio&comercial.  Los tejedores necesitan acceso a una calzada y mano de obra.  Pueden almacenar en el propio edificio una pequeña cantidad de lino para seguir trabajando de forma continua pese a pequeñas interrupciones del suministro. @PEl lino es un producto importante en la ciudad.  Es esencial para el proceso de embalsamamiento, y los @66tanatorios necesitan un suministro de lino para funcionar adecuadamente.  Los ciudadanos también quieren tener existencias de lino en sus casas para la ropa.  @L@LPara saber más sobre la importancia del lino en el antiguo Egipto y el oficio del tejedor, haz clic @398aquí."
        }
    }
    
    message_building_water_supply {
        id: 61,
        
        size [30, 28]
        title {
            text: "Suministro de agua",
        }
        content {
            text: "Los suministros de agua y los aguadores proporcionan agua potable limpia a los barrios de la ciudad.  El agua de un suministro de agua es una de las primeras demandas que los ciudadanos te plantean cuando quieren mejorar sus @56viviendas. @PLos suministros de agua necesitan acceso a una calzada y mano de obra, y deben colocarse sobre pastizales, lo que indica la presencia de agua subterránea.  No puedes colocarlos en el desierto. @PCuando un suministro de agua tiene lo necesario para funcionar, envía un aguador.  El aguador recorre tus barrios repartiendo agua limpia a las viviendas que pasa.  Conviene revisar de vez en cuando a tus aguadores para asegurarte de que los barrios están bien abastecidos de agua limpia.  Usa la @18capa&de&agua para ver cuáles de tus casas son visitadas con frecuencia por un aguador.  Los aguadores son @42transeúntes itinerantes. @PLos aguadores trabajan más si el suministro de agua ha sido mejorado.  Cuando el atractivo de la zona circundante es lo bastante alto, los trabajadores del suministro de agua mejoran el edificio, y los aguadores recorren el barrio con más frecuencia. @PSolo las viviendas necesitan agua de los suministros de agua, y a la gente le gusta vivir cerca (consulta la entrada sobre el @56atractivo para más información sobre cómo hacer atractivo un barrio). @L@LHaz clic @156aquí para saber más sobre los retos de proporcionar agua potable limpia a la población del antiguo Egipto."
        }
    }

    message_building_well {
        id: 62,
        
        size [30, 28]
        title {
            text: "Pozo",
        }
        content {
            text: "Los pozos son fuentes rudimentarias de @44agua potable.  Solo los barrios más pobres se conformarán con el acceso a un pozo.  Para que las viviendas evolucionen hacia estructuras más señoriales, se necesita acceso a @61suministros de agua. @PLos pozos no necesitan acceso a una calzada ni empleados.  Deben colocarse sobre pastizales, lo que indica la presencia de agua subterránea.  Tienen un ligero efecto positivo sobre el @56atractivo. @PConsulta la @18capa&de&agua para ver qué zonas tienen acceso al agua de pozo. @L@LPara saber más sobre los pozos del antiguo Egipto, haz clic @156aquí."
        }
    }

    message_building_dentist {
        id: 63,
        
        size [30, 28]
        title {
            text: "Dentista",
        }
        content {
            text: "Tus ciudadanos más ricos valoran la capacidad de comer alimentos sólidos, y esperan tener acceso a un consultorio de dentista cercano para conservar o reemplazar sus dientes naturales.  En una tierra donde la arena inevitablemente acaba en los alimentos, los dentistas nunca se quedan sin trabajo.  Los dentistas aumentan el @56atractivo de las viviendas cercanas, pero no tienen efecto sobre la @53salud de la ciudad. @PUsa la @18capa&de&salud para ver los dentistas que trabajan en tu ciudad. @L@LHaz clic @158aquí para leer sobre el papel de los dentistas en el antiguo Egipto."
        }
    }

    message_building_physician {
        id: 64,
        
        size [30, 28]
        title {
            text: "Médico",
        }
        content {
            text: "Los médicos ayudan a mantener una buena @53salud en la ciudad.  Sus visitas ayudan a reducir el riesgo de enfermedades. @PA los ciudadanos les gusta tener un consultorio de médico cerca, y la @56evolución de las viviendas está limitada sin ellos. @PLos consultorios de médico necesitan mano de obra y acceso a una calzada. @PUna visita al @26Supervisor&de&Salud&Pública te ayudará a evaluar la cobertura médica de la ciudad. @L@LHaz clic @160aquí para leer más sobre las prácticas médicas egipcias."
        }
    }

    message_building_apothecary {
        id: 65,
        
        size [30, 28]
        title {
            text: "Botica",
        }
        content {
            text: "Las boticas son farmacias de barrio que emplean a herboristas.  Los herboristas retiran de la circulación a cualquier ciudadano afectado por la peste con el que se crucen en sus viajes.  Las boticas son lo más importante para reducir el riesgo de @53malaria. @PLas boticas necesitan acceso a una calzada y mano de obra para funcionar correctamente.  Para seguir el recorrido de tus herboristas, usa la @18capa&de&salud.  Verás todos los herboristas y boticas de la ciudad, además de cuánto acceso tiene cada casa a los servicios de un herborista. @PConsulta al @26Supervisor&de&Salud&Pública para más información. @L@LPara saber más sobre las prácticas farmacéuticas del antiguo Egipto, haz clic @159aquí."
        }
    }

    message_building_mortuary {
        id: 66,
        
        size [30, 28]
        title {
            text: "Tanatorio",
        }
        content {
            text: "Los embalsamadores de los tanatorios preparan a los difuntos para su viaje al más allá. @PLos tanatorios aumentan la @53salud de la ciudad al cuidar adecuadamente de los muertos.  Como la mayoría de los edificios, los tanatorios necesitan acceso a una calzada y mano de obra.  Además, necesitan un suministro de @60lino que se fabrique en la ciudad o se importe de un @47socio&comercial.  Los embalsamadores usan el lino para envolver los cuerpos de los difuntos tras el proceso de embalsamamiento. @PAunque los ciudadanos exigen tener acceso a los tanatorios, no les gustará vivir cerca de estas estructuras.  Los tanatorios son famosos por sus desagradables olores. @PPara ver dónde están los tanatorios, usa la @18capa&de&salud.  Verás a los embalsamadores atendiendo a los difuntos y recorriendo tus barrios.  Tu @26Supervisor&de&Salud&Pública proporciona información valiosa sobre los servicios funerarios de tu ciudad. @L@LEl embalsamamiento era fundamental para la creencia egipcia en el más allá.  Haz clic @161aquí para saber más sobre esta antigua práctica."
        }
    }

    message_building_shrine_and_temple {
        id: 67,
        
        size [30, 28]
        title {
            text: "Santuario y templo",
        }
        content {
            text: "No puedes apaciguar a los dioses sin santuarios ni templos.  Tanto las deidades locales como los dioses patronos exigen atención, y los ciudadanos esperan tener acceso a la religión.  Para más información sobre los efectos de los dioses en tu ciudad, consulta @51religión.  Para información sobre los efectos concretos del Complejo religioso de cada dios, elige: @L@P@350Complejo&religioso&a&Osiris @P@351Complejo&religioso&a&Ra @P@352Complejo&religioso&a&Ptah @P@353Complejo&religioso&a&Seth @P@354Complejo&religioso&a&Bast @L@PLos santuarios son pequeños monumentos dedicados a un dios concreto.  No necesitan acceso directo a una calzada, pero sí deben estar a menos de dos casillas de una para recibir los servicios de los bomberos y arquitectos.  No requieren mano de obra ni producen transeúntes, por lo que no dan acceso a la religión.  Su función principal es apaciguar a los dioses. @PPara ofrecer lugares de culto a la gente y apaciguar aún más a los dioses, construye templos.  Los templos necesitan acceso a una calzada y emplean a un personal de sacerdotes.  Cuando un templo funciona, verás a los sacerdotes llevando la religión a tu pueblo.  Al igual que los santuarios, los templos están dedicados a un dios concreto. @G73 @PTanto los templos como los santuarios mejoran el @56valor de las propiedades de los barrios en los que se encuentran.  Los santuarios y templos también contribuyen al @35índice&de&cultura de la ciudad. @L@LLa religión era el centro de la vida egipcia.  Para saber más sobre este aspecto importante de la cultura del antiguo Egipto, haz clic @399aquí."
        }
    }

    message_building_scribal_school {
        id: 68,
        
        size [30, 28]
        title {
            text: "Escuela de escribas",
        }
        content {
            text: "Las escuelas de escribas educan a la juventud acomodada de la ciudad. @PLas escuelas necesitan acceso a una calzada y mano de obra para funcionar correctamente.  También necesitan un suministro de @97papiro.  Cuando una escuela funciona bien, los maestros recorren las calles dando clases particulares a los alumnos en sus casas.  Cada vez que un maestro sale de la escuela para buscar a sus alumnos, lleva consigo algunos rollos de papiro para que los estudiantes puedan practicar sus jeroglíficos.  Cada escuela de escribas puede almacenar una pequeña cantidad de papiro en el propio edificio.  Para que las clases continúen, asegúrate de que la industria del papiro de tu ciudad prospera o de importar suficiente de un @47socio&comercial. @PTu @27Supervisor&de&Educación sabe cuántas escuelas de escribas funcionan en la ciudad.  La @18capa&de&educación te muestra dónde están todas las escuelas de escribas y qué casas tienen acceso a los maestros.  Las escuelas de escribas también contribuyen al @35índice&de&cultura de una ciudad. @L@LMuchos egipcios antiguos consideraban la escolarización como el camino hacia un futuro próspero.  Haz clic @163aquí para saber más sobre esta institución del antiguo Egipto."
        }
    }

    message_building_sun_temple {
        id: 69,
        
        size [30, 28]
        title {
            text: "Templo del Sol",
        }
        content {
            text: "Los Templos del Sol rinden un homenaje especial al culto solar, que la mayoría de los faraones tienen en gran estima. @PPara construir un Templo del Sol necesitarás @95arenisca y @94madera, además de los servicios del @363Gremio&de&carpinteros, el @363Gremio&de&canteros y el @8Campamento&de&trabajo. @PLos Templos del Sol comienzan con un obelisco de arenisca.  Antes de poder levantar el obelisco, deben almacenarse suficientes existencias de arenisca en los @4Patios&de&almacenamiento de la ciudad.  Una vez que haya arenisca suficiente, se puede colocar el Templo del Sol.  Elige el Templo del Sol en la lista de Estructuras religiosas: monumentos y selecciona una ubicación.  Si la eliges bien, verás una huella verde del monumento.  Si alguna parte de esta huella muestra un rombo rojo, algún rasgo del terreno impide construir el monumento allí.  Haz clic para empezar a levantar el obelisco de arenisca dentro del Templo del Sol. @PUna vez colocada la piedra, los carpinteros construyen un andamiaje alrededor del obelisco.  Después, los canteros decoran los laterales del obelisco de arenisca.  Cuando terminan el obelisco, comienzan a trabajar en el resto del Templo del Sol.  Primero construyen un vestíbulo y después un muro de piedra.  Una vez terminado el muro, los canteros levantan el templo anterior.  Para completar estos elementos, los canteros necesitan varios trineos cargados de arenisca que transportan los campesinos.  Mientras trabajan en el templo anterior, el muro y el vestíbulo, los canteros colocan azulejos decorativos entre los muros. @PCuando el templo anterior esté terminado y se hayan colocado todos los azulejos, el Templo del Sol estará acabado. @PConsulta al @369capataz&de&obras para conocer los avances de la construcción. Una visita al @373Supervisor&de&los&Monumentos también puede ser útil. @L@LLee sobre la historia de los Templos del Sol y de otros monumentos haciendo clic @396aquí."
        }
    }

    message_building_library {
        id: 70,
        
        size [30, 28]
        title {
            text: "Biblioteca",
        }
        content {
            text: "Los ciudadanos sofisticados necesitan acceso a bibliotecas.  Las bibliotecas aumentan el valor de las propiedades y contribuyen al @35índice&de&cultura de la ciudad. @PLas bibliotecas serían edificios inútiles con estanterías vacías si no hubiera papiro. Antes de poder construir una biblioteca, debe haber existencias de @97papiro almacenadas en los @4Patios&de&almacenamiento. Una vez construida la biblioteca, necesita un depósito de papiro en el propio edificio para funcionar correctamente. @PLas bibliotecas también necesitan acceso a una calzada y mano de obra para funcionar. Cuando la biblioteca tiene todo lo necesario, envía a un bibliotecario por la comunidad local.  Cada vez que un bibliotecario sale de la biblioteca, lleva papiro consigo para repartir literatura entre la población. @PPara llevar la cuenta de las bibliotecas de la ciudad, visita a tu @27Supervisor&de&Educación.  Para ver la ubicación exacta de las bibliotecas, usa la @18capa&de&educación. La capa muestra las bibliotecas, y puedes seguir a los bibliotecarios mientras realizan sus tareas diarias. @L@LLee todo sobre la tradición literaria del antiguo Egipto y sus bibliotecas haciendo clic @164aquí."
        }
    }

    message_building_booth {
        id: 71,
        
        size [30, 28]
        title {
            text: "Caseta",
        }
        content {
            text: "Las casetas son los @49lugares de entretenimiento más pequeños y económicos que puedes construir. Una caseta tiene un escenario en el que actúan malabaristas, que divierten al público con acrobacias y trucos que desafían la gravedad. @PLas casetas necesitan un tipo especial de acceso a la calzada: deben colocarse sobre un cruce, ya sea una encrucijada o una \"T\".  Además, las casetas deben estar completamente dotadas de personal y contar con malabaristas entrenados. El personal ayuda a controlar a la multitud y atiende las necesidades del malabarista mientras actúa.  Los malabaristas se forman en las @75Escuelas&de&malabaristas y también pueden actuar en los @72Quioscos&de&música y los @73Pabellones. @PLas viviendas necesitan acceso al entretenimiento para @56evolucionar, y los malabaristas aportan beneficios a todas las casas por las que pasan.  Tener una caseta en el barrio también aumenta el atractivo de ese barrio.  Las casetas en funcionamiento contribuyen además al @35índice&de&cultura de la ciudad. @PUna visita a tu @28Supervisor&de&Diversiones te indicará cuántos malabaristas trabajan en la ciudad.  La @18capa&de&entretenimiento muestra dónde actúan los malabaristas, y puedes verlos pasear por tus calles. @L@LLos antiguos egipcios fueron pioneros del malabarismo.  Haz clic @169aquí para saber más."
        }
    }

    message_building_bandstand {
        id: 72,
        
        size [30, 28]
        title {
            text: "Quiosco de música",
        }
        content {
            text: "Los quioscos de música son lugares de tamaño medio que tienen dos escenarios: uno para que actúen los malabaristas y otro para los músicos.  El escenario de los malabaristas está en una esquina del local, y la banda toca en un segundo escenario situado en otra esquina.   @PLos quioscos de música deben colocarse en un cruce, ya sea una encrucijada o una \"T\".  Necesitan su propio personal para atender las necesidades de los artistas, además de malabaristas y músicos entrenados. Los artistas se forman en los @75Centros&de&formación. @PLas viviendas necesitan acceso al entretenimiento para @56evolucionar, y los malabaristas y músicos aportan beneficios a todas las casas por las que pasan. Tener un quiosco de música en el barrio también aumenta el atractivo de ese barrio.  Los quioscos en funcionamiento contribuyen además al @35índice&de&cultura de la ciudad. @PUna visita a tu @28Supervisor&de&Diversiones te indicará cuántos malabaristas y músicos trabajan en la ciudad.  La @18capa&de&entretenimiento muestra dónde actúan estos artistas, y puedes verlos pasear por tus calles. @L@LLos antiguos egipcios eran músicos consumados. Aprende más haciendo clic @170aquí. Aprende sobre el malabarismo del antiguo Egipto haciendo clic @169aquí."
        }
    }

    message_building_pavilion {
        id: 73,
        
        size [30, 28]
        title {
            text: "Pabellón",
        }
        content {
            text: "El mayor de los lugares de entretenimiento, los pabellones tienen tres escenarios: uno para espectáculos de malabarismo, otro para conciertos y otro para danzas.  Ningún ciudadano se quejará de vivir junto a un pabellón. @PLos pabellones deben colocarse en un cruce, ya sea una encrucijada o una \"T\".  Necesitan su propio personal para atender las necesidades de los artistas, además de malabaristas, músicos y bailarines entrenados. Los artistas se forman en los @75Centros&de&formación. @PLas viviendas necesitan acceso al @49entretenimiento para @56evolucionar, y los artistas aportan beneficios a todas las casas por las que pasan. Tener un pabellón en el barrio también aumenta el atractivo de ese barrio.  Los pabellones en funcionamiento contribuyen además al @35índice&de&cultura de la ciudad. @PUna visita a tu @28Supervisor&de&Diversiones te indicará cuántos malabaristas, músicos y bailarines trabajan en la ciudad.  La @18capa&de&entretenimiento muestra dónde actúan estos artistas, y puedes verlos pasear por tus calles. @L@LDescubre la última moda de danza del antiguo Egipto haciendo clic @171aquí. Conoce su música haciendo clic @170aquí y sus prácticas de malabarismo haciendo clic @169aquí."
        }
    }

    message_building_senet_house {
        id: 74,
        
        size [30, 28]
        title {
            text: "Casa del senet",
        }
        content {
            text: "Una casa del senet ofrece un lugar donde la gente disfruta de una tranquila partida de senet, un juego que representa el viaje al más allá.  Con jarras de cerveza espumosa al alcance de la mano, los ciudadanos pasan las horas en compañía de otros y disfrutan de una pequeña competición amistosa.   @PAdemás de trabajadores y acceso a la calzada, una casa del senet necesita un suministro de @96cerveza para servir a sus clientes. @PConsulta a tu @28Supervisor&de&Diversiones para saber cuántas casas del senet hay en la ciudad. Usa la @18capa&de&entretenimiento para ver qué casas tienen acceso a una casa del senet. @PA la gente no le gusta vivir demasiado cerca de las casas del senet (haz clic @56aquí para saber más sobre el atractivo).  La clientela suele ser ruidosa y alborotadora, sobre todo los perdedores de las partidas de senet con apuestas altas. @L@LEl senet era mucho más que un juego. Para saber más, haz clic @172aquí."
        }
    }

    message_building_trading_centers {
        id: 75,
        
        size [30, 28]
        title {
            text: "Centros de formación",
        }
        content {
            text: "Para aprender su oficio, los malabaristas, bailarines y músicos deben formarse en un centro. Cada disciplina tiene su propio lugar de enseñanza: los malabaristas aprenden sus trucos en las Escuelas de malabaristas, los músicos estudian en los Conservatorios y los bailarines se entrenan en las Escuelas de danza. @PCada uno de estos edificios necesita acceso a la calzada y su propio personal. Cuando los artistas terminan su formación, se dirigen al lugar de entretenimiento más cercano que necesite sus servicios. Mientras se desplazan hacia los lugares de entretenimiento, las casas por las que pasan obtienen acceso a su tipo de espectáculo. @PUna vez que los artistas llegan a su destino, ofrecen una actuación durante un número determinado de días. Si haces clic con el botón derecho en cualquier lugar de entretenimiento, verás qué artistas están entreteniendo al público y cuántos días más se disfrutarán sus actuaciones. Cuanto más cerca esté un Centro de formación de un lugar de entretenimiento, más larga será la función. Cuando termina la temporada de actuaciones, los artistas regresan a casa. Si no se forman nuevos artistas que ocupen su lugar, el lugar de entretenimiento quedará vacío y no ofrecerá diversión a tus habitantes. @PA tus habitantes no les importará vivir cerca de una Escuela de malabaristas. Sus divertidas payasadas son casi tan entretenidas cuando practican como cuando actúan. Sin embargo, a nadie le gusta vivir cerca de las Escuelas de danza o de los Conservatorios. Los artistas van y vienen a todas horas, y los músicos ensayando no producen los sonidos más agradables. @PPara ver cómo los artistas se desplazan desde sus escuelas hasta los lugares de actuación, usa la @18capa&de&entretenimiento. @L@LLos egipcios encontraron muchas formas de entretenerse.  Haz clic @165aquí para saber más."
        }
    }

    message_building_courthouse {
        id: 76,
        
        size [30, 28]
        title {
            text: "Tribunal",
        }
        content {
            text: "Los tribunales son edificios municipales polivalentes. Además de reducir el @36crimen en los barrios de la ciudad, también almacenan una parte de la riqueza de la ciudad. A los ciudadanos les gusta la seguridad que aportan los tribunales y disfrutan viviendo cerca de estas imponentes estructuras. @PLos tribunales necesitan acceso a la calzada y mano de obra antes de poder enviar magistrados a patrullar las calles de la ciudad. La presencia de un magistrado en un barrio reduce la probabilidad de que surja el crimen allí.  Los magistrados solo son una medida preventiva; si estalla un delito, el magistrado no puede impedir que el delincuente siga con su fechoría. @PParte del @48dinero de la ciudad se guarda en los tribunales. No podrás decidir cuánto dinero se guarda en cada tribunal.  Tu @30Supervisor&del&Tesoro está mucho mejor preparado para encargarse de esto y calculará una cantidad adecuada.  @L@LLos tribunales eran lugares muy activos en el antiguo Egipto.  Para saber más sobre el derecho egipcio antiguo, haz clic @183aquí."
        }
    }
    
    message_building_palace {
        id: 77,
        
        size [30, 28]
        title {
            text: "Palacio",
        }
        content {
            text: "El palacio de la ciudad es la sede del poder.  @PEl palacio es un recurso muy valioso para tu ciudad, y deberías intentar construir uno lo antes posible. Solo se permite un palacio por ciudad. Según tu rango y la importancia de la ciudad, puedes construir un Palacio de aldea, un Palacio de pueblo o un Palacio de ciudad. @PUna ciudad necesita un Palacio para recaudar impuestos. Tus ciudadanos dudarán de tu poder hasta que establezcas una presencia fuerte y centralizada. También puedes ajustar el tipo impositivo desde el Palacio. Haz clic con el botón derecho en el Palacio y usa los botones de desplazamiento de la parte superior de la pantalla para ajustar el tipo impositivo. Para más información sobre los impuestos, haz clic @48aquí. @PLas bóvedas del palacio guardan una parte de los fondos de la ciudad. La pantalla que aparece al hacer clic con el botón derecho te indica exactamente cuánto almacena el edificio. Consulta @48dinero para saber más sobre cómo se guardan los fondos en toda la ciudad. @PEl palacio también ofrece un resumen del estado de tu ciudad. Sitúa el cursor sobre el edificio y aparecerá un informe con el tipo impositivo, los índices y la tasa de desempleo de la ciudad. @PSi tu ciudad tiene la fortuna de encontrarse en una zona de @93minas de oro, el palacio cumple otra función vital.  El mineral de oro se lleva directamente de las minas al palacio, donde se refina y se transforma en dinero.  Los debens resultantes se añaden directamente al tesoro de la ciudad.  El oro nunca se comercia ni se traslada a ningún otro lugar que no sea un Palacio. @PSi el faraón honra a tu ciudad con una visita real, se alojará en el Palacio. @PLa sede del gobierno es uno de los edificios más hermosos y respetados de tu ciudad. A la gente le encanta vivir cerca; algunos creen que refuerza su propio prestigio dentro de la comunidad.   @PEl palacio necesita acceso a la calzada y una plantilla de trabajadores para llevar a cabo su labor. El palacio también necesita acceso al agua subterránea por si recibe la visita de un personaje real. Por ello, al menos una parte del edificio debe colocarse sobre pastizales.  @L@LConoce el gobierno y la burocracia del antiguo Egipto haciendo clic @174aquí."
        }
    }

    message_building_mansion {
        id: 78,
        
        size [30, 28]
        title {
            text: "Mansión",
        }
        content {
            text: "Construye una magnífica residencia en la ciudad para afianzar tu poder y tu prestigio. Tu mansión guarda la riqueza de tu familia, y no podrás cobrar un @48salario hasta que te hayas construido un hogar. Los habitantes de la ciudad quieren asegurarse de que te quedarás de forma permanente en la comunidad antes de permitir que cobres un sueldo.  @PTu sueldo se fija según tu experiencia. Si crees que mereces más o menos dinero, puedes establecer tu propio nivel salarial.  Haz clic con el botón derecho en la mansión y aparecerá una pantalla que muestra tu salario actual en un botón. Haz clic en este botón y verás una lista de todos los rangos del reino con sus niveles salariales. Elige un nuevo salario de esta lista y se te pagará en consecuencia. Eso sí, pagarte más de lo que vales tendrá un efecto negativo en el @35índice&del&reino. También puedes fijar tu salario personal consultando a tu @30Supervisor&del&Tesoro. @PTu residencia necesita acceso a la calzada y una fuente de agua subterránea. Por ello, al menos una parte de la mansión debe estar sobre pastizales. Todo el mundo quiere ser tu vecino, así que tu hogar aumenta considerablemente el atractivo de los alrededores. @PSegún tu rango y las posibilidades de tu ciudad, puedes construir una Mansión personal, una Mansión familiar o la ultralujosa Mansión de la dinastía. @L@LLos faraones vivían en residencias colosales que empequeñecían las casas de la clase trabajadora.  Para saber más sobre estas impresionantes moradas, haz clic @175aquí."
        }
    }
    
    message_building_garden_plaze_statue {
        id: 79,
        
        size [30, 28]
        title {
            text: "Jardín, plaza y estatua",
        }
        content {
            text: "Tener comida y servicios en abundancia está muy bien, pero los ciudadanos no amarán de verdad sus hogares a menos que embellezcas sus alrededores. Las plazas, los jardines y las estatuas realzan el ambiente de un barrio y aumentan el valor de las propiedades. Ninguna de las estructuras de embellecimiento necesita mano de obra, y todas pueden construirse seleccionando el botón correspondiente de embellecimiento en la lista de estructuras municipales.  @PLos jardines son lugares encantadores donde la gente descansa después de una dura jornada de trabajo. Cuanto más terreno les asignes, más lujosos serán. Los jardines no necesitan acceso a la calzada.   @PLas estatuas recuerdan a tus ciudadanos la gloria del antiguo Egipto. Hay tres tamaños: pequeño, mediano y grande. Para construirlas, basta con elegir un tamaño y encontrar un buen emplazamiento. Mientras mantienes el cursor sobre un lugar, pulsa la tecla \"R\" de tu teclado. Mientras mantienes pulsada la tecla, se mostrarán cuatro estatuas diferentes que irán girando. Cuando la estatua que quieres mire en la dirección deseada, haz clic. Las estatuas no necesitan acceso a la calzada. @G72 @PLas plazas son @57calzadas de lujo. Solo pueden construirse sobre calzadas que los ciudadanos hayan pavimentado. Los ciudadanos pavimentan las calzadas cuando sus barrios son lo bastante @56atractivos, y las plazas aumentan aún más ese atractivo. Construir plazas es muy parecido a construir calzadas. Haz clic en el botón de plaza y después en la calzada pavimentada que quieres cubrir con una loseta. Las plazas no cambian en modo alguno la función ni la capacidad de la calzada. Puedes cubrir grandes tramos a la vez arrastrando el cursor del ratón, pero vigila el coste. @L@LLos jardines eran casi una necesidad para los antiguos egipcios. Haz clic @176aquí para leer sobre estos frondosos entornos y conocer el arte público en Egipto."
        }
    }
    
    message_building_tax_collector {
        id: 80,
        
        size [30, 28]
        title {
            text: "Recaudador de impuestos",
        }
        content {
            text: "Los recaudadores de impuestos patrullan las calles de la ciudad para asegurarse de que los habitantes pagan su parte justa. @PLos recaudadores trabajan desde una oficina de recaudación de impuestos, que necesita acceso a la calzada y mano de obra. Además, la ciudad debe tener un @77Palacio en funcionamiento antes de que el recaudador pueda cumplir con su deber. @PUna parte de los fondos de la ciudad se guarda en cada oficina de recaudación de impuestos.  @PFijar el tipo impositivo puede ser delicado. Debes equilibrar las necesidades del tesoro de la ciudad con la paciencia de los ciudadanos. La gente no tolera pagar un tipo impositivo alto durante mucho tiempo y no dudará en abandonar tu ciudad en busca de una situación más asequible. Si una parte de la población paga un tipo alto mientras otra no paga nada, el @39ánimo&de&la&ciudad se desplomará, lo que podría provocar @36crimen. Visita a tu @30Supervisor&del&Tesoro y consulta la entrada sobre el @48dinero para recibir consejo sobre cómo fijar el tipo impositivo. @L@LLos antiguos egipcios pagaban impuestos al faraón para financiar el gobierno.  Haz clic @173aquí para obtener más información sobre los impuestos en el antiguo Egipto."
        }
    }

    message_building_architect_post {
        id: 81,
        
        size [30, 28]
        title {
            text: "Puesto de arquitecto",
        }
        content {
            text: "Las grandes estructuras, como los Patios de almacenamiento, las minas, los Graneros, los Templos y los Complejos religiosos, son propensas a derrumbarse.  Los arquitectos que patrullan las calles de la ciudad reparan los defectos estructurales antes de que llegue el desastre.  Los arquitectos tienen su base en los Puestos de arquitecto. @G68 @PLos Puestos de arquitecto necesitan acceso a la calzada y mano de obra para funcionar correctamente.  @PPuedes comprobar si un edificio concreto corre riesgo de derrumbe usando la @18capa&de&riesgos:&daños. Si observas que un edificio o un grupo de edificios tiene un alto riesgo de derrumbe, es posible que quieras colocar un Puesto de arquitecto cerca para asegurarte de que un arquitecto preste sus servicios. @PEl derrumbe puede tener efectos catastróficos.  Si un @3Granero o un @4Patio&de&almacenamiento se derrumba, se perderá cualquier alimento o mercancía almacenada allí."
        }
    }

    message_building_whipwright {
        id: 82,
        
        size [30, 28]
        title {
            text: "Astillero",
        }
        content {
            text: "Los astilleros suministran barcos con fines comerciales y militares. Construyen barcos de pesca para los @84Muelles&de&pesca, navíos de guerra para los @356Muelles&de&guerra y barcos de transporte para los @357Muelles&de&transporte. Los astilleros deben construirse en un tramo recto de la costa. Sabrás que has elegido un lugar viable cuando veas un \"fantasma\" verde del astillero. @PConstruye el astillero junto a una masa de agua navegable, como el Nilo o una costa marina.  Los astilleros situados en calas estrechas o en aguas interiores no podrán enviar sus barcos a los muelles que los esperan.  Esto puede hundir todo tu esfuerzo marítimo, ya que el astillero construirá barcos una y otra vez que se hundirán en cuanto determinen que no pueden alcanzar sus muelles de destino. @PLos astilleros necesitan mano de obra y acceso a la calzada para funcionar. También necesitan un suministro de madera para construir barcos de transporte y navíos de guerra. No necesitan madera para construir barcos de pesca. Los astilleros reciben órdenes de construir un barco directamente desde los muelles. Una vez terminado el barco, zarpa desde el astillero hasta el muelle correspondiente. A menos que necesites construir muchos barcos con rapidez, un solo astillero debería bastar para cubrir tus necesidades. @PSi un navío de guerra o un barco de transporte sufre daños en combate, envíalo al astillero para repararlo. Los barcos muy dañados llegan cojeando al astillero por iniciativa de sus capitanes. El astillero reparará los daños si dispone de madera. @PLos astilleros no construyen los barcos que usan los @58Embarcaderos de ferry.  Los barqueros proporcionan las embarcaciones para transportar a sus pasajeros, y los inmigrantes y emigrantes tienen sus propios barcos. @PLos astilleros hacen mucho ruido, así que nadie quiere vivir cerca. @L@LLos antiguos egipcios construían barcos de distintas formas y tamaños.  Para saber más sobre esta antigua industria, haz clic @179aquí."
        }
    }
    
    message_building_dock {
        id: 83,
        
        size [30, 28]
        title {
            text: "Muelle",
        }
        content {
            text: "Parte de los @47socios&comerciales de la ciudad llega por agua. Grandes barcos mercantes descienden por el Nilo, pero no servirán de nada a su ciudad si no tienen dónde atracar. Construya un Muelle en la orilla para que las barcazas puedan amarrar. Asegúrese de situar el Muelle junto al Nilo o en una costa marina, por donde navegan los barcos mercantes. Un Muelle construido en una ensenada estrecha o en una masa de agua interior no podrá recibir barcos comerciales. @PPara funcionar correctamente, los Muelles también necesitan acceso por carretera y mano de obra. Una vez atracado un barco, los empujadores de carros del Muelle descargan con diligencia las mercancías y las llevan a los @4Patios&de&almacenamiento de la ciudad; después cargan las mercancías que la ciudad exporta a este socio y las devuelven al Muelle. Es buena idea construir un Patio de almacenamiento cerca del Muelle para acortar los trayectos de los empujadores de carros. @PLos Muelles tienen un efecto negativo sobre el @56atractivo de una zona. @L@LPara saber más sobre el comercio en el antiguo Egipto, haga clic @177aquí."
        }
    }

    message_building_fishing_wharf {
        id: 84,
        
        size [30, 28]
        title {
            text: "Embarcadero de pesca",
        }
        content {
            text: "Si ve peces saltando periódicamente fuera del agua, los pescadores pueden capturarlos para alimentarse. Para pescar, la ciudad necesita uno o más barcos de pesca. @PLos barcos de pesca amarran en los Embarcaderos de pesca. Estos deben construirse en un tramo recto de orilla, y la mitad de la estructura debe sobresalir sobre el agua para que las embarcaciones puedan acceder a ellos. Asegúrese de que el barco de pesca pueda navegar por las aguas alrededor del Embarcadero. Si coloca el Embarcadero en una ensenada estrecha, los barcos no podrán llegar a él. Esto puede frustrar todo su esfuerzo marítimo, ya que los carpinteros de barcos construirán una y otra vez barcos de pesca que se hundirán en cuanto no logren llegar a su embarcadero. @PSi la ciudad cuenta con un @82Astillero en funcionamiento, construir un Embarcadero de pesca indica a los constructores navales que se pongan a trabajar en un barco de pesca. El Astillero no necesita materias primas para construir un barco de pesca. @PLas reservas de pescado son limitadas, pero nunca pueden agotarse por completo. Una población numerosa no podría subsistir solo de pescado. @PLos Embarcaderos de pesca son lugares malolientes y son @56vecinos indeseables. @L@LHaga clic @186aquí para saber más sobre la pesca en el antiguo Egipto."
        }
    }

    message_building_defensive_structures {
        id: 85,
        
        size [30, 28]
        title {
            text: "Estructuras defensivas",
        }
        content {
            text: "El @37ejército y la @356marina defienden la ciudad cuando los enemigos atraviesan sus fronteras. Construir estructuras defensivas puede impedir que los enemigos lleguen a pisar siquiera el interior de la ciudad. @L@LMuros @LLa estructura defensiva más básica es el Muro. Para construir Muros, elíjalos en la lista Estructuras militares: Estructuras defensivas. Haga clic y arrastre el ratón para construir grandes tramos de Muro de una vez, igual que con las carreteras. @PLos Muros de una sola capa de grosor solo retrasan brevemente a los enemigos. Para defender mejor su ciudad de un ataque, construya Muros de varias capas de grosor. A los soldados enemigos les costará mucho más tiempo atravesar un Muro grueso. @PLos Muros se levantan con los materiales naturales que haya a mano, así que no hace falta extraer ni importar piedra para construirlos. Aun así, son caros de construir, por lo que conviene pensar bien el perímetro que se quiere encerrar. @PLos Muros no necesitan acceso por carretera y son @56vecinos indeseables. @L@LTorres @LConstruya Torres para dotar de algo de capacidad ofensiva a sus Muros defensivos. Las Torres están guarnecidas por guardias adiestrados por el @88Reclutador de la ciudad, que lanzan jabalinas contra cualquier enemigo lo bastante valiente o temerario como para acercarse a su alcance. @PSiempre que el Muro sea lo bastante ancho para caminar por él, las Torres también envían centinelas a patrullar a lo largo del Muro y lanzan flechas contra los enemigos que se aproximan. @PLas Torres deben construirse integradas en Muros de dos capas de grosor. También necesitan acceso por carretera, empleados y centinelas procedentes de la oficina de un Reclutador. ¡No construya los Muros tan gruesos que los guardias de las Torres no puedan disparar por encima de ellos! @L@LPuertas de guardia @PPor muy reconfortante que resultara, no puede rodear su ciudad completamente con Muros. Para dejar entrar a los inmigrantes y a las caravanas de comerciantes, necesita Puertas de guardia. @PConstruya las Puertas de guardia allí donde sus principales caminos de acceso lleguen a los Muros de la ciudad. Mientras mantiene el cursor del ratón sobre el lugar deseado, pulse 'R' para cambiar la dirección en la que mira la Puerta de guardia. Una vez colocadas, las Puertas se conectarán automáticamente a cualquier Muro adyacente. Si se amenaza con un ataque, los guardias cerrarán las puertas para mantener fuera al enemigo. @PAl igual que los Bloqueos de carretera, las Puertas de guardia permiten el paso libre a los caminantes con destino, pero hacen retroceder a los caminantes errantes (haga clic @42aquí para saber más sobre los caminantes). @PPara más información, consulte la entrada sobre la @52guerra. @L@LLas ciudades estaban bien defendidas en el antiguo Egipto. Haga clic @182aquí para saber más."
        }
    }

    message_building_police_station {
        id: 86,
        
        size [30, 28]
        title {
            text: "Comisaría",
        }
        content {
            text: "Los agentes mantienen a raya el crimen mientras patrullan sus barrios. @PLos agentes tienen su base en las Comisarías, que necesitan acceso por carretera y mano de obra. Una bandera ondea en lo alto de la Comisaría cuando está en funcionamiento. @PLa presencia de un agente en un barrio reduce la probabilidad de que surja allí el crimen. Si su función preventiva fracasa, el agente combate activamente el delito. Si encuentra a un ladrón en la calle, lo reduce y le impide cometer su fechoría. Los agentes son también una de sus mejores armas contra los @477saqueadores&de&tumbas. @PLos agentes hacen lo que pueden frente a otras amenazas, como las invasiones extranjeras o los ataques de animales salvajes. Un solo agente, sin embargo, no sirve de nada frente a una manada de animales o a un ejército extranjero. Un agente luchará hasta la muerte, pero probablemente no logrará abatir al enemigo. Solo tienen posibilidades de derrotar a estos poderosos adversarios si actúan juntos. Aun así, derrotar a un ejército enemigo es asunto de los militares, que también son los más eficaces frente a una manada de animales salvajes. @G55 @PPara ver qué barrios tienen más probabilidades de producir delincuentes, use la @18Superposición&de&riesgos. La Superposición de riesgos puede ayudarle a planificar la ubicación de sus Comisarías. @PAunque ningún ciudadano querría vivir en un barrio sin patrulla de agentes, tampoco quiere nadie tener la Comisaría al lado. Los agentes van y vienen a todas horas y con frecuencia traen consigo a individuos de mala reputación. @L@LTiene derecho a saber más sobre la ley del antiguo Egipto haciendo clic @183aquí."
        }
    }

    message_company_orders {
        id: 87,
        
        size [30, 28]
        title {
            text: "Órdenes de la compañía",
        }
        content {
            text: "Para situar una @37compañía en el campo, o simplemente para ordenarle que se traslade a un nuevo lugar, haga clic sobre ella y luego en la nueva ubicación. El estandarte de la compañía aparecerá en el nuevo lugar y la compañía marchará hacia allí, siempre que los soldados puedan llegar. Tenga en cuenta que el escarpado y fangoso terraplén entre una llanura aluvial y tierra firme es intransitable, salvo donde una carretera une ambos terrenos.   @PPuede dar a una compañía las siguientes órdenes:  @L@LMantener posición en formación cerrada @LEn formación cerrada, los soldados se colocan lo más juntos posible. Como se les ha ordenado mantener posición, no abandonarán su puesto para atacar al enemigo. Sin embargo, atacarán a cualquier enemigo que entre en su alcance. La formación cerrada reduce el terreno que los soldados pueden defender y los convierte en un blanco más fácil para las flechas enemigas. Su postura hombro con hombro refuerza su resistencia defensiva en el combate cuerpo a cuerpo.   @L@LMantener posición en formación abierta  @LEsta orden solo puede darse a la infantería y a los arqueros; no puede darse a los aurigas. Los soldados en formación abierta se dispersan para cubrir más terreno mientras mantienen sus posiciones. Atacarán si un enemigo entra en su alcance. Esta formación hace que la infantería y los arqueros sean menos vulnerables a las flechas enemigas, pero no ofrece mucha protección frente al ataque de la infantería enemiga, ya que cada soldado de la línea solo puede defenderse a sí mismo.   @L@LAtacar a los enemigos cercanos @LCuando recibe esta orden, la compañía se mueve para atacar a los enemigos de sus inmediaciones. El ataque continúa hasta que el enemigo muere o se retira, o hasta que usted da otra orden... o hasta que la moral de su propia compañía derrotada se quiebra y sus hombres regresan al Fuerte. @L@LRastreo   @LCuando recibe la orden de rastrear, los soldados buscan a cualquier enemigo en una zona amplia y lo atacan. Las compañías con orden de rastreo son las más agresivas: rompen por completo la formación y combaten sin temor contra el enemigo. Sin embargo, esa ausencia de temor dificulta su capacidad de defenderse, así que esta orden es más conveniente cuando el ejército de la ciudad supera en número a sus enemigos.   @L@LCarga  @LLa orden de carga solo puede darse a los aurigas. Cargar contra una línea enemiga rompe su formación y la hace más vulnerable al ataque. Cuando reciben la orden de cargar, los aurigas espolean a los caballos hasta que sudan y llevan los carros a máxima velocidad durante una gran distancia. Con el tiempo, los caballos se cansan y los carros frenan y necesitan descansar, así que dé esta orden con moderación.   @L@LVolver al Fuerte   @LHaga clic en Volver al Fuerte cuando sus soldados hayan cumplido con su deber y derrotado al enemigo. En el Fuerte podrán descansar para la siguiente batalla.   Si la moral está baja, regresarán al Fuerte por su cuenta.  @L@LAdemás de las órdenes específicas descritas anteriormente, también puede ordenar a las compañías que ataquen seleccionándolas y haciendo clic sobre un enemigo. La compañía perseguirá al enemigo señalado hasta la muerte, a menos que usted dé otra orden. @L@LPara saber más sobre la guerra en el antiguo Egipto, haga clic @184aquí."
        }
    }

    message_building_recruiter_academy {
        id: 88,
        
        size [30, 28]
        title {
            text: "Reclutador y Academia",
        }
        content {
            text: "Los hombres dispuestos a luchar por su ciudad acuden a la oficina del Reclutador para alistarse. Para recibir un entrenamiento adicional, pueden pasar a la Academia. Tanto la oficina del Reclutador como la Academia necesitan acceso por carretera y mano de obra.   @PLa función del Reclutador es muy sencilla: alista a los hombres en el @37ejército de su ciudad y les proporciona cualquier armamento especial que puedan necesitar. Para equipar a los aspirantes a infantes, el Reclutador necesita un almacén de armas, importadas de un @47socio&comercial o fabricadas por un @98Armero. Para alistar aurigas, el Reclutador necesita carros de un @98Fabricante&de&carros o de un socio comercial. Los hombres que sueñan con ser arqueros aportan sus propios arcos y flechas. El Reclutador también asigna a los reclutas al servicio de centinela en los Muros de la ciudad y en sus @85Torres, según se necesite. @PLos nuevos soldados salen del Reclutador con sueños de gloria y el armamento necesario, pero con poco más. La Academia adiestra a estos infantes, arqueros y aurigas novatos en las artes más refinadas de la guerra. Los centinelas aprenden su oficio sobre la marcha y no asisten a la Academia. Una vez completados sus estudios, los soldados se dirigen a los Fuertes de sus compañías. @PSi la ciudad no tiene Academia, los soldados van directamente de la oficina del Reclutador al Fuerte de su compañía. @G57 @PDebido al carácter rudo de quienes están asociados con el ejército, el Reclutador y la Academia tienen un efecto negativo sobre el @56atractivo. @L@LDescubra más sobre la guerra en el antiguo Egipto haciendo clic @184aquí."
        }
    }

    message_building_grain_farm {
        id: 89,
        
        size [30, 28]
        title {
            text: "Granja de cereales",
        }
        content {
            text: "El grano no es distinto de cualquier otro alimento de la ciudad, pero las Granjas de cereales producen también una materia prima como subproducto: la paja. La paja sirve de forraje para el ganado de las @360Ganaderías&de&vacuno y es una de las materias primas necesarias para la @364fabricación de ladrillos. La paja (junto con la carne de caza) se usa también como forraje para los animales del @479Zoo. @PLa paja se cosecha al mismo tiempo que el grano. Un repartidor la lleva directamente a las Ganaderías, a los Fabricantes de ladrillos, a los Zoos o a los @4Patios&de&almacenamiento, mientras su compañero transporta la cosecha de grano hasta el Granero o el Patio de almacenamiento de destino. @PLas Granjas de cereales son vecinos indeseables y reducen el valor de cualquier vivienda cercana. @POtros temas que pueden resultarle útiles son @45Alimentos&y&agricultura, @2Mercados y @3Graneros. @L@LHaga clic @185aquí para leer sobre el grano en el antiguo Egipto."
        }
    }

    message_building_fruit_vegetables_farm {
        id: 90,
        
        size [30, 28]
        title {
            text: "Granjas de frutas y verduras",
        }
        content {
            text: "Las frutas y las verduras pueden sostener una vida tan sana como cualquier otro tipo de alimento y aportan una variedad bienvenida a cualquier dieta. Las distintas regiones de Egipto producen cultivos diferentes. Entre los cultivos que pueden estar disponibles para sus ciudadanos figuran las granadas, los higos, los garbanzos y la lechuga. @PLas granjas de frutas y verduras funcionan igual que el resto de granjas de alimentos. No producen más que alimentos. Consulte la sección @45agricultura para obtener consejos completos sobre cómo planificar sus granjas y obtener el máximo beneficio. @PAmbos tipos de granja necesitan mano de obra y acceso por carretera para producir cosechas. En las granjas de la llanura aluvial, esta mano de obra procede de los @8Campamentos&de&trabajo, así que asegúrese de establecer uno o más Campamentos de trabajo cerca de sus granjas. @L@LLos egipcios comían una gran variedad de alimentos y disfrutaban de una cocina sabrosa. Haga clic @187aquí para saber más sobre el menú egipcio."
        }
    }

    message_building_barley_flax_henna_farm {
        id: 91,
        
        size [30, 28]
        title {
            text: "Granjas de cebada, lino y alheña",
        }
        content {
            text: "Las Granjas de cebada, lino y alheña son algo distintas de las @89granjas&de&cereales y de las @90granjas&de&frutas&y&verduras. Estas granjas no producen alimentos, sino materias primas que se transforman en productos valiosos. La cebada se cosecha y se convierte en @96cerveza, el lino se teje para hacer @60tela de lino y la alheña se machaca y se mezcla con líquido para fabricar @470pintura. @PSin embargo, las Granjas de cebada, lino y alheña se construyen y funcionan igual que el resto de granjas. Pueden situarse en cualquier parte de la llanura aluvial. Fuera de ella, deben colocarse en prados cultivables, identificados por las matas de vegetación amarilla. Sabrá que ha elegido un buen lugar cuando vea un «fantasma» verde de la granja antes de colocarla. Las granjas deben estar junto a una carretera y necesitan mano de obra. Las granjas de la llanura aluvial no contratan mano de obra directamente, sino que dependen de los campesinos de los @8Campamentos&de&trabajo. Lea la sección sobre la @45agricultura antes de planificar sus granjas. @PUna vez cosechados la cebada, el lino y la alheña, las cosechas se llevan al fabricante más cercano (Cervecería en el caso de la cebada, Tejedor en el del lino y Fabricante de pintura en el de la alheña). En los fabricantes, la cebada, el lino o la alheña se transforman en un producto final que se distribuye entre sus ciudadanos, se utiliza en el @363Gremio&de&artesanos o se @47comercia&para obtener beneficios. Si no hay espacio en los fabricantes, o si no existe ninguno en la ciudad, la cebada, el lino y la alheña se llevan a un @4Patio&de&almacenamiento. @PLas tres granjas tienen un impacto negativo sobre el @56atractivo de los terrenos cercanos. @L@LPara saber más sobre la historia del cultivo de la cebada, haga clic @185aquí. Para descubrir cómo se cosechaba el lino en el antiguo Egipto, haga clic @189aquí. Para saber más sobre las plantas de alheña, haga clic @469aquí."
        }
    }

    message_building_clay_pit {
        id: 92,
        
        size [30, 28]
        title {
            text: "Pozo de arcilla",
        }
        content {
            text: "Los Pozos de arcilla producen arcilla que puede moldearse para fabricar @1cerámica, combinarse con @89paja para hacer @364ladrillos, o llevarse a un @363Gremio&de&artesanos y convertirse en yeso. @PLos Pozos de arcilla deben tener acceso a la carretera y a una reserva de mano de obra. Solo pueden situarse cerca del agua. @PCuando los trabajadores del Pozo han extraído arcilla suficiente para llenar un carro, el Pozo envía a un repartidor para llevar la mercancía a quien la necesite. El repartidor siempre intenta llevar la arcilla a una Fábrica de ladrillos, a un Alfarero o a un Gremio de artesanos que la necesite, dando preferencia al más cercano. Si ninguna de estas industrias necesita la materia prima, el repartidor lleva la arcilla al @4Patio&de&almacenamiento más cercano que pueda aceptarla. Si nadie puede aceptarla, la entrega espera hasta que haya espacio disponible. @PLos Pozos de arcilla son agujeros oscuros y feos excavados en la tierra, y sus ciudadanos más exigentes no querrán vivir cerca de unas instalaciones tan poco atractivas. @L@LLos antiguos egipcios aprovecharon muy bien los ricos depósitos de arcilla y barro que dejaba la inundación anual del Nilo. Haga clic @190aquí para saber más sobre este valioso recurso."
        }
    }

    message_building_gold_copper_mine {
        id: 93,
        
        size [30, 28]
        title {
            text: "Minas de oro y cobre",
        }
        content {
            text: "El oro y el cobre son metales valiosos. Una ciudad con mineral metálico en su territorio tiene una gran suerte. Si ve rocas con vetas metálicas brillantes, haga clic en el botón de Estructuras industriales del Panel de control y luego elija Materias primas para saber si sus topógrafos han encontrado mineral de oro, de cobre o de ambos. @PEl oro es un bien raro y precioso que debe extraerse siempre que tenga la oportunidad. El oro es @48dinero, y las Minas de oro permiten a la ciudad generar el suyo propio. A diferencia de otros bienes, el oro nunca se entrega a los @4Patios&de&almacenamiento. El oro solo puede llevarse directamente al @77Palacio, que lo convierte en debenes y los añade al tesoro de su ciudad. @G54 @L@LCobre @LEl cobre es casi tan valioso como el oro, aunque se usa de forma más convencional. Es una de las pocas materias primas que puede exportar para obtener un beneficio considerable. @PEn tiempos turbulentos, el cobre es un recurso extremadamente valioso para fabricar @98armas, que pueden alcanzar un precio muy elevado. A menudo, su propia ciudad necesitará armas para equipar a su infantería. Haga clic @52aquí para leer sobre la guerra. @L@LLas minas de metal deben construirse junto a afloramientos rocosos que contengan pepitas metálicas. Ambas minas necesitan acceso por carretera y mano de obra, y están entre los vecinos más indeseables que puede tener una ciudad. @L@LLos antiguos egipcios valoraban el oro y realizaban arduos procesos para extraer el metal de la tierra. Haga clic @191aquí para saber más sobre el oro y sus usos en el antiguo Egipto."
        }
    }
    
    message_building_woodcutter_and_reed_gatherer {
        id: 94,
        
        size [30, 28]
        title { text: "Leñador y recolector de juncos" }
        content {
            text: "Los Leñadores y los Recolectores de juncos obtienen las materias primas disponibles para utilizarlas en otras industrias. La madera tiene múltiples usos. Los carpinteros la necesitan para construir rampas o andamios para los monumentos, los fabricantes de carros la emplean para construir sus mortíferos vehículos y los constructores de barcos la convierten en barcos de guerra y de transporte. Los juncos se utilizan para fabricar @97papiro. @PLos Leñadores pueden situarse en cualquier lugar, pero lo ideal es que estén cerca de los bosques para reducir el tiempo que pasan desplazándose. Los Leñadores necesitan acceso tanto a la carretera como a mano de obra local. Una vez que el edificio está plenamente operativo, los leñadores se dirigen al bosque y empiezan a talar árboles. @G58 @PLos Recolectores de juncos funcionan de forma muy parecida a los Leñadores. Conviene situarlos cerca de un campo de juncos, aunque pueden construirse en cualquier parte. Los campos de juncos son de un verde muy oscuro con matas de verde más claro y amarillas. Al igual que los Leñadores, los Recolectores de juncos necesitan acceso por carretera y mano de obra para funcionar. Una vez que tienen todo lo necesario, se adentran en los pantanos. @PTenga cuidado al planificar sus Leñadores y Recolectores de juncos. La madera y los juncos se regeneran poco a poco, pero ambos pueden sobreexplotarse. Si construye demasiados Leñadores o Recolectores de juncos, corre el riesgo de agotar el recurso. Sus industrias extractivas se detendrán hasta que los árboles y los juncos tengan oportunidad de volver a crecer. @PLa madera es uno de los bienes más valiosos de Egipto. Procure no destruir los bosques despejando terrenos: la ciudad perderá una fuente de ingresos considerable si lo hace. Los pantanos no pueden despejarse y algunos curanderos los relacionan con la malaria.   @L@LHaga clic @192aquí para saber más sobre la importancia de la madera en el antiguo Egipto. Haga clic @188aquí para descubrir los muchos usos de los juncos."
        }
    }

    message_building_stone_quarries {
        id: 95,
        
        size [30, 28]
        title {
            text: "Canteras de piedra",
        }
        content {
            text: "Los canteros tallan grandes bloques de roca en cuatro tipos distintos de cantera: @L@PCantera de piedra corriente @PCantera de caliza @PCantera de granito @PCantera de arenisca @L@LSi hay extensos afloramientos rocosos en el territorio de la ciudad, probablemente podrá construir canteras para extraer la roca. Sin embargo, algunas zonas tienen roca que no sirve para la construcción, o tienen muy poca roca para sostener una industria. En esas zonas, la roca es solo un estorbo, porque no puede despejarse, atravesarse ni edificarse sobre ella. Haga clic en el botón de Estructuras industriales y consulte la lista de materias primas disponibles. Esta lista le indica qué tipos de piedra, si los hay, pueden extraerse en la zona. @PDebe construir las canteras junto a afloramientos rocosos. Cuando elija un lugar adecuado, verá un «fantasma» verde de la cantera que intenta colocar. En caso contrario, verá un bloque rojo. @PLa piedra no puede transformarse en otros productos. Sin embargo, es la materia de los monumentos, y se necesitan cantidades importantes para completar incluso algunos de los monumentos más pequeños. @PLas canteras, excavadas en la ladera de los afloramientos rocosos, son propensas a derrumbarse. Asegúrese de construir un @81Puesto&de&arquitecto cerca de las canteras para evitar desastres. @PLas canteras necesitan una plantilla de trabajadores y acceso por carretera para funcionar. Debido al ruido constante de los golpes sobre la roca, las canteras son vecinos indeseables. @L@LLa extracción de piedra en el antiguo Egipto era una tarea muy laboriosa. Para saber más, haga clic @193aquí."
        }
    }

    message_building_brewery {
        id: 96,
        
        size [30, 28]
        title {
            text: "Cervecería",
        }
        content {
            text: "Para iniciar el proceso de elaboración, las Cervecerías necesitan acceso por carretera, mano de obra y un suministro de cebada. Las @91Granjas&de&cebada producen la cebada necesaria, o puede importarse de un @47socio&comercial. Una Granja de cebada puede abastecer normalmente a dos Cervecerías. Las Cervecerías pueden almacenar algo de cebada en sus instalaciones para seguir trabajando entre cosechas. @PUna vez que los cerveceros tienen todos los suministros necesarios, elaboran la cerveza. Puede saber si un cervecero trabaja duro si ve al cervecero y a su personal en la Cervecería. Terminado el proceso de elaboración, los repartidores intentan llevar primero la cerveza a una @74Casa&de&Senet. Si ninguna Casa de Senet necesita la cerveza, los repartidores la llevan a un @4Patio&de&almacenamiento, donde puede ser recogida por los @2compradores del Mercado para distribuirla entre sus ciudadanos, o @47comerciada para obtener un buen beneficio. La cerveza es uno de los productos que sus ciudadanos necesitan antes de mejorar sus casas hasta convertirlas en @56viviendas&más&atractivas. @PLa cerveza también se sirve en los @51grandes&festivales. @L@LPara leer más sobre la cerveza en el antiguo Egipto, haga clic @194aquí."
        }
    }

    message_building_papyrus_maker {
        id: 97,
        
        size [30, 28]
        title {
            text: "Fabricante de papiro",
        }
        content {
            text: "Los Fabricantes de papiro necesitan mano de obra, acceso a una carretera y un suministro de @94juncos procedentes de un Recolector de juncos o de un @47socio&comercial. Pueden almacenar juncos en sus instalaciones para seguir trabajando entre entregas. @PCuando un carro de papiro está listo, un repartidor lo lleva a una @68Escuela&de&escribas o a una @70Biblioteca que lo necesite. Si ningún edificio educativo necesita papiro, el repartidor lleva los suministros al @4Patio&de&almacenamiento, donde puede @47comerciarse para obtener beneficios. @G69 @PA los ciudadanos no les gusta vivir cerca de un Fabricante de papiro. El constante golpeteo les produce dolor de cabeza. @L@LPara saber más sobre la fabricación de papiro en el antiguo Egipto, haga clic @195aquí."
        }
    }

    message_building_weapongsmith_and_chariot_maker {
        id: 98,
        
        size [30, 28]
        title {
            text: "Armero y fabricante de carros",
        }
        content {
            text: "Los Armeros y los Fabricantes de carros producen los instrumentos de guerra que necesitan ciertas compañías militares. @PCon cobre de una @93Mina&de&cobre o importado de un @47socio&comercial, el Armero fabrica las armas. Las armas terminadas se llevan a un @88Reclutador, que las usa para equipar a las @37compañías de infantería, o a un @45Patio&de&almacenamiento si su Reclutador ya tiene suficientes en su poder o si su ciudad no tiene un Reclutador en funcionamiento. @PEl Fabricante de carros usa madera de un @94Leñador o de un @47socio&comercial para construir magníficos carros de guerra. Envía el producto terminado al Reclutador, que equipa con ellos a los @37aurigas. Si el Reclutador ya tiene algunos carros en su inventario, o si su ciudad no tiene un Reclutador en funcionamiento, los carros se llevan a un Patio de almacenamiento. @PTanto los Armeros como los Fabricantes de carros necesitan acceso por carretera y una fuente de mano de obra. Son @56vecinos indeseables. @L@LPara saber más sobre el armamento en el antiguo Egipto, haga clic @196aquí."
        }
    }

    message_building_jeweler_and_luxury_goods {
        id: 99,
        
        size [30, 28]
        title {
            text: "Joyero y artículos de lujo",
        }
        content {
            text: "Con un suministro de @361piedras preciosas, los Joyeros fabrican bellas piezas de joyería, un artículo de lujo. Las piedras preciosas pueden extraerse o importarse de un @47socio&comercial. @PLos Joyeros necesitan acceso por carretera y mano de obra para funcionar. Tienen un efecto negativo sobre el @56atractivo. @PLa joyería no es una exportación muy lucrativa. La mayor parte del coste de los artículos de lujo importados está en su transporte, no en sus materiales. Por eso, aunque importar lujos de otras ciudades pueda costarle bastante a su tesoro, no obtendrá un precio comparable por sus exportaciones de joyería. @PLa joyería es solo uno de los artículos de lujo que anhelan los ciudadanos. Los más ricos exigirán un segundo artículo de lujo importado. @L@LEl antiguo Egipto es célebre por su espléndida @382joyería. Para leer más sobre otros artículos de lujo del antiguo Egipto, haga clic @197aquí."
        }
    }

    message_population_milestone_100 {
        id: 100,
        
        size [30, 20]
        title { text: "Hito de población" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "100 personas se han instalado en su aldea." }
    }

    message_population_milestone_500 {
        id: 101,
        
        size [30, 20]
        title { text: "Hito de población" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        content { text: "Su naciente pueblo alberga ya a quinientos residentes." }
    }

    message_population_milestone_1000 {
        id: 102,
        type: 2,
        
        size [30, 20]
        title { text: "Hito de población" }
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        video { text: "@17" }
        content { text: "Mil personas ya llaman hogar a su ciudad." }
    }
    message_population_milestone_2000 {
        id: 103,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@17" }
        content { text: "Con dos mil residentes, su ciudad gana importancia." }
    }
    message_population_milestone_3000 {
        id: 104,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@17" }
        content { text: "La población de su ciudad ha alcanzado por primera vez en la historia los tres mil habitantes." }
    }
    message_population_milestone_5000 {
        id: 105,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@18" }
        content { text: "Su ciudad es ya bastante grande.  Ahora viven aquí cinco mil personas." }
    }
    message_population_milestone_10000 {
        id: 106,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@18" }
        content { text: "Su población de diez mil habitantes sitúa a su ciudad en la primera categoría de Egipto." }
    }
    message_population_milestone_15000 {
        id: 107
        type: 2
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@18" }
        content { text: "Pocas ciudades pueden rivalizar con la suya, que ya alberga a quince mil ciudadanos." }
    }
    message_population_milestone_20000 {
        id: 108,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@19" }
        content { text: "¡Otros gobernadores y nomarcas se asombran de que su ciudad albergue a veinte mil personas!" }
    }
    message_population_milestone_25000 {
        id: 109,
        type: 2,
        
        size [30, 20]
        image { pack:PACK_UNLOADED, id: 16, offset: 16, pos [15, 15] }
        title { text: "Hito de población" }
        video { text: "@19" }
        content { text: "Los pocos inmigrantes que fundaron su ciudad hace tantos años nunca imaginaron que llegaría a crecer hasta veinticinco mil personas." }
    }

    message_the_control_panel {
        id: 110,
        
        size [30, 20]
        title { text: "El panel de control"  }
        content {
            text: "Este panel contiene todos los controles que necesita para construir y mantener su ciudad. La mejor forma de entender sus funciones es hacer clic en sus distintos botones; adelante, ¡no puede romper nada! Si la Ayuda del ratón está activada (en 'Ayuda' de la barra de menús), sitúe el cursor sobre cualquier elemento para ver una breve descripción. Para explicaciones detalladas de todos los temas de Faraón, use el elemento 'Ayuda' de la barra de menús."
        }
    }

    message_fire_in_the_city {
        id: 111,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        urgent: 1,
        title { text: "Incendio en la ciudad" }
        content {
            text: "Las llamas se extienden por algunas zonas de la ciudad. Haga clic en 'Superposiciones: Riesgos' para ver dónde podría declararse el próximo incendio y construya Cuarteles de bomberos cerca de los edificios en peligro."
        }
    }

    message_collapsed_building {
        id: 112
        type: 2
        message_type: 1
        
        size [30, 20]
        urgent: 1
        title { text: "Edificio derrumbado" }
        content {
            text: "Sin el mantenimiento adecuado que proporcionan los arquitectos, ciertas grandes estructuras de su ciudad se derrumbarán. Haga clic en 'Superposiciones: Riesgos' para ver qué edificios corren peligro de derrumbarse y construya Puestos de arquitecto cerca de ellos."
        }
    }

    message_ship_aground {
        id: 114,
        type: 2,
        
        size [30, 20]
        title { text: "Barco varado" }
        content { text: "Algunos capitanes inexpertos aprenden a las malas lo peligrosas que son las llanuras aluviales, cuando sus barcos encallan." }
    }

    message_out_of_money {
        id: 115,
        
        size [30, 20]
        title { text: "¡Sin dinero!" }
        content { text: "Su tesoro se ha quedado sin debenes. Se le concede un fondo adicional, pero ningún benefactor volverá a rescatarle. Use este regalo para crear empresas que generen dinero." }
    }

    message_debt_again {
        id: 116,
        
        size [30, 20]
        title { text: "¡Deudas!" }
        content { text: "Su tesoro se desangra. Puede gastar hasta 5.000 debenes de crédito, pero la @48deuda puede llevar a la ruina a su familia si no la salda pronto." }
    }

    message_out_of_money_again {
        id: 117,
        
        size [30, 20]
        title { text: "¡Sin dinero!" }
        content { text: "Las arcas de la ciudad se han quedado vacías, oh Faraón. Sus leales nomarcas donaron todos los debenes que pudieron prescindir, pero no pueden permitirse hacerlo de nuevo." }
    }

    message_wrath_of_the_emperor {
        id: 118,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "La ira del Emperador" }
        video { text: "@12" }
    }

    message_attack_called_off {
        id: 120,
        type: 2,
        
        size [30, 20]
        title { text: "Ataque cancelado" }
        content {
            text: "Acaban de llegar nuevas órdenes. Dicen que ha recuperado parte del respeto en todo Egipto y que ya no es necesaria su destrucción. Me despido de usted... por ahora. "
        }
    }
    message_debt_anniversary {
        id: 121,
        
        size [30, 20]
        urgent: 1,
        title { text: "Aniversario de deudas" }
        content {
            text: "Su tesoro sigue sin tener ni un solo debén. Cada año consecutivo de deuda daña su reputación y, por tanto, su @35calificación&del&reino. Quizá debería repasar sus conocimientos sobre el @48dinero."
        }
    }

    message_barbarians_attack {
        id: 122
        type: 2
        message_type: 7
        
        size [30, 20]
        urgent: 1,
        title { text: "¡Los bárbaros atacan!" }
        video { text: "smk\\Spy_Barbarian.smk" }
    }

    message_legion_attacks {
        id: 123
        type: 2
        message_type: 7
        
        size [30, 20]
        urgent: 1,
        title { text: "Ataque de la legión" }
    }

    message_distant_battle {
        id: 124
        type: MESSAGE_ARCH_MESSAGE
        message_type: MESSAGE_TYPE_DISTANT_BATTLE
        
        title { text: "Batalla lejana" }
        video { text: "@10" }
        content { text: "xxxx ver eventmsg.txt" }
    }

    message_enemies_closing {
        id: 125
        type: 2
        
        size [30, 20]
        title { text: "Enemigos cerca" }
        video { text: "@10" }
        content { text: "xxxx ver eventmsg.txt" }
    }

    message_enemies_at_the_door {
        id: 126
        type: 2
        
        size [30, 20]
        urgent: 1
        title { text: "Enemigos a las puertas" }
        video { text: "@10" }
        content { text: "xxxx see eventmsg.txt" }
    }

    message_template_request {
        id: 130,
        type: 2
        message_type: 2
        size [30, 20]
        title { text: "Petición de bienes del Faraón" }
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
        title { text: "Ira de Bastet" }
        video { text: "@20" }
        content { text: "¡Ay de ti! Bastet está horrorizada por tu indiferencia. Para demostrar que no puedes preservar la salud de tu ciudad sin adorarla, ha llenado el río de sangre, envenenando el suministro de agua. Espera que tus ciudadanos aguanten hasta que el agua vuelva a ser pura." }
    }

    message_city_unemployment {
        id: 135,
        type: 2,
        
        size [30, 20]
        title { text: "Desempleo en la ciudad" }
        content { text: "Hay muy pocos empleos para dar trabajo a todos. A menos que se creen nuevos puestos de trabajo, los desempleados podrían recurrir desesperados al crimen o buscar fortuna en otra parte del Reino." }
    }

    message_employees_needed {
        id: 136,
        
        size [30, 20]
        title { text: "Se necesitan trabajadores" }
        content { text: "Hay muy pocas personas en edad laboral para cubrir los empleos de la ciudad. Si no encuentras nuevos trabajadores pronto, los servicios de la ciudad empeorarán y la producción industrial se resentirá." }
    }

    message_common_festival {
        id: 137,
        
        size [30, 20]
        title { text: "Festival popular" }
        content { text: "Todos agradecen salir del trabajo temprano para relajarse un rato en la Plaza del Festival, y tu dios elegido advierte tu generoso gesto." }
    }

    message_lavish_festival {
        id: 138,
        
        size [30, 20]
        title { text: "Festival suntuoso" }
        content { text: "Comienza el festival de todo el día. La gente de toda la ciudad se dirige ahora a la Plaza del Festival y parece estar de buen humor. Tu dios elegido aprecia tu dedicación." }
    }

    message_grand_festival {
        id: 139,
        
        size [30, 20]
        title { text: "Gran festival" }
        content { text: "¡Por fin comienza el tan esperado festival de dos días! Todos acuden a la Plaza del Festival en busca de cerveza gratis y entretenimiento desenfrenado. El dios honrado en este evento sin duda te sonríe." }
    }

    message_wrath_of_osiris {
        id: 140
        type: 2
        
        size [30, 20]
        title { text: "Ira de Osiris" }
        video { text: "@24" }
        content { text: "Osiris se resiente de la pasmosa falta de dedicación de esta ciudad. A menos que lo aplaques pronto, la próxima crecida será mucho peor de lo esperado... ¡o quizás ni siquiera llegue!" }
    }

    message_wrath_of_ptah {
        id: 141
        type: 2
        
        size [30, 20]
        title { text: "Ira de Ptah" }
        video { text: "@22" }
        content { text: "¡Has provocado la ira de Ptah! Tu ciudad no tiene actualmente industrias que castigar, pero ten mucho cuidado con este dios cuando empieces a extraer, fabricar o cortar piedra." }
    }
    
    message_wrath_of_ptah_2 {
        id: 142
        type: 2
        
        size [30, 20]
        title { text: "Ira de Ptah" }
        video { text: "@22" }
        content { text: "Ptah se ofende por tu orgullo al creer que tu ciudad puede ser industriosa sin rendirle respeto. Destruyó algunos edificios industriales como recordatorio para ti." }
    }

    message_wrath_of_seth_noeffect {
        id: 143
        type: 2
        
        size [30, 20]
        title { text: "Ira de Seth" }
        video { text: "@21" }
        content { text: "Tu ciudad escapó a la ira de Seth por no tener instalaciones militares que el dios pudiera destruir. Aun así, ten cuidado al provocar al Dios de la Destrucción, pues su ira toma muchas formas y su memoria es larga." }
    }

    message_wrath_of_bast {
        id: 144,
        type: 2,
        
        size [30, 20]
        title { text: "Ira de Bastet" }
        video { text: "@20" }
        content { text: "¡Malas noticias! Como tu ciudad descuida rendirle el honor que le es debido, Bastet, Diosa del Hogar, ¡ha derribado algunas de sus mejores casas!" }
    }
    message_blessing_from_ptah {
    id: 145,
        type: 2,
        
        size [30, 20]
        title { text: "Una bendición de Ptah" }
        video { text: "@22" }
        content { text: "Ptah buscaba un Patio de almacenamiento con espacio para más gemas, arcilla, cerámica, lino, tela o joyas. Si lo hubiera encontrado, habría aumentado las reservas de tu ciudad." }
    }
    message_wrath_of_osiris_2 {
        id: 147
        type: 2
        
        size [30, 20]
        title { text: "Ira de Osiris" }
        video { text: "@24" }
        content { text: "¡Día infeliz! Enfadado por tu negativa a rendirle el debido respeto, Osiris envía una plaga de langostas para devorar tus cosechas." }
    }
    message_wrath_of_ptah_4 {
        id: 148,
        type: 2,
        
        size [30, 20]
        title { text: "Ira de Ptah" }
        video { text: "@22" }
        content {
            text: "Ptah está indignado porque te niegas a adorarlo. Llama a una plaga de ranas que descenderá sobre la ciudad. Estas ranas, con su piel viscosa y su hedor pútrido, obligarán a muchos a abandonar sus hogares."
        }
    }

    message_hailstorm_wrath_of_seth {
        id: 149
        type: 2
        
        size [30, 20]
        title { text: "Ira de Seth" }
        video { text: "@21" }
        content { text: "Furioso porque te niegas a rendirle homenaje, Seth invoca una granizada que cae sobre la ciudad, golpeando y matando a cualquiera que se cruce en su camino." }
    }

    message_farming {
    id: 150,
        
        size [30, 20]
        image { id: 81, pos [15, 15] }
        title { text: "Agricultura" }
        subtitle { text: "Historia" }
        content {
            text: "La agricultura era la base de la economía egipcia. Las cosechas abundantes permitían a Egipto @177comerciar con sus vecinos, trayendo nuevos bienes a Egipto. @L@LLa clave de una agricultura exitosa era la Inundación, llamada akhet. Cada año, el Nilo desbordaba sus orillas y fertilizaba de nuevo el suelo. Mientras la Inundación llegara, los egipcios podían contar con comida de sobra. En los años de Inundación escasa o nula, el hambre azotaba Egipto, lo que a veces bastaba para derribar gobiernos. @L@LPara aprovechar la Inundación reparadora, se construían diques alrededor de los campos para retener el agua mientras subía. Cuando el Nilo se retiraba (llamado peret), el agua, junto con sus nutrientes, empapaba lentamente el suelo. Tras unas seis semanas, el campesino abría los diques y dejaba salir el resto del agua. Por supuesto, estar sumergido en agua dejaba el terreno bastante blando. Antes de sembrar, el campesino tenía que esperar a que la tierra se secara un poco y se endureciera. @L@LFinalmente, durante shemu, se cosechaban los cultivos. Los destinados al consumo egipcio se guardaban en @5graneros. La comida destinada a la exportación se almacenaba en @6Patio&de&almacenamiento hasta que pudiera cargarse en barcazas. @L@LLos propietarios de las fincas o el gobierno poseían los campos y empleaban a jornaleros para hacer muchas de las tareas más arduas de la tierra. Labrar la tierra no era trabajo fácil, y gran parte de él se hacía a mano. Las herramientas de que disponían los campesinos incluían la azada, el arado de mano y la hoz. Los bueyes domesticados aliviaban parte del arado. @L@LLa agricultura producía tanto materias primas como alimentos. @185Grano&y&cebada eran los cultivos alimentarios clave, y @189lino, que se transformaba en @398lino de tela, era el cultivo de materia prima más importante. @L@LLa agricultura también era parte integral del más allá egipcio. Una vez concedida al difunto la entrada en el más allá, se encuentra trabajando la tierra en el Campo de Juncos."
        }
    }

    message_industry {
        id: 151,
        
        size [30, 20]
        image { id: 82, pos [15, 15] }
        title { text: "Industria" }
        subtitle { text: "Historia" }
        content {
            text: "Hacia el Reino Antiguo, la fabricación de productos había salido del ámbito doméstico y pasado a talleres centralizados que producían casi todos los suministros necesarios para la vida diaria. Cada taller se especializaba en un producto concreto y funcionaba de forma muy parecida a una cadena de montaje moderna. Cada trabajador era responsable de un aspecto concreto del producto final, en lugar de trabajar un artículo de principio a fin. Las herramientas que usaban los artesanos en estos talleres eran propiedad del Estado, al igual que los materiales que producían. Los artesanos cobraban salarios, por lo general en comida y bienes necesarios. @L@LLa industria egipcia prosperó y produjo muchos bienes. Los egipcios podían encontrar empleo como @198alfareros, @398tejedores, joyeros, curtidores, @389carpinteros y fundidores, además de panaderos y @194cerveceros."
        }
    }
    message_housing {
        id: 152,
        
        size [30, 20]
        image { id: 83, pos [15, 15] }
        title { text: "Viviendas" }
        subtitle { text: "Historia" }
        content {
            text: "Los egipcios construían sus casas con ladrillo, madera, barro o, en ocasiones, piedra. El estilo y el tamaño de la vivienda dependían de la riqueza del ciudadano y del lugar donde viviera. Así, los campesinos que vivían de la agricultura residían en sencillas construcciones de ladrillo o barro prensado de dos a cuatro habitaciones. Las casas urbanas de la clase trabajadora también eran pequeñas, y se construían algunas viviendas de dos plantas para dos familias con el fin de ahorrar espacio en las ciudades más abarrotadas. Los trabajadores urbanos vivían en casas de ladrillo de 3 a 7 habitaciones. @L@LLos ciudadanos más ricos tenían casas más grandes, y algunas eran bastante espaciosas. Los altos funcionarios del gobierno tenían a veces casas de 60 a 70 habitaciones, con techos altos sostenidos por columnas de madera, salones de recepción para agasajar a los invitados, amplio espacio de almacenamiento y dependencias para los sirvientes. Las casas más lujosas de todas eran los @175Palacios&del&Faraón.  @L@LEn su mayor parte, las ciudades egipcias crecían de forma orgánica en la dirección que podían. Sin embargo, algunas ciudades fueron planificadas, sobre todo el asentamiento construido para los trabajadores de Deir el-Medina. @L@LLa mayoría de las ciudades egipcias estaban rodeadas de murallas. Para saber más sobre las estructuras defensivas, haz clic @182aquí."
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
            text: "Carreteras",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El @157Nilo era la autopista principal de Egipto. Barcos de todas las formas y tamaños transportaban personas, bienes y materiales de un punto a otro. Los antiguos egipcios, por supuesto, también tenían caminos terrestres. Estos caminos generalmente no estaban pavimentados de ninguna forma, sino que eran simplemente senderos muy transitados. En la mayoría de las ciudades, los caminos serpenteaban como era necesario. En las ciudades planificadas, como el asentamiento de los trabajadores de Deir el-Medina, las calles se trazaban en una cuadrícula ordenada. @L@LAlgunas rutas comerciales también estaban bien establecidas, pero tampoco estaban pavimentadas, y podían ser muy peligrosas de recorrer. Para saber más sobre los peligros del comercio exitoso, haz clic @177aquí."
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
            text: "Riego",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los egipcios aumentaron la superficie de tierra cultivable mediante el riego. Ya en la novena dinastía, hacia el 2000 a. C., los egipcios empezaron a construir una red de canales y acequias de riego. Algunos canales parecen haber existido antes, pero se usaban para el transporte. Los canales de riego extendían los beneficios del río, llevando limo fértil a zonas alejadas de sus orillas. @L@LA principios de la historia egipcia, los campesinos que querían regar sus tierras lo tenían muy difícil. Regaban a mano, cargando un yugo con dos cubos de arcilla o cuero hasta el Nilo u otra fuente de agua. El campesino volvía con sus cubos llenos a su campo, que estaba dividido por pequeños diques. Los diques retenían el agua, aprovechando al máximo este lento y penoso método de riego.  @L@LA finales de la dinastía 18 (hacia 1300 a. C.), se introdujo el elevador de agua, o shaduf. Es probable que el shaduf llegara a Egipto desde Mesopotamia, donde ya se usaba hacia el 2370 a. C. Colocado en la orilla del Nilo u otra fuente de agua, el shaduf consistía en una larga viga de madera que se mecía sobre un pivote. Un cubo en un extremo de la viga se equilibraba con un ladrillo u otro peso. Una persona empujaba el extremo del cubo hacia abajo para sumergirlo en el agua, y el ladrillo ayudaba al trabajador a elevar el agua hasta la acequia unida al shaduf. @L@LLa introducción del shaduf aumentó la tierra cultivable de Egipto en alrededor de un 15 por ciento. Además, como nunca quedaba sumergida bajo el agua, la tierra regada con shaduf podía producir dos cosechas al año en lugar de una."
        }
    }
    message_tutorial_labor {
        id: 155
        type: 2
        
        size [30, 20]
        image { id: 85, pos [15, 15] }
        title { text: "Mano de obra" }
        subtitle { text: "Historia" }
        content { text: "Los campesinos realizaban la mayor parte del trabajo más duro en el antiguo Egipto. Labraban la tierra y recogían las cosechas durante la temporada de cultivo. Durante la Inundación, esos mismos trabajadores eran reclutados para trabajar para el Estado. Principalmente construían pirámides y otras estructuras, pero también podían encargarse del mantenimiento de la infraestructura egipcia, como los @153caminos y los @154Canales&de&riego. @L@LAunque el trabajo de los campesinos no era fácil, tampoco se les maltrataba del todo. La jornada laboral típica duraba ocho horas con una pausa para comer. La semana laboral duraba ocho días, con dos días libres al final. Además de estos «fines de semana», el trabajo se detenía durante las fiestas. Los trabajadores también podían tomarse tiempo libre si había enfermedad o muerte en la familia. @L@LLa asistencia estaba muy bien documentada, al igual que los motivos de las ausencias. Algunas razones para faltar al trabajo probablemente no serían aceptables como excusas hoy en día. Un empleado faltó al trabajo para ir a beber con un amigo. @L@LA pesar de lo que mucha gente cree, la mano de obra esclava rara vez se usaba en las obras públicas del Estado. A veces se empleaba a esclavos en las canteras, pero en su mayoría servían en las casas. @L@LSi los trabajadores no eran bien tratados, podían ir a la huelga. Durante el reinado de Ramsés III, hacia el 1152 a. C., los trabajadores de Deir el-Medina dejaron formalmente de trabajar para protestar por el retraso en su pago. Su huelga tuvo éxito, y el problema de los pagos atrasados se solucionó." }
    }
    message_clean_water {
        id: 156
        
        size [30, 20]
        image { id: 86, pos [15, 15] }
        title { text: "Pozos y suministro de agua", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "Llevar agua potable a la población era todo un reto en el antiguo Egipto. La principal fuente de agua era el Nilo y el nivel freático del Nilo. Lejos del Nilo había algunos oasis, pero la mayor parte de la tierra era árida. @L@LPara llevar agua a los barrios, se construían cisternas en las casas acomodadas. Los aguadores traían cubos llenos de agua a estas casas y los vaciaban en las cisternas. @L@LLos egipcios eran hábiles excavando pozos. Los trabajadores tuvieron que atravesar 300 pies de roca para un pozo cerca del asentamiento de los trabajadores de Giza. La mayoría de los pozos tenían una caseta encima. Desde la caseta, unas escaleras descendían hasta el nivel del agua. Desde allí, la gente podía llenar sus jarras de agua."
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
            text: "Nilo",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La civilización egipcia sencillamente no habría existido sin el Nilo. En una región donde la lluvia escasea, el Nilo proporciona una fuente fiable de agua tanto para las personas como para la tierra. Al desbordar sus orillas de forma relativamente previsible, el Nilo también fertiliza las tierras de cultivo. @L@LLos antiguos egipcios no pasaban por alto la importancia del Nilo. Ver cómo el Nilo devolvía la vida a la tierra una y otra vez contribuyó enormemente a las costumbres religiosas egipcias, en especial a su creencia en el más allá.  @L@LEl calendario egipcio se dividía en estaciones que recibían el nombre de las distintas fases del Nilo. La Inundación, cuando el Nilo desbordaba sus orillas, se llamaba akhet. La Inundación se producía por los monzones anuales en el nacimiento del Nilo Azul, en las mesetas de Etiopía. La Emersión, o proyet, marcaba el momento en que el Nilo se retiraba y la tierra empezaba a aflorar. La época de la cosecha se llamaba shomu, a veces traducido como sequía."
        }
    }
    message_dentistry {
        id: 158,
        
        size [30, 20]
        image { id: 88, pos [15, 15] }
        title { text: "Odontología" }
        subtitle { text: "Historia" }
        content {
            text: "La odontología era una de las muchas especialidades que podía ejercer un médico egipcio antiguo. Los restos de egipcios antiguos indican que los dentistas libraban una batalla cuesta arriba. La caries era favorecida por la arena omnipresente. La arena se colaba en todo, incluida la comida, y masticar arena constantemente desgastaba rápidamente los dientes de los egipcios. El desgaste dental solía provocar abscesos, que podían hacer que el diente se cayera e incluso causar la muerte. @L@LLos papiros médicos detallan las acciones que tomaban los dentistas para tratar problemas concretos. Por ejemplo, si se caía un diente, el dentista lo sujetaba a un diente vecino con alambre de oro o plata. Incluso hay una receta para empastes, que mezclaba resina y malaquita, pero los arqueólogos no han encontrado restos de dientes con los empastes intactos. @L@LLos arqueólogos han descubierto herramientas que creen que se usaban como cepillos de dientes. Hasta ahora, no se ha informado de ningún hallazgo de hilo dental egipcio antiguo."
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
            text: "Botica",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Las prácticas medicinales y farmacéuticas del antiguo Egipto están bien documentadas. La religión era fundamental para curar enfermedades, y la mayoría de los remedios recetados iban acompañados de oraciones o conjuros. Los papiros médicos describían curas concretas, algunas de las cuales nos parecen un tanto inusuales. Para curar la indigestión, por ejemplo, se machacaba un diente de cerdo y se colocaba dentro de cuatro pasteles de azúcar. El paciente debía comer uno de estos pasteles al día, tras lo cual la indigestión debía curarse. Para la calvicie se recomendaba una mezcla de una vértebra de cuervo, una pezuña quemada de burro y la manteca de una serpiente negra."
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
            text: "Historia",
        }
        content {
            text: "Como otras partes de la sociedad egipcia, la profesión médica estaba muy segmentada y burocratizada. La profesión se organizaba en líneas jerárquicas, con médicos que ostentaban títulos como médico sénior, inspector, supervisor y maestro de médicos. El médico de mayor rango era el «Jefe de los Médicos del Sur y del Norte». @L@LLos médicos adquirían sus conocimientos estudiando los órganos internos de los animales y los textos, no observando el proceso de embalsamamiento. La medicina estaba claramente separada de los ritos funerarios. @L@LLa buena salud se basaba en el concepto de metu. El corazón era el centro del cuerpo, y todas sus partes estaban unidas al corazón por el metu, o canales. Más que una descripción del sistema circulatorio, todos los sistemas del cuerpo se consideraban metu. La enfermedad aparecía cuando alguna parte del metu quedaba bloqueada. @L@LPara curar las enfermedades, los médicos recetaban medicinas combinadas con oración. Para saber más sobre la farmacia egipcia, consulta las @159boticas. @L@LLos egipcios sufrían polio, viruela, tuberculosis de columna y malaria, entre otras dolencias. Los egipcios también eran propensos a enfermedades causadas por gusanos parásitos."
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
            text: "Embalsamadores",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El embalsamamiento es la piedra angular de las costumbres funerarias del antiguo Egipto. El ka, o espíritu, del difunto necesitaba un lugar donde vivir en el más allá y, por tanto, necesitaba su cuerpo. Durante el proceso de embalsamamiento, el cuerpo se lavaba primero con las aguas del Nilo, como símbolo de renacimiento. Después se extraían los órganos internos del cadáver y se guardaban en recipientes llamados vasos canopes. El único órgano que se desechaba era el cerebro (que se extraía por la nariz), porque los antiguos egipcios creían que no tenía ninguna función. Los vasos canopes se enterraban junto al cuerpo. @L@LTras extraer los órganos internos, el embalsamador llenaba la cavidad del cuerpo con perfumes, aceites y lino, y la cerraba. Luego, el cuerpo se cubría de natrón, una clase de sal. Después de 70 días, el cuerpo se lavaba, se envolvía en lino y se untaba con brea. La brea ayudaba a matar bacterias y hongos que de otro modo descompondrían el cuerpo. @L@LDebido al elevado coste del embalsamamiento, solo los ciudadanos más ricos podían permitírselo."
        }
    }
    message_shrine_and_temple {
        id: 162,
        
        size [30, 20]
        image { id: 12, pos [15, 15] }
        title { text: "Santuario y templo", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "Los templos se consideraban las residencias de los dioses, y cada templo contaba con decenas de @384sacerdotes que atendían al dios. Los ciudadanos participaban en el cuidado de los dioses mediante ofrendas, pero rara vez veían la estatua del dios, escondida en lo más profundo del templo. Solo en los días de fiesta, cuando el dios era llevado por la ciudad en una barca ceremonial, los ciudadanos podían vislumbrar la deidad. @L@LLos egipcios acudían a los dioses en busca de consejo. Todos eran bienvenidos en el patio exterior del templo, donde la gente podía consultar a los dioses sobre temas que le preocupaban o pedir perdón por viejas faltas. Los sacerdotes, ocultos a la vista, respondían a los suplicantes. Los ciudadanos también podían hacer preguntas al dios en los días de fiesta, cuando salía a pasear. @L@LAdemás de rendir homenaje en los templos, la mayoría de los egipcios tenían santuarios en sus casas. Con frecuencia, el santuario era de Bes, el dios protector del hogar. Los individuos parecen haber tenido también sus propios dioses patronos. En un registro de asistencia descubierto en Deir el-Medina, a veces los trabajadores faltaban para celebrar el «festival de su dios». @L@LEl concepto de dios patrón se extendía a ciudades, pueblos y regiones. Esa idea provocó cambios en los dioses adorados en distintos períodos de la historia egipcia. Para saber más sobre la evolución de la religión, haz clic @399aquí."
        }
    }
    message_school_and_eduction {
        id: 163,
        
        size [30, 20]
        image { id: 34, pos [15, 15] }
        title { text: "Escuela y educación", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "La educación en el antiguo Egipto era sumamente práctica. Cada persona se educaba pensando en una carrera concreta. Para muchos, la educación significaba el aprendizaje de un oficio, y los hijos solían aprender el oficio de sus padres. Algunas niñas también aprendían un oficio para dedicarse a ser bailarinas, cantantes o tejedoras, pero en su mayoría aprendían el arte de dirigir un hogar. @L@LLos escribas recibían la educación más formal. Las escuelas de escribas, llamadas Per-Ankh o «casa de la vida», estaban vinculadas principalmente a los templos. Allí, los futuros escribas aprendían las lenguas escritas, principalmente la hierática y, más tarde, la demótica, que se usaban para los asuntos cotidianos. Los escribas aprendían su oficio copiando manuscritos en óstracas, es decir, fragmentos viejos de piedra. Solo cuando dominaban el oficio se les confiaba el papiro. La disciplina era exigida y el castigo físico era frecuente. La educación de escriba se impartía generalmente entre los 10 y los 20 años."
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
            text: "Biblioteca y literatura",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Gracias a una lengua escrita, los egipcios registraron muchas de sus historias, poemas e himnos. Estos textos se guardaban en bibliotecas asociadas a la Per-Ankh (casa de la vida), o @163Escuela&de&escribas, que estaba junto al templo.  @L@LLa literatura egipcia nació de una tradición oral, y en su mayor parte se escribía como recordatorio para el narrador. La mayoría de los egipcios eran analfabetos, y muchos @387escribas eran narradores que usaban el registro escrito para ayudarse a recordar las historias, himnos y poemas. Quienes sabían leer, en especial los vinculados a la corte del faraón, podían acceder a las bibliotecas y leer los papiros por sí mismos.  Algunos ciudadanos ricos tenían sus propias bibliotecas. @L@LLa literatura del antiguo Egipto podía dividirse en varios géneros distintos, como la autobiografía, los relatos de aventuras, los cuentos populares, la mitología, el lamento, la poesía y los himnos, entre otros. De estas formas, la autobiografía era la más antigua y procedía de la tradición de grabar los logros de una persona en su tumba.  La sátira también era popular."
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
            text: "Entretenimiento",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los antiguos egipcios podían elegir entre una gran variedad de actividades de ocio. Los deportes eran comunes, sobre todo los deportes acuáticos como el remo y la natación (los más ricos disfrutaban de este deporte en la intimidad de sus propias piscinas). Los egipcios son también la primera cultura conocida que practicó la pesca como actividad de ocio. @L@PEl boxeo era un espectáculo popular, con combates organizados especialmente para el entretenimiento del faraón. Otros deportes incluían el balonmano, una forma de hockey sobre hierba, la gimnasia, el tiro con arco y la halterofilia. @L@PPara los instruidos, la lectura era un pasatiempo popular, y el primer cuento corto conocido se escribió en el antiguo Egipto. La poesía era popular, pero no hay pruebas de que existieran obras de teatro egipcias. Para saber más sobre la lectura, la escritura y la literatura, consulta las @164bibliotecas. @L@L@393Las&fiestas eran también una parte importante de la vida egipcia."
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
            text: "Niños",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los niños eran muy apreciados en el antiguo Egipto y se consideraban una continuación de la vida. El matrimonio temprano era habitual para facilitar familias numerosas. Los niños de clase baja seguían a sus padres a los campos y ayudaban en la cosecha. Los niños de clase media y alta pasaban sus días en casa con su madre. Cuando tenían edad suficiente, los niños de clase alta eran enviados a la escuela y después aprendían un oficio con sus padres. @L@LLos niños egipcios tenían a su disposición muchos juguetes y juegos, como pelotas, muñecas, peonzas y animales de madera. Jugaban a juegos como la cuerda, y disfrutaban de muchas de las mismas actividades de ocio que sus padres, como nadar y pescar. @L@LLos niños y sus padres también tenían una gran variedad de mascotas. Los perros y los gatos eran mascotas populares, al igual que los monos amaestrados, los pájaros, las gacelas y, para los más ricos y valientes, los leones."
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
            text: "Población",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El antiguo Egipto era en muchos aspectos parecido a la sociedad moderna. Mucha gente vivía en centros urbanos donde la industria ofrecía muchos empleos. Los campesinos solían vivir en aldeas rurales más pequeñas. La mayor parte de la población, naturalmente, vivía cerca del río. @L@LEl tamaño de la población egipcia creció con el tiempo, y su crecimiento está directamente ligado al @154riego. Durante la época predinástica, se cree que la población no superaba unos 350.000 habitantes. Hacia finales del segundo milenio a. C., sin embargo, cuando las prácticas de riego habían ampliado la superficie cultivable, se calcula que la población había alcanzado unos 3 millones."
        }
    }
    message_history_society {
        id: 168,
        
        size [30, 20]
        image { id: 5, pos [15, 15] }
        title { text: "Sociedad", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "La sociedad egipcia estaba muy estratificada, con clases distintas y separadas. En su mayor parte, las personas permanecían en la clase en la que habían nacido, aunque hay algunos ejemplos de individuos que se casaron con alguien de una clase superior. @L@LLos miembros de la clase más baja eran los campesinos. Los campesinos tenían la menor esperanza de vida de todas las clases y soportaban una vida de trabajo duro, ya fuera en los campos o en las obras públicas del Estado. Sus restos muestran que la mayoría de los campesinos sufría problemas de espalda, y sus vértebras a veces estaban fusionadas como consecuencia de su duro trabajo. Vivían en estructuras muy básicas de unas pocas habitaciones, eran enterrados en tumbas sencillas y no podían permitirse el embalsamamiento. @L@LLa clase media estaba formada por artesanos, comerciantes y otras personas vinculadas a la industria. Vivían en casas más espaciosas y algunos podían permitirse el embalsamamiento y tumbas modestas. @L@LLa clase más rica eran los altos funcionarios del gobierno. Podían permitirse los mejores lujos, incluido el embalsamamiento, y a menudo se les construían tumbas suntuosas. Su dieta era más rica y variada que la de otros egipcios. En el examen de algunos restos momificados de egipcios de clase alta, entre el 10 y el 20 por ciento tenía arteriosclerosis, es decir, endurecimiento de las arterias, lo que indica un consumo abundante de grasas animales y, quizás, una vida de estrés. Los hombres ricos solían representarse con barriga, señal de su prosperidad."
        }
    }
    message_history_juggling {
        id: 169,
        
        size [30, 20]
        image { id: 95, pos [15, 15] }
        title { text: "Malabarismo", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "Los antiguos egipcios son los malabaristas conocidos más antiguos. En una tumba del Reino Medio en Menat Khufu (Beni Hasan), unas pinturas representan a jóvenes realizando una variedad de malabarismos, incluidas mujeres a hombros de otras que se lanzaban pelotas entre sí. @L@LEl significado del malabarismo en el antiguo Egipto no está claro. Puede que tuviera algún significado religioso, o quizás fuera puro entretenimiento."
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
            text: "Música",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los egipcios tocaban una gran variedad de instrumentos, como flautas (que existían en muchos tamaños distintos), arpas, liras, laúdes, panderos y otros instrumentos de percusión. Los cantantes eran parte integral de la música egipcia, y la mayoría de los himnos y poemas registrados en papiros estaban pensados para cantarse con música. @L@LLos instrumentos de percusión se usaban especialmente para acompañar la @171danza. Muchos bailarines tocaban castañuelas mientras actuaban. @L@LLos egipcios también tocaban trompetas. Las trompetas se asociaban con el ejército (quizá los egipcios tenían su propio toque de diana) y se encuentran con frecuencia en las tumbas de reyes y líderes militares. Se encontraron dos trompetas en la tumba de Tutankamón. Para escuchar cómo sonaban las trompetas, una de ellas se tocó en 1939. Tras unas pocas notas, la trompeta se deshizo de inmediato. Fue restaurada en el acto. La trompeta también se asociaba con @376Osiris, dios de la agricultura y de la crecida del Nilo. @L@LOtros instrumentos también tenían significado religioso. El sistro, un gran instrumento parecido a un sonajero, se asociaba con @380Hathor, diosa de la alegría, el amor y la fiesta. Las flautas se asociaban con @378Amón, dios del Sol."
        }
    }
    message_history_dance {
        id: 171,
        
        size [30, 20]
        image { id: 97, pos [15, 15] }
        title { text: "Danza", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "La danza del antiguo Egipto evolucionó a partir de los rituales que los cazadores usaban para prepararse para la caza. Un bailarín principal, llamado el bailarín-sacerdote, era responsable de que las danzas se ejecutaran correctamente. @L@LMás tarde, la danza fue parte integral de las fiestas y otras celebraciones religiosas, pero también era una forma de entretenimiento por sí misma. Las compañías de danza profesionales actuaban en las plazas de las ciudades y podían contratarse para fiestas privadas. Los bailarines solían ir acompañados de @170música. La mayoría de los bailarines profesionales eran mujeres, y muchas lucían tatuajes de Bes, dios de la música y la danza, en los muslos.  @L@LAlgunos ciudadanos también bailaban como pasatiempo, aunque este entretenimiento estaba reservado principalmente a las clases bajas. Cuanto mayor era la posición de un egipcio, menos probable era que bailara. Además, hombres y mujeres nunca bailaban juntos. Las mujeres bailaban con otras mujeres, y los hombres bailaban con otros hombres. @L@LAl parecer, los pasos de danza egipcios recibían nombres según lo que representaban, por ejemplo, «llevar un animal de la mano», «la captura exitosa de un barco» y «el pollo funky»."
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
            text: "Historia",
        }
        content {
            text: "El senet era el juego de mesa más popular del antiguo Egipto. El tablero era rectangular y estaba dividido en tres filas de 10 casillas cada una. Lo jugaban dos personas, y cada jugador tenía al menos cinco piezas. Los movimientos se determinaban con un conjunto de cuatro palillos de tirar. Las reglas del senet no se registraron en ningún sitio, así que nadie sabe con certeza cómo se jugaba. Sin embargo, la mayoría de los historiadores coinciden en que el juego representaba el viaje al más allá. Se considera que tanto el backgammon como la rayuela descienden del senet. @L@LEl senet, junto con otros juegos, probablemente era una de las muchas diversiones a las que se entregaban los egipcios en tabernas o posadas. Tras un duro día de trabajo, muchos egipcios acudían a las tabernas locales, donde se servía @194cerveza y la conversación animada llenaba el ambiente. Tanto hombres como mujeres, en especial las solteras, frecuentaban las cervecerías."
        }
    }
    message_history_taxation_and_money {
        id: 173,
        
        size [30, 20]
        image { id: 99, pos [15, 15] }
        title { text: "Impuestos y dinero", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "Los antiguos egipcios pagaban impuestos a su faraón, que se abonaban en especie. Así, por ejemplo, un granjero debía entregar al faraón una cantidad determinada de grano. Se enviaba a los escribas a todas las granjas para determinar cuánto debía cada agricultor. @L@LEl valor se expresaba a veces en deben. Los deben eran discos de metal que probablemente se usaron por primera vez como pesas."
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
            text: "Gobierno y burocracia",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El gobierno del antiguo Egipto era muy burocrático. Cada tarea imaginable tenía un funcionario asociado con un título de resonancia grandilocuente. Por encima de todos, por supuesto, estaba el faraón. El hombre de confianza del faraón era su visir, responsable de que se cumplieran todas las órdenes del faraón. Bajo el visir estaban los nomarcas (gobernadores regionales), cancilleres, virreyes, supervisores y alcaldes; la lista sigue y sigue. Y, puesto que el antiguo Egipto era una teocracia, los @384sacerdotes desempeñaban un papel fundamental. @L@LMuchos individuos ostentaban más de un título. Por ejemplo, Imhotep, que sirvió a Dyoser I y supervisó la construcción de la Pirámide Escalonada, ostentaba los títulos de visir, sumo sacerdote de Ptah y supervisor de obras, entre otros."
        }
    }
    message_history_pharaohs_home {
        id: 175,
        
        size [30, 20]
        image { id: 100, pos [15, 15] }
        title { text: "Hogar del faraón", pos [125, 15] }
        subtitle { text: "Historia" }
        content {
            text: "El hogar del faraón era la residencia más majestuosa de la ciudad. Mientras que la mayoría de las casas tenían solo una o dos habitaciones, las mansiones de algunos faraones contaban con decenas de estancias y estaban equipadas con las mejores comodidades que el antiguo Egipto podía ofrecer. @L@LAl igual que en el @174gobierno, los egipcios al servicio del faraón ostentaban títulos y eran responsables de tareas muy concretas. Entre el personal que empleaba el faraón se encontraban el Superintendente de Asuntos Domésticos, el Jefe de Manicuras y el Mayordomo Real. @L@LUno de los mayordomos reales, llamado Nefer-Peret, tenía responsabilidades muy específicas. Nefer-Peret debía cuidar de cuatro vacas palestinas, dos vacas egipcias, un toro y un cubo de bronce. Nada más, y nada menos."
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
            text: "Jardines y arte público",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los jardines eran extremadamente populares en el antiguo Egipto, y la mayoría de las casas tenían uno anexo. Además de cultivar @187frutas&y&verduras en estos jardines para complementar su dieta, ofrecían un lugar donde refugiarse del sol abrasador. Muchos jardines contaban con árboles cuidadosamente cultivados que daban sombra. @L@LEl arte se encontraba principalmente en los monumentos y templos de la ciudad. Se dedicaban tanto tiempo y dinero a los templos y monumentos que el resto de la ciudad solía resultar bastante anodino en comparación."
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
            text: "Comercio",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Aunque el antiguo Egipto estaba bien dotado de recursos naturales, la tierra carecía de algunos bienes. Los egipcios abrieron rutas comerciales con muchos países y regiones cercanos, entre ellos Nubia, el Líbano, Siria, Punt (que los historiadores sitúan en la costa de Somalia) y el mar Egeo, entre otros. Algunas fuentes afirman que el comercio egipcio llegó tan al norte como la actual Turquía. @L@LEl Nilo volvió a desempeñar un papel importante en el comercio egipcio. El río era navegable hasta la primera catarata, un conjunto de rápidos rocosos. Servía de camino y facilitaba los viajes de ida y vuelta a Nubia. @L@LEl Nilo también contribuía a una de las principales exportaciones de Egipto: el grano. Las crecidas eran mucho más fiables que la lluvia en el Líbano y Siria. Mientras la crecida se produjera, Egipto tenía un excedente de grano, un lujo que el Líbano y Siria no tenían con frecuencia. Las demás exportaciones egipcias incluían lino, papiro, lentejas, pescado seco, vasijas de oro y plata, pieles de buey y cuerda. @L@LA cambio, Egipto recibía diversos bienes como importaciones. Entre los más importantes estaban el oro de Nubia, la madera del Líbano y el aceite de oliva de Siria. Los egipcios también importaban otros artículos de lujo, como mirra, vino y ganado. Ocasionalmente importaban armas. @L@LLas caravanas, cargadas de mercancías, eran especialmente propensas a los ataques. Para protegerlas, unidades armadas las acompañaban en sus misiones comerciales. Debido a esas unidades armadas, algunos historiadores sostienen que Egipto no practicaba el libre comercio con sus vecinos, sino que los intimidaba para obtener bienes. Aunque la coacción probablemente tuvo algún papel en el comercio egipcio, algunos papiros también mencionan negociaciones entre Egipto y sus socios comerciales. @L@LAlgunas misiones comerciales exitosas se celebraban con inscripciones y obras de arte. Hatshepsut, una faraona, envió una flota de barcos a Punt para obtener mirra, incienso, marfil y otros bienes finos. El viaje se consideró tan exitoso que quedó registrado en los muros del templo de Hatshepsut en Deir el-Bahari."
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
            text: "Barcos y construcción naval",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El Nilo ha inspirado a los constructores de barcos durante siglos. En tiempos predinásticos, los antiguos egipcios unían juncos de papiro para formar balsas que impulsaban con pértigas. Con la llegada de la construcción de pirámides llegó el carpintero de ribera. Los barcos eran importantes para transportar los pesados materiales necesarios para la construcción de las pirámides. @L@LAl igual que otras industrias de Egipto, los astilleros eran explotaciones propiedad del gobierno. Equipados con herramientas de carpintería, los constructores primero fabricaban el casco colocando tablones uno junto a otro y sujetándolos con clavijas, cola y cuerdas diseñadas para encogerse al mojarse. Cuando las cuerdas se encogían, el casco quedaba firmemente sujeto. Los cascos de los barcos más grandes llevaban cuadernas. Una vez terminado el casco, los carpinteros equipaban el resto de la embarcación, incluido un mástil para la vela y orificios para los remos. Algunos de los barcos más grandes tenían camarotes. @L@LLos barcos eran de manga ancha y estaban diseñados para navegar muy altos sobre la superficie del agua, lo que los ayudaba a mantenerse a flote. El Nilo, aunque relativamente fácil de navegar, tenía sus bancos de arena y puntos poco profundos, y era fácil que los barcos encallaran. @L@LLos constructores de barcos fabricaban embarcaciones de gran tamaño. Una de ellas, empleada para transportar obeliscos al templo de Hatshepsut, medía 82 metros (89 yardas) de eslora. Uno de los hallazgos arqueológicos más famosos es la barcaza de Keops. Encontrada en unas 1.224 piezas junto al lado sur de la pirámide de Keops, la barcaza se reconstruyó a principios de la década de 1960. La embarcación mide más de 42 metros (46 yardas) de largo y 6 metros (6,5 yardas) de ancho, con sitio para 10 remeros más otros dos que dirigían el barco. Los historiadores no saben con certeza su significado. Algunos sostienen que es un símbolo de la barca solar de Horus. Otros creen que pudo ser la barcaza que trasladó los restos de Keops a su pirámide, o que el faraón la usó en vida. En cualquier caso, la embarcación aporta información sobre la construcción de barcos en el antiguo Egipto."
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
            text: "Enemigos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Egipto mantenía un contacto frecuente con sus vecinos, y en ocasiones las relaciones no eran muy amistosas. Egipto fue invadido varias veces durante su larga historia y gobernado por no egipcios. Estos gobernantes extranjeros, sin embargo, asumieron el título de faraón, y hasta la invasión persa, los egipcios lograron recuperar sus tierras. Egipto, no obstante, no siempre fue el que sufría los ataques. Durante el Imperio Nuevo, en particular, Egipto trató de ampliar su imperio e invadió muchas tierras vecinas. @L@LEntre los pueblos contra los que Egipto libró guerras están los nubios y los kush. Egipto invadió Nubia bastante pronto en su historia (ya en el 2900 a. C.), sobre todo para aprovechar sus ricos recursos de oro y cobre. Durante el período tardío, sin embargo, Nubia tomó la ventaja y varios faraones nubios gobernaron Egipto. @L@LA través de la península del Sinaí vivían varios pueblos con los que Egipto libró guerras. Entre ellos están los cananeos, los filisteos, los beduinos (procedentes de lo que hoy es Siria) y los hititas. Los más notables de estos pueblos asiáticos, sin embargo, son los hicsos. Durante el Segundo Período Intermedio, los hicsos gobernaron Egipto. Conservaron muchas de las costumbres culturales egipcias e introdujeron numerosas innovaciones, como el carro tirado por caballos. Los hicsos gobernaron Egipto unos 100 años, hasta que Ahmose I los derrotó y asumió el poder. @L@LAl oeste, Egipto combatió contra tribus libias, en especial los tehenu y los temehu. Los tehenu y los temehu intentaron penetrar en el delta egipcio, y Seti I los contuvo con firmeza. @182Se construyeron fortalezas en el oeste para mantener a raya a las tribus.  @L@LPor último, el poderoso Imperio romano llegó a las costas de Egipto durante el dominio de los ptolomeos. El poder militar en declive de Egipto, aunque con un tesoro y graneros abundantes (sin mencionar a la seductora Cleopatra VII), atrajo de forma natural la mirada codiciosa de Julio César y sus sucesores.  La llegada de las legiones romanas de César a suelo egipcio marcó el inicio del fin de una larga historia de dominio egipcio en la cuenca mediterránea, y finalmente redujo al otrora orgulloso Egipto a un estado vasallo. @L@LHaga clic @184aquí para saber más sobre el ejército de Egipto."
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
            text: "Estructuras defensivas",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Egipto protegía sus ciudades y pueblos con murallas y torres. Las murallas solían ser de ladrillo y se construían en forma de cuadrilátero o de círculo alrededor de la población. Las excavaciones en Abu (Elefantina), situada en el sur de Egipto cerca de la frontera nubia, han sacado a la luz un grueso muro curvo con torres semicirculares intercaladas.  @L@LEgipto defendía sus fronteras con una serie de fortalezas. Entre las más conocidas están la 'Muralla del Príncipe', una serie de 13 fortalezas construidas en la orilla oriental del Nilo."
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
            text: "Leyes",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los egipcios que tuvieran agravios contra otros podían llevar sus quejas ante un magistrado. Según la gravedad de la falta, el caso podía ser resuelto por un magistrado local o por el propio visir. Los magistrados locales eran a veces funcionarios de rango inferior de la población, como un capataz de obra. Los escribas asistían a los juicios y registraban a los participantes, los testigos, las declaraciones y los castigos. @L@LTodos estaban sujetos a la ley, tanto las clases altas como las bajas. En una escena grabada en una capilla mastaba de un visir del Imperio Antiguo, se castiga a gobernadores locales por retener ingresos fiscales. Las mujeres también participaban activamente en los juicios. En un caso, una mujer obtiene la propiedad que sus cuñados le habían arrebatado ilegalmente. En otro, una mujer es declarada culpable de robar una herramienta y una vasija de un santuario de Amón. @L@LLos castigos por los delitos podían ser muy severos y con frecuencia implicaban palizas o trabajos forzados. Durante la dinastía 18 del Imperio Nuevo, el castigo por robar pieles era de 100 golpes y cinco heridas abiertas. Algunos crímenes especialmente atroces se castigaban cortando la nariz al delincuente y desterrándolo a los confines de Egipto. @L@LLa ley egipcia no estaba codificada de forma estricta, y la mayoría de los castigos se imponían caso por caso. Se conservan algunas listas de delitos y sus castigos, sobre todo del Imperio Nuevo, pero estas listas tienden a contradecirse. @L@LLa justicia era también un concepto importante en el más allá. Antes de que una persona pudiera entrar en la otra vida, debía hacer una 'confesión negativa', enumerando todo lo que no había hecho durante su vida. Tras la confesión negativa, el corazón del individuo se pesaba frente a una pluma del tocado de Maat. Si el corazón pesaba lo mismo que la pluma, la persona era admitida en la otra vida. Si era más pesado que la pluma, el corazón era devorado por Ammit, un monstruo espantoso, y la persona era privada del acceso a la otra vida."
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
            text: "Ejército",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El ejército egipcio evolucionó a lo largo de los milenios del gobierno faraónico. En el Imperio Antiguo, los ejércitos se formaban cuando era necesario y solían estar compuestos por nobles y sus seguidores, o por extranjeros. El Imperio Antiguo no tenía un ejército profesional. Los hombres que servían en el ejército procedían de distintos estratos sociales y, presumiblemente, regresaban a sus antiguas profesiones en cuanto terminaban los combates. @L@LSin embargo, en el Imperio Nuevo la estructura del ejército había cambiado. El ejército se dividía claramente en unidades de infantería y de carros. La infantería podía dividirse en dos partes: soldados especializados en el combate cuerpo a cuerpo y soldados especializados en el combate a mayor distancia. Los carros se usaban para el combate móvil a larga distancia. Cada carro iba tripulado por soldados con arcos y flechas, que disparaban contra el enemigo. El combate naval era frecuente, aunque la armada no se consideraba una división separada y distinta de las fuerzas armadas. La armada formaba parte de las fuerzas terrestres, y los soldados que servían en las embarcaciones se describían con los mismos términos que los que servían en tierra. De nuevo, los extranjeros constituían una parte importante del ejército. Nubios, libios, asiáticos y carios luchaban en nombre de los egipcios. @L@LEl ejército egipcio se organizaba en batallones durante el Imperio Antiguo. Durante el Imperio Nuevo, los batallones se subdividían a su vez en divisiones, que recibían el nombre de dioses. Los escribas y los administradores acompañaban a los soldados a la batalla, presumiblemente para llevar el registro de lo que ocurría. @L@LHaga clic @196aquí para averiguar qué armas tenía a su disposición el ejército egipcio."
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
            text: "Cereales y cebada",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El cultivo de cereales (trigo y cebada) producía la materia prima del alimento más básico del antiguo Egipto: el pan. El trigo y la cebada se convertían en harina, que luego se horneaba para hacer pan. Para más información sobre el uso del pan de cebada, véase @194Cerveza. @L@LLos egipcios usaban tres tipos de trigo: escanda, escanda menor y espelta. El trigo se convertía en harina mediante la trilla. Las espigas se colocaban en el suelo, y se hacía entrar a ganado u otros animales grandes para que las pisotearan. Esa presión desprendía el grano de las espigas. Después, el grano se separaba de la paja y de otras impurezas, ya fuera tamizándolo o lanzando el trigo al aire. El viento se llevaba la paja más ligera, mientras que el trigo más pesado caía al suelo. Una vez procesado, el grano se llevaba a los @5graneros. Allí se convertía en harina y se almacenaba para su uso futuro.  @L@LPara hacer pan, se amasaba harina y se vertía en moldes de cerámica de distintas formas. La forma más popular era la cónica. La masa se horneaba en un hogar rodeado de brasas y ceniza. El pan se horneaba tanto en casa como por profesionales en panaderías. Los arqueólogos suponen que, debido a la cantidad de ceniza en el aire, los panaderos profesionales quizá no eran las personas más sanas."
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
            text: "Ganadería y pesca",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los egipcios criaban varios tipos de animales en ranchos o granjas para consumo. Los más comunes eran los bueyes de cuernos largos. Los pastores que cuidaban de ellos aparecen en las escenas de las tumbas como hombres muy delgados y con la cara sin afeitar. El ganado se enviaba a pastar. A veces, se llevaba a campos recién cosechados para que comiera paja y granza. @L@LLos egipcios también criaban ovejas, cabras y cerdos en las granjas, además de gansos y otras aves de corral. También criaban caballos, no para comer, sino para tirar de los carros de los egipcios más nobles. El caballo fue introducido en Egipto por los hicsos, uno de los @181invasores de Egipto. @L@LEl pescado era otra fuente de alimento, aunque parece que lo comían sobre todo las clases bajas. Los egipcios pescaban de varias maneras. Algunos salían en canoas y usaban cañas de pescar con sedal y anzuelos para atrapar un pez cada vez. También se construían trampas para capturar grandes cantidades de peces. Sin embargo, el método más eficaz era la red de arrastre. Como la captura era tan abundante, para subir la red a la superficie hacían falta dos barcos de hombres. @L@LLa pesca tenía sus peligros. Una especie de siluro tenía una espina venenosa en la aleta dorsal, y siempre existía el peligro de los cocodrilos. Los pescadores estaban razonablemente seguros en sus barcas, pero si la embarcación volcaba, el cocodrilo rara vez estaba lejos."
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
            text: "Frutas y verduras",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "@185El cereal y la cebada eran los alimentos básicos de los antiguos egipcios, pero también cultivaban una gran variedad de frutas y verduras. Las judías, los garbanzos, las lentejas y los guisantes eran muy populares, al igual que el ajo, las cebollas, los puerros, la lechuga y los pepinos. En cuanto a la fruta, se consumían higos, dátiles, uvas y granadas. Los dátiles eran especialmente populares entre las clases bajas y se usaban para aromatizar la cerveza. Los egipcios también condimentaban sus comidas con canela, cilantro, comino, eneldo y mostaza."
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
            text: "Juncos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los juncos de papiro, que alcanzaban hasta 7,5 metros de altura, no se usaban solo para hacer papel en Egipto. Con ellos se fabricaban diversos artículos domésticos, como esteras, sandalias y cuerdas. La médula de la planta se comía. A veces, el tallo se usaba como sustituto de la madera, y los tallos de la planta también se unían para formar balsas. Los juncos de papiro estuvieron a punto de extinguirse, pero han resurgido recientemente. Se vuelven a cosechar y a convertir en papel, esta vez para vender a los turistas."
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
            text: "Historia",
        }
        content {
            text: "El lino se cultivaba para fabricar @398lino, el principal textil del antiguo Egipto. Como el tallo era la parte más importante de la planta, cada una debía arrancarse de raíz en lugar de cortarse, por lo que la cosecha del lino era un proceso lento. Una vez cosechado, se eliminaban las raíces y las cabezas de semilla, y los tallos se extendían para secarse. Después, los tallos se sumergían en agua durante dos semanas, tras lo cual se golpeaban contra piedras y se separaban en fibras. Luego las fibras se enviaban a un tejedor para convertirlas en tela."
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
            text: "Arcilla",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La arcilla se obtenía con facilidad en el antiguo Egipto, y su calidad variaba según la región. A lo largo del Nilo, los años de crecidas habían dado lugar a ricos depósitos de limo listos para extraerse y moldearse como cerámica. En las regiones desérticas se encontraban vetas de marga y pizarra blandas en la caliza. La arcilla del desierto producía cerámica más dura que la del Nilo y daba objetos de tono rosado o verdoso. La cerámica hecha con arcilla del Nilo tendía a ser roja o negra. Ambos tipos de arcilla se procesaban de la misma manera para fabricar @198cerámica."
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
            text: "Oro y minería del oro",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El oro se encontraba principalmente en el desierto oriental de Egipto y en Nubia. Extraerlo podía ser una tarea ardua. En el desierto oriental, por ejemplo, las vetas de oro estaban intercaladas en el granito. El granito se reducía a polvo con cinceles y luego se sumergía en agua para separar el oro de la roca. Este proceso era sin duda muy laborioso. Aun así, el oro era relativamente abundante y, de hecho, más fácil de obtener que la plata. @L@LPara preparar el oro, primero se fundía en las minas. Una vez fundido, se vertía en agua. Al enfriarse, el oro formaba pepitas, que se llevaban a los orfebres para su uso. @L@LComo casi cualquier otro bien, las reservas de oro se controlaban estrictamente por medio de los escribas. Cada mañana pesaban cuidadosamente el oro que entregaban a los orfebres, y su trabajo se supervisaba de cerca para asegurarse de que no robaran.  @L@LAunque el oro era más abundante que la plata, de ningún modo había una cantidad excesiva. Por ello, la mayoría de los objetos estaban chapados en oro en lugar de ser de oro macizo."
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
            text: "La madera y sus usos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los árboles autóctonos no abundaban en Egipto. Aunque el suelo de las llanuras aluviales era lo bastante fértil para sustentar el crecimiento de árboles, la crecida los arrancaba de raíz antes de que pudieran desarrollarse. Los árboles que lograban crecer en Egipto incluían el sicómoro, el persea, la palmera datilera y el rábano picante. Cada uno de estos árboles tenía significado religioso y se consideraba morada de los dioses. @L@LDebido a su significado especial, los leñadores necesitaban un permiso especial para talar árboles. La madera de los árboles cortados era quebradiza y de usos limitados. Egipto importaba la mayor parte de su madera de lo que hoy es el Líbano, Siria e Israel. Cuando Egipto conquistó estas tierras durante el Imperio Nuevo, talaron los árboles sin reparos, lo que redujo considerablemente las reservas forestales. @L@LLa madera se usaba para muebles, ataúdes y construcciones. Los carpinteros eran muy hábiles para fabricar piezas de diseño intrincado, con incrustaciones y grabados."
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
            text: "Canteras",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los egipcios extraían varios tipos de roca para sus pirámides, templos y monumentos, entre ellas caliza, granito, arenisca, basalto, pizarra, alabastro y pórfido. Los canteros usaban picos y cinceles para extraer la roca dura, y sierras de cobre para la roca más blanda. @L@LLa mayoría de las canteras funcionaban solo durante la crecida, cuando los proyectos de construcción estatales alcanzaban su punto álgido. Algunas canteras trabajaban todo el año, sobre todo si había en marcha un gran proyecto de construcción, como una pirámide. @L@LPara transportar los bloques hasta su destino final, se colocaban sobre un trineo que un equipo de trabajadores arrastraba. Con frecuencia se colocaban troncos a modo de rodillos para facilitar el proceso. A veces se vertía agua delante del trineo para reducir la fricción. @L@LLos esclavos formaban parte de la mano de obra de las canteras, aunque los egipcios seguían constituyendo la mayor parte de los trabajadores."
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
            text: "Cerveza",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La cerveza era la bebida preferida de los antiguos egipcios. Se debate con fervor sobre los detalles de la industria cervecera egipcia. ¿Cómo se elaboraba la cerveza? ¿Se aromatizaba con fruta? ¿Hacían cerveza de cebada o de otros cereales? ¿Y qué hay de la maltería? Las investigaciones en curso tratan de responder a todas estas preguntas. @L@LSegún las imágenes halladas en las paredes de las tumbas, uno de los métodos de elaboración de los egipcios consistía en hornear una hogaza especial de pan. Este pan se desmenuzaba y se colocaba en un tamiz. Después se hacía pasar agua a través de él, y la mezcla resultante se embotellaba y se dejaba fermentar. Las mujeres eran las principales encargadas de elaborar la cerveza, y en los papiros se han identificado unos 17 tipos de cerveza. @L@LLos egipcios bebían la cerveza en jarras especialmente diseñadas. Las jarras tenían un tubo acodado, parecido a una pajita. En el extremo del tubo había un filtro que retenía cualquier materia sólida que pudiera haber en la cerveza. Además de beber cerveza en casa, los egipcios también la bebían en tabernas y posadas. Para saber más sobre lo que ocurría en estos establecimientos de barrio, haga clic @172aquí."
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
            text: "Fabricación del papiro",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La fabricación del papiro era un proceso bastante complejo. Primero se retiraba la corteza del junco de papiro para dejar al descubierto la médula. La médula de varias plantas se colocaba en paralelo, ligeramente superpuesta, sobre un trozo de tela. Una vez alcanzado el ancho deseado, se colocaban más tiras de médula sobre la primera capa, en ángulo recto. Luego se cubría con una segunda tela y la médula se golpeaba con un trozo de madera pesado o con un mazo. Al golpearla, la médula se soldaba. Después, el papiro se tendía al sol para secarse, y a menudo la superficie se pulía con una piedra."
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
            text: "Armas",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los antiguos egipcios empleaban diversas armas en la batalla. Para el combate cuerpo a cuerpo, los soldados usaban varias armas, entre ellas la maza, la daga, la espada ancha y el hacha de batalla. El arma principal para el combate a mayor distancia era el arco y la flecha, aunque también se usaban honderas. El armamento egipcio evolucionó con el tiempo y dio un gran paso adelante tras la invasión de los hicsos. Los hicsos introdujeron los caballos y los carros en la guerra egipcia."
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
            text: "Artículos de lujo",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La comida, la bebida y la ropa bastaban para los campesinos, pero las clases altas del antiguo Egipto necesitaban una gran variedad de productos para mantener su estilo de vida. El principal de estos lujos era el maquillaje. Tanto hombres como mujeres se pintaban los ojos, con kohl o malaquita. Además de realzar el aspecto, los egipcios creían que el maquillaje de ojos protegía la vista. Las mujeres también usaban alheña como esmalte de uñas y, ocasionalmente, como tinte para el cabello. @L@LLa higiene era importante para los antiguos egipcios, y además del baño habitual, se perfumaban con diversos aceites y extractos. La mirra y el incienso se usaban con este fin. @L@LEstrechamente relacionado con la higiene estaba el uso de pelucas. La mayoría de los egipcios llevaban el pelo corto, quizá para evitar los piojos, y adornaban la cabeza con pelucas. Las pelucas tenían diversos estilos, y la mayoría de las mujeres tenían más de una. Solían hacerse con cabello humano, sujeto a la base de la peluca con cuerdas. @L@L@382Las joyas eran otro artículo de lujo muy popular entre los ricos."
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
            text: "Cerámica",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Muy pocas casas carecían de un suministro de cerámica. La fabricación de cerámica, una de las industrias más antiguas del antiguo Egipto, se originó en el hogar, donde las mujeres producían las vasijas necesarias para cocinar. Como otras industrias de Egipto, la alfarería pasó del ámbito doméstico al taller. @L@LEl primer paso para fabricar cerámica era preparar la @190arcilla para su uso. La arcilla debía amasarse, y a menudo se le añadía paja o granza como aglutinante. Los hombres amasaban la arcilla a mano o con los pies, pisándola para hacerla manejable. Luego la arcilla se colocaba en un torno para darle forma. @L@LEl torno de alfarero evolucionó con el tiempo. En su forma más primitiva, el alfarero hacía girar el torno con una mano mientras moldeaba la arcilla con la otra. Como no podía girar el torno muy deprisa, la cerámica debía alisarse a mano después. Durante el Imperio Nuevo, una segunda persona hacía girar el torno con ambas manos mientras el alfarero daba forma a la vasija. Esto dio lugar a un producto mucho más liso. Hacia el final del Imperio Nuevo, el alfarero volvió a girar su propio torno, esta vez con los pies, lo que produjo la cerámica más lisa hasta entonces. @L@LUna vez moldeadas, las vasijas se dejaban secar. Las piezas se decoraban durante el secado. Después de secarse, se cocían en un horno. El horno era un gran hornillo con una cámara de fuego en la base. La cámara de fuego estaba separada de una cámara superior por una rejilla de arcilla. La cerámica se colocaba sobre esta rejilla. La cámara superior estaba sellada, salvo por un orificio para dejar salir el humo. Una vez terminada la cocción, el producto estaba acabado y se almacenaba hasta que se necesitaba."
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
            text: "Historia",
        }
        content {
            text: "Los bazares eran lugares ruidosos y abarrotados. Comerciantes, hombres y mujeres por igual, exponían sus mercancías, y los compradores llegaban con bienes para intercambiarlos por ellas. Los bazares se situaban generalmente cerca del Nilo para aprovechar las nuevas mercancías que llegaban en barco. @L@LLas escenas de bazar se representaban con frecuencia en las paredes de las tumbas. La tumba de la Quinta Dinastía de Jnumhotep y Niankhkhnum, manicuros del faraón, muestra una vívida escena de mercado, con un mono amaestrado que muerde el tobillo de un aspirante a ladrón."
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
            text: "Nace una aldea",

        }
        content {
            text: "@PBienvenido al antiguo Egipto, ¡tierra de los faraones! Aquí participará en la historia de una de las mayores civilizaciones que el mundo ha conocido, en una épica historia que abarca más de quince siglos y dos docenas de generaciones. Deberá guiar a una familia, generación tras generación, desde sus primeros orígenes en la prehistoria egipcia, pasando por el amanecer de la civilización... hasta la consolidación de un imperio único y poderoso... y más allá.     @PNuestra historia comienza hace más de cinco mil años, a orillas del río Nilo, en una zona conocida como Nubt. Aquí, una pequeña confederación de clanes lucha por sobrevivir en un entorno hostil. Con usted al frente, su familia dirige este pequeño asentamiento."
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
            text: "El amanecer de la civilización",

        }
        content {
            text: "@PTras muchos años y el paso de una generación, su familia se ha asentado en la zona de Thinis, en el Alto Egipto. Aquí, un pequeño grupo de gobernantes locales intenta extender su influencia sobre el Bajo Egipto y todas las tierras a lo largo del río Nilo, y unificar este reino bajo su propia casa, con un único líder supremo.   @PHacer de Thinis una ciudad próspera, como nunca se ha visto, demostrará el valor de la confederación tinita y le ayudará a obtener la supremacía sobre el Bajo Egipto y las demás facciones que compiten por el poder. Con el tiempo, esto supondrá proporcionar entretenimiento a la población y construir magníficos templos para venerar a la deidad patrona de la región. @PPara edificar una ciudad tan grandiosa se necesitará un suministro considerable de dinero. En Thinis encontrará ricos yacimientos de mineral de oro, y explotarlos debería ser su primera prioridad. "
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
            text: "El Nilo impredecible",

        }
        content {
            text: "Los nobles tinitas aún luchan por unir las tierras del Nilo bajo un único gobernante supremo. Para ayudarlos en su empeño, se espera que usted se esfuerce en establecer una próspera comunidad en Perwadjyt, en la húmeda región del Delta del Bajo Egipto, extendiendo así su influencia a lo largo del sagrado río.  Para mantener a una población mayor que la de una aldea, deberá aprender a practicar la agricultura. @PLos agricultores egipcios han empezado a aprovechar el rico y fértil suelo que deposita la crecida anual del Nilo para cultivar sus cosechas.  Sin embargo, el Nilo puede ser peligroso.  Muchos peligros acechan en sus orillas y en sus aguas, como cocodrilos mortales, hipopótamos y mosquitos portadores de malaria."
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
            text: "El primer faraón",

        }
        content {
            text: "Mientras los habitantes de las orillas del Nilo siguen luchando por sobrevivir en este entorno hostil, un rey local llamado Narmer ha alcanzado el poder.  Aunque Narmer domina gran parte de estas tierras, aún no se ha logrado la unificación completa de los dos reinos.  En conmemoración de su ascenso, Narmer desea que su familia establezca y gobierne una nueva ciudad en Nekhen.  Esta ciudad tendrá templos dedicados a muchos de los dioses de Egipto y numerosos lugares de entretenimiento."
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
            text: "Se funda una capital",

        }
        content {
            text: "Tras una larga lucha, el rey Hor-Aha ha logrado unir los dos reinos, el Alto y el Bajo Egipto, y se ha proclamado faraón de todo Egipto.  Como signo de su soberanía absoluta y de la fundación de esta primera dinastía de Egipto, Hor-Aha ha ordenado la fundación de una imponente capital en Men-nefer, desde la cual podrá gobernar esta joven nación.  Gracias a las muchas generaciones de fiel servicio de su familia a esta tierra, el faraón le ha elegido para ser el arquitecto de esta espléndida ciudad.  Puesto que la capital es el símbolo mismo de nuestro reino, sus ciudadanos deben disfrutar de una calidad de vida jamás vista hasta ahora en esta tierra.  Para ello, con el tiempo deberá comerciar con otras ciudades del reino y ofrecer un nivel de educación superior al menos a parte de sus ciudadanos.  También deberá construir una sagrada tumba mastaba para los nobles de la ciudad."
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
            text: "Una expedición al Sinaí",

        }
        content {
            text: "Un nuevo faraón, Den, ha ocupado el trono de Egipto.  El faraón está profundamente preocupado, pues los enemigos han comenzado a amenazar nuestras fronteras y nuestra nación carece de suficiente cobre, un metal valioso necesario para fabricar armas con las que equipar a nuestras tropas.  El faraón Den ha ordenado una expedición minera a la implacable tierra del Sinaí, más allá de nuestras fronteras y en lo profundo del territorio beduino.  La zona conocida como Timna es rica en mineral de oro y cobre, así como en preciosas turquesas, pero por lo demás es estéril.  Las condiciones allí serán duras, y deberá importar muchas comodidades, quizá incluso alimentos adicionales y lino fino, desde Egipto.  El faraón exigirá envíos frecuentes desde el Sinaí y le pedirá dinero, cobre, gemas y armas.  Puede utilizar cualquier excedente de estos artículos para ayudar a sostener la expedición.  Manténgase siempre alerta, pues los beduinos del desierto del Sinaí son adversarios formidables, y no permitirán de buen grado que los extranjeros ocupen sus tierras, y mucho menos que saqueen sus riquezas minerales. @PPara aliviar la carga que estas condiciones de vida imponen a la población de su ciudad, construya un Pabellón en alguna intersección concurrida. Los ciudadanos podrán relajarse en los escenarios de malabarismo y música del Pabellón y, si además construye una Escuela de Danza, este nuevo tipo de espectáculo proporcionará un gran entretenimiento."
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
            text: "La armada del faraón",

        }
        content {
            text: "Las tropas militares de Egipto no tienen rival en el mundo conocido, pero el nuevo faraón, Khasekhemwy de la segunda dinastía, exige ahora también una poderosa armada con base en Behdet.  Nada menos que una flota de navíos de guerra bastará para asegurarnos el dominio de alta mar, pero la madera escasea, pues nuestro clima solo sustenta unas pocas y dispersas zonas de bosque.  El cedro puede importarse a un coste elevado desde Biblos, en el Líbano, al noreste.  Afortunadamente, la exportación de nuestro papiro autóctono permitirá compensar este gasto."
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
            text: "El desafío del mar ",

        }
        content {
            text: "Abedju, el lugar de enterramiento de nuestros antepasados, se ha convertido con los años en una extensa necrópolis de tumbas sagradas.  Ahora, la mayoría de los nobles desean que este sea su lugar de descanso eterno.  Para honrarlos, el nuevo faraón Khasekhemwy de la segunda dinastía ha ordenado la construcción de tres tumbas mastaba sagradas (una de mayor tamaño que las otras dos) para la nobleza local. @PEl faraón también ha ordenado la creación de una poderosa armada con base en Behdet.  Abedju también debe mantener una modesta flota de navíos de combate, si queremos que nuestras costas permanezcan totalmente seguras.  No será fácil, pues la madera escasea y nuestro clima solo sustenta unas pocas zonas dispersas de bosque.  El cedro puede importarse a un coste elevado desde Biblos, en el Líbano, al noreste.  Afortunadamente, la exportación de nuestro papiro autóctono permitirá compensar este gasto."
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
            text: "El camino a África",

        }
        content {
            text: "@PSe ha proclamado un nuevo faraón, Nebka, que inaugura la tercera dinastía de gobernantes egipcios. Nebka ha aportado gran organización y estructura a Egipto, ordenando que todo nuestro reino se divida en distritos, o nomos, cada uno gobernado por un gobernante local llamado 'nomarca'. Aunque este sistema pueda parecer rígido, bajo su liderazgo Egipto ha crecido y prosperado, y ha logrado grandes avances en el arte y la arquitectura.  @L@PLas caravanas de mercaderes, que viajan de oasis en oasis desde lo más profundo del interior africano, han empezado a proporcionar a Egipto muchos artículos de lujo raros y exóticos, ahora muy apreciados por nuestro pueblo. Por desgracia, estas caravanas son atacadas con frecuencia por guerreros de Libia e incluso por beduinos del desierto Oriental. Para asegurar estas rutas comerciales, el faraón Nebka, el de la Juncia y la Abeja, desea que establezca un puesto militar en el oasis de Selima, centro del comercio de caravanas, muy lejos de las fronteras de nuestro reino.   @L@PAllí encontrará algunos árboles aptos para la madera, cuya venta le ayudará a reunir el dinero para financiar la construcción de este puesto. Para fabricar armas, podrá obtener cobre de nuestras recién inauguradas minas de Timna, en el Sinaí. @L@PDesde el oasis de Selima, podrá importar ébano de la nación africana de Kerma. Una vez logrado establecer este puesto, proporcionará una fuente fiable de ébano a todas las ciudades de nuestro reino."
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
            text: "La frontera nubia",

        }
        content {
            text: "@PSe ha proclamado un nuevo faraón, Nebka, que inaugura la tercera dinastía de gobernantes egipcios. Nebka ha aportado gran organización y estructura a Egipto, ordenando que todo nuestro reino se divida en distritos, o nomos, cada uno gobernado por un gobernante local llamado 'nomarca'. Aunque este sistema pueda parecer rígido, bajo su liderazgo Egipto ha crecido y prosperado, y ha logrado grandes avances en el arte y la arquitectura.   @PEl faraón desea extender las fronteras de nuestro reino aún más al sur, hacia Nubia. Ordena fundar una ciudad en la primera catarata del Nilo, en la isla de Abu, para aprovechar los abundantes yacimientos de gemas, granito y arenisca que allí se encuentran.   @PLa creciente necrópolis de Abjedu exige estos materiales para la construcción de tumbas cada vez más elaboradas para la nobleza. La capital de Men-nefer también puede necesitar ladrillos para la construcción de tumbas, y el faraón Nebka puede aprobar las solicitudes de estos y otros materiales de construcción.   @PEl faraón Nebka también ha ordenado que uno de sus pares establezca un puesto militar en el oasis de Selima, para asegurar las rutas caravaneras hacia el interior de África. Una vez establecido, podrá considerar el puesto de Selima como una fuente de ébano importado, un artículo de lujo muy apreciado."
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
            text: "La primera pirámide",

        }
        content {
            text: "La ascensión al trono de Egipto del faraón Dyoser ha inaugurado una nueva era de sabiduría, saber y logros artísticos.  Se establecerá una necrópolis real en Saqqara, que servirá de lugar de descanso eterno para nobles como Hezyre y Khabausokar, los cortesanos de confianza del faraón.   @PPero este lugar albergará también un monumento como nunca antes ha visto el mundo.  Yo, Imhotep, visir real del faraón, he concebido una nueva forma de tumba sagrada para el faraón.  A diferencia de las bajas mastabas de adobe de los faraones anteriores, esta tumba se elevará hacia los cielos, como si estuviera formada por varias mastabas, colocadas unas sobre otras.  Y, además, esta 'pirámide escalonada' se construirá enteramente en piedra, para que pueda perdurar a través de los eones.  En lo más profundo, un sarcófago de granito macizo guardará el cuerpo del faraón para su descanso eterno. @PLos sacerdotes de la necrópolis de Abjedu han perfeccionado el arte de embalsamar a los muertos con lino, abriendo así la puerta de la vida eterna a todos los egipcios.  @PNuestro puesto comercial en el oasis de Selima sigue prosperando, y desde allí podrá importar ébano de África.  @PEl faraón le ha concedido una generosa suma de dinero para comenzar este proyecto. No le defraude."
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
            text: "Los beduinos del este",

        }
        content {
            text: "Al igual que Den antes que él, el faraón Huni ha ordenado una expedición a la dura tierra del Sinaí para obtener turquesas y cobre.  Desea que usted dirija esta expedición a un lugar llamado Serabit Khadim, donde todavía pueden encontrarse los restos de construcciones de un antiguo puesto egipcio.  Se desconoce su estado actual, pero aún podrían brindar algún medio de defensa a la expedición.   @PDebe saber que la última expedición enviada a esta zona nunca regresó.  Una expedición posterior, enviada para recuperarlos, tampoco regresó.  Aun así, si queremos armar adecuadamente a nuestros soldados, nuestro reino necesita cobre para fabricar armas, y este metal escasea en nuestra tierra. @PPrepárese, pues estará bajo la amenaza constante de ataques de los beduinos del desierto del Sinaí y de nuestros enemigos, los cananeos.  Extraiga todo el cobre y las gemas que pueda en estas condiciones, y cumpla con prontitud las peticiones del faraón.  Puede emplear a joyeros para utilizar el excedente de gemas y fabricar joyas para los habitantes del asentamiento."
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
            text: "Una necrópolis real",

        }
        content {
            text: "El faraón Huni desea pasar la eternidad en una pirámide escalonada, como la de Dyoser antes que él.  Desea estar rodeado de las tumbas de sus nobles y ha elegido Meidum, en el Bajo Egipto, como emplazamiento para esta necrópolis real.   @PEn señal de agradecimiento por las muchas generaciones de fiel servicio que su casa le ha prestado, Huni también le ha concedido permiso para ser enterrado en Meidum, en su propia tumba.  Al hacerlo, también ha otorgado un gran honor a su familia. @PPara garantizar que la sabiduría y el saber de Egipto se preserven a lo largo de los siglos, el faraón Huni también insta a la construcción de bibliotecas reales.  Una vez llenas de rollos de papiro, ofrecerán educación superior a las clases altas.  @PEl faraón ha enviado a otro de sus fieles cortesanos en una expedición a Serabit Khadim, en la dura tierra del Sinaí, para obtener turquesas.  Si esta expedición tiene éxito, podrá esperar importar gemas de allí. Los joyeros pueden utilizarlas para fabricar joyas, un valioso artículo de lujo, para los habitantes de su ciudad. @PLa otrora próspera ciudad de Behdet ha comenzado a decaer y ya no exporta muchos de los productos por los que era conocida."
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
            text: "Expansión a Nubia",

        }
        content {
            text: "Nuestro nuevo faraón, Snofru, está decidido a que esta, la cuarta dinastía, sea recordada como la mayor que haya gobernado Egipto.  El faraón desea que nuestras fronteras se extiendan aún más hacia el sur.  Por ello ha decretado la invasión de Nubia y el establecimiento de una ciudad fortificada en Buhen, junto a la segunda catarata del Nilo.  Allí deberá erigir también un obelisco de granito, que sirva de señal de que esta zona pertenece para siempre a Egipto y al faraón.  Sin embargo, no hay granito tan al sur, así que deberá importarlo de Abu.   @PEn Buhen se enfrentará a feroces y curtidos guerreros nubios, que lucharán hasta la muerte para impedir que establezcamos una cabeza de puente tan al sur.  No desespere, pues tras un riguroso entrenamiento en una Academia Militar, sus hombres de armas pueden convertirse en veteranos experimentados.  Además, nuestros ingenieros militares han perfeccionado el diseño de varias estructuras defensivas, como torres, murallas y casas de guardia fortificadas.  Serán de un valor incalculable para resistir el embate del ejército nubio.  También pueden emplearse barcos de transporte para ayudar a mover su ejército por agua cuando sea necesario. @PAl norte, hemos abierto relaciones con Enkomi, en la isla de Chipre.  Esta tierra debe su nombre a sus abundantes reservas de mineral de cobre, que ahora podemos comprarles.  Sin embargo, gracias a una comunidad minera egipcia establecida recientemente en Serabit Khadim, en la tierra del Sinaí, podemos suministrar cobre a nuestros gobernadores a un precio mucho más asequible.  Los suministros desde Serabit Khadim son a menudo irregulares, debido a los incesantes ataques beduinos y cananeos contra el asentamiento, y no sabemos cuánto más podrán resistir las fuerzas egipcias allí estacionadas. @PLa tumba del faraón, un monumento singular y espectacular, se encuentra actualmente en construcción en Dahshur.  De vez en cuando, el faraón puede pedirle que aporte caliza para ayudar a completar este proyecto."
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
            text: "La pirámide acodada de Snofru",

        }
        content {
            text: "@PNuestro nuevo faraón, Snofru, está decidido a que esta, la cuarta dinastía, sea recordada como la mayor que haya gobernado Egipto.  Sus arquitectos han concebido una tumba aún más espectacular que la pirámide escalonada de Huni, y el faraón desea que usted supervise su construcción.  Deberá fundar una ciudad de tamaño considerable al sur de Dahshur, el emplazamiento de la pirámide acodada del faraón.  Una vez establecida, esta ciudad proporcionará la mano de obra necesaria para completar este ambicioso proyecto. @PLa pirámide acodada se construirá con un núcleo de piedra sencilla y revestida de caliza blanca fina, para que brille por siempre bajo el sol del desierto.  Encontrará cantidades suficientes de caliza en Dahshur, pero deberá importar la cantidad necesaria de piedra sencilla para esta empresa. @PEl faraón desea que nuestras fronteras se extiendan aún más hacia el sur, y con este fin ha enviado fuerzas militares para invadir Nubia y establecer una ciudad fortificada en Buhen, junto a la segunda catarata del Nilo. @PAl norte, Egipto ha abierto relaciones con Enkomi, en la isla de Chipre.  Esta tierra debe su nombre a sus abundantes reservas de mineral de cobre, que ahora constituyen una importación importante. @PSe pueden obtener gemas preciosas de un puesto egipcio establecido recientemente en Serabit Khadim, en la tierra del Sinaí.  Últimamente el suministro se ha vuelto irregular, debido a los incesantes ataques beduinos y cananeos contra el asentamiento, y no sabemos cuánto más podrán resistir las fuerzas egipcias allí estacionadas."
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
            text: "La verdadera pirámide",

        }
        content {
            text: "@PEl faraón Snofru ha traído orden a Egipto, y el reino prospera ahora bajo su sabio y benevolente gobierno.  Snofru desea emprender otro proyecto de construcción en Dahshur, aún más ambicioso que la pirámide acodada ya terminada.  Los arquitectos, topógrafos e ingenieros reales confían en poder construir un edificio cuyos lados se elevan en un único ángulo continuo, culminando en un pico perfecto.  Si tienen éxito, será la primera pirámide verdadera y un digno hogar para el faraón Snofru ¡por toda la eternidad!    @PLa esposa del faraón, la reina Hetehpheres, ha dado a luz recientemente a un hijo al que han puesto el nombre de 'Jufu'.  Nuestro pueblo mira al día de su futuro reinado con gran temor, pues los videntes de Horus, dios del faraón, han predicho que no mostrará ninguna de la benevolencia de su padre hacia nuestro pueblo.  Aunque logrará grandes cosas, temen que gobierne Egipto con una tiranía inflexible. @PPuede adquirir madera de Biblos, ya que los carpinteros tendrán que construir muchas rampas para que los trabajadores puedan llegar a la cima de esta gran pirámide."
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
            text: "La defensa de Egipto",

        }
        content {
            text: "@PEl faraón Jufu ha tomado el trono y, tal como anunciaron los videntes de Horus y Ra, nuestro pueblo ya empieza a sufrir bajo su opresión.  @PJufu ha ordenado que se envíe de inmediato un gobernador real a Iunet, para defender nuestra tierra de los invasores kushitas.  Iunet puede sostener una pequeña industria pesquera, que alimentará a este asentamiento durante un tiempo.  Si los kushitas invaden por agua, sin embargo, el río puede volverse peligroso para los barcos de pesca, y las orillas quizá sean más útiles para sostener una flota de barcos de guerra.  Si la comida escasea, también se puede criar ganado para obtener carne, aunque los rebaños necesitan mucha paja como forraje, y la paja es difícil de cultivar en esta tierra.  Debe buscar otras ciudades con las que comerciar por paja, pues también la necesitará para fabricar ladrillos para su mastaba. @PLa ciudad de Biblos, en el Líbano, tierra de los cedros, ha comenzado a comerciar con los poderosos imperios del este.  Se trata de Asiria y Ur, en la tierra llamada 'Mesopotamia', entre los dos grandes ríos, y de ellos se puede obtener el mejor marfil a través de Biblos.  Con la llegada de artículos de lujo tan raros y exóticos, Iunet sin duda prosperará. @PEn la capital, el pueblo egipcio ha empezado a disfrutar de un juego de mesa llamado senet.  Este juego suele disfrutarse con una jarra de cerveza, en un lugar público llamado 'Casa del Senet'.  Estos lugares pueden ofrecer un grato entretenimiento a la gente de Iunet, alejándola de la tiranía de la autoridad de Jufu. @PEl faraón ha ordenado que se excaven innumerables canteras en On, en la región del Delta, para extraer un gran suministro de caliza blanca de calidad.  Solo los dioses saben qué empresa tiene planeada el faraón para el uso de esta piedra.  Se rumorea que planea un colosal proyecto de construcción en la meseta de las afueras de Rostja, para eclipsar la fama que su padre, el sabio y benévolo Snofru, se ha ganado con la finalización de sus dos nobles pirámides."
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
            text: "Marfil del Este",

        }
        content {
            text: "@PEl faraón Jufu ha tomado el trono y, tal como anunciaron los videntes de Horus y Ra, nuestro pueblo ya empieza a sufrir bajo su opresión.  Se rumorea que planea iniciar un colosal proyecto de construcción en la meseta de las afueras de Rostja, para eclipsar la fama que su padre, el sabio y benévolo Snofru, se ha ganado con la finalización de sus dos nobles pirámides.  @PEl faraón Jufu ha ordenado excavar un grupo de canteras en Tura, en la región del Delta, donde recientemente se han descubierto ricos yacimientos de caliza blanca de calidad.  También debe construir tres tumbas mastaba para los nobles de esta región, para que el faraón pueda honrar su devoción.  El asentamiento minero que ha fundado se llamará 'On' y servirá como una abundante fuente de caliza blanca de calidad durante muchos años... aunque solo los dioses saben qué empresa tiene planeada el faraón para su uso. @PLa ciudad de Biblos, en el Líbano, tierra de los cedros, ha comenzado a comerciar con los poderosos imperios del este.  Se trata de Asiria y Ur, en la tierra llamada 'Mesopotamia', entre los dos grandes ríos, y de ellos se puede obtener el mejor marfil a través de Biblos.  Con la llegada de artículos de lujo tan raros y exóticos, On sin duda prosperará. @PJufu también ha enviado un gobernador real a Iunet, para defender nuestra tierra de los invasores kushitas.  Los visires reales miran con compasión al gobernador encargado de esta tarea difícil y peligrosa.  @PEn la capital, el pueblo egipcio ha empezado a disfrutar de un juego de mesa llamado senet.  Este juego suele disfrutarse con una jarra de cerveza, en un lugar público llamado 'Casa del Senet'.  Estos lugares pueden ofrecer un grato entretenimiento a la gente de On, alejándola de la tiranía de la autoridad de Jufu."
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
            text: "La Gran Pirámide y la Esfinge",

        }
        content {
            text: "El faraón Jufu por fin ha dado a conocer sus planes, y sus ilimitadas aspiraciones pesarán sin duda sobre nuestro pueblo.  El faraón tanto maldice como bendice a su familia, pues aunque se le ha concedido el rango de Nomarca, también se le ha encargado llevar a cabo el proyecto de construcción más ambicioso jamás emprendido en nuestra tierra.   @PEl eterno lugar de descanso del faraón será un enorme complejo piramidal, situado lejos de cualquier ciudad, en la meseta de las afueras de Rostja.  Su sarcófago será de granito macizo, y su barca funeraria, de cedro libanés de gran valor. Junto al complejo piramidal del faraón, también se construirá una pirámide menor para su hijo, el príncipe Kefrén, cuya tiranía rivaliza con la de su padre, aunque sus logros no lo hagan.  Kefrén también declara que su imagen sea tallada en la roca viva de Rostja, en una gigantesca figura llamada 'esfinge', con cuerpo de león y cabeza de hombre. @PPara apoyar el enorme esfuerzo constructivo que requiere la finalización de este monumento, deberá establecer un gran asentamiento en Rostja.  Por ello, las condiciones allí quizá no sean muy refinadas, pues su objetivo es únicamente completar estos tres grandes proyectos y honrar al faraón.   @PSe le proporcionará parte de la caliza blanca de calidad necesaria para el revestimiento exterior de estas pirámides, pero también necesitará comprar gran parte de lo que precise con los fondos propios de la ciudad. @PEl faraón le confía, como uno de sus nobles Nomarcas, estas tres tareas sagradas.  Debe demostrar una dedicación inquebrantable al faraón y cumplir sus deseos... cueste lo que cueste."
        }
    }
    message_history_bahariya_oasis {
        id: 219,
        type: 3,
        size [40, 30]
        title {
            text: "Oasis de Bahariya",

        }
        subtitle {
            text: "El Desierto Occidental",

        }
        content {
            text: "@PEl reinado de Jufu y de Kefrén ha llegado a su fin, y con ellos también ha terminado la cuarta dinastía de familias gobernantes egipcias.  Pero la dama Khentkaus, un miembro lejano de esta familia, ha dado a luz a un nuevo faraón llamado 'Userkaf', y así la línea real continúa sin interrupción.  Con Userkaf comienza la quinta dinastía, una era que promete grandes cambios.   @PUserkaf ha descentralizado en cierta medida el gobierno de nuestro país y ha concedido más poder a las autoridades locales.  Ahora los Nomarcas como usted son libres de gestionar sus propios asuntos.  El faraón no intentará la construcción de una tumba monumental que lo albergue por la eternidad, porque tiene otro proyecto en mente para usted. @PEl faraón ha declarado a Ra, dios del sol y del reino, Rey de los Dioses, y pretende proclamar su soberanía por toda la tierra.  Ya hay muchos Templos del Sol esparcidos por el paisaje egipcio, pero el faraón desea extender la influencia de Ra hasta el mismísimo límite de nuestro reino. @PPara lograrlo, debe construir un asentamiento fortificado en el Oasis de Bahariya, en lo profundo del Desierto Occidental. Use con sabiduría el agua que pueda encontrar allí, pues la poca que hay tan lejos del preciado Nilo suele ser codiciada por las fieras del desierto.  También debe estar atento a los ataques de los guerreros libios y de los beduinos del desierto, que últimamente han acosado a las caravanas del desierto.  Planifique sus defensas con cuidado y aproveche los recursos que pueda encontrar en el oasis, como la madera y la caza."
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
            text: "El Templo del Sol",

        }
        content {
            text: "@PEl reinado de Jufu y de Kefrén ha llegado a su fin, y con ellos también ha terminado la cuarta dinastía de familias gobernantes egipcias.  Pero la dama Khentkaus, un miembro lejano de esta familia, ha dado a luz a un nuevo faraón llamado 'Userkaf', y así la línea real continúa sin interrupción.  Con Userkaf comienza la quinta dinastía, una era que promete grandes cambios.   @PUserkaf ha descentralizado en cierta medida el gobierno de nuestro país y ha concedido más poder a las autoridades locales.  Ahora los Nomarcas como usted son libres de gestionar sus propios asuntos. El faraón no intentará la construcción de una tumba monumental que lo albergue por la eternidad, porque tiene otro proyecto en mente para usted. @PEl faraón ha declarado a Ra, dios del sol y del reino, Rey de los Dioses, y pretende proclamar su soberanía por toda la tierra.  Ya hay muchos Templos del Sol esparcidos por el paisaje egipcio, pero el faraón desea que el más grande se encuentre en Djedu, en la húmeda región del Delta del Bajo Egipto.  @PComo la mayor parte del Delta, Djedu es rica en caza, peces y otra fauna y vegetación, pero dispone de pocos recursos minerales.  Por ello, la piedra arenisca necesaria para construir el Templo del Sol deberá importarse de las canteras del Oasis de Dunqul.  Aquí se puede criar ganado para obtener carne, aunque los rebaños necesitan mucha paja como forraje. @PDeberá despejar terreno para crear una ubicación adecuada para el Templo del Sol.  Asegúrese de vender suficiente de la preciada madera que pueda cosechar antes, pues una vez agotada quizá no pueda conseguir más.  Behdet y Abjedu siempre necesitan madera y también caza, así que comerciar con ellas debería ayudar a compensar el coste de construir este monumento sagrado."
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
            text: "La amenaza kushita",

        }
        content {
            text: "@PPepi ha ascendido al trono y ha concedido a su familia el rango de Canciller, pero ha tenido un precio.   @PLa autoridad centralizada sigue debilitándose, a medida que los líderes locales y regionales se vuelven más poderosos.  Las cosechas en algunas regiones están muy por debajo de lo normal, y el espectro del hambre ha comenzado a aparecer en Egipto.  Men-nefer, en otro tiempo una ciudad espléndida y hermosa, empieza a decaer.  Los videntes predicen tiempos difíciles por venir. @PLos poderosos vecinos se están movilizando para aprovechar la creciente debilidad de Egipto.  El puesto avanzado de Buhen está sitiado por soldados kushitas sin miedo enviados desde Kerma, la mayor ciudad no egipcia de África.  Los kushitas exigen tributo, y la menor provocación podría desembocar en un ataque abierto. Nubia también ha lanzado una llamada a la guerra y busca recuperar las tierras perdidas.  @PSi Egipto quiere sobrevivir, debe hacer lo posible por preservar las rutas comerciales para que las mercancías sigan entrando y saliendo de Egipto.  Mantenga abierto el puesto comercial del Oasis de Selima, conquistado con gran esfuerzo.  Pepi, anticipando su viaje al más allá, hará con frecuencia peticiones de piedra para construir su pirámide, y otras ciudades, escasas de alimentos, buscarán sustento en usted. @PUse sus recursos con cuidado.  La valiosa madera abunda en el oasis, pero parte del bosque debe destruirse para acceder al limitado suministro de agua."
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
            text: "La ruta de las caravanas",

        }
        content {
            text: "@P@PPepi ha ascendido al trono y ha concedido a nuestra familia el rango de Canciller, pero ha tenido un precio.   @PLa autoridad centralizada sigue debilitándose a medida que los líderes locales y regionales se vuelven más poderosos.  Las cosechas en algunas regiones están muy por debajo de lo normal, y el espectro del hambre ha comenzado a aparecer en Egipto.  Men-nefer, en otro tiempo una ciudad espléndida y hermosa, empieza a decaer.  Los videntes predicen tiempos difíciles por venir.  @PNuestros poderosos vecinos se están movilizando para aprovechar nuestra creciente debilidad.  Nuestro puesto avanzado de Buhen está sitiado por soldados kushitas sin miedo enviados desde Kerma, la mayor ciudad no egipcia de África.  Los kushitas exigen tributo, y la menor provocación podría desembocar en un ataque abierto.  Nubia también ha lanzado una llamada a la guerra y busca recuperar las tierras perdidas.  @PIntente mantener la estabilidad de Egipto estableciendo un puesto administrativo en el Oasis de Dakhla.  El oasis tiene una gran arboleda de árboles valiosos, pero desafortunadamente estos árboles bloquean el acceso al limitado suministro de agua del oasis.  Desde esta importante ubicación, importe ébano del interior de África.  Pepi, anticipando su viaje al más allá, solicitará ladrillos para la construcción de su monumento.  Otras ciudades, escasas de alimentos, le pedirán sustento."
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
            text: "Guerra civil",

        }
        content {
            text: "El antiguo modo de vida ha desaparecido, y la mayoría teme que Egipto nunca recupere su pasada gloria.  Osiris ha vuelto la espalda a su pueblo, y una serie de crecidas insuficientes ha provocado una hambruna generalizada.  El poder de los faraones, en otro tiempo incuestionable, se ha evaporado y ha sido reemplazado por líderes provinciales que solo riñen entre sí. @PDe este caos han surgido dos nobles familias que intentan hacerse con el control del país.  Los gobernantes de Henen-nesw han reclamado el trono como herederos legítimos.  Son especialmente crueles y hacen poco por aliviar el hambre del pueblo.  Al sur, una nueva familia, la casa de Inyotef, ha ascendido al poder en Waset.  Esta familia ha hecho mucho por reunificar el sur, y ahora Henen-nesw ha iniciado con Waset una mortífera guerra civil por el control de todo Egipto. @PPara mostrar su benevolencia hacia el pueblo de Egipto, los Inyotef le han encomendado la reconstrucción de la recién conquistada ciudad de Thinis, una de las ciudades más antiguas de Egipto.  Dos de los edificios más hermosos y antiguos de Thinis han sobrevivido al tumulto de su conquista: el Complejo del Templo de Osiris y la mansión.  Los Inyotef han decretado que, si cualquiera de estos edificios es destruido, no se malgastará ningún fondo en su restauración.  Los gobernantes de Waset consideran la restauración de Thinis una prioridad absoluta y han reunido fondos considerables, incluso en estos tiempos de conflicto, para este propósito.  Devuelva a Thinis su antiguo esplendor, encargue una armada y reúna un ejército fuerte para defenderla de los frecuentes ataques de quienes son leales a Henen-nesw, incluidas las ciudades de Sauty, Nekhen y Khmun.  Tenga cuidado con los gobernantes de Henen-nesw: pueden exigir tributo para comprobar su lealtad, y extorsionar sus debens.  Vigile también a los oportunistas nubios, que buscan aprovecharse de las luchas internas de Egipto."
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
            text: "Guerra civil",

        }
        content {
            text: "El antiguo modo de vida ha desaparecido, y la mayoría teme que Egipto nunca recupere su pasada gloria.  Osiris ha vuelto la espalda al pueblo, y una serie de crecidas insuficientes ha provocado una hambruna generalizada.  El poder de los faraones, en otro tiempo incuestionable, se ha evaporado y ha sido reemplazado por líderes provinciales que solo riñen entre sí. @PDe este caos han surgido dos nobles familias que intentan hacerse con el control del país.  Los gobernantes de Henen-nesw han reclamado el trono como herederos legítimos.  Son especialmente crueles y hacen poco por aliviar el hambre del pueblo.  Al sur, una nueva familia, la casa de Inyotef, ha ascendido al poder en Waset.  La familia ha hecho mucho por reunificar el sur, y ahora los gobernantes de Henen-nesw han iniciado con los gobernantes de Waset una mortífera guerra civil por el control de todo Egipto. @PLos Inyotef, ocupados en combatir a los gobernantes de Henen-nesw, le han encomendado el desarrollo de su ciudad natal, Waset.  Si los Inyotef quieren triunfar en su lucha contra los gobernantes de Henen-nesw y consolidar su reputación en Egipto, Waset debe ser un punto de referencia en el que otras ciudades confíen, ofreciendo socorro o soldados a quienes pidan ayuda.  Waset, que podría ser la capital si los Inyotef resultan victoriosos, debe convertirse en una gran ciudad.  Con los escasos recursos disponibles, construya un Templo del Sol y una pirámide para mostrar a los egipcios la gloria de los Inyotef. @PWaset no es inmune al ataque.  Los gobernantes de Henen-nesw, y quienes les son leales, pueden amenazar su ciudad de vez en cuando, y Henen-nesw podría intentar extorsionar debens del tesoro de su ciudad.  Para defenderse de estos considerables riesgos, construya un ejército y una armada fuertes que protejan su ciudad y acudan en defensa de otras ciudades amenazadas."
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
            text: "Reunificación",

        }
        content {
            text: "Los servicios de su familia durante la guerra civil no han quedado sin recompensa.  Yo, el faraón Mentuhotep, he concedido a su familia el rango de Visir.  No hay nadie en todo Egipto en quien confíe más que en usted.  Ahora que los reinos gemelos del Alto y el Bajo Egipto están reunidos y la capital de Waset prospera, necesito que me ayude a consolidar mi posición en todo el reino. @PAunque reunificado, Egipto es propenso a escaramuzas internas, sobre todo en las zonas que antes fueron leales a los gobernantes de Henen-nesw.  Para ayudar a consolidar nuestra nueva unión, quiero que reconstruya y defienda Kebet.  Kebet debe ser una ciudad gloriosa que muestre a los ciudadanos de Egipto lo que es posible bajo mi gobierno.  La ciudad sufre ataques frecuentes desde las ciudades leales que quedan, como Khmun, y debe asegurarse de defender las fronteras de su ciudad. @PEl hambre sigue acechando al país, y las ciudades del reino le solicitarán con frecuencia alimentos. Responda con la mayor rapidez posible a sus desgarradores ruegos, para que todo Egipto conozca mi benevolencia y la dedicación de mi visir de mayor confianza. @PSé que le pido mucho, pero no hay nadie más en Egipto capaz de llevar a cabo esta difícil tarea."
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
            text: "Reunificación",

        }
        content {
            text: "Los servicios de su familia durante la guerra civil no han quedado sin recompensa.  Yo, el faraón Mentuhotep, he concedido a su familia el rango de visir.  No hay nadie más en Egipto en quien confíe más que en usted.  Ahora que los reinos gemelos del Alto y el Bajo Egipto están reunidos y la capital de Waset prospera, necesito que me ayude a consolidar mi posición en todo el reino. @PAunque reunificado, Egipto es propenso a escaramuzas internas, sobre todo en las zonas que antes fueron leales a los gobernantes de Henen-nesw.  Para ayudar a consolidar el país recién reunificado, quiero que reconstruya y defienda Menat Khufu, que quedó casi destruida durante la guerra civil.  Menat Khufu debe ser una ciudad gloriosa que muestre a los ciudadanos de Egipto lo que es posible bajo mi gobierno.   @PEl hambre sigue acechando al país, y las ciudades del reino le solicitarán con frecuencia alimentos. Responda con la mayor rapidez posible a sus desgarradores ruegos, para que todo Egipto conozca mi benevolencia y la dedicación de mi visir de mayor confianza. @PTengo una petición más de noble: quiero que construya obeliscos de granito para proclamar aún más todo lo que he hecho por esta tierra durante mi vida. @PSé que le pido mucho, pero también sé que es usted el único en Egipto capaz de hacer lo que le he pedido."
        }
    }
    message_history_itjtawy {
        id: 227
        type: 3
        size [40, 30]
        title { text: "Itjtawy", pos [50, 80] }
        subtitle { text: "Se funda una nueva capital", pos [10, 30] }
        content {
            text: "Oh, poderoso faraón, amado de Ra, cuánta fortuna debe sentir.  Su ascenso sin precedentes al trono de Egipto es material de sueños. ¡Ni los dioses ni los hombres podrían forjar una recompensa mayor! Con la llegada al poder de su familia, Egipto puede empezar de nuevo y quizá todos podamos olvidar los horrores de la guerra civil. @PPara señalar este nuevo comienzo, debería construir una magnífica nueva capital.  Itjtawy, con sus abundantes recursos naturales, es un lugar perfecto.  Aprovechando lo que la tierra ofrece, puede construir una ciudad espléndida, digna del valor y la dedicación de su dinastía. @PPara que las hazañas de su gran dinastía se recuerden siempre, debería construir dos majestuosas pirámides de ladrillo para usted y su familia, y una temible esfinge que custodie su tumba.  Una familia con sus logros no merece menos. @PTenga en cuenta, sin embargo, que algunos en el país cuestionan la legitimidad de su gobierno.  Muchos siguen sufriendo los efectos de la hambruna y murmuran que usurpó el trono.  Si alivia la miseria de esta gente y les ayuda a reconstruir sus hogares, ganará sin duda su lealtad inquebrantable.  Debe intentar proveer a sus nuevos súbditos lo mejor que pueda, para evitar que estas desafortunadas personas tomen las armas contra usted."
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
            text: "Hacia Nubia",

        }
        content {
            text: "Ahora que Egipto está firmemente unido bajo su gobierno, toda su corte y yo, su visir de confianza, recomendamos extender las fronteras de nuestro país hacia el sur, hasta Nubia.  El lecho seco del río en Allaqi es rico en vetas de oro, y una poderosa ciudad en Iken, con usted como residente, sin duda impedirá que los nubios intenten atacar.  Sin embargo, tenga cuidado con los kushitas.  Son un adversario mucho más peligroso que los nubios y usarán sus espadas para animarle, oh faraón, a dejar su reino en paz. @PPara dejar una huella duradera en Nubia, debería construir un gran obelisco que atestigüe los muchos logros de Egipto.  El obelisco ofrecerá a los nubios pruebas convincentes de los beneficios del gobierno egipcio y será un recordatorio constante de nuestra presencia. @PMientras su atención directa se dedica a Iken, no olvide nuestra intención de establecer una próspera ciudad portuaria en el Mar Rojo, en Sawu.  Sawu necesitará su ayuda y no dudará en pedírsela.  Si Sawu prospera, proporcionará a Iken el cobre tan necesario, con el que se podrán forjar armas."
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
            text: "A orillas del Mar Rojo",

        }
        content {
            text: "Ahora que Egipto está firmemente unido bajo su gobierno, debemos desarrollar relaciones comerciales con ciudades de todo el mundo para aumentar la riqueza de Egipto, oh rey de las Dos Tierras.  @PA medida que su pueblo prospera, exige artículos más exóticos.  Cansado de las joyas, un artículo de lujo fácil de obtener, su pueblo desea artículos de lujo raros y costosos, como el incienso.  Su corte y yo, su visir de confianza, recomendamos que establezca un puerto en el Mar Rojo, en Sawu.  Sawu ofrece una ruta comercial hacia la lejana Punt, de donde se puede importar el mejor incienso del mundo, aunque a un gran coste.   @PAparte de algunas modestas vetas de oro y mineral de cobre, Sawu produce pocas materias primas propias, pero puede prosperar como fabricante de productos acabados.  Importando materias primas de sus socios comerciales y exportando productos terminados, Sawu podrá obtener un beneficio considerable. @PMientras usted está ocupado en Sawu, uno de sus Nomarcas más valientes está estableciendo un nuevo centro comercial en Nubia.  Su ciudad, Iken, probablemente sufra ataques, así que mi amado faraón debe estar preparado para enviarle cualquier recurso que necesite. @PBajo su gobierno, Sawu sin duda será una de las ciudades más hermosas del reino, idónea como lugar de descanso final para usted y su familia.  Mientras establece el próspero puerto, no descuide los preparativos para el más allá.  Un mausoleo y una pequeña pirámide de ladrillo proporcionarán aposentos suntuosos para usted y su familia tras su paso al Campo de los Juncos."
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
            text: "El desafío",

        }
        content {
            text: "¡Respetado faraón, todo por lo que su familia ha luchado tan duramente está amenazado!  La armada nubia patrulla el Nilo, penetrando en lo más profundo del territorio egipcio y saqueando tanto aldeas como ciudades.  Los nubios también abordan barcos mercantes y roban sus mercancías.   Para ayudar a sus ciudades del norte a rechazar al enemigo, debe estar preparado para enviar barcos de guerra y soldados a las ciudades que los necesiten.   @PPara impedir que los nubios vuelvan a navegar por nuestras aguas, sus asesores militares recomiendan construir un conjunto de fuertes en Heh, entre la segunda y la tercera catarata del Nilo.  Los fuertes funcionarán como un tapón, encerrando a los nubios al sur.   @PExpulsar con éxito a los nubios depende de la conquista de la ciudad de Baki.  Baki es rica en recursos, y tomarla paralizará la economía nubia.  Una vez arrebatado el control de Baki a los nubios, podrá empezar a importar arenisca de la ciudad para su gran mausoleo.  Su mausoleo en Heh servirá como recordatorio de su dominio sobre los indómitos nubios.   @PHay muchos desafíos ante usted mientras protege Egipto de los nubios.  Preste atención, oh Horus viviente, a la tormenta que se levanta en el este.  El estruendo de los cascos de caballo se oye por toda Canaán, y carros veloces como el rayo arrasan cuanto encuentran a su paso.  Estos formidables carros, como nunca se han visto en ningún lugar, son conducidos por los guerreros hicsos.  Ya se han divisado nubes de tormenta en el horizonte egipcio, y debe prepararse para el peligro inminente."
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
            text: "La ciudad de Bastet",

        }
        content {
            text: "Real faraón, con rutas comerciales sólidas bien establecidas, debemos mostrar ya a Egipto lo que el éxito y la riqueza pueden aportar.  Bubastis es un lugar perfecto para una ciudad así: podemos proteger nuestras valiosas rutas comerciales hacia el este y, al mismo tiempo, rendir homenaje a Bastet, que ha velado por Egipto. @PLa ciudad de Bastet debe ser única en Egipto.  Debe ser tan encantadora como la flor de loto, floreciendo con espectáculos, escuelas, bibliotecas y lugares de culto.  Sus ciudadanos deben estar bien abastecidos de las cosas más refinadas, incluido el incienso importado.  Una vez terminada, Bubastis será la joya de las dos coronas. @PMientras construye esta gloriosa ciudad, preste atención a la tormenta que se levanta en el este.  El estruendo de los cascos de caballo se oye por toda Canaán, y carros veloces como el rayo arrasan cuanto encuentran a su paso.  Estos formidables carros, como nunca se han visto en ningún lugar, son conducidos por los guerreros hicsos.  Ya se han divisado nubes de tormenta en el horizonte egipcio, y debe prepararse para el peligro inminente."
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
            text: "Egipto recuperado",

        }
        content {
            text: "Poderoso faraón, Egipto pide a gritos su ayuda.  Los temibles hicsos han invadido nuestra tierra y han establecido su propia capital en Rowarty.  Desde Rowarty han interrumpido muchas de nuestras rutas comerciales, asfixiando los suministros necesarios.  Debemos detener su conquista antes de que sea demasiado tarde. @PSi es de su agrado, gran faraón, deberíamos recuperar la ciudad de Khmun, que han profanado estos repugnantes invasores.  También deberíamos construir un ejército y una armada fuertes, pues quizá tengamos que suministrar tropas y armas a nuestros compatriotas del norte, sobre todo en Rowarty, para ayudar a repeler la incursión hicsa.  Ellos buscarán su apoyo, hijo de Ra.  Pero ahora también disponemos de un arma nueva.  Nuestros sabios líderes militares se han hecho expertos en el uso del temido carro, y lo volveremos contra nuestros enemigos para expulsarlos ante nosotros.  Una vez expulsados los problemáticos hicsos, nuestros asesores militares recomiendan construir un fuerte en el Sinaí, en Sharuhen, para evitar nuevas invasiones desde el este. @P¡Ojalá nuestros problemas se limitaran al norte!  Los informes de nuestra frontera sur indican que los nubios vuelven a aprovecharse de un Egipto distraído.  Han recuperado las ciudades meridionales de Iken y Heh.  Aunque estas ciudades perdidas son motivo de preocupación, primero debemos expulsar a los hicsos antes de poder dirigir nuestra atención al sur. @PEstos hicsos son invasores impíos.  Acabamos de descubrir que han profanado la pirámide de aquí, en Khmun.  Han robado de la pirámide todas las provisiones funerarias que el poderoso faraón enterrado allí necesita en el Campo de los Juncos.  Debemos proporcionar un nuevo suministro de ajuar funerario para que el faraón enterrado aquí pueda disfrutar de la vida eterna."
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
            text: "Egipto recuperado",

        }
        content {
            text: " Oh rey de las Dos Tierras, Egipto pide a gritos su ayuda.  Los temibles hicsos han invadido nuestra tierra y han establecido su propia capital en Rowarty.  Desde Rowarty han interrumpido muchas de nuestras rutas comerciales.  Debemos detener su conquista antes de que sea demasiado tarde. @PAquí, en Sauty, estamos a salvo de un ataque inmediato, aunque los hicsos tienen la osadía de exigir tributo. Quizá tengamos que suministrar tropas y armas a nuestros compatriotas del norte para ayudar a repeler la incursión hicsa.  Ellos buscarán su apoyo, oh poderoso faraón.  Pero ahora también disponemos de un arma nueva.  Nuestros sabios líderes militares se han hecho expertos en el uso del temido carro, y lo volveremos contra nuestros enemigos para expulsarlos ante nosotros. @P¡Ojalá nuestros problemas se limitaran al norte!  Los informes de nuestra frontera sur indican que los nubios vuelven a aprovecharse de un Egipto distraído.  Han recuperado las ciudades meridionales de Iken y Heh. @PSi Egipto quiere salir intacto de estos tiempos turbulentos, mucho se exigirá a sus generales en el campo de batalla y en el río.  Para inspirar a sus dos mejores generales, usted les ha prometido construir a cada uno una pirámide tan espectacular como la suya.  Confiando en su promesa, combaten con ferocidad al enemigo, invocando toda su fuerza y su valor.   @PSi es de su agrado, poderoso faraón, debería construir tres magníficas pirámides en Sauty, una para usted y una para cada uno de sus generales.  Estas tres pirámides ocuparán un espacio considerable, por lo que tendrá que sacrificar algunos recursos valiosos para acomodarlas.  También puede que deba extender su ciudad al otro lado del Nilo para aprovechar todos los recursos necesarios para que esta ciudad prospere."
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
            text: "Expansión y conquista",

        }
        content {
            text: "Egipto ha salido de sus recientes problemas con una fuerza renovada.  ¡Biblos, con todos sus bosques verdes y sus ricas fuentes de cobre, es nuestra! Con su presencia, la ciudad sin duda prosperará, y se establecerá un Nuevo Reino. @PAh, pero ¡qué inquietante descubrimiento hicimos tras conquistar Biblos!  Un pueblo nuevo y feroz, los hititas, se ha extendido por gran parte de Asia, y algunos dicen que su imperio rivaliza con el nuestro en extensión.  Ahora han puesto los ojos en Biblos, ansiosos por sus riquezas.  Si no nos preparamos bien para su ataque, podríamos perder Biblos a manos de nuestro enemigo.  @PMientras nos preparamos para hacer frente a los hititas, debemos declarar que Biblos es egipcia para siempre.  Con su bendición, oh faraón, erigiremos una serie de tres obeliscos, dos pequeños y uno grande, que proclamen su soberanía y su fama por los confines de su imperio.  Estas torres monumentales recordarán a los habitantes de Biblos a quién deben su lealtad. @PMientras nos ocupamos de los asuntos de Biblos, otras regiones de Egipto siguen expuestas a ataques.  Los nubios han avanzado hacia el norte hasta la primera catarata, y debemos ayudar a nuestros compatriotas a repelerlos.  Los informes de Rowarty hablan de otro enemigo misterioso, los Pueblos del Mar.  Ambos enemigos deben ser sometidos con firmeza si Egipto quiere alcanzar la gloria.  Para mostrar su poderío, asegúrese de enviar tropas y barcos de guerra cuando se los soliciten."
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
            text: "La gloria de Egipto",

        }
        content {
            text: "Con los hicsos expulsados con éxito de nuestro país, nuestra tierra está madura para renacer, un Nuevo Reino que supere la gloria pasada.  Noble faraón, Baki es un lugar ideal para comenzar este Nuevo Reino.  Podemos usar la gran cantidad de oro que se encuentra allí para financiar su nueva visión de Egipto.  @PMientras Egipto está al borde de la grandeza, persisten algunos problemas molestos.  Muchas ciudades egipcias todavía se están recuperando de las perturbaciones causadas por los hicsos y quizá necesiten la ayuda del faraón.  En otras regiones, los antiguos enemigos de Egipto siguen atacándonos, y un nuevo enemigo, los Pueblos del Mar, ha estado asolando nuestra costa norte. Debe estar preparado para defender a otras ciudades egipcias de nuestros enemigos, tanto antiguos como nuevos. @PA medida que Egipto crece en prestigio, muchas ciudades están dispuestas a comerciar.  Algunas de ellas están tan familiarizadas con nuestras costumbres, y tan asombradas por su poder, que se consideran egipcias, mientras que otras nos son ajenas y comercian con nosotros por primera vez.  Por la gloria de Egipto, aproveche todas estas relaciones para proporcionar a su pueblo todos los bienes que desee. @PPara dar la bienvenida a la nueva era, sus arquitectos reales anhelan la oportunidad de construir dos pirámides y un majestuoso mausoleo para usted, oh faraón.  Estos reflejarán sin duda la riqueza y la grandeza que ha traído a Egipto."
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
            text: "Los Pueblos del Mar",

        }
        content {
            text: "Oh Horus de Oro, nuestro dominio sobre Asia es firme e incuestionable, y nuestras fronteras vuelven a extenderse muy al interior de Nubia.  Pero los problemas de nuestra costa norte van en aumento.  Los Pueblos del Mar son cada vez más agresivos y saquean nuestras ciudades sin control.  Solo la presencia del faraón bastará para derrotar a este adversario feroz y astuto.  Si encarga una armada, respaldada por un ejército fuerte, seguro que venceremos a los Pueblos del Mar.   @PMientras trabaja para derrotar a los Pueblos del Mar, sus valientes Nomarcas están dirigiendo ataques por todo el mundo.  Si tienen éxito, Egipto gobernará el mundo desde el gran río Éufrates, en Asia, hasta la extensa ciudad kushita de Kerma, al sur.  Cuando usted y sus Nomarcas hayan alcanzado la dulce victoria, su dinastía quedará registrada como la mayor dinastía que jamás haya velado por Egipto. @PSu influencia de largo alcance se ve reflejada en un nuevo socio comercial lejano, Micenas.  El rey de Micenas ha tenido noticia del esplendor y la riqueza de Egipto, y desea comerciar con nosotros.  Si acepta abrir esta ruta comercial, oh faraón, sus ciudadanos recibirán sin duda artículos exóticos como nunca antes habían visto. @PPara alojar a su familia real en el más allá, deben construirse un mausoleo impresionante y un par de imponentes pirámides de ladrillo.  Estos monumentos recordarán a todos los que vengan después sus hazañas, tanto en el campo de batalla como fuera de él."
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
            text: "La gloria del faraón",

        }
        content {
            text: "Benevolente faraón, ha traído paz y prosperidad a nuestra nación.  Bajo su sabio y capaz gobierno, Egipto vuelve a ser un país fuerte y glorioso.  Todos los Nomarcas le son leales, y ya no quedan amenazas para nuestra gran nación. @PHabiendo cumplido todo lo que su familia se propuso hace tantos años, es momento de conmemorar los logros de su gran dinastía.  La única forma de lograrlo es construir la pirámide más grande que Egipto haya conocido, una pirámide aún mayor que la de Jufu, en Rostja.  Otros miembros de su noble familia han sacrificado mucho en el largo camino que llevó a su gobierno de Egipto.  Ellos también deben ser recordados y honrados, con un mausoleo de arenisca que reconozca su apoyo inquebrantable.   @PEl lugar ideal para estos monumentos es Hetepsensusret, en la rica región del Fayum.  Desde allí podrá atender todos los asuntos de Estado y responder a cualquier petición de suministros que sus ciudades le hagan, mientras construye su gran pirámide."
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
            text: "Las orillas del Nilo",

        }
        content {
            text: "@PCon la ayuda de su familia, el rey tinita Hor-Aha ha unificado con éxito los reinos gemelos del Alto y el Bajo Egipto, se ha proclamado faraón de todo Egipto y ha fundado una imponente capital en Men-nefer.    @PSu clan se ha trasladado una vez más, esta vez a la húmeda región del Delta del Bajo Egipto, a una zona conocida como Perwadjyt. Los barcos de guerra cananeos han amenazado esta región, y probablemente tendrá que enviar algunos barcos de guerra propios cuando llegue el momento. @PSu familia ha alcanzado la condición de nobleza. Por ello, se espera que, antes de pasar de este mundo al siguiente, emprenda la construcción de una exquisita tumba de ladrillo, una mastaba, que albergue su cuerpo en su viaje al más allá. @PSin embargo, primero debe establecer algunas granjas a orillas del Nilo, para aprovechar el rico y fértil suelo que deja la crecida anual del río. Esto permitirá que su población crezca y prospere, y que con el tiempo sea lo bastante grande para completar este monumento sagrado. Pero tenga cuidado, pues muchos peligros acechan entre las aguas que dan vida al Nilo, como los cocodrilos mortíferos, los hipopótamos y los mosquitos portadores de la malaria. @L@LLa agricultura a orillas del Nilo @PDebe construir granjas directamente en la llanura aluvial, para obtener los beneficios de su mayor fertilidad. A diferencia de la mayoría de estructuras de trabajo, las granjas de la llanura aluvial no necesitan acceso directo a los empleados, pero sí necesitan una mano de obra constante de campesinos, suministrada por los campamentos de trabajo, para cuidar sus campos. Construya los campamentos de trabajo bastante cerca de las granjas de la llanura aluvial, para que los campesinos no tengan que caminar demasiado para llegar a ellos. @G56 @L@LLa cosecha anual @L@PCada año, el Nilo inunda sus orillas, renovando el suelo agotado de la llanura aluvial con un barro rico y fértil.  Los campesinos recogen la cosecha anual justo antes de la Inundación y la entregan a sus graneros.  Como solo hay una cosecha al año, asegúrese de tener suficientes graneros para almacenar una cantidad suficiente de alimentos para su población en crecimiento."
        }
    }
    message_tutorial_food_or_famine {
        id: 239
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "¿Comida o hambruna?", pos [0, 15] }
        content {
            text: "@PUna población en crecimiento necesita una fuente fiable de alimentos y algún medio para almacenarlos y distribuirlos. Ciertos animales, como los avestruces de esta región, pueden cazarse para obtener caza. Los graneros almacenan caza y otros alimentos, mientras que los bazares distribuyen la comida a los habitantes de la aldea. Como en la mayoría de estructuras de trabajo, para funcionar correctamente estos edificios deben estar al alcance de las viviendas, y la ciudad debe tener suficientes trabajadores para dotarlos de personal. @L@LCaza para obtener alimentos  @L@PConstruya una Cabaña de caza cerca de las bandadas de avestruces, y los cazadores saldrán en busca de presas. Si tienen éxito, traerán las carcasas de vuelta a la cabaña para descuartizarlas, tras lo cual un empujador de carros las entregará al granero más cercano para almacenarlas.   @PLos distintos trabajadores del bazar evalúan las necesidades de los barrios a los que sirven, obtienen alimentos de los graneros cercanos y entregan esa comida a las casas de sus alrededores para satisfacer dichas necesidades. @G60 @PConstruya graneros y bazares haciendo clic en el botón 'Estructuras de almacenamiento y distribución'. @G77 @L@PEn última instancia, su objetivo en esta misión es transformar algunas de sus 'chozas toscas' en 'chabolas humildes'.  Esto se logra proporcionándoles agua y alimentos del bazar.  Además, asegúrese de que no estén demasiado cerca de edificios industriales antiestéticos ni de viviendas de inferior calidad, pues estos desaniman las mejoras del hogar al reducir el atractivo de la zona.  @PPronto aprenderá diversas formas de aumentar el atractivo de una zona. Por ahora, simplemente evite situar viviendas demasiado cerca de las industrias.  @L@LSupervisores @L@LYa está disponible un Supervisor de los graneros, que le proporcionará información y consejos. Con el tiempo, dispondrá de muchos asesores que le ayudarán a dirigir su ciudad. @G76  @L@PPara acceder a ellos, haga clic en el icono 'Supervisores' o pulse el botón derecho sobre el edificio correspondiente."
        }
    }
    message_tutorial_entertainment {
        id: 240
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Entretenimiento", pos [0, 15] }
        content {
            text: "A medida que su ciudad avanza, algunos ciudadanos pueden disfrutar de actividades de ocio, como asistir a algún espectáculo. Una gran variedad de entretenimiento es uno de los rasgos distintivos de una ciudad verdaderamente culta, pero por ahora solo puede ofrecer entretenimiento en forma de malabaristas. @L@LLugares de entretenimiento y malabaristas @PEl malabarista necesita un lugar donde actuar, el más pequeño de los cuales se llama 'Puesto'. Construya un Puesto en un cruce para representar espectáculos de malabarismo, y una Escuela de malabaristas cerca para formar artistas. Ambos necesitan acceso a viviendas para empleados y trabajadores suficientes para dotarlos de personal. @PLos malabaristas formados en la escuela se dirigirán a cualquier Puesto cercano para dar espectáculos, aportando una cantidad modesta de entretenimiento a la zona circundante. @G61 @L@LConsulte a su Supervisor de Diversiones para conocer mejor las necesidades recreativas de su ciudad.  Haga clic en 'Superposiciones: Entretenimiento' para ver qué casas de su ciudad tienen acceso al entretenimiento."
        }
    }
    message_gold_and_crime {
        id: 241,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Oro y delincuencia" }
        content {
            text: "@L@L Extracción de oro @L@PBusque en las zonas rocosas la presencia de mineral metálico, señalada por manchas metálicas y brillantes entre las rocas. Para extraer el mineral, debe construir minas de oro junto a estas vetas. @G53 @L@LPalacio @L@PSe necesita un Palacio para convertir el mineral de oro en bruto, así como para almacenar los lingotes de oro resultantes. El Palacio es la sede del gobierno de la ciudad y debe construirse donde haya un acceso adecuado al agua subterránea (zonas con hierba). @PUna vez que su Palacio esté en funcionamiento, los mineros entregarán el mineral de oro de las minas de oro para convertirlo en dinero, contado en 'debens'. @G54 @L@LDelincuencia @L@PSin embargo, con una reserva de dinero viene el riesgo de robos. Los agentes pueden ayudar a reducir las pérdidas por robo, tanto patrullando las calles para prevenir el delito como sometiendo a los delincuentes que encuentren. @G55 @L@PSin embargo, la mejor forma de prevenir el delito es mantener contenta a su población con alimentos, atención sanitaria y empleo suficientes."
        }
    }
    message_farming_along_the_nile {
        id: 242,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "La agricultura a orillas del Nilo",

        }
        content {
            text: "La agricultura a orillas del Nilo @L@PDebe construir granjas directamente en la llanura aluvial, para obtener los beneficios de su mayor fertilidad.  A diferencia de la mayoría de estructuras de trabajo, las granjas de la llanura aluvial no necesitan acceso directo a los empleados, pero sí necesitan una mano de obra constante de campesinos, suministrada por los Campamentos de trabajo, para cuidar sus campos.  Construya Campamentos de trabajo bastante cerca de las granjas de la llanura aluvial, para que los campesinos no tengan que caminar demasiado para llegar a ellos. @G56 @L@PCada año, el Nilo inunda sus orillas, renovando el suelo agotado de la llanura aluvial con un barro rico y fértil.  Los campesinos recogen la cosecha anual justo antes de la inundación y la entregan a sus Graneros.  Como solo hay una cosecha al año, asegúrese de que su ciudad tenga suficientes Graneros para almacenar una cantidad suficiente de alimentos para su población en crecimiento."
        }
    }
    message_developing_culture {
        id: 243,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Desarrollo de la cultura",

        }
        content {
            text: "Cerveza @LSus compatriotas egipcios han perfeccionado el arte de elaborar cerveza, que se ha convertido en una bebida muy popular en todo Egipto.  Con un suministro de cebada recibido de las granjas locales, los cerveceros elaborarán cerveza y la entregarán a los Patios de almacenamiento para su distribución posterior por los trabajadores del bazar (como ocurre con los alimentos y la cerámica). @L@LMúltiples dioses @LEl dios patrón de esta región es Ra, pero Osiris y Bastet también son adorados aquí como deidades locales.  Asegúrese de que esta ciudad tenga más Templos y Santuarios dedicados a Ra, ¡pero tampoco descuide a las deidades locales!  Para atender a sus ciudadanos más valiosos, asegúrese de que tengan acceso a templos dedicados a distintos dioses. @L@LMás entretenimiento @LLos egipcios refinados disfrutan escuchando música en su tiempo libre, además de asistir de vez en cuando a un espectáculo de malabarismo.  Mientras que solo los malabaristas pueden actuar en el pequeño Puesto, tanto malabaristas como músicos pueden actuar juntos en un Quiosco de música. Construya un Quiosco de música en un cruce, y un Conservatorio cerca para formar músicos.  Tener acceso a varios tipos de entretenimiento mejora enormemente la calidad de vida de cualquier ciudad. @L@LLey y orden @LUn Magistrado que patrulla desde su Tribunal ayuda a reducir el riesgo de delitos escuchando las quejas y asegurándose de que prevalezca la sensatez."
        }
    }
    message_getting_started {
        id: 244,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Primeros pasos",

        }
        content {
            text: "Comience planificando las zonas de viviendas e industria.  A estas alturas ya sabe lo que quiere la gente, además de lo básico: comida y agua.  Debe proporcionar a algunas casas cerámica, cerveza, entretenimiento y acceso a los servicios religiosos antes de pensar en la educación superior y el comercio."
        }
    }
    message_soldiers_and_forts {
        id: 245
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: " Soldados y fuertes",
        }
        content {
            text: "Para reclutar tropas, construya un Fuerte y un Reclutador.  El Reclutador enviará nuevos reclutas, uno a uno, al fuerte hasta que esté completamente ocupado.  Hay dos tipos de Fuerte, de infantería y de arqueros, y cada Fuerte alberga dieciséis soldados, denominados una 'compañía'.  Si los soldados mueren en combate, el Reclutador se encargará de reclutar reemplazos. @G57 @L@LArmas @PLos arqueros proveen sus propios arcos y flechas, pero las tropas de infantería deben equiparse con lanzas de punta de cobre.  Con un suministro de cobre, un Armero forjará estas armas.  Después se entregan al Reclutador, para que los nuevos soldados de a pie estén debidamente equipados. @L@LObjetivos e informes @PA partir de ahora, sus objetivos inmediatos ya no aparecerán en la parte superior de la pantalla.  Haga clic en el símbolo del 'ankh' en el Panel de control para revisar su Informe de misión con los objetivos, y después visite a sus supervisores para evaluar su progreso general."
        }
    }
    message_trade_on_the_water {
        id: 246,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "A la orilla del agua",

        }
        content {
            text: "Comercio por agua @LEl comercio también puede realizarse por río y por mar, si alguna de estas rutas acuáticas llega actualmente a la ciudad.  Para abrir una ruta comercial por agua, visite el Mapa del mundo.  Para comerciar por una ruta acuática, su ciudad también necesitará un Muelle en funcionamiento. @L@LPesca en el Nilo @LEl Nilo es una fuente abundante de peces, un alimento popular en Egipto.  Además, una dieta compuesta por varios tipos de alimentos mejora la salud y la felicidad de su pueblo.  Para aprovechar esta rica abundancia, necesitará algunas barcas de pesca. @L@LConstrucción de barcos y navíos @LEl Constructor de barcos fabrica navíos de combate y barcas de pesca.  Cada barco debe contar con su propio Embarcadero.  Siempre que haya un Embarcadero que necesite una embarcación, el Constructor de barcos comenzará a construirla para él.  Sin un Embarcadero en espera, el Constructor de barcos no construirá ningún navío.   @LAunque un solo Constructor de barcos puede abastecer todas las embarcaciones que su ciudad necesite, varios Constructores permitirán reemplazar con mayor rapidez las embarcaciones perdidas.  El Constructor de barcos no necesita materiales para fabricar barcas de pesca, pero sí necesitará madera para construir embarcaciones militares, como barcos de guerra y barcos de transporte. @LLas embarcaciones militares, los barcos mercantes y las barcas de pesca tienen una manga ancha y una quilla profunda para navegar por el Nilo y las aguas costeras. No están hechas para surcar canales muy estrechos y, de hecho, no pueden viajar por arroyos o ensenadas pequeñas.  Nada le impedirá construir Constructores de barcos, Muelles o Embarcaderos en tales ubicaciones, pero si lo hace, los barcos no podrán llegar ni salir de estas instalaciones, y no funcionarán. @LAl explorar la costa en busca de emplazamientos marítimos adecuados, tenga presente que todos los barcos necesitan un paso libre entre su puerto y su destino.  Por ejemplo, no puede construir un Embarcadero de pesca en un lago interior y esperar que sus barcos alcancen los caladeros del Nilo, aunque ese lago esté conectado al Nilo por un pequeño arroyo."
        }
    }
    message_at_the_waters_edge {
        id: 247,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "A la orilla del agua",

        }
        content {
            text: "Comercio por agua @LEl comercio también puede realizarse por río y por mar, si alguna de estas rutas acuáticas llega actualmente a la ciudad.  Para abrir una ruta comercial por agua, visite el Mapa del mundo.  Para comerciar por una ruta acuática, su ciudad también necesitará un Muelle en funcionamiento. @L@LPesca en el Nilo @LEl Nilo es una fuente abundante de peces, un alimento popular en Egipto.  Además, una dieta compuesta por varios tipos de alimentos mejora la salud y la felicidad de su pueblo.  Para aprovechar esta rica abundancia, necesitará algunas barcas de pesca. @L@LConstrucción de barcos y navíos @LEl Constructor de barcos fabrica navíos de combate y barcas de pesca.  Cada barco debe contar con su propio Embarcadero.  Siempre que haya un Embarcadero que necesite una embarcación, el Constructor de barcos comenzará a construirla para él.  Sin un Embarcadero en espera, el Constructor de barcos no construirá ningún navío.   @LAunque un solo Constructor de barcos puede abastecer todas las embarcaciones que su ciudad necesite, varios Constructores permitirán reemplazar con mayor rapidez las embarcaciones perdidas.  El Constructor de barcos no necesita materiales para fabricar barcas de pesca, pero sí necesitará madera para construir embarcaciones militares, como barcos de guerra y barcos de transporte. @LLas embarcaciones militares, los barcos mercantes y las barcas de pesca tienen una manga ancha y una quilla profunda para navegar por el Nilo y las aguas costeras. No están hechas para surcar canales muy estrechos y, de hecho, no pueden viajar por arroyos o ensenadas pequeñas.  Nada le impedirá construir Constructores de barcos, Muelles o Embarcaderos en tales ubicaciones, pero si lo hace, los barcos no podrán llegar ni salir de estas instalaciones, y no funcionarán. @LAl explorar la costa en busca de emplazamientos marítimos adecuados, tenga presente que todos los barcos necesitan un paso libre entre su puerto y su destino.  Por ejemplo, no puede construir un Embarcadero de pesca en un lago interior y esperar que sus barcos alcancen los caladeros del Nilo, aunque ese lago esté conectado al Nilo por un pequeño arroyo. @L@LFabricación de ladrillos @LLos ladrillos son un material de construcción algo menos costoso, que se usa en la creación de ciertos tipos de tumbas.  Para fabricar ladrillos necesitará una Fábrica de ladrillos, así como suministros de arcilla y paja."
        }
    }
    message_the_finer_things_tutorial {
        id: 248,
        type: 2,
        message_type: 4,
        size [40, 30]
        title {
            text: "Las cosas refinadas",

        }
        content {
            text: "Complejos de templos @LA medida que crece la devoción por sus dioses patronos, el pueblo egipcio exige lugares de culto cada vez más grandes.  La mayoría de las ciudades querrán erigir un Complejo de templos a su dios elegido, para disfrutar plenamente de su benevolencia.  Una vez construido, el Complejo de templos puede ampliarse con la adición de un Oráculo y un Altar, dedicados cada uno a otros dioses menores.  Estos dioses también aportarán ciertos beneficios a la ciudad.   @L@LArtículos de lujo @LAdemás de las joyas fabricadas localmente, el pueblo egipcio aprecia ciertos otros artículos de lujo, que solo están disponibles mediante importación.  Una ciudad necesita acceso a más de un tipo de artículo de lujo para llegar a ser verdaderamente civilizada.  @L@LExplotación de la madera @G58 @LLa madera es un bien raro y valioso en el árido país de Egipto.  Las regiones con bosques son realmente afortunadas.  Para aprovechar la poca vegetación arbórea utilizable que pueda encontrarse, construya un Leñador, y se enviará a hombres a talar madera.  La madera se utiliza para fabricar barcos de guerra, barcos de transporte y también como estructura de soporte de algunos monumentos."
        }
    }
    message_housing_and_roads {
        id: 249,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Viviendas y caminos" }
        content { text: "@PLo primero que necesitará esta aldea son viviendas, para proporcionar a los colonos un lugar adecuado donde vivir, y una red de caminos, para que sus futuros habitantes encuentren su camino con facilidad y eficiencia. @PConstruya zonas de viviendas, y pronto verá a la gente instalarse en la aldea. @G50 @L@LCaminos @L@PHaga clic y arrastre el ratón para construir tramos largos de camino de una sola vez. @G51 @PEn cada cruce, los caminantes deben elegir por dónde ir, por lo que cada cruce reduce su control sobre las rutas que realmente siguen. @G52 @PPlanifique los caminos con cuidado, con el menor número posible de cruces, para asegurarse de que la gente camine por donde usted quiere.  @PEl camino por el que estos inmigrantes llegan a su ciudad se conoce como el Camino del Reino. Los migrantes siempre necesitan un paso libre desde el Camino del Reino hasta las zonas de viviendas de la ciudad. Si aísla algún barrio de este vínculo vital con el mundo exterior, sus casas simplemente desaparecerán. @L@LPara salir de cualquier panel de mensajes (como este), haga clic con el botón derecho del ratón." }
    }
    message_basic_healthcare {
        id: 250
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Atención sanitaria básica" }
        content { text: "Su ciudad sufre problemas de salud, como es de esperar con una población en crecimiento. La malaria y las enfermedades son las crisis sanitarias más comunes que afectarán a los hogares de su ciudad, aunque una peste generalizada puede golpear si la atención sanitaria es excepcionalmente insuficiente.  @PSi una casa llega a infectarse de malaria o enfermedad, todos sus ocupantes morirán, y la casa no podrá volver a ocuparse durante cierto tiempo. @G64 @LMalaria @L@PLa malaria es más frecuente cerca del agua y de los pantanos. La superposición 'Riesgos: Malaria' muestra qué casas tienen más probabilidades de sucumbir a esta enfermedad.   @PEl acceso a agua limpia de un Suministro de agua y el repelente de insectos proporcionado por un Boticario local reducen en gran medida el riesgo de malaria para cada hogar. Como la mayoría de edificios, el Boticario solo funciona cuando tiene acceso a caminos y mano de obra. @G63 @LEnfermedades @L@PLos Médicos ayudan a reducir el riesgo de enfermedad administrando medicinas a las casas a las que atienden. Un suministro constante de alimentos también es esencial para prevenir las enfermedades. La superposición 'Riesgos: Enfermedad' muestra qué casas corren peligro de sucumbir a la enfermedad." }
    }
    message_requests_from_other_cities {
        id: 251
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Peticiones de otras ciudades"
            pos [0, 20]
        }
        content {
            text: "Una de sus ciudades hermanas está en apuros y le ha hecho una petición. Si quiere mantener buenas relaciones con el resto del Reino en crecimiento, por lo general conviene atender estas peticiones de buena voluntad y con prontitud. @G65   @PUna vez que sus Patios de almacenamiento tengan suficiente cantidad del artículo solicitado, consulte a su Supervisor político para enviar un envío a la ciudad en cuestión."
        }
    }
    message_fire_in_the_village {
        id: 252,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "¡Incendio en la aldea!" }
        content { text: "¡Se ha declarado un incendio en la aldea! @L@PPara protegerse de futuros incendios, ya puede construir Parques de bomberos.  @PAl igual que la mayoría de edificios no residenciales de la aldea, el Parque de bomberos necesita trabajadores para funcionar. Para encontrar empleados, se envía a alguien desde el edificio en busca de casas ocupadas. Una vez localizada alguna vivienda, el edificio tiene acceso a empleados, aunque esto no significa necesariamente que haya suficientes trabajadores en la aldea para cubrir todos los puestos vacantes. Una vez dotado de personal, el Parque de bomberos puede enviar inspectores de incendios a patrullar la aldea.  @PLos inspectores de incendios revisan los edificios de sus rutas en busca de riesgos de incendio, reduciendo su peligro de incendiarse a medida que pasan. Los inspectores de incendios pueden prestar sus servicios a cualquier edificio situado a dos casillas de un camino. @G67 @PSi descubre un incendio, el inspector se apresura a apagar las llamas con cubos de agua y luego vuelve a su patrulla habitual. @G66 @PHaga clic en 'Superposiciones: Riesgos' para ver qué edificios corren peligro de incendiarse.  Si un edificio se quema, puede hacer clic con el botón derecho sobre el montón de escombros que queda para saber qué había allí antes del incendio. @L@LMensajes @L@PCuando oiga la campanilla que sonó al aparecer este panel, significa que le ha llegado un mensaje. Para leer un mensaje, haga clic en el botón de mensajes. @L@PAlgunos mensajes urgentes (como este) se le presentan antes de guardarse con el resto de sus mensajes. Los avisos menos urgentes van directamente a su buzón de mensajes sin mostrarse de forma especial, así que esté atento a la campanilla.  Los mensajes instructivos especiales (como este) se marcan con un pergamino azul para que pueda consultarlos fácilmente cuando los necesite." }
    }
    message_tutorial_collapsed_building {
        id: 253,
        type: 2,
        message_type: 4,
        size [40, 30]
        title { text: "Edificio derrumbado" }
        content { text: "Ciertas estructuras grandes de su ciudad se derrumbarán sin un mantenimiento adecuado. Para evitarlo, construya un Puesto de arquitectos. Al igual que el Parque de bomberos, esta estructura envía trabajadores, en este caso arquitectos, a patrullar las calles y reparar los edificios dañados que encuentren. @G68 @L@PHaga clic en 'Superposiciones: Riesgos' para ver qué edificios corren peligro de incendiarse o derrumbarse." }
    }
    message_tutorial_education {
        id: 254
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Educación", pos [0, 15] }
        content {
            text: "Ahora que ha desarrollado algo esta ciudad, es momento de proporcionar educación a algunos ciudadanos.  @L@PLas Escuelas y Bibliotecas no pueden educar a la gente sin papiro en el que escribir. @G69 @PLos Recolectores de juncos suministran a los Fabricantes de papiro las materias primas necesarias, y el papiro se distribuye directamente a las instalaciones educativas de la ciudad."
        }
    }
    message_tutorial_clean_water {
        id: 255
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Agua limpia",

        }
        content {
            text: "¡Bien hecho! Ha conseguido abastecer de alimentos el Granero de esta aldea. Ahora los aldeanos necesitan acceso a agua limpia de un Suministro de agua, muy preferible al agua de pozo.    @L@LSuministro de agua @L@PComo los Pozos, estos deben construirse en terrenos con agua subterránea, indicada por la presencia de hierba verde. Los Suministros de agua también necesitan acceso a empleados en las viviendas cercanas. @G70   @L@PUna vez en funcionamiento, un Suministro de agua enviará a un aguador a repartir cubos de agua potable limpia a todas las casas de sus inmediaciones.  Haga clic en 'Superposiciones: Agua' para ver qué casas tienen acceso a agua limpia de un Suministro de agua, a un simple pozo o a ninguna fuente de agua. @L@LInforme de misión y objetivos @PPara completar esta misión, debe proporcionar alimentos de un Bazar a seis 'chozas resistentes', para que evolucionen hasta convertirse en 'chabolas humildes'.  Haga clic en el icono del pergamino para revisar los objetivos de esta y de cualquier otra misión."
        }
    }

    message_tutorial_municipal_structures {
    id: 256,
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Estructuras municipales" }
        content {
            text: "¡Excelente trabajo! Ya tiene algo de industria en funcionamiento, y ahora puede pensar en realizar algunas mejoras en su ciudad. Los embellecimientos pueden usarse para hacer más atractivos algunos barrios, mientras que otras Estructuras municipales pueden ayudar a que las cosas funcionen con más eficiencia.   @L@LJardines, estatuas y plazas@G72 @PAl embellecer el área que los rodea, los Jardines, las Estatuas y las Plazas pueden ayudar a que las casas evolucionen.  Varias parcelas de jardín pueden colocarse una junto a otra para formar parques más grandes. Coloque Plazas en caminos pavimentados para mejorar su aspecto y aumentar el atractivo de los terrenos cercanos.  @L@LBloqueos de caminos @G62 @PLos Bloqueos de caminos pueden utilizarse para guiar a los caminantes de su ciudad.  Algunos caminantes tienen un destino específico en mente, mientras que otros no.  Simplemente recorren las calles, otorgando sus beneficios a los edificios por los que pasan.  Los Bloqueos de caminos impiden el paso de estos caminantes, pero permiten que los que tienen un destino concreto pasen y completen sus recados. @L@LCruces de agua @G71 @PLos transbordadores pueden ayudar a que su ciudad funcione con más fluidez. Los cruces de agua colocados con cuidado permiten a los habitantes de su ciudad llegar a zonas del paisaje que de otro modo serían inaccesibles, para encontrar presas u otros recursos valiosos. En algunos casos, pueden mejorar la puntualidad de ciertos repartidores al acortar sus trayectos."
        }
    }
    message_tutorial_monuments_and_more {
        id: 257
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "¡Monumentos y mucho más!"
        }
        content {
            text: "Como has llegado hasta aquí en la demo, es hora de que pruebes un poco más de lo que Pharaoh tiene para ofrecer. Asegúrate de consultar a tus nuevos asesores para obtener más información y ayuda en la gestión de tu floreciente ciudad. @L@LMonumentos @L@P¡Ya puedes empezar a construir tu tumba mastaba! Para colocar la mastaba, haz clic en el botón 'Estructuras religiosas: Monumentos'.  Necesitarás un suministro de ladrillos, además de albañiles y peones (proporcionados por los Campamentos de trabajo) para completar esta tarea 'monumental'... ¡y solo tienes once años para hacerlo! @G75 @L@LOtras comodidades del hogar @L@PAdemás de la cerámica, los hogares egipcios necesitan un suministro de cerveza y lino (y algunas otras cosas que no están disponibles en esta demo). La cerveza se elabora en una Cervecería, con cebada cultivada en granjas locales. El lino lo fabrica un Tejedor a partir del lino, otro cultivo local. Al igual que la comida y la cerámica, la cerveza y el lino se distribuyen a las casas desde el Bazar. @L@LLey y orden @L@PUn magistrado que patrulla desde su Tribunal ayuda a reducir el riesgo de delitos, escuchando las quejas y asegurándose de que prevalezca la sensatez. @L@LSalud y saneamiento @L@PCada ciudad necesita algunos embalsamadores para garantizar el saneamiento y ofrecer a sus habitantes más sofisticados los ritos funerarios adecuados. El Mortuorio utiliza lino (fabricado por un Tejedor) y presta servicios de embalsamamiento a las casas de los alrededores. Los dentistas proporcionan a las casas a las que atienden la tan deseada atención dental. @L@LEducación @L@PLas Escuelas y Bibliotecas no pueden educar a la gente sin papiro en el que escribir. Los Recolectores de juncos proporcionan a los Fabricantes de papiro las materias primas necesarias, y el papiro se distribuye directamente a las instalaciones educativas de la ciudad. @G69 @L@LNavíos de guerra @L@PPuede que necesites defender las costas de tu ciudad con robustos navíos de guerra. Necesitarás un Leñador que suministre madera al Carpintero de ribera, que construye estas embarcaciones de combate para los Embarcaderos de navíos de guerra. @L@LImpuestos @L@PAunque en esta demo no puedes obtener ingresos mediante el comercio y la exportación, sí puedes sacar algunos debens a tu población mediante impuestos. Construye suficientes Recaudadores de impuestos para cubrir toda la ciudad, y especialmente sus viviendas más caras."
        }
    }
    message_tutorial_the_gods_of_egypt {
        id: 258
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Los dioses de Egipto" }
        content {
            text: "Una ciudad egipcia no puede prosperar de verdad sin lugares de culto adecuados, en forma de Templos y Capillas religiosas. Deben situarse cerca de las casas a las que sirven y estar dedicados a uno de cinco dioses:  @L@POsiris - Dios del Nilo @PRa - Dios del Reino @PPtah - Dios de los artesanos @PSeth - Dios de la destrucción @PBastet - Diosa del hogar @L@PCada ciudad tiene distintas inclinaciones religiosas. En una ciudad determinada, un dios suele gozar de especial estima, y se le llama su dios 'patrono', mientras que los demás dioses se adoran como simples 'deidades locales' (y otros pueden ser completamente desconocidos). El dios patrono de Thinis es Bastet. @PTanto los dioses patronos como las deidades locales pueden volverse hostiles si no se les muestra el respeto que merece su posición.  Para apaciguar a los dioses, construye suficientes Templos y Capillas dedicados a cada uno de ellos para atender a tu población actual. @PUn Templo en funcionamiento envía a un sacerdote a recorrer los barrios cercanos, concediendo a los residentes acceso al culto de su dios. @G73  @LFestividades @PLas festividades son otra forma de apaciguar a los dioses.  Construye un Pabellón de festividades en la ciudad e indica a tu Supervisor de templos que celebre una festividad en honor a uno de los dioses. @L@LSupervisor de templos @L@PConsulta al Supervisor de templos para determinar el estado de cada dios en una ciudad concreta y si los dioses están suficientemente apaciguados. Los rayos indican que el dios se siente hostil hacia tu ciudad, mientras que un símbolo místico azul indica que el dios se siente benevolente hacia ella. Cuanto más veas de cualquiera de los dos, más probable es que tu ciudad sienta la presencia del dios (¡para bien o para mal!). @PHaz clic en 'Superposiciones: Religión' para ver qué casas de tu ciudad son atendidas por Templos."
        }
    }
    message_tutorial_industry {
        id: 259
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Industria" }
        content { text: "Ahora que has proporcionado a tu pueblo comida y agua básicas, puedes mejorar su nivel de vida con otros bienes, como la cerámica.  \t @L@LIndustria y cerámica @L@PConstruye un Pozo de arcilla cerca del agua, y un Alfarero cerca de él. Asegúrate de que tengan acceso a mano de obra como de costumbre, y en poco tiempo una carreta llevará arcilla al Alfarero, que fabricará cerámica para tu ciudad.  @PConstruye un Patio de almacenamiento para guardar el producto final, así como el exceso de arcilla que el Alfarero no necesite (un Pozo de arcilla suele bastar para abastecer a dos Alfareros).   @PLos trabajadores del Bazar recogerán la cerámica del Patio de almacenamiento y la distribuirán igual que hacen con la comida. @G74 @LLas industrias como la cerámica también proporcionan a los habitantes de tu ciudad empleos muy necesarios. Ahora puedes recurrir a tu Supervisor de trabajadores para ayudar a asignar tu mano de obra." }
    }
    message_tutorial_trade_with_other_cities {
        id: 260
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Comercio con otras ciudades" }
        content { text: "Ahora que has conseguido educar a parte de tu pueblo, puede que quieras generar ingresos adicionales vendiendo el papiro sobrante a las ciudades vecinas.  También necesitarás importar ladrillos de Perwadjyt para construir la sagrada tumba mastaba.  Cuando estés listo, haz clic en el icono del Mapa del mundo [gráfico aquí] para ver qué otras ciudades existen en el mundo conocido y empezar a establecer comercio." }
    }

    message_tutorial_flooded_clay_pit {
        id: 271
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Pozo de arcilla inundado" }
        content { text: "Uno de nuestros Pozos de arcilla sufrió una terrible inundación. Tuvimos que destruirlo para evitar que otros cayeran en él." }
    }
    
    message_kingdom_road_blocked {
        id: 279
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Camino real bloqueado" }
        content { text: "Una construcción reciente bloqueó el @57Camino&real que atraviesa estas tierras.  Los arquitectos reales reabrieron esta vital ruta... ¡pero tuvieron que derribar uno o dos edificios en el proceso!" }
    }
    
    message_wrath_of_ra {
        id: 280
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira de Ra" }
        video { text: "@23" }
        content { text: "Ra castiga tu arrogancia reduciendo severamente tu reputación en todo el Reino. Como despreciaste al dios, así menospreciarán los egipcios a tu persona." }
    }

    message_wrath_of_seth {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira de Seth" }
        video { text: "@21" }
        content { text: "Tu desprecio por Seth incita al dios a destruir todos tus barcos." }
    }

    message_wrath_of_seth_2 {
        id: 281
        type: 2
        message_type: 1
        
        size [30, 20]
        title { text: "Ira de Seth 2" }
        video { text: "@21" }
        content { text: "Tu desprecio por Seth incita al dios a destruir todos tus barcos." }
    }

    message_the_world_map {
        id: 282
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "El mapa del mundo",

        }
        content {
            text: "El Mapa del mundo muestra la ubicación de tu propia ciudad, así como la de otras ciudades del mundo.  Aquí puedes pagar para abrir rutas comerciales con las ciudades dispuestas a comerciar.   @L@LOtras ciudades  @LLas ciudades que deseen comerciar aparecen en el mapa a todo color y ondean una bandera.  Las ciudades que no quieran comerciar con la tuya aparecen apagadas.  Para establecer una ruta comercial, haz clic en la ciudad con la que quieras hacer negocios.   @L@LImportación y exportación @LUna vez establecida una ruta comercial, aún tendrás que indicar al Supervisor de comercio qué recursos y mercancías deseas importar o exportar.  Nunca puedes importar y exportar el mismo artículo al mismo tiempo."
        }
    }

    message_tutorial_monuments {
        id: 283
        type: 2
        message_type: 4
        size [40, 30]
        title { text: "Monumentos" }
        content {
            text: "Con un suministro de ladrillos, ya estás listo para empezar la obra de la sagrada tumba mastaba.  La mayoría de los monumentos requieren tanto mano de obra cualificada como no cualificada.   @L@LGremios de construcción @LLos Gremios de construcción proporcionan la mano de obra cualificada necesaria para erigir monumentos.  La mastaba está hecha íntegramente de ladrillos y solo requiere Gremios de albañiles para construirla.  Puedes emplear tantos Gremios de albañiles como tu economía pueda sostener, pero asegúrate también de que se entreguen suficientes ladrillos en la obra para mantenerlos ocupados. @PUna vez que el Gremio de albañiles tenga mano de obra suficiente, enviará albañiles a la obra, donde esperarán la entrega de ladrillos por parte de los peones no cualificados. @L@LMano de obra campesina @LCuando haya algunos albañiles esperando suministros en el lugar del monumento, cuadrillas de peones empezarán a acarrear cargas de ladrillos hacia ellos.  Como esos mismos peones también deben cuidar los campos de la llanura aluvial, puede que observes que el trabajo en el monumento se ralentiza un poco cuando la crecida retrocede y los campesinos vuelven a sus campos.  Puedes construir Campamentos de trabajo adicionales, para que cualquier trabajador excedente que no sea necesario en los campos pueda trabajar en el monumento durante todo el año. @G75 @L@LEmpieza haciendo clic en el icono de Estructuras religiosas y, a continuación, busca un lugar adecuado donde colocar este gran edificio."
        }
    }
    
    message_the_finer_things {
        id: 284
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Las cosas más refinadas"
        }
        content {
            text: "Complejos de templos @LA medida que crece la devoción por sus dioses patronos, el pueblo egipcio exige lugares de culto cada vez más grandes.  La mayoría de las ciudades querrán erigir un Complejo de templos en honor a su dios elegido, para poder disfrutar plenamente de su benevolencia.  Una vez construido, el Complejo de templos puede ampliarse con la adición de un Oráculo y un Altar, cada uno dedicado a otros dioses menores.  Estos dioses también aportarán ciertos beneficios a la ciudad.   @L@LJoyería @LCon un suministro de piedras preciosas, los Joyeros de tu ciudad pueden fabricar joyas.  La joyería es un tipo de bien de lujo valioso que demandan las clases sociales más altas de la ciudad.  @L@LBienes de lujo @LAdemás de la joyería fabricada localmente, el pueblo egipcio aprecia ciertos otros bienes de lujo, que solo están disponibles mediante importación.  Una ciudad necesita acceso a más de un tipo de bien de lujo para llegar a ser verdaderamente civilizada.  @L@LExtracción de piedra @LPara extraer piedra, un material de construcción muy codiciado, construye una cantera junto a un afloramiento rocoso.  Los canteros entregarán bloques de piedra, uno a uno, al Patio de almacenamiento.  ¡Asegúrate de emplear arquitectos para que las canteras no se derrumben!"
        }
    }

    message_innovations {
        id: 285
        type: 2
        message_type: 4
        size [40, 30]
        title {
            text: "Innovaciones"
        }        
        content {
            text: "Agricultura de prados @LAlgunas tierras son lo bastante fértiles para la agricultura, aunque no se encuentren en la llanura aluvial.  Puedes identificar estas zonas de prado por su alto crecimiento de plantas amarillas.  Algunas granjas plantadas en prados pueden producir más de una cosecha al año, aunque el rendimiento suele ser algo menor que el de una granja de la llanura aluvial. @G59   @L@LRiego @LUtiliza el riego para aumentar la fertilidad de cualquier tierra de cultivo. Las acequias de riego en la llanura aluvial pueden conectarse directamente al Nilo, pero necesitarás una Noria para elevar el agua hasta la tierra seca.   @L@LNorias @LLas Norias pueden construirse en el borde de la llanura aluvial o en la costa, donde puedes elevar el agua directamente desde el río hasta la tierra seca. Conecta una acequia de riego a la parte trasera de la Noria para llevar agua de riego a las granjas del interior.  @L@LCanteros y carpinteros @LSerán necesarios dos nuevos tipos de Gremio de construcción para erigir la pirámide escalonada: el Gremio de canteros y el Gremio de carpinteros.  Los canteros del Gremio esperan en la obra a que lleguen bloques de piedra, transportados hasta allí por peones campesinos.  Estos transportistas de bloques necesitan rampas para alcanzar los niveles superiores de la estructura.  Cuando llegue el momento de que la pirámide escalonada se eleve otro nivel, un carpintero llevará madera desde el Gremio hasta la obra y construirá una rampa para los transportistas de bloques. @L@LConservación de los muertos @LCada ciudad necesita algunos embalsamadores para garantizar el saneamiento y ofrecer a sus habitantes más sofisticados los ritos funerarios adecuados. El Mortuorio utiliza lino, fabricado por un Tejedor, y presta servicios de embalsamamiento a las casas de los alrededores."
        }
    }

    message_troops_return_failed {
        id: 287
        type: 2
        
        size [30, 20]
        title { text: "La compañía regresa" }
        content { text: "Bajo el manto de la noche, los supervivientes de tu deshonrada compañía regresan a hurtadillas a la comodidad de los Fuertes de la ciudad, decididos a no volver a sufrir la humillación en la batalla." }
    }
    message_troops_return_victorious {
        id: 288
        type: 2
        
        size [30, 20]
        title {
            text: "¡Los héroes regresan!"
        }
        content {
            text: "Tus soldados victoriosos han vuelto a casa tras la guerra. Su número puede haber disminuido algo desde su partida, ¡pero el sacrificio de sus camaradas fue por el bien de Egipto! "
        }
    }
    message_city_retaken {
        id: 289,
        type: 2,
        
        size [30, 20]
        title { text: "Ciudad recuperada" }
    }
    message_osiris_is_upset {
        id: 290
        type: 2
        
        size [30, 20]
        title { text: "Osiris está furioso" }
        content { text: "¡El señor de la crecida del Nilo castigará a esta ciudad por su falta de devoción, y la crecida del próximo año destruirá todas las granjas que encuentre a su paso!" }
    }
    message_ra_is_upset_2 {
        id: 291
        type: 2
        
        size [30, 20]
        title { text: "Ra está furioso" }
        video { text: "@23" }
        content { text: "Enfadado por tu falta de respeto hacia él, Ra reduce tu propia reputación a los ojos del Reino." }
    }
    message_ptah_is_upset {
        id: 292
        type: 2
        
        size [30, 20]
        title { text: "Ptah está furioso" }
        video { text: "@22" }
        content { text: "Disgustado por tu desinterés hacia él, Ptah destruye uno de tus Patios de almacenamiento y todos los bienes que contenía." }
    }
    message_seth_is_upset {
        id: 293
        type: 2
        
        size [30, 20]
        title { text: "Seth está furioso" }
        video { text: "@21" }
        content { text: "Para recordarte que Seth solo protege a quienes muestran el respeto debido, el dios destruye tu mejor compañía de soldados y arrasa su Fuerte." }
    }
    message_bast_is_upset {
        id: 294
        type: 2
        
        size [30, 20]
        title { text: "Bastet está furiosa" }
        video { text: "@20" }
        content { text: "La diosa Bastet, herida por tu indiferencia, envía una plaga para acechar a tu ciudad. Recuerda que de ella fluyen la salud y la felicidad." }
    }
    message_blessing_from_osiris {
        id: 295
        type: 2
        
        size [30, 20]
        title { text: "Una bendición de Osiris" }
        video { text: "@24" }
        content { text: "Osiris, dios de la crecida del Nilo, bendice esta ciudad por su sincera devoción. ¡Todas las granjas de la llanura aluvial cosecharán el doble de lo esperado esta temporada!" }
    }
    message_construction_blessing {
        id: 1012
        type: 2

        size [30, 20]
        title { text: "Una bendición para la construcción" }
        content { text: "Los dioses se complacen con tu devoción y dan un gran impulso a tu monumento. Deja que tus trabajadores se aparten mientras se recibe esta bendición." }
    }
    message_construction_blessing_minor {
        id: 1013
        type: 2

        size [30, 20]
        title { text: "Una bendición para la construcción" }
        content { text: "Los dioses reconocen tu devoción ayudando a tu monumento. Deja que tus trabajadores descansen brevemente mientras llega este regalo." }
    }
    message_blessing_trade_from_ra {
        id: 296
        type: 2
        
        size [30, 20]
        title { text: "Una bendición de Ra" }
        video { text: "@23" }
        content { text: "¡Ra recompensa a sus fieles! Durante los próximos 12 meses, tu ciudad podrá vender sus exportaciones por la mitad más de su valor habitual." }
    }
    message_blessing_trade_from_ptah {
        id: 297
        type: 2
        
        size [30, 20]
        title { text: "Una bendición de Ptah" }
        video { text: "@22" }
        content { text: "Ptah elige un Patio de almacenamiento con capacidad excedente y aumenta las piedras preciosas, la arcilla, la cerámica, el lino en rama, el lino o la joyería que ya haya allí." }
    }
    message_blessing_trade_from_seth {
        id: 298
        type: 2
        
        size [30, 20]
        title { text: "Una bendición de Seth" }
        video { text: "@21" }
        content { text: "Seth aprueba tu temor y tu obediencia, así que golpeará a los próximos enemigos que se atrevan a violar tu ciudad." }
    }
    message_blessing_from_bast {
        id: 299,
        type: 2,
        
        size [30, 20]
        title { text: "Una bendición de Bastet" }
        video { text: "@20" }
        content { text: "¡Como esta ciudad es tan fiel y devota, Bastet bendice sus casas y bazares con una abundancia de comida y bienes!" }
    }
    message_the_gods_are_wrathful {
        id: 300
        type: 2
        
        size [30, 20]
        title { text: "Los dioses están airados" }
        content { text: "Al menos un dios está enfadado con la ciudad. Tu pueblo te suplica que construyas más Templos... y siempre agradecen también una festividad." }
    }
    message_illness {
        id: 301,
        type: 2,
        
        size [30, 20]
        title { text: "Dolencia" }
        video { text: "smk\\sick.smk" }
    }
    message_disease {
        id: 302,
        type: 2,
        
        size [30, 20]
        title { text: "Enfermedad" }
        video { text: "smk\\sick.smk" }
    }
    message_pestilence {
        id: 303,
        type: 2,
        
        size [30, 20]
        title { text: "Peste" }
        video { text: "smk\\sick.smk" }
    }
    message_the_spirit_of_seth {
        id: 304,
        type: 2,
        
        size [30, 20]
        title {
            text: "El espíritu de Seth",
        }
        video {
            text: "@21"
        }
        content {
            text: "Seth recuerda su promesa de protegerte y se complace en abatir a quienes fueron lo bastante necios para amenazar tu ciudad."
        }
    }
    message_the_emperors_respect {
        id: 305,
        type: 2,
        
        size [30, 20]
        title {
            text: "El respeto del Emperador",
        }
    }
    message_the_emperors_respect_1 {
        id: 306,
        type: 2,
        
        size [30, 20]
        title { text: "El respeto del Emperador" }
    }
    message_the_emperors_respect_2 {
        id: 307,
        type: 2,
        
        size [30, 20]
        title { text: "El respeto del Emperador" }
    }
    message_working_hippodrome {
        id: 308,
        type: 2,
        
        size [30, 20]
        title { text: "Hipódromo en funcionamiento" }
        video { text: "smk\\\\1st_chariot.smk" }
    }
    message_compliance_now_possible {
        id: 309,
        type: 2,
        message_type: 2,
        
        size [30, 20]
        title { text: "Cumplimiento ahora posible" }
        content { text: "Tu Supervisor político informa de que la ciudad ya dispone de debens  suficientes para cumplir la reciente petición." }
    }
    message_tutorial_finances {
        id: 310,
        type: 2,
        message_type: 4
        size [40, 30]
        title { text: "Finanzas" }
        content {
            text: "Impuestos @LUna gran ciudad necesita obtener ingresos adicionales, más allá de su financiación inicial.  Una forma de lograrlo es mediante impuestos.  Para recaudar impuestos, tu ciudad necesitará un Palacio y Recaudadores de impuestos.  Asegúrate de construir suficientes Recaudadores de impuestos para cubrir toda la ciudad, especialmente sus barrios más acomodados.  Recuerda que cuanta mejor calidad de vida disfrute un hogar, más impuestos pagarán sus ocupantes. @L@LTu salario personal @LSi construyes una Mansión para ti, podrás cobrar un salario personal del tesoro de la ciudad.  Los fondos personales los conserva tu familia, para usarlos cuando la situación lo exija, incluso en misiones posteriores.  Pero ten cuidado, porque asignarte un salario superior al que corresponde a tu cargo puede tener efectos perjudiciales en tu posición en el Reino."
        }
    }
    message_mission_defeat {
        id: 311,
        type: 2,
        
        size [30, 20]
        title { text: "¡Derrota!" }
        content { text: "¡Qué día tan amargo! Tu indigno final no debería haber sido posible. Has fallado a tu pueblo, a tus antepasados y a tus descendientes. Ahora Egipto anhela otro campeón que ocupe tu lugar..." }
    }
    message_mission_victory {
        id: 312,
        type: 2,
        
        size [30, 20]
        title { text: "El ganador" }
        video { text: "smk\\win_game.smk" }
        content { text: "Entrada no utilizada 312" }
    }
    message_enemy_rome_army_attacks {
        id: 313
        type: 2
        message_type: 7
        
        size [30, 20]
        title { text: "Ejército enemigo ataca" }
        video { text: "smk\\spy_army.smk" }
        content { text: " Los enemigos de Roma están a las afueras de su ciudad. Espere que se presenten para tomar un par de ánforas de vino, ¡y lo que se les antoje!" }
    }
    message_storage_yards_ready_to_fulfill_request {
        id: 314,
        type: 2,
        message_type: 2,
        
        size [30, 20]
        title {
            text: "Cumplimiento ya posible",
        }
        content {
            text: "Su Supervisor Político informa de que los Almacenes de la ciudad ya tienen suficientes de estos bienes para cumplir la reciente petición."
        }
    }
    message_kingdom_road_obstructed {
        id: 315,
        type: 2,
        
        size [30, 20]
        title {
            text: "Camino del reino obstruido",
        }
        content {
            text: "Los arquitectos tuvieron que demoler una construcción reciente para restablecer el paso libre por el @57Camino&del&reino."
        }
    }
    message_no_working_dock {
        id: 316,
        type: 2,
        
        size [30, 20]
        title { text: "No hay muelle en funcionamiento" }
        content { text: "Aunque ordenó a su Intendente de Comercio iniciar el comercio con un mercader marítimo, ¡el mercader no puede atracar en nuestra ciudad! Necesita construir un muelle y dotarlo de trabajadores. Una vez que tenga un muelle en funcionamiento, llegarán barcos y comenzarán a comerciar." }
    }
    message_fishing_boats_cant_navigate {
        id: 317,
        type: 2,
        
        size [30, 20]
        title { text: "Los barcos de pesca no pueden navegar" }
        content { text: "¡Nuestros pescadores informan de que un Puente bloquea su ruta! Los barcos no pueden navegar bajo los Puentes. Retire el Puente para que los barcos de pesca abastezcan a su ciudad de pescado fresco." }
    }
    message_health {
        id: 318,
        type: 3,
        
        size [30, 20]
        title {
            text: "Salud",
        }
        content {
            text: "A la gente le gusta estar sana. Si come bien y un médico de una clínica la visita con regularidad, debería gozar de buena salud. Si su salud empeora, tendrá más probabilidades de enfermar. @PLos hospitales son muy útiles cuando los ciudadanos enferman. Quien esté enfermo necesita un hospital que lo cure. Si no hay sitio en el hospital, morirá. @PAsí pues: las clínicas ayudan a prevenir enfermedades, mientras que los hospitales las curan. @L@LOcasionalmente puede desatarse una plaga, y se sabe que Bast envía enfermedades a las ciudades que la han ofendido. En esos momentos, una buena cobertura hospitalaria es la única defensa. Su Supervisor de Salud Pública le indicará si tiene o no una buena cobertura hospitalaria."
        }
    }
    message_messages_await_you {
        id: 319,
        type: 3,
        
        size [30, 20]
        title {
            text: "Hay mensajes esperándole",
        }
        content {
            text: "Cuando oiga una fanfarria, significa que su escriba ha recibido otro mensaje para usted y lo ha archivado. @L@LAlgunos mensajes, como este, aparecen abiertos automáticamente. Son asuntos muy urgentes que el escriba considera que debe ver de inmediato. Puede revisarlos más tarde, si lo desea, pulsando su botón de mensajes. @PLos mensajes importantes, pero no urgentes, se señalan con una fanfarria de importancia, aunque no aparecen automáticamente. La mayoría son mensajes normales con una fanfarria habitual, que puede consultar cuando le convenga. @L@LSu escriba guarda todos los mensajes para que pueda consultarlos cuando quiera. También puede eliminarlos si lo desea. Si desea más información, elija Ayuda en la barra de menús y pulse en 'Mensajes de sus escribas' (cerca del final del índice)."
        }
    }
    message_local_uprising {
        id: 320,
        message_type: 7
        
        size [30, 20]
        urgent: 1
        title { text: "Revuelta local" }
        content { text: "¡Inspirados por Seth, algunos habitantes han decidido expresar los numerosos agravios que llevan tiempo guardándole!!" }
    }
    message_small_blessing_from_osiris {
        id: 321
        type: 2
        
        size [30, 20]
        title { text: "Una pequeña bendición de Osiris" }
        video { text: "@24" }
        content { text: "Osiris ha observado la fiel dedicación de su ciudad. La próxima Inundación del Nilo será mejor de lo que se esperaba." }
    }
    message_minor_blessing_from_ra {
        id: 322
        type: 2
        
        size [30, 20]
        title { text: "Una pequeña bendición de Ra" }
        video { text: "@23"}
        content { text: "Animado por su debida reverencia, Ra eleva algo su reputación en todo el reino." }
    }
    message_minor_blessing_from_ptah {
        id: 323
        type: 2
        
        size [30, 20]
        title { text: "Una pequeña bendición de Ptah" }
        video { text: "@22" }
        content { text: "Ptah está complacido con su atención, así que se asegura de que los Constructores de barcos, Tejedores o Joyeros de su ciudad dispongan de materias primas en abundancia." }
    }
    message_minor_blessing_from_seth {
        id: 324
        type: 2
        
        title { text: "Una pequeña bendición de Seth" }
        video { text: "@21" }
        content { text: "Para recompensar su obediencia, Seth jura proteger a cualquiera de sus soldados enviados a combatir a tierras lejanas." }
    }
    message_small_blessing_from_bast {
        id: 325
        type: 2
        
        size [30, 20]
        title { text: "Una pequeña bendición de Bast" }
        video { text: "@20" }
        content { text: "Bast está complacida de que su ciudad la honre. Ha organizado una fiesta para que todos los dioses adviertan su devoción." }
    }
    message_disease_strikes {
        id: 326,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Brota una enfermedad",
        }
        content {
            text: "La enfermedad ha golpeado un hogar con escaso acceso a la sanidad.  La gente muere y usted no puede ayudarla.  Mejore las zonas insalubres para evitar que se repita."
        }
    }
    message_a_plague {
        id: 327,
        type: 2,
        message_type: 1,
        
        size [30, 20]
        title {
            text: "Una plaga",
        }
        content {
            text: "¡La plaga azota la ciudad!  Temíamos que ocurriera, dada la pésima @53salud&urbana general.  Recemos para que nuestros boticarios puedan con ella."
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
            text: "Algunos hogares han contraído malaria.  ¡Unas mejores medidas sanitarias podrían evitar esta pérdida innecesaria de vidas humanas!"
        }
    }
    message_blessing_reputation_from_ra {
        id: 329,
        type: 2,
        
        size [30, 20]
        title { text: "Una bendición de Ra" }
        video { text: "@23" }
        content {
            text: "¡Ha honrado a Ra, así que su reputación en todo el reino es mucho mejor que antes!"
        }
    }
    message_minor_blessing_trading_from_ra {
        id: 331,
        type: 2,
        
        size [30, 20]
        title { text: "Una pequeña bendición de Ra" }
        video { text: "@23" }
        content { text: "Para reconocer su actitud respetuosa, Ra anima a sus socios comerciales a comerciar más que antes." }
    }
    message_wrath_of_ra_2 {
        id: 332,
        type: 2,
        
        size [30, 20]
        title { text: "La ira de Ra" }
        video { text: "@23" }
        content { text: "¡Ha provocado la cólera de Ra! El dios ha reducido la estima de los bienes de su ciudad, y sus socios comerciales comerciarán ahora mucho menos que antes." }
    }
    message_wrath_of_ra_3 {
        id: 333,
        type: 2,
        
        size [30, 20]
        title { text: "La ira de Ra" }
        video { text: "@23" }
        content { text: "Como usted ha abandonado a Ra, sus socios comerciales le abandonarán a usted. Ningún barco comercial ni caravana visitará su ciudad durante un año completo." }
    }
    message_ra_is_upset {
        id: 334,
        type: 2,
        
        size [30, 20]
        image { id: 224, pos [15, 15] }
        title { text: "¡Ra está disgustado!" }
        video { text: "@23" }
        content { text: "Como ha despreciado a Ra, sus socios comerciales despreciarán los bienes de su ciudad. Han decidido reducir la cantidad que están dispuestos a comerciar con usted." }
    }
    message_wrath_of_bast_2 {
        id: 335,
        type: 2,

        size [30, 20]
        title { text: "La ira de Bast", }
        content { text: "Su ciudad escapó de la ira de Bast: la diosa quiso arrasar sus mejores casas, pero no encontró hogares dignos de su furia en este día. Sea prudente, no obstante, al provocar a la Diosa del Hogar, pues es paciente y tiene buena memoria. Muestre a Bast el respeto que exige antes de que regrese." }
    }
    message_wrath_of_ra_4 {
        id: 336,
        type: 2,
        
        size [30, 20]
        title {
            text: "La ira de Ra",
        }
        content {
            text: "¡Ra se encargará de que sea castigado por su falta de respeto!"
        }
    }
    message_wrath_of_osiris_3 {
        id: 337,
        type: 2,
        
        size [30, 20]
        title {
            text: "La ira de Osiris",
        }
        video {
            text: "@24"
        }
        content {
            text: "Osiris está indignado, aunque es impotente para castigar a su ciudad.  Disfrute de esto mientras pueda, pues su ciudad quizá no tenga tanta suerte la próxima vez."
        }
    }
    message_blessing_inundation_from_osiris {
        id: 340,
        type: 2,
        
        size [30, 28]
        title { text: "Osiris le bendice" }
        video { text: "@24" }
        content { text: "Osiris recompensa a quienes le rinden culto. La próxima Inundación será mucho mejor de lo que esperábamos." }
    }
    message_wrath_of_osiris_4 {
        id: 341,
        type: 2,
        
        size [30, 20]
        title { text: "La ira de Osiris" }
        video { text: "@24" }
        content { text: "Osiris le recuerda que se le debe respeto. La próxima Inundación será peor de lo que esperábamos." }
    }
    message_mediocre_inundation_seers {
        id: 342,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "Nuestros videntes advierten de que la Inundación del próximo año será, en el mejor de los casos, mediocre." }
    }
    message_poor_inundation_seers {
        id: 343,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "Los sacerdotes esperan una mala Inundación el próximo año." }
    }
    message_no_inundation {
        id: 344,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "¡Malas noticias! ¡Todos los presagios indican que este año no habrá Inundación alguna!" }
    }
    message_poor_inundation {   
        id: 345,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "Los sacerdotes predicen una mala Inundación para el próximo año. Su pueblo le suplica que se asegure de apaciguar a Osiris y reza por mejores crecidas en los años venideros." }
    }
    message_mediocre_inundation {
        id: 346,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "Esperamos que la próxima Inundación sea, en el mejor de los casos, mediocre. Quizá Osiris nos conceda su benevolencia si nos aseguramos de apaciguarlo." }
    }
    message_good_inundation {
        id: 347,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "Todos los augurios apuntan a una buena Inundación el próximo año." }
    }
    message_excellent_inundation {
        id: 348,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "¡Los agricultores están encantados con las predicciones de una excelente Inundación el próximo año!" }
    }
    message_perfect_inundation {
        id: 349,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title { text: "Predicción del nilómetro" }
        content { text: "¡Los sacerdotes predicen que la ciudad será bendecida con una Inundación perfecta el próximo año!" }
    }
    message_temple_complex_to_osiris {
        id: 350,
        
        size [30, 20]
        title {
            text: "Complejo de templos a Osiris",
        }
        subtitle {
            text: "Religión",
        }
        content {
            text: "Cuando construya un Complejo de templos para Osiris, el dios tenderá a enviar mejores crecidas de año en año. Puede construir las siguientes adiciones al Complejo de templos de Osiris: @L@LAltar de Sebek, Dios de la fertilidad @LSebek concede a los sacerdotes de Osiris el poder de estirar las reservas de alimentos y bienes de la ciudad.  Cuando los sacerdotes de Osiris pasan por su ciudad, la gente de las casas por las que pasan se conforma de repente con menos. @L@LOráculo de Min, Dios de la regeneración @LCuando su ciudad honra a Min con un Oráculo, acelera el rebrote de árboles y juncos, aumenta la tasa de reproducción de los animales presa y mejora el rendimiento de la pesca y la caza. @L@LA la gente le encanta vivir junto a un Complejo de templos. Para saber más sobre la religión, pulse @51aquí. @L@LConozca a Osiris, Sebek y Min en el antiguo Egipto pulsando @376aquí."
        }
    }
    message_temple_complex_to_ra {
        id: 351,
        
        size [30, 20]
        title {
            text: "Complejo de templos a Ra",
        }
        content {
            text: "Ra sonríe a la ciudad cuando le ha dedicado un Complejo de templos, y se asegura de que los demás del reino también sonrían a su ciudad.  Construir un Complejo de templos para Ra aumenta su calificación en el reino y, si la ciudad se encuentra endeudada, le permite pagar un tipo de interés más bajo.  Construir un Altar y un Oráculo en el Complejo de templos de Ra le ayuda a gestionar los asuntos de la ciudad: @L@LAltar de Ma'at, Diosa de la justicia @LA través de los sacerdotes de Ra, Ma'at concede un efecto calmante a su ciudad.  Al pasar junto a las casas, los sacerdotes de Ra disuaden a los residentes de robar.  La sola presencia del Altar reduce el riesgo general de que estallen delitos en la ciudad. @L@LOráculo de Horus, Dios de los faraones @LEste Oráculo aumenta la dedicación de los ciudadanos a su ciudad y al reino, animándolos a aceptar un salario más bajo sin que ello afecte a su ánimo. @L@LA la gente le encanta vivir junto a un Complejo de templos. Para saber más sobre la religión, pulse @51aquí. @L@LConozca a Ra, Ma'at y Horus en el antiguo Egipto pulsando @377aquí."
        }
    }
    message_temple_complex_to_ptah {
        id: 352,
        
        size [30, 20]
        title {
            text: "Complejo de templos a Ptah",
        }
        content {
            text: "Cuando le construya un Complejo de templos, Ptah acelera la producción de muchas de las industrias de su ciudad, incluidas las Minas de oro, las Minas de cobre, las Minas de piedras preciosas, los Pozos de arcilla, los Constructores de barcos, los Joyeros y los Tejedores.  El Altar y el Oráculo del Complejo de templos de Ptah aceleran la producción de otras industrias y mejoran la capacidad de los educadores: @L@LAltar de Amón, Dios del sol @LHonrado por su atención, Amón acelera el trabajo de las canteras, los Leñadores y las Ladrilleras. @L@LOráculo de Thoth, Dios de la sabiduría y el saber @LThoth quiere llevar la luz del saber al mayor número de personas posible.  Cuando construye un Oráculo de Thoth, los bibliotecarios y maestros usan menos papiro para educar a los habitantes de la ciudad. @L@LA la gente le encanta vivir junto a un Complejo de templos. Para saber más sobre la religión, pulse @51aquí. @L@LConozca a Ptah, Amón y Thoth en el antiguo Egipto pulsando @378aquí."
        }        
    }
    message_temple_complex_to_seth {
        id: 353,
        
        size [30, 20]
        title { text: "Complejo de templos a Seth" }
        content { text: "Cuando una ciudad tiene un Complejo de templos dedicado a él, Seth infunde una voluntad feroz en los soldados de la ciudad, concediéndoles más experiencia y protegiéndolos en la batalla.  Las adiciones al Complejo de templos de Seth son:  @L@LAltar de Anubis, Dios de la muerte @LAnubis facilita a los ciudadanos el acceso a la vida eterna.  Con su bendición, las Funerarias necesitan menos lino para preparar los cuerpos para la eternidad.   @L@LOráculo de Sekhmet, Diosa de la guerra @LSekhmet concede a los sacerdotes de Seth el poder de reducir el riesgo de delitos en las casas por las que pasan y de capturar a los criminales de la ciudad.  @L@LA la gente le encanta vivir junto a un Complejo de templos. Para saber más sobre la religión, pulse @51aquí. @L@LConozca a Seth, Anubis y Sekhmet en el antiguo Egipto pulsando @379aquí." }
    }
    message_temple_complex_to_bast {
        id: 354,
        
        size [30, 20]
        title { text: "Complejo de templos a Bast" }
        content { text: "Construir un Templo a Bast trae buena fortuna a cualquier ciudad.  Bast ayuda a mantener felices a los ciudadanos haciendo que se conformen con menos.  Gracias a su benevolencia, la tasa a la que los ciudadanos consumen alimentos y bienes se reduce, y los efectos de los artistas, educadores y proveedores de salud duran más.  Sus diosas hermanas también mejoran la vida de sus ciudadanos: @L@LAltar de Isis, Diosa de la curación @LA través de las sacerdotisas de Bast, Isis impone sus manos sanadoras sobre la población de la ciudad, retirando de las calles a los transeúntes afectados por la plaga y purificando las casas infectadas por las que pasan las sacerdotisas.  Isis también se ocupa de mejorar la salud general de su ciudad. @L@LOráculo de Hathor, Diosa de la alegría, el amor y la fiesta @LHathor, halagada por el Oráculo que usted le ha construido, mejorará el ánimo de los ciudadanos, lo que se traducirá en un mejor @39Sentimiento&de&la&ciudad. @L@LA la gente le encanta vivir junto a un Complejo de templos. Para saber más sobre la religión, pulse @51aquí. @L@LConozca a Bast, Isis y Hathor en el antiguo Egipto pulsando @380aquí." }
    }
    message_building_firehouse {
        id: 355,
        
        size [30, 20]
        title {
            text: "Cuartel de bomberos",
        }
        content {
            text: "Algunos edificios de la ciudad pueden incendiarse. Los candidatos más probables son las viviendas deterioradas y los edificios industriales, como los Alfareros.  Si no hace nada para evitarlo, el fuego puede extenderse por la ciudad y destruir secciones enteras de una vez. Para prevenirlo, construya Cuarteles de bomberos cerca de los edificios que tengan más probabilidades de incendiarse. Los jefes de bomberos de los Cuarteles recorren la ciudad (pulse @42aquí para más información sobre los transeúntes) y reducen el riesgo de incendio de los edificios por los que pasan. @PSi se declara un incendio, los jefes de bomberos cercanos acuden al lugar para apagar las llamas. Si un jefe de bomberos tiene que recorrer una gran distancia, las llamas podrían extenderse y la destrucción en su ciudad podría ser muy grave. @G67 @PEl @18mapa&de&incendios es una guía útil para la prevención de incendios. El mapa muestra a los jefes de bomberos en acción, pero, sobre todo, señala qué edificios son especialmente propensos a incendiarse. Utilice esta información para planificar la ubicación de su próximo Cuartel de bomberos. @PLos Cuarteles de bomberos necesitan acceso por carretera y mano de obra para funcionar. A los residentes no les gusta vivir cerca de los Cuarteles de bomberos."
        }
    }
    message_building_warship_wharf {
        id: 356,
        
        size [30, 20]
        title {
            text: "Muelle de guerra",
        }
        content {
            text: "Los Muelles de guerra dan amarre a los barcos de guerra. Lo primero que hace un nuevo Muelle de guerra es encargar un barco de guerra al @82Constructor&de&barcos. @PUn Muelle de guerra necesita acceso por carretera y mano de obra. Además, debe estar en un tramo recto de costa, y los barcos deben poder llegar fácilmente al Muelle. Los ciudadanos no querrán vivir demasiado cerca de un Muelle de guerra. Después de todo, algunos marineros no tienen la mejor reputación. @PCuando un barco de guerra no está combatiendo, su tripulación prefiere regresar a la seguridad del muelle. Allí puede descansar para la siguiente batalla. @PLea la entrada sobre los @365barcos de guerra para saber cómo maniobrar un barco en combate. @L@LLa tradición militar del antiguo Egipto es larga y legendaria. Pulse @184aquí para saber más."
        }
    }
    message_building_transport_wharf {
        id: 357,
        
        size [30, 20]
        title {
            text: "Muelle de transporte",
        }
        content {
            text: "Los muelles de transporte atracan los barcos de transporte. Lo primero que hace un muelle de transporte recién construido es encargar un barco de transporte a un @82Constructor&de&barcos.  @PEl muelle de transporte requiere acceso por carretera y mano de obra. Además, debe situarse en un tramo recto de costa, y los barcos deben poder llegar al muelle con facilidad. Sus ciudadanos no querrán vivir demasiado cerca de un muelle de transporte.  @PLea la entrada sobre los @367barcos de transporte para saber cómo maniobrar un barco en combate. @L@LLa tradición militar del antiguo Egipto es larga e ilustre.  Haga clic @181aquí para saber más."
        }
    }
    message_building_roadblock {
        id: 358,
        
        size [30, 20]
        title {
            text: "Bloqueo de carretera",
        }
        content {
            text: "Los bloqueos de carretera le permiten controlar las rutas que siguen los @42viandantes&errantes.  Cuando los viandantes que deambulan por la ciudad se encuentran con un bloqueo, dan media vuelta.  Los bloqueos no afectan a los viandantes con destino fijo.   @PConstruya un bloqueo en cualquier lugar al que sus viandantes errantes no necesiten ir; por ejemplo, en el camino hacia sus zonas industriales.  Sin embargo, tenga cuidado de no aislar por completo ninguna zona de los viandantes errantes.  El mismo bloqueo que impide que un comerciante del Bazar se adentre en el sector industrial también hace retroceder a arquitectos, bomberos y alguaciles.  Además, impide que los reclutadores de mano de obra vayan desde la zona industrial hasta su sector residencial, donde encuentran empleados. @G62 @PCuando levante un bloqueo nuevo cerca de un edificio existente, quizá le convenga observar el edificio un momento para asegurarse de que su viandante sale por el lado correcto del bloqueo.  A veces, los empleados del edificio no entienden sus intenciones y envían a su viandante en la dirección equivocada.  Esto puede resultar especialmente irritante con los buscadores de acceso a mano de obra, porque el edificio que los emplea cree que tiene acceso a mano de obra, pero el bloqueo impide que el viandante llegue nunca a la reserva de trabajadores.  Su única solución es reconstruir el bloqueo un poco más lejos. @PLos bloqueos no necesitan empleados, y su única restricción es que deben colocarse sobre carreteras. No tienen ningún efecto sobre el atractivo."
        }
    }
    message_building_hunting_lodge {
        id: 359,
        
        size [30, 20]
        title {
            text: "Refugio de caza",
        }
        content {
            text: "Construya un Refugio de caza para enviar cazadores tras sus presas. Se pueden cazar avestruces, aves de corral y antílopes. @PPuede construir refugios de caza en cualquier lugar, aunque conviene situarlos cerca de sus presas, que suelen permanecer junto a sus zonas de cría.  Los refugios de caza necesitan mano de obra y acceso por carretera para funcionar. Cuando estén en marcha, verá a un cazador en el patio practicando el tiro al blanco. @PLos cazadores salen del refugio hacia los campos, donde les aguardan sus presas. Tras abatirlas, traen los animales de vuelta al refugio, donde se preparan para el consumo. Cuando hay una carreta de carne de caza lista, se lleva a los @3Graneros o a los @4Patios&de&almacenamiento (si se les ha indicado que acepten carne de caza). @G60 @PLa carne de caza puede ser una parte importante de la dieta de los ciudadanos. Aporta la variedad que la gente desea. Sin embargo, lo más probable es que la ciudad no pueda subsistir solo de carne de caza. El tamaño de los rebaños y las manadas es limitado, así que la caza por sí sola no puede proporcionar toda la comida que necesita una gran ciudad. Para saber más sobre cómo alimentar a su pueblo, lea sobre la @45agricultura&y&producción&de&alimentos. @PLa carne de caza (junto con la @89paja) también se utiliza para alimentar a los animales de un @479Zoo.  @PLos refugios de caza tienen un efecto negativo sobre el @56atractivo. @L@LLa carne de caza complementaba la dieta del antiguo Egipto. Además, la caza era un deporte apreciado por la élite.  Haga clic @383aquí para saber más."
        }
    }
    message_building_cattle_ranch {
        id: 360,
        
        size [30, 20]
        title {
            text: "Rancho de ganado",
        }
        content {
            text: "Críe ganado en un Rancho de ganado para proporcionar carne a los habitantes de la ciudad. @PLos ranchos de ganado deben situarse junto a una carretera y necesitan mano de obra. También necesitan paja, ya sea de una @89Granja&de&cereales o importada de un @47socio&comercial. Los ranchos de ganado no necesitan construirse en tierra fértil, ni tampoco acceso al agua. @PLea sobre la @45agricultura&y&producción&de&alimentos para saber más sobre el papel de la carne en la dieta de sus ciudadanos. @PLos ranchos de ganado apestan, y a los ciudadanos no les gusta vivir cerca. @L@LLos antiguos egipcios criaban muchos animales para alimentarse.  Haga clic @186aquí para saber más."
        }
    }
    message_building_gemstone_mine {
        id: 361,
        
        size [30, 20]
        title {
            text: "Mina de gemas",
        }
        content {
            text: "Las gemas se extraen de los afloramientos rocosos. No se puede saber a simple vista si una roca puede producir gemas. Si hay gemas que extraer, las Minas de gemas aparecerán en la lista de Estructuras industriales: materias primas. Al igual que las @95canteras, las Minas de gemas deben situarse junto a afloramientos rocosos, y necesitan trabajadores y acceso por carretera.  También son propensas a derrumbarse, así que asegúrese de construir cerca un @81Puesto&del&arquitecto. @PLas minas de gemas son lugares polvorientos, y los ciudadanos no quieren vivir cerca. @L@LLea más sobre las gemas en el antiguo Egipto haciendo clic @382aquí."
        }
    }
    message_building_sphinx {
        id: 362,
        
        size [30, 20]
        title {
            text: "Esfinge",
        }
        content {
            text: "La Esfinge es un protector de las pirámides, elaboradamente tallado y pintado. @PPara construir una Esfinge, primero debe encontrar una ubicación.  Elija 'Esfinge' en la lista de Estructuras religiosas: monumentos.  Aparecerá la huella de la esfinge.  Al mover esta huella por el paisaje, se mostrará toda en verde o en verde con uno o más rombos rojos.  Cuando la huella esté completamente en verde, habrá encontrado un yacimiento de piedra oculto adecuado.  Haga clic con el botón del ratón y la piedra quedará al descubierto.  Si aparece algún rombo rojo en la huella, algún defecto del terreno impide construir la Esfinge aquí.   @PAhora, los @363canteros y los @363carpinteros pueden ponerse a trabajar, siempre que tenga la madera necesaria.  Los carpinteros construyen andamios por los que suben los canteros para tallar la Esfinge. @PHaga clic con el botón derecho sobre la Esfinge para visitar al @369Capataz&de&obras y recibir un informe de progreso. @L@LHaga clic @391aquí para leer sobre la Esfinge más famosa."
        }
    }
    message_construction_guilds {
        id: 363,
        
        size [30, 20]
        title {
            text: "Gremios de construcción",
        }
        content {
            text: "Sin los Gremios de construcción no podrá levantar las magníficas estructuras que honran al faraón y a Egipto. @PHay cuatro Gremios de construcción especializados: el de carpinteros, el de albañiles, el de canteros y el de artesanos. Aunque los obreros comunes de los @8Campamentos&de&trabajo aportan la mayor parte de la fuerza física de un proyecto monumental, los gremios expertos convierten montones de materias primas en las edificaciones más grandes y complejas que construirá, como las pirámides, la @362Esfinge, las @371mastabas, el @69Templo&del&Sol, los @368mausoleos y los @392obeliscos. Cada monumento requiere sus propios trabajadores de gremio. @PLos gremios de construcción deben tener acceso por carretera y una fuente local de mano de obra. Los gremios de carpinteros deben tener madera disponible. Los gremios de artesanos necesitan un suministro de @470pintura y @92arcilla (para el enlucido) con el que dar los toques finales a las tumbas. Los albañiles y los canteros esperan en el lugar del monumento a que lleguen los materiales que necesitan. @PDebido al ruido, a sus ciudadanos no les gusta vivir cerca de los gremios de construcción. @L@LPara saber más sobre estos oficios especializados en el antiguo Egipto, lea las entradas sobre los @386albañiles, @385canteros, @389carpinteros y @472artesanos."
        }
    }
    message_building_brickworks {
        id: 364,
        
        size [30, 20]
        title {
            text: "Ladrillera",
        }
        content {
            text: "Las ladrilleras convierten la @92arcilla y la @89paja en ladrillos.  Los ladrillos se usan en la construcción de varios tipos de monumentos y también pueden @47exportarse para obtener beneficios. @PUna vez que una ladrillera tiene mano de obra y acceso por carretera, necesita un suministro de materias primas para funcionar. Las ladrilleras necesitan tanto paja como arcilla. La paja se produce en las @89Granjas&de&cereales y la arcilla se extrae del suelo en los @92Yacimientos&de&arcilla. Ambas materias primas también pueden importarse de un @47socio&comercial.  @PCuando una ladrillera está produciendo ladrillos, puede ver a los fabricantes trabajando en su patio. Cuando se produce una carga de ladrillos, estos se entregan a un @4Patio&de&almacenamiento. @PLas ladrilleras son @56vecinos&indeseables. @L@LHaga clic @390aquí para saber más sobre los ladrillos en el antiguo Egipto."
        }
    }
    message_building_warship {
        id: 365,
        
        size [30, 20]
        title {
            text: "Barco de guerra",
        }
        content {
            text: "Los barcos de guerra patrullan las vías fluviales, embistiendo o disparando contra otros barcos que intenten causar daño a la ciudad.  Los barcos de guerra también pueden atacar con proyectiles a los soldados en tierra, siempre que estén cerca de la costa. Un barco de guerra atraca en un @356Muelle&de&guerra.  Puede distinguirlo de un barco de transporte por la ausencia de camarote en la popa y por su estilo de acabado. @L@LPrioridades de ataque @LSin importar qué orden le dé a un barco de guerra, su capitán siempre sigue la misma agenda al atacar al enemigo. Por orden de importancia, las prioridades del capitán son: @L@LBarcos de transporte con soldados enemigos a bordo  @LEl capitán sabe que su misión habrá fracasado en gran medida si los soldados enemigos llegan a tierra.  Si hay barcos de transporte con soldados enemigos en las aguas de la ciudad, los ataca primero, antes de que puedan desembarcar a sus invasores. @L@LEnemigos desembarcados cerca de la orilla  @LSi el capitán no logra impedir que los soldados enemigos desembarquen, navega cerca de la orilla y lanza flechas sobre los invasores desembarcados que estén a su alcance. @L@LBarcos de guerra  @LLos barcos de guerra enemigos son su tercera prioridad.  Si no hay barcos de transporte con tropas a bordo ni enemigos desembarcados, el capitán intenta embestir a los barcos de guerra enemigos que haya. @L@LBarcos de transporte enemigos vacíos  @LLos barcos de transporte enemigos vacíos son la última prioridad de su capitán.  Los atacará si no hay nada más que atacar. @L@LSu capitán reacciona con rapidez ante los cambios de situación.  Abandonará un combate si surge una situación de mayor prioridad.  Por ejemplo, si está atacando a un barco de guerra cuando un barco de transporte cargado de soldados enemigos entra en la zona que protege, abandonará al barco de guerra y atacará el transporte cargado. @L@LÓrdenes del barco de guerra @LDé órdenes a un barco de guerra haciendo clic con el botón derecho sobre él.  Los barcos de guerra pueden cumplir las siguientes órdenes: @L@LMantener posición   @LCuando se le ordena Mantener posición, el barco de guerra no se moverá del lugar que usted indique.  Se defiende girándose para enfrentarse a los barcos de guerra enemigos y así reducir el daño de sus embestidas, y ataca a los enemigos que estén a su alcance disparando flechas.  Si varios barcos de guerra se alinean y todos han recibido la orden de Mantener posición, forman un bloqueo con el objetivo de impedir la entrada de invasores.   @L@LAtacar a los enemigos cercanos   @LCuando se le ordena Atacar a los enemigos cercanos, el barco de guerra ataca a los enemigos que estén en un pequeño radio alrededor de su posición.   @L@LBuscar y destruir a todos los enemigos   @LCuando recibe esta orden, el barco de guerra patrulla las aguas en busca de enemigos a los que derrotar.   @L@LReparar   @LSi el barco de guerra resulta dañado en un conflicto, al pulsar este botón se envía el barco al Constructor de barcos para las reparaciones necesarias.  Cuando el Constructor de barcos termine de repararlo, regresará a su muelle de origen.  Si el barco de guerra está muy dañado, su capitán lo enviará por su cuenta al Constructor de barcos.  Los constructores de barcos necesitan madera para realizar las reparaciones.   @L@LVolver al muelle   @LAl hacer clic en esta opción, el barco regresa a su muelle de origen. @L@LPara ordenar a un barco de guerra que se mueva, basta con hacer clic sobre él y luego en una nueva ubicación.  Cuando llegue al nuevo lugar, seguirá la última orden recibida.  Si hace clic sobre un enemigo, el barco de guerra perseguirá al enemigo elegido hasta que sea derrotado o, si es un objetivo terrestre, hasta que quede fuera de su alcance. @L@LHaga clic @184aquí para leer sobre el combate en el antiguo Egipto."
        }
    }
    message_building_festival_square {
        id: 366,
        
        size [30, 20]
        title {
            text: "Plaza de festivales",
        }
        content {
            text: "Antes de celebrar un festival (consulte @51religión para más información sobre los festivales), debe tener una Plaza de festivales en su ciudad.  La Plaza de festivales debe construirse sobre un cruce, pero no requiere mano de obra.  Cada ciudad solo puede tener una Plaza de festivales, y resulta un vecino muy @56atractivo.   @PCuando no hay ningún festival en curso, la plaza está casi desierta, aunque no afecta al tráfico de las carreteras sobre las que se construyó.  Cuando comienza el festival, la gente acude aquí desde todos los rincones de la ciudad para disfrutar de la fiesta.   @PLos antiguos egipcios celebraban festivales para conmemorar muchos acontecimientos distintos.  Haga clic @393aquí para saber más."
        }
    }
    message_figure_transport_ship {
        id: 367,
        
        size [30, 20]
        title {
            text: "Barco de transporte",
        }
        subtitle {
            text: "Barco de transporte",
        }
        content {
            text: "Los barcos de transporte llevan a su ejército a través del río o por mar hasta tierras lejanas.  Cualquier compañía puede embarcar en un barco de transporte, pero este solo puede llevar una compañía a la vez. Un barco de transporte atraca en un @357Muelle&de&transporte.  Puede distinguirlo de un barco de guerra por su camarote en la popa y por su estilo de acabado. @L@LÓrdenes del barco de transporte Puede dar órdenes específicas a los barcos de transporte.  Para mover un barco de transporte de un lugar a otro, haga clic sobre él y luego en una nueva ubicación.  Haga clic con el botón derecho sobre el transporte para dar cualquiera de las siguientes órdenes: @L@LMantener posición   @LOrdena al barco de transporte que se quede donde está.  Si el barco sufre un ataque, el capitán lo girará para intentar reducir el daño.  Sin embargo, no zarpará para evitar el ataque.  Esta opción debe usarse con precaución, porque los barcos de transporte no están bien equipados para defenderse.   @L@LEvitar enemigos   @LLos barcos de transporte, especialmente los cargados con sus soldados, son valiosos y vulnerables.  Haga clic en Evitar enemigos para que el capitán del barco de transporte use todos sus recursos para evitar el ataque.  El capitán siempre intenta evitar a los enemigos, salvo que usted le ordene lo contrario.   @L@LEmbarcar/Desembarcar   @LPara cargar una compañía de soldados en el barco de transporte, primero haga clic en el botón Embarcar y luego en la compañía de soldados que desea trasladar por el agua.  Los soldados subirán al barco de transporte, y la nave mostrará el estandarte de la compañía.  Si hace clic con el botón derecho sobre el barco de transporte, se mostrará información sobre la compañía a bordo. @PPara devolver a los soldados a tierra, haga clic en Desembarcar y luego mueva el cursor a la ubicación donde desea acuartelar la compañía. @PLa opción Embarcar/Desembarcar alterna entre ambas según haya soldados a bordo del barco de transporte en ese momento.   @L@LReparar   @LSi el barco de transporte está dañado, haga clic en Reparar para enviar la nave al @82Constructor&de&barcos. El capitán llevará el barco al Constructor por su cuenta si el casco está muy dañado.  Los constructores de barcos necesitan madera para realizar las reparaciones.   @L@LVolver al muelle   @LHaga clic en este botón para enviar el barco de transporte de vuelta a su @357muelle."
        }
    }
    message_building_mausoleum {
        id: 368,
        
        size [30, 20]
        title {
            text: "Mausoleo",
        }
        content {
            text: "Los mausoleos son grandes tumbas utilizadas para enterrar a faraones y nobles.   @PPara construir un Mausoleo se necesitan suministros de arenisca y madera, además de al menos un @363Gremio&de&carpinteros, un @363Gremio&de&canteros y un @8Campamento&de&trabajo en funcionamiento. @PPara situar un Mausoleo, primero debe haber una gran cantidad de arenisca almacenada en los @4Patios&de&almacenamiento de la ciudad.  Cuando haya suficiente piedra almacenada, elija Mausoleo en la lista de Estructuras religiosas: monumentos.  Coloque el Mausoleo usando el color de la huella como guía (todo en verde significa que puede colocar la estructura; los rombos rojos indican que algún rasgo del terreno impide construir allí).  Una vez elegido el lugar del edificio, los campesinos del Campamento de trabajo despejan el terreno y levantan los cimientos. @PUna vez puestos los cimientos, los canteros empiezan a trabajar.  Cada vez que un Patio de almacenamiento acumula cuatro bloques de arenisca, los campesinos cargan la piedra en un trineo y la arrastran hasta la obra.  Los canteros colocan la piedra hasta completar la primera planta.  Después, los carpinteros instalan rampas de madera para que los canteros puedan trabajar en la segunda planta del Mausoleo.  Cuando la segunda planta está terminada, el Mausoleo queda concluido. @L@LLea sobre la historia de estas tumbas haciendo clic @396aquí."
        }
    }
    message_figure_construction_foreman {
        id: 369,
        
        size [30, 20]
        title {
            text: "Capataz de obras",
        }
        content {
            text: "Una vez iniciada la construcción de un monumento, el Capataz de obras proporciona información detallada sobre su estado.  Lleva un recuento continuo de cuánto de cada material de construcción se necesita para completar el monumento.  Si la construcción no avanza con normalidad, puede explicarle el motivo.  Para visitar al Capataz de obras, haga clic con el botón derecho sobre el lugar del monumento."
        }
    }
    message_building_monument_construction {
        id: 370,
        
        size [30, 20]
        title {
            text: "Construcción de monumentos",
        }
        content {
            text: "Para completar con éxito la mayoría de las misiones, deberá construir al menos un monumento.  Algunas misiones le exigirán construir varios.  Puede construir los monumentos necesarios en el orden que prefiera. @PPara la mayoría de los monumentos, los trabajadores de los @363Gremios&de&construcción esperan en el lugar del monumento a que los campesinos de un @8Campamento&de&trabajo les traigan los suministros necesarios desde un @4Patio&de&almacenamiento.  Los campesinos caminarán lo que haga falta para llegar al lugar del monumento.  La @362Esfinge y el @372Obelisco se construyen de forma algo diferente. @G75 @PLos trabajadores de la ciudad pueden trabajar en más de un monumento a la vez, y puede sentir la tentación de ordenárselo.  Sin embargo, le advierto que ese plan puede no ser tan acertado como parece.  La ineficiencia aparece cuando los @363canteros y los transportistas de bloques no coordinan su trabajo.  Los campesinos pueden llevar los materiales de construcción a un monumento mientras los canteros esperan ociosos en el lugar donde preferirían trabajar.   @PEsta situación frustra profundamente al @373Supervisor&de&monumentos, pero es más difícil de lo que parece conciliar las órdenes rígidas de los transportistas de bloques con la actitud independiente de los canteros.  Lo mejor es evitar por completo este conflicto ordenando que los monumentos de su ciudad se construyan de forma secuencial, en lugar de simultánea. @PDebido a su inmenso tamaño, algunos monumentos pueden resultar especialmente difíciles de colocar en su ciudad.  En los monumentos más grandes, no podrá ver toda la huella de la estructura de una sola vez. @PPara evaluar una ubicación seleccionada para un monumento, pulse la tecla 'M'.  La huella del monumento se fijará en el lugar elegido, y podrá mover su punto de vista por la ciudad con normalidad.  Para colocar el monumento en el lugar seleccionado, siempre que sea viable, haga clic con el botón del ratón.  Para seguir buscando un lugar adecuado, pulse 'M' de nuevo.  La huella del monumento volverá a seguir su cursor por la ciudad. @PAdemás, algunos monumentos deben construirse en acantilados. Estos monumentos son el @492Abu&Simbel y las @478Tumbas&reales. @PPara saber más sobre los monumentos, lea las entradas de cada uno. Aparecen en el menú de ayuda. @L@LPara conocer más sobre la historia de los monumentos, haga clic en cualquiera de estos: @391esfinge, @392pirámides, @394mastabas, @493Abu&Simbel, @481Biblioteca&de&Alejandría, @482Cesareo, @475Valle&de&los&Reyes y @396otros&monumentos."
        }
    }
    message_building_mastaba {
        id: 371,
        
        size [30, 20]
        title {
            text: "Mastaba",
        }
        content {
            text: "Las mastabas son tumbas elegantes construidas para la nobleza. A veces, elegirá una mastaba como su propio lugar de descanso final. @PPara construir una mastaba necesitará un gran suministro de @364ladrillos y un @363Gremio&de&albañiles.  También necesitará campesinos de los @8Campamentos&de&trabajo. @PEl primer paso para construir una mastaba es elegir el lugar. Sabrá que ha elegido un lugar viable si ve el 'fantasma' verde de la huella de la mastaba. Si la huella verde contiene algún rombo rojo, algún rasgo del terreno impide construir allí.  Haga clic con el botón del ratón cuando la huella esté completamente en verde, y la ubicación de la mastaba quedará fijada. Unas estacas marcan las esquinas del lugar. @PUna vez establecido el lugar, los albañiles y los campesinos se ponen a trabajar. Los campesinos arrastran trineos cargados de ladrillos, y los albañiles los colocan en su sitio. @PLos difuntos necesitan muchas cosas en el Campo de los Juncos, así que probablemente tendrá que proveer la mastaba de @374provisiones&funerarias. Su @373Supervisor&de&monumentos le dirá qué bienes son necesarios. Consulte con el @369Capataz&de&obras para conocer el estado de la construcción de la mastaba. Haga clic @370aquí para obtener más información sobre la construcción de monumentos. @L@LHaga clic @394aquí para saber más sobre las mastabas en el antiguo Egipto."
        }
    }
    message_building_obelisk {
        id: 372,
        
        size [30, 20]
        title {
            text: "Obelisco",
        }
        content {
            text: "Los obeliscos simbolizan los rayos del sol, y en sus caras se conmemoran grandes hazañas y logros. @PLos obeliscos se fabrican con una gran cantidad de @95granito, y todo el granito necesario para el Obelisco debe almacenarse en los @4Patios&de&almacenamiento de la ciudad antes de poder colocar el monumento. @PMueva el cursor sobre el terreno para elegir una ubicación para el Obelisco.  Si ve la huella del monumento completamente en verde, puede colocar el obelisco.  Si la huella contiene algún rombo rojo, algún rasgo del terreno impide construir el obelisco allí.   @PUna vez elegida la ubicación, se coloca el granito.  Después, los carpinteros del @363Gremio&de&carpinteros levantan los andamios alrededor del monumento, y los @363canteros acuden al monumento para tallar diseños intrincados en él.  No necesita los servicios de campesinos para construir un obelisco. @PHaga clic con el botón derecho sobre el monumento para visitar al @369Capataz&de&obras.  Él le informará del estado del monumento. @L@LLos obeliscos llevan miles de años alzándose hacia el cielo. Haga clic @397aquí para saber más sobre este antiguo monumento."
        }
    }
    message_overseer_monuments {
        id: 373,
        
        size [30, 20]
        title {
            text: "Supervisor de monumentos",
        }
        content {
            text: "Su Supervisor de monumentos puede indicarle qué impide que empiece la construcción de un monumento.  También gestiona el envío de @374provisiones&funerarias a cualquier tumba que pueda necesitarlas.  Para conocer el progreso real de la construcción de un monumento, haga clic con el botón derecho sobre la obra para visitar al Capataz de obras."
        }
    }
    message_burial_provisions {
        id: 374,
        
        size [30, 20]
        title {
            text: "Provisiones funerarias",
        }
        content {
            text: "Para garantizar que el difunto tenga todo lo que necesite en el más allá, debe abastecer la mayoría de las tumbas con provisiones funerarias.  Las provisiones funerarias son materiales que el difunto usó en vida.  También puede que deba proporcionar materiales para la construcción de accesorios especiales necesarios en el más allá, como una barca funeraria y un sarcófago.  Los monumentos no se completan hasta que se suministran las provisiones funerarias necesarias.  El @373Supervisor&de&monumentos tiene una lista de los artículos necesarios y de las cantidades.  Cuando esté listo para enviarlos, ordene al Supervisor de monumentos que despache los bienes a la tumba. @PNo hace falta tener la cantidad completa del material requerido en los @4Patios&de&almacenamiento para poder enviar bienes al monumento.  Puede enviar porciones más pequeñas del bien necesario hasta cumplir el requisito. @PSu ciudad puede necesitar @47importar algunas provisiones funerarias. @L@LLos antiguos egipcios enterraban muchos objetos junto al cuerpo del difunto. Haga clic @395aquí para saber qué suministros llevaban los antiguos egipcios al más allá."
        }
    }
    message_building_stepped_pyramid {
        id: 375,
        
        size [30, 20]
        title {
            text: "Pirámide escalonada",
        }
        content {
            text: "Las Pirámides escalonadas, las primeras pirámides construidas en Egipto, son gigantescas escaleras hacia el sol.  Están hechas por completo de @95piedra&lisa, aunque se necesita madera para construir las rampas que llevan la piedra a los niveles superiores de la pirámide.  Para construir rampas y colocar la piedra, necesitará un @363Gremio&de&carpinteros y un @363Gremio&de&canteros.  También se necesitan campesinos para arrastrar los enormes trineos de piedra hasta la obra.  Cuando haya cuatro bloques de piedra lisa almacenados en los @4Patios&de&almacenamiento y los canteros estén listos, los campesinos comienzan su penoso viaje hasta el lugar del monumento. @PLas Pirámides escalonadas se presentan en cinco tamaños diferentes: pequeña, mediana, grande, complejo piramidal y gran complejo piramidal.  Visite al @369Capataz&de&obras y al @373Supervisor&de&monumentos para obtener más información. La entrada sobre la @370construcción&de&monumentos también puede serle útil. @L@LHaga clic @392aquí para conocer la innovación del visir Imhotep: la Pirámide escalonada."
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
            text: "Osiris, Sebek y Min",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "El papel de Osiris en la religión egipcia cambió a lo largo de los milenios. Junto con su esposa y hermana Isis y su hermano Set, fue uno de los primeros dioses y miembro de la Enéada (consulte @399religión para saber más sobre la Enéada). @L@LEl mito que define a Osiris lo vincula con la agricultura, el Nilo y las costumbres funerarias. Ra-Atum le concedió el gobierno del antiguo Egipto. Osiris se casó con su hermana Isis y, como gobernante, enseñó a su pueblo muchas cosas, sobre todo el arte de la agricultura. Tras instruir a los egipcios, Osiris dejó Egipto para civilizar el resto del mundo, y confió el gobierno a Isis. Isis gobernó bien en su ausencia, pero cuando Osiris regresó, su hermano Set comenzó a tramar contra él. Set invitó a Osiris a un suntuoso banquete, donde presentó un hermoso sarcófago. Ofreció el sarcófago a quien mejor le quedara. Cuando Osiris se metió en él, Set cerró la tapa y arrojó el sarcófago al Nilo. Isis logró sacarlo del río, pero Set la atrapó y despedazó a Osiris. Isis, desconsolada, lloró, y se creía que sus lágrimas eran la causa de la inundación. Finalmente, Isis reunió los trozos dispersos del cuerpo de Osiris, excepto sus genitales, que habían sido devorados por el pez oxirrinco. Isis envolvió a Osiris con lino, igual que se vendaba a las momias. Los egipcios tenían, comprensiblemente, prohibido comer el pez oxirrinco. Con el tiempo, Osiris se convirtió en el dios del inframundo y en el juez supremo que concedía o negaba la entrada en el más allá. @L@LSebek, el dios cocodrilo, era un dios de la fertilidad que se veneraba principalmente en el Fayum, aunque era conocido en todo Egipto. Su nombre significa 'te vigila'. Min, dios de la regeneración, también estaba asociado con la fertilidad masculina y se veneraba en todo Egipto."
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
            text: "Ra, Maat y Horus",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Ra fue considerado el dios principal durante gran parte de la historia de Egipto. Como progenitor de todos los dioses de la Enéada, era el dios creador supremo y estaba asociado con el sol. @L@LMaat era la diosa de la justicia, también asociada con la verdad y el orden. La pluma de avestruz que lleva en la cabeza se usa durante el pesaje del corazón, el último paso que deben superar los individuos antes de entrar en el más allá. @L@LHorus estaba estrechamente asociado con los faraones. Era hijo de Osiris e Isis y vengó la muerte de su padre al revelar que Set era el asesino de Osiris. Horus estaba representado por un halcón. "
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
            text: "Ptah, Amón y Thot",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Ptah es el dios de los artesanos y está asociado con los faraones de Men-nefer (Menfis), que fueron los primeros en unificar Egipto (consulte @399religión para saber más sobre el efecto de los faraones de Men-nefer en las creencias egipcias). Era especialmente venerado por los artesanos de Deir el-Medina, que construyeron las tumbas del Valle de los Reyes y del Valle de las Reinas. @L@LAmón era un dios del sol, asociado especialmente con el sol de la mañana. Alcanzó su prominencia durante la Dinastía XII, cuando los reyes de Waset (Tebas) tomaron el control de Egipto. @L@LThot era el dios de la sabiduría y el saber, y se consideraba el escriba de los demás dioses. Estaba asociado sobre todo con Khmun (Hermópolis)."
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
            text: "Set, Anubis y Sejmet",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Set, hermano de @376Osiris, era el dios de la destrucción. Originalmente, Set era el protector del Bajo Egipto. Cuando el Alto Egipto cobró importancia, el dios patrón del Alto Egipto, @377Horus, se volvió más importante, y Set fue presentado de forma negativa. @L@LAnubis, dios de la muerte, era el dios de la momificación. Representado por el chacal, Anubis protegía a los muertos. @L@LSejmet era una diosa de la guerra con cabeza de leona. Esposa de Ptah, destruía lo que él creaba. Los egipcios la veneraban con la esperanza de apaciguarla para que no desatara su furia."
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
            text: "Bastet, Isis y Hathor",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Bastet, una mujer con cabeza de gato o una leona, era la diosa del hogar, así como de los gatos, el fuego y las mujeres embarazadas. Protegía el hogar tanto por medios dóciles como agresivos. También era la diosa patrona de Bubastis. @L@LIsis, esposa de @376Osiris y madre de @377Horus, volvió a unir el cuerpo roto de Osiris con vendas. Como resultado, fue considerada la diosa de la curación. Se la representaba como una mujer y a menudo aparece con su hijo. @L@LHathor era la diosa de la alegría, el amor y las fiestas. Representada por una vaca, era la diosa patrona de Iunet (Dendera), Men-nefer (Menfis), Qis (Cusae) y Perhathor (Gebelein)."
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
            text: "Historia",
        }
        content {
            text: "La malaria era uno de los riesgos de vivir cerca de los pantanos. En los humanos, la malaria es causada por cualquiera de cuatro parásitos transmitidos por el mosquito anopheles, que es activo principalmente de noche. El inicio de la malaria se caracteriza por la fiebre, seguida de dolores musculares, sudoración y fatiga. Uno de los parásitos que causan la malaria produce casos graves que pueden llevar a la muerte. @L@LPara prevenir las picaduras de mosquito, potencialmente mortales y, como mínimo, molestamente picantes, los antiguos egipcios usaban mosquiteros en sus camas. Heródoto, historiador griego, también señala que los egipcios elevaban sus camas sobre torres para dormir, creyendo que los mosquitos no podían volar a esa altura."
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
            text: "Joyería",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los joyeros tomaban piedras preciosas y semipreciosas y las convertían en collares, gargantillas de cuentas, cinturones y otros adornos. Para ensartar las cuentas, primero perforaban la piedra con un taladro de mano con punta de sílex. Una vez hechos los agujeros, se enhebraba el hilo y se sujetaba. Los joyeros también eran hábiles incrustando gemas. @L@LSegún las representaciones en las paredes de las tumbas, los enanos empleaban con frecuencia en la industria de la joyería."
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
            text: "Caza",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "En comparación con los alimentos cultivados en las granjas y criados en los ranchos, la caza aportaba poco a las reservas de alimentos de Egipto. Aun así, la caza era apreciada por la clase alta, y muchos faraones presumían de sus habilidades como cazadores. Gacelas, antílopes, íbices, bueyes, ovejas y avestruces eran las principales presas, aunque algunos cazaban hienas, leones y leopardos por deporte (y por sus pieles, en el caso de leopardos y leones). Los cazadores usaban arcos y flechas, lanzas o jabalinas para matar a sus presas. @L@LLos egipcios eran igualmente aficionados a cazar animales acuáticos, como aves y hipopótamos. Grupos de hombres cazaban al hipopótamo juntos con una lanza especial atada a una cuerda. Varios hombres intentaban alcanzar al hipopótamo con las lanzas. Una vez causado el daño suficiente, los hombres arrastraban al hipopótamo hasta la orilla con la cuerda. @L@LLas aves se mataban con palos arrojadizos, algo parecidos a los bumeranes australianos. Los ayudantes del cazador, ya fueran familiares o sirvientes, recogían las aves abatidas. También se capturaban aves con redes tendidas en un campo. La red se espolvoreaba con comida para atraerlas. Cuando las aves llegaban al lugar, se tiraba de las esquinas de la red y quedaban atrapadas en su interior."
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
            text: "Sacerdotes",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Una parte importante de la población del antiguo Egipto eran sacerdotes. Su papel iba mucho más allá de los deberes religiosos. Como el antiguo Egipto era una teocracia, los sacerdotes a menudo asumían funciones administrativas en sus comunidades, a veces impartiendo justicia. @L@LLa marca de un sacerdote era su limpieza. Los sacerdotes pasaban por ritos de purificación antes de entrar en el templo y se afeitaban el pelo para asegurarse de que no albergaban piojos ni otras impurezas. Según el dios al que sirviera, un sacerdote tenía prohibido comer ciertos alimentos. Los sacerdotes llevaban ropa especial y también debían usar sandalias blancas. Los sacerdotes de mayor rango a veces se adornaban con pieles de leopardo. @L@LLa principal preocupación religiosa del sacerdocio era el cuidado y la alimentación del dios residente. Cada templo tenía una estatua de su dios patrón en sus dependencias. Cada sacerdote del templo tenía su propia responsabilidad para asegurarse de que el dios estuviera contento. Algunos sacerdotes se encargaban de que el dios estuviera bien alimentado. Con comida ofrecida por los vecinos o producida en la finca del templo, los sacerdotes preparaban una comida para el dios. El dios tomaba la 'esencia' de la comida, y los sacerdotes comían lo que sobraba. Los sacerdotes también vestían y bañaban al dios, y le proporcionaban entretenimiento. Ocasionalmente, el dios era sacado de paseo y llevado en procesión por la aldea (consulte @393festivales para más información). @L@LEl sacerdocio estaba dividido en clases bien diferenciadas. El sacerdote de más alto rango era el Sumo sacerdote, también llamado Primer profeta, que era nombrado por el faraón. El Sumo sacerdote era la máxima autoridad dentro del templo y con frecuencia servía como consejero del faraón. Por debajo del Sumo sacerdote estaban los Sumos sacerdotes adjuntos, o Segundos profetas, que supervisaban funciones concretas del templo o de su finca, como los talleres o las granjas. Por debajo de ellos había sacerdotes encargados de funciones específicas, como bañar al dios o proporcionar entretenimiento. La mayoría de los sacerdotes servían por turnos, trabajando un mes de cada tres."
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
            text: "Canteros",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los canteros supervisaban las @193canteras y la construcción de las @392pirámides y otros monumentos. Aunque conocían a fondo la piedra y la mejor forma de extraerla de las canteras, ellos mismos no realizaban la mayor parte del trabajo agotador. Los campesinos de la clase más baja, y en ocasiones los esclavos, hacían el trabajo más duro. Los canteros lo supervisaban. Además de los grandes proyectos de construcción, la pericia de los canteros era necesaria para trabajos más pequeños, como colocar los cimientos de una casa."
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
            text: "Albañiles",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La técnica de la albañilería apenas ha cambiado en milenios. Los materiales son esencialmente los mismos: @390ladrillos y mortero como aglutinante. En el antiguo Egipto, el mortero se hacía con una mezcla de arcilla, arena, paja y granza. Los albañiles extendían el mortero con una paleta de madera y colocaban el ladrillo en su sitio. Usaban plomadas para asegurarse de que los muros que construían quedaran rectos."
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
            text: "Escribas",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los escribas, o sesh, estaban presentes en toda la sociedad y el gobierno egipcios, y se asociaban con casi todas las acciones del gobierno. Los antiguos egipcios llevaban registros de casi todo, y solo los escribas podían desempeñar esta función. Los escribas registraban cuántos impuestos debía pagar cada persona al gobierno, llevaban la cuenta de las exportaciones e importaciones e incluso acompañaban a los soldados a la batalla para registrar los acontecimientos. Para los ciudadanos particulares, los escribas redactaban documentos legales, como testamentos, y también leían y escribían cartas para las personas. @L@LLas herramientas del oficio de escriba eran el papiro, una paleta con dos panes de tinta (normalmente negra y roja), un recipiente con agua y pinceles de caña. El escriba mojaba el pincel en el agua y luego lo frotaba sobre un pan de tinta. Después escribía sobre el papiro. @L@LMUY pocos escribas sabían escribir jeroglíficos. Los jeroglíficos se reservaban para monumentos y templos. Para el uso diario se empleaba una versión más sencilla de los jeroglíficos, llamada hierática. @L@LLa lengua escrita constaba de unos 700 signos y símbolos combinados, que representaban sonidos junto con símbolos que representaban ideas. La escritura omitía las vocales, por lo que los historiadores solo pueden especular sobre cómo sonaba el antiguo egipcio."
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
            text: "Inmigración",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Egipto disfrutaba de una economía relativamente estable y de una producción de alimentos generalmente constante gracias a la inundación. Los vecinos de Egipto lo sabían, y muchos habitantes de tierras vecinas emigraron a Egipto. @L@LAlgunos de los inmigrantes llegaron para dedicarse al comercio. Las pruebas arqueológicas en las grandes ciudades portuarias, como Menfis, revelan la existencia de asentamientos no egipcios. Estos comerciantes extranjeros aparecen representados en las tumbas del Reino Medio y del Reino Nuevo. Algunos residentes de países vecinos, como Libia, se extendieron por el antiguo Egipto. Hacia la Dinastía XII, los libios ocupaban grandes zonas del oeste del Delta y pronto se extendieron por el este del Delta. @L@LAlgunos llegaron a Egipto con intenciones menos nobles. @181Los invasores de Egipto a menudo se quedaban, incluso después de perder su poder. Muchos de los que se quedaron parecen haber disfrutado de los mismos derechos que los egipcios, y algunos ocuparon altos cargos dentro del gobierno egipcio."
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
            text: "Carpinteros",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los carpinteros fabricaban muchos objetos necesarios para los egipcios. La @192madera autóctona era escasa, así que los carpinteros aprovechaban con gran eficiencia la madera de que disponían. También se usaba madera importada, pero era cara y, por tanto, reservada a los ciudadanos más ricos. @L@LLos carpinteros disponían de hachas, sierras y azuelas para convertir troncos en tablones de madera utilizable. Con el hacha, el carpintero quitaba las ramas de los troncos y, si fabricaba vigas, partía la madera. Las sierras servían para cortar los troncos en tablones, y las azuelas para alisar los tablones y quitarles cualquier bulto. @L@LLos productos terminados incluían cofres, camas, puertas y marcos de puerta, sillas y, quizá lo más importante, ataúdes. En lugar de clavos, se usaban espigas de madera para unir las piezas terminadas. Algunas de las piezas acabadas eran exquisitas, con finas incrustaciones y grabados decorando sus superficies. @L@LLos carpinteros también eran necesarios para la construcción de casas más grandes. Los techos de las casas más ricas solían sostenerse con columnas de madera finamente decoradas. @L@LLa carpintería básica cambió poco a lo largo de la historia del antiguo Egipto, y se prefirieron las mismas herramientas básicas. La gran innovación de la carpintería fue el desarrollo del taladro. Durante el Reino Nuevo se usó un taladro de arco para perforar los agujeros de las espigas."
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
            text: "Ladrillos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los ladrillos eran un material de construcción ideal para los antiguos egipcios. Como no conducían bien el calor, las casas de ladrillo se mantenían relativamente frescas en el interior durante los calurosos veranos. Los ladrillos se fabricaban mezclando arcilla y paja. La arcilla se humedecía, se mezclaba con paja y luego se sumergía en agua. Mientras estaba sumergida, la paja empezaba a descomponerse y, al hacerlo, excretaba un limo que mantenía unido el ladrillo. Después, el ladrillo se secaba al sol. Cuando los ladrillos estaban listos, los @386albañiles podían comenzar su trabajo."
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
            text: "Esfinge",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La Esfinge, asociada con Amón en el antiguo Egipto, tiene cuerpo de león y cabeza de rey. Hubo muchas esfinges en Egipto, pero la más famosa, con diferencia, es la Gran Esfinge de Giza (Rostja).  @L@LConstruida hacia el 2500 a. C., la Gran Esfinge parece custodiar la pirámide de Kefrén y se alza sobre una antigua cantera. Se cree que su rostro es el del propio Kefrén. La Esfinge mide unos 60 metros de largo y unos 20 metros de alto. Está tallada en arenisca blanda. @L@LLa Esfinge estuvo enterrada en la arena durante la mayor parte de su existencia. La leyenda cuenta que Tutmosis IV, antes de convertirse en faraón, estaba de caza en la zona de la Esfinge y se quedó dormido en el lugar donde se encuentra. Mientras dormía, la Esfinge le habló y le dijo que, si la desenterraba, se convertiría en faraón. Tutmosis obedeció a la Esfinge y se convirtió en faraón en 1425 a. C. Registró la historia en estelas y la colocó entre las patas de la Esfinge. @L@LLa Gran Esfinge volvió a quedar enterrada y, por fin, fue descubierta de forma definitiva en la década de 1930. Los intentos de conservarla han tenido resultados desiguales."
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
            text: "Pirámides",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Durante siglos se ha especulado sobre cómo se construyeron las pirámides. Resulta inconcebible que los antiguos egipcios, sin la ayuda de grúas elevadoras, excavadoras ni la gran variedad de maquinaria moderna, pudieran levantar estructuras tan magníficas. @L@LLa construcción de cualquier pirámide comenzaba con un plan bien trazado. El visir, solo por detrás del faraón en rango, supervisaba probablemente todo el proceso, mientras que el arquitecto real (conocido en el antiguo Egipto como medjeh nesu) establecía los planos. El arquitecto real era responsable de elegir los materiales y de calcular cómo llevarlos hasta la obra. @L@LUna vez elegido con cuidado el emplazamiento, los astrónomos determinaban el eje norte-sur de la pirámide. Después, los topógrafos trazaban todos los lados de la pirámide con un cordel especial, tan grueso que no se estiraba y no alteraba las dimensiones de la pirámide. Luego se nivelaba el terreno, quizá llenando de agua las zanjas para determinar un plano uniforme. @L@LCompletadas estas tareas, la construcción podía comenzar. Para iniciarla se celebraba una ceremonia en la que el faraón marcaba las esquinas de la pirámide con estacas, tendía un cordel entre ellas y colocaba un ladrillo de barro ceremonial como primera piedra del monumento. @L@LEn ese momento, los @385canteros y los @155trabajadores tomaban el relevo. Los canteros excavaban las salas subterráneas, incluida la cámara funeraria. Una vez listas, comenzaba el arduo proceso de transportar bloques de piedra, algunos de los cuales pesaban hasta 2,5 toneladas. Las piedras se arrastraban sobre trineos y probablemente se usaban rampas para llegar a las partes más altas de la pirámide. Además de las piedras toscamente labradas que formaban el interior de la pirámide, una piedra más fina revestía la estructura. @L@LAlgunas pirámides se alzaban solas, pero con más frecuencia formaban parte de conjuntos piramidales más grandes. El conjunto contaba con un templo del valle situado junto al agua o en el borde de la zona cultivada. Desde el templo del valle, una larga calzada conducía al templo funerario, situado en el lado este de la pirámide. @L@LLa forma de las pirámides evolucionó a medida que se perfeccionaba la técnica para construirlas. La primera pirámide, la pirámide escalonada de Dyoser, no tiene caras lisas. Construida hacia el 2620 a. C., la pirámide escalonada es una serie de cuadrados apilados unos sobre otros. La primera pirámide verdadera es la de Esnefru, construida hacia el 2550 a. C. Un revestimiento exterior alisó los 'escalones' de la pirámide, y esta práctica se adoptó pronto en otras pirámides. La pirámide más grande es la de Keops, que mide 230 x 230 metros en la base y alcanza una altura de 146 metros. Una pirámide singular es la pirámide acodada de Esnefru. El ángulo de las caras cambia a unos dos tercios de la altura. Se cree que los arquitectos juzgaron que la pirámide sería demasiado pesada y propensa a derrumbarse si seguía con su ángulo original. Y como la primera pirámide de Esnefru se derrumbó, probablemente pensó que más valía prevenir que curar."
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
            text: "Festivales",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los festivales del antiguo Egipto eran celebraciones alegres en las que había comida en abundancia y la cerveza corría libremente. Se celebraban por muchos motivos: para honrar a un dios, para marcar la cosecha y para reconocer la longevidad del faraón. Los últimos cinco días del año egipcio se dedicaban a la celebración, y a lo largo del año se producían otros muchos festivales. @L@LFue durante los festivales en honor de una deidad cuando todas las personas tenían acceso directo a sus dioses. En el centro de las celebraciones religiosas estaba la procesión del dios. Durante el festival, la estatua del dios que residía en el templo, fuera de la vista del público, se vestía con sus mejores ropajes y se paseaba por la ciudad en una barca ceremonial llevada por sacerdotes. Los sacerdotes descansaban de forma periódica, y en esos momentos se realizaban ritos. Durante el Reino Nuevo, los ciudadanos podían hacer preguntas al dios mientras los sacerdotes descansaban. Los sacerdotes se inclinaban si la respuesta del dios era positiva y retrocedían si era negativa. Al final del festival, el dios regresaba a su morada en el templo. @L@LA veces, los dioses viajaban bastante lejos y eran transportados en barco. Por ejemplo, durante el festival de Opet, Amón viajaba de Karnak a su capilla meridional de Luxor. Para hacer el viaje, navegaba por el Nilo. El Opet era uno de los festivales más alegres y duraba entre 11 y 27 días. @L@LSi un faraón gozaba de salud suficiente para reinar durante 30 años, se celebraba el festival Heb-sed. Celebrado en el año 30 del reinado del faraón y cada tres años después, el festival incluía una carrera ritual en la que el faraón demostraba que seguía en forma para gobernar. Algunos faraones no esperaron a los 30 años para celebrar el Heb-sed y lo celebraron mucho antes en su reinado. @L@LSin duda, los egipcios de todos los estratos sociales recibían los festivales como una ocasión para comer y beber muy bien. Los festivales también ofrecían un respiro de la rutina diaria."
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
            text: "Historia",
        }
        content {
            text: "Los primeros faraones y nobles del Reino Antiguo fueron enterrados bajo mastabas. Las mastabas cubrían el pozo que conducía a la cámara funeraria. Al principio eran construcciones bajas y sencillas con inscripciones, pero evolucionaron hasta convertirse en estructuras más grandes, con capillas incluidas. Las mastabas se consideran precursoras de las pirámides, y la pirámide escalonada de Dyoser pudo haber empezado como una mastaba."
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
            text: "Provisiones funerarias",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Las tumbas estaban bien equipadas con todo lo que el difunto necesitaría en el más allá. Conocidas como provisiones funerarias, estas mercancías incluían las herramientas del oficio del difunto, comida, artículos de aseo, joyas, instrumentos musicales, maquillaje; en definitiva, casi todo lo que el difunto había usado en vida. Las tumbas también se dotaban de shabtis, o 'respondedores'. Estas figuritas se incluían en la tumba por si al difunto se le pedía que trabajara en el más allá. El shabti realizaría el trabajo en lugar del difunto."
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
            text: "Otros monumentos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Además de los @397obeliscos, las @394mastabas, las @392pirámides y las @391esfinges, el antiguo Egipto tenía otros muchos monumentos. Entre ellos había mausoleos y templos del Sol.  @L@LEn el antiguo Egipto, el sol se consideraba dador de vida, y se construyeron muchos templos del Sol por todo Egipto, sobre todo durante la Dinastía V. Los templos solares más notables están en Abu Gurab. Allí se levantaban dos templos solares en los que se realizaban sacrificios de animales. @L@LLos mausoleos y las capillas se construían con frecuencia sobre las tumbas para que la familia del difunto pudiera hacer ofrendas. Estas ofrendas garantizaban que el difunto siguiera disfrutando del más allá. Cualquiera que tuviera recursos construía estas capillas para sus familiares, y los mausoleos personales abundan en el paisaje egipcio."
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
            text: "Obelisco",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los obeliscos se asociaban con el sol y representaban los rayos solares o el montículo primigenio sobre el que el sol brilló por primera vez. Tallados en granito y grabados con jeroglíficos, los obeliscos se erigían fuera de los templos, por lo general en parejas. @L@LLa forma del obelisco se labraba en las canteras, y uno inacabado en Asuán revela mucho sobre el proceso de extracción de una pieza de roca tan grande. Los obreros usaban percutores de dolerita para tallar lentamente la forma necesaria. El obelisco de Asuán se abandonó porque se produjo una fisura en el centro de la piedra. @L@LUna vez extraído el obelisco de la roca, nadie sabe con certeza cómo se erigían. Los intentos modernos de levantar obeliscos con lo que se cree que eran métodos antiguos han fracasado."
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
            text: "Lino y tejeduría",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Hecho de @189lino, el lino era el textil predominante en el antiguo Egipto. Aunque algunas telas se fabricaban con lana o cáñamo, se consideraban muy inferiores al lino. @L@LPara hacer tela, primero había que hilar las fibras de lino para convertirlas en hilo. Sentados frente a montones de lino, los hiladores retorcían las fibras y las enrollaban en ovillos. Después, el hilo se colocaba en husos y comenzaba el tejido. @L@LLos egipcios usaban un telar horizontal colocado en el suelo. Los tejedores preparaban el telar con dos filas paralelas de hilo (la urdimbre). Dos trabajadores se sentaban a ambos lados del telar y hacían pasar la lanzadera con el hilo (la trama) de un lado a otro para formar la tela. @L@LDurante el Reino Nuevo, un telar vertical reemplazó al horizontal. El telar vertical permitía a los tejedores sentarse más cómodamente en taburetes. @L@LLa mayoría de los tejedores eran mujeres, que con frecuencia formaban parte del harén del faraón."
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
            text: "Religión",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La religión egipcia contaba con un panteón numeroso de dioses mayores y menores. La mayoría de las ciudades, e incluso los individuos, consideraban a un dios concreto como su patrón, y esta costumbre influía en qué dioses tenían más importancia. @L@LUna de las primeras estructuras de creencias fue la Eneada, o grupo de nueve dioses. Fundada en la ciudad de On (Heliópolis), el primer dios de la Eneada es Atum, quien se unió a Ra para convertirse en Ra-Atum. Ra-Atum, aunque masculino, logró dar a luz él solo a los gemelos Shu y Tefnut. Shu era el dios del aire, y Tefnut la diosa del orden del mundo. Shu y Tefnut tuvieron cuatro hijos: Isis, Osiris, Neftis y Set. Completa la lista de nueve dioses Horus, hijo de Isis y Osiris. Más adelante, Ra se concibió por separado de Atum y se convirtió en el dios principal de la Eneada. Este sistema de dioses dominó el Egipto predinástico, y Ra siguió siendo un dios importante para los antiguos egipcios.  @L@LCuando Hor-Aha unificó el Alto y el Bajo Egipto, su creencia personal en Ptah, dios creador, cambió el sistema de creencias. Hor-Aha sostenía que los dioses de la Eneada eran todas manifestaciones de Ptah. Aun así, Ra seguía siendo el dios predominante. @L@LOtra teoría surgió en la ciudad del Alto Egipto de Jmún (Hermópolis). Los hermopolitanos creían en una Ogdóada, o grupo de ocho dioses. En la Ogdóada, un par de dioses masculino y femenino representan distintos aspectos del mundo. Nun y Naunet representaban el agua, Huh y Hauhet representaban la infinitud, Kuk y Kauket eran los dioses de la oscuridad, y Amón y Amaunet eran los dioses del aire. @L@LEn el Reino Nuevo, Amón desplazó a Ra como dios principal. El dominio de Amón continuó hasta el reinado de Akenatón. Akenatón intentó introducir el monoteísmo en Egipto, sosteniendo que Atón, encarnado en el disco solar, era el único dios. Durante su gobierno, conocido como el período de Amarna, Akenatón clausuró los templos de los demás dioses. Tras su muerte, sin embargo, el politeísmo se restableció rápidamente y los templos de los demás dioses volvieron a abrirse."
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
            text: "Nace una aldea",

        }
        content {
            text: "@PBienvenido al antiguo Egipto, tierra de los faraones. Aquí participará en la historia de una de las mayores civilizaciones que el mundo ha conocido, en una epopeya que abarca más de quince siglos y dos docenas de generaciones. Deberá guiar a una familia, generación tras generación, desde sus primeros orígenes en la prehistoria egipcia, a través del amanecer de la civilización... hasta el establecimiento de un imperio único y poderoso... y más allá.     @PNuestra historia comienza hace más de cinco mil años, a orillas del río Nilo, en una zona conocida como Naqada. Aquí, una pequeña confederación de clanes lucha por sobrevivir en un entorno hostil. Con usted a la cabeza, su familia dirige este pequeño asentamiento."
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
            text: "El amanecer de la civilización",

        }
        content {
            text: "@PTras muchos años, y el paso de una generación, su familia se ha reasentado en la zona de Thinis, en el Alto Egipto. Aquí, un pequeño grupo de gobernantes locales intenta extender su influencia sobre el Bajo Egipto y todas las tierras a orillas del río Nilo, y unificar este reino bajo su propia casa, con un único líder supremo.   @PConvertir Thinis en una ciudad próspera, como nunca antes se había visto, demostrará el valor de la confederación tinita y le ayudará a obtener la supremacía sobre el Bajo Egipto y sobre las demás facciones que compiten por el poder. Con el tiempo, esto significará proporcionar entretenimiento a la población y construir templos maravillosos para venerar al dios patrón de la región. @PPara construir una ciudad tan grandiosa se necesitará una cuantiosa suma de dinero. En Thinis encontrará ricos yacimientos de mineral de oro, y explotarlos debe ser su primera prioridad. "
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
            text: "Los nobles tinitas todavía luchan por unir las tierras del Nilo bajo un único gobernante supremo. Para ayudarles en su causa, se espera que usted establezca una comunidad próspera en Buto, en la húmeda región del Delta del Bajo Egipto, extendiendo así su influencia a lo largo del sagrado río. Para mantener a una población mayor que la de una aldea, debe aprender a practicar la agricultura. @PLos agricultores egipcios han empezado a aprovechar el fértil suelo que deja la inundación anual del Nilo para cultivar sus cosechas. Sin embargo, el Nilo puede ser peligroso. Muchos peligros acechan en sus orillas y en sus aguas, como cocodrilos mortales, hipopótamos y mosquitos portadores de malaria."
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
            text: "El primer faraón",

        }
        content {
            text: "Mientras el pueblo que vive a orillas del Nilo todavía lucha por sobrevivir en este entorno hostil, un rey local llamado Narmer ha llegado al poder. Aunque Narmer domina gran parte de esta tierra, la unificación total de los dos reinos aún no se ha logrado. En conmemoración de su ascenso, Narmer desea que su familia establezca y gobierne una nueva ciudad en Hierakonpolis. Esta ciudad tendrá templos dedicados a muchos de los dioses de Egipto y numerosos lugares de entretenimiento."
        }
    }
    message_mission_memphis {
        id: 404,
        type: 3,
        size [40, 30]
        title {
            text: "Menfis",

        }
        subtitle {
            text: "Se funda una capital",

        }
        content {
            text: "Tras una larga lucha, el rey Hor-Aha ha conseguido unir los dos reinos del Alto y el Bajo Egipto, y se ha proclamado faraón de todo Egipto. Como señal de su soberanía absoluta y del establecimiento de esta primera dinastía de Egipto, Hor-Aha ha ordenado la fundación de una imponente capital en Menfis, desde la que pueda gobernar esta nación recién nacida. Gracias a las muchas generaciones de servicio leal de su familia a esta tierra, el Faraón le ha elegido como arquitecto de esta espléndida ciudad. Como la capital es el símbolo mismo de nuestro reino, sus ciudadanos deben disfrutar de una calidad de vida nunca antes conocida en esta tierra. Para ello, con el tiempo deberá comerciar con otras ciudades del reino y ofrecer un nivel de educación superior al menos a algunos de sus ciudadanos. También debe construir una tumba mastaba sagrada para los nobles de la ciudad."
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
            text: "Una expedición al Sinaí"
        }
        content {
            text: "Un nuevo faraón, Den, ha ocupado el trono de Egipto. El Faraón está profundamente preocupado, pues los enemigos han comenzado a amenazar nuestras fronteras y nuestra nación carece de suministros adecuados del valioso cobre necesario para fabricar las armas con las que equipar a nuestras tropas. El faraón Den ha ordenado una expedición minera a la implacable tierra del Sinaí, más allá de nuestras fronteras y en lo profundo del territorio beduino. La zona conocida como Timna es rica en mineral de oro y cobre, así como en preciosas piedras de turquesa, pero por lo demás es un lugar yermo. Las condiciones allí serán duras y deberá importar muchas comodidades, quizá incluso alimentos adicionales y lino fino, desde Egipto. El Faraón exigirá envíos frecuentes desde el Sinaí y le pedirá dinero, cobre, gemas y armas. Puede utilizar cualquier excedente de estos artículos para ayudar a sostener la expedición. Manténgase siempre alerta, pues los beduinos del desierto del Sinaí son adversarios formidables y no permitirán de buen grado que los extranjeros ocupen su tierra, y mucho menos que saqueen sus riquezas minerales. @PPara aliviar la carga que estas condiciones de vida imponen a la población de su ciudad, construya un Pabellón en alguna intersección concurrida. Los ciudadanos podrán relajarse en los escenarios de malabarismo y música del Pabellón y, si además construye una Escuela de Danza, este nuevo tipo de espectáculo proporcionará un gran entretenimiento. "
        }
    }
    message_mission_apollinopolis {
        id: 406,
        type: 3,
        size [40, 30]
        title {
            text: "Apolinópolis"
        }
        subtitle {
            text: "La flota del Faraón",
        }
        content {
            text: "Las tropas militares de Egipto no tienen rival en el mundo conocido, pero el nuevo faraón, Jasejemuy de la segunda dinastía, exige también una poderosa flota con base en Apolinópolis. Nada menos que una flota de navíos de guerra bastará para asegurarnos el dominio de los mares, pero la madera escasea, pues nuestro clima sólo sostiene unas pocas y dispersas zonas de bosque. El cedro puede importarse, a un costo muy elevado, desde Biblos, en el Líbano, al noreste. Afortunadamente, las exportaciones de nuestro papiro autóctono servirán para compensar este gasto."
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
            text: "El desafío del mar ",

        }
        content {
            text: "Abydos, lugar de enterramiento de nuestros antepasados, se ha convertido con los años en una extensa necrópolis de tumbas sagradas. Ahora, la mayoría de los nobles, hombres y mujeres, desean que este sea su lugar de descanso eterno. Para honrarlos, el nuevo faraón Jasejemuy de la segunda dinastía ha ordenado construir tres tumbas mastaba sagradas (una de mayor tamaño que las otras dos) para la nobleza local. @PEl Faraón también ha ordenado la creación de una poderosa flota, con base en Apolinópolis. Abydos también debe sostener una modesta flota de navíos de combate, si nuestras costas han de permanecer totalmente seguras. Esto no será fácil, pues la madera escasea y nuestro clima sólo sostiene unas pocas zonas de bosque dispersas. El cedro puede importarse, a un costo muy elevado, desde Biblos, en el Líbano, al noreste. Afortunadamente, las exportaciones de nuestro papiro autóctono servirán para compensar este gasto."
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
            text: "El camino a África",

        }
        content {
            text: "@PHa sido proclamado un nuevo faraón, Nebka, que inaugura la tercera dinastía de gobernantes egipcios. Nebka ha aportado gran organización y estructura a Egipto, ordenando que todo el reino se divida en distritos, o nomos, cada uno gobernado por un gobernante local llamado 'nomarca'. Aunque este sistema pueda parecer rígido, bajo su liderazgo Egipto ha crecido y prosperado, y ha logrado grandes avances en el arte y la arquitectura. @L@PLas caravanas de mercaderes, que viajan de oasis en oasis desde lo profundo del interior africano, han comenzado a proporcionar a Egipto muchos bienes de lujo raros y exóticos, hoy muy apreciados por nuestro pueblo. Desafortunadamente, estas caravanas son atacadas habitualmente por guerreros de Libia e incluso por beduinos del desierto Oriental. Para asegurar estas rutas comerciales, el faraón Nebka, Aquel del Junco y la Abeja, desea que establezca un puesto militar en el oasis de Selima, centro del comercio de caravanas, muy lejos de las fronteras de nuestro reino. @L@PAllí encontrará algunos árboles aptos para madera, cuya venta le ayudará a reunir el dinero para financiar este puesto. Para forjar armas, puede obtener cobre de nuestras recién establecidas minas de Timna, en la tierra del Sinaí. @L@PDesde el oasis de Selima puede importar ébano de la nación africana de Kerma. Una vez que haya logrado establecer este puesto, será una fuente fiable de ébano para todas las ciudades de nuestro reino."
        }
    }
    message_mission_elephantine {
        id: 409,
        type: 3,
        size [40, 30]
        title {
            text: "Elefantina",

        }
        subtitle {
            text: "La frontera nubia",

        }
        content {
            text: "@PHa sido proclamado un nuevo faraón, Nebka, que inaugura la tercera dinastía de gobernantes egipcios. Nebka ha aportado gran organización y estructura a Egipto, ordenando que todo el reino se divida en distritos, o nomos, cada uno gobernado por un gobernante local llamado 'nomarca'. Aunque este sistema pueda parecer rígido, bajo su liderazgo Egipto ha crecido y prosperado, y ha logrado grandes avances en el arte y la arquitectura.   @PEl Faraón desea extender las fronteras de nuestro reino más al sur, hacia Nubia. Ordena fundar una ciudad en la primera catarata del Nilo, en la isla de Elefantina, para aprovechar los abundantes yacimientos de gemas, granito y arenisca que allí se encuentran.   @PLa creciente necrópolis de Abydos exige estos materiales para la construcción de tumbas cada vez más elaboradas para la nobleza. La capital, Menfis, también puede necesitar ladrillos para la construcción de tumbas, y el faraón Nebka puede aprobar las solicitudes de estos y otros materiales de construcción. @PEl faraón Nebka también ha ordenado que uno de sus pares establezca un puesto militar en el oasis de Selima, para asegurar las rutas de caravanas hacia el interior africano. Una vez establecido, podrá considerar el puesto de Selima como fuente de ébano importado, un bien de lujo muy apreciado."
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
            text: "La primera pirámide",

        }
        content {
            text: "La subida al trono del faraón Yoser ha inaugurado una nueva era de sabiduría, saber y logros artísticos. Se establecerá una necrópolis real en Saqqara, que servirá como lugar de descanso eterno para nobles como Hezyre y Jabausokar, consejeros de confianza del Faraón.   @PPero este lugar albergará también un monumento como nunca antes se ha visto en el mundo. Yo, Imhotep, visir real del Faraón, he concebido una nueva forma de tumba sagrada para el Faraón. A diferencia de las bajas mastabas de adobe de faraones anteriores, esta tumba se elevará hacia los cielos, como si estuviera formada por varias mastabas colocadas unas sobre otras. Y, además, esta 'pirámide escalonada' se construirá enteramente en piedra, para que resista el paso de los eones. En su interior, un sarcófago de granito macizo guardará el cuerpo del Faraón para su descanso eterno. @PLos sacerdotes de la necrópolis de Abydos han perfeccionado el arte de usar lino para embalsamar a los muertos, abriendo así a todos los egipcios la puerta a la vida eterna.  @PNuestro puesto comercial en el oasis de Selima sigue prosperando, y desde allí puede importar ébano de África.  @PEl Faraón le ha concedido una generosa suma de dinero para comenzar este proyecto. No le defraude."
        }
    }
    message_mission_serabit_khadim {
        id: 411,
        type: 3,
        size [40, 30]
        title {
            text: "Serabit Jadim",

        }
        subtitle {
            text: "Los beduinos del Este",

        }
        content {
            text: "Como Den antes que él, el faraón Huni ha ordenado una expedición a la dura tierra del Sinaí para adquirir piedras de turquesa y cobre. Desea que usted dirija esta expedición a un lugar llamado Serabit Jadim, donde aún pueden encontrarse los restos de construcciones de un antiguo puesto egipcio. Se desconoce su estado actual, pero aún podrían proporcionar algún medio de defensa a la expedición.   @PDebe saber que la última expedición enviada a esta zona nunca regresó. Una expedición posterior, enviada para recuperarlos, tampoco regresó. Aun así, si queremos armar adecuadamente a nuestros soldados, nuestro reino necesita cobre para fabricar armas, y este metal escasea en nuestra tierra. @PPrepárese, pues estará bajo la constante amenaza de ataques de los beduinos del desierto del Sinaí y de nuestros enemigos, los cananeos. Extraiga el cobre y las gemas que pueda en estas condiciones, y sea diligente al cumplir las peticiones del Faraón. Puede emplear joyeros para usar cualquier excedente de gemas en la fabricación de joyas para los habitantes del asentamiento."
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
            text: "Una necrópolis real",

        }
        content {
            text: "El faraón Huni desea pasar la eternidad en una pirámide escalonada, como la de Yoser antes que él. Desea estar rodeado de las tumbas de sus nobles, y ha elegido Meidum, en el Bajo Egipto, como lugar para esta necrópolis real.   @PEn señal de agradecimiento por las muchas generaciones de servicio leal prestado por su casa, Huni también ha accedido a que usted sea enterrado en Meidum, en su propia tumba. Con ello, ha conferido un gran honor a su familia. @PPara que la sabiduría y el saber de Egipto se preserven a través de los siglos, el faraón Huni también insta a la construcción de bibliotecas reales. Una vez llenas de rollos de papiro, proporcionarán educación superior a las clases altas. @PEl Faraón ha enviado a otro de sus leales cortesanos en una expedición a Serabit Jadim, en la dura tierra del Sinaí, para adquirir piedras de turquesa. Si esta expedición tiene éxito, podrá esperar importar gemas desde allí. Los joyeros pueden usarlas para fabricar joyas, un valioso bien de lujo, para la gente de su ciudad. @PLa antaño próspera ciudad de Apolinópolis ha comenzado a decaer y ya no exporta muchos de los productos por los que era conocida."
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
            text: "Expansión a Nubia",

        }
        content {
            text: "Nuestro nuevo faraón, Snofru, está decidido a que esta cuarta dinastía sea recordada como la mayor que haya gobernado Egipto. El Faraón desea que nuestras fronteras se extiendan aún más al sur. Por ello ha decretado que invadamos Nubia y establezcamos una ciudad fortificada en Buhen, junto a la segunda catarata del Nilo. Allí también deberá erigir un obelisco de granito, que sirva de faro para proclamar que esta zona pertenece para siempre a Egipto y al Faraón. Sin embargo, no hay granito tan al sur, así que deberá importarlo de Elefantina.   @PEn Buhen se enfrentará a feroces y experimentados guerreros nubios, que lucharán hasta la muerte para impedir que establezcamos una base tan al sur. No desespere, pues tras un riguroso entrenamiento en una Academia Militar, sus hombres de armas pueden convertirse en veteranos curtidos. Además, nuestros ingenieros militares han perfeccionado el diseño de varias estructuras defensivas, como torres fortificadas, murallas y puertas fortificadas. Estas serán de gran valor para resistir el embate del ejército nubio. También pueden emplearse barcos de transporte para ayudar a mover su ejército por agua cuando sea necesario. @PAl norte, hemos establecido relaciones con Enkomi, en la isla de Chipre. Esta tierra debe su nombre a sus abundantes reservas de mineral de cobre, que ahora podemos comprarle. Sin embargo, gracias a una comunidad minera egipcia establecida recientemente en Serabit Jadim, en la tierra del Sinaí, podemos suministrar cobre a nuestros gobernadores a un precio mucho más asequible. Los suministros de Serabit Jadim son a menudo irregulares, debido a los ataques incesantes de beduinos y cananeos contra el asentamiento, y no sabemos cuánto tiempo más podrán resistir las fuerzas egipcias allí destacadas. @PLa tumba del Faraón, un monumento único y espectacular, se encuentra actualmente en construcción en Dahshur. De vez en cuando, el Faraón podrá pedirle que aporte caliza para ayudar a completar este proyecto."
        }
    }
    message_mission_south_dahshur {
        id: 414,
        type: 3,
        size [40, 30]
        title {
            text: "Dahshur Sur",

        }
        subtitle {
            text: "La pirámide acodada de Snofru",

        }
        content {
            text: "@PNuestro nuevo faraón, Snofru, está decidido a que esta cuarta dinastía sea recordada como la mayor que haya gobernado Egipto. Sus arquitectos han ideado una tumba aún más espectacular que la pirámide escalonada de Huni, y el Faraón desea que usted supervise su construcción. Deberá establecer un asentamiento de tamaño considerable al sur de Dahshur, el lugar de la pirámide acodada del Faraón. Una vez establecida, esta ciudad proporcionará la mano de obra necesaria para completar este ambicioso proyecto. @PLa pirámide acodada debe construirse con un núcleo de piedra sencilla y revestirse con fina caliza blanca, para que brille para siempre bajo el sol del desierto. Encontrará suficiente caliza en Dahshur, pero deberá importar la cantidad necesaria de piedra sencilla para esta empresa. @PEl Faraón desea que nuestras fronteras se extiendan aún más al sur, y con este fin ha enviado fuerzas militares para invadir Nubia y establecer una ciudad fortificada en Buhen, junto a la segunda catarata del Nilo. @PAl norte, Egipto ha establecido relaciones con Enkomi, en la isla de Chipre. Esta tierra debe su nombre a sus abundantes reservas de mineral de cobre, que ahora son una importación importante. @PSe pueden obtener gemas preciosas de un puesto egipcio establecido recientemente en Serabit Jadim, en la tierra del Sinaí. Últimamente el suministro se ha vuelto irregular, debido a los ataques incesantes de beduinos y cananeos contra el asentamiento, y no sabemos cuánto tiempo más podrán resistir las fuerzas egipcias allí destacadas."
        }
    }
    message_mission_north_dahshur {
        id: 415,
        type: 3,
        size [40, 30]
        title {
            text: "Dahshur Norte",

        }
        subtitle {
            text: "La verdadera pirámide",

        }
        content {
            text: "@PEl faraón Snofru ha traído orden a Egipto, y el reino prospera bajo su sabio y benevolente gobierno. Snofru desea emprender otro proyecto de construcción en Dahshur, aún más ambicioso que la pirámide acodada ya terminada. Los arquitectos, topógrafos e ingenieros reales confían en poder levantar un edificio cuyas caras se elevan en un ángulo continuo, culminando en un vértice perfecto. Si lo logran, será la primera verdadera pirámide, ¡y un digno hogar para el faraón Snofru por toda la eternidad!    @PLa esposa del Faraón, la reina Hetepheres, ha dado recientemente a luz a un hijo al que han llamado 'Keops'. Nuestro pueblo mira hacia el día de su eventual reinado con gran temor, pues los videntes de Horus, dios del Faraón, han predicho que no mostrará ninguna de la benevolencia de su padre hacia nuestro pueblo. Aunque logrará grandes cosas, temen que gobierne Egipto con una tiranía inquebrantable. @PPuede adquirir madera de Biblos, pues los carpinteros tendrán que construir muchas rampas para que los trabajadores alcancen la cima de esta gran pirámide."
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
            text: "La defensa de Egipto",

        }
        content {
            text: "@PHa subido al trono el faraón Keops y, como vaticinaron los videntes de Horus y Ra, nuestro pueblo ya ha empezado a sufrir su opresión. @PKeops ha ordenado que un gobernador real sea enviado de inmediato a Dendera, para defender nuestra tierra de los invasores kushitas. Dendera puede sostener una pequeña industria pesquera, que alimentará a este asentamiento durante un tiempo. Sin embargo, si los kushitas invaden por agua, el río podría volverse inseguro para los barcos de pesca, y las zonas costeras podrían aprovecharse mejor para sostener una flota de navíos de guerra. Si los alimentos escasean, también puede criarse ganado para obtener carne, aunque los rebaños necesitan mucha paja como forraje, y la paja es difícil de cultivar en esta tierra. Debe buscar otras ciudades con las que comerciar para obtener paja, pues también la necesitará para fabricar ladrillos para su mastaba. @PLa ciudad de Biblos, en el Líbano, tierra de los cedros, ha comenzado a comerciar con los poderosos imperios del este. Se trata de Asiria y Ur, en la tierra llamada 'Mesopotamia', entre los dos grandes ríos, y de ellos puede obtenerse el mejor marfil a través de Biblos. Con la llegada de bienes de lujo raros y exóticos como este, Dendera sin duda prosperará. @PEn la capital, el pueblo egipcio ha empezado a disfrutar de un juego de mesa llamado senet. Este juego suele disfrutarse con una jarra de cerveza, en un lugar público de reunión llamado 'Casa del Senet'. Estos lugares pueden ofrecer un entretenimiento bienvenido a la gente de Dendera, alejándola de la tiranía de la autoridad de Keops. @PEl Faraón ha ordenado excavar innumerables canteras en Heliópolis, en la región del Delta, para extraer un gran suministro de caliza blanca de calidad. Solo los dioses saben qué empresa tiene planeada el Faraón para el uso de esta piedra. Se rumorea que planea un proyecto de construcción colosal en la meseta frente a Giza, para usurpar la fama que su padre, el sabio y benevolente Snofru, ganó con la finalización de sus dos nobles pirámides."
        }
    }
    message_mission_heliopolis {
        id: 417,
        type: 3,
        size [40, 30]
        title {
            text: "Heliópolis",

        }
        subtitle {
            text: "Marfil del Este",

        }
        content {
            text: "@PEl faraón Keops ha subido al trono y, como vaticinaron los videntes de Horus y Ra, nuestro pueblo ya ha empezado a sufrir su opresión. Se rumorea que planea iniciar un proyecto de construcción colosal en la meseta frente a Giza, para usurpar la fama que su padre, el sabio y benevolente Snofru, ganó con la finalización de sus dos nobles pirámides.  @PKeops ha ordenado excavar un conjunto de canteras en Tura, en la región del Delta, donde recientemente se han descubierto ricos yacimientos de caliza blanca de calidad. También debe construir tres tumbas mastaba para los nobles de esta región, para que el Faraón pueda honrar su devoción. El asentamiento de canteras que ha fundado se llamará 'Heliópolis' y servirá como fuente abundante de caliza blanca de calidad durante muchos años... aunque solo los dioses saben qué empresa tiene planeada el Faraón para su uso. @PLa ciudad de Biblos, en el Líbano, tierra de los cedros, ha comenzado a comerciar con los poderosos imperios del este. Se trata de Asiria y Ur, en la tierra llamada 'Mesopotamia', entre los dos grandes ríos, y de ellos puede obtenerse el mejor marfil a través de Biblos. Con la llegada de bienes de lujo raros y exóticos como este, Heliópolis sin duda prosperará. @PKeops también ha enviado a un gobernador real a Dendera, para defender nuestra tierra de los invasores kushitas. Los visires reales miran con compasión al gobernador encargado de esta tarea difícil y peligrosa. @PEn la capital, el pueblo egipcio ha empezado a disfrutar de un juego de mesa llamado senet. Este juego suele disfrutarse con una jarra de cerveza, en un lugar público de reunión llamado 'Casa del Senet'. Estos lugares pueden ofrecer un entretenimiento bienvenido a la gente de Heliópolis, alejándola de la tiranía de la autoridad de Keops."
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
            text: "La Gran Pirámide y la Esfinge",

        }
        content {
            text: "El faraón Keops ha dado a conocer por fin sus planes, y sus aspiraciones sin límites sin duda pesarán mucho sobre nuestro pueblo. El Faraón a la vez maldice y bendice a su familia, pues aunque se le ha otorgado la condición de nomarca, también se le ha encomendado llevar a cabo el proyecto de construcción más ambicioso jamás emprendido en nuestra tierra.   @PEl lugar de descanso eterno del Faraón será un enorme complejo piramidal, situado lejos de cualquier ciudad, en la meseta frente a Giza. Su sarcófago será de granito macizo, y su barca funeraria, de cedro libanés de gran calidad. Junto al complejo piramidal del Faraón se construirá también una pirámide más pequeña para su hijo, el príncipe Kefrén, cuya tiranía rivaliza con la de su padre, aunque sus logros no. Kefrén también declara que su imagen sea tallada en la roca viva de Giza, en una gigantesca figura llamada 'esfinge', con cuerpo de león y cabeza de hombre. @PPara sostener el enorme esfuerzo constructivo necesario para completar este monumento, deberá establecer un gran asentamiento en Giza. Por ello, las condiciones allí no serán demasiado refinadas, pues su objetivo es únicamente completar estas tres grandes obras y honrar al Faraón.   @PSe le proporcionará parte de la fina caliza blanca necesaria para el revestimiento exterior de estas pirámides, pero también deberá comprar gran parte de lo que necesite con los fondos de la propia ciudad. @PEl Faraón le encomienda, a usted, uno de sus nomarcas reales, estas tres tareas sagradas. Debe demostrar una dedicación inquebrantable al Faraón y cumplir sus deseos... cueste lo que cueste."
        }
    }
    message_mission_bahariya_oasis {
        id: 419,
        type: 3,
        size [40, 30]
        title {
            text: "Oasis de Bahariya",

        }
        subtitle {
            text: "El desierto Occidental",

        }
        content {
            text: "@PLos reinados de Keops y Kefrén han llegado a su fin, y con ellos también la cuarta dinastía de familias gobernantes egipcias. Pero la dama Jentkaus, miembro lejano de esta familia, ha dado a luz a un nuevo faraón llamado 'Userkaf', y así la línea real continúa sin interrupción. Con Userkaf comienza la quinta dinastía, una era que promete grandes cambios.   @PUserkaf ha descentralizado en cierta medida el gobierno de nuestro país y ha concedido más poder a las autoridades locales. Ahora los nomarcas como usted son libres de gestionar sus propios asuntos. El Faraón no intentará la construcción de una tumba colosal que lo albergue por la eternidad, pues tiene otro proyecto en mente para usted. @PEl Faraón ha declarado a Ra, dios del sol y del reino, Rey de los Dioses, y pretende proclamar su soberanía por toda la tierra. Muchos templos solares ya salpican el paisaje egipcio, pero el Faraón desea extender la influencia de Ra hasta el mismísimo confín de nuestro reino. @PPara lograrlo, debe construir un asentamiento fortificado en el oasis de Bahariya, muy adentro del desierto Occidental. Use sabiamente el agua que pueda encontrar allí, pues lo poco que hay tan lejos del preciado Nilo suele ser codiciado por las fieras del desierto. También debe estar atento a los ataques de guerreros libios y de beduinos del desierto, que últimamente han asolado las caravanas. Planifique sus defensas con cuidado y aproveche los recursos que pueda encontrar en el oasis, como la madera y la caza."
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
            text: "El templo del sol",

        }
        content {
            text: "@PLos reinados de Keops y Kefrén han llegado a su fin, y con ellos también la cuarta dinastía de familias gobernantes egipcias. Pero la dama Jentkaus, miembro lejano de esta familia, ha dado a luz a un nuevo faraón llamado 'Userkaf', y así la línea real continúa sin interrupción. Con Userkaf comienza la quinta dinastía, una era que promete grandes cambios.   @PUserkaf ha descentralizado en cierta medida el gobierno de nuestro país y ha concedido más poder a las autoridades locales. Ahora los nomarcas como usted son libres de gestionar sus propios asuntos. El Faraón no intentará la construcción de una tumba colosal que lo albergue por la eternidad, pues tiene otro proyecto en mente para usted. @PEl Faraón ha declarado a Ra, dios del sol y del reino, Rey de los Dioses, y pretende proclamar su soberanía por toda la tierra. Muchos templos solares ya salpican el paisaje egipcio, pero el Faraón desea que el más grande se encuentre en Abusir, en la húmeda región del Delta del Bajo Egipto. @PComo la mayor parte del Delta, Abusir es rica en caza, peces y otra fauna y vegetación, pero ofrece pocos recursos minerales. Por ello, la arenisca necesaria para la construcción del templo solar deberá importarse de las canteras del oasis de Dunqul. Aquí pueden criarse rebaños para obtener carne, aunque necesitan mucha paja como forraje. @PDeberá despejar terreno para crear un emplazamiento adecuado para el templo solar. Asegúrese de vender suficiente de la preciosa madera que pueda cosechar primero, pues una vez agotada puede que no pueda obtener más. Apolinópolis y Abydos siempre necesitan madera, y también caza, así que el comercio con ellas debería ayudar a compensar el coste de construir este monumento sagrado."
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
            text: "La amenaza kushita",

        }
        content {
            text: "@PPepi ha subido al trono y ha concedido a su familia el rango de Canciller, pero ello tiene un precio.    @PLa autoridad centralizada sigue erosionándose, a medida que los líderes locales y regionales ganan poder. Las cosechas en algunas regiones son muy inferiores a lo normal, y el espectro de la hambruna ha empezado a aparecer en Egipto.  Menfis, antaño una ciudad espléndida y hermosa, empieza a decaer.  Los videntes predicen tiempos difíciles por venir. @PLos poderosos vecinos se están movilizando para aprovechar la creciente debilidad de Egipto.  El puesto avanzado de Buhen está sitiado por soldados kushitas sin miedo, enviados desde Kerma, la ciudad más grande de África que no es egipcia.  Los kushitas exigen tributo, y la menor provocación podría desencadenar un ataque abierto. Nubia también ha llamado a la guerra y busca recuperar las tierras perdidas.  @PSi Egipto quiere sobrevivir, debe hacer cuanto esté en su mano para conservar las rutas comerciales que permiten que los bienes entren y salgan de Egipto. Mantenga abierto el puesto comercial del oasis de Selima, conseguido con gran esfuerzo.  Pepi, anticipando su viaje al más allá, hará frecuentes peticiones de piedra para construir su pirámide, y otras ciudades, escasas de alimentos, buscarán sustento en usted. @PUse sus recursos con prudencia.  La valiosa madera abunda en el oasis, pero hay que talar parte del bosque para acceder al limitado suministro de agua."
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
            text: "La ruta de las caravanas",

        }
        content {
            text: "@PPepi ha subido al trono y ha concedido a su familia el rango de Canciller, pero ello tiene un precio.   @PLa autoridad centralizada sigue erosionándose a medida que los líderes locales y regionales ganan poder. Las cosechas en algunas regiones son muy inferiores a lo normal, y el espectro de la hambruna ha empezado a aparecer en Egipto.  Menfis, antaño una ciudad espléndida y hermosa, empieza a decaer.  Los videntes predicen tiempos difíciles por venir.  @PNuestros poderosos vecinos se están movilizando para aprovechar nuestra creciente debilidad.  Nuestro puesto avanzado de Buhen está sitiado por soldados kushitas sin miedo, enviados desde Kerma, la ciudad más grande de África que no es egipcia.  Los kushitas exigen tributo, y la menor provocación podría desencadenar un ataque abierto.  Nubia también ha llamado a la guerra y busca recuperar las tierras perdidas.  @PIntente mantener la estabilidad de Egipto estableciendo un puesto administrativo en el oasis de Dakhla.  El oasis tiene una gran extensión de árboles valiosos, pero por desgracia estos árboles bloquean el acceso al limitado suministro de agua del oasis.  Desde este lugar tan importante, importe ébano del interior de África.  Pepi, anticipando su viaje al más allá, pedirá ladrillos para la construcción de su monumento.  Otras ciudades, escasas de alimentos, le pedirán sustento."
        }
    }
    message_mission_thinis {
        id: 423,
        type: 3,
        size [40, 30]
        title {
            text: "Tinis ",

        }
        subtitle {
            text: "Guerra civil",

        }
        content {
            text: "El antiguo modo de vida ha desaparecido, y la mayoría teme que Egipto nunca recupere su antigua gloria.  Osiris ha vuelto la espalda a su pueblo, y una serie de crecidas insuficientes ha provocado una hambruna generalizada.  El poder de los faraones, antaño incuestionable, se ha desvanecido, sustituido por líderes provinciales que solo se disputan el poder. @PDe este caos han surgido dos nobles familias que intentan hacerse con el control del país.  Los gobernantes de Heracleópolis reclaman el trono como legítimos herederos.  Son especialmente crueles y hacen poco por aliviar el hambre del pueblo.  Al sur, una nueva familia, la casa de Intef, ha ascendido al poder en Tebas.  Esta familia ha hecho mucho por reunificar el sur, y ahora Heracleópolis se ha enfrentado a Tebas en una guerra civil mortal por el control de todo Egipto. @PPara demostrar su benevolencia hacia el pueblo de Egipto, los Intef le han encomendado la reconstrucción de la recién conquistada ciudad de Tinis, una de las más antiguas de Egipto.  Dos de los edificios más hermosos y antiguos de Tinis han sobrevivido a la agitación de la conquista: el complejo del templo de Osiris y la mansión.  Los Intef han decretado que, si cualquiera de estos edificios fuera destruido, no se malgastará ningún fondo en su restauración.  Los gobernantes tebanos consideran la restauración de Tinis una prioridad absoluta y han reunido fondos considerables, incluso en estos tiempos de disputa, para este fin.  Devuelva a Tinis su antiguo esplendor, encargue una armada y reclute un ejército fuerte para defenderla de los frecuentes ataques de los leales a Heracleópolis, incluidas las ciudades de Licópolis, Hieracómpolis y Hermópolis.  Tenga cuidado con los gobernantes de Heracleópolis: podrían exigir tributo para comprobar si su lealtad, y sus debens, pueden ser extorsionados.  Vigile también a los nubios oportunistas que buscan aprovecharse de las luchas internas de Egipto."
        }
    }
    message_mission_thebes {
        id: 424,
        type: 3,
        size [40, 30]
        title {
            text: "Tebas",

        }
        subtitle {
            text: "Guerra civil",

        }
        content {
            text: "El antiguo modo de vida ha desaparecido, y la mayoría teme que Egipto nunca recupere su antigua gloria.  Osiris ha vuelto la espalda a su pueblo, y una serie de crecidas insuficientes ha provocado una hambruna generalizada.  El poder de los faraones, antaño incuestionable, se ha desvanecido, sustituido por líderes provinciales que solo se disputan el poder. @PDe este caos han surgido dos nobles familias que intentan hacerse con el control del país.  Los gobernantes de Heracleópolis reclaman el trono como legítimos herederos.  Son especialmente crueles y hacen poco por aliviar el hambre del pueblo.  Al sur, una nueva familia, la casa de Intef, ha ascendido al poder en Tebas.  Esta familia ha hecho mucho por reunificar el sur, y ahora los gobernantes de Heracleópolis se enfrentan a los gobernantes de Tebas en una guerra civil mortal por el control de todo Egipto. @PLos Intef, ocupados en combatir a los gobernantes de Heracleópolis, le han encomendado el desarrollo de su ciudad natal, Tebas.  Si los Intef quieren vencer en su lucha contra los gobernantes heracleopolitanos y consolidar su reputación en Egipto, Tebas debe ser un referente en el que otras ciudades puedan confiar, ofreciendo ayuda o soldados a quienes la soliciten.  Tebas, que podría convertirse en la capital si los Intef vencen, debe ser una gran ciudad.  Con los escasos recursos a su disposición, construya un templo del sol y una pirámide para mostrar a los egipcios la gloria de los Intef. @PTebas no es inmune a los ataques.  Los gobernantes heracleopolitanos, y quienes les son leales, pueden amenazar su ciudad de vez en cuando, y Heracleópolis podría intentar extorsionar debens del tesoro de su ciudad.  Para defenderse de estos considerables riesgos, construya un ejército y una armada fuertes que protejan su ciudad y acudan en defensa de otras ciudades amenazadas."
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
            text: "Reunificación",

        }
        content {
            text: "Los servicios de su familia durante la guerra civil no han quedado sin recompensa.  Yo, el faraón Mentuhotep, he concedido a su familia el rango de visir.  No hay nadie en todo Egipto en quien confíe más que en usted.  Ahora que los dos reinos de Alto y Bajo Egipto están reunidos y la capital, Tebas, prospera, necesito que me ayude a consolidar mi posición en todo el reino. @PAunque reunificado, Egipto es propenso a escaramuzas internas, sobre todo en zonas que antes fueron leales a los gobernantes de Heracleópolis.  Para ayudar a consolidar nuestra nueva unión, quiero que reconstruya y defienda Coptos.  Coptos debe ser una ciudad gloriosa que muestre a los ciudadanos de Egipto lo que es posible bajo mi gobierno.   La ciudad sufre ataques frecuentes de las ciudades que aún son leales a los antiguos gobernantes, como Hermópolis, y debe asegurarse de defender sus fronteras. @PLa hambruna sigue azotando el país, y otras ciudades del reino le pedirán comida con frecuencia.  Responda lo antes posible a sus desgarradoras súplicas, para que todo Egipto conozca mi benevolencia y la dedicación de mi visir más leal. @PSé que le pido mucho, pero no hay nadie más en Egipto capaz de realizar esta difícil tarea."
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
            text: "Reunificación",

        }
        content {
            text: "Los servicios de su familia durante la guerra civil no han quedado sin recompensa.  Yo, el faraón Mentuhotep, he concedido a su familia el rango de visir.  No hay nadie más en Egipto en quien confíe más que en usted.  Ahora que los dos reinos de Alto y Bajo Egipto están reunidos y la capital, Tebas, prospera, necesito que me ayude a consolidar mi posición en todo el reino. @PAunque reunificado, Egipto es propenso a escaramuzas internas, sobre todo en zonas que antes fueron leales a los gobernantes de Heracleópolis.  Para ayudar a consolidar el país recién reunificado, quiero que reconstruya y defienda Beni Hasan, que estuvo a punto de ser destruida durante la guerra civil.  Beni Hasan debe ser una ciudad gloriosa que muestre a los ciudadanos de Egipto lo que es posible bajo mi gobierno.   @PLa hambruna sigue azotando el país, y otras ciudades del reino le pedirán comida con frecuencia.  Responda lo antes posible a sus desgarradoras súplicas, para que todo Egipto conozca mi benevolencia y la dedicación de mi visir más leal. @PTengo una petición más, noble: quiero que construya obeliscos de granito para proclamar aún más todo lo que he hecho por esta tierra durante mi vida. @PSé que le pido mucho, pero también sé que es el único en Egipto capaz de hacer lo que le pido."
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
            text: "Se funda una nueva capital",

        }
        content {
            text: "¡Oh, poderoso faraón, amado de Ra, cuánta fortuna debe sentir!  Su ascenso sin precedentes al trono de Egipto es material de sueños. Ni los dioses ni los hombres podrían forjar una recompensa mayor. Con la llegada de su familia al poder, Egipto puede empezar de nuevo, y quizá todos podamos olvidar los horrores de la guerra civil. @PPara marcar este nuevo comienzo, debe construir una magnífica nueva capital.  Itjtawy, con sus abundantes recursos naturales, es un emplazamiento perfecto.  Aprovechando lo que la tierra ofrece, podrá levantar una ciudad espléndida, digna del valor y la dedicación de su dinastía. @PPara que las hazañas de su gran dinastía se recuerden siempre, debe construir dos majestuosas pirámides de ladrillo para usted y su familia, y una temible esfinge que guarde su tumba.  Una familia con sus logros no merece menos. @PSin embargo, tenga en cuenta que algunos en el país cuestionan la legitimidad de su gobierno.  Muchos siguen sufriendo los efectos de la hambruna y murmuran que usurpó el trono.  Si alivia su miseria y les ayuda a reconstruir sus hogares, se ganará sin duda su lealtad eterna.  Procure atender a sus nuevos súbditos lo mejor que pueda, para evitar que estas desafortunadas personas tomen las armas contra usted."
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
            text: "Hacia Nubia",

        }
        content {
            text: "Ahora que Egipto está firmemente unido bajo su gobierno, toda su corte y yo, su visir de confianza, recomendamos extender las fronteras de nuestro país hacia el sur, en Nubia.  El lecho seco del río en Allaqi es rico en vetas de oro, y una poderosa ciudad en Mirgissa, con usted como residente, sin duda disuadirá a los nubios de atacar.  Sin embargo, tenga cuidado con los kushitas.  Son un adversario mucho más peligroso que los nubios y usarán sus espadas para animarle, oh faraón, a dejar en paz su reino. @PPara dejar una huella duradera en Nubia, debe erigir un gran obelisco que atestigüe los muchos logros de Egipto.  El obelisco ofrecerá a los nubios pruebas convincentes de los beneficios del gobierno egipcio, y será un recordatorio constante de nuestra presencia. @PMientras su atención directa se centra en Mirgissa, no olvide nuestra intención de establecer una próspera ciudad portuaria en el mar Rojo, en Mersa.  Mersa necesitará su ayuda y no dudará en pedirla.  Si Mersa prospera, proveerá a Mirgissa del cobre tan necesario, con el que se pueden forjar armas."
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
            text: "A orillas del mar Rojo",

        }
        content {
            text: "Ahora que Egipto está firmemente unido bajo su gobierno, debemos desarrollar relaciones comerciales con ciudades de todo el mundo para aumentar la riqueza de Egipto, oh rey de las Dos Tierras.  @PA medida que su pueblo prospera, exige artículos más exóticos.  Cansado de las joyas, un artículo de lujo fácil de obtener, su pueblo desea bienes de lujo raros y caros, como el incienso.  Su corte y yo, su visir de confianza, recomendamos que establezca un puerto en el mar Rojo, en Mersa.  Mersa ofrece una ruta comercial hacia el lejano Punt, de donde puede importarse el mejor incienso del mundo, aunque a un coste elevado.   @PAdemás de modestas vetas de oro y mineral de cobre, Mersa produce pocas materias primas propias, pero puede prosperar como fabricante de productos acabados.  Importando materias primas de sus socios comerciales y exportando productos terminados, Mersa podrá obtener un buen beneficio. @PMientras usted se ocupa de establecer Mersa, uno de sus nomarcas más valientes está fundando un nuevo centro comercial en Nubia.  Su ciudad, Mirgissa, probablemente sufrirá ataques, así que mi querido faraón debe estar preparado para enviarle los recursos que necesite. @PBajo su gobierno, Mersa será sin duda una de las ciudades más hermosas del reino, adecuada como lugar de descanso final para usted y su familia.  Mientras establece el próspero puerto, no descuide los preparativos para el más allá.  Un mausoleo y una pequeña pirámide de ladrillo proporcionarán un alojamiento suntuoso a usted y su familia tras su paso al Campo de Juncos."
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
            text: "El desafío",

        }
        content {
            text: "¡Respetado faraón, todo por lo que su familia ha luchado tanto está amenazado!  La armada nubia patrulla el Nilo, penetrando en lo profundo del territorio egipcio y saqueando tanto aldeas como ciudades.  Los nubios también abordan barcos mercantes y se apropian de sus mercancías.   Para ayudar a sus ciudades del norte a repeler al enemigo, debe estar preparado para enviar barcos de guerra y soldados a las ciudades que los necesiten.   @PPara impedir que los nubios vuelvan a navegar por nuestras aguas, sus asesores militares recomiendan construir un conjunto de fortalezas en Semna, entre la segunda y la tercera catarata del Nilo.  Las fortalezas actuarán como un tapón, encerrando a los nubios al sur.   @PExpulsar con éxito a los nubios depende de conquistar la ciudad de Kuban.  Kuban es rica en recursos, y tomarla paralizará la economía nubia.  Una vez arrebatado el control de Kuban a los nubios, podrá empezar a importar arenisca de la ciudad para su gran mausoleo.  Su mausoleo en Semna servirá de recordatorio de su dominio sobre los indómitos nubios.   @PHay muchos desafíos ante usted mientras protege Egipto de los nubios.  Preste atención, oh Horus Viviente, a la tormenta que se levanta en el este.  El estruendo de los cascos de los caballos se oye por todo Canaán, y carros veloces como el rayo arrasan todo a su paso.  Estos formidables carros, como nunca se han visto en ningún otro lugar, son conducidos por los guerreros hicsos.  Ya se han divisado nubes de tormenta en el horizonte egipcio, y debe prepararse para el peligro inminente."
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
            text: "La ciudad de Bastet",

        }
        content {
            text: "Real faraón, con las rutas comerciales firmemente establecidas, debemos mostrar ahora a Egipto lo que el éxito y la riqueza pueden traer.  Bubastis es el emplazamiento perfecto para tal ciudad: podemos proteger nuestras valiosas rutas comerciales hacia el este mientras rendimos homenaje a Bastet, que ha velado por Egipto. @PLa ciudad de Bastet debe ser como ninguna otra en Egipto.  Debe ser tan hermosa como la flor de loto, floreciendo con espectáculos, escuelas, bibliotecas y lugares de culto.  Sus ciudadanos deben estar bien abastecidos de los bienes más finos, incluido el incienso importado.  Una vez terminada, Bubastis será la joya de las dos coronas. @PMientras construye esta gloriosa ciudad, preste atención a la tormenta que se levanta en el este.  El estruendo de los cascos de los caballos se oye por todo Canaán, y carros veloces como el rayo arrasan todo a su paso.  Estos formidables carros, como nunca se han visto en ningún otro lugar, son conducidos por los guerreros hicsos.  Ya se han divisado nubes de tormenta en el horizonte egipcio, y debe prepararse para el peligro inminente."
        }
    }
    message_mission_hermopolis {
        id: 432,
        type: 3,
        size [40, 30]
        title {
            text: "Hermópolis",

        }
        subtitle {
            text: "Egipto recuperado",

        }
        content {
            text: "Poderoso faraón, Egipto clama por su ayuda.  Los amenazantes hicsos han invadido nuestra tierra y han establecido su propia capital en Avaris.  Desde Avaris, han interrumpido muchas de nuestras rutas comerciales, asfixiando los suministros necesarios.  Debemos detener su conquista antes de que sea demasiado tarde. @PSi os place, gran faraón, debemos recuperar la ciudad de Hermópolis, que han profanado estos inmundos invasores.  También debemos construir un ejército y una armada fuertes, pues quizá tengamos que suministrar tropas y armas a nuestros compatriotas del norte, especialmente en Avaris, para ayudar a repeler la incursión hicsa.  Ellos buscarán su apoyo, hijo de Ra.  Pero ahora también disponemos de un arma nueva.  Nuestros sabios líderes militares se han hecho expertos en el temido carro, y lo volveremos contra nuestros enemigos para expulsarlos ante nosotros.  Una vez expulsados los problemáticos hicsos, nuestros asesores militares recomiendan construir una fortaleza en el Sinaí, en Sharuhen, para impedir nuevas invasiones desde el este. @PSi nuestros problemas se limitaran al norte... Los informes de nuestra frontera sur muestran que los nubios vuelven a aprovecharse de un Egipto distraído.  Han recuperado las ciudades meridionales de Mirgissa y Semna.  Aunque estas ciudades perdidas son motivo de preocupación, primero debemos expulsar a los hicsos antes de volcar nuestra atención hacia el sur. @PEstos hicsos son invasores profundamente impíos.  Acabamos de descubrir que han profanado la pirámide de aquí, en Hermópolis.  Han robado de la pirámide todas las provisiones funerarias que el poderoso faraón enterrado aquí necesita en el Campo de Juncos.  Debemos proporcionar un nuevo suministro de ajuar funerario para que el faraón enterrado aquí pueda disfrutar de la vida eterna."
        }
    }
    message_mission_lykopolis {
        id: 433,
        type: 3,
        size [40, 30]
        title {
            text: "Licópolis",

        }
        subtitle {
            text: "Egipto recuperado",

        }
        content {
            text: " Oh rey de las Dos Tierras, Egipto clama por su ayuda.  Los amenazantes hicsos han invadido nuestra tierra y han establecido su propia capital en Avaris.  Desde Avaris, han interrumpido muchas de nuestras rutas comerciales.  Debemos detener su conquista antes de que sea demasiado tarde. @PAquí, en Licópolis, estamos a salvo de un ataque inmediato, aunque los hicsos tienen la osadía de exigir tributo. Quizá debamos suministrar tropas y armas a nuestros compatriotas del norte para ayudar a repeler la incursión hicsa.  Ellos buscarán su apoyo, oh poderoso faraón.  Pero ahora también disponemos de un arma nueva: nuestros sabios líderes militares se han hecho expertos en el temido carro, y lo volveremos contra nuestros enemigos para expulsarlos ante nosotros. @PSi nuestros problemas se limitaran al norte... Los informes de nuestra frontera sur muestran que los nubios vuelven a aprovecharse de un Egipto distraído.  Han recuperado las ciudades meridionales de Mirgissa y Semna. @PSi Egipto quiere salir intacto de estos tiempos turbulentos, mucho se exigirá a sus generales en el campo y en el río.  Para inspirar a sus dos mejores generales, les ha prometido construir a cada uno una pirámide tan espectacular como la suya.  Guardando su promesa en el corazón, combaten con fiereza contra el enemigo, invocando toda su fuerza y su vigor.   @PSi os place, poderoso faraón, debe construir tres magníficas pirámides en Licópolis, una para usted y otra para cada uno de sus generales.  Estas tres pirámides ocuparán un espacio considerable, por lo que deberá sacrificar algunos recursos valiosos para acomodarlas.  Quizá también necesite extender su ciudad al otro lado del Nilo para disponer de todos los recursos necesarios para que esta ciudad prospere."
        }
    }
    message_mission_byblos {
        id: 434,
        type: 3,
        size [40, 30]
        title {
            text: "Biblos",

        }
        subtitle {
            text: "Expansión y conquista",

        }
        content {
            text: "Egipto ha salido de sus recientes problemas con una fuerza renovada.  ¡Biblos, con sus bosques verdes y sus ricas fuentes de cobre, es nuestra!  Con su presencia, la ciudad seguro que prosperará, y se establecerá un Nuevo Reino. @PAh, pero ¡qué descubrimiento tan alarmante hicimos tras conquistar Biblos!  Un pueblo nuevo y feroz, los hititas, se ha extendido por gran parte de Asia, y algunos dicen que su imperio rivaliza con el nuestro en tamaño.  Ahora han puesto sus ojos en Biblos, codiciosos de sus riquezas.  Si no nos preparamos bien para su ataque, podríamos perder Biblos ante nuestro enemigo.  @PMientras nos preparamos para hacer frente a los hititas, debemos dejar claro que Biblos es egipcia para siempre.  Con su bendición, oh faraón, erigiremos una serie de tres obeliscos, dos pequeños y uno grande, que proclamen su soberanía y su fama por los lejanos confines de su imperio.  Estos imponentes monumentos recordarán a los habitantes de Biblos a quién deben su lealtad. @PMientras nos ocupamos de los asuntos de Biblos, otras regiones de Egipto siguen expuestas a ataques.  Los nubios han avanzado hacia el norte hasta la primera catarata, y debemos ayudar a nuestros compatriotas a expulsarlos.  Los informes de Avaris hablan de otro enemigo misterioso, los Pueblos del Mar.  Ambos enemigos deben ser sometidos con firmeza si Egipto quiere alcanzar la gloria.  Para mostrar su poderío, asegúrese de enviar tropas y barcos de guerra cuando se los soliciten."
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
            text: "La gloria de Egipto",

        }
        content {
            text: "Con los hicsos expulsados con éxito de nuestro país, nuestra tierra está madura para renacer, un Nuevo Reino que eclipse la gloria pasada.  Noble faraón, Kuban es un lugar ideal para comenzar este Nuevo Reino.  Podemos usar la gran cantidad de oro que se encuentra allí para financiar su nueva visión de Egipto.  @PMientras Egipto está al borde de la grandeza, persisten algunos problemas molestos.  Muchas ciudades egipcias todavía se recuperan de los trastornos causados por los hicsos y quizá necesiten la ayuda del faraón.  En otras regiones, nuestros viejos enemigos siguen atacándonos, y un enemigo nuevo, los Pueblos del Mar, ha estado saqueando nuestra costa norte. Debe estar preparado para defender otras ciudades egipcias de nuestros enemigos, viejos y nuevos. @PA medida que Egipto crece en prestigio, muchas ciudades están dispuestas a comerciar.  Algunas de ellas conocen tan bien nuestras costumbres, y están tan impresionadas por su poder, que se consideran egipcias, mientras que otras nos son extrañas y comercian con nosotros por primera vez.  Por la gloria de Egipto, aproveche todas estas relaciones para proporcionar a su pueblo todos los bienes que desea. @PPara dar la bienvenida a la nueva era, sus arquitectos reales anhelan la oportunidad de construir dos pirámides y un majestuoso mausoleo para usted, oh faraón. Sin duda reflejarán la riqueza y la grandeza que ha traído a Egipto."
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
            text: "Los Pueblos del Mar",

        }
        content {
            text: "Oh Horus de Oro, nuestro dominio sobre Asia es firme e incontestable, y nuestras fronteras vuelven a extenderse profundamente en Nubia.  Pero los problemas en nuestra costa norte van en aumento.  Los Pueblos del Mar se han vuelto cada vez más agresivos, saqueando nuestras ciudades sin control.  Solo la presencia del faraón bastará para derrotar a este adversario feroz y astuto.  Si encarga una armada, respaldada por un ejército fuerte, sin duda venceremos a los Pueblos del Mar.   @PMientras trabaja para derrotar a los Pueblos del Mar, sus valientes nomarcas dirigen ataques por todo el mundo.  Si tienen éxito, Egipto gobernará el mundo desde el gran río Éufrates, en Asia, hasta la extensa ciudad kushita de Kerma, al sur.  Cuando usted y sus nomarcas hayan alcanzado la dulce victoria, su dinastía quedará registrada como la mayor que jamás haya velado por Egipto. @PDando fe de su influencia lejana, tenemos un nuevo socio comercial distante, Micenas.  El rey de Micenas ha oído hablar del esplendor y la abundancia de Egipto, y desea comerciar con nosotros.  Si acepta abrir esta ruta comercial, oh faraón, sus ciudadanos recibirán sin duda bienes exóticos como nunca antes han visto. @PPara albergar a su familia real en el más allá, deben construirse un par de imponentes mausoleos y una impresionante pirámide de ladrillo.  Estos monumentos recordarán a todos los que vengan después sus hazañas, tanto en el campo de batalla como fuera de él."
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
            text: "La gloria del faraón",

        }
        content {
            text: "Benévolo faraón, ha traído paz y prosperidad a nuestra nación.  Bajo su sabio y capaz gobierno, Egipto es de nuevo un país fuerte y glorioso.  Todos los nomarcas le son leales, y ya no quedan amenazas para nuestra gran nación. @PHabiendo cumplido todo lo que su familia se propuso hace tantos años, ha llegado el momento de conmemorar los logros de su gran dinastía.  La única manera de lograrlo es construir la pirámide más grandiosa que Egipto haya conocido jamás, una pirámide aún mayor que la de Keops, en Giza.  Otros miembros de su noble familia han sacrificado mucho en el largo camino hacia su gobierno de Egipto.  Ellos también deben ser recordados y honrados, con un mausoleo de arenisca que reconozca su apoyo inquebrantable.   @PEl emplazamiento ideal para estos monumentos es Kahun, en la rica región del Fayum.  Desde allí podrá atender todos los asuntos de Estado, y responder a las peticiones de suministros que sus ciudades le hagan, mientras construye su gran pirámide."
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
            text: "@PCon la ayuda de su familia, el rey tinita Hor-Aha ha unido con éxito los dos reinos de Alto y Bajo Egipto, se ha proclamado faraón de todo Egipto y ha fundado una imponente capital en Menfis.    @PSu clan se ha trasladado una vez más, esta vez a la húmeda región del Delta del Bajo Egipto, a una zona conocida como Buto. Los barcos de guerra cananeos han estado amenazando esta región, y probablemente tendrá que enviar algunos barcos de guerra propios cuando llegue el momento. @PSu familia ha alcanzado la condición de nobleza. Por ello, se espera que, antes de pasar de este mundo al siguiente, emprenda la construcción de una exquisita tumba de ladrillo, una mastaba, que albergue su cuerpo en su viaje al más allá. @PSin embargo, primero debe establecer granjas a orillas del Nilo, para aprovechar la rica y fértil tierra que deposita la Inundación anual del río. Esto permitirá que su población crezca y prospere, y que con el tiempo sea lo bastante numerosa para completar este monumento sagrado. Pero cuidado, pues muchos peligros acechan entre las aguas que dan vida al Nilo, como cocodrilos mortales, hipopótamos y mosquitos portadores de malaria. @L@L Agricultura a orillas del Nilo @PDebe construir granjas directamente en la llanura aluvial, para obtener los beneficios de su mayor fertilidad. A diferencia de la mayoría de las estructuras productivas, las granjas en la llanura aluvial no necesitan acceso directo a empleados, pero sí una mano de obra constante de campesinos, suministrada por los campamentos de trabajo, que cuide sus campos. Construya los campamentos de trabajo bastante cerca de las granjas de la llanura aluvial, para que los campesinos no tengan que caminar demasiado para llegar a ellos. @G56 @L@PCada año el Nilo inunda sus orillas, reponiendo el suelo agotado de la llanura aluvial con barro rico y fértil.  Los campesinos recogen la cosecha anual justo antes de la Inundación y la entregan a sus graneros.  Como solo hay una cosecha al año, asegúrese de tener graneros suficientes para almacenar una cantidad adecuada de alimentos para su población en crecimiento."
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
            text: "La tierra de los Pueblos del Mar",

        }
        content {
            text: "@PLos rumores de angustia y descontento del oeste se han vuelto recientemente más amenazadores.  Los exploradores informan de que varias tribus bárbaras, que hablan lenguas extrañas, han llegado a las costas de Cirenaica, al oeste.  Para empeorar las cosas, estos pueblos caminan ahora de la mano de Maraye, hijo de Did, rey de los libios y enemigo del Faraón.   @PLa noticia ha llegado ya al faraón Merneptah de que estas viles gentes, con todas sus mujeres, niños y posesiones terrenales pisándoles los talones, pronto se dirigirán hacia el este, hacia el fértil delta del Nilo, ¡nuestra patria!, en busca de un lugar donde asentarse.  Ya ha habido pequeños enfrentamientos en los oasis septentrionales de Siwi y Farafra.  Tu ciudad del delta, Pi-yer, es ahora la que se interpone en su camino.  Dentro de poco, esta lenta banda de salvajes podría estar a las puertas de tu ciudad.  ¡El Faraón ha decretado que, si llegan, no se les debe permitir penetrar más allá! @PNecesitarás importar madera con la que construir robustas naves de guerra, y cobre para las armas.  Es tu fortuna que los hititas, antes problemáticos, ahora se mantengan en paz gracias a la gran victoria de Ramsés II en Qadesh, padre del amado Merneptah.  Haz que tu ciudad sea fuerte y prepara a tus leales tropas para el combate a muerte."
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
            text: "Repeler a los asirios",

        }
        content {
            text: "@PDesde los días del gran Shabaka, unificador del Alto y el Bajo Egipto y padre del faraón Taharqa, el conflicto con los agresivos asirios ha sido la norma.  Mientras vivió, el faraón Shabaka consideró oportuno ayudar a nuestros hermanos de Palestina, que se hallaban bajo el duro yugo de Asiria.  ¡Cuidado!  Los súbditos del rey pagano Asarhaddón vuelven a estar en marcha y, como siempre, sus ojos están puestos en las fértiles tierras de Egipto.  ¡Ahora te toca a ti alcanzar la gloria!  Como alcalde real de Migdol, se espera que defiendas la ciudad de la serie de ataques de estos malditos enemigos.  Situada en el borde oriental del delta del Nilo, tu fortaleza fronteriza se encuentra en primera línea de las defensas exteriores de Egipto. @PAdiestrar adecuadamente a tus soldados y establecer vínculos comerciales para asegurar armas, o las materias primas con las que fabricar las tuyas, será importante. @P¡No flaquees!  Una firme resistencia militar es vital para garantizar la independencia continuada de Egipto.  Si logras resistir apenas siete años, la victoria estará asegurada.  ¡Taharqa, el gran faraón, segundo hijo de Shabaka, os estará observando!"
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
            text: "Renacimiento de una armada",

        }
        content {
            text: "@PDurante muchas generaciones, los egipcios han sufrido bajo el cruel puño de Persia.  Sin embargo, el dominio de Babilonia sobre nuestras sagradas tierras ya no es tan fuerte como lo fue en otro tiempo.  Mientras nuestros malditos opresores estaban ocupados entrometiéndose en la política de Grecia, una serie de revueltas en Egipto ha logrado por fin aflojar el odiado yugo persa.  Sin embargo, ahora ha llegado al faraón Achoris la noticia de que una fuerza al mando del almirante de la flota Conón (un lacayo griego que recibe oro persa), enviada por Artajerjes II, se dirige a nuestras costas.  El faraón Achoris ha determinado sabiamente que se necesita una fuerte presencia naval en el Nilo para frustrar esta incursión.  Como gobernador real de Tanis durante los próximos diez años, debes construir naves robustas y entrenar a tropas valerosas para proteger los accesos por agua y por tierra. @PNecesitarás establecer una ruta comercial con Enkomi para importar madera resistente con la que construir una flota.  El cobre también puede importarse de Enkomi, en la isla de Chipre.  Esta ruta comercial es precaria en el mejor de los casos, ya que discurre cerca de la costa del Levante, bajo el control de nuestro enemigo.  Abastecer al faraón con los suministros necesarios debería ayudarte a complementar tus ingresos.   @PTen en cuenta que los fondos son escasos en estos tiempos difíciles.  Para triunfar, debes ser hábil en los negocios y el comercio, además de un comandante diestro."
        }
    }
    message_mission_alexandria_2 {
        id: 442,
        type: 3,
        size [40, 30]
        title {
            text: "Alejandría",

        }
        subtitle {
            text: "Alejandro Magno",

        }
        content {
            text: "@PEl gran Alejandro, hijo de Filipo II de Macedonia y azote del Imperio babilónico, bendijo las tierras de Egipto con su presencia.  Con su llegada, el último sátrapa persa corrupto huyó precipitadamente.  Tras sacrificar al toro Apis en Menfis, Alejandro fue aceptado como faraón.  ¡Todo el pueblo se regocija!  Antes de emprender su viaje hacia el oráculo de Amón en el oasis de Siwa, sin embargo, nuestro líder decidió fundar una nueva ciudad, que algún día desea que sea la capital de su vasto y creciente imperio.  En su infinita sabiduría, te ha designado primer alcalde de esta futura ciudad! @PEl gran Alejandro te ha concedido una generosa dotación de fondos con los que iniciar la construcción, y te ha dado los servicios del respetado arquitecto griego Dinócrates.  Dentro de apenas una docena de años, espera que hayas desarrollado el poderío comercial, cultural y militar de su ciudad hasta alcanzar altos niveles, pues ha prometido regresar.  @PNuestro líder incluso se ha tomado la molestia de trazar la posición de las dos calles principales de su ciudad.  La calle Canopo discurre en sentido este-oeste; la otra avenida principal es perpendicular a ella y se dirige tierra adentro, desde el cabo Lochias hacia el sur, en dirección al lago Mariut. @PComo supervisor de confianza de este proyecto, debes construir cuanto antes instalaciones portuarias y establecer rutas comerciales lucrativas.  Debería haber muchos clientes para nuestros productos, en especial trigo, cebada, papiro y lino.  No descuides, sin embargo, los aspectos culturales ni los militares de esta ciudad, pues todavía hay vándalos errantes que desean robar la riqueza de Egipto."
        }
    }
    message_mission_ptolemy_alexandria {
        id: 443,
        type: 3,
        size [40, 30]
        title {
            text: "La Alejandría de Ptolomeo",

        }
        subtitle {
            text: "Un faro de luz",

        }
        content {
            text: "@PEl legado de Alejandro Magno sigue vivo en nuestra orgullosa ciudad.  Aunque sus restos mortales descansan en el Mausoleo de Alejandría, su gran ciudad sigue prosperando.  Depende de ti, Ptolomeo I Soter, continuar la labor que comenzó el noble Alejandro.  Desde su fundación por Alejandro hace apenas 30 años, la ciudad se ha convertido en un poderoso centro comercial que abastece de alimentos básicos y artículos de lujo a gran parte de la región circundante.  Para impulsar su progreso económico y garantizar el paso seguro de los numerosos barcos que entran en el gran puerto, debes construir un enorme faro en la isla de Faros, cerca de la boca del puerto.  La luz de esta estructura guiará a los navegantes lejanos hasta el puerto con seguridad, evitando que encallen en sus traicioneros bajíos. @PPor importante que sea el comercio, no puedes ignorar el avance cultural e intelectual de nuestra sociedad.  Bajo tu liderazgo, Alejandría puede convertirse también en la capital intelectual del mundo conocido.  Reúne obras del saber de cerca y de lejos, y construye una gran Biblioteca donde conservarlas.  Tan seguro como que las hormigas se sienten atraídas por la miel, los eruditos de todas partes viajarán a este centro de saber y aprendizaje sin igual.   @PPara levantar estos grandes monumentos necesitarás importar un material de construcción, como el mármol blanco, adecuado para estas grandes estructuras.  Enkomi, en la isla de Chipre, es una buena fuente de este material.   @PPor último, no descuides tu ejército.  Siempre parece haber inquietud en un lugar u otro.  Puede ser necesario enviar tropas a las fronteras lejanas para proteger los intereses de Egipto y defender su honor."
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
            text: "César y Cleopatra",

        }
        content {
            text: "@PEl insolente zarpazo del Imperio romano se hace más fuerte y alcanza más lejos cada día que pasa.  Incluso las letales luchas de poder políticas de Roma han llegado a nuestra tierra.  Con el reciente asesinato de Pompeyo en las costas de Egipto, Julio César tiene ahora el control completo de las poderosas legiones de Roma y ha puesto sus ojos en las riquezas de Egipto, y en la belleza de nuestra cautivadora faraona, Cleopatra VII, hija de Ptolomeo XII Auletes.  Nuestra astuta líder, sin embargo, no se deja vencer fácilmente en el campo de batalla del ingenio.  Si César desea utilizarla como medio para aumentar la influencia de Roma en Egipto, ella también planea emplearlo como instrumento para mantener el poder dinástico de nuestra gran tierra. @PLa llegada de César a Alejandría con sus impopulares romanos ha provocado un levantamiento entre sus ciudadanos de espíritu independiente.  Una turba alborotada, incitada por el hermano menor de Cleopatra, Ptolomeo XIII, ha acorralado a César y a sus hombres en el barrio real de la ciudad.  Han estallado violentos combates callejeros que han causado numerosas bajas.  Para mantener abierta su ruta de escape por mar, César incendió la flota egipcia que estaba fondeada en el puerto de Alejandría.  Por desgracia, el incendio se extendió a algunos almacenes de la costa, quemando grandes cantidades de rollos de papiro pertenecientes a la Gran Biblioteca.   @PPara romper la trampa en la que se encuentra ahora, César ha convocado al leal Mitrídates y a sus tropas desde Siria para realizar su rescate.  Tras asaltar con éxito la fortaleza fronteriza de Migdol, Mitrídates ha hecho marchar a sus hombres a marchas forzadas alrededor del vértice del delta del Nilo para acercarse a Alejandría desde el sudeste.  Los elementos de vanguardia de esta fuerza acampan actualmente en las afueras de la pequeña aldea de Maritis, en la orilla oriental del lago Mariut, preparándose para la última etapa de su viaje. @PEl nefasto Ptolomeo XIII ha tenido noticia de la aproximación de estos refuerzos.  En respuesta, ha sacado la mayor parte de su numeroso ejército hacia el sudeste, fuera de Alejandría.  Una batalla decisiva está a punto de desencadenarse en la orilla oriental del lago Mariut.  ¿Podrás, al mando de las legiones romanas de Mitrídates, derrotar al ejército egipcio rebelde de Ptolomeo y abrirte paso hasta César y Cleopatra en Alejandría?  Su destino está en tus manos."
        }
    }
    message_mission_cleopatra_alexandria {
        id: 445,
        type: 3,
        size [40, 30]
        title {
            text: "La Alejandría de Cleopatra",

        }
        subtitle {
            text: "El legado de una reina",

        }
        content {
            text: "@PLa sangrienta muerte de César a manos de los puñales de sus asesinos sumió en el caos al mundo romano y te ha sumido a ti, nuestra faraona Cleopatra VII, en el dolor y el luto.  Se ha ido tu amante, tu mentor, tu confidente y tu poderoso aliado.  Octavio, su sobrino nieto adoptivo, adolescente, ha sido nombrado heredero, pero Marco Antonio, más experimentado y antes cónsul de César, se ha convertido en el jefe de estado nominal, para disgusto del joven Octavio.  No es de extrañar que el testamento de César no mencionara a tu hijo con él, Ptolomeo César, conocido popularmente como Cesarión.  Deseosa de seguridad para ti y para tu hijo, y como siempre con la intención de preservar el poder de Egipto, has abandonado Roma rumbo a Alejandría. @PA pesar de todas las leguas que separan Roma de ti, no puedes dejar atrás todas sus disputas internas.  Los hombres poderosos siguen luchando por el poder; tu apoyo y el acceso a las riquezas de Egipto serían un gran activo para cualquier facción.  Es fundamental que apoyes al vencedor en esta lucha por el poder, pues ponerte del lado del perdedor podría acabar fácilmente con Egipto.  El dramático enfrentamiento entre las facciones rivales de Roma tuvo lugar hace poco en Filipos, donde los cesarianos de Marco Antonio derrotaron de forma decisiva a las fuerzas de Bruto y Casio.  Antonio, Octavio y Lépido han repartido ahora el imperio para gobernarlo conjuntamente, y Antonio ha reclamado la parte oriental, que incluye Egipto. @PPoco después de la batalla, Marco Antonio te convocó para reunirte con él en Tarso, en Asia Menor, para que pudieras explicar mejor por qué habías tardado en unirte a los cesarianos.  Nada dispuesta a acudir como un perrito faldero, sabiamente te negaste a responder.  Después de todo, sabes mejor que nadie que es mucho mejor tratar con un romano según tus propios términos y condiciones, ¡y no según los suyos! @PAsí pues, tú, faraona Cleopatra, has regresado a casa, a Alejandría, a Egipto.  Ahora es el momento de engrandecer la gloria de esta magnífica ciudad, fundada por el gran Alejandro, cuya tumba todavía recibe visitantes.  La famosa Gran Biblioteca de Alejandría sigue atrayendo a eruditos de todo el mundo; la brillante luz del maravilloso Faro de Faros sigue encendida para que los navegantes puedan atravesar con seguridad las traicioneras aguas del puerto.  Ahora puedes enriquecer aún más la belleza de la ciudad construyendo el amplio Cesareo en honor a tu antiguo amante y a tu joven hijo.  Además, asegura tu propio tránsito al más allá construyendo otro mausoleo, para que puedas ser debidamente venerada tras tu viaje al Campo de los Juncos.   @PLa próxima vez que Marco Antonio te reclame, ¿quizá emplee un poco más de tacto?"
        }
    }
    message_mission_actium {
        id: 446,
        type: 3,
        size [40, 30]
        title {
            text: "Accio",

        }
        subtitle {
            text: "Antonio y Cleopatra",

        }
        content {
            text: "@P¡Oh noble faraona Cleopatra VII, consorte de César y ahora de Antonio!  El destino de Egipto está en tus manos, pero tus manos descansan ahora en las de un romano, Marco Antonio, y él está profundamente inmerso en la lucha por el control de Roma y de sus legiones.   @PNecesitando los inestimables recursos de Egipto, pero también deseando tu amor y tu afecto, Antonio accedió a tu exigencia de matrimonio.  Por desgracia, la noticia de esta nueva unión ha escandalizado a Roma.  Como sabías, Antonio seguía casado con Octavia, hermana de Octavio, heredero legal de César y, junto con Antonio, detentador conjunto del poderío de Roma.  Pero con las noticias de las costumbres polígamas de Antonio, esta relación se ha tensado gravemente.  Octavio cree que Antonio ha mancillado no solo el honor de su hermana y de su familia, sino también el prestigio de Roma.  Para resolver esta cuestión de honor y poner fin a la lucha por el control definitivo de Roma, Octavio ha desafiado formalmente a tu amante, Antonio, a un combate.  Con esto en mente, Antonio, acompañado por ti y por tu flota egipcia, ha encontrado en la península griega, cerca de Accio, un lugar para acampar.  El emplazamiento ofrece un buen puerto con numerosos atracaderos potenciales para tus naves.   @PDebes aumentar rápidamente tu poderío militar, en especial la fuerza naval.  Octavio ha jurado regresar en septiembre del año 31. @PAhora tu destino y el de Marco Antonio, así como el destino de Egipto y de Roma, dependen una vez más del rendimiento de vuestro poderío militar."
        }
    }
    message_mission_thutmose_valley {
        id: 447,
        type: 3,
        size [40, 30]
        title {
            text: "Tutmosis en el Valle",

        }
        subtitle {
            text: "La primera tumba",

        }
        content {
            text: "@PTras muchas brillantes victorias en lejanos campos de batalla en defensa de las tierras y del pueblo de Egipto, el faraón Tutmosis, como todos deben hacer algún día, ha dirigido sus pensamientos a los preparativos de su viaje al más allá.  Para asegurar que este viaje sea un éxito, el faraón desea que comiences cuanto antes la construcción de su tumba.  Establece una aldea en la orilla occidental del Nilo para disponer de un grupo de trabajadores capacitados.  Localiza un lugar adecuado para su tumba en los acantilados al oeste de la aldea.  Necesitarás canteros expertos para excavar en la roca las numerosas cámaras de la tumba, y artesanos talentosos para enlucir y pintar las estancias.   @PPara iluminar a los trabajadores que laboren en las zonas más recónditas de la tumba, necesitarás establecer talleres de lamparistas.   Abastece a los lamparistas con cerámica y aceite importado como combustible.  Planta campos de henna que proporcionen tinte para los brillantes colores que necesitarán los pintores."
        }
    }
    message_mission_tutankhamun_valley {
        id: 448,
        type: 3,
        size [40, 30]
        title {
            text: "Tut en el Valle",

        }
        subtitle {
            text: "Muerte de Tutankamón",

        }
        content {
            text: "@P¡Una terrible tragedia ha caído sobre nuestro joven y querido faraón, Tutankamón!  Su reinado, que en otro tiempo prometía gloria, ha sido cruelmente truncado por la mano del destino.  Es hora de que los trabajadores de Deir el-Medina vuelvan a preparar una cámara de descanso eterna para el faraón.  Con su inesperada y temprana muerte, es imperativo que obligues a tus trabajadores a esforzarse al máximo.  La tumba de Tutankamón debe estar completamente abastecida de provisiones para su viaje al más allá y lista para recibir sus sagrados restos en unos pocos años.  ¡La rapidez es de suma importancia!"
        }
    }
    message_mission_seti_valley {
        id: 449,
        type: 3,
        size [40, 30]
        title {
            text: "Seti en el Valle",

        }
        subtitle {
            text: "Tumba para un faraón",

        }
        content {
            text: "@PNuestro faraón más poderoso, Seti, hijo de Ramsés I, ha declarado que este es el momento propicio para empezar a prepararse para su viaje al más allá.  Con este fin, comenzarás la excavación de su tumba real en el Valle de los Reyes.  Tus trabajadores no deben escatimar esfuerzos en su preparación.  Deben tomarse las medidas adecuadas para garantizar que, una vez terminada, su calidad artesanal sea inigualable durante muchos años. @PPero, mientras avanza la construcción de este proyecto real, toma las precauciones debidas contra los vándalos.  Ya se han recibido informes de bandas de criminales codiciosos, dispuestos a enriquecerse profanando las tumbas y perturbando la paz de los faraones que descansan eternamente en Egipto.  No permitas que este acto sacrílego deshonre las tumbas reales del Valle, pues, tan seguro como que el sol sale por el este, tu posición en el reino quedará manchada."
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
            text: "Tierras del Levante",

        }
        content {
            text: "@P¡Salud, gobernador real, regente del Levante y leal súbdito de nuestro faraón, hijo de Ra!  Es realmente afortunado vivir en esta época en que la benevolente mano de Egipto se extiende desde los lejanos confines de Nubia hasta las costas del Levante.  Infinita es la sabiduría de nuestro nuevo faraón, el venerado Ramsés II, y grande es su visión, pues es él quien te ha enviado a gobernar esta hermosa tierra, ahora parte del dominio siempre en expansión de Egipto. @PAunque esta región sigue plagada de peligros, tiene muchas riquezas que deben explotarse.  Las verdes colinas están cubiertas de altos árboles que producen madera fina, ideal para fabricar carros y útil en muchas formas de construcción.  También se encuentran vetas de cobre, aunque no abundantes, que serán muy útiles para forjar armas resistentes.  La madera y el cobre, tan escasos en nuestra patria, serán sin duda bienvenidos cuando se envíen en gran cantidad.  Por ello se te encomienda supervisar el establecimiento de un poderoso puerto comercial desde el que exportar estos valiosos productos.  ¡El faraón y el pueblo de Egipto te quedarán muy agradecidos! @P¡Pero ten cuidado!  Asegúrate de que tus propios soldados de confianza estén equipados con carros rápidos y armas robustas, pues los hititas, aunque sometidos por Seti, padre del faraón, siguen siendo peligrosos y podrían desafiar nuestra legítima autoridad en esta fértil tierra.  Una fuerte presencia militar en este nuevo territorio puede ser necesaria para sofocar insurrecciones y, sin duda, será muy útil en el futuro. @PPor último, para recordar a la gente de esta región a quién debe ahora rendir homenaje, el faraón Ramsés II considera oportuno que erijas un obelisco que proclame sus glorias."
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
            text: "La batalla de Qadesh",

        }
        content {
            text: "@PLa tierra de Amurru, cercana a la costa del Levante, tiembla bajo el casco y los pies de tus poderosas legiones, bendecido faraón.  Esta región puede estar bendecida con gemas raras, pero también está llena de discordia.  Los hititas armados, dirigidos por el miserable rey Muwatalli, buscan una vez más disputar el control de esta tierra, que nos pertenece por derecho.  Espías capturados hablan de cómo sus bandas hostiles siguen muy lejos, al norte, y por ello no suponen ninguna amenaza.  ¿Pero se debe creer esto?  Sabio es el guerrero que no baja su escudo en la batalla.   @PPara acallar tales rumores de insurrección, tú, nuestro más venerado faraón, Ramsés II, hijo de Ra, has llegado a la ciudad fortaleza de Qadesh.  Ya se han establecido en sus afueras los campamentos de dos de tus temidas compañías de carros.  Pero no son todas.  A tu disposición inmediata hay otras tropas veteranas, concretamente las experimentadas tropas que combatieron hace poco cerca de Sumur.  ¡Pero ten cuidado!  Puede ser aconsejable retrasar el despliegue de estos valiosos recursos hasta que su necesidad sea más evidente, pues también es sabio el guerrero que tiene un buen número de tropas de confianza a las que convocar en el momento culminante de la batalla. @PUna vez derrotado el miserable enemigo, será necesario reactivar la economía estancada de Qadesh para que también contribuya a la gloria de Egipto.  Recoge gemas valiosas y contrata a joyeros expertos que fabriquen productos exquisitos para los leales súbditos del faraón.  ¡Los artículos de lujo de tan rara belleza sin duda tendrán gran demanda!"
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
            text: "Colosos de Abu Simbel",

        }
        content {
            text: "@PLa gloria de nuestro faraón, Ramsés II, impregna la tierra.  Para que el legado de su reinado viva para siempre, se ha decretado que se construya un gran monumento y un templo dedicados a su gobierno en lo profundo de Nubia, y el propio faraón ha elegido el lugar perfecto para esta creación.  Desde los acantilados de arenisca rosada que dominan la orilla occidental del Nilo en Abu Simbel, supervisarás la talla de cuatro enormes figuras sentadas de Su Majestad.  Las superficies del monumento, excavadas en la roca viva, proclamarán las hazañas heroicas del faraón durante su gran triunfo en la batalla de Qadesh.  Este enorme monumento, al tiempo que pregona las proezas de nuestro líder, servirá también de recordatorio para los pueblos de Nubia de la grandeza y el poder de Egipto, pues, aunque Nubia es rica en yacimientos de oro y otras gemas raras, su pueblo siempre ha vivido con inquietud bajo el dominio egipcio.  Por ello debes estar siempre preparado para la defensa y para enviar tropas si el faraón las necesita. @PLa arenisca puede exportarse para construcciones en otros lugares del reino, al igual que otros productos que podrás fabricar con los abundantes recursos de la región.  Sin embargo, hay muy poca madera.  Sin duda tendrás que establecer una ruta comercial para importar este producto, pues será necesario para los andamios de la inmensa escultura."
        }
    }
    message_mission_ramses_valley {
        id: 453,
        type: 3,
        size [40, 30]
        title {
            text: "Ramsés en el Valle",

        }
        subtitle {
            text: "Un lugar de descanso inigualable",

        }
        content {
            text: "@PHan transcurrido muchos años largos y gloriosos desde que nuestro faraón, el venerado Ramsés II, recibió el cayado y el mayal de manos de su padre, Seti I.  Con las bendiciones de Ra, seguirá reinando durante muchos años más.  No obstante, ha llegado el momento de comenzar a excavar en las entrañas de la tierra y preparar el lugar de descanso eterno para nuestro insigne líder.  Ha proporcionado a tu arquitecto de tumbas un plan para la tumba más grande construida hasta ahora, que supera incluso la de su padre.  Ahora depende de ti asegurar que esta petición real se lleve a buen término. @P¡Pero debes saber de antemano!  Existe un grado alarmante de descontento entre algunos trabajadores y esclavos de espíritu independiente, tanto en la localidad como en el Bajo Egipto.  Siguen a un hombre que en otro tiempo se crió en la corte de nuestro faraón, y han amenazado con invocar a su dios para que intervenga divinamente.  Esperan que, con tal ayuda divina, puedan salirse con la suya.  Incluso ahora, sacerdotes y hombres santos debaten la validez de estas amenazas.  Mientras esperamos pacientemente sus opiniones, puede ser prudente prepararse para lo inesperado."
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
            text: "La tierra de los Pueblos del Mar",

        }
        content {
            text: "@PLos rumores de angustia y descontento del oeste se han vuelto recientemente más amenazadores.  Los exploradores informan de que varias tribus bárbaras, que hablan lenguas extrañas, han llegado a las costas de Cirenaica, al oeste.  Para empeorar las cosas, estos pueblos caminan ahora de la mano de Maraye, hijo de Did, rey de los libios y enemigo del Faraón.   @PLa noticia ha llegado ya al faraón Merneptah de que estas viles gentes, con todas sus mujeres, niños y posesiones terrenales pisándoles los talones, pronto se dirigirán hacia el este, hacia el fértil delta del Nilo, ¡nuestra patria!, en busca de un lugar donde asentarse.  Ya ha habido pequeños enfrentamientos en los oasis septentrionales de Siwi y Farafra.  Tu ciudad del delta, Pi-yer, es ahora la que se interpone en su camino.  Dentro de poco, esta lenta banda de salvajes podría estar a las puertas de tu ciudad.  ¡El Faraón ha decretado que, si llegan, no se les debe permitir penetrar más allá! @PNecesitarás importar madera con la que construir robustas naves de guerra, y cobre para las armas.  Es tu fortuna que los hititas, antes problemáticos, ahora se mantengan en paz gracias a la gran victoria de Ramsés II en Qadesh, padre del amado Merneptah.  Haz que tu ciudad sea fuerte y prepara a tus leales tropas para el combate a muerte."
        }
    }
    message_mission_pelusium {
        id: 455,
        type: 3,
        size [40, 30]
        title {
            text: "Pelusio",

        }
        subtitle {
            text: "Repeler a los asirios",

        }
        content {
            text: "@PDesde los días del gran Shabaka, unificador del Alto y el Bajo Egipto y padre del faraón Taharqa, el conflicto con los agresivos asirios ha sido la norma.  Mientras vivió, el faraón Shabaka consideró oportuno ayudar a nuestros hermanos de Palestina, que se hallaban bajo el duro yugo de Asiria.  ¡Cuidado!  Los súbditos del rey pagano Asarhaddón vuelven a estar en marcha y, como siempre, sus ojos están puestos en las fértiles tierras de Egipto.  ¡Ahora te toca a ti alcanzar la gloria!  Como alcalde real de Pelusio, se espera que defiendas la ciudad de la serie de ataques de estos malditos enemigos.  Situada en el borde oriental del delta del Nilo, tu fortaleza fronteriza se encuentra en primera línea de las defensas exteriores de Egipto. @PAdiestrar adecuadamente a tus soldados y establecer vínculos comerciales para asegurar armas, o las materias primas con las que fabricar las tuyas, será importante. @P¡No flaquees!  Una firme resistencia militar es vital para garantizar la independencia continuada de Egipto.  Si logras resistir apenas siete años, la victoria estará asegurada.  ¡Taharqa, el gran faraón, segundo hijo de Shabaka, os estará observando!"
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
            text: "Renacimiento de una armada",

        }
        content {
            text: "@PDurante muchas generaciones, los egipcios han sufrido bajo el cruel puño de Persia.  Sin embargo, el dominio de Babilonia sobre nuestras sagradas tierras ya no es tan fuerte como lo fue en otro tiempo.  Mientras nuestros malditos opresores estaban ocupados entrometiéndose en la política de Grecia, una serie de revueltas en Egipto ha logrado por fin aflojar el odiado yugo persa.  Sin embargo, ahora ha llegado al faraón Achoris la noticia de que una fuerza al mando del almirante de la flota Conón (un lacayo griego que recibe oro persa), enviada por Artajerjes II, se dirige a nuestras costas.  El faraón Achoris ha determinado sabiamente que se necesita una fuerte presencia naval en el Nilo para frustrar esta incursión.  Como gobernador real de Tanis durante los próximos diez años, debes construir naves robustas y entrenar a tropas valerosas para proteger los accesos por agua y por tierra. @PNecesitarás establecer una ruta comercial con Enkomi para importar madera resistente con la que construir una flota.  El cobre también puede importarse de Enkomi, en la isla de Chipre.  Esta ruta comercial es precaria en el mejor de los casos, ya que discurre cerca de la costa del Levante, bajo el control de nuestro enemigo.  Abastecer al faraón con los suministros necesarios debería ayudarte a complementar tus ingresos.   @PTen en cuenta que los fondos son escasos en estos tiempos difíciles.  Para triunfar, debes ser hábil en los negocios y el comercio, además de un comandante diestro."
        }
    }
    message_mission_alexandria {
        id: 457,
        type: 3,
        size [40, 30]
        title {
            text: "Alejandría",

        }
        subtitle {
            text: "Alejandro Magno",

        }
        content {
            text: "@PEl gran Alejandro, hijo de Filipo II de Macedonia y azote del Imperio babilónico, bendijo las tierras de Egipto con su presencia.  Con su llegada, el último sátrapa persa corrupto huyó precipitadamente.  Tras sacrificar al toro Apis en Menfis, Alejandro fue aceptado como faraón.  ¡Todo el pueblo se regocija!  Antes de emprender su viaje hacia el oráculo de Amón en el oasis de Siwa, sin embargo, nuestro líder decidió fundar una nueva ciudad, que algún día desea que sea la capital de su vasto y creciente imperio.  En su infinita sabiduría, te ha designado primer alcalde de esta futura ciudad! @PEl gran Alejandro te ha concedido una generosa dotación de fondos con los que iniciar la construcción, y te ha dado los servicios del respetado arquitecto griego Dinócrates.  Dentro de apenas una docena de años, espera que hayas desarrollado el poderío comercial, cultural y militar de su ciudad hasta alcanzar altos niveles, pues ha prometido regresar.  @PNuestro líder incluso se ha tomado la molestia de trazar la posición de las dos calles principales de su ciudad.  La calle Canopo discurre en sentido este-oeste; la otra avenida principal es perpendicular a ella y se dirige tierra adentro, desde el cabo Lochias hacia el sur, en dirección al lago Mariut. @PComo supervisor de confianza de este proyecto, debes construir cuanto antes instalaciones portuarias y establecer rutas comerciales lucrativas.  Debería haber muchos clientes para nuestros productos, en especial trigo, cebada, papiro y lino.  No descuides, sin embargo, los aspectos culturales ni los militares de esta ciudad, pues todavía hay vándalos errantes que desean robar la riqueza de Egipto."
        }
    }
    message_mission_ptolemy_alexandria_2 {
        id: 458,
        type: 3,
        size [40, 30]
        title {
            text: "La Alejandría de Ptolomeo",

        }
        subtitle {
            text: "Un faro de luz",

        }
        content {
            text: "@PEl legado de Alejandro Magno sigue vivo en nuestra orgullosa ciudad.  Aunque sus restos mortales descansan en el Mausoleo de Alejandría, su gran ciudad sigue prosperando.  Depende de ti, Ptolomeo I Soter, continuar la labor que comenzó el noble Alejandro.  Desde su fundación por Alejandro hace apenas 30 años, la ciudad se ha convertido en un poderoso centro comercial que abastece de alimentos básicos y artículos de lujo a gran parte de la región circundante.  Para impulsar su progreso económico y garantizar el paso seguro de los numerosos barcos que entran en el gran puerto, debes construir un enorme faro en la isla de Faros, cerca de la boca del puerto.  La luz de esta estructura guiará a los navegantes lejanos hasta el puerto con seguridad, evitando que encallen en sus traicioneros bajíos. @PPor importante que sea el comercio, no puedes ignorar el avance cultural e intelectual de nuestra sociedad.  Bajo tu liderazgo, Alejandría puede convertirse también en la capital intelectual del mundo conocido.  Reúne obras del saber de cerca y de lejos, y construye una gran Biblioteca donde conservarlas.  Tan seguro como que las hormigas se sienten atraídas por la miel, los eruditos de todas partes viajarán a este centro de saber y aprendizaje sin igual.   @PPara levantar estos grandes monumentos necesitarás importar un material de construcción, como el mármol blanco, adecuado para estas grandes estructuras.  Enkomi, en la isla de Chipre, es una buena fuente de este material.   @PPor último, no descuides tu ejército.  Siempre parece haber inquietud en un lugar u otro.  Puede ser necesario enviar tropas a las fronteras lejanas para proteger los intereses de Egipto y defender su honor."
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
            text: "César y Cleopatra",

        }
        content {
            text: "@PEl insolente zarpazo del Imperio romano se hace más fuerte y alcanza más lejos cada día que pasa.  Incluso las letales luchas de poder políticas de Roma han llegado a nuestra tierra.  Con el reciente asesinato de Pompeyo en las costas de Egipto, Julio César tiene ahora el control completo de las poderosas legiones de Roma y ha puesto sus ojos en las riquezas de Egipto, y en la belleza de nuestra cautivadora faraona, Cleopatra VII, hija de Ptolomeo XII Auletes.  Nuestra astuta líder, sin embargo, no se deja vencer fácilmente en el campo de batalla del ingenio.  Si César desea utilizarla como medio para aumentar la influencia de Roma en Egipto, ella también planea emplearlo como instrumento para mantener el poder dinástico de nuestra gran tierra. @PLa llegada de César a Alejandría con sus impopulares romanos ha provocado un levantamiento entre sus ciudadanos de espíritu independiente.  Una turba alborotada, incitada por el hermano menor de Cleopatra, Ptolomeo XIII, ha acorralado a César y a sus hombres en el barrio real de la ciudad.  Han estallado violentos combates callejeros que han causado numerosas bajas.  Para mantener abierta su ruta de escape por mar, César incendió la flota egipcia que estaba fondeada en el puerto de Alejandría.  Por desgracia, el incendio se extendió a algunos almacenes de la costa, quemando grandes cantidades de rollos de papiro pertenecientes a la Gran Biblioteca.   @PPara romper la trampa en la que se encuentra ahora, César ha convocado al leal Mitrídates y a sus tropas desde Siria para realizar su rescate. Tras asaltar con éxito la fortaleza fronteriza de Pelusio, Mitrídates ha hecho marchar a sus hombres a marchas forzadas alrededor del vértice del delta del Nilo para acercarse a Alejandría desde el sudeste. Los elementos de vanguardia de esta fuerza acampan actualmente en las afueras de la pequeña aldea de Maritis, en la orilla oriental del lago Mariut, preparándose para la última etapa de su viaje.  @PEl nefasto Ptolomeo XIII ha tenido noticia de la aproximación de estos refuerzos.  En respuesta, ha sacado la mayor parte de su numeroso ejército hacia el sudeste, fuera de Alejandría.  Una batalla decisiva está a punto de desencadenarse en la orilla oriental del lago Mariut.  ¿Podrás, al mando de las legiones romanas de Mitrídates, derrotar al ejército egipcio rebelde de Ptolomeo y abrirte paso hasta César y Cleopatra en Alejandría?  Su destino está en tus manos."
        }
    }
    message_mission_cleopatra_alexandria_2 {
        id: 460,
        type: 3,
        size [40, 30]
        title {
            text: "La Alejandría de Cleopatra",

        }
        subtitle {
            text: "El legado de una reina",

        }
        content {
            text: "@PLa sangrienta muerte de César a manos de los puñales de sus asesinos sumió en el caos al mundo romano y te ha sumido a ti, nuestra faraona Cleopatra VII, en el dolor y el luto.  Se ha ido tu amante, tu mentor, tu confidente y tu poderoso aliado.  Octavio, su sobrino nieto adoptivo, adolescente, ha sido nombrado heredero, pero Marco Antonio, más experimentado y antes cónsul de César, se ha convertido en el jefe de estado nominal, para disgusto del joven Octavio.  No es de extrañar que el testamento de César no mencionara a tu hijo con él, Ptolomeo César, conocido popularmente como Cesarión.  Deseosa de seguridad para ti y para tu hijo, y como siempre con la intención de preservar el poder de Egipto, has abandonado Roma rumbo a Alejandría. @PA pesar de todas las leguas que separan Roma de ti, no puedes dejar atrás todas sus disputas internas.  Los hombres poderosos siguen luchando por el poder; tu apoyo y el acceso a las riquezas de Egipto serían un gran activo para cualquier facción.  Es fundamental que apoyes al vencedor en esta lucha por el poder, pues ponerte del lado del perdedor podría acabar fácilmente con Egipto.  El dramático enfrentamiento entre las facciones rivales de Roma tuvo lugar hace poco en Filipos, donde los cesarianos de Marco Antonio derrotaron de forma decisiva a las fuerzas de Bruto y Casio.  Antonio, Octavio y Lépido han repartido ahora el imperio para gobernarlo conjuntamente, y Antonio ha reclamado la parte oriental, que incluye Egipto. @PPoco después de la batalla, Marco Antonio te convocó para reunirte con él en Tarso, en Asia Menor, para que pudieras explicar mejor por qué habías tardado en unirte a los cesarianos.  Nada dispuesta a acudir como un perrito faldero, sabiamente te negaste a responder.  Después de todo, sabes mejor que nadie que es mucho mejor tratar con un romano según tus propios términos y condiciones, ¡y no según los suyos! @PAsí pues, tú, faraona Cleopatra, has regresado a casa, a Alejandría, a Egipto.  Ahora es el momento de engrandecer la gloria de esta magnífica ciudad, fundada por el gran Alejandro, cuya tumba todavía recibe visitantes.  La famosa Gran Biblioteca de Alejandría sigue atrayendo a eruditos de todo el mundo; la brillante luz del maravilloso Faro de Faros sigue encendida para que los navegantes puedan atravesar con seguridad las traicioneras aguas del puerto.  Ahora puedes enriquecer aún más la belleza de la ciudad construyendo el amplio Cesareo en honor a tu antiguo amante y a tu joven hijo.  Además, asegura tu propio tránsito al más allá construyendo otro mausoleo, para que puedas ser debidamente venerada tras tu viaje al Campo de los Juncos.   @PLa próxima vez que Marco Antonio te reclame, ¿quizá emplee un poco más de tacto?"
        }
    }
    message_mission_actium_2 {
        id: 461,
        type: 3,
        size [40, 30]
        title {
            text: "Accio",

        }
        subtitle {
            text: "Antonio y Cleopatra",

        }
        content {
            text: "@P¡Oh noble faraona Cleopatra VII, consorte de César y ahora de Antonio!  El destino de Egipto está en tus manos, pero tus manos descansan ahora en las de un romano, Marco Antonio, y él está profundamente inmerso en la lucha por el control de Roma y de sus legiones.   @PNecesitando los inestimables recursos de Egipto, pero también deseando tu amor y tu afecto, Antonio accedió a tu exigencia de matrimonio.  Por desgracia, la noticia de esta nueva unión ha escandalizado a Roma.  Como sabías, Antonio seguía casado con Octavia, hermana de Octavio, heredero legal de César y, junto con Antonio, detentador conjunto del poderío de Roma.  Pero con las noticias de las costumbres polígamas de Antonio, esta relación se ha tensado gravemente.  Octavio cree que Antonio ha mancillado no solo el honor de su hermana y de su familia, sino también el prestigio de Roma.  Para resolver esta cuestión de honor y poner fin a la lucha por el control definitivo de Roma, Octavio ha desafiado formalmente a tu amante, Antonio, a un combate.  Con esto en mente, Antonio, acompañado por ti y por tu flota egipcia, ha encontrado en la península griega, cerca de Accio, un lugar para acampar.  El emplazamiento ofrece un buen puerto con numerosos atracaderos potenciales para tus naves.   @PDebes aumentar rápidamente tu poderío militar, en especial la fuerza naval.  Octavio ha jurado regresar en septiembre del año 31. @PAhora tu destino y el de Marco Antonio, así como el destino de Egipto y de Roma, dependen una vez más del rendimiento de vuestro poderío militar."
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
            text: "La primera tumba",

        }
        content {
            text: "@PTras muchas brillantes victorias en lejanos campos de batalla en defensa de las tierras y del pueblo de Egipto, el faraón Tutmosis, como todos deben hacer algún día, ha dirigido sus pensamientos a los preparativos de su viaje al más allá.  Para asegurar que este viaje sea un éxito, el faraón desea que comiences cuanto antes la construcción de su tumba.  Establece una aldea en la orilla occidental del Nilo para disponer de un grupo de trabajadores capacitados.  Localiza un lugar adecuado para su tumba en los acantilados al oeste de la aldea.  Necesitarás canteros expertos para excavar en la roca las numerosas cámaras de la tumba, y artesanos talentosos para enlucir y pintar las estancias.   @PPara iluminar a los trabajadores que laboren en las zonas más recónditas de la tumba, necesitarás establecer talleres de lamparistas.   Abastece a los lamparistas con cerámica y aceite importado como combustible.  Planta campos de henna que proporcionen tinte para los brillantes colores que necesitarán los pintores."
        }
    }
    message_mission_tutankhamun_valley_2 {
        id: 463,
        type: 3,
        size [40, 30]
        title {
            text: "Tut en el Valle",

        }
        subtitle {
            text: "Muerte de Tutankamón",

        }
        content {
            text: "@P¡Una terrible tragedia ha caído sobre nuestro joven y querido faraón, Tutankamón!  Su reinado, que en otro tiempo prometía gloria, ha sido cruelmente truncado por la mano del destino.  Es hora de que los trabajadores de Deir el-Medina vuelvan a preparar una cámara de descanso eterna para el faraón.  Con su inesperada y temprana muerte, es imperativo que obligues a tus trabajadores a esforzarse al máximo.  La tumba de Tutankamón debe estar completamente abastecida de provisiones para su viaje al más allá y lista para recibir sus sagrados restos en unos pocos años.  ¡La rapidez es de suma importancia!"
        }
    }
    message_mission_seti_valley_2 {
        id: 464,
        type: 3,
        size [40, 30]
        title {
            text: "Seti en el Valle",

        }
        subtitle {
            text: "Tumba para un faraón",

        }
        content {
            text: "@PNuestro faraón más poderoso, Seti, hijo de Ramsés I, ha declarado que este es el momento propicio para empezar a prepararse para su viaje al más allá.  Con este fin, comenzarás la excavación de su tumba real en el Valle de los Reyes.  Tus trabajadores no deben escatimar esfuerzos en su preparación.  Deben tomarse las medidas adecuadas para garantizar que, una vez terminada, su calidad artesanal sea inigualable durante muchos años. @PPero, mientras avanza la construcción de este proyecto real, toma las precauciones debidas contra los vándalos.  Ya se han recibido informes de bandas de criminales codiciosos, dispuestos a enriquecerse profanando las tumbas y perturbando la paz de los faraones que descansan eternamente en Egipto.  No permitas que este acto sacrílego deshonre las tumbas reales del Valle, pues, tan seguro como que el sol sale por el este, tu posición en el reino quedará manchada."
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
            text: "Tierras del Levante",

        }
        content {
            text: "@P¡Salud, gobernador real, regente del Levante y leal súbdito de nuestro faraón, hijo de Ra!  Es realmente afortunado vivir en esta época en que la benevolente mano de Egipto se extiende desde los lejanos confines de Nubia hasta las costas del Levante.  Infinita es la sabiduría de nuestro nuevo faraón, el venerado Ramsés II, y grande es su visión, pues es él quien te ha enviado a gobernar esta hermosa tierra, ahora parte del dominio siempre en expansión de Egipto. @PAunque esta región sigue plagada de peligros, tiene muchas riquezas que deben explotarse.  Las verdes colinas están cubiertas de altos árboles que producen madera fina, ideal para fabricar carros y útil en muchas formas de construcción.  También se encuentran vetas de cobre, aunque no abundantes, que serán muy útiles para forjar armas resistentes.  La madera y el cobre, tan escasos en nuestra patria, serán sin duda bienvenidos cuando se envíen en gran cantidad.  Por ello se te encomienda supervisar el establecimiento de un poderoso puerto comercial desde el que exportar estos valiosos productos.  ¡El faraón y el pueblo de Egipto te quedarán muy agradecidos! @P¡Pero ten cuidado!  Asegúrate de que tus propios soldados de confianza estén equipados con carros rápidos y armas robustas, pues los hititas, aunque sometidos por Seti, padre del faraón, siguen siendo peligrosos y podrían desafiar nuestra legítima autoridad en esta fértil tierra.  Una fuerte presencia militar en este nuevo territorio puede ser necesaria para sofocar insurrecciones y, sin duda, será muy útil en el futuro. @PPor último, para recordar a la gente de esta región a quién debe ahora rendir homenaje, el faraón Ramsés II considera oportuno que erijas un obelisco que proclame sus glorias."
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
            text: "La batalla de Qadesh",

        }
        content {
            text: "@PLa tierra de Amurru, cerca de la costa levantina, tiembla bajo los cascos y las pisadas de tus poderosas legiones, bendecido faraón.  Esta región puede ser bendecida con gemas raras, pero también está llena de discordia.  Los hititas armados, dirigidos por el miserable rey Mutwatalli, buscan de nuevo disputar el control de esta tierra, que nos pertenece por derecho.  Espías capturados cuentan que sus bandas hostiles siguen muy lejos, al norte, y por ello no suponen amenaza alguna.  Pero ¿es esto creíble?  Sabio es el guerrero que no suelta su escudo en la batalla.   @PPara acallar tales rumores de insurrección, tú, nuestro venerado faraón Ramsés II, hijo de Ra, has llegado a la ciudadela fortificada de Qadesh.  Ya se han establecido campamentos de dos de tus temidas compañías de carros en sus afueras.  Pero no son todas.  A tu disposición inmediata hay otras tropas veteranas, concretamente las tropas experimentadas que combatieron hace poco cerca de Sumur.  ¡Pero atención!  Puede ser prudente retrasar el despliegue de estos valiosos recursos hasta que la necesidad sea más evidente, pues también es sabio el guerrero que tiene a mano un buen número de tropas de confianza para llamar en lo más reñido de la batalla. @PUna vez derrotado el miserable enemigo, será necesario reactivar la economía estancada de Qadesh para que también contribuya a la gloria de Egipto.  Recoge gemas valiosas y contrata joyeros expertos para fabricar exquisitos productos para los leales súbditos del faraón.  ¡Los artículos de lujo de tan rara belleza tendrán sin duda mucha demanda!"
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
            text: "Colosos de Abu Simbel",

        }
        content {
            text: "@PLa gloria de nuestro faraón, Ramsés II, impregna la tierra.  Para que el legado de su reinado viva para siempre se ha decretado que se construya un gran monumento y un templo dedicado a su gobierno en lo profundo de Nubia, y el propio faraón ha elegido el lugar perfecto para esta obra.  Desde los acantilados de arenisca rosada que dominan la orilla oeste del Nilo en Abu Simbel supervisarás la talla de cuatro enormes figuras sentadas de Su Majestad.  Las superficies del monumento, excavadas en la roca viva, proclamarán las hazañas heroicas del faraón en su gran triunfo en la batalla de Qadesh.  Este colosal monumento, que pregonará las proezas de nuestro líder, servirá también como recordatorio a los pueblos de Nubia de la grandeza y el poder de Egipto, pues, aunque Nubia es rica en depósitos de oro y otras gemas raras, sus gentes siempre han soportado con inquietud el dominio egipcio.  Por ello debes estar siempre preparado para la defensa y en condiciones de enviar tropas si el faraón las necesita. @PLa arenisca puede exportarse para construcciones en otros lugares del reino, al igual que otros productos que podrás fabricar con los abundantes recursos de la región.  Sin embargo, apenas se encuentra madera.  Sin duda tendrás que establecer una ruta comercial para importar este producto, pues será necesaria para el andamiaje de la inmensa escultura."
        }
    }
    message_mission_ramses_valley_2 {
        id: 468,
        type: 3,
        size [40, 30]
        title {
            text: "Ramsés en el valle",

        }
        subtitle {
            text: "Un lugar de descanso incomparable",

        }
        content {
            text: "@PHan transcurrido muchos años largos y gloriosos desde que nuestro faraón, el venerado Ramsés II, recibió el cayado y el mayal de manos de su padre, Seti I.  Con las bendiciones de Ra, seguirá reinando durante muchos años más.  No obstante, ha llegado el momento de adentrarse en las entrañas de la tierra y preparar el lugar de reposo eterno de nuestro insigne líder.  Ha entregado a tu arquitecto de tumbas un plan para la tumba más grande jamás construida, que superará incluso la de su padre.  Ahora depende de ti asegurar que esta petición real se lleve a buen término. @P¡Pero ten en cuenta!  Existe un grado alarmante de inquietud entre algunos trabajadores y esclavos independientes, tanto en la región como en el Bajo Egipto.  Siguen a un hombre que en otro tiempo se crio en la corte de nuestro faraón, y han amenazado con invocar a su dios para que intervenga divinamente.  Esperan que, con tal ayuda divina, puedan salirse con la suya.  Incluso ahora los sacerdotes y hombres santos debaten la validez de estas amenazas.  Mientras aguardamos con paciencia sus opiniones, puede ser prudente prepararse para lo inesperado."
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
            text: "Historia",
        }
        content {
            text: "Durante más de tres milenios diversos pueblos han utilizado la planta de henna, un arbusto, como fuente de tinte.  La henna (de nombre científico Lawsonia inermis) pertenece a la familia de las litráceas y es originaria del norte de África y de Oriente Medio.  Al triturar sus hojas y ramas se obtiene un tinte rojo anaranjado que, bien aplicado, sirve para teñir el cabello, las uñas y la piel.  Incluso hoy la henna se emplea habitualmente en muchos rituales religiosos y ritos funerarios de Asia, Oriente Medio y África, y es el colorante básico de muchos de los populares 'tatuajes temporales'.  La henna es también el colorante principal de una amplia variedad de tintes para el cabello."
        }
    }
    message_mission_paint_maker {
        id: 470,
        
        size [30, 28]
        title {
            text: "Fabricante de pinturas",
        }
        content {
            text: "Los fabricantes de pintura necesitan un suministro de @469henna para producir pintura. Las hojas y los tallos triturados de la planta de henna se usan para obtener diversos tintes, necesarios para fabricar pinturas. La henna se cultiva en @91campos&de&henna, o bien puede establecerse una @47ruta&comercial para importarla.  @PUna vez que un fabricante de pinturas dispone de mano de obra estable, acceso a caminos y ha recibido un cargamento de henna, verás a los fabricantes trabajando duro para producir pintura. Cuando termina la producción, la pintura se entrega a un @4patio&de&almacenamiento. Después, los @363artesanos la emplean al pintar las @478tumbas&reales&de&enterramiento. @PDebido a sus olores desagradables y al ruido, los fabricantes de pintura son @56vecinos&poco&deseables. @L@LHaz clic @472aquí para saber más sobre la fabricación de pintura en el antiguo Egipto."
        }
    }
    message_illness_video {
        id: 471,
        type: 2,
        
        size [30, 20]
        title {
            text: "Enfermedad",
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
            text: "Artesanos",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Aunque la mayoría de las construcciones del antiguo Egipto contaban con artistas que aplicaban los toques finales, es en las tumbas del Imperio Nuevo, en el @475Valle&de&los&Reyes, donde las extraordinarias habilidades de estos talentosos artistas brillan de verdad. Prácticamente cada palmo de las paredes y los techos interiores de estas tumbas subterráneas proclamaba la grandeza del difunto mediante jeroglíficos e ilustraciones pintados con maestría. @PA pesar de la extravagancia y del detalle de sus ilustraciones, los artistas antiguos disponían de una paleta de colores bastante limitada y empleaban pinceles naturales hechos de @94cañas o de madera fibrosa, como las nervaduras de las palmeras. Sus pigmentos se preparaban con frecuencia en pequeños talleres que los fabricaban a partir de tintes naturales (como la @469henna) y de otros pigmentos naturales (como carbonato de calcio, carbón vegetal, óxido de hierro, rejalgar, oropimente, azurita y malaquita) molidos hasta convertirlos en polvo. Estos polvos podían mezclarse con un aglutinante, como goma vegetal o cola animal, y aplicarse como pintura. @PMuchos artistas especializados trabajaban juntos para crear espléndidas imágenes en bajorrelieve en las tumbas. Primero se preparaba un yeso con una mezcla de @190arcilla, agua y un agente blanqueador, y se aplicaba a las paredes de la tumba. Después se trazaba en rojo un diseño aproximado sobre las paredes recién enyesadas. Un maestro dibujante refinaba luego este contorno, normalmente en negro. Un maestro pintor hacía después más correcciones y añadía detalles para guiar al escultor de bajorrelieves que venía a continuación. Luego se aplicaba la pintura en grandes superficies planas de color. El detallado final, como los contornos y los detalles interiores, lo aplicaba otro maestro artista."
        }
    }
    message_building_lamp_maker {
        id: 473,
        
        size [30, 28]
        title {
            text: "Fabricante de lámparas",
        }
        content {
            text: "El fabricante de lámparas prepara lámparas cuya luz ayuda a guiar a los trabajadores por los oscuros pasillos de una @478tumba&real&de&enterramiento.  @PPara fabricar lámparas, el fabricante necesita un suministro de cerámica y aceite. Un @1alfarero puede proporcionar cerámica, o bien puede importarse de un @47socio&comercial. El @476aceite solo puede importarse. @PUn fabricante de lámparas debe tener acceso a caminos y una fuente de mano de obra cercana. Una vez que el fabricante ha recibido suficiente cerámica y aceite, verás a los fabricantes de lámparas trabajando duro, llenando las vasijas de aceite para hacer lámparas. @PLos fabricantes de lámparas tienen un efecto negativo en la @56deseabilidad, así que no los coloques demasiado cerca de tus zonas residenciales. @L@LHaz clic @474aquí para saber más sobre las lámparas del antiguo Egipto."
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
            text: "Lámparas",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los antiguos egipcios fabricaban pequeñas lámparas de cerámica que quemaban @476aceites naturales o grasa animal derretida como combustible. Estas lámparas proporcionaban la luz necesaria a los artesanos que trabajaban en lo más profundo de una tumba de enterramiento."
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
            text: "Valle de los Reyes",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "@PEl Valle de los Reyes fue la necrópolis durante cinco siglos de faraones, c. 1539-1075 a. C., entre ellos Tutmosis I, Tutankamón y Ramsés el Grande (Ramsés II).  Situado en la orilla occidental del Nilo, frente al complejo de templos de Tebas, el valle está dominado por el-Qurn, una montaña casi piramidal que recibe cada día las últimas bendiciones de Ra antes de que se ponga el sol.  Entre el valle y el gran Nilo se encuentran los templos funerarios reales dedicados a los faraones que esperaban disfrutar de su vida después de la muerte en las tumbas del valle.  Un pueblo cercano, Deir el-Medina, alojaba a cientos de trabajadores y sus familias. @PTrabajadores especializados preparaban las tumbas reales de enterramiento, y cada uno tenía una tarea importante que cumplir.  @385Los canteros tallaban escalones y pasillos en los acantilados de caliza.  Se dejaban pilares de piedra para sostener los techos de las grandes cámaras.  Las salas excavadas se alisaban y enyesaban antes de que llegaran los @472artesanos para decorar los techos y las paredes con bajorrelieves tallados y pinturas que ayudarían al faraón a atravesar su vida después de la muerte.  El rey difunto era colocado en su sarcófago y sellado en la tumba junto con muchos tesoros dignos de la condición divina que le otorgaban los antiguos egipcios.  Debido a estos grandes tesoros, las tumbas eran saqueadas con frecuencia, a veces por las mismas personas encargadas de vigilarlas. @PLos arqueólogos europeos redescubrieron el Valle de los Reyes a principios del siglo XIX.  En 1922 Howard Carter abrió la tumba sellada de Tutankamón y encontró muchos tesoros, entre ellos un sarcófago de oro.  A lo largo de los siglos, las crecidas repentinas han llenado muchas tumbas de limo y escombros, y es muy probable que aún queden por descubrir pasillos e incluso algunas tumbas en el valle."
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
            text: "Aceite",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "La mayor parte de los aceites que usaban los antiguos egipcios se importaban de Grecia, Chipre y Fenicia. Los aceites naturales tenían muchos usos, como combustible para las @474lámparas y para cocinar. Se extraían de diversas fuentes (la mayoría todavía se usan hoy), como el sésamo, la linaza, la aceituna y las grasas animales naturales."
        }
    }
    message_figure_tomb_robber {
        id: 477,
        
        size [30, 28]
        title {
            text: "Ladrón de tumbas",
        }
        content {
            text: "@P¡Donde hay una tumba, hay tesoro! El ladrón de tumbas es un tipo de delincuente que aparece si la @39opinión&de&la&ciudad es muy baja. Sin embargo, solo atacará la ciudad si hay tesoros que saquear. Así que, si tu ciudad no tiene tumbas (ya sean pirámides, @371mastabas, @368mausoleos o @478tumbas&reales&de&enterramiento), no se molestará en venir. Tampoco se molestará si no hay @374provisiones&funerarias que robar, bien porque la tumba no exigió que se enviaran o bien porque aún no se las has enviado. @PA veces, los ladrones de tumbas actúan incluso cuando no hay señales de delito en la ciudad. Si los ladrones profesionales reciben noticia de sus cómplices de que hay provisiones funerarias especialmente valiosas en las tumbas de tu ciudad, desatarán una ola de delincuencia. No hay forma de predecir cuándo podría producirse una ola de delincuencia.  @PTodos los ladrones de tumbas tienen un único objetivo: privar a un faraón que duerme eternamente de las riquezas y tesoros guardados en su tumba para su uso en la otra vida. Para llevar a cabo este plan, el ladrón debe llegar a la tumba sin ser capturado.  Si en su camino hacia la tumba se encuentra con un guardia o con algunos soldados, normalmente es 'detenido' en silencio y con eficacia, aunque un ladrón extremadamente ágil a veces logra escapar. Si el ladrón de tumbas consigue llegar a un monumento funerario, se llevará algunas provisiones funerarias ya enviadas y tu @35calificación&del&reino se verá afectada, pues ¿quién querría ser gobernado por alguien incapaz de proteger la santidad de las tumbas de sus antepasados? @PLos ladrones de tumbas no son exigentes con las tumbas que atacan. Están dispuestos a intentar robar en cualquier monumento que ya existiera en la ciudad antes de que empezaras a gobernar. Por suerte, estas tumbas preexistentes están bien selladas, y el ladrón no podrá robar provisiones funerarias de ellas. Sin embargo, la gente de todo Egipto se quedará tan asombrada de que se amenazara una de las tumbas más antiguas que la calificación de tu reino caerá en picado. @P¡Atención! Si el ladrón de tumbas se marcha con provisiones funerarias, deberás reponer cada objeto robado antes de poder completar la misión. @PPara más información sobre la delincuencia en tu ciudad, haz clic @36aquí. @L@LPara saber más sobre las tumbas de enterramiento del Valle de los Reyes del antiguo Egipto, haz clic @475aquí."
        }
    }
    message_building_royal_burial_tomb {
        id: 478,
        
        size [30, 28]
        title {
            text: "Tumba real de enterramiento",
        }
        content {
            text: "@PA partir del Imperio Nuevo, los antiguos egipcios comenzaron a enterrar a sus faraones y a otros nobles en tumbas cada vez más elaboradas, excavadas en la roca viva de un valle casi inaccesible. @PPara iniciar la construcción de una tumba real de enterramiento primero deberás encontrar un emplazamiento adecuado.  Selecciona 'Tumba real de enterramiento' en la lista de Estructuras religiosas: monumentos.  Aparecerá una gran huella.  La mayor parte del monumento debe colocarse sobre los acantilados, salvo la pequeña entrada que sobresale de uno de sus lados. Mueve la huella por los acantilados hasta encontrar un lugar adecuado. Sabrás que has encontrado un buen sitio cuando toda la huella se vuelva verde. Cualquier parte roja de la huella indica que no has encontrado un lugar viable para el monumento. @PPuede que te resulte más fácil colocar la tumba real de enterramiento aplanando temporalmente los acantilados. Basta con pulsar 'H' para aplanar los acantilados, o elegir 'Ocultar acantilados' en la lista de @18superposiciones. Para volver a levantar los acantilados a su altura original, pulsa 'H' de nuevo o selecciona 'Normal' en la lista de superposiciones. En tumbas especialmente grandes, también puede serte útil la tecla 'M'. Al pulsar 'M' la huella se fija en su sitio y puedes desplazar tu vista para comprobar si el emplazamiento elegido es adecuado. Si lo es, simplemente haz clic con el botón del ratón para colocar el monumento. Si el emplazamiento no es apropiado, pulsa 'M' de nuevo para liberar la huella y seguir buscando un lugar. @PUna vez elegido el emplazamiento, debe entregarse un envío de lámparas a la tumba antes de que pueda comenzar cualquier trabajo. Las lámparas las fabrica un @473fabricante&de&lámparas y también pueden importarse de un @47socio&comercial. Cuando haya 400 lámparas almacenadas en un @4patio&de&almacenamiento, un campesino arrastrará un trineo cargado de lámparas hasta la obra. @PCuando las lámparas llegan para iluminar el camino, los @363canteros labran a grandes rasgos las numerosas cámaras de la tumba en la roca sólida. Una vez que los canteros han terminado su trabajo en una cámara, se convocará a @363artesanos especializados para empezar a enyesar y pintar las paredes. Estos artesanos necesitarán un suministro de @92arcilla para el yeso y de pintura procedente de un @470fabricante&de&pinturas. Los productos llegarán directamente al Gremio de Artesanos, bien entregados por los propios fabricantes o desde un patio de almacenamiento. Si tu ciudad no puede producir uno o ambos productos, quizá puedas @47importarlos. @PHaz clic con el botón derecho sobre un monumento de tumba real de enterramiento para visitar a su @369capataz&de&obras y consultar el progreso. @L@LHaz clic @475aquí para saber más sobre el Valle de los Reyes y sus tumbas reales de enterramiento."
        }
    }
    message_building_zoo {
        id: 479,
        
        size [30, 28]
        title {
            text: "Zoológico",
        }
        content {
            text: "Los zoológicos son una forma popular de @49entretenimiento en cualquier ciudad. El zoológico necesita acceso a caminos y trabajadores que cuiden de los animales, así como un suministro de @89paja y de @359carne&de&caza como alimento. La paja puede cosecharse en las granjas de cereales, y los cazadores del pabellón de caza pueden conseguir la carne. También puedes establecer una @47ruta&comercial para importar estos productos. @PConsulta con tu @28supervisor&de&diversiones para saber cuántos zoológicos tiene tu ciudad, y usa la superposición de @18entretenimiento para ver qué casas tienen acceso al zoológico y observar cómo los cuidadores recorren la ciudad. @PA pesar de las distracciones únicas que ofrece un zoológico, a los ciudadanos no les gusta vivir demasiado cerca, pues los rugidos y los fuertes olores que emanan de los animales resultan muy ofensivos para cualquier egipcio bien educado. Haz clic @56aquí para saber más sobre la deseabilidad. @L@LPara saber más sobre los zoológicos del antiguo Egipto, haz clic @480aquí."
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
            text: "Zoológico",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Los antiguos egipcios eran aficionados a lo divertido y a lo insólito, y ambas cosas podían encontrarse en abundancia en un zoológico. A medida que el poder y la influencia de Egipto se extendían por varios continentes, muchos faraones recibieron criaturas extrañas y exóticas de gobernantes de tierras lejanas como regalos o tributos. Estos animales se presentaban al faraón y luego se mantenían en jardines zoológicos especiales, que inevitablemente se encontraban a poca distancia del palacio del soberano. Es evidente que los primeros zoológicos de Egipto servían principalmente para el espectáculo público y, en segundo lugar, para el estudio. Se dice que la Gran Biblioteca de Alejandría contaba entre sus terrenos con un jardín botánico y un recinto zoológico."
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
            text: "Alejandría y su biblioteca",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Desde sus inicios, Alejandro Magno esperaba que Alejandría, la ciudad en la desembocadura del Nilo que él fundó y ayudó a planificar, se convirtiera en un centro de comercio y cultura para la cuenca mediterránea. Menos de cincuenta años después de su fundación en 331 a. C., la floreciente metrópolis se había convertido en un centro comercial sofisticado, debido en gran parte a su famosa Gran Biblioteca.  @PPoco después de la muerte inesperadamente temprana de Alejandro en 323 a. C., su vasto imperio se disolvió en tres grandes regiones. Uno de sus amigos más cercanos y de sus generales más capaces, Ptolomeo, era en aquel momento gobernador de facto de Egipto. Se hizo con las riendas de aquella antigua tierra, llegando finalmente a ser faraón (como Ptolomeo I Sóter) y continuando así la presencia griega en Egipto iniciada por Alejandro. Fue Ptolomeo quien interceptó el cortejo fúnebre de Alejandro, con destino a Macedonia, y trasladó sus restos mortales a Alejandría para su sepultura.  @PAdemás de la gloria personal y la vida de lujo, los primeros gobernantes ptolemaicos también se interesaron, para su mérito, por mejorar la cultura de su ciudad y de su tierra. Alejandría, la nueva capital de Egipto, ya era el centro comercial del mundo conocido; querían que también fuera la capital intelectual. Con este fin se concibió y construyó la Gran Biblioteca de Alejandría. La Gran Biblioteca fue el primer centro de aprendizaje académico e investigación de la humanidad. Las brillantes mentes de la Antigüedad sentaron aquí las bases del estudio sistemático de la astronomía, la geografía, la literatura, las matemáticas, la medicina y la física. Fue aquí donde Euclides definió por primera vez la geometría y Eratóstenes midió con precisión la circunferencia de la Tierra, sosteniendo que se podía llegar a la India navegando hacia el oeste desde España. @PLos Ptolomeos dedicaron mucho tiempo y energía, y no una pequeña parte de su riqueza, a obtener copias de todos los manuscritos importantes conocidos por el hombre. Para ello se promulgó una ley que establecía que todas las caravanas y barcos que entraran en Alejandría debían ser registrados, no en busca de contrabando, sino de artículos de conocimiento. Cualquier mapa o pergamino que se encontrara se entregaba a la biblioteca para que los escribas pudieran copiarlo. Así, el refugio académico de Alejandría llegó a contener más de 700.000 rollos de papiro catalogados sistemáticamente, incluidas muchas obras maestras hoy perdidas de arte, literatura y ciencia, como clásicos de Homero, Aristóteles, Sófocles, Esquilo y Eurípides.  @PPero no todo era aprendizaje. Los terrenos de la legendaria biblioteca también contaban con un jardín botánico y un museo, así como con un templo a las nueve musas (dioses y diosas griegos de las artes y las ciencias). Un corto paseo por una empalizada bordeada de jardines llevaba hasta un @480zoológico, sin duda con muchos animales exóticos. Fueron muchos los sabios de la Antigüedad que recorrieron sus pasillos con columnas.  @PLo que llevó a la desaparición de la Gran Biblioteca no está del todo claro. Gran parte de sus obras, de valor incalculable, se destruyó al parecer en un incendio que se produjo cuando Julio César incendió los barcos del hermano de Cleopatra VII. Hacia el siglo IV d. C., cuando la influencia del cristianismo se extendía, la mayoría de los manuscritos restantes de la biblioteca fueron destruidos, aparentemente, en un esfuerzo por erradicar todas las reliquias del paganismo y la herejía. Más tarde, en el 640 d. C., los árabes que arrasaron la ciudad, casi abandonada, probablemente quemaron como combustible los pergaminos que habían sobrevivido. De las 123 obras de Sófocles que se sabía que estaban en la Gran Biblioteca, hoy solo quedan siete."
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
            text: "Cesáreo",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "Cleopatra VII comenzó el Cesáreo. Originalmente consistía en un pequeño templo o altar en medio de un santuario, aparentemente destinado al culto de Marco Antonio. Sin embargo, su suicidio, seguido poco después por la muerte de Cleopatra, hizo que este monumento fuera completado por su rival, Octavio (César Augusto), quien terminó la estructura y la dedicó a su propio culto. Dos obeliscos (comúnmente llamados Agujas de Cleopatra, aunque ella no tuvo nada que ver con ellos) fueron durante siglos hitos destacados a lo largo de la costa del Puerto Oriental de Alejandría. Estos obeliscos, trasladados a Alejandría desde Heliópolis por orden de Octavio, marcaban la entrada al Cesáreo mucho después de que el resto fuera destruido. Ambos obeliscos han sido retirados (uno se alza en el Central Park de Nueva York, el otro a orillas del Támesis, en Londres). @PNo se conocen con precisión los detalles de las estructuras reales del Cesáreo. Nuestro conocimiento procede de breves descripciones de algunos autores antiguos. Su arquitectura, como la de los demás grandes monumentos de Alejandría, era de estilo griego. Al parecer contenía un santuario central rodeado de patios al aire libre y de stoas (galerías con columnas) que probablemente servían de 'muros' exteriores del monumento. Las salas y pórticos situados entre las stoas contenían pergaminos y podían utilizarse para asambleas o para el estudio tranquilo."
        }
    }
    message_plague_of_locusts {
        id: 483,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Plaga de langostas",
        }
        content {
            text: "Nos han llegado informes de enjambres enloquecidos de langostas voraces que devoran las cosechas por todo Egipto.  ¡Tenga cuidado con su embestida durante la próxima temporada de crecimiento!"
        }
    }
    message_plague_of_frogs {
        id: 484,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Plaga de ranas",
        }
        content {
            text: "¡Una horrible maldición ha caído sobre la tierra!  Multitudes de ranas contaminan nuestras calles y viviendas, obligando a los habitantes a abandonar sus hogares."
        }
    }
    message_hailstorm {
        id: 485,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Granizada",
        }
        content {
            text: "¡La muerte y la destrucción llegan con el viento!  Una feroz granizada ha venido a traer una lluvia mortal de hielo.  ¡Que los dioses se apiaden de quien no se resguarde de esta maldición maligna, pues tiene pocas esperanzas de sobrevivir!"
        }
    }
    message_river_of_blood {
        id: 486,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Río de sangre",
        }
        content {
            text: "¡Ay de nosotros!  Las aguas, antaño fuente de vida y sustento, están envenenadas con sangre.  ¿Cuánto tiempo tardará en levantarse esta vulgar plaga?"
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
            text: "Faro de Faros",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "@PAunque la ubicación de Alejandría era ideal para un puerto comercial, con mucha costa y un gran puerto natural, sus accesos estaban plagados de peligrosos bancos de arena.  Por ello se concibió que un alto faro en la isla de Faros, cerca de la boca del puerto, no solo sería de provecho para los marineros, sino que (si era lo bastante magnífico) sería también una nueva atracción maravillosa que incrementaría la fama de Alejandría.  @PEl faro de Faros, como llegó a conocerse, se construyó en parte con mármol blanco de Proconeso, en gran parte importado de las Islas de los Príncipes, frente a la costa de la actual Turquía.  Se edificó en tres grandes niveles: la base, o nivel más bajo, era cuadrangular; el nivel intermedio era octogonal; el nivel superior era cilíndrico.  Una enorme escalera de caracol que llevaba a la cima permitía incluso que los animales de carga subieran leña para alimentar el brillante fuego que ardía allí.  Coronaba la espectacular estructura (según algunos relatos) una estatua de Poseidón; otro relato sostiene que era una imagen de Zeus, o quizá una estatua de ambos. @PLa construcción del faro de Alejandría fue iniciada por el primer Ptolomeo (Auletes), pero no se terminó hasta el 283 a. C., durante el reinado de su hijo, Ptolomeo Filadelfo.  Según todos los testimonios, era un espectáculo increíble, más que digno de ser la Séptima Maravilla del mundo antiguo. @PLa desaparición de este monumento no fue obra del hombre, sino de una serie de terremotos que sacudieron la región.  Su nivel superior se derrumbó durante un fuerte sismo en el 303 d. C.  Sin embargo, no fue hasta un enorme temblor el 8 de agosto de 1303 cuando cayó la mayor parte de la estructura que quedaba, siendo engullida por las aguas circundantes.  Hoy, en la isla de Faros, donde se alzaba el maravilloso faro, se puede ver una fortaleza construida por el sultán mameluco Qait Bey."
        }
    }
    message_building_alexandria_library {
        id: 488,
        
        size [30, 28]
        title {
            text: "Biblioteca de Alejandría",
        }
        content {
            text: "Eruditos y otros hombres y mujeres sabios de todo el mundo conocido acuden a la Gran Biblioteca de Alejandría, el mayor depósito de conocimiento de la humanidad. @PPara construir la Biblioteca de Alejandría, primero debe seleccionar un emplazamiento adecuado. Elija Biblioteca de Alejandría en la lista de Estructuras religiosas: monumentos. Si la huella que ve está completamente en verde, la ubicación seleccionada es aceptable.  @PPara construir la Biblioteca de Alejandría necesitará los servicios de campesinos de un @8Campamento&de&trabajo, canteros de un @363Gremio&de&albañiles y carpinteros de un @363Gremio&de&carpinteros. Los carpinteros necesitarán @94madera para construir andamios, que puede importarse si no la puede obtener en su ciudad. También deberá @47importar mármol blanco de un socio comercial. Para terminar el monumento, necesitará un suministro de @93cobre, ya sea de las minas de su propia ciudad o de un socio comercial.  @PHaga clic derecho en la Biblioteca de Alejandría durante su construcción para obtener un informe de progreso del @369Capataz&de&obra. @L@LHaga clic en @481aquí para saber más sobre la historia de la Biblioteca de Alejandría."
        }
    }
    message_building_pharos_lighthouse {
        id: 489,
        
        size [30, 28]
        title {
            text: "Faro de Faros",
        }
        content {
            text: "El espectacular faro de Faros de Alejandría, de día o de noche, ayuda a guiar a los marineros por los peligrosos bajíos de su puerto. @PEl Faro de Faros solo puede construirse sobre el terreno rocoso de la isla de Faros, en el puerto de Alejandría. Seleccione 'Faro de Faros' en la lista de Estructuras religiosas: monumentos y luego mueva el cursor sobre el terreno cubierto de rocas cerca de la entrada del puerto exterior.  Una vez que la huella del monumento esté completamente en verde, habrá encontrado un emplazamiento adecuado que soportará el enorme peso de esta estructura. @PUna vez despejado el terreno, necesitará un suministro de mármol blanco importado.  Este producto puede obtenerse mediante una @47ruta&comercial con otra ciudad.  Los canteros de un @363Gremio&de&albañiles colocarán con cuidado el mármol blanco que los campesinos de un @8Campamento&de&trabajo traerán desde un @4Almacén. Los campesinos traerán el mármol blanco en cuanto haya al menos cuatro bloques almacenados en un mismo Almacén. Los @363carpinteros de un Gremio de carpinteros y una cantidad de @94madera también serán necesarios para construir los andamios una vez iniciadas las obras. @PHaga clic derecho en el Faro de Faros mientras se construye para ver un informe de progreso de su @369Capataz&de&obra. @L@LHaga clic en @487aquí para saber más sobre el Faro de Faros de Alejandría."
        }
    }
    message_building_caesareum {
        id: 490,
        
        size [30, 28]
        title {
            text: "Cesáreo",
        }
        content {
            text: "Una de las obras arquitectónicas más destacadas de Alejandría es el Cesáreo, un extenso templo junto al mar y un hito visual para los marineros que entran en el enorme puerto de Alejandría. @PPara construir el Cesáreo, primero selecciónelo en la lista de Estructuras religiosas: monumentos del Panel de control. Después de seleccionarlo, verá la huella del edificio. Busque una zona despejada suficientemente grande y coloque el monumento. Sabrá que ha elegido un lugar adecuado cuando la huella esté completamente en verde.  @PUna vez determinado un emplazamiento adecuado, puede comenzar la construcción.  Los campesinos de un @8Campamento&de&trabajo empezarán despejando el terreno, dejando al descubierto la roca madre.  Cuando el terreno esté listo, llegarán los @363canteros de un Gremio de albañiles para colocar el mármol blanco que los campesinos traerán desde un @4Almacén. El mármol blanco debe @47importarse de un socio comercial. Los campesinos arrastrarán el mármol blanco hasta la obra en cuanto haya cuatro bloques almacenados en un mismo Almacén. @P@363Los carpinteros de un Gremio de carpinteros, provistos de @94madera, también serán necesarios para construir los andamios. Si su ciudad no tiene una fuente propia de madera, deberá importarla. Hacia el final del proyecto también hará falta un suministro de granito desde un Almacén, que puede importarse si su ciudad no puede @95extraer su propio granito de una cantera. @PHaga clic derecho en el Cesáreo durante su construcción y su @369Capataz&de&obra le presentará un informe de progreso. @LHaga clic en @482aquí para obtener más información histórica sobre el Cesáreo."
        }
    }
    message_crime_wave {
        id: 491,
        type: 2,
        
        size [30, 20]
        urgent: 1,
        title {
            text: "Ola de crímenes",
        }
        content {
            text: "¡Que los dioses se apiaden de nosotros!  Una banda de codiciosos saqueadores de tumbas, sedientos de riquezas mal habidas, se ha desatado sobre nuestra hermosa ciudad.  ¡Deténgalos antes de que roben las magníficas provisiones funerarias depositadas con nuestros nobles difuntos!"
        }
    }
    message_building_abu_simbel {
        id: 492,
        
        size [30, 28]
        title {
            text: "Abu Simbel",
        }
        content {
            text: "@PEl templo de Abu Simbel es un colosal monumento que Ramsés II mandó excavar en los acantilados de arenisca que dominan el Nilo alto, en Nubia. @PPara comenzar la construcción de Abu Simbel, primero selecciónelo en la lista de Estructuras religiosas: monumentos. Aparecerá una huella del monumento. La mayor parte del monumento debe construirse dentro de los acantilados. La entrada, que sobresale del costado del monumento, debe situarse sobre terreno despejado. Sabrá que ha elegido un buen lugar cuando toda la huella se vuelva verde. Haga clic con el ratón para fijar el monumento en su lugar. @PPuede resultarle útil aplanar temporalmente el terreno del acantilado mientras busca un lugar adecuado para colocar el monumento. Simplemente pulse 'H' o seleccione 'Ocultar acantilados' en la lista de @18superposiciones. Puede restaurar los acantilados a su altura original pulsando 'H' de nuevo o seleccionando 'Normal' en la lista de superposiciones.  @PUna vez designado un emplazamiento adecuado, necesitará una mano de obra capaz, encabezada por @363canteros de un Gremio de albañiles que tallen la roca y @363carpinteros de un Gremio de carpinteros que construyan los andamios necesarios.  Los carpinteros necesitarán @192madera para los andamios, que puede importarse mediante una @47ruta&comercial o extraerse del terreno por un @94Leñador. @PHaga clic derecho en el monumento de Abu Simbel para obtener un informe de progreso de su @369Capataz&de&obra. @L@LHaga clic en @493aquí para saber más sobre el monumento más famoso de Ramsés II."
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
            text: "Historia",
        }
        content {
            text: "@PRamsés el Grande (Ramsés II) gobernó Egipto hacia 1279-1212 a. C.  Este faraón de largo reinado es célebre por los numerosos templos y monumentos construidos durante su reinado, el más grandioso de los cuales fue Abu Simbel.   @PA unas 350 millas al sur de Waset (Tebas), en la provincia de Nubia, los canteros de Ramsés tallaron en los acantilados de arenisca rosada que dominan el valle del Nilo una hilera de cuatro estatuas sedentes del faraón.  Cada estatua mide más de 66 pies de altura: solo la Gran Esfinge de Guiza es más alta.  Las figuras sentadas flanquean la entrada de un túnel que conduce a un santuario interior excavado 160 pies en la roca.  El templo mira al este y fue diseñado de modo que dos veces al año la luz del sol naciente penetra hasta el muro del fondo del santuario, iluminando tres estatuas más pequeñas de Ramsés, Amón y Ra.  También hay en el santuario una estatua de Ptah, pero como está asociado al inframundo, su estatua se sitúa de modo que la luz del sol no caiga sobre ella.  Los relieves del interior del templo también conmemoran las victorias militares de Ramsés.  Cerca, un templo gemelo excavado en los acantilados honra a la diosa Hathor y a la esposa principal de Ramsés, la reina Nefertari.  Todo el conjunto pretendía impresionar a los súbditos nubios y fomentar sus tributos.   @PAbu Simbel se terminó hacia 1256 a. C.  Durante milenios, las arenas lo sepultaron.  En 1817, el arqueólogo Giovanni Belzoni descubrió el enorme monumento.  Amenazado de nuevo a mediados de los años sesenta por las aguas que subían tras la recién construida presa de Asuán, Abu Simbel fue cortado de la roca y reconstruido con gran precisión en un terreno más elevado, una hazaña de ingeniería que sin duda habría impresionado a los antiguos egipcios."
        }
    }
    message_tutorial_major_plagues {
        id: 494
        
        size [30, 28]
        title { text: "Grandes plagas" }
        content { text: "Hay muchas calamidades que pueden azotar a una ciudad, sin importar su tamaño o riqueza, y las grandes plagas son de las peores. Tenga en cuenta, sin embargo, que las grandes plagas no son lo mismo que la @53peste. La peste golpea la ciudad cuando la salud urbana es especialmente mala. Las grandes plagas pueden golpear sin ninguna razón.  @PTodas las grandes plagas provocan un descenso del @39ánimo&de&la&ciudad. Sus otras terribles consecuencias se describen a continuación: @L@LRío de sangre @LCuando el Río de sangre golpea la ciudad, el río y las aguas de su ciudad se volverán sangre durante varios meses y no serán aptos para @44beber&agua ni para otros usos. Parte del agua que las casas almacenan en el lugar también quedará contaminada e imbebible, y quienes viven más cerca del río sentirán más sus efectos. Las personas que viven junto al agua correrán además un riesgo aún mayor de enfermedades y de malaria (para más detalles sobre enfermedades y malaria, vea @53salud&de&la&ciudad). Los @84Muelles&de&pesca, los @59Elevadores&de&agua, los @94Recolectores&de&juncos, los @62Pozos y los @61Suministros&de&agua dejarán de funcionar durante la plaga. Una @354Bast descontenta podría desatar esta plaga sobre su ciudad, o la plaga podría producirse sin motivo alguno. @L@LRanas @LCuando la Plaga de ranas cae sobre su ciudad, legiones de ranas invaden sus fronteras e infestan cualquier casa que atraviesen. Nadie puede vivir en una casa infestada de ranas, así que los habitantes son obligados a salir y nadie puede volver a entrar durante varios meses. Puede intentar contener a las ranas construyendo muros a su alrededor o colocando los edificios estratégicamente para acorralarlas. @352Ptah puede hacer caer esta maldición sobre su ciudad si le desagrada, o las ranas pueden aparecer por voluntad propia. @L@LGranizada @LLos granizos mortales son la progenie de las granizadas, que pueden matar a cualquiera que camine por su ciudad. Los granizos no discriminan y pueden matar a soldados (incluidos los enemigos) y animales con la misma facilidad que a los ciudadanos corrientes. Las granizadas también provocan violentas turbulencias en el río, y muchos de sus barcos pueden hundirse. Si descuida a @353Seth, puede traer este terror a su ciudad. Las granizadas también pueden ser un fenómeno meteorológico natural. @L@LLangostas @LLas langostas descienden sobre la tierra y devoran cualquier cosecha que crezca en sus @45granjas. Los cultivos tanto de la llanura aluvial como de los prados quedarán completamente destruidos justo antes de la cosecha, privando a su ciudad del beneficio de la cosecha de ese año. Cuando haya provocado la ira de @350Osiris, es posible que envíe esta plaga a su ciudad. A veces, sin embargo, las langostas aparecen sin provocación.   @L@LPara saber más sobre las grandes plagas que azotaron la tierra de los faraones, haga clic @495aquí." }
    }
    message_history_major_plagues {
        id: 495,
        
        size [30, 20]
        image {
            id: 1010,
            pos [15, 15]
        }
        title {
            text: "Grandes plagas",
            pos [125, 15]
        }
        subtitle {
            text: "Historia",
        }
        content {
            text: "En el siglo XIII a. C., durante los reinados de Seti I y de su hijo Ramsés el Grande (Ramsés II), los hebreos de Egipto estaban esclavizados para trabajar en proyectos de construcción.  Según el Libro del Éxodo de la Biblia, el Señor Dios se apareció a uno de estos hijos de Israel, el profeta Moisés, y le prometió ayudarles a escapar hacia la libertad.  Guiado así por el Señor, Moisés pidió al faraón que 'dejara ir a mi pueblo' en diez ocasiones distintas, y Ramsés rechazó la petición cada vez. Cada negativa provocó una plaga diferente que afligía al faraón y a los egipcios, mientras perdonaba a los hebreos esclavizados.  Primero, el río se convirtió en sangre, matando a los peces y haciendo el agua no apta para beber.  Tras la segunda negativa del faraón, salieron ranas de los estanques y ríos para infestar las casas de las aldeas. La séptima plaga fue una tormenta de granizo atronadora que golpeó a hombres y bestias en el campo y destruyó los cultivos de cebada y lino.  Según el Libro del Éxodo, la octava negativa de Ramsés a dejar salir de Egipto a los hijos de Israel trajo un enjambre de langostas, que oscureció la tierra con su número y devoró todo lo verde que el granizo de la plaga anterior había dejado. Ramsés cedió tras la décima plaga, que mató a todos los primogénitos egipcios y a sus animales, aunque envió a su ejército en persecución de los hebreos que huían a través del Mar de las Cañas. @PAunque estas plagas no aparecen en los registros egipcios contemporáneos, hay muchos casos de catástrofes similares a lo largo de la historia y de la prehistoria.  Incluso en el siglo XX d. C., las granizadas y los enjambres de langostas han azotado a la humanidad."
        }
    }
    message_mummy_attacks {
        id: 496,
        type: 2,
        
        size [30, 20]
        urgent: 1
        title { text: "¡Ataque de momias!" }
        content { text: "Una momia se ha levantado y camina por las calles de nuestra ciudad.  Detenga esta maldición no muerta antes de que se extienda por toda la tierra." }
    }
    message_wrath_of_bast_lions {
        id: 497,
        type: 2,

        size [30, 20]
        title { text: "Ira de Bastet" }
        video { text: "@20" }
        content { text: "La paciencia de Bastet se ha agotado. Desde sus templos —e incluso desde el zoológico, si tiene uno— desata una manada de leones sobre sus calles. Ciudadanos y soldados se dispersan por igual mientras comienza la caza: honre a la Diosa del Hogar antes de que más sangre manche las calles." }
    }
    message_invasion_quick_battle {
        id: 498,
        type: 7,
        size [30, 16]
        title { text: "Enemigo a las puertas" }
        content { text: "Una fuerza invasora ha llegado a las puertas de la ciudad y espera la batalla. Sus generales resolverán el combate según la fuerza del ejército en unos días, o puede ordenarles que ataquen ahora. El control de las tropas queda suspendido para esta oleada. @PHaga clic en Ir al problema para reabrir el panel de batalla rápida." }
    }
    message_invasion_auto_resolve_win {
        id: 499,
        type: 2,
        size [30, 16]
        title { text: "¡Victoria!" }
        content { text: "Sus generales han resuelto la batalla. Los invasores han sido derrotados. Algunos de sus soldados cayeron en los combates." }
    }
    message_invasion_auto_resolve_lose {
        id: 500,
        type: 2,
        size [30, 16]
        title { text: "Derrota" }
        content { text: "Sus generales informan de la derrota. La fuerza invasora era demasiado poderosa. Muchos de sus soldados han caído, pero el enemigo se retira del campo." }
    }
    message_invasion_bribe_withdraw {
        id: 531,
        type: 2,
        size [30, 16]
        title { text: "Tributo aceptado" }
        content { text: "Los invasores aceptaron su tributo y se retiraron. Su tesoro ha quedado más ligero, pero la ciudad sigue en pie." }
    }
    message_wrath_of_seth_asps {
        id: 501,
        type: 2,

        size [30, 20]
        title { text: "Ira de Seth" }
        video { text: "@21" }
        content { text: "La furia de Seth no encuentra a nadie a quien maldecir, así que envía áspides desde sus templos a sus calles. Los ciudadanos huyen mientras las serpientes cazan. Apacigüe al Dios de la Destrucción antes de que se derrame más sangre." }
    }
    message_wrath_of_ptah_scorpions {
        id: 509,
        type: 2,

        size [30, 20]
        title { text: "Ira de Ptah" }
        video { text: "@22" }
        content { text: "Ptah no encuentra talleres que destrozar, así que envía escorpiones desde sus templos a sus calles. Los ciudadanos se dispersan mientras el aguijón de la ira del artesano los alcanza. Honre al Dios de las Artes antes de que más sangre manche las calles." }
    }

    // Random / .map table events (price_change / demand_change / random_event).
    // Titles align with localization group 19 banner strings used by OG Popup Messages.
    message_kingdome_raises_wages {
        id: 502,
        type: 2,
        size [30, 20]
        title { text: "Salarios aumentados en el reino" }
        content { text: "Los salarios han aumentado en todo el Reino. Sus propios trabajadores podrían marcharse en busca de mejores oportunidades si no cobran tanto como sus homólogos de otras ciudades." }
    }
    message_kingdome_lowers_wages {
        id: 503,
        type: 2,
        size [30, 20]
        title { text: "Salarios reducidos en el reino" }
        content { text: "Los salarios han bajado en todo el Reino de Egipto. Parece que en todas partes la gente trabajará por menos." }
    }
    message_price_increased {
        id: 504,
        type: 2,
        size [30, 20]
        title { text: "Subida de precios" }
        content { text: "El precio de un bien comercial ha subido." }
    }
    message_price_decreased {
        id: 505,
        type: 2,
        size [30, 20]
        title { text: "Bajada de precios" }
        content { text: "El precio de un bien comercial ha bajado." }
    }
    message_increased_trading {
        id: 506,
        type: 2,
        size [30, 20]
        title { text: "El comercio con la ciudad aumenta" }
        content { text: "Una ciudad comercial comprará o venderá más de un bien este año." }
    }
    message_decreased_trading {
        id: 507,
        type: 2,
        size [30, 20]
        title { text: "El comercio con la ciudad disminuye" }
        content { text: "Una ciudad comercial comprará o venderá menos de un bien este año." }
    }
    message_trade_stopped {
        id: 508,
        type: 2,
        size [30, 20]
        title { text: "Comercio detenido" }
        content { text: "Una ciudad comercial ya no comerciará con un bien este año." }
    }

    // Monument completion popups (keys match city_message_post from mastaba/pyramid).
    // Eventmsg PHRASE_* strings are for the event system; these are lang message ids.
    pyramid_congratulations {
        id: 520,
        size [30, 18]
        title { text: "¡Pirámide terminada!" }
        content {
            text: "¡Este es un logro espectacular! Tras innumerables meses de trabajo, ¡la pirámide por fin está completa!"
        }
    }
    stepped_pyramid_congratulations {
        id: 521,
        size [30, 18]
        title { text: "¡Pirámide escalonada terminada!" }
        content {
            text: "¡Por fin está completa la Pirámide escalonada! Este monumento será para siempre un testimonio de sus capacidades."
        }
    }
    bent_pyramid_congratulations {
        id: 522,
        size [30, 18]
        title { text: "¡Pirámide acodada terminada!" }
        content {
            text: "¡La construcción de la Pirámide acodada por fin ha terminado! Es un logro formidable para su ciudad."
        }
    }
    sun_temple_congratulations {
        id: 523,
        size [30, 18]
        title { text: "¡Templo del Sol terminado!" }
        content {
            text: "Tras muchos meses de esfuerzo, las obras del Templo del Sol por fin han concluido. ¡Es un gran logro para su ciudad!"
        }
    }
    abu_simbel_congratulations {
        id: 525,
        size [30, 18]
        title { text: "¡Abu Simbel terminado!" }
        content {
            text: "¡Este es un logro verdaderamente espectacular! Sus hábiles trabajadores han creado un monumento eterno que proclama la gloria de nuestro faraón y el poderío de Egipto."
        }
    }
    caesareum_congratulations {
        id: 526,
        size [30, 18]
        title { text: "¡Cesáreo terminado!" }
        content {
            text: "¡El santo templo y los resplandecientes patios ajardinados del Cesáreo por fin están completos! La noticia de su magnífica belleza ya se extiende por toda la región."
        }
    }
    alex_library_congratulations {
        id: 527,
        size [30, 18]
        title { text: "¡Biblioteca de Alejandría terminada!" }
        content {
            text: "Tras mucho esfuerzo, las bellas puertas labradas a mano de la magnífica Gran Biblioteca de Alejandría están listas para abrirse de par en par a los eruditos del mundo."
        }
    }
    lighthouse_congratulations {
        id: 529,
        size [30, 18]
        title { text: "¡Faro de Faros terminado!" }
        content {
            text: "¡Tras mucho sudor y no poca sangre derramada, los obreros han colocado con cuidado el último bloque de mármol del maravilloso Faro de Faros! Su alta luz ya atrae a comerciantes de todas partes."
        }
    }
    mausoleum_congratulations {
        id: 530,
        size [30, 18]
        title { text: "¡Mausoleo terminado!" }
        content {
            text: "¡El sagrado Mausoleo por fin está completo! Es un logro notable para su ciudad."
        }
    }
    mudbrick_pyramid_congratulations {
        id: 528,
        size [30, 18]
        title { text: "¡Pirámide de ladrillo terminada!" }
        content {
            text: "Los albañiles han dado los últimos retoques al brillante revestimiento exterior de caliza fina, ¡y la Pirámide de ladrillo por fin está terminada!"
        }
    }
    sphinx_congratulations {
        id: 532,
        size [30, 18]
        title { text: "¡Esfinge terminada!" }
        content {
            text: "Por fin los canteros han terminado de tallar la poderosa Esfinge.  Este monumento velará por Egipto durante todas las edades."
        }
    }
    message_dike_breach {
        id: 524,
        type: 2,
        size [30, 16]
        title { text: "Rotura de diques" }
        content { text: "La ira de Osiris ha abierto brechas en los diques de su llanura aluvial. Las cuencas selladas han sido rotas: repare los diques antes de la próxima inundación si quiere aprovechar el don de la crecida." }
    }
}

