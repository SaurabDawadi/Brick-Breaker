#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>


/*some macros */
#define TEXTX 500
#define TEXTY 200
#define FONT_SIZE 3
#define LEFT -100
#define RIGHT 100
#define WIDTH 1600
#define HEIGHT 700
#define FREQ 2500

int blength=100;
int bthick=40;

/*border*/
typedef struct{
    char Name[90];
    long score;


}data;

typedef struct{
    int inih,inik;//ini means initial
    int r,h,k;
    int vx,vy;

}ball;
typedef struct{
    int len;
    int thick;
    int inipos;
    int curpos;//current postion
}launcher;
struct brick{
    int flag;
}s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
float TIME;
int RX1=100,RY1=50,RX2=1100,RY2=650;
int current=0;

/*prototype */
void mainscreen(void);
void makebricks(void);
int brickdelete(int);
int changeKicker(int,int,int,int);
void drawKicker(int,int ,int);
void moveBall(int,int ,int ,int ,int);
void drawBall(int ,int ,int );
void deleteKicker(int,int,int);
void deleteBall(int,int,int);
void gameMenu(void);
void levelScreen(void);
void instructions(void);
void playerDetail(void);
void gameScreen(void);
int  points_gain(int);
void gameover(void);
int decide_brick(int,int,int);
int decide_point(int,int);





int firstscreen()
{   initwindow(WIDTH,HEIGHT,"Brick  breaker");
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(10,50,10);
    int x=getmaxx()/2;
    int y=getmaxy()/2;
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,6);
    outtextxy(x-250,y-200,(char *)"***BRICK BREAKER***");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
    outtextxy(x-260,y-100,(char *)"********Created By********");
    outtextxy(x-160,y-30,(char *)"Roshan Neupane");
    outtextxy(x-160,y+5,(char *)"Sagar Thapa");
    outtextxy(x-160,y+40,(char *)"Saroj Baral");
    outtextxy(x-160,y+75,(char *)"Saurab Dawadi");
    setlinestyle(1,1,5);
    rectangle(x-500,y-200,x+500,y+200);
    setlinestyle(1,1,10);
    rectangle(x-515,y-215,x+515,y+215);
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(x-500,y+270,(char *)"Our Game is About to Begin...");
    // outtextxy(x-500,y+300,(char *)"Player!! Please Enter your name:");//casted to get rid of error:deprecated conversion
    delay(100);
    getch();
	return 0;
}



