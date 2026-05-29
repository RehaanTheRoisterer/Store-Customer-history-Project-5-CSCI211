#include <iostream>
#include "pqueue.h"
#include "cust.h"
using namespace std;

Pqueue::Node::Node(Cust *class_cust, int prio, Node *next)
{
    cust = class_cust;
    m_prio = prio;
    m_next = next;
}

int Pqueue::get_priority_of_first_elem()
{
    if (m_head == nullptr)
    {
        return -1;
    }
    return m_head->m_prio;
}

bool Pqueue::empty()
{
    return m_head == nullptr;
}

int Pqueue::length()
{
    int length = 0;

    Node *ptr = m_head;
    while (ptr != nullptr)
    {
        ptr = ptr->m_next;
        length++;
    }

    return length;
}

void Pqueue::enqueue(Cust *class_cust, int prio)
{

    Node *newNode = new Node(class_cust, prio, nullptr);

    if (m_head == nullptr || prio < m_head->m_prio)
    {
        newNode->m_next = m_head;
        m_head = newNode;
        return;
    }

    Node *cur = m_head;

    while (cur->m_next != nullptr && cur->m_next->m_prio <= prio)
    {
        cur = cur->m_next;
    }

    newNode->m_next = cur->m_next;
    cur->m_next = newNode;
}

Cust *Pqueue::dequeue()
{
    if (m_head == nullptr)
    {
        return nullptr;
    }

    Node *temp = m_head;
    m_head = m_head->m_next;

    Cust *c = temp->cust;

    delete temp;

    return c;
}
