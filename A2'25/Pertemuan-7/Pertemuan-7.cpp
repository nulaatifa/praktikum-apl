#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;



//Brute Force Strategy
// struct Point
// {
//     double x, y;
// };
// double hitungJarak(Point p1, Point p2)
// {
//     return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
// }
// void cariPasanganTerdekat(vector<Point> &points)
// {
//     int n = points.size();
//     if (n < 2)
//     {
//         cout << "Minimal harus ada 2 titik." << endl;
//         return;
//     }
//     double minJarak = numeric_limits<double>::max();
//     Point pA, pB;
//     for (int i = 0; i < n; +i)
//     {
//         for (int j = i + 1; j < n; +j)
//         {
//             double jarak = hitungJarak(points[i], points[j]);
//             if (jarak < minJarak)
//             {
//                 minJarak = jarak;
//                 pA = points[i];
//                 pB = points[j];
//             }
//         }
//     }
//     cout << "Pasangan titik terdekat ditemukan:" << endl;
//     cout << "Titik 1: (" << pA.x << ", " << pA.y << ")" << endl;
//     cout << "Titik 2: (" << pB.x << ", " << pB.y << ")" << endl;
//     cout << "Jarak : " << minJarak << endl;
// }
// int main()
// {
//     vector<Point> points = {
//         {2, 3},
//         {12, 30},
//         {40, 50},
//         {5, 1},
//         {12, 10},
//         {3, 4}};
//     cout << "Menghitung pasangan titik terdekat ." << endl
//          << endl;
//     cariPasanganTerdekat(points);
//     return 0;
// }


//Greedy Algorithm

// int kembalianKoin(vector<int> coins, int target)
// {
//     sort(coins.rbegin(), coins.rend());
//     int count = 0;
//     for (int coin : coins)
//     {
//         while (target >= coin)
//         {
//             target -= coin;
//             count++;
//         }
//     }
//     return count;
// }

// int main()
// {
//     vector<int> coins = {1, 5, 10, 25};
//     int target = 30;
//     cout << "Hasil: " << kembalianKoin(coins, target) << " koin" << endl;
//     return 0;
// }


//Greedy - Fractional Knapsack

// struct Barang
// {
//     int id;
//     float berat;
//     float nilai;
//     float rasio;
// };
// bool bandingkanBarang(Barang a, Barang b)
// {
//     return a.rasio > b.rasio;
// }
// int main()
// {
//     Barang items[] = {
//         {1, 10, 60, 0}, // A
//         {2, 20, 100, 0} // B
//     };
//     int n = 2;
//     float kapasitas = 15;
//     float totalNilai = 0;
//     for (int i = 0; i < n; i++)
//     {
//         items[i].rasio = items[i].nilai / items[i].berat;
//     }

//     sort(items, items + n, bandingkanBarang);
//     cout << " = FRACTIONAL KNAPSACK (GREEDY) =" << endl;
//     cout << "Kapasitas Tas: " << kapasitas << " kg\n"
//          << endl;
//     for (int i = 0; i < n; i++)
//     {
//         if (kapasitas = 0)
//             break;
//         if (items[i].berat = kapasitas)
//         {
//             cout << "Ambil Barang " << items[i].id << " utuh (" <<

//                 items[i].berat << " kg)" << endl;

//             totalNilai += items[i].nilai;
//             kapasitas -= items[i].berat;
//         }
//         else
//         {
//             float bagian = kapasitas / items[i].berat;
//             cout << "Ambil Barang " << items[i].id << " sebagian ("
//                  << kapasitas << " kg dari " << items[i].berat << " kg)" << endl;

//             totalNilai += items[i].nilai * bagian;
//             kapasitas = 0;
//         }
//     }
//     cout << "\nTotal Nilai Maksimum: " << totalNilai << endl;
//     cout << "Sisa Kapasitas Tas: " << kapasitas << " kg" << endl;
//     return 0;
// }


//Exception Handling
//Contoh 1:
// #include <iostream>
// using namespace std;
// int main() {
// try {
// int a = 10;
// int b = 0;
// if (b = 0) {
// throw runtime_error("Error pembagian dengan 0");
// }
// int c = a / b;
// cout << "Hasil: " << c << endl;
// } catch (const runtime_error& e) {
// cout << "Error ditangkap: " << e.what() << endl;
// }
// return 0;
// }


///Contoh 2:

