namespace android {

namespace base {
    enum LogSeverity { VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL };
    bool ShouldLog(LogSeverity, const char*) { return false; }
}

} // namespace android

// binder_stub.cpp (additions)

namespace android {

class ProcessState {
public:
    // Stub for initWithDriver
    static void initWithDriver(const char* /*driver*/) {
        // no-op
    }

    // Stub for self()
    static ProcessState* self() {
        static ProcessState instance;
        return &instance;
    }

    // Stub for setThreadPoolMaxThreadCount
    void setThreadPoolMaxThreadCount(unsigned long /*count*/) {
        // no-op
    }

    // Stub for startThreadPool
    void startThreadPool() {
        // no-op
    }
};

} // namespace android
