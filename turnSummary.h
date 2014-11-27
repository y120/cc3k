#ifndef __TURN_SUMMARY_H__
#define __TURN_SUMMARY_H__

#include <string>
#include <vector>

class TurnSummary {
public:
	static void add(std::string);
	static void clear();
	static std::string get();

private:
	static std::vector<std::string> lines;
};

#endif
