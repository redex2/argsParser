#include <gtest/gtest.h>
#include <argsParser.h>

TEST(optShort, optShort) {
	char* arg[2] = { (char*)"foo", (char*)"-b" };
	int argc = 2;
	argsParser parser;
	parser.addOpt("bar", 'b', "", false);

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
	EXPECT_THROW(parser.getArgument("bar"), std::invalid_argument);
	EXPECT_THROW(parser.getArgument('b'), std::invalid_argument);
}
