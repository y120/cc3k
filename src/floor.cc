#include "floor.h"

#include "game.h"
#include "player.h"
#include "chamber.h"
#include "tile.h"
#include "tileType.h"
#include "abstractItem.h"
#include "abstractPotion.h"
#include "basePotions.h"
#include "goldPile.h"
#include "dragonHoard.h"
#include "abstractEnemy.h"
#include "baseEnemies.h"

#include <iostream>
#include <queue>
#include <functional>

/**
 *	Constructor. Initialise passages and # of goldPiles / potions. The chambers,
 *	enemies, and items vectors will initialise automatically to empty, but we
 *	will reserve space for the vectors.
 */
Floor::Floor() : goldPiles(0), potions(0), passages(new Chamber()) {
	passages->setFloor(this);
	this->chambers.reserve(Game::getInstance()->getMaxChambers());
	this->enemies.reserve(Game::getInstance()->getMaxEnemies());
	this->items.reserve(Game::getInstance()->getMaxPotions() + Game::getInstance()->getMaxGoldPiles());
}

/**
 *	Constructs a floor from an input stream
 */
Floor::Floor(std::istream &iss) : goldPiles(0), potions(0), passages(new Chamber()) {
	passages->setFloor(this);
	this->chambers.reserve(Game::getInstance()->getMaxChambers());
	this->enemies.reserve(Game::getInstance()->getMaxEnemies());
	this->items.reserve(Game::getInstance()->getMaxPotions() + Game::getInstance()->getMaxGoldPiles());
	// default constructor above
	//std::cerr << "Floor: constructor " << std::endl;
	int row = 25, col = 79;
	std::vector<std::string> store(row, "");
	for (int l0 = 0; l0 < row; l0++) {
		getline(iss, store[l0]);
		//std::cerr << store[l0] << '\n';
	}
	//std::cerr << "Floor: got lines " << std::endl;
	for (int l0 = 1; l0 < row - 1; l0++) {
		for (int l1 = 1; l1 < col - 1; l1++) {
			if (store[l0][l1] == '#') {
				this->addPassage(new Tile(l0, l1, TileType::PassageTile));
			} else if (store[l0][l1] != ' ' && 
					   store[l0][l1] != '|' &&
					   store[l0][l1] != '-' &&
					   store[l0][l1] != '+') {
				this->addChamber(new Chamber(this, store, l0, l1));
			}
		}
	}
}

/**
 *	Destructor. Delete all chambers, enemies, and items, as well as passages.
 */
Floor::~Floor() {
	for (std::vector<Chamber*>::iterator i = this->chambers.begin(); i != this->chambers.end(); ++i) {
		delete *i;
	}
	for (std::vector<AbstractEnemy*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i) {
		delete *i;
	}
	for (std::vector<AbstractItem*>::iterator i = this->items.begin(); i != this->items.end(); ++i) {
		delete *i;
	}
	delete this->passages;
}

/**
 *	Generates the exit (staircase). This cannot be in the same Chamber as the
 *	PC.
 *
 *	Note that the exit is not actually stored anywhere; it's just marked as such
 *	within the Tile class.
 */
void Floor::generateExit() {
	// To generate the exit, we first choose the Chamber. To do this, we just
	// randomly choose chambers until we get one that is NOT the one the PC is
	// in. We do this because PC position is generated before exit generation.
	// We also ensure that the selected Chamber actually has an unoccupied tile.
	Chamber *chamber;
	Chamber *chamberPC = this->getChamber(Game::getInstance()->getPlayer()->getTile());
	Tile *tile;
	do {
		chamber = this->getRandomChamber();
	} while (chamber == chamberPC || !(tile = chamber->getUnoccupiedTile()));
	tile->setTileType(TileType::ExitTile);
}

/**
 *	Adds a chamber to the list of chambers, setting the ID appropriately.
 */
void Floor::addChamber(Chamber *chamber) {
	//std::cerr << "Floor: addChamber " << std::endl;
	this->chambers.push_back(chamber);
	chamber->setId(this->chambers.size());
	chamber->setFloor(this);
}

/**
 *	Gets a random Chamber.
 */
Chamber *Floor::getRandomChamber() const {
	return this->chambers[Game::getInstance()->rand(this->chambers.size())];
}

/**
 *	Gets a specific Chamber by ID.
 */
Chamber *Floor::getChamber(int id) const {
	return this->chambers.at(id - 1);
}

/**
 *	Registers a Passage tile.
 */
void Floor::addPassage(Tile *t) {
	this->passages->addTile(t);
}

