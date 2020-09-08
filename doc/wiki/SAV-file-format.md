Savegame/map data file format for Pharaoh.

### File format offsets and description
Offsets are relative to the beginning of each group to accomodate for variable size chunks of compressed (zip) data

| Group | Offset | Length | Buf. size | Description |
| ----: | :----: | :----  | :-------- | :---------- |
| #1    | 0      | 1      | -         | Primary mission index. Used for briefing messages and map name
|       | 1      | 2      | -         | ???
|       | 3      | 1      | -         | Secondary mission index. Used for goal messages in briefing and at the top of the screen
|       | 4      | 4      | -         | File version?
|       | 8      | 4      | -         | ???
|       | 12     | 6000   | -         | ??????????????????????????????
|       | 6012   | -      | 207936    | Image grid
|       | -      | -      | 51984     | Edge grid
|       | -      | -      | 103968    | Building grid
|       | -      | -      | 207936    | Terrain grid
|       | -      | -      | 51984     | Aqueduct grid
|       | -      | -      | 103968    | Figure grid
|       | -      | -      | 51984     | Bitfields grid
|       | -      | -      | 51984     | Sprite grid
| #2    | 0      | 51984  | -         | Random grid
|       | 51984  | -      | 51984     | Desiderability grid
|       | -      | -      | 51984     | Elevation grid
|       | -      | -      | 103968    | Building damage grid
|       | -      | -      | 51984     | Aqueduct backup grid
|       | -      | -      | 51984     | Sprite backup grid
|       | -      | -      | 776000    | Figures
|       | -      | -      | 2000      | Figure routes
|       | -      | -      | 500000    | Route paths
|       | -      | -      | 7200      | Formations
| #3    | 0      | 12     | -         | Total formations
|       | 12     | -      | 37808     | City data
| #4    | 0      | 4      | -         | City faction unkown
|       | 4      | 64     | -         | Player name
|       | 68     | 4      | -         | City faction
|       | 72     | -      | 1056000   | Buildings
| #5    | 0      | 4      | -         | Camera orientation
|       | 4      | 20     | -         | Game time
|       | 24     | 8      | -         | Highest building ID (ever)
|       | 32     | 8      | -         | Random IV
|       | 40     | 8      | -         | Camera position
|       | 48     | 8      | -         | Graphs order
|       | 56     | 12     | -         | Empire   
|       | 68     | -      | 6466      | Empire cities
| #6    | 0      | 288    | -         | ??? (industry)
|       | 288    | 288    | -         | Trade prices
|       | 576    | 84     | -         | Figure names
|       | 660    | 2      | -         | Starting year
|       | 662    | 2      | -         | ???
|       | 664    | 2      | -         | Empire ID
|       | 666    | 26     | -         | ???
|       | 622    | 4      | -         | Initial funds (not adjusted by difficulty)
|       | 696    | 2      | -         | Enemy ID
|       | 698    | 6      | -         | ???
|       | 704    | 4      | -         | Map width
|       | 708    | 4      | -         | Map height
|       | 712    | 4      | -         | Map border start
|       | 716    | 4      | -         | Map border start
|       | 720    | 64     | -         | Scenario subtitle
|       | 784    | 522    | -         | Brief description of scenario (unused?)
|       | 1306   | 2      | -         | ??? (image id)
|       | 1308   | 2      | -         | ??? (open play)
|       | 1310   | 2      | -         | Player rank
|       | 1312   | 48     | -         | ??? (default FFFF (-1) 2-byte fields, non cyclic)
|       | 1360   | 44     | -         | ???
|       | 1404   | 64     | -         | ??? (default FFFF (-1) 2-byte fields, cyclic - invasion points?)
|       | 1468   | 36     | -         | ??? (18 two-byte flag fields)
|       | 1504   | 4      | -         | Prosperity rating goal
|       | 1508   | 4      | -         | Culture rating goal
|       | 1512   | 4      | -         | Monument rating goal
|       | 1516   | 4      | -         | Kingdom rating goal
|       | 1520   | 4      | -         | Extra scenario goal 1
|       | 1524   | 4      | -         | Extra scenario goal 2
|       | 1528   | 1      | -         | Prosp. goal enabled flag
|       | 1529   | 1      | -         | Cult. goal enabled flag
|       | 1530   | 1      | -         | Monum. goal enabled flag
|       | 1531   | 1      | -         | Kingd. goal enabled flag
|       | 1532   | 1      | -         | Extra goal 1 enabled flag
|       | 1533   | 1      | -         | Extra goal 2 enabled flag
|       | 1534   | 22     | -         | ??? (unused additional win condition spaces?)
|       | 1556   | 4      | -         | Population goal enabled flag
|       | 1560   | 4      | -         | Population goal
|       | 1564   | 52     | -         | ??? (default FFFF (-1) 2-byte fields, non cyclic)
|       | 1616   | 4      | -         | ???
|       | 1620   | 12     | -         | ??? (3 integers?)
|       | 1632   | 12     | -         | ??? (3 integers? usually go n, n+2, n+1497)
|       | 1644   | 14     | -         | ???
|       | 1658   | 34     | -         | ??? (default FFFF (-1) 2-byte fields, non cyclic)
|       | 1692   | 228    | -         | Allowed buildings 2-byte flags (see offsets in table below)
|       | 1920   | 24     | -         | ??? (default FFFF (-1) 2-byte fields, cyclic?)
|       | 1944   | 4      | -         | ???
|       | 1948   | 2      | -         | First monument field
|       | 1950   | 2      | -         | Second monument field
|       | 1952   | 2      | -         | Third monument field
|       | 1954   | 290    | -         | ???
|       | 2244   | 4      | -         | ???
|       | 2248   | 4      | -         | ???
|       | 2252   | 4      | -         | ???
|       | 2256   | -      | 48000     | Messages
| #7    | 0      | 12     | -         | Messages extra data
|       | 12     | 10     | -         | Population messages
|       | 22     | 80     | -         | Message counts
|       | 102    | 80     | -         | Message delays
|       | 182    | 8      | -         | Total burning buildings
|       | 190    | 4      | -         | Figures sequence phase
|       | 194    | 12     | -         | Scenario settings
|       | 206    | -      | 3232      | Invasion warnings
| #8    | 0      | 4      | -         | Custom scenario flag
|       | 4      | 8960   | -         | City sounds
|       | 8964   | 4      | -         | Highest building ID in map
|       | 8968   | 8804   | -         | Trader figures
|       | 17772  | -      | 1000      | Burning buildings list
|       | -      | -      | 1000      | Building list (small)
|       | -      | -      | 8000      | Building list (large)
| #9    | 0      | 32     | -         | ??? (Tutorial part 1?)
|       | 32     | 24     | -         | ???
|       | 56     | 39200  | -         | ??? (200 196-byte fields)
|       | 39256  | -      | 2880      | Trade route - limits
|       | -      | -      | 2880      | Trade route - traded so far
| #10   | 0      | 12     | -         | ???
|       | 12     | 16     | -         | City entry points coords
|       | 28     | 22     | -         | ???
|       | 50     | 65     | -         | Scenario name
|       | 115    | 32     | -         | Bookmarks  (default FFFF (-1) 2-byte fields)
|       | 147    | 4      | -         | ??? (Tutorial part 3?)
|       | 151    | 8      | -         | City entry points offsets?
|       | 159    | 52370  | -         | ??? (empty 0000 chunks)
|       | 52529  | 18600  | -         | ??? (150 124-byte data chunks)
|       | 71129  | 38     | -         | ???
|       | 71167  | 13416  | -         | ??? (00 chunk)
|       | 84583  | 8200   | -         | ??? (10 820-byte data chunks)
|       | 92783  | -      | 1280      | ??????????????????????????????
|       | -      | -      | 19600     | ??????????????????????????????
|       | -      | -      | 16200     | ??????????????????????????????
| #11   | 0      | 51984  | -         | ??? (FF chunk)
|       | 51984  | 20     | -         | ???
|       | 52004  | 528    | -         | ??? (22 24-byte data chunks)
|       | 52532  | -      | 36        | ??????????????????????????????
|       | -      | -      | 207936    | ??????????????????????????????
| #12   | 0      | 312    | -         | ??? (13 24-byte data chunks)
|       | 312    | 64     | -         | ???
|       | 376    | 41     | -         | ??? (41 1-byte flag fields)
|       | 417    | -      | 51984     | ??????????????????????????????
| #13   | 0      | 1      | -         | ??? (lone byte field?)
|       | 1      | -      | 51984     | ??????????????????????????????
| #14   | 0      | 672    | -         | ??? (28 24-byte data chunks)
|       | 672    | 20     | -         | ???
|       | 692    | 4800   | -         | ??????????????????????????????


