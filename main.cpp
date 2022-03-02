#include <iostream>
#include "time.h"
using namespace std;
/////////////part of board (har khone)
class Pob {
public:
    char data;
    char show;
    bool bomb=false;
    bool number= false;
};
/////////////click
class Click{
public:
    bool select= false;
    bool flag= false;
    bool question= false;
};
//////////board
class Board{
public:
    int str;
    int soton;
    Pob board[15][15];
    bool end=false;
    int availablebomb;
    int foundbomb=0;
    int tedadbomb;
    Board(int st,int so,int tb) {
        str = st;
        soton = so;
        tedadbomb=tb;
        availablebomb=tb;
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < soton; ++j) {
                board[i][j].data='.';
                board[i][j].show='.';
            }
        }
    }
    void showboard(){
        cout<<"  ";
        for (int i = 0; i < soton; ++i) {
            cout<<i+1<<" ";
        }
        cout<<'\n';
        for (int i = 0; i<str ; ++i) {
            cout<<i+1<<" ";
            for (int j = 0; j<soton; ++j) {
                cout << board[i][j].show << " ";
            }
            cout<<'\n';
        }
    }
    void showamswer(){
        cout<<"  ";
        for (int i = 0; i < soton; ++i) {
            cout<<i+1<<" ";
        }
        cout<<'\n';
        for (int i = 0; i<str ; ++i) {
            cout<<i+1<<" ";
            for (int j = 0; j<soton; ++j) {
                cout << board[i][j].data<< " ";
            }
            cout<<'\n';
        }
    }
    void setbomb(int st,int so) {
        for (int i = 0; i < tedadbomb; ++i) {
            int random = rand() % (str*soton);
            int a = random / str;
            int b = random % soton;

            if (board[a][b].bomb == true||(a==st&&b==so))
                i--;
            else {
                board[a][b].bomb = true;
                board[a][b].data = 'b';
            }
        }
    }
    int setnum(){
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < soton; j++) {
                if (board[i][j].bomb != true)
                {
                    board[i][j].data=count(i,j);
                    board[i][j].number= true;
                }
            }
        }
    }
    void checkclick(int st,int so,Click click){
        if (click.select== true&&board[st][so].data=='0')
        {
            reveal(st,so);
        }
         if (board[st][so].number==true&&click.select== true&&board[st][so].data!='0')
            board[st][so].show=board[st][so].data;
        if (board[st][so].bomb==true&&click.select==true)
        {
            cout<<'\n';
            cout<<"****game over****"<<'\n';
            cout<<"amswer"<<'\n';
            showamswer();
            end= true;
        }
        if (board[st][so].bomb==true&&click.flag==true)
        {
            availablebomb--;
            foundbomb++;
            board[st][so].show='f';
        }
        if (board[st][so].bomb== false&&click.flag==true)
        {
            board[st][so].show='f';
        }
        if (click.question== true)
        {
            board[st][so].show='?';
        }
    }
    bool isValid(int st, int so)
    {
        return (st >= 0) && (st < str) && (so >= 0) && (so < soton);
    }
    char count(int row, int col) {
        int count = 0;
        if (isValid (row-1, col) == true)
        {
            if (board [row-1][col].bomb == true)
                count++;
        }
        if (isValid (row+1, col) == true)
        {
            if (board [row+1][col].bomb == true)
                count++;
        }
        if (isValid (row, col+1) == true)
        {
            if (board [row][col+1].bomb == true)
                count++;
        }
        if (isValid (row, col-1) == true)
        {
            if (board [row][col-1].bomb == true)
                count++;
        }
        if (isValid (row-1, col+1) == true)
        {
            if (board [row-1][col+1].bomb == true)
                count++;
        }
        if (isValid (row-1, col-1) == true)
        {
            if (board [row-1][col-1].bomb == true)
                count++;
        }
        if (isValid (row+1, col+1) == true)
        {
            if (board [row+1][col+1].bomb == true)
                count++;
        }
        if (isValid (row+1, col-1) == true)
        {
            if (board [row+1][col-1].bomb == true)
                count++;
        }
        char c;
        switch (count)
        {
            case 0 :c='0'; break;
            case 1 :c='1'; break;
            case 2 :c='2'; break;
            case 3 :c='3'; break;
            case 4 :c='4'; break;
            case 5 :c='5'; break;
            case 6 :c='6'; break;
            case 7 :c='7'; break;
            default :c='8';
        }
        return c;
    }
    void reveal(int i,int j)
    {
        if (board[i][j].show=='.'&&board[i][j].bomb== false &&i>=0&&i<str&&j>=0&&j<soton)
        {
            board[i][j].show=board[i][j].data;
            if(board[i][j].data=='0')
            {
                reveal(i,j-1);
                reveal(i,j+1);
                reveal(i-1,j-1);
                reveal(i+1,j-1);
                reveal(i+1,j+1);
                reveal(i-1,j+1);
                reveal(i-1,j);
                reveal(i+1,j);
            }
        }
    }
    bool endgame() {
        bool wingame = true;
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < soton; j++) {
                if (board[i][j].number == true) {
                    if (board[i][j].show == '.' || board[i][j].show == 'f' || board[i][j].show == '?') {
                        wingame = false;
                        break;
                    }
                }
            }
        }
        return wingame;
    }
};
////////// tabe game
void playgame(){
    int n,m,numofbomb;
    cout << "row :";
    cin>>n;
    cout<<"column :";
    cin>>m;
    while(1) {
    cout<<"num of the bomb :";
    cin>>numofbomb;
    if (numofbomb<(n*m))
        break;
    }
    int sr,so,react;
    Board board(n,m,numofbomb);
    time_t start, end;
    start = time(NULL);
    board.showboard();
    cout << "row :";
    cin >> sr;
    cout << "column :";
    cin >> so;
    Click click1;
    cout<<"point : first choice you can't set flag or question mark (its number)"<<'\n';
    click1.select=true;
    board.setbomb(sr-1,so-1);
    board.setnum();
    board.checkclick(sr-1,so-1,click1);
    while (true) {
        cout << "available bomb :" << board.availablebomb << "  found bomb :" << board.foundbomb << '\n';
        board.showboard();
        Click click;
        cout << "row :";
        cin >> sr;
        cout << "column :";
        cin >> so;
        cout << "1.select 2.flag 3.question mark : ";
        cin >> react;
        switch (react) {
            case 1:click.select = true;break;
            case 2:click.flag = true;break;
            case 3:click.question = true;break;
            default:break;
        }
        if (board.board[sr-1][so-1].number==true && board.board[sr-1][so-1].show != '.'&&board.board[sr-1][so-1].show != 'f'&&board.board[sr-1][so-1].show != '?')
        cout<<"it's number !"<<'\n';
        else if (sr>board.str||so>board.soton)
            cout<<"unavailable"<<'\n';
            else{
            board.checkclick(sr - 1, so - 1, click);
            end = time(NULL);
            cout<<"time (s) : "<< difftime(end, start)<<'\n';
            if (board.end)
                break;
            if (board.endgame()) {
                cout<<"****you win****"<<'\n';
                cout<<"answer"<<'\n';
                board.showamswer();
                break;
            }
        }
    }
}
int main() {
    playgame();
    return 0;
}