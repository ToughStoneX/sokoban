#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "sokoban.h"

using namespace std;

Point point[] = {
	{ 8,8 },{ 9,9 },{ 7,10 },{ 8,6 },{ 8,8 },{ 11,13 },{ 8,10 },{ 7,10 },{ 9,11 },{ 8,7 },{ 6,12 },{ 7,8 },{ 13,10 },{ 7,8 },{ 7,8 },{ 9,10 },{ 7,9 },{ 9,10 },
	{ 8,10 },{ 8,7 },{ 8,11 },{ 9,9 },{ 8,10 },{ 9,14 },{ 10,11 },{ 12,13 },{ 12,15 },{ 13,16 },{ 7,9 },{ 7,12 },{ 8,9 },{ 8,8 },{ 12,14 },{ 13,15 },{ 10,10 },
	{ 12,15 },{ 8,9 },{ 12,12 },{ 10,11 },{ 7,7 }
};

//0:空地,1:墻,3:目的地,4:箱子,5:人
int Maps[][16][16] =
{
	{
		{ 0,0,1,1,1,0,0,0 },{ 0,0,1,3,1,0,0,0 },{ 0,0,1,0,1,1,1,1 },{ 1,1,1,4,0,4,3,1 },
		{ 1,3,0,4,5,1,1,1 },{ 1,1,1,1,4,1,0,0 },{ 0,0,0,1,3,1,0,0 },{ 0,0,0,1,1,1,0,0 }
	},
	{
		{ 1,1,1,1,1,0,0,0,0 },{ 1,0,0,0,1,0,0,0,0 },{ 1,0,4,4,1,0,1,1,1 },{ 1,5,4,0,1,0,1,3,1 },
		{ 1,1,1,0,1,1,1,3,1 },{ 0,1,1,0,0,0,0,3,1 },{ 0,1,0,0,0,1,0,0,1 },{ 0,1,0,0,0,1,1,1,1 },{ 0,1,1,1,1,1,0,0,0 }
	},
	{
		{ 0,1,1,1,1,1,1,1,0,0 },{ 0,1,0,0,0,0,0,1,1,1 },{ 1,1,4,1,1,1,0,0,0,1 },{ 1,5,0,0,4,0,0,4,0,1 },
		{ 1,0,3,3,1,0,4,0,1,1 },{ 1,1,3,3,1,0,0,0,1,0 },{ 0,1,1,1,1,1,1,1,1,0 }
	},
	{
		{ 0,1,1,1,1,0 },{ 1,1,0,0,1,0 },{ 1,5,0,4,1,0 },{ 1,1,0,0,1,1 },{ 1,1,4,4,0,1 },{ 1,3,4,0,0,1 },
		{ 1,3,3,7,3,1 },{ 1,1,1,1,1,1 }
	},
	{
		{ 0,1,1,1,1,1,0,0 },{ 0,1,0,5,1,1,1,0 },{ 0,1,0,4,0,0,1,0 },{ 1,1,1,0,1,0,1,1 },{ 1,3,1,0,1,0,0,1 },
		{ 1,3,4,0,0,1,0,1 },{ 1,3,0,0,0,4,0,1 },{ 1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,0,1,1,1,1,1,1,1,0,0,0 },{ 1,1,1,1,0,0,0,0,0,1,0,0,0 },{ 1,0,0,0,3,1,1,1,0,1,0,0,0 },
		{ 1,0,1,0,1,0,0,0,0,1,1,0,0 },{ 1,0,1,0,4,0,4,1,3,0,1,0,0 },{ 1,0,1,0,0,7,0,0,1,0,1,0,0 },{ 1,0,3,1,4,0,4,0,1,0,1,0,0 },
		{ 1,1,0,0,0,0,1,0,1,0,1,1,1 },{ 0,1,0,1,1,1,3,0,0,0,0,5,1 },{ 0,1,0,0,0,0,0,1,1,0,0,0,1 },{ 0,1,1,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,0,1,1,1,1,1,1,1 },{ 0,0,1,1,0,0,1,0,5,1 },{ 0,0,1,0,0,0,1,4,0,1 },{ 0,0,1,4,0,0,4,0,0,1 },
		{ 0,0,1,0,4,1,1,0,0,1 },{ 1,1,1,0,4,0,1,0,1,1 },{ 1,3,3,3,3,3,0,0,1,0 },{ 1,1,1,1,1,1,1,1,1,0 }
	},
	{
		{ 0,0,0,1,1,1,1,1,1,0 },{ 0,1,1,1,0,0,0,0,1,0 },{ 1,1,3,0,4,1,1,0,1,1 },{ 1,3,3,4,0,4,0,0,5,1 },
		{ 1,3,3,0,4,0,4,0,1,1 },{ 1,1,1,1,1,1,0,0,1,0 },{ 0,0,0,0,0,1,1,1,1,0 }
	},
	{
		{ 0,1,1,1,1,1,1,1,1,1,0 },{ 0,1,0,0,1,1,0,0,0,1,0 },{ 0,1,0,0,0,4,0,0,0,1,0 },{ 0,1,4,0,1,1,1,0,4,1,0 },
		{ 0,1,0,1,3,3,3,1,0,1,0 },{ 1,1,0,1,3,3,3,1,0,1,1 },{ 1,0,4,0,0,4,0,0,4,0,1 },{ 1,0,0,0,0,0,1,0,0,5,1 },{ 1,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1 },{ 1,3,3,4,3,3,1 },{ 1,3,3,1,3,3,1 },{ 1,0,4,4,4,0,1 },{ 1,0,0,4,0,0,1 },{ 1,0,4,4,4,0,1 },
		{ 1,0,0,1,0,5,1 },{ 1,1,1,1,1,1,1 }
	},
	{
		{ 0,1,1,1,1,0,0,1,1,1,1,1 },{ 1,1,0,0,1,0,0,1,0,0,0,1 },{ 1,0,4,0,1,1,1,1,4,0,0,1 },{ 1,0,0,4,3,3,3,3,0,4,0,1 },
		{ 1,1,0,0,0,0,1,0,5,0,1,1 },{ 0,1,1,1,1,1,1,1,1,1,1,0 }
	},
	{
		{ 0,0,1,1,1,1,1,0 },{ 1,1,1,0,0,5,1,0 },{ 1,0,0,4,3,0,1,1 },{ 1,0,0,3,4,3,0,1 },{ 1,1,1,0,7,4,0,1 },{ 0,0,1,0,0,0,1,1 },
		{ 0,0,1,1,1,1,1,0 }
	},
	{
		{ 0,0,1,1,1,1,1,1,1,0 },{ 0,1,1,0,0,0,0,0,1,1 },{ 0,1,0,4,0,0,4,3,0,1 },{ 1,1,0,0,1,1,3,4,0,1 },{ 1,0,0,4,5,1,4,3,0,1 },
		{ 1,0,0,0,1,1,3,4,1,1 },{ 1,1,1,4,1,0,4,3,0,1 },{ 0,1,0,0,3,0,1,1,0,1 },{ 0,1,0,0,0,0,1,0,0,1 },{ 0,1,1,3,0,1,1,0,1,1 },{ 0,0,1,1,3,1,0,0,1,0 },
		{ 0,0,0,1,0,0,0,1,1,0 },{ 0,0,0,1,1,1,1,1,0,0 }
	},
	{
		{ 1,1,1,1,1,1,1,1 },{ 1,0,0,1,0,0,0,1 },{ 1,0,4,3,3,4,0,1 },{ 1,5,4,3,7,0,1,1 },{ 1,0,4,3,3,4,0,1 },
		{ 1,0,0,1,0,0,0,1 },{ 1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,1,1,1,1,1,1,0 },{ 1,1,0,0,0,0,1,1 },{ 1,0,4,0,4,4,0,1 },{ 1,3,3,3,3,3,3,1 },{ 1,0,4,4,0,4,0,1 },
		{ 1,1,1,0,5,1,1,1 },{ 0,0,1,1,1,1,0,0 }
	},
	{
		{ 0,0,1,1,1,1,1,1,1,1 },{ 0,0,1,0,0,0,0,1,1,1 },{ 0,0,1,0,4,0,0,0,0,1 },{ 1,1,1,0,4,0,1,1,0,1 },{ 1,3,3,3,0,4,0,0,0,1 },
		{ 1,3,3,3,4,1,4,0,1,1 },{ 1,1,1,1,0,1,0,4,0,1 },{ 0,0,0,1,0,0,0,5,0,1 },{ 0,0,0,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,0,0,0 },{ 1,0,0,0,0,1,0,0,0 },{ 1,0,4,4,4,1,1,0,0 },{ 1,0,0,1,3,3,1,1,1 },{ 1,1,0,0,3,3,4,0,1 },
		{ 0,1,0,0,5,0,0,0,1 },{ 0,1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,1,1,1,1,1,1,1,1 },{ 0,0,1,0,0,0,1,3,0,1 },{ 0,1,1,0,0,4,3,3,3,1 },{ 0,1,0,0,4,0,1,7,3,1 },
		{ 1,1,0,1,1,4,1,0,1,1 },{ 1,0,0,0,4,0,0,4,0,1 },{ 1,0,0,0,1,0,0,0,0,1 },{ 1,1,1,1,1,1,1,5,0,1 },{ 0,0,0,0,0,0,1,1,1,1 }
	},
	{
		{ 0,1,1,1,1,1,1,1,0,0 },{ 0,1,3,3,3,3,0,1,0,0 },{ 1,1,1,3,3,3,4,1,1,1 },{ 1,0,0,4,1,4,0,4,0,1 },
		{ 1,0,4,4,0,0,1,4,0,1 },{ 1,0,0,0,0,1,0,0,0,1 },{ 1,1,1,1,0,5,0,1,1,1 },{ 0,0,0,1,1,1,1,1,0,0 }
	},
	{
		{ 1,1,1,1,1,1,1 },{ 1,3,3,4,3,3,1 },{ 1,3,3,1,3,3,1 },{ 1,0,4,4,4,0,1 },{ 1,0,0,4,0,0,1 },{ 1,0,4,4,4,0,1 },
		{ 1,0,0,1,5,0,1 },{ 1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,0,1,1,1,1,1,1,0,0 },{ 0,0,0,1,0,3,3,3,1,0,0 },{ 1,1,1,1,3,3,3,3,1,0,0 },{ 1,0,0,1,1,1,4,0,1,1,1 },
		{ 1,0,4,0,4,0,0,4,4,0,1 },{ 1,5,0,4,0,4,0,0,0,0,1 },{ 1,0,0,0,1,1,1,0,0,0,1 },{ 1,1,1,1,1,0,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,0 },{ 1,0,0,0,0,0,0,1,0 },{ 1,0,1,4,4,0,0,1,0 },{ 1,0,3,3,3,1,0,1,0 },{ 1,1,3,3,3,4,0,1,1 },
		{ 0,1,0,1,1,0,4,0,1 },{ 0,1,4,0,0,4,0,0,1 },{ 0,1,0,0,1,0,0,5,1 },{ 0,1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,1,1,1,1,1,0,0,0 },{ 1,1,1,0,0,0,1,1,1,1 },{ 1,0,0,0,4,0,0,4,0,1 },{ 1,0,4,0,5,4,0,0,0,1 },{ 1,1,1,4,4,1,1,1,1,1 },
		{ 0,0,1,0,0,3,3,1,0,0 },{ 0,0,1,3,3,3,3,1,0,0 },{ 0,0,1,1,1,1,1,1,0,0 }
	},
	{
		{ 1,1,1,1,1,1,0,0,0,1,1,1,1,1 },{ 1,0,0,0,0,1,1,1,0,1,0,0,0,1 },{ 1,0,0,4,0,4,0,1,0,1,3,3,3,1 },
		{ 1,0,1,0,0,4,0,1,1,1,0,0,3,1 },{ 1,0,0,4,4,4,0,0,0,4,0,5,3,1 },{ 1,1,1,0,0,4,0,0,4,1,0,0,3,1 },{ 0,0,1,0,0,4,1,4,0,1,3,3,3,1 },
		{ 0,0,1,1,0,0,0,0,0,1,0,0,3,1 },{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,0,0,0,1,1,1,1,1,1 },{ 0,1,1,1,1,1,3,0,0,0,1 },{ 0,1,0,0,1,3,3,1,1,0,1 },{ 0,1,0,0,4,3,3,0,0,0,1 },
		{ 0,1,0,0,1,0,3,1,0,1,1 },{ 1,1,1,0,1,1,4,1,0,0,1 },{ 1,0,4,0,0,0,0,4,4,0,1 },{ 1,0,1,4,1,0,0,1,0,0,1 },{ 1,5,0,0,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,0,0,0,0,0,0 }
	},
	{
		{ 0,1,1,1,1,1,1,1,1,1,0,0,0 },{ 0,1,0,0,0,1,1,0,0,1,1,1,1 },{ 0,1,0,4,0,0,0,0,0,0,0,0,1 },{ 0,1,1,4,1,1,1,0,1,1,0,0,1 },
		{ 0,1,0,0,1,1,0,7,0,1,0,1,1 },{ 0,1,0,4,3,3,3,3,3,3,0,1,0 },{ 1,1,0,1,1,1,0,3,0,1,0,1,0 },{ 1,0,0,0,0,0,4,1,1,1,4,1,0 },
		{ 1,0,0,0,1,0,0,0,0,4,5,1,0 },{ 1,1,1,1,1,4,1,0,1,1,1,1,0 },{ 0,0,0,0,1,0,0,0,1,0,0,0,0 },{ 0,0,0,0,1,1,1,1,1,0,0,0,0 }
	},
	{
		{ 0,0,0,0,0,0,1,1,1,1,1,1,1,1,1 },{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },{ 0,0,0,0,0,0,1,0,1,0,1,0,1,0,1 },
		{ 0,0,0,0,0,0,1,0,0,4,0,4,1,0,1 },{ 1,1,1,1,1,1,1,0,0,0,4,0,0,0,1 },{ 1,3,3,1,0,0,1,1,0,4,0,4,1,0,1 },{ 1,3,3,0,0,0,1,1,0,4,0,4,0,0,1 },
		{ 1,3,3,1,0,0,1,1,0,1,1,1,1,1,1 },{ 1,3,3,1,0,1,0,4,0,4,0,1,0,0,0 },{ 1,3,3,0,0,0,0,0,4,0,0,1,0,0,0 },{ 1,0,0,1,1,1,5,0,0,1,1,1,0,0,0 },
		{ 1,1,1,1,0,1,1,1,1,1,0,0,0,0,0 }
	},
	{
		{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 },{ 1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0 },{ 1,0,0,4,0,4,0,1,0,1,1,1,1,1,1,1 },
		{ 1,0,0,0,4,0,0,1,0,1,7,3,7,3,7,1 },{ 1,1,0,4,0,4,0,1,1,1,3,7,3,7,3,1 },{ 0,1,4,0,4,0,0,1,0,0,7,3,7,3,7,1 },{ 0,1,5,4,0,4,0,0,0,0,3,7,3,7,1,1 },
		{ 0,1,4,0,4,0,0,1,0,0,7,3,7,3,7,1 },{ 1,1,0,4,0,4,0,1,1,1,3,7,3,7,3,1 },{ 1,0,0,0,4,0,0,1,0,1,7,3,7,3,7,1 },
		{ 1,0,0,4,0,4,0,1,0,1,1,1,1,1,1,1 },{ 1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0 },{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 }
	},
	{
		{ 1,1,1,1,1,1,1,1,0 },{ 1,3,3,3,3,3,3,1,0 },{ 1,0,0,4,0,1,0,1,1 },{ 1,0,4,0,1,0,4,0,1 },{ 1,1,4,0,4,0,4,0,1 },
		{ 0,1,0,0,5,0,0,0,1 },{ 0,1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,1,1,1,1,1,1,1,1,1,1 },{ 1,1,1,0,0,0,3,4,5,0,0,1 },{ 1,0,0,0,1,1,4,1,1,0,0,1 },{ 1,0,0,0,7,0,3,0,3,0,1,1 },
		{ 1,1,0,4,1,1,4,1,1,0,1,0 },{ 0,1,0,0,0,0,3,0,0,0,1,0 },{ 0,1,1,1,1,1,1,1,1,1,1,0 }
	},
	{
		{ 0,0,0,1,1,1,1,1,1 },{ 1,1,1,1,3,0,0,5,1 },{ 1,0,0,4,4,4,0,0,1 },{ 1,3,1,1,3,1,1,3,1 },{ 1,0,0,0,4,0,0,0,1 },
		{ 1,0,0,4,3,1,0,1,1 },{ 1,1,1,1,0,0,0,1,0 },{ 0,0,0,1,1,1,1,1,0 }
	},
	{
		{ 0,1,1,1,1,1,1,0 },{ 0,1,3,0,3,3,1,0 },{ 0,1,3,0,4,3,1,0 },{ 1,1,1,0,0,4,1,1 },{ 1,0,4,0,0,4,0,1 },
		{ 1,0,1,4,1,1,0,1 },{ 1,0,0,0,5,0,0,1 },{ 1,1,1,1,1,1,1,1 }
	},
	{
		{ 0,0,0,0,1,1,1,1,1,1,0,0,0,0 },{ 0,0,1,1,1,0,0,0,0,1,1,1,0,0 },{ 0,0,1,0,0,0,1,4,0,0,0,1,1,1 },{ 0,0,1,0,0,0,4,0,0,0,4,4,0,1 },
		{ 0,0,1,0,4,4,0,1,4,0,0,0,0,1 },{ 0,0,1,1,0,0,0,4,0,0,0,4,0,1 },{ 1,1,1,1,1,1,0,1,4,1,1,1,1,1 },{ 1,3,3,5,0,1,4,0,0,1,0,0,0,0 },
		{ 1,3,1,3,3,0,0,4,1,1,0,0,0,0 },{ 1,3,3,3,3,4,1,0,1,0,0,0,0,0 },{ 1,3,3,3,3,0,0,0,1,0,0,0,0,0 },{ 1,1,1,1,1,1,1,1,1,0,0,0,0,0 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },{ 1,0,0,0,0,0,0,1,0,0,0,0,0,0,1 },{ 1,0,4,0,1,4,0,1,0,4,1,1,4,0,1 },
		{ 1,0,1,0,0,4,0,1,0,0,0,0,0,0,1 },{ 1,0,0,0,1,1,4,1,4,1,1,4,4,0,1 },{ 1,0,1,0,1,0,3,3,3,0,1,0,0,0,1 },{ 1,0,4,0,0,3,0,1,0,3,4,0,0,0,1 },
		{ 1,0,4,1,5,4,3,3,3,1,0,1,0,0,1 },{ 1,0,0,0,0,3,0,1,0,3,0,0,4,0,1 },{ 1,0,1,1,3,4,1,1,1,4,3,0,1,0,1 },{ 1,0,1,0,4,3,3,3,3,3,0,1,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,0 },{ 1,0,0,0,1,1,0,0,1,0 },{ 1,0,1,0,4,0,4,0,1,0 },{ 1,0,0,7,3,1,0,0,1,0 },{ 1,1,0,1,3,5,3,1,1,0 },
		{ 1,1,4,1,1,1,7,1,1,1 },{ 1,0,0,0,0,0,0,0,0,1 },{ 1,0,0,0,1,1,0,1,0,1 },{ 1,1,1,1,1,1,0,0,0,1 },{ 0,0,0,0,0,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0 },{ 1,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },{ 1,0,4,4,0,0,0,1,1,1,0,0,0,0,0 },
		{ 1,0,0,4,0,4,4,4,0,1,1,1,1,1,0 },{ 1,1,0,1,1,0,3,3,3,0,0,0,0,1,1 },{ 0,1,0,1,5,1,3,3,3,1,1,1,4,0,1 },
		{ 0,1,0,1,0,4,3,3,3,0,0,0,0,0,1 },{ 1,1,0,1,0,4,3,3,3,4,0,1,0,1,1 },{ 1,0,0,1,1,1,1,1,0,1,1,1,0,1,0 },
		{ 1,0,0,0,0,0,0,4,0,0,0,4,0,1,0 },{ 1,1,1,1,1,1,1,1,1,1,1,0,0,1,0 },{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0 }
	},
	{
		{ 0,0,0,1,1,1,1,1,0 },{ 0,0,0,1,0,5,0,1,0 },{ 0,0,0,1,4,4,4,1,0 },{ 1,1,1,1,0,0,0,1,0 },{ 1,0,0,0,3,4,4,1,1 },
		{ 1,0,4,3,4,3,0,3,1 },{ 1,0,0,1,3,1,3,1,1 },{ 1,1,1,1,1,1,1,1,0 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1 },{ 1,3,3,3,0,1,0,0,0,0,0,1 },{ 1,3,3,0,0,1,0,1,1,0,0,1 },{ 1,3,3,0,0,0,0,0,1,0,0,1 },
		{ 1,3,3,0,0,1,0,4,1,1,0,1 },{ 1,3,3,3,0,1,4,0,4,0,0,1 },{ 1,1,1,1,1,1,0,0,4,4,0,1 },{ 0,1,1,0,0,4,0,4,4,0,0,1 },{ 0,1,5,0,4,4,4,0,0,1,0,1 },
		{ 0,1,1,0,4,0,1,1,0,0,0,1 },{ 0,0,1,0,0,0,0,0,0,0,0,1 },{ 0,0,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,0,0 },{ 1,0,0,0,0,0,0,0,1,0,0 },{ 1,0,0,4,0,4,0,4,1,0,0 },{ 1,1,0,1,4,1,1,0,1,0,0 },{ 0,1,0,3,3,0,3,3,1,1,0 },
		{ 0,1,1,3,3,0,3,3,0,1,0 },{ 0,0,1,0,1,1,4,1,0,1,1 },{ 0,0,1,4,0,4,0,4,0,0,1 },{ 0,0,1,0,0,0,0,0,0,5,1 },{ 0,0,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1 },{ 1,3,0,3,0,3,1 },{ 1,0,4,4,4,0,1 },{ 1,3,4,5,4,3,1 },{ 1,0,4,4,4,0,1 },{ 1,3,0,3,0,3,1 },{ 1,1,1,1,1,1,1 }
	}
};

