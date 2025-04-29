#include <bits/stdc++.h>
using namespace std;

// Model
class Plane{
private:
    string name;
    int capacity;
    int flights;
public:
    Plane(string Name, int Capacity, int Flights) : name(Name), capacity(Capacity), flights(Flights) {}

    string getName() {return name;}
    int getCapacity() {return capacity;}
    int getFlights() {return flights;}
    void addFlights() {flights++;}
};

class Flight{
private:
    Plane plane;
    int passengers;
    string origin;
    string destination;
    string date;
    int ticketPrice;
public:
    Flight(Plane pLane, int Passengers, string Origin, string Destination, string Date, int TicketPrice) :
    plane(pLane), passengers(Passengers), origin(Origin), destination(Destination), date(Date)
    , ticketPrice(TicketPrice) {}

    string getDate() {return date;}
    string getDestination() {return destination;}
    string getOrigin() {return origin;}
    Plane getPlane() {return plane;}
    int getTicketPrice() {return ticketPrice;}
    int getPassengers() {return passengers;}
    void addPassengers() {passengers++;}
};

class User{
private:
    string password;
    string username;
    bool isAdmin;
    int balance;
    vector<Flight> tickets;
public:
    User(string PassWord, string UserName) : password(PassWord), username(UserName){
        balance = 0;
        isAdmin = false;
    }

    string getUsername() {return username;}
    string getPassword() {return password;}
    bool getIsAdmin() {return isAdmin;}
    int getBalance() {return balance;}
    void setIsAdmin() {isAdmin = true;}
    void decBalance(int Balance) {balance -= Balance;}
    void incBalance(int Balance) {balance += Balance;}
    void getTickets(vector<Flight> &fl) {fl = tickets;}
    void addTickets(const Flight &ticket) {tickets.push_back(ticket);}
};
User currentUser("","");

// Controller
class ProgramController{
private:
    vector<User> users;
    vector<Plane> planes;
    vector<Flight> flights;
public:
    int addClientUser(const string &username, const string &password) {
        regex pattern1("[a-z]");
        regex pattern2("[A-Z]");
        regex pattern3("[0-9]");
        regex pattern4("_");
        regex pattern5("^[a-zA-Z0-9_]+$");
        if (!regex_search(username,pattern5) || (!regex_search(username,pattern1) && !regex_search(username,pattern2)))
            return 1;
        for (auto user:users) {
            if (user.getUsername() == username)
                return 2;
        }
        if (!regex_search(password,pattern5))
            return 3;
        if (password.size() < 5 || !regex_search(password,pattern2) ||
            !regex_search(password,pattern3) || !regex_search(password,pattern1))
            return 4;
        User user(password,username);
        users.push_back(user);
        return 5;
    }

    int addAdminUser(const string &username, const string &password) {
        regex pattern1("[a-z]");
        regex pattern2("[A-Z]");
        regex pattern3("[0-9]");
        regex pattern4("_");
        regex pattern5("^[a-zA-Z0-9_]+$");
        for (User user:users) {
            if (user.getIsAdmin()) {
                return 1;
            }
        }
        if (!regex_search(username,pattern5))
            return 2;
        for (User user:users) {
            if (user.getUsername() == username)
                return 3;
        }
        if (!regex_search(password,pattern5))
            return 4;
        if (password.size() < 5 || (!regex_search(password,pattern2) &&
            !regex_search(password,pattern3) && !regex_search(password,pattern1)))
            return 5;
        User user(password,username);
        user.setIsAdmin();
        users.push_back(user);
        return 6;
    }

    int login(const string &username, const string &password) {
        bool isThereThisUsername = false;

        for (User &user:users) {
            if (user.getUsername() == username) {
                isThereThisUsername = true;
                currentUser = user;
                break;
            }
        }
        if (!isThereThisUsername)
            return 1;
        if (currentUser.getPassword() != password)
            return 2;
        return 3;
    }

    int addPlane(const string &name, int capacity) {
        for (Plane plane:planes) {
            if (plane.getName() == name)
                return 1;
        }
        if (capacity < 10)
            return 2;
        Plane newPlane(name,capacity,0);
        planes.push_back(newPlane);
        return 3;
    }

    int addFlight(const string &orig, const string &dest, const string &date, const string &apName, int tiPr) {
        if (date.size() != 10 || date.find("-") != 4 || date.find_last_of("-") != 7)
            return 1;
        bool airFound = false;
        for (Plane &plane:planes) {
            if (plane.getName() == apName) {
                airFound = true;
                break;
            }
        }
        if (!airFound)
            return 2;
        if (tiPr <= 0)
            return 3;
        for (Flight flight:flights) {
            if (flight.getDate() == date && flight.getPlane().getName() == apName)
                return 4;
        }
        for (Plane &plane:planes) {
            if (plane.getName() == apName) {
                Flight newFlight(plane,0,orig,dest,date,tiPr);
                plane.addFlights();
                flights.push_back(newFlight);
                break;
            }
        }
        return 5;
    }

