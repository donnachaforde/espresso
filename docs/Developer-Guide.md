# Developer's Guide - espresso lib 
This is your guide to including the espresso library into your project and using its features. 

## Compiling

All the features of the espresso library can be utilized by pulling in the top-level header. 

```cpp
#include <espresso.hxx>
using namespace espresso; 
```

> [!NOTE]  
> All artifacts in the library are contained within the `espresso` namespace. 
 

### Library Macros
The library has just a couple of macros that exist for developer flexibility. First, the library headers disable some common C++ compiler warnings (for the sake of clear build output) but you might not want it to do that. Defining `ESPRESSO_ENABLE_WARNINGS` ensures these compile errors won't be suppressed. 

Second, it can print additional information about the build to `stdout` during compilation. Defining `ESPRESSO_ENABLE_TRACING` enables this logging. 

| Macro| Default |Purpose |
|----------|----------|----------|
|  ESPRESSO_ENABLE_WARNINGS| Disabled| Defining this macro will ensure certain compiler warnings are not disabled.|
|  ESPRESSO_ENABLE_TRACING|  Disabled | Defining this macro ensures compilation notes and todo messages are written to the output window.|

Enable as follows:
```cpp
#define ESPRESSO_ENABLE_WARNINGS
#define ESPRESSO_ENABLE_TRACING
```

> [!IMPORTANT]  
> Of course, these macros must be defined before Crucial information necessary for users to succeed.






## Linking

Add the libespresso library to your list of additional libraries and add the location path to your list of included directories. 

Note that libespresso uses the convention as follows:

| library | Version |
|----------|----------|
|  libespresso  |  Runtime |
|  libespressod  |  Debug |

***
## Coding

Using the library for cmd-line argument parsing is pretty straightforward. Simply create an instance of the arg-manager, add default switches, add your own custom switches and then parse the argv list. 

### Initialization & Specification

First, declare an instance of `Args`, as follows:
```cpp
Args args(argc, 
		  argv, 
		  "programName", 
		  "Add your description here.", 
		  "0.9.0-beta", 
		  "Author's name", 
		  "2025", 
		  "contact email"); 	# or your preferred communication choice
```

You specify the program name and brief description, the version and author, the copyright year and any contact details for bugs or support. These details will be will be used when displaying `--help` or `--usage` information. 


Next, most CLI applications react to the cmd-line args `--help`, `--usage`, `--info` and `--version` and you can leverage the built-in support for this by telling it you want to add these default switches.  

```cpp
args.addDefaults();
```


Then, specify your own cmd-line arguments. Provide the name, the type, a description, whether the argument is mandatory or not and whether the arg/switch requires a target (e.g. ``--file filename.ext``)

```cpp
args.add("file",	Arg::STRING,	"Filename to modify.", true, "filename");
args.add("text",	Arg::NOARG,		"Display text only.");
args.add("count",	Arg::INTEGER,	"Number of lines of text to display.");
```

You may well want to add support for shortcut switches, referred to as 'aliases'

```cpp
args.addAlias("text", 't');
args.addAlias("file", 'f');
args.addAlias("count", 'c');
```

> [!WARNING]  
> The characters 'v', 'i', 'h' and 'u' are automatically specified for the default switches. 


The nature of your CLI may be that it requires a target and you can info the library to enforce that. If the target isn't present, it'll print the usage output to remind the user of what's needed. 

```cpp
args.requireTarget();
```

Finally, create an instance of the `ArgManager` and parse the args. 

```cpp
ArgManager argMgr = ArgManagerFactory::createInstance();
int nRetVal = argMgr.parseAndProcessArgs(args);
if (nRetVal != 0)
{
	::exit(0);
}
```


### Using and Interrogating

Now, you can interrogate this object about args you expect to be present, etc. 

```cpp
// check display preferences
if (args.isPresent("text"))
{
	.
	.
	.
}
```

Or, use the alias character.
```cpp
// check display preferences
if (args.isPresent('t'))
{
	.
	.
	.
}
```

In fact, there is convenient way to check that all your required args are present before you start processing. 

```cpp
if (args.isRequiredArgsPresent())
{
	// we're good to go...
}
```


You can check that a value has been supplied and obtain the stringified or numeric representation of the associated value.

```cpp
String strFilename;
if (args.isPresent("file") && args.isValueSupplied("file"))
{
	strFilename = args.getStringValue("file");
}

int nNumLines = 0; 
if (args.isPresent("--count") && args.isValueSupplied("count"))
{
	nNumLines = args.getNumericValue("count");
}
```




	
***
Donnacha Forde

_Author of the Espresso library 1995-2025_




