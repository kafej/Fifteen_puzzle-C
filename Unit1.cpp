//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
gra pietnastka; // globalnie dostepna instancja gry
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        int plansza[4][4] = {
                                {1, 2, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10,11,12},
                                {13,14,15,99}
                                };      // poczatkowe ustawienie pol, 99 dla pustego pola

        pietnastka.inicjalizuj(plansza);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonXClick(TObject *Sender)
{
        // klikniecie na jedno z 16 pol gry

        TButton* etykieta = (TButton*) Sender;
        //etykieta->Color = 0x00ff00;
        //Form1->Button1->Color = 0x00ff00;

        pietnastka.przesun(etykieta);
        pietnastka.proponuj();
}
//---------------------------------------------------------------------------


void gra::inicjalizuj(int plansza_startowa[][4])
{
        plansza_etykiety[0][0] = Form1->Button1;
        plansza_etykiety[0][1] = Form1->Button2;
        plansza_etykiety[0][2] = Form1->Button3;
        plansza_etykiety[0][3] = Form1->Button4;
        plansza_etykiety[1][0] = Form1->Button5;
        plansza_etykiety[1][1] = Form1->Button6;
        plansza_etykiety[1][2] = Form1->Button7;
        plansza_etykiety[1][3] = Form1->Button8;
        plansza_etykiety[2][0] = Form1->Button9;
        plansza_etykiety[2][1] = Form1->Button10;
        plansza_etykiety[2][2] = Form1->Button11;
        plansza_etykiety[2][3] = Form1->Button12;
        plansza_etykiety[3][0] = Form1->Button13;
        plansza_etykiety[3][1] = Form1->Button14;
        plansza_etykiety[3][2] = Form1->Button15;
        plansza_etykiety[3][3] = Form1->Button16;

        
        for(int y=0; y<=3; y++)
        {
                for(int x=0; x<=3; x++)
                {
                        plansza_start[y][x] = plansza_startowa[y][x]; // kopiowanie planszy do zmiennej w klasie
                }
        }


        ustawPlansze(plansza_startowa);
        kroki = 0;
}

void gra::losujPlansze(int iloscKrokow)
{
        int wylosowany_kierunek;
        int plansza_tmp[4][4];          // na tym bedziemy mieszac
        int puste_tmp[] = {pusteY, pusteX};   // na tym bedziemy mieszac

        for(int y=0; y<=3; y++)
        {
                for(int x=0; x<=3; x++)
                {
                        plansza_tmp[y][x] = plansza[y][x];        // kopiowanie planszy do zmiennej tymczasowej
                }
        }

        randomize();
        for(int krok=0; krok<iloscKrokow; krok++)
        {
                wylosowany_kierunek = random(4);
                przesunPuste(wylosowany_kierunek, plansza_tmp, puste_tmp);
              //  pusteY = puste_tmp[0];
              //  pusteX = puste_tmp[1];
        }

      //  odswiezPlansze();
        ustawPlansze(plansza_tmp);
        kroki = 0;
}

void gra::przesunPuste(int kierunek, int plansza_tmp[][4], int puste_tmp[])
{
        if(kierunek == 0)
        {
                if(puste_tmp[0]-1 >= 0)
                {
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]] = plansza_tmp[puste_tmp[0]-1][puste_tmp[1]]; // w miejsce poprzedniego pustego wstawiamy nowa wartosc
                        plansza_tmp[puste_tmp[0]-1][puste_tmp[1]] = 99;                      // ustawiamy nowe puste
                        puste_tmp[0] -= 1;                                         // zapamietujemy nowa pozycje pustego
                }
        } else if(kierunek == 1)
        {
                if(puste_tmp[0]+1 <= 3)
                {
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]] = plansza_tmp[puste_tmp[0]+1][puste_tmp[1]];
                        plansza_tmp[puste_tmp[0]+1][puste_tmp[1]] = 99;
                        puste_tmp[0] += 1;
                }
        } else if(kierunek == 2)
        {
                if(puste_tmp[1]-1 >= 0)
                {
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]] = plansza_tmp[puste_tmp[0]][puste_tmp[1]-1];
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]-1] = 99;
                        puste_tmp[1] -= 1;
                }
        } else {      
                if(puste_tmp[1]+1 <= 3)
                {
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]] = plansza_tmp[puste_tmp[0]][puste_tmp[1]+1];
                        plansza_tmp[puste_tmp[0]][puste_tmp[1]+1] = 99;
                        puste_tmp[1] += 1;
                }
        }
}

