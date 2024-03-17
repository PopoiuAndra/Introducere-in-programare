#include <iostream>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
#define NMAX 100

struct
{
    char sablon[NMAX][NMAX];
    int cnt;
} sabloane;

struct raspunsuri
{
    char response[NMAX];
    int numarPropozitii; /// numarul de propozitii din fisier pentru sablonnul respectiv
    int propozitieDeAfisat = 0; /// propozitia din fisier care va fi afisata ca raspuns
} r[NMAX][NMAX];

struct verbe
{
    char conj1[NMAX]; /// conjugarea initiala(la persoana 1)
    char conj2[NMAX]; /// conjugarea finala(la persoana 2)
    int cnt;
} c[NMAX];

struct keywords
{
    char kbani[NMAX][NMAX];
    int cntBani = 0;
    char ksanatate[NMAX][NMAX];
    int cntSanatate = 0;
    char kfamilie[NMAX][NMAX];
    int cntFamilie = 0;
} key;

struct last_answers
{
    int n;
    char text[100];
} last[100];

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

bool apartine(punct P, dreptunghi D)
{
    return D.SS.x<=P.x && P.x<=D.DJ.x && D.SS.y<=P.y && P.y<=D.DJ.y;
}

struct butoane_meniu
{

    dreptunghi D;
    int culoare;
    char text[20];
};

butoane_meniu B[6];
int nrButoaneMeniu = 6;
int avatar;

void deseneazaMeniul()
{
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(0,0, 800, 800); /// fundalul meniului
    int i;
    int font, font_size, direction;

    /// SCRISUL DE SUS
    {
        font = 8;
        font_size = 8;
        direction = 0;

        settextstyle(font, direction, 8);

        setcolor(BLACK); /// setez culoarea scrisului
        setbkcolor(LIGHTRED); /// culoarea din spatele scrisului
        outtextxy(300, 50, "ELSA");

        font_size = 5;

        settextstyle(font, direction, font_size);
        outtextxy(225, 150, "terapeutul tau");
    }

    /// CARACTERISTICI GENERALE BUTOANE
    {
        setcolor(WHITE); /// marginea butonului
        setfillstyle(SOLID_FILL,MAGENTA);

        font = 1;
        font_size = 5;
        direction = 0;

        settextstyle(font, direction, font_size);
    }

    /// BUTONUL PRINCIPAL - BUTONUL 1
    {
        B[1].D.SS.x=300;
        B[1].D.DJ.x=500;
        B[1].D.SS.y=300;
        B[1].D.DJ.y=365;
        strcpy(B[1].text,"Start");

        bar(B[1].D.SS.x, B[1].D.SS.y, B[1].D.DJ.x, B[1].D.DJ.y);/// coloreaza butonul fara ce e scris (printr o bara de grosime 30)
        rectangle(B[1].D.SS.x, B[1].D.SS.y,B[1].D.DJ.x,B[1].D.DJ.y);
        setbkcolor(MAGENTA); /// culoarea din spatele scrisului
        outtextxy(B[1].D.SS.x+30,B[1].D.SS.y+10,B[1].text);
    }

    /// BUTONUL DE IESIRE
    {
        B[2].D.SS.x=300;
        B[2].D.DJ.x=500;
        B[2].D.SS.y=400;
        B[2].D.DJ.y=465;
        strcpy(B[2].text,"Iesire");
        bar(B[2].D.SS.x, B[2].D.SS.y, B[2].D.DJ.x, B[2].D.DJ.y);/// coloreaza butonul fara ce e scris (printr o bara de grosime 30)
        rectangle(B[2].D.SS.x, B[2].D.SS.y,B[2].D.DJ.x,B[2].D.DJ.y);
        setbkcolor(MAGENTA); /// culoarea din spatele scrisului
        outtextxy(B[2].D.SS.x+25,B[2].D.SS.y+10,B[2].text);
    }

    /// BUTOANE DE ALES AVATAR
    {
        font = 8;
        font_size = 5;
        direction = 0;

        settextstyle(font, direction, font_size);

        setcolor(BLACK); /// setez culoarea scrisului
        setbkcolor(LIGHTRED); /// culoarea din spatele scrisului
        outtextxy(150, 550, "Alege-ti avatarul!");

        /// Cele 4 avatare - BUTONUL 3, 4, 5 SI 6

        setcolor(WHITE); /// setez culoarea ramei

        /// Avatar 1
        B[3].D.SS.x=125;
        B[3].D.DJ.x=225;
        B[3].D.SS.y=620;
        B[3].D.DJ.y=720;

        readimagefile("caracterA.jpg", 125,620,225,720);

        /// Avatar 2
        B[4].D.SS.x=275;
        B[4].D.DJ.x=375;
        B[4].D.SS.y=620;
        B[4].D.DJ.y=720;

        readimagefile("caracterB.jpg", 275,620,375,720);

        /// Avatar 3
        B[5].D.SS.x=425;
        B[5].D.DJ.x=525;
        B[5].D.SS.y=620;
        B[5].D.DJ.y=720;

        readimagefile("caracterC.jpg", 425,620,525,720);

        /// Avatar 4
        B[6].D.SS.x=575;
        B[6].D.DJ.x=675;
        B[6].D.SS.y=620;
        B[6].D.DJ.y=720;

        readimagefile("caracterD.jpg", 575,620,675,720);
    }
}

