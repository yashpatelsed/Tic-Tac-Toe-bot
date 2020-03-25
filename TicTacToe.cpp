/*

Tic-Tac-Toe

1.Introduction:
    Two players, Cross and Nought, take turns to place crosses (X) and noughts (O) in empty cells of a 3X3 array.
    The player who succeeds in placing three of their marks in a horizontal row, vertical column, or diagonal wins
    the game. If this doesn't happen, the game ends in a draw. The simplicity of the 3X3 game ensures that best
    play from both the players ensures a draw.

2.Strategy

    List of priorities:
    1)Win: If the player has two in a row (here, row represents horizontal row or vertical
     column or diagonal), they can place a third (if empty) to get three in a row.

    2)Block: If the opponent has two in a row, the player must play the third themselves to
    block the opponent's win.

    3)Opportunity move: Create an opportunity where the player has two ways to win (two non-blocked lines of 2).
    It is a move which creates an opportunity for the player to definitely win in the next move.

    4)Blocking an opponent's opportunity move (in priority order):

        Option 1: The player should create two in a row to force the opponent into
              defending, as long as it doesn't result in them creating an opportunity move. For example, if
              "X" has two opposite corners and "O" has the center, "O" must not play a
              corner in order to win. (Playing a corner in this scenario creates an opportunity move for "X"
               to win.)
        Option 2: If there is a configuration where the opponent can have an opportunity move, the player
               should block that move.

    5)If none of the above moves exist, the following strategy should be used in the same priority order:
        i)The player should play a move which can lead to an opportunity move if the opponent doesn't play the next
         move optimally.
        ii)The player should play a move which can lead to win in next move, given that the
         opponent doesn't play optimally.
        iii)Otherwise any random move can be played.



    To play optimally, O should adopt the following strategies:
    i)    If X plays corner opening move (best move for them), O should take center in the next move. This
        will ensure that X has no move to play that will give an opportunity move. Then follow the list of priorities.
    ii)    If X plays edge opening move, O should take center, and then follow the given list of priorities.
    iii)If X plays center opening move, O should take corner, and then follow the above list of priorities.

    To play optimally, X should adopt the following strategies:
    i)    X should play the centre as the opening move and then follow the list of priorities.
*/










#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
 * This function takes the board and displays it.
 * This is called when a human is playing against the computer.
 */
void displayBoard( const string& board)
{
    cout << "            " << board[1] << " " << board[2] << " " << board[3] << '\n';
    cout << "            " << board[4] << " " << board[5] << " " << board[6] << '\n';
    cout << "            " << board[7] << " " << board[8] << " " << board[9] << '\n';
    //cout<<"----------------------------------"<<endl;
}

/*
 * opponentPlay function takes the current board configuration and human's mark as arguments.
 * It takes input from the user the move it wants to play and makes that move iff it is possible,
 * otherwise it keeps asking user for correct move.
 */
void opponentPlay(string& board, char humanMark)
{
    cout << "Make your move" << endl;
    int i;
    cin >> i;
    while(i<1 || i>9 || board[i]!='_')
    {
        cout << "Make a valid move" << endl;
        cin >> i;
    }
    board[i]= humanMark;
    cout << "----------------------------------" << '\n';
    cout << "You played:" << '\n';
}

/*
 * win function checks whether player with given mark has won or not, in this board configuration.
 * Returns 1 if this player has won.
 * Otherwise returns 0.
 * */
int win(const string& board, char mark)
{
    if(board[1]==mark && board[2]==mark && board[3]==mark)
        return 1;
    if(board[4]==mark && board[5]==mark && board[6]==mark)
        return 1;
    if(board[7]==mark && board[8]==mark && board[9]==mark)
        return 1;
    if(board[1]==mark && board[4]==mark && board[7]==mark)
        return 1;
    if(board[2]==mark && board[5]==mark && board[8]==mark)
        return 1;
    if(board[3]==mark && board[6]==mark && board[9]==mark)
        return 1;
    if(board[1]==mark && board[5]==mark && board[9]==mark)
        return 1;
    if(board[5]==mark && board[3]==mark && board[7]==mark)
        return 1;
    else
        return 0;
}

