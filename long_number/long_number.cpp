#include "long_number.hpp"
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>

using biv::LongNumber;

LongNumber::LongNumber()
{
	numbers = new int[1]{0};
	length = 1;
	sign = 1;
}

namespace
{
	enum class ParseState
	{
		Start,
		Sign,
		Zeros,
		Digits,
		Dead
	};

	ParseState transition_function(ParseState state, char c)
	{
		switch (state)
		{

		case ParseState::Start:
			switch (c)
			{
			case '0':
				return ParseState::Zeros;

			case '+':
			case '-':
				return ParseState::Sign;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return ParseState::Digits;

			default:
				return ParseState::Dead;
			}

		case ParseState::Sign:
			switch (c)
			{
			case '0':
				return ParseState::Zeros;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return ParseState::Digits;

			default:
				return ParseState::Dead;
			}

		case ParseState::Zeros:
			switch (c)
			{
			case '0':
				return ParseState::Zeros;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return ParseState::Digits;

			default:
				return ParseState::Dead;
			}

		case ParseState::Digits:
			switch (c)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return ParseState::Digits;

			default:
				return ParseState::Dead;
			}

		case ParseState::Dead:

		default:
			return ParseState::Dead;
		}
	}

	LongNumber TenPow(u_int64_t n)
	{
		std::string s = "1" + std::string(n, '0');
		return LongNumber(s.c_str());
	}
}

LongNumber::LongNumber(const char *const str)
{
	if (str == nullptr || str[0] == '\0')
	{
		throw std::invalid_argument("empty string is not a valid LongNumber");
	}

	sign = 1;

	std::vector<int> tmp;
	ParseState state = ParseState::Start;

	for (int i = 0; str[i] != '\0'; ++i)
	{
		char c = str[i];
		state = transition_function(state, c);

		if (state == ParseState::Dead)
			throw std::invalid_argument(std::string("not a valid LongNumber: '") + str + "'");

		if (state == ParseState::Sign)
		{
			if (c == '-')
				sign = -1;
		}
		else if (state == ParseState::Digits)
		{
			tmp.push_back(c - '0');
		}
	}

	if (state == ParseState::Digits)
	{
		length = static_cast<int>(tmp.size());
		numbers = new int[length];
		for (int i = 0; i < length; ++i)
		{
			numbers[i] = tmp[length - 1 - i];
		}
		return;
	}

	else if (state == ParseState::Zeros)
	{
		sign = 1;
		length = 1;
		numbers = new int[1]{0};
		return;
	}

	throw std::invalid_argument(std::string("not a valid LongNumber: '") + str + "'");
}

LongNumber::LongNumber(const LongNumber &x)
{
	length = x.length;
	sign = x.sign;

	numbers = new int[length];
	for (int i = 0; i < length; ++i)
		numbers[i] = x.numbers[i];
}

LongNumber::LongNumber(LongNumber &&x)
{
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;

	x.length = 0;
	x.sign = 1;
	x.numbers = nullptr;
}

LongNumber::~LongNumber()
{
	delete[] numbers;
}

LongNumber &LongNumber::operator=(const char *const str)
{
	LongNumber tmp(str);
	return *this = tmp;
}

// Лишнее? Почему?
LongNumber &LongNumber::operator=(const LongNumber &x)
{
	if (this == &x)
		return *this;

	return *this = LongNumber(x);
}

LongNumber &LongNumber::operator=(LongNumber &&x)
{
	if (this == &x)
	{
		return *this;
	}

	delete[] numbers;

	numbers = x.numbers;
	length = x.length;
	sign = x.sign;

	x.numbers = nullptr;
	x.length = 0;
	x.sign = 1;

	return *this;
}

bool LongNumber::operator==(const LongNumber &x) const
{
	return sign == x.sign && length == x.length && std::equal(numbers, numbers + length, x.numbers);
}

bool LongNumber::operator!=(const LongNumber &x) const
{
	return !(*this == x);
}

