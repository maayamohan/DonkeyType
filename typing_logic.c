#include <stdio.h>
#include <string.h>
#include <time.h>

int compare_sentences(const char *typed, const char *original) {
    int correct = 0;
    int i = 0;

    while (typed[i] != '\0' && original[i] != '\0') {
        if (typed[i] == original[i]) {
            correct++;
        }
        i++;
    }
    return correct;
}

double calculate_accuracy(const char *typed, const char *original) {
    int total_chars = strlen(original);
    int correct_chars = compare_sentences(typed, original);
    return ((double)correct_chars / total_chars) * 100.0;
}

double calculate_wpm(int char_count, double time_seconds) {
    if (time_seconds == 0) return 0;
    double time_minutes = time_seconds / 60.0;
    return (char_count / 5.0) / time_minutes;  // average word = 5 characters
}
