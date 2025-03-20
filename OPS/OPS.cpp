// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>

#include <stack>
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
	Stack stack1;// обьект струкрутра стека
	const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
	const set<string> one_operations = {"sin","cos","tg"}; // операции доступные сейчас 
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
	void operationsa_procces(Stack* p_begin, string operation, bool one_opertion = false) {
		if (operation == "+") {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b + a));
		}
		else  if (operation == "-" && one_opertion == false) {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b - a));
		}
		else  if (operation == "*") {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b * a));
		}
		else  if (operation == "/") {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b / a));
		}
		else  if (operation == "^") {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(pow(b, a)));
		}
		else  if (operation == "-" && one_opertion) {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(a * -1));
		}
		else  if (operation == "sin" && one_opertion) {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(sin(a)));
		}
		else  if (operation == "cos" && one_opertion) {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(cos(a)));
		}
		else  if (operation == "tg" && one_opertion) {
			double a = stoi(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(tan(a)));
		}

	}
	double stack_machine(string expression) {
		string word;
		Stack* p_top = stack1.create();
		stringstream ex_ss(expression);
		double ot = 0;// значение по умолчанию
		while (ex_ss >> word) {
			if (operations.count(word) == 0 && one_operations.count(word) == 0) {
				stack1.push(p_top, word);
				//cout << stack.top(p_top) << endl;
			}
			else {
				if (stack1.isEmpty(p_top)|| one_operations.count(word) == 1) {
					string opernd = word;// записываем унарную операцию
					ex_ss >> word;
					stack1.push(p_top, word);
					operationsa_procces(p_top, opernd, true);
				}
				else {
					operationsa_procces(p_top, word);
				}


			}

		}
		ot = stof(stack1.top(p_top)); 
		//для большей точности используй 
		//long double num_ld = std::stold("123.456");
		stack1.pop(p_top);
		return ot;
	}
	pair<string, int> get_digit(string x, int i = 0) {
		string xi;
		pair<string, int> digit;
		digit.first = "";
		digit.second = 0;
		for (i; i < x.size(); i++) {
			xi = x[i];
			if (isdigit(x[i])) {
				digit.first = digit.first + xi;
				digit.second = digit.second + 1;
			}
			else {
				break;
			}
		}
		return digit;

	}
	pair<string, int> get_text(string xv, int j = 0) {
		string xi;
		pair<string, int> text;
		//text.first = "fuck";
		text.first = "";
		text.second = 0;
		for (j; j < xv.size(); j++) {
			xi = xv[j];
			if (!isdigit(xv[j])) {
				if (operations.count(xi) == 1 && operations.count(text.first) == 1) {
					break;
				}
				else {
					text.first = text.first + xi;
					text.second = text.second + 1;
				}
				
			}
			else {
				//cout << "dfdf" << endl;
				//text.second = j;
				break;
			}
		}
		return text;
	}

	string sort_station(string expression) {
		string output = "";
		stack<string> op_stack;
		int size = expression.size();

		for (int i = 0; i < size;) {
			if (isdigit(expression[i])) {
				//если число то 
				pair<string, int> digit = get_digit(expression, i);
				if (output == "") {
					output = digit.first;
				}
				else {
					output += " " + digit.first;
				}
				i = i + digit.second;
			}
			else {
				pair<string, int> text = get_text(expression, i);
				string x = text.first;
				i =i + text.second;
				//cout << x << endl;
				if (x == "(" || op_stack.empty()|| get_priority(x) > get_priority(op_stack.top())) {
					op_stack.push(x);
					//cout << x << endl;
				}
				else if (get_priority(x) <= get_priority(op_stack.top()) && get_priority(x)>0) {
					while (!op_stack.empty() &&
						get_priority(x) <= get_priority(op_stack.top())) {
						output += " " + op_stack.top();
						op_stack.pop();
					}
					op_stack.push(x);
				}
				else if (x == ")") {
					//cout << "ss" << endl;
					while (op_stack.empty() || op_stack.top() != "(") {
						//cout << op_stack.top() << endl;
						//cout << (op_stack.top() == "(") << endl;
						output += " " + op_stack.top();
						op_stack.pop();
					}
					//cout << op_stack.top() << endl;
					op_stack.pop();
					// Удаляем ")"
					/*
					
					if (op_stack.empty()) {
						throw runtime_error("Mismatched parentheses");
					}
					*/
					//op_stack.pop(); // Удаляем "("
				}
			}
		}

		while (!op_stack.empty()) {
			output += " " + op_stack.top();
			op_stack.pop();
		}

		return output;
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
	//cout << cal.stack_machine("1 2 + 4 -") << endl;;
	 //string x = cal.get_digit("12244+").first;
	 cout << cal.sort_station("-1") << endl;
	 cout << cal.stack_machine("tg 5") << endl;;
	//cout << x << endl;
	// cout << "NEW" << endl;
	 //string y = cal.get_text("122+", cal.get_digit("122+").second).first;
	 //cout << y << endl;
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
