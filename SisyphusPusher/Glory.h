#pragma once

#include <map>
#include <string>
#include <tuple>

class Glory
{
public:

	Glory() {

	}

	std::string ToString() {
		std::tuple<std::string, std::string> tuple = round(glory, 2);
		return std::get<0>(tuple) + "." + std::get<1>(tuple) + strEquivalent.at(exponent) + " Glory";
	}

	int Update() {
		UpdateGlory();
		return 0;
	}

	int AddGlory(float glry, int exp) {
		if (exp == exponent)
		{
			glory += glry;
			return 0;
		}

		if (exp > exponent)
		{
			glory += (exp - exponent) * 10 + glry;
			return 0;
		}

		glory += glry * (float)pow(0.1, exponent - exp);
		return 0;
	}

private:
	int exponent = 0;
	const int expInterval = 3;
	std::map<int, std::string> strEquivalent = {
		{0, ""},
		{3, " Thousand"},
		{6, " Million"},
		{9, " Billion"},
		{12, " Trillion"},
		{15, " Quadrillion"},
		{18, " Quintillion"},
	};

	float glory = 0;

	int UpdateGlory() {
		if (glory >= pow(10, expInterval))
		{
			exponent += expInterval;
			glory /= pow(10, expInterval);
		}

		if (glory < 1)
		{
			exponent -= expInterval;
			glory *= pow(10, expInterval);
		}

		return 0;
	}

	std::tuple<std::string, std::string> round(float var, int decimals)
	{
		float value = (int)(var * pow(10, decimals) + .5);
		int wholeNum = (int)value / pow(10, decimals);
		int decimal = fmod(value, 100);
		return std::tuple<std::string, std::string> { std::to_string(wholeNum), std::to_string(decimal)};
	}
};


