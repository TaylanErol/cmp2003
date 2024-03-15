# Movie Ratings Data Analysis Tool

## Overview

This tool is designed to import, save, and analyze movie ratings data from a CSV file. The core functionality includes setting a file name for data import, saving and organizing user and movie rating data into internal structures, and providing analyses such as printing saved data, identifying top users and movies by the number of ratings, and calculating similarity indexes based on cosine similarity.

## Features

- **Set File Name**: Users can specify the name of the CSV file containing the movie ratings data.
- **Import and Save Data**: Imports data from a specified file and saves it into internal data structures for efficient processing and analysis. The function ensures data uniqueness and proper association between users and movies.
- **Print Saved Data**: Displays all saved user data, including user IDs, movie IDs, and ratings.
- **Print Top 10 Users**: Identifies and displays the top 10 users who have rated the most movies.
- **Print Top 10 Movies**: Identifies and displays the top 10 movies that have received the most ratings.
- **Get User Count**: Returns the total number of unique users who have rated movies.
- **Get Movie Count**: Returns the total number of unique movies that have been rated.
- **Cosine Similarity Calculation (WIP)**: A work-in-progress feature for calculating the similarity index between users based on their ratings.

## Installation

1. Ensure you have a C++ compiler installed on your system.
2. Download or clone the project repository.
3. Compile the project using your C++ compiler. For example, if you are using `g++`, you can compile the project with the following command:

```bash
g++ -o movieRatingsTool term_project.cpp
