// a wip calculator
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>


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
		Token get();
		void put_back(Token t);
		char get_char(); // fuck you cin :"(
		void get_input();// fuck you cin :"(
		//void chk_input();
		//void correct_ip();
		double compose_num();
	private:
		bool full = false;
		Token buffer;
		string input;
		int i;// a var indicating next char of input.
};
Token_stream ts;
void Token_stream::get_input()//works ok.
{
	cout << "5";
	cin >> input;
	i = 0;
	cout << input;
}
/*void Token_stream::chk_input()
{

}*/
double Token_stream::compose_num() // has problems.
{
	double n = 0;
	//vector<char> n_v;
	string numstr = "";
	while ( (input[i] == '.') || (input[i] == '0')|| (input[i] =='1')||
		(input[i] == '2') || (input[i] == '3') || (input[i] == '4') ||
		(input[i] == '5') || (input[i] =='6') || (input[i] =='7') ||
		(input[i] =='8' )|| (input[i] =='9') )
	{
		//n_v.push_back(input[i]);
		numstr += ts.get_char();
	}
	/*for (int i = n_v.size() - 1; i >= 0; --i)
	{
		n += int(n_v[i]) * pow(10, i);
	}*/
	//istringstream convert(numstr);
	//convert >> n; // might fail
	cout << '1';
	n =  strtod(numstr.c_str(),NULL);
	return n;

}
char Token_stream::get_char() // ignores ' '.
{
	int a = i;
	if((i == input.size() - 1 ) && (input[i] == ';'))
	{
		return 'l';// last element.
	}
	/*else if ( i == input.size() - 1 )
	{
		// wrong input format!
	}*/
	while ( input[i] == ' ')
	{
		++i;
	}
	++i;
	return input[a];


}
Token Token_stream::get()
{
	if ( full )
	{
		full = false;
		return buffer;
	}
	char ch;
	ch = ts.get_char();
	switch ( ch )
	{
		case '*':
		case '+':
		case '/':
		case '-':
        case '(':
        case ')':
        case ';':
        case 'l':
        case 'q':
			return Token{ch};
		case '.': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
			{
				--i;
				double num = ts.compose_num();
				return Token{'0', num}; // numeric token has kind = 0.
			}
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
//______________________________________________________________________
int main()
{
	while (true)
	{
		cout << "IN:  ";
		ts.get_input();
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
