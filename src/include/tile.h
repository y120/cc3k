#ifndef __TILE_H__
#define __TILE_H__

#include <string>
#include <vector>
#include <map>
#include "renderable.h"
#include "tileType.h"

class Chamber;

class Tile : public Renderable {
public:
	// contents can be null, in which case default is rendered.
	Tile(int r, int c, TileType tt, Renderable *contents = NULL);

	// True if it's a door tile, a passage tile, an unoccupied floor tile, or
	// a floor tile occupied by an item.
	bool isPassableByPlayer() const;
	// True if it's an unoccupied floor tile.
	bool isPassableByEnemy() const;
	// True if it's occupied. Walls are considered unoccupied.
	bool isOccupied() const;
	// True if it's a specific TileType.
	bool is(TileType) const;

	TileType getTileType() const;
	void setTileType(TileType tt);

	Renderable* getContents() const;
	void setContents(Renderable*);

	int getDistance(Tile*) const;
	int getTaxicabDistance(Tile*) const;

	const std::vector<Tile*>& getNeighbours() const;
	std::vector<Tile*> getUnoccupiedNeighbours() const;

	Chamber *getChamber() const;
	void setChamber(Chamber *);

	// Changed display code - render() no longer returns a string
	//std::string render();

	std::map<TileType, Renderable> &getTileset();
	void render();

private:
	Chamber *chamber;
	TileType tt;
	Renderable *contents;
};

#endif
