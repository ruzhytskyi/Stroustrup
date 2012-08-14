#include <iostream>
#include <cctype>
#include <map>

int main() {
	char ch;
	typedef std::multimap< std::string, double > NameValTbl;	
	NameValTbl table;
	while (true) {
		std::string name;
		double value;
		std::cin.get(ch);
		if (ch == '0') break;
		while (ch != '\n') {
			while (isspace(ch) && ch != '\n') std::cin.get(ch);
			if (isalpha(ch)) {
				std::cin.putback(ch);
				std::cin>>name;
			}
			else if (ch == '\n') break;
			else {
				std::cout<<"Wrong name beginning.\n";
				break;
			}
			do std::cin.get(ch); while (isspace(ch) && ch != '\n');
			if (isdigit(ch)) {
				std::cin.putback(ch);
				std::cin>>value;
			}
			else if (ch == '\n') break;
			else {
				std::cout<<"Wrong value.\n";
				break;
			}
			table.insert(std::make_pair(name, value));
			std::cin.get(ch);
		}
	}
	std::map< std::string, double > sum;
	std::map< std::string, int > count;
	typedef std::map< std::string, double > SumType;

	for(NameValTbl::iterator i = table.begin(); i!=table.end(); i++) {
		sum[i->first]+=i->second;
		count[i->first]+=1;
	}	

	for(NameValTbl::iterator i = table.begin(); i!=table.end(); i++) {
		std::cout<<"Name: "<<i->first<<", value: "<<i->second<<"\n";
	}	
	for(SumType::iterator i = sum.begin(); i!=sum.end(); i++) {
		std::cout<<"Name: "<<i->first<<", Sum: "
			 <<i->second<<", Mean: "<<i->second/count[i->first]<<std::endl;
	}
}	
