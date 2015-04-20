/*
g++ -o **** *****.cpp -lSDLmain -lSDl -lGL -lSDL_image
*/
// specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
#include "func_draw.cpp"
#include "func_loadtexture.cpp"
#include "func_check_collission.cpp"
#include "func_cs.cpp"
using namespace std ;


//
//start of the program
int main()
 {
 bool isCongrats = false;
 bool isRunning2 = true ;
 bool isRunning = true;
 bool instructions = false;
 int score = 0;
 int score2 = 0;
 int score3 = 0;
 //initialize SDL
 SDL_Init(SDL_INIT_EVERYTHING);
 
 
 //caption of the window
 SDL_WM_SetCaption( " BRICK BREAKERS V.1.0 ",NULL);

 //dimensions of the window
 SDL_SetVideoMode(600,400,32,SDL_OPENGL);

 // the clear colour // background colour precisely
 glClearColor(1,1,1,1); // red,green,blue,alpha
 
 // what portion of screen we use
 glViewport(0,0,600,400);
 
 
 //shader model
 glShadeModel(GL_SMOOTH);
 
 //2d rendering
 glMatrixMode(GL_PROJECTION);
 
 //"save" it
 glLoadIdentity();
 
  // diasable depth checking(coz we dont do any 3d )
 glDisable(GL_DEPTH_TEST);

 //for images
glEnable( GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

 
 //cout << "opengl is running\n" ;
 //cout<< "mainloop has started running\n";
 // Game runs with 60 frames per sec
 
 //handles main loop

 
 // creating brick array
 Brick a[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    a[i][j].x =i*75;
    a[i][j].y =j*40;
    a[i][j].length =70;
    a[i][j].height = 35; }
  }
 
 //counting variables(alive /dead)
 int f[8][5], g[8][5],h[8][5] ;
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    f[i][j] = 0 ;
    h[i][j]= 0 ;
  }
 }

 //logic array for each brick;
 bool brCollide[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    brCollide[i][j] = false ;
  }
 }
 // handling events
 SDL_Event event;
 float myX =300;
 float myY =350;
 float width=100;
 float height=30;
 bool left = false , right= false;
 bool levelup = false;
 bool startscreen = true;
 bool isGameover = false;
 //ball details
 float ballX = 340 ;
 float ballY = 330 ;
 float ballWH = 20;

 float velX = 2.5;
 float velY = -2.5;
 
 float midX=(myX+myX+100)/2;
 float midY=myY;

 float New;

 //insert images
unsigned int pad_texture=0,startscreen_texture = 0,brick_texture=0;
unsigned int ball_texture=0,background_texture= 0,instructions_texture = 0;

pad_texture=loadTexture("paddle1.png");
ball_texture = loadTexture("ball1.png");
instructions_texture = loadTexture("instructions.png");
startscreen_texture = loadTexture("start.png");


