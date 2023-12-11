#pragma once
#include <iostream>
#include <fstream>

class SaveState
{
public:

	SaveState(Glory* glory, Sisyphus* sisyphus, std::list<StrButton*>& strButtonList, StaminaRefillButton* stamButton, StaminaExpandButton* stamExpandButton) {
		this->glory = glory;
		this->sisyphus = sisyphus;
		this->strButtonList = strButtonList;
		this->stamButton = stamButton;
		this->stamExpandButton = stamExpandButton;
	}

	int Save() {
		saveFileInput.open("SaveState.txt");
		saveFileInput.clear();
		saveFileInput << "Glory:(" + std::to_string(glory->GetGlory()->Value()) + "," + std::to_string(glory->GetGlory()->Exponent()) + ")\n";
		saveFileInput << sisyphus->ToString() + "\n";
		for (StrButton* strButton : strButtonList)
			saveFileInput << "Strength:" + strButton->ToString() + "\n";
		saveFileInput << "Stamina:" + stamButton->ToString() + "\n";
		saveFileInput << "StaminaExpand:" + stamExpandButton->ToString();

		saveFileInput.close();

		return 0;
	}

	int Load() {
		saveFileOutput.open("SaveState.txt");
		int i = 0;
		if (saveFileOutput.is_open())
		{
			while (saveFileOutput.good()) {
				strings.push_back("");
				std::getline(saveFileOutput, strings.at(i++));
				if (strings.at(0) == "") {
					std::cout << "Save file was not formatted in the right way, overriding existing file on exit.";
					return 0;
				}
			}
		}

		std::vector<std::string> str = Split(strings.at(0), '(');
		str = Split(str.at(1), ',');
		std::string str1 = str.at(0);
		std::string str2 = str.at(1);
		str2.erase(remove(str2.begin(), str2.end(), ')'), str2.end());
		glory->Load(new LargeNumber(std::stof(str1), std::stoi(str2)));

		int j = 3;
		for (StrButton* strButton : strButtonList) {
			str = Split(strings.at(j++), ':');
			strButton->Load(std::stoi(str.at(2)));
		}
		
		str = Split(strings.at(13), ':');
		stamButton->Load(std::stoi(str.at(2)));

		str = Split(strings.at(14), ':');
		stamExpandButton->Load(std::stoi(str.at(2)));
		
		str = Split(strings.at(0), '(');
		str = Split(str.at(1), ',');
		str1 = str.at(0);
		str2 = str.at(1);
		str2.erase(remove(str2.begin(), str2.end(), ')'), str2.end());
		std::list<LargeNumber*> numbers = {};
		for (StrButton* strButton : strButtonList)
			numbers.push_back(strButton->TotalStrength());
		for (LargeNumber* num : numbers)
			num->Update();
		sisyphus->Load(new LargeNumber(std::stof(str1), std::stoi(str2)), numbers);

		saveFileOutput.close();
		return 0;
	}

	std::vector<std::string> Split(std::string str, char separator) {
		int startIndex = 0, endIndex = 0;
		std::vector<std::string> strings = {};
		for (int i = 0; i <= str.size(); i++) {

			// If we reached the end of the word or the end of the input.
			if (str[i] == separator || i == str.size()) {
				endIndex = i;
				std::string temp;
				temp.append(str, startIndex, endIndex - startIndex);
				strings.push_back(temp);
				startIndex = endIndex + 1;
			}
		}
		return strings;
	}

private:
	std::ofstream saveFileInput;
	std::ifstream saveFileOutput;
	std::vector<std::string> strings;
	Glory* glory; 
	Sisyphus* sisyphus; 
	std::list<StrButton*> strButtonList;
	StaminaRefillButton* stamButton;
	StaminaExpandButton* stamExpandButton;
};