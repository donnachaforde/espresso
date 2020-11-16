# README - espresso lib 
A small C++ library for developing CLI tools easily and quickly.

***
## Introduction

Have you ever had a good idea for a CLI tool but found yourself somewhat hindered by having to provide support for command-line arguments? If so, **espresso** can alleviate this overhead by handling parsing and handling command-line switches. 

The key features are:
* A clear and simple API to define the arguments/switches supported by your utility. 
* Parse the arglist and provide syntax checking to ensure the correct params are being provided.
* Provide basic help and info messages about your CLI tool. 




***
## Contents

Whats included?

* libespresso -  static C++ library 
* header files - the espresso C++ header files 


***
## Supported Platforms


What platforms are supported?

* Windows 10 (Visual C++ 2017)
* macOS (gcc)


Previously, the following platforms were supported for *gcc*. They haven't been exercised in recent years but there's every chance the makefile will still work. 

* Solaris SunOS
* AIX
* HP-UX
* Red Hat Linux

The software was originally developed on Windows 32-bit environments but was successfully ported and deployed to Unix/Linux environments. Later, the code was successfully built for x64 environments without issue. While the `makefile` is primitive, it should still work for Unix/Linux environments. Most recently, it has been revised to build on macOS environments. 


***
## Build Environments

The original visual studio file were created Visual Studio 6.0 (which gives an indication as to the point when this 'tinkering' began) but were later ported to Visual Studio 2003, then Visual Studio 2005 and later Visual Studio 2008. There followed a fallow period before I again became re-acquainted with DevStudio using Visual Studio 2014 and then Visual Studio 2017. Most recently, I've ported to Visual Studio 2019. 

The makefile is pretty trivial but works. Plans are afoot to adopt CMake. 


***
## Examples
Check out [Espresso Tools](https://github.com/donnachaforde/espresso-tools) for example code that uses Espresso lib. 

***




Donnacha Forde

2020