/**
 *	Returns a fake Chamber holding the passages.
 */
Chamber *Floor::getPassages() const {
	return this->passages;
}

/**
 *	Registers an Enemy to this floor.
 */
AbstractEnemy *Floor::addEnemy(AbstractEnemy *enemy) {
	this->enemies.push_back(enemy);
	return enemy;
}

/**
 *	Generates and registers an Enemy to this floor.
 */
void Floor::generateEnemy() {
	// We limit generation to the max, as specified by the Game.
	if ((int)this->enemies.size() >= Game::getInstance()->getMaxEnemies()) {
		return;
	}

	// To spawn an enemy, we first select the Chamber and Tile. Then, we choose
	// the Enemy type, and finally we register it.

	Tile *tile = this->getRandomUnoccupiedTile();

	/* Enemy probability distribution:
	 * Human: 2/9
	 * Dwarf: 3/18
	 * Halfling: 5/18
	 * Elf: 1/9
	 * Orc: 1/9
	 * Merchant: 1/9
	 */
	AbstractEnemy *enemy;
	switch (Game::getInstance()->rand(18)) {
		case 0: case 1: case 2: case 3: // 2/9 = 4/18
			enemy = new Human();
			break;
		case 4: case 5: case 6: // 3/18
			enemy = new Dwarf();
			break;
		case 7: case 8: case 9: case 10: case 11: // 5/18
			enemy = new Halfling();
			break;
		case 12: case 13: // 1/9 = 2/18
			enemy = new Elf();
			break;
		case 14: case 15: // 1/9 = 2/18
			enemy = new Orc();
			break;
		case 16: case 17: // 1/9 = 2/18
			enemy = new Merchant();
			break;
	}

	// Now, having decided the enemy, set its position and register it.
	enemy->moveTo(tile);
	this->addEnemy(enemy);
}

/**
 *	Adds an item to the item list.
 */
AbstractItem *Floor::addItem(AbstractItem *item) {
	// If it's a goldPile, increment that count.
	if (dynamic_cast<GoldPile*>(item)) {
		this->goldPiles++;
	} else if (dynamic_cast<AbstractPotion*>(item)) {
		this->potions++;
	}
	this->items.push_back(item);
	return item;
}

/**
 *	Creates and adds a random Potion.
 */
void Floor::generatePotion() {
	// First, check if we're allowed to add this potion.
	if (this->potions >= Game::getInstance()->getMaxPotions()) {
		return;
	}

	// As before, select the Tile first, then place the Potion.
	Tile *tile = this->getRandomUnoccupiedTile();

	// Each Potion has a 1/6 chance of being selected.
	AbstractPotion *potion;
	switch (Game::getInstance()->rand(6)) {
		case 0:
			potion = new RHPotion();
			break;
		case 1:
			potion = new BAPotion();
			break;
		case 2:
			potion = new BDPotion();
			break;
		case 3:
			potion = new PHPotion();
			break;
		case 4:
			potion = new WAPotion();
			break;
		case 5:
			potion = new WDPotion();
			break;
	}

	// Unlike for Enemy generation, in Item generation, we just set the Tile
	// contents directly.
	tile->setContents(potion);
	this->addItem(potion);
}

/**
 *	Creates and adds a random GoldPile.
 *
 *	Note there are some special generation semantics here.
 */
void Floor::generateGoldPile() {
	// Again, first check if we're allowed to add the GoldPile.
	if (this->goldPiles >= Game::getInstance()->getMaxGoldPiles()) {
		return;
	}

	// Then, again, pick a Tile and then what kind of GoldPile.
	Tile *tile = this->getRandomUnoccupiedTile();

	// 5/8 normal, 1/8 dragon, 1/4 small.
	GoldPile *goldPile;
	switch (Game::getInstance()->rand(8)) {
		case 0: case 1: // 1/4 = 2/8
			goldPile = new GoldPile(GoldPile::SmallPile);
			break;
		case 2: case 3: case 4: case 5: case 6: // 5/8
			goldPile = new GoldPile(GoldPile::NormalPile);
			break;
		case 7: // 1/8
			// When generating a Dragon Hoard, we must also create and assign
			// a dragon to one of the surrounding blocks.
			// If there is no surrounding block, we regenerate the tile until
			// we get one.
			Tile *dragonTile = NULL;
			do {
				// Check that there exists some unoccupied Tile surrounding this.
				// If not, generate Tiles until we get one.
				std::vector<Tile*> unoccupied;
				for (int dr = -1; dr <= 1; dr++) {
					for (int dc = -1; dc <= 1; dc++) {
						if (!(dr == 0 && dc == 0)) {
							Tile *t = this->getTile(tile->getR() + dr, tile->getC() + dc);
							if (t == NULL) {
								continue;
							}

							if (t->is(TileType::FloorTile) && !t->isOccupied()) {
								unoccupied.push_back(t);
							}
						}
					}
				}

				if (unoccupied.size()) {
					dragonTile = unoccupied[Game::getInstance()->rand(unoccupied.size())];
				} else {
					tile = this->getRandomUnoccupiedTile();
				}
			} while (dragonTile == NULL);

			// Now create the dragon!
			Dragon *dragon = new Dragon(tile);
			// Then, create the Hoard.
			goldPile = new DragonHoard(dragon);
			break;
	}

	// Finally, set the Tile and register the GoldPile.
	tile->setContents(goldPile);
	this->addItem(goldPile);
}