void gra::przesun(TButton* kliknietaEtykieta)
{
        wartoscKliknietego = kliknietaEtykieta->Caption.ToInt();

        int *wspolrzedneKliknietego;
        int kliknietyY, kliknietyX;

        wspolrzedneKliknietego = wspolrzedneWartosci(wartoscKliknietego, plansza);
        //ShowMessage(IntToStr(wartoscKliknietego));

        kliknietyY = wspolrzedneKliknietego[0];
        kliknietyX = wspolrzedneKliknietego[1];

        if(znajdzSasiadujacePuste(wspolrzedneKliknietego))   // puste pole jest obok kliknietego, mozna zamienic je miejscami
        {
                //ShowMessage("tak");
                //ShowMessage(IntToStr(wartoscKliknietego));
                plansza[pusteY][pusteX] = plansza[kliknietyY][kliknietyX];            
                plansza_etykiety[pusteY][pusteX]->Caption = IntToStr(plansza[kliknietyY][kliknietyX]);
                plansza[kliknietyY][kliknietyX] = 99;
                plansza_etykiety[kliknietyY][kliknietyX]->Caption = "";

                plansza_etykiety[kliknietyY][kliknietyX]->Enabled = False;
                plansza_etykiety[pusteY][pusteX]->Enabled = True;

                pusteY = kliknietyY;
                pusteX = kliknietyX;
                //odswiezPlansze();
                kroki++;

                int trudnosc = obliczPoziomSkomplikowania(plansza);
                Form1->Label1->Caption = "Aktualna ocena trudnoœci planszy: " +IntToStr(trudnosc);


                Form1->Label8->Caption = "Iloœæ wykonanych kroków: "+ IntToStr(kroki);
                if(trudnosc == 0)
                {
                        Form1->Label7->Caption = "Plansza rozwi¹zana!";
                } else {
                        Form1->Label7->Caption = "";
                }
        }


}

int* gra::wspolrzedneWartosci(int wartoscPola, int przeszukiwanaPlansza[][4])
{
        bool znalezione = False;
        int *wspolrzedne = new int[2];

        wspolrzedne[0] = -1;
        wspolrzedne[1] = -1;

        for(int y=0; y<=3; y++)                      // zlokalizowanie x i y w tablicy (a zarazem na planszy)
        {
                for(int x=0; x<=3; x++)
                {
                        if(przeszukiwanaPlansza[y][x] == wartoscPola)
                        {
                                wspolrzedne[0] = y;
                                wspolrzedne[1] = x;

                                znalezione = True;
                                break;
                        }
                }
                if(znalezione)
                {
                        break;
                }
        }
        //ShowMessage(IntToStr(wspolrzedne[0]) +" "+  IntToStr(wspolrzedne[1]));
        return wspolrzedne;                      // y i x w tablicy planszy
}

bool gra::znajdzSasiadujacePuste(int *wspolrzedneKliknietego)
{
        bool znalezione = False;

        int kliknietyY, kliknietyX;
        //ShowMessage(IntToStr(wartoscKliknietego));
        //wspolrzedneKliknietego = wspolrzedneWartosci(wartoscKliknietego);

        kliknietyY = wspolrzedneKliknietego[0];
        kliknietyX = wspolrzedneKliknietego[1];

        // szukamy pustego pola przy kliknietym
        if(kliknietyX == pusteX)
        {
                if(kliknietyY-1 == pusteY)             // czy puste jest wyzej
                {
                        znalezione = True;
                        //ShowMessage("wyzej");
                } else if(kliknietyY+1 == pusteY) {            // lub nizej
                        znalezione = True;
                        //ShowMessage("nizej");
                }
        }

        if(kliknietyY == pusteY)
        {
                if(kliknietyX-1 == pusteX)                     // w lewo
                {
                        znalezione = True;
                        //ShowMessage("lewo");
                } else if(kliknietyX+1 == pusteX) {               // lub w prawo
                        znalezione = True;
                        //ShowMessage("prawo");
                }
        }

        if(znalezione)                     // znaleziono
        {         //  ShowMessage(IntToStr(kliknietyY) +":"+ IntToStr(kliknietyX) +"\n"+ IntToStr(tempy) +":"+ IntToStr(tempx));
                return True;
        } else {                           // nie znaleziono pola
                return False;
        }
}

void gra::ustawPlansze(int nowa_plansza[][4])
{
        for(int y=0; y<=3; y++)
        {
                for(int x=0; x<=3; x++)
                {
                        plansza[y][x] = nowa_plansza[y][x];
                        if(nowa_plansza[y][x] != 99)                     // wyswietlamy plansze dla gracza
                        {
                                //plansza_etykiety[y][x]->Caption = IntToStr(123);
                                plansza_etykiety[y][x]->Caption = IntToStr(nowa_plansza[y][x]); 
                                plansza_etykiety[y][x]->Enabled = True;
                        } else {                                           // 99 oznacza puste pole
                                pusteY = y;                                // znalezlismy puste pole, zapamietujemy
                                pusteX = x;
                                plansza_etykiety[y][x]->Caption = "";
                                plansza_etykiety[y][x]->Enabled = False;
                        }
                }
        }
        Form1->Label1->Caption = "Aktualna ocena trudnoœci planszy: " +IntToStr(obliczPoziomSkomplikowania(plansza));
}

