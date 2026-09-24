# Adaptive Polymorphic Honeypot (APH)

A low-cost cybersecurity device that changes its identity every 10 seconds to confuse hackers and protect small networks.

## What It Does
- Acts as a fake shop (honeypot) to attract attackers
- Changes identity every 10 seconds (Moving Target Defense)
- Detects scans, sounds alarm, and logs attacks
- Blocks attacker IPs

## Hardware Used
- Lolin NodeMCU (Decoy)
- 2x Amica NodeMCU (Detector + Firewall)
- Arduino Uno (Alarm Controller)
- Buzzer, LED, Power Bank

## How to Use
1. Upload code to each board
2. Power all boards
3. Connect tablet to Wi-Fi "APH-Decoy"
4. Open 192.168.4.1/dashboard

## Mathematical Model
S(t+1) = f(S(t), R)
P_success = (1/10)^5 = 0.001%

## Project Report
See `docs/report.pdf` for full documentation.

## Author
Bharat Dashrath Patil
Class XII SCI | St. Francis of Assisi Convent High School, Navsari
Academic Year: 2026-27