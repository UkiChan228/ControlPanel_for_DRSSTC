# ControlPanel for DRSSTC (RP2350)

Universal, open-source control panel for Dual Resonant Solid State Tesla Coils (DRSSTC) based on the Raspberry Pi RP2350.

<p align="center">
  <img src="https://img.shields.io/badge/Platform-RP2350-blue.svg?style=flat-square&logo=raspberrypi" alt="Platform">
  <img src="https://img.shields.io/badge/Status-Alpha--Development-orange.svg?style=flat-square" alt="Status">
  <img src="https://img.shields.io/badge/Hardware-AliExpress--Sourced-red.svg?style=flat-square" alt="Hardware">
</p>

<p align="center">
  <a href="https://codeberg.org/uki_chan228/ControlPanel_for_DRSSTC" title="Codeberg Repository">Codeberg</a> |
  <a href="https://codeberg.org/uki_chan228/ControlPanel_for_DRSSTC/issues" title="Bug reports and feature requests">Issues</a>
</p>

<br/>

### Table of Contents
<p>
  <a href="#-overview">Overview</a> <br/>
  <a href="#%EF%B8%8F-status">Status</a> <br/>
  <a href="#-getting-started">Getting Started</a> <br/>
  <a href="#-hardware-choices">Hardware Choices</a> <br/>
  <a href="#-project-history">Project History</a>
</p>

<br/>

## 📒 Overview

This project is a dedicated, portable controller for **DRSSTC (Dual Resonant Solid State Tesla Coils)**. Built around the Raspberry Pi **RP2350**, it integrates reliable, high-frequency power management, an IPS touchscreen interface, and critical hardware-level safety features required for high-voltage control.

The primary goal is to provide a robust, noise-immune controller that can reliably send pulses to a Tesla coil over fiber optics without risking signal corruption from electromagnetic interference (EMI).

---

## ⚠️ Status

> [!WARNING]
> This project is currently in the **Alpha** development phase. The core hardware architecture is established, but firmware and features are actively being updated. Treat it as experimental.

---

## 🧑‍💻 Getting Started

To clone the repository along with the required submodules for graphics libraries and drivers, run:

```bash
# Clone the repository
git clone https://codeberg.org/uki_chan228/ControlPanel_for_DRSSTC  

# Initialize and update all submodules recursively
cd ControlPanel_for_DRSSTC
git submodule update --init --recursive
```

---

## 💡 Hardware Choices

### 1. MCU: Why RP2350 and not STM32?
The decision to use the **RP2350** instead of standard STM32 chips (like the STM32H or G series) came down to two major factors: **counterfeits and unique hardware features**.

*   **The Counterfeit Problem:** Finding genuine, reasonably priced STM32 microcontrollers on open marketplaces like AliExpress is incredibly difficult; almost all of them are clones or fakes. Original chips are expensive. In contrast, reputable manufacturers like *WeAct Studio* sell genuine RP2350 boards for around $3, whereas original STM32 equivalents cost between $5.50 and $10.
*   **The PIO (Programmable I/O) Advantage:** The absolute killer feature of the RP2350 is its PIO blocks (12 independent state machines in total). This functions like a mini-FPGA directly inside the MCU. For a Tesla coil controller, this is crucial: we can offload the critical fiber-optic pulse generation entirely to the PIO. Even if the main CPU hangs, freezes, or is busy rendering the UI, the PIO continues to execute pulses safely and independently at the hardware level.

While Chinese STM32 alternatives (like GD32, AT32, APM32, CH32) exist and are decent options, they still lack the dedicated PIO block that makes the RP2350 uniquely suited for this application.

### 2. Display and User Interface
The system uses the **MSP3526**, a 3.5-inch IPS display ($480 \times 320$ pixels) with a capacitive touchscreen. 

*   **IPS Panel:** Enables wide viewing angles and supports up to 16 million colors, allowing for comfortable navigation and clear real-time diagnostic graphs.
*   **Safety Interlock:** To prevent accidental triggers or interference during operation, touchscreen interrupts are completely ignored at the firmware level while the controller is actively transmitting pulses to the coil.

### 3. Power Supply & Charging
*   **Symmetrical Battery Layout:** The board is powered by two **18650 Li-ion cells** mounted in holders placed symmetrically on the PCB to balance the weight of the handheld unit.
*   **High-Frequency Regulation:** Voltage regulation is handled by the **TLV62130** step-down buck converter (a design choice inspired by the control boards of Antminer S9 miners, which run five of these converters). Operating at a high switching frequency of **1.25 MHz to 2.5 MHz** reduces output voltage ripple significantly, eliminating the need for bulky filtering capacitors. It also offers proven durability in harsh, noisy environments.
*   **USB-C Charging:** Safe and efficient charging of the 2S battery pack is managed by the **IP2326** switching charger IC.

*All active and passive components are standard and can be easily sourced from AliExpress, making this build straightforward to replicate.*

---

## 🌟 Project History

This project represents the dedication and effort of a single teenage developer fascinated by high-voltage electronics. 

The project has gone through a massive evolution since its inception:
*   **Late January 2026:** Started as a simple, low-power breadboard setup using an ATmega328P, a character LCD1602, a physical encoder, one LED, and a basic start button.
*   **Mid-April 2026:** The project transition was made to a much more powerful architecture, moving away from 8-bit limits to the RP2350 to allow for an IPS graphical interface, touchscreen control, and independent hardware safety loops.
*   **June 2026:** Final hardware iteration and completion of the core layout.

Special thanks to the **PCBWay** design contest for setting up a concrete deadline. Having a specific target date to complete the hardware provided the necessary momentum to bring this project to life.
