// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
//#include <stack>
using namespace std;

struct Node
{
	Node* next = nullptr;
	string data = "2";
};
struct  Stack {
private:
	Node* node = nullptr;
public:
	Stack* create() {
		return nullptr;
	}
	void push(Stack*& p_top, string x) {
		Node* n = new Node;
		n->data = x;
		n->next = nullptr;
		if (p_top == nullptr) {
			p_top = new Stack; 
			p_top->node = n;
		}
		else {
			n->next = p_top->node;
			p_top->node = n;
		}

	}
	string top(Stack* p_top) {
		if (p_top == nullptr) {
			throw "Error";
		}
		return p_top->node->data;
	}
	void pop(Stack*& p_top) {
		if (p_top == nullptr) {
			throw "Error";
		}
		else {
			Node* t = p_top->node;
			p_top->node = p_top->node->next;
			delete t;
		}
	}
	bool isEmpty(Stack*& p_top) {
		return (p_top == nullptr);
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
	void operationsa_procces(Stack* p_begin,string operation) {
		if (operation == "+") {
			double a =  stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(b+a));
		}
		else  if (operation == "-") {
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(b - a));
		}
		else  if (operation == "*") {
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(b * a));
		}
		else  if (operation == "/") {
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(b / a));
		}
		else  if (operation == "^") {
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(pow(b,a)));
		}
		else  if (operation == "-" && stack.isEmpty(p_begin)) {
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(-a));
		}
		
	}
	void sort_station() {


	}
	double stack_machine(string expression) {
		string word;
		Stack *p_top = stack.create();
		stringstream ex_ss(expression);
		double ot = 0;// значение по умолчанию
		while (ex_ss >> word) {
			if (operations.count(word) == 0) {
				stack.push(p_top, word);
				//cout << stack.top(p_top) << endl;
			}
			else {
					operationsa_procces(p_top, word);
				}
			
		}
		ot = stoi(stack.top(p_top));
		stack.pop(p_top);
		return ot ;
	}
};
int main()
{
	cout << "Hello user" << endl;
	string data;
	string da;
	 bool k = false;
	 //cout << "sdsd" << endl;
	 Calculator cal;
	 cout << cal.stack_machine("- 3 4 + 5") << endl;;
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
