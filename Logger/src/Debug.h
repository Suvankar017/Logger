#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <Windows.h>

/*
Default Color - 7
Info Color - 15
Warning Color - 6
Error Color - 12
Success Color - 10
*/

class Debug
{
public:
	template<typename... Args>
	static void Info(const char* format, const Args&... args)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, m_InfoColor);

		Print(format, args...);

		SetConsoleTextAttribute(h, m_DefaultColor);
	}

	template<typename... Args>
	static void Success(const char* format, const Args&... args)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, m_SuccessColor);

		Print(format, args...);

		SetConsoleTextAttribute(h, m_DefaultColor);
	}

	template<typename... Args>
	static void Warning(const char* format, const Args&... args)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, m_WarningColor);

		Print(format, args...);

		SetConsoleTextAttribute(h, m_DefaultColor);
	}

	template<typename... Args>
	static void Error(const char* format, const Args&... args)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, m_ErrorColor);

		Print(format, args...);

		SetConsoleTextAttribute(h, m_DefaultColor);
	}

private:
	static void GetArgs(std::vector<std::stringstream>& argList)
	{

	}

	template<typename First, typename... Args>
	static void GetArgs(std::vector<std::stringstream>& argList, const First& f, const Args&... args)
	{
		size_t index = argList.size();
		argList.resize(index + 1);
		argList[index] << f;

		GetArgs(argList, args...);
	}

	template<typename... Args>
	static void Print(const char* format, const Args&... args)
	{
		std::vector<std::stringstream> argList;
		GetArgs(argList, args...);

		size_t start = 0, count = 0, index = 0;

		for (size_t i = 0; format[i] != '\0'; i++)
		{
			char ch = format[i];

			switch (ch)
			{
			case '#':
				std::cout << std::string_view(&format[start], count) << argList[index].str();
				index++;
				start = i + 1;
				count = 0;
				break;

			default:
				count++;
				break;
			}
		}

		std::cout << std::string_view(&format[start], count) << std::endl;
	}

private:
	const static unsigned short m_DefaultColor = 7;
	const static unsigned short m_InfoColor = 15;
	const static unsigned short m_SuccessColor = 10;
	const static unsigned short m_WarningColor = 6;
	const static unsigned short m_ErrorColor = 12;
};

#if _DEBUG

#define ASSERT(assertion, message) if (!(assertion)) \
{ \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79); \
	std::cout << "File : " << __FILE__ << "\nLine : " << __LINE__ << "\nMessage : " << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
	__debugbreak(); \
}

#else

#define ASSERT(assertion, message)

#endif

