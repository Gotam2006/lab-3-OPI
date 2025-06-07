#include <iostream>
#include <string>

class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void draw() const = 0;
};

class Primitive : public Graphic {
    int x, y, width, height;
public:
    Primitive(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}

    void draw() const override {
        std::cout << "Primitive at (" << x << ", " << y << "), size " << width << "x" << height << "\n";
    }
};

class Decorator : public Graphic {
protected:
    Graphic* component;
public:
    Decorator(Graphic* comp) : component(comp) {}
    ~Decorator() { delete component; }

    void draw() const override {
        component->draw();
    }
};

class BorderDecorator : public Decorator {
    std::string borderStyle;
public:
    BorderDecorator(Graphic* comp, const std::string& style)
        : Decorator(comp), borderStyle(style) {}

    void draw() const override {
        Decorator::draw();
        std::cout << "Adding border: " << borderStyle << "\n";
    }
};

int main() {
    Graphic* prim = new Primitive(10, 20, 100, 50);
    Graphic* decorated = new BorderDecorator(prim, "red thick border");

    decorated->draw();

    delete decorated;
    return 0;
}

