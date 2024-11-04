# 🔍 HeapLeakDetection Registry Forensics

## 🎯 Overview
HeapLeakDetection, specifically the registry key at `HKLM\Software\Microsoft\RADAR\HeapLeakDetection\DiagnosedApplications`, is a powerful forensic artifact for investigating suspicious executables. This key tracks programs that Windows RADAR (Runtime Application Self-healing and Detection At Runtime) flags for memory leak detection.

## 🏗️ Structure and Significance
- 📝 Registry Location: `HKLM\Software\Microsoft\RADAR\HeapLeakDetection\DiagnosedApplications`
- 📊 Contains subkeys for each detected executable
- ⏰ Records `LastDetectionTime` for each detection event
- 🔄 Continuously monitors system-wide memory behavior

## 🔬 How Detection Works
According to [research by Harel Segev](https://harelsegev.github.io/posts/the-mystery-of-the-heapleakdetection-registry-key/), RADAR monitors processes based on several factors:
- 📈 Commits at least 5% of total physical memory (CommitThreshold)
- ⏱️ Checks processes at regular intervals (TimerInterval)
- 🕒 Maintains detection history to prevent duplicate entries

## 🛠️ Memory Leak Simulation Tool
This repository includes a C++ program that demonstrates how to trigger Windows RADAR HeapLeakDetection:

### Features
- 💾 Controlled memory allocation in configurable chunks
- 📊 Real-time allocation monitoring
- ⚡ Optimized for RADAR detection
- 🔄 Continuous execution until detection

### Usage
1. Clone this repository
2. Build using provided build script or Visual Studio
3. Run as administrator
4. Monitor registry for detection entry

## 🔍 Forensic Value
As highlighted by [security researchers](https://x.com/samaritan_o/status/1848743680384889031), this artifact provides:
- 🕵️ Alternative evidence source when traditional artifacts are missing
- ⏰ Temporal correlation for suspicious executables
- 🧪 Behavioral insights into application memory patterns
- 🛡️ Resilience against common anti-forensic techniques

## 📚 References
- [The Mystery of the HeapLeakDetection Registry Key](https://harelsegev.github.io/posts/the-mystery-of-the-heapleakdetection-registry-key/)
- [Twitter Thread on Forensic Applications](https://x.com/samaritan_o/status/1848743680384889031)

## 🤝 Contributing
Contributions are welcome! Please feel free to submit pull requests or open issues for improvements.
