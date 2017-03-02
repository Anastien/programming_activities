// a wip calculator
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <exception>

using namespace std;

double expression();
double term();
double primary();

// Token system ......................................................
class Token // type to represent enties as nums, "(" or an operator.
{
	public:
		//Token();
		char kind; // for operators it is the operator itself,for numbers it is '0'.
		double value;
};
class Token_stream
{
	public:
		Token_stream(string);//constructor.
		Token_stream();
		Token get();
		void put_back(Token t);
	private:
		bool full = false;
		Token buffer;
		int i;// a var indicating next char of input.
		stringstream instr{};
};
class Wrong_format : public exception
{
	public:
		Wrong_format(const string &errMessage) : errMessage_(errMessage){};
		// overriden what() method from exception class
	  	virtual const char* what() const throw() { return errMessage_.c_str(); }
	private:
	  	string errMessage_;
};
Token_stream::Token_stream(string input)
{
    instr.str(input);
    cout << instr.str();
}
Token_stream::Token_stream()
{

}
Token Token_stream::get() // only produces legal tokens.
{
	if ( full )
	{
		full = false;
		return buffer;
	}
	double num;
	char ch;
	instr >> ch;
	/*if(! instr )
	{
		throw Wrong_format{"Wront format! got no input. \ntype f for format.\n"};

	}*/
	switch ( ch )
	{
		case '*': case '+': case '/': case '-':
        case '(': case ')': case ';': case 'l':
        case 'q':
			return Token{ch};
		case '.': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
			{
				instr.unget();
				/*if(!(instr >> num))//not sure if this can happen!
				{
					throw Wrong_format{"Wront format! excpeted a num. type f for format."};
				}*/
				instr >> num;
				return Token{'0', num}; // numeric token has kind = 0.
			}
		default:
			stringstream sss;
			cout << 5;
			sss << ch;
			cout << sss.str();
            string msg = "Wront format! illegal char. \ntype f for format.\n";
            throw Wrong_format{msg};

	}
}
void Token_stream::put_back(Token t)
{
	full = true;
	buffer = t;
}
string get_input() //input only span single line.
{
	//gets and slightly corrects input formt.
	string input;
	getline(cin, input);
	/*if (input[0] != 'q')
	{
		input.back() = 'l';// convert last; to 'l'

	}*/
	return input;
}
//*___*
Token_stream ts;
int main()
{
	while (true)
	{
		try
		{
			cout << "IN:  ";
			Token_stream ts (get_input());
			Token q_chk = ts.get();
			if(q_chk.kind == 'q')
				break;
			else
				ts.put_back(q_chk);
			while (true)
			{
				cout << "OUT: " << expression() <<"\n";
				Token t = ts.get();
				if (t.kind == 'l')
	            {
	                break;
	            }
			}
		}
		catch(Wrong_format &error)
		{
			cout << error.what();
		}
	}

	return 0;
}
//....................................................................
/*grammer system------------------------------------------------------
the calculation is based on 3 functions:
*/
double expression() // starts by a number and ends with ';'.
{
	double result = term();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
			case '+':
				result += term();
				break;
			case '-':
				result -= term();
				break;
			case ';':
				ts.put_back(t);
				return result;
		}
	}
}
double term() // 2*5*6 in exrepsion( 2*5*6 + 3*4 )is a term.
{
	double result = primary();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		    case '*':
                result*= primary();
                break;
            case '/':
                result /= primary();
                break;
            case ';':
				ts.put_back(t);
				return result;
		}
	}
}
double primary()// 2 in (2*3+5) is a primary, experssions in '(exp)' are also primary
{
	Token pri = ts.get();
	switch (pri.kind)
	{	case '(':
		{	double result = expression();
			return result;
		}
		case '0':
			return pri.value;
    }
}

//______________________________________________________________________
