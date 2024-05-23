#include <iostream>
#include <vector>
#include <algorithm>

// Observer interface
class Observer {
public:
    virtual void update() = 0;
};

// Subject class
class Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }

    virtual int getState() const = 0;
    virtual void setState(int state) = 0;

private:
    std::vector<Observer*> observers;
};

// Concrete Subject class
class ConcreteSubject : public Subject {
public:
    int getState() const override {
        return state;
    }

    void setState(int newState) override {
        std::cout << "ConcreteSubject setState: " << newState << std::endl;
        state = newState;
        notify(); // Notify observers of state change
    }

private:
    int state = 0;
};

// Concrete Observer class
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject* subject) : subject(subject) {
        subject->attach(this);
    }

    ~ConcreteObserver() {
        subject->detach(this);
    }

    void update() override {
        std::cout << "Observer updated. New state: " << subject->getState() << std::endl;
    }

private:
    Subject* subject;
};

int main() {
    ConcreteSubject subject;

    ConcreteObserver observer1(&subject);
    ConcreteObserver observer2(&subject);

    subject.setState(1);
    subject.setState(2);

    return 0;
}