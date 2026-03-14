// Tugas pratikum struktur data semester 2

#include <iostream>
#include <string>
#include <limits>
#include <thread>
#include <ctime>
#include <sstream>
using namespace std;

// struct data buku linked list
struct Buku {
    string id = "";
    string judul = "";
    string penulis = "";
    int tahunTerbit = 0;
    string genre = "";
    bool Tersedia = false;
};

struct Node {
    Buku data;
    Node* next;
};

Node* head = NULL;


// struct data pinjaman queue
struct Pinjaman {
    string id;
    string idBuku;
    string judul;
    string nama;
    long long nim;
    string tanggal;
};

struct NodePinjam {
    Pinjaman data;
    NodePinjam* next;
};

NodePinjam* frontPinjam = NULL;
NodePinjam* rearPinjam = NULL;


// struct data riwayat pinjaman
struct NodeRiwayat {
    Pinjaman data;
    NodeRiwayat* next;
};

NodeRiwayat* headRiwayat = NULL;


// stack untuk pengembalian
struct NodeKembali {
    Pinjaman data;
    NodeKembali* next;
};

NodeKembali* topKembali = NULL;



// clear error input
void clearError() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    this_thread::sleep_for(chrono::seconds(1));
}


// tanggal sekarang
string bulan[] = {
"Januari","Februari","Maret","April","Mei","Juni",
"Juli","Agustus","September","Oktober","November","Desember"
};

string TanggalSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;

    ss << ltm->tm_mday << " " << bulan[ltm->tm_mon] << " " << (1900 + ltm->tm_year) << " " << ltm->tm_hour << ":" << ltm->tm_min;

    return ss.str();
}


 
void welcomeMSG() {
    cout << endl;
    cout << "===========================" << endl;
    cout << "          Welcome          " << endl;
    cout << "===========================" << endl;
    cout << "1. Masuk sebagai pegawai" << endl;
    cout << "2. Masuk sebagai pengunjung" << endl;
    cout << "0. Keluar" << endl;
}


void menuAdmin() {
    cout << endl;
    cout << "===========================" << endl;
    cout << "       dasboard admin      " << endl;
    cout << "===========================" << endl;
    cout << "1. Menambah buku" << endl;
    cout << "2. Tampilkan data buku" << endl;
    cout << "3. mengubah data buku" << endl;
    cout << "4. menghapus data buku" << endl;
    cout << "5. Proses permintaan pinjaman" << endl;
    cout << "6. Proses pengembalian buku" << endl;
    cout << "0. Kembali" << endl;
}






void enqueuePinjam(Pinjaman pinjam) {

    NodePinjam* newNode = new NodePinjam;
    newNode->data = pinjam;
    newNode->next = NULL;

    if (rearPinjam == NULL) {
        frontPinjam = rearPinjam = newNode;
    } else {
        rearPinjam->next = newNode;
        rearPinjam = newNode;
    }
}


void dequeuePinjam() {

    if (frontPinjam == NULL){
        return;
    }

    NodePinjam* temp = frontPinjam;
    frontPinjam = frontPinjam->next;

    if (frontPinjam == NULL){
        rearPinjam = NULL;
    }

    delete temp;
}


// ===== ID ======
bool isIdExist(string id) {

    Node* current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// ID untuk buku
string generateIDBuku(string judul, int tahunTerbit) {
    // digit2
    char hurufPertama = judul[0];
    char hurufTerakhir = judul[judul.length() - 1];

    int selisih = hurufTerakhir - hurufPertama;
    selisih = abs(selisih);

    // digit4
    int jumlahTahun = 0;
    int temp = tahunTerbit;

    while (temp > 0) {
        jumlahTahun += temp % 10;
        temp /= 10;
    } 


    // to string
    string id2 = "";
    string id4 = "";

    if (selisih < 10) {
        id2 = "0" + to_string(selisih);
    } else {
        id2 = to_string(selisih);
    }

    if (jumlahTahun < 10) {
        id4 = "0" + to_string(jumlahTahun);
    } else {
        id4 = to_string(jumlahTahun);
    }

    string baseID = id2 + id4;

    string id = baseID + "0"; 
    int counter = 0;
    while (isIdExist(id)) {
        counter++;
        id = baseID + to_string(counter);
    }

    return id;
}

// ID untuk pinjaman
string generateIDPinjam(Buku buku, string nama, int nomor) {

    string idBuku = buku.id.substr(0,5);
    char kategori = tolower(buku.genre[0]);

    string tahun = "26";

    string inisial = "";
    inisial += tolower(nama[0]);

    if(nama.length() > 1)
        inisial += tolower(nama[1]);
    else
        inisial += 'x';

    string urut;

    if (nomor < 10)
        urut = "0" + to_string(nomor);
    else
        urut = to_string(nomor);

    return idBuku + kategori + tahun + inisial + urut;
}




// Management Buku
void insertBuku(Buku bukuBaru) {

    Node* newNode = new Node;
    newNode->data = bukuBaru;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
    }
}


