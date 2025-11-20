// This file is part of CaesarIA.
#include "zipreader.hpp"

#include <zlib.h>
#include "lzma/LzmaDec.h"
#include "bzip/bzlib.h"
#include "core/log.h"

namespace vfs {

    ZipArchive::ZipArchive(const vfs::path &file) : _filepath(file) {
        vfs::path ospath = vfs::content_file(file);
        _data = vfs::file_open(ospath, "rb");

        SZIPFileHeader header;

        _data->r(&header.Sig, 4);

        const bool zip = (header.Sig == 0x04034b50);
        _isGZip = ((header.Sig & 0xffff) == 0x8b1f); // gzip

        _data->seek(0);
        if (_data && (zip || _isGZip)) {
            if (_isGZip) {
                while (scanGZipHeader()) {
                    ; //
                }
            } else {
                while (scanZipHeader()) {
                    ; //
                }
            }
        }
    }

    ZipArchive::~ZipArchive() {
    }

    bool ZipArchive::isGzip() const {
        return _isGZip;
    }

    const std::vector<xstring> &ZipArchive::entries() const {
        return _entries;
    }

    //! scans for a local header, returns false if there is no more local file header.
    //! The gzip file format seems to think that there can be multiple files in a gzip file
    //! but none
    bool ZipArchive::scanGZipHeader() {
        SZipFileEntry entry;
        entry.Offset = 0;
        memset(&entry.header, 0, sizeof(SZIPFileHeader));

        if (_data->eof()) {
            return false;
        }

        // read header
        SGZIPMemberHeader header;
        _data->r(&header, sizeof(SGZIPMemberHeader));

        // check header value
        if (header.sig != 0x8b1f) {
            return false;
        }

        // now get the file info
        if (header.flags & EGZF_EXTRA_FIELDS) {
            // read lenth of extra data
            unsigned short dataLen;

            _data->r(&dataLen, 2);

            // skip it
            _data->advance(dataLen);
        }

        bstring512 ZipFileName;

        if (header.flags & EGZF_FILE_NAME) {
            char c;
            _data->r(&c, 1);
            while (c) {
                ZipFileName.append(c);
                _data->r(&c, 1);
            }
        } else {
            ZipFileName = _filepath.c_str();

            // rename tgz to tar or remove gz extension
            int length = ZipFileName.len();
            if (file_has_extension(ZipFileName, "tgz")) {
                ZipFileName[length - 2] = 'a';
                ZipFileName[length - 1] = 'r';
            } else if (file_has_extension(ZipFileName, "gz")) {
                ZipFileName[length - 3] = 0;
            }
        }

        if (header.flags & EGZF_COMMENT) {
            char c = 'a';
            while (c) {
                _data->r(&c, 1);
            }
        }

        if (header.flags & EGZF_CRC16) {
            _data->advance(2);
        }

        // we are now at the start of the data blocks
        entry.Offset = _data->tell();

        entry.header.FilenameLength = ZipFileName.len();

        entry.header.CompressionMethod = header.compressionMethod;
        entry.header.DataDescriptor.CompressedSize = (_data->size() - 8) - _data->tell();

        // seek to file end
        _data->advance(entry.header.DataDescriptor.CompressedSize);

        // read CRC
        _data->r(&entry.header.DataDescriptor.CRC32, 4);
        // read uncompressed size
        _data->r(&entry.header.DataDescriptor.UncompressedSize, 4);

        // now we've filled all the fields, this is just a standard deflate block
        _entries.push_back(ZipFileName.c_str());
        _files.push_back(entry);
        return true;
    }

