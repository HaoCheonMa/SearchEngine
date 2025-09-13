# ITBoxSearchEngine

## О проекте

**ITBoxSearchEngine** — это программа, реализующая простую поисковую систему по текстовым документам. Основные компоненты проекта:

- **ConverterJSON** — чтение и запись данных из JSON-файлов (конфигурация, запросы, ответы).
- **InvertedIndex** — построение инвертированного индекса с подсчетом частот слов в документах.
- **SearchServer** — обработка поисковых запросов и ранжирование документов по релевантности.

Проект поддерживает многопоточную обработку индекса, возвращает результаты в формате JSON с учетом максимального количества ответов на запрос.

---

## Требования
 
- CMake
- Bash, CMD и т.п. 
- Компилятор MinGW или MSVC

---

## Сборка проекта

Команда для быстрой вставки: 

*MinGW*:

git clone https://github.com/HaoCheonMa/SearchEngine.git && cd SearchEngine && mkdir build && cd build && cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "MinGW Makefiles" .. && cmake --build .

*MSVC*:

git clone https://github.com/HaoCheonMa/SearchEngine.git && cd SearchEngine && mkdir build && cd build && cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "Visual Studio 17 2022" .. && cmake --build .

Команды по отдельности:

- git clone https://github.com/HaoCheonMa/SearchEngine.git

- cd SearchEngine

- mkdir build

- cd build

- cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "MinGW Makefiles" ..
- или
- cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -G "Visual Studio 17 2022" ..

- cmake --build .

---

## Запуск проекта

Для запуска приложения выполните(bash):

*MinGW*: ./SearchEngine.exe 

*MSVC*: Debug/SearchEngine.exe

*ВНИМАНИЕ!*

Если проект собран с MSVC, необходимо перенести папку json в build 

---

## Запуск тестов

Для запуска модульных тестов выполните(bash):

*MinGW: ./tests.exe*

*MSVC: Debug/tests.exe*

*ВНИМАНИЕ!* 

При запуске тестов проекта, собранного с помощью MinGW, из за особенностей типа float и самого компилятора, один тест покажет FAILED, не пугайтесь.

При сборке через MSVC все тесты будут успешно пройдены.

---

## Команды

--

*search* - запуск поиска по установкам из папки json

*stop* - выход из программы

--

## Функциональность проекта

- Корректная загрузка конфигурации и списка файлов.  
- Индексация документов с параллельной обработкой.  
- Поддержка запросов из JSON и вычисление релевантности документов.  
- Вывод результатов в формате JSON с учетом максимального количества ответов.  
- Модульные тесты покрывают логику индексации и поиска.  
