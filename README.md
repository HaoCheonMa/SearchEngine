# SearchEngine


## Описание


Простой поисковый движок на C++ с использованием JSON-конфигураций.


## Структура проекта

- `config/` — конфигурационные файлы и данные

- `resources/` — исходные тексты для индексации

- `src/` — исходный код

- `tests/` - тесты


## Сборка

Необходимо иметь компилятор MinGW

Команда в одну строку:

`git clone https://github.com/HaoCheonMa/SearchEngine.git && cd SearchEngine && cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "MinGW Makefiles" && cmake --build .`

Команды по отдельности:

`https://github.com/HaoCheonMa/SearchEngine.git`

`cd SearchEngine`

`cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "MinGW Makefiles"`

`cmake --build .`

Запуск

bash

`./src/searchserver`- запуск движка

`./tests/servertest`- запуск тестов

Настройка

    Редактируйте config/config.json для списка файлов
    Редактируйте config/requests.json для запросов
    Результаты в config/answers.json
