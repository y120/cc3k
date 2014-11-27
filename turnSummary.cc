#include "turnSummary.h"

#include <string>
#include <vector>

std::vector<std::string> TurnSummary::lines;

void TurnSummary::add(std::string s) {
	TurnSummary::lines.push_back(s);
}

void TurnSummary::clear() {
	TurnSummary::lines.clear();
}

std::string TurnSummary::get() {
	std::string s;
	for (std::vector<std::string>::iterator i = TurnSummary::lines.begin();
		i != TurnSummary::lines.end(); ++i) {
		s += *i + " ";
	}
	return s;
}
