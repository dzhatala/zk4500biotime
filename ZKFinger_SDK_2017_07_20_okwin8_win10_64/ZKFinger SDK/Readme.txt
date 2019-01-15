   ------------------------------------------------------------------
                             ZKTeco Inc.    

                              Readme File
          
                              July 2013
   ------------------------------------------------------------------
               
          (c) ZKTeco Inc., 2013. All rights reserved



---------
1.CONTENTS
---------

Demo
	Demo.exe, In addition to the registration and identification fingerprint, there are functions for EM/Mifare card.

setup.exe
	Fingerprint Reader Driver setup(Ver 2.3.3.5). It's compatible with all ZKSensor. After installed all the files in the windows system directory.

ZKFinger SDK.pdf
	ZKFinger SDK User Manual.

Samples
	The demo's source code of VC.

----------------
2. CHANGELOG 
----------------
2.3.3.5
	(1) ZK4500/ZK7500/ZK8500 can use in Windows 8 64bit system.
	
2.3.3.4
	(1) Remove 64-bit Patch£¬it's include in setup.exe¡£
	
2.3.3.3
	(1) Solve the problem of after PC sleep&hibernate, still can capture image from fingerprint sensor.
	
2.3.3.2
	(1) Solve the error when ZK8000/ZK8500 control light&beep in ver 2.3.3.1.
	(2) Solve the problem of reading error cardnumber in Demo.
	
2.3.3.1
	(1) Solve the error when dragging Biokey.ocx in VS2010. 
	(2) Solve the error when calling InitEngine() function on some systems in ver 2.3.3.
	
2.3.3
	(1) Support ZK4500/ZK7500/ZK8500 fingerprint sensors.
	
2.3.2
	(1) The range of 10.0 algorithm score is 0-100.
	(2) 10.0 algorithm can set property Threshold(0-100), it's no use in previous version. 1:1 Threshold is recommended to 15, and 1:N Threshold is recommended to 35.

2.3.1	
	(1) Solve the problem of capturing fingerprint image is not stable.
	(2) 10.0 algorithm supports 360 degrees of rotation verification.
	(3) Add property LastQuality as lastest fingerprint quality, and LowestQuality as allowed lowest fingerprint quality. When LastQuality is less than LowestQuality then results insufficient feature points.

2.3.0
	(1) 10.0 algorithm is license-free when ZK fingerprint sensor in the windows operating system above 2000 and U.are.U fingerprint sensor in the windows XP and windows 7 operating system.
	(2) After registered successfully, you can get 9 and 10 algorithm template simultaneously via interface.

----------------
3. Platforms
----------------

(1) ZK4000 fingerprint sensors support Win 8/Win 7/Vista/XP (32/64-bit), Windows Server 2003/2008 (32/64-bit).
(2) U.are.U fingerprint sensors support Win 7/Vista/XP (32/64-bit), Windows Server 2003/2008 (32/64-bit).
(3) ZK6000/ZK7000/ZK8000 fingerprint sensors only support Win 8/Win 7/Vista/XP (32-bit), Windows Server 2003/2008 (32-bit), these fingerprint sensors chip doesn't support 64-bit.
(4) ZK4500/ZK7500/ZK8500 fingerprint sensors support Win 8/Win 7/Vista/XP (32/64-bit), Windows Server 2003/2008 (32/64-bit).

----------------
4. CD NOTES
----------------

We hereby make a promise that the CD together with the goods is stable version, maybe it is not the latest version. In order to meet customer¡¯s requirement, perfect our software and provide customer service in time. We will release the latest software version in our website, so that customer can download easily. Although we spent more effort for strict testing, we are not absolutely sure for its stability. If you have any questions, please contact us by telephone or MSN for assistance. We are not liable for any damages trouble or what else, which are caused by downloading the latest version software.

------------------------
5. SUPPORT AND FEEDBACK
------------------------
 
If you have suggestions for future product releases or require technical support for your product, send e-mail to support@zksoftware.com. 

The ZKSoftware Web site, at http://www.zkteco.com, provides support for registered users as well.

