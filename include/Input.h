#ifndef INPUT_H
#define INPUT_H

#include "gtimer.h"


class Input
{
    public:
        void update();

        bool Quit();

        int GetMouseX()
        {
            return mousex;
        }
        int GetMouseY()
        {
            return mousey;
        }

        bool LCPressed(); //LEFTCLICK
        bool RCPressed(); //RIGHTCLICK
        bool MCPressed(); //MIDDLECLICK

        bool Qispressed(); //Q
        bool Wispressed(); //W
        bool Eispressed(); //E
        bool Rispressed(); //R
        bool Tispressed(); //T
        bool Yispressed(); //Y
        bool Uispressed(); //U
        bool Iispressed(); //I
        bool Oispressed(); //O
        bool Pispressed(); //P
        bool Aispressed(); //A
        bool Sispressed(); //S
        bool Dispressed(); //D
        bool Fispressed(); //F
        bool Gispressed(); //G
        bool Hispressed(); //H
        bool Jispressed(); //J
        bool Kispressed(); //K
        bool Lispressed(); //L
        bool Zispressed(); //Z
        bool Xispressed(); //X
        bool Cispressed(); //C
        bool Vispressed(); //V
        bool Bispressed(); //B
        bool Nispressed(); //N
        bool Mispressed(); //M

        bool UPispressed(); //UP
        bool DOWNispressed(); //DOWN
        bool LEFTispressed(); //LEFT
        bool RIGHTispressed(); //RIGHT
        bool SPACEispressed(); //Space


        bool NUM1ispressed(); //1
        bool NUM2ispressed(); //2
        bool NUM3ispressed(); //3
        bool NUM4ispressed(); //4
        bool NUM5ispressed(); //5
        bool NUM6ispressed(); //6
        bool NUM7ispressed(); //7
        bool NUM8ispressed(); //8
        bool NUM9ispressed(); //9
        bool NUM0ispressed(); //0

        bool GetWheelDown();
        bool GetWheelUp();



        int GetxFOROFFSET(int Lastlock);
        int GetyFOROFFSET(int Lastlock);
        void ClearFORSET();

        bool MouseMovement();


    private:
        bool quit = false;

        SDL_Event Event0;

        double mousex = 0, mousey = 0;

        bool LCTru = false; //LEFTCLICK
        bool RCTru = false; //RIGHTCLICK
        bool MCTru = false; //MIDDLECLICK

        bool Qtru = false; //Q
        bool Wtru = false; //W
        bool Etru = false; //E
        bool Rtru = false; //R
        bool Ttru = false; //T
        bool Ytru = false; //Y
        bool Utru = false; //U
        bool Itru = false; //I
        bool Otru = false; //O
        bool Ptru = false; //P
        bool Atru = false; //A
        bool Stru = false; //S
        bool Dtru = false; //D
        bool Ftru = false; //F
        bool Gtru = false; //G
        bool Htru = false; //H
        bool Jtru = false; //J
        bool Ktru = false; //K
        bool Ltru = false; //L
        bool Ztru = false; //Z
        bool Xtru = false; //X
        bool Ctru = false; //C
        bool Vtru = false; //V
        bool Btru = false; //B
        bool Ntru = false; //N
        bool Mtru = false; //M

        bool UPtru = false; //DOWN
        bool DOWNtru = false; //DOWN
        bool LEFTtru = false; //LEFT
        bool RIGHTtru = false; //RIGHT
        bool SPACEtru = false; //Space


        bool NUM1tru = false; //1
        bool NUM2tru = false; //2
        bool NUM3tru = false; //3
        bool NUM4tru = false; //4
        bool NUM5tru = false; //5
        bool NUM6tru = false; //6
        bool NUM7tru = false; //7
        bool NUM8tru = false; //8
        bool NUM9tru = false; //9
        bool NUM0tru = false; //0

        bool MouseWheelUP = false;
        bool MouseWheelDown = false;
        int TimeZoomLockA = 0;
        int TimeZoomLockB = 20;


        int MoveMemoryX = 0;
        int MoveMemoryY = 0;
        bool MouseMOVEMENT = false;

};

#endif // INPUT_H
