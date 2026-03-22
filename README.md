<div align="center">
  
# 🎓 Nexus School Software (NSS)

![NSS Logo](https://img.shields.io/badge/Nexus%20School%20Software-v1.0-blue)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=cplusplus)
![Status](https://img.shields.io/badge/Status-Active-success)

**An interactive educational software platform for students to learn web development (HTML, CSS, JavaScript) and take IT assessments.**

</div>

---

## 📋 Table of Contents

- [About the Project](#about-the-project)
- [Core Features](#core-features)
- [Used Technologies](#used-technologies)
- [Download & Installation](#download--installation)
- [Project Structure](#project-structure)
- [Main Functions](#main-functions)
- [Contributors](#contributors)

---

<div align="center">

## 🎯 About the Project

</div>

**Nexus School Software (NSS)** is a comprehensive C++ educational platform designed to help students learn and master web development fundamentals. The application provides an interactive environment where students can:

- **Access Structured Lessons** on HTML, CSS, and JavaScript basics
- **Take Randomized Assessments** with a total of 20 questions (7 HTML, 7 CSS, 6 JavaScript)
- **Track Performance** with detailed statistics and grade calculations
- **Manage User Accounts** with secure login and registration system

The software uses a unique randomization system where each student receives a personalized question order based on their student ID, ensuring fair and consistent testing experiences.

### Key Functionality

| Feature | Description |
|---------|------------|
| **User Authentication** | Sign up and login system with account management |
| **Interactive Lessons** | Comprehensive tutorials on HTML, CSS, and JavaScript |
| **IT Assessment Test** | 20-question randomized test covering all three categories |
| **Statistics Dashboard** | Detailed performance tracking and grade analysis |
| **Student ID Seeding** | Personalized question randomization for each student |
| **Grade Calculation** | Automatic grading on a 2.0-6.0 scale based on percentage |

---

<div align="center">

## 🚀 Core Features

</div>

### 1. **Authentication System** (`auth.cpp`)
- User account registration (Sign up)
- Secure login with username and password
- Account validation and duplicate username prevention
- Support for multiple user accounts

### 2. **Lesson Management** (`question.cpp`)
Three comprehensive lessons:
- **HTML Basics**: Learn about HTML tags, elements, and structure
- **CSS Basics**: Understand styling, properties, and CSS selectors
- **JavaScript Basics**: Master variables, functions, loops, and events

### 3. **Adaptive Testing** (`test.cpp`)
- 30 total questions (10 per category)
- 20-question randomized tests
- Category distribution: 7 HTML + 7 CSS + 6 JavaScript
- Real-time answer validation and feedback
- Automatic grading system

### 4. **Statistics & Analytics** (`statistics.cpp`)
- Total tests completed tracking
- Highest and lowest grade records
- Average grade calculation
- Per-category performance metrics (HTML, CSS, JavaScript)
- Best and weakest category identification

### 5. **Input Validation & Error Handling**
- Robust menu input validation
- Prevention of invalid numeric entries
- Graceful error recovery

---

<div align="center">

## 🛠️ Used Technologies

</div>

<table>
<tr>
<td align="center" width="16.66%">
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" width="50" height="50" alt="C++"/>
<br/>
<strong>C++</strong>
<br/>
<a href="https://cplusplus.com/" rel="noopener noreferrer">Official Site</a>
</td>
<td align="center" width="16.66%">
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/visualstudio/visualstudio-plain.svg" width="50" height="50" alt="Visual Studio"/>
<br/>
<strong>Visual Studio 2022</strong>
<br/>
<a href="https://visualstudio.microsoft.com/" rel="noopener noreferrer">Official Site</a>
</td>
<td align="center" width="16.66%">
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" width="50" height="50" alt="GitHub"/>
<br/>
<strong>GitHub</strong>
<br/>
<a href="https://github.com/" rel="noopener noreferrer">Official Site</a>
</td>
<td align="center" width="16.66%">
<img src="https://img.icons8.com/color/452/microsoft-word-2019--v1.png" width="50" height="50" alt="MS Word"/>
<br/>
<strong>Microsoft Word</strong>
<br/>
<a href="https://www.microsoft.com/en-us/microsoft-365/word" rel="noopener noreferrer">Official Site</a>
</td>
<td align="center" width="16.66%">
<img src="https://img.icons8.com/color/452/microsoft-powerpoint-2019--v1.png" width="50" height="50" alt="MS PowerPoint"/>
<br/>
<strong>Microsoft PowerPoint</strong>
<br/>
<a href="https://www.microsoft.com/en-us/microsoft-365/powerpoint" rel="noopener noreferrer">Official Site</a>
</td>
<td align="center" width="16.66%">
<img src="https://img.icons8.com/color/452/microsoft-teams.png" width="50" height="50" alt="MS Teams"/>
<br/>
<strong>Microsoft Teams</strong>
<br/>
<a href="https://www.microsoft.com/en-us/microsoft-teams/group-chat-software" rel="noopener noreferrer">Official Site</a>
</td>
</tr>
</table>

### Technology Stack Details

- **Primary Language**: C++ (Standard Library)
- **IDE**: Visual Studio 2022 Community/Professional
- **Version Control**: Git & GitHub
- **Documentation Tools**: Microsoft Word, PowerPoint
- **Communication**: Microsoft Teams
- **Build System**: Visual Studio Project (.vcxproj)

---

<div align="center">

## 📥 Download & Installation

</div>

### Prerequisites
- Windows OS (Visual Studio 2022 compatible)
- Git installed on your system
- Visual Studio 2022 with C++ development tools

### Clone the Repository

```bash
# Using HTTPS
git clone https://github.com/MGIliev24/NSS.git

# Using SSH
git clone git@github.com:MGIliev24/NSS.git

# Navigate to the project directory
cd NSS/nexusSchoolSoftware
