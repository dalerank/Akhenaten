/*
 ---------------------------------------------------------------------------
 Copyright (c) 2002, Dr Brian Gladman <                 >, Worcester, UK.
 All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software in both source and binary 
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright 
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      in the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products 
      built using this software without specific written permission. 

 ALTERNATIVELY, provided that this notice is retained in full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 in which case the provisions of the GPL apply INSTEAD OF those given above.
 
 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness 
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue Date: 26/08/2003

 This is a byte oriented version of SHA2 that operates on arrays of bytes
 stored in memory. This code implements sha256, sha384 and sha512 but the
 latter two functions rely on efficient 64-bit integer operations that 
 may not be very efficient on 32-bit machines

 The sha256 functions use a type 'sha256_ctx' to hold details of the 
 current hash state and uses the following three calls:

       void sha256_begin(sha256_ctx ctx[1])
       void sha256_hash(const unsigned char data[], 
                            unsigned long len, sha256_ctx ctx[1])
       void sha256_end(unsigned char hval[], sha256_ctx ctx[1])

 The first subroutine initialises a hash computation by setting up the 
 context in the sha256_ctx context. The second subroutine hashes 8-bit 
 bytes from array data[] into the hash state withinh sha256_ctx context, 
 the number of bytes to be hashed being given by the the unsigned long 
 integer len.  The third subroutine completes the hash calculation and 
 places the resulting digest value in the array of 8-bit bytes hval[].

 The sha384 and sha512 functions are similar and use the interfaces:

       void sha384_begin(sha384_ctx ctx[1]);
       void sha384_hash(const unsigned char data[], 
                            unsigned long len, sha384_ctx ctx[1]);
       void sha384_end(unsigned char hval[], sha384_ctx ctx[1]);

       void sha512_begin(sha512_ctx ctx[1]);
       void sha512_hash(const unsigned char data[], 
                            unsigned long len, sha512_ctx ctx[1]);
       void sha512_end(unsigned char hval[], sha512_ctx ctx[1]);

 In addition there is a function sha2 that can be used to call all these
 functions using a call with a hash length parameter as follows:

       int sha2_begin(unsigned long len, sha2_ctx ctx[1]);
       void sha2_hash(const unsigned char data[], 
                            unsigned long len, sha2_ctx ctx[1]);
       void sha2_end(unsigned char hval[], sha2_ctx ctx[1]);

 My thanks to Erik Andersen <andersen@codepoet.org> for testing this code 
 on big-endian systems and for his assistance with corrections
*/

/* define the hash functions that you need          */

#define SHA_2           /* for dynamic hash length  */
#define SHA_256
#define SHA_384
#define SHA_512

#include <string.h>     /* for memcpy() etc.        */
#include <stdlib.h>     /* for _lrotr with VC++     */

#include "sha2.h"

/*  BYTE ORDER IN 32-BIT WORDS

    To obtain the highest speed on processors with 32-bit words, this code
    needs to determine the byte order of the target machine. The following 
    block of code is an attempt to capture the most obvious ways in which 
    various environemnts define byte order. It may well fail, in which case 
    the definitions will need to be set by editing at the points marked 
    **** EDIT HERE IF NECESSARY **** below.  My thanks to Peter Gutmann for 
    some of these defines (from cryptlib).
*/

#define BRG_LITTLE_ENDIAN   1234 /* byte 0 is least significant (i386) */
#define BRG_BIG_ENDIAN      4321 /* byte 0 is most significant (mc68k) */

#ifdef __BIG_ENDIAN__
#define PLATFORM_BYTE_ORDER BRG_BIG_ENDIAN
#else
#define PLATFORM_BYTE_ORDER BRG_LITTLE_ENDIAN
#endif

#ifdef _MSC_VER
#pragma intrinsic(memcpy)
#endif

#define rotr32(x,n)   (((x) >> n) | ((x) << (32 - n)))

