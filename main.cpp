// #include <QCoreApplication>

// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);

//     return a.exec();
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <gmpxx.h>
#include <vector>
#include <iostream>
#include <fstream>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string FILE_PATH = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin";
constexpr size_t NUM_SYNAPSES = 10105;
std::vector<mpz_class> list_of_synapses(0);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE: функции:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<mpz_class> readVectorFromFile(const std::string& filename) {

    FILE* inFile = fopen(filename.c_str(), "rb");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return list_of_synapses;
    }

    while (!feof(inFile)) {
        mpz_class num;
        if (mpz_inp_raw(num.get_mpz_t(), inFile) == 0) {
            break; // EOF or error
        }
        list_of_synapses.push_back(num);
    }

    fclose(inFile);
    return     list_of_synapses;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void redirectOutputToFile2(const QString &filePath) {
    // Открываем файл для записи и очищаем его содержимое
    FILE *file = freopen(filePath.toStdString().c_str(), "w", stdout);
    if (!file) {
        std::cerr << "Failed to redirect stdout to file" << std::endl;
        return;
    }

    // Перенаправляем stderr тоже, если нужно
    file = freopen(filePath.toStdString().c_str(), "w", stderr);
    if (!file) {
        std::cerr << "Failed to redirect stderr to file" << std::endl;
        return;
    }

    std::cout << "Console output is now redirected to the log file." << std::endl;
    std::cerr << "Error output is also redirected to the log file." << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readFromFile(std::vector<mpz_class>& list_of_synapses, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Ошибка открытия файла для чтения:" << file.errorString();
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    // Считываем размер вектора
    quint32 vectorSize;
    in >> vectorSize;

    list_of_synapses.resize(vectorSize);

    for (quint32 i = 0; i < vectorSize; ++i) {
        quint32 size;
        in >> size;

        std::vector<unsigned char> buffer(size);
        if (in.readRawData(reinterpret_cast<char*>(buffer.data()), size) != size) {
            qCritical() << "Ошибка чтения числа из файла для элемента" << i;
            return;
        }

        // Импортируем данные в mpz_class
        mpz_import(list_of_synapses[i].get_mpz_t(), size, 1, 1, 0, 0, buffer.data());
    }

    file.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readFromFile2(std::vector<mpz_class>& list_of_synapses, const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        qCritical() << "Ошибка открытия файла для чтения";
        return;
    }

    for (size_t i = 0; i < NUM_SYNAPSES; ++i) {
        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        std::vector<char> buffer(size);
        inFile.read(buffer.data(), size);
        list_of_synapses[i].set_str(std::string(buffer.begin(), buffer.end()), 10);
    }

    inFile.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readFromFile3(std::vector<mpz_class>& list_of_synapses, const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        qCritical() << "Ошибка открытия файла для чтения";
        return;
    }

    for (size_t i = 0; i < NUM_SYNAPSES; ++i) {
        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        std::vector<char> buffer(size);
        inFile.read(buffer.data(), size);
        list_of_synapses[i].set_str(std::string(buffer.begin(), buffer.end()), 10);
    }

    inFile.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void redirectOutputToFile(const QString& logFilePath) {
    // Открываем файл для записи
    QFile logFile(logFilePath);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        std::cerr << "Could not open log file for writing: " << logFilePath.toStdString() << std::endl;
        return;
    }

    // Перенаправляем std::cout
    static std::ofstream out(logFilePath.toStdString().c_str(), std::ios::app);
    std::cout.rdbuf(out.rdbuf());

    // Перенаправляем std::cerr
    static std::ofstream err(logFilePath.toStdString().c_str(), std::ios::app);
    std::cerr.rdbuf(err.rdbuf());
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rewriteTFile(const QString& logFilePath) {
QString logFilePath4 =
 "/home/viktor/my_projects_qt_2_build/build-chtenie_binarnogo_faila_v_konsoly-Desktop_Qt_6_8_0-Debug/application.log";
    // Укажите путь к вашему .log файлу

QFile file(logFilePath4);

// Открыть файл в режиме записи (QIODevice::WriteOnly) и очистить его содержимое
if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    qCritical() << "Could not open file for writing:" << file.errorString();
 //   return -1;
}

// Создать QTextStream для записи текста в файл
QTextStream out(&file);
out << "This is a new log entry." << Qt::endl;

file.close();

qDebug() << "Log file has been overwritten successfully.";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QString logFilePath =
        "/home/viktor/my_projects_qt_2_build/build-chtenie_binarnogo_faila_v_konsoly-Desktop_Qt_6_8_0-Debug/application.log";
    redirectOutputToFile(logFilePath);

// redirectOutputToFile2(logFilePath);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Пример использования
    // std::vector<mpz_class> list_of_synapses(//0
    //                                      10105
    //                                      );
  QString filePath = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin";
    // Чтение чисел из бинарного файла
  //  std::vector<mpz_class> read_synapses(NUM_SYNAPSES);
  // readFromFile3(list_of_synapses, FILE_PATH);
  readVectorFromFile(FILE_PATH);
    // readFromFile(list_of_synapses, //FILE_PATH
    //              filePath
    //               );

    // Выводим прочитанные данные для проверки
   int i=0;
    for (const auto& num : list_of_synapses) {
       std::cout <<i<<":"<< num.get_str() << std::endl;
        i++;
    }

    return 0;
}





























