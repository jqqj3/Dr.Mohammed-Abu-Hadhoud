#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

struct sClientData {
    string NumberAccount, PinCode, Name, Phone;
    double AccountBalance;

};
fstream FClient;

sClientData ConvertLineToRecord(string stLine, string Seperator = "#//#");

void Menue() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Main Menue Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "[1] Show Client List.\n";
    cout << "[2] Add New Client.\n";
    cout << "[3] Delete Client.\n";
    cout << "[4] Update Client Info.\n";
    cout << "[5] Find Client.\n";
    cout << "[6] Exit.\n";
    cout << "----------------------------------------------------------------------------------------------\n";
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
string ReadString(string Message) {

    cout << Message;
    getline(cin >> ws, Message);

    return Message;
}


vector <string>  MySplit(string S1, string delim = "#//#")
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
vector <sClientData> LoadClientsDataFromFile(string FileName)
{
    vector <sClientData> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    
    string Line;
    sClientData Client;
    while (getline(MyFile, Line))
    {
        Client = ConvertLineToRecord(Line);
        vClients.push_back(Client);
    }
    MyFile.close();

    return vClients;
}

sClientData ConvertLineToRecord(string stLine, string Seperator) {

    sClientData CD;
    vector<string> S1 = MySplit(stLine, Seperator);

    CD.NumberAccount = S1[0];
    CD.PinCode = S1[1];
    CD.Name = S1[2];
    CD.Phone = S1[3];
    CD.AccountBalance = stod(S1[4]);

    return CD;
}

