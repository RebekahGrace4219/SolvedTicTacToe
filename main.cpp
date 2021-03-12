/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>
#include<tuple>
using namespace std;


/*
* void PrintBoard(char ar[3][3]): Prints out the board with all characters and number for empty spots for 
*
* input: ar[3][3]
*       This is the array holding all the positions: it goes [rows][columns]
* output: none, but it does print to cout
*/
void PrintBoard(char** board){
    for(int i = 0; i<3; i++){
        cout<<"   "<<board[i][0]<<"  |  "<<board[i][1]<<"  |  "<<board[i][2]<<endl;
        if(i<2){
            cout<<" ----------------"<<endl;
        }
    }
    cout<<endl;
}

/*
* char** FillBoard(): resets the board to 1 through 9
*
* returns a completely full board
*/
char** FillBoard(){
    char** board = new char*[3];
    for(int i = 0; i < 3; ++i)
        board[i] = new char[3]; 
        
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            board[i][j] = 3*i+j+'1';
        }
    }
    return board;
}

/*
* char** playerPick(char** board): allows the player to pick their next spot
*
* input: the board
* output: the board
*
*/
char** playerPick(char** board, char playerChar){
    bool isTurnComplete = false;
    int move;
    
    PrintBoard(board);
    
    while(!isTurnComplete){
        cout<<"What square do you want?"<<endl;
        cin>>move;
        
        if(move>0 && move<10 && board[(move-1)/3][(move-1)%3] != 'X' && board[(move-1)/3][(move-1)%3] != 'O'){
            board[(move-1)/3][(move-1)%3] = playerChar;
            isTurnComplete = true;
        }
    }
    
    return board;
    
}

bool win(char** board){
    for(int i = 0; i<3; i++){
        //The rows are the same
        if(board[i][0] == board[i][1] && board[i][0]==board[i][2]){
            return true;
        }
        //The columns are the same
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return true;
        }
    }
    //First Diagonol
    if(board[0][0] == board[1][1] && board[1][1]== board[2][2]){
        return true;
    }
    //Other Diagonol
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2]){
        return true;
    }
    
    
    return false;
}

int firstMove(){
    int randNum = rand()%12;
    
    if(randNum<9){
        return 5;
    }
    else if(randNum == 9){
        return 1;
    }
    else if(randNum == 10){
        return 3;
    }
    else if(randNum == 11){
        return 7;
    }
    else{
        return 9;
    }
}

