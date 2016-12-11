// a wip calculator
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

double expression();
double term();
double primary();

// Tokens ystem ......................................................
class Token // type to represent enties as nums, "(" or an operator.
{
	public:
		char kind;
		double value;
};
class Token_stream // a stream that eases reading tokens.
{
	public:
		Token get();
		void put_back(Token t);
		char get_char();
		void get_input();
	private:
		bool full = false;
		Token buffer;
		string input;
		int i = -1;
}
Token_stream ts;
void Token_stream::get_input()
{
	//
	cin >> input;
}
char Token_stream::get_char()
{
	i+=1;
	if(i == input.size()-1 && input[i] == ';')
	{
		return'l';// last element.
	}
	else if (i == input.size()-1)
	{
		// wrong input format!
	}
	return input[i];
}
Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	ch = ts.get_char();
	switch (ch)
	{
		case '*':
        case '+':
        case '/':
        case '-':
        case '(':
        case ')':
			return Token{ch};
		case '.': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			cin.putback(ch);
			double num;
			cin >> num;
			return Token{'0', num}; // numeric token has kind = 0.
		case ';':
			return Token{ch};
		case 'l':
			return Token{ch};
		default:
		    5;
			//illegal char.
	}
}
void Token_stream::put_back(Token t)
{
	full = true;
	buffer = t;
}

//....................................................................
/*grammer system------------------------------------------------------
the calculation is based on 3 functions:
*/
double expression()
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
				return result;
			default:
				ts.put_back(t);
				return result;
		}
	}
}
double term()
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
            	return result;
            default:
                ts.put_back(t);
                return result;
		}
	}
}
double primary()
{
	Token pri = ts.get();
	switch (pri.kind)
	{	case '(':
		{	double result = expression();
			return result;
		}
		case '0':
			return pri.value;
			return expression();
		default:

		    5;
    }		//bad primary.
}
//______________________________________________________________________
int main()
{
	while (true)
	{
		cout << "IN:  ";
		ts.get_input();
		if(ts.get().kind == 'q') break;
		while (true)
		{
			cout << "OUT: " << expression() <<"\n";
			Token t = ts.get();
			if (t.kind == 'l')
            {
                break;
            }
            else ts.put_back(t);
		}
	}
	return 0;
}
