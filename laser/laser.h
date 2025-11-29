/* pre-supplied function and type declarations */

char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **array, int rows);
char **load_board(const char *filename, int &height, int &width);
void print_board(char **board, int height, int width);

enum Direction {NORTH, EAST, SOUTH, WEST};

/* add your own function and type declarations here */
bool find_laser(char** board, int height, int width, int& row);

char mirror_label(char** board, int height, int width, int row, int column);

void change_beam(char& beam, int& increment, char** board, int r, int c);
bool shoot(char** board, int height, int width, char* message, int& last_row, int& last_col);

bool find_next_question(char** board, int height, int width, int start_row, int start_col, int& q_r, int& q_c);
bool board_matches_target(char** board, int height, int width, const char* target);
bool solve_recursive(char** board, int height, int width, const char* target, int start_row, int start_col);
//bool shoot_question(char** board, int height, int width, char* message, char& beam, int& increment, int& last_row, int& last_col);
bool solve(char** board, int height, int width, const char* target);