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

    void calculateAverage();//������ ������� ����
    void validateName(const char* nameValid) const; // ������������ ����� 
    void validatePrice(double price) const;// ������������ ����
    void validateQuantity(int quantity) const;//������������ ������������

public:
    // ������������
    HouseholdItem();// ������� ������ ������
    explicit HouseholdItem(const char* itemName);// ������� ������ � �������� ������, ��������� ������������� �������������
    HouseholdItem(const HouseholdItem& other);//����������� �����������

    // ����������
    ~HouseholdItem();//����������� ������������ �������

    // �������� ������������
    HouseholdItem& operator=(const HouseholdItem& other);//���������� ������������ ��������

    // ���������//������ ���� ��� ������������ ���������
    const char* const getName() const;
    double getCurrentPrice() const;
    double getMaxPrice() const;
    double getMinPrice() const;
    int getTotalOrdered() const;
    double getTotalSpent() const;
    double getAveragePrice() const;

    // ������
    void purchase(int quantity, const double& price);//�������
    void print() const;
};

#endif // HOUSEHOLD_ITEM_H