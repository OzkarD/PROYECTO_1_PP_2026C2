#pragma once

namespace sequential
{
	void merge_sort(int* v, int n);
}

namespace parallel
{
	void merge_sort(int* v, int n);
}

void merge(int* v, int left, int mid, int right);

void merge_sort_parallel(int* v, int left, int right);