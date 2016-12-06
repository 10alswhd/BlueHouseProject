#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int select_ai_difficulty();
char* rand_dictionary_word();
char* select_dict_word(char* command, int num);
int count_dict(char* word, int exact);
void error_exit(char* msg);
char* generate_scrambled_word(int difficulty, char** original_word);
void execute_turn(int turn_num, int difficulty, int* player_score, int* ai_score);
char* validate_input_word(char* letters);

int main(int argc, char** argv)
{
	int diff, i;
	diff = select_ai_difficulty();

	int player_score, ai_score;
	player_score = ai_score = 0;

	for (i = 1; i <= 5; i++)
	{
		execute_turn(i, diff, &player_score, &ai_score);
	}
	if (player_score > ai_score)
		printf("\n\nPlayer Wins (%d vs %d)!\n", player_score, ai_score);
	else if (ai_score > player_score)
		printf("\n\nAI Wins (%d vs %d)!\n", player_score, ai_score);
	else
		printf("\n\nTie, no winner (%d vs %d)!\n", player_score, ai_score);

	exit(0);
}

void execute_turn(int turn_num, int difficulty, int* player_score, int* ai_score)
{
	char* ai_word;
	char* scrambled_word;
	char* input_word;
	int i, points;

	printf("\nTurn %d -- Points You: %d, Computer: %d\n", turn_num, *player_score , *ai_score);
	printf("------------------------------------\n");
	printf("Your letters: ");
	scrambled_word = generate_scrambled_word(difficulty, &ai_word);
	for (i = 0; i < strlen(scrambled_word); i++)
	{
		printf("%c ", scrambled_word[i]);
	}

	do
	{
		printf("\nYour word: ");
		input_word = validate_input_word(scrambled_word);
		if  (input_word == NULL)
			printf("You can not spell that with your letters, try again\n");
		if (count_dict(input_word, 1) <= 0)
		{
			printf("That word is not in the dictionary, try again\n");
			input_word = NULL;
		}
	}
	while(input_word == NULL);
	printf("Valid word! Open Fire!!!!\n");
	printf("AI selects \"%s\"\n", ai_word);

	if (strlen(input_word) > strlen(ai_word))
	{
		points = (strlen(input_word) - strlen(ai_word));
		printf("%s vs %s -- You win!\n", input_word, ai_word);
		printf("You had %d letters left over - you score %d points\n", points, points);
		printf("AI had 0 letters left over - AI score 0 points\n");
		*player_score += points;
	}
	else if (strlen(input_word) < strlen(ai_word))
	{
		points = (strlen(ai_word) - strlen(input_word));
		printf("%s vs %s -- Computer wins!\n", input_word, ai_word);
		printf("You had 0 letters left over - you score 0 points\n");
		printf("AI had %d letters left over - AI score %d points\n", points, points);
		*ai_score += points;
	}
	else
		printf("%s vs %s -- Tie!\n", input_word, ai_word);


}

char* validate_input_word(char* letters)
{
	int count, i, j, len;
	char* buf;
	buf = malloc(sizeof(char) * 255);
	if (buf == NULL)
		error_exit("Unable to allocate memory");

	if (fgets(buf, 255, stdin) == NULL)
		error_exit("Unable to read from stdin");
	len = strlen(buf);
	for (i = 0; i < len - 1; i++)
	{
		count = 0;
		for (j = 0; j < strlen(letters); j++)
                {
                        if (buf[i] == letters[j])
                                count++;
                }
		for (j = 0; j < len - 1; j++)
		{
			if (buf[i] == buf[j])
				count--;
		}

		if (count < 0)
			return NULL;
	}
	buf[len - 1] = '\0';
	return buf;
}


