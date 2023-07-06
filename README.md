# zlogger
Header-only, thread-safe, lightweight, stream-overloaded logger

## Getting Started
Simply grab the header file `zlogger.hpp` from the `include` folder and include into your project 🚀🌟

## Examples
To build the examples:
```
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Logging to console
zlogger logs to console by default. 
```cpp
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
```

The output may look something like:
```
[INFO][07/06/22 18:47:55][PID: 43136] Hello there!
[INFO][07/06/22 18:47:55][PID: 43136] My name is  Timothy, and my age is: 25
[ERROR][07/06/22 18:47:55][PID: 43136] Oops, I made a mistake!
[WARN][07/06/22 18:47:55][PID: 43136] My hair is not doing great today with a spikiness index of 0.78283 , goodness!
[ERROR][07/06/22 18:47:55][PID: 43136] Mistake number 2!
[TRACE][07/06/22 18:47:55][PID: 43136] Test test #2!
[DEBUG][07/06/22 18:47:55][PID: 43136] Debuggin'
[INFO][07/06/22 18:47:55][PID: 43136] INfo-in'
[WARN][07/06/22 18:47:55][PID: 43136] Warn-in'
[ERROR][07/06/22 18:47:55][PID: 43136] Kaboom
```

To explicitly log to console (or switch back to logging to console):
```cpp
zlogger::set_output_stream(std::cout);
```

### Logging to file
Simply change output stream and then log away 🚀
```cpp
std::ofstream out_file_handle(LOGFILE_PATH);
if (out_file_handle.is_open()) {
    zlogger::set_output_stream(out_file_handle);
} else {
    throw std::runtime_error(std::string("Could not open ") + LOGFILE_PATH + " for writing");
}

LOG_TRACE << "testing, testing!"; /* should not appear by default */
LOG_INFO << "Hello there!";
```

### Thread-safety
While zlogger cannot prevent race conditions between two threads trying to write to log at the same time, it will make sure that the messages are not interleaved in the output
```cpp
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
```

Possible output:
```
[INFO][07/06/22 18:52:43][PID: 76904] Hello there!
[INFO][07/06/22 18:52:43][PID: 76904] My name is  Timothy, and my age is: 25
[ERROR][07/06/22 18:52:43][PID: 76904] Oops, I made a mistake!
[ERROR][07/06/22 18:52:43][PID: 76904] Mistake number 2!
[TRACE][07/06/22 18:52:43][PID: 76904] Test test #2!
[DEBUG][07/06/22 18:52:43][PID: 76904] Debuggin'
[INFO][07/06/22 18:52:43][PID: 76904] INfo-in'
[WARN][07/06/22 18:52:43][PID: 76904] Warn-in'
[ERROR][07/06/22 18:52:43][PID: 76904] Kaboom
[DEBUG][07/06/22 18:52:43][PID: 76904] Hi
```
