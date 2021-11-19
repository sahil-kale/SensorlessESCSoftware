# SensorlessESCSoftware

I like making motors spin! I decided to make a custom sensorless BLDC motor controller.

## Commentary
- A standard RC servo PWM control interface is employed (1000-2000us Duty Cycle, 50Hz) to control the BLDC motor to make it usable in RC drones and cars
- I opted to make the BackEMF Zero-Sensing with an external comparator to simplify the code. Additionally, it would make the software easier for a sensored ESC
- Due to chip shortage, the pins were broken out and a nucleo was used instead.

## Schematic
![image](https://user-images.githubusercontent.com/32375512/142559879-6bcc972d-e7d7-4192-b4b5-bf94f3be7d23.png)
![image](https://user-images.githubusercontent.com/32375512/142559903-1e754333-308f-49bd-9c56-6b7a22ce56b6.png)

## Photo:
