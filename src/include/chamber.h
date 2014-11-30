#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include <string>
#include <vector>
#include <map>

#include "floor.h"

class Renderable;
class Tile;
enum class TileType;

// A Chamber holds all the tiles within said chamber, including walls and doors.
class Chamber {
public:
	Chamber(int id = 0);
	Chamber(Floor *, std::vector<std::string> &, int, int);
	~Chamber();

	Tile *addTile(int, int, TileType, Renderable*);
	Tile *addTile(Tile*);

	Tile *getTile(int, int) const;
	Tile *getUnoccupiedTile() const;

	int getId() const;
	void setId(int);

	Floor *getFloor() const;
	void setFloor(Floor *);

	void floodFill(std::vector<std::string> &, int, int);

	void render();

private:
	int id;
	Floor *floor;
	std::map<std::pair<int, int>, Tile*> tiles; 
};

#endif
