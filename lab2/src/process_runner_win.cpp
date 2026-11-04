#ifdef _WIN32 // Компилируется только на Windows

#include "process_runner.h"
#include <windows.h>
#include <iostream>

bool run_and_wait(const std::string& command, int& exit_code) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Формируем команду для cmd.exe
    std::string cmd_line = "cmd.exe /C " + command;

    // CreateProcess требует изменяемую строку
    char* cmd_buf = new char[cmd_line.size() + 1];
    strcpy(cmd_buf, cmd_line.c_str());

    if (!CreateProcessA(NULL, cmd_buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed. Error: " << GetLastError() << std::endl;
        delete[] cmd_buf;
        return false;
    }
    delete[] cmd_buf;

    // Ждем завершения процесса
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD dwExitCode;
    if (!GetExitCodeProcess(pi.hProcess, &dwExitCode)) {
        std::cerr << "GetExitCodeProcess failed." << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }

    exit_code = static_cast<int>(dwExitCode);

    // Закрываем дескрипторы
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

#endif