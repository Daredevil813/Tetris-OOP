#include<iostream>
#define NOMINMAX
#include<windows.h>
#include<SFML/Graphics.hpp>
#include<fstream>
#pragma comment(lib, "user32.lib")
#include<ctime>
using namespace std;
using namespace sf;

class well
{
	int** p;
	friend class tetramino;
	friend class O;
	friend class I;
	friend class S;
	friend class Z;
	friend class L;
	friend class J;
	friend class T;
	friend class game;
public:
	well()
	{
		p = new int* [20];
		for (int i = 0; i < 20; i++)
		{
			p[i] = new int[10];
		}
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				p[i][j] = 0;
			}
		}
	}

	void print()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << p[i][j];
			}
			cout << endl;
		}
	}
};

class tetramino
{
protected:
	int x, y;
	int r;
	int height, width;

public:
	bool control;
	virtual bool gameend(well& u) =0;
	tetramino(int x1 = 0, int y1 = 0, int rotate = 1)
	{
		x = x1;
		y = y1;
		r = rotate;
		height = x1;
		width = x1;
		control = false;

	}
	bool getc()
	{
		return control;


	}
	void setx(int x1)
	{
		x = x1;
	}
	void sety(int y1)
	{
		y = y1;
	}
	void seth(int y)
	{
		height = y;
	}
	void setw(int y)
	{
		width = y;
	}
	void incx()
	{
		if (x < 9)
		{
			x++;
		}
	}
	void decx()
	{
		if (x > 0)
		{
			x--;
		}
	}
	void incy()
	{
		if (y < 19)
		{
			y++;
		}


	}
	void sc(bool& c)
	{
		if (c == 1)
			c = 0;
		else
			c = 1;
	}
	void incr()
	{
		r++;
		if (r == 5)
		{
			r = 1;
		}
	}
	virtual void right(well& u)
	{};
	virtual void left(well& u)
	{}
	virtual void rotate(well& u) {};
	virtual void down(well& u) {};
	virtual void check(well& u) {};
};
class I :public tetramino
{
public:

	I()
	{

	};
	void deassign(well& u)
	{
		if (r == 1 || r == 3)
		{
			for (int i = y; i < (y + 4); i++)
			{
				u.p[i][x] = 0;
			}

		}
		else
		{

			for (int i = x; i < (x + 4); i++)
			{
				u.p[y][i] = 0;
			}

		}



	}
	void assign(well& u)
	{
		if (r == 1 || r == 3)
		{
			for (int i = y; i < (y + 4); i++)
			{
				u.p[i][x] = 2;
			}

		}
		else
		{

			for (int i = x; i < (x + 4); i++)
			{
				u.p[y][i] = 2;
			}

		}



	}
	I(well& u)
	{
		setx(5);
		sety(0);
		setw(1);
		seth(4);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		if (rcheck(u))
		{
			incr();
		}
		assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x < 9 && u.p[y][x + 1] == 0 && u.p[y + 1][x + 1] == 0 && u.p[y + 2][x + 1] == 0 && u.p[y + 3][x + 1] == 0)
			{
				incx();
			}
		}
		else
		{
			if (x < 6 && u.p[y][x + 4] == 0)
			{
				incx();
			}
		};

		assign(u);


	};
	virtual void left(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x > 0) {
				if (u.p[y][x - 1] == 0 && u.p[y + 1][x - 1] == 0 && u.p[y + 2][x - 1] == 0 && u.p[y + 3][x - 1] == 0)
				{
					decx();
				}
			}
		}
		else
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0)
				{
					decx();
				}
			}
		}
		assign(u);



	}
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{

		if (r == 1 || r == 3)
		{
			if (y == 16)
				sc(control);
			else if (u.p[y + 4][x] != 0)
				sc(control);
		}
		else
		{
			if (y == 19)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 1][x + 1] != 0 || u.p[y + 1][2 + x] != 0 || u.p[y + 1][x + 3] != 0)
				sc(control);
		};


	}
	bool rcheck(well& u)
	{
		if (r == 1 || r == 3)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (x > 6)
			{
				while (k == 0)
				{


					if (x1 < 7 && u.p[y][x1 + 1] == 0 && u.p[y][x1 + 2] == 0 && u.p[y][x1 + 3] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}
					else if (x1 > 6 && u.p[y][x1 - 1] == 0)
					{
						t++;
						x1 = x - t;
					}
					else if (u.p[y][x1 - 1] != 0)
						return false;
					else
						return false;
				}
				k = 0;
			}
			else
			{
				while (k == 0 && x > 0)
				{
					if (u.p[y][x1 + 1] == 0 && u.p[y][x1 + 2] == 0 && u.p[y][x1 + 3] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}

					else if (u.p[y][x1 - 1] == 0)
					{
						t++;
						x1 = x - t;
					}

					else if (u.p[y][x1 - 1] != 0)
						return false;
					else
						return false;
				}

			}
		}
		else if (r == 2 || r == 4)
		{
			if (y > 16) 
			{
				return false;
			}
			if (u.p[y + 1][x] == 0 && u.p[y + 2][x] == 0 && u.p[y + 3][x] == 0)
			{
				return true;
			}
			else if (u.p[y + 1][x + 3] == 0 && u.p[y + 2][x + 3] == 0 && u.p[y + 3][x + 3] == 0)
			{
				setx(x + 3);
				return true;

			}
			else return false;

		}

	}
	bool gameend(well&u) 
	{
		if (r == 1 || r == 3)
		{
			if (y == 0)
			{
				if (u.p[y+4][x] != 0 )
				{
					return true;
				}
				else return false;
			}
			else return false;
		}



	}
};
class O :public tetramino
{
public:

