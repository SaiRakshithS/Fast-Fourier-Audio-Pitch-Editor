#include <iostream>
#include "Logger.hpp"

Logger::Logger(std::string logFileName, std::string ModuleName) {

    try {

        logFile.open(logFileName, std::fstream::out);
        moduleName = ModuleName;

        std::cout << "--------------------" << std::endl;
        std::cout << "Starting Log" << std::endl;
        std::cout << "--------------------" << std::endl;

        logFile << "--------------------" << "\n";
        logFile << "Starting Log" << "\n";
        logFile << "--------------------" << "\n";
    }

    catch(std::fstream::failure& fileExcept) {

        std::cout << "Log File could not be opened" << std::endl; 
        std::cout << "Log for " + ModuleName + "will not be logged" << std::endl;

        failure = true;
    }
}

Logger::~Logger() {

    if (!failure) {

        std::cout << "Closing Present Log for: " << moduleName << std::endl;
        std::cout << "--------------------" << std::endl;

        logFile << "Closing Present Log for: " << moduleName << "\n";
        logFile << "--------------------" << "\n";
    }

    logFile.close();
}

void Logger::FileLog(std::string message, logLevel level) {

    if (!failure) {

        logFile << "In module: " << moduleName;
        logFile << message << "\n";
        logFile << "Log Level: " << logName[level] << "\n";

        if (level < 4) {
            logFile << "Exited from module\n";
        }

        logFile << "----------------------------------" << "\n";
    }
}

void Logger::ConsoleLog(std::string message, logLevel level) {

    if (!failure) {

        std::cout << "In module: " << moduleName << std::endl;
        std::cout << message << std::endl;
        std::cout << "LogLevel: " << logName[level] << std::endl;

        if (level < 4) {
            std::cout << "Exiting from module" << std::endl;
        }

        std::cout << "---------------------------" << std::endl;
    }
}

void Logger::LogToFileAndConsole(std::string message, logLevel level) {

    ConsoleLog(message, level);
    FileLog(message, level);
}