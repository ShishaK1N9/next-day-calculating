#include <stdio.h>
#include <stdbool.h>

#define size_of_array(array) sizeof(array) / sizeof(int*)

static const int MONTHS_WITH_31_DAYS[7] = {1, 3, 5, 7, 8, 10, 12}, MONTHS_WITH_30_DAYS[4] = {4, 6, 9, 11};
static const int MIN_COUNT_OF_DAYS = 28, AVERAGE_COUNT_OF_DAYS = 30, MAX_COUNT_OF_DAYS = 31;
static const int MAX_COUNT_OF_MONTHS = 12;

bool is_in_array(int month_number, const int array[], int array_size)
{
    for(int i = 0; i < array_size; i++)
        if(month_number == array[i]) return true;
    return false;
}

bool is_bissextile(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return true;
    return false;
}

void get_date(const char string[], int *day, int *month, int *year)
{
    *day = (string[0] - '0') * 10 + (string[1] - '0');
    *month = (string[3] - '0') * 10 + (string[4] - '0');
    *year = (string[6] - '0') * 1000 + (string[7] - '0') * 100 + (string[8] - '0') * 10 + (string[9] - '0');
}

void print_next_date(int next_day, int next_month, int next_year)
{
    if(next_day < 10) printf("%i%i-", 0, next_day);
    else printf("%i-", next_day);

    if(next_month < 10) printf("%i%i-", 0, next_month);
    else printf("%i-", next_month);

    if(next_year < 10) printf("%i%i%i%i\n", 0, 0, 0, next_year);
    else if(next_year < 100) printf("%i%i%i\n", 0, 0, next_year);
    else if(next_year < 1000) printf("%i%i\n", 0, next_year);
    else printf("%i\n", next_year);
}

void plus_one_day(int day, int month, int year)
{
    if(day < MIN_COUNT_OF_DAYS)
        print_next_date(day + 1, month, year);
    else if(is_in_array(day, MONTHS_WITH_30_DAYS, size_of_array(MONTHS_WITH_30_DAYS)))
    {
        if(day < AVERAGE_COUNT_OF_DAYS) print_next_date(day + 1, month, year);
        else
            if(month == MAX_COUNT_OF_MONTHS) print_next_date(1, 1, year + 1);
            else print_next_date(1, month + 1, year);
    }
    else if(is_in_array(day, MONTHS_WITH_31_DAYS, size_of_array(MONTHS_WITH_31_DAYS)))
    {
        if(day < MAX_COUNT_OF_DAYS) print_next_date(day + 1, month, year);
        else
            if(month == MAX_COUNT_OF_MONTHS) print_next_date(1, 1, year + 1);
            else print_next_date(1, month + 1, year);
    }
    else
    {
        if(is_bissextile(year))
        {
            if(day < MIN_COUNT_OF_DAYS + 1) print_next_date(day + 1, month, year);
            else
                if(month == MAX_COUNT_OF_MONTHS) print_next_date(1, 1, year + 1);
                else print_next_date(1, month + 1, year);
        }
        else
        {
            if(day < MIN_COUNT_OF_DAYS) print_next_date(day + 1, month, year);
            else
                if(month == MAX_COUNT_OF_MONTHS) print_next_date(1, 1, year + 1);
                else print_next_date(1, month + 1, year);
        }
    }
}

int main()
{
    int input_day = 0, input_month = 0, input_year = 0;
    char input_string[10];
    scanf("%s", input_string);

    get_date(input_string, &input_day, &input_month, &input_year);
    plus_one_day(input_day, input_month, input_year);

    return 0;
}