#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

const int initialX = 50;
const int initialY = 10;

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

struct nodeInventori
{
    std::string namaBarang;
    int jumlah;
    long int harga;

    nodeInventori *next;
};

typedef nodeInventori *pInvent;
typedef pInvent stackInventori;

stackInventori topStack = nullptr;

struct nodePesanan
{
    std::string namaPelanggan, namaBarang, status;
    int jumlah;
    int tgl, bln, thn;

    nodePesanan *next;
};
typedef nodePesanan *pPesanan;

struct queue
{
    pPesanan head, tail;
};
queue qPesanan;

class Admin
{
    private:
    

    public:
    std::string username, password, name;
    void insert_data(std::string login, std::string pw)
    {
        std::ofstream database;
        database.open("Login.txt", std::ios::app);
            database << "\nA" << "\t\t" << login << "\t\t" << pw;
        database.close();
        
    }

    void get_data(std::string name)
    {
        char key;
        std::string pwKey;
        std::ifstream database;
        database.open("Login.txt");
            while(!database.eof())
            {
                database >> key >> username >> pwKey;
                if(username == name)
                { password = pwKey; }
            }
        database.close();
    }

    bool stack_inventori_empty()
    { return topStack == nullptr; }

    void create_element_stack(pInvent &pNew, std::string nama, int jumlah, long int harga)
    {
        pNew = new nodeInventori;
        pNew->namaBarang = nama;
        pNew->jumlah = jumlah;
        pNew->harga = harga;
        pNew->next = nullptr;
    }

    void push_stack_inventori(pInvent newElement)
    {
        if(stack_inventori_empty())
        { topStack = newElement; }

        else
        {
            newElement->next = topStack;
            topStack = newElement;
        }
    }

    void pop_stack()
    {
        pInvent pDel = new nodeInventori;
        if(stack_inventori_empty())
        { pDel = nullptr; }

        else if(topStack->next == nullptr)
        {
            pDel = topStack;
            topStack = nullptr;
        }

        else
        {
            pDel = topStack;
            topStack = topStack->next;
            pDel->next = nullptr;
        }

        delete pDel;
    }

    void print_stack(int titikX, int titikY)
    {
        pInvent curr = topStack;
        int x=titikX, y=titikY;

        while(curr != nullptr)
        {
            gotoxy(x, y); std::cout << curr->namaBarang << "\t\t\t" << curr->jumlah << "\t\tRp" << curr->harga;
            y++; // Iterasi titik y
            curr = curr->next; // Iterasi current node
        }
    }

    void destroy_stack()
    {
        if(stack_inventori_empty())
        { topStack = nullptr; }

        else
        {
            pInvent curr = topStack, tempNode = nullptr;
            while(curr != nullptr)
            {
                tempNode = curr->next;
                delete curr;
                curr = tempNode;
            }
            topStack = nullptr;
        }
    }

    void save_stack()
    {
        std::ofstream database;
        database.open("Inventori.txt", std::ios::app);
            pInvent curr = topStack;
            while(curr != nullptr)
            {
                database << "\n" << curr->namaBarang << "\t\t"
                                 << curr->jumlah << "\t\t"
                                 << curr->harga;
                
                curr = curr->next;
            }
        database.close();
    }

    void create_queue()
    {
        qPesanan.head = nullptr;
        qPesanan.tail = nullptr;
    }

    void create_element_queue(pPesanan &pNew, std::string name, std::string namaBarang, int jumlah, int tgl, int bln, int thn, std::string status)
    {
        pNew = new nodePesanan;
        pNew->namaPelanggan = name;
        pNew->namaBarang = namaBarang;
        pNew->jumlah = jumlah;
        pNew->tgl = tgl;
        pNew->bln = bln;
        pNew->thn = thn;
        pNew->status = status;
        pNew->next = nullptr;
    }

    bool is_empty()
    { return (qPesanan.head==nullptr && qPesanan.tail == nullptr); }

    void enqueue(pPesanan pNew)
    {
        if(is_empty())
        {
            qPesanan.head = pNew;
            qPesanan.tail = pNew;
        }

        else
        {
            pPesanan curr = qPesanan.head;
            pPesanan pRev = nullptr;
            while(pNew->tgl >= curr->tgl)
            {
                if(curr->next == nullptr)
                { break; }
                pRev = curr;
                curr = curr->next;
            }

            if(
                curr == qPesanan.head &&
                pNew->tgl < curr->tgl
            )
            {
                pNew->next = curr;
                qPesanan.head = pNew;
            }

            else if(
                curr == qPesanan.tail &&
                pNew->tgl > curr->tgl
            )
            {
                curr->next = pNew;
                qPesanan.tail = pNew;
            }

            else
            {
                pRev->next = pNew;
                pNew->next = curr;
            }
        }
    }

    void dequeu()
    {
        pPesanan pDel;

        if(is_empty())
        { pDel = nullptr; }

        else if(qPesanan.head->next == nullptr)
        {
            pDel = qPesanan.head;
            qPesanan.head = nullptr;
            qPesanan.tail = nullptr;
        }

        else
        {
            pDel = qPesanan.head;
            qPesanan.head = qPesanan.head->next;
            pDel->next = nullptr;
            delete pDel;
        }
    }