#if (PLATFORM_BYTE_ORDER == BRG_LITTLE_ENDIAN)
#define SWAP_BYTES
#else
#undef  SWAP_BYTES
#endif

#if defined(SHA_2) || defined(SHA_256)

#define SHA256_MASK (SHA256_BLOCK_SIZE - 1)

#if defined(SWAP_BYTES)
  #define bswap_32_TT(X) ( (((X)&0x000000FF)<<24) | (((X)&0xFF000000) >> 24) | (((X)&0x0000FF00) << 8) | (((X) &0x00FF0000) >> 8))
  #define bsw_32(p,n) { int _i = (n); while(_i--) p[_i] = bswap_32_TT(p[_i]); }
#else
  #define bsw_32(p,n)
#endif

/* SHA256 mixing function definitions   */

#if 0

#define ch(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define maj(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#else   /* Thanks to Rich Schroeppel and Colin Plumb for the following      */

#define ch(x,y,z)       ((z) ^ ((x) & ((y) ^ (z))))
#define maj(x,y,z)      (((x) & (y)) | ((z) & ((x) ^ (y))))

#endif

#define s256_0(x) (rotr32((x),  2) ^ rotr32((x), 13) ^ rotr32((x), 22)) 
#define s256_1(x) (rotr32((x),  6) ^ rotr32((x), 11) ^ rotr32((x), 25)) 
#define g256_0(x) (rotr32((x),  7) ^ rotr32((x), 18) ^ ((x) >>  3)) 
#define g256_1(x) (rotr32((x), 17) ^ rotr32((x), 19) ^ ((x) >> 10)) 

/* rotated SHA256 round definition. Rather than swapping variables as in    */
/* FIPS-180, different variables are 'rotated' on each round, returning     */
/* to their starting positions every eight rounds                           */

#define h2(i) p[i & 15] += \
    g256_1(p[(i + 14) & 15]) + p[(i + 9) & 15] + g256_0(p[(i + 1) & 15])

#define h2_cycle(i,j)  \
    v[(7 - i) & 7] += (j ? h2(i) : p[i & 15]) + k256[i + j] \
        + s256_1(v[(4 - i) & 7]) + ch(v[(4 - i) & 7], v[(5 - i) & 7], v[(6 - i) & 7]); \
    v[(3 - i) & 7] += v[(7 - i) & 7]; \
    v[(7 - i) & 7] += s256_0(v[(0 - i) & 7]) + maj(v[(0 - i) & 7], v[(1 - i) & 7], v[(2 - i) & 7])

/* SHA256 mixing data   */

const sha2_32t k256[64] =
{   n_u32(428a2f98), n_u32(71374491), n_u32(b5c0fbcf), n_u32(e9b5dba5), 
    n_u32(3956c25b), n_u32(59f111f1), n_u32(923f82a4), n_u32(ab1c5ed5), 
    n_u32(d807aa98), n_u32(12835b01), n_u32(243185be), n_u32(550c7dc3), 
    n_u32(72be5d74), n_u32(80deb1fe), n_u32(9bdc06a7), n_u32(c19bf174), 
    n_u32(e49b69c1), n_u32(efbe4786), n_u32(0fc19dc6), n_u32(240ca1cc), 
    n_u32(2de92c6f), n_u32(4a7484aa), n_u32(5cb0a9dc), n_u32(76f988da), 
    n_u32(983e5152), n_u32(a831c66d), n_u32(b00327c8), n_u32(bf597fc7), 
    n_u32(c6e00bf3), n_u32(d5a79147), n_u32(06ca6351), n_u32(14292967), 
    n_u32(27b70a85), n_u32(2e1b2138), n_u32(4d2c6dfc), n_u32(53380d13), 
    n_u32(650a7354), n_u32(766a0abb), n_u32(81c2c92e), n_u32(92722c85),
    n_u32(a2bfe8a1), n_u32(a81a664b), n_u32(c24b8b70), n_u32(c76c51a3), 
    n_u32(d192e819), n_u32(d6990624), n_u32(f40e3585), n_u32(106aa070), 
    n_u32(19a4c116), n_u32(1e376c08), n_u32(2748774c), n_u32(34b0bcb5), 
    n_u32(391c0cb3), n_u32(4ed8aa4a), n_u32(5b9cca4f), n_u32(682e6ff3), 
    n_u32(748f82ee), n_u32(78a5636f), n_u32(84c87814), n_u32(8cc70208), 
    n_u32(90befffa), n_u32(a4506ceb), n_u32(bef9a3f7), n_u32(c67178f2),
};