bool LongNumber::operator>(const LongNumber &x) const
{
	if (sign > x.sign)
		return true;
	if (sign < x.sign)
		return false;
	if (length > x.length)
		return (sign == 1);
	if (length < x.length)
		return (sign == -1);

	for (int i = length - 1; i >= 0; --i)
	{
		if (numbers[i] != x.numbers[i])
			return ((numbers[i] > x.numbers[i]) == (sign == 1));
	}

	return false;
}

bool LongNumber::operator<(const LongNumber &x) const
{
	return !(*this > x) && (*this != x);
}

LongNumber LongNumber::operator+(const LongNumber &x) const
{
	if (sign == 1 && x.sign == -1)
	{
		auto subtrahend = x;
		subtrahend.sign = 1;
		return *this - subtrahend;
	}

	else if (sign == -1 && x.sign == 1)
	{
		auto subtrahend = *this;
		subtrahend.sign = 1;
		return x - subtrahend;
	}

	int res_sum_length = std::max(length, x.length) + 1;
	int *res_sum = new int[res_sum_length];
	int carry = 0;

	for (int i = 0; i < std::max(length, x.length); ++i)
	{
		int first_addend = (i < length) ? numbers[i] : 0;
		int second_addend = (i < x.length) ? x.numbers[i] : 0;

		res_sum[i] = (first_addend + second_addend + carry) % 10;
		carry = (first_addend + second_addend + carry) > 9;
	}
	res_sum[res_sum_length - 1] = carry;

	int final_length = (res_sum[res_sum_length - 1] == 0)
						   ? res_sum_length - 1
						   : res_sum_length;

	LongNumber result;

	delete[] result.numbers;

	result.length = final_length;
	result.sign = sign;

	result.numbers = new int[final_length];
	for (int i = 0; i < final_length; ++i)
		result.numbers[i] = res_sum[i];

	delete[] res_sum;

	return result;
}

// Как реализовать по-другому? Намного проще?
LongNumber LongNumber::operator-(const LongNumber &x) const
{
    if (*this == x)
        return LongNumber();

    if (sign != x.sign)
    {
        LongNumber temp = x;
        temp.sign = sign;
        return *this + temp;
    }

    if ((sign == 1 && *this < x) || (sign == -1 && *this > x))
    {
        LongNumber res = x - *this;
        res.sign = -res.sign;
        return res;
    }

    int len = length;
    int* res_numbers = new int[len];

    int carry = 0;
    for (int i = 0; i < len; ++i)
    {
        int val1 = numbers[i];
        int val2 = (i < x.length) ? x.numbers[i] : 0;

        int diff = val1 - val2 - carry;

        if (diff < 0)
        {
            diff += 10;
            carry = 1;
        }
        else
            carry = 0;
        res_numbers[i] = diff;
    }

    int real_len = len;
    while (real_len > 1 && res_numbers[real_len - 1] == 0)
        real_len--;

    LongNumber result;
    delete[] result.numbers;

    if (real_len == len)
    {
        result.numbers = res_numbers;
    }
    else
    {
        result.numbers = new int[real_len];
        std::copy(res_numbers, res_numbers + real_len, result.numbers);
        delete[] res_numbers;
    }

    result.length = real_len;
    result.sign = sign;

    return result;
}

