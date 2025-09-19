// libui_stub.cpp
// Minimal stub for android::GraphicBufferMapper and its Singleton
// Provides just enough to satisfy linker symbols when libui is absent.

#include <cutils/native_handle.h>

namespace android {

// Dummy Mutex type so Singleton has something to instantiate
struct Mutex {};

// Forward declaration of template
template <typename T> struct Singleton;

// Stubbed GraphicBufferMapper
class GraphicBufferMapper {
public:
    GraphicBufferMapper(); // ctor
    int importBufferNoValidate(const native_handle* handle,
                               const native_handle** outHandle);
    int freeBuffer(const native_handle* handle);
};

// Definitions
GraphicBufferMapper::GraphicBufferMapper() {}

int GraphicBufferMapper::importBufferNoValidate(const native_handle* /*handle*/,
                                                const native_handle** outHandle) {
    if (outHandle) {
        *outHandle = nullptr;
    }
    return 0; // pretend success
}

int GraphicBufferMapper::freeBuffer(const native_handle* /*handle*/) {
    return 0; // pretend success
}

// Singleton template with static members
template <typename T>
struct Singleton {
    static Mutex sLock;
    static T* sInstance;
};

template <typename T> Mutex Singleton<T>::sLock;
template <typename T> T*   Singleton<T>::sInstance = nullptr;

// Explicit instantiation for GraphicBufferMapper
template struct Singleton<GraphicBufferMapper>;

} // namespace android
