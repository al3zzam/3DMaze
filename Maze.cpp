#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <glut.h>

using namespace std;

class Position
{
public:
	Position (float X = 0.0, float Y = 0.0, float Z = 0.0)
		: x(X), y(Y), z(Z)
	{}
	float x, y, z;
};

class Vector
{
public:
	Vector(float X = 0.0, float Y = 0.0, float Z = 0.0)
		: x(X), y(Y), z(Z)
	{}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
		z /= Len;
	}

	float x, y, z;
};

class Color
{
public:
	Color(float r = 0.0, float g = 0.0, float b = 0.0)
		: red(r), green(g), blue(b)
	{}
	float red, green, blue;
};

class Box
{
public:
	Box(Position posStart, Position posDest, float xLen, float yLen, float zLen, Color clr)
		: posStart(posStart), posDest(posDest), clr(clr), xLength(xLen), yLength(yLen), zLength(zLen), 
		motionDir(posDest.x - posStart.x, posDest.y - posStart.y, posDest.z - posStart.z)
	{
		motionDir.Normalize();
	}

	void Draw() const;
	bool Insersection(const Box& other) const;
	void Move();

	Position posStart, posDest;
	Color clr;
	Vector motionDir;
	float xLength, yLength, zLength;
};

void Box::Draw() const
{
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face
	glColor3f(clr.red, clr.green, clr.blue);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);

	// Bottom face 
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);

	// Front face
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);

	// Back face
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);

	// Left face
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);

	// Right face
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glEnd();  // End of drawing color-cube

	glLineWidth(2);
	glColor3f(0.0f, 0.0f, 0.0f);

	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glBegin(GL_LINE_LOOP);                // Begin drawing the color cube with 6 quads
	// Top face 
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Bottom face
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Front face
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Back face
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Left face
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x - xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Right face
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z + zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y + yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z - zLength / 2);
	glVertex3f(posStart.x + xLength / 2, posStart.y - yLength / 2, posStart.z + zLength / 2);
	glEnd();  // End of drawing color-cube
}

bool Box::Insersection(const Box& other) const
{
	if (posStart.x + xLength / 2 < other.posStart.x - other.xLength / 2) return false;
	if (posStart.x - xLength / 2 > other.posStart.x + other.xLength / 2) return false;

	if (posStart.z + zLength / 2 < other.posStart.z - other.zLength / 2) return false;
	if (posStart.z - zLength / 2 > other.posStart.z + other.zLength / 2) return false;
	return true; // boxes intersect
}

void Box::Move()
{
	
	if(posStart.x<posDest.x)
		posStart.x+=0.0088;
	
	if(posStart.y<posDest.y)
		posStart.y+=0.0088;
	
	if(posStart.z<posDest.z)
		posStart.z+=0.0088;

	if(posStart.x>posDest.x)
		posStart.x-=0.0088;
	if(posStart.y>posDest.y)
		posStart.y-=0.0088;
	if(posStart.z>posDest.z)
		posStart.z-=0.0088;

}

float thinkness = 0.05;

// floor box
Box fr(Position(0, 0, 0), Position(0, 0, 0), 6, thinkness, 5, Color(0.2, 0.2, 0.2));
Box flr(Position(0, 0, 0), Position(0, 0, 0), 7, thinkness, 6, Color(0.2, 0.2, 0.2));

// player box
Box player(Position(-2.5, 0.3, -1.5), Position(-2.5, 0.3, -1.5), 0.5, 0.5, 0.5, Color(1.0, 0.0, 0.0));

// target box
Box target(Position(0, 0.3, -0.5), Position(0, 0.3, -0.5), 0.5, 0.5, 0.5, Color(0.0, 0.45, 0.0));

std::vector<Box> vecWalls;

std::clock_t start;
double duration;

const float step = 0.1;			// motion step

bool bWin = false;

float width, height;	// global variables to store window width and height
float xRot = 30, yRot = -45;

int numWalls = 0;	// initially numWalls = 0


