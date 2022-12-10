#pragma once
#include <vector>
#include <map>
#include <functional>
#include <exception>
#include <set>

template<typename Object, typename ...Args>
using Method = int(Object::*)(Args...);

class Wrapper {
	std::function<int(std::vector<int>&)> caller;
	std::set<std::string> argNames;

public:
	Wrapper() = delete;
	~Wrapper() = default;

	Wrapper(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;

	Wrapper& operator=(Wrapper const&) = delete;
	Wrapper& operator=(Wrapper&&) = default;

	template<typename Subject, typename... Args>
	Wrapper(Subject* subj, Method<Subject, Args...> func, const std::vector<std::pair<std::string, int>>& args) {

		if (subj == nullptr) {
			throw std::exception("Wrapper exception: null subject");
		}

		if (func == nullptr) {
			throw std::exception("Wrapper exception: null function");
		}

		for (auto& arg : args) {
			argNames.insert(arg.first);
		}

		if (args.size() != argNames.size()) {
			throw std::exception("Wrapper exception: wrong args naming");
		}

		caller = [this, &subj, func](const std::vector<int>& argsFunc) {
			return executeFunction(subj, func, argsFunc, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	int execute(const std::map<std::string, int>& argsMap) {
		std::vector<int> argsVec;
		for (auto& arg : argsMap) {
			if (argNames.find(arg.first) == argNames.end()) {
				throw std::exception("Wrapper exception: not initialized command");
			}

			argsVec.push_back(arg.second);
		}

		return caller(argsVec);
	}

private:
	template<typename Subject, typename FuncName, int... Indexes>
	int executeFunction(Subject* subj, FuncName funcName, const std::vector<int>& args, const std::index_sequence<Indexes...>&) {
		return ((subj->*funcName)(args[Indexes]...));
	}
};