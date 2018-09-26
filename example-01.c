
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

/* 1) Fill an array named 'binary'.
 * 2) Convert 'binary' in base64 format in an array named 'base64'.
 * 3) Print 'base64'.
 * 4) Convert 'base64' in binary format in an array named 'output'.
 * 5) Check if the conversion was successful.
 * 6) Check the length of 'output'.
 * 7) Compare 'binary' with 'output'. */
int main( void ) {

    char binary[64];
    for( int i = 0; i < 64; ++i )
        binary[i] = i;

    char base64[128];
    bintob64( base64, binary, sizeof binary );

    printf( "%s%s%s", "The base64: '", base64, "'.\n" );

    char output[64];
    char* const end = b64tobin( output, base64 );
    if ( !end ) {
        fputs( "Bad base64 format.", stderr );
        return -1;
    }

    int const outputlen = end - output;
    if ( outputlen != sizeof binary ) {
        fputs( "The length of the output is not as expected.\n", stderr );
        return -1;
    }

    int const equal = !memcmp( binary, output, sizeof binary );
    if( !equal ) {
        fputs( "The output is different from the input.\n", stderr );
        return -1;
    }

    return 0;
}