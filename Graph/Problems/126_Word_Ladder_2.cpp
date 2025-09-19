#include <bits/stdc++.h>
using namespace std;

//------------------------Basic Approach : ----------------------


class Solution
{
public:
    vector<vector<string>> findSequences(string beginWord, string endWord,
                                         vector<string> &wordList)
    {
        // Push all values of wordList into a set
        // to make deletion from it easier and in less time complexity.
        unordered_set<string> st(wordList.begin(), wordList.end());
        
        // Creating a queue ds which stores the words in a sequence which is
        // required to reach the targetWord after successive transformations.
        queue<vector<string>> q;

        // BFS traversal with pushing the new formed sequence in queue 
        // when after a transformation, a word is found in wordList.

        q.push({beginWord});

        // A vector defined to store the words being currently used
        // on a level during BFS.
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
       
        // A vector to store the resultant transformation sequence.
        vector<vector<string>> ans;
        while (!q.empty())
        {
            vector<string> vec = q.front();
            q.pop();

            // Now, erase all words that have been
            // used in the previous levels to transform
            if (vec.size() > level)
            {
                level++;
                for (auto it : usedOnLevel)
                {
                    st.erase(it);
                }
            }

            string word = vec.back();

            // store the answers if the end word matches with targetWord.
            if (word == endWord)
            {
                // the first sequence where we reached end
                if (ans.size() == 0)
                {
                    ans.push_back(vec);
                }
                else if (ans[0].size() == vec.size())
                {
                    ans.push_back(vec);
                }
            }
            for (int i = 0; i < word.size(); i++)
            {   
                // Now, replace each character of ‘word’ with char
                // from a-z then check if ‘word’ exists in wordList.
                char original = word[i];
                for (char c = 'a'; c <= 'z'; c++)
                {
                    word[i] = c;
                    if (st.count(word) > 0)
                    { 
                        // Check if the word is present in the wordList and
                        // push the word along with the new sequence in the queue.
                        vec.push_back(word);
                        q.push(vec);
                        // mark as visited on the level
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i] = original;
            }
        }
        return ans;
    }
};










//------------------------Advanced Approach : ----------------------
// link to refer -> https://leetcode.com/problems/word-ladder-ii/solutions/6319954/i-spent-3-hours-developing-this-fastest-approach-check-it-out-and-don-t-forget-to-drop-a-like/


class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> depthMap;
        vector<vector<string>> ans;
        
        // BFS to find the shortest path
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        queue<string> q;
        q.push(beginWord);
        depthMap[beginWord] = 1;
        wordSet.erase(beginWord);
        
        while (!q.empty()) {
            string word = q.front();
            q.pop();
            int steps = depthMap[word];
            if (word == endWord) break;
            for (int i = 0; i < word.size(); ++i) {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    word[i] = ch;
                    if (wordSet.count(word)) {
                        q.push(word);
                        wordSet.erase(word);
                        depthMap[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }
        
        // DFS to find all paths
        if (depthMap.count(endWord)) {
            vector<string> seq = {endWord};
            dfs(endWord, beginWord, seq, depthMap, ans);
        }
        
        return ans;
    }
    
private:
    void dfs(string word, string beginWord, vector<string>& seq, unordered_map<string, int>& depthMap, vector<vector<string>>& ans) {
        if (word == beginWord) {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }
        
        int steps = depthMap[word];
        for (int i = 0; i < word.size(); ++i) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                word[i] = ch;
                if (depthMap.count(word) && depthMap[word] + 1 == steps) {
                    seq.push_back(word);
                    dfs(word, beginWord, seq, depthMap, ans);
                    seq.pop_back();
                }
            }
            word[i] = original;
        }
    }
};