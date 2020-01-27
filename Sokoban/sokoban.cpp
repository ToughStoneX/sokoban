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

//0:�յ�,1:��,3:Ŀ�ĵ�,4:����,5:��
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

/*��λ���*/
void Sokoban::Gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*���ع��*/
void Sokoban::Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 1,0Ϊ����ȺͿɼ���
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*���˵�*/
void Sokoban::Menu(char* ch)
{
	while (1)
	{
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\t       ��        ��        ��\n\n";
		cout << "\n\n\t\t       ������\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):��ʼ��Ϸ\n\n";
		cout << "\t\t   (2):��������\n\n";
		cout << "\t\t   (3):��Ϸ����\n\n";
		cout << "\t\t   (4):�˳���Ϸ\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "****************��һ�����ȹۿ���������****************\n\n";
		cout << "";
		cout << "\t\t    ��������š�\n";
		
		int s = _getch();
		while (s < '1' || s > '4')
		{
			cout << "\t\t�����������������롣\n";
			s = _getch();
		}
		if (s == '1')
			MenuOne(ch); // �˵�һ
		else if (s == '2')
			Operation(ch);
		else if (s == '3')
			Introduction(ch);
		else
		{
			int i = MessageBox(NULL, L"\nȷ��Ҫ�˳���Ϸ��", L"�˳���ʾ", MB_YESNO);
			if (i == IDYES)
				exit(0);
		}
	}
}

/*��������*/
void Sokoban::Operation(char* ch)
{
	char hh = '!';
	while (1)
	{
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "\t\t\t����˵��:\n\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); // ��ɫ
		cout << "   (W):�����ƶ� (S):�����ƶ� (A):�����ƶ� (D):�����ƶ�\n\n";
		cout << "      (��):�������� (��):������   (��):����Ŀ�ĵ�\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); // ��ɫ
		cout << "\t        *������ǰ����������뷨��\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "\t\t     �˳��밴   ����\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		Gotoxy(29, 16);
		cout << "ESC";
		hh = _getch();
		if (hh == 27)
		{
			// ע��Դ��������ط��о���̫�ԣ��᲻���׽��µ�while���棬ֱ����break�˳��ص�֮ǰ��Menu�����л᲻���һ�㣿
			//Menu(ch);
			break;
		}
	}
}

/*��Ϸ����*/
void Sokoban::Introduction(char* ch)
{
	int s;
	system("cls");
	Hide(); // ���ع��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << ("\n\n\n\n\n\n\n");
	cout << ("         ------------------------------------\n\n");
	cout << ("\t\t (1):��Ϸ����:������\n\n");
	cout << ("\t\t (2):��Ϸ���:->(next)\n\n");
	cout << ("\t\t (3):�������:2018��3��\n\n");
	cout << ("\t\t (4):����:xhb\n\n");
	cout << ("\t\t (5):QQ:2775751197\n\n");
	cout << ("\t\t (6):�汾:%d.\n\n", VERSION);
	cout << ("\t\t (7):�˳�ҳ��\n\n");
	cout << ("         ------------------------------------\n\n");
	cout << ("\t\t    ��������š�\n");
	s = _getch();
	while (s != '2' && s != '7')
	{
		cout << "\t\tSorry�������û����һҳ�ˡ�\n";
		s = _getch();
	}
	if (s == '2')
		GameSummary(ch); // ��Ϸ���
	else if (s == '7')
	{
		//Menu(ch);
		; // ʲô��������ֱ���˳�
	}
}

