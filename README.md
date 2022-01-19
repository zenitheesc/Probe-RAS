# Probe-RAS
<h1 align="center" style="color:white; background-color:black">Probe-RAS</h1>
<h4 align="center"> Telecommunication board for the Zenith's Stack architecture.</h4>

<p align="center">
	<a href="http://zenith.eesc.usp.br/">
    <img src="https://img.shields.io/badge/Zenith-Embarcados-black?style=for-the-badge"/>
    </a>
    <a href="https://eesc.usp.br/">
    <img src="https://img.shields.io/badge/Linked%20to-EESC--USP-black?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/zenitheesc/Probe-RAS?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/issues">
    <img src="https://img.shields.io/github/issues/zenitheesc/Probe-RAS?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/commits/main">
    <img src="https://img.shields.io/github/commit-activity/m/zenitheesc/Probe-RAS?style=for-the-badge">
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/zenitheesc/Probe-RAS?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/commits/main">
    <img src="https://img.shields.io/github/last-commit/zenitheesc/Probe-RAS?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/issues">
    <img src="https://img.shields.io/github/issues-raw/zenitheesc/Probe-RAS?style=for-the-badge" />
    </a>
    <a href="https://github.com/zenitheesc/Probe-RAS/pulls">
    <img src = "https://img.shields.io/github/issues-pr-raw/zenitheesc/Probe-RAS?style=for-the-badge">
    </a>
</p>

<p align="center">
    <a href="#environment-and-tools">Environment and Tools</a> •
    <a href="#Z-Hub">Z-Hub</a> •
    <a href="#Block-Diagram">Block Diagram</a> •
    <a href="#Schematic">Schematic</a> • 
    <a href="#Board">Board</a>
</p>

## Environment and tools

This board was designed using KiCad 5.1.10.

## Block Diagram

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Diagram.png"/>
</p>

## Z-Hub

This board contains a Stack Connector, with the 2021 Z-Hub pinout.


<table align = "center">
  <thead>
    <tr>
      <th colspan=2>   Z-Hub 2021   </th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>GND</td>
      <td>GND</td>
    </tr>
    <tr>
      <td>GND</td>
      <td>GND</td>
    </tr>
    <tr>
      <td>BAT+</td>
      <td>BAT+</td>
    </tr>
    <tr>
      <td>SOl+</td>
      <td>SOl-</td>
    </tr>
    <tr>
      <td>5V</td>
      <td>5V</td>
    </tr>
    <tr>
      <td>3V3</td>
      <td>3V3</td>
    </tr>
    <tr>
      <td>MISO1</td>
      <td>MOSI1</td>
    </tr>
    <tr>
      <td>SCK1</td>
      <td>CAN_H</td>
    </tr>
    <tr>
      <td>SDA </td>
      <td>CAN_L</td>
    </tr>
    <tr>
      <td>SCL</td>
      <td>CE02</td>
    </tr>
    <tr>
      <td>CE11</td>
      <td>CE12</td>
    </tr>
    <tr>
      <td>SDA1</td>
      <td>SCL1</td>
    </tr>
    <tr>
      <td>SDA2</td>
      <td>SCL2</td>
    </tr>
    <tr>
      <td>TX1</td>
      <td>RX1</td>
    </tr>
    <tr>
      <td>TX2</td>
      <td>RX2</td>
    </tr>
    <tr>
      <td>DIG1</td>
      <td>DIG6</td>
    </tr>
    <tr>
      <td>ALRT1</td>
      <td>/CHRG</td>
    </tr>
    <tr>
      <td>PWM</td>
      <td>DIG8</td>
    </tr>
    <tr>
      <td>/FAULT</td>
      <td>DIG9</td>
    </tr>
    <tr>
      <td>DIG5</td>
      <td>DIG10</td>
    </tr>
  </tbody>
</table>

## Schematic

The design was separated in hierarchical sheets to accommodate all components in an orderly way.

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Schematic_Page_1.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Schematic_Page_2.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Schematic_Page_3.png"/>
</p>


## Board

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Top.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Bottom.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Probe-RAS/blob/main/Other_Files/Images/Perspective.png"/>
</p>


---

<p align="center">
    <a href="http://zenith.eesc.usp.br">
    <img src="https://img.shields.io/badge/Check%20out-Zenith's Oficial Website-black?style=for-the-badge" />
    </a> 
    <a href="https://www.facebook.com/zenitheesc">
    <img src="https://img.shields.io/badge/Like%20us%20on-facebook-blue?style=for-the-badge"/>
    </a> 
    <a href="https://www.instagram.com/zenith_eesc/">
    <img src="https://img.shields.io/badge/Follow%20us%20on-Instagram-red?style=for-the-badge"/>
    </a>

</p>
<p align = "center">
<a href="zenith.eesc@gmail.com">zenith.eesc@gmail.com</a>
</p>
