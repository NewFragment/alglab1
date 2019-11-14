﻿#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <conio.h>
using namespace std;

struct list
{
	int symbol;
	list* next;
	list* head;
};

//---------------------------------------------------
list* input(int b); //Функция ввода входных данных
list* arrtolist(int* b, int c); //Функция перевода массива в список
char strings(int a); //Вспомогательная функция для отображения наименования множества при вводе данных
void incorrect();	//Вспомогательная функция для предупреждения об ошибки ввода и очистки потока ввода
list* check(list*A, list*B, list*C, list*D); //Функция обработки по условию(работа с отображениями)
int* check_01(list*A, list*B, bool c); //Вспомогательная функция обработки по условию(создание массивов отображения на универсум)
int* check_02(int* a, int b, int c); //Вспомогательная функция обработки по условию(запись результата в массив)
void output(list *E, int b); //Функция вывода результата
list* freemem(list* A, list* B, list* C, list* D, list* E, int a); //Функция очистки памяти
//---------------------------------------------------

int main()
{

	setlocale(LC_ALL, "RUS");
	list *A, *B, *C, *D, *E;
	A = input(0);
	B = input(1);
	C = input(2);
	D = input(3);
	E = check(A, B, C, D);
	output(A, 0);
	output(B, 1);
	output(C, 2);
	output(D, 3);
	output(E, 4);
	system("pause");
	freemem(A, B, C, D, E, 0);

	return 0;

}

//--------------------------------------------------------------------------------------

bool test(char ch, const char *keys, unsigned int size)
{
	for (int i = 0; i < size; i++)
		if (keys[i] == ch) return true;
	return false;
}

//--------------------------------------------------------------------------------------
list* input(int b)
{
	const char keys[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	int *spisok;
	spisok = NULL;
	int a = 1;
	char S;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Введите множество " << strings(b) << ": ";
	while ((S = _getch()) != '\r')//enter
		if (test(S, keys, 16))
		{
			if (!spisok) spisok = new int[1];
			else {
				a++;
				spisok = (int*)realloc(spisok, (a) * sizeof(int));
			}
			if (test(S, keys, 10))
				spisok[a - 1] = S - (int)48;
			else
				spisok[a - 1] = S - (int)87;
			cout << S;
		}

	cout << endl << "-------------------------------------------------------------" << endl;
	system("pause");
	return arrtolist(spisok, a); //с помощью этой функции переводим массив в список
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
list* arrtolist(int* b, int c) {
	if (!b) return NULL;
	int i = 0;
	list* A = new list;
	A->head = A;
	do {							//заполняем список из массива
		A->symbol = b[i];
		i++;
		if (i != c) { //при последнем заходе мы таким образом не создадим лишний элемент
			A->next = new list;
			A->next->head = A->head;
			A = A->next;
		}
	} while (i != c);
	A->next = NULL;
	return A->head;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
char strings(int a)
{
	switch (a)
	{
	case 0: {return 'A'; }
	case 1: {return 'B'; }
	case 2: {return 'C'; }
	case 3: {return 'D'; }
	case 4: {return 'E'; }
	}
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void incorrect() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
	cout << "Некорректный ввод! Повторите" << endl;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
list* check(list*A, list*B, list*C, list*D)
{
	if (!A && !C) return NULL;
	int* spisok = NULL; //массив, который потом станет E
	int count = 0; //размер массива

	int* u1 = check_01(A, C, false); //отображение на универсум A ИЛИ C

	int* u2 = check_01(B, D, true); //отображение на универсум B И D
		for (int i = 0; i < 16; i++) u1[i] = u1[i] * u2[i]; //Применяем побитовое умножение чтобы получить результат
	for (int i = 0; i < 16; i++) //вводим результат в массив
	{
		if (u1[i] == 1) //берём наш универсум и если мы наткнулись на единицу
		{
			spisok = check_02(spisok, count, i); //то сохраняем в массив порядковый номер
			count++; //не забываем размер массива обновлять
		}
	}
	if (spisok)
		return arrtolist(spisok, count);   //с помощью этой функции переводим массив в список
	else
		return NULL;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
int* check_01(list* first, list* second, bool c)
{
	int* u = new int[16];

	for (int i = 0; i < 16; ++i) //создаём нулевой массив
		u[i] = 0;

	if (c) { //если на вход принимаются B и D и они оба не пустые, то заполняем универсум (B && D)
		if (first)
			for (list*a = first->head; a; a = a->next)
				if (second)
					for (list*b = second->head; b; b = b->next) {
						if (a->symbol == b->symbol) {
							u[a->symbol] = 1;
							break;
						}
					}
				else break;
		for (int i = 0; i < 16; ++i) //отображение инвертируем по условию (~)
			u[i] == 1 ? u[i] = 0 : u[i] = 1;
		return u;
	}
	if (first)
		for (list*a = first->head; a; a = a->next)	 //заполняем отображение по первому множеству
			u[a->symbol] = 1;

	if (second)
		for (list*a = second->head; a; a = a->next)	//и по второму туда же
			u[a->symbol] = 1;

	return u;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
int* check_02(int* a, int b, int c) {

	if (!a) {	//при первом заходе создаём массив и сохраняем цифру
		a = new int;
		a[b] = c; //записываем число в массив
		
	}
	else {		//при последующих увеличиваем память на 1 ячейку и сохраняем цифру
		a = (int*)realloc(a, (c + 1) * sizeof(int));
		a[b] = c; //записываем число в массив
	}
	return a;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void output(list *A, int b)
{
	if (A)
	{
		if (b == 4) cout << endl << endl;
		cout << "Множество '" << strings(b) << "': [ ";
		for (list *p = A->head; p; p = p->next)
		{
			if (p->next)
				cout << hex << p->symbol << ", ";
			else cout << hex << p->symbol << " ";
		}
		cout << "]" << endl;
	}
	else cout << "Множество '" << strings(b) << "' - пустое" << endl;
	if (b == 4) cout << endl << endl;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
list* freemem(list* A, list* B, list* C, list* D, list* E, int a) {
	if (!A) return NULL;
	A = A->head;
	if (!A->next) {
		delete A;
		return NULL;
	}
	for (list *p = A->head->next; p; p = p->next) {
		delete A;
		A = p;
	}
	delete A;
	if (a != 4)
		freemem(B, C, D, E, E, a + 1); //рекурсивно двигаемся по функции пока не дойдем до E(тогда a == 4 и мы выйдем)

	return NULL;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------