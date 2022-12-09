/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaassila <yaassila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:57:30 by yaassila          #+#    #+#             */
/*   Updated: 2022/12/10 00:11:56 by yaassila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tester.h"
#include <bsd/string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#pragma region Utils

char	**make_string_array(int num_strings, ...)
{
	va_list		args;
	char		**array;
	const char	*str;
	int			i;

	va_start(args, num_strings);
	array = malloc((num_strings + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < num_strings)
	{
		str = va_arg(args, const char *);
		array[i] = strdup(str);
		if (!array[i])
			return (NULL);
		i++;
	}
	array[num_strings] = NULL;
	va_end(args);
	return (array);
}

int	compare_string_arrays(char **arr1, char **arr2)
{
	int	i;
	int	result;

	i = 0;
	while (arr1[i] != NULL && arr2[i] != NULL)
	{
		result = strcmp(arr1[i], arr2[i]);
		if (result != 0)
			return (result); // Not equal
		i++;
	}
	// Return 0 if both arrays are terminated by a NULL value
	if (arr1[i] == NULL && arr2[i] == NULL)
		return (0);
	// Return a negative number if arr1 is shorter than arr2
	if (arr1[i] == NULL)
		return (-1);
	// Return a positive number if arr1 is longer than arr2
	return (1);
}

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(t_list *list)
{
	t_list	*next;

	while (list != NULL)
	{
		free(list->content);
		next = list->next;
		free(list);
		list = next;
	}
}

void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_list	*create_list(int count, ...)
{
	t_list	*head;
	t_list	*last;
	va_list	args;
	int		i;
	t_list	*elem;

	head = NULL;
	last = NULL;
	i = 0;
	va_start(args, count);
	while (i < count)
	{
		elem = malloc(sizeof(t_list));
		if (!elem)
			return (NULL);
		elem->content = va_arg(args, void *);
		elem->next = NULL;
		if (head == NULL)
			head = elem;
		else
			last->next = elem;
		last = elem;
		i++;
	}
	va_end(args);
	return (head);
}

char	fn_strmapi(unsigned int i, char c)
{
	// Spongebob case
	if (i % 2 == 0)
		return (toupper(c));
	else
		return (tolower(c));
}

void	fn_striteri(unsigned int i, char *c)
{
	// Spongebob case
	if (i % 2 == 0)
		*c = toupper(*c);
	else
		*c = tolower(*c);
}

void	fn_lstiter(void *ptr)
{
	char	*str;
	size_t	i;

	str = ptr;
	i = 0;
	while (str[i])
	{
		str[i] = toupper(str[i]);
		i++;
	}
}

void	*fn_lstmap(void *ptr)
{
	char	*str;
	size_t	i;

	str = strdup((char *)ptr);
	i = 0;
	while (str[i])
	{
		str[i] = toupper(str[i]);
		i++;
	}
	return (str);
}

#pragma endregion

TESTER("yaassila's libft tester", {
	group("ft_isascii", {
		test(isascii(32) == ft_isascii(32));
		test(isascii(0) == ft_isascii(0));
		test(isascii(-1) == ft_isascii(-1));
		test(isascii(256) == ft_isascii(256));
		test(isascii(255) == ft_isascii(255));
		test(isascii(128) == ft_isascii(128));
		test(isascii(127) == ft_isascii(127));
		test(isascii(300) == ft_isascii(300));
	});
	group("ft_isprint", {
		test(ft_isprint(33) > 0);
		test(ft_isprint(32) > 0);
		test(isprint(31) == ft_isprint(31));
		test(isprint(0) == ft_isprint(0));
		test(isprint(-1) == ft_isprint(-1));
		test(ft_isprint(126) > 0);
		test(isprint(127) == ft_isprint(127));
		test(isprint(128) == ft_isprint(128));
		test(isprint(300) == ft_isprint(300));
	});
	group("ft_bzero", {
		unsigned char tmp[100];
		memset(tmp, 'A', 100);
		ft_bzero(tmp, 42);
		test(tmp[0] == '\0');
		test(tmp[41] == '\0');
		test(tmp[42] == 'A');
	});
	group("ft_memcpy", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];

		memcpy(dest, src, 12);
		ft_memcpy(ft_dest, ft_src, 12);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_memmove_1", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];

		memmove(dest, src, 12);
		ft_memmove(ft_dest, ft_src, 12);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_memmove_2", {
		char src[] = "Hello World";
		char ft_src[] = "Hello World";

		memmove(src + 2, src, 5);
		ft_memmove(ft_src + 2, ft_src, 5);

		test(strcmp(src + 2, ft_src + 2) == 0);
	});
	group("ft_memmove_3", {
		char dest[] = "Hello World";
		char ft_dest[] = "Hello World";

		memmove(dest, dest + 4, 5);
		ft_memmove(ft_dest, ft_dest + 4, 5);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_strlcpy_1", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];

		strlcpy(dest, src, 12);
		ft_strlcpy(ft_dest, ft_src, 12);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_strlcpy_2", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];

		strlcpy(dest, src, 6);
		ft_strlcpy(ft_dest, ft_src, 6);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_strlcpy_3", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];
		size_t res;
		size_t ft_res;

		res = strlcpy(dest, src, 6);
		ft_res = ft_strlcpy(ft_dest, ft_src, 6);

		test(res == ft_res);
	});
	group("ft_strlcpy_4", {
		char src[] = "Hello World\0";
		char dest[12];
		char ft_src[] = "Hello World\0";
		char ft_dest[12];
		size_t res;
		size_t ft_res;

		res = strlcpy(dest, src, 0);
		ft_res = ft_strlcpy(ft_dest, ft_src, 0);

		test(res == ft_res);
	});
	group("ft_strlcpy_5", {
		char src[] = "Hello\0World\0";
		char dest[12];
		char ft_src[] = "Hello\0World\0";
		char ft_dest[12];

		strlcpy(dest, src, 12);
		ft_strlcpy(ft_dest, ft_src, 12);

		test(!memcmp(dest, ft_dest, 12));
	});
	group("ft_strlcpy_6", {
		char src[] = "Hello\0World\0";
		char dest[12];
		char ft_src[] = "Hello\0World\0";
		char ft_dest[12];

		test(strlcpy(dest, src, -1) == ft_strlcpy(ft_dest, ft_src, -1));
	});
	group("ft_strlcat_1", {
		char src[] = "Hello World\0";
		char dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		char ft_src[] = "Hello World\0";
		char ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";

		strlcat(dest, src, 12);
		ft_strlcat(ft_dest, ft_src, 12);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_strlcat_2", {
		char src[] = "Hello World\0";
		char dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		char ft_src[] = "Hello World\0";
		char ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";

		strlcat(dest, src, 6);
		ft_strlcat(ft_dest, ft_src, 6);

		test(strcmp(dest, ft_dest) == 0);
	});
	group("ft_strlcat_3", {
		char src[] = "Hello World\0";
		char dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		char ft_src[] = "Hello World\0";
		char ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		size_t res;
		size_t ft_res;

		res = strlcat(dest, src, 6);
		ft_res = ft_strlcat(ft_dest, ft_src, 6);

		test(res == ft_res);
	});
	group("ft_strlcat_4", {
		char src[] = "Hello World\0";
		char dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		char ft_src[] = "Hello World\0";
		char ft_dest[] = "-> \0\0\0\0\0\0\0\0\0\0\0\0";
		size_t res;
		size_t ft_res;

		res = strlcat(dest, src, 0);
		ft_res = ft_strlcat(ft_dest, ft_src, 0);

		test(res == ft_res);
	});
	group("ft_toupper", {
		test(ft_toupper('a') == 'A');
		test(ft_toupper('p') == 'P');
		test(ft_toupper('z') == 'Z');
		test(ft_toupper('V') == 'V');
		test(ft_toupper('&') == '&');
		test(toupper('p' + 256) == ft_toupper('p' + 256));
	});
	group("ft_tolower", {
		test(ft_tolower('A') == 'a');
		test(ft_tolower('P') == 'p');
		test(ft_tolower('Z') == 'z');
		test(ft_tolower('v') == 'v');
		test(ft_tolower('&') == '&');
		test(toupper('P' + 256) == ft_toupper('P' + 256));
	});
	group("ft_strchr", {
		test(strchr("Aecde", 'A') == ft_strchr("Aecde", 'A'));
		test(strchr("Aecde", 'c') == ft_strchr("Aecde", 'c'));
		test(strchr("Aecde", 'e') == ft_strchr("Aecde", 'e'));
		test(strchr("Aecde", '\0') == ft_strchr("Aecde", '\0'));
		test(strchr("Aecde", 'f') == ft_strchr("Aecde", 'f'));
	});
	group("ft_strrchr", {
		test(strrchr("Aecde", 'A') == ft_strrchr("Aecde", 'A'));
		test(strrchr("Aecde", 'c') == ft_strrchr("Aecde", 'c'));
		test(strrchr("Aecde", 'e') == ft_strrchr("Aecde", 'e'));
		test(strrchr("Aecde", '\0') == ft_strrchr("Aecde", '\0'));
		test(strrchr("Aecde", 'f') == ft_strrchr("Aecde", 'f'));
	});
	group("ft_strncmp", {
		test(strncmp("Abc", "Def", 0) == ft_strncmp("Abc", "Def", 0));
		test(strncmp("Abc", "Abd", 0) == ft_strncmp("Abc", "Abd", 0));
		test(strncmp("Abc", "Abd", 1) == ft_strncmp("Abc", "Abd", 1));
		test(strncmp("Abc", "Abd", 2) == ft_strncmp("Abc", "Abd", 2));
		test(strncmp("Abc", "Abd", 3) == ft_strncmp("Abc", "Abd", 3));
		test(strncmp("Abc", "Abd", 4) == ft_strncmp("Abc", "Abd", 4));
		test(strncmp("Abc", "Abd", 5) == ft_strncmp("Abc", "Abd", 5));
	});
	group("ft_memchr", {
		test(memchr("Aecde", 'A', 5) == ft_memchr("Aecde", 'A', 5));
		test(memchr("Aecde", 'c', 5) == ft_memchr("Aecde", 'c', 5));
		test(memchr("Aecde", 'e', 5) == ft_memchr("Aecde", 'e', 5));
		test(memchr("Aecde", '\0', 5) == ft_memchr("Aecde", '\0', 5));
		test(memchr("Aecde", 'f', 5) == ft_memchr("Aecde", 'f', 5));
	});
	group("ft_memcmp", {
		unsigned char arr1[] = "\0\0\127\0\0";
		unsigned char arr2[] = "\0\0\42\0\0";

		test(memcmp("Abc", "Def", 0) == ft_memcmp("Abc", "Def", 0));
		test(memcmp("Abc", "Abd", 0) == ft_memcmp("Abc", "Abd", 0));
		test(memcmp("Abc", "Abd", 1) == ft_memcmp("Abc", "Abd", 1));
		test(memcmp("Abc", "Abd", 2) == ft_memcmp("Abc", "Abd", 2));
		test(memcmp("Abc", "Abd", 3) == ft_memcmp("Abc", "Abd", 3));
		test(memcmp("Abc", "Abd", 4) == ft_memcmp("Abc", "Abd", 4));
		test(memcmp("Abc", "Abd", 5) == ft_memcmp("Abc", "Abd", 5));
		test(ft_memcmp(arr1, arr2, 4) > 0);
	});
	group("ft_strnstr", {
		test(strnstr("Foo Bar Baz", "", 7) == ft_strnstr("Foo Bar Baz", "", 7));
		test(strnstr("Foo Bar Baz", "Bar", 0) == ft_strnstr("Foo Bar Baz",
					"Bar", 0));
		test(strnstr("Foo Bar Baz", "Bar", 4) == ft_strnstr("Foo Bar Baz",
					"Bar", 4));
		test(strnstr("Foo Bar Baz", "Bar", 5) == ft_strnstr("Foo Bar Baz",
					"Bar", 5));
		test(strnstr("Foo Bar Baz", "Bar", 6) == ft_strnstr("Foo Bar Baz",
					"Bar", 6));
		test(strnstr("Foo Bar Baz", "Bar", 7) == ft_strnstr("Foo Bar Baz",
					"Bar", 7));
		test(strnstr("Foo Bar Baz", "Bol", 8) == ft_strnstr("Foo Bar Baz",
					"Bol", 8));
		test(strnstr("Foo Bar Baz", "Bol", 25) == ft_strnstr("Foo Bar Baz",
					"Bol", 25));
	});
	group("ft_atoi", {
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
		// test(!ft_atoi(0));
	});
	group("ft_substr", {
		char *res;

		// Test 1
		res = ft_substr("Hello World", 0, 0);
		test(strcmp(res, "") == 0);
		free(res);
		// Test 2
		res = ft_substr("Hello World", 0, 1);
		test(strcmp(res, "H") == 0);
		free(res);
		// Test 3
		res = ft_substr("Hello World", 0, 5);
		test(strcmp(res, "Hello") == 0);
		free(res);
		// Test 4
		res = ft_substr("Hello World", 1, 15);
		test(strcmp(res, "ello World") == 0);
		free(res);
		// Test 5
		res = ft_substr("Hello World", 11, 15);
		test(strcmp(res, "") == 0);
		free(res);
		// Test 6
		res = ft_substr("Hello World", 13, 15);
		test(strcmp(res, "") == 0);
		free(res);
		// Test 7
		// res = ft_substr("Hello World", 0, -1);
		// test(strcmp(res, "Hello World") == 0);
		// free(res);
	});
	group("ft_strjoin", {
		char *res;

		// Test 1
		res = ft_strjoin("Hello", "World");
		test(strcmp(res, "HelloWorld") == 0);
		free(res);
		// Test 2
		res = ft_strjoin("Hello", "");
		test(strcmp(res, "Hello") == 0);
		free(res);
		// Test 3
		res = ft_strjoin("", "World");
		test(strcmp(res, "World") == 0);
		free(res);
		// Test 4
		res = ft_strjoin("", "");
		test(strcmp(res, "") == 0);
		free(res);
	});
	group("ft_strtrim", {
		char *res;

		// Test 1
		res = ft_strtrim("", "");
		test(strcmp(res, "") == 0);
		free(res);
		// Test 2
		res = ft_strtrim("", "\r\n");
		test(strcmp(res, "") == 0);
		free(res);
		// Test 3
		res = ft_strtrim("Hello", "");
		test(strcmp(res, "Hello") == 0);
		free(res);
		// Test 4
		res = ft_strtrim("  Hello  ", " ");
		test(strcmp(res, "Hello") == 0);
		free(res);
		// Test 5
		res = ft_strtrim("\nHello\nWorld\n \n", " \n");
		test(strcmp(res, "Hello\nWorld") == 0);
		free(res);
		// Test 6
		res = ft_strtrim("     xxxxx  xxx", " x");
		test(strcmp(res, "") == 0);
		free(res);
	});
	group("ft_split", {
		char **arr;
		char **res;

		arr = make_string_array(2, "Hello", "World");
		// Test 1
		res = ft_split("Hello World", ' ');
		test(compare_string_arrays(res, arr) == 0);
		free_string_array(res);
		// Test 2
		res = ft_split("Hello   World", ' ');
		test(compare_string_arrays(res, arr) == 0);
		free_string_array(res);
		// Test 3
		res = ft_split("  Hello  World  ", ' ');
		test(compare_string_arrays(res, arr) == 0);
		free_string_array(res);
		free_string_array(arr);

		arr = make_string_array(1, "HelloWorld");
		// Test 4
		res = ft_split("  HelloWorld  ", ' ');
		test(compare_string_arrays(res, arr) == 0);
		free_string_array(res);
		free_string_array(arr);

		arr = make_string_array(0);
		// Test 5
		res = ft_split("", '\0');
		test(compare_string_arrays(res, arr) == 0);
		free_string_array(res);
		free_string_array(arr);
	});
	group("ft_itoa", {
		char *res;

		// Test 1
		res = ft_itoa(0);
		test(strcmp(res, "0") == 0);
		free(res);
		// Test 2
		res = ft_itoa(123);
		test(strcmp(res, "123") == 0);
		free(res);
		// Test 3
		res = ft_itoa(-123);
		test(strcmp(res, "-123") == 0);
		free(res);
		// Test 4
		res = ft_itoa(1000);
		test(strcmp(res, "1000") == 0);
		free(res);
		// Test 5
		res = ft_itoa(2147483647);
		test(strcmp(res, "2147483647") == 0);
		free(res);
		// Test 6
		res = ft_itoa(-2147483648);
		test(strcmp(res, "-2147483648") == 0);
		free(res);
	});
	group("ft_strmapi", {
		char *res;

		// Test 1
		res = ft_strmapi("Bonjour", &fn_strmapi);
		test(strcmp(res, "BoNjOuR") == 0);
		free(res);
		// Test 2
		res = ft_strmapi(" Bonjour", &fn_strmapi);
		test(strcmp(res, " bOnJoUr") == 0);
		free(res);
	});
	group("ft_striteri", {
		char str1[] = "Bonjour";
		char str2[] = " Bonjour";

		ft_striteri(str1, &fn_striteri);
		ft_striteri(str2, &fn_striteri);

		test(strcmp(str1, "BoNjOuR") == 0);
		test(strcmp(str2, " bOnJoUr") == 0);
	});
	group("ft_putchar_fd", {
		// Create a temporary pipe
		int pipefd[2];
		pipe(pipefd);

		// Save the original standard output file descriptor
		int stdout_copy = dup(1);

		// Redirect standard output to the temporary pipe
		dup2(pipefd[1], 1);

		// Write to standard output using ft_putchar_fd()
		char c = 'C';
		ft_putchar_fd(c, 1);

		// Close the write end of the pipe
		close(pipefd[1]);

		// Read from the temporary pipe using read()
		char buffer[10];
		int bytes_read = read(pipefd[0], buffer, 1);

		// Restore the original standard output file descriptor
		dup2(stdout_copy, 1);
		close(stdout_copy);

		// Clean up
		close(pipefd[0]);

		// Check if the number of bytes read matches the length of the char
		test(bytes_read == 1);

		// Compare the read data with the char
		test(buffer[0] == c);
	});
	group("ft_putstr_fd", {
		// Create a temporary pipe
		int pipefd[2];
		pipe(pipefd);

		// Save the original standard output file descriptor
		int stdout_copy = dup(1);

		// Redirect standard output to the temporary pipe
		dup2(pipefd[1], 1);

		// Write to standard output using ft_putstr_fd()
		char str[] = "Hello, world!\n";
		ft_putstr_fd(str, 1);

		// Close the write end of the pipe
		close(pipefd[1]);

		// Read from the temporary pipe using read()
		char buffer[100];
		int bytes_read = read(pipefd[0], buffer, strlen(str));

		// Restore the original standard output file descriptor
		dup2(stdout_copy, 1);
		close(stdout_copy);

		// Clean up
		close(pipefd[0]);

		// Check if the number of bytes read matches the length of the string
		test(bytes_read == strlen(str));

		// Compare the read data with the string, up to the number of bytes read
		test(strncmp(buffer, str, bytes_read) == 0);
	});
	group("ft_lstnew", {
		char str[] = "Elem";
		t_list *elem = ft_lstnew(str);

		test(strcmp(str, elem->content) == 0);
		test(elem->next == NULL);

		free(elem);
	});
	group("ft_lstadd_front", {
		char str1[] = "First";
		char str2[] = "New First";
		t_list *elem1 = ft_lstnew(str1);
		t_list **lst = &elem1;
		t_list *elem2 = ft_lstnew(str2);
		ft_lstadd_front(lst, elem2);
		test(strcmp(str2, (*lst)->content) == 0);
		test(strcmp(str1, ((*lst)->next)->content) == 0);
		test((*lst) == elem2);
		free((*lst)->next);
		free(*lst);
	});
	group("ft_lstsize", {
		char str1[] = "First";
		char str2[] = "New First";
		t_list *elem1 = ft_lstnew(str1);
		t_list **lst = &elem1;
		t_list *elem2 = ft_lstnew(str2);
		ft_lstadd_front(lst, elem2);
		test(ft_lstsize(0) == 0);
		test(ft_lstsize(*lst) == 2);
		free((*lst)->next);
		free(*lst);
	});
	group("ft_lstlast", {
		char str1[] = "First";
		char str2[] = "New First";
		t_list *elem1 = ft_lstnew(str1);
		t_list *elem2 = ft_lstnew(str2);
		elem2->next = elem1;
		test(ft_lstlast(0) == 0);
		test(ft_lstlast(elem2) == elem1);
		free(elem1);
		free(elem2);
	});
	group("ft_lstadd_back", {
		char str1[] = "First";
		char str2[] = "Last";
		t_list *elem1 = ft_lstnew(str1);
		t_list **lst = &elem1;
		t_list *elem2 = ft_lstnew(str2);
		t_list *null_ptr = NULL;
		ft_lstadd_back(lst, elem2);
		test(strcmp(str1, (*lst)->content) == 0);
		test(strcmp(str2, ((*lst)->next)->content) == 0);
		test((*lst) == elem1);
		ft_lstadd_back(&null_ptr, elem1);
		free(elem1);
		free(elem2);
	});
	group("ft_lstclear", {
		t_list *lst = create_list(2, strdup(""), strdup(""));
		ft_lstclear(&lst, &free);
		printf("Please use `valgrind` to check for any memory leaks.\n");
	});
	group("ft_lstiter", {
		t_list *lst = create_list(2, strdup("First"), strdup("Last"));
		t_list *elem1 = lst;
		t_list *elem2 = lst->next;
		ft_lstiter(lst, &fn_lstiter);

		test(strcmp(elem1->content, "FIRST") == 0);
		test(strcmp(elem2->content, "LAST") == 0);

		free_list(lst);
	});
	group("ft_lstmap", {
		t_list *lst = create_list(2, strdup("First"), strdup("Last"));
		t_list *mapped_lst = ft_lstmap(lst, &fn_lstmap, &free);
		t_list *mapped_elem1 = mapped_lst;
		t_list *mapped_elem2 = mapped_lst->next;

		test(strcmp(mapped_elem1->content, "FIRST") == 0);
		test(strcmp(mapped_elem2->content, "LAST") == 0);

		free_list(lst);
		free_list(mapped_lst);
	});
});
