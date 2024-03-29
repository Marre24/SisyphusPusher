#pragma once
#include <iostream>
#include <fstream>

class SaveState
{
public:

	SaveState(Glory* glory, Sisyphus* sisyphus, std::vector<StrButton> strButtonList, StaminaRefillButton* stamButton, StaminaExpandButton* stamExpandButton) :
		glory(glory), sisyphus(sisyphus), strButtonList(strButtonList), stamButton(stamButton), stamExpandButton(stamExpandButton)
	{
	}

	int Save() {
		saveFileInput.open("SaveState.txt");
		saveFileInput.clear();
		saveFileInput << "Glory:(" + std::to_string(glory->GetGlory()) + ")\n";
		saveFileInput << sisyphus->ToString() + "\n";
		for (StrButton strButton : strButtonList)
			saveFileInput << "Strength:" + strButton.ToString() + "\n";
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
		std::string str1 = str.at(1);
		str1.erase(remove(str1.begin(), str1.end(), ')'), str1.end());
		glory->Load(std::stof(str1));

		int j = 2;
		for (StrButton strButton : strButtonList) {
			str = Split(strings.at(j++), ':');
			strButton.Load(std::stoi(str.at(2)));
		}
		
		str = Split(strings.at(12), ':');
		stamButton->Load(std::stoi(str.at(2)));

		str = Split(strings.at(13), ':');
		stamExpandButton->Load(std::stoi(str.at(2)));
		
		str = Split(strings.at(0), '(');
		str1 = str.at(1);
		str1.erase(remove(str1.begin(), str1.end(), ')'), str1.end());
		std::list<float> numbers = {};
		for (StrButton strButton : strButtonList)
			numbers.push_back(strButton.TotalStrength());
		sisyphus->Load(std::stof(str1), numbers);

		saveFileOutput.close();
		return 0;
	}

	static std::vector<std::string> Split(std::string str, char separator) {
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
	std::vector<StrButton> strButtonList;
	StaminaRefillButton* stamButton;
	StaminaExpandButton* stamExpandButton;
};