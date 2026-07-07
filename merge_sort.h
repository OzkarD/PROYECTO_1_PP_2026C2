#pragma once

namespace sequential
{
	void merge_sort(int* v, int n);
}

namespace parallel
{
	void merge_sort(int* v, int left, int right, int cutoff);
}

void merge(int* v, int left, int mid, int right);