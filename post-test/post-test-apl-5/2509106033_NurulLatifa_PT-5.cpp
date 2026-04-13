#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Studio {
    string nama_studio;
    string negara_studio;
};

struct Film {
    string kode_film;
    string judul_film;
    string genre_film;
    int    tahun_rilis;
    int    harga_sewa;
    Studio studio;
    bool   tersedia;
    
};

struct Pengguna {
    string nama_pengguna;
    string password_pengguna;
    string role_pengguna;
};

struct Tanggal {
    int hari;
    int bulan;
    int tahun;
};

struct DataSewa {
    int     id_sewa;
    string  password_penyewa;
    string  nama_penyewa;
    string  kode_film_sewa;
    string  judul_film_sewa;
    int     harga_per_hari;
    int     durasi_hari;
    Tanggal tanggal_sewa;
    Tanggal tanggal_kembali;
    int     total_bayar;
    int     denda;
    bool    sudah_kembali;
};

#define MAKS_FILM      50
#define MAKS_USER      20
#define MAKS_SEWA     100
#define DENDA_PER_HARI 5000

Film     daftar_film[MAKS_FILM];
int      jumlah_film = 0;

Pengguna daftar_user[MAKS_USER];
int      jumlah_user = 0;

DataSewa daftar_sewa[MAKS_SEWA];
int      jumlah_sewa   = 0;
int      id_berikutnya = 1;

string nama_aktif     = "";
string password_aktif = "";
string role_aktif     = "";

void inisialisasiData();
void menuLihatFilm();
void menuSewaFilm();
void menuKembalikanFilm();
void menuRiwayatSewa(string nama_pengguna, string password_pengguna);
void menuTambahFilm();
void menuEditFilm();
void menuHapusFilm();
void menuSemuaRiwayat();
void prosesRegister(string role_default);
void inputTanggal(int &hari, int &bulan, int &tahun);

bool prosesLogin(string &nama_hasil, string &password_hasil, string &role_hasil);
int  hitungTotalBayar(int harga_per_hari, int durasi_hari);
int  hitungDendaRekursif(int selisih_hari);
int  hitungDenda(int selisih_hari);
int  hitungDenda(int harga_per_hari, int selisih_hari);
int  cariFilm(string kode_film);
int  cariSewa(int id_sewa, string password_penyewa);
int  hitungSelisihHari(Tanggal tanggal_wajib, Tanggal tanggal_aktual);

void tampilDetailFilm(Film *penunjuk_film);
void simpanDataSewa(DataSewa *penunjuk_sewa, int id_baru, string kode_film,
                    string judul_film, int harga_hari, int durasi,
                    Tanggal tgl_sewa, Tanggal tgl_kembali, int total);

void sortingJudul();
void sortingHarga();
void sortingTahun();

void sortingJudul() {
    Film film_tukar;
    bool sudah_urut;
    for (int i = 0; i < jumlah_film - 1; i++) {
        sudah_urut = false;
        for (int j = 0; j < jumlah_film - i - 1; j++) {
            if (daftar_film[j].judul_film > daftar_film[j + 1].judul_film) {
                film_tukar         = daftar_film[j];
                daftar_film[j]     = daftar_film[j + 1];
                daftar_film[j + 1] = film_tukar;
                sudah_urut         = true;
            }
        }
        if (!sudah_urut) break;
    }
}

void sortingHarga() {
    int  indeks_terbesar;
    Film film_tukar;
    for (int i = 0; i < jumlah_film - 1; i++) {
        indeks_terbesar = i;
        for (int j = i + 1; j < jumlah_film; j++) {
            if (daftar_film[j].harga_sewa > daftar_film[indeks_terbesar].harga_sewa) {
                indeks_terbesar = j;
            }
        }
        if (indeks_terbesar != i) {
            film_tukar                   = daftar_film[i];
            daftar_film[i]               = daftar_film[indeks_terbesar];
            daftar_film[indeks_terbesar] = film_tukar;
        }
    }
}

void sortingTahun() {
    Film film_kunci;
    int  j;
    for (int i = 1; i < jumlah_film; i++) {
        film_kunci = daftar_film[i];
        j          = i - 1;
        while (j >= 0 && daftar_film[j].tahun_rilis > film_kunci.tahun_rilis) {
            daftar_film[j + 1] = daftar_film[j];
            j                  = j - 1;
        }
        daftar_film[j + 1] = film_kunci;
    }
}

int hitungDendaRekursif(int selisih_hari) {
    if (selisih_hari <= 0) return 0;
    return DENDA_PER_HARI + hitungDendaRekursif(selisih_hari - 1);
}