    //! scans for a local header, returns false if there is no more local file header.
    bool ZipArchive::scanZipHeader(bool ignoreGPBits) {
        xstring entry_name;
        SZipFileEntry entry;
        entry.Offset = 0;
        memset(&entry.header, 0, sizeof(SZIPFileHeader));

        _data->r(&entry.header, sizeof(SZIPFileHeader));

        if (entry.header.Sig != 0x04034b50) {
            return false; // local file headers end here.
        }

        // read filename
        {
            char tmp[512] = { 0 };
            assert(entry.header.FilenameLength + 2 < sizeof(tmp));
            _data->r(tmp, entry.header.FilenameLength);
            tmp[entry.header.FilenameLength] = 0;
            entry_name = tmp;
        }

        // Skip extra field (AES encryption not supported)
        if (entry.header.ExtraFieldLength) {
            _data->advance(entry.header.ExtraFieldLength);
        }

        // if bit 3 was set, use CentralDirectory for setup
        if (!ignoreGPBits && entry.header.GeneralBitFlag & ZIP_INFO_IN_DATA_DESCRIPTOR) {
            SZIPFileCentralDirEnd dirEnd;
            // First place where the end record could be stored
            _data->seek(_data->size() - 22);
            const char endID[] = { 0x50, 0x4b, 0x05, 0x06, 0x0 };
            char tmp[5] = { '\0' };
            bool found = false;
            // search for the end record ID
            while (!found && _data->tell() > 0) {
                int seek = 8;
                _data->r(tmp, 4);
                switch (tmp[0]) {
                case 0x50:
                    if (!strcmp(endID, tmp)) {
                        seek = 4;
                        found = true;
                    }
                    break;
                case 0x4b:
                    seek = 5;
                    break;
                case 0x05:
                    seek = 6;
                    break;
                case 0x06:
                    seek = 7;
                    break;
                }
                _data->advance(-seek);
            }
            _data->r(&dirEnd, sizeof(dirEnd));

            //_files.resize(dirEnd.TotalEntries);
            //_entries.resize(dirEnd.TotalEntries);
            _data->seek(dirEnd.Offset);
            while (scanCentralDirectoryHeader()) {
                ; //
            }
            return false;
        }

        // store position in file
        entry.Offset = _data->tell();
        // move forward length of data
        _data->advance(entry.header.DataDescriptor.CompressedSize);

        _entries.push_back(entry_name);
        _files.push_back(entry);

        return true;
    }

    //! scans for a local header, returns false if there is no more local file header.
    bool ZipArchive::scanCentralDirectoryHeader() {
        SZIPFileCentralDirFileHeader entry;

        constexpr size_t header_size = sizeof(SZIPFileCentralDirFileHeader);
        const long hpos = _data->tell();
        if (hpos + header_size > _data->size()) {
            return false;
        }

        _data->r(&entry, header_size);

        if (entry.Sig != 0x02014b50) {
            return false; // central dir headers end here.
        }

        const long pos = _data->tell();
        _data->seek(entry.RelativeOffsetOfLocalHeader);
        scanZipHeader(true);
        _data->seek(pos + entry.FilenameLength + entry.ExtraFieldLength + entry.FileCommentLength);
        _files.push_back({});
        _files.back().header.DataDescriptor.CompressedSize = entry.CompressedSize;
        _files.back().header.DataDescriptor.UncompressedSize = entry.UncompressedSize;
        _files.back().header.DataDescriptor.CRC32 = entry.CRC32;
        _entries.push_back({});
        return true;
    }

    //! opens a file by file name
    reader ZipArchive::createAndOpenFile(const vfs::path &filename, pcstr mode) {
        const auto it = std::find_if(_entries.begin(), _entries.end(), [&filename] (const xstring &entry) {
            return !entry.empty() && entry == filename;
        });

        if (it == _entries.end()) {
            logs::warn("File %s not found in archive %s", filename.c_str(), _filepath.c_str());
            return {};
        }

        const int index = std::distance(_entries.begin(), it);
        if (index != -1) {
            return createAndOpenFile(index, mode);
        }

        return {};
    }

    //! Used for LZMA decompression. The lib has no default memory management
    namespace {
        void *SzAlloc(void *p, size_t size) { p; return malloc(size); }
        void SzFree(void *p, void *address) { p; free(address); }
        ISzAlloc lzmaAlloc = { SzAlloc, SzFree };
    }

