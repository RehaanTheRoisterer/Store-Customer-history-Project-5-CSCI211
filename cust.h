#ifndef CUST_H
#define CUST_H

#include <iostream>
using namespace std;

class Cust
{
private:
    string m_name;
    bool is_robber;
    int arrival_time = 1;
    int no_items;
    int m_shopTime;

public:
    Cust(string m_name, bool is_robber, int arrival_time, int no_items);
    string get_name()
    {
        return m_name;
    }
    bool get_is_robber()
    {
        return is_robber;
    }
    int get_time()
    {
        return arrival_time;
    }
    int get_itemNo()
    {
        return no_items;
    }
    int get_shopTime()
    {
        return m_shopTime;
    }
    void set_shopTime(int t)
    {
        m_shopTime = t;
    }
    void print_entered(ostream &os, int clock);
    void print_shopping(ostream &os);
    void print_checkout(ostream &os, int clock, int checker);
    void print_paid(ostream &os, int clock, int checker);
    void print_stole(ostream &os, int clock, int checkerAmount, int checker);
};

#endif