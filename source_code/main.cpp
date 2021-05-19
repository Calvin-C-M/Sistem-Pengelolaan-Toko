#include "menu_user.hpp"

int main()
{
    main_menu();
}


void main_menu()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "MAIN MENU";
    gotoxy(initialX, initialY+1); std::cout << "1. Login";
    gotoxy(initialX, initialY+2); std::cout << "2. Register";
    gotoxy(initialX, initialY+3); std::cout << "3. Keluar";
    gotoxy(initialX, initialY+4); std::cout << "Pilihan = "; std::cin >> pil;

    system("cls");
    switch(pil)
    {
        case 1:
            menu_login();
            break;

        case 2:
            menu_register();
            break;

        case 3:
            gotoxy(initialX, initialY); std::cout << "Terima kasih";
            return;
            break;

        default:
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan pilih kembali";
            Sleep(1500);
            main_menu();
            break;
    }
}

void menu_login()
{
    char status;
    std::string username, password;
    gotoxy(initialX, initialY); std::cout << "Username : "; std::cin >> username;
    gotoxy(initialX, initialY+1); std::cout << "Password : "; std::cin >> password;
    if(check_login(username, password, status))
    {
        if(status == 'P')
        {
            pelanggan.get_data(username);
            main_menu_pelanggan();
        }

        else
        {
            admin.get_data(username);
            main_menu_admin();
        }
    }

    else
    {
        gotoxy(initialX, initialY); std::cout << "Username/Password anda salah!";
        gotoxy(initialX, initialY+1); std::cout << "Mohon menunggu untuk kembali ke menu utama";
        Sleep(1500);
        main_menu();
    }
}

void menu_register()
{
    std::string username, password, sebagai;
    int pil;
    gotoxy(initialX, initialY); std::cout << "Daftar Peran:";
    gotoxy(initialX, initialY+1); std::cout << "1. Pelanggan      2. Admin";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan : "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            sebagai = "Pelanggan";
            break;
        
        case 2:
            sebagai = "Admin";
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); std::cout << "Yang anda pilih tidak ada dalam pilihan";
            gotoxy(initialX, initialY+1); std::cout << "Silahkan coba lagi";
            Sleep(1500);
            menu_register();
            break;
    }

    gotoxy(initialX, initialY+3); std::cout << "Username : "; std::cin >> username;
    gotoxy(initialX, 14); std::cout << "Password : "; std::cin >> password;

    system("cls");


    if(!same_name_password(username, password))
    {
        gotoxy(initialX, initialY); std::cout << "Register Berhasil";
        gotoxy(initialX, initialY+1); std::cout << "Mohon menunggu untuk kembali ke menu utama";
        // Masukkin data ke database
        if(sebagai == "Admin")
        { admin.insert_data(username, password); }
        else
        { pelanggan.insert_data(username, password); }
        Sleep(1000);
        main_menu();
    }

    else
    {
        gotoxy(initialX, initialY); std::cout << "Username/Password yang anda masukkan sudah pernah digunakan";
        gotoxy(initialX, initialY+1); std::cout << "Mohon kembali ke menu utama";
        Sleep(1500);
        main_menu();
    }
}

bool check_login(std::string name, std::string pw, char &stats)
{
    char key;
    std::string nameKey, pwKey;
    std::ifstream database;
    database.open("Login.txt");
        while(!database.eof())
        {
            database >> key >> nameKey >> pwKey;
            if(name == nameKey && pw == pwKey)
            {
                stats = key;
                return true;
            }
        }
    database.close();
    return false;
}

bool same_name_password(std::string name, std::string pw)
{
    char key;
    std::string nameKey, pwKey;
    std::ifstream database;
    database.open("Login.txt");
        while(!database.eof())
        {
            database >> key >> nameKey >> pwKey;
            if(name == nameKey || pw == pwKey)
            { return true; }
        }
    database.close();
    return false;
}

// MENU ADMIN
void main_menu_admin()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "1. Kelola Inventori";
    gotoxy(initialX, initialY+1); std::cout << "2. Kelola Pelanggan";
    gotoxy(initialX, initialY+2); std::cout << "3. Logout";
    gotoxy(initialX, initialY+3); std::cout << "Pilihan: "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            menu_kelola_inventori();
            break;

        case 2:
            menu_kelola_pelanggan();
            break;

        case 3:
            main_menu();
            break;

        default:
            gotoxy(initialX, initialY+3); std::cout << "Ada kesalahan dalam memilih, silahkan coba lagi";
            Sleep(1500);
            main_menu_admin();
            break;
    }
}

void menu_kelola_inventori()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "1. Tambah Barang      4. Keluar dan batalkan";
    gotoxy(initialX, initialY+1); std::cout << "2. Undo             5. Keluar dan simpan inventori";
    gotoxy(initialX, initialY+2); std::cout << "3. Lihat Barang";
    gotoxy(initialX, initialY+3); std::cout << "Pilihan =  "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            tambah_inventori();
            break;

        case 2:
            undo_inventori();
            break;

        case 3:
            lihat_inventori();
            break;

        case 4:
            batal_inventori();
            break;

        case 5:
            simpan_inventori();
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan coba lagi";
            Sleep(1500);
            menu_kelola_inventori();
            break;
    }
}

