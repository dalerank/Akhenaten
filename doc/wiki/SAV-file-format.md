Savegame/map data file format for Pharaoh.

### File format offsets and description
Offsets are relative to the beginning of each group to accomodate for variable size chunks of compressed (zip) data

| Group | Offset | Length | Description |
| ----: | :----: | :----  | :---------- |
| #1  | 0 | 1 | Primary mission index. Used for briefing messages and map name |
|     | 1 | 2 | ??? |
|     | 3 | 1 | Secondary mission index. Used for goal messages in briefing and at the top of the screen |
|     | 4 | 4 | File version? |
|     | 8 | 4 | ??? |
|     | 12 | 6000 | ?????????????????????????????? |
|     | 6012 | - | Image grid |
|     | - | - | Edge grid |
|     | - | - | Building grid |
|     | - | - | Terrain grid |
|     | - | - | Aqueduct grid |
|     | - | - | Figure grid |
|     | - | - | Bitfields grid |
|     | - | - | Sprite grid |
| #2  | 0 | 51984 | Random grid |
|     | 51984 | - | Desiderability grid |
|     | - | - | Elevation grid |
|     | - | - | Building damage grid |
|     | - | - | Aqueduct backup grid |
|     | - | - | Sprite backup grid |
|     | - | - | Figures |
|     | - | - | Figure routes |
|     | - | - | Route paths |
|     | - | - | Formations |
| #3  | 0 | 12 | Total formations |
|     | 12 | - | City data |
| #4  | 0 | 4 | City faction unkown |
|     | 4 | 64 | Player name |
|     | 68 | 4 | City faction |
|     | 72 | - | Buildings |
| #5  | 0 | 4 | Camera orientation |
|     | 4 | 20 | Game time |
|     | 24 | 8 | Highest building ID (ever) |
|     | 32 | 8 | Random IV |
|     | 40 | 8 | Camera position |
|     | 48 | 8 | Graphs order |
|     | 56 | 12 | Empire  |
|     | 68 | - | Empire cities |
| #6  | 0 | 288 | ??? (industry) |
|     | 288 | 288 | Trade prices |
|     | 576 | 84 | Figure names |
|     | 660 | 2 | Starting year |
|     | 662 | 2 | ??? |
|     | 664 | 2 | Empire ID |
|     | 666 | 8 | ??? |
|     | 674 | 4 | Initial funds (not adjusted by difficulty) |
|     | 678 | 2 | Enemy ID |
|     | 680 | 6 | ??? |
|     | 686 | 4 | Map width |
|     | 690 | 4 | Map height |
|     | 694 | 4 | Map border start |
|     | 698 | 4 | Map border start |
|     | 702 | 64 | Scenario subtitle |
|     | 766 | 522 | Brief description of scenario (unused?) |
|     | 1288 | 2 | ??? (image id) |
|     | 1290 | 2 | ??? (open play) |
|     | 1292 | 2 | Player rank |
|     | 1294 | 48 | ??? (default FFFF (-1) 2-byte fields, non cyclic) |
|     | 1342 | 44 | ??? |
|     | 1386 | 64 | ??? (default FFFF (-1) 2-byte fields, cyclic - invasion points?) |
|     | 1450 | 36 | ??? (18 two-byte flag fields) |
|     | 1486 | 4 | Prosperity rating goal |
|     | 1490 | 4 | Culture rating goal |
|     | 1494 | 4 | Monument rating goal |
|     | 1498 | 4 | Kingdom rating goal |
|     | 1502 | 4 | Extra scenario goal 1 |
|     | 1506 | 4 | Extra scenario goal 2 |
|     | 1510 | 1 | Prosp. goal enabled flag |
|     | 1511 | 1 | Cult. goal enabled flag |
|     | 1512 | 1 | Monum. goal enabled flag |
|     | 1513 | 1 | Kingd. goal enabled flag |
|     | 1514 | 1 | Extra goal 1 enabled flag |
|     | 1515 | 1 | Extra goal 2 enabled flag |
|     | 1516 | 22 | ??? (unused additional win condition spaces?) |
|     | 1538 | 4 | Population goal enabled flag |
|     | 1542 | 4 | Population goal |
|     | 1546 | 52 | ??? (default FFFF (-1) 2-byte fields, non cyclic) |
|     | 1598 | 4 | ??? |
|     | 1602 | 12 | ??? (3 integers?) |
|     | 1614 | 12 | ??? (3 integers? usually go n, n+2, n+1497) |
|     | 1626 | 14 | ??? |
|     | 1640 | 34 | ??? (default FFFF (-1) 2-byte fields, non cyclic) |
|     | 1674 | 228 | Allowed buildings 2-byte flags (see offsets in table below) |
|     | 1902 | 24 | ??? (default FFFF (-1) 2-byte fields, cyclic?) |
|     | 1926 | 4 | ??? |
|     | 1930 | 2 | First monument field |
|     | 1932 | 2 | Second monument field |
|     | 1934 | 2 | Third monument field |
|     | 1936 | 290 | ??? |
|     | 2226 | 4 | ??? |
|     | 2230 | 4 | ??? |
|     | 2234 | 4 | ??? |
|     | 2238 | - | Messages |
| #7  | 0 | 12 | Messages extra data |
|     | 12 | 10 | Population messages |
|     | 22 | 80 | Message counts |
|     | 102 | 80 | Message delays |
|     | 182 | 8 | Total burning buildings |
|     | 190 | 4 | Figures sequence phase |
|     | 194 | 12 | Scenario settings |
|     | 206 | - | Invasion warnings |
| #8  | 0 | 4 | Custom scenario flag |
|     | 4 | 8960 | City sounds |
|     | 8964 | 4 | Highest building ID in map |
|     | 8968 | 8804 | Trader figures |
|     | 17772 | - | Burning buildings list |
|     | - | - | Building list (small) |
|     | - | - | Building list (large) |
| #9  | 0 | 32 | ??? (Tutorial part 1?) |
|     | 32 | 24 | ??? |
|     | 56 | 39200 | ??? (200 196-byte fields) |
|     | 39256 | - | Trade route - limits |
|     | - | - | Trade route - traded so far |
| #10 | 0 | 12 | ??? |
|     | 12 | 16 | City entry points coords |
|     | 28 | 22 | ??? |
|     | 50 | 65 | Scenario name |
|     | 115 | 32 | Bookmarks  (default FFFF (-1) 2-byte fields) |
|     | 147 | 4 | ??? (Tutorial part 3?) |
|     | 151 | 8 | City entry points offsets? |
|     | 159 | 52370 | ??? (empty 0000 chunks) |
|     | 52529 | 18600 | ??? (150 124-byte data chunks) |
|     | 71129 | 38 | ??? |
|     | 71167 | 13416 | ??? (00 chunk) |
|     | 84583 | 8200 | ??? (10 820-byte data chunks) |
|     | 92783 | - | ?????????????????????????????? |
|     | - | - | ?????????????????????????????? |
|     | - | - | ?????????????????????????????? |
| #11 | 0 | 51984 | ??? (FF chunk) |
|     | 51984 | 20 | ??? |
|     | 52004 | 528 | ??? (22 24-byte data chunks) |
|     | 52532 | - | ?????????????????????????????? |
|     |  | - | ?????????????????????????????? |
| #12 | 0 | 312 | ??? (13 24-byte data chunks) |
|     | 312 | 64 | ??? |
|     | 376 | 41 | ??? (41 1-byte flag fields) |
|     | 417 | - | ?????????????????????????????? |
| #13 | 0 | 1 | ??? (lone byte field?) |
|     | 1 | - | ?????????????????????????????? |
| #14 | 0 | 672 | ??? (28 24-byte data chunks) |
|     | 672 | 20 | ??? |
|     | 692 | 4800 | ?????????????????????????????? |


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