	O()
	{

	};
	void deassign(well& u)
	{

		u.p[y][x] = 0;
		u.p[y + 1][x] = 0;
		u.p[y][x + 1] = 0;
		u.p[y + 1][x + 1] = 0;



	}
	void assign(well& u)
	{

		u.p[y][x] = 1;
		u.p[y + 1][x] = 1;
		u.p[y][x + 1] = 1;
		u.p[y + 1][x + 1] = 1;


	}
	O(well& u)
	{
		setx(4);
		sety(0);
		setw(2);
		seth(2);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		incr();
		assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (x < 18 && u.p[y][x + 2] == 0 && u.p[y + 1][x + 2] == 0)
		{
			incx();
		}
		assign(u);


	};
	virtual void left(well& u)
	{
		deassign(u);
		if (x > 0)
		{
			if (u.p[y][x - 1] == 0 && u.p[y + 1][x - 1] == 0)
				decx();
		}
		assign(u);



	}
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{
		if (y == 18)
		{
			sc(control);
		}
		else if (u.p[y + 2][x] != 0 || u.p[y + 2][x + 1] != 0)
		{
			sc(control);
		}
	}
	bool gameend(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (y == 0)
			{
				if (u.p[y + 2][x] != 0 || u.p[y + 2][x + 1] != 0)
				{
					return true;
				}
				else return false;
			}
			else return false;
		}



	}
};
class S :public tetramino
{
public:

	S()
	{

	};
	void deassign(well& u)
	{
		if (r == 1 || r == 3)
		{
			u.p[y][x] = 0;
			u.p[y - 1][x] = 0;
			u.p[y - 1][x + 1] = 0;
			u.p[y][x - 1] = 0;
		}
		else
		{
			u.p[y][x] = 0;
			u.p[y][x - 1] = 0;
			u.p[y - 1][x - 1] = 0;
			u.p[y + 1][x] = 0;



		}


	}
	void assign(well& u)
	{
		if (r == 1 || r == 3)
		{
			u.p[y][x] = 7;
			u.p[y - 1][x] = 7;
			u.p[y - 1][x + 1] = 7;
			u.p[y][x - 1] = 7;
		}
		else
		{
			u.p[y][x] = 7;
			u.p[y][x - 1] = 7;
			u.p[y - 1][x - 1] = 7;
			u.p[y + 1][x] = 7;



		}
	}
	S(well& u)
	{
		setx(4);
		sety(1);
		setw(3);
		seth(2);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		if (rcheck(u)) {
			incr();
		}assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x < 8 && u.p[y][x + 1] == 0 && u.p[y - 1][x + 2] == 0)
			{
				incx();
			}
		}
		else if (r == 2 || r == 4)
		{
			if (x < 9 && u.p[y][x + 1] == 0 && u.p[y + 1][x + 1] == 0)
			{
				incx();
			}


		}
		assign(u);


	};
	virtual void left(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x > 1)
				if
					(u.p[y][x - 2] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						decx();
					}
				}
		}
		else if (r == 2 || r == 4)
		{
			if (x > 1)
				if (u.p[y][x - 2] == 0 && u.p[y - 1][x - 2] == 0 && u.p[y + 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

		}
		assign(u);


	};
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (y == 19)
				sc(control);

			else if (u.p[y + 1][x] != 0 || u.p[y][x + 1] != 0 || u.p[y + 1][x - 1] != 0)
				sc(control);
		}
		else
		{
			if (y == 18)
				sc(control);
			else if (u.p[y + 2][x] != 0 || u.p[y + 1][x - 1] != 0)
				sc(control);
		};



	}
	bool rcheck(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (u.p[y - 1][x - 1] != 0)
			{
				if (x < 8 && u.p[y][x + 1] == 0 && u.p[y + 1][x + 1] == 0 || u.p[y - 1][x] == 0)
				{
					incx();
					return true;
				}
				else
					return false;
			}
			else if (u.p[y - 1][x - 1] != 0 || u.p[y + 1][x] != 0)
			{
				return false;
			}
			else return true;
		}
		else if (r == 2 || r == 4)
		{
			if (x < 9)
			{
				if (x > 1)
				{

					if (u.p[y - 1][x + 1] != 0)
					{
						if (u.p[y][x - 2] == 0 || u.p[y - 1][x] == 0)
						{
							decx();
							return true;
						}
					}
					if (u.p[y - 1][x] != 0 || u.p[y - 1][x + 1] != 0)
					{
						return false;

					}
					else return true;
				}
			}
			else
				if (x == 9)
				{
					if (u.p[y][x - 2] == 0 && u.p[y - 1][x] == 0)
					{
						decx();
						return true;

					}
					else
						return false;
				
				}

		}
	}
	bool gameend(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (y == 1)
			{
				if (u.p[y + 1][x] != 0 || u.p[y][x + 1] != 0 || u.p[y + 1][x - 1] != 0)
				{
					return true;
				}
				else return false;
			}
			else return false;
		}



	}
};
class Z :public tetramino
{
public:

