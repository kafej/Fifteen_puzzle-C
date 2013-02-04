//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *ButtonMieszaj;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TButton *Button12;
        TButton *Button13;
        TButton *Button14;
        TButton *Button15;
        TButton *Button16;
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button17;
        TButton *Button18;
        TButton *Button19;
        TButton *Button20;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TButton *Button21;
        void __fastcall ButtonXClick(TObject *Sender);
        void __fastcall ButtonMieszajClick(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

class gra
{
        // klasa gry w 15

        private:
                int plansza[4][4];            // 2-wymiarowa tablica odzworowania planszy (wiersze i kolumny)
                int plansza_start[4][4];      // plansza startowa (jednoczesnie cel gry, plansza koncowa)
                int pusteY, pusteX;             // lokalizacja pustego pola na planszy
                int wartoscKliknietego;
                int kroki;
            //    int kliknietyY, kliknietyX;
                TButton* plansza_etykiety[4][4];            // 2-wymiarowa tablica odzworowania etykiet planszy (wiersze i kolumny)

        public:
                void inicjalizuj(int plansza_start[][4]);
                void przesun(TButton*);                          // obslugujemy klikniecie
                void losujPlansze(int iloscKrokow);
                void proponuj();                                 // AI
                int obliczPoziomSkomplikowania(int ocenianaPlansza[][4]);
        private:
                void ustawPlansze(int nowa_plansza[][4]);       // ustawiamy
                bool znajdzSasiadujacePuste(int *wspolrzedneKliknietego);
                int* wspolrzedneWartosci(int wartoscPola, int przeszukiwanaPlansza[][4]);
                void przesunPuste(int kierunek, int plansza_tmp[][4], int puste_tmp[]);
};
