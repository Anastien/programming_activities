// a wip calcultor
#include <iostream>
#include<cmath>
using namespace std;
double expression();
double term();
double primary();
int main()
{
	cout << "IN: ";
	while (cin)
	{
		cout << "OUT: " << expression() <<"\n";
	}

	return 0;
}
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
	private:
		bool full;
		Token buffer;
};
Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
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
Token_stream ts;
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
            default:
                ts. put_back(t);
                return result;
		}
	}
}
double primary()
{
	Token pri = ts.get();
	switch (pri.kind)
	{	case '(':
			{double result = expression();
			return result;
			break;}
		case '0':
			return pri.value;
			break;
		default:
		    5;
    }		//bad primary.
}
