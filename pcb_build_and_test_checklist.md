# PCB Build & Test Checklist — board_pcb v1.0.0

> **Board:** board_pcb | **Rev:** v1.0.0 | **Fab:** JLCPCB  
> **Tools needed:** Multimeter, tweezers (metal), flux, soldering iron, USB-C cable, LiPo battery

---

## How to Use This Checklist

Work through each **Stage** in order. Every stage has two sections:

- **PRE-INSTALL SIMULATION** — tests you run on bare pads _before_ soldering anything, using tweezers to simulate connections
- **POST-INSTALL VERIFICATION** — tests you run _after_ soldering that stage's components

**Multimeter modes used:**
| Symbol | Mode | Use for |
|--------|------|---------|
| 🔔 | Continuity / beep | Checking connections exist |
| ⚡ | Diode mode | Checking diode orientation & health |
| 🔋 | DC Voltage (20V range) | Checking live voltage rails |

**Probe conventions:**

- 🔴 = Red probe (positive)
- ⚫ = Black probe (negative / GND reference)

---

## Matrix Quick Reference

Each key has a complete path: **MCU pin (P0–P5) → Switch → Row net → Diode → MCU pin (P6–P10)**

| Switch | Diode | Row Net            | MCU Pin A (via switch) | MCU Pin B (via diode) |
| ------ | ----- | ------------------ | ---------------------- | --------------------- |
| S1     | D1    | extra_pinky_bottom | P0 (XIAO pad 24)       | P6 (XIAO pad 18)      |
| S2     | D2    | extra_pinky_home   | P0 (XIAO pad 24)       | P7 (XIAO pad 7)       |
| S3     | D3    | extra_pinky_top    | P0 (XIAO pad 24)       | P8 (XIAO pad 6)       |
| S4     | D4    | extra_pinky_upper  | P0 (XIAO pad 24)       | P9 (XIAO pad 5)       |
| S5     | D5    | pinky_bottom       | P1 (XIAO pad 23)       | P6 (XIAO pad 18)      |
| S6     | D6    | pinky_home         | P1 (XIAO pad 23)       | P7 (XIAO pad 7)       |
| S7     | D7    | pinky_top          | P1 (XIAO pad 23)       | P8 (XIAO pad 6)       |
| S8     | D8    | pinky_upper        | P1 (XIAO pad 23)       | P9 (XIAO pad 5)       |
| S9     | D9    | ring_bottom        | P2 (XIAO pad 22)       | P6 (XIAO pad 18)      |
| S10    | D10   | ring_home          | P2 (XIAO pad 22)       | P7 (XIAO pad 7)       |
| S11    | D11   | ring_top           | P2 (XIAO pad 22)       | P8 (XIAO pad 6)       |
| S12    | D12   | ring_upper         | P2 (XIAO pad 22)       | P9 (XIAO pad 5)       |
| S13    | D13   | middle_bottom      | P3 (XIAO pad 21)       | P6 (XIAO pad 18)      |
| S14    | D14   | middle_home        | P3 (XIAO pad 21)       | P7 (XIAO pad 7)       |
| S15    | D15   | middle_top         | P3 (XIAO pad 21)       | P8 (XIAO pad 6)       |
| S16    | D16   | middle_upper       | P3 (XIAO pad 21)       | P9 (XIAO pad 5)       |
| S17    | D17   | index_bottom       | P4 (XIAO pad 20)       | P6 (XIAO pad 18)      |
| S18    | D18   | index_home         | P4 (XIAO pad 20)       | P7 (XIAO pad 7)       |
| S19    | D19   | index_top          | P4 (XIAO pad 20)       | P8 (XIAO pad 6)       |
| S20    | D20   | index_upper        | P4 (XIAO pad 20)       | P9 (XIAO pad 5)       |
| S21    | D21   | inner_bottom       | P5 (XIAO pad 19)       | P6 (XIAO pad 18)      |
| S22    | D22   | inner_home         | P5 (XIAO pad 19)       | P7 (XIAO pad 7)       |
| S23    | D23   | inner_top          | P5 (XIAO pad 19)       | P8 (XIAO pad 6)       |
| S24    | D24   | inner_upper        | P5 (XIAO pad 19)       | P9 (XIAO pad 5)       |
| S25    | D25   | near_thumb         | P3 (XIAO pad 21)       | P10 (XIAO pad 4)      |
| S26    | D26   | home_thumb         | P4 (XIAO pad 20)       | P10 (XIAO pad 4)      |
| S27    | D27   | far_thumb          | P5 (XIAO pad 19)       | P10 (XIAO pad 4)      |

---

---

# STAGE 0 — Bare PCB

> Nothing soldered. Board fresh from JLCPCB. No power connected.

## 0A — Visual Inspection

