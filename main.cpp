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
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Пример использования
    std::vector<mpz_class> list_of_synapses(10105);
  QString filePath = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin";
    // Чтение чисел из бинарного файла
  //  std::vector<mpz_class> read_synapses(NUM_SYNAPSES);
   readFromFile3(list_of_synapses, FILE_PATH);
    // readFromFile(list_of_synapses, //FILE_PATH
    //              filePath
    //               );

    // Выводим прочитанные данные для проверки
    for (const auto& num : list_of_synapses) {
        std::cout << num.get_str() << std::endl;
    }

    return 0;
}





























