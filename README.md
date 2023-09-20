# libft-tester

## Installation

```sh
git clone https://github.com/younesaassila/libft-tester.git
make all
cd libft-tester
```

## Build

### Mandatory part

```sh
find .. -maxdepth 1 -type f -name '*.c' | xargs cc -Wall -Wextra -Werror -L.. -lft -lbsd -o tester tester.c
```

### Bonus part

```sh
find .. -maxdepth 1 -type f -name '*.c' | xargs cc -Wall -Wextra -Werror -D BONUS -L.. -lft -lbsd -o tester tester.c
```

## Usage

```sh
./tester
```
