#include <iostream>
#include <cstdlib>
#include <string>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

const int cutNum = 7;
const int minimum = 5;
const int minDeckNum = 20;

struct Dealer
{
    Card upCard;
    Card holeCard;
};

static void shuffleDriver(Deck& deck);
static void showCard(Card draw);
static Card showDealt(std::string Name, Deck& deck, Hand& hand, Player* player);

int main(int argc, char* argv[])
{
    int  chand = 1;
    //bool simple = true;
    Card draw;
    int  bet;
    Deck deck; // deck is reset when initalized.
    Player* player;
    Hand    playerHand;
    Dealer  dealer;
    Hand    dealerHand;

    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    if (argv[3][0] == 's')
    {
        player = get_Simple();
    }
    else 
    {
        player = get_Counting();
    }

    /* shuffle the deck */
    shuffleDriver(deck);
    
    /* initial setup */ 
    player->shuffled();  // set the running_count to zero;
    /* begin turns */
    while (chand++ <= hands && player->bet(bankroll, minimum) <= bankroll)
    {
        std::cout << "Hand " << chand-1 << " bankroll " << bankroll << std::endl;

        /* clear hand before start */
        playerHand.discardAll();
        dealerHand.discardAll();


        /* whether or not to shuffle the deck */
        if (deck.cardsLeft() < minDeckNum)
        {
            // 未知;
            shuffleDriver(deck);
            player->shuffled(); // set the running_count to zero;
        }

        bet = player->bet(bankroll, minimum);
        std::cout << "Player bets " << bet << std::endl;

        /* dealt to player and dealer */
        showDealt("Player", deck, playerHand, player);
        dealer.upCard = showDealt("Dealer", deck, dealerHand, player);
        showDealt("Player", deck, playerHand, player);
        draw = deck.deal(); dealerHand.addCard(draw); dealer.holeCard = draw; // hidden card, no expose and no cout;

        if (playerHand.handValue().count == 21)
        {
            std::cout << "Player dealt natural 21\n";
            bankroll += bet * 3 / 2;
            continue;
        }

        while (player->draw(dealer.upCard, playerHand))
        {
            showDealt("Player", deck, playerHand, player);
        }

        HandValue playerValue = playerHand.handValue();
        std::cout << "Player's total is " << playerValue.count << std::endl;

        /* bust or natural */
        if (playerValue.count > 21)
        {
            std::cout << "Player busts\n";
            bankroll -= bet;
            continue;
        }

        /* dealer's turn */
        std::cout << "Dealer's hole card is "; showCard(dealer.holeCard); player->expose(draw);
        HandValue dealerValue = dealerHand.handValue();
        while (dealerValue.count < 17  || (dealerValue.count > 21 && dealerValue.soft))
        {
            showDealt("Dealer", deck, dealerHand, player);
            dealerValue = dealerHand.handValue();
        }
        std::cout << "Dealer's total is " << dealerValue.count << std::endl;

        if (dealerValue.count > 21)
        {
            std::cout << "Dealer busts\n";
            bankroll += bet;
        }
        /* check point */
        else if (dealerValue.count > playerValue.count)
        {
            std::cout << "Dealer wins\n";
            bankroll -= bet;
        }
        else if (dealerValue.count < playerValue.count)
        {
            std::cout << "Player wins\n";
            bankroll += bet;
        }
        else 
        {
            std::cout << "Push\n";
        }
    }
    std::cout << "Player has " << bankroll << " after " << chand-2 << " hands\n";
}




/* helper functions */
static void shuffleDriver(Deck& deck)
{
    std::cout << "Shuffling the deck\n";
    for (int c = 0; c < cutNum; c++)
    {
        int cut = get_cut();
        std::cout << "cut at " << cut << std::endl;
        deck.shuffle(cut);
    }
}

static void showCard(Card draw)
{
    std::cout << SpotNames[draw.spot] << " of " << SuitNames[draw.suit] << std::endl;
}

static Card showDealt(std::string Name, Deck& deck, Hand& hand, Player* player)
{
    Card draw = deck.deal(); 
    std::cout << Name << " dealt "; showCard(draw);
    hand.addCard(draw); 
    player->expose(draw);
    return draw;
}