Sokoban::Sokoban()
{
}


Sokoban::~Sokoban()
{
}

/*定位光标*/
void Sokoban::Gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*隐藏光标*/
void Sokoban::Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 1,0为光标厚度和可见度
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*主菜单*/
void Sokoban::Menu(char* ch)
{
	while (1)
	{
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\t       主        菜        单\n\n";
		cout << "\n\n\t\t       推箱子\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):开始游戏\n\n";
		cout << "\t\t   (2):操作介绍\n\n";
		cout << "\t\t   (3):游戏介绍\n\n";
		cout << "\t\t   (4):退出游戏\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "****************第一次请先观看操作介绍****************\n\n";
		cout << "";
		cout << "\t\t    请输入序号。\n";
		
		int s = _getch();
		while (s < '1' || s > '4')
		{
			cout << "\t\t输入有误，请重新输入。\n";
			s = _getch();
		}
		if (s == '1')
			MenuOne(ch); // 菜单一
		else if (s == '2')
			Operation(ch);
		else if (s == '3')
			Introduction(ch);
		else
		{
			int i = MessageBox(NULL, L"\n确定要退出游戏吗？", L"退出提示", MB_YESNO);
			if (i == IDYES)
				exit(0);
		}
	}
}

/*操作介绍*/
void Sokoban::Operation(char* ch)
{
	char hh = '!';
	while (1)
	{
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "\t\t\t操作说明:\n\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); // 红色
		cout << "   (W):向上移动 (S):向下移动 (A):向左移动 (D):向右移动\n\n";
		cout << "      (□):代表箱子 (♀):代表人   (☆):代表目的地\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); // 绿色
		cout << "\t        *按键盘前请调整好输入法。\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "\t\t     退出请按   键。\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		Gotoxy(29, 16);
		cout << "ESC";
		hh = _getch();
		if (hh == 27)
		{
			// 注：源代码这个地方感觉不太对，会不断套进新的while里面，直接用break退出回到之前的Menu函数中会不会好一点？
			//Menu(ch);
			break;
		}
	}
}

