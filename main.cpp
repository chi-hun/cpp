// 8-1

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <locale>
#include "utils.h"

class Cell;
class Table;

class Cell {
    protected:
        int x;
        int y;
        Table* table;
    
    public:
        Cell(int x, int y, Table* table);
        virtual std::string stringify() = 0;
        virtual int to_numeric() = 0;
};

Cell::Cell(int x, int y, Table* table) : x(x), y(y), table(table) {}

// std::string Cell::stringify() {
//     return data;
// }

// int Cell::to_numeric() {
//     return 0;
// }

class StringCell : public Cell {
    private:
        std::string data;

    public:
        StringCell(std::string data, int x, int y, Table* table) ;
        std::string stringify();
        int to_numeric();
};

StringCell::StringCell(std::string data, int x, int y, Table* table) : Cell(x, y, table), data(data) {}
std::string StringCell::stringify(){return data;}
int StringCell::to_numeric(){return 0;}

class NumberCell : public Cell {
    private:
        int data;

    public:
        NumberCell(int data, int x, int y, Table* table);
        std::string stringify();
        int to_numeric();
};

NumberCell::NumberCell(int data, int x, int y, Table* table) : Cell(x, y, table), data(data) {}
std::string NumberCell::stringify(){return std::to_string(data);}
int NumberCell::to_numeric(){return data;}

class DateCell : public Cell {
    private:
        std::time_t data;

    public:
        DateCell(std::string s, int x, int y, Table* table);
        std::string stringify();
        int to_numeric();
};

DateCell::DateCell(std::string s, int x, int y, Table* table) : Cell(x, y, table) {
    // s ex)2025-07-03
    int year = std::atoi(s.c_str());
    int month = std::atoi(s.c_str() + 5);
    int day = std::atoi(s.c_str() + 8);
    std::tm info;
    info.tm_year = year - 1900;
    info.tm_mon = month - 1;
    info.tm_mday = day;
    info.tm_hour = 0;
    info.tm_min = 0;
    info.tm_sec = 0;
    data = std::mktime(&info);
}
std::string DateCell::stringify(){
    char buf[50];
    // std::tm temp;
    // std::localtime(temp, &data);
    std::tm* temp_ptr = std::localtime(&data);
    std::strftime(buf, 50, "%F", temp_ptr);
    return std::string(buf);
}
int DateCell::to_numeric(){return static_cast<int>(data);}



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
    delete[] max_col_width;
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

class ExprCell : public Cell {
    private:
        std::string data;
        std::string* parsed_expr;
        MyExel::Vector exp_vec;

        int precedence(char c);
        void parse_expression();

    public:
        ExprCell(std::string data, int x, int y, Table* table);
        std::string stringify();
        int to_numeric();
};

ExprCell::ExprCell(std::string data, int x, int y, Table* table) : Cell(x, y, table), data(data) {
    parse_expression();
}

std::string ExprCell::stringify() {return std::to_string(to_numeric());}

int ExprCell::to_numeric(){
    double result = 0;
    MyExel::NumStack stack;

    for (int i = 0; i < exp_vec.size(); i++) {
        std::string s = exp_vec[i];
        if (std::isalpha(s[0])) {
            stack.push(table -> to_numeric(s));
        } else if (std::isdigit(s[0])) {
            stack.push(std::stoi(s.c_str()));
        } else {
            double y = stack.pop();
            double x = stack.pop();
            switch (s[0]) {
                case '+':
                    stack.push(x + y);
                    break;
                case '-':
                    stack.push(x - y);
                    break;
                case '*':
                    stack.push(x * y);
                    break;
                case '/':
                    stack.push(x / y);
                    break;
            }
        }
    }
    return stack.pop();
}

int ExprCell::precedence(char c) {
  switch (c) {
    case '(':
    case '[':
    case '{':
      return 0;
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
  }
  return 0;
}

void ExprCell::parse_expression() {
  MyExel::Stack stack;

  // 수식 전체를 () 로 둘러 사서 exp_vec 에 남아있는 연산자들이 push 되게
  // 해줍니다.
  data.insert(0, "(");
  data.push_back(')');

  for (int i = 0; i < data.length(); i++) {
    if (isalpha(data[i])) {
      exp_vec.push_back(data.substr(i, 2));
      i++;
    } else if (isdigit(data[i])) {
      exp_vec.push_back(data.substr(i, 1));
    } else if (data[i] == '(' || data[i] == '[' ||
               data[i] == '{') {  // Parenthesis
      stack.push(data.substr(i, 1));
    } else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
      std::string t = stack.pop();
      while (t != "(" && t != "[" && t != "{") {
        exp_vec.push_back(t);
        t = stack.pop();
      }
    } else if (data[i] == '+' || data[i] == '-' || data[i] == '*' ||
               data[i] == '/') {
      while (!stack.is_empty() &&
             precedence(stack.peek()[0]) >= precedence(data[i])) {
        exp_vec.push_back(stack.pop());
      }
      stack.push(data.substr(i, 1));
    }
  }
}

int main(void) {
    TxtTable table(5, 5);
    table.reg_cell(new NumberCell(2, 1, 1, &table), 1, 1);
    table.reg_cell(new NumberCell(3, 1, 2, &table), 1, 2);
    table.reg_cell(new NumberCell(4, 2, 1, &table), 2, 1);
    table.reg_cell(new NumberCell(5, 2, 2, &table), 2, 2);
    table.reg_cell(new ExprCell("B2+B3*(C2+C3-2)", 3, 3, &table), 3, 2);
    table.reg_cell(new StringCell("B2 + B3 * ( C2 + C3 - 2 ) = ", 3, 2, &table),3, 1);
    // table.print_table();
    std::cout << table;
    std::ofstream out("test.txt");
    out << table;
    out.close();
    return 0;
}
