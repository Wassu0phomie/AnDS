#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

template <typename T>
T readValue() {
	T value = 0;
	while (true) {
		cin >> value;
		if (cin.fail()) {
			cout << "Incorrect input. Enter new value: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
	}
}












//**********************STACK STRUCTYRE**********************
struct _Stack {
	string value;
	struct _Stack* next = nullptr;
};

//**********************Контейнер приорететов**********************
map <string, double> weights = {
	{"+", 1},
	{"-", 1},
	{"*", 2},
	{"/", 2},
	{"^", 3},
	{"(", 0},
	{")", 0},
	{"sin", 4},
	{"cos", 4}
};

//**********************Контейнер переменных**********************
map<string, int> variables = {};


//**********************GET SIZE**********************
int stackSize(_Stack* head) {
	int count = 0;
	while (head) {
		count++;
		head = head->next;
	}
	return count;
}

//**********************ADDING A NEW ELEMENT TO AN EMPTY STACK**********************
void stackPush(_Stack*& head, string data) {
	_Stack* first = new _Stack;
	first->value = data;
	first->next = head;
	head = first;
}


//**********************READING AN ELEMENT FROM THE TOP OF THE STACK**********************
string stackPop(_Stack*& head) {
	_Stack* prev = nullptr;
	if (head == nullptr)
		return 0;
	prev = head;
	string val = head->value;
	head = head->next;
	delete prev;
	return val;
}

//**********************GETTING A REFERENCE TO THE TOP ELEMENT OF THE STACK**********************
_Stack* pop(_Stack* str) {
	_Stack* prev = str->next;
	delete str;
	str = prev;
	return str;
}
//**********************GETTING A REFERENCE TO THE LAST ELEMENT OF THE STACK**********************
_Stack* stackLast(_Stack* head) {
	if (head == nullptr)
		return nullptr;
	while (head->next)
		head = head->next;
	return head;
}

//**********************FREE MEMORY**********************
void stackClear(_Stack* head) {
	_Stack* prev = nullptr;
	while (head->next) {
		prev = head;
		head = head->next;
		delete prev;
	}
	delete head;
}

//**********************GETTING A REFERENCE TO THE LAST ELEMENT OF THE STACK(operation > 2)**********************
_Stack* stackGetLastButOne(_Stack* head) {
	if (head == nullptr || head->next == nullptr)
		return nullptr;
	while (head->next->next)
		head = head->next;
	return head;
}
//**********************PRINT STACK**********************
void stackPrint(_Stack* head) {
	while (head) {
		cout << head->value << " ";
		head = head->next;
	}
}
//**********************CHECK STACK (if emty return 0)**********************
bool empty(_Stack* str) {
	if (!str) return 1;
	else return 0;
}


//**********************ADDING A NEW ELEMENT TO THE TOP OF THE STACK**********************
void stackPushBack(_Stack* head, string data) {
	_Stack* last = stackLast(head);
	_Stack* next = new _Stack;
	next->value = data;
	next->next = nullptr;
	last->next = next;
}


//**********************READING AN ELEMENT FROM THE TOP OF THE STACK(operation > 2)**********************
string stackPopBack(_Stack* head) {
	string value;
	_Stack* lastbn = nullptr;
	if (!head)
		return 0;

	lastbn = stackGetLastButOne(head);
	value = lastbn->next->value;

	if (lastbn == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		delete lastbn->next;
		lastbn->next = nullptr;
	}
	return value;
}

//**********************STACK INITIALIZATION:**********************
void stackAdd(_Stack*& head, const string& data) {
	if (!head)
		stackPush(head, data);
	else
		stackPushBack(head, data);
}

//**********************CHECK WEIGHT**********************
string stackTake(_Stack*& head) {
	if (stackSize(head) > 1)
		return stackPopBack(head);
	else
		return stackPop(head);
}

//**********************CHECK TOKEN (operation)**********************
bool isOperation(const string& str) {
	auto res = weights.find(str);
	return res != weights.end();
}

//**********************CHECK TOKEN (literal)**********************
bool isLiteral(const string& str) {
	auto res = variables.find(str);
	return res != variables.end();
}

//**********************CHECK TOKEN (number)**********************
bool isNumber(const string& str) {
	string::const_iterator it = str.begin();
	while (it != str.end() && isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

//**********************GET TOKENS**********************
vector<string> tokenize(const string& text) {
	vector<string> tokens{};
	istringstream input(text);

	for (string token; getline(input, token, ' ');)
		tokens.push_back(token);
	return tokens;
}

//**********************CHECK WEIGHT**********************
bool MoveOperation(string token, _Stack* opstack) {
	_Stack* last = stackLast(opstack);
	return weights.find(last->value)->second >= weights.find(token)->second;
}

//**********************CHECK PRIORITY**********************
int _switch(const std::string& p) {
	if (p == "(" || p == ")") return 0;
	if (p == "+" || p == "-") return 1;
	if (p == "*" || p == "/") return 2;
	if (p == "^") return 3;
	if (p == "sin" || p == "cos") return 4;
	return -1;
}
//**********************CHECK Sin or Cos**********************
bool isSinOrCos(const std::string& str, int pos) {
	if (pos + 3 <= str.length() && str.substr(pos, 3) == "sin") {
		return true;
	}
	if (pos + 3 <= str.length() && str.substr(pos, 3) == "cos") {
		return true;
	}
	return false;
}


bool isOperator(const std::string& c) {
	return _switch(c) >= 0;
}
//**********************CORRECTION OF A MATHEMATICAL EXPRESSION**********************
bool correct(std::string& str) {
	_Stack* tok = nullptr;
	int k = 0;

	for (int i = 1; i < str.length() - 1; i++) {
		if (str[i] == ' ' && _switch(str.substr(i - 1, 1)) == -1 && _switch(str.substr(i + 1, 1)) == -1)
			return false;
	}

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			std::string s1(1, str[i]);
			stackAdd(tok, s1);
		}
		if (str[i] == ')') {
			if (!empty(tok)) {
				tok = pop(tok);
			}
			else return false;
		}
	}

	for (int i = 1; i < str.length(); i++) {
		if (isSinOrCos(str, i)) {
			if (i > 0 && !isOperator(str.substr(i - 1, 1)) && str[i - 1] != ' ') {
				return false;
			}
			i += 2; // Пропустить "sin" или "cos"
			k++; // Увеличить счетчик для проверки парности скобок внутри sin или cos
		}
	}

	for (int i = 1; i < str.length(); i++) {
		if (_switch(str.substr(i - 1, 1)) > 0 && _switch(str.substr(i, 1)) > 0 && str[i] != '-')
			return false;
	}
	for (int i = 0, k = 0; i < str.length(); i++) {
		if (_switch(str.substr(i, 1)) > 0) k++;
		if (i == 1 && str[i - 1] != '-' && _switch(str.substr(i - 1, 1)) > 0)
			return false;
		else if (i == str.length() - 1 && _switch(str.substr(i, 1)) > 0 || i == str.length() - 1 && !k)
			return false;
	}

	return true;
}


//**********************RPN**********************
string reversePolishNotation(string& inpt_str, ofstream& ofs, bool silent = false) {
	variables.clear();
	string current_str;
	vector<string> str_tokens = tokenize(inpt_str);
	_Stack* outStack = nullptr;
	_Stack* opStack = nullptr;

	for (const auto& token : str_tokens) {

		if (isNumber(token)) {
			stackAdd(outStack, token);
		}

		else if (isOperation(token)) {
			if (!opStack)
				stackPush(opStack, token);
			else if (token == "(")
				stackAdd(opStack, token);
			else if (token == ")") {
				while (opStack && current_str != "(") {
					if (stackSize(opStack) >= 2)
					{
						current_str = stackPopBack(opStack);
					}
					else {
						current_str = stackPop(opStack);
					}
					stackAdd(outStack, current_str);
					_Stack* last = stackLast(opStack);
					if (!last)
						throw "Обнаружена непарная скобка";
					current_str = last->value;
				}
				if (!opStack)
					throw "Обнаружена непарная скобка";
				current_str.clear();
				if (stackSize(opStack) >= 2)
				{
					current_str = stackPopBack(opStack);
				}
				else {
					current_str = stackPop(opStack);
				}
			}

			else if (MoveOperation(token, opStack)) {
				if (stackSize(opStack) >= 2)
				{
					stackPushBack(outStack, stackPopBack(opStack));
				}
				else {
					stackPushBack(outStack, stackPop(opStack));
				}
				stackAdd(opStack, token);
			}
			else
				stackPushBack(opStack, token);
		}
		else {
			if (silent) {
				stackAdd(outStack, "1");
			}
			else {
				auto found = variables.find(token);
				if (found == variables.end()) {
					cout << "Введите значение для " + token + ": ";
					int var = readValue<double>();
					variables[token] = var;
					stackAdd(outStack, to_string(var));
				}
				else {
					stackAdd(outStack, to_string(found->second));
				}
			}
		}
		if (!silent) {
			cout << "----------------------------- " << "Token: " + token << " -----------------------------" << "\nвыходная строка: ";
			stackPrint(outStack);
			cout << "\nСтэк : ";
			stackPrint(opStack);
			cout << endl << endl;
		}
	}

	if (!silent)
		cout << "Перемещение операций в основной стэк...\n";
	while (opStack)
		if (stackSize(opStack) >= 2)
		{
			stackPushBack(outStack, stackPopBack(opStack));
		}
		else {
			stackPushBack(outStack, stackPop(opStack));
		}

	if (!silent) {
		cout << "\nОбратная польская нотация:\t";
		stackPrint(outStack);
		cout << "\n\n\n";
	}
	string outp;
	while (outStack) {
		outp += outStack->value + ' ';
		outStack = outStack->next;
	}
	outp.pop_back();
	return outp;
}


//**********************CALCULATOR**********************
double calculatorRpn(string& rpn, ofstream& ofs) {
	istringstream reader(rpn);
	_Stack* outStack = nullptr;
	string token;
	while (!reader.eof()) {
		reader >> token;
		if (isNumber(token)) {
			cout << "Переносим в стэк " << token << endl;
			stackAdd(outStack, token);
		}
		else {
			double a, b;
			double b_in_degrees, b_in_radians;
			if (!(token == "sin" || token == "cos")) { // If the operator is not unary(it's binary)
				if (stackSize(outStack) < 2)
					throw "Неверный порядок!";
				b = stod(stackTake(outStack));
				a = stod(stackTake(outStack));
			}
			if (token == "+") {
				cout << "Забираем числа " << a << " и " << b << " из стека. Складываем. Результат переносим в стек.\n";
				cout << to_string(a) << " + " << to_string(b) << " = " << to_string(a + b) << '\n';
				stackAdd(outStack, to_string(a + b));
			}
			else if (token == "-") {
				cout << "Забираем числа " << a << " и " << b << " из стека. Вычитаем. Результат переносим в стек.\n";
				cout << to_string(a) << " - " << to_string(b) << " = " << to_string(a - b) << '\n';
				stackAdd(outStack, to_string(a - b));
			}
			else if (token == "*") {
				cout << "Забираем числа " << a << " и " << b << " из стека. Умножаем. Результат переносим в стек.\n";
				cout << to_string(a) << " * " << to_string(b) << " = " << to_string(a * b) << '\n';
				stackAdd(outStack, to_string(a * b));
			}
			else if (token == "/") {
				if (b == 0)
					throw "Ошибка: деление на ноль!";
				cout << "Забираем числа " << a << " и " << b << " из стека. Делим. Результат переносим в стек.\n";
				cout << to_string(a) << " / " << to_string(b) << " = " << to_string(a / b) << '\n';
				stackAdd(outStack, to_string(a / b));
			}
			else if (token == "sin") {
				b_in_degrees = stod(stackTake(outStack));
				b_in_radians = b_in_degrees * std::acos(-1) / 180.0;
				cout << "Берем число " << b_in_degrees << " из стека, преобразуем в радианы и вычисляем sin. Результат переносим в стек.\n";
				stackAdd(outStack, to_string(sin(b_in_radians)));
			}
			else if (token == "cos") {
				b_in_degrees = stod(stackTake(outStack));
				b_in_radians = b_in_degrees * std::acos(-1) / 180.0;
				cout << "Берем число " << b_in_degrees << " из стека, преобразуем в радианы и вычисляем cos. Результат переносим в стек.\n";
				stackAdd(outStack, to_string(cos(b_in_radians)));
			}
			else if (token == "^") {
				cout << "Забираем числа " << a << " и " << b << " из стека. Возводим в степень. Результат переносим в стек.\n";
				cout << to_string(a) << " ^ " << to_string(b) << " = " << to_string(pow(a, b)) << '\n';
				stackAdd(outStack, to_string(pow(a, b)));
			}
			else {
				string errt = "Неизвестный оператор " + token;
				throw errt.c_str();
			}
		}
	}
	if (stackSize(outStack) != 1)
		throw "Invalid stack size";
	return stod(stackPop(outStack));
}






int mainRPN() {



	setlocale(LC_ALL, "rus");
	ofstream ofs("out.txt");
	while (true) {
		system("cls");
		cout <<
			"Choose the command:\n"
			"(1) - Convert expression into reverse polish notation\n"
			"(2) - Validate and compute mathematical expression\n"
			"(3) - Validate and compute reverse polish notation expression\n"
			"(0) - Exit\n\n";
		cout << "Action >> ";
		int choice = readValue<int>();
		cout << endl;
		switch (choice) {
		case 0:
			return 0;
		case 1: {
			system("cls");

			std::string expression;
			std::cout << "Введите математическое выражение: ";
			std::getline(std::cin, expression);

			cout << endl << "Перевод в обратную польскую нотацию...\n\n";
			reversePolishNotation(expression, ofs);

			break;
		}
		case 2: {
			system("cls");
			string inp;
			cout << "Введите математическое выражение: ";
			getline(cin, inp);
			if (!correct(inp)) {
				cout << "Expression is invalid!\n";
			}
			else {
				cout << "Expression is valid.\n";
			}
			break;
		}
		case 3: {
			system("cls");
			string inp;
			cout << "Enter reverse polish notation expression: ";
			getline(cin, inp);
			try {
				cout << "\nОтвет: " << calculatorRpn(inp, ofs) << endl << endl;
				cout << "Expression is valid.\n";
			}
			catch (const char* data) {
				cout << "\nERROR\n" << "Expression is invalid! " << data << endl;
			}
			break;
		}

		default:
			cout << "\nCategory with number " << choice << " does not exist." << endl;
			break;
		}
		system("pause");
	}
	return 0;
}