### Allowed building offsets
| Field # | Building |
| :-----: | :------: |
0|???
1|???
2|Gold Mine
3|Water Lift
4|Irrigation Ditch
5|Shipwright
6|Work Camp
7|Granary
8|Bazaar
9|Storage Yard
10|Dock
11|Booth & Juggler School
12|Bandstand & Conservatory
13|Pavillion & Dance School
14|Senet House
15|Festival Square
16|Scribal School
17|Library
18|Water Supply
19|Dentist
20|Apothecary
21|Physician
22|Mortuary
23|Tax Collector
24|Courthouse
25|Village Palace
26|Personal Mansion
27|Roadblock
28|Bridge
29|Ferry Landing
30|Beautification (gardens)
31|Beautification (plaza)
32|Beautification (statues)
33|Wall
34|Tower
35|Gatehouse
36|Recruiter
37|Infantry Fort
38|Archers Fort
39|Charioteers Fort
40|Academy
41|Weaponsmith
42|Chariot Maker
43|Warship Wharf
44|Transport Wharf
45|Zoo
46-103|???
104|Temple Complex to Osiris
105|Temple Complex to Ra
106|Temple Complex to Ptah
107|Temple Complex to Seth
108|Temple Complex to Bast
109|???
110|???
111|???
112|???
113|???
114|???

