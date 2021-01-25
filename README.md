# jamSholat
بسم الله الرحمن الرحيم  

Project jam sholat untuk led modul P4.75 dengan menggunakan board berbasis STM32, free to share!

Note: 
Project ini didedikasikan sepenuhnya untuk keperluan amal, silakan memanfaatkan, menyebarkan, dan mengembangkannya. 
Adapun jika anda berniat untuk memanfaatkannya untuk keperluan komersial, harap sisihkan keuntungannya untuk pengembangan lebih lanjut lalu sebarkan ulang pengetahuan tersebut, semoga saja keuntungan yang didapat tidak berhenti hingga rupiah yang terkumpul. tetapi ada keuntungan akhirat yang juga ikut kita tabung.. 


Project ini terdiri dari 3 bagian hardware, software, dan tools
***
## Hardware
Mikrokontroller core yang dipakai adalah varian dari STM32 Bluepill atau Blackpill(belom tested).
Saya biasa memakai varian STM32F103C8T6 dengan papan berwarna biru. 
![](/PCB/Digital_Praytime_Display_P4.75_v0.9.png)

Dalam kontroler board utama (file: Digital_Praytime_Display_P4.75_v0.9.brd) terdiri dari:
* soket mikrokontroler
* soket untuk HUB08
* soket baterai RTC 
* interface untuk rotary encoder
* interface untuk serial
* interface untuk buzzer
* terminal power

![](/PCB/External_Battery.png)
![](/PCB/Encoder.png)

Pada board eksternal (file: External_Battery.brd dan Encoder.brd) terdiri dari:
* soket baterai 
* tombol rotary encoder
board eksternal berfungsi sebagai papan expansi untuk jam sholat yang menggunakan frame tertutup, sehingga board ini bisa diakses diluar 


## Software
Software yang dipakai adalah arduino dengan menggunakan tambahan *hardware* STM32 dari [Arduino STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32). Untuk library saya memakai HUB08 dan RTClock. 
