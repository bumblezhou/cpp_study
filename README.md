# cpp_study

## binary_search
``` c++
g++ binary_search.cpp -o binary_search -std=c++14
```

## quick_sort.cpp
``` c++
g++ quick_sort.cpp -o quick_sort -std=c++14
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