/*游戏介绍*/
void Sokoban::Introduction(char* ch)
{
	int s;
	system("cls");
	Hide(); // 隐藏光标
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << ("\n\n\n\n\n\n\n");
	cout << ("         ------------------------------------\n\n");
	cout << ("\t\t (1):游戏名称:推箱子\n\n");
	cout << ("\t\t (2):游戏简介:->(next)\n\n");
	cout << ("\t\t (3):完成日期:2018年3月\n\n");
	cout << ("\t\t (4):作者:xhb\n\n");
	cout << ("\t\t (5):QQ:2775751197\n\n");
	cout << ("\t\t (6):版本:%d.\n\n", VERSION);
	cout << ("\t\t (7):退出页面\n\n");
	cout << ("         ------------------------------------\n\n");
	cout << ("\t\t    请输入序号。\n");
	s = _getch();
	while (s != '2' && s != '7')
	{
		cout << "\t\tSorry，此序号没有下一页了。\n";
		s = _getch();
	}
	if (s == '2')
		GameSummary(ch); // 游戏简介
	else if (s == '7')
	{
		//Menu(ch);
		; // 什么都不做，直接退出
	}
}

/*游戏介绍*/
void Sokoban::GameSummary(char* ch)
{
	while (1)
	{
		char hh = '!';
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n";
		cout << "   《推箱子》是一款经典电子游戏，1982年由日本Thinking Rabbit公司首次发行";
		cout << "之后其他游戏开发者争相制作仿制或衍生作品。致使推箱子成为此类游戏的代名词。";
		cout << "游戏要求玩家在一个狭小的仓库中，要求把木箱放到指定的位置，稍不小心就会出现";
		cout << "t箱子无法移动或者通道被堵住的情况，所以需要巧妙的利用有限的空间和通道，合理";
		cout << "t安排移动的次序和位置，才能顺利的完成任务。 \n";
		cout << "    推箱子是一个来自日本的古老游戏，目的是在训练玩家的逻辑思考能力。在一个狭";
		cout << "小的仓库中，要求把木箱放到指定的位置，稍不小心就会出现箱子无法移动或者通道被堵";
		cout << "住的情况，所以需要巧妙的利用有限的空间和通道，合理安排移动的次序和位置，才能顺";
		cout << "利地完成任务。\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "        注：游戏关卡来源于经典推箱子关卡。\n\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\t\t  退出请按   键。\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		Gotoxy(26, 15);
		cout << "ESC";
		hh = _getch();
		if (hh == 27)
		{
			//Introduction(ch);
			break;
		}
	}
}

