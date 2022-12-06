#include <iostream>
#include <string>
#include <cstdlib>

class TimeFormatMistake
{};

void convertTo12(std::string str);

int main() {

	std::string time;

	bool repeat = true;
	char answer;

	while (repeat) {
		std::cout << "Enter time in 24-hour notation: (HH:MM)" << std::endl;
		std::cin >> time;

		try {
			convertTo12(time);
		}
		catch (TimeFormatMistake) {
			std::cout << "There is no such time as " << time << std::endl;
			std::cout << "Try again: " << std::endl;
			continue;
		}

		std::cout << "Again? (y/n) " << std::endl;
		std::cin >> answer;
		if (answer != 'y' && answer != 'Y') {
			repeat = false;
		}
	}

	std::cout << std::endl << "End of program" << std::endl;
	return 0;
}

void convertTo12(std::string str) {

	// Make sure string str contains only digits 
	// (except for colon seperating minutes and hours)
	for (int i = 0; i < str.length(); i++) {
		// Skip index with colon
		if (i == 2)
			continue;

		char c = str[i];
		if ((c < '0') || (c > '9')) {
			throw TimeFormatMistake();
		}
	}

	// Make sure hour and minutes are in correct range
	if (str[0] > '2') {
		throw TimeFormatMistake();
	}
	else if (str[1] > '4' && str[0] > '1') {
		throw TimeFormatMistake();
	} // Make sure colon is used
	else if (str[2] != ':') { 
		throw TimeFormatMistake();
	}
	else if (str[3] > '5') {
		throw TimeFormatMistake();
	}
	else if (str[4] > '9') {
		throw TimeFormatMistake();
	}

	// Minutes stay the same, so we'll leave them alone
	// Get the hours and manipulate them
	int hour1 = (int)str[0] - '0';
	int hour2 = (int)str[1] - '0';

	int hh = hour1 * 10 + hour2;

	// Find out if time is in am or pm
	std::string amOrPm;
	if (hh < 12) {
		amOrPm = "AM";
	}
	else {
		amOrPm = "PM";
	}

	// Convert to 12 hour time
	hh %= 12;

	std::cout << "That is the same as" << std::endl;
	// Deal with midnight and noon
	if (hh == 0) {
		std::cout << "12";

		// Print minutes next
		for (int i = 2; i < 5; i++) {
			std::cout << str[i];
		}
	} // Any time besides midnight and noon
	else {
		std::cout << hh;
		for (int i = 2; i < 5; i++) {
			std::cout << str[i];
		}
	}

	// Print amOrPm
	std::cout << " " << amOrPm << std::endl;
}