void buildMaze()
{
	// Draw X Rectangles
	vecWalls.push_back(Box(Position(0, 0, 0), Position(0, 0.5, -3), 7, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-2, 0.5, -2), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(3, 0.5, -2), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-2.5, 0.5, -1), 2, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(0, 0.5, -1), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(2, 0.5, -1), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(0, 0.5, 0), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(3, 0.5, 0), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-1, 0.5, 1), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(2, 0.5, 1), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-2, 0.5, 2), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(0, 0.5, 2), 1, 1, thinkness, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(0, 0.5, 3), 7, 1, thinkness, Color(0.0, 1.0, 1.0)));

	// Draw Z Rectangles
	vecWalls.push_back(Box(Position(0, 0, 0), Position(-3.5, 0.5, -2), thinkness, 1, 2, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(-3.5, 0.5, 1), thinkness, 1, 4, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-2.5, 0.5, 1), thinkness, 1, 2, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-1.5, 0.5, 1.5), thinkness, 1, 1, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(-1.5, 0.5, -0.5), thinkness, 1, 1, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(-0.5, 0.5, 1.5), thinkness, 1, 1, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(-0.5, 0.5, -1.5), thinkness, 1, 1, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(0.5, 0.5, -2), thinkness, 1, 2, Color(0.0, 1.0, 1.0)));
	vecWalls.push_back(Box(Position(0, 0, 0), Position(0.5, 0.5, 1.5), thinkness, 1, 3, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(1.5, 0.5, 0), thinkness, 1, 4, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(2.5, 0.5, 2), thinkness, 1, 2, Color(0.0, 1.0, 1.0)));

	vecWalls.push_back(Box(Position(0, 0, 0), Position(3.5, 0.5, 0), thinkness, 1, 6, Color(0.0, 1.0, 1.0)));
}

void renderBitmapString(float x, float y, float z, void* font, const char* string)
{
	const char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void init ()
{
	glClearColor (1.0, 1.0, 1.0, 0.0);	// set display-window color to white
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);

	srand(time(0));

	start = std::clock();
	
}

void reshape (int width, int height)
{
	::width = width;
	::height = height;

	glViewport (0, 0, width, height);

	glMatrixMode (GL_PROJECTION);		// set projection parameters
	glLoadIdentity ();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

	glMatrixMode (GL_MODELVIEW);		// set projection parameters
	glLoadIdentity ();
}

