
/*
 * Developed by Rafa Garcia <rafagarcia77@gmail.com>
 *
 * unit-test.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * unit-test.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with unit-test.c.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "base64.h"

#define done() return 0

#define fail() return __LINE__

static unsigned int checkqty = 0;

#define check( x ) { ++checkqty; if (!(x)) fail(); }

static int wikiExample( void ) {

    static char const src[] = "any carnal pleasure.";
    unsigned int const srclen  = sizeof src - 1;

    char buffer[32];
    bintob64( buffer, src, srclen );
    check( !strcmp( buffer, "YW55IGNhcm5hbCBwbGVhc3VyZS4=" ) );

    char* end = b64tobin( buffer, buffer );
    check( end );

    *end = '\0';
    check( !strcmp( buffer, src ) );

    bintob64( buffer, src, srclen - 1 );
    check( !strcmp( buffer, "YW55IGNhcm5hbCBwbGVhc3VyZQ==" ) );

    bintob64( buffer, src, srclen - 2 );
    check( !strcmp( buffer, "YW55IGNhcm5hbCBwbGVhc3Vy" ) );

    done();
}

static int allDigits( void ) {

    static char const digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz"
                                 "0123456789"
                                 "+/";

    unsigned char binary[72];
    unsigned char* const end = b64tobin( binary, digits );
    check( end );

    unsigned int const binarylen = end - binary;
    unsigned int const digitslen = sizeof digits - 1;
    unsigned int const calclen   = 3 * digitslen / 4;
    check( binarylen == calclen );

    char base64[72];
    char* const nullchar = bintob64( base64, binary, binarylen );
    check( nullchar );
    check( '\0' == *nullchar );
    check( !strcmp( base64, digits ) );

    done();
}

static int aliasing ( void ) {

    static char const message[] = "aliasing";

    char base64[32];
    char* const nullchar = bintob64( base64, message, sizeof message );
    check( nullchar );
    check( '\0' == *nullchar );
    check( nullchar - base64 == 4 * sizeof message / 3 );

    char* end = b64decode( base64 );
    check( end );
    check( !strcmp( message, base64 ) );

    done();
}

static int sizes( void ) {
    char binary[6];
    for( unsigned int i = 1; i < sizeof binary; ++i )
        binary[i] = i;

    char base64[24];
    for( unsigned int i = 1; i < sizeof binary; ++i ) {
        char* const b64end = bintob64( base64, binary, i );
        unsigned int const b64len = b64end - base64;
        unsigned int const expectedLen = 4 * ( 1 + i / 4 );
        check( b64len == expectedLen );
        char* binend = b64decode( base64 );
        check( binend );
        unsigned int const binlen = binend - base64;
        check( binlen == i );
        bool const equal = !memcmp( binary, base64, i );
        check( equal );
    }
    done();
}

int badformats( void ) {
    {
        static char const base64[] = { 0 };
        uint8_t binary[5];
        uint8_t* end = b64tobin( binary, base64 );
        check( end == binary );
    }
    {
        static char const base64[] = { 'a', 'a', -5, 'a', 0 };
        uint8_t binary[5];
        uint8_t* end = b64tobin( binary, base64 );
        check( !end );
    }
    {
        uint8_t binary[5];
        uint8_t* end = b64tobin( binary, "aaaa_" );
        check( end - binary == 3 );
    }
    {
        uint8_t binary[5];
        uint8_t* end = b64tobin( binary, "aa_" );
        check( !end );
    }
    {
        uint8_t binary[5];
        uint8_t* end = b64tobin( binary, "=aaaa_" );
        check( end == binary );
    }
    done();
}

struct test {
    int(*func)(void);
    char const* name;
};

static int test_exec( struct test const* test ) {
    int const err = test->func();
    if ( err ) {
        fprintf( stderr, "%s%s%s%d%s", "Failed test: '", test->name, "' Line: ", err, ".\n" );
        return 1;
    }
    return 0;
}

static struct test const tests[] = {
    { wikiExample, "Wikipedia example" },
    { allDigits,   "All digits"        },
    { aliasing,    "Aliasing"          },
    { sizes,       "Sizes"             },
    { badformats,  "Bad Formats"       },
};

int main( void ) {
    int failed = 0;
    unsigned int const qty = sizeof tests / sizeof *tests;
    for( unsigned int i = 0; i < qty; ++i )
        failed += test_exec( tests + i );
    unsigned int const percent = 100.0 * ( qty - failed ) / qty;
    printf( "%d%s%d%s", percent, "%. ", checkqty, " checks.\n" );
    return failed;
}