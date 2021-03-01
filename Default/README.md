# AURIX Default Template

This tutorial will guide you how to prepare the HighTec IDE to develepor project using AURIX™ Family – TC29xT, Infineon iLLD, the idea is help to create project that will share other project togheter e.g. FreeRTOS.

## Introdution

Which IDE has its methon to create, start and configuration project, the HighTec isn't different, so, to make easy your development use the HighTec IDE, I already done a default project that you can get it [Here](@). below I am going to discrible how to import and compile it. Go aread and get the project and help yourself.

### Import a Default Project into HighTec IDE

If you didn't make any project yet, don't freak out, I'm going to start a project from Zero. below you can see the HighTec when it was execute in the first time. In this windows you just need to close the welcome.

<img Src="https://drive.google.com/uc?id=1RKJtaL_qxT9ddeuU-ea5m9QmqW68F7on"  alt="">

So, Before we done something in the HighTec IDE, we need to clone the **Default** project that should be found [Here](C:\AURIX_TFT_Board\Default). and put it in the Workapace, if you don't know how to do it, look at [How to Clone a Repository on Github](https://www.wikihow.com/Clone-a-Repository-on-Github#:~:text=Enter%20%E2%80%9Cgit%20clone%E2%80%9D%20followed%20by%20the%20source%20location,type%20out%20the%20source%20location%20after%20the%20command.). Now you can close the Welcome windows, it will became this new windows in below image.

<img  Src=" https://drive.google.com/uc?id=1XDlehlOzTXx9MYZ_aU8ZruZ7leYvQwrZ"  alt="">

In this new windows, we're going to import our **Default** project, to import it, click in __File__ -> __Import__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[File]--> B[Import]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1U285IpwpwuTY1gjxVG-AkTiYkJS4QubX " alt="" >
</td>
</tr>
</table>

It will open a new windows, expand __General__ and select __Existing projects into Workspace__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[General]--> B[Existing projects into Workspace]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1jBIW1vm510gRf5DPbRu0KMx4Cr-jjKnS"
alt="">
</td>
</tr>
</table>

It will open a new windows, here you need to __Browser__ to Workspace and select the Workspace folder after that click __Finish__.

<img  Src="https://drive.google.com/uc?id=1EjzMOBSYmgk0EDJFVhF3q1wIk4tzzZ8_"
alt="" >

Done, we've finished the import of our default project and below you can see the final work.

<img  Src="https://drive.google.com/uc?id=1VVjh3RvpZ9x-kMoMBtSSFiz9GbuvmVUV"
alt="" >

Now it is possible to compile it. To do it move __Active Build Connfiguration__ to __Debug__, to do this __Right Click__ on __Default Project__ and go thoughout __Builg Configuration__ -> __Set Active__ -> __Debug__ below you can see the final work.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[Default Project]-->
B[Builg Configuration]-->
C[Set Active]-->
D[Debug]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=13sOtGdhNYozAop3rkG3E-QqG4f2jmvK_ "
alt="">
</td>
</tr>
</table>

## Build the Default Project

Yes, You got it. Now __Right Click__ on __Default Project__ and click in __Build Project__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[Default Project]-->
B[Build Project]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1MhQRaA7aP8iKnjWzPu10JIANtNyxtlPK"
alt="">
</td>
</tr>
</table>

It will start to build the project and you can follow it looking at __Console__.

<img  Src="https://drive.google.com/uc?id=1LwhDXALCD4A9K7xoGV1N8-2-9SJh5wBp"
alt="">

YEP! we've done our import.

<img  Src="https://drive.google.com/uc?id=1kWH1f_5xkjzxLmzBu3JWUGIa8gp40qce"  alt="">

we are going to use it to get the files inside the project or we can use it and only rename the project and import again.

## Debug the Default Project

Now it is time to debbuge and test our project in the Board. With Board pluged on PC. __Right Click__ on __Default Project__ and go throughout __Debug As -> Debug Configurations..__

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[Default Project]-->
B[Debug As]-->
C[Debug Configurations..]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1yOnifPKhR7OdLniED2e17Z3RS-3aEtMC"
alt="" >
</td>
</tr>
</table>


In the new windows, doble click in __Universal Debug Engine__

<img  Src="https://drive.google.com/uc?id=1_gUsJxdwCkIs604Hdy3qxzNUO0xQx_JJ"
alt="">

In the new windows, in __Project:__ click in __Browser__ and Choice the __Default Project__ and click __OK__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[Project:]-->
B[Browser]-->
C[Default Project]-->
D[OK]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1QbleqlNZhYD-LleqFNl0rt0X63MgYz1y"
alt="" >
</td>
</tr>
</table>

In the new windows, in __C/C++ Application:__ click in __Browser__ open __Debug__ path and Choice the __Default.elf__ and click __Open__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[C/C++ Application:]-->
B[Browser]-->
C[Debug]-->
D[Default.elf]-->
E[Open]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1AfIAJytd3poeuy_ThYgbwOP5Yd7lrIDn"
alt="">
</td>
</tr>
</table>

Now select __UDE Startup__ and in __Select UDE Target Configuratioin File:__ click in __Browse Configuration__ it will open a new windows click in __New__ select __Use a default target configuration__ and expand __TriCore -> Infineon -> TC297B Application kit__ and choice __Application Kit with TC297T B-Step (Multicore Configuration)__ and click on __conclud__, choice a place in the computer and save it.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[UDE Startup]-->
B[Select UDE Target Configuratioin File:]-->
C[Browse Configuration]-->
D[New]-->
E[Use a default target configuration]-->
F[TriCore]-->
G[Infineon]-->
H[TC297B Application kit]-->
I[Application Kit with TC297T B-Step Multicore Configuration]-->
J[Conclud]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1o6ISLy1WdY6sSkkXWTqP80bPhsq1KC3f"
alt="">
</td>
</tr>
</table>

after those steps we will have the target to run the code into. click in __OK__

<img  Src="https://drive.google.com/uc?id=1OQGXNlf-BkVHMBJOsvuz1ANl17HznCNV"
alt="" >

click in __Apply__ and in __Debug__

<img  Src="https://drive.google.com/uc?id=151Eitj-7b7LrylC6Ydb_YP2ABkiJHLuJ"
alt=""
width="700px"
height="500px"  >

it will start __Launching Default Debug__

<img  Src="https://drive.google.com/uc?id=1idkpEj_PZiHoAPmw0FXTQibrkHpJuy3q"
alt="" >

After finished the Launching, it will open a new windows, click __Program__ it will open a new windows and fhash the prongram into board after finished click in __Exit__ and __Exit__.

<table  style="width:200%"  id="t01">
<tr>
<td>
<div  class="mermaid">
graph TD
A[Program]-->
B[Exit]-->
C[Exit]
</div>
</td>
<td>
<img  Src="https://drive.google.com/uc?id=1t0N2TR0Z74HtkwCEsuwlrLLihXvAfpeX"
alt=""
width="700px"
height="500px"  >
</td>
</tr>
</table>

To run the program click in __Start Program__

<img  Src="https://drive.google.com/uc?id=1z2LLc4lfvvaBa7_WTRAh_Axltc_8MSbp"
alt="">

So, it will do nothig aparent, but if you got to here without error, its mean that you a ready to run wherever program you want.

[Here](@) you are going to find the __Blinky_LED__ and how to configure it.