int opposite(int a){
    if(a==2){
        return 0;
    }
    else if(a==0){
        return 2;
    }
    else{
        return -1;
    }
}
//This is a complicated one;
int thirdMove(char** board, char computerChar, char playerChar){
    int rowComp, colComp, rowPlay, colPlay;
    
    //First figure out where the computerChar is and where the playerChar is
    for(int i=0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(board[i][j] == computerChar){
                rowComp = i;
                colComp = j;
            }
            else if(board[i][j] == playerChar){
                rowPlay = i;
                colPlay = j;
            }
        }
    }
    
    //Determine what the pieces are
    bool isCompCorner{false}, isCompCenter{false}, isPlayCenter{false}, isPlayCorner{false}, isPlaySide{false};
    if(rowComp == 1 && colComp == 1){
        isCompCenter = true;
    }
    else{
        isCompCorner = true;
    }
    
    if(rowPlay == 1 && colPlay == 1){
        isPlayCenter = true;
    }
    else if((rowPlay == 2 || rowPlay == 0) && (colPlay == 2 || colPlay == 0)){
        isPlayCorner = true;
    }
    else{
        isPlaySide = true;
    }
    
    //Declare answer row and col
    int rowAns, colAns;
    
    //Roll the random number generator: six options
    int randNum = rand()%6;
    
    //Case 1: Comp played the center 
    //1.1: Player played the side 
    if(isCompCenter && isPlaySide){
        //Computer play top left corner
        if(randNum == 0){
            return 1;
        }
        //Computer play top right corner
        else if(randNum ==1){
            return 3;
        }
        //Computer play bottom left corner
        else if(randNum ==2){
            return 7;
        }
        //Computer play bottom right corner
        else if(randNum == 3){
            return 9;
        }
        else if(rowPlay!=1){
            //Player played the top side or bottom side    
            if(randNum ==4){
                //Computer play the left side
                return 4;
            }
            else{
                //Computer play the right side
                return 6;
            }
        }
        else{
            //Payer played the left or right side
            if(randNum ==4){
                //Computer play the top side
                return 2;
            }
            else{
                //Computer play the bottom side
                return 8;
            }
        }
    }
    
    //1.2: Player played the corner
    if(isCompCenter && isPlayCorner){
        //Computer plays the opposite corner of where the player played
        return 3*opposite(rowPlay)+opposite(colPlay)+1;
    }
    
    
    //Case 2: Comp played a corner
    //2.1: Player played the center
    if(isCompCorner && isPlayCenter){
        //Computer plays the opposite corner from what played originally
        return 3*opposite(rowComp)+opposite(colComp)+1;
    }
    //2.2 Player played the adjacent side
    if(isCompCorner && isPlaySide && (rowComp == rowPlay || colComp == colPlay)){
        if(randNum<2){
            //Computer plays the center
            return 5;
        }
        else if(randNum <4){
            //Computer returns the other adjacent side
            if(rowPlay == rowComp){
                //Return the middle row and the column of the the computer
                return colComp + 4;
            }
            else{
                //Return the middle colum and row of the computer
                return 3*rowComp + 2;
            }
        }
        else{
            //Computer plays the corner that is not adjacent to the player, but not opposite the computer 
            if(rowPlay == rowComp){
                //return the opposite row to the computer, same column
                return 3*opposite(rowComp)+ colComp + 1;
            }
            else{
                //return the opposite column to the computer, same rowComp
                return 3*rowComp + opposite(colComp) + 1;
            }
        }
    }
    //2.3 Player played the side not adjacent
    if(isCompCorner && isPlaySide && rowComp != rowPlay && colComp != colPlay){
        if(randNum <2){
            //Computer plays the center
            return 5;
        }
        else if(randNum <4){
            //Computer plays a corner sharing a row but not a column
            return 3*rowComp + opposite(colComp)+1;
        }
        else{
            //Computer plays a corner sharing a column but not a row
            return 3*opposite(rowComp) + colComp + 1;
        }
    }
    //2.4 Player played the corner sharing row or column
    if(isCompCorner && isPlayCorner && (rowComp == rowPlay || colComp == colPlay)){
        if(randNum <2){
            //Computer plays the opposite corner to itself
            return 3*opposite(rowComp)+opposite(colComp)+1;
        }
        else if(randNum <4){
            //Computer plays the opposite corner to the player
             return 3*opposite(rowPlay)+opposite(colPlay)+1;
        }
        else{
            if(rowPlay == rowComp){
                //Computer plays middle row that shares the computer's column
                return colComp + 4;
            }
            else{
                //Computer plays middle column that share the computer's row
                return 3*rowComp + 2;
            }
        }
    }
    //2.5 player played the opposite corner
    if(isCompCorner && isPlayCorner && rowComp != rowPlay && colComp != colPlay){
        if(randNum <3){
            //Computer plays a corner sharing a row but not a column
            return 3*rowComp + opposite(colComp)+1;
        }
        else{
            //Computer plays a corner sharing a column but not a row
            return 3*opposite(rowComp) + colComp + 1;
        }
    }
}

