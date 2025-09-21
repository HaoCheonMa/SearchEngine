# SearchEngine


## Описание


Простой поисковый движок на C++ с использованием JSON-конфигураций.


## Структура проекта


- `bin/` — исполняемые файлы

- `config/` — конфигурационные файлы и данные

- `resources/` — исходные тексты для индексации

- `src/` — исходный код

- `tests/` - тесты


## Сборка

Необходимо иметь компилятор MSVC

Команда в одну строку:

git clone https://github.com/HaoCheonMa/SearchEngine.git && cd SearchEngine && mkdir build && cd build && cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "Visual Studio 17 2022" .. && cmake --build . --config Release

Команды по отдельности:

https://github.com/HaoCheonMa/SearchEngine.git

cd SearchEngine

mkdir build

cd build

cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "Visual Studio 17 2022" ..

cmake --build . --config Release

Запуск

bash

./bin/searchserver

Настройка

    Редактируйте config/config.json для списка файлов
    Редактируйте config/requests.json для запросов
    Результаты в config/answers.json
