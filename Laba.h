#ifndef HASH_TABLE_LABA_H
#define HASH_TABLE_LABA_H
#include <cstdlib>

std::ofstream fout(OUTPUT_FILE);


void Research(unsigned int hash(const std::string& str)) {
    std::ifstream fin(INPUT_FILE);

    std::string str = "";
    mm::List<std::string> lst[TABLE_SIZE];

    while (!fin.eof()) {
        fin >> str;
        unsigned int temp = hash(str) % TABLE_SIZE;

        lst[temp].push_back(str);
    }


    for (auto & i : lst)
        fout << i.list_size() << ';';

    fout << std::endl;
}

#endif //HASH_TABLE_LABA_H
