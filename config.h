#pragma once

typedef struct UserData
{
	int bit_shift;
	int min_range;
	int max_range;
	int repetitions;
} UserData;

typedef struct ResultTime
{
	double omp_time;
	double chrono_time;
} ResultTime;