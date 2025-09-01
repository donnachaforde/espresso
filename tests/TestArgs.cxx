#include <gtest/gtest.h>
#include <espresso.hxx>
using namespace espresso;

TEST(ArgsTest, GetProgramName)
{
    const string strProgramName = "myprog";
    Args args(0, nullptr, strProgramName, "desc", "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getProgramName(), strProgramName);
}

TEST(ArgsTest, GetProgramDescription) 
{
    const string strProgramDescription = "desc.";
    Args args(0, nullptr, "test", strProgramDescription, "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getProgramDescription(), strProgramDescription);
}

TEST(ArgsTest, GetVersion) 
{
    const string strVersion = "1.2.3";
    Args args(0, nullptr, "test", "desc", strVersion, "author", "2025", "@handle");
    EXPECT_EQ(args.getVersion(), strVersion);
}


TEST(ArgsTest, GetYearAndOwner)
{
    const string strYear = "2025";
    const string strCopyrightOwner = "John Smith";
    string strCopyrightMessage = "Copyright " + strYear + ", " + strCopyrightOwner + ". All rights reserved.";

    Args args(0, nullptr, "test", "desc", "0.1", strCopyrightOwner, strYear, "@handle");
    EXPECT_EQ(args.getCopyrightNotice(), strCopyrightMessage);
}

TEST(ArgsTest, GeBugReportingHandle)
{
    const string strHandle = "@janedoe";
    string strMessage = "Report bugs to " + strHandle + ".";
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", strHandle);
    EXPECT_EQ(args.getBugReportingInstructions(), strMessage);
}

// TEST(ArgsTest, DefaultHelpPresent) 
// {
//     Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
//     args.addDefaults();

// 	ArgManager argMgr = ArgManagerFactory::createInstance();
// 	int nRetVal = argMgr.parseAndProcessArgs(args);
// 	if (nRetVal != 0)
// 	{
// 		::exit(0);
// 	}    

//     EXPECT_TRUE(args.isPresent("help"));
// }


