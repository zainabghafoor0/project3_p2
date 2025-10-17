#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "Scanner.hpp"
#include "BST.hpp"
#include "PriorityQueue.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    // 1) Parse and validate arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // Build paths for output files
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string freqFileName = dirName + "/" + inputFileBaseName + ".freq";

    // Verify input file, directory exist and output files are writable
    if (error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR)
        exitOnError(status, inputFileName);

    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR)
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    if (error_type status; (status = canOpenForWriting(freqFileName)) != NO_ERROR)
        exitOnError(status, freqFileName);

    // 2) Scanner: tokenize input file
    std::vector<std::string> words;
    auto fileToWords = Scanner(std::filesystem::path(inputFileName));
    
    if (error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
        exitOnError(status, inputFileName);

    // Write tokens to .tokens file
    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    // 3) BST: build tree from tokens and compute frequencies
    BST bst;
    bst.buildFromTokens(words);
    
    // Get frequency data
    auto frequencies = bst.getFrequencies();
    
    // 4) Print BST measures to stdout
    size_t totalTokens = words.size();
    size_t uniqueWords = bst.getUniqueWords();
    int height = bst.getHeight();
    size_t minFreq, maxFreq;
    bst.getMinMaxFrequency(minFreq, maxFreq);
    
    std::cout << "BST height: " << height << '\n';
    std::cout << "BST unique words: " << uniqueWords << '\n';
    std::cout << "Total tokens: " << totalTokens << '\n';
    std::cout << "Min frequency: " << minFreq << '\n';
    std::cout << "Max frequency: " << maxFreq << '\n';

    // 5) PriorityQueue: sort by count (desc) then word (asc), write to .freq
    PriorityQueue pq;
    pq.buildQueue(frequencies);
    
    if (error_type status; (status = pq.writeToFile(freqFileName)) != NO_ERROR)
        exitOnError(status, freqFileName);

    // 6) Success
    return 0;
}