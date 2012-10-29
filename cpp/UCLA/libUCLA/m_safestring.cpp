#include "m_safestring.h"

#ifdef UCLA_HAVE_UNIX

size_t m_strlcpy(char *destination, size_t n, char const *source)
{
	return snprintf(destination, n, "%s", source);
}

size_t m_strlcat(char *destination, size_t n, char const *source)
{
	return snprintf(destination, n, "%s%s", destination, source);
}

#endif