background_texture = loadTexture("q.png");
brick_texture = loadTexture("brick1.png");
//std::cout<<pad_texture<<std::endl;
//main game loop

 while (isRunning)
    {
     //INPUT OR EVENT
     while( SDL_PollEvent (&event) )
           {
           //logic that should happen for a certain event
           if(event.type == SDL_QUIT)
                 {
                     isRunning = false;
                 }
           
           if((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE ))
             {
                isRunning = false;
             }
           
           
           
           if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_LEFT)
                {
                      left = true ;
                }
                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                  right = true;
                }
                if(event.key.keysym.sym == SDLK_s)
                {
                  startscreen= false;
                }
               
                if(event.key.keysym.sym == SDLK_i)
                {
                  instructions = true;
                }


               // fun wid background color

                if(event.key.keysym.sym == SDLK_g)
                {
                  glClearColor(0,1,0,0);
                }
                if(event.key.keysym.sym == SDLK_b)
                {
                  glClearColor(0,0,1,0);
                }
                if(event.key.keysym.sym == SDLK_y)
                {
                  glClearColor(1,1,0,0);
                }
            }   
           }
      if (event.type==SDL_KEYUP)
      {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
          left = false;
        }
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
          right= false;
        }
      if(event.key.keysym.sym == SDLK_i)
      {
        instructions = false;
      }
      }

        if(startscreen == false)

        {
        // paddle
        if ( (left == true)&& (myX > 2.5) )
        {
          myX= myX - 7.5;
            
        
        }
        if( (right == true)&& (myX < 497.5 ))
        {
          myX = myX + 7.5;
            
        }
        

         // LOGIC FOR THE BALL MOTION
            ballX += velX;
            ballY += velY;
        
         if(ballX<0 || ballX + ballWH > 600 )
    {
          velX= -velX ;
        }
      if(ballX+ballWH==myX && myY<ballY+ballWH && myY+20>ballY+ballWH){
       velX= -velX;
          }
    if(ballX==myX+width && myY<ballY+ballWH && myY+20>ballY+ballWH){
       velX= -velX;
          }
       if(ballY <0 || (ballY+ballWH == myY && ballX+ballWH > myX && ballX-2 <myX + width  )){
          velY = -velY ;
           
       }
      if(midX<ballX+20&& midX >ballX && midY<ballY+20 && midY>ballY+15)
       {
        velX=0;
        velY=-velY;
       }
    if(ballY+20>myY && ballY+17<myY)
       {New=myX-ballX;
        New=New+40;
        New=New/100;
        velX=New;
    }
         

        if (ballY+ ballWH > myY + 5 ){isRunning = false ; }        
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
                if (validCollision(ballX, ballY,a[i][j].x,a[i][j].y, velY) == true)
                {
                  brCollide[i][j] = true ;
                  if(f[i][j]==0 && (a[i][j].y + 35 == ballY )) {velY= -velY;
                                                              f[i][j] = 1;
                                                              score = score + 5;
                                                            }
                  else if(f[i][j]==0) {velX= -velX;
                                       f[i][j]= 1 ;
                                       score = score + 5 ;
                                     }
                }
                
            }          
        }
        }
        if(startscreen == true)
                {
                  glClearColor(1,0,0,1);

                }
        
        if(startscreen == false){
          glClearColor(1,1,1,1);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // renders to the screen
        //brings up the grid which we drawon
        glPushMatrix();//start phase
        glOrtho(0,600,400,0,-1,1); // set the matrix
        if(startscreen == true )
        {
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,startscreen_texture);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

        }
        if(instructions == true )
        {
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,instructions_texture);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

        }


        if(startscreen == false)
        {
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
              if(brCollide[i][j] == false){
                glColor4ub(255,50,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a[i][j].x,a[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a[i][j].x+a[i][j].length , a[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a[i][j].x+a[i][j].length , a[i][j].y +a[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a[i][j].x , a[i][j].y + a[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);              
              }
            }  
        }

        glColor4ub(0,0,0,255);
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,pad_texture);        

    glBegin(GL_QUADS);
        glTexCoord2d(0,0);glVertex2f(myX,myY);
        glTexCoord2d(1,0);glVertex2f(myX+width,myY);
        glTexCoord2d(1,1);glVertex2f(myX+width,myY+height);
        glTexCoord2d(0,1);glVertex2f(myX,myY+height);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);    
        
        glColor4ub(255,0,0,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ball_texture);  
    glBegin(GL_QUADS);
        
        glTexCoord2d(0,0);glVertex2f(ballX,ballY);
        glTexCoord2d(1,0);glVertex2f(ballX,ballY+ballWH);
        glTexCoord2d(1,1);glVertex2f(ballX+ballWH , ballY+ballWH);
        glTexCoord2d(0,1);glVertex2f(ballX+ballWH,ballY);

        glEnd();
        glDisable(GL_TEXTURE_2D);
        }
        
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,background_texture);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

         if(score == 200)
         {
          isRunning = false;
         }      



        glPopMatrix();//stop phase???
      
        SDL_GL_SwapBuffers();//?????

    }
        
if(isRunning == false && score < 200)
  {
    isGameover = true ;
  }





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(score == 200)
{

    //handles main loop
 bool isRunning2 = true;
 
 // creating brick array
 Brick a2[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    a2[i][j].x =i*75;
    a2[i][j].y =j*40;
    a2[i][j].length =70;
    a2[i][j].height = 35; }
  }
 
 int f2[8][5], g2[8][5],h2[8][5] ;
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    f2[i][j] = 0 ;
    g2[i][j] =0 ;
    h2[i][j]= 0 ;
  }
 }

 //logic array for each brick;
 bool brCollide2[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    brCollide2[i][j] = false ;
  }
 }
 // handling events
 float myX2 =300;
 float myY2 =350;
 float width2=100;
 float height2=30;
 bool left2 = false , right2= false;
 bool levelup2 = false;
 bool startscreen2 = true;
 

 //ball details
 float ballX2 = 340 ;
 float ballY2 = 330 ;
 float ballWH2 = 20;

 float velX2 = 5;
 float velY2 = -5;
 float midX2=(myX2+myX2+100)/2;
 float midY2=myY2;

 float New2;

 //insert images
