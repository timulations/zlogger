#include "zlogger.hpp"

int main(int argc, char* argv[]) {
    LOG_TRACE << "testing, testing!"; /* should not appear by default */
    LOG_INFO << "Hello there!";
    LOG_INFO << "My name is " << " Timothy," << " and my age is: " << 25;
    LOG_ERROR << "Oops, I made a mistake!";
    LOG_WARN << "My hair is not doing great today with a spikiness index of " << 0.78283 << " , goodness!";

    zlogger::set_level(zlogger::level::error);
    LOG_WARN << "My hair still isn't that great!"; /* should not appear */
    LOG_ERROR << "Mistake number 2!";
    LOG_DEBUG << "Hi"; /* should not appear */

    zlogger::set_level(zlogger::level::trace); /* everything should appear now */
    LOG_TRACE << "Test test #2!"; 
    LOG_DEBUG << "Debuggin'";
    LOG_INFO << "INfo-in'";
    LOG_WARN << "Warn-in'";
    LOG_ERROR << "Kaboom";

    return EXIT_SUCCESS;
}