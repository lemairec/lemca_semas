/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "AppHW.h"
#include "sdkconfig.h"
#include "lemca.h"

#include "IsoCommonDef.h"
#include "IsoCommonApi.h"
#include "settings.h"
#include "esp_err.h"
#include "spiffs_access.h"
#include "esp_heap_caps.h"

extern int isobus_main(int_t argc, char_t* argv[]);
void app_main(void)
{
	hw_DebugPrint("app_main() called\n");

    // log available memory
    hw_DebugPrint("Internal RAM: %u bytes free\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    hw_DebugPrint("SPI RAM: %u bytes free\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
	hw_DebugPrint("app_main \n");


	/* Initialize file storage */
	ESP_ERROR_CHECK(init_spiffs());


	/* Initialize application */
	Settings_init();






	hw_DebugPrint("aSettings_init\n");
	hw_DebugPrint("Internal RAM: %u bytes free\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    hw_DebugPrint("SPI RAM: %u bytes free\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
	hw_DebugPrint("app_main \n");

	lemca_init();

	isobus_main(0, NULL);

}