- [ ] **0A.1** Inspect F.Cu (front) under good lighting — look for obvious copper bridges, scratches through traces, missing pads
- [ ] **0A.2** Inspect B.Cu (back) — same checks
- [ ] **0A.3** Check all 27 diode footprints (D1–D27) — confirm both pads present, no pre-bridged pads
- [ ] **0A.4** Check all 27 switch footprints (S1–S27) — confirm all switch pads present on both layers
- [ ] **0A.5** Check JST1 connector footprint — confirm pads are clean
- [ ] **0A.6** Check PWR1 power switch footprint — confirm pads are clean
- [ ] **0A.7** Check RST1 reset switch footprint — confirm both through-hole pads present
- [ ] **0A.8** Check XIAO BLE footprint — count and confirm all castellated pads
- [ ] **0A.9** Check via holes — confirm all small vias (0.3mm drill) are open and not filled/blocked
- [ ] **0A.10** Check board edge — confirm no cracks, clean cuts on curved sections

## 0B — Bare Board Short Check

> 🔔 **Multimeter: Continuity mode.** Board unpowered.  
> **A beep = short = BAD** for everything below.

| #   | What to check                 | 🔴 Red probe       | ⚫ Black probe                   | Expected |
| --- | ----------------------------- | ------------------ | -------------------------------- | -------- |
| [ ] | GND vs RAW trace              | GND via near RST1  | RAW pad (PAD1 / PWR1)            | No beep  |
| [ ] | GND vs BAT_P trace            | GND via near RST1  | BAT_P pad (JST1 footprint pin 1) | No beep  |
| [ ] | GND vs any diode pad          | GND via            | Any D1–D27 pad                   | No beep  |
| [ ] | Adjacent diode pads (sample)  | D1 pad 1           | D1 pad 2                         | No beep  |
| [ ] | Adjacent diode pads (sample)  | D9 pad 1           | D9 pad 2                         | No beep  |
| [ ] | Adjacent switch pads (sample) | S1 pad 1           | S1 pad 2                         | No beep  |
| [ ] | Adjacent switch pads (sample) | S14 pad 1          | S14 pad 2                        | No beep  |
| [ ] | PWR1 pad 1 vs pad 2           | PWR1 pad 1 (BAT_P) | PWR1 pad 2 (RAW)                 | No beep  |
| [ ] | PWR1 pad 1 vs pad 3           | PWR1 pad 1         | PWR1 pad 3                       | No beep  |

## 0C — Bare Board Trace Continuity Check

> 🔔 **Multimeter: Continuity mode.**  
> **A beep = connection = GOOD** for everything below.  
> This confirms traces are intact before you start soldering.

| #   | What to check                             | 🔴 Red probe         | ⚫ Black probe       | Expected            |
| --- | ----------------------------------------- | -------------------- | -------------------- | ------------------- |
| [ ] | GND ring (RST to JST)                     | RST1 pad 2 footprint | JST1 pin 2 footprint | Beep                |
| [ ] | BAT_P to PWR1                             | JST1 pin 1 footprint | PWR1 pad 1 footprint | Beep                |
| [ ] | RAW to PWR1                               | PAD1 (RAW pad)       | PWR1 pad 2 footprint | Beep                |
| [ ] | D1 pad 1 connects to same net as D5 pad 1 | D1 pad 1             | D5 pad 1             | Beep (both on P6)   |
| [ ] | D1 pad 1 connects to same net as D9 pad 1 | D1 pad 1             | D9 pad 1             | Beep (both on P6)   |
| [ ] | D1 pad 2 connects to S1 pad 1             | D1 pad 2             | S1 pad 1             | Beep (same row net) |
| [ ] | D2 pad 2 connects to S2 pad 1             | D2 pad 2             | S2 pad 1             | Beep (same row net) |
| [ ] | S1 pad 2 connects to S2 pad 2             | S1 pad 2             | S2 pad 2             | Beep (both on P0)   |
| [ ] | S5 pad 2 connects to S6 pad 2             | S5 pad 2             | S6 pad 2             | Beep (both on P1)   |

---

---

# STAGE 1 — Diodes (D1–D27)

> **Component:** 27× SOD-123 diodes  
> **Install on:** The side you choose to solder (F.Cu or B.Cu — pick one side and be consistent)  
> **Orientation:** Cathode bar (line on diode body) faces toward the **pad marked with square/line** on PCB silkscreen

## 1A — PRE-INSTALL SIMULATION

> Simulate what a correctly-installed diode would do, using tweezers.  
> ⚡ **Multimeter: Diode mode.**

**How to simulate:** Probe the two pads of each diode footprint. The PCB traces already connect pad 1 to the column net and pad 2 to the row net. We are verifying the _pad isolation_ before installing.

| #   | What                        | 🔴 Red probe | ⚫ Black probe | Expected                 |
| --- | --------------------------- | ------------ | -------------- | ------------------------ |
| [ ] | D1 pad 1 vs pad 2 isolated  | D1 pad 1     | D1 pad 2       | OL (open) — no diode yet |
| [ ] | D9 pad 1 vs pad 2 isolated  | D9 pad 1     | D9 pad 2       | OL (open)                |
| [ ] | D25 pad 1 vs pad 2 isolated | D25 pad 1    | D25 pad 2      | OL (open)                |

**Tweezers simulation — check row-to-column path works via PCB trace:**

