#include <fstream>
#include <sstream>
#include <functional>

class parser
{
private:
    const int max_length; /* Maximum length of string to do something using `stream.getline' */
    std::ifstream stream; /* File stream */

    std::string read_one_line() { return read(stream, '\n'); }
    std::string read(std::istream &stream, const char &delimiter)
    {
        char data[max_length];
        stream.getline(&data[0], max_length, delimiter); /* Get line until the delimiter appears */

        /* Do conversion char[] to string */
        std::string output;
        for(char d : data)
        {
            output.push_back(d);
            if(d == '\0') break;
        }

        return output;
    }

public:
    parser(const int max_length = 100000) : max_length(max_length) {}
    parser(const std::string &path_of_file, const int max_length = 100000) : max_length(max_length) { open(path_of_file); }

    ~parser(void) { close(); }

    bool open(const std::string &path_of_file)
    {
        stream.open(path_of_file);
        return stream.is_open();
    }

    void close(void) { stream.close(); }

    void parse(const std::function<void(std::string)> &callback)
    {
        while(stream.eof() != true) callback(read_one_line());
    }

    int divide_by_delimiter(std::string dest[], const std::string &src, const int max_count_of_array, const char &delimiter)
    {
        /* Do conversion string to stream */
        std::stringstream stream(src);

        /* Divide stream, and store them to dest[] */
        int count;
        for(count = 0; count < max_count_of_array && stream.eof() != true; ++count)
            dest[count] = read(stream, delimiter);

        return count; /* Return a count of array */
    }
};
