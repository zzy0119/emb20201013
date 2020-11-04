#include <stdio.h>
#include <string.h>

char *mystrncpy(char *dest, char *src, int size);
char *mystrcat(char *dest, char *src);
int mystrcmp(char *s1, char *s2);
char *mystrstr(char *s1, char *s2);
int main(void)
{
	char d[100] = "hello";
	char *p = "good morning";
	
	// printf("%s\n", mystrcat(d, p));
	strncat(d, p, 94);

	printf("%d\n", mystrcmp("hello", "hi"));
	printf("%d\n", mystrcmp("hello", "hello"));

	printf("%s\n", mystrstr("hello wooooooowabcd", "ooow"));

	return 0;
}

// strcpy(3)
char *mystrcpy(char *dest, char *src)
{
	char *ret = dest;
	int i;

#if 0
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
#endif
	for (i = 0; src[i]; i++) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return ret;
}

char *mystrncpy(char *dest, char *src, int size)
{
	int i;

	for (i = 0; src[i] && i < size-1; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return dest;
}

// 字符串拼接
char *mystrcat(char *dest, char *src)
{
	char *ret = dest; // char *ret; ret = dest;

	while (*dest)
		dest++;
	mystrcpy(dest, src);

	return ret;
}

int mystrcmp(char *s1, char *s2)
{
	while (*s1 == *s2) {
		if (*s1 == '\0')
			return 0;
		s1 ++;
		s2 ++;
	}
	return *s1 - *s2;
}

// s1中第一次出现s2首地址
char *mystrstr(char *s1, char *s2)
{
	char *s1_equal, *s2_equal;		

	while (*s1) {
		if (*s1 == *s2) {
			s1_equal = s1+1;
			s2_equal = s2+1;
			while (*s1_equal == *s2_equal) {
				s1_equal ++;
				s2_equal ++;
			}
			if (*s2_equal == '\0')
				return s1;
		}	
		s1++;
	}

	return NULL; // 0
}