> Touch tweezers across D1 pads (bridging pad 1 and pad 2) to simulate a zero-resistance link.  
> 🔔 Switch to **continuity mode.**

| #   | Simulation                   | Tweezer on       | 🔴 Red   | ⚫ Black | Expected                         |
| --- | ---------------------------- | ---------------- | -------- | -------- | -------------------------------- |
| [ ] | Bridge D1 pads with tweezers | D1 pad 1 + pad 2 | D1 pad 1 | S1 pad 1 | Beep (row net connected through) |
| [ ] | Bridge D1 pads with tweezers | D1 pad 1 + pad 2 | D1 pad 1 | D5 pad 1 | Beep (P6 net shared)             |
| [ ] | Remove tweezers              | —                | D1 pad 1 | S1 pad 1 | No beep                          |

## 1B — INSTALL DIODES D1–D27

> Solder all 27 diodes. Double-check orientation on every single diode before soldering.  
> Cathode (bar end) → toward **square pad** or as marked on your silkscreen.

- [ ] **1B.1** Solder D1–D4 (extra pinky row, connects to P0/P6-P9)
- [ ] **1B.2** Solder D5–D8 (pinky row, connects to P1/P6-P9)
- [ ] **1B.3** Solder D9–D12 (ring row, connects to P2/P6-P9)
- [ ] **1B.4** Solder D13–D16 (middle row, connects to P3/P6-P9)
- [ ] **1B.5** Solder D17–D20 (index row, connects to P4/P6-P9)
- [ ] **1B.6** Solder D21–D24 (inner row, connects to P5/P6-P9)
- [ ] **1B.7** Solder D25–D27 (thumb row, connects to P3-P5/P10)
- [ ] **1B.8** Visual re-check — confirm all diode bodies oriented same way

## 1C — POST-INSTALL DIODE VERIFICATION

> ⚡ **Multimeter: Diode mode.**  
> Check each diode: forward voltage 0.3–0.7V, reverse = OL.

### Diode health check (all 27)

| #   | Diode | 🔴 Red (cathode / pad 1) | ⚫ Black (anode / pad 2) | Forward V | Reverse check |
| --- | ----- | ------------------------ | ------------------------ | --------- | ------------- |
| [ ] | D1    | D1 pad 1                 | D1 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D2    | D2 pad 1                 | D2 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D3    | D3 pad 1                 | D3 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D4    | D4 pad 1                 | D4 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D5    | D5 pad 1                 | D5 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D6    | D6 pad 1                 | D6 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D7    | D7 pad 1                 | D7 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D8    | D8 pad 1                 | D8 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D9    | D9 pad 1                 | D9 pad 2                 | 0.3–0.7V  | Swap → OL     |
| [ ] | D10   | D10 pad 1                | D10 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D11   | D11 pad 1                | D11 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D12   | D12 pad 1                | D12 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D13   | D13 pad 1                | D13 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D14   | D14 pad 1                | D14 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D15   | D15 pad 1                | D15 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D16   | D16 pad 1                | D16 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D17   | D17 pad 1                | D17 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D18   | D18 pad 1                | D18 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D19   | D19 pad 1                | D19 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D20   | D20 pad 1                | D20 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D21   | D21 pad 1                | D21 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D22   | D22 pad 1                | D22 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D23   | D23 pad 1                | D23 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D24   | D24 pad 1                | D24 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D25   | D25 pad 1                | D25 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D26   | D26 pad 1                | D26 pad 2                | 0.3–0.7V  | Swap → OL     |
| [ ] | D27   | D27 pad 1                | D27 pad 2                | 0.3–0.7V  | Swap → OL     |

### Cross-diode short check (diodes sharing same column must not short rows)

> 🔔 **Continuity mode.** These should NOT beep.

| #   | What                                             | 🔴 Red probe | ⚫ Black probe | Expected |
| --- | ------------------------------------------------ | ------------ | -------------- | -------- |
| [ ] | D1 anode vs D5 anode (diff rows, same col P6)    | D1 pad 2     | D5 pad 2       | No beep  |
| [ ] | D1 anode vs D9 anode                             | D1 pad 2     | D9 pad 2       | No beep  |
| [ ] | D2 anode vs D6 anode (diff rows, same col P7)    | D2 pad 2     | D6 pad 2       | No beep  |
| [ ] | D25 anode vs D26 anode (diff rows, same col P10) | D25 pad 2    | D26 pad 2      | No beep  |

### Row-to-column path through diode (sample)

> 🔔 **Continuity mode.** These SHOULD beep — confirms full trace path intact.

| #   | What                                      | 🔴 Red probe | ⚫ Black probe | Expected |
| --- | ----------------------------------------- | ------------ | -------------- | -------- |
| [ ] | D1 trace: pad 1 to S1 pad 1 (via row net) | D1 pad 2     | S1 pad 1       | Beep     |
| [ ] | D14 trace: pad 2 to S14 pad 1             | D14 pad 2    | S14 pad 1      | Beep     |
| [ ] | D27 trace: pad 2 to S27 pad 1             | D27 pad 2    | S27 pad 1      | Beep     |

---

