project('drmfb-composer', ['c','cpp'], version: '1.0')

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
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libbase/include/'),
  # system/core/libsystem/
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/'),
  # hardware/gralloc.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/hardware/libhardware/include/'),
  # system/graphics-base-v1.0.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/include/'),
  # sync/sync.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsync/include'),
  # libvndksupport
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libvndksupport/include'),
  # libsysutils
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsysutils/'),
  # graphics.common-V4 AIDL headers
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  # libcutils
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libcutils/include'),
  # log/log.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/logging/liblog/include_vndk/'),
  # BufferDescriptorInfo.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/aidl/android.hardware.graphics.allocator-V2-ndk-source/gen/include/'),
  # graphics.common@1.2
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.2/android.hardware.graphics.common@1.2_genc++_headers/gen/'),
  # graphics.common@1.1
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.1/android.hardware.graphics.common@1.1_genc++_headers/gen/'),
  # graphics.common@1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.0/android.hardware.graphics.common@1.0_genc++_headers/gen/'),
  # Hidlsupport.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhidl/base/include/'),
  # utils/Error.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libutils/include'),
  # fmq/MQDescriptorBase.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libfmq/base/'),
  # IMapper 4.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/mapper/4.0/android.hardware.graphics.mapper@4.0_genc++_headers/gen/'),
  # IBase 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/base/1.0/android.hidl.base@1.0_genc++_headers/gen/'),
  # IServiceNotification 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/'),
  # gralloctypes/Gralloc4.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/gralloc/types/include/'),
  # system/window.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativewindow/include/'),
  # nativebase.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativebase/include/'),
  #
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/common/aidl/android.hardware.common-V2-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/binder/ndk/include_platform/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/4.0/android.hardware.graphics.allocator@4.0_genc++_headers/gen/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhidl/transport/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/binder/include/'),
  # framework and libhwbinder both have IBinder.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhwbinder/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/composer/aidl/android.hardware.graphics.composer3-V1-ndk-source/gen/include/aidl/'),

  join_paths(ndk_root, 'prebuilt/vndk/v30/arm64/include/generated-headers/hardware/interfaces/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++_headers/gen/'),

  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/ui/include_vndk/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/math/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libfmq/include'),
  # local shim includes
#  join_paths('.', 'include/stable-c-v34/include'),
#  join_paths('.', 'include/stable-c-v34/implutils/include/'),
  join_paths('.', 'include/'),
)

inc_extra = inc_extra_v34

common_cflags = [
 '-D_GNU_SOURCE=1',
'-D_FILE_OFFSET_BITS=64',
 '-Wall',
 '-Wsign-compare',
 '-Wpointer-arith',
 '-Wcast-qual',
 '-Wcast-align',
'-Wno-unused-parameter',
'-Wunused-function',
#'-DHAS_DMABUF_SYSTEM_HEAP',
] 

common_cppflags = [
 '-D__NR_memfd_create',
#'-DHAS_DMABUF_SYSTEM_HEAP',
'-D_LIBCPP___CONFIG_SITE',
'-D_LIBCPP_ABI_VERSION=1',
#'-D_LIBCPP_ABI_NAMESPACE __ndk1',
'-D_LIBCPP_HAS_NO_VENDOR_AVAILABILITY_ANNOTATIONS',
'-D_LIBCPP_HAS_NO_STD_MODULES',
'-D_LIBCPP_HAS_NO_TIME_ZONE_DATABASE',
'-D_LIBCPP_PSTL_CPU_BACKEND_THREAD',
'-D_LIBCPP_HARDENING_MODE_DEFAULT=2',
'-D_LIBCPP_ABI_NAMESPACE=__1',
#'-D__ANDROID_API__=34',
'-D__ANDROID__',
'-D__ANDROID_MIN_SDK_VERSION__=34',
'-DANDROID_API_LEVEL=34',
# Since from AOSP 15 the VNDK migrate to system
# so need to compile as platform context not NDK context.
#'-stdlib=libc++',
'-O0',
'-g',
'-fPIC',
'-fvisibility=default',
#'-fno-inline',
'-fexceptions',
'-fno-rtti',
'-Wno-unused-parameter',
#'-static-libc++',
#'-static-libstdc++',
#'-stdlib=libc++',
]

