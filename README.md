# IoT-Based-Password-Typist (Unlocking PC remotely)  

This project is under the Course No : CSE 3152  
Course Title : Microprocessor & Embedded Systems Sessionall  
Date: 10-04-2023  

The project is Supervised by  
Atanu Shome  
Assistant Professor  
Computer Science & Engineering Discipline, Khulna University  
Khulna University,  Khulna, Bangladesh.  

Project by,
Sheyum Hossain,  Mridul Paul,  Fatima Rahman  
Electronics and Communication Engineering Discipline,   
Khulan University, Khulna  

# Objectives:  
1. Design and build a microcontroller and IoT-based system that can remotely turn on a
computer.
2. Develop a password input system that can be controlled by the microcontroller.

# Introduction  
Nowadays sudden power loss becomes a regular phenomenon that hampers the
continuous use of computers remotely. Another issue that hampers is screen lock. Since this
device is IoT based, it can power on the PC using mechanical push and using USB data
connectivity it can unlock the pc by giving password command at any time. An application can
monitor its status. The instruments are available and uses low power.

# Project Figure  
![337614417_936621794246845_2044728132786000688_n](https://github.com/user-attachments/assets/8df01ea4-ab55-4688-9d51-8f9458b6bb81)
![337686032_756509885970590_7949252064440105539_n](https://github.com/user-attachments/assets/e55b2b84-3e4c-46a7-af8b-5699c9383162)

# This project is an integrated system that involves three main components:

1. Arduino UNO as an HID Device:
- The Arduino UNO is programmed to act as a Human Interface Device (HID). It emulates a keyboard and communicates directly with the computer. When the system receives a password from the user, the Arduino inputs this password as if it were typed on a keyboard.  
- This is useful for situations where an automated or remote password entry is needed without manually typing.


2. ESP32 Development Board for Communication:  
-The ESP32 serves as a bridge between the computer and the database. It communicates wirelessly with a cloud-based database (such as Firebase) to receive and store passwords.  
- The ESP32 retrieves the password from the cloud, processes it, and sends it over a serial communication channel to the Arduino UNO. It is capable of handling both the communication and storage of password information, ensuring that passwords are securely stored and can be updated when necessary.  

3. PC Remote App for Control:  
- The PC Remote App is used by the user to control the entire system remotely. The app allows the user to send a password to the cloud-based database.  
- Once the password is in the database (e.g., Firebase), the ESP32 retrieves it and sends it to the Arduino board. The Arduino then emulates typing the password into the PC, enabling remote control without direct physical access to the computer.

 # System Workflow:
1. The user enters a password using the PC Remote App.  

2. The app pushes this password into a cloud database (like Firebase).  

3. The ESP32 fetches the password from the cloud and sends it to the Arduino UNO via serial communication.  

4. The Arduino UNO emulates a keyboard input, typing the password on the connected PC.  

This project is a useful combination of hardware and software that allows for remote password management and input, potentially for secure login systems or automated systems requiring authentication.  
