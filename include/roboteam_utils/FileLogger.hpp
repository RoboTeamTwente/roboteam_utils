#pragma once

#include <string>
#include <memory>

namespace rtt {

/* A class that makes logging to a file easier and safer.
 * It handles opening and closing, writing and flushing.
 * Will append to previously written text in the file. */
class FileLogger {
public:
    // Will create and open the file you specify. Eg. "log/LOG.txt"
    explicit FileLogger(const std::string& filePath);
    // Will close the file
    ~FileLogger();

    // Writes the line and appends with a newline character
    void writeNewLine(const std::string& line);
    // Writes the given text to the file
    void write(const std::string& text);
    // Synchronizes the file with the internal buffer. Read: saves
    bool flush();

private:
    std::unique_ptr<std::ofstream> stream;
};

class FailedToOpenFileException : public std::exception {
public:
    FailedToOpenFileException(const std::string& message);
    virtual const char *what() const noexcept;
private:
    const std::string message;
};

} // namespace rtt::robothub