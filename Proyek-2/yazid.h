#pragma warning(disable : 4996)
#pragma once
#ifndef yazid_h
#define yazid_h
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <time.h>
#include <random>
#include "header.h"


void recordHistory(char username[], char filename[]);

void getCurrentTime(char* timeString);

void historylogin(char* username);

void historyregistered(char* username);

char* bacafile(const char* file_path);

void recordHistorydekrip(char username[], char filename[]);

void showuser(char filename[]);

void encrypt_friend(char* curruser, char* friendname);

#endif
