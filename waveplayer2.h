/**
  ******************************************************************************
  * @file    waveplayer2.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    feb-2016
  * @brief   Header for waveplayer2.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WAVE_PLAYER_H
#define __WAVE_PLAYER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio_dac.h"
#include "stm32f4_discovery_lis302dl.h"
#include <stdio.h>
#include "stm32f4xx_it.h"
#include "ff.h"
#include "stm32f4_discovery_lcd.h"


/* Exported types ------------------------------------------------------------*/
typedef enum
{
  LittleEndian,
  BigEndian
}Endianness;

typedef struct
{
  uint32_t  RIFFchunksize;
  uint16_t  FormatTag;
  uint16_t  NumChannels;
  uint32_t  SampleRate;
  uint32_t  ByteRate;
  uint16_t  BlockAlign;
  uint16_t  BitsPerSample;
  uint32_t  DataSize;
}
WAVE_FormatTypeDef;

typedef enum
{
  Valid_WAVE_File = 0,
  Unvalid_RIFF_ID,
  Unvalid_WAVE_Format,
  Unvalid_FormatChunk_ID,
  Unsupporetd_FormatTag,
  Unsupporetd_Number_Of_Channel,
  Unsupporetd_Sample_Rate,
  Unsupporetd_Bits_Per_Sample,
  Unvalid_DataChunk_ID,
  Unsupporetd_ExtraFormatBytes,
  Unvalid_FactChunk_ID
} ErrorCode;

/* Exported constants --------------------------------------------------------*/
#define  CHUNK_ID                            0x52494646  /* correspond to the letters 'RIFF' */
#define  FILE_FORMAT                         0x57415645  /* correspond to the letters 'WAVE' */
#define  FORMAT_ID                           0x666D7420  /* correspond to the letters 'fmt ' */
#define  DATA_ID                             0x64617461  /* correspond to the letters 'data' */
#define  FACT_ID                             0x66616374  /* correspond to the letters 'fact' */
#define  WAVE_FORMAT_PCM                     0x01
#define  FORMAT_CHNUK_SIZE                   0x10
#define  CHANNEL_MONO                        0x01
#define  CHANNEL_STEREO                      0x02
#define  SAMPLE_RATE_8000                    8000
#define  SAMPLE_RATE_11025                   11025
#define  SAMPLE_RATE_22050                   22050
#define  SAMPLE_RATE_44100                   44100
#define  BITS_PER_SAMPLE_8                   8
#define  BITS_PER_SAMPLE_16                  16

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void WaveDMA_Interrupt_Handler(void);
void Codec_DMA_DAC_TransferComplete_CallBack (uint32_t pBuffer, uint32_t Size);
void Codec_DMA_DAC__HalfTransfer_CallBack(uint32_t pBuffer, uint32_t Size);
void Codec_DMA_DAC_Error_CallBack(void* pData);
uint32_t MyReadUnit(uint8_t *buffer, uint8_t idx, uint8_t NbrOfBytes, Endianness BytesFormat);
ErrorCode WaveParsing(uint32_t *FileLen);
#endif /* __WAVE_PLAYER_H */
