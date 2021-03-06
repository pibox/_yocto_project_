DEPENDS += "libdrm expat udev"
X11_DEPS += "dri2proto"

DRIDRIVERS = "swrast"
DRIDRIVERS_append_x86 = ",i915,i965"
DRIDRIVERS_append_x86-64 = ",i915,i965"

EXTRA_OECONF += "--disable-gallium --without-gallium-drivers"
EXTRA_OECONF += "--enable-dri --with-dri-drivers=${DRIDRIVERS}"
EXTRA_OECONF += "--enable-gbm"

PACKAGECONFIG[gles] = "--enable-gles1 --enable-gles2, --disable-gles1 --disable-gles2"

EGL_PLATFORMS  = "drm"
EGL_PLATFORMS .="${@base_contains('DISTRO_FEATURES', 'x11', ',x11', '', d)}"
EGL_PLATFORMS .="${@base_contains('DISTRO_FEATURES', 'wayland', ',wayland', '', d)}"
PACKAGECONFIG[egl] = "--enable-egl --with-egl-platforms=${EGL_PLATFORMS}, --disable-egl"

python populate_packages_prepend() {
    dri_drivers_root = os.path.join(d.getVar('libdir', True), "dri")

    do_split_packages(d, dri_drivers_root, '^(.*)_dri\.so$', 'mesa-dri-driver-%s', 'Mesa %s DRI driver', extra_depends='')
}

PACKAGES_DYNAMIC += "^mesa-dri-driver-.*"

FILES_${PN}-dbg += "${libdir}/dri/.debug/*"

