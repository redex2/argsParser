#include <gtest/gtest.h>
#include <argsParser.h>

TEST(opt, opt) {
	char* arg[2] = { (char*)"foo", (char*)"--bar" };
	int argc = 2;
	argsParser parser;
	parser.addOpt("bar", 'b');

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
}
