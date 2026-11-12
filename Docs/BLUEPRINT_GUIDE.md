# Blueprint & UI Implementation Guide (Unreal Editor)

Bu rehber, takimin Unreal Editor icinde yapacagi Blueprint/UI islerini siralar.

## 1. Proje acilisi
1. Epic Games Launcher -> Unreal 5.4 -> NASA-OYUN.uproject ac.
2. Ilk acilista "Generate Visual Studio project files" onayla.
3. Solution'i build et (Development Editor).
4. Editor acilinca Content Browser -> Data -> DataTables olustur:
   - DT_Instruments (row struct: FInstrumentRow) <- import Content/Data/DT_Instruments.csv
   - DT_BusComponents (FBusComponentRow) <- DT_BusComponents.csv
   - DT_LaunchVehicles (FLaunchVehicleRow) <- DT_LaunchVehicles.csv
   - DT_Orbits (FOrbitRow) <- DT_Orbits.csv
   - DT_Missions (FMissionRow) <- DT_Missions.csv
   - DT_Events (FMissionEventRow) <- DT_Events.csv

## 2. Level'ler
- Content/Maps/MainMenu (Level Blueprint minimal).
- Content/Maps/MissionDesigner (ana oyun level'i).
- GameMode override: MissionGameMode, GameState: MissionGameState, PlayerState: MissionPlayerState.

## 3. Widget Blueprint'leri (base C++ siniflarindan turet)
Tum widget'lar C++ base class'i secerek olusturulur (Parent Class -> NASAOYUN module).

### WBP_MainMenu (parent: UUserWidget)
- Buttons: Single Player, Team Play (Host/Join), Sandbox, Quit.
- Host -> Create Session (listen server) + OpenLevel MisionDesigner?listen.
- Join -> Find Sessions + Join.

### WBP_MissionDesigner (parent: UMissionDesignerWidget)
- Tabs (Widget Switcher): Spacecraft / Payload / Launch / Orbit / Resources.
- Spacecraft tab: Grid of bus component cards (from DT_BusComponents). Select toggle -> add to design.
- Payload tab: Grid of instrument cards (from DT_Instruments). Select toggle.
- Launch tab: list of launch vehicles (from DT_LaunchVehicles).
- Orbit tab: list of orbits (from DT_Orbits).
- Resources tab: toplam kaynaklar + validation mesajlari.
- "Run Simulation" button -> enabled only if validation passes.

### WBP_HUD (parent: UMissionHUDWidget)
- Mass bar, Power bar (gen/draw), Budget bar, Data bar, Comms bar, Lifetime indicator.
- Bind to RefreshResources / UpdateResourceBars events.

### WBP_Simulation (parent: UMissionSimulationWidget)
- Zaman cizelgesi (Timeline widget) 1..N ay.
- Event log scroll box; her event icin kart (title + description + severity rengi).
- "Skip" / "Continue" butonlari.

### WBP_Results (parent: UMissionResultsWidget)
- Grade (buyuk), toplam skor, alt skorlar (Science/Efficiency/Reliability/Collab).
- Event ozeti, post-mission analiz metni.
- "Save Design" (SaveGame), "Share", "New Mission", "Main Menu".

## 4. Veri binding
- DataTable'lari GameInstance (UMissionGameInstance) veya GameMode uzerinden cache'le.
- Designer widget Event Construct'ta GameInstance'dan DataTable referanslarini al.
- Kaynak hesaplama: UMissionResourceManager::ComputeBudget + Validate (Blueprint'ten cagrilabilir, UFUNCTION).
- Bilimsel toplam: UMissionDataLibrary::SumScienceValue.
- Firlatma kapasitesi: UMissionDataLibrary::GetLaunchCapacity.

## 5. Simulasyon akisi (Blueprint)
1. Validate -> if not valid, mesajlari goster, dur.
2. UMissionSimulationSubsystem::RunSimulation(Design, Mission, MonthsToSimulate, Budget).
3. WBP_Simulation::PlaySimulation(Events, Duration).
4. Her event icin ses/VFX tetikle.
5. UMissionScoringLibrary::ComputeScore(...).
6. WBP_Results::ShowResults(Score, Events).
7. SaveGame (UMissionSaveGame) ile kaydet (slot name = mission id + timestamp).

## 6. Multiplayer (team mode)
- Host: "Create Session" (Online Subsystem Null veya Steam) + ServerTravel to MissionDesigner?listen.
- Client: "Find Sessions" + Join.
- Role secimi: MissionGameState uzerinden (Server RPC). Her oyuncu bir EMissionRole secar.
- Tasarimi kilitle: tum oyuncular onaylayinca (Server RPC) bDesignLocked=true.
- Katki skoru: her rolun sorumlu oldugu secim sayisi (client -> server RPC ile raporlanir).

## 7. Gorsel stil
- Tema: "Mission Control" - koyu arka plan (#0B0F1A), neon yesil/kirmizi aksanlar, monospace font (Roboto Mono / JetBrains Mono).
- Kaynak barlari renk kodlu: yesil (>60%), sari (30-60%), kirmizi (<30%).
- 3D uzay araci: exploded view, bileşenler tiklanabilir.

## 8. Ses & VFX
- UI click/hover sesleri, basarili/uyari sesleri.
- Simulasyon event'leri icin parca efektleri (Niagara).
- Arka plan muzigi: ambient space drone.

## 9. Test senaryolari
- 3 gorev x 3 zorluk = 9 kombinasyon.
- Edge case: max kutle, sifir guc, sifir butce.
- Multiplayer: 2/3/4 oyuncu senkronizasyonu.