unsigned int pad_texture2=0,startscreen_texture2 = 0,brick_texture2=0;
unsigned int ball_texture2=0,background_texture2= 0;
unsigned int brick_texture2_1 = 0,brick_texture2_2 = 0 ,brick_texture2_3 = 0;
pad_texture2=loadTexture("paddle1.png");
ball_texture2 = loadTexture("ball1.png");
startscreen_texture2 = loadTexture("levelup.png");
background_texture2 = loadTexture("q.png");
brick_texture2_1 = loadTexture("brick1.png");
brick_texture2_2 = loadTexture("brick2.png");
brick_texture2_3 = loadTexture("brick3.png");
//std::cout<<pad_texture2<<std::endl;
//main game loop

 for(int i=0;i<8;i++){
  for(int j=0;j<8;j++){
    if(i*j%3 == 0) g[i][j] = 1;
    if(i*j%3 == 1) g[i][j] = 2;
    if(i*j%3 == 2) g[i][j] = 3;
  }
 }


 while (isRunning2)
    {
     //INPUT OR EVENT
     while( SDL_PollEvent (&event) )
           {
           //logic that should happen for a certain event
           if(event.type == SDL_QUIT)
                 {
                     isRunning2 = false;
                 }
           
           if((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE ))
             {
                isRunning2 = false;
             }
           
           
           
           if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_LEFT)
                {
                      left2 = true ;
                }
                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                  right2 = true;
                }
                if(event.key.keysym.sym == SDLK_s)
                {
                  startscreen2= false;
                }
               
                


               // fun wid background color

                if(event.key.keysym.sym == SDLK_g)
                {
                  glClearColor(0,1,0,0);
                }
                if(event.key.keysym.sym == SDLK_b)
                {
                  glClearColor(0,0,1,0);
                }
                if(event.key.keysym.sym == SDLK_y)
                {
                  glClearColor(1,1,0,0);
                }
            }   
           }
      if (event.type==SDL_KEYUP)
      {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
          left2 = false;
        }
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
          right2= false;
        }
      }

        if(startscreen2 == false)

        {
        // paddle
        if ( (left2 == true)&& (myX2 > 2.5) )
        {
          myX2= myX2 - 10;
            
        
        }
        if( (right2 == true)&& (myX2 < 497.5 ))
        {
          myX2 = myX2 + 10;
            
        }
        

         // LOGIC FOR THE BALL MOTION
            ballX2 += velX2;
            ballY2 += velY2;
        
         if(ballX2<0 || ballX2 + ballWH2 > 600 )
    {
          velX2= -velX2 ;
        }
      if(ballX2+ballWH2==myX2 && myY2<ballY2+ballWH2 && myY2+20>ballY2+ballWH2){
       velX2 = -velX2;
          }
    if(ballX2==myX2+width2 && myY2<ballY2+ballWH2 && myY2+20>ballY2+ballWH2){
       velX2= -velX2;
          }
       if(ballY2 <0 || (ballY2+ballWH2 == myY2 && ballX2+ballWH2 > myX2 && ballX2-2 <myX2 + width2  )){
          velY2 = -velY2 ;
           
       }
      if(midX2<ballX2+20&& midX2 >ballX2 && midY2<ballY2+20 && midY2>ballY2+15)
       {
        velX2=0;
        velY2=-velY2;
       }
    if(ballY2+20>myY2 && ballY2+17<myY2)
       {New2=myX2-ballX2;
        New2=New2+40;
        New2=New2/100;
        velX2=New2;
    }
        if (ballY2+ ballWH2 > myY2 + 5 ){isRunning2 = false ; }        
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
                if (validCollision(ballX2, ballY2,a2[i][j].x,a2[i][j].y, velY2) == true )
                {
                  if(g[i][j] == 0) 
  {brCollide2[i][j] = true ;}
                  if(f2[i][j]==0 && (a2[i][j].y + 35 == ballY2 )) {velY2= -velY2;
                                                              
                                                              if(g[i][j] ==1 ){
                                                                g[i][j] = 0;
                                                                f2[i][j] = 1; 
                                                          
                                                              }
                                                               if(g[i][j] == 2)
                                                              {
                                                                g[i][j] = 1;
                                                              }
                                                              if(g[i][j] == 3)
                                                              {
                                                                g[i][j] = 2;
                                                              }
                                                              score2 = score2+ 5;
                                                            }
                                            else if(f2[i][j]==0) {velX2= -velX2;
                                                              if(g[i][j] ==1 ){
                                                                g[i][j] = 0;
                                                                f2[i][j] = 1; 
                                                          
                                                              }
                                                               if(g[i][j] == 2)
                                                              {
                                                                g[i][j] = 1;
                                                              }
                                                              if(g[i][j] == 3)
                                                              {
                                                                g[i][j] = 2;
                                                              }
                                                              score2 = score2+ 5;
                                                            }
                }
                
            }          
        }
        }
        if(startscreen2 == true)
                {
                  glClearColor(1,1,1,1);

                }
        
        if(startscreen2 == false){
          glClearColor(1,1,1,1);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // renders to the screen
        //brings up the grid which we drawon
        glPushMatrix();//start phase
        glOrtho(0,600,400,0,-1,1); // set the matrix
        if(startscreen2 == true)
        {
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,startscreen_texture2);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

        }


        if(startscreen2 == false)
        {
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
              if(brCollide2[i][j] == false ){
                 if(g[i][j] == 1)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture2_1); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
                if(g[i][j] == 2)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture2_2); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
                if(g[i][j] == 3)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture2_3); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
              }
            }  
        }

        glColor4ub(0,0,0,255);
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,pad_texture2);        

    glBegin(GL_QUADS);
        glTexCoord2d(0,0);glVertex2f(myX2,myY2);
        glTexCoord2d(1,0);glVertex2f(myX2+width2,myY2);
        glTexCoord2d(1,1);glVertex2f(myX2+width2,myY2+height2);
        glTexCoord2d(0,1);glVertex2f(myX2,myY2+height2);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);    
        
        glColor4ub(255,0,0,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ball_texture2);  
    glBegin(GL_QUADS);
        
        glTexCoord2d(0,0);glVertex2f(ballX2,ballY2);
        glTexCoord2d(1,0);glVertex2f(ballX2,ballY2+ballWH2);
        glTexCoord2d(1,1);glVertex2f(ballX2+ballWH2 , ballY2+ballWH2);
        glTexCoord2d(0,1);glVertex2f(ballX2+ballWH2,ballY2);

        glEnd();
        glDisable(GL_TEXTURE_2D);
        }
        
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,background_texture2);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

         
          if(score2 == 310)
          {
            isRunning2 = false;
            cout << score2 ;
          }  




        glPopMatrix();//stop phase???
      
        SDL_GL_SwapBuffers();//?????

    }


    if(isRunning2== false && score2 < 310)
    {
      isGameover= true;
    }
  }
  cout << endl <<endl<<"level1_score :   "<< score<<endl;
  cout << "level2_score :   "<< score2<<endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(score2 == 310)
{

    //handles main loop
 bool isRunning3 = true , brCollide2[8][5];
 
 // creating brick array
 Brick a2[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    a2[i][j].x =i*75;
    a2[i][j].y =j*40;
    a2[i][j].length =70;
    a2[i][j].height = 35; }
  }
 int f2[8][5];
 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    f2[i][j] = 0 ;
  }
 }


 for(int i=0;i<8;i++){
  for(int j=0;j<5;j++){
    brCollide2[i][j] = false ;
  }
 }
 // handling events
  float myX2 =300;
  float myY2 =350;
  float width2=100;
  float height2=30;
  bool left2 = false , right2= false;
  bool levelup3 = false;
  bool startscreen3 = true;
 

 //ball details
 float ballX2 = 340 ;
 float ballY2 = 330 ;
 float ballWH2 = 20;

 float velX2 = 5;
 float velY2 = -5;
 

 //insert images
