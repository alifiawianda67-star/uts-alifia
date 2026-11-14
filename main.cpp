#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// ==========================================
// STRUCT DATA MAHASISWA
// ==========================================

struct Mahasiswa {
	string nim;
	string nama;
	float tugas, kehadiran, uts, uas;
	float mutuAngka;
	char mutu;
};

// ==========================================
// STRUCT NODE
// ==========================================

struct Node {
	Mahasiswa data;
	Node* next;
	Node* prev;
};

// ==========================================
// CLASS LINKED LIST
// ==========================================

class LinkedList {
private:
	Node* head;
	Node* tail;
	int jumlah;
	int jenis;

	// Mengatur Circular Linked List
	void perbaruiCircular() {
		if (jenis == 3 && tail != NULL) {
			tail->next = head;
		}
	}

	// Menghitung nilai akhir dan mutu
	void hitungMutu(Mahasiswa &m) {
		m.mutuAngka =
			(m.tugas * 0.20f) +
			(m.kehadiran * 0.15f) +
			(m.uts * 0.30f) +
			(m.uas * 0.35f);

		if (m.mutuAngka < 45)
			m.mutu = 'E';
		else if (m.mutuAngka < 55)
			m.mutu = 'D';
		else if (m.mutuAngka < 65)
			m.mutu = 'C';
		else if (m.mutuAngka < 75)
			m.mutu = 'B';
		else
			m.mutu = 'A';
	}

	// Membuat node baru
	Node* buatNode(const Mahasiswa &m) {
		Node* baru = new Node;

		baru->data = m;
		baru->next = NULL;
		baru->prev = NULL;

		return baru;
	}

public:

	// Constructor
	LinkedList(int tipe) {
		head = NULL;
		tail = NULL;
		jumlah = 0;
		jenis = tipe;
	}

	// Destructor
	~LinkedList() {
		if (jenis == 3 && tail != NULL) {
			tail->next = NULL;
		}

		Node* bantu = head;

		while (bantu != NULL) {
			Node* hapus = bantu;
			bantu = bantu->next;
			delete hapus;
		}

		head = NULL;
		tail = NULL;
	}

	// ======================================
	// INPUT DATA MAHASISWA
	// ======================================

	Mahasiswa inputMahasiswa() {
		Mahasiswa m;

		cout << "\nMasukkan NIM             : ";
		cin >> m.nim;

		cout << "Masukkan Nama            : ";
		getline(cin >> ws, m.nama);

		do {
			cout << "Nilai Tugas (0-100)      : ";
			cin >> m.tugas;
		} while (m.tugas < 0 || m.tugas > 100);

		do {
			cout << "Nilai Kehadiran (0-100)  : ";
			cin >> m.kehadiran;
		} while (m.kehadiran < 0 || m.kehadiran > 100);

		do {
			cout << "Nilai UTS (0-100)        : ";
			cin >> m.uts;
		} while (m.uts < 0 || m.uts > 100);

		do {
			cout << "Nilai UAS (0-100)        : ";
			cin >> m.uas;
		} while (m.uas < 0 || m.uas > 100);

		hitungMutu(m);

		return m;
	}

	// ======================================
	// SISIP DEPAN
	// ======================================

	void sisipDepan(const Mahasiswa &m) {
		Node* baru = buatNode(m);

		if (head == NULL) {
			head = tail = baru;
		}
		else {
			baru->next = head;

			if (jenis == 2) {
				head->prev = baru;
			}

			head = baru;
		}

		perbaruiCircular();
		jumlah++;

		cout << "\nData berhasil disisipkan di depan.\n";
	}

	// ======================================
	// SISIP BELAKANG
	// ======================================

	void sisipBelakang(const Mahasiswa &m) {
		Node* baru = buatNode(m);

		if (head == NULL) {
			head = tail = baru;
		}
		else {
			tail->next = baru;

			if (jenis == 2) {
				baru->prev = tail;
			}

			tail = baru;
		}

		perbaruiCircular();
		jumlah++;

		cout << "\nData berhasil disisipkan di belakang.\n";
	}

	// ======================================
	// SISIP TENGAH
	// ======================================

	void sisipTengah(const Mahasiswa &m, int posisi) {
		if (posisi < 1 || posisi > jumlah + 1) {
			cout << "\nPosisi tidak valid.\n";
			return;
		}

		if (posisi == 1) {
			sisipDepan(m);
			return;
		}

		if (posisi == jumlah + 1) {
			sisipBelakang(m);
			return;
		}

		Node* sebelum = head;

		for (int i = 1; i < posisi - 1; i++) {
			sebelum = sebelum->next;
		}

		Node* baru = buatNode(m);

		baru->next = sebelum->next;
		sebelum->next = baru;

		if (jenis == 2) {
			baru->prev = sebelum;
			baru->next->prev = baru;
		}

		jumlah++;

		cout << "\nData berhasil disisipkan pada posisi "
			<< posisi << ".\n";
	}

	// ======================================
	// HAPUS DEPAN
	// ======================================

	void hapusDepan() {
		if (head == NULL) {
			cout << "\nLinked List masih kosong.\n";
			return;
		}

		Node* hapus = head;

		if (head == tail) {
			head = NULL;
			tail = NULL;
		}
		else {
			head = head->next;

			if (jenis == 2) {
				head->prev = NULL;
			}
		}

		delete hapus;

		jumlah--;
		perbaruiCircular();

		cout << "\nData paling depan berhasil dihapus.\n";
	}

	// ======================================
	// HAPUS BELAKANG
	// ======================================

	void hapusBelakang() {
		if (head == NULL) {
			cout << "\nLinked List masih kosong.\n";
			return;
		}

		if (head == tail) {
			delete head;
			head = NULL;
			tail = NULL;
		}
		else {
			Node* sebelum = head;

			while (sebelum->next != tail) {
				sebelum = sebelum->next;
			}

			delete tail;

			tail = sebelum;
			tail->next = NULL;
		}

		jumlah--;
		perbaruiCircular();

		cout << "\nData paling belakang berhasil dihapus.\n";
	}

	// ======================================
	// HAPUS TENGAH
	// ======================================

	void hapusTengah(int posisi) {
		if (head == NULL) {
			cout << "\nLinked List masih kosong.\n";
			return;
		}

		if (posisi < 1 || posisi > jumlah) {
			cout << "\nPosisi tidak valid.\n";
			return;
		}

		if (posisi == 1) {
			hapusDepan();
			return;
		}

		if (posisi == jumlah) {
			hapusBelakang();
			return;
		}

		Node* sebelum = head;

		for (int i = 1; i < posisi - 1; i++) {
			sebelum = sebelum->next;
		}

		Node* hapus = sebelum->next;

		sebelum->next = hapus->next;

		if (jenis == 2) {
			hapus->next->prev = sebelum;
		}

		delete hapus;

		jumlah--;
		perbaruiCircular();

		cout << "\nData pada posisi " << posisi
			<< " berhasil dihapus.\n";
	}

	// ======================================
	// TAMPILKAN DATA MAHASISWA
	// ======================================

	void tampilkanData() {
		if (head == NULL) {
			cout << "\nBelum ada data mahasiswa.\n";
			return;
		}

		cout << "\n";
		cout << "================ DATA MAHASISWA ================\n";

		cout << left
			<< setw(4) << "No"
			<< setw(15) << "NIM"
			<< setw(22) << "Nama"
			<< setw(9) << "Tugas"
			<< setw(9) << "Hadir"
			<< setw(9) << "UTS"
			<< setw(9) << "UAS"
			<< setw(13) << "Mutu Angka"
			<< "Mutu\n";

		cout << string(100, '-') << "\n";

		Node* bantu = head;
		int nomor = 1;

		while (bantu != NULL) {
			cout << left
				<< setw(4) << nomor++
				<< setw(15) << bantu->data.nim
				<< setw(22) << bantu->data.nama
				<< setw(9) << fixed << setprecision(2)
				<< bantu->data.tugas
				<< setw(9) << bantu->data.kehadiran
				<< setw(9) << bantu->data.uts
				<< setw(9) << bantu->data.uas
				<< setw(13) << bantu->data.mutuAngka
				<< bantu->data.mutu << "\n";

			bantu = bantu->next;

			if (jenis == 3 && bantu == head) {
				break;
			}
		}

		cout << "------------------------------------------------\n";
		cout << "Jumlah data mahasiswa: " << jumlah << "\n";
	}
};

