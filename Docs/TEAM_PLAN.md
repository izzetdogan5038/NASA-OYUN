# AstraTeam - Task Assignment and Plan

NASA Space Apps 2026 (Kayseri) - Space Mission Design Game - Unreal Engine 5
Team: AstraTeam (Izzet [Captain], Ali Firat, Elif Sebnem, Buglem, Eymen)

## Roles (primary + backup)
- Izzet (Captain): Lead Programmer / Systems Architect. C++ core (data model, Resource Manager, simulation, scoring, multiplayer), GameMode phases, architecture, scope control. Backup: Eymen.
- Elif Sebnem: Lead UI/UX and Visual Design. UMG widgets, HUD, style guide, 3D scene layout, post-mission analysis screen, art direction. Backup: Buglem.
- Ali Firat: Content and Narrative + Pitch Lead. Mission scenarios, instrument/launcher/orbit data, in-game text/tooltips, documentation, pitch deck, presentation. Backup: Buglem.
- Buglem: Content Implementation and QA Lead. DataTable entry, balancing playtests, bug tracking, asset/sound collection, test scenarios. Backup: Ali.
- Eymen: Gameplay and Blueprint Developer. Blueprint interaction flows, simulation animation, VFX, sound integration, scene setup. Backup: Elif.

## 48-hour sprint phases
- Phase 0 Setup (0-3h): repo, project, wireframes, scenario drafts, DataTable schemas.
- Phase 1 Core systems (3-12h): C++ structs, Resource Manager, GameMode phases, UI skeleton, first data entries.
- Phase 2 Content and UI (12-24h): launchers/orbits data, 3 missions, HUD, Blueprint flows, 3D preview, tooltips.
- Phase 3 Simulation and scoring (24-36h): sim tick + random events, scoring engine, sim animation, post-mission screen, balancing playtest.
- Phase 4 Multiplayer and polish (36-44h): listen server, roles UI, sound, VFX, bug fixing.
- Phase 5 Pitch and demo (44-48h): pitch deck, demo script, rehearsal, video capture, final build.

## Sleep rotation (2 sleep / 3 work)
Block 1 (0-8h): sleep Ali+Buglem; work Izzet,Elif,Eymen
Block 2 (8-16h): sleep Eymen+Ali; work Izzet,Elif,Buglem
Block 3 (16-24h): sleep Izzet+Elif; work Ali,Buglem,Eymen
Block 4 (24-32h): sleep Buglem+Eymen; work Izzet,Elif,Ali
Block 5 (32-40h): sleep Elif+Ali; work Izzet,Buglem,Eymen
Block 6 (40-48h): sleep Izzet+Eymen; work Elif,Ali,Buglem

## Handoff rules
1. Commit messages: [PHASE] [MODULE] short desc - @author
2. Stand-up every 4 hours (5 min).
3. Shared TODO board (GitHub Projects/Trello).
4. Sleepers start with git pull + build; fix broken build first.
5. Architectural/scope decisions require captain approval (Elif is deputy when Izzet sleeps).

## Scope control
MVP first (single-player flow + 3 missions + validation + sim + score). Nice-to-have cut order:
VR -> sandbox -> leaderboard -> sound -> 3D preview -> multiplayer -> (never cut MVP).

## Parallel workstreams
A. Core C++ (Izzet) - foundation, no dependency.
B. UI/Widgets (Elif,Eymen) - depends on struct interfaces (defined early).
C. Content/DataTables (Ali,Buglem) - depends on struct schemas (shared early).
D. Sound/VFX/Polish (Eymen) - depends on widgets.
E. Pitch/Docs (Ali,Elif) - continuous.
