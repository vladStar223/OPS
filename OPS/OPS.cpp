// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
#include<deque>
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
Stack stack1;// струкрутра стека
const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
const set<string> one_operations = { "sin","cos","tg","sqrt" }; // операции доступные сейчас 
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
		return 10;
	}
	else if (x == "sin" || x == "cos" || x == "tg" || x == "sqrt") {
		return 5;
	}
}
void operationsa_procces(Stack* p_begin, string operation, bool one_opertion = false) {
	if ((one_opertion == false && (stack1.get_size(p_begin) <= 1))) {
		throw runtime_error("Error");
	}
	else {
		if ((operation == "+" || operation == "/" || operation == "*" || operation == "^") && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(a));
		}
		else if (operation == "+") {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b + a));
		}
		else  if (operation == "-" && one_opertion == false) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b - a));
		}
		else  if (operation == "*") {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(b * a));
		}
		else  if (operation == "/") {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			if (a == 0) {
				throw runtime_error("delenie na 0");
			}
			else {
				stack1.push(p_begin, to_string(b / a));
			}

		}
		else  if (operation == "^") {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			double b = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(pow(b, a)));
		}
		else  if (operation == "-" && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(a * -1));
		}
		else  if (operation == "sin" && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(sin(a)));
		}
		else  if (operation == "cos" && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(cos(a)));
		}
		else  if (operation == "tg" && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(tan(a)));
		}
		else  if (operation == "sqrt" && one_opertion) {
			double a = stof(stack1.top(p_begin));
			stack1.pop(p_begin);
			stack1.push(p_begin, to_string(sqrt(a)));
		}
	}


}
double stack_machine(string expression) {
	string word;
	Stack* p_top = stack1.create();
	stringstream ex_ss(expression);
	double ot = 0;// значение по умолчанию
	while (ex_ss >> word) {
		//cout << word << endl;
		if (operations.count(word) == 0 && one_operations.count(word) == 0) {
			stack1.push(p_top, word);
		}
		else {
			if (stack1.get_size(p_top) <= 1 || one_operations.count(word) == 1) {
				if (stack1.get_size(p_top) == 0) {
					throw runtime_error("Error");
				}
				//string opernd = word;// записываем унарную операцию
				//ex_ss >> word;
				//stack1.push(p_top, word);

				operationsa_procces(p_top, word, true);


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
	Stack* p_top = stack1.create();
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
			if (x == "(" || stack1.isEmpty(p_top) || get_priority(x) > get_priority(stack1.top(p_top))) {
				stack1.push(p_top,x);
			}
			else if (get_priority(x) <= get_priority(stack1.top(p_top)) && get_priority(x) > 0) {
				while (!stack1.isEmpty(p_top) &&
					get_priority(x) <= get_priority(stack1.top(p_top))) {
					output += " " + stack1.top(p_top);
					stack1.pop(p_top);
				}
				stack1.push(p_top,x);
			}
			else if (x == ")") {
				//cout << "ss" << endl;
				while (stack1.isEmpty(p_top) || stack1.top(p_top) != "(") {
					//cout << stack1.top() << endl;
					//cout << (stack1.top() == "(") << endl;
					if (stack1.isEmpty(p_top)) {
						throw runtime_error("Mismatched parentheses");
					}
					output += " " + stack1.top(p_top);
					stack1.pop(p_top);
				}
				if (stack1.isEmpty(p_top)) {
					throw runtime_error("Mismatched parentheses");
				}
				//cout << op_stack.top() << endl;
				stack1.pop(p_top);
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
						if (x == "(" || stack1.isEmpty(p_top) || get_priority(x) > get_priority(stack1.top(p_top))) {
							prev = true;
							stack1.push(p_top,x + " -1 *");
						}
						else if (get_priority(x) <= get_priority(stack1.top(p_top)) && get_priority(x) > 0) {
							while (!stack1.isEmpty(p_top) &&
								get_priority(x) <= get_priority(stack1.top(p_top))) {
								output += stack1.top(p_top);
								stack1.pop(p_top);
							}
							stack1.push(p_top,x);
						}
						else if (x == ")") {
							//cout << "ss" << endl;
							while (stack1.isEmpty(p_top) || stack1.top(p_top) != "(") {
								//cout << stack1.top() << endl;
								//cout << (stack1.top() == "(") << endl;
								output += stack1.top(p_top);
								stack1.pop(p_top);
							}
							//cout << stack1.top() << endl;
							if (stack1.isEmpty(p_top)) {
								throw runtime_error("Mismatched parentheses");
							}
							stack1.pop(p_top);
							prev = false;
							// Удаляем ")"
							/*


							*/
							//stack1.pop(); // Удаляем "("
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

	while (!stack1.isEmpty(p_top)) {
		output += " " + stack1.top(p_top);
		stack1.pop(p_top);
	}

	return output;
}

void print() {}
int main()
{
	cout << "Hello user" << endl;
	string data;
	string da;
	bool k = false;
	//cout << "sdsd" << endl;
	string expression;
	string sort_station1;
	string x = "1";

	do
	{
		try
		{
			cout << "Input fun" << endl;
			cout << "For correct work use (-1) + (-1)" << endl;
			cout << "1 is input expression" << endl;
			cout << "2 is exit" << endl;
			getline(cin, x);
			if (stoi(x) == 1) {
				cout << "Input" << endl;
				getline(cin, expression);
				//expression = "1 1 +";
				sort_station1 = sort_station(expression);
				//cout << sort_station << endl;
				//sort_station = "-1-1";`
				//cout << sort_station << endl;
				cout << expression << " = " << stack_machine(sort_station1) << endl;;

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
