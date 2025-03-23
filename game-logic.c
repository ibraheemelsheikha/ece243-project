#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BLACK -1
#define WHITE 1
#define EMPTY 0

bool positionInBounds(int row, int col) {
  return (col >= 0 && col < 8 && row >= 0 && row < 8);
}

int squareContents(row, col) {
    pass; // this function will be written after figuring out how to take input from mouse
    // if white, return 1
    //else if black, return -1
    //else if empty, return 0
}

void drawPiece(int row, int col, int color) {
    pass; // will do this soon
}

void drawCircle(int row, int col) {
    pass; // draws a faint circle indicating a valid move
}

void clearBoard() {
    pass; // just draw a brand new empty board, don't worry about clearing individual pieces
}

void startingBoard() {
    clearBoard();
    pass; // draw two black and two white pieces in the center of the board
}

void setFirstPlayer() {
    // seed the rng
    srand(time(NULL));
    return (rand() % 2) ? 1 : -1; // return either -1 (black) or 1 (white)
    // can maybe have a coin-flipping animation for this
}

bool checkLegalInDirection(int row, int col, int color, int deltaRow, int deltaCol) {
  
  int opp_color = color * -1;
  
    //if current position is occupied or out-of-bounds, return false
    if (squareContents(row, col) != EMPTY || !positionInBounds(row, col)) {
    return false;
  }

  // move to adjacent square
  int newRow = row + deltaRow;
  int newCol = col + deltaCol;

  //if new position out of bounds, if a player's piece is already there, or if it is empty, return false
  if ((!positionInBounds(newRow, newCol)) || 
      squareContents(newRow, newCol) == color || 
      squareContents(newRow, newCol) == EMPTY)
    return false;

  //while the new position is in-bounds and there is an opponent's piece in the direction we are travelling, keep checking in that direction, as it is valid
  while ((positionInBounds(newRow, newCol)) &&
          (squareContents(newRow, newCol) == opp_color)) {
    newRow += deltaRow;
    newCol += deltaCol;
  }
  // while loop just exited either because position is out-of-bounds, or because it encountered a non-opponent piece
  // at this point, (newRow, newCol) represent the position immediately after the last opponent piece in that direction

  //check again if new position is out-of-bounds
  if (!positionInBounds(newRow, newCol)) {
    return false;
  }
  
  // if opponent's pieces have been sandwiched, return true
  if (squareContents(newRow, newCol) == color) {
    return true;
  }
  
  return false;
}

void flipTiles(int row, int col, int color) {
  
  // going in all eight directions surrounding a given square
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      
      if (checkLegalInDirection(row, col, color, deltaRow, deltaCol)) {
        int newRow = row + deltaRow;
        int newCol = col + deltaCol;
        
        while (squareContents(newRow, newCol) != color) {
          drawPiece(newRow, newCol, color);
          newRow += deltaRow;
          newCol += deltaCol;
        }
      }  
    }
  }
  
  return;
}

void displayLegalMoves(int row, int col, int color) {
  // check all legal moves in all directions and draw circles indicating valid moves
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(row, col, color, deltaRow, deltaCol)) {
        drawCircle(row, col);
      }
    }
  }
}

bool isLegalMove(int row, int col, int color) {
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol))
        return true;
    }
  }
  return false;
}

void getInput(int* row, int* col, int color) {
  pass; // get mouse input
}

// counts how many opponent pieces are captured for a particular move (will be used for hint button)
int findScore(int row, int col, int color) {
  int score = 0;
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      
      if (checkLegalInDirection(row, col, colour, deltaRow, deltaCol)) {
        int newRow = row + deltaRow;
        int newCol = col + deltaCol;
        
        while (squareContents(newRow, newCol) != colour) {
          score++;
          newRow += deltaRow;
          newCol += deltaCol;

        }
      }  
    }
  }
  return score;
}

// finds the best possible move (will be used for hint button)
int findBestMove(int color, int *row, int *col) {
  int highScore = 0;
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      if (squareContents(r, c) == EMPTY) {
        int score = findScore(r, c, colour);
        if (highScore < score) {
          highScore = score;
          *row = r;
          *col = c;
        }
      }
    }
  }
  return highScore;
}

bool isGameOver() {
  int row = 0, col = 0;
  if ((findBestMove(1, &row, &col) == 0) && (findBestMove(-1, &row, &col) == 0)) {
    return true;
  }
  return false;
}

bool hasLegalMoves(int color) {
  for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
          if (isLegalMove(row, col, color)) {
              return true;
          }
      }
  }
  return false;
}

void switchPlayer(int *currentPlayer) {
  *currentPlayer = (*currentPlayer == BLACK) ? WHITE : BLACK;
}

void winner() {
  int wCount = 0, bCount = 0;
  
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (squareContents(row, col) == WHITE) {
        wCount++;
      } else if (squareContents(row, col) == BLACK) {
        bCount++;
      }
    }
  }
  if (wCount > bCount) {
    printf("W player wins.\n");
  } else if (bCount > wCount) {
    printf("B player wins.\n");
  } else {
    printf("Draw!\n");
  }
}

int main(void) {
  /*
  startingBoard();
  int currentPlayer = setFirstPlayer();

  while (!isGameOver()) {
  if player has valid moves
  if (hasLegalMoves(currentPlayer))  
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (squareContents(row, col) == EMPTY) {
        displayLegalMoves(row, col, currentPlayer);
      }
    }
  }  
  (row, col) = getInput
    if (isLegalMove(row, col)) {
      drawPiece(row, col, currentPlayer);
      flipTiles(row, col, currentPlayer);
      switchPlayer(&currentPlayer);
    }

  }
  winner();

  */


  return 0;
}
