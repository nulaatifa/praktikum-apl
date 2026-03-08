#include <iostream>
using namespace std;

struct Studio {
    string nama;
    string negara;
};

struct Film {
    string kode;
    string judul;
    string genre;
    int    tahun;
    int    harga_sewa;
    Studio studio;
    bool   tersedia;
};

struct Pengguna {
    string nama;
    string password;
    string role;
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
    string  kode_film;
    string  judul_film;
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

int main() {

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

    bool program_jalan = true;

    do {
        cout << "==============================================" << endl;
        cout << "         SELAMAT DATANG DI CINEMARENT        " << endl;
        cout << " 1. Login"                                     << endl;
        cout << " 2. Register"                                  << endl;
        cout << " 0. Keluar"                                    << endl;
        cout << "==============================================" << endl;
        cout << "  Pilihan : ";
        int pilihan_awal; cin >> pilihan_awal;

        if (pilihan_awal == 2) {
            if (jumlah_user >= MAKS_USER) {
                cout << "  [!] Kapasitas penuh." << endl;
            } else {
                cin.ignore();
                cout << "  Nama      : "; getline(cin, daftar_user[jumlah_user].nama);
                bool nama_sudah_ada = false;
                for (int i = 0; i < jumlah_user; i++)
                    if (daftar_user[i].nama == daftar_user[jumlah_user].nama) { nama_sudah_ada = true; break; }
                if (nama_sudah_ada) {
                    cout << "  [!] Nama sudah digunakan." << endl;
                    daftar_user[jumlah_user].nama = "";
                } else {
                    cout << "  Password  : "; getline(cin, daftar_user[jumlah_user].password);
                    daftar_user[jumlah_user].role = "User";
                    jumlah_user++;
                    cout << "  [v] Akun berhasil dibuat!" << endl;
                }
            }
            cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();

        } else if (pilihan_awal == 1) {
            int  sisa_coba = 3;
            bool login_ok  = false;

            while (sisa_coba > 0 && !login_ok) {
                string input_nama, input_nim;
                cin.ignore();
                cout << "  Nama      : "; getline(cin, input_nama);
                cout << "  Password  : "; getline(cin, input_nim);
                for (int i = 0; i < jumlah_user; i++) {
                    if (daftar_user[i].nama == input_nama && daftar_user[i].password == input_nim) {
                        nama_aktif     = daftar_user[i].nama;
                        password_aktif = daftar_user[i].password;
                        role_aktif     = daftar_user[i].role;
                        login_ok       = true;
                        break;
                    }
                }
                if (login_ok) {
                    cout << "  [v] Selamat datang, " << nama_aktif << "!" << endl;
                    cout << "  [Tekan Enter...]"; cin.get();
                } else {
                    sisa_coba--;
                    if (sisa_coba > 0)
                        cout << "  [!] Salah. Sisa percobaan: " << sisa_coba << endl;
                    else {
                        cout << "  [!!!] Gagal 3 kali. Program berhenti." << endl;
                        program_jalan = false;
                    }
                }
            }

            if (login_ok) {
                bool sedang_login = true;
                do {
                    cout << "==============================================" << endl;
                    cout << "  MENU " << (role_aktif == "Admin" ? "ADMIN" : "USER") << " | " << nama_aktif << endl;
                    cout << "  1. Lihat Film"    << endl;
                    cout << "  2. Sewa Film"     << endl;
                    cout << "  3. Kembalikan"    << endl;
                    cout << "  4. Riwayat Sewa"  << endl;
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

                    case 1: {
                        cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;
                        cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr | Status  |" << endl;
                        cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;
                        for (int i = 0; i < jumlah_film; i++) {
                            string sf;
                            if (daftar_film[i].tersedia) sf = "Tersedia";
                            else                         sf = "Disewa  ";
                            cout << "| " << daftar_film[i].kode;
                            for (int s = daftar_film[i].kode.length(); s < 6; s++) cout << " ";
                            cout << "| " << daftar_film[i].judul;
                            for (int s = daftar_film[i].judul.length(); s < 29; s++) cout << " ";
                            cout << "| " << daftar_film[i].genre;
                            for (int s = daftar_film[i].genre.length(); s < 10; s++) cout << " ";
                            cout << "| " << daftar_film[i].tahun << " | Rp" << daftar_film[i].harga_sewa;
                            if (daftar_film[i].harga_sewa < 10000)      cout << "  ";
                            else if (daftar_film[i].harga_sewa < 100000) cout << " ";
                            cout << "| " << sf << "|" << endl;
                        }
                        cout << "+-------+------------------------------+-----------+-------+----------+---------+" << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 2: {
                        cout << "  === SEWA FILM ===" << endl;
                        cout << "+-------+------------------------------+-----------+----------+" << endl;
                        cout << "| Kode  | Judul                        | Genre     | Harga/Hr |" << endl;
                        cout << "+-------+------------------------------+-----------+----------+" << endl;
                        bool ada_tersedia = false;
                        for (int i = 0; i < jumlah_film; i++) {
                            if (!daftar_film[i].tersedia) continue;
                            cout << "| " << daftar_film[i].kode;
                            for (int s = daftar_film[i].kode.length(); s < 6; s++) cout << " ";
                            cout << "| " << daftar_film[i].judul;
                            for (int s = daftar_film[i].judul.length(); s < 29; s++) cout << " ";
                            cout << "| " << daftar_film[i].genre;
                            for (int s = daftar_film[i].genre.length(); s < 10; s++) cout << " ";
                            cout << "| Rp" << daftar_film[i].harga_sewa;
                            if (daftar_film[i].harga_sewa < 10000)      cout << "  ";
                            else if (daftar_film[i].harga_sewa < 100000) cout << " ";
                            cout << "|" << endl;
                            ada_tersedia = true;
                        }
                        cout << "+-------+------------------------------+-----------+----------+" << endl;
                        if (!ada_tersedia) { cout << "  Semua film sedang disewa." << endl; cin.ignore(); cin.get(); break; }

                        cout << "  Kode (Tekan Enter -> Kembali) : ";
                        string kode_sewa; cin.ignore(); getline(cin, kode_sewa);
                        if (kode_sewa == "") break;

                        int idx_film = -1;
                        for (int i = 0; i < jumlah_film; i++)
                            if (daftar_film[i].kode == kode_sewa && daftar_film[i].tersedia) { idx_film = i; break; }
                        if (idx_film == -1) { cout << "  [!] Film tidak ditemukan atau sedang disewa." << endl; cin.get(); break; }

                        Tanggal tgl_sewa;
                        cout << "  Tgl Sewa - Hari  : "; cin >> tgl_sewa.hari;
                        cout << "  Tgl Sewa - Bulan : "; cin >> tgl_sewa.bulan;
                        cout << "  Tgl Sewa - Tahun : "; cin >> tgl_sewa.tahun;
                        int durasi_sewa;
                        cout << "  Durasi (hari)    : "; cin >> durasi_sewa;

                        Tanggal tgl_kembali = tgl_sewa;
                        int hari_per_bulan[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
                        tgl_kembali.hari += durasi_sewa;
                        while (tgl_kembali.hari > hari_per_bulan[tgl_kembali.bulan]) {
                            tgl_kembali.hari -= hari_per_bulan[tgl_kembali.bulan];
                            tgl_kembali.bulan++;
                            if (tgl_kembali.bulan > 12) { tgl_kembali.bulan = 1; tgl_kembali.tahun++; }
                        }

                        int total_bayar_sewa = daftar_film[idx_film].harga_sewa * durasi_sewa;

                        cout << "  Film         : " << daftar_film[idx_film].judul << endl;
                        cout << "  Tgl Sewa     : ";
                        if (tgl_sewa.hari < 10) cout << "0";
                        cout << tgl_sewa.hari << "/";
                        if (tgl_sewa.bulan < 10) cout << "0";
                        cout << tgl_sewa.bulan << "/" << tgl_sewa.tahun << endl;
                        cout << "  Wajib Kembal : ";
                        if (tgl_kembali.hari < 10) cout << "0";
                        cout << tgl_kembali.hari << "/";
                        if (tgl_kembali.bulan < 10) cout << "0";
                        cout << tgl_kembali.bulan << "/" << tgl_kembali.tahun << endl;
                        cout << "  Total        : Rp" << total_bayar_sewa << "  (denda Rp" << DENDA_PER_HARI << "/hari)" << endl;
                        cout << "  Konfirmasi? (y/n) : "; char konfirmasi; cin >> konfirmasi;
                        if (konfirmasi != 'y' && konfirmasi != 'Y') { cout << "  Dibatalkan." << endl; cin.ignore(); cin.get(); break; }

                        daftar_film[idx_film].tersedia               = false;
                        daftar_sewa[jumlah_sewa].id_sewa             = id_berikutnya++;
                        daftar_sewa[jumlah_sewa].password_penyewa    = password_aktif;
                        daftar_sewa[jumlah_sewa].nama_penyewa        = nama_aktif;
                        daftar_sewa[jumlah_sewa].kode_film           = kode_sewa;
                        daftar_sewa[jumlah_sewa].judul_film          = daftar_film[idx_film].judul;
                        daftar_sewa[jumlah_sewa].harga_per_hari      = daftar_film[idx_film].harga_sewa;
                        daftar_sewa[jumlah_sewa].durasi_hari         = durasi_sewa;
                        daftar_sewa[jumlah_sewa].tanggal_sewa        = tgl_sewa;
                        daftar_sewa[jumlah_sewa].tanggal_kembali     = tgl_kembali;
                        daftar_sewa[jumlah_sewa].total_bayar         = total_bayar_sewa;
                        daftar_sewa[jumlah_sewa].denda               = 0;
                        daftar_sewa[jumlah_sewa].sudah_kembali       = false;
                        jumlah_sewa++;
                        cout << "  [v] Berhasil menyewa \"" << daftar_film[idx_film].judul << "\"!" << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 3: {
                        cout << "  === KEMBALIKAN FILM ===" << endl;
                        cout << "+----+------------------------------+------------+------------+" << endl;
                        cout << "| ID | Judul                        | Tgl Sewa   | Wajib Kemb |" << endl;
                        cout << "+----+------------------------------+------------+------------+" << endl;
                        bool ada_aktif = false;
                        for (int i = 0; i < jumlah_sewa; i++) {
                            if (daftar_sewa[i].password_penyewa != password_aktif || daftar_sewa[i].sudah_kembali) continue;
                            cout << "| " << daftar_sewa[i].id_sewa;
                            if (daftar_sewa[i].id_sewa < 10)  cout << "  ";
                            else if (daftar_sewa[i].id_sewa < 100) cout << " ";
                            cout << "| " << daftar_sewa[i].judul_film;
                            for (int s = daftar_sewa[i].judul_film.length(); s < 29; s++) cout << " ";
                            cout << "| ";
                            if (daftar_sewa[i].tanggal_sewa.hari < 10) cout << "0";
                            cout << daftar_sewa[i].tanggal_sewa.hari << "/";
                            if (daftar_sewa[i].tanggal_sewa.bulan < 10) cout << "0";
                            cout << daftar_sewa[i].tanggal_sewa.bulan << "/" << daftar_sewa[i].tanggal_sewa.tahun;
                            cout << " | ";
                            if (daftar_sewa[i].tanggal_kembali.hari < 10) cout << "0";
                            cout << daftar_sewa[i].tanggal_kembali.hari << "/";
                            if (daftar_sewa[i].tanggal_kembali.bulan < 10) cout << "0";
                            cout << daftar_sewa[i].tanggal_kembali.bulan << "/" << daftar_sewa[i].tanggal_kembali.tahun;
                            cout << " |" << endl;
                            ada_aktif = true;
                        }
                        cout << "+----+------------------------------+------------+------------+" << endl;
                        if (!ada_aktif) { cout << "  Tidak ada sewa aktif." << endl; cin.ignore(); cin.get(); break; }

                        int id_kembalikan;
                        cout << "  ID sewa : "; cin >> id_kembalikan;
                        int idx_sewa = -1;
                        for (int i = 0; i < jumlah_sewa; i++)
                            if (daftar_sewa[i].id_sewa == id_kembalikan && daftar_sewa[i].password_penyewa == password_aktif && !daftar_sewa[i].sudah_kembali) { idx_sewa = i; break; }
                        if (idx_sewa == -1) { cout << "  [!] ID tidak valid." << endl; cin.ignore(); cin.get(); break; }

                        Tanggal tgl_aktual;
                        cout << "  Tgl Kembali - Hari  : "; cin >> tgl_aktual.hari;
                        cout << "  Tgl Kembali - Bulan : "; cin >> tgl_aktual.bulan;
                        cout << "  Tgl Kembali - Tahun : "; cin >> tgl_aktual.tahun;

                        int hari_wajib  = daftar_sewa[idx_sewa].tanggal_kembali.tahun * 365 + daftar_sewa[idx_sewa].tanggal_kembali.bulan * 30 + daftar_sewa[idx_sewa].tanggal_kembali.hari;
                        int hari_aktual = tgl_aktual.tahun * 365 + tgl_aktual.bulan * 30 + tgl_aktual.hari;
                        int selisih     = hari_aktual - hari_wajib;
                        int denda_bayar = (selisih > 0) ? selisih * DENDA_PER_HARI : 0;

                        daftar_sewa[idx_sewa].denda         = denda_bayar;
                        daftar_sewa[idx_sewa].sudah_kembali = true;
                        for (int i = 0; i < jumlah_film; i++)
                            if (daftar_film[i].kode == daftar_sewa[idx_sewa].kode_film) { daftar_film[i].tersedia = true; break; }

                        cout << "  [v] Film dikembalikan!" << endl;
                        if (selisih > 0) cout << "  Denda " << selisih << " hari: Rp" << denda_bayar << endl;
                        else             cout << "  Tepat waktu, tidak ada denda." << endl;
                        cout << "  TOTAL BAYAR: Rp" << daftar_sewa[idx_sewa].total_bayar + denda_bayar << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 4: {
                        cout << "  === RIWAYAT SEWA - " << nama_aktif << " ===" << endl;
                        cout << "+----+------------------------------+----------+---------+" << endl;
                        cout << "| ID | Judul                        | Total    | Status  |" << endl;
                        cout << "+----+------------------------------+----------+---------+" << endl;
                        bool ada_riwayat = false;
                        for (int i = 0; i < jumlah_sewa; i++) {
                            if (daftar_sewa[i].password_penyewa != password_aktif) continue;
                            string stat;
                            if (daftar_sewa[i].sudah_kembali) stat = "Selesai ";
                            else                              stat = "Aktif   ";
                            int total_tampil = daftar_sewa[i].total_bayar + daftar_sewa[i].denda;
                            cout << "| " << daftar_sewa[i].id_sewa;
                            if (daftar_sewa[i].id_sewa < 10)       cout << "  ";
                            else if (daftar_sewa[i].id_sewa < 100)  cout << " ";
                            cout << "| " << daftar_sewa[i].judul_film;
                            for (int s = daftar_sewa[i].judul_film.length(); s < 29; s++) cout << " ";
                            cout << "| Rp" << total_tampil;
                            if      (total_tampil < 10000)   cout << "  ";
                            else if (total_tampil < 100000)  cout << " ";
                            cout << "| " << stat << "|" << endl;
                            ada_riwayat = true;
                        }
                        cout << "+----+------------------------------+----------+---------+" << endl;
                        if (!ada_riwayat) cout << "  Belum ada riwayat." << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 5: {
                        if (role_aktif != "Admin") { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); break; }
                        cout << "  === TAMBAH FILM ===" << endl;
                        if (jumlah_film >= MAKS_FILM) { cout << "  [!] Kapasitas penuh." << endl; cin.ignore(); cin.get(); break; }
                        cout << "  Daftar film saat ini:" << endl;
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr |" << endl;
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        for (int i = 0; i < jumlah_film; i++) {
                            cout << "| " << daftar_film[i].kode;
                            for (int s = daftar_film[i].kode.length(); s < 6; s++) cout << " ";
                            cout << "| " << daftar_film[i].judul;
                            for (int s = daftar_film[i].judul.length(); s < 29; s++) cout << " ";
                            cout << "| " << daftar_film[i].genre;
                            for (int s = daftar_film[i].genre.length(); s < 10; s++) cout << " ";
                            cout << "| " << daftar_film[i].tahun << " | Rp" << daftar_film[i].harga_sewa;
                            if (daftar_film[i].harga_sewa < 10000)      cout << "  ";
                            else if (daftar_film[i].harga_sewa < 100000) cout << " ";
                            cout << "|" << endl;
                        }
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        cin.ignore();
                        cout << "  Kode   : "; getline(cin, daftar_film[jumlah_film].kode);
                        if (daftar_film[jumlah_film].kode == "") break;
                        bool kode_duplikat = false;
                        for (int i = 0; i < jumlah_film; i++)
                            if (daftar_film[i].kode == daftar_film[jumlah_film].kode) { kode_duplikat = true; break; }
                        if (kode_duplikat) { cout << "  [!] Kode sudah ada." << endl; daftar_film[jumlah_film].kode = ""; cin.get(); break; }
                        cout << "  Judul  : "; getline(cin, daftar_film[jumlah_film].judul);
                        cout << "  Genre  : "; getline(cin, daftar_film[jumlah_film].genre);
                        cout << "  Tahun  : "; cin >> daftar_film[jumlah_film].tahun;      cin.ignore();
                        cout << "  Harga  : "; cin >> daftar_film[jumlah_film].harga_sewa; cin.ignore();
                        cout << "  Studio : "; getline(cin, daftar_film[jumlah_film].studio.nama);
                        cout << "  Negara : "; getline(cin, daftar_film[jumlah_film].studio.negara);
                        daftar_film[jumlah_film].tersedia = true;
                        jumlah_film++;
                        cout << "  [v] Film ditambahkan!" << endl;
                        cout << "  [Tekan Enter...]"; cin.get();
                        break;
                    }

                    case 6: {
                        if (role_aktif != "Admin") { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); break; }
                        cout << "  === EDIT FILM ===" << endl;
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        cout << "| Kode  | Judul                        | Genre     | Tahun | Harga/Hr |" << endl;
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        for (int i = 0; i < jumlah_film; i++) {
                            cout << "| " << daftar_film[i].kode;
                            for (int s = daftar_film[i].kode.length(); s < 6; s++) cout << " ";
                            cout << "| " << daftar_film[i].judul;
                            for (int s = daftar_film[i].judul.length(); s < 29; s++) cout << " ";
                            cout << "| " << daftar_film[i].genre;
                            for (int s = daftar_film[i].genre.length(); s < 10; s++) cout << " ";
                            cout << "| " << daftar_film[i].tahun << " | Rp" << daftar_film[i].harga_sewa;
                            if (daftar_film[i].harga_sewa < 10000)      cout << "  ";
                            else if (daftar_film[i].harga_sewa < 100000) cout << " ";
                            cout << "|" << endl;
                        }
                        cout << "+-------+------------------------------+-----------+-------+----------+" << endl;
                        cin.ignore();
                        cout << "  Kode film (Tekan Enter -> kembali) : ";
                        string kode_edit; getline(cin, kode_edit);
                        if (kode_edit == "") break;
                        int idx_edit = -1;
                        for (int i = 0; i < jumlah_film; i++)
                            if (daftar_film[i].kode == kode_edit) { idx_edit = i; break; }
                        if (idx_edit == -1) { cout << "  [!] Kode tidak ditemukan." << endl; cin.get(); break; }
                        cout << "  [1]Judul [2]Genre [3]Tahun [4]Harga [5]Studio [6]Negara" << endl;
                        cout << "  Pilihan : "; int pilihan_edit; cin >> pilihan_edit; cin.ignore();
                        if      (pilihan_edit == 1) { cout << "  Judul baru  : "; getline(cin, daftar_film[idx_edit].judul); }
                        else if (pilihan_edit == 2) { cout << "  Genre baru  : "; getline(cin, daftar_film[idx_edit].genre); }
                        else if (pilihan_edit == 3) { cout << "  Tahun baru  : "; cin >> daftar_film[idx_edit].tahun; }
                        else if (pilihan_edit == 4) { cout << "  Harga baru  : "; cin >> daftar_film[idx_edit].harga_sewa; }
                        else if (pilihan_edit == 5) { cout << "  Studio baru : "; getline(cin, daftar_film[idx_edit].studio.nama); }
                        else if (pilihan_edit == 6) { cout << "  Negara baru : "; getline(cin, daftar_film[idx_edit].studio.negara); }
                        cout << "  [v] Film diedit!" << endl;
                        cout << "  [Tekan Enter...]"; cin.get();
                        break;
                    }

                    case 7: {
                        if (role_aktif != "Admin") { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); break; }
                        cout << "  === HAPUS FILM ===" << endl;
                        cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
                        cout << "| Kode  | Judul                        | Genre     | Tahun | Status  |" << endl;
                        cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
                        for (int i = 0; i < jumlah_film; i++) {
                            string sf;
                            if (daftar_film[i].tersedia) sf = "Tersedia";
                            else                         sf = "Disewa  ";
                            cout << "| " << daftar_film[i].kode;
                            for (int s = daftar_film[i].kode.length(); s < 6; s++) cout << " ";
                            cout << "| " << daftar_film[i].judul;
                            for (int s = daftar_film[i].judul.length(); s < 29; s++) cout << " ";
                            cout << "| " << daftar_film[i].genre;
                            for (int s = daftar_film[i].genre.length(); s < 10; s++) cout << " ";
                            cout << "| " << daftar_film[i].tahun << " | " << sf << "|" << endl;
                        }
                        cout << "+-------+------------------------------+-----------+-------+---------+" << endl;
                        cin.ignore();
                        cout << "  Kode film (Tekan Enter -> kembali) : ";
                        string kode_hapus; getline(cin, kode_hapus);
                        if (kode_hapus == "") break;
                        int idx_hapus = -1;
                        for (int i = 0; i < jumlah_film; i++)
                            if (daftar_film[i].kode == kode_hapus) { idx_hapus = i; break; }
                        if (idx_hapus == -1) { cout << "  [!] Kode tidak ditemukan." << endl; cin.get(); break; }
                        if (!daftar_film[idx_hapus].tersedia) { cout << "  [!] Film sedang disewa." << endl; cin.get(); break; }
                        cout << "  Hapus \"" << daftar_film[idx_hapus].judul << "\"? (y/n) : ";
                        char konfirmasi_hapus; cin >> konfirmasi_hapus;
                        if (konfirmasi_hapus != 'y' && konfirmasi_hapus != 'Y') { cout << "  Dibatalkan." << endl; cin.ignore(); cin.get(); break; }
                        for (int i = idx_hapus; i < jumlah_film - 1; i++) daftar_film[i] = daftar_film[i + 1];
                        jumlah_film--;
                        cout << "  [v] Film dihapus!" << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 8: {
                        if (role_aktif != "Admin") { cout << "  [!] Akses ditolak." << endl; cin.ignore(); cin.get(); break; }
                        cout << "  === SEMUA RIWAYAT SEWA ===" << endl;
                        cout << "+----+-----------+------------------------------+----------+---------+" << endl;
                        cout << "| ID | Penyewa   | Film                         | Total    | Status  |" << endl;
                        cout << "+----+-----------+------------------------------+----------+---------+" << endl;
                        if (jumlah_sewa == 0) cout << "  Belum ada riwayat." << endl;
                        for (int i = 0; i < jumlah_sewa; i++) {
                            string stat;
                            if (daftar_sewa[i].sudah_kembali) stat = "Selesai ";
                            else                              stat = "Aktif   ";
                            int total_tampil = daftar_sewa[i].total_bayar + daftar_sewa[i].denda;
                            cout << "| " << daftar_sewa[i].id_sewa;
                            if (daftar_sewa[i].id_sewa < 10)       cout << "  ";
                            else if (daftar_sewa[i].id_sewa < 100)  cout << " ";
                            cout << "| " << daftar_sewa[i].nama_penyewa;
                            for (int s = daftar_sewa[i].nama_penyewa.length(); s < 10; s++) cout << " ";
                            cout << "| " << daftar_sewa[i].judul_film;
                            for (int s = daftar_sewa[i].judul_film.length(); s < 29; s++) cout << " ";
                            cout << "| Rp" << total_tampil;
                            if      (total_tampil < 10000)   cout << "  ";
                            else if (total_tampil < 100000)  cout << " ";
                            cout << "| " << stat << "|" << endl;
                        }
                        cout << "+----+-----------+------------------------------+----------+---------+" << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    case 0: {
                        cout << "  Sampai jumpa, " << nama_aktif << "!" << endl;
                        nama_aktif = ""; password_aktif = ""; role_aktif = "";
                        sedang_login = false;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                    default:
                        cout << "  [!] Pilihan tidak valid." << endl;
                        cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
                        break;
                    }

                } while (sedang_login);
            }

        } else if (pilihan_awal == 0) {
            cout << "  Terima kasih! Sampai jumpa!" << endl;
            program_jalan = false;
        } else {
            cout << "  [!] Pilihan tidak valid." << endl;
            cout << "  [Tekan Enter...]"; cin.ignore(); cin.get();
        }

    } while (program_jalan);
    return 0;
}