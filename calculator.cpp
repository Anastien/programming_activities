// a wip calculator
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

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
		Token_stream()//constructor.
		Token get();
		void put_back(Token t);
	private:
		bool full = false;
		Token buffer;
		//string input;
		int i;// a var indicating next char of input.
		stringstream instream;
};

Token Token_stream::get()
{
	if ( full )
	{
		full = false;
		return buffer;
	}
	double num;
	char ch;
	istringstream >> ch;
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
				istringstream.unget();
				istringstream >> num;
				return Token{'0', num}; // numeric token has kind = 0.
			}
		default:
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
			/*default:
				ts.put_back(t);
				return result;*/
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
            /*default:
                ts.put_back(t);
                return result;*/
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
		default:
			5;
		//throw bad input
    }
}
string get_input() //input only span single line.
{
	//gets and slightly corrects input formt.
	getline(cin, string input);
	if (input != 'q')
	{
		input.back() = 'l';// convert last; to 'l'

	}


}
//______________________________________________________________________
int main()
{
	while (true)
	{
		cout << "IN:  ";
		Token_stream ts {input};
		cout << "4";
		Token q_chk = ts.get();
		if(q_chk.kind == 'q')
			break;
		else
			ts.put_back(q_chk);
		cout << '2';
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
	return 0;
}
