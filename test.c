/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaassila <yaassila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:57:30 by yaassila          #+#    #+#             */
/*   Updated: 2022/11/08 15:36:50 by yaassila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc test.c -o test -L. -lft -lbsd && ./test

#include "libft.h"
#include <bsd/string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define test(condition) printf(condition ? GRN "OK\n" RESET : RED "Error\n" RESET)

void test_isascii(void)
{
	test(isascii(32) == ft_isascii(32));
	test(isascii(0) == ft_isascii(0));
	test(isascii(-1) == ft_isascii(-1));
	test(isascii(256) == ft_isascii(256));
	test(isascii(255) == ft_isascii(255));
	test(isascii(128) == ft_isascii(128));
	test(isascii(127) == ft_isascii(127));
	test(isascii(300) == ft_isascii(300));
}


void test_isprint(void)
{
	test(ft_isprint(33) > 0);
	test(ft_isprint(32) > 0);
	test(isprint(31) == ft_isprint(31));
	test(isprint(0) == ft_isprint(0));
	test(isprint(-1) == ft_isprint(-1));
	test(ft_isprint(126) > 0);
	test(isprint(127) == ft_isprint(127));
	test(isprint(128) == ft_isprint(128));
	test(isprint(300) == ft_isprint(300));
}


void	test_bzero(void)
{
	unsigned char tmp[100];
	memset(tmp, 'A', 100);
	ft_bzero(tmp, 42);
	test(tmp[0] == '\0');
	test(tmp[41] == '\0');
	test(tmp[42] == 'A');
}


void	test_memcpy_1(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];

	memcpy(dest, src, 12);
	ft_memcpy(ft_dest, ft_src, 12);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_memcpy_2(void)
{
	char	src[] = "Hello World";
	char	ft_src[] = "Hello World";

	memcpy(src + 2, src, 5);
	ft_memcpy(ft_src + 2, ft_src, 5);

	test(strcmp(src + 2, ft_src + 2) == 0);
}

void	test_memcpy_3(void)
{
	char	dest[] = "Hello World";
	char	ft_dest[] = "Hello World";

	memcpy(dest, dest + 4, 5);
	ft_memcpy(ft_dest, ft_dest + 4, 5);

	test(strcmp(dest, ft_dest) == 0);
}


void	test_memmove_1(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];

	memmove(dest, src, 12);
	ft_memmove(ft_dest, ft_src, 12);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_memmove_2(void)
{
	char	src[] = "Hello World";
	char	ft_src[] = "Hello World";

	memmove(src + 2, src, 5);
	ft_memmove(ft_src + 2, ft_src, 5);

	test(strcmp(src + 2, ft_src + 2) == 0);
}

void	test_memmove_3(void)
{
	char	dest[] = "Hello World";
	char	ft_dest[] = "Hello World";

	memmove(dest, dest + 4, 5);
	ft_memmove(ft_dest, ft_dest + 4, 5);

	test(strcmp(dest, ft_dest) == 0);
}


void	test_strlcpy_1(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];

	strlcpy(dest, src, 12);
	ft_strlcpy(ft_dest, ft_src, 12);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_strlcpy_2(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];

	strlcpy(dest, src, 6);
	ft_strlcpy(ft_dest, ft_src, 6);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_strlcpy_3(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];
	size_t	res;
	size_t	ft_res;

	res = strlcpy(dest, src, 6);
	ft_res = ft_strlcpy(ft_dest, ft_src, 6);

	test(res == ft_res);
}

void	test_strlcpy_4(void)
{
	char	src[] = "Hello World\0";
	char	dest[12];
	char	ft_src[] = "Hello World\0";
	char	ft_dest[12];
	size_t	res;
	size_t	ft_res;

	res = strlcpy(dest, src, 0);
	ft_res = ft_strlcpy(ft_dest, ft_src, 0);

	test(res == ft_res);
}

void	test_strlcpy_5(void)
{
	char	src[] = "Hello\0World\0";
	char	dest[12];
	char	ft_src[] = "Hello\0World\0";
	char	ft_dest[12];

	strlcpy(dest, src, 12);
	ft_strlcpy(ft_dest, ft_src, 12);

	test(!memcmp(dest, ft_dest, 12));
}

void	test_strlcpy_6(void)
{
	char	src[] = "Hello\0World\0";
	char	dest[12];
	char	ft_src[] = "Hello\0World\0";
	char	ft_dest[12];

	test(strlcpy(dest, src, -1) == ft_strlcpy(ft_dest, ft_src, -1));
}


void	test_strlcat_1(void)
{
	char	src[] = "Hello World\0";
	char	dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	char	ft_src[] = "Hello World\0";
	char	ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";

	strlcat(dest, src, 12);
	ft_strlcat(ft_dest, ft_src, 12);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_strlcat_2(void)
{
	char	src[] = "Hello World\0";
	char	dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	char	ft_src[] = "Hello World\0";
	char	ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";

	strlcat(dest, src, 6);
	ft_strlcat(ft_dest, ft_src, 6);

	test(strcmp(dest, ft_dest) == 0);
}

void	test_strlcat_3(void)
{
	char	src[] = "Hello World\0";
	char	dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	char	ft_src[] = "Hello World\0";
	char	ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	size_t	res;
	size_t	ft_res;

	res = strlcat(dest, src, 6);
	ft_res = ft_strlcat(ft_dest, ft_src, 6);

	test(res == ft_res);
}

void	test_strlcat_4(void)
{
	char	src[] = "Hello World\0";
	char	dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	char	ft_src[] = "Hello World\0";
	char	ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	size_t	res;
	size_t	ft_res;

	res = strlcat(dest, src, 0);
	ft_res = ft_strlcat(ft_dest, ft_src, 0);

	test(res == ft_res);
}

void	test_strlcat_5(void)
{
	char	src[] = "Hello World\0";
	char	dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
	char	ft_src[] = "Hello World\0";
	char	ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";

	test(strlcat(dest, src, -1) == ft_strlcat(ft_dest, ft_src, -1));
}


void test_toupper(void)
{
	test(ft_toupper('a') == 'A');
	test(ft_toupper('p') == 'P');
	test(ft_toupper('z') == 'Z');
	test(ft_toupper('V') == 'V');
	test(ft_toupper('&') == '&');
	test(toupper('p' + 256) == ft_toupper('p' + 256));
}


void test_tolower(void)
{
	test(ft_tolower('A') == 'a');
	test(ft_tolower('P') == 'p');
	test(ft_tolower('Z') == 'z');
	test(ft_tolower('v') == 'v');
	test(ft_tolower('&') == '&');
	test(toupper('P' + 256) == ft_toupper('P' + 256));
}


void test_strchr(void)
{
	test(strchr("Aecde", 'A') == ft_strchr("Aecde", 'A'));
	test(strchr("Aecde", 'c') == ft_strchr("Aecde", 'c'));
	test(strchr("Aecde", 'e') == ft_strchr("Aecde", 'e'));
	test(strchr("Aecde", '\0') == ft_strchr("Aecde", '\0'));
	test(strchr("Aecde", 'f') == ft_strchr("Aecde", 'f'));
}


void test_strrchr(void)
{
	test(strrchr("Aecde", 'A') == ft_strrchr("Aecde", 'A'));
	test(strrchr("Aecde", 'c') == ft_strrchr("Aecde", 'c'));
	test(strrchr("Aecde", 'e') == ft_strrchr("Aecde", 'e'));
	test(strrchr("Aecde", '\0') == ft_strrchr("Aecde", '\0'));
	test(strrchr("Aecde", 'f') == ft_strrchr("Aecde", 'f'));
}


void test_strncmp(void)
{
	test(strncmp("Abc", "Def", 0) == ft_strncmp("Abc", "Def", 0));
	test(strncmp("Abc", "Abd", 0) == ft_strncmp("Abc", "Abd", 0));
	test(strncmp("Abc", "Abd", 1) == ft_strncmp("Abc", "Abd", 1));
	test(strncmp("Abc", "Abd", 2) == ft_strncmp("Abc", "Abd", 2));
	test(strncmp("Abc", "Abd", 3) == ft_strncmp("Abc", "Abd", 3));
	test(strncmp("Abc", "Abd", 4) == ft_strncmp("Abc", "Abd", 4));
	test(strncmp("Abc", "Abd", 5) == ft_strncmp("Abc", "Abd", 5));
}


void test_memchr(void)
{
	test(memchr("Aecde", 'A', 5) == ft_memchr("Aecde", 'A', 5));
	test(memchr("Aecde", 'c', 5) == ft_memchr("Aecde", 'c', 5));
	test(memchr("Aecde", 'e', 5) == ft_memchr("Aecde", 'e', 5));
	test(memchr("Aecde", '\0', 5) == ft_memchr("Aecde", '\0', 5));
	test(memchr("Aecde", 'f', 5) == ft_memchr("Aecde", 'f', 5));
}


void test_memcmp(void)
{
	unsigned char arr1[] = {0, 0, 127, 0, 0};
	unsigned char arr2[] = {0, 0, 42, 0, 0};

	test(memcmp("Abc", "Def", 0) == ft_memcmp("Abc", "Def", 0));
	test(memcmp("Abc", "Abd", 0) == ft_memcmp("Abc", "Abd", 0));
	test(memcmp("Abc", "Abd", 1) == ft_memcmp("Abc", "Abd", 1));
	test(memcmp("Abc", "Abd", 2) == ft_memcmp("Abc", "Abd", 2));
	test(memcmp("Abc", "Abd", 3) == ft_memcmp("Abc", "Abd", 3));
	test(memcmp("Abc", "Abd", 4) == ft_memcmp("Abc", "Abd", 4));
	test(memcmp("Abc", "Abd", 5) == ft_memcmp("Abc", "Abd", 5));
	test(ft_memcmp(arr1, arr2, 4) > 0);
}


void test_strnstr(void)
{
	test(strnstr("Foo Bar Baz", "", 7) == ft_strnstr("Foo Bar Baz", "", 7));
	test(strnstr("Foo Bar Baz", "Bar", 0) == ft_strnstr("Foo Bar Baz", "Bar", 0));
	test(strnstr("Foo Bar Baz", "Bar", 4) == ft_strnstr("Foo Bar Baz", "Bar", 4));
	test(strnstr("Foo Bar Baz", "Bar", 5) == ft_strnstr("Foo Bar Baz", "Bar", 5));
	test(strnstr("Foo Bar Baz", "Bar", 6) == ft_strnstr("Foo Bar Baz", "Bar", 6));
	test(strnstr("Foo Bar Baz", "Bar", 7) == ft_strnstr("Foo Bar Baz", "Bar", 7));
	test(strnstr("Foo Bar Baz", "Bol", 8) == ft_strnstr("Foo Bar Baz", "Bol", 8));
	test(strnstr("Foo Bar Baz", "Bol", 25) == ft_strnstr("Foo Bar Baz", "Bol", 25));
}


void test_atoi(void)
{
	test(atoi(" \f\n\r\t\v123") == ft_atoi(" \f\n\r\t\v123"));
	test(atoi(" \f\n\r\t\v100") == ft_atoi(" \f\n\r\t\v100"));
	test(atoi(" \f\n\r\t\v001") == ft_atoi(" \f\n\r\t\v001"));
	test(atoi(" \f\n\r\t\v+42") == ft_atoi(" \f\n\r\t\v+42"));
	test(atoi(" \f\n\r\t\v++42") == ft_atoi(" \f\n\r\t\v++42"));
	test(atoi(" \f\n\r\t\v-42") == ft_atoi(" \f\n\r\t\v-42"));
	test(atoi(" \f\n\r\t\v--42") == ft_atoi(" \f\n\r\t\v--42"));
	test(atoi("BRUH \f\n\r\t\v--42") == ft_atoi("BRUH \f\n\r\t\v--42"));
	test(atoi("0") == ft_atoi("0"));
	test(atoi("000") == ft_atoi("000"));
	test(atoi("42abc") == ft_atoi("42abc"));
	test(atoi("") == ft_atoi(""));
	test(atoi(" +2147483647") == ft_atoi(" +2147483647"));
	test(atoi(" -2147483648") == ft_atoi(" -2147483648"));
	test(atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234") == ft_atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234"));
	test(!ft_atoi(0));
}


void test_substr(void)
{
	test(strcmp(ft_substr("Hello World", 0, 0), "") == 0);
	test(strcmp(ft_substr("Hello World", 0, 1), "H") == 0);
	test(strcmp(ft_substr("Hello World", 0, 5), "Hello") == 0);
	test(strcmp(ft_substr("Hello World", 1, 15), "ello World") == 0);
	test(strcmp(ft_substr("Hello World", 11, 15), "") == 0);
	test(strcmp(ft_substr("Hello World", 13, 15), "") == 0);
	free(ft_substr("Hello World", 13, 15));
	test(strcmp(ft_substr("Hello World", 0, -1), "Hello World") == 0);
}


void test_strjoin(void)
{
	test(strcmp(ft_strjoin("Hello", "World"), "HelloWorld") == 0);
	test(strcmp(ft_strjoin("Hello", ""), "Hello") == 0);
	test(strcmp(ft_strjoin("", "World"), "World") == 0);
	test(strcmp(ft_strjoin("", ""), "") == 0);
	free(ft_strjoin("", ""));
}


void test_strtrim(void)
{
	test(strcmp(ft_strtrim("", ""), "") == 0);
	test(strcmp(ft_strtrim("", "\r\n"), "") == 0);
	test(strcmp(ft_strtrim("Hello", ""), "Hello") == 0);
	test(strcmp(ft_strtrim("  Hello  ", " "), "Hello") == 0);
	test(strcmp(ft_strtrim("\nHello\nWorld\n \n", " \n"), "Hello\nWorld") == 0);
	test(strcmp(ft_strtrim("     xxxxx  xxx", " x"), "") == 0);
	free(ft_strtrim("     xxxxx  xxx", " x"));
}


void print_split(char **tab)
{
	size_t i;

	printf("[");
	i = 0;
	while (tab[i])
	{
		printf("%s, ", tab[i]);
		i++;
	}
	printf("NULL]\n");
}

void test_split(void)
{
	print_split(ft_split("Hello World", ' '));
	print_split(ft_split(" Hello World ", ' '));
	print_split(ft_split(" \nHello\nWorld\n ", '\n'));
}


void test_itoa(void)
{
	test(strcmp(ft_itoa(0), "0") == 0);
	test(strcmp(ft_itoa(123), "123") == 0);
	test(strcmp(ft_itoa(-123), "-123") == 0);
	test(strcmp(ft_itoa(1000), "1000") == 0);
	test(strcmp(ft_itoa(2147483647), "2147483647") == 0);
	test(strcmp(ft_itoa(-2147483648), "-2147483648") == 0);
	free(ft_itoa(-2147483648));
}


char fn_strmapi(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (toupper(c));
	else
		return (tolower(c));
}

void test_strmapi(void)
{
	test(strcmp(ft_strmapi("BONJOUR", &fn_strmapi), "BoNjOuR") == 0);
	test(strcmp(ft_strmapi(" BONJOUR", &fn_strmapi), " bOnJoUr") == 0);
	free(ft_strmapi("BONJOUR", &fn_strmapi));
}


void fn_striteri(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = toupper(*c);
	else
		*c = tolower(*c);
}

void test_striteri(void)
{
	char str1[] = "BONJOUR";
	char str2[] = " BONJOUR";

	ft_striteri(str1, &fn_striteri);
	ft_striteri(str2, &fn_striteri);
	test(strcmp(str1, "BoNjOuR") == 0);
	test(strcmp(str2, " bOnJoUr") == 0);
}


void test_putchar_fd(void)
{
	ft_putchar_fd('O', 1);
	ft_putchar_fd('K', 1);
	ft_putchar_fd('\n', 1);
}


void test_putstr_fd(void)
{
	ft_putstr_fd("OK\n", 1);
}


void test_lstnew(void)
{
	char str[] = "Hello World";
	t_list *elem = ft_lstnew(str);
	test(strcmp(str, (*elem).content) == 0);
	test((*elem).next == 0);
}


void test_lstadd_front(void)
{
	char str1[] = "First";
	char str2[] = "New First";
	t_list *elem1 = ft_lstnew(str1);
	t_list **lst = &elem1;
	t_list *elem2 = ft_lstnew(str2);
	ft_lstadd_front(lst, elem2);
	test(strcmp(str2, (*lst)->content) == 0);
	test(strcmp(str1, ((*lst)->next)->content) == 0);
	test((*lst) == elem2);
}


void test_lstsize(void)
{
	char str1[] = "First";
	char str2[] = "New First";
	t_list *elem1 = ft_lstnew(str1);
	t_list **lst = &elem1;
	t_list *elem2 = ft_lstnew(str2);
	ft_lstadd_front(lst, elem2);
	test(ft_lstsize(0) == 0);
	test(ft_lstsize(*lst) == 2);
}


void test_lstlast(void)
{
	char str1[] = "First";
	char str2[] = "New First";
	t_list *elem1 = ft_lstnew(str1);
	t_list *elem2 = ft_lstnew(str2);
	elem2->next = elem1;
	test(ft_lstlast(0) == 0);
	test(ft_lstlast(elem2) == elem1);
}


void test_lstadd_back(void)
{
	char str1[] = "First";
	char str2[] = "Last";
	t_list *elem1 = ft_lstnew(str1);
	t_list **lst = &elem1;
	t_list *elem2 = ft_lstnew(str2);
	t_list *null_ptr = 0;
	ft_lstadd_back(lst, elem2);
	test(strcmp(str1, (*lst)->content) == 0);
	test(strcmp(str2, ((*lst)->next)->content) == 0);
	test((*lst) == elem1);
	ft_lstadd_back(&null_ptr, elem1);
}


void lstclear_del(void *ptr)
{
	free(ptr);
}

void test_lstclear(void)
{
	char *str1 = malloc(sizeof(char));
	str1[0] = '\0';
	char *str2 = malloc(sizeof(char));
	str2[0] = '\0';
	t_list *elem1 = ft_lstnew(str1);
	t_list *elem2 = ft_lstnew(str2);
	elem2->next = elem1;
	t_list **lst = &elem2;
	ft_lstclear(lst, &lstclear_del);
	printf("OK\n");
}


void lstiter_fn(void *ptr)
{
	printf("%s", (char *)ptr);
}

void test_lstiter(void)
{
	char str1[] = "O";
	char str2[] = "K";
	t_list *elem1 = ft_lstnew(str1);
	t_list *elem2 = ft_lstnew(str2);
	elem1->next = elem2;
	ft_lstiter(elem1, &lstiter_fn);
	printf("\n");
}


void *lstmap_fn(void *ptr)
{
	char *str;
	size_t i;

	str = strdup((char *)ptr);
	i = 0;
	while (str[i])
	{
		str[i] = toupper(str[i]);
		i++;
	}
	return str;
}

void test_lstmap(void)
{
	char *str1 = malloc(6 * sizeof(char));
	str1[0] = 'h';
	str1[1] = 'e';
	str1[2] = 'l';
	str1[3] = 'l';
	str1[4] = 'o';
	str1[5] = '\0';
	char *str2 = malloc(6 * sizeof(char));
	str2[0] = 'w';
	str2[1] = 'o';
	str2[2] = 'r';
	str2[3] = 'l';
	str2[4] = 'd';
	str2[5] = '\0';
	t_list *elem1 = ft_lstnew(str1);
	t_list *elem2 = ft_lstnew(str2);
	elem1->next = elem2;
	t_list *lst = ft_lstmap(elem1, &lstmap_fn, &lstclear_del);
	test(strcmp(lst->content, "HELLO") == 0);
	// printf("%p\n", lst->next);
	test(strcmp((*(lst->next)).content, "WORLD") == 0);
}


int	main(void)
{
	printf("===isascii===\n");
	test_isascii();
	printf("\n");
	printf("===isprint===\n");
	test_isprint();
	printf("\n");
	printf("===bzero===\n");
	test_bzero();
	printf("\n");
	printf("===memcpy===\n");
	test_memcpy_1();
	// Undefined behaviors
	// test_memcpy_2();
	// test_memcpy_3();
	printf("\n");
	printf("===memmove===\n");
	test_memmove_1();
	test_memmove_2();
	test_memmove_3();
	printf("\n");
	printf("===strlcpy===\n");
	test_strlcpy_1();
	test_strlcpy_2();
	test_strlcpy_3();
	test_strlcpy_4();
	test_strlcpy_5();
	test_strlcpy_6();
	printf("\n");
	printf("===strlcat===\n");
	test_strlcat_1();
	test_strlcat_2();
	test_strlcat_3();
	test_strlcat_4();
	printf("\n");
	printf("===toupper===\n");
	test_toupper();
	printf("\n");
	printf("===tolower===\n");
	test_tolower();
	printf("\n");
	printf("===strchr===\n");
	test_strchr();
	printf("\n");
	printf("===strrchr===\n");
	test_strrchr();
	printf("\n");
	printf("===strncmp===\n");
	test_strncmp();
	printf("\n");
	printf("===memchr===\n");
	test_memchr();
	printf("\n");
	printf("===memcmp===\n");
	test_memcmp();
	printf("\n");
	printf("===strnstr===\n");
	test_strnstr();
	printf("\n");
	printf("===atoi===\n");
	test_atoi();
	printf("\n");
	printf("===substr===\n");
	test_substr();
	printf("\n");
	printf("===strjoin===\n");
	test_strjoin();
	printf("\n");
	printf("===strtrim===\n");
	test_strtrim();
	printf("\n");
	printf("===split===\n");
	test_split();
	printf("\n");
	printf("===itoa===\n");
	test_itoa();
	printf("\n");
	printf("===strmapi===\n");
	test_strmapi();
	printf("\n");
	printf("===striteri===\n");
	test_striteri();
	printf("\n");
	printf("===putchar_fd===\n");
	test_putchar_fd();
	printf("\n");
	printf("===putstr_fd===\n");
	test_putstr_fd();
	printf("\n");
	printf("===lstnew===\n");
	test_lstnew();
	printf("\n");
	printf("===lstadd_front===\n");
	test_lstadd_front();
	printf("\n");
	printf("===lstsize===\n");
	test_lstsize();
	printf("\n");
	printf("===lstlast===\n");
	test_lstlast();
	printf("\n");
	printf("===lstadd_back===\n");
	test_lstadd_back();
	printf("\n");
	printf("===lstclear===\n");
	test_lstclear();
	printf("\n");
	printf("===lstiter===\n");
	test_lstiter();
	printf("\n");
	printf("===lstmap===\n");
	test_lstmap();
	printf("\n");
	return (0);
}
