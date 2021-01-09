#include <iostream>
#include "HuitAmericain.hpp"

HuitAmericain::HuitAmericain(Deck *_deck, int player) : Game(_deck, player){
    colors = new COLOR[5];
    colors[0] = TREFLE;
    colors[1] = COEUR;
    colors[2] = CARREAU;
    colors[3] = PIQUE;
    colors[4] = NONE;

    joueurs.push_back(new Player(0, "Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player(1, "Yacine", vector<Card *> {}, 0));

    cardOnTop = new ColoredCard("3", 3, 3, TREFLE);
    cout << "CONSTRUC 8US : ACTUAL " << actualPlaying << endl;
}

void HuitAmericain::createCards() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};

    // cards  3 - 7 (Leur propre valeur numérale)
    for (int numero = 3; numero <= 7; numero++){
        for (int symbol = 0; symbol < 4; symbol++){
            deck->addCard(new ColoredCard(to_string(numero), numero, numero, symbols[symbol]));
        }
    }
    // cards  "9" (leur propre valeur numérale)
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard(to_string(9), 9,9,symbols[symbol]));
    }

    // cards  "Dame" and "Roi" (value 10 points)
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard("DAME", 10,10,symbols[symbol]));
        deck->addCard(new ColoredCard("ROI", 11,10,symbols[symbol]));
    }

    // cards  Valet, AS, 2 (value 20 points )
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard("VALET", 12,20, symbols[symbol]));
        deck->addCard(new ColoredCard("AS", 13,20, symbols[symbol]));
        deck->addCard(new ColoredCard("2", 2,20, symbols[symbol]));
    }

    // cards "8" and "Joker" : (value 50 points )
    // (4 cartes de 8 et 2 cartes de jocker avec NONE comme symbol)
    for (int symbol = 0; symbol < 4; symbol++)
        deck->addCard(new ColoredCard(to_string(8),  8,50, symbols[4]));

    deck->addCard(new ColoredCard("JOKER", 14, 50, symbols[4]));
    deck->addCard(new ColoredCard("JOKER", 14, 50, symbols[4]));
}

void HuitAmericain::startGame() {
    initGame();

}

//modifications a faire pour le controller !!
void HuitAmericain::playRound(int indexCardToPlay) {
    if(playerCanPlay(joueurs[actualPlaying]->getHand())){
        Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
        if(cardPlayable(temp)){
            deck->addCard(cardOnTop);
            cardOnTop = temp;
            getIndexOfParseCard();

            nextPlayer();
        }else{
            cout << "La carte ne peut pas etre jouée" << endl;
        }
    }else{
        nextPlayer();
    }
}

int HuitAmericain::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 2://2
            nextPlayer();
            plusTwo();
            break;
        case 8: //8
            changeColor();
            return 1;
        case 10://VALET
            nextPlayer();
            break;
        case 12: //AS
            reversed();
            break;
        case 13://JOKER
            nextPlayer();
            plusFour();
            break;
    }

    return 0;
}

bool HuitAmericain::isWinner() {
    for(Player* player : joueurs){
        if(player->handEmpty()){
            return true;
        }
    }

    return false;
}

int HuitAmericain::getWinner() {
    int winner = -1;
    for(int i = 0; i < joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            winner = i;
        }else{
            setPoints(i);
        }
    }

    return winner;
}

void HuitAmericain::plusTwo() {
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck->getCard());
    }
}

void HuitAmericain::plusFour(){
    for(int i = 0; i < 4; i ++){
        joueurs[actualPlaying]->addCard(deck->getCard());
    }
}

void HuitAmericain::reversed(){
    sensInverse = !sensInverse;
}

void HuitAmericain::nextPlayer() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);

    actualPlaying = actualPlaying % (int)joueurs.size();
}

void HuitAmericain::changeColor() {
    int color = -1;

    do{
        cout << "Choisissez la nouvelle couleur: \n";
        cout << "  1 pour " << colors[0] << endl;
        cout << "  2 pour " << colors[1] << endl;
        cout << "  3 pour " << colors[2] << endl;
        cout << "  4 pour " << colors[3] << endl;
        cin >> color;

    } while (color < 0 || color > 4);

    switch (color) {
        case 1:
            colors[4] = colors[0];
            break;
        case 2:
            colors[4] = colors[1];
            break;
        case 3:
            colors[4] = colors[2];
            break;
        case 4:
            colors[4] = colors[3];
            break;
        default:
            cout << "Couleur Modifiée";
            break;
    }
}

bool HuitAmericain::cardPlayable(Card *toPlay) {

    return *dynamic_cast<ColoredCard*>(cardOnTop) == *dynamic_cast<ColoredCard*>(toPlay);
}

bool HuitAmericain::playerCanPlay(const vector<Card *>& hand) {
    for(Card* card : hand){
        if(cardPlayable(card)){
            return true;
        }
    }

    return false;
}

void HuitAmericain::print(ostream &out) {
    out << "Les Joueurs :" << endl;

    for(Player* player : joueurs){
        out << player-> getName() << " a " << player->getCurrentScore() << " points" << endl;
    }

    out << "Carte au dessus" << endl;
    out << *dynamic_cast<ColoredCard*>(cardOnTop);

    out << "ACUTIAL PLAYING" << actualPlaying;

    out << "la main de " << joueurs.at(actualPlaying)->getName() << endl;

    for(Card* card : joueurs.at(actualPlaying)->getHand()){
        out << *dynamic_cast<ColoredCard*>(card);
    }

}

void HuitAmericain::setPoints(int iPlayer) {
    for(Card* card : joueurs[iPlayer]->getHand()){
        joueurs[iPlayer]->setCurrentScore(joueurs[iPlayer]->getCurrentScore() +card->getValue());
    }
}

void HuitAmericain::distribution() {
    deck->distributeCards(7, joueurs);
}