/**
 *	Gets a Tile, given row and column.
 *	If the Tile can't be found in a Chamber or a Passage, returns NULL.
 */
Tile *Floor::getTile(int r, int c) const {
	Tile *tile = this->passages->getTile(r, c);
	for (int i = 0; !tile && i < (int)this->chambers.size(); i++) {
		tile = this->chambers[i]->getTile(r, c);
	}
	return tile;
}

/**
 *	Gets the Chamber that owns a tile, or NULL if none. Does not search
 *	passages.
 */
Chamber *Floor::getChamber(int r, int c) const {
	for (int i = 0; i < (int)this->chambers.size(); i++) {
		if (this->chambers[i]->getTile(r, c)) {
			return this->chambers[i];
		}
	}
	return NULL;
}

/**
 *	As above, but with a Tile instead of a pair of ints.
 */
Chamber *Floor::getChamber(Tile *tile) const {
	return tile == NULL ? NULL : this->getChamber(tile->getR(), tile->getC());
}

/**
 *	Randomly generates the floor layout. First clears all chambers.
 *
 *	We do this by first selecting five "seeds" -- these are where the chambers
 *	will be generated from. We then grow these out for an appropriate amount of
 *	time.
 *
 *	For this, we pretend the board is 75x21 (to have a nice buffer area!) and
 *	ensure that when growing each room, we do not infringe on any neighbouring
 *	areas. (All neighbouring tiles become 'owned' by a room when a tile is
 *	generated.)
 */
