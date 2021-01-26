#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <graphics.h>

using namespace std;

class F //This is a class holding all the attributes of towards a single face
{
    public:
    char face[3][3];// a mult. dim. array holding the pieces of a face

    F(char color); //constructor
    void rotation(); //single cw rotation
    void doubrotation();//double cw rotation
    void triprotation();//single ccw rotation
};

F::F(char color)//constructor to set a face to exactly one color
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
    {
        face[i][j]=color;// assigns a char representation of the occupying color
    }
}

void F::rotation(){//this function rotates one single face only by swapping member variables
    char tempr[3]; //temp array to swap contents
    tempr[0]=face[0][0];
    tempr[1]=face[0][1];
    tempr[2]=face[0][2];

    face[0][0]=face[2][0];
    face[0][1]=face[1][0];
    face[0][2]=face[0][0];

    face[0][0]=face[2][0];
    face[1][0]=face[2][1];
    face[2][0]=face[2][2];

    face[2][0]=face[2][2];
    face[2][1]=face[1][2];
    face[2][2]=face[0][2];

    face[0][2]=tempr[0];
    face[1][2]=tempr[1];
    face[2][2]=tempr[2];
}

void F::doubrotation(){ //double rotation
rotation();
rotation();
}

void F::triprotation(){ //triple rotation or ccw rotation
doubrotation();
rotation();
}

int EXIT=0,MOVES=1; //exit condition and move counter

F temp('0'); // temporary object for swapping object contents

inline void initcube(F &back, F &left, F &right, F &up, F &down, F &front);//function to make a single move on the cube
inline void display(F &back, F &left, F &right, F &up, F &down, F &front);//function to display status on the console
void Right(F &back, F &left, F &right, F &up, F &down, F &front);// function to tune cube to the left
void Left(F &back, F &left, F &right, F &up, F &down, F &front);//function to tune the cube to the right
void Up(F &back, F &left, F &right, F &up, F &down, F &front);//function to tune the cube down
void Down(F &back, F &left, F &right, F &up, F &down, F &front);//function to tune the cube up
void cwshift(F &back, F &left, F &right, F &up, F &down, F &front);//function to swap adjacent faces during cw rotation
void doubshift(F &back, F &left, F &right, F &up, F &down, F &front);//function to call cwshift twice
void ccwshift(F &back, F &left, F &right, F &up, F &down, F &front);//function to swap adjacent faces during ccw rotation
inline void output(char c);//function to output colored boxes on to the console
void read(F &back, F &left, F &right, F &up, F &down, F &front);//function to read earlier progress through out the game
void save(F &back, F &left, F &right, F &up, F &down, F &front);//function to save the status throughout the game
void reset(F &back, F &left, F &right, F &up, F &down, F &front);//function to reset the progress throughout the game
inline void cube(char a[3][3],char b[3][3],char e[3][3]);// to build a 3D demonstration of the cube of the cube
inline int coloring(char d);//return a color value for the 3D cube
void Exit(F &back, F &left, F &right, F &up, F &down, F &front);//function to exit game and send farewell note

int main()
{
    initwindow(680,680, "Rubik's Cube Simulator"); //to initialize a 3D demonstration window for the Cube
    F right('B'); //Declarations of faces
    F left('G');
    F up('O');
    F down('R');
    F front('W');
    F back('Y');
    F temp('0');
    read(back, left, right, up, down, front);  //reading previous progress


    while(::EXIT == 0) //for loop for every move
        initcube(back, left, right, up, down, front); //a single move
        return 0;

}
void Down(F &back, F &left, F &right, F &up, F &down, F &front){ //tunes cube by swapping and rotating
    back.doubrotation();
    left.triprotation();
    right.rotation();
    up.doubrotation();

    ::temp=front;
    front=down;
    down=back;
    back=up;
    up=::temp;
}

void Up(F &back, F &left, F &right, F &up, F &down, F &front){ //tunes cube by swapping and rotating
    back.doubrotation();
    down.doubrotation();
    right.triprotation();
    left.rotation();

    ::temp=up;
    up=back;
    back=down;
    down=front;
    front=::temp;
}

void Left(F &back, F &left, F &right, F &up, F &down, F &front){
    ::temp=back;
    back=right;
    right=front;
    front=left;
    left=::temp;

    up.triprotation();
    down.rotation();
}