//Answer the part that would make me win!
int evaluateMove(char** board, char oneChar){
    //When oneChar is the computer's character, it searches for lines where two are itself
    //  and the last piece is empty
    
    //When oneChar is the player's character, it searches for the place where there are two of the oponent's
    //  and blocks them
    
    for(int i = 0; i<3; i++){
        //The first two in a row is computer
        if(board[i][0] == board[i][1] && board[i][0] == oneChar && board[i][2] != 'X' && board[i][2] != 'O'){
            return 3*i+3;
        }
        //The first and last in a row is computer
        else if(board[i][0] == board[i][2] && board[i][0] == oneChar && board[i][1] != 'X' && board[i][1] != 'O'){
            return 3*i+2;
        }
        //The last two of a row are computer
        else if(board[i][1] == board[i][2] && board[i][1] == oneChar && board[i][0] != 'X' && board[i][0] != 'O'){
            return 3*i+1;
        }
        //The first two of a column are oneChar
        else if(board[0][i] == board[1][i] && board[0][i] == oneChar && board[2][i] != 'X' && board[2][i] != 'O'){
            return i+7;
        }
        //The first and last of a column are computer
        else if(board[0][i] == board[2][i] && board[0][i] == oneChar && board[1][i] != 'X' && board[1][i] != 'O'){
            return i+4;
        }
        //the last two of a column are computer
        else if(board[1][i] == board[2][i] && board[1][i] == oneChar && board[0][i] != 'X' && board[0][i] != 'O'){
            return i+1;
        }
    }
    
    //The first Diagonol
    if(board[0][0] == board[1][1] && board[0][0] == oneChar && board[2][2]!= 'X' && board[2][2] != 'O'){
        return 9;
    }
    else if(board[0][0] == board[2][2] && board[0][0] == oneChar && board[1][1]!= 'X' && board[1][1] != 'O'){
        return 5;
    }
    else if(board[1][1] == board[2][2] && board[1][1] == oneChar && board[0][0]!= 'X' && board[0][0] != 'O'){
        return 1;
    }
    
    //The second Diagonol
    if(board[0][2] == board[1][1] && board[0][2] == oneChar && board[2][0]!= 'X' && board[2][0] != 'O'){
        return 7;
    }
    else if(board[0][2] == board[2][0] && board[0][2] == oneChar && board[1][1]!= 'X' && board[1][1] != 'O'){
        return 5;
    }
    else if(board[1][1] == board[2][0] && board[1][1] == oneChar && board[0][2]!= 'X' && board[0][2] != 'O'){
        return 3;
    }
    
    return -1;
}

/*
*
*
*
*
*/
bool causeTrap(char** board, char oneChar){
    //The board has already been altered, we just need to check if two paths made a trap
    int numLanes= 0;
   
    for(int i = 0; i<3; i++){
        //The first two in a row is computer
        if(board[i][0] == board[i][1] && board[i][0] == oneChar && board[i][2] != 'X' && board[i][2] != 'O'){
           numLanes++;
        }
        //The first and last in a row is computer
        if(board[i][0] == board[i][2] && board[i][0] == oneChar && board[i][1] != 'X' && board[i][1] != 'O'){
            numLanes++;
        }
        //The last two of a row are computer
        if(board[i][1] == board[i][2] && board[i][1] == oneChar && board[i][0] != 'X' && board[i][0] != 'O'){
            numLanes++;
        }
        //The first two of a column are oneChar
        if(board[0][i] == board[1][i] && board[0][i] == oneChar && board[2][i] != 'X' && board[2][i] != 'O'){
            numLanes++;
        }
        //The first and last of a column are computer
        if(board[0][i] == board[2][i] && board[0][i] == oneChar && board[1][i] != 'X' && board[1][i] != 'O'){
            numLanes++;
        }
        //the last two of a column are computer
        if(board[1][i] == board[2][i] && board[1][i] == oneChar && board[0][i] != 'X' && board[0][i] != 'O'){
            numLanes++;
        }
    }
    
    //The first Diagonol
    if(board[0][0] == board[1][1] && board[0][0] == oneChar && board[2][2]!= 'X' && board[2][2] != 'O'){
        numLanes++;
    }
    else if(board[0][0] == board[2][2] && board[0][0] == oneChar && board[1][1]!= 'X' && board[1][1] != 'O'){
        numLanes++;
    }
    else if(board[1][1] == board[2][2] && board[1][1] == oneChar && board[0][0]!= 'X' && board[0][0] != 'O'){
        numLanes++;
    }
    
    //The second Diagonol
    if(board[0][2] == board[1][1] && board[0][2] == oneChar && board[2][0]!= 'X' && board[2][0] != 'O'){
        numLanes++;
    }
    else if(board[0][2] == board[2][0] && board[0][2] == oneChar && board[1][1]!= 'X' && board[1][1] != 'O'){
        numLanes++;
    }
    else if(board[1][1] == board[2][0] && board[1][1] == oneChar && board[0][2]!= 'X' && board[0][2] != 'O'){
        numLanes++;
    }
   
    if(numLanes>=2){
        return true;
    }
    return false;
    
}

