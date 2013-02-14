#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <list>
#include <algorithm>
//recursively genereate all possible inputs

void writeToFile(std::vector<int>& out){
    int end = out.size();
    char fileName[20];
//    std::sort(out.begin(),out.end());
    std::sprintf(fileName, "%d.txt", end);
    std::ofstream output(fileName, std::ios_base::app);
    for(int i=0; i< end; ++i)
	output << out[i] << " ";
    output << "\n";
    output.close();
	
}

void removeDuplicates(int n){
    //Scans through the current file and removes duplicate elts
    std::list<std::vector<int> > entries;
    char fileName[20];
    std::sprintf(fileName, "%d.txt", n);
    std::ifstream file(fileName);
    //Add everything in the file to the list
    while(!file.eof()&& file.good()){//Infinite Loop, also only reading the first line
	std::vector<int> currEntry;
	currEntry.reserve(n);
	char* line = new char[3*n];
	file.getline(line,3*n);
	std::stringstream s(line);
	for(int number; s >> number;)
	    currEntry.push_back(number);
	entries.push_back(currEntry);
	delete[] line;
    }

    file.close();
    
    //Search the rest of the list for peermutations of the curr vector
    std::list<std::vector<int> >::iterator it = entries.begin(), end = entries.end();
    for(; it != end;){
	std::list<std::vector<int> >::iterator curr = it;
	std::remove(++it, end, *curr);
    }

    //Remove fileName so that it can be recreated.
    std::remove(fileName);
    
    // Now write it all back
    for(it= entries.begin(); it != end; ++it)
	writeToFile(*it);
    
}

void generate(int n){
    //All tokens in new slot
    std::vector<int> currOut(n,0);
    currOut[n-1] = n;
    writeToFile(currOut);
    
    char fileName[20];

    //iterative over all but 0 tokens in the new slot
    for(int i = 1; i < n; ++i){
	std::sprintf(fileName, "%d.txt", i);
	std::ifstream in(fileName);
	while(!in.eof()){
	    currOut.resize(n,50);
	    char* line = new char[3*n];
	    in.getline(line, 3*n);
	    if(0 == std::strcmp(line,"")){
		delete[] line;
		continue;
	    }
	    std::stringstream s(line);
	    int j = 0;
	    for(int number; s >> number; ++j)
		currOut[j] = number;
	    currOut[n-1] = n-i;
	    writeToFile(currOut);
	    delete[] line;
	}
	in.close();
    }
    

    //No token is the new slot
    std::sprintf(fileName, "%d.txt", n-1);
    std::ifstream in(fileName);
    while(!in.eof()){
	char* line = new char[3*n];
	in.getline(line,3*n);
	for(int k = 0; k < n-1; ++k){
	    //currOut.clear();
	    //currOut.reserve(n+1);
	    currOut.resize(n+1,0);
	    if(0 == std::strcmp(line, "")){
		delete[] line;
		continue;
	    }
	    std::stringstream vecLine(line);
	    int j = 0;
	    for(int number; vecLine >> number; ++j)
		currOut[j] = number;
	    currOut[k] += 1;
	    currOut[n-1] = 0;
	    currOut[n]=k;
	    writeToFile(currOut);
	    delete[] line;
	}
    }
    in.close();
}

int main(){
    generate(2);
    //removeDuplicates(3);
    return 0;
}
