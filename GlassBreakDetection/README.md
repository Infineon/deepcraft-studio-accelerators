# Glass Break Detection

## Overview

This machine learning project focuses on developing a glass break detection model that can accurately identify glass break events by analyzing audio signals.
Such models play a critical role in modern security infrastructures, where they enhance situational awareness and enable rapid response.

Glass break detection can be deployed across diverse environments:

- Home security systems: safeguarding families and property against intrusions.

- Commercial and retail buildings: protecting assets and ensuring customer safety.

- Vehicles: detecting accidents or break-ins to trigger immediate alerts and safety measures.

By combining audio signal processing with machine learning the model provides accurate event classification, minimizes false alarms, 
and supports intelligent safety and security management across multiple domains. This model enhances the reliability of traditional alarm systems while also serving as a foundation for advanced IoT‑based security solutions that intelligently adapt to different environments and conditions.
## Contents

`Data`   - Folder containing the glass break audio wav files used in this project.

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

## Collection of Data
The data for this project was primarily collected from the Freesound site, with careful verification of licensing to ensure proper eligibility for use in model training. Infineon also contributed the data providing samples that strengthen 
the reliability and diversity of the training set. All audio recordings in the dataset have a sampling frequency of 48 kHz, ensuring consistency and high-resolution quality for signal analysis and model training.


## Adding More Data
The project currently includes 369 audio WAV files, forming the foundation for model training. While this provides a solid starting point, additional recordings are needed to broaden coverage. 
In particular, expanding the dataset with more diverse glass break samples as well as recordings captured under noisier conditions and varying distances will help improve the model’s robustness and generalization to real-world environments. 
Deepcraft Studio provides a streamlined environment for recording glass break audio samples and offers integrated tools for labeling and preprocessing, ensuring that data preparation is both efficient and consistent. While studio recordings offer clean baseline samples, they should be complemented with field recordings 
or augmented with synthetic noise to ensure the model performs reliably in real-world scenarios.

## Steps to Production
The recommended path to production for a glass break detection model begins with clearly defining the environments and glass types you want the 
system to handle such as residential windows, retail storefronts, or automotive glass. Once the scope is set, data collection should be performed 
across diverse scenarios ensuring coverage of different glass materials, break mechanisms, microphone placements, and acoustic conditions so the 
model learns to remain robust under varying circumstances. To further increase variability, data augmentation techniques such as adding background 
noise, pitch shifting or time stretching can be applied. All recordings should be standardized to a consistent sampling frequency such as 48 kHz and 
preprocessed to remove noise and extract meaningful features. It is also essential to maintain a strict separation between Train, Validation, 
and Test sets, with the Test set containing unseen data that reflects diverse scenarios. Negative data, such as recordings of similar but non‑glass 
sounds, should be included to reduce false alarms and strengthen reliability. After training, the model must be 
evaluated in real‑world conditions to identify weaknesses. If performance drops in specific environments, adding representative data from those 
contexts is often the most effective way to improve robustness. This iterative cycle of data expansion, parameter tuning, and scenario testing 
ensures the final model is production‑ready, delivering accurate detection and seamless integration into security systems.