<h1>John Conway's Game of life</h1>

<h3>🐠 Описание 🐠</h3>

Моя реализация этой игры на языке <code>C</code> <br>
В коде используется библиотека <code>ncurses</code> <br>
для интерактивного режима

<h3>🐟 Сборка 🐟</h3>

Делается из корневой папки <br>
<code>gcc -Wall -Werror -Wextra -lncurses -std=c1
./src/game_of_life.c -o game_of_life.out</code>

<h3>🪼 Запуск 🪼</h3>

Для запуска требуется передать заготовленный рисунок <br>
через перенаправление ввода
Для корректной работы <br> следует перенаправить терминал обратно после ввода <br>
<code>./game_of_life.out < ./payloads/\<file>.txt < /dev/tty</code> <br>

<h3>🦑 Скриншоты 🦑</h3>

<img src="./screenshots/screensho1.png" alt="game_of_life.png" />