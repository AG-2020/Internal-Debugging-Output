#include "debugConsole.hpp"

debugConsole::debugConsole() {
	std::remove("YOURFILE.txt"); // deletes previous log 
}
debugConsole::~debugConsole() {
	info("Destroying console...");
	fclose(reinterpret_cast<FILE*>(stdout));
	fclose(reinterpret_cast<FILE*>(stderr));
	debugConsole::file.close();
	FreeConsole();
}

void debugConsole::enable(const std::string& title) {
	try {
		if (!AllocConsole())
			throw std::exception("Failed to allocate memory and create console.");
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout); //will add error check for this when I get the chance
		freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr); //will add error check for this when I get the chance
		EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
		if (!SetConsoleTitle(title.c_str()))
			throw std::exception("SetConsoleTitle Failed.");
		if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY))
			throw std::exception("SetConsoleTextAttribute failed.");
		debugConsole::file.open("FeroxCSGO.txt", std::ofstream::out | std::ofstream::app | std::ofstream::trunc);
		info("Console initialized.");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