/*菜单一*/
void Sokoban::MenuOne(char* ch)
{
	while (1)
	{
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):闯关模式\n\n";
		cout << "\t\t   (2):选关模式\n\n";
		cout << "\t\t   (3):退出页面\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    请输入序号。\n";
		int s = _getch();
		while (s < '1' || s > '3')
		{
			cout << "\t\t输入有误，请重新输入。\n";
			s = _getch();
		}
		if (s == '1')
			MenuTwo(ch); // 菜单二
		else if (s == '2')
			Select(ch); // 选关模式
		else
		{
			// 注：源代码这个地方感觉不太对，会不断套进新的while里面，直接用break退出回到之前的Menu函数中会不会好一点？
			//Menu(ch);
			break;
		}
	}
}

/*选择关卡*/
void Sokoban::Select(char* ch)
{
	int chapter;
	while (1)
	{
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t    请\n\n\t\t\t   输入\n\n\t\t\t 所要选择\n\n\t\t      的关卡(1-40关)，\n\n\t\t     输入0回退到前一\n\n\t\t    页面。之后按回车键：";
		scanf_s("%d", &chapter);
		while (chapter < 0 || chapter > 40)
		{
			cout << "\t\t输入有误，请重新输入。\n";
			scanf_s("%d", &chapter);
		}
		if (chapter == 0)
			break; // 什么都不做，退回到菜单一
		else
			SelectGameReady(ch, chapter);
	}
}