int trapMove(char** board, char computerChar, char playerChar){
    //first evaluate all the potential moves:
    std::vector<tuple<int, int>> potentialMoves; //stores [0, 0] to [2, 2]
    
    for(int i = 0; i<3; i++){
        for(int j= 0; j<3; j++){
            if(board[i][j]!= computerChar && board[i][j]!= playerChar){
                potentialMoves.push_back(make_tuple(i, j));
            }
        }
    }
    
    
    //for each move, evaluate if it would cause a trap. If yes, return its result
    for(int i = 0; i<potentialMoves.size(); i++){
        int j = get<0>(potentialMoves[i]);
        int k = get<1>(potentialMoves[i]);
        board[j][k] = computerChar;
        
        if(causeTrap(board, computerChar)){
            //This move did cause a trap, so set the board back and return the result
            board[j][k] = 3*j + k + 1+'0';
            return 3*j + k + 1;
        }
        else{
            //set the board back
            board[j][k] = 3*j + k + 1+'0';
        }
    }
    
    //No move produced a trap
    return -1;
}

int randomMove(char** board, char computerChar, char playerChar){
    for(int i=0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(board[i][j]!= playerChar && board[i][j]!= computerChar){
                return 3*i+j+1;
            }
        }
    }
}

int middleMove(char** board, char computerChar, char playerChar){
    int result = evaluateMove(board, computerChar);
    if(result!= -1){
        return result;
    }
    result = evaluateMove(board, playerChar);
    if(result != -1){
        return result;
    }
    result = trapMove(board, computerChar, playerChar);
    if(result!=-1){
        return result;
    }
    result = randomMove(board, computerChar, playerChar);
    return result;
}

int computerPick(int numMoves, char** board, char computerChar, char playerChar){
    if(numMoves == 1){
        return firstMove();
    }
    else if(numMoves == 3){
        return thirdMove(board, computerChar, playerChar);
    }
    else if(numMoves == 5 || numMoves == 7){
        return middleMove(board, computerChar, playerChar);
    }
    else if(numMoves == 9){
        return randomMove(board, computerChar, playerChar);
    }
    return 0;
}

int main()
{
    
    //First fill the board and randomize the seed
    char**board = FillBoard();
    srand(time(NULL));
    
    //Ordinarily I would ask the player should who go first, but computer goes first
    // false means the computer goes first, true means the player goes first
    bool ifPlayerTurn = false;
    
    //Ordinarily I would ask the player what letter they want
    //but for the time being, I am assining them
    char playerChar = 'O';
    char computerChar = 'X';
    
    
    //The move that the tic tac toe board is on
    int numMoves = 1;
    
    if(ifPlayerTurn){
        board = playerPick(board, playerChar);
        numMoves++;
        ifPlayerTurn = false;
    }
    
    int result; //The result of what the computer pick function doles out, converted to 1-9
    
    //PLay for as long as the game has not been won or there are turns left
    while(!win(board) && numMoves<10){
        if(ifPlayerTurn){
            board = playerPick(board, playerChar);
            if(win(board)){
                cout<<"\n\nPlayer has won!!"<<endl;
                PrintBoard(board);
                break;
            }
            numMoves++;
            ifPlayerTurn = false; 
        }
        else{
            result = computerPick(numMoves, board, computerChar, playerChar);
            board[(result-1)/3][(result-1)%3] = computerChar;
            if(win(board)){
                cout<<"\n\nComputer has won!!"<<endl;
                PrintBoard(board);
                break;
            }
            numMoves++;
            ifPlayerTurn = true;
        }
    }
    
    if(numMoves ==10){
        cout<<"\n\nTie Game"<<endl;
        PrintBoard(board);
    }
    
    return 0;
}
