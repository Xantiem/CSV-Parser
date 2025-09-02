#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


unsigned csv_parse(unsigned **position, char sep, const char *string, int string_size) {
    *position = malloc(sizeof(unsigned));
    (*position)[0] = 0;

    unsigned number = 0;
    for (int pos = 0; pos < string_size; pos++) {
        if (string[pos] == sep) {
            number++;
            unsigned *tmp = realloc(*position, (number + 1) * sizeof(unsigned));
            *position = tmp;
            (*position)[number] = pos;
        }
    }
    return number+1;
}

void csv_parse_p(char *string, unsigned string_size, unsigned column, unsigned row, unsigned *start_position, unsigned *end_position, char seperator) {

    unsigned count_column = 0;
    unsigned count_row = 0;

    unsigned start_pos = 0;
    unsigned end_pos = 0;
    bool end = false;

    for (unsigned count=0;count<string_size;count++) {

        if (count_column < column) {
            if (string[count] == '\n'){
                count_column++;
            }
            start_pos++;
        }
        else {
            if (count_row < row) {
                if (string[count] == seperator) {
                    count_row++;
            }
            start_pos++;
            end_pos = start_pos;
            }
            else {
                if (!end) {
                    if (string[count] != '\n' && string[count] != seperator)
                    end_pos = count;   // track last valid character
                else
                    end = true;
                }
            }
        }
              
    }

    *start_position = start_pos;
    *end_position = end_pos;
}




int main() {
    char string[] = {"hello,world\nthis,is\na,test"};
    int size = strlen(string);
    unsigned start_position, end_position;

    csv(string, size, 2, 1, &start_position, &end_position, ',');

    printf("Start: %u End: %u", start_position, end_position);
    printf("Start: %c End: %c", string[start_position], string[end_position]);

}


/*
int main() {
    char string[] = {"hello,world\nthis,is\na,test"};
    int size = strlen(string);
    
    // Parse shit

    char column_sep = '\n';
    unsigned *column_positions = NULL;  // must initialize to NULL
    unsigned column_number = csv_parse(&column_positions, column_sep, string, size);

    for (unsigned i = 0; i < column_number; i++) {
        printf("Column: %u \n", column_positions[i]);
    }
    printf("\n");

    int column = 1;
    int row = 1;

    char row_sep = ',';

    // Need to account for < and for ==
    if (column < column_number) {
        unsigned start = column_positions[column];
        unsigned end = column_positions[column+1];
        unsigned char_count = end - start;

        printf("%u %u", start, end);


    }
    free(column_positions);
    return 0;
}
    
int main() {
    char string[] = {"hello,world\nthis,is\na,test"};
    int size = strlen(string);

    char column_sep = '\n';
    char row_sep = ',';

    int column = 1;
    int row = 1;

    unsigned count_column = 0;
    unsigned count_row = 0;

    unsigned start_pos = 0;
    unsigned end_pos = 0;
    bool end = false;

    for (unsigned count=0;count<size;count++) {

        if (count_column < column) {
            if (string[count] == column_sep){
                count_column++;
            }
            start_pos++;
        }
        else {
            if (count_row < row) {
                if (string[count] == row_sep){
                    count_row++;
                }
                end_pos = start_pos++;
            }
            else {
                // start_pos found now find end
                if (end == false && string[count]!= column_sep && string[count] != row_sep) {
                    end_pos++;
                }
                else
                    end = true;
            }
        }       
    }

    printf("Start: %u End: %u", start_pos, end_pos);
    printf("Start: %c End: %c", string[start_pos], string[end_pos]);

}

*/
