# SD_DAC_AudioPlayerERIKA
Audio Player implementation over STM32F4 discovery board

<img src="https://github.com/Daparrag/Audio-Player-STM32f4-and-Erika-OS/blob/master/ImplementationDiagram.png" alt="Implementation Diagram" width="1000px" />

This Project repesent an implementation of an audio player over the operating system ERIKA and the STM32f4 discovery Board 
                        
The implementation consist of read the wav file from the SDcard using the SDIO and DMA2, then independently the DMA1 is able to acces to the memory
and transffer data directly from the flash memory and put it into the dac which automatically convert to analog values and then generate the sound. 


If you want excuted this program in your machine follow the next steps.

1. Install Eclipse with pluging for ERIKA-RTOS OS; you can find the instalator on: http://erika.tuxfamily.org/drupal/download.html

2. Once intalled the platform you can start creating a simple example for ERIKA-RTOS OS:                                                
    2.1 path: file->new->rtdruid project. and setup the name of the project for example audioplayertest.                                 
    2.2 create a project using a template for cortex-MX STM32F4 discovery board. Choose any DEMO.

3. Import the project:                                                                                                                  
    3.1 left click on the project-->import->File System                                                                                 
    3.2 Browse the folder where you dowmload the audio player project. and choose all the files.

4. Once imported the file system delete the content of the debug folder.

    4.1 left click on the project --> clear project
    
5. Compile(build) the project:

    5.1   left click on the project--> build project
    
6.copy the binary file generated on the folder Debug on the discovery board using the tool STM32 ST-LINK Utility which can be download for the web side of STM. or simple searching on google.

7. end

## This is How it looks

<img src="https://github.com/Daparrag/Audio-Player-STM32f4-and-Erika-OS/blob/master/AudioPlayer1.png" alt="SD-CARD view" width="1000px" />

<img src="https://github.com/Daparrag/Audio-Player-STM32f4-and-Erika-OS/blob/master/AudioPlayer2.png" alt="Reproductor view" width="1000px" />


    