    void query_pesanan()
    {
        std::string nameKey, namaB, status;
        int jumlah, tgl, bln, thn;

        std::ifstream database;
        database.open("Pesanan.txt");
            while(!database.eof())
            {
                database >> nameKey >> namaB >> jumlah >> tgl >> bln >> thn >> status;

                if(status == "SUDAH DIKIRIM")
                { continue; }

                pPesanan pNew;
                create_element_queue(pNew, nameKey, namaB, jumlah, tgl, bln, thn, status);
                enqueue(pNew);
            }
        database.close();
    }

    void print_queue(int x, int y, int &lastY)
    {
        pPesanan curr = qPesanan.head;
        while(curr != qPesanan.tail)
        {
            gotoxy(x, y); printf("%s\t\t%s\t\t%d\t\t%d/%d/%d\t\t%s", curr->namaPelanggan, curr->namaBarang, curr->jumlah, curr->tgl, curr->bln, curr->thn, curr->status);
            y++;
            curr = curr->next;
        }
        lastY = y;
    }

    void ubah_pesanan()
    {
        std::ofstream database;
        database.open("Pesanan.txt");
            pPesanan curr = qPesanan.head;
            while(curr != qPesanan.tail)
            {
                database << "\n" << username << "\t\t\t" 
                                 << curr->namaBarang << "\t\t\t" 
                                 << curr->jumlah << "\t\t" 
                                 << curr->tgl << "\t"
                                 << curr->bln << '\t'
                                 << curr->thn << "\t\t"
                                 << curr->status;

                curr = curr->next;
            }
        database.close();
    }

    void destroy_queue()
    {
        if(qPesanan.head != nullptr)
        {
            pPesanan curr = qPesanan.head, temp = nullptr;
            while(curr != qPesanan.tail)
            {
                temp = curr->next;
                delete curr;
                curr = temp;
            }
        }
    }
};

struct nodeKeranjang
{
    std::string namaBarang;
    int jumlahBarang;
    int tgl, bln, thn;

    nodeKeranjang *next;
};
typedef nodeKeranjang *pKeranjang;
typedef pKeranjang listKeranjang;
listKeranjang headKeranjang = nullptr;

class Pelanggan
{
    public:
    std::string username, password, name;
    void insert_data(std::string login, std::string pw)
    {
        std::ofstream database;
        database.open("Login.txt", std::ios::app);
            database << "\nP" << "\t\t" << login << "\t\t" << pw;
        database.close();
    }

    void get_data(std::string name)
    {
        char key;
        std::string nameKey;
        std::string pwKey;
        std::ifstream database;
        database.open("Login.txt");
            while(!database.eof())
            {
                database >> key >> nameKey >> pwKey;
                if(nameKey == name)
                {
                    username = nameKey;
                    password = pwKey;
                }
            }
        database.close();
    }

    void create_element_list(pKeranjang &pNew, std::string nama, int jumlah, int tgl, int bln, int thn)
    {
        pNew = new nodeKeranjang;
        pNew->namaBarang = nama;
        pNew->jumlahBarang = jumlah;
        pNew->tgl = tgl;
        pNew->bln = bln;
        pNew->thn = thn;
        pNew->next = nullptr;
    }

    void push_list(pKeranjang pNew)
    {
        if(headKeranjang == nullptr)
        { headKeranjang = pNew; }

        else
        {
            pKeranjang curr = headKeranjang;
            while(curr->next != nullptr )
            { curr = curr->next; }
            curr->next = pNew;
        }
    }

    void destroy_list()
    {
        if(headKeranjang == nullptr)
        { headKeranjang = nullptr; }

        else
        {
            pKeranjang curr = headKeranjang, tempNode = nullptr;
            while(curr != nullptr)
            {
                tempNode = curr->next;
                delete curr;
                curr = tempNode;
            }
            headKeranjang = nullptr;
        }
    }

    void print_list(int titikX, int titikY)
    {
        int x=titikX, y=titikY;

        pKeranjang curr = headKeranjang;
        while(curr != nullptr)
        {
            gotoxy(x, y); std::cout << curr->namaBarang << "\t\t" << curr->jumlahBarang << "\t\t" << curr->tgl << "/" << curr->bln << "/" << curr->thn << "\n";
            y++;
            curr = curr->next;
        }
    }

    void insert_pesanan()
    {
        std::ofstream database;
        database.open("Pesanan.txt", std::ios::app);
            pKeranjang curr = headKeranjang;
            while(curr != nullptr)
            {
                database << "\n" << username << "\t\t\t" 
                                 << curr->namaBarang << "\t\t\t" 
                                 << curr->jumlahBarang << "\t\t" 
                                 << curr->tgl << "\t"
                                 << curr->bln << '\t'
                                 << curr->thn << "\t\t"
                                 << "SEDANG DIPROSES";
                
                curr = curr->next;
            }
        database.close();
    }

    void query_pesanan(int x, int y)
    {
        std::string nameKey, namaB, status;
        int jumlah, tgl, bln, thn;

        std::ifstream database;
        database.open("Pesanan.txt");
            while(!database.eof())
            {
                database >> nameKey >> namaB >> jumlah >> tgl >> bln >> thn >> status;
                if(nameKey == username)
                {
                    gotoxy(x, y); std::cout << namaB << "\t\t" << jumlah << "\t\t" << tgl << "/" << bln << "/" << thn;
                    y++;
                }
            }
        database.close();
    }
};