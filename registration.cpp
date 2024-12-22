// registration.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <sqlite_modern_cpp.h>
using namespace std;

class UserAuth {
private:
    sqlite::database db;

public:
    UserAuth(const std::string& dbName) : db(dbName) {
        db << "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password TEXT);";
    }
    void registerUser(const std::string& username, const std::string& password) {
        try {
            db << "INSERT INTO users (username, password) VALUES (?, ?);"
                << username << password;
            cout << "Регистрация успешна!" << endl;
        }
        catch (const std::exception& e) {
            cerr << "Ошибка регистрации: " << e.what() << endl;
        }
    }
    bool loginUser(const string& username, const string& password) {
        string storedPassword;
        try {
            db << "SELECT password FROM users WHERE username = ?;"
                << username >> storedPassword;

            if (storedPassword == password) {
                cout << "Авторизация успешна!" << std::endl;
                return true;
            }
            else {
                cout << "Неверный пароль!" << std::endl;
                return false;
            }
        }
        catch (const std::exception& e) {
            cerr << "Ошибка авторизации: " << e.what() << std::endl;
            return false;
        }
    }
};
int main() {
    UserAuth auth("users.db");
    int choice;
    string username, password;

    while (true) {
        cout << "1. Регистрация\n2. Авторизация\n3. Выход\nВведите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите имя пользователя: ";
            cin >> username;

            cout << "Введите пароль: ";
            cin >> password;

            auth.registerUser(username, password);
            break;

        case 2:
            cout << "Введите имя пользователя: ";
            cin >> username;

            cout << "Введите пароль: ";
            cin >> password;

            auth.loginUser(username, password);
            break;

        case 3:
            return 0;

        default:
            cout << "Неверный выбор, попробуйте еще раз." << endl;
        }
    }
    return 0;
}