    void sortFlight(vector<Flight> &orderedFlight) {
        for (int i = 0;i < orderedFlight.size();i++) {
            for (int j = 0;j < i;j++) {
                if (orderedFlight[i].getDate() < orderedFlight[j].getDate()) {
                    Flight temp = orderedFlight[i];
                    orderedFlight[i] = orderedFlight[j];
                    orderedFlight[j] = temp;
                }
                else if (orderedFlight[i].getDate() == orderedFlight[j].getDate() && orderedFlight[i].getTicketPrice() < orderedFlight[j].getTicketPrice()) {
                    Flight temp = orderedFlight[i];
                    orderedFlight[i] = orderedFlight[j];
                    orderedFlight[j] = temp;
                }
                else if (orderedFlight[i].getDate() == orderedFlight[j].getDate() &&
                        orderedFlight[i].getTicketPrice() == orderedFlight[j].getTicketPrice() &&
                        orderedFlight[i].getPlane().getName() < orderedFlight[j].getPlane().getName()) {
                    Flight temp = orderedFlight[i];
                    orderedFlight[i] = orderedFlight[j];
                    orderedFlight[j] = temp;
                }
            }
        }
    }

    bool printAllFlights(vector<Flight> &Flights) {
        if (flights.empty())
            return false;
        Flights = flights;
        return true;
    }

    bool printFlightsOnDate(vector<Flight> &fls, const string &date) {
        if (flights.empty())
            return false;
        fls.clear();
        for (auto flight:flights) {
            if (flight.getDate() == date) {
                fls.push_back(flight);
            }
        }
        if (fls.empty())
            return false;
        return true;
    }

    void sortAirplanes(vector<Plane> &orderedAir) {
        for (int i = 0;i < orderedAir.size();i++) {
            for (int j = 0; j < i; j++) {
                if (orderedAir[i].getName() < orderedAir[j].getName()) {
                    Plane temp = orderedAir[i];
                    orderedAir[i] = orderedAir[j];
                    orderedAir[j] = temp;
                }
            }
        }
    }

    bool printAirplanes(vector<Plane> &pln) {
        if (planes.empty())
            return false;
        pln = planes;
        return true;
    }

    int showCapital() {
        return currentUser.getBalance();
    }

    int showTickets(vector<Flight> &fls, const string &orig, const string &dest) {
        bool dateFound = false;
        for (Flight &flight:flights) {
            if (flight.getOrigin() == orig && flight.getDestination() == dest) {
                dateFound = true;
                fls.push_back(flight);
            }
        }
        if (!dateFound)
            return 1;
        return 2;
    }

    int analyseBeforeBuyATicket(string num, vector<Flight> &fls) {
        regex number("\\D");
        if (num == "end")
            return 1;
        if (regex_search(num, number))
            return 2;
        int n = stoi(num);
        if (n > fls.size() || n < 1)
            return 3;
        if (fls[n - 1].getPassengers() >= fls[n - 1].getPlane().getCapacity())
            return 4;
        if (currentUser.getBalance() < fls[n - 1].getTicketPrice())
            return 5;
        if (buyTicket(fls[n-1]))
            return 6;
        return -1;
    }

    int analyseBeforeReturnATicket(string num, vector<Flight> &fls) {
        regex number("\\D");
        if (num == "end")
            return 1;
        if (regex_search(num, number))
            return 2;
        int n = stoi(num);
        if (n > fls.size() || n < 1)
            return 3;
        else if (printUserTicket(fls[n-1]))
            return 4;
        return -1;
    }

    bool buyTicket(Flight &fl) {
        currentUser.decBalance(fl.getTicketPrice());
        for (User user:users) {
            if (user.getIsAdmin()) {
                user.incBalance(fl.getTicketPrice());
                currentUser.addTickets(fl);
                fl.addPassengers();
                return true;
            }
        }
        return false;
    }

    void showUnevenTickets() {

    }
    void buyUnevenTicket() {

    }

    int chargeBalance(int amount) {
        if (amount <= 0)
            return 1;
        currentUser.incBalance(amount);
        return 2;
    }

    bool printUserTicket(Flight &fl) {
        int n = fl.getTicketPrice();
        n = n*4/5;
        currentUser.incBalance(n);
        for (auto &user:users) {
            if (user.getIsAdmin()) {
                user.decBalance(n);
                return true;
            }
        }
        return false;
    }

