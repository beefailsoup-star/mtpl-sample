using System;

namespace MtplSample
{
    public class SortAlgorithms
    {
        public void BubbleSort<T>(T[] array) where T : IComparable<T>
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                bool swapped = false;
                for (int j = 0; j < array.Length - 1 - i; j++)
                {
                    if (array[j].CompareTo(array[j + 1]) > 0)
                    {
                        Swap(ref array[j], ref array[j + 1]);
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }

        public void SelectionSort<T>(T[] array) where T : IComparable<T>
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                int minIndex = i;
                for (int j = i + 1; j < array.Length; j++)
                {
                    if (array[j].CompareTo(array[minIndex]) < 0)
                        minIndex = j;
                }
                if (minIndex != i)
                    Swap(ref array[i], ref array[minIndex]);
            }
        }

        public void InsertionSort<T>(T[] array) where T : IComparable<T>
        {
            for (int i = 1; i < array.Length; i++)
            {
                var key = array[i];
                int j = i - 1;
                while (j >= 0 && array[j].CompareTo(key) > 0)
                {
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = key;
            }
        }

        public void QuickSort<T>(T[] array) where T : IComparable<T>
        {
            QuickSortInternal(array, 0, array.Length - 1);
        }

        private void QuickSortInternal<T>(T[] array, int left, int right) where T : IComparable<T>
        {
            if (left >= right) return;
            var pivot = Partition(array, left, right);
            QuickSortInternal(array, left, pivot - 1);
            QuickSortInternal(array, pivot + 1, right);
        }

        private int Partition<T>(T[] array, int left, int right) where T : IComparable<T>
        {
            var pivot = array[right];
            int i = left - 1;
            for (int j = left; j < right; j++)
            {
                if (array[j].CompareTo(pivot) <= 0)
                {
                    i++;
                    Swap(ref array[i], ref array[j]);
                }
            }
            Swap(ref array[i + 1], ref array[right]);
            return i + 1;
        }

        public void MergeSort<T>(T[] array) where T : IComparable<T>
        {
            if (array.Length <= 1) return;
            var temp = new T[array.Length];
            MergeSortInternal(array, temp, 0, array.Length - 1);
        }

        private void MergeSortInternal<T>(T[] array, T[] temp, int left, int right) where T : IComparable<T>
        {
            if (left >= right) return;
            int mid = left + (right - left) / 2;
            MergeSortInternal(array, temp, left, mid);
            MergeSortInternal(array, temp, mid + 1, right);
            Merge(array, temp, left, mid, right);
        }

        private void Merge<T>(T[] array, T[] temp, int left, int mid, int right) where T : IComparable<T>
        {
            int i = left, j = mid + 1, k = left;
            while (i <= mid && j <= right)
            {
                temp[k++] = array[i].CompareTo(array[j]) <= 0 ? array[i++] : array[j++];
            }
            while (i <= mid) temp[k++] = array[i++];
            while (j <= right) temp[k++] = array[j++];
            for (int idx = left; idx <= right; idx++)
                array[idx] = temp[idx];
        }

        private static void Swap<T>(ref T a, ref T b)
        {
            (a, b) = (b, a);
        }
    }
}
