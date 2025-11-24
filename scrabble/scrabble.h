enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

/* insert your function prototypes here */
int tile_score(char letter);

bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles);

void apply_modifier(ScoreModifier score_modifier, const char* played_tiles, int index, int& score);

int compute_score(const char* played_tiles, ScoreModifier score_modifiers[]);

int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier score_modifiers[],char* word);