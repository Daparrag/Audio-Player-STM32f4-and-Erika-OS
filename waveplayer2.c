/**
  ******************************************************************************
  * @file    waveplayer2.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    feb-2016
  * @brief   TIMER audio program 
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

/* Includes ------------------------------------------------------------------*/
#include "waveplayer2.h"

/*-----------Wave private Variables--------------------*/
static __IO uint32_t SpeechDataOffset = 0x00;
static uint32_t wavelen = 0;
__IO uint32_t WaveCounter;
__IO ErrorCode WaveFileStatus = Unvalid_RIFF_ID;
 UINT BytesRead;
WAVE_FormatTypeDef WAVE_Format;
uint16_t buffer1[_MAX_SS] ={0x00};
uint16_t buffer2[_MAX_SS] ={0x00};
uint8_t buffer_switch = 1;
FIL fileR;
FILINFO fno;
//uint16_t *CurrentPos;



__IO uint32_t XferCplt = 0;
__IO uint32_t WaveDataLength = 0;
__IO uint8_t AudioPlayStart = 0;
__IO uint8_t RepeatState;
uint32_t AudioRemSize;
__IO uint8_t Command_index;


/*------------------ private Function Definition-------------*/
ErrorCode WavePlayer_WaveParsing(uint32_t *FileLen);
/*------------------------------------------------------------*/

/**
  * @brief  Checks the format of the .WAV file and gets information about
  *   the audio format. This is done by reading the value of a
  *   number of parameters stored in the file header and comparing
  *   these to the values expected authenticates the format of a
  *   standard .WAV  file (44 bytes will be read). If  it is a valid
  *   .WAV file format, it continues reading the header to determine
  *   the  audio format such as the sample rate and the sampled data
  *   size. If the audio format is supported by this application,
  *   it retrieves the audio format in WAVE_Format structure and
  *   returns a zero value. Otherwise the function fails and the
  *   return value is nonzero.In this case, the return value specifies
  *   the cause of  the function fails. The error codes that can be
  *   returned by this function are declared in the header file.
  * @param  None
  * @retval Zero value if the function succeed, otherwise it return
  *         a nonzero value which specifies the error code.
  */
WavePlayBack(uint32_t  SampleRate){
	/* Start playing */
	  AudioPlayStart = 1;
	  RepeatState =0;
	/*Configure: /TIM6/DMA1/DAC/GPIOA  */
	  AudioPlayerInit(SampleRate);
	  AudioRemSize = 0;
	  if(f_lseek(&fileR, WaveCounter)!=FR_OK){
		  LCD_ClearLine(LINE(17));
		  LCD_DisplayStringLine(LINE(17),"Error in f_lseek Operation");
	  }	else if (f_read (&fileR, buffer1, _MAX_SS, &BytesRead) | f_read (&fileR, buffer2, _MAX_SS, &BytesRead) != FR_OK){
		  LCD_ClearLine(LINE(17));
		  LCD_DisplayStringLine(LINE(17),"error read file");

	  	  }else{
	  		AudioPlayerStart((uint32_t) buffer1, _MAX_SS);
	  		buffer_switch = 1;
	  		XferCplt = 0;
	  		while (WaveDataLength & XferCplt){
	  		XferCplt=0;
	  			if(buffer_switch == 0)
	        	{
	        	/* Play data from buffer1 */
	  			AudioPlayerStart((uint32_t)buffer1, _MAX_SS);
	          	  /* Store data in buffer2 */
	          	  f_read (&fileR, buffer2, _MAX_SS, &BytesRead);
	          	  buffer_switch = 1;
	        	}
	        	else
	        	{
	        	/* Play data from buffer2 */
	        	AudioPlayerStart((uint32_t)buffer2, _MAX_SS);
	          	  /* Store data in buffer1 */
	          	  f_read (&fileR, buffer1, _MAX_SS, &BytesRead);
	          	  buffer_switch = 0;
	        	}
	  		//PauseResumeStatus = 1;
	  		}	///Count = 0;
	  	 }

}



