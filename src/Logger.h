/*
 * Logger.h
 *
 *  Created on: 11/12/2013
 *      Author: Windsdon
 */

#pragma once

#include <iostream>
#include <stdio.h>
#include "LogEntry.h"

using namespace std;

/*
 * A singleton used for logging events globally
 */
class LogEntry;
class Logger {
	public:
		/*
		 * The usable instance
		 */
		static Logger& getInstance() {
			static Logger instance;
			return instance;
		}

		/*
		 * Logs the entry
		 */
		void log(LogEntry&);
		/*
		 * Logs a basic info
		 */
		void log(const string&);

		enum Severity {
			INFO, WARNING, ALERT, ERROR, FATAL
		};

		static const char* NAME[];
	private:
		Logger() {
			log("Logger started");
		};
		Logger(Logger&);
};