void addBuku() {
    Buku bukuBaru;

    cout << endl;
    cout << "===========================" << endl;
    cout << "       Menambah Buku       " << endl;
    cout << "===========================" << endl;

    cin.ignore();
    while (true) {

        cout << "Masukkan judul buku: ";
        getline(cin, bukuBaru.judul);
        
        if (bukuBaru.judul.empty() || bukuBaru.judul.length() < 2) {
            cout << "Input tidak valid! Judul tidak boleh kosong." << endl;
            clearError();
            continue;
        } else {
            break;
        }

    }

    cout << "Masukkan penulis buku: ";
    getline(cin, bukuBaru.penulis);

    while (true) {
        cout << "Masukkan tahun terbit buku: ";
        cin >> bukuBaru.tahunTerbit;

        if (cin.fail() || bukuBaru.tahunTerbit < 1000 || bukuBaru.tahunTerbit > 2026) {
            cout << endl << "Input tidak valid! Harap masukkan angka dengan benar." << endl << endl;
            clearError();
            continue;
        } else {
            break;
        }
    }

    cin.ignore();
    cout << "Masukkan genre buku: ";
    getline(cin, bukuBaru.genre);

    bukuBaru.Tersedia = true;
    bukuBaru.id = generateIDBuku(bukuBaru.judul, bukuBaru.tahunTerbit);

    insertBuku(bukuBaru);

    cout << "Buku berhasil ditambahkan!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
}


