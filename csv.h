#include <stdbool.h>

void csv_count(char *string, unsigned string_size, unsigned *column_number, unsigned *row_number, char seperator) {
    unsigned row = 0;
    unsigned column = 0;

    for(int i=0;i<string_size; i++) {
        if(string[i] == seperator) row++;
        else if (string[i] == '\n') column++;
    }

    *column_number = column;
    *row_number = row;

}

void csv_parse(char *string, unsigned string_size, unsigned column, unsigned row, unsigned *start_position, unsigned *end_position, char seperator) {

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

// Not supported

/*
unsigned beta_csv_parse_advanced(unsigned **position, char sep, const char *string, int string_size) {
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
*/