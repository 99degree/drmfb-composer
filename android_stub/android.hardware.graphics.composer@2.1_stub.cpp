// Minimal drop-in stub for android.hardware.graphics.composer@2.1.so
// Matches VNDK v30 2.1 headers per your symbol dump.
// This is non-functional; it only satisfies linkage and loader calls.

#include <android/hardware/graphics/composer/2.1/IComposer.h>
#include <android/hardware/graphics/composer/2.1/IComposerClient.h>
#include <android/hardware/graphics/composer/2.1/IComposerCallback.h>

#include <android/hardware/graphics/common/1.0/types.h>
#include <hidl/MQDescriptor.h>

#include <hidl/Status.h>
#include <hidl/HidlSupport.h>

using ::android::sp;
using ::android::hardware::Return;
using ::android::hardware::Void;

namespace ahw = ::android::hardware;
namespace gfx = ::android::hardware::graphics;
namespace common10 = ::android::hardware::graphics::common::V1_0;
namespace composer21 = ::android::hardware::graphics::composer::V2_1;

using IComposer       = composer21::IComposer;
using IComposerClient = composer21::IComposerClient;
using IComposerCallback = composer21::IComposerCallback;
using Error = composer21::Error;

// Define the public descriptors (appear as dynamic data symbols in your dump)
namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

// Add this missing method here
int IComposer::registerAsService(const std::string& /*serviceName*/) {
    // Return 0 to indicate success (android::OK)
    return 0;
}

const char* IComposer::descriptor =
        "android.hardware.graphics.composer@2.1::IComposer";
const char* IComposerClient::descriptor =
        "android.hardware.graphics.composer@2.1::IComposerClient";
const char* IComposerCallback::descriptor =
        "android.hardware.graphics.composer@2.1::IComposerCallback";

// No-op client implementing all pure virtuals present in your v30 headers
struct ComposerClientNoop : public IComposerClient {
    // Layer management
    Return<void> createLayer(uint64_t /*display*/, uint32_t /*bufferSlotCount*/,
                             IComposerClient::createLayer_cb cb) override {
        cb(Error::NONE, static_cast<uint64_t>(0));
        return Void();
    }
    Return<Error> destroyLayer(uint64_t /*display*/, uint64_t /*layer*/) override {
        return Error::NONE;
    }

    // Display config/state
    Return<void> getDisplayConfigs(uint64_t /*display*/,
                                   IComposerClient::getDisplayConfigs_cb cb) override {
        cb(Error::NONE, {});
        return Void();
    }
    Return<void> getDisplayName(uint64_t /*display*/,
                                IComposerClient::getDisplayName_cb cb) override {
        cb(Error::NONE, ahw::hidl_string("Composer21Stub"));
        return Void();
    }
    Return<void> getDisplayType(uint64_t /*display*/,
                                IComposerClient::getDisplayType_cb cb) override {
        cb(Error::NONE, IComposerClient::DisplayType::INVALID);
        return Void();
    }
    Return<void> getDozeSupport(uint64_t /*display*/,
                                IComposerClient::getDozeSupport_cb cb) override {
        cb(Error::NONE, false);
        return Void();
    }
    Return<void> getHdrCapabilities(uint64_t /*display*/,
                                    IComposerClient::getHdrCapabilities_cb cb) override {
        cb(Error::NONE, ahw::hidl_vec<common10::Hdr>{}, 0.0f, 0.0f, 0.0f);
        return Void();
    }
    Return<void> getDisplayAttribute(uint64_t /*display*/, uint32_t /*config*/,
                                     IComposerClient::Attribute /*attribute*/,
                                     IComposerClient::getDisplayAttribute_cb cb) override {
        cb(Error::NONE, 0);
        return Void();
    }
    Return<void> getActiveConfig(uint64_t /*display*/,
                                 IComposerClient::getActiveConfig_cb cb) override {
        cb(Error::NONE, 0U);
        return Void();
    }
    Return<Error> setActiveConfig(uint64_t /*display*/, uint32_t /*config*/) override {
        return Error::NONE;
    }

