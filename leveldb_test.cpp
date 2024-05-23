#include <iostream>
#include <leveldb/db.h>

int main() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    // Open the database
    leveldb::Status status = leveldb::DB::Open(options, "./test_leveldb.db", &db);
    if(!status.ok()) {
        std::cerr << "Unable to open database: " << status.ToString() << std::endl;
        return 1;
    }

    // Put key-value pares
    status = db->Put(leveldb::WriteOptions(), "key1", "value1");
    if(!status.ok()) {
        std::cerr << "Put error: " << status.ToString() << std::endl;
    }

    status = db->Put(leveldb::WriteOptions(), "key2", "value2");
    if (!status.ok()) {
        std::cerr << "Put error: " << status.ToString() << std::endl;
    }

    // Get value by key
    std::string value;
    status = db->Get(leveldb::ReadOptions(), "key1", &value);
    if (status.ok()) {
        std::cout << "Value of key1: " << value << std::endl;
        value.clear();
    } else {
        std::cerr << "Get error: " << status.ToString() << std::endl;
    }

    status = db->Get(leveldb::ReadOptions(), "key2", &value);
    if (status.ok()) {
        std::cout << "Value of key2: " << value << std::endl;
        value.clear();
    } else {
        std::cerr << "Get error: " << status.ToString() << std::endl;
    }

    // Close the database
    delete db;

    return 0;
}