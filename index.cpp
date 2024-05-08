#include<graphics.h>
#include<conio.h>
#include<vector>
#include<iostream>
using namespace std;
struct sb{
	int x;
	int y;
};

class board{
	public:
		int height;
		int width;
		board(){
			height = 500;
			width = 500;
		}
};
class food{
	public:
		int fx;
		int fy;
};

class snake:public board,public food{
	public:
	int dirx,diry;
	int next;
	static int len;
	struct sb body[50];
	
	snake(){
		dirx=diry=0;
		next = height/25;
		fx = (rand()*next)%width;
		fy = (rand()*next)%height;
	}
	
	void drawBoard();
	void render(int,int);
	void update();
	bool gameOver();
};
int snake::len=0;

//draw board
void snake::drawBoard(){
	setcolor(1);
	rectangle(0,0,width,height);
}

//render the snake
void snake::render(int x,int y){
	//render snake body
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);
	rectangle(x,y,x+next,y+next);
	floodfill(x+3,y+3,GREEN);
	
	// render food
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	rectangle(fx,fy,fx+next,fy+next);
	floodfill(fx+3,fy+3,RED);
	
	//display score
	setcolor(RED);
	settextstyle(1,0,2);
	outtextxy(600,100,"Score : ");
	;
}

//update the snake values
void snake::update(){
	//keyboard event
		if(kbhit())
		switch(getch()){
			case 's': diry = 1; dirx = 0; break;
			case 'd': dirx = 1; diry = 0; break;
			case 'w': diry = -1; dirx = 0; break;
			case 'a': dirx = -1; diry = 0; break;				
		}
	
	// move snake in dirx and diry
	if(dirx == 1){
		body[len].x += next;
		body[len].y += 0;
	}
	else if(dirx == -1){
		body[len].x -= next;
		body[len].y += 0;
	}
	else if(diry==1){
		body[len].x += 0;
		body[len].y += next;
	}
	else if(diry == -1){
		body[len].x += 0;
		body[len].y -= next;
	}
	else{
		dirx = 0;
		diry = 0;
	}
	
	//check if snake eaten food or not
	if(fx == body[len].x && fy == body[len].y){
		++len;
		body[len].x = fx;
		body[len].y = fy;
		cout<<"\nfood eaten...";
		cout<<"\nscore : "<<len*10;
		fx = (rand()*next)%width;
		fy = (rand()*next)%height;
	}
	
}

//game over function
bool snake::gameOver(){
	if(body[len].x<0 || body[len].y<0 || body[len].x>width-next || body[len].y>height-next)
	{
		setcolor(RED);
		settextstyle(1,0,2);
		outtextxy(550,100,"GAME OVER");
		getch();
		return true;	
	}
	
}

//main function
int main()
{
	initwindow(800,800);	
	snake s;
	int i;
	s.body[snake::len].x = 0;
	s.body[snake::len].y = 0;
	s.drawBoard();
	s.render(s.body[snake::len].x,s.body[snake::len].y);
	s.dirx = 1;
	getch();
	
	while(!s.gameOver()){
		cleardevice();
		s.drawBoard();
		s.update();
		s.render(s.body[snake::len].x,s.body[snake::len].y);
		for(i=0;i<snake::len;i++){
			s.render(s.body[i].x,s.body[i].y);
			s.body[i] = s.body[i+1];
			s.render(s.body[i].x,s.body[i].y);
		}
		Sleep(300);
	}
	return 0;
}