int hitungTotalBayar(int harga_per_hari, int durasi_hari) {
    return harga_per_hari * durasi_hari;
}

int hitungDenda(int selisih_hari) {
    if (selisih_hari <= 0) return 0;
    return hitungDendaRekursif(selisih_hari);
}

int hitungDenda(int harga_per_hari, int selisih_hari) {
    if (selisih_hari <= 0) return 0;
    return selisih_hari * harga_per_hari;
}

int cariFilm(string kode_film) {
    for (int i = 0; i < jumlah_film; i++) {
        if (daftar_film[i].kode_film == kode_film) return i;
    }
    return -1;
}

int cariSewa(int id_sewa, string password_penyewa) {
    for (int i = 0; i < jumlah_sewa; i++) {
        if (daftar_sewa[i].id_sewa == id_sewa &&
            daftar_sewa[i].password_penyewa == password_penyewa &&
            !daftar_sewa[i].sudah_kembali) return i;
    }
    return -1;
}

int hitungSelisihHari(Tanggal tanggal_wajib, Tanggal tanggal_aktual) {
    int total_wajib  = tanggal_wajib.tahun  * 365 + tanggal_wajib.bulan  * 30 + tanggal_wajib.hari;
    int total_aktual = tanggal_aktual.tahun * 365 + tanggal_aktual.bulan * 30 + tanggal_aktual.hari;
    return total_aktual - total_wajib;
}

void inputTanggal(int &hari, int &bulan, int &tahun) {
    do {
        cout << "  Hari  (1-31) : "; cin >> hari;
        if (hari < 1 || hari > 31) cout << "  [!] Hari tidak valid, masukkan 1-31." << endl;
    } while (hari < 1 || hari > 31);

    do {
        cout << "  Bulan (1-12) : "; cin >> bulan;
        if (bulan < 1 || bulan > 12) cout << "  [!] Bulan tidak valid, masukkan 1-12." << endl;
    } while (bulan < 1 || bulan > 12);

    do {
        cout << "  Tahun        : "; cin >> tahun;
        if (tahun < 2000) cout << "  [!] Tahun tidak valid, masukkan >= 2000." << endl;
    } while (tahun < 2000);
}

void tampilDetailFilm(Film *penunjuk_film) {
    cout << "  +------------------------------------------+" << endl;
    cout << "  | DETAIL FILM                              |" << endl;
    cout << "  +------------------------------------------+" << endl;
    cout << "  Kode        : " << (*penunjuk_film).kode_film            << endl;
    cout << "  Judul       : " << (*penunjuk_film).judul_film           << endl;
    cout << "  Genre       : " << (*penunjuk_film).genre_film           << endl;
    cout << "  Tahun Rilis : " << (*penunjuk_film).tahun_rilis          << endl;
    cout << "  Harga/Hari  : Rp" << (*penunjuk_film).harga_sewa        << endl;
    cout << "  Studio      : " << (*penunjuk_film).studio.nama_studio   << endl;
    cout << "  Negara      : " << (*penunjuk_film).studio.negara_studio << endl;
    cout << "  Status      : " << ((*penunjuk_film).tersedia ? "Tersedia" : "Sedang Disewa") << endl;
    cout << "  +------------------------------------------+" << endl;
}

void simpanDataSewa(DataSewa *penunjuk_sewa, int id_baru, string kode_film,
                    string judul_film, int harga_hari, int durasi,
                    Tanggal tgl_sewa, Tanggal tgl_kembali, int total) {
    (*penunjuk_sewa).id_sewa          = id_baru;
    (*penunjuk_sewa).password_penyewa = password_aktif;
    (*penunjuk_sewa).nama_penyewa     = nama_aktif;
    (*penunjuk_sewa).kode_film_sewa   = kode_film;
    (*penunjuk_sewa).judul_film_sewa  = judul_film;
    (*penunjuk_sewa).harga_per_hari   = harga_hari;
    (*penunjuk_sewa).durasi_hari      = durasi;
    (*penunjuk_sewa).tanggal_sewa     = tgl_sewa;
    (*penunjuk_sewa).tanggal_kembali  = tgl_kembali;
    (*penunjuk_sewa).total_bayar      = total;
    (*penunjuk_sewa).denda            = 0;
    (*penunjuk_sewa).sudah_kembali    = false;
}

