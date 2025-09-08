#include <gtest/gtest.h>
#include <espresso.hxx>
using namespace espresso;

TEST(ArgsTest, GetProgramNameReturnsExpectedName)
{
    const string strProgramName = "myprog";
    Args args(0, nullptr, strProgramName, "desc", "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getProgramName(), strProgramName);
}

TEST(ArgsTest, GetProgramDescriptionReturnsExpectedDescription) 
{
    const string strProgramDescription = "desc.";
    Args args(0, nullptr, "test", strProgramDescription, "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getProgramDescription(), strProgramDescription);
}

TEST(ArgsTest, GetVersionReturnsExpectedVersion) 
{
    const string strVersion = "1.2.3";
    Args args(0, nullptr, "test", "desc", strVersion, "author", "2025", "@handle");
    EXPECT_EQ(args.getVersion(), strVersion);
}


TEST(ArgsTest, GetCopyrightDetailsReturnsExpectedCopyrightYearAndOwner)
{
    const string strYear = "2025";
    const string strCopyrightOwner = "John Smith";
    string strCopyrightMessage = "Copyright " + strYear + ", " + strCopyrightOwner + ". All rights reserved.";

    Args args(0, nullptr, "test", "desc", "0.1", strCopyrightOwner, strYear, "@handle");
    EXPECT_EQ(args.getCopyrightNotice(), strCopyrightMessage);
}

TEST(ArgsTest, GeBugReportingInstructionsReturnsExpectedContact)
{
    const string strHandle = "@janedoe";
    string strMessage = "Report bugs to " + strHandle + ".";
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", strHandle);
    EXPECT_EQ(args.getBugReportingInstructions(), strMessage);
}


TEST(ArgsTest, TargetRequiredNotPresentBeforehand) 
{
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
    EXPECT_FALSE(args.isTargetPresent());
}

TEST(ArgsTest, TargetShouldBeAnEmptyStringBeforehand) 
{
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getTarget(), "");
}

TEST(ArgsTest, TargetPresentShouldBeFalseBeforeParsing) 
{
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
    EXPECT_FALSE(args.isTargetRequired());
}

TEST(ArgsTest, TargetShouldBeAnEmptyStringBeforeParsing) 
{
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getTarget(), "");
}

TEST(ArgsTest, InvalidOptionShouldBeEmptyStringBeforeParsing) 
{
    Args args(0, nullptr, "test", "desc", "0.1", "author", "2025", "@handle");
    EXPECT_EQ(args.getInvalidOption(), "");
}

TEST(ArgsTestPostSetup, GetUsageReturnsExpectedKeywords)
{
    Args args(0, nullptr, "myprog", "A test program", "1.0", "John Smith", "2025", "bugs@example.com");
    args.add("--input", Arg::type_t::STRING, true, "Input file");
    args.add("--output", Arg::type_t::STRING, false, "Output file");
    args.addDefaults();

    std::string usage = args.getUsage();

    // Check that usage contains expected switches and program name
    EXPECT_NE(usage.find("myprog"), std::string::npos);
    EXPECT_NE(usage.find("Usage:"), std::string::npos);
    EXPECT_NE(usage.find("Usage"), std::string::npos);
}

TEST(ArgsTestPostSetup, GetUsageReturnsRequiredArgs)
{
    Args args(0, nullptr, "myprog", "A test program", "1.0", "John Smith", "2025", "bugs@example.com");
    args.add("--required", Arg::type_t::STRING, true, "Input file");
    args.add("--optional", Arg::type_t::STRING, false, "Output file");

    std::string usage = args.getUsage();

    EXPECT_NE(usage.find("required"), std::string::npos);
    EXPECT_NE(usage.find("optional"), std::string::npos);
}






