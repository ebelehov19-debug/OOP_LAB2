#include "src/string.h"
#include <gtest/gtest.h>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>

void expect_text(const String& value, const char* expected)
{
    EXPECT_EQ(value.size(), std::strlen(expected));
    EXPECT_STREQ(value.c_str(), expected);
    EXPECT_EQ(value.c_str()[value.size()], '\0');
}

TEST(StringConstruction, DefaultIsEmptyWithMinimumCapacity)
{
    const String value;
    expect_text(value, "");
    EXPECT_TRUE(value.empty());
    EXPECT_EQ(value.capacity(), 1u);
}

TEST(StringConstruction, FromCString)
{
    const String value("Hello");
    expect_text(value, "Hello");
    EXPECT_FALSE(value.empty());
}

TEST(StringRuleOfFive, CopyConstructor)
{
    const String source("abc");
    String copy(source);
    EXPECT_NE(copy.c_str(), source.c_str());
    copy.push_back('d');
    expect_text(copy, "abcd");
    expect_text(source, "abc");
}

TEST(StringRuleOfFive, MoveConstructor)
{
    String source("abc");
    const char* buffer = source.c_str();
    const String moved(std::move(source));
    expect_text(moved, "abc");
    EXPECT_EQ(moved.c_str(), buffer);
    expect_text(source, "");
    EXPECT_EQ(source.capacity(), 0u);
}

TEST(StringRuleOfFive, CopyAssignment)
{
    const String source("abc");
    String target("old");
    target = source;
    EXPECT_NE(target.c_str(), source.c_str());
    target.push_back('d');
    expect_text(target, "abcd");
    expect_text(source, "abc");
}

TEST(StringRuleOfFive, MoveAssignment)
{
    String source("abc");
    String target("old");
    const char* buffer = source.c_str();
    target = std::move(source);
    expect_text(target, "abc");
    EXPECT_EQ(target.c_str(), buffer);
    expect_text(source, "");
    EXPECT_EQ(source.capacity(), 0u);
}

TEST(StringRuleOfFive, SelfAssignment)
{
    String value("abc");
    String& other = value;
    value = other;
    expect_text(value, "abc");
    value = std::move(other);
    expect_text(value, "abc");
}

TEST(StringSwap, ExchangesStrings)
{
    String first("a");
    String second("hello");
    first.swap(second);
    expect_text(first, "hello");
    expect_text(second, "a");
    EXPECT_EQ(first.capacity(), 5u);
    EXPECT_EQ(second.capacity(), 1u);
    first.swap(first);
    expect_text(first, "hello");
}

TEST(StringPushBack, AddsCharactersAndDoublesCapacity)
{
    String value;
    value.push_back('a');
    EXPECT_EQ(value.capacity(), 1u);
    value.push_back('b');
    EXPECT_EQ(value.capacity(), 2u);
    value.push_back('c');
    EXPECT_EQ(value.capacity(), 4u);
    expect_text(value, "abc");
}

TEST(StringPushBack, WorksAfterMove)
{
    String source("abc");
    const String moved(std::move(source));
    source.push_back('x');
    expect_text(source, "x");
    EXPECT_EQ(source.capacity(), 1u);
    expect_text(moved, "abc");
}

TEST(StringAppend, AppendsCString)
{
    String value("Hello");
    value.append(", World!");
    expect_text(value, "Hello, World!");
    EXPECT_EQ(value.capacity(), 20u);
}

TEST(StringAppend, AppendsStringObject)
{
    String value("ab");
    const String suffix("cd");
    value.append(suffix);
    expect_text(value, "abcd");
    expect_text(suffix, "cd");
}

TEST(StringAppend, AppendsEmptyString)
{
    String value("abc");
    const String empty;
    value.append("");
    value.append(empty);
    expect_text(value, "abc");
}

TEST(StringAppend, AppendsItself)
{
    String value("abc");
    value.append(value);
    expect_text(value, "abcabc");
}

TEST(StringFind, FindsSubstring)
{
    const String value("Hello, World!");
    EXPECT_EQ(value.find("World"), 7u);
    EXPECT_EQ(value.find("Hello"), 0u);
    EXPECT_EQ(value.find("!"), 12u);
    EXPECT_EQ(value.find("missing"), String::npos);
    EXPECT_EQ(String("ababababac").find("ababac"), 4u);
}

TEST(StringPrint, PrintsString)
{
    const String value("Hello");
    std::ostringstream out;
    value.print(out);
    EXPECT_EQ(out.str(), "Hello");
    EXPECT_TRUE(out.good());
}

TEST(StringWrap, WrapsWordsAndKeepsOriginal)
{
    const String value("aa bb ccc");
    expect_text(value.wrap(4), "aa\nbb\nccc");
    expect_text(value.wrap(5), "aa bb\nccc");
    expect_text(value, "aa bb ccc");
}

TEST(StringWrap, EmptyStringAndSingleWord)
{
    const String empty;
    const String word("hello");
    expect_text(empty.wrap(4), "");
    expect_text(word.wrap(5), "hello");
    expect_text(String("   ").wrap(4), "");
}

TEST(StringWrap, KeepsLongWordsWhole)
{
    const String value("a longword b");
    expect_text(value.wrap(3), "a\nlongword\nb");
}

TEST(StringWrap, RejectsZeroWidth)
{
    const String value("abc");
    EXPECT_THROW(value.wrap(0), std::invalid_argument);
    expect_text(value, "abc");
}
