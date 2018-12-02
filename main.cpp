#include <iostream>
#include <winbgim.h>
#include <stdlib.h>

using namespace std;
#define MAX 20
#define CAINE CYAN
#define VULPE RED
#define SPATIU 0

int stanga,sus,width,height,latura,numar;
bool gata;
int TablaDeJoc[MAX][MAX];


/*void stergePiesa(int linia, int coloana)
{
   int x1,y1,x2,y2,xmijloc,ymijloc;
   x1=stanga+latura*(coloana-1);
   y1=sus+latura*(linia-1);
   x2=x1+latura; y2=y1+latura;
   xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
   if((linia + coloana)%2 == 0)
   setcolor(GREEN); rectangle(x1,y1,x2,y2);
   else
    setcolor(BLACK); rectangle(x1,y1,x2,y2);
   setcolor(FUNDAL); setfillstyle(SOLID_FILL,FUNDAL);
   bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
} */

void deseneazaPiesa(int linia, int coloana, int codPiesa)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    setcolor(WHITE);
    if((linia + coloana )%2 == 1)
    {
        rectangle(x1,y1,x2,y2);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(xmijloc,ymijloc,WHITE);

    }
    else
    {
        rectangle(x1,y1,x2,y2);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(xmijloc,ymijloc,WHITE);

    }
    if(codPiesa != 0)
    {
        setcolor(codPiesa);
        setfillstyle(SOLID_FILL,codPiesa);
        fillellipse(xmijloc,ymijloc,18,15);
    }

}

void initTabla()
{
    numar=8;
    int coloana,linia;
    for(linia = 1; linia <= numar ; linia++)
        for(coloana = 1; coloana <= numar; coloana ++)
            TablaDeJoc[linia][coloana] = SPATIU;
    for(coloana = 1; coloana <= numar; coloana+=2)
        TablaDeJoc[numar][coloana] = CAINE;
    TablaDeJoc[1][4] = VULPE;
}

void initializariDimensiuni()
{
    width = 500;
    height=500;
    latura=width/numar;
    sus=(getmaxy()-width)/2;
    stanga=(getmaxx()-height)/2;
}

void desenTabla()
{
    initializariDimensiuni();
    setbkcolor(BLACK);
    clearviewport();
    //   setcolor(BLUE);
    int linia,coloana;
    for (linia=1; linia<=numar; linia++)
        for (coloana=1; coloana<=numar; coloana++)
        {
            deseneazaPiesa(linia,coloana,TablaDeJoc[linia][coloana]);
        }
}


int main()
{
    initwindow(800, 600);
    initTabla();
    desenTabla();
    gata = false;
    while(!gata)
    {
        getch();
        closegraph();
    }
    return 0;
}
