// FindWordsMadeOfOtherWordsInTheList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
using namespace std;

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

std::set<std::wstring> gWordsDict;

bool FileExists(wstring filePath)
{
	wfstream infile(filePath);
    return infile.good();	
}

void ShowUsage()
{
	cout << "Usage:" << endl;
    cout << "  FindWordsMadeOfOtherWords.py <inputFileName> numberOfWordsMadeOfOtherWordsToFind" << endl;
    cout << "    Where" << endl;
    cout << "      <inputFilePath> is a path to a file that has words sorted alphabetically one word per line" << endl;
    cout << "      <numberOfWordsMadeOfOtherWordsToFind> if 2 it will find the 2 longest words made of other words in the list." << endl;
    cout << "                                            if the value is -1 then it will return 2 longest word, " << endl;
    cout << "                                            and the total number of word that are made of other workds in the list" << endl;
    cout << "End." << endl;
}

std::vector<std::wstring> ReadFileLineByLine(const std::wstring& filePath)
{
	std::wfstream hFile(filePath);

	std::vector<std::wstring> lines;
	std::wstring line = _T("");
	while(getline(hFile, line))
	{
		lines.push_back(line);
	}

  return lines;
}

std::set<std::wstring> ReadFileLineByLineAsSet(const std::wstring& filePath)
{
	std::wfstream hFile(filePath);

	std::set<std::wstring> lines;
	std::wstring line = _T("");
	while(getline(hFile, line))
	{
		lines.insert(line);
	}

  return lines;
}

bool reverseCompareWStringLength (const wstring& s1, const wstring& s2)
{
    return s1.length() > s2.length();
}

/*
Recursive method that check if a word is made of other words in the list.
   1. First finds substr that belongs to the list,
   2. then takes restOfStr call the method recursively to see if that is made of other words in the list
   3. if restOfStr is made of the other words in the list then returns True
   4. if not returns False
Arguments:
    word (wstring):   input word
Returns:
    returns True if the words is made of other words if not False
*/
bool IsWordMadeOfOtherWords(const wstring& word)
{
    bool isWordMadeOfOtherWords = false;

    int wordLength = word.length();
    for (int subStrEnd = 1; subStrEnd < wordLength+1; subStrEnd++)
	{
        wstring subStr = word.substr( 0, subStrEnd);
        wstring restOfStr = word.substr(subStrEnd);
		if (gWordsDict.find(subStr) != gWordsDict.end()) 
		{
            if (restOfStr != _T(""))
			{
                isWordMadeOfOtherWords = IsWordMadeOfOtherWords(restOfStr);
                if (isWordMadeOfOtherWords)
				{
                    return isWordMadeOfOtherWords;
				}
			} 
			else 
			{
                isWordMadeOfOtherWords = true;
                return isWordMadeOfOtherWords;
			}
		} 
		else
		{
            isWordMadeOfOtherWords = false;
		}
	}

    return isWordMadeOfOtherWords;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Parse out the commandline arguments
	wstring inputFilePath = _T("");
	int numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind = 1;
	if (argc >= 2) {
		inputFilePath = argv[1];
		if (!FileExists(inputFilePath)) {
			ShowUsage();
			return 0;
		}
		if (argc >= 3) {
			numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind = ::_wtoi(argv[2]);
			if (numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind == 0) {
				numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind = 1;
			}
		}
	} else {
		ShowUsage();
		return 0;
	}

	cout << "Loading the input file line by line as vector" << endl;	
	vector<wstring> sortedWords = ReadFileLineByLine(inputFilePath);
	cout << "sorting the vector of strings" << endl;
	std::sort(sortedWords.begin(), sortedWords.end(), reverseCompareWStringLength);

	cout << "Copying Vector to a Set" << endl;
	gWordsDict = std::set<wstring>(sortedWords.begin(), sortedWords.end());

	cout << "Finding Words that are made of other words in the list" << endl;
	std::vector<std::wstring> WordsMadeOfOtherWords;
	for (std::vector<std::wstring>::iterator iter = sortedWords.begin();
											iter != sortedWords.end();
											++iter)
	{
		std::wstring word = *iter;
		gWordsDict.erase(word);
        if (IsWordMadeOfOtherWords(word))
		{
			WordsMadeOfOtherWords.push_back(word);
			// if numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind is < 0 find all the words made of other words in the list,
			// if not break as soon as we find the requested number.
            if (numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind > 0 && numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind == WordsMadeOfOtherWords.size())
			{
                break;
			}
		}
	}

    cout << endl << ">>>>>>>>>>>>>>>>>>>>>>" << endl;
    if (numberOfLongestWordsMadeOfOtherWordsThatWeNeedToFind == -1) 
	{
		cout << "5 longest words that are made of other words in the list are:" << endl;
		for (std::vector<wstring>::iterator iter = WordsMadeOfOtherWords.begin();
											iter != WordsMadeOfOtherWords.end() && iter != WordsMadeOfOtherWords.begin()+5;
											++iter) 
		{
			std::wcout << *iter << std::endl;
		} 
		cout << "-------------------------" << endl;
		cout << "Total number of words that are made of other words in the list: " <<  WordsMadeOfOtherWords.size() << " out of all the elements in the input list " << sortedWords.size() << "." << endl;
	} 
	else 
	{
		cout <<  WordsMadeOfOtherWords.size() << " longest words that are made of other words in the list are:" << endl;
		for (std::vector<wstring>::iterator iter = WordsMadeOfOtherWords.begin();
											iter != WordsMadeOfOtherWords.end();
											++iter) 
		{
			std::wcout << *iter << std::endl;
		}
	}
    cout << "<<<<<<<<<<<<<<<<<<<<<<" << endl;
	
	return 0;
}

