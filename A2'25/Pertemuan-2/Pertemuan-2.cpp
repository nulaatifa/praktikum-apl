#include <iostream>
using namespace std;

// #define MAX_MAHASISWA 100 // Ukuran maksimum array

// int main() {

//     int panjang = 0; // Jumlah data mahasiswa saat ini
//     string mahasiswa[MAX_MAHASISWA]; // Array 1 dimensi

//     int pilihan, index;

//     do {
//         cout << "\n=== MENU PROGRAM DATA MAHASISWA ===" << endl;
//         cout << "1. Tampilkan Mahasiswa" << endl;
//         cout << "2. Tambah Mahasiswa" << endl;
//         cout << "3. Ubah Mahasiswa" << endl;
//         cout << "4. Hapus Mahasiswa" << endl;
//         cout << "5. Keluar" << endl;
//         cout << "Pilihan: ";
//         cin >> pilihan;

//         switch (pilihan) {

//         case 1: // READ
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }
//             }
//             break;

//         case 2: // CREATE
//             if (panjang < MAX_MAHASISWA) {
//                 cout << "Masukkan nama mahasiswa: ";
//                 cin.ignore();
//                 getline(cin, mahasiswa[panjang]);
//                 panjang++;
//                 cout << "Mahasiswa berhasil ditambahkan." << endl;
//             } else {
//                 cout << "Kapasitas penuh!" << endl;
//             }
//             break;

//         case 3: // UPDATE
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa untuk diubah." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }

//                 cout << "Masukkan nomor mahasiswa yang akan diubah: ";
//                 cin >> index;

//                 if (index > 0 && index <= panjang) {
//                     cout << "Masukkan nama baru: ";
//                     cin.ignore();
//                     getline(cin, mahasiswa[index - 1]);
//                     cout << "Data berhasil diubah." << endl;
//                 } else {
//                     cout << "Nomor tidak valid." << endl;
//                 }
//             }
//             break;

//         case 4: // DELETE
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa untuk dihapus." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }

//                 cout << "Masukkan nomor mahasiswa yang akan dihapus: ";
//                 cin >> index;

//                 if (index > 0 && index <= panjang) {
//                     for (int i = index - 1; i < panjang - 1; i++) {
//                         mahasiswa[i] = mahasiswa[i + 1]; 
//                     }
//                     panjang--;
//                     cout << "Mahasiswa berhasil dihapus." << endl;
//                 } else {
//                     cout << "Nomor tidak valid." << endl;
//                 }
//             }
//             break;

//         case 5:
//             cout << "Program selesai." << endl;
//             break;

//         default:
//             cout << "Pilihan tidak valid." << endl;
//         }

//     } while (pilihan != 5);

//     return 0;
// }

// int main(){
//     int matriks[3][3] = {
//         {1, 2, 3},
//         {4, 5, 6},
//         {7, 8, 9} 
//     };

//     cout << matriks[0][1] << endl;
//     cout << matriks[2][0] << endl;

//     for (int i = 0; i < 3; i ++) { 
//         for (int j = 0; j < 3; j ++) { 
//              cout << matriks[i][j] << " ";
//         }
//         cout << endl;
//     }
//     for (auto &baris : matriks) { 
//         for (auto &elemen : baris) { 
//             cout << elemen << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }

// int main() {
// int nilai[2][2][2] = {
// { {80, 85}, {75, 90} }, 
// { {88, 92}, {70, 78} } 
// };
// cout << " = DATA NILAI MAHASISWA =\n\n";
// for (int k = 0; k < 2; k++) {
// cout << "Kelas " << char('A' + k) << endl;
// for (int m = 0; m < 2; m++) {
// cout << " Mahasiswa " << m + 1 << endl;
// cout << " UTS : " << nilai[k][m][0] << endl;
// cout << " UAS : " << nilai[k][m][1] << endl;
// }
// cout << endl;
// }
// return 0;
// }


//struck
 
struct Alamat {
    string jalan;
    int    nomor;
    string kota;
};
 
struct Mahasiswa {
    string nama;
    int    umur;
    string jurusan;
    Alamat alamat;
};
 
#define MAX_MAHASISWA 100
int panjang = 0;
Mahasiswa mhs[MAX_MAHASISWA];
 
