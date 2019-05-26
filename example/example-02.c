
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

/* 1) A null-terminated string is stored in an array named 'plain'.
 * 2) The text in 'plain' is printed.
 * 3) Convert 'plain' in base64 format in an array named 'buffer'.
 * 4) Print 'buffer'.
 * 5) Convert 'buffer' in plain text in the same array 'buffer'.
 * 6) Check if the conversion was successful.
 * 7) Check the length of 'buffer'.
 * 8) Compare 'plain' with 'buffer'.
 * 9) Print the plain text stored in 'buffer'. */
int main( void ) {

    static char const plain[] = "This is a plain text.";
    puts( plain );

    char buffer[128];
    bintob64( buffer, plain, sizeof plain );

    printf( "%s%s%s", "The base64: '", buffer, "'.\n" );

    char* const end = b64decode( buffer );
    if ( !end ) {
        fputs( "Bad base64 format.", stderr );
        return -1;
    }

    int const outputlen = end - buffer;
    if ( outputlen != sizeof plain ) {
        fputs( "The length of the output is not as expected.\n", stderr );
        return -1;
    }

    int const equal = !strcmp( plain, buffer );
    if( !equal ) {
        fputs( "The output is different from the input.\n", stderr );
        return -1;
    }

    puts( buffer );

    return 0;
}