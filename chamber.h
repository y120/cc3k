#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include <map>

class Renderable;
class Tile;
enum class TileType;

// A Chamber holds all the tiles within said chamber, including walls and doors.
class Chamber {
public:
	Chamber(int id = 0);
	~Chamber();

	void addTile(int, int, TileType, Renderable*);
	void addTile(Tile*);

	Tile *getTile(int, int) const;
	Tile *getUnoccupiedTile() const;

	int getId() const;
	void setId(int);

private:
	int id;
	std::map<std::pair<int, int>, Tile*> tiles; 
};

#endif
