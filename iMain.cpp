#include "iGraphics.h"
#include "gl.h"
#include<math.h>
#include<windows.h>

void drw(double a,double b,double c,int amp,float angle);
void drw1(double a1,double b1,double c1,int amp1,float angle1);
void summation(double sum,double a2,int cnt);
void ballchange();

int n,Amp[20],i,inc=1,state[20],R=255,G=255,B=255,visball[20],viscurve[20],c1=20,c2,phase[15],inc1=1,R1=250,G1=250,B1=3;
double ballx[20],bally[20],ballz[20],da[20],ball2x=0,sum2=0,cnt2=0,ball2y=0,da2=1.0;
int clrstate=1,mode=0,ampx[15],ampy[15],dif[15],fy[15],iy[15],px[15],py[15],pdif[15],pfy[15],cb1=255,cb2=255,cb3=255;
int op=0,bmode=0,mball,frex[20],frey[20],ffy[20],t[20],dmode[20];
char str[10];
float fre[20],fdif[20],dc[20];

void iDraw()
{
    iClear();
    if(mode==0)
    {
        iSetColor(25,250,250);
        iText(50,580,"AMPLITUDE MODIFIER : A(INCREASE) AND a(decrease)");
        iText(50,560,"FREQUENCY MODIFIER : F(INCREASE) AND f(decrease)");
        iText(50,540,"PHASE  MODIFIER    : RIGHT ARROW(INCREASE) AND LEFT ARROW(DECREASE)");
        iText(50,520,"BALL SPEED MODIFIER: UP ARROW(INCREASE) AND DOWN ARROW(DECREASE)");
        iText(50,500,"TO PAUSE MOTION    : p");
        iText(50,480,"TO RESUME MOTION   : r");
        iText(50,460,"TOGGLE i-th curve  : i and SHIFT-i");
        iText(50,440,"TO CHANGE COLOR    : USE RGB COLOR PALETTE");
        iText(50,420,"KNOW MODIFICATIONS : SEE MODIFICATIONS OPTION");
        iText(50,400,"TO EXIT            : PRESS END");
        iText(50,150,"PARTICULAR BALL AND CURVE MODIFIERS ARE DIRECTED ON SCREEN.");
        iText(50,130,"YOU ARE REQUESTED TO EXPLORE");
        iText(50,170,"TO ADD A SINE CURVE : PRESS Y");
        iText(50,190,"TO ADD A COS CURVE :PRESS Z");
        iSetColor(255,0,0);
        iText(50,210,"CLICK RIGHT ON YELLOW BALL TO DELETE AND UNDO");
        iSetColor(200,200,0);
        iRectangle(150,300,350,50);
        iSetColor(255,0,0);
        iText(155,320,"CLICK HERE TO SEE THE CURVES");
        //"CLICK HERE SO SEE CURVES");

    }
    if(mode==3)
    {
        iSetColor(2,255,0);
        iRectangle(150,250,600,200);
        iText(170,300,"THANKS FOR WATCHING");
        iRectangle(400,50,100,50);
        iText(450,70,"OK");
    }
     if(mode==1)
    {
        iSetColor(2,255,255);
        iText(10,530,"SPEED TRACKER ON LEFT CLICK");
    iLine(0,300,1000,300);
    if(bmode==1)
    {
        iSetColor(0,255,0);
        iRectangle(150,450,100,40);
        iText(170,460,"INCREASE");
        iSetColor(255,0,0);
        iRectangle(260,450,100,40);
        iText(280,460,"DECREASE");
        iSetColor(255,255,0);
        iRectangle(370,450,100,40);
        iText(390,460,"REVERSE");
    }
    for(i=0;i<n;i++)
    {
        if(state[i]==1)
        {

          if(viscurve[i]==1)
            drw(0,0,0,Amp[i],fre[i]);
        }
        else
        {
           if(viscurve[i]==1)
              drw1(0,0,0,Amp[i],fre[i]);
        }
    }
    for(i=0;i<n;i++)
    {
        iSetColor(255,255,0);
        iFilledCircle(300+i*50,530,5);
        iSetColor(199,250,25);
        iLine(300+i*50,25,300+i*50,60);
        iSetColor(50,255,89);
        iLine(315+i*50,25,315+i*50,60);//lines done
        ampx[i]=300+i*50;
        iSetColor(255,250,89);
        iLine(330+i*50,25,330+i*50,60);
        frex[i]=330+i*50;
        //ampy[i]=25;
        iy[i]=25;
        //frey[i]=25;
    }
    iSetColor(255,255,1);
    iFilledCircle(cb1,20,3);//color ball indiating in palette
    iFilledCircle(cb2,30,3);
    iFilledCircle(cb3,40,3);
    for(i=0;i<n;i++)
    {
        iSetColor(255,8,255);
        iFilledCircle(ampx[i],ampy[i],4);
        iSetColor(255,78,9);
        iFilledCircle(px[i],py[i],4);
        iSetColor(0,255,0);
        iFilledCircle(frex[i],frey[i],4);

    }
    summation(0,0,0);
    iSetColor(255,0,0);
    for(i=0;i<n;i++)
    {
        if(visball[i]==1)
        iFilledCircle(ballx[i],bally[i],4);
    }
    iSetColor(255,0,0);
    iLine(1,20,255,20);
    iSetColor(0,255,0);
    iLine(1,30,255,30);
    iSetColor(0,0,255);
    iLine(1,40,255,40);
    for(i=1;i<=n;i++)
    {
        iSetColor(255,0,0);
        iFilledCircle(i*c1,560,4);
    }
    iSetColor(G1,R1,B1);
    iFilledCircle(ball2x,ball2y,5);
    iSetColor(255,255,10);
    iText(5,50,"RGB COLOR PALATTE");
    iSetColor(10,255,255);
    iText(15,580,"BALL TRACER ON RIGHT CLICK");
    iSetColor(255,8,255);
    iFilledCircle(400,580,5);
    iSetColor(0,255,0);
    iFilledCircle(280,580,5);
    iFilledRectangle(310,560,8,6);
    iSetColor(8,255,250);
    iText(412,580,"AMPLITUDE");
    iText(298,580,"FREQUENCY");
    iText(550,580,"PHASE");
    iSetColor(255,255,0);
    iText(320,558,"PRESS i and SHIFT-i TO TOGGLE i-th CURVE");
    iSetColor(255,50,50);
    iFilledCircle(530,580,5);
    iSetColor(0,255,10);
    iFilledCircle(650,585,4);
    iText(665,580,"MODIFICATIONS :");

    iText(850,580,"PRESS END TO QUIT");
    sprintf(str,"%d",op);
    iText(790,580,str);
    iSetColor(255,0,0);
    iRectangle(900,550,50,20);
    iText(910,555,"BACK");
    iSetColor(255,255,0);
    iFilledCircle(670,560,4);
    iSetColor(255,0,255);
    iText(680,560,"DELETE AND UNDO");

    }
}