/* SHA256 initialisation data */

const sha2_32t i256[8] =
{
    n_u32(6a09e667), n_u32(bb67ae85), n_u32(3c6ef372), n_u32(a54ff53a),
    n_u32(510e527f), n_u32(9b05688c), n_u32(1f83d9ab), n_u32(5be0cd19)
};

sha2_void sha256_begin(sha256_ctx ctx[1])
{
    ctx->count[0] = ctx->count[1] = 0;
    memcpy(ctx->hash, i256, 8 * sizeof(sha2_32t));
}

/* Compile 64 bytes of hash data into SHA256 digest value   */
/* NOTE: this routine assumes that the byte order in the    */
/* ctx->wbuf[] at this point is in such an order that low   */
/* address bytes in the ORIGINAL byte stream placed in this */
/* buffer will now go to the high end of words on BOTH big  */
/* and little endian systems                                */

sha2_void sha256_compile(sha256_ctx ctx[1])
{   sha2_32t    v[8], j, *p = ctx->wbuf;

    memcpy(v, ctx->hash, 8 * sizeof(sha2_32t));

    for(j = 0; j < 64; j += 16)
    {
        h2_cycle( 0, j); h2_cycle( 1, j); h2_cycle( 2, j); h2_cycle( 3, j);
        h2_cycle( 4, j); h2_cycle( 5, j); h2_cycle( 6, j); h2_cycle( 7, j);
        h2_cycle( 8, j); h2_cycle( 9, j); h2_cycle(10, j); h2_cycle(11, j);
        h2_cycle(12, j); h2_cycle(13, j); h2_cycle(14, j); h2_cycle(15, j);
    }

    ctx->hash[0] += v[0]; ctx->hash[1] += v[1]; ctx->hash[2] += v[2]; ctx->hash[3] += v[3];
    ctx->hash[4] += v[4]; ctx->hash[5] += v[5]; ctx->hash[6] += v[6]; ctx->hash[7] += v[7];
}

/* SHA256 hash data in an array of bytes into hash buffer   */
/* and call the hash_compile function as required.          */

sha2_void sha256_hash(const unsigned char data[], unsigned long len, sha256_ctx ctx[1])
{   sha2_32t pos = (sha2_32t)(ctx->count[0] & SHA256_MASK), 
             space = SHA256_BLOCK_SIZE - pos;
    const unsigned char *sp = data;

    if((ctx->count[0] += len) < len)
        ++(ctx->count[1]);

    while(len >= space)     /* tranfer whole blocks while possible  */
    {
        memcpy(((unsigned char*)ctx->wbuf) + pos, sp, space);
        sp += space; len -= space; space = SHA256_BLOCK_SIZE; pos = 0; 
        bsw_32(ctx->wbuf, SHA256_BLOCK_SIZE >> 2)
        sha256_compile(ctx);
    }

    memcpy(((unsigned char*)ctx->wbuf) + pos, sp, len);
}

/* SHA256 Final padding and digest calculation  */

static sha2_32t  m1[4] =
{
    n_u32(00000000), n_u32(ff000000), n_u32(ffff0000), n_u32(ffffff00)
};