/*
 * win_in_one function checks whether player with given mark can win just by putting his/her
 * mark in given cell in given board configuration.
 * If yes, it returns cell index (just the argument) and plays the move.
 * otherwise it returns 0.
 * */
int win_in_one(string& board, char mark, int cell)
{
    string boardcopy = board;

    if(boardcopy[cell]=='_')
    {
        boardcopy[cell]= mark;
        if(win(boardcopy, mark) )
        {
            board[cell]= mark;
            return cell;
        }
    }
    return 0;
}

/*
 * This win_in_one function calls the other win_in_one function with all possible cells.
 * If it is possible to win in 1 move, it plays the move, too.
 * Returns the index of any one cell which can let player with given mark win.
 * Otherwise returns 0 if it is not possible.
 * */
int win_in_one(string& board, char mark)
{
    string boardcopy= board;

    for(int i=1; i<10; i++)
    {
        if(win_in_one(board, mark, i))
        {   return i;
        }
    }
    return 0;
}

/*
 * defend_in_one function checks whether the given cell, which if not selected, can lead to
 * immediate win of the other player.
 * If yes, it puts mark into the cell, and returns the index.
 * Otherwise returns 0.
 * */
int defend_in_one(string& board, char mark, int cell)
{
    string boardcopy= board;
    char other;

    if(mark == 'x')
        other= 'o';
    else
        other= 'x';

    if(boardcopy[cell]=='_')
    {
        if(win_in_one(boardcopy, other, cell))
        {   //If this move is left, human can win in 1.
            //This is a move computer should never leave.
            board[cell]= boardcopy[cell]= mark;
            return cell;
        }
    }
    return 0;
}

/*
 * This defend_in_one function calls its overload, with all possible cells.
 * It checks whether there is any cell, which if not selected by "mark", can lead to
 * immediate win of the other player.
 * If it finds any such cell, it returns the index of such a cell, and puts mark there.
 * Otherwise it returns 0.
 * */
int defend_in_one(string& board, char mark)
{
    for(int i=1; i<10; i++)
    {
        if(defend_in_one(board, mark, i))
            return i;
    }
    return 0;
}

/*
 * Checks whether putting "mark" in given cell can lead to a definite win after the other
 * player plays.
 * If given cell is such a cell, it returns cell, and puts mark there.
 * Otherwise returns 0.
 * */
int win_in_three(string& board, char mark, int cell)
{
    string boardcopy = board;
    char other;

    if(mark == 'x')
        other = 'o';
    else
        other = 'x';

    int blank=0, counterable_opp_moves=0;
    if(boardcopy[cell]=='_')
    {
        boardcopy[cell]= mark;
        string anothercopy = boardcopy;
        for(int x=1; x<10; x++)
        {
            anothercopy= boardcopy;
            if(anothercopy[x]=='_')
            {
                blank++;
                anothercopy[x]= other;
                counterable_opp_moves += (win_in_one(anothercopy, mark) != 0);
            }
        }
        if(blank < 2)
            return 0;
        if(counterable_opp_moves == blank)
        {
            board[cell]= mark;
            return cell;
        }
    }
    return 0;
}

/*
 * This function calls its overload to check whether there is any cell which can lead to
 * a definite win in 3 moves.
 * Returns the index of any such cell, and puts mark there.
 * Otherwise returns 0 if no such cell is found.
 * */
int win_in_three(string& board, char mark)
{
    for(int i=1; i<10; i++)
    {
        if(win_in_three(board, mark, i))
            return i;
    }
    return 0;
}

/*
 * This function takes in parameters board-Board configuration and mark-Computer's mark(X or O).
 * It checks if there is any cell, which if not selected, will lead to win in the next 3 moves for opponent.
 * If there is no such cell, the function returns 0.
 *
 * Otherwise, it will first try to get a cell, playing which can lead to win in 1 move for the computer, to force the opponent to defend.
 * The function returns that cell only if the cell the opponent plays to defend does not lead to win in 1 move for opponent.
 * If no such cell exists, the function will return a cell which simply blocks win in 3 moves for opponent.
 *
 * */