void gra::proponuj()
{
        int plansza_tmp[4][4];                // na tym bedziemy mieszac
        int wyniki[4] = {-1,-1,-1,-1};        // wyniki trudnosci planszy po przesunieciu w gore, dol, lewo, prawo

        for(int y=0; y<=3; y++)
        {
                for(int x=0; x<=3; x++)
                {
                        plansza_tmp[y][x] = plansza[y][x];        // kopiowanie planszy do zmiennej tymczasowej
                }
        }

        if(pusteY-1 >=0)         // w gore
        {
                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY-1][pusteX];
                plansza_tmp[pusteY-1][pusteX] = plansza_tmp[pusteY][pusteX];

                wyniki[0] = obliczPoziomSkomplikowania(plansza_tmp);

                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY-1][pusteX];
                plansza_tmp[pusteY-1][pusteX] = plansza_tmp[pusteY][pusteX];

                Form1->Button18->Caption = IntToStr(plansza_tmp[pusteY-1][pusteX]);
                Form1->Label4->Caption = wyniki[0];
        } else {
                Form1->Button18->Caption = "";
                Form1->Label4->Caption= "";
        }
        if(pusteY+1 <=3)         // w dol
        {
                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY+1][pusteX];
                plansza_tmp[pusteY+1][pusteX] = plansza_tmp[pusteY][pusteX];

                wyniki[1] = obliczPoziomSkomplikowania(plansza_tmp);

                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY+1][pusteX];
                plansza_tmp[pusteY+1][pusteX] = plansza_tmp[pusteY][pusteX];

                Form1->Button20->Caption = IntToStr(plansza_tmp[pusteY+1][pusteX]);
                Form1->Label5->Caption = wyniki[1];
        } else {
                Form1->Button20->Caption = "";                                   
                Form1->Label5->Caption= "";
        }
        if(pusteX-1 >=0)         // w lewo
        {
                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY][pusteX-1];
                plansza_tmp[pusteY][pusteX-1] = plansza_tmp[pusteY][pusteX];

                wyniki[2] = obliczPoziomSkomplikowania(plansza_tmp);

                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY][pusteX-1];
                plansza_tmp[pusteY][pusteX-1] = plansza_tmp[pusteY][pusteX];

                Form1->Button17->Caption = IntToStr(plansza_tmp[pusteY][pusteX-1]);
                Form1->Label6->Caption = wyniki[2];
        } else {
                Form1->Button17->Caption = "";    
                Form1->Label6->Caption= "";
        }
        if(pusteX+1 <=3)         // w prawo
        {
                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY][pusteX+1];
                plansza_tmp[pusteY][pusteX+1] = plansza_tmp[pusteY][pusteX];

                wyniki[3] = obliczPoziomSkomplikowania(plansza_tmp);
                                                                            
                plansza_tmp[pusteY][pusteX] = plansza_tmp[pusteY][pusteX+1];
                plansza_tmp[pusteY][pusteX+1] = plansza_tmp[pusteY][pusteX];

                Form1->Button19->Caption = IntToStr(plansza_tmp[pusteY][pusteX+1]);
                Form1->Label3->Caption = wyniki[3];
        } else {
                Form1->Button19->Caption = "";
                Form1->Label3->Caption = "";
        }
        

        // AAAAAAAAAAAAAAAAAAAAA
}

int gra::obliczPoziomSkomplikowania(int ocenianaPlansza[][4])   // pozwala na ocene ruchow, im mniejszy wynik tym blizej rozwiazania
{
        int wynik=0;
        int wartosc=0, docelY, docelX; // dla czytelnosci kodu w petli
        int *lokalizacja_docelowa;

        for(int y=0; y<=3; y++)
        {
                for(int x=0; x<=3; x++)
                {
                        wartosc = ocenianaPlansza[y][x];        // pobieramy wartosc pola z planszy
                        if(wartosc != 99)            // dla pustego pola nie obliczamy
                        {
                                lokalizacja_docelowa = wspolrzedneWartosci(wartosc, plansza_start);// gdzie ta wartosc ma zostac ustawiona na planszy
                                docelY = lokalizacja_docelowa[0];
                                docelX = lokalizacja_docelowa[1];

                                if(docelY > y)                      // obliczamy odleglosc do celu
                                {
                                        wynik += (docelY-y);        // odejmujac mniejsza wspolrzedna od wiekszej
                                } else {
                                        wynik += (y-docelY);        // wynikiem po przeliczeniu X i Y jest odleglosc
                                }
                                if(docelX > x)
                                {
                                        wynik += (docelX-x);
                                } else {
                                        wynik += (x-docelX);
                                }
                                //  docelowaWartosc = plansza_start[y][x];  // wartosc ktora gracz ma ustawic w tym miejscu
                        }

                }
        }

        return wynik;
}

void __fastcall TForm1::ButtonMieszajClick(TObject *Sender)
{
        int ilosc;

        ilosc = Form1->Edit1->Text.ToInt();

        Form1->ButtonMieszaj->Enabled = False;
        pietnastka.losujPlansze(ilosc);
        pietnastka.proponuj();
        Form1->ButtonMieszaj->Enabled = True;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button21Click(TObject *Sender)
{

        int plansza[4][4] = {
                                {1, 2, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10,11,12},
                                {13,14,15,99}
                                };      // poczatkowe ustawienie pol, 99 dla pustego pola

        pietnastka.inicjalizuj(plansza);
}
//---------------------------------------------------------------------------

