#include <iostream>
#include "table.hpp"

using namespace std;

Table::Table(const Table& rhs) {
    for (const auto& bucket : rhs.data) {
        data.push_back(make_unique<Bucket>(bucket->first, make_unique<Service>(*bucket->second)));
    }
}

Bucket& Table::operator [] (const string& key) const {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].first == key) {
            return data[i];
            break;
    }
}

bool Table::find(const string& key) const {
    bool find = false;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i]->first == key) {
            find = true;
            break;
        }
    }
    return find;
}

void Table::add(const Bucket& bucket) {
    data.push_back(make_unique<Bucket>(bucket.first, make_unique<Service>(*bucket.second)));
}

void Table::remove(const string& key) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i]->first == key) {
            data.erase(data.begin() + i);
        }
    }
}

void Table::print_table() {
    for (const auto& bucket : data) {
        cout << "Key: " << bucket->first << ", Service: ";
        bucket->second->print();
        cout << endl;
    }
}



