//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//=========================================================================|||
//_________________________________________________________________________|||
//_________________________________________________________________________|||
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Name        : game.cpp                                                  |||
// Modified by : ANAS HAMEED                                               |||
// ROLLNUMBER  : 19I-2008                                                  |||
// Version     :                                                           |||
// Copyright   : (c) Reserved                                              |||
// Description : Basic 2D game of Dodge 'Em...                             |||
//_________________________________________________________________________|||
//_________________________________________________________________________|||
//=========================================================================|||
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int position1=320, position2=29,position3=400,position4=29,score=0,speed1=6,life=3;
int screen=0;
void Mycarmovement();
void ComputerCarmovement();
void Drawfood();
void Displaymanu();
void collision_detection();
void levels();

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
 	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
	
	if(screen==1)
	{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	

	// calling some functions from util.cpp file to help students

	//Square at 400,20 positionn
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
    collision_detection();
	Drawfood();
	// Drawing opponent car
     int  x = position1;                //intial position of cars x-coordinate.
	 int  y = position2;                //intial position of cars y-coordinate
	float width = 15;           //size of oppenent car.
	float height = 10;         // for size of oppenent car.
	float* color = colors[BLUE_VIOLET]; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
		
	//drawing My car	
    glClearColor(1/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	//glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	int    x1= position3; 
	int   y1 = position4;
	float width1=15;
	float height1=10;
	float* color1 = colors[DARK_RED];  
	DrawRoundRect(x1,y1,width1,height1,color1,radius); // bottom left tyre
	DrawRoundRect(x1+width1*3,y1,width1,height1,color1,radius); // bottom right tyre
	DrawRoundRect(x1+width1*3,y1+height1*4,width1,height1,color1,radius); // top right tyre
	DrawRoundRect(x1,y1+height1*4,width1,height1,color1,radius); // top left tyre
	DrawRoundRect(x1, y1+height1*2, width1, height1, color1, radius/2); // body left rect
	DrawRoundRect(x1+width1, y1+height, width1*2, height1*3, color1, radius/2); // body center rect
	DrawRoundRect(x1+width1*3, y1+height1*2, width1, height1, color1, radius/2); // body right rect


	// Drawing Arena
	int gap_turn = 60;
	int sx = 20;
	int sy = -60;
	int swidth = 800/2 - gap_turn/2 ; // half width
	int sheight = 10;
	float *scolor = colors[MIDNIGHT_BLUE];
	DrawRectangle(        sx-15             , sy+70  , swidth , sheight , scolor ) ; // bottom left
	DrawRectangle(sx + swidth + gap_turn+15 , sy+70  , swidth , sheight , scolor ) ; // bottom right
	DrawRectangle(sx + swidth + gap_turn+15 , sy+800 , swidth , sheight , scolor ) ; // top right
	DrawRectangle(        sx-15             , sy+800 , swidth , sheight , scolor ) ; // top left		
	DrawRectangle(sx+swidth*2+gap_turn , sy+sheight+60                  , sheight*2 , swidth*.91 , scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn , sy+sheight+swidth+gap_turn+30  , sheight*2 , swidth*.91 , scolor); // right up
	DrawRectangle(sx-sheight*2         , sy+sheight+swidth+gap_turn+30  , sheight*2 , swidth*.91 , scolor); // left up
	DrawRectangle(sx-sheight*2         , sy+sheight+60                  , sheight*2 , swidth*.91 , scolor); // left down*/
     
     
     
    //drawing of gab rectangle 1
	int sx1 =  120;
	int sy1 =  -60;    
    DrawRectangle(sx1-20                        , sy1+150 , swidth*.7 , sheight , scolor); // bottom left
	DrawRectangle(sx1 + swidth + gap_turn-65    , sy1+150 , swidth*.7 , sheight , scolor); // bottom right
	DrawRectangle(sx1 + swidth + gap_turn-65    , sy1+700 , swidth*.7 , sheight , scolor); // top right
	DrawRectangle(sx1-20                        , sy1+700 , swidth*.7 , sheight , scolor); // top left						
	DrawRectangle(sx1+swidth*2+gap_turn-185 , sy1+sheight+swidth+gap_turn+45 , sheight*1.2 , swidth*.61     , scolor); // right up
	DrawRectangle(sx1-sheight*2           , sy1+sheight+swidth+gap_turn+45 , sheight*1.2 , swidth*.61     , scolor); // left up			
	DrawRectangle(sx1+swidth*2+gap_turn-185 , sy1+sheight+140                , sheight*1.2 , swidth*.61+20  , scolor); // right down
	DrawRectangle(sx1-sheight*2             , sy1+sheight+140                , sheight*1.2 , swidth*.61+20  , scolor); // left down

		
	//drawing of gab rectangle 2
	int sx2 =  50 ;
	int sy2 =  -10 ;	
    DrawRectangle(sx2+140                       , sy2+190 , swidth*.45 , sheight , scolor); // bottom left
	DrawRectangle(sx2 + swidth + gap_turn+5    , sy2+190 , swidth*.45 , sheight , scolor); // bottom right	
	DrawRectangle(sx2 + swidth + gap_turn+5    , sy2+555 , swidth*.45 , sheight , scolor); // top right
	DrawRectangle(sx2+140                       , sy2+555 , swidth*.45 , sheight , scolor); // top left				
	DrawRectangle(sx2+swidth*2+gap_turn-210  , sy2+sheight+swidth+gap_turn-10 , sheight*1.2 , swidth*.36  , scolor); // right up
	DrawRectangle(sx2-sheight*2+160          , sy2+sheight+swidth+gap_turn-10 , sheight*1.2 , swidth*.36  , scolor); // left up			
	DrawRectangle(sx2+swidth*2+gap_turn-210  , sy2+sheight+180                , sheight*1.2 , swidth*.36+10  , scolor); // right down
	DrawRectangle(sx2-sheight*2+160          , sy2+sheight+180                , sheight*1.2 , swidth*.36+10  , scolor); // left down


    //drawing of gab rectangle 3
	int sx3 =  -40 ;
	int sy3 =  80  ;	
    DrawRectangle(sx3+330                        , sy3+190   , swidth*.19   , sheight , scolor);          //   BOTTOM LEFT 
    DrawRectangle(sx3 + 2*swidth + gap_turn-275  , sy3+190   , swidth*.19   , sheight , scolor);          //   bottom RIGHT
    DrawRectangle(sx3+330                        , sy3+380   , swidth*.19   , sheight , scolor);          //   top left
	DrawRectangle(sx3+2*swidth + gap_turn-275    , sy3+380   , swidth*.19   , sheight , scolor);          //   top right
	
    DrawRectangle(sx3+2*swidth+gap_turn-215      , sy3+ 335   ,   sheight*1.2 , swidth*.14  , scolor);    //   right up
    DrawRectangle(sx3+2*swidth + gap_turn-215    , sy3+ 190   ,   sheight*1.2 , swidth*.14  , scolor);    //   right down     	
	
	DrawRectangle(sx3+2*swidth+gap_turn-470      , sy3+ 335   ,   sheight*1.2 , swidth*.14  , scolor);    //   left up
    DrawRectangle(sx3 + 2*swidth + gap_turn-470  , sy3+ 190   ,   sheight*1.2 , swidth*.14  , scolor);   //   bottom down
	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}
     else if(screen==0)
     Displaymanu();
     else if(screen==2)
     Displaymanu();
     else if(screen==3)
     Displaymanu();
   
   
    glutPostRedisplay();  
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the

 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	  cout<<"X_coordinate= "<<position1<<"      "<<"Y_coordinate= "<<position2<<endl; 
	  
	  //for horizontal movement.
       int X_Min_Max[7][2]={{32,122},{122,218},{218,308},{308,476},{476,566},{566,662},{662,752}};
      //for vertical   movement.
       int Y_Min_Max[7][2]={{29,113},{113,203},{203,287},{287,401},{401,479},{479,569},{569,665}};
     
     
     
      for(int i=0;i<7; i++)
	  {
	  if (key== GLUT_KEY_UP)
	  {
	            if(position1>=340 && position1<=440 && position2==Y_Min_Max[i][0]) 
	            {
	            position2=Y_Min_Max[i][1];
	            break;
	            }
	  }
	 else if (key== GLUT_KEY_DOWN) 
     {
                if(position1>=340 && position1<=440 && position2==Y_Min_Max[i][1]) 
	            {
	            position2=Y_Min_Max[i][0];
	            break;
	            }
	 }
	 
	 else if (key== GLUT_KEY_RIGHT) 	
  	 {
  	            if(position2>=311 && position2<=413 && position1==X_Min_Max[i][0]) 
	           {
	            position1= X_Min_Max[i][1];
	            break;
	           }
     }
     else if (key== GLUT_KEY_LEFT)
	 {  
	            if(position2>=311 && position2<=413 && position1==X_Min_Max[i][1])          
                {
                position1=X_Min_Max[i][0];
                break;
                }
	 }   
	 }
	 /* else if (key== GLUT_KEY_LEFT GLUT_KEY_UP is constant and contains ASCII for up arrow key) {*/
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();

}

