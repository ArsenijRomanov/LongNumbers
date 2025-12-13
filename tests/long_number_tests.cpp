#include <gtest/gtest.h>
#include <sstream>
#include "long_number.hpp"

using biv::LongNumber;

// ----------------------------------------------------------
// ZeroConstructor
// ----------------------------------------------------------

TEST(LongNumberConstructor, DefaultIsZero)
{
	LongNumber n = LongNumber();
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

// ----------------------------------------------------------
// StringConstructor
// ----------------------------------------------------------

TEST(LongNumberConstructor, NullStr)
{
	EXPECT_THROW(
		{
			LongNumber n(nullptr);
		},
		std::invalid_argument);
}

TEST(LongNumberConstructor, EmptyStr)
{
	EXPECT_THROW(
		LongNumber n(""),
		std::invalid_argument);
}

TEST(LongNumberConstructor, OnlyPlus)
{
	EXPECT_THROW(
		LongNumber n("+"),
		std::invalid_argument);
}

TEST(LongNumberConstructor, OnlyMinus)
{
	EXPECT_THROW(
		LongNumber n("-"),
		std::invalid_argument);
}

TEST(LongNumberConstructor, ZeroStr)
{
	LongNumber n = LongNumber("0");
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberConstructor, PositiveZero)
{
	LongNumber n = LongNumber("+0");
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberConstructor, NegativeZero)
{
	LongNumber n = LongNumber("-0");
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberConstructor, PositiveNumber)
{
	LongNumber n = LongNumber("+123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, PositiveNumberWithoutSign)
{
	LongNumber n = LongNumber("123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, ValidNegativeNumber)
{
	LongNumber n = LongNumber("-123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_TRUE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, PositiveNumberWithLeadingZeros)
{
	LongNumber n = LongNumber("00000123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, NegativeNumberWithLeadingZeros)
{
	LongNumber n = LongNumber("-00000123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_TRUE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, DoubleSign)
{
	EXPECT_THROW(
		LongNumber n("--123"),
		std::invalid_argument);
}

TEST(LongNumberConstructor, InvalidCharacters)
{
	EXPECT_THROW(
		LongNumber n("1284a13"),
		std::invalid_argument);
}

TEST(LongNumberConstructor, FiveZeros)
{
	LongNumber n = LongNumber("00000");

	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

// ----------------------------------------------------------
// CopyConstructor
// ----------------------------------------------------------

TEST(LongNumberConstructor, CopyPositiveNumber)
{
	LongNumber first = LongNumber("123");
	LongNumber second = LongNumber(first);

	EXPECT_EQ(first.is_negative(), second.is_negative());
	EXPECT_EQ(first.get_digits_number(), second.get_digits_number());
	EXPECT_EQ(first.get_rank_number(0), second.get_rank_number(0));
	EXPECT_EQ(first.get_rank_number(1), second.get_rank_number(1));
	EXPECT_EQ(first.get_rank_number(2), second.get_rank_number(2));

	LongNumber modified("999");
	second = modified;

	EXPECT_EQ(first.get_digits_number(), 3);
	EXPECT_EQ(first.get_rank_number(0), 3);
	EXPECT_EQ(first.get_rank_number(1), 2);
	EXPECT_EQ(first.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, CopyNegativeNumber)
{
	LongNumber first = LongNumber("-123");
	LongNumber second = LongNumber(first);

	EXPECT_EQ(first.is_negative(), second.is_negative());
	EXPECT_EQ(first.get_digits_number(), second.get_digits_number());
	EXPECT_EQ(first.get_rank_number(0), second.get_rank_number(0));
	EXPECT_EQ(first.get_rank_number(1), second.get_rank_number(1));
	EXPECT_EQ(first.get_rank_number(2), second.get_rank_number(2));

	LongNumber modified("999");
	second = modified;

	EXPECT_EQ(first.get_digits_number(), 3);
	EXPECT_EQ(first.get_rank_number(0), 3);
	EXPECT_EQ(first.get_rank_number(1), 2);
	EXPECT_EQ(first.get_rank_number(2), 1);
}

TEST(LongNumberConstructor, MoveConstructor)
{
	LongNumber original("12345");

	LongNumber moved(std::move(original));

	std::ostringstream oss;
	oss << moved;
	EXPECT_EQ(oss.str(), "12345");
	EXPECT_FALSE(moved.is_negative());
	EXPECT_EQ(moved.get_digits_number(), 5);
	EXPECT_EQ(moved.get_rank_number(0), 5);
	EXPECT_EQ(moved.get_rank_number(4), 1);

	EXPECT_EQ(original.get_digits_number(), 0);
	EXPECT_FALSE(original.is_negative());

	EXPECT_THROW(original.get_rank_number(0), std::out_of_range);
}

// ----------------------------------------------------------
// Assigment
// ----------------------------------------------------------

TEST(LongNumberAssignment, StringAssignment)
{
	LongNumber n = "123";
}

TEST(LongNumberAssignment, NullStr)
{
	EXPECT_THROW(
		{
			LongNumber n(nullptr);
		},
		std::invalid_argument);
}

TEST(LongNumberAssignment, EmptyStr)
{
	EXPECT_THROW(
		LongNumber n = "",
		std::invalid_argument);
}

TEST(LongNumberAssignment, OnlyPlus)
{
	EXPECT_THROW(
		LongNumber n = "+",
		std::invalid_argument);
}

TEST(LongNumberAssignment, OnlyMinus)
{
	EXPECT_THROW(
		LongNumber n = "-",
		std::invalid_argument);
}

TEST(LongNumberAssignment, ZeroStr)
{
	LongNumber n = "0";
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberAssignment, PositiveZero)
{
	LongNumber n = "+0";
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberAssignment, NegativeZero)
{
	LongNumber n = "-0";
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberAssignment, PositiveNumber)
{
	LongNumber n = "+123";
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, PositiveNumberWithoutSign)
{
	LongNumber n = "123";
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, ValidNegativeNumber)
{
	LongNumber n = "-123";
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_TRUE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, PositiveNumberWithLeadingZeros)
{
	LongNumber n = "00000123";
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, NegativeNumberWithLeadingZeros)
{
	LongNumber n = "-00000123";
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_TRUE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 3);
	EXPECT_EQ(n.get_rank_number(1), 2);
	EXPECT_EQ(n.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, DoubleSign)
{
	EXPECT_THROW(
		LongNumber n = "--123",
		std::invalid_argument);
}

TEST(LongNumberAssignment, InvalidCharacters)
{
	EXPECT_THROW(
		LongNumber n = "1284a13",
		std::invalid_argument);
}

TEST(LongNumberAssignment, FiveZeros)
{
	LongNumber n = "00000";

	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(n.get_rank_number(0), 0);
}

// ----------------------------------------------------------
// CopyAssigment
// ----------------------------------------------------------

TEST(LongNumberAssignment, AssignmentPositiveNumber)
{
	LongNumber first = LongNumber("123");
	LongNumber second = first;

	EXPECT_EQ(first.is_negative(), second.is_negative());
	EXPECT_EQ(first.get_digits_number(), second.get_digits_number());
	EXPECT_EQ(first.get_rank_number(0), second.get_rank_number(0));
	EXPECT_EQ(first.get_rank_number(1), second.get_rank_number(1));
	EXPECT_EQ(first.get_rank_number(2), second.get_rank_number(2));

	LongNumber modified("999");
	second = modified;

	EXPECT_EQ(first.get_digits_number(), 3);
	EXPECT_EQ(first.get_rank_number(0), 3);
	EXPECT_EQ(first.get_rank_number(1), 2);
	EXPECT_EQ(first.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, AssignmentNegativeNumber)
{
	LongNumber first = LongNumber("-123");
	LongNumber second = first;

	EXPECT_EQ(first.is_negative(), second.is_negative());
	EXPECT_EQ(first.get_digits_number(), second.get_digits_number());
	EXPECT_EQ(first.get_rank_number(0), second.get_rank_number(0));
	EXPECT_EQ(first.get_rank_number(1), second.get_rank_number(1));
	EXPECT_EQ(first.get_rank_number(2), second.get_rank_number(2));

	LongNumber modified("999");
	second = modified;

	EXPECT_EQ(first.get_digits_number(), 3);
	EXPECT_EQ(first.get_rank_number(0), 3);
	EXPECT_EQ(first.get_rank_number(1), 2);
	EXPECT_EQ(first.get_rank_number(2), 1);
}

TEST(LongNumberAssignment, MoveAssignment)
{
	LongNumber src("12345");
	LongNumber dst("999");

	dst = std::move(src);

	std::ostringstream oss;
	oss << dst;
	EXPECT_EQ(oss.str(), "12345");
	EXPECT_EQ(dst.get_digits_number(), 5);
	EXPECT_FALSE(dst.is_negative());
	EXPECT_EQ(dst.get_rank_number(0), 5);
	EXPECT_EQ(dst.get_rank_number(4), 1);

	EXPECT_EQ(src.get_digits_number(), 0);
	EXPECT_FALSE(src.is_negative());
	EXPECT_THROW(src.get_rank_number(0), std::out_of_range);
}

// ----------------------------------------------------------
// Equals
// ----------------------------------------------------------

TEST(LongNumbersEquals, SameNumbers)
{
	LongNumber first("123");
	LongNumber second("123");

	EXPECT_TRUE(first == second);
}

TEST(LongNumbersEquals, DifferentNumbers)
{
	LongNumber first("123");
	LongNumber second("12345");

	EXPECT_FALSE(first == second);
}

TEST(LongNumbersEquals, DifferentSigns)
{
	LongNumber first("123");
	LongNumber second("-123");

	EXPECT_FALSE(first == second);
}

// ----------------------------------------------------------
// NotEquals
// ----------------------------------------------------------

TEST(LongNumbersNotEquals, SameNumbers)
{
	LongNumber first("123");
	LongNumber second("123");

	EXPECT_FALSE(first != second);
}

TEST(LongNumbersNotEquals, DifferentNumbers)
{
	LongNumber first("123");
	LongNumber second("12345");

	EXPECT_TRUE(first != second);
}

TEST(LongNumbersNotEquals, DifferentSigns)
{
	LongNumber first("123");
	LongNumber second("-123");

	EXPECT_TRUE(first != second);
}

// ----------------------------------------------------------
// GreaterThan
// ----------------------------------------------------------

TEST(LongNumbersGreaterThan, FirstGreater)
{
	LongNumber first("9");
	LongNumber second("5");

	EXPECT_TRUE(first > second);
}

TEST(LongNumbersGreaterThan, SecondGreater)
{
	LongNumber first("5");
	LongNumber second("9");

	EXPECT_FALSE(first > second);
}

TEST(LongNumbersGreaterThan, SameNumbers)
{
	LongNumber first("5");
	LongNumber second("5");

	EXPECT_FALSE(first > second);
}

TEST(LongNumbersGreaterThan, FirstLonger)
{
	LongNumber first("99999999999999999999999");
	LongNumber second("5");

	EXPECT_TRUE(first > second);
}

TEST(LongNumbersGreaterThan, SecondLonger)
{
	LongNumber first("5");
	LongNumber second("99999999999999999999999");

	EXPECT_FALSE(first > second);
}

TEST(LongNumbersGreaterThan, NegativeFirstGreater)
{
	LongNumber first("-5");
	LongNumber second("-9");

	EXPECT_TRUE(first > second);
}

TEST(LongNumbersGreaterThan, NegativeSecondGreater)
{
	LongNumber first("-9");
	LongNumber second("-5");

	EXPECT_FALSE(first > second);
}

TEST(LongNumbersGreaterThan, FirstNegativeSecondPositive)
{
	LongNumber first("-5");
	LongNumber second("5");

	EXPECT_FALSE(first > second);
}

TEST(LongNumbersGreaterThan, SecondNegativeFirstPositive)
{
	LongNumber first("5");
	LongNumber second("-5");

	EXPECT_TRUE(first > second);
}

// ----------------------------------------------------------
// LessThan
// ----------------------------------------------------------

TEST(LongNumbersLessThan, FirstGreater)
{
	LongNumber first("9");
	LongNumber second("5");

	EXPECT_FALSE(first < second);
}

TEST(LongNumbersLessThan, SecondGreater)
{
	LongNumber first("5");
	LongNumber second("9");

	EXPECT_TRUE(first < second);
}

TEST(LongNumbersLessThan, SameNumbers)
{
	LongNumber first("5");
	LongNumber second("5");

	EXPECT_FALSE(first < second);
}

TEST(LongNumbersLessThan, FirstLonger)
{
	LongNumber first("99999999999999999999999");
	LongNumber second("5");

	EXPECT_FALSE(first < second);
}

TEST(LongNumbersLessThan, SecondLonger)
{
	LongNumber first("5");
	LongNumber second("99999999999999999999999");

	EXPECT_TRUE(first < second);
}

TEST(LongNumbersLessThan, NegativeFirstGreater)
{
	LongNumber first("-5");
	LongNumber second("-9");

	EXPECT_FALSE(first < second);
}

TEST(LongNumbersLessThan, NegativeSecondGreater)
{
	LongNumber first("-9");
	LongNumber second("-5");

	EXPECT_TRUE(first < second);
}

TEST(LongNumbersLessThan, FirstNegativeSecondPositive)
{
	LongNumber first("-5");
	LongNumber second("5");

	EXPECT_TRUE(first < second);
}

TEST(LongNumbersLessThan, SecondNegativeFirstPositive)
{
	LongNumber first("5");
	LongNumber second("-5");

	EXPECT_FALSE(first < second);
}

// ----------------------------------------------------------
// Addition
// ----------------------------------------------------------

static std::string ToString(const LongNumber &n)
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

TEST(LongNumberAddition, ZeroPlusZero)
{
	LongNumber a("0");
	LongNumber b("0");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "0");
	EXPECT_FALSE(s.is_negative());
	EXPECT_EQ(s.get_digits_number(), 1);
}

TEST(LongNumberAddition, ZeroPlusPositive)
{
	LongNumber a("0");
	LongNumber b("123456789");

	LongNumber s1 = a + b;
	LongNumber s2 = b + a;

	EXPECT_EQ(ToString(s1), "123456789");
	EXPECT_EQ(ToString(s2), "123456789");
}

TEST(LongNumberAddition, ZeroPlusNegative)
{
	LongNumber a("0");
	LongNumber b("-987654321");

	LongNumber s1 = a + b;
	LongNumber s2 = b + a;

	EXPECT_EQ(ToString(s1), "-987654321");
	EXPECT_EQ(ToString(s2), "-987654321");
}

TEST(LongNumberAddition, SimplePositiveNoCarry)
{
	LongNumber a("123");
	LongNumber b("456");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "579");
}

TEST(LongNumberAddition, SimplePositiveWithCarry)
{
	LongNumber a("999");
	LongNumber b("1");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "1000");
}

TEST(LongNumberAddition, DifferentLengthsPositive)
{
	LongNumber a("123456789");
	LongNumber b("987");

	LongNumber s1 = a + b;
	LongNumber s2 = b + a;

	EXPECT_EQ(ToString(s1), "123457776");
	EXPECT_EQ(ToString(s2), "123457776");
}

TEST(LongNumberAddition, BothNegative)
{
	LongNumber a("-123");
	LongNumber b("-4567");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "-4690");
	EXPECT_TRUE(s.is_negative());
}

TEST(LongNumberAddition, PositivePlusNegativeSameAbs)
{
	LongNumber a("1000");
	LongNumber b("-1000");

	LongNumber s1 = a + b;
	LongNumber s2 = b + a;

	EXPECT_EQ(ToString(s1), "0");
	EXPECT_EQ(ToString(s2), "0");
	EXPECT_FALSE(s1.is_negative());
}

TEST(LongNumberAddition, PositivePlusNegativeAbsGreaterFirst)
{
	LongNumber a("1000");
	LongNumber b("-1");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "999");
	EXPECT_FALSE(s.is_negative());
}

TEST(LongNumberAddition, PositivePlusNegativeAbsGreaterSecond)
{
	LongNumber a("1000");
	LongNumber b("-5000");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "-4000");
	EXPECT_TRUE(s.is_negative());
}

TEST(LongNumberAddition, NegativePlusPositive)
{
	LongNumber a("-1000");
	LongNumber b("1");

	LongNumber s = a + b;
	EXPECT_EQ(ToString(s), "-999");
	EXPECT_TRUE(s.is_negative());
}

TEST(LongNumberAddition, VeryLongNumbersWithCarries)
{
	std::string s1(50, '9');
	std::string s2(50, '1');

	LongNumber a(s1.c_str());
	LongNumber b(s2.c_str());

	LongNumber s = a + b;

	std::string expected = "1";
	expected += std::string(49, '1');
	expected += "0";

	EXPECT_EQ(ToString(s), expected);
	EXPECT_EQ(s.get_digits_number(), static_cast<int>(expected.size()));
}

TEST(LongNumberAddition, VeryLongAndShort)
{
	std::string big(100, '8');
	LongNumber a(big.c_str());
	LongNumber b("5");

	LongNumber s = a + b;

	std::string expected(100, '8');
	int carry = 5;
	for (int i = 99; i >= 0; --i)
	{
		int digit = (expected[i] - '0') + carry;
		expected[i] = char('0' + (digit % 10));
		carry = digit / 10;
	}
	if (carry > 0)
		expected.insert(expected.begin(), char('0' + carry));

	EXPECT_EQ(ToString(s), expected);
}

TEST(LongNumberAddition, CommutativityForLongNumbers)
{
	LongNumber a("1234567890123456789012345678901234567890");
	LongNumber b("9876543210987654321098765432109876543210");

	LongNumber s1 = a + b;
	LongNumber s2 = b + a;

	EXPECT_EQ(ToString(s1), ToString(s2));
}

// ----------------------------------------------------------
// Subtraction
// ----------------------------------------------------------

TEST(LongNumberSubtraction, ZeroMinusZero)
{
	LongNumber a("0");
	LongNumber b("0");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "0");
	EXPECT_FALSE(d.is_negative());
	EXPECT_EQ(d.get_digits_number(), 1);
}

TEST(LongNumberSubtraction, ZeroMinusPositive)
{
	LongNumber a("0");
	LongNumber b("123456");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "-123456");
	EXPECT_TRUE(d.is_negative());
}

TEST(LongNumberSubtraction, ZeroMinusNegative)
{
	LongNumber a("0");
	LongNumber b("-123456");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "123456");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, PositiveMinusZero)
{
	LongNumber a("987654321");
	LongNumber b("0");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "987654321");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, NegativeMinusZero)
{
	LongNumber a("-987654321");
	LongNumber b("0");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "-987654321");
	EXPECT_TRUE(d.is_negative());
}

TEST(LongNumberSubtraction, SamePositiveGivesZero)
{
	LongNumber a("123456789");
	LongNumber b("123456789");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "0");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, SameNegativeGivesZero)
{
	LongNumber a("-123456789");
	LongNumber b("-123456789");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "0");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, PositiveMinusSmallerPositive)
{
	LongNumber a("1000");
	LongNumber b("1");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "999");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, PositiveMinusGreaterPositive)
{
	LongNumber a("1");
	LongNumber b("1000");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "-999");
	EXPECT_TRUE(d.is_negative());
}

