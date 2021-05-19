#include "class.cpp"

Admin admin;
Pelanggan pelanggan;

// ========= MENU UMUM ===========

void main_menu();
void menu_login();
void menu_register();
bool check_login(std::string name, std::string pw, char &stats);
bool same_name_password(std::string name, std::string pw);

// ================================


// ========= MENU ADMIN ===========

void main_menu_admin();
void menu_kelola_inventori();
void tambah_inventori();
void undo_inventori();
void lihat_inventori();
void batal_inventori();
void simpan_inventori();

void menu_kelola_pelanggan();
void ubah_status_pesanan(int y, std::string status);

// ================================


// ======== MENU PELANGGAN ========

void print_list(int titikX, int titikY, int &lastY);
void main_menu_pelanggan();
void menu_pesan_barang();
void tambah_keranjang();
void lihat_keranjang();
void hapus_keranjang();
void simpan_pesanan();
void riwayat_pesanan();

// ================================