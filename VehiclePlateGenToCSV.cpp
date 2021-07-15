// VehiclePlate Generator to CSV file
// VehiclePlate Generator from Yandex.praktikum
// 2021.07.16

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <iomanip>

using namespace std;

std::string ReadLine() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    std::cin >> result;
    ReadLine();
    return result;
}

int GenerateNumber(mt19937& engine_, short max_number_) {
    uniform_int_distribution<short> num_gen{0, max_number_};
    return num_gen(engine_);
}
class VehiclePlate {
private:
    auto AsTuple() const {
        return tie(letters_, digits_, region_);
    }

public:
    bool operator==(const VehiclePlate& other) const {
        return AsTuple() == other.AsTuple();
    }

    bool operator<(const VehiclePlate& other) const {
        return AsTuple() < other.AsTuple();
    }

    VehiclePlate(char l0, char l1, int digits, char l2, int region)
        : letters_{l0, l1, l2}
        , digits_(digits)
        , region_(region) {
    }

    string ToString() const {
        ostringstream out;
        out << letters_[0] << letters_[1];
        out << setfill('0') << right << setw(3) << digits_;
        out << letters_[2] << setw(2) << region_;

        return out.str();
    }

    const array<char, 3>& GetLetters() const {
        return letters_;
    }

    int GetDigits() const {
        return digits_;
    }

    int GetRegion() const {
        return region_;
    }

private:
    array<char, 3> letters_;
    int digits_;
    int region_;
};

struct PlateHasherTrivial {
    size_t operator()(const VehiclePlate& plate) const {
        return static_cast<size_t>(plate.GetDigits());
    }
};

class PlateGenerator {
    char GenerateChar() {
        uniform_int_distribution<short> char_gen{0, static_cast<short>(possible_chars_.size() - 1)};
        return possible_chars_[char_gen(engine_)];
    }

    int GenerateNumber() {
        uniform_int_distribution<short> num_gen{0, 999};
        return num_gen(engine_);
    }

    int GenerateRegion() {
        uniform_int_distribution<short> region_gen{0, static_cast<short>(possible_regions_.size() - 1)};
        return possible_regions_[region_gen(engine_)];
    }

public:
    VehiclePlate Generate() {
        return VehiclePlate(GenerateChar(), GenerateChar(), GenerateNumber(), GenerateChar(), GenerateRegion());
    }

private:
    mt19937 engine_;

    // допустимые значения сохраним в static переменных
    // они объявлены inline, чтобы их определение не надо было выносить вне класса
    inline static array possible_regions_
    = {1,  2,  102, 3,   4,   5,   6,   7,   8,  9,   10,  11,  12, 13,  113, 14,  15, 16,  116, 17, 18,
       19, 20, 21,  121, 22,  23,  93,  123, 24, 84,  88,  124, 25, 125, 26,  27,  28, 29,  30,  31, 32,
       33, 34, 35,  36,  136, 37,  38,  85,  39, 91,  40,  41,  82, 42,  142, 43,  44, 45,  46,  47, 48,
       49, 50, 90,  150, 190, 51,  52,  152, 53, 54,  154, 55,  56, 57,  58,  59,  81, 159, 60,  61, 161,
       62, 63, 163, 64,  164, 65,  66,  96,  67, 68,  69,  70,  71, 72,  73,  173, 74, 174, 75,  80, 76,
       77, 97, 99,  177, 199, 197, 777, 78,  98, 178, 79,  83,  86, 87,  89,  94,  95};

    // постфикс s у литерала тут недопустим, он приведёт к неопределённому поведению
    inline static string_view possible_chars_ = "ABCEHKMNOPTXY"sv;
};

template <class Conteiner, class ezstream>
void TicketsOutStream (const Conteiner& cont, ezstream& out, char separator, vector<string>& datalines){

    for (auto It = cont.begin(); It != cont.end(); ++It){

        out << datalines[*It] << separator;

    }

    out << endl;
}


