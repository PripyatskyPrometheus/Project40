#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
    size_t time = 0;

    void operator+=(const stats& rhs) {
        comparison_count += rhs.comparison_count;
        copy_count += rhs.copy_count;
        time += rhs.time;
    }
};

stats Insert_Sort(vector<int>& arr) {
    stats result;
    for (int i = 1; i < arr.size(); i++) {
        result.comparison_count++;
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--, result.comparison_count++) {
            result.copy_count += 3;
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
        }
    }
    return result;
}

stats Quick_Sort(vector<int>& arr, int left, int right) {
    stats result;
    int i = left, j = right;
    int mid = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < mid) {
            result.comparison_count++;
            i++;
        }
        result.comparison_count++;
        while (arr[j] > mid) {
            result.comparison_count++;
            j--;
        }
        result.comparison_count++;
        if (i <= j) {
            result.copy_count += 3;
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        result += Quick_Sort(arr, left, j);
    }
    if (right > i)
    {
        result += Quick_Sort(arr, i, right);
    }
    return result;
}

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

stats Test_Insert_Sort_Random(int numb) {
    stats result;
    for (int j = 0; j < 100; j++) {
        vector<int> array;
        for (int i = 0; i < numb; i++) {
            array.push_back(lcg());
        }

        auto start = chrono::high_resolution_clock::now();
        result += Insert_Sort(array);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        result.time += duration.count();
    }
    cout << "InsertSort for RANDOM array with len: " << numb << endl <<
        "time: " << (double)result.time / 100 << " microseconds" << endl <<
        "comparison_count : " << result.comparison_count / 100 << endl <<
        "copy_count : " << result.copy_count / 100 << endl;
    return result;
}

stats Test_Insert_Sort_Sorted(int numb) {
    stats result;
    vector<int> array;
    for (int i = 0; i < numb; i++) {
        array.push_back(i);
    }

    auto start = chrono::high_resolution_clock::now();
    result += Insert_Sort(array);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.time += duration.count();

    cout << "InsertSort for SORTED array with len: " << numb << endl <<
        "time: " << (double)result.time << " microseconds" << endl <<
        "tcomparison_count: " << result.comparison_count << endl <<
        "copy_count: " << result.copy_count << endl;
    return result;

}

stats Test_Insert_Sort_Reverse_Sorted(int numb) {
    stats result;
    vector<int> array;
    for (int i = numb; i > 0; i--) {
        array.push_back(i);
    }

    auto start = chrono::high_resolution_clock::now();
    result += Insert_Sort(array);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.time += duration.count();

    cout << "InsertSort for REVERSE-SORTED array with len: " << numb << endl <<
        "time: " << (double)result.time << " microseconds" << endl <<
        "comparison_count: " << result.comparison_count << endl <<
        "copy_count: " << result.copy_count << endl;
    return result;
}

stats Test_Quick_Sort_Random(int numb) {
    stats result;
    for (int j = 0; j < 100; j++) {
        vector<int> array;
        for (int i = 0; i < numb; i++) {
            array.push_back(lcg());
        }

        auto start = chrono::high_resolution_clock::now();
        result += Quick_Sort(array, 0, array.size() - 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        result.time += duration.count();
    }
    cout << "Quick_Sort for RANDOM array with len: " << numb << endl <<
        "time: " << (double)result.time / 100 << " microseconds" << endl <<
        "comparison_count : " << result.comparison_count / 100 << endl <<
        "copy_count : " << result.copy_count / 100 << endl;
    return result;
}

stats Test_Quick_Sort_Sorted(int numb) {
    stats result;
    vector<int> array;
    for (int i = 0; i < numb; i++) {
        array.push_back(i);
    }

    auto start = chrono::high_resolution_clock::now();
    result += Quick_Sort(array, 0, array.size() - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.time += duration.count();

    cout << "QuickSort for SORTED array with len: " << numb << endl <<
        "ime: " << (double)result.time << " microseconds" << endl <<
        "comparison_count : " << result.comparison_count << endl <<
        "copy_count : " << result.copy_count << endl;
    return result;
}

stats Test_Quick_Sort_Reverse_Sorted(int numb) {
    stats result;
    vector<int> array;
    for (int i = numb; i > 0; i--) {
        array.push_back(i);
    }

    auto start = chrono::high_resolution_clock::now();
    result += Quick_Sort(array, 0, array.size() - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.time += duration.count();

    cout << "QuickSort for REVERSE-SORTED array with len: " << numb << endl <<
        "time: " << (double)result.time << " microseconds" << endl <<
        "comparison_count : " << result.comparison_count << endl <<
        "copy_count : " << result.copy_count << endl;
    return result;
}

int main() {
    while (true) {
        cout << "1. Insert_sort" << endl;
        cout << "2. Quick_sort" << endl;
        cout << "3. Check stats" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            vector<int> arr;
            arr.push_back(5);
            arr.push_back(9);
            arr.push_back(8);
            arr.push_back(10);
            arr.push_back(7);
            arr.push_back(1);
            arr.push_back(6);
            arr.push_back(4);
            arr.push_back(3);
            arr.push_back(2);
            stats tmp = Insert_Sort(arr);
            cout << tmp.comparison_count << " " << tmp.copy_count << endl;
            for (int i = 0; i < arr.size(); i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        }
        case(2): {
            vector<int> arr;
            arr.push_back(8);
            arr.push_back(5);
            arr.push_back(1);
            arr.push_back(2);
            arr.push_back(6);
            arr.push_back(3);
            stats tmp = Quick_Sort(arr, 0, arr.size() - 1);
            cout << tmp.comparison_count << " " << tmp.copy_count << endl;
            for (int i = 0; i < arr.size(); i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        }

        case(3): {
            vector<int> numbs = { 1000,  2000, 3000, 4000, 5000, 6000, 7000,8000,9000, 10000, 25000, 50000, 100000 };

            stats tmp1, tmp2, tmp3;

            for (auto i : numbs) {
                tmp1 = Test_Insert_Sort_Random(i);
                tmp2 = Test_Insert_Sort_Sorted(i);
                tmp3 = Test_Insert_Sort_Reverse_Sorted(i);
                cout << endl;
                cout << i << " " << tmp1.comparison_count << " " << tmp2.comparison_count << " " << tmp3.comparison_count << endl;
                cout << i << " " << tmp1.copy_count << " " << tmp2.copy_count << " " << tmp3.copy_count << endl;
                cout << i << " " << tmp1.time << " " << tmp2.time << " " << tmp3.time << endl;
                cout << endl;
            }

            cout << "-------------------------------------------" << endl;

            for (auto i : numbs) {
                tmp1 = Test_Quick_Sort_Random(i);
                tmp2 = Test_Quick_Sort_Sorted(i);
                tmp3 = Test_Quick_Sort_Reverse_Sorted(i);
                cout << endl;
                cout << i << " " << tmp1.comparison_count << " " << tmp2.comparison_count << " " << tmp3.comparison_count << endl;
                cout << i << " " << tmp1.copy_count << " " << tmp2.copy_count << " " << tmp3.copy_count << endl;
                cout << i << " " << tmp1.time << " " << tmp2.time << " " << tmp3.time << endl;
                cout << endl;
            }
            break;
        }
        case 4: {
            return 0;
        }
        default: {
            break;
        }
        }
    }
}