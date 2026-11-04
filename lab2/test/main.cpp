#include "process_runner.h"
#include <iostream>

int main() {
    int code = 0;

    std::cout << "Test 1: Successful command" << std::endl;
#ifdef _WIN32
    // На Windows: выведет "Hello" и вернет 0
    if (run_and_wait("echo Hello", code)) {
#else
    // На Linux: выведет "Hello" и вернет 0
    if (run_and_wait("echo Hello", code)) {
#endif
        std::cout << "Command finished with code: " << code << std::endl;
    } else {
        std::cout << "Failed to run command." << std::endl;
    }

    std::cout << "\nTest 2: Command with non-zero exit code" << std::endl;
    // Эта команда завершится с ошибкой (код 1 или 9009 на Windows)
#ifdef _WIN32
    if (run_and_wait("exit /b 42", code)) {
#else
    if (run_and_wait("exit 42", code)) {
#endif
        std::cout << "Command finished with code: " << code << std::endl;
    }

    return 0;
}