static sha2_32t  b1[4] =
{
    n_u32(80000000), n_u32(00800000), n_u32(00008000), n_u32(00000080)
};

sha2_void sha256_end(unsigned char hval[], sha256_ctx ctx[1])
{   sha2_32t    i = (sha2_32t)(ctx->count[0] & SHA256_MASK);

    bsw_32(ctx->wbuf, (i + 3) >> 2)
    /* bytes in the buffer are now in an order in which references  */
    /* to 32-bit words will put bytes with lower addresses into the */
    /* top of 32 bit words on BOTH big and little endian machines   */
    
    /* we now need to mask valid bytes and add the padding which is */
    /* a single 1 bit and as many zero bits as necessary.           */
    ctx->wbuf[i >> 2] = (ctx->wbuf[i >> 2] & m1[i & 3]) | b1[i & 3];

    /* we need 9 or more empty positions, one for the padding byte  */
    /* (above) and eight for the length count.  If there is not     */
    /* enough space pad and empty the buffer                        */
    if(i > SHA256_BLOCK_SIZE - 9)
    {
        if(i < 60) ctx->wbuf[15] = 0;
        sha256_compile(ctx);
        i = 0;
    }
    else    /* compute a word index for the empty buffer positions  */
        i = (i >> 2) + 1;

    while(i < 14) /* and zero pad all but last two positions      */ 
        ctx->wbuf[i++] = 0;
    
    /* the following 32-bit length fields are assembled in the      */
    /* wrong byte order on little endian machines but this is       */
    /* corrected later since they are only ever used as 32-bit      */
    /* word values.                                                 */

    ctx->wbuf[14] = (ctx->count[1] << 3) | (ctx->count[0] >> 29);
    ctx->wbuf[15] = ctx->count[0] << 3;

    sha256_compile(ctx);

    /* extract the hash value as bytes in case the hash buffer is   */
    /* mislaigned for 32-bit words                                  */
    for(i = 0; i < SHA256_DIGEST_SIZE; ++i)
        hval[i] = (unsigned char)(ctx->hash[i >> 2] >> (8 * (~i & 3)));
}

sha2_void sha256(unsigned char hval[], const unsigned char data[], unsigned long len) 
{   sha256_ctx  cx[1];
    
    sha256_begin(cx); sha256_hash(data, len, cx); sha256_end(hval, cx);
}

#endif

#if defined(SHA_2) || defined(SHA_384) || defined(SHA_512)

#define SHA512_MASK (SHA512_BLOCK_SIZE - 1)

#define rotr64(x,n)   (((x) >> n) | ((x) << (64 - n)))

#if !defined(bswap_64)
#define bswap_64(x) ((((sha2_64t)(bswap_32_TT((sha2_32t)(x)))) << 32) | (bswap_32_TT((sha2_32t)((x) >> 32))))
#endif

#if defined(SWAP_BYTES)
#define bsw_64(p,n) { int _i = (n); while(_i--) p[_i] = bswap_64(p[_i]); }
#else
#define bsw_64(p,n) 
#endif

/* SHA512 mixing function definitions   */

#define s512_0(x) (rotr64((x), 28) ^ rotr64((x), 34) ^ rotr64((x), 39)) 
#define s512_1(x) (rotr64((x), 14) ^ rotr64((x), 18) ^ rotr64((x), 41)) 
#define g512_0(x) (rotr64((x),  1) ^ rotr64((x),  8) ^ ((x) >>  7)) 
#define g512_1(x) (rotr64((x), 19) ^ rotr64((x), 61) ^ ((x) >>  6)) 

/* rotated SHA512 round definition. Rather than swapping variables as in    */
/* FIPS-180, different variables are 'rotated' on each round, returning     */
/* to their starting positions every eight rounds                           */

#define h5(i) ctx->wbuf[i & 15] += \
    g512_1(ctx->wbuf[(i + 14) & 15]) + ctx->wbuf[(i + 9) & 15] + g512_0(ctx->wbuf[(i + 1) & 15])