void display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear display window
	glLoadIdentity();
	if (width == 0.0 || height == 0.0)
		return;
	if(!bWin)
	{
		bool meh = false;
		Position targetoldpos;
		targetoldpos.x=target.posStart.x;
		targetoldpos.z=target.posStart.z;
		if((long long)duration%5000==0 && duration )
		{	
			while(meh == false)
			{
				
				int count = 0;
				target.posStart.x=rand()%9;
				target.posStart.z=rand()%9;
				

				for(int i=0;i<numWalls;i++)
					if(target.Insersection(vecWalls[i]) == false)
						count++;

				if(count==numWalls)
				{
					if(target.Insersection(fr))
						if(target.posStart.x!=targetoldpos.x&&target.posStart.z!=targetoldpos.z)
					{
						target.Draw();
						meh = true;
						duration = 0;
					}
						else
							meh=false;
					else
						meh=false;
			}
				else
					meh=false;
		}
	}
		
		
		duration=(std::clock()-start);
}
	
	
	//TODO // update the timer
	std::string str = "Duration:" + std::to_string((long long)(duration / CLOCKS_PER_SEC)%5) + ":" + std::to_string((long long)(duration / 10) % 100);
	renderBitmapString(2.5, 3.8, 0.2, GLUT_BITMAP_TIMES_ROMAN_24, str.c_str());
	
	if (bWin)
	{
		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(-2, 2.5, 0);
			glVertex3f(2.2, 2.5, 0);
			glVertex3f(2.2, 4.5, 0);
			glVertex3f(-2, 4.5, 0);
		glEnd();
		glColor3f(0, 0, 0);
		glLineWidth(3);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-2, 2.5, 0);
			glVertex3f(2.2, 2.5, 0);
			glVertex3f(2.2, 4.5, 0);
			glVertex3f(-2, 4.5, 0);
		glEnd();
		renderBitmapString(-2, 3.5, 0.2, GLUT_BITMAP_TIMES_ROMAN_24, "Congraulations, you win!");
	}

	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	

	// Draw arrow pointing into +X
	glColor3f(1, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(-4, 0, 4);
	glVertex3f(4, 0, 4);

	glVertex3f(4, 0, 4);
	glVertex3f(3.8, 0.2, 4);

	glVertex3f(4, 0, 4);
	glVertex3f(3.8, -0.2, 4);
	glEnd();
	renderBitmapString(4.1, 0, 4, GLUT_BITMAP_TIMES_ROMAN_24, "+X");

	// Draw arrow pointing into +Z
	glColor3f(0, 0, 1);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(-4, 0, 4);
	glVertex3f(-4, 0, -4);

	glVertex3f(-4, 0, -4);
	glVertex3f(-4, 0.2, -3.8);

	glVertex3f(-4, 0, -4);
	glVertex3f(-4, -0.2, -3.8);
	glEnd();
	renderBitmapString(-4.1, 0, -4, GLUT_BITMAP_TIMES_ROMAN_24, "-Z");

	// Draw floor
	flr.Draw();

	// Draw walls
	for (int i = 0; i < numWalls; ++i) 
	{
		vecWalls[i].Draw();
		vecWalls[i].Move();
		
	}
			
	
	// Draw player
	player.Draw();

	target.Draw();

	
	glutSwapBuffers();
	glFlush ();			// process all openGl routines as quickly as possible
}

void processSpecialKeys(int key, int x, int y)
{
	if(!bWin){
	Position playerOldPosition = player.posStart;
	
	if (key == GLUT_KEY_UP)
	{
		player.posStart.z -= step;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		player.posStart.z += step;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		player.posStart.x -= step;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		player.posStart.x += step;
	}

	// if player hits any wall don't allow motion
	if(player.Insersection(fr)==false)
	player.posStart = playerOldPosition;
	for (unsigned i = 0; i < numWalls; ++i)
	{
		if (player.Insersection(vecWalls[i]))
		{
			
			player.posStart = playerOldPosition;
			break;
		}
		
	}

	// if player hits target box
	if (player.Insersection(target))
		bWin = true;

	glutPostRedisplay();}

}
void processNormalKeys (unsigned char key, int x, int y) 
{
	if (key == 'w' || key == 'W')
	{
		xRot += 2.0;;
	}
	else if (key == 'z' || key == 'Z')
	{
		xRot -= 2.0;
	}
	else if (key == 'd' || key == 'D')
	{
		yRot += 2.0;
	}
	else if (key == 'a' || key == 'A')
	{
		yRot -= 2.0;
	}
	else if (key == 'p' || key == 'P')
	{
		if(numWalls<25)
		numWalls++;
		
	}
	else if(key=='r'|| key=='R')
	{
		
		bWin=false;
		
		player.posStart.x=-2.5;
		
		player.posStart.z=-1.5;
		
		while((long long)(duration/CLOCKS_PER_SEC)%5||(long long)(duration/10)%100)
			duration++;

		numWalls=0;
	}
	else if (key == 27)
		exit(0);
	
}

void main (int argc, char** argv)
{

	glutInit (&argc, argv);							// initialize GLUT
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);	// set display mode
	glutInitWindowPosition (20, 20);		// set top left display window position
	glutInitWindowSize (600, 600);			// set display window width and height
	glutCreateWindow ("OpenGL - Homework 2");	// create display window

	buildMaze();
	init ();								// execute initialization function
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc (processNormalKeys);
	glutReshapeFunc (reshape);
	glutDisplayFunc (display);				// send graphics to display window
	glutIdleFunc (display);
	glutMainLoop ();						// dispaly everthing and wait
}