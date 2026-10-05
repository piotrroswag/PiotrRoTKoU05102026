# World Reactivity & Action Logic System - Gameplay Programming Test

The project allows for designing logic based on events and actions. 

## 🚀 Quick Start
* **Engine Version:** Unreal Engine 5.5.4
* **Test Level:** `/Content/Maps/L_TestMap.umap`
* **Map contains:**
	* `ActorA` `ActorB` `Player` `hidden layer - StreamLevel`
* **Controls:** 
  * `W` `A` `S` `D` `Space`
  * `Escape` - Exit the simulation.
  * 
---

## 🏛️ Architectural structure
An action is a discrete unit of logic used to build gameplay. Events are containers for data actions `UWrActionData`. Each action contains a data that is processed by a DataAsset. Each action also contains logic `UWrActionLogicBasic` that is executed by a UObject. Event also contains conditions<br>
Event<br>
	&emsp;- Condition 1,<br>
	&emsp;- Condition 2,<br>
	&emsp; <br>
	&emsp;- Data Action 1,<br>
	&emsp;- Data Action 2,<br>
	&emsp;- Data Action n<br>
	&emsp;...<br>
Events can be assigned to gameplay time using `UWrWorldTimeEventConfig`

---
 
## 🧱 Composition
`UWrActionEventComponent` is the place where events are iterated, added, and removed. The component includes a filtering mechanism that passes through only the relevant data action. Data action registered within the component creates the corresponding logic. Any actor wishing to receive events must have a `UWrActionEventComponent` attached. Such granularity of actions allows for their repeated use (first ActorA chases ActorB, and then the Player), same logic different data.
<br><br>
The project consists of subsystems: one `UWrWorldTimeSubSystem` for time management, and another `UWrWorldTimeEventConfig` that handles events based on gameplay time. The entire structure was designed to allow for the easy addition of further events (composed of actions).<br>
The game logic also features an entity known as `UWrEventContext`. This allows for the easy passing of dynamic data (which must be calculated on the fly) to the action logic. That context is use inside `UWrEventCondition` to check if component can receive event

---

## 📈 Further improvements
A `condition` mechanism can be introduced to data actions to check whether a given action could be performed. 

---

## 🔍 Ambiguity in the test task
1. Task states that the actors move-roaming around the map. 
That’s why I created an action (event) that allows for this. This action is triggered at 10:00.
2. Task states: 'actor disappears'. The task does not describe exactly what this means. That’s why I created an action that removes the actor from the map (Destroy).
3. The task also does not specify what happens when the next day begins in the game. In my implementation, the events won't fire again.<br>

---

## 🛠️ Debug Utilities & CVars
`Wr.Debug.EventComponent.ShowDebug` is showing active action on Actor

---

## ℹ️ Other Information
In this task, I am not focusing on the visual aspect. I consider it sufficient.