#define h5_cycle(i,j)  \
    v[(7 - i) & 7] += (j ? h5(i) : ctx->wbuf[i & 15]) + k512[i + j] \
        + s512_1(v[(4 - i) & 7]) + ch(v[(4 - i) & 7], v[(5 - i) & 7], v[(6 - i) & 7]); \
    v[(3 - i) & 7] += v[(7 - i) & 7]; \
    v[(7 - i) & 7] += s512_0(v[(0 - i) & 7]) + maj(v[(0 - i) & 7], v[(1 - i) & 7], v[(2 - i) & 7])

/* SHA384/SHA512 mixing data    */

const sha2_64t  k512[80] = 
{
    sha2_64t(0x428a2f98d728ae22ull), sha2_64t(0x7137449123ef65cdull), 
    sha2_64t(0xb5c0fbcfec4d3b2full), sha2_64t(0xe9b5dba58189dbbcull),
    sha2_64t(0x3956c25bf348b538ull), sha2_64t(0x59f111f1b605d019ull),
    sha2_64t(0x923f82a4af194f9bull), sha2_64t(0xab1c5ed5da6d8118ull),
    sha2_64t(0xd807aa98a3030242ull), sha2_64t(0x12835b0145706fbeull),
    sha2_64t(0x243185be4ee4b28cull), sha2_64t(0x550c7dc3d5ffb4e2ull),
    sha2_64t(0x72be5d74f27b896full), sha2_64t(0x80deb1fe3b1696b1ull),
    sha2_64t(0x9bdc06a725c71235ull), sha2_64t(0xc19bf174cf692694ull),
    sha2_64t(0xe49b69c19ef14ad2ull), sha2_64t(0xefbe4786384f25e3ull),
    sha2_64t(0x0fc19dc68b8cd5b5ull), sha2_64t(0x240ca1cc77ac9c65ull),
    sha2_64t(0x2de92c6f592b0275ull), sha2_64t(0x4a7484aa6ea6e483ull),
    sha2_64t(0x5cb0a9dcbd41fbd4ull), sha2_64t(0x76f988da831153b5ull),
    sha2_64t(0x983e5152ee66dfabull), sha2_64t(0xa831c66d2db43210ull),
    sha2_64t(0xb00327c898fb213full), sha2_64t(0xbf597fc7beef0ee4ull),
    sha2_64t(0xc6e00bf33da88fc2ull), sha2_64t(0xd5a79147930aa725ull),
    sha2_64t(0x06ca6351e003826full), sha2_64t(0x142929670a0e6e70ull),
    sha2_64t(0x27b70a8546d22ffcull), sha2_64t(0x2e1b21385c26c926ull),
    sha2_64t(0x4d2c6dfc5ac42aedull), sha2_64t(0x53380d139d95b3dfull),
    sha2_64t(0x650a73548baf63deull), sha2_64t(0x766a0abb3c77b2a8ull),
    sha2_64t(0x81c2c92e47edaee6ull), sha2_64t(0x92722c851482353bull),
    sha2_64t(0xa2bfe8a14cf10364ull), sha2_64t(0xa81a664bbc423001ull),
    sha2_64t(0xc24b8b70d0f89791ull), sha2_64t(0xc76c51a30654be30ull),
    sha2_64t(0xd192e819d6ef5218ull), sha2_64t(0xd69906245565a910ull),
    sha2_64t(0xf40e35855771202aull), sha2_64t(0x106aa07032bbd1b8ull),
    sha2_64t(0x19a4c116b8d2d0c8ull), sha2_64t(0x1e376c085141ab53ull),
    sha2_64t(0x2748774cdf8eeb99ull), sha2_64t(0x34b0bcb5e19b48a8ull),
    sha2_64t(0x391c0cb3c5c95a63ull), sha2_64t(0x4ed8aa4ae3418acbull),
    sha2_64t(0x5b9cca4f7763e373ull), sha2_64t(0x682e6ff3d6b2b8a3ull),
    sha2_64t(0x748f82ee5defb2fcull), sha2_64t(0x78a5636f43172f60ull),
    sha2_64t(0x84c87814a1f0ab72ull), sha2_64t(0x8cc702081a6439ecull),
    sha2_64t(0x90befffa23631e28ull), sha2_64t(0xa4506cebde82bde9ull),
    sha2_64t(0xbef9a3f7b2c67915ull), sha2_64t(0xc67178f2e372532bull),
    sha2_64t(0xca273eceea26619cull), sha2_64t(0xd186b8c721c0c207ull),
    sha2_64t(0xeada7dd6cde0eb1eull), sha2_64t(0xf57d4f7fee6ed178ull),
    sha2_64t(0x06f067aa72176fbaull), sha2_64t(0x0a637dc5a2c898a6ull),
    sha2_64t(0x113f9804bef90daeull), sha2_64t(0x1b710b35131c471bull),
    sha2_64t(0x28db77f523047d84ull), sha2_64t(0x32caab7b40c72493ull),
    sha2_64t(0x3c9ebe0a15c9bebcull), sha2_64t(0x431d67c49c100d4cull),
    sha2_64t(0x4cc5d4becb3e42b6ull), sha2_64t(0x597f299cfc657e2aull),
    sha2_64t(0x5fcb6fab3ad6faecull), sha2_64t(0x6c44198c4a475817ull)
};

