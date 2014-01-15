/*
 * Logger.cpp
 *
 *  Created on: 11/12/2013
 *      Author: Windsdon
 */

#include "Logger.h"

const char* Logger::NAME[] = { " INFO", " WARN", "ALERT", "ERROR", "FATAL" };

void Logger::log(LogEntry& entry) {
	cout << "[" << Logger::NAME[entry.getSeverity()] << "]" << "[" << entry.getThreadId() << "]" << " " << entry.getMessage() << endl;
}

void Logger::log(const string& message) {
	cout << "[" << Logger::NAME[Logger::Severity::INFO] << "]" << "[?]" << " " << message << endl;
}

