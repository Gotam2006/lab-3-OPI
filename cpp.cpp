#include <iostream>

// Subject — загальний інтерфейс
class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() = 0;
};

// RealSubject — реальна реалізація
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request.\n";
    }
};

// Proxy — клас-замінник, який контролює доступ
class Proxy : public Subject {
private:
    RealSubject* realSubject;

    void checkAccess() {
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
    }

    void logAccess() {
        std::cout << "Proxy: Logging the time of request.\n";
    }

public:
    Proxy() : realSubject(nullptr) {}
    ~Proxy() { delete realSubject; }

    void request() override {
        if (!realSubject) {
            realSubject = new RealSubject();
        }
        checkAccess();
        realSubject->request();
        logAccess();
    }
};

int main() {
    Proxy proxy;
    proxy.request();

    return 0;
}