    // Power/vsync/color
    Return<Error> setPowerMode(uint64_t /*display*/, IComposerClient::PowerMode /*mode*/) override {
        return Error::NONE;
    }
    Return<Error> setVsyncEnabled(uint64_t /*display*/, IComposerClient::Vsync /*enabled*/) override {
        return Error::NONE;
    }
    Return<Error> setColorMode(uint64_t /*display*/, common10::ColorMode /*mode*/) override {
        return Error::NONE;
    }
    Return<void> getColorModes(uint64_t /*display*/,
                               IComposerClient::getColorModes_cb cb) override {
        cb(Error::NONE, ahw::hidl_vec<common10::ColorMode>{});
        return Void();
    }

    // Virtual displays
    Return<void> createVirtualDisplay(uint32_t /*width*/, uint32_t /*height*/,
                                      common10::PixelFormat /*formatHint*/,
                                      uint32_t /*outputBufferSlotCount*/,
                                      IComposerClient::createVirtualDisplay_cb cb) override {
        cb(Error::NONE, static_cast<uint64_t>(0), common10::PixelFormat::RGBA_8888);
        return Void();
    }
    Return<Error> destroyVirtualDisplay(uint64_t /*display*/) override {
        return Error::NONE;
    }
    Return<uint32_t> getMaxVirtualDisplayCount() override {
        return static_cast<uint32_t>(0);
    }

    // Client target support/slots
    Return<Error> getClientTargetSupport(uint64_t /*display*/,
                                         uint32_t /*width*/, uint32_t /*height*/,
                                         common10::PixelFormat /*format*/,
                                         common10::Dataspace /*dataspace*/) override {
        // In 2.1 this method returns Error: NONE if supported, UNSUPPORTED otherwise.
        return Error::NONE;
    }
    Return<Error> setClientTargetSlotCount(uint64_t /*display*/, uint32_t /*count*/) override {
        return Error::NONE;
    }

    // Command queues (FMQ)
    Return<void> getOutputCommandQueue(
        IComposerClient::getOutputCommandQueue_cb cb) override {
        // Return an empty descriptor
        ahw::MQDescriptor<uint32_t, ahw::kSynchronizedReadWrite> out;
        cb(Error::NONE, out);
        return Void();
    }
    Return<Error> setInputCommandQueue(
        const ahw::MQDescriptor<uint32_t, ahw::kSynchronizedReadWrite>& /*in*/) override {
        return Error::NONE;
    }

    // Batched commands
    Return<void> executeCommands(
        uint32_t /*inLength*/,
        const ahw::hidl_vec<ahw::hidl_handle>& /*inHandles*/,
        IComposerClient::executeCommands_cb cb) override {
        // indicate "handled = false", "outLength = 0", empty handles
        cb(Error::NONE, false, 0U, ahw::hidl_vec<ahw::hidl_handle>{});
        return Void();
    }

    // Callbacks
    // NOTE: In your headers, this returns Return<void>
    Return<void> registerCallback(const sp<IComposerCallback>& /*callback*/) override {
        return Void();
    }
};

// Minimal IComposer that hands out the no-op client
struct ComposerStub : public IComposer {
    Return<void> getCapabilities(IComposer::getCapabilities_cb cb) override {
        cb(ahw::hidl_vec<IComposer::Capability>{});
        return Void();
    }
    Return<void> dumpDebugInfo(IComposer::dumpDebugInfo_cb cb) override {
        cb(ahw::hidl_string("composer@2.1 stub"));
        return Void();
    }
    Return<void> createClient(IComposer::createClient_cb cb) override {
        sp<IComposerClient> client = new ComposerClientNoop();
        cb(Error::NONE, client);
        return Void();
    }
};

} // namespace V2_1
} // namespace composer
} // namespace graphics
} // namespace hardware
} // namespace android

// Factory symbol the HIDL loader looks up via dlsym()
extern "C" composer21::IComposer* HIDL_FETCH_IComposer(const char* /*name*/) {
    static composer21::ComposerStub kStub;
    return &kStub;
}

// Extra symbol you can reference from your binary to prevent the linker dropping the .so
extern "C" void composer21_stub_keepalive() {}
