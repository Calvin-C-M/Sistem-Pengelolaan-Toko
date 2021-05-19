class Admin
{
    private:
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

    void create_element_stack(pInvent pNew, std::string nama, int jumlah, long int harga)
    {
        pNew = new nodeInventori;
        pNew->namaBarang = nama;
        pNew->jumlah = jumlah;
        pNew->harga = harga;
        pNew->next = nullptr;
    }

    void push_stack_inventori(std::string nama, int jumlah, long int harga)
    {
        pInvent newElement;
        create_element_stack(newElement, nama, jumlah, harga);

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
            gotoxy(x, y); std::cout << curr->namaBarang << "\t\t" << curr->jumlah << "\t\tRp" << curr->harga;
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
        std::fstream database;
        std::fstream temp;

        pInvent curr = topStack;
        database.open("Inventori.txt", std::ios::in);
            while(!database.eof())
            {
                std::string nama;
                int jumlah;
                long int harga;

                database >> nama >> jumlah >> harga;

                while(curr != nullptr)
                {
                    if(curr->namaBarang == nama && curr->harga == harga)
                    { curr->jumlah += jumlah; }
                    
                    else
                    { push_stack_inventori(nama, jumlah, harga); }
                    curr = curr->next;
                }
            }
        database.close();

        temp.open("temp.txt", std::ios::out | std::ios::app);
            pInvent curr = topStack;
            while(curr != nullptr)
            {
                temp << "\n" << curr->namaBarang << '\t\t' << curr->jumlah << '\t\t' << curr->harga;
            }
        temp.close();

        remove("Inventori.txt");
        rename("temp.txt", "Inventori.txt");
    }
};