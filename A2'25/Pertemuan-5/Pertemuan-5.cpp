#include <iostream>
#include <utility>
using namespace std;

// // Inisialisasi Array Global
// int arr[] = {64, 34, 25, 12, 22, 11, 90};
// int n = sizeof(arr) / sizeof(arr[0]);

// void bubbleSort(int arr[], int n) {
//     bool swapped;
//     // Loop luar untuk jumlah lintasan (pass)
//     for (int i = 0; i < n - 1; i++) {
//         swapped = false;
//         // Loop dalam untuk membandingkan elemen yang bersebelahan
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 // Tukar elemen jika elemen kiri lebih besar dari kanan
//                 swap(arr[j], arr[j + 1]);
//                 swapped = true;
//             }
//         }
//         // Optimasi: Jika tidak ada pertukaran, berarti array sudah urut
//         if (!swapped)
//             break;
//     }
// }

// void tampilkanArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }

// int main() {
//     cout << "Data Sebelum Bubble Sort: ";
//     tampilkanArray(arr, n);
//     bubbleSort(arr, n);
//     cout << "Data Setelah Bubble Sort : ";
//     tampilkanArray(arr, n);
//     return 0;
// }


// Inisialisasi Array Global
// int arr[] = {29, 10, 14, 37, 13};
// int n = sizeof(arr) / sizeof(arr[0]);

// void selectionSort(int arr[], int n) {
//     // Loop luar untuk memindahkan batas sub-array yang belum urut
//     for (int i = 0; i < n - 1; i++) {
//         // Anggap elemen pertama dari bagian belum urut sebagai yang terkecil
//         int indeksMin = i;

//         // Loop dalam untuk mencari elemen terkecil di sisa array
//         for (int j = i + 1; j < n; j++) {
//             if (arr[j] < arr[indeksMin]) {
//                 indeksMin = j; // Simpan indeks elemen yang lebih kecil
//             }
//         }

//         // Tukar elemen terkecil yang ditemukan dengan elemen di posisi i
//         if (indeksMin != i) {
//             swap(arr[i], arr[indeksMin]);
//         }
//     }
// }

// void tampilkanArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }

// int main() {
//     cout << "Sebelum Selection Sort: ";
//     tampilkanArray(arr, n);
//     selectionSort(arr, n);
//     cout << "Sesudah Selection Sort : ";
//     tampilkanArray(arr, n);
//     return 0;
// }




// // Array Global agar mudah diakses oleh semua fungsi
// int arr[] = {38, 27, 43, 3, 9, 82, 10, 55};
// int n = sizeof(arr) / sizeof(arr[0]);

// // Fungsi untuk menggabungkan dua sub-array yang sudah terbagi
// void merge(int arr[], int l, int m, int r) {
//     // Buat array temp dengan ukuran dinamis berdasarkan rentang
//     int temp[r - l + 1];

//     int i = l;      // Indeks awal sub-array kiri
//     int j = m + 1;  // Indeks awal sub-array kanan
//     int k = 0;      // Indeks awal array temp

//     // Bandingkan elemen kiri dan kanan, masukkan yang terkecil ke temp
//     while (i <= m && j <= r) {
//         if (arr[i] < arr[j]) {
//             temp[k] = arr[i];
//             i++;
//         } else {
//             temp[k] = arr[j];
//             j++;
//         }
//         k++;
//     }

//     // Jika sub-array kiri masih ada sisa, masukkan ke temp
//     while (i <= m) {
//         temp[k] = arr[i];
//         i++;
//         k++;
//     }

//     // Jika sub-array kanan masih ada sisa, masukkan ke temp
//     while (j <= r) {
//         temp[k] = arr[j];
//         j++;
//         k++;
//     }

//     // Salin kembali data dari temp ke array asli (arr)
//     for (int x = 0; x < k; x++) {
//         arr[l + x] = temp[x];
//     }
// }

// // Fungsi rekursif untuk membagi array (Divide)
// void mergeSort(int arr[], int l, int r) {
//     if (l < r) {
//         // Cari titik tengah
//         int m = l + (r - l) / 2;  // Mencegah overflow pada indeks besar

//         // Bagi terus sisi kiri dan kanan
//         mergeSort(arr, l, m);
//         mergeSort(arr, m + 1, r);

//         // Gabungkan kembali (Conquer & Combine)
//         merge(arr, l, m, r);
//     }
// }

