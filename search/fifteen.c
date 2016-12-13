/*
*
* fifteen.c for cs50 course pset3
*
* Connie Chow-Petit
*
* Implements the game Fifteen, 4 steps
* Code shown does not include entire code provided
*
*/

...

void init(void)
{
    // TODO Create the board

int i = ((d*d)-1);

    // Attribute values
    for (int k = 0; k < d; k++)
    {
        for (int j = 0; j < d; j++, i--)
        {
            board[k][j] = i;
        }
    }
    board[d - 1][d - 1] = (d*d);    
    if (((d * d)-1)%2 == 1)
    {
        board[d-1][d-2]++;
        board[d-1][d-3]--; 
    }
} 
    
/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO Print the current state of board
    printf("\n\n");
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == (d*d))
            {
                printf("   _");
            }
        
        else 
        {
        printf("%4d", board[i][j]);
        
        if (j == d - 1)
        {
            printf("\n");
        }
        }
        }
      printf("\n");
    }
    
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO Search for tile positions and move
    int i = 0;
    int j = 0;
    
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                if (board[i + 1][j] == (d*d))
                {
                    board[i + 1][j] = tile;
                    board[i][j] = (d*d);
                    return true;
                }
                if (board[i - 1][j] == (d*d))
                {
                    board[i - 1][j] = tile;
                    board[i][j] = (d*d);
                    return true;
                }
                if (board[i][j + 1] == (d*d))
                {
                board[i][j + 1] = tile;
                    board[i][j] = (d*d);
                    return true;
                }
                if (board[i][j - 1] == (d*d))
                {
                    board[i][j - 1] = tile;
                    board[i][j] = (d*d);
                    return true;
                }
                
            }
        }
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO Winning the game
    int i = 0;
    int j = 0;
    
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < d; j++) 
        {
          if (board[i][j] != (1 + (i * d) + j))
          {
            return false;
          }
        }
    }
    return true;
}

...
