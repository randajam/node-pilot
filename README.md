# NodePilot

> Agent-first open-source platform for monitoring and managing Linux servers from a single web interface.

## Overview

**NodePilot** is an open-source remote management system for Linux hosts.

It is designed primarily for developers who maintain home servers, VPS instances, Raspberry Pi devices, or small clusters and want a convenient alternative to repeatedly connecting via SSH for routine operations.

Unlike many traditional management solutions, NodePilot follows an **Agent First** architecture.

The agent is the core of the system and is responsible for all interaction with the operating system. The backend acts only as a coordinator, while the frontend provides a web interface.

## Motivation

Managing one or more Linux servers usually involves repetitive tasks such as:

* checking CPU, memory and disk usage;
* viewing logs;
* restarting services;
* running common shell commands;
* monitoring long-running processes.

NodePilot aims to provide a unified dashboard for these operations while remaining lightweight, extensible and fully self-hosted.

---

## Architecture

```text
                 Browser
          React + TypeScript
                  │
          REST API / WebSocket
                  │
          ┌──────────────────┐
          │     Backend      │
          └────────▲─────────┘
                   ▲
                   │
          Persistent TCP connection
                   │
          ┌────────┴─────────┐
          │      Agent       │
          └────────▲─────────┘
                   │
               Linux API
```

The project follows several architectural principles:

* **Agent First**
* **Single Responsibility**
* **Dependency Injection**
* **Persistent Connections**
* **Extensible Design**

More details can be found in the architecture documentation.

---

## Repository Structure

```text
.
├── agent/        # C++ agent
├── backend/      # FastAPI backend
├── frontend/     # React frontend
├── docs/         # RFC, ADR and architecture documentation
└── scripts/      # Utility scripts
```

---

## Current Status

The project is under active development.

Current progress:

* ✅ Project architecture (RFC-001)
* ✅ Agent application lifecycle
* ✅ Metrics collection (CPU, RAM, Disk, Uptime)
* ✅ JSON serialization
* ✅ Transport abstraction (`ITransport`)
* ✅ Console transport
* 🚧 TCP transport
* ⏳ Backend
* ⏳ Web interface

---

## Building

Requirements:

* CMake 3.16+
* GCC 12+ or Clang 15+
* C++20

Build the agent:

```bash
cd agent

cmake -B build
cmake --build build

./build/nodepilot-agent
```

---

## Roadmap

The first public version (v0.1) includes:

* agent registration;
* persistent TCP connection;
* real-time metrics;
* command execution;
* service management;
* log viewing.

Future versions will include:

* Docker management;
* WireGuard integration;
* GPU monitoring;
* plugin system;
* embedded terminal;
* MLOps tools.

---

## Documentation

Project documentation is available in the `docs/` directory.

* `docs/architecture/rfc-001.md`
* `docs/architecture/adr/`

---

## Technologies

* **C++20**
* **CMake**
* **FastAPI**
* **Python**
* **React**
* **TypeScript**
* **Docker**
* **WebSocket**
* **TCP**

---

## License

This project is licensed under the MIT License.

---

## Author

Created by **randajam**.
