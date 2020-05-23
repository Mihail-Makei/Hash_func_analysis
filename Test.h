#ifndef HASH_TABLE_TEST_H
#define HASH_TABLE_TEST_H

#define TESTS 150000000

void test(unsigned int func(const std::string& str)) {
    std::string temp = "Ilovecats";
    for (int i = 0; i < 15000; i++)
        unsigned int tmp = func(temp);
};

#endif //HASH_TABLE_TEST_H
