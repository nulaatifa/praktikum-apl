#ifndef VALIDASI_H
#define VALIDASI_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

void validasiTidakKosong(string teks, string nama_field) {
    if (teks.empty()) {
        throw invalid_argument(nama_field + " tidak boleh kosong!");
    }
}

void validasiRentangInt(int nilai, int batas_bawah, int batas_atas, string nama_field) {
    if (nilai < batas_bawah || nilai > batas_atas) {
        throw out_of_range(nama_field + " harus antara " + to_string(batas_bawah) + " dan " + to_string(batas_atas) + "!");
    }
}

void validasiMinInt(int nilai, int batas_bawah, string nama_field) {
    if (nilai < batas_bawah) {
        throw invalid_argument(nama_field + " minimal " + to_string(batas_bawah) + "!");
    }
}

void validasiInputCin() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw runtime_error("Input harus berupa angka!");
    }
}

#endif