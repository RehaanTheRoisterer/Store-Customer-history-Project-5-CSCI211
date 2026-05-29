#include <iostream>
#include <vector>
#include <cassert>
#include "cust.h"
using namespace std;

Cust::Cust(string name, bool bool_role, int in_time, int in_items)
{
    m_name = name;
    is_robber = bool_role;
    arrival_time = in_time;
    no_items = in_items;
}

void Cust::print_entered(ostream &os, int clock)
{
    // assert(clock == arrival_time);
    os << clock << ": " << m_name << " entered store" << endl;
}

void Cust::print_shopping(ostream &os)
{
    os << m_shopTime << ": " << m_name << " done shopping" << endl;
}

void Cust::print_checkout(ostream &os, int clock, int checker)
{
    os << clock << ": " << m_name << " started checkout with checker " << checker << endl;
}

void Cust::print_paid(ostream &os, int clock, int checker)
{
    if (no_items == 1)
    {
        os << clock << ": " << m_name << " paid $" << no_items * 3 << " for " << no_items << " item to checker " << checker << endl;
    }
    else
    {
        os << clock << ": " << m_name << " paid $" << no_items * 3 << " for " << no_items << " items to checker " << checker << endl;
    }
}

void Cust::print_stole(ostream &os, int clock, int checkerAmount, int checker)
{
    if (no_items == 1)
    {
        os << clock << ": " << m_name << " stole $" << checkerAmount << " and " << no_items << " item from checker " << checker << endl;
    }
    else
    {
        os << clock << ": " << m_name << " stole $" << checkerAmount << " and " << no_items << " items from checker " << checker << endl;
    }
}