char* generate_scrambled_word(int difficulty, char** original_word)
{
	char* dict_word;
	char* scrambled_letters;
	int i, dict_len, total_len, min_len, to, from;
	char temp;

	min_len = difficulty * 3;
	while(1)
	{
		dict_word = rand_dictionary_word();
		dict_len = strlen(dict_word);
		if (dict_len >= min_len)
			break;
	}

	total_len = dict_len - 1 + 8 / difficulty; // -1 removes newline char
	scrambled_letters = malloc(sizeof(char) * (total_len + 1)); // +1 for NULL terminator
	if (scrambled_letters == NULL)
		error_exit("Unable to allocate memory");

	memcpy(scrambled_letters, dict_word, dict_len);
	for (i = dict_len; i < total_len; i++)
	{
		scrambled_letters[i] = (char)(97 + rand() % 26);
	}

	for (i = 0; i < 1000; i++)
	{
		from = rand() % total_len;
		to = rand() % total_len;
		temp = scrambled_letters[to];
		scrambled_letters[to] = scrambled_letters[from];
		scrambled_letters[from] = temp;
	}
	scrambled_letters[total_len] = '\0';

	*original_word = dict_word;

	return scrambled_letters;
}


char* rand_dictionary_word() {
	int count, i, j, rand_num;
	char search_buf[50];
	char command_buf[255];
	char* word;

	memset(&search_buf, '\0', 50);

	srand ( time(NULL) );

	for (i = 0; i < 50; i++)
	{
		rand_num = rand() % 26;
		search_buf[i] = (char)(97 + rand_num);

		count = count_dict(search_buf, 0);
		if (count < 100 && count > 0)
		{
			if (sprintf(command_buf, "grep \"%s\" /usr/share/dict/words", search_buf) < 0)
				error_exit("Unable to format command");

			word = select_dict_word(command_buf, rand() % count);
			for (j = 0; j < strlen(word); j++)
			{
				if (word[j] < 97 || word[j] > 122)
				{
					search_buf[i] = '\0';
					i--;
					word = NULL;
					break;
				}
			}
			if (word != NULL)
			{
				return word;
			}
		}
		else if (count <= 0)
		{
			search_buf[i] = '\0';
			i--;
		}
	}

	error_exit("Unable to find dictionary word");
}

char* select_dict_word(char* command, int num)
{
	int count;
	FILE* input;
	char* buf;
	buf = malloc(sizeof(char) * 255);
	if (buf == NULL)
		error_exit("Unable to allocate buffer");

	count = 0;

	input = popen(command, "r");
	if (input == NULL)
		error_exit("Unable to execute shell command");
	while (fgets(buf, 255, input) != NULL)
	{
		if (count == num)
			break;
		count++;
	}
	if (pclose(input) < 0)
		error_exit("Error closing shell input");

	buf[strlen(buf) - 1] = '\0'; //trim newline
	return buf;
}

int count_dict(char* word, int exact)
{
	int size;
	FILE* input;
	char buf[255];
	char command_buf[255];

	if (sprintf(command_buf, (exact != 0 ? "grep -Fxo \"%s\" /usr/share/dict/words | wc -l" : "grep -o \"%s\" /usr/share/dict/words | wc -l"), word) < 0)
		error_exit("Unable to format command");

	input = popen(command_buf, "r");
	if (input == NULL)
		error_exit("Unable to execute shell command");
	if (fgets(buf, 255, input) == NULL)
		error_exit("Unable to read shell command output");
	size = atoi(buf);
	
	if (pclose(input) < 0)
		error_exit("Error closing shell input");

	return size;
}

int select_ai_difficulty()
{
	char input[3];
	int diff;

	printf("Welcome to Words with Enemies!\n");
	printf("Select an AI difficulty\n");
	printf("1 - Easy\n");
	printf("2 - Hard\n");
	if (fgets(input, 3, stdin) == NULL)
		error_exit("Unable to read input");
	diff = input[0] - 48;
	printf("Chosen Difficulty: %s (%d)\n", (diff == 1 ? "Easy" : "Hard"), diff);

	return diff;
}

void error_exit(char* msg)
{
	printf("Unhandled Error: %s\n", msg);
	exit(1);
}
