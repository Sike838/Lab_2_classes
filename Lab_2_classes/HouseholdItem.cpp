#include "HouseholdItem.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>

// Вспомогательные методы
void HouseholdItem::calculateAverage() {//средняя цена
    if (totalOrdered == 0) {
        averagePrice = 0.0;
    }
    else {
        averagePrice = totalSpent / totalOrdered;
    }
}
// проверки корректности ввода
void HouseholdItem::validateName(const char* nameValid) const { // TODO n rename 
    if (nameValid == nullptr) {
        throw std::invalid_argument("Name cannot be null");
    }
    if (strlen(nameValid) == 0) {
        throw std::invalid_argument("Name cannot be empty");
    }
    if (strlen(nameValid) > 100) {
        throw std::invalid_argument("Name too long");
    }
}

void HouseholdItem::validatePrice(double price) const {
    if (price <= 0) {
        throw std::invalid_argument("Price must be positive");
    }
    if (price > 1e9) {
        throw std::invalid_argument("Price too high");
    }
}

void HouseholdItem::validateQuantity(int quantity) const {
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }
    if (quantity > 1000000) {
        throw std::invalid_argument("Quantity too high");
    }
}

// Конструкторы
//создание пустого объекта
HouseholdItem::HouseholdItem() : name(nullptr), 
                                currentPrice(0), 
                                maxPrice(0), 
                                minPrice(0),
                                totalOrdered(0),
                                totalSpent(0),
                                averagePrice(0) {}
//создание объекта с заданным именем
HouseholdItem::HouseholdItem(const char* itemName) : HouseholdItem() {
    validateName(itemName);
    size_t length = strlen(itemName);
    name = new char[length + 1];

    // Безопасное копирование для Visual Studio
#ifdef _MSC_VER
    strcpy_s(name, length + 1, itemName);
#else
    strcpy(name, itemName);
#endif
}

// ПЕРЕГРУЖЕННЫЙ конструктор - создание уже купленного товара
HouseholdItem::HouseholdItem(const char* itemName, int quantity, double price)
    : HouseholdItem(itemName) { // Делегируем конструктору с именем

    if (quantity > 0) {
        if (price <= 0) {
            // Если цена не указана или 0, устанавливаем цену по умолчанию 1.0
            price = 1.0;
        }
        // Выполняем первую покупку
        purchase(quantity, price);
    }
}

// конструктор копирования(создает полную копию объекта)
HouseholdItem::HouseholdItem(const HouseholdItem& other) {
    if (other.name == nullptr) {
        name = nullptr;
    }
    else {
        validateName(other.name);
        size_t length = strlen(other.name);
        name = new char[length + 1];

#ifdef _MSC_VER
        strcpy_s(name, length + 1, other.name);
#else
        strcpy(name, other.name);
#endif
    }

    currentPrice = other.currentPrice;
    maxPrice = other.maxPrice;
    minPrice = other.minPrice;
    totalOrdered = other.totalOrdered;
    totalSpent = other.totalSpent;
    averagePrice = other.averagePrice;
}

// Деструктор
HouseholdItem::~HouseholdItem() {
    delete[] name;
}

// Оператор присваивания
HouseholdItem& HouseholdItem::operator=(const HouseholdItem& other) {
    if (this != &other) {
        // Освобождаем старую память
        delete[] name;

        // Копируем новое имя
        if (other.name == nullptr) {
            name = nullptr;
        }
        else {
            validateName(other.name);
            size_t length = strlen(other.name);
            name = new char[length + 1];

#ifdef _MSC_VER
            strcpy_s(name, length + 1, other.name);
#else
            strcpy(name, other.name);
#endif
        }

        // Копируем остальные поля
        currentPrice = other.currentPrice;
        maxPrice = other.maxPrice;
        minPrice = other.minPrice;
        totalOrdered = other.totalOrdered;
        totalSpent = other.totalSpent;
        averagePrice = other.averagePrice;
    }
    return *this;
}

// Селекторы
const char* const HouseholdItem::getName() const { return name; }
double HouseholdItem::getCurrentPrice() const { return currentPrice; }
double HouseholdItem::getMaxPrice() const { return maxPrice; }
double HouseholdItem::getMinPrice() const { return minPrice; }
int HouseholdItem::getTotalOrdered() const { return totalOrdered; }
double HouseholdItem::getTotalSpent() const { return totalSpent; }
double HouseholdItem::getAveragePrice() const { return averagePrice; }

// Метод покупки
void HouseholdItem::purchase(int quantity, const double& price) {
    validateQuantity(quantity);
    validatePrice(price);

    currentPrice = price;

    if (totalOrdered == 0) {//уменьшение условных проверок
        minPrice = maxPrice = currentPrice = price;
    }
    else {
        currentPrice = price;
        if (price < minPrice) minPrice = price;
        if (price > maxPrice) maxPrice = price;
    }
    // обновляем статистику
    totalOrdered += quantity;
    double purchaseTotal = quantity * price;  // Вычисляем один раз
    totalSpent += purchaseTotal;
    calculateAverage();
}

// ПЕРЕГРУЖЕННЫЙ метод покупки по текущей стоимости
void HouseholdItem::purchase(int quantity) {
    validateQuantity(quantity);

    if (currentPrice <= 0) {
        throw std::invalid_argument("Current price is not set or zero");
    }

    // Используем текущую цену для покупки
    if (totalOrdered == 0) {
        // Если это первая покупка, устанавливаем min/max цены
        maxPrice = currentPrice;
        minPrice = currentPrice;
    }
    else {
        // Обновляем min/max, если текущая цена выходит за пределы
        if (currentPrice > maxPrice) maxPrice = currentPrice;
        if (currentPrice < minPrice) minPrice = currentPrice;
    }

    totalOrdered += quantity;
    totalSpent += quantity * currentPrice;
    calculateAverage();
}

// ПЕРЕГРУЖЕННЫЙ оператор += (покупка по текущей цене)
HouseholdItem& HouseholdItem::operator+=(int quantity) {
    // Вызываем перегруженный метод purchase с одним параметром
    purchase(quantity);
    return *this;
}

// Метод вывода
void HouseholdItem::print() const {
    std::cout << "Name: " << (name ? name : "N/A") << "\n"
        << "Current Price: " << currentPrice << "\n"
        << "Max Price: " << maxPrice << "\n"
        << "Min Price: " << minPrice << "\n"
        << "Total Ordered: " << totalOrdered << "\n"
        << "Total Spent: " << totalSpent << "\n"
        << "Average Price: " << averagePrice << std::endl;
}
// ПЕРЕГРУЖЕННЫЙ оператор += вне класса для общей стоимости
double& operator+=(double& sum, const HouseholdItem& item) {
    sum += item.getTotalSpent();
    return sum;
}
