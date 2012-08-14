#include <iostream>
#include <cctype>
#include <map>

enum Token {
	NAME, END, NUMBER,
	MINUS = '-', PLUS = '+', MUL = '*',
	DIV = '/', PRINT = ';', ASSIGN = '=',
	LP = '(', RP = ')'
};

Token curToken = PRINT;
std::string curName;
double curNumber;
std::map< std::string, double > names;

double term(bool);
double primary(bool);
void getToken();

double expr(bool get) {
	double lval = term(get);	
	while(true) {
		switch(curToken) {
		case PLUS: 
			lval+=term(true);
			break;
		case MINUS: 
			lval-=term(true);
			break;
		default: 
			return lval;
		}
	}
}

double term(bool get) {
	double lval = primary(get);
	while(true) {
		switch (curToken) {
		case MUL: 
			lval*=primary(true);
			break;
		case DIV: 
			lval/=primary(true);
			break;
		default: 
			return lval;
		}
	}	
}

double primary(bool get) {
	double r;
	if(get) getToken();
	switch (curToken) {
	case NUMBER: getToken(); return curNumber;
	case NAME: 
		getToken();
		if (curToken == ASSIGN) return names[curName]=expr(true);
		else {
			if (names.find(curName) != names.end()) {
				return names[curName]; 
			}
			else {
				std::cout<<"Name is not defined\n"; 
				return 0; //FIXME An exeption should be thrown here.
			}
		}
	case MINUS: getToken(); return -primary(false);
	case LP: 
		r = expr(true);
		if (curToken != RP) std::cout<<"No right parenthe.\n";	
		getToken();
		return r;
	default: 
		std::cout<<curToken<<std::endl;
		std::cout<<"Received wrong token in primary\n";
	}
}

void getToken() {
	char ch;
	do std::cin.get(ch); while(ch != '\n' && isspace(ch));
	switch (ch) {
	case '-': curToken = MINUS; break;
	case '+': curToken = PLUS; break;
	case '*': curToken = MUL; break;
	case '/': curToken = DIV; break;
	case ';': curToken = PRINT; break;
	case '(': curToken = LP; break; 
	case ')': curToken = RP; break;
	case '=': curToken = ASSIGN; break;
	case 0 : curToken = END; break;
	case '\n': curToken = PRINT; break;
	default :
		if (isalpha(ch)) {
			std::string var;
			var.push_back(ch);
			while(isalnum(ch)) {
				var.push_back(ch); 
				std::cin.get(ch);
			}
			std::cin.putback(ch);
			curName = var;
			curToken = NAME;	
		} 
		else if (isdigit(ch) || ch == '.') {
			std::cin.putback(ch);
			std::cin>>curNumber;
			curToken = NUMBER;
		}
		else {
			std::cout<<"Wrong symbol in input\n";
		}
	}
}

int main() {
	while (std::cin) {
		getToken();
		if (curToken == PRINT) continue;
		if (curToken == END) break;
		std::cout<<expr(false)<<std::endl;	
	}
	return 0;
}