/* Compile 64 bytes of hash data into SHA384/SHA512 digest value  */

sha2_void sha512_compile(sha512_ctx ctx[1])
{   sha2_64t    v[8];
    sha2_32t    j;

    memcpy(v, ctx->hash, 8 * sizeof(sha2_64t));

    for(j = 0; j < 80; j += 16)
    {
        h5_cycle( 0, j); h5_cycle( 1, j); h5_cycle( 2, j); h5_cycle( 3, j);
        h5_cycle( 4, j); h5_cycle( 5, j); h5_cycle( 6, j); h5_cycle( 7, j);
        h5_cycle( 8, j); h5_cycle( 9, j); h5_cycle(10, j); h5_cycle(11, j);
        h5_cycle(12, j); h5_cycle(13, j); h5_cycle(14, j); h5_cycle(15, j);
    }

    ctx->hash[0] += v[0]; ctx->hash[1] += v[1]; ctx->hash[2] += v[2]; ctx->hash[3] += v[3];
    ctx->hash[4] += v[4]; ctx->hash[5] += v[5]; ctx->hash[6] += v[6]; ctx->hash[7] += v[7];
}

/* Compile 128 bytes of hash data into SHA256 digest value  */
/* NOTE: this routine assumes that the byte order in the    */
/* ctx->wbuf[] at this point is in such an order that low   */
/* address bytes in the ORIGINAL byte stream placed in this */
/* buffer will now go to the high end of words on BOTH big  */
/* and little endian systems                                */

sha2_void sha512_hash(const unsigned char data[], unsigned long len, sha512_ctx ctx[1])
{   sha2_32t pos = (sha2_32t)(ctx->count[0] & SHA512_MASK), 
             space = SHA512_BLOCK_SIZE - pos;
    const unsigned char *sp = data;

    if((ctx->count[0] += len) < len)
        ++(ctx->count[1]);

    while(len >= space)     /* tranfer whole blocks while possible  */
    {
        memcpy(((unsigned char*)ctx->wbuf) + pos, sp, space);
        sp += space; len -= space; space = SHA512_BLOCK_SIZE; pos = 0; 
        bsw_64(ctx->wbuf, SHA512_BLOCK_SIZE >> 3);        
        sha512_compile(ctx);
    }

    memcpy(((unsigned char*)ctx->wbuf) + pos, sp, len);
}