unsigned int pad_texture3=0,startscreen_texture3 = 0,brick_texture3=0;
unsigned int ball_texture3=0,background_texture3= 0;
unsigned int brick_texture3_1 = 0,brick_texture3_2 = 0 ,brick_texture3_3 = 0;
pad_texture3=loadTexture("paddle1.png");
ball_texture3 = loadTexture("ball1.png");
startscreen_texture3 = loadTexture("levelup.png");
background_texture3 = loadTexture("q.png");
brick_texture3_1 = loadTexture("brick1.png");
brick_texture3_2 = loadTexture("brick2.png");
brick_texture3_3 = loadTexture("brick3.png");
//std::cout<<pad_texture2<<std::endl;
//main game loop

 for(int i=0;i<8;i++){
  for(int j=0;j<8;j++){
    if(i*j%3 == 0) g[i][j] = 1;
    if(i*j%3 == 1) g[i][j] = 2;
    if(i*j%3 == 2) g[i][j] = 3;
  }
 }


 while (isRunning3)
    {
     //INPUT OR EVENT
     while( SDL_PollEvent (&event) )
           {
           //logic that should happen for a certain event
           if(event.type == SDL_QUIT)
                 {
                     isRunning3 = false;
                 }
           
           if((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE ))
             {
                isRunning3 = false;
             }
           
           
           
           if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_LEFT)
                {
                  left2 = true ;
                }
                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                  right2 = true;
                }
                if(event.key.keysym.sym == SDLK_s)
                {
                  startscreen3= false;
                }
               
                


               // fun wid background color

                if(event.key.keysym.sym == SDLK_g)
                {
                  glClearColor(0,1,0,0);
                }
                if(event.key.keysym.sym == SDLK_b)
                {
                  glClearColor(0,0,1,0);
                }
                if(event.key.keysym.sym == SDLK_y)
                {
                  glClearColor(1,1,0,0);
                }
            }   
           }
      if (event.type==SDL_KEYUP)
      {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
          left2 = false;
        }
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
          right2= false;
        }
      }

        if(startscreen3 == false)

        {
        // paddle
        if ( (left2 == true)&& (myX2 > 2.5) )
        {
          myX2= myX2 - 10;
            
        
        }
        if( (right2 == true)&& (myX2 < 497.5 ))
        {
          myX2 = myX2 + 10;
            
        }
        

         // LOGIC FOR THE BALL MOTION
            ballX2 += velX2;
            ballY2 += velY2;
        
         if(ballX2<0 || ballX2 + ballWH2 > 600 )
    {
          velX2= -velX2 ;
        }
      if(ballX2+ballWH2==myX2 && myY2<ballY2+ballWH2 && myY2+20>ballY2+ballWH2){
       velX2 = -velX2;
          }
    if(ballX2==myX2+width2 && myY2<ballY2+ballWH2 && myY2+20>ballY2+ballWH2){
       velX2= -velX2;
          }
       if(ballY2 <0 || (ballY2+ballWH2 == myY2 && ballX2+ballWH2 > myX2 && ballX2-2 <myX2 + width2  )){
          velY2 = -velY2 ;
           
       }
      
        if (ballY2+ ballWH2 > myY2 + 5 ){isRunning3 = false ; }        
        
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
              if(cs(i,j)== true)
              {
                brCollide[i][j] = true;
              }
            }

          }

        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
                if (validCollision(ballX2, ballY2,a2[i][j].x,a2[i][j].y, velY2) == true && cs(i,j)== false)
                {
                  if(g[i][j] == 0) 
  {brCollide2[i][j] = true ;}
                  if(f2[i][j]==0 && (a2[i][j].y + 35 == ballY2 )) 
                    {velY2= -velY2;
                                                              
                                                             
                    if(g[i][j] ==1 )
                    {
                      g[i][j] = 0;
                      f2[i][j] = 1; 
                                                          
                    }
                   if(g[i][j] == 2)
                    {
                      g[i][j] = 1;
                    }
                   if(g[i][j] == 3)
                    {
                      g[i][j] = 2;
                    }
        score3 = score3+ 5;
                    }
      else if(f2[i][j]==0) 
        {velX2= -velX2;
        if(g[i][j] ==1 )
        {
          g[i][j] = 0;
          f2[i][j] = 1; 
            
        }
        if(g[i][j] == 2)
        {
          g[i][j] = 1;
        }
        if(g[i][j] == 3)
        {
          g[i][j] = 2;
        }
         score3 = score3+ 5;
        }
                }
                
            }          
        }
        }
        if(startscreen3 == true)
                {
                  glClearColor(1,1,1,1);

                }
        
        if(startscreen3 == false){
          glClearColor(1,1,1,1);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // renders to the screen
        //brings up the grid which we drawon
        glPushMatrix();//start phase
        glOrtho(0,600,400,0,-1,1); // set the matrix
        if(startscreen3 == true)
        {
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,startscreen_texture3);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

        }


        if(startscreen3 == false)
        {
        for(int i=0;i<8;i++){
            for(int j=0;j<5;j++){
              if(brCollide2[i][j] == false && cs(i,j)==false){

                 if(g[i][j] == 1)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture3_1); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
                if(g[i][j] == 2)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture3_2); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
                if(g[i][j] == 3)
               {
                glColor4ub(255,255,255,255);
               

                glEnable(GL_TEXTURE_2D);  
                glBindTexture(GL_TEXTURE_2D,brick_texture3_3); 
                

                glBegin(GL_QUADS);
                
                glTexCoord2d(0,0);glVertex2f(a2[i][j].x,a2[i][j].y);
                glTexCoord2d(1,0);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y);
                glTexCoord2d(1,1);glVertex2f(a2[i][j].x+a2[i][j].length , a2[i][j].y +a2[i][j].height );
                glTexCoord2d(0,1);glVertex2f(a2[i][j].x , a2[i][j].y + a2[i][j].height );
                glEnd();    
                
                glDisable(GL_TEXTURE_2D);
                }
              }
            }  
        }

        glColor4ub(0,0,0,255);
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,pad_texture3);        

    glBegin(GL_QUADS);
        glTexCoord2d(0,0);glVertex2f(myX2,myY2);
        glTexCoord2d(1,0);glVertex2f(myX2+width2,myY2);
        glTexCoord2d(1,1);glVertex2f(myX2+width2,myY2+height2);
        glTexCoord2d(0,1);glVertex2f(myX2,myY2+height2);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);    
        
        glColor4ub(255,0,0,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ball_texture3);  
    glBegin(GL_QUADS);
        
        glTexCoord2d(0,0);glVertex2f(ballX2,ballY2);
        glTexCoord2d(1,0);glVertex2f(ballX2,ballY2+ballWH2);
        glTexCoord2d(1,1);glVertex2f(ballX2+ballWH2 , ballY2+ballWH2);
        glTexCoord2d(0,1);glVertex2f(ballX2+ballWH2,ballY2);

        glEnd();
        glDisable(GL_TEXTURE_2D);
        }
        
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,background_texture3);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 

         
          if(score3 == 160)
          {
            isRunning3 = false;
            isCongrats = true ;
          }  




        glPopMatrix();//stop phase???
      
        SDL_GL_SwapBuffers();//?????

    }


    if(isRunning3== false && score3 < 160)
    {
      isGameover= true;
    }
  }
