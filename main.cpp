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


void iesireUrgenta()
{
    char tasta;
    if (kbhit())
    {
        tasta=getch();
        if (tasta==27)
        {
            closegraph();
            exit(0);
        }
    }
}

bool inInterior(int x, int y, int x1, int y1, int x2, int y2)
{
    return x1<=x && x<=x2 && y1<=y && y<=y2;
}


void stergePiesa(int linia, int coloana)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    setcolor(WHITE);
    if((linia + coloana)%2 == 1)
    {
        rectangle(x1,y1,x2,y2);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(xmijloc,ymijloc, WHITE);
    }
    else
    {
        rectangle(x1,y1,x2,y2);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(xmijloc,ymijloc, WHITE);
    }
}

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
bool vulpeIncoltita(int linia, int coloana)
{
    if(linia == 1 )
    {
        if(coloana == 1)
        {
            if(TablaDeJoc[linia + 1][coloana + 1] == CAINE )
                return true;
        }
        else if(coloana == 8 )
        {
            if(TablaDeJoc[linia + 1][coloana - 1] == CAINE )
                return true;
        }
        else if (TablaDeJoc[linia + 1][coloana + 1] == CAINE && TablaDeJoc[linia +1][coloana - 1] == CAINE )
            return true;
    }
    if(coloana == 1)
        if(TablaDeJoc[linia-1][coloana + 1] == CAINE && TablaDeJoc[linia +1][coloana +1] == CAINE )
            return true;
    if(coloana == 8)
        if(TablaDeJoc[linia -1][coloana - 1] == CAINE && TablaDeJoc[linia +1][coloana -1]==CAINE )
            return true;
    if(TablaDeJoc[linia - 1][coloana +1] == CAINE && TablaDeJoc[linia - 1][coloana - 1] == CAINE &&
            TablaDeJoc[linia + 1][coloana +1] == CAINE && TablaDeJoc[linia + 1][coloana - 1] == CAINE)
        return true ;
    return false;
}

bool vulpeCastiga(int linia , int coloana)
{
    if(linia == 8)
        return true;
    return false;
}
void mutareCaine()
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    bool mutareCorecta;
    do
    {
        iesireUrgenta();
        mutareCorecta=false;
        if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            // x=mousex(); y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            // cout<<linia1<<","<<coloana1<<"=>";
            //circle(stanga+coloana1*latura+latura/2, sus+linia1*latura+latura/2,5);
            if (TablaDeJoc[linia1][coloana1]==CAINE)
            {
                do
                {
                    iesireUrgenta();
                    if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        // x=mousex(); y=mousey();
                        linia2=(y-sus)/latura+1;
                        coloana2=(x-stanga)/latura+1;
                        // cout<<linia2<<","<<coloana2<<endl;
                        if (TablaDeJoc[linia2][coloana2]==SPATIU  && (linia2 == linia1 - 1) && ((coloana2 == coloana1 + 1) || coloana2 == coloana1 -1))
                        {
                            mutareCorecta=true;
                            TablaDeJoc[linia1][coloana1]=SPATIU;
                            TablaDeJoc[linia2][coloana2]=CAINE;
                            stergePiesa(linia1,coloana1);
                            deseneazaPiesa(linia2,coloana2,CAINE);
                        }
                    }
                }
                while (!mutareCorecta);
            }
        }
    }
    while (!mutareCorecta);
}


void mutareVulpe()
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    bool mutareCorecta;
    do
    {
        iesireUrgenta();
        mutareCorecta=false;
        if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            // x=mousex(); y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            // cout<<linia1<<","<<coloana1<<"=>";
            //circle(stanga+coloana1*latura+latura/2, sus+linia1*latura+latura/2,5);
            if (TablaDeJoc[linia1][coloana1]==VULPE)
            {
                bool incoltita = vulpeIncoltita(linia1,coloana1);
                if(incoltita == true)
                {
                    clearviewport();
                    outtextxy(width/2,height/2, "VULPEA A FOST INCOLTITA.FELICITARI CAINI!");

                    break;
                }
                do
                {
                    iesireUrgenta();
                    if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        // x=mousex(); y=mousey();
                        linia2=(y-sus)/latura+1;
                        coloana2=(x-stanga)/latura+1;
                        // cout<<linia2<<","<<coloana2<<endl;
                        if (TablaDeJoc[linia2][coloana2]==SPATIU && ((linia2 == linia1 - 1 ) || (linia2 == linia1 + 1)) && ((coloana2 == coloana1 + 1) || coloana2 == coloana1 -1))
                        {
                            mutareCorecta=true;
                            TablaDeJoc[linia1][coloana1]=SPATIU;
                            TablaDeJoc[linia2][coloana2]=VULPE;
                            stergePiesa(linia1,coloana1);
                            deseneazaPiesa(linia2,coloana2,VULPE);
                            bool vulpeWin = vulpeCastiga(linia2 , coloana2);
                            if(vulpeWin){
                                clearviewport();
                                outtextxy(width/2,height/2, "VULPEA A CASTIGAT.FELICITARI VULPE!");
                            }
                        }
                    }
                }
                while (!mutareCorecta);
            }
        }
    }
    while (!mutareCorecta);
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
    initwindow(800,600);
    initTabla();
    desenTabla();
    do
    {
        mutareVulpe();
        mutareCaine();
    }
    while (true);
    return 0;
}
