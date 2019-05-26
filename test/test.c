
/*
<https://github.com/rafagafe/base64>
     
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
  Copyright (c) 2016-2018 Rafa Garcia <rafagarcia77@gmail.com>.
  Permission is hereby  granted, free of charge, to any  person obtaining a copy
  of this software and associated  documentation files (the "Software"), to deal
  in the Software  without restriction, including without  limitation the rights
  to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
  copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
  IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
  FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
  AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
  LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
    
*/

#include <stdio.h>
#include <string.h>
#include "base64.h"


// ----------------------------------------------------- Test "framework": ---

#define done() return 0
#define fail() return __LINE__
static int checkqty = 0;
#define check( x ) do { ++checkqty; if (!(x)) fail(); } while ( 0 )

struct test {
    int(*func)(void);
    char const* name;
};

static int test_suit( struct test const* tests, int numtests ) {
    printf( "%s", "\n\nTests:\n" );
    int failed = 0;
    for( int i = 0; i < numtests; ++i ) {
        printf( " %02d%s%-25s ", i, ": ", tests[i].name );
        int linerr = tests[i].func();
        if ( 0 == linerr )
            printf( "%s", "OK\n" );
        else {
            printf( "%s%d\n", "Failed, line: ", linerr );
            ++failed;
        }
    }
    printf( "\n%s%d\n", "Total checks: ", checkqty );
    printf( "%s[ %d / %d ]\r\n\n\n", "Tests PASS: ", numtests - failed, numtests );
    return failed;
}


// ----------------------------------------------------------- Unit tests: ---

static int wikiExample( void ) {

    static char const src[] = "any carnal pleasure.";
    int const srclen  = sizeof src - 1;

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

    char binary[72];
    char* const end = b64tobin( binary, digits );
    check( end );

    int const binarylen = end - binary;
    int const digitslen = sizeof digits - 1;
    int const calclen   = 3 * digitslen / 4;
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
    for( int i = 1; i < sizeof binary; ++i )
        binary[i] = i;

    char base64[24];
    for( int i = 1; i < sizeof binary; ++i ) {
        char* const b64end = bintob64( base64, binary, i );
        int const b64len = b64end - base64;
        int const expectedLen = 4 * ( 1 + i / 4 );
        check( b64len == expectedLen );
        char* binend = b64decode( base64 );
        check( binend );
        int const binlen = binend - base64;
        check( binlen == i );
        int const equal = 0 == memcmp( binary, base64, i );
        check( equal );
    }
    done();
}

int badformats( void ) {
    {
        static char const base64[] = { 0 };
        char binary[5];
        char* end = b64tobin( binary, base64 );
        check( end == binary );
    }
    {
        static char const base64[] = { 'a', 'a', -5, 'a', 0 };
        char binary[5];
        char* end = b64tobin( binary, base64 );
        check( !end );
    }
    {
        char binary[5];
        char* end = b64tobin( binary, "aaaa_" );
        check( end - binary == 3 );
    }
    {
        char binary[5];
        char* end = b64tobin( binary, "aa_" );
        check( !end );
    }
    {
        char binary[5];
        char* end = b64tobin( binary, "=aaaa_" );
        check( end == binary );
    }
    done();
}


// --------------------------------------------------------- Execute tests: ---

int main( void ) {
    static struct test const tests[] = {
        { wikiExample, "Wikipedia example" },
        { allDigits,   "All digits"        },
        { aliasing,    "Aliasing"          },
        { sizes,       "Sizes"             },
        { badformats,  "Bad Formats"       }
    };
    return test_suit( tests, sizeof tests / sizeof *tests );
}
