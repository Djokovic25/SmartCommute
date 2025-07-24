# SmartCommute
# 🚇 SmartCommute – Metro Navigation System

SmartCommute is a C++ console-based metro route planner designed to simulate core metro app features using Data Structures and Algorithms. It supports shortest path finding, route history, and dynamic station blocking for maintenance.

---

## 🧠 Features

- ✅ **Shortest Route** using Dijkstra's algorithm
- 🕘 **Recent Route History** using Queue 
- 🚫 **Blocked Station Simulation** to avoid closed/under-maintenance stations
- 🧠 Modular & expandable design with C++ STL 

---

## 💻 Technologies Used

- C++ (STL)
- Graphs: Adjacency List
- Dijkstra’s Algorithm (Min Heap)
- Queue (History)
- Unordered Map (Name ↔ ID mapping)

---

## 🗺️ Sample Metro Network (Hardcoded)
                     [Baiyappanahalli]  
                            ↑    
                            | (6)
                     [Indiranagar]
                        ↑      ↖
                      (5)      (8)
                        |        \
                    [MG Road]    [Kempegowda Metro Station]
                      ↑   ↖           ↑
                    (4)   (6)        (7)
                      |      \      /
                  [Majestic]───[Vidhana Soudha]
                   ↑   ↖    ↖        ↑
                 (10)(7)  (3)        |
                 /     \   \         |
     [Banashankari]  [Mysore Road]  (6)
             ↖           ↑         /
             (15)       (5)      /
                \        |     /
               [Yeshwanthpur]
                      ↑
                     (4)
                      |
                [Rajajinagar]
                      ↑
                     (6)
                      |
                 [Jalahalli]