int main(){
    int brick=0;
    int points=0;
    TIME=10;
    char ch;
    data player;

//launcher properties
    launcher l;
    l.len=100;
    l.thick=20;
    l.inipos=500;



    /*BALL properties*/
    ball b;
    b.r=10;
    b.inih =(RX2-RX1+l.len)/2;
    b.inik = RY2-l.thick-b.r;
    b.vx = 5;
    b.vy = 5;
    firstscreen();
    initwindow(WIDTH,HEIGHT,"Brick  breaker");
    mainscreen();
    //settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    //outtextxy(TEXTX,TEXTY,(char *)"Enter your name");//casted to get rid of error:deprecated conversion
    getch();

   // gets(player.Name);
    gameMenu();
    cleardevice();
    mainscreen();

    s1.flag=0;
    s2.flag=0;
    s3.flag=0;
    s4.flag=0;
    s5.flag=0;
    s6.flag=0;
    s7.flag=0;
    s8.flag=0;
    s9.flag=0;
    s10.flag=0;



    /*game starts */


    gameScreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
   setcolor(YELLOW);
    outtext((char *)"Press any key to start!!!!");
    getch();
    mainscreen();
    gameScreen();
    drawBall(b.inih,b.inik,b.r);
    drawKicker(l.inipos,l.thick,l.len);
    l.curpos=l.inipos;
    b.h=b.inih;
    b.k=b.inik;
    setcolor(RED);
   // rectangle(300,100,1000,200);
    makebricks();
    while(1){
            points_gain(points);
            delay(TIME);
        /*ball at bound */
        if(b.k<(RY2+10)){
        if(b.h>=RX2-b.r || b.h<=RX1+5+b.r){
            Beep(FREQ,TIME);    //5 is added for boundary effect
            b.vx=b.vx*(-1);

        }
        if (b.h>=l.curpos-13 && b.h<=l.curpos+l.len+13){
        if(b.k>=(RY2-b.r-l.thick)){
            Beep(FREQ,TIME);
            b.vy=b.vy*(-1);

        }
        }
         if (b.k>=RY2-l.thick-2 && b.k<=RY2 ){
        if((b.h>=(l.curpos-b.r-3) && b.h<=(l.curpos)) || (b.h<=(l.curpos+b.r+l.len+3) && b.h>=(l.curpos+l.len))){
           Beep(FREQ,TIME);
            b.vx=b.vx*(-1);

        }
        }
        if(b.k<=RY1+44+b.r){
             if (b.h<=RX1+blength && s1.flag==0){
                s1.flag=brickdelete(b.h);
                Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h<=RX1+blength && s1.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);
                   //KHALI
                                    }
                        }
             if (b.h>RX1+blength && b.h<=RX1+2*blength && s2.flag==0){
                s2.flag=brickdelete(b.h);
                Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+blength && b.h<=RX1+2*blength && s2.flag==1){
                    if(b.k<=RY1+5+b.r){
                   Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+2*blength && b.h<=RX1+3*blength && s3.flag==0){
                s3.flag=brickdelete(b.h);
                Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+2*blength && b.h<=RX1+3*blength && s3.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+3*blength && b.h<=RX1+4*blength && s4.flag==0){
                s4.flag=brickdelete(b.h);
                Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+3*blength && b.h<=RX1+4*blength && s4.flag==1){
                    if(b.k<=RY1+5+b.r){
                   Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
           if (b.h>RX1+4*blength && b.h<=RX1+5*blength && s5.flag==0){
                s5.flag=brickdelete(b.h);
                Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+4*blength && b.h<=RX1+5*blength && s5.flag==1){
                    if(b.k<=RY1+5+b.r){
                      Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+5*blength && b.h<=RX1+6*blength && s6.flag==0){
                s6.flag=brickdelete(b.h);
                  Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+5*blength && b.h<=RX1+6*blength && s6.flag==1){
                    if(b.k<=RY1+5+b.r){
                      Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+6*blength && b.h<=RX1+7*blength && s7.flag==0){
                s7.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+6*blength && b.h<=RX1+7*blength && s7.flag==1) {
                    if(b.k<=RY1+5+b.r){
                      Beep(FREQ,TIME);
                      b.vy=b.vy*(-1);


                                    }
                        }
            if (b.h>RX1+7*blength && b.h<=RX1+8*blength && s8.flag==0){
                s8.flag=brickdelete(b.h);
                 Beep(FREQ,TIME);
                 b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+7*blength && b.h<=RX1+8*blength && s8.flag==1){
                    if(b.k<=RY1+5+b.r){
                     Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+8*blength && b.h<=RX1+9*blength && s9.flag==0){
                s9.flag=brickdelete(b.h);
                  Beep(FREQ,TIME);
                b.vy=b.vy*(-1);

                points+=100;
                }else if(b.h>RX1+8*blength && b.h<=RX1+9*blength && s9.flag==1) {
                    if(b.k<=RY1+5+b.r){
                      Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
            if (b.h>RX1+9*blength && b.h<=RX1+10*blength && s10.flag==0){
                s10.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if (b.h>RX1+9*blength && b.h<=RX1+10*blength && s10.flag==1){
                    if(b.k<=RY1+5+b.r){
                      Beep(FREQ,TIME);
                    b.vy=b.vy*(-1);

                                    }
                        }
        }
        }else{
            gameover();
        }
        b.h+=b.vx;
        b.k+=b.vy;



        moveBall(b.inih,b.inik,b.h,b.k,b.r);
        b.inih=b.h;
        b.inik=b.k;




        /* kicker */

        fflush(stdin);
        if (l.curpos>RX1 && l.curpos<RX2-l.len){
        if(kbhit()){
            ch=getch();
            switch(ch)
            {
            case 'a' : case 'A':
                l.curpos=changeKicker(l.curpos,LEFT,l.len,l.thick);
                break;

            case 'd': case 'D':
                l.curpos=changeKicker(l.curpos,RIGHT,l.len,l.thick);
                break;
            default:
                break;

            }
        }
        }else{
            deleteKicker(l.curpos,l.thick,l.len);
            if(l.curpos<=RX1){
                l.curpos=RX1+1;
            }
            if(l.curpos>=RX2-l.len){
                l.curpos=RX2-l.len-1;
            }
            drawKicker(l.curpos,l.thick,l.len);
                continue;
        }



}
    return 0;
}
void mainscreen(){

    setfillstyle(SOLID_FILL,BROWN);
    floodfill(10,50,10);


}
void gameScreen(){
    setcolor(YELLOW);
    rectangle(RX1,RY1,RX2,RY2);
}
int brickdelete( int b){
    int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
    int brick=0;
    int x1=RX1+1,y1=RY1+1;
    if(b<=RX1+blength){
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a1=1;
        return a1;
    }else if(b>RX1+blength && b<=RX1+2*blength){
        x1=x1+blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a2=1;
        return a2;
    }else if (b>RX1+2*blength && b<=RX1+3*blength){
         x1=x1+2*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a3=1;
        return a3;
    }else if(b>RX1+3*blength && b<=RX1+4*blength){
        x1=x1+3*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a4=1;
        return a4;
    }else if (b>RX1+4*blength && b<=RX1+5*blength){
         x1=x1+4*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a5=1;
        return a5;
    }else if(b>RX1+5*blength && b<=RX1+6*blength){
        x1=x1+5*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
       a6=1;
        return a6;
    }else if (b>RX1+6*blength && b<=RX1+7*blength){
         x1=x1+6*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a7=1;
        return a7;
    }else if(b>RX1+7*blength && b<=RX1+8*blength){
        x1=x1+7*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a8=8;
        return a8;
    }else if(b>RX1+8*blength && b<=RX1+9*blength){
        x1=x1+8*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a9=1;
        return a9;
    }else if(b>RX1+9*blength && b<=RX1+10*blength){
        x1=x1+9*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a10=1;
        return a10;
    }
    else{
        return 0;
    }
    //return brick;
}
void makebricks(){
    int x1=RX1+1,y1=RY1+1;
    setcolor(RED);
    rectangle(x1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
   x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
}
int  changeKicker(int cur,int dis,int len,int thick){


          deleteKicker(cur,thick,len);
          drawKicker(cur+dis,thick,len);
          return (cur+dis);
}
void drawKicker(int pos,int thick ,int len){
    setcolor(BLACK);
    if(pos>RX1 && pos+len<RX2)
    rectangle(pos,RY2-thick,pos+len,RY2-5);
    return ;


}
void deleteKicker(int pos,int thick,int len){
    setcolor(BROWN);
    if(pos>RX1 && pos+len<RX2)
    rectangle(pos,RY2-thick,pos+len,RY2-5);

}
void drawBall(int h,int k,int r){
    setcolor(BLACK);
    circle(h,k,r);

}
void moveBall(int inih,int inik,int h,int k,int r){
    deleteBall(inih,inik,r);
    setcolor(BLACK);
    drawBall(h,k,r);

}
void deleteBall(int h,int k,int r){
    setcolor(BROWN);
    circle(h,k,r);
}
void gameMenu(){
    cleardevice();
    mainscreen();
    char choice;
      settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,(char *)"1.Start game");
    outtextxy(TEXTX,TEXTY+100,(char *)"2.Select Level");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Instructions");
    outtextxy(TEXTX,TEXTY+3*100, (char *)"4.Quit");
    choice=getch();
    switch(choice){
    case '1':

        return ;
    case '2':
        levelScreen();
        gameMenu();
        break;

    case '3':
        instructions();
        gameMenu();
        break;


    case '4':
        playerDetail();
        gameMenu();
        break;
    case '5':
        outtextxy(500,500,(char *)"QUITTING");
        delay(25);
        exit(0);
    default:
        gameMenu();
        break;
    }

  return ;


}
void levelScreen(){
    cleardevice();
    mainscreen();

    char choice;
      settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,(char *)"1.Easy");
    outtextxy(TEXTX,TEXTY+1*100,(char *)"2.Medium");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Hard");
    choice=getch();
    switch(choice){
    case '1':
        TIME=20;
        return ;
    case '2':
        TIME=10;
        return ;
    case '3':
        TIME=5;
        break;
    default:
        levelScreen();
        return ;

    }
    return ;

}
void  instructions(){
    cleardevice();
    mainscreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(200,200,(char *)"Hit 'A' to move left or 'D' to move right ");
    outtextxy(200,230,(char *)"Press any key to go back");
    getch();
    return;

}

void playerDetail(){
    FILE *fp;
    char d;
   char buffer[1];
    int y=TEXTY;
    cleardevice();
    mainscreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, 1);
    fp=fopen("data.txt","r+");
    if(!fp){
            outtext((char *)"Error");
        return ;
    }
    while(1)
    {
        d=getc(fp);
        if(d==EOF)
           break;
        putc(d,fp);

    }
    fclose(fp);
    getch();
    return;

}
int points_gain(int points){
    char point[11];
    int X,Y;
    X=RX2+10;
    Y=RY1;
    setcolor(WHITE);
    sprintf(point,"%d",points); //converts integer to character string
    outtextxy(X+60,Y+80,point);

    outtextxy(X+60,Y+20,"SCORE");

}
void gameover(void){
   cleardevice();
   mainscreen();
   int i;
   outtextxy((RX2-RX1-100)/3,(RY1+RY2)/2,"GAME OVER !!! PRESS ANY KEY TO RETURN TO EXIT");
   //Beep(FREQ-400,TIME+20); Beep(FREQ-600,TIME+40); Beep(FREQ-300,TIME+20);
   main();

}
