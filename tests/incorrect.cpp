#include <gtest/gtest.h>
#include <argsParser.h>

TEST(IncorrectInput, IncorrectInput) {
	char* iarg[2] = { (char*)"foo", (char*)"-bar" };
	int argc = 2;
	argsParser parser;

	EXPECT_FALSE(parser.parse(argc, iarg));
	EXPECT_THROW(parser.getArgument("bar"), std::invalid_argument);
	EXPECT_THROW(parser.getArgument('b'), std::invalid_argument);

	parser.addOpt("bar", 'b', "", true);
	EXPECT_FALSE(parser.parse(argc, iarg));

	EXPECT_EQ(parser.getArgument("bar"), "");
	EXPECT_EQ(parser.getArgument('b'), "");
	EXPECT_THROW(parser.isOptSet("qux"), std::invalid_argument);
	EXPECT_THROW(parser.isOptSet('q'), std::invalid_argument);
	EXPECT_THROW(parser.getArgument("qux"), std::invalid_argument);
	EXPECT_THROW(parser.getArgument('q'), std::invalid_argument);
}
