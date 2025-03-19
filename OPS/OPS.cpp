// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
//#include <stack>
using namespace std;

struct  Stack {
private:
    Stack* next = nullptr;
	string data="2";
public:
	Stack* create() {
		Stack* p_begin = new Stack;
		return p_begin;
	}
	void push(Stack* &p_begin,string x) {
		Stack * p;
		p = p_begin;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = new Stack;
		p->data = x;
		p->next->next = nullptr;


	}
	void print_List(Stack* p_begin) {
		Stack* p;
		p = p_begin;
		if (p != nullptr) {
			while (p->next != nullptr) {
				//cout << p->next << endl;
				cout << p->data << endl;
				p = p->next;
			}
		}
		else {
			cout << "Stack is null" << endl;
		}
		
	}
	int size(Stack* p_begin) {
		Stack* p, n;
		int i = 0;
		p = p_begin;
		if (p != nullptr) {
			while (p->next != nullptr) {
				//cout << p->next << endl;
				i++;
				//cout << p->data << endl;
				p = p->next;
			}
		}
		else {
			i = 0;
		}
		return i;
	}
	string top(Stack* p_begin) {
		Stack* p;
		p = p_begin;
			string x;
			x = p->data;
			while (p->next != nullptr) {
				//cout << p->next << endl;
				x = p->data;
				p = p->next;
			}
			return x;
		
	}
	void pop(Stack* &p_begin){
		Stack* p;
		Stack* n;
		p = p_begin;
		if (size(p_begin) == 1) {
			Stack* t = p_begin;
			p_begin = create();
			delete t;
		}
		else {
			for (int i = 1; i < size(p_begin); i++)
			{
				p = p->next;
			}
			n = p;
			delete p->next->next;
			n->next = nullptr;
		}
		
	}
	

};
struct Calculator
{
	Stack stack;// обьект струкрутра стека
	const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
	int get_priority(string x, int p = 0) {
		if (x == "(" || x == ")") {
			return 0;
		}
		else if (x == "+" || x == "-") {
			return 1;
		}
		else if (x == "*" || x == "/") {
			return 2;
		}
		else if (x == "^") {
			return 3;
		}
		else if (x == "-" && p == 1) {
			return 4;
		}
	}
	pair<string,int> get_digit(string x, int i = 0) {
		string xi;
		pair<string, int> digit;
		for (i; i < x.size(); i++) {
			xi = x[i];
			if (operations.count(xi) == 0) {
				digit.first = digit.first + xi;
			}
			else {
				digit.second = i;
				return digit;
			}
		}
	}
	double operationsa_procces(Stack* p_begin) {
		double ot;
		while (stack.size(p_begin) > 0) {
			ot = ot + stoi(stack.top(p_begin));
			stack.pop(p_begin);
		}
		stack.push(p_begin, to_string(ot));
	}
	void sort_station() {


	}
	double stack_machine(string expression) {
		string word;
		Stack* p_begin = stack.create();
		
		//stack.print_List(p_begin);
		stringstream ex_ss(expression);
		double ot = 0;// значение по умолчанию
		while (ex_ss >> word) {
			if (operations.count(word) == 0) {
				stack.push(p_begin, word);
			}
			else {
				while (stack.size(p_begin) > 0) {
					ot = ot + stoi(stack.top(p_begin));
					stack.pop(p_begin);
				}
				stack.push(p_begin, to_string(ot));
			}
			
		}
		//stack.print_List(p_begin);
		return ot;
	}
};
int main()
{
	cout << "Hello user" << endl;
	string data;
	string da;
	 bool k = false;
	 Calculator cal;
	 cout << cal.stack_machine("1 1 100  +") << endl;;
	 ///stack<string>x;
	 //cout << cal.get_digit("012+1212").second << endl;
	 /*
	 
	 do
	 {
		 cout << "Input equation" << endl;
		 getline(cin, data);
	 } while (k);
	 */
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