int defend_in_three(string& board, char mark)
{
    int cnt=0;
    string boardcopy = board;
    char other;

    if(mark=='x')
        other='o';
    else
        other='x';

    for(int i=1; i<10; i++)
    {
        boardcopy= board;
        if(boardcopy[i]=='_')
        {
            boardcopy[i]= mark;
            if(win_in_three(boardcopy, other))
            {
                cnt++;
            }
        }
    }

    if(cnt==0)
        return 0;

    int bestMove=0, cnt2=0;

    for(int i=1;i<10;i++)
    {
        boardcopy= board;
        if(boardcopy[i]=='_')
        {
            boardcopy[i] = mark;
            string copy2 = boardcopy;
            if(win_in_one(copy2, mark)==0)
                continue;

            defend_in_one(boardcopy, other);

            for(int j=1;j<10;j++)
            {    string copy3 = boardcopy;
                if(copy3[j]=='_')
                {
                    copy3[j]= mark;
                    if(win_in_one(copy3, other))
                        continue;
                    else
                    {
                        board[i]= mark;
                        return i;
                    }
                }
            }
        }
    }


    for(int i=1; i<10; i++)
    {
        boardcopy= board;
        if(boardcopy[i] == '_')
        {
            boardcopy[i]= mark;
            if(win_in_three(boardcopy, other)==0)
            {
                cnt2++;
                bestMove=i;
                if(win_in_one(boardcopy, mark))
                {
                    board[i]= mark;
                    return i;
                }
            }
        }
    }
    return 0;
}

/*
 * If none of the above strategies work, this is just a heuristic to try any possible move.
 * */
int random(string& board, char mark)
{
    int i, cnt=0, bestMove=0;
    string boardcopy= board;
    char other;

    if(mark == 'x')
        other='o';
    else
        other='x';

    for(i=1; i<10; i++)
    {
        if(boardcopy[i] == '_')
        {
            cnt=0;
            boardcopy[i]= mark;

            if(win_in_three(boardcopy, mark))
            {
                cnt++;
                bestMove=i;
            }
        }
    }
    if(bestMove!=0)
    {
        board[bestMove]= mark;
        return bestMove;
    }

    boardcopy = board;
    for(i=1; i<10; i++)
    {
        if(boardcopy[i]=='_')
        {
            cnt=0;
            boardcopy[i]= mark;
            //bestMove=i;
            if(win_in_one(boardcopy, mark))
            {
                cnt++;
                bestMove=i;
            }
        }
    }
    if(bestMove != 0)
    {
        board[bestMove]= mark;
        return bestMove;
    }
    else
    {
        for(i=1; i<10; i++)
        {
            if(board[i] == '_')
            {   board[i] = mark;
                return i;
            }
        }
    }
    return 0;
}

/*
 * This tries to play a move for mark (computer) in following preference order:
 * 0. If it's the first or second move of the game, it tries to play the centre or a corner.
 * 1. try for an immediate win (win in 1).
 * 2. stop other player from immediate win (win in 1).
 * 3. try for an assured win in 3.
 * 4. stop other player from having assured win in 3 moves after current move.
 * 5. If none of the above work, play randomly.
 * Returns the index of the move it plays, and puts mark there.
 * If it cannot find any move to play, it returns 0.
 * */
int autoplay(string& board, char mark)
{
    int empty= 0;
    for(int i=1; i<=9; i++)
    {
        if(board[i]=='_')
            empty++;
    }

    if(empty>=8 && board[5]!='_' && board[1]=='_')
    {
        board[1]= mark;
        return 1;
    }
    else if(empty>=8 && board[5]=='_')
    {
        board[5]= mark;
        return 5;
    }

    empty--;

    int move=0;
    move = win_in_one(board, mark);
    if(move)
    {
        //cout << p << " wins" << endl;
        //cout << "win in one" << endl;
        return move;
    }
    else if((move = defend_in_one(board, mark)))
    {
        //cout << "defend in one" << endl;
        return move;
    }
    else if((move = win_in_three(board, mark)))
    {
        //cout << "win in three" << endl;
        return move;
    }
    else if((move = defend_in_three(board, mark)))
    {
        //cout << "defend in three" << endl;
        return move;
    }
    else
    {
        move = random(board, mark);
        //cout << "random" << endl;
        return move;
    }
    return 0;
}

