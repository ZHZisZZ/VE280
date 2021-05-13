#include "deck.h"

Deck::Deck()
{
    reset();
}

void Deck::reset()
{
    next = 0;
    int index = 0;
    for (int suit = 0; suit < DIAMONDS + 1; suit++)
    {
        for (int spot = 0; spot < ACE + 1; spot++)
        {
            deck[index++] = {(Spot)spot, (Suit)suit};
        }
    }
}

void Deck::shuffle(int n)
{
    next = 0;
    Card tempDeck[DeckSize];
    for (int i = 0; i < DeckSize; i++) 
    {
        tempDeck[i] = deck[i];
    }

    for (int index = 0, i = 0, j = n; index < DeckSize; i++, j++)
    {
        if (j < DeckSize) deck[index++] = tempDeck[j];
        if (i < n) deck[index++] = tempDeck[i];
    }
}

Card Deck::deal()
{
    if (next < DeckSize) return deck[next++];
    else throw DeckEmpty();
}

int Deck::cardsLeft()
{
    return DeckSize - next;
}
