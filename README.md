# UE5 Tanks (C++ Gameplay Prototype)

A small-scale tank shooter prototype built with Unreal Engine 5 using C++.
The project focuses on **gameplay programming, architecture, and core combat systems**.

---

## 🎥 Gameplay Preview



---

## 🧩 Features

* Component-based tank architecture
* Health & damage system
* Weapon & projectile system with cooldown
* Basic AI with state machine (Idle / Move / Attack)
* GameMode & GameState match flow
* Win condition system (base destruction)
* HUD displaying health and reload status

---

## 🏗️ Architecture Overview

The project is structured around Unreal Engine gameplay framework:

```
TankPawn
 ├── HealthComponent
 ├── WeaponComponent
 ├── MovementComponent

TankAIController → controls AI tanks
PlayerController → handles player input

TanksGameMode → manages match flow
TanksGameState → stores match data

TankHUD → renders gameplay UI
```

### Key Design Decisions

* **Component-based design**
  Core gameplay systems (health, weapon, movement) are separated into reusable components.

* **Separation of responsibilities**

  * Pawn → high-level tank behavior
  * Components → specific mechanics
  * GameMode → game rules
  * AIController → decision-making

* **Simple AI state machine**
  AI switches between:

  * Idle
  * Moving to target
  * Attacking target

---

## 🔫 Combat System

* Tanks can fire projectiles with a cooldown
* Projectiles apply damage via `HealthComponent`
* Destruction of actors triggers GameMode events
* Win condition is determined by base destruction

---

## 🤖 AI Behavior

AI-controlled tanks:

* Search for targets (enemy tanks or base)
* Move toward targets
* Attack when in range
* Switch states based on distance and target validity

---

## 🧠 What This Project Demonstrates

* Understanding of Unreal Engine gameplay framework
* C++ gameplay systems implementation
* Component-based architecture
* Basic AI logic and state management
* Interaction between gameplay systems (damage, weapons, game rules)

---

## 🚀 Possible Improvements

* Add team system and friendly-fire checks
* Improve AI decision-making and performance
* Replace Canvas HUD with UMG widgets
* Introduce different weapon types (data-driven)
* Optimize target search (avoid GetAllActorsOfClass)
* Add multiplayer support (replication)

---

## 🛠️ Tech Stack

* Unreal Engine 5.7
* C++
* Unreal Gameplay Framework

---

## ▶️ How to Run

1. Clone the repository
2. Open the `.uproject` file in Unreal Engine 5
3. Build the project
4. Press Play in editor

---

## 📌 Notes

This is a learning project focused on gameplay programming and system design rather than visuals or content.

---