/*
 * This allows a human vs computer game, by printing instructions to the terminal, taking user
 * mark, validating it, and then letting user and computer play alternate.
 * This terminates the game as soon as it detects a win or draw.
 * */
void humanVScomp()
{
    string board(10, '_');
    char userMark, compMark;
    int empty=9;

    cout << endl << "X to play first" << endl;
    cout << "Choose: X or O" << endl;
    do
    {
        cin >> userMark;
    }
    while(userMark != 'X' && userMark!= 'O');

    cout << "Format:" << endl;
    cout << "1|2|3" << endl;
    cout << "4|5|6" << endl;
    cout << "7|8|9" << endl;


    if(userMark=='X')
    {
        compMark = 'o';
        userMark = 'x';
        opponentPlay(board, userMark);
        displayBoard(board);
        empty--;
        autoplay(board, compMark);
        cout << "PC Played:\n";
        displayBoard(board);
        empty--;
    }
    else
    {    compMark='x';
        userMark = 'o';
        autoplay(board, compMark);
        cout << "PC Played:\n";
        displayBoard(board);
        empty--;
    }

    while(empty>0)
    {
        opponentPlay(board, userMark);
        displayBoard(board);
        if(win(board, userMark))
        {
            cout << userMark << " wins" << endl;
            return ;
        }
        empty--;

        if(empty == 0)
        {
            cout << "It's a Draw";
            return ;
        }

        autoplay(board, compMark);
        cout << "PC played:" << endl;
        displayBoard(board);
        if(win(board, compMark))
        {
            cout << compMark << " wins" << endl;
            return ;
        }
        empty--;
    }
    cout << "It's a Draw";
}

/*
 * This takes final board configuration and the sequence of moves of human, and prints them.
 * */
void displayGame(const string &board, const vector<int> &humanMoveSequence)
{
    displayBoard(board);
    cout << "Played Moves: ";
    for(size_t move=0; move < humanMoveSequence.size(); move++)
        cout << humanMoveSequence[move] << " ";
    cout << '\n';
}

/*
 * This function takes as parameters, the mark of the human (user), and the order in which
 * human wants to put the mark onto the board.
 * It tries to put marks from the sequence in order, and if some cell is already occupied,
 * it tries for the next choice of the user.
 * If user runs out of his choices (which is possible only if seq has less than 9 choices),
 * it declares an incomplete game.
 * After each move of the user, computer puts its mark by calling autoplay() function.
 * If autoplay doesn't return any move, this function declares an incomplete game.
 *
 * Returns 2 if game is left incomplete. (user or computer doesn't have any move.)
 * Returns 1 if computer has won.
 * Returns 0 if game ends in a draw.
 * Returns -1 if user has won.
 * Returns 10 if the current game has already been played once, and is redundant.
 * */
int test(vector<int> &seq, char userMark, set<vector<int> > &completedSeq)
{
    string board(10, '_');
    char compMark;
    int empty=9;
    vector<int> humanMoveSequence;

    size_t k=0;

    if(userMark=='X')
    {
        compMark = 'o';
        userMark = 'x';
        //opponentPlay(board, userMark);
        while(seq[k]<1 || seq[k]>9 || board[seq[k]]!='_')
            k++;

        humanMoveSequence.push_back(seq[k]);
        board[seq[k++]]=userMark;
        empty--;

        autoplay(board, compMark);
        empty--;
    }
    else
    {
        compMark = 'x';
        userMark = 'o';
        autoplay(board, compMark);
        empty--;
    }
    while(empty>0)
    {
        while(seq[k]<1 || seq[k]>9 || board[seq[k]]!='_')
        {
            k++;
            if(k>=seq.size() && empty>0)
                return 2;
        }
        humanMoveSequence.push_back(seq[k]);
        board[seq[k++]] = userMark;
        empty--;

        if(empty!=0)
        {
            int compMove = autoplay(board, compMark);
            if(compMove == 0 && empty>0)
                return 2;
            empty--;
        }

        if(win(board,userMark) || win(board,compMark) || empty==0)
        {
            if(completedSeq.find(humanMoveSequence) == completedSeq.end())
            {
                completedSeq.insert(humanMoveSequence);    //This is a new move sequence.

                displayGame(board,humanMoveSequence);

                if(win(board, userMark))
                    return -1;

                else if(win(board, compMark))
                    return 1;

                else
                    return 0;
            }
            else
                return 10;
        }
    }
    return 0;
}//end of test

