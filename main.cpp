// 8-1

#include <iostream>
#include <string>
#include "utils.h"

class Cell;
class Table;

class Cell {
    protected:
        int x;
        int y;
        Table* table;
        std::string data;
    
    public:
        Cell(std::string data, int x, int y, Table* table);
        virtual std::string stringify();
        virtual int to_numeric();
};

Cell::Cell(std::string data, int x, int y, Table* table) : data(data), x(x), y(y), table(table) {}

std::string Cell::stringify() {
    return data;
}

int Cell::to_numeric() {
    return 0;
}


class Table {
    protected:
        int max_row_size;
        int max_col_size;
        Cell*** data_table;

    public:
        Table(int max_row_size, int max_col_size);
        ~Table();
        void reg_cell(Cell* cell, int row, int col);
        std::string stringify(std::string& s);
        std::string stringify(int row, int col);
        int to_numeric(std::string& s);
        int to_numeric(int row, int col);
        virtual std::string print_table() = 0; 
};

Table::Table(int max_row_size, int max_col_size) : max_row_size(max_row_size), max_col_size(max_col_size) {
    data_table = new Cell**[max_row_size];
    for (int i = 0; i < max_row_size; i++) {
        data_table[i] = new Cell*[max_col_size];
    }
    for (int i = 0; i < max_row_size; i++) {
        for (int j = 0; j < max_col_size; j++) {
            data_table[i][j] = nullptr;
        }
    }
}

Table::~Table() {
    for (int i = 0; i < max_row_size; i++) {
        for (int j = 0; j < max_col_size; j++) {
            delete data_table[i][j];
        }
    }
    for (int i = 0; i < max_row_size; i++) {
        delete[] data_table[i];
    }
    delete[] data_table;
}

void Table::reg_cell(Cell* cell, int row, int col) {
    if (!((row >= 0 && row < max_row_size) && (col >= 0 && col < max_col_size))) {
        return;
    }
    if (data_table[row][col] != nullptr) {
        delete data_table[row][col];
    }
    data_table[row][col] = cell;
}

int Table::to_numeric(std::string& s) {
    int col = s[0] - 'A';
    int row = std::stoi(s.c_str() + 1) - 1;
    if ((row >= 0 && row < max_row_size) && (col >= 0 && col < max_col_size)) {
        if (data_table[row][col] != nullptr) {
            return data_table[row][col]->to_numeric();
        }
    }
    return 0;
}

int Table::to_numeric(int row, int col) {
    if ((row >= 0 && row < max_row_size) && (col >= 0 && col < max_col_size)) {
        if (data_table[row][col] != nullptr) {
            return data_table[row][col]->to_numeric();
        }
    }
    return 0;
}

std::string Table::stringify(std::string& s) {
    int col = s[0] - 'A';
    int row = std::stoi(s.c_str() + 1) - 1;
    if ((row >= 0 && row < max_row_size) && (col >= 0 && col < max_col_size)) {
        if (data_table[row][col] != nullptr) {
            return data_table[row][col]->stringify();
        }
    }
    return "";
}

std::string Table::stringify(int row, int col) {
    if ((row >= 0 && row < max_row_size) && (col >= 0 && col < max_col_size)) {
        if (data_table[row][col] != nullptr) {
            return data_table[row][col]->stringify();
        }
    }
    return "";
}

std::ostream& operator<<(std::ostream& o, Table& table) {
    o << table.print_table();
    return o;
}

class TxtTable : public Table {
    private:
        std::string repeat_char(int n, char c);
        std::string col_num_to_char(int n);

    public:
        TxtTable(int row, int col);
        std::string print_table();
};

TxtTable::TxtTable(int row, int col) : Table(row, col) {};


std::string TxtTable::print_table() {
    std::string total_table;

    int* max_col_width = new int[max_col_size];
    for (int i = 0; i < max_col_size; i++) {
        unsigned int max_width = 2;
        for (int j = 0; j < max_row_size; j++) {
            if (data_table[j][i] != nullptr && data_table[j][i]->stringify().length() > max_width) {
                max_width = data_table[j][i]->stringify().length();
            }
        }
        max_col_width[i] = max_width;
    }

    total_table += "    ";
    int total_wide = 4;
    for (int i = 0; i < max_col_size; i++) {
        if (max_col_width[i]) {
            int max_len = std::max(max_col_width[i], 2);
            total_table += " | " + col_num_to_char(i);
            total_table += repeat_char(max_len - col_num_to_char(i).length(), ' ');
            total_wide += max_len + 3;
        }
    }

    total_table += "\n";
    for (int i = 0; i < max_row_size; i++) {
        total_table += repeat_char(total_wide, '-');
        total_table += "\n" + std::to_string(i + 1);
        total_table += repeat_char(4 - std::to_string(i + 1).length(), ' ');
        for (int j = 0; j < max_col_size; j++) {
            if (max_col_width[j]) {
                int max_len = std::max(2, max_col_width[j]);
                std::string s;
                if (data_table[i][j] != nullptr) {
                    s = data_table[i][j]->stringify();
                }
                total_table += " | " + s;
                total_table += repeat_char(max_len - s.length(), ' ');
            }
        }
        total_table += "\n";
    }
    return total_table;
}

std::string TxtTable::repeat_char(int n, char c) {
    std::string s = "";
    for (int i = 0; i < n; i++) {
        s += c;
    }
    return s;
}

std::string TxtTable::col_num_to_char(int n) {
    std::string s = "";
    if (n < 26) {
        s += ('A' + n);
    } else {
        char first = 'A' + n / 26 - 1;
        char second = 'A' + n % 26;
        s += first;
        s += second;
    }
    return s;
}

int main(void) {
    TxtTable table(10, 10);
    table.reg_cell(new Cell("Hello~", 0, 0, &table), 0, 0);
    table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);
    table.reg_cell(new Cell("Programming", 1, 1, &table), 1, 1);
    table.print_table();
    std::cout << table;
    return 0;
}