TEST(LongNumberSubtraction, NegativeMinusPositive)
{
	LongNumber a("-1000");
	LongNumber b("1");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "-1001");
	EXPECT_TRUE(d.is_negative());
}

TEST(LongNumberSubtraction, PositiveMinusNegative)
{
	LongNumber a("1000");
	LongNumber b("-1");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "1001");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, NegativeMinusGreaterNegative)
{
	LongNumber a("-5");
	LongNumber b("-10");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "5");
	EXPECT_FALSE(d.is_negative());
}

TEST(LongNumberSubtraction, NegativeMinusSmallerNegative)
{
	LongNumber a("-10");
	LongNumber b("-5");

	LongNumber d = a - b;
	EXPECT_EQ(ToString(d), "-5");
	EXPECT_TRUE(d.is_negative());
}

TEST(LongNumberSubtraction, VeryLongNumbersNoBorrow)
{
	std::string s1(100, '9');
	std::string s2(100, '1');

	LongNumber a(s1.c_str());
	LongNumber b(s2.c_str());

	LongNumber d = a - b;

	std::string expected(100, '8');
	EXPECT_EQ(ToString(d), expected);
}

TEST(LongNumberSubtraction, VeryLongNumbersWithBorrow)
{
	std::string s1(100, '0');
	s1[0] = '1';
	LongNumber a(s1.c_str());
	LongNumber b("1");

	LongNumber d = a - b;

	std::string expected(99, '9');
	EXPECT_EQ(ToString(d), expected);
	EXPECT_FALSE(d.is_negative());
}

