#include "player.h"

class PlayerBase : public Player
{
public:
    bool draw(Card dealer, const Hand &player)
    {
        /* hard */
        HandValue state = player.handValue();
        if(!state.soft)
        {
            //if (state.count <= 11) return true;
            if (state.count == 12)
            {
                if (dealer.spot >= FOUR && dealer.spot <= SIX) return false;
            }
            else if (state.count >= 13 && state.count <= 16)
            {
                if (dealer.spot >= TWO && dealer.spot <= SIX) return false;
            }
            else if (state.count >= 17)
            {
                return false;
            }
            return true;
        }
        /* soft */
        else
        {
            //if (state.count <= 17) return true;
            if (state.count == 18)
            {
                if (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) return false;
            }
            else if (state.count >= 19)
            {
                return false;
            }
            return true;
        }
    }
};

class PlayerSimple : public PlayerBase
{
    int bet(unsigned int bankroll, unsigned int minimum) 
    {
        return minimum;
    }
    void shuffled() {};
    void expose(Card c) {};
};


class PlayerCounting : public PlayerBase
{
    int runningCount;
public:
    int bet(unsigned int bankroll, unsigned int minimum) 
    {
        return (runningCount >= 2 && bankroll >= 2*minimum) ?
                2*minimum : minimum;
    }
    void shuffled() 
    {
        runningCount = 0;
    };
    void expose(Card c) 
    {
        if (c.spot <= SIX) runningCount++;
        else if (c.spot >= TEN) runningCount--;
    };
};

Player* get_Simple()
{
    static PlayerSimple ps;
    return &ps;
}

Player* get_Counting()
{
    static PlayerCounting pc;
    return &pc;
}