/*��Ϸ����*/
void Sokoban::GameSummary(char* ch)
{
	while (1)
	{
		char hh = '!';
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n";
		cout << "   �������ӡ���һ��������Ϸ��1982�����ձ�Thinking Rabbit��˾�״η���";
		cout << "֮��������Ϸ�����������������ƻ�������Ʒ����ʹ�����ӳ�Ϊ������Ϸ�Ĵ����ʡ�";
		cout << "��ϷҪ�������һ����С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�ã��Բ�С�ľͻ����";
		cout << "t�����޷��ƶ�����ͨ������ס�������������Ҫ������������޵Ŀռ��ͨ��������";
		cout << "t�����ƶ��Ĵ����λ�ã�����˳����������� \n";
		cout << "    ��������һ�������ձ��Ĺ�����Ϸ��Ŀ������ѵ����ҵ��߼�˼����������һ����";
		cout << "С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�ã��Բ�С�ľͻ���������޷��ƶ�����ͨ������";
		cout << "ס�������������Ҫ������������޵Ŀռ��ͨ�����������ƶ��Ĵ����λ�ã�����˳";
		cout << "�����������\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "        ע����Ϸ�ؿ���Դ�ھ��������ӹؿ���\n\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\t\t  �˳��밴   ����\n";
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

/*�˵�һ*/
void Sokoban::MenuOne(char* ch)
{
	while (1)
	{
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):����ģʽ\n\n";
		cout << "\t\t   (2):ѡ��ģʽ\n\n";
		cout << "\t\t   (3):�˳�ҳ��\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    ��������š�\n";
		int s = _getch();
		while (s < '1' || s > '3')
		{
			cout << "\t\t�����������������롣\n";
			s = _getch();
		}
		if (s == '1')
			MenuTwo(ch); // �˵���
		else if (s == '2')
			Select(ch); // ѡ��ģʽ
		else
		{
			// ע��Դ��������ط��о���̫�ԣ��᲻���׽��µ�while���棬ֱ����break�˳��ص�֮ǰ��Menu�����л᲻���һ�㣿
			//Menu(ch);
			break;
		}
	}
}

/*ѡ��ؿ�*/
void Sokoban::Select(char* ch)
{
	int chapter;
	while (1)
	{
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t    ��\n\n\t\t\t   ����\n\n\t\t\t ��Ҫѡ��\n\n\t\t      �Ĺؿ�(1-40��)��\n\n\t\t     ����0���˵�ǰһ\n\n\t\t    ҳ�档֮�󰴻س�����";
		scanf_s("%d", &chapter);
		while (chapter < 0 || chapter > 40)
		{
			cout << "\t\t�����������������롣\n";
			scanf_s("%d", &chapter);
		}
		if (chapter == 0)
			break; // ʲô���������˻ص��˵�һ
		else
			SelectGameReady(ch, chapter);
	}
}

/*�ؿ�ѡ����ϣ���Ϸ׼��*/
int Sokoban::SelectGameReady(char* ch, int chapter)
{
	int ret;
	while (1)
	{
		int s;
		system("cls");
		Hide(); // ���ع��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n\n\n\n\n\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t   (1):��Ϸ��ʼ\n\n";
		cout << "\t\t   (2):��Ϸ�˳�\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    ��������š�\n";
		s = _getch();
		while (s != '1' && s != '2')
		{
			cout << "\t\t�����������������롣\n";
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

/*��Ϸ��ʼ*/
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
				Hide(); // ���ع��
				cout << "\n\t\t    �� ϲ ͨ �أ�\n\n";
				cout << "\t       ���Ե�,�������ùؿ���\n";
				CountDown();
				clear_flag = true;
				break;
			}
			PlayGame(Map, &n, &m, ch);
			if (*ch == '*')
			{
				step = 0; // ����˳������Զ���ղ�������
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

/*ѡ�ص�ͼ*/
void Sokoban::SelectMap(int Map[][20], int* n, int* m, char* ch, int chapter)
{
	if (chapter > 0)
		chapter--;

	// ��ͼ��С
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

/*���Ƶ�ͼ*/
int Sokoban::DrawMap(int Map[20][20], int* n, int* m, int chapter)
{
	int sum = 0;
	Hide();
	cout << "\n\n\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	//cout << "\t\t     ��  " << chapter << "  ��\n\n\n\n";
	for (int i = 0; i < *n; i++)
	{
		cout << "\t\t   ";
		for (int j = 0; j < *m;j++)
		{
			switch (Map[i][j]) {
			case 1: // ǽ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("��");
				break;
			case 0: // �յ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("  ");
				break;
			case 3: // Ŀ�ĵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("��");
				break;
			case 4: // ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("��");
				break;
			case 5: // ��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				printf("��");
				break;
			case 7: // ������Ŀ�ĵ� 4+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("��");
				sum++;
				break;
			case 8: // ����Ŀ�ĵ� 5+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("��");
				break;
			}
		}
		cout << endl;
	}

	if (space == 1)
	{
		cout << "\n\t\t     ��ǰ����Ϊ" << step << "����";
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
		cout << "\n\t\t  ���ո���鿴��ǰ������";
	}
	disp = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n     ��ESC���˳�����Ϸ��֮�����½���Ӹù����¿�ʼ��\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n\t   ��ʼ��Ϸǰ���뷨��������Ӣ�Ĵ�д��\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	Gotoxy(12, 23);
	cout << "W/��:����";
	Gotoxy(32, 23);
	cout << "S/��:����";
	Gotoxy(12, 25);
	cout << "A/��:����";
	Gotoxy(32, 25);
	cout << "D/��:����";

	return sum;
}

/*���㿪ʼʱδ��Ŀ�ĵص�������*/
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

/*�������ӿ�ʼʱ����Ŀ�ĵص���Ŀ*/
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

/*����ʱ*/
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

/*��Ϸ����*/
void Sokoban::PlayGame(int Map[20][20], int* n, int* m, char* ch)
{
	char input;
	int i, j;
	// ȷ���˵�λ��
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
	// ��
	case 72:
	case 'W':
	case 'w':
		if (Map[i - 1][j] == 0 || Map[i - 1][j] == 3) // �˵�ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		{
			Map[i - 1][j] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i - 1][j] == 4 || Map[i - 1][j] == 7) // �˵�ǰ��������
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
	
	// ��
	case 80:
	case 'S':
	case 's':
		if (Map[i + 1][j] == 0 || Map[i + 1][j] == 3) // ��ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		{
			Map[i + 1][j] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i + 1][j] == 4 || Map[i + 1][j] == 7) // �˵�ǰ��������
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

	// ��
	case 75:
	case 'A':
	case 'a':
		if (Map[i][j - 1] == 0 || Map[i][j - 1] == 3) // ��ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		{
			Map[i][j - 1] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i][j - 1] == 4 || Map[i][j - 1] == 7) // �˵�ǰ��������
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

	// ��
	case 77:
	case 'D':
	case 'd':
		if (Map[i][j + 1] == 0 || Map[i][j + 1] == 3) // ��ǰ���ǿյػ����˵�ǰ����Ŀ�ĵ�
		{
			Map[i][j + 1] += 5;
			Map[i][j] -= 5;
			step++;
		}
		else if (Map[i][j + 1] == 4 || Map[i][j + 1] == 7) // �˵�ǰ��������
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