void inisialisasiData() {
    daftar_user[0] = {"Admin", "000",        "Admin"};
    daftar_user[1] = {"Nurul", "2509106033", "User"};
    jumlah_user = 2;

    daftar_film[0]  = {"F001", "The Nun II",               "Horror",    2023, 12000, {"Warner Bros", "Amerika"}, true};
    daftar_film[1]  = {"F002", "Hereditary",               "Horror",    2018, 12000, {"A24",         "Amerika"}, true};
    daftar_film[2]  = {"F003", "It (2017)",                "Horror",    2017, 12000, {"Warner Bros", "Amerika"}, true};
    daftar_film[3]  = {"F004", "Talk to Me",               "Horror",    2023, 12000, {"A24",         "Amerika"}, true};
    daftar_film[4]  = {"F005", "Your Name",                "Romance",   2016, 10000, {"Toho",        "Jepang"},  true};
    daftar_film[5]  = {"F006", "To All The Boys",          "Romance",   2018, 10000, {"Netflix",     "Amerika"}, true};
    daftar_film[6]  = {"F007", "Five Feet Apart",          "Romance",   2019, 10000, {"Warner Bros", "Amerika"}, true};
    daftar_film[7]  = {"F008", "A Silent Voice",           "Romance",   2016, 10000, {"Toho",        "Jepang"},  true};
    daftar_film[8]  = {"F009", "The Dark Knight",          "Action",    2008, 13000, {"Warner Bros", "Amerika"}, true};
    daftar_film[9]  = {"F010", "John Wick",                "Action",    2014, 13000, {"Lionsgate",   "Amerika"}, true};
    daftar_film[10] = {"F011", "Mad Max: Fury Road",       "Action",    2015, 13000, {"Warner Bros", "Amerika"}, true};
    daftar_film[11] = {"F012", "Demon Slayer: Mugen",      "Action",    2020, 13000, {"Toho",        "Jepang"},  true};
    daftar_film[12] = {"F013", "Saltburn",                 "Thriller",  2023, 12000, {"A24",         "Amerika"}, true};
    daftar_film[13] = {"F014", "Gone Girl",                "Thriller",  2014, 12000, {"Warner Bros", "Amerika"}, true};
    daftar_film[14] = {"F015", "Bird Box",                 "Thriller",  2018, 12000, {"Netflix",     "Amerika"}, true};
    daftar_film[15] = {"F016", "Midsommar",                "Thriller",  2019, 12000, {"A24",         "Amerika"}, true};
    daftar_film[16] = {"F017", "Super Mario Bros Movie",   "Comedy",    2023, 10000, {"Nintendo",    "Amerika"}, true};
    daftar_film[17] = {"F018", "Puss in Boots 2",          "Comedy",    2022, 10000, {"DreamWorks",  "Amerika"}, true};
    daftar_film[18] = {"F019", "How To Train Your Dragon", "Animation", 2014, 10000, {"DreamWorks",  "Amerika"}, true};
    daftar_film[19] = {"F020", "Spirited Away",            "Animation", 2001, 10000, {"Toho",        "Jepang"},  true};
    jumlah_film = 20;
}

void menuLihatFilm() {
    cout << "  Urutkan berdasarkan:"                 << endl;
    cout << "  1. Judul A-Z       (Bubble Sort)"     << endl;
    cout << "  2. Harga Tertinggi (Selection Sort)"  << endl;
    cout << "  3. Tahun Terlama   (Insertion Sort)"  << endl;
    cout << "  Pilihan : ";
    int pilihan_sort; cin >> pilihan_sort;

    if      (pilihan_sort == 1) sortingJudul();
    else if (pilihan_sort == 2) sortingHarga();
    else if (pilihan_sort == 3) sortingTahun();
    else {
        cout << "  [!] Pilihan tidak valid, masukkan 1-3." << endl;
        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get(); return;
    }

    cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;
    cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr | Status  |" << endl;
    cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;
    for (int i = 0; i < jumlah_film; i++) {
        string status_film = daftar_film[i].tersedia ? "Tersedia" : "Disewa  ";
        string harga_str   = "Rp" + to_string(daftar_film[i].harga_sewa);
        cout << "| " << left << setw(5)  << daftar_film[i].kode_film
             << "| "         << setw(29) << daftar_film[i].judul_film
             << "| "         << setw(10) << daftar_film[i].genre_film
             << "| "         << setw(5)  << daftar_film[i].tahun_rilis
             << " | "        << setw(8)  << harga_str
             << "| "         << status_film << "|" << endl;
    }
    cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;

    string kode_detail;
    cout << "  Kode film untuk detail (Enter -> Kembali) : ";
    cin.ignore(); getline(cin, kode_detail);
    if (kode_detail != "") {
        int indeks_detail = cariFilm(kode_detail);
        if (indeks_detail == -1) {
            cout << "  [!] Film tidak ditemukan." << endl;
        } else {
            Film *penunjuk_film = &daftar_film[indeks_detail];
            tampilDetailFilm(penunjuk_film);
        }
        cin.get();
    }
}

