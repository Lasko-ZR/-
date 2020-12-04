#include <iostream>
#include <conio.h>


#pragma warning(disable:4996) 

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();

char getMapValue(int value);

// Розміри поля
const int mapwidth = 20;
const int mapheight = 20;

const int size = mapwidth * mapheight;

int map[size];

// Деталі голови змійки
int headxpos;
int headypos;
int direction;

// Кількість їжі у змії на початок гри (довжина)
int food = 3;

// Визначення, чи запущена гра
bool running;

int main()
{
	
	run();
	return 0;
}

// Основна функція гри
void run()
{
	setlocale(LC_CTYPE, "ukr");

	// Ініціалізація поля 
	initMap();
	running = true;
	while (running) {
		// Якщо натиснута клавіші
		if (kbhit()) {
			// Зміна напрямку, що визначається натисканням клавіші
			changeDirection(getch());
		}
		// Оновленя поля
		update();

		// Очищеня екрану
		clearScreen();

		// друкування поля
		printMap();

		// затримка 0.5 секунди
		_sleep(500);
	}

	// Вивід тексту після завершення гри
	std::cout << "\t\t!Гра завершена!" << std::endl << "\t\tДовжина змiйки: " << food;

	// Зупинка автоматичного закриття консолі
	std::cin.ignore();
}

// Змінна напрямку змії від напискання
void changeDirection(char key) {
	
	//   W
	// A + D
	//   S
    
	switch (key) {
	case 'w':
		if (direction != 2) direction = 0;
		break;
	case 'd':
		if (direction != 3) direction = 1;
		break;
	case 's':
		if (direction != 4) direction = 2;
		break;
	case 'a':
		if (direction != 5) direction = 3;
		break;
	}
}

// Переміщення голови на нові координати
void move(int dx, int dy) {
	// Визначає нове положення голови
	int newx = headxpos + dx;
	int newy = headypos + dy;

	// Перевіряємо чи є там їжа
	if (map[newx + newy * mapwidth] == -2) {
		// Збільшення довжина тіла
		food++;

		// Створення нової їжі на полі
		generateFood();
	}

	// Швидка перевірка місця розташування 
	else if (map[newx + newy * mapwidth] != 0) {
		running = false;
	}

	// Переміщення голови на нове місце
	headxpos = newx;
	headypos = newy;
	map[headxpos + headypos * mapwidth] = food + 1;

}

// Очищення екрану
void clearScreen() {

	system("cls");
}

// Генеруємо нову їжу на карті
void generateFood() {
	int x = 0;
	int y = 0;
	do {
		// Створюємо випадкові значення x та y на карті
		x = rand() % (mapwidth - 2) + 1;
		y = rand() % (mapheight - 2) + 1;

		// Якщо значення вже були, шукаємо інші
	} while (map[x + y * mapwidth] != 0);

	// Встановлюємо нову їжу
	map[x + y * mapwidth] = -2;
}

// Оновлення поля
void update() {
	// Рух у вказаному напрямку
	switch (direction) {
	case 0: move(-1, 0);
		break;
	case 1: move(0, 1);
		break;
	case 2: move(1, 0);
		break;
	case 3: move(0, -1);
		break;
	}

	// Зменшує  значення змії на полі на 1
	for (int i = 0; i < size; i++) {
		if (map[i] > 0) map[i]--;
	}
}

// Ініціалізує поле
void initMap()
{
	// Розміщуємо початкове розташування голови в середині карти
	headxpos = mapwidth / 2;
	headypos = mapheight / 2;
	map[headxpos + headypos * mapwidth] = 1;

	// Розміщуємо верхню і нижню стіни
	for (int x = 0; x < mapwidth; ++x) {
		map[x] = -1;
		map[x + (mapheight - 1) * mapwidth] = -1;
	}

	// Розміщуємо ліву та праву стіни
	for (int y = 0; y < mapheight; y++) {
		map[0 + y * mapwidth] = -1;
		map[(mapwidth - 1) + y * mapwidth] = -1;
	}

	// Генеруємо першу їжу
	generateFood();
}

// Друкуємо поле на консолі
void printMap()
{
	for (int x = 0; x < mapwidth; ++x) {
		for (int y = 0; y < mapheight; ++y) {
			// Друкуємо значення в поточному розташуванні x, y
			std::cout << getMapValue(map[x + y * mapwidth]);
		}
		// Завершуємо рядок для наступного значення x
		std::cout << std::endl;
	}
}

// Повертаємо графічний символ для відображення зі значення поля
char getMapValue(int value)
{
	// Ввідображення тіла змії
	if (value > 0) return 'O';

	switch (value) {
		// Відображення стін
	case -1: return '#';
		// Відображення Їжі
	case -2: return '$';
	}

	return ' ';
}