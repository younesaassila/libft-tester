# libft-tester

## Installation

```sh
git clone https://github.com/younesaassila/libft-tester.git
cd libft-tester
```

## Build

### Mandatory part

```sh
cd ..
make && make clean
cd libft-tester
cc -Wall -Wextra -Werror -L.. -lft -lbsd -o tester tester.c
```

### Bonus part

```sh
cd ..
make bonus && make clean
cd libft-tester
cc -Wall -Wextra -Werror -D BONUS -L.. -lft -lbsd -o tester tester.c
```

## Usage

### Run tests

```sh
./tester
```

### Memory leaks

```sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tester
```