// ----------------------------------------------------------
// Multiplication
// ----------------------------------------------------------


TEST(LongNumberMultiplication, ZeroTimesZero)
{
	LongNumber a("0");
	LongNumber b("0");

	LongNumber p = a * b;
	EXPECT_EQ(ToString(p), "0");
	EXPECT_FALSE(p.is_negative());
	EXPECT_EQ(p.get_digits_number(), 1);
}

TEST(LongNumberMultiplication, ZeroTimesPositive)
{
	LongNumber a("0");
	LongNumber b("123456789");

	LongNumber p1 = a * b;
	LongNumber p2 = b * a;

	EXPECT_EQ(ToString(p1), "0");
	EXPECT_EQ(ToString(p2), "0");
	EXPECT_FALSE(p1.is_negative());
	EXPECT_FALSE(p2.is_negative());
}

TEST(LongNumberMultiplication, ZeroTimesNegative)
{
	LongNumber a("0");
	LongNumber b("-987654321");

	LongNumber p1 = a * b;
	LongNumber p2 = b * a;

	EXPECT_EQ(ToString(p1), "0");
	EXPECT_EQ(ToString(p2), "0");
	EXPECT_FALSE(p1.is_negative());
	EXPECT_FALSE(p2.is_negative());
}

TEST(LongNumberMultiplication, SimplePositive)
{
	LongNumber a("12");
	LongNumber b("34");

	LongNumber p = a * b;
	EXPECT_EQ(ToString(p), "408");
	EXPECT_FALSE(p.is_negative());
}

