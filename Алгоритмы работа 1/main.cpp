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
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Некорректный ввод! Повторите" << endl;
			}
		}
	} while (true);

	spisok = (int*)malloc(a * sizeof(int));

	for (int i = 0; i < a; i++) { //вводим массив
		do {
			cout << endl << "Введите значение для множества '" << strings(b) << "' в 16СС: ";
			if (!(cin >> hex >> spisok[i]))
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Некорректный ввод! Повторите" << endl;
			}
			else break;

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
	bool x, x1, x2;
	if (!A) return E;

	for (list *p = A->head; p; p = p->next)
	{
		x = false;

		if (E)
		{
			for (list *d = E->head; d; d = d->next)
			{ //сверяем A/C с E
				if (p->symbol == d->symbol)
				{
					x = true;
					break;
				}

			}
			if (!x && B) //Если в E не нашлось, то
			{
				for (list *d = B->head; d; d = d->next)//Сверяем с B
				{
					if (p->symbol == d->symbol)
					{
						x = true;
						break;
					}
				}
				if (x) //Если в B нашлось, то
				{
					x = false;
					if (D)
						for (list *d = D->head; d; d = d->next) //Сверяем с D
						{
							if (p->symbol == d->symbol)
							{
								x = true;
								break;
							}
						}
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
				for (list *d = B->head; d; d = d->next)//Сверяем с B
				{
					if (p->symbol == d->symbol)
					{
						x = true;
						break;
					}
				}
			}
			if (x) //Если есть в B, то сверяем с D
			{
				x = false;
				if (D)
					for (list *d = D->head; d; d = d->next)
					{
						if (p->symbol == d->symbol)
						{
							x = true;
							break;
						}
					}
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