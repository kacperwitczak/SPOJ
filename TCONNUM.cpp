#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
 
char convertToNumber(char c) {
    if (isdigit(c)) {
        c -= '0';
    }
    else {
        c -= 'A';
        c += 10;
    }
    return c;
}
 
char convertToChar(int c) {
    if (c >= 0 && c < 10) {
        return c + '0';
    }
    else {
        return c + 'A' - 10;
    }
}
 
bool isZero(std::vector<int>& number) {
    if (number.empty()) {
        return true;
    }
    for (auto& i : number) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}
 
void cutZeros(std::vector<int> &numbers) {
    while (!numbers.empty() && numbers[0] == 0 ) {
        numbers.erase(numbers.begin());
    }
}
 
void convertFromRToS(std::vector<int> &number, int baseR, int baseS) {
    std::vector<int> converted;
    if (isZero(number)) {
        converted.push_back(0);
    }
    while (!isZero(number)) {
        std::vector<int> next;
        for (int i = 0; i < number.size(); i++) {
            int val = number[i];
            int whole = val / baseS;
            int rest = val % baseS;
            if (i == number.size() - 1) {
                converted.push_back(rest);
                next.push_back(whole);
            }
            else {
                number[i + 1] = number[i + 1] + rest * baseR;
                next.push_back(whole);
            }
        }
        cutZeros(next);
        number = next;
    }
    std::reverse(converted.begin(), converted.end());
    number = converted;
};
 
std::vector<int> mapToInt(std::string& numberString) {
    std::vector<int> result;
    for (auto& c : numberString) {
        result.push_back(convertToNumber(c));
    }
    return result;
}
 
std::string maptoChar(std::vector<int>& number) {
    std::string result = "";
    for (auto& i : number) {
        result += convertToChar(i);
    }
    return result;
}
 
int main()
{
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    while (n > 0) {
        std::string numberString;
        int baseR;
        int baseS;
        std::cin >> numberString >> baseR >> baseS;
        std::vector<int> number = mapToInt(numberString);
        convertFromRToS(number, baseR, baseS);
        numberString = maptoChar(number);
        std::cout << numberString << '\n';
        n--;
    }
    return 0;
}
 
 
