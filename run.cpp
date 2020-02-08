#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

/// GLOBAL VARIABLES
char letter_tab[9] = {'A','B','C','D','E','F','G','H','I'}; // char array

string tab3 ="\t\t\t\t\t   ";   // big tabulator
string anw;

int anwser1,anwser2;

int X,Y; // update coordinates

int how_many_hits,how_many_enemy_hits; // counts enemy/player sinked ships

// ENEMEMY
int T[9][9];   // ship position array
int tab[9][9];   // game state array

//PLAYER
int A[9][9];    // ship position array
int tab_player[9][9]; // game state array

int los(int z)
    {
        int a;
        srand(time(NULL));
        a = rand() % z + 0;
        return a;
    }

/// #####################################################################################################

char check(char x) // converts char for the int (A->0,B->1,...)
{
    int result;
    for(int a=0;a<9;a++)
    {
        if(letter_tab[a]==x)
        {
            result = a;
            break;
        }
    }
    return result;
}

/// #####################################################################################################

void enemy_ships() // Setting Enemy ships
{
    int px,py,h_or_v;
    int reser=10;

    for(int k=0;k<3;k++)
    {
       (k==0)?(h_or_v=0):((k==1)?(h_or_v=1):(h_or_v=0)); // vertical = 1 - pionowy, horizontal = 0 - poziomy

       if(h_or_v==0)// poziomo
       {
        px = rand() % 9 + 0;
        py = rand() % 6 + 0;
        T[px][py]=+1;
        T[px][py+1]=+1;
        T[px][py+2]=+1;

       }else if(h_or_v==1){ // pionowo
        px = rand() % 6 + 0;
        py = rand() % 6 + 0;

        T[px][py]=+1;
        T[px+1][py]=+1;
        T[px+2][py]=+1;
       }
    }

    for(int q=0;q<9;q++)  // checking if ships aren't on the same places
    {
        for(int w=0;w<9;w++)
        {
            if (T[q][w]>=2){enemy_ships();} // if yes function will be done again
        }
    }

}

/// #####################################################################################################

void drawmap_player() // Draws player map
{
    string symbol[] = {"[ ]","[.]","[X]","[#]"}; // tablica symboli

    cout << tab3 << ("      --- PLAYER ---        ") << endl << endl;

    cout << tab3 << ("  A  B  C  D  E  F  G  H  I ") << endl;

    for (int a=0;a<9;a++)   // kolumny
    {
        cout << tab3 << a;
        for(int b=0;b<9;b++) // wiersze
        {
            if(tab_player[a][b]==0) {cout << symbol[0]; // empty
            }else if(tab_player[a][b]==1){cout << symbol[1]; // miss
            }else if(tab_player[a][b]==2){cout << symbol[2]; // hit
            }else{cout << symbol[3];} // my ship
        }
        cout << endl ;
    }

}

/// #####################################################################################################

void drawmap_enemy() // Draws computer map
{
    string symbol[] = {"[ ]","[.]","[X]"}; // tablica symboli

    cout << endl << endl << tab3 <<("     --- COMPUTER ---        ") << endl << endl;

    cout << tab3 << ("  A  B  C  D  E  F  G  H  I ") << endl;

    for (int a=0;a<9;a++)   // kolumny
    {
        cout << tab3 << a;
        for(int b=0;b<9;b++) // wiersze
        {
            if(tab[a][b]==0) {cout << symbol[0]; // empty
            }else if(tab[a][b]==1){cout << symbol[1]; // miss
            }else if(tab[a][b]==2){cout << symbol[2];} // hit
        }
        cout << endl ;
    }

    cout << endl << endl ;
}

/// #####################################################################################################

void player_ships() // setting player ships
{
    string response;
    int number1,number2;
    char letter;
    for(int s=0;s<9;s++)
    {
        cout << endl << "You have : " << 9-s << " ship pieces left" << endl;
        cout << endl << "Enter Coordinates of your " << s+1 << " ship : " ;
        cin >> response;

        letter = response[0];
        number2 = response[1];

        number2 = int(number2);
        number2 = number2 - 48;

        number1 = check(letter);

        A[number2][number1]=1;
        tab_player[number2][number1]=3;

        drawmap_player();
    }

}

/// #####################################################################################################

void enemy_shot() // randomize the coordinates of enemy shot
{
    srand(time(NULL));

    X = rand() % 9 + 0;
    Y = rand() % 9 + 0;
}

/// #####################################################################################################

void update()   // logic function which adds new shoots
{
    // PLAYER SHOT
    if(T[anwser2][anwser1]==0)
    {
        tab[anwser2][anwser1]=1;
        cout << tab3 <<" --> You Missed <--";
    }else if(T[anwser2][anwser1]==1){

        tab[anwser2][anwser1]=2;
        cout<< tab3 << " --> You Hit !!! <--";
        how_many_hits++;
    }else{
    cout << tab3 << " Out of Range !!!" ;    }

    //ENEMY SHOT

    enemy_shot();

    if(A[X][Y]==0)
    {
        cout << " --> Computer Missed <--" << endl;
        tab_player[X][Y]=1;
    }else if(A[X][Y]==1)
    {
        cout << " --> Computer Hit <--" << endl;
        tab_player[X][Y]=2;
        how_many_enemy_hits++;
    }
}
/// #####################################################################################################

void get_coordinates()
{
    char a,b;
    cout << endl << " --> Enter Shoot Coordinates: ";
    cin >> anw ;
    cout << endl ;

    a = anw[0];
    b = anw[1];

    anwser1 = check(a);

    anwser2 = int(b);
    anwser2 = anwser2 - 48;

}

void setup()    // setting default options in the start of the program
{

    cout << endl << "\t\t\t *** Welcome in Battle Ships ***" << endl << endl;
    cout << "\t -> Please press 'Caps Lock' button before you start playing" << endl << endl;
    cout << "\t -> Entering coordinates type for example A4 " << endl << endl << endl ;

    srand(time(NULL));
    system("color 3f");     // color setup
    system("title _____________________________________________________________________BATTLE SHIPS_______________________________________________________________");
    // wyzerowanie tablic
    for (int x=0;x<9;x++)   // kolumny
    {
        for(int y=0;y<9;y++) // wiersze
        {
            T[x][y]=0;
            tab[x][y]=0;       // 0 - empty    1 - ship

            A[x][y]=0;
            tab_player[x][y]=0;
        }

    }
    // ustawenie pozycji statkow przeciwnika

    enemy_ships(); // setting enemy ships

    how_many_hits=0;
    how_many_enemy_hits=0;

    // ustawienie pozycji statków gracza

    player_ships();

}


/// #####################################################################################################

int main()
{
    setup();

    // Game main loop
    while (1<2)
    {
        cout << tab3 << "  *Computer Shoots Randomly";

        drawmap_enemy();
        drawmap_player();

        get_coordinates();

        update();

        if(how_many_hits==9)    // Check if player WON
            {  cout << endl << tab3 <<"#################" << endl;
               cout << tab3 << "#  You Won !!!  #" << endl;
               cout << tab3 << "#################" << endl;
               break;
            }
        if(how_many_enemy_hits==9)  // Check if computer WON
           {  cout << endl << tab3 <<"#################" << endl;
               cout << tab3 << "#  You Lose !!!  #" << endl;
               cout << tab3 << "#################" << endl;
               break;
           }
    }

    return 0;
}
