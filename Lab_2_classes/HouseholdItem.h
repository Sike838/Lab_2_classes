#ifndef HOUSEHOLD_ITEM_H
#define HOUSEHOLD_ITEM_H

class HouseholdItem {
private:
    char* name;
    double currentPrice;
    double maxPrice;
    double minPrice;
    int totalOrdered;
    double totalSpent;
    double averagePrice;

    void calculateAverage();//расчет средней цены
    void validateName(const char* nameValid) const; // корректность имени 
    void validatePrice(double price) const;// корректность цены
    void validateQuantity(int quantity) const;//корректность колличесства

public:
    // Конструкторы
    HouseholdItem();// создает пустой объект
    explicit HouseholdItem(const char* itemName);// создает объект с заданным именем, используя делегирование конструкторов
    HouseholdItem(const HouseholdItem& other);//конструктор копирования

    // Деструктор
    ~HouseholdItem();//освобождаем динамическую паммять

    // Оператор присваивания
    HouseholdItem& operator=(const HouseholdItem& other);//безопасное присваивания объектов

    // Селекторы//читаем поля без возможностии изменений
    const char* const getName() const;
    double getCurrentPrice() const;
    double getMaxPrice() const;
    double getMinPrice() const;
    int getTotalOrdered() const;
    double getTotalSpent() const;
    double getAveragePrice() const;

    // Методы
    void purchase(int quantity, const double& price);//покупка
    void print() const;
};

#endif // HOUSEHOLD_ITEM_H