    //! opens a file by index
    reader ZipArchive::createAndOpenFile(unsigned int index, pcstr mode) {
        //Supports 0, 8, 12, 14, 99
        //0 - The file is stored (no compression)
        //1 - The file is Shrunk
        //2 - The file is Reduced with compression factor 1
        //3 - The file is Reduced with compression factor 2
        //4 - The file is Reduced with compression factor 3
        //5 - The file is Reduced with compression factor 4
        //6 - The file is Imploded
        //7 - Reserved for Tokenizing compression algorithm
        //8 - The file is Deflated
        //9 - Reserved for enhanced Deflating
        //10 - PKWARE Date Compression Library Imploding
        //12 - bzip2 - Compression Method from libbz2, WinZip 10
        //14 - LZMA - Compression Method, WinZip 12
        //96 - Jpeg compression - Compression Method, WinZip 12
        //97 - WavPack - Compression Method, WinZip 11
        //98 - PPMd - Compression Method, WinZip 10
        //99 - AES encryption, WinZip 9

        const bool is_text_file = !!strstr(mode, "t");
        const int txr_limiter = is_text_file ? 1 : 0;
        const SZipFileEntry &e = _files[index];

        short actualCompressionMethod = e.header.CompressionMethod;

        // AES encryption not supported
        if ((e.header.GeneralBitFlag & ZIP_FILE_ENCRYPTED) && (e.header.CompressionMethod == 99)) {
            return {};
        }

        switch (actualCompressionMethod) {
        case 0: // no compression
        {
            _data->seek(e.Offset);
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const size_t memsize = uncompressedSize + txr_limiter;
            char *mem = (char*)malloc(memsize);
            _data->r(mem, uncompressedSize);
            if (is_text_file) {
                mem[uncompressedSize] = 0; // null-terminate the string
            }
            return std::make_shared<data_reader>(_entries[index].c_str(), mem, (int)memsize);
        }
        break;

        case 8:
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);

            if (pBuf.empty() || pcData.empty()) {
                //Logger::warning( "Not enough memory for decompressing " + item( index ).fullpath.toString() );
                return {};
            }

            _data->seek(e.Offset);
            _data->r(pcData.data(), compressedSize);

            // Setup the inflate stream.
            z_stream stream;
            int err;

            stream.next_in = (Bytef *)pcData.data();
            stream.avail_in = (uInt)compressedSize;
            stream.next_out = (Bytef *)pBuf.data();
            stream.avail_out = uncompressedSize;
            stream.zalloc = (alloc_func)0;
            stream.zfree = (free_func)0;

            // Perform inflation. wbits < 0 indicates no zlib header inside the data.
            err = inflateInit2(&stream, -MAX_WBITS);
            if (err == Z_OK) {
                err = inflate(&stream, Z_FINISH);
                inflateEnd(&stream);

                if (err == Z_STREAM_END)
                    err = Z_OK;
                err = Z_OK;
                inflateEnd(&stream);
            }

            if (err != Z_OK) {
                //Logger::warning( "Error decompressing " + item( index ).fullpath.toString() );
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, memsize);
                return r;
            }
        }
        break;

        case 12:
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);

            if (pBuf.empty() || pcData.empty()) {
                //Logger::error( "Not enough memory for decompressing " + item( index ).fullpath.toString() );
                return {};
            }

            _data->seek(e.Offset);
            _data->r(pcData.data(), compressedSize);

            bz_stream bz_ctx = { 0 };
            /* use BZIP2's default memory allocation
            bz_ctx->bzalloc = NULL;
            bz_ctx->bzfree  = NULL;
            bz_ctx->opaque  = NULL;
            */
            int err = BZ2_bzDecompressInit(&bz_ctx, 0, 0); /* decompression */
            if (err != BZ_OK) {
                //Logger::error( "bzip2 decompression failed. File cannot be read." );
                return {};
            }

            bz_ctx.next_in = (char *)pcData.data();
            bz_ctx.avail_in = compressedSize;
            /* pass all input to decompressor */
            bz_ctx.next_out = pBuf.data();
            bz_ctx.avail_out = uncompressedSize;
            err = BZ2_bzDecompress(&bz_ctx);
            //err;

            err = BZ2_bzDecompressEnd(&bz_ctx);

            if (err != BZ_OK) {
                //Logger::error( "Error decompressing +" + item( index ).fullpath.toString() );
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, memsize);
                return r;
            }
        }
        break;

        case 14:
        {
            unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);
            if (pBuf.empty() || pcData.empty()) {
                //Logger::error( "Not enough memory for decompressing " + item( index ).fullpath.toString() );
                return {};
            }

            _data->seek(e.Offset);
            _data->r(pcData.data(), compressedSize);

            ELzmaStatus status;
            SizeT tmpDstSize = uncompressedSize;
            SizeT tmpSrcSize = compressedSize;

            unsigned int propSize = (pcData[3] << 8) + pcData[2];
            int err = LzmaDecode((Byte *)pBuf.data(), &tmpDstSize,
                (Byte *)pcData.data() + 4 + propSize, &tmpSrcSize,
                (Byte *)pcData.data() + 4, propSize, e.header.GeneralBitFlag & 0x1 ? LZMA_FINISH_END : LZMA_FINISH_ANY, &status, &lzmaAlloc);
            uncompressedSize = tmpDstSize; // may be different to expected value

            if (err != SZ_OK) {
                //Logger::error( "Error decompressing " + item( index ).fullpath.toString() );
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, memsize);
                return r;
            }
        }
        break;

        case 99:
        {
            return {};
        }

        default:
        {
            //Logger::error( "file {} has unsupported compression method", item( index ).fullpath.toCString() );
            return {};
        }
        }

        //Logger::error( "Can't read file " + item( index ).fullpath.toString() );
        return {};
    }
} // vfs
