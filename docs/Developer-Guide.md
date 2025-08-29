# Developer's Guide - espresso lib 
Additional info about using the espresso library. 

***
## Compiling

The easiest way to start using the library is to #include <espresso.hxx> header file. In turn, it #includes all the constituent parts. 


### namespace
All articles within the espresso library are contained within the 'espresso' namespace.


### macros
All espresso macros must be #defined before <espresso.hxx> is #included. 
| macro| Default |Purpose |
|----------|----------|----------|
|  ESPRESSO_ENABLE_WARNINGS| Disabled| Defining this macro will ensure specific certain compiler warnings are not disabled.|
|  ESPRESSO_ENABLE_TRACING|  Disabled | Defining this macro ensure compilation notes and todo messages are written to the output window.|




### version

The version number of the library is defined within the <espresso.hxx> header, which is publicly accessible as:

		espresso::BUILD_VERSION 
***
## Linking

Add the libespresso library to your list of additional libraries and add the location path to your list of included directories. 

Note that libespresso uses the convention as follows:

| library | Version |
|----------|----------|
|  libespresso  |  Runtime |
|  libespressod  |  Debug |

***
## Coding

Using the library for CMD-line argument parsing is pretty straightforward. Simply create an instance of the arg-manager, add default switches, add your own custom switches and then parse the argv list. 


	Args args(argc, 
			  argv, 
			  "programName", 
			  "Add your description here.", 
			  "0.9.0-beta", 
			  "Author's name", 
			  "2021", 
			  "@TwitterHandle");

You will most likely want to include support for cmd-line args like 'help' and 'version' and these are already availble by adding defaults, like this. 

	args.addDefaults();

Next, specify your own cmd-line arguments. Provide the name, the type, a description, whether the argument is mandatory or not and whether the arg/switch requires a target (e.g. --file filename.ext)

	args.add("file",	Arg::STRING,	"Filename to modify.", true, "filename");
	args.add("text",	Arg::NOARG,		"Display text only.");


Shortcut switches are also support as 'aliases'

	args.addAlias("columns", 'c');
	args.addAlias("file", 'f');

Next, create an Argument Manager and 'parse' the args. 

	ArgManager argMgr = ArgManagerFactory::createInstance();
	int nRetVal = argMgr.parseAndProcessArgs(args);
	if (nRetVal != 0)
	{
		::exit(0);
	}

You can interogate the Arg-Manager about args you expect, etc. 

	// check display preferences
	if (args.isPresent("text"))
	{
		.
		.
		.
	}
	
	
***
Donnacha Forde - Espresso Library

1995-2021




