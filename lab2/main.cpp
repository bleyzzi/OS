#include <Windows.h>
#include <iostream>
#include <vector>

using namespace std;

DWORD WINAPI min_max(LPVOID lpParam)
{
    vector<int>* nums = (vector<int>*)lpParam;
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    for (int i = 0; i < nums->size(); i++) {
        if (nums->at(i) < min_val) {
            min_val = nums->at(i);
        }
        Sleep(7);
        if (nums->at(i) > max_val) {  
            max_val = nums->at(i);
        }
        Sleep(7);
    }
    cout << "Min value: " << min_val << endl;
    cout << "Max value: " << max_val << endl;
    return 0;
}

DWORD WINAPI average(LPVOID lpParam)
{
    vector<int>* nums = (vector<int>*)lpParam;
    int sum = 0;
    for (int i = 0; i < nums->size(); i++) {
        sum += nums->at(i);
        Sleep(12);
    }
    double avg = (double)sum / nums->size();
    cout << "Average value: " << avg << endl;
    return 0;
}

int main()
{
    // Create array of integers
    vector<int> nums;
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    // Create min_max thread
    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &nums, 0, NULL);
    if (hMinMax == NULL) {
        cout << "Failed to create min_max thread" << endl;
        return 1;
    }

    // Create average thread
    HANDLE hAverage = CreateThread(NULL, 0, average, &nums, 0, NULL);
    if (hAverage == NULL) {
        cout << "Failed to create average thread" << endl;
        CloseHandle(hMinMax);
        return 1;
    }

    // Wait for min_max and average threads to finish
    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    // Replace max and min values with average value
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums.at(i) < min_val) {
            min_val = nums.at(i);
        }
        if (nums.at(i) > max_val) {
            max_val = nums.at(i);
        }
        sum += nums.at(i);
    }
    double avg = (double)sum / nums.size();
    for (int i = 0; i < nums.size(); i++) {
        if (nums.at(i) == min_val || nums.at(i) == max_val) {
            nums.at(i) = avg;
        }
    }

    // Print updated array
    cout << "Updated array: ";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums.at(i) << " ";
    }
    cout << endl;

    // Close handles and exit
    CloseHandle(hMinMax);
    CloseHandle(hAverage);
    return 0;
}  