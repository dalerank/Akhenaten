// This file is part of CaesarIA.
#include "core/vfs/zipreader.hpp"

#include <zlib.h>
#include "lzma/LzmaDec.h"
#include "bzip/bzlib.h"
#include "core/log.h"

namespace vfs {

    ZipArchive::ZipArchive(const vfs::path &file) : _filepath(file) {
        vfs::path ospath = vfs::path::resolve(file);
        _data = vfs::file_open(ospath, "rb");
        if (!_data) {
            return;
        }

        uint32_t sig = 0;
        _data->r(&sig, 4);

        const bool zip = (sig == 0x04034b50);
        _isGZip = ((sig & 0xffff) == 0x8b1f); // gzip

        _data->seek(0);
        if (zip || _isGZip) {
            if (_isGZip) {
                while (!_corrupt && scanGZipHeader()) {
                    ; //
                }
            } else {
                while (!_corrupt && scanZipHeader()) {
                    ; //
                }
            }
        }

        if (_data->failed() && !_corrupt) {
            markCorrupt("truncated");
        }

        if (_corrupt) {
            _files.clear();
            _entries.clear();
            _names.clear();
        }
    }

    void ZipArchive::markCorrupt(pcstr reason) {
        if (!_corrupt) {
            logs::warn("zip: %s is corrupt (%s), ignored", _filepath.c_str(), reason);
        }
        _corrupt = true;
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
        if (!_data->r(&header, sizeof(SGZIPMemberHeader))) {
            return false;
        }

        // check header value
        if (header.sig != 0x8b1f) {
            return false;
        }

        // now get the file info
        if (header.flags & EGZF_EXTRA_FIELDS) {
            // read lenth of extra data
            unsigned short dataLen = 0;

            _data->r(&dataLen, 2);

            // skip it
            _data->advance(dataLen);
        }

        bstring512 ZipFileName;

        if (header.flags & EGZF_FILE_NAME) {
            char c = 0;
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

        if (_data->failed() || _data->elapsed() < 8) {
            return false;
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
        _names.push_back(ZipFileName.c_str());
        _entries.push_back(ZipFileName.tolower().c_str());
        _files.push_back(entry);
        return true;
    }

    //! scans for a local header, returns false if there is no more local file header.
    bool ZipArchive::scanZipHeader(bool ignoreGPBits) {
        bstring256 entry_name;
        SZipFileEntry entry;
        entry.Offset = 0;
        memset(&entry.header, 0, sizeof(SZIPFileHeader));

        if (!_data->r(&entry.header, sizeof(SZIPFileHeader))) {
            return false;
        }

        if (entry.header.Sig != 0x04034b50) {
            return false; // local file headers end here.
        }

        // read filename
        {
            char tmp[512] = { 0 };
            if (entry.header.FilenameLength >= sizeof(tmp)) {
                markCorrupt("file name too long");
                return false;
            }
            if (!_data->r(tmp, entry.header.FilenameLength)) {
                return false;
            }
            tmp[entry.header.FilenameLength] = 0;
            entry_name = tmp;
        }

        // Skip extra field (AES encryption not supported)
        if (entry.header.ExtraFieldLength && !_data->advance(entry.header.ExtraFieldLength)) {
            return false;
        }

        // if bit 3 was set, use CentralDirectory for setup
        if (!ignoreGPBits && entry.header.GeneralBitFlag & ZIP_INFO_IN_DATA_DESCRIPTOR) {
            SZIPFileCentralDirEnd dirEnd;
            // First place where the end record could be stored
            if (!_data->seek(_data->size() - 22)) {
                return false;
            }
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
                if (!_data->advance(-seek)) {
                    break;
                }
            }
            if (!found) {
                markCorrupt("no central directory");
                return false;
            }
            if (!_data->r(&dirEnd, sizeof(dirEnd)) || !_data->seek(dirEnd.Offset)) {
                return false;
            }

            while (!_corrupt && scanCentralDirectoryHeader()) {
                ; //
            }
            return false;
        }

        // store position in file
        entry.Offset = _data->tell();
        // move forward length of data
        if (!_data->advance(entry.header.DataDescriptor.CompressedSize)) {
            return false;
        }

        _names.push_back(entry_name.c_str());
        _entries.push_back(entry_name.tolower().c_str());
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
        const size_t scanned = _files.size();
        if (!_data->seek(entry.RelativeOffsetOfLocalHeader)) {
            return false;
        }
        scanZipHeader(true);
        if (!_data->seek((int64_t)pos + entry.FilenameLength + entry.ExtraFieldLength + entry.FileCommentLength)) {
            return false;
        }
        // a streamed archive (bit 3) leaves the sizes of the local header at 0: the central directory has them
        if (_files.size() == scanned + 1) {
            _files.back().header.DataDescriptor.CompressedSize = entry.CompressedSize;
            _files.back().header.DataDescriptor.UncompressedSize = entry.UncompressedSize;
            _files.back().header.DataDescriptor.CRC32 = entry.CRC32;
        }
        return true;
    }

    //! opens a file by file name
    reader ZipArchive::createAndOpenFile(const vfs::path &filename, pcstr mode) {
        vfs::path wanted = filename;
        wanted.tolower();
        const auto it = std::find_if(_entries.begin(), _entries.end(),
          [&wanted](const xstring& entry) { return !entry.empty() && entry == wanted; });

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
        void *SzAlloc(void *p, size_t size) {
						(void)p;
						return malloc(size);
				}
				void SzFree(void *p, void *address) {
						(void)p;
						free(address);
				}
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
        if (index >= _files.size()) {
            return {};
        }
        const SZipFileEntry &e = _files[index];
        constexpr unsigned int max_entry_size = 256u << 20;
        if (e.header.DataDescriptor.UncompressedSize > max_entry_size
            || e.header.DataDescriptor.CompressedSize > (unsigned int)_data->size()) {
            logs::warn("zip: %s in %s is too large", _entries[index].c_str(), _filepath.c_str());
            return {};
        }

        short actualCompressionMethod = e.header.CompressionMethod;

        // AES encryption not supported
        if ((e.header.GeneralBitFlag & ZIP_FILE_ENCRYPTED) && (e.header.CompressionMethod == 99)) {
            return {};
        }

        switch (actualCompressionMethod) {
        case 0: // no compression
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const size_t memsize = uncompressedSize + txr_limiter;
            char *mem = (char*)malloc(memsize);
            if (!_data->seek(e.Offset) || !_data->r(mem, uncompressedSize)) {
                free(mem);
                return {};
            }
            if (is_text_file) {
                mem[uncompressedSize] = 0; // null-terminate the string
            }
            return std::make_shared<data_reader>(_entries[index].c_str(), mem, (int)memsize);
        } break;

        case 8:
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.reserve(uncompressedSize + 1);
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);

            if (!_data->seek(e.Offset) || !_data->r(pcData.data(), compressedSize)) {
                return {};
            }

            // Setup the inflate stream.
            z_stream stream = {};
            stream.next_in = (Bytef *)pcData.data();
            stream.avail_in = (uInt)compressedSize;
            stream.next_out = (Bytef *)pBuf.data();
            stream.avail_out = uncompressedSize;

            // Perform inflation. wbits < 0 indicates no zlib header inside the data.
            int err = inflateInit2(&stream, -MAX_WBITS);
            if (err == Z_OK) {
                err = inflate(&stream, Z_FINISH);
                const uLong total_out = stream.total_out;
                inflateEnd(&stream);
                if (err == Z_STREAM_END && total_out != uncompressedSize) {
                    err = Z_DATA_ERROR;
                }
            }

            if (err != Z_STREAM_END) {
                logs::warn("zip: %s in %s is corrupt (inflate %d), ignored", _entries[index].c_str(), _filepath.c_str(),
                  err);
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, static_cast<int>(memsize));
                return r;
            }
        }
        break;

        case 12:
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.reserve(uncompressedSize + 1);
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);

            if (!_data->seek(e.Offset) || !_data->r(pcData.data(), compressedSize)) {
                return {};
            }

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
            if (err == BZ_STREAM_END && bz_ctx.total_out_lo32 != uncompressedSize) {
                err = BZ_DATA_ERROR;
            }
            BZ2_bzDecompressEnd(&bz_ctx);

            if (err != BZ_STREAM_END) {
                logs::warn("zip: %s in %s is corrupt (bzip2 %d), ignored", _entries[index].c_str(), _filepath.c_str(),
                  err);
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, static_cast<int>(memsize));
                return r;
            }
        }
        break;

        case 14:
        {
            const unsigned int uncompressedSize = e.header.DataDescriptor.UncompressedSize;
            const unsigned int compressedSize = e.header.DataDescriptor.CompressedSize;
            std::vector<char> pBuf;
            pBuf.resize(uncompressedSize);

            std::vector<char> pcData;
            pcData.resize(compressedSize);

            if (!_data->seek(e.Offset) || !_data->r(pcData.data(), compressedSize)) {
                return {};
            }

            ELzmaStatus status;
            SizeT tmpDstSize = uncompressedSize;

            if (compressedSize < 4) {
                return {};
            }
            const unsigned int propSize = ((uint8_t)pcData[3] << 8) + (uint8_t)pcData[2];
            if (propSize + 4 > compressedSize) {
                return {};
            }
            SizeT tmpSrcSize = compressedSize - 4 - propSize;
            int err = LzmaDecode((Byte*)pBuf.data(), &tmpDstSize, (Byte*)pcData.data() + 4 + propSize, &tmpSrcSize,
              (Byte*)pcData.data() + 4, propSize, e.header.GeneralBitFlag & 0x1 ? LZMA_FINISH_END : LZMA_FINISH_ANY,
              &status, &lzmaAlloc);

            if (err != SZ_OK || tmpDstSize != uncompressedSize) {
                logs::warn("zip: %s in %s is corrupt (lzma %d), ignored", _entries[index].c_str(), _filepath.c_str(),
                  err);
                return {};
            } else {
                const size_t memsize = pBuf.size() + txr_limiter;
                char *mem = (char*)malloc(memsize);
                memcpy(mem, pBuf.data(), pBuf.size());
                if (is_text_file) {
                    mem[pBuf.size()] = 0; // null-terminate the string
                }

                auto r = std::make_shared<data_reader>(_entries[index].c_str(), mem, static_cast<int>(memsize));
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