void collision_detection()
{
//bool y=(position2==position4);
//bool x=(position1==position3);
if (((position1>=position3-20 && position1<=position3+50)) && ((position2>=position4-20 && position2<=position4+50) ) )
{
 position1=320;
 position2=29;
 position3=400;
 position4=29;
 life--;
 }
 string X=Num2Str(life);
 	DrawString( 700, 800, "Life=", colors[MISTY_ROSE]);
 	DrawString( 770, 800,   X    , colors[MISTY_ROSE]);
 	if(life==0)
 	{
     screen=3;
     GameDisplay();
     glutPostRedisplay();
    }

}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
 void Displaymanu()
{
	//glClearColor(0/*Red Component*/, 0.4,	//148.0/255/*Green Component*/,
			//0.4/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClearColor( 0.1, 0.8,0.4, 0.6);
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	if(screen==0)
	{
	int gap_turn = 0;
	int sx = 20;
	int sy = -60;
	int swidth = 800/2 - gap_turn/2 ; // half width
	int sheight = 10;
	float *scolor = colors[DARK_RED];
	DrawRectangle(        sx-15             , sy+60  , swidth*10 , sheight*2 , scolor ) ; // bottom left
	DrawRectangle(sx + swidth + gap_turn+15 , sy+60  , swidth*10 , sheight*2 , scolor ) ; // bottom right
	DrawRectangle(sx + swidth + gap_turn+15 , sy+881 , swidth*10 , sheight*2 , scolor ) ; // top right
	DrawRectangle(        sx-15             , sy+881 , swidth*10 , sheight*2 , scolor ) ; // top left		
	DrawRectangle(sx+swidth*2+gap_turn+10 , sy+sheight+61                  , sheight*2 , swidth*10 , scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn+10 , sy+sheight+swidth+gap_turn+61  , sheight*2 , swidth*10 , scolor); // right up
	DrawRectangle(sx-sheight*2         , sy+sheight+swidth+gap_turn+30  , sheight*2 , swidth*10 , scolor); // left up
	DrawRectangle(sx-sheight*2         , sy+sheight+60                  , sheight*2 , swidth*10 , scolor); // left down*/
     
	
	
   DrawString( 150 , 570 , "1) START NEW GAME", colors[BLACK]);
   DrawString( 150 , 540 , "2) GUIDELINE TO PLAY", colors[BLACK]); 
   DrawString( 150 , 510 , "3)  PAUSE", colors[BLACK]);
   DrawString( 150 , 480 , "4) RESUME", colors[BLACK]);
   DrawString( 150 , 450 , "5) SEE HIGHSCORE ", colors[BLACK]);
   DrawString( 150 , 420 , "6) EXIT", colors[BLACK]);
   
   
   DrawString( 150 , 360 , " DODGE     E'M      ATARI    2600 ", colors[WHITE]);
   
   DrawString( 500 , 570 , " PRESS      S   ", colors[BLACK]);
   DrawString( 500 , 540 , " PRESS      U   ", colors[BLACK]);
   DrawString( 500 , 510 , " PRESS      P   ", colors[BLACK]);
   DrawString( 500 , 480 , " PRESS      R   ", colors[BLACK]);
   DrawString( 500 , 450 , " PRESS      H   ", colors[BLACK]);
   DrawString( 500 , 420 , " PRESS      E   ", colors[BLACK]);
   }
    else if(screen==2)
    {
    glClearColor( 1, 1 , 1 ,  1 );//SET THE SCREEN COLOUR
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	DrawString( 150,690, "USER GUIDELINE:                          ", colors[DARK_RED]);
	DrawString( 150,660, "MOVEMENT                               ", colors[DARK_RED]);  
    DrawString( 150,600, "1)PRESS LEFT  ARROW  KEY TO MOVE LEFT    ", colors[BLACK]);
    DrawString( 150,570, "2)PRESS RIGHT ARROW KEY TO MOVE RIGHT    ", colors[BLACK]);
    DrawString( 150,540, "3)PRESS UP  ARROW KEY TO MOVE UP SIDE    ", colors[BLACK]);
    DrawString( 150,510, "4)PRESS DOWN ARROW KEY TO MOVE DOWN SIDE ", colors[BLACK]);
    DrawString( 150,450, " ABOUT GAME      ", colors[DARK_RED]);  
    DrawString( 150,420, "This game have four levels:          ", colors[BLACK]); 
    DrawString( 150,390, "Collect all gift boxes to level up  ", colors[BLACK]);
    DrawString( 150,330, "HIDDEN CODE:                          ", colors[DARK_RED]);  
    DrawString( 150,270, "PRESS SPACE TO DOUBLE THE SPEED OF PLAYER CAR         ", colors[BLACK]); 
    DrawString( 150,240, "PRESS M TO SLOW  DOWN THE SPEED OF PLAYER CAR        ", colors[BLACK]);   
    DrawString( 150,210, "LEFT  CLICK MOUSE TO START THE GAME         ", colors[BLACK]);   
    DrawString( 150,180, "PIGHT CLICK MOUSE TO PAUSE  THE GAME          ", colors[BLACK]); 
    DrawString( 150,130, "PRESS B TO GO BACK                      ", colors[DARK_RED]);
    }
    else if(screen==3)
    {
    glClearColor( 0 , 0 , 0 ,  0 );//SET THE SCREEN COLOUR
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
    DrawString( 250 , 360 , " G A M E      O V E R           ", colors[WHITE]);
    DrawString( 250 , 330 , " press 's' to continue          ", colors[DARK_RED]);
    DrawString( 250 , 300 , " press 'e' to exit              ", colors[DARK_RED]);
    }
      glutSwapBuffers(); 
} 
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}   
   else if(key=='s' || key=='S')
        {
         screen=1;
         life=3;
         glutPostRedisplay();
        }   
        else if(key=='P' || key=='p')
             {
             screen=0;
             Displaymanu(); 
             } 
             else if(key=='r' || key=='R')
                  {
                  screen=1;
                  GameDisplay();
                  glutPostRedisplay();
                  }
                  else if(key=='U' || key=='u')    
                       {
                       screen=2;
                       Displaymanu();
                       }
                       else if (key == 'b' || key == 'B')
	                        {
	                        screen=0;
                            Displaymanu();
                            }
                            else if(key=='e' || key=='E')
                            exit (1);
                                 else if( key== 32 )
                                {
                                 speed1*=2;
                                 Mycarmovement();
                                 glutPostRedisplay();
                                }                                
                                       else if(key=='M'|| key=='m')
                                       {
                                       speed1/=2;                                     
                                       Mycarmovement();
                                       glutPostRedisplay();
                                       }
glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS	
	 glutTimerFunc(10, Timer, 0);
    if(screen==1)
       {
        Mycarmovement();
	    ComputerCarmovement();	
        glutPostRedisplay();
       }
 glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout <<"x-coordinate=" <<x<< "  " <<"Y-coordinate="<<y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		    screen=1;
		    

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			screen=0;

	}
	glutPostRedisplay();//this function is call

}
void ComputerCarmovement()
{
//for horizontal movement.
int X_Min_Max[4][2]={{28,754},{124,664},{214,568},{310,478}};
//for vertical   movement.
int Y_Min_Max[4][2]={{29,665},{113,569},{203,479},{287,401}};
int  gap_turn[2]={340,440};
srand(time(0));
bool x=rand()%2;
static int check=0;

  for(int i=0; i<4;  i++)
 {
         if(position4>=Y_Min_Max[i][0] && position3==X_Min_Max[i][1])
          {
           if(position4<Y_Min_Max[i][1])
           position4+=6;
          }
          
         if(position3> gap_turn[0] && position3< gap_turn[1])
         {
                 if(position4==Y_Min_Max[i][1]  && i<3)
                  {
                               if(check==0 && x )
               				   {
                			   position4=Y_Min_Max[i+1][1];
                 			   position3=340;
               			       check++; 
                 			   x=rand()%2;
               				   }
            			       else if (check==1 && x)
             			       {
             			       position4=Y_Min_Max[i+1][1];
            			       position3=340;
              			       check++;
              			       x=rand()%2;
                               }                 
               			       else if(check==2 && x)
                               {
             			       position4=Y_Min_Max[i+1][1];
                               position3=340;
                               check++;
                               x=rand()%2;
                 			   }	  
                 }
           }
          if(position3> gap_turn[0] && position3< gap_turn[1])
          {
                         if(position4==Y_Min_Max[i][0]  && i>0 )
                        {
                               if(check==3 && x)
               				   {
                			   position4=Y_Min_Max[i-1][0];
                 			   position3=442;
               			       check--;  
                 			   x=rand()%2;
               				   }
            			       else if (check==2 && x)
             			       {
             			       position4=Y_Min_Max[i-1][0];
            			       position3=442;
              			       check--;
              			       x=rand()%2;
                               }                 
               			       else if(check==1 && x)
                              {
             			       position4=Y_Min_Max[i-1][0];
                               position3=442;
                               check--;
                               x=rand()%2;
                 			  }
                 	    }
         }
          
         
         
         if(position4<=Y_Min_Max[i][1] && position3==X_Min_Max[i][0] )          
           {
           if(position4>Y_Min_Max[i][0])
           position4-=6;
           }
 
 
         if(position3>=X_Min_Max[i][0] && position4==Y_Min_Max[i][0])
           {              
            if(position3<X_Min_Max[i][1])
            position3+=6;
           }
    
        if(position3<=X_Min_Max[i][1] && position4==Y_Min_Max[i][1])
           {
            if(position3>X_Min_Max[i][0])
            position3-=6;
           }         
  }
glutPostRedisplay();
}
void Mycarmovement()
{
//for horizontal movement.
int X_Min_Max[4][2]={{32,752},{122,662},{218,566},{308,476}};
//for vertical   movement.
int Y_Min_Max[4][2]={{29,665},{113,569},{203,479},{287,401}};
  for(int i=0;i<4;i++)
 {
       if(position1<=X_Min_Max[i][1] && position2==Y_Min_Max[i][0])
          {              
           if(position1>X_Min_Max[i][0])
           position1-=speed1;
          }
       if( position2>=Y_Min_Max[i][0] && position1==X_Min_Max[i][0])
          {
           if(position2<Y_Min_Max[i][1])
           position2+=speed1;
          }
       if(position1>=X_Min_Max[i][0] && position2==Y_Min_Max[i][1])
          {
           if(position1<X_Min_Max[i][1])
           position1+=speed1;
          }         
       if(position2<=Y_Min_Max[i][1] && position1==X_Min_Max[i][1] )          
         {
          if(position2>Y_Min_Max[i][0])
          position2-=speed1;
         }
  }
  
while(position2>Y_Min_Max[0][1])  
position2--;
glutPostRedisplay();
}
void Drawfood()
// Drawing food in the arena
{  	
	
     static int num1=60,num2=90;
	 int array[800][750];	
	 for(int i=num1 ;i<800 ;i+=num2 )
	 {
	      for(int j=60 ; j<750 ; j+=90)
	      {
	         if(i>=position1 && i<position1+50  && j>position2 && j<position2+50)
	         {
	         array[i][j]=100;  
	         }
	      }
	  }
	  
	  for( int i=60;i<800 ;i+=90 )
	  {
	         for(int j=60 ; j<750 ; j+=90 )
	       {
	         if(array[i][j]==100)
	         {
	         continue;
	         }
	         else
	         	{
	         	DrawCircle(i,j,6,colors[WHITE]);
	         	glutPostRedisplay();
	         	}
	       }
	  }
             
DrawString( 50, 800, "Score=", colors[MISTY_ROSE]);
string X=Num2Str(score);
DrawString(160, 800, X, colors[MISTY_ROSE]);
             static bool flag=true;
             static int check[72];
             if(flag==true)
             {
                   for(int i=0; i<72 ; i++ ) 
                   check[i]=true;
             }
             flag=false;
             /*int y_coordinate[]={29,113,203,287,401,479,569,665};
             for(int j=0; j<8 ; j++ )
              {
                   for(int i=0 ; i<72 ;i++ )
                  {
                   if(check[i]==true)
             		{
             		   if(position1>20 && position1<70 && position2==y_coordinate[j]  )             
             		  {
             		   score++;
              		   check[i]=false;
             		  }
                      else if (position1>110 && position1 <160 && position2==y_coordinate[j] )
              	   	  {
              		  score++;
              		  check[i]=false;
           		      }
            	      else if(position1>200 && position1 <250 && position2==y_coordinate[j] )
             	      {
             	      score++;
             	      check[i]=false;
                      }
                      else if(position1>290 && position1 <340 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      }  
                      else if(position1>380 && position1 <430 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      }  
                      else if(position1>470 && position1 <520 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      } 
                      else if(position1>560 && position1 <610 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      }   
                      else if(position1>650 && position1 <700 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      }  
                      else if(position1>740 && position1 <790 && position2==y_coordinate[j]) 
                      {
                      score++;
                      check[i]=false;
                      }              
                 }             
             }
          break;
         }*/
              
            if(check[0]==true)
             		if(position1>20 && position1<70 && position2==29  )             
             		{
             		score++;
              		check[0]=false;
             		}
             if (check[1]==true)
             		if (position1>110 && position1 <160 && position2==29 )
              		{
              		score++;
              		check[1]=false;
           		    }
             if (check[2]==true)
            	  if(position1>200 && position1 <250 && position2==29 )
             	  {
             	  score++;
             	  check[2]=false;
                  }
             if (check[3]==true)
                   if(position1>290 && position1 <340 && position2==29) 
                   {
                   score++;
                   check[3]=false;
                   }  
             if (check[4]==true)
                   if(position1>380 && position1 <410 && position2==29) 
                   {
                   score++;
                   check[4]=false;
                   }  
             if (check[5]==true)
                   if(position1>470 && position1 <520 && position2==29) 
                   {
                   score++;
                   check[5]=false;
                   } 
             if (check[6]==true)
                   if(position1>560 && position1 <610 && position2==29) 
                   {
                   score++;
                   check[6]=false;
                   }   
             if (check[7]==true)
                   if(position1>650 && position1 <700 && position2==29) 
                   {
                   score++;
                   check[7]=false;
                   }  
             if (check[8]==true)
                   if(position1>720 && position1 <770 && position2==29) 
                   {
                   score++;
                   check[8]=false;
                   } 
              
              if(check[9]==true)
             		if(position1>110 && position1<160 && position2==113 )             
             		{
             		score++;
              		check[9]=false;
             		}
             if (check[10]==true)
             		if (position1>110 && position1 <160 && position2==113 )
              		{
              		score++;
              		check[10]=false;
           		    }
             if (check[11]==true)
            	  if(position1>200 && position1 <250 && position2==113)
             	  {
             	  score++;
             	  check[11]=false;
                  }
             if (check[12]==true)
                   if(position1>290 && position1 <340 && position2==113) 
                   {
                   score++;
                   check[12]=false;
                   }  
             if (check[13]==true)
                   if(position1>380 && position1 <430 && position2==113 ) 
                   {
                   score++;
                   check[13]=false;
                   }  
             if (check[14]==true)
                   if(position1>470 && position1 <520 && position2==113 ) 
                   {
                   score++;
                   check[14]=false;
                   } 
             if (check[15]==true)
                   if(position1>560 && position1 <610 && position2==113 ) 
                   {
                   score++;
                   check[15]=false;
                   }   
             if (check[16]==true)
                   if(position1>650 && position1 <700 && position2==113 ) 
                   {
                   score++;
                   check[16]=false;
                   }  
             if (check[17]==true)
                   if(position1>740 && position1 <790 && position2==113 ) 
                   {
                   score++;
                   check[17]=false;
                   }
             if(check[18]==true)
             		if(position1>20 && position1<70 && position2==203 )             
             		{
             		score++;
              		check[18]=false;
             		}
             if (check[19]==true)
             		if (position1>110 && position1 <160 &&  position2==203 )
              		{
              		score++;
              		check[19]=false;
           		    }
             if (check[20]==true)
            	  if(position1>200 && position1 <250 && position2==203 )
             	  {
             	  score++;
             	  check[20]=false;
                  }
             if (check[21]==true)
                   if(position1>290 && position1 <340 &&  position2==203 ) 
                   {
                   score++;
                   check[21]=false;
                   }  
             if (check[22]==true)
                   if(position1>380 && position1 <430 &&  position2==203 ) 
                   {
                   score++;
                   check[22]=false;
                   }  
             if (check[23]==true)
                   if(position1>470 && position1 <520 &&  position2==203 ) 
                   {
                   score++;
                   check[23]=false;
                   } 
             if (check[24]==true)
                   if(position1>560 && position1 <610 &&  position2==203 ) 
                   {
                   score++;
                   check[24]=false;
                   }   
             if (check[25]==true)
                   if(position1>650 && position1 <700 &&  position2==203 ) 
                   {
                   score++;
                   check[25]=false;
                   }  
             if (check[26]==true)
                   if(position1>740 && position1 <790 &&  position2==203 ) 
                   {
                   score++;
                   check[26]=false;
                   } 
              
              if(check[27]==true)
             		if(position1>20 && position1<70 &&  position2==287  )             
             		{
             		score++;
              		check[27]=false;
             		}
             if (check[28]==true)
             		if (position1>110 && position1 <160 && position2==287 )
              		{
              		score++;
              		check[28]=false;
           		    }
             if (check[29]==true)
            	  if(position1>200 && position1 <250 && position2==287 )
             	  {
             	  score++;
             	  check[29]=false;
                  }
             if (check[30]==true)
                   if(position1>290 && position1 <340 && position2==287 ) 
                   {
                   score++;
                   check[30]=false;
                   }  
             if (check[31]==true)
                   if(position1>380 && position1 <430 && position2==287 ) 
                   {
                   score++;
                   check[31]=false;
                   }  
             if (check[32]==true)
                   if(position1>470 && position1 <520 && position2==287 ) 
                   {
                   score++;
                   check[32]=false;
                   } 
             if (check[33]==true)
                   if(position1>560 && position1 <610 && position2==287 ) 
                   {
                   score++;
                   check[33]=false;
                   }   
             if (check[34]==true)
                   if(position1>650 && position1 <700 && position2==287 ) 
                   {
                   score++;
                   check[34]=false;
                   }  
             if (check[35]==true)
                   if(position1>740 && position1 <790 && position2==287 ) 
                   {
                   score++;
                   check[35]=false;
                   }          
             if(check[36]==true)
             		if(position1>20 && position1<70 && position2==401)             
             		{
             		score++;
              		check[36]=false;
             		}
             if (check[37]==true)
             		if (position1>110 && position1 <160 && position2==401)
              		{
              		score++;
              		check[37]=false;
           		    }
             if (check[38]==true)
            	  if(position1>200 && position1 <250 && position2==401 )
             	  {
             	  score++;
             	  check[38]=false;
                  }
             if (check[39]==true)
                   if(position1>290 && position1 <340 && position2==401 ) 
                   {
                   score++;
                   check[39]=false;
                   }  
             if (check[40]==true)
                   if(position1>380 && position1 <430 && position2==401 ) 
                   {
                   score++;
                   check[40]=false;
                   }  
             if (check[41]==true)
                   if(position1>470 && position1 <520 && position2==401 ) 
                   {
                   score++;
                   check[41]=false;
                   } 
             if (check[42]==true)
                   if(position1>560 && position1 <610 && position2==401 ) 
                   {
                   score++;
                   check[42]=false;
                   }   
             if (check[43]==true)
                   if(position1>650 && position1 <700 && position2==401 ) 
                   {
                   score++;
                   check[43]=false;
                   }  
             if (check[44]==true)
                   if(position1>740 && position1 <790 && position2==401) 
                   {
                   score++;
                   check[44]=false;
                   } 
              
              if(check[45]==true)
             		if(position1>20 && position1<70 && position2==479 )             
             		{
             		score++;
              		check[45]=false;
             		}
             if (check[46]==true)
             		if (position1>110 && position1 <160 && position2==479 )
              		{
              		score++;
              		check[46]=false;
           		    }
             if (check[47]==true)
            	  if(position1>200 && position1 <250 && position2==479)
             	  {
             	  score++;
             	  check[47]=false;
                  }
             if (check[48]==true)
                   if(position1>290 && position1 <340 && position2==479 ) 
                   {
                   score++;
                   check[48]=false;
                   }  
             if (check[49]==true)
                   if(position1>380 && position1 <430 && position2==479 ) 
                   {
                   score++;
                   check[49]=false;
                   }  
             if (check[50]==true)
                   if(position1>470 && position1 <520 && position2==479 ) 
                   {
                   score++;
                   check[50]=false;
                   } 
             if (check[51]==true)
                   if(position1>560 && position1 <610 && position2==479 ) 
                   {
                   score++;
                   check[51]=false;
                   }   
             if (check[52]==true)
                   if(position1>650 && position1 <700 && position2==479 ) 
                   {
                   score++;
                   check[52]=false;
                   }  
             if (check[53]==true)
                   if(position1>740 && position1 <790 && position2==479 ) 
                   {
                   score++;
                   check[53]=false;
                   }
                   
             if(check[54]==true)
             		if(position1>20 && position1<70 && position2==569 )             
             		{
             		score++;
              		check[54]=false;
             		}
             if (check[55]==true)
             		if (position1>110 && position1 <160 && position2==569 )
              		{
              		score++;
              		check[55]=false;
           		    }
             if (check[56]==true)
            	  if(position1>200 && position1 <250 && position2==569 )
             	  {
             	  score++;
             	  check[56]=false;
                  }
             if (check[57]==true)
                   if(position1>290 && position1 <340 && position2==569 ) 
                   {
                   score++;
                   check[57]=false;
                   }  
             if (check[58]==true)
                   if(position1>370 && position1 <420 && position2==569 ) 
                   {
                   score++;
                   check[58]=false;
                   }  
             if (check[59]==true)
                   if(position1>470 && position1 <520 && position2==569 ) 
                   {
                   score++;
                   check[59]=false;
                   } 
             if (check[60]==true)
                   if(position1>560 && position1 <610 && position2==569 ) 
                   {
                   score++;
                   check[60]=false;
                   }   
             if (check[61]==true)
                   if(position1>650 && position1 <700 && position2==569 ) 
                   {
                   score++;
                   check[61]=false;
                   }  
             if (check[62]==true)
                   if(position1>740 && position1 <790 && position2==569 ) 
                   {
                   score++;
                   check[62]=false;
                   } 
              
              if(check[63]==true)
             		if(position1>20 && position1<70 && position2==665 )             
             		{
             		score++;
              		check[63]=false;
             		}
             if (check[64]==true)
             		if (position1>110 && position1<160 && position2==665 )
              		{
              		score++;
              		check[64]=false;
           		    }
             if (check[65]==true)
            	  if(position1>200 && position1<250 && position2==665 )
             	  {
             	  score++;
             	  check[65]=false;
                  }
             if (check[66]==true)
                   if(position1>290 && position1<340 && position2==665  ) 
                   {
                   score++;
                   check[66]=false;
                   }  
             if (check[67]==true)
                   if(position1>380 && position1<430 && position2==665  ) 
                   {
                   score++;
                   check[67]=false;
                   }  
             if (check[68]==true)
                   if(position1>470 && position1<520 && position2==665  ) 
                   {
                   score++;
                   check[68]=false;
                   } 
             if (check[69]==true)
                   if(position1>560 && position1<610 && position2==665  ) 
                   {
                   score++;
                   check[69]=false;
                   }   
             if (check[70]==true)
                   if(position1>650 && position1<700 && position2==665  ) 
                   {
                   score++;
                   check[70]=false;
                   }  
             if (check[71]==true)
                   if(position1>740 && position1<790 && position2==665  ) 
                   {
                   score++;
                   check[71]=false;
                   }
 
 
  static int level=1;             
  DrawString( 400, 800, "Level=", colors[MISTY_ROSE]);
  string Y=Num2Str(level);
  DrawString(500, 800, Y, colors[MISTY_ROSE]); 

if(score==70)
{
screen=1;
num1=55;
num2=90;
flag=true;
position1=320;
position2=29;
position3=400;
position4=29;
level++;
GameDisplay();
glutPostRedisplay();
}
glutPostRedisplay();
}  



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 840, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator....
	glutInit(&argc, argv); // initialize the graphics library....
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels....

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	Displaymanu();	
	glutDisplayFunc(GameDisplay);
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
