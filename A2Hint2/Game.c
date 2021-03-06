
    //------------------------------------
    //    Include Libraries
    //------------------------------------
    #include "game.h"

    //------------------------------------
    //    01. FUNCTION create_new_game
    //------------------------------------
    game* create_new_game(char* p1, char* p2, int connect, int rows, int columns){
        //1. We create the variable for hosting the game
        game* g = (game*)malloc(1 * sizeof(game));
        
        //2. We use the names passed as arguments
        (*g).p1 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
        strcpy((*g).p1, p1);
        
        (*g).p2 = (char*)malloc((strlen(p2) + 1) * sizeof(char));
        strcpy((*g).p2, p2);
        
        //3. We set the mode to the one passed by parameter
        int mode = 0;
        if (strcmp(p1, "Computer") == 0)
            mode = mode + 2;
        if (strcmp(p2, "Computer") == 0)
            mode = mode + 1;
        (*g).mode = mode;
        
        //4. We set the status to be 1; i.e., player1 moves first
        (*g).status = 1;
        
        //5. We initialise the connect, rows and columns
        (*g).connect = connect;
        (*g).rows = rows;
        (*g).columns = columns;
        
        //6. We initialise the board to contain all positions empty
        (*g).board = (char**)malloc(rows * sizeof(char*));
        (*g).board[0] = (char*)malloc((rows * columns) * sizeof(char));
        for (int i = 0; i < rows; i++)
            (*g).board[i] = (*g).board[0] + (columns * i);
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                (*g).board[i][j] = ' ';
        
        //7. We return the game
        return g;
    }

    //------------------------------------
    //    02. FUNCTION display_board
    //------------------------------------
    void display_board(game* g) {
        printf("\n        **************\n        Connect 4 Game\n        **************");
        printf("\n   ");
        
        for (int x = 0; x < (*g).columns; x++)
        {
            printf("%d   ", x);
        }
        printf("\n +");
        
        for (int y = 0; y < (*g).columns; y++)
        {
            printf("---+");
        }
        
        for (int row = 0; row < (*g).rows; row++)
        {
           printf("\n%d", row);
            for (int col = 0; col < (*g).columns; col++)
            {
                printf("| %c ", (*g).board[row][col] );
                if (col == ((*g).columns -1))
                {
                    printf("|\n");
                    printf(" +");
                    for (int y = 0; y < (*g).columns; y++)
                    {
                        printf("---+");
                    }
                }
            }

        }
        
    }

    //------------------------------------
    //    03. FUNCTION display_game_status
    //------------------------------------
    void display_game_status(game* g) {
        if((*g).status == 1)
        {
            printf("\nGame is open. Player %s moves next!", (*g).p1);
        }
        if((*g).status == 2)
        {
            printf("\nGame is open. Player %s moves next!", (*g).p2);
        }
        if((*g).status == 3)
        {
            printf("\nGame is over. Player %s has won!\n", (*g).p1);
        }
        if((*g).status == 4)
        {
            printf("\nGame is over. Player %s has won!\n", (*g).p2);
        }
        if((*g).status == 5)
        {
            printf("\nGame is over. It finished with a draw");
        }
    }

    //--------------------------------------------------
    // 04. FUNCTION my_getchar
    //--------------------------------------------------
    char my_get_char() {
        //1. We create the variable for hosting the char
        char my_char = ' ';
        
        //2. We create an extra variable to consume any other characters entered until a return is pressed
        bool line_consumed = False;
        char dummy_char = ' ';
        
        //3. We consume the first char entered, i.e., the one we are interested at
        my_char = getchar();
        
        //4. While still there are remaining characters
        while (line_consumed == False) {
            //4.1. We consume the next character
            dummy_char = getchar();
            
            //4.2. If the new character is the end of line one, we can ensure we have consumed the entire line.
            if (dummy_char == '\n')
                line_consumed = True;
        }
        
        //5. We return the first character entered by the user, i.e., the one we are interested at
        return my_char;
    }

    //------------------------------------
    //    05. FUNCTION ask_for_column
    //------------------------------------
    int ask_for_column(game* g) {
        char columnInput = ' ';
        int x = 0;
        do
        {
           // printf("\nEnter column number 1-3: ");
            columnInput = my_get_char();
            printf("Your input is: %c", columnInput);
            x = columnInput - '0';
        } while ((x > (*g).columns) || (x < 1) || (columnInput == ' ') || (columnInput == '\n') );
        
        return x;
    }

    //------------------------------------
    //    06. FUNCTION user_movement
    //------------------------------------
    void user_movement(game* g, int* c, int* r) {
        *c = -1;
        //*r = -1;
        
        while (*c == -1){
        
            int input = 0;
            int i = (*g).rows - 1;
            bool assign = False;
            input = ask_for_column(g);
            while (assign == False && i >= 0)
            {
                if((*g).board[i][input-1] == ' ')
                {
                    if((*g).status == 1)
                    {
                        (*g).board[i][input-1] = 'X';
                        *c = input - 1;
                        assign = True;
                    }
                    else if((*g).status == 2)
                    {
                        (*g).board[i][input-1] = 'O';
                        *c = input - 1;
                        assign = True;
                    }
                }
                else
                {
                    i--;
                }
                *r = i;
            }
            
            
            assign = False;
            
        }
    }

    //------------------------------------
    //    07. FUNCTION computer_movement
    //------------------------------------
    void computer_movement(game* g, int* c, int* r) {
        *c = -1;
        //*r = -1;
        
            while (*c == -1){
            
            int aux;
            int i = (*g).rows - 1;
            bool assign = False;
            aux = rand() % (*g).columns;
            while (assign == False && i >= 0)
            {
                if((*g).board[i][aux] == ' ')
                {
                    if((*g).status == 1)
                    {
                        (*g).board[i][aux] = 'X';
                        *c = aux;
                        assign = True;
                    }
                    else if((*g).status == 2)
                    {
                        (*g).board[i][aux] = 'O';
                        *c = aux;
                        assign = True;
                    }
                    
                }
                else
                {
                    i--;
                }
                *r = i;
            }
                assign = False;
            }
    }

    //------------------------------------
    //    08. FUNCTION new_movement
    //------------------------------------
    void new_movement(game* g) {
        
    }

    //------------------------------------
    //    09. FUNCTION winning_row
    //------------------------------------
    bool winning_row(game* g, int* r, int ply) {
        bool checkRow = False;
        int i = 0;
        int count = 0;
        char playerLetter = ' ';
        //Choose letter to be checked
        if(ply == 1)
        {
            playerLetter = 'X';
        }
        else if (ply == 2)
        {
            playerLetter = 'O';
        }
        //While to check
        while((i < (*g).columns) && (count < (*g).connect))
        {
            if ((*g).board[*r][i] != playerLetter)
            {
                count = 0;
            }
            else
            {
                count = count + 1;
            }
            i++;
        }
        count = 0;
        //if there is 4 in a line change to true
        if (count == (*g).connect)
        {
            checkRow = True;
        }
        
        return checkRow;
    }


    //------------------------------------
    //    10. FUNCTION winning_column
    //------------------------------------
    bool winning_column(game* g, int* c, int ply) {
        bool checkCol = False;
        int i = (*g).rows;
        int count = 0;
        char playerLetter = ' ';
        
        //Choose letter to be checked
        if(ply == 1)
        {
            playerLetter = 'X';
        }
        else if (ply == 2)
        {
            playerLetter = 'O';
        }
        
        //While to check
        while((i >= 0) && (count < (*g).connect))
        {
            if ((*g).board[i - 1][*c] != playerLetter)
            {
                count = 0;
            }
            else
            {
                count = count + 1;
            }
            i--;
        }
        
        //if there is 4 in a line change to true
        if (count == (*g).connect)
        {
            checkCol = True;
        }
        return checkCol;
    }

    //------------------------------------
    //    11. FUNCTION winning_diagonal
    //------------------------------------
    bool winning_diagonal(game* g, int* c, int* r, int ply, bool left) {
        bool checkDia = False;
        int i = *r;  //4
        int j = *c;   // 7
        int count = 0;
        char playerLetter = ' ';
        if(ply == 1)
        {
            playerLetter = 'X';
        }
        else if (ply == 2)
        {
            playerLetter = 'O';
        }
        if (left == True)
        {
            while(i > 0 && j > 0)
            {
                i--;
                j--;
            }
            
            while(((i < (*g).rows) && (j < (*g).columns)) && (count < (*g).connect)) // *c 0 *r 5
            {
                if ((*g).board[i][j] != playerLetter) // 5 0
                {
                    count = 0;
                }
                else
                {
                    count = count + 1;
                }
                i++;
                j++;
            }
        }
        else if (left == False)
        {
            while(i > 0 && j < ((*g).columns - 1))
            {
                i--;
                j++;
            }
            
            while(((i < (*g).rows) && (j >= 0)) && (count < (*g).connect))
            {
                if ((*g).board[i][j] != playerLetter)
                {
                    count = 0;
                }
                else
                {
                    count = count + 1;
                }
                i++;
                j--;
            }
            if (count == (*g).connect)
            {
                checkDia = True;
            }

        }
        if (count == (*g).connect)
        {
            checkDia = True;
        }
        
        
        return checkDia;
    }


    //------------------------------------
    //    12. FUNCTION winning_player
    //------------------------------------
    bool winning_player(game* g, int ply) {
        bool i = False;
        return i;
    }

    //------------------------------------
    //    13. FUNCTION update_status
    //------------------------------------
    void update_status(game* g) {
        if((*g).status == 1)
        {
            (*g).status = 2;
        }
        else if((*g).status == 2)
        {
            (*g).status = 1;
        }
    }

    //------------------------------------
    //    14. FUNCTION play_game
    //------------------------------------
    void play_game(int connect, int rows, int columns, char* p1, char* p2){
        game* c = create_new_game(p1, p2, connect, rows, columns);
        int dummy = -1;
        int* col = &dummy;
        int dummy1 = -1;
        int* row = &dummy1;
        bool checkCol = False;
        bool checkRow = False;
        bool checkDiaRight = False;
        bool checkDiaLeft = False;
        int player = -1;
        int movesCounter = 0;
        int maxMoves = ((*c).columns * (*c).rows) - 1;
        while ((*c).status != 3 && (*c).status != 4 && (*c).status != 5)
        {
            
            //Switch player variable depending on the status
            if((*c).status == 1)
            {
                player = 1;
            }
            else if((*c).status == 2)
            {
                player = 2;
            }

            display_board(c);
            display_game_status(c);
            
            if ((*c).mode == 0)                 // If mode is 0 just ask for user movements PvP
            {
                printf("\nEnter column number 1-7: ");
                user_movement(c, col, row);
            }
            else if((*c).mode > 2)              // If mode is 3 only ask for computer movements CvC
            {
                computer_movement(c, col, row);
            }
            else if((*c).status == 2 && (*c).mode == 1)     //If mode is 1 and Status 2 Computer then ask for computer movement
            {
                computer_movement(c, col, row);
                printf("\nComputer has made its move");
            }
            
            else if((*c).status == 1 && (*c).mode == 1)     //If mode is 1 and Status 1 Computer then ask for user movement
            {
                printf("\nEnter column number 1-7: ");
                user_movement(c, col, row);
            }
            else if((*c).status == 1 && (*c).mode == 2)     //If mode is 2 and Status 1 Computer then ask for computer movement
            {
                computer_movement(c, col, row);
                printf("\nComputer has made its move");
            }
            
            else if((*c).status == 2 && (*c).mode == 2)     //If mode is 2 and Status 2 Computer then ask for computer movement
            {
                printf("\nEnter column number 1-7: ");
                user_movement(c, col, row);
            }
           //checkCol = winning_column(c, col, player);
           //checkRow = winning_row(c, row, player);
           //checkDiaRight = winning_diagonal(c, col, row, player, True);
           //checkDiaLeft = winning_diagonal(c, col, row, player, False);
            if((checkCol == True) || (checkRow == True) || (checkDiaRight == True) || (checkDiaLeft == True))
            {
                if(player == 1)
                {
                    (*c).status = 3;
                }
                else if(player == 2)
                {
                    (*c).status = 4;
                }
            }
        if (movesCounter >= maxMoves)
        {
            (*c).status = 5;
        }
        movesCounter++;
        update_status(c);
            
        }
        display_board(c);
        display_game_status(c);
        my_get_char();
    }