    int returnTicket(vector<Flight> &fls) {
        currentUser.getTickets(fls);
        if (fls.empty())
            return 1;
        return 2;
    }
};

// View
class View{
private:
    ProgramController programcontroller;
public:
    void run() {
        int state = 1; // sign in menu-1, main menu-2, admin menu-3, customer menu-4

        vector<string> cp;
        string command,word;

        while (true) {
            getline(cin,command);
            stringstream ss(command);

            while (ss >> word) {
                cp.push_back(word);
            }

            // Sign in menu
            if (cp[0] == "register" && cp[1] == "as" && cp[2] == "admin" && cp.size() == 5) {
                string username = cp[3];
                string password = cp[4];
                int status = programcontroller.addAdminUser(username, password);
                switch (status) {
                    case 1:
                        cout << "admin user already created" << endl;
                        break;
                    case 2:
                        cout << "username format is invalid" << endl;
                        break;
                    case 3:
                        cout << "a user exists with this username" << endl;
                        break;
                    case 4:
                        cout << "password format is invalid" << endl;
                        break;
                    case 5:
                        cout << "password is weak" << endl;
                        break;
                    case 6:
                        cout << "admin user created successfully" << endl;
                        break;
                }
            }

            else if (cp[0] == "register" && cp.size() == 3) {
                string username = cp[1];
                string password = cp[2];
                int status = programcontroller.addClientUser(username, password);
                switch (status) {
                    case 1:
                        cout << "username format is invalid" << endl;
                        break;
                    case 2:
                        cout << "a user exists with this username" << endl;
                        break;
                    case 3:
                        cout << "password format is invalid" << endl;
                        break;
                    case 4:
                        cout << "password is weak" << endl;
                        break;
                    case 5:
                        cout << "register successful" << endl;
                        break;
                }
            }

            else if (cp[0] == "login" && cp.size() == 3) {
                string username = cp[1];
                string password = cp[2];
                int status = programcontroller.login(username, password);
                switch (status) {
                    case 1:
                        cout << "no user exists with this username" << endl;
                        break;
                    case 2:
                        cout << "incorrect password" << endl;
                        break;
                    case 3:
                        cout << "login successful" << endl;
                        state = 2;
                        break;
                }
            }

            else if (cp[0] == "Exit" && cp.size() == 1) {
                return;
            }

            // Main menu
            else if (cp[0] == "admin" && cp[1] == "menu" && cp.size() == 2) {
                if (currentUser.getIsAdmin())
                    state = 3;
                else
                    cout << "you don't have access to this menu" << endl;
            }

            else if (cp[0] == "customer" && cp[1] == "menu" && cp.size() == 2) {
                if (currentUser.getIsAdmin())
                    cout << "you don't have access to this menu" << endl;
                else
                    state = 4;
            }

            // Admin Menu
            else if (cp[0] == "add" && cp[1] == "airplane" && cp.size() == 4) {
                string name = cp[2];
                int capacity = stoi(cp[3]);
                int status = programcontroller.addPlane(name, capacity);
                switch (status) {
                    case 1:
                        cout << "an airplane exists with this name" << endl;
                        break;
                    case 2:
                        cout << "invalid capacity" << endl;
                        break;
                    case 3:
                        cout << "plane created successfully" << endl;
                        break;
                }
            }

            else if (cp[0] == "logout" && cp.size() == 1) {
                User cureUser("","");
                currentUser = cureUser;
                state = 2;
                cout << "logout successful" << endl;
            }

            else if (cp[0] == "add" && cp[1] == "flight" && cp.size() == 7) {
                string origin = cp[2];
                string destination = cp[3];
                string date = cp[4];
                string airplanesName = cp[5];
                int ticketPrice = stoi(cp[6]);
                int status = programcontroller.addFlight(origin, destination, date, airplanesName, ticketPrice);
                switch (status) {
                    case 1:
                        cout << "invalid command!" << endl;
                        break;
                    case 2:
                        cout << "no airplane exists with this name" << endl;
                        break;
                    case 3:
                        cout << "invalid ticket price" << endl;
                        break;
                    case 4:
                        cout << "This aircraft already has a flight on this date" << endl;
                        break;
                    case 5:
                        cout << "flight created successfully" << endl;
                        break;
                }
            }

            else if (cp[0] == "show" && cp[1] == "all" && cp[2] == "flights" && cp.size() == 3) {
                vector<Flight> fls;
                string date = cp[3];
                if (programcontroller.printAllFlights(fls)) {
                    int counter = 1;
                    programcontroller.sortFlight(fls);
                    for (Flight flight: fls) {
                        cout << counter << "- " << flight.getOrigin() << "->" << flight.getDestination() << " "
                             << flight.getDate() << " " << flight.getPlane().getName() << " "
                             << flight.getTicketPrice() << endl;
                        counter++;
                    }
                }
                else
                    cout << "nothing" << endl;
            }

            else if (cp[0] == "show" && cp[1] == "flights" && cp[2] == "on" && cp.size() == 4) {
                string date = cp[3];
                vector<Flight> fls;
                if (programcontroller.printFlightsOnDate(fls, date)) {
                    programcontroller.sortFlight(fls);
                    int counter = 1;
                    for (Flight flight: fls) {
                        cout << counter << "- " << flight.getOrigin() << "->" << flight.getDestination() << " "
                        << flight.getDate() << " " << flight.getPlane().getName() << " "
                        << flight.getTicketPrice() << endl;
                        counter++;
                    }
                }
                else
                    cout << "nothing" << endl;
            }

            else if (cp[0] == "show" && cp[1] == "airplanes") {
                vector<Plane> planes;
                if (programcontroller.printAirplanes(planes)) {
                    programcontroller.sortAirplanes(planes);
                    int counter = 1;
                    for (Plane plane: planes) {
                        cout << counter << "- " << plane.getName() << " : " << plane.getFlights() << endl;
                        counter++;
                    }
                }
                else
                    cout << "nothing" << endl;
            }

            else if (cp[0] == "show" && cp[1] == "capital" && cp.size() == 2) {
                int capital = programcontroller.showCapital();
                cout << capital << endl;
            }

            else if (cp[0] == "back" && cp.size() == 1) {
                if (state == 3 || state == 4)
                    state = 2;
                else
                    cout << "invalid command!" << endl;
            }

            // Customer menu
            else if (cp[0] == "purchase" && cp[1] == "ticket" && cp.size() == 4) {
                string origin = cp[2];
                string destination = cp[3];
                vector<Flight> fls;
                int status = programcontroller.showTickets(fls, origin, destination);
                switch (status) {
                    case 1:
                        cout << "There is no direct flight from " << origin << " to " << destination << endl;
                        break;
                    case 2:
                        int counter = 1;
                        programcontroller.sortFlight(fls);
                        for (Flight flight: fls) {
                            cout << counter << "- " << flight.getDate() << " " << flight.getPlane().getName() << " "
                            << flight.getTicketPrice() << endl;
                            counter++;
                        }

                        string num;
                        while (true) {
                            getline(cin,num);
                            int statuss = programcontroller.analyseBeforeBuyATicket(num,fls);
                            if (statuss == 1) {
                                break;
                            }
                            else if (statuss == 2)
                                cout << "invalid command!" << endl;
                            else if (statuss == 3)
                                cout << "invalid number" << endl;
                            else if (statuss == 4)
                                cout << "no empty seat" << endl;
                            else if (statuss == 5)
                                cout << "you don't have enough money" << endl;
                            else if (statuss == 6)
                                cout << "purchase successful" << endl;
                        }

                        break;
                }
            }

            else if (cp[0] == "charge" && cp[1] == "account" && cp.size() == 3) {
                int amount = stoi(cp[2]);
                int status = programcontroller.chargeBalance(amount);
                switch (status) {
                    case 1:
                        cout << "invalid amount" << endl;
                        break;
                    case 2:
                        cout << "account charged successfully" << endl;
                        break;
                }
            }

            else if (cp[0] == "cancel" && cp[1] == "ticket" && cp.size() == 2) {
                vector<Flight> fls;
                int status = programcontroller.returnTicket(fls);
                switch (status) {
                    case 1:
                        cout << "you don't have any tickets" << endl;
                        break;
                    case 2:
                        int counter = 1;
                        for (Flight flight: fls) {
                            cout << counter << "- " << flight.getOrigin() << "->" << flight.getDestination() << " " << flight.getDate() << " " << flight.getTicketPrice() << endl;
                            counter++;
                        }

                        string num;
                        while (true) {
                            getline(cin,num);
                            int statuss = programcontroller.analyseBeforeReturnATicket(num, fls);
                            if (statuss == 1) {
                                break;
                            } else if (statuss == 2)
                                cout << "invalid command!" << endl;
                            else if (statuss == 3)
                                cout << "invalid number" << endl;
                            else if (statuss == 4) {
                                cout << "cancel successful" << endl;
                                break;
                            }
                        }

                        break;
                }
            }

            else
                cout << "invalid command!" << endl;

            cp.clear();
        }
    }
};

int main() {
    View view;

    view.run();

    return 0;
}