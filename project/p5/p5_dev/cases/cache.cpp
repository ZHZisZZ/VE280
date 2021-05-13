#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "dlist.h"

enum class ERROR {UNKOWN_INSTRUCTIONS, NOT_ENOUGH_OPERANDS, TOO_MANY_OPERANDS, ADDRESS_OUT_OF_BOUND};

class LRUCache
{
private:
    int mem_size;
    int *memory;
    struct block
    {
        int address;
        int data;
    };
    int cur_cache_size;
    int max_cache_size;
    Dlist<block> cache;

    // EFFECTS: //
    static bool compare(const block *a, const block *b);
public:

    // EFFECTS: //
    LRUCache(int cache_size, int memory_size);
    // EFFECTS: //
    ~LRUCache();
    // EFFECTS: //
    int read(int address);
    // EFFECTS: //
    void write(int address, int data);
    // EFFECTS: //
    void printCache();
    // EFFECTS: //
    void printMem();
};

// EFFECTS: //
bool LRUCache::compare(const LRUCache::block *a, const LRUCache::block *b)
{
    return a->address == b->address;
}

// EFFECTS: //
LRUCache::LRUCache(int cache_size, int memory_size)
        : mem_size(memory_size), memory(new int[memory_size]{0}),
          cur_cache_size(0), max_cache_size(cache_size)
{
}

// EFFECTS: //
LRUCache::~LRUCache()
{
    delete [] memory;
}

// EFFECTS: //
int LRUCache::read(int address)
{
    if (address >= mem_size || address < 0) throw ERROR::ADDRESS_OUT_OF_BOUND;
    block target = {address, 0};
    block *find = cache.remove(compare, &target);
    if (find) {
        cache.insertFront(find);
        return find->data;
    } else {
        if (cur_cache_size == max_cache_size) {
            find = cache.removeBack();
            memory[find->address] = find->data;
            delete find;
        } else { cur_cache_size++; }
        cache.insertFront(new block{address, memory[address]});
        return memory[address];
    }
}

// EFFECTS: //
void LRUCache::write(int address, int data)
{
    if (address >= mem_size || address < 0) throw ERROR::ADDRESS_OUT_OF_BOUND;
    block target = {address, 0};
    block *find = cache.remove(compare, &target);
    if (find) {
        find->data = data;
        cache.insertFront(find);
    } else {
        if (cur_cache_size == max_cache_size) {
            find = cache.removeBack();
            memory[find->address] = find->data;
            delete find;
        } else { cur_cache_size++; }
        cache.insertFront(new block{address, data});
    }
}

// EFFECTS: //
void LRUCache::printCache()
{
    for (int i = 0; i < cur_cache_size; i++) {
        block *t = cache.removeFront();
        std::cout << t->address << " " << t->data << std::endl;
        cache.insertBack(t);
    }
}

// EFFECTS: //
void LRUCache::printMem()
{
    for (int i = 0; i < mem_size; i++) {
        std::cout << memory[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
    int cacheSize, memSize;
    std::string input[4];
    std::stringstream ss;
    std::cin >> cacheSize >> memSize; std::cin.get();
    LRUCache cache(cacheSize, memSize);
    while (getline(std::cin, input[0])) {
        ss.str(std::string());
        ss.clear();
        ss << input[0];
        int cnt = 0;
        for (; cnt < 4 && ss >> input[cnt]; cnt++) continue;
        try {
            if (input[0] == "READ") {
                if (cnt <= 1) throw ERROR::NOT_ENOUGH_OPERANDS;
                if (cnt >= 3) throw ERROR::TOO_MANY_OPERANDS;
                std::cout << cache.read(atoi(input[1].c_str())) << std::endl;
            } else if (input[0] == "WRITE") {
                if (cnt <= 2) throw ERROR::NOT_ENOUGH_OPERANDS;
                if (cnt >= 4) throw ERROR::TOO_MANY_OPERANDS;
                cache.write(atoi(input[1].c_str()), atoi(input[2].c_str()));
            } else if (input[0] == "PRINTCACHE") {
                if (cnt >= 2) throw ERROR::TOO_MANY_OPERANDS;
                cache.printCache();
            } else if (input[0] == "PRINTMEM") {
                if (cnt >= 2) throw ERROR::TOO_MANY_OPERANDS;
                cache.printMem();
            } else if (input[0] == "EXIT") {
                if (cnt >= 2) throw ERROR::TOO_MANY_OPERANDS;
                break;
            } else {
                throw ERROR::UNKOWN_INSTRUCTIONS;
            }
        } catch (ERROR e) {
            std::cout << "ERROR: ";
            switch (e) {
                case ERROR::UNKOWN_INSTRUCTIONS:
                    std::cout << "Unknown instruction\n";break;
                case ERROR::NOT_ENOUGH_OPERANDS:
                    std::cout << "Not enough operands\n";break;
                case ERROR::TOO_MANY_OPERANDS:
                    std::cout << "Too many operands\n";break;
                case ERROR::ADDRESS_OUT_OF_BOUND:
                    std::cout << "Address out of bound\n";break;
            }
        }
    }
}