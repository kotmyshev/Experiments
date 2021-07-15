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
    uniform_int_distribution<short> num_gen{1, max_number_};
    return num_gen(engine_);
}

template <class Conteiner, class ezstream>
void TicketsOutStream (const Conteiner& cont, ezstream& out, char separator){

    for (auto It = cont.begin(); It != cont.end(); ++It){

    out << *It << separator;

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
void FileOutAllTickets (const Conteiner& conteiner, const string& filenametxt, const string& title){

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

StreamOutAllTickets (conteiner, outf, "Ticket "s, ';');

}

int main()
{


    int N = 20;      // Number of tickets
    int R = 60;      // Rabdom digits variants
    int D = 25;      // Number on one ticket

    cout << "BingoGenerator unordered set \n"s << endl;
    cout << "Enter quantity of tickets : "s ;
    N = ReadLineWithNumber();
    cout << "Enter Max Value for randomize: "s ;
    R = ReadLineWithNumber();
    cout << "Enter quantity of numbers in one ticket: "s ;
    D = ReadLineWithNumber();

    vector<unordered_set<int>> tickets(N);

    mt19937 engine;

    for (int i= 0; i < N; ++i)
    {
        unordered_set<int>& temp = tickets[i];


        while (temp.size() < static_cast<size_t>(D) ){

         temp.emplace(GenerateNumber(engine, static_cast<short>(R)));
        }

    }

    int randomnu = GenerateNumber(engine, static_cast<short>(999));
    string newfilename = "BingoTickets_"s + to_string(randomnu) + "_"s + to_string(N) + "_"s + to_string(R) + "_"s + to_string(D) + ".csv"s;

StreamOutAllTickets(tickets, std::cout, "T"s, ' ');

cout << "Get Result from file " << newfilename << " from EXE directory."s << endl;

FileOutAllTickets(tickets, newfilename, "Max Value"s + to_string(R));

    return 0;
}
