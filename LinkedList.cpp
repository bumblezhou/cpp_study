#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

public:
    class Iterator {
    private:
        Node* currentNode;

    public:
        Iterator(Node* node) : currentNode(node) {}

        T& operator*() const {
            return currentNode->data;
        }

        Iterator& operator++() {
            currentNode = currentNode->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return currentNode != other.currentNode;
        }
    };

private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void insert(T value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    void remove(T value) {
        if (isEmpty()) {
            return;
        }

        Node* currentNode = head;
        Node* previousNode = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                if (previousNode == nullptr) {
                    head = currentNode->next;
                } else {
                    previousNode->next = currentNode->next;
                }

                if (currentNode == tail) {
                    tail = previousNode;
                }

                delete currentNode;
                size--;
                return;
            }

            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    void clear() {
        Node* currentNode = head;

        while (currentNode != nullptr) {
            Node* temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }

        head = tail = nullptr;
        size = 0;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void print() const {
        Node* currentNode = head;

        while (currentNode != nullptr) {
            std::cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }

        std::cout << std::endl;
    }
};

struct Student {
    std::int32_t age;
    bool sex;
    std::string name;
    
    bool operator==(const Student& other) const {
        return (age == other.age && sex == other.sex && name == other.name);
    }
};

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "name:" << student.name << ", age:" << student.age << ", sex:" << (student.sex?"male":"female") << std::endl;
    return os;
}

int main() {
    LinkedList<Student> myList;
    myList.insert({24, true, "Huang"});
    myList.insert({32, false, "Liu"});
    myList.insert({38, true, "Zhang"});
    myList.insert({25, false, "Wang"});

    for (auto& item : myList) {
        std::cout << item;
    }
    std::cout << std::endl;

    myList.remove({24, true, "Huang"});

    for (auto& item : myList) {
        std::cout << item;
    }
    std::cout << std::endl;

    return 0;
}