/*关卡选择完毕，游戏准备*/
int Sokoban::SelectGameReady(char* ch, int chapter)
{
	int ret;
	while (1)
	{
		int s;
		system("cls");
		Hide(); // 隐藏光标
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):游戏开始\n\n";
		cout << "\t\t   (2):游戏退出\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    请输入序号。\n";
		s = _getch();
		while (s != '1' && s != '2')
		{
			cout << "\t\t输入有误，请重新输入。\n";
			s = _getch();
		}
		if (s == '1')
		{
			ret = SelectGame(ch, chapter);
			if (ret == 1)
				break;
		}
		else
			break;
	}
	return 0;
}

/*游戏开始*/
int Sokoban::SelectGame(char* ch, int chapter)
{
	int Map[20][20];
	int m, n;
	memset(Map, -1, sizeof(Map));
	int sum = 0, data = 0, sl = 0;
	bool clear_flag = false;
	while (1)
	{
		SelectMap(Map, &n, &m, ch, chapter);
		data = BoxData(Map, &n, &m);
		sl = GroundData(Map, &n, &m);
		while (1)
		{
			system("cls");
			sum = DrawMap(Map, &n, &m, chapter);
			sum -= sl;
			if (sum == data)
			{
				Hide(); // 隐藏光标
				cout << "\n\t\t    恭 喜 通 关！\n\n";
				cout << "\t       请稍等,正在重置关卡。\n";
				CountDown();
				clear_flag = true;
				break;
			}
			PlayGame(Map, &n, &m, ch);
			if (*ch == '*')
			{
				step = 0; // 如果退出，则自动清空步数计数
				break;
			}
		}
		if (*ch == '*')
		{
			*ch = '!';
			break;
		}
		if (clear_flag == true)
			break;
	}
	if (clear_flag == true)
		return 1;
	else
		return 0;
}

