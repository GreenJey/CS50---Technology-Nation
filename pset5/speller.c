/**
 * speller.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a spell-checker.
 */

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"
#undef calculate
#undef getrusage

// default dictionary
#define DICTIONARY "dictionaries/large"

// prototype
double calculate(const struct rusage* b, const struct rusage* a);

int main(int argc, char* argv[])
{
    // check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // Структури даних для синхронізації
    struct rusage before, after;

    // тести
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // визначити словник та використовувати
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // завантажити словник
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // перервати, якщо словник не завантажено
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // розрахувати час для завантаження словника
    time_load = calculate(&before, &after);

    // відкрити текст
    char* text = (argc == 3) ? argv[2] : argv[1];
    FILE* fp = fopen(text, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // підготувати доповідь помилок
    printf("\nMISSPELLED WORDS\n\n");

    // підготувати перевірки правопису
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];

    // орфографію перевіряти кожне слово в тексті
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // дозволити тільки літерні символи і апостроф
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // додати символ слова
            word[index] = c;
            index++;

            // ігнорувати літерні рядки занадто довго, щоб бути слова
            if (index > LENGTH)
            {
                // споживати залишок алфавітній рядки
                while ((c = fgetc(fp)) != EOF && isalpha(c));

                // підготуватися до нового слова
                index = 0;
            }
        }

        // ігнорувати слова з цифрами
        else if (isdigit(c))
        {
            // споживати залишок алфавітно-цифровий рядки
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // підготуватися до нового слова
            index = 0;
        }

        // знайшли ціле слово
        else if (index > 0)
        {
            // припинити поточнt слово
            word[index] = '\0';

            // поновити лічильник
            words++;

            // перевірка орфографії
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // оновлення тест
            time_check += calculate(&before, &after);

            // друк слово, якщо помилка
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // підготуватися до наступного слова
            index = 0;
        }
    }

    // перевірте, чи є помилка
    if (ferror(fp))
    {
        fclose(fp);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // закрити текст
    fclose(fp);

    // визначити розмір словника
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // розрахувати час, щоб визначити розмір словника
    time_size = calculate(&before, &after);

    // вивантажити словник
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // перервати, якщо Словник не вивантажується
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // розрахувати час, щоб вивантажити словник
    time_unload = calculate(&before, &after);

    // тести звіт
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n", time_load + time_check + time_size + time_unload);

    // that's all folks
    return 0;
}

/**
 * Returns number of seconds between b and a.
 */
double calculate(const struct rusage* b, const struct rusage* a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