---

# STAGE 2 — Power Switch (PWR1) + RAW Pad (PAD1)

> **Components:** 1× SMD side power switch (PWR1), 1× SMD RAW pad (PAD1)  
> **Note:** PWR1 has mechanical mounting pins (no net) and 3 signal pads: pad 1 = BAT_P, pad 2 = RAW, pad 3 = NC

## 2A — PRE-INSTALL SIMULATION

> 🔔 **Continuity mode.** Simulate switch ON by bridging PWR1 pad 1 and pad 2 with tweezers.

| #   | Simulation             | Tweezer on   | 🔴 Red     | ⚫ Black             | Expected                   |
| --- | ---------------------- | ------------ | ---------- | -------------------- | -------------------------- |
| [ ] | Bridge PWR1 pad1+pad2  | PWR1 pad 1+2 | PWR1 pad 1 | JST1 pin 1 footprint | Beep (BAT_P trace intact)  |
| [ ] | Bridge PWR1 pad1+pad2  | PWR1 pad 1+2 | PWR1 pad 2 | PAD1 (RAW)           | Beep (RAW trace intact)    |
| [ ] | No bridge (switch OFF) | —            | PWR1 pad 1 | PAD1                 | No beep (open, switch off) |

## 2B — INSTALL PWR1 AND PAD1

- [ ] **2B.1** Solder PWR1 power switch — confirm mechanical pins are secure, toggle mechanism moves freely
- [ ] **2B.2** Solder PAD1 (RAW SMD pad)

## 2C — POST-INSTALL POWER SWITCH VERIFICATION

> 🔔 **Continuity mode.**

| #   | Switch state                                 | 🔴 Red probe         | ⚫ Black probe    | Expected |
| --- | -------------------------------------------- | -------------------- | ----------------- | -------- |
| [ ] | PWR switch **OFF**                           | PWR1 pad 1 (BAT_P)   | PAD1 (RAW)        | No beep  |
| [ ] | PWR switch **ON**                            | PWR1 pad 1 (BAT_P)   | PAD1 (RAW)        | Beep     |
| [ ] | PWR switch **OFF** again                     | PWR1 pad 1 (BAT_P)   | PAD1 (RAW)        | No beep  |
| [ ] | PWR switch **ON** — confirm BAT_P to JST pad | JST1 pin 1 footprint | PWR1 pad 1        | Beep     |
| [ ] | Short check: BAT_P vs GND                    | PWR1 pad 1           | GND via near RST1 | No beep  |
| [ ] | Short check: RAW vs GND                      | PAD1                 | GND via near RST1 | No beep  |

---

---

# STAGE 3 — JST Battery Connector (JST1)

> **Component:** 1× JST-PH 2-pin battery connector  
> **Pin 1:** BAT_P (positive, red wire), **Pin 2:** GND (negative, black wire)

## 3A — PRE-INSTALL SIMULATION

> 🔔 **Continuity mode.** Confirm traces are in place for JST pads.

| #   | What                              | 🔴 Red probe   | ⚫ Black probe    | Expected                  |
| --- | --------------------------------- | -------------- | ----------------- | ------------------------- |
| [ ] | JST pin 1 footprint to PWR1 pad 1 | JST1 pin 1 pad | PWR1 pad 1        | Beep (BAT_P trace intact) |
| [ ] | JST pin 2 footprint to GND        | JST1 pin 2 pad | GND via near RST1 | Beep (GND trace intact)   |
| [ ] | JST pin 1 vs pin 2 isolated       | JST1 pin 1 pad | JST1 pin 2 pad    | No beep                   |

## 3B — INSTALL JST1

- [ ] **3B.1** Insert JST1 connector into footprint, confirm correct orientation (latch faces outward for cable access)
- [ ] **3B.2** Solder both through-hole pins and SMD pads
- [ ] **3B.3** Visual check — no solder bridge between pin 1 and pin 2

## 3C — POST-INSTALL JST VERIFICATION

> 🔔 **Continuity mode.** **DO NOT connect battery yet.**

| #   | What                       | 🔴 Red probe       | ⚫ Black probe | Expected |
| --- | -------------------------- | ------------------ | -------------- | -------- |
| [ ] | JST pin 1 to BAT_P on PWR1 | JST1 pin 1 (metal) | PWR1 pad 1     | Beep     |
| [ ] | JST pin 2 to GND           | JST1 pin 2 (metal) | GND via        | Beep     |
| [ ] | Pin 1 vs pin 2 short check | JST1 pin 1         | JST1 pin 2     | No beep  |
| [ ] | BAT_P vs GND short check   | JST1 pin 1         | JST1 pin 2     | No beep  |

> 🔋 **NOW connect battery. PWR switch OFF. Multimeter: DC Voltage mode.**

| #   | What                   | 🔴 Red probe | ⚫ Black probe | Expected                |
| --- | ---------------------- | ------------ | -------------- | ----------------------- |
| [ ] | Battery voltage at JST | JST1 pin 1   | JST1 pin 2     | ~3.7V (battery voltage) |
| [ ] | BAT_P with switch OFF  | PWR1 pad 1   | GND via        | ~3.7V                   |
| [ ] | RAW with switch OFF    | PAD1         | GND via        | ~0V (switch open)       |
| [ ] | RAW with switch ON     | PAD1         | GND via        | ~3.7V                   |