/*选关地图*/
void Sokoban::SelectMap(int Map[][20], int* n, int* m, char* ch, int chapter)
{
	if (chapter > 0)
		chapter--;

	// 地图大小
	*n = point[chapter].x;
	*m = point[chapter].y;
	for (unsigned int i = 0; i < *n; i++)
	{
		for (unsigned int j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[chapter][i][j];
		}
	}
}

/*绘制地图*/
int Sokoban::DrawMap(int Map[20][20], int* n, int* m, int chapter)
{
	int sum = 0;
	Hide();
	cout << "\n\n\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	//cout << "\t\t     第  " << chapter << "  关\n\n\n\n";
	for (int i = 0; i < *n; i++)
	{
		cout << "\t\t   ";
		for (int j = 0; j < *m;j++)
		{
			switch (Map[i][j]) {
			case 1: // 墙
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("■");
				break;
			case 0: // 空地
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("  ");
				break;
			case 3: // 目的地
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("☆");
				break;
			case 4: // 箱子
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("□");
				break;
			case 5: // 人
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				printf("♀");
				break;
			case 7: // 箱子在目的地 4+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("★");
				sum++;
				break;
			case 8: // 人在目的地 5+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("♀");
				break;
			}
		}
		cout << endl;
	}

	if (space == 1)
	{
		cout << "\n\t\t     当前步数为" << step << "步。";
		if (delay == 10)
		{
			space = 0;
			delay = 0;
		}
		delay += 1;
		disp = 1;
	}
	if (disp == 1)
	{
		cout << "\n\t\t  按空格键查看当前步数。";
	}
	disp = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n     按ESC键退出此游戏，之后重新进入从该关重新开始。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n\t   开始游戏前输入法请锁定成英文大写。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	Gotoxy(12, 23);
	cout << "W/↑:上移";
	Gotoxy(32, 23);
	cout << "S/↓:下移";
	Gotoxy(12, 25);
	cout << "A/←:左移";
	Gotoxy(32, 25);
	cout << "D/→:右移";

	return sum;
}

