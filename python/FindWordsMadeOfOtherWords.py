import os
import sys
import datetime

def ShowUsage():
    print "Usage:"
    print "  FindWordsMadeOfOtherWords.py <inputFileName> numberOfWordsMadeOfOtherWordsToFind"
    print "    Where"
    print "      <inputFilePath> is a path to a file that has words sorted alphabetically one word per line"
    print "      <numberOfWordsMadeOfOtherWordsToFind> if 2 it will find the 2 longest words made of other words in the list." \
          "                                            if the value is -1 then it will return 2 longest word, " \
          "                                            and the total number of word that are made of other workds in the list"
    print "End."

gWordsDict = {}

"""
Recursive method that check if a word is made of other words in the list.
   1. First finds substr that belongs to the list,
   2. then takes restOfStr call the method recursively to see if that is made of other words in the list
   3. if restOfStr is made of the other words in the list then returns True
   4. if not returns False
Arguments:
    word (str):   input word
Returns:
    returns True if the words is made of other words if not False
"""
def IsWordMadeOfOtherWords(word):
    isWordMadeOfOtherWords = False

    wordLength = len(word)
    for subStrEnd in range(1, wordLength+1):
        subStr = word[:subStrEnd]
        restOfStr = word[subStrEnd:]
        if gWordsDict.has_key(subStr):
            if restOfStr:
                isWordMadeOfOtherWords = IsWordMadeOfOtherWords(restOfStr)
                if isWordMadeOfOtherWords:
                    return isWordMadeOfOtherWords
                else:
                    continue
            else:
                isWordMadeOfOtherWords = True
                return isWordMadeOfOtherWords
        else:
            isWordMadeOfOtherWords = False

    return isWordMadeOfOtherWords

inputFilePath = None
numberOfWordsThatAreMadeOfOtherWords = 1
if len(sys.argv) >= 2:
    inputFilePath = sys.argv[1]
    if not os.path.exists(inputFilePath):
        ShowUsage()
    if len(sys.argv) == 3:
        numberOfWordsThatAreMadeOfOtherWords = int(sys.argv[2])
        if numberOfWordsThatAreMadeOfOtherWords == 0:
            numberOfWordsThatAreMadeOfOtherWords = 1
else:
    ShowUsage()

print "Loading words from the inputFile into a dictionary..."
with open(inputFilePath, "r") as inputFileHandle:

    #parse out the terms and add it to a dict(hash)
    word = inputFileHandle.readline().strip()
    while word:
        gWordsDict[word] = True
        word = inputFileHandle.readline().strip()

    print "Creating a sorted list of words from the dictionary..."
    # sort the words by length in descending order
    sortedWords = sorted(gWordsDict.keys(), key=len, reverse=True)

    WordsMadeOfOtherWords = []
    print "Process words in the sorted list"
    for word in sortedWords:
        del gWordsDict[word]
        if IsWordMadeOfOtherWords(word):
            WordsMadeOfOtherWords.append(word)
            if numberOfWordsThatAreMadeOfOtherWords > 0 and numberOfWordsThatAreMadeOfOtherWords == len(WordsMadeOfOtherWords):
                break

    print ""
    print ">>>>>>>>>>>>>>>>>>>>>>"
    if numberOfWordsThatAreMadeOfOtherWords == -1:
        print "{} longest words that are made of other words in the list are: {}.".format(5, WordsMadeOfOtherWords[:5])
        print "--------------------"
        print "Total number of words that are made of other words in the list: {} out of all the elements in the input list {}.".format(len(WordsMadeOfOtherWords), len(sortedWords))
    else:
        print "{} longest words that are made of other words in the list are: {}.".format(numberOfWordsThatAreMadeOfOtherWords, WordsMadeOfOtherWords)
    print "<<<<<<<<<<<<<<<<<<<<<<"