TEST(LongNumberMultiplication, ByTen)
{
	LongNumber a("12345");
	LongNumber b("10");

	LongNumber p1 = a * b;
	LongNumber p2 = b * a;

	EXPECT_EQ(ToString(p1), "123450");
	EXPECT_EQ(ToString(p2), "123450");
}

TEST(LongNumberMultiplication, PositiveTimesNegative)
{
	LongNumber a("123");
	LongNumber b("-10");

	LongNumber p1 = a * b;
	LongNumber p2 = b * a;

	EXPECT_EQ(ToString(p1), "-1230");
	EXPECT_EQ(ToString(p2), "-1230");
	EXPECT_TRUE(p1.is_negative());
	EXPECT_TRUE(p2.is_negative());
}

TEST(LongNumberMultiplication, NegativeTimesNegative)
{
	LongNumber a("-123");
	LongNumber b("-10");

	LongNumber p = a * b;

	EXPECT_EQ(ToString(p), "1230");
	EXPECT_FALSE(p.is_negative());
}

TEST(LongNumberMultiplication, VeryLongNumbers)
{
	std::string s(50, '9');

	LongNumber a(s.c_str());
	LongNumber b(s.c_str());

	LongNumber p = a * b;

	std::string expected = std::string(49, '9') + "8" + std::string(49, '0') + "1";

	EXPECT_EQ(ToString(p), expected);
}