void Floor::generate() {
	using namespace std;

	// Approximate desired size. Can generate larger or smaller.
	const int REQUIRED = 90;
	const int DESIRED = 130;
	const int MAXIMUM = 150;

	const int MAX_ROWS = 21;
	const int MAX_COLS = 75;

	/**
	 *	Returns the chance of generating another tile, in percentage.
	 *
	 *	Until we have sqrt(desired), always generate a tile.
	 *	Otherwise, the chance should gradually get smaller, such that there is
	 *	a 50% chance of generation when size = desired.
	 */
	auto getGenerationChance = [=] (int size) {
		if (size < REQUIRED) {
			return 100;
		} else if (size > MAXIMUM) {
			return 0;
		} else {
			int d = DESIRED - size;
			return 50 + d;
		}
	};

	// A tile owned by a Chamber can only be used by that chamber.
	int owner[MAX_ROWS][MAX_COLS] = {};
	// Contains a representation of the board (easy printing).
	char board[MAX_ROWS][MAX_COLS] = {};
	// Whether a tile is a vertical wall or not.
	bool vert[MAX_ROWS][MAX_COLS] = {};

	// Returns true if r, c is actually in bounds.
	auto inBounds = [] (int r, int c) {
		return r >= 0 && c >= 0 && r < MAX_ROWS && c < MAX_COLS;
	};

	// Sets a tile and its 9 surrounding tiles as owned by a specific chamber.
	// The further surrounding whatever are marked as owned by nobody (-1).
	auto markOwned = [=, &owner] (pair<int, int> pii, int n) {
		int r = pii.first, c = pii.second;
		/*for (int dr = -2; dr <= 2; dr++) {
			for (int dc = -2; dc <= 2; dc++) {
				int nr = r + dr, nc = c + dc;
				if (inBounds(nr, nc) && !board[nr][nc]) {
					owner[nr][nc] = -1;
				}
			}
		}*/
		owner[r][c] = n + 1;
		/*for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				int nr = r + dr, nc = c + dc;
				if (inBounds(nr, nc) && owner[nr][nc] < 1) {
					owner[nr][nc] = n + 1;
				}
			}
		}*/
	};

	// Contains the next points to consider.
	queue<pair<int, int> > next[5];
	// Contains the actual positions decided upon.
	vector<pair<int, int> > tiles[5];
	// Contains the passages. Passages will grow toward doors or other
	// passages, and away from walls.
	vector<pair<int, int> > passages;

	// Select five random seeds.
	/*for (int i = 0; i < 5; i++) {
		// Choose the r and c. We need to make sure we don't start off with an
		// owned cell.
		int r, c;
		do {
			r = Game::getInstance()->rand(MAX_ROWS);
			c = Game::getInstance()->rand(MAX_COLS);
		} while (owner[r][c]);
		pair<int, int> pii = make_pair(r, c);
		markOwned(pii, i);
		cout << "Seed " << i << " : " << pii.first << " " << pii.second << endl;
		next[i].push(pii);
	}*/
	pair<int, int> seeds[] = {{4, 20}, {5, 65}, {16, 10}, {17, 55}, {11, 38}};
	// 30% chance to swap x-positions of 0 and 2, 1 and 4.
	for (int i = 0; i < 2; i++) {
		if (Game::getInstance()->rand(100) < 30) {
			int t = seeds[i + 2].first;
			seeds[i + 2].first = seeds[i].first;
			seeds[i].first = t;
		}
	}
	for (int i = 0; i < 5; i++) {
		pair<int, int> seed = seeds[i];
		seed.first += Game::getInstance()->rand(-3, 3);
		seed.second += Game::getInstance()->rand(-8, 8);
		next[i].push(seed);
	}
	/*next[0].push(make_pair(3, 20));
	next[1].push(make_pair(3, 65));
	next[2].push(make_pair(18, 10));
	next[3].push(make_pair(18, 55));
	next[4].push(make_pair(11, 38));*/

	int dr[] = {-1, +1, +0, +0};
	int dc[] = {+0, +0, -1, +1};
	// Now, grow everything! done holds the number of completed chambers.
	for (bool allEmpty = false; !allEmpty;) {
		allEmpty = true;

		// curChamber is the chamber we're currently considering
		for (int curChamber = 0; curChamber < 5; curChamber++) {
			// Check emptiness first.
			if (next[curChamber].empty()) {
				continue;
			} else {
				allEmpty = false;
			}

			// The current tile to consider.
			pair<int, int> curPos = next[curChamber].front();
			next[curChamber].pop();
			int chance = getGenerationChance(tiles[curChamber].size());
			int curOwner = owner[curPos.first][curPos.second];

			// First, see if we are even allowed to use this one. (It's possible
			// that a neighbouring tile was sniped recently, or that we're
			// checking the same thing twice!
			if ((curOwner && curOwner != curChamber + 1) || board[curPos.first][curPos.second]) {
				if(0&&curChamber==1)cout<<"can't use, owned by "<<curOwner<<endl;
				continue;
			}
			//cout << "cursize: " << tiles[curChamber].size() << "; chance: " << chance << endl;
			// Then check if we decide to use this or not.
			if (Game::getInstance()->rand(100) >= chance) {
			if (0&&curChamber==1)cout<<"Reject!"<<endl;
				continue;
			}

			if (0&&curChamber==1)
			cout << "Take " << curPos.first << " " << curPos.second << " for " << curChamber << endl;

			// We've decided to use it, so add it to the list of actual tiles
			// and mark this (and its neighbours) as owned.
			tiles[curChamber].push_back(curPos);
			board[curPos.first][curPos.second] = '.'; // '0' + curChamber;
			markOwned(curPos, curChamber);

			bool used[4] = {};

			for (int j = 0; j < 4; j++) {
				// For each direction, we randomly decide whether or not we will
				// even consider that Tile.
				/*if (Game::getInstance()->rand(100) >= chance) {
					continue;
				}*/
				int i;
				do {
					i = Game::getInstance()->rand(4);
					// Make horizontal growth marginally more likely
					if (i < 2 && !Game::getInstance()->rand(2)) {
						i += 2;
					}
				} while (used[i]);
				used[i] = true;

				pair<int, int> nextPos(curPos);
				nextPos.first += dr[i];
				nextPos.second += dc[i];
				if (!inBounds(nextPos.first, nextPos.second)) {
					continue;
				}
				int nextOwner = owner[nextPos.first][nextPos.second];
				if (0&&curChamber == 1)
				cerr << "Consider " << nextPos.first << " " << nextPos.second << " for " << curChamber << " (owned by " << nextOwner << ")\n";

				// If this tile isn't owned by somebody else, then we add it to
				// our list for future consideration.
				if (!nextOwner || nextOwner == curChamber + 1) {
					next[curChamber].push(nextPos);
				}
			}
		} // for curChamber
	} // for allEmpty

	// Syntactic sugar for iteration over the board.
	auto iterate = [=, &board] (function<bool(int, int)> cond, function<void(int, int, int, int)> expr) {
		for (int r = 0; r < MAX_ROWS; r++) {
			for (int c = 0; c < MAX_COLS; c++) {
				if (cond(r, c)) {
					for (int dr = -1; dr <= 1; dr++) {
						for (int dc = -1; dc <= 1; dc++) {
							int nr = r + dr, nc = c + dc;
							if (inBounds(nr, nc)) {
								expr(r, c, nr, nc);
							}
						}
					}
				}
			}
		}
	};

	// Postprocess step 1: remove floor tiles next to floor tiles of a different
	// chamber by replacing with empty space.
	iterate([=] (int r, int c) { return board[r][c] == '.'; },
		[=, &board] (int r, int c, int nr, int nc) {

		if (board[nr][nc] == '.' && owner[r][c] != owner[nr][nc]) {
			if (Game::getInstance()->rand(2)) {
				board[r][c] = 0;
			} else {
				board[nr][nc] = 0;
			}
		}
	});

	// Step 2: transform floor tiles bordering empty space into walls
	iterate([=, &board] (int r, int c) {
		if (r == 0 || c == 0 || r == MAX_ROWS - 1 || c == MAX_COLS - 1) {
			board[r][c] = '|';
			return false;
		}
		return board[r][c] == '.';
	}, [=, &board] (int r, int c, int nr, int nc) {
		if (board[nr][nc] == 0) {
			board[r][c] = '|';
		}
	});
	// Step 3: transform walls not bordering floor tiles into empty space (i.e.
	// pruning), and mark walls as either vertical or horizontal.
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLS; c++) {
			if (board[r][c] == '|') {
				bool shouldRemove = true;
				for (int dr = -1; dr <= 1; dr++) {
					for (int dc = -1; dc <= 1; dc++) {
						int nr = r + dr, nc = c + dc;
						if (!inBounds(nr, nc)) {
							continue;
						}
						if (board[nr][nc] == '.') {
							shouldRemove = false;
						} else if (board[nr][nc] == '|' && dr && !dc) {
							vert[r][c] = true;
						}
					}
				}
				if (shouldRemove) {
					board[r][c] = 0;
				}
			}
			if (board[r][c] == 0) {
				cout << ' ';
			} else if (board[r][c] == '|') {
				cout << (vert[r][c] ? '|' : '-');
			} else {
				cout << board[r][c];
			}
		}
		cout << endl;
	}
