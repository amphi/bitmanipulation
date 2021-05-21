# Bitmanipulation

This is a small C++ library that brings functions to do bitmanipulation. This
is also a learning project. The goal is to build this project with CMake and
Nix, and to enable other projects to easily include this library using CMake
and Nix.

## How to build

You can build this project using nix, cmake and ninja:

```bash
$ mkdir build
$ nix-shell
nix-shell$ cd build
nix-shell$ cmake .. -G Ninja
nix-shell$ ninja
```

This project also has some tests, you can execute them from the `build` folder:

```bash
nix-shell$ ctest
```
