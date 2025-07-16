# DateTime Class ![Tests](https://raster.shields.io/badge/tests-passed-brightgreen)![C++](https://raster.shields.io/badge/C++-17-blue)

  

Класс для работы с датой и временем на C++.

  

##  Основные возможности класса

 

- Преобразование из Unix timestamp в DateTime и обратно

- Добавление/вычитание  (секунды, дни, месяцы, годы)

- Расчет разницы между датами

- Определение дня недели

- Автоматическая проверка корректности дат

- Компактное хранение в битовых полях

- Полный набор операторов сравнения

- Форматированный строковый вывод



*Полный список функций, конструкторов, полей можно посмотреть по [ссылке](https://github.com/Nikita-bite/DateTime/blob/main/DateTime/DateTime.h).*

  

## Примеры использования

  

```cpp
// Создание объектов
DateTime Now;

Now = Now.get_Now(); // Текущее время

DateTime Date(0, 15, 12, 2023); // 15 декабря 2023

// Арифметические операции
Date.AddDays(7); // Добавить неделю

long long diff = Date - Now; // Разница в секундах

// Форматированный вывод
std::cout << "Новая дата: " << Date.ToString() << " (" << Date.DayofWeekName() << ")";

```

## Требования

  
- Компилятор с поддержкой C++17(GCC, Clang, MSVC)

- CMake 3.15+

- SFML 2.6.x (только для системных зависимостей)

- Тестовая среда: Google Test (для unit-тестов, подключается автоматически)

## Сборка проекта

### Visual studio code
- Для этого надо установить компилятор через сайт https://winlibs.com/
- Затем распаковать mingw64 на диск С, чтобы получилось так:
```bash
C:\mingw64
```
- В разделе **переменные среды** добавить в переменную Path путь:
 ```bash
C:\mingw64\bin
```
  
После проделанных действий должен работать компилятор

### Xcode
- Создать Command Line Tool проект

- В Target Membership поставить галочку на main.cpp (на других убрать). Если нужен другой файл - переставить галочку

- Product -> Run

### Bash
- Перейти в корневую директорию проекта

- Выполнить следующие команды:

 ```bash
cd DateTime

g++ DateTime.cpp main.cpp -o datetime_app && ./datetime_app
```


### Общий способ через CMake
-	Клонируйте репозиторий:
 
 ```bash
git clone --recursive https://github.com/Nikita-bite/DateTime.git
cd DateTime
```

-	Создайте папку сборки и сконфигурируйте проект:
 
 ```bash
rm -r -fo build # (если DateTime\build уже есть)
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
```

-	Соберите проект:
 
 ```bash
cmake --build . --config Release
```

-	Запустите приложение:
 
 ```bash
./bin/DateTimeApp  # Linux/macOS
.\bin\DateTimeApp.exe  # Windows
```

#### Для разработчиков
Запуск тестов:
```bash
cd build
ctest --output-on-failure
```
Или напрямую:
```bash
.\bin\DateTimeTests.exe
```

#### Платформенные особенности
##### Windows:
Рекомендуется использовать Ninja:
 ```bash
cmake .. -G "Ninja" -DSFML_DIR="C:/SFML-2.6.2/lib/cmake/SFML"
```

##### macOS (Xcode):
```bash
cmake .. -G "Xcode"
open DateTime.xcodeproj
```

##### Linux:
```bash
sudo apt install build-essential cmake libsfml-dev
```

## Структура проекта

```bash
DateTime/
├── build/          # Папка сборки (не в репозитории)
├── DateTime/
│   ├── DateTime.h  # Основной заголовочный файл
│   ├── DateTime.cpp
│   ├── main.cpp    # Пример использования
│   └── DateTimeTests/ # Unit-тесты
├── libs/
│   └── googletest  # Автоматически подключается
└── CMakeLists.txt  # Конфигурация сборки
```

