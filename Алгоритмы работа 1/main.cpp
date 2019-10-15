﻿#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

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
list* check(list*A, list*B, list*C, list*D); //Функция обработки по условию(работа с отображениями)
int* check_01(list*A, list*B, bool c); //Вспомогательная функция обработки по условию(создание массивов отображения на универсум)
int* check_02(int* a, int b, int c); //Вспомогательная функция обработки по условию(запись результата в массив)
void output(list *E, int b); //Функция вывода результата
list* freemem(list* A, list* B, list* C, list* D, list* E, int a); //Функция очистки памяти
//---------------------------------------------------

int main()
{
	srand(time(nullptr)); //очистка псевдорандома, чтобы при каждой компиляции выдавало разный рандом

	setlocale(LC_ALL, "RUS");
	list *A, *B, *C, *D, *E;
	A = input(0);
	B = input(1);
	C = input(2);
	D = input(3);
	E = check(A, B, C, D);
	output(E, 4);

	freemem(A, B, C, D, E, 0);
	system("pause");
	return 0;
}

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
list* input(int b)
{
	int *spisok;
	spisok = NULL;
	int a;
	cout << endl << "-------------------------------------------------------------" << endl;
	a = rand() % 16; //случайным образом выбираем число от 0 до 16 (шанс 1/16)
	cout << "Количество элементов множества '" << strings(b) << "': " << dec << a << endl;

	if (a == 0)
	{
		cout << "Множество '" << strings(b) << "' - пустое" << endl;
		cout << "-------------------------------------------------------------" << endl;
		return NULL;
	}

	spisok = new int[a]; //выделяем память для массива длинной a
	for (int i = 0; i < a; i++) { //вводим массив
		spisok[i] = rand() % 16;//случайным образом выбираем число от 0 до 16 в 16СС (шанс 1/16)
	}
	list* A = arrtolist(spisok, a);
	output(A, b);
	cout << "-------------------------------------------------------------" << endl << endl ;
	return A; //с помощью гениальной мега универсальной функции хуячим массив в список и сразу подаём на стол
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
list* arrtolist(int* b, int c) {
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
list* check(list*A, list*B, list*C, list*D)
{
	if (!A && !C) return NULL;
	int* spisok = NULL; //массив, который потом станет E
	int count = 0; //размер массива

	int* u1 = check_01(A, C, false); //отображение на универсум A ИЛИ C

	int* u2 = check_01(B, D, true); //отображение на универсум B И D

	for (int i = 0; i < 16; i++) u1[i] = u1[i] * u2[i]; //Применяем побитовое умножение чтобы получить результат
	for (int i = 0; i < 16; i++) //хуячим результат в массив
	{
		if (u1[i] == 1) //берём наш универсум и если мы наткнулись на единицу
		{
			spisok = check_02(spisok, count, i); //то запихиваем в массив порядковый номер
			count++; //не забываем размерчик массива обновлять я векторы не учил поэтому придется делать колхоз
		}
	}
	if (spisok)
		return arrtolist(spisok, count);   //с помощью гениальной мега универсальной функции хуячим массив в список и сразу подаём на стол
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

	if (c && first && second) { //если на вход принимаются B и D и они оба не пустые, то заполняем универсум (B && D)
		for (list*a = first->head; a; a = a->next)
			for (list*b = second->head; b; b = b->next)
				if (a->symbol == b->symbol) {
					u[a->symbol] = 1;
					break;
				}
	}
	else {
		if (first)
			for (list*a = first->head; a; a = a->next)	 //заполняем отображение по первому множеству
				u[a->symbol] = 1;

		if (second)
			for (list*a = second->head; a; a = a->next)	//и по второму туда же
				u[a->symbol] = 1;


	}
	if (c) //если на вход принимаются B и D, то отображение инвертируем по условию (~)
		for (int i = 0; i < 16; ++i)
			u[i] == 1 ? u[i] = 0 : u[i] = 1;

	return u;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
int* check_02(int* a, int b, int c) {

	if (!a) {	//при первом заходе создаём массив и впихуеваем цифру
		a = new int;
		a[b] = c; //записываем число в массив
		
	}
	else {		//при последующих увеличиваем память на 1 ячейку и впихуеваем цифру
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
		cout << "Множество '" << strings(b) << "': { ";
		for (list *p = A->head; p; p = p->next)
		{
			if (p->next)
				cout << hex << p->symbol << "; ";
			else cout << hex << p->symbol << " ";
		}
		cout << "}" << endl;
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
		freemem(B, C, D, E, E, a + 1); //рекурсивно хуячим по функции пока не дойдем до E(тогда a == 4 и мы выйдем)
	return NULL;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------