// ==========================================
// MENU UTAMA
// ==========================================

void tampilMenuUtama() {
	cout << "\n========== MENU UTAMA ==========\n";
	cout << "1. Single Linked List\n";
	cout << "2. Double Linked List\n";
	cout << "3. Circular Linked List\n";
	cout << "4. Keluar\n";
	cout << "Pilih menu: ";
}

// ==========================================
// SUB MENU
// ==========================================

void jalankanSubMenu(int jenis) {
	LinkedList daftar(jenis);

	char pilih;
	bool kembali = false;

	while (!kembali) {

		cout << "\n========== SUB MENU ==========\n";
		cout << "a. Input Data Mahasiswa\n";
		cout << "b. Sisip Depan\n";
		cout << "c. Sisip Tengah\n";
		cout << "d. Sisip Belakang\n";
		cout << "e. Hapus Depan\n";
		cout << "f. Hapus Tengah\n";
		cout << "g. Hapus Belakang\n";
		cout << "h. Tampilkan Data Mahasiswa\n";
		cout << "i. Kembali ke Menu Utama\n";

		cout << "Pilih menu: ";
		cin >> pilih;

		Mahasiswa m;
		int posisi;
		int banyak;

		switch (pilih) {

		case 'a':
		case 'A':

			cout << "Jumlah mahasiswa yang akan diinput: ";
			cin >> banyak;

			if (banyak <= 0) {
				cout << "Jumlah harus lebih dari 0.\n";
				break;
			}

			for (int i = 1; i <= banyak; i++) {
				cout << "\nInput mahasiswa ke-" << i << "\n";

				m = daftar.inputMahasiswa();
				daftar.sisipBelakang(m);
			}

			break;

		case 'b':
		case 'B':

			m = daftar.inputMahasiswa();
			daftar.sisipDepan(m);

			break;

		case 'c':
		case 'C':

			m = daftar.inputMahasiswa();

			cout << "Masukkan posisi penyisipan: ";
			cin >> posisi;

			daftar.sisipTengah(m, posisi);

			break;

		case 'd':
		case 'D':

			m = daftar.inputMahasiswa();
			daftar.sisipBelakang(m);

			break;

		case 'e':
		case 'E':

			daftar.hapusDepan();

			break;

		case 'f':
		case 'F':

			cout << "Masukkan posisi data yang dihapus: ";
			cin >> posisi;

			daftar.hapusTengah(posisi);

			break;

		case 'g':
		case 'G':

			daftar.hapusBelakang();

			break;

		case 'h':
		case 'H':

			daftar.tampilkanData();

			break;

		case 'i':
		case 'I':

			kembali = true;

			cout << "\nKembali ke menu utama.\n";

			break;

		default:

			cout << "\nPilihan tidak valid. Pilih a sampai i.\n";
		}
	}
}

// ==========================================
// PROGRAM UTAMA
// ==========================================

int main() {
	int pilih;

	do {
		tampilMenuUtama();

		cin >> pilih;

		switch (pilih) {

		case 1:

			cout << "\nAnda memilih SINGLE LINKED LIST.\n";
			jalankanSubMenu(1);

			break;

		case 2:

			cout << "\nAnda memilih DOUBLE LINKED LIST.\n";
			jalankanSubMenu(2);

			break;

		case 3:

			cout << "\nAnda memilih CIRCULAR LINKED LIST.\n";
			jalankanSubMenu(3);

			break;

		case 4:

			cout << "\nProgram selesai. Terima kasih.\n";

			break;

		default:

			cout << "\nPilihan tidak valid. Masukkan angka 1 sampai 4.\n";
		}

	} while (pilih != 4);

	return 0;
}
