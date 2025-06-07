#include <iostream>
#include <string>

/**
 * @brief Базовий інтерфейс графічного примітива.
 * 
 * Визначає метод draw(), який виводить інформацію про примітив.
 */
class Graphic {
public:
    virtual ~Graphic() = default;

    /**
     * @brief Метод відображення графічного примітива.
     */
    virtual void draw() const = 0;
};

/**
 * @brief Клас конкретного графічного примітива (наприклад, Rectangle).
 * 
 * Містить позицію (x, y) та розмір (width, height).
 */
class Primitive : public Graphic {
protected:
    int x, y;           ///< Координати розміщення
    int width, height;  ///< Розміри

public:
    Primitive(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    /**
     * @brief Відображає позицію та розмір примітива.
     */
    void draw() const override {
        std::cout << "Primitive: position=(" << x << ", " << y 
                  << "), size=(" << width << ", " << height << ")\n";
    }
};

/**
 * @brief Абстрактний клас-декоратор, що реалізує інтерфейс Graphic.
 * 
 * Декоратор містить вказівник на компонент типу Graphic,
 * до якого делегує виклики методів, додаючи власну поведінку.
 */
class Decorator : public Graphic {
protected:
    Graphic* component; ///< Компонент, що декорується

public:
    explicit Decorator(Graphic* comp) : component(comp) {}

    virtual ~Decorator() {
        delete component;
    }

    /**
     * @brief Делегує виклик методу draw() компоненту.
     */
    void draw() const override {
        component->draw();
    }
};

/**
 * @brief Конкретний декоратор, який додає обведення (рамку) до примітива.
 */
class BorderDecorator : public Decorator {
private:
    std::string borderStyle; ///< Стиль обведення

public:
    BorderDecorator(Graphic* comp, const std::string& style)
        : Decorator(comp), borderStyle(style) {}

    /**
     * @brief Додає відображення рамки до стандартного методу draw().
     */
    void draw() const override {
        Decorator::draw(); // виклик базового примітива
        std::cout << "BorderDecorator: додано рамку зі стилем '" << borderStyle << "'\n";
    }
};

int main() {
    // Створюємо примітив
    Graphic* primitive = new Primitive(10, 20, 100, 50);

    // Обгортаємо його в декоратор з рамкою
    Graphic* decoratedPrimitive = new BorderDecorator(primitive, "червона товста");

    // Викликаємо метод draw()
    decoratedPrimitive->draw();

    delete decoratedPrimitive;

    return 0;
}