/* SHA384/512 Final padding and digest calculation  */

static sha2_64t  m2[8] =
{
    sha2_64t(0x0000000000000000ull), sha2_64t(0xff00000000000000ull),
    sha2_64t(0xffff000000000000ull), sha2_64t(0xffffff0000000000ull),
    sha2_64t(0xffffffff00000000ull), sha2_64t(0xffffffffff000000ull),
    sha2_64t(0xffffffffffff0000ull), sha2_64t(0xffffffffffffff00ull)
};

static sha2_64t  b2[8] =
{
    sha2_64t(0x8000000000000000ull), sha2_64t(0x0080000000000000ull),
    sha2_64t(0x0000800000000000ull), sha2_64t(0x0000008000000000ull),
    sha2_64t(0x0000000080000000ull), sha2_64t(0x0000000000800000ull),
    sha2_64t(0x0000000000008000ull), sha2_64t(0x0000000000000080ull)
};

static void sha_end(unsigned char hval[], sha512_ctx ctx[1], const unsigned int hlen)
{   sha2_32t    i = (sha2_32t)(ctx->count[0] & SHA512_MASK);

    bsw_64(ctx->wbuf, (i + 7) >> 3);

    /* bytes in the buffer are now in an order in which references  */
    /* to 64-bit words will put bytes with lower addresses into the */
    /* top of 64 bit words on BOTH big and little endian machines   */
    
    /* we now need to mask valid bytes and add the padding which is */
    /* a single 1 bit and as many zero bits as necessary.           */
    ctx->wbuf[i >> 3] = (ctx->wbuf[i >> 3] & m2[i & 7]) | b2[i & 7];

    /* we need 17 or more empty byte positions, one for the padding */
    /* byte (above) and sixteen for the length count.  If there is  */
    /* not enough space pad and empty the buffer                    */
    if(i > SHA512_BLOCK_SIZE - 17)
    {
        if(i < 120) ctx->wbuf[15] = 0;
        sha512_compile(ctx);
        i = 0;
    }
    else
        i = (i >> 3) + 1;

    while(i < 14)
        ctx->wbuf[i++] = 0;
    
    /* the following 64-bit length fields are assembled in the      */
    /* wrong byte order on little endian machines but this is       */
    /* corrected later since they are only ever used as 64-bit      */
    /* word values.                                                 */

    ctx->wbuf[14] = (ctx->count[1] << 3) | (ctx->count[0] >> 61);
    ctx->wbuf[15] = ctx->count[0] << 3;

    sha512_compile(ctx);

    /* extract the hash value as bytes in case the hash buffer is   */
    /* misaligned for 32-bit words                                  */
    for(i = 0; i < hlen; ++i)
        hval[i] = (unsigned char)(ctx->hash[i >> 3] >> (8 * (~i & 7)));
}

#endif

#if defined(SHA_2) || defined(SHA_384)

/* SHA384 initialisation data   */

const sha2_64t  i384[80] = 
{
    sha2_64t(0xcbbb9d5dc1059ed8ull), sha2_64t(0x629a292a367cd507ull),
    sha2_64t(0x9159015a3070dd17ull), sha2_64t(0x152fecd8f70e5939ull),
    sha2_64t(0x67332667ffc00b31ull), sha2_64t(0x8eb44a8768581511ull),
    sha2_64t(0xdb0c2e0d64f98fa7ull), sha2_64t(0x47b5481dbefa4fa4ull)
};

sha2_void sha384_begin(sha384_ctx ctx[1])
{
    ctx->count[0] = ctx->count[1] = 0;
    memcpy(ctx->hash, i384, 8 * sizeof(sha2_64t));
}

sha2_void sha384_end(unsigned char hval[], sha384_ctx ctx[1])
{
    sha_end(hval, ctx, SHA384_DIGEST_SIZE);
}

