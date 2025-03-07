## Утилита сортировки строк `sort_strings`

Утилита `sort_strings` читает строки из текстового файла, сортирует их с использованием выбранного алгоритма и выводит результат в стандартный поток вывода.

## Поддерживаемые алгоритмы сортировки
- `bubble` — сортировка пузырьком
- `insertion` — сортировка вставками
- `merge` — сортировка слиянием
- `quick` — быстрая сортировка
- `radix` — поразрядная сортировка

## Поддерживаемые компараторы
- `asc` — по возрастанию (ascending)
- `des` — по убыванию (descending)

## Сборка и запуск
mkdir build  
cd build  
cmake -DUSE_MMAP=OFF/ON ..  
cmake --build  

## Запуск тестов
ctest
или
./tests
### Требования
- Компилятор C (например, GCC)
- CMake (версия 3.10 или выше)

### Сборка
1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/Galay-Nastya/Sortings.git
   cd sort_strings
