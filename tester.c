/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaassila <yaassila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:00:00 by yaassila          #+#    #+#             */
/*   Updated: 2023/09/20 16:00:00 by yaassila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "tester.h"
#include <bsd/string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#pragma region Integer Utils

int	sign(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

#pragma endregion

#pragma region String Utils

int	ft_putchar_fd_output_matches(char c, int fd)
{
	int		pipefd[2];
	int		fd_copy;
	char	output[BUFSIZ];
	ssize_t	bytes_read;

	// Create a temporary pipe
	pipe(pipefd);
	// Save the original fd
	fd_copy = dup(fd);
	// Redirect fd to the temporary pipe
	dup2(pipefd[1], fd);
	// Write to fd using ft_putchar_fd()
	ft_putchar_fd(c, fd);
	// Close the write end of the pipe
	close(pipefd[1]);
	// Read from the temporary pipe using read()
	bytes_read = read(pipefd[0], output, 1);
	// Restore the original fd
	dup2(fd_copy, fd);
	close(fd_copy);
	// Clean up
	close(pipefd[0]);
	return ((bytes_read == 1) && (strncmp(output, &c, bytes_read) == 0));
}

int	ft_putstr_fd_output_matches(char *str, int fd)
{
	int		pipefd[2];
	int		fd_copy;
	char	output[BUFSIZ];
	ssize_t	bytes_read;

	// Create a temporary pipe
	pipe(pipefd);
	// Save the original fd
	fd_copy = dup(fd);
	// Redirect fd to the temporary pipe
	dup2(pipefd[1], fd);
	// Write to fd using ft_putstr_fd()
	ft_putstr_fd(str, fd);
	// Close the write end of the pipe
	close(pipefd[1]);
	// Read from the temporary pipe using read()
	bytes_read = read(pipefd[0], output, strlen(str));
	// Restore the original fd
	dup2(fd_copy, fd);
	close(fd_copy);
	// Clean up
	close(pipefd[0]);
	return ((bytes_read == (ssize_t)strlen(str)) && (strncmp(output, str,
				bytes_read) == 0));
}

#pragma endregion

#pragma region Array Utils

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

#pragma endregion

#pragma region List Utils

t_list	*lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
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
		elem = lstnew(va_arg(args, void *));
		if (!elem)
			return (NULL);
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

#pragma endregion

#pragma region Handlers

char	tospongebob_strmapi(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (toupper(c));
	else
		return (tolower(c));
}

void	tospongebob_striteri(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = toupper(*c);
	else
		*c = tolower(*c);
}

void	toupper_lstiter(void *ptr)
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

void	*toupper_lstmap(void *ptr)
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
		test(sign(isascii(32)) == sign(ft_isascii(32)));
		test(sign(isascii(0)) == sign(ft_isascii(0)));
		test(sign(isascii(-1)) == sign(ft_isascii(-1)));
		test(sign(isascii(127)) == sign(ft_isascii(127)));
		test(sign(isascii(128)) == sign(ft_isascii(128)));
		test(sign(isascii(300)) == sign(ft_isascii(300)));
	});
	group("ft_isprint", {
		test(sign(isprint(33)) == sign(ft_isprint(33)));
		test(sign(isprint(32)) == sign(ft_isprint(32)));
		test(sign(isprint(31)) == sign(ft_isprint(31)));
		test(sign(isprint(0)) == sign(ft_isprint(0)));
		test(sign(isprint(-1)) == sign(ft_isprint(-1)));
		test(sign(isprint(126)) == sign(ft_isprint(126)));
		test(sign(isprint(127)) == sign(ft_isprint(127)));
		test(sign(isprint(128)) == sign(ft_isprint(128)));
		test(sign(isprint(300)) == sign(ft_isprint(300)));
	});
	group("ft_bzero", {
		unsigned char tmp[100];
		memset(tmp, '*', 100);

		ft_bzero(tmp, 42);

		test(tmp[0] == '\0');
		test(tmp[19] == '\0');
		test(tmp[41] == '\0');
		test(tmp[42] == '*');
		test(tmp[43] == '*');
		test(tmp[99] == '*');
	});
	group("ft_memcpy", {
		char src[] = "Hello World";
		char dest[12] = {0};
		char ft_src[] = "Hello World";
		char ft_dest[12] = {0};

		memcpy(dest, src, 12);
		ft_memcpy(ft_dest, ft_src, 12);

		test(memcmp(dest, ft_dest, 12) == 0);
	});
	group("ft_memmove (No Overlap)", {
		char src[] = "Hello World";
		char dest[12] = {0};
		char ft_src[] = "Hello World";
		char ft_dest[12] = {0};

		memmove(dest, src, 12);
		ft_memmove(ft_dest, ft_src, 12);

		test(memcmp(dest, ft_dest, 12) == 0);
	});
	group("ft_memmove (Overlap Right)", {
		char src[] = "Hello World";
		char ft_src[] = "Hello World";

		memmove(src + 2, src, 5);
		ft_memmove(ft_src + 2, ft_src, 5);

		test(memcmp(src, ft_src, 12) == 0);
	});
	group("ft_memmove (Overlap Left)", {
		char dest[] = "Hello World";
		char ft_dest[] = "Hello World";

		memmove(dest, dest + 4, 5);
		ft_memmove(ft_dest, ft_dest + 4, 5);

		test(memcmp(dest, ft_dest, 12) == 0);
	});
	group("ft_strlcpy (Full)", {
		char src[] = "Hello World";
		char dest[12] = {0};
		char ft_src[] = "Hello World";
		char ft_dest[12] = {0};

		size_t res = strlcpy(dest, src, 12);
		size_t ft_res = ft_strlcpy(ft_dest, ft_src, 12);

		test(memcmp(dest, ft_dest, 12) == 0);
		test(res == ft_res);
	});
	group("ft_strlcpy (Partial)", {
		char src[] = "Hello World";
		char dest[12] = {0};
		char ft_src[] = "Hello World";
		char ft_dest[12] = {0};

		size_t res = strlcpy(dest, src, 6);
		size_t ft_res = ft_strlcpy(ft_dest, ft_src, 6);

		test(memcmp(dest, ft_dest, 12) == 0);
		test(res == ft_res);
	});
	group("ft_strlcpy (Empty)", {
		char src[] = "Hello World";
		char dest[12] = {0};
		char ft_src[] = "Hello World";
		char ft_dest[12] = {0};

		size_t res = strlcpy(dest, src, 0);
		size_t ft_res = ft_strlcpy(ft_dest, ft_src, 0);

		test(memcmp(dest, ft_dest, 12) == 0);
		test(res == ft_res);
	});
	group("ft_strlcpy (Negative Size)", {
		char src[] = "Hello\0World";
		char dest[12] = {0};
		char ft_src[] = "Hello\0World";
		char ft_dest[12] = {0};

		size_t res = strlcpy(dest, src, -1);
		size_t ft_res = ft_strlcpy(ft_dest, ft_src, -1);

		test(memcmp(dest, ft_dest, 12) == 0);
		test(res == ft_res);
	});
	group("ft_strlcpy (Null Byte)", {
		char src[] = "Hello\0World";
		char dest[12] = {0};
		char ft_src[] = "Hello\0World";
		char ft_dest[12] = {0};

		size_t res = strlcpy(dest, src, 12);
		size_t ft_res = ft_strlcpy(ft_dest, ft_src, 12);

		test(memcmp(dest, ft_dest, 12) == 0);
		test(res == ft_res);
	});
	group("ft_strlcat (Full)", {
		char src[] = "World";
		char dest[12] = "Hello ";
		char ft_src[] = "World";
		char ft_dest[12] = "Hello ";

		size_t res = strlcat(dest, src, 12);
		size_t ft_res = ft_strlcat(ft_dest, ft_src, 12);

		test(strcmp(dest, ft_dest) == 0);
		test(res == ft_res);
	});
	group("ft_strlcat (Full More)", {
		char src[] = "World";
		char dest[12] = "Hello ";
		char ft_src[] = "World";
		char ft_dest[12] = "Hello ";

		size_t res = strlcat(dest, src, 42);
		size_t ft_res = ft_strlcat(ft_dest, ft_src, 42);

		test(strcmp(dest, ft_dest) == 0);
		test(res == ft_res);
	});
	group("ft_strlcat (Partial)", {
		char src[] = "lo World";
		char dest[12] = "Hel";
		char ft_src[] = "lo World";
		char ft_dest[12] = "Hel";

		size_t res = strlcat(dest, src, 6);
		size_t ft_res = ft_strlcat(ft_dest, ft_src, 6);

		test(strcmp(dest, ft_dest) == 0);
		test(res == ft_res);
	});
	group("ft_strlcat (Empty)", {
		char src[] = "lo World";
		char dest[12] = "Hel";
		char ft_src[] = "lo World";
		char ft_dest[12] = "Hel";

		size_t res = strlcat(dest, src, 0);
		size_t ft_res = ft_strlcat(ft_dest, ft_src, 0);

		test(strcmp(dest, ft_dest) == 0);
		test(res == ft_res);
	});
	group("ft_strlcat (Negative Size)", {
		char src[] = "World";
		char dest[12] = "Hello ";
		char ft_src[] = "World";
		char ft_dest[12] = "Hello ";

		size_t res = strlcat(dest, src, -1);
		size_t ft_res = ft_strlcat(ft_dest, ft_src, -1);

		test(strcmp(dest, ft_dest) == 0);
		test(res == ft_res);
	});
	group("ft_toupper", {
		test(toupper('A') == ft_toupper('A'));
		test(toupper('b') == ft_toupper('b'));
		test(toupper('c') == ft_toupper('c'));
		test(toupper('!') == ft_toupper('!'));
		test(toupper('A' + 256) == ft_toupper('A' + 256));
		test(toupper('\0') == ft_toupper('\0'));
	});
	group("ft_tolower", {
		test(tolower('A') == ft_tolower('A'));
		test(tolower('b') == ft_tolower('b'));
		test(tolower('c') == ft_tolower('c'));
		test(tolower('!') == ft_tolower('!'));
		test(tolower('A' + 256) == ft_tolower('A' + 256));
		test(tolower('\0') == ft_tolower('\0'));
	});
	group("ft_strchr", {
		char str[] = "Abba";

		test(strchr(str, 'A') == ft_strchr(str, 'A'));
		test(strchr(str, 'b') == ft_strchr(str, 'b'));
		test(strchr(str, 'a') == ft_strchr(str, 'a'));
		test(strchr(str, '\0') == ft_strchr(str, '\0'));
		test(strchr(str, 'd') == ft_strchr(str, 'd'));
		test(strchr("\0\0\127\0\0", '\127') == ft_strchr("\0\0\127\0\0",
				'\127'));
	});
	group("ft_strrchr", {
		char str[] = "Abba";

		test(strrchr(str, 'A') == ft_strrchr(str, 'A'));
		test(strrchr(str, 'b') == ft_strrchr(str, 'b'));
		test(strrchr(str, 'a') == ft_strrchr(str, 'a'));
		test(strrchr(str, '\0') == ft_strrchr(str, '\0'));
		test(strrchr(str, 'd') == ft_strrchr(str, 'd'));
		test(strrchr("\0\0\127\0\0", '\127') == ft_strrchr("\0\0\127\0\0",
				'\127'));
	});
	group("ft_strncmp", {
		char str1[] = "Abc";
		char str2[] = "Abd";

		test(strncmp(str1, "Def", 0) == ft_strncmp(str1, "Def", 0));
		test(strncmp(str1, str2, 0) == ft_strncmp(str1, str2, 0));
		test(strncmp(str1, str2, 1) == ft_strncmp(str1, str2, 1));
		test(strncmp(str1, str2, 2) == ft_strncmp(str1, str2, 2));
		test(strncmp(str1, str2, 3) == ft_strncmp(str1, str2, 3));
		test(strncmp(str1, str2, 4) == ft_strncmp(str1, str2, 4));
		test(strncmp(str1, str2, 5) == ft_strncmp(str1, str2, 5));
	});
	group("ft_memchr", {
		char str[] = "Abba";

		test(memchr(str, 'A', 4) == ft_memchr(str, 'A', 4));
		test(memchr(str, 'b', 4) == ft_memchr(str, 'b', 4));
		test(memchr(str, 'a', 4) == ft_memchr(str, 'a', 4));
		test(memchr(str, '\0', 4) == ft_memchr(str, '\0', 4));
		test(memchr(str, 'd', 4) == ft_memchr(str, 'd', 4));
		test(memchr("\0\0\127\0\0", '\127', 4) == ft_memchr("\0\0\127\0\0",
				'\127', 4));
	});
	group("ft_memcmp", {
		unsigned char str1[] = "Abc";
		unsigned char str2[] = "Abd";
		unsigned char arr1[] = "\0\0\127\0\0";
		unsigned char arr2[] = "\0\0\42\0\0";

		test(sign(memcmp(str1, "Def", 0)) == sign(ft_memcmp(str1, "Def", 0)));
		test(sign(memcmp(str1, str2, 0)) == sign(ft_memcmp(str1, str2, 0)));
		test(sign(memcmp(str1, str2, 1)) == sign(ft_memcmp(str1, str2, 1)));
		test(sign(memcmp(str1, str2, 2)) == sign(ft_memcmp(str1, str2, 2)));
		test(sign(memcmp(str1, str2, 3)) == sign(ft_memcmp(str1, str2, 3)));
		test(sign(memcmp(str1, str2, 4)) == sign(ft_memcmp(str1, str2, 4)));
		test(sign(memcmp(arr1, arr2, 4)) == sign(ft_memcmp(arr1, arr2, 4)));
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
		test(atoi("0") == ft_atoi("0"));
		test(atoi("00000") == ft_atoi("00000"));
		test(atoi("00042") == ft_atoi("00042"));
		test(atoi("1234") == ft_atoi("1234"));
		test(atoi("1000") == ft_atoi("1000"));
		test(atoi("+42") == ft_atoi("+42"));
		test(atoi("++42") == ft_atoi("++42"));
		test(atoi("-42") == ft_atoi("-42"));
		test(atoi("--42") == ft_atoi("--42"));
		test(atoi("+") == ft_atoi("+"));
		test(atoi("-") == ft_atoi("-"));
		test(atoi("") == ft_atoi(""));
		test(atoi(" \f\n\r\t\v+42unit") == ft_atoi(" \f\n\r\t\v+42unit"));
		test(atoi("Foobar \f\n\r\t\v-42") == ft_atoi("Foobar \f\n\r\t\v-42"));
		test(atoi("+2147483647") == ft_atoi("+2147483647"));
		test(atoi("-2147483648") == ft_atoi("-2147483648"));
		test(atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234") == ft_atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234"));
	});
	group("ft_calloc", {
		void *ptr;

		// Test: Overflow
		ptr = ft_calloc(2, SIZE_MAX);
		test(ptr == NULL);
		free(ptr);

		// Test: Too Restrictive
		ptr = calloc(0, 0);
		int is_not_restrictive = (ptr != NULL);
		free(ptr);
		if (is_not_restrictive)
		{
			ptr = ft_calloc(0, 0);
			test(ptr != NULL);
			free(ptr);
		}
	});
	group("ft_strdup", {
		char *res;

		// Test 1
		res = ft_strdup("Hello World");
		test(strcmp(res, "Hello World") == 0);
		free(res);

		// Test 2
		res = ft_strdup("");
		test(strcmp(res, "") == 0);
		free(res);
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
		res = ft_strtrim("ooooo", "");
		test(strcmp(res, "ooooo") == 0);
		free(res);
		// Test 4
		res = ft_strtrim("  ooooo  ", " ");
		test(strcmp(res, "ooooo") == 0);
		free(res);
		// Test 5
		res = ft_strtrim("\n ooooo \nooo\n \n", " \n");
		test(strcmp(res, "ooooo \nooo") == 0);
		free(res);
		// Test 6
		res = ft_strtrim("     ooooo  ooo", " o");
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
		res = ft_strmapi("Bonjour", &tospongebob_strmapi);
		test(strcmp(res, "BoNjOuR") == 0);
		free(res);
		// Test 2
		res = ft_strmapi(" Bonjour", &tospongebob_strmapi);
		test(strcmp(res, " bOnJoUr") == 0);
		free(res);
		// Test 3
		res = ft_strmapi("", &tospongebob_strmapi);
		test(strcmp(res, "") == 0);
		free(res);
	});
	group("ft_striteri", {
		char str1[] = "Bonjour";
		char str2[] = " Bonjour";
		char str3[] = "";

		// Test 1
		ft_striteri(str1, &tospongebob_striteri);
		test(strcmp(str1, "BoNjOuR") == 0);
		// Test 2
		ft_striteri(str2, &tospongebob_striteri);
		test(strcmp(str2, " bOnJoUr") == 0);
		// Test 3
		ft_striteri(str3, &tospongebob_striteri);
		test(strcmp(str3, "") == 0);
	});
	group("ft_putchar_fd", {
		int fd;

		fd = STDOUT_FILENO;
		test(ft_putchar_fd_output_matches('C', fd));
		test(ft_putchar_fd_output_matches('\e', fd));

		fd = STDERR_FILENO;
		test(ft_putchar_fd_output_matches('C', fd));
		test(ft_putchar_fd_output_matches('\e', fd));
	});
	group("ft_putstr_fd", {
		int fd;

		fd = STDOUT_FILENO;
		test(ft_putstr_fd_output_matches("Hello, world!\n", fd));
		test(ft_putstr_fd_output_matches("", fd));

		fd = STDERR_FILENO;
		test(ft_putstr_fd_output_matches("Hello, world!\n", fd));
		test(ft_putstr_fd_output_matches("", fd));
	});
#ifdef BONUS
	group("ft_lstnew", {
		char str[] = "Elem";
		t_list *elem = ft_lstnew(str);

		test(strcmp(str, elem->content) == 0);
		test(elem->next == NULL);

		free(elem);
	});
	group("ft_lstadd_front", {
		char *str1 = strdup("First");
		char *str2 = strdup("New First");
		t_list *elem1 = lstnew(str1);
		t_list *elem2 = lstnew(str2);
		t_list **lst = &elem1;
		ft_lstadd_front(lst, elem2);

		test((*lst) == elem2);
		test(strcmp(str2, (*lst)->content) == 0);
		test(strcmp(str1, ((*lst)->next)->content) == 0);

		free_list(*lst);
	});
	group("ft_lstsize", {
		t_list *lst;

		// Test 1
		lst = create_list(1, strdup("Elem"));
		test(ft_lstsize(lst) == 1);
		free_list(lst);
		// Test 2
		lst = create_list(3, strdup("First"), NULL, strdup("Last"));
		test(ft_lstsize(lst) == 3);
		free_list(lst);
		// Test 3
		lst = create_list(0);
		test(ft_lstsize(lst) == 0);
		free_list(lst);
	});
	group("ft_lstlast", {
		t_list *elem1 = lstnew(strdup("First"));
		t_list *elem2 = lstnew(strdup("Last"));
		elem1->next = elem2;
		t_list *lst = elem1;

		test(ft_lstlast(lst) == elem2);
		test(ft_lstlast(NULL) == NULL);

		free_list(lst);
	});
	group("ft_lstadd_back", {
		char *str1 = strdup("First");
		char *str2 = strdup("Last");
		t_list *elem1 = lstnew(str1);
		t_list *elem2 = lstnew(str2);
		t_list *elemNull = NULL;
		t_list **lst = &elem1;

		ft_lstadd_back(lst, elem2);
		test((*lst) == elem1);
		test((*lst)->next == elem2);
		test(strcmp(str1, (*lst)->content) == 0);
		test(strcmp(str2, ((*lst)->next)->content) == 0);

		ft_lstadd_back(&elemNull, elem1);
		test(elemNull == elem1);
		test(strcmp(elemNull->content, elem1->content) == 0);

		free_list(*lst);
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
		ft_lstiter(lst, &toupper_lstiter);

		test(strcmp(elem1->content, "FIRST") == 0);
		test(strcmp(elem2->content, "LAST") == 0);

		free_list(lst);
	});
	group("ft_lstmap", {
		t_list *lst = create_list(2, strdup("First"), strdup("Last"));
		t_list *mapped_lst = ft_lstmap(lst, &toupper_lstmap, &free);
		t_list *mapped_elem1 = mapped_lst;
		t_list *mapped_elem2 = mapped_lst->next;

		test(strcmp(mapped_elem1->content, "FIRST") == 0);
		test(strcmp(mapped_elem2->content, "LAST") == 0);

		free_list(lst);
		free_list(mapped_lst);
	});
#endif

});
