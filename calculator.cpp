// first try for calculator

#include <iostream>
#include <limits>

using namespace std;

double Deist(double a, char b, double c)
{
    double d;
    switch (b)
    {
    case '+':
        d = a + c;
        return d;
    case '-':
        d = a - c;
        return d;
    case '*':
        d = a * c;
        return d;
    case '/':
        d = a / c;
        return d;
    }
}

int main()
{
    double Sum1, Sum2, Result, A;
    char Operation;
    short int n = 3;

    cout << "Vuvedi 1va stoinost: ";

    while (!(cin >> Sum1))
    {
        cout << "Vuvedi chislo za 1va stoinost ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    do
    {
        cout << "Vuvedi deistvie (+, -, *, /): ";
        cin >> Operation;
    } while (Operation != '+' && Operation != '-' && Operation != '*' && Operation != '/');

    cout << "Vuvedi 2ra stoinost: ";

    while (!(cin >> Sum2))
    {
        cout << "vuvedi chislo za 2ra stoinost ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Result = Deist(Sum1, Operation, Sum2);
    A = Result;

    do
    {
        cout << "Vuvedi deistvie (+, -, *, /, =): ";
        cin >> Operation;
        if (Operation == '+' || Operation == '-' || Operation == '*' || Operation == '/' || Operation == '=')
        {
            if (Operation != '=')
            {
                cout << "Vuvedi " << n << "ta stoinsot: ";

                while (!(cin >> Sum2))
                {
                    cout << " vuvedi chislo za " << n << "ta stoinost: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                n++;
                Result = Deist(0, Operation, Sum2);
                A = A + Result;
            }
        }
    } while (Operation != '=');
    cout << "Rezultat: " << A;

    return 0;
}