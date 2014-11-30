#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <iostream>
#include <vector>

class Chamber;
class Tile;
class AbstractEnemy;
class AbstractItem;

class Floor {
public:
	Floor();
	Floor(std::istream &);
	~Floor();

	void generateExit();

	void addChamber(Chamber*);
	Chamber *getRandomChamber() const;
	Chamber *getChamber(int) const;

	void addPassage(Tile*);
	Chamber *getPassages() const;

	AbstractEnemy *addEnemy(AbstractEnemy*);
	void generateEnemy();

	AbstractItem *addItem(AbstractItem*);
	void generatePotion();
	void generateGoldPile();

	/*
	 *	A brief explanation on overloads of getChamber():
	 *		getChamber(int i) returns the Chamber with id i.
	 *		getChamber(int r, int c) returns the Chamber that owns the tile
	 *			specified by (r, c).
	 *		getChamber(Tile *t) returns the Chamber that owns the tile t.
	 */
	Tile *getTile(int, int) const;
	Chamber *getChamber(int, int) const;
	Chamber *getChamber(Tile*) const;

	void setPlayerPos(int, int);
	int getPlayerR() const;
	int getPlayerC() const;
	void render();

protected:
	Tile *getRandomUnoccupiedTile() const;

private:
	std::vector<Chamber*> chambers;
	std::vector<AbstractEnemy*> enemies;
	std::vector<AbstractItem*> items;
	int playerR;
	int playerC;

	// We count how many goldPiles / potions we have on the floor solely for the
	// purpose of generation.
	int goldPiles;
	int potions;

	// Explanation: Chamber happens to hold exactly the properties that we need.
	// Rather than making it into a TileContainer and making Chamber an empty
	// subclass of that, we simply make use of Chamber as is.
	// TODO maybe refactor... if I don't run out of time.
	Chamber *passages;
};

#endif
