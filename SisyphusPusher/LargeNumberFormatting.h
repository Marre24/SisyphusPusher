#pragma once
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "SaveState.h";

class LargeNumberFormatting
{
public:
	static std::string ToString(float f) {
		std::map<int, std::string> strEquivalent = {
		{0, ""},
		{3, " Thousand"},
		{6, " Million"},
		{9, " Billion"},
		{12, " Trillion"},
		{15, " Quadrillion"},
		{18, " Quintillion"},
		{21, " Sextillion"},
		{24, " Septillion"},
		{27, " Octillion"},
		{30, " Nonillion"} };

		int digits = GetAmountOfDigits(f);
		int exp = digits / 3;

		std::tuple<std::string, std::string> str = Round(f / pow(10, exp), 2);
		return std::get<0>(str) + "." + std::get<1>(str) + strEquivalent.at(exp);
	}

	static std::string ToString(float f, bool usePrefix) {
		const std::map<int, std::string> prefixEquivalent = {
		{0, ""},
		{3, "Kilo"},
		{6, "Mega"},
		{9, "Giga"},
		{12, "Tera"},
		{15, "Peta"},
		{18, "Exa"} };
		int digits = GetAmountOfDigits(f);
		int exp = digits / 3;

		std::tuple<std::string, std::string> str = Round(f / pow(10, exp), 2);
		return std::get<0>(str) + "." + std::get<1>(str) + prefixEquivalent.at(exp);
	}

	static std::tuple<std::string, std::string> Round(float var, int decimals)
	{
		float value = (int)(var * pow(10, decimals) + .5);
		int wholeNum = (int)value / pow(10, decimals);
		int decimal = fmod(value, 100);
		if (decimal < 10)
			return std::tuple<std::string, std::string> { std::to_string(wholeNum), std::to_string(decimal) + "0"};
		return std::tuple<std::string, std::string> { std::to_string(wholeNum), std::to_string(decimal)};
	}

	static int GetAmountOfDigits(float f) {
		std::string str = std::to_string(f);
		std::vector<std::string> strVec = SaveState::Split(str, '.');
		str = strVec.at(0);
		return str.length();
	}

	

private:
	static const int expInterval = 3;
};