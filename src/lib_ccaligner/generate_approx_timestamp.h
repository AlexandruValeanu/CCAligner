/*
 * Author   : Saurabh Shrivastava
 * Email    : saurabh.shrivastava54@gmail.com
 * Link     : https://github.com/saurabhshri
*/

#ifndef GENERATE_APPROX_TIMESTAMP_H
#define GENERATE_APPROX_TIMESTAMP_H

#include "srtparser.h"
#include "commons.h"
#include "params.h"

class currentSub    //processing one subtitle at a time
{
    int _sentenceLength, _wordCount;    //length of the dialogue, number of words in that dialogue
    long _dialogueDuration;             //duration of the dialogue in ms
    static int _wordNumber;             //used to maintain the information about which word is being processed
    SubtitleItem *_sub;                 //the subtitle itself (SubtitleItem is defined in srtparser.h)


public:
    int getDuration (long startTime, long endTime); //return the duration in ms between ending and starting timestamp
    double getWordWeight (std::string word);        //returns the approximate weight of word
    currentSub(SubtitleItem *sub);
    void run();                                     //run the alignment
    void alignNonRecognised(recognisedBlock currBlock);                      //run the approx alignment on unrecognised words
    void printAsKaraoke(std::string fileName, outputOptions printOption);
    void printToSRT(std::string fileName, outputOptions printOption);          //prints the aligned result in SRT format
    void printToJSON(std::string fileName);         //prints the aligned result in JSON format
    void printToXML(std::string fileName);          //prints the aligned information in XML format
    void printToConsole(std::string fileName);      //prints the output to console/stdout
    void assignTime(long int &wordDuration, const std::string &word );  //assign the approximate duration the word is estimated to be spoken
    ~currentSub();
};

class ApproxAligner
{
private:
    std::string _fileName,_outputFileName;          //input and output filenames
    outputFormats _outputFormat;                    //output format (xml/json/srt/stdout)
public:
    ApproxAligner(std::string fileName, outputFormats outputFormat = srt);  //default output is in SRT format
    std::vector<SubtitleItem *, std::allocator<SubtitleItem *>> align();   //begin alignment
    ~ApproxAligner();
};

#endif //GENERATE_APPROX_TIMESTAMP_H
