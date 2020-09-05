_Original article: [bvschaik/citybuilding-tools/wiki/ENG-file-format](https://github.com/bvschaik/citybuilding-tools/wiki/ENG-file-format)_

Translatable strings in the citybuilding games are stored in ENG files. There are two types of files:
- [Text files](#text-files) for simple text strings
- [Message files](#message-files) for complex messages with title, body text, and more properties, such as the help pages

## Text files
Strings in text files are grouped together into groups. A text is referenced by two numbers: its group number, and an index of the string within the group.

Text files consist of three parts:
- [Header](#text-file-header)
- [Index](#text-file-index)
- [Data](#text-file-data)

The games look up strings in the following way: first, the index entry for the group is consulted. This gives us the offset into the data part where the group's strings start. Then, the data part is consulted. If the third string is needed, the first two strings starting at the offset are skipped, and the third string encountered in the group is returned.

### Text file header
The 28-byte header consists of the following fields:

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 16 | String describing the file, example: "C3 textfile." |
| 16 | 4 | Total number of groups in use, defined by maximum used group ID, plus 1 |
| 20 | 4 | Total number of strings in the file |
| 24 | 4 | Total number of words in the file, may not be accurate |

### Text file index
The index consists of 1000 entries. Each entry is 8 bytes in total, but the exact meaning of the fields differs per game.

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 4 | Index into the data part of the file where this group starts |
| 4 | 4 | Earlier games: 0 = entry is unused, 1 = entry is used <br/>Later games: the number of strings in this group, implying 0 = unused |

### Text file data
The data is just a lot of strings one after the other, separated by one (or more) 0-byte per string. A string must contain at least one printable character (value >= 32) to count.

Encoding of the strings depends on the language and the game itself. For Caesar 3, the following encodings are used:

| Language | Encoding |
| -------- | -------- |
| Western European languages: English, French, German, Italian, Portuguese, Spanish, Swedish | Windows-1252 |
| Polish | Windows-1250 |
| Russian | Windows-1251 |
| Korean | Windows-950 |
| Traditional Chinese | Custom encoding |

## Message files
ENG files with a name ending in `_mm.eng` contain more complex messages. These files also consist of 3 parts:

- [Header](#message-file-header)
- [Index](#message-file-index)
- [Data](#message-file-data)

### Message file header
The 24-byte header consists of the following fields:

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 16 | String describing the file, example: "C3 MMfile" |
| 16 | 4 | Number of entries in the index, this is usually 1000 |
| 20 | 4 | Last entry in use, plus 1 |

### Message file index
The index consists of 80-byte entries. The total number of entries is defined in the header part.

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 2 | Type of entry, see [message types](#message-types) |
| 2 | 2 | Subtype of entry, see [message subtypes](#message-subtypes) |
| 4 | 2 | (unused) |
| 6 | 2 | Dialog X position |
| 8 | 2 | Dialog Y position |
| 10 | 2 | Dialog width, in blocks of 16 pixels; a width of 10 equals 160 pixels |
| 12 | 2 | Dialog height, in blocks of 16 pixels |
| 14 | 2 | Image ID |
| 16 | 2 | Image X position |
| 18 | 2 | Image Y position |
| 20 | 2 | Secondary image ID |
| 22 | 2 | Secondary image X position |
| 24 | 2 | Secondary image Y position |
| 26 | 2 | Title X position |
| 28 | 2 | Title Y position |
| 30 | 2 | Subtitle X position |
| 32 | 2 | Subtitle Y position |
| 34 | 2 | (unused X position) |
| 36 | 2 | (unused Y position) |
| 38 | 2 | Video X position |
| 40 | 2 | Video Y position |
| 42 | 14 | (unused) |
| 56 | 4 | Whether the message is urgent: 0 = not urgent, 1 = urgent |
| 60 | 4 | Video string offset |
| 64 | 4 | (unknown string offset) |
| 68 | 4 | Title string offset |
| 72 | 4 | Subtitle string offset |
| 76 | 4 | Content string offset, content string may contain [formatting](#message-content-formatting) |

### Message file data
Like the text file, the data part of the file are the strings, separated by 0-bytes. The first 16 bytes of the data part are always 0-bytes, to ensure that every string offset is greater than zero.

### Message types
`TODO`

### Message subtypes
`TODO`

### Message content formatting
`TODO`
