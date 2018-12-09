#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

#define MAX 20
#define FUNDAL BLACK
#define SPATIU 0
#define CAINE 1
#define VULPE 2
#define PIATRA 3
#define TINTA 4
int stanga,sus,width,height,latura,numar;
int liniaTarget, coloanaTarget;
bool gata;

int TablaDeJoc[MAX][MAX];

void initializariDimensiuni()
{
    width=500;
    height=500;
    latura=width/numar;
    sus=(getmaxy()-width)/2;
    stanga=(getmaxx()-height)/2;
}

void initTabla( int nivel = 0)
{
    numar=8;
    int coloana,linia;
    for(linia = 1; linia <= numar ; linia++)
        for(coloana = 1; coloana <= numar; coloana ++)
            TablaDeJoc[linia][coloana] = SPATIU;
    for(coloana = 1; coloana <= numar; coloana+=2)
        TablaDeJoc[numar][coloana] = CAINE;
    TablaDeJoc[1][4] = VULPE;

    if(nivel == 1)
    {
        TablaDeJoc[5][2] = PIATRA;
        TablaDeJoc[3][6] = PIATRA;
    }
    if(nivel == 2)
    {

    }
    if(nivel == 3)
    {

    }
    if(nivel == 4)
    {
        TablaDeJoc[5][2] = PIATRA;
        TablaDeJoc[3][6] = PIATRA;
        TablaDeJoc[4][6] = PIATRA;
        TablaDeJoc[2][7] = PIATRA;
        liniaTarget = 8;
        coloanaTarget = 4;
        TablaDeJoc[liniaTarget][coloanaTarget] = TINTA;

    }
}


void stergePiesa(int linia, int coloana)
{
    int x1,y1,x2,y2;//xmijloc,ymijloc;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    setfillstyle(SOLID_FILL,getpixel(x1+1,y1+1));
    bar(x1,y1,x2,y2);
}

void deseneazaPiesa(int linia, int coloana, int codPiesa)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    if(codPiesa==CAINE)
        readimagefile("Screenshot_3.jpg",x1,y1,x2,y2);
    else if(codPiesa == VULPE)
        readimagefile("fox1.bmp",x1,y1,x2,y2);
    else if(codPiesa == PIATRA)
        readimagefile("piatra.jpg",x1,y1,x2,y2);
    else if((linia + coloana)%2 ==1)
        readimagefile("target1.jpg", x1,y1,x2,y2);
    else
        readimagefile("target2.jpg",x1,y1,x2,y2);
}

void desenTabla()
{
    initializariDimensiuni();
    setbkcolor(FUNDAL);
    clearviewport();
    //   setcolor(BLUE);
    int linia,coloana;
    for (linia=1; linia<=numar; linia++)
        for (coloana=1; coloana<=numar; coloana++)
        {
            int x1=stanga+latura*(coloana-1);
            int y1=sus+latura*(linia-1);
            int x2=x1+latura;
            int y2=y1+latura;
            if((linia + coloana )%2 == 1)
            {
                setfillstyle(SOLID_FILL,GREEN);
                bar(x1,y1,x2,y2);
            }
            else
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(x1,y1,x2,y2);
            }
            if(TablaDeJoc[linia][coloana]!=SPATIU)
                deseneazaPiesa(linia,coloana,TablaDeJoc[linia][coloana]);
        }
}

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

bool vulpeIncoltita(int linia, int coloana)
{
    if(linia == 1 )
    {
        if(coloana == 1)
        {
            if(TablaDeJoc[linia + 1][coloana + 1] != SPATIU )
                return true;
        }
        else if(coloana == 8 )
        {
            if(TablaDeJoc[linia + 1][coloana - 1] != SPATIU )
                return true;
        }
        else if (TablaDeJoc[linia + 1][coloana + 1] !=SPATIU && TablaDeJoc[linia +1][coloana - 1] != SPATIU )
            return true;
    }
    if(coloana == 1)
        if(TablaDeJoc[linia-1][coloana + 1] != SPATIU && TablaDeJoc[linia +1][coloana +1] != SPATIU )
            return true;
    if(coloana == 8)
        if(TablaDeJoc[linia -1][coloana - 1] != SPATIU && TablaDeJoc[linia +1][coloana -1]!=SPATIU )
            return true;
    if(TablaDeJoc[linia - 1][coloana +1] !=SPATIU && TablaDeJoc[linia - 1][coloana - 1] != SPATIU &&
            TablaDeJoc[linia + 1][coloana +1] != SPATIU && TablaDeJoc[linia + 1][coloana - 1] != SPATIU)
        return true ;
    return false;
}

bool vulpeCastiga(int linia, int coloana)
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
    if(!gata)
        outtextxy(getmaxx()/2, 5, "Rand Caine");

    do
    {
        iesireUrgenta();
        mutareCorecta=false;
        if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
        {

            clearmouseclick(WM_LBUTTONDOWN);

            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;

            if (TablaDeJoc[linia1][coloana1]==CAINE)
            {

                do
                {
                    iesireUrgenta();
                    if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);

                        linia2=(y-sus)/latura+1;
                        coloana2=(x-stanga)/latura+1;

                        if (TablaDeJoc[linia2][coloana2]==SPATIU  && (linia2 == linia1 - 1) && ((coloana2 == coloana1 + 1) || coloana2 == coloana1 -1))
                        {
                            mutareCorecta=true;
                            TablaDeJoc[linia1][coloana1]=SPATIU;
                            TablaDeJoc[linia2][coloana2]=CAINE;
                            stergePiesa(linia1,coloana1);
                            deseneazaPiesa(linia2,coloana2,CAINE);
                        }
                        else
                        {
                            setfillstyle(SOLID_FILL,FUNDAL);
                            bar(0, 0, getmaxx(), 40);
                            outtextxy(getmaxx()/2 - textwidth("Mutare gresita. Este inca randul cainelui")/2, 5, "Mutare gresita. Este inca randul cainelui");


                            break;
                        }
                    }
                }
                while (!mutareCorecta);
            }
        }
    }
    while (!mutareCorecta);
    setfillstyle(SOLID_FILL,FUNDAL);
    bar(0, 0, getmaxx(), 40);
}

void mutareVulpe()
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    bool mutareCorecta, vulpeWin, incoltita;
    if(!gata)
        outtextxy(getmaxx()/2, 5, "Rand Vulpe");
    do
    {
        iesireUrgenta();
        mutareCorecta=false;
        if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;

            if (TablaDeJoc[linia1][coloana1]==VULPE)
            {
                incoltita = vulpeIncoltita(linia1,coloana1);
                if(incoltita == true)
                {
                    gata = true;
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

                        linia2=(y-sus)/latura+1;
                        coloana2=(x-stanga)/latura+1;

                        if (TablaDeJoc[linia2][coloana2]==SPATIU && ((linia2 == linia1 - 1 ) || (linia2 == linia1 + 1)) && ((coloana2 == coloana1 + 1) || coloana2 == coloana1 -1))
                        {
                            mutareCorecta=true;
                            TablaDeJoc[linia1][coloana1]=SPATIU;
                            TablaDeJoc[linia2][coloana2]=VULPE;
                            stergePiesa(linia1,coloana1);
                            deseneazaPiesa(linia2,coloana2,VULPE);
                            vulpeWin = vulpeCastiga(linia2, coloana2);
                            if(vulpeWin)
                            {
                                gata = true;
                                clearviewport();
                                outtextxy(width/2,height/2, "VULPEA A CASTIGAT.FELICITARI VULPE!");
                            }
                        }
                        else
                        {
                            setfillstyle(SOLID_FILL,FUNDAL);
                            bar(0, 0, getmaxx(), 40);
                            outtextxy(getmaxx()/2 -textwidth("Mutare gresita. Este inca randul vulpii")/2, 5, "Mutare gresita. Este inca randul vulpii");
                            break;
                        }
                    }
                }
                while (!mutareCorecta);
            }
        }
    }
    while (!mutareCorecta);
    setfillstyle(SOLID_FILL,FUNDAL);
    bar(0, 0, getmaxx(), 40);
}
void mutareTinta()
{
    bool targetVulpe;
    int liniaTarget1, coloanaTarget1;
    do
    {
        srand((unsigned)time(0));
        liniaTarget1 = rand() % 8 + 1;
        coloanaTarget1 = rand() %8 +1 ;
        if(TablaDeJoc[liniaTarget1][coloanaTarget1] == VULPE)
        {

            clearviewport();
            outtextxy(getmaxx()/2,getmaxy()/2, "VULPEA A FOST IMPUSCATA.CAINII CASTIGA!");

        }
        if(TablaDeJoc[liniaTarget1][coloanaTarget1] != CAINE && TablaDeJoc[liniaTarget1][coloanaTarget1] != VULPE && TablaDeJoc[liniaTarget1][coloanaTarget1] != PIATRA)
        {
            TablaDeJoc[liniaTarget][coloanaTarget]=SPATIU;
            stergePiesa(liniaTarget,coloanaTarget);
            liniaTarget = liniaTarget1;
            coloanaTarget = coloanaTarget1;
            TablaDeJoc[liniaTarget][coloanaTarget] = TINTA;
            deseneazaPiesa(liniaTarget,coloanaTarget,TINTA);
        }
    }
    while(TablaDeJoc[liniaTarget][coloanaTarget]!= TINTA);


}


int main()
{
    initwindow(800,600);
    initTabla();
    readimagefile("Game-of-Fox-and-Hounds.jpg",0, 0, getmaxx(),getmaxy());
    delay(3000);
    clearviewport();
    desenTabla();
    do
    {
        mutareVulpe();
        mutareCaine();
       // mutareTinta();
    }
    while (true);
    return 0;
}
