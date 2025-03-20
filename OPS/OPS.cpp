// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
#include <cctype>
//#include <stack>
using namespace std;

struct Node {
	Node* next;
	string data;

	Node(const string& value) : next(nullptr), data(value) {}  // Явная инициализация
};

struct Stack {
private:
	Node* top_node = nullptr;  // Вершина стека

public:
	// Создание стека (не требуется, можно использовать конструктор)
	static Stack* create() {
		return new Stack();
	}

	// Добавление элемента
	void push(Stack* p_begin,const string& x) {
		Node* new_node = new Node(x);
		new_node->next = top_node;
		top_node = new_node;
	}

	// Получение верхнего элемента
	string top(Stack* p_begin) const {
		if (isEmpty(p_begin)) {
			throw runtime_error("Stack is empty");
		}
		return top_node->data;
	}

	// Удаление верхнего элемента
	void pop(Stack* p_begin) {
		if (isEmpty(p_begin)) {
			throw runtime_error("Stack underflow");
		}
		Node* temp = top_node;
		top_node = top_node->next;
		delete temp;
	}

	// Проверка на пустоту
	bool isEmpty(Stack* p_begin) const {
		return top_node == nullptr;
	}

	// Очистка стека
	void clear(Stack* p_begin) {
		while (!isEmpty(p_begin)) {
			pop(p_begin);
		}
	}

	// Деструктор
	~Stack() {
		clear(nullptr);
	}
};
struct Calculator
{
	Stack stack;// обьект струкрутра стека
	const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
	const set<string> one_operations = { "-"}; // операции доступные сейчас 
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
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			double b = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(b + a));
		}
		else  if (operation == "-" && one_opertion == false) {
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
			stack.push(p_begin, to_string(pow(b, a)));
		}
		else  if (operation == "-" && one_opertion) {
			stack.pop(p_begin);
			double a = stoi(stack.top(p_begin));
			stack.pop(p_begin);
			stack.push(p_begin, to_string(a * -1));
		}

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
		Stack* p_top = stack.create();
		pair<string, int>digit;
		pair<string, int>text;
		string y;
		int size = expression.size();
		for (int i = 0; i < size;)
		{
			//cout << i << endl;
			//cout <<"Did" <<bool(isdigit(expression[i])) << endl;
			if (isdigit(expression[i])) {
				digit = get_digit(expression, i);
				if (output == "") {
					output = digit.first;
				}
				else {
					output = output + " " + digit.first;
				}
				
				i = i + digit.second;
				if (i >= size) {
					break;
				}
			}
			else {

				text = get_text(expression, i);
				string x = text.first;
				//cout << x << endl;
				//cout << get_priority(x) << endl;
				if ((stack.isEmpty(p_top) || (text.first == "(") || get_priority(x) > get_priority(stack.top(p_top)))) {
					stack.push(p_top, x);
				}
				 else if (get_priority(x) <= get_priority(stack.top(p_top))) {
					while (get_priority(x) <= get_priority(stack.top(p_top))) {
						y = stack.top(p_top);
						if (output == "") {
							output = y;
						}
						else {
							output = output + " " + y;
						}
						stack.pop(p_top);

					}
					stack.push(p_top, x);
				}
				 else if (text.first == ")"){
					while ( "(" == stack.top(p_top) || stack.isEmpty(p_top)) {
						y = stack.top(p_top);
						if (output == "") {
							output = y;
						}
						else {
							output = output + " " + y;
						}
						stack.pop(p_top);

					}
					stack.pop(p_top);

				}
				 else {
					cout << "ddf" << endl;
				}
				i = i + text.second;
				//i = i + text.second;
			}
			//text.second = 0;
			//digit.second = 0;
			

			
		}
		//cout << stack.isEmpty(p_top) << endl;
		while (!stack.isEmpty(p_top)) {
			y = stack.top(p_top);
			output = output + " " + y;
			stack.pop(p_top);
		}
			
			
			
		
		return output;
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
				if (stack.isEmpty(p_top)) {
					string opernd = word;// записываем унарную операцию
					ex_ss >> word;
					stack.push(p_top, word);
					stack.push(p_top,word);
					operationsa_procces(p_top, opernd,true);
				}
				else {
					operationsa_procces(p_top, word);
				}
				
				
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
	// cout << cal.stack_machine("- 3 6 -") << endl;;
	 //string x = cal.get_digit("12244+").first;
	 cout << cal.sort_station("1+2+3") << endl;
	// cout << x << endl;
	// cout << "NEW" << endl;
	 //string y = cal.get_text("122+3", cal.get_digit("122+++4").second).first;
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
