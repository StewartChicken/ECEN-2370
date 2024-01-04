#include "Gyro.h"

[[maybe_unused]] static SPI_HandleTypeDef GYRO_Handle;
[[maybe_unused]] static HAL_StatusTypeDef GYRO_Status;

[[maybe_unused]] static int16_t GYRO_angle;


/**
 * @brief initialize gyro registers 
*/
void GYRO_Init()
{
    GYRO_Power_On();

    GYRO_config_reg(CTRL1_ADDR, CTRL1_CONFIG);
    GYRO_config_reg(CTRL4_ADDR, CTRL4_CONFIG);
    GYRO_config_reg(CTRL5_ADDR, CTRL5_CONFIG);
    GYRO_config_reg(FIFO_CTRL_ADDR, FIFO_CTRL_CONFIG);

    if(GYRO_Status != HAL_OK)
    {
        for(;;);
    }

}

/**
 * @brief Configure pins 7, 8, 9 for port F and pin 1 for port C to enable communication with the gyro
*/
void GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

    GPIO_InitTypeDef SpiPinConfig; // Creates new GPIO config for the gyroscope

    SpiPinConfig.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    SpiPinConfig.Mode = GPIO_MODE_AF_PP; // Alternate function push/pull
    SpiPinConfig.Pull = GPIO_NOPULL; 
    SpiPinConfig.Speed = GPIO_SPEED_FREQ_LOW;
    SpiPinConfig.Alternate = 0b101; // Enable alternate function 5 
    HAL_GPIO_Init(GPIOF, &SpiPinConfig); // Initialize

    // Chip Select
    SpiPinConfig.Pin = GPIO_PIN_1;       
    SpiPinConfig.Mode = GPIO_MODE_OUTPUT_OD;
    SpiPinConfig.Pull = GPIO_PULLUP;     
    SpiPinConfig.Speed = GPIO_SPEED_FREQ_HIGH;    
    HAL_GPIO_Init(GPIOC, &SpiPinConfig); 
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //Set it; defaults to 0, pull high.
}

/**
 * @brief Initialize spi5 to enable communication with gyroscope
*/
void SPI5_Init()
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;

    GYRO_Handle.Instance = SPI5;
    GYRO_Handle.Init.Mode = SPI_MODE_MASTER;
    GYRO_Handle.Init.Direction = SPI_DIRECTION_2LINES;
    GYRO_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
    GYRO_Handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
    GYRO_Handle.Init.CLKPhase = SPI_PHASE_2EDGE;
    GYRO_Handle.Init.NSS = SPI_NSS_SOFT;
    GYRO_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    GYRO_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    GYRO_Handle.Init.TIMode = SPI_TIMODE_DISABLE;
    GYRO_Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    GYRO_Handle.Init.CRCPolynomial = 0;

    GYRO_Status = HAL_SPI_Init(&GYRO_Handle);

}

/**
 * @brief Turn gyroscope on
*/
void GYRO_Power_On()
{
    SPI5->CR1 |= (SPI_CR1_SPE); // Enable SPE in CR1 of SPI5
}

/**
 * @brief Turn gyroscope off
*/
void GYRO_Power_Off()
{
    SPI5->CR1 &= ~(SPI_CR1_SPE); // Enable SPE in CR1 of SPI5
}

/**
 * @brief Pull chip select low to enable communication with gyro
*/
void GYRO_Enable_Slave_Communication(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // Write low
}

/**
 * @brief Bring chip select high to disable communication with gyro
*/
void GYRO_Disable_Slave_Communication(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); // Write high
}

/**
 * @brief Configure a register of the gyro
 * 
 * @param address - address of which gyro register to configure
 * @param config - config information
*/
void GYRO_config_reg(uint8_t address, uint8_t config)
{
    uint16_t buffer = GYRO_WRITE | address | config << 8;
    
    GYRO_Enable_Slave_Communication();
    GYRO_Status = HAL_SPI_Transmit(&GYRO_Handle, (uint8_t*) &buffer, 2, HAL_MAX_DELAY);
    GYRO_Disable_Slave_Communication();

}

/**
 * @brief Return the current configuration/value of a specific register within the gyroscope
 * 
 * @param address - address of register to access
 * 
 * @return returns uint8_t which contains the data of the specified register
*/
uint8_t GYRO_get_reg_value(uint8_t address)
{
    uint8_t transmission = GYRO_READ | address; // Read from register at address
    uint16_t receivedData = 0;

    GYRO_Enable_Slave_Communication();
    //GYRO_Status = HAL_SPI_TransmitReceive(&GYRO_Handle, &transmission, (uint8_t*) &receivedData, 2, HAL_MAX_DELAY);
    GYRO_Status = HAL_SPI_TransmitReceive(&GYRO_Handle, &transmission, (uint8_t*) &receivedData, 2, HAL_MAX_DELAY);

    GYRO_Disable_Slave_Communication();

    if(GYRO_Status != HAL_OK)
    {
        for(;;);
    }

    receivedData = (0xFF00 & receivedData) >> 8;

    return receivedData;
}

/**
 * @brief Update angle that the gyroscope is being held at by the user
 * 
 * @param angle - the value the angle should be adjusted by
*/
void GYRO_update_angle(int16_t angle)
{
    GYRO_angle += angle;
}

/**
 * @brief Get the current angle of the gyroscope
 * 
 * @return - uint16_t which stores the angle information of the gyroscope
*/
int16_t GYRO_get_angle(void)
{
    return GYRO_angle;
}