int main() {
    int pilihan, index;
    
    do {
        cout << "==============================" << endl;
        cout << "   Menu Manajemen Mahasiswa  " << endl;
        cout << "==============================" << endl;
        cout << "1. Tampilkan Data Mahasiswa"  << endl;
        cout << "2. Tambah Data Mahasiswa"     << endl;
        cout << "3. Ubah Data Mahasiswa"       << endl;
        cout << "4. Hapus Data Mahasiswa"      << endl;
        cout << "5. Keluar"                    << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            
        case 1: // READ
            if (panjang == 0) {
                cout << "Belum ada data mahasiswa." << endl;
            } else {
                cout << "Daftar Mahasiswa:" << endl;
                cout << "================================" << endl;
                for (int i = 0; i < panjang; i++) {
                    cout << "Mahasiswa ke-" << i + 1 << endl;
                    cout << "Nama    : " << mhs[i].nama    << endl;
                    cout << "Umur    : " << mhs[i].umur    << endl;
                    cout << "Jurusan : " << mhs[i].jurusan << endl;
                    cout << "Alamat  : " << mhs[i].alamat.jalan
                         << " No. " << mhs[i].alamat.nomor
                         << ", "    << mhs[i].alamat.kota << endl;
                    cout << "--------------------------------" << endl;
                }
            }
            break;
            
        case 2: // CREATE
            if (panjang < MAX_MAHASISWA) {
                cin.ignore();
                cout << "Masukkan nama     : ";
                getline(cin, mhs[panjang].nama);
                
                cout << "Masukkan umur     : ";
                cin >> mhs[panjang].umur;
                
                cin.ignore();
                cout << "Masukkan jurusan  : ";
                getline(cin, mhs[panjang].jurusan);
                
                cout << "--- Alamat ---" << endl;
                cout << "Jalan : ";
                getline(cin, mhs[panjang].alamat.jalan);
                
                cout << "Nomor : ";
                cin >> mhs[panjang].alamat.nomor;
                
                cin.ignore();
                cout << "Kota  : ";
                getline(cin, mhs[panjang].alamat.kota);
                
                panjang++;
                cout << "Data berhasil ditambahkan!" << endl;
            } else {
                cout << "Kapasitas penuh!" << endl;
            }
            break;
            
        case 3: // UPDATE
            if (panjang == 0) {
                cout << "Belum ada mahasiswa untuk diubah." << endl;
            } else {
                cout << "Daftar Mahasiswa" << endl;
                cout << "==================" << endl;
                for (int i = 0; i < panjang; i++) {
                    cout << i + 1 << ". " << mhs[i].nama << endl;
                }
                
                cout << "Masukkan nomor mahasiswa yang akan diubah: ";
                cin >> index;
                
                if (index > 0 && index <= panjang) {
                    cin.ignore();
                    cout << "Masukkan nama mahasiswa baru: ";
                    getline(cin, mhs[index - 1].nama);
                    
                    cout << "Masukkan umur mahasiswa baru: ";
                    cin >> mhs[index - 1].umur;
                    
                    cin.ignore();
                    cout << "Masukkan jurusan mahasiswa baru: ";
                    getline(cin, mhs[index - 1].jurusan);
                    
                    cout << "Masukkan alamat mahasiswa baru:" << endl;
                    cout << "Jalan: ";
                    getline(cin, mhs[index - 1].alamat.jalan);
                    
                    cout << "Nomor: ";
                    cin >> mhs[index - 1].alamat.nomor;
                    
                    cin.ignore();
                    cout << "Kota: ";
                    getline(cin, mhs[index - 1].alamat.kota);
                    
                    cout << "Mahasiswa berhasil diubah" << endl;
                } else {
                    cout << "Nomor mahasiswa tidak valid" << endl;
                }
            }
            break;
            
        case 4: // DELETE
            if (panjang == 0) {
                cout << "Belum ada mahasiswa untuk dihapus." << endl;
            } else {
                cout << "Daftar Mahasiswa" << endl;
                cout << "==================" << endl;
                for (int i = 0; i < panjang; i++) {
                    cout << i + 1 << ". " << mhs[i].nama << endl;
                }
                
                cout << "Masukkan nomor mahasiswa yang akan dihapus: ";
                cin >> index;
                
                if (index > 0 && index <= panjang) {
                    for (int i = index - 1; i < panjang - 1; i++) {
                        mhs[i] = mhs[i + 1];
                    }
                    panjang--;
                    cout << "Mahasiswa berhasil dihapus" << endl;
                } else {
                    cout << "Nomor mahasiswa tidak valid" << endl;
                }
            }
            break;
            
        case 5:
            cout << "Sampai jumpa!" << endl;
            break;
            
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
        
    } while (pilihan != 5);
    
    return 0;
}