#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <vector>
#include <clocale>
#include <unordered_set>
#include <Windows.h>

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
    int R = 0;      // Rabdom digits variants
    int D = 0;      // Number on one ticket

    cout << "BingoGenerator unordered set \n"s << endl;
    cout << "Enter quantity of tickets : "s ;
    N = ReadLineWithNumber();

    cout << "Enter quantity of numbers in one ticket: "s ;
    D = ReadLineWithNumber();

    cout << "Reading file: "s << infname << endl;

    vector<string> data;

    FileDataRead(data, infname);

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
