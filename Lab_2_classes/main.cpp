#include "HouseholdItem.h"
#include <iostream>
#include <vector>

void demonstrateOverloadedMethods() {
    std::cout << "=== DEMONSTRATING OVERLOADED METHODS AND OPERATORS ===" << std::endl;

    try {
        // 1. Демонстрация перегруженного конструктора
        std::cout << "\n1. Testing overloaded constructor:" << std::endl;
        HouseholdItem prePurchased("Pre-purchased Laptop", 3, 50000.0);
        std::cout << "Created with 3 laptops at 50000 RUB each:" << std::endl;
        prePurchased.print();

        // Конструктор с параметрами по умолчанию
        HouseholdItem defaultPrice("Item with default price", 5); // Цена по умолчанию 1.0
        std::cout << "\nCreated with 5 items at default price:" << std::endl;
        defaultPrice.print();

        // 2. Демонстрация перегруженного метода purchase
        std::cout << "\n2. Testing overloaded purchase method:" << std::endl;
        HouseholdItem chair("Office Chair");
        chair.purchase(2, 4500.0); // Обычная покупка
        std::cout << "After first purchase (2 chairs at 4500 RUB):" << std::endl;
        chair.print();

        chair.purchase(3); // Перегруженный метод - покупка по текущей цене
        std::cout << "\nAfter overloaded purchase (3 chairs at current price):" << std::endl;
        chair.print();

        // 3. Демонстрация перегруженного оператора +=
        std::cout << "\n3. Testing overloaded operator += (member):" << std::endl;
        HouseholdItem table("Dining Table");
        table.purchase(1, 25000.0); // Устанавливаем цену
        std::cout << "Initial state:" << std::endl;
        table.print();

        table += 2; // Используем перегруженный оператор
        std::cout << "\nAfter using += 2 (bought 2 more at current price):" << std::endl;
        table.print();

        // 4. Демонстрация перегруженного оператора += вне класса
        std::cout << "\n4. Testing overloaded operator += (non-member):" << std::endl;
        double totalSpent = 0.0;

        HouseholdItem item1("Item 1");
        item1.purchase(2, 1000.0);

        HouseholdItem item2("Item 2");
        item2.purchase(3, 1500.0);

        HouseholdItem item3("Item 3");
        item3.purchase(1, 2000.0);

        // Суммируем общие затраты на все товары
        totalSpent += item1;
        totalSpent += item2;
        totalSpent += item3;

        std::cout << "Item 1 total spent: " << item1.getTotalSpent() << " RUB" << std::endl;
        std::cout << "Item 2 total spent: " << item2.getTotalSpent() << " RUB" << std::endl;
        std::cout << "Item 3 total spent: " << item3.getTotalSpent() << " RUB" << std::endl;
        std::cout << "Total spent on all items: " << totalSpent << " RUB" << std::endl;

        // 5. Комбинированное использование
        std::cout << "\n5. Combined usage demonstration:" << std::endl;
        HouseholdItem smartphone("Smartphone", 10, 30000.0); // Создаем с покупкой
        std::cout << "Initial state after constructor with purchase:" << std::endl;
        smartphone.print();

        smartphone += 5; // Покупаем еще 5 по текущей цене
        std::cout << "\nAfter using += to buy 5 more:" << std::endl;
        smartphone.print();

        smartphone.purchase(3, 28000.0); // Покупаем со скидкой
        std::cout << "\nAfter purchasing 3 at discounted price:" << std::endl;
        smartphone.print();

        smartphone.purchase(2); // Покупаем еще 2 по текущей цене
        std::cout << "\nAfter purchasing 2 at current price:" << std::endl;
        smartphone.print();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void testErrorCases() {
    std::cout << "\n\n=== TESTING ERROR CASES ===" << std::endl;

    try {
        HouseholdItem item("Test Item");

        // Попытка использовать перегруженный purchase без установленной цены
        std::cout << "Testing purchase without set price:" << std::endl;
        item.purchase(5); // Должно бросить исключение

    }
    catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
        // Конструктор с некорректными параметрами
        HouseholdItem invalid("Invalid", -5, 100.0);
    }
    catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

int main() {
    demonstrateOverloadedMethods();
    testErrorCases();

    std::cout << "\n\n=== PROGRAM COMPLETED ===" << std::endl;
    return 0;
}
