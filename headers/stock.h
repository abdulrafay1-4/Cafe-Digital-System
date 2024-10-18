#include"header.h"

#ifndef stock_H
#define stock_H

class stock {
private:
    char itemName[18];
    int quantity;
    double price;
    double total_price;
public:
    stock();
    stock(char*, int, double);
    void updateStock(int, int);

    void addItem(const char *, int, double);
    void removeItem(const char *);

    bool searchStock(const char *);
    int findItem(char[]);

    int checkPrice(const char *);
    void updateQuantity(int, int);

    void calculateTotal(int);
    void randomQuanDecrease();

    operator int();//conversion function

    void sortStock();
    ~stock();

    const char *getItemName() const;
    int getQuantity() const;
    double getPrice() const;
    int getObjects();

    void setItemDetails(const char *, int, double);

    friend ostream &operator<<(ostream &, stock &);
};

#endif