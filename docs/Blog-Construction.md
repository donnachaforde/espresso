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

Further, I wanted this to default seamlessly to stdout. While a design goal was to provide the user with the flexibility to define and provide their own arg-renderer, I wanted to encapsulate this.  

	ArgManager argMgr = ArgManagerFactory::createInstance();

I had defined an interface for arg-rendering in `IArgRenderer` so as to allow the user to provide their own renderer as follows:

	ArgManager argMgr = ArgManagerFactory::createInstance(myRenderer);
 

The `createInstance()` methods are defined as static members of the `ArgFactory` class, which has all ctors declared as private. 

Under the covers, the implementation of `createInstance()` was as follows:

	ArgMgr ArgManagerFactory::createInstance()
	{
		StdoutArgRenderer stdoutArgRenderer;
		return createInstance(stdoutArgRenderer);
	}
	


***
Donnacha Forde - Espresso Library

May 2021

