#include <iostream>

using namespace std;

int a[100], b[100], c[100], tempmod[100], mod[100];
int acount, bcount, ap, cp=99, mp;
int div();
int mul(int);
void sub();
int main()
{
	int i, j;
	char ch[100];
	cout << "Enter first number:";
	cin >> ch;
	for (i=0; i<100; i++)
		if (ch[i] == '\0')
		{
			acount = (i-1);
			i--;
			for (j=0; j<=acount; j++)
				a[j] = ch[i--] - 48;
			break;
		}
	cout << "a=";
	for (i=acount; i>=0; i--)
		cout << a[i];
	cout << endl << "acount = " << acount << endl;
	for (i=0; i<100; i++)
		ch[i] = '\0';
	cout << "Enter second number:";
	cin >> ch;
	for (i=0; i<100; i++)
		if (ch[i] == '\0')
		{
			bcount = (i-1);
			i--;
			for (j=0; j<=bcount; j++)
				b[j] = ch[i--] - 48;
			break;
		}
	cout << "b=";
	for (i=bcount; i>=0; i--)
		cout << b[i];
	cout << endl << "bcount = " << bcount << endl;
	if (acount < bcount)
	{
		cout << "0 (1)";
		return 0;
	}
	else if (acount == bcount)
	{
		for (i=acount; i>=0; i--)
			if (a[i]<b[i])
			{
				cout << "0 (2)";
				return 0;
			}
			else if (a[i]>b[i])
				break;
	}
	ap = acount - bcount;
	cout << "ap = " << ap << endl;
	div();
	cout << "Result div = ";
	for (i=99; i>cp; i--)
		cout << c[i];
	cout << "\nMod = ";
	if (mp < 0)
		cout << "0";
	for (i=mp; i>=0; i--)
		cout << mod[i];
	return 0;
}
int div()
{
	int atemp, btemp, ctemp, i, j;
	if (acount-ap < bcount)
	{
		c[cp--] = 0;
		ap--;
		div();
		return 0;
	}
	else if (acount-ap == bcount)
	{
		for (i=acount, j=bcount; j>=0; i--, j--)
			if (a[i]<b[j])
			{
				c[cp--] = 0;
				ap--;
				div();
				return 0;
			}
			else if (a[i] > b[j])
				break;
		atemp = a[acount]*100 + a[acount-1]*10 + a[acount-2];
	}
	else
		atemp = a[acount]*1000 + a[acount-1]*100 + a[acount-2]*10 + a[acount-3];
	cout << "atemp = " << atemp << endl;
	btemp = b[bcount]*100 + b[bcount-1]*10 + b[bcount-2];
	cout << "btemp = " << btemp << endl;
	ctemp = atemp / btemp;
	cout << "ctemp = " << ctemp << endl;
	if (ctemp > 9)
		c[cp--] = ctemp / 10;
	c[cp--] = ctemp % 10;
	mul(ctemp);
	cout << "tempmod = ";
	for (i=99; i>=0; i--)
		cout << tempmod[i];
	cout << endl;
	sub();
	cout << "mod = ";
	for (i=mp; i>=0; i--)
		cout << mod[i];
	cout << endl;
	for (i=ap, j=0; i<=acount; i++, j++)
		a[i] = mod[j];
	acount = ap + mp;
	cout << "ACOUNT = " << acount << endl;
	cout << "A=";
	for (i=acount; i>=0; i--)
		cout << a[i];
	cout << endl;
	ap--;
	if (ap < 0)
	{
		for (i=0; i<=acount; i++)
			mod[i] = a[i];
		mp = acount;
		return 0;
	}
	div();
}
int mul(int ctemp)
{
	int i, temp1[100], temp2[100], carry=0;
	for (i=0; i<100; i++)
		tempmod[i] = temp1[i] = temp2[i] = 0;
	for (i=0; i<=bcount; i++)
	{
		temp1[i] = (b[i] * (ctemp%10) + carry) %10;
		carry = (b[i] * (ctemp%10) + carry) /10;
	}
	temp1[bcount+1] = carry;
	if (ctemp < 10)
	{
		for (i=0; i<=bcount+1; i++)
			tempmod[i] = temp1[i];
		return 0;
	}
	else
	{
		carry = 0;
		temp2[0] = 0;
		for (i=0; i<=bcount; i++)
		{
			temp2[i+1] = (b[i] * (ctemp/10) + carry) %10;
			carry = (b[i] * (ctemp/10) + carry) /10;
		}
		temp2[bcount+2] = carry;
		carry = 0;
		for (i=0; i<100; i++)
		{
			tempmod[i] = (temp1[i] + temp2[i] + carry) %10;
			carry = (temp1[i] + temp2[i] + carry) /10;
		}
		if (carry > 0)
			for (i=99; i>=0; i--)
				if (tempmod[i] > 0)
				{
					tempmod[i+1] = carry;
					return 0;
				}
	}
	return 0;
}
void sub()
{
	int i, j;
	for (i=0; i<100; i++)
		mod[i] = 0;
	mp = -1;
	for (i=0, j=ap; j<=acount; j++, i++)
	{
		if (a[j] < tempmod[i])
		{
			a[j+1]--;
			a[j] += 10;
		}
		mod[++mp] = a[j] - tempmod[i];
	}
	for (i=mp; i>=0; i--)
	{
		if (mod[i] > 0)
			break;
		mp--;
	}
	cout << "MP = " << mp << endl;
}
