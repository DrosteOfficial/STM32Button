#include "utils.h"

int values[4][4] = {
    {1, 2, 3, 15},
    {4, 5, 6, 14},
    {7, 8, 9, 13},
    {10, 0, 11, 12}
};

void blinking(void)
{
    // Check pin state and perform corresponding action
    HAL_GPIO_WritePin(User_led_GPIO_Port, User_led_Pin, GPIO_PIN_SET);
    HAL_Delay(500); // Corrected from HAL_WAIT to HAL_Delay
    HAL_GPIO_WritePin(User_led_GPIO_Port, User_led_Pin, GPIO_PIN_RESET);
    HAL_Delay(500); // Corrected from HAL_WAIT to HAL_Delay
}

void blinkXTimes(int x)
{
    for (int i = 0; i < x; i++) {
        HAL_GPIO_WritePin(User_led_GPIO_Port, User_led_Pin, GPIO_PIN_SET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(User_led_GPIO_Port, User_led_Pin, GPIO_PIN_RESET);
        HAL_Delay(200);
    }
}

void pinInit(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0, GPIO_PIN_RESET);
}

int readInput(void)
{
    int row = -1;
    int col = -1;

    for (int i = 4; i < 8; i++) {
        row = i - 4;
        uint16_t pom = 1 << i;

        HAL_GPIO_WritePin(GPIOA, pom, GPIO_PIN_SET);
                  HAL_Delay(50);

        for (int j = 0; j < 4; j++) {
            uint16_t pom1 = 1 << j;
            if (HAL_GPIO_ReadPin(GPIOA, pom1) == GPIO_PIN_SET) {
                col = j;
                break;
            }
            HAL_Delay(50);
        }
        HAL_GPIO_WritePin(GPIOA, pom, GPIO_PIN_RESET);
        if (col != -1) {
            break;
        }
    }

    if (col == -1) {
        return -1;
    }
    int retValue = values[row][col];
    return retValue;
}
