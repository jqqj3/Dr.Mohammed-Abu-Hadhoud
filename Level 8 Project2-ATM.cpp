#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct stClientData {
    string AccountNumber, PinCode, Name, Phone;
    double AccountBalance;

};

fstream FClient;

string ReadString(string Message);
float ReadNumber(string Message);

stClientData ConvertLineToRecord(string stLine, string Seperator = "#//#");

vector <stClientData> LoadClientsDataFromFile(string FileName);
vector <string> MySplit(string S1, string delim = "#//#");

string ConvertRecordToLine(stClientData CD, string Seperator = "#//#");

int Withdraw(int Balance);

void MenueATM();
void MenueQuickWithdraw();
void MenueNormalWithdraw();

void Start();
void LoginATM();

void ReturnToTheFile();
void QuickWithdraw();
void NormalWithdraw();
void Deposit();
void CheckBalance();


vector <stClientData> vClient = LoadClientsDataFromFile("Client File");
stClientData Client;
int main()
{
    LoginATM();
    
    return 0;
}


string ReadString(string Message) {

    cout << Message;
    getline(cin >> ws, Message);

    return Message;
}
float ReadNumber(string Message) {

    float Number = 0;

    cout << Message;
    cin >> Number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Invalid Number, Enter a valid one: ";
        cin >> Number;
    }

    return Number;

}

stClientData ConvertLineToRecord(string stLine, string Seperator) {

    stClientData CD;
    vector<string> S1 = MySplit(stLine, Seperator);

    CD.AccountNumber = S1[0];
    CD.PinCode = S1[1];
    CD.Name = S1[2];
    CD.Phone = S1[3];
    CD.AccountBalance = stod(S1[4]);

    return CD;
}

vector <stClientData> LoadClientsDataFromFile(string FileName)
{
    vector <stClientData> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    string Line;
    stClientData Client;
    while (getline(MyFile, Line))
    {
        Client = ConvertLineToRecord(Line);
        vClients.push_back(Client);
    }
    MyFile.close();

    return vClients;
}
vector <string> MySplit(string S1, string delim)
{
    vector<string> vWord;
    short Counter = 0;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vWord.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != "")
    {
        sWord = S1.substr(0, pos);
        vWord.push_back(sWord);
    }

    return vWord;
}

string ConvertRecordToLine(stClientData CD, string Seperator) {

    string stCD = "";
    stCD = CD.AccountNumber + Seperator;
    stCD += CD.PinCode + Seperator;
    stCD += CD.Name + Seperator;
    stCD += CD.Phone + Seperator;
    stCD += to_string(CD.AccountBalance);

    return stCD;
}

int Withdraw(int Balance) {

    if (Client.AccountBalance >= Balance) {

        char Check = 'n';
        cout << "\n\nAre you sure you want perform this transaction? y/n: "; cin >> Check;
        
        if(Check == 'y' || Check == 'Y')
        {
            Client.AccountBalance -= Balance;
            ReturnToTheFile();
            cout << "\n\nDone Successfully. New Balance is " << Client.AccountBalance << endl << endl;;
        }
        return 1;

    }
    else {
        cout << "\n\nThe amount exceeds your balance, make another choice.\n"; system("pause>0");
        return 0;
    }

}

void MenueATM() {

    system("Cls");
    cout << "======================================================================\n";
    cout << "\t\t\t ATM Main Menue Screen\n";
    cout << "======================================================================\n";
    cout << "[1] Quick Withdraw.\n";
    cout << "[2] Normal Withdraw.\n";
    cout << "[3] Deposit.\n";
    cout << "[4] Check Balance.\n";
    cout << "[5] Logout.\n";
    cout << "======================================================================\n";

}
void MenueQuickWithdraw() {

    system("Cls");
    cout << "======================================================================\n";
    cout << "\t\t\t Quick Withdraw\n";
    cout << "======================================================================\n";
    cout << "[1] 20 \t\t\t[2] 50\n";
    cout << "[3] 100 \t\t[4] 200\n";
    cout << "[5] 400 \t\t[6] 600\n";
    cout << "[7] 800 \t\t[8] 1000\n";
    cout << "[9] Exit\n";
    cout << "======================================================================\n";

}
void MenueNormalWithdraw() {

    system("Cls");
    cout << "======================================================================\n";
    cout << "\t\t\t Normal Withdraw\n";
    cout << "======================================================================\n\n";

}

