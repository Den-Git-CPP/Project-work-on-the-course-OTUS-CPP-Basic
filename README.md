# OTUS-CPP-Basic
📚Проектная работа разработано для курса "C++ Developer. Basic"

Программа собирается простыми командами:

-mkdir build

-cd build

-cmake .. -G "MinGW Makefiles"

Команда mingw32-make install устанавливает программу в каталог !MyProgram текущей директории.


Программа декодирует крайнюю сводку TAF.

К примеру на запрос аэропорта в программе введите четерехбуквенный код UUWW или UUEE.

UUWW  -Международный код ИКАО для аэропорта Москва(Внуково)

UUEE  -Международный код ИКАО для аэропорта Москва(Шереметьево)

UUDD  -Международный код ИКАО для аэропорта Москва(Домодедово)

ULLI  -Международный код ИКАО для аэропорта Санкт-Петербург(Пулково)

Запуск запуск из консоли с параметрами 

"-metar" выводит только декодированную сводку METAR по запрошенному аэропорту.

"-taf" выводит только декодированную сводку TAF по запрошенному аэропорту.
