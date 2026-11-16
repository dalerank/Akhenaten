log_info("akhenaten: localization_sp config started")

localization_base_sp = [
    { group:1, id:0, text: "Archivo" }
    { group:1, id:1, text: "Nueva partida" }
    { group:1, id:2, text: "Volver a jugar la misión" }
    { group:1, id:3, text: "Cargar partida" }
    { group:1, id:4, text: "Guardar partida" }
    { group:1, id:5, text: "Salir" }
    { group:1, id:6, text: "Eliminar partida" }
    { group:2, id:0, text: "Opciones" }
    { group:2, id:1, text: "Configuración imagen" }
    { group:2, id:2, text: "Configuración sonido" }
    { group:2, id:3, text: "Configuración velocidad" }
    { group:2, id:4, text: "Agilización de las pirámides: ACTIVADA" }
    { group:2, id:5, text: "Agilización de las pirámides: DESACTIVADA" }
    { group:2, id:6, text: "Dificultad" }
    { group:2, id:7, text: "Ciudades: egipcias" }
    { group:2, id:8, text: "Ciudades: clásicas" }
    { group:2, id:9, text: "Autoguardado - activado" }
    { group:2, id:10, text: "Autoguardado - desactivado" }
    { group:2, id:11, text: "Mensajes emergentes" }
    { group:3, id:0, text: "Ayuda" }
    { group:3, id:1, text: "Ayuda" }
    { group:3, id:2, text: "Ayuda del ratón - Inactiva" }
    { group:3, id:3, text: "Ayuda del ratón - Parcial" }
    { group:3, id:4, text: "Ayuda del ratón - Completa" }
    { group:3, id:5, text: "Avisos - Inactiva" }
    { group:3, id:6, text: "Avisos - Activa" }
    { group:3, id:7, text: "Acerca de Faraón" }
    { group:3, id:8, text: "Guía del Editor de mapas" }
    { group:4, id:0, text: "Supervisores" }
    { group:4, id:1, text: "Supervisor de los trabajadores" }
    { group:4, id:2, text: "Supervisor militar" }
    { group:4, id:3, text: "Supervisor político" }
    { group:4, id:4, text: "Supervisor de puntuaciones" }
    { group:4, id:5, text: "Supervisor comercial" }
    { group:4, id:6, text: "Supervisor de la población" }
    { group:4, id:7, text: "Supervisor de salud pública" }
    { group:4, id:8, text: "Supervisor de educación" }
    { group:4, id:9, text: "Supervisor de entretenimiento" }
    { group:4, id:10, text: "Supervisor de los templos" }
    { group:4, id:11, text: "Supervisor del tesoro" }
    { group:4, id:12, text: "Supervisor jefe" }
    { group:4, id:13, text: "Supervisor de monumentos" }
    { group:5, id:0, text: "Salir" }
    { group:5, id:1, text: "¿Abandonar el imperio?" }
    { group:5, id:2, text: "Abrir ruta comercial" }
    { group:5, id:3, text: "¿Pagar para abrir esta ruta comercial por tierra?" }
    { group:5, id:4, text: "Abrir ruta comercial" }
    { group:5, id:5, text: "¿Pagar para abrir esta ruta comercial por mar?" }
    { group:5, id:6, text: "Petición del faraón" }
    { group:5, id:7, text: "¿Despachar bienes?" }
    { group:5, id:8, text: "Petición del faraón" }
    { group:5, id:9, text: "No hay artículos suficientes para cumplir la solicitud." }
    { group:5, id:10, text: "Petición del faraón" }
    { group:5, id:11, text: "No tienes ninguna compañía para enviar" }
    { group:5, id:12, text: "Petición del faraón" }
    { group:5, id:13, text: "Pide al supervisor militar que destine compañías operativas a la protección del imperio" }
    { group:5, id:14, text: "Petición del faraón" }
    { group:5, id:15, text: "¿Enviar fuerzas de refresco?" }
    { group:5, id:16, text: "Demolición de un fuerte" }
    { group:5, id:17, text: "¿Seguro que deseas poner este fuerte fuera de servicio?" }
    { group:5, id:18, text: "CD ausente" }
    { group:5, id:19, text: "Sustituye el CD de \"La Reina del Nilo - Cleopatra\" en la unidad de CD-ROM." }
    { group:5, id:20, text: "Demolición de un puente" }
    { group:5, id:21, text: "Ten cuidado cuando derribes puentes. Las comunidades incomunicadas desaparecen pronto si quedan aisladas de la carretera del imperio." }
    { group:5, id:22, text: "Salir" }
    { group:5, id:23, text: "¿Deseas salir sin guardar la partida?" }
    { group:5, id:24, text: "Versión anterior" }
    { group:5, id:25, text: "Este archivo es de una versión anterior y no se puede cargar" }
    { group:5, id:26, text: "¡Demasiadas provisiones funerarias!" }
    { group:5, id:27, text: "En este escenario no se permiten más de cinco provisiones funerarias." }
    { group:5, id:28, text: "¡Aviso!" }
    { group:5, id:29, text: "Esta provisión funeraria no está disponible en este escenario!" }
    { group:5, id:30, text: "No hay artículos suficientes." }
    { group:5, id:31, text: "No tienes suficientes artículos de esta clase almacenados." }
    { group:5, id:32, text: "Completado." }
    { group:5, id:33, text: "No necesitas más provisiones funerarias para esta mercancía." }
    { group:5, id:34, text: "Número máximo de ciudades" }
    { group:5, id:35, text: "Se ha alcanzado el número máximo de ciudades" }
    { group:5, id:36, text: "Se necesita transporte" }
    { group:5, id:37, text: "Estas tropas deben estar a bordo de un barco de transporte para servir al imperio en el conflicto actual." }
    { group:5, id:38, text: "Se necesitan tropas de tierra" }
    { group:5, id:39, text: "Para servir al imperio en el conflicto actual sólo se necesitan tropas de infantería." }
    { group:5, id:40, text: "No se necesitan tropas" }
    { group:5, id:41, text: "No se necesitan tropas por tierra ni por mar." }
    { group:5, id:42, text: "Tropas en el imperio" }
    { group:5, id:43, text: "Estas tropas no están en la ciudad" }
    { group:5, id:44, text: "Barco de guerra en el imperio" }
    { group:5, id:45, text: "Este barco de guerra no está en la ciudad." }
    { group:5, id:46, text: "No se puede cambiar el precio." }
    { group:5, id:47, text: "Este artículo no está disponible en este escenario." }
    { group:5, id:48, text: "Este edificio no puede funcionar." }
    { group:5, id:49, text: "La ciudad no puede producir ni importar fibra de lino." }
    { group:5, id:50, text: "Este edificio no puede funcionar." }
    { group:5, id:51, text: "La ciudad no puede producir ni importar cerveza." }
    { group:5, id:52, text: "Este edificio no puede funcionar." }
    { group:5, id:53, text: "La ciudad no puede producir ni importar papiro." }
    { group:5, id:54, text: "Los mortuorios no pueden funcionar." }
    { group:5, id:55, text: "La ciudad no puede producir ni importar fibra de lino. Los mortuorios han sido eliminados." }
    { group:5, id:56, text: "El local de Senet no puede funcionar." }
    { group:5, id:57, text: "La ciudad no puede producir ni importar cerveza. Los locales de Senet han sido eliminados." }
    { group:5, id:58, text: "Las escuelas de escribas no pueden funcionar." }
    { group:5, id:59, text: "La ciudad no puede producir ni importar papiros. Las escuelas de escribas han sido eliminadas." }
    { group:5, id:60, text: "Las bibliotecas no pueden funcionar." }
    { group:5, id:61, text: "La ciudad no puede producir ni importar papiros. Las bibliotecas han sido eliminadas." }
    { group:5, id:62, text: "Este edificio no puede funcionar." }
    { group:5, id:63, text: "La ciudad no puede producir ni importar cobre." }
    { group:5, id:64, text: "Las armerías no pueden funcionar." }
    { group:5, id:65, text: "La ciudad no puede producir ni importar cobre. Los armeros han sido eliminados." }
    { group:5, id:66, text: "Este edificio no puede funcionar." }
    { group:5, id:67, text: "La ciudad no puede producir ni importar madera." }
    { group:5, id:68, text: "Los talleres de carros de combate no pueden funcionar." }
    { group:5, id:69, text: "La ciudad no puede producir ni importar madera. Los talleres de carros de combate han sido eliminados." }
    { group:5, id:70, text: "Este edificio no puede funcionar." }
    { group:5, id:71, text: "Esta ciudad no dispone de un reclutador." }
    { group:5, id:72, text: "Fuerte: La infantería no puede trabajar." }
    { group:5, id:73, text: "Esta ciudad no dispone de un reclutador. Fuerte: La infantería ha sido eliminada." }
    { group:5, id:74, text: "Fuerte: Los arqueros no pueden trabajar." }
    { group:5, id:75, text: "Esta ciudad no dispone de un reclutador. Fuerte: Los arqueros han sido eliminados." }
    { group:5, id:76, text: "Fuerte: Los aurigas no pueden trabajar." }
    { group:5, id:77, text: "Esta ciudad no dispone de un reclutador. Fuerte: El auriga ha sido eliminado." }
    { group:5, id:78, text: "Las academias no pueden funcionar" }
    { group:5, id:79, text: "Esta ciudad no dispone de un reclutador. Las academias han sido eliminadas." }
    { group:5, id:80, text: "Este edificio no puede funcionar." }
    { group:5, id:81, text: "La ciudad no puede producir ni importar armas." }
    { group:5, id:82, text: "Este edificio no puede funcionar." }
    { group:5, id:83, text: "La ciudad no puede producir ni importar carros de combate." }
    { group:5, id:84, text: "Fuerte: La infantería no puede trabajar." }
    { group:5, id:85, text: "Esta ciudad no dispone de un armero. Fuerte: La infantería ha sido eliminada." }
    { group:5, id:86, text: "Fuerte: Los aurigas no pueden trabajar." }
    { group:5, id:87, text: "Esta ciudad no dispone de un taller de carros de combate Fuerte: El auriga ha sido eliminado." }
    { group:5, id:88, text: "Fiestas: No hay pabellón." }
    { group:5, id:89, text: "Hace falta una plaza de festivales para celebrar un festival." }
    { group:5, id:90, text: "¿Borrar dinastía?" }
    { group:5, id:91, text: "Esto borrará la dinastía seleccionada y todos los juegos guardados relacionados con ella. ¿Quieres continuar?" }
    { group:5, id:92, text: "La dinastía ya existe" }
    { group:5, id:93, text: "Este nombre ya está en uso. Escoge uno distinto." }
    { group:5, id:94, text: "No hay ninguna dinastía seleccionada" }
    { group:5, id:95, text: "Debes seleccionar una dinastía" }
    { group:5, id:96, text: "Advertencia" }
    { group:5, id:97, text: "No tienes debens suficientes para celebrar un festival." }
    { group:5, id:98, text: "Petición del faraón" }
    { group:5, id:99, text: "No tienes compañías marítimas para enviar" }
    { group:5, id:100, text: "Petición del faraón" }
    { group:5, id:101, text: "Pide a tu supervisor militar que destine compañías marítimas operativas a proteger al imperio" }
    { group:5, id:102, text: "Enviar fuerzas" }
    { group:5, id:103, text: "Las fuerzas que has seleccionado se pueden enviar a varios destinos. Debes decir a tu supervisor político dónde enviar estas tropas." }
    { group:5, id:104, text: "Derribar un monumento" }
    { group:5, id:105, text: "¿Seguro que quieres derribar este monumento?" }
    { group:5, id:106, text: "Derribar un complejo de templos" }
    { group:5, id:107, text: "¿Seguro que tenemos que derribar este complejo de templos?" }
    { group:5, id:108, text: "No se puede guardar" }
    { group:5, id:109, text: "Puntos de caza en lugares no válidos" }
    { group:5, id:110, text: "El archivo ya existe" }
    { group:5, id:111, text: "¿Reemplazar el archivo existente?" }
    { group:5, id:112, text: "No hay vendedores" }
    { group:5, id:113, text: "En la actualidad no hay ciudades que quieran vender esta mercancía." }
    { group:5, id:114, text: "No hay compradores" }
    { group:5, id:115, text: "En la actualidad no hay ciudades que quieran comprar esta mercancía." }
    { group:5, id:116, text: "No abrir ruta comercial" }
    { group:5, id:117, text: "Visita el mapa del mundo para abrir una ruta comercial para exportar esta mercancía." }
    { group:5, id:118, text: "Visita el mapa del mundo para abrir una ruta comercial para importar esta mercancía." }
    { group:5, id:119, text: "Aviso" }
    { group:5, id:120, text: "No tienes suficientes debens para abrir una ruta comercial" }
    { group:5, id:121, text: "No se puede guardar" }
    { group:5, id:122, text: "Demasiados tipos de alimentos (máximo 4)." }
    { group:5, id:123, text: "No se puede editar el mapa del mundo" }
    { group:5, id:124, text: "Para editar el mapa del mundo es necesaria una resolución de pantalla de 800x600 o superior." }
    { group:5, id:125, text: "No se puede salir del mapa del mundo" }
    { group:5, id:126, text: "Demasiados tipos de alimentos (máximo 4)." }
    { group:5, id:127, text: "No se puede guardar" }
    { group:5, id:128, text: "Algunas zonas de pesca están en lugares no válidos." }
    { group:5, id:129, text: "No se puede guardar" }
    { group:5, id:130, text: "Puntos de entrada/salida en lugares no válidos." }
    { group:5, id:131, text: "No se puede guardar" }
    { group:5, id:132, text: "Puntos de entrada de río/salida de río en lugares no válidos." }
    { group:5, id:133, text: "No se puede guardar" }
    { group:5, id:134, text: "Algunos puntos de invasión (terrestres) están en lugares no válidos." }
    { group:5, id:135, text: "No se puede guardar" }
    { group:5, id:136, text: "Algunos puntos de invasión (marítimos) están en lugares no válidos." }
    { group:5, id:137, text: "Faraón" }
    { group:5, id:138, text: "Introduce el CD de \"La Reina del Nilo - Cleopatra\"." }
    { group:5, id:139, text: "El zoológico no puede funcionar." }
    { group:5, id:140, text: "La ciudad no puede producir ni importar carne o paja. Se ha eliminado el zoo." }
    { group:5, id:141, text: "La familia no ganó ninguna misión." }
    { group:5, id:142, text: "Si eres novato en Faraón, pulsa \"Comenzar la historia de la familia\". ¿Continuar?" }
    { group:6, id:0, text: "Db" }
    { group:6, id:1, text: "Pobl" }
    { group:6, id:2, text: "Meses que faltan para completar la misión" }
    { group:6, id:3, text: "meses para la victoria" }
    { group:6, id:4, text: "Capas" }
    { group:6, id:5, text: "Ya has ganado esta misión y has elegido seguir gobernando" }
    { group:6, id:6, text: "Coloca las tumbas sobre precipicios asegurándote de que la entrada esté situada sobre un terreno despejado" }
    { group:7, id:0, text: "Archivo" }
    { group:7, id:1, text: "Nuevo mapa" }
    { group:7, id:2, text: "Cargar mapa" }
    { group:7, id:3, text: "Guardar mapa" }
    { group:7, id:4, text: "Salir editor de mapas" }
    { group:8, id:0, text: "Debens" }
    { group:8, id:1, text: "Deben" }
    { group:8, id:2, text: "Persona" }
    { group:8, id:3, text: "Gente" }
    { group:8, id:4, text: "mes" }
    { group:8, id:5, text: "meses" }
    { group:8, id:6, text: "granero contiene" }
    { group:8, id:7, text: "graneros contienen" }
    { group:8, id:8, text: "año" }
    { group:8, id:9, text: "años" }
    { group:8, id:10, text: "unidad" }
    { group:8, id:11, text: "unid." }
    { group:8, id:12, text: "Empleado" }
    { group:8, id:13, text: "Empleados" }
    { group:8, id:14, text: "persona más" }
    { group:8, id:15, text: "personas más" }
    { group:8, id:16, text: "unidad." }
    { group:8, id:17, text: "unidades." }
    { group:8, id:18, text: "Escuela de escribas" }
    { group:8, id:19, text: "Escuelas de escribas" }
    { group:8, id:20, text: "Academia" }
    { group:8, id:21, text: "Academias" }
    { group:8, id:22, text: "Biblioteca" }
    { group:8, id:23, text: "Bibliotecas" }
    { group:8, id:24, text: "Médico" }
    { group:8, id:25, text: "Médicos" }
    { group:8, id:26, text: "Dentista" }
    { group:8, id:27, text: "Dentistas" }
    { group:8, id:28, text: "Botica" }
    { group:8, id:29, text: "Boticas" }
    { group:8, id:30, text: "Mortuorio" }
    { group:8, id:31, text: "Mortuorios" }
    { group:8, id:32, text: "Oráculo" }
    { group:8, id:33, text: "Oráculos" }
    { group:8, id:34, text: "Quiosco" }
    { group:8, id:35, text: "Quioscos" }
    { group:8, id:36, text: "Quiosco de música" }
    { group:8, id:37, text: "Quioscos de música" }
    { group:8, id:38, text: "Escenario" }
    { group:8, id:39, text: "Escenarios" }
    { group:8, id:40, text: "Juego de senet" }
    { group:8, id:41, text: "Juegos de senet" }
    { group:8, id:42, text: "Mensaje" }
    { group:8, id:43, text: "Mensajes" }
    { group:8, id:44, text: "Día" }
    { group:8, id:45, text: "Días" }
    { group:8, id:46, text: "Soldado" }
    { group:8, id:47, text: "Soldados" }
    { group:8, id:48, text: "Compañía" }
    { group:8, id:49, text: "Compañías" }
    { group:8, id:50, text: "Barco de guerra" }
    { group:8, id:51, text: "Barcos de guerra" }
    { group:8, id:52, text: "Mortuorio" }
    { group:8, id:53, text: "Mortuorios" }
    { group:8, id:54, text: "carga" }
    { group:8, id:55, text: "cargas" }
    { group:8, id:56, text: "Bloque" }
    { group:8, id:57, text: "Bloques" }
    { group:8, id:58, text: "transporte" }
    { group:8, id:59, text: "transportes" }
    { group:9, id:0, text: "Faraón (Expansión de La Reina del Nilo - Cleopatra)" }
    { group:9, id:1, text: "Versión 2.0" }
    { group:9, id:2, text: "Copyright 1999-2000 Sierra On-Line Inc." }
    { group:9, id:3, text: "Estreno beta de: BreakAway Games Tester" }
    { group:9, id:4, text: "test1 string" }
    { group:9, id:5, text: "Pon tu nombre aquí" }
    { group:9, id:6, text: "Ciudad egipcia" }
    { group:9, id:7, text: "Scenario1" }
    { group:9, id:8, text: "Editor de tareas de Faraón" }
    { group:9, id:9, text: "Demo de Faraón" }
    { group:10, id:0, text: "Restablecer" }
    { group:10, id:1, text: "Eliminar zonas mortales" }
    { group:10, id:2, text: "Eliminar pescado" }
    { group:10, id:3, text: "Eliminar invasiones" }
    { group:10, id:4, text: "Eliminar puntos de desembarcos" }
    { group:10, id:5, text: "Eliminar zonas de caza" }
    { group:10, id:6, text: "Cargar desde BMP" }
    { group:10, id:7, text: "Guardar como BMP" }
    { group:10, id:8, text: "Editar imperio" }
    { group:10, id:9, text: "Salvar imperio" }
    { group:10, id:10, text: "Actualizar mapa" }
    { group:11, id:0, text: "Configurando" }
    { group:11, id:1, text: "test_string ,,,¡,°,¿,A,À,Á,Â,Ä, E,È,É,Ê,I,Ì,Í,Î,Ï,N,Ñ,O,Ò,Ó,Ô,Ö, U,Ù,Ú,Û,Ü,ß,a,à,á,â,ä,c,ç, e,è,é,ê,i,ì,í,î,ï,n,ñ,o,ò,ó,ô,ö,u,ù,ú,û,ü,..." }
    { group:11, id:2, text: "Cargando ..." }
    { group:11, id:3, text: "Preparando datos ..." }
    { group:11, id:4, text: "Cargando sonidos ..." }
    { group:11, id:5, text: "Tiempo acelerado" }
    { group:11, id:6, text: "Haz clic derecho para continuar" }
    { group:11, id:7, text: "Cargando fondos ..." }
    { group:11, id:8, text: "Cargando animación ..." }
    { group:11, id:9, text: "Cargando monumentos ..." }
    { group:11, id:10, text: "Cargando enemigos ..." }
    { group:11, id:11, text: "Cargando escenarios ..." }
    { group:12, id:0, text: "Atrás" }
    { group:12, id:1, text: "Ir al lugar del suceso" }
    { group:12, id:2, text: "para aceptar" }
    { group:12, id:3, text: "Las escasas reservas de comida son un problema." }
    { group:12, id:4, text: "El alto desempleo es un problema." }
    { group:12, id:5, text: "Los elevados impuestos son un problema." }
    { group:12, id:6, text: "Los salarios bajos son un problema" }
    { group:12, id:7, text: "Los habitantes de las viviendas de bajo nivel quieren mejores condiciones" }
    { group:13, id:0, text: "Haz clic para continuar" }
    { group:13, id:1, text: "Haz clic derecho para continuar" }
    { group:13, id:2, text: "Juego en pausa (Pulsar 'P' para continuar)" }
    { group:13, id:3, text: "Haz clic derecho para continuar" }
    { group:13, id:4, text: "Cancelar" }
    { group:13, id:5, text: "Continuar" }
    { group:13, id:6, text: "No disponible en la demo!" }
    { group:13, id:7, text: "Haz clic para empezar" }
    { group:13, id:8, text: "Elige un nombre egipcio" }
    { group:14, id:0, text: "Normal" }
    { group:14, id:1, text: "Riesgos" }
    { group:14, id:2, text: "Agua" }
    { group:14, id:3, text: "Entretenimiento" }
    { group:14, id:4, text: "Religión" }
    { group:14, id:5, text: "Educación" }
    { group:14, id:6, text: "Sanidad" }
    { group:14, id:7, text: "Gobierno" }
    { group:14, id:8, text: "Fuego" }
    { group:14, id:9, text: "Daño" }
    { group:14, id:10, text: "Crimen" }
    { group:14, id:11, text: "Total" }
    { group:14, id:12, text: "Malabarista" }
    { group:14, id:13, text: "Músico" }
    { group:14, id:14, text: "Bailarina" }
    { group:14, id:15, text: "Senet" }
    { group:14, id:16, text: "Guardas del Zoo" }
    { group:14, id:17, text: "Total" }
    { group:14, id:18, text: "Escuelas" }
    { group:14, id:19, text: "Biblioteca" }
    { group:14, id:20, text: "Pasos de agua" }
    { group:14, id:21, text: "Dentista" }
    { group:14, id:22, text: "Médico" }
    { group:14, id:23, text: "Botica" }
    { group:14, id:24, text: "Mortuorio" }
    { group:14, id:25, text: "Impuestos" }
    { group:14, id:26, text: "Bazar" }
    { group:14, id:27, text: "Atractivo" }
    { group:14, id:28, text: "Fertilidad" }
    { group:14, id:29, text: "Trabajadores" }
    { group:14, id:30, text: "Nativo" }
    { group:14, id:31, text: "Problemas" }
    { group:14, id:32, text: "Problemas" }
    { group:14, id:33, text: "Cereales" }
    { group:14, id:34, text: "Garbanzos" }
    { group:14, id:35, text: "Granadas" }
    { group:14, id:36, text: "Higos" }
    { group:14, id:37, text: "Carne" }
    { group:14, id:38, text: "Presas de caza" }
    { group:14, id:39, text: "Cerámica" }
    { group:14, id:40, text: "Joyería" }
    { group:14, id:41, text: "Fibra de lino" }
    { group:14, id:42, text: "Cerveza" }
    { group:14, id:43, text: "Enfermedades" }
    { group:14, id:44, text: "Vivienda infectada" }
    { group:14, id:45, text: "Agua" }
    { group:14, id:46, text: "Vivienda vacía" }
    { group:14, id:47, text: "Riego" }
    { group:14, id:48, text: "Malaria" }
    { group:14, id:49, text: "Defensas" }
    { group:14, id:50, text: "Juez" }
    { group:14, id:51, text: "Ocultar precip." }
    { group:15, id:0, text: "Aceptar bienes" }
    { group:15, id:1, text: "Rechazar bienes" }
    { group:15, id:2, text: "Consigue bienes" }
    { group:16, id:0, text: "Edificio" }
    { group:16, id:1, text: "Fábrica" }
    { group:16, id:2, text: "Control" }
    { group:16, id:3, text: "Gfx" }
    { group:16, id:4, text: "Estructura" }
    { group:16, id:5, text: "Red" }
    { group:16, id:6, text: "Aleatorio" }
    { group:16, id:7, text: "Figura" }
    { group:16, id:8, text: "Anim" }
    { group:16, id:9, text: "Sticky" }
    { group:16, id:10, text: "RM_build" }
    { group:16, id:11, text: "Edificio - suministro de agua" }
    { group:16, id:12, text: "Edificio - acceso" }
    { group:16, id:13, text: "Edificio - de capital" }
    { group:16, id:14, text: "Edificio - daños" }
    { group:16, id:15, text: "Edificio - Población" }
    { group:16, id:16, text: "Atractivo" }
    { group:16, id:17, text: "Altura" }
    { group:16, id:18, text: "River sticky" }
    { group:16, id:19, text: "Barb sticky" }
    { group:16, id:20, text: "Daño" }
    { group:16, id:21, text: "Nof figs" }
    { group:16, id:22, text: "Tipo antiguo" }
    { group:16, id:23, text: "Influencia" }
    { group:16, id:24, text: "Wall sticky" }
    { group:16, id:25, text: "Road net" }
    { group:16, id:26, text: "Distrito" }
    { group:17, id:0, text: "Norte" }
    { group:17, id:1, text: "Noreste" }
    { group:17, id:2, text: "Este" }
    { group:17, id:3, text: "Sudeste" }
    { group:17, id:4, text: "Sur" }
    { group:17, id:5, text: "Sudoeste" }
    { group:17, id:6, text: "Oeste" }
    { group:17, id:7, text: "Noroeste" }
    { group:18, id:0, text: "No" }
    { group:18, id:1, text: "Sí" }
    { group:18, id:2, text: "Cancelar" }
    { group:18, id:3, text: "Aceptar" }
    { group:18, id:4, text: "ACTIVADO" }
    { group:18, id:5, text: "DESACTIVADO" }
    { group:18, id:6, text: "N/A" }
    { group:18, id:7, text: "Más datos." }
    { group:18, id:8, text: "y" }
    { group:18, id:9, text: "Volver a intentar" }
    { group:18, id:10, text: "Abandonar" }
    { group:18, id:11, text: "Pasar por alto" }
    { group:19, id:0, text: "Debe construirse en terreno despejado" }
    { group:19, id:1, text: "Sin fondos." }
    { group:19, id:2, text: "Solamente puedes tener un edificio de este tipo" }
    { group:19, id:3, text: "Evolución casa DESACTIVADO" }
    { group:19, id:4, text: "Evolución casa ACTIVADO" }
    { group:19, id:5, text: "Evolución carretera DESACTIVADO" }
    { group:19, id:6, text: "Evolución carretera ACTIVADO" }
    { group:19, id:7, text: "Mostrar gente DESACTIVADO" }
    { group:19, id:8, text: "Mostrar gente ACTIVADO" }
    { group:19, id:9, text: "Este edificio necesita un acceso por carretera" }
    { group:19, id:10, text: "Este edificio no está cerca del agua." }
    { group:19, id:11, text: "No disponible en esta misión." }
    { group:19, id:12, text: "Aún no disponible." }
    { group:19, id:13, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build a large temple" }
    { group:19, id:14, text: "This line should not appear anywhere - You need 2 cartloads of alabaster to build an oracle" }
    { group:19, id:15, text: "La ciudad necesita más trabajadores." }
    { group:19, id:16, text: "La gente consume más comida de la que produce" }
    { group:19, id:17, text: "Construye bazares para distribuir la comida almacenada aquí" }
    { group:19, id:18, text: "Construye granjas en la pradera (busca la hierba amarilla)" }
    { group:19, id:19, text: "Construye pozos de arcilla cerca del agua." }
    { group:19, id:20, text: "Construye esto cerca de zonas rocosas." }
    { group:19, id:21, text: "Construye serrerías cerca de los árboles" }
    { group:19, id:22, text: "Construye esto cerca de zonas rocosas." }
    { group:19, id:23, text: "Explora el río para encontrar un lugar adecuado." }
    { group:19, id:24, text: "Este edificio necesita cobre" }
    { group:19, id:25, text: "Este edificio necesita cebada" }
    { group:19, id:26, text: "Este edificio necesita lino" }
    { group:19, id:27, text: "Este edificio necesita arcilla." }
    { group:19, id:28, text: "Este edificio necesita piedras preciosas" }
    { group:19, id:29, text: "Establece una ruta comercial para su importación." }
    { group:19, id:30, text: "Da instrucciones al supervisor comercial para importarlo" }
    { group:19, id:31, text: "Construye una mina de cobre" }
    { group:19, id:32, text: "Construye una granja de cebada" }
    { group:19, id:33, text: "Construye una granja de lino" }
    { group:19, id:34, text: "Construye un pozo de arcilla." }
    { group:19, id:35, text: "Construye una mina de piedras preciosas" }
    { group:19, id:36, text: "Necesita tener acceso a una bomba de agua para funcionar" }
    { group:19, id:37, text: "Necesita estar cerca del agua para llenarse." }
    { group:19, id:38, text: "Usa acequias de riego para conectar a una bomba de agua" }
    { group:19, id:39, text: "Debe estar cerca de una muralla para enviar patrulla." }
    { group:19, id:40, text: "Necesita un reclutador operativo para conseguir soldados" }
    { group:19, id:41, text: "Algunos soldados necesitarán suministros de armas." }
    { group:19, id:42, text: "Crea un centro de malabarismo para que envíe artistas" }
    { group:19, id:43, text: "Construye un conservatorio para los músicos" }
    { group:19, id:44, text: "Construye una escuela de danza" }
    { group:19, id:45, text: "Construye un local de senet para celebrar partidas" }
    { group:19, id:46, text: "No disponible en la versión de demostración." }
    { group:19, id:47, text: "Solamente puedes construir torres en murallas gruesas." }
    { group:19, id:48, text: "Demasiado cerca de las tropas enemigas." }
    { group:19, id:49, text: "La compañía tiene la moral muy baja para responder." }
    { group:19, id:50, text: "El ejército tiene todos los fuertes que necesita" }
    { group:19, id:51, text: "Guardado automático mensual ACTIVADO" }
    { group:19, id:52, text: "Guardado automático mensual DESACTIVADO" }
    { group:19, id:53, text: "Hay gente en el puente. No puedes derribarlo." }
    { group:19, id:54, text: "Este lago interior no está conectado al mar." }
    { group:19, id:55, text: "No se puede establecer el modo de ventanas." }
    { group:19, id:56, text: "Pon recolectores de caña cerca de terreno pantanoso" }
    { group:19, id:57, text: "Los astilleros necesitan madera para barcos de guerra" }
    { group:19, id:58, text: "Se necesita un palacio para convertir el oro en debens" }
    { group:19, id:59, text: "No puedes construir sobre lugares de cría de animales." }
    { group:19, id:60, text: "Algunas parcelas están demasiado lejos de la carretera" }
    { group:19, id:61, text: "Parte de la ciudad está aislada de la carretera del imperio" }
    { group:19, id:62, text: "El sector estará estancado hasta que se reanude el acceso" }
    { group:19, id:63, text: "Límite de datos; ver archivo Readme (Léeme)" }
    { group:19, id:64, text: "Sólo puedes poner controles de carretera en carreteras" }
    { group:19, id:65, text: "Coloca el otro puerto para transbordadores" }
    { group:19, id:66, text: "No hay lugares adecuados para este transbordador" }
    { group:19, id:67, text: "El imperio ya produce cuatro clases de alimentos." }
    { group:19, id:68, text: "No puedes producir carne sin producir o importar paja." }
    { group:19, id:69, text: "No puedes producir carne en la ciudad. La han eliminado" }
    { group:19, id:70, text: "Sólo tendrás un tipo de piedra en el imperio." }
    { group:19, id:71, text: "Antes debes construir un complejo de templos" }
    { group:19, id:72, text: "Un complejo de templos sólo puede tener oráculo y altar" }
    { group:19, id:73, text: "En los complejos debes colocar oráculos y altares" }
    { group:19, id:74, text: "Esta estructura necesita agua. Ponla en una zona verde." }
    { group:19, id:75, text: "Debes situar este lugar de entretenimiento en un cruce" }
    { group:19, id:76, text: "Antes debes tener un templo terminado." }
    { group:19, id:77, text: "Necesitas 500 papiros para construir una biblioteca." }
    { group:19, id:78, text: "Este edificio necesita cañas" }
    { group:19, id:79, text: "Construye un recolector de caña" }
    { group:19, id:80, text: "Este edificio necesita paja" }
    { group:19, id:81, text: "Construye una granja de cereales" }
    { group:19, id:82, text: "Tu ciudad tiene suficientes dársenas de barcos de guerra" }
    { group:19, id:83, text: "Necesitas 100 cubos de granito para un obelisco pequeño" }
    { group:19, id:84, text: "Necesitas 200 cubos de granito para un obelisco grande" }
    { group:19, id:85, text: "No puedes construir algunos monumentos, se han eliminado" }
    { group:19, id:86, text: "No es posible construir más de un obelisco a la vez" }
    { group:19, id:87, text: "No puedes recaudar impuestos si no tienes un palacio." }
    { group:19, id:88, text: "Necesitas 220 cubos de arenisca para un templo del Sol" }
    { group:19, id:89, text: "No es posible construir más de un templo del Sol a la vez" }
    { group:19, id:90, text: "Hay muy pocos puestos de trabajo para la población actual." }
    { group:19, id:91, text: "El nivel de alimentos es bajo." }
    { group:19, id:92, text: "La gente consume más comida de la que produce." }
    { group:19, id:93, text: "La sanidad es pésima. La epidemia es inminente." }
    { group:19, id:94, text: "La sanidad es terrible y puede haber una epidemia." }
    { group:19, id:95, text: "La sanidad empeora; existe un grave riesgo de epidemia." }
    { group:19, id:96, text: "La sanidad está empeorando y puede surgir una epidemia." }
    { group:19, id:97, text: "La sanidad mejora, pero hay riesgo de epidemia." }
    { group:19, id:98, text: "Aún hay riesgo de epidemia, pero la sanidad mejora." }
    { group:19, id:99, text: "La sanidad mejora, pero la epidemia aún puede azotarla." }
    { group:19, id:100, text: "Han robado en el palacio." }
    { group:19, id:101, text: "Te han robado ahorros personales del palacete." }
    { group:19, id:102, text: "No tenemos tropas para defendernos del inminente ataque." }
    { group:19, id:103, text: "Toda la ciudad te detesta." }
    { group:19, id:104, text: "La gente está muy enfadada:" }
    { group:19, id:105, text: "La gente está enfadada:" }
    { group:19, id:106, text: "La gente está muy disgustada:" }
    { group:19, id:107, text: "La gente está disgustada:" }
    { group:19, id:108, text: "La gente está enojada:" }
    { group:19, id:109, text: "Le eres indiferente a la gente." }
    { group:19, id:110, text: "La gente está satisfecha contigo." }
    { group:19, id:111, text: "La gente está muy satisfecha contigo." }
    { group:19, id:112, text: "La gente está muy satisfecha contigo." }
    { group:19, id:113, text: "La gente te quiere." }
    { group:19, id:114, text: "La gente te idolatra como a un dios." }
    { group:19, id:115, text: "porque no hay suficiente comida." }
    { group:19, id:116, text: "porque no hay suficiente trabajo." }
    { group:19, id:117, text: "porque los impuestos son muy altos." }
    { group:19, id:118, text: "porque los salarios son bajos." }
    { group:19, id:119, text: "hay demasiadas zonas pobres" }
    { group:19, id:120, text: "La gente está emigrando a la ciudad" }
    { group:19, id:121, text: "La falta de vivienda impide la emigración" }
    { group:19, id:122, text: "Los bajos salarios disuaden a los inmigrantes" }
    { group:19, id:123, text: "La falta de empleo frena la inmigración" }
    { group:19, id:124, text: "La falta de alimentos frena la inmigración" }
    { group:19, id:125, text: "Los elevados impuestos frenan la inmigración" }
    { group:19, id:126, text: "Los barrios bajos impiden la inmigración" }
    { group:19, id:127, text: "La escasa moral ciudadana impide la inmigración" }
    { group:19, id:128, text: "La gente abandona la ciudad por la falta de vivienda." }
    { group:19, id:129, text: "La gente abandona la ciudad por los bajos salarios." }
    { group:19, id:130, text: "La gente deja la ciudad a causa del alto desempleo." }
    { group:19, id:131, text: "La gente deja la ciudad debido a la falta de alimentos." }
    { group:19, id:132, text: "La gente prefiere irse antes que pagar los impuestos." }
    { group:19, id:133, text: "Los barrios bajos animan a la gente a marcharse." }
    { group:19, id:134, text: "La moral ciudadana es tan mala que la gente se marcha" }
    { group:19, id:135, text: "Este edificio necesita cerveza para funcionar." }
    { group:19, id:136, text: "Construye una cervecería." }
    { group:19, id:137, text: "Este edificio necesita papiros para funcionar" }
    { group:19, id:138, text: "Crea una fábrica de papiros." }
    { group:19, id:139, text: "Este edificio necesita fibra de lino para funcionar" }
    { group:19, id:140, text: "Crea un telar." }
    { group:19, id:141, text: "Este edificio necesita madera para funcionar" }
    { group:19, id:142, text: "Crea una serrería." }
    { group:19, id:143, text: "Este edificio necesita arcilla y paja" }
    { group:19, id:144, text: "Establece una ruta comercial para importar arcilla" }
    { group:19, id:145, text: "Instruye al supervisor comercial para importar arcilla." }
    { group:19, id:146, text: "Establece una ruta comercial para importar paja" }
    { group:19, id:147, text: "Ordena al supervisor comercial importar paja." }
    { group:19, id:148, text: "Este monumento necesita piedra normal y caliza" }
    { group:19, id:149, text: "Construye una cantera de piedra normal" }
    { group:19, id:150, text: "Establece una ruta comercial para importar piedra normal" }
    { group:19, id:151, text: "Ordena al supervisor comercial importar piedra normal" }
    { group:19, id:152, text: "Construye una cantera de caliza" }
    { group:19, id:153, text: "Establece una ruta comercial para importar caliza" }
    { group:19, id:154, text: "Ordena al supervisor comercial importar caliza" }
    { group:19, id:155, text: "Este  monumento necesita piedra normal" }
    { group:19, id:156, text: "Este monumento necesita caliza" }
    { group:19, id:157, text: "Este monumento necesita ladrillos y caliza" }
    { group:19, id:158, text: "Construye una fábrica de ladrillos" }
    { group:19, id:159, text: "Establece una ruta comercial para importar ladrillos" }
    { group:19, id:160, text: "Instruye al supervisor comercial para importar ladrillo" }
    { group:19, id:161, text: "Este monumento necesita ladrillos y piedra caliza blanca" }
    { group:19, id:162, text: "Este monumento necesita arenisca" }
    { group:19, id:163, text: "Construye una cantera de arenisca" }
    { group:19, id:164, text: "Instruye al supervisor comercial para importar cerveza" }
    { group:19, id:165, text: "Establece una ruta comercial para importar cerveza" }
    { group:19, id:166, text: "Instruye al supervisor comercial para importar cebada" }
    { group:19, id:167, text: "Establece una ruta comercial para importar cebada" }
    { group:19, id:168, text: "Ordena al supervisor comercial importar cañas" }
    { group:19, id:169, text: "Establece una ruta comercial para importar cañas" }
    { group:19, id:170, text: "Instruye al supervisor comercial para importar papiros" }
    { group:19, id:171, text: "Establece una ruta comercial para importar papiros" }
    { group:19, id:172, text: "Da instrucciones al supervisor comercial para importar lino" }
    { group:19, id:173, text: "Establece una ruta comercial para importar lino" }
    { group:19, id:174, text: "Instruye al supervisor comercial para importar lino" }
    { group:19, id:175, text: "Establece una ruta comercial para importar fibra de lino" }
    { group:19, id:176, text: "Los mortuorios no pueden funcionar y han sido eliminados. La ciudad no puede producir ni importar fibra de lino." }
    { group:19, id:177, text: "El local de senet no puede funcionar y ha sido eliminado. La ciudad no puede producir ni importar cerveza." }
    { group:19, id:178, text: "Las escuelas de escribas no pueden funcionar y han sido eliminadas. La ciudad no puede producir ni importar papiros." }
    { group:19, id:179, text: "Las bibliotecas no pueden funcionar y han sido eliminadas. La ciudad no puede producir ni importar papiros." }
    { group:19, id:180, text: "La armería no puede funcionar y ha sido eliminada. La ciudad no puede producir ni importar cobre." }
    { group:19, id:181, text: "El taller de carros no puede funcionar y ha sido eliminado. La ciudad no puede producir ni importar madera." }
    { group:19, id:182, text: "Fuerte: La infantería no puede trabajar y ha sido eliminada. La ciudad no dispone de un reclutador." }
    { group:19, id:183, text: "Fuerte: Los arqueros no pueden trabajar y han sido eliminados. La ciudad no dispone de un reclutador." }
    { group:19, id:184, text: "Fuerte: Los aurigas no pueden trabajar y han sido eliminados. La ciudad no dispone de un reclutador." }
    { group:19, id:185, text: "Las academias no pueden funcionar y han sido eliminadas. La ciudad no puede producir ni importar madera." }
    { group:19, id:186, text: "Fuerte: La infantería no puede trabajar y ha sido eliminada. La ciudad no puede producir ni importar armas." }
    { group:19, id:187, text: "Fuerte: Los aurigas no pueden trabajar y han sido eliminados. La ciudad no producir ni importar aurigas." }
    { group:19, id:188, text: "Necesitas 240 unidades de arenisca para un mausoleo" }
    { group:19, id:189, text: "Crea una cervecería u ordena que se importe cerveza" }
    { group:19, id:190, text: "Crea una cervecería o una ruta para importar cerveza" }
    { group:19, id:191, text: "Construye un taller de papiros u ordena que se importen" }
    { group:19, id:192, text: "Crea un taller de papiros o una ruta para importarlos." }
    { group:19, id:193, text: "Crea un telar u ordena importar fibra de lino." }
    { group:19, id:194, text: "Crea un telar o una ruta comercial para importar lino." }
    { group:19, id:195, text: "Han robado en una oficina de recaudación de impuestos." }
    { group:19, id:196, text: "Unos ladrones han robado un juzgado." }
    { group:19, id:197, text: "Han destruido y saqueado tu palacete." }
    { group:19, id:198, text: "Han destruido y saqueado el palacio." }
    { group:19, id:199, text: "Han saqueado una oficina de recaudación de impuestos." }
    { group:19, id:200, text: "Han destruido y saqueado un juzgado." }
    { group:19, id:201, text: "Han atacado y robado a un trabajador de una mina de oro." }
    { group:19, id:202, text: "Fabrica un granero para almacenar las próximas cosechas" }
    { group:19, id:203, text: "Construye graneros para almacenar las próximas cosechas" }
    { group:19, id:204, text: "No puedes tener más de 10 muelles funcionando a la vez" }
    { group:19, id:205, text: "Construir los santuarios en dos espacios de una carretera" }
    { group:19, id:206, text: "Crea un centro para enviar malabaristas a esta calle" }
    { group:19, id:207, text: "Crea un conservatorio para enviar músicos a esta calle" }
    { group:19, id:208, text: "Crea una escuela para formar bailarines para esta calle" }
    { group:19, id:209, text: "Esta compañía no puede llegar a su destino" }
    { group:19, id:210, text: "Partida guardada." }
    { group:19, id:211, text: "Se debe construir en un lugar despejado" }
    { group:19, id:212, text: "La carretera elevada del monumento debe llevar al agua" }
    { group:19, id:213, text: "Construye la plaza de festivales en un cruce de caminos" }
    { group:19, id:214, text: "No se inmigrará si los enemigos corrompen nuestra tierra" }
    { group:19, id:215, text: "Trampas activadas" }
    { group:19, id:216, text: "Trampas desactivadas" }
    { group:19, id:217, text: "La riada será perfecta" }
    { group:19, id:218, text: "La riada será excelente" }
    { group:19, id:219, text: "La riada será buena" }
    { group:19, id:220, text: "La riada será mediocre" }
    { group:19, id:221, text: "La riada será mala" }
    { group:19, id:222, text: "La riada fallará" }
    { group:19, id:223, text: "Aumento de precio" }
    { group:19, id:224, text: "Disminución de precio" }
    { group:19, id:225, text: "Los salarios bajaron en el imperio." }
    { group:19, id:226, text: "Los salarios aumentaron en el imperio." }
    { group:19, id:227, text: "El comercio disminuye con la ciudad." }
    { group:19, id:228, text: "El comercio aumenta con la ciudad." }
    { group:19, id:229, text: "La reputación del imperio aumenta." }
    { group:19, id:230, text: "Hito de población conseguido." }
    { group:19, id:231, text: "Bendición de un dios menor recibida." }
    { group:19, id:232, text: "El festival está comenzando." }
    { group:19, id:233, text: "Se puede cumplir: los artículos se envían automáticamente." }
    { group:19, id:234, text: "El zoológico no funcionó y fue eliminado. La ciudad no puede producir ni importar paja o carne." }
    { group:19, id:235, text: "Este edificio necesita carne para funcionar." }
    { group:19, id:236, text: "Construye un refugio de caza." }
    { group:19, id:237, text: "Construye un refugio de caza u ordena que importen carne." }
    { group:19, id:238, text: "Construye un refugio o importa carne." }
    { group:19, id:239, text: "Este monumento necesita cobre." }
    { group:19, id:240, text: "Este monumento necesita mármol." }
    { group:19, id:241, text: "¡Sólo puedes crear una Biblioteca de Alejandría!" }
    { group:19, id:242, text: "¡Sólo puedes construir un faro de Pharos!" }
    { group:19, id:243, text: "¡Sólo puedes construir un Caesareum!" }
    { group:19, id:244, text: "La enfermedad ataca." }
    { group:19, id:245, text: "La malaria ataca." }
    { group:19, id:246, text: "Este monumento necesita granito." }
    { group:19, id:247, text: "Debe construirse sobre roca en su totalidad." }
    { group:19, id:248, text: "El faro de Pharos no se puede derribar." }
    { group:19, id:249, text: "¡Los ladrones de tumbas han saqueado una tumba antigua!" }
    { group:19, id:250, text: "¡Han saqueado el mausoleo de Alejandro el Magno!" }
    { group:19, id:251, text: "¡Los ladrones de tumbas han robado provisiones funerarias!" }
    { group:19, id:252, text: "Han arrestado a un ladrón de tumbas." }
    { group:19, id:253, text: "Este edificio necesita aceite y cerámica para funcionar." }
    { group:19, id:254, text: "Construye una alfarería." }
    { group:19, id:255, text: "Establece una ruta comercial para importar cerámica." }
    { group:19, id:256, text: "Ordena al supervisor comercial que importe cerámica." }
    { group:19, id:257, text: "Establece una ruta comercial para importar aceite." }
    { group:19, id:258, text: "Ordena al supervisor comercial que importe aceite." }
    { group:19, id:259, text: "Este edificio necesita henna para funcionar." }
    { group:19, id:260, text: "Construye una granja de henna." }
    { group:19, id:261, text: "Ordena al supervisor comercial que importe henna." }
    { group:19, id:262, text: "Establece una ruta comercial para importar henna." }
    { group:19, id:263, text: "Este edificio necesita aceite para funcionar." }
    { group:19, id:264, text: "Este edificio necesita cerámica para funcionar." }
    { group:19, id:265, text: "Crea un fabricante de pinturas o crea una ruta para importar pintura." }
    { group:19, id:266, text: "Crea un fabricante de pinturas u ordena al supervisor comercial que las importe." }
    { group:19, id:267, text: "Crea un fabricante de pinturas." }
    { group:19, id:268, text: "Este edificio necesita arcilla y pintura para funcionar." }
    { group:19, id:269, text: "Se necesitan empleados" }
    { group:19, id:270, text: "Debes construir enteramente sobre precipicios..." }
    { group:19, id:271, text: "con la entrada sobre un terreno despejado." }
    { group:20, id:0, text: "AC" }
    { group:20, id:1, text: "DC" }
    { group:21, id:0, text: "Elefantina" }
    { group:21, id:1, text: "Abedyú" }
    { group:21, id:2, text: "Oasis de Bahariya" }
    { group:21, id:3, text: "Kuban" }
    { group:21, id:4, text: "Apolinópolis" }
    { group:21, id:5, text: "Bubastis" }
    { group:21, id:6, text: "Buhen" }
    { group:21, id:7, text: "Biblos" }
    { group:21, id:8, text: "Dashur" }
    { group:21, id:9, text: "Oasis de Daila" }
    { group:21, id:10, text: "Abusir" }
    { group:21, id:11, text: "Oasis de Dunqul" }
    { group:21, id:12, text: "Enkomi" }
    { group:21, id:13, text: "Oasis de Farafra" }
    { group:21, id:14, text: "Gaza" }
    { group:21, id:15, text: "Semna" }
    { group:21, id:16, text: "Heracleópolis" }
    { group:21, id:17, text: "Kahun" }
    { group:21, id:18, text: "Mirgisa" }
    { group:21, id:19, text: "Ititawi" }
    { group:21, id:20, text: "Dendera" }
    { group:21, id:21, text: "Jericó" }
    { group:21, id:22, text: "Coptos" }
    { group:21, id:23, text: "Kerma" }
    { group:21, id:24, text: "Oasis de Jarga" }
    { group:21, id:25, text: "Hermópolis" }
    { group:21, id:26, text: "Knossos" }
    { group:21, id:27, text: "Kirene" }
    { group:21, id:28, text: "Meidum" }
    { group:21, id:29, text: "Menfis" }
    { group:21, id:30, text: "Beni Hasán" }
    { group:21, id:31, text: "Micenas" }
    { group:21, id:32, text: "Herakónpolis" }
    { group:21, id:33, text: "Naqada" }
    { group:21, id:34, text: "Heliópolis" }
    { group:21, id:35, text: "Buto" }
    { group:21, id:36, text: "Punt" }
    { group:21, id:37, text: "Qades" }
    { group:21, id:38, text: "Giza" }
    { group:21, id:39, text: "Avaris" }
    { group:21, id:40, text: "Saqqara" }
    { group:21, id:41, text: "Likópolis" }
    { group:21, id:42, text: "Mersa Gawasis" }
    { group:21, id:43, text: "Oasis de Selima" }
    { group:21, id:44, text: "Serabit Jadim" }
    { group:21, id:45, text: "Sai" }
    { group:21, id:46, text: "Sharuhen" }
    { group:21, id:47, text: "Tinis" }
    { group:21, id:48, text: "Timna" }
    { group:21, id:49, text: "Toshka" }
    { group:21, id:50, text: "Tiros" }
    { group:21, id:51, text: "Tebas" }
    { group:21, id:52, text: "Pelusium" }
    { group:21, id:53, text: "Alejandría" }
    { group:21, id:54, text: "Sumur" }
    { group:21, id:55, text: "Deir el-Medina" }
    { group:21, id:56, text: "Abu Simbel" }
    { group:21, id:57, text: "Accio" }
    { group:21, id:58, text: "Roma" }
    { group:21, id:59, text: "Tanis" }
    { group:21, id:60, text: "Pi-Yer" }
    { group:21, id:61, text: "Oasis de Siwi" }
    { group:21, id:62, text: "Maritis" }
    { group:21, id:63, text: "Piramesse" }
    { group:21, id:64, text: "Atenas" }
    { group:21, id:65, text: "Cleoantonópolis" }
    { group:22, id:0, text: "\"Compañía vacía\"" }
    { group:22, id:1, text: "\"Los leones\"" }
    { group:22, id:2, text: "\"Los cocodrilos\"" }
    { group:22, id:3, text: "\"Las cobras\"" }
    { group:22, id:4, text: "\"Los escorpiones\"" }
    { group:22, id:5, text: "\"Los halcones\"" }
    { group:22, id:6, text: "\"Los carneros\"" }
    { group:22, id:7, text: "\"Los leopardos\"" }
    { group:22, id:8, text: "\"Las arañas\"" }
    { group:22, id:9, text: "\"Los gatos\"" }
    { group:22, id:10, text: "\"Las hienas\"" }
    { group:23, id:0, text: "Nada" }
    { group:23, id:1, text: "Cereales" }
    { group:23, id:2, text: "Carne" }
    { group:23, id:3, text: "Lechugas" }
    { group:23, id:4, text: "Garbanzos" }
    { group:23, id:5, text: "Granadas" }
    { group:23, id:6, text: "Higos" }
    { group:23, id:7, text: "Pescado" }
    { group:23, id:8, text: "Caza" }
    { group:23, id:9, text: "Paja" }
    { group:23, id:10, text: "Armas" }
    { group:23, id:11, text: "Arcilla" }
    { group:23, id:12, text: "Ladrillos" }
    { group:23, id:13, text: "Cerámica" }
    { group:23, id:14, text: "Cebada" }
    { group:23, id:15, text: "Cerveza" }
    { group:23, id:16, text: "Lino" }
    { group:23, id:17, text: "Fibra de lino" }
    { group:23, id:18, text: "Piedras preciosas" }
    { group:23, id:19, text: "Artículos de lujo" }
    { group:23, id:20, text: "Madera" }
    { group:23, id:21, text: "Oro" }
    { group:23, id:22, text: "Cañas" }
    { group:23, id:23, text: "Papiro" }
    { group:23, id:24, text: "Piedra normal" }
    { group:23, id:25, text: "Caliza" }
    { group:23, id:26, text: "Granito" }
    { group:23, id:27, text: "Alabastro" }
    { group:23, id:28, text: "Carro de combate" }
    { group:23, id:29, text: "Cobre" }
    { group:23, id:30, text: "Arenisca" }
    { group:23, id:31, text: "Aceite" }
    { group:23, id:32, text: "Henna" }
    { group:23, id:33, text: "Pintura" }
    { group:23, id:34, text: "Lámparas" }
    { group:23, id:35, text: "Mármol" }
    { group:23, id:36, text: "Deben" }
    { group:23, id:37, text: "Tropas" }
    { group:23, id:38, text: "Joyas (artículos de lujo)" }
    { group:23, id:39, text: "Joyas" }
    { group:23, id:40, text: "Vino (artículos de lujo)" }
    { group:23, id:41, text: "Vino" }
    { group:23, id:42, text: "Marfil (artículos de lujo)" }
    { group:23, id:43, text: "Marfil" }
    { group:23, id:44, text: "Ébano (artículos de lujo)" }
    { group:23, id:45, text: "Ébano" }
    { group:23, id:46, text: "Incienso (artículos de lujo)" }
    { group:23, id:47, text: "Incienso" }
    { group:23, id:48, text: "Aceite de oliva (artículos de lujo)" }
    { group:23, id:49, text: "Aceite de oliva" }
    { group:23, id:50, text: "Pieles de leopardo (artículos de lujo)" }
    { group:23, id:51, text: "Pieles de leopardo" }
    { group:23, id:52, text: "Perfume (artículos de lujo)" }
    { group:23, id:53, text: "Perfume" }
    { group:23, id:54, text: "Este espacio se deja en blanco" }
    { group:23, id:55, text: "cestas de cereales" }
    { group:23, id:56, text: "trozos de carne" }
    { group:23, id:57, text: "lechugas" }
    { group:23, id:58, text: "tarros de garbanzos" }
    { group:23, id:59, text: "granadas" }
    { group:23, id:60, text: "tarros de higos" }
    { group:23, id:61, text: "cubos de pescado" }
    { group:23, id:62, text: "partes de presas de caza" }
    { group:23, id:63, text: "balas de paja" }
    { group:23, id:64, text: "armas" }
    { group:23, id:65, text: "bolsas de arcilla" }
    { group:23, id:66, text: "ladrillos" }
    { group:23, id:67, text: "piezas de cerámica" }
    { group:23, id:68, text: "fardos de cebada" }
    { group:23, id:69, text: "ánforas de cerveza" }
    { group:23, id:70, text: "balas de lino" }
    { group:23, id:71, text: "madejas de fibra lino" }
    { group:23, id:72, text: "piedras preciosas" }
    { group:23, id:73, text: "bolsas de artículos de lujo" }
    { group:23, id:74, text: "tablones de madera" }
    { group:23, id:75, text: "oro" }
    { group:23, id:76, text: "cañas" }
    { group:23, id:77, text: "hojas de papiro" }
    { group:23, id:78, text: "bloques de piedra normal" }
    { group:23, id:79, text: "bloques de caliza" }
    { group:23, id:80, text: "bloques de granito" }
    { group:23, id:81, text: "línea sin usar" }
    { group:23, id:82, text: "Carros" }
    { group:23, id:83, text: "lingotes de cobre" }
    { group:23, id:84, text: "bloques de arenisca" }
    { group:23, id:85, text: "tarros de aceite" }
    { group:23, id:86, text: "balas de henna" }
    { group:23, id:87, text: "botes de pintura" }
    { group:23, id:88, text: "lámparas" }
    { group:23, id:89, text: "bloques de mármol" }
    { group:23, id:90, text: "debens" }
    { group:23, id:91, text: "tropas" }
    { group:24, id:0, text: "Semana 1" }
    { group:24, id:1, text: "Semana 2" }
    { group:24, id:2, text: "Semana 3" }
    { group:24, id:3, text: "Semana 4" }
    { group:24, id:4, text: "Semana 5" }
    { group:24, id:5, text: "Semana 6" }
    { group:24, id:6, text: "Semana 7" }
    { group:24, id:7, text: "Semana 8" }
    { group:24, id:8, text: "Semana 9" }
    { group:24, id:9, text: "Semana 10" }
    { group:24, id:10, text: "Semana 11" }
    { group:24, id:11, text: "Semana 12" }
    { group:24, id:12, text: "Semana 13" }
    { group:24, id:13, text: "Semana 14" }
    { group:24, id:14, text: "Semana 15" }
    { group:24, id:15, text: "Semana 16" }
    { group:25, id:0, text: "Ene" }
    { group:25, id:1, text: "Feb" }
    { group:25, id:2, text: "Mar" }
    { group:25, id:3, text: "Abr" }
    { group:25, id:4, text: "May" }
    { group:25, id:5, text: "Jun" }
    { group:25, id:6, text: "Jul" }
    { group:25, id:7, text: "Ago" }
    { group:25, id:8, text: "Sep" }
    { group:25, id:9, text: "Oct" }
    { group:25, id:10, text: "Nov" }
    { group:25, id:11, text: "Dic" }
    { group:26, id:0, text: "Blanco" }
    { group:26, id:1, text: "Rojo" }
    { group:26, id:2, text: "Azul" }
    { group:26, id:3, text: "Verde" }
    { group:26, id:4, text: "Naranja" }
    { group:26, id:5, text: "Plata" }
    { group:26, id:6, text: "Púrpura" }
    { group:26, id:7, text: "Amarillo" }
    { group:26, id:8, text: "Negro" }
    { group:27, id:0, text: "Periodo predinást." }
    { group:27, id:1, text: "Periodo arcaico" }
    { group:27, id:2, text: "Imperio antiguo" }
    { group:27, id:3, text: "Imperio medio" }
    { group:27, id:4, text: "Imperio nuevo" }
    { group:27, id:5, text: "Valle de los Reyes" }
    { group:27, id:6, text: "Ramsés II" }
    { group:27, id:7, text: "Antiguos conquist." }
    { group:27, id:8, text: "Capital" }
    { group:28, id:0, text: "Ningún sitio" }
    { group:28, id:1, text: "Deshacer" }
    { group:28, id:2, text: "Granjas" }
    { group:28, id:3, text: "Materias primas" }
    { group:28, id:4, text: "Gremios de la construcción" }
    { group:28, id:5, text: "Carretera" }
    { group:28, id:6, text: "Muralla de barro" }
    { group:28, id:7, text: "Bomba de agua" }
    { group:28, id:8, text: "Acequia de riego" }
    { group:28, id:9, text: "Excavación" }
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
    { group:28, id:30, text: "Quiosco de música" }
    { group:28, id:31, text: "Quiosco" }
    { group:28, id:32, text: "Local de senet" }
    { group:28, id:33, text: "Pabellón" }
    { group:28, id:34, text: "Conservatorio" }
    { group:28, id:35, text: "Escuela de danza" }
    { group:28, id:36, text: "Escuela de malabarismo" }
    { group:28, id:37, text: "Maestro de senet" }
    { group:28, id:38, text: "Plaza" }
    { group:28, id:39, text: "Jardines" }
    { group:28, id:40, text: "Aurigas" }
    { group:28, id:41, text: "Estatua pequeña" }
    { group:28, id:42, text: "Estatua mediana" }
    { group:28, id:43, text: "Estatua grande" }
    { group:28, id:44, text: "Arqueros" }
    { group:28, id:45, text: "Infantería" }
    { group:28, id:46, text: "Botica" }
    { group:28, id:47, text: "Mortuorio" }
    { group:28, id:48, text: "Monumentos" }
    { group:28, id:49, text: "Dentista" }
    { group:28, id:50, text: "Almacén" }
    { group:28, id:51, text: "Escuela de escribas" }
    { group:28, id:52, text: "Pasos de aguas" }
    { group:28, id:53, text: "Biblioteca" }
    { group:28, id:54, text: "Nada" }
    { group:28, id:55, text: "Comisaría de policía" }
    { group:28, id:56, text: "Triumphal arch (not used?)" }
    { group:28, id:57, text: "Fuertes" }
    { group:28, id:58, text: "Portón de barro" }
    { group:28, id:59, text: "Torre de barro" }
    { group:28, id:60, text: "Templo de Osiris" }
    { group:28, id:61, text: "Templo de Ra" }
    { group:28, id:62, text: "Templo de Ptah" }
    { group:28, id:63, text: "Templo de Set" }
    { group:28, id:64, text: "Templo de Bastet" }
    { group:28, id:65, text: "Complejo de templos de Osiris" }
    { group:28, id:66, text: "Complejo de templos de Ra" }
    { group:28, id:67, text: "Complejo de templos de Ptah" }
    { group:28, id:68, text: "Complejo de templos de Seth" }
    { group:28, id:69, text: "Complejo de templos de Bastet" }
    { group:28, id:70, text: "Bazar" }
    { group:28, id:71, text: "Granero" }
    { group:28, id:72, text: "Almacén" }
    { group:28, id:73, text: "Almacenes" }
    { group:28, id:74, text: "Astillero" }
    { group:28, id:75, text: "Muelle" }
    { group:28, id:76, text: "Dársena pesquera" }
    { group:28, id:77, text: "Palacete privado" }
    { group:28, id:78, text: "Palacete familiar" }
    { group:28, id:79, text: "Palacete de la dinastía" }
    { group:28, id:80, text: "Mission post (not used?)" }
    { group:28, id:81, text: "Puesto de arquitecto" }
    { group:28, id:82, text: "Puente" }
    { group:28, id:83, text: "Puente de barcos" }
    { group:28, id:84, text: "Palacio del pueblo" }
    { group:28, id:85, text: "Palacio de la ciudad" }
    { group:28, id:86, text: "Recaudador de impuestos" }
    { group:28, id:87, text: "Recaudador de impuestos" }
    { group:28, id:88, text: "Nada" }
    { group:28, id:89, text: "Nada" }
    { group:28, id:90, text: "Bomba de agua" }
    { group:28, id:91, text: "Ornamentación" }
    { group:28, id:92, text: "Pozo" }
    { group:28, id:93, text: "Nada" }
    { group:28, id:94, text: "Academia" }
    { group:28, id:95, text: "Reclutador" }
    { group:28, id:96, text: "Templos" }
    { group:28, id:97, text: "Complejo de templos" }
    { group:28, id:98, text: "Oráculo" }
    { group:28, id:99, text: "Ruina en llamas" }
    { group:28, id:100, text: "Cebada" }
    { group:28, id:101, text: "Lino" }
    { group:28, id:102, text: "Cereales" }
    { group:28, id:103, text: "Lechugas" }
    { group:28, id:104, text: "Granadas" }
    { group:28, id:105, text: "Garbanzos" }
    { group:28, id:106, text: "Cantera de piedra normal" }
    { group:28, id:107, text: "Cantera de caliza" }
    { group:28, id:108, text: "Serrería" }
    { group:28, id:109, text: "Pozo de arcilla" }
    { group:28, id:110, text: "Cervecería" }
    { group:28, id:111, text: "Telar" }
    { group:28, id:112, text: "Armería" }
    { group:28, id:113, text: "Joyería" }
    { group:28, id:114, text: "Alfarería" }
    { group:28, id:115, text: "Refugio de caza" }
    { group:28, id:116, text: "Nada" }
    { group:28, id:117, text: "Nada" }
    { group:28, id:118, text: "Nada" }
    { group:28, id:119, text: "Nada" }
    { group:28, id:120, text: "Plateau (not used?)" }
    { group:28, id:121, text: "Crack (not used?)" }
    { group:28, id:122, text: "Anti plateau (not used?)" }
    { group:28, id:123, text: "Nada" }
    { group:28, id:124, text: "Nada" }
    { group:28, id:125, text: "Nada" }
    { group:28, id:126, text: "Nada" }
    { group:28, id:127, text: "Nada" }
    { group:28, id:128, text: "Nada" }
    { group:28, id:129, text: "Nada" }
    { group:28, id:130, text: "TXT_BUILDING_130" }
    { group:28, id:131, text: "TXT_BUILDING_131" }
    { group:28, id:132, text: "TXT_BUILDING_132" }
    { group:28, id:133, text: "TXT_BUILDING_133" }
    { group:28, id:134, text: "TXT_BUILDING_134" }
    { group:28, id:135, text: "TXT_BUILDING_135" }
    { group:28, id:136, text: "Embarcadero del transbordador" }
    { group:28, id:137, text: "TXT_BUILDING_137" }
    { group:28, id:138, text: "Control de carretera" }
    { group:28, id:139, text: "TXT_BUILDING_139" }
    { group:28, id:140, text: "Santuario de Osiris" }
    { group:28, id:141, text: "Santuario de Ra" }
    { group:28, id:142, text: "Santuario de Ptah" }
    { group:28, id:143, text: "Santuario de Seth" }
    { group:28, id:144, text: "Santuario de Bastet" }
    { group:28, id:145, text: "Santuario de" }
    { group:28, id:146, text: "Santuario de" }
    { group:28, id:147, text: "Santuario de" }
    { group:28, id:148, text: "Santuario de" }
    { group:28, id:149, text: "Santuario de" }
    { group:28, id:150, text: "Santuarios" }
    { group:28, id:151, text: "Templo de Osiris" }
    { group:28, id:152, text: "Templo de Ra" }
    { group:28, id:153, text: "Templo de Ptah" }
    { group:28, id:154, text: "Templo de Seth" }
    { group:28, id:155, text: "Templo de Bastet" }
    { group:28, id:156, text: "God 5" }
    { group:28, id:157, text: "God 6" }
    { group:28, id:158, text: "God 7" }
    { group:28, id:159, text: "God 8" }
    { group:28, id:160, text: "God 9" }
    { group:28, id:161, text: "Mina de oro" }
    { group:28, id:162, text: "Mina de piedras preciosas" }
    { group:28, id:163, text: "Piedra corriente" }
    { group:28, id:164, text: "Piedra de mineral" }
    { group:28, id:165, text: "Sin usar" }
    { group:28, id:166, text: "Sin usar" }
    { group:28, id:167, text: "Parque de bomberos" }
    { group:28, id:168, text: "Muralla de ladrillo" }
    { group:28, id:169, text: "Muralla" }
    { group:28, id:170, text: "Portón de ladrillo" }
    { group:28, id:171, text: "Portón" }
    { group:28, id:172, text: "Torre de ladrillo" }
    { group:28, id:173, text: "Torre" }
    { group:28, id:174, text: "Construcciones de barro" }
    { group:28, id:175, text: "Construcciones de ladrillo" }
    { group:28, id:176, text: "Construcciones de defensa" }
    { group:28, id:177, text: "Gremio de carpinteros" }
    { group:28, id:178, text: "Gremio de albañiles" }
    { group:28, id:179, text: "Gremio de canteros" }
    { group:28, id:180, text: "Suministro de agua" }
    { group:28, id:181, text: "Dársena de transporte" }
    { group:28, id:182, text: "Dársena de barcos de guerra" }
    { group:28, id:183, text: "Pirámide" }
    { group:28, id:184, text: "Palacio de justicia" }
    { group:28, id:185, text: "Academia militar 2" }
    { group:28, id:186, text: "Academia militar 3" }
    { group:28, id:187, text: "Palacio del pueblo" }
    { group:28, id:188, text: "Palacio de la ciudad" }
    { group:28, id:189, text: "Palacio de la gran ciudad" }
    { group:28, id:190, text: "Bazar 2" }
    { group:28, id:191, text: "Granero 2" }
    { group:28, id:192, text: "Muelle 2" }
    { group:28, id:193, text: "Almacén 2" }
    { group:28, id:194, text: "Granja de ganado vacuno" }
    { group:28, id:195, text: "Recolector de caña" }
    { group:28, id:196, text: "Granja de higos" }
    { group:28, id:197, text: "Terreno pantanoso" }
    { group:28, id:198, text: "Dunas" }
    { group:28, id:199, text: "Campo de trabajo" }
    { group:28, id:200, text: "Portón de barro" }
    { group:28, id:201, text: "Portón de ladrillo" }
    { group:28, id:202, text: "Portón" }
    { group:28, id:203, text: "Taller de papiro" }
    { group:28, id:204, text: "Fábrica de ladrillos" }
    { group:28, id:205, text: "Taller de cuadrigas" }
    { group:28, id:206, text: "Médico" }
    { group:28, id:207, text: "Placeholder4" }
    { group:28, id:208, text: "Placeholder5" }
    { group:28, id:209, text: "Plaza de festivales" }
    { group:28, id:210, text: "Esfinge" }
    { group:28, id:211, text: "Mejora del complejo de templos" }
    { group:28, id:212, text: "Mejora del complejo de templos" }
    { group:28, id:213, text: "Placeholder10" }
    { group:28, id:214, text: "Punto de desembarco" }
    { group:28, id:215, text: "Cantera de alabastro (¿sin uso?)" }
    { group:28, id:216, text: "Cantera de granito" }
    { group:28, id:217, text: "Mina de cobre" }
    { group:28, id:218, text: "temp" }
    { group:28, id:219, text: "temp" }
    { group:28, id:220, text: "temp" }
    { group:28, id:221, text: "Cantera de arenisca" }
    { group:28, id:222, text: "Mausoleo" }
    { group:28, id:223, text: "Precipicio" }
    { group:28, id:224, text: "Henna" }
    { group:28, id:225, text: "La Biblioteca de Alejandría" }
    { group:28, id:226, text: "Zoológico" }
    { group:28, id:227, text: "El Caesareum" }
    { group:28, id:228, text: "El Faro de Pharos" }
    { group:28, id:229, text: "La tumba funeraria real pequeña" }
    { group:28, id:230, text: "El Abu Simbel" }
    { group:28, id:231, text: "Gremio de artesanos" }
    { group:28, id:232, text: "Fabricante de lámparas" }
    { group:28, id:233, text: "Fabricante de pinturas" }
    { group:28, id:234, text: "La tumba funeraria real mediana" }
    { group:28, id:235, text: "La tumba funeraria real grande" }
    { group:28, id:236, text: "La tumba funeraria real grandiosa" }
    { group:29, id:0, text: "Cabaña rudimentaria" }
    { group:29, id:1, text: "Cabaña resistente" }
    { group:29, id:2, text: "Choza pobre" }
    { group:29, id:3, text: "Choza normal" }
    { group:29, id:4, text: "Casa de campo tosca" }
    { group:29, id:5, text: "Casa de campo corriente" }
    { group:29, id:6, text: "Casa modesta" }
    { group:29, id:7, text: "Casa amplia" }
    { group:29, id:8, text: "Piso modesto" }
    { group:29, id:9, text: "Piso amplio" }
    { group:29, id:10, text: "Residencia normal" }
    { group:29, id:11, text: "Residencia amplia" }
    { group:29, id:12, text: "Residencia elegante" }
    { group:29, id:13, text: "Residencia lujosa" }
    { group:29, id:14, text: "Finca normal" }
    { group:29, id:15, text: "Finca amplia" }
    { group:29, id:16, text: "Finca elegante" }
    { group:29, id:17, text: "Finca majestuosa" }
    { group:29, id:18, text: "Hacienda modesta" }
    { group:29, id:19, text: "Hacienda palaciega" }
    { group:29, id:20, text: "Cabañas rudimentarias" }
    { group:29, id:21, text: "Cabañas resistentes" }
    { group:29, id:22, text: "Chozas pobres" }
    { group:29, id:23, text: "Chozas normales" }
    { group:29, id:24, text: "Casas de campo toscas" }
    { group:29, id:25, text: "Casas de campo" }
    { group:29, id:26, text: "Casas modestas" }
    { group:29, id:27, text: "Casas amplias" }
    { group:29, id:28, text: "Pisos modestos" }
    { group:29, id:29, text: "Pisos amplios" }
    { group:29, id:30, text: "Residencias normales" }
    { group:29, id:31, text: "Residencias amplias" }
    { group:29, id:32, text: "Residencias elegantes" }
    { group:29, id:33, text: "Residencias lujosas" }
    { group:29, id:34, text: "Fincas normales" }
    { group:29, id:35, text: "Fincas amplias" }
    { group:29, id:36, text: "Fincas elegantes" }
    { group:29, id:37, text: "Fincas majestuosas" }
    { group:29, id:38, text: "Haciendas modestas" }
    { group:29, id:39, text: "Haciendas palaciegas" }
    { group:29, id:40, text: "Cabañas rudimentarias:" }
    { group:29, id:41, text: "Cabañas resistentes:" }
    { group:29, id:42, text: "Chozas pobres:" }
    { group:29, id:43, text: "Chozas normales:" }
    { group:29, id:44, text: "Casas de campo toscas:" }
    { group:29, id:45, text: "Casas de campo corrientes:" }
    { group:29, id:46, text: "Casas modestas:" }
    { group:29, id:47, text: "Casas amplias:" }
    { group:29, id:48, text: "Pisos modestos:" }
    { group:29, id:49, text: "Pisos amplios:" }
    { group:29, id:50, text: "Residencias normales:" }
    { group:29, id:51, text: "Residencias amplias:" }
    { group:29, id:52, text: "Residencias elegantes:" }
    { group:29, id:53, text: "Residencias lujosas:" }
    { group:29, id:54, text: "Fincas normales:" }
    { group:29, id:55, text: "Fincas amplias:" }
    { group:29, id:56, text: "Fincas elegantes:" }
    { group:29, id:57, text: "Fincas majestuosas:" }
    { group:29, id:58, text: "Haciendas modestas:" }
    { group:29, id:59, text: "Haciendas palaciegas:" }
    { group:30, id:0, text: "Faraón/La Reina del Nilo" }
    { group:30, id:1, text: "Jugar a la demo de Faraón" }
    { group:30, id:2, text: "Ir a la página web de Faraón" }
    { group:30, id:3, text: "Editor de mapas" }
    { group:30, id:4, text: "Abandonar" }
    { group:30, id:5, text: "Principales familias" }
    { group:31, id:0, text: "Escribe un nombre de familia" }
    { group:31, id:1, text: "Haz clic derecho para continuar" }
    { group:32, id:0, text: "Patriarca de la aldea" }
    { group:32, id:1, text: "Noble de la aldea" }
    { group:32, id:2, text: "Sabio real" }
    { group:32, id:3, text: "Escriba real" }
    { group:32, id:4, text: "Juez real" }
    { group:32, id:5, text: "Alcalde real" }
    { group:32, id:6, text: "Gobernador real" }
    { group:32, id:7, text: "Nomarca" }
    { group:32, id:8, text: "Canciller" }
    { group:32, id:9, text: "Visir" }
    { group:32, id:10, text: "Faraón" }
    { group:32, id:11, text: "Oh, jefe de la aldea" }
    { group:32, id:12, text: "Oh, noble de la aldea" }
    { group:32, id:13, text: "Oh, sabio real" }
    { group:32, id:14, text: "Oh, escriba real" }
    { group:32, id:15, text: "Oh, juez real" }
    { group:32, id:16, text: "Oh, mayordomo real" }
    { group:32, id:17, text: "Oh, gobernador real" }
    { group:32, id:18, text: "Oh, nomarca" }
    { group:32, id:19, text: "Oh, canciller" }
    { group:32, id:20, text: "Oh, visir" }
    { group:32, id:21, text: "Oh, gran faraón" }
    { group:32, id:22, text: "Misión insignificante" }
    { group:32, id:23, text: "Misión muy sencilla" }
    { group:32, id:24, text: "Misión fácil" }
    { group:32, id:25, text: "Misión bastante fácil" }
    { group:32, id:26, text: "Misión normal" }
    { group:32, id:27, text: "Misión bastante difícil" }
    { group:32, id:28, text: "Misión difícil" }
    { group:32, id:29, text: "Misión muy difícil" }
    { group:32, id:30, text: "Misión extremadamente difícil" }
    { group:32, id:31, text: "Misión prácticamente imposible" }
    { group:33, id:0, text: "Mapa diminuto" }
    { group:33, id:1, text: "Mapa pequeño" }
    { group:33, id:2, text: "Mapa mediano" }
    { group:33, id:3, text: "Mapa grande" }
    { group:33, id:4, text: "Mapa enorme" }
    { group:33, id:5, text: "Mapa gigante" }
    { group:33, id:6, text: "Cancelar" }
    { group:34, id:0, text: "Sin invasores" }
    { group:34, id:1, text: "Ejército enemigo" }
    { group:34, id:2, text: "Ejército egipcio" }
    { group:34, id:3, text: "Ejército del faraón" }
    { group:34, id:4, text: "Ejército beduino" }
    { group:35, id:0, text: "ciudad egipcia conquistada" }
    { group:35, id:1, text: "ciudad extranjera conquistada" }
    { group:35, id:2, text: "ruta comercial disponible" }
    { group:35, id:3, text: "ruta comercial cerrada" }
    { group:35, id:4, text: "ciudad comercial sitiada" }
    { group:36, id:0, text: "Atacar cadena de alimentos" }
    { group:36, id:1, text: "Atacar almacenes de oro" }
    { group:36, id:2, text: "Atacar mejores edificios" }
    { group:36, id:3, text: "Atacar tropas" }
    { group:36, id:4, text: "Ataque al azar" }
    { group:37, id:0, text: "Hicsos" }
    { group:37, id:1, text: "Pueblos del mar" }
    { group:37, id:2, text: "Hititas" }
    { group:37, id:3, text: "Mitanios" }
    { group:37, id:4, text: "Cusitas" }
    { group:37, id:5, text: "Libios" }
    { group:37, id:6, text: "Nubios" }
    { group:37, id:7, text: "Cananeos" }
    { group:37, id:8, text: "Asirios" }
    { group:37, id:9, text: "Romanos" }
    { group:37, id:10, text: "Fenicios" }
    { group:37, id:11, text: "Persas" }
    { group:37, id:12, text: "Egipcios" }
    { group:37, id:13, text: "Beduinos" }
    { group:37, id:14, text: "Soldado hicso" }
    { group:37, id:15, text: "Soldado de los pueblos del mar" }
    { group:37, id:16, text: "Soldado hitita" }
    { group:37, id:17, text: "Soldado mitanio" }
    { group:37, id:18, text: "Soldado cusita" }
    { group:37, id:19, text: "Soldado libio" }
    { group:37, id:20, text: "Soldado nubio" }
    { group:37, id:21, text: "Soldado cananeo" }
    { group:37, id:22, text: "Soldado asirio" }
    { group:37, id:23, text: "Soldado romano" }
    { group:37, id:24, text: "Soldado fenicio" }
    { group:37, id:25, text: "Soldado persa" }
    { group:37, id:26, text: "Soldado egipcio" }
    { group:37, id:27, text: "Soldado beduino" }
    { group:37, id:28, text: "el ejército hicso" }
    { group:37, id:29, text: "el ejército de los pueblos del mar" }
    { group:37, id:30, text: "el ejército hitita" }
    { group:37, id:31, text: "el ejército mitanio" }
    { group:37, id:32, text: "el ejército cusita" }
    { group:37, id:33, text: "el ejército libio" }
    { group:37, id:34, text: "el ejército nubio" }
    { group:37, id:35, text: "el ejército cananeo" }
    { group:37, id:36, text: "el ejército asirio" }
    { group:37, id:37, text: "el ejército romano" }
    { group:37, id:38, text: "el ejército fenicio" }
    { group:37, id:39, text: "el ejército persa" }
    { group:37, id:40, text: "el ejército egipcio" }
    { group:37, id:41, text: "el ejército beduino" }
    { group:38, id:0, text: "Sucesos especiales" }
    { group:38, id:1, text: "Terremoto" }
    { group:38, id:2, text: "Rebelión de gladiadores" }
    { group:38, id:3, text: "Cambio de faraón" }
    { group:38, id:4, text: "Problema de comercio marítimo" }
    { group:38, id:5, text: "Problema de comercio terrestre" }
    { group:38, id:6, text: "El faraón sube los salarios" }
    { group:38, id:7, text: "El faraón baja los salarios" }
    { group:38, id:8, text: "Agua contaminada" }
    { group:38, id:9, text: "Derrumbamiento de una mina de oro" }
    { group:38, id:10, text: "Inundación en pozos de arcilla" }
    { group:38, id:11, text: "En uso" }
    { group:38, id:12, text: "Regulación del tiempo" }
    { group:38, id:13, text: "Aleatorio" }
    { group:39, id:0, text: "Nuestra ciudad" }
    { group:39, id:1, text: "Ciudad comercial de Faraón" }
    { group:39, id:2, text: "Ciudad de Faraón" }
    { group:39, id:3, text: "Ciudad comercial egipcia" }
    { group:39, id:4, text: "Ciudad egipcia" }
    { group:39, id:5, text: "Ciudad comercial extranjera" }
    { group:39, id:6, text: "Ciudad extranjera" }
    { group:40, id:0, text: "Ninguna" }
    { group:40, id:1, text: "Menor" }
    { group:40, id:2, text: "Mediano" }
    { group:40, id:3, text: "Mayor" }
    { group:41, id:0, text: "Ningún sitio" }
    { group:41, id:1, text: "Nada" }
    { group:41, id:2, text: "Nada" }
    { group:41, id:3, text: "Nada" }
    { group:41, id:4, text: "Nada" }
    { group:41, id:5, text: "Carretera" }
    { group:41, id:6, text: "Muralla de barro" }
    { group:41, id:7, text: "Acequia de riego" }
    { group:41, id:8, text: "Bomba de agua" }
    { group:41, id:9, text: "Nada" }
    { group:41, id:10, text: "Cabaña rudimentaria" }
    { group:41, id:11, text: "Cabaña resistente" }
    { group:41, id:12, text: "Choza pobre" }
    { group:41, id:13, text: "Choza normal" }
    { group:41, id:14, text: "Casa de campo tosca" }
    { group:41, id:15, text: "Casa de campo corriente" }
    { group:41, id:16, text: "Casa modesta" }
    { group:41, id:17, text: "Casa amplia" }
    { group:41, id:18, text: "Piso modesto" }
    { group:41, id:19, text: "Piso amplio" }
    { group:41, id:20, text: "Residencia normal" }
    { group:41, id:21, text: "Residencia amplia" }
    { group:41, id:22, text: "Residencia elegante" }
    { group:41, id:23, text: "Residencia lujosa" }
    { group:41, id:24, text: "Finca normal" }
    { group:41, id:25, text: "Finca amplia" }
    { group:41, id:26, text: "Finca elegante" }
    { group:41, id:27, text: "Finca majestuosa" }
    { group:41, id:28, text: "Hacienda modesta" }
    { group:41, id:29, text: "Hacienda palaciega" }
    { group:41, id:30, text: "Pabellón de música" }
    { group:41, id:31, text: "Quiosco" }
    { group:41, id:32, text: "Local de senet" }
    { group:41, id:33, text: "Escenario de baile" }
    { group:41, id:34, text: "Conservatorio" }
    { group:41, id:35, text: "Escuela de danza" }
    { group:41, id:36, text: "Escuela de malabaristas" }
    { group:41, id:37, text: "Instrucción de aurigas" }
    { group:41, id:38, text: "Plaza" }
    { group:41, id:39, text: "Jardines" }
    { group:41, id:40, text: "Fuerte de infantería" }
    { group:41, id:41, text: "Estatua pequeña" }
    { group:41, id:42, text: "Estatua mediana" }
    { group:41, id:43, text: "Estatua grande" }
    { group:41, id:44, text: "Arqueros" }
    { group:41, id:45, text: "Infantería" }
    { group:41, id:46, text: "Botica" }
    { group:41, id:47, text: "Mortuorio" }
    { group:41, id:48, text: "Monumentos" }
    { group:41, id:49, text: "Dentista" }
    { group:41, id:50, text: "Centro de distribución" }
    { group:41, id:51, text: "Escuela de escribas" }
    { group:41, id:52, text: "Pasos de aguas" }
    { group:41, id:53, text: "Biblioteca" }
    { group:41, id:54, text: "Nada" }
    { group:41, id:55, text: "Comisaría" }
    { group:41, id:56, text: "Triumphal arch (not used?)" }
    { group:41, id:57, text: "Fuertes" }
    { group:41, id:58, text: "Portón de barro" }
    { group:41, id:59, text: "Torre de barro" }
    { group:41, id:60, text: "Templo de Osiris" }
    { group:41, id:61, text: "Templo de Ra" }
    { group:41, id:62, text: "Templo de Ptah" }
    { group:41, id:63, text: "Templo de Seth" }
    { group:41, id:64, text: "Templo de Bastet" }
    { group:41, id:65, text: "Complejo de templos de Osiris" }
    { group:41, id:66, text: "Complejo de templos de Ra" }
    { group:41, id:67, text: "Complejo de templos de Ptah" }
    { group:41, id:68, text: "Complejo de templos de Seth" }
    { group:41, id:69, text: "Complejo de templos de Bastet" }
    { group:41, id:70, text: "Bazar" }
    { group:41, id:71, text: "Granero" }
    { group:41, id:72, text: "Almacén" }
    { group:41, id:73, text: "Almacenes" }
    { group:41, id:74, text: "Astillero" }
    { group:41, id:75, text: "Muelle" }
    { group:41, id:76, text: "Dársena pesquera" }
    { group:41, id:77, text: "Palacete privado" }
    { group:41, id:78, text: "Palacete familiar" }
    { group:41, id:79, text: "Palacete de la dinastía" }
    { group:41, id:80, text: "Puesto de misión" }
    { group:41, id:81, text: "Puesto de arquitecto" }
    { group:41, id:82, text: "Puente pequeño" }
    { group:41, id:83, text: "Puente grande" }
    { group:41, id:84, text: "Palacio del pueblo" }
    { group:41, id:85, text: "Palacio de la ciudad" }
    { group:41, id:86, text: "Recaudador de impuestos" }
    { group:41, id:87, text: "Recaudador de impuestos" }
    { group:41, id:88, text: "Choza de nativos" }
    { group:41, id:89, text: "Punto de encuentro de nativos" }
    { group:41, id:90, text: "Bomba de agua" }
    { group:41, id:91, text: "Ornamentación" }
    { group:41, id:92, text: "Pozo" }
    { group:41, id:93, text: "Nada" }
    { group:41, id:94, text: "Academia" }
    { group:41, id:95, text: "Reclutador" }
    { group:41, id:96, text: "Nada" }
    { group:41, id:97, text: "Nada" }
    { group:41, id:98, text: "Oráculo" }
    { group:41, id:99, text: "Ruina en llamas" }
    { group:41, id:100, text: "Granja de cebada" }
    { group:41, id:101, text: "Granja de lino" }
    { group:41, id:102, text: "Granja de cereales" }
    { group:41, id:103, text: "Granja de lechugas" }
    { group:41, id:104, text: "Granja de granadas" }
    { group:41, id:105, text: "Granja de garbanzos" }
    { group:41, id:106, text: "Cantera de piedra normal" }
    { group:41, id:107, text: "Cantera de caliza" }
    { group:41, id:108, text: "Serrería" }
    { group:41, id:109, text: "Pozo de arcilla" }
    { group:41, id:110, text: "Cervecería" }
    { group:41, id:111, text: "Telar" }
    { group:41, id:112, text: "Armería" }
    { group:41, id:113, text: "Joyería" }
    { group:41, id:114, text: "Alfarería" }
    { group:41, id:115, text: "Refugio de caza" }
    { group:41, id:116, text: "Hierba" }
    { group:41, id:117, text: "Árboles" }
    { group:41, id:118, text: "Agua" }
    { group:41, id:119, text: "Terremoto" }
    { group:41, id:120, text: "Maleza" }
    { group:41, id:121, text: "Rocas" }
    { group:41, id:122, text: "Pradera" }
    { group:41, id:123, text: "Plateau (not used?)" }
    { group:41, id:124, text: "Anti Plateau (not used?)" }
    { group:41, id:125, text: "Carretera" }
    { group:41, id:126, text: "Punto de invasión" }
    { group:41, id:127, text: "Punto de entrada" }
    { group:41, id:128, text: "Punto de salida" }
    { group:41, id:129, text: "Ramp (not used?)" }
    { group:41, id:130, text: "Entrada de río" }
    { group:41, id:131, text: "Salida de río" }
    { group:41, id:132, text: "Zona de pesca" }
    { group:41, id:133, text: "Zona mortal" }
    { group:41, id:134, text: "Pradera" }
    { group:41, id:135, text: "Riego" }
    { group:41, id:136, text: "Desembarcadero del transbordador" }
    { group:41, id:137, text: "Red de carreteras" }
    { group:41, id:138, text: "No hay acceso" }
    { group:41, id:139, text: "Punto de presas del mapa" }
    { group:41, id:140, text: "Santuario de Osiris" }
    { group:41, id:141, text: "Santuario de Ra" }
    { group:41, id:142, text: "Santuario de Ptah" }
    { group:41, id:143, text: "Santuario de Seth" }
    { group:41, id:144, text: "Santuario de Bastet" }
    { group:41, id:145, text: "Shrine God5" }
    { group:41, id:146, text: "Shrine God6" }
    { group:41, id:147, text: "Shrine God7" }
    { group:41, id:148, text: "Shrine God8" }
    { group:41, id:149, text: "Shrine God9" }
    { group:41, id:150, text: "Santuario" }
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
    { group:41, id:161, text: "Mina de oro" }
    { group:41, id:162, text: "Mina de piedras preciosas" }
    { group:41, id:163, text: "Piedra corriente" }
    { group:41, id:164, text: "Roca de oro" }
    { group:41, id:165, text: "Roca de piedras preciosas" }
    { group:41, id:166, text: "Piedra vista" }
    { group:41, id:167, text: "Parque de bomberos" }
    { group:41, id:168, text: "Muralla de ladrillo" }
    { group:41, id:169, text: "Muralla" }
    { group:41, id:170, text: "Portón de ladrillo" }
    { group:41, id:171, text: "Portón" }
    { group:41, id:172, text: "Torre de ladrillo" }
    { group:41, id:173, text: "Torre" }
    { group:41, id:174, text: "Edificios de barro" }
    { group:41, id:175, text: "Edificios de ladrillo" }
    { group:41, id:176, text: "Edificios de defensa" }
    { group:41, id:177, text: "Gremio de carpinteros" }
    { group:41, id:178, text: "Gremio de albañiles" }
    { group:41, id:179, text: "Gremio de canteros" }
    { group:41, id:180, text: "Suministro de agua" }
    { group:41, id:181, text: "Dársena de barcos de transporte" }
    { group:41, id:182, text: "Dársena de barcos de guerra" }
    { group:41, id:183, text: "Pirámide" }
    { group:41, id:184, text: "Palacio de justicia" }
    { group:41, id:185, text: "Academia militar 2" }
    { group:41, id:186, text: "Academia militar 3" }
    { group:41, id:187, text: "Palacio del pueblo" }
    { group:41, id:188, text: "Palacio de la ciudad" }
    { group:41, id:189, text: "Palacio de la gran ciudad" }
    { group:41, id:190, text: "Bazar 2" }
    { group:41, id:191, text: "Granero 2" }
    { group:41, id:192, text: "Muelle 2" }
    { group:41, id:193, text: "Almacén 2" }
    { group:41, id:194, text: "Granja de ganado vacuno" }
    { group:41, id:195, text: "Recolector de caña" }
    { group:41, id:196, text: "Granja de higos" }
    { group:41, id:197, text: "Terreno pantanoso" }
    { group:41, id:198, text: "Duna" }
    { group:41, id:199, text: "Campo de trabajo" }
    { group:41, id:200, text: "Portón de barro" }
    { group:41, id:201, text: "Portón de ladrillo" }
    { group:41, id:202, text: "Portón" }
    { group:41, id:203, text: "Fabricante de papiro" }
    { group:41, id:204, text: "Fabricante de ladrillos" }
    { group:41, id:205, text: "Taller de cuadrigas" }
    { group:41, id:206, text: "Médico" }
    { group:41, id:207, text: "Placeholder4" }
    { group:41, id:208, text: "Placeholder5" }
    { group:41, id:209, text: "Plaza de festivales" }
    { group:41, id:210, text: "Esfinge" }
    { group:41, id:211, text: "Mejora del complejo de templos" }
    { group:41, id:212, text: "Mejora del complejo de templos" }
    { group:41, id:213, text: "Placeholder10" }
    { group:41, id:214, text: "Punto de desembarco" }
    { group:41, id:215, text: "unused 1474" }
    { group:41, id:216, text: "Cantera de granito" }
    { group:41, id:217, text: "Mina de cobre" }
    { group:41, id:218, text: "temp" }
    { group:41, id:219, text: "temp" }
    { group:41, id:220, text: "temp" }
    { group:41, id:221, text: "Mina de arenisca" }
    { group:41, id:222, text: "Mausoleo" }
    { group:41, id:223, text: "Precipicio" }
    { group:41, id:224, text: "Granja de henna" }
    { group:41, id:225, text: "La Biblioteca de Alejandría" }
    { group:41, id:226, text: "Zoológico" }
    { group:41, id:227, text: "El Caesareum" }
    { group:41, id:228, text: "El Faro de Pharos" }
    { group:41, id:229, text: "La tumba funeraria real pequeña" }
    { group:41, id:230, text: "El Abu Simbel" }
    { group:41, id:231, text: "Gremio de artesanos" }
    { group:41, id:232, text: "Fabricante de lámparas" }
    { group:41, id:233, text: "Fabricante de pinturas" }
    { group:41, id:234, text: "La tumba funeraria real mediana" }
    { group:41, id:235, text: "La tumba funeraria real grande" }
    { group:41, id:236, text: "La tumba funeraria real grandiosa" }
    { group:42, id:0, text: "Opciones" }
    { group:42, id:1, text: "Pantalla completa" }
    { group:42, id:2, text: "Pantalla con ventanas" }
    { group:42, id:3, text: "Resolución 640 x 480" }
    { group:42, id:4, text: "Resolución 800 x 600" }
    { group:42, id:5, text: "Resolución 1024 x 768" }
    { group:42, id:6, text: "Cancelar" }
    { group:43, id:0, text: "Guardando la ciudad" }
    { group:43, id:1, text: "Cargar partida" }
    { group:43, id:2, text: "Este archivo no existe" }
    { group:43, id:3, text: "Guardando una provincia" }
    { group:43, id:4, text: "Cargando una provincia" }
    { group:43, id:5, text: "¿Aplicar?" }
    { group:43, id:6, text: "Eliminar un archivo" }
    { group:44, id:0, text: "Añadir obj." }
    { group:44, id:1, text: "Editar obj." }
    { group:44, id:2, text: "Borrar obj." }
    { group:44, id:3, text: "General" }
    { group:44, id:4, text: "Importar mapa" }
    { group:44, id:5, text: "Compra" }
    { group:44, id:6, text: "No libre" }
    { group:44, id:7, text: "OK" }
    { group:44, id:8, text: "Gráfico simple" }
    { group:44, id:9, text: "Ciudad" }
    { group:44, id:10, text: "Región" }
    { group:44, id:11, text: "Punto de batalla" }
    { group:44, id:12, text: "Gratis" }
    { group:44, id:13, text: "Fecha de inicio." }
    { group:44, id:14, text: "Solicitudes de Faraón" }
    { group:44, id:15, text: "Invasiones" }
    { group:44, id:16, text: "OK" }
    { group:44, id:17, text: "Cancelar" }
    { group:44, id:18, text: "Estado actual del imperio" }
    { group:44, id:19, text: "Sin solicitudes." }
    { group:44, id:20, text: "Sin invasiones." }
    { group:44, id:21, text: "Misión aún no superada" }
    { group:44, id:22, text: "Programación de una invasión" }
    { group:44, id:23, text: "Ranura libre" }
    { group:44, id:24, text: "en" }
    { group:44, id:25, text: "Desprogramar solicitud" }
    { group:44, id:26, text: "Desprogramar invasión" }
    { group:44, id:27, text: "desde" }
    { group:44, id:28, text: "Ruta terrestre" }
    { group:44, id:29, text: "Ruta marítima" }
    { group:44, id:30, text: "Punto de ejército" }
    { group:44, id:31, text: "Punto de enemigo" }
    { group:44, id:32, text: "Ruta" }
    { group:44, id:33, text: "Demanda" }
    { group:44, id:34, text: "Coste" }
    { group:44, id:35, text: "Recursos" }
    { group:44, id:36, text: "Ventas" }
    { group:44, id:37, text: "Descripción breve" }
    { group:44, id:38, text: "Breve descripción de este mapa para los jugadores. Historia, objetivos y consejos, etc." }
    { group:44, id:39, text: "Fondos iniciales" }
    { group:44, id:40, text: "Solicitudes" }
    { group:44, id:41, text: "El enemigo es" }
    { group:44, id:42, text: "Invasiones" }
    { group:44, id:43, text: "¿La capital proporciona cereales?" }
    { group:44, id:44, text: "Edificios autorizados" }
    { group:44, id:45, text: "Criterios de victoria" }
    { group:44, id:46, text: "Ajustar" }
    { group:44, id:47, text: "Estructuras autorizadas" }
    { group:44, id:48, text: "Criterios de victoria" }
    { group:44, id:49, text: "Eventos especiales" }
    { group:44, id:50, text: "Cultura necesaria" }
    { group:44, id:51, text: "Prosperidad necesaria" }
    { group:44, id:52, text: "Número de monumentos" }
    { group:44, id:53, text: "Imperio necesario" }
    { group:44, id:54, text: "Límite de tiempo (tiempo de derrota)" }
    { group:44, id:55, text: "Supervivencia (tiempo de victoria)" }
    { group:44, id:56, text: "Población necesaria" }
    { group:44, id:57, text: "Se necesita punto de terremoto" }
    { group:44, id:58, text: "Punto de terremoto colocado" }
    { group:44, id:59, text: "0 punto de entrada" }
    { group:44, id:60, text: "0 puntos de gente" }
    { group:44, id:61, text: "0 punto de salida" }
    { group:44, id:62, text: "Puntos de gente colocados" }
    { group:44, id:63, text: "0 puntos de invasión" }
    { group:44, id:64, text: "1 punto de invasión" }
    { group:44, id:65, text: "puntos de invasión" }
    { group:44, id:66, text: "0 puntos de río" }
    { group:44, id:67, text: "Puntos de río colocados" }
    { group:44, id:68, text: "Regalos de Faraón" }
    { group:44, id:69, text: "Punto de batalla" }
    { group:44, id:70, text: "Sendero" }
    { group:44, id:71, text: "Orden" }
    { group:44, id:72, text: "Deseos" }
    { group:44, id:73, text: "Imperio" }
    { group:44, id:74, text: "Marcas significativas en" }
    { group:44, id:75, text: "Guardar" }
    { group:44, id:76, text: "Terreno establecido" }
    { group:44, id:77, text: "Clima húmedo" }
    { group:44, id:78, text: "Clima normal" }
    { group:44, id:79, text: "Clima árido" }
    { group:44, id:80, text: "¿Restos flotantes en?" }
    { group:44, id:81, text: "Expansión en" }
    { group:44, id:82, text: "Posiciones ampliadas" }
    { group:44, id:83, text: "Establecer los niveles de demanda/suministro" }
    { group:44, id:84, text: "Ninguna" }
    { group:44, id:85, text: "bajo" }
    { group:44, id:86, text: "medio" }
    { group:44, id:87, text: "alto" }
    { group:44, id:88, text: "Condiciones de comienzo" }
    { group:44, id:89, text: "Ajustar la fecha de inicio" }
    { group:44, id:90, text: "Entrada 90, utilizada tan sólo como marcador" }
    { group:44, id:91, text: "Marca significativa - 25%" }
    { group:44, id:92, text: "Marca significativa - 50%" }
    { group:44, id:93, text: "Marca significativa - 75%" }
    { group:44, id:94, text: "Cambios en la demanda" }
    { group:44, id:95, text: "Eventos" }
    { group:44, id:96, text: "Añadir evento" }
    { group:44, id:97, text: "Borrar evento" }
    { group:44, id:98, text: "en ruta" }
    { group:44, id:99, text: "caídas" }
    { group:44, id:100, text: "subidas" }
    { group:44, id:101, text: "demanda de este producto" }
    { group:44, id:102, text: "1601 sin usar" }
    { group:44, id:103, text: "disminuye un" }
    { group:44, id:104, text: "crece un" }
    { group:44, id:105, text: "Evento no válido" }
    { group:44, id:106, text: "CONSEJO: Emplea las teclas de la coma y el punto para desplazarte rápidamente por los objetos." }
    { group:44, id:107, text: "Abrir partida (sin victorias/derrotas)" }
    { group:44, id:108, text: "Rango inicial" }
    { group:44, id:109, text: "Terreno" }
    { group:44, id:110, text: "Enemigos" }
    { group:44, id:111, text: "Invasiones" }
    { group:44, id:112, text: "Actividad militar inexistente" }
    { group:44, id:113, text: "Pequeñas escaramuzas" }
    { group:44, id:114, text: "Alguna actividad militar" }
    { group:44, id:115, text: "Mucha actividad militar" }
    { group:44, id:116, text: "La ciudad está siendo atacada" }
    { group:44, id:117, text: "Rango" }
    { group:44, id:118, text: "Deben" }
    { group:44, id:119, text: "¿Alimentos de la capital?" }
    { group:44, id:120, text: "Tamaño del mapa" }
    { group:44, id:121, text: "Provincia diminuta" }
    { group:44, id:122, text: "Provincia pequeña" }
    { group:44, id:123, text: "Provincia mediana" }
    { group:44, id:124, text: "Provincia grande" }
    { group:44, id:125, text: "Provincia muy grande" }
    { group:44, id:126, text: "Provincia enorme" }
    { group:44, id:127, text: "Condiciones de victoria" }
    { group:44, id:128, text: "Ninguna" }
    { group:44, id:129, text: "Cultura" }
    { group:44, id:130, text: "Prosperidad" }
    { group:44, id:131, text: "Monumento" }
    { group:44, id:132, text: "Imperio" }
    { group:44, id:133, text: "Personas" }
    { group:44, id:134, text: "Máximo de años" }
    { group:44, id:135, text: "Años de supervivencia" }
    { group:44, id:136, text: "Ir a la ciudad" }
    { group:44, id:137, text: "Se necesita entrada de río" }
    { group:44, id:138, text: "Se necesita salida de río" }
    { group:44, id:139, text: "Evento" }
    { group:44, id:140, text: "mes" }
    { group:44, id:141, text: "entre" }
    { group:44, id:142, text: "y" }
    { group:44, id:143, text: "ciudades" }
    { group:44, id:144, text: "de los puntos" }
    { group:44, id:145, text: "a" }
    { group:44, id:146, text: "cantidad" }
    { group:44, id:147, text: "escala" }
    { group:44, id:148, text: "de" }
    { group:44, id:149, text: "dentro de" }
    { group:44, id:150, text: "meses" }
    { group:44, id:151, text: "Cumplir el evento" }
    { group:44, id:152, text: "Rechazar el evento" }
    { group:44, id:153, text: "Evento tardío" }
    { group:44, id:154, text: "Evento perdido" }
    { group:44, id:155, text: "Evento perder batalla" }
    { group:44, id:156, text: "Siguiente evento" }
    { group:44, id:157, text: "Evento único" }
    { group:44, id:158, text: "Evento repetido" }
    { group:44, id:159, text: "Evento provocado" }
    { group:44, id:160, text: "Provocado por un favor" }
    { group:44, id:161, text: "Faraón" }
    { group:44, id:162, text: "Ciudad" }
    { group:44, id:163, text: "Barcos de guerra" }
    { group:44, id:164, text: "Configuraciones de los dioses" }
    { group:44, id:165, text: "No hay dios protector" }
    { group:44, id:166, text: "Añadir ruta" }
    { group:44, id:167, text: "Editar ruta" }
    { group:44, id:168, text: "Borrar ruta" }
    { group:44, id:169, text: "Ruta general" }
    { group:44, id:170, text: "Ruta marítima" }
    { group:44, id:171, text: "Ruta terrestre" }
    { group:44, id:172, text: "Espaciado" }
    { group:44, id:173, text: "Longitud de la ruta" }
    { group:44, id:174, text: "Nombre" }
    { group:44, id:175, text: "Rango" }
    { group:44, id:176, text: "Complejo de templos" }
    { group:44, id:177, text: "Tipo de interés sobre la deuda" }
    { group:44, id:178, text: "Configuración de la riada" }
    { group:44, id:179, text: "La riada comienza a:" }
    { group:44, id:180, text: "Principios de Junio" }
    { group:44, id:181, text: "Finales de Junio" }
    { group:44, id:182, text: "Principios de Julio" }
    { group:44, id:183, text: "Finales de Julio" }
    { group:44, id:184, text: "Principios de Agosto" }
    { group:44, id:185, text: "Finales de Agosto" }
    { group:44, id:186, text: "Principios de Septiembre" }
    { group:44, id:187, text: "Finales de Septiembre" }
    { group:44, id:188, text: "La riada dura:" }
    { group:44, id:189, text: "Dos meses" }
    { group:44, id:190, text: "Tres meses" }
    { group:44, id:191, text: "Cuatro meses" }
    { group:44, id:192, text: "Calidad de la riada:" }
    { group:44, id:193, text: "Ninguna" }
    { group:44, id:194, text: "Pobre" }
    { group:44, id:195, text: "Mediocre" }
    { group:44, id:196, text: "Buena" }
    { group:44, id:197, text: "Excelente" }
    { group:44, id:198, text: "Perfecta" }
    { group:44, id:199, text: "Riada fallida" }
    { group:44, id:200, text: "Riada perfecta" }
    { group:44, id:201, text: "Seleccionar monumentos" }
    { group:44, id:202, text: "Faraón actual:" }
    { group:44, id:203, text: "Personificación del jugador:" }
    { group:44, id:204, text: "Establecer precios" }
    { group:44, id:205, text: "Compra" }
    { group:44, id:206, text: "Ventas" }
    { group:44, id:207, text: "Aceptar" }
    { group:44, id:208, text: "Rechazar" }
    { group:44, id:209, text: "Posponer" }
    { group:44, id:210, text: "Nivel de las viviendas" }
    { group:44, id:211, text: "Restablecer precios" }
    { group:44, id:212, text: "Dios" }
    { group:44, id:213, text: "1 carga o bloque de piedra = 100 unidades" }
    { group:44, id:214, text: "Modificar este mapa" }
    { group:44, id:215, text: "Jugar a esta misión" }
    { group:44, id:216, text: "Dificultad" }
    { group:44, id:217, text: "Salir" }
    { group:44, id:218, text: "Comenzar la misión" }
    { group:44, id:219, text: "Cancelar" }
    { group:44, id:220, text: "Mostrar resultados anteriores" }
    { group:44, id:221, text: "Mostrar objetivos de la misión" }
    { group:44, id:222, text: "Editor del imperio" }
    { group:44, id:223, text: "Restablecer" }
    { group:44, id:224, text: "Punto de entrada fijado" }
    { group:44, id:225, text: "Punto de salida fijado" }
    { group:44, id:226, text: "1 punto de río fijado" }
    { group:44, id:227, text: "Lucha contra Egipto" }
    { group:45, id:0, text: "Velocidad" }
    { group:45, id:1, text: "Cancelar" }
    { group:45, id:2, text: "Juego" }
    { group:45, id:3, text: "Desplazamiento" }
    { group:45, id:4, text: "Aceptar" }
    { group:46, id:0, text: "Opciones de sonido" }
    { group:46, id:1, text: "Música desactivada." }
    { group:46, id:2, text: "Música activada." }
    { group:46, id:3, text: "Diálogo desactivado." }
    { group:46, id:4, text: "Diálogo activado." }
    { group:46, id:5, text: "Efectos sonido desactivados" }
    { group:46, id:6, text: "Efectos de sonido activados" }
    { group:46, id:7, text: "Sonidos ciudad desactivados" }
    { group:46, id:8, text: "Sonidos de ciudad activados" }
    { group:46, id:9, text: "Cancelar" }
    { group:46, id:10, text: "Estado de sonido actual" }
    { group:46, id:11, text: "Volumen" }
    { group:46, id:12, text: "Aceptar" }
    { group:47, id:0, text: "Una ciudad lejana." }
    { group:47, id:1, text: "¡Nuestra ciudad!" }
    { group:47, id:2, text: "Esta ruta comercial aún no se ha establecido" }
    { group:47, id:3, text: "Coste de apertura" }
    { group:47, id:4, text: "Compra" }
    { group:47, id:5, text: "Ventas" }
    { group:47, id:6, text: "abrir una ruta comercial por tierra" }
    { group:47, id:7, text: "abrir una ruta comercial por agua" }
    { group:47, id:8, text: "Al supervisor comercial" }
    { group:47, id:9, text: "Haz clic sobre una ciudad para obtener información sobre ella." }
    { group:47, id:10, text: "Comprado" }
    { group:47, id:11, text: "Vendido" }
    { group:47, id:12, text: "de" }
    { group:47, id:13, text: "Ciudad egipcia" }
    { group:47, id:14, text: "Ciudad capturada" }
    { group:47, id:15, text: "Un ejército enemigo que amenaza una ciudad del imperio" }
    { group:47, id:16, text: "Tu ejército, que marcha a liberar a una ciudad del imperio" }
    { group:47, id:17, text: "Tu ejército, que vuelve a la ciudad" }
    { group:47, id:18, text: "Lugar de una reciente escaramuza de invasores bárbaros" }
    { group:47, id:19, text: "La ciudad del faraón" }
    { group:48, id:0, text: "Pincel diminuto" }
    { group:48, id:1, text: "Pincel pequeño" }
    { group:48, id:2, text: "Pincel mediano" }
    { group:48, id:3, text: "Pincel grande" }
    { group:48, id:4, text: "Pincel muy grande" }
    { group:48, id:5, text: "Punto de entrada" }
    { group:48, id:6, text: "Punto de salida" }
    { group:48, id:7, text: "Elevar tierra" }
    { group:48, id:8, text: "Rebajar tierra" }
    { group:48, id:9, text: "Rampa de acceso" }
    { group:48, id:10, text: "Punto de invasión 1 (Tierra)" }
    { group:48, id:11, text: "Punto de invasión 2 (Tierra)" }
    { group:48, id:12, text: "Punto de invasión 3 (Tierra)" }
    { group:48, id:13, text: "Punto de invasión 4 (Tierra)" }
    { group:48, id:14, text: "Punto de invasión 5 (Tierra)" }
    { group:48, id:15, text: "Punto de invasión 6 (Tierra)" }
    { group:48, id:16, text: "Punto de invasión 7 (Tierra)" }
    { group:48, id:17, text: "Punto de invasión 8 (Tierra)" }
    { group:48, id:18, text: "Entrada de río" }
    { group:48, id:19, text: "Salida de río" }
    { group:48, id:20, text: "Choza de nativos" }
    { group:48, id:21, text: "Centro de nativos" }
    { group:48, id:22, text: "Campo de nativos" }
    { group:48, id:23, text: "Zona de pesca 1" }
    { group:48, id:24, text: "Zona de pesca 2" }
    { group:48, id:25, text: "Zona de pesca 3" }
    { group:48, id:26, text: "Zona de pesca 4" }
    { group:48, id:27, text: "Zona de pesca 5" }
    { group:48, id:28, text: "Zona de pesca 6" }
    { group:48, id:29, text: "Zona de pesca 7" }
    { group:48, id:30, text: "Zona de pesca 8" }
    { group:48, id:31, text: "Zona mortal 1" }
    { group:48, id:32, text: "Zona mortal 2" }
    { group:48, id:33, text: "Zona mortal 3" }
    { group:48, id:34, text: "Zona mortal 4" }
    { group:48, id:35, text: "Agua" }
    { group:48, id:36, text: "Terreno aluvial" }
    { group:48, id:37, text: "Acequia de riego" }
    { group:48, id:38, text: "Pantano" }
    { group:48, id:39, text: "Zona de caza 1" }
    { group:48, id:40, text: "Zona de caza 2" }
    { group:48, id:41, text: "Zona de caza 3" }
    { group:48, id:42, text: "Zona de caza 4" }
    { group:48, id:43, text: "Roca normal" }
    { group:48, id:44, text: "Rocal de mineral" }
    { group:48, id:45, text: "Roca normal" }
    { group:48, id:46, text: "Roca especial" }
    { group:48, id:47, text: "Dunas de arena" }
    { group:48, id:48, text: "Punto de invasión 9 (Mar)" }
    { group:48, id:49, text: "Punto de invasión 10 (Mar)" }
    { group:48, id:50, text: "Punto de invasión 11 (Mar)" }
    { group:48, id:51, text: "Punto de invasión 12 (Mar)" }
    { group:48, id:52, text: "Punto de invasión 13 (Mar)" }
    { group:48, id:53, text: "Punto de invasión 14 (Mar)" }
    { group:48, id:54, text: "Punto de invasión 15 (Mar)" }
    { group:48, id:55, text: "Punto de invasión 16 (Mar)" }
    { group:48, id:56, text: "Punto de desembarco 1" }
    { group:48, id:57, text: "Punto de desembarco 2" }
    { group:48, id:58, text: "Punto de desembarco 3" }
    { group:48, id:59, text: "Tipo mortal 1" }
    { group:48, id:60, text: "Tipo mortal 2" }
    { group:49, id:0, text: "Allanar tierra" }
    { group:49, id:1, text: "Árboles" }
    { group:49, id:2, text: "Agua" }
    { group:49, id:3, text: "Terremoto" }
    { group:49, id:4, text: "Maleza" }
    { group:49, id:5, text: "Rocas" }
    { group:49, id:6, text: "Pradera" }
    { group:49, id:7, text: "Meseta" }
    { group:49, id:8, text: "Tamaño del pincel" }
    { group:49, id:9, text: "Rampa de acceso" }
    { group:49, id:10, text: "Carretera" }
    { group:49, id:11, text: "Elevar tierra" }
    { group:49, id:12, text: "Rebajar tierra" }
    { group:49, id:13, text: "Punto de invasión" }
    { group:49, id:14, text: "Punto de migración" }
    { group:49, id:15, text: "Punto de entrada" }
    { group:49, id:16, text: "Punto de salida" }
    { group:49, id:17, text: "Punto de río" }
    { group:49, id:18, text: "Entrada de río" }
    { group:49, id:19, text: "Salida de río" }
    { group:49, id:20, text: "Nativos" }
    { group:49, id:21, text: "Choza de nativos" }
    { group:49, id:22, text: "Centro de nativos" }
    { group:49, id:23, text: "Campo de nativos" }
    { group:49, id:24, text: "Aguas de pesca" }
    { group:49, id:25, text: "Zona mortal" }
    { group:49, id:26, text: "Terreno aluvial" }
    { group:49, id:27, text: "Riego" }
    { group:49, id:28, text: "Presa" }
    { group:49, id:29, text: "Pantano" }
    { group:49, id:30, text: "Dunas de arena" }
    { group:49, id:31, text: "Punto de desembarco" }
    { group:49, id:32, text: "Tipo mortal" }
    { group:49, id:33, text: "Precipicio" }
    { group:50, id:0, text: "Supervisor de los trabajadores" }
    { group:50, id:1, text: "Producción y distribución de alimentos" }
    { group:50, id:2, text: "Industria y comercio" }
    { group:50, id:3, text: "Entretenimiento" }
    { group:50, id:4, text: "Religión" }
    { group:50, id:5, text: "Educación" }
    { group:50, id:6, text: "Sanidad y servicios sanitarios" }
    { group:50, id:7, text: "Infraestructuras" }
    { group:50, id:8, text: "Gobierno" }
    { group:50, id:9, text: "Ejército" }
    { group:50, id:10, text: "Necesidad" }
    { group:50, id:11, text: "Posesión" }
    { group:50, id:12, text: "Mano de obra empleada" }
    { group:50, id:13, text: "Mano de obra desempleada (" }
    { group:50, id:14, text: "Salario/10" }
    { group:50, id:15, text: "Deben" }
    { group:50, id:16, text: "inferior a la tasa del imperio de" }
    { group:50, id:17, text: "superior a la tasa del imperio de" }
    { group:50, id:18, text: "(el imperio paga" }
    { group:50, id:19, text: "Coste previsto para este año:" }
    { group:50, id:20, text: "Fijado" }
    { group:50, id:21, text: "Prioridad" }
    { group:50, id:22, text: "Sector" }
    { group:50, id:23, text: "Necesidad" }
    { group:50, id:24, text: "Posesión" }
    { group:50, id:25, text: "Nivel de prioridad." }
    { group:50, id:26, text: "Sin prioridad." }
    { group:50, id:27, text: "1" }
    { group:50, id:28, text: "2" }
    { group:50, id:29, text: "3" }
    { group:50, id:30, text: "4" }
    { group:50, id:31, text: "5" }
    { group:50, id:32, text: "6" }
    { group:50, id:33, text: "7" }
    { group:50, id:34, text: "8" }
    { group:50, id:35, text: "9" }
    { group:51, id:0, text: "Estado del ejército" }
    { group:51, id:1, text: "Ir a la" }
    { group:51, id:2, text: "compañía" }
    { group:51, id:3, text: "Volver" }
    { group:51, id:4, text: "al fuerte" }
    { group:51, id:5, text: "Imperio" }
    { group:51, id:6, text: "servicio" }
    { group:51, id:7, text: "en" }
    { group:51, id:8, text: "No hay informes sobre amenazas a la ciudad" }
    { group:51, id:9, text: "Nos están llegando informes de enemigos avanzando." }
    { group:51, id:10, text: "Nuestros enemigos están a la vista de la ciudad." }
    { group:51, id:11, text: "Un batallón de las tropas del faraón está a las puertas de la ciudad." }
    { group:51, id:12, text: "No tenemos solicitudes de ayuda en el imperio." }
    { group:51, id:13, text: "En algún lugar del imperio necesitan nuestras tropas." }
    { group:51, id:14, text: "Nuestro batallón marcha a salvar una ciudad del imperio" }
    { group:51, id:15, text: "Nuestro batallón regresa a la ciudad." }
    { group:51, id:16, text: "No tienes compañías a las que dar órdenes. Antes debes construir un fuerte para alojar una nueva compañía." }
    { group:51, id:17, text: "Compañía" }
    { group:51, id:18, text: "Experiencia" }
    { group:51, id:19, text: "Estado de la flota de guerra" }
    { group:51, id:20, text: "nave de guerra" }
    { group:51, id:21, text: "a dársena" }
    { group:51, id:22, text: "Fuerza" }
    { group:51, id:23, text: "del casco" }
    { group:51, id:24, text: "Estado de la tripulación" }
    { group:51, id:25, text: "No tienes barcos de guerra a los que dar órdenes. Antes debes construir una dársena para un nuevo barco de guerra." }
    { group:51, id:26, text: "Se necesita a tu flota de guerra en otro sitio" }
    { group:51, id:27, text: "Nuestra compañía ha partido a salvar una ciudad egipcia" }
    { group:51, id:28, text: "Nuestra compañía navega de vuelta a nuestra ciudad" }
    { group:51, id:29, text: "en el extranjero" }
    { group:51, id:30, text: "Envío" }
    { group:51, id:31, text: "ahora" }
    { group:51, id:32, text: "y" }
    { group:52, id:0, text: "Puntuación del imperio" }
    { group:52, id:1, text: "Ahorros de" }
    { group:52, id:2, text: "Dar a la ciudad" }
    { group:52, id:3, text: "Debens por mes" }
    { group:52, id:4, text: "Salario del jefe de la aldea de" }
    { group:52, id:5, text: "Salario del noble de la aldea de" }
    { group:52, id:6, text: "Salario del sabio real de" }
    { group:52, id:7, text: "Salario del escriba real de" }
    { group:52, id:8, text: "Salario del juez real de" }
    { group:52, id:9, text: "Salario del mayordomo real de" }
    { group:52, id:10, text: "Salario del gobernador real de" }
    { group:52, id:11, text: "Salario del nomarca de" }
    { group:52, id:12, text: "Salario del canciller de" }
    { group:52, id:13, text: "Salario del visir de" }
    { group:52, id:14, text: "Salario del faraón de" }
    { group:52, id:15, text: "Establecer nivel de salario" }
    { group:52, id:16, text: "Dar dinero a la ciudad" }
    { group:52, id:17, text: "La donación es" }
    { group:52, id:18, text: "Dar dinero" }
    { group:52, id:19, text: "Todo" }
    { group:52, id:20, text: "Solicitudes actuales" }
    { group:52, id:21, text: "Por el momento no hay solicitudes pendientes." }
    { group:52, id:22, text: "\"La opinión popular echaría tus restos a los chacales.\"" }
    { group:52, id:23, text: "\"Los malabaristas te usan en sus parodias y tu nombre se pronuncia como una maldición.\"" }
    { group:52, id:24, text: "\"Se cree que tu sola presencia provoca la malaria.\"" }
    { group:52, id:25, text: "\"Los boticarios están de acuerdo en que tu nombre es más amargo que ninguna hierba conocida.\"" }
    { group:52, id:26, text: "\"Las madres usan tu nombre para asustar a los niños pequeños.\"" }
    { group:52, id:27, text: "\"Tu nombre nunca se menciona entre gente educada.\"" }
    { group:52, id:28, text: "\"Tu reputación es muy mala y tu propia familia te rechaza.\"" }
    { group:52, id:29, text: "\"Tu nombre es reconocido, pero ridiculizado, en las dos tierras.\"" }
    { group:52, id:30, text: "\"La gente importante conoce tu nombre y tu historia, aunque suele insultarte.\"" }
    { group:52, id:31, text: "\"En el imperio, muy poca gente conoce tu historial, que no impresiona a nadie.\"" }
    { group:52, id:32, text: "\"Los pocos que conocen tu nombre no saben nada más sobre ti.\"" }
    { group:52, id:33, text: "\"Tus escasos logros no son famosos, pero por lo general caes bien a quienes te conocen.\"" }
    { group:52, id:34, text: "\"La gente importante conoce tu historia y por lo general le parece bien lo que has hecho.\"" }
    { group:52, id:35, text: "\"Tu nombre es reconocido y aplaudido por las dos tierras.\"" }
    { group:52, id:36, text: "\"Tu reputación es buena y a menudo te abordan parientes lejanos.\"" }
    { group:52, id:37, text: "\"La sola mención de tu nombre alegra el corazón de aquellos que lo escuchan.\"" }
    { group:52, id:38, text: "\"Las madres de todo el imperio le ponen tu nombre a sus hijos.\"" }
    { group:52, id:39, text: "\"Muchas ciudades egipcias proyectan celebrar festivales en tu honor.\"" }
    { group:52, id:40, text: "\"El baile más popular que recorre Egipto representa la historia de tu vida.\"" }
    { group:52, id:41, text: "\"Los músicos te componen canciones y tu nombre se labra en todos los lugares públicos.\"" }
    { group:52, id:42, text: "\"Todos los habitantes de Egipto desearían servirte eternamente en el Campo de cañas.\"" }
    { group:52, id:43, text: "en almacenes" }
    { group:52, id:44, text: "en los tesoros de la ciudad" }
    { group:52, id:45, text: "Gente" }
    { group:52, id:46, text: "Armas" }
    { group:52, id:47, text: "Enviar pedido" }
    { group:52, id:48, text: "Imposible satisfacer solicitud." }
    { group:52, id:49, text: "Mandar un regalo." }
    { group:52, id:50, text: "Tiempo desde el último regalo" }
    { group:52, id:51, text: "Una tablilla babilónica" }
    { group:52, id:52, text: "Alfombras persas" }
    { group:52, id:53, text: "Tallas antiguas" }
    { group:52, id:54, text: "Marfil africano" }
    { group:52, id:55, text: "Una tropa de esclavos" }
    { group:52, id:56, text: "Pura sangres árabes" }
    { group:52, id:57, text: "Un esclavo educado" }
    { group:52, id:58, text: "Guardaespaldas libios" }
    { group:52, id:59, text: "Guepardos y una jirafa" }
    { group:52, id:60, text: "Un cofre de zafiros" }
    { group:52, id:61, text: "Un carro de oro" }
    { group:52, id:62, text: "Un barco de cedro libanés" }
    { group:52, id:63, text: "Modesto:" }
    { group:52, id:64, text: "Generoso:" }
    { group:52, id:65, text: "Lujoso:" }
    { group:52, id:66, text: "Mandar regalo modesto" }
    { group:52, id:67, text: "Mandar regalo generoso" }
    { group:52, id:68, text: "Mandar regalo lujoso" }
    { group:52, id:69, text: "Dar al pueblo de Egipto" }
    { group:52, id:70, text: "No tienes suficientes ahorros personales para hacer un regalo a Egipto. Prueba a subirte el salario." }
    { group:52, id:71, text: "Aviso: Si te asignas un salario mayor al que corresponde a tu rango actual no causarás muy buena impresión." }
    { group:52, id:72, text: "Envía tropas para proteger" }
    { group:52, id:73, text: "Un pequeño ejercito atacará en" }
    { group:52, id:74, text: "Una fuerza mediana atacará" }
    { group:52, id:75, text: "Un grande ejercito atacará en" }
    { group:52, id:76, text: "Ahora puedes fijar libremente tu salario." }
    { group:52, id:77, text: "El palacio te prohibe cobrar un salario mientras sigas gobernando a tu libre albedrío." }
    { group:52, id:78, text: "Necesitas construir un palacete para cobrar un salario." }
    { group:52, id:79, text: "debens perdidos este año por robos." }
    { group:52, id:80, text: "Envía tropas por agua para proteger" }
    { group:52, id:81, text: "Supervisor político para" }
    { group:53, id:0, text: "Puntuaciones" }
    { group:53, id:1, text: "Cultura" }
    { group:53, id:2, text: "Prosperidad" }
    { group:53, id:3, text: "Monumentos" }
    { group:53, id:4, text: "Imperio" }
    { group:53, id:5, text: "exigidos" }
    { group:53, id:6, text: "Población:" }
    { group:53, id:7, text: "(Sin objetivo de población)" }
    { group:53, id:8, text: "Haz clic sobre una puntuación para obtener información." }
    { group:53, id:9, text: "Tienes muy pocos malabaristas en la ciudad. Si hubiera más, mejoraría esta puntuación." }
    { group:53, id:10, text: "Tienes muy pocos músicos en la ciudad. Si hubiera más, mejoraría esta puntuación." }
    { group:53, id:11, text: "Tienes muy pocos bailarines en la ciudad. Si hubiera más, mejoraría esta puntuación." }
    { group:53, id:12, text: "Tienes muy pocos locales de senet en la ciudad. Si hubiera más, mejoraría esta puntuación." }
    { group:53, id:13, text: "Hay muy pocos zoológicos en la ciudad. Si puedes, construye zoológicos para mejorar esta puntuación." }
    { group:53, id:14, text: "Tienes muy pocos lugares de culto en la ciudad. Construir más mejoraría esta puntuación." }
    { group:53, id:15, text: "Tienes muy pocas escuelas de escribas en la ciudad. Si hubiera más, mejoraría esta puntuación." }
    { group:53, id:16, text: "Tienes muy pocas bibliotecas en la ciudad. Construir más mejoraría esta puntuación." }
    { group:53, id:17, text: "No hay suficientes casas con acceso al dentista. Un mejor acceso mejorará esta puntuación." }
    { group:53, id:18, text: "No hay suficientes casas con acceso al médico. Un mejor acceso mejorará esta puntuación." }
    { group:53, id:19, text: "No hay suficientes casas con acceso al mortuorio. Un mejor acceso mejorará esta puntuación." }
    { group:53, id:20, text: "la puntuación está aumentando." }
    { group:53, id:21, text: "la puntuación está bajando." }
    { group:53, id:22, text: "la puntuación está estancada." }
    { group:53, id:23, text: "La calidad general de las viviendas de la ciudad hace que la puntuación disminuya. Mejorar las viviendas la aumentará." }
    { group:53, id:24, text: "El año pasado tu ciudad tuvo pérdidas, lo cual redujo su prosperidad." }
    { group:53, id:25, text: "El elevado desempleo en la ciudad está retardando la puntuación de prosperidad." }
    { group:53, id:26, text: "Pagar salarios inferiores a los del imperio empaña la imagen de prosperidad de tu ciudad." }
    { group:53, id:27, text: "La alta concentración de personas de barrio bajo en la ciudad le otorga la apariencia de una ciudad pobre." }
    { group:53, id:28, text: "Tu incapacidad para pagar el tributo anual al faraón indica que tu ciudad ha fracasado." }
    { group:53, id:29, text: "La falta de variedad de los alimentos perjudica tu prosperidad." }
    { group:53, id:30, text: "La falta de trabajadores reduce tu prosperidad." }
    { group:53, id:31, text: "La ciudad es más próspera cuando las ganancias por exportación son mayores que los gastos por importación." }
    { group:53, id:32, text: "La consideración en el imperio de tu ciudad está descendiendo. Paga el tributo anual, cobra un salario razonable y coopera con las solicitudes." }
    { group:53, id:33, text: "El salario tan ridículamente alto que te pagas enfada al faraón y disminuye la consideración en el imperio." }
    { group:53, id:34, text: "Tu continua incapacidad para pagar un tributo disminuye la consideración en el imperio de la ciudad." }
    { group:53, id:35, text: "La solicitud que cancelaste recientemente perjudica al prestigio de tu ciudad en el imperio." }
    { group:53, id:36, text: "El salario que te has asignado sobrepasa el de tu rango y perjudica a tu reputación en el imperio." }
    { group:53, id:37, text: "Por segundo año consecutivo, no has pagado el tributo y la puntuación de tu ciudad se ve afectada." }
    { group:53, id:38, text: "Tu respuesta ante determinados acontecimientos ha perjudicado un poco tu reputación en el imperio." }
    { group:53, id:39, text: "Tu salario es demasiado alto para tu puesto actual. La consideración en el imperio aumentará si lo reduces un poco." }
    { group:53, id:40, text: "No has podido pagar el tributo, lo que ha reducido la puntuación de imperio. Guarda algo de dinero en el tesoro para poder hacer tu pago anual." }
    { group:53, id:41, text: "Tu salario es demasiado alto para tu puesto actual. Sería mejor que lo redujeras un poco." }
    { group:53, id:42, text: "Tu lento progreso hacia la consecución puntual de los objetivos ha reducido tu puntuación de imperio." }
    { group:53, id:43, text: "Tu descaro, al cobrar un salario superior al de tu rango, hace que desaprueben tu actuación." }
    { group:53, id:44, text: "Tu puntuación de imperio ha aumentado desde el año pasado." }
    { group:53, id:45, text: "Tu puntuación de imperio no ha cambiado desde el año pasado." }
    { group:53, id:46, text: "La puntuación de paz aumentará por cada año en que no se produzcan motines o invasiones que dañen la propiedad pública." }
    { group:53, id:47, text: "Esta provincia ha estado en paz durante un breve período de tiempo, pero los ciudadanos no se sienten todavía muy a salvo." }
    { group:53, id:48, text: "Esta provincia se siente relativamente en paz. Esta sensación mejorará con el tiempo." }
    { group:53, id:49, text: "Esta es una provincia respetuosa de la ley y con el tiempo podría llegar a ser muy pacífica." }
    { group:53, id:50, text: "Esta provincia se ha convertido en un lugar tranquilo con pocas amenazas reales, justo como les gusta a sus habitantes." }
    { group:53, id:51, text: "La fama de tranquilidad y seguridad de esta provincia es legendaria. Es probable que otros gobernadores piensen jubilarse aquí." }
    { group:53, id:52, text: "Los recientes motines de la ciudad han tenido un pésimo efecto en su puntuación general de paz." }
    { group:53, id:53, text: "La existencia de tropas enemigas en las cercanías de la ciudad afecta a su puntuación de paz." }
    { group:53, id:54, text: "Los cercanos batallones del faraón asustan a tu gente y esto irá en detrimento de la puntuación de paz." }
    { group:53, id:55, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:56, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:57, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:58, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:59, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:60, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:61, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:62, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:63, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:64, text: "El supervisor de monumentos y el capataz de construcción (haz clic derecho en un monumento) pueden aconsejarte." }
    { group:53, id:65, text: "Esta ciudad es la más culta de todo Egipto." }
    { group:53, id:66, text: "La increíble prosperidad de esta ciudad es la comidilla de todo Egipto." }
    { group:53, id:67, text: "Esta ciudad tiene los monumentos más magníficos de todo Egipto." }
    { group:53, id:68, text: "Tu imperio tiene el mejor coeficiente de puntuación de todo Egipto." }
    { group:54, id:0, text: "Supervisor comercial" }
    { group:54, id:1, text: "pulsa un artículo para comerciar, reservar o cambiar el estado" }
    { group:54, id:2, text: "Mostrar precios" }
    { group:54, id:3, text: "Reservar" }
    { group:54, id:4, text: "Sin comerciar" }
    { group:54, id:5, text: "Importar hasta" }
    { group:54, id:6, text: "Exportar más de" }
    { group:54, id:7, text: "No hay industrias en la ciudad" }
    { group:54, id:8, text: "industria activa en la ciudad" }
    { group:54, id:9, text: "industrias activas en la ciudad" }
    { group:54, id:10, text: "industria paralizada en la ciudad" }
    { group:54, id:11, text: "industrias paralizadas en la ciudad" }
    { group:54, id:12, text: "Funcionando" }
    { group:54, id:13, text: "industrias desocupadas en la ciudad" }
    { group:54, id:14, text: "industria desocupada en la ciudad" }
    { group:54, id:15, text: "guardado en los almacenes de la ciudad" }
    { group:54, id:16, text: "La industria está ACTIVADA" }
    { group:54, id:17, text: "La industria está DESACTIVADA" }
    { group:54, id:18, text: "Sin comerciar" }
    { group:54, id:19, text: "Importar hasta" }
    { group:54, id:20, text: "Exportar superados" }
    { group:54, id:21, text: "Precios en todo Egipto" }
    { group:54, id:22, text: "Los compradores pagan" }
    { group:54, id:23, text: "Los vendedores reciben" }
    { group:54, id:24, text: "No hay rutas comerciales abiertas para estos bienes." }
    { group:54, id:25, text: "Estos bienes sólo están disponibles mediante importación." }
    { group:54, id:26, text: "Reservar recurso" }
    { group:54, id:27, text: "Haz clic aquí para desactivar la reserva" }
    { group:54, id:28, text: "Comerciar y utilizar este recurso" }
    { group:54, id:29, text: "Haz clic aquí para reservarlo" }
    { group:54, id:30, text: "Ir al mapa del mundo" }
    { group:54, id:31, text: "Disponible para importar" }
    { group:54, id:32, text: "Disponible para exportar" }
    { group:54, id:33, text: "Disponible para importar o exportar" }
    { group:54, id:34, text: "Abrir ruta comercial para importar" }
    { group:54, id:35, text: "Abrir ruta comercial para exportar" }
    { group:54, id:36, text: "Abrir ruta para importar/exportar" }
    { group:54, id:37, text: "Importar si es necesario" }
    { group:54, id:38, text: "Exportar tan sólo los excedentes" }
    { group:54, id:39, text: "Haz clic para importar" }
    { group:54, id:40, text: "Haz clic para exportar" }
    { group:54, id:41, text: "No hay vendedores de este recurso" }
    { group:54, id:42, text: "No hay compradores para este recurso" }
    { group:54, id:43, text: "Importar cuando sea necesario" }
    { group:54, id:44, text: "Exportar los excedentes" }
    { group:54, id:45, text: "múltiple" }
    { group:54, id:46, text: "Ver estado del comercio" }
    { group:54, id:47, text: "por arma" }
    { group:54, id:48, text: "por carro" }
    { group:54, id:49, text: "por bloque" }
    { group:54, id:50, text: "por 100 piezas" }
    { group:55, id:0, text: "Población - Historia" }
    { group:55, id:1, text: "Población - Censo" }
    { group:55, id:2, text: "Población - Sociedad" }
    { group:55, id:3, text: "Historia" }
    { group:55, id:4, text: "Censo" }
    { group:55, id:5, text: "Sociedad" }
    { group:55, id:6, text: "Población de la ciudad en el tiempo." }
    { group:55, id:7, text: "Composición de la población por edades (en años)." }
    { group:55, id:8, text: "Composición de la población por ingresos." }
    { group:55, id:9, text: "Habitantes de cabañas" }
    { group:55, id:10, text: "Habitantes de haciendas" }
    { group:55, id:11, text: "La capital proporciona todos los alimentos de esta ciudad" }
    { group:55, id:12, text: "- alimentos para" }
    { group:55, id:13, text: "- algunos alimentos para el próximo mes" }
    { group:55, id:14, text: "- ningún alimento para el próximo mes" }
    { group:55, id:15, text: "- muy poco alimento para el próximo mes" }
    { group:55, id:16, text: "Las viviendas actuales pueden alojar a" }
    { group:55, id:17, text: "personas más" }
    { group:55, id:18, text: "nuevos habitantes han llegado este mes." }
    { group:55, id:19, text: "nuevo habitante ha llegado este mes." }
    { group:55, id:20, text: "La falta de viviendas vacías está limitando la inmigración." }
    { group:55, id:21, text: "Los bajos salarios reducen la inmigración a tu ciudad." }
    { group:55, id:22, text: "El desempleo está reduciendo el número de inmigrantes." }
    { group:55, id:23, text: "La falta de alimentos en los graneros frena la inmigración." }
    { group:55, id:24, text: "Los altos impuestos impiden que la gente emigre a tu ciudad." }
    { group:55, id:25, text: "En general, la gente viene a la ciudad, o desea venir." }
    { group:55, id:26, text: "En general, la gente está abandonando la ciudad." }
    { group:55, id:27, text: "La falta de trabajo está alejando a la gente." }
    { group:55, id:28, text: "La gente se va a otros sitios en búsqueda de mejores salarios." }
    { group:55, id:29, text: "La gente está abandonando la ciudad debido a los elevados impuestos." }
    { group:55, id:30, text: "En general, la población de la ciudad permanece estática." }
    { group:55, id:31, text: "Hay un equilibrio entre la gente que viene y que se va de la ciudad." }
    { group:55, id:32, text: "La ciudad es rica, pero el mal alojamiento frena la inmigración." }
    { group:55, id:33, text: "Nadie quiere vivir en la ciudad." }
    { group:55, id:34, text: "Producimos o importamos suficientes alimentos para" }
    { group:55, id:35, text: "personas." }
    { group:55, id:36, text: "Consumimos más que producimos." }
    { group:55, id:37, text: "Consumimos más de lo que producimos, pero la ciudad puede crecer." }
    { group:55, id:38, text: "Consumimos más de lo que producimos; la población podría aumentar" }
    { group:55, id:39, text: "Ahora consumimos más de lo que producimos." }
    { group:55, id:40, text: "Consumimos más que producimos y es posible que la ciudad merme." }
    { group:55, id:41, text: "Consumimos más de lo que producimos; la población podría aumentar" }
    { group:55, id:42, text: "Ahora consumimos un poco más de lo que producimos." }
    { group:55, id:43, text: "Consumimos algo más de lo que producimos; la ciudad puede mermar." }
    { group:55, id:44, text: "Consumimos más de lo que producimos, pero la ciudad puede crecer." }
    { group:55, id:45, text: "Ahora producimos lo necesario para alimentar a todo el mundo." }
    { group:55, id:46, text: "Producimos más de lo que consumimos, pero la ciudad puede mermar." }
    { group:55, id:47, text: "Producimos más que consumimos y es probable que la ciudad crezca." }
    { group:55, id:48, text: "Ahora producimos un poco más de lo que consumimos." }
    { group:55, id:49, text: "Hay excedentes de producción, pero la ciudad puede mermar." }
    { group:55, id:50, text: "Hay excedentes de producción y la población puede aumentar." }
    { group:55, id:51, text: "Ahora producimos mucho más de lo que consumimos." }
    { group:55, id:52, text: "Producimos más de lo que comemos pero es posible que la ciudad merme." }
    { group:55, id:53, text: "Producimos más que consumimos y la población debería aumentar." }
    { group:56, id:0, text: "Supervisor de salud pública" }
    { group:56, id:1, text: "Gratis" }
    { group:56, id:2, text: "Ninguna" }
    { group:56, id:3, text: "Funcionando" }
    { group:56, id:4, text: "Cuidados para" }
    { group:56, id:5, text: "Cobertura en la ciudad" }
    { group:56, id:6, text: "pacientes" }
    { group:56, id:7, text: "Algunas zonas de la ciudad necesitan accesos a médicos." }
    { group:56, id:8, text: "Algunas zonas de la ciudad requieren más médicos." }
    { group:56, id:9, text: "Algunas zonas prósperas de la ciudad requieren dentistas. Un dentista local aumentará la categoría del vecindario." }
    { group:56, id:10, text: "Muchas zonas de la ciudad necesitan dentistas. Como tu ciudad aumenta su riqueza, cada vez más habitantes se pueden permitir dientes de marfil." }
    { group:56, id:11, text: "Algunas zonas de la ciudad piden acceso a una botica." }
    { group:56, id:12, text: "Cada vez más gente quiere instalaciones médicas (boticas) accesibles." }
    { group:56, id:13, text: "Los pocos mortuorios de la ciudad están frenando el desarrollo de algunas zonas de la ciudad." }
    { group:56, id:14, text: "Los ciudadanos necesitan más mortuorios para preparar adecuadamente a sus muertos para el otro mundo." }
    { group:56, id:15, text: "Actualmente, no hay solicitudes de instalaciones sanitarias. Aunque, según crezca la ciudad, la gente esperará tener acceso a cuidados sanitarios, dentistas e incluso más instalaciones médicas." }
    { group:56, id:16, text: "Tu pequeño asentamiento todavía no ha informado de problemas de salud." }
    { group:56, id:17, text: "¡La sanidad pública es malísima! La peste está asegurada en estas condiciones." }
    { group:56, id:18, text: "La sanidad pública es terrible. Las enfermedades son casi inevitables." }
    { group:56, id:19, text: "La sanidad pública es mala. Más trabajadores sanitarios podrían mejorar la situación." }
    { group:56, id:20, text: "La sanidad pública es deficiente. Las instalaciones con alimentos y medicinas la mejorarían." }
    { group:56, id:21, text: "La sanidad pública está por debajo de la media. Asegúrate de que los ciudadanos tienen alimentos y acceso a la sanidad." }
    { group:56, id:22, text: "La sanidad pública es normal. Las enfermedades están bajo control y la gente tiene suficientes alimentos." }
    { group:56, id:23, text: "La sanidad pública es buena. Los ciudadanos únicamente son propensos a pequeñas dolencias." }
    { group:56, id:24, text: "La sanidad pública es buena. Los asistentes locales no están muy saturados." }
    { group:56, id:25, text: "La sanidad pública es excelente y no hay esperas para visitar las instalaciones sanitarias locales." }
    { group:56, id:26, text: "La sanidad pública es casi perfecta y las instalaciones sanitarias están prácticamente vacías." }
    { group:56, id:27, text: "La sanidad pública es perfecta. Los trabajadores de la sanidad pasan la mayor parte del tiempo jugando al senet." }
    { group:56, id:28, text: "La sanidad pública es malísima." }
    { group:56, id:29, text: "La sanidad pública es muy mala." }
    { group:56, id:30, text: "La sanidad pública es mala." }
    { group:56, id:31, text: "La sanidad pública es deficiente." }
    { group:56, id:32, text: "La sanidad pública está por debajo de la media." }
    { group:56, id:33, text: "La sanidad pública es regular." }
    { group:56, id:34, text: "La sanidad pública es buena." }
    { group:56, id:35, text: "La sanidad pública es muy buena." }
    { group:56, id:36, text: "La sanidad pública es excelente." }
    { group:56, id:37, text: "La sanidad pública es casi perfecta." }
    { group:56, id:38, text: "La sanidad pública es perfecta." }
    { group:56, id:39, text: "Médicos" }
    { group:56, id:40, text: "Dentistas" }
    { group:56, id:41, text: "Boticas" }
    { group:56, id:42, text: "Mortuorios" }
    { group:56, id:43, text: "Escasa" }
    { group:56, id:44, text: "Muy pobre" }
    { group:56, id:45, text: "Pobre" }
    { group:56, id:46, text: "Inf. a la media" }
    { group:56, id:47, text: "Mediano" }
    { group:56, id:48, text: "Mediano" }
    { group:56, id:49, text: "Supera la media" }
    { group:56, id:50, text: "Buena" }
    { group:56, id:51, text: "Muy buena" }
    { group:56, id:52, text: "Excelente" }
    { group:56, id:53, text: "Perfecta" }
    { group:56, id:54, text: "0 -" }
    { group:56, id:55, text: "Unos pocos" }
    { group:56, id:56, text: "Algunos" }
    { group:56, id:57, text: "Varios" }
    { group:56, id:58, text: "Muchos" }
    { group:56, id:59, text: "Boticas trabajan actualmente para proteger a la ciudad de la malaria." }
    { group:56, id:60, text: "nuevos brotes se han descubierto este mes." }
    { group:56, id:61, text: "variedad de alimentos de tu ciudad." }
    { group:57, id:0, text: "Supervisor de educación" }
    { group:57, id:1, text: "Funcionando" }
    { group:57, id:2, text: "Se puede educar a" }
    { group:57, id:3, text: "Cobertura en la ciudad" }
    { group:57, id:4, text: "Niños" }
    { group:57, id:5, text: "Jóvenes" }
    { group:57, id:6, text: "Personas" }
    { group:57, id:7, text: "Ninguna" }
    { group:57, id:8, text: "Escasa" }
    { group:57, id:9, text: "Muy pobre" }
    { group:57, id:10, text: "Pobre" }
    { group:57, id:11, text: "Inf. a la media" }
    { group:57, id:12, text: "Mediano" }
    { group:57, id:13, text: "Mediano" }
    { group:57, id:14, text: "Sup. a la media" }
    { group:57, id:15, text: "Buena" }
    { group:57, id:16, text: "Muy buena" }
    { group:57, id:17, text: "Excelente" }
    { group:57, id:18, text: "Perfecta" }
    { group:57, id:19, text: "Algunas zonas de la ciudad necesitan acceso a escuelas de escribas. La falta de acceso a la educación impide que en algunas partes de la ciudad se construyan mejores viviendas." }
    { group:57, id:20, text: "Algunos barrios piden un mejor acceso a las escuelas de escribas. Algunas casas tienen acceso a las escuelas públicas, pero otras no, y esto impide su desarrollo." }
    { group:57, id:21, text: "Ahora se necesita acceso a la biblioteca en algunas zonas de la ciudad. Los ciudadanos necesitan acceder a la literatura si quieren trabajar de escribas." }
    { group:57, id:22, text: "Algunas zonas de la ciudad solicitan mejor acceso a las bibliotecas. A los escribas de clase alta no les gusta tener que caminar mucho hasta la biblioteca." }
    { group:57, id:23, text: "Un mejor acceso a la escuela de escribas y la biblioteca realzaría algunas zonas de la ciudad. La gente no tendría que desplazarse tan lejos para aprender." }
    { group:57, id:24, text: "Los ciudadanos aún no piden instalaciones educativas, aunque a medida que aumente la categoría de la ciudad, la gente pedirá escuelas de escribas y bibliotecas." }
    { group:57, id:25, text: "Todos los que solicitan instalaciones educativas gozan de éstas, que además son perfectas en toda la ciudad." }
    { group:57, id:26, text: "Todos los barrios que solicitan instalaciones educativas las consiguen, pero si se construyeran más escuelas de escribas se reduciría la masificación de las aulas." }
    { group:57, id:27, text: "Todos los vecindarios que las solicitan gozan de  instalaciones educativas, pero si se construyesen más bibliotecas se reduciría la masificación de estos centros." }
    { group:57, id:28, text: "Escuelas de escribas" }
    { group:57, id:29, text: "Biblioteca" }
    { group:58, id:0, text: "Supervisor de entretenimiento" }
    { group:58, id:1, text: "Funcionando" }
    { group:58, id:2, text: "Espectáculos" }
    { group:58, id:3, text: "Entretiene a" }
    { group:58, id:4, text: "Cobertura en la ciudad" }
    { group:58, id:5, text: "Personas" }
    { group:58, id:6, text: "N/A" }
    { group:58, id:7, text: "Por el momento tus ciudadanos tienen en mente necesidades más básicas que el entretenimiento. Pero cuando la ciudad crezca, solicitarán algo que los libere de la rutina diaria." }
    { group:58, id:8, text: "Los ciudadanos que buscan diversión ven cumplidos sus deseos. Pero cuando la ciudad crezca habrá que ofrecer formas más espectaculares de entretenimiento y en mayor cantidad." }
    { group:58, id:9, text: "Algunos ciudadanos se quejan del escaso acceso a las instalaciones recreativas. Ciertas  zonas de la ciudad necesitan más variedad de  instalaciones recreativas que faciliten su posterior desarrollo." }
    { group:58, id:10, text: "Algunas zonas de la ciudad se quejan de la falta de acceso a instalaciones recreativas. Estas zonas pobres crecerían con más instalaciones." }
    { group:58, id:11, text: "Algunos ciudadanos se quejan de la escasez de actividades de ocio que hay en sus zonas. Necesitarás ofrecer más variedad o quizás construir más escuelas de artistas para surtir a los lugares que los necesitan." }
    { group:58, id:12, text: "En algunos lugares faltan músicos o malabaristas, por lo que no están funcionando a plena capacidad. Más comediantes ayudarán a levantar algunas zonas de la ciudad que se quejan de la falta de actividades de ocio." }
    { group:58, id:13, text: "Necesitas más espectáculos. Si facilitas más bailarines aumentarás los niveles de entretenimiento en algunas zonas de la ciudad." }
    { group:58, id:14, text: "Mientras el local de Senet tenga empleados y cerveza, el maestro de senet recorrerá el vecindario para recordar a la gente que hay partidas en juego." }
    { group:58, id:15, text: "desde el último festival" }
    { group:58, id:16, text: "Celebrar nuevo festival." }
    { group:58, id:17, text: "Festivales" }
    { group:58, id:18, text: "Los más juerguistas aún están durmiendo la mona del último festival." }
    { group:58, id:19, text: "La gente aún sonríe cuando recuerda tu último festival." }
    { group:58, id:20, text: "El recuerdo del último festival se desvanece de las mentes del pueblo." }
    { group:58, id:21, text: "La gente no recuerda el último festival celebrado en la ciudad." }
    { group:58, id:22, text: "Los ciudadanos se quejan ante la falta de festivales en la ciudad." }
    { group:58, id:23, text: "Tu pueblo no puede aguantar la perspectiva de otro año sin festival." }
    { group:58, id:24, text: "\"¡Necesitamos un día de fiesta!\", grita la gente en las calles." }
    { group:58, id:25, text: "Celebrar festival de Osiris" }
    { group:58, id:26, text: "Celebrar festival de Ra" }
    { group:58, id:27, text: "Celebrar festival de Ptah" }
    { group:58, id:28, text: "Celebrar festival de Seth" }
    { group:58, id:29, text: "Celebrar festival de Bastet" }
    { group:58, id:30, text: "costes" }
    { group:58, id:31, text: "Festival normal" }
    { group:58, id:32, text: "Festival lujoso" }
    { group:58, id:33, text: "Super-festival" }
    { group:58, id:34, text: "Preparar festival para" }
    { group:58, id:35, text: "Ninguna" }
    { group:58, id:36, text: "Escasa" }
    { group:58, id:37, text: "Muy pobre" }
    { group:58, id:38, text: "Pobre" }
    { group:58, id:39, text: "Inf. a la media" }
    { group:58, id:40, text: "Mediano" }
    { group:58, id:41, text: "Mediano" }
    { group:58, id:42, text: "Sup. a la media" }
    { group:58, id:43, text: "Buena" }
    { group:58, id:44, text: "Muy buena" }
    { group:58, id:45, text: "Excelente" }
    { group:58, id:46, text: "Perfecta" }
    { group:58, id:47, text: "Escenario malabares" }
    { group:58, id:48, text: "Escenario de música" }
    { group:58, id:49, text: "Escenario de danza" }
    { group:58, id:50, text: "Locales de senet" }
    { group:58, id:51, text: "-" }
    { group:58, id:52, text: "Encargar un festival" }
    { group:58, id:53, text: "Encargo de festival para" }
    { group:58, id:54, text: "próximo mes" }
    { group:58, id:55, text: "Escenarios" }
    { group:58, id:56, text: "Zoológicos" }
    { group:59, id:0, text: "Supervisor de los templos" }
    { group:59, id:1, text: "Templos" }
    { group:59, id:2, text: "Complejos" }
    { group:59, id:3, text: "Aplacamiento" }
    { group:59, id:4, text: "N/A" }
    { group:59, id:5, text: "Templo" }
    { group:59, id:6, text: "Meses" }
    { group:59, id:7, text: "Festival" }
    { group:59, id:8, text: "desde el" }
    { group:59, id:9, text: "Los ciudadanos muestran interés por la religión. La falta de acceso a un lugar de culto cercano está mermando el desarrollo de la ciudad." }
    { group:59, id:10, text: "Cada vez más ciudadanos demandan un lugar de culto en sus barrios para mejorar la visión de los dioses respecto a ellos." }
    { group:59, id:11, text: "Algunos ciudadanos quieren acceder a otras religiones cerca de sus hogares. La falta de diversidad religiosa limita el desarrollo urbano en determinadas zonas de la ciudad." }
    { group:59, id:12, text: "Algunos ciudadanos quieren que se establezca una tercera religión cerca de su casa. Creen que ayudaría a atraer a escribas mejores." }
    { group:59, id:13, text: "Por el momento los ciudadanos se preocupan de otros aspectos de la vida urbana, pero con el crecimiento de la ciudad querrán tener fácil acceso a distintos templos." }
    { group:59, id:14, text: "La religión florece en la ciudad. Las necesidades religiosas están cubiertas y los dioses están satisfechos." }
    { group:59, id:15, text: "El descontento de Osiris es peligroso. Puede destruir tus cosechas y vaciar tus graneros, o incluso evitar la riada." }
    { group:59, id:16, text: "Si aumenta el descontento de Ra, padre de los faraones, puede hacer que las ciudades vecinas compartan sus sentimientos. La armonía del imperio peligra cuando Ra se enfada." }
    { group:59, id:17, text: "Ptah, cuyo favor necesitan tus fabricantes, se está enfadando. Recupera su favor o prepara a tus trabajadores para perder todas las industrias y productos." }
    { group:59, id:18, text: "Los soldados más valientes tiemblan ante la ira de Seth. Recupera rápidamente la buena opinión de este dios sobre tu ciudad o tus batallones desaparecerán." }
    { group:59, id:19, text: "Cuando Bastet se enoja, la gente no está nunca a salvo. Aplaca a esta diosa enseguida o la ciudad sufrirá pestes y plagas." }
    { group:59, id:20, text: "Enfurecido" }
    { group:59, id:21, text: "Furioso" }
    { group:59, id:22, text: "Enfadado" }
    { group:59, id:23, text: "Resentido" }
    { group:59, id:24, text: "Desencantado" }
    { group:59, id:25, text: "Apático" }
    { group:59, id:26, text: "Amable" }
    { group:59, id:27, text: "Simpático" }
    { group:59, id:28, text: "Compasivo" }
    { group:59, id:29, text: "Aprobatorio" }
    { group:59, id:30, text: "Benevolente" }
    { group:59, id:31, text: "Has desactivado los efectos de los dioses. Aunque estén enfadados o contentos, no darán señales de ello." }
    { group:59, id:32, text: "Osiris, dios de la riada del Nilo y del reino de los muertos, bendecirá tu ciudad con una gran riada anual que fertilizará las tierras. También puede mejorar las cosechas de otras muchas formas. Un altar a Sebek, diosa de la fertilidad, permite a los sacerdotes de Osiris ayudar a los ciudadanos a aumentar los alimentos y suministros. Un oráculo de Min, dios de la regeneración, ayuda a que la vida salvaje se reproduzca por la ciudad y sus alrededores y que los animales y los peces sean más fuertes, e incluso acelera el crecimiento de las plantas." }
    { group:59, id:33, text: "Ra, dios del imperio, facilita el comercio y los viajes por todo el mundo conocido, e incluso puede ayudar a mejorar tu reputación por todo Egipto. Un altar a Maat, diosa de la justicia, ayuda a prevenir la delincuencia en la ciudad, mientras que un oráculo de Horus, dios del faraón, hace que tus trabajadores estén más deseosos de realizar las tareas cotidianas. En nombre del faraón, se sentirán inspirados a trabajar por el bien de Egipto." }
    { group:59, id:34, text: "Ptah es el dios protector de los artesanos y los ayuda a terminar sus tareas más deprisa. Un altar a Amón, dios del Sol, mejora la capacidad de la ciudad a la hora de construir monumentos, mientras que un oráculo de Thot, dios de la sabiduría y el conocimiento, puede facilitar el acceso de los ciudadanos a la educación." }
    { group:59, id:35, text: "Cuando Seth está contento, tus enemigos son sus enemigos. Puede conseguir que los soldados más inexpertos luchen como veteranos e incluso puede abatir a tus enemigos con su propia mano. Es tan poderoso que su influencia puede llegar a las batallas más lejanas. Por supuesto, si no se aplaca su ira, la ciudad sentirá toda la fuerza de sus destructivos poderes." }
    { group:59, id:36, text: "Bastet, diosa del hogar, puede mejorar la calidad de vida de la ciudad y permitir a los ciudadanos disfrutar de un nivel de vida más alto. Su poder es tan grande que incluso puede mantener satisfechos a los otros dioses. Por supuesto, si no está satisfecha, tu ciudad conocerá la miseria y el sufrimiento. Un altar a Isis, diosa de la curación, puede hacer que tus ciudadanos gocen de buena salud e incluso auxiliarlos si enferman. Un oráculo de Hator, diosa de la alegría, el amor y la fiesta, puede conseguir que los ciudadanos estén contentos, a pesar de sus problemas." }
    { group:59, id:37, text: "-" }
    { group:59, id:38, text: "Sacerdotisa" }
    { group:60, id:0, text: "Supervisor del tesoro" }
    { group:60, id:1, text: "Impuestos:" }
    { group:60, id:2, text: "El tesoro de la ciudad tiene un activo de" }
    { group:60, id:3, text: "La ciudad tiene una deuda de" }
    { group:60, id:4, text: "genera aproximadamente" }
    { group:60, id:5, text: "de contribuyentes" }
    { group:60, id:6, text: "El año pasado" }
    { group:60, id:7, text: "Hasta ahora, en este año" }
    { group:60, id:8, text: "Impuestos" }
    { group:60, id:9, text: "Ganancias de exportación" }
    { group:60, id:10, text: "Beneficio" }
    { group:60, id:11, text: "Gastos de importación" }
    { group:60, id:12, text: "Salarios" }
    { group:60, id:13, text: "Construcción" }
    { group:60, id:14, text: "Interés en" }
    { group:60, id:15, text: "Salario personal" }
    { group:60, id:16, text: "Robo" }
    { group:60, id:17, text: "Gastos" }
    { group:60, id:18, text: "Flujo neto int./ext." }
    { group:60, id:19, text: "Balance" }
    { group:60, id:20, text: "Regalos" }
    { group:60, id:21, text: "Tributos" }
    { group:60, id:22, text: "Solicitudes y festivales" }
    { group:60, id:23, text: "no cobrados este año" }
    { group:60, id:24, text: "Oro extraído" }
    { group:61, id:0, text: "Supervisor jefe" }
    { group:61, id:1, text: "Opinión" }
    { group:61, id:2, text: "Migración" }
    { group:61, id:3, text: "Trabajo" }
    { group:61, id:4, text: "Comida" }
    { group:61, id:5, text: "Alimentación" }
    { group:61, id:6, text: "Sanidad" }
    { group:61, id:7, text: "Religión" }
    { group:61, id:8, text: "Economía" }
    { group:61, id:9, text: "Crimen" }
    { group:61, id:10, text: "Ejército" }
    { group:61, id:11, text: "Imperio" }
    { group:61, id:12, text: "Nilómetro" }
    { group:61, id:13, text: "Producimos mucho más de lo que comemos" }
    { group:61, id:14, text: "Producimos un poco más de lo que comemos" }
    { group:61, id:15, text: "Producimos lo justo para alimentar a todos" }
    { group:61, id:16, text: "IMPORTANTE: Consumimos algo más que producimos" }
    { group:61, id:17, text: "GRAVE: Consumimos más de lo que producimos" }
    { group:61, id:18, text: "URGENTE: Consumimos mucho más que producimos" }
    { group:61, id:19, text: "Sin usar" }
    { group:61, id:20, text: "Todo el mundo te aborrece" }
    { group:61, id:21, text: "La gente está muy enfadada:" }
    { group:61, id:22, text: "La gente está enfadada:" }
    { group:61, id:23, text: "La gente está muy disgustada:" }
    { group:61, id:24, text: "La gente está disgustada:" }
    { group:61, id:25, text: "La gente está enojada:" }
    { group:61, id:26, text: "Le eres indiferente a la gente:" }
    { group:61, id:27, text: "La gente está contenta contigo" }
    { group:61, id:28, text: "La gente está muy contenta contigo" }
    { group:61, id:29, text: "La gente está excepcionalmente contenta contigo" }
    { group:61, id:30, text: "La gente te quiere" }
    { group:61, id:31, text: "La gente te idolatra como a un dios" }
    { group:61, id:32, text: "no hay suficiente comida." }
    { group:61, id:33, text: "no hay suficiente trabajo." }
    { group:61, id:34, text: "los impuestos son muy altos." }
    { group:61, id:35, text: "los salarios son bajos." }
    { group:61, id:36, text: "hay demasiadas áreas pobre" }
    { group:61, id:37, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Tus ciudadanos no están nada contentos por la falta de alimentos, pero los elevados impuestos, los bajos salarios, las desigualdades sociales y la falta de trabajo también pueden estar contribuyendo a esta situación." }
    { group:61, id:38, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Tus ciudadanos están muy disgustados por la falta de trabajo pero los elevados impuestos, los bajos salarios, las desigualdades sociales y la falta de alimentos también pueden estar contribuyendo a esta situación." }
    { group:61, id:39, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Los elevados impuestos están molestando en gran manera a tus ciudadanos, pero los bajos salarios, las desigualdades sociales y la falta de alimentos y empleos también pueden estar contribuyendo a esta situación." }
    { group:61, id:40, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Los ciudadanos están muy disgustados a causa de lo poco que cobran, los elevados impuestos, las desigualdades sociales y la falta de alimentos y empleos también pueden estar contribuyendo a esta situación." }
    { group:61, id:41, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Los ciudadanos están muy disgustados a causa de la profunda desigualdad social, pero los elevados impuestos, los bajos salarios y la falta de alimentos y empleos también pueden estar contribuyendo a esta situación." }
    { group:61, id:42, text: "La baja percepción ciudadana contribuye a aumentar la delincuencia, impide que la gente venga a la ciudad e incluso puede animar a los habitantes a recoger sus cosas y abandonar la ciudad. Los bajos salarios, los elevados impuestos, la desigualdad social y la falta de alimentos y empleos contribuyen a esta situación." }
    { group:61, id:43, text: "La guerra está disuadiendo a los inmigrantes." }
    { group:61, id:44, text: "La gente está inmigrando a la ciudad" }
    { group:61, id:45, text: "La falta de vivienda impide la inmigración" }
    { group:61, id:46, text: "Los bajos salarios frenan la inmigración" }
    { group:61, id:47, text: "La falta de empleo impide la inmigración" }
    { group:61, id:48, text: "La falta de alimentos frena la inmigración" }
    { group:61, id:49, text: "Los elevados impuestos frenan la inmigración" }
    { group:61, id:50, text: "Los barrios bajos frenan la inmigración." }
    { group:61, id:51, text: "La baja moral ciudadana evita la inmigración" }
    { group:61, id:52, text: "La gente deja la ciudad por falta de viviendas." }
    { group:61, id:53, text: "La gente deja la ciudad por los bajos salarios." }
    { group:61, id:54, text: "La gente deja la ciudad por la falta de empleo." }
    { group:61, id:55, text: "La gente deja la ciudad por la falta de alimento" }
    { group:61, id:56, text: "La gente deja la ciudad por los impuestos injustos y elevados." }
    { group:61, id:57, text: "Los barrios bajos ahuyentan a la población." }
    { group:61, id:58, text: "La gente deja la ciudad a causa de la baja moral ciudadana." }
    { group:61, id:59, text: "Se esperan pocos cambios" }
    { group:61, id:60, text: "La gente vendrá a instalarse en la ciudad mientras queden viviendas libres y los habitantes están contentos contigo. Necesitas construir más viviendas para que la ciudad crezca y prospere." }
    { group:61, id:61, text: "La gente vendrá a instalarse en la ciudad mientras los habitantes están contentos contigo y haya suficientes viviendas disponibles. Necesitas subir los salarios para atraer a la gente a tu ciudad." }
    { group:61, id:62, text: "La gente vendrá a instalarse en la ciudad mientras los habitantes están contentos contigo y haya suficientes viviendas disponibles. Necesitas crear más empleos, mediante la creación de más industrias, para atraer a la gente a la ciudad." }
    { group:61, id:63, text: "La gente vendrá a instalarse en la ciudad mientras los habitantes estén contentos contigo y haya suficientes viviendas disponibles. Necesitas producir más alimentos de los que hay en la actualidad para atraer a la gente a tu ciudad." }
    { group:61, id:64, text: "La gente vendrá a instalarse en la ciudad mientras los habitantes están contentos contigo y haya suficientes viviendas disponibles. Necesitas bajar los impuestos para atraer a la gente a tu ciudad." }
    { group:61, id:65, text: "Normalmente, es deseable aumentar la población para que la ciudad pueda crecer y prosperar. Las viviendas libres y una mayor percepción ciudadana atraen a los emigrantes." }
    { group:61, id:66, text: "Normalmente, es deseable aumentar la población para que la ciudad pueda crecer y prosperar. La gente está llegando en tropel a la ciudad, gracias a la existencia de viviendas desocupadas y a que los habitantes se sienten satisfechos." }
    { group:61, id:67, text: "Si existe una gran diferencia entre los ricos y los pobres, nadie querrá venir a tu ciudad. Proporciona mejores servicios a los barrios más pobres, para equilibrar un poco la desigualdad social." }
    { group:61, id:68, text: "La gente vendrá a instalarse en la ciudad mientras los habitantes estén contentos contigo y haya suficientes viviendas disponibles. Necesitas aumentar la percepción ciudadana para atraer la gente a la ciudad." }
    { group:61, id:69, text: "La gente vendrá a instalarse en la ciudad mientras haya suficientes viviendas disponibles y los habitantes estén contentos. Construye más viviendas para que la ciudad crezca y prospere." }
    { group:61, id:70, text: "Los ciudadanos permanecerán en la ciudad mientras estén contentos y haya suficientes viviendas. Sube los salarios si quieres que la gente se quede." }
    { group:61, id:71, text: "Los ciudadanos permanecerán en la ciudad mientras estén contentos y haya suficientes viviendas. Crea más empleos, mediante la construcción de más industrias si quieres que la gente se quede." }
    { group:61, id:72, text: "Los ciudadanos permanecerán en la ciudad mientras estén contentos y haya suficientes viviendas. Dado el tamaño de la población, necesitas producir más alimentos de los que hay en la actualidad, si quieres que la gente se quede." }
    { group:61, id:73, text: "Los ciudadanos permanecerán en la ciudad mientras estén contentos y haya suficientes viviendas. Unos impuestos más bajos ayudarán a que la gente se quede." }
    { group:61, id:74, text: "Si existe una gran diferencia entre los ricos y los pobres, la gente tenderá a buscar nuevas oportunidades en otros lugares. Proporciona mejores servicios a los barrios más pobres, para equilibrar un poco la desigualdad social." }
    { group:61, id:75, text: "La gente vendrá a instalarse en la ciudad mientras haya suficientes viviendas disponibles y los habitantes estén contentos; de paso, los habitantes actuales no emigrarán a pastos más verdes. Necesitas aumentar la percepción ciudadana si quieres que la gente se quede." }
    { group:61, id:76, text: "URGENTE: La ciudad tiene un desempleo de" }
    { group:61, id:77, text: "GRAVE: La ciudad tiene un desempleo de" }
    { group:61, id:78, text: "IMPORTANTE: La ciudad tiene un desempleo del" }
    { group:61, id:79, text: "La ciudad tiene un desempleo de" }
    { group:61, id:80, text: "URGENTE: La ciudad está escasa de" }
    { group:61, id:81, text: "GRAVE: La ciudad está escasa de" }
    { group:61, id:82, text: "IMPORTANTE: La ciudad necesite" }
    { group:61, id:83, text: "La ciudad está escasa de" }
    { group:61, id:84, text: "La ciudad no tiene problemas de empleo" }
    { group:61, id:85, text: "La alta tasa de desempleo alentará a los ciudadanos a buscar trabajo en otros lugares. Construye más industrias para crear algunos empleos." }
    { group:61, id:86, text: "La alta tasa de desempleo puede alentar a los ciudadanos a buscar trabajo en otros lugares. Puedes crear más empleos mediante la creación de industrias." }
    { group:61, id:87, text: "La alta tasa de desempleo puede alentar a los ciudadanos a buscar trabajo en otros lugares. Puedes crear más empleos mediante la creación de industrias." }
    { group:61, id:88, text: "Esta tasa de desempleo se puede tolerar, pero si aumenta, los ciudadanos buscarán trabajo en otros lugares. Puedes crear más empleos mediante la creación de más industrias." }
    { group:61, id:89, text: "La considerable escasez de trabajadores llevará a tu ciudad a una parada absoluta. Cierra todas las industrias que nos sean necesarias o atrae a más trabajadores con viviendas desocupadas y una población feliz." }
    { group:61, id:90, text: "La considerable escasez de trabajadores impedirá que tus ciudadanos lleven a cabo sus tareas cotidianas. Cierra todas las industrias que no sean necesarias o atrae a más trabajadores con viviendas desocupadas y una población feliz." }
    { group:61, id:91, text: "A causa de la escasez de trabajadores, los ciudadanos tienen dificultades para realizar sus tareas cotidianas." }
    { group:61, id:92, text: "La escasez de trabajadores puede provocar una reducción de los bienes y servicios de la ciudad. Mejora el rendimiento de la ciudad cerrando las industrias que no sean necesarias o atrae a más trabajadores con viviendas y una población feliz." }
    { group:61, id:93, text: "La alta tasa de desempleo puede hacer que los ciudadanos, contentos con el resto de cosas, abandonen la ciudad en busca de empleos. La falta de trabajadores puede causar una reducción de los bienes y servicios de la ciudad." }
    { group:61, id:94, text: "La capital cubre todas nuestras necesidades" }
    { group:61, id:95, text: "URGENTE: El nivel de alimentos es bajo." }
    { group:61, id:96, text: "GRAVE: El nivel de alimentos es bajo." }
    { group:61, id:97, text: "IMPORTANTE: El nivel de alimentos es bajo." }
    { group:61, id:98, text: "Suministros para" }
    { group:61, id:99, text: "Los ciudadanos enfermarán si no comen lo suficiente, o abandonarán la ciudad en busca de una vida mejor. Asegúrate de que la gente no consume más de lo que produce y de que dispones de los graneros adecuados para almacenar las cosechas." }
    { group:61, id:100, text: "Los ciudadanos enfermarán si no comen lo suficiente, o abandonarán la ciudad en busca de una vida mejor. Asegúrate de que la gente no consume más de lo que produce y de que dispones de los graneros adecuados para almacenar las cosechas." }
    { group:61, id:101, text: "Los ciudadanos enfermarán si no comen lo suficiente, o abandonarán la ciudad en busca de un mejor estilo de vida. Asegúrate de que la gente no consume más de lo que produce y de que dispones de los graneros adecuados para almacenar las cosechas." }
    { group:61, id:102, text: "Los ciudadanos enfermarán si no comen lo suficiente, o abandonarán la ciudad en busca de una vida mejor. Asegúrate de que la gente no consume más de lo que produce y de que dispones de los graneros adecuados para almacenar las cosechas." }
    { group:61, id:103, text: "URGENTE: Sanidad pésima; riesgo de epidemia." }
    { group:61, id:104, text: "URGENTE: Sanidad muy mala; posible epidemia." }
    { group:61, id:105, text: "GRAVE: La sanidad es mala; riesgo de epidemia." }
    { group:61, id:106, text: "IMPORTANTE: Mala sanidad; epidemia inminente." }
    { group:61, id:107, text: "La sanidad pública está por debajo de la media." }
    { group:61, id:108, text: "La sanidad pública es regular." }
    { group:61, id:109, text: "La sanidad pública es buena." }
    { group:61, id:110, text: "La sanidad pública es muy buena." }
    { group:61, id:111, text: "La sanidad pública es excelente." }
    { group:61, id:112, text: "La sanidad pública es casi perfecta." }
    { group:61, id:113, text: "La sanidad pública es perfecta." }
    { group:61, id:114, text: "A causa de la mala salud de la mayoría de los habitantes, es muy probable que en la ciudad se declare una epidemia, que diezmaría la población. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos." }
    { group:61, id:115, text: "Con tanta gente enferma, es probable que en breve se declare una epidemia y la población de la ciudad quede diezmada. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos.." }
    { group:61, id:116, text: "Con tal cantidad de gente enferma, es difícil para los boticarios y los médicos continuar su trabajo. La ciudad corre el riesgo de sufrir una epidemia, que puede ser devastadora para los habitantes. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos." }
    { group:61, id:117, text: "Con tal cantidad de gente enferma, es difícil para los boticarios y los médicos continuar su trabajo. La ciudad puede sufrir una epidemia, que sería devastadora para los habitantes. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos." }
    { group:61, id:118, text: "Si la salud de la población empeora, se podría declarar una epidemia, que sería devastadora para los habitantes de la ciudad. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos." }
    { group:61, id:119, text: "Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Construye edificios para los médicos y mortuorios, ya que actualmente la gente no tiene acceso a los servicios que proporcionan médicos y embalsamadores. Asegúrate de que los ciudadanos tengan suficientes alimentos." }
    { group:61, id:120, text: "La buena salud es importante para frenar la malaria y otras enfermedades, y sobre todo para evitar que se declaren epidemias en la ciudad. Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Los médicos y embalsamadores de los edificios médicos y los mortuorios ayudan a mantener la ciudad sana, así como un buen suministro de diferentes alimentos." }
    { group:61, id:121, text: "La buena salud es importante para frenar la malaria y otras enfermedades, y sobre todo para evitar que se declaren epidemias en la ciudad. Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Los médicos y embalsamadores de los edificios médicos y los mortuorios ayudan a mantener la ciudad sana, así como un buen suministro de diferentes alimentos." }
    { group:61, id:122, text: "La buena salud es importante para frenar la malaria y otras enfermedades, y sobre todo para evitar que se declaren epidemias en la ciudad. Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Los médicos y embalsamadores de los edificios médicos y los mortuorios ayudan a mantener la ciudad sana, así como un buen suministro de diferentes alimentos." }
    { group:61, id:123, text: "La buena salud es importante para frenar la malaria y otras enfermedades, y sobre todo para evitar que se declaren epidemias en la ciudad. Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Los médicos y embalsamadores de los edificios médicos y los mortuorios ayudan a mantener la ciudad sana, así como un buen suministro de diferentes alimentos." }
    { group:61, id:124, text: "La buena salud es importante para frenar la malaria y otras enfermedades, y sobre todo para evitar que se declaren epidemias en la ciudad. Si la salud de la población empeora, la ciudad podría sufrir una epidemia, que puede ser devastadora para sus habitantes. Los médicos y embalsamadores de los edificios médicos y los mortuorios ayudan a mantener la ciudad sana, así como un buen suministro de diferentes alimentos." }
    { group:61, id:125, text: "IMPORTANTE: Algunos dioses no han sido aplacados" }
    { group:61, id:126, text: "GRAVE: Algunos dioses pueden acabar con nosotros" }
    { group:61, id:127, text: "IMPORTANTE: Tres dioses están sin aplacar." }
    { group:61, id:128, text: "GRAVE: Hay tres dioses que no han sido aplacados" }
    { group:61, id:129, text: "IMPORTANTE: Dos dioses están sin aplacar." }
    { group:61, id:130, text: "GRAVE: Hay dos dioses que no han sido aplacados" }
    { group:61, id:131, text: "IMPORTANTE: Hay un dios que no ha sido aplacado" }
    { group:61, id:132, text: "GRAVE: Hay un dios que no ha sido aplacado" }
    { group:61, id:133, text: "Todos los dioses han sido correctamente aplacados" }
    { group:61, id:134, text: "Los dioses están contentos, sobre todo uno." }
    { group:61, id:135, text: "Los dioses están contentos, sobre todo dos." }
    { group:61, id:136, text: "Los dioses están contentos, sobre todo tres." }
    { group:61, id:137, text: "Varios dioses están especialmente contentos." }
    { group:61, id:138, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:139, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:140, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:141, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:142, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:143, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:144, text: "Los dioses hostiles pueden usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlos." }
    { group:61, id:145, text: "Un dios enfadado puede usar sus poderes para destruir la ciudad. Construye templos y celebra festivales en su honor para aplacarlo." }
    { group:61, id:146, text: "Si un dios se vuelve hostil, puede usar sus poderes para destruir la ciudad." }
    { group:61, id:147, text: "Los dioses benevolentes pueden usar sus poderes para bendecir la ciudad de muchas formas. Asegúrate de mantener aplacados a los dioses, dedicándoles templos y celebrando festivales en su honor, a medida que crece la ciudad." }
    { group:61, id:148, text: "Los dioses benevolentes pueden usar sus poderes para bendecir la ciudad de muchas formas. Asegúrate de mantener aplacados a los dioses, dedicándoles templos y celebrando festivales en su honor, a medida que crece la ciudad." }
    { group:61, id:149, text: "Los dioses benevolentes pueden usar sus poderes para bendecir la ciudad de muchas formas. Asegúrate de mantener aplacados a los dioses, dedicándoles templos y celebrando festivales en su honor, a medida que crece la ciudad." }
    { group:61, id:150, text: "Los dioses benevolentes pueden usar sus poderes para bendecir la ciudad de muchas formas. Asegúrate de mantener aplacados a los dioses, dedicándoles templos y celebrando festivales en su honor, a medida que crece la ciudad." }
    { group:61, id:151, text: "GRAVE: No recaudamos la mayoría de los impuestos." }
    { group:61, id:152, text: "Este año los bienes han aumentado en" }
    { group:61, id:153, text: "Lo estamos haciendo tan bien como el año pasado" }
    { group:61, id:154, text: "Este año los bienes han descendido en" }
    { group:61, id:155, text: "Estás perdiendo una cantidad sustancial de dinero porque la ciudad no tiene suficientes recaudadores de impuestos. Crea más recaudadores de impuestos, sobre todo en las zonas de alto nivel de vida, y consulta la transparencia Impuestos para comprobar que todo el mundo tiene acceso a un recaudador de impuestos." }
    { group:61, id:156, text: "Si te quedas sin dinero, tienes un crédito de 5.000 debens. Sin embargo, si sigues endeudado durante mucho tiempo, las consecuencias podrían ser muy graves. Los impuestos, las exportaciones y las minas de oro son las principales fuentes de ingresos. Por supuesto, también puedes transferir dinero de tus ahorros personales al erario público." }
    { group:61, id:157, text: "Si te quedas sin dinero, tienes un crédito de 5.000 debens. Sin embargo, si sigues endeudado durante mucho tiempo, las consecuencias podrían ser muy graves. Los impuestos, las exportaciones y las minas de oro son las principales fuentes de ingresos. Por supuesto, también puedes transferir dinero de tus ahorros personales al erario público." }
    { group:61, id:158, text: "Si sigues perdiendo dinero, es posible que tengas que utilizar tu línea de crédito, que asciende a 5.000 debens, pero si sigues endeudado durante mucho tiempo, las consecuencias podrían ser muy graves. Los impuestos, las exportaciones y las minas de oro son las principales fuentes de ingresos. Por supuesto, también puedes transferir dinero de tus ahorros personales al erario público." }
    { group:61, id:159, text: "URGENTE: Muchos robos recientes," }
    { group:61, id:160, text: "GRAVE: Varios robos recientes," }
    { group:61, id:161, text: "IMPORTANTE: Algunos robos recientes," }
    { group:61, id:162, text: "Muy pocos robos." }
    { group:61, id:163, text: "No hay robos." }
    { group:61, id:164, text: "Debens robados." }
    { group:61, id:165, text: "Esta elevada cantidad de robos pueden causar una importante pérdida al erario público o incluso a tus ahorros personales. Una cantidad adecuada de palacios de justicia y comisarías puede ayudar a frenar la delincuencia y los policías controlarán a los ladrones que encuentren. Por supuesto, si la gente está contenta es más difícil que se cometan delitos." }
    { group:61, id:166, text: "Los frecuentes robos pueden causar una importante pérdida al erario público o incluso a tus ahorros personales. Los palacios de justicia y comisarías puede ayudar a frenar la delincuencia y los policías controlarán a los ladrones que encuentren. Por supuesto, si la gente está contenta es más difícil que se cometan delitos." }
    { group:61, id:167, text: "Los frecuentes robos pueden influir de forma negativa sobre las finanzas de la ciudad o incluso a tus ahorros personales. Una cantidad adecuada de palacios de justicia y comisarías puede ayudar a frenar la delincuencia y los policías controlarán a los ladrones que encuentren. Por supuesto, si la gente está contenta es más difícil que se cometan delitos." }
    { group:61, id:168, text: "Los frecuentes robos pueden influir de forma negativa sobre las finanzas de la ciudad o incluso a tus ahorros personales. Los palacios de justicia y comisarías puede ayudar a frenar la delincuencia y los policías controlarán a los ladrones que encuentren. Por supuesto, si la gente está contenta es más difícil que se cometan delitos." }
    { group:61, id:169, text: "Los robos pueden influir de forma negativa sobre las finanzas de la ciudad o incluso a tus ahorros personales. Una cantidad adecuada de palacios de justicia y comisarías puede ayudar a frenar la delincuencia y los policías controlarán a los ladrones que encuentren. Por supuesto, si la gente está contenta es más difícil que se cometan delitos." }
    { group:61, id:170, text: "No tienes compañías a las que mandar" }
    { group:61, id:171, text: "No existen informes de amenazas" }
    { group:61, id:172, text: "Se acercan enemigos a la ciudad" }
    { group:61, id:173, text: "Los enemigos están atacando la ciudad" }
    { group:61, id:174, text: "Tropas enemigas a las puertas de la ciudad." }
    { group:61, id:175, text: "Necesitan nuestras tropas en otros sitios" }
    { group:61, id:176, text: "Tenemos tropas en otros sitios" }
    { group:61, id:177, text: "No disponemos de ejército. Actualmente no existe ninguna necesidad, ya que todo está seguro." }
    { group:61, id:178, text: "Si los enemigos avanzaran hacia tu ciudad, recibirás un mensaje. Los ejércitos enemigos también aparecen en el mapa del mundo, de modo que puedes ver su avance, y con un poco de suerte, preparar la ciudad para cuando lleguen." }
    { group:61, id:179, text: "Un ejército enemigo avanza para atacar la ciudad. Durante el ataque, puede ser imposible o muy difícil construir edificios, así que prepara tus defensas mediante la construcción de murallas, torres, portones y fuertes antes de que lleguen." }
    { group:61, id:180, text: "Siempre es mejor estar preparado para el ataque en vez de intentar reclutar gente para el ejército en el último momento. Es de esperar que la ciudad disponga de las defensas adecuadas para su protección." }
    { group:61, id:181, text: "Siempre es mejor estar preparado para el ataque en vez de intentar reclutar gente para el ejército en el último momento. Es de esperar que la ciudad disponga de las defensas adecuadas para su protección." }
    { group:61, id:182, text: "Se ha recibido una solicitud de tropas de otro jefe egipcio. Generalmente, es mejor aceptar las solicitudes si se quieren mantener buenas relaciones con el resto del imperio. Consulta con el supervisor político y con el supervisor de ejército para enviar tropas." }
    { group:61, id:183, text: "Las tropas lejanas mejoran nuestra reputación." }
    { group:61, id:184, text: "Hay muchas peticiones de ayuda pendientes." }
    { group:61, id:185, text: "Hay varias peticiones de ayuda pendientes." }
    { group:61, id:186, text: "Hay algunas peticiones de ayuda pendientes." }
    { group:61, id:187, text: "No hay peticiones de ayuda pendientes." }
    { group:61, id:188, text: "Si no respondes a las solicitudes del faraón o de tus vecinos, puede tener lugar una serie de efectos negativos. Las ciudades egipcias vecinas pueden sucumbir a la pobreza o caer en manos de los enemigos si no las ayudas en tiempos de necesidad, de modo que si quieres mantener buenas relaciones con tus compatriotas, es mejor que respondas a sus solicitudes de buen grado y sin tardanza." }
    { group:61, id:189, text: "Si no respondes a las solicitudes del faraón o de tus vecinos, puede tener lugar una serie de efectos negativos. Las ciudades egipcias vecinas pueden sucumbir a la pobreza o caer en manos de los enemigos si no las ayudas en tiempos de necesidad, de modo que si quieres mantener buenas relaciones con tus compatriotas, es mejor que respondas a sus solicitudes de buen grado y sin tardanza." }
    { group:61, id:190, text: "Si no ayudas a las otras ciudades egipcias en tiempos de necesidad, pueden sucumbir a la pobreza, caer en manos de los enemigos o sufrir otro triste destino. Esto podría influir negativamente sobre el comercio, los precios y tu consideración en el imperio, de modo que si quieres mantener buenas relaciones con tus compatriotas, es mejor que respondas a sus solicitudes de buen grado y sin tardanza." }
    { group:61, id:191, text: "Si quieres mantener buenas relaciones con tus compatriotas, es mejor que respondas a cualquier solicitud, que te hagan en tiempos de necesidad, de buen grado y sin tardanza. Si no lo haces, pueden sucumbir a la pobreza, caer en manos de los enemigos o sufrir otro triste destino. Esto podría influir negativamente sobre el comercio, los precios y tu consideración en el imperio." }
    { group:61, id:192, text: "Este año no habrá crecida" }
    { group:61, id:193, text: "La crecida será escasa este año" }
    { group:61, id:194, text: "La crecida será regular este año" }
    { group:61, id:195, text: "La crecida será buena este año" }
    { group:61, id:196, text: "La crecida será excelente este año" }
    { group:61, id:197, text: "La crecida será perfecta este año" }
    { group:61, id:198, text: "La falta de crecida de este año significará que el fértil lodo del Nilo no se depositará en los campos. Si la ciudad depende del cultivo de las praderas inundadas para conseguir alimentos, esto podría poner en grave peligro la supervivencia de las ciudadanos. Si veneras a Osiris, dios de la crecida del Nilo, puede evitar que ocurra lo mismo el año que viene." }
    { group:61, id:199, text: "La débil crecida que se espera este año significará que poca cantidad del fértil lodo del Nilo se depositará en los campos. Si la ciudad depende del cultivo de las praderas inundadas para conseguir alimentos, esto podría poner en grave peligro la supervivencia de las ciudadanos. Si veneras a Osiris, dios de la crecida del Nilo, puede evitar que ocurra lo mismo el año que viene." }
    { group:61, id:200, text: "La crecida moderada que se espera este año significará que no será mucho el lodo del Nilo que se deposite en los campos. Si la ciudad depende del cultivo de las praderas inundadas para conseguir alimentos, esto podría poner en grave peligro la supervivencia de las ciudadanos. Si veneras a Osiris, dios de la crecida del Nilo, puede evitar que ocurra lo mismo el año que viene." }
    { group:61, id:201, text: "La buena crecida esperada para este año llenará del rico y fértil lodo del Nilo los campos de tu ciudad. Asegúrate de que Osiris, dios de la crecida del Nilo, sigue complacido; de lo contrario, podría contener esta bendición el año que viene." }
    { group:61, id:202, text: "Si tu ciudad depende del cultivo de las praderas inundadas para conseguir alimentos, la cantidad de lodo depositado en los campos por esta excelente crecida es un regalo que no hay que dar por sentado. Asegúrate de que Osiris, dios de la crecida del Nilo, sigue complacido; de lo contrario, podría contener esta bendición el año que viene." }
    { group:61, id:203, text: "Si tu ciudad depende del cultivo de las praderas inundadas para conseguir alimentos, la cantidad de lodo depositado en los campos por esta increíble crecida es un regalo impagable que no hay que dar por sentado. Alaba a Osiris, dios de la crecida del Nilo, para que se repita esta bendición el año que viene." }
    { group:61, id:204, text: "La crecida se espera para principios de junio." }
    { group:61, id:205, text: "La crecida se espera para finales de junio." }
    { group:61, id:206, text: "La crecida se espera para principios de julio." }
    { group:61, id:207, text: "La crecida se espera para finales de julio." }
    { group:61, id:208, text: "La crecida se espera para principios de agosto." }
    { group:61, id:209, text: "La crecida se espera para finales de agosto." }
    { group:61, id:210, text: "Se espera que la crecida sea a principios de septiembre" }
    { group:61, id:211, text: "La crecida se espera para finales de septiembre." }
    { group:61, id:212, text: "Si tus ciudadanos no comen lo suficiente, enfermarán o abandonarán la ciudad en busca de una vida mejor. Construye más campos de cultivo, refugios de caza, dársenas pesqueras o granjas de ganado vacuno, o importa más comida, para alimentar a esta cantidad de población. También puedes usar el riego para mejorar el rendimiento de la tierra que cultivas en la actualidad." }
    { group:61, id:213, text: "Si tus ciudadanos no comen lo suficiente, enfermarán o abandonarán la ciudad en busca de una vida mejor. Construye más campos de cultivo, refugios de caza, dársenas pesqueras o granjas de ganado vacuno, o importa más comida, para alimentar a esta cantidad de población." }
    { group:61, id:214, text: "Si tus ciudadanos no comen lo suficiente, enfermarán o abandonarán la ciudad en busca de una vida mejor. Construye más campos de cultivo, refugios de caza, dársenas pesqueras o granjas de ganado vacuno, o importa más comida." }
    { group:61, id:215, text: "Si tus ciudadanos no comen lo suficiente, enfermarán o abandonarán la ciudad en busca de una vida mejor. Tienes la cantidad adecuada de campos de cultivo, refugios de caza, dársenas pesqueras, granjas de ganado vacuno e importación de comida para alimentar a esta cantidad de población." }
    { group:61, id:216, text: "Si tus ciudadanos están bien alimentados, es probable que gocen de buena salud y no abandonarán la ciudad en busca de una dieta mejor. Tienes más granjas de cultivo y ganado, así como refugios de caza, de los que necesitas para alimentar a la población." }
    { group:61, id:217, text: "Si tus ciudadanos están bien alimentados, es probable que gocen de buena salud y no abandonarán la ciudad en busca de una dieta mejor. Tienes muchas más granjas de cultivo y ganado, así como refugios de caza, de los que necesitas para alimentar a la población." }
    { group:61, id:218, text: "Haz clic en cualquier opción para conseguir más información y consejos" }
    { group:62, id:0, text: "Victoria" }
    { group:62, id:1, text: "¡Despedido!" }
    { group:62, id:2, text: "Has completado con éxito esta misión." }
    { group:62, id:3, text: "Continuar" }
    { group:62, id:4, text: "Continuar gobernando durante 2 años más." }
    { group:62, id:5, text: "Continuar durante 5 años más." }
    { group:62, id:6, text: "Nueva partida" }
    { group:62, id:7, text: "A la ciudad" }
    { group:62, id:8, text: "¡Felicidades!" }
    { group:62, id:9, text: "Has terminado las misiones del periodo predinástico. Para llevar a cabo un desafío de verdad, haz clic de nuevo en Jugar demo y pasa al imperio antiguo." }
    { group:62, id:10, text: "Objetivos" }
    { group:62, id:11, text: "Población de" }
    { group:62, id:12, text: "Puntos de cultura" }
    { group:62, id:13, text: "Puntos de prosperidad" }
    { group:62, id:14, text: "Puntos de monumentos" }
    { group:62, id:15, text: "Puntos de imperio" }
    { group:62, id:16, text: "Estoy muy confundido. A pesar de la confianza que la gente de Egipto depositó en ti, parece que los dioses te han abandonado. Tu ciudad no honra a Egipto. Incluso se cuestiona tu entrada en el Campo de cañas. Es un triste final para un comienzo tan prometedor. Ahora debes dejar tu puesto a otro: el faraón." }
    { group:62, id:17, text: "Construir parques de bomberos" }
    { group:62, id:18, text: "Construir puestos de arquitectos." }
    { group:62, id:19, text: "Construir un granero y llenarlo con presas" }
    { group:62, id:20, text: "Proporcionar a las casas alimentos de un bazar" }
    { group:62, id:21, text: "Construir casas" }
    { group:62, id:22, text: "Construir quioscos y escuelas de malabaristas" }
    { group:62, id:23, text: "Construir templos y santuarios de Bastet" }
    { group:62, id:24, text: "Extraer oro" }
    { group:62, id:25, text: "Construir boticas y médicos" }
    { group:62, id:26, text: "Embellece y mejora tu ciudad con jardines." }
    { group:62, id:27, text: "Llenar un almacén de cerámica." }
    { group:62, id:28, text: "Construir un granero y llenarlo de higos." }
    { group:62, id:29, text: "Importar ladrillos" }
    { group:62, id:30, text: "Fabricar papiros y construir una escuela de escribas" }
    { group:62, id:31, text: "Construir un piso amplio en la ciudad." }
    { group:62, id:32, text: "Construir una mastaba." }
    { group:62, id:33, text: "Destilar cerveza." }
    { group:62, id:34, text: "Pulsa el símbolo ankh (cruz) para ver los objetivos de la misión" }
    { group:62, id:35, text: "Tu lugar en la historia está asegurado. Los egipcios te han declarado dios." }
    { group:62, id:36, text: "¡Acepta el status de deidad!" }
    { group:62, id:37, text: "Repetir misión" }
    { group:62, id:38, text: "¡Se acabó el tiempo!" }
    { group:62, id:39, text: "Has perdido esta misión. Puedes disminuir la dificultad para conseguir tiempo extra o puedes volver a jugar la misión." }
    { group:62, id:40, text: "Disminuir la dificultad" }
    { group:63, id:0, text: "Mensajes" }
    { group:63, id:1, text: "Actualmente no tienes mensajes. A medida que crezca tu ciudad, o si otras ciudades te piden artículos, irán apareciendo aquí." }
    { group:63, id:2, text: "Fecha" }
    { group:63, id:3, text: "Tema" }
    { group:63, id:4, text: "Haz clic izquierdo sobre un mensaje para leerlo. Haz clic derecho para borrarlo." }
    { group:63, id:5, text: "Para" }
    { group:63, id:6, text: "Borrar los mensajes leídos" }
    { group:64, id:0, text: "Nadie" }
    { group:64, id:1, text: "Inmigrante" }
    { group:64, id:2, text: "Emigrante" }
    { group:64, id:3, text: "Indigente" }
    { group:64, id:4, text: "Carretero" }
    { group:64, id:5, text: "Ciudadano" }
    { group:64, id:6, text: "Explosión" }
    { group:64, id:7, text: "Recaudador de impuestos" }
    { group:64, id:8, text: "Arquitecto" }
    { group:64, id:9, text: "Almacenista" }
    { group:64, id:10, text: "Bombero" }
    { group:64, id:11, text: "Arquero" }
    { group:64, id:12, text: "Auriga" }
    { group:64, id:13, text: "Infantería" }
    { group:64, id:14, text: "Mozo normal" }
    { group:64, id:15, text: "Malabarista" }
    { group:64, id:16, text: "Músico" }
    { group:64, id:17, text: "Bailarina" }
    { group:64, id:18, text: "Jugador de senet" }
    { group:64, id:19, text: "Caravana de mercaderes de" }
    { group:64, id:20, text: "Barco de comercio de" }
    { group:64, id:21, text: "Caravana de mercaderes de" }
    { group:64, id:22, text: "Manifestante" }
    { group:64, id:23, text: "Criminal" }
    { group:64, id:24, text: "Ladrón de tumbas" }
    { group:64, id:25, text: "Barco de pesca" }
    { group:64, id:26, text: "Comerciante de bazar" }
    { group:64, id:27, text: "Sacerdote" }
    { group:64, id:28, text: "Alumno" }
    { group:64, id:29, text: "Profesor" }
    { group:64, id:30, text: "Bibliotecario" }
    { group:64, id:31, text: "Dentista" }
    { group:64, id:32, text: "Médico" }
    { group:64, id:33, text: "Herbolario" }
    { group:64, id:34, text: "Embalsamador" }
    { group:64, id:35, text: "Trabajador" }
    { group:64, id:36, text: "Bandera de mapa" }
    { group:64, id:37, text: "Restos flotantes" }
    { group:64, id:38, text: "Estibador" }
    { group:64, id:39, text: "Cliente de bazar" }
    { group:64, id:40, text: "Escriba" }
    { group:64, id:41, text: "Indigenous native (not used?)" }
    { group:64, id:42, text: "Centinela" }
    { group:64, id:43, text: "Enemigo" }
    { group:64, id:44, text: "Enemigo" }
    { group:64, id:45, text: "Enemigo" }
    { group:64, id:46, text: "Enemigo" }
    { group:64, id:47, text: "Enemigo" }
    { group:64, id:48, text: "Enemigo" }
    { group:64, id:49, text: "Barbarian (not used?)" }
    { group:64, id:50, text: "Barbarian (not used?)" }
    { group:64, id:51, text: "Barbarian (not used?)" }
    { group:64, id:52, text: "Barbarian (not used?)" }
    { group:64, id:53, text: "Enemigo" }
    { group:64, id:54, text: "Enemigo" }
    { group:64, id:55, text: "Enemigo" }
    { group:64, id:56, text: "Enemigo" }
    { group:64, id:57, text: "Enemigo" }
    { group:64, id:58, text: "Native Trader (not used?)" }
    { group:64, id:59, text: "Flecha" }
    { group:64, id:60, text: "Jabalina" }
    { group:64, id:61, text: "Proyectil" }
    { group:64, id:62, text: "Ballesta" }
    { group:64, id:63, text: "Criatura" }
    { group:64, id:64, text: "Misionero" }
    { group:64, id:65, text: "Gaviotas" }
    { group:64, id:66, text: "Chico de reparto" }
    { group:64, id:67, text: "Naufragio" }
    { group:64, id:68, text: "Aves" }
    { group:64, id:69, text: "Avestruz" }
    { group:64, id:70, text: "Antílope" }
    { group:64, id:71, text: "Lanza" }
    { group:64, id:72, text: "Auriga" }
    { group:64, id:73, text: "Cazador" }
    { group:64, id:74, text: "Lanza de cazador" }
    { group:64, id:75, text: "Serrería" }
    { group:64, id:76, text: "Transbordador" }
    { group:64, id:77, text: "Buque de transporte" }
    { group:64, id:78, text: "Buque de guerra" }
    { group:64, id:79, text: "Carpintero" }
    { group:64, id:80, text: "Albañil" }
    { group:64, id:81, text: "Cantero" }
    { group:64, id:82, text: "Cocodrilo" }
    { group:64, id:83, text: "Hiena" }
    { group:64, id:84, text: "Hipopótamo" }
    { group:64, id:85, text: "Trabajador" }
    { group:64, id:86, text: "Trineo" }
    { group:64, id:87, text: "Aguador" }
    { group:64, id:88, text: "Policía" }
    { group:64, id:89, text: "Juez" }
    { group:64, id:90, text: "Recolector de caña" }
    { group:64, id:91, text: "Sacerdote de festival" }
    { group:64, id:92, text: "Transporte enemigo" }
    { group:64, id:93, text: "Buque enemigo" }
    { group:64, id:94, text: "Funerario" }
    { group:64, id:95, text: "Pescado" }
    { group:64, id:96, text: "Conductor de trineo" }
    { group:64, id:97, text: "Comediante" }
    { group:64, id:98, text: "Ciudadano apestado" }
    { group:64, id:99, text: "Infantería beduina" }
    { group:64, id:100, text: "Barco de guerra egipcio" }
    { group:64, id:101, text: "Barco de transporte egipcio" }
    { group:64, id:102, text: "Áspid" }
    { group:64, id:103, text: "León" }
    { group:64, id:104, text: "Escorpión" }
    { group:64, id:105, text: "Guarda del zoológico" }
    { group:64, id:106, text: "Rana" }
    { group:64, id:107, text: "Langosta" }
    { group:64, id:108, text: "Artesano de tumbas" }
    { group:64, id:109, text: "Momia" }
    { group:64, id:110, text: "Faraón" }
    { group:65, id:0, text: "unused section 65 - was c3 walker names" }
    { group:66, id:0, text: "Ayuda contextual sobreimpresa" }
    { group:66, id:1, text: "Esta tierra está dentro del radio de un suministro de aguas subterráneas, por lo que los pozos de cualquier tamaño pueden funcionar aquí." }
    { group:66, id:2, text: "Esta vivienda no tiene acceso a agua potable" }
    { group:66, id:3, text: "Esta vivienda tan sólo tiene acceso básico a agua potable" }
    { group:66, id:4, text: "Esta casa no tiene reserva de alimentos." }
    { group:66, id:5, text: "Esta casa gastará pronto su limitada reserva de alimentos." }
    { group:66, id:6, text: "Esta casa tiene una reserva de alimentos que durará al menos hasta el mes próximo." }
    { group:66, id:7, text: "Esta casa no tiene problemas para conseguir la comida necesaria que le permita salir adelante ." }
    { group:66, id:8, text: "A esta casa no llega el reparto de agua potable limpia" }
    { group:66, id:9, text: "Esta casa ha sido visitada recientemente por un aguador. Tendrá agua potable limpia durante mucho tiempo" }
    { group:66, id:10, text: "Esta casa tiene reservas de agua potable limpia" }
    { group:66, id:11, text: "A menos que un aguador la visite pronto, esta casa acabará con sus reservas de agua potable limpia" }
    { group:66, id:12, text: "Esta casa no tiene acceso a templos ni santuarios" }
    { group:66, id:13, text: "Esta casa tiene acceso a un templo de un solo dios." }
    { group:66, id:14, text: "Esta casa tiene acceso a templos de 2 dioses diferentes." }
    { group:66, id:15, text: "Esta casa tiene acceso a templos de 3 dioses diferentes." }
    { group:66, id:16, text: "Esta casa tiene acceso a templos de 4 dioses diferentes." }
    { group:66, id:17, text: "Esta casa tiene acceso a templos de todos los dioses." }
    { group:66, id:18, text: "Esta casa tiene acceso a un santuario y a templos de todos los dioses" }
    { group:66, id:19, text: "Esta casa no tiene acceso a una escuela de escribas" }
    { group:66, id:20, text: "Esta casa ha sido visitada recientemente por un sabio. Tendrá acceso a la escuela de escribas durante mucho tiempo" }
    { group:66, id:21, text: "Esta casa tiene acceso a la escuela de escribas" }
    { group:66, id:22, text: "A menos que un sabio la visite pronto, esta casa perderá el acceso a la escuela de escribas" }
    { group:66, id:23, text: "Esta casa no tiene acceso a una biblioteca." }
    { group:66, id:24, text: "Esta casa ha sido visitada recientemente por un bibliotecario. Tendrá acceso a la biblioteca durante mucho tiempo." }
    { group:66, id:25, text: "Esta casa tiene acceso a una biblioteca." }
    { group:66, id:26, text: "A menos que sea visitada pronto por un bibliotecario, esta casa perderá el acceso a la biblioteca." }
    { group:66, id:27, text: "Esta casa no tiene acceso a una academia." }
    { group:66, id:28, text: "Esta casa ha sido visitada recientemente por un profesor. Tendrá acceso a la academia durante mucho tiempo." }
    { group:66, id:29, text: "Esta casa tiene acceso a una academia." }
    { group:66, id:30, text: "A menos que sea visitada pronto por un profesor, esta casa perderá el acceso a la academia." }
    { group:66, id:31, text: "Esta casa no tiene acceso a la consulta de un dentista" }
    { group:66, id:32, text: "Esta casa ha sido visitada recientemente por un dentista. Tendrá acceso a un dentista durante mucho tiempo" }
    { group:66, id:33, text: "Esta casa tiene acceso a un dentista" }
    { group:66, id:34, text: "A menos que un dentista la visite pronto, esta casa perderá el acceso a la consulta del dentista" }
    { group:66, id:35, text: "Esta casa no tiene acceso a una botica" }
    { group:66, id:36, text: "Esta casa ha sido visitada recientemente por un boticario. Tendrá acceso a la botica durante mucho tiempo." }
    { group:66, id:37, text: "Esta casa tiene acceso a una botica" }
    { group:66, id:38, text: "A menos que un boticario la visite pronto, esta casa perderá el acceso a una botica." }
    { group:66, id:39, text: "Esta casa no tiene acceso a un mortuorio" }
    { group:66, id:40, text: "Esta casa ha sido visitada recientemente por un embalsamador. Tendrá acceso a un mortuorio durante mucho tiempo" }
    { group:66, id:41, text: "Esta casa tiene acceso a un mortuorio" }
    { group:66, id:42, text: "A menos que un embalsamador la visite pronto, esta casa perderá el acceso al mortuorio" }
    { group:66, id:43, text: "Esta casa no está inscrita para los impuestos, por lo que no paga ninguno." }
    { group:66, id:44, text: "No se han recaudado impuestos en esta casa este año." }
    { group:66, id:45, text: "debens recaudados este año hasta ahora" }
    { group:66, id:46, text: "Este edificio no tiene posibilidades de incendiarse." }
    { group:66, id:47, text: "Este edificio tiene pocas posibilidades de incendiarse." }
    { group:66, id:48, text: "Este edificio tiene algo de riesgo de incendio." }
    { group:66, id:49, text: "Este edificio tiene riesgo de incendio." }
    { group:66, id:50, text: "Este edificio es una trampa incendiaria." }
    { group:66, id:51, text: "¡Este edificio podría incendiarse en cualquier momento!" }
    { group:66, id:52, text: "Este edificio está en perfectas condiciones estructurales." }
    { group:66, id:53, text: "Este edificio tiene pocas posibilidades de derrumbarse." }
    { group:66, id:54, text: "Este edificio tiene algo de riesgo de derrumbarse." }
    { group:66, id:55, text: "Este edificio presenta algunos fallos estructurales." }
    { group:66, id:56, text: "Este edificio presenta numerosos fallos estructurales y grietas." }
    { group:66, id:57, text: "Este edificio está inestable y puede derrumbarse en cualquier momento." }
    { group:66, id:58, text: "Este es un vecindario cumplidor de la ley, donde no se registra criminalidad." }
    { group:66, id:59, text: "En esta zona raramente hay criminalidad." }
    { group:66, id:60, text: "Esta es una zona con poca criminalidad, pero algunos vecinos se han quejado." }
    { group:66, id:61, text: "Recientemente se han registrado varios crímenes, pero en general este vecindario es bastante seguro." }
    { group:66, id:62, text: "Ésta es una zona de alta criminalidad. Los residentes están descontentos y las calles no son seguras por la noche." }
    { group:66, id:63, text: "Esta zona es un hervidero de crimen y barbarie. Los delitos y motines están generalizados." }
    { group:66, id:64, text: "Esta vivienda no tiene acceso a ningún tipo de entretenimiento." }
    { group:66, id:65, text: "Esta vivienda apenas tiene acceso a entretenimientos." }
    { group:66, id:66, text: "Esta vivienda tiene acceso muy limitado a actividades de entretenimiento." }
    { group:66, id:67, text: "Esta vivienda tiene acceso limitado a actividades de entretenimiento." }
    { group:66, id:68, text: "Esta vivienda tiene algo de acceso a actividades de entretenimiento." }
    { group:66, id:69, text: "Esta vivienda tiene acceso a varias actividades de entretenimiento." }
    { group:66, id:70, text: "Esta vivienda tiene acceso razonable a actividades de entretenimiento." }
    { group:66, id:71, text: "Esta vivienda tiene buen acceso a actividades de entretenimiento." }
    { group:66, id:72, text: "Esta vivienda tiene muy buen acceso a actividades de entretenimiento." }
    { group:66, id:73, text: "Esta vivienda tiene un excelente acceso a actividades de entretenimiento." }
    { group:66, id:74, text: "Esta vivienda tiene acceso a todas las actividades de entretenimiento que desee." }
    { group:66, id:75, text: "Esta casa no tiene acceso a malabaristas" }
    { group:66, id:76, text: "Esta casa ha sido visitada recientemente por un malabarista. Tendrá acceso a un malabarista durante mucho tiempo" }
    { group:66, id:77, text: "Esta casa tiene acceso a malabaristas" }
    { group:66, id:78, text: "Esta casa no ha sido visitada por ningún malabarista durante bastante tiempo. Pronto perderá el acceso a un malabarista." }
    { group:66, id:79, text: "Esta casa no tiene acceso a un escenario de músicos" }
    { group:66, id:80, text: "Esta casa ha sido visitada recientemente por un músico. Tendrá acceso a la música durante mucho tiempo" }
    { group:66, id:81, text: "Esta casa tiene acceso a un músico" }
    { group:66, id:82, text: "Esta casa no ha sido visitada por ningún músico durante un tiempo. Pronto perderá el acceso a la música." }
    { group:66, id:83, text: "Esta casa no tiene acceso a un escenario de baile" }
    { group:66, id:84, text: "Esta casa ha sido visitada recientemente por una bailarina. Tendrá acceso a la danza durante mucho tiempo" }
    { group:66, id:85, text: "Esta casa tiene acceso a un escenario de danza" }
    { group:66, id:86, text: "Esta casa no ha sido visitada por ninguna bailarina durante cierto tiempo. Pronto perderá el acceso a la danza" }
    { group:66, id:87, text: "Esta casa no tiene acceso a un local de senet" }
    { group:66, id:88, text: "Esta casa ha sido visitada recientemente por un maestro de senet. Tendrá acceso a un local de senet durante mucho tiempo" }
    { group:66, id:89, text: "Esta casa tiene acceso a un local de senet" }
    { group:66, id:90, text: "Esta casa no ha sido visitada por ningún maestro de senet durante cierto tiempo. Pronto perderá el acceso a un local de senet" }
    { group:66, id:91, text: "Ningún ciudadano desea vivir aquí." }
    { group:66, id:92, text: "Tus ciudadanos no asocian factores negativos o positivos con esta zona." }
    { group:66, id:93, text: "Esta tierra es una zona deseable" }
    { group:66, id:94, text: "Este edificio no tiene acceso a gente que aporte trabajo." }
    { group:66, id:95, text: "Este edificio tiene muy poco acceso a gente que aporte trabajo." }
    { group:66, id:96, text: "Este edificio tiene acceso precario a gente que aporte trabajo." }
    { group:66, id:97, text: "Este edificio tiene algo de acceso a gente que aporte trabajo." }
    { group:66, id:98, text: "Este edificio tiene buen acceso a gente que aporte trabajo." }
    { group:66, id:99, text: "Este edificio tiene un acceso excelente a gente que aporte trabajo." }
    { group:66, id:100, text: "Esta casa no tiene acceso a escuelas de escribas ni a bibliotecas." }
    { group:66, id:101, text: "Esta casa tiene acceso a una escuela de escribas o a una biblioteca" }
    { group:66, id:102, text: "Esta casa tiene acceso a una escuela de escribas y a una biblioteca" }
    { group:66, id:103, text: "Esta casa tiene acceso a una escuela de escribas y a una biblioteca. Los niños acuden a la academia." }
    { group:66, id:104, text: "Los habitantes de esta cabaña buscan entre la basura para conseguir comida." }
    { group:66, id:105, text: "Esta tierra es muy fértil. Las cosechas serán abundantes y resistentes" }
    { group:66, id:106, text: "Esta tierra es bastante fértil. Las cosechas tenderán a ser muy saludables" }
    { group:66, id:107, text: "Esta tierra es moderadamente fértil. Las cosechas no alcanzarán todo el esplendor posible." }
    { group:66, id:108, text: "Esta tierra no es muy fértil. Apenas es posible cosechar algo aquí." }
    { group:66, id:109, text: "Esta tierra no es fértil. No se puede cosechar nada aquí." }
    { group:66, id:110, text: "cestas de cereales están almacenadas en este edificio." }
    { group:66, id:111, text: "cesta de cereales está almacenada en este edificio." }
    { group:66, id:112, text: "tarros de fruta están almacenados en este edificio." }
    { group:66, id:113, text: "tarro de fruta está almacenado en este edificio." }
    { group:66, id:114, text: "tarros de verduras están almacenados en este edificio." }
    { group:66, id:115, text: "tarro de verdura está almacenado en este edificio." }
    { group:66, id:116, text: "trozos de carne están almacenados en este edificio." }
    { group:66, id:117, text: "trozo de carne está almacenado en este edificio." }
    { group:66, id:118, text: "piezas de cerámica están almacenadas en este edificio." }
    { group:66, id:119, text: "pieza de cerámica está almacenada en este edificio." }
    { group:66, id:120, text: "bolsas de joyas (artículos de lujo) están almacenadas en este edificio." }
    { group:66, id:121, text: "bolsa de joyas (artículos de lujo) está almacenada en este edificio." }
    { group:66, id:122, text: "madejas de fibra de lino están almacenadas en este edificio." }
    { group:66, id:123, text: "madeja de fibra de lino está almacenada en este edificio." }
    { group:66, id:124, text: "botellas de cerveza están almacenadas en este edificio." }
    { group:66, id:125, text: "botella de cerveza está almacenada en este edificio." }
    { group:66, id:126, text: "Este edificio no almacena bienes" }
    { group:66, id:127, text: "No es probable que en este edificio se declare una enfermedad" }
    { group:66, id:128, text: "En este edificio existe un riesgo insignificante de que se declare una enfermedad" }
    { group:66, id:129, text: "En este edificio existe un riesgo considerable de que se declare una enfermedad" }
    { group:66, id:130, text: "En este edificio existe un gran riesgo de que se declare una enfermedad" }
    { group:66, id:131, text: "En este edificio se ha declarado una enfermedad" }
    { group:66, id:132, text: "No hay acceso a un médico" }
    { group:66, id:133, text: "Esta casa no ha sido visitada por ningún médico durante cierto tiempo" }
    { group:66, id:134, text: "Esta casa ha sido visitada por un médico" }
    { group:66, id:135, text: "Esta casa ha sido visitada recientemente por un médico" }
    { group:66, id:136, text: "No es probable que en este edificio se declare la malaria" }
    { group:66, id:137, text: "En este edificio existe un riesgo insignificante de que se declare la malaria" }
    { group:66, id:138, text: "En este edificio existe un riesgo considerable de que se declare la malaria" }
    { group:66, id:139, text: "En este edificio existe un gran riesgo de que se declare la malaria" }
    { group:66, id:140, text: "En este edificio se declarará pronto la malaria" }
    { group:66, id:141, text: "Esta casa tiene los siguientes problemas:" }
    { group:66, id:142, text: "Esta industria tiene los siguientes problemas:" }
    { group:66, id:143, text: "Riesgo de derrumbamiento" }
    { group:66, id:144, text: "Riesgo de incendio" }
    { group:66, id:145, text: "Riesgo de enfermedad" }
    { group:66, id:146, text: "Vacío" }
    { group:66, id:147, text: "Riesgo de malaria" }
    { group:66, id:148, text: "Enfermedad" }
    { group:66, id:149, text: "Posible riesgo de delincuencia" }
    { group:66, id:150, text: "Decaerá pronto" }
    { group:66, id:151, text: "Falta de materia prima" }
    { group:66, id:152, text: "No hay trabajadores" }
    { group:66, id:153, text: "Trabajadores a tiempo parcial" }
    { group:66, id:154, text: "En reserva" }
    { group:66, id:155, text: "No hay acceso a mano de obra" }
    { group:66, id:156, text: "Plagado de ranas" }
    { group:66, id:157, text: "En esta vivienda no vive nadie" }
    { group:66, id:158, text: "Esta casa no tiene acceso a un juzgado" }
    { group:66, id:159, text: "Esta casa ha sido visitada hace poco por un juez. Tendrá acceso a un juzgado durante mucho tiempo." }
    { group:66, id:160, text: "Esta casa tiene acceso a un juzgado" }
    { group:66, id:161, text: "Esta casa no ha sido visitada por ningún juez durante cierto tiempo. Pronto perderá el acceso a un juzgado." }
    { group:66, id:162, text: "Esta es una de las zonas menos atractivas de la ciudad" }
    { group:66, id:163, text: "A nadie le gustaría vivir aquí, pero hay sitios peores" }
    { group:66, id:164, text: "La gente no tiene ideas muy firmes sobre el atractivo de esta zona" }
    { group:66, id:165, text: "Esta zona es mejor que otras, pero no es muy atractiva" }
    { group:66, id:166, text: "La mayoría de la gente encontraría este lugar agradable para vivir" }
    { group:66, id:167, text: "Ésta es una de las direcciones más elegantes de la ciudad" }
    { group:66, id:168, text: "Esta casa no tiene acceso a un zoológico." }
    { group:66, id:169, text: "Esta casa ha sido visitada hace poco por un guarda. Tendrá acceso a un zoológico durante mucho tiempo." }
    { group:66, id:170, text: "Esta casa tiene acceso a un zoológico." }
    { group:66, id:171, text: "Esta casa no ha sido visitada por un guarda durante cierto tiempo. Pronto perderá el acceso a un zoológico." }
    { group:66, id:172, text: "Esta casa está plagada de ranas." }
    { group:67, id:0, text: "Estructuras autorizadas" }
    { group:67, id:1, text: "Materias primas" }
    { group:67, id:2, text: "Mina de oro" }
    { group:67, id:3, text: "Bomba de agua" }
    { group:67, id:4, text: "Acequia de riego" }
    { group:67, id:5, text: "Dársena pesquera" }
    { group:67, id:6, text: "Campo de trabajo" }
    { group:67, id:7, text: "Granero" }
    { group:67, id:8, text: "Bazar" }
    { group:67, id:9, text: "Almacén" }
    { group:67, id:10, text: "Muelle" }
    { group:67, id:11, text: "Malabares" }
    { group:67, id:12, text: "Música" }
    { group:67, id:13, text: "Danza" }
    { group:67, id:14, text: "Juegos de senet" }
    { group:67, id:15, text: "Plaza de festivales" }
    { group:67, id:16, text: "Escuela de escribas" }
    { group:67, id:17, text: "Biblioteca" }
    { group:67, id:18, text: "Suministro de agua" }
    { group:67, id:19, text: "Dentista" }
    { group:67, id:20, text: "Botica" }
    { group:67, id:21, text: "Médico" }
    { group:67, id:22, text: "Mortuorio" }
    { group:67, id:23, text: "Recaudador de impuestos" }
    { group:67, id:24, text: "Palacio de justicia" }
    { group:67, id:25, text: "Palacio" }
    { group:67, id:26, text: "Palacete" }
    { group:67, id:27, text: "Barricada" }
    { group:67, id:28, text: "Puente" }
    { group:67, id:29, text: "Embarc. del transbordador" }
    { group:67, id:30, text: "Jardines" }
    { group:67, id:31, text: "Plaza" }
    { group:67, id:32, text: "Estatuas" }
    { group:67, id:33, text: "Muralla" }
    { group:67, id:34, text: "Torre" }
    { group:67, id:35, text: "Portón" }
    { group:67, id:36, text: "Reclutador" }
    { group:67, id:37, text: "Fuerte: infantería" }
    { group:67, id:38, text: "Fuerte: arqueros" }
    { group:67, id:39, text: "Fuerte: aurigas" }
    { group:67, id:40, text: "Academia" }
    { group:67, id:41, text: "Armero" }
    { group:67, id:42, text: "Taller de cuadrigas" }
    { group:67, id:43, text: "Dársena barco guerra" }
    { group:67, id:44, text: "Dársena barco transporte" }
    { group:67, id:45, text: "Zoológico" }
    { group:68, id:0, text: "Este es el texto para la ayuda del ratón" }
    { group:68, id:1, text: "Muestra la pagina de ayuda apropiada para este panel" }
    { group:68, id:2, text: "Salir de este panel" }
    { group:68, id:3, text: "Cargar esta partida guardada" }
    { group:68, id:4, text: "Guardar la partida actual en este archivo" }
    { group:68, id:5, text: "Cancelar esta operación" }
    { group:68, id:6, text: "Recorrer las partidas guardadas" }
    { group:68, id:7, text: "Haz clic sobre el nombre de un archivo para seleccionarlo" }
    { group:68, id:8, text: "mouse help free" }
    { group:68, id:9, text: "mouse help free" }
    { group:68, id:10, text: "Oculta el panel de control para ver una zona de juego más amplia" }
    { group:68, id:11, text: "Seleccionar un informe superpuesto de la ciudad" }
    { group:68, id:12, text: "Mostrar el panel de control completo" }
    { group:68, id:13, text: "Cargar esta partida" }
    { group:68, id:14, text: "Guardar la partida actual en este archivo" }
    { group:68, id:15, text: "Cancelar esta operación" }
    { group:68, id:16, text: "Recorrer las misiones" }
    { group:68, id:17, text: "Haz clic sobre el nombre de un archivo para seleccionarlo" }
    { group:68, id:18, text: "mouse help free" }
    { group:68, id:19, text: "mouse help free" }
    { group:68, id:20, text: "Construir viviendas" }
    { group:68, id:21, text: "Construir carreteras" }
    { group:68, id:22, text: "Despejar tierra" }
    { group:68, id:23, text: "Estructuras agrícolas y alimentarias" }
    { group:68, id:24, text: "Estructuras industriales" }
    { group:68, id:25, text: "Estructuras de almacenamiento y distribución" }
    { group:68, id:26, text: "Estructuras de entretenimiento" }
    { group:68, id:27, text: "Estructuras religiosas" }
    { group:68, id:28, text: "Estructuras educativas" }
    { group:68, id:29, text: "Estructuras sanitarias" }
    { group:68, id:30, text: "Estructuras municipales" }
    { group:68, id:31, text: "Estructuras militares" }
    { group:68, id:32, text: "DESHACER última acción (sólo cuando el icono está activado)" }
    { group:68, id:33, text: "Ver mensajes" }
    { group:68, id:34, text: "Acceder a cualquier punto conflictivo de la ciudad." }
    { group:68, id:35, text: "Repasa tu misión" }
    { group:68, id:36, text: "Haz clic sobre este mapa para desplazarte a las zonas más lejanas de la ciudad" }
    { group:68, id:37, text: "mouse help free" }
    { group:68, id:38, text: "mouse help free" }
    { group:68, id:39, text: "mouse help free" }
    { group:68, id:40, text: "mouse help free" }
    { group:68, id:41, text: "Visita a los supervisores" }
    { group:68, id:42, text: "Ir al mapa del mundo" }
    { group:68, id:43, text: "Repasar la misión" }
    { group:68, id:44, text: "Orientar la visión al norte" }
    { group:68, id:45, text: "Girar la vista en el sentido de las agujas del reloj" }
    { group:68, id:46, text: "Girar la vista en sentido contrario a las agujas del reloj" }
    { group:68, id:47, text: "mouse help free" }
    { group:68, id:48, text: "mouse help free" }
    { group:68, id:49, text: "mouse help free" }
    { group:68, id:50, text: "mouse help free" }
    { group:68, id:51, text: "Cargar, guardar, nueva partida y salir" }
    { group:68, id:52, text: "Opciones de sonido y velocidad" }
    { group:68, id:53, text: "Acceder a la ayuda del juego" }
    { group:68, id:54, text: "Ir directamente a los informes de los supervisores" }
    { group:68, id:55, text: "mouse help free" }
    { group:68, id:56, text: "mouse help free" }
    { group:68, id:57, text: "mouse help free" }
    { group:68, id:58, text: "mouse help free" }
    { group:68, id:59, text: "mouse help free" }
    { group:68, id:60, text: "mouse help free" }
    { group:68, id:61, text: "Fondos actuales de la ciudad" }
    { group:68, id:62, text: "Población actual de la ciudad" }
    { group:68, id:63, text: "Fecha actual" }
    { group:68, id:64, text: "mouse help free" }
    { group:68, id:65, text: "mouse help free" }
    { group:68, id:66, text: "mouse help free" }
    { group:68, id:67, text: "mouse help free" }
    { group:68, id:68, text: "mouse help free" }
    { group:68, id:69, text: "mouse help free" }
    { group:68, id:70, text: "Visita al supervisor comercial" }
    { group:68, id:71, text: "Visita al supervisor de los trabajadores" }
    { group:68, id:72, text: "Visita al supervisor militar" }
    { group:68, id:73, text: "Visita al supervisor político" }
    { group:68, id:74, text: "Visita al supervisor de puntuación" }
    { group:68, id:75, text: "Visita al supervisor comercial" }
    { group:68, id:76, text: "Visita al supervisor de la población" }
    { group:68, id:77, text: "Visita al supervisor de salud pública" }
    { group:68, id:78, text: "Visita al supervisor de educación" }
    { group:68, id:79, text: "Visita al supervisor de entretenimiento" }
    { group:68, id:80, text: "Visita al supervisor de los templos" }
    { group:68, id:81, text: "Visita al supervisor del tesoro" }
    { group:68, id:82, text: "Visita al supervisor jefe" }
    { group:68, id:83, text: "Visita al supervisor de monumentos" }
    { group:68, id:84, text: "Volver a la vista principal de la ciudad" }
    { group:68, id:85, text: "mouse help free" }
    { group:68, id:86, text: "mouse help free" }
    { group:68, id:87, text: "mouse help free" }
    { group:68, id:88, text: "mouse help free" }
    { group:68, id:89, text: "mouse help free" }
    { group:68, id:90, text: "mouse help free" }
    { group:68, id:91, text: "mouse help free" }
    { group:68, id:92, text: "Haz clic aquí para establecer una prioridad para esta categoría laboral." }
    { group:68, id:93, text: "Decretar el salario anual para cada 10 trabajadores" }
    { group:68, id:94, text: "Haz clic aquí para borrar las prioridades de este comando" }
    { group:68, id:95, text: "Haz clic sobre un número para establecer un nivel de prioridad. Las demás prioridades se ajustarán de acuerdo a éste" }
    { group:68, id:96, text: "Haz clic aquí para donar dinero a la ciudad" }
    { group:68, id:97, text: "Haz clic aquí para establecer tu salario personal" }
    { group:68, id:98, text: "Salir de la pantalla de salario" }
    { group:68, id:99, text: "Seleccionar este nivel de salario" }
    { group:68, id:100, text: "Salir de la pantalla de donaciones" }
    { group:68, id:101, text: "Donar a la ciudad este dinero de tus ahorros familiares" }
    { group:68, id:102, text: "Indica la cantidad a donar" }
    { group:68, id:103, text: "Ajustar la cantidad exacta que deseas donar" }
    { group:68, id:104, text: "Haz clic aquí para asesorarte sobre la puntuación de cultura" }
    { group:68, id:105, text: "Haz clic aquí para asesorarte sobre la puntuación de prosperidad" }
    { group:68, id:106, text: "Haz clic aquí para asesorarte sobre la puntuación de monumentos" }
    { group:68, id:107, text: "Haz clic aquí para asesorarte sobre la puntuación de imperio" }
    { group:68, id:108, text: "Mostrar los precios de importación y exportación de todos los artículos" }
    { group:68, id:109, text: "Haz clic aquí para ver la situación industrial" }
    { group:68, id:110, text: "Establecer la cantidad del producto que deseas conservar antes de exportarlo" }
    { group:68, id:111, text: "Activar o desactivar esta producción en toda la ciudad" }
    { group:68, id:112, text: "Modificar el estado comercial de este objeto" }
    { group:68, id:113, text: "Seleccionar este gráfico" }
    { group:68, id:114, text: "Información sobre festivales" }
    { group:68, id:115, text: "Organizar un festival en honor a este dios" }
    { group:68, id:116, text: "No organizar festivales" }
    { group:68, id:117, text: "Dedicar un festival a Osiris" }
    { group:68, id:118, text: "Dedicar un festival a Ra" }
    { group:68, id:119, text: "Dedicar un festival a Ptah" }
    { group:68, id:120, text: "Dedicar un festival a Seth" }
    { group:68, id:121, text: "Dedicar un festival a Bastet" }
    { group:68, id:122, text: "Modificar el porcentaje de impuestos de la ciudad" }
    { group:68, id:123, text: "Haz clic aquí para hablar con esta persona" }
    { group:68, id:124, text: "Información detallada sobre esta casa" }
    { group:68, id:125, text: "Recorrer los mensajes almacenados" }
    { group:68, id:126, text: "Último mensaje leído. @L Haz clic izquierdo sobre el mensaje para leerlo. @L Haz clic derecho para borrarlo" }
    { group:68, id:127, text: "Mensaje no leído. @L Haz clic izquierdo sobre el mensaje para leerlo. @L Haz clic derecho para borrarlo" }
    { group:68, id:128, text: "Regresar a la última pantalla de ayuda" }
    { group:68, id:129, text: "Salir de la ayuda de Faraón" }
    { group:68, id:130, text: "Recorrer la ayuda de este tema" }
    { group:68, id:131, text: "Borrar este mensaje" }
    { group:68, id:132, text: "Haz clic aquí para ir a este punto conflictivo" }
    { group:68, id:133, text: "Enviar regalo para Egipto" }
    { group:68, id:134, text: "Haz clic aquí para modificar la formación de la compañía" }
    { group:68, id:135, text: "Desempleo" }
    { group:68, id:136, text: "Puntuación de cultura" }
    { group:68, id:137, text: "Puntuación de prosperidad" }
    { group:68, id:138, text: "Puntuación de monumentos" }
    { group:68, id:139, text: "Puntuación de imperio" }
    { group:68, id:140, text: "Haz clic aquí para dar órdenes a los buques de transporte" }
    { group:68, id:141, text: "Haz clic aquí para dar órdenes a los buques de guerra" }
    { group:68, id:142, text: "Impuestos" }
    { group:68, id:143, text: "Ver el estado del ejército" }
    { group:68, id:144, text: "Ver el estado de la armada" }
    { group:68, id:145, text: "Ir a mapa del mundo" }
    { group:68, id:146, text: "Establecer los criterios de la misión" }
    { group:68, id:147, text: "Allanar tierra" }
    { group:68, id:148, text: "Árboles" }
    { group:68, id:149, text: "Agua y pantanos" }
    { group:68, id:150, text: "Pradera" }
    { group:68, id:151, text: "Carretera" }
    { group:68, id:152, text: "Rocas y dunas" }
    { group:68, id:153, text: "Puntos de río" }
    { group:68, id:154, text: "Puntos de invasión" }
    { group:68, id:155, text: "Puntos de gente" }
    { group:68, id:156, text: "Puntos de animales" }
    { group:68, id:157, text: "Pinceles" }
    { group:68, id:158, text: "Añadir ciudad, región o gráfico" }
    { group:68, id:159, text: "Editar ciudad, región o gráfico" }
    { group:68, id:160, text: "Borrar ciudad, región o gráfico" }
    { group:68, id:161, text: "Ver menú principal" }
    { group:68, id:162, text: "Añadir ruta comercial o ruta de invasión" }
    { group:68, id:163, text: "Editar ruta comercial o ruta de invasión" }
    { group:68, id:164, text: "Restablecer el mapa predeterminado" }
    { group:68, id:165, text: "Volver a la vista de la región" }
    { group:68, id:166, text: "Modificar los precios de las importaciones y las exportaciones" }
    { group:68, id:167, text: "Modificar el rango, la financiación, la fecha de inicio y el faraón actual" }
    { group:68, id:168, text: "Acceder a las opciones de clima" }
    { group:68, id:169, text: "Planear eventos" }
    { group:68, id:170, text: "Seleccionar un enemigo" }
    { group:68, id:171, text: "Escoger dioses" }
    { group:68, id:172, text: "Establecer los edificios disponibles" }
    { group:68, id:173, text: "Establecer los requisitos de puntuación y seleccionar monumentos" }
    { group:68, id:174, text: "Decidir la duración y la calidad de la riada" }
    { group:68, id:175, text: "Rotar la vista" }
    { group:68, id:176, text: "Cambiar el gráfico" }
    { group:68, id:177, text: "Clases mortales" }
    { group:68, id:178, text: "Época de monumentos" }
    { group:69, id:0, text: "necesarios)" }
    { group:69, id:1, text: "Eficiencia" }
    { group:69, id:2, text: "Sin riesgo de derrumbamiento" }
    { group:69, id:3, text: "Riesgo de derrumbamiento muy bajo" }
    { group:69, id:4, text: "Riesgo de derrumbamiento bajo" }
    { group:69, id:5, text: "Riesgo de derrumbamiento mediano" }
    { group:69, id:6, text: "Riesgo de derrumbamiento alto" }
    { group:69, id:7, text: "Riesgo de derrumbamiento muy alto" }
    { group:69, id:8, text: "Derrumbamiento inminente" }
    { group:69, id:9, text: "Sin riesgo de incendio" }
    { group:69, id:10, text: "Riesgo de incendio muy bajo" }
    { group:69, id:11, text: "Riesgo de incendio bajo" }
    { group:69, id:12, text: "Riesgo de incendio mediano" }
    { group:69, id:13, text: "Riesgo de incendio alto" }
    { group:69, id:14, text: "Riesgo de incendio muy alto" }
    { group:69, id:15, text: "Riesgo de incendio extremo" }
    { group:69, id:16, text: "¡No hay gente en la ciudad!" }
    { group:69, id:17, text: "No viven trabajadores cerca." }
    { group:69, id:18, text: "El supervisor podría cambiar la mano de obra" }
    { group:69, id:19, text: "El supervisor podría cambiar la mano de obra" }
    { group:69, id:20, text: "AVISO: Acceso deficiente a la mano de obra." }
    { group:69, id:21, text: "Apenas funciona. Destina más trabajadores a nuestro sector." }
    { group:69, id:22, text: "Funcionamiento pobre. Asigna más trabajadores a nuestro sector." }
    { group:69, id:23, text: "Buen funcionamiento, pero debería destinarse más trabajadores a nuestro sector." }
    { group:69, id:24, text: "Funcionando a capacidad reducida. Apenas llega personal nuevo." }
    { group:69, id:25, text: "AVISO: Este edificio debe estar cerca de una carretera" }
    { group:69, id:26, text: "Con poco personal. Puede despachar bienes, pero no recibirlos." }
    { group:69, id:27, text: "Personal escasísimo. Ni se reciben ni se despachan bienes." }
    { group:70, id:0, text: "No hay gente en esta localidad." }
    { group:70, id:1, text: "Gratis" }
    { group:70, id:2, text: "Gratis" }
    { group:70, id:3, text: "Gratis" }
    { group:70, id:4, text: "Gratis" }
    { group:70, id:5, text: "Gratis" }
    { group:70, id:6, text: "Gratis" }
    { group:70, id:7, text: "Gratis" }
    { group:70, id:8, text: "Gratis" }
    { group:70, id:9, text: "Gratis" }
    { group:70, id:10, text: "Nada" }
    { group:70, id:11, text: "Árboles y bosques" }
    { group:70, id:12, text: "Rocas" }
    { group:70, id:13, text: "Agua" }
    { group:70, id:14, text: "Árboles" }
    { group:70, id:15, text: "Grietas en la tierra" }
    { group:70, id:16, text: "Carretera" }
    { group:70, id:17, text: "Acequia de riego" }
    { group:70, id:18, text: "Escombros de edificios destruidos" }
    { group:70, id:19, text: "Muralla" }
    { group:70, id:20, text: "Tierra vacía" }
    { group:70, id:21, text: "Puente" }
    { group:70, id:22, text: "Jardines" }
    { group:70, id:23, text: "Plaza" }
    { group:70, id:24, text: "Para la capital" }
    { group:70, id:25, text: "Para el imperio" }
    { group:70, id:26, text: "Roca con minerales" }
    { group:70, id:27, text: "Roca normal" }
    { group:70, id:28, text: "Roca especial" }
    { group:70, id:29, text: "Pradera" }
    { group:70, id:30, text: "Pradera sumergida" }
    { group:70, id:31, text: "Terreno pantanoso" }
    { group:70, id:32, text: "Dunas" }
    { group:70, id:33, text: "Muralla de ladrillo" }
    { group:70, id:34, text: "Muralla" }
    { group:70, id:35, text: "Pradera" }
    { group:70, id:36, text: "Precipicios" }
    { group:70, id:37, text: "Los árboles son infranqueables, pero se pueden talar. Las serrerías deberían estar cerca de los árboles. Con el tiempo, los árboles se regeneran. (Para seleccionar un edificio, haz clic derecho sobre sus cimientos)." }
    { group:70, id:38, text: "Las rocas son infranqueables y no se pueden retirar. Si tienes suerte puedes hacer una cantera de caliza, arenisca o granito, aunque también podrían ser rocas normales. Consulta tus recursos para descubrirlo." }
    { group:70, id:39, text: "Sólo los barcos viajan por agua, pero los transbordadores y puentes permiten a la gente cruzar a algunas zonas. Los muelles facilitan el comercio con el imperio. Los pozos de arcilla deben estar junto al agua" }
    { group:70, id:40, text: "Terreno infranqueable que puede despejarse para permitir la expansión de la ciudad. Las serrerías tienen que estar cerca de los árboles para talar madera." }
    { group:70, id:41, text: "Estas grietas son el resultado de terremotos. No pueden cruzarse ni rellenarse, y a la gente no le gusta vivir cerca de ellas." }
    { group:70, id:42, text: "Las carreteras son fundamentales para el buen funcionamiento de la ciudad, cuyos habitantes solamente saldrán de sus casas para internarse en ellas." }
    { group:70, id:43, text: "Las acequias de riego mejoran la fertilidad de las granjas situadas como mucho a dos espacios." }
    { group:70, id:44, text: "Estos escombros de edificios antiguos rebajan el atractivo de la tierra en sus alrededores." }
    { group:70, id:45, text: "Las murallas protegen a los indefensos ciudadanos de los invasores. Sólo pueden resistir un cierto número de golpes de ariete; las murallas más gruesas resisten más." }
    { group:70, id:46, text: "En esta tierra se puede edificar. Los cazadores y los soldados, amigos o enemigos, pueden cruzarla libremente." }
    { group:70, id:47, text: "Este puente comunica nuestra ciudad con nuevas tierras, pero también permite a los depredadores e invasores cruzar el agua." }
    { group:70, id:48, text: "Los jardines mejoran el entorno de la zona." }
    { group:70, id:49, text: "¡La gente prefiere las plazas!" }
    { group:70, id:50, text: "Esta carretera nos conecta con el resto de Egipto y debe estar abierta para que los emigrantes y los comerciantes puedan venir a nuestra ciudad" }
    { group:70, id:51, text: "Ésta es la carretera que lleva a los más lejanos lugares del imperio. Es una vía real, y como tal, se debe mantener en toda ella la libertad de paso." }
    { group:70, id:52, text: "Esta roca contiene minerales. Aquí puedes extraer oro o cobre, según el metal disponible." }
    { group:70, id:53, text: "Esto es roca normal. Según los recursos de la ciudad, tal vez puedas extraer de aquí rocas para la construcción o incluso piedras preciosas." }
    { group:70, id:54, text: "This is Special rock.  Blah blah blah... (this text should not appear anywhere)" }
    { group:70, id:55, text: "Esta zona ofrece tierra muy fértil, ahora que el río ha vuelto a su cauce." }
    { group:70, id:56, text: "Esta zona ofrecerá tierra muy fértil una vez que el río vuelva a su cauce." }
    { group:70, id:57, text: "Las zonas pantanosas son demasiado húmedas para la edificación, pero los ciudadanos pueden atravesarlas si tienen precaución. Las cañas crecen aquí, pero ¡cuidado con los cocodrilos!" }
    { group:70, id:58, text: "Las arenas movedizas de esta zona son demasiado inestables para la edificación, pero los ciudadanos las pueden cruzar con cuidado." }
    { group:70, id:59, text: "Esta muralla es de ladrillo. Contiene a los invasores durante más tiempo que una muralla de barro, pero no puede sustituir a una compañía de soldados entrenados." }
    { group:70, id:60, text: "Ésta es una sencilla muralla de barro. Detendrá a los invasores durante  cierto tiempo, pero no deberías considerarla una defensa fuerte." }
    { group:70, id:61, text: "Esta tierra permite cultivar cualquier verdura. Cuanto más exuberantes son las flores, más fértil es la tierra." }
    { group:70, id:62, text: "Estos precipicios son ideales para construir ciertos monumentos. No se puede caminar sobre este abrupto terreno, ni se pueden extraer minerales." }
    { group:71, id:0, text: "Quiosco de música" }
    { group:71, id:1, text: "La gente viene aquí a ver malabarismos y escuchar música." }
    { group:71, id:2, text: "En esta plaza nunca hay espectáculos. Necesita malabaristas y músicos." }
    { group:71, id:3, text: "Esta plaza ofrece a su comunidad emocionantes juegos malabares y música." }
    { group:71, id:4, text: "Esta plaza ofrece música para el entretenimiento de la comunidad local. Busca malabaristas para montar unos cuantos espectáculos." }
    { group:71, id:5, text: "Esta plaza ofrece malabarismos. A los espectadores les gustaría más si tuviera músicos." }
    { group:71, id:6, text: "Esta plaza está muerta. No tiene empleados y no proporciona ningún servicio de ocio a la comunidad local." }
    { group:71, id:7, text: "No hay espectáculos musicales en la actualidad" }
    { group:71, id:8, text: "Los músicos tocarán por otros" }
    { group:71, id:9, text: "No hay juegos malabares en la actualidad" }
    { group:71, id:10, text: "Los malabaristas actuarán por otros" }
    { group:72, id:0, text: "Quiosco" }
    { group:72, id:1, text: "Los ciudadanos disfrutan de los malabares y otras diversiones." }
    { group:72, id:2, text: "Esta plaza nunca ofrece espectáculos. Necesita malabaristas de verdad para que ofrezcan entretenimiento." }
    { group:72, id:3, text: "Actualmente, esta plaza ofrece espectáculos de malabaristas, que normalmente consiguen una buena audiencia." }
    { group:72, id:4, text: "El viento es lo único que se mueve en esta plaza. No tiene trabajadores y no ofrece espectáculos para la gente." }
    { group:72, id:5, text: "En la actualidad no hay espectáculos de malabarismo" }
    { group:72, id:6, text: "El espectáculo actual se representa por otros" }
    { group:72, id:7, text: "Presentación de: \"Juegos malabares del gran Mefistofeles\", por Mefistófeles" }
    { group:72, id:8, text: "Presentación de: \"Las arenas del tiempo\", por Ironrodhotep" }
    { group:72, id:9, text: "Presentación de: \"Lágrimas de cocodrilo\", por Waseth" }
    { group:72, id:10, text: "Presentación de: \"La pirámide de 10.000 debens\", por Desenseth" }
    { group:72, id:11, text: "Presentación de: \"Rock del cocodrilo\", por El-Tonyón" }
    { group:73, id:0, text: "Local de senet" }
    { group:73, id:1, text: "Los juegos de habilidad y azar añaden interés a la vida de todo el mundo" }
    { group:73, id:2, text: "Este local de senet tiene jugadores, pero un buen suministro de cerveza animaría las partidas." }
    { group:73, id:3, text: "Este local de senet celebra juegos constantemente, para deleite de la población local." }
    { group:73, id:4, text: "Nadie acude a este local de senet. Sin trabajadores, la comunidad local no se siente atraída." }
    { group:73, id:5, text: "No hay juegos en marcha" }
    { group:73, id:6, text: "Los juegos actuales durarán" }
    { group:73, id:7, text: "Cerveza almacenada," }
    { group:74, id:0, text: "Pabellón" }
    { group:74, id:1, text: "Baile, música, malabarismos... ¿Qué más podría desear un ciudadano?" }
    { group:74, id:2, text: "Esta plaza no ofrece espectáculos. Necesita bailarines, músicos y malabaristas para atraer a la multitud." }
    { group:74, id:3, text: "Esta plaza ofrece una danza encantadora, músicos mágicos y alegres malabaristas que deleitan a la comunidad local." }
    { group:74, id:4, text: "Esta plaza ofrece bailarines y músicos a los lugareños. Los malabaristas añadirían más variedad a los espectáculos." }
    { group:74, id:5, text: "Esta plaza ofrece bailarines y malabaristas. Necesita músicos para ofrecer un total entretenimiento." }
    { group:74, id:6, text: "Esta plaza ofrece músicos y malabaristas, pero los músicos necesitan bailarines para completar el espectáculo." }
    { group:74, id:7, text: "Esta plaza ofrece malabaristas, pero necesita músicos y bailarines para llenar los escenarios vacíos." }
    { group:74, id:8, text: "Esta plaza cuenta con músicos, pero no tiene malabaristas ni bailarines." }
    { group:74, id:9, text: "Esta plaza cuenta con bailarines, pero no tiene malabaristas ni músicos." }
    { group:74, id:10, text: "Esta plaza está cerrada. No tiene empleados y es inútil como zona de ocio." }
    { group:74, id:11, text: "No hay espectáculos de malabarismo en la actualidad" }
    { group:74, id:12, text: "Los malabarismos continuarán por otros" }
    { group:74, id:13, text: "En la actualidad no hay actuaciones musicales" }
    { group:74, id:14, text: "La música continuará por otros" }
    { group:74, id:15, text: "En la actualidad no hay danza" }
    { group:74, id:16, text: "La danza se representa por otros" }
    { group:75, id:0, text: "Conservatorio" }
    { group:75, id:1, text: "Los egipcios siempre están deseando oír las interpretaciones de los nuevos músicos." }
    { group:75, id:2, text: "Nos complace anunciar que, con todos los puestos de trabajo cubiertos,  estamos instruyendo a cuatro nuevos músicos cada mes." }
    { group:75, id:3, text: "Tenemos poco personal, de modo que como mucho podemos instruir a dos nuevos músicos cada mes." }
    { group:75, id:4, text: "Tenemos la mitad del personal necesario, de modo que como mucho podremos instruir a un músico el próximo mes." }
    { group:75, id:5, text: "Tenemos una gran necesidad de empleados, pero nos esforzaremos en instruir a un músico en dos meses." }
    { group:75, id:6, text: "El único empleado soy yo. No se puede esperar que trabaje en estas condiciones. En el mejor de los casos, puedo instruir a un músico cada tres meses." }
    { group:75, id:7, text: "Esta escuela no puede instruir a nuevos músicos, porque no tiene personal." }
    { group:76, id:0, text: "Escuela de danza" }
    { group:76, id:1, text: "Los bailarines deleitan al público con gráciles y tentadores movimientos." }
    { group:76, id:2, text: "Nos complace anunciar que, con todos los puestos de trabajo cubiertos, podemos instruir a cuatro nuevos bailarines cada mes." }
    { group:76, id:3, text: "Tenemos poco personal, de modo que sólo podemos instruir a dos nuevos bailarines cada mes." }
    { group:76, id:4, text: "Tenemos la mitad del personal necesario, de modo que como mucho podremos instruir a una bailarina el próximo mes." }
    { group:76, id:5, text: "Tenemos una gran necesidad de empleados y apenas podremos instruir a una bailarina en los próximos dos meses." }
    { group:76, id:6, text: "El único empleado soy yo. No se puede esperar que trabaje en estas condiciones. En el mejor de los casos, puedo instruir a una bailarina cada tres meses." }
    { group:76, id:7, text: "Esta escuela no puede instruir a nuevos bailarines, porque no tiene personal." }
    { group:77, id:0, text: "Escuela de juegos malabares" }
    { group:77, id:1, text: "Siempre se piden nuevos malabaristas que realicen nuevos trucos." }
    { group:77, id:2, text: "Nos complace anunciar que, con todos los puestos de trabajo cubiertos, estamos instruyendo a cuatro nuevos malabaristas cada mes." }
    { group:77, id:3, text: "Tenemos poco personal, de modo que como mucho podemos instruir a dos nuevos malabaristas cada mes." }
    { group:77, id:4, text: "Tenemos la mitad del personal necesario, de modo que como mucho podremos instruir a un malabarista el próximo mes." }
    { group:77, id:5, text: "Necesitamos empleados con urgencia. Nos esforzaremos por instruir a un malabarista en los próximos dos meses." }
    { group:77, id:6, text: "El único empleado soy yo. No se puede esperar que trabaje en estas condiciones. En el mejor de los casos, puedo instruir a un malabarista cada tres meses." }
    { group:77, id:7, text: "Esta escuela está vacía. Sin maestros, no se entrenarán nuevos malabaristas." }
    { group:78, id:0, text: "Instructores de senet" }
    { group:78, id:1, text: "Los grandes estrategas que trabajan aquí preparan a los expertos maestros de senet, para que visiten los más populares locales de senet de la ciudad." }
    { group:78, id:2, text: "Nos complace anunciar que, con todos los puestos de trabajo cubiertos, podemos instruir a cuatro maestros de senet cada mes." }
    { group:78, id:3, text: "Tenemos poco personal, de modo que como mucho podemos preparar a dos nuevos maestros de senet cada mes." }
    { group:78, id:4, text: "Tenemos la mitad del personal necesario, de modo que sólo podremos preparar a un maestro de senet en el próximo mes." }
    { group:78, id:5, text: "Tenemos una gran necesidad de empleados, pero nos esforzaremos por instruir a un nuevo maestro de senet en dos meses." }
    { group:78, id:6, text: "El único empleado soy yo. Nos se puede esperar que trabaje en estas condiciones. En el mejor de los casos, puedo preparar a un maestro de senet en tres meses." }
    { group:78, id:7, text: "Sin maestros, no se puede preparar a los nuevos maestros de senet. Por este motivo, los locales de senet de la ciudad se pueden ver afectados." }
    { group:79, id:0, text: "Jardines" }
    { group:79, id:1, text: "Este lugar permite escapar del ruido, el calor y la suciedad de la ciudad ofreciendo a los ciudadanos la frescura de un verde oasis. Todo el mundo quiere un jardín junto a su casa." }
    { group:80, id:0, text: "Estatua" }
    { group:80, id:1, text: "Los monumentos a los dioses y a los antiguos faraones realzan el prestigio de los barrios. La gente está orgullosa de tener estatuas cerca... y cuanto más grandes, mejor." }
    { group:80, id:2, text: "Arco del Triunfo" }
    { group:80, id:3, text: "Esta magnífica construcción conmemora las históricas victorias de Egipto. No hay nada más prestigioso." }
    { group:81, id:0, text: "Botica" }
    { group:81, id:1, text: "Los boticarios mejoran la salud de los ciudadanos, ya que realizan visitas a domicilio en los barrios de su ruta. Las zonas más ricas quieren un boticario." }
    { group:81, id:2, text: "Esta botica no está en funcionamiento y no es de utilidad para la comunidad local." }
    { group:81, id:3, text: "Esta botica está en funcionamiento y proporciona pociones y ungüentos a la comunidad." }
    { group:82, id:0, text: "Mortuorio" }
    { group:82, id:1, text: "Aunque nadie quiere vivir en sus inmediaciones, los mortuorios salvan vidas cuando hay enfermedades. La ciudad debe poder embalsamar a todos sus muertos." }
    { group:82, id:2, text: "Este mortuorio no está en funcionamiento y no es de utilidad para la comunidad local." }
    { group:82, id:3, text: "Este mortuorio está en funcionamiento y momifica a los fallecidos rápida y profesionalmente." }
    { group:82, id:4, text: "Sin lino no podemos enterrar a los muertos" }
    { group:83, id:0, text: "Médico" }
    { group:83, id:1, text: "Una granada al día, de médico te ahorraría. Los médicos mejoran la salud." }
    { group:83, id:2, text: "Este médico no trabaja." }
    { group:83, id:3, text: "Este médico desempeña su trabajo y la comunidad local goza de buena salud" }
    { group:84, id:0, text: "Dentista" }
    { group:84, id:1, text: "Hay arena en todas partes, incluso en la comida. La constante abrasión proporciona mucho trabajo a los dentistas egipcios." }
    { group:84, id:2, text: "Este dentista no trabaja y no es de utilidad para la comunidad local." }
    { group:84, id:3, text: "Este dentista desempeña su trabajo y la población muestra orgullosa el brillo de sus dientes." }
    { group:85, id:0, text: "Escuela de escribas" }
    { group:85, id:1, text: "Los niños de las familias ricas deben acudir a las escuelas del barrio para aprender a leer y escribir, si quieren alcanzar la categoría de sus padres." }
    { group:85, id:2, text: "Este colegio no está en funcionamiento, y no sirve a la comunidad local." }
    { group:85, id:3, text: "Este colegio está en funcionamiento. Los niños son cultos y están instruidos." }
    { group:86, id:0, text: "Izquierda" }
    { group:86, id:1, text: "Arriba" }
    { group:86, id:2, text: "Derecha" }
    { group:86, id:3, text: "Abajo" }
    { group:87, id:0, text: "Biblioteca" }
    { group:87, id:1, text: "Las obras literarias de todo el imperio están almacenadas aquí. Los sabios insisten en que las bibliotecas son decisivas para una ciudad importante." }
    { group:87, id:2, text: "Los fondos de esta biblioteca están vacíos y no sirven a la comunidad." }
    { group:87, id:3, text: "Esta biblioteca está en funcionamiento. Sus estanterías rebosan sabiduría." }
    { group:88, id:0, text: "Comisaría" }
    { group:88, id:1, text: "Las comisarías mandan policías a la ciudad para mantener el orden. El orden de la ciudad está asegurado cuando los policías patrullan la ciudad de forma constante." }
    { group:88, id:2, text: "Nuestro policía está patrullando." }
    { group:88, id:3, text: "Nuestro policía se está preparando para cumplir con su deber." }
    { group:88, id:4, text: "En la actualidad, nuestro plan de servicios está completo. Nuestros policías buscan continuamente señales de delitos." }
    { group:88, id:5, text: "Necesitamos unos cuantos policías más. Tenemos huecos de un día o dos en nuestra zona de cobertura." }
    { group:88, id:6, text: "Tenemos poco personal, y tenemos huecos peligrosos de hasta una semana en nuestra agenda de servicios." }
    { group:88, id:7, text: "Tenemos pocos hombres. Los delincuentes podrían actuar sin control durante dos semanas seguidas." }
    { group:88, id:8, text: "Sólo trabajamos con una persona. A veces transcurre un mes antes de que se envíe a un policía a patrullar." }
    { group:88, id:9, text: "Sin personal, esto se ha convertido en caldo de cultivo del vandalismo." }
    { group:88, id:10, text: "robos este año." }
    { group:88, id:11, text: "oro robado este año." }
    { group:89, id:0, text: "Fuerte" }
    { group:89, id:1, text: "Seth ha maldecido este fuerte y pasará algún tiempo antes de que los soldados osen volver." }
    { group:89, id:2, text: "Los fuertes recurren al reclutador de la ciudad para conseguir soldados. La creación de una academia militar proporcionaría unas tropas mejor preparadas." }
    { group:90, id:0, text: "Portón" }
    { group:90, id:1, text: "Las murallas necesitan un portón para que los emigrantes y comerciantes puedan ir y venir con libertad." }
    { group:91, id:0, text: "Torre" }
    { group:91, id:1, text: "Construye torres en las murallas a intervalos regulares, o por lo menos en las zonas vulnerables. Las torres reciben vigías, enviados por el reclutador, cuando están conectadas a las carreteras. Los vigías de las torres lanzan jabalinas a los invasores y patrullan las murallas que sean suficientemente gruesas." }
    { group:91, id:2, text: "Sin trabajadores no podemos apostar guardias en las torres ni contratar gente para patrullar las murallas." }
    { group:91, id:3, text: "Nuestros hombres están alerta y preparados para repeler cualquier ataque." }
    { group:91, id:4, text: "Tenemos personal de mantenimiento, pero necesitamos vigías enviados por un reclutador." }
    { group:92, id:0, text: "Templo de Osiris (agric.)" }
    { group:92, id:1, text: "Osiris fertiliza la tierra y hace que la cosecha crezca. Manténlo contento o prepárate para pasar hambre." }
    { group:93, id:0, text: "Templo de Ra (el imperio)" }
    { group:93, id:1, text: "Los mercaderes conocen muy bien el valor de tener contento a Ra. El comercio es más seguro y más beneficioso con la bendición de Ra, y tu ciudad se tiene en mayor consideración." }
    { group:94, id:0, text: "Templo de Ptah (artesanía)" }
    { group:94, id:1, text: "Los trabajadores y los artesanos veneran a Ptah para que facilite su trabajo. Cuando Ptah está enfadado, ninguna industria se libra de la catástrofe." }
    { group:95, id:0, text: "Templo de Seth (destrucción)" }
    { group:95, id:1, text: "Seth vela por los soldados y les infunde valor en el combate. Ningún hombre se atreve a luchar sin la bendición de Seth." }
    { group:96, id:0, text: "Templo de Bastet (Hogar)" }
    { group:96, id:1, text: "Cuando Bastet no se siente complacida, nadie está a salvo dentro de casa. Hay quien culpa a Bastet de las enfermedades." }
    { group:97, id:0, text: "Bazar" }
    { group:97, id:1, text: "Nuestros bazares ponen al alcance de todos los ciudadanos con dinero las riquezas del reino. Todas las casas necesitan tener acceso al bazar, aunque nadie quiere tener uno al lado." }
    { group:97, id:2, text: "Este bazar no está en funcionamiento y no tiene suministros para la comunidad local." }
    { group:97, id:3, text: "Este bazar está en funcionamiento." }
    { group:97, id:4, text: "Este bazar dispone de comerciantes, pero en la actualidad están buscando alimentos y artículos para vender." }
    { group:97, id:5, text: "Suministros de alimentos para" }
    { group:97, id:6, text: "Órdenes especiales" }
    { group:97, id:7, text: "Instrucciones del bazar" }
    { group:97, id:8, text: "Comprar" }
    { group:97, id:9, text: "No comprar" }
    { group:97, id:10, text: "El comerciante del bazar espera alimentos." }
    { group:97, id:11, text: "El comerciante está distribuyendo artículos." }
    { group:97, id:12, text: "El comerciante vuelve a por más artículos" }
    { group:98, id:0, text: "Granero" }
    { group:98, id:1, text: "Los graneros llenos son vitales para mantener lleno el estómago de la gente y para atraer a nuevos ciudadanos. En un granero se puede almacenar todo tipo de alimentos." }
    { group:98, id:2, text: "Almacenando" }
    { group:98, id:3, text: "Sitio para" }
    { group:98, id:4, text: "Este granero no es necesario. Egipto provee a nuestra ciudad de todos los cereales que necesita. Cualquier alimento que producimos se deposita en los almacenes que tengan sitio." }
    { group:98, id:5, text: "Órdenes especiales" }
    { group:98, id:6, text: "Instrucciones del granero" }
    { group:98, id:7, text: "Vaciar granero" }
    { group:98, id:8, text: "Detener vaciado de granero" }
    { group:98, id:9, text: "Intentando enviar comida a otra parte" }
    { group:99, id:0, text: "Almacén" }
    { group:99, id:1, text: "Se necesitan almacenes para todo tipo de artículos. Las caravanas comercian en los almacenes, los muelles canjean las exportaciones por las importaciones en los almacenes cercanos y los bazares se abastecen en ellos." }
    { group:99, id:2, text: "Órdenes especiales" }
    { group:99, id:3, text: "Instrucciones del almacén" }
    { group:99, id:4, text: "EMPEZAR a vaciar el almacén" }
    { group:99, id:5, text: "PARAR de vaciar el almacén" }
    { group:99, id:6, text: "Intentando enviar bienes a otra parte" }
    { group:99, id:7, text: "No aceptar nada" }
    { group:99, id:8, text: "No aceptar" }
    { group:99, id:9, text: "Obtener bienes" }
    { group:99, id:10, text: "Obtener alimentos" }
    { group:99, id:11, text: "Centro de comercio" }
    { group:99, id:12, text: "Convertir en centro de comercio" }
    { group:99, id:13, text: "AVISO. Este almacén está totalmente lleno. No puede aceptar más mercancía." }
    { group:99, id:14, text: "AVISO: Este almacén está casi lleno. No aceptará nuevas mercancías, sólo artículos de las clases existentes." }
    { group:99, id:15, text: "Nuestro repartidor espera nuevas instrucciones." }
    { group:99, id:16, text: "Nuestro carro lleva bienes a otras partes." }
    { group:99, id:17, text: "Nuestro carro vuelve de hacer un reparto." }
    { group:99, id:18, text: "Aceptar" }
    { group:99, id:19, text: "Obtener" }
    { group:99, id:20, text: "Vaciar alimentos" }
    { group:99, id:21, text: "Vaciar" }
    { group:99, id:22, text: "Este almacén está vacío." }
    { group:99, id:23, text: "bloque de" }
    { group:99, id:24, text: "bloques de" }
    { group:99, id:25, text: "1/4" }
    { group:99, id:26, text: "1/2" }
    { group:99, id:27, text: "3/4" }
    { group:99, id:28, text: "todo" }
    { group:99, id:29, text: "Almacén" }
    { group:99, id:30, text: "Granero" }
    { group:99, id:31, text: "máximo" }
    { group:99, id:32, text: "Llenar" }
    { group:99, id:33, text: "Nuestro repartidor ha ido a buscar artículos" }
    { group:100, id:0, text: "Astillero" }
    { group:100, id:1, text: "Con suficientes trabajadores, el astillero construye toda clase de barcos para las dársenas de la ciudad. Los barcos de guerra y transporte necesitan 100 tablones de madera." }
    { group:100, id:2, text: "La producción está al:" }
    { group:100, id:3, text: "." }
    { group:100, id:4, text: "En la actualidad no hay dársenas que soliciten barcos." }
    { group:100, id:5, text: "Estamos construyendo un barco para una dársena de la ciudad." }
    { group:100, id:6, text: "Estamos reparando un barco." }
    { group:100, id:7, text: "Madera almacenada," }
    { group:100, id:8, text: "Necesitamos madera para reparar y construir barcos." }
    { group:100, id:9, text: "Carecemos de madera para completar un barco, para una dársena de la ciudad." }
    { group:100, id:10, text: "Tenemos barcos en espera de reparación, pero no tenemos la madera necesaria." }
    { group:101, id:0, text: "Muelle" }
    { group:101, id:1, text: "Los barcos comerciales de todo el mundo amarran aquí para descargar las importaciones y cargar las exportaciones. No es posible comerciar con el extranjero sin muelles." }
    { group:101, id:2, text: "Al no tener estibadores en plantilla no podemos ofrecer servicios al barco atracado." }
    { group:101, id:3, text: "Ofrecemos servicio al barco atracado. Sin embargo, con tan pocos trabajadores, puede ser que tardemos mucho tiempo." }
    { group:101, id:4, text: "Ofrecemos servicio al barco atracado, aunque tardaremos un poco más que si tuviésemos el personal al completo." }
    { group:101, id:5, text: "Con tantos trabajadores, podemos dar servicio al barco atracado de manera rápida y eficaz." }
    { group:101, id:6, text: "El barco que atraque aquí no dispondrá de trabajadores para la carga y descarga de mercancías." }
    { group:101, id:7, text: "Debido a el escaso número de estibadores que trabajan aquí, la carga y descarga de los barcos que atraquen en el puerto, llevará mucho tiempo." }
    { group:101, id:8, text: "Tenemos poco personal, por lo que tardaremos más de lo deseado en cargar y descargar la mercancía de los barcos que lleguen." }
    { group:101, id:9, text: "Con tanto personal, los estibadores simplemente esperan a que entre un barco." }
    { group:102, id:0, text: "Dársena pesquera" }
    { group:102, id:1, text: "Los barcos zarpan aquí, desde el astillero, para aceptar tripulación y empezar a pescar en las aguas de la zona. Cada dársena puede mantener un barco de pesca." }
    { group:102, id:2, text: "En la actualidad estamos esperando que un astillero nos construya un barco de pesca." }
    { group:102, id:3, text: "Nuestro barco de pesca ha salido a buscar bancos de peces." }
    { group:102, id:4, text: "Nuestro barco de pesca se encuentra en un banco de peces, cargando pescado." }
    { group:102, id:5, text: "Nuestro barco se dirige ahora a la dársena." }
    { group:102, id:6, text: "Estamos reabasteciendo nuestro barco de pesca para hacer otra salida." }
    { group:102, id:7, text: "Nuestro barco de pesca regresa de los bancos de peces con la mercancía." }
    { group:102, id:8, text: "Nuestros pescadores esperan que alguien descubra bancos de peces en las aguas de esta provincia algún día. No se pueden ganar la vida sin peces." }
    { group:102, id:9, text: "El supervisor comercial ha ordenado la detención de la pesca." }
    { group:102, id:10, text: "¡Nuestro barco de pesca no va a navegar en esas aguas contaminadas!" }
    { group:103, id:0, text: "Palacete" }
    { group:103, id:1, text: "Tu casa es una de las preferidas de la ciudad. Tu palacete te da autoridad para cobrar un sueldo." }
    { group:103, id:2, text: "Debens al mes" }
    { group:103, id:3, text: "Salario del jefe de la aldea de" }
    { group:103, id:4, text: "Salario de noble de la aldea de" }
    { group:103, id:5, text: "Salario de sabio real de" }
    { group:103, id:6, text: "Salario de escriba real de" }
    { group:103, id:7, text: "Salario de juez real de" }
    { group:103, id:8, text: "Salario de mayordomo real de" }
    { group:103, id:9, text: "Salario de gobernador real de" }
    { group:103, id:10, text: "Salario de nomarca real de" }
    { group:103, id:11, text: "Salario de canciller real de" }
    { group:103, id:12, text: "Salario de visir real de" }
    { group:103, id:13, text: "Salario de faraón de" }
    { group:104, id:0, text: "Puesto de arquitecto" }
    { group:104, id:1, text: "Los arquitectos egipcios son los más avanzados jamás conocidos por el mundo. Su vigilancia evita que los edificios se derrumben." }
    { group:104, id:2, text: "Nuestro arquitecto está trabajando duro." }
    { group:104, id:3, text: "Nuestro arquitecto se está preparando para salir." }
    { group:104, id:4, text: "Actualmente no tenemos tiempo libre. Nuestros arquitectos están constantemente fuera, examinando y reparando los edificios más grandes de la ciudad." }
    { group:104, id:5, text: "Faltan un par de días para que nuestros arquitectos saturados de trabajo vuelvan a las calles." }
    { group:104, id:6, text: "Contamos con muy poco personal, por lo que tendremos que esperar una semana antes de volver a disponer de los arquitectos." }
    { group:104, id:7, text: "Estamos tan escasos de personal que entre una ronda de arquitectos y la siguiente pasan dos semanas." }
    { group:104, id:8, text: "Estamos trabajando casi sin personal. Apenas podemos contar con un arquitecto cada mes." }
    { group:104, id:9, text: "Sin arquitectos, el barrio está a merced de las arenas movedizas." }
    { group:105, id:0, text: "Palacio" }
    { group:105, id:1, text: "El palacio se encuentra entre los edificios más deseados de la ciudad y es la piedra angular de la economía de la ciudad. Convierte las pepitas de oro en debens y almacena parte de los fondos de la ciudad." }
    { group:105, id:2, text: "Las arcas contienen" }
    { group:105, id:3, text: "¿Visitar al supervisor de puntuación?" }
    { group:106, id:0, text: "Oficina del recaudador de impuestos" }
    { group:106, id:1, text: "Aunque no son los trabajadores más populares de la ciudad, los recaudadores de impuestos hacen posible nuestro gran imperio y consiguen todos los beneficios que nos llegan." }
    { group:106, id:2, text: "Las arcas contienen" }
    { group:106, id:3, text: "Nuestro recaudador está fuera, inspeccionando las cuentas de los vecinos." }
    { group:106, id:4, text: "Nuestro recaudador se prepara para irse." }
    { group:106, id:5, text: "En la actualidad se trabaja con total eficacia; todos los recaudadores de la ciudad están comprobando que se pagan todos los impuestos." }
    { group:106, id:6, text: "Estamos un poco escasos de personal; habrá que esperar un día o dos para de que los recaudadores de impuestos vuelvan a salir a las calles." }
    { group:106, id:7, text: "Tenemos poco personal y hemos de esperar una semana antes de que los recaudadores vuelvan a sus obligaciones." }
    { group:106, id:8, text: "Tenemos muy poco personal y transcurren dos semanas entre las patrullas de cobro." }
    { group:106, id:9, text: "Con tan poco personal en esta oficina, los ciudadanos pueden evitar el pago de muchos impuestos." }
    { group:106, id:10, text: "Sin recaudadores, este despacho no contribuye en absoluto a engrosar las arcas de la ciudad." }
    { group:106, id:11, text: "Tu ciudad necesita un palacio para recaudar impuestos." }
    { group:106, id:12, text: "Tu ciudad necesita un palacio en funcionamiento para recaudar impuestos." }
    { group:107, id:0, text: "Bomba de agua" }
    { group:107, id:1, text: "Esta bomba de agua puede bombear grandes cantidades de agua, si las acequias de riego están conectadas a las esclusas delanteras o traseras." }
    { group:107, id:2, text: "Esta bomba de agua no está en funcionamiento. Consulta con el supervisor de los trabajadores para asignar más empleados al suministro de agua." }
    { group:107, id:3, text: "Para funcionar, esta bomba de agua necesita estar cerca del agua o estar conectada mediante una acequia de riego a una bomba de agua en funcionamiento." }
    { group:108, id:0, text: "Suministro de agua" }
    { group:108, id:1, text: "Los aguadores sacan el agua limpia de esta deseable fuente y mejoran la salud y la felicidad a medida que la reparten a las casas de su ruta." }
    { group:108, id:2, text: "Nuestro personal está siempre fuera repartiendo el agua limpia entre la población." }
    { group:108, id:3, text: "Nos faltan unos pocos aguadores. Tenemos huecos de un día o dos en nuestra zona de cobertura." }
    { group:108, id:4, text: "Tenemos poco personal y hemos de esperar hasta una semana para continuar con el reparto de agua." }
    { group:108, id:5, text: "Tenemos muy pocos empleados. A veces, no se reparte agua en dos semanas." }
    { group:108, id:6, text: "Estamos trabajando prácticamente sin personal. A menudo, pasa un mes sin que se reparta nada de agua." }
    { group:108, id:7, text: "Sin personal, daría igual que esta instalación fuera un agujero seco en el suelo." }
    { group:109, id:0, text: "Pozo" }
    { group:109, id:1, text: "Los ciudadanos que no tienen acceso al reparto de agua limpia pueden extraerla de los pozos, pero los barrios sin aguadores no son unos sitios muy solicitados para vivir." }
    { group:109, id:2, text: "Este pozo no es necesario, ya que todas las casas a las que sirve reciben agua de un suministro de agua." }
    { group:109, id:3, text: "Este pozo es inservible puesto que no hay casas cerca de él." }
    { group:110, id:0, text: "¿Oráculo? ¿Poner aquí el santuario?" }
    { group:110, id:1, text: "Este santuario hace que las casas cercanas sean sitios deseados para vivir y además complace a todos los dioses, aunque no da trabajo a  sacerdotes ni proporciona a las casas el acceso a ningún dios en concreto." }
    { group:111, id:0, text: "Ruina en llamas" }
    { group:111, id:1, text: "Los bomberos no pueden llegar a este lugar a tiempo para salvar el edificio. Cuando las llamas se extingan, tan sólo quedarán escombros." }
    { group:112, id:0, text: "Granja de cereales" }
    { group:112, id:1, text: "Los cereales deben guardarse en graneros para alimentar a la gente o en almacenes para su exportación." }
    { group:112, id:2, text: "La producción está al:" }
    { group:112, id:3, text: "." }
    { group:112, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de cereales." }
    { group:112, id:5, text: "Esta granja no tiene empleados. La tierra está estéril." }
    { group:112, id:6, text: "Esta granja tiene todo el personal que necesita. Dada su actual fertilidad, consigue unos beneficios elevados." }
    { group:112, id:7, text: "Esta granja podría ser más productiva si tuviera más trabajadores." }
    { group:112, id:8, text: "El personal de esta granja es insuficiente. Sus trabajadores están tardando mucho en cultivar alimentos aquí." }
    { group:112, id:9, text: "Hay muy pocos granjeros trabajando aquí. Por consiguiente, la producción de cereales es escasa." }
    { group:112, id:10, text: "Con tan pocos granjeros, la producción de trigo está prácticamente detenida." }
    { group:112, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:112, id:12, text: "La tierra es" }
    { group:112, id:13, text: "fértil" }
    { group:112, id:14, text: "La próxima cosecha de cereales es en" }
    { group:113, id:0, text: "Granja de lechugas" }
    { group:113, id:1, text: "La lechuga es importante para que la gente siga una dieta equilibrada, y de ese modo, esté contenta y goce de buena salud." }
    { group:113, id:2, text: "La producción está al:" }
    { group:113, id:3, text: "." }
    { group:113, id:4, text: "El supervisor comercial ha decretado la suspensión del cultivo de lechugas." }
    { group:113, id:5, text: "Esta granja no tiene empleados. No se ha plantado nada." }
    { group:113, id:6, text: "Esta granja tiene todo el personal que necesita. Se cultivan lechugas en abundancia." }
    { group:113, id:7, text: "Esta granja está funcionando por debajo de su capacidad máxima, de modo que la producción de lechugas es escasa." }
    { group:113, id:8, text: "Esta granja tiene poco personal. Por lo tanto, las lechugas tardan más en crecer." }
    { group:113, id:9, text: "Aquí trabajan muy pocos granjeros. El cultivo de alimentos llevará mucho tiempo." }
    { group:113, id:10, text: "Con tan pocos granjeros para mantener la granja, apenas crecerá algo." }
    { group:113, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:113, id:12, text: "La tierra es" }
    { group:113, id:13, text: "fértil" }
    { group:113, id:14, text: "La próxima cosecha de lechugas es en" }
    { group:114, id:0, text: "Granja de granadas" }
    { group:114, id:1, text: "Las granadas ayudan a que la gente siga la dieta equilibrada que necesita. Los graneros almacenan las granadas para el consumo local, y los almacenes guardan los excedentes para la exportación." }
    { group:114, id:2, text: "La producción está al:" }
    { group:114, id:3, text: "." }
    { group:114, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de granadas." }
    { group:114, id:5, text: "Este huerto no tiene empleados. La producción se ha detenido." }
    { group:114, id:6, text: "Este huerto tiene todos los empleados que necesita. Los árboles son resistentes y proporcionan suculentas granadas." }
    { group:114, id:7, text: "Este huerto está funcionando por debajo su capacidad máxima, de modo que la producción de granadas desciende poco a poco." }
    { group:114, id:8, text: "Este huerto no tiene suficientes empleados. Produce granadas más lentamente de lo que podría." }
    { group:114, id:9, text: "En este huerto trabaja muy poca gente. Los cultivos de granadas se retrasarán." }
    { group:114, id:10, text: "Casi sin empleados, este huerto tardará siglos en producir granadas." }
    { group:114, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:114, id:12, text: "La tierra es" }
    { group:114, id:13, text: "fértil" }
    { group:114, id:14, text: "La próxima cosecha de granadas es en" }
    { group:115, id:0, text: "Granja de lino" }
    { group:115, id:1, text: "El lino es la materia prima para fabricar la imprescindible fibra de lino. Los talleres procesan e hilan los tallos para fabricar el hilo, que se utiliza para embalsamar y en la exportación." }
    { group:115, id:2, text: "La producción está al:" }
    { group:115, id:3, text: "." }
    { group:115, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de lino." }
    { group:115, id:5, text: "Esta granja no tiene empleados. Aquí no se puede producir lino." }
    { group:115, id:6, text: "Esta granja tiene todos los empleados que necesita. Los campos están alfombrados con flores de lino azules." }
    { group:115, id:7, text: "Esta granja está funcionando por debajo de su capacidad máxima. La producción de lino sería mejor si hubiera más trabajadores." }
    { group:115, id:8, text: "Esta granja no tiene suficientes empleados. Produce lino más lentamente de lo que podría." }
    { group:115, id:9, text: "En esta granja trabaja muy poca gente. Por consiguiente, la producción de lino es más lenta." }
    { group:115, id:10, text: "Casi sin empleados, la mayor parte de la tierra de esta granja es estéril." }
    { group:115, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:115, id:12, text: "La tierra es" }
    { group:115, id:13, text: "fértil" }
    { group:115, id:14, text: "La próxima cosecha de lino es en" }
    { group:116, id:0, text: "Recolector de caña" }
    { group:116, id:1, text: "Los recolectores de caña se aventuran en los terrenos pantanosos para recolectar papiros, sin los que sería imposible la educación." }
    { group:116, id:2, text: "Cañas almacenadas" }
    { group:116, id:3, text: "." }
    { group:116, id:4, text: "El supervisor comercial ha ordenado suspender la recolección de cañas." }
    { group:116, id:5, text: "Este lugar no tiene empleados para recolectar cañas." }
    { group:116, id:6, text: "Este lugar tiene todos los empleados que necesita. No vamos a dejar un papiro en su sitio." }
    { group:116, id:7, text: "Este lugar funciona por debajo de su potencial, de modo que la recolección de caña es más lenta." }
    { group:116, id:8, text: "Este lugar no tiene suficientes empleados, de modo que la recolección de caña es muy lenta." }
    { group:116, id:9, text: "Aquí trabaja muy poca gente y se recolectan muy pocas cañas." }
    { group:116, id:10, text: "Con tan pocos empleados, casi no se recolectan cañas." }
    { group:116, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:116, id:12, text: "La tierra es" }
    { group:116, id:13, text: "fértil" }
    { group:116, id:14, text: "La próxima cosecha de caña será en" }
    { group:117, id:0, text: "Granja de ganado vacuno" }
    { group:117, id:1, text: "Los ciudadanos bien alimentados quieren incluir carne en su dieta. La carne se puede almacenar en graneros para el consumo local o en almacenes para la exportación." }
    { group:117, id:2, text: "La producción está al:" }
    { group:117, id:3, text: "." }
    { group:117, id:4, text: "El supervisor comercial ha ordenado suspender la cría de ganado vacuno." }
    { group:117, id:5, text: "Esta granja no tiene empleados, y los animales se han escapado o han muerto." }
    { group:117, id:6, text: "Esta granja tiene todos los empleados que necesita. Con paja, puede producir mucha carne." }
    { group:117, id:7, text: "Esta granja tiene que contratar más trabajadores para producir carne de forma eficaz." }
    { group:117, id:8, text: "Esta granja no tiene suficientes empleados. No puede alcanzar su producción posible." }
    { group:117, id:9, text: "En esta granja trabaja muy poca gente. Por consiguiente, la producción es lenta." }
    { group:117, id:10, text: "Casi sin empleados, esta granja puede criar muy pocas cabezas de ganado." }
    { group:117, id:11, text: "La tierra de esta granja ha sido arrasada por una reciente plaga de langosta. El ganado no puede crecer hasta que se recupere." }
    { group:117, id:12, text: "La tierra es" }
    { group:117, id:13, text: "fértil" }
    { group:118, id:0, text: "Cantera de piedra normal" }
    { group:118, id:1, text: "Aquí puedes extraer piedra normal. Ya que hay monumentos en construcción por todo Egipto, podrás encontrar un comprador para esta piedra de construcción en caso de que no le puedas dar uso." }
    { group:118, id:2, text: "La producción está al:" }
    { group:118, id:3, text: "." }
    { group:118, id:4, text: "El supervisor comercial ha ordenado suspender la extracción de piedra." }
    { group:118, id:5, text: "Esta cantera no tiene empleados. La producción se ha detenido." }
    { group:118, id:6, text: "Esta cantera cuenta con todos los empleados que necesita y produce muchas toneladas de piedra normal." }
    { group:118, id:7, text: "Esta cantera está trabajando por debajo de su capacidad debido a una ligera escasez de trabajadores." }
    { group:118, id:8, text: "Esta cantera no tiene suficientes empleados y tarda más de lo que debería en producir los bloques de piedra." }
    { group:118, id:9, text: "En esta cantera trabaja muy poca gente. Por consiguiente, la producción es muy lenta." }
    { group:118, id:10, text: "Casi sin empleados, la producción de esta cantera está prácticamente parada. Producirá poco durante el próximo año." }
    { group:119, id:0, text: "Cantera de piedra caliza" }
    { group:119, id:1, text: "Extrae piedra caliza para usarla en la construcción de monumentos o para exportarla." }
    { group:119, id:2, text: "La producción está al:" }
    { group:119, id:3, text: "." }
    { group:119, id:4, text: "El supervisor comercial ha ordenado detener la extracción de caliza." }
    { group:119, id:5, text: "Esta cantera no tiene empleados, de modo que no produce piedra caliza." }
    { group:119, id:6, text: "Esta cantera tiene todos los trabajadores que necesita y produce tanta caliza como puede." }
    { group:119, id:7, text: "Este cantera funciona por debajo de su capacidad. La producción podría ser mayor si hubiera más trabajadores." }
    { group:119, id:8, text: "Este edificio no tiene suficientes empleados. Tarda más de lo que debería en cortar los bloques de caliza." }
    { group:119, id:9, text: "En este edificio trabaja muy poca gente. Por consiguiente, la producción es lenta." }
    { group:119, id:10, text: "Casi sin trabajadores, la producción de caliza es prácticamente inexistente." }
    { group:120, id:0, text: "Serrería" }
    { group:120, id:1, text: "La madera tiene muchos usos, que van desde la construcción de monumentos hasta la de barcos. Además, está muy demandada por todo el imperio." }
    { group:120, id:2, text: "Bodega" }
    { group:120, id:3, text: "Madera sin tratar" }
    { group:120, id:4, text: "El supervisor comercial ha ordenado suspender la tala de árboles." }
    { group:120, id:5, text: "Esta serrería no tiene empleados y no contribuye en nada a la economía de la ciudad." }
    { group:120, id:6, text: "Este edificio tiene todo el personal que necesita. Tala madera con total eficacia." }
    { group:120, id:7, text: "Esta serrería no tiene suficientes empleados y la producción de madera es menor de lo que podría ser." }
    { group:120, id:8, text: "Esta serrería tiene muy poco personal y tarda más de lo que debería en talar madera." }
    { group:120, id:9, text: "En este almacén trabaja muy poca gente. Como resultado, la producción de madera es muy lenta." }
    { group:120, id:10, text: "Con tan pocos taladores, la producción de madera está casi parada." }
    { group:121, id:0, text: "Pozo de arcilla" }
    { group:121, id:1, text: "Extrae arcilla para comerciar o para proveer a los alfareros. La gente encuentra muchos usos para la cerámica y a menudo puedes comerciar con rentabilidad con otras ciudades." }
    { group:121, id:2, text: "La producción está al:" }
    { group:121, id:3, text: "." }
    { group:121, id:4, text: "El supervisor comercial ha detenido la extracción de arcilla." }
    { group:121, id:5, text: "Este pozo de arcilla no tiene empleados. La producción se ha detenido." }
    { group:121, id:6, text: "Este pozo de arcilla tiene todo el personal que necesita. Se esmera en producir arcilla." }
    { group:121, id:7, text: "Este pozo de arcilla está trabajando por debajo de su capacidad máxima. Por consiguiente, la producción de arcilla será algo inferior." }
    { group:121, id:8, text: "Este pozo de arcilla tiene muy poco personal, por lo que la producción de arcilla es más lenta de lo deseado." }
    { group:121, id:9, text: "Aquí trabaja muy poco personal. Por consiguiente, la extracción de arcilla es extremadamente lenta." }
    { group:121, id:10, text: "Con tan poco personal en este pozo de arcilla, la producción es casi inexistente. Producirá muy poca arcilla el próximo año." }
    { group:122, id:0, text: "Cervecería" }
    { group:122, id:1, text: "Los cerveceros convierten la cebada en cerveza, sin la que los locales de senet estarían vacíos y los festivales de la ciudad serían aburridos. La cerveza es una mercancía muy demandada." }
    { group:122, id:2, text: "La producción está al:" }
    { group:122, id:3, text: "." }
    { group:122, id:4, text: "El supervisor comercial ha ordenado suspender la producción de cerveza." }
    { group:122, id:5, text: "Esta cervecería no tiene empleados. La producción ha parado." }
    { group:122, id:6, text: "Esta cervecería tiene todos los empleados que necesita y produce cerveza a pleno rendimiento." }
    { group:122, id:7, text: "Esta cervecería funciona por debajo de su capacidad. La producción de cerveza es un poco más lenta de lo que podría ser." }
    { group:122, id:8, text: "Esta cervecería no tiene suficientes empleados y tarda en producir cerveza más de lo debido." }
    { group:122, id:9, text: "En esta cervecería trabaja muy poca gente. Por consiguiente, la producción de cerveza es muy lenta." }
    { group:122, id:10, text: "Casi sin cerveceros, la producción de este taller está prácticamente parada. Producirá poca cerveza durante el próximo año." }
    { group:122, id:11, text: "Este taller no puede producir cerveza hasta que reciba una entrega de cebada de un almacén o una granja." }
    { group:122, id:12, text: "Cebada almacenada," }
    { group:123, id:0, text: "Tejedor" }
    { group:123, id:1, text: "Aquí se procesa el lino y se convierte en fibra, necesaria en los mortuorios para embalsamar. El lino puede se lucrativo a la hora de comerciar." }
    { group:123, id:2, text: "La producción está al:" }
    { group:123, id:3, text: "." }
    { group:123, id:4, text: "El supervisor comercial ha ordenado suspender la producción de fibra de lino." }
    { group:123, id:5, text: "Este telar no tiene tejedores y no puede producir fibra de lino." }
    { group:123, id:6, text: "Este telar tiene completo su personal y produce suficiente hilo de alta calidad." }
    { group:123, id:7, text: "Este telar podría tener más trabajadores para alcanzar su máxima producción de hilo." }
    { group:123, id:8, text: "Este telar no tiene suficiente personal y produce hilo más lentamente de lo debido." }
    { group:123, id:9, text: "En este telar trabaja muy poca gente. Por consiguiente, la producción de fibra de lino es lenta." }
    { group:123, id:10, text: "Casi sin empleados, este telar producirá muy poca fibra de lino durante el próximo año." }
    { group:123, id:11, text: "Este taller no puede producir fibra de lino si no tiene un cargamento de lino, ya sea de un almacén o de una granja." }
    { group:123, id:12, text: "Lino almacenado," }
    { group:124, id:0, text: "Armero" }
    { group:124, id:1, text: "Los fabricantes de armas transforman el cobre en lanzas, con las que puedes comerciar y obtener un buen beneficio, o usarlas para equipar a tu ejército." }
    { group:124, id:2, text: "La producción está al:" }
    { group:124, id:3, text: "." }
    { group:124, id:4, text: "El supervisor comercial ha ordenado suspender la producción de armas." }
    { group:124, id:5, text: "Este taller no tiene empleados. La producción se ha detenido." }
    { group:124, id:6, text: "Este taller tiene todo el personal que necesita. Se esmera en producir armas." }
    { group:124, id:7, text: "Este taller está trabajando por debajo de su capacidad máxima. Por consiguiente, la producción de armas será algo inferior." }
    { group:124, id:8, text: "Este taller tiene muy poco personal, por lo que la producción de armas es más lenta de lo deseado." }
    { group:124, id:9, text: "Aquí trabaja muy poco personal. Por consiguiente, la producción de armas es muy lenta." }
    { group:124, id:10, text: "Con tan poco personal, esta armería contribuye con muy pocas armas a los esfuerzos de la ciudad." }
    { group:124, id:11, text: "Este taller necesita cobre, de un almacén o de una mina de cobre, para producir armas." }
    { group:124, id:12, text: "Cobre almacenado," }
    { group:125, id:0, text: "Joyero" }
    { group:125, id:1, text: "Los artesanos de esta instalación producen joyas (artículos de lujo) a partir de piedras preciosas. Algunos ciudadanos quieren artículos de joyería, y además puedes comerciar con los excedentes." }
    { group:125, id:2, text: "La producción está al:" }
    { group:125, id:3, text: "." }
    { group:125, id:4, text: "El supervisor comercial ha ordenado suspender la producción de joyas." }
    { group:125, id:5, text: "Esta instalación no tiene joyeros. La producción ha parado." }
    { group:125, id:6, text: "Esta instalación tiene todo el personal que necesita y se esmera en producir joyas (artículos de lujo)." }
    { group:125, id:7, text: "Esta instalación necesita unos cuantos trabajadores. La producción de joyas (artículos de lujo) mejorará cuando los tenga." }
    { group:125, id:8, text: "Esta instalación no tiene suficientes empleados y tarda en producir joyas (artículos de lujo) más de lo debido." }
    { group:125, id:9, text: "Aquí trabajan muy pocos artesanos. La producción de joyas (artículos de lujo) es muy lenta." }
    { group:125, id:10, text: "Casi sin artesanos, esta joyería producirá pocos artículos de lujo durante el próximo año." }
    { group:125, id:11, text: "Este taller necesita un cargamento de piedras preciosas de un almacén o de una mina para producir joyas." }
    { group:125, id:12, text: "Piedras preciosas almacenadas," }
    { group:126, id:0, text: "Alfarería" }
    { group:126, id:1, text: "Aquí, los alfareros, convierten la arcilla en vasijas que los ciudadanos usan para guardar la mercancía. Comercia con la cerámica o haz que los bazares la distribuyan para que la gente mejore su vivienda." }
    { group:126, id:2, text: "La producción está al:" }
    { group:126, id:3, text: "." }
    { group:126, id:4, text: "El supervisor comercial ha ordenado suspender la producción de cerámica." }
    { group:126, id:5, text: "Este taller no tiene empleados. La producción se ha detenido." }
    { group:126, id:6, text: "Este taller tiene todo el personal que necesita. Se esmera en producir cerámica." }
    { group:126, id:7, text: "Este taller está trabajando por debajo de su capacidad máxima. Por consiguiente, la producción de cerámica será algo inferior." }
    { group:126, id:8, text: "Este taller tiene muy poco personal, por lo que la producción de cerámica es más lenta de lo deseado." }
    { group:126, id:9, text: "Aquí trabaja muy poca gente. Por consiguiente, la producción de cerámica es lenta." }
    { group:126, id:10, text: "Casi sin empleados, esta alfarería producirá muy poca cerámica durante el próximo año." }
    { group:126, id:11, text: "Este taller necesita arcilla de un almacén o un pozo, para producir cerámica." }
    { group:126, id:12, text: "Arcilla almacenada," }
    { group:127, id:0, text: "Viviendas" }
    { group:127, id:1, text: "Desactivar modo prueba" }
    { group:127, id:2, text: "Activar modo prueba" }
    { group:127, id:3, text: "Atractivo" }
    { group:127, id:4, text: "Entr." }
    { group:127, id:5, text: "H2O" }
    { group:127, id:6, text: "Religión" }
    { group:127, id:7, text: "Educación" }
    { group:127, id:8, text: "Acceso a un bazar" }
    { group:127, id:9, text: "Acceso a un dentista" }
    { group:127, id:10, text: "Acceso a un médico" }
    { group:127, id:11, text: "Sanidad" }
    { group:127, id:12, text: "Tipos de comida" }
    { group:127, id:13, text: "Cerámica necesaria" }
    { group:127, id:14, text: "Fibra de lino necesaria" }
    { group:127, id:15, text: "Artículos de lujo necesarios" }
    { group:127, id:16, text: "Cerveza necesaria" }
    { group:127, id:17, text: "Ahora" }
    { group:127, id:18, text: "mejora a" }
    { group:127, id:19, text: "necesita" }
    { group:127, id:20, text: "ocupantes" }
    { group:127, id:21, text: "demasiado." }
    { group:127, id:22, text: "Espacio extra para" }
    { group:127, id:23, text: "No recibe visitas del recaudador. No paga impuestos." }
    { group:127, id:24, text: "Generados" }
    { group:127, id:25, text: "de momento." }
    { group:127, id:26, text: "Los residentes no informan de incidentes violentos." }
    { group:127, id:27, text: "Este es un vecindario pacífico." }
    { group:127, id:28, text: "Hay poca criminalidad, nada serio." }
    { group:127, id:29, text: "La criminalidad se está convirtiendo en un problema." }
    { group:127, id:30, text: "El alto índice de criminalidad asusta a los habitantes." }
    { group:127, id:31, text: "Una zona sin ley. Los ciudadanos están aterrorizados." }
    { group:127, id:32, text: "Éste es un caldo de cultivo para los ladrones." }
    { group:127, id:33, text: "Las cabañas no mejorarán hasta que reciban alimentos de un bazar." }
    { group:127, id:34, text: "Housing FREE" }
    { group:127, id:35, text: "Housing FREE" }
    { group:127, id:36, text: "Housing FREE" }
    { group:127, id:37, text: "Housing FREE" }
    { group:127, id:38, text: "Housing FREE" }
    { group:127, id:39, text: "Housing FREE" }
    { group:127, id:40, text: "Esta casa decaerá pronto. El escaso atractivo de la localidad acabará por arruinar la zona." }
    { group:127, id:41, text: "Esta casa decaerá pronto, puesto que no tiene acceso ni a las formas más primitivas de abastecimiento de agua." }
    { group:127, id:42, text: "Esta casa decaerá pronto, puesto que no la visita un aguador." }
    { group:127, id:43, text: "Esta casa decaerá pronto, puesto que no hay entretenimiento en la zona." }
    { group:127, id:44, text: "Esta casa decaerá pronto, puesto que apenas hay entretenimiento en la zona." }
    { group:127, id:45, text: "Esta casa decaerá pronto, puesto que no hay bastante entretenimiento en la zona." }
    { group:127, id:46, text: "Esta casa decaerá pronto, puesto que puede encontrarse algo de entretenimiento en la ciudad, pero no resulta suficiente." }
    { group:127, id:47, text: "Esta casa decaerá pronto, puesto que pese al buen entretenimiento que ofrece la ciudad, aún no hay una variada oferta." }
    { group:127, id:48, text: "Esta casa decaerá pronto. En el lugar hay excelentes locales de entretenimiento, pero están muy concurridos, o hay poca variedad para las exigentes clases instruidas." }
    { group:127, id:49, text: "Esta casa decaerá pronto, puesto que últimamente no recibe suministros de alimentos de un bazar local." }
    { group:127, id:50, text: "Esta casa decaerá pronto, puesto que en la actualidad sólo tiene acceso a un tipo de alimentos del bazar local. Esto desanima a los ciudadanos más pudientes." }
    { group:127, id:51, text: "Esta casa decaerá pronto, puesto que en la actualidad sólo tiene acceso a dos tipos de alimentos del bazar local. Esto desanima a las clases instruidas." }
    { group:127, id:52, text: "Esta casa decaerá pronto. Ha perdido el acceso a un bazar." }
    { group:127, id:53, text: "Esta casa decaerá pronto. Aunque tiene acceso a un bazar, éste tiene dificultades para conseguir alimentos." }
    { group:127, id:54, text: "Esta casa decaerá pronto, puesto que ha perdido todas las instalaciones educativas básicas, que proporcionaban la escuela de escribas o la biblioteca." }
    { group:127, id:55, text: "Esta casa decaerá pronto. Su antiguo acceso a la educación se ha visto mermado y ha perdido el acceso a una biblioteca." }
    { group:127, id:56, text: "Esta casa decaerá pronto. Su antiguo acceso a la educación se ha visto mermado, ya que ha perdido el acceso a una biblioteca." }
    { group:127, id:57, text: "Esta casa decaerá pronto. Su acceso a la educación, antes excelente, se vio degradado cuando perdió el acceso a la educación superior." }
    { group:127, id:58, text: "Esta casa decaerá pronto, puesto que no tiene acceso a los jueces de los palacios de justicia." }
    { group:127, id:59, text: "Esta casa decaerá pronto. Se ha quedado sin cerámica, y el bazar local tiene, en el mejor de los casos, un suministro irregular." }
    { group:127, id:60, text: "Esta casa decaerá pronto, puesto que ha perdido todo acceso a las instalaciones religiosas." }
    { group:127, id:61, text: "Esta casa decaerá pronto. Su acceso a las instalaciones religiosas se ha visto reducido a los templos de un solo dios." }
    { group:127, id:62, text: "Esta casa decaerá pronto. Sus instalaciones religiosas, antes excelentes, se han visto reducidas a los templos de sólo dos dioses." }
    { group:127, id:63, text: "Esta casa decaerá pronto, puesto que ha perdido el acceso a un dentista." }
    { group:127, id:64, text: "Esta casa decaerá pronto, puesto que tiene unos servicios sanitarios lamentables. No sólo le falta el acceso a un mortuorio, sino que el acceso a los médicos deja mucho que desear." }
    { group:127, id:65, text: "Esta casa decaerá pronto, ya que se han recortado los cuidados sanitarios. La cobertura médica es buena, pero no hay acceso a un mortuorio." }
    { group:127, id:66, text: "Esta casa decaerá pronto, ya que se han recortado los cuidados sanitarios. Tiene acceso a un mortuorio, pero es difícil encontrar médicos." }
    { group:127, id:67, text: "Esta casa decaerá pronto, puesto que se ha quedado sin fibra de lino y el bazar local tiene, en el mejor de los casos, un suministro irregular." }
    { group:127, id:68, text: "Sin usar" }
    { group:127, id:69, text: "Esta casa decaerá pronto, puesto que se ha quedado sin cerveza y el bazar local tiene, en el mejor de los casos, un suministro irregular." }
    { group:127, id:70, text: "Esta vivienda no puede mejorar hasta que mejore la zona." }
    { group:127, id:71, text: "Esta casa no puede mejorar, puesto que ni siquiera tiene acceso a la fuente de agua más primitiva." }
    { group:127, id:72, text: "Esta casa no puede mejorar, puesto que no tiene acceso a los servicios de un aguador." }
    { group:127, id:73, text: "Esta casa no puede mejorar, puesto que no hay entretenimiento en la zona." }
    { group:127, id:74, text: "Esta casa no puede mejorar, puesto que apenas hay entretenimiento en la zona." }
    { group:127, id:75, text: "Esta casa no puede mejorar, puesto que hay muy poco entretenimiento en la zona." }
    { group:127, id:76, text: "Esta casa no puede mejorar, puesto que puede encontrarse algo de entretenimiento en la ciudad, pero no resulta suficiente." }
    { group:127, id:77, text: "Esta casa no puede mejorar, puesto que pese al buen entretenimiento que ofrece la ciudad, aún no hay una variada oferta." }
    { group:127, id:78, text: "Esta casa no puede mejorar. En el lugar hay excelentes locales de entretenimiento, pero están muy concurridos o hay poca variedad para las exigentes clases instruidas." }
    { group:127, id:79, text: "Esta casa no puede mejorar, puesto que necesita un suministro de alimento de un bazar local." }
    { group:127, id:80, text: "Esta casa no puede mejorar, puesto que necesita una segunda clase de alimento, proporcionada por el bazar local, para animar a los egipcios más pudientes a trasladarse." }
    { group:127, id:81, text: "Esta casa no puede mejorar, puesto que necesita una tercera clase de alimento, proporcionadas por un bazar local, para animar a los egipcios de clase más alta a trasladarse." }
    { group:127, id:82, text: "Esta casa no puede mejorar, puesto que no tiene acceso a un bazar local." }
    { group:127, id:83, text: "Esta casa no puede mejorar. Aunque tiene acceso a un bazar local, éste tiene problemas para conseguir alimentos." }
    { group:127, id:84, text: "Esta casa no puede mejorar, puesto que no tiene instalaciones educativas básicas, que proporcionaría una escuela de escribas o una biblioteca." }
    { group:127, id:85, text: "Esta casa no puede mejorar, puesto que su acceso a la educación debe mejorarse con el acceso a una biblioteca." }
    { group:127, id:86, text: "Esta casa no puede mejorar, puesto que necesita que se mejore su acceso a la educación con una escuela de escribas." }
    { group:127, id:87, text: "Línea sin uso que informa sobre la evolución interrumpida por la falta de acceso a una academia." }
    { group:127, id:88, text: "Esta casa no puede mejorar, puesto que no tiene acceso a un juez de un palacio de justicia." }
    { group:127, id:89, text: "Esta casa no puede mejorar. Necesita suministros de cerámica, proporcionados por un bazar local, para que se trasladen ciudadanos pudientes." }
    { group:127, id:90, text: "Esta casa no puede mejorar, puesto que no tiene acceso a instalaciones religiosas." }
    { group:127, id:91, text: "Esta casa no puede mejorar, puesto que solamente tiene acceso a templos de un solo dios. Cuando sus habitantes prosperen, querrán emplear su tiempo en adorar a más dioses." }
    { group:127, id:92, text: "Esta casa no puede mejorar, puesto que sólo tiene acceso a templos de dos dioses. Cuando sus habitantes prosperen, querrán emplear su tiempo en adorar a más dioses." }
    { group:127, id:93, text: "Esta casa no puede mejorar, puesto que no tiene acceso a un dentista." }
    { group:127, id:94, text: "Esta casa no puede mejorar, puesto que no cuenta con cuidados sanitarios. No tiene acceso ni a un médico ni a un mortuorio." }
    { group:127, id:95, text: "Esta casa no puede mejorar, puesto que requiere mayores cuidados sanitarios. La cobertura médica es buena, pero no tiene acceso a un mortuorio." }
    { group:127, id:96, text: "Esta casa no puede mejorar, puesto que requiere mayores cuidados sanitarios. Tiene acceso a un mortuorio, pero necesita una botica cerca." }
    { group:127, id:97, text: "Esta casa no puede mejorar. Necesita suministros de fibra de lino, proporcionados por el bazar local, para que se trasladen los ciudadanos pudientes." }
    { group:127, id:98, text: "Sin usar" }
    { group:127, id:99, text: "Esta casa no puede mejorar. Necesita suministros de cerveza, proporcionada por el bazar local, para que se trasladen los ciudadanos pudientes." }
    { group:127, id:100, text: "Los habitantes de este palacio están en la cima de la sociedad egipcia. No carecen de nada. Mantener sus necesidades cubiertas es un logro notable." }
    { group:127, id:101, text: "Esta vivienda pronto se convertirá en una de mayor categoría, como resultado de la mejora de las condiciones locales." }
    { group:127, id:102, text: "Un edificio cercano (" }
    { group:127, id:103, text: "tiene efectos perjudiciales sobre el prestigio de la zona." }
    { group:127, id:104, text: "Si tuviese más espacio hacia donde expandirse, esta vivienda pronto se convertiría en una de mayor categoría." }
    { group:127, id:105, text: "Sin usar" }
    { group:127, id:106, text: "Sin usar" }
    { group:127, id:107, text: "Casa infectada durante" }
    { group:127, id:108, text: "Esta casa no puede mejorar. Necesita suministros de artículos de lujo como" }
    { group:127, id:109, text: "Casa infectada de ranas durante" }
    { group:127, id:110, text: "Esta casa decaerá pronto, puesto que la ciudad sólo tiene una clase de artículos de lujo" }
    { group:127, id:111, text: "y sus exigentes habitantes se quejan de la falta de variedad." }
    { group:127, id:112, text: "Esta casa decaerá pronto. Necesita suministros de artículos de lujo, como joyas," }
    { group:127, id:113, text: "para satisfacer el sibaritismo de la clase alta." }
    { group:127, id:114, text: "Esta casa no puede mejorar." }
    { group:127, id:115, text: "pero necesita una segunda clase de artículos de lujo, como ébano, marfil o incienso," }
    { group:127, id:116, text: "para satisfacer el sibaritismo de la clase alta." }
    { group:128, id:0, text: "Parcela libre" }
    { group:128, id:1, text: "Nadie ha venido aquí, aunque es probable que lleguen inmigrantes si les ofreces comida y trabajo." }
    { group:128, id:2, text: "Este terreno está lejos de la carretera. Si no se hace cerca una, volverá a ser campo abierto." }
    { group:129, id:0, text: "desde" }
    { group:129, id:1, text: "Capacidad" }
    { group:129, id:2, text: "Compra" }
    { group:129, id:3, text: "Ventas" }
    { group:129, id:4, text: "Comprado" }
    { group:129, id:5, text: "Vendido" }
    { group:129, id:6, text: "Anclado, esperando a un muelle libre." }
    { group:129, id:7, text: "En el muelle, comprando y vendiendo bienes." }
    { group:129, id:8, text: "Regresando a casa." }
    { group:129, id:9, text: "Navegando hacia los muelles de la ciudad." }
    { group:129, id:10, text: "Comerciando con bienes." }
    { group:129, id:11, text: "Regresando a casa." }
    { group:129, id:12, text: "Dirigiéndose a los almacenes de la ciudad" }
    { group:129, id:13, text: "Nada con lo que comerciar, solamente de paso." }
    { group:129, id:14, text: "desde" }
    { group:129, id:15, text: "Yendo a" }
    { group:129, id:16, text: "Volviendo a" }
    { group:129, id:17, text: "Recogiendo" }
    { group:129, id:18, text: "Volviendo con" }
    { group:129, id:19, text: "unidad de" }
    { group:129, id:20, text: "unidades de" }
    { group:129, id:21, text: "Que lleva" }
    { group:130, id:0, text: "(No es usada)" }
    { group:131, id:0, text: "Choza de nativos" }
    { group:131, id:1, text: "Does this text appear anywhere?" }
    { group:132, id:0, text: "Choza de encuentro de nativos" }
    { group:132, id:1, text: "¿Se usa esta entrada en algún lugar?" }
    { group:133, id:0, text: "Cultivos básicos" }
    { group:133, id:1, text: "This entry is probably unused." }
    { group:134, id:0, text: "Puesto de misión" }
    { group:134, id:1, text: "Where did this text appear?" }
    { group:135, id:0, text: "Academia militar" }
    { group:135, id:1, text: "Cuando los soldados novatos terminan su entrenamiento básico con el reclutador, tratan de mejorar su calidad y capacidad en esta academia, pero no será posible hasta que tenga completo el personal." }
    { group:135, id:2, text: "Sin personal somos incapaces de perfeccionar la destreza de los nuevos soldados de la ciudad. Tendrán que ir directamente a sus fuertes y confiar en su fortuna." }
    { group:135, id:3, text: "Proporcionamos a los soldados inexpertos recién reclutados la formación que necesitan para sobresalir en un ejército egipcio moderno." }
    { group:136, id:0, text: "Reclutador" }
    { group:136, id:1, text: "Nadie puede alistarse en el ejército egipcio sin haber pasado antes por la academia de entrenamiento de la ciudad para nuevos reclutas." }
    { group:136, id:2, text: "Armas almacenadas" }
    { group:136, id:3, text: "Sin personal, no podemos ni entrenar ni a un solo recluta. Seth nos ayuda en tiempos de guerra." }
    { group:136, id:4, text: "Actualmente no estamos entrenando a ningún recluta, ya que ni los fuertes ni las torres de la ciudad nos han solicitado nuevos efectivos." }
    { group:136, id:5, text: "Podemos entrenar nuevos arqueros suficientemente deprisa, pero necesitamos armas para añadir infantería o carros de combate al batallón de la ciudad." }
    { group:136, id:6, text: "Nos faltan empleados, de modo que entrenamos a los nuevos soldados poco a poco. No podemos entrenar ni a soldados de infantería ni a aurigas sin tener armas almacenadas." }
    { group:136, id:7, text: "Perdemos empleados, así que podemos entrenar pocos soldados. Podemos entrenar arqueros, pero a un ritmo lento." }
    { group:136, id:8, text: "Con este personal tan reducido y sin suministros de armas, apenas podemos entrenar a un arquero de vez en cuando." }
    { group:136, id:9, text: "Estamos entrenando soldados nuevos con el máximo nivel de eficiencia y tenemos las armas para adiestrar a cualquier tipo de soldado." }
    { group:136, id:10, text: "Estamos entrenando soldados nuevos con un nivel de eficiencia reducido debido a la falta de personal, aunque tenemos las armas para adiestrar a cualquier tipo de soldado." }
    { group:136, id:11, text: "Nuestro personal es insuficiente y por ello entrenamos lentamente a los nuevos soldados, aunque tenemos las armas para entrenar a cualquier tipo de soldado." }
    { group:136, id:12, text: "Con este personal tan reducido estamos entrenando a nuevos soldados a un ritmo extremadamente lento, aunque tenemos las armas para entrenar a cualquier tipo de soldado." }
    { group:136, id:13, text: "Carros almacenados" }
    { group:136, id:14, text: "Carro almacenado" }
    { group:136, id:15, text: "Armas almacenadas" }
    { group:137, id:0, text: "Plaza" }
    { group:137, id:1, text: "Los bulevares hacen que las carreteras normales sean más atractivas, sin afectar al tráfico." }
    { group:138, id:0, text: "\"Los leones\"" }
    { group:138, id:1, text: "\"Los cocodrilos\"" }
    { group:138, id:2, text: "\"Las cobras\"" }
    { group:138, id:3, text: "\"Los escorpiones\"" }
    { group:138, id:4, text: "\"Los halcones\"" }
    { group:138, id:5, text: "\"Los carneros\"" }
    { group:138, id:6, text: "\"Las hienas\"" }
    { group:138, id:7, text: "\"Los escarabajos\"" }
    { group:138, id:8, text: "'Los chacales'" }
    { group:138, id:9, text: "\"Los chacales\"" }
    { group:138, id:10, text: "\"Las víboras\"" }
    { group:138, id:11, text: "En la actualidad, esta compañía no dispone de soldados. Cuando lleguen nuevas tropas entrenadas por el reclutador, se convertirá en una unidad de lucha." }
    { group:138, id:12, text: "Esta compañía no dispone de soldados y no es de ayuda. No hay ningún reclutador para conseguir tropas y la unidad seguirá vacía." }
    { group:138, id:13, text: "Mantenerse firme en formación apretada" }
    { group:138, id:14, text: "La compañía se mantiene firme y lucha sólo si la atacan. Los soldados tienen ventaja en el ataque, pero son más vulnerables al fuego de proyectiles." }
    { group:138, id:15, text: "Mantenerse firme en formación libre" }
    { group:138, id:16, text: "La compañía lucha sólo si la atacan. Los soldados ocupan más terreno y son menos vulnerables a los proyectiles, pero sus habilidades se resienten." }
    { group:138, id:17, text: "Entablar combate con los enemigos cercanos" }
    { group:138, id:18, text: "Con esta orden, la compañía ataca en formación a todos los enemigos tan tontos como para acercarse." }
    { group:138, id:19, text: "Romper filas" }
    { group:138, id:20, text: "Cuando se da esta orden, la compañía rompe la formación para buscar y atacar a todos los enemigos que pueda encontrar." }
    { group:138, id:21, text: "Cargar" }
    { group:138, id:22, text: "La compañía que recibe esta orden deja la precaución y vuelca todo su poder en romper las filas del enemigo." }
    { group:138, id:23, text: "Cuando se da esta orden, la compañía deja el campo y vuelve a su fuerte para sustituir a los caídos, descansar y recuperar los ánimos." }
    { group:138, id:24, text: "Soldados en la compañía" }
    { group:138, id:25, text: "Salud de los soldados" }
    { group:138, id:26, text: "Experiencia" }
    { group:138, id:27, text: "Perfecta" }
    { group:138, id:28, text: "Muy buena" }
    { group:138, id:29, text: "Buena" }
    { group:138, id:30, text: "Mediano" }
    { group:138, id:31, text: "Pobre" }
    { group:138, id:32, text: "Muy pobre" }
    { group:138, id:33, text: "Espantosa" }
    { group:138, id:34, text: "Aurigas" }
    { group:138, id:35, text: "Infantería" }
    { group:138, id:36, text: "Arqueros" }
    { group:138, id:37, text: "Moral" }
    { group:138, id:38, text: "Presa del pánico" }
    { group:138, id:39, text: "Aterrorizados" }
    { group:138, id:40, text: "Asustadísimos" }
    { group:138, id:41, text: "Muy asustados" }
    { group:138, id:42, text: "Asustados" }
    { group:138, id:43, text: "Muy desconcertados" }
    { group:138, id:44, text: "Desconcertados" }
    { group:138, id:45, text: "Pobre" }
    { group:138, id:46, text: "Bastante pobres" }
    { group:138, id:47, text: "Inf. a la media" }
    { group:138, id:48, text: "Mediano" }
    { group:138, id:49, text: "Sup. a la media" }
    { group:138, id:50, text: "Animados" }
    { group:138, id:51, text: "Bastante audaces" }
    { group:138, id:52, text: "Audaces" }
    { group:138, id:53, text: "Intrépidos" }
    { group:138, id:54, text: "Muy intrépidos" }
    { group:138, id:55, text: "Fuertes" }
    { group:138, id:56, text: "Muy fuertes" }
    { group:138, id:57, text: "Excelente" }
    { group:138, id:58, text: "Perfecta" }
    { group:138, id:59, text: "Volver al fuerte" }
    { group:138, id:60, text: "Maldito por Seth." }
    { group:138, id:61, text: "Verde" }
    { group:138, id:62, text: "Especializado" }
    { group:138, id:63, text: "Veterano" }
    { group:138, id:64, text: "Maestros" }
    { group:138, id:65, text: "Élite" }
    { group:138, id:66, text: "El mejor" }
    { group:138, id:67, text: "Puntos de tiro" }
    { group:138, id:68, text: "Ataque cuerpo a cuerpo" }
    { group:138, id:69, text: "Defensa cuerpo a cuerpo" }
    { group:138, id:70, text: "Defensa o proyectiles" }
    { group:138, id:71, text: "Ataque con proyectiles" }
    { group:138, id:72, text: "Alcance de proyectiles" }
    { group:138, id:73, text: "Alcance de disparo de proyectiles" }
    { group:138, id:74, text: "Compañía" }
    { group:138, id:75, text: "Compañía de infantería" }
    { group:138, id:76, text: "Compañía de arqueros" }
    { group:138, id:77, text: "Compañía de aurigas" }
    { group:138, id:78, text: "Pulsa aquí para girar la compañía" }
    { group:138, id:79, text: "Órdenes y orientación de la compañía" }
    { group:139, id:0, text: "Muralla de barro" }
    { group:139, id:1, text: "Las murallas evitan el avance de los invasores hacia la ciudad. Éstos pueden destruir las murallas. Las murallas gruesas son más fuertes y permiten patrullar a los guardias entre las torres conectadas." }
    { group:140, id:0, text: "Escombros" }
    { group:140, id:1, text: "Estas son las ruinas del edificio cuyo nombre aparece arriba. Los lugares abandonados como éste no ayudan a mejorar el entorno." }
    { group:141, id:0, text: "Acequia de riego" }
    { group:141, id:1, text: "Esta acequia de riego lleva agua para ayudar a fertilizar la tierras de labranza." }
    { group:141, id:2, text: "Esta acequia de riego no lleva agua a las tierras más estériles, puesto que no está conectada a ninguna fuente de agua." }
    { group:142, id:0, text: "Establecida nueva ruta comercial." }
    { group:142, id:1, text: "Para comerciar con estos nuevos artículos disponibles, da instrucciones al supervisor comercial para asignarles la condición de importación o exportación." }
    { group:142, id:2, text: "¿Visitar al supervisor?" }
    { group:142, id:3, text: "¡RECUERDA! Tu ciudad necesita un muelle para que los barcos comerciales puedan transitar esta nueva ruta marítima." }
    { group:143, id:0, text: "Aceptar bienes" }
    { group:143, id:1, text: "Rechazar bienes" }
    { group:143, id:2, text: "Solicitar comida" }
    { group:144, id:0, text: "Haz clic en una ciudad para gobernarla" }
    { group:144, id:1, text: "I" }
    { group:144, id:2, text: "Blanco" }
    { group:144, id:3, text: "Blanco" }
    { group:144, id:4, text: "II" }
    { group:144, id:5, text: "Blanco" }
    { group:144, id:6, text: "Blanco" }
    { group:144, id:7, text: "III" }
    { group:144, id:8, text: "Blanco" }
    { group:144, id:9, text: "Blanco" }
    { group:144, id:10, text: "IV" }
    { group:144, id:11, text: "Blanco" }
    { group:144, id:12, text: "Blanco" }
    { group:144, id:13, text: "V" }
    { group:144, id:14, text: "Blanco" }
    { group:144, id:15, text: "Blanco" }
    { group:144, id:16, text: "VI" }
    { group:144, id:17, text: "Blanco" }
    { group:144, id:18, text: "Blanco" }
    { group:144, id:19, text: "VII Final del periodo arcaico" }
    { group:144, id:20, text: "Bedet (Apolinópolis): Aguas peligrosas" }
    { group:144, id:21, text: "Abedyú (Abidós): La necrópolis" }
    { group:144, id:22, text: "Nacimiento del imperio antiguo" }
    { group:144, id:23, text: "Oasis de Selima: Proteger el rastro de las caravanas" }
    { group:144, id:24, text: "Abú (Elefantina): Obtener nuevas riquezas" }
    { group:144, id:25, text: "IX (El imperio antiguo)" }
    { group:144, id:26, text: "Blanco" }
    { group:144, id:27, text: "Blanco" }
    { group:144, id:28, text: "El imperio antiguo" }
    { group:144, id:29, text: "Serabit Jadim: El duro Sinaí" }
    { group:144, id:30, text: "Meidum: Una de tus tumbas" }
    { group:144, id:31, text: "La era de las pirámides" }
    { group:144, id:32, text: "Buhen: Dominando a los Nubios" }
    { group:144, id:33, text: "Sur de Dashur: Un nuevo tipo de pirámide" }
    { group:144, id:34, text: "XII (El imperio antiguo)" }
    { group:144, id:35, text: "Blanco" }
    { group:144, id:36, text: "Blanco" }
    { group:144, id:37, text: "La era de las pirámides" }
    { group:144, id:38, text: "Iunet (Dendera): Una amenaza de los cusitas" }
    { group:144, id:39, text: "On (Heliópolis): Las canteras de Tura" }
    { group:144, id:40, text: "XIV (El imperio antiguo)" }
    { group:144, id:41, text: "Blanco" }
    { group:144, id:42, text: "Blanco" }
    { group:144, id:43, text: "La cumbre del imperio antiguo" }
    { group:144, id:44, text: "Oasis de Bahariya: Los soldados de Ra" }
    { group:144, id:45, text: "Diedu (Abusir): Venerando a Ra" }
    { group:144, id:46, text: "El declive del imperio antiguo" }
    { group:144, id:47, text: "Oasis de Dunqul: Expulsar a los chacales" }
    { group:144, id:48, text: "Oasis de Daila: Orden en medio del caos" }
    { group:144, id:49, text: "El primer periodo intermedio" }
    { group:144, id:50, text: "Tinis: La guerra por el trono" }
    { group:144, id:51, text: "Waset (Tebas): La gloria amenazada" }
    { group:144, id:52, text: "El nacimiento del imperio medio" }
    { group:144, id:53, text: "Kebet (Coptos): Luchando por la paz" }
    { group:144, id:54, text: "Menat Jufú (Beni Hasán): Hambre" }
    { group:144, id:55, text: "XIX" }
    { group:144, id:56, text: "Blanco" }
    { group:144, id:57, text: "Blanco" }
    { group:144, id:58, text: "El imperio medio" }
    { group:144, id:59, text: "Iken (Mirgisa): Empujando la frontera" }
    { group:144, id:60, text: "Sawu (Mersa Gawasis): Nuevos comerciantes" }
    { group:144, id:61, text: "El imperio medio" }
    { group:144, id:62, text: "Heh (Semna): Antiguos y nuevos enemigos" }
    { group:144, id:63, text: "Bubastis: La joya de la corona de Egipto" }
    { group:144, id:64, text: "El segundo periodo intermedio" }
    { group:144, id:65, text: "Jmun (Hermópolis): Venganza" }
    { group:144, id:66, text: "Sautí (Likópolis): Inspiración" }
    { group:144, id:67, text: "Imperio nuevo: ¿Conquista o paz?" }
    { group:144, id:68, text: "Biblos: Invadir Palestina" }
    { group:144, id:69, text: "Baki (Kubán): Una época dorada" }
    { group:144, id:70, text: "Última misión" }
    { group:144, id:71, text: "Rowarty (Avaris): El mundo es nuestro" }
    { group:144, id:72, text: "Hatsepusret (Kahun): La magnífica pirámide" }
    { group:145, id:0, text: "En esta misión no hay condiciones de victoria o derrota. Simplemente trata de edificar tu ciudad." }
    { group:146, id:0, text: "Confirma que la nueva resolución está configurada correctamente (si puedes ver esto, es correcta). Este mensaje desaparecerá en 10 segundos." }
    { group:146, id:1, text: "No se ha seleccionado la localización del imperio." }
    { group:146, id:2, text: "Estoy usando la ubicación predeterminada." }
    { group:146, id:3, text: "Ir a la pantalla del imperio." }
    { group:147, id:0, text: "¡Bien hecho! Al proporcionar alimento a la gente y proteger sus casas de incendios y derrumbamientos, has ayudado a esta nueva civilización a dar su primer paso en el largo camino de la historia." }
    { group:147, id:1, text: "¡Excelente! Has construido la primera ciudad de verdad en esta tierra árida, proporcionando a tus ciudadanos necesidades corporales y espirituales, y has ayudado a la confederación tinita a unificar la tierra dividida." }
    { group:147, id:2, text: "¡Fantástico! Tus ciudadanos empiezan a verte como su guardian y las ciudades vecinas también te aclaman como un proveedor en tiempos de necesidad." }
    { group:147, id:3, text: "¡Bien hecho! Gracias a tu capacidad de liderazgo, la civilización egipcia ha avanzado considerablemente y continuará haciéndolo en las próximas décadas." }
    { group:147, id:4, text: "Felicidades. Has construido una capital digna tanto de los vivos como de los muertos. Al desarrollar las relaciones con otras ciudades, has metido a tu ciudad en la escena internacional." }
    { group:147, id:5, text: "El faraón te aplaude. Gracias a tu hábil gestión, has defendido con éxito a tu ciudad del ataque beduino y has proporcionado a Egipto los medios para defenderse." }
    { group:147, id:6, text: "El faraón está complacido. Has dominado los mares y ríos y has hecho buen uso de los recursos que te ofrecen. La poderosa flota de guerra que construiste patrulla las vías fluviales, protegiendo nuestras fronteras." }
    { group:147, id:7, text: "El faraón se alegra por tus logros. Has sacado todo el provecho a lo que te ofrecen el mar y el río, defendiendo nuestras fronteras con una pequeña pero eficaz flota de barcos. También has honrado a la nobleza al proporcionarle tumbas para alojar sus cuerpos." }
    { group:147, id:8, text: "¡Bien hecho! Has cumplido el doble reto de proteger una importante ruta comercial y construir una próspera ciudad que acoge a los ciudadanos más educados. Tu logro es verdaderamente notable." }
    { group:147, id:9, text: "¡Bien hecho! Has establecido una próspera ciudad, a la que otras ciudades egipcias toman como ejemplo y Nubia mira con envidia." }
    { group:147, id:10, text: "La hazaña que has realizado es incomparable. Con tu sabiduría, una monumental pirámide como nunca se ha visto antes, se extiende hacia el cielo y garantiza la inmortalidad a nuestro querido faraón." }
    { group:147, id:11, text: "Has podido superar los peligros del Sinaí y has proporcionado a Egipto abundantes cantidades de valioso cobre y turquesas. Tus actos se recordarán durante generaciones." }
    { group:147, id:12, text: "Excelente. La necrópolis real que has construido es realmente magnífica, y tus años de dedicación y los de tu familia han sido generosamente recompensados con una tumba sagrada." }
    { group:147, id:13, text: "Gracias a tu habilidad, Ahora Egipto reclama parte de Nubia como suya. Con la ciudad que has construido, has demostrado la fuerza, riqueza y grandeza de Egipto a los vencidos nubios." }
    { group:147, id:14, text: "El faraón te elogia. La pirámide romboidal que construiste en su honor es magnífica y supera a cualquier monumento hecho en el pasado." }
    { group:147, id:15, text: "Excelente. Has tomado parte en un momento histórico: la construcción de la primera pirámide de verdad. Con la terminación de la pirámide de Snofru, has sentado el criterio de la construcción de pirámides que seguirán todos los demás." }
    { group:147, id:16, text: "Extraordinario. A pesar de las pobres condiciones y el continuo ataque de los violentos cusitas, has construido una excelente ciudad y has reforzado la frontera sur de Egipto." }
    { group:147, id:17, text: "Magnífico. Las minas que estableciste en Tura han suministrado toda la caliza que Kéops ha solicitado... hasta ahora. Tu ciudad ha alcanzado nuevas cimas culturales y sociales, gracias a una fuerte economía basada en las productivas minas de Tura." }
    { group:147, id:18, text: "Todo Egipto se inclina ante tus logros. Has construido la monumental pirámide de Kéops y la has llenado con ricas provisiones funerarias, y has honrado a Kefrén mediante la construcción de su último lugar de descanso y su impresionante esfinge." }
    { group:147, id:19, text: "Bien hecho. Has sacado el máximo provecho de los limitados recursos y has traído el poder de Ra a este lugar aislado." }
    { group:147, id:20, text: "Fantástico. El magnífico templo del sol que has construido honra a Ra y al Faraón." }
    { group:147, id:21, text: "Has podido mantener a tu gente mientras Egipto se desmorona a tu alrededor. La experiencia de tu familia será de ayuda a Egipto en los difíciles tiempos que se venan." }
    { group:147, id:22, text: "Mientras que Egipto se desmorona a tu alrededor, has podido mantener a tu ciudad unida.Estas habilidades servirán a Egipto en los difíciles tiempos que vienen." }
    { group:147, id:23, text: "Incluso en tiempos de gran desasosiego, la considerable capacidad de liderazgo de tu familia ha devuelto a Tinis a sus glorias pasadas. Tu valiente ejército ha ayudado a la familia de Iniotef, una hazaña que no se olvidará pronto." }
    { group:147, id:24, text: "Gracias a tu diligencia, has alimentado a una gente hambrienta durante la guerra. Tus logros tardarán en olvidarse." }
    { group:147, id:25, text: "Tus incansables esfuerzos le han dado al imperio una bonita y majestuosa ciudad. También has hecho mucho por todo Egipto, ya que has alimentado a los hambrientos en tiempos de necesidad. Tus considerables esfuerzos serán recompensados." }
    { group:147, id:26, text: "Las pirámides y obeliscos que has construido para mí permanecen como testimonio de mi reindo, y por eso estoy muy agradecido. Tu dedicación será recompensada." }
    { group:147, id:27, text: "Gracias a tu generosa dedicación para mantener a tu gente, Egipto te acepta como su legítimo faraón y espera que tu dinastía tenga herederos igual de benevolentes y hábiles." }
    { group:147, id:28, text: "Todos se inclinan ante tu esplendor, poderoso faraón. Has conquistado el norte de Nubia con éxito, al tiempo que has proporcionado al puerto del Mar Rojo los recursos que necesita para prosperar, garantizándo que nuestro ejército tendrá una fiable fuente de cobre." }
    { group:147, id:29, text: "Todos aclaman al sabio y hábil faraón. El nuevo puerto comercial del Mar Rojo está en auge y tu apoyo ayuda a establecer un puesto comercial igual de fuerte en Nubia." }
    { group:147, id:30, text: "Sin duda, Seth te sonríe, faraón. Has conseguido expulsar a los nubios y has sellado la frontera del Sur." }
    { group:147, id:31, text: "La brillante ciudad de Bubastis te hace honor a ti, muy capaz faraón, y a todo Egipto." }
    { group:147, id:32, text: "¡Egipto se regocija! Los hicsos han sido expulsados de nuestra tierra y bajo tu liderazgo Egipto es reclamado" }
    { group:147, id:33, text: "Has conseguido con éxito,que tus generales consiguieran grandes victorias con promesas de vida eterna. Los hicsos y sus temibles carros han sido expulsados de Egipto." }
    { group:147, id:34, text: "Todopoderoso faraón, haciendo retroceder a los hititas, Egipto se ha convertido en un poderoso imperio. Tu espada ha hecho al mundo el regalo de la civilización egipcia." }
    { group:147, id:35, text: "Pacífico faraón, tu serena influencia ha llevado a Egipto al borde de una nueva grandeza." }
    { group:147, id:36, text: "¡Todos alaban al poderoso faraón! Tu dinastía no tiene igual y los egipcios dirán tu nombre con gran reverencia desde ahora hasta el final de los tiempos." }
    { group:147, id:37, text: "¡Todos alaban al poderoso faraón! Tu dinastía no tiene igual y los egipcios dirán tu nombre con gran reverencia desde ahora hasta el final de los tiempos." }
    { group:147, id:38, text: "Bien hecho. La tumba de Tutmosis I está terminada. ¡Es un logro extraordinario! El faraón confía en que una tumba tan bellamente decorada complazca a los dioses y así aceleren su viaje a la otra vida." }
    { group:147, id:39, text: "¡Una hazaña admirable! Es poco común que unos trabajadores bajo tanta presión puedan crear un trabajo tan bello. La tumba de Tutankamón está sellada para toda la eternidad. ¡Sólo queda esperar que los ladrones herejes nunca descubran su lugar de descanso!" }
    { group:147, id:40, text: "¡Un trabajo excelente! Has conseguido proteger de forma adecuada las tumbas reales del Valle y has terminado la nueva tumba como se te ordenó. El faraón Seti está encantado con el magnífico trabajo de tus trabajadores." }
    { group:147, id:41, text: "¡Un trabajo bien hecho! Nuestro gran faraón, Ramsés II, no se equivocó cuando te eligió para supervisar el desarrollo comercial y militar de esta tierra. ¡Pero el peligro está en el aire! El ejército hitita ha vuelto a desafiar nuestro legítimo control sobre esta valiosa región." }
    { group:147, id:42, text: "La mano del faraón ha vuelto a aplastar a los odiosos hititas. ¡Grande es el júbilo de nuestro sabio y valiente líder, Ramsés II! Sin duda, tu magnífica victoria en esta dura batalla quedará grabada para siempre en los anales de la historia." }
    { group:147, id:43, text: "¡Un trabajo bien hecho! Ramsés II está encantado con el colosal monumento que has construido en su honor en Abu Simbel." }
    { group:147, id:44, text: "¡Bien hecho! A pesar de una serie de horribles plagas y desgracias aparentemente interminables, la gran tumba de nuestro anciano faraón está totalmente preparada. Su grandeza muestra nuestro aprecio por Ramsés II, sin duda uno de los mejores líderes de Egipto." }
    { group:147, id:45, text: "El sol ha disipado la nube de tormenta que había cubierto Egipto. ¡Nuestra alegría es mucha! El vil líder de los Libu y sus aliados del mar han huido al amparo de la noche. Su mal planeado intento para establecerse en nuestras costas ha sido aplastado. Es una suerte que un gran número de sus mujeres e hijos sean ahora nuestros avergonzados prisioneros." }
    { group:147, id:46, text: "¡Bien hecho! Tu valor y tenacidad en la batalla inspiraron a nuestras tropas a dar el máximo. Los execrables asirios han sido expulsados de Egipto sin compasión. Tus hazañas han llegado a oídos del faraón y está muy agradecido." }
    { group:147, id:47, text: "¡Ave al héroe de Tanis, protector de Egipto! Tus gloriosas victorias en tierra y en el mar han garantizado la independencia de Egipto. Los otrora poderosos persas ahora tiemblan al escuchar el nombre del faraón Achoris." }
    { group:147, id:48, text: "Lo has hecho bien. Tu sensato liderazgo y la cuidada planificación han convertido a Alejandría en el centro del comercio mediterráneo. Es una pena que Alejandro Magno no llegara a ver la capital de su imperio. Por los menos nos queda la satisfacción de saber que ahora está enterrado en él." }
    { group:147, id:49, text: "¡La metrópolis de Alejandría se ha convertido en un faro que ilumina el mundo! Su Gran Biblioteca no tiene rival como centro de conocimiento y el imponente faro de Pharos ya es una de las maravillas del mundo." }
    { group:147, id:50, text: "Tus poderosas legiones han aplastado a los seguidores de Ptolomeo XIII. Su cuerpo sin vida fue rescatado del Nilo como prueba de su muerte. El sitio ha sido levantado y Cleopatra ya tiene asegurado su trono. Para celebrar la victoria y consolidar aún más su relación, César y Cleopatra van a realizar un viaje por el Nilo abordo de la lujosa barcaza real." }
    { group:147, id:51, text: "Las maravillas de Alejandría y el destino de Egipto están en buenas manos bajo tu dirección. Como se esperaba, cuando por fin honraste a Marco Antonio con tu presencia, él te rindió el homenaje adecuado ya que buscaba tu ayuda económica para conseguir sus objetivos. De hecho, se enamoró de tal manera que ha venido a Alejandría para ser tu compañero y amante." }
    { group:147, id:52, text: "Gracias a la inmensa riqueza de Cleopatra y a la habilidad de Marco Antonio para la táctica militar, la flota de Octavio y sus veteranas legiones han sido dispersadas a los cuatro vientos. Los romanos esperan impacientes la triunfante llegada de Antonio y Cleopatra. Juntas, Roma Y Alejandría, gobernarán el Mediterráneo durante muchas generaciones." }
    { group:147, id:53, text: "Victoria del mapa a medida" }
    { group:147, id:54, text: "Lo has hecho bien, pero te esperan muchos otros desafíos en tu empeño por llegar a ser... ¡faraón!" }
    { group:148, id:0, text: "Puntuación de cultura" }
    { group:148, id:1, text: "Puntuación de prosperidad" }
    { group:148, id:2, text: "Puntuación de monumentos" }
    { group:148, id:3, text: "Puntuación de imperio" }
    { group:148, id:4, text: "Población final" }
    { group:148, id:5, text: "Fondos finales" }
    { group:148, id:6, text: "Monumentos erigidos" }
    { group:148, id:7, text: "La misión se ha terminado en" }
    { group:148, id:8, text: "Dificultad:" }
    { group:148, id:9, text: "Puntuación:" }
    { group:148, id:10, text: "Felicidades. Puedes volver atrás e intentar superar tu puntuación pulsando el botón \"Seleccionar una misión\"." }
    { group:148, id:11, text: "Lo hiciste mejor la última vez que jugaste esta misión." }
    { group:148, id:12, text: "¡Gran trabajo! ¡Has superado la última puntuación de esta misión!" }
    { group:148, id:13, text: "Has finalizado esta misión con éxito, pero [player_name] aún es el gobernante supremo de esta ciudad." }
    { group:148, id:14, text: "Has mejorado los logros de [player_name]." }
    { group:148, id:15, text: "meses" }
    { group:148, id:16, text: "¡Nos has defraudado! Tu puntuación no es digna de ser incluida entre las mejores familias." }
    { group:149, id:0, text: "Solicitudes generales" }
    { group:149, id:1, text: "Ciudad egipcia atacada" }
    { group:149, id:2, text: "Batalla lejana" }
    { group:149, id:3, text: "Festival" }
    { group:149, id:4, text: "Construcción" }
    { group:149, id:5, text: "Hambre" }
    { group:149, id:6, text: "Amenaza" }
    { group:150, id:0, text: "Ciudad egipcia salvada" }
    { group:150, id:1, text: "Batalla lejana ganada" }
    { group:150, id:2, text: "Batalla lejana perdida" }
    { group:150, id:3, text: "Agradecimiento" }
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
    { group:151, id:32, text: "Reina Merneith" }
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
    { group:151, id:57, text: "Reina Sobknefru" }
    { group:151, id:58, text: "Teti" }
    { group:151, id:59, text: "Unas" }
    { group:151, id:60, text: "Userkaf" }
    { group:151, id:61, text: "Userkara" }
    { group:151, id:62, text: "Weneg" }
    { group:151, id:63, text: "Ahmosis I" }
    { group:151, id:64, text: "Amenofis I" }
    { group:151, id:65, text: "Tutmosis I" }
    { group:151, id:66, text: "Tutmosis II" }
    { group:151, id:67, text: "Hatshepsut" }
    { group:151, id:68, text: "Tutmosis III" }
    { group:151, id:69, text: "Amenofis II" }
    { group:151, id:70, text: "Tutmosis IV" }
    { group:151, id:71, text: "Amenofis III" }
    { group:151, id:72, text: "Akenatón" }
    { group:151, id:73, text: "Neferneferuaten" }
    { group:151, id:74, text: "Smenkhare" }
    { group:151, id:75, text: "Tutankamón" }
    { group:151, id:76, text: "Ay" }
    { group:151, id:77, text: "Horemheb" }
    { group:151, id:78, text: "Ramsés I" }
    { group:151, id:79, text: "Seti I" }
    { group:151, id:80, text: "Ramsés II" }
    { group:151, id:81, text: "Merneptah" }
    { group:151, id:82, text: "Amenmes" }
    { group:151, id:83, text: "Seti II" }
    { group:151, id:84, text: "Siptah" }
    { group:151, id:85, text: "Reina Twosret" }
    { group:151, id:86, text: "Setnakhte" }
    { group:151, id:87, text: "Ramsés III" }
    { group:151, id:88, text: "Ramsés IV" }
    { group:151, id:89, text: "Ramsés V" }
    { group:151, id:90, text: "Ramsés VI" }
    { group:151, id:91, text: "Ramsés VII" }
    { group:151, id:92, text: "Ramsés VIII" }
    { group:151, id:93, text: "Ramsés IX" }
    { group:151, id:94, text: "Ramsés X" }
    { group:151, id:95, text: "Ramsés XI" }
    { group:151, id:96, text: "Piye" }
    { group:151, id:97, text: "Shabaka" }
    { group:151, id:98, text: "Shebitku" }
    { group:151, id:99, text: "Taharqa" }
    { group:151, id:100, text: "Tantamani" }
    { group:151, id:101, text: "Neferites I" }
    { group:151, id:102, text: "Psammutis" }
    { group:151, id:103, text: "Nefaarud I" }
    { group:151, id:104, text: "Hakoris" }
    { group:151, id:105, text: "Naknebef" }
    { group:151, id:106, text: "Alejandro el Magno" }
    { group:151, id:107, text: "Filipo Arrideo" }
    { group:151, id:108, text: "Alejandro IV" }
    { group:151, id:109, text: "Ptolomeo I" }
    { group:151, id:110, text: "Ptolomeo II" }
    { group:151, id:111, text: "Ptolomeo III" }
    { group:151, id:112, text: "Ptolomeo IV" }
    { group:151, id:113, text: "Ptolomeo V" }
    { group:151, id:114, text: "Ptolomeo VI" }
    { group:151, id:115, text: "Ptolomeo VII" }
    { group:151, id:116, text: "Ptolomeo VIII" }
    { group:151, id:117, text: "Ptolomeo IX" }
    { group:151, id:118, text: "Ptolomeo X" }
    { group:151, id:119, text: "Ptolomeo XI" }
    { group:151, id:120, text: "Ptolomeo XII" }
    { group:151, id:121, text: "Reina Berenice IV" }
    { group:151, id:122, text: "Ptolomeo XIII" }
    { group:151, id:123, text: "Cleopatra VII" }
    { group:151, id:124, text: "Ptolomeo XV" }
    { group:152, id:0, text: "Ninguna" }
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
    { group:153, id:0, text: "Parámetros de dificultad" }
    { group:153, id:1, text: "Muy fác." }
    { group:153, id:2, text: "Fácil" }
    { group:153, id:3, text: "Normal" }
    { group:153, id:4, text: "Difícil" }
    { group:153, id:5, text: "Muy dif." }
    { group:153, id:6, text: "Efectos de dioses desactivados" }
    { group:153, id:7, text: "Efectos de dioses activados" }
    { group:153, id:8, text: "Haz clic derecho para continuar" }
    { group:154, id:0, text: "Refugio de caza" }
    { group:154, id:1, text: "Aquí, los cazadores reúnen las piezas que se cobran entre los animales de la zona. Desde el refugio de caza se distribuyen las presas entre los almacenes o graneros." }
    { group:154, id:2, text: "La producción está al:" }
    { group:154, id:3, text: "." }
    { group:154, id:4, text: "El supervisor comercial ha decretado que la caza debe cesar." }
    { group:154, id:5, text: "Este refugio no tiene empleados." }
    { group:154, id:6, text: "Este refugio tiene todos los empleados que necesita. Los cazadores acechan a todas las manadas que pueden encontrar." }
    { group:154, id:7, text: "Este refugio funciona por debajo de su capacidad. Por consiguiente, la cantidad de alimento disminuirá." }
    { group:154, id:8, text: "Este refugio no tiene suficientes empleados y se tarda en conseguir carne más de lo debido." }
    { group:154, id:9, text: "Aquí trabaja muy poca gente, y la cantidad de alimento disminuye." }
    { group:154, id:10, text: "Casi sin empleados, en este refugio se encuentran muy pocos animales y se matan muchos menos. Puede ser una  temporada muy dura." }
    { group:154, id:11, text: "Los cazadores de este refugio están buscando presas." }
    { group:154, id:12, text: "Se tarda mucho tiempo en llevar la carne al refugio. Intenta acercarlo más al hábitat de los animales." }
    { group:154, id:13, text: "Carne almacenada," }
    { group:155, id:0, text: "Control de carretera" }
    { group:155, id:1, text: "Coloca controles de carretera para restringir el recorrido de los  patrulleros. La gente que vaya a destinos determinados (como los que empujan los carros o los compradores del bazar) puede pasar con libertad." }
    { group:156, id:0, text: "Acontecimiento libre" }
    { group:156, id:1, text: "Solicitud" }
    { group:156, id:2, text: "Invasión" }
    { group:156, id:3, text: "Terremoto" }
    { group:156, id:4, text: "Rebelión" }
    { group:156, id:5, text: "Cambiar de faraón" }
    { group:156, id:6, text: "Prob. de comercio marítimo" }
    { group:156, id:7, text: "Prob. de comercio terrestre" }
    { group:156, id:8, text: "Aumento de salarios" }
    { group:156, id:9, text: "Disminución de salarios" }
    { group:156, id:10, text: "Agua contaminada" }
    { group:156, id:11, text: "Derrumbamiento de una mina" }
    { group:156, id:12, text: "Inundación de un pozo" }
    { group:156, id:13, text: "Aumento de la demanda" }
    { group:156, id:14, text: "Disminución de la demanda" }
    { group:156, id:15, text: "Aumento de precio" }
    { group:156, id:16, text: "Disminución de precio" }
    { group:156, id:17, text: "Aumento del imperio" }
    { group:156, id:18, text: "Disminución del imperio" }
    { group:156, id:19, text: "Cambio en la ciudad" }
    { group:156, id:20, text: "Mensaje de evento" }
    { group:156, id:21, text: "Riada fallida" }
    { group:156, id:22, text: "Riada perfecta" }
    { group:156, id:23, text: "Regalo" }
    { group:156, id:24, text: "Plaga de langostas" }
    { group:156, id:25, text: "Plaga de ranas" }
    { group:156, id:26, text: "Granizada" }
    { group:156, id:27, text: "Río de sangre" }
    { group:156, id:28, text: "Ola de delincuencia" }
    { group:156, id:29, text: "Momia" }
    { group:157, id:0, text: "Osiris" }
    { group:157, id:1, text: "Ra" }
    { group:157, id:2, text: "Ptah" }
    { group:157, id:3, text: "Seth" }
    { group:157, id:4, text: "Bastet" }
    { group:157, id:5, text: "Hermi" }
    { group:157, id:6, text: "Jano" }
    { group:158, id:0, text: "Dios de la agricultura y la riada del Nilo" }
    { group:158, id:1, text: "Dios del imperio" }
    { group:158, id:2, text: "Dios de los artesanos" }
    { group:158, id:3, text: "Dios de la guerra y la oscuridad" }
    { group:158, id:4, text: "Diosa del hogar" }
    { group:158, id:5, text: "(Odontología)" }
    { group:158, id:6, text: "(Todo)" }
    { group:159, id:0, text: "Embarcadero - transbordador" }
    { group:159, id:1, text: "¡AVISO! Este embarcadero del transbordador no tiene un enlace al otro lado del río. Tan sólo pueden cruzar los emigrantes." }
    { group:159, id:2, text: "¡AVISO! El otro embarcadero del transbordador no tiene acceso por carretera. Tan sólo pueden cruzar los emigrantes." }
    { group:159, id:3, text: "¡AVISO! El otro embarcadero del transbordador tiene problemas de personal. Tan sólo pueden cruzar los emigrantes." }
    { group:160, id:0, text: "Enero" }
    { group:160, id:1, text: "Febrero" }
    { group:160, id:2, text: "Marzo" }
    { group:160, id:3, text: "Abril" }
    { group:160, id:4, text: "Mayo" }
    { group:160, id:5, text: "Junio" }
    { group:160, id:6, text: "Julio" }
    { group:160, id:7, text: "Agosto" }
    { group:160, id:8, text: "Septiembre" }
    { group:160, id:9, text: "Octubre" }
    { group:160, id:10, text: "Noviembre" }
    { group:160, id:11, text: "Diciembre" }
    { group:161, id:0, text: "Santuario de Osiris (agric.)" }
    { group:161, id:1, text: "Osiris fertiliza la tierra y hace que crezcan las cosechas. Aplácalo o prepárate para pasar hambre." }
    { group:161, id:2, text: "Santuario de Ra (imperio)" }
    { group:161, id:3, text: "Los mercaderes conocen muy bien el valor de tener contento a Ra. El comercio es más seguro y beneficioso con la bendición de Ra, y la ciudad goza de mayor consideración." }
    { group:161, id:4, text: "Santuario de Ptah (artesanía)" }
    { group:161, id:5, text: "Los trabajadores y los artesanos veneran a Ptah para que facilite su trabajo. Cuando Ptah está enfadado, ninguna industria se salva de la catástrofe." }
    { group:161, id:6, text: "Santuario de Seth (destrucción)" }
    { group:161, id:7, text: "Seth vigila a los soldados y les infunde valor en el combate. Ningún hombre se atreve a luchar sin la bendición de Seth." }
    { group:161, id:8, text: "Santuario de Bastet (hogar)" }
    { group:161, id:9, text: "Cuando Bastet no se siente complacida, nadie está a salvo en su casa. Hay quienes culpan a Bastet de las enfermedades." }
    { group:162, id:0, text: "Mina de oro" }
    { group:162, id:1, text: "La extracción de oro es la forma más rápida de llenar la tesorería de una ciudad. La ciudad que disponga de este valioso recurso es afortunada, porque su riqueza está asegurada." }
    { group:162, id:2, text: "La producción está al:" }
    { group:162, id:3, text: "." }
    { group:162, id:4, text: "El supervisor comercial ha ordenado que se detenga la extracción de oro." }
    { group:162, id:5, text: "Esta mina no tiene empleados. La producción se ha detenido." }
    { group:162, id:6, text: "Esta mina tiene todos los empleados que necesita y produce todo el oro posible." }
    { group:162, id:7, text: "Esta mina está trabajando por debajo de su capacidad. La producción podría ser un poco más eficaz si tuviera más trabajadores." }
    { group:162, id:8, text: "Esta mina no tiene suficiente personal. Produce menos oro del que podría." }
    { group:162, id:9, text: "En este edificio trabaja muy poca gente. Por consiguiente, la producción es lenta." }
    { group:162, id:10, text: "Casi no hay empleados, por lo que la extracción está prácticamente paralizada. De aquí saldrá muy poco oro." }
    { group:163, id:0, text: "Mina de piedras preciosas" }
    { group:163, id:1, text: "Extrae piedras preciosas para exportar o para convertirlas en joyas, el artículo de lujo básico de la ciudad." }
    { group:163, id:2, text: "La producción está al:" }
    { group:163, id:3, text: "." }
    { group:163, id:4, text: "El supervisor comercial ha decidido que la ciudad tiene suficientes piedras preciosas y ha detenido la extracción." }
    { group:163, id:5, text: "Esta mina no tiene empleados. La producción se ha detenido." }
    { group:163, id:6, text: "Esta mina tiene todos los empleados que necesita y produce todas las piedras preciosas posibles." }
    { group:163, id:7, text: "Esta mina funciona por debajo de su capacidad. La producción podría ser un poco más eficaz si hubiera más trabajadores." }
    { group:163, id:8, text: "Esta mina no tiene suficientes empleados. Produce menos piedras preciosas de las que podría." }
    { group:163, id:9, text: "En este edificio trabaja muy poca gente. Por consiguiente, la producción es lenta." }
    { group:163, id:10, text: "Casi no hay empleados, por lo que se extraen muy pocas piedras preciosas." }
    { group:164, id:0, text: "Parque de bomberos" }
    { group:164, id:1, text: "Los parques de bomberos envían bomberos por toda la ciudad para evitar los incendios y combatir los que se han desatado." }
    { group:164, id:2, text: "Nuestro bombero está patrullando." }
    { group:164, id:3, text: "Nuestro bombero se está preparando para el trabajo." }
    { group:164, id:4, text: "En la actualidad, nuestro plan de trabajo está completo. Nuestros bomberos siempre están fuera, recorriendo las calles." }
    { group:164, id:5, text: "Nos faltan unos cuantos bomberos. Tenemos huecos de un día o dos en nuestra zona de cobertura." }
    { group:164, id:6, text: "Tenemos poco personal, y tenemos huecos peligrosos de hasta una semana en nuestra agenda de servicios." }
    { group:164, id:7, text: "Tenemos muy poco personal. A veces, ningún bombero sale del parque durante dos semanas seguidas." }
    { group:164, id:8, text: "Sólo trabajamos con una persona. A veces transcurre un mes antes de que un bombero salga a patrullar." }
    { group:164, id:9, text: "Dado que este parque de bomberos no tiene personal, es más que posible que se declare un incendio en cualquier momento." }
    { group:165, id:0, text: "Muralla de ladrillos" }
    { group:165, id:1, text: "Las murallas frenan el avance de los invasores hacia la ciudad, pero no lo detienen. Las murallas gruesas son más fuertes y permiten patrullar a los guardias entre las torres." }
    { group:166, id:0, text: "Muralla" }
    { group:166, id:1, text: "Las murallas evitan el avance de los invasores hacia la ciudad. Éstos pueden destruir las murallas. Las murallas gruesas son más fuertes y permiten patrullar a los guardias entre las torres conectadas." }
    { group:167, id:0, text: "Portón de ladrillo" }
    { group:167, id:1, text: "Las murallas necesitan un portón para que los emigrantes y comerciantes puedan ir y venir con libertad." }
    { group:168, id:0, text: "Portón" }
    { group:168, id:1, text: "Las murallas necesitan un portón para que los emigrantes y comerciantes puedan ir y venir con libertad." }
    { group:169, id:0, text: "Torre de ladrillos" }
    { group:169, id:1, text: "Construye torres en las murallas a intervalos regulares o por lo menos en las zonas más vulnerables. Si las conectas a las carreteras, las torres recibirán vigías del reclutador de la ciudad. Los vigías de las torres lanzan jabalinas a los invasores cercanos y patrullan las murallas suficientemente gruesas." }
    { group:169, id:2, text: "Sin trabajadores no podemos apostar gente en las torres ni contratar guardias para patrullar las murallas." }
    { group:169, id:3, text: "Nuestros hombres están alerta y preparados para repeler cualquier ataque." }
    { group:169, id:4, text: "Tenemos personal de mantenimiento, pero necesitamos vigías de un reclutador para defender la ciudad." }
    { group:170, id:0, text: "Torre" }
    { group:170, id:1, text: "Construye torres en las murallas a intervalos regulares o por lo menos en las zonas más vulnerables. Si las conectas a las carreteras, las torres recibirán vigías del reclutador de la ciudad. Los vigías de las torres lanzan jabalinas a los invasores cercanos y patrullan las murallas suficientemente gruesas." }
    { group:170, id:2, text: "Sin trabajadores no podemos apostar hombres en las torres ni contratar guardias para patrullar las murallas." }
    { group:170, id:3, text: "Nuestros hombres están alerta y preparados para repeler cualquier ataque." }
    { group:170, id:4, text: "Tenemos personal de mantenimiento, pero necesitamos vigías de un reclutador para defender la ciudad." }
    { group:171, id:0, text: "Gremio de carpinteros" }
    { group:171, id:1, text: "Los carpinteros se reúnen aquí para contar anécdotas, intercambiar consejos sobre la profesión, buscar encargos y resolver sus problemas." }
    { group:171, id:2, text: "La producción está al:" }
    { group:171, id:3, text: "." }
    { group:171, id:4, text: "El supervisor comercial ha cerrado este gremio." }
    { group:171, id:5, text: "Este gremio no tiene empleados. La producción ha parado." }
    { group:171, id:6, text: "Este gremio tiene todos los empleados que necesita y trabaja ininterrumpidamente." }
    { group:171, id:7, text: "Este gremio trabaja por debajo de su capacidad. Por consiguiente, el trabajo será algo más lento." }
    { group:171, id:8, text: "Este gremio no tiene suficientes empleados y  proporciona menos carpinteros de los que podría." }
    { group:171, id:9, text: "Aquí trabaja muy poca gente. Hay que esperar mucho para obtener los servicios de un carpintero." }
    { group:171, id:10, text: "Casi sin empleados en este gremio, parece que habrá que esperar eternamente a que aparezca un carpintero." }
    { group:171, id:11, text: "Este taller necesita madera." }
    { group:171, id:12, text: "Madera almacenada," }
    { group:172, id:0, text: "Gremio de albañiles" }
    { group:172, id:1, text: "Los albañiles se reúnen aquí para contar anécdotas, intercambiar consejos sobre su profesión, buscar encargos y hacer planes para el futuro." }
    { group:172, id:2, text: "La producción está al:" }
    { group:172, id:3, text: "." }
    { group:172, id:4, text: "El supervisor comercial ha cerrado este gremio." }
    { group:172, id:5, text: "Este gremio no tiene empleados. No es posible colocar ladrillos." }
    { group:172, id:6, text: "Este gremio tiene todos los empleados que necesita. Los albañiles pueden trabajar con máxima eficacia." }
    { group:172, id:7, text: "Este gremio trabaja por debajo de su capacidad. Por consiguiente, el trabajo será algo más lento." }
    { group:172, id:8, text: "Este gremio no tiene suficientes empleados y proporciona menos albañiles de los que podría." }
    { group:172, id:9, text: "Aquí trabaja muy poca gente. Hay una espera considerable para obtener los servicios de un albañil." }
    { group:172, id:10, text: "Casi sin empleados en este gremio, parece que habrá que esperar eternamente a que aparezca un albañil." }
    { group:172, id:11, text: "Este taller necesita ladrillos." }
    { group:172, id:12, text: "Ladrillos almacenados," }
    { group:173, id:0, text: "Gremio de canteros" }
    { group:173, id:1, text: "Los canteros se reúnen aquí para contar anécdotas, intercambiar consejos sobre su profesión, buscar encargos y hacer planes para el futuro." }
    { group:173, id:2, text: "La producción está al:" }
    { group:173, id:3, text: "." }
    { group:173, id:4, text: "El supervisor comercial ha cerrado este gremio." }
    { group:173, id:5, text: "Este gremio no tiene empleados. No se puede tallar la roca." }
    { group:173, id:6, text: "Los canteros pueden trabajar con máxima eficacia." }
    { group:173, id:7, text: "Este gremio trabaja por debajo de su capacidad. Por consiguiente, el trabajo será algo más lento." }
    { group:173, id:8, text: "Este gremio no tiene suficientes empleados y proporciona menos canteros de los que podría." }
    { group:173, id:9, text: "Aquí trabaja muy poca gente. Hay una espera considerable para obtener los servicios de un cantero." }
    { group:173, id:10, text: "Casi sin empleados en este gremio, parece que habrá que esperar eternamente para que un cantero se incorpore al trabajo." }
    { group:173, id:11, text: "Este gremio proporciona experimentados trabajadores para los monumentos. No necesita su propio suministro de piedra." }
    { group:173, id:12, text: "Piedra almacenada," }
    { group:174, id:0, text: "Dársena de transporte" }
    { group:174, id:1, text: "Los barcos de transporte, construidos en los astilleros, se amarran aquí entre encargo y encargo. El batallón necesita barcos de transporte para navegar por el Nilo." }
    { group:174, id:2, text: "Nuestro transporte está en el puerto." }
    { group:174, id:3, text: "Nuestro transporte está realizando un trabajo." }
    { group:175, id:0, text: "Dársena de barcos de guerra" }
    { group:175, id:1, text: "Un barco de guerra atraca aquí entre batalla y batalla. Cualquier ciudad del Nilo debe tener al menos un par de barcos de defensa preparados." }
    { group:175, id:2, text: "Nuestro barco de guerra está en el puerto." }
    { group:175, id:3, text: "Nuestro barco de guerra está defendiendo a la ciudad de una invasión." }
    { group:176, id:0, text: "Palacio de justicia" }
    { group:176, id:1, text: "Los palacios de justicia envían jueces, que ayudan a reducir la delincuencia haciendo que todos los conflictos se diriman en un litigio justo. Las cámaras del palacio de justicia guardan parte del erario de la ciudad." }
    { group:176, id:2, text: "Este palacio de justicia no tiene ningún empleado, de modo que los ciudadanos resuelven sus disputas como pueden." }
    { group:176, id:3, text: "Hay tan pocos jueces disponibles que los demandantes tienen la impresión de que los veredictos se dictan al azar." }
    { group:176, id:4, text: "Con sólo la mitad de los trabajadores que necesita, este palacio de justicia emite a veces veredictos apresurados." }
    { group:176, id:5, text: "Como sólo le faltan unos pocos empleados, este palacio de justicia tiene muy pocos casos atrasados." }
    { group:176, id:6, text: "Es palacio de justicia tiene todo el personal que necesita para atender las quejas de los ciudadanos y tomar decisiones prudentes." }
    { group:176, id:7, text: "El juez está fuera, resolviendo disputas." }
    { group:176, id:8, text: "El juez está en su despacho." }
    { group:176, id:9, text: "Las cámaras tienen" }
    { group:177, id:0, text: "Esta tierra es de regadío." }
    { group:177, id:1, text: "Esta tierra no es de regadío." }
    { group:177, id:2, text: "Las próximas inundaciones llegarán en" }
    { group:177, id:3, text: "Esta zona ofrece tierra muy fértil, ahora que el río ha vuelto a su cauce." }
    { group:177, id:4, text: "Esta zona ofrecerá tierra muy fértil una vez que el río vuelva a su cauce." }
    { group:177, id:5, text: "Esta granja necesita empleados, que se pueden preparar en un campo de trabajo." }
    { group:177, id:6, text: "Esta granja tiene todos los empleados que necesita, y están trabajando en los campos." }
    { group:178, id:0, text: "terminar." }
    { group:178, id:1, text: "Los trabajadores ya terminan la fachada de la pirámide." }
    { group:178, id:2, text: "Esta tarea es" }
    { group:178, id:3, text: "Los trabajadores están despejando el lugar de construcción de la pirámide" }
    { group:178, id:4, text: "Los trabajadores están despejando el lugar de construcción de la mastaba" }
    { group:178, id:5, text: "Los trabajadores están haciendo surcos en la roca para retener el agua" }
    { group:178, id:6, text: "Los surcos de la base de la pirámide se están llenando con agua" }
    { group:178, id:7, text: "Se está vaciando el agua y se están haciendo marcas para establecer el nivel de visión." }
    { group:178, id:8, text: "Se está cortando la roca para nivelarla." }
    { group:178, id:9, text: "Las ranuras se están llenando con escombros" }
    { group:178, id:10, text: "La base ha sido nivelada, ahora se está construyendo la tumba." }
    { group:178, id:11, text: "La base ha sido nivelada y se está colocando el tejado de la tumba." }
    { group:178, id:12, text: "Capataz de construcción" }
    { group:178, id:13, text: "Necesitaré peones para hacer este trabajo. Tienes que construir campos de trabajo." }
    { group:178, id:14, text: "No hay canteros disponibles para trabajar en este monumento. Si quieres avanzar, ¡construye un gremio de canteros inmediatamente!" }
    { group:178, id:15, text: "¿Cómo quieres que contrate albañiles, si en esta ciudad no hay gremios de albañiles?" }
    { group:178, id:16, text: "Debo tener acceso a un gremio de carpinteros si quiero terminar este monumento." }
    { group:178, id:17, text: "Estoy esperando a que lleguen peones para trabajar. Tal vez debas visitar los campos de trabajo y ver si hay algún problema." }
    { group:178, id:18, text: "Estoy esperando a que vengan canteros para trabajar. Tal vez una visita al gremio de los canteros indique si hay problemas." }
    { group:178, id:19, text: "Estoy esperando que los albañiles se incorporen al trabajo. Por si hay algún problema, sería conveniente hacer una visita al gremio de albañiles." }
    { group:178, id:20, text: "Necesito un carpintero inmediatamente. Es posible que haya algún problema en el gremio de carpinteros." }
    { group:178, id:21, text: "Mis trabajadores están esperando a que un carpintero construya una rampa para poder llegar al siguiente nivel." }
    { group:178, id:22, text: "Mis canteros necesitan un suministro de piedra normal para este monumento." }
    { group:178, id:23, text: "Mis canteros necesitan un suministro de caliza para este monumento." }
    { group:178, id:24, text: "Mis canteros necesitan un suministro de arenisca para este monumento." }
    { group:178, id:25, text: "Mis canteros necesitan un suministro de granito para este monumento." }
    { group:178, id:26, text: "A menos que importes más mármol, los canteros no podrán terminar nunca este monumento." }
    { group:178, id:27, text: "Mis albañiles necesitan un suministro de ladrillos para este monumento." }
    { group:178, id:28, text: "Mis carpinteros necesitan un suministro de madera para este monumento." }
    { group:178, id:29, text: "Los canteros están preparados para añadir cobre al tejado, si es que llega. Debes extraer o importar más." }
    { group:178, id:30, text: "Los trabajadores están despejando y nivelando el lugar de construcción. Después, necesitaremos mucha piedra normal y caliza para completar el trabajo." }
    { group:178, id:31, text: "Parece que todo va bien y la pirámide sube cada vez más." }
    { group:178, id:32, text: "Los canteros están haciendo el trabajo de tallado. No necesitamos más caliza para terminar este trabajo." }
    { group:178, id:33, text: "Los trabajadores están despejando y nivelando el lugar de construcción. Después, necesitaremos muchos ladrillos y caliza para completar el trabajo." }
    { group:178, id:34, text: "Parece que todo va bien y la pirámide continua subiendo cada vez más." }
    { group:178, id:35, text: "Los canteros están haciendo el trabajo de tallado. No necesitamos más ladrillos ni caliza para terminar este trabajo." }
    { group:178, id:36, text: "Los trabajadores están despejando y nivelando el lugar de la construcción. Después, necesitaremos mucha piedra normal para construir este monumento." }
    { group:178, id:37, text: "Parece que todo va bien y la pirámide continua subiendo poco a poco." }
    { group:178, id:38, text: "¡Por fin está terminada la pirámide!" }
    { group:178, id:39, text: "Los trabajadores están despejando el lugar de construcción. Después, necesitaremos muchos ladrillos para la mastaba." }
    { group:178, id:40, text: "Parece que todo va bien. Esta mastaba estará terminada en poco tiempo." }
    { group:178, id:41, text: "La mastaba está terminada." }
    { group:178, id:42, text: "Por fin tenemos todo el granito que necesitamos. Cuando los carpinteros hayan terminado de construir el andamiaje, los canteros pueden empezar a tallar el obelisco." }
    { group:178, id:43, text: "Mis canteros trabajan duro en la talla del imponente obelisco." }
    { group:178, id:44, text: "¡El obelisco está terminado!" }
    { group:178, id:45, text: "Los canteros está tallando la estructura de la esfinge." }
    { group:178, id:46, text: "Los canteros están tallando los detalles de la esfinge." }
    { group:178, id:47, text: "Los trabajadores están terminando la esfinge y la están pintando." }
    { group:178, id:48, text: "¡La esfinge está terminada!" }
    { group:178, id:49, text: "La carpintería es" }
    { group:178, id:50, text: "El trabajo de los canteros es" }
    { group:178, id:51, text: "En esta época, la mayoría de los campesinos está trabajando en la granjas de los terrenos aluviales." }
    { group:178, id:52, text: "El acceso a este monumento está bloqueado." }
    { group:178, id:53, text: "Ahora que tenemos suficiente arenisca, podemos comenzar a construir el templo del Sol. Mis trabajadores están despejando el lugar." }
    { group:178, id:54, text: "Una vez que los carpinteros terminen la construcción del andamiaje, los canteros pueden comenzar a tallar el obelisco central del templo del Sol." }
    { group:178, id:55, text: "Los canteros están tallando el obelisco central. Cuando lo hayan terminado, necesitaremos más arenisca para terminar el resto del templo del Sol." }
    { group:178, id:56, text: "Tan pronto como terminemos el vestíbulo, el muro y la parte delantera, este monumento estará terminado." }
    { group:178, id:57, text: "¡El templo del Sol está terminado!" }
    { group:178, id:58, text: "Ahora que tenemos suficiente arenisca, podemos comenzar a construir el monumento. Los trabajadores están despejando el lugar." }
    { group:178, id:59, text: "Los canteros están trabajando duro para terminar este mausoleo. Con un suministro continuado de arenisca, no creo que haya ningún problema." }
    { group:178, id:60, text: "El mausoleo está terminado." }
    { group:178, id:61, text: "Construcción: [monument_name] está al [percent_complete]" }
    { group:178, id:62, text: "Aún no se ha colocado en su lugar ninguna hilada." }
    { group:178, id:63, text: "Se ha colocado una hilada completa." }
    { group:178, id:64, text: "Se han colocado [number_courses_complete] hiladas." }
    { group:178, id:65, text: "La hilada actual necesita [quantity_needed_current_course_main] ([number_loads_current_course_main]) para estar terminada." }
    { group:178, id:66, text: "La hilada actual necesita [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) para estar terminada." }
    { group:178, id:67, text: "La hilada actual necesita [quantity_needed_current_course_main] ([number_loads_current_course_main]) y [quantity_needed_current_course_secondary] ([number_loads_current_course_secondary]) para estar terminada." }
    { group:178, id:68, text: "[monument_name] necesitará [quantity_needed_remainder_main] ([number_loads_remainder_main]) adicionales." }
    { group:178, id:69, text: "[monument_name] necesitará [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary]) adicionales." }
    { group:178, id:70, text: "[monument_name] necesitará [quantity_needed_remainder_main] ([number_loads_remainder_main]) y [quantity_needed_remainder_secondary] ([number_loads_remainder_secondary])." }
    { group:178, id:71, text: "[monument_name] se ha construido y contiene un total de [quantity_total_main]." }
    { group:178, id:72, text: "[monument_name] se ha construido y contiene un total de [quantity_total_main] y [quantity_total_secondary]." }
    { group:178, id:73, text: "La mastaba" }
    { group:178, id:74, text: "La pirámide" }
    { group:178, id:75, text: "La pirámide escalonada" }
    { group:178, id:76, text: "La pirámide romboidal" }
    { group:178, id:77, text: "La pirámide de ladrillos" }
    { group:178, id:78, text: "El obelisco" }
    { group:178, id:79, text: "La esfinge" }
    { group:178, id:80, text: "El templo del sol" }
    { group:178, id:81, text: "La Biblioteca de Alejandría" }
    { group:178, id:82, text: "El Abu Simbel" }
    { group:178, id:83, text: "La tumba funeraria real pequeña" }
    { group:178, id:84, text: "La tumba funeraria real mediana" }
    { group:178, id:85, text: "La tumba funeraria real grande" }
    { group:178, id:86, text: "La tumba funeraria real grandiosa" }
    { group:178, id:87, text: "El Caesareum" }
    { group:178, id:88, text: "El Faro" }
    { group:178, id:89, text: "El mausoleo" }
    { group:178, id:90, text: "bloques de piedra lisa" }
    { group:178, id:91, text: "bloques de piedra caliza" }
    { group:178, id:92, text: "bloques de granito" }
    { group:178, id:93, text: "bloques de arenisca" }
    { group:178, id:94, text: "ladrillos" }
    { group:178, id:95, text: "bloques de mármol" }
    { group:178, id:96, text: "lingotes de cobre" }
    { group:178, id:97, text: "Este mausoleo necesita los servicios de un carpintero" }
    { group:178, id:98, text: "El supervisor comercial se niega a entregar piedra normal a mis trabajadores. Afirma que diste órdenes de almacenarla. No le creo, pero tal vez debas hablar con él." }
    { group:178, id:99, text: "Tu supervisor comercial dice que le ordenaste almacenar piedra caliza. A menos que hables con él, mis trabajadores nunca recibirán ningún envío." }
    { group:178, id:100, text: "¿De verdad ordenaste al supervisor comercial que almacenara arenisca? No autorizará que ningún cargamento salga de los almacenes." }
    { group:178, id:101, text: "¿Puedes ordenar a tu supervisor comercial que deje de almacenar mármol blanco? Es necesario para el monumento." }
    { group:178, id:102, text: "Tu supervisor comercial dice que le ordenaste almacenar granito. A menos que hables con él, mis trabajadores nunca recibirán ningún envío." }
    { group:178, id:103, text: "¡Tu supervisor comercial se atreve a culparte del paro del trabajo! Afirma que diste la orden de almacenar ladrillos." }
    { group:178, id:104, text: "El supervisor comercial dice que le has ordenado almacenar cobre. Seguro que tienes una buena razón para hacerlo, pero mis hombres no pueden seguir trabajando en el monumento sin esa materia." }
    { group:178, id:105, text: "Al faraón no le hará gracia que la historia de su vida no se muestre de la forma más elegante. Si no hay gremio de artesanos, ¿quién esperas que decore la tumba?" }
    { group:178, id:106, text: "Una tumba algo sosa, ¿verdad? Así se va a quedar, ¡a menos que aparezcan pronto algunos artesanos! Siempre he pensado que eran unos holgazanes. Será mejor que descubras porqué se retrasan" }
    { group:178, id:107, text: "Sin mármol nuestros experimentados canteros no pueden hacer nada. Es una verdadera pena, ya que me gustaría verlos más ocupados. Sería mejor que te aseguraras de que se importa mármol cuanto antes." }
    { group:178, id:108, text: "Este tejado tendrá más goteras que un colador, si no conseguimos cobre. Si no puedes extraerlo, será mejor que importes algo. ¡Cuanto antes lo tenga, antes se terminará el monumento!" }
    { group:178, id:109, text: "Los trabajadores están despejando y nivelando la tierra. Ahora es un buen momento para comenzar a almacenar una cantidad importante de mármol." }
    { group:178, id:110, text: "El trabajo avanza muy bien. Los trabajadores disponen de todos los suministros que necesitan." }
    { group:178, id:111, text: "Es difícil de creer, pero el supervisor comercial me ha comunicado que se está almacenando mármol en los almacenes. Si no hay mármol, ¿cómo esperas que el trabajo continúe?" }
    { group:178, id:112, text: "Me he enterado por fuentes fidedignas de que se está almacenando granito. ¿Esperas que consiga lo que necesito en las arenas del Nilo? Será mejor que pongas granito a disposición de mis canteros inmediatamente." }
    { group:178, id:113, text: "¿Cómo esperas que se termine el tejado de esta gran estructura sin cobre? Puede parecer increíble, pero tu supervisor comercial me ha dicho que lo está almacenando." }
    { group:178, id:114, text: "Esperamos peones para despejar la tierra." }
    { group:178, id:115, text: "Una vez despejada la tierra, los canteros están construyendo los cimientos." }
    { group:178, id:116, text: "Los cimientos están terminados y podemos comenzar el suelo." }
    { group:178, id:117, text: "Terminado el suelo, estamos construyendo algunas columnas." }
    { group:178, id:118, text: "Lo siguiente es construir el tejado. Las columnas están terminadas." }
    { group:178, id:119, text: "Necesitamos cobre para terminar el tejado y que brille como el sol." }
    { group:178, id:120, text: "Estamos dando los toques finales a la Biblioteca." }
    { group:178, id:121, text: "La Biblioteca de Alejandría está terminada y es el centro de saber del mundo conocido." }
    { group:178, id:122, text: "Los peones trabajan duro despejando la tierra para el Caesareum." }
    { group:178, id:123, text: "Con la tierra preparada, los canteros están levantando unos sólidos cimientos." }
    { group:178, id:124, text: "Nuestros cansados canteros han terminado los cimientos. Pero no hay descanso para ellos, ha comenzado la construcción del templo." }
    { group:178, id:125, text: "Terminado el templo central, ¡comienza la construcción del patio!" }
    { group:178, id:126, text: "¡De los patios a los pórticos! Nuestros hábiles canteros han terminado el patio y han comenzado con el pórtico." }
    { group:178, id:127, text: "Los canteros han comenzado a poner el tejado en los pilares del pórtico." }
    { group:178, id:128, text: "Todas las secciones de tejado están colocadas sobre los pórticos." }
    { group:178, id:129, text: "Se ha finalizado la majestuosa entrada del Caesareum." }
    { group:178, id:130, text: "Los canteros han terminado el interior del Caesareum y han pasado a construir los obeliscos de granito que adornan el exterior del edificio." }
    { group:178, id:131, text: "El Caesareum está terminado y celebra la unión de Egipto y Roma." }
    { group:178, id:132, text: "Los peones han comenzado la ardua tarea de despejar la tierra." }
    { group:178, id:133, text: "Los canteros están muy ocupados con los cimientos del faro." }
    { group:178, id:134, text: "Los cimientos están casi terminados y se está colocando el suelo de parqué." }
    { group:178, id:135, text: "Terminando el suelo de parqué, los canteros han comenzado a construir el primer nivel del faro." }
    { group:178, id:136, text: "Los canteros no tienen tiempo de admirar el trabajo del primer nivel, ya que pronto comenzará la construcción del nivel octogonal." }
    { group:178, id:137, text: "El faro comienza a tomar forma. El nivel octogonal está terminado y los canteros comenzarán la cúpula pronto." }
    { group:178, id:138, text: "Ya se ha colocado la última pieza del faro, pero el monumento no estará terminado hasta que se hayan quitado los andamios. Ese trabajo comienza ahora." }
    { group:178, id:139, text: "Se han quitado la mayoría de los andamios y el faro está casi terminado." }
    { group:178, id:140, text: "El faro de Pharos está terminado y brilla como un sol sobre la parte oriental del Mediterráneo." }
    { group:178, id:141, text: "En el Abu Simbel se trabaja duro. Asegúrate de que los carpinteros tienen mucha madera para construir los andamios de manera adecuada." }
    { group:178, id:142, text: "Las impresionantes figuras de Ramsés II reciben a quien llega a Egipto desde el sur." }
    { group:178, id:143, text: "Los artesanos y los canteros se niegan a ir a la tumba funeraria real sin lámparas. ¡Está muy oscuro!" }
    { group:178, id:144, text: "Los artesanos y los canteros trabajan duro y la construcción de la tumba funeraria real va muy bien. Recuerda que debes facilitar arcilla y pintura al gremio de artesanos para asegurar que todo avanza sin problemas." }
    { group:178, id:145, text: "La tumba funeraria real está terminada. Sólo faltan las provisiones funerarias que el fallecido necesitará en el Campo de cañas." }
    { group:178, id:146, text: "La tumba funeraria real oculta ya está preparada para el faraón. ¡Que Horus proteja la tumba y castigue a aquel que ose profanarla!" }
    { group:178, id:147, text: "Lámparas:" }
    { group:178, id:148, text: "Los trabajadores no pueden llegar hasta la entrada de la tumba. Averigua qué está bloqueando la entrada." }
    { group:178, id:149, text: "Los trabajadores no pueden llegar al andamiaje del monumento. Averigua qué les bloquea el acceso." }
    { group:179, id:0, text: "Campo de trabajo" }
    { group:179, id:1, text: "Este edificio cobija a los trabajadores que no pueden trabajar en las granjas de los terrenos aluviales ni en los monumentos." }
    { group:179, id:2, text: "Este edificio necesita empleados para instruir a los trabajadores." }
    { group:179, id:3, text: "Estamos instruyendo a los trabajadores tan deprisa como podemos." }
    { group:179, id:4, text: "Nuestros trabajadores han salido a buscar empleo." }
    { group:179, id:5, text: "Nuestros trabajadores están trabajando en las granjas de los terrenos aluviales." }
    { group:179, id:6, text: "Nuestros trabajadores están trabajando en los monumentos." }
    { group:179, id:7, text: "Nuestros trabajadores están trabajando en las granjas de los terrenos aluviales y en los monumentos." }
    { group:180, id:0, text: "Fábricas de ladrillos" }
    { group:180, id:1, text: "Aquí se fabrican adobes con arcilla y paja." }
    { group:180, id:2, text: "La producción está al:" }
    { group:180, id:3, text: "." }
    { group:180, id:4, text: "El supervisor comercial ha ordenado suspender la producción de ladrillos." }
    { group:180, id:5, text: "Este taller no tiene empleados. La producción se ha detenido." }
    { group:180, id:6, text: "Esta taller tiene todos los empleados que necesita. Produce ladrillos a pleno rendimiento." }
    { group:180, id:7, text: "Este taller funciona por debajo de su capacidad. Por consiguiente, la producción de ladrillos será un poco más lenta." }
    { group:180, id:8, text: "Este taller no tiene suficientes empleados y se tarda en producir ladrillos más de lo debido." }
    { group:180, id:9, text: "Aquí trabaja muy poca gente, por lo que la producción de ladrillos es muy lenta." }
    { group:180, id:10, text: "Casi sin empleados, la producción de este taller está prácticamente parada. Producirá pocos ladrillos durante el próximo año." }
    { group:180, id:11, text: "Este taller necesita arcilla, de un almacén o de un pozo, para producir ladrillos." }
    { group:180, id:12, text: "Este taller necesita paja, de un almacén o de una granja de cereales, para producir ladrillos." }
    { group:180, id:13, text: "Arcilla:" }
    { group:180, id:14, text: "Paja:" }
    { group:181, id:0, text: "Granja de cebada" }
    { group:181, id:1, text: "La cebada es el principal ingrediente para hacer cerveza, sin la que la civilización no podría existir." }
    { group:181, id:2, text: "La producción está al:" }
    { group:181, id:3, text: "." }
    { group:181, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de cebada.." }
    { group:181, id:5, text: "Esta granja no tiene empleados. La tierra está estéril." }
    { group:181, id:6, text: "Esta granja tiene todo el personal que necesita. Saca el máximo beneficio de la tierra cultivada." }
    { group:181, id:7, text: "Esta granja está funcionando por debajo de su capacidad máxima.  Sería mas productiva si tuviese mas trabajadores." }
    { group:181, id:8, text: "Esta granja no tiene suficientes empleados. Sus trabajadores tardan mucho en cultivar cebada." }
    { group:181, id:9, text: "Aquí trabajan tan pocos granjeros que apenas tenemos suficiente cebada para una cerveza sin alcohol." }
    { group:181, id:10, text: "Con tan pocos granjeros, la producción de trigo está prácticamente detenida." }
    { group:181, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:181, id:12, text: "La tierra es" }
    { group:181, id:13, text: "fértil." }
    { group:181, id:14, text: "La próxima cosecha de cebada es en" }
    { group:182, id:0, text: "Granja de garbanzos" }
    { group:182, id:1, text: "Los garbanzos son una excelente fuente de proteínas y son muy habituales en la dieta de nuestros habitantes." }
    { group:182, id:2, text: "La producción está al:" }
    { group:182, id:3, text: "." }
    { group:182, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de garbanzos." }
    { group:182, id:5, text: "Esta granja no tiene empleados. La tierra está estéril." }
    { group:182, id:6, text: "Esta granja tiene todos los trabajadores que necesita. Dada su fertilidad, obtiene el máximo beneficio." }
    { group:182, id:7, text: "Esta granja está funcionando por debajo de su capacidad máxima.  Sería mas productiva si tuviese mas trabajadores." }
    { group:182, id:8, text: "Esta granja no tiene suficientes empleados. Sus trabajadores tardan mucho en cultivar garbanzos." }
    { group:182, id:9, text: "Aquí trabajan muy pocos granjeros. Por consiguiente, la producción de garbanzos es lenta." }
    { group:182, id:10, text: "Con tan pocos granjeros, la producción de trigo está prácticamente detenida." }
    { group:182, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:182, id:12, text: "La tierra es" }
    { group:182, id:13, text: "fértil." }
    { group:182, id:14, text: "La próxima cosecha de garbanzos es en" }
    { group:183, id:0, text: "Granja de higos" }
    { group:183, id:1, text: "Los higos son muy importantes en una dieta equilibrada." }
    { group:183, id:2, text: "La producción está al:" }
    { group:183, id:3, text: "." }
    { group:183, id:4, text: "El supervisor comercial ha ordenado suspender el cultivo de higos." }
    { group:183, id:5, text: "Esta granja no tiene empleados. La tierra está estéril." }
    { group:183, id:6, text: "Esta granja tiene todos los trabajadores que necesita. Saca el máximo provecho a la fertilidad de la tierra." }
    { group:183, id:7, text: "Esta granja está funcionando por debajo de su capacidad máxima.  Sería mas productiva si tuviese mas trabajadores." }
    { group:183, id:8, text: "Esta granja no tiene suficientes trabajadores. Se tarda mucho en cultivar higos." }
    { group:183, id:9, text: "Aquí trabajan muy pocos granjeros. Por consiguiente, la producción de higos es lenta." }
    { group:183, id:10, text: "Con tan pocos granjeros, la producción de trigo está prácticamente detenida." }
    { group:183, id:11, text: "Estas tierras han sufrido una plaga reciente de langostas, por lo que tardarán tiempo en recuperarse." }
    { group:183, id:12, text: "La tierra es" }
    { group:183, id:13, text: "fértil." }
    { group:183, id:14, text: "La próxima cosecha de higos es en" }
    { group:184, id:0, text: "Transporte" }
    { group:184, id:1, text: "Barco de guerra" }
    { group:184, id:2, text: "Resistencia del casco" }
    { group:184, id:3, text: "Muy fuerte" }
    { group:184, id:4, text: "Fuertes" }
    { group:184, id:5, text: "Buena" }
    { group:184, id:6, text: "Mediano" }
    { group:184, id:7, text: "Regular" }
    { group:184, id:8, text: "Débil" }
    { group:184, id:9, text: "Mantener la posición" }
    { group:184, id:10, text: "Cuando se da esta orden, el barco permanece en posición, bloqueando el paso a todos los barcos enemigos mientras permanezca a flote." }
    { group:184, id:11, text: "Entablar combate con los enemigos cercanos" }
    { group:184, id:12, text: "Al recibir esta orden, el barco de guerra protege una pequeña zona. Se mueve y ataca a soldados o barcos enemigos que la invadan." }
    { group:184, id:13, text: "Buscar y destruir a todos los enemigos" }
    { group:184, id:14, text: "Cuando tiene esta orden, el barco de guerra busca soldados y barcos enemigos por todas partes y ataca a los que consigue alcanzar." }
    { group:184, id:15, text: "Reparar" }
    { group:184, id:16, text: "El barco vuelve al astillero para las reparaciones. Si un barco está muy dañado, su capitán pondrá rumbo al astillero por propia iniciativa." }
    { group:184, id:17, text: "Volver a la dársena" }
    { group:184, id:18, text: "Ordena al barco volver a su dársena, en la que su tripulación podrá descansar y recuperar ánimos." }
    { group:184, id:19, text: "Mantener la posición" }
    { group:184, id:20, text: "Cuando se da esta orden, el barco permanece en posición a toda costa. Si recibe un ataque, puede que no esté a flote mucho tiempo." }
    { group:184, id:21, text: "Evitar a los enemigos" }
    { group:184, id:22, text: "El capitán de este barco ha recibido la orden de evitar. Mientras no le digan lo contrario, tiene que evitar el contacto con el enemigo a toda costa." }
    { group:184, id:23, text: "Embarcar" }
    { group:184, id:24, text: "Esta orden da instrucciones al capitán del barco para que recoja a una compañía de soldados para transportarla." }
    { group:184, id:25, text: "Desembarcar" }
    { group:184, id:26, text: "Esta orden da instrucciones al capitán para que deje en tierra una compañía de soldados." }
    { group:184, id:27, text: "Fatiga de la tripulación" }
    { group:184, id:28, text: "Descansada" }
    { group:184, id:29, text: "Cansada" }
    { group:184, id:30, text: "Agotada" }
    { group:184, id:31, text: "Compañía de arqueros," }
    { group:184, id:32, text: "Compañía de carros," }
    { group:184, id:33, text: "Compañía de infantería," }
    { group:184, id:34, text: "a bordo" }
    { group:185, id:0, text: "Taller de carros" }
    { group:185, id:1, text: "Aquí, los expertos artesanos fabrican los carros de combate, una de las armas más mortíferas de Egipto." }
    { group:185, id:2, text: "La producción está al:" }
    { group:185, id:3, text: "." }
    { group:185, id:4, text: "El supervisor comercial ha decretado el cese de la producción de carros." }
    { group:185, id:5, text: "Esta fábrica de carros no tiene empleados y no puede fabricar nada." }
    { group:185, id:6, text: "Esta fábrica de carros tiene todo el personal que necesita y produce suficientes carros de alta calidad." }
    { group:185, id:7, text: "Esta fábrica de carros podría contratar a más trabajadores para alcanzar la producción posible de carros." }
    { group:185, id:8, text: "Este fabricante de carros no tiene suficientes empleados y produce carros más lentamente de lo debido." }
    { group:185, id:9, text: "En este taller de carros trabaja muy poca gente. Por consiguiente, la producción de carros es lenta." }
    { group:185, id:10, text: "Esta fábrica de carros no tiene casi empleados y producirá pocos carros durante el próximo año." }
    { group:185, id:11, text: "Este taller no producirá carros sin un cargamento de madera, ya sea de un almacén o de una serrería." }
    { group:185, id:12, text: "Madera almacenada," }
    { group:187, id:0, text: "Desconocido" }
    { group:187, id:1, text: "Deidad local" }
    { group:187, id:2, text: "Dios protector" }
    { group:188, id:0, text: "Plaza de festivales" }
    { group:188, id:1, text: "Cuando des instrucciones al supervisor de templos para organizar un festival en honor de uno de los dioses, los ciudadanos se reunirán aquí para participar en él." }
    { group:188, id:2, text: "Celebra un festival para alegrar a la gente y aplacar a los dioses." }
    { group:188, id:3, text: "Actualmente hay un festival en marcha" }
    { group:189, id:0, text: "Altar de Sebek" }
    { group:189, id:1, text: "Oráculo de Min" }
    { group:189, id:2, text: "Altar de Maat" }
    { group:189, id:3, text: "Oráculo de Horus" }
    { group:189, id:4, text: "Altar de Amón" }
    { group:189, id:5, text: "Oráculo de Thot" }
    { group:189, id:6, text: "Altar de Anubis" }
    { group:189, id:7, text: "Oráculo de Sejmet" }
    { group:189, id:8, text: "Altar de Isis" }
    { group:189, id:9, text: "Oráculo de Hator" }
    { group:190, id:0, text: "Fábrica de papiro" }
    { group:190, id:1, text: "Aquí se une la médula de las cañas para hacer los papiros que necesitan las escuelas para escribir y educar a los alumnos. Además, el comercio de papiros produce muchos beneficios." }
    { group:190, id:2, text: "La producción está al:" }
    { group:190, id:3, text: "." }
    { group:190, id:4, text: "El supervisor comercial ha decretado que la producción de papiros debe parar." }
    { group:190, id:5, text: "Esta fábrica de papiros no tiene empleados, por lo que no producirá nada." }
    { group:190, id:6, text: "Esta fábrica de papiros tiene todo el personal que necesita y produce suficientes papiros de alta calidad." }
    { group:190, id:7, text: "Esta fábrica de papiros podría contratar más trabajadores para alcanzar toda la producción posible." }
    { group:190, id:8, text: "Esta fábrica de papiros no tiene suficientes empleados y produce papiros más despacio de lo debido." }
    { group:190, id:9, text: "En este taller trabaja muy poca gente, por lo que la producción de papiros es lenta." }
    { group:190, id:10, text: "Casi sin empleados, esta fábrica de papiros producirá poco durante el próximo año." }
    { group:190, id:11, text: "Este taller no producirá papiros sin un cargamento de cañas, de un almacén o de un recolector de caña." }
    { group:190, id:12, text: "Cañas almacenadas," }
    { group:191, id:0, text: "Desactivar diálogo" }
    { group:191, id:1, text: "Desactivar trampas" }
    { group:192, id:0, text: "Cantera de granito" }
    { group:192, id:1, text: "Para hacer obeliscos se usan grandes bloques de granito, que se tallan en las entrañas de la tierra." }
    { group:192, id:2, text: "La producción está al:" }
    { group:192, id:3, text: "." }
    { group:192, id:4, text: "El supervisor comercial ha ordenado que no se extraiga más granito." }
    { group:192, id:5, text: "Esta cantera no tiene empleados. La producción ha parado." }
    { group:192, id:6, text: "Esta cantera tiene todos los empleados que necesita y produce todo el granito posible." }
    { group:192, id:7, text: "Esta cantera funciona por debajo de su capacidad. La producción podría ser un poco más eficaz si hubiera más trabajadores." }
    { group:192, id:8, text: "Esta cantera no tiene suficientes empleados y tarda en producir granito más de lo debido." }
    { group:192, id:9, text: "En esta cantera trabaja muy poca gente, por lo que la produce poco granito." }
    { group:192, id:10, text: "La producción de esta cantera, casi sin empleados, ha descendido mucho. Producirá muy poco durante el próximo año." }
    { group:193, id:0, text: "Mina de cobre" }
    { group:193, id:1, text: "Con el cobre, muy maleable y duradero, se fabrican buenas armas y es un valioso material para exportar." }
    { group:193, id:2, text: "La producción está al:" }
    { group:193, id:3, text: "." }
    { group:193, id:4, text: "El supervisor comercial ha ordenado suspender la extracción de cobre." }
    { group:193, id:5, text: "Esta mina no tiene empleados. La producción se ha detenido." }
    { group:193, id:6, text: "Esta mina tiene todos los empleados que necesita y produce todo el cobre posible." }
    { group:193, id:7, text: "Esta mina funciona por debajo de su capacidad. La producción podría ser un poco más eficaz si hubiera más trabajadores." }
    { group:193, id:8, text: "Esta mina no tiene suficientes empleados y tarda en producir cobre más de lo debido." }
    { group:193, id:9, text: "En esta mina trabaja muy poca gente, por lo que la producción es lenta." }
    { group:193, id:10, text: "La producción de esta mina, casi sin empleados, ha descendido mucho. Producirá muy poco durante el próximo año." }
    { group:194, id:0, text: "Cantera de arenisca" }
    { group:194, id:1, text: "La arenisca es el único material adecuado para construir mausoleos y templos del Sol." }
    { group:194, id:2, text: "La producción está al:" }
    { group:194, id:3, text: "." }
    { group:194, id:4, text: "El supervisor comercial ha ordenado que no se extraiga más arenisca." }
    { group:194, id:5, text: "Esta cantera no tiene trabajadores. La producción ha parado." }
    { group:194, id:6, text: "Esta cantera tiene todos los trabajadores que necesita y produce toda la arenisca posible." }
    { group:194, id:7, text: "Esta cantera funciona por debajo de su capacidad. La producción podría ser un poco más eficaz si hubiera más trabajadores." }
    { group:194, id:8, text: "Esta cantera no tiene suficientes empleados y tarda en producir arenisca más de lo debido." }
    { group:194, id:9, text: "En esta cantera trabaja muy poca gente, por lo que la producción es lenta." }
    { group:194, id:10, text: "La producción de esta cantera, casi sin empleados, ha descendido mucho. Producirá muy poco durante el próximo año." }
    { group:195, id:0, text: "Abu" }
    { group:195, id:1, text: "Abydos" }
    { group:195, id:2, text: "Oasis de Bahriya" }
    { group:195, id:3, text: "Baki" }
    { group:195, id:4, text: "Behdet" }
    { group:195, id:5, text: "Bubastis" }
    { group:195, id:6, text: "Buhen" }
    { group:195, id:7, text: "Byblos" }
    { group:195, id:8, text: "Dahshur" }
    { group:195, id:9, text: "Oasis de Daila" }
    { group:195, id:10, text: "Djedu" }
    { group:195, id:11, text: "Oasis de Dunqul" }
    { group:195, id:12, text: "Enkomi" }
    { group:195, id:13, text: "Oasis de Farafra" }
    { group:195, id:14, text: "Gaza" }
    { group:195, id:15, text: "Heh" }
    { group:195, id:16, text: "Henen-nesw" }
    { group:195, id:17, text: "Hetepsenusret" }
    { group:195, id:18, text: "Iken" }
    { group:195, id:19, text: "Ititawi" }
    { group:195, id:20, text: "Iunet" }
    { group:195, id:21, text: "Jericho" }
    { group:195, id:22, text: "Kebet" }
    { group:195, id:23, text: "Kerma" }
    { group:195, id:24, text: "Oasis de Jariya" }
    { group:195, id:25, text: "Khmun" }
    { group:195, id:26, text: "Knossos" }
    { group:195, id:27, text: "Kyrene" }
    { group:195, id:28, text: "Meidum" }
    { group:195, id:29, text: "Men-nefer" }
    { group:195, id:30, text: "Menat Khufu" }
    { group:195, id:31, text: "Mycenae" }
    { group:195, id:32, text: "Nekhen" }
    { group:195, id:33, text: "Nubt (Ombos)" }
    { group:195, id:34, text: "On" }
    { group:195, id:35, text: "Perwadjyt" }
    { group:195, id:36, text: "Pwenet" }
    { group:195, id:37, text: "Qades" }
    { group:195, id:38, text: "Rostja" }
    { group:195, id:39, text: "Rowarty" }
    { group:195, id:40, text: "Saqqara" }
    { group:195, id:41, text: "Sauti" }
    { group:195, id:42, text: "Sawu" }
    { group:195, id:43, text: "Oasis de Selima" }
    { group:195, id:44, text: "Serabit Khadim" }
    { group:195, id:45, text: "Shaat" }
    { group:195, id:46, text: "Sharuhen" }
    { group:195, id:47, text: "Tinis" }
    { group:195, id:48, text: "Timna" }
    { group:195, id:49, text: "Toshka" }
    { group:195, id:50, text: "Tyre" }
    { group:195, id:51, text: "Waset" }
    { group:195, id:52, text: "Migdol" }
    { group:195, id:53, text: "Alejandría" }
    { group:195, id:54, text: "Sumur" }
    { group:195, id:55, text: "Deir el-Medina" }
    { group:195, id:56, text: "Abu Simbel" }
    { group:195, id:57, text: "Accio" }
    { group:195, id:58, text: "Roma" }
    { group:195, id:59, text: "Tanis" }
    { group:195, id:60, text: "Pi-Yer" }
    { group:195, id:61, text: "Oasis de Siwi" }
    { group:195, id:62, text: "Maritis" }
    { group:195, id:63, text: "Piramesse" }
    { group:195, id:64, text: "Atenas" }
    { group:195, id:65, text: "Cleoantonópolis" }
    { group:196, id:0, text: "CRETA" }
    { group:196, id:1, text: "CHIPRE" }
    { group:196, id:2, text: "ÁFRICA ORIENTAL" }
    { group:196, id:3, text: "DESIERTO ORIENTAL" }
    { group:196, id:4, text: "GRECIA" }
    { group:196, id:5, text: "LIBIA" }
    { group:196, id:6, text: "BAJO EGIPTO" }
    { group:196, id:7, text: "DELTA" }
    { group:196, id:8, text: "FAYUM" }
    { group:196, id:9, text: "NUBIA" }
    { group:196, id:10, text: "PALESTINA" }
    { group:196, id:11, text: "SINAÍ" }
    { group:196, id:12, text: "SIRIA" }
    { group:196, id:13, text: "ALTO EGIPTO" }
    { group:196, id:14, text: "DESIERTO OCCIDENTAL" }
    { group:196, id:15, text: "LÍBANO" }
    { group:196, id:16, text: "CANAÁN" }
    { group:197, id:0, text: "Nombres masculinos" }
    { group:197, id:1, text: "Akunosh" }
    { group:197, id:2, text: "Benermerut" }
    { group:197, id:3, text: "Genubath" }
    { group:197, id:4, text: "Hemaka" }
    { group:197, id:5, text: "Inarus" }
    { group:197, id:6, text: "Khensthoth" }
    { group:197, id:7, text: "Mentuemhat" }
    { group:197, id:8, text: "Minnakht" }
    { group:197, id:9, text: "Nebhotep" }
    { group:197, id:10, text: "Nefermenu" }
    { group:197, id:11, text: "Neshi" }
    { group:197, id:12, text: "Nimlot" }
    { group:197, id:13, text: "Osorkon" }
    { group:197, id:14, text: "Pashedu" }
    { group:197, id:15, text: "Ptahshepses" }
    { group:197, id:16, text: "Sennedjem" }
    { group:197, id:17, text: "Tahrqa" }
    { group:197, id:18, text: "Wepawetmose" }
    { group:197, id:19, text: "Yanhamu" }
    { group:197, id:20, text: "Zazamoukh" }
    { group:197, id:21, text: "Nombres femeninos" }
    { group:197, id:22, text: "Abana" }
    { group:197, id:23, text: "Baktwerel" }
    { group:197, id:24, text: "Duathor" }
    { group:197, id:25, text: "Enehy" }
    { group:197, id:26, text: "Herneith" }
    { group:197, id:27, text: "Hetephenebti" }
    { group:197, id:28, text: "Iras" }
    { group:197, id:29, text: "Isetemkheb" }
    { group:197, id:30, text: "Khamaat" }
    { group:197, id:31, text: "Kiya" }
    { group:197, id:32, text: "Meretseger" }
    { group:197, id:33, text: "Mutnodjmet" }
    { group:197, id:34, text: "Neferura" }
    { group:197, id:35, text: "Nofertiri" }
    { group:197, id:36, text: "Peshet" }
    { group:197, id:37, text: "Reddjedet" }
    { group:197, id:38, text: "Sutailja" }
    { group:197, id:39, text: "Tetisheri" }
    { group:197, id:40, text: "Ubastet" }
    { group:197, id:41, text: "Wepwawet" }
    { group:198, id:0, text: "Ninguna" }
    { group:198, id:1, text: "Pirámide romboidal pequeña" }
    { group:198, id:2, text: "Pirámide romboidal mediana" }
    { group:198, id:3, text: "Pirámide de adobe pequeña" }
    { group:198, id:4, text: "Pirámide de adobe mediana" }
    { group:198, id:5, text: "Pirámide de adobe grande" }
    { group:198, id:6, text: "Complejo de pirámides de adobe" }
    { group:198, id:7, text: "Gran comp. pirámides de adobe" }
    { group:198, id:8, text: "Pirámide escalonada pequeña" }
    { group:198, id:9, text: "Pirámide escalonada mediana" }
    { group:198, id:10, text: "Pirámide escalonada grande" }
    { group:198, id:11, text: "Complejo de pirámides escalonadas" }
    { group:198, id:12, text: "Gran comp. pirámides escalonadas" }
    { group:198, id:13, text: "Pirámide pequeña" }
    { group:198, id:14, text: "Pirámide mediana" }
    { group:198, id:15, text: "Pirámide grande" }
    { group:198, id:16, text: "Complejo de pirámides" }
    { group:198, id:17, text: "Gran complejo de pirámides" }
    { group:198, id:18, text: "Mastaba pequeña" }
    { group:198, id:19, text: "Mastaba mediana" }
    { group:198, id:20, text: "Mastaba grande" }
    { group:198, id:21, text: "Esfinge" }
    { group:198, id:22, text: "Obelisco pequeño" }
    { group:198, id:23, text: "Obelisco grande" }
    { group:198, id:24, text: "Templo del Sol" }
    { group:198, id:25, text: "Mausoleo" }
    { group:198, id:26, text: "Mausoleo" }
    { group:198, id:27, text: "Mausoleo" }
    { group:198, id:28, text: "El Faro de Pharos" }
    { group:198, id:29, text: "La Biblioteca de Alejandría" }
    { group:198, id:30, text: "El Caesareum" }
    { group:198, id:31, text: "Colosos" }
    { group:198, id:32, text: "Templo de Luxor" }
    { group:198, id:33, text: "La tumba funeraria real pequeña" }
    { group:198, id:34, text: "La tumba funeraria real mediana" }
    { group:198, id:35, text: "La tumba funeraria real grande" }
    { group:198, id:36, text: "La tumba funeraria real grandiosa" }
    { group:198, id:37, text: "El Abu Simbel" }
    { group:199, id:0, text: "Supervisor de monumentos" }
    { group:199, id:1, text: "almacenado" }
    { group:199, id:2, text: "Terminado" }
    { group:199, id:3, text: "Haz clic en las provisiones funerarias para repartir." }
    { group:199, id:4, text: "Cantidad para enviar" }
    { group:199, id:5, text: "Todo" }
    { group:199, id:6, text: "Haz clic para enviar" }
    { group:199, id:7, text: "Cancelar" }
    { group:199, id:8, text: "Aumentar la cantidad" }
    { group:199, id:9, text: "Disminuir la cantidad" }
    { group:199, id:10, text: "Enviar provisiones funerarias" }
    { group:199, id:11, text: "Puntuación de monumentos" }
    { group:199, id:12, text: "No hay provisiones funerarias para enviar" }
    { group:199, id:13, text: "Si quieres más detalles, visita el lugar de construcción." }
    { group:199, id:14, text: "El trabajo en la pirámide no ha empezado. Necesitas peones para" }
    { group:199, id:15, text: "este proyecto y mucha piedra normal y caliza para terminar." }
    { group:199, id:16, text: "Construcción: La pirámide está al" }
    { group:199, id:17, text: "La pirámide ya está terminada." }
    { group:199, id:18, text: "La pirámide está terminada y espera la llegada de los restos sagrados." }
    { group:199, id:19, text: "El trabajo en la pirámide de ladrillo no ha empezado. Necesitas peones" }
    { group:199, id:20, text: "para este proyecto, y muchos ladrillos y piedra caliza para terminar." }
    { group:199, id:21, text: "Construcción: La pirámide de ladrillos está al" }
    { group:199, id:22, text: "La pirámide de ladrillos ya está terminada." }
    { group:199, id:23, text: "La pirámide está terminada y espera la llegada de los restos sagrados." }
    { group:199, id:24, text: "El trabajo en la pirámide escalonada aún no ha empezado. Necesitas" }
    { group:199, id:25, text: "campesinos para comenzar y mucha piedra normal para terminar." }
    { group:199, id:26, text: "Construcción: La pirámide escalonada está al" }
    { group:199, id:27, text: "La pirámide escalonada ya está terminada." }
    { group:199, id:28, text: "La pirámide está terminada y espera la llegada de los restos sagrados." }
    { group:199, id:29, text: "El trabajo en la pirámide romboidal aún no ha empezado. Necesitas" }
    { group:199, id:30, text: "campesinos para comenzar y mucha piedra normal y caliza para terminar." }
    { group:199, id:31, text: "Construcción: La pirámide romboidal está al" }
    { group:199, id:32, text: "La pirámide romboidal ya está terminada." }
    { group:199, id:33, text: "La pirámide está terminada y espera la llegada de los restos sagrados." }
    { group:199, id:34, text: "El trabajo en la mastaba no ha empezado, necesitas campesinos para" }
    { group:199, id:35, text: "este proyecto y un buen suministro de ladrillos para terminarlo." }
    { group:199, id:36, text: "Construcción: La mastaba está al" }
    { group:199, id:37, text: "La mastaba ya está terminada." }
    { group:199, id:38, text: "La mastaba está terminada y espera la llegada de los restos sagrados." }
    { group:199, id:39, text: "La esfinge no se ha empezado. Necesitas carpinteros, canteros," }
    { group:199, id:40, text: "madera y piedra normal para comenzar este proyecto." }
    { group:199, id:41, text: "Construcción: La esfinge está al" }
    { group:199, id:42, text: "La esfinge ya está terminada." }
    { group:199, id:43, text: "El trabajo en el obelisco aún no ha empezado. Necesitarás" }
    { group:199, id:44, text: "bloques de granito para comenzar este proyecto. Tienes" }
    { group:199, id:45, text: "Construcción: El obelisco está al" }
    { group:199, id:46, text: "El obelisco ya está terminado." }
    { group:199, id:47, text: "El trabajo en el templo del Sol aún no ha empezado. Necesitarás" }
    { group:199, id:48, text: "bloques de arenisca para comenzar este proyecto. Tienes" }
    { group:199, id:49, text: "Construcción: El templo del Sol está al" }
    { group:199, id:50, text: "El templo del Sol ya está terminado." }
    { group:199, id:51, text: "El trabajo en el mausoleo aún no ha empezado. Necesitarás" }
    { group:199, id:52, text: "bloques de arenisca para comenzar este proyecto. Tienes" }
    { group:199, id:53, text: "Construcción: El mausoleo está al" }
    { group:199, id:54, text: "El mausoleo ya está terminado." }
    { group:199, id:55, text: "El mausoleo está terminado y espera la llegada de los restos sagrados." }
    { group:199, id:56, text: "Haz clic aquí para visitar el lugar de construcción." }
    { group:199, id:57, text: "bloque" }
    { group:199, id:58, text: "bloques" }
    { group:199, id:59, text: "La construcción de la biblioteca de Alejandría no ha comenzado. Necesitarás" }
    { group:199, id:60, text: "mano de obra para comenzar este proyecto y mármol y cobre para terminarlo." }
    { group:199, id:61, text: "La biblioteca de Alejandría está al" }
    { group:199, id:62, text: "¡La biblioteca de Alejandría está terminada!" }
    { group:199, id:63, text: "La construcción del Caesareum no ha comenzado. Necesitarás mano de obra" }
    { group:199, id:64, text: "para comenzar este proyecto y mármol y granito para terminarlo." }
    { group:199, id:65, text: "El Caesareum está al" }
    { group:199, id:66, text: "¡El Caesareum está terminado!" }
    { group:199, id:67, text: "La construcción del faro de Pharos no ha comenzado. Necesitarás" }
    { group:199, id:68, text: "mano de obra para comenzar este proyecto y mármol para terminarlo." }
    { group:199, id:69, text: "El faro de Pharos está al" }
    { group:199, id:70, text: "¡El faro de Pharos está terminado!" }
    { group:199, id:71, text: "La construcción de Abu Simbel no ha comenzado. Necesitarás carpinteros," }
    { group:199, id:72, text: "canteros y un suministro de madera para este proyecto." }
    { group:199, id:73, text: "El Abu Simbel está al" }
    { group:199, id:74, text: "¡El Abu Simbel está terminado!" }
    { group:199, id:75, text: "El trabajo en la tumba funeraria pequeña no ha comenzado. Necesitarás" }
    { group:199, id:76, text: "canteros, artesanos, arcilla, pintura y lámparas para comenzar este proyecto." }
    { group:199, id:77, text: "La tumba funeraria real pequeña está al" }
    { group:199, id:78, text: "¡La tumba funeraria real pequeña está terminada!" }
    { group:199, id:79, text: "El trabajo en la tumba funeraria mediana no ha comenzado. Necesitarás" }
    { group:199, id:80, text: "canteros, artesanos, arcilla, pintura y lámparas para comenzar este proyecto." }
    { group:199, id:81, text: "La tumba funeraria real mediana está al" }
    { group:199, id:82, text: "¡La tumba funeraria real mediana está terminada!" }
    { group:199, id:83, text: "El trabajo en la tumba funeraria grande no ha comenzado. Necesitarás canteros," }
    { group:199, id:84, text: "artesanos, arcilla, pintura y lámparas para comenzar este proyecto." }
    { group:199, id:85, text: "La tumba funeraria real grande está al" }
    { group:199, id:86, text: "¡La tumba funeraria real grande está terminada!" }
    { group:199, id:87, text: "El trabajo en la tumba funeraria grandiosa no ha comenzado. Necesitarás" }
    { group:199, id:88, text: "canteros, artesanos, arcilla, pintura y lámparas para comenzar este proyecto." }
    { group:199, id:89, text: "La tumba funeraria real grandiosa está al" }
    { group:199, id:90, text: "¡La tumba funeraria real grandiosa está terminada!" }
    { group:200, id:0, text: "Fase uno: Obtener granito para colocar la estructura" }
    { group:200, id:1, text: "Fase dos: Los carpinteros usan madera para construir el andamiaje" }
    { group:200, id:2, text: "Fase tres: Los canteros tallan la forma final, de arriba a abajo." }
    { group:200, id:3, text: "Estado:" }
    { group:200, id:4, text: "No se ha comenzado" }
    { group:200, id:5, text: "Incompleta" }
    { group:200, id:6, text: "Terminada" }
    { group:200, id:7, text: "Progreso general:" }
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
    { group:202, id:0, text: "Acabo de llegar, y me pregunto que ofrecerá esta ciudad a alguien como yo." }
    { group:202, id:1, text: "He oído que aquí hay trabajo para todo el que quiera." }
    { group:202, id:2, text: "La gente dice que en esta ciudad hay comida para todo el mundo." }
    { group:203, id:0, text: "Aquí no encuentro trabajo. Buscaré en otro sitio." }
    { group:203, id:1, text: "No hay suficiente comida. ¡Me voy de este desierto!" }
    { group:203, id:2, text: "Los impuestos son demasiado altos. Me extraña que no me hayan cobrado por irme." }
    { group:203, id:3, text: "No puedo vivir con lo que me pagan." }
    { group:203, id:4, text: "Las casas que he visto están abarrotadas. No puedo quedarme aquí sin un sitio donde vivir." }
    { group:204, id:0, text: "Me han echado de mi casa." }
    { group:204, id:1, text: "¡No encuentro un sitio donde vivir!" }
    { group:205, id:0, text: "Tal vez, si robo algo de su tesoro, atraiga su atención." }
    { group:205, id:1, text: "¡Cogeré lo que quiera! ¡No intentes detenerme!" }
    { group:205, id:2, text: "En esta ciudad, el empleo más provechoso es el de ladrón." }
    { group:205, id:3, text: "Coger, coger, coger. Eso es lo que siempre hago." }
    { group:206, id:0, text: "(Cof, cof) ¡Ayyy mi estómago! ¡Ay, mi cabeza!" }
    { group:207, id:0, text: "¡La epidemia podría azotar en cualquier momento! Espero que se quede en las zonas pobres de la ciudad." }
    { group:207, id:1, text: "¡Que una persona de mi categoría pueda saber lo que es el hambre es escandaloso!" }
    { group:207, id:2, text: "No creo que esta ciudad pueda resistir un ataque y tengo mucho que perder." }
    { group:207, id:3, text: "¿Cómo pueden tan pocos trabajadores satisfacer apropiadamente mis necesidades?" }
    { group:207, id:4, text: "Me tratan mejor que a los dioses. Espero que no nos castiguen." }
    { group:207, id:5, text: "Me avergüenzo de vivir aquí. Espero que nuestros enemigos no se aprovechen de nuestra mala reputación." }
    { group:207, id:6, text: "¡Mira todos esos vagos! ¿Por que no buscan trabajo?" }
    { group:207, id:7, text: "¿Cómo puedo llevar una vida de lujo, si no me entretienen adecuadamente?" }
    { group:207, id:8, text: "Supongo que esta ciudad es aceptable." }
    { group:207, id:9, text: "¡Esta ciudad es la mejor!" }
    { group:207, id:10, text: "Estos festivales serían mejores si fueran por invitación" }
    { group:208, id:0, text: "Los antílopes caen como corderitos." }
    { group:208, id:1, text: "Esta noche habrá filetes para todo el mundo." }
    { group:209, id:0, text: "Los avestruces son casi invisibles cuando esconden la cabeza en la arena." }
    { group:209, id:1, text: "Éstos sí que son muslos, y no los del pollo." }
    { group:210, id:0, text: "Los pájaros son astutos y se escaparán si no te acercas con cuidado." }
    { group:210, id:1, text: "Mira esos preciosos pájaros, listos para asar." }
    { group:211, id:0, text: "Otro día perfecto para ir a pescar. Espero que la pesca sea tan abundante como siempre." }
    { group:211, id:1, text: "Nuestra bodega está repleta, pero tenías que haber visto el que se escapó." }
    { group:211, id:2, text: "¡Más rápido! No podemos volver al trabajo hasta que descarguemos." }
    { group:212, id:0, text: "Hay mucha gente enferma. Espero que las cosas no empeoren." }
    { group:212, id:1, text: "Estoy muerto de hambre. Es difícil trabajar con el estómago vacío." }
    { group:212, id:2, text: "Espero que nuestros enemigos no sepan lo fácil que sería invadirnos." }
    { group:212, id:3, text: "Hay empleos por todas partes. Tal vez consiga trabajo como bombero." }
    { group:212, id:4, text: "Espero que los dioses no desencadenen su ira." }
    { group:212, id:5, text: "He oído que nuestra ciudad no goza de muy buena reputación. Alguien podría atacarnos." }
    { group:212, id:6, text: "Soy afortunado por tener este trabajo. Hay mucha gente en paro." }
    { group:212, id:7, text: "Lo único que hago es trabajar. En esta ciudad no hay nada más que hacer." }
    { group:212, id:8, text: "Me gusta vivir aquí, pero siempre se puede mejorar." }
    { group:212, id:9, text: "¡Espero vivir aquí siempre!" }
    { group:212, id:10, text: "(not used)" }
    { group:212, id:11, text: "Estoy preparado para trabajar, pero no puedo llegar a la granja." }
    { group:212, id:12, text: "Con los campos anegados, ahora trabajaré por la gloria eterna." }
    { group:213, id:0, text: "Veo gente enferma por todas partes. Podría desencadenarse una epidemia." }
    { group:213, id:1, text: "Me muero de hambre. Mejor buscaré comida en vez de trabajadores." }
    { group:213, id:2, text: "Temo que puedan atacar nuestra ciudad. La ventaja es que así llegarán extranjeros para cubrir los trabajos vacantes." }
    { group:213, id:3, text: "Mi trabajo es imposible, no hay trabajadores disponibles." }
    { group:213, id:4, text: "Espero que los dioses no nos castiguen. Debemos prestarles más atención." }
    { group:213, id:5, text: "Los enemigos pueden atacar en cualquier momento. Nadie nos respeta." }
    { group:213, id:6, text: "Mi trabajo debería ser fácil, ya que hay mucha gente sin trabajo." }
    { group:213, id:7, text: "Aquí me aburro. Me gustaría poder contratar a más artistas." }
    { group:213, id:8, text: "No me molesta vivir aquí. Las cosas podrían ser peores." }
    { group:213, id:9, text: "¡Esta ciudad es la mejor!" }
    { group:213, id:10, text: "Soy la persona más popular de la ciudad. Mucha gente necesita trabajo." }
    { group:213, id:11, text: "La lista de vacantes es enorme y no encuentro trabajadores para llenarlas." }
    { group:214, id:0, text: "He salido a pasar el día talando." }
    { group:214, id:1, text: "Estoy seguro de que a esta madera se le dará buen uso." }
    { group:215, id:0, text: "Pantano, pantano, pantano. Las cañas sólo crecen en los pantanos." }
    { group:215, id:1, text: "Con estas cañas se harán excelentes papiros." }
    { group:216, id:0, text: "En el monumento requieren mis servicios." }
    { group:216, id:1, text: "Sin mis rampas y andamiajes, este monumento sería muy bajo." }
    { group:217, id:0, text: "Ha llegado el momento de poner los ladrillos del monumento." }
    { group:217, id:1, text: "Con mis ladrillos, este monumento será resistente." }
    { group:218, id:0, text: "Voy al monumento a dar forma a las piedras." }
    { group:218, id:1, text: "Mi trabajo en la piedra perdurará durante siglos." }
    { group:219, id:0, text: "Ha enfermado demasiada gente. Si no se recuperan pronto, podría estallar una epidemia." }
    { group:219, id:1, text: "Me muero de hambre. Todos mis clientes piden comida y apenas puedo alimentarme yo." }
    { group:219, id:2, text: "Nuestras defensas son débiles. Nos pueden invadir con facilidad." }
    { group:219, id:3, text: "Seré muy amable con mis ayudantes. Con la cantidad de empleos que hay, podría perderlos fácilmente." }
    { group:219, id:4, text: "Si no prestamos pronto más atención a los dioses, nos van a infligir un desagradable castigo." }
    { group:219, id:5, text: "¡Pronto pagaremos el precio por la mala reputación de la ciudad!" }
    { group:219, id:6, text: "Soy afortunada por tener trabajo. Hay mucha gente en paro." }
    { group:219, id:7, text: "Aquí no pasa nada en absoluto. Me gustaría que hubiera más espectáculos." }
    { group:219, id:8, text: "No voy a quejarme de esta ciudad... pero podría." }
    { group:219, id:9, text: "Esta ciudad es la mejor de todas." }
    { group:219, id:10, text: "El bazar necesita mercancía y voy a conseguirla." }
    { group:219, id:11, text: "Estos artículos vendrán muy bien en el bazar." }
    { group:220, id:0, text: "¡Mis suministros se venden como rosquillas! Voy al bazar a buscar más." }
    { group:220, id:1, text: "Hago todo lo que puedo para dar a la gente lo que quiere." }
    { group:221, id:0, text: "Esas cestas son demasiado pesadas para un crío como yo." }
    { group:221, id:1, text: "Esa mandona me tiene todo el día llevando mercancía." }
    { group:221, id:2, text: "Quizás por el momento sólo transporte cestas, pero algún día dirigiré el bazar." }
    { group:222, id:0, text: "No voy a seguir empujando estos suministros hasta que alguien pueda descargarlos." }
    { group:222, id:1, text: "¡Nadie puede aceptar esta mercancía! Me quedaré con lo que sobra." }
    { group:222, id:2, text: "Tengo que atravesar la ciudad con estos artículos. ¡Me llevará todo el día!" }
    { group:223, id:0, text: "Trabajamos más de lo que nos corresponde. Necesitamos más ayuda." }
    { group:223, id:1, text: "Esperaré aquí hasta que haya sitio para esta mercancía." }
    { group:223, id:2, text: "¿He llegado ya? No puedo transportar estos artículos mucho más." }
    { group:224, id:0, text: "Me pregunto si esta ciudad tiene algún lugar de interés que pueda visitar mientras descargan mi barco." }
    { group:224, id:1, text: "Estamos esperando a que suban un cargamento a nuestro barco." }
    { group:224, id:2, text: "No sé por qué hemos venido. Esta ciudad nunca comercia y es aburrida." }
    { group:224, id:3, text: "¡Me encanta el arte del comercio. Estoy deseando vender mis suministros." }
    { group:224, id:4, text: "¡Qué viaje más provechoso!" }
    { group:225, id:0, text: "Hemos hecho en vano este largo y peligroso viaje. En esta ciudad no se comercia." }
    { group:225, id:1, text: "Comprar a la baja, vender a la alta. ¡Ese es mi lema!" }
    { group:225, id:2, text: "¡La vida del comerciante es para mí!" }
    { group:225, id:3, text: "Cuando lleve estos artículos a mi tierra seré un héroe." }
    { group:225, id:4, text: "Esto es una ganga, amigo. Apenas me da para cubrir los gastos." }
    { group:226, id:0, text: "Jamás había visto tanta gente enferma. Espero que no estalle una epidemia." }
    { group:226, id:1, text: "Es difícil coger los palos cuando se tiene tanta hambre." }
    { group:226, id:2, text: "Tal vez podría lanzar los palos al enemigo si atacara. Parece que nadie más defiende la ciudad." }
    { group:226, id:3, text: "Hay empleos vacantes por todas partes. Empiezo a plantearme lo del pluriempleo." }
    { group:226, id:4, text: "Me temo lo peor. Los dioses deben de pensar que los hemos olvidado." }
    { group:226, id:5, text: "Esta ciudad tiene peor reputación que yo. Espero que nadie nos ataque." }
    { group:226, id:6, text: "Me gustaría que hubiera más empleos en la ciudad. Ninguno de mis espectadores puede pagarme." }
    { group:226, id:7, text: "No puedo hacer tantos malabarismos. Desearía que hubiera otros artistas en la ciudad." }
    { group:226, id:8, text: "Esta ciudad no está tan mal." }
    { group:226, id:9, text: "No hay otro lugar en el que prefiera hacer malabarismos." }
    { group:226, id:10, text: "Me encanta trabajar en estos festivales multitudinarios. ¡Todo el mundo está tan feliz...!" }
    { group:227, id:0, text: "Si en esta ciudad no mejora la sanidad, sólo tocaré marchas fúnebres." }
    { group:227, id:1, text: "Cantaría para costearme la cena, pero en esta ciudad no hay suficiente comida." }
    { group:227, id:2, text: "Tal vez podría atacar a los invasores con el sistro. Esta ciudad no tiene más defensas." }
    { group:227, id:3, text: "Aquí no puedo tocar más que solos. En esta ciudad no hay suficientes trabajadores." }
    { group:227, id:4, text: "Espero que mi música aplaque a los dioses. Podrían lanzar su ira sobre nosotros." }
    { group:227, id:5, text: "Nuestra mala reputación podría provocar un ataque." }
    { group:227, id:6, text: "Insisto en que no voy a contratar a nadie. Hay mucha gente buscando trabajo." }
    { group:227, id:7, text: "Incluso a los artistas nos gusta que nos entretengan. Aquí no hay mucho que hacer." }
    { group:227, id:8, text: "Supongo que esta ciudad podría ser peor." }
    { group:227, id:9, text: "Espero seguir haciendo buena música en esta ciudad durante mucho tiempo." }
    { group:227, id:10, text: "¡Estos festivales son geniales! Todo el mundo canta conmigo." }
    { group:228, id:0, text: "En la ciudad hay mucha gente enferma. Espero no contagiarme." }
    { group:228, id:1, text: "No puedo brincar muy bien sin suficiente comida." }
    { group:228, id:2, text: "Los invasores no tendrían muchos problemas para conquistar nuestra ciudad. Nadie la defiende." }
    { group:228, id:3, text: "Otro compañero perdido por la falta de trabajadores. Odio bailar sola." }
    { group:228, id:4, text: "Deberíamos hacer algo más para aplacar a los dioses, y deprisa." }
    { group:228, id:5, text: "La reputación de la ciudad es peor que la de un malabarista. Espero que no nos ataquen." }
    { group:228, id:6, text: "Si no fuera tan rápido, pisaría a todos los desempleados que hay por el suelo." }
    { group:228, id:7, text: "(Bah) Necesito que me entretengan" }
    { group:228, id:8, text: "Supongo que esta ciudad es tan buena como cualquier otra." }
    { group:228, id:9, text: "¡Esta ciudad es fantástica!" }
    { group:228, id:10, text: "La multitud de estos festivales es tan entusiasta que me dan ganas de saltar más alto." }
    { group:229, id:0, text: "La salud de la gente está en peligro. El riesgo de epidemias es grande." }
    { group:229, id:1, text: "Estoy tan hambriento como un hipopótamo, pero se encuentra poca comida." }
    { group:229, id:2, text: "Tendría que aprender el arte de la guerra. Con unas defensas tan débiles, estamos en peligro." }
    { group:229, id:3, text: "La falta de trabajadores podría causar verdaderos problemas en la ciudad." }
    { group:229, id:4, text: "A decir verdad, no me atrevería a tratar a los dioses tan mal." }
    { group:229, id:5, text: "La reputación de la ciudad no es muy buena. Nos pueden atacar." }
    { group:229, id:6, text: "Para la mayoría, buscar trabajo en esta ciudad es un esfuerzo inútil que acaba en fracaso." }
    { group:229, id:7, text: "Esta ciudad debería fijarse en la falta de entretenimiento" }
    { group:229, id:8, text: "No me arrepiento de vivir aquí." }
    { group:229, id:9, text: "Esta ciudad ocupa todo mi corazón. Me gusta vivir aquí." }
    { group:229, id:10, text: "¡Toma tu cerveza aquí! ¡Cálida, sosa, refrescante cerveza! ¡Baja en sedimentos!" }
    { group:230, id:0, text: "La ciudad está plagada de gente enferma. Espero que no estalle una epidemia." }
    { group:230, id:1, text: "Ningún sacerdote de Osiris debería pasar hambre." }
    { group:230, id:2, text: "Nuestra ciudad no tiene casi defensas. Espero que nadie nos ataque." }
    { group:230, id:3, text: "Sin más trabajadores, tal vez no podamos ofrecer a Osiris el respeto que merece." }
    { group:230, id:4, text: "Osiris no es el único dios enfadado por el descuido." }
    { group:230, id:5, text: "Nuestra ciudad es el hazmerreír de Egipto. Estamos pidiendo a gritos que nos ataquen." }
    { group:230, id:6, text: "El paro es un problema muy grave en esta ciudad. Espero que se creen más empleos pronto." }
    { group:230, id:7, text: "Incluso un sacerdote necesita algo más que rezos para entretenerse." }
    { group:230, id:8, text: "La ciudad es adecuada." }
    { group:230, id:9, text: "Osiris está orgulloso de que se le venere en una ciudad tan bonita." }
    { group:230, id:10, text: "Los festivales alegran el corazón de Osiris." }
    { group:230, id:11, text: "Osiris podría castigar a la ciudad por su indiferencia con una riada pequeña." }
    { group:231, id:0, text: "La gente que acude al templo no parece muy sana. Espero que la enfermedad no se extienda." }
    { group:231, id:1, text: "No tengo suficiente comida para Ra ni para mí." }
    { group:231, id:2, text: "Desearía que la defensa de la ciudad dependiera de Ra. No creo que nuestro gobernador haga un buen trabajo." }
    { group:231, id:3, text: "Espero que la ciudad encuentre más trabajadores pronto. Los servicios podrían verse afectados." }
    { group:231, id:4, text: "Esta ciudad debería mostrar más respeto hacia los dioses." }
    { group:231, id:5, text: "La reputación es importante. Sin ella, a cualquiera le puede dar por invadir la ciudad." }
    { group:231, id:6, text: "Nunca había oído a tanta gente preguntar a Ra si por fin encontrará trabajo." }
    { group:231, id:7, text: "Necesito más diversiones. Complacer a Ra todo el día no es fácil, necesito distraerme." }
    { group:231, id:8, text: "No tengo quejas graves sobre esta ciudad." }
    { group:231, id:9, text: "El único lugar mejor que esta ciudad es el otro mundo." }
    { group:231, id:10, text: "A Ra le encanta ver a su gente durante el festival." }
    { group:231, id:11, text: "Nuestra ciudad es una vergüenza para el resto del imperio." }
    { group:232, id:0, text: "Si no se mejoran las condiciones de la ciudad, la mala sanidad podría desembocar en una epidemia." }
    { group:232, id:1, text: "El ruido de mi estómago vacío me distrae de mis deberes para Ptah." }
    { group:232, id:2, text: "Nuestras débiles defensas serán inútiles si alguien decide atacarnos." }
    { group:232, id:3, text: "Ptah se entristece al ver que las industrias no funcionan a causa de la falta de trabajadores." }
    { group:232, id:4, text: "Los dioses pueden infligir un justo castigo si la ciudad continua sin hacerles caso." }
    { group:232, id:5, text: "Nuestra mala reputación puede animar a los invasores." }
    { group:232, id:6, text: "Ptah desea que todos los desempleados de la ciudad puedan encontrar un trabajo productivo." }
    { group:232, id:7, text: "Me gusta pasar un buen rato, como a todo el mundo. Desearía que hubiera más artistas en la ciudad." }
    { group:232, id:8, text: "Esta ciudad tiene sus problemas, pero es un buen sitio para vivir." }
    { group:232, id:9, text: "¡Esta es la ciudad mejor abastecida de empleo de todo Egipto!" }
    { group:232, id:10, text: "Ptah sabe que las vacaciones mantienen contentos a los trabajadores." }
    { group:232, id:11, text: "La mano de Ptah no lo puede hacer todo. Las industrias de esta ciudad necesitan más trabajadores." }
    { group:233, id:0, text: "Si la sanidad de la ciudad no mejora, una epidemia podría causar estragos." }
    { group:233, id:1, text: "Durante todo el día combato con mi hambre. Necesito más comida." }
    { group:233, id:2, text: "Dependemos de Seth para que nos proteja en la batalla. La ciudad no está preparada para defenderse." }
    { group:233, id:3, text: "Los servicios se resienten porque no se encuentran trabajadores." }
    { group:233, id:4, text: "Esta ciudad debería dejar de provocar la ira de los dioses con su inactividad." }
    { group:233, id:5, text: "Puede que pronto descubramos qué piensan los demás de nuestra ciudad, cuando vengan y la destruyan." }
    { group:233, id:6, text: "Las legiones de desempleados inundan las calles." }
    { group:233, id:7, text: "Es increíble lo aburrido que es esto." }
    { group:233, id:8, text: "Esta ciudad es suficientemente buena para mí." }
    { group:233, id:9, text: "En todo Egipto no hay rival para esta ciudad." }
    { group:233, id:10, text: "Incluso los guerreros de Seth necesitan un festival de vez en cuando." }
    { group:233, id:11, text: "La gloria está en el horizonte. Los enemigos se acercan a la ciudad rápidamente." }
    { group:234, id:0, text: "Bastet se aflige al ver a tanta gente enferma. Espero que no se desate un epidemia." }
    { group:234, id:1, text: "En esta ciudad es difícil conseguir comida. Todo el mundo pasa hambre." }
    { group:234, id:2, text: "Las lamentables defensas de nuestra ciudad invitan a nuestros enemigos a atacarnos." }
    { group:234, id:3, text: "No es posible que nuestra ciudad funcione bien, con tantos trabajos vacantes." }
    { group:234, id:4, text: "Los dioses le están dando la espalda a esta ciudad. Debemos mostrarles más respeto." }
    { group:234, id:5, text: "La reputación de esta ciudad es terrible. En cualquier momento puede tener lugar una invasión." }
    { group:234, id:6, text: "Ni siquiera Bastet puede alegrar los corazones de tanta gente desempleada." }
    { group:234, id:7, text: "Bastet está escandalizada por la falta de entretenimiento que hay en esta ciudad." }
    { group:234, id:8, text: "Esta ciudad no es un lugar tan malo para vivir." }
    { group:234, id:9, text: "Esta ciudad es la mejor" }
    { group:234, id:10, text: "A Bastet le gustan los buenos festivales." }
    { group:234, id:11, text: "La gente de la ciudad está muy insatisfecha. Podría desatarse una oleada de delincuencia." }
    { group:234, id:12, text: "¿Qué puede hacer una sacerdotisa? Aquí hay muy pocas diversiones." }
    { group:234, id:13, text: "Bastet me concede el poder para curar a los enfermos antes de que extiendan su enfermedad." }
    { group:235, id:0, text: "La ciudad podría aprender pronto que una mala sanidad puede desembocar en una terrible epidemia." }
    { group:235, id:1, text: "Mi mente se alimenta de conocimientos, pero mi cuerpo necesita comida." }
    { group:235, id:2, text: "Los invasores no tendrían problemas para atravesar nuestras escasas defensas." }
    { group:235, id:3, text: "La escasez de trabajadores afecta a toda la ciudad y limita sus servicios." }
    { group:235, id:4, text: "El comportamiento sacrílego de la ciudad podría hacer que los dioses nos destruyeran." }
    { group:235, id:5, text: "Ah, la reputación, la reputación. Nuestra mala reputación invita a que nos ataquen." }
    { group:235, id:6, text: "Ni siquiera la educación remediaría el problema de desempleo de la ciudad." }
    { group:235, id:7, text: "Aburrida, sosa, tediosa, monótona, pesada. Esta ciudad es insoportable." }
    { group:235, id:8, text: "Esta ciudad es normal y corriente." }
    { group:235, id:9, text: "Esta ciudad da la talla." }
    { group:235, id:10, text: "En los festivales se puede aprender mucho sobre la naturaleza humana." }
    { group:236, id:0, text: "La gente está enferma. Mis papiros médicos me dicen que la enfermedad se podría convertir pronto en epidemia." }
    { group:236, id:1, text: "Estoy muerto de hambre. Es difícil levantar los pergaminos con el estómago vacío." }
    { group:236, id:2, text: "Incluso el enemigo más insignificante podría atravesar nuestras defensas." }
    { group:236, id:3, text: "A menos que vengan pronto nuevos trabajadores, la ciudad se verá afectada." }
    { group:236, id:4, text: "La literatura está llena de historias de dioses enfadados y sus venganzas." }
    { group:236, id:5, text: "La historia nos dice que una ciudad como la nuestra pagará cara su mala reputación." }
    { group:236, id:6, text: "En la ciudad hay muchos desempleados. Al menos tienen mucho tiempo para leer." }
    { group:236, id:7, text: "A veces me apetece ver algo que no fueran jeroglíficos. Quiero asistir a un espectáculo." }
    { group:236, id:8, text: "Esta ciudad se puede comparar con otras sobre las que he leído." }
    { group:236, id:9, text: "Esta ciudad es la mejor jamás conocida en la historia." }
    { group:237, id:0, text: "Me da miedo ir a algunos barrios. La gente está enferma y no quiero contagiarme." }
    { group:237, id:1, text: "Estoy débil por el hambre. Casi no puedo con el agua." }
    { group:237, id:2, text: "Parece que, si hay un ataque, la defensa de la ciudad dependerá de los ciudadanos." }
    { group:237, id:3, text: "Trabajo, trabajo por todas partes y ningún trabajador." }
    { group:237, id:4, text: "Si fuera un dios no estaría contento con la falta de atención de esta ciudad." }
    { group:237, id:5, text: "He oído que otras ciudades se ríen de nosotros y están planeando una invasión." }
    { group:237, id:6, text: "Cuando hago mis repartos veo a mucha gente en paro." }
    { group:237, id:7, text: "Llevar agua no es un entretenimiento. Me gustaría que hubiera diversiones de verdad." }
    { group:237, id:8, text: "Me gusta vivir aquí, pero si yo dirigiera la ciudad haría las cosas de otra forma." }
    { group:237, id:9, text: "No hay un lugar mejor sobre la tierra." }
    { group:238, id:0, text: "La gente está tan preocupada por la epidemia que nadie se preocupa por la salud dental." }
    { group:238, id:1, text: "Últimamente he comido tan poco... Qué desperdicio de dientes perfectos." }
    { group:238, id:2, text: "Las defensas de la ciudad están cariadas. Los enemigos podrían atacarnos." }
    { group:238, id:3, text: "La mano de obra de la ciudad es como la boca de un viejo. ¡Hay que cubrir tantos huecos!" }
    { group:238, id:4, text: "Me preocupan los molares, digo la moralidad, de la ciudad. Tenemos que mostrar más respeto a los dioses." }
    { group:238, id:5, text: "Nuestra reputación es pésima. Nos podrían atacar." }
    { group:238, id:6, text: "¡Jamás había visto a tanta gente en paro!" }
    { group:238, id:7, text: "¡Me aburro! Supongo que tendré que cepillarme los dientes de nuevo." }
    { group:238, id:8, text: "Esta ciudad está bien. Tan sólo hay unas pocas caries." }
    { group:238, id:9, text: "Esta ciudad tiene la sonrisa más resplandeciente de todo Egipto." }
    { group:239, id:0, text: "Últimamente estoy muy ocupado. Cada vez hay más gente enferma." }
    { group:239, id:1, text: "Tener hambre todo el día no me ayuda a trabajar mejor." }
    { group:239, id:2, text: "Creo que la ciudad debería reforzar las defensas, para que los enemigos no nos ataquen." }
    { group:239, id:3, text: "He atendido a mucha gente con agotamiento por exceso de trabajo. Esta ciudad necesita mano de obra." }
    { group:239, id:4, text: "No creo que mostremos a los dioses suficiente respeto. Es un comportamiento muy arriesgado." }
    { group:239, id:5, text: "Nuestra mala reputación invita a que nos ataquen." }
    { group:239, id:6, text: "Haraganear en espera de empleos no es bueno para la salud de nuestra gente." }
    { group:239, id:7, text: "Hay quien viene a hacerse un chequeo simplemente porque no tiene nada mejor que hacer." }
    { group:239, id:8, text: "Supongo que esta ciudad es suficientemente buena." }
    { group:239, id:9, text: "Esta ciudad goza de magnífica salud." }
    { group:239, id:10, text: "Una epidemia mortal podría asolar la ciudad en cualquier momento." }
    { group:240, id:0, text: "Parece que la sanidad está empeorando por toda la ciudad." }
    { group:240, id:1, text: "A juzgar por el número de enfermos de la ciudad, pronto seré rico." }
    { group:240, id:2, text: "Estoy muerto de hambre. Dentro de poco, estaré más flaco que una momia." }
    { group:240, id:3, text: "La ciudad no tiene unas buenas defensas. Un enemigo podría derrotarnos fácilmente." }
    { group:240, id:4, text: "Si quiero dejar de embalsamar, éste es el momento. Hay muchos puestos de trabajo." }
    { group:240, id:5, text: "Los dioses podrían deshacerse pronto de nuestra ciudad si no les mostramos más respeto." }
    { group:240, id:6, text: "La mala reputación de la ciudad podría matarnos a todos. Nos pueden atacar en cualquier momento." }
    { group:240, id:7, text: "Cuando veo a tanta gente en paro me alegro de tener trabajo." }
    { group:240, id:8, text: "Esta ciudad está tan muerta como los cuerpos con los que trabajo todo el día. Desearía que la ciudad estuviera rebosante de entretenimientos." }
    { group:240, id:9, text: "Podría vivir aquí siempre. Es tan buen sitio como cualquier otro." }
    { group:240, id:10, text: "Lo siento mucho por mis clientes. No van a poder disfrutar de esta increíble ciudad." }
    { group:241, id:0, text: "(Not used)" }
    { group:241, id:1, text: "Aquí no parece que la malaria sea un problema." }
    { group:241, id:2, text: "Si no se hace algo, podría aparecer un brote de malaria." }
    { group:242, id:0, text: "Espero que no estalle una epidemia. Algunas se extienden como el fuego." }
    { group:242, id:1, text: "Ni siquiera mientras apago incendios puedo dejar de pensar en el hambre que tengo." }
    { group:242, id:2, text: "Si nos invadiera algún enemigo podría arder toda la ciudad." }
    { group:242, id:3, text: "Temo que alguno de esos edificios medio vacíos pueda incendiarse. Me gustaría que hubiera más trabajadores." }
    { group:242, id:4, text: "La implacable ira de los dioses caerá sobre nosotros, si no les mostramos más respeto." }
    { group:242, id:5, text: "Jamás dejaría que mi reputación cayera tan bajo como la de la ciudad. Nos van a atacar en cualquier momento." }
    { group:242, id:6, text: "Hay más voluntarios para el parque de bomberos. Esta gente necesita un empleo." }
    { group:242, id:7, text: "Apagar incendios es un trabajo duro y me gustaría distraerme con un buen espectáculo. Aquí no hay suficientes." }
    { group:242, id:8, text: "Estoy contento con esta ciudad." }
    { group:242, id:9, text: "Esta ciudad es genial." }
    { group:242, id:10, text: "Ahora no puedo hablar. Estoy ocupado apagando este incendio." }
    { group:242, id:11, text: "¡Si no actúo rápidamente, este incendio puede arrasar toda la ciudad!" }
    { group:242, id:12, text: "¡Oh, eso está caliente!" }
    { group:243, id:0, text: "Hay mucha gente en peor estado que los edificios. Espero que las cosas no empeoren." }
    { group:243, id:1, text: "Puede que el hambre no afecte a la resistencia de estos edificios, pero sí afecta a la mía." }
    { group:243, id:2, text: "¿Qué haremos si nos atacan? Las defensas de la ciudad son ridículas." }
    { group:243, id:3, text: "¿Qué importancia tiene que esos edificios se derrumben? De todas formas, no hay trabajadores dentro." }
    { group:243, id:4, text: "Si los dioses están enfadados, ni siquiera el mejor arquitecto puede reparar el daño que causan." }
    { group:243, id:5, text: "La reputación de la ciudad es tan baja que temo que los enemigos nos ataquen." }
    { group:243, id:6, text: "A mi juicio, hay mucha gente en paro." }
    { group:243, id:7, text: "Hmmm. Incluso a los arquitectos nos gusta un poco de diversión." }
    { group:243, id:8, text: "La vida podría ser mucho peor." }
    { group:243, id:9, text: "Esta ciudad tiene todo lo que un arquitecto podría desear." }
    { group:243, id:10, text: "Hay tantos lugares en penosas condiciones que no doy abasto." }
    { group:243, id:11, text: "Espero que se me reconozca el mérito por el buen estado de esta ciudad." }
    { group:244, id:0, text: "Hay tanta gente débil y enferma que temo por el futuro." }
    { group:244, id:1, text: "Hace tanto tiempo que no como que empiezo a pensar en robar algo de comida." }
    { group:244, id:2, text: "Si nos invaden, parece que me tocará a mí solo defender la ciudad." }
    { group:244, id:3, text: "Si no me gustara el riesgo del trabajo policial, cogería sin pensarlo uno de los muchos empleos disponibles." }
    { group:244, id:4, text: "Si yo gobernara, prestaría más atención a los dioses." }
    { group:244, id:5, text: "He oído que nuestra ciudad es un blanco fácil para los invasores. Tenemos mala reputación." }
    { group:244, id:6, text: "No me gusta ver a todos estos desempleados por todas partes. ¡No puedo hacer mi ronda sin tropezar con ellos!" }
    { group:244, id:7, text: "Esta ciudad es aburrida. No hay buenos espectáculos que ver." }
    { group:244, id:8, text: "Esta ciudad no es perfecta, pero ¿qué ciudad lo es?" }
    { group:244, id:9, text: "Si el bazar repartiera más variedad de pasteles, la ciudad sería perfecta." }
    { group:244, id:10, text: "Aquí todo el mundo se lleva bien. Prácticamente no se cometen delitos." }
    { group:244, id:11, text: "Unos delitos aquí, otros allí, pero nada fuera de lo normal." }
    { group:244, id:12, text: "Ni siquiera a mí me gusta adentrarme en esa zona de la ciudad." }
    { group:244, id:13, text: "Ahora estoy muy ocupado para hablar, pregúntame más tarde." }
    { group:244, id:14, text: "Contribuiré en lo que pueda para evitar que esta ciudad sea peligrosa." }
    { group:244, id:15, text: "La lucha contra los invasores no figura en mi contrato." }
    { group:244, id:16, text: "Esos bribones no se adueñarán de la ciudad mientras esté bajo mi vigilancia." }
    { group:244, id:17, text: "Si no consigo ayuda pronto, el enemigo podría ganar." }
    { group:245, id:0, text: "Parece que una enfermedad está mermando la salud de la gente. Espero que no estalle una epidemia." }
    { group:245, id:1, text: "Me gustaría que la gente pagara los impuestos en comida. ¡Me muero de hambre!" }
    { group:245, id:2, text: "Nuestra ciudad no parece capaz de defenderse." }
    { group:245, id:3, text: "Por muchos impuestos que cobremos, esto seguirá siendo un desastre. Necesitamos más trabajadores." }
    { group:245, id:4, text: "Tenemos una gran deuda con los dioses y no quiero estar aquí cuando vengan a cobrarla." }
    { group:245, id:5, text: "He oído que la invasión es inminente, a causa de nuestra reputación en Egipto." }
    { group:245, id:6, text: "En muchas de esas casas hay desempleados. ¿Cómo van a pagar impuestos?" }
    { group:245, id:7, text: "Por mucho que me guste recaudar impuestos, también me gustaría ver un espectáculo profesional." }
    { group:245, id:8, text: "La vida no es demasiado mala aquí." }
    { group:245, id:9, text: "Prefiero vivir aquí antes que en cualquier otro lugar." }
    { group:245, id:10, text: "Esta ciudad podría tener más ingresos si contara con más recaudadores de impuestos." }
    { group:245, id:11, text: "Parece que cuanto mejor es su casa, más se queja la gente a la hora de pagar su parte." }
    { group:245, id:12, text: "Odio recaudar impuestos en estas casas pobres. No vale la pena el tiempo que pierdo." }
    { group:246, id:0, text: "Las condiciones sanitarias de esta ciudad son penosas. La epidemia es el castigo que cuadra con el delito." }
    { group:246, id:1, text: "Tengo tanta hambre que una buena comida compraría cualquier veredicto." }
    { group:246, id:2, text: "¡Qué defensas más lamentables! Nuestros enemigos podrían entrar en la ciudad y hacerse con ella." }
    { group:246, id:3, text: "Jamás había visto tantos trabajos vacantes." }
    { group:246, id:4, text: "Los dioses nos declararán culpables de negligencia si no empezamos a prestarles más atención" }
    { group:246, id:5, text: "Nuestra ciudad es una de las peores del imperio. Temo que se ejecute nuestro castigo." }
    { group:246, id:6, text: "Los parados disponen de mucho tiempo libre y eso es peligroso." }
    { group:246, id:7, text: "Esta ciudad es culpable de tener pocas opciones de entretenimiento." }
    { group:246, id:8, text: "Esta ciudad está en equilibrio: nada demasiado bueno, pero nada demasiado malo." }
    { group:246, id:9, text: "Juzgaría a esta ciudad como la mejor." }
    { group:246, id:10, text: "(sin uso)" }
    { group:246, id:11, text: "Espero ganarme una comitiva funeraria cuando llegue el momento." }
    { group:246, id:12, text: "En el juzgado todo está tranquilo. Aquí no se cometen delitos." }
    { group:246, id:13, text: "Tan sólo he juzgado casos insignificantes. Nada demasiado serio." }
    { group:246, id:14, text: "Apenas doy abasto, pero las calles aún no son seguras." }
    { group:247, id:0, text: "¡Necesitan mis cualidades como pintor y yesero en el monumento!" }
    { group:247, id:1, text: "Plasmo las historias de Egipto en las paredes de las tumbas reales." }
    { group:248, id:0, text: "¡El oro debería ser para los vivos, no para los muertos!" }
    { group:248, id:1, text: "¡Piensa en la fortuna que conseguiré cuando venda todos esos tesoros!" }
    { group:249, id:0, text: "¡Lucharemos hasta la muerte para defender nuestra bella ciudad!" }
    { group:249, id:1, text: "¡El enemigo es superior! Si escapamos, podremos luchar otro día." }
    { group:249, id:2, text: "¡Los enemigos se acercan!" }
    { group:249, id:3, text: "Somos tan peligrosos como un cocodrilo, listos para atacar a los invasores cuando lleguen." }
    { group:249, id:4, text: "Cuando lleguen los enemigos, estaremos preparados." }
    { group:250, id:0, text: "¡Remad más rápido! Debemos proteger nuestro barco a toda costa." }
    { group:250, id:1, text: "El enemigo está aquí. Todos preparados para maniobrar." }
    { group:250, id:2, text: "¡Al ataque! Estamos preparados" }
    { group:250, id:3, text: "Estamos preparados para combatir si surge la necesidad." }
    { group:251, id:0, text: "Chariot Exact 1" }
    { group:252, id:0, text: "No se avistan enemigos, pero estamos preparados." }
    { group:252, id:1, text: "Estamos preparados y ansiosos por derrotar al enemigo que se acerca." }
    { group:252, id:2, text: "¿Llamas ejército a eso? No tendremos problemas para derrotar a esa variopinta tripulación." }
    { group:252, id:3, text: "Este enemigo es implacable. Hago todo lo que puedo para derrotarlo." }
    { group:253, id:0, text: "Templo del Sol" }
    { group:253, id:1, text: "Fase 1" }
    { group:253, id:2, text: "Se ha colocado la estructura del obelisco" }
    { group:253, id:3, text: "y los trabajadores están despejando el lugar" }
    { group:253, id:4, text: "Fase 2" }
    { group:253, id:5, text: "Los carpinteros están colocando andamiajes alrededor del" }
    { group:253, id:6, text: "obelisco" }
    { group:253, id:7, text: "Fase 3" }
    { group:253, id:8, text: "Los canteros están tallando la figura final" }
    { group:253, id:9, text: "del obelisco" }
    { group:253, id:10, text: "Fase 4" }
    { group:253, id:11, text: "El vestíbulo, el muro, la plaza y" }
    { group:253, id:12, text: "la parte anterior del templo se están construyendo" }
    { group:253, id:13, text: "Un solo cantero está esperando la piedra." }
    { group:253, id:14, text: "los canteros están esperando la piedra." }
    { group:253, id:15, text: "El templo del Sol está" }
    { group:253, id:16, text: "porcentaje terminado" }
    { group:253, id:17, text: "bloques de piedra necesarios para" }
    { group:253, id:18, text: "terminar la construcción del templo del Sol." }
    { group:254, id:0, text: "Sutymose" }
    { group:254, id:1, text: "Nimlot" }
    { group:254, id:2, text: "Pamu" }
    { group:254, id:3, text: "Shabaka" }
    { group:254, id:4, text: "Zazamoukh" }
    { group:254, id:5, text: "Wahka" }
    { group:254, id:6, text: "Osorkon" }
    { group:254, id:7, text: "Jarha" }
    { group:254, id:8, text: "Genubath" }
    { group:254, id:9, text: "Bakenmut" }
    { group:254, id:10, text: "Wepwawetmose" }
    { group:254, id:11, text: "Wahankh" }
    { group:254, id:12, text: "Ankhnefer" }
    { group:254, id:13, text: "Horwebbefer" }
    { group:254, id:14, text: "Horapollo" }
    { group:254, id:15, text: "Kaka" }
    { group:254, id:16, text: "Khensthoth" }
    { group:254, id:17, text: "Kha'y" }
    { group:254, id:18, text: "Inarus" }
    { group:254, id:19, text: "Herenamenpenaef" }
    { group:254, id:20, text: "Narmer" }
    { group:254, id:21, text: "Nebitka" }
    { group:254, id:22, text: "Nebmaatre" }
    { group:254, id:23, text: "Naga-ed-der" }
    { group:254, id:24, text: "Menmire" }
    { group:254, id:25, text: "Amenmose" }
    { group:254, id:26, text: "Addaya" }
    { group:254, id:27, text: "Ankhsheshonq" }
    { group:254, id:28, text: "Benermerut" }
    { group:254, id:29, text: "Djedptahefankh" }
    { group:254, id:30, text: "Akunosh" }
    { group:254, id:31, text: "Amenhirkopshef" }
    { group:254, id:32, text: "Ameneheb" }
    { group:254, id:33, text: "Apophis" }
    { group:254, id:34, text: "Bakenkhonsu" }
    { group:254, id:35, text: "Deniuenkhons" }
    { group:254, id:36, text: "Heqamaatre" }
    { group:254, id:37, text: "Horemheb" }
    { group:254, id:38, text: "Hornedjitef" }
    { group:254, id:39, text: "Horpais" }
    { group:254, id:40, text: "Harkhuf" }
    { group:254, id:41, text: "Harmhabi" }
    { group:254, id:42, text: "Ibana" }
    { group:254, id:43, text: "Irhoreru" }
    { group:254, id:44, text: "Ishpi" }
    { group:254, id:45, text: "Iufankh" }
    { group:254, id:46, text: "Iufenamun" }
    { group:254, id:47, text: "Iuseneb" }
    { group:254, id:48, text: "Kadjadja" }
    { group:254, id:49, text: "Khonsirdais" }
    { group:254, id:50, text: "Khakheperraseneb" }
    { group:254, id:51, text: "Manetho" }
    { group:254, id:52, text: "Menmet-Ra" }
    { group:254, id:53, text: "Merirahasetef" }
    { group:254, id:54, text: "Mernebptah" }
    { group:254, id:55, text: "Meryrahashtef" }
    { group:254, id:56, text: "Neferhotep" }
    { group:254, id:57, text: "Neshorpakhered" }
    { group:254, id:58, text: "Miankkhnum" }
    { group:254, id:59, text: "Niumateped" }
    { group:254, id:60, text: "Pedibastet" }
    { group:254, id:61, text: "Qenymin" }
    { group:254, id:62, text: "Rudiju" }
    { group:254, id:63, text: "Sneferu" }
    { group:254, id:64, text: "Heptseshet" }
    { group:254, id:65, text: "Amkhaibitu" }
    { group:254, id:66, text: "Maatafemsesh" }
    { group:254, id:67, text: "Setqesu" }
    { group:254, id:68, text: "Taret" }
    { group:254, id:69, text: "Hetchabehu" }
    { group:254, id:70, text: "Amsenef" }
    { group:254, id:71, text: "Ambesek" }
    { group:254, id:72, text: "Thenemi" }
    { group:254, id:73, text: "Sethgregorshef" }
    { group:254, id:74, text: "Hansptah" }
    { group:254, id:75, text: "Ankhenrimhat" }
    { group:254, id:76, text: "Nenedjasondjed" }
    { group:254, id:77, text: "Jeremshepenwet" }
    { group:254, id:78, text: "Sasolomonmut" }
    { group:254, id:79, text: "Rajohnhotep" }
    { group:254, id:80, text: "Kethnakte" }
    { group:254, id:81, text: "Akenaba" }
    { group:254, id:82, text: "Shmikenakht" }
    { group:254, id:83, text: "Roneith" }
    { group:254, id:84, text: "Ankhscotshonq" }
    { group:254, id:85, text: "Amenwaynsu" }
    { group:254, id:86, text: "Tanutamun" }
    { group:254, id:87, text: "Wadjtonymose" }
    { group:254, id:88, text: "Labarjamoukh" }
    { group:254, id:89, text: "Saltsenkhamen" }
    { group:254, id:90, text: "Zizzamoukh" }
    { group:254, id:91, text: "Pramessu" }
    { group:254, id:92, text: "Sipair" }
    { group:254, id:93, text: "Shawnbaka" }
    { group:254, id:94, text: "Sisekhmet" }
    { group:254, id:95, text: "Panas" }
    { group:254, id:96, text: "Maakha" }
    { group:254, id:97, text: "Butehamun" }
    { group:254, id:98, text: "Nekhen" }
    { group:254, id:99, text: "Ankhu" }
    { group:254, id:100, text: "Craigamun" }
    { group:254, id:101, text: "Remensses" }
    { group:254, id:102, text: "Ashaamedes" }
    { group:254, id:103, text: "Ib'remedes" }
    { group:254, id:104, text: "Bewethaat" }
    { group:254, id:105, text: "Inyotef" }
    { group:254, id:106, text: "Niankhkhnum" }
    { group:254, id:107, text: "Khnumhotep" }
    { group:254, id:108, text: "Sinuhe" }
    { group:254, id:109, text: "Senwosret" }
    { group:254, id:110, text: "Setka" }
    { group:254, id:111, text: "Niumateped" }
    { group:254, id:112, text: "Ahkenrusses" }
    { group:254, id:113, text: "Padalineith" }
    { group:254, id:114, text: "Montuhotep" }
    { group:254, id:115, text: "Keraghotep" }
    { group:254, id:116, text: "Montumery" }
    { group:254, id:117, text: "Horemchadhotep" }
    { group:254, id:118, text: "Meryrahashtef" }
    { group:254, id:119, text: "Ipy" }
    { group:254, id:120, text: "Akunosh" }
    { group:254, id:121, text: "Akencheres" }
    { group:254, id:122, text: "Djedptahefankh" }
    { group:254, id:123, text: "Herenamenpenaef" }
    { group:254, id:124, text: "Simontu" }
    { group:254, id:125, text: "Mekuniwetel" }
    { group:254, id:126, text: "Nespanetjerenpere" }
    { group:254, id:127, text: "Shedsunefertum" }
    { group:255, id:0, text: "Tutu" }
    { group:255, id:1, text: "Shewet" }
    { group:255, id:2, text: "Bebaat" }
    { group:255, id:3, text: "Neferheret" }
    { group:255, id:4, text: "Naasheba" }
    { group:255, id:5, text: "Nebabui" }
    { group:255, id:6, text: "Webaoner" }
    { group:255, id:7, text: "Ramesses" }
    { group:255, id:8, text: "Hemjunu" }
    { group:255, id:9, text: "Ptahhotep" }
    { group:255, id:10, text: "Imhotep" }
    { group:255, id:11, text: "Prehotep" }
    { group:255, id:12, text: "Amasis" }
    { group:255, id:13, text: "Ptahnefer" }
    { group:255, id:14, text: "Impeihotep" }
    { group:255, id:15, text: "Menkaure" }
    { group:255, id:16, text: "Gebu" }
    { group:255, id:17, text: "Ankh-hori" }
    { group:255, id:18, text: "Khonshotep" }
    { group:255, id:19, text: "Khonsnefru" }
    { group:255, id:20, text: "Merykhons" }
    { group:255, id:21, text: "Beshotep" }
    { group:255, id:22, text: "Merybes" }
    { group:255, id:23, text: "Ptahhudjankhef" }
    { group:255, id:24, text: "Meryedjo" }
    { group:255, id:25, text: "Edjohotep" }
    { group:255, id:26, text: "Heqetmeses" }
    { group:255, id:27, text: "Menheqet" }
    { group:255, id:28, text: "Akenheqet" }
    { group:255, id:29, text: "Kheprihotep" }
    { group:255, id:30, text: "Akenkhepri" }
    { group:255, id:31, text: "Merykhepri" }
    { group:256, id:0, text: "Itchenkhamen" }
    { group:256, id:1, text: "Techemes" }
    { group:256, id:2, text: "Djesersukhons" }
    { group:256, id:3, text: "Ay" }
    { group:256, id:4, text: "Aadmeru" }
    { group:256, id:5, text: "Nebumery" }
    { group:256, id:6, text: "Nebaak" }
    { group:256, id:7, text: "Burglakhamen" }
    { group:256, id:8, text: "Amunloot" }
    { group:256, id:9, text: "Pedibandit" }
    { group:256, id:10, text: "Nebnodjmet" }
    { group:256, id:11, text: "Ankhefeneb" }
    { group:256, id:12, text: "Akeneb" }
    { group:256, id:13, text: "Nebtet" }
    { group:256, id:14, text: "Nekhbehotep" }
    { group:256, id:15, text: "Herishef" }
    { group:257, id:0, text: "Nebwam" }
    { group:257, id:1, text: "Ankhmery" }
    { group:257, id:2, text: "Pasebakhaenniut" }
    { group:257, id:3, text: "Her-uben" }
    { group:257, id:4, text: "Seshed" }
    { group:257, id:5, text: "Kingmery" }
    { group:257, id:6, text: "Pedidavi" }
    { group:257, id:7, text: "Akenturner" }
    { group:257, id:8, text: "Carnegmose" }
    { group:257, id:9, text: "Forbesankh" }
    { group:257, id:10, text: "Snotmose" }
    { group:257, id:11, text: "Rockesenmut" }
    { group:257, id:12, text: "Anhetepf" }
    { group:257, id:13, text: "Seshemfenti" }
    { group:257, id:14, text: "Minkhat" }
    { group:257, id:15, text: "Nehahra" }
    { group:257, id:16, text: "Ankhwa" }
    { group:257, id:17, text: "Yuya" }
    { group:257, id:18, text: "Kaha" }
    { group:257, id:19, text: "Poy" }
    { group:257, id:20, text: "Fraankptah" }
    { group:257, id:21, text: "Stevemeses" }
    { group:257, id:22, text: "Merymar" }
    { group:257, id:23, text: "Tjanefer" }
    { group:257, id:24, text: "Takany" }
    { group:257, id:25, text: "Wadjet" }
    { group:257, id:26, text: "Paser" }
    { group:257, id:27, text: "Hetchabehu" }
    { group:257, id:28, text: "Hrafhaf" }
    { group:257, id:29, text: "Nehahra" }
    { group:257, id:30, text: "Nehawelti" }
    { group:257, id:31, text: "Neret" }
    { group:258, id:0, text: "Onurishotep" }
    { group:258, id:1, text: "Meryonuris" }
    { group:258, id:2, text: "Onurisnodjmet" }
    { group:258, id:3, text: "Karem" }
    { group:258, id:4, text: "Iuseneb" }
    { group:258, id:5, text: "Khahor" }
    { group:258, id:6, text: "Wahmery" }
    { group:258, id:7, text: "Ankhmery" }
    { group:258, id:8, text: "Techemesmery" }
    { group:258, id:9, text: "Nestanebetasheru" }
    { group:258, id:10, text: "Raia" }
    { group:258, id:11, text: "Shedsunefertum" }
    { group:258, id:12, text: "Serapion" }
    { group:258, id:13, text: "Tymisba" }
    { group:258, id:14, text: "Taharqa" }
    { group:258, id:15, text: "Panehsy" }
    { group:259, id:0, text: "Apoutit" }
    { group:259, id:1, text: "Amanishakheto" }
    { group:259, id:2, text: "Abana" }
    { group:259, id:3, text: "Bunefer" }
    { group:259, id:4, text: "Hatshepsut" }
    { group:259, id:5, text: "Hettimenhu" }
    { group:259, id:6, text: "Iras" }
    { group:259, id:7, text: "Khamereernebty" }
    { group:259, id:8, text: "Kiya" }
    { group:259, id:9, text: "Mehetweshket" }
    { group:259, id:10, text: "Kristenefer" }
    { group:259, id:11, text: "Nefertiti" }
    { group:259, id:12, text: "Neferkatia" }
    { group:259, id:13, text: "Shananofru" }
    { group:259, id:14, text: "Awildamer" }
    { group:259, id:15, text: "Andremose" }
    { group:259, id:16, text: "Hetemaria" }
    { group:259, id:17, text: "Heidinefer" }
    { group:259, id:18, text: "Lisatiti" }
    { group:259, id:19, text: "Duatnefret" }
    { group:259, id:20, text: "Nyla" }
    { group:259, id:21, text: "Donamoses" }
    { group:259, id:22, text: "Claudipatra" }
    { group:259, id:23, text: "Tabubu" }
    { group:259, id:24, text: "Tetisheri" }
    { group:259, id:25, text: "Yunet" }
    { group:259, id:26, text: "Weretimtes" }
    { group:259, id:27, text: "Pebatma" }
    { group:259, id:28, text: "Sofiwepet" }
    { group:259, id:29, text: "Neferneferuaten" }
    { group:259, id:30, text: "Ubastet" }
    { group:259, id:31, text: "Baktwerel" }
    { group:260, id:0, text: "Marakhen" }
    { group:260, id:1, text: "Seshedakhen" }
    { group:260, id:2, text: "Nebuakhen" }
    { group:260, id:3, text: "Hedjakhen" }
    { group:260, id:4, text: "Siamun" }
    { group:260, id:5, text: "Nodjmet" }
    { group:260, id:6, text: "Amenemopet" }
    { group:260, id:7, text: "Mekuniwetel" }
    { group:260, id:8, text: "Meryptah" }
    { group:260, id:9, text: "Naneferkeptah" }
    { group:260, id:10, text: "Neshi" }
    { group:260, id:11, text: "Padiamenet" }
    { group:260, id:12, text: "Shepenwepet" }
    { group:260, id:13, text: "Udjahorresne" }
    { group:260, id:14, text: "Wenis" }
    { group:260, id:15, text: "Payneferher" }
    { group:261, id:0, text: "Maestro del Nilo" }
    { group:261, id:1, text: "Orgullo de Osiris" }
    { group:261, id:2, text: "Crucero de Tefnut" }
    { group:261, id:3, text: "Abastecedor" }
    { group:261, id:4, text: "Comerciante rápido" }
    { group:261, id:5, text: "Brisa" }
    { group:261, id:6, text: "Negociante" }
    { group:261, id:7, text: "Comerciante nuevo" }
    { group:261, id:8, text: "Canjeador" }
    { group:261, id:9, text: "Barcaza de abundancia" }
    { group:261, id:10, text: "Granada" }
    { group:261, id:11, text: "Navegante" }
    { group:261, id:12, text: "Generosidad de Ptah" }
    { group:261, id:13, text: "Alcahuete" }
    { group:261, id:14, text: "Demandante" }
    { group:261, id:15, text: "Proveedor" }
    { group:262, id:0, text: "Searseneb" }
    { group:262, id:1, text: "Akenwalmart" }
    { group:262, id:2, text: "Bakenbradleehotep" }
    { group:262, id:3, text: "Nefermacy" }
    { group:262, id:4, text: "Pennybastet" }
    { group:262, id:5, text: "Gapahmose" }
    { group:262, id:6, text: "Amunherpanesha" }
    { group:262, id:7, text: "Huya" }
    { group:262, id:8, text: "Nigmed" }
    { group:262, id:9, text: "Paperpa" }
    { group:262, id:10, text: "Tefibi" }
    { group:262, id:11, text: "Amihotep" }
    { group:262, id:12, text: "Kevinefer" }
    { group:262, id:13, text: "Tobykhamen" }
    { group:262, id:14, text: "Pebes" }
    { group:262, id:15, text: "Salatis" }
    { group:263, id:0, text: "Hapimen" }
    { group:263, id:1, text: "Tielamun" }
    { group:263, id:2, text: "Nebrianmes" }
    { group:263, id:3, text: "Harsiese" }
    { group:263, id:4, text: "Bay" }
    { group:263, id:5, text: "Bek" }
    { group:263, id:6, text: "Serkheru" }
    { group:263, id:7, text: "Dannikhamen" }
    { group:263, id:8, text: "Meryhem" }
    { group:263, id:9, text: "Pethotep" }
    { group:263, id:10, text: "Wenefakhen" }
    { group:263, id:11, text: "Shetchaat" }
    { group:263, id:12, text: "Heredhotep" }
    { group:263, id:13, text: "Ahinodjmet" }
    { group:263, id:14, text: "Ahitut" }
    { group:263, id:15, text: "Nodjmet-ta-sherit" }
    { group:263, id:16, text: "Pepi" }
    { group:263, id:17, text: "Thothotep" }
    { group:263, id:18, text: "Smendes" }
    { group:263, id:19, text: "Sithoth" }
    { group:263, id:20, text: "Minmery" }
    { group:263, id:21, text: "Siunnefer" }
    { group:263, id:22, text: "Unneferhotep" }
    { group:263, id:23, text: "Minhotep" }
    { group:263, id:24, text: "Merythoth" }
    { group:263, id:25, text: "Djau" }
    { group:263, id:26, text: "Bakenaten" }
    { group:263, id:27, text: "Ishpi" }
    { group:263, id:28, text: "Katep" }
    { group:263, id:29, text: "Pathemwia" }
    { group:263, id:30, text: "Nigmed" }
    { group:263, id:31, text: "Suty" }
    { group:264, id:0, text: "Yoyomaatre" }
    { group:264, id:1, text: "Bakenabbamaat" }
    { group:264, id:2, text: "Claudipaatra" }
    { group:264, id:3, text: "Wia" }
    { group:264, id:4, text: "Wabkhet" }
    { group:264, id:5, text: "Heret" }
    { group:264, id:6, text: "Naunakht" }
    { group:264, id:7, text: "Heria" }
    { group:264, id:8, text: "Hunro" }
    { group:264, id:9, text: "Haphen-refer" }
    { group:264, id:10, text: "Retep" }
    { group:264, id:11, text: "Hatshepsut" }
    { group:264, id:12, text: "Nofertiri" }
    { group:264, id:13, text: "Ptennisnet" }
    { group:264, id:14, text: "Ankhesenaten" }
    { group:264, id:15, text: "Apoutit" }
    { group:264, id:16, text: "Beketaten" }
    { group:264, id:17, text: "Dedi" }
    { group:264, id:18, text: "Duathor" }
    { group:264, id:19, text: "Esemkhebe" }
    { group:264, id:20, text: "Hathor" }
    { group:264, id:21, text: "Hehenhit" }
    { group:264, id:22, text: "Henutnofret" }
    { group:264, id:23, text: "Hetepheres" }
    { group:264, id:24, text: "Iniihue" }
    { group:264, id:25, text: "Ipip" }
    { group:264, id:26, text: "Isetnofret" }
    { group:264, id:27, text: "Iutenheb" }
    { group:264, id:28, text: "Karem" }
    { group:264, id:29, text: "Khamaat" }
    { group:264, id:30, text: "Kiya" }
    { group:264, id:31, text: "Meketre" }
    { group:265, id:0, text: "Mercia" }
    { group:265, id:1, text: "Bunefer" }
    { group:265, id:2, text: "Ipuky" }
    { group:265, id:3, text: "Innovandora" }
    { group:265, id:4, text: "Sinuhe" }
    { group:265, id:5, text: "Nebefer" }
    { group:265, id:6, text: "Nenufer" }
    { group:265, id:7, text: "Neskhons" }
    { group:265, id:8, text: "Pekersater" }
    { group:265, id:9, text: "Reddjedet" }
    { group:265, id:10, text: "Seshseshet" }
    { group:265, id:11, text: "Tabubu" }
    { group:265, id:12, text: "Taweret" }
    { group:265, id:13, text: "Tefenet" }
    { group:265, id:14, text: "Ubastet" }
    { group:265, id:15, text: "Wenis" }
    { group:266, id:0, text: "Siosiris" }
    { group:266, id:1, text: "Osirishotep" }
    { group:266, id:2, text: "Pedosiris" }
    { group:266, id:3, text: "Akenosiris" }
    { group:266, id:4, text: "Wahosiris" }
    { group:266, id:5, text: "Tutankhosiris" }
    { group:266, id:6, text: "Merenosiris" }
    { group:266, id:7, text: "Iufosiris" }
    { group:266, id:8, text: "Sebekhotep" }
    { group:266, id:9, text: "Sisebek" }
    { group:266, id:10, text: "Wasebek" }
    { group:266, id:11, text: "Akensebek" }
    { group:266, id:12, text: "Pedimin" }
    { group:266, id:13, text: "Tutankhmin" }
    { group:266, id:14, text: "Merymin" }
    { group:266, id:15, text: "Akenmin" }
    { group:267, id:0, text: "Menma'atra" }
    { group:267, id:1, text: "Akenra" }
    { group:267, id:2, text: "Nefera" }
    { group:267, id:3, text: "Ranofret" }
    { group:267, id:4, text: "Mutnodra" }
    { group:267, id:5, text: "Meryra" }
    { group:267, id:6, text: "Ramose" }
    { group:267, id:7, text: "Rashepses" }
    { group:267, id:8, text: "Ma'athotep" }
    { group:267, id:9, text: "Meryma'at" }
    { group:267, id:10, text: "Pedima'at" }
    { group:267, id:11, text: "Neferma'at" }
    { group:267, id:12, text: "Akenhorus" }
    { group:267, id:13, text: "Iunhorus" }
    { group:267, id:14, text: "Bakenhorus" }
    { group:267, id:15, text: "Wahorus" }
    { group:268, id:0, text: "Ptahhotep" }
    { group:268, id:1, text: "Ptahhudjankef" }
    { group:268, id:2, text: "Ptahmose" }
    { group:268, id:3, text: "Pediptah" }
    { group:268, id:4, text: "Ptahhemhat-Ty" }
    { group:268, id:5, text: "Ptahhemakehet" }
    { group:268, id:6, text: "Akenptah" }
    { group:268, id:7, text: "Waptah" }
    { group:268, id:8, text: "Amonhotep" }
    { group:268, id:9, text: "Akenamon" }
    { group:268, id:10, text: "Siamon" }
    { group:268, id:11, text: "Bakenamon" }
    { group:268, id:12, text: "Merythoth" }
    { group:268, id:13, text: "Thothnodjmet" }
    { group:268, id:14, text: "Akenthoth" }
    { group:268, id:15, text: "Pedithoth" }
    { group:269, id:0, text: "Siseth" }
    { group:269, id:1, text: "Wahseth" }
    { group:269, id:2, text: "Sethmesses" }
    { group:269, id:3, text: "Meryseth" }
    { group:269, id:4, text: "Sethmose" }
    { group:269, id:5, text: "Pediseth" }
    { group:269, id:6, text: "Akenseth" }
    { group:269, id:7, text: "Sethnodjmet" }
    { group:269, id:8, text: "Anubishotep" }
    { group:269, id:9, text: "Anubismose" }
    { group:269, id:10, text: "Bakenanubis" }
    { group:269, id:11, text: "Sianubis" }
    { group:269, id:12, text: "Akensekhmet" }
    { group:269, id:13, text: "Sekhmetnakht" }
    { group:269, id:14, text: "Niankhsekhmet" }
    { group:269, id:15, text: "Merysekhmet" }
    { group:270, id:0, text: "Pedibast" }
    { group:270, id:1, text: "Sitbast" }
    { group:270, id:2, text: "Basthotep" }
    { group:270, id:3, text: "Bastnofret" }
    { group:270, id:4, text: "Bastmire" }
    { group:270, id:5, text: "Bastwedjebu" }
    { group:270, id:6, text: "Bastemshaf" }
    { group:270, id:7, text: "Akenbast" }
    { group:270, id:8, text: "Isetnofret" }
    { group:270, id:9, text: "Sitisis" }
    { group:270, id:10, text: "Isismose" }
    { group:270, id:11, text: "Isisnodjmet" }
    { group:270, id:12, text: "Sithathor" }
    { group:270, id:13, text: "Pedihathor" }
    { group:270, id:14, text: "Meryhathor" }
    { group:270, id:15, text: "Hathornofret" }
    { group:271, id:0, text: "Nebnefer" }
    { group:271, id:1, text: "Anhirkawi" }
    { group:271, id:2, text: "Kenhirkhopeshef" }
    { group:271, id:3, text: "Anupemheb" }
    { group:271, id:4, text: "Prahotep" }
    { group:271, id:5, text: "Panhesi" }
    { group:271, id:6, text: "Paneb" }
    { group:271, id:7, text: "Sithoth" }
    { group:271, id:8, text: "Kjaemwase" }
    { group:271, id:9, text: "Neferabu" }
    { group:271, id:10, text: "Amennakht" }
    { group:271, id:11, text: "Kha'nun" }
    { group:271, id:12, text: "Mentmose" }
    { group:271, id:13, text: "Patwere" }
    { group:271, id:14, text: "Pa'anuket" }
    { group:271, id:15, text: "Harshire" }
    { group:271, id:16, text: "Keneben" }
    { group:271, id:17, text: "Hormin" }
    { group:271, id:18, text: "Tjanefer" }
    { group:271, id:19, text: "Amenwa" }
    { group:271, id:20, text: "Pentaweret" }
    { group:271, id:21, text: "Pentahetnakht" }
    { group:271, id:22, text: "Nesamenopet" }
    { group:271, id:23, text: "Sobeksankh" }
    { group:271, id:24, text: "Pinejem" }
    { group:271, id:25, text: "Sinnejem" }
    { group:271, id:26, text: "Ankhu" }
    { group:271, id:27, text: "Ametju" }
    { group:271, id:28, text: "Rensi" }
    { group:271, id:29, text: "Khunanpu" }
    { group:271, id:30, text: "Thutinakhte" }
    { group:271, id:31, text: "Khentika" }
    { group:272, id:0, text: "Ptahshedu" }
    { group:272, id:1, text: "Ankhtifi" }
    { group:272, id:2, text: "Beshirkopshef" }
    { group:272, id:3, text: "Merybes" }
    { group:272, id:4, text: "Bakenbes" }
    { group:272, id:5, text: "Heqethotep" }
    { group:272, id:6, text: "Waheqet" }
    { group:272, id:7, text: "Nefertumhotep" }
    { group:272, id:8, text: "Merynefertum" }
    { group:272, id:9, text: "Nephthysankh" }
    { group:272, id:10, text: "Meryneith" }
    { group:272, id:11, text: "Siselkis" }
    { group:272, id:12, text: "Merytaweret" }
    { group:272, id:13, text: "Medesian" }
    { group:272, id:14, text: "Akenimsety" }
    { group:272, id:15, text: "Akenselket" }
    { group:272, id:16, text: "Si'isis" }
    { group:272, id:17, text: "Akenisis" }
    { group:272, id:18, text: "Akenfluoris" }
    { group:272, id:19, text: "Novakhamen" }
    { group:272, id:20, text: "Merytecheknen" }
    { group:272, id:21, text: "Mektyabehu" }
    { group:272, id:22, text: "Khenmrshabehu" }
    { group:272, id:23, text: "Hetch-abehu" }
    { group:272, id:24, text: "Mesedjerikem" }
    { group:272, id:25, text: "Saieb" }
    { group:272, id:26, text: "Sarekhyt" }
    { group:272, id:27, text: "Wahetau" }
    { group:272, id:28, text: "Eckerdhotep" }
    { group:272, id:29, text: "Meryrevco" }
    { group:272, id:30, text: "Bakenosco" }
    { group:272, id:31, text: "Akenbayer" }
    { group:273, id:0, text: "Tesersukhons" }
    { group:273, id:1, text: "Anubisherkhepshef" }
    { group:273, id:2, text: "Anubismose" }
    { group:273, id:3, text: "Naneferkeneith" }
    { group:273, id:4, text: "Sekerhotep" }
    { group:273, id:5, text: "Merygeb" }
    { group:273, id:6, text: "Noferanpu" }
    { group:273, id:7, text: "Anpunodjmet" }
    { group:273, id:8, text: "Tutankhanpu" }
    { group:273, id:9, text: "Meryhaat" }
    { group:273, id:10, text: "Swaadjhaat" }
    { group:273, id:11, text: "Feqaadjem" }
    { group:273, id:12, text: "Awsenef" }
    { group:273, id:13, text: "Nebseshta" }
    { group:273, id:14, text: "Benumery" }
    { group:273, id:15, text: "Duamutefhotep" }
    { group:274, id:0, text: "Abemose" }
    { group:274, id:1, text: "Meryneba" }
    { group:274, id:2, text: "Fenti" }
    { group:274, id:3, text: "Heptsesh" }
    { group:274, id:4, text: "Uath-nesert" }
    { group:274, id:5, text: "Wahnet" }
    { group:274, id:6, text: "Netti" }
    { group:274, id:7, text: "Techemes" }
    { group:274, id:8, text: "Bebaat" }
    { group:274, id:9, text: "Webed" }
    { group:274, id:10, text: "Kymery" }
    { group:274, id:11, text: "Nenesert" }
    { group:274, id:12, text: "Shemshu" }
    { group:274, id:13, text: "Hepertmenu" }
    { group:274, id:14, text: "Selkishotep" }
    { group:274, id:15, text: "Pedijon" }
    { group:275, id:0, text: "Casijonesahken" }
    { group:275, id:1, text: "Ptahshepses" }
    { group:275, id:2, text: "Pinotmou" }
    { group:275, id:3, text: "Necho" }
    { group:275, id:4, text: "Dougeptah" }
    { group:275, id:5, text: "Ptahnetjeru" }
    { group:275, id:6, text: "Sabef" }
    { group:275, id:7, text: "Salatis" }
    { group:275, id:8, text: "Pamose" }
    { group:275, id:9, text: "Siptah" }
    { group:275, id:10, text: "Hori" }
    { group:275, id:11, text: "Montuhirkopshef" }
    { group:275, id:12, text: "Fiskhamen" }
    { group:275, id:13, text: "Khufu" }
    { group:275, id:14, text: "Thutmose" }
    { group:275, id:15, text: "Nesmont" }
    { group:276, id:0, text: "Merydonut" }
    { group:276, id:1, text: "Samspadehotep" }
    { group:276, id:2, text: "Mektuankh" }
    { group:276, id:3, text: "Kojahken-ta-sherit" }
    { group:276, id:4, text: "Bluhotep" }
    { group:276, id:5, text: "Ahkenbadgaten" }
    { group:276, id:6, text: "Cuffnefer" }
    { group:276, id:7, text: "Pedibarnahmose" }
    { group:276, id:8, text: "Rasiren" }
    { group:276, id:9, text: "Magnumhotep" }
    { group:276, id:10, text: "Rockfordmaatre" }
    { group:276, id:11, text: "Kojahken" }
    { group:276, id:12, text: "Fridayahmose" }
    { group:276, id:13, text: "Polyseneb" }
    { group:276, id:14, text: "Wiggumwenemef" }
    { group:276, id:15, text: "Hammereperre" }
    { group:277, id:0, text: "Takelot" }
    { group:277, id:1, text: "Amineweh" }
    { group:277, id:2, text: "Nebuwaat" }
    { group:277, id:3, text: "Bewet" }
    { group:277, id:4, text: "Iaret" }
    { group:277, id:5, text: "Neret" }
    { group:277, id:6, text: "Ankhet" }
    { group:277, id:7, text: "Hedjemet" }
    { group:277, id:8, text: "Khenmeshemefkaat" }
    { group:277, id:9, text: "Mekeshkesh" }
    { group:277, id:10, text: "Amhetepf" }
    { group:277, id:11, text: "Avaris" }
    { group:277, id:12, text: "Raneb" }
    { group:277, id:13, text: "Rahotep" }
    { group:277, id:14, text: "Petety" }
    { group:277, id:15, text: "Bitakhen" }
    { group:278, id:0, text: "Amoy" }
    { group:278, id:1, text: "Mose" }
    { group:278, id:2, text: "Mektu" }
    { group:278, id:3, text: "Wamektu" }
    { group:278, id:4, text: "Wahikem" }
    { group:278, id:5, text: "Tutwa" }
    { group:278, id:6, text: "Tjepu" }
    { group:278, id:7, text: "Peksater" }
    { group:278, id:8, text: "Peftjauabastet" }
    { group:278, id:9, text: "Ma'athotep" }
    { group:278, id:10, text: "Pramessu" }
    { group:278, id:11, text: "Roma-Roy" }
    { group:278, id:12, text: "Sethe" }
    { group:278, id:13, text: "Senebtyfy" }
    { group:278, id:14, text: "Yanhamu" }
    { group:278, id:15, text: "Teti-en" }
    { group:279, id:0, text: "Bendición de Osiris" }
    { group:279, id:1, text: "Fortuna de Ra" }
    { group:279, id:2, text: "Favor de Ptah" }
    { group:279, id:3, text: "La gloria de Bastet" }
    { group:279, id:4, text: "Barca de Seth" }
    { group:279, id:5, text: "Garbanzo" }
    { group:279, id:6, text: "Granada" }
    { group:279, id:7, text: "Higo de Amón" }
    { group:279, id:8, text: "Ocaso" }
    { group:279, id:9, text: "Crucero del Nilo" }
    { group:279, id:10, text: "Barcaza" }
    { group:279, id:11, text: "Anquet" }
    { group:279, id:12, text: "Jnenmu" }
    { group:279, id:13, text: "La suerte de Hapi" }
    { group:279, id:14, text: "Transbordador" }
    { group:279, id:15, text: "Transportador" }
    { group:280, id:0, text: "Menmaatre" }
    { group:280, id:1, text: "Clarkenophis" }
    { group:280, id:2, text: "Ankhomallhotep" }
    { group:280, id:3, text: "Horoconnhotep" }
    { group:280, id:4, text: "Benjaseneb" }
    { group:280, id:5, text: "Khaemaleksnefer" }
    { group:280, id:6, text: "Merenadamptah" }
    { group:280, id:7, text: "Adamwenemef" }
    { group:280, id:8, text: "Bobenkhonsu" }
    { group:280, id:9, text: "Billamun" }
    { group:280, id:10, text: "Merydanseneb" }
    { group:280, id:11, text: "Pashacrisedu" }
    { group:280, id:12, text: "Wendjedarrindjed" }
    { group:280, id:13, text: "Damiankhef" }
    { group:280, id:14, text: "Nebrethotep" }
    { group:280, id:15, text: "Shependenniswepet" }
    { group:280, id:16, text: "Nesedtefnut" }
    { group:280, id:17, text: "Hericihor" }
    { group:280, id:18, text: "Gabubath" }
    { group:280, id:19, text: "Khemi" }
    { group:280, id:20, text: "Anaf" }
    { group:280, id:21, text: "Usekhnemtet" }
    { group:280, id:22, text: "Iryaahotep" }
    { group:280, id:23, text: "Aadset" }
    { group:280, id:24, text: "Medesmektu" }
    { group:280, id:25, text: "Shemshutchesm" }
    { group:280, id:26, text: "Munef" }
    { group:280, id:27, text: "Medjed" }
    { group:280, id:28, text: "Ipwetuhaat" }
    { group:280, id:29, text: "Ahkenptah" }
    { group:280, id:30, text: "Inbahken" }
    { group:280, id:31, text: "Hemethotep" }
    { group:281, id:0, text: "Keret" }
    { group:281, id:1, text: "Aqhat" }
    { group:281, id:2, text: "Shachar" }
    { group:281, id:3, text: "Shalim" }
    { group:281, id:4, text: "Yam" }
    { group:281, id:5, text: "Kothar" }
    { group:281, id:6, text: "Khasis" }
    { group:281, id:7, text: "Khirkhib" }
    { group:281, id:8, text: "Mot" }
    { group:281, id:9, text: "Resheph" }
    { group:281, id:10, text: "Yassib" }
    { group:281, id:11, text: "Hirgab" }
    { group:281, id:12, text: "Radmanu" }
    { group:281, id:13, text: "Athtar" }
    { group:281, id:14, text: "Yatpah" }
    { group:281, id:15, text: "Yarikh" }
    { group:282, id:0, text: "Psuro" }
    { group:282, id:1, text: "Psaro" }
    { group:282, id:2, text: "Karoya" }
    { group:282, id:3, text: "Kasaya" }
    { group:282, id:4, text: "Shekitku" }
    { group:282, id:5, text: "Hetauiah" }
    { group:282, id:6, text: "Hysbroze" }
    { group:282, id:7, text: "Uyek" }
    { group:282, id:8, text: "Skarabya" }
    { group:282, id:9, text: "Dogon" }
    { group:282, id:10, text: "Kubafang" }
    { group:282, id:11, text: "Medjay" }
    { group:282, id:12, text: "Askut" }
    { group:282, id:13, text: "Tjury" }
    { group:282, id:14, text: "Kumi" }
    { group:282, id:15, text: "D'lekta" }
    { group:283, id:0, text: "Abdullah" }
    { group:283, id:1, text: "Sahoser" }
    { group:283, id:2, text: "Muammar" }
    { group:283, id:3, text: "Fez" }
    { group:283, id:4, text: "Garamantes" }
    { group:283, id:5, text: "Ayoub" }
    { group:283, id:6, text: "Jamil" }
    { group:283, id:7, text: "Raafat" }
    { group:283, id:8, text: "Salheen" }
    { group:283, id:9, text: "Muskat" }
    { group:283, id:10, text: "Hishaam" }
    { group:283, id:11, text: "Ataar" }
    { group:283, id:12, text: "Faywi" }
    { group:283, id:13, text: "Khalid" }
    { group:283, id:14, text: "Wafiti" }
    { group:283, id:15, text: "Hajjaji" }
    { group:284, id:0, text: "Sebiumeker" }
    { group:284, id:1, text: "Arensuphis" }
    { group:284, id:2, text: "Kasnta" }
    { group:284, id:3, text: "Alara" }
    { group:284, id:4, text: "Piye" }
    { group:284, id:5, text: "Shabako" }
    { group:284, id:6, text: "Taharqa" }
    { group:284, id:7, text: "Apedernak" }
    { group:284, id:8, text: "Aqrakamani" }
    { group:284, id:9, text: "Natakamani" }
    { group:284, id:10, text: "Khal" }
    { group:284, id:11, text: "Grrski" }
    { group:284, id:12, text: "Sobek" }
    { group:284, id:13, text: "Kashta" }
    { group:284, id:14, text: "Shebitku" }
    { group:284, id:15, text: "Tanwetamani" }
    { group:285, id:0, text: "Qar" }
    { group:285, id:1, text: "Salitis" }
    { group:285, id:2, text: "Apop" }
    { group:285, id:3, text: "Ammi-enshi" }
    { group:285, id:4, text: "Bnon" }
    { group:285, id:5, text: "Apachnan" }
    { group:285, id:6, text: "Seshi" }
    { group:285, id:7, text: "Khamudi" }
    { group:285, id:8, text: "Khian" }
    { group:285, id:9, text: "Iannas" }
    { group:285, id:10, text: "Assis" }
    { group:285, id:11, text: "Aamu" }
    { group:285, id:12, text: "Yakbam" }
    { group:285, id:13, text: "Jacob-Her" }
    { group:285, id:14, text: "Sekhanre" }
    { group:285, id:15, text: "Yoam" }
    { group:286, id:0, text: "Pithana" }
    { group:286, id:1, text: "Labarna" }
    { group:286, id:2, text: "Hattusili" }
    { group:286, id:3, text: "Mursili" }
    { group:286, id:4, text: "Hantili" }
    { group:286, id:5, text: "Zidanta" }
    { group:286, id:6, text: "Amnuna" }
    { group:286, id:7, text: "Telipinu" }
    { group:286, id:8, text: "Huzziya" }
    { group:286, id:9, text: "Alluwamna" }
    { group:286, id:10, text: "Muwatalli" }
    { group:286, id:11, text: "Arnuwanda" }
    { group:286, id:12, text: "Tudhaliya" }
    { group:286, id:13, text: "Suppiluliuma" }
    { group:286, id:14, text: "Karunta" }
    { group:286, id:15, text: "Anitta" }
    { group:287, id:0, text: "Goliath" }
    { group:287, id:1, text: "Beelzebub" }
    { group:287, id:2, text: "Abimelech" }
    { group:287, id:3, text: "Phicol" }
    { group:287, id:4, text: "Achish" }
    { group:287, id:5, text: "Ahaziah" }
    { group:287, id:6, text: "Minos" }
    { group:287, id:7, text: "Dagon" }
    { group:287, id:8, text: "Potidas" }
    { group:287, id:9, text: "Alcinous" }
    { group:287, id:10, text: "Asterius" }
    { group:287, id:11, text: "Nia" }
    { group:287, id:12, text: "Phaestos" }
    { group:287, id:13, text: "Dedalus" }
    { group:287, id:14, text: "Icarus" }
    { group:287, id:15, text: "Britomantis" }
    { group:288, id:0, text: "Tushratta" }
    { group:288, id:1, text: "Artatama" }
    { group:288, id:2, text: "Tarmitessup" }
    { group:288, id:3, text: "Saushtatar" }
    { group:288, id:4, text: "Sulpae" }
    { group:288, id:5, text: "Zabazuna" }
    { group:288, id:6, text: "Zuja" }
    { group:288, id:7, text: "Pasatatar" }
    { group:288, id:8, text: "Kirta" }
    { group:288, id:9, text: "Idrimi" }
    { group:288, id:10, text: "Niqmepa" }
    { group:288, id:11, text: "Samas" }
    { group:288, id:12, text: "Kipteshub" }
    { group:288, id:13, text: "Ilimilimma" }
    { group:288, id:14, text: "Sataura" }
    { group:288, id:15, text: "Huradi" }
    { group:289, id:0, text: "Destructor" }
    { group:289, id:1, text: "Rompedor" }
    { group:289, id:2, text: "Demoledor" }
    { group:289, id:3, text: "Destrozador" }
    { group:289, id:4, text: "Aniquilador" }
    { group:289, id:5, text: "Acuchillador" }
    { group:289, id:6, text: "Mutilador" }
    { group:289, id:7, text: "Desafiante" }
    { group:289, id:8, text: "Vengador" }
    { group:289, id:9, text: "Ruina" }
    { group:289, id:10, text: "Tenaza" }
    { group:289, id:11, text: "Garra" }
    { group:289, id:12, text: "Caballo de batalla" }
    { group:289, id:13, text: "Dañino" }
    { group:289, id:14, text: "Desguazador" }
    { group:289, id:15, text: "Saqueador" }
    { group:290, id:0, text: "Putasokinhet" }
    { group:290, id:1, text: "Xander" }
    { group:290, id:2, text: "Ironrod" }
    { group:290, id:3, text: "Hat Tubig" }
    { group:290, id:4, text: "Roedor imprudente" }
    { group:290, id:5, text: "Antiguo" }
    { group:290, id:6, text: "Bedu" }
    { group:290, id:7, text: "Intruso" }
    { group:290, id:8, text: "Nómada" }
    { group:290, id:9, text: "Vagabundo" }
    { group:290, id:10, text: "Hombre de arena" }
    { group:290, id:11, text: "Conan" }
    { group:290, id:12, text: "Shababa" }
    { group:290, id:13, text: "Rababa" }
    { group:290, id:14, text: "Fuqara" }
    { group:290, id:15, text: "Petra" }
    { group:291, id:0, text: "Mausoleo" }
    { group:291, id:1, text: "Fase 1" }
    { group:291, id:2, text: "Los cimientos se han colocado" }
    { group:291, id:3, text: "y los trabajadores están despejando el lugar" }
    { group:291, id:4, text: "Fase 2" }
    { group:291, id:5, text: "Los canteros están construyendo la parte inferior" }
    { group:291, id:6, text: "del mausoleo" }
    { group:291, id:7, text: "Fase 3" }
    { group:291, id:8, text: "Los canteros están construyendo la parte superior" }
    { group:291, id:9, text: "del mausoleo" }
    { group:291, id:10, text: "Un único cantero está esperando la piedra" }
    { group:291, id:11, text: "canteros están esperando la piedra" }
    { group:291, id:12, text: "El mausoleo está" }
    { group:291, id:13, text: "porcentaje completado" }
    { group:291, id:14, text: "bloques de piedra necesarios para" }
    { group:291, id:15, text: "terminar la construcción del mausoleo" }
    { group:292, id:0, text: "Crear familia" }
    { group:292, id:1, text: "Borrar familia" }
    { group:292, id:2, text: "Continuar" }
    { group:292, id:3, text: "Registro de familias" }
    { group:292, id:4, text: "Volver al menú principal" }
    { group:293, id:0, text: "Reanudar la historia de la familia" }
    { group:293, id:1, text: "Seleccionar una misión" }
    { group:293, id:2, text: "Cargar partida guardada" }
    { group:293, id:3, text: "Misiones a medida" }
    { group:293, id:4, text: "Volver al registro de familias" }
    { group:293, id:5, text: "Familia de [player_name]" }
    { group:293, id:6, text: "Investigar la historia" }
    { group:293, id:7, text: "Comenzar la historia de la familia" }
    { group:294, id:0, text: "Periodo predinástico" }
    { group:294, id:1, text: "Durante el periodo predinástico, los clanes que finalmente gobernaron Egipto dieron sus primeros pasos hacia la civilización." }
    { group:294, id:2, text: "Tu familia comienza en el periodo predinástico guiando a una pequeña banda de nómadas a lo largo del descubrimiento de la civilización. Tu liderazgo ayuda a poner a Egipto en el camino a la grandeza, aún muy lejana." }
    { group:294, id:3, text: "El periódico predinástico es el comienzo de la historia egipcia y de la de tu familia." }
    { group:294, id:4, text: "Periodo arcaico" }
    { group:294, id:5, text: "Poco a poco, los pueblos que se establecieron durante el periodo predinástico se fusionaron en un imperio, con una magnífica capital y sus primeras tumbas monumentales." }
    { group:294, id:6, text: "Durante el periodo arcaico, las aldeas que aparecieron en el predinástico se unirán gradualmente para formar el gran imperio de Egipto. La joven civilización funda una capital, asegura sus fronteras, domina las aguas y construye sus primeros monumentos funerarios." }
    { group:294, id:7, text: "¡Debes vivir la historia familiar en orden! No puedes pasar al periodo arcaico antes de aprender las destrezas descubiertas en el predinástico." }
    { group:294, id:8, text: "Imperio antiguo" }
    { group:294, id:9, text: "Egipto entra en una época dorada de riqueza, poder y gloria, y construye asombrosos monumentos por todo el mundo. Tras alcanzar estas alturas de vértigo, Egipto entró en la guerra." }
    { group:294, id:10, text: "Egipto alcanza un poder, una riqueza y una gloria sin parangón en el imperio antiguo. Pero mientras los monumentos más increíbles se extienden por el valle del Nilo, los videntes hacen perturbadoras predicciones sobre el destino de las dos tierras." }
    { group:294, id:11, text: "No puedes saltarte periodos mientras forjas la historia de tu familia. Antes de entrar en el imperio antiguo debes completar el periodo arcaico." }
    { group:294, id:12, text: "Imperio medio" }
    { group:294, id:13, text: "Desde su dolorosa concepción, el imperio medio ha resultado ser una época propicia para mejorar la posición de tu familia en el mundo. Cuando restablezcas y fomentes la época dorada de Egipto, podrás ir a \"Seleccionar una misión\" para volver a jugar el periodo entero o alguna de sus misiones." }
    { group:294, id:14, text: "El imperio medio, nacido en conflicto, resulta ser una época de grandes oportunidades para tu familia. Bajo tu liderazgo, Egipto recupera su anterior esplendor... y lo supera." }
    { group:294, id:15, text: "La historia de la familia debe avanzar en orden. El imperio medio no puede comenzar antes de que termine el imperio antiguo." }
    { group:294, id:16, text: "Imperio nuevo" }
    { group:294, id:17, text: "Un nuevo y feroz enemigo, con una ingeniosa e imparable nueva arma, ha acabado con el imperio medio. Partiendo de esta destrucción, Egipto ha vuelto a renacer." }
    { group:294, id:18, text: "Unos desconocidos nuevos enemigos con un  arma terrible han terminado con el imperio medio y preparan el camino para seguir con el magnífico imperio nuevo." }
    { group:294, id:19, text: "¡No puedes abandonar el curso de la historia de tu familia! Tu familia no puede acceder al Imperio nuevo hasta completar los periodos anteriores." }
    { group:294, id:20, text: "Valle de los Reyes" }
    { group:294, id:21, text: "La creación de una nueva necrópolis en el Valle de los Reyes dio lugar a una nueva forma de preparar a los faraones para sus viajes a la otra vida." }
    { group:294, id:22, text: "Aunque son grandiosas, las pirámides de tus antepasados se han erosionado con el paso de los siglos, las tumbas del interior han sido profanadas y los tesoros ocultos robados por ladrones (¡sin duda serán castigados por los dioses durante toda la eternidad!). Renunciarás a las pirámides y comenzarás una nueva necrópolis en un uadi de difícil acceso junto a Tebas. Excavarás las tumbas en los precipicios para crear el Valle de los Reyes, a salvo de ladrones. ¿Estará a salvo?" }
    { group:294, id:23, text: "En la historia de tu familia todo tiene su momento. No puedes construir las magníficas tumbas del Valle de los Reyes hasta que hayas completado los esplendores del Imperio nuevo." }
    { group:294, id:24, text: "Ramsés II" }
    { group:294, id:25, text: "Ramsés II ha logrado la mayor victoria de Egipto y celebra su grandeza con magníficos monumentos." }
    { group:294, id:26, text: "Ramsés II es el tercero en la línea dinástica que comenzó con su abuelo, Ramsés I, un visir sin sangre real que reclamó el trono cuando Horemheb murió sin descendencia. Tendrás que lograr triunfos militares y construir grandes monumentos para convencer a tus súbditos de tu condición de deidad, desesperar a tus enemigos y dar a conocer el nombre de Ramsés el Grande y la gloria de Egipto a las generaciones venideras." }
    { group:294, id:27, text: "La historia de la familia debe completarse en orden. No puedes gobernar como Ramsés II hasta construir las gloriosas tumbas del Valle de los Reyes." }
    { group:294, id:28, text: "Antiguos conquistadores" }
    { group:294, id:29, text: "Han llegado poderosos guerreros de lejanas tierras para intentar dominar las riquezas de Egipto. Tras rechazar estos ataques y dar la bienvenida al glorioso Alejandro, puedes ir a \"Seleccionar una misión\" para volver a jugar toda la campaña o cualquiera de sus misiones." }
    { group:294, id:30, text: "Egipto tiene muchos vecinos envidiosos que vigilan nuestro rico imperio de la misma forma que una manada de hienas mira la presa de un león. ¿Puedes crear y comandar el ejército y la flota necesarios para acabar con estas graves amenazas, así como defender el delta del Nilo de las sucesivas invasiones de los Pueblos del mar, los asirios y los persas? ¡Egipto necesita tu protección!" }
    { group:294, id:31, text: "Han llegado poderosos guerreros de lejanas tierras para intentar dominar las riquezas de Egipto. Tras rechazar estos ataques y dar la bienvenida al glorioso Alejandro, puedes ir a \"Seleccionar una misión\" para volver a jugar toda la campaña o cualquiera de sus misiones." }
    { group:294, id:32, text: "La capital de Cleopatra" }
    { group:294, id:33, text: "Los Ptolomeos de Grecia devuelven la gloria a la tierra de los faraones y rechazan la amenaza de Roma." }
    { group:294, id:34, text: "El propio Alejandro el Magno ha buscado la ubicación de Alejandría, la ciudad portuaria del Mediterráneo que debes construir. En los 300 años de reinado de los Ptolomeos, que finalizan con Cleopatra VII, Alejandría se convertirá en la mayor ciudad del mundo, superando a Roma en población y riqueza. El mausoleo de Alejandro, la Gran Biblioteca, el faro de Pharos y el Caesareum son los proyectos de tu ciudad. Pero, ¿y las poderosas legiones de Roma? ¿Se utilizarán a favor o en contra del Egipto de Cleopatra?" }
    { group:294, id:35, text: "La historia de tu familia no puede añadir la vida de Cleopatra a sus anales hasta que hayas derrotado a los Antiguos conquistadores." }
    { group:294, id:36, text: "Comenzar" }
    { group:294, id:37, text: "Jugar" }
    { group:294, id:38, text: "Misiones individuales" }
    { group:294, id:39, text: "Campañas" }
    { group:294, id:40, text: "Tan sólo puedes volver a jugar las misiones después de haberlas terminado con éxito." }
    { group:294, id:41, text: "Faraón" }
    { group:294, id:42, text: "La Reina del Nilo - Cleopatra" }
    { group:295, id:0, text: "Ese festival ha alegrado a todo el mundo. La ciudad debería celebrar otro pronto." }
    { group:295, id:1, text: "Han pasado unos cuantos meses desde el último festival. Es un buen momento para celebrar otro." }
    { group:295, id:2, text: "No ha habido festivales durante bastante tiempo y la gente se empieza a quejar." }
    { group:295, id:3, text: "Ha pasado más de un año desde el último festival. La gente está aburrida y trabaja demasiado." }
    { group:295, id:4, text: "El último festival fue hace casi dos años. La gente necesita un descanso urgente." }
    { group:295, id:5, text: "Han pasado más de dos años sin festivales. La gente empieza a perder la esperanza." }
    { group:295, id:6, text: "La gente añora los buenos días pasados, cuando los festivales aliviaban la monotonía." }
    { group:295, id:7, text: "Ha sido un festival maravilloso. Preparar una fiesta como ésa lleva mucho tiempo." }
    { group:295, id:8, text: "Preparar un festival requiere mucho tiempo y esfuerzo, así que convendría que fueras organizándolo." }
    { group:295, id:9, text: "El último festival se celebró hace mucho tiempo; ya es hora de que organices otro." }
    { group:295, id:10, text: "El festival normal está casi preparado. Toda la gente habla sobre el día de fiesta del próximo mes." }
    { group:295, id:11, text: "Se está preparando el festival normal. Sólo faltan dos meses para que todos tengan un día de fiesta." }
    { group:295, id:12, text: "Los preparativos del festival normal, que se celebrará en tres meses, comenzarán el próximo mes." }
    { group:295, id:13, text: "Los organizadores están concretando los planes para el festival que se celebrará en cuatro meses." }
    { group:295, id:14, text: "El festival tendrá lugar en cinco meses. Los organizadores están repasando las sugerencias." }
    { group:295, id:15, text: "Los organizadores confían en estar preparados para celebrar el festival normal en seis meses." }
    { group:295, id:16, text: "Los rápidos organizadores han prometido que el festival normal se celebrará dentro de siete meses." }
    { group:295, id:17, text: "El festival normal no tendrá lugar antes de ocho meses. La planificación apenas ha comenzado." }
    { group:295, id:18, text: "Los organizadores están tan ocupados que el festival normal no se celebrará antes de nueve meses." }
    { group:295, id:19, text: "¿Ya quieres otro? En diez meses los organizadores no podrán celebrar otro festival normal." }
    { group:295, id:20, text: "El lujoso festival está casi listo. La gente está entusiasmada por la celebración del próximo mes." }
    { group:295, id:21, text: "Se está preparando el lujoso festival y tan sólo tenemos dos meses para prepararnos." }
    { group:295, id:22, text: "El lujoso festival se está preparando. Dentro de tres meses disfrutaremos de una celebración memorable." }
    { group:295, id:23, text: "Los organizadores han progresado mucho y es probable que el lujoso festival sea en cuatro meses." }
    { group:295, id:24, text: "Los artistas están puliendo sus actuaciones para el lujoso festival que se celebrará en cinco meses." }
    { group:295, id:25, text: "Los organizadores confirman que el lujoso festival tendrá lugar en seis meses, como se prometió." }
    { group:295, id:26, text: "Los organizadores estudian las sugerencias para el lujoso festival que se celebrará en diez meses." }
    { group:295, id:27, text: "Los artistas están ideando nuevos números para el lujoso festival que se celebrará en ocho meses." }
    { group:295, id:28, text: "Con tanto por planear, el lujoso festival tardará nueve meses en celebrarse." }
    { group:295, id:29, text: "Como nadie tiene tiempo para dedicarse al lujoso festival, este tendrá lugar dentro de diez meses." }
    { group:295, id:30, text: "Los organizadores están tan ocupados que han programado el nuevo festival para dentro de once meses." }
    { group:295, id:31, text: "El gran festival se acerca. En un mes, habrá cerveza fresca para todo el mundo." }
    { group:295, id:32, text: "La preparación del gran festival está prevista dentro de dos meses. La expectación es insoportable." }
    { group:295, id:33, text: "El gran festival se está preparando. La gente tan sólo tiene tres meses para hacer planes." }
    { group:295, id:34, text: "Se prepara el gran festival. Nadie puede esperar los cuatro meses que necesitan los organizadores." }
    { group:295, id:35, text: "Los organizadores pueden comenzar los preparativos el próximo mes y celebrar el festival en cinco." }
    { group:295, id:36, text: "Los malabaristas nos darán varias sorpresas en el gran festival, dentro de seis meses." }
    { group:295, id:37, text: "Todos los músicos están componiendo canciones para el gran festival, dentro de sólo siete meses." }
    { group:295, id:38, text: "Se puede ver a las bailarinas ensayar provocativos movimientos para el gran festival, en ocho meses." }
    { group:295, id:39, text: "Los organizadores tienen ideas y energía suficientes para celebrar un gran festival en nueve meses." }
    { group:295, id:40, text: "Los organizadores del festival trabajan horas extras para preparar el gran festival en diez meses." }
    { group:295, id:41, text: "Los organizadores confían en que pueden celebrar un gran festival en once meses." }
    { group:295, id:42, text: "Los organizadores tienen tanto trabajo que el gran festival que deseas se celebrará dentro de un año." }
    { group:296, id:0, text: "Casas eternas de Egipto" }
    { group:296, id:1, text: "Misión" }
    { group:296, id:2, text: "Mejor familia" }
    { group:296, id:3, text: "Dificultad" }
    { group:296, id:4, text: "Puntuación" }
    { group:296, id:5, text: "Casa de" }
    { group:296, id:6, text: "No hay mejores puntuaciones." }
    { group:297, id:0, text: "Los primeros antepasados registrados de tu familia destacaron y aprendieron las nociones del liderazgo." }
    { group:297, id:1, text: "Tras establecer a tu familia en Tinis, tus antepasados ayudaron a la confederación tinita a unificar el Alto y el Bajo Egipto." }
    { group:297, id:2, text: "Las leyendas de la familia dicen que tu clan descubrió importantes tecnologías y aprendió a usar la riada." }
    { group:297, id:3, text: "Tu familia entró en la historia oficial de Egipto cuando Narmer nombró a uno de tus antepasados arquitecto real." }
    { group:297, id:4, text: "Tu familia desempeñó un papel importante en la fundación de la primera capital y la construcción de la primera mastaba." }
    { group:297, id:5, text: "La leyenda dice que tu familia abrió las primeras minas de cobre en Timna, que fueron la clave del éxito del faraón para contener a los beduinos." }
    { group:297, id:6, text: "Por primera vez, uno de tus antepasados prefirió el agua a la tierra y aprendido las habilidades marítimas, incluida la guerra." }
    { group:297, id:7, text: "Por primera vez, uno de tus antepasados prefirió el agua a la tierra y aprendió las habilidades marítimas en tiempos de paz." }
    { group:297, id:8, text: "Tus antepasados establecieron un importante puesto militar lejos de la civilización, abriendo rutas comerciales con África que aún existen." }
    { group:297, id:9, text: "Para alegría del faraón Nebka, tu familia aprovechó la riqueza mineral de la primera catarata, sin la que no se podrían haber hecho muchas tumbas y muchos nobles no habrían accedido al Campo de cañas." }
    { group:297, id:10, text: "Tus antepasados lograron realizar satisfactoriamente la visión del visir Imhotep y construyeron la primera pirámide de piedra para alojar a la momia de Zóser." }
    { group:297, id:11, text: "Tu heroico antepasado arrancó valiosas piedras preciosas y cobre de la hostil tierra de Sinaí, que hizo lo imposible para frustrar el esfuerzo." }
    { group:297, id:12, text: "La mejora de la fortuna de tu clan está representada por la tumba familiar de Meidum, que aún sigue en pie como testimonio de la importancia de tu familia para Egipto." }
    { group:297, id:13, text: "La fortaleza construida en Buhen y el modo tajante con el que tus parientes derrotaron al enemigo allí, llevó el poder de Egipto hasta la segunda catarata, en las tierras reclamadas por la hostil Nubia." }
    { group:297, id:14, text: "Mientras otros trataban de extender las fronteras del imperio, tus ancestros construían la tumba más magnífica jamás vista, la pirámide romboidal de Snofru." }
    { group:297, id:15, text: "Mientras Snofru tuvo un heredero a quién los videntes reales calificaron de tirano, tus antepasados terminaron la primera pirámide verdadera del mundo para alojar los restos del faraón." }
    { group:297, id:16, text: "A pesar de la tiranía de Kéops, tu antepasado le sirvió lealmente como su gobernador real y defendió las fronteras egipcias de los invasores cusitas." }
    { group:297, id:17, text: "Protegido del ataque cusita, tu antepasado abrió unas productivas canteras en Tura para satisfacer la inexplicable demanda de Kéops de cantidades de caliza aparentemente ilimitadas." }
    { group:297, id:18, text: "Tu antepasado ascendió a nomarca de Kéops y Kefrén, y con una fuerza de voluntad que rivaliza con la del propio faraón, erigió la eterna gran pirámide y su esfinge guardiana." }
    { group:297, id:19, text: "El faraón declaró a Ra dios supremo y encargó a tu antepasado que extendiera el culto del Sol hasta los páramos hostiles del desierto occidental, en el último rincón del imperio." }
    { group:297, id:20, text: "El faraón Userkaf declaró a Ra dios supremo y ordenó a tu antepasado que construyera el mayor templo del Sol del fértil delta, una región carente de piedra de construcción." }
    { group:297, id:21, text: "Mientras los ejércitos enemigos acudían como los escarabajos a la carroña, tu familia ascendió a la cancillería y evitó que los enemigos del imperio rompieran sus contactos con otros lugares." }
    { group:297, id:22, text: "Mientras los ejércitos enemigos acudían como los escarabajos a la carroña, tu familia ascendió a la cancillería y demostró que podía seguir gobernando aunque todo lo demás se derrumbara." }
    { group:297, id:23, text: "Tus antepasados fueron leales a la legítima familia, los Iniotef, y restablecieron la gloria de Tinis, a pesar de los esfuerzos concertados de los ejércitos rebeldes de frustrar este logro." }
    { group:297, id:24, text: "Dos facciones luchaban por el corazón de Egipto, en el momento que su estómago estaba vacío. Tu antepasado salvó a muchos del hambre, mientras que daba su crucial apoyo a la legítima dinastía." }
    { group:297, id:25, text: "Mentuhotep ha concedido a tu familia la categoría de visir y depende en gran medida de su apoyo para acabar con los esfuerzos de algunos rebeldes y posibles usurpadores para evitar la unificación." }
    { group:297, id:26, text: "Mentuhotep ha concedido a tu familia la categoría de visir y su esfuerzo de unificación se ha beneficiado mucho de la gloria que se refleja en la majestuosa ciudad que has construido a partir de la nada." }
    { group:297, id:27, text: "Al fin, un miembro de tu familia ha cumplido el destino y se ha convertido en faraón. Tu clan se ha convertido en una dinastía real. Construye una nueva capital y acalla la oposición con comprensión y buenos trabajos." }
    { group:297, id:28, text: "Tu divino antepasado conquistó a nuestros antiguos enemigos en el norte de Nubia, inculcó a los cusitas respeto hacia tu dinastía y estableció un importante puerto en el Mar Rojo." }
    { group:297, id:29, text: "El puerto del Mar Rojo de tu divino antepasado trajo riquezas y lujos desconocidos a tu gente, y la tumba de tu familia resistirá el paso del tiempo." }
    { group:297, id:30, text: "Tu ilustre antepasado, que descansa hoy día en un fabuloso mausoleo, aplastó la flota de guerra nubia y conquistó una de sus mejores ciudades." }
    { group:297, id:31, text: "La ciudad de Bubastis sigue siendo la joya de la corona de los dos reinos. Tu antecesor construyó una ciudad que todo Egipto mira con orgullo." }
    { group:297, id:32, text: "Convertir los temidos carros hicsos en un arma egipcia y usarlos contra los enemigos de nuestro asediado imperio fue un gran logro que la historia nunca olvidará." }
    { group:297, id:33, text: "Tu familia ha sido bendecida durante mucho tiempo con la sabiduría. La estrategia de tu antepasado de inspirar en los más grandes generales egipcios esfuerzos sobrehumanos obtuvo una espléndida recompensa." }
    { group:297, id:34, text: "Fundaste un nuevo imperio, aseguraste los bosques de Biblos para siempre y enseñaste a los feroces hititas y a los misteriosos Pueblos del mar a respetar las fronteras egipcias." }
    { group:297, id:35, text: "Creaste una inimaginable riqueza para tu imperio, mientras defendías las ciudades egipcias contra viejos y nuevos enemigos." }
    { group:297, id:36, text: "Tu reinado fue el mayor jamás conocido por Egipto. Nuestras fronteras abarcaban el mundo conocido y nuestra gente disfrutó de lujos jamás imaginados." }
    { group:297, id:37, text: "Tras derrotar a todos los enemigo y conseguir una prosperidad incalculable para el imperio, construiste una pirámide superior incluso a la del legendario Kéops." }
    { group:297, id:38, text: "Con la fundación de Deir el-Medina, los faraones pueden descansar eternamente sin miedo a ser perturbados por los temidos saqueadores." }
    { group:297, id:39, text: "Se terminó la tumba de Tutankamón, con un escaso margen de tiempo, y se abasteció con lujosas provisiones funerarias." }
    { group:297, id:40, text: "La tumba funeraria de Seti I es maravillosa, e incluso más notoria debido a las oleadas de saqueadores que tuvieron que reprimirse para construirla. Es una pena que los ojos del mundo no puedan contemplar su eterna belleza." }
    { group:297, id:41, text: "El puerto de Sumur bulle con el comercio y trabaja para satisfacer la necesidad que tiene nuestra patria de madera y otras mercancías." }
    { group:297, id:42, text: "Egipto logró su mayor victoria en la batalla de Qades y reafirmó su dominio sobre la tierra de Amurra. La amenaza hitita fue aplastada de una vez por todas." }
    { group:297, id:43, text: "Los colosos de Abu Simbel mostrarán para siempre el poder y la gloria de Egipto." }
    { group:297, id:44, text: "Los restos mortales de Ramsés II descansan en su lujosa tumba. En su vida eterna, sin duda continuará ayudando a guiar la mano de Egipto." }
    { group:297, id:45, text: "Los peligrosos bandidos del mar que intentaron inútilmente establecerse en las tierras de Egipto, fueron rechazados. Las fronteras de Egipto volvieron a estar seguras." }
    { group:297, id:46, text: "El puesto fortificado del interior de Egipto resistió uno tras otro los ataques asirios, garantizando que el malvado enemigo no penetrara más allá de las Dos tierras." }
    { group:297, id:47, text: "El pueblo de Achoris relatará durante mucho tiempo la destrucción de la flota persa y la aniquilación de su infantería. Se asestó un gran golpe a los sueños de conquista de los persas." }
    { group:297, id:48, text: "En apenas una docena de años, Alejandría surgió de la tierra y convirtió en una próspera ciudad lo que años antes sólo era un pobre pueblo de pescadores." }
    { group:297, id:49, text: "Alejandría fue adornada con la Gran Biblioteca y el faro de Pharos, y su importancia en el mundo aumentó." }
    { group:297, id:50, text: "Las legiones de Mithradates acabaron con el hermano rebelde de Cleopatra, Ptolomeo XIII, en una gran batalla en el lago Mariut." }
    { group:297, id:51, text: "El glorioso desarrollo de Alejandría continuó cuando el Caesareum y otro templo mortuorio se añadieron a la lista de lugares magníficos." }
    { group:297, id:52, text: "La flota de Egipto y las fuerzas de Antonio aplastaron a Octavio, y Egipto y Roma se unieron como iguales para gobernar el mundo conocido." }
    { group:298, id:0, text: "Puntuación de cultura" }
    { group:298, id:1, text: "Puntuación de prosperidad" }
    { group:298, id:2, text: "Puntuación de monumentos" }
    { group:298, id:3, text: "Puntuación de imperio" }
    { group:298, id:4, text: "Población final" }
    { group:298, id:5, text: "Fondos finales" }
    { group:298, id:6, text: "La misión se ha terminado en" }
    { group:298, id:7, text: "Nivel de dificultad:" }
    { group:298, id:8, text: "La puntuación final ha sido:" }
    { group:298, id:9, text: "años" }
    { group:299, id:0, text: "Resultado directo" }
    { group:299, id:1, text: "Accesorio" }
    { group:299, id:2, text: "A pesar de" }
    { group:299, id:3, text: "No hay motivo" }
    { group:299, id:4, text: "Continuo/Cíclico" }
    { group:299, id:5, text: "Especificar cuando sea necesario" }
    { group:299, id:6, text: "Automático" }
    { group:299, id:7, text: "Directo" }
    { group:299, id:8, text: "Por cierto" }
    { group:299, id:9, text: "Aunque" }
    { group:299, id:10, text: "Ninguna" }
    { group:299, id:11, text: "Ciclo" }
    { group:299, id:12, text: "Por si acaso" }
    { group:299, id:13, text: "Auto" }
    { group:300, id:0, text: "Shumash" }
    { group:300, id:1, text: "Shalmaneser" }
    { group:300, id:2, text: "Tikulti" }
    { group:300, id:3, text: "Esnacher" }
    { group:300, id:4, text: "Urtaku" }
    { group:300, id:5, text: "Nabopollassar" }
    { group:300, id:6, text: "Ashur" }
    { group:300, id:7, text: "Bel-ibni" }
    { group:300, id:8, text: "Sennacher" }
    { group:300, id:9, text: "Ashurnadin" }
    { group:300, id:10, text: "Alkhut" }
    { group:300, id:11, text: "Neskhut" }
    { group:300, id:12, text: "Tilkhut" }
    { group:300, id:13, text: "Belnikut" }
    { group:300, id:14, text: "Belnesir" }
    { group:300, id:15, text: "Shasazur" }
    { group:301, id:0, text: "Marco" }
    { group:301, id:1, text: "Arminio" }
    { group:301, id:2, text: "Luculo" }
    { group:301, id:3, text: "Craso" }
    { group:301, id:4, text: "Gregorio" }
    { group:301, id:5, text: "Lucio" }
    { group:301, id:6, text: "Gnaeo" }
    { group:301, id:7, text: "Antono" }
    { group:301, id:8, text: "Séptimo" }
    { group:301, id:9, text: "Beroso" }
    { group:301, id:10, text: "Cornelio" }
    { group:301, id:11, text: "Lico" }
    { group:301, id:12, text: "Alejo" }
    { group:301, id:13, text: "Lascivo" }
    { group:301, id:14, text: "Gayo" }
    { group:301, id:15, text: "Garrulo" }
    { group:302, id:0, text: "Salmani" }
    { group:302, id:1, text: "Mirjama" }
    { group:302, id:2, text: "Tesmet" }
    { group:302, id:3, text: "Al Busir" }
    { group:302, id:4, text: "Ishtar" }
    { group:302, id:5, text: "Ahkmed" }
    { group:302, id:6, text: "Al Khaban" }
    { group:302, id:7, text: "Al Mustaf" }
    { group:302, id:8, text: "Hassan" }
    { group:302, id:9, text: "Samtiyar" }
    { group:302, id:10, text: "Tekdinar" }
    { group:302, id:11, text: "Santimer" }
    { group:302, id:12, text: "Almut" }
    { group:302, id:13, text: "Yusif" }
    { group:302, id:14, text: "Tandinar" }
    { group:302, id:15, text: "Tesmar" }
    { group:303, id:0, text: "Orodes" }
    { group:303, id:1, text: "Pakores" }
    { group:303, id:2, text: "Shurtruk" }
    { group:303, id:3, text: "Arsames" }
    { group:303, id:4, text: "Bagoas" }
    { group:303, id:5, text: "Artabanus" }
    { group:303, id:6, text: "Ciajares" }
    { group:303, id:7, text: "Astiages" }
    { group:303, id:8, text: "Teispes" }
    { group:303, id:9, text: "Haxamanish" }
    { group:303, id:10, text: "Shulla" }
    { group:303, id:11, text: "Histaspes" }
    { group:303, id:12, text: "Bardiya" }
    { group:303, id:13, text: "Smerdis" }
    { group:303, id:14, text: "Artajerjes" }
    { group:303, id:15, text: "Nahunte" }
    { group:304, id:0, text: "Página siguiente" }
    { group:304, id:1, text: "Página anterior" }
    { group:305, id:0, text: "Tu familia nunca se ha enfrentado a este reto. Para ver los objetivos de la misión, pulsa el botón situado más abajo." }
    { group:306, id:0, text: "Granja de henna" }
    { group:306, id:1, text: "La mejor henna crece aquí y se envía al fabricante de pinturas, que crea las brillantes pinturas que decoran las tumbas." }
    { group:306, id:2, text: "La producción está al:" }
    { group:306, id:3, text: "." }
    { group:306, id:4, text: "Tu supervisor comercial ha decretado el cese de la producción de henna." }
    { group:306, id:5, text: "Sin trabajadores, esta granja no puede producir henna." }
    { group:306, id:6, text: "Esta granja tiene todos los trabajadores que necesita. Los campos están llenos de plantas de henna." }
    { group:306, id:7, text: "Con más trabajadores, esta granja podría recoger más henna." }
    { group:306, id:8, text: "Esta granja no tiene suficientes trabajadores para ocuparse de un campo de henna." }
    { group:306, id:9, text: "Aquí trabaja muy poca gente. La cosecha de henna ser verá afectada por esto." }
    { group:306, id:10, text: "La mayor parte de esta granja es tierra árida. Necesita más trabajadores para cultivar más henna." }
    { group:306, id:11, text: "Las langostas han devorado todo lo que crecía aquí y la tierra necesita tiempo para recuperarse." }
    { group:306, id:12, text: "La tierra es" }
    { group:306, id:13, text: "fértil" }
    { group:306, id:14, text: "La próxima cosecha de henna es en" }
    { group:307, id:0, text: "0,0,0,0  //misión 0" }
    { group:307, id:1, text: "0,0,0,0" }
    { group:307, id:2, text: "0,0,0,0" }
    { group:307, id:3, text: "0,0,0,0  //Nekhen: primera misión con un sueldo personal." }
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
    { group:307, id:37, text: "1,0,0,0  //Última misión del juego original" }
    { group:307, id:38, text: "0,0,0,1  //Tutmosis" }
    { group:307, id:39, text: "0,0,V,1  //Tutankamón" }
    { group:307, id:40, text: "0,0,V,1  //Seti" }
    { group:307, id:41, text: "0,0,0,0,  //Sumer" }
    { group:307, id:42, text: "1,1,0,0  //Qades" }
    { group:307, id:43, text: "1,1,0,0  //Abu Simbel" }
    { group:307, id:44, text: "1,1,V,0  //Ramsés en el Valle" }
    { group:307, id:45, text: "0,0,0,0  //Pi-Yer" }
    { group:307, id:46, text: "0,0,0,0  //Migdol" }
    { group:307, id:47, text: "0,0,0,0  //Tanis" }
    { group:307, id:48, text: "0,0,0,1  //Alejandría (de Alejandro)" }
    { group:307, id:49, text: "1,1,A,1  //Alejandría (de los Ptolomeos)" }
    { group:307, id:50, text: "0,0,0,0  //César y Cleopatra" }
    { group:307, id:51, text: "1,1,A,0  //El legado de Cleopatra" }
    { group:307, id:52, text: "1,1,0,0  //Accio" }
    { group:308, id:0, text: "Zoológico" }
    { group:308, id:1, text: "Animales exóticos de todas partes deleitan a los ciudadanos en el zoo." }
    { group:308, id:2, text: "Este zoo tiene guardas, pero necesita carne para que los animales puedan llamarlo hogar." }
    { group:308, id:3, text: "Este zoo tiene empleados, pero sin paja no puede alojar animales." }
    { group:308, id:4, text: "A la gente le asusta visitar el zoo sin guardas. Hasta que el zoo encuentre algunos empleados, no será beneficioso para el barrio." }
    { group:308, id:5, text: "Sin animales, este zoo no tiene nada más que jaulas vacías." }
    { group:308, id:6, text: "Carne:" }
    { group:308, id:7, text: "Paja:" }
    { group:309, id:0, text: "El peligro de enfermedad es tan grande que incluso las alegres hienas están tristes." }
    { group:309, id:1, text: "¿Cómo vamos a alimentar a los animales si apenas podemos alimentarnos a nosotros mismos?" }
    { group:309, id:2, text: "Nuestras defensas son muy débiles. ¿Quizás debamos entrenar al hipopótamo para la lucha?" }
    { group:309, id:3, text: "Ni siquiera un elefante puede recordar los tiempos en los que había una escasez tan grande de trabajadores." }
    { group:309, id:4, text: "¡Cuando un dios está enfadado, lo último que quieres es que tu cuello se alargue tanto como el de una jirafa!" }
    { group:309, id:5, text: "El faraón es tan desdichado... ¡Espero que los animales del zoológico no sean necesarios como regalos exóticos!" }
    { group:309, id:6, text: "Conseguir un trabajo en esta ciudad es más difícil que capturar un león salvaje." }
    { group:309, id:7, text: "Las opciones de entretenimiento en esta ciudad huelen peor que las jaulas de los monos." }
    { group:309, id:8, text: "Vivir aquí es mejor que dormir en la jaula de los leones." }
    { group:309, id:9, text: "Viviendo en esta ciudad soy más feliz que un hipopótamo cubierto de barro." }
    { group:310, id:0, text: "Mensajes emergentes" }
    { group:310, id:1, text: "Ver mensajes en la parte superior de la pantalla" }
    { group:310, id:2, text: "Mensajes de la riada" }
    { group:310, id:3, text: "Mensajes de población" }
    { group:310, id:4, text: "Ahora es posible cumplir" }
    { group:310, id:5, text: "Mayor reputación del imperio" }
    { group:310, id:6, text: "Festivales" }
    { group:310, id:7, text: "Bendiciones menores" }
    { group:310, id:8, text: "El precio cambia" }
    { group:310, id:9, text: "El nivel comercial cambia" }
    { group:310, id:10, text: "El salario cambia" }
    { group:310, id:11, text: "La enfermedad ataca" }
    { group:310, id:12, text: "Malaria" }
    { group:310, id:13, text: "Se necesitan empleados" }
    { group:310, id:14, text: "OK" }
    { group:310, id:15, text: "Cancelar" }
    { group:311, id:0, text: "Seleccionar Era de monumentos" }
    { group:311, id:1, text: "Pirámides" }
    { group:311, id:2, text: "Valle de los Reyes" }
    { group:311, id:3, text: "Alejandría" }
    { group:311, id:4, text: "Abu Simbel" }
    { group:312, id:0, text: "Gremio de artesanos" }
    { group:312, id:1, text: "Los artesanos se reúnen aquí para fabricar yeso con arcilla y mezclar las pinturas antes de ir a decorar la tumba." }
    { group:312, id:2, text: "Este gremio no tiene empleados y no puede enviar artesanos." }
    { group:312, id:3, text: "Este gremio tiene muchos artesanos que decoran el interior de las tumbas sin perder un minuto." }
    { group:312, id:4, text: "A este gremio le falta un artesano o dos. La decoración de la tumba va algo más lenta." }
    { group:312, id:5, text: "Este gremio hace lo que puede para enviar artesanos a la tumba y proporciona menos de los que podría." }
    { group:312, id:6, text: "Este gremio necesita más trabajadores. Los pocos artesanos que trabajan aquí hacen lo que pueden para decorar la tumba, pero necesitan ayuda." }
    { group:312, id:7, text: "La pintura de las tumbas tiene mucho tiempo para secarse. A menos que el gremio encuentre más trabajadores, decorar la tumba puede llevar una eternidad." }
    { group:312, id:8, text: "Los artesanos se ven en apuros para decorar la tumba sin la pintura de un fabricante de pinturas o un almacén." }
    { group:312, id:9, text: "El gremio no enviará artesanos a la tumba hasta que reciba arcilla." }
    { group:312, id:10, text: "Pintura:" }
    { group:312, id:11, text: "Arcilla:" }
    { group:313, id:0, text: "Fabricante de pinturas" }
    { group:313, id:1, text: "Aquí se aplasta la henna y se convierte en pintura, que los artesanos utilizan para decorar los muros de las tumbas funerarias reales." }
    { group:313, id:2, text: "La producción está al:" }
    { group:313, id:3, text: "." }
    { group:313, id:4, text: "Tu supervisor comercial ha parado la producción de pintura." }
    { group:313, id:5, text: "Este fabricante de pinturas no tiene empleados. Sin trabajadores, no se puede fabricar pintura." }
    { group:313, id:6, text: "Con la plantilla al completo, este fabricante de pinturas produce pintura tan rápida y eficazmente como puede." }
    { group:313, id:7, text: "Este fabricante de pinturas tiene pocos empleados, así que la producción está en peligro." }
    { group:313, id:8, text: "Este fabricante de pinturas no dispone de suficientes empleados y produce pintura más lento de lo debido." }
    { group:313, id:9, text: "Este fabricante de pinturas necesita más trabajadores. La producción de pintura es muy lenta." }
    { group:313, id:10, text: "Este fabricante de pinturas tiene pocos empleados. Una plantilla tan pequeña apenas puede fabricar pintura." }
    { group:313, id:11, text: "Este taller necesita henna de una granja o un almacén para poder fabricar pintura." }
    { group:313, id:12, text: "Henna:" }
    { group:314, id:0, text: "Fabricante de lámparas" }
    { group:314, id:1, text: "Aquí, los trabajadores llenan la cerámica con aceite para hacer lámparas duraderas." }
    { group:314, id:2, text: "La producción está al:" }
    { group:314, id:3, text: "." }
    { group:314, id:4, text: "Tu supervisor comercial dio por terminada la producción de lámparas." }
    { group:314, id:5, text: "Este fabricante de lámparas no hace lámparas. No tiene empleados." }
    { group:314, id:6, text: "Con la plantilla completa, este fabricante de lámparas no tiene problemas para producir lámparas de forma oportuna." }
    { group:314, id:7, text: "Este fabricante de lámparas tiene algunas vacantes y esto disminuye en parte la producción del lámparas." }
    { group:314, id:8, text: "A este taller le faltan empleados y la producción de lámparas es pequeña." }
    { group:314, id:9, text: "Este fabricante de lámparas necesita más empleados. La pequeña plantilla hace lo que puede, pero la producción ha descendido considerablemente." }
    { group:314, id:10, text: "Este fabricante de lámparas apenas produce lámparas. Necesita más trabajadores para aumentar la producción." }
    { group:314, id:11, text: "Este taller necesita que le lleven aceite de un almacén para producir lámparas." }
    { group:314, id:12, text: "Este taller necesita que le lleven cerámica, de un almacén o una alfarería, para producir lámparas." }
    { group:314, id:13, text: "Aceite:" }
    { group:314, id:14, text: "Cerámica:" }
    { group:314, id:16, text: "***END----------------------------------------------------------------------" }
]
