# README - espresso lib 
A simple C++ library to help develop CLI tools easily and quickly by handling processing of command-line args. 


## Introduction

Have you ever found yourself building an application of tool only to get bogged down having to parse command-line args?

That's where the **espresso** library comes in. It makes it easy to specify what cmd-line switches you wish to support, whether they take a parameter and whether they're mandatory. It provides the ability to interrogate these switches, check they are present and retrieve their stringified or numeric values. In short, it handles these chores and allows you to concentrate on your applications features.


The key features are:
* A clear and simple API to define the arguments/switches your application supports.  
* Automatic parsing of the arg-list and syntax checking to ensure the correct params and required params are being provided.
* Provision of common default args, such as `--help`, `--version`, `--info` and `--usage`. 
* Support for output to `stdout` by default but which is extensible so you can leverage it for your GUI app. 




## Contents

Whats included?

* libespresso -  static C++ library 
* header files - the espresso C++ header files 


## Supported Platforms


What platforms are supported?

* Windows 10 and 11 x64 (Visual C++ 2019)
* macOS (cmake)


Previously, the following platforms were supported for *gcc* using `make`. They haven't been exercised recently but there's every chance the makefile will still work. 

* Solaris SunOS
* AIX
* HP-UX
* Red Hat Linux

The software was originally developed on Windows 32-bit environments but was successfully ported and deployed to Unix/Linux environments. Later, the code was successfully built for x64 environments without issue. While the `makefile` is primitive, it should still work for UNIX environments. Most recently, it has been revised to build on macOS environments. 


## Build Environments

The original visual studio file were created Visual Studio 6.0 (which gives an indication as to the point when this 'tinkering' began) but were later ported to Visual Studio 2003, then Visual Studio 2005 and later Visual Studio 2008. There then followed a fallow period before I again became re-acquainted with DevStudio using Visual Studio 2014 and then Visual Studio 2017. Most recently, I've ported to Visual Studio 2019. 


## Building with CMake (macOS & Cross-Platform)

The project now supports building with CMake, making it easy to build on macOS and other platforms.

### Prerequisites

- CMake (install via Homebrew: `brew install cmake`)
- A C++17-compatible compiler (e.g., Apple Clang, GCC, MSVC)

### Build Steps (macOS/Linux)

Clone the repo.
```bash
git clone https://github.com/donnachaforde/espresso.git
cd espresso
```
Trigger the CMake 'generate' and 'build' steps.
```bash
cmake -S ./src -B ./build 
cmake --build ./build --config Release   # For release build (libespresso.a)
cmake --build ./build --config Debug     # For debug build (libespressod.a)
```

The static library will be generated in `build/lib/` as `libespresso.a` (Release) and `libespressod.a` (Debug).

### Build Steps (Windows)

You can use CMake with Visual Studio 2019 or later:

```powershell
cmake -S ./src -B ./build
cmake --build ./build --config Release   # libespresso.lib
cmake --build ./build --config Debug     # libespressod.lib
```

### Notes
- Precompiled headers are supported (using `stdhdr.hxx`).
- The legacy makefile is still available for Unix-like systems.


## Further Info

### Developer Guide
The [Developer Guide](docs/Developer-Guide.md) guide will walk you through how to incorporate the library into your project and how to exercise the code. 




### Examples
To see examples of how the **espresso** library is used in anger, check out [espresso tools](https://github.com/donnachaforde/espresso-tools), which is a collection of simple CLI utilities. 

### Blog

There is a [blog](docs/README.md) about the design of the **espresso** library that describes how its design evolved. 





***

Donnacha Forde

_Last updated:_ September 2025