- [ ] **3C.1** Turn switch back OFF. Disconnect battery for remaining stages.

---

---

# STAGE 4 — Reset Switch (RST1)

> **Component:** 1× THT tactile reset button  
> **Pad 1:** RST net (connects to XIAO RST pin), **Pad 2:** GND

## 4A — PRE-INSTALL SIMULATION

> 🔔 **Continuity mode.**

| #   | What                                       | 🔴 Red probe         | ⚫ Black probe | Expected                           |
| --- | ------------------------------------------ | -------------------- | -------------- | ---------------------------------- |
| [ ] | RST1 pad 1 footprint to GND trace isolated | RST1 pad 1           | RST1 pad 2     | No beep (open, button not pressed) |
| [ ] | RST1 pad 2 footprint to GND via            | RST1 pad 2 footprint | GND via        | Beep (GND trace intact)            |

**Simulate button press with tweezers:**
| # | Simulation | Tweezer on | 🔴 Red | ⚫ Black | Expected |
|---|-----------|------------|--------|---------|---------|
| [ ] | Bridge RST1 pad 1+2 | RST1 pad 1+2 | RST1 pad 1 | GND via | Beep (RST pulled to GND = reset) |

## 4B — INSTALL RST1

- [ ] **4B.1** Insert RST1 button through the board, correct orientation
- [ ] **4B.2** Solder both pins
- [ ] **4B.3** Confirm button clicks and springs back when pressed

## 4C — POST-INSTALL RST VERIFICATION

> 🔔 **Continuity mode.**

| #   | Button state                         | 🔴 Red probe | ⚫ Black probe | Expected |
| --- | ------------------------------------ | ------------ | -------------- | -------- |
| [ ] | Not pressed                          | RST1 pin 1   | RST1 pin 2     | No beep  |
| [ ] | **Press and hold** button            | RST1 pin 1   | RST1 pin 2     | Beep     |
| [ ] | Release button                       | RST1 pin 1   | RST1 pin 2     | No beep  |
| [ ] | GND trace check                      | RST1 pin 2   | GND via        | Beep     |
| [ ] | Short check RST vs GND (not pressed) | RST1 pin 1   | GND via        | No beep  |

---

---

# STAGE 5 — XIAO BLE Microcontroller

> **Component:** Seeed XIAO BLE (nRF52840)  
> **Install via:** Pin headers + female socket, OR direct solder to castellated pads

## 5A — PRE-INSTALL SIMULATION

> 🔔 **Continuity mode.** Verify XIAO footprint pads connect to the correct matrix nets.

**Column net traces (P0–P10 to XIAO pad footprint):**

| #   | Net | XIAO pad footprint | Connected to                     | Expected                                    |
| --- | --- | ------------------ | -------------------------------- | ------------------------------------------- |
| [ ] | P0  | XIAO pad 24        | S1, S2, S3, S4 pad 2             | Bridge XIAO pad 24 → probe S1 pad 2 → Beep  |
| [ ] | P1  | XIAO pad 23        | S5, S6, S7, S8 pad 2             | Bridge XIAO pad 23 → probe S5 pad 2 → Beep  |
| [ ] | P2  | XIAO pad 22        | S9–S12 pad 2                     | Bridge XIAO pad 22 → probe S9 pad 2 → Beep  |
| [ ] | P3  | XIAO pad 21        | S13–S16, S25 pad 2               | Bridge XIAO pad 21 → probe S13 pad 2 → Beep |
| [ ] | P4  | XIAO pad 20        | S17–S20, S26 pad 2               | Bridge XIAO pad 20 → probe S17 pad 2 → Beep |
| [ ] | P5  | XIAO pad 19        | S21–S24, S27 pad 2               | Bridge XIAO pad 19 → probe S21 pad 2 → Beep |
| [ ] | P6  | XIAO pad 18        | D1, D5, D9, D13, D17, D21 pad 1  | Bridge XIAO pad 18 → probe D1 pad 1 → Beep  |
| [ ] | P7  | XIAO pad 7         | D2, D6, D10, D14, D18, D22 pad 1 | Bridge XIAO pad 7 → probe D2 pad 1 → Beep   |
| [ ] | P8  | XIAO pad 6         | D3, D7, D11, D15, D19, D23 pad 1 | Bridge XIAO pad 6 → probe D3 pad 1 → Beep   |
| [ ] | P9  | XIAO pad 5         | D4, D8, D12, D16, D20, D24 pad 1 | Bridge XIAO pad 5 → probe D4 pad 1 → Beep   |
| [ ] | P10 | XIAO pad 4         | D25, D26, D27 pad 1              | Bridge XIAO pad 4 → probe D25 pad 1 → Beep  |

**Power rail traces (before XIAO installed):**