void deseneazaChatul()
{
    settextstyle(8,0,2);
    setfillstyle(SOLID_FILL, WHITE);
    bar(0, 0, getmaxx()+1, getmaxy());
    setfillstyle(SOLID_FILL, MAGENTA);
    bar(0, 0, getmaxx()+1, 40);
    setbkcolor(MAGENTA);
    outtextxy(20, 10,"ELIZA");
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 50, 790, 700);
    bar(75, 755, 785, 760);

    /// Avatar
    if(avatar != 0)
    {
        if(avatar == 3)
            readimagefile("caracterA2.jpg", 10,700,70,760);

        else if(avatar == 4)
            readimagefile("caracterB2.jpg", 10,700,70,760);

        else if(avatar == 5)
            readimagefile("caracterC2.jpg", 10,700,70,760);

        else
            readimagefile("caracterD2.jpg", 10,700,70,760);
    }
}

void avatarulAles(int nr)
{
    /// Refacem casutele initiale

    readimagefile("caracterA.jpg", 125,620,225,720);
    readimagefile("caracterB.jpg", 275,620,375,720);
    readimagefile("caracterC.jpg", 425,620,525,720);
    readimagefile("caracterD.jpg", 575,620,675,720);

    /// Marginea avatarului ales
    setfillstyle(SOLID_FILL, MAGENTA);
    if(nr == 3)
    {
        bar(125, 620, 226, 630);
        bar(125, 620, 135, 721);
        bar(125, 710, 226, 721);
        bar(215, 620, 226, 721);
    }
    else if(nr == 4)
    {
        bar(275, 620, 376, 630);
        bar(275, 620, 285, 721);
        bar(275, 710, 376, 721);
        bar(365, 620, 376, 721);
    }
    else if(nr == 5)
    {
        bar(425, 620, 526, 630);
        bar(425, 620, 435, 721);
        bar(425, 710, 526, 721);
        bar(515, 620, 526, 721);
    }
    else if(nr == 6)
    {
        bar(575, 620, 676, 630);
        bar(575, 620, 585, 721);
        bar(575, 710, 676, 721);
        bar(665, 620, 676, 721);
    }
}

void recopiaza_text1(char s[NMAX])
{
    for(int i = 21; i > 2; -- i)
        last[i] = last[i-2];
    strcpy(last[2].text, s);
    last[2].n = strlen(s);

    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 50, 790, 700);

    settextstyle(8, 0, 1);
    setbkcolor(BLACK);
    setcolor(WHITE);

    for(int i = 2; i <= 21; ++ i)
        if(strlen(last[i].text) == 0 && strlen(last[i+1].text) == 0) break;
        else if(i%2 == 1)
        {
            outtextxy(15, 700-i*30,"ELSA: ");
            outtextxy(90, 700-i*30, last[i].text);
        }
        else
        {
            outtextxy(15, 700-i*30,"USER: ");
            outtextxy(90, 700-i*30, last[i].text);
        }
}

int butonAlesMeniu()
{
    int i;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x=mousex();
        p.y=mousey();
        for (i=1; i<=nrButoaneMeniu; i++)
            if (apartine(p,B[i].D))
                return i;
    }
    return 0;
}

void conjugare (char s[NMAX])
{
    int i;
    bool ok;
    char *p;
    char aux[NMAX]= {""};
    p = strtok (s, " ,.?!-");
    while (p)
    {
        ok = 0;
        for(i = 1; i <= c[0].cnt && ok == 0; ++ i)
            if(strcmp(p, c[i].conj1) == 0)
            {
                ok = 1;
                strcat(aux, c[i].conj2);
                strcat(aux, " ");
            }
        if(ok == 0)
        {
            strcat (aux, p);
            strcat (aux, " ");
        }
        p = strtok (NULL, " ,.?!-");
    }
    strcpy(s, aux);
}