/*
 * This takes as argument the mark of the user, and generates all possible 9! game-sequences
 * that user might want have at his choice list.
 * Then, calls test function with given choice list, and checks the result of the game.
 * Counts the number of time computer has won, lost, drawed, or game has terminated incomplete.
 * After trying all 9! permutations, it prints the game statistics.
 * */
void genTests(char userMark)
{
    static const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> seq (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    int testIndex = 0, wins = 0, loses = 0, draws = 0, incomplete = 0;

    set<vector<int> > completedSeq;

    do {
        testIndex++;
        int result = test(seq, userMark, completedSeq);
        //result = 1  : computer won.
        //result = 0  : game resulted in draw.
        //result = -1 : human won.
        //result = 2  : game incomplete. This means computer doesn't know what to do.
        //If computer ever loses or results in an incomplete game, print the index of such a
        //test and print the result.
        //if(result!=1 && result!=0)
            //cout << testIndex << ' ' << result << endl;
        if(result==10)
            continue;
        char compMark;
        if(userMark=='O')
            compMark='X';
        else
            compMark='O';
        cout << "Test No. : " << testIndex << '\n';
        if(result == 1)
            cout << compMark << " Wins\n";
        else if(result == 0)
            cout << "It's a draw\n";
        else if(result == -1)
            cout << userMark << " Wins\n";

        cout << "--------------------------------------" << '\n';
        switch(result)
        {
            case 1: wins++; break;
            case 0: draws++; break;
            case -1: loses++; break;
            case 2: incomplete++; break;
        }
    } while ( next_permutation(seq.begin(), seq.end()) );

    cout << "Wins \t\t : " << wins << '\n';
    cout << "Draws \t\t : " << draws << '\n';
    cout << "Loses \t\t : " << loses << '\n';
    cout << "Incomplete games : " << incomplete << '\n';

}



int main()
{
    cout << "TicTacToe game" << endl;
    cout << "Enter 1 for playing against computer" << endl;
    cout << "Enter 2 for testing the soundness and completeness of computer moves, in all 9! possible games." << endl;
    int choice;
    cin >> choice;
    while(choice!=1 && choice!=2 && choice!=3)
    {   cout << "Enter choice properly" << endl;
        cin >> choice;
    }

    if(choice == 1)
    {
        humanVScomp();        //To play against computer.
    }
    else if (choice == 2)
    {   cin.tie(NULL);
        ios_base::sync_with_stdio(false);
        cout << "When human has mark X. i.e. It is the first player" << endl;
        genTests('X');

        cout << endl << "When human has mark O. i.e. It is the second player" << endl;
        genTests('O');
    }
    else
    {
        while(1)
        {
            string board;
            if (! (cin>>board))
                break;
            for(int i=0; i<9; i++)
            {
                if(board[i]=='c')
                    board[i]='_';
            }
            board = '0'+board;
            autoplay(board, 'x');
            for(int i=1; i<=9; i++)
            {
                if(board[i]=='_')
                    board[i]='c';
                cout << board[i];
            }
            cout << '\n';
        }
    }
    /*static const int arr[] = {3,1,2,4,5,6,7,8,9};
    vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    char m='X';

    cout << test(vec, m); */    //To test with a given move preference list of the user.

    /*board = "_x____oxox";
    random(board, 'o');
    displayBoard(board);*/    //To unittest any given function.
    //cout << win("0oxxxxooox", 'o');
return 0;
}
