# AURIX Basic Template 
This tutorial will guide you how to prepare the High Tec IDE to develepor project using  AURIX™ Family – TC29xT, Infineon iLLD, the idea is help to create project that will share other project togheter e.g. FreeRTOS.

## Introdution

AURIX™ TriCore™ unites the elements of a RISC processor core, a microcontroller and a DSP in one single MCU. TriCore™-based products target a large variety of automotive application. These include the control of combustion engines, **electrical and hybrid vehicles**, **transmission control units** , **chassis domains**, **braking systems**, **electric power steering systems**, **airbags**, connectivity and **advanced driver assistance systems** to support the trend toward autonomous, clean and connected cars. The AURIX™ family delivers also the versatility required for the **industrial sector**, excelling in optimized **motor control** applications and signal processing.

<table style="width:200%" id="t01">  
<tr><th>Key features</th></tr>  
<tr> <td>
- Triple TriCore with 300MHz / DSP functionality
<br> - Up to 8 MB Flash w/ ECC protection
<br> - 128 KB EEPROM at 500 k cycles
<br> - Up to 728 KB RAM w/ ECC protection
<br> - <b>128x </b> [DMA] channels
<br> - <b>3x </b>  Delta-Sigma ADC converters
<br> - <b>4x </b>  12bit SAR ADC converter
<br> - Sensor interfaces :  
<blockquote>
 <b>15x </b> SENT; <br>
 <b>5x </b> PSI5 sensor interfaces.
</blockquote>
 -   State of the art connectivity: 
 <blockquote>
Ethernet 100Mbit;<br>
<b>2x </b>FlexRay;<br>
<b>4x </b>ASCLIN;<br>
<b>6x </b>QSPI;<br>
<b>2x </b>I²C;<br>
<b>15x </b>SENT;<br>
<b>3x </b>MSC;<br>
<b>1x </b>HSS;<br>
<b>1x </b>I²S emulation.<br>
</blockquote>
-  Programmable [HSM] (Hardware Security Module) <br>
-  Single voltage supply 5V or 3.3V<br>
-  [LFBGA-292 package]<br>
-  BGA-416 package <br>
- [LFBGA-516 package] <br>
- Ambient Temperaure range -40°...+150°<br>
	    </td>  
	<td color="#FFFFFF"><img width="400px" height="400px" Src="C:\AURIX_TFT_Board\img\Aurix_Tricore_Chip.png" alt=""> </td>  
	</tr>  
</table>

## Pré-Requirement
In order to perform this AURIX Basic Template it will need to use the **HighTec Free TriCore™ Entry Tool Chain** that you can donwload it [Here](https://free-entry-toolchain.hightec-rt.com/). You only need to make a register and than download it. to Install the IDE in the ease way you can use the [AURIX™ TC3xx - Free Entry Tool Chain](https://free-entry-toolchain.hightec-rt.com/gettingstarted.pdf?d=20190812) documentation. after this installation you can rigth to start.

## Make a blank project
Hey, if you go here, congratulation, I assume that you got to install the HighTec IDE and alredy run the example that is explane inside the [AURIX™ TC3xx - Free Entry Tool Chain](https://free-entry-toolchain.hightec-rt.com/gettingstarted.pdf?d=20190812). So let's get started.

### knowing the IDE
If you didn't make any project yet, don't freak out, I'm going to start a project from Zero. below you can see the HighTec when it was execute in the first time.


<table style="width:200%" id="t01">   
<tr> 	  
	<td><img width="600px" height="400px" Src="C:\AURIX_TFT_Board\img\hightec_0.png" alt=""></td>  
	<td> In this windows you just need to close the welcome.</td>
</tr>  
</table>

So, Before we done something in the HighTec IDE, we need to clone the **Default** project that should be found [Here](C:\AURIX_TFT_Board\Default). and put it in the Workapace, if you don't know how to do it, look at [How to Clone a Repository on Github](https://www.wikihow.com/Clone-a-Repository-on-Github#:~:text=Enter%20%E2%80%9Cgit%20clone%E2%80%9D%20followed%20by%20the%20source%20location,type%20out%20the%20source%20location%20after%20the%20command.). Now you can close the Welcome windows, it will became this new windows in below image.


<img Src="C:\AURIX_TFT_Board\img\hightec_1.png" alt="">

In this new windows, we're going to import our **Default** project, to import it, click in __File__ -> __Import__.


<table style="width:200%" id="t01">   
	<tr>
		<td> 
			<div class="mermaid">
				graph TD
				A[File]--> B[Import]
			</div>
		</td> 	  
		<td>
			<img width="700px" height="500px" Src="C:\AURIX_TFT_Board\img\hightec_2.png" alt="">
		</td> 
	</tr>  
</table>

It will open a new windows, expand __General__ and select __Existing projects into Workspace__.

<table style="width:200%" id="t01">   
	<tr>
		<td> 
			<div class="mermaid">
				graph TD 
				A[General]--> B[Existing projects into Workspace]
			</div>
		</td> 	  
		<td>
			<img width="700px" height="500px" Src="C:\AURIX_TFT_Board\img\hightec_3.png" alt="">
		</td> 
	</tr>  
</table>

it will open a new windows, here you need to __Browser__ to Workspace and select the Workspace folder after that click __Finish__.

<img width="700px" height="500px" Src="C:\AURIX_TFT_Board\img\hightec_4.png" alt="">

Done, we've finished the import of our default project, to compile it move __Active Build Connfiguration__ to __Debug__ below you can see the final work.

<table style="width:200%" id="t01">   
	<tr>
		<td> 
			<div class="mermaid">
				graph TD 
				A[General]--> B[Existing projects into Workspace]
			</div>
		</td> 	  
		<td>
			<img width="700px" height="500px" Src="C:\AURIX_TFT_Board\img\hightec_7.png" alt="">
		</td> 
	</tr>  
</table>

<img width="700px" height="500px" Src="C:\AURIX_TFT_Board\img\hightec_6.png" alt="">

we are going to use it to get the files inside the project and use it. 

[Here](@) you are going to find the Blinky_Led and how to configure it.

