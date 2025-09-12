# README - espresso lib 
A simple C++ library to help develop CLI tools easily and quickly by handling processing of command-line args. 


## Introduction

Have you ever found yourself building an application or tool only to get bogged down having to parse command-line args?

That's where the **espresso** library comes in. It makes it easy to specify what cmd-line switches you wish to support, whether they take a parameter and whether they're mandatory. It provides the ability to interrogate these switches, check they're present and retrieve their stringified or numeric values. In short, it handles these chores so that you're free to concentrate on your applications features.


The key features are:
* A clear and simple API to define the arguments/switches your application supports.  
* Automatic parsing of the arg-list and syntax checking to ensure the correct params and required params have been provided.
* Built-in support for default args - i.e. `--help`, `--version`, `--info` and `--usage`. 
* Built-in support for `stdout` output (extensible so you can provide your own - e.g for your Windows GUI app). 




## Contents

Whats included?

* libespresso -  static C++ library (both Debug and Release versions)
* header files - the espresso C++ header files 


## Supported Platforms


What platforms are supported?

* Windows 10 and 11 x64 (Visual C++ 2019)
* macOS (cmake)

### Additional Platforms

Previously, the following platforms were supported for *gcc* using `make`. They haven't been exercised recently but there's every chance the makefile will still work. 

* Solaris SunOS
* AIX
* HP-UX
* Red Hat Linux

### History of Build Environments & Supported Platforms
The original visual studio file were created Visual Studio 6.0, which provides a clue as to when the project idea originated. The project was later ported to Visual Studio 2003, then Visual Studio 2005 and later again Visual Studio 2008. There then followed a fallow period when I worked on other tech stacks before becoming re-acquainted with DevStudio using Visual Studio 2014 and then Visual Studio 2017. The most recent port was to Visual Studio 2019 though Visual Studio 2022 is overdue. 

As the library was first built with Visual Studio 6.0, it only supported Windows 32-bit environments but was successfully ported and deployed to UNIX/Linux environments using a basic `makefile`. Later, the code was successfully built for x64 environments without issue. While the `makefile` is primitive, it should still work for UNIX environments. 

Most recently, the build for macOS environments was revised to support `cmake`. 





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
cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=Release # for release build
cmake -S ./src -B ./build -DCMAKE_BUILD_TYPE=Debug   # for debug build
```

```bash
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

## Installation

### Install Steps (macOS & Linux)
You can either build the project or download the artifacts from the releases on GitHub. 

If you build the project using CMake, you can install the headers and libs directly.

```bash
# install to default location (usually usr/local/include and /usr/local/lib)
sudo cmake --install ./build --config Release   
```

If you first want to check out what the install is going, simply install locally as follows:

```bash
cmake --install ./build --prefix ./install

```


## Additional Resources
There are other resources you can use to familiarize yourself with the library, as follows:

-  [Developer Guide](docs/Developer-Guide.md) - This will walk you through how to incorporate the library into your project and how to exercise the library. 

- [Sample Implementations](https://github.com/donnachaforde/espresso-tools) - Code examples showing how to use the library can be viewed in [espresso tools](https://github.com/donnachaforde/espresso-tools),  a collection of simple CLI utilities. 

- [Design Discussions](https://donnachaforde.github.io/blogs+posts/software-engineering/espresso/)- Blogs discussing design options and trade-offs for those that'd like to delve deeper into the design philosophy behind `libespresso`.





***

Donnacha Forde

_Last updated: September 2025_

