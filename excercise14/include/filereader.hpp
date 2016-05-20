/**
 *
 *  File reader
 *
 *  https://github.com/kdzlvaids/algorithm_and_practice-pknu-2016
 *
 */

#ifndef ALGORITHM_FILEREADER_HPP_
#define ALGORITHM_FILEREADER_HPP_ 1

/** Includes */
#include <string>
#include <fstream>      /** File stream */
#include <sstream>      /** String stream */
#include <functional>
#include <regex>        /** Regular expressions */
#include <array>        /** Containers */
#include <vector>       /** Containers */

namespace algorithm
{

/** File reader */
template<
    std::streamsize StreamSize  = 1000,                             /**< Stream unit size (word, line, etc.)*/
    class   StringType          = std::string,                      /**< Char array type */
    class   StringArrayType     = std::vector<StringType>,          /**< Array of Char array type */
    class   DelimsType          = StringType                        /**< List of delimiters type (Char array type, should be iterable) */
>
class FileReader
{
public:
    typedef size_t              SizeType;
    typedef char                CharType;   /**< Char type */

    typedef std::istream        InputStreamType;        /**< Common input stream type */
    typedef std::ifstream       FileInputStreamType;    /**< File input stream type */
    typedef std::stringstream   StringInputStreamType;  /**< String input stream type */
    typedef std::regex          RegexType;              /**< Regular expression pattern type */

private:
    FileInputStreamType         stream_;    /**< File stream */

    /** Test whether the character matches with one of delims

        \note   If the number of delimiters is N, then the time complexity is O(N).

        \return     Return true if ch is a delimiter; otherwise return false
        \param[in]  ch      Character to compare
        \param[in]  delims  List of delimiters
    */
    inline
    bool
    IsDelimiter(const CharType & ch, const DelimsType & delims)
    {
        for(const CharType & delim : delims)
        {
            if(ch == delim)
                return true;
        }

        return false;
    }

public:
    /** Constructor */
    FileReader(void)
    { }

    FileReader(const StringType & filename)
    { Open(filename); }

    /** Destructor */
    ~FileReader(void)
    { Close(); }

    /** Open a file and associates it with the stream
        
        \param[in]  filename    Path of the file
    */
    void
    Open(const StringType & filename)
    { stream_.open(filename); } 

    /** Close the associated file */
    void
    Close(void)
    { stream_.close(); }

    /** Close and re-open the associated file

        \param[in]  filename    Path of the file
    */
    void
    Reopen(const StringType & filename)
    {
        Close();
        Open(filename);
    }

    /** Test whether the stream has an associated file

        \return     Return true if the stream has an associated file;
                    otherwise return false
    */
    inline
    bool
    IsOpen(void)
    { return stream_.is_open(); }

    /** Test whether the stream reached to End-of-file
    
        \return     Return true if the stream reached to EOF; otherwise return false
    */
    inline
    bool
    IsEOF(void)
    { return stream_.eof(); }

    /** Read a file until specific delimiter

        \note   If the length of each line in input stream is M
                and the number of delimiters is N,
                then the time complexity is O(M*N).

        \return     Length of output string
        \param[out] out_string  String to store
        \param[in]  stream      File stream
        \param[in]  delims      List of delimiters
    */
    SizeType
    Read(StringType & out_string, InputStreamType & stream, const DelimsType & delims)
    {
        out_string.clear();

        CharType ch;
        while(stream.eof() != true && IsDelimiter(ch = stream.get(), delims) != true)
            out_string += ch;

        return out_string.length();
    }

    /** Read a line

        \return     Length of output string
        \param[out] out_string  String to store a line
    */
    SizeType
    ReadLine(StringType & out_string)
    { return Read(out_string, stream_, "\n"); }

    /** Tokenising the stream by delimiter

        \return     Number of tokens
        \param[out] out_tokens  Array to store tokens;
                    Requires member functions: clear(), push_back(), size() 
        \param[in]  stream      File stream
        \param[in]  delims      List of delimiters
    */
    SizeType
    DivideByDelimiter(StringArrayType & out_tokens, InputStreamType & stream, const DelimsType & delims)
    {
        out_tokens.clear();

        StringType string;
        while(Read(string, stream, delims) > 0)
            out_tokens.push_back(string);

        return out_tokens.size();
    }

    /** Tokenising the string by delimiter

        \return     Number of tokens
        \param[out] out_tokens  Array to store tokens;
                    Requires member functions: clear(), push_back(), size() 
        \param[in]  string      String
        \param[in]  delims      List of delimiters
    */
    SizeType
    DivideByDelimiter(StringArrayType & out_tokens, const StringType & string, const DelimsType & delims)
    {
        StringInputStreamType stream(string);
        return DivideByDelimiter(out_tokens, stream, delims);
    }

    /** Parser

        Loop the logic (line reading) until term_condition comes true.
        Callback is called with each line.

        There is two functions which works as callback function:
            *   void callback(StringType &)
            *   bool term_condition(InputStreamType &)

        First, function named `callback' is called in every line.
        As argument, string of each line is passed.

        Second, function named `term_condition' is called in every line, too.
        As argument, input stream is passed, which is potentially unsafe.

        `term_condition' is works as contitional expression in `while' loop,
        which continues the line reading, should return true to escape out the loop.
        `term_condition' is OPTIONAL, and the default value is:
        `
            bool
            term_condition(InputStreamType & stream)
            { return IsEOF(); }
        '.

        \note   Experimental

        \param[in]  callback        Callback function
        \param[in]  term_condition  Function which have a termination condition;
                                    if the loop reached to terminate condition,
                                    term_condition should return true to escape out
                                    (Optional, default value is: `return IsEOF;')
    */
    void
    Parse(std::function<void(StringType &)> & callback,
          std::function<bool(InputStreamType &)> & term_condition =
          [] (InputStreamType & stream)
          -> bool
          { return IsEOF(); }
    )
    {
        while(term_condition(stream_) != true)
        {
            StringType string;
            ReadLine(string);
            callback(string);
        }
    }

#if 0
    /** Regular expression match operation

        \note   Experimental

        \return     Return true if match exists; otherwise return false
        http://en.cppreference.com/w/cpp/regex/regex_match
    */
    bool
    RegexMatch(StringType & out_result, const StringType & string, const StringType & regex_pattern)
    {
        RegexType pattern(regex_pattern);
        bool r = regex_match(string, pattern);

        return (r.ready() == true && r.empty() == true && r.size() == 0) != true;
    }
#endif
};

} /** ns: algorithm */

#endif /** ! ALGORITHM_FILEREADER_HPP_ */
