/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void
die(const char *fmt, ...)
{
	va_list ap;
	int saved_errno;

	saved_errno = errno;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':')
		fprintf(stderr, " %s", strerror(saved_errno));
	fputc('\n', stderr);

	exit(1);
}

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		die("calloc:");
	return p;
}

// arr1 and arr2 should be null terminated
// Returns a null terminated array.
const char **
merge(const char **arr1, const char **arr2)
{
	int arr1Length = 0;
	int arr2Length = 0;

	while(arr1 && arr1[arr1Length]) {
		arr1Length++;
	}
	while(arr2 && arr2[arr2Length]) {
		arr2Length++;
	}

	const char **mergedArr = malloc((arr1Length + arr2Length + 1) * sizeof(char *));
	if (!mergedArr)
		return NULL;
	
	for(int i = 0; i < arr1Length; i++) {
		mergedArr[i] = arr1[i];
	}
	for(int i = 0; i < arr2Length; i++) {
		mergedArr[arr1Length + i] = arr2[i];
	}
	mergedArr[arr1Length + arr2Length] = NULL;
	
	return mergedArr;
}
