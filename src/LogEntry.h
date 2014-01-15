/*
 * LogEntry.h
 *
 *  Created on: 11/12/2013
 *      Author: Windsdon
 */

#pragma once

#include <iostream>
#include <time.h>
#include "Logger.h"

/*
 * A single log entry, describing a event
 */
using namespace std;

class Logger;
class LogEntry {
	public:
		static const string UNKNOWN_THREAD;

		/*
		 * Creates a LogEntry with the specified time
		 */
		LogEntry(int severity, const string message, const string threadId, time_t time)
				: severity(severity), message(message), threadId(threadId), created(time) {
		}

		/*
		 * Creates a LogEntry with the current time
		 */
		LogEntry(int severity, const string message, const string threadId)
				: LogEntry(severity, message, threadId, time(NULL)) {
		}

		/*
		 * Creates a LogEntry with the current time and a undefined thread
		 */
		LogEntry(int severity, const string message)
				: LogEntry(severity, message, LogEntry::UNKNOWN_THREAD, time(NULL)) {
		}
		
		time_t getCreated() const {
			return created;
		}
		
		const string& getMessage() const {
			return message;
		}
		
		int getSeverity() const {
			return severity;
		}
		
		const string& getThreadId() const {
			return threadId;
		}

	private:
		int severity;
		string message;
		string threadId;
		time_t created;
		LogEntry(LogEntry&);
};