### Monument field values
| Value | Hex   | Monument |
| :---: | :---: | :------: |
0|00|N/A
1|01|Small Bent Pyramid
2|02|Medium Bent Pyramid
3|03|Small Mudbrick Pyramid
4|04|Medium Mudbrick Pyramid
5|05|Large Mudbrick Pyramid
6|06|Mudbrick Pyramid Complex
7|07|Grand Mudbrick Pyramid Complex
8|08|Small Stepped Pyramid
9|09|Medium Stepped Pyramid
10|0A|Large Stepped Pyramid
11|0B|Stepped Pyramid Complex
12|0C|Grand Stepped Pyramid Complex
13|0D|Small Pyramid
14|0E|Medium Pyramid
15|0F|Large Pyramid
16|10|Pyramid Complex
17|11|Grand Pyramid Complex
18|12|Small Mastaba
19|13|Medium Mastaba
20|14|Large Mastaba
21|15|Sphinx
22|16|Small Obelisk
23|17|Large Obelisk
24|18|Sun Temple
25|19|Mausoleum
26|1A|Mausoleum
27|1B|Mausoleum
28|1C|Pharos Lighthouse
29|1D|Alexandria's Library
30|1E|Caesareum
31|1F|Colossi
32|20|Temple of Luxor
33|21|Small Royal Burial Tomb
34|22|Medium Royal Burial Tomb
35|23|Large Royal Burial Tomb
36|24|Grand Royal Burial Tomb
37|25|Abu Simbel