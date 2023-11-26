#pragma once
#include <map>
#include <string>
#include <tuple>

class LargeNumber
{
public:
	float Value() { return std::get<0>(number); }
	int Exponent() { return std::get<1>(number); }

	LargeNumber(float startValue, int exponent) {
		number = std::tuple<float, int>(startValue, exponent);
	}

	int Update() {
		if (Value() >= pow(10, expInterval + 2))
		{
			std::get<1>(number) += expInterval;
			std::get<0>(number) /= pow(10, expInterval);
		}

		if (Value() < 10 && Exponent() >= expInterval)
		{
			std::get<1>(number) -= expInterval;
			std::get<0>(number) *= pow(10, expInterval);
		}

		return 0;
	}

	int Add(LargeNumber* num) {
		float value = num->Value();
		int exp = num->Exponent();
		if (exp == std::get<1>(number))
		{
			std::get<0>(number) += value;
			return 0;
		}

		if (exp > Exponent())
		{
			std::get<0>(number) += (exp - Exponent()) * 10 * value;
			return 0;
		}

		std::get<0>(number) += value * (float)pow(0.1, Exponent() - exp);
		return 0;
	}

	int Remove(LargeNumber* num) {
		int interger = (int)num->Value();
		int count = 0;
		while (interger != 0) {
			interger = interger / 10;
			count++;
		}
		int intergerTwo = (int)Value();
		int countTwo = 0;
		while (intergerTwo != 0) {
			intergerTwo = intergerTwo / 10;
			countTwo++;
		}

		if (num->Exponent() + count > Exponent() + countTwo || num->Value() > Value())
			return -1;

		std::get<0>(number) -= num->Value() * (float)pow(0.1, Exponent() - num->Exponent());
		return 0;
	}

	bool LargerThan(LargeNumber* num) {
		int interger = (int)num->Value();
		int count = 0;
		while (interger != 0) {
			interger = interger / 10;
			count++;
		}
		int intergerTwo = (int)Value();
		int countTwo = 0;
		while (intergerTwo != 0) {
			intergerTwo = intergerTwo / 10;
			countTwo++;
		}

		if (num->Exponent() + count > Exponent() + countTwo || num->Value() > Value())
			return false;
		return true;
	}

	std::string ToString() {
		std::tuple<std::string, std::string> str = Round(std::get<0>(number), 2);
		return std::get<0>(str) + "." + std::get<1>(str) + strEquivalent.at(std::get<1>(number));
	}

	std::string ToString(bool usePrefix) {
		std::tuple<std::string, std::string> str = Round(std::get<0>(number), 2);
		return std::get<0>(str) + "." + std::get<1>(str) + prefixEquivalent.at(std::get<1>(number));
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

private:
	const int expInterval = 3;
	const std::map<int, std::string> strEquivalent = {
		{0, ""},
		{3, " Thousand"},
		{6, " Million"},
		{9, " Billion"},
		{12, " Trillion"},
		{15, " Quadrillion"},
		{18, " Quintillion"},
	};
	const std::map<int, std::string> prefixEquivalent = {
		{0, ""},
		{3, "Kilo"},
		{6, "Mega"},
		{9, "Giga"},
		{12, "Tera"},
		{15, "Peta"},
		{18, "Exa"},
	};
	std::tuple<float, int> number = std::tuple<float, int>();


	
};