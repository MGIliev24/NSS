<div align="center">

<img src="https://github.com/MGIliev24/NSS/raw/main/assets/logo.png" width="300" height="300" alt="NSS Logo">

# 🎓 Nexus School Software (NSS)

![Version](https://img.shields.io/badge/version-1.0-blue)
![Language](https://img.shields.io/badge/language-C++-00599C?logo=cplusplus)
![Status](https://img.shields.io/badge/status-active-success)


**An interactive educational platform for learning web development and testing IT knowledge**

</div>

---

<div align="center">

## 📋 Table of Contents

</div>

* [🎯 About the Project](#about-the-project)
* [🚀 Core Features](#core-features)
* [🛠️ Used Technologies](#technologies)
* [📊 System Overview](#system-overview)
* [👥 Contributors](#contributors)
* [📥 Installation](#installation)

---

<div align="center">
<h2 id="about-the-project">🎯 About the Project</h2>
</div>

**Nexus School Software (NSS)** is a C++-based educational system designed to help students **learn and practice web development fundamentals** in an interactive way.

### ✨ What students can do:

* 📚 Study HTML, CSS, and JavaScript
* 🧠 Take randomized tests
* 📈 Track performance and progress
* 🔐 Use a secure account system

### 🧩 Smart System

Each test is uniquely generated using the student ID as a seed.

---

<div align="center">
<h2 id="core-features">🚀 Core Features</h2>
</div>

### 🔐 Authentication System (`auth.cpp`)

* Registration & login
* Duplicate prevention
* Multi-user support

---

### 📘 Learning Module (`question.cpp`)

* HTML basics
* CSS styling
* JavaScript fundamentals

---

### 📝 Testing Engine (`test.cpp`)

* 30-question pool
* 20 randomized per test
* Balanced categories
* Instant grading

---

### 📊 Statistics Dashboard (`statistics.cpp`)

* Total tests taken
* Highest / lowest score
* Average performance
* Category breakdown
* Strength & weakness detection

  ---

<div align="center">
<h2 id="resources">📄 Project Resources</h2>

<br>

<a href="documentation/presentation.pptx">
  <img src="https://img.shields.io/badge/Presentation-View-blue?style=for-the-badge&logo=microsoftpowerpoint&logoColor=white" />
</a>

<a href="documentation/documentation.docx">
  <img src="https://img.shields.io/badge/Documentation-Read-green?style=for-the-badge&logo=microsoftword&logoColor=white" />
</a>

</div>

---

### ⚙️ Input Validation

* Prevents invalid input
* Stable execution

---

<div align="center">
<h2 id="technologies">🛠️ Used Technologies</h2>

<br>

<a href="https://cplusplus.com/"><img src="https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=white&style=for-the-badge" style="margin:0"/></a><a href="https://visualstudio.microsoft.com/"><img src="https://img.shields.io/badge/Visual%20Studio-5C2D91?logo=visualstudio&logoColor=white&style=for-the-badge" style="margin:0"/></a><a href="https://github.com/"><img src="https://img.shields.io/badge/GitHub-181717?logo=github&logoColor=white&style=for-the-badge" style="margin:0"/></a><a href="https://www.microsoft.com/microsoft-365/word"><img src="https://img.shields.io/badge/Microsoft%20Word-2B579A?logo=microsoftword&logoColor=white&style=for-the-badge" style="margin:0"/></a><a href="https://www.microsoft.com/microsoft-365/powerpoint"><img src="https://img.shields.io/badge/PowerPoint-B7472A?logo=microsoftpowerpoint&logoColor=white&style=for-the-badge" style="margin:0"/></a><a href="https://www.microsoft.com/microsoft-teams"><img src="https://img.shields.io/badge/Microsoft%20Teams-6264A7?logo=microsoftteams&logoColor=white&style=for-the-badge" style="margin:0"/></a>

</div>

---

<div align="center">
<h2 id="system-overview">📊 System Overview</h2>
</div>

| Component        | Responsibility       |
| ---------------- | -------------------- |
| `auth.cpp`       | User management      |
| `question.cpp`   | Lessons & content    |
| `test.cpp`       | Testing logic        |
| `statistics.cpp` | Performance tracking |

---

<div align="center">
<h2 id="contributors">👥 Contributors</h2>
</div>

<table>
  <tr>
    <td align="center" width="250">
      <img src="https://github.com/MGIliev24/NSS/raw/main/assets/altai.jpg" width="120" height="120" style="border-radius: 50%; border: 3px solid #0078d4;" alt="Altai"><br><br>
      <b>Алтай Йеменджиев</b><br>
      <sub>🎯 Scrum Trainer</sub>
    </td>
    <td align="center" width="250">
      <img src="https://github.com/MGIliev24/NSS/raw/main/assets/az.jpg" width="120" height="120" style="border-radius: 50%; border: 3px solid #0078d4;" alt="Miroslav"><br><br>
      <b>Мирослав Илиев</b><br>
      <sub>⚙️ Back-End Developer</sub>
    </td>
  </tr>
  <tr height="50"></tr>
  <tr>
    <td align="center" width="250">
      <img src="https://github.com/MGIliev24/NSS/raw/main/assets/jordan.jpg" width="120" height="120" style="border-radius: 50%; border: 3px solid #0078d4;" alt="Jordan"><br><br>
      <b>Йордан Райнов</b><br>
      <sub>🎨 Front-End Developer</sub>
    </td>
    <td align="center" width="250">
      <img src="https://github.com/MGIliev24/NSS/raw/main/assets/artem.jpg" width="120" height="120" style="border-radius: 50%; border: 3px solid #0078d4;" alt="Artem"><br><br>
      <b>Артем Бок</b><br>
      <sub>🖌️ Designer</sub>
    </td>
  </tr>
</table>

---

<div align="center">
<h2 id="installation">📥 Installation</h2>
</div>

### ⚙️ Requirements

* Windows OS
* Visual Studio 2022
* Git

---

### 📦 Setup

```bash
git clone https://github.com/MGIliev24/NSS.git
cd NSS/nexusSchoolSoftware
