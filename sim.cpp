#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include "pqueue.h"
#include "cust.h"
using namespace std;

struct Checker // manages checker
{
    int money;
    int done_time;
    Cust *current;
};

void workflow(Pqueue &arrival_q, int checkerNo, int breakLength, ostream &os);
bool legal_int(char *str); // makes sure command line arguments only get numbers

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cerr << "Error: invalid number of command line arguments." << endl;
        exit(1);
    }

    int checkerNo = atoi(argv[1]);
    int breakLength = atoi(argv[2]);

    ifstream input(argv[3]);
    if (!input)
    {
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        exit(1);
    }

    if (!legal_int(argv[1]))
    {
        cerr << "Error: invalid number of checkers specified." << endl;
        exit(1);
    }

    if (!legal_int(argv[2]))
    {
        cerr << "Error: invalid checker break duration specified." << endl;
        exit(1);
    }
    ofstream output(argv[4]);
    if (!output)
    {
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        exit(1);
    }

    Pqueue arrival_q; // queue for entry
    string new_name;
    string new_role;
    int new_time;
    int new_items;
    bool role;
    while (input >> new_name >> new_role >> new_time >> new_items) // separating input into variables
    {
        role = (new_role == "robber");
        Cust *new_cust = new Cust(new_name, role, new_time, new_items);
        arrival_q.enqueue(new_cust, new_time);
    }

    workflow(arrival_q, checkerNo, breakLength, output);
    return 0;
}

void workflow(Pqueue &arrival_q, int checkerNo, int breakLength, ostream &os)
{
    Checker *checkers = new Checker[checkerNo]; // dynamic array
    for (int i = 0; i < checkerNo; i++)
    {
        checkers[i].money = 250;
        checkers[i].done_time = 0;
        checkers[i].current = NULL;
    }

    Pqueue ShopQueue;
    Pqueue CheckoutQueue;
    int num_customers = arrival_q.length();
    int clock = 1;

    for (; num_customers > 0; clock++)
    {

        while (!arrival_q.empty() &&
               arrival_q.get_priority_of_first_elem() == clock)
        {
            Cust *new_class = arrival_q.dequeue();
            new_class->print_entered(os, clock);
            int shopTime = clock + 2 * new_class->get_itemNo();
            new_class->set_shopTime(shopTime); // time when shopping is done
            ShopQueue.enqueue(new_class, shopTime);
        }

        while (!ShopQueue.empty() &&
               ShopQueue.get_priority_of_first_elem() <= clock)
        {
            Cust *new_class = ShopQueue.dequeue();
            new_class->print_shopping(os);
            CheckoutQueue.enqueue(new_class, 0);
        }

        for (int i = 0; i < checkerNo; i++)
        {
            if (checkers[i].current != NULL && checkers[i].done_time == clock)
            {
                Cust *new_class = checkers[i].current;
                if (!new_class->get_is_robber())
                {
                    new_class->print_paid(os, clock, i);
                    checkers[i].money += new_class->get_itemNo() * 3;
                }
                else
                {
                    new_class->print_stole(os, clock, checkers[i].money, i);
                    checkers[i].money = 0;
                    checkers[i].done_time = clock + breakLength;
                }
                num_customers--;
                delete new_class;
                checkers[i].current = NULL;
            }
        }

        while (!CheckoutQueue.empty())
        {
            int avail = -1;
            for (int i = 0; i < checkerNo; i++)
            {
                if (checkers[i].current == NULL && checkers[i].done_time <= clock)
                {
                    avail = i;
                    break;
                }
            }
            if (avail == -1)
                break;

            Cust *new_class = CheckoutQueue.dequeue();
            checkers[avail].current = new_class;
            new_class->print_checkout(os, clock, avail);
            checkers[avail].done_time = clock +
                                        (new_class->get_is_robber() ? 7 : new_class->get_itemNo());
        }
    }

    for (int i = 0; i < checkerNo; i++)
        os << "registers[" << i << "] = $" << checkers[i].money << endl;
    os << "time = " << clock << endl;

    delete[] checkers;
}

bool legal_int(char *str)
{
    if (str == NULL || *str == '\0')
        return false;
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}