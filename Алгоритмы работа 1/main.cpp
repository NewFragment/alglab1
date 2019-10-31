#include <stdio.h>
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
	case 4: {return 'E'; }
	}

}

void incorrect() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Некорректный ввод! Повторите" << endl;
}

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

	list* A = new list;
	A->head = A;

	int i = 0;
	do { //заполняем список из массива
		A->symbol = spisok[i];
		if (i + 1 != a) {
			A->next = new list;
			A->next->head = A->head;
			A = A->next;
		}
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
	E = NULL;
	A = input(0);
	B = input(1);
	C = input(2);
	D = input(3);
	E = check(C, B, D, E);
	output(A, 0);
	output(B, 1);
	output(C, 2);
	output(D, 3);
	output(E, 4);
	system("pause");
	A = freemem(A);
	B = freemem(B);
	C = freemem(C);
	D = freemem(D);
	E = freemem(E);

	return 0;

}