void tambah_inventori()
{
    system("cls");
    
    std::string namaBarang;
    int jumlahBarang;
    long int hargaSatuan;

    gotoxy(initialX, initialY); std::cout << "Nama Barang: "; std::cin >> namaBarang;
    gotoxy(initialX, initialY+1); std::cout << "Jumlah: "; std::cin >> jumlahBarang;
    gotoxy(initialX, initialY+2); std::cout << "Harga Satuan: Rp"; std::cin >> hargaSatuan;

    pInvent pNew;
    admin.create_element_stack(pNew, namaBarang, jumlahBarang, hargaSatuan);
    admin.push_stack_inventori(pNew);

    system("pause");

    menu_kelola_inventori();
}

void undo_inventori()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "Apakah anda yakin?";
    gotoxy(initialX, initialY+1); std::cout << "1. Iya      2. Tidak";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan = "; std::cin >> pil;

    system("cls");
    switch(pil)
    {
        case 1:
            admin.pop_stack();
            gotoxy(initialX, initialY); std::cout << "Data berhasil diundo";
            Sleep(1500);
            menu_kelola_inventori();
            break;
        
        case 2:
            gotoxy(initialX, initialY); std::cout << "Silahkan kembali ke menu sebelumnya";
            menu_kelola_inventori();
            break;

        default:
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan pilih kembali";
            Sleep(1500);
            undo_inventori();
            break;
    }
}

void lihat_inventori()
{
    system("cls");
    
    gotoxy(initialX, initialY); printf("Nama Barang\t\tJumlah\t\tHarga Satuan");
    admin.print_stack(initialX, initialY+1);

    system("pause");
    menu_kelola_inventori();
}

void batal_inventori()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "Apakah anda yakin?";
    gotoxy(initialX, initialY+1); std::cout << "1. Iya      2. Tidak";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan = "; std::cin >> pil;

    system("cls");
    switch(pil)
    {
        case 1:
            admin.destroy_stack();
            gotoxy(initialX, initialY); std::cout << "Daftar barang berhasil dibatalkan";
            gotoxy(initialX, initialY+1); std::cout << "Silahkan kembali ke menu admin";
            Sleep(1500);
            main_menu_admin();
            break;

        case 2:
            gotoxy(initialX, initialY); std::cout << "Silahkan kembali ke menu sebelumnya";
            Sleep(1500);
            menu_kelola_inventori();
            break;

        default:
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan pilih kembali";
            Sleep(1500);
            batal_inventori();
            break;
    }
}

void simpan_inventori()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "Apakah anda yakin?";
    gotoxy(initialX, initialY+1); std::cout << "1. Iya      2. Tidak";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan = "; std::cin >> pil;

    system("cls");
    switch(pil)
    {
        case 1:
            admin.save_stack();
            admin.destroy_stack();
            gotoxy(initialX, initialY); std::cout << "Barang berhasil ditambahkan ke inventori";
            gotoxy(initialX, initialY+1); std::cout << "Silahkan kembali ke menu admin";
            Sleep(1500);
            main_menu_admin();
            break;

        case 2:
            gotoxy(initialX, initialY); std::cout << "Silahkan kembali ke menu sebelumnya";
            Sleep(1500);
            menu_kelola_inventori();
            break;

        default:
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan pilih kembali";
            Sleep(1500);
            simpan_inventori();
            break;
    }
}

void menu_kelola_pelanggan()
{
    system("cls");
    int lastY;

    admin.create_queue();
    admin.query_pesanan();

    gotoxy(initialX, initialY); printf("Nama Pelanggan\t\tNama Barang\t\tJumlah\t\tTgl\t\tStatus");

    admin.print_queue(initialX, initialY+1, lastY);

    int pil;
    gotoxy(initialX, lastY+1); std::cout << "1. Kirim Barang";
    gotoxy(initialX, lastY+2); std::cout << "2. Barang sudah diterima";
    gotoxy(initialX, lastY+3); std::cout << "3. Tolak Barang";
    gotoxy(initialX, lastY+4); std::cout << "4. Keluar";
    gotoxy(initialX, lastY+5); std::cout << "Pilihan: "; std::cin >> pil;

    std::string stats;
    switch(pil)
    {
        case 1:
            ubah_status_pesanan(lastY+6, "SEDANG DIKIRIM");
            break;

        case 2:
            ubah_status_pesanan(lastY+6, "SUDAH TERKIRIM");
            break;

        case 3:
            ubah_status_pesanan(lastY+6, "PESANAN DITOLAK");
            break;

        case 4:
            admin.destroy_queue();
            main_menu_admin();
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); printf("Ada kesalahan dalam memlih, silahkan coba lagi");
            Sleep(1500);
            menu_kelola_pelanggan();
            break;
    }
}

