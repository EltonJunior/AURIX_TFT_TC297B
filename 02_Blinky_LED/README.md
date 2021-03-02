# AURIX Blinky_LED

This tutorial will guide you to do a __Hello World__ with a blink Led on AURIX TFT Board.

<img  src="https://drive.google.com/uc?id=1pgr-lLuV-1v0e2IiE_WKkSCWhLU8G-r-"  width="400"  height="400"/>

## Introduction

As every programmer says, if you don't do a Hello World you don't ready to do another program. So, we are going to broke this "malediction". If you want more examples you can find them on __Infineon__  [AURIX_code_examples](https://github.com/Infineon/AURIX_code_examples). there you can find a lot of examples, so we are going to use [Blinky_LED_1_KIT_TC297_TFT](https://github.com/Infineon/AURIX_code_examples/tree/master/code_examples/Blinky_LED_1_KIT_TC297_TFT), there you will find the program that will use as a base in this example. Also, you can find more detail about this project on [Blinky_LED_1 for KIT_AURIX_TC297_TFT](https://www.infineon.com/dgdl/Infineon-AURIX_Blinky_LED_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b96a038bf)

### Make a Blinky_LED using Default Project

In the [Default Project](https://github.com/EltonJunior/AURIX_TFT_TC297B/tree/main/Default) we done the imported the project in the HighTec IDE and compile it, so, to create a __Blinky_Led Project__ we need to copy de __Default Project__ and past it in the __WorkSpace__.

![Image_1](https://drive.google.com/uc?id=17M0yak7wOEHJroBNT18-Er2Iu7BIAZnS)

Now we need to renamed de __Default - Copy__ to __Blinky_LED__.

![Image_2](https://drive.google.com/uc?id=1TIsONAYYiIKVBvFQXw2Zbvl3UIkugPlo)

So, now go to __HighTec IDE__ and import the __Blinky_Led Project__ from workspace to __HighTec Project Explorer__, to do it, click in __File__ -> __Import__.

  ![Image_3](https://drive.google.com/uc?id=1U285IpwpwuTY1gjxVG-AkTiYkJS4QubX )

It will open a new window, in the __General__, expand and select __Existing projects into Workspace__.

![Image_4](https://drive.google.com/uc?id=1jBIW1vm510gRf5DPbRu0KMx4Cr-jjKnS) 

It will open a new window, where you need to __Browser__ to Workspace and select the __Workspace folder__ then click __Finish__.

![Image_5](https://drive.google.com/uc?id=1UCd8FkKlqdCTJf3L8a1rbBapo8O9QmfP)

After import, __Right Click__ on __Blink_LED Project__ change it to __Set Active Project__.

![Image_6](https://drive.google.com/uc?id=1HuButSf549EtsX_NewxNrQsJ7xbre_b1)

Done, we've finished the import of our default project, and below you can see the final work.

## Build the Blinky_LED Project

Now it is possible to compile it. To do it change __Active Build Connfiguration__ to __Debug__, to do this __Right Click__ on __Blinky_LED Project__ and go throughout __Builg Configuration__ -> __Set Active__ -> __Debug__ below you can see the final work.

![Image_7](https://drive.google.com/uc?id=1B944tKjecDFwHQMuNOOYKbEmUzA7t5mS)

Yes, You got it. Now __Right Click__ on __Blinky_LED Project__ and click in __Build Project__.

![Image_8](https://drive.google.com/uc?id=15ooDfckTUeNh4ybAUA30S3BA3xhfpEcI)

YEP! we've done our import correctly.

![Image_9](https://drive.google.com/uc?id=1gJD281O10ZTEiyTKiEGZnqCeQJbFn38E)

## Create Blinky_LED Files

Now we are going to include the Blink Led files, on __Blinky_LED Project__ go throughout the path __src -> AppSw -> Tricore -> Demo_IIId__ and create the files __Blinky_LED.c__ and __Blinky_LED.h__. __Right Click__ on __Blinky_LED Project -> New -> Source File__.

![Image_10](https://drive.google.com/uc?id=1YgK_wnxfehdRZYVAReZJvdlwOwhwmUEx)

put the name __Blinky_LED.c__ and click __Finish__.

![Image_11](https://drive.google.com/uc?id=1mz0TrwW8tq7GGfYAA6v1nKg2gVw4qFY7)
 
do it to __Blinky_LED.h__.

![Image_12](https://drive.google.com/uc?id=1FtoIxJ9eoeiA0TkpT4TeABWZXiXg1xYz)

Now, it's time to implement the code, to do it in an easy way, copy the code of [Blinky_LED.c](https://github.com/Infineon/AURIX_code_examples/blob/master/code_examples/Blinky_LED_1_KIT_TC297_TFT/Blinky_LED.c) and [Blinky_LED.h](https://github.com/Infineon/AURIX_code_examples/blob/master/code_examples/Blinky_LED_1_KIT_TC297_TFT/Blinky_LED.h), open the file that you have created and past respectively.

![Image_13](https://drive.google.com/uc?id=1ei0AZKSBbunZi-ScqisftPacAP1v3rP7)

>If you want to know about the function used in this example have a look at [Blinky_LED_1 for KIT_AURIX_TC297_TFT](https://www.infineon.com/dgdl/Infineon-AURIX_Blinky_LED_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b96a038bf), this is the Training made by Infineon and explain the __Blinky_LED__ example.

After created both files, its time to call them in the main function, in __src -> AppSw -> Tricore -> Main__ open the file __Cpu0_Main.c__ go to [Cpu0_Main.c](https://github.com/Infineon/AURIX_code_examples/blob/master/code_examples/Blinky_LED_1_KIT_TC297_TFT/Cpu0_Main.c) and copy the code. The code in the [Cpu0_Main.c](https://github.com/Infineon/AURIX_code_examples/blob/master/code_examples/Blinky_LED_1_KIT_TC297_TFT/Cpu0_Main.c) already has the Included of __Blinky_LED.h__, the call of __InitLED__ and __blinkLED__ function.

![Image_14](https://drive.google.com/uc?id=18fz_aV9GuXLIr7GLY7wrLobwywiblC6V)

## Debug the Blinky_LED Project

Now it is time to debug and test our project on the Board. With Board plugged on PC. __Right Click__ on __Blinky_LED Project__ and go throughout __Debug As -> Debug Configurations..__.

![Image_15](https://drive.google.com/uc?id=1TVkIF9O-yeveENR6eSjU2_kGgaJzhVFv)

In the new windows, double click in __Universal Debug Engine__.

![Image_16](https://drive.google.com/uc?id=1za3LtSQlUjH1KmggeVPuWCLzWpNEm62B)

In the new windows, in __Project:__ click in __Browser__ and Choice the __Blinky_LED Project__ and click __OK__.

![Image_17](https://drive.google.com/uc?id=1ckAzKadcmJ1YvVUMroMjeysHDwfT1YBz)

In the new windows, in __C/C++ Application:__ click in __Browser__ open __Debug__ path and Choice the __Default.elf__ and click __Open__.

![Image_18](https://drive.google.com/uc?id=1eXAGUCRwI_hG-zUYQz_XIVtOzXKrbEVd)

Now select __UDE Startup__ and in __Select UDE Target Configuration File:__ click in __Browse Configuration__ it will open a new windows click in __New__ select __Use a default target configuration__ and expand __TriCore -> Infineon -> TC297B Application kit__ and choice __Application Kit with TC297T B-Step (Multicore Configuration)__ and click on __conclud__, choose a place in the computer and save it.

![Image_19](https://drive.google.com/uc?id=1fI61EK69H0OUQWnMSzyYjD1VQB4R1CqN)

after those steps, we will have the target to run the code into. click in __OK__

![Image_20](https://drive.google.com/uc?id=1c-qmunYZP-50siEARZQHEuE6O0HOT73L)

click in __Apply__ and in __Debug__

![Image_21](https://drive.google.com/uc?id=1HX-fkra7EsDE6W4Y1-0EWQyf5vxEdcXA)

it will start __Launching Blinky_LED Debug__

![Image_22](https://drive.google.com/uc?id=1f_z2ZW1Y9FcEPK6Tw6YBUbk1z2WmX3Cm)

After finished the Launching, it will open a new window, click __Program__ it will open a new window and flash the program into board after finished click in __Exit__ and __Exit__.

![Image_23](https://drive.google.com/uc?id=1KHtO0cZ6hC7y8M8MypoHfR8UBf31VPJr)

To run the program click in __Start Program__

![Image_24](https://drive.google.com/uc?id=1egNXcJ7ZuKvuNf609hvTSdK_anoxVy0Y)

Done. Now the Led should be Blinking.

<img  src="https://drive.google.com/uc?id=1pgr-lLuV-1v0e2IiE_WKkSCWhLU8G-r-"  width="400"  height="400"/>