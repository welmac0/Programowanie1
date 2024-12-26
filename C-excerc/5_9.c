#include <stdio.h>

static int daytab[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_the_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int today[] = {12, 25, 2024};
    int day = day_of_the_year(today[2], today[0], today[1]);
    printf("Today is %dth day", day);
    month_day(2020, day, &today[0], &today[1]);
    printf("In 2020 today was %dth of %d month in 2020.", today[1], today[0]);

    return 0;
}

int day_of_the_year(int year, int month, int day) {
    if (year < 0 || year > 2025 || month < 0 || month > 12 || day < 0 || day > 31)
        return -1;
    int i = 0, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    int *p = &daytab[leap][1];
    while (month-- > 1)
        day += *p++;
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    if (year < 0 || year > 2025 || yearday < 0 || yearday > 366 || *pmonth < 0 || *pmonth > 12 || *pday < 0 || *pday > 31)
        printf("ERROR");
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int *p = &daytab[leap][1];

    while (yearday > *p)
        yearday -= *p++;

    *pmonth = p - &daytab[leap][0];
    *pday = yearday;
}