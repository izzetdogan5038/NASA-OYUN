# AstraTeam - Space Mission Design Game

NASA Space Apps Challenge 2026 (Kayseri) entry.
Team: AstraTeam (Izzet, Ali Firat, Elif Sebnem, Buglem, Eymen).

An interactive Unreal Engine 5 game that lets players design, manage and simulate a
complete space mission - choosing objectives, spacecraft bus components, scientific
instruments, launch vehicle and orbit - while balancing mass, power, budget, data,
communications and lifetime trade-offs. Supports single-player and team play
(up to 4 players with distinct roles).

## Engine and Stack
- Unreal Engine 5.4 (C++ + Blueprints)
- UMG for UI, DataTables for content, Listen Server for multiplayer

## Project Layout
    NASA-OYUN.uproject
    Config/                      Engine and game settings
    Content/Data/                CSV templates for DataTables
    Source/NASAOYUN/             C++ module
    Docs/                        Team plan, task assignment, roadmap

## How to open
1. Install Unreal Engine 5.4 via Epic Games Launcher.
2. Double-click NASA-OYUN.uproject (Generate Visual Studio project files).
3. Build the NASAOYUN module (Development Editor).
4. Import CSVs in Content/Data/ as DataTables choosing the matching row struct:
   - DT_Instruments.csv -> FInstrumentRow
   - DT_BusComponents.csv -> FBusComponentRow
   - DT_LaunchVehicles.csv -> FLaunchVehicleRow
   - DT_Orbits.csv -> FOrbitRow
   - DT_Missions.csv -> FMissionRow

## Gameplay Loop
Briefing -> Design -> Validation -> Simulation -> Evaluation -> Post-mission analysis.

## Team Roles
See Docs/TEAM_PLAN.md.

## License
MIT (code). Asset licenses vary.
