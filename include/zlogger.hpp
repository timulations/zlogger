#ifndef ZLOGGER_HPP
#define ZLOGGER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <mutex>

#ifdef _WIN32 /* Windows */
    #include <windows.h>
    #define GET_PROCESS_ID() GetCurrentProcessId()
#else /* MacOS and other POSIX systems (Linux, etc) */
    #include <unistd.h>
    #define GET_PROCESS_ID() getpid()
#endif

class zlogger {
public:
    enum level {
        trace = 0,
        debug,
        info,
        warn,
        error
    };

    constexpr static const char* level_to_string[] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR"
    };

    zlogger(level curr_level) noexcept :curr_level_{curr_level} {}

    ~zlogger() {
        /* flush to stream */
        std::scoped_lock lock{mtx_};
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm *ptm = std::localtime(&t);

        *os_ << "[" << level_to_string[curr_level_] << "]";
        *os_ << "[" << std::put_time(ptm, "%c") << "]";
        *os_ << "[PID: " << GET_PROCESS_ID() << "] ";
        *os_ << ss_.rdbuf();
        *os_ << std::endl;
    }

    template <typename T>
    zlogger& operator<<(T&& val) noexcept {
        ss_ << std::forward<T>(val);
        return *this;
    }

    static void set_level(level log_level) {
        std::scoped_lock lock{mtx_};
        log_level_ = log_level;
    }

    const static level get_level() noexcept {
        return log_level_;
    }

    static void set_output_stream(std::ostream& os) {
        std::scoped_lock lock{mtx_};
        os_ = std::addressof(os);
    }

    static std::ostream& get_output_stream() {
        return *os_;
    }

private:
    static inline std::mutex mtx_;

#ifdef RELEASE
    static inline level log_level_ = level::info;
#else
    static inline level log_level_ = level::debug;
#endif

    static inline std::ostream* os_ = std::addressof(std::cout);;

    level curr_level_;
    std::stringstream ss_;
};

#define LOG_TRACE if (zlogger::get_level() <= zlogger::level::trace) zlogger(zlogger::level::trace)
#define LOG_DEBUG if (zlogger::get_level() <= zlogger::level::debug)  zlogger(zlogger::level::debug)
#define LOG_INFO  if (zlogger::get_level() <= zlogger::level::info)  zlogger(zlogger::level::info)
#define LOG_WARN  if (zlogger::get_level() <= zlogger::level::warn)  zlogger(zlogger::level::warn)
#define LOG_ERROR if (zlogger::get_level() <= zlogger::level::error)  zlogger(zlogger::level::error)

#endif