void summation(double sum,double a2,int cnt)
{
    for(a2=0;a2<1000;a2+=1)
    {
        for(i=0;i<n;i++)
        {
            if(state[i]==1)
            {
                sum=sum+Amp[i]*sin(((cnt*fre[i]*3.14159)/180)+phase[i]);
            }
            else
                sum=sum+Amp[i]*cos(((cnt*fre[i]*3.14159)/180)+phase[i]);
        }

        sum=sum+300;
        iSetColor(R1,G1,B1);
        iPoint(a2,sum);
        sum=0;
        cnt++;

    }
}
void clrchange()
{
    if(clrstate==1)
    {
        B1=255;
        R1=0;
        G1=0;
        clrstate=2;
    }
    else if(clrstate==2)
    {
        B1=0;
        R1=0;
        G1=255;
        clrstate=3;
    }
    else if(clrstate==3)
    {
        R1=255;
        G1=255;
        B1=0;
        clrstate=4;
    }
    else if(clrstate==4)
    {
        R1=255;
        B1=0;
        G1=0;
        clrstate=5;
    }
    else if(clrstate==5)
    {
        R1=10;
        B1=250;
        G1=255;
        clrstate=6;
    }
    else if(clrstate==6)
    {
        R1=255;
        B1=240;
        G1=90;
        clrstate=7;
    }
    else if(clrstate==7){R1=255;G1=255;B1=51;clrstate=8;}
    else if(clrstate==8){R1=128;G1=255;B1=0;clrstate=1;}

}

