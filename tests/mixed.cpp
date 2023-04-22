#include <gtest/gtest.h>
#include <argsParser.h>

TEST(mixedOpt, mixedOpt) {
	char* arg[6] = { (char*)"foo", (char*)"--bar", (char*)"baz", (char*)"-q", (char*)"quux" , (char*)"--corge" };
	int argc = 6;
	argsParser parser;
	parser.addOpt("bar", 'b', "", true);
	parser.addOpt("qux", 'q', "", true);
	parser.addOpt("corge", 'c', "", false);

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
	EXPECT_EQ(parser.getArgument("bar"), "baz");
	EXPECT_EQ(parser.getArgument('b'), "baz");

	EXPECT_TRUE(parser.isOptSet("qux"));
	EXPECT_TRUE(parser.isOptSet('q'));
	EXPECT_EQ(parser.getArgument("qux"), "quux");
	EXPECT_EQ(parser.getArgument('q'), "quux");

	EXPECT_TRUE(parser.isOptSet("corge"));
	EXPECT_TRUE(parser.isOptSet('c'));
}
