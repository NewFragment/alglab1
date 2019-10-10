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

list* freemem(list* A) {
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

	return NULL;
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

void incorrect() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Некорректный ввод! Повторите" << endl;
}

list* input(list* A, int b)
{
	int *spisok;
	spisok = NULL;
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
				return NULL;
			}
			else
				incorrect();
			
		}
	} while (true);

	spisok = new int[a];

	for (int i = 0; i < a; i++) { //вводим массив
		do {
			cout << endl << "Введите значение для множества '" << strings(b) << "' в 16СС: ";
			if ((cin >> hex >> spisok[i]) && spisok[i] < 16)
			{
				break;
			}
			else
				incorrect();

		} while (true);
	}

	A = new list;
	A->head = A;

	int i = 0;
	do { //заполняем список из массива
		A->symbol = spisok[i];
		A->next = new list;
		A->next->head = A->head;
		A = A->next;
		i++;
	} while (i != a);
	delete spisok;

	system("pause");
	A->next = NULL;
	return A->head;
}

bool alg(list* d, int a) {
	for (d; d; d = d->next)
	{ 
		if (a == d->symbol)
		{
			return true;
		}

	}
	return false;
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

list* check(list* A, list *B, list *D, list *E)
{
	bool x;
	if (!A) return E;

	for (list *p = A->head; p; p = p->next)
	{
		x = false;

		if (E)
		{
			
			x = alg(E->head, p->symbol); //сверяем A с E

			if (!x && B) //Если в E не нашлось, то
			{
				
				x = alg(B->head, p->symbol); //Сверяем с B

				if (x) //Если в B нашлось, то
				{
					x = false;
					if (D)
					x = alg(D->head, p->symbol); //сверяем с D
				}
			}
			if (!x)
			{

				E->next = new list;
				E->next->head = E->head;
				E = E->next;
				E->symbol = p->symbol;
				E->next = NULL;

			}
		}
		else
		{
			if (B)
			{
				x = alg(B->head, p->symbol); //Сверяем с B
			}
			if (x) //Если есть в B, то сверяем с D
			{
				x = false;
				if (D)
					x = alg(D->head, p->symbol); //сверяем с D
			}
			if (!x)
			{
				E = new list;
				E->head = E;
				E->symbol = p->symbol;
				E->next = NULL;
			}
		}
	}



	return E;
}

int main()
{

	setlocale(LC_ALL, "RUS");

	list *A, *B, *C, *D, *E;
	A = NULL;
	B = NULL;
	C = NULL;
	D = NULL;
	E = NULL;

	A = input(A, 0);
	B = input(B, 1);
	C = input(C, 2);
	D = input(D, 3);
	E = check(A, B, D, E);
	E = check(C, B, D, E);
	output(E);

	A = freemem(A);
	B = freemem(B);
	C = freemem(C);
	D = freemem(D);
	E = freemem(E);

	return 0;

}