# README - espresso lib 
A simple C++ library to help develop CLI tools easily and quickly by handling command-line args. 


## Introduction

Have you ever had a good idea for a CLI tool? But, when it comes to developing it, you get bogged down dealing with the intricacies of dealing with command line options? If so, then, **espresso** can alleviate that overhead by taking care of command-line options, help and versioning output, automatic error checking and handling, thereby freeing you up to concentrate on solving your utility. 

The key features are:
* A clear and simple API to define the arguments/switches your tool supports. 
* Automatic parsing of the arglist and syntax checking to ensure the correct params are being provided.
* Provision of common default args, such as --help, --version, --info and --usage. 




## Contents

Whats included?

* libespresso -  static C++ library 
* header files - the espresso C++ header files 


## Supported Platforms


What platforms are supported?

* Windows 10 x64 (Visual C++ 2019)
* macOS (gcc)


Previously, the following platforms were supported for *gcc*. They haven't been exercised recently but there's every chance the makefile will still work. 

* Solaris SunOS
* AIX
* HP-UX
* Red Hat Linux

The software was originally developed on Windows 32-bit environments but was successfully ported and deployed to Unix/Linux environments. Later, the code was successfully built for x64 environments without issue. While the `makefile` is primitive, it should still work for Unix/Linux environments. Most recently, it has been revised to build on macOS environments. 


## Build Environments

The original visual studio file were created Visual Studio 6.0 (which gives an indication as to the point when this 'tinkering' began) but were later ported to Visual Studio 2003, then Visual Studio 2005 and later Visual Studio 2008. There followed a fallow period before I again became re-acquainted with DevStudio using Visual Studio 2014 and then Visual Studio 2017. Most recently, I've ported to Visual Studio 2019. 


## Building with CMake (macOS & Cross-Platform)

The project now supports building with CMake, making it easy to build on macOS and other platforms.

### Prerequisites

- CMake (install via Homebrew: `brew install cmake`)
- A C++17-compatible compiler (e.g., Apple Clang, GCC, MSVC)

### Build Steps (macOS/Linux)

```bash
git clone https://github.com/donnachaforde/espresso.git
cd espresso

cmake -S ./ -B ./build 
cmake --build ./build --config Release   # For release build (libespresso.a)
cmake --build ./build --config Debug     # For debug build (libespressod.a)
```

The static library will be generated in `build/lib/` as `libespresso.a` (Release) and `libespressod.a` (Debug).

### Build Steps (Windows)

You can use CMake with Visual Studio 2019 or later:

```powershell
cmake -S . -B ./build
cmake --build ./build --config Release   # libespresso.lib
cmake --build ./build --config Debug     # libespressod.lib
```

### Notes
- Precompiled headers are supported (using `stdhdr.hxx`).
- The legacy makefile is still available for Unix-like systems.



## Examples
Check out [espresso tools](https://github.com/donnachaforde/espresso-tools) for example code that uses Espresso lib. There is also a [Developer Guide](docs/Developer-Guide.md) that mas more info on how to use the library to get you up and running quickly. 

Finally, there's a [blog](docs/README.md) where I try to capture thoughts on design as the solution evolves. 

***




Donnacha Forde

August 2025