common_cflags += [
#  '-D__ANDROID_API__=34',
  '-D__ANDROID__',
  '-O0', '-g',
  '-fPIC',
  '-fvisibility=default',
  '-Wno-unused-parameter'
]

common_link_args = [
  '-Wl,--no-gc-sections',
'-Wl,--whole-archive', '-lc++_static', '-Wl,--no-whole-archive',
]

nosym_link_args = ['-Wl,--unresolved-symbols=ignore-all']

drmfb_sources = files(
  'DrmComposer.cpp',
  'DrmDevice.cpp',
  'DrmDisplay.cpp',
  'DrmFramebuffer.cpp',
  'DrmFramebufferLibDrm.cpp',
  'DrmHotplugThread.cpp',
  'DrmVsyncThread.cpp',
  'GraphicsThread.cpp',
  'service.cpp',
  'ComposerResources.cpp',
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
base_deps = []
stub_libs = []                                                                                                                                
lib_names = [
 'cutils', 'hardware', 'log', 'base',
 'nativewindow', 'sync', 'binder_ndk', 'utils', 'fmq',
 'hidltransport', 'c++_shared', 'gralloctypes', 'hidlbase', 'ui', 'binder'
#    'android.hardware.graphics.composer@2.1',
]

#  if with_libbacktrace
#    lib_names += ['backtrace']
#  endif
foreach lib : lib_names
    stub_libs += shared_library(                                                     
      lib,
      files('android_stub/' + lib + '_stub.cpp'),
      include_directories : inc_extra,
      c_args: common_cflags,
      cpp_args: common_cppflags,
      link_args: common_link_args + nosym_link_args,
      install : false,
      #pic: true,
    )
  base_deps = declare_dependency(
    link_with : stub_libs,
  )
endforeach

lib = 'android.hardware.graphics.composer@2.1'
stub_libs += shared_library(
      lib,
      files('android_stub/' + lib + '_stub.cpp'),
      include_directories : inc_extra,
      c_args: common_cflags,
      cpp_args: common_cppflags,
      link_args: common_link_args + nosym_link_args,
      install : false,
      #pic: true,
      name_prefix : '',
 )

lib = 'hidlbase_log'
stub_libs += static_library(
      lib,
      files('android_stub/' + lib + '_stub.cpp'),
      include_directories : inc_extra,
      c_args: common_cflags,
      cpp_args: common_cppflags,
      link_args: common_link_args + nosym_link_args,
      install : false,
      #pic: true,
      name_prefix : '',
)

deps_found = [base_deps, libdrm_dep]

dep_names = [
    'libbase',
    'libbinder_ndk',
    'libhidlbase',
    'liblog',
    'android.hardware.graphics.composer@2.1',
]

aidl_deps = []
foreach name : dep_names
    d = cc.find_library(name, required: false)
    if d.found()
        aidl_deps += [d]
    endif
endforeach


executable(
  'drmfb-composer',
  drmfb_sources,
  install: true,
  dependencies: deps_found + aidl_deps,
  link_with : stub_libs,
  link_args: [common_link_args, '-Wl,--no-as-needed'] + nosym_link_args,
  install_dir: join_paths(get_option('prefix'), 'lib', 'hw'),
  cpp_args: [use_minigbm ? ['-DUSE_MINIGBM'] : [], common_cppflags],
  include_directories: use_minigbm ? include_directories('external/minigbm/cros_gralloc') : [] + inc_extra_v34,
)

install_data('android.hardware.graphics.composer@2.1-service.drmfb.xml',
  install_dir : join_paths(get_option('datadir'), 'vintf')
)
