# U.S Traffic Accidents

This C++ program is part of a project designed to compare the performance of two different data structures, a Hash Table and a Red-Black Tree, in managing a large dataset of U.S. Traffic Accidents. Here’s a detailed explanation of how to use the program, its menu structure, and a summary of the project:

## How to use it

Upon launching the program, you're welcomed with a message about the U.S. Traffic Accidents database, which mentions that the data is stored using two data structures: a Red-Black Tree and a Hash Table. Here's how you can interact with the program:

### Choosing the Data Structure:

The program prompts you to choose between using a Red-Black Tree or a Hash Table. Based on your choice, you can interact with the dataset using the respective data structure.

### Menu Options:

Each data structure has its dedicated menu with the following options:

Insert: Add a new traffic accident record by entering details such as ID, severity, distance, city, state, and zipcode.

Search: Look up records by ID, severity, city, state, or zipcode. You can choose the attribute you want to search by.
Remove by ID: Delete a record from the structure using its unique ID.

Display: Show all records in the data structure. For the Red-Black Tree, this will be an in-order traversal, displaying the records in a sorted manner.

Filter: Apply filters based on severity, city, state, or zipcode. This allows for narrowing down the records to meet specific criteria.

Exit: Leave the menu and, depending on your choice, either return to the structure selection or exit the program.
Timing Operations:

Each operation is timed using <chrono>, which helps in evaluating the performance of the data structures for various operations.




## Authors

- [Daniel Mata](https://github.com/Danimata10)
- [Aaron Beschorner](https://github.com/aaronbesc)
- [Eric Krivoy](https://github.com/EKS2003)
