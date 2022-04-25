#include "card.h"
#include "player.h"
#include <iostream>
using namespace std;

player::player()
{
    head = NULL;
    size = 0;
}

player::player(const player &other)
{
    copy(other);
}

const player &player::operator=(const player &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

player::~player()
{
    clear();
}

void player::hand_add(card temp_card)
{
    card_elem *temp_ptr;
    temp_ptr = new card_elem();
    temp_ptr->data = temp_card;
    temp_ptr->next = head;
    head = temp_ptr;
    size++;
}

card player::hand_remove(int pos)
{
    // error checking
    if (pos < 0 || pos >= size)
    {
        return card();
    }

    card_elem *prev_ptr = head;
    card_elem *target = prev_ptr->next;
    card temp_card;
    int temp_pos = pos;

    // delete at front
    if (pos == 0)
    {
        temp_card = head->data;
        head = head->next;
        delete prev_ptr;
        size--;
        return temp_card;
    }
    // find previous element
    while (temp_pos > 1)
    {
        prev_ptr = prev_ptr->next;
        target = prev_ptr->next;
        temp_pos--;
    }
    // connect previous element to next element
    prev_ptr->next = target->next;
    temp_card = target->data;
    delete target;
    size--;
    return temp_card;
}

void player::uno()
{
}

void player::print() const
{
    int temp_size = size;

    int i = 0;
    card_elem *temp_ptr = head;
    while (temp_size > 0)
    {
        cout << i + 1 << ":  " << temp_ptr->data << endl;
        temp_ptr = temp_ptr->next;
        i++;
        temp_size--;
    }
}

void player::copy(const player &other)
{
    size = other.size;

    // create the head of target player
    if (size > 0)
    {
        head = new card_elem();
        head->data = other.head->data;
    }
    else
    {
        head = NULL;
        return;
    }

    // other_ptr to traverse the other list
    card_elem *other_ptr = other.head->next;
    // create a temp_ptr to create the rest of linked list
    card_elem *temp_ptr;
    // create a previous ptr to point next to correct one
    card_elem *prev_ptr = head;
    for (int i = 1; i < size; i++)
    {
        temp_ptr = new card_elem();
        prev_ptr->next = temp_ptr;
        temp_ptr->data = other_ptr->data;
        prev_ptr = temp_ptr;
        temp_ptr = NULL;
        other_ptr = other_ptr->next;
    }
}

void player::clear()
{
    card_elem *temp_ptr = head;
    card_elem *next_ptr;
    while (size > 0)
    {
        next_ptr = temp_ptr->next;
        delete temp_ptr;
        temp_ptr = next_ptr;
        size--;
    }
    head = NULL;
}

int player::get_size() const
{
    return size;
}

card player::peek(int pos) const
{
    int temp_pos = pos;
    card_elem *temp_elem = head;
    while (temp_pos > 0)
    {
        temp_elem = temp_elem->next;
        temp_pos--;
    }

    return temp_elem->data;
}