void drw(double a,double b,double c,int amp,float angle)
{
    for(a=0;a<1000;a+=1)
    {
        b=amp*sin(((3.14159*c)/180)+phase[i]);
        b=b+300;
        iSetColor(R,G,B);
        iPoint(a,b);
        c=c+angle;
    }
}

void drw1(double a1,double b1,double c1,int amp1,float angle1)
{
    for(a1=0;a1<1000;a1+=1)
    {
        b1=amp1*cos(((3.14159*c1)/180)+phase[i]);
        b1=b1+300;
        iSetColor(R,G,B);
        iPoint(a1,b1);
        c1=c1+angle1;
    }
}
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    if(my>60)
        my=60;
    if(my<25)
        my=25;
    if(mode==1)
    {


    op=op+1;
    for(i=0;i<n;i++)
    {
        if(mx<=(ampx[i]+4)&& mx>=(ampx[i]-4) && my>=(ampy[i]-4)&& my<=(ampy[i]+4))
        {
            fy[i]=my;
            dif[i]=fy[i]-ampy[i];
            dif[i]=dif[i]*2;
            Amp[i]=Amp[i]+dif[i];
            if(Amp[i]>100)
                Amp[i]=100;
            else if(Amp[i]<0)
                Amp[i]=0;
            ampy[i]=fy[i];


        }
        if(mx<=(px[i]+4)&& mx>=(px[i]-4)&& my>=(py[i]-4)&& my<=(py[i]+4))
        {
            pfy[i]=my;
            pdif[i]=pfy[i]-py[i];
            pdif[i]=pdif[i]*2;
            phase[i]=phase[i]+pdif[i];
            py[i]=pfy[i];
        }
        if(mx<=(frex[i]+4) && mx>=(frex[i]-4) && my>=(frey[i]-4) && my<=(frey[i]+4))
        {
            ffy[i]=my;
            fdif[i]=ffy[i]-frey[i];
            //fdif[i]=fdif[i];
            fdif[i]=fdif[i]*0.1;
            frey[i]=my;
            fre[i]=fre[i]+fdif[i];
            dc[i]=fre[i];
            ballx[i]=0;
            ballz[i]=0;
            da[i]=1;
        }

    }
    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{

     if(mode==0)
    {
        if(button== GLUT_LEFT_BUTTON && state==GLUT_DOWN)
            if(mx<=500 && mx>=150 && my<=350 && my>=300)
            {

                op=0;
                mode=1;
            }
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
            op=op+1;
            if(mx<=950 && mx>=900 && my<=570 && my>=550)
            {
                mode=0;
            }
         if(mx>1 && mx<255)
        {
            if(my>=18 && my<=22)
            {
                R=mx;
                cb1=mx;
            }
            if(my>=28 && my<=32)
            {
                G=mx;cb2=mx;
            }
            if(my>=38 && my<=42)
            {
             B=mx;cb3=mx;
            }
        }
   }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        op=op+1;
       if(my>=556 && my<=564)
       {
           for(i=1;i<=n;i++)
           {
               c2=c1*i;
               if(mx<=(c2+4)&& (mx>=(c2-4)))
               {
                  if(visball[i-1]==1)
                    visball[i-1]=0;
                  else
                    visball[i-1]=1;
               }
            }
       }
       if(my>=525 && my<=535)
       {
           for(i=0;i<n;i++)
           {
               if(mx>=(ampx[i]-5)&& mx<=(ampx[i]+5))
               {
                   if(dmode[i]==0)
                   {
                       dmode[i]=1;
                       t[i]=Amp[i];
                       Amp[i]=0;
                       visball[i]=0;
                   }
                   else if(dmode[i]==1)
                   {
                       dmode[i]=0;
                       Amp[i]=t[i];
                       visball[i]=1;
                   }
               }
           }
       }

    }
    //delete till mode 3

     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        op=op+1;
       if(my>=556 && my<=564)
       {
           for(i=1;i<=n;i++)
           {
               c2=c1*i;
               if(mx<=(c2+4)&& (mx>=(c2-4)))
               {
                  bmode=1;
                  mball=i-1;
               }
            }
       }

    }

    if(mode==1 && bmode==1)
    {
        if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        {
            if(mx>=150 && mx<=250 && my<=490 && my>=450)
            {
                da[mball]=da[mball]*2;
                dc[mball]=dc[mball]*2;
                bmode=0;
            }
            if(mx>=260 && mx<=360 && my>=450 && my<=490)
            {
                da[mball]=da[mball]/2;
                dc[mball]=dc[mball]/2;
                bmode=0;
            }
            if(mx>=370 && mx<=470 && my>=450 && my<=490)
            {
                da[mball]=da[mball]*(-1);
                dc[mball]=dc[mball]*(-1);
                bmode=0;
            }
        }
    }

    if(mode==3)
    {
        if(button== GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        if(mx>400 && mx<500 && my<100 & my>50)
            exit(0);
    }

}


void iKeyboard(unsigned char key)
{
    op=op+1;
	if(key == 'p')
	{
		//do something with 'q'
		//iPauseTimer(0);
		iPauseTimer(1);

	}
	if(key == 'r')
	{
		//iResumeTimer(0);
		iResumeTimer(1);
	}
	if(key=='A')
    {
        for(i=0;i<n;i++)
        {
            if(dmode[i]==0)
               Amp[i]=Amp[i]+5;
            if(Amp[i]>100)
                Amp[i]=100;
        }
    }
    if(key=='a')
    {
        for(i=0;i<n;i++)
        {
            if((Amp[i]-5)>=0)
            Amp[i]=Amp[i]-5;
        }
    }
    if(key=='1')
        viscurve[0]=0;
    if(key=='!')
        viscurve[0]=1;
    if(key=='2')
        viscurve[1]=0;
    if(key=='@')
        viscurve[1]=1;
    if(key=='3')
        viscurve[2]=0;
    if(key=='#')
        viscurve[2]=1;
        if(key=='4')
            viscurve[3]=0;
        if(key=='$')
            viscurve[3]=1;
        if(key=='5')
            viscurve[4]=0;
        if(key=='%')
            viscurve[4]=1;
            if(key=='6')
                viscurve[5]=0;
            if(key=='^')
                viscurve[5]=1;
                if(key=='7')
                    viscurve[6]=0;
                if(key=='&') viscurve[6]=1;
                if(key=='8')viscurve[7]=0;
                if(key=='*')viscurve[7]=1;
                if(key=='9')viscurve[8]=0;
                if(key=='(')viscurve[8]=1;
                if(key=='0')viscurve[9]=0;
                if(key==')')viscurve[9]=1;
            //toggle the curves upto


            if(key=='F')
            {
                for(i=0;i<n;i++)
                {
                    fre[i]=fre[i]*1.5;
                    ballx[i]=0;
                    ballz[i]=0;
                    dc[i]=fre[i];
                    da[i]=1;
                }
            }
            if(key=='f')
            {
                for(i=0;i<n;i++)
                {
                    fre[i]=fre[i]*0.5;
                    ballx[i]=0;
                    ballz[i]=0;
                    dc[i]=fre[i];
                    da[i]=1;
                }
            }
            //delete here
            /*if(key=='g')
            {
                fre[0]=fre[0]+1;
                ballx[0]=0;
                ballz[0]=0;
                dc[0]=fre[0];
                da[0]=1;
            }*/




        //toggle the curves

	//place your codes for other keys here
	if(key=='Y')
    {   if(n<10)
      {


        n=n+1;
        viscurve[n-1]=visball[n-1]=1;
        Amp[n-1]=Amp[n-2]+10;
        fre[n-1]=fre[n-2]+1;
        da[n-1]=1;
        dc[n-1]=fre[n-1];
        phase[n-1]=0;
        ballx[n-1]=0;
        ballz[n-1]=0;
        state[n-1]=1;
        frey[n-1]=ampy[n-1]=py[n-1]=25;
        px[n-1]=315+(n-1)*50;
        dmode[n-1]=0;
        t[n-1]=0;
     }
    }
    if(key=='Z')
    {   if(n<10)
    {


         n=n+1;
        viscurve[n-1]=visball[n-1]=1;
        Amp[n-1]=Amp[n-2]+10;
        fre[n-1]=fre[n-2]+1;
        da[n-1]=1;
        dc[n-1]=fre[n-1];
        phase[n-1]=0;
        ballx[n-1]=0;
        ballz[n-1]=0;
        state[n-1]=2;
        frey[n-1]=ampy[n-1]=py[n-1]=25;
        px[n-1]=315+(n-1)*50;
        dmode[n-1]=0;
        t[n-1]=0;
    }
    }

}



void iSpecialKeyboard(unsigned char key)
{

    op=op+1;
    if(key == GLUT_KEY_UP)
    {
        for(i=0;i<n;i++)
        {
            da[i]=da[i]*2;
            dc[i]=dc[i]*2;
        }
    }//will increase velocity of balls
    if(key==GLUT_KEY_DOWN)
    {
        for(i=0;i<n;i++)
        {
            da[i]=da[i]*0.5;
            dc[i]=dc[i]*0.5;
        }
    }
    if(key==GLUT_KEY_RIGHT)
    {
        for(i=0;i<n;i++)
            phase[i]=phase[i]+2;
    }

    if(key==GLUT_KEY_LEFT)
    {
        for(i=0;i<n;i++)
          phase[i]=phase[i]-2;
    }

    if(key==GLUT_KEY_END)
        mode=3;
    //place your codes for
    //place your codes for other keys here
}
void ballchange()
{
    for(i=0;i<n;i++)
    {
        ballx[i]+=da[i];
        ballz[i]+=dc[i];
        if(state[i]==1)
        {
            bally[i]=Amp[i]*sin(((ballz[i]*3.14159)/180)+phase[i]);
            bally[i]+=300;

        }
        else
        {
            bally[i]=Amp[i]*cos(((ballz[i]*3.14159)/180)+phase[i]);
            bally[i]+=300;
        }
        if(ballx[i]>1000 || ballx[i]<0)
        {
            da[i]=da[i]*(-1);
            dc[i]=dc[i]*(-1);
        }
    }//change in the curve balls

    ball2x=ball2x+da2;
        cnt2=cnt2+inc1;

    for(i=0;i<n;i++)
    {
        if(state[i]==1)
            sum2=sum2+Amp[i]*sin(((cnt2*fre[i]*3.14159)/180)+phase[i]);
        else
            sum2=sum2+Amp[i]*cos(((cnt2*fre[i]*3.14159)/180)+phase[i]);

    }
    sum2=sum2+300;
    ball2y=sum2;
    sum2=0;
    if(ball2x>1000 || ball2x<0)
    {


        da2=da2*(-1);
        inc1=inc1*(-1);
    }
}


int main()
{

    printf("HOW MANY CURVES ? (Enter less than 10 to get better feature.)\n");
    scanf("%d",&n);
    printf("ENTER THE AMPLITUDES OF THE CURVES :( ENTER LESS THAN %d)\n",100);
    for(i=0;i<n;i++)
    {
        scanf("%d",&Amp[i]);
        if(Amp[i]>100)
        {
            printf("Enter less than %d\n",100);
            i--;
        }
    }
    for(i=0;i<n;i++)
    {
        fre[i]=inc;
        inc=inc+1;
        phase[i]=0;
        frey[i]=25;
    }
    printf(" STATE %d for sin and %d for cos :\n",1,2);
    for(i=0;i<n;i++)
    {
        scanf("%d",&state[i]);
    }
    for(i=0;i<n;i++)
    {
        da[i]=1;ampy[i]=25;px[i]=315+i*50;py[i]=25;
        dc[i]=fre[i];
        ballx[i]=0;
        bally[i]=0;
        ballz[i]=0;
        dmode[i]=0;
        t[i]=0;
    }
    for(i=0;i<n;i++)
    {
        visball[i]=1;
        viscurve[i]=1;
    }
    iSetTimer(1000,clrchange);
    iSetTimer(5,ballchange);
    iInitialize(1000,600,"sin-cos curves");
    return 0;
}
