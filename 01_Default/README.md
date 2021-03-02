# AURIX Default Template

This tutorial will guide you how to prepare the HighTec IDE to develepor project using AURIX™ Family – TC29xT, Infineon iLLD, the idea is help to create project that will share other project togheter e.g. FreeRTOS.

## Introdution

Which IDE has its methon to create, start and configuration project, the HighTec isn't different, so, to make easy your development use the HighTec IDE, I already done a default project that you can get it [Here](https://github.com/EltonJunior/AURIX_TFT_TC297B/tree/main/01_Default). below I am going to discrible how to import and compile it. Go aread and get the project and help yourself.

### Import a Default Project into HighTec IDE

If you didn't make any project yet, don't freak out, I'm going to start a project from Zero. below you can see the HighTec when it was execute in the first time. In this windows you just need to close the welcome.

![image_0](https://drive.google.com/uc?id=1RKJtaL_qxT9ddeuU-ea5m9QmqW68F7on)

So, Before we done something in the HighTec IDE, we need to clone the **Default** project that should be found [Here](https://github.com/EltonJunior/AURIX_TFT_TC297B/tree/main/Default). and put it in the Workapace, if you don't know how to do it, look at [How to Clone a Repository on Github](https://www.wikihow.com/Clone-a-Repository-on-Github#:~:text=Enter%20%E2%80%9Cgit%20clone%E2%80%9D%20followed%20by%20the%20source%20location,type%20out%20the%20source%20location%20after%20the%20command.). Now you can close the Welcome windows, it will became this new windows in below image.

![Image_1](https://drive.google.com/uc?id=1XDlehlOzTXx9MYZ_aU8ZruZ7leYvQwrZ)

In this new windows, we're going to import our **Default** project, to import it, click in __File__ -> __Import__.

![Image_2](https://drive.google.com/uc?id=1U285IpwpwuTY1gjxVG-AkTiYkJS4QubX )

It will open a new windows, expand __General__ and select __Existing projects into Workspace__.

![Image_3](https://drive.google.com/uc?id=1jBIW1vm510gRf5DPbRu0KMx4Cr-jjKnS)

It will open a new windows, here you need to __Browser__ to Workspace and select the Workspace folder after that click __Finish__.

![Image_4](https://drive.google.com/uc?id=1EjzMOBSYmgk0EDJFVhF3q1wIk4tzzZ8_)

Done, we've finished the import of our default project and below you can see the final work.

![Image_5](https://drive.google.com/uc?id=1VVjh3RvpZ9x-kMoMBtSSFiz9GbuvmVUV)

Now it is possible to compile it. To do it move __Active Build Connfiguration__ to __Debug__, to do this __Right Click__ on __Default Project__ and go thoughout __Builg Configuration__ -> __Set Active__ -> __Debug__ below you can see the final work.

![Image_6](https://drive.google.com/uc?id=13sOtGdhNYozAop3rkG3E-QqG4f2jmvK_)

Before we build the __Default Project__ we need to create a __Environment variable__, to do it go to __File -> Properties__.

![Image_21](https://drive.google.com/uc?id=1z8TJaQx8FPiSiuRyxDNZmcr839x8Igst)

it will open a new windows. go to __C/C++ Build -> Enviorenment__ click in __Add__ will open a dailog Box in __Name:__ put __projdirpath__ and in __Value:__ put the directory of the workspace and click __OK__.

![Image_22](https://drive.google.com/uc?id=16f8-hxLJ2M40ZCkuLyVv_YjIsAylxCxd)

Click __Apply -> Apply and Close__.

![Image_23](https://drive.google.com/uc?id=1gkcsc_jZqB7_GZwN5fQy1OSD9RcolEiT)

## Build the Default Project

Yes, You got it. Now __Right Click__ on __Default Project__ and click in __Build Project__.

![Image_7](https://drive.google.com/uc?id=1MhQRaA7aP8iKnjWzPu10JIANtNyxtlPK)

It will start to build the project and you can follow it looking at __Console__.

![Image_8](https://drive.google.com/uc?id=1LwhDXALCD4A9K7xoGV1N8-2-9SJh5wBp)

YEP! we've done our import.

![Image_9](https://drive.google.com/uc?id=1kWH1f_5xkjzxLmzBu3JWUGIa8gp40qce)

we are going to use it to get the files inside the project or we can use it and only rename the project and import again.

## Debug the Default Project

Now it is time to debbuge and test our project in the Board. With Board pluged on PC. __Right Click__ on __Default Project__ and go throughout __Debug As -> Debug Configurations..__

![Image_10](https://drive.google.com/uc?id=1yOnifPKhR7OdLniED2e17Z3RS-3aEtMC)

In the new windows, doble click in __Universal Debug Engine__

![Image_11](https://drive.google.com/uc?id=1_gUsJxdwCkIs604Hdy3qxzNUO0xQx_JJ)

In the new windows, in __Project:__ click in __Browser__ and Choice the __Default Project__ and click __OK__.

![Image_12](https://drive.google.com/uc?id=1QbleqlNZhYD-LleqFNl0rt0X63MgYz1y)

In the new windows, in __C/C++ Application:__ click in __Browser__ open __Debug__ path and Choice the __Default.elf__ and click __Open__.

![Image_13](https://drive.google.com/uc?id=1AfIAJytd3poeuy_ThYgbwOP5Yd7lrIDn)

Now select __UDE Startup__ and in __Select UDE Target Configuratioin File:__ click in __Browse Configuration__ it will open a new windows click in __New__ select __Use a default target configuration__ and expand __TriCore -> Infineon -> TC297B Application kit__ and choice __Application Kit with TC297T B-Step (Multicore Configuration)__ and click on __conclud__, choice a place in the computer and save it.

![Image_14](https://drive.google.com/uc?id=1o6ISLy1WdY6sSkkXWTqP80bPhsq1KC3f)

after those steps we will have the target to run the code into. click in __OK__

![Image_15](https://drive.google.com/uc?id=1OQGXNlf-BkVHMBJOsvuz1ANl17HznCNV)

click in __Apply__ and in __Debug__

![Image_16](https://drive.google.com/uc?id=151Eitj-7b7LrylC6Ydb_YP2ABkiJHLuJ)

it will start __Launching Default Debug__

![Image_17](https://drive.google.com/uc?id=1idkpEj_PZiHoAPmw0FXTQibrkHpJuy3q)

After finished the Launching, it will open a new windows, click __Program__ it will open a new windows and fhash the prongram into board after finished click in __Exit__ and __Exit__.

![Image_18](https://drive.google.com/uc?id=1t0N2TR0Z74HtkwCEsuwlrLLihXvAfpeX)

To run the program click in __Start Program__

![Image_19](https://drive.google.com/uc?id=1z2LLc4lfvvaBa7_WTRAh_Axltc_8MSbp)

So, it will do nothig aparent, but if you got to here without error, its mean that you a ready to run wherever program you want.

[Here](https://github.com/EltonJunior/AURIX_TFT_TC297B/tree/main/02_Blinky_LED) you are going to find the __Blinky_LED__ and how to configure it.
