// OPS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<string>
#include <set>
using namespace std;
int size_s = 0;
struct Node
{
	Node* next = nullptr;
	string data = "2";
	int size = 0;

};
void push(Node*& p_top, string x) {
	Node* n = new Node;
	n->data = x;
	n->next = nullptr;
	if (p_top == nullptr) {
		p_top = new Node;
		p_top->next = n;
	}
	else {
		n->next = p_top->next;
		p_top->next = n;
	}
	p_top->size = p_top->size + 1;

}
string top(Node* p_top) {
	if (p_top == nullptr) {
		throw "Error";
	}
	return p_top->next->data;
}
void pop(Node*& p_top) {
	if (p_top == nullptr) {
		throw "Error";
	}
	else {
		Node* t = p_top->next;
		p_top->next = p_top->next->next;
		delete t;
	}
}
bool isEmpty(Node* p_top) {
	return (p_top->next == nullptr);
}
 int get_size(Node*  p_top) {
	 return p_top->size;
}


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
void operationsa_procces(Node* p_begin, string operation, bool one_opertion = false) {
	if ((one_opertion == false && (get_size(p_begin) <= 1))) {
		throw runtime_error("Error");
	}
	else {
		if ((operation == "+" || operation == "/" || operation == "*" || operation == "^") && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(a));
		}
		else if (operation == "+") {
			double a = stof(top(p_begin));
			pop(p_begin);
			double b = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(b + a));
		}
		else  if (operation == "-" && one_opertion == false) {
			double a = stof(top(p_begin));
			pop(p_begin);
			double b = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(b - a));
		}
		else  if (operation == "*") {
			double a = stof(top(p_begin));
			pop(p_begin);
			double b = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(b * a));
		}
		else  if (operation == "/") {
			double a = stof(top(p_begin));
			pop(p_begin);
			double b = stof(top(p_begin));
			pop(p_begin);
			if (a == 0) {
				throw runtime_error("delenie na 0");
			}
			else {
				push(p_begin, to_string(b / a));
			}

		}
		else  if (operation == "^") {
			double a = stof(top(p_begin));
			pop(p_begin);
			double b = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(pow(b, a)));
		}
		else  if (operation == "-" && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(a * -1));
		}
		else  if (operation == "sin" && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(sin(a)));
		}
		else  if (operation == "cos" && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(cos(a)));
		}
		else  if (operation == "tg" && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(tan(a)));
		}
		else  if (operation == "sqrt" && one_opertion) {
			double a = stof(top(p_begin));
			pop(p_begin);
			push(p_begin, to_string(sqrt(a)));
		}
	}


}
double stack_machine(string expression) {
	string word;
	Node* p_top=new Node;
	stringstream ex_ss(expression);
	double ot = 0;// значение по умолчанию
	while (ex_ss >> word) {
		//cout << word << endl;
		if (operations.count(word) == 0 && one_operations.count(word) == 0) {
			push(p_top, word);
		}
		else {
			if (get_size(p_top) <= 0 || one_operations.count(word) == 1) {
				if (get_size(p_top) == 0) {
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
	ot = stof(top(p_top));
	//для большей точности используй 
	//long double num_ld = std::stold("123.456");
	pop(p_top);
	return ot;
}
int main()
{
	cout << "Hello user" << endl;
	string data;
	string da;
	 bool k = false;
	 //cout << "sdsd" << endl;
	 string expression;
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
				 cout << stack_machine(expression) << endl;;
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