//*/
}

/**
 *	Populates the Floor. Sets PC position as well.
 */
void Floor::fill() {
	// Player Character location.
	Tile *tile = this->getRandomUnoccupiedTile();
	Game::getInstance()->getPlayer()->moveTo(tile);
	// Stairway location.
	this->generateExit();
	// Potions
	for (int i = 0; i < Game::getInstance()->getMaxPotions(); i++) {
		this->generatePotion();
	}
	// Gold
	for (int i = 0; i < Game::getInstance()->getMaxGoldPiles(); i++) {
		this->generateGoldPile();
	}
	// Enemies
	for (int i = 0; i < Game::getInstance()->getMaxEnemies(); i++) {
		this->generateEnemy();
	}
}

/*
 *	Sets initial position of player on floor to be (r,c)
 */
void Floor::setPlayerPos(int r, int c) {
	this->playerR = r;
	this->playerC = c;
}
// gets player pos on floor
int Floor::getPlayerR() const {
	return this->playerR;
}
int Floor::getPlayerC() const {
	return this->playerC;
}

/**
 *	Renders all chambers on the floor
 */
void Floor::render() {
	for (int l0 = 0; l0 < (int)this->chambers.size(); l0++) {
		if (this->chambers[l0]) {
			//std::cerr << "Floor: render chamber " << l0 << std::endl;
			this->chambers[l0]->render();
		}
	}
	//std::cerr << "Floor: render passages " << std::endl;
	this->passages->render();
}

/**
 *	Gets a random unoccupied tile from a random chamber. The selected tile has
 *	an equal chance of being selected from each chamber.
 *
 *	Technically it's not guaranteed to terminate (it's possible all Tiles in
 *	all Chambers are occupied), but in practice, this is not going to happen.
 */
Tile *Floor::getRandomUnoccupiedTile() const {
	Tile *tile;
	do {
		tile = this->getRandomChamber()->getUnoccupiedTile();
	} while (tile == NULL);
	return tile;
}
