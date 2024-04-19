#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
 
void printBooks(std::unordered_map<int,int> &bp) {
	for (int i = 0; i < bp.size(); i++) {
		std::cout << bp[i] << ' ';
	}
	std::cout << '\n';
}
 
void swapPositions(std::unordered_map<int, int>& bTp,int bookA, int bookB,std::unordered_map<int, int>& pTb, int indexA, int indexB) {
	int tempPosA = bTp[bookA];
	bTp[bookA] = bTp[bookB];
	bTp[bookB] = tempPosA;
	int tempBookA = pTb[indexA];
	pTb[indexA] = pTb[indexB];
	pTb[indexB] = tempBookA;
}
 
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
 
	//collecting data
	int n;
	std::cin >> n;
	std::vector<int> books(n);
	std::unordered_map<int, int> bookToPosition;
	std::unordered_map<int, int> positionToBook;
	for (int i = 0; i < n; i++) {
		std::cin >> books[i];
		bookToPosition[books[i]] = i;
		positionToBook[i] = books[i];
	}
 
	std::deque<int> sortedBooks(books.size());
	std::copy(books.begin(), books.end(), sortedBooks.begin());
	std::sort(sortedBooks.begin(), sortedBooks.end(), [](int a, int b) {
		return a > b;
		});
 
	std::vector<int> moves(n);
	for (int i = 0; i < n; i++) {
		std::cin >> moves[i];
		moves[i]--;
	}
 
	int stateToShow;
	std::vector<int> statesToShow;
	while (std::cin >> stateToShow) {
		statesToShow.emplace_back(--stateToShow);
	}
 
	int lastIndexInBooks = books.size() - 1;
	int indexInStatesToCheck = 0;
	int m;
	int book;
	int bookToSwap;
 
	for (int i = 0; i < moves.size(); i++) {
		m = moves[i];
		book = sortedBooks[m]; //book to shuffle
		sortedBooks.erase(sortedBooks.begin() + m); //deleted taken book
		bookToSwap = positionToBook[lastIndexInBooks];
		swapPositions(bookToPosition, book, bookToSwap,positionToBook,bookToPosition[book], lastIndexInBooks);
		lastIndexInBooks--;
		if (i == statesToShow[indexInStatesToCheck]) {
			printBooks(positionToBook);
			indexInStatesToCheck++;
		}
	}
 
	return 0;
} 