bool AfiseazaRaspuns(char keyw[NMAX], char e[NMAX])
{
    int i;
    for(i = 1; i <= sabloane.cnt; ++ i)
    {
        if(strlen(keyw) >= strlen(sabloane.sablon[i]) && strstr(keyw,sabloane.sablon[i]) != 0)
        {
            if(r[i][0].propozitieDeAfisat == r[i][0].numarPropozitii)
                r[i][0].propozitieDeAfisat = 0;
            r[i][0].propozitieDeAfisat ++;
            strcpy(e, r[i][r[i][0].propozitieDeAfisat].response);
            cout<<e<<"\n";
            return 1;
        }
    }
    return 0;
}

void CopiereKeyWords(char v[NMAX][NMAX], FILE *fisier, int &n)
{
    n = 0;
    rewind(fisier);
    while(!feof(fisier))
    {
        n ++;
        if (!fgets(v[n],NMAX,fisier))
            break;
        v[n][strlen(v[n])-1] = NULL;
    }
    n--;
}

void CopiereRaspunsuri(FILE *fam)
{
    int linieRaspuns = 0, numarulPropozitiei, cuvant, i, nrSablon;
    char propozitii[NMAX*NMAX];
    char *p, *q, *p2;
    char nou[NMAX];
    bool ok = 1;

    nrSablon = 0;
    rewind(fam);
    while(!feof(fam))
    {
        if(!fgets(propozitii, NMAX*NMAX, fam))
            break;
        propozitii[strlen(propozitii)-1] = NULL;

        p = strtok(propozitii, "=|");
        numarulPropozitiei = 0;
        linieRaspuns ++;
        ok = 1;
        while(p)
        {
            /// Pentru sablonul de la inceput
            if(ok == 1)
                strcpy(sabloane.sablon[++nrSablon], p);

            /// Pentru fiecare raspuns
            else
            {
                numarulPropozitiei++;
                strcpy(r[linieRaspuns][numarulPropozitiei].response, p);
            }
            ok = 0;
            p = strtok(0,"=|");
        }
        /// cate propozitii avem pentru respectivul sablon
        r[linieRaspuns][0].numarPropozitii = numarulPropozitiei;
    }
    sabloane.cnt = nrSablon;
}

void CopiereConjugari(FILE *fisier)
{
    char aux[NMAX];
    int pozEgal, n = 0;
    rewind(fisier);
    while(!feof(fisier))
    {
        n ++;
        if (!fgets(aux,NMAX,fisier))
            break;
        aux[strlen(aux)-1] = NULL;

        strcpy(c[n].conj2, strchr(aux,'=') + 1 ); /// copiaza partea de dupa egal din fisier ( "+1" pentru a nu copia si '=')
        pozEgal = strlen(aux) - strlen(c[n].conj2) - 1;
        strncpy(c[n].conj1, aux, pozEgal);
    }
    n--;
    c[0].cnt = n;
}

void FormareVectorDeSabloane(char vect[NMAX][NMAX], char keyw[NMAX], int n, char cuv[NMAX], int &cnt)
{
    for(int i = 1; i <= n; ++ i)
        if(strncmp(cuv, vect[i], strlen(vect[i])) == 0)
        {
            strcat(keyw, vect[i]);
            strcat(keyw, "%");
            cnt ++;
            return;
        }
}

void sortare (char keyw[NMAX])
{
    char sortat[NMAX][NMAX];
    char *p;
    int k=0;
    p=strtok(keyw, "%");
    while (p)
    {
        strcpy(sortat[k++], p);
        p=strtok( NULL, "%");
    }
    k--;
    char aux[NMAX];
    for (int i=0; i<=k-1; i++)
        for (int j=i+1; j<=k; j++)
            if (strcmp(sortat[i],sortat[j])>0)
            {
                strcpy(aux, sortat[i]);
                strcpy(sortat[i], sortat[j]);
                strcpy(sortat[j], aux);
            }
    strcpy(keyw,"");
    for (int i=0; i<=k; i++)
    {
        strcat(keyw, sortat[i]);
        strcat(keyw, "%");
    }
}

