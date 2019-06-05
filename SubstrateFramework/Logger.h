#pragma once

#include <stdio.h>
#include <signal.h>
#include <string>

namespace ssfw
{
	class Logger
	{
	private:

	public:

		static const int verbocityLvl = 0;

		Logger() {}
		~Logger() {}

		static void printMsg(const std::string &s, const int importance)
		{
			if (importance >= verbocityLvl)
				std::fprintf(stdout, "%s\n", s.c_str());
		}

		static void printExcep(const std::exception &e, const int importance)
		{
			if (importance >= verbocityLvl)
				std::fprintf(stderr, "Error: %s\n", e.what());
		}

		static void printErrMsg(const std::string &s, const int importance)
		{
			if (importance >= verbocityLvl)
				std::fprintf(stderr, "%s\n", s.c_str());
		}
	};
}