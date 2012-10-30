#ifdef UCLA_HAVE_UNIX

/*
GLibC does not provide safe string copy and concatenate functions.
This is a tiny hack to get those functions (from snprintf).
*/

#include <stdio.h>
#include <string.h>

#ifndef M_SAFESTRING_H
#define M_SAFESTRING_H

/**
Copies up to \b n - 1 characters from the string \b source to \b destination,
NUL-terminating the result if \b n is not 0.
@param \b destination Pointer to destination buffer.
@param \b n Size in bytes of \b destination buffer (includeing 0).
@param \b source Source buffer.
@retrun The total length of the created string.
If the return value is >= dstsize, the output string has been truncated.
*/
size_t m_strlcpy(char *destination, size_t n, char const *source);

/**
Appends string \b source to the end of \b destination. It will append at most
\b n - strlen(\b destination) - 1 characters. It will then NUL-terminate, unless
\b n is 0 or the original \b destination string was longer than \b n (in
practice this should not happen as it means that either \b n is
incorrect or that \b destination is not a proper string).
@param \b destination Pointer to destination buffer.
@param \b n Size in bytes of \b destination buffer (includeing 0).
@param \b source Source buffer.
@retrun The total length of the created string.
If the return value is >= dstsize, the output string has been truncated.
*/
size_t m_strlcat(char *destination, size_t n, char const *source);

#endif // M_SAFESTRING_H

#endif
