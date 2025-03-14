/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "network.h"
#include "network_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

DMA_HandleTypeDef hdma_memtomem_dma1_stream2;
/* USER CODE BEGIN PV */
int notifyReceived;

ai_handle network_model = AI_HANDLE_NULL;

AI_ALIGNED(32)
static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];

AI_ALIGNED(32)
static ai_float in_data[AI_NETWORK_IN_1_SIZE];
AI_ALIGNED(32)
static ai_float out_data[AI_NETWORK_OUT_1_SIZE];

static ai_buffer *ai_input;
static ai_buffer *ai_output;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_MDMA_Init(void);
static void MX_DMA_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Resize_Frame2(uint8_t *src, uint8_t *dst,uint16_t srcwidth,uint16_t srcheight);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_HSEM_FreeCallback(uint32_t SemMask){
	notifyReceived = 1;
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
}

//int aiInit(void) {
//  ai_error err;
//
//  /* Create and initialize the c-model */
//  const ai_handle acts[] = { activations };
//  err = ai_network_create_and_init(&network, acts, NULL);
//  if (err.type != AI_ERROR_NONE) {
//	  printf("Hello worldd\r\n");
//	  return -1;
//  }
//
//  /* Reteive pointers to the model's input/output tensors */
//  ai_input = ai_network_inputs_get(network, NULL);
//  ai_output = ai_network_outputs_get(network, NULL);
//
//  return 0;
//}
//
//int aiRun(const void *in_data, void *out_data) {
//  ai_i32 n_batch;
//  ai_error err;
//
//  /* 1 - Update IO handlers with the data payload */
//  ai_input[0].data = AI_HANDLE_PTR(in_data);
//  ai_output[0].data = AI_HANDLE_PTR(out_data);
//
//  /* 2 - Perform the inference */
//  n_batch = ai_network_run(network, &ai_input[0], &ai_output[0]);
//  if (n_batch != 1) {
//      err = ai_network_get_error(network);
//      printf("errr\r\n");
//
//  };
//
//  return 0;
//}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */




  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /* Activate HSEM notification for Cortex-M4*/
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
  /*
  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
  perform system initialization (system clock config, external memory configuration.. )
  */
  HAL_PWREx_ClearPendingEvent();
  HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
  /* Clear HSEM flag */
  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_MDMA_Init();
  MX_DMA_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
  ai_handle network = AI_HANDLE_NULL;
  ai_error err;
  ai_network_report report;

  /** @brief Initialize network */
  const ai_handle acts[] = { activations };
  err = ai_network_create_and_init(&network, acts, NULL);
  if (err.type != AI_ERROR_NONE) {
	  printf("ai init_and_create error\n");
	  return -1;
  }

  /** @brief {optional} for debug/log purpose */
  if (ai_network_get_report(network, &report) != true) {
	  printf("ai get report error\n");
	  return -1;
  }

  printf("Model name      : %s\n", report.model_name);
  printf("Model signature : %s\n", report.model_signature);

  ai_input = &report.inputs[0];
  ai_output = &report.outputs[0];
  printf("input[0] : (%d, %d, %d)\n", AI_BUFFER_SHAPE_ELEM(ai_input, AI_SHAPE_HEIGHT),
									  AI_BUFFER_SHAPE_ELEM(ai_input, AI_SHAPE_WIDTH),
									  AI_BUFFER_SHAPE_ELEM(ai_input, AI_SHAPE_CHANNEL));
  printf("output[0] : (%d, %d, %d)\n", AI_BUFFER_SHAPE_ELEM(ai_output, AI_SHAPE_HEIGHT),
									   AI_BUFFER_SHAPE_ELEM(ai_output, AI_SHAPE_WIDTH),
									   AI_BUFFER_SHAPE_ELEM(ai_output, AI_SHAPE_CHANNEL));

  /** @brief Fill input buffer with random values */
  srand(1);
  for (int i = 0; i < AI_NETWORK_IN_1_SIZE; i++) {
	  in_data[i] = rand() % 0xFFFF;
  }

  /** @brief Normalize, convert and/or quantize inputs if necessary... */

  /** @brief Perform inference */
  ai_i32 n_batch;

  /** @brief Create the AI buffer IO handlers
   *  @note  ai_inuput/ai_output are already initilaized after the
   *         ai_network_get_report() call. This is just here to illustrate
   *         the case where get_report() is not called.
   */
  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);

  /** @brief Set input/output buffer addresses */
  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].data = AI_HANDLE_PTR(out_data);

  /** @brief Perform the inference */
  n_batch = ai_network_run(network, &ai_input[0], &ai_output[0]);
  if (n_batch != 1) {
	  err = ai_network_get_error(network);
	  printf("ai run error %d, %d\n", err.type, err.code);
  }else {
	  /** @brief Post-process the output results/predictions */
	    printf("Inference output..\n");
	    for (int i = 0; i < AI_NETWORK_OUT_1_SIZE; i++) {
	  	  printf("%d,", out_data[i]);
	    }
	    printf("\n");
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  if(notifyReceived == 1){
//		  HAL_GPIO_TogglePin(GPIOJ, GPIO_PIN_2);
//		  HAL_Delay(100);
//	  }
//	  acquire_and_process_data(in_data);

  }
  /* USER CODE END 3 */
}

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma1_stream2
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma1_stream2 on DMA1_Stream2 */
  hdma_memtomem_dma1_stream2.Instance = DMA1_Stream2;
  hdma_memtomem_dma1_stream2.Init.Request = DMA_REQUEST_MEM2MEM;
  hdma_memtomem_dma1_stream2.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_stream2.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_stream2.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_stream2.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_memtomem_dma1_stream2.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_memtomem_dma1_stream2.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_stream2.Init.Priority = DMA_PRIORITY_VERY_HIGH;
  hdma_memtomem_dma1_stream2.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma1_stream2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma1_stream2.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma1_stream2.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_stream2) != HAL_OK)
  {
    Error_Handler( );
  }

}

/**
  * Enable MDMA controller clock
  */
static void MX_MDMA_Init(void)
{

  /* MDMA controller clock enable */
  __HAL_RCC_MDMA_CLK_ENABLE();
  /* Local variables */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOJ_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : PJ2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
#define resizeImgwidth 128
#define resizeImgheight 128
void Resize_Frame2(uint8_t *src, uint8_t *dst,uint16_t srcwidth,uint16_t srcheight)
{//https://www.programcreek.com/cpp/?CodeExample=resize+image
	int numComponents=3;
    int srcPitch = srcwidth * numComponents;

    float ratioX = (float)srcwidth / resizeImgwidth;
    float ratioY = (float)srcheight / resizeImgheight;

    for (int y = 0; y < resizeImgheight; y++) {
        int iY = y * ratioY;

        int offsetY = iY * srcPitch;

        for (int x = 0; x < resizeImgwidth; x++) {
            int iX = x * ratioX;

            int offsetX = iX * numComponents;

            //const T *srcPtrY = &src[offsetY];
            uint8_t *ptr = &src[offsetY];

            for (int i = 0; i < numComponents; i++) {
                *dst++ = ptr[offsetX + i];
            }
        }
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