int maxim(int a, int b, int c)
{
    if (a>=b && a>=c) return 1;
    if (b>=a && b>=c) return 2;
    if (c>=b && c>=a) return 3;
}

void transformare(char s[NMAX])
{
    for (int i=0; i<strlen(s); i++)
        if (s[i]>='A' && s[i]<='Z')
            s[i]+=32;
}

char s[NMAX], s1[NMAX], s2[NMAX], e1[NMAX], e2[NMAX], e[NMAX];
char cuv[NMAX], *p, aux[NMAX], keyw[NMAX], keyw2[NMAX], semnificativ[NMAX], replica[NMAX];
int j=0, j2=1;

int main()
{
    char s[NMAX];
    /// FISIERE ------------------------
    {
        FILE *bani, *sanatate, *familie;

        bani = fopen("bani.txt", "r+");
        sanatate = fopen("sanatate.txt", "r+");
        familie = fopen("familie.txt", "r+");

        CopiereKeyWords(key.kbani, bani, key.cntBani);
        CopiereKeyWords(key.kfamilie, familie, key.cntFamilie);
        CopiereKeyWords(key.ksanatate, sanatate, key.cntSanatate);

        FILE *raspunsuri_kw, *conjugari_verbe;
        raspunsuri_kw = fopen("raspunsuri_keywords.txt", "r+");
        conjugari_verbe = fopen("conjugari_verbe.txt", "r+");

        CopiereRaspunsuri(raspunsuri_kw);
        CopiereConjugari(conjugari_verbe);

        fclose(bani);
        fclose(sanatate);
        fclose(familie);
        fclose(raspunsuri_kw);
        fclose(conjugari_verbe);
    }

    /// GRAFICA ------------------------
    bool ok = 0;
    int font, direction, font_size;
    int inaltime, latime;
    int comanda, butonul_apasat;

    inaltime = GetSystemMetrics(SM_CYSCREEN);
    latime = GetSystemMetrics(SM_CXSCREEN);

    initwindow(800, 800, "ELIZA");

    deseneazaMeniul();
    do
    {
        butonul_apasat = butonAlesMeniu();
        switch(butonul_apasat)
        {
        case 1:
            comanda=butonul_apasat;
            cout<<"Comanda "<<comanda<<endl;
            goto chat;
            break;
        case 2:
            comanda=butonul_apasat;
            cout<<"Comanda "<<comanda<<endl;
            ok = 1;
            break;
        /// Selectia avatarului
        case 3:
        case 4:
        case 5:
        case 6:
            if(avatar == butonul_apasat) avatar = 0;
            else avatar = butonul_apasat;
            comanda = butonul_apasat;
            cout<<"Comanda "<<comanda<<endl;
            avatarulAles(avatar);
            break;
        }
    }
    while (comanda != 2);

    if(ok == 0)
    {
        chat:
        int x = 1, y = 1, cntKeywords;
        bool ok = 0, aFostAfisatRaspunsul;
        bool sal=0;
        char s[100]= {0};
        int valoare;
        deseneazaChatul();

        settextstyle(8, 0, 1);
        setbkcolor(BLACK);
        setcolor(WHITE);
        strcpy(last[1].text,"Buna, sunt Elsa, terapeutul tau!");
        outtextxy(15, 700-30,"ELSA: ");
        outtextxy(90, 700-30, last[1].text);

        comanda = 0;
        do
        {
            valoare = 0;
            valoare = getch();

            if(valoare == 13)
            {

                setfillstyle(SOLID_FILL,WHITE);
                bar(75, 755, 785,690);
                recopiaza_text1(s);

                ///  ... ->
                setbkcolor(WHITE);
                setcolor(BLACK);
                outtextxy(75,765,"Eliza tasteaza ...");
                sleep_for(seconds(1));

                setfillstyle(SOLID_FILL, WHITE);
                bar(75, 765, 400, 790);
                /// ... <-

                printf("ELSA: ");
                transformare(s);
                strcpy(e,"");

                /// Cazuri de inceput
                if (sal==0)  //prima replica, daca saluta sau nu;
                {
                    if (!strstr(s, "hei") && !strstr(s, "hello") && !strstr(s, "buna") && !strstr(s, "salut"))
                        strcpy(e,"BUNA! Nu stii sa saluti?");

                    else
                        strcpy(e,"Ce faci? Ce problema ai?");

                    sal++;
                }
                else if (sal==1 && (strstr(s, "hei") || strstr(s, "buna") || strstr(s, "hello") || strstr(s, "salut")))
                {
                    strcpy(e,"Ce faci? Ce problema ai?");
                    sal++;
                }
                else if (strstr (s, "scuze") > 0 || strstr (s, "imi pare rau") > 0)
                    strcpy(e, "E in regula. :)");

                else if (strcmp (s, s1)==0 || strcmp (s, s2)==0)
                    strcpy(e,"Altceva nu stii sa spui?");

                else if (strlen(s)==1 && isalpha(s[0]))
                {
                    strcpy(e, "Vorbeste daca vrei sa te ajut. :D");
                    aFostAfisatRaspunsul = 1;
                }

                ///daca repeta ce spune elsa;
                else if (strcmp(e1, s)==0)
                    strcpy(e, "Nu repeta ce spun eu daca vrei o solutie!");

                ///daca spune nu
                else if (strcmp(s, "nu")==0 && strlen(s)<4)
                    strcpy(e, "Cam negativisti suntem azi... :(");

                else if (strcmp(s, "da")==0 && strlen(s)<4)
                    strcpy(e, "Bine atunci. Hai sa schimbam subiectul.");

                else if (strstr (s, "nu am probleme"))
                    strcpy(e, "Atunci de ce ai mai venit la mine? :)");

                else if (strstr (s, "multumesc"))
                    strcpy(e, "Cu drag. <3");

                else if (strstr (s, "nu e adevarat") || strstr(s, "ba nu"))
                    strcpy(e, "Esti sigur?");

                else if(strstr(s, "la revedere") || strcmp (s, "pa")==0)
                {
                    strcpy(e,"A fost o placere sa vorbesc cu tine! :)");
                    cout<<e<<'\n';
                }

                if (strlen(e))
                    cout<<e<<'\n';

                ///GENERALIZARE
                else
                {
                    /// Cauta cuvinte cheie in fiecare folder
                    int n = 0;
                    strcpy(aux, s);
                    cntKeywords = 0;
                    strcpy(keyw, "");
                    p = strtok(aux, " ");
                    while(p)
                    {
                        strcpy(cuv, p);

                        /// FORMAREA VECTORULUI DE SABLOANE in keyw
                        FormareVectorDeSabloane(key.kbani, keyw, key.cntBani, cuv, cntKeywords);
                        FormareVectorDeSabloane(key.kfamilie, keyw, key.cntFamilie, cuv, cntKeywords);
                        FormareVectorDeSabloane(key.ksanatate, keyw, key.cntSanatate, cuv, cntKeywords);

                        p = strtok(NULL, " ");
                    }
                    sortare(keyw);

                    ///daca gaseste sa nu cuvintele cheie din cele 3 domenii
                    if(cntKeywords != 0)
                        aFostAfisatRaspunsul = AfiseazaRaspuns(keyw,e);

                    if (cntKeywords == 0 || aFostAfisatRaspunsul == 0)
                    {
                        if (s[0]==NULL)
                        {
                            strcpy(keyw, "nimic%");
                            AfiseazaRaspuns(keyw, e);
                            aFostAfisatRaspunsul=1;
                        }

                        char w[NMAX];
                        w[0] = NULL;

                        ///sunt ...
                        if (strstr (s, "sunt") >0)
                        {
                            strcpy(e, "Din ce cauza esti ");
                            strcpy (w, strstr(s, "sunt"));
                            p=strtok(w, " ");
                            p=strtok(NULL, " ");
                            strcat (e, p);
                            strcat (e, "?");
                        }

                        ///nu vreau/vreau ceva...
                        else if (strstr (s, "nu vreau") > 0)
                        {
                            strcpy(e, "De ce nu vreau ");
                            strcpy (w, strstr(s, "vreau"));
                            p=strtok(w, " ");
                            p=strtok(NULL, " ");
                            while (p)
                            {
                                strcat (e, p);
                                strcat (e, " ");
                                p=strtok(NULL, " ");
                            }
                            conjugare(e);
                            strcat(e,"?");
                        }

                        else if (strstr (s, "vreau") > 0)
                        {
                            char sth[NMAX];
                            bool ceva=0;
                            strcpy(sth, "Chiar cred ca daca am fi avut ");
                            strcpy (w, strstr(s, "vreau"));
                            p=strtok(w, " ");
                            p=strtok(NULL, " ");
                            while (p)
                            {
                                if (strcmp(p, "un")==0 || strcmp(p, "o")==0 || strcmp(p, "niste")==0 || strcmp(p, "alt")==0 || strcmp(p, "alta")==0)
                                {
                                    strcat(sth, p);
                                    ceva=1;
                                }
                                else strcat (sth, p);
                                strcat (sth, " ");
                                p=strtok(NULL, " ");
                            }
                            conjugare(sth);
                            strcat(sth, "te-ai fi simtit mai bine?");
                            if (ceva==1)
                                strcpy(e, sth);
                            else
                                ///vreau sa...
                            {
                                strcpy(e, "De ce am vrea ");
                                strcpy (w, strstr(s, "vreau"));
                                p=strtok(w, " ");
                                p=strtok(NULL, " ");
                                while (p)
                                {
                                    strcat (e, p);
                                    strcat (e, " ");
                                    p=strtok(NULL, " ");
                                }
                                conjugare(e);
                                strcat(e,"?");
                            }
                        }

                        ///daca da o explicatie utilizatorul
                        else if (strstr (s, "pentru ca")!=NULL || strstr(s, "deoarece")!=NULL || strstr (s, "intrucat")!=NULL)
                        {
                            strcpy(keyw,"explicatie%");
                            AfiseazaRaspuns(keyw, e);
                            aFostAfisatRaspunsul=1;
                        }

                        ///dar ...
                        else if (strncmp(s, "dar", 3)==0)
                        {
                            strcpy(e,"'");
                            strcat(e, s+4);
                            strcat(e, "' mhm...");
                        }
                        ///nu stiu
                        else if (strstr (s, "nu stiu"))
                        {
                            strcpy(keyw, "nustiu%");
                            AfiseazaRaspuns(keyw, e);
                            aFostAfisatRaspunsul=1;
                        }
                        else if (strlen(e)<1)
                        {
                            char dif[NMAX];
                            strcpy(e, "De ce");
                            strcpy (w, s);
                            strcpy(dif, s);

                            if (strncmp(s, "ca ", 3)==0)
                            {
                                strcat (e, s+2);
                                strcat(e,"?");
                            }
                            else
                            {
                                p=strtok(w, " ");
                                while (p)
                                {
                                    strcat (e, " ");
                                    strcat (e, p);
                                    p=strtok(NULL, " ");
                                }
                            }
                            conjugare(e);

                            if (strncmp(e+6, dif, strlen(dif))==0)
                            {
                                strcpy (keyw, "noreply%");
                                j++;
                                if (j>2 && strlen(semnificativ)>0)
                                {
                                    strcpy(e, "OK... '");
                                    strcat(e, replica);
                                    if (j2==1)
                                    {
                                        strcat(e, "'. Detaliaza.");
                                        j2=0;
                                    }
                                    else if (j2==0)
                                    {
                                        strcat(e, "'. Mai spune-mi.");
                                        j2=1;
                                    }
                                    j=0;
                                }
                                else
                                {
                                    AfiseazaRaspuns(keyw, e);
                                    aFostAfisatRaspunsul=1;
                                }
                            }

                            else
                                strcat(e,"?");

                        }

                        if (strlen(e) && aFostAfisatRaspunsul==0)
                        {
                            cout<<e<<'\n';
                            aFostAfisatRaspunsul=1;
                        }
                    }
                }

                ///ultimul sir de keywords seminificativ
                if (strcmp (keyw, "noreply%")!=0)
                {
                    strcpy (semnificativ, keyw);
                    strcpy (replica, s);
                }

                ///salvarea ultimelor replici
                strcpy (s2, s1);
                strcpy (s1, s);
                strcpy (e2, e1);
                strcpy (e1, e);
                strcpy(keyw2, keyw);

                /// Citire standard pentru urmatoarea propozitie
                printf("\nUser: ");

                strcpy(last[1].text, e);
                strcpy(s,"");

                setbkcolor(BLACK);
                setcolor(WHITE);
                outtextxy(15, 670,"ELSA: ");
                outtextxy(90, 670, last[1].text);
            }

            else if(valoare == 8)
                s[strlen(s) - 1] = NULL;

            else
            {
                char c[2];
                c[0] = (char)(valoare);
                strncat(s,c,1);
            }

            /// CASETA TEXT ->
            setfillstyle(SOLID_FILL,WHITE);
            bar(75,700,785,755);

            setbkcolor(WHITE);
            setcolor(BLACK);
            outtextxy(90, 720,s);
            /// <-
        }
        while (strcmp(s, "exit") !=0);
    }
    closegraph();
    return 0;
}
