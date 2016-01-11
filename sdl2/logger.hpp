#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
/*
	Puts sexy logs in the logs folder with time since log creation.
	Will not do anything of folder does not exist -> TODO create folder if it does not exist
	If you have any sexier ideas on how to print the logs go ahead 
*/

class Logger{
public:
	Logger(std::string filename);
	void log(std::string message);
private:
	std::string m_filename;
	std::chrono::system_clock::time_point m_start_time;
};

