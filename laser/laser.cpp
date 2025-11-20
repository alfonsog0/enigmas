#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include "laser.h"

using namespace std;

/* pre-supplied helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **array = new char *[rows];
  assert(array);
  for (int r=0; r<rows; r++) {
    array[r] = new char[columns];
    assert(array[r]);
  }
  return array;
}

/* pre-supplied helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **array, int rows) {
  for (int r=0; r<rows; r++)
    delete [] array[r];
  delete [] array;
}

/* internal helper function which gets the dimensions of a board */
bool get_board_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* internal helper function which removes carriage returns and newlines from end of strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width) {

  bool success = get_board_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **board = allocate_2D_array(height, width + 1);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    filter(line);
    strcpy(board[r], line);
  }
  
  return board;
}

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

/* add your own function definitions here */
bool find_laser(char** board, int height, int width, int& row) {
    int col = 0;
    for (int r = 0; r < height; r++) {
        if (board[r][col] == '>') {
            row = r;
            return true;
        }
    }
    row = -1;
    return false;
}

char mirror_label(char** board, int height, int width, int row, int column) {
    //cout << "height: " << height << endl << "width: " << width << endl;
    if (isspace(board[row][column])) {
        return '\0';
    }
    int start_row = row - 1;
    int start_col = column - 1;
    for (int r = start_row; r <= row + 1; r++) {
        for (int c = start_col; c <= column + 1; c++) {
            if (r < 0 || r >= height || c < 0 || c >= width) continue;
            if (isalpha(board[r][c])) {
                return board[r][c];
            }
        }
    }
    return '\0';
}

void change_beam(char& beam, int& increment, char** board, int r, int c) {
    if (beam == '-') beam = '|';
    else if (beam == '|') beam = '-';
    if (board[r][c] == '/') increment *= -1;
}

bool shoot(char** board, int height, int width, char* message, int& last_row, int& last_col) {
    int row;
    // find the starting point
    find_laser(board, height, width, row);
    if (row == -1) {
        *message = '\0';
        return false;
    }
    
    int r = row;
    int c = 1;
    char beam = '-';
    int increment = 1;
    // loop throuugh the board from the starting point
    while (beam == '-' && c < width && c >= 0 && r < height && r >= 0) {
        bool flag = false;
        if (r < height && r >= 0 && c >= 0 && board[r][c] != ' ') {
            // if its a \ / rotate the beam and change the variable beam
            if (board[r][c] == '\\' || board[r][c] == '/') {

                *message = mirror_label(board, height, width, r, c);
                if (*message) {
                    message += 1;
                }
                change_beam(beam, increment, board, r, c);
                r += increment;
                flag = true;
                //continue;
            }
            // if it is a question mark end
            else if (r < height && r >= 0 && c >= 0 && (board[r][c] == '?' || board[r][c] == '#')) {
                last_row = r;
                last_col = c;
                *message = '\0';
                return false;
            }
            else if (r < height && r >= 0 && c >= 0 && board[r][c] == '@') {
                last_row = r;
                last_col = c;
                *message = '\0';
                return true;
            }
        }
        if (flag == false && r < height && r >= 0 && c < width && c >= 0) {
            board[r][c] = beam;
            c += increment;
        }
        
        while (beam == '|' && r < height && r >= 0 && c < width && c >= 0) {
            // if the position in the board is not a whitespace:
            if (r < height && r >= 0 && c >= 0 && board[r][c] != ' ') {
                // if its a \ / rotate the beam and change the variable beam
                if (board[r][c] == '\\' || board[r][c] == '/') {
                    *message = mirror_label(board, height, width, r, c);
                    if (*message) {
                        message += 1;
                    }
                    change_beam(beam, increment, board, r, c);
                    c += increment;
                    continue;
                }
                // if it is a question mark end
                else if (r < height && r >= 0 && c >= 0 && (board[r][c] == '?' || board[r][c] == '#')) {
                    last_row = r;
                    last_col = c;
                    *message = '\0';
                    return false;
                }
                else if (r < height && r >= 0 && c >= 0 && board[r][c] == '@') {
                    last_row = r;
                    last_col = c;
                    *message = '\0';
                    return true;
                }
            }
            if (r < height && r >= 0 && c < width && c >= 0) {
                board[r][c] = beam;
                r += increment;
            }
        }
    } 
    return false;
}

// bool solve(char** board, int height, int width, char* target) {
//     // how do i update lr and lc in recursive calls?
//     int lr = 0, lc = 0;
//     if (shoot(board, height, width, target, lr, lc)) {
//         return true;
//     }
//     char symbols[3] = {'\\', '/', ' '};
//     for (int i = 0; i < 3; i++) {
//         // recursive backtrackin
//         // l'ultima cella della chiamata precedente (=?) fa ripartire lo shoot
//         board[lr][lc] = symbols[i];

//     }
//     // stub
//     return false;
// }

bool solve(char** board, int height, int width, char* target) {
    // how do i update lr and lc in recursive calls?
    int lr = 0, lc = 0;
    // base case
    // if (board[lr][lc] == '@')
    if (shoot(board, height, width, target, lr, lc)) {
        return true;
    }
    else {
        solve_recursive(board, height, width, target, lr, lc);
    }
}