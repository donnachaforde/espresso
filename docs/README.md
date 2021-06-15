# Design Blog- espresso lib 
Ruminations on the design and evolution of the espresso library. 

***
## Introduction

The idea of capturing this work in a library came to me many years ago now
while I was still a relatively junior engineer. I'd been working on migration/upload feature developed for performance to complete the task in an strictly limited time-window, as part of an overnight batch job. 

I'd leveraged multithreading to maximize throughput and was running extensive testing to determine exactly how many concurrent threads were optimum and it became clear that passing this info as an arg parameter was an important feature. I implemented a rudimentary solution quickly enough but a curiosity for a more robust solution was ignited and I began tinkering with a more comprehensive command line argument parsing solution. 

I figured it would have general applicability so a standalone library seemed apt. Some time later, having gained experience of API design and Physical Code Design, I remodeled the library into pretty much the current layout. 

At this point, anytime I had an idea for a handy tool or utility, I had a quick way to create it and treat it as a command, with the typical handling of help, version and usage information. 


***
## Design Goals/Influences

There are a few stylistic aspects to the solution that are a result of some influences. 

* I like libraries that have a single header for simple inclusion and adoption. 
* Equally, I like libraries that are logically segregated so you can include the parts you like and avoid #including the parts you don't. 
* I wanted the solution to be cross-platform so I could build tools for Windows and Unix/Linux. Later, as macOS emerged as a development platform, I ported to this OS. 
* Internally, I wanted to take advantage of precompiled headers when working on Windows. 
* I wanted a completely clean build, without any compiler or linker warnings so I wanted to be able to disable some compiler warnings. However, I wanted a way for the user to disable that.
* I like to use write additional messages to the output window when compiling, but I wanted to provide a way to disable this in case they annoyed other users. 

So, as theme, I wanted ultimately flexibility. 



***
## Design Evolution


When working with C++ and taking an object-oriented approach, there are lots of ways to devise a solution. It occurred to me that while I originally developed the library for use with CMD-line tools, some Windows developers have a preference, if not a natural instinct, to devise tool solutions using the Windows UI. So, while you may well launch the command from the CMD-line with optional arguments, it actually launches a Windows GUI. 

This really challenged my assumptions about the library writing to stdout. I didn't want to limit its scope so I set about catering to this facet - i.e. separating argument parsing logic from writing output to stdout. My initial attempt was to use class inheritance to separate 'common' logic into an abstract base class and pushing the parts leveraging stdout into a concrete class. This succeeded in achieving the design goal but it didn't sit well with me as an elegant solution. 

Years later, when working with Java and learning about Spring's Inversion of Control (IOC) design pattern, I learnt about the concept of separating function down to it's core parts. For example, I realized that rendering output is quite distinct from argument parsing. This allowed me to provide a stdout renderer as standard but provided a means for another developer to devise a compatible renderer for there environment. 

I detailed the design thought process in a separate article on [construction](Blog-Construction.md). 

Another design journey lead me down a track that led to the implementation of the [MVC pattern](Blog-Manager-Object.md). 

***
## Style, Conventions and External Influences

When I first devised the espresso library, I was strongly influenced by the Visual C++ naming conventions, using camelCase with a leading capital letter. I always thought this more aesthetically pleasing that the use of underscores in names.

However, after years and years of Java programming, I came round to having a preference for camelCase 'without' the leading uppercase letter. I tend to use a 'light' version of Hungarian notation so I found my new preference to be compatible with this. 

***
## IDE History

This library was first developed using Visual C++ 6.0. That version of the Microsoft C/C++ compiler had quite a long life and the project was still tied to that version for many years. Eventually, it was upgraded to Visual Studio 2003 (Visual C++ 7), then Visual C++ 8 and Visual C++ 9. Thereafter, it was neglected while I pursued pure Java development and didn't get any attention until Visual Studio 2014 but then was upgraded to Visual Studio 17 and most recently Visual Studio 2019. 

***
Donnacha Forde - Espresso Library

1995-2021

