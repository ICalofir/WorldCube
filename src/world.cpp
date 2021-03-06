#include "world.hpp"
#include "person.hpp"
#include "utils/parsable_utils.hpp"
#include <iostream>

// Action

void Action::Dump(std::ostream &out) {
	out << "Action \"" << name << "\"\n";
	out << "InfoMessages: ";
	for (auto x : infoMessages) {
		out << "\"" << x.message << "\" ";
	}
	out << "\nEffects: ";
	for (auto x : effects) {
		out << "[" << x.name << " -> " << x.delta << "] ";
	}
	out << std::endl;
}

// Item

void Item::Dump(std::ostream &out) {}

// Subitem

void Subitem::Dump(std::ostream & out) {}

// InfoMessage

void InfoMessage::s_Print(unsigned long long t, void* context, void* additionalInfo) {
	static_cast<InfoMessage*>(context)->Print(t, static_cast<Person*>(additionalInfo));
}

void InfoMessage::Print(unsigned long long t, Person* owner) {
	std::string printMsg, var;
	bool inVar = false;

	for (const char& c : message) {
		if (c == '%') {
			if (inVar) {
				printMsg += owner->GetEnvVar(var);
				var.clear();
			}
			inVar = !inVar;
			continue;
		}

		if (inVar) {
			var.push_back(c);
		}
		else {
			printMsg.push_back(c);
		}
	}

	std::cout << t << ": " << printMsg << "\n";
}

// World

World* World::singletonPtr = nullptr;

World::World() {}

World::~World() {}

void World::Init() {
	if (singletonPtr == nullptr) {
		singletonPtr = new World();

		singletonPtr->items = ParsableFactory<std::unordered_map<std::string, Item>>::Build(XMLParser("items.xml").GetRoot());
		singletonPtr->actions = ParsableFactory<std::unordered_map<std::string, Action>>::Build(XMLParser("actions.xml").GetRoot());
	}
}

Action* World::GetAction(const std::string name) {
	return &singletonPtr->actions[name];
}

Item* World::GetItem(const std::string name) {
	return &singletonPtr->items[name];
}