WavePlayInit(TCHAR * WaveFileName){

	if (f_open(&fileR,(TCHAR*)WaveFileName ,FA_READ) != FR_OK)
	    {	Command_index = 1;
		 	 LCD_ClearLine(LINE(17));
			 LCD_DisplayStringLine(LINE(17),"Error Opening the file");
	    }else if(f_read (&fileR, buffer1, _MAX_SS, &BytesRead)!= FR_OK){
	    		LCD_ClearLine(LINE(17));
	    		LCD_DisplayStringLine(LINE(17),"Error Opening the file");
	    		}else{
	    			WaveFileStatus = WaveParsing(&wavelen);
	    			if (WaveFileStatus == Valid_WAVE_File)  /* the .WAV file is valid */
	    			      {
	    			        /* Set WaveDataLenght to the Speech wave length */
	    			        WaveDataLength = WAVE_Format.DataSize;
	    			      }

	    			WavePlayBack(WAVE_Format.SampleRate);
	    			}
}
  
  
ErrorCode WaveParsing(uint32_t *FileLen)
{
  uint32_t temp = 0x00;
  uint32_t extraformatbytes = 0;

  /* Read chunkID, must be 'RIFF' */
  temp = MyReadUnit((uint8_t*)buffer1, 0, 4, BigEndian);
  if (temp != CHUNK_ID)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unvalid_RIFF_ID");
    return(Unvalid_RIFF_ID);
  }

  /* Read the file length */
  WAVE_Format.RIFFchunksize = MyReadUnit((uint8_t*)buffer1, 4, 4, LittleEndian);

  /* Read the file format, must be 'WAVE' */
  temp = MyReadUnit((uint8_t*)buffer1, 8, 4, BigEndian);
  if (temp != FILE_FORMAT)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unvalid_WAVE_Format");
    return(Unvalid_WAVE_Format);
  }

  /* Read the format chunk, must be'fmt ' */
  temp = MyReadUnit((uint8_t*)buffer1, 12, 4, BigEndian);
  if (temp != FORMAT_ID)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unvalid_FormatChunk_ID");
    return(Unvalid_FormatChunk_ID);
  }
  /* Read the length of the 'fmt' data, must be 0x10 -------------------------*/
  temp = MyReadUnit((uint8_t*)buffer1, 16, 4, LittleEndian);
  if (temp != 0x10)
  {
    extraformatbytes = 1;
  }
  /* Read the audio format, must be 0x01 (PCM) */
  WAVE_Format.FormatTag = MyReadUnit((uint8_t*)buffer1, 20, 2, LittleEndian);
  if (WAVE_Format.FormatTag != WAVE_FORMAT_PCM)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unsupporetd_FormatTag");
    return(Unsupporetd_FormatTag);
  }

  /* Read the number of channels, must be 0x01 (Mono) or 0x02 (Stereo) */
  WAVE_Format.NumChannels = MyReadUnit((uint8_t*)buffer1, 22, 2, LittleEndian);

  /* Read the Sample Rate */
  WAVE_Format.SampleRate = MyReadUnit((uint8_t*)buffer1, 24, 4, LittleEndian);

  /* Read the Byte Rate */
  WAVE_Format.ByteRate = MyReadUnit((uint8_t*)buffer1, 28, 4, LittleEndian);

  /* Read the block alignment */
  WAVE_Format.BlockAlign = MyReadUnit((uint8_t*)buffer1, 32, 2, LittleEndian);

  /* Read the number of bits per sample */
  WAVE_Format.BitsPerSample = MyReadUnit((uint8_t*)buffer1, 34, 2, LittleEndian);
  if (WAVE_Format.BitsPerSample != BITS_PER_SAMPLE_16)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unsupporetd_Bits_Per_Sample");
    return(Unsupporetd_Bits_Per_Sample);
  }
  SpeechDataOffset = 36;
  /* If there is Extra format bytes, these bytes will be defined in "Fact Chunk" */
  if (extraformatbytes == 1)
  {
    /* Read th Extra format bytes, must be 0x00 */
    temp = MyReadUnit((uint8_t*)buffer1, 36, 2, LittleEndian);
    if (temp != 0x00)
    {
    	LCD_ClearLine(LINE(18));
    	LCD_DisplayStringLine(LINE(18),"Unsupporetd_ExtraFormatBytes");
      return(Unsupporetd_ExtraFormatBytes);
    }
    /* Read the Fact chunk, must be 'fact' */
    temp = MyReadUnit((uint8_t*)buffer1, 38, 4, BigEndian);
    if (temp != FACT_ID)
    {
    	LCD_ClearLine(LINE(18));
    	LCD_DisplayStringLine(LINE(18),"Unvalid_FactChunk_ID");
      return(Unvalid_FactChunk_ID);
    }
    /* Read Fact chunk data Size */
    temp = MyReadUnit((uint8_t*)buffer1, 42, 4, LittleEndian);

    SpeechDataOffset += 10 + temp;
  }
  /* Read the Data chunk, must be 'data' */
  temp = MyReadUnit((uint8_t*)buffer1, SpeechDataOffset, 4, BigEndian);
  SpeechDataOffset += 4;
  if (temp != DATA_ID)
  {
	  LCD_ClearLine(LINE(18));
	  LCD_DisplayStringLine(LINE(18),"Unvalid_DataChunk_ID");
    return(Unvalid_DataChunk_ID);
  }

  /* Read the number of sample data */
  WAVE_Format.DataSize = MyReadUnit((uint8_t*)buffer1, SpeechDataOffset, 4, LittleEndian);
  SpeechDataOffset += 4;
  WaveCounter =  SpeechDataOffset;
  LCD_ClearLine(LINE(18));
  	  LCD_DisplayStringLine(LINE(18),"Valid_WAVE_File");
  return(Valid_WAVE_File);
}


