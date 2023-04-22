#include <gtest/gtest.h>
#include <argsParser.h>

TEST(NoArgumentOpt, NoArgumentOpt) {
	char* arg[2] = { "foo", "--bar" };
	int argc = 2;
	argsParser parser;
	parser.addOpt("bar", 'b');

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
}

TEST(ArgumentOpt, ArgumentOpt) {
	char* arg[3] = { "foo", "--bar", "baz" };
	int argc = 3;
	argsParser parser;
	parser.addOpt("bar", 'b', "", true);

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
	EXPECT_EQ(parser.getArgument("bar"), "baz");
	EXPECT_EQ(parser.getArgument('b'), "baz");
}

TEST(ArgumentOptShort, ArgumentOptShort) {
	char* arg[3] = { "foo", "-b", "baz" };
	int argc = 3;
	argsParser parser;
	parser.addOpt("bar", 'b', "", true);

	ASSERT_TRUE(parser.parse(argc, arg));

	EXPECT_TRUE(parser.isOptSet("bar"));
	EXPECT_TRUE(parser.isOptSet('b'));
	EXPECT_EQ(parser.getArgument("bar"), "baz");
	EXPECT_EQ(parser.getArgument('b'), "baz");
}

TEST(MixedOpt, MixedOpt) {
	char* arg[6] = { "foo", "--bar", "baz", "-q", "quux" , "--corge" };
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

TEST(IncorrectInput, IncorrectInput) {
	char* iarg[2] = { "foo", "-bar" };
	int argc = 2;
	argsParser parser;

	EXPECT_FALSE(parser.parse(argc, iarg));

	parser.addOpt("bar", 'b', "", true);
	EXPECT_FALSE(parser.parse(argc, iarg));

	EXPECT_EQ(parser.getArgument("bar"), "");
	EXPECT_EQ(parser.getArgument('b'), "");
	EXPECT_THROW(parser.isOptSet("qux"), std::invalid_argument);
	EXPECT_THROW(parser.isOptSet('q'), std::invalid_argument);
	EXPECT_THROW(parser.getArgument("qux"), std::invalid_argument);
	EXPECT_THROW(parser.getArgument('q'), std::invalid_argument);
}