| #   | Net                              | XIAO pad footprint | 🔴 Red               | ⚫ Black             | Expected           |
| --- | -------------------------------- | ------------------ | -------------------- | -------------------- | ------------------ |
| [ ] | GND                              | XIAO pad 2         | XIAO pad 2 footprint | GND via (RST1 pin 2) | Beep               |
| [ ] | VCC5                             | XIAO pad 1         | XIAO pad 1 footprint | PAD1 (RAW)           | Beep (USB 5V rail) |
| [ ] | XIAO pad 1 vs pad 2 (5V vs GND)  | XIAO pad 1         | XIAO pad 2           | No beep              |
| [ ] | XIAO pad 3 vs pad 2 (3V3 vs GND) | XIAO pad 3         | XIAO pad 2           | No beep              |
| [ ] | RST trace                        | XIAO pad (RST)     | RST1 pin 1           | Beep                 |

## 5B — INSTALL XIAO BLE

- [ ] **5B.1** If using socket: solder female socket to PCB, insert XIAO into socket
- [ ] **5B.2** If direct solder: carefully align XIAO castellated pads, tack two corners first, then solder all pads
- [ ] **5B.3** Visual check — no solder bridges between adjacent XIAO pads
- [ ] **5B.4** Check pads 1-7 (top row) individually under magnification
- [ ] **5B.5** Check pads 18-24 (bottom row) individually under magnification

## 5C — POST-INSTALL XIAO VERIFICATION (No Power)

> 🔔 **Continuity mode.** Board unpowered.

**Adjacent pin short check (most critical):**

| #   | What              | 🔴 Red | ⚫ Black | Expected |
| --- | ----------------- | ------ | -------- | -------- |
| [ ] | XIAO pad 1 vs 2   | pad 1  | pad 2    | No beep  |
| [ ] | XIAO pad 2 vs 3   | pad 2  | pad 3    | No beep  |
| [ ] | XIAO pad 3 vs 4   | pad 3  | pad 4    | No beep  |
| [ ] | XIAO pad 4 vs 5   | pad 4  | pad 5    | No beep  |
| [ ] | XIAO pad 5 vs 6   | pad 5  | pad 6    | No beep  |
| [ ] | XIAO pad 6 vs 7   | pad 6  | pad 7    | No beep  |
| [ ] | XIAO pad 18 vs 19 | pad 18 | pad 19   | No beep  |
| [ ] | XIAO pad 19 vs 20 | pad 19 | pad 20   | No beep  |
| [ ] | XIAO pad 20 vs 21 | pad 20 | pad 21   | No beep  |
| [ ] | XIAO pad 21 vs 22 | pad 21 | pad 22   | No beep  |
| [ ] | XIAO pad 22 vs 23 | pad 22 | pad 23   | No beep  |
| [ ] | XIAO pad 23 vs 24 | pad 23 | pad 24   | No beep  |

**Net continuity through XIAO pads:**

| #   | What                     | 🔴 Red      | ⚫ Black   | Expected |
| --- | ------------------------ | ----------- | ---------- | -------- |
| [ ] | P0 reaches switch column | XIAO pad 24 | S1 pad 2   | Beep     |
| [ ] | P6 reaches diode column  | XIAO pad 18 | D1 pad 1   | Beep     |
| [ ] | GND at XIAO              | XIAO pad 2  | RST1 pin 2 | Beep     |

## 5D — First Power-On with XIAO (USB only, no battery)

> 🔋 **Multimeter: DC Voltage mode.** Connect USB-C. PWR switch **OFF**.

| #   | What                                      | 🔴 Red      | ⚫ Black       | Expected |
| --- | ----------------------------------------- | ----------- | -------------- | -------- |
| [ ] | VCC5 via USB                              | XIAO pad 1  | XIAO pad 2     | ~5V      |
| [ ] | VCC3 via USB                              | XIAO pad 3  | XIAO pad 2     | ~3.3V    |
| [ ] | GND reference                             | XIAO pad 2  | GND via (RST1) | ~0V      |
| [ ] | P0–P5 idle (should be floating or pulled) | XIAO pad 24 | XIAO pad 2     | < 3.3V   |
| [ ] | P6–P10 idle                               | XIAO pad 18 | XIAO pad 2     | < 3.3V   |

> 🔋 **Now test with battery. Connect battery to JST1. PWR switch ON.**

| #   | What                   | 🔴 Red     | ⚫ Black   | Expected                    |
| --- | ---------------------- | ---------- | ---------- | --------------------------- |
| [ ] | RAW with switch ON     | PAD1       | XIAO pad 2 | ~3.7V                       |
| [ ] | VCC3 from battery      | XIAO pad 3 | XIAO pad 2 | ~3.3V                       |
| [ ] | Confirm XIAO powers on | —          | —          | LED blinks / device visible |

- [ ] **5D.1** Confirm XIAO BLE appears in Bluetooth scan list on phone/computer
- [ ] **5D.2** Confirm XIAO appears as USB device when plugged in
- [ ] Disconnect battery and USB before continuing

---

---

# STAGE 6 — Choc Switches (S1–S27)

