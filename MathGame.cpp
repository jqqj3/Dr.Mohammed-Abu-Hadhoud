#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel {
    EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4
};
enum enOperationType {
    Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5
};

struct finalResutls
{
    int numberOfQuestion = 0, numberOfRightAnswer = 0, numberOfWrongAnswer = 0;
    enOperationType opType;
    enQuestionsLevel questionLevel;
};

int ReadPositiveNumber(string message, int n) {
    int number;
    do {
        cout << message << " ";
        cin >> number;
    } while (number < 0 || number > n);
    return number;
}
int RandomNumber(int from, int to) {

    int randNum = rand() % (to - from + 1) + from;

    return randNum;
}


enQuestionsLevel CheckLevel(int questions) {

    switch (questions)
    {
    case 1:
        return enQuestionsLevel::EasyLevel;
    case 2:
        return enQuestionsLevel::MedLevel;
    case 3:
        return enQuestionsLevel::HardLevel;
    case 4:
        return enQuestionsLevel::Mix;
    default:
        break;
    }
}

enOperationType CheckOperation(int operation) {

    switch (operation)
    {
    case 1:
        return enOperationType::Add;
    case 2:
        return enOperationType::Sub;
    case 3:
        return enOperationType::Mult;
    case 4:
        return enOperationType::Div;
    case 5:
        return enOperationType::MixOp;
    default:
        break;
    }
}

string ChangeOperation(enOperationType type) {

    switch (type) {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mult:
        return "*";
    case Div:
        return "/";
    case MixOp:
        return "MixOp";
    }
}
string ChangeQuestions(enQuestionsLevel type) {

    switch (type)
    {
    case EasyLevel:
        return "Easy";
    case MedLevel:
        return "Med";
    case HardLevel:
        return "Hard";
    case Mix:
        return "Mix";
    default:
        break;
    }

}

void PrintRoll2(int number1, int number2, finalResutls& f1) {
    
    int answer;
    enOperationType n;
    
    if (f1.opType == enOperationType::MixOp)
        n = CheckOperation(RandomNumber(1, 4));
    else
        n = f1.opType;
    cout << number1 << endl;
    cout << number2 << "  " << ChangeOperation(n) << endl;
    cout << "\n-----------\n";
    cin >> answer;
    
    switch (n)
    {
    case 1:
        if (number1 + number2 == answer)
        {
            system("color 2F");
            cout << "\nRight answer :-)\n";
            ++f1.numberOfRightAnswer;
            break;
        }
        else
        {
            system("color 4F");
            cout << "\a";
            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is: " << number1 + number2 << endl;
            f1.numberOfWrongAnswer++;
            break;
        }
    case 2:
        if (number1 - number2 == answer)
        {
            system("color 2F");
            cout << "\nRight answer :-)\n";
            f1.numberOfRightAnswer++;
            break;
        }
        else
        {
            system("color 4F");
            cout << "\a";
            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is: " << number1 - number2 << endl;
            f1.numberOfWrongAnswer++;
            break;
        }
    case 3:
        if (number1 * number2 == answer)
        {
            system("color 2F");
            cout << "\nRight answer :-)\n";
            f1.numberOfRightAnswer++;
            break;
        }
        else
        {
            system("color 4F");
            cout << "\a";
            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is: " << number1 * number2 << endl;
            f1.numberOfWrongAnswer++;
            break;
        }
    case 4:
        if (number1 / number2 == answer)
        {
            system("color 2F");
            cout << "\nRight answer :-)\n";
            f1.numberOfRightAnswer++;
            break;
        }
        else
        {
            system("color 4F");
            cout << "\a";
            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is: " << number1 / number2 << endl;
            f1.numberOfWrongAnswer++;
            break;
        }
    default:
        break;
    }

}
void PrintRoll(finalResutls& f1) {
    

    int counter = 0;
    do {
        cout << "\n\nQuestion [" << ++counter << "/" << f1.numberOfQuestion << "]\n\n";
        switch (f1.questionLevel)
            {
            case EasyLevel:
                PrintRoll2(RandomNumber(1, 10), RandomNumber(1, 10), f1);
                break;
            case MedLevel:
                PrintRoll2(RandomNumber(11, 50), RandomNumber(11, 50), f1);
                break;
            case HardLevel:
                PrintRoll2(RandomNumber(51, 100), RandomNumber(51, 100), f1);
                break;
            case Mix:
                PrintRoll2(RandomNumber(1, 100), RandomNumber(1, 100), f1);
                break;
            default:
                break;
            }
    } while (counter != f1.numberOfQuestion);

    
    
}

void PrintResult(finalResutls f1) {
    cout << "\n------------------------------------------\n";
    if (f1.numberOfWrongAnswer > f1.numberOfRightAnswer)
    {
        system("color 4F");
        cout << "\nFinal Resutls is Fail :-(\n";
    }
    else {
        cout << "\nFinal Results is PASS :-)\n";
    }

    cout << "\n------------------------------------------\n";
    cout << "\nNumber of Questions     : " << f1.numberOfQuestion << endl;
    cout << "Questions Level\t\t: " << ChangeQuestions(f1.questionLevel) << endl;
    cout << "OpType\t\t\t: " << ChangeOperation(f1.opType) << endl;
    cout << "Number of Right Answers : " << f1.numberOfRightAnswer << endl;
    cout << "Number of Wrong Answers : " << f1.numberOfWrongAnswer << endl;
    cout << "\n------------------------------------------\n";


}

void ResetScreen() {

    system("cls");
    system("color 0F");
}

void StartAnswer() {

    
    char choose = 'y';
    
    do {
        ResetScreen();
        finalResutls f1;
        f1.numberOfQuestion = ReadPositiveNumber("How many questions do you want to answer? from 1 to 10: ", 10);
        int level = ReadPositiveNumber("Which level do you want? Easy:1, Med:2, Hard:3 ?", 3);
        int operationsType = ReadPositiveNumber("How do you want operation type? Add:1, Sub:2, Mult:3, Div:4 or Mix:5? ", 5);
    
        f1.questionLevel = CheckLevel(level);
        f1.opType = CheckOperation(operationsType);
        PrintRoll(f1);
        PrintResult(f1);

        cout << "Do you want to play again? Y/N? "; cin >> choose;
        
    } while (toupper(choose) == 'Y');

}


int main()
{
    srand((unsigned)time(NULL));
    StartAnswer();

    return 0;
}