/*计算开始时未在目的地的箱子数*/
int Sokoban::BoxData(int Map[][20], int* n, int* m)
{
	int sum = 0;
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *m;j++)
		{
			if (Map[i][j] == 3)
			{
				sum++;
			}
		}
	}
	return sum;
}

/*计算箱子开始时就在目的地的数目*/
int Sokoban::GroundData(int Map[][20], int* n, int* m)
{
	int sum = 0;
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *m;j++)
		{
			if (Map[i][j] == 7)
			{
				sum++;
			}
		}
	}
	return sum;
}

/*倒计时*/
void Sokoban::CountDown()
{
	int t = 0;
	for (int i = 9; i >= 0; i--)
	{
		Sleep(500);
		Gotoxy(25, 23);
		if (t == 3)
			t = 0;
		if (t == 0)
			cout << i << ".   ";
		else if (t == 1)
			cout << i << "..  ";
		else
			cout << i << "... ";
		t++;
	}
}

/*游戏控制*/
void Sokoban::PlayGame(int Map[20][20], int* n, int* m, char* ch)
{
	char input;
	int i, j;
	// 确定人的位置
	for (i = 0;i < *n;i++)
	{
		for (j = 0;j < *m;j++)
		{
			if (Map[i][j] == 5 || Map[i][j] == 8)
				break;
		}
		if (Map[i][j] == 5 || Map[i][j] == 8)
			break;
	}
	// cout << "i: " << i << ", j: " << j << endl;

	input = _getch();
	switch (input)
	{
	// 上
	case 72:
	case 'W':
	case 'w':
		if (Map[i - 1][j] == 0 || Map[i - 1][j] == 3) // 人的前面是空地或者人的前面是目的地
		{
			Map[i - 1][j] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i - 1][j] == 4 || Map[i - 1][j] == 7) // 人的前面是箱子
		{
			if (Map[i - 2][j] == 0 || Map[i - 2][j] == 3)
			{
				Map[i - 2][j] += 4;
				Map[i - 1][j] += (5 - 4);
				Map[i][j] -= 5;
				step++;
			}
		}
		break;
	
	// 下
	case 80:
	case 'S':
	case 's':
		if (Map[i + 1][j] == 0 || Map[i + 1][j] == 3) // 人前面是空地或者人的前面是目的地
		{
			Map[i + 1][j] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i + 1][j] == 4 || Map[i + 1][j] == 7) // 人的前面是箱子
		{
			if (Map[i + 2][j] == 0 || Map[i + 2][j] == 3)
			{
				Map[i + 2][j] += 4;
				Map[i + 1][j] += (5 - 4);
				Map[i][j] -= 5;
				step++;
			}
		}
		break;

	// 左
	case 75:
	case 'A':
	case 'a':
		if (Map[i][j - 1] == 0 || Map[i][j - 1] == 3) // 人前面是空地或者人的前面是目的地
		{
			Map[i][j - 1] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i][j - 1] == 4 || Map[i][j - 1] == 7) // 人的前面是箱子
		{
			if (Map[i][j - 2] == 0 || Map[i][j - 2] == 3)
			{
				Map[i][j - 2] += 4;
				Map[i][j - 1] += (5 - 4);
				Map[i][j] -= 5;
				step++;
			}
		}
		break;

	// 右
	case 77:
	case 'D':
	case 'd':
		if (Map[i][j + 1] == 0 || Map[i][j + 1] == 3) // 人前面是空地或者人的前面是目的地
		{
			Map[i][j + 1] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i][j + 1] == 4 || Map[i][j + 1] == 7) // 人的前面是箱子
		{
			if (Map[i][j + 2] == 0 || Map[i][j + 2] == 3)
			{
				Map[i][j + 2] += 4;
				Map[i][j + 1] += (5 - 4);
				Map[i][j] -= 5;
				step++;
			}
		}
		break;

	// ESC
	case 27:
		*ch = '*';
		break;

	// space
	case 32:
		space = 1;
		break;
	}
}

/*菜单二*/
void Sokoban::MenuTwo(char* ch)
{
	int s;
	while (1)
	{
		system("cls");
		Hide();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):简单关卡\n\n";
		cout << "\t\t   (2):中等关卡\n\n";
		cout << "\t\t   (3):困难关卡\n\n";
		cout << "\t\t   (4):退出页面\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    请输入序号。\n";
		s = _getch();
		while (s < '1' || s > '4')
		{
			cout << "输入有误，请重新输入:";
			s = _getch();
		}
		if (s == '1')
			EasyGame(ch);
		else if (s == '2')
			MiddleGame(ch);
		else if (s == '3')
			HardGame(ch);
		else
			break;
	}
}

//游戏准备
int Sokoban::LevelGameReady()
{
	system("cls");
	Hide();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//白色
	int s;
	cout << "\n\n\n\n\n\n\n";
	cout << "         ------------------------------------\n\n";
	cout << "\t\t   (1):游戏开始\n\n";
	cout << "\t\t   (2):游戏退出\n\n";
	cout << "         ------------------------------------\n\n";
	cout << "\t\t    请输入序号。\n";
	s = _getch();
	while (s != '1' && s != '2')
	{
		cout << "\t\t输入有误，请重新输入。\n";
		s = _getch();
	}
	return s;
}