template <class Conteiner, class ezstream>
void TicketsOutStream (const Conteiner& cont, ezstream& out, char separator){

    for (auto It = cont.begin(); It != cont.end(); ++It){

        out << *It << separator;

    }

    out << endl;
}

template <class Conteiner, class ezstream>
void StreamOutAllTickets (const Conteiner& cont, ezstream& out , const string& mark, char separator, vector<string>& datalines){

    size_t j = 1;

    for (auto It = cont.begin(); It != cont.end(); ++It){
        out << mark << (j++) << ':' << separator;

        TicketsOutStream (*It, out , separator, datalines);
    }

    out << endl;

}

template <class Conteiner, class ezstream>
void StreamOutAllTickets (const Conteiner& cont, ezstream& out , const string& mark, char separator){

    size_t j = 1;

    for (auto It = cont.begin(); It != cont.end(); ++It){
        out << mark << (j++) << ':' << separator;

        TicketsOutStream (*It, out , separator);
    }

    out << endl;

}

template <class Conteiner>
void FileOutAllTickets (const Conteiner& conteiner, const string& filenametxt, const string& title , vector<string>& datalines){

    ofstream ofs(filenametxt);
    //ofs.close();

    ofstream outf(filenametxt);

    // Если мы не можем открыть этот файл для записи данных,
    if (!outf)
    {
        // то выводим сообщение об ошибке и выполняем функцию exit()
        cerr << "Uh oh, " << filenametxt << "could not be opened for writing!" << endl;
        exit(1);
    }
    outf <<  title << endl;

    StreamOutAllTickets (conteiner, outf, "Ticket "s, ';' , datalines);

}

void FileDataRead (vector<string>& datalines, const string& filenametxt){

    std::ifstream file (filenametxt);

    while(file) {
        std::string str;
        std::getline(file, str);
        if (str.size()>0){
            datalines.push_back(str);
        }
    }

}

int main()
{
    const string infname = "inputdata.txt"s;

    int N = 0;      // Number of tickets
    int R = 0;      // Random digits variants
    int D = 0;      // Number on one ticket

    vector<string> data;

    cout << "BingoGenerator unordered set \n"s << endl;
    cout << "Enter quantity of tickets : "s ;
    N = ReadLineWithNumber();

    cout << "Enter quantity of numbers in one ticket: "s ;
    D = ReadLineWithNumber();

    cout << "Select: Reading file or Generate VehiclePlate [R/G] "s << infname << endl;

    string answer = ReadLine();



    if (answer == "R"s || answer == "r"s){
        cout << "Reading file: "s << infname << endl;
        FileDataRead(data, infname);
    } else {
        cout << "Generate VehiclePlate Numbers: "s << endl;

        int V = N * D;

        data.reserve(V);

        PlateGenerator plate_gen;

        for (int k = 0; k < V; ++k) {
            data.push_back(plate_gen.Generate().ToString());
        }
    }

    R = data.size();

    cout << "Max quantity of variants: "s  << R << endl;

    vector<unordered_set<int>> tickets(N);

    mt19937 engine;

    for (int i= 0; i < N; ++i)
    {
        unordered_set<int>& temp = tickets[i];


        while (temp.size() < static_cast<size_t>(D) ){

            temp.emplace(GenerateNumber(engine, static_cast<short>(R-1)));
        }

    }

    int randomnu = GenerateNumber(engine, static_cast<short>(999));
    string newfilename = "BingoTickets_"s + to_string(randomnu) + "_"s + to_string(N) + "_"s + to_string(R) + "_"s + to_string(D) + ".csv"s;

    StreamOutAllTickets(tickets, std::cout, "T"s, ' ');



    FileOutAllTickets(tickets, newfilename, "Max Value"s + to_string(R), data);

    cout << "Get Result from file " << newfilename << " from EXE directory."s << endl;

    return 0;
}