cout<<"level3_score "<<":" << "   "<< score3 <<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isRunning4 = true ;
unsigned int endscreen_texture = 0;
if(isGameover == true || (isRunning == false && score < 20))
{
  endscreen_texture = loadTexture("gameover.png");
}
if(isCongrats == true)
{
endscreen_texture = loadTexture("congrats.png");
}
while (isRunning4)
    {
     //INPUT OR EVENT
     while( SDL_PollEvent (&event) )
           {
           //logic that should happen for a certain event
           if(event.type == SDL_QUIT)
                 {
                     isRunning4 = false;
                 }
           
           if((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE ))
             {
                isRunning4 = false;
             }
            }
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
        // renders to the screen
        //brings up the grid which we drawon
          glPushMatrix();//start phase
          glOrtho(0,600,400,0,-1,1); // set the matrix
          glColor4ub(255,255,255,255);
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,endscreen_texture);
          glBegin(GL_QUADS);
          glTexCoord2d(0,0);glVertex2f(0,0);
          glTexCoord2d(1,0);glVertex2f(600,0);
          glTexCoord2d(1,1);glVertex2f(600,400);
          glTexCoord2d(0,1);glVertex2f(0,400);
          glEnd();
          glDisable(GL_TEXTURE_2D); 
          glPopMatrix();//stop phase???


        
      
        SDL_GL_SwapBuffers();//?????
}

 SDL_Quit();
 cout << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl <<"FINAL SCORE :" << "  " <<  score + score2 + score3 << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl;   
 return 0;
 }


