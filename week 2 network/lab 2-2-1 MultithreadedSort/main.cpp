#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QThread>

#include <QtDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

#include <cstring>
#include <algorithm>

const int LEN = 100000000;

int data_orig[LEN];
int data[LEN];

void doubleMergesort(int *data, int start, int end)
{
    int mid = start + (end - start) / 2;
    int *left = new int[mid - start];
    int *right = new int[end - mid];
    std::memcpy(left, data + start, (mid - start) * sizeof(int));
    std::memcpy(right, data + mid, (end - mid) * sizeof(int));
    std::function<int(int *, int*)> func([&](int *begin, int *end){ std::sort(begin, end); return 0; });
    QFuture<int> future1 = QtConcurrent::run(func, left, left + (mid - start));
    QFuture<int> future2 = QtConcurrent::run(func, right, right + (end - mid));
    future1.result();
    future2.result();
    int i = 0, j = 0;
    for (int k = start; k != end; ++k) {
        if (i < mid - start && left[i] <= right[j]) {
            data[k] = left[i];
            ++i;
        } else {
            data[k] = right[j];
            ++j;
        }
    }
    delete[] left;
    delete[] right;
}


void fourMergesort(int *data, int start, int end)
{
    int mid = start + (end - start) / 2;
    int *left = new int[mid - start];
    int *right = new int[end - mid];
    std::memcpy(left, data + start, (mid - start) * sizeof(int));
    std::memcpy(right, data + mid, (end - mid) * sizeof(int));
    std::function<int(int *, int, int)> func([&](int *data, int start, int end){ doubleMergesort(data, start, end); return 0; });
    QFuture<int> future1 = QtConcurrent::run(func, left, 0, mid - start);
    QFuture<int> future2 = QtConcurrent::run(func, right, 0, end - mid);
    future1.result();
    future2.result();
    int i = 0, j = 0;
    for (int k = start; k != end; ++k) {
        if (i < mid - start && left[i] <= right[j]) {
            data[k] = left[i];
            ++i;
        } else {
            data[k] = right[j];
            ++j;
        }
    }
    delete[] left;
    delete[] right;
}

void eightMergesort(int *data, int start, int end)
{
    int mid = start + (end - start) / 2;
    int *left = new int[mid - start];
    int *right = new int[end - mid];
    std::memcpy(left, data + start, (mid - start) * sizeof(int));
    std::memcpy(right, data + mid, (end - mid) * sizeof(int));
    std::function<int(int *, int, int)> func([&](int *data, int start, int end){ fourMergesort(data, start, end); return 0; });
    QFuture<int> future1 = QtConcurrent::run(func, left, 0, mid - start);
    QFuture<int> future2 = QtConcurrent::run(func, right, 0, end - mid);
    future1.result();
    future2.result();
    int i = 0, j = 0;
    for (int k = start; k != end; ++k) {
        if (i < mid - start && left[i] <= right[j]) {
            data[k] = left[i];
            ++i;
        } else {
            data[k] = right[j];
            ++j;
        }
    }
    delete[] left;
    delete[] right;
}

void sixteenMergesort(int *data, int start, int end)
{
    int mid = start + (end - start) / 2;
    int *left = new int[mid - start];
    int *right = new int[end - mid];
    std::memcpy(left, data + start, (mid - start) * sizeof(int));
    std::memcpy(right, data + mid, (end - mid) * sizeof(int));
    std::function<int(int *, int, int)> func([&](int *data, int start, int end){ eightMergesort(data, start, end); return 0; });
    QFuture<int> future1 = QtConcurrent::run(func, left, 0, mid - start);
    QFuture<int> future2 = QtConcurrent::run(func, right, 0, end - mid);
    future1.result();
    future2.result();
    int i = 0, j = 0;
    for (int k = start; k != end; ++k) {
        if (i < mid - start && left[i] <= right[j]) {
            data[k] = left[i];
            ++i;
        } else {
            data[k] = right[j];
            ++j;
        }
    }
    delete[] left;
    delete[] right;
}

void thirtyTwoMergesort(int *data, int start, int end)
{
    int mid = start + (end - start) / 2;
    int *left = new int[mid - start];
    int *right = new int[end - mid];
    std::memcpy(left, data + start, (mid - start) * sizeof(int));
    std::memcpy(right, data + mid, (end - mid) * sizeof(int));
    std::function<int(int *, int, int)> func([&](int *data, int start, int end){ sixteenMergesort(data, start, end); return 0; });
    QFuture<int> future1 = QtConcurrent::run(func, left, 0, mid - start);
    QFuture<int> future2 = QtConcurrent::run(func, right, 0, end - mid);
    future1.result();
    future2.result();
    int i = 0, j = 0;
    for (int k = start; k != end; ++k) {
        if (i < mid - start && left[i] <= right[j]) {
            data[k] = left[i];
            ++i;
        } else {
            data[k] = right[j];
            ++j;
        }
    }
    delete[] left;
    delete[] right;
}


int main(int argc, char *argv[])
{
    QFile fileIn("input.txt");
    fileIn.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fileIn);
    int i = 0;
    while (!in.atEnd()) {
        data_orig[i++] = in.readLine().toInt();
    }
    fileIn.close();

    long timestamp;

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 1 thread ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    std::sort(data, data + LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 2 threads ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    doubleMergesort(data, 0, LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 4 threads ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    fourMergesort(data, 0, LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 8 threads ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    eightMergesort(data, 0, LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 16 threads ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    sixteenMergesort(data, 0, LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    std::memcpy(data, data_orig, sizeof data);
    qDebug() << "--- sort in 32 threads ---";
    timestamp = QDateTime::currentMSecsSinceEpoch();
    thirtyTwoMergesort(data, 0, LEN);
    qDebug() << "completed in" << QDateTime::currentMSecsSinceEpoch() - timestamp << "ms" << "\n";

    QFile fileOut("output.txt");
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&fileOut);
    for (i = 0; i < LEN; ++i) {
        out << data[i] << "\n";
    }
    fileOut.close();

    return 0;
}