void menuSewaFilm() {
    cout << "  === SEWA FILM ===" << endl;
    cout << "+-------+------------------------------+-----------+----------+" << endl;
    cout << "| Kode  | Judul                        | Genre     | Harga/Hr |" << endl;
    cout << "+-------+------------------------------+-----------+----------+" << endl;

    bool ada_tersedia = false;
    for (int i = 0; i < jumlah_film; i++) {
        if (!daftar_film[i].tersedia) continue;
        string harga_str = "Rp" + to_string(daftar_film[i].harga_sewa);
        cout << "| " << left << setw(5)  << daftar_film[i].kode_film
             << "| "         << setw(29) << daftar_film[i].judul_film
             << "| "         << setw(10) << daftar_film[i].genre_film
             << "| "         << setw(8)  << harga_str << "|" << endl;
        ada_tersedia = true;
    }
    cout << "+-------+------------------------------+-----------+----------+" << endl;

    if (!ada_tersedia) {
        cout << "  Semua film sedang disewa." << endl;
        cin.ignore(); cin.get(); return;
    }

    string kode_dipilih;
    cout << "  Kode film (Enter -> Kembali) : ";
    cin.ignore(); getline(cin, kode_dipilih);
    if (kode_dipilih == "") return;

    int indeks_film = cariFilm(kode_dipilih);
    if (indeks_film == -1 || !daftar_film[indeks_film].tersedia) {
        cout << "  [!] Film tidak ditemukan atau sedang disewa." << endl;
        cin.get(); return;
    }

    Tanggal tanggal_sewa;
    int durasi_hari;
    cout << "  Tanggal Sewa:" << endl;
    inputTanggal(tanggal_sewa.hari, tanggal_sewa.bulan, tanggal_sewa.tahun);
    do {
        cout << "  Durasi (hari, min 1) : "; cin >> durasi_hari;
        if (durasi_hari < 1) cout << "  [!] Durasi tidak valid, minimal 1 hari." << endl;
    } while (durasi_hari < 1);

    Tanggal tanggal_kembali = tanggal_sewa;
    int hari_per_bulan[13]  = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    tanggal_kembali.hari   += durasi_hari;
    while (tanggal_kembali.hari > hari_per_bulan[tanggal_kembali.bulan]) {
        tanggal_kembali.hari -= hari_per_bulan[tanggal_kembali.bulan];
        tanggal_kembali.bulan++;
        if (tanggal_kembali.bulan > 12) { tanggal_kembali.bulan = 1; tanggal_kembali.tahun++; }
    }

    int total_bayar_sewa = hitungTotalBayar(daftar_film[indeks_film].harga_sewa, durasi_hari);

    cout << "  Film          : " << daftar_film[indeks_film].judul_film << endl;
    cout << "  Tgl Sewa      : ";
    if (tanggal_sewa.hari   < 10) cout << "0"; cout << tanggal_sewa.hari   << "/";
    if (tanggal_sewa.bulan  < 10) cout << "0"; cout << tanggal_sewa.bulan  << "/" << tanggal_sewa.tahun  << endl;
    cout << "  Wajib Kembali : ";
    if (tanggal_kembali.hari  < 10) cout << "0"; cout << tanggal_kembali.hari  << "/";
    if (tanggal_kembali.bulan < 10) cout << "0"; cout << tanggal_kembali.bulan << "/" << tanggal_kembali.tahun << endl;
    cout << "  Total Bayar   : Rp" << total_bayar_sewa << endl;
    cout << "  Denda         : Rp" << DENDA_PER_HARI << "/hari jika terlambat" << endl;
    cout << "  Konfirmasi? (y/n) : ";
    char konfirmasi_sewa; cin >> konfirmasi_sewa;
    if (konfirmasi_sewa != 'y' && konfirmasi_sewa != 'Y') {
        cout << "  Dibatalkan." << endl; cin.ignore(); cin.get(); return;
    }

    daftar_film[indeks_film].tersedia = false;

    DataSewa *penunjuk_sewa = &daftar_sewa[jumlah_sewa];
    simpanDataSewa(penunjuk_sewa, id_berikutnya++, kode_dipilih,
                   daftar_film[indeks_film].judul_film,
                   daftar_film[indeks_film].harga_sewa,
                   durasi_hari, tanggal_sewa, tanggal_kembali, total_bayar_sewa);
    jumlah_sewa++;

    cout << "  [v] Berhasil menyewa \"" << daftar_film[indeks_film].judul_film << "\"!" << endl;
    cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
}

