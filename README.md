# Base64
[![Build Status](https://travis-ci.org/rafagafe/base64.svg?branch=master)](https://travis-ci.org/rafagafe/base64)

Base64 is a C library to convert from plain to base64 and vice versa suitable for embedded systems.

# API
To convert from plain to base64 the following function is used:
```C
char* bintob64( char* dest, void const* src, size_t size );
```
* The parameter 'src' is the source memory block to be converted.
* The parameter 'size' is the size in bytes of the source memory block.
* The parameter 'dest' is the destination buffer where the translation to base64 is stored. Also a null character is added at the end to become a null-terminated string.
* The return value is a pointer to the null character.

To convert from base64 to plain the following function is used:
```C
void* b64tobin( void* dest, char const* src );
```
* The parameter 'src' is the source base64 string. It must be terminated in a non base64-digit. A null-terminated string is OK.
* The parameter 'dest' is the destination memory block where the result of convertion is stroed.
* The return value is a null pointer if the base64 string has bad format. If the convertion is successfully the return value is a pointer to the end of the convertion. With this pointer you can get the length of the result.

Convert from base64 to plain in the same memory block is possible using the previous function by setting the same pointer for the destination and source. Or just use the following wrapper function:
```C
static inline void* b64decode( void* p ) {
    return b64tobin( p, (char*)p );
}
```
