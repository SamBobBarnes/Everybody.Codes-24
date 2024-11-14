//
// Created by sb17057 on 11/14/2024.
//

#ifndef BUCKET_H
#define BUCKET_H
#include <map>

class Bucket {
private:
    std::map<int, tuple<int, vector<int> > > collection{};

public:
    bool Collect(const int cry, const int i) {
        if (collection.contains(cry)) {
            get<0>(collection[cry])++;
            get<1>(collection[cry]).push_back(i);
        } else {
            collection.insert({cry, {1, {i}}});
        }
        return get<0>(collection[cry]) == 50;
    }

    void PrintData() {
        map<int, tuple<int, vector<int> > >::iterator cry = collection.begin();
        int size = collection.size();
        for (int i = 0; i < size; i++) {
            if (get<0>(cry->second) > 25) {
                cout << cry->first << ":" << get<0>(cry->second) << " [ ";

                string array;
                for (const int iter: get<1>(cry->second)) {
                    array += to_string(iter) + ", ";
                }
                int length = array.length();
                cout << array.substr(0, length - 2) << " ]" << endl;
            }
            advance(cry, 1);
        }
    }
};

#endif //BUCKET_H
