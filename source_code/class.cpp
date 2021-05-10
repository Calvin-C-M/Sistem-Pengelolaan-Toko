#include <iostream>
#include <fstream>
#include "data_struct.hpp"

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
                {
                    password = pwKey;
                }
            }
        database.close();
    }
};

class Admin
{
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
                {
                    password = pwKey;
                }
            }
        database.close();
    }
};