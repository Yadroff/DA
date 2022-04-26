#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

const char DIGITS_NUMBER = 10;
const char COUNTRY_CODE_SIZE = 3;
const char CITY_CODE_SIZE = 3;
const char TELEPHONE_NUMBER_SIZE = 7;
const char VALUE_SIZE = 64;



class TObject {
public:
    TObject() {
        for (int i = 0; i <= VALUE_SIZE; ++i){
            VALUE[i] = '\0';
        }
        for (int i = 0; i <= CITY_CODE_SIZE; ++i){
            CITY_CODE[i] = '\0';
        }
        for (int i = 0; i <= COUNTRY_CODE_SIZE; ++i){
            COUNTRY_CODE[i] = '\0';
        }
        for (int i = 0; i <= TELEPHONE_NUMBER_SIZE; ++i){
            TELEPHONE_NUMBER[i] = '\0';
        }
    };

    explicit TObject(std::string &string);

    friend std::istream &operator>>(std::istream &is, TObject &obj);

    friend std::ostream &operator<<(std::ostream &os, TObject &obj);

    char VALUE[VALUE_SIZE + 1] = {'\0'};
    char COUNTRY_CODE[COUNTRY_CODE_SIZE + 1] = {'\0'};
    char CITY_CODE[CITY_CODE_SIZE + 1] = {'\0'};
    char TELEPHONE_NUMBER[TELEPHONE_NUMBER_SIZE + 1] = {'\0'};
};

TObject::TObject(std::string &string) {
    std::stringstream telephone_value_stream(string);
    telephone_value_stream.ignore();
    telephone_value_stream.getline(this->COUNTRY_CODE, COUNTRY_CODE_SIZE + 1, '-');
    telephone_value_stream.getline(this->CITY_CODE, CITY_CODE_SIZE + 1, '-');
    telephone_value_stream.getline(this->TELEPHONE_NUMBER, TELEPHONE_NUMBER_SIZE + 1, '\t');
    telephone_value_stream.getline(this->VALUE, VALUE_SIZE + 1);
}

std::istream &operator>>(std::istream &is, TObject &obj) {
    std::string input_string;
    std::getline(is, input_string);
    std::stringstream telephone_value_stream(input_string);
    telephone_value_stream.ignore();
    telephone_value_stream.getline(obj.COUNTRY_CODE, COUNTRY_CODE_SIZE + 1, '-');
    telephone_value_stream.getline(obj.CITY_CODE, CITY_CODE_SIZE + 1, '-');
    telephone_value_stream.getline(obj.TELEPHONE_NUMBER, TELEPHONE_NUMBER_SIZE + 1, '\t');
    telephone_value_stream.getline(obj.VALUE, VALUE_SIZE + 1);
    return is;
}

std::ostream &operator<<(std::ostream &os, TObject &obj) {
    os << '+' << obj.COUNTRY_CODE << '-' << obj.CITY_CODE << '-' << obj.TELEPHONE_NUMBER << '\t' << obj.VALUE;
    return os;
}


void RadixSort(std::vector<TObject> &vector) {
    for (auto &obj: vector){
        while (obj.COUNTRY_CODE[2] == '\0'){ // смещаем число вправо, иначе 7 > 675
            char tmp = obj.COUNTRY_CODE[2];
            for (int i = 2; i > 0; --i){
                obj.COUNTRY_CODE[i] = obj.COUNTRY_CODE[i - 1];
            }
            obj.COUNTRY_CODE[0] = tmp;
        }
    }
    // проходим справа налево по номеру и сортируем по i-й позиции номера
    for (int i = TELEPHONE_NUMBER_SIZE - 1; i >= 0; --i) { // сортируем по номеру телефона
        int cnt[DIGITS_NUMBER] = {0};
        for (auto &obj: vector) {
            ++cnt[obj.TELEPHONE_NUMBER[i] - '0'];
        }
        for (int k = 1; k < DIGITS_NUMBER; ++k) { // считаем префиксную сумму
            cnt[k] += cnt[k - 1];
        }
        std::vector<TObject> tmp(vector);
        for (int k =(int) vector.size() - 1; k >= 0; --k){
            vector[--cnt[tmp[k].TELEPHONE_NUMBER[i] - '0']] = tmp[k];
        }
    }
    for (int i = CITY_CODE_SIZE - 1; i >= 0; --i){
        int cnt[DIGITS_NUMBER] = {0};
        for (auto &obj: vector) {
            ++cnt[obj.CITY_CODE[i] - '0'];
        }
        for (int k = 1; k < DIGITS_NUMBER; ++k) { // считаем префиксную сумму
            cnt[k] += cnt[k - 1];
        }
        std::vector<TObject> tmp(vector);
        for (int k =(int) vector.size() - 1; k >= 0; --k){
            vector[--cnt[tmp[k].CITY_CODE[i] - '0']] = tmp[k];
        }
    }
    for (int i = COUNTRY_CODE_SIZE - 1; i >= 0; --i){
        int cnt[DIGITS_NUMBER] = {0};
        for (auto &obj: vector) {
            obj.COUNTRY_CODE[i] == '\0' ? ++cnt[0] : ++cnt[obj.COUNTRY_CODE[i] - '0'];
        }
        for (int k = 1; k < DIGITS_NUMBER; ++k) { // считаем префиксную сумму
            cnt[k] += cnt[k - 1];
        }
        std::vector<TObject> tmp(vector);
        for (int k =(int) vector.size() - 1; k >= 0; --k){
            int ind = tmp[k].COUNTRY_CODE[i] == '\0' ? --cnt[0] : --cnt[tmp[k].COUNTRY_CODE[i] - '0'];
            vector[ind] = tmp[k];
        }
    }
    for (auto &obj: vector){ // смещаем первое число обратно для вывода
        while (obj.COUNTRY_CODE[0] == '\0'){
            char tmp = obj.COUNTRY_CODE[0];
            for (int i = 0; i < 2; ++i){
                obj.COUNTRY_CODE[i] = obj.COUNTRY_CODE[i+1];
            }
            obj.COUNTRY_CODE[2] = tmp;
        }
    }
}

int main() {
    clock_t start = clock();
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::vector<TObject> vector(0);
    vector.reserve(1000000);
    std::string string;
    while (getline(std::cin, string)) {
        while (string.empty()){
            getline(std::cin, string);
        }
        vector.emplace_back(string);
    }
    RadixSort(vector);
    for (auto &x: vector) {
        std::cout << x << '\n';
    }
    clock_t end = clock();
    std::cout << (end - start) << std::endl;
    return 0;
}