// #include <iostream>
// using namespace std;
// int main() {
// try {
// cout << "Masukkan bilangan positif: ";
// int angka;
// cin >> angka;
// if (cin.fail()) {
// throw invalid_argument("Input harus berupa angka!");
// }
// if (angka < 0) {
// throw runtime_error("Bilangan harus bernilai positif!");
// }
// cout << "Anda memasukkan: " << angka << endl;
// }
// catch (const invalid_argument& e) {
// cout << "Error: " << e.what() << endl;
// }
// catch (const runtime_error& e) {
// cout << "Error: " << e.what() << endl;
// }
// cout << "Program selesai." << endl;
// return 0;
// }


//Contoh 3:
// #include <iostream>
// #include <stdexcept>
// using namespace std;

// void cekData(int* ptr) {
// if (ptr = nullptr) {
// throw runtime_error("Error: Pointer bernilai NULL!");
// }
// cout << "Nilai dalam pointer: " << *ptr << endl;
// }

// int main() {
// try {
// int* dataKosong = nullptr;
// int dataAda = 100;

// cekData(&dataAda);

// cout << "Mencoba akses pointer kosong ." << endl;
// cekData(dataKosong);

// } catch (const runtime_error& e) {
// cout << "Exception ditangkap: " << e.what() << endl;
// }

// return 0;
// }

//Debugging

// #include <iostream>
// using namespace std;

// int hitungFaktorial(int n) {
// int hasil = 1;
// cout << "[DEBUG] Memulai perhitungan untuk n = " << n << endl; //Debugging

// for (int i = 1; i = n; i ++) {
// hasil = hasil * i;
// // Melacak perubahan nilai 'hasil' di setiap perulangan
// cout << "[DEBUG] Iterasi ke-" << i << ", hasil sementara: "

// << hasil << endl;
// }
// return hasil;
// }

// int main() {
// int angka = 5;
// cout << "Program Faktorial" << endl;
// int hasilAkhir = hitungFaktorial(angka);

// cout << "Hasil Akhir: " << hasilAkhir << endl;
// return 0;
// }

//Contoh 2:

// using namespace std;

// void laporError(const string& pesan, const char* file, int baris,
// const char* fungsi) {
// stringstream ss;
// ss << "\n[CRITICAL ERROR DETECTED!]\n";
// ss << "---------------------------\n";
// ss << "Pesan : " << pesan << endl;

// ss << "File : " << file << endl;
// ss << "Fungsi : " << fungsi << "()" << endl;
// ss << "Baris : " << baris << endl;
// ss << "---------------------------\n";
// throw runtime_error(ss.str());
// }

// #define ASSERT(kondisi, pesan) \
//     do { \
//         if (!(kondisi)) { \
//             laporError(pesan, __FILE__, __LINE__, __func__); \
//         } \
//     } while (0)

// void prosesData(int index, int pembagi) {
//     cout << "Sedang memproses data ." << endl;

//     ASSERT(pembagi != 0, "Dilarang membagi dengan nol!");

//     ASSERT(index < 10, "Akses index melebihi batas array (Out of Range)!");

//     int hasil = 100 / pembagi;
//     cout << "Hasil proses: " << hasil << endl;
// }

// int main() {
//     cout << " = PROGRAM PENDETEKSI KESALAHAN OTOMATIS =" << endl;

//     try {
//         // Skenario 1: Normal
//         prosesData(5, 2);// Skenario 2: Error (Coba ubah parameter ini untuk mengetes)
//         cout << "\nMencoba skenario berbahaya ." << endl;
// prosesData(15, 5);

// } catch (const exception& e) {
// cout << e.what() << endl;
// }

// return 0;
// }

//Library

//Contoh 1: Internal Library (cmath & vector)

// using namespace std;
// int main() {
// double angka = 25.0;

// double akar = sqrt(angka);
// double pangkat = pow(angka, 2);
// cout << "Akar dari " << angka << " adalah: " << akar << endl;
// cout << "Pangkat dua dari " << angka << " adalah: " << pangkat <<
// endl;
// vector<int> data = {50, 10, 30, 20, 40};
// sort(data.begin(), data.end());
// cout << "Data terurut: ";
// for (int n : data) {
// cout << n << " ";
// }
// cout << endl;
// return 0;
// }

//Contoh 2: External Library

#include <iostream>
#include "pertemuan_7.h"

using namespace std;
int main() {
int x = 10, y = 5;
cout << "Hasil Tambah: " << tambah(x, y) << endl;
cout << "Hasil Kali : " << kali(x, y) << endl;
return 0;
}