void ubah_status_pesanan(int y, std::string status)
{
    std::string nama, barang;
    gotoxy(initialX, y+1); std::cout << "Nama Pelanggan: "; std::cin >> nama;
    gotoxy(initialX, y+2); std::cout << "Nama Barang: "; std::cin >> barang;

    pPesanan curr = qPesanan.head;
    while(curr != qPesanan.tail)
    {
        if(curr->namaPelanggan == nama && curr->namaBarang == barang)
        { curr->status = status; }

        curr = curr->next;
    }

    menu_kelola_pelanggan();
}


// MENU PELANGGAN

void print_list(int titikX, int titikY, int &lastY)
{
    std::string nama;
    int jumlah;
    long int harga;

    std::ifstream database;
    database.open("Inventori.txt");
        while(!database.eof())
        {
            database >> nama >> jumlah >> harga;
            gotoxy(titikX, titikY); std::cout << nama << "\t\t\tRp" << harga;
            titikY++;
        }
    database.close();
    lastY = titikY;
}

void main_menu_pelanggan()
{
    int pil;
    gotoxy(initialX, initialY); std::cout << "1. Pesan Barang";
    gotoxy(initialX, initialY+1); std::cout << "2. Riwayat Pesanan";
    gotoxy(initialX, initialY+2); std::cout << "3. Logout";
    gotoxy(initialX, initialY+3); std::cout << "Pilihan: "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            menu_pesan_barang();
            break;

        case 2:
            riwayat_pesanan();
            break;

        case 3:
            main_menu();
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan coba lagi";
            Sleep(1500);
            main_menu_pelanggan();
            break;
    }
}

void menu_pesan_barang()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "1. Tambah Barang";
    gotoxy(initialX, initialY+1); std::cout << "2. Lihat keranjang";
    gotoxy(initialX, initialY+2); std::cout << "3. Batal pesanan";
    gotoxy(initialX, initialY+3); std::cout << "4. Checkout";
    gotoxy(initialX, initialY+4); std::cout << "Plihan: "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            tambah_keranjang();
            break;

        case 2:
            lihat_keranjang();
            break;

        case 3:
            hapus_keranjang();
            break;

        case 4:
            simpan_pesanan();
            break;

        default:
            gotoxy(initialX, initialY); std::cout << "Ada kesalahan dalam memilih, silahkan pilih kembali";
            Sleep(1500);
            menu_pesan_barang();
            break;
    }
}

void tambah_keranjang()
{
    system("cls");

    int lastY;
    gotoxy(initialX, initialY); printf("Nama Barang\t\tHarga Barang");
    print_list(initialX, initialY+1, lastY);

    std::string nama;
    int jumlah;
    int tanggal, bulan, tahun;
    gotoxy(initialX, lastY+1); std::cout << "Nama Barang: "; std::cin >> nama;
    gotoxy(initialX, lastY+2); std::cout << "Jumlah: "; std::cin >> jumlah;
    gotoxy(initialX, lastY+3); std::cout << "Tanggal: "; std::cin >> tanggal;
    gotoxy(initialX, lastY+4); std::cout << "Bulan: "; std::cin >> bulan;
    gotoxy(initialX, lastY+5); std::cout << "Tahun: "; std::cin >> tahun;

    pKeranjang pNew;
    pelanggan.create_element_list(pNew, nama, jumlah, tanggal, bulan, tahun);
    pelanggan.push_list(pNew);

    system("pause");

    menu_pesan_barang();
}

void lihat_keranjang()
{
    system("cls");

    gotoxy(initialX, initialY); printf("Nama Barang\t\tJumlah\t\tTanggal Pesan");
    pelanggan.print_list(initialX, initialY+1);
    system("pause");
    menu_pesan_barang();
}

void hapus_keranjang()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "Apakah anda yakin?";
    gotoxy(initialX, initialY+1); std::cout << "1. Iya      2. Tidak";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan: "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            pelanggan.destroy_list();
            main_menu_pelanggan();
            break;

        case 2:
            menu_pesan_barang();
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); printf("Ada kesalahan dalam memilih, silahkan pilih kembali");
            Sleep(1500);
            menu_pesan_barang();
            break;
    }
}

void simpan_pesanan()
{
    system("cls");

    int pil;
    gotoxy(initialX, initialY); std::cout << "Apakah anda yakin?";
    gotoxy(initialX, initialY+1); std::cout << "1. Iya      2. Tidak";
    gotoxy(initialX, initialY+2); std::cout << "Pilihan: "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            pelanggan.insert_pesanan();
            pelanggan.destroy_list();
            gotoxy(initialX, initialY); printf("Pesanan berhasil ditambahkan, silahkan menunggu barang diantar");
            Sleep(1500);
            main_menu_pelanggan();
            break;

        case 2:
            menu_pesan_barang();
            break;

        default:
            system("cls");
            gotoxy(initialX, initialY); printf("Ada kesalahan dalam memilih, silahkan pilih kembali");
            Sleep(1500);
            menu_pesan_barang();
            break;
    }
}

void riwayat_pesanan()
{
    system("cls");

    gotoxy(initialX, initialY); printf("Nama Barang\t\t\tJumlah\t\tTanggal Pesan");
    pelanggan.query_pesanan(initialX, initialY+1);
    system("pause");
    main_menu_pelanggan();
}