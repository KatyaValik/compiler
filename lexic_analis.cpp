#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <exception>

using namespace std;

enum ST
{
	BEGIN, WORD, NUMBER, COMMENT, HEXADECIMAL, DECIMAL, OPERATOR
};

class lexem
{
public:
	string s;
	string type;
	string to_string()
	{
		ostringstream str;
		str << type <<": " << s;
		return str.str();
	}
};

char gc()
{
	char c;
	scanf("%c", &c);
	return c;
}

int main()
{
	ST L = BEGIN;
	char c = gc();
	string s, s1;
	s += c;
	while (c != EOF)
	{
		switch (L)
		{
		case BEGIN:
			if (((c >= 'a') && (c <= 'z')) || (c == '_') || ((c >= 'A') && (c <= 'Z')))
			{
				L = WORD;
				c = gc();
			}
			else if ((c >= '0') && (c <= '9'))
			{
				L = NUMBER;
				c = gc();
			}
			else if (c == '/')
			{
				L = COMMENT;
				c = gc();
				if (c != '*')
				{
					cout << "error";
				}
				c = gc();
				s = '\0';
			}
			else if ((c == '=') || (c == '^') || (c == '|'))
			{
				L = OPERATOR;
				s = c;
				c = gc();

			}

			else if ((c == ' ') || (c == ';') || (c == '\n'))
			{
				c = gc();
				s = c;
			}
			break;

		case WORD:
			if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
			{
				s += c;
				c = gc();
			}
			else if ((c == ' ') || (c == ';') || (c == '\n'))
			{
				if ((s == "if") || (s == "for") || (s == "int") || (s == "while") || (s == "return"))
				{
					cout << "KEYW: " << s << endl;
					c = gc();
					s = c;
					L = BEGIN;
				}
				else
				{
					cout << "ID: " << s << endl;
					c = gc();
					s = c;
					L = BEGIN;
				}
			}
			else if ((c == '=') || (c == '^') || (c == '|'))
			{
				if ((s == "if") || (s == "for") || (s == "int") || (s == "while") || (s == "return"))
				{
					cout << "KEYW: " << s << endl;
					s = c;
					c = gc();
					L = OPERATOR;
				}
				else
				{
					cout << "ID: " << s << endl;
					s = c;
					c = gc();
					L = OPERATOR;
				}
			}
			break;

		case NUMBER:
			if ((s == "0") && ((c == 'x') || (c == 'X')))
			{
				L = HEXADECIMAL;
				c = gc();
				s = '\0';
			}
			else if ((c >= '0') && (c <= '9'))
			{
				L = DECIMAL;
				s += c;
				c = gc();
			}
			else if ((c == '=') || (c == '^') || (c == '|'))
			{
				cout << "DECIMAL: " << s << endl;
				s = c;
				c = gc();
				L = OPERATOR;
			}

			break;

		case DECIMAL:
			if ((c >= '0') && (c <= '9'))
			{
				s += c;
				c = gc();
			}
			else if ((c == ' ') || (c == ';') || (c == '\n'))
			{
				cout << "DECIMAL: " << s << endl;
				c = gc();
				s = c;
				L = BEGIN;
			}
			else if ((c == '=') || (c == '^') || (c == '|'))
			{
				cout << "DECIMAL: " << s << endl;
				s = c;
				c = gc();
				L = OPERATOR;
			}
			break;

		case HEXADECIMAL:
			if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F')) || ((c >= 'a') && (c <= 'f')))
			{
				s += c;
				c = gc();
			}
			else if ((c == ' ') || (c == ';') || (c == '\n'))
			{
				cout << "HEXADECIMAL: " << s << endl;
				c = gc();
				s = c;
				L = BEGIN;
			}
			else if ((c == '=') || (c == '^') || (c == '|'))
			{
				cout << "HEXADECIMAL: " << s << endl;
				s = c;
				c = gc();
				L = OPERATOR;
			}
			break;

		case OPERATOR:
			s1 = s + c;
			if ((s1 == "==") || (s1 == "|=") || (s1 == "||") || (s1 == "^="))
			{
				cout << "OPERATOR" << s1 << endl;
				;
				L = BEGIN;
				c = gc();
				s = c;
			}
			else
			{
				cout << "OPERATOR" << s << endl;
				s = c;
				L = BEGIN;
			}
			break;

		case COMMENT:
			if (c != '*')
			{
				s += c;
				c = gc();
			}
			else
			{
				c = gc();
				if (c == '/')
				{
					cout << "COMMENT: " << s << endl;
					c = gc();
					s = c;
					L = BEGIN;
				}
			}
			break;
		}
	}

	return 0;
}
