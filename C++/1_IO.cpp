#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Enter the score count: ";
    int maxSize;
    cin >> maxSize;

    int* const scores = new int[maxSize];
    int scr = 0;
    string str("");
    int index = 0;
    int sum = 0;

    while (str != "quit")
    {
        cout << "Enter command: (add, sum, average, quit) ";
        cin >> str;
        for (int i = 0; i < str.size(); i++) { str[i] = tolower(str[i]); }

        if(str == "add")
        {
            if(index == maxSize)
            {
                cout << "\tToo many scores" << endl;
                continue;
            }

            cout << "Enter score: ";
            cin >> scr;
            if(scr < 0 || scr > 100)
            {
                cout << "\tScore should be between 0 and 100 " << endl;
                continue;
            }

            scores[index++] = scr;
            sum += scr;
            cout << "\t" << scr << " added" << endl;
        }

        else if(str == "quit")
        {
            cout << "\tBye" << endl;
            continue;
        }

        else if(str == "sum")
        {
                cout << "\tSum: " << sum << endl;
        }

        else if(str == "average")
        {
            if(index == 0)
            {
                cout << "1�� �̻��� ������ �ԷµǾ�� �Ѵ�" << endl;
                continue;
            }
            double avg = (double)sum / index;
            cout << "\tAverage: " << avg << endl;
        }
        else
        {
            cout << "�߸��� �Է��Դϴ�, �ٽ� �Է����ּ���" << endl;
        }
    }

    delete []scores;
    return 0;
}
