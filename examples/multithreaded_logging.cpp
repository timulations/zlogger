#include <thread>
#include "zlogger.hpp"

void logging1() {
    LOG_TRACE << "testing, testing!";
    LOG_INFO << "Hello there!";
    LOG_INFO << "My name is " << " Timothy," << " and my age is: " << 25;
    LOG_ERROR << "Oops, I made a mistake!";
    LOG_WARN << "My hair is not doing great today with a spikiness index of " << 0.78283 << " , goodness!";
}

void logging2() {
    zlogger::set_level(zlogger::level::error);
    LOG_WARN << "My hair still isn't that great!";
    LOG_ERROR << "Mistake number 2!";
    LOG_DEBUG << "Hi"; 
}

void logging3() {
    zlogger::set_level(zlogger::level::trace);
    LOG_TRACE << "Test test #2!"; 
    LOG_DEBUG << "Debuggin'";
    LOG_INFO << "INfo-in'";
    LOG_WARN << "Warn-in'";
    LOG_ERROR << "Kaboom";
}

int main(int argc, char* argv[]) {
    std::thread t1{logging1}, t2{logging2}, t3{logging3};

    /* synchronize the threads, pauses until all 3 threads finish */
    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}