@echo off
rem git pull

if not exist build mkdir build
cd build
cmake ..

cmake --build . --config Release

echo Для запуска выполните: build\Release\hello_app.exe
cd ..
pause