/*简单难度关卡控制*/
void Sokoban::EasyGame(char* ch)
{
	int Map[20][20], n, m, js;
	static int chapter = 1;
	memset(Map, -1, sizeof(Map));
	int sum = 0, data = 0, sl = 0;
	while (1)
	{
		int t = LevelGameReady();
		if (t == '2')
			break;
		while (1)
		{
			EasyMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			GameOperate(Map, &n, &m, &js, &sum, &data, &sl, &chapter, ch);
			if (js == 0)
			{
				chapter++;
				if (chapter >= 11)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "恭喜你已经通过全部简单关卡,接下来有中等关卡等待你去挑战\n";
					Gotoxy(19, 26);
					cout << "！！！！！！";
					break;
				}
			}
			else if (js == 1)
				break;
			else if (js == 2)
			{
				*ch = '*';
				continue;
			}
		}
	}
}

void Sokoban::EasyMap(int Map[20][20], int* n, int* m, char* ch)
{
	static int cs = 0;
	int chapter;
	if (*ch == '*')
	{
		chapter = cs;
		if (chapter > 0)
			chapter--;
		*ch = '!';
	}
	else
	{
		chapter = cs;
		cs++;
	}

	*n = point[chapter].x;
	*m = point[chapter].y;
	for (unsigned int i = 0; i < *n; i++)
	{
		for (unsigned int j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[chapter][i][j];
		}
	}
}

void Sokoban::GameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* chapter, char* ch)
{
	while (1)
	{
		clock_t start, end;
		start = clock();
		*js = 0;
		system("cls");//清屏
		Hide();
		*sum = DrawMap(Map, n, m, *chapter);
		*sum -= *sl;
		if (*sum == *data)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t    恭 喜 通 关！\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			int t = MessageBox(NULL, L"\t      你真棒！！！\n\n\t是否进入下一关？", L"提示", MB_YESNO);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\t\t 通关所用步数为" << step << "步。\n";
			end = clock();
			printf("\t\t 通关所用时间为%.3lf秒\n", (double)(end - start) / 9.56);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\t\t 请稍等,正在创建下一关。";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			CountDown();
			if (t == IDYES)
			{
				step = 0;
				break;
			}
			else
			{
				step = 0;
				disp = 1;
				*js = 2;
				break;
			}
		}
		PlayGame(Map, n, m, ch);
		if (*ch == '*')
		{
			int i = MessageBox(NULL, L"\t\n确定要退出游戏吗？\n\n（提示：退出后重新进入从退出的关卡开始）。", L"退出提示", MB_YESNO);
			if (i == IDYES)
			{
				step = 0;
				disp = 1;
				*js = 1;
				break;
			}
			else
			{
				*ch = '!';
				continue;
			}
		}
	}
}

void Sokoban::MiddleGame(char* ch)
{
	int Map[20][20], n, m, js;
	static int chapter = 1;
	memset(Map, -1, sizeof(Map));
	int sum = 0, data = 0, sl = 0;
	while (1)
	{
		int t = LevelGameReady();
		if (t == '2')
			break;
		while (1)
		{
			MiddleMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			GameOperate(Map, &n, &m, &js, &sum, &data, &sl, &chapter, ch);
			if (js == 0)
			{
				chapter++;
				if (chapter >= 21)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "恭喜你已经通过全部简单关卡,接下来有中等关卡等待你去挑战\n";
					Gotoxy(19, 26);
					cout << "！！！！！！";
					break;
				}
			}
			else if (js == 1)
				break;
			else if (js == 2)
			{
				*ch = '*';
				continue;
			}
		}
	}
}

void Sokoban::MiddleMap(int Map[20][20], int* n, int* m, char* ch)
{
	static int cs = 0;
	int chapter;
	if (*ch == '*')
	{
		chapter = cs;
		if (chapter > 0)
			chapter--;
		*ch = '!';
	}
	else
	{
		chapter = cs;
		cs++;
	}

	*n = point[chapter + 10].x;
	*m = point[chapter + 10].y;
	for (unsigned int i = 0; i < *n; i++)
	{
		for (unsigned int j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[chapter + 10][i][j];
		}
	}
}

void Sokoban::HardGame(char* ch)
{
	int Map[20][20], n, m, js;
	static int chapter = 1;
	memset(Map, -1, sizeof(Map));
	int sum = 0, data = 0, sl = 0;
	while (1)
	{
		int t = LevelGameReady();
		if (t == '2')
			break;
		while (1)
		{
			HardMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			GameOperate(Map, &n, &m, &js, &sum, &data, &sl, &chapter, ch);
			if (js == 0)
			{
				chapter++;
				if (chapter >= 21)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "恭喜你已经通过全部简单关卡,接下来有中等关卡等待你去挑战\n";
					Gotoxy(19, 26);
					cout << "！！！！！！";
					break;
				}
			}
			else if (js == 1)
				break;
			else if (js == 2)
			{
				*ch = '*';
				continue;
			}
		}
	}
}

void Sokoban::HardMap(int Map[][20], int* n, int* m, char* ch)
{
	static int cs = 0;
	int chapter;
	if (*ch == '*')
	{
		chapter = cs;
		if (chapter > 0)
			chapter--;
		*ch = '!';
	}
	else
	{
		chapter = cs;
		cs++;
	}

	*n = point[chapter + 20].x;
	*m = point[chapter + 20].y;
	for (unsigned int i = 0; i < *n; i++)
	{
		for (unsigned int j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[chapter + 20][i][j];
		}
	}
}

void Sokoban::Run()
{
	char ch = '!';
	system("title 推箱子---XHB制作"); //设置标题
	system("mode con cols=55 lines=32"); //控制窗口大小
	Menu(&ch);
}