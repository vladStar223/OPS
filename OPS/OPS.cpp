﻿// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
using namespace std;

struct Node {
	Node* next = nullptr;
	string data;
};

struct Stack {
private:
	
	Node* node = nullptr;
	int size = 0;
public:
	// Создание стека (не требуется, можно использовать конструктор)
	static Stack* create() {
		return new Stack();
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
		p_top->size = p_top->size + 1;
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
		return (p_top->node == nullptr);
	}
	int get_size(Stack*& p_top) {
		return p_top->size;
	}
};
const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
const set<string> one_operations = { "sin","cos","tg","sqrt" }; // операции доступные сейчас 
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
		if (operations.count(xi) == 1) {
			if (text.first.empty()) {
				text.first = xi;
				text.second = 1;
			}
			break;
		}
		if (!isdigit(xv[j])) {

			text.first = text.first + xi;
			text.second = text.second + 1;

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
	string xi = "";
	pair<string, int> digit;
	pair<string, int> text;
	bool prev = false; // есть ли скобка
	for (int i = 0; i < size;) {
		xi = expression[i];
		if (!isdigit(expression[i]) && xi != "-" && xi != ".") {
			text = get_text(expression, i);
			string x = text.first;
			i = i + text.second;
			//cout << x << endl;
			if (x == "(" || op_stack.empty() || get_priority(x) > get_priority(op_stack.top())) {
				op_stack.push(x);
			}
			else if (get_priority(x) <= get_priority(op_stack.top()) && get_priority(x) > 0) {
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
					if (op_stack.empty()) {
						throw runtime_error("Mismatched parentheses");
					}
					output += " " + op_stack.top();
					op_stack.pop();
				}
				if (op_stack.empty()) {
					throw runtime_error("Mismatched parentheses");
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
		else {
			if (xi == ".") {
				output += ".";
				i = i + 1;
				digit = get_digit(expression, i);
				output += digit.first;
				i = i + digit.second;
			}
			else {
				if (xi == "-") {
					i = i + 1;
					if (isdigit(expression[i])) {
						digit = get_digit(expression, i);
						if (output == "") {
							output = "-" + digit.first;
						}
						else {

							output += " -" + digit.first;


						}
						i = i + digit.second;
					}
					else {
						text = get_text(expression, i);
						string x = text.first;
						i = i + text.second;
						if (x == "(" || op_stack.empty() || get_priority(x) > get_priority(op_stack.top())) {
							prev = true;
							op_stack.push(x + " -1 *");
						}
						else if (get_priority(x) <= get_priority(op_stack.top()) && get_priority(x) > 0) {
							while (!op_stack.empty() &&
								get_priority(x) <= get_priority(op_stack.top())) {
								output += op_stack.top();
								op_stack.pop();
							}
							op_stack.push(x);
						}
						else if (x == ")") {
							//cout << "ss" << endl;
							while (op_stack.empty() || op_stack.top() != "(") {
								//cout << op_stack.top() << endl;
								//cout << (op_stack.top() == "(") << endl;
								output += op_stack.top();
								op_stack.pop();
							}
							//cout << op_stack.top() << endl;
							if (op_stack.empty()) {
								throw runtime_error("Mismatched parentheses");
							}
							op_stack.pop();
							prev = false;
							// Удаляем ")"
							/*


							*/
							//op_stack.pop(); // Удаляем "("
						}

					}
				}
				else {
					//если число то 
					digit = get_digit(expression, i);
					if (output == "") {
						output = digit.first;
					}
					else {
						output += " " + digit.first;
					}
					i = i + digit.second;
				}
			}

		}
	}

	while (!op_stack.empty()) {
		output += " " + op_stack.top();
		op_stack.pop();
	}

	return output;
}
int main()
{
	cout << "Hello user" << endl;
	string data;
	string da;
	 bool k = false;
	 //cout << "sdsd" << endl;
	 Calculator cal;
	 string expression;
	 string sort_station;
	 string x = "1";
	 
		 do
		 {
			 try
			 {
			 cout << "Input fun" << endl;
			 cout << "For correct work use (-1) + (-1)" << endl;
			 cout << "1 is input expression" << endl;
			 cout << "2 is exit" << endl;
			 cin >> x;
			 if (stoi(x) == 1) {
				 cout << "Input" << endl;
				 cin >> expression;
				 cout << sort_station(expression) << endl;;
				 //cout << sort_station << endl;
				 //sort_station = "-1-1";
				 //cout << sort_station << endl;
				 //cout << expression << " = " << cal.stack_machine(sort_station) << endl;;

			 }
			 else if (stoi(x) == 2) {
				 k = false;
				 break;
			 }
			 else {
				 cout << "You are Strange" << endl;
				 break;
			 }
			 }
			 catch (runtime_error exception)
			 {
				 cout << exception.what() << endl;
			 }
			 catch (const std::exception&)
			 {
				 cout << "Unhandle error" << endl;
			 }

		 } while (!k);
		 cout << "Thank for using" << endl;
	
	
	 
	

}
/*
/стабильная версия точно
//test git
// test git 2
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
