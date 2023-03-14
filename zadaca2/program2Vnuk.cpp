#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class UsernameBase {
public:
    UsernameBase(int m);

    vector<bool> container;

    void insert(const string& user);
    string search(const string& user);

    int h1(const string& user);
    int h2(const string& user);
    int h3(const string& user);
    int h4(const string& user);

};

UsernameBase::UsernameBase(int m) {
    container.resize(m, false); //Kreiramo container s obzirom na zadanu veličinu tablice
}

void UsernameBase::insert(const string &user) {
    container[h1(user)] = true;
    container[h2(user)] = true;
    container[h3(user)] = true;
    container[h4(user)] = true;
}

string UsernameBase::search(const string &user) {
    string fail = "Element nije u tablici.";
    string success = "Element je vjerojatno u tablici.";

    if (container[h1(user)] == false){
        return fail;
    }
    if (container[h2(user)] == false){
        return fail;
    }
    if (container[h3(user)] == false){
        return fail;
    }
    if (container[h4(user)] == false){
        return fail;
    }

    return success;
}

//Definiramo hash funkcije h1,h2,h3,h4 kako su zadane u zadatku
int UsernameBase::h1(const string &s) {
    unsigned long long sum = 0;
    int n = s.size();
    int m = container.size();

    for (int i=0; i<n; i++) {
        sum+=s[i] % m;
    }

    return sum % m;
}

int UsernameBase::h2(const string &s) {
    unsigned long long sum = 0;
    int n = s.size();
    int m = container.size();
    for (int i=0; i<n; i++) {
        sum += (s[i] * int(pow(19, i))) % m;
    }
    return (1 + sum) % m;
}

int UsernameBase::h3(const string &s) {
    unsigned long long sum = 0;
    int n = s.size();
    int m = container.size();
    for (int i=0; i<n; i++){
        sum+=(s[i] * int(pow(30, i))) % m;
    }
    return (7 + sum) % m;
}

int UsernameBase::h4(const string &s) {
    unsigned long long sum = 0;
    int n = s.size();
    int m = container.size();
    for (int i=0; i<n; i++) {
        sum+=(s[i] * int(pow(3, i)) * int(pow(7, i))) % m;
    }
    return (3 + sum) % m;
}

int main() {
    UsernameBase db(100);

    vector<string> names = {
            "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar",
            "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
            "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan",
            "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac",
            "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic",
            "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija",
            "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for (auto name : names)
        db.insert(name);

    cout << db.search("DMV1204") << endl;
    cout << db.search("DMV1203") << endl;
    cout << db.search("istvavk") << endl;
    cout << db.search("TomislavVinkovic") << endl;
    cout << db.search("BraneBB") << endl;
    cout << db.search("UranjekovPreworkout") << endl;
    cout << db.search("Baki") << endl;

    return 0;
}