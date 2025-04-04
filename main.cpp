#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class sumGame {
public:
    sumGame(int gameArray[3][3]) {
        int num = 1;
        for (int row = 0; row <= 3; row++) {
            for (int col = 0; col <= 3; col++) {
                gameArray[row][col] = num++;
            }
        }
    }

    void setMove(int turn) { moves = turn; }
    int getMove() { return moves; }

    void findSum(int array[3][3]) {
        rowSum1 = rowSum2 = rowSum3 = 0;
        colSum1 = colSum2 = colSum3 = 0;
        diagSum1 = diagSum2 = 0;

        for (int c = 0; c < 3; c++) {
            rowSum1 += gameArray[0][c];
            rowSum2 += gameArray[1][c];
            rowSum3 += gameArray[2][c];
        }
        for (int r = 0; r < 3; r++) {
            colSum1 += gameArray[r][0];
            colSum2 += gameArray[r][1];
            colSum3 += gameArray[r][2];
        }
        for (int r = 0; r < 3; r++) {
            diagSum1 += gameArray[r][r];
            if ((r + r) == 2) diagSum2 += gameArray[r][2 - r];
        }
    }

    void Test_winningSum() {
        rowSum1 = colSum1 = rowSum2 = colSum2 = rowSum3 = colSum3 = diagSum1 = diagSum2 = 15;
        cout << checkWin(1) << endl;
        getSum();
    }

    void Test_losingSum() {
        rowSum1 = colSum1 = rowSum2 = colSum2 = rowSum3 = colSum3 = diagSum1 = diagSum2 = 0;
        cout << checkWin(0) << endl;
        getSum();
    }

    void getSum() {
        cout << "Row 1: " << setw(13) << rowSum1 << endl;
        cout << "Column 1: " << setw(10) << colSum1 << endl;
        cout << "Row 2: " << setw(13) << rowSum2 << endl;
        cout << "Column 2: " << setw(10) << colSum2 << endl;
        cout << "Row 3: " << setw(13) << rowSum3 << endl;
        cout << "Column 3: " << setw(10) << colSum3 << endl;
        cout << "Diagonal Left: " << setw(5) << diagSum1 << endl;
        cout << "Diagonal Right: " << setw(4) << diagSum2 << endl;

        if (rowSum1 == 15 && rowSum2 == 15 && rowSum3 == 15 && colSum1 == 15 && colSum3 == 15 && diagSum1 == 15 && diagSum2 == 15) {
            cout << "\nBoard Complete!!";
        } else {
            cout << "\nBoard Not Complete!";
        }
    }

    int checkWin(int win) {
        if (rowSum1 == 15 && rowSum2 == 15 && rowSum3 == 15 && colSum1 == 15 && colSum3 == 15 && diagSum1 == 15 && diagSum2 == 15) {
            return 0;
        } else {
            return 1;
        }
    }

    void swapArray(int chosenNum, int swapNum) {
        int row1 = 0, col1 = 0, row2 = 0, col2 = 0;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (gameArray[row][col] == chosenNum) {
                    row1 = row; col1 = col; break;
                }
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (gameArray[row][col] == swapNum) {
                    row2 = row; col2 = col; break;
                }
            }
        }

        int temp = gameArray[row1][col1];
        gameArray[row1][col1] = gameArray[row2][col2];
        gameArray[row2][col2] = temp;
    }

    void setGame(int array[3][3]) {
        num = 0;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                gameArray[row][col] = ++num;
            }
        }
    }

    void Test_arrayOutput(int array[3][3]) {
        cout << "\nExpected 1–9 grid:\n";
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                gameArray[row][col] = ++num;
            }
        }
        getGame();
    }

    void shuffleGame(int arr[3][3], int rows, int cols) {
        srand(time(NULL));
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                int randRow = rand() % 3;
                int randCol = rand() % 3;
                swap(gameArray[i][j], arr[randRow][randCol]);
            }
        }
    }

    void getGame() {
        for (int row = 0; row < 3; row++) {
            cout << "\n";
            for (int col = 0; col < 3; col++) {
                cout << gameArray[row][col] << " ";
            }
        }
        cout << endl;
    }

private:
    int gameArray[4][4];
    int moves, num;
    int rowSum1, rowSum2, rowSum3;
    int colSum1, colSum2, colSum3;
    int diagSum1, diagSum2;
};

int main() {
    int turnNum = 0, targetNum, swapNum, winLoss = 1;
    int allFifteen[3][3];
    bool runGame = true;

    sumGame game(allFifteen);
    game.setGame(allFifteen);
    game.shuffleGame(allFifteen, 3, 3);

    while (runGame) {
        game.getGame();
        cout << "\n\n";
        game.findSum(allFifteen);
        game.getSum();
        cout << endl;

        if (game.checkWin(winLoss) == 1) {
            cout << "\nEnter digit to move: ";
            cin >> targetNum;
            cout << "Enter digit to swap with: ";
            cin >> swapNum;
            cout << endl;
            game.swapArray(targetNum, swapNum);
            turnNum++;
        } else {
            runGame = false;
            break;
        }
    }

    if (!runGame) {
        cout << "\nNumber of moves taken: " << turnNum << endl;
    }
    return 0;
}