void deleteBuku() {

    cout << endl;
    cout << "===========================" << endl;
    cout << "       Menghapus Buku      " << endl;
    cout << "===========================" << endl;

    if (head == NULL) {
        cout << "Belum ada data buku." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    string idHapus;
    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> idHapus;

    Node* current = head;
    Node* prev = NULL;

    while (current != NULL && current->data.id != idHapus) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "ID tidak ditemukan." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    // Tampilkan detail buku
    cout << endl;
    cout << "------------ Detail Buku -------------" << endl;
    cout << "Judul        : " << current->data.judul << endl;
    cout << "Id           : " << current->data.id << endl;
    cout << "Penulis      : " << current->data.penulis << endl;
    cout << "Tahun        : " << current->data.tahunTerbit << endl;
    cout << "Genre        : " << current->data.genre << endl;
    cout << "Ketersediaan : " << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
    cout << "--------------------------------------" << endl;

    string konfirmasi;
    cout << endl;
    cout << "Apakah anda yakin ingin menghapus buku ini? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi != "y" && konfirmasi != "Y") {
        cout << "Penghapusan dibatalkan." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    
    if (current == head) {
        head = current->next;
        delete current;
    } else {
        prev->next = current->next;
        delete current;
    }   

    cout << "Buku berhasil dihapus." << endl;
    this_thread::sleep_for(chrono::seconds(1));
}


void editBuku() {

    cout << endl;
    cout << "===========================" << endl;
    cout << "       Mengedit Buku       " << endl;
    cout << "===========================" << endl;

    if (head == NULL) {
        cout << "Belum ada data buku." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    string idEdit;
    cout << "Masukkan ID buku yang ingin diubah: ";
    cin >> idEdit;

    Node* current = head;

    while (current != NULL && current->data.id != idEdit) {
        current = current->next;
    }

    if (current == NULL) {
        cout << "ID tidak ditemukan." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    cout << endl;
    cout << "------------ Detail Buku -------------" << endl;
    cout << "Judul        : " << current->data.judul << endl;
    cout << "Id           : " << current->data.id << endl;
    cout << "Penulis      : " << current->data.penulis << endl;
    cout << "Tahun        : " << current->data.tahunTerbit << endl;
    cout << "Genre        : " << current->data.genre << endl;
    cout << "Ketersediaan : " << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
    cout << "--------------------------------------" << endl;

    cout << endl;
    cout << "1. Ubah judul" << endl;
    cout << "2. Ubah penulis" << endl;
    cout << "3. Ubah tahun terbit" << endl;
    cout << "4. Ubah genre" << endl;
    cout << "5. Ubah ketersediaan" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilih: ";
    
    int pilihanEdit;
    while(true){
        cin >> pilihanEdit;

        if (cin.fail() || pilihanEdit < 0 || pilihanEdit > 5) {
            cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
            clearError();
            cout << "Pilih: ";
            continue;
        } else {
            break;
        }
    }

    cout << endl;
    cin.ignore();

    if (pilihanEdit == 1) {

        while (true) {
            cout << "Masukkan judul baru: ";
            getline(cin, current->data.judul);

            if (current->data.judul.empty() || current->data.judul.length() < 2) {
                cout << "Input tidak valid! Judul tidak boleh kosong." << endl;
                continue;
            } else {
                break;
            }
        }
        current->data.id = generateIDBuku(current->data.judul, current->data.tahunTerbit);

    } else if (pilihanEdit == 2) {

        cout << "Masukkan penulis baru: ";
        getline(cin, current->data.penulis);

    } else if (pilihanEdit == 3) {

        while (true) {
            cout << "Masukkan tahun terbit baru: ";
            cin >> current->data.tahunTerbit;
            if (cin.fail() || current->data.tahunTerbit < 1000 || current->data.tahunTerbit > 2026) {
                cout << endl << "Input tidak valid! Harap masukkan angka dengan benar." << endl << endl;
                clearError();
                continue;
            } else {
                break;
            }
        }
        current->data.id = generateIDBuku(current->data.judul, current->data.tahunTerbit);

    } else if (pilihanEdit == 4) {

        cout << "Masukkan genre baru: ";
        getline(cin, current->data.genre);

    } else if (pilihanEdit == 5) {

        current->data.Tersedia = !current->data.Tersedia;
        cout << "Status ketersediaan berhasil diubah." << endl;

    } else if (pilihanEdit == 0) {
        return;
    }
    
    cout << "Data buku dan ID berhasil disimpan!" << endl;

    cout << endl;
    cout << "------------ Detail Buku -------------" << endl;
    cout << "Judul        : " << current->data.judul << endl;
    cout << "Id           : " << current->data.id << endl;
    cout << "Penulis      : " << current->data.penulis << endl;
    cout << "Tahun        : " << current->data.tahunTerbit << endl;
    cout << "Genre        : " << current->data.genre << endl;
    cout << "Ketersediaan : " << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
    cout << "--------------------------------------" << endl;

    this_thread::sleep_for(chrono::seconds(2));
}



void pushKembali(Pinjaman p) {
    NodeKembali* newNode = new NodeKembali;
    newNode->data = p;
    newNode->next = topKembali;
    topKembali = newNode;
}

void popKembali() {
    if (topKembali == NULL) return;

    NodeKembali* temp = topKembali;
    topKembali = topKembali->next;
    delete temp;
}


void tambahRiwayat(Pinjaman p) {
    NodeRiwayat* newNode = new NodeRiwayat;
    newNode->data = p;
    newNode->next = NULL;

    if (headRiwayat == NULL) {
        headRiwayat = newNode;
    } else {
        NodeRiwayat* temp = headRiwayat;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


void prosesPinjaman() {

    cout << endl;
    if (frontPinjam == NULL) {
        cout << "Tidak ada pinjaman untuk diproses !!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int nomor = 1;

    while (frontPinjam != NULL) {

        Pinjaman p = frontPinjam->data;

        cout << "======================================" << endl;
        cout << "              PINJAMAN KE-" << nomor << endl;
        cout << "======================================" << endl;

        cout << "--------------------------------------" << endl;
        cout << "Id : " << p.id << endl;
        cout << "Judul : " << p.judul << endl;
        cout << "Nama : " << p.nama << endl;
        cout << "NIM : " << p.nim << endl;
        cout << "Tanggal : " << p.tanggal << endl;
        cout << "--------------------------------------" << endl;

        cout << "1. Setujui" << endl;
        cout << "2. Tolak" << endl;
        cout << "0. Kembali" << endl;
        cout << "> ";

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            Node* buku = head;
            while (buku != NULL) {
                if (buku->data.id == p.idBuku) {
                    buku->data.Tersedia = false;
                    break;
                }
                buku = buku->next;
            }

            cout << "Pinjaman dengan id " << p.id << " telah diproses !!" << endl;
            tambahRiwayat(p);
            dequeuePinjam();
        }

        else if (pilihan == 2) {
            cout << "Pinjaman ditolak." << endl;
            dequeuePinjam();
        }

        else if (pilihan == 0) {
            break;
        }

        nomor++;
    }
}


void riwayatPinjaman() {

    if (headRiwayat == NULL) {
        cout << "Belum ada riwayat pinjaman." << endl;
        return;
    }

    int index = 0;
    int pilihan;

    while (true) {

        NodeRiwayat* current = headRiwayat;
        int counter = 0;

        while (counter < index) {
            current = current->next;
            counter++;
        }

        cout << "--------------------------------------" << endl;
        cout << "Id : " << current->data.id << endl;
        cout << "Judul : " << current->data.judul << endl;
        cout << "Nama : " << current->data.nama << endl;
        cout << "NIM : " << current->data.nim << endl;
        cout << "Tanggal : " << current->data.tanggal << endl;
        cout << "--------------------------------------" << endl;

        cout << "1. Selanjutnya" << endl;
        cout << "2. Sebelumnya" << endl;
        cout << "3. Kembalikan Buku" << endl;
        cout << "0. Kembali" << endl;
        while(true){
            cout << "> ";
            cin >> pilihan;

            if (cin.fail() || pilihan < 0 || pilihan > 3) {
                cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                clearError();
                continue;
            } else {
                break;
            }
        }

        if (pilihan == 0)
            break;

        int total = 0;
        NodeRiwayat* temp = headRiwayat;
        while (temp != NULL) {
            total++;
            temp = temp->next;
        }

        // selanjutnya
        if (pilihan == 1) {
            index++;
            if (index >= total)
                index = 0;
        }

        // sebelumnya
        else if (pilihan == 2) {
            index--;
            if (index < 0)
                index = total - 1;
        }

        // kembalikan buku
        else if (pilihan == 3) {

            char konfirmasi;
            while (true) {
                cout << "Apakah anda yakin ingin memproses pengembalian buku ini? (y/n) ";
                cout << "> ";
                cin >> konfirmasi;

                if (konfirmasi == 'y' || konfirmasi == 'n' || konfirmasi == 'Y' || konfirmasi == 'N')
                    break;

                clearError();
                cout << "Input tidak valid." << endl;
            }

            if (konfirmasi == 'n' || konfirmasi == 'N') {
                cout << "Pengembalian dibatalkan." << endl;
                continue;
            }

            pushKembali(current->data);

            cout << "Buku \"" << current->data.judul 
                 << "\" telah dikembalikan !!" << endl;

            NodeRiwayat* temp = headRiwayat;
            NodeRiwayat* prev = NULL;

            while (temp != NULL && temp != current) {
                prev = temp;
                temp = temp->next;
            }

            if (prev == NULL)
                headRiwayat = temp->next;
            else
                prev->next = temp->next;

            delete temp;

            int total = 0;
            NodeRiwayat* cek = headRiwayat;
            while (cek != NULL) {
                total++;
                cek = cek->next;
            }

            if (total == 0) {
                cout << "Tidak ada riwayat pinjaman lagi." << endl;
                return;
            }

            if (index >= total) {
                index = total - 1;
            }
        }
    }
}


void prosesPengembalian() {

    if (topKembali == NULL) {
        cout << "Tidak ada pengembalian untuk diproses !!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    int nomor = 1;
    while (topKembali != NULL) {

        Pinjaman p = topKembali->data;

        cout << "======================================" << endl;
        cout << "         PENGEMBALIAN KE-" << nomor << endl;
        cout << "======================================" << endl;

        cout << "Id : " << p.id << endl;
        cout << "Judul : " << p.judul << endl;
        cout << "Nama : " << p.nama << endl;
        cout << "NIM : " << p.nim << endl;
        cout << "Tanggal : " << p.tanggal << endl;

        cout << "1. Proses" << endl;
        cout << "0. Kembali" << endl;

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            Node* buku = head;
            while (buku != NULL) {
                if (buku->data.id == p.idBuku) {
                    buku->data.Tersedia = true;
                    break;
                }
                buku = buku->next;
            }

            cout << "Buku \"" << p.judul << "\" telah dikembalikan !!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            popKembali();
        }

        else if (pilihan == 0)
            break;

        nomor++;
    }
}




// =========== tampilan ===========
void tampilanAdmin() {

    if (head == NULL) {

        cout << "Belum ada data buku." << endl;

        string enter;
        cout << endl << "Tekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        getline(cin, enter);

        return;
    }

    int index = 0;
    int pilihan;

    while (true) {

        Node* current = head;
        int counter = 0;

        while (counter < index) {
            current = current->next;
            counter++;
        }

        // Menampilkan 1 buku
        cout << endl;
        cout << "------------ List Buku -------------" << endl;
        cout << "Judul        : " << current->data.judul << endl;
        cout << "Id           : " << current->data.id << endl;
        cout << "Penulis      : " << current->data.penulis << endl;
        cout << "Tahun        : " << current->data.tahunTerbit << endl;
        cout << "Genre        : " << current->data.genre << endl;
        cout << "Ketersediaan : " << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "--------------------------------------" << endl;

        while(true){
            cout << "1. Selanjutnya" << endl;
            cout << "2. Sebelumnya" << endl;
            cout << "0. Kembali" << endl;
            cout << "> ";
            cin >> pilihan;

            if (cin.fail() || pilihan < 0 || pilihan > 2) {
                cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                clearError();
                continue;
            } else {
                break;
            }
        }


        if (pilihan == 0) break;

        // Hitung isi buku
        int total = 0;
        Node* temp = head;
        while (temp != NULL) {
            total++;
            temp = temp->next;
        }

        // next
        if (pilihan == 1) { 
            index++;
            if (index >= total) {
                index = 0; 
            }
        }

        // previous
        else if (pilihan == 2) {
            index--;
            if (index < 0) {
                index = total - 1;
            }
        }

        else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}


void tampilanPengunjung() {

    if (head == NULL) {


        cout << "Belum ada data buku." << endl;

        string enter;
        cout << endl << "Tekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        getline(cin, enter);

        return;
    }

    int index = 0;
    int pilihan;

    while (true) {

        Node* current = head;
        int counter = 0;

        while (counter < index) {
            current = current->next;
            counter++;
        }

        // Menampilkan 1 buku
        cout << endl;
        cout << "------------ List Buku -------------" << endl;
        cout << "Judul        : " << current->data.judul << endl;
        cout << "Id           : " << current->data.id << endl;
        cout << "Penulis      : " << current->data.penulis << endl;
        cout << "Tahun        : " << current->data.tahunTerbit << endl;
        cout << "Genre        : " << current->data.genre << endl;
        cout << "Ketersediaan : " << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "--------------------------------------" << endl;

        while(true){
            cout << "1. Selanjutnya" << endl;
            cout << "2. Sebelumnya" << endl;
            cout << "3. Pinjam" << endl;
            cout << "0. Kembali" << endl;
            cout << "> ";
            cin >> pilihan;

            if (cin.fail() || pilihan < 0 || pilihan > 3) {
                cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                clearError();
                continue;
            } else {
                break;
            }
        }


        if (pilihan == 0) break;

        // Hitung isi buku
        int total = 0;
        Node* temp = head;
        while (temp != NULL) {
            total++;
            temp = temp->next;
        }

        // next
        if (pilihan == 1) { 
            index++;
            if (index >= total) {
                index = 0; 
            }
        }

        // previous
        else if (pilihan == 2) {
            index--;
            if (index < 0) {
                index = total - 1;
            }
        }

        // pinjam
        else if (pilihan == 3) {

            if (!current->data.Tersedia) {
                cout << "Buku tidak tersedia." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }

            Pinjaman pinjam;

            cin.ignore();
            while (true){
                cout << "Masukkan nama peminjam > ";
                getline(cin, pinjam.nama);

                if (pinjam.nama.empty() || pinjam.nama.length() < 2) {
                    cout << "Input tidak valid! Nama tidak boleh kosong." << endl;
                    continue;
                } else {
                    break;
                }
            }

            while (true) {
                cout << "Masukkan NIM peminjam > ";
                cin >> pinjam.nim;

                if (cin.fail() || pinjam.nim <= 0) {
                    cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                    clearError();
                    continue;
                } else {
                    break;
                }
            }

            pinjam.judul = current->data.judul;
            pinjam.idBuku = current->data.id;
            pinjam.tanggal = TanggalSekarang();

            static int nomor = 1;
            pinjam.id = generateIDPinjam(current->data, pinjam.nama, nomor);

            nomor++;
            enqueuePinjam(pinjam);

            cout << endl;
            cout << "Permintaan pinjaman telah berhasil dibuat !!" << endl;

            cout << "--------------------------------------" << endl;
            cout << "Id : " << pinjam.id << endl;
            cout << "Judul : " << pinjam.judul << endl;
            cout << "Nama : " << pinjam.nama << endl;
            cout << "NIM : " << pinjam.nim << endl;
            cout << "Tanggal : " << pinjam.tanggal << endl;
            cout << "--------------------------------------" << endl;

            cout << "Menunggu persetujuan pegawai" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }

        else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}


 
// ============ main program ============
int main() {
    int pilihanUtama; //untuk membuat pilihan utamanya

    while (true) {

        // untuk pilihan utama
        while(true){
            welcomeMSG();
            cout << "> ";
            cin >> pilihanUtama;

            if (cin.fail() || pilihanUtama < 0 || pilihanUtama > 2) {
                cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                clearError();
                continue;
            } else {
                break;
            }
        }

        if (pilihanUtama == 0) {
            cout << "Terima kasih telah menggunakan program ini." << endl;
            break;
        }

        else if (pilihanUtama == 1) {  //admin

            int pilihanAdmin;

            while (true) {

                while(true){
                    menuAdmin();
                    cout << "> ";
                    cin >> pilihanAdmin;

                    if (cin.fail() || pilihanAdmin < 0 || pilihanAdmin > 6) {
                        cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                        clearError();
                        continue;
                    } else {
                        break;
                    }
                }


                if (pilihanAdmin == 0) {
                    break;
                }

                else if (pilihanAdmin == 1) {
                    addBuku();
                }

                else if (pilihanAdmin == 2) {
                    tampilanAdmin();
                }

                else if (pilihanAdmin == 3) {
                    editBuku();
                }

                else if (pilihanAdmin == 4) {
                    deleteBuku();
                }

                else if (pilihanAdmin == 5) {
                    prosesPinjaman();
                }

                else if (pilihanAdmin == 6) {
                    prosesPengembalian();
                }
            }
        }

        else if (pilihanUtama == 2) {  // Pengunjung
            int pilihanPengguna;
            while(true){

                while(true){
                    cout << endl;
                    cout << "======================================" << endl;
                    cout << "         DASHBOARD PENGGUNA" << endl;
                    cout << "======================================" << endl;
                    cout << "1. Daftar Buku" << endl;
                    cout << "2. Riwayat Pinjaman" << endl;
                    cout << "0. Kembali" << endl;
                    cout << "> ";
                    cin >> pilihanPengguna;
    
                    if (cin.fail() || pilihanPengguna < 0 || pilihanPengguna > 2) {
                        cout << "Input tidak valid! Harap masukkan angka dengan benar." << endl;
                        clearError();
                        continue;
                    } else {
                        break;
                    }
                }
    
                if (pilihanPengguna == 0) {
                    break;
                }
    
                else if (pilihanPengguna == 1) {  
                    tampilanPengunjung();
    
                }
    
                else if (pilihanPengguna == 2) { 
                    riwayatPinjaman();
                }
            }
        }
    }



    return 0;
}