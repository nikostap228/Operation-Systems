#!/bin/bash
set -e 

# git pull # Раскомментируйте эту строку, когда настроите удаленный репозиторий (GitHub/GitLab)

if [ -d "build" ]; then
    rm -rf build
fi

mkdir -p build
cd build
cmake ..

make

echo "Для запуска выполните: ./build/hello_app"