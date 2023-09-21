# libft-tester

## Installation

```sh
git clone https://github.com/younesaassila/libft-tester.git
cd libft-tester
```

## Build

### Mandatory part

```sh
make -C .. && make -C .. clean
cc -I.. -o tester tester.c -L.. -lft -lbsd
```

### Bonus part

```sh
make -C .. bonus && make -C .. clean
cc -D BONUS -I.. -o tester tester.c -L.. -lft -lbsd
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
