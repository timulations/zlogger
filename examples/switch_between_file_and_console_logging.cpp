#include <fstream>
#include <string>

#include "zlogger.hpp"

#define LOGFILE_PATH "test2.log"

int main(int argc, char* argv[]) {

    std::ofstream out_file_handle(LOGFILE_PATH);
    if (out_file_handle.is_open()) {
        zlogger::set_output_stream(out_file_handle);
    } else {
        throw std::runtime_error(std::string("Could not open ") + LOGFILE_PATH + " for writing");
    }

    LOG_TRACE << "testing, testing!"; /* should not appear by default */
    LOG_INFO << "Hello there!";
    LOG_INFO << "My name is " << " Timothy," << " and my age is: " << 25;
    LOG_ERROR << "Oops, I made a mistake!";
    LOG_WARN << "My hair is not doing great today with a spikiness index of " << 0.78283 << " , goodness!";

    zlogger::set_level(zlogger::level::error);
    LOG_WARN << "My hair still isn't that great!"; /* should not appear */
    LOG_ERROR << "Mistake number 2!";
    LOG_DEBUG << "Hi"; /* should not appear */

    /* change back to console */
    if (auto& my_out_file_handle = dynamic_cast<std::ofstream&>(zlogger::get_output_stream())) {
        my_out_file_handle.close();
    }

    zlogger::set_output_stream(std::cout);
    zlogger::set_level(zlogger::level::trace); 
    LOG_TRACE << "Test test #2!"; 
    LOG_DEBUG << "Debuggin'";
    LOG_INFO << "INfo-in'";
    LOG_WARN << "Warn-in'";
    LOG_ERROR << "Kaboom";

    return EXIT_SUCCESS;
}