sha2_void sha384(unsigned char hval[], const unsigned char data[], unsigned long len)
{   sha384_ctx  cx[1];
    
    sha384_begin(cx); sha384_hash(data, len, cx); sha384_end(hval, cx);
}

#endif

#if defined(SHA_2) || defined(SHA_512)

/* SHA512 initialisation data   */

const sha2_64t  i512[80] = 
{
    sha2_64t(0x6a09e667f3bcc908ull), sha2_64t(0xbb67ae8584caa73bull),
    sha2_64t(0x3c6ef372fe94f82bull), sha2_64t(0xa54ff53a5f1d36f1ull),
    sha2_64t(0x510e527fade682d1ull), sha2_64t(0x9b05688c2b3e6c1full),
    sha2_64t(0x1f83d9abfb41bd6bull), sha2_64t(0x5be0cd19137e2179ull)
};

sha2_void sha512_begin(sha512_ctx ctx[1])
{
    ctx->count[0] = ctx->count[1] = 0;
    memcpy(ctx->hash, i512, 8 * sizeof(sha2_64t));
}

sha2_void sha512_end(unsigned char hval[], sha512_ctx ctx[1])
{
    sha_end(hval, ctx, SHA512_DIGEST_SIZE);
}

sha2_void sha512(unsigned char hval[], const unsigned char data[], unsigned long len) 
{   sha512_ctx  cx[1];
    
    sha512_begin(cx); sha512_hash(data, len, cx); sha512_end(hval, cx);
}

#endif

#if defined(SHA_2)

#define CTX_256(x)  ((x)->uu->ctx256)
#define CTX_384(x)  ((x)->uu->ctx512)
#define CTX_512(x)  ((x)->uu->ctx512)

/* SHA2 initialisation */

sha2_int sha2_begin(unsigned long len, sha2_ctx ctx[1])
{   unsigned long   l = len;
    switch(len)
    {
        case 256:   l = len >> 3;
        case  32:   CTX_256(ctx)->count[0] = CTX_256(ctx)->count[1] = 0;
                    memcpy(CTX_256(ctx)->hash, i256, 32); break;
        case 384:   l = len >> 3;
        case  48:   CTX_384(ctx)->count[0] = CTX_384(ctx)->count[1] = 0;
                    memcpy(CTX_384(ctx)->hash, i384, 64); break;
        case 512:   l = len >> 3;
        case  64:   CTX_512(ctx)->count[0] = CTX_512(ctx)->count[1] = 0;
                    memcpy(CTX_512(ctx)->hash, i512, 64); break;
        default:    return SHA2_BAD;
    }
    
    ctx->sha2_len = l; return SHA2_GOOD;
}

sha2_void sha2_hash(const unsigned char data[], unsigned long len, sha2_ctx ctx[1])
{
    switch(ctx->sha2_len)
    {
        case 32: sha256_hash(data, len, CTX_256(ctx)); return;
        case 48: sha384_hash(data, len, CTX_384(ctx)); return;
        case 64: sha512_hash(data, len, CTX_512(ctx)); return;
    }
}

sha2_void sha2_end(unsigned char hval[], sha2_ctx ctx[1])
{
    switch(ctx->sha2_len)
    {
        case 32: sha256_end(hval, CTX_256(ctx)); return;
        case 48: sha_end(hval, CTX_384(ctx), SHA384_DIGEST_SIZE); return;
        case 64: sha_end(hval, CTX_512(ctx), SHA512_DIGEST_SIZE); return;
    }
}

sha2_int sha2(unsigned char hval[], unsigned long size,
                                const unsigned char data[], unsigned long len)
{   sha2_ctx    cx[1];

    if(sha2_begin(size, cx) == SHA2_GOOD)
    {
        sha2_hash(data, len, cx); sha2_end(hval, cx); return SHA2_GOOD;
    }
    else
        return SHA2_BAD;
}

#endif

