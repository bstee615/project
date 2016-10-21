#ifndef COIN_H
#define COIN_H

#include"object.h"
#include"collectible.h"

class Coin : public Collectible
{
	private:
		int amount;
	public:
		int getAmount() { return amount; }
		void set Amount(int newAmount) { amount = newAmount; }
};

#endif // COIN_H
