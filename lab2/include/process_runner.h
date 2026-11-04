#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <string>

// Запускает программу в фоне, ждет завершения и возвращает код ответа
// Возвращает true в случае успешного запуска и ожидания
// В случае ошибки возвращает false
bool run_and_wait(const std::string& command, int& exit_code);

#endif 