bool IsClientAdded(string NumberAccoutn) {
    
    vector <sClientData> C;
    sClientData CD;
    string line;
    FClient.open("Client File", ios::in);
    while (getline(FClient, line)) {
        CD = ConvertLineToRecord(line);
        if (CD.NumberAccount == NumberAccoutn)
        {
            FClient.close();
            return true;
        }
    }
    FClient.close();
    
    return false;
}
bool FindClientByAccountNumber(string AccountNumber, sClientData& Client)
{
    vector <sClientData> vClients = LoadClientsDataFromFile("Client File");

    for (sClientData C : vClients)
    {
        if (C.NumberAccount == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

string ConvertRecordToLine(sClientData CD, string Seperator = "#//#") {

    string stCD = "";
    stCD = CD.NumberAccount + Seperator;
    stCD += CD.PinCode + Seperator;
    stCD += CD.Name + Seperator;
    stCD += CD.Phone + Seperator;
    stCD += to_string(CD.AccountBalance);

    return stCD;
}

void UpdateBankClient(sClientData& CD) {

    CD.PinCode = ReadString("Enter PinCode: ");
    CD.Name = ReadString("Enter your Name: ");
    CD.Phone = ReadString("Enter Phone Number: ");
    CD.AccountBalance = ReadNumber("Enter AccountBalance: ");


}
void PrintSClientData(sClientData CD) {

    cout << setw(17) << left << "Account Number: " << CD.NumberAccount << endl;
    cout << setw(17) << left << "Pin Code: " << CD.PinCode << endl;
    cout << setw(17) << left << "Name: " << CD.Name << endl;
    cout << setw(17) << left << "Phone: " << CD.Phone << endl;
    cout << setw(17) << left << "Account Balance: " << CD.AccountBalance << endl;

}
bool ReadBankClient(sClientData& CD) {

    CD.NumberAccount = ReadString("Enter Account Number: ");
    if(!IsClientAdded(CD.NumberAccount))
    {
        CD.PinCode = ReadString("Enter PinCode: ");
        CD.Name = ReadString("Enter your Name: ");
        CD.Phone = ReadString("Enter Phone Number: ");
        CD.AccountBalance = ReadNumber("Enter AccountBalance: ");
    }
    else
    {
        cout << "\nThe Client is added befor!\n";
        return false;
    }
    
    return true;
}

void ReadFile(string NameFile = "Client File") {

    vector <sClientData> C;
    sClientData CD;
    string line;
    FClient.open(NameFile, ios::in);

    while (getline(FClient, line)) {
        CD = ConvertLineToRecord(line);
        C.push_back(CD);
    }
    FClient.close();

    cout << setw(300) << "Client list (" << C.size() << ") Client(s)" << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| Accoiunt Number     " << "| Pin Code        " << "| Client Name                          " << "| Phone              " << "| Balance            " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

    for(sClientData& CD: C){
        
        cout << "| " << CD.NumberAccount << setw(22 - CD.NumberAccount.length());
        cout << "| " << CD.PinCode << setw(18 - CD.PinCode.length());
        cout << "| " << CD.Name << setw(38 - CD.Name.length());
        cout << "| " << CD.Phone << setw(21 - CD.Phone.length());
        cout << "| " << CD.AccountBalance << endl;

    }
    cout << "\n----------------------------------------------------------------------------------------------------------------------" << endl;
    
}
void AddClient()
{
    char choose = 'y';
    sClientData CD;
    do {
        system("cls");
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t Add Clients Screen\n";
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "Adding New Client\n\n";
        if (!ReadBankClient(CD))
            break;

        FClient.open("Client File", ios::out | ios::app);
        FClient << ConvertRecordToLine(CD) << endl;
        FClient.close();

        cout << "\nCilent Added Successfully,\nDo you want to add more clients? Yes = y/No = n : "; cin >> choose;

    } while (toupper(choose) == toupper('y'));

}
void DeletClientByAccountNumber() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Delete Client Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    sClientData CD;
    string AccountNumber = ReadString("Enter Account Number For Delet Client? ");

    if (FindClientByAccountNumber(AccountNumber, CD))
    {
        PrintSClientData(CD);

        char Check = 'n';

        cout << "\nAre you sure you want delete this Client? y/n ?"; cin >> Check;
        if (tolower(Check) == 'y')
        {
            vector <sClientData> vClient = LoadClientsDataFromFile("Client File");
            FClient.open("Client File", ios::out);
            for (sClientData& C : vClient) {
                if (C.NumberAccount == AccountNumber)
                    continue;

                FClient << ConvertRecordToLine(C) << endl;
            }
            FClient.close();
            cout << "\nClient Deleted Successfully." << endl;
        }
    }
    else
        cout << "Client with Account Number (" << AccountNumber << ") Not Found!";
}
void UpdateClientByAccountNumber() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Update Client Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    sClientData CD;
    string AccountNumber = ReadString("Enter Account Number For Update Client? ");

    if (FindClientByAccountNumber(AccountNumber, CD))
    {
        PrintSClientData(CD);

        char Check = 'n';

        cout << "\nAre you sure you want Update this Client? y/n ?"; cin >> Check;
        if (tolower(Check) == 'y')
        {
            vector <sClientData> vClient = LoadClientsDataFromFile("Client File");
            FClient.open("Client File", ios::out);
            for (sClientData& C : vClient) {
                if (C.NumberAccount == AccountNumber)
                    UpdateBankClient(C);

                FClient << ConvertRecordToLine(C) << endl;
            }
            FClient.close();
            cout << "\nClient Updated Successfully." << endl;
        }
    }
    else
        cout << "Client with Account Number (" << AccountNumber << ") Not Found!";

}
void FindClientAccountNumber() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Search Client Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    string AccountNumber = ReadString("Enter Account Number? ");

    sClientData CD;
    if (FindClientByAccountNumber(AccountNumber, CD)) {

        PrintSClientData(CD);

    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") Not Found!";

    }

}

void Start() {
    
    int NumChoose = 0;
    do {
        system("Cls"); 
        Menue();
        NumChoose = (int) ReadNumber("Choose what do you want to do? [1 to 6]: ");
        switch (NumChoose)
        {
        case 1: system("Cls"); ReadFile(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break; 
        case 2: system("Cls"); AddClient(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break; 
        case 3: system("Cls"); DeletClientByAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break; 
        case 4: system("Cls"); UpdateClientByAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;
        case 5: system("Cls"); FindClientAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0"); break;

        default:
            break;
        }
    } while (NumChoose != 6);

}

int main()
{
    Start();

    return 0;
}