void menuKembalikanFilm() {
    cout << "  === KEMBALIKAN FILM ===" << endl;
    cout << "+----+------------------------------+------------+------------+" << endl;
    cout << "| ID | Judul                        | Tgl Sewa   | Wajib Kemb |" << endl;
    cout << "+----+------------------------------+------------+------------+" << endl;

    bool ada_sewa_aktif = false;
    for (int i = 0; i < jumlah_sewa; i++) {
        if (daftar_sewa[i].password_penyewa != password_aktif || daftar_sewa[i].sudah_kembali) continue;

        string tgl_sewa_str = "";
        if (daftar_sewa[i].tanggal_sewa.hari   < 10) tgl_sewa_str += "0";
        tgl_sewa_str += to_string(daftar_sewa[i].tanggal_sewa.hari) + "/";
        if (daftar_sewa[i].tanggal_sewa.bulan  < 10) tgl_sewa_str += "0";
        tgl_sewa_str += to_string(daftar_sewa[i].tanggal_sewa.bulan) + "/" + to_string(daftar_sewa[i].tanggal_sewa.tahun);

        string tgl_kemb_str = "";
        if (daftar_sewa[i].tanggal_kembali.hari   < 10) tgl_kemb_str += "0";
        tgl_kemb_str += to_string(daftar_sewa[i].tanggal_kembali.hari) + "/";
        if (daftar_sewa[i].tanggal_kembali.bulan  < 10) tgl_kemb_str += "0";
        tgl_kemb_str += to_string(daftar_sewa[i].tanggal_kembali.bulan) + "/" + to_string(daftar_sewa[i].tanggal_kembali.tahun);

        cout << "| " << left << setw(2)  << daftar_sewa[i].id_sewa
             << " | "        << setw(29) << daftar_sewa[i].judul_film_sewa
             << "| "         << setw(11) << tgl_sewa_str
             << "| "         << setw(11) << tgl_kemb_str << "|" << endl;
        ada_sewa_aktif = true;
    }
    cout << "+----+------------------------------+------------+------------+" << endl;

    if (!ada_sewa_aktif) {
        cout << "  Tidak ada sewa aktif." << endl; cin.ignore(); cin.get(); return;
    }

    int id_dikembalikan;
    cout << "  ID sewa : "; cin >> id_dikembalikan;

    int indeks_sewa = cariSewa(id_dikembalikan, password_aktif);
    if (indeks_sewa == -1) {
        cout << "  [!] ID tidak valid." << endl; cin.ignore(); cin.get(); return;
    }

    Tanggal tanggal_aktual_kembali;
    cout << "  Tanggal Kembali:" << endl;
    inputTanggal(tanggal_aktual_kembali.hari, tanggal_aktual_kembali.bulan, tanggal_aktual_kembali.tahun);

    int selisih_hari    = hitungSelisihHari(daftar_sewa[indeks_sewa].tanggal_kembali, tanggal_aktual_kembali);
    int denda_terlambat = hitungDenda(selisih_hari);

    daftar_sewa[indeks_sewa].denda         = denda_terlambat;
    daftar_sewa[indeks_sewa].sudah_kembali = true;

    int indeks_film_kembali = cariFilm(daftar_sewa[indeks_sewa].kode_film_sewa);
    if (indeks_film_kembali != -1) daftar_film[indeks_film_kembali].tersedia = true;

    cout << "  [v] Film berhasil dikembalikan!" << endl;
    if (selisih_hari > 0) {
        cout << "  Terlambat " << selisih_hari << " hari" << endl;
        cout << "  Denda     : Rp" << denda_terlambat << endl;
    } else {
        cout << "  Tepat waktu, tidak ada denda." << endl;
    }
    cout << "  TOTAL BAYAR: Rp" << daftar_sewa[indeks_sewa].total_bayar + denda_terlambat << endl;
    cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
}

void menuRiwayatSewa(string nama_pengguna, string password_pengguna) {
    cout << "  === RIWAYAT SEWA - " << nama_pengguna << " ===" << endl;
    cout << "+----+------------------------------+----------+---------+" << endl;
    cout << "| ID | Judul                        | Total    | Status  |" << endl;
    cout << "+----+------------------------------+----------+---------+" << endl;

    bool ada_riwayat = false;
    for (int i = 0; i < jumlah_sewa; i++) {
        if (daftar_sewa[i].password_penyewa != password_pengguna) continue;
        string status_sewa   = daftar_sewa[i].sudah_kembali ? "Selesai " : "Aktif   ";
        int    total_tampil  = daftar_sewa[i].total_bayar + daftar_sewa[i].denda;
        string total_str     = "Rp" + to_string(total_tampil);
        cout << "| " << left << setw(2)  << daftar_sewa[i].id_sewa
             << " | "        << setw(29) << daftar_sewa[i].judul_film_sewa
             << "| "         << setw(8)  << total_str
             << "| "         << status_sewa << "|" << endl;
        ada_riwayat = true;
    }
    cout << "+----+------------------------------+----------+---------+" << endl;
    if (!ada_riwayat) cout << "  Belum ada riwayat." << endl;
    cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
}

