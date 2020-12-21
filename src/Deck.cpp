#include <iostream>
#include "Deck.hpp"

// Ctor
Deck::Deck(const vector<Card*> &_deckOfCards) : deck_of_cards(_deckOfCards) {
    std::cout << "construction of Deck" << std::endl;
}

// Dtor
Deck::~Deck() = default;

// Getters :

const vector<Card*> &Deck::getDeckOfCards() const {
    return deck_of_cards;
}

// Other methods :

// Stack a new card in the deck of cards.
void Deck::addCard(Card *pCard) {
    deck_of_cards.push_back(pCard);
}

Card *Deck::getCard() {
    Card* temp = deck_of_cards.back();
    deck_of_cards.pop_back();

    return temp;
}
