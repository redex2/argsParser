#include <gtest/gtest.h>
#include <argsParser.h>

TEST(argumentOpt, argumentOpt) {
	char* arg[3] = { (char*)"foo", (char*)"--bar", (char*)"baz" };
	int argc = 3;
	argsParser parser;
	parser.addOpt("bar", 'b', "", true);

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
	EXPECT_EQ(parser.getArgument("bar"), "baz");
	EXPECT_EQ(parser.getArgument('b'), "baz");
}
