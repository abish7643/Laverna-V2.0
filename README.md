# Laverna V2 | Line Follower Robot | 3i INC

This project is a follow up of a previous project, [Laverna](https://github.com/abish7643/Laverna). Compared to the previous one, we used a custom 3D printed chassis (Fork of Brandon Makridis's [design](https://www.thingiverse.com/thing:1584316)), invested more into ligher materials & moved to an Arduino Nano for decreasing size and implementing on a breadboard for better modularity.

All turns are independently handled. That means PID is turned off at turns and Laverna uses a simple way of tackling Acute, Obtuse and Right angles.

> We secured a place in top 3 positions for 6 out of
the 8 participated line follower competitions conducted across different colleges in Kerala during 2019-20. Notables ones are NIT Calicut (Tathva 19), College of Engineering Trivandrum (Escape 19) & CDAC (Techfiesta 2K20).

## Images

![Laverna - The Goddess Of Death](https://github.com/abish7643/Laverna-V2.0/tree/master/Pictures/Laverna_LineFollowerBot_1.jpg?raw=true)

![Laverna - The Goddess Of Death](https://github.com/abish7643/Laverna-V2.0/tree/master/Pictures/Laverna_LineFollowerBot_2.jpg?raw=true)


## Prerequisites

1. [Qtrsensor 4.0.0 Library](https://github.com/pololu/qtr-sensors-arduino)
2. [Button](https://www.arduinolibraries.info/libraries/button)

All Libraries are included in the repository, upgrade after trying out the included one.

## Components we used

1. [Polulu QTR-8RC Reflectance Sensor](https://www.pololu.com/product/961)
2. [6V 300RPM Micro Gear Motors](https://robu.in/product/n20-6v-300-rpm-micro-metal-gear-motor/) and [Wheel (x2)](https://robokits.co.in/robot-parts/robot-wheels/rubber-wheels/d-axis-43mm-tracking-rubber-wheel-for-n20-dc-geared-motor)
3. [Polulu Castor Wheel](https://robokits.co.in/robot-parts/castors/3pi-n20-universal-ball-wheel-castor) & [Motor Mounting Brackets](https://robokits.co.in/motors/mounting-clamps/n20-metal-gear-micro-dc-motor-mounting-bracket?cPath=2_592_521&)
4. [L293D Motor Driver - IC Only](https://www.electronicscomp.com/l293d-dual-h-bridge-motor-driver-ic)
5. Printed a Custom Chassis (ABS Plastic - White)
   - [Chassis Source](https://www.thingiverse.com/thing:1584316) (Changed The Design To Accomodate Our Components)
   - [A3DXYZ India](https://a3dxyz.com/) (Printing Costed Approximately 450 INR)
6. Arduino Nano (Select any arduino board with sufficient pins)
7. [LIPO 7.4V 850 mAh](https://robokits.co.in/batteries-chargers/skycell-lipo-battery/7.4v-lipo-batteries-2-cell/lithium-polymer-lipo-rechargeable-battery-7.4v-850mah-25c)
8.  One [Button Switch](https://robu.in/product/12x12x7-3mm-tactile-push-button-switch-round/) and One [Power Switch](https://robu.in/product/spst-rocker-switch-pack-of-3/)

## Authors

Abish Vijayan (https://github.com/abish7643/ | abishvijayan7643@gmail.com)

### Contributers

- Abhijit M (abhimadhu523@gmail.com)
- Adith GM (adithgm14@gmail.com)
- Kaveri TS (tscauvery007@gmail.com)

### License

This project is Open Source, Feel free to do whatever you want & also contact any of us if you have any queries.