TEST(LongNumberMultiplication, OneTimesVeryLong)
{
	std::string s(100, '7');
	LongNumber a("1");
	LongNumber b(s.c_str());

	LongNumber p1 = a * b;
	LongNumber p2 = b * a;

	EXPECT_EQ(ToString(p1), s);
	EXPECT_EQ(ToString(p2), s);
}

// a / b, a / (-b), -a / b, -a / (-b)
// ----------------------------------------------------------
// Division
// ----------------------------------------------------------

TEST(LongNumberDivision, MathRulesSignCombinations)
{
    LongNumber a("7");
    LongNumber b("3");
    LongNumber neg_a("-7");
    LongNumber neg_b("-3");

    EXPECT_EQ(ToString(a / b), "2");
    EXPECT_EQ(ToString(a % b), "1");

    EXPECT_EQ(ToString(a / neg_b), "-2");
    EXPECT_EQ(ToString(a % neg_b), "1");

    EXPECT_EQ(ToString(neg_a / b), "-3");
    EXPECT_EQ(ToString(neg_a % b), "2");

    EXPECT_EQ(ToString(neg_a / neg_b), "3");
    EXPECT_EQ(ToString(neg_a % neg_b), "2");
}

TEST(LongNumberDivision, MathRulesExactDivision)
{
    LongNumber a("-6");
    LongNumber b("2");
    LongNumber neg_b("-2");

    EXPECT_EQ(ToString(a / b), "-3");
    EXPECT_EQ(ToString(a % b), "0");

    EXPECT_EQ(ToString(a / neg_b), "3");
    EXPECT_EQ(ToString(a % neg_b), "0");
}

