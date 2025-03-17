# 🎮 프로젝트명: Ymir Heist

- **개발 환경**: Unreal Engine, Visual Studio
- **개발 언어**: C++, Blueprint
- **개발 기간**: 2025.02.17 ~ 2025.03.07
- **개발 동기**:
  - **SF 기반의 하이스트 게임**을 언리얼 엔진을 활용해 개발.
  - **커스텀 총기 시스템**과 **인벤토리 시스템**을 직접 구현하여 유기적으로 연결.
  - FPS 게임에서의 시스템 이해와, 언리얼 엔진의 이해도를 높이고자 함.

📌 **[시연 영상 보기]([https://youtu.be/TT6TkHSnpaQ](https://www.youtube.com/watch?v=SnrPjFUvvFs&ab_channel=%ED%95%9C%EC%83%81%ED%98%81))**

---

# 🥇 팀원 구성 🥇

| 이름 | 담당 역할 |
| :--: | :-------: |
| **백의현** | 게임 모드 |
| **신중은** | 플레이어 애니메이션 |
| **정완훈** | UI |
| **한상혁** | 총기, 인벤토리 |
| **홍성래** | 적 AI 및 애니메이션 |

---

# 🔑 주요 구현 🔑

## 🔫 총기 시스템
- `CP_Guns` 클래스 제작하여 **히트스캔 및 투사체 방식**을 지원하는 총기 시스템 개발.
- **탄창 시스템** 구현: 탄약 소모 및 재장전 기능 포함.
- 다양한 **총기 부품(Barrel, Body, Trigger, Scope)**을 조합하여 **커스텀 총기** 제작 가능.
- `ACP_GunSpawn` 클래스를 활용한 **총기 부품 스폰 시스템** 구현:
  - 배럴, 바디, 트리거를 개별적으로 스폰하며 **회전 애니메이션 적용**.

---
<img width="1842" alt="3" src="https://github.com/user-attachments/assets/bed599d9-ebb6-4cbc-8c68-1d5d9894b9db" />





<img width="1842" alt="3" src="https://github.com/user-attachments/assets/81ec8e00-4743-4758-9396-bf88df5ec663" />



## 🎒 아이템 및 인벤토리 시스템
- `UCP_Inventory` 클래스를 활용한 **인벤토리 시스템** 개발.
- **아이템 종류**: 탄약(Ammo), 장비(Gear), 치료제(Heal), 총기 부품(Gun Parts).
- `ACP_ItemSpawn` 클래스를 사용하여 **랜덤 아이템 스폰 시스템** 구현.
- **아이템 습득 및 인벤토리 저장 기능** 적용.
- **인벤토리 UI** 개발 (WBP 활용):
  - 아이템을 마우스 **우클릭하여 장착 가능**.

---

<img width="1842" alt="3" src="https://github.com/user-attachments/assets/43f1b085-b7a5-497f-bed6-7d400bb097d3" />


# 🏆 게임 주요 특징 🏆
- **아이템 파츠**에 따라 달라지는 총기.
- **불릿 타임**을 활용한 시원한 전투 
- 최종 보스를 처치하고 **탈출 성공**을 목표로 함.

---


<img width="1868" alt="4" src="https://github.com/user-attachments/assets/ed8b80bb-a18d-4c51-8341-85d065239dff" />



