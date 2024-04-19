//korzystaÅem z poniÅ¼szych zrodel
//https://en.wikipedia.org/wiki/Largest_differencing_method
//https://en.wikipedia.org/wiki/Partition_problem
//https://stackoverflow.com/questions/3889783/how-does-the-karmarkar-karp-differencing-algorithm-work
 
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <deque>
 
struct IndexItem {
    int index;
    long long item;
 
    bool operator==(const IndexItem& other) const {
        return other.item == this->item;
    }
};
 
struct Step {
    IndexItem large;
    IndexItem small;
};
 
 
 
void KarmarkarKarp(std::stack<long long>& differences, std::stack<Step>& steps, std::deque<IndexItem>& items) {
    while (!items.empty())
    {
        std::sort(items.begin(), items.end(), [](const IndexItem& a, const IndexItem& b) {
            return a.item > b.item;
            });
        IndexItem itemLarge = items.front();
        items.pop_front();
        //index = -1 oznacza, Å¼e element jest roznica pomiedzy dwoma najwiekszymi elementami
        IndexItem itemSmall = { -1,-1 };
        if (!items.empty()) {
            itemSmall = items.front();
            items.pop_front();
            items.emplace_back(IndexItem{ -1, itemLarge.item - itemSmall.item });
        }
        steps.emplace(Step{ itemLarge,itemSmall });
        differences.emplace(itemLarge.item - itemSmall.item);
    }
}
 
std::vector<IndexItem> KarmarkarKarpWithBacktracking(std::deque<IndexItem>& items) {
    std::stack<long long> differences;
    std::stack<Step> steps;
    KarmarkarKarp(differences, steps, items);
 
    //rekonstrukcja zbiorÃ³w
    std::vector<IndexItem> leftHand;
    std::vector<IndexItem> rightHand;
 
    while (!steps.empty()) {
        Step s = steps.top();
        steps.pop();
        long long diff = differences.top();
        differences.pop();
        //sprawdzenie czy w lewym zbiorze istnieje element rÃ³wny rÃ³Åºnicy
        auto itemLeft_iterator = std::find(leftHand.begin(), leftHand.end(), IndexItem{ -1,diff });
        auto itemRight_iterator = std::find(rightHand.begin(), rightHand.end(), IndexItem{ -1,diff });
        //roznica jest w lewym zbiorze
        if (itemLeft_iterator != leftHand.end()) {
            leftHand.erase(itemLeft_iterator);
            leftHand.emplace_back(s.large);
            rightHand.emplace_back(s.small);
        }
        else {
            if (itemRight_iterator != rightHand.end()) {
                rightHand.erase(itemRight_iterator);
            }
            leftHand.emplace_back(s.small);
            rightHand.emplace_back(s.large);
        }
    }
 
    return leftHand;
}
 
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
 
    int n;
    std::cin >> n;
    std::deque<IndexItem> items; //index and item
    for (int i = 1; i <= n; i++) {
        long long item;
        std::cin >> item;
        items.emplace_back(IndexItem{i,item});
    }
    std::vector<IndexItem> leftHand = KarmarkarKarpWithBacktracking(items);
 
    for (int i = leftHand.size() - 1; i >= 0; i--) {
        if (leftHand[i].item != -1) {
            std::cout << leftHand[i].index << '\n';
        }
    }
} 
