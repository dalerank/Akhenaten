#pragma once

#include "content/vfs.h"
#include "core/xstring.h"

namespace vfs {

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined (__BCPLUSPLUS__)
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	error compiler not supported
#endif

    // set if the file is encrypted
    const short ZIP_FILE_ENCRYPTED = 0x0001;
    // the fields crc-32, compressed size and uncompressed size are set to
    // zero in the local header
    const short ZIP_INFO_IN_DATA_DESCRIPTOR = 0x0008;

    struct SZIPFileDataDescriptor {
        unsigned int CRC32;
        unsigned int CompressedSize;
        unsigned int UncompressedSize;
    } PACK_STRUCT;

    struct SZIPFileHeader {
        unsigned int Sig;				// 'PK0304' little endian (0x04034b50)
        short VersionToExtract;
        short GeneralBitFlag;
        short CompressionMethod;
        short LastModFileTime;
        short LastModFileDate;
        SZIPFileDataDescriptor DataDescriptor;
        short FilenameLength;
        short ExtraFieldLength;
        // filename (variable size)
        // extra field (variable size )
    } PACK_STRUCT;

    struct SZIPFileCentralDirFileHeader {
        unsigned int Sig;	// 'PK0102' (0x02014b50)
        unsigned short VersionMadeBy;
        unsigned short VersionToExtract;
        unsigned short GeneralBitFlag;
        unsigned short CompressionMethod;
        unsigned short LastModFileTime;
        unsigned short LastModFileDate;
        unsigned int CRC32;
        unsigned int CompressedSize;
        unsigned int UncompressedSize;
        unsigned short FilenameLength;
        unsigned short ExtraFieldLength;
        unsigned short FileCommentLength;
        unsigned short DiskNumberStart;
        unsigned short InternalFileAttributes;
        unsigned int ExternalFileAttributes;
        unsigned int RelativeOffsetOfLocalHeader;

        // filename (variable size)
        // extra field (variable size)
        // file comment (variable size)

    } PACK_STRUCT;

    struct SZIPFileCentralDirEnd {
        unsigned int Sig;			// 'PK0506' end_of central dir signature			// (0x06054b50)
        unsigned short NumberDisk;		// number of this disk
        unsigned short NumberStart;	// number of the disk with the start of the central directory
        unsigned short TotalDisk;		// total number of entries in the central dir on this disk
        unsigned short TotalEntries;	// total number of entries in the central dir
        unsigned int Size;			// size of the central directory
        unsigned int Offset;			// offset of start of centraldirectory with respect to the starting disk number
        unsigned short CommentLength;	// zipfile comment length
        // zipfile comment (variable size)
    } PACK_STRUCT;


    enum E_GZIP_FLAGS {
        EGZF_TEXT_DAT = 1,
        EGZF_CRC16 = 2,
        EGZF_EXTRA_FIELDS = 4,
        EGZF_FILE_NAME = 8,
        EGZF_COMMENT = 16
    };

    struct SGZIPMemberHeader {
        unsigned short sig; // 0x8b1f
        unsigned char  compressionMethod; // 8 = deflate
        unsigned char  flags;
        unsigned int time;
        unsigned char  extraFlags; // slow compress = 2, fast compress = 4
        unsigned char  operatingSystem;
    } PACK_STRUCT;

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined (__BCPLUSPLUS__)
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

    //! Contains extended info about zip files in the archive
    struct SZipFileEntry {
        //! Position of data in the archive file
        int Offset;

        //! The header for this file containing compression info etc
        SZIPFileHeader header;
    };

    class ZipArchive {
    public:
        ZipArchive(const vfs::path &filename);

        //! destructor
        ~ZipArchive();

        //! opens a file by file name
        reader createAndOpenFile(const vfs::path &filename, pcstr mode);

        //! opens a file by index
        reader createAndOpenFile(unsigned int index, pcstr mode);

        //! returns the list of files
        const std::vector<xstring> &entries() const;
        const vfs::path &filepath() const { return _filepath; }

        bool isGzip() const;
        bool isValid() const { return !_files.empty(); }
    protected:

        //! reads the next file header from a ZIP file, returns false if there are no more headers.
        /* if ignoreGPBits is set, the item will be read despite missing
           file information. This is used when reading items from the central
           directory. */
        bool scanZipHeader(bool ignoreGPBits = false);

        //! the same but for gzip files
        bool scanGZipHeader();

        bool scanCentralDirectoryHeader();

        // holds extended info about files
        vfs::path _filepath;
        std::vector<SZipFileEntry> _files;
        std::vector<xstring> _entries;
        reader _data;

        bool _isGZip;
    };

} // vfs
