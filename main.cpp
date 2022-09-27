#include <iostream>
#include <vector>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <algorithm> 

using namespace std;

void print(vector < vector<string> > grid);
vector <int> gridPosition(string a);
void turnFlip(string *player);
int checkWin(vector < vector<string> > grid);
int minimax(vector < vector<string> > board, int depth, bool isMaxPlayer);
vector<int> bestMove(vector < vector<string> > board, string *player);



int main(){
    //3 x 3 vector
    vector<vector<string> > grid(3, vector<string>(3, " "));

    //player choice
    string choice;

    //position
    vector <int> position;

    //booleans for looping
    int win = 0;
    bool validAnswer = false;

    //turn flipper - true: player 1, false: player 2 / computer
    string player = "x";
    vector <int> computer;

    //while no one has won
    while(win == 0){
        //print the grid
        print(grid);

        //while a valid answer has not been input
        while(!validAnswer){

            //take in player input
            cout << "Choose (a1, b3, etc.): ";
            cin >> choice;

            //find what position the player has input. Outputs 9 for invalid options
            position = gridPosition(choice);

            //if input is invalid or  position is not empty
            if ((position[0] == 9 || position[1] == 9)|| (grid[position[0]][position[1]] != " ")){
                //no valid answer, loop again for player input
                validAnswer = false;
                cout << "Invalid choice.\n";
            }
            else{
                //valid answer, exit loop
                validAnswer = true;     
                grid[position[0]][position[1]] = player;
                turnFlip(&player);
                
            } 
        }  
        //go back into the loop to get player input
        validAnswer = false; 

        computer = bestMove(grid, &player);
        grid[computer[0]][computer[1]] = player;

        //continue or end game.
        win = checkWin(grid);  
    }
}






//METHODS ------
//update print
void print(vector < vector<string> > grid){
    int label[3] = {1,2,3};
    string input;

    cout << "    a   b   c \n";
    for(int x = 0; x < 3; x++){
        cout << "  ------------- \n";
        cout << label[x];
        for(int y = 0; y < 3; y++){
            cout << " | " << grid[x][y];
        }
        cout << " | \n";
    }
    cout << "  ------------- \n";   
}

//find what position the player has input
vector <int> gridPosition(string a){
    char letters[] = {'a', 'b', 'c'};
    char numbers[] = {'1','2','3'};
    vector <int> position(2, 9);


    //check both arrays, not a value
    for(int i = 0; i < sizeof(letters)/sizeof(letters[0]); i ++){
        if(a[0] == letters[i])
        {
            position[1] = i; // first value
            for(int i = 0; i < sizeof(letters)/sizeof(letters[0]); i ++){
                if(a[1] == numbers[i])
                {
                    position[0] = i; //second value
                    return position; // sucess
                }
            }
            break; // fail
        }
        else if(a[0] == numbers[i])
        {
            position[0] = i; //second value
            for(int i = 0; i < sizeof(letters)/sizeof(letters[0]); i ++){
                if(a[1] == letters[i])
                {
                    position[1] = i; // first value
                    return position; // sucess
                }
            }
            break; // fail
        }
    }  
    return position;
}


//switch to new player
void turnFlip(string *player){
    if(*player == "o"){//true switch to false
        *player = "x";
    }
    else if(*player == "x"){ //false switch to true
        *player = "o";
    }
}

//check if anyone has won
int checkWin(vector < vector<string> > grid){
    //PLAYER 1
        //columns - better solution later
        for(int y = 0; y < 3; y ++)
        {
            if(grid[0][y] == "x" && grid[1][y] == "x" && grid[2][y] == "x")
            {
                return 10;
            }
        }

        //rows - better solution later
        for(int x = 0; x < 3; x ++)
        {
            if(grid[x][0] == "x" && grid[x][1] == "x" && grid[x][2] == "x")
            {
                return 10;
            }
        }

        //diagonal
        if(grid[0][0] == "x" && grid[1][1] == "x" && grid[2][2] == "x")
        {
                return 10;
        }

        if(grid[2][0] == "x" && grid[1][1] == "x" && grid[0][2] == "x")
        {
                return 10;
        }
        

    //PLAYER 2
        //columns - better solution later
        for(int y = 0; y < 3; y ++)
        {
            if(grid[0][y] == "o" && grid[1][y] == "o" && grid[2][y] == "o")
            {
                return -10;
            }
        }

        //rows - better solution later
        for(int x = 0; x < 3; x ++)
        {
            if(grid[x][0] == "o" && grid[x][1] == "o" && grid[x][2] == "o")
            {
                return -10;
            }
        }

        //diagonal
        if(grid[0][0] == "o" && grid[1][1] == "o" && grid[2][2] == "o")
        {
                return -10;
        }

        if(grid[2][0] == "o" && grid[1][1] == "o" && grid[0][2] == "o")
        {
                return -10;
        }

    //no winner - draw
    return 0;
}

//minimax algorithm and other elements
int minimax(vector < vector<string> > board, int depth, bool isMaxPlayer){
    int score = checkWin(board);

    //return score if maximizer or minimizer wins game
    if (score == 10 || score == -10)
        return score;
    else   
    {
        //check if board full
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                if(board[x][y] != " "){
                    return 0;
                }
            }
        }
        //or draw
    }

    //maximizer
    if (isMaxPlayer){
        int best = -1000;
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                //check if empty
                if(board[x][y] == " ")
                {
                    board[x][y];

                    best = max(best, minimax(board,depth+1,!isMaxPlayer));
                    board[x][y] = " ";
                }
            }
        }

        return best;
    }
    //minimizer
    else{
        int best = 1000;
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                //check if empty
                if(board[x][y] == " ")
                {
                    board[x][y];

                    best = min(best, minimax(board,depth+1,!isMaxPlayer));
                    board[x][y] = " ";
                }
            }
        }
        return best;
    }
}



vector<int> bestMove(vector < vector<string> > board, string *player){
    board;
    int bestVal = -1000;
    vector<int> bestSpot(2,0);

    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            if(board[x][y] == " ")
            {
                board[x][y] = *player; 
                int moveVal = minimax(board, 0, false);   

                //undo everything
                board[x][y] = " ";  

                if (moveVal > bestVal)
                {
                    bestSpot[0] = x;
                    bestSpot[1] = y;
                }  
            }
        }
    }
    return bestSpot;
}


