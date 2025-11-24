enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

/* insert your function prototypes here */
int tile_score(char letter);

bool can_form_word_from_tiles(char* word, char* tiles, char* played_tiles);