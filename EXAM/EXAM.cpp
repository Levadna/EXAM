#include "CD.h"
#include "ArrayTemplate.h"
#define CREATE_OR_LOAD 1

int main() {
    srand(time(0));
    FILE* file = nullptr;
    CD* cds = nullptr;
    int NCDs = 0;

#if CREATE_OR_LOAD == 0
    NCDs = 2;
    cds = new CD[2]{
        {"Thriller", "Michael Jackson", 1982, 250, false},
        {"Back in Black", "AC/DC", 1980, 230, false}
    };
#else
    fopen_s(&file, "cd_store.txt", "r");
    if (file == nullptr) cout << "ERROR: not loaded!\n";
    else {
        fscanf_s(file, "%d\n", &NCDs);
        cds = new CD[NCDs];
        for (int i = 0; i < NCDs; i++)
            cds[i].loadFromTextFile(file);
        fclose(file);
    }
#endif

    int menu = 0;
    CD temp_cd;
    char temp[100];
    do {
        cout << "==============================\n";
        cout << " MUSIC STORE MENU\n";
        cout << "==============================\n";
        cout << "0 - Exit and Save\n";
        cout << "1 - Show all CDs\n";
        cout << "2 - Add new CD\n";
        cout << "3 - Rent CD\n";
        cout << "4 - Return CD\n";
        cout << "5 - Sell CD\n";
        cout << "6 - Search by Artist\n";
        cout << "7 - Sort by Year\n";
        cout << ">>> ";
        cin >> menu;

        switch (menu) {
        case 0:
            cout << "Saving...\n";
            break;
        case 1:
            if (NCDs == 0) cout << "List is empty!\n";
            else {
                for (int i = 0; i < NCDs; i++)
                    cds[i].print();
            }
            break;
        case 2:
            cin.ignore();
            temp_cd.fill();
            addItemBack(cds, NCDs, temp_cd);
            break;
        case 3:
            cin.ignore();
            cout << "Enter CD title to rent: ";
            cin.getline(temp, 100);
            for (int i = 0; i < NCDs; i++) {
                if (strcmp(cds[i].title, temp) == 0 && cds[i].isRented == false) {
                    double payment;
                    cout << "Rental price is 100 UAH. Enter amount you pay: ";
                    cin >> payment;
                    if (payment < 100) {
                        cout << "You can't rent this CD. Please pay 100 UAH.\n";
                    }
                    else {
                        cin.ignore();
                        cds[i].rent();
                        double change = payment - 100;
                        cout << "CD rented successfully. Your change is: " << change << " UAH\n";
                    }
                    break;
                }
            }
            break;
        case 4:
            cin.ignore();
            cout << "Enter CD title to return: ";
            cin.getline(temp, 100);
            for (int i = 0; i < NCDs; i++) {
                if (strcmp(cds[i].title, temp) == 0 && cds[i].isRented == true) {
                    cds[i].returnCD();
                    break;
                }
            }
            break;
        case 5:
            cin.ignore();
            cout << "Enter CD title to sell: ";
            cin.getline(temp, 100);
            for (int i = 0; i < NCDs; i++) {
                if (strcmp(cds[i].title, temp) == 0) {
                    if (cds[i].isRented == true) {
                        cout << "This CD is currently rented and cannot be sold.\n";
                        break;
                    }
                    double payment;
                    cout << "The price is " << cds[i].price << " UAH. Enter amount you pay: ";
                    cin >> payment;
                    if (payment < cds[i].price) {
                        cout << "You can't buy this CD. Please pay full price.\n";
                    }
                    else {
                        double change = payment - cds[i].price;
                        if (change > 0)
                            cout << "Thank you for your purchase! Your change is: " << change << " UAH\n";
                        else
                            cout << "Thank you for your purchase!\n";
                        for (int j = i; j < NCDs - 1; j++)
                            cds[j] = cds[j + 1];
                        NCDs--;
                    }
                    break;
                }
            }
            break;
        case 6:
            cin.ignore();
            cout << "Enter artist name: ";
            cin.getline(temp, 100);
            for (int i = 0; i < NCDs; i++)
                if (strcmp(cds[i].artist, temp) == 0)
                    cds[i].print();
            break;
        case 7:
            sortCDsByYear(cds, NCDs);
            cout << "Sorted by year.\n";
            break;
        default:
            cout << "Invalid option!\n";
        }
    } while (menu != 0);

    fopen_s(&file, "cd_store.txt", "w");
    if (file != nullptr) {
        fprintf(file, "%d\n", NCDs);
        for (int i = 0; i < NCDs; i++)
            cds[i].saveToTextFile(file);
        fclose(file);
    }
    delete[] cds;
    cout << "Saved!\n";
    return 0;
}
