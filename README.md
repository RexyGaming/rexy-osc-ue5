# Rexy OSC UE5

A complete Unreal Engine 5 virtual camera control system driven by the **Rexy Wheels** HID hand wheel controller, via OSC messaging.

Built by [Real Pro Gear](https://realprогear.com) — makers of Rexy Wheels.

---

## What This Is

This project lets you control a CineCamera in Unreal Engine 5 using the Rexy Wheels 2-axis hand wheel controller. Turning the wheels pans and tilts the virtual camera in real time, making it useful for virtual production, previsualization, and camera control testing.

**The signal chain:**

```
Rexy Wheels (USB HID) → Python Middleware (Mac/PC) → OSC → Unreal Engine 5
```

---

## What's Included

- Full UE5 project (`RexyOSC2`) with Open World template level
- Custom C++ actor (`RexyOSCActor`) that receives OSC and drives the camera
- Python middleware script (`rexy_middleware.py`) that reads HID input and sends OSC

---

## Requirements

- Rexy Wheels device (by Real Pro Gear)
- Unreal Engine 5.5 or later (tested on UE 5.7)
- Mac or PC
- Python 3.9+ with the following packages:
  - `pygame` (HID input)
  - `python-osc` (OSC output)
- UE5 plugins enabled:
  - **OSC** (built-in, just needs enabling in Plugins menu)

---

## Setup Guide

### Step 1 — Install Python dependencies

```bash
pip3 install pygame python-osc
```

### Step 2 — Run the middleware

Connect your Rexy Wheels via USB, then run:

```bash
python3 rexy_middleware.py
```

You should see output like:
```
Connected to: Real Pro Gear Rexy Wheels Device
Sending OSC to 127.0.0.1:8000
Pan: +0.0 | Tilt: +0.0
```

Turning the wheels will update the Pan and Tilt values in the terminal.

### Step 3 — Open the UE5 project

Open `RexyOSC2.uproject` in Unreal Engine 5. When prompted to rebuild modules, click **Yes**.

### Step 4 — Open the level

Open the level `RexyMain2` from the Content Drawer. It contains:
- `CineCameraActor` — the virtual camera
- `RexyOSCActor` — the OSC receiver (Target Camera is already set)
- `PlayerStart` — spawn point

### Step 5 — Hit Play

With the middleware running in Terminal, hit **Play** in Unreal. You should see on screen:
- 🟡 **RexyOSC: Camera reference is set!**
- 🟢 **RexyOSC: Server started on port 8000**
- 🟡 **RexyOSC: Camera view set**

Turn the wheels — the camera will pan and tilt in real time.

---

## OSC Message Format

| Address | Value | Description |
|---|---|---|
| `/rexy/wheels/pan` | float (degrees) | Yaw rotation |
| `/rexy/wheels/tilt` | float (degrees) | Pitch rotation |

Port: `8000` (UDP)
Host: `127.0.0.1` (localhost)

---

## Troubleshooting

**No green message on Play** — OSC plugin may not be enabled. Go to Edit > Plugins, search "OSC", enable it, restart.

**Red "Could not find camera" message** — Make sure a CineCameraActor exists in your level and the RexyOSCActor's Target Camera property is set to it.

**Middleware not detecting device** — Make sure Rexy Wheels is connected via USB before running the script.

**Camera not moving despite middleware running** — Check that UE5 is not blocking UDP port 8000 in your firewall settings.

---

## About Rexy Wheels

Rexy Wheels is a 2-axis hand wheel HID controller designed for virtual production camera control. Built on Raspberry Pi Pico, it connects via USB and outputs joystick HID signals.

More info: [Real Pro Gear Wiki](https://realprогear.miraheze.org)

---

## Licence

MIT — free to use, modify and share. Attribution appreciated.
