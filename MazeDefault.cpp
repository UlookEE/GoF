enum Direction { North, South, East, West };

class MapSite {
public:
	virtual void Enter() = 0;
};

class Room : public MapSite {
public:
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

class Maze {
public:
	Maze();
	void AddRoom(Room*);
	Room* RoomNo(int) const;
private:

};

class MazeGame {
private:
	Maze* CreateMaze();
};

Maze* MazeGame::CreateMaze(){
	Maze *aMaze = new Maze;
	Room *r1 = new Room(1);
	Room *r2 = new Room(2);
	Door *theDoor = new Door(r1, r2);
	
	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	//r1->SetSide(North, new Wall);
	//r1->SetSide(East, theDoor);
	//r1->SetSide(South, new Wall);
	//r1->SetSide(West, new Wall);

	//r2->SetSide(North, new Wall);
	//r2->SetSide(East, new Wall);
	//r2->SetSide(South, new Wall);
	//r2->SetSide(West, theDoor);
	//-> These codes remove to use constructor in Room class;

	r1->SetSide(East, theDoor);
	r2->SetSide(West, theDoor);
	return aMaze;
};

//If add new spell or special room??
//Problem
//1. Using constructor -> Hard coding
//-> use virtual function to make instance... Factory Method pattern
//2. Pass create function to CreateMaze method parameter... Abstract Factory pattern
//3. Inherit class of Builder(it makes object..) 
//4. Copy with pre-created instances... Prototype Pattern
