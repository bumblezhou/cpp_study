# cpp_study

## binary_search
``` c++
g++ binary_search.cpp -o binary_search -std=c++14
```

## quick_sort.cpp
``` c++
g++ quick_sort.cpp -o quick_sort -std=c++14
```

## LinkedList.cpp
``` c++
g++ LinkedList.cpp -o LinkedList -std=c++14
```

## copy_semantic
``` c++
g++ copy_semantic.cpp -o copy_semantic -std=c++14
```

## move_semantic
``` c++
g++ move_semantic.cpp -o move_semantic -std=c++14
```

## TestGetInstance
``` c++
g++ TestGetInstance.cpp -o TestGetInstance -std=c++14 -lpthread
```

## TestLifeCircle
``` c++
g++ TestLifeCircle.cpp -o TestLifeCircle -std=c++14 -lpthread
```

## Copy constructor and copy assignment
``` c++
g++ copy_constructor_assignment.cpp -o copy_constructor_assignment -std=c++14
```

## Sqlite3 test
```bash
sudo apt update && sudo apt install sqlite3 libsqlite3-dev -y
```
``` c++
g++ sqlite_test.cpp -o sqlite_test -std=c++14 -lsqlite3
```

## LevelDB test
```bash
sudo apt update && sudo apt install libleveldb-dev -y
leveldbutil --version
```
``` c++
g++ leveldb_test.cpp -o leveldb_test -std=c++14 -lleveldb
```

## Factory singleton test
``` c++
g++ FactorySingletonTest.cpp -o FactorySingletonTest -std=c++14 -lpthread
```

## Observer pattern
``` c++
g++ ObserverPattern.cpp -o ObserverPattern -std=c++14
```

## Producer-Consumer
``` c++
g++ ProduceConsume.cpp -o ProduceConsume -std=c++14 -lpthread

## Producer-Consumer
``` c++
g++ ProducerConsumer.cpp -o ProducerConsumer -std=c++14 -lpthread
```

## HTTP server
1. Build
``` c++
g++ http_server.cpp -o http_server -std=c++17
```
2. Run
```bash
./http_server 8080 ./
```
[browser]
http://localhost:8080/static/test.html

## C++11 features
1. Build
``` c++
g++ c++11_features.cpp -o c++11_features -std=c++11
```
2. Run
```bash
./c++11_features
```

## C++14 features
1. Build
``` c++
g++ c++14_features.cpp -o c++14_features -std=c++14
```
2. Run
```bash
./c++14_features
```

## C++17 features
1. Build
``` c++
g++ c++17_features.cpp -o c++17_features -std=c++17
```
2. Run
```bash
./c++17_features
```

## C++20 features
1. Prepare
```bash
apt search '^g\+\+-[0-9]+$'
sudo apt update && sudo apt install g++-10 -y
g++-10 --version
```
1. Build
``` c++
g++-10 c++2a_features.cpp -o c++2a_features -std=c++2a -fcoroutines
g++-10 c++2a_feature_coroutine.cpp -o c++2a_feature_coroutine -std=c++2a -fcoroutines -pthread
```
2. Run
```bash
./c++2a_features
./c++2a_feature_coroutine
