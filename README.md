# ⏰ Arduino Alarm Clock  

This project is an **Arduino-based alarm clock**, inspired by [this project](https://projecthub.arduino.cc/tittiamo68/alarm-clock-057133). The main modification is replacing the **20x4 LCD** with a **16x2 LCD**, making the design more compact while maintaining full functionality.  

## 🛠️ Features  
- 🕰️ **Real-time clock (RTC)** for accurate timekeeping  
- 🔔 **Alarm function** with buzzer notification  
- 📺 **16x2 LCD display** to show time and alarm status  
- 🎛️ **Button controls** for setting time and alarm  

## 🔧 Components Used  
| Component | Description |  
|-----------|------------|  
| Arduino UNO | Microcontroller board |  
| LCD 16x2 | Display for time and alarm status |  
| DS3231 RTC Module | Real-time clock for accurate timekeeping |  
| Buzzer | Alarm sound output |  
| Push Buttons | Used to set time and alarm |   

## 🔌 Circuit Diagram  
Below is the wiring diagram for the system:  

<p align="center">
  <img src="https://github.com/user-attachments/assets/c6845b8e-47e6-4d4d-9879-bc1f9e4c589d" width="450">
</p>

 

## 📜 How It Works  
1. The **DS3231 RTC module** keeps track of the time.  
2. The **16x2 LCD** displays the current time and alarm status.  
3. **Buttons** are used to set the time and alarm.  
4. When the alarm time is reached, the **buzzer** sounds.  
