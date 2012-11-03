#include "m_safestring.h"

/* This code is derived from 
 *
 * $OpenBSD: strlcpy.c,v 1.4 1999/05/01
 * and
 * $OpenBSD: strlcat.c,v 1.2 1999/06/17
 *
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

size_t UCLA::Utils::m_strlcpy(char *destination, size_t n, char const *source)
{
	register char *d = destination;
	register const char *s = source;
	register size_t i = n;

	/* Copy as many bytes as will fit */
	if (i != 0 && --i != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--i != 0);
	}

	/* Not enough room in destination, add NUL and traverse rest of source */
	if (i == 0) {
		if (n != 0)
			*d = '\0';		/* NUL-terminate destination */
		while (*s++);
	}

	return(s - source - 1);	/* count does not include NUL */
}

size_t UCLA::Utils::m_strlcat(char *destination, size_t n, char const *source)
{
    	register char *d = destination;
	register const char *s = source;
	register size_t i = n;
	size_t dlen;

	/* Find the end of destination and adjust bytes left but don't go past end */
	while (*d != '\0' && i-- != 0)
		d++;

	dlen = d - destination;
	i = n - dlen;

	if (i == 0)
		return(dlen + strlen(s));

	while (*s != '\0') {
		if (i != 1) {
			*d++ = *s;
			i--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - source));	/* count does not include NUL */
}
