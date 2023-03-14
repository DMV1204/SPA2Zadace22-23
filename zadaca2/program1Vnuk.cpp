#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

vector<int> znamenke(int broj) {
    vector<int> znamenke{};
    if (broj==0) {
        return {0};
    }
    while (broj>0) {
        znamenke.push_back(broj%10);
        broj/=10;
    }
    return znamenke;
};

template<typename T>
class HashTable {

public:
    HashTable();
    vector<list<pair<int, T>>> container;
    pair<int, T> search(int key);
    void insert(int key, T value);
    vector<int> random_ai;
    int hash(int key);
};

template<typename T>
HashTable<T>::HashTable() {
    default_random_engine generator(time(0)); //random generator ai-ova
    uniform_int_distribution<int> distribute(0, 6); //interval iz kojeg dolaze

    for (int i=0; i<7; i++) {
        random_ai.push_back(distribute(generator)); //nasumično ih odaberemo i pushbackamo u vec
    }

    container.resize(7);
}

template<typename T>
pair<int, T> HashTable<T>::search(int key) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &a){
        return a.first == key;
    });
    if (it == container[h].end()) {
        cout << "Nije naden element s kljucem: " << key;
        return {};
    }
    else {
        return *it;
    }
}

template<typename T>
void HashTable<T>::insert(int key, T value) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &a){
        return a.first == key;
    });
    if (it != container[h].end()){
        it->second = value;
    }
    else {
        container[h].push_front({key, value});
    }
}

template<typename T>
int HashTable<T>::hash(int key) {
    vector<int> znam = znamenke(key);
    int n = znam.size();
    int sum = 0;

    for (int i=0; i<n; i++) {
        sum += random_ai[i] * znam[i];
    }

    return sum % 7;
}

int main() {
    HashTable<float> hashtablica;

    vector<int> keys = {39, 127, 290, 2, 213, 262, 274, 17, 258, 100, 191, 209};

    float value = 0.0f;
    for (auto key : keys) {
        hashtablica.insert(key, value);
        value += 0.1f;
    }

    pair<int, float> p = hashtablica.search(17);

    cout << p.first << ", " << p.second << endl;

    pair<int, float> p1 = hashtablica.search(333);

    return 0;
}
