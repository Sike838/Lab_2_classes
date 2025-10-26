#include "HouseholdItem.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>

// ��������������� ������
void HouseholdItem::calculateAverage() {//������� ����
    if (totalOrdered == 0) {
        averagePrice = 0.0;
    }
    else {
        averagePrice = totalSpent / totalOrdered;
    }
}
// �������� ������������ �����
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

// ������������
//�������� ������� �������
HouseholdItem::HouseholdItem() : name(nullptr), 
                                currentPrice(0), 
                                maxPrice(0), 
                                minPrice(0),
                                totalOrdered(0),
                                totalSpent(0),
                                averagePrice(0) {}
//�������� ������� � �������� ������
HouseholdItem::HouseholdItem(const char* itemName) : HouseholdItem() {
    validateName(itemName);
    size_t length = strlen(itemName);
    name = new char[length + 1];

    // ���������� ����������� ��� Visual Studio
#ifdef _MSC_VER
    strcpy_s(name, length + 1, itemName);
#else
    strcpy(name, itemName);
#endif
}
// ����������� �����������(������� ������ ����� �������)
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

// ����������
HouseholdItem::~HouseholdItem() {
    delete[] name;
}

// �������� ������������
HouseholdItem& HouseholdItem::operator=(const HouseholdItem& other) {
    if (this != &other) {
        // ����������� ������ ������
        delete[] name;

        // �������� ����� ���
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

        // �������� ��������� ����
        currentPrice = other.currentPrice;
        maxPrice = other.maxPrice;
        minPrice = other.minPrice;
        totalOrdered = other.totalOrdered;
        totalSpent = other.totalSpent;
        averagePrice = other.averagePrice;
    }
    return *this;
}

// ���������
const char* const HouseholdItem::getName() const { return name; }
double HouseholdItem::getCurrentPrice() const { return currentPrice; }
double HouseholdItem::getMaxPrice() const { return maxPrice; }
double HouseholdItem::getMinPrice() const { return minPrice; }
int HouseholdItem::getTotalOrdered() const { return totalOrdered; }
double HouseholdItem::getTotalSpent() const { return totalSpent; }
double HouseholdItem::getAveragePrice() const { return averagePrice; }

// ����� �������
void HouseholdItem::purchase(int quantity, const double& price) {
    validateQuantity(quantity);
    validatePrice(price);

    currentPrice = price;

    if (totalOrdered == 0) {//���������� �������� ��������
        minPrice = maxPrice = currentPrice = price;
    }
    else {
        currentPrice = price;
        if (price < minPrice) minPrice = price;
        if (price > maxPrice) maxPrice = price;
    }
    // ��������� ����������
    totalOrdered += quantity;
    double purchaseTotal = quantity * price;  // ��������� ���� ���
    totalSpent += purchaseTotal;
    calculateAverage();
}

// ����� ������
void HouseholdItem::print() const {
    std::cout << "Name: " << (name ? name : "N/A") << "\n"
        << "Current Price: " << currentPrice << "\n"
        << "Max Price: " << maxPrice << "\n"
        << "Min Price: " << minPrice << "\n"
        << "Total Ordered: " << totalOrdered << "\n"
        << "Total Spent: " << totalSpent << "\n"
        << "Average Price: " << averagePrice << std::endl;
}