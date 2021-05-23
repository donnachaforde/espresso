# Blog - Construction
The thought process around construction. 

***
## Introduction

In this blog, I explore construction patterns for initializing the library. As described in my top-level blog, my goal was to provide a way to initialize the library for writing to stdout without excluding alternative rendering. 



***
## Influences

When thinking about design, I find it helps to have a conversation with yourself to try to identify 'baggage' - what pre-conceptions and preferences you're bringing to the table on day-one.  

* I like simple and clean interfaces that are easy to use and encourage adoption.  
* I prefer Factory classes over constructors.
* I like utilizing 'Manager' classes or singletons where there is ever only one instance or there is a need to address objects collectively (through a manager).
* I like clearly defined roles and responsibilities when it comes to memory management and resource usage. Consequently, I'm often reluctant to defer to using the heap when I don't control both client and server (or caller and callee) code. 
* I admire the IOC design pattern employed in Spring. 




***
## Design Evolution

Taking the programmer's experience of the library into consider, I wanted a clear way to model and capture command-line argument info, as follows:

	Args args(...);

	args.add(...);
	args.add(...);
	args.add(...);
	
	args.addAlias(...);
	args.addAlias(...);

Next, I wanted the user to declare a manager object that, under the covers, defined the relationship between the args and the arg-renderer. Early on, I let the user define the Argument-Manager directly but once I had incorporated the ability to render the args in more ways than stdout, a factory made more sense. 

Originally, the code would have had to be declared as follows:

	StdoutArgRenderer stdoutArgRenderer;
	ArgMgr argMgr(stdoutArgRenderer);

The idea being that if a developer wanted to show command-line argument info in a dialog box, they could define their own render and initialize as follows:

	WindowsArgRenderer windowsArgRenderer;
	ArgMgr argMgr(windowsArgRenderer);


This was possible because I had defined an interface for arg-rendering - i.e. `IArgRenderer` to allow the user to provide their own renderer. The `ArgMgr` class holds a reference of type `IArgRenderer` and in turn, the object delegates all print output to this instance. So, the trick is simply to provide the ArgMgr instance with a valid ArgRenderer. 


However, I really wanted this to encapsulate this detail for the vast majority of users so I decided to employ a Factory that would do this simple initialization for me. 

	ArgManager argMgr = ArgManagerFactory::createInstance();

Under the covers, an early attempt took this approach:

	ArgMgr ArgManagerFactory::createInstance()
	{
		StdoutArgRenderer stdoutArgRenderer;
		return createInstance(stdoutArgRenderer);
	}

	ArgMgr ArgManagerFactory::createInstance(IArgRenderer& argRenderer)
	{
		ArgMgr argMgr(argRenderer);
		return argMgr;
	}
The mechanics of this approach meant that I had to provide a copy-constructor implementation for ArgMgr, though this was trivial. You can see that the cleanest implementation for the factory methods involved passing back a copy of the object rather than a pointer or reference (thus avoiding any messy responsibilities for deletion). 


Of course, this approach didn't work. 


Even though this succeeded in providing the ArgMgr object with a valid reference to a renderer object, declaring the stdoutRenderer on the heap meant that it got destructed when the factory method returned. The valid reference referenced invalid memory causing an Access Violation. 

Incidentally, things work when the user explicitly declares the ArgRenderer (as above) because it will still exist on the heap. 

My first reaction was that, despite my best efforts, I was going to have to rely on the renderer object being allocated on the heap. I couldn't utilize concrete objects **and** rely on dynamic types at runtime. The ArgMgr class couldn't know the concrete type of the object is was interacting with here. It had to use a pointer or reference in order for that dynamic relationship. In this instance, it's clear that the GC approach deployed in Java provides a greater degree of freedom in facilitating Dynamic Injection (DI) and the Inversion of Control (IoC) pattern. 


	


***
Donnacha Forde - Espresso Library

May 2021

