#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function declarations
void start_timer();
double stop_timer();
int compare_sentences(const char *typed, const char *original);
double calculate_accuracy(const char *typed, const char *original);
double calculate_wpm(int char_count, double time_seconds);

// load sentence from CSV based on difficulty level
int load_sentence_by_difficulty(const char *difficulty, char *output_sentence) {
    FILE *fp = fopen("sentences.csv", "r");
    if (!fp) {
        perror("Failed to open sentences.csv");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        if (token && strcmp(token, difficulty) == 0) {
            char *sentence = strtok(NULL, "\n");
            if (sentence) {
                strncpy(output_sentence, sentence, 512);
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}

// start a 30-second timer
void start_timer() {
    printf("\nTimer started. You have 30 seconds to type the sentence!\n");
}

// stop the timer and return elapsed time in seconds
double stop_timer(time_t start_time) {
    time_t end_time = time(NULL);
    return difftime(end_time, start_time);  // return the difference in seconds
}

int main() {
    char difficulty[16];
    char sentence[512];
    char typed[256];

    // get user input for difficulty
    printf("Enter difficulty (easy/medium/hard): ");
    scanf("%15s", difficulty);
    getchar(); // consume newline left by scanf

    // load sentence based on difficulty
    if (!load_sentence_by_difficulty(difficulty, sentence)) {
        printf("Could not find sentence for difficulty '%s'\n", difficulty);
        return 1;
    }

    printf("\nType the following sentence within 30 seconds:\n%s\n", sentence);
    printf("Your input: ");

    // start timer (30 seconds countdown)
    start_timer();

    // store the current time
    time_t start_time = time(NULL);  // capture start time using time(NULL)

    // user input handling
    fgets(typed, sizeof(typed), stdin);

    // measure the time taken to type the sentence
    double elapsed = stop_timer(start_time);  // calculate elapsed time using time(NULL)

    // if elapsed time exceeds 30 seconds, print that the time is up
    if (elapsed >= 30.0) {
        printf("\nTime's up! You took too long to type.\n");
    }

    // remove newline character from input if present
    typed[strcspn(typed, "\n")] = 0;

    
    int correct = compare_sentences(typed, sentence);
    double accuracy = calculate_accuracy(typed, sentence);
    double wpm = calculate_wpm(strlen(typed), elapsed);

    
    printf("\n--- Results ---\n");
    printf("Time: %.2f seconds\n", elapsed);
    printf("Correct Characters: %d\n", correct);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("WPM: %.2f\n", wpm);

    return 0;
}
