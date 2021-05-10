#include "functions.hpp"

void main_menu()
{
    system("cls");

    int pil;
    gotoxy(50, 10); std::cout << "MAIN MENU";
    gotoxy(50, 11); std::cout << "1. Login";
    gotoxy(50, 12); std::cout << "2. Register";
    gotoxy(50, 13); std::cout << "Pilihan = "; std::cin >> pil;
}

void menu_login()
{
    char status;
    std::string username, password;
    gotoxy(50, 10); std::cout << "Username : "; std::cin >> username;
    gotoxy(50, 11); std::cout << "Password : "; std::cin >> password;
    if(check_login(username, password, status))
    {
        if(status == 'P')
        {
            
        }

        else
        {

        }
    }

    else
    {
        gotoxy(50, 10); std::cout << "Username/Password anda salah!";
        gotoxy(50, 11); std::cout << "Mohon menunggu untuk kembali ke menu utama";
        Sleep(500);
        main_menu();
    }
}

void menu_register()
{
    std::string username, password, sebagai;
    int pil;
    gotoxy(50, 10); std::cout << "Daftar Peran:";
    gotoxy(50, 11); std::cout << "1. Pelanggan      2. Admin";
    gotoxy(50, 12); std::cout << "Pilihan : "; std::cin >> pil;

    switch(pil)
    {
        case 1:
            sebagai = "Pelanggan";
            break;
        
        case 2:
            sebagai = "Admin";
            break;

        default:
            gotoxy(50, 10); std::cout << "Yang anda pilih tidak ada dalam pilihan";
            gotoxy(50, 11); std::cout << "Silahkan coba lagi";
            Sleep(500);
            menu_register();
            break;
    }

    gotoxy(50, 13); std::cout << "Username : "; std::cin >> username;
    gotoxy(50, 14); std::cout << "Password : "; std::cin >> password;

    system("cls");


    if(same_name_password(username, password))
    {
        gotoxy(50, 10); std::cout << "Register Berhasil";
        gotoxy(50, 11); std::cout << "Mohon menunggu untuk kembali ke menu utama";
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
        gotoxy(50, 10); std::cout << "Username/Password yang anda masukkan sudah pernah digunakan";
        gotoxy(50, 11); std::cout << "Mohon kembali ke menu utama";
        Sleep(500);
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
            if(name == nameKey)
            { return true; }

            if(pw == pwKey)
            { return true; }
        }
    database.close();
    return false;
}