#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#define FMT_HEADER_ONLY //so we only have to use the header files from the FMT repo
#include <fmt/format.h>
#pragma warning (disable : 4996)

class debugConsole {
	static std::ofstream file;
	const enum class ePrefix {
		eINFO = 1,
		eERROR,
		eWARNING
	};
public:
	debugConsole();
	~debugConsole();

	static void enable(const std::string& targetProcess);

	template <typename... Args>
	static void output(const ePrefix& msgType, const std::string_view& str, Args&&... args) {
		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		std::string prefix;
		switch (msgType) {
		case ePrefix::eINFO: prefix = "INFO"; break;
		case ePrefix::eERROR: prefix = "ERROR"; break;
		case ePrefix::eWARNING: prefix = "EVENT"; break;
		default: prefix = "UNK";
		}

		const std::string prefixStr = fmt::format("[{0}:{1}:{2}] [{3}] ", tm->tm_hour, tm->tm_min, tm->tm_sec, prefix);
		const std::string body = fmt::format(std::string(str), args...);

		if (msgType == ePrefix::eERROR)
			std::cerr << prefixStr << body << std::endl;
		else
			std::cout << prefixStr << body << std::endl;

		debugConsole::file << prefixStr << body << std::endl;
	}

	template <typename... Args>
	static void error(const std::string_view& str, Args&&... args) {
		output(ePrefix::eERROR, str, args...);
	}
	template <typename... Args>
	static void info(const std::string_view& str, Args&&... args) {
		output(ePrefix::eINFO, str, args...);
	}
	template <typename... Args>
	static void warning(const std::string_view& str, Args&&... args) {
		output(ePrefix::eWARNING, str, args...);
	}
};
