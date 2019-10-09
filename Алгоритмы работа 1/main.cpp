#include <stdio.h>
#include <iostream>
#include <locale.h>
using namespace std;

struct list
{
	int symbol;
	list* next;
	list* head;
};	

//-----------------------описание функций--------------------
char strings(int a);//вспомогательная функция для вывода наименования множества
list* input(int b);//функция ввода массива
void incorrect();//функция для сообщения об ошибке ввода
list* arrtolist(int* spisok, int b);//функция перевода массива в список
list* check(list* A, list* C, list *B, list *D);//функция проверки основного условия
int* check_01(int* spisok, int first, int second, int third);//вспомогательная функция проверки основного условия
void output(list *E);//функция вывода результата на экран
list* freemem(list* A, list* B, list* C, list* D, list* E);//функция очистки памяти
void freemem_01(list*A);//вспомогательная функция очистки памяти
//------------------------------------------------------------

int main()
{
	setlocale(LC_ALL, "RUS");
	list *A, *B, *C, *D, *E;

	A = input(0);
	B = input(1);
	C = input(2);
	D = input(3);
	E = check(A, C, B, D);

	output(E);

	freemem(A, B, C, D, E);
	
	return 0;
}

char strings(int a)
{

	switch (a)
	{
	case 0: {return 'A'; }
	case 1: {return 'B'; }
	case 2: {return 'C'; }
	case 3: {return 'D'; }
	}

}

list* input(int b)
{
	int* spisok = NULL;
	int a;
	cout << endl << "Введите количество элементов множества '" << strings(b) << "' (от 0 до 16):";
	do
	{
		if (cin >> a && a >= 1 && a <= 16) break;
		else
		{
			if (a == 0)
			{
				cout << "Вы ввели пустое множество '" << strings(b) << "' !" << endl;
				system("pause");
				return NULL;
			}
			else incorrect();
		}
	} while (true);

	spisok = new int[a];

	for (int i = 0; i < a; i++) { //вводим массив
		do {
			cout << endl << "Введите значение для множества '" << strings(b) << "' в 16СС: ";
			if (!(cin >> hex >> spisok[i]))
				incorrect();
			else break;

		} while (true);
	}



	system("pause");
	return arrtolist(spisok, a)->head;
}

void incorrect() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Некорректный ввод! Повторите" << endl;
}

list* arrtolist(int* spisok, int b) {
	list* A = NULL;
	A = new list;
	A->head = A;

	for (int i = 0; i < b; i++) //заполняем список из массива
	{ 
		A->symbol = spisok[i];
		if (i != b - 1) {
			A->next = new list;
			A->next->head = A->head;
			A = A->next;
		}
	}

	delete spisok;
	A->next = NULL;
	return A;
}

list* check(list* A, list* C, list *B, list *D)
{
	list* E = NULL;
	bool x = false;
	if (!A || !C) return E;

	int* spisok = NULL; //массив, который потом запишим в множество E(результат)

	for (list *frst = A->head, *scnd = C->head; frst, scnd; frst = frst->next, scnd = scnd->next) //делаем цикл сразу по A и C одновременно
	{
		x = false;
		if (spisok) {
			for (int i = 0; i < (_msize(spisok) / sizeof(int)); i++) //сверяем с E(если уже есть)
				if (spisok[i] == frst->symbol || spisok[i] == scnd->symbol) {
					x = true;
					break;
				}
			if (x) continue; //скипаем все остальные проверки тк в E уже есть такое число
		}

		for (list* thrd = B->head; thrd; thrd = thrd->next) //сверяем с B
			if (frst->symbol != thrd->symbol || scnd->symbol != thrd->symbol) { //если нету хотя бы одного то идем проверять какого именно
				spisok = check_01(spisok, frst->symbol, scnd->symbol, thrd->symbol);
				x = true;
				break;
			}
		if (!x) //если не нашли в B то
			for (list* thrd = D->head; thrd; thrd = thrd->next) //сверяем с D
				if (frst->symbol != thrd->symbol || scnd->symbol != thrd->symbol) { //если нету хотя бы одного то идем проверять какого именно
					spisok = check_01(spisok, frst->symbol, scnd->symbol, thrd->symbol);
					break;
				}
	}

	int i = (_msize(spisok) / sizeof(int)) - 1; //получаем длинну массива уродским способом за который мне стыдно
	spisok = (int*)realloc(spisok, (i - 1) * sizeof(int)); //убераем последний элемент в массиве тк я дыбил и там пустая ячейка
	return arrtolist(spisok, i + 1)->head;
}

int* check_01(int* spisok, int first, int second, int third) {
	if (!spisok)
		spisok = new int[1];
	int i = (_msize(spisok) / sizeof(int)) - 1; //длинна массива а также последний элемент

	if (first != second) { //если A и C не равны, то
		if (first != third && second != third) { //если они оба подходят под условие, то и запихиваем оба
			spisok = (int*)realloc(spisok, (i + 3) * sizeof(int));
			spisok[i] = first;
			spisok[i + 1] = second;
			return spisok;
		}
		spisok = (int*)realloc(spisok, (i + 2) * sizeof(int)); //заранее выделяем память под 1 элемент
		if (first != third) { //если только A подходит под условие
			spisok[i] = first;
			return spisok;
		}
		else if (second != third) { //если только C подходит под условие
			spisok[i] = second;
			return spisok;
		}
	}
	else {
		spisok[i] = first; //тут нам по барабану че пихать тк A и C равны
		return spisok;
	}
}

void output(list *E)
{
	if (E)
	{
		cout << "Сформированное множество E: { ";
		for (list *p = E->head; p; p = p->next)
		{
			if (p->next)
				cout << hex << p->symbol << "; ";
			else cout << hex << p->symbol << " ";
		}
		cout << "}" << endl;
	}
	else cout << "Множество E - пустое" << endl;

	system("pause");
}

list* freemem(list* A, list* B, list* C, list* D, list* E) {
	char arr[5] = { 'A','B','C','D','E' };
	if (!A) return NULL;
	A = A->head;
	if (!A->next) {
		delete A;
		return NULL;
	}
	freemem_01(A);
	freemem_01(B);
	freemem_01(C);
	freemem_01(D);
	freemem_01(E);

	return NULL;
}

void freemem_01(list*A) {
	for (list *p = A->head->next; p; p = p->next) {
		delete A;
		A = p;
	}
	delete A;
}