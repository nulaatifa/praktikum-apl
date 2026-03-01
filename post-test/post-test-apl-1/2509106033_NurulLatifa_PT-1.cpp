#include <iostream>
#include <string>
using namespace std;

int main() {
    string nama_input;
    string password_input;
    string nama_benar = "Nurul Latifa";
    string password_benar = "033";
    int jumlah_percobaan = 0;
    bool status_login = false;

    cout << "==============================" << endl;
    cout << "      KONVERSI SATUAN PANJANG " << endl;
    cout << "==============================" << endl;
    cout << "  Menu Login" << endl;
    cout << "------------------------------" << endl;

    
    while (jumlah_percobaan < 3 && status_login == false) {
        cout << "Nama     : ";
        getline(cin, nama_input);
        cout << "Password : ";
        getline(cin, password_input);

        if (nama_input == nama_benar && password_input == password_benar) {
            status_login = true;
        } else {
            jumlah_percobaan++;
            if (jumlah_percobaan < 3) {
                cout << "------------------------------" << endl;
                cout << "  Login gagal! Sisa: " << (3 - jumlah_percobaan) << "x percobaan" << endl;
                cout << "------------------------------" << endl;
            }
        }
    }

    if (status_login == false) {
        cout << "==============================" << endl;
        cout << "  Login gagal 3x. Berhenti." << endl;
        cout << "==============================" << endl;
        return 0;
    }

    cout << "==============================" << endl;
    cout << "  Selamat datang, " << nama_input << "!" << endl;
    cout << "==============================" << endl;

    int pilihan_menu;
    double nilai_panjang;

    do {
        cout << endl;
        cout << "==============================" << endl;
        cout << "    MENU KONVERSI PANJANG     " << endl;
        cout << "==============================" << endl;
        cout << "  1. Meter    -> Km & Cm" << endl;
        cout << "  2. Kilometer -> M & Cm" << endl;
        cout << "  3. Centimeter-> M & Km" << endl;
        cout << "  4. Keluar" << endl;
        cout << "------------------------------" << endl;
        cout << "  Pilihan (1-4): ";
        cin >> pilihan_menu;
        cout << "------------------------------" << endl;

        switch (pilihan_menu) {
            case 1:
                cout << "  Masukkan nilai Meter : ";
                cin >> nilai_panjang;
                cout << "------------------------------" << endl;
                cout << "  " << nilai_panjang << " M = " << nilai_panjang / 1000 << " Km" << endl;
                cout << "  " << nilai_panjang << " M = " << nilai_panjang * 100 << " Cm" << endl;
                cout << "==============================" << endl;
                break;

            case 2:
                cout << "  Masukkan nilai Kilometer : ";
                cin >> nilai_panjang;
                cout << "------------------------------" << endl;
                cout << "  " << nilai_panjang << " Km = " << nilai_panjang * 1000 << " M" << endl;
                cout << "  " << nilai_panjang << " Km = " << nilai_panjang * 100000 << " Cm" << endl;
                cout << "==============================" << endl;
                break;

            case 3:
                cout << "  Masukkan nilai Centimeter : ";
                cin >> nilai_panjang;
                cout << "------------------------------" << endl;
                cout << "  " << nilai_panjang << " Cm = " << nilai_panjang / 100 << " M" << endl;
                cout << "  " << nilai_panjang << " Cm = " << nilai_panjang / 100000 << " Km" << endl;
                cout << "==============================" << endl;
                break;

            case 4:
                cout << "  Terima kasih! Sampai jumpa." << endl;
                cout << "==============================" << endl;
                break;

            default:
                cout << "  Pilihan tidak valid! Masukkan 1-4." << endl;
                cout << "==============================" << endl;
        }

    } while (pilihan_menu != 4);

    return 0;
}