TEST(LongNumberDivision, MathRulesLargeNumbers)
{
    LongNumber a("-105");
    LongNumber b("10");

    EXPECT_EQ(ToString(a / b), "-11");
    EXPECT_EQ(ToString(a % b), "5");

    LongNumber q = a / b;
    LongNumber r = a % b;

    EXPECT_EQ(ToString(q * b + r), "-105");
}

TEST(LongNumberDivision, DivisionByZeroThrows)
{
	LongNumber a("12345");
	LongNumber z("0");

	EXPECT_THROW(a / z, std::invalid_argument);
}

TEST(LongNumberDivision, ZeroDividedByNonZeroIsZero)
{
	LongNumber z("0");
	LongNumber b("12345");

	LongNumber q1 = z / b;
	LongNumber q2 = z / LongNumber("-999");

	EXPECT_EQ(ToString(q1), "0");
	EXPECT_EQ(ToString(q2), "0");
	EXPECT_FALSE(q1.is_negative());
	EXPECT_FALSE(q2.is_negative());
}

TEST(LongNumberDivision, SmallerDividendThanDivisorIsZero)
{
	LongNumber a("5");
	LongNumber b("10");

	LongNumber q = a / b;
	EXPECT_EQ(ToString(q), "0");
	EXPECT_FALSE(q.is_negative());
}

TEST(LongNumberDivision, DivideByOneKeepsValueAndSign)
{
	LongNumber a("123456789");
	LongNumber b("1");

	LongNumber q1 = a / b;
	LongNumber q2 = LongNumber("-123456789") / b;

	EXPECT_EQ(ToString(q1), "123456789");
	EXPECT_FALSE(q1.is_negative());

	EXPECT_EQ(ToString(q2), "-123456789");
	EXPECT_TRUE(q2.is_negative());
}

TEST(LongNumberDivision, DivideByMinusOneFlipsSign)
{
	LongNumber a("123456789");
	LongNumber b("-1");

	LongNumber q = a / b;

	EXPECT_EQ(ToString(q), "-123456789");
	EXPECT_TRUE(q.is_negative());
}

TEST(LongNumberDivision, SimpleExactDivisionPositive)
{
	LongNumber a("1000");
	LongNumber b("10");

	LongNumber q = a / b;
	EXPECT_EQ(ToString(q), "100");
	EXPECT_FALSE(q.is_negative());
}

TEST(LongNumberDivision, SimpleExactDivisionNegative)
{
	LongNumber a("-1000");
	LongNumber b("10");

	LongNumber q = a / b;
	EXPECT_EQ(ToString(q), "-100");
	EXPECT_TRUE(q.is_negative());
}

TEST(LongNumberDivision, SimpleDivisionWithRemainder)
{
	LongNumber a("1234");
	LongNumber b("10");

	LongNumber q = a / b;
	EXPECT_EQ(ToString(q), "123");

	LongNumber r = a % b;
	EXPECT_EQ(ToString(r), "4");
}

TEST(LongNumberDivision, SignsWithRemainder)
{
	LongNumber a("1234");
	LongNumber b("-10");

	LongNumber q1 = a / b;
	LongNumber r1 = a % b;

	EXPECT_EQ(ToString(q1), "-123");
	EXPECT_TRUE(q1.is_negative());
	EXPECT_EQ(ToString(r1), "4");
	EXPECT_FALSE(r1.is_negative());

	LongNumber a2("-1234");
	LongNumber b2("10");

	LongNumber q2 = a2 / b2;
	LongNumber r2 = a2 % b2;

	EXPECT_EQ(ToString(q2), "-124");
	EXPECT_TRUE(q2.is_negative());
	EXPECT_EQ(ToString(r2), "6");
	EXPECT_FALSE(r2.is_negative());

	LongNumber q3 = a2 / b;
	LongNumber r3 = a2 % b;

	EXPECT_EQ(ToString(q3), "124");
	EXPECT_FALSE(q3.is_negative());
	EXPECT_EQ(ToString(r3), "6");
	EXPECT_FALSE(r3.is_negative());
}

