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
		std::tuple<std::string, std::string> GLORY = Round(glory, 2);
		std::tuple<std::string, std::string> GPS = Round(std::get<0>(gps), 2);
		return std::get<0>(GLORY) + "." + std::get<1>(GLORY) + strEquivalent.at(exponent) + " Glory (" + std::get<0>(GPS) + "." + std::get<1>(GPS) + strEquivalent.at(std::get<1>(gps)) + "/s)";
	}

	int Update() {
		UpdateGlory();
		UpdateGps();
		AddGlory(std::get<0>(gps), std::get<1>(gps));
		return 0;
	}

	int AddGps(float f, int exp) {

		if (exp == std::get<1>(gps))
		{
			gps = std::tuple<float, int>(std::get<0>(gps) + f, std::get<1>(gps));
			return 0;
		}

		if (exp > std::get<1>(gps))
		{
			gps = std::tuple<float, int>((exp - std::get<1>(gps)) * 10 * f, std::get<1>(gps));
			return 0;
		}

		gps = std::tuple<float, int>(std::get<0>(gps) * (float)pow(0.1, std::get<1>(gps) - exp), std::get<1>(gps));
		return 0;
	}
	
	int RemoveGlory(std::tuple<float, int> cost) {

		if (std::get<1>(cost) > exponent || (std::get<1>(cost) == exponent && std::get<0>(cost) > glory))
			return -1;

		glory -= std::get<0>(cost) * (float)pow(0.1, exponent - std::get<1>(cost));
		return 0;
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

	const std::map<int, std::string> strEquivalent = {
		{0, ""},
		{3, " Thousand"},
		{6, " Million"},
		{9, " Billion"},
		{12, " Trillion"},
		{15, " Quadrillion"},
		{18, " Quintillion"},
	};

private:
	float glory = 0;
	std::tuple<float, int> gps = std::tuple<float,int>(1,0); //Glory per second, exponent
	int exponent = 0;
	const int expInterval = 3;

	int AddGlory(float glry, int exp) {
		if (exp == exponent)
		{
			glory += glry;
			return 0;
		}

		if (exp > exponent)
		{
			glory += (exp - exponent) * 10 * glry;
			return 0;
		}

		glory += glry * (float)pow(0.1, exponent - exp);
		return 0;
	}

	


	int UpdateGps() {
		float f = std::get<0>(gps);
		int i = std::get<1>(gps);
		if (f >= pow(10, expInterval))
		{
			i += expInterval;
			f /= pow(10, expInterval);
		}

		if (glory < 1 && i >= expInterval)
		{
			i -= expInterval;
			f *= pow(10, expInterval);
		}

		gps = std::tuple<float, int>(f, i);
		return 0;
	}

	int UpdateGlory() {
		if (glory >= pow(10, expInterval))
		{
			exponent += expInterval;
			glory /= pow(10, expInterval);
		}

		if (glory < 1 && exponent >= expInterval)
		{
			exponent -= expInterval;
			glory *= pow(10, expInterval);
		}

		return 0;
	}
};


