#pragma once

int* createVector(int n);
void destroyVector(int* v);
void fillRandom(int* v, int n, int min_value, int max_value);
void printSample(const int* v, int n, int max_items);
void checkSorted(const int* v, int n);