> **Component:** 27× Kailh Choc v1/v2 switches  
> **Install:** Switches sit on top of diodes. The dual-layer footprint supports either soldering or hotswap sockets.

## 6A — PRE-INSTALL SIMULATION (Full Key Path Test)

> This is the most important simulation stage. Use **metal tweezers** to short each switch footprint's pad 1 and pad 2, simulating a keypress.  
> ⚠️ XIAO must be installed and USB connected for this test.  
> Flash firmware first (see 6A.1), then simulate keypresses.

### 6A.1 — Flash Firmware

- [ ] Connect XIAO via USB-C
- [ ] Press RST button **twice quickly** (double-tap) to enter bootloader
- [ ] Confirm board appears as USB mass storage (UF2 bootloader drive)
- [ ] Copy/flash your ZMK or QMK firmware `.uf2` file to the drive
- [ ] Wait for board to reboot
- [ ] Confirm board is recognized as a USB HID keyboard

### 6A.2 — Open Key Tester

- [ ] Open [https://www.keyboardtester.com](https://www.keyboardtester.com) or any text editor
- [ ] Have your keymap reference ready to know which key each switch should send

### 6A.3 — Simulate Each Switch with Tweezers

> 🔴⚫ Touch metal tweezers to **both pads of the switch footprint simultaneously** to simulate a keypress.  
> Each switch footprint has pad 1 (row net) and pad 2 (column net via P0–P5).

**Extra Pinky column (P0):**

| #   | Switch | Pad 1 net          | Pad 2 net | Action                             | Expected                |
| --- | ------ | ------------------ | --------- | ---------------------------------- | ----------------------- |
| [ ] | S1     | extra_pinky_bottom | P0        | Touch tweezers to S1 pad 1 + pad 2 | Key registers in tester |
| [ ] | S2     | extra_pinky_home   | P0        | Touch tweezers to S2 pad 1 + pad 2 | Key registers           |
| [ ] | S3     | extra_pinky_top    | P0        | Touch tweezers to S3 pad 1 + pad 2 | Key registers           |
| [ ] | S4     | extra_pinky_upper  | P0        | Touch tweezers to S4 pad 1 + pad 2 | Key registers           |

**Pinky column (P1):**

| #   | Switch | Pad 1 net    | Pad 2 net | Action                             | Expected      |
| --- | ------ | ------------ | --------- | ---------------------------------- | ------------- |
| [ ] | S5     | pinky_bottom | P1        | Touch tweezers to S5 pad 1 + pad 2 | Key registers |
| [ ] | S6     | pinky_home   | P1        | Touch tweezers to S6 pad 1 + pad 2 | Key registers |
| [ ] | S7     | pinky_top    | P1        | Touch tweezers to S7 pad 1 + pad 2 | Key registers |
| [ ] | S8     | pinky_upper  | P1        | Touch tweezers to S8 pad 1 + pad 2 | Key registers |

**Ring column (P2):**

| #   | Switch | Pad 1 net   | Pad 2 net | Action                     | Expected      |
| --- | ------ | ----------- | --------- | -------------------------- | ------------- |
| [ ] | S9     | ring_bottom | P2        | Touch tweezers to S9 pads  | Key registers |
| [ ] | S10    | ring_home   | P2        | Touch tweezers to S10 pads | Key registers |
| [ ] | S11    | ring_top    | P2        | Touch tweezers to S11 pads | Key registers |
| [ ] | S12    | ring_upper  | P2        | Touch tweezers to S12 pads | Key registers |

**Middle column (P3):**

| #   | Switch | Pad 1 net     | Pad 2 net | Action                     | Expected      |
| --- | ------ | ------------- | --------- | -------------------------- | ------------- |
| [ ] | S13    | middle_bottom | P3        | Touch tweezers to S13 pads | Key registers |
| [ ] | S14    | middle_home   | P3        | Touch tweezers to S14 pads | Key registers |
| [ ] | S15    | middle_top    | P3        | Touch tweezers to S15 pads | Key registers |
| [ ] | S16    | middle_upper  | P3        | Touch tweezers to S16 pads | Key registers |
| [ ] | S25    | near_thumb    | P3        | Touch tweezers to S25 pads | Key registers |

**Index column (P4):**

| #   | Switch | Pad 1 net    | Pad 2 net | Action                     | Expected      |
| --- | ------ | ------------ | --------- | -------------------------- | ------------- |
| [ ] | S17    | index_bottom | P4        | Touch tweezers to S17 pads | Key registers |
| [ ] | S18    | index_home   | P4        | Touch tweezers to S18 pads | Key registers |
| [ ] | S19    | index_top    | P4        | Touch tweezers to S19 pads | Key registers |
| [ ] | S20    | index_upper  | P4        | Touch tweezers to S20 pads | Key registers |
| [ ] | S26    | home_thumb   | P4        | Touch tweezers to S26 pads | Key registers |

**Inner column (P5):**

| #   | Switch | Pad 1 net    | Pad 2 net | Action                     | Expected      |
| --- | ------ | ------------ | --------- | -------------------------- | ------------- |
| [ ] | S21    | inner_bottom | P5        | Touch tweezers to S21 pads | Key registers |
| [ ] | S22    | inner_home   | P5        | Touch tweezers to S22 pads | Key registers |
| [ ] | S23    | inner_top    | P5        | Touch tweezers to S23 pads | Key registers |
| [ ] | S24    | inner_upper  | P5        | Touch tweezers to S24 pads | Key registers |
| [ ] | S27    | far_thumb    | P5        | Touch tweezers to S27 pads | Key registers |

> **If a key does NOT register:** check that its diode reads correct forward voltage (Stage 1C), and confirm the trace from switch pad 2 to the XIAO pad is continuous.

## 6B — INSTALL SWITCHES S1–S27

- [ ] **6B.1** Install and solder/socket S1–S4 (extra pinky column)
- [ ] **6B.2** Install and solder/socket S5–S8 (pinky column)
- [ ] **6B.3** Install and solder/socket S9–S12 (ring column)
- [ ] **6B.4** Install and solder/socket S13–S16 (middle column)
- [ ] **6B.5** Install and solder/socket S17–S20 (index column)
- [ ] **6B.6** Install and solder/socket S21–S24 (inner column)
- [ ] **6B.7** Install and solder/socket S25, S26, S27 (thumb cluster)
- [ ] **6B.8** Visual check — all switches seated flush, no tilted switches

## 6C — POST-INSTALL SWITCH VERIFICATION

> All 27 keys tested with physical switches. USB connected, firmware flashed.  
> Open keyboard tester. Press each physical switch.

**Extra Pinky:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S1 | Press switch | Key registers |
| [ ] | S2 | Press switch | Key registers |
| [ ] | S3 | Press switch | Key registers |
| [ ] | S4 | Press switch | Key registers |

**Pinky:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S5 | Press switch | Key registers |
| [ ] | S6 | Press switch | Key registers |
| [ ] | S7 | Press switch | Key registers |
| [ ] | S8 | Press switch | Key registers |

**Ring:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S9 | Press switch | Key registers |
| [ ] | S10 | Press switch | Key registers |
| [ ] | S11 | Press switch | Key registers |
| [ ] | S12 | Press switch | Key registers |

**Middle:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S13 | Press switch | Key registers |
| [ ] | S14 | Press switch | Key registers |
| [ ] | S15 | Press switch | Key registers |
| [ ] | S16 | Press switch | Key registers |
| [ ] | S25 | Press switch | Key registers |

**Index:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S17 | Press switch | Key registers |
| [ ] | S18 | Press switch | Key registers |
| [ ] | S19 | Press switch | Key registers |
| [ ] | S20 | Press switch | Key registers |
| [ ] | S26 | Press switch | Key registers |

**Inner:**
| # | Switch | Physical press | Expected |
|---|--------|---------------|---------|
| [ ] | S21 | Press switch | Key registers |
| [ ] | S22 | Press switch | Key registers |
| [ ] | S23 | Press switch | Key registers |
| [ ] | S24 | Press switch | Key registers |
| [ ] | S27 | Press switch | Key registers |

**Ghost key check — press multiple keys simultaneously:**
| # | Keys held | Expected |
|---|-----------|---------|
| [ ] | S1 + S2 | Both register, no phantom third key |
| [ ] | S5 + S9 (same diode column P6) | Both register, no phantom key |
| [ ] | S13 + S17 + S21 (all P6, diff P-col) | All three register correctly |

---

---

# STAGE 7 — Final System Tests

## 7A — Battery Operation Test

- [ ] **7A.1** Disconnect USB. Connect battery. PWR switch ON.
- [ ] **7A.2** Confirm XIAO boots (LED activity)
- [ ] **7A.3** Pair board via Bluetooth on your computer or phone
- [ ] **7A.4** Press 5 random keys — confirm they register wirelessly
- [ ] **7A.5** PWR switch OFF — confirm keyboard stops responding
- [ ] **7A.6** PWR switch ON — confirm keyboard reconnects

## 7B — Charging Test

- [ ] **7B.1** Keep battery connected and PWR switch ON
- [ ] **7B.2** Plug in USB-C
- [ ] **7B.3** 🔋 Check charge LED on XIAO (orange = charging, green = full)
- [ ] **7B.4** Confirm keyboard still works while charging (USB + battery simultaneously)

## 7C — Reset Function Test

- [ ] **7C.1** Press RST button once — confirm board resets and reconnects
- [ ] **7C.2** Double-tap RST — confirm board enters bootloader (appears as USB drive)
- [ ] **7C.3** Unplug USB — bootloader exits, normal operation resumes

---

## Fault Log

| Date | Stage | Component | Symptom | Root Cause | Fix Applied |
| ---- | ----- | --------- | ------- | ---------- | ----------- |
|      |       |           |         |            |             |
|      |       |           |         |            |             |
|      |       |           |         |            |             |
|      |       |           |         |            |             |
|      |       |           |         |            |             |

---

_Generated from board_pcb v1.0.0 KiCad file. Matrix: duplex (P0–P5 via switches, P6–P10 via diodes). 27 keys total._
