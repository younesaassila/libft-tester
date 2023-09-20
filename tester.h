/**
 * 42-tester.h v1.0.2 by Younes Aassila (https://github.com/younesaassila)
 */

#ifndef TESTER_H
# define TESTER_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define BOLD "\001\e[1m\002"
# define RED "\001\e[31m\002"
# define GRN "\001\e[32m\002"
# define YEL "\001\e[33m\002"
# define BLU "\001\e[34m\002"
# define MAG "\001\e[35m\002"
# define CYN "\001\e[36m\002"
# define WHT "\001\e[37m\002"
# define RESET "\001\e[0m\002"

# define TESTER(title, code)                                     \
	int main(int argc, char const *argv[])                       \
	{                                                            \
		int __exit_status;                                       \
		int __test_index;                                        \
		int __success_count;                                     \
		int __failure_count;                                     \
		bool EXIT_ON_FAIL;                                       \
                                                                 \
		__exit_status = EXIT_SUCCESS;                            \
		__test_index = 0;                                        \
		__success_count = 0;                                     \
		__failure_count = 0;                                     \
		EXIT_ON_FAIL = false;                                    \
		printf(BOLD "%s\n\n" RESET, title);                      \
		code;                                                    \
		printf("\n");                                            \
		if (__failure_count)                                     \
			printf(RED "%d failed" RESET ", ", __failure_count); \
		printf(GRN "%d passed\n" RESET, __success_count);        \
		(void)argc;                                              \
		(void)argv;                                              \
		return (__exit_status);                                  \
	}

# define group(name, code)                     \
	{                                          \
		int __test_index;                      \
                                               \
		__test_index = 0;                      \
		printf(BOLD CYN "[%s]\n" RESET, name); \
		code;                                  \
		printf("\n");                          \
	}

# define test(condition)                                         \
	{                                                            \
		if (condition)                                           \
		{                                                        \
			__success_count++;                                   \
			printf(GRN "%d. OK\n" RESET, (__test_index + 1));    \
		}                                                        \
		else                                                     \
		{                                                        \
			__failure_count++;                                   \
			printf(RED "%d. Error\n" RESET, (__test_index + 1)); \
			__exit_status = EXIT_FAILURE;                        \
			if (EXIT_ON_FAIL)                                    \
				return (__exit_status);                          \
		}                                                        \
		__test_index++;                                          \
	}

#endif
