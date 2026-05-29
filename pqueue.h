#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include "cust.h"

using namespace std;

class Pqueue
{
private:
    class Node
    {
    public:
        Node *m_next;
        Cust *cust;
        int m_prio;
        Node(Cust *class_cust, int prio, Node *next);
    };
    Node *m_head;

public:
    Pqueue()
    {
        m_head = nullptr;
    }

    void enqueue(Cust *class_cust, int prio);
    int get_priority_of_first_elem();
    bool empty();
    int length();
    Cust *dequeue();
};

#endif