void Start() {

    int NumChoose = 0;
    do {
        system("Cls");
        MenueATM();
        NumChoose = (int)ReadNumber("Choose what do you want to do? [1 to 5]: ");
        switch (NumChoose)
        {
        case 1: system("Cls"); QuickWithdraw(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;
        case 2: system("Cls"); NormalWithdraw(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;
        case 3: system("Cls"); Deposit(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;
        case 4: system("Cls"); CheckBalance(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;
        
        default:
            break;
        }
    } while (NumChoose != 5);

}
void LoginATM() {

    string NameFile = "Client File";
    vector <stClientData> vClient = LoadClientsDataFromFile("Client File");
    string AccountNumber, Pin;
    bool chick = false;

    while (true)
    {
        system("Cls");
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t Login Screen\n";
        cout << "----------------------------------------------------------------------------------------------\n\n";

        if (chick)
            cout << "Invlaid Username/PassWord!\n\n";

        AccountNumber = ReadString("Enter Account Number: ");
        Pin = ReadString("Enter Pin: ");
        for (stClientData& Userindex : vClient) {
            if (AccountNumber == Userindex.AccountNumber && Pin == Userindex.PinCode)
            {
                chick = false;
                Client = Userindex;
                Start();
                break;
            }
            else
                chick = true;
        }

    }

}

void ReturnToTheFile() {
    
    FClient.open("Client File", ios::out);
    for (stClientData& C : vClient) {
        if (C.AccountNumber == Client.AccountNumber && C.PinCode == Client.PinCode)
            C = Client;
        FClient << ConvertRecordToLine(C) << endl;
    }
    FClient.close();
}
void QuickWithdraw() {
    
    int NumChoose = 0, chick = 0;
    do
    {
        system("Cls");
        MenueQuickWithdraw();
        cout << "Your Balance is " << (int)Client.AccountBalance << endl << endl;

        NumChoose = (int)ReadNumber("Choose what to Withdraw from [1] to [9]: ");

        switch (NumChoose)
        {
        case 1: chick = Withdraw(20);   break;
        case 2: chick = Withdraw(50);   break;
        case 3: chick = Withdraw(100);  break;
        case 4: chick = Withdraw(200);  break;
        case 5: chick = Withdraw(400);  break;
        case 6: chick = Withdraw(600);  break;
        case 7: chick = Withdraw(800);  break;
        case 8: chick = Withdraw(1000); break;
        default:
            break;
        }
    } while (chick == 0 && NumChoose != 9);

}
void NormalWithdraw() {

    int MultiplesOf5 = 0, chick = 0;
    system("Cls");
    MenueNormalWithdraw();
    cout << "Your Balance is " << (int)Client.AccountBalance << endl << endl;
    do
    {
       MultiplesOf5 = (int)ReadNumber("\nEnter an amount multiples of 5\'s: ");
       
       if(MultiplesOf5 % 5 == 0)
       {
           chick = Withdraw(MultiplesOf5);
       }
    } while (chick == 0);
    
    
}
void Deposit() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Deposit Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    int AccountBalance = ReadNumber("Enter a positive deposit Amount: ");
    char Check = 'n';
    cout << "Are you sure you want perform this transaction? y/n: "; cin >> Check;
    if (toupper(Check) == toupper('y')) {
        Client.AccountBalance += AccountBalance;
        ReturnToTheFile();
        cout << "Done Successfully. New balance is: " << Client.AccountBalance << endl << endl;
    }
}
void CheckBalance() {
    system("Cls");
    cout << "======================================================================\n";
    cout << "\t\t\t Check Balance Screen\n";
    cout << "======================================================================\n\n";

    cout << "Your Balance is " << (int)Client.AccountBalance;
}