/**
* @brief  Reads a number of bytes and convert  them in Big
*         or little endian.
* @param  NbrOfBytes: number of bytes to read.
*         This parameter must be a number between 1 and 4.
* @param  ReadAddr: external memory address to read from.
* @param  Endians: specifies the bytes endianness.
*         This parameter can be one of the following values:
*             - LittleEndian
*             - BigEndian
* @retval Bytes read from the SPI Flash.
*/
uint32_t MyReadUnit(uint8_t *buffer, uint8_t idx, uint8_t NbrOfBytes, Endianness BytesFormat)
{
  uint32_t index = 0;
  uint32_t temp = 0;

  for (index = 0; index < NbrOfBytes; index++)
  {
    temp |= buffer[idx + index] << (index * 8);
  }

  if (BytesFormat == BigEndian)
  {
    temp = __REV(temp);
  }
  return temp;
}


/*--------------------------------
Callbacks implementation:
the callbacks prototypes are defined in the stm324xg_eval_audio_codec.h file
and their implementation should be done in the user code if they are needed.
Below some examples of callback implementations.
--------------------------------------------------------*/
/**
* @brief  Calculates the remaining file size and new position of the pointer.
* @param  None
* @retval None
*/

void Codec_DMA_DAC_TransferComplete_CallBack (uint32_t pBuffer, uint32_t Size){
/* Calculate the remaining audio data in the file and the new size 
for the DMA transfer. If the Audio files size is less than the DMA max 
data transfer size, so there is no calculation to be done, just restart 
from the beginning of the file ... */
/* Check if the end of file has been reached */	
#ifdef AUDIO_MAL_MODE_NORMAL  
 XferCplt = 1;
  if (WaveDataLength) WaveDataLength -= _MAX_SS;
  if (WaveDataLength < _MAX_SS) WaveDataLength = 0;
#else /* #ifdef AUDIO_MAL_MODE_CIRCULAR */
  
  
#endif /* AUDIO_MAL_MODE_CIRCULAR */
}
void Codec_DMA_DAC__HalfTransfer_CallBack(uint32_t pBuffer, uint32_t Size){
#ifdef AUDIO_MAL_MODE_CIRCULAR
    
#endif /* AUDIO_MAL_MODE_CIRCULAR */
  
  /* Generally this interrupt routine is used to load the buffer when 
  a streaming scheme is used: When first Half buffer is already transferred load 
  the new data to the first half of buffer while DMA is transferring data from 
  the second half. And when Transfer complete occurs, load the second half of 
  the buffer while the DMA is transferring from the first half ... */
  /* 
  ...........
  */
  if (WaveDataLength) WaveDataLength -=(_MAX_SS/2);
  if (WaveDataLength < (_MAX_SS/2)) WaveDataLength = 0;
  
}

void Codec_DMA_DAC_Error_CallBack(void* pData)
{
  /* Stop the program with an infinite loop */
  while (1)
  {}
  
  /* could also generate a system reset to recover from the error */
  /* .... */
}
