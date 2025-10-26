#include "HouseholdItem.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== Testing HouseholdItem Class ===" << std::endl;

        // Test 1: Basic functionality
        HouseholdItem item1("Chair");
        item1.purchase(2, 1500.0);
        item1.purchase(1, 1800.0);
        std::cout << "Item 1:" << std::endl;
        item1.print();

        // Test 2: Copy constructor
        HouseholdItem item2 = item1;
        std::cout << "\nItem 2 (copy of item1):" << std::endl;
        item2.print();

        // Test 3: Assignment operator
        HouseholdItem item3("Table");
        item3 = item1;
        std::cout << "\nItem 3 (assigned from item1):" << std::endl;
        item3.print();

        std::cout << "\n=== All tests passed! ===" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}