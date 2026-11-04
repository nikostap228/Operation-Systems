#ifndef _WIN32
#include "process_runner.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>

bool run_and_wait(const std::string& command, int& exit_code) {
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Fork failed" << std::endl;
        return false;
    }

    if (pid == 0) {
        // Дочерний процесс: выполняем команду через оболочку sh
        execl("/bin/sh", "sh", "-c", command.c_str(), (char*)nullptr);
        // Если execl вернулся, значит произошла ошибка
        std::cerr << "execl failed" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс: ждем завершения дочернего
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            std::cerr << "waitpid failed" << std::endl;
            return false;
        }

        if (WIFEXITED(status)) {
            exit_code = WEXITSTATUS(status);
            return true;
        }
        // Процесс был завершен сигналом, а не нормальным выходом
        exit_code = -1;
        return false;
    }
}

#endif