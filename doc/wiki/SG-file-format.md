_Original article: [bvschaik/citybuilding-tools/wiki/SG-file-format](https://github.com/bvschaik/citybuilding-tools/wiki/SG-file-format)_

Graphics in the citybuilding games are stored in SG files, either .sg2 (Caesar 3) or .sg3 (Pharaoh, Zeus, Emperor), and .555 files.

SG files are basically an index containing information about multiple images, such as width, height, and other properties, and an offset into a .555 file. The .555 file contains the actual pixel data for the images.

SG files consist of 4 parts:
- 80-byte header
- Index of 300 entries, allowing the game to quickly look up image IDs
- Bitmap entries
- Up to 10,000 image entries

## Header
The 80-byte header consists of the following fields:

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 4 | File size of this SG file |
| 4 | 4 | Version of the SG file format |
| 8 | 4 | Unknown |
| 12 | 4 | Total number of image records present in this file |
| 16 | 4 | Number of image records in use |
| 20 | 4 | Number of bitmap records in this file |
| 24 | 4 | Unknown but related to number of bitmap records |
| 28 | 4 | Total image data file size (both internal and external) |
| 32 | 4 | File size of the internal 555 file (the one with the same name as the SG file) |
| 36 | 4 | File size of image data in external 555 files (555 files with another name) |
| 40 | 40 | Unknown |

### Version

| Version | Description |
| :-----: | :---- |
| 211 | SG2 format |
| 213 | SG3 format |
| 214 | SG3 format with alpha mask |

## Index

The index is 600 bytes long, interpreted as 300 entries of 16-bit unsigned shorts. These shorts refer to an image id in the image entries. This index is used in the games as in the following example from Caesar 3:

The entry at position 22 contains 2872. Position 22 in the index means "market". If the game wants to draw a market, it will look at position 22 in the index and finds 2872. It will then retrieve the image in the images section at position 2872.
This way the artists could insert additional images in the image list, without the programmers having to update all IDs: all that had to be done is change the 2872 to another number.

## Bitmaps

The next section contains a number of "bitmaps". The total number of entries is in the header.

Bitmaps are used for grouping related images and for referring to external .555 files. This is done for the larger images that are not needed frequently, such as mission backgrounds in Caesar 3.

Bitmap entries are 200 bytes long and consist of the following fields:

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 65 | Bitmap filename |
| 65 | 51 | Optional description |
| 116 | 4 | Width of the image (if external bitmap) |
| 120 | 4 | Height of the image (if external bitmap) |
| 124 | 4 | Number of images in this bitmap |
| 128 | 4 | First image index |
| 132 | 4 | Last image index |
| 136 | 16 x 4 | 16 integers, unknown purpose |

## Images

The final section contains the image entries. The total number of entries is in the header.

The size of an image entry depends on the version of the SG file. Versions below 214 are 64 bytes, versions above 214 contain extra alpha fields and are 72 bytes.

| Offset | Length | Description |
| :----: | :----: | :---------- |
| 0 | 4 | Offset into .555 |
| 4 | 4 | Length of the image data |
| 8 | 4 | Length of the uncompressed part of the image |
| 12 | 4 | Zero bytes |
| 16 | 4 | SG3 only: offset into .555 of the mirrored image |
| 20 | 2 | Width of the image |
| 22 | 2 | Height of the image |
| 24 | 3x2 | 3 unknown shorts |
| 30 | 2 | Number of animation sprites |
| 32 | 2 | Unknown short |
| 34 | 2 | X offset of animation sprite |
| 36 | 2 | Y offset of animation sprite |
| 38 | 10 | Unknown bytes |
| 48 | 1 | Flag: animation is reversible |
| 49 | 1 | Unknown byte |
| 50 | 1 | Image type, see below |
| 51 | 1 | Flag: image data is fully compressed |
| 52 | 1 | Flag: image data is external |
| 53 | 1 | Flag: image is partly compressed |
| 54 | 2x1 | Unknown bytes |
| 56 | 1 | Bitmap ID (unsigned byte) |
| 57 | 1 | Unknown byte |
| 58 | 1 | Animation speed ID |
| 59 | 1 | Unknown byte |
| 60 | 4 | Zero bytes |
| 64 | 4 | (Alpha only) Offset of alpha mask image |
| 68 | 4 | (Alpha only) Length of alpha mask image |

### Bitmap types

| Type | Description |
| :--: | :---------- |
| 0 | Regular image, can contain transparent pixels |
| 1, 10, 12, 13, 20 | Regular image |
| 30 | Isometric image |