void menuTambahFilm() {
    cout << "  === TAMBAH FILM ===" << endl;
    if (jumlah_film >= MAKS_FILM) {
        cout << "  [!] Kapasitas penuh." << endl; cin.ignore(); cin.get(); return;
    }
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr |" << endl;
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    for (int i = 0; i < jumlah_film; i++) {
        string harga_str = "Rp" + to_string(daftar_film[i].harga_sewa);
        cout << "| " << left << setw(5)  << daftar_film[i].kode_film
             << "| "         << setw(29) << daftar_film[i].judul_film
             << "| "         << setw(10) << daftar_film[i].genre_film
             << "| "         << setw(5)  << daftar_film[i].tahun_rilis
             << " | "        << setw(8)  << harga_str << "|" << endl;
    }
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    cin.ignore();
    cout << "  Kode   : "; getline(cin, daftar_film[jumlah_film].kode_film);
    if (daftar_film[jumlah_film].kode_film == "") return;

    bool kode_duplikat = false;
    for (int i = 0; i < jumlah_film; i++)
        if (daftar_film[i].kode_film == daftar_film[jumlah_film].kode_film) { kode_duplikat = true; break; }
    if (kode_duplikat) {
        cout << "  [!] Kode sudah ada." << endl;
        daftar_film[jumlah_film].kode_film = ""; cin.get(); return;
    }
    cout << "  Judul  : "; getline(cin, daftar_film[jumlah_film].judul_film);
    cout << "  Genre  : "; getline(cin, daftar_film[jumlah_film].genre_film);
    cout << "  Tahun  : "; cin >> daftar_film[jumlah_film].tahun_rilis;  cin.ignore();
    cout << "  Harga  : "; cin >> daftar_film[jumlah_film].harga_sewa;   cin.ignore();
    cout << "  Studio : "; getline(cin, daftar_film[jumlah_film].studio.nama_studio);
    cout << "  Negara : "; getline(cin, daftar_film[jumlah_film].studio.negara_studio);
    daftar_film[jumlah_film].tersedia = true;
    jumlah_film++;
    cout << "  [v] Film berhasil ditambahkan!" << endl;
    cout << "  [Tekan Enter...]"; cin.get();
}

void menuEditFilm() {
    cout << "  === EDIT FILM ===" << endl;
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr |" << endl;
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    for (int i = 0; i < jumlah_film; i++) {
        string harga_str = "Rp" + to_string(daftar_film[i].harga_sewa);
        cout << "| " << left << setw(5)  << daftar_film[i].kode_film
             << "| "         << setw(29) << daftar_film[i].judul_film
             << "| "         << setw(10) << daftar_film[i].genre_film
             << "| "         << setw(5)  << daftar_film[i].tahun_rilis
             << " | "        << setw(8)  << harga_str << "|" << endl;
    }
    cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
    cin.ignore();
    string kode_diedit;
    cout << "  Kode film (Enter -> Kembali) : ";
    getline(cin, kode_diedit);
    if (kode_diedit == "") return;

    int indeks_edit = cariFilm(kode_diedit);
    if (indeks_edit == -1) {
        cout << "  [!] Kode tidak ditemukan." << endl; cin.get(); return;
    }
    cout << "  [1]Judul  [2]Genre  [3]Tahun  [4]Harga  [5]Studio  [6]Negara" << endl;
    cout << "  Pilihan  : "; int pilihan_edit; cin >> pilihan_edit; cin.ignore();
    if      (pilihan_edit == 1) { cout << "  Judul baru  : "; getline(cin, daftar_film[indeks_edit].judul_film); }
    else if (pilihan_edit == 2) { cout << "  Genre baru  : "; getline(cin, daftar_film[indeks_edit].genre_film); }
    else if (pilihan_edit == 3) { cout << "  Tahun baru  : "; cin >> daftar_film[indeks_edit].tahun_rilis; }
    else if (pilihan_edit == 4) { cout << "  Harga baru  : "; cin >> daftar_film[indeks_edit].harga_sewa; }
    else if (pilihan_edit == 5) { cout << "  Studio baru : "; getline(cin, daftar_film[indeks_edit].studio.nama_studio); }
    else if (pilihan_edit == 6) { cout << "  Negara baru : "; getline(cin, daftar_film[indeks_edit].studio.negara_studio); }
    cout << "  [v] Film berhasil diedit!" << endl;
    cout << "  [Tekan Enter...]"; cin.get();
}

