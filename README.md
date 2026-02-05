## AQM-ML – Air Quality Management with CO Prediction

This repository implements an end‑to‑end air quality management workflow focused on **carbon monoxide (CO) prediction** and **automatic actuation** of ventilation hardware (fan and blower).  
Machine learning runs on logged sensor data to forecast near‑term CO levels; simple decision logic then drives actuators on an embedded controller.

### 1. Problem statement

Indoor and semi‑indoor environments can accumulate unsafe CO levels if ventilation is not adequate.  
The goal of this project is to:

- **Predict short‑term CO concentration** using historical sensor readings.
- **Decide** when to activate a fan or a stronger blower based on predicted levels.
- **Actuate hardware** (fan/blower) via a microcontroller, closing the loop from data to physical response.

The ML and control logic run off‑device (in notebooks), while the microcontroller is used purely as an actuator layer that receives or uses CO information to switch hardware.

### 2. ML + decision + actuation pipeline

1. **Data collection**
   - CO and related sensor signals are collected and saved into CSV files under `data/`.
2. **Modeling and prediction (ML layer)**
   - A predictive model is trained to forecast CO levels over short and/or longer horizons.
   - The model uses historical sensor data (and, in some variants, fan/blower state) to predict future CO concentration.
3. **Decision logic**
   - Predicted CO values are compared to threshold levels to decide whether the **fan** or **blower** should operate.
   - The decision policy is implemented in the notebooks; model architecture, thresholds, and parameters are **not** changed by this restructuring.
4. **Actuation (hardware layer)**
   - The final decision (fan vs blower vs off) is translated into digital signals on the microcontroller.
   - The hardware firmware drives the motor and blower pins to physically enforce the chosen ventilation action.

The main deliverables for this pipeline are the **two primary notebooks** (ML + decision), the **experimental notebooks** (exploration/variants), and the **hardware firmware** (actuation).

### 3. Main notebooks (final workflows)

These notebooks represent the primary, interview‑ready workflows:

- `co_prediction_and_control.ipynb`  
  Short‑term CO prediction and fan/blower control logic, tying together data, model, and actuation decisions.

- `long_term_co_forecasting.ipynb`  
  Longer‑horizon CO forecasting pipeline, focused on time‑series modeling and evaluation over extended windows.

Both are kept at the repository root to highlight the final, polished workflows.

### 4. Experimental notebooks (exploration and variants)

Exploratory and iterative work is grouped under `experimental/` to keep the main workflows clean while preserving the full development history:

- `experimental/experimental_next_minute_prediction_fan_blower.ipynb`  
  Next‑minute prediction variant that includes additional features such as fan/blower status and other exploratory ideas.

- `experimental/experimental_adp_variant.ipynb`  
  Alternative/ADP‑style variant with overlapping logic plus additional visualizations and experiments.

These notebooks are **not** modified by this restructuring; they are simply organized as experimental work.

### 5. Data organization

All datasets are read‑only; **no CSV contents are altered**. They are organized as:

- `data/main/`  
  Primary sensor datasets used for the core modeling and control notebooks:
  - `sensor_data.csv`
  - `sensor_data_with_fan.csv`

- `data/delay/`  
  Synthetic, delay, or derived datasets used for experiments involving delayed effects or additional transformations:
  - `sensor_data_with_delay.csv`
  - `sensor_delay.csv`

This layout makes it clear which files are main inputs vs. derived/experimental variations.

### 6. Hardware layer (actuation firmware)

The `hardware/` directory contains the microcontroller firmware used to drive the fan and blower based on CO readings and/or externally computed decisions:

- `hardware/air_quality_controller.ino`  
  **Final controller firmware** used during the project.  
  Runs on an ESP8266‑based board, connects to Wi‑Fi, reads the CO sensor, and controls the motor (fan) and blower pins based on thresholded CO values.  
  This file reflects the final actuation logic; pin mappings, thresholds, and control logic are **not** changed by this restructuring.

- `hardware/experimental/`  
  Supporting and test sketches used during hardware bring‑up and debugging:
  - `motor_blower_basic.ino` – Simple motor/blower control based directly on analog sensor readings.
  - `esp8266_serial_test.ino` – Basic serial test for communication with an ESP8266.

The hardware layer is intentionally separated from the ML notebooks to emphasize that the microcontroller serves purely as the **actuator**, while ML runs off‑device.

### 7. Repository layout overview

At a high level, the repository is now structured as:

- `co_prediction_and_control.ipynb` – Final CO prediction + control pipeline.
- `long_term_co_forecasting.ipynb` – Final long‑term forecasting pipeline.
- `experimental/` – All exploratory and variant notebooks.
- `data/main/` – Primary sensor datasets.
- `data/delay/` – Delay/synthetic/derived datasets.
- `hardware/` – Final firmware and experimental hardware sketches.
- `README.md` – This documentation.

This structure is intended to be clean, interview‑ready, and easy to navigate for reviewers.

### 8. What was and wasn’t changed

- **Changed**: Only file and folder organization and this `README.md` documentation.
- **Not changed**:
  - No Python, ML, or Arduino **code logic** was modified.
  - No model architectures, thresholds, or parameters were altered.
  - No CSV contents or datasets were edited.

In other words: **only file and folder organization was changed; code logic and datasets were not modified.**
