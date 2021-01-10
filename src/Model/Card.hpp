#ifndef CARD_GAMES_FRAMEWORK_CARD_HPP
#define CARD_GAMES_FRAMEWORK_CARD_HPP

#include <string>


using namespace std;

class Card {
private:
    const string name;
    const int id;

protected:
    int value;

public:
    // Ctor and Dtor :
    Card(const string &_name, int _id, int _value);
    virtual ~Card();

    // Getters and Setters :
    int getId() const;
    string getName() const;
    int getValue() const;

    virtual bool operator== (Card const & other) const;
    virtual bool operator> (Card const & other) const;
    friend ostream& operator<<(ostream& out, const Card &fs);
};


#endif //CARD_GAMES_FRAMEWORK_CARD_HPP
