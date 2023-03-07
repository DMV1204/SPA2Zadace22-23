#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Dictionary {
    private:
        vector<pair<int, T>> container;
        int size = 0;
    public:
        //Konstruktori i destruktori
        Dictionary();
        Dictionary(int s);
        ~Dictionary();
        //Funkcije
        int hash(int k, int i);
        typename vector<pair<int, T>>::iterator search(int key) const;
        bool remove(int key);
        bool insert(int key, T value);
        void print() const;
        //Iteratori
        typename vector<pair<int, T>>::iterator begin() const;
        typename vector<pair<int, T>>::iterator end() const;
};

template<typename T>
Dictionary<T>::Dictionary() {}

template<typename T>
Dictionary<T>::Dictionary(int s) {
    for (int i = 0; i < s; i++) {
        container.push_back({-1, T()}); //setamo ih na -1 pri kreiranju
    }
}

template<typename T>
Dictionary<T>::~Dictionary() {}

//Hash funkcija iz 1. zadatka b)
template<typename T>
int Dictionary<T>::hash(int k, int i) {
    int m = container.size();
    int h1 = k % m;
    int h2 = i * (1 + (k % (m - 1)));
    return (h1 + h2) % m;
}

template<typename T>
typename vector<pair<int, T>>::iterator Dictionary<T>::search(int key) const {
    int i = 0;
    while (true) {
        int h = hash(key, i);
        if (container[h].first == -1) { //check ako je -1 sa početka
            return container.end();
        }
        else if (container[h].first == key) { //ako ga pronađemo
            return container.begin() + h;
        }
        i++; //inkrement za dalje
    }
}

template<typename T>
bool Dictionary<T>::remove(int key) { //Skoro pa identično kao search samo kada nađemo setamo na -1
    int i = 0;
    while(true) {
        int h = hash(key, i);
        if (container[h].first == -1) {
            return false;
        }
        else if (container[h].first == key) {
            container[h].first = -1;
            container[h].second = T();
            return true;
        }
        i++;
    }
}

template<typename T>
bool Dictionary<T>::insert(int key, T value) {
    if (size < container.size()) {
        int i = 0;
        while (true) {
            int h = hash(key, i);
            if (container[h].first == -1) { //ako je slobodan samo upišemo vrijednosti
                container[h].first = key;
                container[h].second = value;
                size++;
                return true;
            }
            else if (container[h].first == key) { //ako nije, pregazimo ga
                container[h].second = value;
                return true;
            }
            i++;
        }
    }
    else{
        return false;
    }
}

template<typename T>
void Dictionary<T>::print() const {
    for (pair<int, T> p : container) {
        if (p.first == -1){
            cout << "nil ";
        }
        else {
            cout << "K:" << p.first << " V:" << p.second << " ";
        }
    }
    cout << endl;
}

template<typename T>
typename vector<pair<int, T>>::iterator Dictionary<T>::begin() const {
    return container.begin();
}

template<typename T>
typename vector<pair<int, T>>::iterator Dictionary<T>::end() const {
    return container.end();
}

int main()
{
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    Dictionary<float> dict(19);

    for (int i = 0; i < 10; i++)
        cin >> keys[i];

    for (int i = 0; i < 10; i++)
        dict.insert(keys[i], values[i]);

    dict.remove(keys[6]);
    dict.insert(keys[2], 1.1);
    dict.print();

    return 0;
}