	Z()
	{

	};
	void deassign(well& u)
	{
		if (r == 1 || r == 3)
		{
			u.p[y][x] = 0;
			u.p[y - 1][x] = 0;
			u.p[y - 1][x - 1] = 0;
			u.p[y][x + 1] = 0;
		}
		else
		{
			u.p[y][x] = 0;
			u.p[y][x - 1] = 0;
			u.p[y + 1][x - 1] = 0;
			u.p[y - 1][x] = 0;



		}


	}
	void assign(well& u)
	{

		if (r == 1 || r == 3)
		{
			u.p[y][x] = 6;
			u.p[y - 1][x] = 6;
			u.p[y - 1][x - 1] = 6;
			u.p[y][x + 1] = 6;
		}
		else
		{
			u.p[y][x] = 6;
			u.p[y][x - 1] = 6;
			u.p[y + 1][x - 1] = 6;
			u.p[y - 1][x] = 6;



		}


	}
	Z(well& u)
	{
		setx(4);
		sety(1);
		setw(3);
		seth(2);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		if (rcheck(u))
		{
			incr();
		}
		assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x < 8)
			{
				if (u.p[y][x + 2] == 0 && u.p[y - 1][x + 1] == 0)
				{
					incx();
				}
			}
		}
		else if (r == 2 || r == 4)
		{
			if (x < 9)
			{
				if (u.p[y][x + 1] == 0 && u.p[y - 1][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		assign(u);
	}
	virtual void left(well& u)
	{
		deassign(u);
		if (r == 1 || r == 3)
		{
			if (x > 1)
				if
					(u.p[y][x - 1] == 0 && u.p[y - 1][x - 2] == 0)
				{
					{
						decx();
					}
				}
		}
		else if (r == 2 || r == 4)
		{
			if (x > 1)
				if (u.p[y][x - 2] == 0 && u.p[y + 1][x - 2] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

		}
		assign(u);


	};
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (y == 19)
				sc(control);

			else if (u.p[y + 1][x] != 0 || u.p[y][x - 1] != 0 || u.p[y + 1][x + 1] != 0)
				sc(control);
		}
		else
		{
			if (y == 18)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 2][x - 1] != 0)
				sc(control);
		};
	}
	bool rcheck(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (u.p[y][x - 1] != 0 || u.p[y + 1][x - 1] != 0)
			{
				if (x < 8 && u.p[y - 1][x + 1] == 0 && u.p[y + 1][x] == 0)
				{
					incx();
					return true;
				}
				else
					return false;
			}
			else if (u.p[y + 1][x - 1] != 0 || u.p[y + 2][x - 1] != 0)
			{
				return false;
			}
		}
		else if (r == 2 || r == 4)
		{
			if (x < 9)
			{
				if (x > 1)
				{

					if (u.p[y - 1][x - 1] != 0 || u.p[y][x + 1] != 0)
					{
						if (u.p[y - 1][x + 1] == 0 && u.p[y][x + 1] == 0 && u.p[y][x + 2] == 0)
						{
							incx();
							return true;
						}
						if (u.p[y - 1][x - 1] == 0 && u.p[y][x - 2] == 0)
						{


							decx();
							return true;
						}
						else
							return false;
					}
					if (u.p[y][x + 1] != 0 || u.p[y - 1][x - 1] != 0)
					{
						return false;

					}
				}
			}
			else
				if (x == 9)
				{
					if (u.p[y - 1][x - 1] == 0 && u.p[y - 1][x] == 0)
					{
						decx();
						return true;

					}
					else
						return false;

				}

		}
	}
	bool gameend(well& u)
	{
		if (r == 1 || r == 3)
		{
			if (y == 1)
			{
				if (u.p[y + 1][x] != 0 || u.p[y][x - 1] != 0 || u.p[y + 1][x + 1] != 0)
				{
					return true;
				}
				else return false;
			
			}
			else return false;
		}



	}
};
class L : public tetramino
{
public:

	L()
	{

	};
	void deassign(well& u)
	{
		if (r == 1)
		{
			u.p[y][x] = 0;
			u.p[y + 1][x] = 0;
			u.p[y + 2][x] = 0;
			u.p[y + 2][x + 1] = 0;
		}
		else if (r == 2)
		{
			u.p[y][x] = 0;
			u.p[y][x - 1] = 0;
			u.p[y][x - 2] = 0;
			u.p[y + 1][x - 2] = 0;
		}
		else if (r == 3)
		{
			u.p[y][x] = 0;
			u.p[y - 1][x] = 0;
			u.p[y - 2][x] = 0;
			u.p[y - 2][x - 1] = 0;



		}
		else if (r == 4)
		{
			u.p[y][x] = 0;
			u.p[y][x + 1] = 0;
			u.p[y][x + 2] = 0;
			u.p[y - 1][x + 2] = 0;




		}
	}
	void assign(well& u)