void menuHapusFilm() {
    cout << "  === HAPUS FILM ===" << endl;
    cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
    cout << "| Kode  | Judul                        | Genre     | Tahun | Status  |" << endl;
    cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
    for (int i = 0; i < jumlah_film; i++) {
        string status_film = daftar_film[i].tersedia ? "Tersedia" : "Disewa  ";
        cout << "| " << left << setw(5)  << daftar_film[i].kode_film
             << "| "         << setw(29) << daftar_film[i].judul_film
             << "| "         << setw(10) << daftar_film[i].genre_film
             << "| "         << setw(5)  << daftar_film[i].tahun_rilis
             << " | "        << status_film << "|" << endl;
    }
    cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
    cin.ignore();
    string kode_dihapus;
    cout << "  Kode film (Enter -> Kembali) : ";
    getline(cin, kode_dihapus);
    if (kode_dihapus == "") return;

    int indeks_hapus = cariFilm(kode_dihapus);
    if (indeks_hapus == -1) {
        cout << "  [!] Kode tidak ditemukan." << endl; cin.get(); return;
    }
    if (!daftar_film[indeks_hapus].tersedia) {
        cout << "  [!] Film sedang disewa, tidak bisa dihapus." << endl; cin.get(); return;
    }
    cout << "  Hapus \"" << daftar_film[indeks_hapus].judul_film << "\"? (y/n) : ";
    char konfirmasi_hapus; cin >> konfirmasi_hapus;
    if (konfirmasi_hapus != 'y' && konfirmasi_hapus != 'Y') {
        cout << "  Dibatalkan." << endl; cin.ignore(); cin.get(); return;
    }
    for (int i = indeks_hapus; i < jumlah_film - 1; i++) daftar_film[i] = daftar_film[i + 1];
    jumlah_film--;
    cout << "  [v] Film berhasil dihapus!" << endl;
    cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
}

void menuSemuaRiwayat() {
    cout << "  === SEMUA RIWAYAT SEWA ===" << endl;
    cout << "+----+-----------+------------------------------+----------+---------+" << endl;
    cout << "| ID | Penyewa   | Film                         | Total    | Status  |" << endl;
    cout << "+----+-----------+------------------------------+----------+---------+" << endl;
    if (jumlah_sewa == 0) cout << "  Belum ada riwayat." << endl;
    for (int i = 0; i < jumlah_sewa; i++) {
        string status_sewa  = daftar_sewa[i].sudah_kembali ? "Selesai " : "Aktif   ";
        int    denda_tampil = daftar_sewa[i].sudah_kembali
                              ? daftar_sewa[i].denda
                              : hitungDenda(daftar_sewa[i].harga_per_hari, 0);
        int    total_tampil = daftar_sewa[i].total_bayar + denda_tampil;
        string total_str    = "Rp" + to_string(total_tampil);
        cout << "| " << left << setw(2)  << daftar_sewa[i].id_sewa
             << " | "        << setw(10) << daftar_sewa[i].nama_penyewa
             << "| "         << setw(29) << daftar_sewa[i].judul_film_sewa
             << "| "         << setw(8)  << total_str
             << "| "         << status_sewa << "|" << endl;
    }
    cout << "+----+-----------+------------------------------+----------+---------+" << endl;
    cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
}

bool prosesLogin(string &nama_hasil, string &password_hasil, string &role_hasil) {
    int  sisa_percobaan = 3;
    bool login_berhasil = false;

    while (sisa_percobaan > 0 && !login_berhasil) {
        string input_nama, input_password;
        cin.ignore();
        cout << "  Nama      : "; getline(cin, input_nama);
        cout << "  Password  : "; getline(cin, input_password);
        for (int i = 0; i < jumlah_user; i++) {
            if (daftar_user[i].nama_pengguna     == input_nama &&
                daftar_user[i].password_pengguna == input_password) {
                nama_hasil     = daftar_user[i].nama_pengguna;
                password_hasil = daftar_user[i].password_pengguna;
                role_hasil     = daftar_user[i].role_pengguna;
                login_berhasil = true;
                break;
            }
        }
        if (login_berhasil) {
            cout << "  [v] Selamat datang, " << nama_hasil << "!" << endl;
            cout << "  [Tekan Enter...]"; cin.get();
        } else {
            sisa_percobaan--;
            if (sisa_percobaan > 0)
                cout << "  [!] Nama/password salah. Sisa percobaan: " << sisa_percobaan << endl;
            else
                cout << "  [!!!] Gagal 3 kali. Kembali ke menu utama." << endl;
        }
    }
    return login_berhasil;
}

