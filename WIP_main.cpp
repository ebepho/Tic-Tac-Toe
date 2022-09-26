#include <iostream>
#include <vector>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end


using namespace std;

void print(vector < vector<string> > p);

string positionChoice();
vector <int> gridPosition(string a);

char turnFlip(bool *flip);
int checkWin(vector < vector<string> > p);
bool gameOver(vector < vector<string> > p);

int main(){
    vector<vector<string> > grid(3, vector<string>(3, " "));
    string choice;
    vector <int> position;

    bool win = false;
    bool validAnswer = false;

    bool turn = true;

    
    while(!win){
        print(grid);
        while(!validAnswer){
            choice = positionChoice();
            position = gridPosition(choice);
            if ((position[0] == 9 || position[1] == 9)|| (grid[position[0]][position[1]] != " ")){
                validAnswer = false;
                cout << "Invalid choice.\n";
            }
            else{
                validAnswer = true;
                grid[position[0]][position[1]] =  turnFlip(&turn);
            }
        }  
        validAnswer = false; 
        win = false;  
        cout << checkWin(grid); 
    }
}







void print(vector < vector<string> > p){
    int label[3] = {1,2,3};
    string input;

    cout << "    a   b   c \n";
    for(int x = 0; x < 3; x++){
        cout << "  ------------- \n";
        cout << label[x];
        for(int y = 0; y < 3; y++){
            cout << " | " << p[x][y];
        }
        cout << " | \n";
    }
    cout << "  ------------- \n";
    
}

string positionChoice(){
    string input;
    cout << "Choose (a1, b3, etc.): ";

    cin >> input;
    return input;
}


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

char turnFlip(bool *flip){
    if(*flip){//true switch to false
        *flip = false;
        return 'x';
    }
    else if(!*flip){ //false switch to true
        *flip = true;
        return 'o';
    }
}

int checkWin(vector < vector<string> > p){
    //PLAYER 1
        //columns - better solution later
        for(int y = 0; y < p.size(); y ++)
        {
            if(p[0][y] == "x" && p[1][y] == "x" && p[2][y] == "x")
            {
                return 10;
            }
        }

        //rows - better solution later
        for(int x = 0; x < p.size(); x ++)
        {
            if(p[x][0] == "x" && p[x][1] == "x" && p[x][2] == "x")
            {
                return 10;
            }
        }

        //diagonal
        if(p[0][0] == "x" && p[1][1] == "x" && p[2][2] == "x")
        {
                return 10;
        }

        if(p[2][0] == "x" && p[1][1] == "x" && p[0][2] == "x")
        {
                return 10;
        }
        

    //PLAYER 2
        //columns - better solution later
        for(int y = 0; y < p.size(); y ++)
        {
            if(p[0][y] == "o" && p[1][y] == "o" && p[2][y] == "o")
            {
                return -10;
            }
        }

        //rows - better solution later
        for(int x = 0; x < p.size(); x ++)
        {
            if(p[x][0] == "o" && p[x][1] == "o" && p[x][2] == "o")
            {
                return -10;
            }
        }

        //diagonal
        if(p[0][0] == "o" && p[1][1] == "o" && p[2][2] == "o")
        {
                return -10;
        }

        if(p[2][0] == "o" && p[1][1] == "o" && p[0][2] == "o")
        {
                return -10;
        }

    //no winner - draw
    return 0;
}

bool gameOver(vector < vector<string> > p){
    bool win = false;

    //COLUMNS 
    for(int y = 0; y < p.size(); y ++)
    {
        //p1
        if(p[0][y] == "x" && p[1][y] == "x" && p[2][y] == "x")
        {
            win = true;
        }

        //p2
        if(p[0][y] == "o" && p[1][y] == "o" && p[2][y] == "o")
        {
            win = true;
        }
    }

    //ROWS 
    for(int x = 0; x < p.size(); x ++)
    {
        //p1
        if(p[x][0] == "x" && p[x][1] == "x" && p[x][2] == "x")
        {
            win = true;
        }

        //p2
        if(p[x][0] == "o" && p[x][1] == "o" && p[x][2] == "o")
        {
            win = true;
        }
    }

    //DIAGONAL
    //p1
    if(p[0][0] == "x" && p[1][1] == "x" && p[2][2] == "x")
    {
            win = true;
    }

    if(p[2][0] == "x" && p[1][1] == "x" && p[0][2] == "x")
    {
            return true;
    }

    //p2
    if(p[0][0] == "o" && p[1][1] == "o" && p[2][2] == "o")
    {
            win = true;
    }

    if(p[2][0] == "o" && p[1][1] == "o" && p[0][2] == "o")
    {
            return true;
    }
    
    //FULL
    for(int x = 0; x < p.size(); x ++)
    {
        for(int y = 0; y < p.size(); y ++)
        {
            if(p[x][y] == "o" || p[x][y] == "x")
            {
                win = true;
            }
            else{
                win = false;
                return win;
            }
        }
    }
    return win;   
}

int minimaz(vector < vector<string> > p){
  
int depth;
//one option
    //all other options
    //branch out
}
