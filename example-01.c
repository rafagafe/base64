
/*
 * Developed by Rafa Garcia <rafagarcia77@gmail.com>
 *
 * example-01.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * example-01.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with example-01.c.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

    uint8_t binary[64];
    for( unsigned int i = 0; i < 64; ++i )
        binary[i] = i;

    char base64[128];
    bintob64( base64, binary, sizeof binary );

    printf( "%s%s%s", "The base64: '", base64, "'.\n" );

    uint8_t output[64];
    uint8_t* const end = b64tobin( output, base64 );
    if ( !end ) {
        fputs( "Bad base64 format.", stderr );
        return EXIT_FAILURE;
    }

    unsigned int const outputlen = end - output;
    if ( outputlen != sizeof binary ) {
        fputs( "The length of the output is not as expected.\n", stderr );
        return EXIT_FAILURE;
    }

    bool const equal = !memcmp( binary, output, sizeof binary );
    if( !equal ) {
        fputs( "The output is different from the input.\n", stderr );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}