// int main() {
//     cout << "Sebelum sorting: ";
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     // Panggil fungsi merge sort
//     mergeSort(arr, 0, n - 1);

//     cout << "Sesudah sorting: ";
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }



// Inisialisasi Array Global
// int arr[] = {3, 4, 2, 9, 8, 6, 5, 7};
// int n = sizeof(arr) / sizeof(arr[0]);

// void quickSort(int arr[], int low, int high) {
//     // Base case: jika pointer low melewati high, berhenti
//     if (low >= high) return;

//     // Menentukan data tengah sebagai pivot (Strategi yang lebih stabil)
//     int mid = low + (high - low) / 2;
//     int pivot = arr[mid];

//     int i = low, j = high;

//     // Proses Partisi (Hoare Partition Scheme)
//     while (i <= j) {
//         // Cari elemen di kiri yang >= pivot
//         while (arr[i] < pivot) {
//             i++;
//         }
//         // Cari elemen di kanan yang <= pivot
//         while (arr[j] > pivot) {
//             j--;
//         }
//         // Tukar elemen jika ditemukan posisi yang salah
//         if (i <= j) {
//             swap(arr[i], arr[j]);
//             i++;
//             j--;
//         }
//     }

//     // Rekursi untuk sub-array bagian kiri (dari low sampai j)
//     if (low < j) {
//         quickSort(arr, low, j);
//     }
//     // Rekursi untuk sub-array bagian kanan (dari i sampai high)
//     if (i < high) {
//         quickSort(arr, i, high);
//     }
// }

// int main() {
//     cout << "Data Belum Terurut: ";
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     // Memanggil fungsi Quick Sort
//     quickSort(arr, 0, n - 1);

//     cout << "Hasil Quick Sort : ";
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }



// // Struktur Data Buku
// struct Buku {
//     int idBuku;
//     string judul;
// };

// // Fungsi Insertion Sort
// void insertionSort(Buku rak[], int n) {
//     // Loop luar: mengambil buku satu per satu mulai dari buku kedua
//     for (int i = 1; i < n; i++) {
//         Buku key = rak[i];
//         int j = i - 1;

//         /* Loop dalam: Membandingkan 'key' dengan buku di kirinya.
//            Jika buku di kiri lebih besar, geser ke kanan. */
//         while (j >= 0 && rak[j].idBuku > key.idBuku) {
//             rak[j + 1] = rak[j];
//             j = j - 1;
//         }
//         // Sisipkan buku 'key' di posisi yang benar
//         rak[j + 1] = key;
//     }
// }

// void tampilkanRak(Buku rak[], int n) {
//     for (int i = 0; i < n; i++) {
//         cout << rak[i].idBuku << " | " << rak[i].judul << endl;
//     }
//     cout << endl;
// }

// int main() {
//     int n = 5;

//     // SCENARIO 1: BEST CASE (O(n))
//     // Data sudah urut, pustakawan hanya mengecek tanpa menggeser.
//     Buku rakUrut[] = {
//         {101, "Laskar Pelangi"},
//         {102, "Bumi Manusia"},
//         {103, "Negeri 5 Menara"},
//         {104, "Filosofi Teras"},
//         {105, "Hujan"}
//     };

//     cout << "=== BEST CASE (Data Terurut) ===" << endl;
//     cout << "Sebelum sort:" << endl;
//     tampilkanRak(rakUrut, n);
//     insertionSort(rakUrut, n);
//     cout << "Setelah sort:" << endl;
//     tampilkanRak(rakUrut, n);

//     // SCENARIO 2: WORST CASE (O(n^2))
//     // Data terbalik, setiap buku harus digeser sampai ke ujung kiri.
//     Buku rakTerbalik[] = {
//         {105, "Hujan"},
//         {104, "Filosofi Teras"},
//         {103, "Negeri 5 Menara"},
//         {102, "Bumi Manusia"},
//         {101, "Laskar Pelangi"}
//     };

//     cout << "=== WORST CASE (Data Terbalik) ===" << endl;
//     cout << "Sebelum sort:" << endl;
//     tampilkanRak(rakTerbalik, n);
//     insertionSort(rakTerbalik, n);
//     cout << "Setelah sort:" << endl;
//     tampilkanRak(rakTerbalik, n);

//     return 0;
// }
