#include <stdio.h>
#include <time.h>

void log(const char* format, ...) {
    FILE* file = fopen("log.txt", "a"); // Open file in "append" mode
    if (file != NULL) {
        // Get the current time
        time_t currentTime;
        time(&currentTime);
        struct tm* timeInfo = localtime(&currentTime);

        // Format the time as a string
        char timestamp[25];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeInfo);

        // Write the log message with timestamp and variable arguments to the file
        fprintf(file, "[%s] ", timestamp);

        // Handle variable arguments using va_list and vsnprintf
        va_list args;
        va_start(args, format);
        char buffer[256]; // Adjust the buffer size as needed
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        fprintf(file, "%s\n", buffer);

        fclose(file); // Close the file after writing
    } else {
        printf("Error opening log file.\n");
    }
}
