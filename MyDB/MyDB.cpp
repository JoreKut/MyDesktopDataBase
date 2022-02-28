#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

const int FIELD_SIZE = 20;
const string PATH = "my_db.txt";

float calcZP(float gain, int data) {
	// Анализ данных

	//
	// ==> дата: 28.02.2011 выручка: 2000$
	// 6% + 1% => 7% 
	//

	float percent;
	
	if (gain > 1000) {
		percent = 0.06;
	}
	else {
		percent = 0.05;
	}

	// Проверить стаж
	// Сейчас 2022
	if (2022 - data > 10) {
		percent += 0.01;
	}
	
	float zp = gain * percent;

	return zp;

}

string formatField(string s) {

	int space_number = FIELD_SIZE - s.length() - 1;

	for (int i = 0; i < space_number; i++) {
		// добавлять пробелы
		s += " ";
	}

	// добавим один символ "|"
	s += "|";

	//вернем новую строку
	return s;
}

void drawLine(ofstream& file, int field_number) {
	file << "+--";
	for (int i = 0; i < field_number * FIELD_SIZE - 1; i++) {
		file << "-";
	}
	file << "+\n";
}

void loadDataToFile(ofstream &file, string name, string surname, string number, int data, float gain, float zp){

	file << "|  ";
	file << formatField(name);
	file << formatField(surname);
	file << formatField(number);
	file << formatField(to_string(data));
	file << formatField(to_string(gain));
	file << formatField(to_string(zp));
	file << endl;
	drawLine(file, 6);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	cout << "Введите количество сотрудников: ";
	int n;
	cin >> n;

	string name;
	string surname;
	string number;
	int data;
	float gain;
	float zp;

	float gainSum = 0;
	float zpSum = 0;
	
	ofstream file(PATH);

	drawLine(file, 6);
	for (int i = 0; i < n; i++) {
		
		// считывание
		cin >> name >> surname >> number >> data >> gain;
		
		// Анализ
		zp = calcZP(gain, data);
		zpSum += zp;
		gainSum += gain;

		// добавление в файл
		loadDataToFile(file, name, surname, number, data, gain, zp);
	
	}

	file << "|  " << formatField("Прибыль работников:") << formatField(to_string(zpSum)) << endl;
	drawLine(file, 2);
	file << "|  " << formatField("Выручка:") << formatField(to_string(gainSum)) << endl;
	drawLine(file, 2);
	file << "|  " << formatField("Прибыль:") << formatField(to_string(gainSum - zpSum)) << endl;
	drawLine(file, 2);
	file.close();

	// чтение
	// запись

	// Фамилия
	// Имя
	// Номер
	// Дата
	// Выручка
	// -> ЗП


	// 
	//	Для каждого сотрудника:
	//		1. считать данные
	//		2. обработать данные
	//			a. Высчитаем зп
	//			b. ---
	//		3. добавить данные в файл
	//
	//	Вывести итоги



	// A B C 2011 2000 => zp = 140
	// AA BB CC 2016 4000 => 240
	// AAA BBB CCC 2015 6000 => 360 
	// AAAA BBBB CCCC 2021 800 => 40

	// имя1 фамилия1 номер1 2011 2000
	// имя2 фамилия2 номер2 2016 6000
	// имя3 фамилия3 номер3 2015 4000
	// имя4 фамилия4 номер4 2021 800

	// Выручка = 12 800
	// Работники = 780
	// Прибыль = 12 020

	// строка - человек
	// .txt 50 человек = 50 строк
	// доп строка => сумма всей выручки
}