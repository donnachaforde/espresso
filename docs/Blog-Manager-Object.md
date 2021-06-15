# Blog - Manager Object
The rationale behind the introduction of the 'Manager' object in espresso.   

***
## Introduction

In this blog, I explore the presence of the 'manager' object in the class design for the espresso library, which might be considered controversial in some circles. In a pure OO model, your classes represent real-work entities and managers don't always, if perhaps never, fit into that model. Still, I remain a fan and resort to deploying such classes frequently. 



***
## Influences

There were two drivers to introducing the `ArgumentManager` class, as follows:

1. From a modelling perspective, having the `ArgList` class both represent the list of arguments - and - the parser of the list didn't seem quite right. Is it representing the thing or is it parsing the thing?

2. Every command-line tool using the library had duplicate code to handle the normal stdout messages. I needed to remove duplication. 



***
## Design Evolution

The initial driver though was the desire to avoid writing duplicate code. After developing some tools that leveraged the espresso library, I realised certain command-line arguments are common to almost all commands. Requests for _help_ and _version_ being practically universal. 


The following code was common across all the CLI tools I'd developed:

	// check for requests for help, usage and version
	if (args.isPresent("help") || args.isPresent('h') || args.isPresent('?'))
	{
		cout															<< endl
			 << args.getProgramDescription()							<< endl
																		<< endl 
			 << args.getUsage()											<< endl
																		<< endl 
			 << args.getOptionsDescriptions()							<< endl
																		<< endl
			 << args.getCopyrightNotice()								<< endl
			 << args.getBugReportingInstructions()						<< endl;

		::exit(0);
	}
	else if (args.isPresent("usage"))
	{
		cout << args.getUsage()											<< endl
																		<< endl 
			 << args.getCopyrightNotice()								<< endl;
		::exit(0);
	}
	else if (args.isPresent("version"))
	{
		cout << args.getProgramName() << " " << args.getVersion()		<< endl 
			 << args.getCopyrightNotice()								<< endl;
		::exit(0);
	}


I really needed somewhere 'common' to put this and decided a 'manager' would do. Later, as I write about in my [overview blog](README.md), I related this requirement to the need to decouple rendering from the target render type so, in the end, this code was later moved out of the Manager to a dedicated stdout renderer. 


In shifting parsing duties from the `ArgList` class to the `ArgumentManager`, I also had to address basic error handling and the misuse of command-line arguments. In doing so, I changed the method name from `parse()` to `parseAndProcess()`, which better infers that some processing of the parsed args is going to happen. In general, I find that taking a little care with method/function names is worth the efforts can pay dividends down the line. 


## Conclusion
It was really only after the fact that it dawned on me that, between the separation of model and manager and the dedicated renderer, I'd essentially implemented an __MVC design pattern__. Honestly, I didn't set out with that intention (though, maybe I should've) but in hindsight, it's the correct approach to have had applied and in a way, reinforces the smaller design decisions made along the way. 



***
Donnacha 
