class Maze {
public:
	Maze();
	void AddRoom(Room*);
	Room* RoomNo(int) const;
private:

};

enum Direction { North, South, East, West };


class MazePrototypeFactory;
class MazeGame {
public:
	Maze* CreateMaze(MazePrototypeFactory&);
};

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
	Wall() = default;
	Wall(const Wall&) = default;
	Wall* Clone();
	virtual void Enter();
};

Wall* Wall::Clone() {
	return new Wall(*this);
}

class Door : public MapSite {
public:
	Door() = default;
	Door(const Door&);

	virtual void Initialize(Room*, Room*);
	virtual Door* Clone() const;
	virtual void Enter();
	Room* OhterSideFrom(Room *);

private:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
};

Door::Door(const Door& ohter) {
	_room1 = ohter._room1;
	_room2 = ohter._room2;
}

void Door::Initialize(Room *r1, Room* r2) {
	_room1 = r1;
	_room2 = r2;
}

Door* Door::Clone() const {
	return new Door(*this);
}

Maze* MazeGame::CreateMaze(MazePrototypeFactory& mpf) {
	Maze * m;
	/* Make objects with prototype*/
	return m;
}

class BombedWall : public Wall {
public:
	BombedWall();
	BombedWall(const BombedWall&);

	virtual Wall* Clone() const;
	bool HasBomb();

private:
	bool _bomb;
};

BombedWall::BombedWall(const BombedWall& other) : Wall(other) {
	_bomb = other._bomb;
}

Wall* BombedWall::Clone() const {
	return new BombedWall(*this);
}

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

/* TEMPLATE OF MAZE */

class MazeFactory {

};
class MazePrototypeFactory : public MazeFactory {
public:
	MazePrototypeFactory(Maze*, Wall*, Room*, Door*);
	virtual Maze* MakeMaze() const;
	virtual Room* MakeRoom() const;
	virtual Wall* MakeWall() const;
	virtual Door* MakeDoor(Room*, Room*) const;
	
private:
	Maze* _prototypeMaze;
	Room* _prototypeRoom;
	Wall* _prototypeWall;
	Door* _prototypeDoor;
};

MazePrototypeFactory::MazePrototypeFactory(Maze* m, Wall* w, Room* r, Door* d) {
	_prototypeMaze = m;
	_prototypeRoom = r;
	_prototypeWall = w;
	_prototypeDoor = d;
}

Wall* MazePrototypeFactory::MakeWall() const {
	return _prototypeWall->Clone();
}

Door* MazePrototypeFactory::MakeDoor(Room* r1, Room* r2) const {
	Door* door = _prototypeDoor->Clone();
	door->Initialize(r1, r2);
	return door;
}

MazeGame game;
MazePrototypeFactory simpleMazeFactory(new Maze, new Wall, new Room, new Door);
Maze* maze = game.CreateMaze(simpleMazeFactory);

MazePrototypeFactory bombedMazeFactoy(new Maze, new BombedWall, new RoomWithBomb, new Door)
