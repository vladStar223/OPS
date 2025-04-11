#include <iostream>
#include<sstream>
#include<string>
#include <set>
#include<cmath>
using namespace std;

//Узел дерева
struct NodeTree
{
	string data = "";
	NodeTree* right = nullptr;
	NodeTree* left = nullptr;
	NodeTree* prev = nullptr;
	/*
	NodeTree(string data = "", NodeTree* right = nullptr, NodeTree* left = nullptr, NodeTree* prev = nullptr)
	{
		data = data;
		left = left;
		right = right;
		prev = right;

	}
	*/
}; // узел дерево 
//Ячейка стека
struct Node {
	Node* next = nullptr;
	string data;
};
//Структра Стек
struct Stack {
private:

	Node* node = nullptr;
	int size = 0;// размер стека
public:
	static Stack* create() {
		return new Stack();
	}
	// добавление
	//Принимает ссылку на указатель  головы стека и строку добавления
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
	// показывает вверх стека
	string top(Stack* p_top) {
		if (p_top == nullptr) {
			throw "Error";
		}
		return p_top->node->data;
	}
	// удаляет элемент из стека
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
	// проверяет  пустой ли стек
	bool isEmpty(Stack*& p_top) {
		return (p_top->node == nullptr);
	}
	//получает размер стека
	int get_size(Stack*& p_top) {
		return p_top->size;
	}
};
Stack stack1;// струкрутра стека
const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
const set<string> one_operations = { "sin","cos","tg","sqrt","~"}; // операции доступные сейчас
// получает приоритет операции x
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
	else if (x == "~") {
		return 10;
	}
	else if (x == "sin" || x == "cos" || x == "tg" || x == "sqrt") {
		return 5;
	}
}
// считает
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
		else  if (operation == "~" && one_opertion) {
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
//Стековая машина
double stack_machine(string expression) {
	string word;
	Stack* p_top = stack1.create();
	stringstream ex_ss(expression);
	double ot = 0;// значение по умолчанию
	bool prev = false;
	while (ex_ss >> word) {
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
//Обработка чисел
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
//обработка символов
pair<string, int> get_text(string xv, int j = 0) {
	string xi;
	pair<string, int> text;
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
//Замена унарного минуса на тильду
string toNormalExpression(string expression) {
	string normal_expression;
	int size = expression.size();
	for (int i = 0; i < size; i++) {
		if (expression[i] == '(' && i + 1 < size && expression[i + 1] == '-') {
			normal_expression += "(~";
			i=i+1; 
		}
		else if (expression[i] == '-' && i + 1 < size &&  isalpha(expression[i + 1])) {
			normal_expression += "~1*";
		}
		else if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(')) {
			normal_expression += '~';
		}
		else {
			normal_expression += expression[i];
		}
	}

	return normal_expression;
}
//Получение постфиксной формы
string postfix_print(NodeTree* node, string ex = "") {
	if (node != nullptr) {
		ex = postfix_print(node->left, ex);
		ex = postfix_print(node->right, ex);
		ex += node->data + " ";
	}
	return ex;
}
string postfix_print(NodeTree* node, string ex = "") {
	if (node != nullptr) {
		ex = postfix_print(node->left, ex);
		ex = postfix_print(node->right, ex);
		ex += node->data + " ";
	}
	return ex;
}
string postfix_print(NodeTree* node, string ex = "") {
	if (node != nullptr) {
		ex = postfix_print(node->left, ex);
		ex = postfix_print(node->right, ex);
		ex += node->data + " ";
	}
	return ex;
}
//Сортировочная стация через дерево
NodeTree* sort_tree_station(string expression) {
	NodeTree* root = new NodeTree();
	int size = expression.size();
	pair<string, int> digit;
	pair<string, int> text;
	string ops = "";
	NodeTree* p = root;
	for (int i = 0; i < size;)
	{
		if (!isdigit(expression[i])) {
			text = get_text(expression, i);
			string token = text.first;
			if (token == "(") {
				p->left = new NodeTree();
				p->left->prev = p;
				p = p->left;
			}
			else if (token == ")") {

				if (p->prev != nullptr) {
					p = p->prev;
				}


			}
			else {
				p->data = token;
				p->right = new NodeTree();
				p->right->prev = p;
				p = p->right;

			}
			i = i + text.second;
		}
		else {
			digit = get_digit(expression, i);
			p->data = digit.first;
			//cout << p->data << endl;

			if (p->prev != nullptr) {
				p = p->prev;
			}

			i = i + digit.second;

		}
	}
	return root;
}
//Добавление скобочек
string add_m(string x) {
	string ot = "(";
	bool oper = false;
	for (int i = 0; i < x.size(); i++) {
		if (isdigit(x[i])) {
			if (oper == false) {
				ot = ot + "(" + x[i];
			}
			else {
				ot = ot + x[i] + ")";
				oper = false;
			}
		}
		else {
			ot = ot + x[i];
			oper = true;
		}
	}
	return ot;
}
//Проверка выражения для сортировочной стации через дерево
void check_expression(string expression) {
	int parentheses_count = 0;
	int size = expression.size();
	string xi = "";
	pair<string, int> digit;
	pair<string, int> text;
	bool prev_oper = false;
	bool prev_di = false;

	for (int i = 0; i < size;) {
		xi = expression[i];
		if (!isdigit(expression[i]) ){
			text = get_text(expression, i);
			string x = text.first;
			i += text.second;

			if (x == "(") {
				if (prev_di) {
					throw runtime_error("Missing operator before '('");
				}
				prev_di = false;
				prev_oper = false;
			}
			else if (x == ")") {
				if (parentheses_count < 0) {
					throw runtime_error("Mismatched parentheses");
				}
				if (prev_oper) {
					throw runtime_error("Operator before ')'");
				}
				prev_di = true;
				prev_oper = false;
			}
			else if (one_operations.count(x) || operations.count(x)) {
				if ((prev_oper  || !prev_di) && x!="-") {
					throw runtime_error("Duplicate operators");
				}
				if (x != "-") {
					prev_oper = true;
					prev_di = false;
				}
				
			}
			else {
				throw runtime_error("Invalid token: " + x);
			}
		}
		else {
			digit = get_digit(expression, i);
			i += digit.second;
			prev_oper = false;
			prev_di = true;
		}
	}

	if (parentheses_count != 0) {
		throw runtime_error("Mismatched parentheses");
	}
}
int main()
{
	cout << "Hello user" << endl;
	bool k = false; // Для цикла
	bool test = false; //Для перевода в режим с откладко
	//Выражение ввода
	string expression;
	//Нормальное выражение ввода
	string expression_n;
	//Результат сортировочной стации
	string sort_station1;
	string x = "1"; //Выбор режима какулятора 
	//Специальные штука
	string test_s;
	cout << "Input version" << endl;
	cout << "1 is normal version" << endl;
	cout << "0 is test version" << endl;
	getline(cin, test_s);
	if (test_s == "0") {
		test = true;
	}
	do
	{
		try
		{
			cout << "Input fun" << endl;
			
			cout << "2 is input expression with Tree sort station" << endl;
			cout << "3 is exit" << endl;
			getline(cin, x);
			 if (stoi(x) == 2) {
				cout << "Do you need add brackets?" << endl;
				cout << "Input  1 is Yes" << endl;
				cout << "Input  0 is No" << endl;
				string y; // Выбор режима работы
				getline(cin, y);
				cout << "Input" << endl;
				getline(cin, expression);
				if (y == "1") {
					expression_n = add_m(expression);
				}
				else {
					expression_n = expression;
				}
				try
				{
					
					check_expression(expression_n);
					expression_n = toNormalExpression(expression_n);
					NodeTree* root = nullptr;
					root = sort_tree_station(expression_n);
					sort_station1 = postfix_print(root, "");
					if (test) {
						cout << "add_m " << expression_n << endl;
						cout << "NormalExpression " << expression_n << endl;
						cout << "Postfix " << sort_station1 << endl;
					}
					cout << expression << " = " << stack_machine(sort_station1) << endl;;
					
				}
				catch (runtime_error exception)
				{
					cout << exception.what() << endl;
					
				}
				catch (const std::exception&)
				{
					cout << "Unhandle error" << endl;
					
				}
			
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