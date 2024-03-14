void recordHistory(char username[], char filename[]) {
    FILE *historyFile;
    time_t rawtime;
    struct tm *timeinfo;
    char timeString[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

    historyFile = fopen("history.txt", "a"); // Buka file teks untuk menambahkan (append)

    if (historyFile == NULL) {
        printf("Error saat membuka file history.txt\n");
        exit(1);
    }

    fprintf(historyFile, "[%s] User '%s' membuka file '%s'\n", timeString, username, filename);

    fclose(historyFile);
}
