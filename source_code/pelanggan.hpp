struct nodeBarang
{
    std::string namaBarang;
    int jumlahBarang;
    long int hargaBarang;

    nodeBarang *next;
};
typedef nodeBarang *pBarang;
typedef pBarang listBarang;

listBarang head = nullptr;

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

    bool salah_pilih(std::string name)
    {
        
    }

    bool kelebihan(int jumlah)
    {

    }
};