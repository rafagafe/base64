
/*
 * Developed by Rafa Garcia <rafagarcia77@gmail.com>
 *
 * base64.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * base64.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with base64.h.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _BASE64_H_
#define	_BASE64_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/** @defgroup base64 Base64 Converter.
  * @{ */

/** Convert a binary memory block in a base64 null-terminated string.
  * @param dest Destination memory wher to put the base64 null-terminated string.
  * @param src Source binary memory block.
  * @param size Size in bytes of source binary memory block.
  * @return A pointer to the null character of the base64 null-terminated string. */
char* bintob64( char* dest, void const* src, size_t size );

/** Convert a base64 string to binary format.
  * @param dest Destination memory block.
  * @param src Source base64 string.
  * @return If success a pointer to the next byte in memory block.
  *         Null if string has a bad format.  */
void* b64tobin( void* dest, char const* src );

/** Convert a base64 string to binary format.
  * @param p Source base64 string and destination memory block.
  * @return If success a pointer to the next byte in memory block.
  *         Null if string has a bad format.  */
static inline void* b64decode( void* p ) {
    return b64tobin( p, (char*)p );
}

/** @ } */

#ifdef __cplusplus
}
#endif

#endif	/* _BASE64_H_ */
