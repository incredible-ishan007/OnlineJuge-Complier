
# OnlineJudge-Compiler

A web-based Online Judge and Compiler platform that allows users to practice programming problems, submit C++ solutions, and receive automated evaluation results.

The project combines a React-based frontend, Node.js backend, and a custom C++ judging system to provide an integrated coding environment.

## Features

- User Registration and Login
- JWT-Based Authentication
- Browse and Filter Programming Problems
- Submit C++ Solutions
- Automated Code Compilation and Execution
- Test Case-Based Evaluation
- Time Limit and Memory Limit Enforcement
- Submission History
- Accepted and Rejected Submission Results
- Custom Test Case Checking

## Tech Stack

### Frontend
- React.js
- Vite
- JavaScript
- CSS

### Backend
- Node.js
- Express.js
- MongoDB
- JWT Authentication

### Judge System
- C++
- Windows Process Management
- Automated Test Case Evaluation
- Custom Checkers

## System Architecture

The application consists of three major components:

1. **Frontend:** Provides the user interface for authentication, problem browsing, code submission, and viewing results.
2. **Backend:** Handles authentication, API requests, submission management, and communication with the judging system.
3. **Judge:** Compiles and executes submitted C++ programs against predefined test cases and determines the submission result.

## Project Structure

```text
OnlineJuge-Complier/
├── backend/
│   ├── app.js
│   ├── controllers/
│   ├── routes/
│   ├── models/
│   └── middleware/
│
├── frontend/
│   ├── src/
│   │   ├── components/
│   │   └── pages/
│   └── package.json
│
├── judge/
│   ├── problems/
│   ├── submissions/
│   └── judge.cpp
│
└── .gitignore
```

## Getting Started

### Prerequisites

- Node.js and npm
- MongoDB
- C++ Compiler (g++)
- Windows Operating System

### 1. Clone the Repository

```bash
git clone https://github.com/incredible-ishan007/OnlineJuge-Complier.git
cd OnlineJuge-Complier
```

### 2. Setup the Backend

Open a terminal:

```bash
cd backend
npm install
npm start
```

Configure the required environment variables in the backend `.env` file before starting the server.

### 3. Setup the Frontend

Open another terminal:

```bash
cd frontend
npm install
npm run dev
```

Open the local development URL provided by Vite in your browser.

### 4. Run the Judge

The judging system compiles and executes submitted C++ programs against the configured test cases.

The judge executable can be run using the project's configured command:

```powershell
.\judge.exe <problem_id> submissions\solution.cpp
```

Replace `<problem_id>` with the required problem identifier.

## Screenshots

Add screenshots of the application here.

<!--
![Login Page](screenshots/login.png)

![Problem Page](screenshots/problem-page.png)

![Submission Result](screenshots/submission-result.png)
-->

## Contributors

| Name | Student ID |
|------|------------|
| Ishan Garg | 24106039 |
| Gracy | 24106026 |

## Academic Project

Developed as an academic project to demonstrate the implementation of an online coding platform with automated code compilation, execution, and evaluation.
