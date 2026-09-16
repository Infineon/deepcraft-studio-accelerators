# Arc Fault Detection

This project is designed to work exclusively with DEEPCRAFT™ Studio. Download it from [here](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)

## Overview - Use-Case

Electrical faults are a well-documented cause of residential fires. In China, electrical fires accounted for 33.7% of all fire incidents between 2008 and 2012, and arc faults were responsible for 63.9% of those electrical fires [[1]](#citations). In the United States, an estimated 45,210 home structure fires per year (2010–2014) involved electrical failure or malfunction; when the specific failure type could be identified, some form of arcing was the most common mechanism [[2]](#citations).

This project trains a model to detect arc faults from appliance current waveforms. Current is recorded with an oscilloscope and provided here at 200 kHz. Data from other oscilloscopes can be used if it is downsampled to the same rate. The resulting model is intended for real-time arc fault detection.

- **Problem:** Real-time detection of series and related arc faults in AC loads from a current waveform
- **Machine learning method:** CNN binary classification (arc vs. no arc)
- **Sensor and data:** Oscilloscope with a Hall-effect current probe (rated bandwidth DC–100 kHz); original sampling rate 50 MHz, downsampled to 200 kHz
- **Relevance:** Rapid CNN-based detection for built-in arc-fault monitoring in residential and appliance electrical products, helping reduce fire risk that conventional over-current protection may miss

## Contents

**`Data`** — Downsampled 200 kHz current recordings and labels, grouped by class (`arc_fault` and `no_arc_fault`)

**`Models`** — Folder where the trained DEEPCRAFT™ model, predictions, and generated Edge code are saved

**`Resources`** — [`original_names.csv`](Resources/original_names.csv) and [`new_names.csv`](Resources/new_names.csv) for arc-test name mapping, plus photographs of the arcing setup and load simulator in `Resources/Images/`

## Sensor(s) & Data

Current is measured with an oscilloscope and a Hall-effect current probe (rated bandwidth DC–100 kHz). Recordings were originally sampled at 50 MHz and are supplied in this project at 200 kHz.

Recordings in the project use the class labels `arc_fault` and `no_arc_fault`.

**Oscilloscope**

![Arcing Setup](Resources/Images/arcing-setup.jpg)

**Load simulator**

![Resistor Box](Resources/Images/resistor_box_and_inductor.png)

### Arc-fault collection (KTH)

Arc faults were simulated at [KTH](#citations) (Kungliga Tekniska högskolan) University (Stockholm) in a controlled laboratory environment. Sockets of different types and commercial brands were connected to a range of loads:

- Resistive (R)
- Resistive–inductive (RL)
- Resistive–capacitive (RC)
- Computer
- Two types of drill
- Industrial vacuum cleaner

Tests used both solid single-core wire and multi-strand wire.

In this project those recordings live under `Data/arc_fault/data-arctests/` (arc) and `Data/no_arc_fault/data-arctests/` (no arc from the same campaign). Original source files: [data-arctests](https://gnu.eecs.kth.se/nt/tmp/y/data-arctests/). Use [`Resources/new_names.csv`](Resources/new_names.csv) to match a session folder to its index, and [`Resources/original_names.csv`](Resources/original_names.csv) for the lab capture name. The original names carry extra setup detail that the shortened folder names omit, including the **type of socket** used for that measurement (for example ABB, Eljo, long socket, short socket) as well as wire, load, and whether an arc was induced.

### Non-arc appliance measurements (KTH)

The dataset also includes **non-arc** current recordings from the same KTH laboratory campaign. These were measured with an oscilloscope on a wide range of appliances (no arc induced), so the model can learn the difference between normal load current and an arc fault.

In this project they are stored under `Data/no_arc_fault/data-applnonarc/` (1220 sessions). Folder names follow the appliance capture (for example `waterheater_tesy_30L_06`). Original non-arc CSV files: [data-applnonarc](https://gnu.eecs.kth.se/nt/tmp/y/data-applnonarc/). Appliance types include:

- adapters (ADSL router; mosquito catcher)
- air compressor
- Fender Champion 40 amplifier
- AEG WS8-125S angle grinder
- car battery chargers (including an older 6 A unit)
- Ryobi RCS1935 chainsaw
- Ryobi RSH2845T chopper
- ICA coffee machine
- computers (Dell OptiPlex 760, Dell OptiPlex 990 desktop, 6-disk server)
- cooker / fan oven
- TEM EE15 dimmer with LED load
- drill charger and Cotech 810 W drill
- electric blanket (60 W)
- Belling 2 kW electric fire
- fan heaters (Dimplex 3 kW; 2 kW wall-mount)
- fans (50 W floor-standing; 30 W table)
- 30 W LED floodlight
- Philips food mixer
- Bosch fridge-freezer
- electronically controlled 800 W heater
- Qlima SJA2518 / SJA2519 air-to-air heat pumps
- Hamron 450 W impact wrench
- Ryobi RJS750 jigsaw
- RHB 3 kW kettle
- lamps: incandescent, LED, fluorescent (electronic and magnetic ballast), and several dimmer models (400821, TEM-EE15, TEM-EE19, VFR200M)
- laptop chargers (Dell 65 W; HP 65 W travel; HP 90 W)
- ICA microwave
- Philips and Samsung monitors
- mower
- HPS plant lights (400 W magnetic ballast; 600 W electronic)
- printer
- 260 W delta sander
- 4-slot sandwich toaster
- soldering iron
- Ryobi RLT3525 strimmer
- Tesco 2-slot and 4-slot toasters
- Samsung TV
- UPS units (APC CS350; Eaton 3S 550)
- 4-port USB charger
- Miele S2 1600 W vacuum cleaner
- Elva 700 W waffle iron
- Tesy 30 L water heater

The data from these appliances covered different operating variants such as startup, speed change, or varied supply voltage.

The original untransformed recordings, scripts that convert the raw `.isf` oscilloscope files, and other accompanying material are available [here](https://gnu.eecs.kth.se/nt/tmp/y/).

### Data specifications

Each session is cut from a **random starting point** in the original source file, and the timestamp track is always reset so that **time begins at zero**. That avoids a spurious correlation between the arc / non-arc label and incidental file details such as sample rate, time offset, or where the snippet sat in the long recording.

**Input features (`data.data`)**

| Field | Description |
| --- | --- |
| `t` | Timestamp (seconds) |
| `i` | Current measured by the oscilloscope |

**Target variable (`label.label`)**

| Field | Description |
| --- | --- |
| `Time` | Timestamp of the beginning of the label (seconds) |
| `Length` | Duration of the label (seconds) |
| `Label` | `arc_fault` or `no_arc_fault` |
| `Comment` | Optional notes for the sample |

**Sampling**

- Original sampling rate: 50 MHz
- Sampling rate of the provided data: 200 kHz

**Files**

- **1496** paired sessions in total (`.data` input + `.label` target)
- **178** sessions labelled `arc_fault` in `Data/arc_fault/data-arctests/`
- **1318** sessions labelled `no_arc_fault`:
  - **98** in `Data/no_arc_fault/data-arctests/` (lab loads without an induced arc)
  - **1220** in `Data/no_arc_fault/data-applnonarc/` (appliances)
- Format: CSV-style `.data` (input) and `.label` (target) files

### Data attribution

The measurements were gathered by N. Taylor and Y. Jiang at Kungliga Tekniska högskolan (KTH) [[3]](#citations). Use of this accelerator through DEEPCRAFT™ Studio is subject to Infineon’s [Studio terms and conditions](https://developer.imagimob.com/legal/studio-terms-and-conditions). For commercial use of the underlying KTH recordings beyond that, confirm the licence and conditions with the data authors and the source repository at [gnu.eecs.kth.se](https://gnu.eecs.kth.se/nt/tmp/y/).

## Adding More Data

Expand the dataset with additional current waveforms that match this project’s format (single current channel at **200 kHz**, labels `arc_fault` / `no_arc_fault`). Place new sessions under `Data/arc_fault/` or `Data/no_arc_fault/` so the folder class matches the label.

**How to collect**

- Repeat the KTH-style setup: Hall-effect current probe on an oscilloscope, then downsample to 200 kHz. New files from other oscilloscopes are usable if they are brought to the same rate.
- Capture a wider set of **environments, devices, sockets, brands, wiring** (solid and multi-strand), **loads**, and **operating patterns** (startup, shutdown, speed changes, dimming, voltage variation).
- Add more **positive (`arc_fault`)** cases: induced arcs on additional socket types, wire types, and loads. The current split is 178 `arc_fault` vs. 1318 `no_arc_fault` sessions.
- Add more **negative (`no_arc_fault`)** cases from appliances that look electrically “noisy” (motors, dimmers, switch-mode supplies) so the model does not confuse them with arcs. Put appliance sessions under `Data/no_arc_fault/data-applnonarc/`.
- Import extra source files from [data-arctests](https://gnu.eecs.kth.se/nt/tmp/y/data-arctests/) and [data-applnonarc](https://gnu.eecs.kth.se/nt/tmp/y/data-applnonarc/) after conversion, or record new sessions on Infineon hardware with a current-sensing front end and bring them into Studio (for example via [Graph UX / bring-your-own-data](https://developer.imagimob.com/deepcraft-studio/data-preparation/data-collection/bring-your-data/bring-your-own-data)).



## Steps to Production

Bring this classifier from a lab accelerator to a product by reducing missed arcs (false negatives) and nuisance trips (false positives), then deploying a small, fast model on the edge.

**Increase data variability**

- Current status: 1496 sessions (178 `arc_fault` in `data-arctests`, 1318 `no_arc_fault` from `data-arctests` plus `data-applnonarc`) recorded at KTH.
- Collect data from additional appliances, sockets, and wiring to cover device-to-device variation.
- Record further arc-fault scenarios so the positive class is less under-represented.
- Prefer real transients (startup, shutdown, load steps) over only steady-state current.

**Train / validation / test split**

- Keep the **test set** off sessions that appear in train or validation.
- Put both arc and non-arc examples in the test set, including appliances and operating modes that were not used in training, so you can check generalization.

**Negative data and robustness**

- Keep a large non-arc set (already the majority of this project) and grow it with difficult negatives: dimmers, motors, SMPS, and other loads that produce current distortion.
- Add more induced-arc positives so the model does not under-detect arcs.
- Validate on held-out appliances and, where possible, compare against traditional AFDD / AFCI algorithmic detectors.

**Edge deployment**

- Memory: keep the model small enough for the target Infineon MCU.
- Inference speed: meet real-time arc-fault latency (current windows use 2048 samples at 200 kHz with stride 1024).
- Power: efficient inference for always-on monitoring.

**Safety and validation**

- Set accuracy / false-negative and false-positive thresholds that match the product safety case.
- Commission against the physical current sensor on the production hardware.
- Define how the model will be updated after new field or lab data.

---

## Attributions & Citations

<a name="citations"></a>

[1] G. Si, “Analysis on China’s electrical fire situation and feature from 2008 to 2012,” *Fire Science and Technology* (消防科学与技术), vol. 33, no. 5, pp. 569–572, 2014. [Google Scholar](https://scholar.google.com/scholar?q=%22Analysis+on+China%27s+electrical+fire+situation+and+feature+from+2008+to+2012%22+Si). Bibliographic record as cited in open literature, e.g. [Guo *et al.*, *Algorithms*, 2015](https://doi.org/10.3390/a8040929).

[2] R. Campbell, *Electrical Fires*, National Fire Protection Association (NFPA Research), Quincy, MA, Mar. 2017. Estimated 45,210 U.S. home structure fires per year (2010–2014) involved electrical failure or malfunction; among classified cases, arcing was the most common mechanism. [Report PDF](https://inspectapedia.com/electric/Home-Electrical-Fires-NFPA-2017.pdf). The same figures are cited by NFPA in [*Falling Behind*](https://www.nfpa.org/-/media/Project/Storefront/Catalog/Files/Policy-and-action/Policy-Institute/PolicyInstituteFallingBehingElectricalSafetyReport.pdf) (notes 1 and 5).

[3] Nathaniel Taylor and Y. Jiang, Kungliga Tekniska högskolan (KTH). Dataset, conversion scripts, and accompanying material: [gnu.eecs.kth.se/nt/tmp/y/](https://gnu.eecs.kth.se/nt/tmp/y/) ([arc tests](https://gnu.eecs.kth.se/nt/tmp/y/data-arctests/), [appliance non-arc](https://gnu.eecs.kth.se/nt/tmp/y/data-applnonarc/)). [N. Taylor, KTH](https://www.kth.se/om/upptack/akademiska-hogtider/professorsinstallation/2024/nathaniel-taylor-1.1396976).

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about DEEPCRAFT™ Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model onto the device, please submit a ticket on the Infineon [community forum](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) DEEPCRAFT™ Studio page.
