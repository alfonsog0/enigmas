/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

bool dictionary_search(const char *word);

/* add your function prototypes here */
const int MAX_WORD_LEN = 16;      
const int MAX_NEIGHBOURS = 100;
const int MAX_STEPS = 5;
const int MAX_CHAIN_LEN = 100;
static char chain_storage[MAX_CHAIN_LEN][MAX_WORD_LEN + 1];

bool valid_step(const char* current_word, const char* next_word);

bool display_chain(const char* chain[], ostream& output_stream);

bool valid_chain(const char* chain[]);

void get_neighbours(const char* current_word, char neighbours[][MAX_WORD_LEN + 1], int& count);
bool dfs(const char* current, const char* target);
bool dfs(const char* current, const char* target, int remaining_steps);
bool dfs(const char* current, const char* target, char answer_chain[][MAX_WORD_LEN + 1], int current_len, int remaining_steps);

bool find_chain(const char* start_word, const char* target_word, const char* answer_chain[], int max_steps);