	{
		if (r == 1)
		{
			u.p[y][x] = 3;
			u.p[y + 1][x] = 3;
			u.p[y + 2][x] = 3;
			u.p[y + 2][x + 1] = 3;
		}
		else if (r == 2)
		{
			u.p[y][x] = 3;
			u.p[y][x - 1] = 3;
			u.p[y][x - 2] = 3;
			u.p[y + 1][x - 2] = 3;
		}
		else if (r == 3)
		{
			u.p[y][x] = 3;
			u.p[y - 1][x] = 3;
			u.p[y - 2][x] = 3;
			u.p[y - 2][x - 1] = 3;



		}
		else if (r == 4)
		{
			u.p[y][x] = 3;
			u.p[y][x + 1] = 3;
			u.p[y][x + 2] = 3;
			u.p[y - 1][x + 2] = 3;




		}
	}
	L(well& u)
	{
		setx(4);
		sety(0);
		setw(2);
		seth(3);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		if (rcheck(u))
		{
			incr();
		}
		assign(u);
	}
	virtual void right(well& u)
	{
		deassign(u);



		if (r == 1)
		{
			if (x < 8)
			{
				if (u.p[y][x + 1] == 0 && u.p[y + 1][x + 1] == 0 && u.p[y + 2][x + 2] == 0)
				{
					incx();
				}
			}
		}
		else if (r == 2)
		{
			if (x < 9)
			{
				if (u.p[y + 1][x - 1] == 0 && u.p[y][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x < 9)
			{
				if (u.p[y - 1][x + 1] == 0 && u.p[y - 2][x + 1] == 0 && u.p[y][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x < 7)
			{
				if (u.p[y][x + 3] == 0 && u.p[y - 1][x + 3] == 0)
				{
					{
						incx();
					}
				}

			}
		}

		assign(u);


	};
	virtual void left(well& u)
	{
		deassign(u);
		if (r == 1)
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0 && u.p[y + 1][x - 1] == 0 && u.p[y + 2][x - 1] == 0)
				{
					decx();
				}
			}
		}
		else if (r == 2)
		{
			if (x > 2)
			{
				if (u.p[y][x - 3] == 0 && u.p[y + 1][x - 3] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x > 1)
			{
				if (u.p[y][x - 1] == 0 && u.p[y - 1][x - 1] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0 && u.p[y - 1][x + 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		assign(u);
	};
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{
		if (r == 1)
		{
			if (y == 17)
				sc(control);
			else if (u.p[y + 3][x] != 0 || u.p[y + 3][x + 1] != 0)
			{
				sc(control);

			}
		}
		else if (r == 2)
		{
			if (y == 18)
				sc(control);
			else if (u.p[y + 2][x - 2] != 0 || u.p[y + 1][x - 1] != 0 || u.p[y+1][x ] != 0)
			{
				sc(control);

			}


		}
		else if (r == 3)
		{
			if (y == 19)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y - 1][x - 1] != 0)
			{
				sc(control);

			}
		}
		else if (r == 4)
		{
			if (y == 19)

				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 1][x + 1] != 0 || u.p[y + 1][x + 2] != 0)
			{
				sc(control);

			}

		}
	}
	bool rcheck(well& u)
	{




		if (r == 1)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (x < 2)
			{
				while (k == 0)
				{


					if (x1 > 1)
					{
						if (u.p[y][x1 - 1] == 0 && u.p[y][x1 - 2] == 0 && u.p[y + 1][x1 - 2] == 0)
						{
							setx(x + t);
							return true;
							k = 1;
						}
					}
					else if (x1 < 9)
					{
						if (x > 0)
						{
							if (u.p[y + 1][x1 - 1] == 0 && u.p[y][x1 + 1] == 0)
							{
								t++;
								x1++;
							}
						}
						else if (u.p[y][x1 + 1] == 0)
						{
								t++;
								x1++;
						}
						else if (u.p[y][x1 + 1] != 0 || u.p[y + 1][x1 - 1] != 0)
							return false;
						else
							return false;
					}
					k = 0;
				}
			}
			else
			{
				while (k == 0)
				{
					if (u.p[y][x1 - 1] == 0 && u.p[y][x1 - 2] == 0 && u.p[y + 1][x1 - 2] == 0)
					{
						setx(x + t);
						return true;
						k = 1;
					}

					else if (u.p[y][x1 + 1] == 0 && u.p[y + 1][x1 +2] == 0)
					{
						t++;
						x1 = x - t;
					}

					else if (u.p[y][x1 + 1] != 0 || u.p[y + 1][x1 - 1] != 0)
						return false;
					else
						return false;
				}
			}


			}
			else if (r == 2)

			{
				int t = 0;
				bool k = 0;
				int x1 = x - t;

				if (y < 2)
				{


					

					 if (u.p[y + 1][x1] == 0 && u.p[y + 2][x1] == 0)
					{
						incy();
						incy();
					}
				
					 if (u.p[y - 2][x1 ] == 0 && u.p[y - 1][x1] == 0 && u.p[y - 2][x1 - 1] == 0)
				{
					setx(x - t);
					return true;
					k = 1;
				}
					else if (u.p[y + 1][x1] != 0 || u.p[y + 2][x1] != 0)
						return false;
					else
						return false;

				}
				else if (u.p[y -2][x1] == 0 && u.p[y - 1][x1] == 0 && u.p[y-2][x1-1] == 0)
				{
					setx(x - t);
					return true;
				}
				else
					return false;

			}
			else if (r == 3)
			{
				int t = 0;
				bool k = 0;
				int x1 = x - t;
				
				if (x > 7)
				{
					while (k == 0)
					{


						if (x1 < 8 && u.p[y][x1 + 2] == 0 && u.p[y - 1][x1 + 2] == 0 && u.p[y][x1 + 1] == 0)
						{
							setx(x - t);
							return true;
							k = 1;
						}
						else if (x1 > 7 && u.p[y][x1 - 1] == 0 )
						{
							t++;
							x1 = x - t;
						}
						else if (u.p[y][x1 - 1] != 0 )
							return false;
						else
							return false;
					}
					k = 0;
				}
				else
				{
					while (k == 0 && x > 0)
					{
						if (u.p[y][x1 + 2] == 0 && u.p[y - 1][x1 + 2] == 0 && u.p[y][x1 + 1] == 0)
						{
							setx(x - t);
							return true;
							k = 1;
						}

						else if (u.p[y][x1 - 1] == 0 && u.p[y - 1][x1 + 1] == 0)
						{
							t++;
							x1 = x - t;
						}

						else if (u.p[y][x1 - 1] != 0 || u.p[y + 1][x1 + 1] != 0)
							return false;
						else
							return false;
					}

				}
			}
			else if (r == 4)

			{
				int t = 0;
				bool k = 0;
				int x1 = x - t;
				if (y > 18)
				{
					return false;
				}

				{
					while (k == 0 && x > 0)
					{
						if (u.p[y + 1][x1] == 0 && u.p[y + 2][x1] == 0 && u.p[y + 2][x1 + 2] == 0)
						{
							setx(x - t);
							return true;
							k = 1;
						}

						else if (u.p[y + 1][x1 - 1] == 0 && u.p[y + 2][x1 - 1] == 0 && u.p[y + 2][x1 - 1] == 0 && u.p[y + 2][x1] == 0)
						{
							t++;
							x1 = x - t;
						}

						else if (u.p[y + 1][x1 - 1] != 0 || u.p[y + 2][x1 - 1] != 0 || u.p[y + 2][x1 - 1] != 0 || u.p[y + 2][x1] != 0)
							return false;
						else
							return false;
					}

				}
			}






		};
		bool gameend(well& u)
		{
			if (r == 1 )
			{
				if (y == 0)
				{
					if (u.p[y + 3][x] != 0 || u.p[y + 3][x + 1] != 0)
					{
						return true;
					}
					else return false;
				}
				else return false;
			}

			

		}};
class J :public tetramino
{
public:

	J()
	{

	};
	void deassign(well& u)
	{
		if (r == 1)
		{
			u.p[y][x] = 0;
			u.p[y + 1][x] = 0;
			u.p[y + 2][x] = 0;
			u.p[y + 2][x - 1] = 0;
		}
		else if (r == 2)
		{
			u.p[y][x] = 0;
			u.p[y][x - 1] = 0;
			u.p[y][x - 2] = 0;
			u.p[y - 1][x - 2] = 0;
		}
		else if (r == 3)
		{
			u.p[y][x] = 0;
			u.p[y - 2][x + 1] = 0;
			u.p[y - 1][x] = 0;
			u.p[y - 2][x] = 0;



		}
		else if (r == 4)
		{
			u.p[y][x] = 0;
			u.p[y][x + 2] = 0;
			u.p[y][x + 1] = 0;
			u.p[y + 1][x + 2] = 0;



		}

	}
	void assign(well& u)
	{
		if (r == 1)
		{
			u.p[y][x] = 4;
			u.p[y + 1][x] = 4;
			u.p[y + 2][x] = 4;
			u.p[y + 2][x - 1] = 4;
		}
		else if (r == 2)
		{
			u.p[y][x] = 4;
			u.p[y][x - 1] = 4;
			u.p[y][x - 2] = 4;
			u.p[y - 1][x - 2] = 4;
		}
		else if (r == 3)
		{
			u.p[y][x] = 4;
			u.p[y - 2][x + 1] = 4;
			u.p[y - 1][x] = 4;
			u.p[y - 2][x] = 4;
		}
		else if (r == 4)
		{
			u.p[y][x] = 4;
			u.p[y][x + 2] = 4;
			u.p[y][x + 1] = 4;
			u.p[y + 1][x + 2] = 4;

		}

	}
	J(well& u)
	{
		setx(4);
		sety(0);
		setw(2);
		seth(3);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);

		if (rcheck(u))
		{
			incr();
		}	assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (r == 1)
		{
			if (x < 9)
			{
				if (u.p[y][x + 1] == 0 && u.p[y + 1][x + 1] == 0 && u.p[y + 2][x + 1] == 0)
				{
					incx();
				}
			}
		}
		else if (r == 2)
		{
			if (x < 9)
			{
				if (u.p[y][x + 1] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x < 8)
			{
				if (u.p[y][x + 1] == 0 && u.p[y - 1][x + 1] == 0 && u.p[y - 2][x + 2] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x < 7)
			{
				if (u.p[y][x + 3] == 0 && u.p[y + 1][x + 3] == 0)
				{
					{
						incx();
					}
				}

			}
		}

		assign(u);
	};
	virtual void left(well& u)
	{

		deassign(u);



		if (r == 1)
		{
			if (x > 1)
			{
				if (u.p[y][x - 1] == 0 && u.p[y + 1][x - 1] == 0 && u.p[y + 2][x - 2] == 0)
				{
					decx();
				}
			}
		}
		else if (r == 2)
		{
			if (x > 0)
			{
				if (u.p[y][x - 3] == 0 && u.p[y - 1][x - 3] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0 && u.p[y - 1][x - 1] == 0 && u.p[y - 2][x - 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0 && u.p[y + 1][x + 2] == 0)
				{
					{
						decx();
					}
				}

			}
		}

		assign(u);




	};
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{


		if (r == 1)
		{
			if (y == 17)
			{
				sc(control);

			}
			else if (u.p[y + 3][x] != 0 || u.p[y + 3][x - 1] != 0)
			{
				sc(control);

			}
		}
		else if (r == 2)
		{
			if (y == 19)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 1][x - 1] != 0 || u.p[y +1 ][x -2] != 0)
			{
				sc(control);

			}


		}
		else if (r == 3)
		{
			if (y == 19)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y - 1][x + 1] != 0)
			{
				sc(control);

			}
		}

