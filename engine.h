#pragma once
#include "wrapper.h"

class Engine {
	std::map<std::string, Wrapper*> functions;
public:
	Engine() = default;
	~Engine() = default;

	Engine(Engine const&) = delete;
	Engine(Engine&&) = default;

	Engine& operator =(Engine const&) = delete;
	Engine& operator =(Engine&&) = default;

	void registerCommand(Wrapper* wrapper, const std::string& nameCommand) {
		if (functions[nameCommand] != nullptr) {
			throw std::exception("Engine exception: command already exist");
		}

		functions[nameCommand] = wrapper;
	}

	int execute(const std::string& nameCommand, const std::map<std::string, int>& args) {
		auto command = functions[nameCommand];
		if (command == nullptr) {
			throw std::exception("Engine exception: no such command");
		}
		
		//auto wrapper = static_cast<Wrapper*>(command);
		return command->execute(args);
	}
};