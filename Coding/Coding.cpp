#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enATMMainMenuOptions {
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eExit = 5
};

const string ClientsFileName = "Clients.txt";

struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient CurrentClient;

void Login();
void ShowATMMainMenu();
void ShowNormalWithdrawScreen();



vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite Mode

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                CurrentClient.AccountBalance = C.AccountBalance;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
    }
    return false;
}



short ReadQuickWithdrawOption()
{
    short Choice = 0;
    while (Choice < 1 || Choice > 9)
    {
        cout << "Choose what to do from [1] to [9] ? ";
        cin >> Choice;
    }
    return Choice;
}


short GetQuickWithdrawAmount(short QuickWithdrawOption)
{
    switch (QuickWithdrawOption)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 400;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    default: return 0;
    }
}

void PerformQuickWithdraw(short QuickWithdrawOption)
{
 

    if (QuickWithdrawOption == 9)
    {
        return;
    }


    short WithdrawAmount = GetQuickWithdrawAmount(QuickWithdrawOption);

    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Any key to continue...";
        system("pause>0");
        return;
    }

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClients);
}


void ShowQuickWithdrawScreen()
{
    cout << "\n===========================================\n";
    cout << "\tQuick Withdraw Screen";
    cout << "\n===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";

    cout << "Your balance now is " << CurrentClient.AccountBalance;

    PerformQuickWithdraw(ReadQuickWithdrawOption());
}
void ShowCheckBalanceScreen()
{
    cout << "\n===========================================\n";
    cout << "\tCheck Balance Screen";
    cout << "\n===========================================\n";

    cout << "Your Balance is: " << CurrentClient.AccountBalance << "\n";
}

double ReadDepositAmount()
{
    double DepositAmount;
    cout << "\nEnter a positive Deposit Amount? ";
    cin >> DepositAmount;

    while (DepositAmount<=0)
    {
        cout << "\nPlease enter positive deposit amount? ";
        cin >> DepositAmount;
    }
    return DepositAmount;

}
void PerformDeopsitOption()
{
    double DepositAmount = ReadDepositAmount();
   

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
}

void ShowDepositScreen()
{
    cout << "\n===========================================\n";
    cout << "\tDeposit Screen";
    cout << "\n===========================================\n";
    PerformDeopsitOption();

   
}

int ReadWithdrawAmount()
{
    int Amount;
    cout << "\nEnter an amount multiple of 5's ? ";
    cin >> Amount;
    while (Amount % 5 != 0)
    {
        cout << "\nInvalid Amount! It must be a multiple of 5's.\nPlease enter an amount multiple of 5's ?";
        cin >> Amount;
    }

    return Amount;
}
void PerformNormalWithdrawOption()
{
    int WithdrawAmount = ReadWithdrawAmount();

    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Any key to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClients);
}
void ShowNormalWithdrawScreen()
{
    cout << "\n===========================================\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n===========================================\n";
    PerformNormalWithdrawOption();

  
}





short ReadATMMainMenuOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> Choice;
    return Choice;
}



void GoBackToATMMainMenu()
{
    cout << "\n\nPress any key to go back to ATM Main Menu...";
    system("pause>0");
    ShowATMMainMenu();
}

void PerformATMMainMenuOption(enATMMainMenuOptions ATMOption)
{
    switch (ATMOption)
    {
    case enATMMainMenuOptions::eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToATMMainMenu();
        break;

    case enATMMainMenuOptions::eNormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToATMMainMenu();
        break;

    case enATMMainMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToATMMainMenu();
        break;

    case enATMMainMenuOptions::eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToATMMainMenu();
        break;

    case enATMMainMenuOptions::eExit:
        system("cls");
        Login();
        break;
    }
}

void ShowATMMainMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";

    PerformATMMainMenuOption((enATMMainMenuOptions)ReadATMMainMenuOption());
}

bool LoadClientInfo(string AccountNimber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNimber, PinCode, CurrentClient))
        return true;
    else
    {
        return false;
    }
}

void Login()
{
    bool isLoginFailed = false;
    string AccountNumber, PinCode;

    do
    {
        system("cls");
        cout << "\n===========================================\n";
        cout << "\tLogin Screen";
        cout << "\n===========================================\n";

        if (isLoginFailed)
        {
            cout << "Invalid Account Number/PinCode!\n";
        }

        cout << "Enter Account Number? ";
        cin >> AccountNumber;

        cout << "Enter Pin? ";
        cin >> PinCode;

        isLoginFailed = !LoadClientInfo(AccountNumber, PinCode);

    } while (isLoginFailed);

   
    ShowATMMainMenu();
}

int main()
{
    Login();

    

    return 0;
}