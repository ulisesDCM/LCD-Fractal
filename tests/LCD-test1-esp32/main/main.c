#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/spi_master.h>

#define LOG_MAIN_TAG        ("main.c")

#define SPIX_HOST           (SPI3_HOST)
#define SPI3_CS0_PIN        (5)
#define SPI3_SCLK_PIN       (18)
#define SPI3_MISO_PIN       (19)
#define SPI3_MOSI_PIN       (23)

spi_device_handle_t spi;

void test_task(void *pvParameters){
    while(1){
        ESP_LOGI(LOG_MAIN_TAG, "Running task 1");
        vTaskDelay( 1000 / portTICK_PERIOD_MS);
    }
}

static esp_err_t spi_configuration(void){
    esp_err_t ret = ESP_OK;

    spi_bus_config_t bus_config = {
        .miso_io_num = SPI3_MISO_PIN,
        .mosi_io_num = SPI3_MOSI_PIN,
        .sclk_io_num = SPI3_SCLK_PIN,
        .quadhd_io_num = -1,
        .quadwp_io_num = -1,
    };

    spi_device_interface_config_t dev_conf = {
        .mode = 0,
        .spics_io_num = SPI3_CS0_PIN
    };

    /* Initialize SPI Bus. */
    ret = spi_bus_initialize(SPIX_HOST, &bus_config, SPI_DMA_DISABLED);
    if(ret != ESP_OK){
        ESP_ERROR_CHECK(ret);
    }

    /* Initialize SPI Bus. */
    ret = spi_bus_add_device(SPIX_HOST, &dev_conf, &spi);
    if(ret != ESP_OK){
        ESP_ERROR_CHECK(ret);
    }

    return ret;
}

void app_main(void)
{
    
    xTaskCreate( test_task, "test task", 1024*2, NULL, 1, NULL );

    while(1){
        ESP_LOGI(LOG_MAIN_TAG, "Hello world!!!");
        vTaskDelay( 1000 / portTICK_PERIOD_MS);
    }    
}