		else if (r == 4)
		{
			if (y == 18)

				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 1][x + 1] != 0 || u.p[y + 2][x + 2] != 0)
			{
				sc(control);

			}

		}




	}
	bool rcheck(well& u)
	{




		if (r == 1)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (y == 0) 
			{
				if (x > 1 && u.p[y + 1][x1 - 1] == 0 && u.p[y + 1][x1 - 2] == 0 && u.p[y][x1 - 2] == 0)
				{
					incy();
					return true;
				}
				else if(u.p[y+1][x1 +1] == 0)
				{
					incy();
					incx();
				}
			}
			if (x < 2)
			{
				while (k == 0)
				{


					if (x1 > 1)
					{
						if (u.p[y][x1 - 1] == 0 && u.p[y][x1 - 2] == 0 && u.p[y - 1][x1 - 2] == 0)
						{
							setx(x + t);
							return true;
							k = 1;
						}
					}
					else if (x1 < 9)
					{
						if (x > 0)
						{
							if (u.p[y - 1][x1 - 1] == 0 && u.p[y][x1 + 1] == 0)
							{
								t++;
								x1++;
							}
						}
						
						else if (u.p[y][x1 + 1] != 0 || u.p[y - 1][x1 - 1] != 0)
							return false;
						else
							return false;
					}
					k = 0;
				}
			}
			else
			{
				while (k == 0)
				{
					if (u.p[y][x1 - 1] == 0 && u.p[y][x1 - 2] == 0 && u.p[y - 1][x1 - 2] == 0)
					{
						setx(x + t);
						return true;
						k = 1;
					}

					else if (u.p[y - 1][x1 - 1] == 0 && u.p[y][x1 + 1] == 0)
					{
						t++;
						x1 = x +t;
					}

					else if (u.p[y][x1 + 1] != 0 || u.p[y - 1][x1 - 1] != 0)
						return false;
					else
						return false;
				}
			}
		}
		else if (r == 2)

		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;

			if (y < 2)
			{




				if (u.p[y + 1][x1] == 0 && u.p[y -1][x1] == 0 && u.p[y -1][x1+1] == 0)
				{
					
					incy();
				}

				if (u.p[y - 2][x1 + 1] == 0 && u.p[y - 1][x1] == 0 && u.p[y - 2][x1 ] == 0)
				{
					setx(x - t);
					return true;
					k = 1;
				}
				else if (u.p[y + 1][x1] != 0 || u.p[y -1][x1] != 0 || u.p[y - 1][x1+1] != 0)
					return false;
				else
					return false;

			}
			else if (x == 9) 
			{
				if (u.p[y - 2][x1 -1] == 0 && u.p[y - 1][x1 - 1] == 0 && u.p[y - 2][x1] == 0) 
				{
					decx();

				}
				if (u.p[y - 2][x1 + 1] == 0 && u.p[y - 1][x1 - 1] == 0 && u.p[y - 2][x1] == 0)
				{
					setx(x - t);
					return true;
				}


			}
			else if (u.p[y - 2][x1 +1] == 0 && u.p[y - 1][x1 - 1] == 0 && u.p[y -2][x1] == 0)
			{
				setx(x - t);
				return true;
			}
			else
				return false;

		}
		else if (r == 3)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (y == 0)
			{
				if (u.p[y + 1][x] == 0 && u.p[y + 3][x + 1] == 0)
				{
					incy();


				}
				else return false;

			}
			if (x > 7)
			{
				while (k == 0)
				{


					if (x1 < 8 && u.p[y][x1 + 2] == 0 && u.p[y - 1][x1 + 2] == 0 && u.p[y][x1 + 1] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}
					else if (x1 > 7 && u.p[y][x1 - 1] == 0 && u.p[y - 1][x1 + 1] == 0)
					{
						t++;
						x1 = x - t;
					}
					else if (u.p[y][x1 - 1] != 0 || u.p[y - 1][x1 - 1] != 0)
						return false;
					else
						return false;
				}
				k = 0;
			}
			else
			{
				while (k == 0 && x > 0)
				{
					if (u.p[y][x1 + 2] == 0 && u.p[y - 1][x1 + 2] == 0 && u.p[y][x1 + 1] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}

					else if (u.p[y][x1 - 1] == 0 && u.p[y - 1][x1 + 1] == 0)
					{
						t++;
						x1 = x - t;
					}

					else if (u.p[y][x1 - 1] != 0 || u.p[y + 1][x1 + 1] != 0)
						return false;
					else
						return false;
				}

			}
		}
		else if (r == 4)

		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (y > 18)
			{
				return false;
			}
			if (x == 0) 
			{
				if (x > 0)
				{
					if (u.p[y + 1][x1] == 0 && u.p[y + 2][x1] == 0 && u.p[y + 2][x1 + 2] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}
				}
				if (u.p[y + 1][x1 + 1] == 0 && u.p[y + 2][x1] == 0 && u.p[y + 2][x1 + 1] == 0)
				{
					incx();
					return true;
				}
				else if (u.p[y + 1][x1 + 1] != 0 ||u.p[y + 2][x1] != 0 || u.p[y + 2][x1 + 1] != 0)
				{
					return false;

				}
			
			}
			else 
			{
				while (k == 0 && x > 0)
				{
					if (u.p[y + 1][x1] == 0 && u.p[y + 2][x1] == 0 && u.p[y + 2][x1 + 2] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}

					else if (u.p[y + 1][x1 - 1] == 0 && u.p[y + 2][x1 - 1] == 0 && u.p[y + 2][x1 - 1] == 0 && u.p[y + 2][x1] == 0)
					{
						t++;
						x1 = x - t;
					}

					else if (u.p[y + 1][x1 - 1] != 0 || u.p[y + 2][x1 - 1] != 0 || u.p[y + 2][x1 - 1] != 0 || u.p[y + 2][x1] != 0)
						return false;
					else
						return false;
				}

			}
		}






	};
	bool gameend(well& u)
	{
		if (r == 1)
		{
			if (y == 0)
			{
				if (u.p[y + 3][x] != 0 || u.p[y + 3][x - 1] != 0)
				{
					return true;
				}
				else return false;
			}
			else return false;
		}



	}
};
class T :public tetramino
{

public:

