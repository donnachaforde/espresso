# espresso
A small C++ library to help with developing CLI tools quickly (plus a few handy CLI utilities).

***
## Contents

Whats included?

* espresso-lib - a static C++ library
 
    - Support for simplfying processing of command-line args.
    - Helper code around some handy C/C++ library calls

* espresso-tools - A set of help utilities, built using the espresso library. 


***
## Supported Platforms

What platforms are supported?

* Windows 32-bit
* Solaris SunOS
* AIX
* HP-UX
* Red Hat Linux

The software was initially written to be used on Windows 32-bit but it has been successfully built and used on the platforms above. 


***
## Build Environments

The project files were originally started using Visual Studio 6.0 (which gives an indication as to the point 'tinkering' began) but for the espresso library, were ported to Visual Studio 2003, then Visual Studio 2005 and later Visual Studio 2008. There followed a fallow period before I again became acquainted with DevStudio using Visual Studio 2014. 

Whenever I needed a tool to work on a Unix/Linux platform, I used a really simple Make file so a number of the tools projects will have make capability.


