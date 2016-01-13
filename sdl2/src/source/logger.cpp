#include "logger.hpp"



Logger::Logger(const std::string & filename){

	m_start_time = std::chrono::system_clock::now();

	m_filename = "logs/" + filename;
	remove(m_filename.c_str());

}

void Logger::log(const std::string & message){

	std::chrono::duration<double> duration = std::chrono::system_clock::now() - m_start_time;
	std::ofstream file;
  	file.open(m_filename, std::ios_base::app);
  	file << duration.count() << "s: " << message << std::endl;
  	file.close();
  	
}