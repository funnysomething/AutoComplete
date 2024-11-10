#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>

using namespace std;
#define ALPHABET_SIZE 26

struct Comparator{
    bool operator()(const pair<int, string>& a, const pair<int, string>& b){
        return a.first>b.first;
    }
};

struct TrieNode {
    unordered_map<int, TrieNode*> children;
    int priority;
    bool isWord;
};

class AutoComplete {
    private:
        TrieNode* root;
        TrieNode* createnode(){
            TrieNode* newNode = new TrieNode;
            newNode->isWord = false;
            newNode->children = {};
            return newNode;
        };
        bool is_leaf(TrieNode* curr){
            return curr->children.empty();
        }
        priority_queue<pair<int, string>, vector<pair<int, string>>, Comparator> 
            get_suggestionsrec(
                TrieNode* curr, string prefix, 
                priority_queue<pair<int, string>, 
                vector<pair<int, string>>, Comparator> acc
                ){
            if (curr->isWord){
                acc.push({curr->priority, prefix});
            }
            for (int i = 0; i  < ALPHABET_SIZE; i++){
                if (curr->children.count(i)){
                    char c = i + 'a';
                    acc = get_suggestionsrec(curr->children[i], prefix + c, acc);
                }
            }
            return acc;
        }
    public:
        AutoComplete(){
            root = createnode();
            ifstream Dictionary("most-common.txt");
            string text;
            int line = 0;
            while (getline (Dictionary, text)){
                insert(text, line++);
            }
            Dictionary.close();
        }
        int insert(string key, int priority){
            TrieNode* curr = root;
            for (char c : key){
                int index = tolower(c) - 'a';
                if (!curr->children.count(index)){
                    curr->children.emplace(index, createnode());
                }
                curr = curr->children[index];
            }
            curr->priority = priority;
            curr->isWord = true;
            return 1;
        }
        vector<string> get_suggestions(string prefix){
            TrieNode* curr = root;
            if (prefix.empty()){
                return {};
            }
            for (char c : prefix){
                int index = tolower(c) -'a';
                if (!curr->children.count(index)){
                    cout << "Couldn't find suggestions for " << prefix << '\n';
                    return {};
                }
                curr = curr->children[index];
            }

            priority_queue<pair<int, string>, vector<pair<int, string>>, Comparator> 
                queue = get_suggestionsrec(curr, prefix, {});
            vector<string> ret;
            //Converting priority_queue to vector
            while (!queue.empty()){
                ret.push_back(queue.top().second);
                queue.pop();
            }
            return ret;
        }
};