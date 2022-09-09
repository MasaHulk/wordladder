#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <fstream>

void printSet(std::set<std::string>&);
void initializeWords(std::string&,std::string&);
bool checkWords(std::string&,std::string&,std::set<std::string>&);
void printLadder(std::vector<std::string>&);

int main(){
    std::ifstream myfile("EnglishWords.txt");
    std::set<std::string> Lexicon;
    std::string word;
    //input words from .txt file
    if(myfile.is_open()){
        while(myfile >> word){
            Lexicon.insert(word);
        }
    }
    //initialization of start and destination words
    std::string START_WORD;
    std::string DEST_WORD;
    initializeWords(START_WORD,DEST_WORD);

    //checks if words exists in Lexicon
    if(checkWords(START_WORD,DEST_WORD,Lexicon)){
        std::queue<std::vector<std::string>> NODES_QUEUE;//create an empty queue        
        std::set<std::string> VISITED_NODES;
        std::vector<std::string> CURRENT_LADDER;
        std::string CURRENT_WORD;
        std::vector<std::string> COPY_CURRENT_LADDER;
        CURRENT_LADDER.push_back(START_WORD);        
        NODES_QUEUE.push(CURRENT_LADDER);//push ladder to queue

        //main algorithm
        while(!NODES_QUEUE.empty()){            
            CURRENT_LADDER = NODES_QUEUE.front();//assign next ladder to current ladder vector            
            NODES_QUEUE.pop();//dequeue the first ladder              
            
            if(CURRENT_LADDER[CURRENT_LADDER.size()-1] == DEST_WORD){//if final word in ladder is dest word, print
                printLadder(CURRENT_LADDER);
                break;
            }   
            //for each word in this lexicon which differs by one letter
            for(int i = 0; i < START_WORD.size(); i ++){//iterate through characters of string
                for(char c = 'a'; c <= 'z' ; c ++){//replace word letter with whole alphabet
                    CURRENT_WORD = CURRENT_LADDER[CURRENT_LADDER.size()-1];
                    CURRENT_WORD[i] = c;                    
                    if(Lexicon.find(CURRENT_WORD) != Lexicon.end() && VISITED_NODES.find(CURRENT_WORD) == VISITED_NODES.end()){                        
                        COPY_CURRENT_LADDER = CURRENT_LADDER;
                        COPY_CURRENT_LADDER.push_back(CURRENT_WORD);
                        NODES_QUEUE.push(COPY_CURRENT_LADDER);
                        VISITED_NODES.insert(CURRENT_WORD);
                    }
                }
            }
        }
    }

    return 0;
}

void printSet(std::set<std::string>& set){
    std::set<std::string>::iterator it;

    for(it = set.begin(); it != set.end(); it ++){
        std::cout << *it << std::endl;
    }

}

void initializeWords(std::string& start,std::string& dest){
    while(1){
        std::cout << "Enter start word : ";
        std::cin >> start;
        std::cout << "Enter destination word : ";
        std::cin >> dest;       
        if(start.size() == dest.size()){
            break; 
        }         
    }
    
}

bool checkWords(std::string& s1,std::string& s2,std::set<std::string>& set){
    if(set.find(s1) != set.end() && set.find(s2) != set.end()){
        return true;
    } else {
        return false;
    }
}

void printLadder(std::vector<std::string>& v){
    std::cout << "\n" << "Path from start word to destination word is : " << "\n";
    for(int i = 0; i < v.size(); i ++){
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}