/*�˵���*/
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
		cout << "\t\t   (1):�򵥹ؿ�\n\n";
		cout << "\t\t   (2):�еȹؿ�\n\n";
		cout << "\t\t   (3):���ѹؿ�\n\n";
		cout << "\t\t   (4):�˳�ҳ��\n\n";
		cout << "         ------------------------------------\n\n";
		cout << "\t\t    ��������š�\n";
		s = _getch();
		while (s < '1' || s > '4')
		{
			cout << "������������������:";
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

//��Ϸ׼��
int Sokoban::LevelGameReady()
{
	system("cls");
	Hide();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//��ɫ
	int s;
	cout << "\n\n\n\n\n\n\n";
	cout << "         ------------------------------------\n\n";
	cout << "\t\t   (1):��Ϸ��ʼ\n\n";
	cout << "\t\t   (2):��Ϸ�˳�\n\n";
	cout << "         ------------------------------------\n\n";
	cout << "\t\t    ��������š�\n";
	s = _getch();
	while (s != '1' && s != '2')
	{
		cout << "\t\t�����������������롣\n";
		s = _getch();
	}
	return s;
}

/*���Ѷȹؿ�����*/
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
					cout << "��ϲ���Ѿ�ͨ��ȫ���򵥹ؿ�,���������еȹؿ��ȴ���ȥ��ս\n";
					Gotoxy(19, 26);
					cout << "������������";
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
		system("cls");//����
		Hide();
		*sum = DrawMap(Map, n, m, *chapter);
		*sum -= *sl;
		if (*sum == *data)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t    �� ϲ ͨ �أ�\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			int t = MessageBox(NULL, L"\t      �����������\n\n\t�Ƿ������һ�أ�", L"��ʾ", MB_YESNO);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\t\t ͨ�����ò���Ϊ" << step << "����\n";
			end = clock();
			printf("\t\t ͨ������ʱ��Ϊ%.3lf��\n", (double)(end - start) / 9.56);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\t\t ���Ե�,���ڴ�����һ�ء�";
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
			int i = MessageBox(NULL, L"\t\nȷ��Ҫ�˳���Ϸ��\n\n����ʾ���˳������½�����˳��Ĺؿ���ʼ����", L"�˳���ʾ", MB_YESNO);
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
					cout << "��ϲ���Ѿ�ͨ��ȫ���򵥹ؿ�,���������еȹؿ��ȴ���ȥ��ս\n";
					Gotoxy(19, 26);
					cout << "������������";
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
					cout << "��ϲ���Ѿ�ͨ��ȫ���򵥹ؿ�,���������еȹؿ��ȴ���ȥ��ս\n";
					Gotoxy(19, 26);
					cout << "������������";
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
	system("title ������---XHB����"); //���ñ���
	system("mode con cols=55 lines=32"); //���ƴ��ڴ�С
	Menu(&ch);
}