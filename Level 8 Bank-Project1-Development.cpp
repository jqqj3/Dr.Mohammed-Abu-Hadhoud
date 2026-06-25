#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

enum enMainMenuePermissions {
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient= 4,
    pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
};

struct sClientData {
    string NumberAccount, PinCode, Name, Phone;
    double AccountBalance;

};
struct stUsersinfo {
    string Admin, PassWord, Permissions;
};

fstream FClient;
fstream FUsers;

void Start(stUsersinfo User);
void Transactions();
void ManageUsers();

sClientData ConvertLineToRecord(string stLine, string Seperator = "#//#");
stUsersinfo ConvertLineToRecordUser(string stLine, string Seperator = "#//#");

void Menue() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Main Menue Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "[1] Show Client List.\n";
    cout << "[2] Add New Client.\n";
    cout << "[3] Delete Client.\n";
    cout << "[4] Update Client Info.\n";
    cout << "[5] Find Client.\n";
    cout << "[6] Transactions.\n";
    cout << "[7] Manage Users.\n";
    cout << "[8] Logout.\n";
    cout << "----------------------------------------------------------------------------------------------\n";
}
void MenueTransactions() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Transactions Menue Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "[1] Deposit.\n";
    cout << "[2] Withdraw.\n";
    cout << "[3] Total Balances.\n";
    cout << "[4] Main Menue.\n";
    cout << "----------------------------------------------------------------------------------------------\n";
}
void MenueManageUsers() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t MenueManage Users Menue Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "[1] List Users.\n";
    cout << "[2] Add New User.\n";
    cout << "[3] Delete User.\n";
    cout << "[4] Update User.\n";
    cout << "[5] Find User.\n";
    cout << "[6] Main Menue.\n";
    cout << "----------------------------------------------------------------------------------------------\n";
}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';
    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }
    cout << "\nDo you want to give access to : \n ";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        Permissions += enMainMenuePermissions::pListClients;
    }
    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }
    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }
    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }
    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }
    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }
    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }
    return Permissions;
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
vector <stUsersinfo> LoadUsersDataFromFile(string FileName)
{
    vector <stUsersinfo> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    string Line;
    stUsersinfo user;
    while (getline(MyFile, Line))
    {
        user = ConvertLineToRecordUser(Line);
        vUsers.push_back(user);
    }
    MyFile.close();

    return vUsers;
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
stUsersinfo ConvertLineToRecordUser(string stLine, string Seperator) {

    stUsersinfo User;
    vector<string> vUser = MySplit(stLine, Seperator);

    User.Admin = vUser[0];
    User.PassWord = vUser[1];
    User.Permissions = vUser[2];

    return User;
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
bool IsUserAdded(string AdminName) {

    vector <stUsersinfo> vUsers;
    stUsersinfo user;
    string line;
    FUsers.open("Users File", ios::in);
    while (getline(FUsers, line)) {
        user = ConvertLineToRecordUser(line);
        if (user.Admin == AdminName)
        {
            FUsers.close();
            return true;
        }
    }
    FUsers.close();

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
bool FindUserByAdminName(string AdminName, stUsersinfo& user)
{
    vector <stUsersinfo> vUsers = LoadUsersDataFromFile("Users File");

    for (stUsersinfo Userindex : vUsers)
    {
        if (Userindex.Admin == AdminName)
        {
            user = Userindex;
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
string ConvertRecordToLine(stUsersinfo user, string Seperator = "#//#") {

    string stUser = "";
    stUser = user.Admin + Seperator;
    stUser += user.PassWord + Seperator;
    stUser += user.Permissions + Seperator;

    return stUser;
}

void ReturnToTheFile(vector <sClientData> vCD) {
    FClient.open("Client File", ios::out);
    for (sClientData& C : vCD) {
        FClient << ConvertRecordToLine(C) << endl;
    }
    FClient.close();
}

void UpdateBankClient(sClientData& CD) {

    CD.PinCode = ReadString("Enter PinCode: ");
    CD.Name = ReadString("Enter your Name: ");
    CD.Phone = ReadString("Enter Phone Number: ");
    CD.AccountBalance = ReadNumber("Enter AccountBalance: ");


}
void UpdateBankUser(stUsersinfo& user) {

    user.PassWord = ReadString("Enter PassWord: ");
    user.Permissions = ReadString("Enter Permissions: ");


}
void PrintSClientData(sClientData CD) {

    cout << "The following are the client details:\n";
    cout << "----------------------------------------------------\n";
    cout << setw(17) << left << "Account Number: " << CD.NumberAccount << endl;
    cout << setw(17) << left << "Pin Code: " << CD.PinCode << endl;
    cout << setw(17) << left << "Name: " << CD.Name << endl;
    cout << setw(17) << left << "Phone: " << CD.Phone << endl;
    cout << setw(17) << left << "Account Balance: " << CD.AccountBalance << endl;
    cout << "----------------------------------------------------\n\n";

}
void PrintUserData(stUsersinfo user) {

    cout << "The following are the User details:\n";
    cout << "----------------------------------------------------\n";
    cout << setw(17) << left << "Admin Name: " << user.Admin << endl;
    cout << setw(17) << left << "PassWord: " << user.PassWord << endl;
    cout << setw(17) << left << "Permissions: " << user.Permissions << endl;
    cout << "----------------------------------------------------\n\n";

}
bool ReadBankClient(sClientData& CD) {

    CD.NumberAccount = ReadString("Enter Account Number: ");
    if (!IsClientAdded(CD.NumberAccount))
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
bool ReadBankUser(stUsersinfo& user) {

    user.Admin = ReadString("Enter Admin Name: ");
    if (!IsUserAdded(user.Admin))
    {
        user.PassWord = ReadString("Enter PassWord: ");
        user.Permissions = to_string(ReadPermissionsToSet());
    }
    else
    {
        cout << "\nThe User is added befor!\n";
        return false;
    }

    return true;
}

//
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

    for (sClientData& CD : C) {

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

void Deposit() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Deposit Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    string NumberAccount = ReadString("Enter Account Number: ");
    if (IsClientAdded(NumberAccount)) {
        vector <sClientData> vCD = LoadClientsDataFromFile("Client File");
        for (sClientData& C : vCD) {
            if (C.NumberAccount == NumberAccount) {
                PrintSClientData(C);
                int AccountBalance = ReadNumber("Enter deposit amount: ");
                char Check = 'n';
                cout << "Are you sure you want perform this transaction? y/n: "; cin >> Check;
                if (toupper(Check) == toupper('y')) {
                    C.AccountBalance += AccountBalance;
                    cout << "Done Successfully. New balance is: " << C.AccountBalance << endl << endl;
                    ReturnToTheFile(vCD);
                    break;
                }
                else break;
            }
        }
    }
    else
    {
        cout << "\nClient with [" << NumberAccount << "] does not exist.\n";
    }

}
void TotalBalances() {
    vector <sClientData> vC;
    sClientData CD;
    string line;
    FClient.open("Client File", ios::in);

    while (getline(FClient, line)) {
        CD = ConvertLineToRecord(line);
        vC.push_back(CD);
    }
    FClient.close();

    cout << setw(150) << "Client list (" << vC.size() << ") Client(s)" << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| Accoiunt Number     " << "| Client Name                          " "| Balance            " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    int Total = 0;
    for (sClientData& CD : vC) {

        cout << "| " << CD.NumberAccount << setw(22 - CD.NumberAccount.length());
        cout << "| " << CD.Name << setw(38 - CD.Name.length());
        cout << "| " << CD.AccountBalance << endl;
        Total += CD.AccountBalance;
    }
    cout << "\n----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t Total Balances = " << Total << endl << endl;
}
void Withdraw() {
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Deposit Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    string NumberAccount = ReadString("Enter Account Number: ");
    if (IsClientAdded(NumberAccount)) {
        vector <sClientData> vCD = LoadClientsDataFromFile("Client File");
        for (sClientData& C : vCD) {
            if (C.NumberAccount == NumberAccount) {
                PrintSClientData(C);
                int AccountBalance = ReadNumber("Enter withdraw amount: ");
                while (C.AccountBalance < AccountBalance) {
                    cout << "\nAmount Exceeds the balance, you can withdraw up to: " << C.AccountBalance << endl;
                    AccountBalance = ReadNumber("Enter withdraw amount: ");
                }
                char Check = 'n';
                cout << "\nAre you sure you want perform this transaction? y/n: "; cin >> Check;
                if (toupper(Check) == toupper('y')) {
                    C.AccountBalance -= AccountBalance;
                    cout << "\nDone Successfully. New balance is: " << C.AccountBalance << endl << endl;
                    ReturnToTheFile(vCD);
                    break;
                }
                else break;
            }
        }
    }
    else
    {
        cout << "\nClient with [" << NumberAccount << "] does not exist.\n";
    }

}

//Manage Users
void ListUsers() {

    string NameFile = "Users File";
    vector <stUsersinfo> vUsers;
    stUsersinfo user;
    string line;
    FUsers.open(NameFile, ios::in);

    while (getline(FUsers, line)) {
        user = ConvertLineToRecordUser(line);
        vUsers.push_back(user);
    }
    FUsers.close();

    cout << setw(300) << "User List (" << vUsers.size() << ") User(s)" << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    cout << "| User Name        " << "| Password        " << "| Permissions         " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    for (stUsersinfo& userindex : vUsers) {

        cout << "| " << userindex.Admin << setw(19 - userindex.Admin.length());
        cout << "| " << userindex.PassWord << setw(18 - userindex.PassWord.length());
        cout << "| " << userindex.Permissions << endl;
        
    }
    cout << "\n----------------------------------------------------------------------------------------------------------------------" << endl;
}
void AddNewUser() {

    char choose = 'y';
    stUsersinfo user;
    do {
        system("cls");
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t Add User Screen\n";
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "Adding New User\n\n";
        if (!ReadBankUser(user))
            break;

        FUsers.open("Users File", ios::out | ios::app);
        FUsers << ConvertRecordToLine(user) << endl;
        FUsers.close();

        cout << "\nUser Added Successfully,\nDo you want to add more User? Yes = y/No = n : "; cin >> choose;

    } while (toupper(choose) == toupper('y'));

}
void DeleteUser() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Delete User Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    stUsersinfo user;
    string AdminName = ReadString("Enter Admin Name For Delet User? ");
    if (AdminName == "Admin")
    {
        cout << "\n\nYou Can not Delete This User.\n";
    }
    else
    if (FindUserByAdminName(AdminName, user))
    {
        PrintUserData(user);

        char Check = 'n';

        cout << "\nAre you sure you want delete this User? y/n ?"; cin >> Check;
        if (tolower(Check) == 'y')
        {
            vector <stUsersinfo> vUsers = LoadUsersDataFromFile("Users File");
            FUsers.open("Users File", ios::out);
            for (stUsersinfo& Userindex : vUsers) {
                if (Userindex.Admin == AdminName)
                    continue;

                FUsers << ConvertRecordToLine(Userindex) << endl;
            }
            FUsers.close();
            cout << "\nUser Deleted Successfully." << endl;
        }
    }
    else
        cout << "User with Admin Name (" << AdminName << ") Not Found!";
}
void UpdateUser() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Update User Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    stUsersinfo user;
    string AdminName = ReadString("Enter Admin Name For Update User? ");
    
    if (FindUserByAdminName(AdminName, user))
    {
        PrintUserData(user);

        char Check = 'n';

        cout << "\nAre you sure you want Update this User? y/n ?"; cin >> Check;
        if (tolower(Check) == 'y')
        {
            vector <stUsersinfo> vUsers = LoadUsersDataFromFile("Users File");
            FUsers.open("Users File", ios::out);
            for (stUsersinfo& Userindex : vUsers) {
                if (Userindex.Admin == AdminName)
                    UpdateBankUser(Userindex);

                FUsers << ConvertRecordToLine(Userindex) << endl;
            }
            FUsers.close();
            cout << "\nUser Update Successfully." << endl;
        }
    }
    else
        cout << "User with Admin Name (" << AdminName << ") Not Found!";
}
void FindUser() {

    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Search User Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    string AdminName = ReadString("Enter Admin Name? ");

    stUsersinfo user;
    if (FindUserByAdminName(AdminName, user)) {

        PrintUserData(user);

    }
    else
    {
        cout << "User with Admin Name (" << AdminName << ") Not Found!";

    }
}
void Message() {

    system("Cls");
    cout << "------------------------------------------------\n";
    cout << "Access Denied,\nYou don\'t Have Permission To Do this,\nP;ease Conact Your Admin.";
    cout << "\n------------------------------------------------\n";
    cout << "\nPress any key to go back to Menue..."; system("pause>0");

}

void Start(stUsersinfo User) {

    int NumChoose = 0;
    do {
        system("Cls");
        Menue();
        NumChoose = (int)ReadNumber("Choose what do you want to do? [1 to 7]: ");
        switch (NumChoose)
        {
        case 1: 
            if (stoi(User.Permissions) & enMainMenuePermissions::pListClients || stoi(User.Permissions) == -1)
            {
                system("Cls");
                ReadFile(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 2:
            if (stoi(User.Permissions) & enMainMenuePermissions::pAddNewClient || stoi(User.Permissions) == -1)
            {
                system("Cls");
                AddClient(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 3:
            if (stoi(User.Permissions) & enMainMenuePermissions::pDeleteClient || stoi(User.Permissions) == -1)
            {
                system("Cls"); DeletClientByAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 4:
            if (stoi(User.Permissions) & enMainMenuePermissions::pUpdateClients || stoi(User.Permissions) == -1)
            {
                system("Cls"); UpdateClientByAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 5:
            if (stoi(User.Permissions) & enMainMenuePermissions::pFindClient || stoi(User.Permissions) == -1)
            {
                system("Cls"); FindClientAccountNumber(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 6:
            if (stoi(User.Permissions) & enMainMenuePermissions::pTranactions || stoi(User.Permissions) == -1)
            {
                system("Cls"); Transactions(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;
        case 7:
            if (stoi(User.Permissions) & enMainMenuePermissions::pManageUsers || stoi(User.Permissions) == -1)
            {
                system("Cls"); ManageUsers(); cout << "\nPress any key to go back to Menue..."; system("pause>0");
            }
            else
                Message();
            break;

        default:
            break;
        }
    } while (NumChoose != 8);

}
void Transactions() {
    stUsersinfo user;
    int NumChoose = 0;
    do {
        system("Cls");
        MenueTransactions();
        NumChoose = (int)ReadNumber("Choose what do you want to do? [1 to 4]: ");
        switch (NumChoose)
        {
        case 1: system("Cls"); Deposit(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 2: system("Cls"); Withdraw(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 3: system("Cls"); TotalBalances(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 4: system("Cls"); Start(user); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;

        default:
            break;
        }
    } while (NumChoose != 4);
}
void ManageUsers() {
    stUsersinfo user;
    int NumChoose = 0;
    do {
        system("Cls");
        MenueManageUsers();
        NumChoose = (int)ReadNumber("Choose what do you want to do? [1 to 6]: ");
        switch (NumChoose)
        {
        case 1: system("Cls"); ListUsers(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 2: system("Cls"); AddNewUser(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 3: system("Cls"); DeleteUser(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 4: system("Cls"); UpdateUser(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 5: system("Cls"); FindUser(); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;
        case 6: system("Cls"); Start(user); cout << "\nPress any key to go back to Transactions Menue..."; system("pause>0"); break;

        default:
            break;
        }
    } while (NumChoose != 6);
}
void Login() {
    
    system("Cls");
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Login Screen\n";
    cout << "----------------------------------------------------------------------------------------------\n\n";

    string NameFile = "Users File";
    vector <stUsersinfo> vUsers;
    stUsersinfo user;
    string line;
    FUsers.open(NameFile, ios::in);

    while (getline(FUsers, line)) {
        user = ConvertLineToRecordUser(line);
        vUsers.push_back(user);
    }
    FUsers.close();
      
    string Username = ReadString("Enter Username: ");
    string UserPassWord = ReadString("Enter PassWord: ");
    bool chick = true;

    while (chick)
    {
        
        for (stUsersinfo& Userindex: vUsers) {
            if (Username == Userindex.Admin && UserPassWord == Userindex.PassWord)
            {
                //chick = false;
                Start(Userindex);
                break;
            }
        }
        system("Cls");
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t Login Screen\n";
        cout << "----------------------------------------------------------------------------------------------\n\n";
        cout << "Invlaid Username/PassWord!\n\n";
        Username = ReadString("Enter Username: ");
        UserPassWord = ReadString("Enter PassWord: ");
    }
    
    

}


int main()
{
    Login();

    return 0;
}
