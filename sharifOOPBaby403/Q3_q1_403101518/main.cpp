#include <bits/stdc++.h>
using namespace std;

class User{
private:
    string username;
    string password;
public:
    User(string username, string password) : username(username), password(password) {}
    string getUsername() {return username;}
    string getPassword() {return password;}
    void setUsername(const string &u) {username = u;}
    void setPassword(const string &p) {password = p;}
};

class UserManagement{
private:
    vector<User> users;
    int indexKeeper = 0;
public:
    UserManagement() {}

    void signUp(const string &username, const string &password) {
        int counter = 0;
        for (User user:users) {
            if (user.getUsername() == username) {
                cout << "This username is already taken" << endl;
                return;
            }
        }
        if (password.size() < 6) {
            cout << "Password must be at least 6 characters long" << endl;
            return;
        }
        User u(username,password);
        users.push_back(u);
        cout << "Account created successfully!" << endl;
        indexKeeper = users.size()-1;
    }


    void logIn(const string &username, const string &password) {
        bool userFound = false;
        int counter = 0;
        for (User &user:users) {
            if (user.getUsername() == username) {
                userFound = true;
                indexKeeper = counter;
                break;
            }
            counter++;
        }
        if (!userFound) {
            cout << "The username is not registered" << endl;
            return;
        }
        if (users[indexKeeper].getPassword() != password) {
            cout << "Password is incorrect" << endl;
            return;
        }
        cout << "Logged in successfully!" << endl;
    }

    void changePassword(const string &username, const string &password) {
        if (users[indexKeeper].getUsername() != username || users[indexKeeper].getPassword() != password) {
            cout << "Invalid username or password" << endl;
            return;
        }
        string newPassword;
        cin >> newPassword;
        if (newPassword.size() < 6) {
            cout << "New password must be at least 6 characters long" << endl;
            cin.ignore();
            return;
        }
        users[indexKeeper].setPassword(newPassword);
        cout << "Password changed successfully!" << endl;
        cin.ignore();
    }

    void showUsers() {
        for (User user:users) {
            cout << user.getUsername() << endl;
        }
    }
};

int main() {
    string command,username,password;
    UserManagement userManagement;

    while (true) {
        getline(cin,command);
        if (command == "exit")
            break;
        else if (command == "Sign up") {
            cin >> username >> password;
            cin.ignore();
            userManagement.signUp(username,password);
        }
        else if (command == "Log in") {
            cin >> username >> password;
            cin.ignore();
            userManagement.logIn(username,password);
        }
        else if (command == "Change password") {
            cin >> username >> password;
            cin.ignore();
            userManagement.changePassword(username,password);
        }
        else if (command == "Show users") {
            userManagement.showUsers();
        }
    }

    return 0;
}