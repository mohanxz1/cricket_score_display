CRICKET_SCORE_DISPLAY
Transforming Live Scores into Instant Cricket Moments

  

Built with the tools and technologies:

Table of Contents
Overview
Getting Started
Prerequisites
Installation
Usage
Testing
Overview
cricket_score_display is a developer tool that facilitates the presentation of real-time cricket scores, integrating detailed match data and player statistics into a cohesive display. It serves as the backbone for building dynamic cricket scoreboards and analysis systems.

This project streamlines the process of tracking and displaying cricket match data. The core features include:

Data Structures: Well-organized definitions for players, teams, and match details, enabling comprehensive data management. The C code defines struct batsman to store batsman details (name, runs, balls, boundaries, strike rate) and struct bowler for bowler details (name, runs given, overs, wickets, economy, maiden overs).
Real-Time Updates: Supports dynamic score display, ensuring users see the latest match information.
Performance Metrics: Tracks individual performance metrics like runs, balls faced, boundaries, and bowling economy. The C code calculates strike rate for batsmen and economy for bowlers.
User-Friendly Design: Provides an intuitive framework for integrating and presenting cricket scores effectively.
Extensible Architecture: Built with foundational components that can be expanded for advanced analysis and features.
Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

Prerequisites
To compile and run this C program, you will need:

A C compiler (e.g., GCC).
Installation
Clone the repository (if applicable):

Bash

git clone https://github.com/your-username/cricket_score_display.git
cd cricket_score_display
(Note: Replace your-username and cricket_score_display with the actual GitHub username and repository name if this project is hosted on GitHub.)

Compile the C code:

Bash

gcc finaldef.c -o cricket_score_display
Usage
To run the program and input match data:

Execute the compiled program:

Bash

./cricket_score_display
Follow the prompts:
The program will guide you through entering match details such as:

Team names (e.g., "India", "Australia")
Venue (e.g., "Lords Cricket Ground")
Date (e.g., "24,06,2025")
Toss winner and their decision (bat or bowl)
Number of batsmen and their individual statistics (runs in ones, twos, threes, fours, sixes, balls played) for both innings.
Number of bowlers and their individual statistics (runs given, overs bowled, wickets taken, maiden overs) for both innings.
Extras (wides, no-balls, byes, leg-byes) for each innings.
Navigate the Menu:
After all data is input, a menu will appear allowing you to view:

Individual batsman details for either team.
Individual bowler details for either team.
A complete match summary, including total scores, extras, highest batsman scores, and best bowling figures for both innings, and the final result.
The match summary will also be saved to a file named all_match_summaries.txt.
Testing
The provided code includes an interactive menu for viewing player statistics and a match summary, which serves as a form of functional testing for data accuracy and display.

To test the functionality:

Run the program as described in the Usage section.
Input various realistic and edge-case values for player statistics and extras.
Verify that the displayed individual player details and the overall match summary are accurate based on your inputs.
Check the all_match_summaries.txt file to ensure the match summary is correctly appended.