	T()
	{

	};
	void deassign(well& u)
	{
		if (r == 1)
		{
			u.p[y][x] = 0;
			u.p[y][x + 1] = 0;
			u.p[y][x - 1] = 0;
			u.p[y + 1][x] = 0;
		}
		else if (r == 2)
		{
			u.p[y][x] = 0;
			u.p[y + 1][x] = 0;
			u.p[y - 1][x] = 0;
			u.p[y][x - 1] = 0;
		}
		else if (r == 3)
		{
			u.p[y][x] = 0;
			u.p[y][x + 1] = 0;
			u.p[y][x - 1] = 0;
			u.p[y - 1][x] = 0;



		}
		else if (r == 4)
		{
			u.p[y][x] = 0;
			u.p[y + 1][x] = 0;
			u.p[y - 1][x] = 0;
			u.p[y][x + 1] = 0;



		}

	}
	void assign(well& u) {
		if (r == 1)
		{

			u.p[y][x] = 5;
			u.p[y][x + 1] = 5;
			u.p[y][x - 1] = 5;
			u.p[y + 1][x] = 5;
		}
		else if (r == 2)
		{
			u.p[y][x] = 5;
			u.p[y + 1][x] = 5;
			u.p[y - 1][x] = 5;
			u.p[y][x - 1] = 5;
		}
		else if (r == 3)
		{
			u.p[y][x] = 5;
			u.p[y][x + 1] = 5;
			u.p[y][x - 1] = 5;
			u.p[y - 1][x] = 5;



		}
		else if (r == 4)
		{
			u.p[y][x] = 5;
			u.p[y + 1][x] = 5;
			u.p[y - 1][x] = 5;
			u.p[y][x + 1] = 5;



		}
	}
	T(well& u)
	{
		setx(4);
		sety(0);
		setw(2);
		seth(3);
		assign(u);
	};
	virtual void rotate(well& u)
	{
		deassign(u);
		if (rcheck(u))
		{
			incr();
		}
		assign(u);

	}
	virtual void right(well& u)
	{
		deassign(u);
		if (r == 1)
		{
			if (x < 8)
			{
				if (u.p[y][x + 2] == 0 && u.p[y + 1][x + 1] == 0)
				{
					incx();
				}
			}
		}
		else if (r == 2)
		{
			if (x < 9)
			{
				if (u.p[y][x + 1] == 0 && u.p[y - 1][x + 1] == 0 && u.p[y + 1][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x < 8)
			{
				if (u.p[y][x + 2] == 0 && u.p[y - 1][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x < 8)
			{
				if (u.p[y][x + 2] == 0 && u.p[y + 1][x + 1] == 0 && u.p[y - 1][x + 1] == 0)
				{
					{
						incx();
					}
				}

			}
		}

		assign(u);

	};
	virtual void left(well& u)
	{
		deassign(u);
		if (r == 1)
		{
			if (x > 1)
			{
				if (u.p[y][x - 2] == 0 && u.p[y + 1][x - 1] == 0)
				{
					decx();
				}
			}
		}
		else if (r == 2)
		{
			if (x > 1)
			{
				if (u.p[y][x - 2] == 0 && u.p[y - 1][x - 1] == 0 && u.p[y + 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 3)
		{
			if (x > 1)
			{
				if (u.p[y][x - 2] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}
		else if (r == 4)
		{
			if (x > 0)
			{
				if (u.p[y][x - 1] == 0 && u.p[y + 1][x - 1] == 0 && u.p[y - 1][x - 1] == 0)
				{
					{
						decx();
					}
				}

			}
		}

		assign(u);

	};
	virtual void down(well& u)
	{
		deassign(u);
		incy();
		assign(u);

	}
	virtual void check(well& u)
	{

		if (r == 1)
		{
			if (y == 18)
				sc(control);
			else if (u.p[y + 2][x] != 0 || u.p[y + 1][x - 1] != 0 || u.p[y + 1][x + 1] != 0)
			{
				sc(control);

			}

		}
		else if (r == 2)
		{
			if (y == 18)
				sc(control);
			else if (u.p[y + 2][x] != 0 || u.p[y + 1][x - 1] != 0)
			{
				sc(control);

			}
		}
		else if (r == 3)
		{
			if (y == 19)
				sc(control);
			else if (u.p[y + 1][x] != 0 || u.p[y + 1][x - 1] != 0 || u.p[y + 1][x + 1] != 0)
			{
				sc(control);

			}
		}
		else if (r == 4)
		{
			if (y == 17)
				sc(control);
			else if (u.p[y + 2][x] != 0 || u.p[y + 1][x + 1] != 0)
			{
				sc(control);

			}
		}




	}
	bool rcheck(well& u)
	{




		if (r == 1)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (y == 0)
			{
				if (u.p[y + 1][x1 - 1] == 0)
				{
					incy();
					return true;
				}
				else return false;

			}
			if (u.p[y - 1][x] == 0 )
			{
				setx(x - t);
				return true;
				k = 1;

			}
			else if (u.p[y+2][x] == 0&& u.p[y + 1][x-1] == 0)
			{

				incy();

			}
			else if (u.p[y - 1][x] != 0)
				return false;
			else
				return false;



		}
		else if (r == 2)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (x > 8)
			{
				while (k == 0)
				{


					if (x1 < 9 && u.p[y][x1 + 1] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}
					else if (x1 > 8 && u.p[y][x1 - 2] == 0&& u.p[y+1][x1 - 1] == 0)
					{
						t++;
						x1 = x - t;
					}
					else if (u.p[y][x1 + 2] != 0 || u.p[y+1][x1 - 1] != 0)
						return false;
					else
						return false;
				}
				k = 0;
			}
			else
			{
				while (k == 0 && x > 0)
				{
					if (u.p[y][x1 +1] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}

					else if (u.p[y][x1 - 2] == 0 && u.p[y + 1][x1 - 1] == 0)
					{
						t++;
						x1 = x - t;
					}

					else if (u.p[y][x1 + 2] != 0 || u.p[y + 1][x1 - 1] != 0)
						return false;
					else
						return false;
				}

			}
		}
		else if (r == 3)
		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (y > 1)
			{

				if (u.p[y][x1 + 1] == 0)
				{
					setx(x - t);
					return true;
					k = 1;
				}

				else if (u.p[y - 2][x1] == 0)
				{
					y--;
				}

				else if (u.p[y - 2][x1] != 0 || u.p[y + 1][x1] != 0)
					return false;
				else
					return false;

			}
			else if (u.p[y][x1 + 1] == 0)
			{
				setx(x - t);
				return true;

			}

		}
		else if (r == 4)

		{
			int t = 0;
			bool k = 0;
			int x1 = x - t;
			if (x == 1) {
				while (x < 1)
				{

					if (u.p[y][x1 - 1] == 0)
					{
						setx(x - t);
						return true;
						k = 1;
					}
					else if (u.p[y][x1 + 2] == 0 && u.p[y + 1][x1 + 1] == 0)
					{
						incx();
					}

					else if (u.p[y + 1][x1 + 1] != 0 && u.p[y][x1 + 2] != 0)
						return false;
					else
						return false;


				}
			}
			else 
			{

				if (u.p[y][x1 - 1] == 0)
				{
					setx(x - t);
					return true;
					k = 1;
				}
				else if (u.p[y][x1 + 2] == 0 && u.p[y + 1][x1 + 1] == 0)
				{
					incx();
				}

				else if (u.p[y + 1][x1 + 1] != 0 && u.p[y][x1 + 2] != 0)
					return false;
				else
					return false;

			}
		}






	};
	bool gameend(well& u)
	{
		if (r == 1)
		{
			if (y == 0)
			{
				if (u.p[y + 2][x] != 0 || u.p[y + 1][x - 1] != 0 || u.p[y + 1][x + 1] != 0)
				{
					return true;
				}
				else return false;
			}
			else return false;
		}
		

	}
};
class game
{
	well pt;
	bool control;
	tetramino* shape = nullptr;
	int level;
	int Line;
	int score;
	string Name;
	bool end;
public:
	game(int x1 = 0, int y1 = 1)
	{
		control = x1;
		score = x1;
		level = y1;
		Line = x1;
		score = x1;
		end = x1;
	}
	void sc(well& u)
	{

		for (int i = 0; i < 20; i++)
		{
			if (horizontalchecker(u, i))
			{

				score++;
				Line++;
				if (Line == 10)
				{

					level++;
					Line = 0;

				}
				down(u, i);
			}
		}
	}
	void down(well& u, int y)
	{

		for (int i = y; i > 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				u.p[i][j] = u.p[i - 1][j];
			}
		}
		for (int j = 0; j < 10; j++)
		{
			u.p[0][j] = 0;
		}
	}
	bool horizontalchecker(well& u, int y)
	{
		for (int j = 0; j < 10; j++)
		{
			if (u.p[y][j] == 0)
			{
				return false;
			}
		}
		return true;
	}
	void random()
	{
		int s;
		srand(time((0)));

		s = rand();
		s = s % 7;


		if (s == 0)
		{

			shape = new S(pt);
		}
		else if (s == 1) {

			shape = new O(pt);
		}
		else if (s == 2)
		{

			shape = new I(pt);
		}
		else if (s == 3)
		{

			shape = new L(pt);
		}
		else if (s == 4)
		{

			shape = new J(pt);
		}
		else if (s == 5) {

			shape = new T(pt);
		}
		else if (s == 6) {

			shape = new Z(pt);
		}
	}
	void scoreHandling()
	{
		ifstream fin("sc.txt");
		ifstream fin_n("nm.txt");
		ofstream fout("tsc.txt");
		ofstream fout_n("tnm.txt");
		bool check = false;
		string tempName;
		string s_num;
		int i = 0;
		while (getline(fin, s_num) && i < 5)
		{
			getline(fin_n, tempName);
			int num = stoi(s_num);
			if (score > num && check == false)
			{
				fout << score << endl;
				fout_n << Name << endl;
				check = true;
				i++;
			}
			else if (check == false)
			{
				fout << num << endl;
				fout_n << tempName << endl;
				i++;
			}
			if (check == true && i != 5)
			{
				fout << num << endl;
				fout_n << tempName << endl;
				i++;
			}
		}
		fin.close();
		fin_n.close();
		fout.close();
		fout_n.close();
		remove("sc.txt");
		remove("nm.txt");
		rename("tnm.txt", "nm.txt");
		rename("tsc.txt", "sc.txt");
	}

	void game1()
	{

		cout << "Enter your name" << endl;
		getline(cin, Name);
		random();
		RenderWindow window(VideoMode(1000, 1000), "TETRIS", Style::Default);
		sf::Clock timer; //  a clock object to measure time
		float fallTime = 1.1f - level * 0.1; // Set the fall time
		sf::Time timeSinceLastFall = sf::Time::Zero; // Keep track of time since the last fell

		while (window.isOpen() && end == 0)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Escape)
						window.close();
					if (event.key.code == Keyboard::Down)
					{
						shape->check(pt);
						if (shape->control == 0)
						{
							shape->down(pt);
						}
						if (shape->control)
						{
							sc(pt);
							random();
							if (shape->gameend(pt))
							{
								end = 1;
							}
						}
					}
					if (event.key.code == Keyboard::Left)
						shape->left(pt);
					if (event.key.code == Keyboard::Right)
						shape->right(pt);
					if (event.key.code == Keyboard::Up)
						shape->rotate(pt);
				}
			}
			// Update position if enough time has passed
			timeSinceLastFall += timer.restart();
			if (timeSinceLastFall.asSeconds() >= fallTime)
			{
				shape->check(pt);
				if (shape->control == 0)
				{
					shape->down(pt);
				}
				if (shape->control)
				{
					sc(pt);
					random();
					if (shape->gameend(pt))
					{
						end = 1;
					}
				}timeSinceLastFall = sf::Time::Zero;
			}
			if (level != 11 && end == 0)//add condition of gameend
			{
				window.clear(Color(27, 161, 226));
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						drawSquare(window, sf::Vector2f(100.f + j * 30, 100.f + i * 30), pt.p[i][j]);
					}
				}
				drawtext(window, Vector2f(450, 200), "Name: " + Name);
				drawtext(window, Vector2f(450, 260), "level:" + to_string(level));
				drawtext(window, Vector2f(450, 320), "Score:" + to_string(score));
				drawtext(window, Vector2f(450, 380), "Lines:" + to_string(Line));

				ifstream fin("sc.txt");
				ifstream fin_n("nm.txt");
				string tempName;
				string s_num;

				drawtext(window, Vector2f(450, 450), "Highscore: ");
				for (int i = 1; i < 6; i++)
				{
					getline(fin, s_num);
					getline(fin_n, tempName);
					int num = stoi(s_num);
					drawtext(window, Vector2f(450, (450 + (i * 60))), tempName + "  " + to_string(num));

				}
				fin.close();
				fin_n.close();

			}
			else
			{
				scoreHandling();
				window.clear(Color::Red);
				drawtext(window, Vector2f(200, 200), "Your Score:" + to_string(score));
			}
			window.display();
		}
		if (end == 1)
		{
			Event event;
			scoreHandling();
			while (window.isOpen())
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
							window.close();
					}
					window.clear(Color::Red);
					drawtext(window, Vector2f(200, 200), "Your Score:" + to_string(score));
					window.display();
				}
			}
		}
	}

			

	void drawtext(RenderWindow& window, Vector2f position, string Na)
	{
		sf::Font font;
		if (!font.loadFromFile("GoldenWings.ttf"))
		{
			// Handle error - unable to load font file
		}
		sf::Text nameText;
		nameText.setFont(font);
		nameText.setCharacterSize(24);
		nameText.setFillColor(sf::Color::White);
		nameText.setPosition(position); //  position of the text
		nameText.setString(Na);
		window.draw(nameText);
	}
	void drawSquare(RenderWindow& window, Vector2f position, int num)
	{
		Color fillColor;
		if (num == 1)
			fillColor = Color::White;
		if (num == 2)
			fillColor = Color::Yellow;
		if (num == 3)
			fillColor = Color::Green;
		if (num == 4)
			fillColor = Color::Red;
		if (num == 5)
			fillColor = Color::Blue;
		if (num == 6)
			fillColor = Color(170, 0, 255);
		if (num == 7)
			fillColor = Color(255, 165, 0);
		if (num == 0)
			fillColor = Color::Black;
		// creating a square shape
		sf::RectangleShape square(Vector2f(30.f, 30.f));
		square.setPosition(position);
		square.setFillColor(fillColor);
		square.setOutlineColor(Color::White);
		square.setOutlineThickness(1);

		// creating the square to the window
		window.draw(square);
	}
	
};

int main()
{

	game test;
	test.game1();
	
}