#include <iostream>
#include <fstream>
#include<string>
#include<tuple>
#include<chrono>

struct Rooms
{
    char letter;
    int digit;
};
struct FIOs
{
    std::string F;
    std::string I;
    std::string O;
};
struct times
{
    int hour;
    int minute;
};
struct record
{
    Rooms Room ;
    FIOs FIO;
    times time;
};
void GetSize(int& size)
{
    std::fstream(file);
    file.open("data1.txt");
    std::string line;
    std::getline(file, line);
    size = std::stoi(line);
    file.close();
}
void GetArray(record*& RecArr, record*& CopyRecArr, int size)
{
    std::fstream(file);
    file.open("data1.txt");
    std::string line,elem;
    getline(file, line);
    int i = 0;
    while (i!=size)
    {
        int j=0;
        getline(file, line, ' ');
        RecArr[i].Room.letter = line[j];
        CopyRecArr[i].Room.letter = line[j];
        elem = line.erase(0, 1);
        RecArr[i].Room.digit = std::stoi(elem);
        CopyRecArr[i].Room.digit = std::stoi(elem);
        getline(file, line, ' ');
        RecArr[i].FIO.F = line;
        CopyRecArr[i].FIO.F = line;
        getline(file, line, ' ');
        RecArr[i].FIO.I = line;
        CopyRecArr[i].FIO.I = line;
        getline(file, line, ' ');
        RecArr[i].FIO.O = line;
        CopyRecArr[i].FIO.O = line;
        getline(file, line, ':');
        RecArr[i].time.hour = std::stoi(line);
        CopyRecArr[i].time.hour = std::stoi(line);
        getline(file, line);
        RecArr[i].time.minute = std::stoi(line);
        CopyRecArr[i].time.minute = std::stoi(line);
        elem = "";
        i += 1;
    }
    file.close();
}
void PrintProc(record* RecArr, int size, double time, int flag, std::string filename)
{
    std::ofstream(file);
    file.open(filename);
    file << time << "s\n"; !flag ? file << " stable\n" : file << "unstable\n";
    for (auto i = 0; i < size; ++i)
    {
        file << RecArr[i].Room.letter << RecArr[i].Room.digit << " ";
        file << RecArr[i].FIO.F << " " << RecArr[i].FIO.I << " " << RecArr[i].FIO.O << " ";
        file << RecArr[i].time.hour << ":" << RecArr[i].time.minute << std::endl;
    }
    file.close();
}
void PrintCompare(int flag1, int flag2, double time1, double time2, std::string filename)
{
    std::ofstream(file);
    file.open(filename);
    file << "Bubble Sort                   Merge(top-down) \n";
    file << "Stable Check: stable ";
    flag2 == 0 ? file << "    stable\n" : file << "unstable\n";
    file << "Time:" << time1 << "  " << time2 << std::endl << std::endl;
    time1 > time2 ? file << "Merge is faster then Bubble Sort\n" : time1 == time2 ? file << "They are equal\n" : file << "Bubble Sort is faster then Merge\n";
}
void Swap(auto* xp, auto* yp)
{
    auto temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void BubbleSort(record*& array, int size){
    bool swapped = true; int i = 0;
    while (swapped)
    {
        swapped = false;
        for (int j = 0;j < size - i - 1; j++){
            if (std::tie(array[j].Room.letter,array[j].Room.digit) < (std::tie(array[j+1].Room.letter, array[j+1].Room.digit))){
                Swap(&array[j], &array[j+1]);
                swapped = true;
            }
            else if((std::tie(array[j].Room.letter,array[j].Room.digit) == (std::tie(array[j+1].Room.letter, array[j+1].Room.digit))) &&
            (std::tie(array[j].FIO.F,array[j].FIO.I,array[j].FIO.O) < (std::tie(array[j+1].FIO.F,array[j+1].FIO.I,array[j+1].FIO.O)))) {
                Swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }
        i = i + 1;
    }
}
void BubbleTimer(double& time, record*& array, int size){
    std::chrono::time_point < std::chrono::high_resolution_clock>start, end;
    start = std::chrono::high_resolution_clock::now();
    BubbleSort(array, size);
    end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsedTime(end - start);
    const double seconds(elapsedTime.count());
    time = seconds;
}
void merge(record*& array,int start,int mid,int end) {
    record *temp = new record[end - start + 1];

    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (std::tie(array[i].Room.letter, array[i].Room.digit) > std::tie(array[j].Room.letter, array[j].Room.digit)) {
            temp[k]=array[i];
            k += 1;
            i += 1;
        }
        else if((std::tie(array[i].Room.letter,array[i].Room.digit) == (std::tie(array[j].Room.letter, array[j].Room.digit))) &&
                (std::tie(array[i].FIO.F,array[i].FIO.I,array[i].FIO.O) > (std::tie(array[j].FIO.F,array[j].FIO.I,array[j].FIO.O)))){
            temp[k]=array[i];
            k += 1;
            i += 1;

        }
        else {
            temp[k] = array[j];
            k += 1;
            j += 1;
        }
    }
    while(i <= mid) {
        temp[k] = array[i];
        k += 1;
        i += 1;
    }

    while(j <= end) {
        temp[k] = array[j];
        k += 1;
        j += 1;
    }
    for(i = start; i <= end; i += 1) {
        array[i] = temp[i - start];
    }
}
void MergeSort(record*& array, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        MergeSort(array, start, mid);
        MergeSort(array, mid+1, end);
        merge(array, start, mid, end);
    }
}
void MergeTimer(double& time, record*& array, int size){
    std::chrono::time_point < std::chrono::high_resolution_clock>start, end;
    start = std::chrono::high_resolution_clock::now();
    MergeSort(array,0, size-1);
    end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsedTime(end - start);
    const double seconds(elapsedTime.count());
    time = seconds;
}

int main() {
    int flag1 = 0, flag2 = 0,size=0;
    double time1 = 0, time2 = 0;

    GetSize(size);
    record* array = new record[size];
    record* rec_array = new record[size];
    GetArray(array, rec_array,size);

    BubbleTimer(time1,array,size);
    PrintProc(array, size, time1, flag1, "BubbleSort_output.txt");

    MergeTimer(time2,rec_array,size);
    PrintProc(rec_array, size, time2, flag2, "MergeSort_output.txt");

    PrintCompare(flag1,flag2,time1,time2,"compare.txt");
    return 0;
}
