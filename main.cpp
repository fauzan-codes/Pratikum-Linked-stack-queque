#include <iostream>
#include <string>
#include <limits>
#include <thread>
using namespace std;



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

void clearError() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    this_thread::sleep_for(std::chrono::seconds(1));
}


void welcomeMSG() {
    cout << endl;
    cout << "===========================" << endl;
    cout << "          Welcome          " << endl;
    cout << "===========================" << endl;
    cout << "1. Masuk sebagai pegawai" << endl;
    cout << "2. Masuk sebagai pengunjung" << endl;
    cout << "0. Keluar" << endl << endl;
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
    cout << "0. Keluar" << endl << endl;
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

string generateID(string judul, int tahunTerbit) {
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

    cin.ignore();
    cout << "Masukkan judul buku: ";
    getline(cin, bukuBaru.judul);

    cout << "Masukkan penulis buku: ";
    getline(cin, bukuBaru.penulis);

    while (true) {
        cout << "Masukkan tahun terbit buku: ";
        cin >> bukuBaru.tahunTerbit;

        if (cin.fail() || bukuBaru.tahunTerbit < 1000 || bukuBaru.tahunTerbit > 2026) {
            cout << endl << "Input tidak valid! Harap masukkan angka." << endl << endl;
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
    bukuBaru.id = generateID(bukuBaru.judul, bukuBaru.tahunTerbit);

    insertBuku(bukuBaru);

    cout << "Buku berhasil ditambahkan!" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
}


void deleteBuku() {

    if (head == NULL) {
        cout << "Belum ada data buku." << endl;
        return;
    }

    string idHapus;
    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin >> idHapus;

    Node* current = head;
    Node* prev = NULL;

    if (current != NULL && current->data.id == idHapus) {
        head = current->next;
        delete current;
        cout << "Buku berhasil dihapus." << endl;
        this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    // Cari node yang ingin dihapus
    while (current != NULL && current->data.id != idHapus) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "ID tidak ditemukan." << endl;
        this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    prev->next = current->next;
    delete current;

    cout << "Buku berhasil dihapus." << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
}


void editBuku() {

    if (head == NULL) {
        cout << "Belum ada data buku." << endl;
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
        this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    cin.ignore();
    cout << "Masukkan judul baru: ";
    getline(cin, current->data.judul);

    cout << "Masukkan penulis baru: ";
    getline(cin, current->data.penulis);
    
    while (true) {
        int tahun;
        cout << "Masukkan tahun terbit baru: ";
        cin >> tahun;
        if (cin.fail() || tahun < 1000 || tahun > 2026) {
            cout << endl << "Input tidak valid! Harap masukkan angka." << endl << endl;
            clearError();
            continue;
        } else {
            current->data.tahunTerbit = tahun;
            break;
        }
    }

    cin.ignore();
    cout << "Masukkan genre baru: ";
    getline(cin, current->data.genre);

    // perbarui id yg data yg berubah
    current->data.id = generateID(current->data.judul, current->data.tahunTerbit);

    cout << "Data buku berhasil diubah!" << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
}




// tampilan
void tampilSemua() {

    if (head == NULL) {
        cout << "Belum ada data buku." << endl;
        return;
    }

    Node* current = head;

    while (current != NULL) {
        cout << "----------------------" << endl;
        cout << "ID      : " << current->data.id << endl;
        cout << "Judul   : " << current->data.judul << endl;
        cout << "Penulis : " << current->data.penulis << endl;
        cout << "Tahun   : " << current->data.tahunTerbit << endl;
        cout << "Genre   : " << current->data.genre << endl;
        cout << "Status  : "
             << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia") 
             << endl;

        current = current->next;
    }
}



// =========== menu pengunjung ===========
void menuPengunjungAksi() {

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
        cout << "\n--------------------------------------" << endl;
        cout << "Judul : " << current->data.judul << endl;
        cout << "Id : " << current->data.id << endl;
        cout << "Penulis : " << current->data.penulis << endl;
        cout << "Tahun : " << current->data.tahunTerbit << endl;
        cout << "Genre : " << current->data.genre << endl;
        cout << "Ketersediaan : "
             << (current->data.Tersedia ? "Tersedia" : "Tidak Tersedia")
             << endl;
        cout << "--------------------------------------" << endl;

        while(true){
            cout << "1. Selanjutnya" << endl;
            cout << "2. Sebelumnya" << endl;
            cout << "3. Pinjam" << endl;
            cout << "0. Keluar" << endl;
            cout << "> ";
            cin >> pilihan;

            if (cin.fail() || pilihan < 0 || pilihan > 3) {
                cout << "Input tidak valid! Harap masukkan angka." << endl;
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
            cout << "Fitur peminjaman belum tersedia." << endl;
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
            cout << "Masukkan pilihan: ";
            cin >> pilihanUtama;

            if (cin.fail() || pilihanUtama < 0 || pilihanUtama > 2) {
                cout << "Input tidak valid! Harap masukkan angka." << endl;
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

                // untuk pilihan admin
                while(true){
                    menuAdmin();
                    cout << "Masukkan pilihan: ";
                    cin >> pilihanAdmin;

                    if (cin.fail() || pilihanAdmin < 0 || pilihanAdmin > 4) {
                        cout << "Input tidak valid! Harap masukkan angka." << endl;
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
                    tampilSemua();

                    string enter;
                    cout << endl << "Tekan Enter untuk kembali ke menu utama...";
                    cin.ignore();
                    getline(cin, enter); 
                }

                else if (pilihanAdmin == 3) {
                    editBuku();
                }

                else if (pilihanAdmin == 4) {
                    deleteBuku();
                }
            }
        }

        else if (pilihanUtama == 2) {  // Pengunjung
            menuPengunjungAksi();
        }
    }




    return 0;
}