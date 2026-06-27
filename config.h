#pragma once

typedef struct UserData
{
	int bit_shift;
	int min_value;
	int max_value;
	int repetitions;
} UserData;

typedef struct ResultTime
{
	double omp_time;
	double chrono_time;
} ResultTime;