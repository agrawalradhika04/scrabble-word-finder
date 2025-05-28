#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to calculate the score for each word
// Pre: Takes a vector of strings containing letters in hand and the word formed of string datatype
// Post: Returns the score of that word of int datatype
int score(const vector<char> &list_of_letters, string word){
    vector<char> letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	
	// Points in correspondence to each letter in the vector called letters
    vector<int> points = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	
	int score = 0;
	
	for(int i = 0; i < word.size(); i++){
		for(int j = 0; j < letters.size(); j++){
			if(word[i] == letters[j])
				score = score + points[j];
		}
	}
	// Any words that use all of the letters provided by the user (the typical hand size is 7) gain 50 extra points.
	if(list_of_letters.size() == word.size() - 1) // Letter on board, which has been used in the word, is not a part of letters in hand
		score = score + 50;
	return score;
}

// Function to see if a word is in the list
// Pre: Takes in a vector of strings containing all the words and a key of string datatype which is to be found
// Post: Returns true if the key is found, false otherwise
bool binary_search(const vector<string> &list, string key){
	int low = 0;
	int high = list.size() - 1;
	
	while(low <= high){
		int mid = (low + high)/2;
		if(list[mid] == key) // Key found
			return true;
		else if(list[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	// Exited the loop, meaning key not found
	return false; 
}

// Recursive backtracking function
// Pre: Takes in a boolean vector to keep track of letters that have been used, a vector of strings containing all the words, a vector of strings containing letters in hand, a letter on board as string datatype and its position as boolean type, and a string of the current word.
// Post: Prints out all legal words that can be made using the letters in hand, in accordance with the position of the letter on board, along with their scores. A word is legal if it is present in the wordlist file.
void find_legal_words(vector<bool> &letters_used, const vector<string> &list, const vector<char> &list_of_letters, string letter_on_board, bool letter_position, string cur_word){
    
    // Base case: All letters inputted have been used, so return
    bool chosen = true;
    for(int i = 0; i < letters_used.size(); i++){
        if(letters_used[i] == false) // Checking if an element in the vector called letters_used is false
            chosen = false;
    }
    if(chosen) // Chosen is true, meaning all elements in the vector called letters_used are true
            return;
    
    // Recursive Case: Add an unused letter to the current word. If the new word exists in our wordlist, which can be checked using binary search, print that word with its score.
    for(int i = 0; i < list_of_letters.size(); ++i){
        if(!letters_used[i]){ // Checking if the letter is unused
            letters_used[i] = true;
            
            if(letter_position){ // Letter on board is at the beginning of the word
                cur_word = cur_word + list_of_letters[i];
                
                if(binary_search(list, cur_word))
                    cout << cur_word << " " << score(list_of_letters, cur_word) << endl;
                
                find_legal_words(letters_used, list, list_of_letters, letter_on_board, letter_position, cur_word);
                letters_used[i] = false;
                cur_word = cur_word.substr(0, cur_word.size() - 1);
            }
            else{ // Letter on board is at the end of the word
                cur_word =  cur_word + list_of_letters[i];
                
                if(binary_search(list, cur_word + letter_on_board))
                    cout << cur_word + letter_on_board << " " << score(list_of_letters, cur_word + letter_on_board) << endl;
                
                find_legal_words(letters_used, list, list_of_letters, letter_on_board, letter_position, cur_word);
                letters_used[i] = false;
                cur_word = cur_word.substr(0, cur_word.size() - 1);
            }
        }
    }
}

int main(){
	
	cout << "Enter the name of the wordlist file: ";
	string filename;
	cin >> filename;
	
	ifstream file;
	
	file.open(filename); // Assuming the filename entered is correct
	
	// Reading the file as a vector
	vector<string> list;
	string entry;
	while(file >> entry){
		list.push_back(entry);
	}
	
	bool play = 1;
    
	
	while(play){
		cout << "Enter your current letters: ";
		string cur_letters;
		cin >> cur_letters;

		// Making a vector of the string
		vector<char> list_of_letters(cur_letters.begin(), cur_letters.end());

		cout << "What letter is on the board? ";
		string letter_on_board;
		cin >> letter_on_board;

		cout << "Is this letter at the beginning of the word? Enter 1 for yes and 0 for no. ";
		bool letter_position;
		cin >> letter_position;

        // Boolean vector to keep check if a particular letter in hand has been used
        vector<bool> letters_used(list_of_letters.size(), false);
        
        if(letter_position){ // Letter on board is at the beginning of the word
            find_legal_words(letters_used, list, list_of_letters, letter_on_board, letter_position, letter_on_board);
        }
        else{ // Letter on board is at the end of the word
            find_legal_words(letters_used, list, list_of_letters, letter_on_board, letter_position, "");
        }
        
		cout << "Go again? Enter 1 for yes and 0 for no. ";
		cin >> play;
	}
	
	return 0;
}