void Right(F &back, F &left, F &right, F &up, F &down, F &front){
    ::temp=left;
    left=front;
    front=right;
    right=back;
    back=::temp;

    up.rotation();
    down.triprotation();

}

inline void display(F &back, F &left, F &right, F &up, F &down, F &front){// updates and displays 3d and console demonstration

        system("cls");

        cube(up.face,front.face,right.face); //calls cube function to display 3d demonstration

        output('R');output('Y');output('B');output('G');output('O');output('R');output('Y');output('B');output('G');output('O');

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
    cout<<"                        ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
        cout<<" ";
        output('O');output('G');output('B');output('Y');output('R');output('O');output('G');output('B');output('Y');output('R');
        cout<<endl;
        output('R');output('Y');output('B');output('G');output('O');output('R');output('Y');output('B');output('G');output('O');

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
    cout<<" Rubik's Cube Simulator ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
        cout<<" ";
        output('O');output('G');output('B');output('Y');output('R');output('O');output('G');output('B');output('Y');output('R');

    cout<<"\n    |Press ESC to return or exit.                           |Press 0 to GIVE UP& RESET!."; //prints out instructions
    cout<<"\n                                     Instructions\n";
    cout<<"  Cube Turning Keys                                         |Press Num 8 to Choose UPPER side.    \n";
    cout<<"    |Up Arrow       |Press A to rotate Clockwise.           |Press Num 2 to Choose LOWER side.    \n";
    cout<<"    |Down Arrow     |Press D to rotate Counter Clockwise.   |Press Num 4 to Choose LEFT side.     \n";
    cout<<"    |Right Arrow    |Press W to rotate Up(Not for Front).   |Press Num 6 to Choose RIGHT side.    \n";
    cout<<"    |Left Arrow     |Press S to rotate Down(Not for Front). |Press Num 5 to Choose Center Pieces. \n";
    cout<<"";

        cout<<endl;

    for(int i=0; i<3; i++) //draws upper face on the console
    {
        cout<<"\t\t";
        cout<<"\t      ";
        for(int j=0; j<3; j++)
            output(up.face[i][j]);
        cout<<endl<<endl;
    }

    for(int i=0; i<3; i++) //draws all lateral faces all together
    {
        cout<<"\t\t";
        for(int j=0; j<3; j++) //draws left face elements
            output(left.face[i][j]);
            cout<<"  ";

        for(int j=0; j<3; j++) //draws front face elements
            output(front.face[i][j]);
            cout<<"  ";

        for(int j=0; j<3; j++) //draws right face elements
            output(right.face[i][j]);
            cout<<"  ";

        for(int j=0; j<3; j++) //draws back face elements
            output(back.face[i][j]);

    cout<<endl<<endl;
    }


        for(int i=0; i<3; i++)//draws back face elements
    {
        cout<<"\t\t";
        cout<<"\t      ";
        for(int j=0; j<3; j++)
            output(down.face[i][j]);
        cout<<endl<<endl;
        if (i==2)
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\tMoves: "<<::MOVES<<endl;
    }

    }

void cwshift(F &back, F &left, F &right, F &up, F &down, F &front){ // shifts face and adjacent sides clockwise by swapping and rotating
front.rotation();

char tempr[3];

tempr[0]=down.face[0][0];
tempr[1]=down.face[0][1];
tempr[2]=down.face[0][2];

down.face[0][0]=right.face[2][0];
down.face[0][1]=right.face[1][0];
down.face[0][2]=right.face[0][0];

right.face[0][0]=up.face[2][0];
right.face[1][0]=up.face[2][1];
right.face[2][0]=up.face[2][2];

up.face[2][0]=left.face[2][2];
up.face[2][1]=left.face[1][2];
up.face[2][2]=left.face[0][2];

left.face[0][2]=tempr[0];
left.face[1][2]=tempr[1];
left.face[2][2]=tempr[2];
}

void ccwshift(F &back, F &left, F &right, F &up, F &down, F &front){ //shifts face and adjacent sides counter clockwise by calling cwshift 3 times
cwshift(back, left, right, up, down, front);
cwshift(back, left, right, up, down, front);
cwshift(back, left, right, up, down, front);
}

