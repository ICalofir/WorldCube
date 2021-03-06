#pragma once

#include "world.hpp"
#include <string>
#include <unordered_map>

class Person {
public:
	std::unordered_map<std::string, double> needs;

	Person(const std::string name);
	
	std::string GetName();
	std::string GetEnvVar(const std::string var);
	void DoAction(Action* action);

private:
	std::unordered_map<std::string, std::string> envVars;

	static void FinishAction(unsigned long long t, void* context, void* additionalInfo);
	static void UpdateNeed(unsigned long long t, void* context, void* additionalInfo);
};
