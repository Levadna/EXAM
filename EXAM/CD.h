#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

struct RentalInfo {
    char fullName[100] = "";
    char address[100] = "";
    char phone[20] = "";
    char rentDate[20] = "";
    char returnDate[20] = "";
};

struct CD {
    char title[100] = "";
    char artist[100] = "";
    int year = 0;
    double price = 0;
    bool isRented = false;
    RentalInfo rental;

    void fill() {
        cout << "Enter title: ";
        cin.getline(title, 100);
        cout << "Enter artist: ";
        cin.getline(artist, 100);
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter price: ";
        cin >> price;
        isRented = false;
    }

    void print() {
        cout << "Title: " << title << ", Artist: " << artist << ", Year: " << year << ", Price: " << price << "\n";
        if (isRented == true) {
            cout << "  Rented to: " << rental.fullName << ", Until: " << rental.returnDate << "\n";
        }
    }

    void rent() {
        cout << "Enter full name: ";
        cin.getline(rental.fullName, 100);
        cout << "Enter address: ";
        cin.getline(rental.address, 100);
        cout << "Enter phone: ";
        cin.getline(rental.phone, 20);
        cout << "Enter rent date: ";
        cin.getline(rental.rentDate, 20);
        cout << "Enter return date: ";
        cin.getline(rental.returnDate, 20);
        isRented = true;
    }

    void returnCD() {
        isRented = false;
    }

    void saveToTextFile(FILE* file) {
        fprintf(file, "%s\n%s\n%d %lf %d\n", title, artist, year, price, isRented);
        if (isRented == true) {
            fprintf(file, "%s\n%s\n%s\n%s\n%s\n",
                rental.fullName, rental.address, rental.phone,
                rental.rentDate, rental.returnDate);
        }
    }

    void loadFromTextFile(FILE* file) {
        fgets(title, 100, file); title[strcspn(title, "\n")] = 0;
        fgets(artist, 100, file); artist[strcspn(artist, "\n")] = 0;
        fscanf_s(file, "%d %lf %d\n", &year, &price, &isRented);
        if (isRented == 1) {
            fgets(rental.fullName, 100, file); rental.fullName[strcspn(rental.fullName, "\n")] = 0;
            fgets(rental.address, 100, file); rental.address[strcspn(rental.address, "\n")] = 0;
            fgets(rental.phone, 20, file); rental.phone[strcspn(rental.phone, "\n")] = 0;
            fgets(rental.rentDate, 20, file); rental.rentDate[strcspn(rental.rentDate, "\n")] = 0;
            fgets(rental.returnDate, 20, file); rental.returnDate[strcspn(rental.returnDate, "\n")] = 0;
        }
    }
};

void sortCDsByYear(CD* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i].year > arr[j].year) {
                CD temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
