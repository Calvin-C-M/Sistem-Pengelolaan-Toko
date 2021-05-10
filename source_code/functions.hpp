#include <conio.h>
#include <windows.h>

#include "class.cpp"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

Admin admin;
Pelanggan pelanggan;

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

void menu_login();
void menu_register();
bool check_login(std::string name, std::string pw, char &stats);
bool same_name_password(std::string name, std::string pw);