LongNumber LongNumber::operator*(const LongNumber &x) const
{
	LongNumber res; // 0
	if (*this == res || x == res)
		return res;

	int res_length = length + x.length;
	int *res_numbers = new int[res_length]{};
	int *tmp = new int[this->length + 1]{};

	for (int second_index = 0; second_index < x.length; ++second_index)
	{
		if (x.numbers[second_index] == 0)
			continue;
		tmp[this->length] = 0;

		int carry = 0;

		for (int first_index = 0; first_index < this->length; ++first_index)
		{
			int tmp_mult = this->numbers[first_index] * x.numbers[second_index] + carry;
			tmp[first_index] = tmp_mult % 10;
			carry = tmp_mult / 10;
		}
		tmp[this->length] = carry;
		carry = 0;

		for (int i = 0; i < this->length + 1; ++i)
		{
			int tmp_sum = res_numbers[i + second_index] + tmp[i] + carry;
			carry = tmp_sum / 10;
			res_numbers[i + second_index] = tmp_sum % 10;
		}
	}
	delete[] tmp;

	int total_length = res_length;
	if (res_numbers[total_length - 1] == 0)
		--total_length;

	delete[] res.numbers;
	res.numbers = new int[total_length];

	for (int i = 0; i < total_length; ++i)
		res.numbers[i] = res_numbers[i];
	delete[] res_numbers;

	res.length = total_length;
	res.sign = (sign == x.sign ? 1 : -1);

	return res;
}

LongNumber LongNumber::operator/(const LongNumber &x) const
{
    LongNumber zero;

    if (x == zero)
       throw std::invalid_argument("division by zero");

    if (*this == zero)
       return zero;

    LongNumber dividend = *this;
    LongNumber divisor = x;
    dividend.sign = 1;
    divisor.sign = 1;

    int max_q_len = length - x.length + 1;
    if (max_q_len < 0) max_q_len = 0;

    int *res_numbers = new int[max_q_len > 0 ? max_q_len : 1]{};

    while (dividend > divisor || dividend == divisor)
    {
       int length_dif = dividend.length - divisor.length;
       LongNumber sub_base = divisor * TenPow(length_dif);

       if (dividend < sub_base)
       {
          --length_dif;
          sub_base = divisor * TenPow(length_dif);
       }

       int digit = 0;
       for (int d = 1; d <= 9; ++d)
       {
          LongNumber prod = sub_base * LongNumber(std::to_string(d).c_str());
          if (prod > dividend)
             break;

          digit = d;
       }

       LongNumber prod = sub_base * LongNumber(std::to_string(digit).c_str());
       dividend = dividend - prod;
       res_numbers[length_dif] += digit;
    }

    int total_length = max_q_len;
    while (total_length > 1 && res_numbers[total_length - 1] == 0)
       --total_length;

    LongNumber res;
    delete[] res.numbers;

    if (total_length <= 0) total_length = 1;

    res.numbers = new int[total_length];
    for (int i = 0; i < total_length; ++i)
       res.numbers[i] = res_numbers[i];
    delete[] res_numbers;

    res.length = total_length;
    res.sign = (sign == x.sign ? 1 : -1);

    if (res.length == 1 && res.numbers[0] == 0)
       res.sign = 1;


    if (sign == -1 && dividend != zero)
    {
       LongNumber one("1");
       if (x.sign == 1)
          res = res - one;
       else
          res = res + one;
    }

    return res;
}

LongNumber LongNumber::operator%(const LongNumber &x) const
{
	LongNumber zero;

	if (x == zero)
		throw std::invalid_argument("division by zero");

	LongNumber quotient = *this / x;
	LongNumber product = quotient * x;
	LongNumber remainder = *this - product;

	return remainder;
}

int LongNumber::get_digits_number() const noexcept
{
	return length;
}

int LongNumber::get_rank_number(int rank) const
{
	if (rank < 0 || rank >= length)
		throw std::out_of_range("rank is out of range in LongNumber::get_rank_number");

	return numbers[rank];
}

bool LongNumber::is_negative() const noexcept
{
	return sign == -1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char *const str) const noexcept
{
	if (str == nullptr || str[0] == '\0')
		return 0;

	int i = 0;

	if (str[i] == '+' || str[i] == '-')
		++i;

	while (str[i] == '0')
		++i;

	if (str[i] == '\0')
		return 1;

	int count = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		++count;
		++i;
	}

	return count;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv
{
	std::ostream &operator<<(std::ostream &os, const LongNumber &x)
	{
		if (x.sign < 0)
			os << '-';

		for (int i = x.length - 1; i >= 0; --i)
		{
			os << x.numbers[i];
		}

		return os;
	}
}
