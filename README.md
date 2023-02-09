# Динамические строки

## Постановка задачи

Тестовое задание заключается в реализации класса динамических строк, который:

1. Написан на C++11 без сторонних библиотек. Не использует в своей основе какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.
2. Класс не шаблонный. Поддерживает строки произвольного размера используя базовые операции работы с динамическим хипом (функции malloc()/free() или операторы new/delete) для манипуляциип последовательностями символов типа char.
3. Имеет конструктор копирования, оператор присваивания и поддерживает move-семантику. 

У класса есть "внешний" оператор сложения двух строк.

Реализация не содержит в себе какие-то изощренные методы оптимизации (типа COW и многопоточной поддержки).

Пример написан с использованием этого класса динамических строк и какого-либо контейнера STL. Программа принимает список строк, затем выдает его в порядке, обратном лексикографическому без учета регистра.

Программа-пример работает из командной строки.

## Запуск

Вы можете создать сборку и скомпилировать программу при помощи утилиты `CMake`.

### Unix
```sh
cmake -S . -B build
make -C build
``` 

### Windows
```sh
# On windows:
cmake -S . -B build -G "MinGW Makefiles"
mingw32-make -C build
``` 

В директории `bin/` будут находиться два исполняемых файла для самой скомпилированной программы и тестов: 

```tree
bin/
|-- dynstr.exe       # Программа
`-- test-dynstr.exe  # Тесты
```

## Тестирование

Программа содержит тесты, написанные при помощи библиотеки [`googletest`](https://github.com/google/googletest). Все необходимые зависимости подключены при сборке с помощью `CMake`.

Чтобы запустить тесты, достаточно скомпилировать программу и исполнить запускаемый файл:

```sh
./bin/test-dynstr.exe
```