TEST(LongNumberDivision, LargeNumbersExact)
{
	LongNumber a("999999999000000000");
	LongNumber b("3");

	LongNumber q = a / b;

	EXPECT_EQ(ToString(q), "333333333000000000");
	EXPECT_FALSE(q.is_negative());
}

TEST(LongNumberDivision, LargeNumbersWithRemainder)
{
	LongNumber a("100000000000000000000");
	LongNumber b("7");

	LongNumber q = a / b;
	LongNumber r = a % b;

	LongNumber check = q * b + r;

	EXPECT_EQ(ToString(check), ToString(a));
	EXPECT_TRUE(r.get_digits_number() >= 1);
	EXPECT_TRUE(r < b);
}

TEST(LongNumberDivision, DividendEqualsDivisorGivesOne)
{
	LongNumber a("12345678901234567890");
	LongNumber b("12345678901234567890");

	LongNumber q = a / b;
	LongNumber r = a % b;

	EXPECT_EQ(ToString(q), "1");
	EXPECT_EQ(ToString(r), "0");
}

// ----------------------------------------------------------
// Remainder
// ----------------------------------------------------------

TEST(LongNumberRemainder, DivisionByZeroThrows)
{
	LongNumber a("123");
	LongNumber zero("0");

	EXPECT_THROW(a % zero, std::invalid_argument);
}

TEST(LongNumberRemainder, ZeroModNonZeroIsZero)
{
	LongNumber a("0");
	LongNumber b("123");

	LongNumber r = a % b;
	EXPECT_EQ(ToString(r), "0");
	EXPECT_FALSE(r.is_negative());
}

TEST(LongNumberRemainder, PositiveDividendPositiveDivisor)
{
	LongNumber a("1234");
	LongNumber b("10");

	LongNumber q = a / b;
	LongNumber r = a % b;

	EXPECT_EQ(ToString(q), "123");
	EXPECT_EQ(ToString(r), "4");

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
}

TEST(LongNumberRemainder, PositiveDividendNegativeDivisor)
{
	LongNumber a("1234");
	LongNumber b("-10");

	LongNumber q = a / b;
	LongNumber r = a % b;

	EXPECT_EQ(ToString(q), "-123");
	EXPECT_EQ(ToString(r), "4");

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
}

TEST(LongNumberRemainder, NegativeDividendPositiveDivisor)
{
	LongNumber a("-1234");
	LongNumber b("10");

	LongNumber q = a / b;
	LongNumber r = a % b;

	EXPECT_EQ(ToString(q), "-124");
	EXPECT_EQ(ToString(r), "6");

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
}

TEST(LongNumberRemainder, NegativeDividendNegativeDivisor)
{
	LongNumber a("-1234");
	LongNumber b("-10");

	LongNumber q = a / b;
	LongNumber r = a % b;

	EXPECT_EQ(ToString(q), "124");
	EXPECT_EQ(ToString(r), "6");

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
}

TEST(LongNumberRemainder, VeryLongNumberModSmallPositive)
{
	std::string big(100, '9');
	LongNumber a(big.c_str());
	LongNumber b("97");

	LongNumber q = a / b;
	LongNumber r = a % b;

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
	EXPECT_TRUE(r < b);
	EXPECT_FALSE(r.is_negative());
}

TEST(LongNumberRemainder, VeryLongNumbersMod)
{
	std::string s1 = "12345678901234567890123456789012345678901234567890";
	std::string s2 = "98765432109876543210";

	LongNumber a(s1.c_str());
	LongNumber b(s2.c_str());

	LongNumber q = a / b;
	LongNumber r = a % b;

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
	EXPECT_TRUE(r < b);
}

TEST(LongNumberRemainder, VeryLongNegativeDividend)
{
	std::string s = "1234567890123456789012345678901234567890";
	LongNumber a(("-" + s).c_str());
	LongNumber b("12345");

	LongNumber q = a / b;
	LongNumber r = a % b;

	LongNumber check = q * b + r;
	EXPECT_EQ(ToString(check), ToString(a));
}

// ----------------------------------------------------------
// GetLength
// ----------------------------------------------------------

TEST(LongNumberGetDigitsNumber, DefaultConstructorIsOne)
{
	LongNumber n;
	EXPECT_EQ(n.get_digits_number(), 1);
	EXPECT_EQ(ToString(n), "0");
}

TEST(LongNumberGetDigitsNumber, PositiveNumberNoLeadingZeros)
{
	LongNumber n("123456");
	EXPECT_EQ(n.get_digits_number(), 6);
}

TEST(LongNumberGetDigitsNumber, NegativeNumber)
{
	LongNumber n("-987654321");
	EXPECT_EQ(n.get_digits_number(), 9);
	EXPECT_TRUE(n.is_negative());
}

TEST(LongNumberGetDigitsNumber, LeadingZerosPositive)
{
	LongNumber n("0000123");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_EQ(ToString(n), "123");
}

TEST(LongNumberGetDigitsNumber, LeadingZerosNegative)
{
	LongNumber n("-0000456");
	EXPECT_EQ(n.get_digits_number(), 3);
	EXPECT_EQ(ToString(n), "-456");
}

TEST(LongNumberGetDigitsNumber, VeryLongNumber)
{
	std::string s(100, '9');
	LongNumber n(s.c_str());
	EXPECT_EQ(n.get_digits_number(), 100);
}

// ----------------------------------------------------------
// GetRankNumber
// ----------------------------------------------------------

TEST(LongNumberGetRankNumber, SimplePositive)
{
	LongNumber n("12345");

	EXPECT_EQ(n.get_rank_number(0), 5);
	EXPECT_EQ(n.get_rank_number(1), 4);
	EXPECT_EQ(n.get_rank_number(2), 3);
	EXPECT_EQ(n.get_rank_number(3), 2);
	EXPECT_EQ(n.get_rank_number(4), 1);
}

TEST(LongNumberGetRankNumber, SimpleNegative)
{
	LongNumber n("-908");

	EXPECT_EQ(n.get_rank_number(0), 8);
	EXPECT_EQ(n.get_rank_number(1), 0);
	EXPECT_EQ(n.get_rank_number(2), 9);
}

TEST(LongNumberGetRankNumber, Zero)
{
	LongNumber n("0");
	EXPECT_EQ(n.get_rank_number(0), 0);
}

TEST(LongNumberGetRankNumber, OutOfRangePositiveIndex)
{
	LongNumber n("123");

	EXPECT_THROW(n.get_rank_number(3), std::out_of_range);
	EXPECT_THROW(n.get_rank_number(10), std::out_of_range);
}

TEST(LongNumberGetRankNumber, OutOfRangeNegativeIndex)
{
	LongNumber n("123");

	EXPECT_THROW(n.get_rank_number(-1), std::out_of_range);
}

// ----------------------------------------------------------
// IsNegative
// ----------------------------------------------------------

TEST(LongNumberIsNegative, DefaultIsNotNegative)
{
	LongNumber n;
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(ToString(n), "0");
}

TEST(LongNumberIsNegative, PositiveNumber)
{
	LongNumber n("12345");
	EXPECT_FALSE(n.is_negative());
}

TEST(LongNumberIsNegative, NegativeNumber)
{
	LongNumber n("-12345");
	EXPECT_TRUE(n.is_negative());
}

TEST(LongNumberIsNegative, MinusZeroBecomesNonNegative)
{
	LongNumber n("-0000");
	EXPECT_FALSE(n.is_negative());
	EXPECT_EQ(ToString(n), "0");
}

TEST(LongNumberIsNegative, ResultOfSubtraction)
{
	LongNumber a("5");
	LongNumber b("10");

	LongNumber d = a - b;
	EXPECT_TRUE(d.is_negative());
	EXPECT_EQ(ToString(d), "-5");
}

TEST(LongNumberIsNegative, ResultOfMultiplication)
{
	LongNumber a("2");
	LongNumber b("-3");
	LongNumber c("-4");

	LongNumber p1 = a * b;
	LongNumber p2 = b * c;

	EXPECT_TRUE(p1.is_negative());
	EXPECT_FALSE(p2.is_negative());
}

// ----------------------------------------------------------
// Operator
// ----------------------------------------------------------

TEST(LongNumberOstream, Zero)
{
	LongNumber n("0");
	EXPECT_EQ(ToString(n), "0");
}

TEST(LongNumberOstream, DefaultConstructor)
{
	LongNumber n;
	EXPECT_EQ(ToString(n), "0");
}

TEST(LongNumberOstream, PositiveNumber)
{
	LongNumber n("123456789");
	EXPECT_EQ(ToString(n), "123456789");
}

TEST(LongNumberOstream, NegativeNumber)
{
	LongNumber n("-987654321");
	EXPECT_EQ(ToString(n), "-987654321");
}

TEST(LongNumberOstream, LeadingZerosPositive)
{
	LongNumber n("0000123");
	EXPECT_EQ(ToString(n), "123");
}

TEST(LongNumberOstream, LeadingZerosNegative)
{
	LongNumber n("-0000456");
	EXPECT_EQ(ToString(n), "-456");
}

TEST(LongNumberOstream, VeryLongNumber)
{
	std::string s(100, '9');
	LongNumber n(s.c_str());
	EXPECT_EQ(ToString(n), s);
}
