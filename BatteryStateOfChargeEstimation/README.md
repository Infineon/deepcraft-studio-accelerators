# Overview - Battery State of Charge Estimation

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

A Battery Management System (BMS) is a crucial component in any xEV, responsible for monitoring, protecting, and optimizing battery performance.

Battery State Estimation Algorithms lie at the core of the BMS. These algorithms compute battery states, which are essential for monitoring and controlling the battery system, as well as providing feedback to the operator.

This project is an example for **Li‑ion battery state estimation** using a **multilayer perceptron (MLP)** neural network. We estimate battery **State of Charge (SoC)**. It represents the amount of electrical charge currently stored in a battery relative to its maximum capacity, expressed on a 0–1 scale. An open source dataset for LG 18650HG2 3.6V 3000 mAh Li‑ion battery from [1] is used to train and validate the model.

About the Neural Network:
- Inputs: voltage, current, temperature, average voltage (last 500 seconds) and average current (last 500 seconds)
- Output: State of Charge (SOC)

## Contents

`Data` 	- Folder where the data is.		 

`Models` - Folder where the trained model, its predictions and generated edge code are saved.

## Sensor(s) & Data

The model uses voltage, current, temperature, and short-term averages of voltage and current from Li-ion cell measurements (LG 18650HG2 open-source dataset cited below).

## Adding More Data

Expand the dataset with other manufacturers, chemistries, and charge/discharge profiles. Keep the same feature format (voltage, current, temperature, and averages) and split new sessions so the Test set stays unseen.

## Steps to Production

Below are some points to expand and improve the topic further:
- Expanding the dataset: include a wider range of manufacturers, operating conditions, and possibly chemistries. Additionaly, use data augmentation to increase the training data. Finally, incorporating different charging/discharging profiles is essential to replicate real world conditions.
- Experimenting with different length for the window used to calculate the average voltage, and the average current. Also, experimenting with adding multiple time windows instead of one, for example to capture short, and medium-term patterns separately.

## Attributions & Citations

<a id="1">[1]</a>
Kollmeyer, Philip; Vidal, Carlos; Naguib, Mina; Skells, Michael  (2020), “LG 18650HG2 Li-ion Battery Data and Example Deep Neural Network xEV SOC Estimator Script”, Mendeley Data, V3, doi: 10.17632/cp3473x7xv.3

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
