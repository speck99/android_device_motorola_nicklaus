#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/strings.h>
#include <android-base/logging.h>

#include "property_service.h"

namespace android {
namespace init {

void init_alarm_boot_properties()
{
    char const *boot_mode_file = "/sys/devices/virtual/BOOT/BOOT/boot/boot_mode";
    std::string boot_mode;

    if (android::base::ReadFileToString(boot_mode_file, &boot_mode)) {
        if (android::base::Trim(boot_mode) == "7") {
            property_set("ro.alarm_boot", "true");
        }
    }
    else {
        LOG(ERROR) << "Unable to read boot_mode from " << boot_mode_file;
    }
}

void check_device()
{
    std::string ram;

    ram = android::base::GetProperty("ro.boot.ram", "");

    if (ram == "2GB")
    {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "384m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");

        property_set("ro.hwui.texture_cache_size", "72");
        property_set("ro.hwui.layer_cache_size", "48");
        property_set("ro.hwui.r_buffer_cache_size", "8");
        property_set("ro.hwui.path_cache_size", "32");
        property_set("ro.hwui.gradient_cache_size", "1");
        property_set("ro.hwui.drop_shadow_cache_size", "6");
        property_set("ro.hwui.texture_cache_flushrate", "0.4");
        property_set("ro.hwui.text_small_cache_width", "1024");
        property_set("ro.hwui.text_small_cache_height", "1024");
        property_set("ro.hwui.text_large_cache_width", "2048");
        property_set("ro.hwui.text_large_cache_height", "1024");
    }
    else
    {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "288m");
        property_set("dalvik.vm.heapsize", "768m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");

        property_set("ro.hwui.texture_cache_size", "72");
        property_set("ro.hwui.layer_cache_size", "48");
        property_set("ro.hwui.r_buffer_cache_size", "8");
        property_set("ro.hwui.path_cache_size", "32");
        property_set("ro.hwui.gradient_cache_size", "1");
        property_set("ro.hwui.drop_shadow_cache_size", "6");
        property_set("ro.hwui.texture_cache_flushrate", "0.4");
        property_set("ro.hwui.text_small_cache_width", "1024");
        property_set("ro.hwui.text_small_cache_height", "1024");
        property_set("ro.hwui.text_large_cache_width", "2048");
        property_set("ro.hwui.text_large_cache_height", "1024");
    }
}

void num_sims()
{
    std::string dualsim;

    dualsim = android::base::GetProperty("ro.boot.dualsim", "");

    if (dualsim == "true") {
        property_set("persist.radio.multisim.config", "dsds");
    } else {
        property_set("persist.radio.multisim.config", "");
    }
}
void vendor_load_properties()
{
    LOG(INFO) << "Starting custom init";
    std::string platform;

    sku = android::base::GetProperty("ro.boot.hardware.sku", "");
    platform = android::base::GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    check_device();
    num_sims();
    init_alarm_boot_properties();
}

}  // namespace init
}  // namespace android