void doubshift(F &back, F &left, F &right, F &up, F &down, F &front){ // shifts a two sided rotation
cwshift(back, left, right, up, down, front);
cwshift(back, left, right, up, down, front);
}

inline void output (char c){ //draws a single square on the console using windows.h functions


    if(c=='R')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),260); //sets color attr. to desired color and background color
        cout<<(char)219<<(char)219<<(char)221<<" "; //prints two wider boxes and a thinner box with the desired color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271); //return back to default console color

    }
    else if(c=='Y')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),270);
        cout<<(char)219<<(char)219<<(char)221<<" ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
    }
    else if(c=='O')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),262);
        cout<<(char)219<<(char)219<<(char)221<<" ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
    }
    else if(c=='B')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),257);
        cout<<(char)219<<(char)219<<(char)221<<" ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
    }
    else if(c=='G')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),258);
        cout<<(char)219<<(char)219<<(char)221<<" ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
    }
    else if(c=='W')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
        cout<<(char)219<<(char)219<<(char)221<<" ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),271);
    }

}

inline void initcube(F &back, F &left, F &right, F &up, F &down, F &front){ //simple switch scenario for making a single move
switch(getch())
    {

    case 72: //up direction key for tuning
        Up(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        break;
    case 80: //down direction key for tuning
        Down(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        break;
    case 75: //left direction key for tunning
        Left(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        break;
    case 77: //right direction key for tuning
        Right(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        break;
    case 65: //rotates faces ccw
    case 97:
        cwshift(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        ++::MOVES;
        break;
    case 100:
    case 68:
        ccwshift(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        ++::MOVES;
        break;
    case 105:
    case 56:
        cout<<"UPPER SIDE \nROTATE OR press ESC to return";
        switch(getch()){
            case 97:
            case 65:
                Up(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 68:
            case 100:
                Up(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            default:display(back, left, right, up, down, front);
            break;
        }
        break;
    case 106:
    case 74:
    case 52:
        cout<<"LEFT SIDE \nROTATE OR press OTHER KEY to return";
        switch(getch()){
            case 83:
            case 115:
                Left(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 87:
            case 119:
                Left(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
            default: display(back, left, right, up, down, front);
            break;

        }
        break;
    case 108:
    case 76:
    case 54: //num6
        cout<<"RIGHT SIDE \nROTATE OR press OTHER KEY to return";
        switch(getch()){
            case 83:
            case 115:
                Right(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Left(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 87:
            case 119:
                Right(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Left(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
            default:display(back, left, right, up, down, front);
            break;

        }
         break;
    case 107:
    case 50://num 2
        cout<<"DOWN SIDE \nROTATE OR press ESC to return";
        switch(getch()){
            case 97:
            case 65:
                Down(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Up(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 68:
            case 100:
                Down(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Up(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            default: display(back, left, right, up, down, front);
            break;
        }
        break;
    case 53:
        cout<<"MIDDLE SIDE \nROTATE OR press ESC to return";
        switch(getch()){
            case 97:
            case 65:
                Up(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Up(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 68:
            case 100:
                Up(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Up(back, left, right, up, down, front);
                Left(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 83:
            case 115:
                Left(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Left(back, left, right, up, down, front);
                Up(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            case 87:
            case 119:
                Left(back, left, right, up, down, front);
                cwshift(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                Right(back, left, right, up, down, front);
                ccwshift(back, left, right, up, down, front);
                Left(back, left, right, up, down, front);
                Down(back, left, right, up, down, front);
                display(back, left, right, up, down, front);
                ++::MOVES;
                break;
            default: display(back, left, right, up, down, front);
                        break;
        }
        break;
    case 48:
        system("cls");
        reset(back, left, right, up, down, front);
        display(back, left, right, up, down, front);
        cout<<"You have chosen to give up and reset all your progress\n";
        break;

    case 27:
        Exit(back, left, right, up, down, front);

        break;
    }

}

void read(F &back, F &left, F &right, F &up, F &down, F &front){
ifstream infile;
ofstream outfile;
infile.open("progress.txt");
if (!infile){
    outfile.open("progress.txt");
    outfile.close();

    }
else{
    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>back.face[i][j];

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>left.face[i][j];

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>right.face[i][j];

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>up.face[i][j];

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>down.face[i][j];

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    infile>>front.face[i][j];

    infile>>::MOVES;

    infile.close();
    }

display(back, left, right, up, down, front);
}

void save(F &back, F &left, F &right, F &up, F &down, F &front){
ofstream outfile;
outfile.open("progress.txt");

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<back.face[i][j]<<endl;

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<left.face[i][j]<<endl;

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<right.face[i][j]<<endl;

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<up.face[i][j]<<endl;

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<down.face[i][j]<<endl;

    for (int i=0 ; i<3 ; i++)
    for (int j=0 ; j<3 ; j++)
    outfile<<front.face[i][j]<<endl;

    outfile<<::MOVES;

    outfile.close();
}

void reset(F &back, F &left, F &right, F &up, F &down, F &front){
ofstream outfile;
outfile.open("progress.txt");
remove("progress.txt");
outfile.close();
    F* pointr= &right;
    F* pointl= &left;
    F* pointu= &up;
    F* pointd= &down;
    F* pointf= &front;
    F* pointb= &back;

    F rightn('B');
    F leftn('G');
    F upn('O');
    F downn('R');
    F frontn('W');
    F backn('Y');

    *pointr= rightn;
    *pointl= leftn;
    *pointu = upn;
    *pointd= downn;
    *pointf= frontn;
    *pointb= backn;

    ::MOVES=0;

}

inline int coloring(char d){//returns color code for the setfillstyle(graphics.h function) called in cube function

    if(d=='R')
        return 4;
    else if(d=='B')
        return 1;
        else if(d=='G')
            return 2;
        else if(d=='Y')
            return 14;
            else if(d=='W')
                return 7;
            else if(d=='O')
                return 6;
}

inline void cube(char a[3][3],char b[3][3],char e[3][3]){ //draws and fills all single elements for the 3D demonstration


    //A
    setfillstyle(9,coloring(a[0][0]));//selects fill color
    line(286,14,400,35); //draws a single piece
    line(400,35,308,113);
    line(308,113,192,93);
    line(192,93,286,14);
    floodfill(300,60,WHITE); //fills with the selected color

    //B
    setfillstyle(9,coloring(a[0][1]));
    line(400,35,519,56);
    line(519,56,427,134);
    line(427,134,308,113);
    line(308,113,400,35);
    floodfill(420,90,WHITE);

    //C
    setfillstyle(9,coloring(a[0][2]));
    line(519,56,639,77);
    line(639,77,549,155);
    line(549,155,427,134);
    line(427,134,519,56);
    floodfill(540,100,WHITE);

    //D
    setfillstyle(9,coloring(a[1][0]));
    line(192,93,308,113);
    line(308,113,219,187);
    line(219,187,103,167);
    line(103,167,192,93);
    floodfill(210,130,WHITE);

    //E
    setfillstyle(9,coloring(a[1][1]));
    line(308,113,427,134);
    line(427,134,338,208);
    line(338,208,219,187);
    line(219,187,308,113);
    floodfill(320,160,WHITE);

    //F
    setfillstyle(9,coloring(a[1][2]));
    line(427,134,549,155);
    line(549,155,460,230);
    line(460,230,338,208);
    line(338,208,427,134);
    floodfill(430,180,WHITE);

    //G
    setfillstyle(9,coloring(a[2][0]));
    line(103,167,219,187);
    line(219,187,133,259);
    line(133,259,17,239);
    line(17,239,103,167);
    floodfill(130,210,WHITE);

    //H
    setfillstyle(9,coloring(a[2][1]));
    line(219,187,338,208);
    line(338,208,252,281);
    line(252,281,133,259);
    line(133,259,219,187);
    floodfill(230,230,WHITE);

    //I
    setfillstyle(9,coloring(a[2][2]));
    line(338,208,460,230);
    line(460,230,372,302);
    line(372,302,252,281);
    line(252,281,338,208);
    floodfill(350,250,WHITE);

   //J
    setfillstyle(9,coloring(b[0][0]));
    line(17,239,133,259);
    line(133,259,133,378);
    line(133,378,17,358);
    line(17,358,17,239);
    floodfill(70,300,WHITE);

    //K
    setfillstyle(9,coloring(b[0][1]));
    line(133,259,252,281);
    line(252,281,252,399);
    line(252,399,133,378);
    line(133,378,133,259);
    floodfill(200,330,WHITE);

    //L
    setfillstyle(9,coloring(b[0][2]));
    line(252,281,372,302);
    line(372,302,372,420);
    line(372,420,252,399);
    line(252,399,252,281);
    floodfill(310,350,WHITE);

    //M
    setfillstyle(9,coloring(b[1][0]));
    line(17,358,133,378);
    line(133,378,133,497);
    line(133,497,17,476);
    line(17,476,17,358);
    floodfill(70,430,WHITE);

    //N
    setfillstyle(9,coloring(b[1][1]));
    line(133,378,252,399);
    line(252,399,252,518);
    line(252,518,133,497);
    line(133,497,133,378);
    floodfill(200,450,WHITE);

    //O
    setfillstyle(9,coloring(b[1][2]));
    line(252,399,372,420);
    line(372,420,372,539);
    line(372,539,252,518);
    line(252,518,252,399);
    floodfill(310,470,WHITE);

    //P
    setfillstyle(9,coloring(b[2][0]));
    line(17,476,133,497);
    line(133,497,133,615);
    line(133,615,17,595);
    line(17,595,17,476);
    floodfill(70,550,WHITE);

    //Q
    setfillstyle(9,coloring(b[2][1]));
    line(133,497,252,518);
    line(252,518,252,636);
    line(252,636,133,615);
    line(133,615,133,497);
    floodfill(190,570,WHITE);

    //R
    setfillstyle(9,coloring(b[2][2]));
    line(252,518,372,539);
    line(372,539,372,657);
    line(372,657,252,636);
    line(252,636,252,518);
    floodfill(310,580,WHITE);

    //S
    setfillstyle(9,coloring(e[0][0]));
    line(372,302,460,230);
    line(460,230,460,347);
    line(460,347,372,420);
    line(372,420,372,302);
    floodfill(420,330,WHITE);

    //T
    setfillstyle(9,coloring(e[0][1]));
    line(460,230,549,155);
    line(549,155,549,272);
    line(549,272,460,347);
    line(460,347,460,230);
    floodfill(500,250,WHITE);

    //U
    setfillstyle(9,coloring(e[0][2]));
    line(549,155,639,77);
    line(639,77,639,196);
    line(639,196,549,272);
    line(549,272,549,155);
    floodfill(600,170,WHITE);

    //V
    setfillstyle(9,coloring(e[1][0]));
    line(372,420,460,347);
    line(460,347,460,466);
    line(460,466,372,539);
    line(372,539,372,420);
    floodfill(410,450,WHITE);

    //W
    setfillstyle(9,coloring(e[1][1]));
    line(460,347,549,272);
    line(549,272,549,391);
    line(549,391,460,466);
    line(460,466,460,347);
    floodfill(500,380,WHITE);

    //X
    setfillstyle(9,coloring(e[1][2]));
    line(549,272,639,196);
    line(639,196,639,315);
    line(639,315,549,391);
    line(549,391,549,272);
    floodfill(590,290,WHITE);

    //Y
    setfillstyle(9,coloring(e[2][0]));
    line(372,539,460,466);
    line(460,466,460,584);
    line(460,584,372,657);
    line(372,657,372,539);
    floodfill(410,570,WHITE);

    //Z
    setfillstyle(9,coloring(e[2][1]));
    line(460,466,549,391);
    line(549,391,549,510);
    line(549,510,460,584);
    line(460,584,460,466);
    floodfill(500,490,WHITE);

    //Last
    setfillstyle(9,coloring(e[2][2]));
    line(549,391,639,315);
    line(639,315,639,433);
    line(639,433,549,510);
    line(549,510,549,391);
    floodfill(590,410,WHITE);

}

void Exit(F &back, F &left, F &right, F &up, F &down, F &front){ //exits the game with a farewell note
        system("cls");
        save(back, left, right, up, down, front);
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t    Thank You For Playing Our Very First Game."<<endl;
        cout<<"\t\t\t\t\t ------------------------------"<<endl;
        cout<<"\t\t\t\t\t| Brought to you by C0DE-l3R0S |"<<endl;
        cout<<"\t\t\t\t\t|\t 0732   &   0818       |\n";
        cout<<"\t\t\t\t\t ------------------------------";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        getch();
        ::EXIT=1;
        system("cls");
}
