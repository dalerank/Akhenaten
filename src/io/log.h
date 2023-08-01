#pragma once

/**
 * Logs an info message
 * @param msg Message
 * @param va_list
 */
void log_info(const char* msg, ...);

/**
 * Logs an error message
 * @param msg Message
 * @param va_list
 */
void log_error(const char* msg, ...);