#include <iostream>
#include <utility>
#include "service.hpp"
#include "vector.hpp"

using namespace std;
using Bucket = pair<string, unique_ptr<Service>>;

class Table {
public:
    Table() = default;
    Table(const Table& rhs);
    ~Table() = default;
    bool find(const string& key) const;
    void remove(const string& key);
    void add(const Bucket& bucket);
    Bucket& operator[](const string& key);
    void print_table();

private:
    Vector<unique_ptr<Bucket>> data;
};


