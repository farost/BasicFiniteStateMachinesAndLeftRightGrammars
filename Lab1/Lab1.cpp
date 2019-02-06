/* Новоселов Георгий, студент группы БИВ164. Лабораторная работа №1.
Вариант студента: 17
Варианты заданий: 3, 5, 2.
Задание 1: Вариант 3. Написать программу, строящую лево- и правостороннюю грамматику:
A0::=B, 1A::=C, As::=0, 0B::=D, 1B::=B, Bs::=0, 0C::=C, 1C::=D, Cs::=0, 0D::=D, 1D::=D, Ds::=1. 
Программа должна поддерживать смену нетерминалов в матрице конечного автомата.
Задание 2: Вариант 5. Построить программу конечного распознавателя для заданного языка:
каждый третий символ - "1".
Задание 3: Вариант 2. Построить КА для распознавания цепочек и анализа ошибок, которые:
представляют собой идентификаторы целого типа в Фортране, начинающиеся с I, J, K, L, M N.
*/

#include "stdafx.h"
#include "FSMTable.h"

void InNumbers(int *n, int *m) {
	std::cout << "Number of states: ";
	while (!(std::cin >> *n) || (*n < 1) || (*n > 20)) {
		std::cout << "ERROR: Not an integer between 1 and 20.\nNumber of states: ";
		std::cin.clear();
		std::cin.ignore(132, '\n');
	}

	std::cout << "Number of letters: ";
	while (!(std::cin >> *m) || (*m < 1) || (*m > 20)) {
		std::cout << "ERROR: Not an integer between 1 and 20.\nNumber of letters: ";
		std::cin.clear();
		std::cin.ignore(132, '\n');
	}
}


void ChangeState(FSMTable *FSM) {
	int n, m, s, l, ifchange = 1;
	char c;
	do {
		std::cout << "Do you want to change a cell? (1/0)" << std::endl;
		std::cin >> n;
		if (n != 1 && n != 0)
			std::cout << "ERROR: Type the number '1' or '0'." << std::endl;
		else if (n) {
			std::cout << "State: ";
			std::cin >> s;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Letter: ";
			std::cin >> l;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "New cell's info: ";
			std::cin >> c;
			if (!FSM->ChangeTerminal(s, l, c)) std::cout << "ERROR: Cannot change this cell" << std::endl;
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "The matrix have been changed. Do you want to print it? (1/0)" << std::endl;
				std::cin >> m;
				if (m) FSM->PrintMatrix();
			}
		}
		else ifchange = 0;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (ifchange);
}


void ChangeStatesName(FSMTable *FSM) {
	int n, m, ifchange = 0;
	char c, nw;
	do {
		std::cout << "Do you want to change a state's name? (1/0)" << std::endl;
		std::cin >> n;
		if (n != 1 && n != 0)
			std::cout << "ERROR: Type the number '1' or '0'." << std::endl;
		else if (n) {
			std::cout << "Prev state's name: ";
			std::cin >> c;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "New state's name: ";
			std::cin >> nw;
			FSM->ChangeTerminalAll(c, nw);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Do you want to print matrix? (1/0)" << std::endl;
			std::cin >> m;
			if (m) FSM->PrintMatrix();
		}
		else ifchange = 1;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!ifchange);
}


void Task1(FSMTable *FSM) {
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	if (!FSM->PrintGrammar('r')) std::cout << "Error in printing Right grammar." << std::endl;
	std::cout << "Left grammar:" << std::endl;
	if (!FSM->PrintGrammar('l')) std::cout << "Error in printing Left grammar." << std::endl;
}


void Task2(FSMTable *FSM) {
	std::cout << "Our language: every 3rd symbol - 1." << std::endl;
	FSM->MakeMatrixTask2();
	std::cout << "Printing the Task 2 Matrix:" << std::endl;
	FSM->PrintMatrix();
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	FSM->PrintGrammar('r');
	std::cout << "Left grammar:" << std::endl;
	FSM->PrintGrammar('l');
}

void Task3(FSMTable *FSM) {
	std::cout << "Our language - Fortran's integers. Latin's alphabet & numbers." << std::endl;
	FSM->MakeMatrixTask3();
	std::cout << "Printing the Task 3 Matrix:" << std::endl;
	FSM->PrintMatrix();
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	FSM->PrintGrammar('r');
	std::cout << "Left grammar:" << std::endl;
	FSM->PrintGrammar('l');
}


int main()
{
	char task;
	int br = 0;
	FSMTable Task1FSM, Task2FSM, Task3FSM;
	do {
		std::cout << "What task do you want to check?" << std::endl;
		std::cin >> task;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (task) {
		case '0':
			br = 1;
			break;
		case '1':
			int n, m;
			InNumbers(&n, &m);
			if (!Task1FSM.MakeMatrixUser(n, m))
				std::cout << "ERROR: Cannot make matrix." << std::endl;
			else {
				std::cout << "Matrix made successfully." << std::endl;
				Task1FSM.PrintMatrix();
			}

			ChangeState(&Task1FSM);
			ChangeStatesName(&Task1FSM);

			Task1(&Task1FSM);
			std::cout << "FIRST DONE" << std::endl;
			break;

		case '2':
			Task2(&Task2FSM);
			break;

		case '3':
			Task3(&Task3FSM);
			break;

		default:
			std::cout << "I don't understand you. Please retry." << std::endl;
			break;
		}
	} while (!br);

	std::cout << "Thank you, goodbye!" << std::endl;
	system("pause");
    return 0;
}

