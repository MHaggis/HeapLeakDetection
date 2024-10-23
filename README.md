# HeapLeakDetection

## Overview

HeapLeakDetection, specifically the registry key at `HKLM\Software\Microsoft\RADAR\HeapLeakDetection\DiagnosedApplications`, is a valuable yet lesser-known artifact when investigating malicious executables. This key, residing in the Software hive, records executables that RADAR (Runtime Application Self-healing and Detection At Runtime) has detected for potential memory leaks.

## Structure and Significance

- The key contains subkeys representing individual executables.
- Each subkey records a `LastDetectionTime`, indicating when RADAR last detected a memory leak from the executable.
- While RADAR primarily focuses on system performance and diagnostics, this information serves as a crucial forensic artifact for investigators.

## Forensic Value

1. **Alternative Evidence Source**: Particularly useful when traditional evidence (e.g., Prefetch files, event logs) is missing or tampered with.
2. **Temporal Correlation**: Helps tie malicious executables to memory issues at specific times.
3. **Behavioral Insights**: Provides leads to investigate an application's behavior, potentially exposing malicious activity.
4. **Resilience to Anti-Forensics**: Often overlooked by attackers, offering unaltered data in post-intrusion scenarios.

## Investigative Application

- Analysts can use this registry key to track memory leak detection over time for specific executables.
- It serves as a fresh, unaltered point of reference in post-intrusion investigations.
- The data can guide deeper analysis into suspicious application behavior.

## Visual Evidence

Screenshots from test environments typically showcase:
- Subkeys representing different executables
- `LastDetectionTime` values for each subkey
- Chronological tracking of memory leak detections

By leveraging this often-overlooked artifact, investigators can uncover valuable leads and correlate malicious activity that might otherwise go unnoticed.

# Memory Leak Simulation for HeapLeakDetection

This project contains a simple C++ program that simulates a memory leak to trigger Windows RADAR HeapLeakDetection.

## Contents

- `heapmemleak.c++`: The source code for the memory leak simulation.
- `.github/workflows/build-and-test.yml`: GitHub Actions workflow for building and testing the program.

## How it works

The `heapmemleak.c++` program continuously allocates memory without freeing it, simulating a memory leak. This is designed to trigger the Windows HeapLeakDetection mechanism.

## GitHub Actions Workflow

The included GitHub Actions workflow does the following:

1. Compiles the `heapmemleak.c++` file.
2. Runs the compiled executable for a short period.
3. Checks for the presence of the HeapLeakDetection registry key.

To use this workflow:

1. Fork or clone this repository.
2. Push changes to the `main` branch or create a pull request.
3. The workflow will automatically run.
4. You can also manually trigger the workflow from the Actions tab in the GitHub repository.

## Local Testing

To run the test locally:

1. Compile the `heapmemleak.c++` file.
2. Run the compiled executable.
3. Check the registry key: `HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\HeapLeakDetection`

Note: Running this program may consume significant system resources. Use with caution and only on systems you have permission to test on.
