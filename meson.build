project('drmfb-composer', 'cpp', version: '1.0')

cc = meson.get_compiler('c')

cpu_map = {
  'arm':     'arch-arm-armv7-a-neon',
  'aarch64': 'arch-arm64-armv8-a',
  'x86':     'arch-x86',
  'x86_64':  'arch-x86_64'
}

compiler_map = {
  'arm':     'arm-linux-androideabi',
  'aarch64': 'aarch64-linux-android',
  'x86':     'i686-linux-android',
  'x86_64':  'x86_64-linux-android'
}

cpu_family = host_machine.cpu_family()

# Cosmetic rename for display (optional)
cpu_name = (cpu_family == 'aarch64') ? 'arm64' : cpu_family

inst_name = cpu_map.get(cpu_family, '')
compiler_name = compiler_map.get(cpu_family, '')

message('CPU name: ' + cpu_name)
message('Instruction dir: ' + inst_name)
message('Compiler family: ' + compiler_name)

ndk_root = get_option('ndk_root')
if ndk_root == ''
  ndk_root = meson.get_external_property('ndk_root', '')
endif

if ndk_root == ''
  error('You must set ndk_root either in the cross file or with -Dndk_root=...')
endif

# For Same Process like mapper

# Define all available drivers in one place
_all_drivers = [
  'amdgpu', 'i915', 'xe', 'meson', 'msm', 'vc4',
  'mediatek', 'rockchip', 'virtgpu', 'radeon', 'arcvm', 'generic', 'intel'
]

# Read the option from meson_options.txt (or fallback to default)
drivers = get_option('drivers')
if drivers.length() == 0
  drivers = _all_drivers
endif

# === Include directories ===
inc = include_directories('.')

# Extended include paths for Android VNDK v34
# Each path below has a comment describing what headers it provides
inc_extra_v34 = include_directories(
  # android-base/unique_fd.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/libbase/include/'),
  # system/core/libsystem/
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libsystem/'),
  # hardware/gralloc.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/hardware/libhardware/include/'),
  # system/graphics-base-v1.0.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libsystem/include/'),
  # sync/sync.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libsync/include'),
  # libvndksupport
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libvndksupport/include'),
  # libsysutils
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libsysutils/'),
  # graphics.common-V4 AIDL headers
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  # libcutils
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libcutils/include'),
  # log/log.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/logging/liblog/include_vndk/'),
  # BufferDescriptorInfo.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/aidl/android.hardware.graphics.allocator-V2-ndk-source/gen/include/'),
  # graphics.common@1.2
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.2/android.hardware.graphics.common@1.2_genc++_headers/gen/'),
  # graphics.common@1.1
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.1/android.hardware.graphics.common@1.1_genc++_headers/gen/'),
  # graphics.common@1.0
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.0/android.hardware.graphics.common@1.0_genc++_headers/gen/'),
  # Hidlsupport.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/libhidl/base/include/'),
  # utils/Error.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/core/libutils/include'),
  # fmq/MQDescriptorBase.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/libfmq/base/'),
  # IMapper 4.0
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/mapper/4.0/android.hardware.graphics.mapper@4.0_genc++_headers/gen/'),
  # IBase 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/system/libhidl/transport/base/1.0/android.hidl.base@1.0_genc++_headers/gen/'),
  # IServiceNotification 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/system/libhidl/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/'),
  # gralloctypes/Gralloc4.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/frameworks/native/libs/gralloc/types/include/'),
  # system/window.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/frameworks/native/libs/nativewindow/include/'),
  # nativebase.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/frameworks/native/libs/nativebase/include/'),
  #
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/common/aidl/android.hardware.common-V2-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/frameworks/native/libs/binder/ndk/include_platform/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/4.0/android.hardware.graphics.allocator@4.0_genc++_headers/gen/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/libhidl/transport/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/frameworks/native/libs/binder/include/'),
  # framework and libhwbinder both have IBinder.h
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/system/libhwbinder/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/composer/aidl/android.hardware.graphics.composer3-V1-ndk-source/gen/include/aidl/'),

  # local shim includes
#  join_paths('.', 'include/stable-c-v34/include'),
#  join_paths('.', 'include/stable-c-v34/implutils/include/'),
#  join_paths('.', 'include/'),
)

drmfb_sources = files(
  'DrmComposer.cpp',
  'DrmDevice.cpp',
  'DrmDisplay.cpp',
  'DrmFramebuffer.cpp',
  'DrmFramebufferLibDrm.cpp',
  'DrmHotplugThread.cpp',
  'DrmVsyncThread.cpp',
  'GraphicsThread.cpp',
  'service.cpp'
)

libdrm_dep = dependency(
  'libdrm',
  version: '>=2.4.100',
  required: true,
  fallback: ['libdrm', 'libdrm_dep'],
  static: true
)

# Optional source if USE_MINIGBM is enabled
use_minigbm = false
#use_minigbm = get_option('use_minigbm')
if use_minigbm 
  drmfb_sources += files('DrmFramebufferMinigbm.cpp')
endif

# Dependencies
deps = [
  libdrm_dep,
  dependency('libsync', required: false),
  dependency('liblog', required: false),
  dependency('libutils', required: false),
  dependency('libbase', required: false),
  dependency('libbinder', required: false),
  dependency('libcutils', required: false),
  dependency('libfmq', required: false),
  dependency('libhidlbase', required: false)
]

deps_found = []

foreach dep : deps
  if dep.found()
    deps_found += dep
  endif
endforeach

executable(
  'drmfb-composer',
  drmfb_sources,
  install: true,
  dependencies: deps_found,
  install_dir: join_paths(get_option('prefix'), 'lib', 'hw'),
  cpp_args: use_minigbm ? ['-DUSE_MINIGBM'] : [],
  include_directories: use_minigbm ? include_directories('external/minigbm/cros_gralloc') : [] + inc_extra_v34,
)
