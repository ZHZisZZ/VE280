#include "hand.h"

Hand::Hand()
{
    discardAll();
}

void Hand::discardAll()
{
    curValue = {0, false};
}

void Hand::addCard(Card c)
{
    bool softBefore = curValue.soft;
    if (c.spot <= NINE) curValue.count += c.spot + 2;
    else if (c.spot <= KING) curValue.count += 10;
    else
    {
        curValue.count += 11;
        curValue.soft = true;
    }
    
    if (curValue.count > 21 && curValue.soft)
    {
        curValue.count -= 10;
        if (c.spot != ACE || !softBefore) curValue.soft = false;
    }
}

HandValue Hand::handValue() const
{
    return curValue;
}

