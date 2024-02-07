#pragma once

enum DOORS 
{
	MAIN_ROOM,
	ROOM_2

};


class Door
{

private:
	int id;
public:

	Door(FloatRect bounds, int id);

	const int getDoorId()const ;
};

