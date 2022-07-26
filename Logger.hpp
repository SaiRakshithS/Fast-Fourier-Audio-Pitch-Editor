#pragma once

#include <string>
#include <fstream>

enum logLevel {
    emerg, alert, 
    crit, err, 
    warn, notice,
    info, debug
};

const std::string logName[8] = {
    "Emergency", "Alert",
    "Critical", "Error",
    "Warning", "Notice",
    "Information", "Debug"
};

class Logger {

    private:
        bool failure;
        std::ofstream logFile;
        std::string moduleName;

    public:
        Logger(std::string = "", std::string = "");
        ~Logger();

        void FileLog(std::string, logLevel);
        void ConsoleLog(std::string message, logLevel level);
        void LogToFileAndConsole(std::string message, logLevel level);
};