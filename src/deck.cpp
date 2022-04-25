#define DECK_SIZE 108

#include "deck.h"
#include "card.h"
#include <iostream>
#include <cstdlib>
using namespace std;

deck::deck()
{
    ptr_deck = new card[DECK_SIZE];
    size = 0;
}

void deck::create()
{
    int num = 0;

    // card rank 0
    for (int col = 1; col <= 4; col++)
    {
        ptr_deck[size].number = num;
        ptr_deck[size].color = static_cast<COLOR>(col);
        size++;
    }

    // card rank 1 till 9 , "draw-two", "skip", "reverse"
    for (num = 1; num <= 12; num++)
    {
        for (int x = 0; x < 2; x++)
        {
            for (int col = 1; col <= 4; col++)
            {
                ptr_deck[size].number = num;
                ptr_deck[size].color = static_cast<COLOR>(col);
                size++;
            }
        }
    }

    // card "wild", "wild-draw-four"
    for (num = 13; num <= 14; num++)
    {
        for (int x = 0; x < 4; x++)
        {
            ptr_deck[size].number = num;
            ptr_deck[size].color = wild;
            size++;
        }
    }
}

deck::deck(const deck &other)
{
    copy(other);
}

const deck &deck::operator=(const deck &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

deck::~deck()
{
    clear();
}

void deck::shuffle()
{
    // create a temp deck
    card *temp_deck = new card[size];
    for (int i = 0; i < size; i++)
    {
        temp_deck[i] = ptr_deck[i];
    }

    int temp_size = size;
    int temp_pos;
    int pos;
    for (int i = 0; i < size; i++)
    {
        srand(time(NULL));
        pos = rand() % temp_size;
        ptr_deck[i] = temp_deck[pos];

        temp_size--;
        for (temp_pos = pos; temp_pos < temp_size; temp_pos++)
        {
            temp_deck[temp_pos] = temp_deck[temp_pos + 1];
        }
    }

    delete[] temp_deck;
}
card deck::draw()
{
    if (size <= 0)
    {
        return card();
    }
    card temp_card = ptr_deck[size - 1];
    size--;
    return temp_card;
}

int deck::add_card(card temp_card)
{
    if (size < DECK_SIZE)
    {
        ptr_deck[size] = temp_card;
        size++;
        return 0;
    }
    else
        return -1;
}

void deck::quick_shuffle()
{
    int pos;
    int temp_size = size - 1;
    card temp_card;
    while (temp_size > 0)
    {
        srand(time(NULL));
        pos = rand() % temp_size;
        temp_card = ptr_deck[temp_size];
        ptr_deck[temp_size] = ptr_deck[pos];
        ptr_deck[pos] = temp_card;
        temp_size--;
    }
}

void deck::print_deck()
{
    for (int i = 0; i < size; i++)
    {
        cout << i << ": " << ptr_deck[i] << endl;
    }
}

void deck::copy(const deck &other)
{
    size = other.size;
    ptr_deck = new card[size];
    for (int i = 0; i < size; i++)
    {
        ptr_deck[i] = other.ptr_deck[i];
    }
}

void deck::clear()
{
    delete[] ptr_deck;
    ptr_deck = NULL;
    size = 0;
}

int deck::get_size()
{
    return size;
}
