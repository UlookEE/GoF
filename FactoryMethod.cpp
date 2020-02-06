class Maze {
public:
	Maze();
	void AddRoom(Room*);
	Room* RoomNo(int) const;
private:

};

enum Direction { North, South, East, West };

class MapSite {
public:
	virtual void Enter() = 0;
};

class Room : public MapSite {
public:
	Room() = default;
	Room(int RoomNo);
	MapSite* GetSide(Direction) const;
	void SetSide(Direction, MapSite*);

	virtual void Enter();

private:
	MapSite* _sides[4];
	int _roomNumber;
};

class Wall : public MapSite {
public:
	Wall();
	virtual void Enter();
};

class Door : public MapSite {
public:
	Door(Room* = 0, Room* = 0);

	virtual void Enter();
	Room* OhterSideFrom(Room *);

private:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
};

/* TEMPLATE OF MAZE */

/* All function to virtual */
class MazeGame {
public:
	Maze* CreateMaze();
	virtual Maze* MakeMaze() const {
		return new Maze;
	}
	virtual Room* MakeRoom(int n) const {
		return new Room(n);
	}
	virtual Wall* MakeWall() const {
		return new Wall();
	}
	virtual Door* MakeDoor(Room* r1, Room* r2)const {
		return new Door(r1, r2);
	}
	
};

Maze* MazeGame::CreateMaze() {
	Maze* aMaze = MakeMaze();
	Room* r1 = MakeRoom(1);
	Room* r2 = MakeRoom(2);
	Door* aDoor = MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North, MakeWall());
	r1->SetSide(East, MakeWall());
	r1->SetSide(South, MakeWall());
	r1->SetSide(West, MakeWall());

	r2->SetSide(North, MakeWall());
	r2->SetSide(East, MakeWall());
	r2->SetSide(South, MakeWall());
	r2->SetSide(West, MakeWall());

	return aMaze;
}

class BombedWall : public Wall{};
class RoomWithBomb : public Room {};

/* Override which i want*/
class BombedMazeGame : public MazeGame {
public:
	BombedMazeGame();

	virtual Wall* MakeWall() const {
		return new BombedWall;
	}
	virtual Room* MakeRoom() const {
		return new RoomWithBomb;
	}
};