void prosesRegister(string role_default) {
    if (jumlah_user >= MAKS_USER) {
        cout << "  [!] Kapasitas pengguna penuh." << endl;
        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get(); return;
    }
    cin.ignore();
    cout << "  Nama      : "; getline(cin, daftar_user[jumlah_user].nama_pengguna);
    bool nama_sudah_ada = false;
    for (int i = 0; i < jumlah_user; i++)
        if (daftar_user[i].nama_pengguna == daftar_user[jumlah_user].nama_pengguna) {
            nama_sudah_ada = true; break;
        }
    if (nama_sudah_ada) {
        cout << "  [!] Nama sudah digunakan." << endl;
        daftar_user[jumlah_user].nama_pengguna = "";
    } else {
        cout << "  Password  : "; getline(cin, daftar_user[jumlah_user].password_pengguna);
        daftar_user[jumlah_user].role_pengguna = role_default;
        jumlah_user++;
        cout << "  [v] Akun berhasil dibuat!" << endl;
    }
    cout << "  [Tekan Enter...]"; cin.get();
}

int main() {
    inisialisasiData();

    bool program_berjalan = true;
    do {
        cout << "==============================================" << endl;
        cout << "         SELAMAT DATANG DI CINEMARENT        " << endl;
        cout << "  1. Login"                                     << endl;
        cout << "  2. Register"                                  << endl;
        cout << "  0. Keluar"                                    << endl;
        cout << "==============================================" << endl;
        cout << "  Pilihan : ";
        int pilihan_awal; cin >> pilihan_awal;

        if (pilihan_awal == 2) {
            prosesRegister("User");

        } else if (pilihan_awal == 1) {
            bool login_ok = prosesLogin(nama_aktif, password_aktif, role_aktif);

            if (login_ok) {
                bool sedang_login = true;
                do {
                    cout << "==============================================" << endl;
                    cout << "  MENU " << (role_aktif == "Admin" ? "ADMIN" : "USER")
                         << " | " << nama_aktif << endl;
                    cout << "  1. Lihat Film"   << endl;
                    cout << "  2. Sewa Film"    << endl;
                    cout << "  3. Kembalikan"   << endl;
                    cout << "  4. Riwayat Sewa" << endl;
                    if (role_aktif == "Admin") {
                        cout << "-------------------------------------------" << endl;
                        cout << "  5. Tambah Film"   << endl;
                        cout << "  6. Edit Film"     << endl;
                        cout << "  7. Hapus Film"    << endl;
                        cout << "  8. Semua Riwayat" << endl;
                    }
                    cout << "  0. Logout" << endl;
                    cout << "----------------------------------------------" << endl;
                    cout << "  Pilihan : ";
                    int pilihan_menu; cin >> pilihan_menu;

                    switch (pilihan_menu) {
                        case 1: menuLihatFilm();                              break;
                        case 2: menuSewaFilm();                               break;
                        case 3: menuKembalikanFilm();                         break;
                        case 4: menuRiwayatSewa(nama_aktif, password_aktif);  break;
                        case 5:
                            if (role_aktif == "Admin") menuTambahFilm();
                            else { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); }
                            break;
                        case 6:
                            if (role_aktif == "Admin") menuEditFilm();
                            else { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); }
                            break;
                        case 7:
                            if (role_aktif == "Admin") menuHapusFilm();
                            else { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); }
                            break;
                        case 8:
                            if (role_aktif == "Admin") menuSemuaRiwayat();
                            else { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); }
                            break;
                        case 0:
                            cout << "  Sampai jumpa, " << nama_aktif << "!" << endl;
                            nama_aktif = ""; password_aktif = ""; role_aktif = "";
                            sedang_login = false;
                            cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                            break;
                        default:
                            cout << "  [!] Pilihan tidak valid." << endl;
                            cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                            break;
                    }
                } while (sedang_login);
            }

        } else if (pilihan_awal == 0) {
            cout << "  Terima kasih! Sampai jumpa!" << endl;
            program_berjalan = false;
        } else {
            cout << "  [!] Pilihan tidak valid." << endl;
            cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
        }

    } while (program_berjalan);
    return 0;
}